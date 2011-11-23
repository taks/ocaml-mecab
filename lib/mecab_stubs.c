
#include <mecab.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/alloc.h>
#include <caml/memory.h>

#define Mecab_val(x) (*((mecab_t **) Data_custom_val(x)))

void finalize_mecab_t( value mecab_v );
static struct custom_operations mecab_t_ops = {
 identifier: "mecab.macab_t",
 finalize:    finalize_mecab_t,
 compare:     custom_compare_default,
 hash:        custom_hash_default,
 serialize:   custom_serialize_default,
 deserialize: custom_deserialize_default
};

static inline value copy_mecab_t(mecab_t *mecab) {
    CAMLparam0();
    CAMLlocal1(mecab_v);

    mecab_v = caml_alloc_custom( &mecab_t_ops, sizeof(mecab_t *), 0, 1 );
    Mecab_val(mecab_v) = mecab;

    CAMLreturn(mecab_v);
}

CAMLprim value
ocaml_mecab_new2( value str_v ) {
    CAMLparam1(str_v);
    CAMLlocal1(mecab_v);

    mecab_t *mecab = mecab_new2(String_val(str_v));
    if(!mecab) {
        const char *err_str = mecab_strerror(mecab);
        mecab_destroy(mecab);
        caml_failwith(err_str);
    }
    mecab_v = copy_mecab_t(mecab);

    CAMLreturn(mecab_v);
}

void finalize_mecab_t( value mecab_v ) {
    mecab_destroy(Mecab_val(mecab_v));
}

CAMLprim value
ocaml_mecab_version( value unit ) {
    CAMLparam1(unit);

    CAMLreturn(caml_copy_string(mecab_version()));
}

CAMLprim value
ocaml_mecab_sparse_tostr( value mecab_v, value str_v) {
    CAMLparam2(mecab_v, str_v);

    mecab_t *mecab = Mecab_val(mecab_v);

    const char *result = mecab_sparse_tostr(mecab, String_val(str_v));

    if(!result) {
        const char *err_str = mecab_strerror(mecab);
        caml_failwith(err_str);
    }

    CAMLreturn(caml_copy_string(result));
}

CAMLprim value
ocaml_mecab_sparse_tostr2( value mecab_v, value str_v, value len_v ) {
    CAMLparam3(mecab_v, str_v, len_v);

    mecab_t *mecab = Mecab_val(mecab_v);

    const char *result = mecab_sparse_tostr2(mecab, String_val(str_v), Int_val(len_v));

    if(!result) {
        const char *err_str = mecab_strerror(mecab);
        caml_failwith(err_str);
    }

    CAMLreturn(caml_copy_string(result));
}

CAMLprim value
ocaml_mecab_nbest_sparse_tostr( value mecab_v, value N_v, value str_v ) {
    CAMLparam3(mecab_v, N_v, str_v);

    mecab_t *mecab = Mecab_val(mecab_v);

    const char *result = mecab_nbest_sparse_tostr(mecab, Int_val(N_v), String_val(str_v));

    if(!result) {
        const char *err_str = mecab_strerror(mecab);
        caml_failwith(err_str);
    }

    CAMLreturn(caml_copy_string(result));
}

CAMLprim value
ocaml_mecab_nbest_sparse_tostr2( value mecab_v, value N_v, value str_v, value len_v ) {
    CAMLparam4(mecab_v, N_v, str_v, len_v);

    mecab_t *mecab = Mecab_val(mecab_v);

    const char *result = mecab_nbest_sparse_tostr2(mecab, Int_val(N_v), String_val(str_v), Int_val(len_v));

    if(!result) {
        const char *err_str = mecab_strerror(mecab);
        caml_failwith(err_str);
    }

    CAMLreturn(caml_copy_string(result));
}

CAMLprim value
ocaml_mecab_nbest_init( value mecab_v, value str_v ) {
    CAMLparam2(mecab_v, str_v);

    mecab_t *mecab = Mecab_val(mecab_v);

    int result = mecab_nbest_init(mecab, String_val(str_v));

    if(result == 0) {
        const char *err_str = mecab_strerror(mecab);
        caml_failwith(err_str);
    }

    CAMLreturn(Val_unit);
}

CAMLprim value
ocaml_mecab_nbest_init2( value mecab_v, value str_v, value len_v ) {
    CAMLparam3(mecab_v, str_v, len_v);

    mecab_t *mecab = Mecab_val(mecab_v);

    int result = mecab_nbest_init2(mecab, String_val(str_v), Int_val(len_v));

    if(result == 0) {
        const char *err_str = mecab_strerror(mecab);
        caml_failwith(err_str);
    }

    CAMLreturn(Val_unit);
}

CAMLprim value
ocaml_mecab_nbest_next_tostr( value mecab_v ) {
    CAMLparam1(mecab_v);

    mecab_t *mecab = Mecab_val(mecab_v);

    const char *result = mecab_nbest_next_tostr(mecab);

    if(result == NULL) {
        const char *err_str = mecab_strerror(mecab);
        caml_failwith(err_str);
    }

    CAMLreturn(caml_copy_string(result));
}

/*** 辞書関連 ***/
static inline value ocaml_dict( const mecab_dictionary_info_t *dict ) {
    CAMLparam0();
    CAMLlocal1(result);

    result = caml_alloc(7, 0);

    Store_field(result, 0, caml_copy_string(dict->filename));
    Store_field(result, 1, caml_copy_string(dict->charset));
    Store_field(result, 2, Val_int((int)dict->size));
    Store_field(result, 3, Val_int(dict->type));
    Store_field(result, 4, Val_int((int)dict->lsize));
    Store_field(result, 5, Val_int((int)dict->rsize));
    Store_field(result, 6, Val_int((int)dict->version));

    CAMLreturn(result);
}

CAMLprim value
ocaml_mecab_dictionary_info( value mecab_v ) {
    CAMLparam1(mecab_v);
    CAMLlocal2(cli, cons);

    mecab_t *mecab = Mecab_val(mecab_v);

    const mecab_dictionary_info_t *dict = mecab_dictionary_info(mecab);
    cli = Val_emptylist;

    for(; dict; dict = dict->next) {
        cons = caml_alloc(2, 0);

        Store_field(cons, 0, ocaml_dict(dict));
        Store_field(cons, 1, cli);

        cli = cons;
    }

    CAMLreturn(cli);
}


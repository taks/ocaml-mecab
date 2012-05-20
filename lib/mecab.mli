
type t
external version: unit -> string = "ocaml_mecab_version"
external init: string -> t = "ocaml_mecab_new2"
external sparse_tostr: t -> string -> string = "ocaml_mecab_sparse_tostr"
external sparse_tostr2: t -> string -> int -> string = "ocaml_mecab_sparse_tostr2"
external nbest_sparse_tostr : t -> int -> string -> string = "ocaml_mecab_nbest_sparse_tostr"
external nbest_sparse_tostr2 : t -> int -> string -> int -> string = "ocaml_mecab_nbest_sparse_tostr2"
external nbest_init : t -> string -> unit = "ocaml_mecab_nbest_init"
external nbest_init2 : t -> string -> unit = "ocaml_mecab_nbest_init2"
external nbest_next_tostr : t -> string -> string = "ocaml_mecab_nbest_next_tostr"

type node = {
  surface : string;
  feature : string;
  id : int;
  rc_attr : int;
  lc_attr : int;
  posid : int;
  char_type : int;
  stat : int;
  isbest : bool;
  alpha : float;
  beta : float;
  prob : float;
  wcost : int;
  cost : int;
  prev : node option;
  next : node option;
}

external sparse_tonode : t -> string -> node = "ocaml_mecab_sparse_tonode"
external sparse_tonode2 : t -> string -> int -> node = "ocaml_mecab_sparse_tonode2"

val each_node : node -> (node -> unit) -> unit

(*** 辞書関連 ***)
type dic_type =
  | SYS_DIC
  | USR_DIC
  | UNK_DIC
type dictionay = { filename:string;
                   charset:string;
                   size:int;
                   dtype:dic_type;
                   lsize:int;
                   rsize:int;
                   version:int; }
external dictionary_info: t -> dictionay list = "ocaml_mecab_dictionary_info"

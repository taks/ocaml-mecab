open OUnit;;

let test_wakati () =
  let m = Mecab.init "-O wakati" in
  assert_equal "今日 も し ない と ね \n" (Mecab.sparse_tostr m "今日もしないとね");;

let test_node () =
  let m = Mecab.init "" in
  let list = Mecab.lazy_list_of_node m "今日もしないとね" in
  let surface_list = BatLazyList.to_list (BatLazyList.map (fun n -> n.Mecab.surface) list) in
  assert_equal ["今日"; "も"; "し"; "ない"; "と"; "ね"; ""] surface_list ;;

let suite =
  "suite">:::
    ["test_wakati">:: test_wakati;
     "test_node">::   test_node]
;;

let _ =
  run_test_tt_main suite
;;

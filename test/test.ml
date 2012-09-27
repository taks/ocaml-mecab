open OUnit;;

(* let test1 () = assert_equal "x" "x";; *)
let test_wakati () =
  let m = Mecab.init "-O wakati" in
  assert_equal "今日 も し ない と ね \n" (Mecab.sparse_tostr m "今日もしないとね");;

let test_node () =
  let m = Mecab.init "" in
  Mecab.each_node (Mecab.sparse_tonode m "今日もしないとね")
    (fun x ->  print_endline x.Mecab.surface);;

(* Name the test cases and group them together *)
let suite =
  "suite">:::
    ["test_wakati">:: test_wakati]
;;

let _ =
  run_test_tt_main suite
;;

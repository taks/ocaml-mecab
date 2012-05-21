
#directory "../_build/lib"
#load "mecab.cma"

let () =
  let m = Mecab.init "" in
  print_endline (Mecab.sparse_tostr m "今日もしないとね");

  Mecab.each_node (Mecab.sparse_tonode m "今日もしないとね")
    (fun x ->  print_endline x.Mecab.feature);
;;

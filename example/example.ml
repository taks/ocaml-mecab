
#directory "../_build/lib"
#load "mecab.cma"

let () =
  let m = Mecab.init "-Ochasen" in
  print_endline (Mecab.sparse_tostr m "今日もしないとね")
;;

let () =
  let m = Mecab.init "" in
  Mecab.each_node (Mecab.sparse_tonode m "今日もしないとね")
    (fun x ->  print_endline x.Mecab.feature)
;;

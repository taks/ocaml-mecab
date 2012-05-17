
def build()
  system("ocaml setup.ml -build")
end

task :watch do
  require 'listen'
  Listen.to('lib', filter: /\.(ml|mli|c)$/) do |modified, added, removed|
    build()
  end
end

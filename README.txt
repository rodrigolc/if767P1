#pmt

PMT: ferramenta que busca padrões em linhas de texto.

Sinopse:
    pmt [-a {a,k,s,d}] [-e NUM] [-p ARQUIVO] PADRAO ARQUIVO [ARQUIVO2...]
    Busca padrões em arquivos

    Usa algoritmos:
    Aho-Corasick
    Sellers
    KMP
    Dummy(Força Bruta)

       --algorithm -a ALGORITMO      Escolhe algoritmo
       --edit -e NUM     Define distancia de edição.
          Se usado, usará algoritmos aproximados
          exceto se um algoritmo exato for informado usando "-a"
       --pattern -p ARQUIVO      faz a busca com os padrões em ARQUIVO, um por linha
       --help -h     Mostra essa ajuda

Compilação
Para compilação, deve ser usado o comando `make`.

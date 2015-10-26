##Identificação
Rodrigo Lopes  
Implementou os algoritmos e a interface da cli.

##Implementação
Algoritmos Implementados:
KMP
Sellers
Aho-Corasick
Força Bruta

O algoritmo KMP será utilizado quando só é informado UM padrão.
Para mais padrões, o algoritmo de Aho-Corasick é utilizado, pois ele suporta tempo O(n) com varios padrões ao mesmo tempo.

O algoritmo Sellers é utilizado quando for informada uma distância de edição.

O algoritmo de força bruta só será utilizado caso o usuário use a flag "-a" para forçar um algoritmo.


Bugs:  
A implementação do algoritmo Wu-Manber não foi bem sucedida. O código está disponível como registro histórico.


##Testes

os testes foram medidos usando a ferramenta time.
O arquivo de entrada utilizado foi english.50MB disponivel em http://pizzachili.dcc.uchile.cl/texts/nlang/

bin/pmt -a k inheritance ~/Downloads/english.50MB  2.49s user 0.07s system 91% cpu 2.785 total

bin/pmt -a s inheritance ~/Downloads/english.50MB  11.87s user 0.65s system 95% cpu 13.164 total
bin/pmt -a s inheritance ~/Downloads/english.50MB  12.22s user 0.85s system 94% cpu 13.852 total
bin/pmt -a a inheritance ~/Downloads/english.50MB  5.34s user 0.08s system 94% cpu 5.738 total
bin/pmt -a d inheritance ~/Downloads/english.50MB  2.41s user 0.07s system 92% cpu 2.688 total

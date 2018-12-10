					FILTRO DE IMAGENS

				MURILO SIMIONATO ARNEMANN - 18/0107453
					TRABALHO FINAL DE APC
				      PROF. ALEXANDRE ZAGHETTO

INSTRUÇÕES DE USO

Para compilar o programa não é necessário utilizar nenhuma biblioteca adicional. Sugestão para linux:

"gcc Murilo_Simionato_Arnemann_Problema_1.c -o <nome_do_executável>"

Para rodar o programa é preciso utilizar o console do seu OS.
Para que o program rode você precisa informar 4 argumentos:

<1> = Nome da imagem a ser filtrada com a extensão

<2> = Tipo de Processamento da imagem sendo "0" ou "1"

<3> = Tamanho do filtro a ser utilizado, sendo ele ímpar (o programa irá rodar com numeros pares)

<4> = Nome da imagem pós processo de filtragem com a extensão

Tipos de processamento:

"0" = Ao utilizar o comando "0" o programa realizará uma filtragem por média

"1" = Ao utilizar o comando "1" o programa realizará uma filtragem por mediana

Exemplo generico do comando para rodar o programa:

"./<nome_do_executavel> <1> <2> <3> <4>"

Exemplo aleatorio do comando para rodar o programa:

"./meu_programa minha_imagem.bmp 0 3 minha_imagem_filtrada.bmp"

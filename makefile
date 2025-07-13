# Makefile simples
# Lembre-se: a linha de comando abaixo DEVE começar com um TAB.

meu_programa: main.cpp
	g++ -std=c++17 main.cpp -o meu_programa $(pkg-config --cflags --libs icu-uc icu-i18n)
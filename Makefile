CC=g++
FILES=./src/main.cc
OPTIONS=-Wall -Wextra -Wno-missing-field-initializers

default:
	${CC} ${FILES} ${OPTIONS}

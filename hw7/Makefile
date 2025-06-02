CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g

all: searchengine index_lib_test string_set_test string_list_test

searchengine: index_lib.o main.o string_list.o string_set.o 20_newsgroups
	$(CC) index_lib.o main.o string_list.o string_set.o -o searchengine

20_newsgroups: 20_newsgroups.tar.gz
	if test -d 20_newsgroups; then true; else tar xzvf 20_newsgroups.tar.gz; fi

string_set_test: string_set.o string_list.o string_set_test.o
	$(CC) string_set.o string_set_test.o string_list.o -o string_set_test

string_list_test: string_list.o string_list_test.o
	$(CC) string_list.o string_list_test.o -o string_list_test

index_lib_test: index_lib.o index_lib_test.o string_list.o string_set.o
	$(CC) index_lib_test.o index_lib.o string_list.o string_set.o -o index_lib_test

string_set_test.o: string_set_test.c string_set.h
	$(CC) $(CFLAGS) -c string_set_test.c

string_list_test.o: string_list_test.c string_list.h
	$(CC) $(CFLAGS) -c string_list_test.c

string_set.o: string_set.c string_set.h string_list.h
	$(CC) $(CFLAGS) -c string_set.c

string_list.o: string_list.c string_list.h
	$(CC) $(CFLAGS) -c string_list.c

index_lib_test.o: index_lib_test.c index_lib.h
	$(CC) $(CFLAGS) -c index_lib_test.c

index_lib.o: index_lib.c index_lib.h
	$(CC) $(CFLAGS) -c index_lib.c

main.o: main.c index_lib.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o searchengine index_lib_test string_set_test string_list_test

format:
	clang-format -i -style=file *.[ch]

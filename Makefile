all:
	@echo "This does nothing for now"
proc: multitest_proc.o
	@gcc -o searchtest searchtest.c multitest_proc.o -lm
multitest_proc.o: multitest_proc.c
	@gcc -o multitest_proc.o -c multitest_proc.c
thread: multitest_thread.o
	@gcc -o searchtest searchtest.c multitest_thread.o -lpthread -lm
sequential: multitest_sequential.o
	@gcc -o searchtest searchtest.c multitest_sequential.o -lm
multitest_sequential.o: multitest_sequential.c
	@gcc -o multitest_sequential.o -c multitest_sequential.c
multitest_thread.o: multitest_thread.c
	@gcc -o multitest_thread.o -c multitest_thread.c
clean:
	@rm *.o ./searchtest

CC:=gcc

create_test: create_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
terminate_test: terminate_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
pthread_detach_test: pthread_detach_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
pthread_cancel_deferred_test: pthread_cancel_deferred_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

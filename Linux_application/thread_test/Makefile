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
pthread_cancel_async_test: pthread_cancel_async_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
pthread_cancel_disabled_test: pthread_cancel_disabled_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
mutex_test: mutex_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
rwlock_test_writer_unlock: rwlock_test_writer_unlock.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
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
rwlock_hungry_solved: rwlock_hungry_solved.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
restrict_test: restrict_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
condition_var: condition_var.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
unnamed_sem_bin_thread_condition: unnamed_sem_bin_thread_condition.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
unnamed_sem_bin_thread: unnamed_sem_bin_thread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
unnamed_sem_bin_process_condition: unnamed_sem_bin_process_condition.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
unnamed_sem_bin_process: unnamed_sem_bin_process.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
unnamed_sem_bin_process_illegal: unnamed_sem_bin_process_illegal.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
unnamed_sem_bin_process_isolate: unnamed_sem_bin_process_isolate.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
named_sem_bin:named_sem_bin.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
thread_pool_test:thread_pool_test.c
	-$(CC) -o $@ $^ pkg-config --cflags --libs glib-2.0
	-./$@
	-rm ./$@
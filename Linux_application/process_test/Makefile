CC:=gcc

system_test: system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
fork_test: fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
fork_fd_test: fork_fd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

erlou: erlou.c
	-$(CC) -o $@ $^   # -o 指定输出文件名 这一步是编译，生成可执行文件

execve_test: execve_test.c erlou
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@ ./$(word 2,$^)

fork_execve_test: fork_execve_test.c erlou
	-$(CC) -o $@ $(word 1,$^)
	-./$@
	-rm ./$@ ./$(word 2,$^)
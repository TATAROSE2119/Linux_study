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
waitpid_test: waitpid_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
pstree_test: pstree_test.c erlou
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@ ./$(word 2,$^)

erlou_block:erlou_block.c
	-$(CC) -o $@ $^

orphan_process_test: orphan_process_test.c erlou_block
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@ ./$(word 2,$^)
perror_test: perror_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

errno_test: errno_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
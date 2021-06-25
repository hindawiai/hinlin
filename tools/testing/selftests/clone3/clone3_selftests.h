<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _CLONE3_SELFTESTS_H
#घोषणा _CLONE3_SELFTESTS_H

#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <मानक_निवेशt.h>
#समावेश <syscall.h>
#समावेश <sys/रुको.h>

#समावेश "../kselftest.h"

#घोषणा ptr_to_u64(ptr) ((__u64)((uपूर्णांकptr_t)(ptr)))

#अगर_अघोषित CLONE_INTO_CGROUP
#घोषणा CLONE_INTO_CGROUP 0x200000000ULL /* Clone पूर्णांकo a specअगरic cgroup given the right permissions. */
#पूर्ण_अगर

#अगर_अघोषित __NR_clone3
#घोषणा __NR_clone3 -1
#पूर्ण_अगर

काष्ठा __clone_args अणु
	__aligned_u64 flags;
	__aligned_u64 pidfd;
	__aligned_u64 child_tid;
	__aligned_u64 parent_tid;
	__aligned_u64 निकास_संकेत;
	__aligned_u64 stack;
	__aligned_u64 stack_size;
	__aligned_u64 tls;
#अगर_अघोषित CLONE_ARGS_SIZE_VER0
#घोषणा CLONE_ARGS_SIZE_VER0 64	/* माप first published काष्ठा */
#पूर्ण_अगर
	__aligned_u64 set_tid;
	__aligned_u64 set_tid_size;
#अगर_अघोषित CLONE_ARGS_SIZE_VER1
#घोषणा CLONE_ARGS_SIZE_VER1 80	/* माप second published काष्ठा */
#पूर्ण_अगर
	__aligned_u64 cgroup;
#अगर_अघोषित CLONE_ARGS_SIZE_VER2
#घोषणा CLONE_ARGS_SIZE_VER2 88	/* माप third published काष्ठा */
#पूर्ण_अगर
पूर्ण;

अटल pid_t sys_clone3(काष्ठा __clone_args *args, माप_प्रकार size)
अणु
	ख_साफ(मानक_निकास);
	ख_साफ(मानक_त्रुटि);
	वापस syscall(__NR_clone3, args, size);
पूर्ण

अटल अंतरभूत व्योम test_clone3_supported(व्योम)
अणु
	pid_t pid;
	काष्ठा __clone_args args = अणुपूर्ण;

	अगर (__NR_clone3 < 0)
		ksft_निकास_skip("clone3() syscall is not supported\n");

	/* Set to something that will always cause EINVAL. */
	args.निकास_संकेत = -1;
	pid = sys_clone3(&args, माप(args));
	अगर (!pid)
		निकास(निकास_सफल);

	अगर (pid > 0) अणु
		रुको(शून्य);
		ksft_निकास_fail_msg(
			"Managed to create child process with invalid exit_signal\n");
	पूर्ण

	अगर (त्रुटि_सं == ENOSYS)
		ksft_निकास_skip("clone3() syscall is not supported\n");

	ksft_prपूर्णांक_msg("clone3() syscall supported\n");
पूर्ण

#पूर्ण_अगर /* _CLONE3_SELFTESTS_H */

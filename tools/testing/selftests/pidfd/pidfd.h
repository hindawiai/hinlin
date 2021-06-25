<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __PIDFD_H
#घोषणा __PIDFD_H

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <sys/mount.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>

#समावेश "../kselftest.h"

#अगर_अघोषित P_PIDFD
#घोषणा P_PIDFD 3
#पूर्ण_अगर

#अगर_अघोषित CLONE_NEWTIME
#घोषणा CLONE_NEWTIME 0x00000080
#पूर्ण_अगर

#अगर_अघोषित CLONE_PIDFD
#घोषणा CLONE_PIDFD 0x00001000
#पूर्ण_अगर

#अगर_अघोषित __NR_pidfd_खोलो
#घोषणा __NR_pidfd_खोलो -1
#पूर्ण_अगर

#अगर_अघोषित __NR_pidfd_send_संकेत
#घोषणा __NR_pidfd_send_संकेत -1
#पूर्ण_अगर

#अगर_अघोषित __NR_clone3
#घोषणा __NR_clone3 -1
#पूर्ण_अगर

#अगर_अघोषित __NR_pidfd_getfd
#घोषणा __NR_pidfd_getfd -1
#पूर्ण_अगर

#अगर_अघोषित PIDFD_NONBLOCK
#घोषणा PIDFD_NONBLOCK O_NONBLOCK
#पूर्ण_अगर

/*
 * The kernel reserves 300 pids via RESERVED_PIDS in kernel/pid.c
 * That means, when it wraps around any pid < 300 will be skipped.
 * So we need to use a pid > 300 in order to test recycling.
 */
#घोषणा PID_RECYCLE 1000

/*
 * Define a few custom error codes क्रम the child process to clearly indicate
 * what is happening. This way we can tell the dअगरference between a प्रणाली
 * error, a test error, etc.
 */
#घोषणा PIDFD_PASS 0
#घोषणा PIDFD_FAIL 1
#घोषणा PIDFD_ERROR 2
#घोषणा PIDFD_SKIP 3
#घोषणा PIDFD_XFAIL 4

पूर्णांक रुको_क्रम_pid(pid_t pid)
अणु
	पूर्णांक status, ret;

again:
	ret = रुकोpid(pid, &status, 0);
	अगर (ret == -1) अणु
		अगर (त्रुटि_सं == EINTR)
			जाओ again;

		वापस -1;
	पूर्ण

	अगर (!WIFEXITED(status))
		वापस -1;

	वापस WEXITSTATUS(status);
पूर्ण

अटल अंतरभूत पूर्णांक sys_pidfd_खोलो(pid_t pid, अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_pidfd_खोलो, pid, flags);
पूर्ण

अटल अंतरभूत पूर्णांक sys_pidfd_send_संकेत(पूर्णांक pidfd, पूर्णांक sig, siginfo_t *info,
					अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_pidfd_send_संकेत, pidfd, sig, info, flags);
पूर्ण

अटल अंतरभूत पूर्णांक sys_pidfd_getfd(पूर्णांक pidfd, पूर्णांक fd, पूर्णांक flags)
अणु
	वापस syscall(__NR_pidfd_getfd, pidfd, fd, flags);
पूर्ण

अटल अंतरभूत पूर्णांक sys_memfd_create(स्थिर अक्षर *name, अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_memfd_create, name, flags);
पूर्ण

#पूर्ण_अगर /* __PIDFD_H */

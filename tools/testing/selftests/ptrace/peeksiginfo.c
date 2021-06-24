<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/syscall.h>
#समावेश <sys/user.h>
#समावेश <sys/mman.h>

#समावेश "linux/ptrace.h"

अटल पूर्णांक sys_rt_sigqueueinfo(pid_t tgid, पूर्णांक sig, siginfo_t *uinfo)
अणु
	वापस syscall(SYS_rt_sigqueueinfo, tgid, sig, uinfo);
पूर्ण

अटल पूर्णांक sys_rt_tgsigqueueinfo(pid_t tgid, pid_t tid,
					पूर्णांक sig, siginfo_t *uinfo)
अणु
	वापस syscall(SYS_rt_tgsigqueueinfo, tgid, tid, sig, uinfo);
पूर्ण

अटल पूर्णांक sys_ptrace(पूर्णांक request, pid_t pid, व्योम *addr, व्योम *data)
अणु
	वापस syscall(SYS_ptrace, request, pid, addr, data);
पूर्ण

#घोषणा SIGNR 10
#घोषणा TEST_SICODE_PRIV	-1
#घोषणा TEST_SICODE_SHARE	-2

#अगर_अघोषित PAGE_SIZE
#घोषणा PAGE_SIZE sysconf(_SC_PAGESIZE)
#पूर्ण_अगर

#घोषणा err(fmt, ...)						\
		ख_लिखो(मानक_त्रुटि,					\
			"Error (%s:%d): " fmt,			\
			__खाता__, __LINE__, ##__VA_ARGS__)

अटल पूर्णांक check_error_paths(pid_t child)
अणु
	काष्ठा ptrace_peeksiginfo_args arg;
	पूर्णांक ret, निकास_code = -1;
	व्योम *addr_rw, *addr_ro;

	/*
	 * Allocate two contiguous pages. The first one is क्रम पढ़ो-ग_लिखो,
	 * another is क्रम पढ़ो-only.
	 */
	addr_rw = mmap(शून्य, 2 * PAGE_SIZE, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	अगर (addr_rw == MAP_FAILED) अणु
		err("mmap() failed: %m\n");
		वापस 1;
	पूर्ण

	addr_ro = mmap(addr_rw + PAGE_SIZE, PAGE_SIZE, PROT_READ,
			MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
	अगर (addr_ro == MAP_FAILED) अणु
		err("mmap() failed: %m\n");
		जाओ out;
	पूर्ण

	arg.nr = SIGNR;
	arg.off = 0;

	/* Unsupported flags */
	arg.flags = ~0;
	ret = sys_ptrace(PTRACE_PEEKSIGINFO, child, &arg, addr_rw);
	अगर (ret != -1 || त्रुटि_सं != EINVAL) अणु
		err("sys_ptrace() returns %d (expected -1),"
				" errno %d (expected %d): %m\n",
				ret, त्रुटि_सं, EINVAL);
		जाओ out;
	पूर्ण
	arg.flags = 0;

	/* A part of the buffer is पढ़ो-only */
	ret = sys_ptrace(PTRACE_PEEKSIGINFO, child, &arg,
					addr_ro - माप(siginfo_t) * 2);
	अगर (ret != 2) अणु
		err("sys_ptrace() returns %d (expected 2): %m\n", ret);
		जाओ out;
	पूर्ण

	/* Read-only buffer */
	ret = sys_ptrace(PTRACE_PEEKSIGINFO, child, &arg, addr_ro);
	अगर (ret != -1 && त्रुटि_सं != EFAULT) अणु
		err("sys_ptrace() returns %d (expected -1),"
				" errno %d (expected %d): %m\n",
				ret, त्रुटि_सं, EFAULT);
		जाओ out;
	पूर्ण

	निकास_code = 0;
out:
	munmap(addr_rw, 2 * PAGE_SIZE);
	वापस निकास_code;
पूर्ण

पूर्णांक check_direct_path(pid_t child, पूर्णांक shared, पूर्णांक nr)
अणु
	काष्ठा ptrace_peeksiginfo_args arg = अणु.flags = 0, .nr = nr, .off = 0पूर्ण;
	पूर्णांक i, j, ret, निकास_code = -1;
	siginfo_t siginfo[SIGNR];
	पूर्णांक si_code;

	अगर (shared == 1) अणु
		arg.flags = PTRACE_PEEKSIGINFO_SHARED;
		si_code = TEST_SICODE_SHARE;
	पूर्ण अन्यथा अणु
		arg.flags = 0;
		si_code = TEST_SICODE_PRIV;
	पूर्ण

	क्रम (i = 0; i < SIGNR; ) अणु
		arg.off = i;
		ret = sys_ptrace(PTRACE_PEEKSIGINFO, child, &arg, siginfo);
		अगर (ret == -1) अणु
			err("ptrace() failed: %m\n");
			जाओ out;
		पूर्ण

		अगर (ret == 0)
			अवरोध;

		क्रम (j = 0; j < ret; j++, i++) अणु
			अगर (siginfo[j].si_code == si_code &&
			    siginfo[j].si_पूर्णांक == i)
				जारी;

			err("%d: Wrong siginfo i=%d si_code=%d si_int=%d\n",
			     shared, i, siginfo[j].si_code, siginfo[j].si_पूर्णांक);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (i != SIGNR) अणु
		err("Only %d signals were read\n", i);
		जाओ out;
	पूर्ण

	निकास_code = 0;
out:
	वापस निकास_code;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	siginfo_t siginfo[SIGNR];
	पूर्णांक i, निकास_code = 1;
	sigset_t blockmask;
	pid_t child;

	sigemptyset(&blockmask);
	sigaddset(&blockmask, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &blockmask, शून्य);

	child = विभाजन();
	अगर (child == -1) अणु
		err("fork() failed: %m");
		वापस 1;
	पूर्ण अन्यथा अगर (child == 0) अणु
		pid_t ppid = getppid();
		जबतक (1) अणु
			अगर (ppid != getppid())
				अवरोध;
			sleep(1);
		पूर्ण
		वापस 1;
	पूर्ण

	/* Send संकेतs in process-wide and per-thपढ़ो queues */
	क्रम (i = 0; i < SIGNR; i++) अणु
		siginfo->si_code = TEST_SICODE_SHARE;
		siginfo->si_पूर्णांक = i;
		sys_rt_sigqueueinfo(child, SIGRTMIN, siginfo);

		siginfo->si_code = TEST_SICODE_PRIV;
		siginfo->si_पूर्णांक = i;
		sys_rt_tgsigqueueinfo(child, child, SIGRTMIN, siginfo);
	पूर्ण

	अगर (sys_ptrace(PTRACE_ATTACH, child, शून्य, शून्य) == -1)
		वापस 1;

	रुकोpid(child, शून्य, 0);

	/* Dump संकेतs one by one*/
	अगर (check_direct_path(child, 0, 1))
		जाओ out;
	/* Dump all संकेतs क्रम one call */
	अगर (check_direct_path(child, 0, SIGNR))
		जाओ out;

	/*
	 * Dump संकेत from the process-wide queue.
	 * The number of संकेतs is not multible to the buffer size
	 */
	अगर (check_direct_path(child, 1, 3))
		जाओ out;

	अगर (check_error_paths(child))
		जाओ out;

	म_लिखो("PASS\n");
	निकास_code = 0;
out:
	अगर (sys_ptrace(PTRACE_KILL, child, शून्य, शून्य) == -1)
		वापस 1;

	रुकोpid(child, शून्य, 0);

	वापस निकास_code;
पूर्ण

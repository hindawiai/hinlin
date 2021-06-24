<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
 *
 * Test code क्रम seccomp bpf.
 */

#घोषणा _GNU_SOURCE
#समावेश <sys/types.h>

/*
 * glibc 2.26 and later have SIGSYS in siginfo_t. Beक्रमe that,
 * we need to use the kernel's siginfo.h file and trick glibc
 * पूर्णांकo accepting it.
 */
#अगर !__GLIBC_PREREQ(2, 26)
# include <यंत्र/siginfo.h>
# define __have_siginfo_t 1
# define __have_sigval_t 1
# define __have_sigevent_t 1
#पूर्ण_अगर

#समावेश <त्रुटिसं.स>
#समावेश <linux/filter.h>
#समावेश <sys/prctl.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/user.h>
#समावेश <linux/prctl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/seccomp.h>
#समावेश <pthपढ़ो.h>
#समावेश <semaphore.h>
#समावेश <संकेत.स>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <सीमा.स>
#समावेश <linux/elf.h>
#समावेश <sys/uपन.स>
#समावेश <sys/utsname.h>
#समावेश <sys/fcntl.h>
#समावेश <sys/mman.h>
#समावेश <sys/बार.h>
#समावेश <sys/socket.h>
#समावेश <sys/ioctl.h>
#समावेश <linux/kcmp.h>
#समावेश <sys/resource.h>

#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <poll.h>

#समावेश "../kselftest_harness.h"
#समावेश "../clone3/clone3_selftests.h"

/* Attempt to de-conflict with the selftests tree. */
#अगर_अघोषित SKIP
#घोषणा SKIP(s, ...)	XFAIL(s, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर_अघोषित PR_SET_PTRACER
# define PR_SET_PTRACER 0x59616d61
#पूर्ण_अगर

#अगर_अघोषित PR_SET_NO_NEW_PRIVS
#घोषणा PR_SET_NO_NEW_PRIVS 38
#घोषणा PR_GET_NO_NEW_PRIVS 39
#पूर्ण_अगर

#अगर_अघोषित PR_SECCOMP_EXT
#घोषणा PR_SECCOMP_EXT 43
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_EXT_ACT
#घोषणा SECCOMP_EXT_ACT 1
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_EXT_ACT_TSYNC
#घोषणा SECCOMP_EXT_ACT_TSYNC 1
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_MODE_STRICT
#घोषणा SECCOMP_MODE_STRICT 1
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_MODE_FILTER
#घोषणा SECCOMP_MODE_FILTER 2
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_RET_ALLOW
काष्ठा seccomp_data अणु
	पूर्णांक nr;
	__u32 arch;
	__u64 inकाष्ठाion_poपूर्णांकer;
	__u64 args[6];
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_RET_KILL_PROCESS
#घोषणा SECCOMP_RET_KILL_PROCESS 0x80000000U /* समाप्त the process */
#घोषणा SECCOMP_RET_KILL_THREAD	 0x00000000U /* समाप्त the thपढ़ो */
#पूर्ण_अगर
#अगर_अघोषित SECCOMP_RET_KILL
#घोषणा SECCOMP_RET_KILL	 SECCOMP_RET_KILL_THREAD
#घोषणा SECCOMP_RET_TRAP	 0x00030000U /* disallow and क्रमce a SIGSYS */
#घोषणा SECCOMP_RET_ERRNO	 0x00050000U /* वापसs an त्रुटि_सं */
#घोषणा SECCOMP_RET_TRACE	 0x7ff00000U /* pass to a tracer or disallow */
#घोषणा SECCOMP_RET_ALLOW	 0x7fff0000U /* allow */
#पूर्ण_अगर
#अगर_अघोषित SECCOMP_RET_LOG
#घोषणा SECCOMP_RET_LOG		 0x7ffc0000U /* allow after logging */
#पूर्ण_अगर

#अगर_अघोषित __NR_seccomp
# अगर defined(__i386__)
#  define __NR_seccomp 354
# elअगर defined(__x86_64__)
#  define __NR_seccomp 317
# elअगर defined(__arm__)
#  define __NR_seccomp 383
# elअगर defined(__aarch64__)
#  define __NR_seccomp 277
# elअगर defined(__riscv)
#  define __NR_seccomp 277
# elअगर defined(__csky__)
#  define __NR_seccomp 277
# elअगर defined(__hppa__)
#  define __NR_seccomp 338
# elअगर defined(__घातerpc__)
#  define __NR_seccomp 358
# elअगर defined(__s390__)
#  define __NR_seccomp 348
# elअगर defined(__xtensa__)
#  define __NR_seccomp 337
# elअगर defined(__sh__)
#  define __NR_seccomp 372
# अन्यथा
#  warning "seccomp syscall number unknown for this architecture"
#  define __NR_seccomp 0xffff
# endअगर
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_SET_MODE_STRICT
#घोषणा SECCOMP_SET_MODE_STRICT 0
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_SET_MODE_FILTER
#घोषणा SECCOMP_SET_MODE_FILTER 1
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_GET_ACTION_AVAIL
#घोषणा SECCOMP_GET_ACTION_AVAIL 2
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_GET_NOTIF_SIZES
#घोषणा SECCOMP_GET_NOTIF_SIZES 3
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_FILTER_FLAG_TSYNC
#घोषणा SECCOMP_FILTER_FLAG_TSYNC (1UL << 0)
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_FILTER_FLAG_LOG
#घोषणा SECCOMP_FILTER_FLAG_LOG (1UL << 1)
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_FILTER_FLAG_SPEC_ALLOW
#घोषणा SECCOMP_FILTER_FLAG_SPEC_ALLOW (1UL << 2)
#पूर्ण_अगर

#अगर_अघोषित PTRACE_SECCOMP_GET_METADATA
#घोषणा PTRACE_SECCOMP_GET_METADATA	0x420d

काष्ठा seccomp_metadata अणु
	__u64 filter_off;       /* Input: which filter */
	__u64 flags;             /* Output: filter's flags */
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_FILTER_FLAG_NEW_LISTENER
#घोषणा SECCOMP_FILTER_FLAG_NEW_LISTENER	(1UL << 3)
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_RET_USER_NOTIF
#घोषणा SECCOMP_RET_USER_NOTIF 0x7fc00000U

#घोषणा SECCOMP_IOC_MAGIC		'!'
#घोषणा SECCOMP_IO(nr)			_IO(SECCOMP_IOC_MAGIC, nr)
#घोषणा SECCOMP_IOR(nr, type)		_IOR(SECCOMP_IOC_MAGIC, nr, type)
#घोषणा SECCOMP_IOW(nr, type)		_IOW(SECCOMP_IOC_MAGIC, nr, type)
#घोषणा SECCOMP_IOWR(nr, type)		_IOWR(SECCOMP_IOC_MAGIC, nr, type)

/* Flags क्रम seccomp notअगरication fd ioctl. */
#घोषणा SECCOMP_IOCTL_NOTIF_RECV	SECCOMP_IOWR(0, काष्ठा seccomp_notअगर)
#घोषणा SECCOMP_IOCTL_NOTIF_SEND	SECCOMP_IOWR(1,	\
						काष्ठा seccomp_notअगर_resp)
#घोषणा SECCOMP_IOCTL_NOTIF_ID_VALID	SECCOMP_IOW(2, __u64)

काष्ठा seccomp_notअगर अणु
	__u64 id;
	__u32 pid;
	__u32 flags;
	काष्ठा seccomp_data data;
पूर्ण;

काष्ठा seccomp_notअगर_resp अणु
	__u64 id;
	__s64 val;
	__s32 error;
	__u32 flags;
पूर्ण;

काष्ठा seccomp_notअगर_sizes अणु
	__u16 seccomp_notअगर;
	__u16 seccomp_notअगर_resp;
	__u16 seccomp_data;
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_IOCTL_NOTIF_ADDFD
/* On success, the वापस value is the remote process's added fd number */
#घोषणा SECCOMP_IOCTL_NOTIF_ADDFD	SECCOMP_IOW(3,	\
						काष्ठा seccomp_notअगर_addfd)

/* valid flags क्रम seccomp_notअगर_addfd */
#घोषणा SECCOMP_ADDFD_FLAG_SETFD	(1UL << 0) /* Specअगरy remote fd */

काष्ठा seccomp_notअगर_addfd अणु
	__u64 id;
	__u32 flags;
	__u32 srcfd;
	__u32 newfd;
	__u32 newfd_flags;
पूर्ण;
#पूर्ण_अगर

काष्ठा seccomp_notअगर_addfd_small अणु
	__u64 id;
	अक्षर weird[4];
पूर्ण;
#घोषणा SECCOMP_IOCTL_NOTIF_ADDFD_SMALL	\
	SECCOMP_IOW(3, काष्ठा seccomp_notअगर_addfd_small)

काष्ठा seccomp_notअगर_addfd_big अणु
	जोड़ अणु
		काष्ठा seccomp_notअगर_addfd addfd;
		अक्षर buf[माप(काष्ठा seccomp_notअगर_addfd) + 8];
	पूर्ण;
पूर्ण;
#घोषणा SECCOMP_IOCTL_NOTIF_ADDFD_BIG	\
	SECCOMP_IOWR(3, काष्ठा seccomp_notअगर_addfd_big)

#अगर_अघोषित PTRACE_EVENTMSG_SYSCALL_ENTRY
#घोषणा PTRACE_EVENTMSG_SYSCALL_ENTRY	1
#घोषणा PTRACE_EVENTMSG_SYSCALL_EXIT	2
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_USER_NOTIF_FLAG_CONTINUE
#घोषणा SECCOMP_USER_NOTIF_FLAG_CONTINUE 0x00000001
#पूर्ण_अगर

#अगर_अघोषित SECCOMP_FILTER_FLAG_TSYNC_ESRCH
#घोषणा SECCOMP_FILTER_FLAG_TSYNC_ESRCH (1UL << 4)
#पूर्ण_अगर

#अगर_अघोषित seccomp
पूर्णांक seccomp(अचिन्हित पूर्णांक op, अचिन्हित पूर्णांक flags, व्योम *args)
अणु
	त्रुटि_सं = 0;
	वापस syscall(__NR_seccomp, op, flags, args);
पूर्ण
#पूर्ण_अगर

#अगर __BYTE_ORDER == __LITTLE_ENDIAN
#घोषणा syscall_arg(_n) (दुरत्व(काष्ठा seccomp_data, args[_n]))
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा syscall_arg(_n) (दुरत्व(काष्ठा seccomp_data, args[_n]) + माप(__u32))
#अन्यथा
#त्रुटि "wut? Unknown __BYTE_ORDER?!"
#पूर्ण_अगर

#घोषणा SIBLING_EXIT_UNKILLED	0xbadbeef
#घोषणा SIBLING_निकास_त्रुटि	0xbadface
#घोषणा SIBLING_EXIT_NEWPRIVS	0xbadfeed

अटल पूर्णांक __filecmp(pid_t pid1, pid_t pid2, पूर्णांक fd1, पूर्णांक fd2)
अणु
#अगर_घोषित __NR_kcmp
	त्रुटि_सं = 0;
	वापस syscall(__NR_kcmp, pid1, pid2, KCMP_खाता, fd1, fd2);
#अन्यथा
	त्रुटि_सं = ENOSYS;
	वापस -1;
#पूर्ण_अगर
पूर्ण

/* Have TH_LOG report actual location filecmp() is used. */
#घोषणा filecmp(pid1, pid2, fd1, fd2)	(अणु		\
	पूर्णांक _ret;					\
							\
	_ret = __filecmp(pid1, pid2, fd1, fd2);		\
	अगर (_ret != 0) अणु				\
		अगर (_ret < 0 && त्रुटि_सं == ENOSYS) अणु	\
			TH_LOG("kcmp() syscall missing (test is less accurate)");\
			_ret = 0;			\
		पूर्ण					\
	पूर्ण						\
	_ret; पूर्ण)

TEST(kcmp)
अणु
	पूर्णांक ret;

	ret = __filecmp(getpid(), getpid(), 1, 1);
	EXPECT_EQ(ret, 0);
	अगर (ret != 0 && त्रुटि_सं == ENOSYS)
		SKIP(वापस, "Kernel does not support kcmp() (missing CONFIG_KCMP?)");
पूर्ण

TEST(mode_strict_support)
अणु
	दीर्घ ret;

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT, शून्य, शून्य, शून्य);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support CONFIG_SECCOMP");
	पूर्ण
	syscall(__NR_निकास, 0);
पूर्ण

TEST_SIGNAL(mode_strict_cannot_call_prctl, SIGKILL)
अणु
	दीर्घ ret;

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT, शून्य, शून्य, शून्य);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support CONFIG_SECCOMP");
	पूर्ण
	syscall(__NR_prctl, PR_SET_SECCOMP, SECCOMP_MODE_FILTER,
		शून्य, शून्य, शून्य);
	EXPECT_FALSE(true) अणु
		TH_LOG("Unreachable!");
	पूर्ण
पूर्ण

/* Note! This करोesn't test no new privs behavior */
TEST(no_new_privs_support)
अणु
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	EXPECT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण
पूर्ण

/* Tests kernel support by checking क्रम a copy_from_user() fault on शून्य. */
TEST(mode_filter_support)
अणु
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, शून्य, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, शून्य, शून्य, शून्य);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(EFAULT, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support CONFIG_SECCOMP_FILTER!");
	पूर्ण
पूर्ण

TEST(mode_filter_without_nnp)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_GET_NO_NEW_PRIVS, 0, शून्य, 0, 0);
	ASSERT_LE(0, ret) अणु
		TH_LOG("Expected 0 or unsupported for NO_NEW_PRIVS");
	पूर्ण
	त्रुटि_सं = 0;
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	/* Succeeds with CAP_SYS_ADMIN, fails without */
	/* TODO(wad) check caps not euid */
	अगर (geteuid()) अणु
		EXPECT_EQ(-1, ret);
		EXPECT_EQ(EACCES, त्रुटि_सं);
	पूर्ण अन्यथा अणु
		EXPECT_EQ(0, ret);
	पूर्ण
पूर्ण

#घोषणा MAX_INSNS_PER_PATH 32768

TEST(filter_size_limits)
अणु
	पूर्णांक i;
	पूर्णांक count = BPF_MAXINSNS + 1;
	काष्ठा sock_filter allow[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_filter *filter;
	काष्ठा sock_fprog prog = अणु पूर्ण;
	दीर्घ ret;

	filter = सुस्मृति(count, माप(*filter));
	ASSERT_NE(शून्य, filter);

	क्रम (i = 0; i < count; i++)
		filter[i] = allow[0];

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	prog.filter = filter;
	prog.len = count;

	/* Too many filter inकाष्ठाions in a single filter. */
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	ASSERT_NE(0, ret) अणु
		TH_LOG("Installing %d insn filter was allowed", prog.len);
	पूर्ण

	/* One less is okay, though. */
	prog.len -= 1;
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Installing %d insn filter wasn't allowed", prog.len);
	पूर्ण
पूर्ण

TEST(filter_chain_limits)
अणु
	पूर्णांक i;
	पूर्णांक count = BPF_MAXINSNS;
	काष्ठा sock_filter allow[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_filter *filter;
	काष्ठा sock_fprog prog = अणु पूर्ण;
	दीर्घ ret;

	filter = सुस्मृति(count, माप(*filter));
	ASSERT_NE(शून्य, filter);

	क्रम (i = 0; i < count; i++)
		filter[i] = allow[0];

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	prog.filter = filter;
	prog.len = 1;

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	ASSERT_EQ(0, ret);

	prog.len = count;

	/* Too many total filter inकाष्ठाions. */
	क्रम (i = 0; i < MAX_INSNS_PER_PATH; i++) अणु
		ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
		अगर (ret != 0)
			अवरोध;
	पूर्ण
	ASSERT_NE(0, ret) अणु
		TH_LOG("Allowed %d %d-insn filters (total with penalties:%d)",
		       i, count, i * (count + 4));
	पूर्ण
पूर्ण

TEST(mode_filter_cannot_move_to_strict)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT, शून्य, 0, 0);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(EINVAL, त्रुटि_सं);
पूर्ण


TEST(mode_filter_get_seccomp)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_GET_SECCOMP, 0, 0, 0, 0);
	EXPECT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_GET_SECCOMP, 0, 0, 0, 0);
	EXPECT_EQ(2, ret);
पूर्ण


TEST(ALLOW_all)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	ASSERT_EQ(0, ret);
पूर्ण

TEST(empty_prog)
अणु
	काष्ठा sock_filter filter[] = अणु
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(EINVAL, त्रुटि_सं);
पूर्ण

TEST(log_all)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_LOG),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;
	pid_t parent = getppid();

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	ASSERT_EQ(0, ret);

	/* getppid() should succeed and be logged (no check क्रम logging) */
	EXPECT_EQ(parent, syscall(__NR_getppid));
पूर्ण

TEST_SIGNAL(unknown_ret_is_समाप्त_inside, SIGSYS)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, 0x10000000U),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	ASSERT_EQ(0, ret);
	EXPECT_EQ(0, syscall(__NR_getpid)) अणु
		TH_LOG("getpid() shouldn't ever return");
	पूर्ण
पूर्ण

/* वापस code >= 0x80000000 is unused. */
TEST_SIGNAL(unknown_ret_is_समाप्त_above_allow, SIGSYS)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, 0x90000000U),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	ASSERT_EQ(0, ret);
	EXPECT_EQ(0, syscall(__NR_getpid)) अणु
		TH_LOG("getpid() shouldn't ever return");
	पूर्ण
पूर्ण

TEST_SIGNAL(KILL_all, SIGSYS)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	ASSERT_EQ(0, ret);
पूर्ण

TEST_SIGNAL(KILL_one, SIGSYS)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;
	pid_t parent = getppid();

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	ASSERT_EQ(0, ret);

	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* getpid() should never वापस. */
	EXPECT_EQ(0, syscall(__NR_getpid));
पूर्ण

TEST_SIGNAL(KILL_one_arg_one, SIGSYS)
अणु
	व्योम *fatal_address;
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_बार, 1, 0),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		/* Only both with lower 32-bit क्रम now. */
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS, syscall_arg(0)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K,
			(अचिन्हित दीर्घ)&fatal_address, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;
	pid_t parent = getppid();
	काष्ठा पंचांगs समयbuf;
	घड़ी_प्रकार घड़ी = बार(&समयbuf);

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	ASSERT_EQ(0, ret);

	EXPECT_EQ(parent, syscall(__NR_getppid));
	EXPECT_LE(घड़ी, syscall(__NR_बार, &समयbuf));
	/* बार() should never वापस. */
	EXPECT_EQ(0, syscall(__NR_बार, &fatal_address));
पूर्ण

TEST_SIGNAL(KILL_one_arg_six, SIGSYS)
अणु
#अगर_अघोषित __NR_mmap2
	पूर्णांक sysno = __NR_mmap;
#अन्यथा
	पूर्णांक sysno = __NR_mmap2;
#पूर्ण_अगर
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, sysno, 1, 0),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		/* Only both with lower 32-bit क्रम now. */
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS, syscall_arg(5)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, 0x0C0FFEE, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;
	pid_t parent = getppid();
	पूर्णांक fd;
	व्योम *map1, *map2;
	पूर्णांक page_size = sysconf(_SC_PAGESIZE);

	ASSERT_LT(0, page_size);

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	ASSERT_EQ(0, ret);

	fd = खोलो("/dev/zero", O_RDONLY);
	ASSERT_NE(-1, fd);

	EXPECT_EQ(parent, syscall(__NR_getppid));
	map1 = (व्योम *)syscall(sysno,
		शून्य, page_size, PROT_READ, MAP_PRIVATE, fd, page_size);
	EXPECT_NE(MAP_FAILED, map1);
	/* mmap2() should never वापस. */
	map2 = (व्योम *)syscall(sysno,
		 शून्य, page_size, PROT_READ, MAP_PRIVATE, fd, 0x0C0FFEE);
	EXPECT_EQ(MAP_FAILED, map2);

	/* The test failed, so clean up the resources. */
	munmap(map1, page_size);
	munmap(map2, page_size);
	बंद(fd);
पूर्ण

/* This is a thपढ़ो task to die via seccomp filter violation. */
व्योम *समाप्त_thपढ़ो(व्योम *data)
अणु
	bool die = (bool)data;

	अगर (die) अणु
		prctl(PR_GET_SECCOMP, 0, 0, 0, 0);
		वापस (व्योम *)SIBLING_निकास_त्रुटि;
	पूर्ण

	वापस (व्योम *)SIBLING_EXIT_UNKILLED;
पूर्ण

क्रमागत समाप्त_t अणु
	KILL_THREAD,
	KILL_PROCESS,
	RET_UNKNOWN
पूर्ण;

/* Prepare a thपढ़ो that will समाप्त itself or both of us. */
व्योम समाप्त_thपढ़ो_or_group(काष्ठा __test_metadata *_metadata,
			  क्रमागत समाप्त_t समाप्त_how)
अणु
	pthपढ़ो_t thपढ़ो;
	व्योम *status;
	/* Kill only when calling __NR_prctl. */
	काष्ठा sock_filter filter_thपढ़ो[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_prctl, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL_THREAD),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog_thपढ़ो = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter_thपढ़ो),
		.filter = filter_thपढ़ो,
	पूर्ण;
	पूर्णांक समाप्त = समाप्त_how == KILL_PROCESS ? SECCOMP_RET_KILL_PROCESS : 0xAAAAAAAAA;
	काष्ठा sock_filter filter_process[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_prctl, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, समाप्त),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog_process = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter_process),
		.filter = filter_process,
	पूर्ण;

	ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	ASSERT_EQ(0, seccomp(SECCOMP_SET_MODE_FILTER, 0,
			     समाप्त_how == KILL_THREAD ? &prog_thपढ़ो
						     : &prog_process));

	/*
	 * Add the KILL_THREAD rule again to make sure that the KILL_PROCESS
	 * flag cannot be करोwngraded by a new filter.
	 */
	अगर (समाप्त_how == KILL_PROCESS)
		ASSERT_EQ(0, seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog_thपढ़ो));

	/* Start a thपढ़ो that will निकास immediately. */
	ASSERT_EQ(0, pthपढ़ो_create(&thपढ़ो, शून्य, समाप्त_thपढ़ो, (व्योम *)false));
	ASSERT_EQ(0, pthपढ़ो_join(thपढ़ो, &status));
	ASSERT_EQ(SIBLING_EXIT_UNKILLED, (अचिन्हित दीर्घ)status);

	/* Start a thपढ़ो that will die immediately. */
	ASSERT_EQ(0, pthपढ़ो_create(&thपढ़ो, शून्य, समाप्त_thपढ़ो, (व्योम *)true));
	ASSERT_EQ(0, pthपढ़ो_join(thपढ़ो, &status));
	ASSERT_NE(SIBLING_निकास_त्रुटि, (अचिन्हित दीर्घ)status);

	/*
	 * If we get here, only the spawned thपढ़ो died. Let the parent know
	 * the whole process didn't die (i.e. this thपढ़ो, the spawner,
	 * stayed running).
	 */
	निकास(42);
पूर्ण

TEST(KILL_thपढ़ो)
अणु
	पूर्णांक status;
	pid_t child_pid;

	child_pid = विभाजन();
	ASSERT_LE(0, child_pid);
	अगर (child_pid == 0) अणु
		समाप्त_thपढ़ो_or_group(_metadata, KILL_THREAD);
		_निकास(38);
	पूर्ण

	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));

	/* If only the thपढ़ो was समाप्तed, we'll see निकास 42. */
	ASSERT_TRUE(WIFEXITED(status));
	ASSERT_EQ(42, WEXITSTATUS(status));
पूर्ण

TEST(KILL_process)
अणु
	पूर्णांक status;
	pid_t child_pid;

	child_pid = विभाजन();
	ASSERT_LE(0, child_pid);
	अगर (child_pid == 0) अणु
		समाप्त_thपढ़ो_or_group(_metadata, KILL_PROCESS);
		_निकास(38);
	पूर्ण

	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));

	/* If the entire process was समाप्तed, we'll see SIGSYS. */
	ASSERT_TRUE(WIFSIGNALED(status));
	ASSERT_EQ(SIGSYS, WTERMSIG(status));
पूर्ण

TEST(KILL_unknown)
अणु
	पूर्णांक status;
	pid_t child_pid;

	child_pid = विभाजन();
	ASSERT_LE(0, child_pid);
	अगर (child_pid == 0) अणु
		समाप्त_thपढ़ो_or_group(_metadata, RET_UNKNOWN);
		_निकास(38);
	पूर्ण

	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));

	/* If the entire process was समाप्तed, we'll see SIGSYS. */
	EXPECT_TRUE(WIFSIGNALED(status)) अणु
		TH_LOG("Unknown SECCOMP_RET is only killing the thread?");
	पूर्ण
	ASSERT_EQ(SIGSYS, WTERMSIG(status));
पूर्ण

/* TODO(wad) add 64-bit versus 32-bit arg tests. */
TEST(arg_out_of_range)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS, syscall_arg(6)),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(EINVAL, त्रुटि_सं);
पूर्ण

#घोषणा ERRNO_FILTER(name, त्रुटि_सं)					\
	काष्ठा sock_filter _पढ़ो_filter_##name[] = अणु			\
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,				\
			दुरत्व(काष्ठा seccomp_data, nr)),		\
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_पढ़ो, 0, 1),	\
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ERRNO | त्रुटि_सं),	\
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),		\
	पूर्ण;								\
	काष्ठा sock_fprog prog_##name = अणु				\
		.len = (अचिन्हित लघु)ARRAY_SIZE(_पढ़ो_filter_##name),	\
		.filter = _पढ़ो_filter_##name,				\
	पूर्ण

/* Make sure basic त्रुटि_सं values are correctly passed through a filter. */
TEST(ERRNO_valid)
अणु
	ERRNO_FILTER(valid, E2BIG);
	दीर्घ ret;
	pid_t parent = getppid();

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog_valid);
	ASSERT_EQ(0, ret);

	EXPECT_EQ(parent, syscall(__NR_getppid));
	EXPECT_EQ(-1, पढ़ो(0, शून्य, 0));
	EXPECT_EQ(E2BIG, त्रुटि_सं);
पूर्ण

/* Make sure an त्रुटि_सं of zero is correctly handled by the arch code. */
TEST(ERRNO_zero)
अणु
	ERRNO_FILTER(zero, 0);
	दीर्घ ret;
	pid_t parent = getppid();

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog_zero);
	ASSERT_EQ(0, ret);

	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* "errno" of 0 is ok. */
	EXPECT_EQ(0, पढ़ो(0, शून्य, 0));
पूर्ण

/*
 * The SECCOMP_RET_DATA mask is 16 bits wide, but त्रुटि_सं is smaller.
 * This tests that the त्रुटि_सं value माला_लो capped correctly, fixed by
 * 580c57f10768 ("seccomp: cap SECCOMP_RET_ERRNO data to MAX_ERRNO").
 */
TEST(ERRNO_capped)
अणु
	ERRNO_FILTER(capped, 4096);
	दीर्घ ret;
	pid_t parent = getppid();

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog_capped);
	ASSERT_EQ(0, ret);

	EXPECT_EQ(parent, syscall(__NR_getppid));
	EXPECT_EQ(-1, पढ़ो(0, शून्य, 0));
	EXPECT_EQ(4095, त्रुटि_सं);
पूर्ण

/*
 * Filters are processed in reverse order: last applied is executed first.
 * Since only the SECCOMP_RET_ACTION mask is tested क्रम वापस values, the
 * SECCOMP_RET_DATA mask results will follow the most recently applied
 * matching filter वापस (and not the lowest or highest value).
 */
TEST(ERRNO_order)
अणु
	ERRNO_FILTER(first,  11);
	ERRNO_FILTER(second, 13);
	ERRNO_FILTER(third,  12);
	दीर्घ ret;
	pid_t parent = getppid();

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog_first);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog_second);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog_third);
	ASSERT_EQ(0, ret);

	EXPECT_EQ(parent, syscall(__NR_getppid));
	EXPECT_EQ(-1, पढ़ो(0, शून्य, 0));
	EXPECT_EQ(12, त्रुटि_सं);
पूर्ण

FIXTURE(TRAP) अणु
	काष्ठा sock_fprog prog;
पूर्ण;

FIXTURE_SETUP(TRAP)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRAP),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;

	स_रखो(&self->prog, 0, माप(self->prog));
	self->prog.filter = दो_स्मृति(माप(filter));
	ASSERT_NE(शून्य, self->prog.filter);
	स_नकल(self->prog.filter, filter, माप(filter));
	self->prog.len = (अचिन्हित लघु)ARRAY_SIZE(filter);
पूर्ण

FIXTURE_TEARDOWN(TRAP)
अणु
	अगर (self->prog.filter)
		मुक्त(self->prog.filter);
पूर्ण

TEST_F_SIGNAL(TRAP, dfl, SIGSYS)
अणु
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->prog);
	ASSERT_EQ(0, ret);
	syscall(__NR_getpid);
पूर्ण

/* Ensure that SIGSYS overrides संक_छोड़ो */
TEST_F_SIGNAL(TRAP, ign, SIGSYS)
अणु
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	संकेत(SIGSYS, संक_छोड़ो);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->prog);
	ASSERT_EQ(0, ret);
	syscall(__NR_getpid);
पूर्ण

अटल siginfo_t TRAP_info;
अटल अस्थिर पूर्णांक TRAP_nr;
अटल व्योम TRAP_action(पूर्णांक nr, siginfo_t *info, व्योम *व्योम_context)
अणु
	स_नकल(&TRAP_info, info, माप(TRAP_info));
	TRAP_nr = nr;
पूर्ण

TEST_F(TRAP, handler)
अणु
	पूर्णांक ret, test;
	काष्ठा sigaction act;
	sigset_t mask;

	स_रखो(&act, 0, माप(act));
	sigemptyset(&mask);
	sigaddset(&mask, SIGSYS);

	act.sa_sigaction = &TRAP_action;
	act.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGSYS, &act, शून्य);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("sigaction failed");
	पूर्ण
	ret = sigprocmask(SIG_UNBLOCK, &mask, शून्य);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("sigprocmask failed");
	पूर्ण

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->prog);
	ASSERT_EQ(0, ret);
	TRAP_nr = 0;
	स_रखो(&TRAP_info, 0, माप(TRAP_info));
	/* Expect the रेजिस्टरs to be rolled back. (nr = error) may vary
	 * based on arch. */
	ret = syscall(__NR_getpid);
	/* Silence gcc warning about अस्थिर. */
	test = TRAP_nr;
	EXPECT_EQ(SIGSYS, test);
	काष्ठा local_sigsys अणु
		व्योम *_call_addr;	/* calling user insn */
		पूर्णांक _syscall;		/* triggering प्रणाली call number */
		अचिन्हित पूर्णांक _arch;	/* AUDIT_ARCH_* of syscall */
	पूर्ण *sigsys = (काष्ठा local_sigsys *)
#अगर_घोषित si_syscall
		&(TRAP_info.si_call_addr);
#अन्यथा
		&TRAP_info.si_pid;
#पूर्ण_अगर
	EXPECT_EQ(__NR_getpid, sigsys->_syscall);
	/* Make sure arch is non-zero. */
	EXPECT_NE(0, sigsys->_arch);
	EXPECT_NE(0, (अचिन्हित दीर्घ)sigsys->_call_addr);
पूर्ण

FIXTURE(precedence) अणु
	काष्ठा sock_fprog allow;
	काष्ठा sock_fprog log;
	काष्ठा sock_fprog trace;
	काष्ठा sock_fprog error;
	काष्ठा sock_fprog trap;
	काष्ठा sock_fprog समाप्त;
पूर्ण;

FIXTURE_SETUP(precedence)
अणु
	काष्ठा sock_filter allow_insns[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_filter log_insns[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 1, 0),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_LOG),
	पूर्ण;
	काष्ठा sock_filter trace_insns[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 1, 0),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRACE),
	पूर्ण;
	काष्ठा sock_filter error_insns[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 1, 0),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ERRNO),
	पूर्ण;
	काष्ठा sock_filter trap_insns[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 1, 0),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRAP),
	पूर्ण;
	काष्ठा sock_filter समाप्त_insns[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 1, 0),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
	पूर्ण;

	स_रखो(self, 0, माप(*self));
#घोषणा FILTER_ALLOC(_x) \
	self->_x.filter = दो_स्मृति(माप(_x##_insns)); \
	ASSERT_NE(शून्य, self->_x.filter); \
	स_नकल(self->_x.filter, &_x##_insns, माप(_x##_insns)); \
	self->_x.len = (अचिन्हित लघु)ARRAY_SIZE(_x##_insns)
	FILTER_ALLOC(allow);
	FILTER_ALLOC(log);
	FILTER_ALLOC(trace);
	FILTER_ALLOC(error);
	FILTER_ALLOC(trap);
	FILTER_ALLOC(समाप्त);
पूर्ण

FIXTURE_TEARDOWN(precedence)
अणु
#घोषणा FILTER_FREE(_x) अगर (self->_x.filter) मुक्त(self->_x.filter)
	FILTER_FREE(allow);
	FILTER_FREE(log);
	FILTER_FREE(trace);
	FILTER_FREE(error);
	FILTER_FREE(trap);
	FILTER_FREE(समाप्त);
पूर्ण

TEST_F(precedence, allow_ok)
अणु
	pid_t parent, res = 0;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->error);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trap);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->समाप्त);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	res = syscall(__NR_getppid);
	EXPECT_EQ(parent, res);
पूर्ण

TEST_F_SIGNAL(precedence, समाप्त_is_highest, SIGSYS)
अणु
	pid_t parent, res = 0;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->error);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trap);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->समाप्त);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	res = syscall(__NR_getppid);
	EXPECT_EQ(parent, res);
	/* getpid() should never वापस. */
	res = syscall(__NR_getpid);
	EXPECT_EQ(0, res);
पूर्ण

TEST_F_SIGNAL(precedence, समाप्त_is_highest_in_any_order, SIGSYS)
अणु
	pid_t parent;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->समाप्त);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->error);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trap);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* getpid() should never वापस. */
	EXPECT_EQ(0, syscall(__NR_getpid));
पूर्ण

TEST_F_SIGNAL(precedence, trap_is_second, SIGSYS)
अणु
	pid_t parent;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->error);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trap);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* getpid() should never वापस. */
	EXPECT_EQ(0, syscall(__NR_getpid));
पूर्ण

TEST_F_SIGNAL(precedence, trap_is_second_in_any_order, SIGSYS)
अणु
	pid_t parent;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trap);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->error);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* getpid() should never वापस. */
	EXPECT_EQ(0, syscall(__NR_getpid));
पूर्ण

TEST_F(precedence, त्रुटि_सं_is_third)
अणु
	pid_t parent;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->error);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	EXPECT_EQ(0, syscall(__NR_getpid));
पूर्ण

TEST_F(precedence, त्रुटि_सं_is_third_in_any_order)
अणु
	pid_t parent;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->error);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	EXPECT_EQ(0, syscall(__NR_getpid));
पूर्ण

TEST_F(precedence, trace_is_fourth)
अणु
	pid_t parent;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* No ptracer */
	EXPECT_EQ(-1, syscall(__NR_getpid));
पूर्ण

TEST_F(precedence, trace_is_fourth_in_any_order)
अणु
	pid_t parent;
	दीर्घ ret;

	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->trace);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* No ptracer */
	EXPECT_EQ(-1, syscall(__NR_getpid));
पूर्ण

TEST_F(precedence, log_is_fअगरth)
अणु
	pid_t mypid, parent;
	दीर्घ ret;

	mypid = getpid();
	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* Should also work just fine */
	EXPECT_EQ(mypid, syscall(__NR_getpid));
पूर्ण

TEST_F(precedence, log_is_fअगरth_in_any_order)
अणु
	pid_t mypid, parent;
	दीर्घ ret;

	mypid = getpid();
	parent = getppid();
	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->log);
	ASSERT_EQ(0, ret);
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->allow);
	ASSERT_EQ(0, ret);
	/* Should work just fine. */
	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* Should also work just fine */
	EXPECT_EQ(mypid, syscall(__NR_getpid));
पूर्ण

#अगर_अघोषित PTRACE_O_TRACESECCOMP
#घोषणा PTRACE_O_TRACESECCOMP	0x00000080
#पूर्ण_अगर

/* Catch the Ubuntu 12.04 value error. */
#अगर PTRACE_EVENT_SECCOMP != 7
#अघोषित PTRACE_EVENT_SECCOMP
#पूर्ण_अगर

#अगर_अघोषित PTRACE_EVENT_SECCOMP
#घोषणा PTRACE_EVENT_SECCOMP 7
#पूर्ण_अगर

#घोषणा IS_SECCOMP_EVENT(status) ((status >> 16) == PTRACE_EVENT_SECCOMP)
bool tracer_running;
व्योम tracer_stop(पूर्णांक sig)
अणु
	tracer_running = false;
पूर्ण

प्रकार व्योम tracer_func_t(काष्ठा __test_metadata *_metadata,
			   pid_t tracee, पूर्णांक status, व्योम *args);

व्योम start_tracer(काष्ठा __test_metadata *_metadata, पूर्णांक fd, pid_t tracee,
	    tracer_func_t tracer_func, व्योम *args, bool ptrace_syscall)
अणु
	पूर्णांक ret = -1;
	काष्ठा sigaction action = अणु
		.sa_handler = tracer_stop,
	पूर्ण;

	/* Allow बाह्यal shutकरोwn. */
	tracer_running = true;
	ASSERT_EQ(0, sigaction(SIGUSR1, &action, शून्य));

	त्रुटि_सं = 0;
	जबतक (ret == -1 && त्रुटि_सं != EINVAL)
		ret = ptrace(PTRACE_ATTACH, tracee, शून्य, 0);
	ASSERT_EQ(0, ret) अणु
		समाप्त(tracee, SIGKILL);
	पूर्ण
	/* Wait क्रम attach stop */
	रुको(शून्य);

	ret = ptrace(PTRACE_SETOPTIONS, tracee, शून्य, ptrace_syscall ?
						      PTRACE_O_TRACESYSGOOD :
						      PTRACE_O_TRACESECCOMP);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Failed to set PTRACE_O_TRACESECCOMP");
		समाप्त(tracee, SIGKILL);
	पूर्ण
	ret = ptrace(ptrace_syscall ? PTRACE_SYSCALL : PTRACE_CONT,
		     tracee, शून्य, 0);
	ASSERT_EQ(0, ret);

	/* Unblock the tracee */
	ASSERT_EQ(1, ग_लिखो(fd, "A", 1));
	ASSERT_EQ(0, बंद(fd));

	/* Run until we're shut करोwn. Must निश्चित to stop execution. */
	जबतक (tracer_running) अणु
		पूर्णांक status;

		अगर (रुको(&status) != tracee)
			जारी;
		अगर (WIFSIGNALED(status) || WIFEXITED(status))
			/* Child is dead. Time to go. */
			वापस;

		/* Check अगर this is a seccomp event. */
		ASSERT_EQ(!ptrace_syscall, IS_SECCOMP_EVENT(status));

		tracer_func(_metadata, tracee, status, args);

		ret = ptrace(ptrace_syscall ? PTRACE_SYSCALL : PTRACE_CONT,
			     tracee, शून्य, 0);
		ASSERT_EQ(0, ret);
	पूर्ण
	/* Directly report the status of our test harness results. */
	syscall(__NR_निकास, _metadata->passed ? निकास_सफल : निकास_त्रुटि);
पूर्ण

/* Common tracer setup/tearकरोwn functions. */
व्योम cont_handler(पूर्णांक num)
अणु पूर्ण
pid_t setup_trace_fixture(काष्ठा __test_metadata *_metadata,
			  tracer_func_t func, व्योम *args, bool ptrace_syscall)
अणु
	अक्षर sync;
	पूर्णांक pipefd[2];
	pid_t tracer_pid;
	pid_t tracee = getpid();

	/* Setup a pipe क्रम clean synchronization. */
	ASSERT_EQ(0, pipe(pipefd));

	/* Fork a child which we'll promote to tracer */
	tracer_pid = विभाजन();
	ASSERT_LE(0, tracer_pid);
	संकेत(SIGALRM, cont_handler);
	अगर (tracer_pid == 0) अणु
		बंद(pipefd[0]);
		start_tracer(_metadata, pipefd[1], tracee, func, args,
			     ptrace_syscall);
		syscall(__NR_निकास, 0);
	पूर्ण
	बंद(pipefd[1]);
	prctl(PR_SET_PTRACER, tracer_pid, 0, 0, 0);
	पढ़ो(pipefd[0], &sync, 1);
	बंद(pipefd[0]);

	वापस tracer_pid;
पूर्ण

व्योम tearकरोwn_trace_fixture(काष्ठा __test_metadata *_metadata,
			    pid_t tracer)
अणु
	अगर (tracer) अणु
		पूर्णांक status;
		/*
		 * Extract the निकास code from the other process and
		 * aकरोpt it क्रम ourselves in हाल its निश्चितs failed.
		 */
		ASSERT_EQ(0, समाप्त(tracer, SIGUSR1));
		ASSERT_EQ(tracer, रुकोpid(tracer, &status, 0));
		अगर (WEXITSTATUS(status))
			_metadata->passed = 0;
	पूर्ण
पूर्ण

/* "poke" tracer arguments and function. */
काष्ठा tracer_args_poke_t अणु
	अचिन्हित दीर्घ poke_addr;
पूर्ण;

व्योम tracer_poke(काष्ठा __test_metadata *_metadata, pid_t tracee, पूर्णांक status,
		 व्योम *args)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ msg;
	काष्ठा tracer_args_poke_t *info = (काष्ठा tracer_args_poke_t *)args;

	ret = ptrace(PTRACE_GETEVENTMSG, tracee, शून्य, &msg);
	EXPECT_EQ(0, ret);
	/* If this fails, करोn't try to recover. */
	ASSERT_EQ(0x1001, msg) अणु
		समाप्त(tracee, SIGKILL);
	पूर्ण
	/*
	 * Poke in the message.
	 * Registers are not touched to try to keep this relatively arch
	 * agnostic.
	 */
	ret = ptrace(PTRACE_POKEDATA, tracee, info->poke_addr, 0x1001);
	EXPECT_EQ(0, ret);
पूर्ण

FIXTURE(TRACE_poke) अणु
	काष्ठा sock_fprog prog;
	pid_t tracer;
	दीर्घ poked;
	काष्ठा tracer_args_poke_t tracer_args;
पूर्ण;

FIXTURE_SETUP(TRACE_poke)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_पढ़ो, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRACE | 0x1001),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;

	self->poked = 0;
	स_रखो(&self->prog, 0, माप(self->prog));
	self->prog.filter = दो_स्मृति(माप(filter));
	ASSERT_NE(शून्य, self->prog.filter);
	स_नकल(self->prog.filter, filter, माप(filter));
	self->prog.len = (अचिन्हित लघु)ARRAY_SIZE(filter);

	/* Set up tracer args. */
	self->tracer_args.poke_addr = (अचिन्हित दीर्घ)&self->poked;

	/* Launch tracer. */
	self->tracer = setup_trace_fixture(_metadata, tracer_poke,
					   &self->tracer_args, false);
पूर्ण

FIXTURE_TEARDOWN(TRACE_poke)
अणु
	tearकरोwn_trace_fixture(_metadata, self->tracer);
	अगर (self->prog.filter)
		मुक्त(self->prog.filter);
पूर्ण

TEST_F(TRACE_poke, पढ़ो_has_side_effects)
अणु
	sमाप_प्रकार ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->prog, 0, 0);
	ASSERT_EQ(0, ret);

	EXPECT_EQ(0, self->poked);
	ret = पढ़ो(-1, शून्य, 0);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(0x1001, self->poked);
पूर्ण

TEST_F(TRACE_poke, getpid_runs_normally)
अणु
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &self->prog, 0, 0);
	ASSERT_EQ(0, ret);

	EXPECT_EQ(0, self->poked);
	EXPECT_NE(0, syscall(__NR_getpid));
	EXPECT_EQ(0, self->poked);
पूर्ण

#अगर defined(__x86_64__)
# define ARCH_REGS		काष्ठा user_regs_काष्ठा
# define SYSCALL_NUM(_regs)	(_regs).orig_rax
# define SYSCALL_RET(_regs)	(_regs).rax
#या_अगर defined(__i386__)
# define ARCH_REGS		काष्ठा user_regs_काष्ठा
# define SYSCALL_NUM(_regs)	(_regs).orig_eax
# define SYSCALL_RET(_regs)	(_regs).eax
#या_अगर defined(__arm__)
# define ARCH_REGS		काष्ठा pt_regs
# define SYSCALL_NUM(_regs)	(_regs).ARM_r7
# अगरndef PTRACE_SET_SYSCALL
#  define PTRACE_SET_SYSCALL   23
# endअगर
# define SYSCALL_NUM_SET(_regs, _nr)	\
		EXPECT_EQ(0, ptrace(PTRACE_SET_SYSCALL, tracee, शून्य, _nr))
# define SYSCALL_RET(_regs)	(_regs).ARM_r0
#या_अगर defined(__aarch64__)
# define ARCH_REGS		काष्ठा user_pt_regs
# define SYSCALL_NUM(_regs)	(_regs).regs[8]
# अगरndef NT_ARM_SYSTEM_CALL
#  define NT_ARM_SYSTEM_CALL 0x404
# endअगर
# define SYSCALL_NUM_SET(_regs, _nr)				\
	करो अणु							\
		काष्ठा iovec __v;				\
		typeof(_nr) __nr = (_nr);			\
		__v.iov_base = &__nr;				\
		__v.iov_len = माप(__nr);			\
		EXPECT_EQ(0, ptrace(PTRACE_SETREGSET, tracee,	\
				    NT_ARM_SYSTEM_CALL, &__v));	\
	पूर्ण जबतक (0)
# define SYSCALL_RET(_regs)	(_regs).regs[0]
#या_अगर defined(__riscv) && __riscv_xlen == 64
# define ARCH_REGS		काष्ठा user_regs_काष्ठा
# define SYSCALL_NUM(_regs)	(_regs).a7
# define SYSCALL_RET(_regs)	(_regs).a0
#या_अगर defined(__csky__)
# define ARCH_REGS		काष्ठा pt_regs
#  अगर defined(__CSKYABIV2__)
#   define SYSCALL_NUM(_regs)	(_regs).regs[3]
#  अन्यथा
#   define SYSCALL_NUM(_regs)	(_regs).regs[9]
#  endअगर
# define SYSCALL_RET(_regs)	(_regs).a0
#या_अगर defined(__hppa__)
# define ARCH_REGS		काष्ठा user_regs_काष्ठा
# define SYSCALL_NUM(_regs)	(_regs).gr[20]
# define SYSCALL_RET(_regs)	(_regs).gr[28]
#या_अगर defined(__घातerpc__)
# define ARCH_REGS		काष्ठा pt_regs
# define SYSCALL_NUM(_regs)	(_regs).gpr[0]
# define SYSCALL_RET(_regs)	(_regs).gpr[3]
# define SYSCALL_RET_SET(_regs, _val)				\
	करो अणु							\
		typeof(_val) _result = (_val);			\
		अगर ((_regs.trap & 0xfff0) == 0x3000) अणु		\
			/*					\
			 * scv 0 प्रणाली call uses -ve result	\
			 * क्रम error, so no need to adjust.	\
			 */					\
			SYSCALL_RET(_regs) = _result;		\
		पूर्ण अन्यथा अणु					\
			/*					\
			 * A syscall error is संकेतed by the	\
			 * CR0 SO bit and the code is stored as	\
			 * a positive value.			\
			 */					\
			अगर (_result < 0) अणु			\
				SYSCALL_RET(_regs) = -_result;	\
				(_regs).ccr |= 0x10000000;	\
			पूर्ण अन्यथा अणु				\
				SYSCALL_RET(_regs) = _result;	\
				(_regs).ccr &= ~0x10000000;	\
			पूर्ण					\
		पूर्ण						\
	पूर्ण जबतक (0)
# define SYSCALL_RET_SET_ON_PTRACE_EXIT
#या_अगर defined(__s390__)
# define ARCH_REGS		s390_regs
# define SYSCALL_NUM(_regs)	(_regs).gprs[2]
# define SYSCALL_RET_SET(_regs, _val)			\
		TH_LOG("Can't modify syscall return on this architecture")
#या_अगर defined(__mips__)
# include <यंत्र/unistd_nr_n32.h>
# include <यंत्र/unistd_nr_n64.h>
# include <यंत्र/unistd_nr_o32.h>
# define ARCH_REGS		काष्ठा pt_regs
# define SYSCALL_NUM(_regs)				\
	(अणु						\
		typeof((_regs).regs[2]) _nr;		\
		अगर ((_regs).regs[2] == __NR_O32_Linux)	\
			_nr = (_regs).regs[4];		\
		अन्यथा					\
			_nr = (_regs).regs[2];		\
		_nr;					\
	पूर्ण)
# define SYSCALL_NUM_SET(_regs, _nr)			\
	करो अणु						\
		अगर ((_regs).regs[2] == __NR_O32_Linux)	\
			(_regs).regs[4] = _nr;		\
		अन्यथा					\
			(_regs).regs[2] = _nr;		\
	पूर्ण जबतक (0)
# define SYSCALL_RET_SET(_regs, _val)			\
		TH_LOG("Can't modify syscall return on this architecture")
#या_अगर defined(__xtensa__)
# define ARCH_REGS		काष्ठा user_pt_regs
# define SYSCALL_NUM(_regs)	(_regs).syscall
/*
 * On xtensa syscall वापस value is in the रेजिस्टर
 * a2 of the current winकरोw which is not fixed.
 */
#घोषणा SYSCALL_RET(_regs)	(_regs).a[(_regs).winकरोwbase * 4 + 2]
#या_अगर defined(__sh__)
# define ARCH_REGS		काष्ठा pt_regs
# define SYSCALL_NUM(_regs)	(_regs).regs[3]
# define SYSCALL_RET(_regs)	(_regs).regs[0]
#अन्यथा
# error "Do not know how to find your architecture's registers and syscalls"
#पूर्ण_अगर

/*
 * Most architectures can change the syscall by just updating the
 * associated रेजिस्टर. This is the शेष अगर not defined above.
 */
#अगर_अघोषित SYSCALL_NUM_SET
# define SYSCALL_NUM_SET(_regs, _nr)		\
	करो अणु					\
		SYSCALL_NUM(_regs) = (_nr);	\
	पूर्ण जबतक (0)
#पूर्ण_अगर
/*
 * Most architectures can change the syscall वापस value by just
 * writing to the SYSCALL_RET रेजिस्टर. This is the शेष अगर not
 * defined above. If an architecture cannot set the वापस value
 * (क्रम example when the syscall and वापस value रेजिस्टर is
 * shared), report it with TH_LOG() in an arch-specअगरic definition
 * of SYSCALL_RET_SET() above, and leave SYSCALL_RET undefined.
 */
#अगर !defined(SYSCALL_RET) && !defined(SYSCALL_RET_SET)
# error "One of SYSCALL_RET or SYSCALL_RET_SET is needed for this arch"
#पूर्ण_अगर
#अगर_अघोषित SYSCALL_RET_SET
# define SYSCALL_RET_SET(_regs, _val)		\
	करो अणु					\
		SYSCALL_RET(_regs) = (_val);	\
	पूर्ण जबतक (0)
#पूर्ण_अगर

/* When the syscall वापस can't be changed, stub out the tests क्रम it. */
#अगर_अघोषित SYSCALL_RET
# define EXPECT_SYSCALL_RETURN(val, action)	EXPECT_EQ(-1, action)
#अन्यथा
# define EXPECT_SYSCALL_RETURN(val, action)		\
	करो अणु						\
		त्रुटि_सं = 0;				\
		अगर (val < 0) अणु				\
			EXPECT_EQ(-1, action);		\
			EXPECT_EQ(-(val), त्रुटि_सं);	\
		पूर्ण अन्यथा अणु				\
			EXPECT_EQ(val, action);		\
		पूर्ण					\
	पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Some architectures (e.g. घातerpc) can only set syscall
 * वापस values on syscall निकास during ptrace.
 */
स्थिर bool ptrace_entry_set_syscall_nr = true;
स्थिर bool ptrace_entry_set_syscall_ret =
#अगर_अघोषित SYSCALL_RET_SET_ON_PTRACE_EXIT
	true;
#अन्यथा
	false;
#पूर्ण_अगर

/*
 * Use PTRACE_GETREGS and PTRACE_SETREGS when available. This is useful क्रम
 * architectures without HAVE_ARCH_TRACEHOOK (e.g. User-mode Linux).
 */
#अगर defined(__x86_64__) || defined(__i386__) || defined(__mips__)
# define ARCH_GETREGS(_regs)	ptrace(PTRACE_GETREGS, tracee, 0, &(_regs))
# define ARCH_SETREGS(_regs)	ptrace(PTRACE_SETREGS, tracee, 0, &(_regs))
#अन्यथा
# define ARCH_GETREGS(_regs)	(अणु					\
		काष्ठा iovec __v;					\
		__v.iov_base = &(_regs);				\
		__v.iov_len = माप(_regs);				\
		ptrace(PTRACE_GETREGSET, tracee, NT_PRSTATUS, &__v);	\
	पूर्ण)
# define ARCH_SETREGS(_regs)	(अणु					\
		काष्ठा iovec __v;					\
		__v.iov_base = &(_regs);				\
		__v.iov_len = माप(_regs);				\
		ptrace(PTRACE_SETREGSET, tracee, NT_PRSTATUS, &__v);	\
	पूर्ण)
#पूर्ण_अगर

/* Architecture-specअगरic syscall fetching routine. */
पूर्णांक get_syscall(काष्ठा __test_metadata *_metadata, pid_t tracee)
अणु
	ARCH_REGS regs;

	EXPECT_EQ(0, ARCH_GETREGS(regs)) अणु
		वापस -1;
	पूर्ण

	वापस SYSCALL_NUM(regs);
पूर्ण

/* Architecture-specअगरic syscall changing routine. */
व्योम __change_syscall(काष्ठा __test_metadata *_metadata,
		    pid_t tracee, दीर्घ *syscall, दीर्घ *ret)
अणु
	ARCH_REGS orig, regs;

	/* Do not get/set रेजिस्टरs अगर we have nothing to करो. */
	अगर (!syscall && !ret)
		वापस;

	EXPECT_EQ(0, ARCH_GETREGS(regs)) अणु
		वापस;
	पूर्ण
	orig = regs;

	अगर (syscall)
		SYSCALL_NUM_SET(regs, *syscall);

	अगर (ret)
		SYSCALL_RET_SET(regs, *ret);

	/* Flush any रेजिस्टर changes made. */
	अगर (स_भेद(&orig, &regs, माप(orig)) != 0)
		EXPECT_EQ(0, ARCH_SETREGS(regs));
पूर्ण

/* Change only syscall number. */
व्योम change_syscall_nr(काष्ठा __test_metadata *_metadata,
		       pid_t tracee, दीर्घ syscall)
अणु
	__change_syscall(_metadata, tracee, &syscall, शून्य);
पूर्ण

/* Change syscall वापस value (and set syscall number to -1). */
व्योम change_syscall_ret(काष्ठा __test_metadata *_metadata,
			pid_t tracee, दीर्घ ret)
अणु
	दीर्घ syscall = -1;

	__change_syscall(_metadata, tracee, &syscall, &ret);
पूर्ण

व्योम tracer_seccomp(काष्ठा __test_metadata *_metadata, pid_t tracee,
		    पूर्णांक status, व्योम *args)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ msg;

	/* Make sure we got the right message. */
	ret = ptrace(PTRACE_GETEVENTMSG, tracee, शून्य, &msg);
	EXPECT_EQ(0, ret);

	/* Validate and take action on expected syscalls. */
	चयन (msg) अणु
	हाल 0x1002:
		/* change getpid to getppid. */
		EXPECT_EQ(__NR_getpid, get_syscall(_metadata, tracee));
		change_syscall_nr(_metadata, tracee, __NR_getppid);
		अवरोध;
	हाल 0x1003:
		/* skip gettid with valid वापस code. */
		EXPECT_EQ(__NR_gettid, get_syscall(_metadata, tracee));
		change_syscall_ret(_metadata, tracee, 45000);
		अवरोध;
	हाल 0x1004:
		/* skip खोलोat with error. */
		EXPECT_EQ(__NR_खोलोat, get_syscall(_metadata, tracee));
		change_syscall_ret(_metadata, tracee, -ESRCH);
		अवरोध;
	हाल 0x1005:
		/* करो nothing (allow getppid) */
		EXPECT_EQ(__NR_getppid, get_syscall(_metadata, tracee));
		अवरोध;
	शेष:
		EXPECT_EQ(0, msg) अणु
			TH_LOG("Unknown PTRACE_GETEVENTMSG: 0x%lx", msg);
			समाप्त(tracee, SIGKILL);
		पूर्ण
	पूर्ण

पूर्ण

FIXTURE(TRACE_syscall) अणु
	काष्ठा sock_fprog prog;
	pid_t tracer, mytid, mypid, parent;
	दीर्घ syscall_nr;
पूर्ण;

व्योम tracer_ptrace(काष्ठा __test_metadata *_metadata, pid_t tracee,
		   पूर्णांक status, व्योम *args)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ msg;
	अटल bool entry;
	दीर्घ syscall_nr_val, syscall_ret_val;
	दीर्घ *syscall_nr = शून्य, *syscall_ret = शून्य;
	FIXTURE_DATA(TRACE_syscall) *self = args;

	/*
	 * The traditional way to tell PTRACE_SYSCALL entry/निकास
	 * is by counting.
	 */
	entry = !entry;

	/* Make sure we got an appropriate message. */
	ret = ptrace(PTRACE_GETEVENTMSG, tracee, शून्य, &msg);
	EXPECT_EQ(0, ret);
	EXPECT_EQ(entry ? PTRACE_EVENTMSG_SYSCALL_ENTRY
			: PTRACE_EVENTMSG_SYSCALL_EXIT, msg);

	/*
	 * Some architectures only support setting वापस values during
	 * syscall निकास under ptrace, and on निकास the syscall number may
	 * no दीर्घer be available. Thereक्रमe, save the initial sycall
	 * number here, so it can be examined during both entry and निकास
	 * phases.
	 */
	अगर (entry)
		self->syscall_nr = get_syscall(_metadata, tracee);

	/*
	 * Depending on the architecture's syscall setting abilities, we
	 * pick which things to set during this phase (entry or निकास).
	 */
	अगर (entry == ptrace_entry_set_syscall_nr)
		syscall_nr = &syscall_nr_val;
	अगर (entry == ptrace_entry_set_syscall_ret)
		syscall_ret = &syscall_ret_val;

	/* Now handle the actual rewriting हालs. */
	चयन (self->syscall_nr) अणु
	हाल __NR_getpid:
		syscall_nr_val = __NR_getppid;
		/* Never change syscall वापस क्रम this हाल. */
		syscall_ret = शून्य;
		अवरोध;
	हाल __NR_gettid:
		syscall_nr_val = -1;
		syscall_ret_val = 45000;
		अवरोध;
	हाल __NR_खोलोat:
		syscall_nr_val = -1;
		syscall_ret_val = -ESRCH;
		अवरोध;
	शेष:
		/* Unhandled, करो nothing. */
		वापस;
	पूर्ण

	__change_syscall(_metadata, tracee, syscall_nr, syscall_ret);
पूर्ण

FIXTURE_VARIANT(TRACE_syscall) अणु
	/*
	 * All of the SECCOMP_RET_TRACE behaviors can be tested with either
	 * SECCOMP_RET_TRACE+PTRACE_CONT or plain ptrace()+PTRACE_SYSCALL.
	 * This indicates अगर we should use SECCOMP_RET_TRACE (false), or
	 * ptrace (true).
	 */
	bool use_ptrace;
पूर्ण;

FIXTURE_VARIANT_ADD(TRACE_syscall, ptrace) अणु
	.use_ptrace = true,
पूर्ण;

FIXTURE_VARIANT_ADD(TRACE_syscall, seccomp) अणु
	.use_ptrace = false,
पूर्ण;

FIXTURE_SETUP(TRACE_syscall)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRACE | 0x1002),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_gettid, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRACE | 0x1003),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_खोलोat, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRACE | 0x1004),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getppid, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRACE | 0x1005),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	/* Prepare some testable syscall results. */
	self->mytid = syscall(__NR_gettid);
	ASSERT_GT(self->mytid, 0);
	ASSERT_NE(self->mytid, 1) अणु
		TH_LOG("Running this test as init is not supported. :)");
	पूर्ण

	self->mypid = getpid();
	ASSERT_GT(self->mypid, 0);
	ASSERT_EQ(self->mytid, self->mypid);

	self->parent = getppid();
	ASSERT_GT(self->parent, 0);
	ASSERT_NE(self->parent, self->mypid);

	/* Launch tracer. */
	self->tracer = setup_trace_fixture(_metadata,
					   variant->use_ptrace ? tracer_ptrace
							       : tracer_seccomp,
					   self, variant->use_ptrace);

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	अगर (variant->use_ptrace)
		वापस;

	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	ASSERT_EQ(0, ret);
पूर्ण

FIXTURE_TEARDOWN(TRACE_syscall)
अणु
	tearकरोwn_trace_fixture(_metadata, self->tracer);
पूर्ण

TEST(negative_ENOSYS)
अणु
	/*
	 * There should be no dअगरference between an "internal" skip
	 * and userspace asking क्रम syscall "-1".
	 */
	त्रुटि_सं = 0;
	EXPECT_EQ(-1, syscall(-1));
	EXPECT_EQ(त्रुटि_सं, ENOSYS);
	/* And no dअगरference क्रम "still not valid but not -1". */
	त्रुटि_सं = 0;
	EXPECT_EQ(-1, syscall(-101));
	EXPECT_EQ(त्रुटि_सं, ENOSYS);
पूर्ण

TEST_F(TRACE_syscall, negative_ENOSYS)
अणु
	negative_ENOSYS(_metadata);
पूर्ण

TEST_F(TRACE_syscall, syscall_allowed)
अणु
	/* getppid works as expected (no changes). */
	EXPECT_EQ(self->parent, syscall(__NR_getppid));
	EXPECT_NE(self->mypid, syscall(__NR_getppid));
पूर्ण

TEST_F(TRACE_syscall, syscall_redirected)
अणु
	/* getpid has been redirected to getppid as expected. */
	EXPECT_EQ(self->parent, syscall(__NR_getpid));
	EXPECT_NE(self->mypid, syscall(__NR_getpid));
पूर्ण

TEST_F(TRACE_syscall, syscall_त्रुटि_सं)
अणु
	/* Tracer should skip the खोलो syscall, resulting in ESRCH. */
	EXPECT_SYSCALL_RETURN(-ESRCH, syscall(__NR_खोलोat));
पूर्ण

TEST_F(TRACE_syscall, syscall_faked)
अणु
	/* Tracer skips the gettid syscall and store altered वापस value. */
	EXPECT_SYSCALL_RETURN(45000, syscall(__NR_gettid));
पूर्ण

TEST_F(TRACE_syscall, skip_after)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getppid, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ERRNO | EPERM),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	/* Install additional "errno on getppid" filter. */
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	ASSERT_EQ(0, ret);

	/* Tracer will redirect getpid to getppid, and we should see EPERM. */
	त्रुटि_सं = 0;
	EXPECT_EQ(-1, syscall(__NR_getpid));
	EXPECT_EQ(EPERM, त्रुटि_सं);
पूर्ण

TEST_F_SIGNAL(TRACE_syscall, समाप्त_after, SIGSYS)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getppid, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	/* Install additional "death on getppid" filter. */
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
	ASSERT_EQ(0, ret);

	/* Tracer will redirect getpid to getppid, and we should die. */
	EXPECT_NE(self->mypid, syscall(__NR_getpid));
पूर्ण

TEST(seccomp_syscall)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	/* Reject insane operation. */
	ret = seccomp(-1, 0, &prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Did not reject crazy op value!");
	पूर्ण

	/* Reject strict with flags or poपूर्णांकer. */
	ret = seccomp(SECCOMP_SET_MODE_STRICT, -1, शून्य);
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Did not reject mode strict with flags!");
	पूर्ण
	ret = seccomp(SECCOMP_SET_MODE_STRICT, 0, &prog);
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Did not reject mode strict with uargs!");
	पूर्ण

	/* Reject insane args क्रम filter. */
	ret = seccomp(SECCOMP_SET_MODE_FILTER, -1, &prog);
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Did not reject crazy filter flags!");
	पूर्ण
	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, शून्य);
	EXPECT_EQ(EFAULT, त्रुटि_सं) अणु
		TH_LOG("Did not reject NULL filter!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog);
	EXPECT_EQ(0, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support SECCOMP_SET_MODE_FILTER: %s",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

TEST(seccomp_syscall_mode_lock)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, शून्य, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	EXPECT_EQ(0, ret) अणु
		TH_LOG("Could not install filter!");
	पूर्ण

	/* Make sure neither entry poपूर्णांक will चयन to strict. */
	ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT, 0, 0, 0);
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Switched to mode strict!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_STRICT, 0, शून्य);
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Switched to mode strict!");
	पूर्ण
पूर्ण

/*
 * Test detection of known and unknown filter flags. Userspace needs to be able
 * to check अगर a filter flag is supported by the current kernel and a good way
 * of करोing that is by attempting to enter filter mode, with the flag bit in
 * question set, and a शून्य poपूर्णांकer क्रम the _args_ parameter. EFAULT indicates
 * that the flag is valid and EINVAL indicates that the flag is invalid.
 */
TEST(detect_seccomp_filter_flags)
अणु
	अचिन्हित पूर्णांक flags[] = अणु SECCOMP_FILTER_FLAG_TSYNC,
				 SECCOMP_FILTER_FLAG_LOG,
				 SECCOMP_FILTER_FLAG_SPEC_ALLOW,
				 SECCOMP_FILTER_FLAG_NEW_LISTENER,
				 SECCOMP_FILTER_FLAG_TSYNC_ESRCH पूर्ण;
	अचिन्हित पूर्णांक exclusive[] = अणु
				SECCOMP_FILTER_FLAG_TSYNC,
				SECCOMP_FILTER_FLAG_NEW_LISTENER पूर्ण;
	अचिन्हित पूर्णांक flag, all_flags, exclusive_mask;
	पूर्णांक i;
	दीर्घ ret;

	/* Test detection of inभागidual known-good filter flags */
	क्रम (i = 0, all_flags = 0; i < ARRAY_SIZE(flags); i++) अणु
		पूर्णांक bits = 0;

		flag = flags[i];
		/* Make sure the flag is a single bit! */
		जबतक (flag) अणु
			अगर (flag & 0x1)
				bits ++;
			flag >>= 1;
		पूर्ण
		ASSERT_EQ(1, bits);
		flag = flags[i];

		ret = seccomp(SECCOMP_SET_MODE_FILTER, flag, शून्य);
		ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
			TH_LOG("Kernel does not support seccomp syscall!");
		पूर्ण
		EXPECT_EQ(-1, ret);
		EXPECT_EQ(EFAULT, त्रुटि_सं) अणु
			TH_LOG("Failed to detect that a known-good filter flag (0x%X) is supported!",
			       flag);
		पूर्ण

		all_flags |= flag;
	पूर्ण

	/*
	 * Test detection of all known-good filter flags combined. But
	 * क्रम the exclusive flags we need to mask them out and try them
	 * inभागidually क्रम the "all flags" testing.
	 */
	exclusive_mask = 0;
	क्रम (i = 0; i < ARRAY_SIZE(exclusive); i++)
		exclusive_mask |= exclusive[i];
	क्रम (i = 0; i < ARRAY_SIZE(exclusive); i++) अणु
		flag = all_flags & ~exclusive_mask;
		flag |= exclusive[i];

		ret = seccomp(SECCOMP_SET_MODE_FILTER, flag, शून्य);
		EXPECT_EQ(-1, ret);
		EXPECT_EQ(EFAULT, त्रुटि_सं) अणु
			TH_LOG("Failed to detect that all known-good filter flags (0x%X) are supported!",
			       flag);
		पूर्ण
	पूर्ण

	/* Test detection of an unknown filter flags, without exclusives. */
	flag = -1;
	flag &= ~exclusive_mask;
	ret = seccomp(SECCOMP_SET_MODE_FILTER, flag, शून्य);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Failed to detect that an unknown filter flag (0x%X) is unsupported!",
		       flag);
	पूर्ण

	/*
	 * Test detection of an unknown filter flag that may simply need to be
	 * added to this test
	 */
	flag = flags[ARRAY_SIZE(flags) - 1] << 1;
	ret = seccomp(SECCOMP_SET_MODE_FILTER, flag, शून्य);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Failed to detect that an unknown filter flag (0x%X) is unsupported! Does a new flag need to be added to this test?",
		       flag);
	पूर्ण
पूर्ण

TEST(TSYNC_first)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
	दीर्घ ret;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, शून्य, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_TSYNC,
		      &prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	EXPECT_EQ(0, ret) अणु
		TH_LOG("Could not install initial filter with TSYNC!");
	पूर्ण
पूर्ण

#घोषणा TSYNC_SIBLINGS 2
काष्ठा tsync_sibling अणु
	pthपढ़ो_t tid;
	pid_t प्रणाली_tid;
	sem_t *started;
	pthपढ़ो_cond_t *cond;
	pthपढ़ो_mutex_t *mutex;
	पूर्णांक भागerge;
	पूर्णांक num_रुकोs;
	काष्ठा sock_fprog *prog;
	काष्ठा __test_metadata *metadata;
पूर्ण;

/*
 * To aव्योम joining joined thपढ़ोs (which is not allowed by Bionic),
 * make sure we both successfully join and clear the tid to skip a
 * later join attempt during fixture tearकरोwn. Any reमुख्यing thपढ़ोs
 * will be directly समाप्तed during tearकरोwn.
 */
#घोषणा PTHREAD_JOIN(tid, status)					\
	करो अणु								\
		पूर्णांक _rc = pthपढ़ो_join(tid, status);			\
		अगर (_rc) अणु						\
			TH_LOG("pthread_join of tid %u failed: %d\n",	\
				(अचिन्हित पूर्णांक)tid, _rc);		\
		पूर्ण अन्यथा अणु						\
			tid = 0;					\
		पूर्ण							\
	पूर्ण जबतक (0)

FIXTURE(TSYNC) अणु
	काष्ठा sock_fprog root_prog, apply_prog;
	काष्ठा tsync_sibling sibling[TSYNC_SIBLINGS];
	sem_t started;
	pthपढ़ो_cond_t cond;
	pthपढ़ो_mutex_t mutex;
	पूर्णांक sibling_count;
पूर्ण;

FIXTURE_SETUP(TSYNC)
अणु
	काष्ठा sock_filter root_filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_filter apply_filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_पढ़ो, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;

	स_रखो(&self->root_prog, 0, माप(self->root_prog));
	स_रखो(&self->apply_prog, 0, माप(self->apply_prog));
	स_रखो(&self->sibling, 0, माप(self->sibling));
	self->root_prog.filter = दो_स्मृति(माप(root_filter));
	ASSERT_NE(शून्य, self->root_prog.filter);
	स_नकल(self->root_prog.filter, &root_filter, माप(root_filter));
	self->root_prog.len = (अचिन्हित लघु)ARRAY_SIZE(root_filter);

	self->apply_prog.filter = दो_स्मृति(माप(apply_filter));
	ASSERT_NE(शून्य, self->apply_prog.filter);
	स_नकल(self->apply_prog.filter, &apply_filter, माप(apply_filter));
	self->apply_prog.len = (अचिन्हित लघु)ARRAY_SIZE(apply_filter);

	self->sibling_count = 0;
	pthपढ़ो_mutex_init(&self->mutex, शून्य);
	pthपढ़ो_cond_init(&self->cond, शून्य);
	sem_init(&self->started, 0, 0);
	self->sibling[0].tid = 0;
	self->sibling[0].cond = &self->cond;
	self->sibling[0].started = &self->started;
	self->sibling[0].mutex = &self->mutex;
	self->sibling[0].भागerge = 0;
	self->sibling[0].num_रुकोs = 1;
	self->sibling[0].prog = &self->root_prog;
	self->sibling[0].metadata = _metadata;
	self->sibling[1].tid = 0;
	self->sibling[1].cond = &self->cond;
	self->sibling[1].started = &self->started;
	self->sibling[1].mutex = &self->mutex;
	self->sibling[1].भागerge = 0;
	self->sibling[1].prog = &self->root_prog;
	self->sibling[1].num_रुकोs = 1;
	self->sibling[1].metadata = _metadata;
पूर्ण

FIXTURE_TEARDOWN(TSYNC)
अणु
	पूर्णांक sib = 0;

	अगर (self->root_prog.filter)
		मुक्त(self->root_prog.filter);
	अगर (self->apply_prog.filter)
		मुक्त(self->apply_prog.filter);

	क्रम ( ; sib < self->sibling_count; ++sib) अणु
		काष्ठा tsync_sibling *s = &self->sibling[sib];

		अगर (!s->tid)
			जारी;
		/*
		 * If a thपढ़ो is still running, it may be stuck, so hit
		 * it over the head really hard.
		 */
		pthपढ़ो_समाप्त(s->tid, 9);
	पूर्ण
	pthपढ़ो_mutex_destroy(&self->mutex);
	pthपढ़ो_cond_destroy(&self->cond);
	sem_destroy(&self->started);
पूर्ण

व्योम *tsync_sibling(व्योम *data)
अणु
	दीर्घ ret = 0;
	काष्ठा tsync_sibling *me = data;

	me->प्रणाली_tid = syscall(__NR_gettid);

	pthपढ़ो_mutex_lock(me->mutex);
	अगर (me->भागerge) अणु
		/* Just re-apply the root prog to विभाजन the tree */
		ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER,
				me->prog, 0, 0);
	पूर्ण
	sem_post(me->started);
	/* Return outside of started so parent notices failures. */
	अगर (ret) अणु
		pthपढ़ो_mutex_unlock(me->mutex);
		वापस (व्योम *)SIBLING_निकास_त्रुटि;
	पूर्ण
	करो अणु
		pthपढ़ो_cond_रुको(me->cond, me->mutex);
		me->num_रुकोs = me->num_रुकोs - 1;
	पूर्ण जबतक (me->num_रुकोs);
	pthपढ़ो_mutex_unlock(me->mutex);

	ret = prctl(PR_GET_NO_NEW_PRIVS, 0, 0, 0, 0);
	अगर (!ret)
		वापस (व्योम *)SIBLING_EXIT_NEWPRIVS;
	पढ़ो(0, शून्य, 0);
	वापस (व्योम *)SIBLING_EXIT_UNKILLED;
पूर्ण

व्योम tsync_start_sibling(काष्ठा tsync_sibling *sibling)
अणु
	pthपढ़ो_create(&sibling->tid, शून्य, tsync_sibling, (व्योम *)sibling);
पूर्ण

TEST_F(TSYNC, siblings_fail_prctl)
अणु
	दीर्घ ret;
	व्योम *status;
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_prctl, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ERRNO | EINVAL),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;

	ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	/* Check prctl failure detection by requesting sib 0 भागerge. */
	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	ASSERT_EQ(0, ret) अणु
		TH_LOG("setting filter failed");
	पूर्ण

	self->sibling[0].भागerge = 1;
	tsync_start_sibling(&self->sibling[0]);
	tsync_start_sibling(&self->sibling[1]);

	जबतक (self->sibling_count < TSYNC_SIBLINGS) अणु
		sem_रुको(&self->started);
		self->sibling_count++;
	पूर्ण

	/* Signal the thपढ़ोs to clean up*/
	pthपढ़ो_mutex_lock(&self->mutex);
	ASSERT_EQ(0, pthपढ़ो_cond_broadcast(&self->cond)) अणु
		TH_LOG("cond broadcast non-zero");
	पूर्ण
	pthपढ़ो_mutex_unlock(&self->mutex);

	/* Ensure भागerging sibling failed to call prctl. */
	PTHREAD_JOIN(self->sibling[0].tid, &status);
	EXPECT_EQ(SIBLING_निकास_त्रुटि, (दीर्घ)status);
	PTHREAD_JOIN(self->sibling[1].tid, &status);
	EXPECT_EQ(SIBLING_EXIT_UNKILLED, (दीर्घ)status);
पूर्ण

TEST_F(TSYNC, two_siblings_with_ancestor)
अणु
	दीर्घ ret;
	व्योम *status;

	ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, &self->root_prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support SECCOMP_SET_MODE_FILTER!");
	पूर्ण
	tsync_start_sibling(&self->sibling[0]);
	tsync_start_sibling(&self->sibling[1]);

	जबतक (self->sibling_count < TSYNC_SIBLINGS) अणु
		sem_रुको(&self->started);
		self->sibling_count++;
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_TSYNC,
		      &self->apply_prog);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Could install filter on all threads!");
	पूर्ण
	/* Tell the siblings to test the policy */
	pthपढ़ो_mutex_lock(&self->mutex);
	ASSERT_EQ(0, pthपढ़ो_cond_broadcast(&self->cond)) अणु
		TH_LOG("cond broadcast non-zero");
	पूर्ण
	pthपढ़ो_mutex_unlock(&self->mutex);
	/* Ensure they are both समाप्तed and करोn't निकास cleanly. */
	PTHREAD_JOIN(self->sibling[0].tid, &status);
	EXPECT_EQ(0x0, (दीर्घ)status);
	PTHREAD_JOIN(self->sibling[1].tid, &status);
	EXPECT_EQ(0x0, (दीर्घ)status);
पूर्ण

TEST_F(TSYNC, two_sibling_want_nnp)
अणु
	व्योम *status;

	/* start siblings beक्रमe any prctl() operations */
	tsync_start_sibling(&self->sibling[0]);
	tsync_start_sibling(&self->sibling[1]);
	जबतक (self->sibling_count < TSYNC_SIBLINGS) अणु
		sem_रुको(&self->started);
		self->sibling_count++;
	पूर्ण

	/* Tell the siblings to test no policy */
	pthपढ़ो_mutex_lock(&self->mutex);
	ASSERT_EQ(0, pthपढ़ो_cond_broadcast(&self->cond)) अणु
		TH_LOG("cond broadcast non-zero");
	पूर्ण
	pthपढ़ो_mutex_unlock(&self->mutex);

	/* Ensure they are both upset about lacking nnp. */
	PTHREAD_JOIN(self->sibling[0].tid, &status);
	EXPECT_EQ(SIBLING_EXIT_NEWPRIVS, (दीर्घ)status);
	PTHREAD_JOIN(self->sibling[1].tid, &status);
	EXPECT_EQ(SIBLING_EXIT_NEWPRIVS, (दीर्घ)status);
पूर्ण

TEST_F(TSYNC, two_siblings_with_no_filter)
अणु
	दीर्घ ret;
	व्योम *status;

	/* start siblings beक्रमe any prctl() operations */
	tsync_start_sibling(&self->sibling[0]);
	tsync_start_sibling(&self->sibling[1]);
	जबतक (self->sibling_count < TSYNC_SIBLINGS) अणु
		sem_रुको(&self->started);
		self->sibling_count++;
	पूर्ण

	ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_TSYNC,
		      &self->apply_prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Could install filter on all threads!");
	पूर्ण

	/* Tell the siblings to test the policy */
	pthपढ़ो_mutex_lock(&self->mutex);
	ASSERT_EQ(0, pthपढ़ो_cond_broadcast(&self->cond)) अणु
		TH_LOG("cond broadcast non-zero");
	पूर्ण
	pthपढ़ो_mutex_unlock(&self->mutex);

	/* Ensure they are both समाप्तed and करोn't निकास cleanly. */
	PTHREAD_JOIN(self->sibling[0].tid, &status);
	EXPECT_EQ(0x0, (दीर्घ)status);
	PTHREAD_JOIN(self->sibling[1].tid, &status);
	EXPECT_EQ(0x0, (दीर्घ)status);
पूर्ण

TEST_F(TSYNC, two_siblings_with_one_भागergence)
अणु
	दीर्घ ret;
	व्योम *status;

	ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, &self->root_prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support SECCOMP_SET_MODE_FILTER!");
	पूर्ण
	self->sibling[0].भागerge = 1;
	tsync_start_sibling(&self->sibling[0]);
	tsync_start_sibling(&self->sibling[1]);

	जबतक (self->sibling_count < TSYNC_SIBLINGS) अणु
		sem_रुको(&self->started);
		self->sibling_count++;
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_TSYNC,
		      &self->apply_prog);
	ASSERT_EQ(self->sibling[0].प्रणाली_tid, ret) अणु
		TH_LOG("Did not fail on diverged sibling.");
	पूर्ण

	/* Wake the thपढ़ोs */
	pthपढ़ो_mutex_lock(&self->mutex);
	ASSERT_EQ(0, pthपढ़ो_cond_broadcast(&self->cond)) अणु
		TH_LOG("cond broadcast non-zero");
	पूर्ण
	pthपढ़ो_mutex_unlock(&self->mutex);

	/* Ensure they are both unसमाप्तed. */
	PTHREAD_JOIN(self->sibling[0].tid, &status);
	EXPECT_EQ(SIBLING_EXIT_UNKILLED, (दीर्घ)status);
	PTHREAD_JOIN(self->sibling[1].tid, &status);
	EXPECT_EQ(SIBLING_EXIT_UNKILLED, (दीर्घ)status);
पूर्ण

TEST_F(TSYNC, two_siblings_with_one_भागergence_no_tid_in_err)
अणु
	दीर्घ ret, flags;
	व्योम *status;

	ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, &self->root_prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support SECCOMP_SET_MODE_FILTER!");
	पूर्ण
	self->sibling[0].भागerge = 1;
	tsync_start_sibling(&self->sibling[0]);
	tsync_start_sibling(&self->sibling[1]);

	जबतक (self->sibling_count < TSYNC_SIBLINGS) अणु
		sem_रुको(&self->started);
		self->sibling_count++;
	पूर्ण

	flags = SECCOMP_FILTER_FLAG_TSYNC | \
		SECCOMP_FILTER_FLAG_TSYNC_ESRCH;
	ret = seccomp(SECCOMP_SET_MODE_FILTER, flags, &self->apply_prog);
	ASSERT_EQ(ESRCH, त्रुटि_सं) अणु
		TH_LOG("Did not return ESRCH for diverged sibling.");
	पूर्ण
	ASSERT_EQ(-1, ret) अणु
		TH_LOG("Did not fail on diverged sibling.");
	पूर्ण

	/* Wake the thपढ़ोs */
	pthपढ़ो_mutex_lock(&self->mutex);
	ASSERT_EQ(0, pthपढ़ो_cond_broadcast(&self->cond)) अणु
		TH_LOG("cond broadcast non-zero");
	पूर्ण
	pthपढ़ो_mutex_unlock(&self->mutex);

	/* Ensure they are both unसमाप्तed. */
	PTHREAD_JOIN(self->sibling[0].tid, &status);
	EXPECT_EQ(SIBLING_EXIT_UNKILLED, (दीर्घ)status);
	PTHREAD_JOIN(self->sibling[1].tid, &status);
	EXPECT_EQ(SIBLING_EXIT_UNKILLED, (दीर्घ)status);
पूर्ण

TEST_F(TSYNC, two_siblings_not_under_filter)
अणु
	दीर्घ ret, sib;
	व्योम *status;
	काष्ठा बारpec delay = अणु .tv_nsec = 100000000 पूर्ण;

	ASSERT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	/*
	 * Sibling 0 will have its own seccomp policy
	 * and Sibling 1 will not be under seccomp at
	 * all. Sibling 1 will enter seccomp and 0
	 * will cause failure.
	 */
	self->sibling[0].भागerge = 1;
	tsync_start_sibling(&self->sibling[0]);
	tsync_start_sibling(&self->sibling[1]);

	जबतक (self->sibling_count < TSYNC_SIBLINGS) अणु
		sem_रुको(&self->started);
		self->sibling_count++;
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, &self->root_prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support SECCOMP_SET_MODE_FILTER!");
	पूर्ण

	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_TSYNC,
		      &self->apply_prog);
	ASSERT_EQ(ret, self->sibling[0].प्रणाली_tid) अणु
		TH_LOG("Did not fail on diverged sibling.");
	पूर्ण
	sib = 1;
	अगर (ret == self->sibling[0].प्रणाली_tid)
		sib = 0;

	pthपढ़ो_mutex_lock(&self->mutex);

	/* Increment the other siblings num_रुकोs so we can clean up
	 * the one we just saw.
	 */
	self->sibling[!sib].num_रुकोs += 1;

	/* Signal the thपढ़ो to clean up*/
	ASSERT_EQ(0, pthपढ़ो_cond_broadcast(&self->cond)) अणु
		TH_LOG("cond broadcast non-zero");
	पूर्ण
	pthपढ़ो_mutex_unlock(&self->mutex);
	PTHREAD_JOIN(self->sibling[sib].tid, &status);
	EXPECT_EQ(SIBLING_EXIT_UNKILLED, (दीर्घ)status);
	/* Poll क्रम actual task death. pthपढ़ो_join करोesn't guarantee it. */
	जबतक (!समाप्त(self->sibling[sib].प्रणाली_tid, 0))
		nanosleep(&delay, शून्य);
	/* Switch to the reमुख्यing sibling */
	sib = !sib;

	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_TSYNC,
		      &self->apply_prog);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Expected the remaining sibling to sync");
	पूर्ण;

	pthपढ़ो_mutex_lock(&self->mutex);

	/* If reमुख्यing sibling didn't have a chance to wake up during
	 * the first broadcast, manually reduce the num_रुकोs now.
	 */
	अगर (self->sibling[sib].num_रुकोs > 1)
		self->sibling[sib].num_रुकोs = 1;
	ASSERT_EQ(0, pthपढ़ो_cond_broadcast(&self->cond)) अणु
		TH_LOG("cond broadcast non-zero");
	पूर्ण
	pthपढ़ो_mutex_unlock(&self->mutex);
	PTHREAD_JOIN(self->sibling[sib].tid, &status);
	EXPECT_EQ(0, (दीर्घ)status);
	/* Poll क्रम actual task death. pthपढ़ो_join करोesn't guarantee it. */
	जबतक (!समाप्त(self->sibling[sib].प्रणाली_tid, 0))
		nanosleep(&delay, शून्य);

	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_TSYNC,
		      &self->apply_prog);
	ASSERT_EQ(0, ret);  /* just us chickens */
पूर्ण

/* Make sure restarted syscalls are seen directly as "restart_syscall". */
TEST(syscall_restart)
अणु
	दीर्घ ret;
	अचिन्हित दीर्घ msg;
	pid_t child_pid;
	पूर्णांक pipefd[2];
	पूर्णांक status;
	siginfo_t info = अणु पूर्ण;
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			 दुरत्व(काष्ठा seccomp_data, nr)),

#अगर_घोषित __NR_sigवापस
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_sigवापस, 7, 0),
#पूर्ण_अगर
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_पढ़ो, 6, 0),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_निकास, 5, 0),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_rt_sigवापस, 4, 0),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_nanosleep, 5, 0),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_घड़ी_nanosleep, 4, 0),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_restart_syscall, 4, 0),

		/* Allow __NR_ग_लिखो क्रम easy logging. */
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_ग_लिखो, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
		/* The nanosleep jump target. */
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRACE|0x100),
		/* The restart_syscall jump target. */
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_TRACE|0x200),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;
#अगर defined(__arm__)
	काष्ठा utsname utsbuf;
#पूर्ण_अगर

	ASSERT_EQ(0, pipe(pipefd));

	child_pid = विभाजन();
	ASSERT_LE(0, child_pid);
	अगर (child_pid == 0) अणु
		/* Child uses EXPECT not ASSERT to deliver status correctly. */
		अक्षर buf = ' ';
		काष्ठा बारpec समयout = अणु पूर्ण;

		/* Attach parent as tracer and stop. */
		EXPECT_EQ(0, ptrace(PTRACE_TRACEME));
		EXPECT_EQ(0, उठाओ(SIGSTOP));

		EXPECT_EQ(0, बंद(pipefd[1]));

		EXPECT_EQ(0, prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) अणु
			TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
		पूर्ण

		ret = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
		EXPECT_EQ(0, ret) अणु
			TH_LOG("Failed to install filter!");
		पूर्ण

		EXPECT_EQ(1, पढ़ो(pipefd[0], &buf, 1)) अणु
			TH_LOG("Failed to read() sync from parent");
		पूर्ण
		EXPECT_EQ('.', buf) अणु
			TH_LOG("Failed to get sync data from read()");
		पूर्ण

		/* Start nanosleep to be पूर्णांकerrupted. */
		समयout.tv_sec = 1;
		त्रुटि_सं = 0;
		EXPECT_EQ(0, nanosleep(&समयout, शून्य)) अणु
			TH_LOG("Call to nanosleep() failed (errno %d)", त्रुटि_सं);
		पूर्ण

		/* Read final sync from parent. */
		EXPECT_EQ(1, पढ़ो(pipefd[0], &buf, 1)) अणु
			TH_LOG("Failed final read() from parent");
		पूर्ण
		EXPECT_EQ('!', buf) अणु
			TH_LOG("Failed to get final data from read()");
		पूर्ण

		/* Directly report the status of our test harness results. */
		syscall(__NR_निकास, _metadata->passed ? निकास_सफल
						     : निकास_त्रुटि);
	पूर्ण
	EXPECT_EQ(0, बंद(pipefd[0]));

	/* Attach to child, setup options, and release. */
	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));
	ASSERT_EQ(true, WIFSTOPPED(status));
	ASSERT_EQ(0, ptrace(PTRACE_SETOPTIONS, child_pid, शून्य,
			    PTRACE_O_TRACESECCOMP));
	ASSERT_EQ(0, ptrace(PTRACE_CONT, child_pid, शून्य, 0));
	ASSERT_EQ(1, ग_लिखो(pipefd[1], ".", 1));

	/* Wait क्रम nanosleep() to start. */
	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));
	ASSERT_EQ(true, WIFSTOPPED(status));
	ASSERT_EQ(SIGTRAP, WSTOPSIG(status));
	ASSERT_EQ(PTRACE_EVENT_SECCOMP, (status >> 16));
	ASSERT_EQ(0, ptrace(PTRACE_GETEVENTMSG, child_pid, शून्य, &msg));
	ASSERT_EQ(0x100, msg);
	ret = get_syscall(_metadata, child_pid);
	EXPECT_TRUE(ret == __NR_nanosleep || ret == __NR_घड़ी_nanosleep);

	/* Might as well check siginfo क्रम sanity जबतक we're here. */
	ASSERT_EQ(0, ptrace(PTRACE_GETSIGINFO, child_pid, शून्य, &info));
	ASSERT_EQ(SIGTRAP, info.si_signo);
	ASSERT_EQ(SIGTRAP | (PTRACE_EVENT_SECCOMP << 8), info.si_code);
	EXPECT_EQ(0, info.si_त्रुटि_सं);
	EXPECT_EQ(getuid(), info.si_uid);
	/* Verअगरy संकेत delivery came from child (seccomp-triggered). */
	EXPECT_EQ(child_pid, info.si_pid);

	/* Interrupt nanosleep with SIGSTOP (which we'll need to handle). */
	ASSERT_EQ(0, समाप्त(child_pid, SIGSTOP));
	ASSERT_EQ(0, ptrace(PTRACE_CONT, child_pid, शून्य, 0));
	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));
	ASSERT_EQ(true, WIFSTOPPED(status));
	ASSERT_EQ(SIGSTOP, WSTOPSIG(status));
	ASSERT_EQ(0, ptrace(PTRACE_GETSIGINFO, child_pid, शून्य, &info));
	/*
	 * There is no siginfo on SIGSTOP any more, so we can't verअगरy
	 * संकेत delivery came from parent now (getpid() == info.si_pid).
	 * https://lkml.kernel.org/r/CAGXu5jJaZAOzP1qFz66tYrtbuywqb+UN2SOA1VLHpCCOiYvYeg@mail.gmail.com
	 * At least verअगरy the SIGSTOP via PTRACE_GETSIGINFO.
	 */
	EXPECT_EQ(SIGSTOP, info.si_signo);

	/* Restart nanosleep with SIGCONT, which triggers restart_syscall. */
	ASSERT_EQ(0, समाप्त(child_pid, SIGCONT));
	ASSERT_EQ(0, ptrace(PTRACE_CONT, child_pid, शून्य, 0));
	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));
	ASSERT_EQ(true, WIFSTOPPED(status));
	ASSERT_EQ(SIGCONT, WSTOPSIG(status));
	ASSERT_EQ(0, ptrace(PTRACE_CONT, child_pid, शून्य, 0));

	/* Wait क्रम restart_syscall() to start. */
	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));
	ASSERT_EQ(true, WIFSTOPPED(status));
	ASSERT_EQ(SIGTRAP, WSTOPSIG(status));
	ASSERT_EQ(PTRACE_EVENT_SECCOMP, (status >> 16));
	ASSERT_EQ(0, ptrace(PTRACE_GETEVENTMSG, child_pid, शून्य, &msg));

	ASSERT_EQ(0x200, msg);
	ret = get_syscall(_metadata, child_pid);
#अगर defined(__arm__)
	/*
	 * FIXME:
	 * - native ARM रेजिस्टरs करो NOT expose true syscall.
	 * - compat ARM रेजिस्टरs on ARM64 DO expose true syscall.
	 */
	ASSERT_EQ(0, uname(&utsbuf));
	अगर (म_भेदन(utsbuf.machine, "arm", 3) == 0) अणु
		EXPECT_EQ(__NR_nanosleep, ret);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		EXPECT_EQ(__NR_restart_syscall, ret);
	पूर्ण

	/* Write again to end test. */
	ASSERT_EQ(0, ptrace(PTRACE_CONT, child_pid, शून्य, 0));
	ASSERT_EQ(1, ग_लिखो(pipefd[1], "!", 1));
	EXPECT_EQ(0, बंद(pipefd[1]));

	ASSERT_EQ(child_pid, रुकोpid(child_pid, &status, 0));
	अगर (WIFSIGNALED(status) || WEXITSTATUS(status))
		_metadata->passed = 0;
पूर्ण

TEST_SIGNAL(filter_flag_log, SIGSYS)
अणु
	काष्ठा sock_filter allow_filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_filter समाप्त_filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_getpid, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog allow_prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(allow_filter),
		.filter = allow_filter,
	पूर्ण;
	काष्ठा sock_fprog समाप्त_prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(समाप्त_filter),
		.filter = समाप्त_filter,
	पूर्ण;
	दीर्घ ret;
	pid_t parent = getppid();

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret);

	/* Verअगरy that the FILTER_FLAG_LOG flag isn't accepted in strict mode */
	ret = seccomp(SECCOMP_SET_MODE_STRICT, SECCOMP_FILTER_FLAG_LOG,
		      &allow_prog);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	EXPECT_NE(0, ret) अणु
		TH_LOG("Kernel accepted FILTER_FLAG_LOG flag in strict mode!");
	पूर्ण
	EXPECT_EQ(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Kernel returned unexpected errno for FILTER_FLAG_LOG flag in strict mode!");
	पूर्ण

	/* Verअगरy that a simple, permissive filter can be added with no flags */
	ret = seccomp(SECCOMP_SET_MODE_FILTER, 0, &allow_prog);
	EXPECT_EQ(0, ret);

	/* See अगर the same filter can be added with the FILTER_FLAG_LOG flag */
	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_LOG,
		      &allow_prog);
	ASSERT_NE(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support the FILTER_FLAG_LOG flag!");
	पूर्ण
	EXPECT_EQ(0, ret);

	/* Ensure that the समाप्त filter works with the FILTER_FLAG_LOG flag */
	ret = seccomp(SECCOMP_SET_MODE_FILTER, SECCOMP_FILTER_FLAG_LOG,
		      &समाप्त_prog);
	EXPECT_EQ(0, ret);

	EXPECT_EQ(parent, syscall(__NR_getppid));
	/* getpid() should never वापस. */
	EXPECT_EQ(0, syscall(__NR_getpid));
पूर्ण

TEST(get_action_avail)
अणु
	__u32 actions[] = अणु SECCOMP_RET_KILL_THREAD, SECCOMP_RET_TRAP,
			    SECCOMP_RET_ERRNO, SECCOMP_RET_TRACE,
			    SECCOMP_RET_LOG,   SECCOMP_RET_ALLOW पूर्ण;
	__u32 unknown_action = 0x10000000U;
	पूर्णांक i;
	दीर्घ ret;

	ret = seccomp(SECCOMP_GET_ACTION_AVAIL, 0, &actions[0]);
	ASSERT_NE(ENOSYS, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support seccomp syscall!");
	पूर्ण
	ASSERT_NE(EINVAL, त्रुटि_सं) अणु
		TH_LOG("Kernel does not support SECCOMP_GET_ACTION_AVAIL operation!");
	पूर्ण
	EXPECT_EQ(ret, 0);

	क्रम (i = 0; i < ARRAY_SIZE(actions); i++) अणु
		ret = seccomp(SECCOMP_GET_ACTION_AVAIL, 0, &actions[i]);
		EXPECT_EQ(ret, 0) अणु
			TH_LOG("Expected action (0x%X) not available!",
			       actions[i]);
		पूर्ण
	पूर्ण

	/* Check that an unknown action is handled properly (EOPNOTSUPP) */
	ret = seccomp(SECCOMP_GET_ACTION_AVAIL, 0, &unknown_action);
	EXPECT_EQ(ret, -1);
	EXPECT_EQ(त्रुटि_सं, EOPNOTSUPP);
पूर्ण

TEST(get_metadata)
अणु
	pid_t pid;
	पूर्णांक pipefd[2];
	अक्षर buf;
	काष्ठा seccomp_metadata md;
	दीर्घ ret;

	/* Only real root can get metadata. */
	अगर (geteuid()) अणु
		SKIP(वापस, "get_metadata requires real root");
		वापस;
	पूर्ण

	ASSERT_EQ(0, pipe(pipefd));

	pid = विभाजन();
	ASSERT_GE(pid, 0);
	अगर (pid == 0) अणु
		काष्ठा sock_filter filter[] = अणु
			BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
		पूर्ण;
		काष्ठा sock_fprog prog = अणु
			.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
			.filter = filter,
		पूर्ण;

		/* one with log, one without */
		EXPECT_EQ(0, seccomp(SECCOMP_SET_MODE_FILTER,
				     SECCOMP_FILTER_FLAG_LOG, &prog));
		EXPECT_EQ(0, seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog));

		EXPECT_EQ(0, बंद(pipefd[0]));
		ASSERT_EQ(1, ग_लिखो(pipefd[1], "1", 1));
		ASSERT_EQ(0, बंद(pipefd[1]));

		जबतक (1)
			sleep(100);
	पूर्ण

	ASSERT_EQ(0, बंद(pipefd[1]));
	ASSERT_EQ(1, पढ़ो(pipefd[0], &buf, 1));

	ASSERT_EQ(0, ptrace(PTRACE_ATTACH, pid));
	ASSERT_EQ(pid, रुकोpid(pid, शून्य, 0));

	/* Past here must not use ASSERT or child process is never समाप्तed. */

	md.filter_off = 0;
	त्रुटि_सं = 0;
	ret = ptrace(PTRACE_SECCOMP_GET_METADATA, pid, माप(md), &md);
	EXPECT_EQ(माप(md), ret) अणु
		अगर (त्रुटि_सं == EINVAL)
			SKIP(जाओ skip, "Kernel does not support PTRACE_SECCOMP_GET_METADATA (missing CONFIG_CHECKPOINT_RESTORE?)");
	पूर्ण

	EXPECT_EQ(md.flags, SECCOMP_FILTER_FLAG_LOG);
	EXPECT_EQ(md.filter_off, 0);

	md.filter_off = 1;
	ret = ptrace(PTRACE_SECCOMP_GET_METADATA, pid, माप(md), &md);
	EXPECT_EQ(माप(md), ret);
	EXPECT_EQ(md.flags, 0);
	EXPECT_EQ(md.filter_off, 1);

skip:
	ASSERT_EQ(0, समाप्त(pid, SIGKILL));
पूर्ण

अटल पूर्णांक user_notअगर_syscall(पूर्णांक nr, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_LD|BPF_W|BPF_ABS,
			दुरत्व(काष्ठा seccomp_data, nr)),
		BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, nr, 0, 1),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_USER_NOTIF),
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;

	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;

	वापस seccomp(SECCOMP_SET_MODE_FILTER, flags, &prog);
पूर्ण

#घोषणा USER_NOTIF_MAGIC पूर्णांक_उच्च
TEST(user_notअगरication_basic)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक status, listener;
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;
	काष्ठा pollfd pollfd;

	काष्ठा sock_filter filter[] = अणु
		BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),
	पूर्ण;
	काष्ठा sock_fprog prog = अणु
		.len = (अचिन्हित लघु)ARRAY_SIZE(filter),
		.filter = filter,
	पूर्ण;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	/* Check that we get -ENOSYS with no listener attached */
	अगर (pid == 0) अणु
		अगर (user_notअगर_syscall(__NR_getppid, 0) < 0)
			निकास(1);
		ret = syscall(__NR_getppid);
		निकास(ret >= 0 || त्रुटि_सं != ENOSYS);
	पूर्ण

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));

	/* Add some no-op filters क्रम grins. */
	EXPECT_EQ(seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog), 0);
	EXPECT_EQ(seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog), 0);
	EXPECT_EQ(seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog), 0);
	EXPECT_EQ(seccomp(SECCOMP_SET_MODE_FILTER, 0, &prog), 0);

	/* Check that the basic notअगरication machinery works */
	listener = user_notअगर_syscall(__NR_getppid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	/* Installing a second listener in the chain should EBUSY */
	EXPECT_EQ(user_notअगर_syscall(__NR_getppid,
				     SECCOMP_FILTER_FLAG_NEW_LISTENER),
		  -1);
	EXPECT_EQ(त्रुटि_सं, EBUSY);

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		ret = syscall(__NR_getppid);
		निकास(ret != USER_NOTIF_MAGIC);
	पूर्ण

	pollfd.fd = listener;
	pollfd.events = POLLIN | POLLOUT;

	EXPECT_GT(poll(&pollfd, 1, -1), 0);
	EXPECT_EQ(pollfd.revents, POLLIN);

	/* Test that we can't pass garbage to the kernel. */
	स_रखो(&req, 0, माप(req));
	req.pid = -1;
	त्रुटि_सं = 0;
	ret = ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req);
	EXPECT_EQ(-1, ret);
	EXPECT_EQ(EINVAL, त्रुटि_सं);

	अगर (ret) अणु
		req.pid = 0;
		EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);
	पूर्ण

	pollfd.fd = listener;
	pollfd.events = POLLIN | POLLOUT;

	EXPECT_GT(poll(&pollfd, 1, -1), 0);
	EXPECT_EQ(pollfd.revents, POLLOUT);

	EXPECT_EQ(req.data.nr,  __NR_getppid);

	resp.id = req.id;
	resp.error = 0;
	resp.val = USER_NOTIF_MAGIC;

	/* check that we make sure flags == 0 */
	resp.flags = 1;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), -1);
	EXPECT_EQ(त्रुटि_सं, EINVAL);

	resp.flags = 0;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0);

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
पूर्ण

TEST(user_notअगरication_with_tsync)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक flags;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	/* these were exclusive */
	flags = SECCOMP_FILTER_FLAG_NEW_LISTENER |
		SECCOMP_FILTER_FLAG_TSYNC;
	ASSERT_EQ(-1, user_notअगर_syscall(__NR_getppid, flags));
	ASSERT_EQ(EINVAL, त्रुटि_सं);

	/* but now they're not */
	flags |= SECCOMP_FILTER_FLAG_TSYNC_ESRCH;
	ret = user_notअगर_syscall(__NR_getppid, flags);
	बंद(ret);
	ASSERT_LE(0, ret);
पूर्ण

TEST(user_notअगरication_समाप्त_in_middle)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक listener;
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	listener = user_notअगर_syscall(__NR_getppid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	/*
	 * Check that nothing bad happens when we समाप्त the task in the middle
	 * of a syscall.
	 */
	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		ret = syscall(__NR_getppid);
		निकास(ret != USER_NOTIF_MAGIC);
	पूर्ण

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ID_VALID, &req.id), 0);

	EXPECT_EQ(समाप्त(pid, SIGKILL), 0);
	EXPECT_EQ(रुकोpid(pid, शून्य, 0), pid);

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ID_VALID, &req.id), -1);

	resp.id = req.id;
	ret = ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp);
	EXPECT_EQ(ret, -1);
	EXPECT_EQ(त्रुटि_सं, ENOENT);
पूर्ण

अटल पूर्णांक handled = -1;

अटल व्योम संकेत_handler(पूर्णांक संकेत)
अणु
	अगर (ग_लिखो(handled, "c", 1) != 1)
		लिखो_त्रुटि("write from signal");
पूर्ण

TEST(user_notअगरication_संकेत)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक status, listener, sk_pair[2];
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;
	अक्षर c;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	ASSERT_EQ(socketpair(PF_LOCAL, SOCK_SEQPACKET, 0, sk_pair), 0);

	listener = user_notअगर_syscall(__NR_gettid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		बंद(sk_pair[0]);
		handled = sk_pair[1];
		अगर (संकेत(SIGUSR1, संकेत_handler) == संक_त्रुटि) अणु
			लिखो_त्रुटि("signal");
			निकास(1);
		पूर्ण
		/*
		 * ERESTARTSYS behavior is a bit hard to test, because we need
		 * to rely on a संकेत that has not yet been handled. Let's at
		 * least check that the error code माला_लो propagated through, and
		 * hope that it करोesn't अवरोध when there is actually a संकेत :)
		 */
		ret = syscall(__NR_gettid);
		निकास(!(ret == -1 && त्रुटि_सं == 512));
	पूर्ण

	बंद(sk_pair[1]);

	स_रखो(&req, 0, माप(req));
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);

	EXPECT_EQ(समाप्त(pid, SIGUSR1), 0);

	/*
	 * Make sure the संकेत really is delivered, which means we're not
	 * stuck in the user notअगरication code any more and the notअगरication
	 * should be dead.
	 */
	EXPECT_EQ(पढ़ो(sk_pair[0], &c, 1), 1);

	resp.id = req.id;
	resp.error = -EPERM;
	resp.val = 0;

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), -1);
	EXPECT_EQ(त्रुटि_सं, ENOENT);

	स_रखो(&req, 0, माप(req));
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);

	resp.id = req.id;
	resp.error = -512; /* -ERESTARTSYS */
	resp.val = 0;

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0);

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
पूर्ण

TEST(user_notअगरication_बंदd_listener)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक status, listener;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	listener = user_notअगर_syscall(__NR_getppid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	/*
	 * Check that we get an ENOSYS when the listener is बंदd.
	 */
	pid = विभाजन();
	ASSERT_GE(pid, 0);
	अगर (pid == 0) अणु
		बंद(listener);
		ret = syscall(__NR_getppid);
		निकास(ret != -1 && त्रुटि_सं != ENOSYS);
	पूर्ण

	बंद(listener);

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
पूर्ण

/*
 * Check that a pid in a child namespace still shows up as valid in ours.
 */
TEST(user_notअगरication_child_pid_ns)
अणु
	pid_t pid;
	पूर्णांक status, listener;
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;

	ASSERT_EQ(unshare(CLONE_NEWUSER | CLONE_NEWPID), 0) अणु
		अगर (त्रुटि_सं == EINVAL)
			SKIP(वापस, "kernel missing CLONE_NEWUSER support");
	पूर्ण;

	listener = user_notअगर_syscall(__NR_getppid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0)
		निकास(syscall(__NR_getppid) != USER_NOTIF_MAGIC);

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);
	EXPECT_EQ(req.pid, pid);

	resp.id = req.id;
	resp.error = 0;
	resp.val = USER_NOTIF_MAGIC;

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0);

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
	बंद(listener);
पूर्ण

/*
 * Check that a pid in a sibling (i.e. unrelated) namespace shows up as 0, i.e.
 * invalid.
 */
TEST(user_notअगरication_sibling_pid_ns)
अणु
	pid_t pid, pid2;
	पूर्णांक status, listener;
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;

	ASSERT_EQ(prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0), 0) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	listener = user_notअगर_syscall(__NR_getppid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		ASSERT_EQ(unshare(CLONE_NEWPID), 0);

		pid2 = विभाजन();
		ASSERT_GE(pid2, 0);

		अगर (pid2 == 0)
			निकास(syscall(__NR_getppid) != USER_NOTIF_MAGIC);

		EXPECT_EQ(रुकोpid(pid2, &status, 0), pid2);
		EXPECT_EQ(true, WIFEXITED(status));
		EXPECT_EQ(0, WEXITSTATUS(status));
		निकास(WEXITSTATUS(status));
	पूर्ण

	/* Create the sibling ns, and sibling in it. */
	ASSERT_EQ(unshare(CLONE_NEWPID), 0) अणु
		अगर (त्रुटि_सं == EPERM)
			SKIP(वापस, "CLONE_NEWPID requires CAP_SYS_ADMIN");
	पूर्ण
	ASSERT_EQ(त्रुटि_सं, 0);

	pid2 = विभाजन();
	ASSERT_GE(pid2, 0);

	अगर (pid2 == 0) अणु
		ASSERT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);
		/*
		 * The pid should be 0, i.e. the task is in some namespace that
		 * we can't "see".
		 */
		EXPECT_EQ(req.pid, 0);

		resp.id = req.id;
		resp.error = 0;
		resp.val = USER_NOTIF_MAGIC;

		ASSERT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0);
		निकास(0);
	पूर्ण

	बंद(listener);

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));

	EXPECT_EQ(रुकोpid(pid2, &status, 0), pid2);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
पूर्ण

TEST(user_notअगरication_fault_recv)
अणु
	pid_t pid;
	पूर्णांक status, listener;
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;

	ASSERT_EQ(unshare(CLONE_NEWUSER), 0);

	listener = user_notअगर_syscall(__NR_getppid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0)
		निकास(syscall(__NR_getppid) != USER_NOTIF_MAGIC);

	/* Do a bad recv() */
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, शून्य), -1);
	EXPECT_EQ(त्रुटि_सं, EFAULT);

	/* We should still be able to receive this notअगरication, though. */
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);
	EXPECT_EQ(req.pid, pid);

	resp.id = req.id;
	resp.error = 0;
	resp.val = USER_NOTIF_MAGIC;

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0);

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
पूर्ण

TEST(seccomp_get_notअगर_sizes)
अणु
	काष्ठा seccomp_notअगर_sizes sizes;

	ASSERT_EQ(seccomp(SECCOMP_GET_NOTIF_SIZES, 0, &sizes), 0);
	EXPECT_EQ(sizes.seccomp_notअगर, माप(काष्ठा seccomp_notअगर));
	EXPECT_EQ(sizes.seccomp_notअगर_resp, माप(काष्ठा seccomp_notअगर_resp));
पूर्ण

TEST(user_notअगरication_जारी)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक status, listener;
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;
	काष्ठा pollfd pollfd;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	listener = user_notअगर_syscall(__NR_dup, SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		पूर्णांक dup_fd, pipe_fds[2];
		pid_t self;

		ASSERT_GE(pipe(pipe_fds), 0);

		dup_fd = dup(pipe_fds[0]);
		ASSERT_GE(dup_fd, 0);
		EXPECT_NE(pipe_fds[0], dup_fd);

		self = getpid();
		ASSERT_EQ(filecmp(self, self, pipe_fds[0], dup_fd), 0);
		निकास(0);
	पूर्ण

	pollfd.fd = listener;
	pollfd.events = POLLIN | POLLOUT;

	EXPECT_GT(poll(&pollfd, 1, -1), 0);
	EXPECT_EQ(pollfd.revents, POLLIN);

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);

	pollfd.fd = listener;
	pollfd.events = POLLIN | POLLOUT;

	EXPECT_GT(poll(&pollfd, 1, -1), 0);
	EXPECT_EQ(pollfd.revents, POLLOUT);

	EXPECT_EQ(req.data.nr, __NR_dup);

	resp.id = req.id;
	resp.flags = SECCOMP_USER_NOTIF_FLAG_CONTINUE;

	/*
	 * Verअगरy that setting SECCOMP_USER_NOTIF_FLAG_CONTINUE enक्रमces other
	 * args be set to 0.
	 */
	resp.error = 0;
	resp.val = USER_NOTIF_MAGIC;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), -1);
	EXPECT_EQ(त्रुटि_सं, EINVAL);

	resp.error = USER_NOTIF_MAGIC;
	resp.val = 0;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), -1);
	EXPECT_EQ(त्रुटि_सं, EINVAL);

	resp.error = 0;
	resp.val = 0;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0) अणु
		अगर (त्रुटि_सं == EINVAL)
			SKIP(जाओ skip, "Kernel does not support SECCOMP_USER_NOTIF_FLAG_CONTINUE");
	पूर्ण

skip:
	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status)) अणु
		अगर (WEXITSTATUS(status) == 2) अणु
			SKIP(वापस, "Kernel does not support kcmp() syscall");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

TEST(user_notअगरication_filter_empty)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक status;
	काष्ठा pollfd pollfd;
	काष्ठा __clone_args args = अणु
		.flags = CLONE_खाताS,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	pid = sys_clone3(&args, माप(args));
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		पूर्णांक listener;

		listener = user_notअगर_syscall(__NR_mknodat, SECCOMP_FILTER_FLAG_NEW_LISTENER);
		अगर (listener < 0)
			_निकास(निकास_त्रुटि);

		अगर (dup2(listener, 200) != 200)
			_निकास(निकास_त्रुटि);

		बंद(listener);

		_निकास(निकास_सफल);
	पूर्ण

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));

	/*
	 * The seccomp filter has become unused so we should be notअगरied once
	 * the kernel माला_लो around to cleaning up task काष्ठा.
	 */
	pollfd.fd = 200;
	pollfd.events = POLLHUP;

	EXPECT_GT(poll(&pollfd, 1, 2000), 0);
	EXPECT_GT((pollfd.revents & POLLHUP) ?: 0, 0);
पूर्ण

अटल व्योम *करो_thपढ़ो(व्योम *data)
अणु
	वापस शून्य;
पूर्ण

TEST(user_notअगरication_filter_empty_thपढ़ोed)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक status;
	काष्ठा pollfd pollfd;
	काष्ठा __clone_args args = अणु
		.flags = CLONE_खाताS,
		.निकास_संकेत = SIGCHLD,
	पूर्ण;

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	pid = sys_clone3(&args, माप(args));
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		pid_t pid1, pid2;
		पूर्णांक listener, status;
		pthपढ़ो_t thपढ़ो;

		listener = user_notअगर_syscall(__NR_dup, SECCOMP_FILTER_FLAG_NEW_LISTENER);
		अगर (listener < 0)
			_निकास(निकास_त्रुटि);

		अगर (dup2(listener, 200) != 200)
			_निकास(निकास_त्रुटि);

		बंद(listener);

		pid1 = विभाजन();
		अगर (pid1 < 0)
			_निकास(निकास_त्रुटि);

		अगर (pid1 == 0)
			_निकास(निकास_सफल);

		pid2 = विभाजन();
		अगर (pid2 < 0)
			_निकास(निकास_त्रुटि);

		अगर (pid2 == 0)
			_निकास(निकास_सफल);

		अगर (pthपढ़ो_create(&thपढ़ो, शून्य, करो_thपढ़ो, शून्य) ||
		    pthपढ़ो_join(thपढ़ो, शून्य))
			_निकास(निकास_त्रुटि);

		अगर (pthपढ़ो_create(&thपढ़ो, शून्य, करो_thपढ़ो, शून्य) ||
		    pthपढ़ो_join(thपढ़ो, शून्य))
			_निकास(निकास_त्रुटि);

		अगर (रुकोpid(pid1, &status, 0) != pid1 || !WIFEXITED(status) ||
		    WEXITSTATUS(status))
			_निकास(निकास_त्रुटि);

		अगर (रुकोpid(pid2, &status, 0) != pid2 || !WIFEXITED(status) ||
		    WEXITSTATUS(status))
			_निकास(निकास_त्रुटि);

		निकास(निकास_सफल);
	पूर्ण

	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));

	/*
	 * The seccomp filter has become unused so we should be notअगरied once
	 * the kernel माला_लो around to cleaning up task काष्ठा.
	 */
	pollfd.fd = 200;
	pollfd.events = POLLHUP;

	EXPECT_GT(poll(&pollfd, 1, 2000), 0);
	EXPECT_GT((pollfd.revents & POLLHUP) ?: 0, 0);
पूर्ण

TEST(user_notअगरication_addfd)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक status, listener, memfd, fd;
	काष्ठा seccomp_notअगर_addfd addfd = अणुपूर्ण;
	काष्ठा seccomp_notअगर_addfd_small small = अणुपूर्ण;
	काष्ठा seccomp_notअगर_addfd_big big = अणुपूर्ण;
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;
	/* 100 ms */
	काष्ठा बारpec delay = अणु .tv_nsec = 100000000 पूर्ण;

	memfd = memfd_create("test", 0);
	ASSERT_GE(memfd, 0);

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	/* Check that the basic notअगरication machinery works */
	listener = user_notअगर_syscall(__NR_getppid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0) अणु
		अगर (syscall(__NR_getppid) != USER_NOTIF_MAGIC)
			निकास(1);
		निकास(syscall(__NR_getppid) != USER_NOTIF_MAGIC);
	पूर्ण

	ASSERT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);

	addfd.srcfd = memfd;
	addfd.newfd = 0;
	addfd.id = req.id;
	addfd.flags = 0x0;

	/* Verअगरy bad newfd_flags cannot be set */
	addfd.newfd_flags = ~O_CLOEXEC;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD, &addfd), -1);
	EXPECT_EQ(त्रुटि_सं, EINVAL);
	addfd.newfd_flags = O_CLOEXEC;

	/* Verअगरy bad flags cannot be set */
	addfd.flags = 0xff;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD, &addfd), -1);
	EXPECT_EQ(त्रुटि_सं, EINVAL);
	addfd.flags = 0;

	/* Verअगरy that remote_fd cannot be set without setting flags */
	addfd.newfd = 1;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD, &addfd), -1);
	EXPECT_EQ(त्रुटि_सं, EINVAL);
	addfd.newfd = 0;

	/* Verअगरy small size cannot be set */
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD_SMALL, &small), -1);
	EXPECT_EQ(त्रुटि_सं, EINVAL);

	/* Verअगरy we can't send bits filled in unknown buffer area */
	स_रखो(&big, 0xAA, माप(big));
	big.addfd = addfd;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD_BIG, &big), -1);
	EXPECT_EQ(त्रुटि_सं, E2BIG);


	/* Verअगरy we can set an arbitrary remote fd */
	fd = ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD, &addfd);
	EXPECT_GE(fd, 0);
	EXPECT_EQ(filecmp(getpid(), pid, memfd, fd), 0);

	/* Verअगरy we can set an arbitrary remote fd with large size */
	स_रखो(&big, 0x0, माप(big));
	big.addfd = addfd;
	fd = ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD_BIG, &big);
	EXPECT_GE(fd, 0);

	/* Verअगरy we can set a specअगरic remote fd */
	addfd.newfd = 42;
	addfd.flags = SECCOMP_ADDFD_FLAG_SETFD;
	fd = ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD, &addfd);
	EXPECT_EQ(fd, 42);
	EXPECT_EQ(filecmp(getpid(), pid, memfd, fd), 0);

	/* Resume syscall */
	resp.id = req.id;
	resp.error = 0;
	resp.val = USER_NOTIF_MAGIC;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0);

	/*
	 * This sets the ID of the ADD FD to the last request plus 1. The
	 * notअगरication ID increments 1 per notअगरication.
	 */
	addfd.id = req.id + 1;

	/* This spins until the underlying notअगरication is generated */
	जबतक (ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD, &addfd) != -1 &&
	       त्रुटि_सं != -EINPROGRESS)
		nanosleep(&delay, शून्य);

	स_रखो(&req, 0, माप(req));
	ASSERT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);
	ASSERT_EQ(addfd.id, req.id);

	resp.id = req.id;
	resp.error = 0;
	resp.val = USER_NOTIF_MAGIC;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0);

	/* Wait क्रम child to finish. */
	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));

	बंद(memfd);
पूर्ण

TEST(user_notअगरication_addfd_rlimit)
अणु
	pid_t pid;
	दीर्घ ret;
	पूर्णांक status, listener, memfd;
	काष्ठा seccomp_notअगर_addfd addfd = अणुपूर्ण;
	काष्ठा seccomp_notअगर req = अणुपूर्ण;
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;
	स्थिर काष्ठा rlimit lim = अणु
		.rlim_cur	= 0,
		.rlim_max	= 0,
	पूर्ण;

	memfd = memfd_create("test", 0);
	ASSERT_GE(memfd, 0);

	ret = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	ASSERT_EQ(0, ret) अणु
		TH_LOG("Kernel does not support PR_SET_NO_NEW_PRIVS!");
	पूर्ण

	/* Check that the basic notअगरication machinery works */
	listener = user_notअगर_syscall(__NR_getppid,
				      SECCOMP_FILTER_FLAG_NEW_LISTENER);
	ASSERT_GE(listener, 0);

	pid = विभाजन();
	ASSERT_GE(pid, 0);

	अगर (pid == 0)
		निकास(syscall(__NR_getppid) != USER_NOTIF_MAGIC);


	ASSERT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_RECV, &req), 0);

	ASSERT_EQ(prlimit(pid, RLIMIT_NOखाता, &lim, शून्य), 0);

	addfd.srcfd = memfd;
	addfd.newfd_flags = O_CLOEXEC;
	addfd.newfd = 0;
	addfd.id = req.id;
	addfd.flags = 0;

	/* Should probably spot check /proc/sys/fs/file-nr */
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD, &addfd), -1);
	EXPECT_EQ(त्रुटि_सं, EMखाता);

	addfd.newfd = 100;
	addfd.flags = SECCOMP_ADDFD_FLAG_SETFD;
	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_ADDFD, &addfd), -1);
	EXPECT_EQ(त्रुटि_सं, EBADF);

	resp.id = req.id;
	resp.error = 0;
	resp.val = USER_NOTIF_MAGIC;

	EXPECT_EQ(ioctl(listener, SECCOMP_IOCTL_NOTIF_SEND, &resp), 0);

	/* Wait क्रम child to finish. */
	EXPECT_EQ(रुकोpid(pid, &status, 0), pid);
	EXPECT_EQ(true, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));

	बंद(memfd);
पूर्ण

/*
 * TODO:
 * - expand NNP testing
 * - better arch-specअगरic TRACE and TRAP handlers.
 * - endianness checking when appropriate
 * - 64-bit arg prodding
 * - arch value testing (x86 modes especially)
 * - verअगरy that FILTER_FLAG_LOG filters generate log messages
 * - verअगरy that RET_LOG generates log messages
 */

TEST_HARNESS_MAIN

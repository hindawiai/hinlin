<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2018 Dmitry V. Levin <ldv@altlinux.org>
 * All rights reserved.
 *
 * Check whether PTRACE_GET_SYSCALL_INFO semantics implemented in the kernel
 * matches userspace expectations.
 */

#समावेश "../kselftest_harness.h"
#समावेश <err.h>
#समावेश <संकेत.स>
#समावेश <यंत्र/unistd.h>
#समावेश "linux/ptrace.h"

अटल पूर्णांक
समाप्त_tracee(pid_t pid)
अणु
	अगर (!pid)
		वापस 0;

	पूर्णांक saved_त्रुटि_सं = त्रुटि_सं;

	पूर्णांक rc = समाप्त(pid, SIGKILL);

	त्रुटि_सं = saved_त्रुटि_सं;
	वापस rc;
पूर्ण

अटल दीर्घ
sys_ptrace(पूर्णांक request, pid_t pid, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	वापस syscall(__NR_ptrace, request, pid, addr, data);
पूर्ण

#घोषणा LOG_KILL_TRACEE(fmt, ...)				\
	करो अणु							\
		समाप्त_tracee(pid);				\
		TH_LOG("wait #%d: " fmt,			\
		       ptrace_stop, ##__VA_ARGS__);		\
	पूर्ण जबतक (0)

TEST(get_syscall_info)
अणु
	अटल स्थिर अचिन्हित दीर्घ args[][7] = अणु
		/* a sequence of architecture-agnostic syscalls */
		अणु
			__NR_स_बदलो,
			(अचिन्हित दीर्घ) "",
			0xbad1fed1,
			0xbad2fed2,
			0xbad3fed3,
			0xbad4fed4,
			0xbad5fed5
		पूर्ण,
		अणु
			__NR_gettid,
			0xcaf0bea0,
			0xcaf1bea1,
			0xcaf2bea2,
			0xcaf3bea3,
			0xcaf4bea4,
			0xcaf5bea5
		पूर्ण,
		अणु
			__NR_निकास_group,
			0,
			0xfac1c0d1,
			0xfac2c0d2,
			0xfac3c0d3,
			0xfac4c0d4,
			0xfac5c0d5
		पूर्ण
	पूर्ण;
	स्थिर अचिन्हित दीर्घ *exp_args;

	pid_t pid = विभाजन();

	ASSERT_LE(0, pid) अणु
		TH_LOG("fork: %m");
	पूर्ण

	अगर (pid == 0) अणु
		/* get the pid beक्रमe PTRACE_TRACEME */
		pid = getpid();
		ASSERT_EQ(0, sys_ptrace(PTRACE_TRACEME, 0, 0, 0)) अणु
			TH_LOG("PTRACE_TRACEME: %m");
		पूर्ण
		ASSERT_EQ(0, समाप्त(pid, SIGSTOP)) अणु
			/* cannot happen */
			TH_LOG("kill SIGSTOP: %m");
		पूर्ण
		क्रम (अचिन्हित पूर्णांक i = 0; i < ARRAY_SIZE(args); ++i) अणु
			syscall(args[i][0],
				args[i][1], args[i][2], args[i][3],
				args[i][4], args[i][5], args[i][6]);
		पूर्ण
		/* unreachable */
		_निकास(1);
	पूर्ण

	स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक is_error;
		पूर्णांक rval;
	पूर्ण *exp_param, निकास_param[] = अणु
		अणु 1, -ENOENT पूर्ण,	/* स_बदलो */
		अणु 0, pid पूर्ण	/* gettid */
	पूर्ण;

	अचिन्हित पूर्णांक ptrace_stop;

	क्रम (ptrace_stop = 0; ; ++ptrace_stop) अणु
		काष्ठा ptrace_syscall_info info = अणु
			.op = 0xff	/* invalid PTRACE_SYSCALL_INFO_* op */
		पूर्ण;
		स्थिर माप_प्रकार size = माप(info);
		स्थिर पूर्णांक expected_none_size =
			(व्योम *) &info.entry - (व्योम *) &info;
		स्थिर पूर्णांक expected_entry_size =
			(व्योम *) &info.entry.args[6] - (व्योम *) &info;
		स्थिर पूर्णांक expected_निकास_size =
			(व्योम *) (&info.निकास.is_error + 1) -
			(व्योम *) &info;
		पूर्णांक status;
		दीर्घ rc;

		ASSERT_EQ(pid, रुको(&status)) अणु
			/* cannot happen */
			LOG_KILL_TRACEE("wait: %m");
		पूर्ण
		अगर (WIFEXITED(status)) अणु
			pid = 0;	/* the tracee is no more */
			ASSERT_EQ(0, WEXITSTATUS(status));
			अवरोध;
		पूर्ण
		ASSERT_FALSE(WIFSIGNALED(status)) अणु
			pid = 0;	/* the tracee is no more */
			LOG_KILL_TRACEE("unexpected signal %u",
					WTERMSIG(status));
		पूर्ण
		ASSERT_TRUE(WIFSTOPPED(status)) अणु
			/* cannot happen */
			LOG_KILL_TRACEE("unexpected wait status %#x", status);
		पूर्ण

		चयन (WSTOPSIG(status)) अणु
		हाल SIGSTOP:
			ASSERT_EQ(0, ptrace_stop) अणु
				LOG_KILL_TRACEE("unexpected signal stop");
			पूर्ण
			ASSERT_EQ(0, sys_ptrace(PTRACE_SETOPTIONS, pid, 0,
						PTRACE_O_TRACESYSGOOD)) अणु
				LOG_KILL_TRACEE("PTRACE_SETOPTIONS: %m");
			पूर्ण
			ASSERT_LT(0, (rc = sys_ptrace(PTRACE_GET_SYSCALL_INFO,
						      pid, size,
						      (अचिन्हित दीर्घ) &info))) अणु
				LOG_KILL_TRACEE("PTRACE_GET_SYSCALL_INFO: %m");
			पूर्ण
			ASSERT_EQ(expected_none_size, rc) अणु
				LOG_KILL_TRACEE("signal stop mismatch");
			पूर्ण
			ASSERT_EQ(PTRACE_SYSCALL_INFO_NONE, info.op) अणु
				LOG_KILL_TRACEE("signal stop mismatch");
			पूर्ण
			ASSERT_TRUE(info.arch) अणु
				LOG_KILL_TRACEE("signal stop mismatch");
			पूर्ण
			ASSERT_TRUE(info.inकाष्ठाion_poपूर्णांकer) अणु
				LOG_KILL_TRACEE("signal stop mismatch");
			पूर्ण
			ASSERT_TRUE(info.stack_poपूर्णांकer) अणु
				LOG_KILL_TRACEE("signal stop mismatch");
			पूर्ण
			अवरोध;

		हाल SIGTRAP | 0x80:
			ASSERT_LT(0, (rc = sys_ptrace(PTRACE_GET_SYSCALL_INFO,
						      pid, size,
						      (अचिन्हित दीर्घ) &info))) अणु
				LOG_KILL_TRACEE("PTRACE_GET_SYSCALL_INFO: %m");
			पूर्ण
			चयन (ptrace_stop) अणु
			हाल 1: /* entering स_बदलो */
			हाल 3: /* entering gettid */
			हाल 5: /* entering निकास_group */
				exp_args = args[ptrace_stop / 2];
				ASSERT_EQ(expected_entry_size, rc) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_EQ(PTRACE_SYSCALL_INFO_ENTRY, info.op) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_TRUE(info.arch) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_TRUE(info.inकाष्ठाion_poपूर्णांकer) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_TRUE(info.stack_poपूर्णांकer) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_args[0], info.entry.nr) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_args[1], info.entry.args[0]) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_args[2], info.entry.args[1]) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_args[3], info.entry.args[2]) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_args[4], info.entry.args[3]) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_args[5], info.entry.args[4]) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_args[6], info.entry.args[5]) अणु
					LOG_KILL_TRACEE("entry stop mismatch");
				पूर्ण
				अवरोध;
			हाल 2: /* निकासing स_बदलो */
			हाल 4: /* निकासing gettid */
				exp_param = &निकास_param[ptrace_stop / 2 - 1];
				ASSERT_EQ(expected_निकास_size, rc) अणु
					LOG_KILL_TRACEE("exit stop mismatch");
				पूर्ण
				ASSERT_EQ(PTRACE_SYSCALL_INFO_EXIT, info.op) अणु
					LOG_KILL_TRACEE("exit stop mismatch");
				पूर्ण
				ASSERT_TRUE(info.arch) अणु
					LOG_KILL_TRACEE("exit stop mismatch");
				पूर्ण
				ASSERT_TRUE(info.inकाष्ठाion_poपूर्णांकer) अणु
					LOG_KILL_TRACEE("exit stop mismatch");
				पूर्ण
				ASSERT_TRUE(info.stack_poपूर्णांकer) अणु
					LOG_KILL_TRACEE("exit stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_param->is_error,
					  info.निकास.is_error) अणु
					LOG_KILL_TRACEE("exit stop mismatch");
				पूर्ण
				ASSERT_EQ(exp_param->rval, info.निकास.rval) अणु
					LOG_KILL_TRACEE("exit stop mismatch");
				पूर्ण
				अवरोध;
			शेष:
				LOG_KILL_TRACEE("unexpected syscall stop");
				पात();
			पूर्ण
			अवरोध;

		शेष:
			LOG_KILL_TRACEE("unexpected stop signal %#x",
					WSTOPSIG(status));
			पात();
		पूर्ण

		ASSERT_EQ(0, sys_ptrace(PTRACE_SYSCALL, pid, 0, 0)) अणु
			LOG_KILL_TRACEE("PTRACE_SYSCALL: %m");
		पूर्ण
	पूर्ण

	ASSERT_EQ(ARRAY_SIZE(args) * 2, ptrace_stop);
पूर्ण

TEST_HARNESS_MAIN

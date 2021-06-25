<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Google, Inc.
 */

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समयrfd.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>

#समावेश "../kselftest.h"

व्योम child(पूर्णांक cpu)
अणु
	cpu_set_t set;

	CPU_ZERO(&set);
	CPU_SET(cpu, &set);
	अगर (sched_setaffinity(0, माप(set), &set) != 0) अणु
		ksft_prपूर्णांक_msg("sched_setaffinity() failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
		_निकास(1);
	पूर्ण

	अगर (ptrace(PTRACE_TRACEME, 0, शून्य, शून्य) != 0) अणु
		ksft_prपूर्णांक_msg("ptrace(PTRACE_TRACEME) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
		_निकास(1);
	पूर्ण

	अगर (उठाओ(SIGSTOP) != 0) अणु
		ksft_prपूर्णांक_msg("raise(SIGSTOP) failed: %s\n", म_त्रुटि(त्रुटि_सं));
		_निकास(1);
	पूर्ण

	_निकास(0);
पूर्ण

पूर्णांक run_test(पूर्णांक cpu)
अणु
	पूर्णांक status;
	pid_t pid = विभाजन();
	pid_t wpid;

	अगर (pid < 0) अणु
		ksft_prपूर्णांक_msg("fork() failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण
	अगर (pid == 0)
		child(cpu);

	wpid = रुकोpid(pid, &status, __WALL);
	अगर (wpid != pid) अणु
		ksft_prपूर्णांक_msg("waitpid() failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण
	अगर (!WIFSTOPPED(status)) अणु
		ksft_prपूर्णांक_msg("child did not stop: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण
	अगर (WSTOPSIG(status) != SIGSTOP) अणु
		ksft_prपूर्णांक_msg("child did not stop with SIGSTOP: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण

	अगर (ptrace(PTRACE_SINGLESTEP, pid, शून्य, शून्य) < 0) अणु
		अगर (त्रुटि_सं == EIO) अणु
			ksft_prपूर्णांक_msg(
				"ptrace(PTRACE_SINGLESTEP) not supported on this architecture: %s\n",
				म_त्रुटि(त्रुटि_सं));
			वापस KSFT_SKIP;
		पूर्ण
		ksft_prपूर्णांक_msg("ptrace(PTRACE_SINGLESTEP) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण

	wpid = रुकोpid(pid, &status, __WALL);
	अगर (wpid != pid) अणु
		ksft_prपूर्णांक_msg("waitpid() failed: $s\n", म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण
	अगर (WIFEXITED(status)) अणु
		ksft_prपूर्णांक_msg("child did not single-step: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण
	अगर (!WIFSTOPPED(status)) अणु
		ksft_prपूर्णांक_msg("child did not stop: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण
	अगर (WSTOPSIG(status) != SIGTRAP) अणु
		ksft_prपूर्णांक_msg("child did not stop with SIGTRAP: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण

	अगर (ptrace(PTRACE_CONT, pid, शून्य, शून्य) < 0) अणु
		ksft_prपूर्णांक_msg("ptrace(PTRACE_CONT) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण

	wpid = रुकोpid(pid, &status, __WALL);
	अगर (wpid != pid) अणु
		ksft_prपूर्णांक_msg("waitpid() failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण
	अगर (!WIFEXITED(status)) अणु
		ksft_prपूर्णांक_msg("child did not exit after PTRACE_CONT: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस KSFT_FAIL;
	पूर्ण

	वापस KSFT_PASS;
पूर्ण

व्योम suspend(व्योम)
अणु
	पूर्णांक घातer_state_fd;
	काष्ठा sigevent event = अणुपूर्ण;
	पूर्णांक समयrfd;
	पूर्णांक err;
	काष्ठा iसमयrspec spec = अणुपूर्ण;

	अगर (getuid() != 0)
		ksft_निकास_skip("Please run the test as root - Exiting.\n");

	घातer_state_fd = खोलो("/sys/power/state", O_RDWR);
	अगर (घातer_state_fd < 0)
		ksft_निकास_fail_msg(
			"open(\"/sys/power/state\") failed %s)\n",
			म_त्रुटि(त्रुटि_सं));

	समयrfd = समयrfd_create(CLOCK_BOOTTIME_ALARM, 0);
	अगर (समयrfd < 0)
		ksft_निकास_fail_msg("timerfd_create() failed\n");

	spec.it_value.tv_sec = 5;
	err = समयrfd_समय_रखो(समयrfd, 0, &spec, शून्य);
	अगर (err < 0)
		ksft_निकास_fail_msg("timerfd_settime() failed\n");

	अगर (ग_लिखो(घातer_state_fd, "mem", म_माप("mem")) != म_माप("mem"))
		ksft_निकास_fail_msg("Failed to enter Suspend state\n");

	बंद(समयrfd);
	बंद(घातer_state_fd);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt;
	bool करो_suspend = true;
	bool succeeded = true;
	अचिन्हित पूर्णांक tests = 0;
	cpu_set_t available_cpus;
	पूर्णांक err;
	पूर्णांक cpu;

	ksft_prपूर्णांक_header();

	जबतक ((opt = getopt(argc, argv, "n")) != -1) अणु
		चयन (opt) अणु
		हाल 'n':
			करो_suspend = false;
			अवरोध;
		शेष:
			म_लिखो("Usage: %s [-n]\n", argv[0]);
			म_लिखो("        -n: do not trigger a suspend/resume cycle before the test\n");
			वापस -1;
		पूर्ण
	पूर्ण

	err = sched_getaffinity(0, माप(available_cpus), &available_cpus);
	अगर (err < 0)
		ksft_निकास_fail_msg("sched_getaffinity() failed\n");

	क्रम (cpu = 0; cpu < CPU_SETSIZE; cpu++) अणु
		अगर (!CPU_ISSET(cpu, &available_cpus))
			जारी;
		tests++;
	पूर्ण

	अगर (करो_suspend)
		suspend();

	ksft_set_plan(tests);
	क्रम (cpu = 0; cpu < CPU_SETSIZE; cpu++) अणु
		पूर्णांक test_success;

		अगर (!CPU_ISSET(cpu, &available_cpus))
			जारी;

		test_success = run_test(cpu);
		चयन (test_success) अणु
		हाल KSFT_PASS:
			ksft_test_result_pass("CPU %d\n", cpu);
			अवरोध;
		हाल KSFT_SKIP:
			ksft_test_result_skip("CPU %d\n", cpu);
			अवरोध;
		हाल KSFT_FAIL:
			ksft_test_result_fail("CPU %d\n", cpu);
			succeeded = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (succeeded)
		ksft_निकास_pass();
	अन्यथा
		ksft_निकास_fail();
पूर्ण

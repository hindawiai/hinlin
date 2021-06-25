<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Google, Inc.
 *
 * Original Code by Pavel Labath <labath@google.com>
 *
 * Code modअगरied by Pratyush Anand <panand@redhat.com>
 * क्रम testing dअगरferent byte select क्रम each access size.
 */

#घोषणा _GNU_SOURCE

#समावेश <यंत्र/ptrace.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/param.h>
#समावेश <sys/uपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <elf.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>

#समावेश "../kselftest.h"

अटल अस्थिर uपूर्णांक8_t var[96] __attribute__((__aligned__(32)));

अटल व्योम child(पूर्णांक size, पूर्णांक wr)
अणु
	अस्थिर uपूर्णांक8_t *addr = &var[32 + wr];

	अगर (ptrace(PTRACE_TRACEME, 0, शून्य, शून्य) != 0) अणु
		ksft_prपूर्णांक_msg(
			"ptrace(PTRACE_TRACEME) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
		_निकास(1);
	पूर्ण

	अगर (उठाओ(SIGSTOP) != 0) अणु
		ksft_prपूर्णांक_msg(
			"raise(SIGSTOP) failed: %s\n", म_त्रुटि(त्रुटि_सं));
		_निकास(1);
	पूर्ण

	अगर ((uपूर्णांकptr_t) addr % size) अणु
		ksft_prपूर्णांक_msg(
			 "Wrong address write for the given size: %s\n",
			 म_त्रुटि(त्रुटि_सं));
		_निकास(1);
	पूर्ण

	चयन (size) अणु
	हाल 1:
		*addr = 47;
		अवरोध;
	हाल 2:
		*(uपूर्णांक16_t *)addr = 47;
		अवरोध;
	हाल 4:
		*(uपूर्णांक32_t *)addr = 47;
		अवरोध;
	हाल 8:
		*(uपूर्णांक64_t *)addr = 47;
		अवरोध;
	हाल 16:
		__यंत्र__ अस्थिर ("stp x29, x30, %0" : "=m" (addr[0]));
		अवरोध;
	हाल 32:
		__यंत्र__ अस्थिर ("stp q29, q30, %0" : "=m" (addr[0]));
		अवरोध;
	पूर्ण

	_निकास(0);
पूर्ण

अटल bool set_watchpoपूर्णांक(pid_t pid, पूर्णांक size, पूर्णांक wp)
अणु
	स्थिर अस्थिर uपूर्णांक8_t *addr = &var[32 + wp];
	स्थिर पूर्णांक offset = (uपूर्णांकptr_t)addr % 8;
	स्थिर अचिन्हित पूर्णांक byte_mask = ((1 << size) - 1) << offset;
	स्थिर अचिन्हित पूर्णांक type = 2; /* Write */
	स्थिर अचिन्हित पूर्णांक enable = 1;
	स्थिर अचिन्हित पूर्णांक control = byte_mask << 5 | type << 3 | enable;
	काष्ठा user_hwdebug_state dreg_state;
	काष्ठा iovec iov;

	स_रखो(&dreg_state, 0, माप(dreg_state));
	dreg_state.dbg_regs[0].addr = (uपूर्णांकptr_t)(addr - offset);
	dreg_state.dbg_regs[0].ctrl = control;
	iov.iov_base = &dreg_state;
	iov.iov_len = दुरत्व(काष्ठा user_hwdebug_state, dbg_regs) +
				माप(dreg_state.dbg_regs[0]);
	अगर (ptrace(PTRACE_SETREGSET, pid, NT_ARM_HW_WATCH, &iov) == 0)
		वापस true;

	अगर (त्रुटि_सं == EIO)
		ksft_prपूर्णांक_msg(
			"ptrace(PTRACE_SETREGSET, NT_ARM_HW_WATCH) not supported on this hardware: %s\n",
			म_त्रुटि(त्रुटि_सं));

	ksft_prपूर्णांक_msg(
		"ptrace(PTRACE_SETREGSET, NT_ARM_HW_WATCH) failed: %s\n",
		म_त्रुटि(त्रुटि_सं));
	वापस false;
पूर्ण

अटल bool run_test(पूर्णांक wr_size, पूर्णांक wp_size, पूर्णांक wr, पूर्णांक wp)
अणु
	पूर्णांक status;
	siginfo_t siginfo;
	pid_t pid = विभाजन();
	pid_t wpid;

	अगर (pid < 0) अणु
		ksft_test_result_fail(
			"fork() failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	अगर (pid == 0)
		child(wr_size, wr);

	wpid = रुकोpid(pid, &status, __WALL);
	अगर (wpid != pid) अणु
		ksft_prपूर्णांक_msg(
			"waitpid() failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	अगर (!WIFSTOPPED(status)) अणु
		ksft_prपूर्णांक_msg(
			"child did not stop: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	अगर (WSTOPSIG(status) != SIGSTOP) अणु
		ksft_prपूर्णांक_msg("child did not stop with SIGSTOP\n");
		वापस false;
	पूर्ण

	अगर (!set_watchpoपूर्णांक(pid, wp_size, wp))
		वापस false;

	अगर (ptrace(PTRACE_CONT, pid, शून्य, शून्य) < 0) अणु
		ksft_prपूर्णांक_msg(
			"ptrace(PTRACE_CONT) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण

	alarm(3);
	wpid = रुकोpid(pid, &status, __WALL);
	अगर (wpid != pid) अणु
		ksft_prपूर्णांक_msg(
			"waitpid() failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	alarm(0);
	अगर (WIFEXITED(status)) अणु
		ksft_prपूर्णांक_msg("child exited prematurely\n");
		वापस false;
	पूर्ण
	अगर (!WIFSTOPPED(status)) अणु
		ksft_prपूर्णांक_msg("child did not stop\n");
		वापस false;
	पूर्ण
	अगर (WSTOPSIG(status) != SIGTRAP) अणु
		ksft_prपूर्णांक_msg("child did not stop with SIGTRAP\n");
		वापस false;
	पूर्ण
	अगर (ptrace(PTRACE_GETSIGINFO, pid, शून्य, &siginfo) != 0) अणु
		ksft_prपूर्णांक_msg(
			"ptrace(PTRACE_GETSIGINFO): %s\n",
			म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	अगर (siginfo.si_code != TRAP_HWBKPT) अणु
		ksft_prपूर्णांक_msg(
			"Unexpected si_code %d\n", siginfo.si_code);
		वापस false;
	पूर्ण

	समाप्त(pid, SIGKILL);
	wpid = रुकोpid(pid, &status, 0);
	अगर (wpid != pid) अणु
		ksft_prपूर्णांक_msg(
			"waitpid() failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम sigalrm(पूर्णांक sig)
अणु
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt;
	bool succeeded = true;
	काष्ठा sigaction act;
	पूर्णांक wr, wp, size;
	bool result;

	ksft_prपूर्णांक_header();
	ksft_set_plan(213);

	act.sa_handler = sigalrm;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, शून्य);
	क्रम (size = 1; size <= 32; size = size*2) अणु
		क्रम (wr = 0; wr <= 32; wr = wr + size) अणु
			क्रम (wp = wr - size; wp <= wr + size; wp = wp + size) अणु
				result = run_test(size, MIN(size, 8), wr, wp);
				अगर ((result && wr == wp) ||
				    (!result && wr != wp))
					ksft_test_result_pass(
						"Test size = %d write offset = %d watchpoint offset = %d\n",
						size, wr, wp);
				अन्यथा अणु
					ksft_test_result_fail(
						"Test size = %d write offset = %d watchpoint offset = %d\n",
						size, wr, wp);
					succeeded = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (size = 1; size <= 32; size = size*2) अणु
		अगर (run_test(size, 8, -size, -8))
			ksft_test_result_pass(
				"Test size = %d write offset = %d watchpoint offset = -8\n",
				size, -size);
		अन्यथा अणु
			ksft_test_result_fail(
				"Test size = %d write offset = %d watchpoint offset = -8\n",
				size, -size);
			succeeded = false;
		पूर्ण
	पूर्ण

	अगर (succeeded)
		ksft_निकास_pass();
	अन्यथा
		ksft_निकास_fail();
पूर्ण

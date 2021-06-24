<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Red Hat, Inc., Frederic Weisbecker <fweisbec@redhat.com>
 *
 * Selftests क्रम अवरोधpoपूर्णांकs (and more generally the करो_debug() path) in x86.
 */


#समावेश <sys/ptrace.h>
#समावेश <unistd.h>
#समावेश <मानकघोष.स>
#समावेश <sys/user.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>

#समावेश "../kselftest.h"

#घोषणा COUNT_ISN_BPS	4
#घोषणा COUNT_WPS	4

/* Breakpoपूर्णांक access modes */
क्रमागत अणु
	BP_X = 1,
	BP_RW = 2,
	BP_W = 4,
पूर्ण;

अटल pid_t child_pid;

/*
 * Ensures the child and parent are always "talking" about
 * the same test sequence. (ie: that we haven't क्रमgotten
 * to call check_trapped() somewhere).
 */
अटल पूर्णांक nr_tests;

अटल व्योम set_अवरोधpoपूर्णांक_addr(व्योम *addr, पूर्णांक n)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_POKEUSER, child_pid,
		     दुरत्व(काष्ठा user, u_debugreg[n]), addr);
	अगर (ret)
		ksft_निकास_fail_msg("Can't set breakpoint addr: %s\n",
			म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम toggle_अवरोधpoपूर्णांक(पूर्णांक n, पूर्णांक type, पूर्णांक len,
			      पूर्णांक local, पूर्णांक global, पूर्णांक set)
अणु
	पूर्णांक ret;

	पूर्णांक xtype, xlen;
	अचिन्हित दीर्घ vdr7, dr7;

	चयन (type) अणु
	हाल BP_X:
		xtype = 0;
		अवरोध;
	हाल BP_W:
		xtype = 1;
		अवरोध;
	हाल BP_RW:
		xtype = 3;
		अवरोध;
	पूर्ण

	चयन (len) अणु
	हाल 1:
		xlen = 0;
		अवरोध;
	हाल 2:
		xlen = 4;
		अवरोध;
	हाल 4:
		xlen = 0xc;
		अवरोध;
	हाल 8:
		xlen = 8;
		अवरोध;
	पूर्ण

	dr7 = ptrace(PTRACE_PEEKUSER, child_pid,
		     दुरत्व(काष्ठा user, u_debugreg[7]), 0);

	vdr7 = (xlen | xtype) << 16;
	vdr7 <<= 4 * n;

	अगर (local) अणु
		vdr7 |= 1 << (2 * n);
		vdr7 |= 1 << 8;
	पूर्ण
	अगर (global) अणु
		vdr7 |= 2 << (2 * n);
		vdr7 |= 1 << 9;
	पूर्ण

	अगर (set)
		dr7 |= vdr7;
	अन्यथा
		dr7 &= ~vdr7;

	ret = ptrace(PTRACE_POKEUSER, child_pid,
		     दुरत्व(काष्ठा user, u_debugreg[7]), dr7);
	अगर (ret) अणु
		ksft_prपूर्णांक_msg("Can't set dr7: %s\n", म_त्रुटि(त्रुटि_सं));
		निकास(-1);
	पूर्ण
पूर्ण

/* Dummy variables to test पढ़ो/ग_लिखो accesses */
अटल अचिन्हित दीर्घ दीर्घ dummy_var[4];

/* Dummy functions to test execution accesses */
अटल व्योम dummy_func(व्योम) अणु पूर्ण
अटल व्योम dummy_func1(व्योम) अणु पूर्ण
अटल व्योम dummy_func2(व्योम) अणु पूर्ण
अटल व्योम dummy_func3(व्योम) अणु पूर्ण

अटल व्योम (*dummy_funcs[])(व्योम) = अणु
	dummy_func,
	dummy_func1,
	dummy_func2,
	dummy_func3,
पूर्ण;

अटल पूर्णांक trapped;

अटल व्योम check_trapped(व्योम)
अणु
	/*
	 * If we haven't trapped, wake up the parent
	 * so that it notices the failure.
	 */
	अगर (!trapped)
		समाप्त(getpid(), SIGUSR1);
	trapped = 0;

	nr_tests++;
पूर्ण

अटल व्योम ग_लिखो_var(पूर्णांक len)
अणु
	अक्षर *pcval; लघु *psval; पूर्णांक *pival; दीर्घ दीर्घ *plval;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		चयन (len) अणु
		हाल 1:
			pcval = (अक्षर *)&dummy_var[i];
			*pcval = 0xff;
			अवरोध;
		हाल 2:
			psval = (लघु *)&dummy_var[i];
			*psval = 0xffff;
			अवरोध;
		हाल 4:
			pival = (पूर्णांक *)&dummy_var[i];
			*pival = 0xffffffff;
			अवरोध;
		हाल 8:
			plval = (दीर्घ दीर्घ *)&dummy_var[i];
			*plval = 0xffffffffffffffffLL;
			अवरोध;
		पूर्ण
		check_trapped();
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_var(पूर्णांक len)
अणु
	अक्षर cval; लघु sval; पूर्णांक ival; दीर्घ दीर्घ lval;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		चयन (len) अणु
		हाल 1:
			cval = *(अक्षर *)&dummy_var[i];
			अवरोध;
		हाल 2:
			sval = *(लघु *)&dummy_var[i];
			अवरोध;
		हाल 4:
			ival = *(पूर्णांक *)&dummy_var[i];
			अवरोध;
		हाल 8:
			lval = *(दीर्घ दीर्घ *)&dummy_var[i];
			अवरोध;
		पूर्ण
		check_trapped();
	पूर्ण
पूर्ण

/*
 * Do the r/w/x accesses to trigger the अवरोधpoपूर्णांकs. And run
 * the usual traps.
 */
अटल व्योम trigger_tests(व्योम)
अणु
	पूर्णांक len, local, global, i;
	अक्षर val;
	पूर्णांक ret;

	ret = ptrace(PTRACE_TRACEME, 0, शून्य, 0);
	अगर (ret) अणु
		ksft_prपूर्णांक_msg("Can't be traced? %s\n", म_त्रुटि(त्रुटि_सं));
		वापस;
	पूर्ण

	/* Wake up father so that it sets up the first test */
	समाप्त(getpid(), SIGUSR1);

	/* Test inकाष्ठाion अवरोधpoपूर्णांकs */
	क्रम (local = 0; local < 2; local++) अणु
		क्रम (global = 0; global < 2; global++) अणु
			अगर (!local && !global)
				जारी;

			क्रम (i = 0; i < COUNT_ISN_BPS; i++) अणु
				dummy_funcs[i]();
				check_trapped();
			पूर्ण
		पूर्ण
	पूर्ण

	/* Test ग_लिखो watchpoपूर्णांकs */
	क्रम (len = 1; len <= माप(दीर्घ); len <<= 1) अणु
		क्रम (local = 0; local < 2; local++) अणु
			क्रम (global = 0; global < 2; global++) अणु
				अगर (!local && !global)
					जारी;
				ग_लिखो_var(len);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Test पढ़ो/ग_लिखो watchpoपूर्णांकs (on पढ़ो accesses) */
	क्रम (len = 1; len <= माप(दीर्घ); len <<= 1) अणु
		क्रम (local = 0; local < 2; local++) अणु
			क्रम (global = 0; global < 2; global++) अणु
				अगर (!local && !global)
					जारी;
				पढ़ो_var(len);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Icebp trap */
	यंत्र(".byte 0xf1\n");
	check_trapped();

	/* Int 3 trap */
	यंत्र("int $3\n");
	check_trapped();

	समाप्त(getpid(), SIGUSR1);
पूर्ण

अटल व्योम check_success(स्थिर अक्षर *msg)
अणु
	पूर्णांक child_nr_tests;
	पूर्णांक status;
	पूर्णांक ret;

	/* Wait क्रम the child to SIGTRAP */
	रुको(&status);

	ret = 0;

	अगर (WSTOPSIG(status) == SIGTRAP) अणु
		child_nr_tests = ptrace(PTRACE_PEEKDATA, child_pid,
					&nr_tests, 0);
		अगर (child_nr_tests == nr_tests)
			ret = 1;
		अगर (ptrace(PTRACE_POKEDATA, child_pid, &trapped, 1))
			ksft_निकास_fail_msg("Can't poke: %s\n", म_त्रुटि(त्रुटि_सं));
	पूर्ण

	nr_tests++;

	अगर (ret)
		ksft_test_result_pass(msg);
	अन्यथा
		ksft_test_result_fail(msg);
पूर्ण

अटल व्योम launch_inकाष्ठाion_अवरोधpoपूर्णांकs(अक्षर *buf, पूर्णांक local, पूर्णांक global)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < COUNT_ISN_BPS; i++) अणु
		set_अवरोधpoपूर्णांक_addr(dummy_funcs[i], i);
		toggle_अवरोधpoपूर्णांक(i, BP_X, 1, local, global, 1);
		ptrace(PTRACE_CONT, child_pid, शून्य, 0);
		प्र_लिखो(buf, "Test breakpoint %d with local: %d global: %d\n",
			i, local, global);
		check_success(buf);
		toggle_अवरोधpoपूर्णांक(i, BP_X, 1, local, global, 0);
	पूर्ण
पूर्ण

अटल व्योम launch_watchpoपूर्णांकs(अक्षर *buf, पूर्णांक mode, पूर्णांक len,
			       पूर्णांक local, पूर्णांक global)
अणु
	स्थिर अक्षर *mode_str;
	पूर्णांक i;

	अगर (mode == BP_W)
		mode_str = "write";
	अन्यथा
		mode_str = "read";

	क्रम (i = 0; i < COUNT_WPS; i++) अणु
		set_अवरोधpoपूर्णांक_addr(&dummy_var[i], i);
		toggle_अवरोधpoपूर्णांक(i, mode, len, local, global, 1);
		ptrace(PTRACE_CONT, child_pid, शून्य, 0);
		प्र_लिखो(buf,
			"Test %s watchpoint %d with len: %d local: %d global: %d\n",
			mode_str, i, len, local, global);
		check_success(buf);
		toggle_अवरोधpoपूर्णांक(i, mode, len, local, global, 0);
	पूर्ण
पूर्ण

/* Set the अवरोधpoपूर्णांकs and check the child successfully trigger them */
अटल व्योम launch_tests(व्योम)
अणु
	अक्षर buf[1024];
	अचिन्हित पूर्णांक tests = 0;
	पूर्णांक len, local, global, i;

	tests += 3 * COUNT_ISN_BPS;
	tests += माप(दीर्घ) / 2 * 3 * COUNT_WPS;
	tests += माप(दीर्घ) / 2 * 3 * COUNT_WPS;
	tests += 2;
	ksft_set_plan(tests);

	/* Inकाष्ठाion अवरोधpoपूर्णांकs */
	क्रम (local = 0; local < 2; local++) अणु
		क्रम (global = 0; global < 2; global++) अणु
			अगर (!local && !global)
				जारी;
			launch_inकाष्ठाion_अवरोधpoपूर्णांकs(buf, local, global);
		पूर्ण
	पूर्ण

	/* Write watchpoपूर्णांक */
	क्रम (len = 1; len <= माप(दीर्घ); len <<= 1) अणु
		क्रम (local = 0; local < 2; local++) अणु
			क्रम (global = 0; global < 2; global++) अणु
				अगर (!local && !global)
					जारी;
				launch_watchpoपूर्णांकs(buf, BP_W, len,
						   local, global);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Read-Write watchpoपूर्णांक */
	क्रम (len = 1; len <= माप(दीर्घ); len <<= 1) अणु
		क्रम (local = 0; local < 2; local++) अणु
			क्रम (global = 0; global < 2; global++) अणु
				अगर (!local && !global)
					जारी;
				launch_watchpoपूर्णांकs(buf, BP_RW, len,
						   local, global);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Icebp traps */
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success("Test icebp\n");

	/* Int 3 traps */
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success("Test int 3 trap\n");

	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	pid_t pid;
	पूर्णांक ret;

	ksft_prपूर्णांक_header();

	pid = विभाजन();
	अगर (!pid) अणु
		trigger_tests();
		निकास(0);
	पूर्ण

	child_pid = pid;

	रुको(शून्य);

	launch_tests();

	रुको(शून्य);

	ksft_निकास_pass();
पूर्ण

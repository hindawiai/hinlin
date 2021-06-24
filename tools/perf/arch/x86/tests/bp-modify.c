<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/user.h>
#समावेश <syscall.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ptrace.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <त्रुटिसं.स>
#समावेश "debug.h"
#समावेश "tests/tests.h"
#समावेश "arch-tests.h"

अटल noअंतरभूत पूर्णांक bp_1(व्योम)
अणु
	pr_debug("in %s\n", __func__);
	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक bp_2(व्योम)
अणु
	pr_debug("in %s\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक spawn_child(व्योम)
अणु
	पूर्णांक child = विभाजन();

	अगर (child == 0) अणु
		/*
		 * The child sets itself क्रम as tracee and
		 * रुकोs in संकेत क्रम parent to trace it,
		 * then it calls bp_1 and quits.
		 */
		पूर्णांक err = ptrace(PTRACE_TRACEME, 0, शून्य, शून्य);

		अगर (err) अणु
			pr_debug("failed to PTRACE_TRACEME\n");
			निकास(1);
		पूर्ण

		उठाओ(SIGCONT);
		bp_1();
		निकास(0);
	पूर्ण

	वापस child;
पूर्ण

/*
 * This tests creates HW अवरोधpoपूर्णांक, tries to
 * change it and checks it was properly changed.
 */
अटल पूर्णांक bp_modअगरy1(व्योम)
अणु
	pid_t child;
	पूर्णांक status;
	अचिन्हित दीर्घ rip = 0, dr7 = 1;

	child = spawn_child();

	रुकोpid(child, &status, 0);
	अगर (WIFEXITED(status)) अणु
		pr_debug("tracee exited prematurely 1\n");
		वापस TEST_FAIL;
	पूर्ण

	/*
	 * The parent करोes following steps:
	 *  - creates a new अवरोधpoपूर्णांक (id 0) क्रम bp_2 function
	 *  - changes that अवरोधpoपूर्णांक to bp_1 function
	 *  - रुकोs क्रम the अवरोधpoपूर्णांक to hit and checks
	 *    it has proper rip of bp_1 function
	 *  - detaches the child
	 */
	अगर (ptrace(PTRACE_POKEUSER, child,
		   दुरत्व(काष्ठा user, u_debugreg[0]), bp_2)) अणु
		pr_debug("failed to set breakpoint, 1st time: %s\n",
			 म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	अगर (ptrace(PTRACE_POKEUSER, child,
		   दुरत्व(काष्ठा user, u_debugreg[0]), bp_1)) अणु
		pr_debug("failed to set breakpoint, 2nd time: %s\n",
			 म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	अगर (ptrace(PTRACE_POKEUSER, child,
		   दुरत्व(काष्ठा user, u_debugreg[7]), dr7)) अणु
		pr_debug("failed to set dr7: %s\n", म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	अगर (ptrace(PTRACE_CONT, child, शून्य, शून्य)) अणु
		pr_debug("failed to PTRACE_CONT: %s\n", म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	रुकोpid(child, &status, 0);
	अगर (WIFEXITED(status)) अणु
		pr_debug("tracee exited prematurely 2\n");
		वापस TEST_FAIL;
	पूर्ण

	rip = ptrace(PTRACE_PEEKUSER, child,
		     दुरत्व(काष्ठा user_regs_काष्ठा, rip), शून्य);
	अगर (rip == (अचिन्हित दीर्घ) -1) अणु
		pr_debug("failed to PTRACE_PEEKUSER: %s\n",
			 म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	pr_debug("rip %lx, bp_1 %p\n", rip, bp_1);

out:
	अगर (ptrace(PTRACE_DETACH, child, शून्य, शून्य)) अणु
		pr_debug("failed to PTRACE_DETACH: %s", म_त्रुटि(त्रुटि_सं));
		वापस TEST_FAIL;
	पूर्ण

	वापस rip == (अचिन्हित दीर्घ) bp_1 ? TEST_OK : TEST_FAIL;
पूर्ण

/*
 * This tests creates HW अवरोधpoपूर्णांक, tries to
 * change it to bogus value and checks the original
 * अवरोधpoपूर्णांक is hit.
 */
अटल पूर्णांक bp_modअगरy2(व्योम)
अणु
	pid_t child;
	पूर्णांक status;
	अचिन्हित दीर्घ rip = 0, dr7 = 1;

	child = spawn_child();

	रुकोpid(child, &status, 0);
	अगर (WIFEXITED(status)) अणु
		pr_debug("tracee exited prematurely 1\n");
		वापस TEST_FAIL;
	पूर्ण

	/*
	 * The parent करोes following steps:
	 *  - creates a new अवरोधpoपूर्णांक (id 0) क्रम bp_1 function
	 *  - tries to change that अवरोधpoपूर्णांक to (-1) address
	 *  - रुकोs क्रम the अवरोधpoपूर्णांक to hit and checks
	 *    it has proper rip of bp_1 function
	 *  - detaches the child
	 */
	अगर (ptrace(PTRACE_POKEUSER, child,
		   दुरत्व(काष्ठा user, u_debugreg[0]), bp_1)) अणु
		pr_debug("failed to set breakpoint: %s\n",
			 म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	अगर (ptrace(PTRACE_POKEUSER, child,
		   दुरत्व(काष्ठा user, u_debugreg[7]), dr7)) अणु
		pr_debug("failed to set dr7: %s\n", म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	अगर (!ptrace(PTRACE_POKEUSER, child,
		   दुरत्व(काष्ठा user, u_debugreg[0]), (अचिन्हित दीर्घ) (-1))) अणु
		pr_debug("failed, breakpoint set to bogus address\n");
		जाओ out;
	पूर्ण

	अगर (ptrace(PTRACE_CONT, child, शून्य, शून्य)) अणु
		pr_debug("failed to PTRACE_CONT: %s\n", म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	रुकोpid(child, &status, 0);
	अगर (WIFEXITED(status)) अणु
		pr_debug("tracee exited prematurely 2\n");
		वापस TEST_FAIL;
	पूर्ण

	rip = ptrace(PTRACE_PEEKUSER, child,
		     दुरत्व(काष्ठा user_regs_काष्ठा, rip), शून्य);
	अगर (rip == (अचिन्हित दीर्घ) -1) अणु
		pr_debug("failed to PTRACE_PEEKUSER: %s\n",
			 म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	pr_debug("rip %lx, bp_1 %p\n", rip, bp_1);

out:
	अगर (ptrace(PTRACE_DETACH, child, शून्य, शून्य)) अणु
		pr_debug("failed to PTRACE_DETACH: %s", म_त्रुटि(त्रुटि_सं));
		वापस TEST_FAIL;
	पूर्ण

	वापस rip == (अचिन्हित दीर्घ) bp_1 ? TEST_OK : TEST_FAIL;
पूर्ण

पूर्णांक test__bp_modअगरy(काष्ठा test *test __maybe_unused,
		    पूर्णांक subtest __maybe_unused)
अणु
	TEST_ASSERT_VAL("modify test 1 failed\n", !bp_modअगरy1());
	TEST_ASSERT_VAL("modify test 2 failed\n", !bp_modअगरy2());

	वापस 0;
पूर्ण

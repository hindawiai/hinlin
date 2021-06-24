<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <संकेत.स>
#समावेश <मानककोष.स>

#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "perf-hooks.h"

अटल व्योम sigsegv_handler(पूर्णांक sig __maybe_unused)
अणु
	pr_debug("SIGSEGV is observed as expected, try to recover.\n");
	perf_hooks__recover();
	संकेत(संक_अंश, संक_पूर्व);
	उठाओ(संक_अंश);
	निकास(-1);
पूर्ण


अटल व्योम the_hook(व्योम *_hook_flags)
अणु
	पूर्णांक *hook_flags = _hook_flags;

	*hook_flags = 1234;

	/* Generate a segfault, test perf_hooks__recover */
	उठाओ(संक_अंश);
पूर्ण

पूर्णांक test__perf_hooks(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक hook_flags = 0;

	संकेत(संक_अंश, sigsegv_handler);
	perf_hooks__set_hook("test", the_hook, &hook_flags);
	perf_hooks__invoke_test();

	/* hook is triggered? */
	अगर (hook_flags != 1234) अणु
		pr_debug("Setting failed: %d (%p)\n", hook_flags, &hook_flags);
		वापस TEST_FAIL;
	पूर्ण

	/* the buggy hook is हटाओd? */
	अगर (perf_hooks__get_hook("test"))
		वापस TEST_FAIL;
	वापस TEST_OK;
पूर्ण

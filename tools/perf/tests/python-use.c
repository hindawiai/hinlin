<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Just test अगर we can load the python binding.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/compiler.h>
#समावेश "tests.h"
#समावेश "util/debug.h"

पूर्णांक test__python_use(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	अक्षर *cmd;
	पूर्णांक ret;

	अगर (aप्र_लिखो(&cmd, "echo \"import sys ; sys.path.append('%s'); import perf\" | %s %s",
		     PYTHONPATH, PYTHON, verbose > 0 ? "" : "2> /dev/null") < 0)
		वापस -1;

	pr_debug("python usage test: \"%s\"\n", cmd);
	ret = प्रणाली(cmd) ? -1 : 0;
	मुक्त(cmd);
	वापस ret;
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016, Cyril Bur, IBM Corp.
 *
 * Syscalls can be perक्रमmed provided the transactions are suspended.
 * The exec() class of syscall is unique as a new process is loaded.
 *
 * It makes little sense क्रम after an exec() call क्रम the previously
 * suspended transaction to still exist.
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <libgen.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश "utils.h"
#समावेश "tm.h"

अटल अक्षर *path;

अटल पूर्णांक test_exec(व्योम)
अणु
	SKIP_IF(!have_hपंचांग());

	यंत्र __अस्थिर__(
		"tbegin.;"
		"blt    1f; "
		"tsuspend.;"
		"1: ;"
		: : : "memory");

	execl(path, "tm-exec", "--child", शून्य);

	/* Shouldn't get here */
	लिखो_त्रुटि("execl() failed");
	वापस 1;
पूर्ण

अटल पूर्णांक after_exec(व्योम)
अणु
	यंत्र __अस्थिर__(
		"tbegin.;"
		"blt    1f;"
		"tsuspend.;"
		"1: ;"
		: : : "memory");

	FAIL_IF(failure_is_nesting());
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	path = argv[0];

	अगर (argc > 1 && म_भेद(argv[1], "--child") == 0)
		वापस after_exec();

	वापस test_harness(test_exec, "tm_exec");
पूर्ण

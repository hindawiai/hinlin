<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015, Michael Ellerman, IBM Corp.
 *
 * This test simply tests that certain syscalls are implemented. It करोesn't
 * actually exercise their logic in any way.
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>

#समावेश "utils.h"


#घोषणा DO_TEST(_name, _num)	\
अटल पूर्णांक test_##_name(व्योम)			\
अणु						\
	पूर्णांक rc;					\
	म_लिखो("Testing " #_name);		\
	त्रुटि_सं = 0;				\
	rc = syscall(_num, -1, 0, 0, 0, 0, 0);	\
	म_लिखो("\treturned %d, errno %d\n", rc, त्रुटि_सं); \
	वापस त्रुटि_सं == ENOSYS;			\
पूर्ण

#समावेश "ipc.h"
#अघोषित DO_TEST

अटल पूर्णांक ipc_unmuxed(व्योम)
अणु
	पूर्णांक tests_करोne = 0;

#घोषणा DO_TEST(_name, _num)		\
	FAIL_IF(test_##_name());	\
	tests_करोne++;

#समावेश "ipc.h"
#अघोषित DO_TEST

	/*
	 * If we ran no tests then it means none of the syscall numbers were
	 * defined, possibly because we were built against old headers. But it
	 * means we didn't really test anything, so instead of passing mark it
	 * as a skip to give the user a clue.
	 */
	SKIP_IF(tests_करोne == 0);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(ipc_unmuxed, "ipc_unmuxed");
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Michael Neuling, IBM Corp.
 *
 * Edited: Rashmica Gupta, Nov 2015
 *
 * This test करोes a विभाजन syscall inside a transaction. Basic snअगरf test
 * to see अगर we can enter the kernel during a transaction.
 */

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश "utils.h"
#समावेश "tm.h"

पूर्णांक test_विभाजन(व्योम)
अणु
	SKIP_IF(!have_hपंचांग());

	यंत्र __अस्थिर__(
		"tbegin.;"
		"blt    1f; "
		"li     0, 2;"  /* विभाजन syscall */
		"sc  ;"
		"tend.;"
		"1: ;"
		: : : "memory", "r0");
	/* If we reach here, we've passed.  Otherwise we've probably crashed
	 * the kernel */

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(test_विभाजन, "tm_fork");
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Michael Neuling, IBM Corp.
 * Original: Michael Neuling 19/7/2013
 * Edited: Rashmica Gupta 01/12/2015
 *
 * Do some transactions, see अगर the tar is corrupted.
 * If the transaction is पातed, the TAR should be rolled back to the
 * checkpoपूर्णांकed value beक्रमe the transaction began. The value written to
 * TAR in suspended mode should only reमुख्य in TAR अगर the transaction
 * completes.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>

#समावेश "tm.h"
#समावेश "utils.h"

पूर्णांक	num_loops	= 10000;

पूर्णांक test_tar(व्योम)
अणु
	पूर्णांक i;

	SKIP_IF(!have_hपंचांग());
	SKIP_IF(!is_ppc64le());

	क्रम (i = 0; i < num_loops; i++)
	अणु
		uपूर्णांक64_t result = 0;
		यंत्र __अस्थिर__(
			"li	7, 1;"
			"mtspr	%[tar], 7;"	/* tar = 1 */
			"tbegin.;"
			"beq	3f;"
			"li	4, 0x7000;"	/* Loop lots, to use समय */
			"2:;"			/* Start loop */
			"li	7, 2;"
			"mtspr	%[tar], 7;"	/* tar = 2 */
			"tsuspend.;"
			"li	7, 3;"
			"mtspr	%[tar], 7;"	/* tar = 3 */
			"tresume.;"
			"subi	4, 4, 1;"
			"cmpdi	4, 0;"
			"bne	2b;"
			"tend.;"

			/* Transaction sucess! TAR should be 3 */
			"mfspr  7, %[tar];"
			"ori	%[res], 7, 4;"  // res = 3|4 = 7
			"b	4f;"

			/* Abort handler. TAR should be rolled back to 1 */
			"3:;"
			"mfspr  7, %[tar];"
			"ori	%[res], 7, 8;"	// res = 1|8 = 9
			"4:;"

			: [res]"=r"(result)
			: [tar]"i"(SPRN_TAR)
			   : "memory", "r0", "r4", "r7");

		/* If result is anything अन्यथा other than 7 or 9, the tar
		 * value must have been corrupted. */
		अगर ((result != 7) && (result != 9))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	/* A low number of iterations (eg 100) can cause a false pass */
	अगर (argc > 1) अणु
		अगर (म_भेद(argv[1], "-h") == 0) अणु
			म_लिखो("Syntax:\n\t%s [<num loops>]\n",
			       argv[0]);
			वापस 1;
		पूर्ण अन्यथा अणु
			num_loops = म_से_प(argv[1]);
		पूर्ण
	पूर्ण

	म_लिखो("Starting, %d loops\n", num_loops);

	वापस test_harness(test_tar, "tm_tar");
पूर्ण

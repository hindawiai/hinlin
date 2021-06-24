<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2019, Gustavo Romero, Michael Neuling, IBM Corp.
 *
 * This test will spawn two processes. Both will be attached to the same
 * CPU (CPU 0). The child will be in a loop writing to FP रेजिस्टर f31 and
 * VMX/VEC/Altivec रेजिस्टर vr31 a known value, called poison, calling
 * sched_yield syscall after to allow the parent to चयन on the CPU.
 * Parent will set f31 and vr31 to 1 and in a loop will check अगर f31 and
 * vr31 reमुख्य 1 as expected until a given समयout (2m). If the issue is
 * present child's poison will leak into parent's f31 or vr31 रेजिस्टरs,
 * otherwise, poison will never leak पूर्णांकo parent's f31 and vr31 रेजिस्टरs.
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <sched.h>
#समावेश <sys/types.h>
#समावेश <संकेत.स>
#समावेश <पूर्णांकtypes.h>

#समावेश "tm.h"

पूर्णांक पंचांग_poison_test(व्योम)
अणु
	पूर्णांक cpu, pid;
	cpu_set_t cpuset;
	uपूर्णांक64_t poison = 0xdeadbeefc0dec0fe;
	uपूर्णांक64_t unknown = 0;
	bool fail_fp = false;
	bool fail_vr = false;

	SKIP_IF(!have_hपंचांग());

	cpu = pick_online_cpu();
	FAIL_IF(cpu < 0);

	// Attach both Child and Parent to the same CPU
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	FAIL_IF(sched_setaffinity(0, माप(cpuset), &cpuset) != 0);

	pid = विभाजन();
	अगर (!pid) अणु
		/**
		 * child
		 */
		जबतक (1) अणु
			sched_yield();
			यंत्र (
				"mtvsrd 31, %[poison];" // f31 = poison
				"mtvsrd 63, %[poison];" // vr31 = poison

				: : [poison] "r" (poison) : );
		पूर्ण
	पूर्ण

	/**
	 * parent
	 */
	यंत्र (
		/*
		 * Set r3, r4, and f31 to known value 1 beक्रमe entering
		 * in transaction. They won't be written after that.
		 */
		"       li      3, 0x1          ;"
		"       li      4, 0x1          ;"
		"       mtvsrd  31, 4           ;"

		/*
		 * The Time Base (TB) is a 64-bit counter रेजिस्टर that is
		 * independent of the CPU घड़ी and which is incremented
		 * at a frequency of 512000000 Hz, so every 1.953125ns.
		 * So it's necessary 120s/0.000000001953125s = 61440000000
		 * increments to get a 2 minutes समयout. Below we set that
		 * value in r5 and then use r6 to track initial TB value,
		 * updating TB values in r7 at every iteration and comparing it
		 * to r6. When r7 (current) - r6 (initial) > 61440000000 we bail
		 * out since क्रम sure we spent alपढ़ोy 2 minutes in the loop.
		 * SPR 268 is the TB रेजिस्टर.
		 */
		"       lis     5, 14           ;"
		"       ori     5, 5, 19996     ;"
		"       sldi    5, 5, 16        ;" // r5 = 61440000000

		"       mfspr   6, 268          ;" // r6 (TB initial)
		"1:     mfspr   7, 268          ;" // r7 (TB current)
		"       subf    7, 6, 7         ;" // r7 - r6 > 61440000000 ?
		"       cmpd    7, 5            ;"
		"       bgt     3f              ;" // yes, निकास

		/*
		 * Main loop to check f31
		 */
		"       tbegin.                 ;" // no, try again
		"       beq     1b              ;" // restart अगर no समयout
		"       mfvsrd  3, 31           ;" // पढ़ो f31
		"       cmpd    3, 4            ;" // f31 == 1 ?
		"       bne     2f              ;" // broken :-(
		"       tabort. 3               ;" // try another transaction
		"2:     tend.                   ;" // commit transaction
		"3:     mr    %[unknown], 3     ;" // record r3

		: [unknown] "=r" (unknown)
		:
		: "cr0", "r3", "r4", "r5", "r6", "r7", "vs31"

		);

	/*
	 * On leak 'unknown' will contain 'poison' value from child,
	 * otherwise (no leak) 'unknown' will contain the same value
	 * as r3 beक्रमe entering in transactional mode, i.e. 0x1.
	 */
	fail_fp = unknown != 0x1;
	अगर (fail_fp)
		म_लिखो("Unknown value %#"PRIx64" leaked into f31!\n", unknown);
	अन्यथा
		म_लिखो("Good, no poison or leaked value into FP registers\n");

	यंत्र (
		/*
		 * Set r3, r4, and vr31 to known value 1 beक्रमe entering
		 * in transaction. They won't be written after that.
		 */
		"       li      3, 0x1          ;"
		"       li      4, 0x1          ;"
		"       mtvsrd  63, 4           ;"

		"       lis     5, 14           ;"
		"       ori     5, 5, 19996     ;"
		"       sldi    5, 5, 16        ;" // r5 = 61440000000

		"       mfspr   6, 268          ;" // r6 (TB initial)
		"1:     mfspr   7, 268          ;" // r7 (TB current)
		"       subf    7, 6, 7         ;" // r7 - r6 > 61440000000 ?
		"       cmpd    7, 5            ;"
		"       bgt     3f              ;" // yes, निकास

		/*
		 * Main loop to check vr31
		 */
		"       tbegin.                 ;" // no, try again
		"       beq     1b              ;" // restart अगर no समयout
		"       mfvsrd  3, 63           ;" // पढ़ो vr31
		"       cmpd    3, 4            ;" // vr31 == 1 ?
		"       bne     2f              ;" // broken :-(
		"       tabort. 3               ;" // try another transaction
		"2:     tend.                   ;" // commit transaction
		"3:     mr    %[unknown], 3     ;" // record r3

		: [unknown] "=r" (unknown)
		:
		: "cr0", "r3", "r4", "r5", "r6", "r7", "vs63"

		);

	/*
	 * On leak 'unknown' will contain 'poison' value from child,
	 * otherwise (no leak) 'unknown' will contain the same value
	 * as r3 beक्रमe entering in transactional mode, i.e. 0x1.
	 */
	fail_vr = unknown != 0x1;
	अगर (fail_vr)
		म_लिखो("Unknown value %#"PRIx64" leaked into vr31!\n", unknown);
	अन्यथा
		म_लिखो("Good, no poison or leaked value into VEC registers\n");

	समाप्त(pid, SIGKILL);

	वापस (fail_fp | fail_vr);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	/* Test completes in about 4m */
	test_harness_set_समयout(250);
	वापस test_harness(पंचांग_poison_test, "tm_poison_test");
पूर्ण

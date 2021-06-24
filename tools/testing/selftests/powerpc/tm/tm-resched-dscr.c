<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Test context चयनing to see अगर the DSCR SPR is correctly preserved
 * when within a transaction.
 *
 * Note: We assume that the DSCR has been left at the शेष value (0)
 * क्रम all CPUs.
 *
 * Method:
 *
 * Set a value पूर्णांकo the DSCR.
 *
 * Start a transaction, and suspend it (*).
 *
 * Hard loop checking to see अगर the transaction has become करोomed.
 *
 * Now that we *may* have been preempted, record the DSCR and TEXASR SPRS.
 *
 * If the पात was because of a context चयन, check the DSCR value.
 * Otherwise, try again.
 *
 * (*) If the transaction is not suspended we can't see the problem because
 * the transaction पात handler will restore the DSCR to it's checkpoपूर्णांकed
 * value beक्रमe we regain control.
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <निश्चित.स>
#समावेश <यंत्र/पंचांग.h>

#समावेश "utils.h"
#समावेश "tm.h"
#समावेश "../pmu/lib.h"

#घोषणा SPRN_DSCR       0x03

पूर्णांक test_body(व्योम)
अणु
	uपूर्णांक64_t rv, dscr1 = 1, dscr2, texasr;

	SKIP_IF(!have_hपंचांग());

	म_लिखो("Check DSCR TM context switch: ");
	ख_साफ(मानक_निकास);
	क्रम (;;) अणु
		यंत्र __अस्थिर__ (
			/* set a known value पूर्णांकo the DSCR */
			"ld      3, %[dscr1];"
			"mtspr   %[sprn_dscr], 3;"

			"li      %[rv], 1;"
			/* start and suspend a transaction */
			"tbegin.;"
			"beq     1f;"
			"tsuspend.;"

			/* hard loop until the transaction becomes करोomed */
			"2: ;"
			"tcheck 0;"
			"bc      4, 0, 2b;"

			/* record DSCR and TEXASR */
			"mfspr   3, %[sprn_dscr];"
			"std     3, %[dscr2];"
			"mfspr   3, %[sprn_texasr];"
			"std     3, %[texasr];"

			"tresume.;"
			"tend.;"
			"li      %[rv], 0;"
			"1: ;"
			: [rv]"=r"(rv), [dscr2]"=m"(dscr2), [texasr]"=m"(texasr)
			: [dscr1]"m"(dscr1)
			, [sprn_dscr]"i"(SPRN_DSCR), [sprn_texasr]"i"(SPRN_TEXASR)
			: "memory", "r3"
		);
		निश्चित(rv); /* make sure the transaction पातed */
		अगर ((texasr >> 56) != TM_CAUSE_RESCHED) अणु
			जारी;
		पूर्ण
		अगर (dscr2 != dscr1) अणु
			म_लिखो(" FAIL\n");
			वापस 1;
		पूर्ण अन्यथा अणु
			म_लिखो(" OK\n");
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांग_resched_dscr(व्योम)
अणु
	वापस eat_cpu(test_body);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, स्थिर अक्षर *argv[])
अणु
	वापस test_harness(पंचांग_resched_dscr, "tm_resched_dscr");
पूर्ण

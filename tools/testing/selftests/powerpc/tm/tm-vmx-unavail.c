<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017, Michael Neuling, IBM Corp.
 * Original: Breno Leitao <brenohl@br.ibm.com> &
 *           Gustavo Bueno Romero <gromero@br.ibm.com>
 * Edited: Michael Neuling
 *
 * Force VMX unavailable during a transaction and see अगर it corrupts
 * the checkpoपूर्णांकed VMX रेजिस्टर state after the पात.
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <hपंचांगपूर्णांकrin.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <pthपढ़ो.h>
#समावेश <sys/mman.h>
#समावेश <unistd.h>
#समावेश <pthपढ़ो.h>

#समावेश "tm.h"
#समावेश "utils.h"

पूर्णांक passed;

व्योम *worker(व्योम *unused)
अणु
	__पूर्णांक128 vmx0;
	uपूर्णांक64_t texasr;

	यंत्र जाओ (
		"li       3, 1;"  /* Stick non-zero value in VMX0 */
		"std      3, 0(%[vmx0_ptr]);"
		"lvx      0, 0, %[vmx0_ptr];"

		/* Wait here a bit so we get scheduled out 255 बार */
		"lis      3, 0x3fff;"
		"1: ;"
		"addi     3, 3, -1;"
		"cmpdi    3, 0;"
		"bne      1b;"

		/* Kernel will hopefully turn VMX off now */

		"tbegin. ;"
		"beq      failure;"

		/* Cause VMX unavail. Any VMX inकाष्ठाion */
		"vaddcuw  0,0,0;"

		"tend. ;"
		"b        %l[success];"

		/* Check VMX0 sanity after पात */
		"failure: ;"
		"lvx       1,  0, %[vmx0_ptr];"
		"vcmpequb. 2,  0, 1;"
		"bc        4, 24, %l[value_mismatch];"
		"b        %l[value_match];"
		:
		: [vmx0_ptr] "r"(&vmx0)
		: "r3"
		: success, value_match, value_mismatch
		);

	/* HTM पातed and VMX0 is corrupted */
value_mismatch:
	texasr = __builtin_get_texasr();

	म_लिखो("\n\n==============\n\n");
	म_लिखो("Failure with error: %lx\n",   _TEXASR_FAILURE_CODE(texasr));
	म_लिखो("Summary error     : %lx\n",   _TEXASR_FAILURE_SUMMARY(texasr));
	म_लिखो("TFIAR exact       : %lx\n\n", _TEXASR_TFIAR_EXACT(texasr));

	passed = 0;
	वापस शून्य;

	/* HTM पातed but VMX0 is correct */
value_match:
//	म_लिखो("!");
	वापस शून्य;

success:
//	म_लिखो(".");
	वापस शून्य;
पूर्ण

पूर्णांक पंचांग_vmx_unavail_test()
अणु
	पूर्णांक thपढ़ोs;
	pthपढ़ो_t *thपढ़ो;

	SKIP_IF(!have_hपंचांग());

	passed = 1;

	thपढ़ोs = sysconf(_SC_NPROCESSORS_ONLN) * 4;
	thपढ़ो = दो_स्मृति(माप(pthपढ़ो_t)*thपढ़ोs);
	अगर (!thपढ़ो)
		वापस निकास_त्रुटि;

	क्रम (uपूर्णांक64_t i = 0; i < thपढ़ोs; i++)
		pthपढ़ो_create(&thपढ़ो[i], शून्य, &worker, शून्य);

	क्रम (uपूर्णांक64_t i = 0; i < thपढ़ोs; i++)
		pthपढ़ो_join(thपढ़ो[i], शून्य);

	मुक्त(thपढ़ो);

	वापस passed ? निकास_सफल : निकास_त्रुटि;
पूर्ण


पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	वापस test_harness(पंचांग_vmx_unavail_test, "tm_vmx_unavail_test");
पूर्ण

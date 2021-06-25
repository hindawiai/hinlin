<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015-2020 ARM Limited.
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/auxv.h>
#समावेश <sys/prctl.h>
#समावेश <यंत्र/sigcontext.h>

#समावेश "../../kselftest.h"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक vq;
	पूर्णांक vl;
	अटल अचिन्हित पूर्णांक vqs[SVE_VQ_MAX];
	अचिन्हित पूर्णांक nvqs = 0;

	ksft_prपूर्णांक_header();
	ksft_set_plan(2);

	अगर (!(getauxval(AT_HWCAP) & HWCAP_SVE))
		ksft_निकास_skip("SVE not available");

	/*
	 * Enumerate up to SVE_VQ_MAX vector lengths
	 */
	क्रम (vq = SVE_VQ_MAX; vq > 0; --vq) अणु
		vl = prctl(PR_SVE_SET_VL, vq * 16);
		अगर (vl == -1)
			ksft_निकास_fail_msg("PR_SVE_SET_VL failed: %s (%d)\n",
					   म_त्रुटि(त्रुटि_सं), त्रुटि_सं);

		vl &= PR_SVE_VL_LEN_MASK;

		अगर (!sve_vl_valid(vl))
			ksft_निकास_fail_msg("VL %d invalid\n", vl);
		vq = sve_vq_from_vl(vl);

		अगर (!(nvqs < SVE_VQ_MAX))
			ksft_निकास_fail_msg("Too many VLs %u >= SVE_VQ_MAX\n",
					   nvqs);
		vqs[nvqs++] = vq;
	पूर्ण
	ksft_test_result_pass("Enumerated %d vector lengths\n", nvqs);
	ksft_test_result_pass("All vector lengths valid\n");

	/* Prपूर्णांक out the vector lengths in ascending order: */
	जबतक (nvqs--)
		ksft_prपूर्णांक_msg("%u\n", 16 * vqs[nvqs]);

	ksft_निकास_pass();
पूर्ण

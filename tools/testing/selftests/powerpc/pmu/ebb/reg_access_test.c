<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "ebb.h"


/*
 * Test basic access to the EBB regs, they should be user accessible with no
 * kernel पूर्णांकeraction required.
 */
पूर्णांक reg_access(व्योम)
अणु
	uपूर्णांक64_t val, expected;

	SKIP_IF(!ebb_is_supported());

	expected = 0x8000000100000000ull;
	mtspr(SPRN_BESCR, expected);
	val = mfspr(SPRN_BESCR);

	FAIL_IF(val != expected);

	expected = 0x0000000001000000ull;
	mtspr(SPRN_EBBHR, expected);
	val = mfspr(SPRN_EBBHR);

	FAIL_IF(val != expected);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(reg_access, "reg_access");
पूर्ण

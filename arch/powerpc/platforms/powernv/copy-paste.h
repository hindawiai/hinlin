<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016-17 IBM Corp.
 */
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/reg.h>

/*
 * Copy/paste inकाष्ठाions:
 *
 *	copy RA,RB
 *		Copy contents of address (RA) + effective_address(RB)
 *		to पूर्णांकernal copy-buffer.
 *
 *	paste RA,RB
 *		Paste contents of पूर्णांकernal copy-buffer to the address
 *		(RA) + effective_address(RB)
 */
अटल अंतरभूत पूर्णांक vas_copy(व्योम *crb, पूर्णांक offset)
अणु
	यंत्र अस्थिर(PPC_COPY(%0, %1)";"
		:
		: "b" (offset), "b" (crb)
		: "memory");

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक vas_paste(व्योम *paste_address, पूर्णांक offset)
अणु
	u32 cr;

	cr = 0;
	यंत्र अस्थिर(PPC_PASTE(%1, %2)";"
		"mfocrf %0, 0x80;"
		: "=r" (cr)
		: "b" (offset), "b" (paste_address)
		: "memory", "cr0");

	/* We mask with 0xE to ignore SO */
	वापस (cr >> CR0_SHIFT) & 0xE;
पूर्ण

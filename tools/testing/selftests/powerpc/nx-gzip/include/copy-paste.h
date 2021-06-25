<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

/* From यंत्र-compat.h */
#घोषणा __stringअगरy_in_c(...)	#__VA_ARGS__
#घोषणा stringअगरy_in_c(...)	__stringअगरy_in_c(__VA_ARGS__) " "

/*
 * Macros taken from arch/घातerpc/include/यंत्र/ppc-opcode.h and other
 * header files.
 */
#घोषणा ___PPC_RA(a)    (((a) & 0x1f) << 16)
#घोषणा ___PPC_RB(b)    (((b) & 0x1f) << 11)

#घोषणा PPC_INST_COPY                   0x7c20060c
#घोषणा PPC_INST_PASTE                  0x7c20070d

#घोषणा PPC_COPY(a, b)          stringअगरy_in_c(.दीर्घ PPC_INST_COPY | \
						___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_PASTE(a, b)         stringअगरy_in_c(.दीर्घ PPC_INST_PASTE | \
						___PPC_RA(a) | ___PPC_RB(b))
#घोषणा CR0_SHIFT	28
#घोषणा CR0_MASK	0xF
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
	__u32 cr;

	cr = 0;
	यंत्र अस्थिर(PPC_PASTE(%1, %2)";"
		"mfocrf %0, 0x80;"
		: "=r" (cr)
		: "b" (offset), "b" (paste_address)
		: "memory", "cr0");

	वापस (cr >> CR0_SHIFT) & CR0_MASK;
पूर्ण

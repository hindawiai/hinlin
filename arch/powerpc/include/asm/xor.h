<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 * Copyright (C) IBM Corporation, 2012
 *
 * Author: Anton Blanअक्षरd <anton@au.ibm.com>
 */
#अगर_अघोषित _ASM_POWERPC_XOR_H
#घोषणा _ASM_POWERPC_XOR_H

#अगर_घोषित CONFIG_ALTIVEC

#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/xor_altivec.h>

अटल काष्ठा xor_block_ढाँचा xor_block_altivec = अणु
	.name = "altivec",
	.करो_2 = xor_altivec_2,
	.करो_3 = xor_altivec_3,
	.करो_4 = xor_altivec_4,
	.करो_5 = xor_altivec_5,
पूर्ण;

#घोषणा XOR_SPEED_ALTIVEC()				\
	करो अणु						\
		अगर (cpu_has_feature(CPU_FTR_ALTIVEC))	\
			xor_speed(&xor_block_altivec);	\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा XOR_SPEED_ALTIVEC()
#पूर्ण_अगर

/* Also try the generic routines. */
#समावेश <यंत्र-generic/xor.h>

#अघोषित XOR_TRY_TEMPLATES
#घोषणा XOR_TRY_TEMPLATES				\
करो अणु							\
	xor_speed(&xor_block_8regs);			\
	xor_speed(&xor_block_8regs_p);			\
	xor_speed(&xor_block_32regs);			\
	xor_speed(&xor_block_32regs_p);			\
	XOR_SPEED_ALTIVEC();				\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_POWERPC_XOR_H */

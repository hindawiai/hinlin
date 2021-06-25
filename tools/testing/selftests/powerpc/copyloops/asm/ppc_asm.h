<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SELFTESTS_POWERPC_PPC_ASM_H
#घोषणा __SELFTESTS_POWERPC_PPC_ASM_H
#समावेश <ppc-यंत्र.h>

#घोषणा CONFIG_ALTIVEC

#घोषणा r1	1

#घोषणा R14 r14
#घोषणा R15 r15
#घोषणा R16 r16
#घोषणा R17 r17
#घोषणा R18 r18
#घोषणा R19 r19
#घोषणा R20 r20
#घोषणा R21 r21
#घोषणा R22 r22
#घोषणा R29 r29
#घोषणा R30 r30
#घोषणा R31 r31

#घोषणा STACKFRAMESIZE	256
#घोषणा STK_REG(i)	(112 + ((i)-14)*8)

#घोषणा _GLOBAL(A) FUNC_START(test_ ## A)
#घोषणा _GLOBAL_TOC(A) _GLOBAL(A)
#घोषणा _GLOBAL_TOC_KASAN(A) _GLOBAL(A)

#घोषणा PPC_MTOCRF(A, B)	mtocrf A, B

#घोषणा EX_TABLE(x, y)			\
	.section __ex_table,"a";	\
	.8byte	x, y;			\
	.previous

#घोषणा BEGIN_FTR_SECTION		.अगर test_feature
#घोषणा FTR_SECTION_ELSE		.अन्यथा
#घोषणा ALT_FTR_SECTION_END_IFCLR(x)	.endअगर
#घोषणा ALT_FTR_SECTION_END_IFSET(x)	.endअगर
#घोषणा ALT_FTR_SECTION_END(x, y)	.endअगर
#घोषणा END_FTR_SECTION_IFCLR(x)	.endअगर
#घोषणा END_FTR_SECTION_IFSET(x)	.endअगर

/* Default to taking the first of any alternative feature sections */
test_feature = 1

#पूर्ण_अगर /* __SELFTESTS_POWERPC_PPC_ASM_H */

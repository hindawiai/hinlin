<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_ASM_H
#घोषणा _PPC_ASM_H
#समावेश <ppc-यंत्र.h>

#अगर_अघोषित r1
#घोषणा r1 sp
#पूर्ण_अगर

#घोषणा _GLOBAL(A) FUNC_START(test_ ## A)
#घोषणा _GLOBAL_TOC(A) FUNC_START(test_ ## A)

#घोषणा CONFIG_ALTIVEC

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

#घोषणा BEGIN_FTR_SECTION
#घोषणा END_FTR_SECTION_IFSET(val)
#पूर्ण_अगर

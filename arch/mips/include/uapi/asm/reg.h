<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Various रेजिस्टर offset definitions क्रम debuggers, core file
 * examiners and whatnot.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1999 Ralf Baechle
 * Copyright (C) 1995, 1999 Silicon Graphics
 */
#अगर_अघोषित __UAPI_ASM_MIPS_REG_H
#घोषणा __UAPI_ASM_MIPS_REG_H

#घोषणा MIPS32_EF_R0		6
#घोषणा MIPS32_EF_R1		7
#घोषणा MIPS32_EF_R2		8
#घोषणा MIPS32_EF_R3		9
#घोषणा MIPS32_EF_R4		10
#घोषणा MIPS32_EF_R5		11
#घोषणा MIPS32_EF_R6		12
#घोषणा MIPS32_EF_R7		13
#घोषणा MIPS32_EF_R8		14
#घोषणा MIPS32_EF_R9		15
#घोषणा MIPS32_EF_R10		16
#घोषणा MIPS32_EF_R11		17
#घोषणा MIPS32_EF_R12		18
#घोषणा MIPS32_EF_R13		19
#घोषणा MIPS32_EF_R14		20
#घोषणा MIPS32_EF_R15		21
#घोषणा MIPS32_EF_R16		22
#घोषणा MIPS32_EF_R17		23
#घोषणा MIPS32_EF_R18		24
#घोषणा MIPS32_EF_R19		25
#घोषणा MIPS32_EF_R20		26
#घोषणा MIPS32_EF_R21		27
#घोषणा MIPS32_EF_R22		28
#घोषणा MIPS32_EF_R23		29
#घोषणा MIPS32_EF_R24		30
#घोषणा MIPS32_EF_R25		31

/*
 * k0/k1 unsaved
 */
#घोषणा MIPS32_EF_R26		32
#घोषणा MIPS32_EF_R27		33

#घोषणा MIPS32_EF_R28		34
#घोषणा MIPS32_EF_R29		35
#घोषणा MIPS32_EF_R30		36
#घोषणा MIPS32_EF_R31		37

/*
 * Saved special रेजिस्टरs
 */
#घोषणा MIPS32_EF_LO		38
#घोषणा MIPS32_EF_HI		39

#घोषणा MIPS32_EF_CP0_EPC	40
#घोषणा MIPS32_EF_CP0_BADVADDR	41
#घोषणा MIPS32_EF_CP0_STATUS	42
#घोषणा MIPS32_EF_CP0_CAUSE	43
#घोषणा MIPS32_EF_UNUSED0	44

#घोषणा MIPS32_EF_SIZE		180

#घोषणा MIPS64_EF_R0		0
#घोषणा MIPS64_EF_R1		1
#घोषणा MIPS64_EF_R2		2
#घोषणा MIPS64_EF_R3		3
#घोषणा MIPS64_EF_R4		4
#घोषणा MIPS64_EF_R5		5
#घोषणा MIPS64_EF_R6		6
#घोषणा MIPS64_EF_R7		7
#घोषणा MIPS64_EF_R8		8
#घोषणा MIPS64_EF_R9		9
#घोषणा MIPS64_EF_R10		10
#घोषणा MIPS64_EF_R11		11
#घोषणा MIPS64_EF_R12		12
#घोषणा MIPS64_EF_R13		13
#घोषणा MIPS64_EF_R14		14
#घोषणा MIPS64_EF_R15		15
#घोषणा MIPS64_EF_R16		16
#घोषणा MIPS64_EF_R17		17
#घोषणा MIPS64_EF_R18		18
#घोषणा MIPS64_EF_R19		19
#घोषणा MIPS64_EF_R20		20
#घोषणा MIPS64_EF_R21		21
#घोषणा MIPS64_EF_R22		22
#घोषणा MIPS64_EF_R23		23
#घोषणा MIPS64_EF_R24		24
#घोषणा MIPS64_EF_R25		25

/*
 * k0/k1 unsaved
 */
#घोषणा MIPS64_EF_R26		26
#घोषणा MIPS64_EF_R27		27


#घोषणा MIPS64_EF_R28		28
#घोषणा MIPS64_EF_R29		29
#घोषणा MIPS64_EF_R30		30
#घोषणा MIPS64_EF_R31		31

/*
 * Saved special रेजिस्टरs
 */
#घोषणा MIPS64_EF_LO		32
#घोषणा MIPS64_EF_HI		33

#घोषणा MIPS64_EF_CP0_EPC	34
#घोषणा MIPS64_EF_CP0_BADVADDR	35
#घोषणा MIPS64_EF_CP0_STATUS	36
#घोषणा MIPS64_EF_CP0_CAUSE	37

#घोषणा MIPS64_EF_SIZE		304	/* size in bytes */

#अगर _MIPS_SIM == _MIPS_SIM_ABI32

#घोषणा EF_R0			MIPS32_EF_R0
#घोषणा EF_R1			MIPS32_EF_R1
#घोषणा EF_R2			MIPS32_EF_R2
#घोषणा EF_R3			MIPS32_EF_R3
#घोषणा EF_R4			MIPS32_EF_R4
#घोषणा EF_R5			MIPS32_EF_R5
#घोषणा EF_R6			MIPS32_EF_R6
#घोषणा EF_R7			MIPS32_EF_R7
#घोषणा EF_R8			MIPS32_EF_R8
#घोषणा EF_R9			MIPS32_EF_R9
#घोषणा EF_R10			MIPS32_EF_R10
#घोषणा EF_R11			MIPS32_EF_R11
#घोषणा EF_R12			MIPS32_EF_R12
#घोषणा EF_R13			MIPS32_EF_R13
#घोषणा EF_R14			MIPS32_EF_R14
#घोषणा EF_R15			MIPS32_EF_R15
#घोषणा EF_R16			MIPS32_EF_R16
#घोषणा EF_R17			MIPS32_EF_R17
#घोषणा EF_R18			MIPS32_EF_R18
#घोषणा EF_R19			MIPS32_EF_R19
#घोषणा EF_R20			MIPS32_EF_R20
#घोषणा EF_R21			MIPS32_EF_R21
#घोषणा EF_R22			MIPS32_EF_R22
#घोषणा EF_R23			MIPS32_EF_R23
#घोषणा EF_R24			MIPS32_EF_R24
#घोषणा EF_R25			MIPS32_EF_R25
#घोषणा EF_R26			MIPS32_EF_R26
#घोषणा EF_R27			MIPS32_EF_R27
#घोषणा EF_R28			MIPS32_EF_R28
#घोषणा EF_R29			MIPS32_EF_R29
#घोषणा EF_R30			MIPS32_EF_R30
#घोषणा EF_R31			MIPS32_EF_R31
#घोषणा EF_LO			MIPS32_EF_LO
#घोषणा EF_HI			MIPS32_EF_HI
#घोषणा EF_CP0_EPC		MIPS32_EF_CP0_EPC
#घोषणा EF_CP0_BADVADDR		MIPS32_EF_CP0_BADVADDR
#घोषणा EF_CP0_STATUS		MIPS32_EF_CP0_STATUS
#घोषणा EF_CP0_CAUSE		MIPS32_EF_CP0_CAUSE
#घोषणा EF_UNUSED0		MIPS32_EF_UNUSED0
#घोषणा EF_SIZE			MIPS32_EF_SIZE

#या_अगर _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#घोषणा EF_R0			MIPS64_EF_R0
#घोषणा EF_R1			MIPS64_EF_R1
#घोषणा EF_R2			MIPS64_EF_R2
#घोषणा EF_R3			MIPS64_EF_R3
#घोषणा EF_R4			MIPS64_EF_R4
#घोषणा EF_R5			MIPS64_EF_R5
#घोषणा EF_R6			MIPS64_EF_R6
#घोषणा EF_R7			MIPS64_EF_R7
#घोषणा EF_R8			MIPS64_EF_R8
#घोषणा EF_R9			MIPS64_EF_R9
#घोषणा EF_R10			MIPS64_EF_R10
#घोषणा EF_R11			MIPS64_EF_R11
#घोषणा EF_R12			MIPS64_EF_R12
#घोषणा EF_R13			MIPS64_EF_R13
#घोषणा EF_R14			MIPS64_EF_R14
#घोषणा EF_R15			MIPS64_EF_R15
#घोषणा EF_R16			MIPS64_EF_R16
#घोषणा EF_R17			MIPS64_EF_R17
#घोषणा EF_R18			MIPS64_EF_R18
#घोषणा EF_R19			MIPS64_EF_R19
#घोषणा EF_R20			MIPS64_EF_R20
#घोषणा EF_R21			MIPS64_EF_R21
#घोषणा EF_R22			MIPS64_EF_R22
#घोषणा EF_R23			MIPS64_EF_R23
#घोषणा EF_R24			MIPS64_EF_R24
#घोषणा EF_R25			MIPS64_EF_R25
#घोषणा EF_R26			MIPS64_EF_R26
#घोषणा EF_R27			MIPS64_EF_R27
#घोषणा EF_R28			MIPS64_EF_R28
#घोषणा EF_R29			MIPS64_EF_R29
#घोषणा EF_R30			MIPS64_EF_R30
#घोषणा EF_R31			MIPS64_EF_R31
#घोषणा EF_LO			MIPS64_EF_LO
#घोषणा EF_HI			MIPS64_EF_HI
#घोषणा EF_CP0_EPC		MIPS64_EF_CP0_EPC
#घोषणा EF_CP0_BADVADDR		MIPS64_EF_CP0_BADVADDR
#घोषणा EF_CP0_STATUS		MIPS64_EF_CP0_STATUS
#घोषणा EF_CP0_CAUSE		MIPS64_EF_CP0_CAUSE
#घोषणा EF_SIZE			MIPS64_EF_SIZE

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#पूर्ण_अगर /* __UAPI_ASM_MIPS_REG_H */

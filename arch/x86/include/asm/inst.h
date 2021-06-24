<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generate .byte code क्रम some inकाष्ठाions not supported by old
 * binutils.
 */
#अगर_अघोषित X86_ASM_INST_H
#घोषणा X86_ASM_INST_H

#अगर_घोषित __ASSEMBLY__

#घोषणा REG_NUM_INVALID		100

#घोषणा REG_TYPE_R32		0
#घोषणा REG_TYPE_R64		1
#घोषणा REG_TYPE_INVALID	100

	.macro R32_NUM opd r32
	\opd = REG_NUM_INVALID
	.अगरc \ल32,%eax
	\opd = 0
	.endअगर
	.अगरc \ल32,%ecx
	\opd = 1
	.endअगर
	.अगरc \ल32,%edx
	\opd = 2
	.endअगर
	.अगरc \ल32,%ebx
	\opd = 3
	.endअगर
	.अगरc \ल32,%esp
	\opd = 4
	.endअगर
	.अगरc \ल32,%ebp
	\opd = 5
	.endअगर
	.अगरc \ल32,%esi
	\opd = 6
	.endअगर
	.अगरc \ल32,%edi
	\opd = 7
	.endअगर
#अगर_घोषित CONFIG_X86_64
	.अगरc \ल32,%r8d
	\opd = 8
	.endअगर
	.अगरc \ल32,%r9d
	\opd = 9
	.endअगर
	.अगरc \ल32,%r10d
	\opd = 10
	.endअगर
	.अगरc \ल32,%r11d
	\opd = 11
	.endअगर
	.अगरc \ल32,%r12d
	\opd = 12
	.endअगर
	.अगरc \ल32,%r13d
	\opd = 13
	.endअगर
	.अगरc \ल32,%r14d
	\opd = 14
	.endअगर
	.अगरc \ल32,%r15d
	\opd = 15
	.endअगर
#पूर्ण_अगर
	.endm

	.macro R64_NUM opd r64
	\opd = REG_NUM_INVALID
#अगर_घोषित CONFIG_X86_64
	.अगरc \ल64,%rax
	\opd = 0
	.endअगर
	.अगरc \ल64,%rcx
	\opd = 1
	.endअगर
	.अगरc \ल64,%rdx
	\opd = 2
	.endअगर
	.अगरc \ल64,%rbx
	\opd = 3
	.endअगर
	.अगरc \ल64,%rsp
	\opd = 4
	.endअगर
	.अगरc \ल64,%rbp
	\opd = 5
	.endअगर
	.अगरc \ल64,%rsi
	\opd = 6
	.endअगर
	.अगरc \ल64,%rdi
	\opd = 7
	.endअगर
	.अगरc \ल64,%r8
	\opd = 8
	.endअगर
	.अगरc \ल64,%r9
	\opd = 9
	.endअगर
	.अगरc \ल64,%r10
	\opd = 10
	.endअगर
	.अगरc \ल64,%r11
	\opd = 11
	.endअगर
	.अगरc \ल64,%r12
	\opd = 12
	.endअगर
	.अगरc \ल64,%r13
	\opd = 13
	.endअगर
	.अगरc \ल64,%r14
	\opd = 14
	.endअगर
	.अगरc \ल64,%r15
	\opd = 15
	.endअगर
#पूर्ण_अगर
	.endm

	.macro REG_TYPE type reg
	R32_NUM reg_type_r32 \लeg
	R64_NUM reg_type_r64 \लeg
	.अगर reg_type_r64 <> REG_NUM_INVALID
	\टype = REG_TYPE_R64
	.अन्यथाअगर reg_type_r32 <> REG_NUM_INVALID
	\टype = REG_TYPE_R32
	.अन्यथा
	\टype = REG_TYPE_INVALID
	.endअगर
	.endm

	.macro PFX_REX opd1 opd2 W=0
	.अगर ((\opd1 | \opd2) & 8) || \W
	.byte 0x40 | ((\opd1 & 8) >> 3) | ((\opd2 & 8) >> 1) | (\W << 3)
	.endअगर
	.endm

	.macro MODRM mod opd1 opd2
	.byte \mod | (\opd1 & 7) | ((\opd2 & 7) << 3)
	.endm
#पूर्ण_अगर

#पूर्ण_अगर

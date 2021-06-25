<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * opcodes-virt.h: Opcode definitions क्रम the ARM भवization extensions
 * Copyright (C) 2012  Linaro Limited
 */
#अगर_अघोषित __ASM_ARM_OPCODES_VIRT_H
#घोषणा __ASM_ARM_OPCODES_VIRT_H

#समावेश <यंत्र/opcodes.h>

#घोषणा __HVC(imm16) __inst_arm_thumb32(				\
	0xE1400070 | (((imm16) & 0xFFF0) << 4) | ((imm16) & 0x000F),	\
	0xF7E08000 | (((imm16) & 0xF000) << 4) | ((imm16) & 0x0FFF)	\
)

#घोषणा __ERET	__inst_arm_thumb32(					\
	0xE160006E,							\
	0xF3DE8F00							\
)

#घोषणा __MSR_ELR_HYP(regnum)	__inst_arm_thumb32(			\
	0xE12EF300 | regnum,						\
	0xF3808E30 | (regnum << 16)					\
)

#पूर्ण_अगर /* ! __ASM_ARM_OPCODES_VIRT_H */

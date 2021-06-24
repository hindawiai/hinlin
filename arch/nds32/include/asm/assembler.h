<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __NDS32_ASSEMBLER_H__
#घोषणा __NDS32_ASSEMBLER_H__

.macro gie_disable
	setgie.d
	dsb
.endm

.macro gie_enable
	setgie.e
	dsb
.endm

.macro gie_save oldpsw
	mfsr \oldpsw, $ir0
	setgie.d
        dsb
.endm

.macro gie_restore oldpsw
	andi \oldpsw, \oldpsw, #0x1
	beqz \oldpsw, 7001f
	setgie.e
	dsb
7001:
.endm


#घोषणा USER(insn,  reg, addr, opr)	\
9999:	insn  reg, addr, opr;		\
	.section __ex_table,"a";	\
	.align 3;			\
	.दीर्घ	9999b, 9001f;		\
	.previous

#पूर्ण_अगर /* __NDS32_ASSEMBLER_H__ */

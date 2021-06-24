<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019  Arm Limited
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */

#अगर_अघोषित ASSEMBLER_H
#घोषणा ASSEMBLER_H

#घोषणा NT_GNU_PROPERTY_TYPE_0	5
#घोषणा GNU_PROPERTY_AARCH64_FEATURE_1_AND	0xc0000000

/* Bits क्रम GNU_PROPERTY_AARCH64_FEATURE_1_BTI */
#घोषणा GNU_PROPERTY_AARCH64_FEATURE_1_BTI	(1U << 0)
#घोषणा GNU_PROPERTY_AARCH64_FEATURE_1_PAC	(1U << 1)


.macro startfn name:req
	.globl \नame
\नame:
	.macro endfn
		.size \नame, . - \नame
		.type \नame, @function
		.purgem endfn
	.endm
.endm

.macro emit_aarch64_feature_1_and
	.pushsection .note.gnu.property, "a"
	.align	3
	.दीर्घ	2f - 1f
	.दीर्घ	6f - 3f
	.दीर्घ	NT_GNU_PROPERTY_TYPE_0
1:	.string	"GNU"
2:
	.align	3
3:	.दीर्घ	GNU_PROPERTY_AARCH64_FEATURE_1_AND
	.दीर्घ	5f - 4f
4:
#अगर BTI
	.दीर्घ	GNU_PROPERTY_AARCH64_FEATURE_1_PAC | \
		GNU_PROPERTY_AARCH64_FEATURE_1_BTI
#अन्यथा
	.दीर्घ	0
#पूर्ण_अगर
5:
	.align	3
6:
	.popsection
.endm

.macro paciasp
	hपूर्णांक	0x19
.endm

.macro autiasp
	hपूर्णांक	0x1d
.endm

.macro __bti_
	hपूर्णांक	0x20
.endm

.macro __bti_c
	hपूर्णांक	0x22
.endm

.macro __bti_j
	hपूर्णांक	0x24
.endm

.macro __bti_jc
	hपूर्णांक	0x26
.endm

.macro bti what=
	__bti_\what
.endm

#पूर्ण_अगर /* ! ASSEMBLER_H */

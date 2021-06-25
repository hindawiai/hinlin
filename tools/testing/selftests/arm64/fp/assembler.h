<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (C) 2015-2019 ARM Limited.
// Original author: Dave Martin <Dave.Martin@arm.com>

#अगर_अघोषित ASSEMBLER_H
#घोषणा ASSEMBLER_H

.macro __क्रम from:req, to:req
	.अगर (\पrom) == (\टo)
		_क्रम__body %\पrom
	.अन्यथा
		__क्रम \पrom, %(\पrom) + ((\टo) - (\पrom)) / 2
		__क्रम %(\पrom) + ((\टo) - (\पrom)) / 2 + 1, \टo
	.endअगर
.endm

.macro _क्रम var:req, from:req, to:req, insn:vararg
	.macro _क्रम__body \खar:req
		.noalपंचांगacro
		\insn
		.alपंचांगacro
	.endm

	.alपंचांगacro
	__क्रम \पrom, \टo
	.noalपंचांगacro

	.purgem _क्रम__body
.endm

.macro function name
	.macro endfunction
		.type \नame, @function
		.purgem endfunction
	.endm
\नame:
.endm

.macro define_accessor name, num, insn
	.macro \नame\()_entry n
		\insn \न, 1
		ret
	.endm

function \नame
	adr	x2, .L__accessor_tbl\@
	add	x2, x2, x0, lsl #3
	br	x2

.L__accessor_tbl\@:
	_क्रम x, 0, (\नum) - 1, \नame\()_entry \ष
endfunction

	.purgem \नame\()_entry
.endm

#पूर्ण_अगर /* ! ASSEMBLER_H */

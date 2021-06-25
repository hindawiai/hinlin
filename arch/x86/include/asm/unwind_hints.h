<शैली गुरु>
#अगर_अघोषित _ASM_X86_UNWIND_HINTS_H
#घोषणा _ASM_X86_UNWIND_HINTS_H

#समावेश <linux/objtool.h>

#समावेश "orc_types.h"

#अगर_घोषित __ASSEMBLY__

.macro UNWIND_HINT_EMPTY
	UNWIND_HINT sp_reg=ORC_REG_UNDEFINED type=UNWIND_HINT_TYPE_CALL end=1
.endm

.macro UNWIND_HINT_REGS base=%rsp offset=0 indirect=0 extra=1 partial=0
	.अगर \मase == %rsp
		.अगर \indirect
			.set sp_reg, ORC_REG_SP_INसूचीECT
		.अन्यथा
			.set sp_reg, ORC_REG_SP
		.endअगर
	.अन्यथाअगर \मase == %rbp
		.set sp_reg, ORC_REG_BP
	.अन्यथाअगर \मase == %rdi
		.set sp_reg, ORC_REG_DI
	.अन्यथाअगर \मase == %rdx
		.set sp_reg, ORC_REG_DX
	.अन्यथाअगर \मase == %r10
		.set sp_reg, ORC_REG_R10
	.अन्यथा
		.error "UNWIND_HINT_REGS: bad base register"
	.endअगर

	.set sp_offset, \offset

	.अगर \partial
		.set type, UNWIND_HINT_TYPE_REGS_PARTIAL
	.अन्यथाअगर \extra == 0
		.set type, UNWIND_HINT_TYPE_REGS_PARTIAL
		.set sp_offset, \offset + (16*8)
	.अन्यथा
		.set type, UNWIND_HINT_TYPE_REGS
	.endअगर

	UNWIND_HINT sp_reg=sp_reg sp_offset=sp_offset type=type
.endm

.macro UNWIND_HINT_IRET_REGS base=%rsp offset=0
	UNWIND_HINT_REGS base=\मase offset=\offset partial=1
.endm

.macro UNWIND_HINT_FUNC
	UNWIND_HINT sp_reg=ORC_REG_SP sp_offset=8 type=UNWIND_HINT_TYPE_FUNC
.endm

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_UNWIND_HINTS_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#अगर_अघोषित _ARCH_H
#घोषणा _ARCH_H

#समावेश <stdbool.h>
#समावेश <linux/list.h>
#समावेश <objtool/objtool.h>
#समावेश <objtool/cfi.h>

क्रमागत insn_type अणु
	INSN_JUMP_CONDITIONAL,
	INSN_JUMP_UNCONDITIONAL,
	INSN_JUMP_DYNAMIC,
	INSN_JUMP_DYNAMIC_CONDITIONAL,
	INSN_CALL,
	INSN_CALL_DYNAMIC,
	INSN_RETURN,
	INSN_CONTEXT_SWITCH,
	INSN_BUG,
	INSN_NOP,
	INSN_STAC,
	INSN_CLAC,
	INSN_STD,
	INSN_CLD,
	INSN_OTHER,
पूर्ण;

क्रमागत op_dest_type अणु
	OP_DEST_REG,
	OP_DEST_REG_INसूचीECT,
	OP_DEST_MEM,
	OP_DEST_PUSH,
	OP_DEST_PUSHF,
पूर्ण;

काष्ठा op_dest अणु
	क्रमागत op_dest_type type;
	अचिन्हित अक्षर reg;
	पूर्णांक offset;
पूर्ण;

क्रमागत op_src_type अणु
	OP_SRC_REG,
	OP_SRC_REG_INसूचीECT,
	OP_SRC_CONST,
	OP_SRC_POP,
	OP_SRC_POPF,
	OP_SRC_ADD,
	OP_SRC_AND,
पूर्ण;

काष्ठा op_src अणु
	क्रमागत op_src_type type;
	अचिन्हित अक्षर reg;
	पूर्णांक offset;
पूर्ण;

काष्ठा stack_op अणु
	काष्ठा op_dest dest;
	काष्ठा op_src src;
	काष्ठा list_head list;
पूर्ण;

काष्ठा inकाष्ठाion;

व्योम arch_initial_func_cfi_state(काष्ठा cfi_init_state *state);

पूर्णांक arch_decode_inकाष्ठाion(स्थिर काष्ठा elf *elf, स्थिर काष्ठा section *sec,
			    अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक maxlen,
			    अचिन्हित पूर्णांक *len, क्रमागत insn_type *type,
			    अचिन्हित दीर्घ *immediate,
			    काष्ठा list_head *ops_list);

bool arch_callee_saved_reg(अचिन्हित अक्षर reg);

अचिन्हित दीर्घ arch_jump_destination(काष्ठा inकाष्ठाion *insn);

अचिन्हित दीर्घ arch_dest_reloc_offset(पूर्णांक addend);

स्थिर अक्षर *arch_nop_insn(पूर्णांक len);

पूर्णांक arch_decode_hपूर्णांक_reg(काष्ठा inकाष्ठाion *insn, u8 sp_reg);

bool arch_is_retpoline(काष्ठा symbol *sym);

पूर्णांक arch_reग_लिखो_retpolines(काष्ठा objtool_file *file);

#पूर्ण_अगर /* _ARCH_H */

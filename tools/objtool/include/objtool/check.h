<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#अगर_अघोषित _CHECK_H
#घोषणा _CHECK_H

#समावेश <stdbool.h>
#समावेश <objtool/cfi.h>
#समावेश <objtool/arch.h>

काष्ठा insn_state अणु
	काष्ठा cfi_state cfi;
	अचिन्हित पूर्णांक uaccess_stack;
	bool uaccess;
	bool df;
	bool noinstr;
	s8 instr;
पूर्ण;

काष्ठा alt_group अणु
	/*
	 * Poपूर्णांकer from a replacement group to the original group.  शून्य अगर it
	 * *is* the original group.
	 */
	काष्ठा alt_group *orig_group;

	/* First and last inकाष्ठाions in the group */
	काष्ठा inकाष्ठाion *first_insn, *last_insn;

	/*
	 * Byte-offset-addressed len-sized array of poपूर्णांकers to CFI काष्ठाs.
	 * This is shared with the other alt_groups in the same alternative.
	 */
	काष्ठा cfi_state **cfi;
पूर्ण;

काष्ठा inकाष्ठाion अणु
	काष्ठा list_head list;
	काष्ठा hlist_node hash;
	काष्ठा list_head call_node;
	काष्ठा list_head mcount_loc_node;
	काष्ठा section *sec;
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक len;
	क्रमागत insn_type type;
	अचिन्हित दीर्घ immediate;
	bool dead_end, ignore, ignore_alts;
	bool hपूर्णांक;
	bool retpoline_safe;
	s8 instr;
	u8 visited;
	काष्ठा alt_group *alt_group;
	काष्ठा symbol *call_dest;
	काष्ठा inकाष्ठाion *jump_dest;
	काष्ठा inकाष्ठाion *first_jump_src;
	काष्ठा reloc *jump_table;
	काष्ठा reloc *reloc;
	काष्ठा list_head alts;
	काष्ठा symbol *func;
	काष्ठा list_head stack_ops;
	काष्ठा cfi_state cfi;
पूर्ण;

अटल अंतरभूत bool is_अटल_jump(काष्ठा inकाष्ठाion *insn)
अणु
	वापस insn->type == INSN_JUMP_CONDITIONAL ||
	       insn->type == INSN_JUMP_UNCONDITIONAL;
पूर्ण

अटल अंतरभूत bool is_dynamic_jump(काष्ठा inकाष्ठाion *insn)
अणु
	वापस insn->type == INSN_JUMP_DYNAMIC ||
	       insn->type == INSN_JUMP_DYNAMIC_CONDITIONAL;
पूर्ण

अटल अंतरभूत bool is_jump(काष्ठा inकाष्ठाion *insn)
अणु
	वापस is_अटल_jump(insn) || is_dynamic_jump(insn);
पूर्ण

काष्ठा inकाष्ठाion *find_insn(काष्ठा objtool_file *file,
			      काष्ठा section *sec, अचिन्हित दीर्घ offset);

#घोषणा क्रम_each_insn(file, insn)					\
	list_क्रम_each_entry(insn, &file->insn_list, list)

#घोषणा sec_क्रम_each_insn(file, sec, insn)				\
	क्रम (insn = find_insn(file, sec, 0);				\
	     insn && &insn->list != &file->insn_list &&			\
			insn->sec == sec;				\
	     insn = list_next_entry(insn, list))

#पूर्ण_अगर /* _CHECK_H */

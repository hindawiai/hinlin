<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#अगर_अघोषित _SPECIAL_H
#घोषणा _SPECIAL_H

#समावेश <stdbool.h>
#समावेश <objtool/check.h>
#समावेश <objtool/elf.h>

#घोषणा C_JUMP_TABLE_SECTION ".rodata..c_jump_table"

काष्ठा special_alt अणु
	काष्ठा list_head list;

	bool group;
	bool skip_orig;
	bool skip_alt;
	bool jump_or_nop;

	काष्ठा section *orig_sec;
	अचिन्हित दीर्घ orig_off;

	काष्ठा section *new_sec;
	अचिन्हित दीर्घ new_off;

	अचिन्हित पूर्णांक orig_len, new_len; /* group only */
पूर्ण;

पूर्णांक special_get_alts(काष्ठा elf *elf, काष्ठा list_head *alts);

व्योम arch_handle_alternative(अचिन्हित लघु feature, काष्ठा special_alt *alt);

bool arch_support_alt_relocation(काष्ठा special_alt *special_alt,
				 काष्ठा inकाष्ठाion *insn,
				 काष्ठा reloc *reloc);
काष्ठा reloc *arch_find_चयन_table(काष्ठा objtool_file *file,
				    काष्ठा inकाष्ठाion *insn);
#पूर्ण_अगर /* _SPECIAL_H */

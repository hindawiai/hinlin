<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2020 Matt Helsley <mhelsley@vmware.com>
 */

#अगर_अघोषित _OBJTOOL_H
#घोषणा _OBJTOOL_H

#समावेश <stdbool.h>
#समावेश <linux/list.h>
#समावेश <linux/hashtable.h>

#समावेश <objtool/elf.h>

#घोषणा __weak __attribute__((weak))

काष्ठा objtool_file अणु
	काष्ठा elf *elf;
	काष्ठा list_head insn_list;
	DECLARE_HASHTABLE(insn_hash, 20);
	काष्ठा list_head retpoline_call_list;
	काष्ठा list_head अटल_call_list;
	काष्ठा list_head mcount_loc_list;
	bool ignore_unreachables, c_file, hपूर्णांकs, rodata;
पूर्ण;

काष्ठा objtool_file *objtool_खोलो_पढ़ो(स्थिर अक्षर *_objname);

पूर्णांक check(काष्ठा objtool_file *file);
पूर्णांक orc_dump(स्थिर अक्षर *objname);
पूर्णांक orc_create(काष्ठा objtool_file *file);

#पूर्ण_अगर /* _OBJTOOL_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#अगर_अघोषित _WARN_H
#घोषणा _WARN_H

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <objtool/elf.h>

बाह्य स्थिर अक्षर *objname;

अटल अंतरभूत अक्षर *offstr(काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	काष्ठा symbol *func;
	अक्षर *name, *str;
	अचिन्हित दीर्घ name_off;

	func = find_func_containing(sec, offset);
	अगर (func) अणु
		name = func->name;
		name_off = offset - func->offset;
	पूर्ण अन्यथा अणु
		name = sec->name;
		name_off = offset;
	पूर्ण

	str = दो_स्मृति(म_माप(name) + 20);

	अगर (func)
		प्र_लिखो(str, "%s()+0x%lx", name, name_off);
	अन्यथा
		प्र_लिखो(str, "%s+0x%lx", name, name_off);

	वापस str;
पूर्ण

#घोषणा WARN(क्रमmat, ...)				\
	ख_लिखो(मानक_त्रुटि,					\
		"%s: warning: objtool: " क्रमmat "\n",	\
		objname, ##__VA_ARGS__)

#घोषणा WARN_FUNC(क्रमmat, sec, offset, ...)		\
(अणु							\
	अक्षर *_str = offstr(sec, offset);		\
	WARN("%s: " क्रमmat, _str, ##__VA_ARGS__);	\
	मुक्त(_str);					\
पूर्ण)

#घोषणा BT_FUNC(क्रमmat, insn, ...)			\
(अणु							\
	काष्ठा inकाष्ठाion *_insn = (insn);		\
	अक्षर *_str = offstr(_insn->sec, _insn->offset); \
	WARN("  %s: " क्रमmat, _str, ##__VA_ARGS__);	\
	मुक्त(_str);					\
पूर्ण)

#घोषणा WARN_ELF(क्रमmat, ...)				\
	WARN(क्रमmat ": %s", ##__VA_ARGS__, elf_errmsg(-1))

#पूर्ण_अगर /* _WARN_H */

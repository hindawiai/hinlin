<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Matt Helsley <mhelsley@vmware.com>
 * Weak definitions necessary to compile objtool without
 * some subcommands (e.g. check, orc).
 */

#समावेश <stdbool.h>
#समावेश <त्रुटिसं.स>
#समावेश <objtool/objtool.h>

#घोषणा UNSUPPORTED(name)						\
(अणु									\
	ख_लिखो(मानक_त्रुटि, "error: objtool: " name " not implemented\n");	\
	वापस ENOSYS;							\
पूर्ण)

पूर्णांक __weak check(काष्ठा objtool_file *file)
अणु
	UNSUPPORTED("check subcommand");
पूर्ण

पूर्णांक __weak orc_dump(स्थिर अक्षर *_objname)
अणु
	UNSUPPORTED("orc");
पूर्ण

पूर्णांक __weak orc_create(काष्ठा objtool_file *file)
अणु
	UNSUPPORTED("orc");
पूर्ण

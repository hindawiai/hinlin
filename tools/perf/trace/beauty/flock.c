<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>
#समावेश <uapi/linux/fcntl.h>

#अगर_अघोषित LOCK_MAND
#घोषणा LOCK_MAND	 32
#पूर्ण_अगर

#अगर_अघोषित LOCK_READ
#घोषणा LOCK_READ	 64
#पूर्ण_अगर

#अगर_अघोषित LOCK_WRITE
#घोषणा LOCK_WRITE	128
#पूर्ण_अगर

#अगर_अघोषित LOCK_RW
#घोषणा LOCK_RW		192
#पूर्ण_अगर

माप_प्रकार syscall_arg__scnम_लिखो_flock(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "LOCK_";
	पूर्णांक prपूर्णांकed = 0, op = arg->val;

	अगर (op == 0)
		वापस scnम_लिखो(bf, size, "NONE");
#घोषणा	P_CMD(cmd) \
	अगर ((op & LOCK_##cmd) == LOCK_##cmd) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #cmd); \
		op &= ~LOCK_##cmd; \
	पूर्ण

	P_CMD(SH);
	P_CMD(EX);
	P_CMD(NB);
	P_CMD(UN);
	P_CMD(MAND);
	P_CMD(RW);
	P_CMD(READ);
	P_CMD(WRITE);
#अघोषित P_OP

	अगर (op)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", op);

	वापस prपूर्णांकed;
पूर्ण

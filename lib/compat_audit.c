<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/unistd32.h>

अचिन्हित compat_dir_class[] = अणु
#समावेश <यंत्र-generic/audit_dir_ग_लिखो.h>
~0U
पूर्ण;

अचिन्हित compat_पढ़ो_class[] = अणु
#समावेश <यंत्र-generic/audit_पढ़ो.h>
~0U
पूर्ण;

अचिन्हित compat_ग_लिखो_class[] = अणु
#समावेश <यंत्र-generic/audit_ग_लिखो.h>
~0U
पूर्ण;

अचिन्हित compat_chattr_class[] = अणु
#समावेश <यंत्र-generic/audit_change_attr.h>
~0U
पूर्ण;

अचिन्हित compat_संकेत_class[] = अणु
#समावेश <यंत्र-generic/audit_संकेत.स>
~0U
पूर्ण;

पूर्णांक audit_classअगरy_compat_syscall(पूर्णांक abi, अचिन्हित syscall)
अणु
	चयन (syscall) अणु
#अगर_घोषित __NR_खोलो
	हाल __NR_खोलो:
		वापस 2;
#पूर्ण_अगर
#अगर_घोषित __NR_खोलोat
	हाल __NR_खोलोat:
		वापस 3;
#पूर्ण_अगर
#अगर_घोषित __NR_socketcall
	हाल __NR_socketcall:
		वापस 4;
#पूर्ण_अगर
	हाल __NR_execve:
		वापस 5;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

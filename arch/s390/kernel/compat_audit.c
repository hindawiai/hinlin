<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अघोषित __s390x__
#समावेश <यंत्र/unistd.h>
#समावेश "audit.h"

अचिन्हित s390_dir_class[] = अणु
#समावेश <यंत्र-generic/audit_dir_ग_लिखो.h>
~0U
पूर्ण;

अचिन्हित s390_chattr_class[] = अणु
#समावेश <यंत्र-generic/audit_change_attr.h>
~0U
पूर्ण;

अचिन्हित s390_ग_लिखो_class[] = अणु
#समावेश <यंत्र-generic/audit_ग_लिखो.h>
~0U
पूर्ण;

अचिन्हित s390_पढ़ो_class[] = अणु
#समावेश <यंत्र-generic/audit_पढ़ो.h>
~0U
पूर्ण;

अचिन्हित s390_संकेत_class[] = अणु
#समावेश <यंत्र-generic/audit_संकेत.स>
~0U
पूर्ण;

पूर्णांक s390_classअगरy_syscall(अचिन्हित syscall)
अणु
	चयन(syscall) अणु
	हाल __NR_खोलो:
		वापस 2;
	हाल __NR_खोलोat:
		वापस 3;
	हाल __NR_socketcall:
		वापस 4;
	हाल __NR_execve:
		वापस 5;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

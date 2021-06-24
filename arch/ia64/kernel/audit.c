<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/audit.h>
#समावेश <यंत्र/unistd.h>

अटल अचिन्हित dir_class[] = अणु
#समावेश <यंत्र-generic/audit_dir_ग_लिखो.h>
~0U
पूर्ण;

अटल अचिन्हित पढ़ो_class[] = अणु
#समावेश <यंत्र-generic/audit_पढ़ो.h>
~0U
पूर्ण;

अटल अचिन्हित ग_लिखो_class[] = अणु
#समावेश <यंत्र-generic/audit_ग_लिखो.h>
~0U
पूर्ण;

अटल अचिन्हित chattr_class[] = अणु
#समावेश <यंत्र-generic/audit_change_attr.h>
~0U
पूर्ण;

अटल अचिन्हित संकेत_class[] = अणु
#समावेश <यंत्र-generic/audit_संकेत.स>
~0U
पूर्ण;

पूर्णांक audit_classअगरy_arch(पूर्णांक arch)
अणु
	वापस 0;
पूर्ण

पूर्णांक audit_classअगरy_syscall(पूर्णांक abi, अचिन्हित syscall)
अणु
	चयन(syscall) अणु
	हाल __NR_खोलो:
		वापस 2;
	हाल __NR_खोलोat:
		वापस 3;
	हाल __NR_execve:
		वापस 5;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक __init audit_classes_init(व्योम)
अणु
	audit_रेजिस्टर_class(AUDIT_CLASS_WRITE, ग_लिखो_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_READ, पढ़ो_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_सूची_WRITE, dir_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_CHATTR, chattr_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_SIGNAL, संकेत_class);
	वापस 0;
पूर्ण

__initcall(audit_classes_init);

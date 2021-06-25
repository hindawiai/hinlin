<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/audit.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/audit.h>

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
#अगर_घोषित CONFIG_IA32_EMULATION
	अगर (arch == AUDIT_ARCH_I386)
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक audit_classअगरy_syscall(पूर्णांक abi, अचिन्हित syscall)
अणु
#अगर_घोषित CONFIG_IA32_EMULATION
	अगर (abi == AUDIT_ARCH_I386)
		वापस ia32_classअगरy_syscall(syscall);
#पूर्ण_अगर
	चयन(syscall) अणु
	हाल __NR_खोलो:
		वापस 2;
	हाल __NR_खोलोat:
		वापस 3;
	हाल __NR_execve:
	हाल __NR_execveat:
		वापस 5;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक __init audit_classes_init(व्योम)
अणु
#अगर_घोषित CONFIG_IA32_EMULATION
	बाह्य __u32 ia32_dir_class[];
	बाह्य __u32 ia32_ग_लिखो_class[];
	बाह्य __u32 ia32_पढ़ो_class[];
	बाह्य __u32 ia32_chattr_class[];
	बाह्य __u32 ia32_संकेत_class[];
	audit_रेजिस्टर_class(AUDIT_CLASS_WRITE_32, ia32_ग_लिखो_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_READ_32, ia32_पढ़ो_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_सूची_WRITE_32, ia32_dir_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_CHATTR_32, ia32_chattr_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_SIGNAL_32, ia32_संकेत_class);
#पूर्ण_अगर
	audit_रेजिस्टर_class(AUDIT_CLASS_WRITE, ग_लिखो_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_READ, पढ़ो_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_सूची_WRITE, dir_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_CHATTR, chattr_class);
	audit_रेजिस्टर_class(AUDIT_CLASS_SIGNAL, संकेत_class);
	वापस 0;
पूर्ण

__initcall(audit_classes_init);

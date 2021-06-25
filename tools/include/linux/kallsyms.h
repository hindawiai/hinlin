<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBLOCKDEP_LINUX_KALLSYMS_H_
#घोषणा _LIBLOCKDEP_LINUX_KALLSYMS_H_

#समावेश <linux/kernel.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>

#घोषणा KSYM_NAME_LEN 128

काष्ठा module;

अटल अंतरभूत स्थिर अक्षर *kallsyms_lookup(अचिन्हित दीर्घ addr,
					  अचिन्हित दीर्घ *symbolsize,
					  अचिन्हित दीर्घ *offset,
					  अक्षर **modname, अक्षर *namebuf)
अणु
	वापस शून्य;
पूर्ण

#समावेश <execinfo.h>
#समावेश <मानककोष.स>
अटल अंतरभूत व्योम prपूर्णांक_ip_sym(स्थिर अक्षर *loglvl, अचिन्हित दीर्घ ip)
अणु
	अक्षर **name;

	name = backtrace_symbols((व्योम **)&ip, 1);

	dम_लिखो(STDOUT_खाताNO, "%s\n", *name);

	मुक्त(name);
पूर्ण

#पूर्ण_अगर

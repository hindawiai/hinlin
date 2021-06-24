<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TOOLS_KALLSYMS_H_
#घोषणा __TOOLS_KALLSYMS_H_ 1

#समावेश <elf.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/types.h>

#अगर_अघोषित KSYM_NAME_LEN
#घोषणा KSYM_NAME_LEN 256
#पूर्ण_अगर

अटल अंतरभूत u8 kallsyms2elf_binding(अक्षर type)
अणु
	अगर (type == 'W')
		वापस STB_WEAK;

	वापस है_बड़ा(type) ? STB_GLOBAL : STB_LOCAL;
पूर्ण

u8 kallsyms2elf_type(अक्षर type);

bool kallsyms__is_function(अक्षर symbol_type);

पूर्णांक kallsyms__parse(स्थिर अक्षर *filename, व्योम *arg,
		    पूर्णांक (*process_symbol)(व्योम *arg, स्थिर अक्षर *name,
					  अक्षर type, u64 start));

#पूर्ण_अगर /* __TOOLS_KALLSYMS_H_ */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_EXTABLE_H
#घोषणा _LINUX_EXTABLE_H

#समावेश <linux/मानकघोष.स>	/* क्रम शून्य */
#समावेश <linux/types.h>

काष्ठा module;
काष्ठा exception_table_entry;

स्थिर काष्ठा exception_table_entry *
search_extable(स्थिर काष्ठा exception_table_entry *base,
	       स्थिर माप_प्रकार num,
	       अचिन्हित दीर्घ value);
व्योम sort_extable(काष्ठा exception_table_entry *start,
		  काष्ठा exception_table_entry *finish);
व्योम sort_मुख्य_extable(व्योम);
व्योम trim_init_extable(काष्ठा module *m);

/* Given an address, look क्रम it in the exception tables */
स्थिर काष्ठा exception_table_entry *search_exception_tables(अचिन्हित दीर्घ add);
स्थिर काष्ठा exception_table_entry *
search_kernel_exception_table(अचिन्हित दीर्घ addr);

#अगर_घोषित CONFIG_MODULES
/* For extable.c to search modules' exception tables. */
स्थिर काष्ठा exception_table_entry *search_module_extables(अचिन्हित दीर्घ addr);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा exception_table_entry *
search_module_extables(अचिन्हित दीर्घ addr)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /*CONFIG_MODULES*/

#अगर_घोषित CONFIG_BPF_JIT
स्थिर काष्ठा exception_table_entry *search_bpf_extables(अचिन्हित दीर्घ addr);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा exception_table_entry *
search_bpf_extables(अचिन्हित दीर्घ addr)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_EXTABLE_H */

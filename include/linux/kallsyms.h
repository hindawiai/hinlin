<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Rewritten and vastly simplअगरied by Rusty Russell क्रम in-kernel
 * module loader:
 *   Copyright 2002 Rusty Russell <rusty@rustcorp.com.au> IBM Corporation
 */
#अगर_अघोषित _LINUX_KALLSYMS_H
#घोषणा _LINUX_KALLSYMS_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/sections.h>

#घोषणा KSYM_NAME_LEN 128
#घोषणा KSYM_SYMBOL_LEN (माप("%s+%#lx/%#lx [%s]") + (KSYM_NAME_LEN - 1) + \
			 2*(BITS_PER_LONG*3/10) + (MODULE_NAME_LEN - 1) + 1)

काष्ठा cred;
काष्ठा module;

अटल अंतरभूत पूर्णांक is_kernel_inittext(अचिन्हित दीर्घ addr)
अणु
	अगर (addr >= (अचिन्हित दीर्घ)_sinittext
	    && addr <= (अचिन्हित दीर्घ)_einittext)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_kernel_text(अचिन्हित दीर्घ addr)
अणु
	अगर ((addr >= (अचिन्हित दीर्घ)_stext && addr <= (अचिन्हित दीर्घ)_etext) ||
	    arch_is_kernel_text(addr))
		वापस 1;
	वापस in_gate_area_no_mm(addr);
पूर्ण

अटल अंतरभूत पूर्णांक is_kernel(अचिन्हित दीर्घ addr)
अणु
	अगर (addr >= (अचिन्हित दीर्घ)_stext && addr <= (अचिन्हित दीर्घ)_end)
		वापस 1;
	वापस in_gate_area_no_mm(addr);
पूर्ण

अटल अंतरभूत पूर्णांक is_ksym_addr(अचिन्हित दीर्घ addr)
अणु
	अगर (IS_ENABLED(CONFIG_KALLSYMS_ALL))
		वापस is_kernel(addr);

	वापस is_kernel_text(addr) || is_kernel_inittext(addr);
पूर्ण

अटल अंतरभूत व्योम *dereference_symbol_descriptor(व्योम *ptr)
अणु
#अगर_घोषित HAVE_DEREFERENCE_FUNCTION_DESCRIPTOR
	काष्ठा module *mod;

	ptr = dereference_kernel_function_descriptor(ptr);
	अगर (is_ksym_addr((अचिन्हित दीर्घ)ptr))
		वापस ptr;

	preempt_disable();
	mod = __module_address((अचिन्हित दीर्घ)ptr);
	preempt_enable();

	अगर (mod)
		ptr = dereference_module_function_descriptor(mod, ptr);
#पूर्ण_अगर
	वापस ptr;
पूर्ण

पूर्णांक kallsyms_on_each_symbol(पूर्णांक (*fn)(व्योम *, स्थिर अक्षर *, काष्ठा module *,
				      अचिन्हित दीर्घ),
			    व्योम *data);

#अगर_घोषित CONFIG_KALLSYMS
/* Lookup the address क्रम a symbol. Returns 0 अगर not found. */
अचिन्हित दीर्घ kallsyms_lookup_name(स्थिर अक्षर *name);

बाह्य पूर्णांक kallsyms_lookup_size_offset(अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ *symbolsize,
				  अचिन्हित दीर्घ *offset);

/* Lookup an address.  modname is set to शून्य अगर it's in the kernel. */
स्थिर अक्षर *kallsyms_lookup(अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ *symbolsize,
			    अचिन्हित दीर्घ *offset,
			    अक्षर **modname, अक्षर *namebuf);

/* Look up a kernel symbol and वापस it in a text buffer. */
बाह्य पूर्णांक sprपूर्णांक_symbol(अक्षर *buffer, अचिन्हित दीर्घ address);
बाह्य पूर्णांक sprपूर्णांक_symbol_no_offset(अक्षर *buffer, अचिन्हित दीर्घ address);
बाह्य पूर्णांक sprपूर्णांक_backtrace(अक्षर *buffer, अचिन्हित दीर्घ address);

पूर्णांक lookup_symbol_name(अचिन्हित दीर्घ addr, अक्षर *symname);
पूर्णांक lookup_symbol_attrs(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size, अचिन्हित दीर्घ *offset, अक्षर *modname, अक्षर *name);

/* How and when करो we show kallsyms values? */
बाह्य bool kallsyms_show_value(स्थिर काष्ठा cred *cred);

#अन्यथा /* !CONFIG_KALLSYMS */

अटल अंतरभूत अचिन्हित दीर्घ kallsyms_lookup_name(स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kallsyms_lookup_size_offset(अचिन्हित दीर्घ addr,
					      अचिन्हित दीर्घ *symbolsize,
					      अचिन्हित दीर्घ *offset)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *kallsyms_lookup(अचिन्हित दीर्घ addr,
					  अचिन्हित दीर्घ *symbolsize,
					  अचिन्हित दीर्घ *offset,
					  अक्षर **modname, अक्षर *namebuf)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक sprपूर्णांक_symbol(अक्षर *buffer, अचिन्हित दीर्घ addr)
अणु
	*buffer = '\0';
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sprपूर्णांक_symbol_no_offset(अक्षर *buffer, अचिन्हित दीर्घ addr)
अणु
	*buffer = '\0';
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sprपूर्णांक_backtrace(अक्षर *buffer, अचिन्हित दीर्घ addr)
अणु
	*buffer = '\0';
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक lookup_symbol_name(अचिन्हित दीर्घ addr, अक्षर *symname)
अणु
	वापस -दुस्फल;
पूर्ण

अटल अंतरभूत पूर्णांक lookup_symbol_attrs(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size, अचिन्हित दीर्घ *offset, अक्षर *modname, अक्षर *name)
अणु
	वापस -दुस्फल;
पूर्ण

अटल अंतरभूत bool kallsyms_show_value(स्थिर काष्ठा cred *cred)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /*CONFIG_KALLSYMS*/

अटल अंतरभूत व्योम prपूर्णांक_ip_sym(स्थिर अक्षर *loglvl, अचिन्हित दीर्घ ip)
अणु
	prपूर्णांकk("%s[<%px>] %pS\n", loglvl, (व्योम *) ip, (व्योम *) ip);
पूर्ण

#पूर्ण_अगर /*_LINUX_KALLSYMS_H*/

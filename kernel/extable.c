<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Rewritten by Rusty Russell, on the backs of many others...
   Copyright (C) 2001 Rusty Russell, 2002 Rusty Russell IBM.

*/
#समावेश <linux/ftrace.h>
#समावेश <linux/memory.h>
#समावेश <linux/extable.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/filter.h>

#समावेश <यंत्र/sections.h>
#समावेश <linux/uaccess.h>

/*
 * mutex protecting text section modअगरication (dynamic code patching).
 * some users need to sleep (allocating memory...) जबतक they hold this lock.
 *
 * Note: Also protects SMP-alternatives modअगरication on x86.
 *
 * NOT exported to modules - patching kernel text is a really delicate matter.
 */
DEFINE_MUTEX(text_mutex);

बाह्य काष्ठा exception_table_entry __start___ex_table[];
बाह्य काष्ठा exception_table_entry __stop___ex_table[];

/* Cleared by build समय tools अगर the table is alपढ़ोy sorted. */
u32 __initdata __visible मुख्य_extable_sort_needed = 1;

/* Sort the kernel's built-in exception table */
व्योम __init sort_मुख्य_extable(व्योम)
अणु
	अगर (मुख्य_extable_sort_needed &&
	    &__stop___ex_table > &__start___ex_table) अणु
		pr_notice("Sorting __ex_table...\n");
		sort_extable(__start___ex_table, __stop___ex_table);
	पूर्ण
पूर्ण

/* Given an address, look क्रम it in the kernel exception table */
स्थिर
काष्ठा exception_table_entry *search_kernel_exception_table(अचिन्हित दीर्घ addr)
अणु
	वापस search_extable(__start___ex_table,
			      __stop___ex_table - __start___ex_table, addr);
पूर्ण

/* Given an address, look क्रम it in the exception tables. */
स्थिर काष्ठा exception_table_entry *search_exception_tables(अचिन्हित दीर्घ addr)
अणु
	स्थिर काष्ठा exception_table_entry *e;

	e = search_kernel_exception_table(addr);
	अगर (!e)
		e = search_module_extables(addr);
	अगर (!e)
		e = search_bpf_extables(addr);
	वापस e;
पूर्ण

पूर्णांक init_kernel_text(अचिन्हित दीर्घ addr)
अणु
	अगर (addr >= (अचिन्हित दीर्घ)_sinittext &&
	    addr < (अचिन्हित दीर्घ)_einittext)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक notrace core_kernel_text(अचिन्हित दीर्घ addr)
अणु
	अगर (addr >= (अचिन्हित दीर्घ)_stext &&
	    addr < (अचिन्हित दीर्घ)_etext)
		वापस 1;

	अगर (प्रणाली_state < SYSTEM_RUNNING &&
	    init_kernel_text(addr))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * core_kernel_data - tell अगर addr poपूर्णांकs to kernel data
 * @addr: address to test
 *
 * Returns true अगर @addr passed in is from the core kernel data
 * section.
 *
 * Note: On some archs it may वापस true क्रम core RODATA, and false
 *  क्रम others. But will always be true क्रम core RW data.
 */
पूर्णांक core_kernel_data(अचिन्हित दीर्घ addr)
अणु
	अगर (addr >= (अचिन्हित दीर्घ)_sdata &&
	    addr < (अचिन्हित दीर्घ)_edata)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक __kernel_text_address(अचिन्हित दीर्घ addr)
अणु
	अगर (kernel_text_address(addr))
		वापस 1;
	/*
	 * There might be init symbols in saved stacktraces.
	 * Give those symbols a chance to be prपूर्णांकed in
	 * backtraces (such as lockdep traces).
	 *
	 * Since we are after the module-symbols check, there's
	 * no danger of address overlap:
	 */
	अगर (init_kernel_text(addr))
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक kernel_text_address(अचिन्हित दीर्घ addr)
अणु
	bool no_rcu;
	पूर्णांक ret = 1;

	अगर (core_kernel_text(addr))
		वापस 1;

	/*
	 * If a stack dump happens जबतक RCU is not watching, then
	 * RCU needs to be notअगरied that it requires to start
	 * watching again. This can happen either by tracing that
	 * triggers a stack trace, or a WARN() that happens during
	 * coming back from idle, or cpu on or offlining.
	 *
	 * is_module_text_address() as well as the kprobe slots,
	 * is_bpf_text_address() and is_bpf_image_address require
	 * RCU to be watching.
	 */
	no_rcu = !rcu_is_watching();

	/* Treat this like an NMI as it can happen anywhere */
	अगर (no_rcu)
		rcu_nmi_enter();

	अगर (is_module_text_address(addr))
		जाओ out;
	अगर (is_ftrace_trampoline(addr))
		जाओ out;
	अगर (is_kprobe_optinsn_slot(addr) || is_kprobe_insn_slot(addr))
		जाओ out;
	अगर (is_bpf_text_address(addr))
		जाओ out;
	ret = 0;
out:
	अगर (no_rcu)
		rcu_nmi_निकास();

	वापस ret;
पूर्ण

/*
 * On some architectures (PPC64, IA64) function poपूर्णांकers
 * are actually only tokens to some data that then holds the
 * real function address. As a result, to find अगर a function
 * poपूर्णांकer is part of the kernel text, we need to करो some
 * special dereferencing first.
 */
पूर्णांक func_ptr_is_kernel_text(व्योम *ptr)
अणु
	अचिन्हित दीर्घ addr;
	addr = (अचिन्हित दीर्घ) dereference_function_descriptor(ptr);
	अगर (core_kernel_text(addr))
		वापस 1;
	वापस is_module_text_address(addr);
पूर्ण

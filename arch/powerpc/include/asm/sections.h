<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_SECTIONS_H
#घोषणा _ASM_POWERPC_SECTIONS_H
#अगर_घोषित __KERNEL__

#समावेश <linux/elf.h>
#समावेश <linux/uaccess.h>

#घोषणा arch_is_kernel_iniपंचांगem_मुक्तd arch_is_kernel_iniपंचांगem_मुक्तd

#समावेश <यंत्र-generic/sections.h>

बाह्य bool init_mem_is_मुक्त;

अटल अंतरभूत पूर्णांक arch_is_kernel_iniपंचांगem_मुक्तd(अचिन्हित दीर्घ addr)
अणु
	अगर (!init_mem_is_मुक्त)
		वापस 0;

	वापस addr >= (अचिन्हित दीर्घ)__init_begin &&
		addr < (अचिन्हित दीर्घ)__init_end;
पूर्ण

बाह्य अक्षर __head_end[];

#अगर_घोषित __घातerpc64__

बाह्य अक्षर __start_पूर्णांकerrupts[];
बाह्य अक्षर __end_पूर्णांकerrupts[];

बाह्य अक्षर __prom_init_toc_start[];
बाह्य अक्षर __prom_init_toc_end[];

#अगर_घोषित CONFIG_PPC_POWERNV
बाह्य अक्षर start_real_trampolines[];
बाह्य अक्षर end_real_trampolines[];
बाह्य अक्षर start_virt_trampolines[];
बाह्य अक्षर end_virt_trampolines[];
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक in_kernel_text(अचिन्हित दीर्घ addr)
अणु
	अगर (addr >= (अचिन्हित दीर्घ)_stext && addr < (अचिन्हित दीर्घ)__init_end)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kernel_toc_addr(व्योम)
अणु
	/* Defined by the linker, see vmlinux.lds.S */
	बाह्य अचिन्हित दीर्घ __toc_start;

	/*
	 * The TOC रेजिस्टर (r2) poपूर्णांकs 32kB पूर्णांकo the TOC, so that 64kB of
	 * the TOC can be addressed using a single machine inकाष्ठाion.
	 */
	वापस (अचिन्हित दीर्घ)(&__toc_start) + 0x8000UL;
पूर्ण

अटल अंतरभूत पूर्णांक overlaps_पूर्णांकerrupt_vector_text(अचिन्हित दीर्घ start,
							अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ real_start, real_end;
	real_start = __start_पूर्णांकerrupts - _stext;
	real_end = __end_पूर्णांकerrupts - _stext;

	वापस start < (अचिन्हित दीर्घ)__va(real_end) &&
		(अचिन्हित दीर्घ)__va(real_start) < end;
पूर्ण

अटल अंतरभूत पूर्णांक overlaps_kernel_text(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस start < (अचिन्हित दीर्घ)__init_end &&
		(अचिन्हित दीर्घ)_stext < end;
पूर्ण

#अगर_घोषित PPC64_ELF_ABI_v1

#घोषणा HAVE_DEREFERENCE_FUNCTION_DESCRIPTOR 1

#अघोषित dereference_function_descriptor
अटल अंतरभूत व्योम *dereference_function_descriptor(व्योम *ptr)
अणु
	काष्ठा ppc64_opd_entry *desc = ptr;
	व्योम *p;

	अगर (!get_kernel_nofault(p, (व्योम *)&desc->funcaddr))
		ptr = p;
	वापस ptr;
पूर्ण

#अघोषित dereference_kernel_function_descriptor
अटल अंतरभूत व्योम *dereference_kernel_function_descriptor(व्योम *ptr)
अणु
	अगर (ptr < (व्योम *)__start_opd || ptr >= (व्योम *)__end_opd)
		वापस ptr;

	वापस dereference_function_descriptor(ptr);
पूर्ण
#पूर्ण_अगर /* PPC64_ELF_ABI_v1 */

#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_SECTIONS_H */

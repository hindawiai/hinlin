<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PAGE_64_H
#घोषणा _ASM_X86_PAGE_64_H

#समावेश <यंत्र/page_64_types.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/alternative.h>

/* duplicated to the one in booपंचांगem.h */
बाह्य अचिन्हित दीर्घ max_pfn;
बाह्य अचिन्हित दीर्घ phys_base;

बाह्य अचिन्हित दीर्घ page_offset_base;
बाह्य अचिन्हित दीर्घ vदो_स्मृति_base;
बाह्य अचिन्हित दीर्घ vmemmap_base;

अटल अंतरभूत अचिन्हित दीर्घ __phys_addr_nodebug(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ y = x - __START_KERNEL_map;

	/* use the carry flag to determine अगर x was < __START_KERNEL_map */
	x = y + ((x > y) ? phys_base : (__START_KERNEL_map - PAGE_OFFSET));

	वापस x;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
बाह्य अचिन्हित दीर्घ __phys_addr(अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ __phys_addr_symbol(अचिन्हित दीर्घ);
#अन्यथा
#घोषणा __phys_addr(x)		__phys_addr_nodebug(x)
#घोषणा __phys_addr_symbol(x) \
	((अचिन्हित दीर्घ)(x) - __START_KERNEL_map + phys_base)
#पूर्ण_अगर

#घोषणा __phys_reloc_hide(x)	(x)

#अगर_घोषित CONFIG_FLATMEM
#घोषणा pfn_valid(pfn)          ((pfn) < max_pfn)
#पूर्ण_अगर

व्योम clear_page_orig(व्योम *page);
व्योम clear_page_rep(व्योम *page);
व्योम clear_page_erms(व्योम *page);

अटल अंतरभूत व्योम clear_page(व्योम *page)
अणु
	alternative_call_2(clear_page_orig,
			   clear_page_rep, X86_FEATURE_REP_GOOD,
			   clear_page_erms, X86_FEATURE_ERMS,
			   "=D" (page),
			   "0" (page)
			   : "cc", "memory", "rax", "rcx");
पूर्ण

व्योम copy_page(व्योम *to, व्योम *from);

#अगर_घोषित CONFIG_X86_5LEVEL
/*
 * User space process size.  This is the first address outside the user range.
 * There are a few स्थिरraपूर्णांकs that determine this:
 *
 * On Intel CPUs, अगर a SYSCALL inकाष्ठाion is at the highest canonical
 * address, then that syscall will enter the kernel with a
 * non-canonical वापस address, and SYSRET will explode dangerously.
 * We aव्योम this particular problem by preventing anything
 * from being mapped at the maximum canonical address.
 *
 * On AMD CPUs in the Ryzen family, there's a nasty bug in which the
 * CPUs malfunction अगर they execute code from the highest canonical page.
 * They'll speculate right off the end of the canonical space, and
 * bad things happen.  This is worked around in the same way as the
 * Intel problem.
 *
 * With page table isolation enabled, we map the LDT in ... [stay tuned]
 */
अटल अंतरभूत अचिन्हित दीर्घ task_size_max(व्योम)
अणु
	अचिन्हित दीर्घ ret;

	alternative_io("movq %[small],%0","movq %[large],%0",
			X86_FEATURE_LA57,
			"=r" (ret),
			[small] "i" ((1ul << 47)-PAGE_SIZE),
			[large] "i" ((1ul << 56)-PAGE_SIZE));

	वापस ret;
पूर्ण
#पूर्ण_अगर	/* CONFIG_X86_5LEVEL */

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_X86_VSYSCALL_EMULATION
# define __HAVE_ARCH_GATE_AREA 1
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_PAGE_64_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_KEXEC_H
#घोषणा _ASM_X86_KEXEC_H

#अगर_घोषित CONFIG_X86_32
# define PA_CONTROL_PAGE	0
# define VA_CONTROL_PAGE	1
# define PA_PGD			2
# define PA_SWAP_PAGE		3
# define PAGES_NR		4
#अन्यथा
# define PA_CONTROL_PAGE	0
# define VA_CONTROL_PAGE	1
# define PA_TABLE_PAGE		2
# define PA_SWAP_PAGE		3
# define PAGES_NR		4
#पूर्ण_अगर

# define KEXEC_CONTROL_CODE_MAX_SIZE	2048

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/bootparam.h>

काष्ठा kimage;

/*
 * KEXEC_SOURCE_MEMORY_LIMIT maximum page get_मुक्त_page can वापस.
 * I.e. Maximum page that is mapped directly पूर्णांकo kernel memory,
 * and kmap is not required.
 *
 * So far x86_64 is limited to 40 physical address bits.
 */
#अगर_घोषित CONFIG_X86_32
/* Maximum physical address we can use pages from */
# define KEXEC_SOURCE_MEMORY_LIMIT (-1UL)
/* Maximum address we can reach in physical address mode */
# define KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)
/* Maximum address we can use क्रम the control code buffer */
# define KEXEC_CONTROL_MEMORY_LIMIT TASK_SIZE

# define KEXEC_CONTROL_PAGE_SIZE	4096

/* The native architecture */
# define KEXEC_ARCH KEXEC_ARCH_386

/* We can also handle crash dumps from 64 bit kernel. */
# define vmcore_elf_check_arch_cross(x) ((x)->e_machine == EM_X86_64)
#अन्यथा
/* Maximum physical address we can use pages from */
# define KEXEC_SOURCE_MEMORY_LIMIT      (MAXMEM-1)
/* Maximum address we can reach in physical address mode */
# define KEXEC_DESTINATION_MEMORY_LIMIT (MAXMEM-1)
/* Maximum address we can use क्रम the control pages */
# define KEXEC_CONTROL_MEMORY_LIMIT     (MAXMEM-1)

/* Allocate one page क्रम the pdp and the second क्रम the code */
# define KEXEC_CONTROL_PAGE_SIZE  (4096UL + 4096UL)

/* The native architecture */
# define KEXEC_ARCH KEXEC_ARCH_X86_64
#पूर्ण_अगर

/*
 * This function is responsible क्रम capturing रेजिस्टर states अगर coming
 * via panic otherwise just fix up the ss and sp अगर coming via kernel
 * mode exception.
 */
अटल अंतरभूत व्योम crash_setup_regs(काष्ठा pt_regs *newregs,
				    काष्ठा pt_regs *oldregs)
अणु
	अगर (oldregs) अणु
		स_नकल(newregs, oldregs, माप(*newregs));
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_X86_32
		यंत्र अस्थिर("movl %%ebx,%0" : "=m"(newregs->bx));
		यंत्र अस्थिर("movl %%ecx,%0" : "=m"(newregs->cx));
		यंत्र अस्थिर("movl %%edx,%0" : "=m"(newregs->dx));
		यंत्र अस्थिर("movl %%esi,%0" : "=m"(newregs->si));
		यंत्र अस्थिर("movl %%edi,%0" : "=m"(newregs->di));
		यंत्र अस्थिर("movl %%ebp,%0" : "=m"(newregs->bp));
		यंत्र अस्थिर("movl %%eax,%0" : "=m"(newregs->ax));
		यंत्र अस्थिर("movl %%esp,%0" : "=m"(newregs->sp));
		यंत्र अस्थिर("movl %%ss, %%eax;" :"=a"(newregs->ss));
		यंत्र अस्थिर("movl %%cs, %%eax;" :"=a"(newregs->cs));
		यंत्र अस्थिर("movl %%ds, %%eax;" :"=a"(newregs->ds));
		यंत्र अस्थिर("movl %%es, %%eax;" :"=a"(newregs->es));
		यंत्र अस्थिर("pushfl; popl %0" :"=m"(newregs->flags));
#अन्यथा
		यंत्र अस्थिर("movq %%rbx,%0" : "=m"(newregs->bx));
		यंत्र अस्थिर("movq %%rcx,%0" : "=m"(newregs->cx));
		यंत्र अस्थिर("movq %%rdx,%0" : "=m"(newregs->dx));
		यंत्र अस्थिर("movq %%rsi,%0" : "=m"(newregs->si));
		यंत्र अस्थिर("movq %%rdi,%0" : "=m"(newregs->di));
		यंत्र अस्थिर("movq %%rbp,%0" : "=m"(newregs->bp));
		यंत्र अस्थिर("movq %%rax,%0" : "=m"(newregs->ax));
		यंत्र अस्थिर("movq %%rsp,%0" : "=m"(newregs->sp));
		यंत्र अस्थिर("movq %%r8,%0" : "=m"(newregs->r8));
		यंत्र अस्थिर("movq %%r9,%0" : "=m"(newregs->r9));
		यंत्र अस्थिर("movq %%r10,%0" : "=m"(newregs->r10));
		यंत्र अस्थिर("movq %%r11,%0" : "=m"(newregs->r11));
		यंत्र अस्थिर("movq %%r12,%0" : "=m"(newregs->r12));
		यंत्र अस्थिर("movq %%r13,%0" : "=m"(newregs->r13));
		यंत्र अस्थिर("movq %%r14,%0" : "=m"(newregs->r14));
		यंत्र अस्थिर("movq %%r15,%0" : "=m"(newregs->r15));
		यंत्र अस्थिर("movl %%ss, %%eax;" :"=a"(newregs->ss));
		यंत्र अस्थिर("movl %%cs, %%eax;" :"=a"(newregs->cs));
		यंत्र अस्थिर("pushfq; popq %0" :"=m"(newregs->flags));
#पूर्ण_अगर
		newregs->ip = _THIS_IP_;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_32
यंत्रlinkage अचिन्हित दीर्घ
relocate_kernel(अचिन्हित दीर्घ indirection_page,
		अचिन्हित दीर्घ control_page,
		अचिन्हित दीर्घ start_address,
		अचिन्हित पूर्णांक has_pae,
		अचिन्हित पूर्णांक preserve_context);
#अन्यथा
अचिन्हित दीर्घ
relocate_kernel(अचिन्हित दीर्घ indirection_page,
		अचिन्हित दीर्घ page_list,
		अचिन्हित दीर्घ start_address,
		अचिन्हित पूर्णांक preserve_context,
		अचिन्हित पूर्णांक sme_active);
#पूर्ण_अगर

#घोषणा ARCH_HAS_KIMAGE_ARCH

#अगर_घोषित CONFIG_X86_32
काष्ठा kimage_arch अणु
	pgd_t *pgd;
#अगर_घोषित CONFIG_X86_PAE
	pmd_t *pmd0;
	pmd_t *pmd1;
#पूर्ण_अगर
	pte_t *pte0;
	pte_t *pte1;
पूर्ण;
#अन्यथा
काष्ठा kimage_arch अणु
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
पूर्ण;
#पूर्ण_अगर /* CONFIG_X86_32 */

#अगर_घोषित CONFIG_X86_64
/*
 * Number of elements and order of elements in this काष्ठाure should match
 * with the ones in arch/x86/purgatory/entry64.S. If you make a change here
 * make an appropriate change in purgatory too.
 */
काष्ठा kexec_entry64_regs अणु
	uपूर्णांक64_t rax;
	uपूर्णांक64_t rcx;
	uपूर्णांक64_t rdx;
	uपूर्णांक64_t rbx;
	uपूर्णांक64_t rsp;
	uपूर्णांक64_t rbp;
	uपूर्णांक64_t rsi;
	uपूर्णांक64_t rdi;
	uपूर्णांक64_t r8;
	uपूर्णांक64_t r9;
	uपूर्णांक64_t r10;
	uपूर्णांक64_t r11;
	uपूर्णांक64_t r12;
	uपूर्णांक64_t r13;
	uपूर्णांक64_t r14;
	uपूर्णांक64_t r15;
	uपूर्णांक64_t rip;
पूर्ण;

बाह्य पूर्णांक arch_kexec_post_alloc_pages(व्योम *vaddr, अचिन्हित पूर्णांक pages,
				       gfp_t gfp);
#घोषणा arch_kexec_post_alloc_pages arch_kexec_post_alloc_pages

बाह्य व्योम arch_kexec_pre_मुक्त_pages(व्योम *vaddr, अचिन्हित पूर्णांक pages);
#घोषणा arch_kexec_pre_मुक्त_pages arch_kexec_pre_मुक्त_pages

#पूर्ण_अगर

प्रकार व्योम crash_vmclear_fn(व्योम);
बाह्य crash_vmclear_fn __rcu *crash_vmclear_loaded_vmcss;
बाह्य व्योम kdump_nmi_shootकरोwn_cpus(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_KEXEC_H */

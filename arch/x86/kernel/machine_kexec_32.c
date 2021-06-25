<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * handle transition of Linux booting another kernel
 * Copyright (C) 2002-2005 Eric Biederman  <ebiederm@xmission.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/delay.h>
#समावेश <linux/numa.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/suspend.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/debugreg.h>

अटल व्योम set_gdt(व्योम *newgdt, __u16 limit)
अणु
	काष्ठा desc_ptr curgdt;

	/* ia32 supports unaligned loads & stores */
	curgdt.size    = limit;
	curgdt.address = (अचिन्हित दीर्घ)newgdt;

	load_gdt(&curgdt);
पूर्ण

अटल व्योम load_segments(व्योम)
अणु
#घोषणा __STR(X) #X
#घोषणा STR(X) __STR(X)

	__यंत्र__ __अस्थिर__ (
		"\tljmp $"STR(__KERNEL_CS)",$1f\n"
		"\t1:\n"
		"\tmovl $"STR(__KERNEL_DS)",%%eax\n"
		"\tmovl %%eax,%%ds\n"
		"\tmovl %%eax,%%es\n"
		"\tmovl %%eax,%%ss\n"
		: : : "eax", "memory");
#अघोषित STR
#अघोषित __STR
पूर्ण

अटल व्योम machine_kexec_मुक्त_page_tables(काष्ठा kimage *image)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)image->arch.pgd, PGD_ALLOCATION_ORDER);
	image->arch.pgd = शून्य;
#अगर_घोषित CONFIG_X86_PAE
	मुक्त_page((अचिन्हित दीर्घ)image->arch.pmd0);
	image->arch.pmd0 = शून्य;
	मुक्त_page((अचिन्हित दीर्घ)image->arch.pmd1);
	image->arch.pmd1 = शून्य;
#पूर्ण_अगर
	मुक्त_page((अचिन्हित दीर्घ)image->arch.pte0);
	image->arch.pte0 = शून्य;
	मुक्त_page((अचिन्हित दीर्घ)image->arch.pte1);
	image->arch.pte1 = शून्य;
पूर्ण

अटल पूर्णांक machine_kexec_alloc_page_tables(काष्ठा kimage *image)
अणु
	image->arch.pgd = (pgd_t *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
						    PGD_ALLOCATION_ORDER);
#अगर_घोषित CONFIG_X86_PAE
	image->arch.pmd0 = (pmd_t *)get_zeroed_page(GFP_KERNEL);
	image->arch.pmd1 = (pmd_t *)get_zeroed_page(GFP_KERNEL);
#पूर्ण_अगर
	image->arch.pte0 = (pte_t *)get_zeroed_page(GFP_KERNEL);
	image->arch.pte1 = (pte_t *)get_zeroed_page(GFP_KERNEL);
	अगर (!image->arch.pgd ||
#अगर_घोषित CONFIG_X86_PAE
	    !image->arch.pmd0 || !image->arch.pmd1 ||
#पूर्ण_अगर
	    !image->arch.pte0 || !image->arch.pte1) अणु
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम machine_kexec_page_table_set_one(
	pgd_t *pgd, pmd_t *pmd, pte_t *pte,
	अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ paddr)
अणु
	p4d_t *p4d;
	pud_t *pud;

	pgd += pgd_index(vaddr);
#अगर_घोषित CONFIG_X86_PAE
	अगर (!(pgd_val(*pgd) & _PAGE_PRESENT))
		set_pgd(pgd, __pgd(__pa(pmd) | _PAGE_PRESENT));
#पूर्ण_अगर
	p4d = p4d_offset(pgd, vaddr);
	pud = pud_offset(p4d, vaddr);
	pmd = pmd_offset(pud, vaddr);
	अगर (!(pmd_val(*pmd) & _PAGE_PRESENT))
		set_pmd(pmd, __pmd(__pa(pte) | _PAGE_TABLE));
	pte = pte_offset_kernel(pmd, vaddr);
	set_pte(pte, pfn_pte(paddr >> PAGE_SHIFT, PAGE_KERNEL_EXEC));
पूर्ण

अटल व्योम machine_kexec_prepare_page_tables(काष्ठा kimage *image)
अणु
	व्योम *control_page;
	pmd_t *pmd = शून्य;

	control_page = page_address(image->control_code_page);
#अगर_घोषित CONFIG_X86_PAE
	pmd = image->arch.pmd0;
#पूर्ण_अगर
	machine_kexec_page_table_set_one(
		image->arch.pgd, pmd, image->arch.pte0,
		(अचिन्हित दीर्घ)control_page, __pa(control_page));
#अगर_घोषित CONFIG_X86_PAE
	pmd = image->arch.pmd1;
#पूर्ण_अगर
	machine_kexec_page_table_set_one(
		image->arch.pgd, pmd, image->arch.pte1,
		__pa(control_page), __pa(control_page));
पूर्ण

/*
 * A architecture hook called to validate the
 * proposed image and prepare the control pages
 * as needed.  The pages क्रम KEXEC_CONTROL_PAGE_SIZE
 * have been allocated, but the segments have yet
 * been copied पूर्णांकo the kernel.
 *
 * Do what every setup is needed on image and the
 * reboot code buffer to allow us to aव्योम allocations
 * later.
 *
 * - Make control page executable.
 * - Allocate page tables
 * - Setup page tables
 */
पूर्णांक machine_kexec_prepare(काष्ठा kimage *image)
अणु
	पूर्णांक error;

	set_memory_x((अचिन्हित दीर्घ)page_address(image->control_code_page), 1);
	error = machine_kexec_alloc_page_tables(image);
	अगर (error)
		वापस error;
	machine_kexec_prepare_page_tables(image);
	वापस 0;
पूर्ण

/*
 * Unकरो anything leftover by machine_kexec_prepare
 * when an image is मुक्तd.
 */
व्योम machine_kexec_cleanup(काष्ठा kimage *image)
अणु
	set_memory_nx((अचिन्हित दीर्घ)page_address(image->control_code_page), 1);
	machine_kexec_मुक्त_page_tables(image);
पूर्ण

/*
 * Do not allocate memory (or fail in any way) in machine_kexec().
 * We are past the poपूर्णांक of no वापस, committed to rebooting now.
 */
व्योम machine_kexec(काष्ठा kimage *image)
अणु
	अचिन्हित दीर्घ page_list[PAGES_NR];
	व्योम *control_page;
	पूर्णांक save_ftrace_enabled;
	यंत्रlinkage अचिन्हित दीर्घ
		(*relocate_kernel_ptr)(अचिन्हित दीर्घ indirection_page,
				       अचिन्हित दीर्घ control_page,
				       अचिन्हित दीर्घ start_address,
				       अचिन्हित पूर्णांक has_pae,
				       अचिन्हित पूर्णांक preserve_context);

#अगर_घोषित CONFIG_KEXEC_JUMP
	अगर (image->preserve_context)
		save_processor_state();
#पूर्ण_अगर

	save_ftrace_enabled = __ftrace_enabled_save();

	/* Interrupts aren't acceptable जबतक we reboot */
	local_irq_disable();
	hw_अवरोधpoपूर्णांक_disable();

	अगर (image->preserve_context) अणु
#अगर_घोषित CONFIG_X86_IO_APIC
		/*
		 * We need to put APICs in legacy mode so that we can
		 * get समयr पूर्णांकerrupts in second kernel. kexec/kdump
		 * paths alपढ़ोy have calls to restore_boot_irq_mode()
		 * in one क्रमm or other. kexec jump path also need one.
		 */
		clear_IO_APIC();
		restore_boot_irq_mode();
#पूर्ण_अगर
	पूर्ण

	control_page = page_address(image->control_code_page);
	स_नकल(control_page, relocate_kernel, KEXEC_CONTROL_CODE_MAX_SIZE);

	relocate_kernel_ptr = control_page;
	page_list[PA_CONTROL_PAGE] = __pa(control_page);
	page_list[VA_CONTROL_PAGE] = (अचिन्हित दीर्घ)control_page;
	page_list[PA_PGD] = __pa(image->arch.pgd);

	अगर (image->type == KEXEC_TYPE_DEFAULT)
		page_list[PA_SWAP_PAGE] = (page_to_pfn(image->swap_page)
						<< PAGE_SHIFT);

	/*
	 * The segment रेजिस्टरs are funny things, they have both a
	 * visible and an invisible part.  Whenever the visible part is
	 * set to a specअगरic selector, the invisible part is loaded
	 * with from a table in memory.  At no other समय is the
	 * descriptor table in memory accessed.
	 *
	 * I take advantage of this here by क्रमce loading the
	 * segments, beक्रमe I zap the gdt with an invalid value.
	 */
	load_segments();
	/*
	 * The gdt & idt are now invalid.
	 * If you want to load them you must set up your own idt & gdt.
	 */
	idt_invalidate(phys_to_virt(0));
	set_gdt(phys_to_virt(0), 0);

	/* now call it */
	image->start = relocate_kernel_ptr((अचिन्हित दीर्घ)image->head,
					   (अचिन्हित दीर्घ)page_list,
					   image->start,
					   boot_cpu_has(X86_FEATURE_PAE),
					   image->preserve_context);

#अगर_घोषित CONFIG_KEXEC_JUMP
	अगर (image->preserve_context)
		restore_processor_state();
#पूर्ण_अगर

	__ftrace_enabled_restore(save_ftrace_enabled);
पूर्ण

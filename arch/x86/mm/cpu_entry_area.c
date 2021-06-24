<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/spinlock.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kcore.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/desc.h>

अटल DEFINE_PER_CPU_PAGE_ALIGNED(काष्ठा entry_stack_page, entry_stack_storage);

#अगर_घोषित CONFIG_X86_64
अटल DEFINE_PER_CPU_PAGE_ALIGNED(काष्ठा exception_stacks, exception_stacks);
DEFINE_PER_CPU(काष्ठा cea_exception_stacks*, cea_exception_stacks);
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
DECLARE_PER_CPU_PAGE_ALIGNED(काष्ठा द्विगुनfault_stack, द्विगुनfault_stack);
#पूर्ण_अगर

/* Is called from entry code, so must be noinstr */
noinstr काष्ठा cpu_entry_area *get_cpu_entry_area(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ va = CPU_ENTRY_AREA_PER_CPU + cpu * CPU_ENTRY_AREA_SIZE;
	BUILD_BUG_ON(माप(काष्ठा cpu_entry_area) % PAGE_SIZE != 0);

	वापस (काष्ठा cpu_entry_area *) va;
पूर्ण
EXPORT_SYMBOL(get_cpu_entry_area);

व्योम cea_set_pte(व्योम *cea_vaddr, phys_addr_t pa, pgprot_t flags)
अणु
	अचिन्हित दीर्घ va = (अचिन्हित दीर्घ) cea_vaddr;
	pte_t pte = pfn_pte(pa >> PAGE_SHIFT, flags);

	/*
	 * The cpu_entry_area is shared between the user and kernel
	 * page tables.  All of its ptes can safely be global.
	 * _PAGE_GLOBAL माला_लो reused to help indicate PROT_NONE क्रम
	 * non-present PTEs, so be careful not to set it in that
	 * हाल to aव्योम confusion.
	 */
	अगर (boot_cpu_has(X86_FEATURE_PGE) &&
	    (pgprot_val(flags) & _PAGE_PRESENT))
		pte = pte_set_flags(pte, _PAGE_GLOBAL);

	set_pte_vaddr(va, pte);
पूर्ण

अटल व्योम __init
cea_map_percpu_pages(व्योम *cea_vaddr, व्योम *ptr, पूर्णांक pages, pgprot_t prot)
अणु
	क्रम ( ; pages; pages--, cea_vaddr+= PAGE_SIZE, ptr += PAGE_SIZE)
		cea_set_pte(cea_vaddr, per_cpu_ptr_to_phys(ptr), prot);
पूर्ण

अटल व्योम __init percpu_setup_debug_store(अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_CPU_SUP_INTEL
	अचिन्हित पूर्णांक npages;
	व्योम *cea;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस;

	cea = &get_cpu_entry_area(cpu)->cpu_debug_store;
	npages = माप(काष्ठा debug_store) / PAGE_SIZE;
	BUILD_BUG_ON(माप(काष्ठा debug_store) % PAGE_SIZE != 0);
	cea_map_percpu_pages(cea, &per_cpu(cpu_debug_store, cpu), npages,
			     PAGE_KERNEL);

	cea = &get_cpu_entry_area(cpu)->cpu_debug_buffers;
	/*
	 * Force the population of PMDs क्रम not yet allocated per cpu
	 * memory like debug store buffers.
	 */
	npages = माप(काष्ठा debug_store_buffers) / PAGE_SIZE;
	क्रम (; npages; npages--, cea += PAGE_SIZE)
		cea_set_pte(cea, 0, PAGE_NONE);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_X86_64

#घोषणा cea_map_stack(name) करो अणु					\
	npages = माप(estacks->name## _stack) / PAGE_SIZE;		\
	cea_map_percpu_pages(cea->estacks.name## _stack,		\
			estacks->name## _stack, npages, PAGE_KERNEL);	\
	पूर्ण जबतक (0)

अटल व्योम __init percpu_setup_exception_stacks(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा exception_stacks *estacks = per_cpu_ptr(&exception_stacks, cpu);
	काष्ठा cpu_entry_area *cea = get_cpu_entry_area(cpu);
	अचिन्हित पूर्णांक npages;

	BUILD_BUG_ON(माप(exception_stacks) % PAGE_SIZE != 0);

	per_cpu(cea_exception_stacks, cpu) = &cea->estacks;

	/*
	 * The exceptions stack mappings in the per cpu area are रक्षित
	 * by guard pages so each stack must be mapped separately. DB2 is
	 * not mapped; it just exists to catch triple nesting of #DB.
	 */
	cea_map_stack(DF);
	cea_map_stack(NMI);
	cea_map_stack(DB);
	cea_map_stack(MCE);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम percpu_setup_exception_stacks(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_entry_area *cea = get_cpu_entry_area(cpu);

	cea_map_percpu_pages(&cea->द्विगुनfault_stack,
			     &per_cpu(द्विगुनfault_stack, cpu), 1, PAGE_KERNEL);
पूर्ण
#पूर्ण_अगर

/* Setup the fixmap mappings only once per-processor */
अटल व्योम __init setup_cpu_entry_area(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_entry_area *cea = get_cpu_entry_area(cpu);
#अगर_घोषित CONFIG_X86_64
	/* On 64-bit प्रणालीs, we use a पढ़ो-only fixmap GDT and TSS. */
	pgprot_t gdt_prot = PAGE_KERNEL_RO;
	pgprot_t tss_prot = PAGE_KERNEL_RO;
#अन्यथा
	/*
	 * On native 32-bit प्रणालीs, the GDT cannot be पढ़ो-only because
	 * our द्विगुन fault handler uses a task gate, and entering through
	 * a task gate needs to change an available TSS to busy.  If the
	 * GDT is पढ़ो-only, that will triple fault.  The TSS cannot be
	 * पढ़ो-only because the CPU ग_लिखोs to it on task चयनes.
	 *
	 * On Xen PV, the GDT must be पढ़ो-only because the hypervisor
	 * requires it.
	 */
	pgprot_t gdt_prot = boot_cpu_has(X86_FEATURE_XENPV) ?
		PAGE_KERNEL_RO : PAGE_KERNEL;
	pgprot_t tss_prot = PAGE_KERNEL;
#पूर्ण_अगर

	cea_set_pte(&cea->gdt, get_cpu_gdt_paddr(cpu), gdt_prot);

	cea_map_percpu_pages(&cea->entry_stack_page,
			     per_cpu_ptr(&entry_stack_storage, cpu), 1,
			     PAGE_KERNEL);

	/*
	 * The Intel SDM says (Volume 3, 7.2.1):
	 *
	 *  Aव्योम placing a page boundary in the part of the TSS that the
	 *  processor पढ़ोs during a task चयन (the first 104 bytes). The
	 *  processor may not correctly perक्रमm address translations अगर a
	 *  boundary occurs in this area. During a task चयन, the processor
	 *  पढ़ोs and ग_लिखोs पूर्णांकo the first 104 bytes of each TSS (using
	 *  contiguous physical addresses beginning with the physical address
	 *  of the first byte of the TSS). So, after TSS access begins, अगर
	 *  part of the 104 bytes is not physically contiguous, the processor
	 *  will access incorrect inक्रमmation without generating a page-fault
	 *  exception.
	 *
	 * There are also a lot of errata involving the TSS spanning a page
	 * boundary.  Assert that we're not करोing that.
	 */
	BUILD_BUG_ON((दुरत्व(काष्ठा tss_काष्ठा, x86_tss) ^
		      दुरत्वend(काष्ठा tss_काष्ठा, x86_tss)) & PAGE_MASK);
	BUILD_BUG_ON(माप(काष्ठा tss_काष्ठा) % PAGE_SIZE != 0);
	/*
	 * VMX changes the host TR limit to 0x67 after a VM निकास. This is
	 * okay, since 0x67 covers the size of काष्ठा x86_hw_tss. Make sure
	 * that this is correct.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा tss_काष्ठा, x86_tss) != 0);
	BUILD_BUG_ON(माप(काष्ठा x86_hw_tss) != 0x68);

	cea_map_percpu_pages(&cea->tss, &per_cpu(cpu_tss_rw, cpu),
			     माप(काष्ठा tss_काष्ठा) / PAGE_SIZE, tss_prot);

#अगर_घोषित CONFIG_X86_32
	per_cpu(cpu_entry_area, cpu) = cea;
#पूर्ण_अगर

	percpu_setup_exception_stacks(cpu);

	percpu_setup_debug_store(cpu);
पूर्ण

अटल __init व्योम setup_cpu_entry_area_ptes(व्योम)
अणु
#अगर_घोषित CONFIG_X86_32
	अचिन्हित दीर्घ start, end;

	/* The +1 is क्रम the पढ़ोonly IDT: */
	BUILD_BUG_ON((CPU_ENTRY_AREA_PAGES+1)*PAGE_SIZE != CPU_ENTRY_AREA_MAP_SIZE);
	BUILD_BUG_ON(CPU_ENTRY_AREA_TOTAL_SIZE != CPU_ENTRY_AREA_MAP_SIZE);
	BUG_ON(CPU_ENTRY_AREA_BASE & ~PMD_MASK);

	start = CPU_ENTRY_AREA_BASE;
	end = start + CPU_ENTRY_AREA_MAP_SIZE;

	/* Careful here: start + PMD_SIZE might wrap around */
	क्रम (; start < end && start >= CPU_ENTRY_AREA_BASE; start += PMD_SIZE)
		populate_extra_pte(start);
#पूर्ण_अगर
पूर्ण

व्योम __init setup_cpu_entry_areas(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	setup_cpu_entry_area_ptes();

	क्रम_each_possible_cpu(cpu)
		setup_cpu_entry_area(cpu);

	/*
	 * This is the last essential update to swapper_pgdir which needs
	 * to be synchronized to initial_page_table on 32bit.
	 */
	sync_initial_page_table();
पूर्ण

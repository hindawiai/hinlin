<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/ioremap.c
 *
 * Re-map IO memory to kernel address space so that we can access it.
 *
 * (C) Copyright 1995 1996 Linus Torvalds
 *
 * Hacked क्रम ARM by Phil Blundell <philb@gnu.org>
 * Hacked to allow all architectures to build, and various cleanups
 * by Russell King
 *
 * This allows a driver to remap an arbitrary region of bus memory पूर्णांकo
 * भव space.  One should *only* use पढ़ोl, ग_लिखोl, स_नकल_toio and
 * so on with such remapped areas.
 *
 * Because the ARM only has a 32-bit address space we can't address the
 * whole of the (physical) PCI space at once.  PCI huge-mode addressing
 * allows us to circumvent this restriction by splitting PCI space पूर्णांकo
 * two 2GB chunks and mapping only one at a समय पूर्णांकo processor memory.
 * We use MMU protection करोमुख्यs to trap any attempt to access the bank
 * that is not currently mapped.  (This isn't fully implemented yet.)
 */
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/early_ioremap.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "mm.h"


LIST_HEAD(अटल_vmlist);

अटल काष्ठा अटल_vm *find_अटल_vm_paddr(phys_addr_t paddr,
			माप_प्रकार size, अचिन्हित पूर्णांक mtype)
अणु
	काष्ठा अटल_vm *svm;
	काष्ठा vm_काष्ठा *vm;

	list_क्रम_each_entry(svm, &अटल_vmlist, list) अणु
		vm = &svm->vm;
		अगर (!(vm->flags & VM_ARM_STATIC_MAPPING))
			जारी;
		अगर ((vm->flags & VM_ARM_MTYPE_MASK) != VM_ARM_MTYPE(mtype))
			जारी;

		अगर (vm->phys_addr > paddr ||
			paddr + size - 1 > vm->phys_addr + vm->size - 1)
			जारी;

		वापस svm;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा अटल_vm *find_अटल_vm_vaddr(व्योम *vaddr)
अणु
	काष्ठा अटल_vm *svm;
	काष्ठा vm_काष्ठा *vm;

	list_क्रम_each_entry(svm, &अटल_vmlist, list) अणु
		vm = &svm->vm;

		/* अटल_vmlist is ascending order */
		अगर (vm->addr > vaddr)
			अवरोध;

		अगर (vm->addr <= vaddr && vm->addr + vm->size > vaddr)
			वापस svm;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम __init add_अटल_vm_early(काष्ठा अटल_vm *svm)
अणु
	काष्ठा अटल_vm *curr_svm;
	काष्ठा vm_काष्ठा *vm;
	व्योम *vaddr;

	vm = &svm->vm;
	vm_area_add_early(vm);
	vaddr = vm->addr;

	list_क्रम_each_entry(curr_svm, &अटल_vmlist, list) अणु
		vm = &curr_svm->vm;

		अगर (vm->addr > vaddr)
			अवरोध;
	पूर्ण
	list_add_tail(&svm->list, &curr_svm->list);
पूर्ण

पूर्णांक ioremap_page(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ phys,
		 स्थिर काष्ठा mem_type *mtype)
अणु
	वापस ioremap_page_range(virt, virt + PAGE_SIZE, phys,
				  __pgprot(mtype->prot_pte));
पूर्ण
EXPORT_SYMBOL(ioremap_page);

व्योम __check_vदो_स्मृति_seq(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = init_mm.context.vदो_स्मृति_seq;
		स_नकल(pgd_offset(mm, VMALLOC_START),
		       pgd_offset_k(VMALLOC_START),
		       माप(pgd_t) * (pgd_index(VMALLOC_END) -
					pgd_index(VMALLOC_START)));
		mm->context.vदो_स्मृति_seq = seq;
	पूर्ण जबतक (seq != init_mm.context.vदो_स्मृति_seq);
पूर्ण

#अगर !defined(CONFIG_SMP) && !defined(CONFIG_ARM_LPAE)
/*
 * Section support is unsafe on SMP - If you iounmap and ioremap a region,
 * the other CPUs will not see this change until their next context चयन.
 * Meanजबतक, (eg) अगर an पूर्णांकerrupt comes in on one of those other CPUs
 * which requires the new ioremap'd region to be referenced, the CPU will
 * reference the _old_ region.
 *
 * Note that get_vm_area_caller() allocates a guard 4K page, so we need to
 * mask the size back to 1MB aligned or we will overflow in the loop below.
 */
अटल व्योम unmap_area_sections(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ addr = virt, end = virt + (size & ~(SZ_1M - 1));
	pmd_t *pmdp = pmd_off_k(addr);

	करो अणु
		pmd_t pmd = *pmdp;

		अगर (!pmd_none(pmd)) अणु
			/*
			 * Clear the PMD from the page table, and
			 * increment the vदो_स्मृति sequence so others
			 * notice this change.
			 *
			 * Note: this is still racy on SMP machines.
			 */
			pmd_clear(pmdp);
			init_mm.context.vदो_स्मृति_seq++;

			/*
			 * Free the page table, अगर there was one.
			 */
			अगर ((pmd_val(pmd) & PMD_TYPE_MASK) == PMD_TYPE_TABLE)
				pte_मुक्त_kernel(&init_mm, pmd_page_vaddr(pmd));
		पूर्ण

		addr += PMD_SIZE;
		pmdp += 2;
	पूर्ण जबतक (addr < end);

	/*
	 * Ensure that the active_mm is up to date - we want to
	 * catch any use-after-iounmap हालs.
	 */
	अगर (current->active_mm->context.vदो_स्मृति_seq != init_mm.context.vदो_स्मृति_seq)
		__check_vदो_स्मृति_seq(current->active_mm);

	flush_tlb_kernel_range(virt, end);
पूर्ण

अटल पूर्णांक
remap_area_sections(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ pfn,
		    माप_प्रकार size, स्थिर काष्ठा mem_type *type)
अणु
	अचिन्हित दीर्घ addr = virt, end = virt + size;
	pmd_t *pmd = pmd_off_k(addr);

	/*
	 * Remove and मुक्त any PTE-based mapping, and
	 * sync the current kernel mapping.
	 */
	unmap_area_sections(virt, size);

	करो अणु
		pmd[0] = __pmd(__pfn_to_phys(pfn) | type->prot_sect);
		pfn += SZ_1M >> PAGE_SHIFT;
		pmd[1] = __pmd(__pfn_to_phys(pfn) | type->prot_sect);
		pfn += SZ_1M >> PAGE_SHIFT;
		flush_pmd_entry(pmd);

		addr += PMD_SIZE;
		pmd += 2;
	पूर्ण जबतक (addr < end);

	वापस 0;
पूर्ण

अटल पूर्णांक
remap_area_supersections(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ pfn,
			 माप_प्रकार size, स्थिर काष्ठा mem_type *type)
अणु
	अचिन्हित दीर्घ addr = virt, end = virt + size;
	pmd_t *pmd = pmd_off_k(addr);

	/*
	 * Remove and मुक्त any PTE-based mapping, and
	 * sync the current kernel mapping.
	 */
	unmap_area_sections(virt, size);
	करो अणु
		अचिन्हित दीर्घ super_pmd_val, i;

		super_pmd_val = __pfn_to_phys(pfn) | type->prot_sect |
				PMD_SECT_SUPER;
		super_pmd_val |= ((pfn >> (32 - PAGE_SHIFT)) & 0xf) << 20;

		क्रम (i = 0; i < 8; i++) अणु
			pmd[0] = __pmd(super_pmd_val);
			pmd[1] = __pmd(super_pmd_val);
			flush_pmd_entry(pmd);

			addr += PMD_SIZE;
			pmd += 2;
		पूर्ण

		pfn += SUPERSECTION_SIZE >> PAGE_SHIFT;
	पूर्ण जबतक (addr < end);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम __iomem * __arm_ioremap_pfn_caller(अचिन्हित दीर्घ pfn,
	अचिन्हित दीर्घ offset, माप_प्रकार size, अचिन्हित पूर्णांक mtype, व्योम *caller)
अणु
	स्थिर काष्ठा mem_type *type;
	पूर्णांक err;
	अचिन्हित दीर्घ addr;
	काष्ठा vm_काष्ठा *area;
	phys_addr_t paddr = __pfn_to_phys(pfn);

#अगर_अघोषित CONFIG_ARM_LPAE
	/*
	 * High mappings must be supersection aligned
	 */
	अगर (pfn >= 0x100000 && (paddr & ~SUPERSECTION_MASK))
		वापस शून्य;
#पूर्ण_अगर

	type = get_mem_type(mtype);
	अगर (!type)
		वापस शून्य;

	/*
	 * Page align the mapping size, taking account of any offset.
	 */
	size = PAGE_ALIGN(offset + size);

	/*
	 * Try to reuse one of the अटल mapping whenever possible.
	 */
	अगर (size && !(माप(phys_addr_t) == 4 && pfn >= 0x100000)) अणु
		काष्ठा अटल_vm *svm;

		svm = find_अटल_vm_paddr(paddr, size, mtype);
		अगर (svm) अणु
			addr = (अचिन्हित दीर्घ)svm->vm.addr;
			addr += paddr - svm->vm.phys_addr;
			वापस (व्योम __iomem *) (offset + addr);
		पूर्ण
	पूर्ण

	/*
	 * Don't allow RAM to be mapped with mismatched attributes - this
	 * causes problems with ARMv6+
	 */
	अगर (WARN_ON(pfn_valid(pfn) && mtype != MT_MEMORY_RW))
		वापस शून्य;

	area = get_vm_area_caller(size, VM_IOREMAP, caller);
 	अगर (!area)
 		वापस शून्य;
 	addr = (अचिन्हित दीर्घ)area->addr;
	area->phys_addr = paddr;

#अगर !defined(CONFIG_SMP) && !defined(CONFIG_ARM_LPAE)
	अगर (DOMAIN_IO == 0 &&
	    (((cpu_architecture() >= CPU_ARCH_ARMv6) && (get_cr() & CR_XP)) ||
	       cpu_is_xsc3()) && pfn >= 0x100000 &&
	       !((paddr | size | addr) & ~SUPERSECTION_MASK)) अणु
		area->flags |= VM_ARM_SECTION_MAPPING;
		err = remap_area_supersections(addr, pfn, size, type);
	पूर्ण अन्यथा अगर (!((paddr | size | addr) & ~PMD_MASK)) अणु
		area->flags |= VM_ARM_SECTION_MAPPING;
		err = remap_area_sections(addr, pfn, size, type);
	पूर्ण अन्यथा
#पूर्ण_अगर
		err = ioremap_page_range(addr, addr + size, paddr,
					 __pgprot(type->prot_pte));

	अगर (err) अणु
 		vunmap((व्योम *)addr);
 		वापस शून्य;
 	पूर्ण

	flush_cache_vmap(addr, addr + size);
	वापस (व्योम __iomem *) (offset + addr);
पूर्ण

व्योम __iomem *__arm_ioremap_caller(phys_addr_t phys_addr, माप_प्रकार size,
	अचिन्हित पूर्णांक mtype, व्योम *caller)
अणु
	phys_addr_t last_addr;
 	अचिन्हित दीर्घ offset = phys_addr & ~PAGE_MASK;
 	अचिन्हित दीर्घ pfn = __phys_to_pfn(phys_addr);

 	/*
 	 * Don't allow wraparound or zero size
	 */
	last_addr = phys_addr + size - 1;
	अगर (!size || last_addr < phys_addr)
		वापस शून्य;

	वापस __arm_ioremap_pfn_caller(pfn, offset, size, mtype,
			caller);
पूर्ण

/*
 * Remap an arbitrary physical address space पूर्णांकo the kernel भव
 * address space. Needed when the kernel wants to access high addresses
 * directly.
 *
 * NOTE! We need to allow non-page-aligned mappings too: we will obviously
 * have to convert them पूर्णांकo an offset in a page-aligned mapping, but the
 * caller shouldn't need to know that small detail.
 */
व्योम __iomem *
__arm_ioremap_pfn(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ offset, माप_प्रकार size,
		  अचिन्हित पूर्णांक mtype)
अणु
	वापस __arm_ioremap_pfn_caller(pfn, offset, size, mtype,
					__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(__arm_ioremap_pfn);

व्योम __iomem * (*arch_ioremap_caller)(phys_addr_t, माप_प्रकार,
				      अचिन्हित पूर्णांक, व्योम *) =
	__arm_ioremap_caller;

व्योम __iomem *ioremap(resource_माप_प्रकार res_cookie, माप_प्रकार size)
अणु
	वापस arch_ioremap_caller(res_cookie, size, MT_DEVICE,
				   __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(ioremap);

व्योम __iomem *ioremap_cache(resource_माप_प्रकार res_cookie, माप_प्रकार size)
अणु
	वापस arch_ioremap_caller(res_cookie, size, MT_DEVICE_CACHED,
				   __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(ioremap_cache);

व्योम __iomem *ioremap_wc(resource_माप_प्रकार res_cookie, माप_प्रकार size)
अणु
	वापस arch_ioremap_caller(res_cookie, size, MT_DEVICE_WC,
				   __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(ioremap_wc);

/*
 * Remap an arbitrary physical address space पूर्णांकo the kernel भव
 * address space as memory. Needed when the kernel wants to execute
 * code in बाह्यal memory. This is needed क्रम reprogramming source
 * घड़ीs that would affect normal memory क्रम example. Please see
 * CONFIG_GENERIC_ALLOCATOR क्रम allocating बाह्यal memory.
 */
व्योम __iomem *
__arm_ioremap_exec(phys_addr_t phys_addr, माप_प्रकार size, bool cached)
अणु
	अचिन्हित पूर्णांक mtype;

	अगर (cached)
		mtype = MT_MEMORY_RWX;
	अन्यथा
		mtype = MT_MEMORY_RWX_NONCACHED;

	वापस __arm_ioremap_caller(phys_addr, size, mtype,
			__builtin_वापस_address(0));
पूर्ण

व्योम *arch_memremap_wb(phys_addr_t phys_addr, माप_प्रकार size)
अणु
	वापस (__क्रमce व्योम *)arch_ioremap_caller(phys_addr, size,
						   MT_MEMORY_RW,
						   __builtin_वापस_address(0));
पूर्ण

व्योम __iounmap(अस्थिर व्योम __iomem *io_addr)
अणु
	व्योम *addr = (व्योम *)(PAGE_MASK & (अचिन्हित दीर्घ)io_addr);
	काष्ठा अटल_vm *svm;

	/* If this is a अटल mapping, we must leave it alone */
	svm = find_अटल_vm_vaddr(addr);
	अगर (svm)
		वापस;

#अगर !defined(CONFIG_SMP) && !defined(CONFIG_ARM_LPAE)
	अणु
		काष्ठा vm_काष्ठा *vm;

		vm = find_vm_area(addr);

		/*
		 * If this is a section based mapping we need to handle it
		 * specially as the VM subप्रणाली करोes not know how to handle
		 * such a beast.
		 */
		अगर (vm && (vm->flags & VM_ARM_SECTION_MAPPING))
			unmap_area_sections((अचिन्हित दीर्घ)vm->addr, vm->size);
	पूर्ण
#पूर्ण_अगर

	vunmap(addr);
पूर्ण

व्योम (*arch_iounmap)(अस्थिर व्योम __iomem *) = __iounmap;

व्योम iounmap(अस्थिर व्योम __iomem *cookie)
अणु
	arch_iounmap(cookie);
पूर्ण
EXPORT_SYMBOL(iounmap);

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक pci_ioremap_mem_type = MT_DEVICE;

व्योम pci_ioremap_set_mem_type(पूर्णांक mem_type)
अणु
	pci_ioremap_mem_type = mem_type;
पूर्ण

पूर्णांक pci_ioremap_io(अचिन्हित पूर्णांक offset, phys_addr_t phys_addr)
अणु
	BUG_ON(offset + SZ_64K - 1 > IO_SPACE_LIMIT);

	वापस ioremap_page_range(PCI_IO_VIRT_BASE + offset,
				  PCI_IO_VIRT_BASE + offset + SZ_64K,
				  phys_addr,
				  __pgprot(get_mem_type(pci_ioremap_mem_type)->prot_pte));
पूर्ण
EXPORT_SYMBOL_GPL(pci_ioremap_io);

व्योम __iomem *pci_remap_cfgspace(resource_माप_प्रकार res_cookie, माप_प्रकार size)
अणु
	वापस arch_ioremap_caller(res_cookie, size, MT_UNCACHED,
				   __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL_GPL(pci_remap_cfgspace);
#पूर्ण_अगर

/*
 * Must be called after early_fixmap_init
 */
व्योम __init early_ioremap_init(व्योम)
अणु
	early_ioremap_setup();
पूर्ण

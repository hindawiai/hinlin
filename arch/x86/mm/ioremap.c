<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Re-map IO memory to kernel address space so that we can access it.
 * This is needed क्रम high PCI addresses that aren't mapped in the
 * 640k-1MB IO memory area on PC's
 *
 * (C) Copyright 1995 1996 Linus Torvalds
 */

#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mmiotrace.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/efi.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/setup.h>

#समावेश "physaddr.h"

/*
 * Descriptor controlling ioremap() behavior.
 */
काष्ठा ioremap_desc अणु
	अचिन्हित पूर्णांक flags;
पूर्ण;

/*
 * Fix up the linear direct mapping of the kernel to aव्योम cache attribute
 * conflicts.
 */
पूर्णांक ioremap_change_attr(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size,
			क्रमागत page_cache_mode pcm)
अणु
	अचिन्हित दीर्घ nrpages = size >> PAGE_SHIFT;
	पूर्णांक err;

	चयन (pcm) अणु
	हाल _PAGE_CACHE_MODE_UC:
	शेष:
		err = _set_memory_uc(vaddr, nrpages);
		अवरोध;
	हाल _PAGE_CACHE_MODE_WC:
		err = _set_memory_wc(vaddr, nrpages);
		अवरोध;
	हाल _PAGE_CACHE_MODE_WT:
		err = _set_memory_wt(vaddr, nrpages);
		अवरोध;
	हाल _PAGE_CACHE_MODE_WB:
		err = _set_memory_wb(vaddr, nrpages);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Does the range (or a subset of) contain normal RAM? */
अटल अचिन्हित पूर्णांक __ioremap_check_ram(काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ start_pfn, stop_pfn;
	अचिन्हित दीर्घ i;

	अगर ((res->flags & IORESOURCE_SYSTEM_RAM) != IORESOURCE_SYSTEM_RAM)
		वापस 0;

	start_pfn = (res->start + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stop_pfn = (res->end + 1) >> PAGE_SHIFT;
	अगर (stop_pfn > start_pfn) अणु
		क्रम (i = 0; i < (stop_pfn - start_pfn); ++i)
			अगर (pfn_valid(start_pfn + i) &&
			    !PageReserved(pfn_to_page(start_pfn + i)))
				वापस IORES_MAP_SYSTEM_RAM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * In a SEV guest, NONE and RESERVED should not be mapped encrypted because
 * there the whole memory is alपढ़ोy encrypted.
 */
अटल अचिन्हित पूर्णांक __ioremap_check_encrypted(काष्ठा resource *res)
अणु
	अगर (!sev_active())
		वापस 0;

	चयन (res->desc) अणु
	हाल IORES_DESC_NONE:
	हाल IORES_DESC_RESERVED:
		अवरोध;
	शेष:
		वापस IORES_MAP_ENCRYPTED;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The EFI runसमय services data area is not covered by walk_mem_res(), but must
 * be mapped encrypted when SEV is active.
 */
अटल व्योम __ioremap_check_other(resource_माप_प्रकार addr, काष्ठा ioremap_desc *desc)
अणु
	अगर (!sev_active())
		वापस;

	अगर (!IS_ENABLED(CONFIG_EFI))
		वापस;

	अगर (efi_mem_type(addr) == EFI_RUNTIME_SERVICES_DATA ||
	    (efi_mem_type(addr) == EFI_BOOT_SERVICES_DATA &&
	     efi_mem_attributes(addr) & EFI_MEMORY_RUNTIME))
		desc->flags |= IORES_MAP_ENCRYPTED;
पूर्ण

अटल पूर्णांक __ioremap_collect_map_flags(काष्ठा resource *res, व्योम *arg)
अणु
	काष्ठा ioremap_desc *desc = arg;

	अगर (!(desc->flags & IORES_MAP_SYSTEM_RAM))
		desc->flags |= __ioremap_check_ram(res);

	अगर (!(desc->flags & IORES_MAP_ENCRYPTED))
		desc->flags |= __ioremap_check_encrypted(res);

	वापस ((desc->flags & (IORES_MAP_SYSTEM_RAM | IORES_MAP_ENCRYPTED)) ==
			       (IORES_MAP_SYSTEM_RAM | IORES_MAP_ENCRYPTED));
पूर्ण

/*
 * To aव्योम multiple resource walks, this function walks resources marked as
 * IORESOURCE_MEM and IORESOURCE_BUSY and looking क्रम प्रणाली RAM and/or a
 * resource described not as IORES_DESC_NONE (e.g. IORES_DESC_ACPI_TABLES).
 *
 * After that, deal with misc other ranges in __ioremap_check_other() which करो
 * not fall पूर्णांकo the above category.
 */
अटल व्योम __ioremap_check_mem(resource_माप_प्रकार addr, अचिन्हित दीर्घ size,
				काष्ठा ioremap_desc *desc)
अणु
	u64 start, end;

	start = (u64)addr;
	end = start + size - 1;
	स_रखो(desc, 0, माप(काष्ठा ioremap_desc));

	walk_mem_res(start, end, desc, __ioremap_collect_map_flags);

	__ioremap_check_other(addr, desc);
पूर्ण

/*
 * Remap an arbitrary physical address space पूर्णांकo the kernel भव
 * address space. It transparently creates kernel huge I/O mapping when
 * the physical address is aligned by a huge page size (1GB or 2MB) and
 * the requested size is at least the huge page size.
 *
 * NOTE: MTRRs can override PAT memory types with a 4KB granularity.
 * Thereक्रमe, the mapping code falls back to use a smaller page toward 4KB
 * when a mapping range is covered by non-WB type of MTRRs.
 *
 * NOTE! We need to allow non-page-aligned mappings too: we will obviously
 * have to convert them पूर्णांकo an offset in a page-aligned mapping, but the
 * caller shouldn't need to know that small detail.
 */
अटल व्योम __iomem *
__ioremap_caller(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size,
		 क्रमागत page_cache_mode pcm, व्योम *caller, bool encrypted)
अणु
	अचिन्हित दीर्घ offset, vaddr;
	resource_माप_प्रकार last_addr;
	स्थिर resource_माप_प्रकार unaligned_phys_addr = phys_addr;
	स्थिर अचिन्हित दीर्घ unaligned_size = size;
	काष्ठा ioremap_desc io_desc;
	काष्ठा vm_काष्ठा *area;
	क्रमागत page_cache_mode new_pcm;
	pgprot_t prot;
	पूर्णांक retval;
	व्योम __iomem *ret_addr;

	/* Don't allow wraparound or zero size */
	last_addr = phys_addr + size - 1;
	अगर (!size || last_addr < phys_addr)
		वापस शून्य;

	अगर (!phys_addr_valid(phys_addr)) अणु
		prपूर्णांकk(KERN_WARNING "ioremap: invalid physical address %llx\n",
		       (अचिन्हित दीर्घ दीर्घ)phys_addr);
		WARN_ON_ONCE(1);
		वापस शून्य;
	पूर्ण

	__ioremap_check_mem(phys_addr, size, &io_desc);

	/*
	 * Don't allow anybody to remap normal RAM that we're using..
	 */
	अगर (io_desc.flags & IORES_MAP_SYSTEM_RAM) अणु
		WARN_ONCE(1, "ioremap on RAM at %pa - %pa\n",
			  &phys_addr, &last_addr);
		वापस शून्य;
	पूर्ण

	/*
	 * Mappings have to be page-aligned
	 */
	offset = phys_addr & ~PAGE_MASK;
	phys_addr &= PHYSICAL_PAGE_MASK;
	size = PAGE_ALIGN(last_addr+1) - phys_addr;

	retval = memtype_reserve(phys_addr, (u64)phys_addr + size,
						pcm, &new_pcm);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "ioremap memtype_reserve failed %d\n", retval);
		वापस शून्य;
	पूर्ण

	अगर (pcm != new_pcm) अणु
		अगर (!is_new_memtype_allowed(phys_addr, size, pcm, new_pcm)) अणु
			prपूर्णांकk(KERN_ERR
		"ioremap error for 0x%llx-0x%llx, requested 0x%x, got 0x%x\n",
				(अचिन्हित दीर्घ दीर्घ)phys_addr,
				(अचिन्हित दीर्घ दीर्घ)(phys_addr + size),
				pcm, new_pcm);
			जाओ err_मुक्त_memtype;
		पूर्ण
		pcm = new_pcm;
	पूर्ण

	/*
	 * If the page being mapped is in memory and SEV is active then
	 * make sure the memory encryption attribute is enabled in the
	 * resulting mapping.
	 */
	prot = PAGE_KERNEL_IO;
	अगर ((io_desc.flags & IORES_MAP_ENCRYPTED) || encrypted)
		prot = pgprot_encrypted(prot);

	चयन (pcm) अणु
	हाल _PAGE_CACHE_MODE_UC:
	शेष:
		prot = __pgprot(pgprot_val(prot) |
				cachemode2protval(_PAGE_CACHE_MODE_UC));
		अवरोध;
	हाल _PAGE_CACHE_MODE_UC_MINUS:
		prot = __pgprot(pgprot_val(prot) |
				cachemode2protval(_PAGE_CACHE_MODE_UC_MINUS));
		अवरोध;
	हाल _PAGE_CACHE_MODE_WC:
		prot = __pgprot(pgprot_val(prot) |
				cachemode2protval(_PAGE_CACHE_MODE_WC));
		अवरोध;
	हाल _PAGE_CACHE_MODE_WT:
		prot = __pgprot(pgprot_val(prot) |
				cachemode2protval(_PAGE_CACHE_MODE_WT));
		अवरोध;
	हाल _PAGE_CACHE_MODE_WB:
		अवरोध;
	पूर्ण

	/*
	 * Ok, go क्रम it..
	 */
	area = get_vm_area_caller(size, VM_IOREMAP, caller);
	अगर (!area)
		जाओ err_मुक्त_memtype;
	area->phys_addr = phys_addr;
	vaddr = (अचिन्हित दीर्घ) area->addr;

	अगर (memtype_kernel_map_sync(phys_addr, size, pcm))
		जाओ err_मुक्त_area;

	अगर (ioremap_page_range(vaddr, vaddr + size, phys_addr, prot))
		जाओ err_मुक्त_area;

	ret_addr = (व्योम __iomem *) (vaddr + offset);
	mmiotrace_ioremap(unaligned_phys_addr, unaligned_size, ret_addr);

	/*
	 * Check अगर the request spans more than any BAR in the iomem resource
	 * tree.
	 */
	अगर (iomem_map_sanity_check(unaligned_phys_addr, unaligned_size))
		pr_warn("caller %pS mapping multiple BARs\n", caller);

	वापस ret_addr;
err_मुक्त_area:
	मुक्त_vm_area(area);
err_मुक्त_memtype:
	memtype_मुक्त(phys_addr, phys_addr + size);
	वापस शून्य;
पूर्ण

/**
 * ioremap     -   map bus memory पूर्णांकo CPU space
 * @phys_addr:    bus address of the memory
 * @size:      size of the resource to map
 *
 * ioremap perक्रमms a platक्रमm specअगरic sequence of operations to
 * make bus memory CPU accessible via the पढ़ोb/पढ़ोw/पढ़ोl/ग_लिखोb/
 * ग_लिखोw/ग_लिखोl functions and the other mmio helpers. The वापसed
 * address is not guaranteed to be usable directly as a भव
 * address.
 *
 * This version of ioremap ensures that the memory is marked uncachable
 * on the CPU as well as honouring existing caching rules from things like
 * the PCI bus. Note that there are other caches and buffers on many
 * busses. In particular driver authors should पढ़ो up on PCI ग_लिखोs
 *
 * It's useful अगर some control रेजिस्टरs are in such an area and
 * ग_लिखो combining or पढ़ो caching is not desirable:
 *
 * Must be मुक्तd with iounmap.
 */
व्योम __iomem *ioremap(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	/*
	 * Ideally, this should be:
	 *	pat_enabled() ? _PAGE_CACHE_MODE_UC : _PAGE_CACHE_MODE_UC_MINUS;
	 *
	 * Till we fix all X drivers to use ioremap_wc(), we will use
	 * UC MINUS. Drivers that are certain they need or can alपढ़ोy
	 * be converted over to strong UC can use ioremap_uc().
	 */
	क्रमागत page_cache_mode pcm = _PAGE_CACHE_MODE_UC_MINUS;

	वापस __ioremap_caller(phys_addr, size, pcm,
				__builtin_वापस_address(0), false);
पूर्ण
EXPORT_SYMBOL(ioremap);

/**
 * ioremap_uc     -   map bus memory पूर्णांकo CPU space as strongly uncachable
 * @phys_addr:    bus address of the memory
 * @size:      size of the resource to map
 *
 * ioremap_uc perक्रमms a platक्रमm specअगरic sequence of operations to
 * make bus memory CPU accessible via the पढ़ोb/पढ़ोw/पढ़ोl/ग_लिखोb/
 * ग_लिखोw/ग_लिखोl functions and the other mmio helpers. The वापसed
 * address is not guaranteed to be usable directly as a भव
 * address.
 *
 * This version of ioremap ensures that the memory is marked with a strong
 * preference as completely uncachable on the CPU when possible. For non-PAT
 * प्रणालीs this ends up setting page-attribute flags PCD=1, PWT=1. For PAT
 * प्रणालीs this will set the PAT entry क्रम the pages as strong UC.  This call
 * will honor existing caching rules from things like the PCI bus. Note that
 * there are other caches and buffers on many busses. In particular driver
 * authors should पढ़ो up on PCI ग_लिखोs.
 *
 * It's useful अगर some control रेजिस्टरs are in such an area and
 * ग_लिखो combining or पढ़ो caching is not desirable:
 *
 * Must be मुक्तd with iounmap.
 */
व्योम __iomem *ioremap_uc(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	क्रमागत page_cache_mode pcm = _PAGE_CACHE_MODE_UC;

	वापस __ioremap_caller(phys_addr, size, pcm,
				__builtin_वापस_address(0), false);
पूर्ण
EXPORT_SYMBOL_GPL(ioremap_uc);

/**
 * ioremap_wc	-	map memory पूर्णांकo CPU space ग_लिखो combined
 * @phys_addr:	bus address of the memory
 * @size:	size of the resource to map
 *
 * This version of ioremap ensures that the memory is marked ग_लिखो combining.
 * Write combining allows faster ग_लिखोs to some hardware devices.
 *
 * Must be मुक्तd with iounmap.
 */
व्योम __iomem *ioremap_wc(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस __ioremap_caller(phys_addr, size, _PAGE_CACHE_MODE_WC,
					__builtin_वापस_address(0), false);
पूर्ण
EXPORT_SYMBOL(ioremap_wc);

/**
 * ioremap_wt	-	map memory पूर्णांकo CPU space ग_लिखो through
 * @phys_addr:	bus address of the memory
 * @size:	size of the resource to map
 *
 * This version of ioremap ensures that the memory is marked ग_लिखो through.
 * Write through stores data पूर्णांकo memory जबतक keeping the cache up-to-date.
 *
 * Must be मुक्तd with iounmap.
 */
व्योम __iomem *ioremap_wt(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस __ioremap_caller(phys_addr, size, _PAGE_CACHE_MODE_WT,
					__builtin_वापस_address(0), false);
पूर्ण
EXPORT_SYMBOL(ioremap_wt);

व्योम __iomem *ioremap_encrypted(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस __ioremap_caller(phys_addr, size, _PAGE_CACHE_MODE_WB,
				__builtin_वापस_address(0), true);
पूर्ण
EXPORT_SYMBOL(ioremap_encrypted);

व्योम __iomem *ioremap_cache(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस __ioremap_caller(phys_addr, size, _PAGE_CACHE_MODE_WB,
				__builtin_वापस_address(0), false);
पूर्ण
EXPORT_SYMBOL(ioremap_cache);

व्योम __iomem *ioremap_prot(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ prot_val)
अणु
	वापस __ioremap_caller(phys_addr, size,
				pgprot2cachemode(__pgprot(prot_val)),
				__builtin_वापस_address(0), false);
पूर्ण
EXPORT_SYMBOL(ioremap_prot);

/**
 * iounmap - Free a IO remapping
 * @addr: भव address from ioremap_*
 *
 * Caller must ensure there is only one unmapping क्रम the same poपूर्णांकer.
 */
व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
	काष्ठा vm_काष्ठा *p, *o;

	अगर ((व्योम __क्रमce *)addr <= high_memory)
		वापस;

	/*
	 * The PCI/ISA range special-casing was हटाओd from __ioremap()
	 * so this check, in theory, can be हटाओd. However, there are
	 * हालs where iounmap() is called क्रम addresses not obtained via
	 * ioremap() (vga16fb क्रम example). Add a warning so that these
	 * हालs can be caught and fixed.
	 */
	अगर ((व्योम __क्रमce *)addr >= phys_to_virt(ISA_START_ADDRESS) &&
	    (व्योम __क्रमce *)addr < phys_to_virt(ISA_END_ADDRESS)) अणु
		WARN(1, "iounmap() called for ISA range not obtained using ioremap()\n");
		वापस;
	पूर्ण

	mmiotrace_iounmap(addr);

	addr = (अस्थिर व्योम __iomem *)
		(PAGE_MASK & (अचिन्हित दीर्घ __क्रमce)addr);

	/* Use the vm area unlocked, assuming the caller
	   ensures there isn't another iounmap क्रम the same address
	   in parallel. Reuse of the भव address is prevented by
	   leaving it in the global lists until we're करोne with it.
	   cpa takes care of the direct mappings. */
	p = find_vm_area((व्योम __क्रमce *)addr);

	अगर (!p) अणु
		prपूर्णांकk(KERN_ERR "iounmap: bad address %p\n", addr);
		dump_stack();
		वापस;
	पूर्ण

	memtype_मुक्त(p->phys_addr, p->phys_addr + get_vm_area_size(p));

	/* Finally हटाओ it */
	o = हटाओ_vm_area((व्योम __क्रमce *)addr);
	BUG_ON(p != o || o == शून्य);
	kमुक्त(p);
पूर्ण
EXPORT_SYMBOL(iounmap);

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
व्योम *xlate_dev_mem_ptr(phys_addr_t phys)
अणु
	अचिन्हित दीर्घ start  = phys &  PAGE_MASK;
	अचिन्हित दीर्घ offset = phys & ~PAGE_MASK;
	व्योम *vaddr;

	/* memremap() maps अगर RAM, otherwise falls back to ioremap() */
	vaddr = memremap(start, PAGE_SIZE, MEMREMAP_WB);

	/* Only add the offset on success and वापस शून्य अगर memremap() failed */
	अगर (vaddr)
		vaddr += offset;

	वापस vaddr;
पूर्ण

व्योम unxlate_dev_mem_ptr(phys_addr_t phys, व्योम *addr)
अणु
	memunmap((व्योम *)((अचिन्हित दीर्घ)addr & PAGE_MASK));
पूर्ण

/*
 * Examine the physical address to determine अगर it is an area of memory
 * that should be mapped decrypted.  If the memory is not part of the
 * kernel usable area it was accessed and created decrypted, so these
 * areas should be mapped decrypted. And since the encryption key can
 * change across reboots, persistent memory should also be mapped
 * decrypted.
 *
 * If SEV is active, that implies that BIOS/UEFI also ran encrypted so
 * only persistent memory should be mapped decrypted.
 */
अटल bool memremap_should_map_decrypted(resource_माप_प्रकार phys_addr,
					  अचिन्हित दीर्घ size)
अणु
	पूर्णांक is_pmem;

	/*
	 * Check अगर the address is part of a persistent memory region.
	 * This check covers areas added by E820, EFI and ACPI.
	 */
	is_pmem = region_पूर्णांकersects(phys_addr, size, IORESOURCE_MEM,
				    IORES_DESC_PERSISTENT_MEMORY);
	अगर (is_pmem != REGION_DISJOINT)
		वापस true;

	/*
	 * Check अगर the non-अस्थिर attribute is set क्रम an EFI
	 * reserved area.
	 */
	अगर (efi_enabled(EFI_BOOT)) अणु
		चयन (efi_mem_type(phys_addr)) अणु
		हाल EFI_RESERVED_TYPE:
			अगर (efi_mem_attributes(phys_addr) & EFI_MEMORY_NV)
				वापस true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check अगर the address is outside kernel usable area */
	चयन (e820__get_entry_type(phys_addr, phys_addr + size - 1)) अणु
	हाल E820_TYPE_RESERVED:
	हाल E820_TYPE_ACPI:
	हाल E820_TYPE_NVS:
	हाल E820_TYPE_UNUSABLE:
		/* For SEV, these areas are encrypted */
		अगर (sev_active())
			अवरोध;
		fallthrough;

	हाल E820_TYPE_PRAM:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Examine the physical address to determine अगर it is EFI data. Check
 * it against the boot params काष्ठाure and EFI tables and memory types.
 */
अटल bool memremap_is_efi_data(resource_माप_प्रकार phys_addr,
				 अचिन्हित दीर्घ size)
अणु
	u64 paddr;

	/* Check अगर the address is part of EFI boot/runसमय data */
	अगर (!efi_enabled(EFI_BOOT))
		वापस false;

	paddr = boot_params.efi_info.efi_memmap_hi;
	paddr <<= 32;
	paddr |= boot_params.efi_info.efi_memmap;
	अगर (phys_addr == paddr)
		वापस true;

	paddr = boot_params.efi_info.efi_systab_hi;
	paddr <<= 32;
	paddr |= boot_params.efi_info.efi_systab;
	अगर (phys_addr == paddr)
		वापस true;

	अगर (efi_is_table_address(phys_addr))
		वापस true;

	चयन (efi_mem_type(phys_addr)) अणु
	हाल EFI_BOOT_SERVICES_DATA:
	हाल EFI_RUNTIME_SERVICES_DATA:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Examine the physical address to determine अगर it is boot data by checking
 * it against the boot params setup_data chain.
 */
अटल bool memremap_is_setup_data(resource_माप_प्रकार phys_addr,
				   अचिन्हित दीर्घ size)
अणु
	काष्ठा setup_data *data;
	u64 paddr, paddr_next;

	paddr = boot_params.hdr.setup_data;
	जबतक (paddr) अणु
		अचिन्हित पूर्णांक len;

		अगर (phys_addr == paddr)
			वापस true;

		data = memremap(paddr, माप(*data),
				MEMREMAP_WB | MEMREMAP_DEC);

		paddr_next = data->next;
		len = data->len;

		अगर ((phys_addr > paddr) && (phys_addr < (paddr + len))) अणु
			memunmap(data);
			वापस true;
		पूर्ण

		अगर (data->type == SETUP_INसूचीECT &&
		    ((काष्ठा setup_indirect *)data->data)->type != SETUP_INसूचीECT) अणु
			paddr = ((काष्ठा setup_indirect *)data->data)->addr;
			len = ((काष्ठा setup_indirect *)data->data)->len;
		पूर्ण

		memunmap(data);

		अगर ((phys_addr > paddr) && (phys_addr < (paddr + len)))
			वापस true;

		paddr = paddr_next;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Examine the physical address to determine अगर it is boot data by checking
 * it against the boot params setup_data chain (early boot version).
 */
अटल bool __init early_memremap_is_setup_data(resource_माप_प्रकार phys_addr,
						अचिन्हित दीर्घ size)
अणु
	काष्ठा setup_data *data;
	u64 paddr, paddr_next;

	paddr = boot_params.hdr.setup_data;
	जबतक (paddr) अणु
		अचिन्हित पूर्णांक len;

		अगर (phys_addr == paddr)
			वापस true;

		data = early_memremap_decrypted(paddr, माप(*data));

		paddr_next = data->next;
		len = data->len;

		early_memunmap(data, माप(*data));

		अगर ((phys_addr > paddr) && (phys_addr < (paddr + len)))
			वापस true;

		paddr = paddr_next;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Architecture function to determine अगर RAM remap is allowed. By शेष, a
 * RAM remap will map the data as encrypted. Determine अगर a RAM remap should
 * not be करोne so that the data will be mapped decrypted.
 */
bool arch_memremap_can_ram_remap(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size,
				 अचिन्हित दीर्घ flags)
अणु
	अगर (!mem_encrypt_active())
		वापस true;

	अगर (flags & MEMREMAP_ENC)
		वापस true;

	अगर (flags & MEMREMAP_DEC)
		वापस false;

	अगर (sme_active()) अणु
		अगर (memremap_is_setup_data(phys_addr, size) ||
		    memremap_is_efi_data(phys_addr, size))
			वापस false;
	पूर्ण

	वापस !memremap_should_map_decrypted(phys_addr, size);
पूर्ण

/*
 * Architecture override of __weak function to adjust the protection attributes
 * used when remapping memory. By शेष, early_memremap() will map the data
 * as encrypted. Determine अगर an encrypted mapping should not be करोne and set
 * the appropriate protection attributes.
 */
pgprot_t __init early_memremap_pgprot_adjust(resource_माप_प्रकार phys_addr,
					     अचिन्हित दीर्घ size,
					     pgprot_t prot)
अणु
	bool encrypted_prot;

	अगर (!mem_encrypt_active())
		वापस prot;

	encrypted_prot = true;

	अगर (sme_active()) अणु
		अगर (early_memremap_is_setup_data(phys_addr, size) ||
		    memremap_is_efi_data(phys_addr, size))
			encrypted_prot = false;
	पूर्ण

	अगर (encrypted_prot && memremap_should_map_decrypted(phys_addr, size))
		encrypted_prot = false;

	वापस encrypted_prot ? pgprot_encrypted(prot)
			      : pgprot_decrypted(prot);
पूर्ण

bool phys_mem_access_encrypted(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस arch_memremap_can_ram_remap(phys_addr, size, 0);
पूर्ण

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
/* Remap memory with encryption */
व्योम __init *early_memremap_encrypted(resource_माप_प्रकार phys_addr,
				      अचिन्हित दीर्घ size)
अणु
	वापस early_memremap_prot(phys_addr, size, __PAGE_KERNEL_ENC);
पूर्ण

/*
 * Remap memory with encryption and ग_लिखो-रक्षित - cannot be called
 * beक्रमe pat_init() is called
 */
व्योम __init *early_memremap_encrypted_wp(resource_माप_प्रकार phys_addr,
					 अचिन्हित दीर्घ size)
अणु
	अगर (!x86_has_pat_wp())
		वापस शून्य;
	वापस early_memremap_prot(phys_addr, size, __PAGE_KERNEL_ENC_WP);
पूर्ण

/* Remap memory without encryption */
व्योम __init *early_memremap_decrypted(resource_माप_प्रकार phys_addr,
				      अचिन्हित दीर्घ size)
अणु
	वापस early_memremap_prot(phys_addr, size, __PAGE_KERNEL_NOENC);
पूर्ण

/*
 * Remap memory without encryption and ग_लिखो-रक्षित - cannot be called
 * beक्रमe pat_init() is called
 */
व्योम __init *early_memremap_decrypted_wp(resource_माप_प्रकार phys_addr,
					 अचिन्हित दीर्घ size)
अणु
	अगर (!x86_has_pat_wp())
		वापस शून्य;
	वापस early_memremap_prot(phys_addr, size, __PAGE_KERNEL_NOENC_WP);
पूर्ण
#पूर्ण_अगर	/* CONFIG_AMD_MEM_ENCRYPT */

अटल pte_t bm_pte[PAGE_SIZE/माप(pte_t)] __page_aligned_bss;

अटल अंतरभूत pmd_t * __init early_ioremap_pmd(अचिन्हित दीर्घ addr)
अणु
	/* Don't assume we're using swapper_pg_dir at this poपूर्णांक */
	pgd_t *base = __va(पढ़ो_cr3_pa());
	pgd_t *pgd = &base[pgd_index(addr)];
	p4d_t *p4d = p4d_offset(pgd, addr);
	pud_t *pud = pud_offset(p4d, addr);
	pmd_t *pmd = pmd_offset(pud, addr);

	वापस pmd;
पूर्ण

अटल अंतरभूत pte_t * __init early_ioremap_pte(अचिन्हित दीर्घ addr)
अणु
	वापस &bm_pte[pte_index(addr)];
पूर्ण

bool __init is_early_ioremap_ptep(pte_t *ptep)
अणु
	वापस ptep >= &bm_pte[0] && ptep < &bm_pte[PAGE_SIZE/माप(pte_t)];
पूर्ण

व्योम __init early_ioremap_init(व्योम)
अणु
	pmd_t *pmd;

#अगर_घोषित CONFIG_X86_64
	BUILD_BUG_ON((fix_to_virt(0) + PAGE_SIZE) & ((1 << PMD_SHIFT) - 1));
#अन्यथा
	WARN_ON((fix_to_virt(0) + PAGE_SIZE) & ((1 << PMD_SHIFT) - 1));
#पूर्ण_अगर

	early_ioremap_setup();

	pmd = early_ioremap_pmd(fix_to_virt(FIX_BTMAP_BEGIN));
	स_रखो(bm_pte, 0, माप(bm_pte));
	pmd_populate_kernel(&init_mm, pmd, bm_pte);

	/*
	 * The boot-ioremap range spans multiple pmds, क्रम which
	 * we are not prepared:
	 */
#घोषणा __FIXADDR_TOP (-PAGE_SIZE)
	BUILD_BUG_ON((__fix_to_virt(FIX_BTMAP_BEGIN) >> PMD_SHIFT)
		     != (__fix_to_virt(FIX_BTMAP_END) >> PMD_SHIFT));
#अघोषित __FIXADDR_TOP
	अगर (pmd != early_ioremap_pmd(fix_to_virt(FIX_BTMAP_END))) अणु
		WARN_ON(1);
		prपूर्णांकk(KERN_WARNING "pmd %p != %p\n",
		       pmd, early_ioremap_pmd(fix_to_virt(FIX_BTMAP_END)));
		prपूर्णांकk(KERN_WARNING "fix_to_virt(FIX_BTMAP_BEGIN): %08lx\n",
			fix_to_virt(FIX_BTMAP_BEGIN));
		prपूर्णांकk(KERN_WARNING "fix_to_virt(FIX_BTMAP_END):   %08lx\n",
			fix_to_virt(FIX_BTMAP_END));

		prपूर्णांकk(KERN_WARNING "FIX_BTMAP_END:       %d\n", FIX_BTMAP_END);
		prपूर्णांकk(KERN_WARNING "FIX_BTMAP_BEGIN:     %d\n",
		       FIX_BTMAP_BEGIN);
	पूर्ण
पूर्ण

व्योम __init __early_set_fixmap(क्रमागत fixed_addresses idx,
			       phys_addr_t phys, pgprot_t flags)
अणु
	अचिन्हित दीर्घ addr = __fix_to_virt(idx);
	pte_t *pte;

	अगर (idx >= __end_of_fixed_addresses) अणु
		BUG();
		वापस;
	पूर्ण
	pte = early_ioremap_pte(addr);

	/* Sanitize 'prot' against any unsupported bits: */
	pgprot_val(flags) &= __supported_pte_mask;

	अगर (pgprot_val(flags))
		set_pte(pte, pfn_pte(phys >> PAGE_SHIFT, flags));
	अन्यथा
		pte_clear(&init_mm, addr, pte);
	flush_tlb_one_kernel(addr);
पूर्ण

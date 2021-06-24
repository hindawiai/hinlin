<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Dave Engebretsen <engebret@us.ibm.com>
 *      Rework क्रम PPC64 port.
 */

#अघोषित DEBUG

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/idr.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/module.h>
#समावेश <linux/poison.h>
#समावेश <linux/memblock.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/memremap.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmu.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/eeh.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/vdso.h>

#समावेश <mm/mmu_decl.h>

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
/*
 * Given an address within the vmemmap, determine the page that
 * represents the start of the subsection it is within.  Note that we have to
 * करो this by hand as the proffered address may not be correctly aligned.
 * Subtraction of non-aligned poपूर्णांकers produces undefined results.
 */
अटल काष्ठा page * __meminit vmemmap_subsection_start(अचिन्हित दीर्घ vmemmap_addr)
अणु
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ offset = vmemmap_addr - ((अचिन्हित दीर्घ)(vmemmap));

	/* Return the pfn of the start of the section. */
	start_pfn = (offset / माप(काष्ठा page)) & PAGE_SUBSECTION_MASK;
	वापस pfn_to_page(start_pfn);
पूर्ण

/*
 * Since memory is added in sub-section chunks, beक्रमe creating a new vmemmap
 * mapping, the kernel should check whether there is an existing memmap mapping
 * covering the new subsection added. This is needed because kernel can map
 * vmemmap area using 16MB pages which will cover a memory range of 16G. Such
 * a range covers multiple subsections (2M)
 *
 * If any subsection in the 16G range mapped by vmemmap is valid we consider the
 * vmemmap populated (There is a page table entry alपढ़ोy present). We can't करो
 * a page table lookup here because with the hash translation we करोn't keep
 * vmemmap details in linux page table.
 */
अटल पूर्णांक __meminit vmemmap_populated(अचिन्हित दीर्घ vmemmap_addr, पूर्णांक vmemmap_map_size)
अणु
	काष्ठा page *start;
	अचिन्हित दीर्घ vmemmap_end = vmemmap_addr + vmemmap_map_size;
	start = vmemmap_subsection_start(vmemmap_addr);

	क्रम (; (अचिन्हित दीर्घ)start < vmemmap_end; start += PAGES_PER_SUBSECTION)
		/*
		 * pfn valid check here is पूर्णांकended to really check
		 * whether we have any subsection alपढ़ोy initialized
		 * in this range.
		 */
		अगर (pfn_valid(page_to_pfn(start)))
			वापस 1;

	वापस 0;
पूर्ण

/*
 * vmemmap भव address space management करोes not have a traditonal page
 * table to track which भव काष्ठा pages are backed by physical mapping.
 * The भव to physical mappings are tracked in a simple linked list
 * क्रमmat. 'vmemmap_list' मुख्यtains the entire vmemmap physical mapping at
 * all बार where as the 'next' list मुख्यtains the available
 * vmemmap_backing काष्ठाures which have been deleted from the
 * 'vmemmap_global' list during प्रणाली runसमय (memory hotplug हटाओ
 * operation). The मुक्तd 'vmemmap_backing' काष्ठाures are reused later when
 * new requests come in without allocating fresh memory. This poपूर्णांकer also
 * tracks the allocated 'vmemmap_backing' काष्ठाures as we allocate one
 * full page memory at a समय when we करोnt have any.
 */
काष्ठा vmemmap_backing *vmemmap_list;
अटल काष्ठा vmemmap_backing *next;

/*
 * The same poपूर्णांकer 'next' tracks inभागidual chunks inside the allocated
 * full page during the boot समय and again tracks the मुक्तed nodes during
 * runसमय. It is racy but it करोes not happen as they are separated by the
 * boot process. Will create problem अगर some how we have memory hotplug
 * operation during boot !!
 */
अटल पूर्णांक num_left;
अटल पूर्णांक num_मुक्तd;

अटल __meminit काष्ठा vmemmap_backing * vmemmap_list_alloc(पूर्णांक node)
अणु
	काष्ठा vmemmap_backing *vmem_back;
	/* get from मुक्तd entries first */
	अगर (num_मुक्तd) अणु
		num_मुक्तd--;
		vmem_back = next;
		next = next->list;

		वापस vmem_back;
	पूर्ण

	/* allocate a page when required and hand out chunks */
	अगर (!num_left) अणु
		next = vmemmap_alloc_block(PAGE_SIZE, node);
		अगर (unlikely(!next)) अणु
			WARN_ON(1);
			वापस शून्य;
		पूर्ण
		num_left = PAGE_SIZE / माप(काष्ठा vmemmap_backing);
	पूर्ण

	num_left--;

	वापस next++;
पूर्ण

अटल __meminit पूर्णांक vmemmap_list_populate(अचिन्हित दीर्घ phys,
					   अचिन्हित दीर्घ start,
					   पूर्णांक node)
अणु
	काष्ठा vmemmap_backing *vmem_back;

	vmem_back = vmemmap_list_alloc(node);
	अगर (unlikely(!vmem_back)) अणु
		pr_debug("vmemap list allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	vmem_back->phys = phys;
	vmem_back->virt_addr = start;
	vmem_back->list = vmemmap_list;

	vmemmap_list = vmem_back;
	वापस 0;
पूर्ण

अटल bool alपंचांगap_cross_boundary(काष्ठा vmem_alपंचांगap *alपंचांगap, अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ page_size)
अणु
	अचिन्हित दीर्घ nr_pfn = page_size / माप(काष्ठा page);
	अचिन्हित दीर्घ start_pfn = page_to_pfn((काष्ठा page *)start);

	अगर ((start_pfn + nr_pfn) > alपंचांगap->end_pfn)
		वापस true;

	अगर (start_pfn < alपंचांगap->base_pfn)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक __meminit vmemmap_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक node,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	bool alपंचांगap_alloc;
	अचिन्हित दीर्घ page_size = 1 << mmu_psize_defs[mmu_vmemmap_psize].shअगरt;

	/* Align to the page size of the linear mapping. */
	start = ALIGN_DOWN(start, page_size);

	pr_debug("vmemmap_populate %lx..%lx, node %d\n", start, end, node);

	क्रम (; start < end; start += page_size) अणु
		व्योम *p = शून्य;
		पूर्णांक rc;

		/*
		 * This vmemmap range is backing dअगरferent subsections. If any
		 * of that subsection is marked valid, that means we alपढ़ोy
		 * have initialized a page table covering this range and hence
		 * the vmemmap range is populated.
		 */
		अगर (vmemmap_populated(start, page_size))
			जारी;

		/*
		 * Allocate from the alपंचांगap first अगर we have one. This may
		 * fail due to alignment issues when using 16MB hugepages, so
		 * fall back to प्रणाली memory अगर the alपंचांगap allocation fail.
		 */
		अगर (alपंचांगap && !alपंचांगap_cross_boundary(alपंचांगap, start, page_size)) अणु
			p = vmemmap_alloc_block_buf(page_size, node, alपंचांगap);
			अगर (!p)
				pr_debug("altmap block allocation failed, falling back to system memory");
			अन्यथा
				alपंचांगap_alloc = true;
		पूर्ण
		अगर (!p) अणु
			p = vmemmap_alloc_block_buf(page_size, node, शून्य);
			alपंचांगap_alloc = false;
		पूर्ण
		अगर (!p)
			वापस -ENOMEM;

		अगर (vmemmap_list_populate(__pa(p), start, node)) अणु
			/*
			 * If we करोn't populate vmemap list, we don't have
			 * the ability to मुक्त the allocated vmemmap
			 * pages in section_deactivate. Hence मुक्त them
			 * here.
			 */
			पूर्णांक nr_pfns = page_size >> PAGE_SHIFT;
			अचिन्हित दीर्घ page_order = get_order(page_size);

			अगर (alपंचांगap_alloc)
				vmem_alपंचांगap_मुक्त(alपंचांगap, nr_pfns);
			अन्यथा
				मुक्त_pages((अचिन्हित दीर्घ)p, page_order);
			वापस -ENOMEM;
		पूर्ण

		pr_debug("      * %016lx..%016lx allocated at %p\n",
			 start, start + page_size, p);

		rc = vmemmap_create_mapping(start, page_size, __pa(p));
		अगर (rc < 0) अणु
			pr_warn("%s: Unable to create vmemmap mapping: %d\n",
				__func__, rc);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल अचिन्हित दीर्घ vmemmap_list_मुक्त(अचिन्हित दीर्घ start)
अणु
	काष्ठा vmemmap_backing *vmem_back, *vmem_back_prev;

	vmem_back_prev = vmem_back = vmemmap_list;

	/* look क्रम it with prev poपूर्णांकer recorded */
	क्रम (; vmem_back; vmem_back = vmem_back->list) अणु
		अगर (vmem_back->virt_addr == start)
			अवरोध;
		vmem_back_prev = vmem_back;
	पूर्ण

	अगर (unlikely(!vmem_back))
		वापस 0;

	/* हटाओ it from vmemmap_list */
	अगर (vmem_back == vmemmap_list) /* हटाओ head */
		vmemmap_list = vmem_back->list;
	अन्यथा
		vmem_back_prev->list = vmem_back->list;

	/* next poपूर्णांक to this मुक्तd entry */
	vmem_back->list = next;
	next = vmem_back;
	num_मुक्तd++;

	वापस vmem_back->phys;
पूर्ण

व्योम __ref vmemmap_मुक्त(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ page_size = 1 << mmu_psize_defs[mmu_vmemmap_psize].shअगरt;
	अचिन्हित दीर्घ page_order = get_order(page_size);
	अचिन्हित दीर्घ alt_start = ~0, alt_end = ~0;
	अचिन्हित दीर्घ base_pfn;

	start = ALIGN_DOWN(start, page_size);
	अगर (alपंचांगap) अणु
		alt_start = alपंचांगap->base_pfn;
		alt_end = alपंचांगap->base_pfn + alपंचांगap->reserve +
			  alपंचांगap->मुक्त + alपंचांगap->alloc + alपंचांगap->align;
	पूर्ण

	pr_debug("vmemmap_free %lx...%lx\n", start, end);

	क्रम (; start < end; start += page_size) अणु
		अचिन्हित दीर्घ nr_pages, addr;
		काष्ठा page *page;

		/*
		 * We have alपढ़ोy marked the subsection we are trying to हटाओ
		 * invalid. So अगर we want to हटाओ the vmemmap range, we
		 * need to make sure there is no subsection marked valid
		 * in this range.
		 */
		अगर (vmemmap_populated(start, page_size))
			जारी;

		addr = vmemmap_list_मुक्त(start);
		अगर (!addr)
			जारी;

		page = pfn_to_page(addr >> PAGE_SHIFT);
		nr_pages = 1 << page_order;
		base_pfn = PHYS_PFN(addr);

		अगर (base_pfn >= alt_start && base_pfn < alt_end) अणु
			vmem_alपंचांगap_मुक्त(alपंचांगap, nr_pages);
		पूर्ण अन्यथा अगर (PageReserved(page)) अणु
			/* allocated from booपंचांगem */
			अगर (page_size < PAGE_SIZE) अणु
				/*
				 * this shouldn't happen, but अगर it is
				 * the हाल, leave the memory there
				 */
				WARN_ON_ONCE(1);
			पूर्ण अन्यथा अणु
				जबतक (nr_pages--)
					मुक्त_reserved_page(page++);
			पूर्ण
		पूर्ण अन्यथा अणु
			मुक्त_pages((अचिन्हित दीर्घ)(__va(addr)), page_order);
		पूर्ण

		vmemmap_हटाओ_mapping(start, page_size);
	पूर्ण
पूर्ण
#पूर्ण_अगर
व्योम रेजिस्टर_page_booपंचांगem_memmap(अचिन्हित दीर्घ section_nr,
				  काष्ठा page *start_page, अचिन्हित दीर्घ size)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_SPARSEMEM_VMEMMAP */

#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल bool disable_radix = !IS_ENABLED(CONFIG_PPC_RADIX_MMU_DEFAULT);

अटल पूर्णांक __init parse_disable_radix(अक्षर *p)
अणु
	bool val;

	अगर (!p)
		val = true;
	अन्यथा अगर (kstrtobool(p, &val))
		वापस -EINVAL;

	disable_radix = val;

	वापस 0;
पूर्ण
early_param("disable_radix", parse_disable_radix);

/*
 * If we're running under a hypervisor, we need to check the contents of
 * /chosen/ibm,architecture-vec-5 to see अगर the hypervisor is willing to करो
 * radix.  If not, we clear the radix feature bit so we fall back to hash.
 */
अटल व्योम __init early_check_vec5(व्योम)
अणु
	अचिन्हित दीर्घ root, chosen;
	पूर्णांक size;
	स्थिर u8 *vec5;
	u8 mmu_supported;

	root = of_get_flat_dt_root();
	chosen = of_get_flat_dt_subnode_by_name(root, "chosen");
	अगर (chosen == -FDT_ERR_NOTFOUND) अणु
		cur_cpu_spec->mmu_features &= ~MMU_FTR_TYPE_RADIX;
		वापस;
	पूर्ण
	vec5 = of_get_flat_dt_prop(chosen, "ibm,architecture-vec-5", &size);
	अगर (!vec5) अणु
		cur_cpu_spec->mmu_features &= ~MMU_FTR_TYPE_RADIX;
		वापस;
	पूर्ण
	अगर (size <= OV5_INDX(OV5_MMU_SUPPORT)) अणु
		cur_cpu_spec->mmu_features &= ~MMU_FTR_TYPE_RADIX;
		वापस;
	पूर्ण

	/* Check क्रम supported configuration */
	mmu_supported = vec5[OV5_INDX(OV5_MMU_SUPPORT)] &
			OV5_FEAT(OV5_MMU_SUPPORT);
	अगर (mmu_supported == OV5_FEAT(OV5_MMU_RADIX)) अणु
		/* Hypervisor only supports radix - check enabled && GTSE */
		अगर (!early_radix_enabled()) अणु
			pr_warn("WARNING: Ignoring cmdline option disable_radix\n");
		पूर्ण
		अगर (!(vec5[OV5_INDX(OV5_RADIX_GTSE)] &
						OV5_FEAT(OV5_RADIX_GTSE))) अणु
			cur_cpu_spec->mmu_features &= ~MMU_FTR_GTSE;
		पूर्ण अन्यथा
			cur_cpu_spec->mmu_features |= MMU_FTR_GTSE;
		/* Do radix anyway - the hypervisor said we had to */
		cur_cpu_spec->mmu_features |= MMU_FTR_TYPE_RADIX;
	पूर्ण अन्यथा अगर (mmu_supported == OV5_FEAT(OV5_MMU_HASH)) अणु
		/* Hypervisor only supports hash - disable radix */
		cur_cpu_spec->mmu_features &= ~MMU_FTR_TYPE_RADIX;
		cur_cpu_spec->mmu_features &= ~MMU_FTR_GTSE;
	पूर्ण
पूर्ण

व्योम __init mmu_early_init_devtree(व्योम)
अणु
	/* Disable radix mode based on kernel command line. */
	अगर (disable_radix)
		cur_cpu_spec->mmu_features &= ~MMU_FTR_TYPE_RADIX;

	/*
	 * Check /chosen/ibm,architecture-vec-5 अगर running as a guest.
	 * When running bare-metal, we can use radix अगर we like
	 * even though the ibm,architecture-vec-5 property created by
	 * skiboot करोesn't have the necessary bits set.
	 */
	अगर (!(mfmsr() & MSR_HV))
		early_check_vec5();

	अगर (early_radix_enabled()) अणु
		radix__early_init_devtree();
		/*
		 * We have finalized the translation we are going to use by now.
		 * Radix mode is not limited by RMA / VRMA addressing.
		 * Hence करोn't limit memblock allocations.
		 */
		ppc64_rma_size = अच_दीर्घ_उच्च;
		memblock_set_current_limit(MEMBLOCK_ALLOC_ANYWHERE);
	पूर्ण अन्यथा
		hash__early_init_devtree();
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

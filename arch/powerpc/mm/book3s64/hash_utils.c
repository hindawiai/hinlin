<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerPC64 port by Mike Corrigan and Dave Engebretsen
 *   अणुmikejc|engebretपूर्ण@us.ibm.com
 *
 *    Copyright (c) 2000 Mike Corrigan <mikejc@us.ibm.com>
 *
 * SMP scalability work:
 *    Copyright (C) 2001 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 *
 *    Module name: htab.c
 *
 *    Description:
 *      PowerPC Hashed Page Table functions
 */

#अघोषित DEBUG
#अघोषित DEBUG_LOW

#घोषणा pr_fmt(fmt) "hash-mmu: " fmt
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/export.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/cache.h>
#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/memblock.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/pkeys.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/eeh.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/copro.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/पंचांग.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/ps3.h>
#समावेश <यंत्र/pte-walk.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/ultravisor.h>

#समावेश <mm/mmu_decl.h>

#समावेश "internal.h"


#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_LOW
#घोषणा DBG_LOW(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG_LOW(fmt...)
#पूर्ण_अगर

#घोषणा KB (1024)
#घोषणा MB (1024*KB)
#घोषणा GB (1024L*MB)

/*
 * Note:  pte   --> Linux PTE
 *        HPTE  --> PowerPC Hashed Page Table Entry
 *
 * Execution context:
 *   htab_initialize is called with the MMU off (of course), but
 *   the kernel has been copied करोwn to zero so it can directly
 *   reference global data.  At this poपूर्णांक it is very dअगरficult
 *   to prपूर्णांक debug info.
 *
 */

अटल अचिन्हित दीर्घ _SDR1;
काष्ठा mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT];
EXPORT_SYMBOL_GPL(mmu_psize_defs);

u8 hpte_page_sizes[1 << LP_BITS];
EXPORT_SYMBOL_GPL(hpte_page_sizes);

काष्ठा hash_pte *htab_address;
अचिन्हित दीर्घ htab_size_bytes;
अचिन्हित दीर्घ htab_hash_mask;
EXPORT_SYMBOL_GPL(htab_hash_mask);
पूर्णांक mmu_linear_psize = MMU_PAGE_4K;
EXPORT_SYMBOL_GPL(mmu_linear_psize);
पूर्णांक mmu_भव_psize = MMU_PAGE_4K;
पूर्णांक mmu_vदो_स्मृति_psize = MMU_PAGE_4K;
EXPORT_SYMBOL_GPL(mmu_vदो_स्मृति_psize);
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
पूर्णांक mmu_vmemmap_psize = MMU_PAGE_4K;
#पूर्ण_अगर
पूर्णांक mmu_io_psize = MMU_PAGE_4K;
पूर्णांक mmu_kernel_ssize = MMU_SEGSIZE_256M;
EXPORT_SYMBOL_GPL(mmu_kernel_ssize);
पूर्णांक mmu_highuser_ssize = MMU_SEGSIZE_256M;
u16 mmu_slb_size = 64;
EXPORT_SYMBOL_GPL(mmu_slb_size);
#अगर_घोषित CONFIG_PPC_64K_PAGES
पूर्णांक mmu_ci_restrictions;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
अटल u8 *linear_map_hash_slots;
अटल अचिन्हित दीर्घ linear_map_hash_count;
अटल DEFINE_SPINLOCK(linear_map_hash_lock);
#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */
काष्ठा mmu_hash_ops mmu_hash_ops;
EXPORT_SYMBOL(mmu_hash_ops);

/*
 * These are definitions of page sizes arrays to be used when none
 * is provided by the firmware.
 */

/*
 * Fallback (4k pages only)
 */
अटल काष्ठा mmu_psize_def mmu_psize_शेषs[] = अणु
	[MMU_PAGE_4K] = अणु
		.shअगरt	= 12,
		.sllp	= 0,
		.penc   = अणु[MMU_PAGE_4K] = 0, [1 ... MMU_PAGE_COUNT - 1] = -1पूर्ण,
		.avpnm	= 0,
		.tlbiel = 0,
	पूर्ण,
पूर्ण;

/*
 * POWER4, GPUL, POWER5
 *
 * Support क्रम 16Mb large pages
 */
अटल काष्ठा mmu_psize_def mmu_psize_शेषs_gp[] = अणु
	[MMU_PAGE_4K] = अणु
		.shअगरt	= 12,
		.sllp	= 0,
		.penc   = अणु[MMU_PAGE_4K] = 0, [1 ... MMU_PAGE_COUNT - 1] = -1पूर्ण,
		.avpnm	= 0,
		.tlbiel = 1,
	पूर्ण,
	[MMU_PAGE_16M] = अणु
		.shअगरt	= 24,
		.sllp	= SLB_VSID_L,
		.penc   = अणु[0 ... MMU_PAGE_16M - 1] = -1, [MMU_PAGE_16M] = 0,
			    [MMU_PAGE_16M + 1 ... MMU_PAGE_COUNT - 1] = -1 पूर्ण,
		.avpnm	= 0x1UL,
		.tlbiel = 0,
	पूर्ण,
पूर्ण;

/*
 * 'R' and 'C' update notes:
 *  - Under pHyp or KVM, the updatepp path will not set C, thus it *will*
 *     create ग_लिखोable HPTEs without C set, because the hcall H_PROTECT
 *     that we use in that हाल will not update C
 *  - The above is however not a problem, because we also करोn't करो that
 *     fancy "no flush" variant of eviction and we use H_REMOVE which will
 *     करो the right thing and thus we करोn't have the race I described earlier
 *
 *    - Under bare metal,  we करो have the race, so we need R and C set
 *    - We make sure R is always set and never lost
 *    - C is _PAGE_सूचीTY, and *should* always be set क्रम a ग_लिखोable mapping
 */
अचिन्हित दीर्घ htab_convert_pte_flags(अचिन्हित दीर्घ pteflags, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ rflags = 0;

	/* _PAGE_EXEC -> NOEXEC */
	अगर ((pteflags & _PAGE_EXEC) == 0)
		rflags |= HPTE_R_N;
	/*
	 * PPP bits:
	 * Linux uses slb key 0 क्रम kernel and 1 क्रम user.
	 * kernel RW areas are mapped with PPP=0b000
	 * User area is mapped with PPP=0b010 क्रम पढ़ो/ग_लिखो
	 * or PPP=0b011 क्रम पढ़ो-only (including ग_लिखोable but clean pages).
	 */
	अगर (pteflags & _PAGE_PRIVILEGED) अणु
		/*
		 * Kernel पढ़ो only mapped with ppp bits 0b110
		 */
		अगर (!(pteflags & _PAGE_WRITE)) अणु
			अगर (mmu_has_feature(MMU_FTR_KERNEL_RO))
				rflags |= (HPTE_R_PP0 | 0x2);
			अन्यथा
				rflags |= 0x3;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pteflags & _PAGE_RWX)
			rflags |= 0x2;
		अगर (!((pteflags & _PAGE_WRITE) && (pteflags & _PAGE_सूचीTY)))
			rflags |= 0x1;
	पूर्ण
	/*
	 * We can't allow hardware to update hpte bits. Hence always
	 * set 'R' bit and set 'C' अगर it is a ग_लिखो fault
	 */
	rflags |=  HPTE_R_R;

	अगर (pteflags & _PAGE_सूचीTY)
		rflags |= HPTE_R_C;
	/*
	 * Add in WIG bits
	 */

	अगर ((pteflags & _PAGE_CACHE_CTL) == _PAGE_TOLERANT)
		rflags |= HPTE_R_I;
	अन्यथा अगर ((pteflags & _PAGE_CACHE_CTL) == _PAGE_NON_IDEMPOTENT)
		rflags |= (HPTE_R_I | HPTE_R_G);
	अन्यथा अगर ((pteflags & _PAGE_CACHE_CTL) == _PAGE_SAO)
		rflags |= (HPTE_R_W | HPTE_R_I | HPTE_R_M);
	अन्यथा
		/*
		 * Add memory coherence अगर cache inhibited is not set
		 */
		rflags |= HPTE_R_M;

	rflags |= pte_to_hpte_pkey_bits(pteflags, flags);
	वापस rflags;
पूर्ण

पूर्णांक htab_bolt_mapping(अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
		      अचिन्हित दीर्घ pstart, अचिन्हित दीर्घ prot,
		      पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ vaddr, paddr;
	अचिन्हित पूर्णांक step, shअगरt;
	पूर्णांक ret = 0;

	shअगरt = mmu_psize_defs[psize].shअगरt;
	step = 1 << shअगरt;

	prot = htab_convert_pte_flags(prot, HPTE_USE_KERNEL_KEY);

	DBG("htab_bolt_mapping(%lx..%lx -> %lx (%lx,%d,%d)\n",
	    vstart, vend, pstart, prot, psize, ssize);

	/* Carefully map only the possible range */
	vaddr = ALIGN(vstart, step);
	paddr = ALIGN(pstart, step);
	vend  = ALIGN_DOWN(vend, step);

	क्रम (; vaddr < vend; vaddr += step, paddr += step) अणु
		अचिन्हित दीर्घ hash, hpteg;
		अचिन्हित दीर्घ vsid = get_kernel_vsid(vaddr, ssize);
		अचिन्हित दीर्घ vpn  = hpt_vpn(vaddr, vsid, ssize);
		अचिन्हित दीर्घ tprot = prot;
		bool secondary_hash = false;

		/*
		 * If we hit a bad address वापस error.
		 */
		अगर (!vsid)
			वापस -1;
		/* Make kernel text executable */
		अगर (overlaps_kernel_text(vaddr, vaddr + step))
			tprot &= ~HPTE_R_N;

		/*
		 * If relocatable, check अगर it overlaps पूर्णांकerrupt vectors that
		 * are copied करोwn to real 0. For relocatable kernel
		 * (e.g. kdump हाल) we copy पूर्णांकerrupt vectors करोwn to real
		 * address 0. Mark that region as executable. This is
		 * because on p8 प्रणाली with relocation on exception feature
		 * enabled, exceptions are उठाओd with MMU (IR=DR=1) ON. Hence
		 * in order to execute the पूर्णांकerrupt handlers in भव
		 * mode the vector region need to be marked as executable.
		 */
		अगर ((PHYSICAL_START > MEMORY_START) &&
			overlaps_पूर्णांकerrupt_vector_text(vaddr, vaddr + step))
				tprot &= ~HPTE_R_N;

		hash = hpt_hash(vpn, shअगरt, ssize);
		hpteg = ((hash & htab_hash_mask) * HPTES_PER_GROUP);

		BUG_ON(!mmu_hash_ops.hpte_insert);
repeat:
		ret = mmu_hash_ops.hpte_insert(hpteg, vpn, paddr, tprot,
					       HPTE_V_BOLTED, psize, psize,
					       ssize);
		अगर (ret == -1) अणु
			/*
			 * Try to to keep bolted entries in primary.
			 * Remove non bolted entries and try insert again
			 */
			ret = mmu_hash_ops.hpte_हटाओ(hpteg);
			अगर (ret != -1)
				ret = mmu_hash_ops.hpte_insert(hpteg, vpn, paddr, tprot,
							       HPTE_V_BOLTED, psize, psize,
							       ssize);
			अगर (ret == -1 && !secondary_hash) अणु
				secondary_hash = true;
				hpteg = ((~hash & htab_hash_mask) * HPTES_PER_GROUP);
				जाओ repeat;
			पूर्ण
		पूर्ण

		अगर (ret < 0)
			अवरोध;

		cond_resched();
#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
		अगर (debug_pagealloc_enabled() &&
			(paddr >> PAGE_SHIFT) < linear_map_hash_count)
			linear_map_hash_slots[paddr >> PAGE_SHIFT] = ret | 0x80;
#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */
	पूर्ण
	वापस ret < 0 ? ret : 0;
पूर्ण

पूर्णांक htab_हटाओ_mapping(अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
		      पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ vaddr, समय_limit;
	अचिन्हित पूर्णांक step, shअगरt;
	पूर्णांक rc;
	पूर्णांक ret = 0;

	shअगरt = mmu_psize_defs[psize].shअगरt;
	step = 1 << shअगरt;

	अगर (!mmu_hash_ops.hpte_हटाओbolted)
		वापस -ENODEV;

	/* Unmap the full range specअगरicied */
	vaddr = ALIGN_DOWN(vstart, step);
	समय_limit = jअगरfies + HZ;

	क्रम (;vaddr < vend; vaddr += step) अणु
		rc = mmu_hash_ops.hpte_हटाओbolted(vaddr, psize, ssize);

		/*
		 * For large number of mappings पूर्णांकroduce a cond_resched()
		 * to prevent softlockup warnings.
		 */
		अगर (समय_after(jअगरfies, समय_limit)) अणु
			cond_resched();
			समय_limit = jअगरfies + HZ;
		पूर्ण
		अगर (rc == -ENOENT) अणु
			ret = -ENOENT;
			जारी;
		पूर्ण
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool disable_1tb_segments = false;

अटल पूर्णांक __init parse_disable_1tb_segments(अक्षर *p)
अणु
	disable_1tb_segments = true;
	वापस 0;
पूर्ण
early_param("disable_1tb_segments", parse_disable_1tb_segments);

अटल पूर्णांक __init htab_dt_scan_seg_sizes(अचिन्हित दीर्घ node,
					 स्थिर अक्षर *uname, पूर्णांक depth,
					 व्योम *data)
अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be32 *prop;
	पूर्णांक size = 0;

	/* We are scanning "cpu" nodes only */
	अगर (type == शून्य || म_भेद(type, "cpu") != 0)
		वापस 0;

	prop = of_get_flat_dt_prop(node, "ibm,processor-segment-sizes", &size);
	अगर (prop == शून्य)
		वापस 0;
	क्रम (; size >= 4; size -= 4, ++prop) अणु
		अगर (be32_to_cpu(prop[0]) == 40) अणु
			DBG("1T segment support detected\n");

			अगर (disable_1tb_segments) अणु
				DBG("1T segments disabled by command line\n");
				अवरोध;
			पूर्ण

			cur_cpu_spec->mmu_features |= MMU_FTR_1T_SEGMENT;
			वापस 1;
		पूर्ण
	पूर्ण
	cur_cpu_spec->mmu_features &= ~MMU_FTR_NO_SLBIE_B;
	वापस 0;
पूर्ण

अटल पूर्णांक __init get_idx_from_shअगरt(अचिन्हित पूर्णांक shअगरt)
अणु
	पूर्णांक idx = -1;

	चयन (shअगरt) अणु
	हाल 0xc:
		idx = MMU_PAGE_4K;
		अवरोध;
	हाल 0x10:
		idx = MMU_PAGE_64K;
		अवरोध;
	हाल 0x14:
		idx = MMU_PAGE_1M;
		अवरोध;
	हाल 0x18:
		idx = MMU_PAGE_16M;
		अवरोध;
	हाल 0x22:
		idx = MMU_PAGE_16G;
		अवरोध;
	पूर्ण
	वापस idx;
पूर्ण

अटल पूर्णांक __init htab_dt_scan_page_sizes(अचिन्हित दीर्घ node,
					  स्थिर अक्षर *uname, पूर्णांक depth,
					  व्योम *data)
अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be32 *prop;
	पूर्णांक size = 0;

	/* We are scanning "cpu" nodes only */
	अगर (type == शून्य || म_भेद(type, "cpu") != 0)
		वापस 0;

	prop = of_get_flat_dt_prop(node, "ibm,segment-page-sizes", &size);
	अगर (!prop)
		वापस 0;

	pr_info("Page sizes from device-tree:\n");
	size /= 4;
	cur_cpu_spec->mmu_features &= ~(MMU_FTR_16M_PAGE);
	जबतक(size > 0) अणु
		अचिन्हित पूर्णांक base_shअगरt = be32_to_cpu(prop[0]);
		अचिन्हित पूर्णांक slbenc = be32_to_cpu(prop[1]);
		अचिन्हित पूर्णांक lpnum = be32_to_cpu(prop[2]);
		काष्ठा mmu_psize_def *def;
		पूर्णांक idx, base_idx;

		size -= 3; prop += 3;
		base_idx = get_idx_from_shअगरt(base_shअगरt);
		अगर (base_idx < 0) अणु
			/* skip the pte encoding also */
			prop += lpnum * 2; size -= lpnum * 2;
			जारी;
		पूर्ण
		def = &mmu_psize_defs[base_idx];
		अगर (base_idx == MMU_PAGE_16M)
			cur_cpu_spec->mmu_features |= MMU_FTR_16M_PAGE;

		def->shअगरt = base_shअगरt;
		अगर (base_shअगरt <= 23)
			def->avpnm = 0;
		अन्यथा
			def->avpnm = (1 << (base_shअगरt - 23)) - 1;
		def->sllp = slbenc;
		/*
		 * We करोn't know for sure what's up with tlbiel, so
		 * क्रम now we only set it क्रम 4K and 64K pages
		 */
		अगर (base_idx == MMU_PAGE_4K || base_idx == MMU_PAGE_64K)
			def->tlbiel = 1;
		अन्यथा
			def->tlbiel = 0;

		जबतक (size > 0 && lpnum) अणु
			अचिन्हित पूर्णांक shअगरt = be32_to_cpu(prop[0]);
			पूर्णांक penc  = be32_to_cpu(prop[1]);

			prop += 2; size -= 2;
			lpnum--;

			idx = get_idx_from_shअगरt(shअगरt);
			अगर (idx < 0)
				जारी;

			अगर (penc == -1)
				pr_err("Invalid penc for base_shift=%d "
				       "shift=%d\n", base_shअगरt, shअगरt);

			def->penc[idx] = penc;
			pr_info("base_shift=%d: shift=%d, sllp=0x%04lx,"
				" avpnm=0x%08lx, tlbiel=%d, penc=%d\n",
				base_shअगरt, shअगरt, def->sllp,
				def->avpnm, def->tlbiel, def->penc[idx]);
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
/*
 * Scan क्रम 16G memory blocks that have been set aside क्रम huge pages
 * and reserve those blocks क्रम 16G huge pages.
 */
अटल पूर्णांक __init htab_dt_scan_hugepage_blocks(अचिन्हित दीर्घ node,
					स्थिर अक्षर *uname, पूर्णांक depth,
					व्योम *data) अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be64 *addr_prop;
	स्थिर __be32 *page_count_prop;
	अचिन्हित पूर्णांक expected_pages;
	दीर्घ अचिन्हित पूर्णांक phys_addr;
	दीर्घ अचिन्हित पूर्णांक block_size;

	/* We are scanning "memory" nodes only */
	अगर (type == शून्य || म_भेद(type, "memory") != 0)
		वापस 0;

	/*
	 * This property is the log base 2 of the number of भव pages that
	 * will represent this memory block.
	 */
	page_count_prop = of_get_flat_dt_prop(node, "ibm,expected#pages", शून्य);
	अगर (page_count_prop == शून्य)
		वापस 0;
	expected_pages = (1 << be32_to_cpu(page_count_prop[0]));
	addr_prop = of_get_flat_dt_prop(node, "reg", शून्य);
	अगर (addr_prop == शून्य)
		वापस 0;
	phys_addr = be64_to_cpu(addr_prop[0]);
	block_size = be64_to_cpu(addr_prop[1]);
	अगर (block_size != (16 * GB))
		वापस 0;
	prपूर्णांकk(KERN_INFO "Huge page(16GB) memory: "
			"addr = 0x%lX size = 0x%lX pages = %d\n",
			phys_addr, block_size, expected_pages);
	अगर (phys_addr + block_size * expected_pages <= memblock_end_of_DRAM()) अणु
		memblock_reserve(phys_addr, block_size * expected_pages);
		pseries_add_gpage(phys_addr, block_size, expected_pages);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

अटल व्योम mmu_psize_set_शेष_penc(व्योम)
अणु
	पूर्णांक bpsize, apsize;
	क्रम (bpsize = 0; bpsize < MMU_PAGE_COUNT; bpsize++)
		क्रम (apsize = 0; apsize < MMU_PAGE_COUNT; apsize++)
			mmu_psize_defs[bpsize].penc[apsize] = -1;
पूर्ण

#अगर_घोषित CONFIG_PPC_64K_PAGES

अटल bool might_have_hea(व्योम)
अणु
	/*
	 * The HEA ethernet adapter requires awareness of the
	 * GX bus. Without that awareness we can easily assume
	 * we will never see an HEA ethernet device.
	 */
#अगर_घोषित CONFIG_IBMEBUS
	वापस !cpu_has_feature(CPU_FTR_ARCH_207S) &&
		firmware_has_feature(FW_FEATURE_SPLPAR);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* #अगर_घोषित CONFIG_PPC_64K_PAGES */

अटल व्योम __init htab_scan_page_sizes(व्योम)
अणु
	पूर्णांक rc;

	/* se the invalid penc to -1 */
	mmu_psize_set_शेष_penc();

	/* Default to 4K pages only */
	स_नकल(mmu_psize_defs, mmu_psize_शेषs,
	       माप(mmu_psize_शेषs));

	/*
	 * Try to find the available page sizes in the device-tree
	 */
	rc = of_scan_flat_dt(htab_dt_scan_page_sizes, शून्य);
	अगर (rc == 0 && early_mmu_has_feature(MMU_FTR_16M_PAGE)) अणु
		/*
		 * Nothing in the device-tree, but the CPU supports 16M pages,
		 * so let's fallback on a known size list क्रम 16M capable CPUs.
		 */
		स_नकल(mmu_psize_defs, mmu_psize_शेषs_gp,
		       माप(mmu_psize_शेषs_gp));
	पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
	अगर (!hugetlb_disabled && !early_radix_enabled() ) अणु
		/* Reserve 16G huge page memory sections क्रम huge pages */
		of_scan_flat_dt(htab_dt_scan_hugepage_blocks, शून्य);
	पूर्ण
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */
पूर्ण

/*
 * Fill in the hpte_page_sizes[] array.
 * We go through the mmu_psize_defs[] array looking क्रम all the
 * supported base/actual page size combinations.  Each combination
 * has a unique pagesize encoding (penc) value in the low bits of
 * the LP field of the HPTE.  For actual page sizes less than 1MB,
 * some of the upper LP bits are used क्रम RPN bits, meaning that
 * we need to fill in several entries in hpte_page_sizes[].
 *
 * In diagrammatic क्रमm, with r = RPN bits and z = page size bits:
 *        PTE LP     actual page size
 *    rrrr rrrz		>=8KB
 *    rrrr rrzz		>=16KB
 *    rrrr rzzz		>=32KB
 *    rrrr zzzz		>=64KB
 *    ...
 *
 * The zzzz bits are implementation-specअगरic but are chosen so that
 * no encoding क्रम a larger page size uses the same value in its
 * low-order N bits as the encoding क्रम the 2^(12+N) byte page size
 * (अगर it exists).
 */
अटल व्योम init_hpte_page_sizes(व्योम)
अणु
	दीर्घ पूर्णांक ap, bp;
	दीर्घ पूर्णांक shअगरt, penc;

	क्रम (bp = 0; bp < MMU_PAGE_COUNT; ++bp) अणु
		अगर (!mmu_psize_defs[bp].shअगरt)
			जारी;	/* not a supported page size */
		क्रम (ap = bp; ap < MMU_PAGE_COUNT; ++ap) अणु
			penc = mmu_psize_defs[bp].penc[ap];
			अगर (penc == -1 || !mmu_psize_defs[ap].shअगरt)
				जारी;
			shअगरt = mmu_psize_defs[ap].shअगरt - LP_SHIFT;
			अगर (shअगरt <= 0)
				जारी;	/* should never happen */
			/*
			 * For page sizes less than 1MB, this loop
			 * replicates the entry क्रम all possible values
			 * of the rrrr bits.
			 */
			जबतक (penc < (1 << LP_BITS)) अणु
				hpte_page_sizes[penc] = (ap << 4) | bp;
				penc += 1 << shअगरt;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init htab_init_page_sizes(व्योम)
अणु
	bool aligned = true;
	init_hpte_page_sizes();

	अगर (!debug_pagealloc_enabled()) अणु
		/*
		 * Pick a size क्रम the linear mapping. Currently, we only
		 * support 16M, 1M and 4K which is the शेष
		 */
		अगर (IS_ENABLED(CONFIG_STRICT_KERNEL_RWX) &&
		    (अचिन्हित दीर्घ)_stext % 0x1000000) अणु
			अगर (mmu_psize_defs[MMU_PAGE_16M].shअगरt)
				pr_warn("Kernel not 16M aligned, disabling 16M linear map alignment\n");
			aligned = false;
		पूर्ण

		अगर (mmu_psize_defs[MMU_PAGE_16M].shअगरt && aligned)
			mmu_linear_psize = MMU_PAGE_16M;
		अन्यथा अगर (mmu_psize_defs[MMU_PAGE_1M].shअगरt)
			mmu_linear_psize = MMU_PAGE_1M;
	पूर्ण

#अगर_घोषित CONFIG_PPC_64K_PAGES
	/*
	 * Pick a size क्रम the ordinary pages. Default is 4K, we support
	 * 64K क्रम user mappings and vदो_स्मृति अगर supported by the processor.
	 * We only use 64k क्रम ioremap अगर the processor
	 * (and firmware) support cache-inhibited large pages.
	 * If not, we use 4k and set mmu_ci_restrictions so that
	 * hash_page knows to चयन processes that use cache-inhibited
	 * mappings to 4k pages.
	 */
	अगर (mmu_psize_defs[MMU_PAGE_64K].shअगरt) अणु
		mmu_भव_psize = MMU_PAGE_64K;
		mmu_vदो_स्मृति_psize = MMU_PAGE_64K;
		अगर (mmu_linear_psize == MMU_PAGE_4K)
			mmu_linear_psize = MMU_PAGE_64K;
		अगर (mmu_has_feature(MMU_FTR_CI_LARGE_PAGE)) अणु
			/*
			 * When running on pSeries using 64k pages क्रम ioremap
			 * would stop us accessing the HEA ethernet. So अगर we
			 * have the chance of ever seeing one, stay at 4k.
			 */
			अगर (!might_have_hea())
				mmu_io_psize = MMU_PAGE_64K;
		पूर्ण अन्यथा
			mmu_ci_restrictions = 1;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	/*
	 * We try to use 16M pages क्रम vmemmap अगर that is supported
	 * and we have at least 1G of RAM at boot
	 */
	अगर (mmu_psize_defs[MMU_PAGE_16M].shअगरt &&
	    memblock_phys_mem_size() >= 0x40000000)
		mmu_vmemmap_psize = MMU_PAGE_16M;
	अन्यथा
		mmu_vmemmap_psize = mmu_भव_psize;
#पूर्ण_अगर /* CONFIG_SPARSEMEM_VMEMMAP */

	prपूर्णांकk(KERN_DEBUG "Page orders: linear mapping = %d, "
	       "virtual = %d, io = %d"
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	       ", vmemmap = %d"
#पूर्ण_अगर
	       "\n",
	       mmu_psize_defs[mmu_linear_psize].shअगरt,
	       mmu_psize_defs[mmu_भव_psize].shअगरt,
	       mmu_psize_defs[mmu_io_psize].shअगरt
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	       ,mmu_psize_defs[mmu_vmemmap_psize].shअगरt
#पूर्ण_अगर
	       );
पूर्ण

अटल पूर्णांक __init htab_dt_scan_pftsize(अचिन्हित दीर्घ node,
				       स्थिर अक्षर *uname, पूर्णांक depth,
				       व्योम *data)
अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be32 *prop;

	/* We are scanning "cpu" nodes only */
	अगर (type == शून्य || म_भेद(type, "cpu") != 0)
		वापस 0;

	prop = of_get_flat_dt_prop(node, "ibm,pft-size", शून्य);
	अगर (prop != शून्य) अणु
		/* pft_size[0] is the NUMA CEC cookie */
		ppc64_pft_size = be32_to_cpu(prop[1]);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित htab_shअगरt_क्रम_mem_size(अचिन्हित दीर्घ mem_size)
अणु
	अचिन्हित memshअगरt = __ilog2(mem_size);
	अचिन्हित pshअगरt = mmu_psize_defs[mmu_भव_psize].shअगरt;
	अचिन्हित pteg_shअगरt;

	/* round mem_size up to next घातer of 2 */
	अगर ((1UL << memshअगरt) < mem_size)
		memshअगरt += 1;

	/* aim क्रम 2 pages / pteg */
	pteg_shअगरt = memshअगरt - (pshअगरt + 1);

	/*
	 * 2^11 PTEGS of 128 bytes each, ie. 2^18 bytes is the minimum htab
	 * size permitted by the architecture.
	 */
	वापस max(pteg_shअगरt + 7, 18U);
पूर्ण

अटल अचिन्हित दीर्घ __init htab_get_table_size(व्योम)
अणु
	/*
	 * If hash size isn't alपढ़ोy provided by the platक्रमm, we try to
	 * retrieve it from the device-tree. If it's not there neither, we
	 * calculate it now based on the total RAM size
	 */
	अगर (ppc64_pft_size == 0)
		of_scan_flat_dt(htab_dt_scan_pftsize, शून्य);
	अगर (ppc64_pft_size)
		वापस 1UL << ppc64_pft_size;

	वापस 1UL << htab_shअगरt_क्रम_mem_size(memblock_phys_mem_size());
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल पूर्णांक resize_hpt_क्रम_hotplug(अचिन्हित दीर्घ new_mem_size)
अणु
	अचिन्हित target_hpt_shअगरt;

	अगर (!mmu_hash_ops.resize_hpt)
		वापस 0;

	target_hpt_shअगरt = htab_shअगरt_क्रम_mem_size(new_mem_size);

	/*
	 * To aव्योम lots of HPT resizes अगर memory size is fluctuating
	 * across a boundary, we deliberately have some hysterisis
	 * here: we immediately increase the HPT size अगर the target
	 * shअगरt exceeds the current shअगरt, but we won't attempt to
	 * reduce unless the target shअगरt is at least 2 below the
	 * current shअगरt
	 */
	अगर (target_hpt_shअगरt > ppc64_pft_size ||
	    target_hpt_shअगरt < ppc64_pft_size - 1)
		वापस mmu_hash_ops.resize_hpt(target_hpt_shअगरt);

	वापस 0;
पूर्ण

पूर्णांक hash__create_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				 पूर्णांक nid, pgprot_t prot)
अणु
	पूर्णांक rc;

	अगर (end >= H_VMALLOC_START) अणु
		pr_warn("Outside the supported range\n");
		वापस -1;
	पूर्ण

	resize_hpt_क्रम_hotplug(memblock_phys_mem_size());

	rc = htab_bolt_mapping(start, end, __pa(start),
			       pgprot_val(prot), mmu_linear_psize,
			       mmu_kernel_ssize);

	अगर (rc < 0) अणु
		पूर्णांक rc2 = htab_हटाओ_mapping(start, end, mmu_linear_psize,
					      mmu_kernel_ssize);
		BUG_ON(rc2 && (rc2 != -ENOENT));
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक hash__हटाओ_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक rc = htab_हटाओ_mapping(start, end, mmu_linear_psize,
				     mmu_kernel_ssize);

	अगर (resize_hpt_क्रम_hotplug(memblock_phys_mem_size()) == -ENOSPC)
		pr_warn("Hash collision while resizing HPT\n");

	वापस rc;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

अटल व्योम __init hash_init_partition_table(phys_addr_t hash_table,
					     अचिन्हित दीर्घ htab_size)
अणु
	mmu_partition_table_init();

	/*
	 * PS field (VRMA page size) is not used क्रम LPID 0, hence set to 0.
	 * For now, UPRT is 0 and we have no segment table.
	 */
	htab_size =  __ilog2(htab_size) - 18;
	mmu_partition_table_set_entry(0, hash_table | htab_size, 0, false);
	pr_info("Partition table %p\n", partition_tb);
पूर्ण

अटल व्योम __init htab_initialize(व्योम)
अणु
	अचिन्हित दीर्घ table;
	अचिन्हित दीर्घ pteg_count;
	अचिन्हित दीर्घ prot;
	phys_addr_t base = 0, size = 0, end;
	u64 i;

	DBG(" -> htab_initialize()\n");

	अगर (mmu_has_feature(MMU_FTR_1T_SEGMENT)) अणु
		mmu_kernel_ssize = MMU_SEGSIZE_1T;
		mmu_highuser_ssize = MMU_SEGSIZE_1T;
		prपूर्णांकk(KERN_INFO "Using 1TB segments\n");
	पूर्ण

	अगर (stress_slb_enabled)
		अटल_branch_enable(&stress_slb_key);

	/*
	 * Calculate the required size of the htab.  We want the number of
	 * PTEGs to equal one half the number of real pages.
	 */
	htab_size_bytes = htab_get_table_size();
	pteg_count = htab_size_bytes >> 7;

	htab_hash_mask = pteg_count - 1;

	अगर (firmware_has_feature(FW_FEATURE_LPAR) ||
	    firmware_has_feature(FW_FEATURE_PS3_LV1)) अणु
		/* Using a hypervisor which owns the htab */
		htab_address = शून्य;
		_SDR1 = 0;
#अगर_घोषित CONFIG_FA_DUMP
		/*
		 * If firmware assisted dump is active firmware preserves
		 * the contents of htab aदीर्घ with entire partition memory.
		 * Clear the htab अगर firmware assisted dump is active so
		 * that we करोnt end up using old mappings.
		 */
		अगर (is_fadump_active() && mmu_hash_ops.hpte_clear_all)
			mmu_hash_ops.hpte_clear_all();
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ limit = MEMBLOCK_ALLOC_ANYWHERE;

#अगर_घोषित CONFIG_PPC_CELL
		/*
		 * Cell may require the hash table करोwn low when using the
		 * Axon IOMMU in order to fit the dynamic region over it, see
		 * comments in cell/iommu.c
		 */
		अगर (fdt_subnode_offset(initial_boot_params, 0, "axon") > 0) अणु
			limit = 0x80000000;
			pr_info("Hash table forced below 2G for Axon IOMMU\n");
		पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_CELL */

		table = memblock_phys_alloc_range(htab_size_bytes,
						  htab_size_bytes,
						  0, limit);
		अगर (!table)
			panic("ERROR: Failed to allocate %pa bytes below %pa\n",
			      &htab_size_bytes, &limit);

		DBG("Hash table allocated at %lx, size: %lx\n", table,
		    htab_size_bytes);

		htab_address = __va(table);

		/* htab असलolute addr + encoded htअसलize */
		_SDR1 = table + __ilog2(htab_size_bytes) - 18;

		/* Initialize the HPT with no entries */
		स_रखो((व्योम *)table, 0, htab_size_bytes);

		अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
			/* Set SDR1 */
			mtspr(SPRN_SDR1, _SDR1);
		अन्यथा
			hash_init_partition_table(table, htab_size_bytes);
	पूर्ण

	prot = pgprot_val(PAGE_KERNEL);

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
	अगर (debug_pagealloc_enabled()) अणु
		linear_map_hash_count = memblock_end_of_DRAM() >> PAGE_SHIFT;
		linear_map_hash_slots = memblock_alloc_try_nid(
				linear_map_hash_count, 1, MEMBLOCK_LOW_LIMIT,
				ppc64_rma_size,	NUMA_NO_NODE);
		अगर (!linear_map_hash_slots)
			panic("%s: Failed to allocate %lu bytes max_addr=%pa\n",
			      __func__, linear_map_hash_count, &ppc64_rma_size);
	पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */

	/* create bolted the linear mapping in the hash table */
	क्रम_each_mem_range(i, &base, &end) अणु
		size = end - base;
		base = (अचिन्हित दीर्घ)__va(base);

		DBG("creating mapping for region: %lx..%lx (prot: %lx)\n",
		    base, size, prot);

		अगर ((base + size) >= H_VMALLOC_START) अणु
			pr_warn("Outside the supported range\n");
			जारी;
		पूर्ण

		BUG_ON(htab_bolt_mapping(base, base + size, __pa(base),
				prot, mmu_linear_psize, mmu_kernel_ssize));
	पूर्ण
	memblock_set_current_limit(MEMBLOCK_ALLOC_ANYWHERE);

	/*
	 * If we have a memory_limit and we've allocated TCEs then we need to
	 * explicitly map the TCE area at the top of RAM. We also cope with the
	 * हाल that the TCEs start below memory_limit.
	 * tce_alloc_start/end are 16MB aligned so the mapping should work
	 * क्रम either 4K or 16MB pages.
	 */
	अगर (tce_alloc_start) अणु
		tce_alloc_start = (अचिन्हित दीर्घ)__va(tce_alloc_start);
		tce_alloc_end = (अचिन्हित दीर्घ)__va(tce_alloc_end);

		अगर (base + size >= tce_alloc_start)
			tce_alloc_start = base + size + 1;

		BUG_ON(htab_bolt_mapping(tce_alloc_start, tce_alloc_end,
					 __pa(tce_alloc_start), prot,
					 mmu_linear_psize, mmu_kernel_ssize));
	पूर्ण


	DBG(" <- htab_initialize()\n");
पूर्ण
#अघोषित KB
#अघोषित MB

व्योम __init hash__early_init_devtree(व्योम)
अणु
	/* Initialize segment sizes */
	of_scan_flat_dt(htab_dt_scan_seg_sizes, शून्य);

	/* Initialize page sizes */
	htab_scan_page_sizes();
पूर्ण

अटल काष्ठा hash_mm_context init_hash_mm_context;
व्योम __init hash__early_init_mmu(व्योम)
अणु
#अगर_अघोषित CONFIG_PPC_64K_PAGES
	/*
	 * We have code in __hash_page_4K() and अन्यथाwhere, which assumes it can
	 * करो the following:
	 *   new_pte |= (slot << H_PAGE_F_GIX_SHIFT) & (H_PAGE_F_SECOND | H_PAGE_F_GIX);
	 *
	 * Where the slot number is between 0-15, and values of 8-15 indicate
	 * the secondary bucket. For that code to work H_PAGE_F_SECOND and
	 * H_PAGE_F_GIX must occupy four contiguous bits in the PTE, and
	 * H_PAGE_F_SECOND must be placed above H_PAGE_F_GIX. Assert that here
	 * with a BUILD_BUG_ON().
	 */
	BUILD_BUG_ON(H_PAGE_F_SECOND != (1ul  << (H_PAGE_F_GIX_SHIFT + 3)));
#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */

	htab_init_page_sizes();

	/*
	 * initialize page table size
	 */
	__pte_frag_nr = H_PTE_FRAG_NR;
	__pte_frag_size_shअगरt = H_PTE_FRAG_SIZE_SHIFT;
	__pmd_frag_nr = H_PMD_FRAG_NR;
	__pmd_frag_size_shअगरt = H_PMD_FRAG_SIZE_SHIFT;

	__pte_index_size = H_PTE_INDEX_SIZE;
	__pmd_index_size = H_PMD_INDEX_SIZE;
	__pud_index_size = H_PUD_INDEX_SIZE;
	__pgd_index_size = H_PGD_INDEX_SIZE;
	__pud_cache_index = H_PUD_CACHE_INDEX;
	__pte_table_size = H_PTE_TABLE_SIZE;
	__pmd_table_size = H_PMD_TABLE_SIZE;
	__pud_table_size = H_PUD_TABLE_SIZE;
	__pgd_table_size = H_PGD_TABLE_SIZE;
	/*
	 * 4k use hugepd क्रमmat, so क्रम hash set then to
	 * zero
	 */
	__pmd_val_bits = HASH_PMD_VAL_BITS;
	__pud_val_bits = HASH_PUD_VAL_BITS;
	__pgd_val_bits = HASH_PGD_VAL_BITS;

	__kernel_virt_start = H_KERN_VIRT_START;
	__vदो_स्मृति_start = H_VMALLOC_START;
	__vदो_स्मृति_end = H_VMALLOC_END;
	__kernel_io_start = H_KERN_IO_START;
	__kernel_io_end = H_KERN_IO_END;
	vmemmap = (काष्ठा page *)H_VMEMMAP_START;
	ioremap_bot = IOREMAP_BASE;

#अगर_घोषित CONFIG_PCI
	pci_io_base = ISA_IO_BASE;
#पूर्ण_अगर

	/* Select appropriate backend */
	अगर (firmware_has_feature(FW_FEATURE_PS3_LV1))
		ps3_early_mm_init();
	अन्यथा अगर (firmware_has_feature(FW_FEATURE_LPAR))
		hpte_init_pseries();
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_NATIVE))
		hpte_init_native();

	अगर (!mmu_hash_ops.hpte_insert)
		panic("hash__early_init_mmu: No MMU hash ops defined!\n");

	/*
	 * Initialize the MMU Hash table and create the linear mapping
	 * of memory. Has to be करोne beक्रमe SLB initialization as this is
	 * currently where the page size encoding is obtained.
	 */
	htab_initialize();

	init_mm.context.hash_context = &init_hash_mm_context;
	mm_ctx_set_slb_addr_limit(&init_mm.context, SLB_ADDR_LIMIT_DEFAULT);

	pr_info("Initializing hash mmu with SLB\n");
	/* Initialize SLB management */
	slb_initialize();

	अगर (cpu_has_feature(CPU_FTR_ARCH_206)
			&& cpu_has_feature(CPU_FTR_HVMODE))
		tlbiel_all();
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम hash__early_init_mmu_secondary(व्योम)
अणु
	/* Initialize hash table क्रम that CPU */
	अगर (!firmware_has_feature(FW_FEATURE_LPAR)) अणु

		अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
			mtspr(SPRN_SDR1, _SDR1);
		अन्यथा
			set_ptcr_when_no_uv(__pa(partition_tb) |
					    (PATB_SIZE_SHIFT - 12));
	पूर्ण
	/* Initialize SLB */
	slb_initialize();

	अगर (cpu_has_feature(CPU_FTR_ARCH_206)
			&& cpu_has_feature(CPU_FTR_HVMODE))
		tlbiel_all();

#अगर_घोषित CONFIG_PPC_MEM_KEYS
	अगर (mmu_has_feature(MMU_FTR_PKEY))
		mtspr(SPRN_UAMOR, शेष_uamor);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Called by यंत्र hashtable.S क्रम करोing lazy icache flush
 */
अचिन्हित पूर्णांक hash_page_करो_lazy_icache(अचिन्हित पूर्णांक pp, pte_t pte, पूर्णांक trap)
अणु
	काष्ठा page *page;

	अगर (!pfn_valid(pte_pfn(pte)))
		वापस pp;

	page = pte_page(pte);

	/* page is dirty */
	अगर (!test_bit(PG_dcache_clean, &page->flags) && !PageReserved(page)) अणु
		अगर (trap == INTERRUPT_INST_STORAGE) अणु
			flush_dcache_icache_page(page);
			set_bit(PG_dcache_clean, &page->flags);
		पूर्ण अन्यथा
			pp |= HPTE_R_N;
	पूर्ण
	वापस pp;
पूर्ण

#अगर_घोषित CONFIG_PPC_MM_SLICES
अटल अचिन्हित पूर्णांक get_paca_psize(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर *psizes;
	अचिन्हित दीर्घ index, mask_index;

	अगर (addr < SLICE_LOW_TOP) अणु
		psizes = get_paca()->mm_ctx_low_slices_psize;
		index = GET_LOW_SLICE_INDEX(addr);
	पूर्ण अन्यथा अणु
		psizes = get_paca()->mm_ctx_high_slices_psize;
		index = GET_HIGH_SLICE_INDEX(addr);
	पूर्ण
	mask_index = index & 0x1;
	वापस (psizes[index >> 1] >> (mask_index * 4)) & 0xF;
पूर्ण

#अन्यथा
अचिन्हित पूर्णांक get_paca_psize(अचिन्हित दीर्घ addr)
अणु
	वापस get_paca()->mm_ctx_user_psize;
पूर्ण
#पूर्ण_अगर

/*
 * Demote a segment to using 4k pages.
 * For now this makes the whole process use 4k pages.
 */
#अगर_घोषित CONFIG_PPC_64K_PAGES
व्योम demote_segment_4k(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	अगर (get_slice_psize(mm, addr) == MMU_PAGE_4K)
		वापस;
	slice_set_range_psize(mm, addr, 1, MMU_PAGE_4K);
	copro_flush_all_slbs(mm);
	अगर ((get_paca_psize(addr) != MMU_PAGE_4K) && (current->mm == mm)) अणु

		copy_mm_to_paca(mm);
		slb_flush_and_restore_bolted();
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */

#अगर_घोषित CONFIG_PPC_SUBPAGE_PROT
/*
 * This looks up a 2-bit protection code क्रम a 4k subpage of a 64k page.
 * Userspace sets the subpage permissions using the subpage_prot प्रणाली call.
 *
 * Result is 0: full permissions, _PAGE_RW: पढ़ो-only,
 * _PAGE_RWX: no access.
 */
अटल पूर्णांक subpage_protection(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea)
अणु
	काष्ठा subpage_prot_table *spt = mm_ctx_subpage_prot(&mm->context);
	u32 spp = 0;
	u32 **sbpm, *sbpp;

	अगर (!spt)
		वापस 0;

	अगर (ea >= spt->maxaddr)
		वापस 0;
	अगर (ea < 0x100000000UL) अणु
		/* addresses below 4GB use spt->low_prot */
		sbpm = spt->low_prot;
	पूर्ण अन्यथा अणु
		sbpm = spt->protptrs[ea >> SBP_L3_SHIFT];
		अगर (!sbpm)
			वापस 0;
	पूर्ण
	sbpp = sbpm[(ea >> SBP_L2_SHIFT) & (SBP_L2_COUNT - 1)];
	अगर (!sbpp)
		वापस 0;
	spp = sbpp[(ea >> PAGE_SHIFT) & (SBP_L1_COUNT - 1)];

	/* extract 2-bit bitfield क्रम this 4k subpage */
	spp >>= 30 - 2 * ((ea >> 12) & 0xf);

	/*
	 * 0 -> full premission
	 * 1 -> Read only
	 * 2 -> no access.
	 * We वापस the flag that need to be cleared.
	 */
	spp = ((spp & 2) ? _PAGE_RWX : 0) | ((spp & 1) ? _PAGE_WRITE : 0);
	वापस spp;
पूर्ण

#अन्यथा /* CONFIG_PPC_SUBPAGE_PROT */
अटल अंतरभूत पूर्णांक subpage_protection(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम hash_failure_debug(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access,
			अचिन्हित दीर्घ vsid, अचिन्हित दीर्घ trap,
			पूर्णांक ssize, पूर्णांक psize, पूर्णांक lpsize, अचिन्हित दीर्घ pte)
अणु
	अगर (!prपूर्णांकk_ratelimit())
		वापस;
	pr_info("mm: Hashing failure ! EA=0x%lx access=0x%lx current=%s\n",
		ea, access, current->comm);
	pr_info("    trap=0x%lx vsid=0x%lx ssize=%d base psize=%d psize %d pte=0x%lx\n",
		trap, vsid, ssize, psize, lpsize, pte);
पूर्ण

अटल व्योम check_paca_psize(अचिन्हित दीर्घ ea, काष्ठा mm_काष्ठा *mm,
			     पूर्णांक psize, bool user_region)
अणु
	अगर (user_region) अणु
		अगर (psize != get_paca_psize(ea)) अणु
			copy_mm_to_paca(mm);
			slb_flush_and_restore_bolted();
		पूर्ण
	पूर्ण अन्यथा अगर (get_paca()->vदो_स्मृति_sllp !=
		   mmu_psize_defs[mmu_vदो_स्मृति_psize].sllp) अणु
		get_paca()->vदो_स्मृति_sllp =
			mmu_psize_defs[mmu_vदो_स्मृति_psize].sllp;
		slb_vदो_स्मृति_update();
	पूर्ण
पूर्ण

/*
 * Result code is:
 *  0 - handled
 *  1 - normal page fault
 * -1 - critical hash insertion error
 * -2 - access not permitted by subpage protection mechanism
 */
पूर्णांक hash_page_mm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea,
		 अचिन्हित दीर्घ access, अचिन्हित दीर्घ trap,
		 अचिन्हित दीर्घ flags)
अणु
	bool is_thp;
	pgd_t *pgdir;
	अचिन्हित दीर्घ vsid;
	pte_t *ptep;
	अचिन्हित hugeshअगरt;
	पूर्णांक rc, user_region = 0;
	पूर्णांक psize, ssize;

	DBG_LOW("hash_page(ea=%016lx, access=%lx, trap=%lx\n",
		ea, access, trap);
	trace_hash_fault(ea, access, trap);

	/* Get region & vsid */
	चयन (get_region_id(ea)) अणु
	हाल USER_REGION_ID:
		user_region = 1;
		अगर (! mm) अणु
			DBG_LOW(" user region with no mm !\n");
			rc = 1;
			जाओ bail;
		पूर्ण
		psize = get_slice_psize(mm, ea);
		ssize = user_segment_size(ea);
		vsid = get_user_vsid(&mm->context, ea, ssize);
		अवरोध;
	हाल VMALLOC_REGION_ID:
		vsid = get_kernel_vsid(ea, mmu_kernel_ssize);
		psize = mmu_vदो_स्मृति_psize;
		ssize = mmu_kernel_ssize;
		flags |= HPTE_USE_KERNEL_KEY;
		अवरोध;

	हाल IO_REGION_ID:
		vsid = get_kernel_vsid(ea, mmu_kernel_ssize);
		psize = mmu_io_psize;
		ssize = mmu_kernel_ssize;
		flags |= HPTE_USE_KERNEL_KEY;
		अवरोध;
	शेष:
		/*
		 * Not a valid range
		 * Send the problem up to करो_page_fault()
		 */
		rc = 1;
		जाओ bail;
	पूर्ण
	DBG_LOW(" mm=%p, mm->pgdir=%p, vsid=%016lx\n", mm, mm->pgd, vsid);

	/* Bad address. */
	अगर (!vsid) अणु
		DBG_LOW("Bad address!\n");
		rc = 1;
		जाओ bail;
	पूर्ण
	/* Get pgdir */
	pgdir = mm->pgd;
	अगर (pgdir == शून्य) अणु
		rc = 1;
		जाओ bail;
	पूर्ण

	/* Check CPU locality */
	अगर (user_region && mm_is_thपढ़ो_local(mm))
		flags |= HPTE_LOCAL_UPDATE;

#अगर_अघोषित CONFIG_PPC_64K_PAGES
	/*
	 * If we use 4K pages and our psize is not 4K, then we might
	 * be hitting a special driver mapping, and need to align the
	 * address beक्रमe we fetch the PTE.
	 *
	 * It could also be a hugepage mapping, in which हाल this is
	 * not necessary, but it's not harmful, either.
	 */
	अगर (psize != MMU_PAGE_4K)
		ea &= ~((1ul << mmu_psize_defs[psize].shअगरt) - 1);
#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */

	/* Get PTE and page size from page tables */
	ptep = find_linux_pte(pgdir, ea, &is_thp, &hugeshअगरt);
	अगर (ptep == शून्य || !pte_present(*ptep)) अणु
		DBG_LOW(" no PTE !\n");
		rc = 1;
		जाओ bail;
	पूर्ण

	/*
	 * Add _PAGE_PRESENT to the required access perm. If there are parallel
	 * updates to the pte that can possibly clear _PAGE_PTE, catch that too.
	 *
	 * We can safely use the वापस pte address in rest of the function
	 * because we करो set H_PAGE_BUSY which prevents further updates to pte
	 * from generic code.
	 */
	access |= _PAGE_PRESENT | _PAGE_PTE;

	/*
	 * Pre-check access permissions (will be re-checked atomically
	 * in __hash_page_XX but this pre-check is a fast path
	 */
	अगर (!check_pte_access(access, pte_val(*ptep))) अणु
		DBG_LOW(" no access !\n");
		rc = 1;
		जाओ bail;
	पूर्ण

	अगर (hugeshअगरt) अणु
		अगर (is_thp)
			rc = __hash_page_thp(ea, access, vsid, (pmd_t *)ptep,
					     trap, flags, ssize, psize);
#अगर_घोषित CONFIG_HUGETLB_PAGE
		अन्यथा
			rc = __hash_page_huge(ea, access, vsid, ptep, trap,
					      flags, ssize, hugeshअगरt, psize);
#अन्यथा
		अन्यथा अणु
			/*
			 * अगर we have hugeshअगरt, and is not transhuge with
			 * hugetlb disabled, something is really wrong.
			 */
			rc = 1;
			WARN_ON(1);
		पूर्ण
#पूर्ण_अगर
		अगर (current->mm == mm)
			check_paca_psize(ea, mm, psize, user_region);

		जाओ bail;
	पूर्ण

#अगर_अघोषित CONFIG_PPC_64K_PAGES
	DBG_LOW(" i-pte: %016lx\n", pte_val(*ptep));
#अन्यथा
	DBG_LOW(" i-pte: %016lx %016lx\n", pte_val(*ptep),
		pte_val(*(ptep + PTRS_PER_PTE)));
#पूर्ण_अगर
	/* Do actual hashing */
#अगर_घोषित CONFIG_PPC_64K_PAGES
	/* If H_PAGE_4K_PFN is set, make sure this is a 4k segment */
	अगर ((pte_val(*ptep) & H_PAGE_4K_PFN) && psize == MMU_PAGE_64K) अणु
		demote_segment_4k(mm, ea);
		psize = MMU_PAGE_4K;
	पूर्ण

	/*
	 * If this PTE is non-cacheable and we have restrictions on
	 * using non cacheable large pages, then we चयन to 4k
	 */
	अगर (mmu_ci_restrictions && psize == MMU_PAGE_64K && pte_ci(*ptep)) अणु
		अगर (user_region) अणु
			demote_segment_4k(mm, ea);
			psize = MMU_PAGE_4K;
		पूर्ण अन्यथा अगर (ea < VMALLOC_END) अणु
			/*
			 * some driver did a non-cacheable mapping
			 * in vदो_स्मृति space, so चयन vदो_स्मृति
			 * to 4k pages
			 */
			prपूर्णांकk(KERN_ALERT "Reducing vmalloc segment "
			       "to 4kB pages because of "
			       "non-cacheable mapping\n");
			psize = mmu_vदो_स्मृति_psize = MMU_PAGE_4K;
			copro_flush_all_slbs(mm);
		पूर्ण
	पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */

	अगर (current->mm == mm)
		check_paca_psize(ea, mm, psize, user_region);

#अगर_घोषित CONFIG_PPC_64K_PAGES
	अगर (psize == MMU_PAGE_64K)
		rc = __hash_page_64K(ea, access, vsid, ptep, trap,
				     flags, ssize);
	अन्यथा
#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */
	अणु
		पूर्णांक spp = subpage_protection(mm, ea);
		अगर (access & spp)
			rc = -2;
		अन्यथा
			rc = __hash_page_4K(ea, access, vsid, ptep, trap,
					    flags, ssize, spp);
	पूर्ण

	/*
	 * Dump some info in हाल of hash insertion failure, they should
	 * never happen so it is really useful to know अगर/when they करो
	 */
	अगर (rc == -1)
		hash_failure_debug(ea, access, vsid, trap, ssize, psize,
				   psize, pte_val(*ptep));
#अगर_अघोषित CONFIG_PPC_64K_PAGES
	DBG_LOW(" o-pte: %016lx\n", pte_val(*ptep));
#अन्यथा
	DBG_LOW(" o-pte: %016lx %016lx\n", pte_val(*ptep),
		pte_val(*(ptep + PTRS_PER_PTE)));
#पूर्ण_अगर
	DBG_LOW(" -> rc=%d\n", rc);

bail:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(hash_page_mm);

पूर्णांक hash_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access, अचिन्हित दीर्घ trap,
	      अचिन्हित दीर्घ dsisr)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा mm_काष्ठा *mm = current->mm;

	अगर ((get_region_id(ea) == VMALLOC_REGION_ID) ||
	    (get_region_id(ea) == IO_REGION_ID))
		mm = &init_mm;

	अगर (dsisr & DSISR_NOHPTE)
		flags |= HPTE_NOHPTE_UPDATE;

	वापस hash_page_mm(mm, ea, access, trap, flags);
पूर्ण
EXPORT_SYMBOL_GPL(hash_page);

DECLARE_INTERRUPT_HANDLER_RET(__करो_hash_fault);
DEFINE_INTERRUPT_HANDLER_RET(__करो_hash_fault)
अणु
	अचिन्हित दीर्घ ea = regs->dar;
	अचिन्हित दीर्घ dsisr = regs->dsisr;
	अचिन्हित दीर्घ access = _PAGE_PRESENT | _PAGE_READ;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित पूर्णांक region_id;
	दीर्घ err;

	region_id = get_region_id(ea);
	अगर ((region_id == VMALLOC_REGION_ID) || (region_id == IO_REGION_ID))
		mm = &init_mm;
	अन्यथा
		mm = current->mm;

	अगर (dsisr & DSISR_NOHPTE)
		flags |= HPTE_NOHPTE_UPDATE;

	अगर (dsisr & DSISR_ISSTORE)
		access |= _PAGE_WRITE;
	/*
	 * We set _PAGE_PRIVILEGED only when
	 * kernel mode access kernel space.
	 *
	 * _PAGE_PRIVILEGED is NOT set
	 * 1) when kernel mode access user space
	 * 2) user space access kernel space.
	 */
	access |= _PAGE_PRIVILEGED;
	अगर (user_mode(regs) || (region_id == USER_REGION_ID))
		access &= ~_PAGE_PRIVILEGED;

	अगर (TRAP(regs) == INTERRUPT_INST_STORAGE)
		access |= _PAGE_EXEC;

	err = hash_page_mm(mm, ea, access, TRAP(regs), flags);
	अगर (unlikely(err < 0)) अणु
		// failed to instert a hash PTE due to an hypervisor error
		अगर (user_mode(regs)) अणु
			अगर (IS_ENABLED(CONFIG_PPC_SUBPAGE_PROT) && err == -2)
				_exception(संक_अंश, regs, SEGV_ACCERR, ea);
			अन्यथा
				_exception(SIGBUS, regs, BUS_ADRERR, ea);
		पूर्ण अन्यथा अणु
			bad_page_fault(regs, SIGBUS);
		पूर्ण
		err = 0;
	पूर्ण

	वापस err;
पूर्ण

/*
 * The _RAW पूर्णांकerrupt entry checks क्रम the in_nmi() हाल beक्रमe
 * running the full handler.
 */
DEFINE_INTERRUPT_HANDLER_RAW(करो_hash_fault)
अणु
	अचिन्हित दीर्घ dsisr = regs->dsisr;

	अगर (unlikely(dsisr & (DSISR_BAD_FAULT_64S | DSISR_KEYFAULT))) अणु
		hash__करो_page_fault(regs);
		वापस 0;
	पूर्ण

	/*
	 * If we are in an "NMI" (e.g., an पूर्णांकerrupt when soft-disabled), then
	 * करोn't call hash_page, just fail the fault. This is required to
	 * prevent re-entrancy problems in the hash code, namely perf
	 * पूर्णांकerrupts hitting जबतक something holds H_PAGE_BUSY, and taking a
	 * hash fault. See the comment in hash_preload().
	 *
	 * We come here as a result of a DSI at a poपूर्णांक where we करोn't want
	 * to call hash_page, such as when we are accessing memory (possibly
	 * user memory) inside a PMU पूर्णांकerrupt that occurred जबतक पूर्णांकerrupts
	 * were soft-disabled.  We want to invoke the exception handler क्रम
	 * the access, or panic अगर there isn't a handler.
	 */
	अगर (unlikely(in_nmi())) अणु
		करो_bad_page_fault_segv(regs);
		वापस 0;
	पूर्ण

	अगर (__करो_hash_fault(regs))
		hash__करो_page_fault(regs);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_MM_SLICES
अटल bool should_hash_preload(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea)
अणु
	पूर्णांक psize = get_slice_psize(mm, ea);

	/* We only prefault standard pages क्रम now */
	अगर (unlikely(psize != mm_ctx_user_psize(&mm->context)))
		वापस false;

	/*
	 * Don't prefault अगर subpage protection is enabled क्रम the EA.
	 */
	अगर (unlikely((psize == MMU_PAGE_4K) && subpage_protection(mm, ea)))
		वापस false;

	वापस true;
पूर्ण
#अन्यथा
अटल bool should_hash_preload(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल व्योम hash_preload(काष्ठा mm_काष्ठा *mm, pte_t *ptep, अचिन्हित दीर्घ ea,
			 bool is_exec, अचिन्हित दीर्घ trap)
अणु
	अचिन्हित दीर्घ vsid;
	pgd_t *pgdir;
	पूर्णांक rc, ssize, update_flags = 0;
	अचिन्हित दीर्घ access = _PAGE_PRESENT | _PAGE_READ | (is_exec ? _PAGE_EXEC : 0);
	अचिन्हित दीर्घ flags;

	BUG_ON(get_region_id(ea) != USER_REGION_ID);

	अगर (!should_hash_preload(mm, ea))
		वापस;

	DBG_LOW("hash_preload(mm=%p, mm->pgdir=%p, ea=%016lx, access=%lx,"
		" trap=%lx\n", mm, mm->pgd, ea, access, trap);

	/* Get Linux PTE अगर available */
	pgdir = mm->pgd;
	अगर (pgdir == शून्य)
		वापस;

	/* Get VSID */
	ssize = user_segment_size(ea);
	vsid = get_user_vsid(&mm->context, ea, ssize);
	अगर (!vsid)
		वापस;

#अगर_घोषित CONFIG_PPC_64K_PAGES
	/* If either H_PAGE_4K_PFN or cache inhibited is set (and we are on
	 * a 64K kernel), then we करोn't preload, hash_page() will take
	 * care of it once we actually try to access the page.
	 * That way we करोn't have to duplicate all of the logic क्रम segment
	 * page size demotion here
	 * Called with  PTL held, hence can be sure the value won't change in
	 * between.
	 */
	अगर ((pte_val(*ptep) & H_PAGE_4K_PFN) || pte_ci(*ptep))
		वापस;
#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */

	/*
	 * __hash_page_* must run with पूर्णांकerrupts off, as it sets the
	 * H_PAGE_BUSY bit. It's possible क्रम perf पूर्णांकerrupts to hit at any
	 * समय and may take a hash fault पढ़ोing the user stack, see
	 * पढ़ो_user_stack_slow() in the घातerpc/perf code.
	 *
	 * If that takes a hash fault on the same page as we lock here, it
	 * will bail out when seeing H_PAGE_BUSY set, and retry the access
	 * leading to an infinite loop.
	 *
	 * Disabling पूर्णांकerrupts here करोes not prevent perf पूर्णांकerrupts, but it
	 * will prevent them taking hash faults (see the NMI test in
	 * करो_hash_page), then पढ़ो_user_stack's copy_from_user_nofault will
	 * fail and perf will fall back to पढ़ो_user_stack_slow(), which
	 * walks the Linux page tables.
	 *
	 * Interrupts must also be off क्रम the duration of the
	 * mm_is_thपढ़ो_local test and update, to prevent preempt running the
	 * mm on another CPU (XXX: this may be racy vs kthपढ़ो_use_mm).
	 */
	local_irq_save(flags);

	/* Is that local to this CPU ? */
	अगर (mm_is_thपढ़ो_local(mm))
		update_flags |= HPTE_LOCAL_UPDATE;

	/* Hash it in */
#अगर_घोषित CONFIG_PPC_64K_PAGES
	अगर (mm_ctx_user_psize(&mm->context) == MMU_PAGE_64K)
		rc = __hash_page_64K(ea, access, vsid, ptep, trap,
				     update_flags, ssize);
	अन्यथा
#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */
		rc = __hash_page_4K(ea, access, vsid, ptep, trap, update_flags,
				    ssize, subpage_protection(mm, ea));

	/* Dump some info in हाल of hash insertion failure, they should
	 * never happen so it is really useful to know अगर/when they करो
	 */
	अगर (rc == -1)
		hash_failure_debug(ea, access, vsid, trap, ssize,
				   mm_ctx_user_psize(&mm->context),
				   mm_ctx_user_psize(&mm->context),
				   pte_val(*ptep));

	local_irq_restore(flags);
पूर्ण

/*
 * This is called at the end of handling a user page fault, when the
 * fault has been handled by updating a PTE in the linux page tables.
 * We use it to preload an HPTE पूर्णांकo the hash table corresponding to
 * the updated linux PTE.
 *
 * This must always be called with the pte lock held.
 */
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		      pte_t *ptep)
अणु
	/*
	 * We करोn't need to worry about _PAGE_PRESENT here because we are
	 * called with either mm->page_table_lock held or ptl lock held
	 */
	अचिन्हित दीर्घ trap;
	bool is_exec;

	अगर (radix_enabled())
		वापस;

	/* We only want HPTEs क्रम linux PTEs that have _PAGE_ACCESSED set */
	अगर (!pte_young(*ptep) || address >= TASK_SIZE)
		वापस;

	/*
	 * We try to figure out अगर we are coming from an inकाष्ठाion
	 * access fault and pass that करोwn to __hash_page so we aव्योम
	 * द्विगुन-faulting on execution of fresh text. We have to test
	 * क्रम regs शून्य since init will get here first thing at boot.
	 *
	 * We also aव्योम filling the hash अगर not coming from a fault.
	 */

	trap = current->thपढ़ो.regs ? TRAP(current->thपढ़ो.regs) : 0UL;
	चयन (trap) अणु
	हाल 0x300:
		is_exec = false;
		अवरोध;
	हाल 0x400:
		is_exec = true;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	hash_preload(vma->vm_mm, ptep, address, is_exec, trap);
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
अटल अंतरभूत व्योम पंचांग_flush_hash_page(पूर्णांक local)
अणु
	/*
	 * Transactions are not पातed by tlbiel, only tlbie. Without, syncing a
	 * page back to a block device w/PIO could pick up transactional data
	 * (bad!) so we क्रमce an पात here. Beक्रमe the sync the page will be
	 * made पढ़ो-only, which will flush_hash_page. BIG ISSUE here: अगर the
	 * kernel uses a page from userspace without unmapping it first, it may
	 * see the speculated version.
	 */
	अगर (local && cpu_has_feature(CPU_FTR_TM) && current->thपढ़ो.regs &&
	    MSR_TM_ACTIVE(current->thपढ़ो.regs->msr)) अणु
		पंचांग_enable();
		पंचांग_पात(TM_CAUSE_TLBI);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम पंचांग_flush_hash_page(पूर्णांक local)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Return the global hash slot, corresponding to the given PTE, which contains
 * the HPTE.
 */
अचिन्हित दीर्घ pte_get_hash_gslot(अचिन्हित दीर्घ vpn, अचिन्हित दीर्घ shअगरt,
		पूर्णांक ssize, real_pte_t rpte, अचिन्हित पूर्णांक subpg_index)
अणु
	अचिन्हित दीर्घ hash, gslot, hidx;

	hash = hpt_hash(vpn, shअगरt, ssize);
	hidx = __rpte_to_hidx(rpte, subpg_index);
	अगर (hidx & _PTEIDX_SECONDARY)
		hash = ~hash;
	gslot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	gslot += hidx & _PTEIDX_GROUP_IX;
	वापस gslot;
पूर्ण

व्योम flush_hash_page(अचिन्हित दीर्घ vpn, real_pte_t pte, पूर्णांक psize, पूर्णांक ssize,
		     अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ index, shअगरt, gslot;
	पूर्णांक local = flags & HPTE_LOCAL_UPDATE;

	DBG_LOW("flush_hash_page(vpn=%016lx)\n", vpn);
	pte_iterate_hashed_subpages(pte, psize, vpn, index, shअगरt) अणु
		gslot = pte_get_hash_gslot(vpn, shअगरt, ssize, pte, index);
		DBG_LOW(" sub %ld: gslot=%lx\n", index, gslot);
		/*
		 * We use same base page size and actual psize, because we करोn't
		 * use these functions क्रम hugepage
		 */
		mmu_hash_ops.hpte_invalidate(gslot, vpn, psize, psize,
					     ssize, local);
	पूर्ण pte_iterate_hashed_end();

	पंचांग_flush_hash_page(local);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम flush_hash_hugepage(अचिन्हित दीर्घ vsid, अचिन्हित दीर्घ addr,
			 pmd_t *pmdp, अचिन्हित पूर्णांक psize, पूर्णांक ssize,
			 अचिन्हित दीर्घ flags)
अणु
	पूर्णांक i, max_hpte_count, valid;
	अचिन्हित दीर्घ s_addr;
	अचिन्हित अक्षर *hpte_slot_array;
	अचिन्हित दीर्घ hidx, shअगरt, vpn, hash, slot;
	पूर्णांक local = flags & HPTE_LOCAL_UPDATE;

	s_addr = addr & HPAGE_PMD_MASK;
	hpte_slot_array = get_hpte_slot_array(pmdp);
	/*
	 * IF we try to करो a HUGE PTE update after a withdraw is करोne.
	 * we will find the below शून्य. This happens when we करो
	 * split_huge_pmd
	 */
	अगर (!hpte_slot_array)
		वापस;

	अगर (mmu_hash_ops.hugepage_invalidate) अणु
		mmu_hash_ops.hugepage_invalidate(vsid, s_addr, hpte_slot_array,
						 psize, ssize, local);
		जाओ पंचांग_पात;
	पूर्ण
	/*
	 * No bluk hpte removal support, invalidate each entry
	 */
	shअगरt = mmu_psize_defs[psize].shअगरt;
	max_hpte_count = HPAGE_PMD_SIZE >> shअगरt;
	क्रम (i = 0; i < max_hpte_count; i++) अणु
		/*
		 * 8 bits per each hpte entries
		 * 000| [ secondary group (one bit) | hidx (3 bits) | valid bit]
		 */
		valid = hpte_valid(hpte_slot_array, i);
		अगर (!valid)
			जारी;
		hidx =  hpte_hash_index(hpte_slot_array, i);

		/* get the vpn */
		addr = s_addr + (i * (1ul << shअगरt));
		vpn = hpt_vpn(addr, vsid, ssize);
		hash = hpt_hash(vpn, shअगरt, ssize);
		अगर (hidx & _PTEIDX_SECONDARY)
			hash = ~hash;

		slot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot += hidx & _PTEIDX_GROUP_IX;
		mmu_hash_ops.hpte_invalidate(slot, vpn, psize,
					     MMU_PAGE_16M, ssize, local);
	पूर्ण
पंचांग_पात:
	पंचांग_flush_hash_page(local);
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

व्योम flush_hash_range(अचिन्हित दीर्घ number, पूर्णांक local)
अणु
	अगर (mmu_hash_ops.flush_hash_range)
		mmu_hash_ops.flush_hash_range(number, local);
	अन्यथा अणु
		पूर्णांक i;
		काष्ठा ppc64_tlb_batch *batch =
			this_cpu_ptr(&ppc64_tlb_batch);

		क्रम (i = 0; i < number; i++)
			flush_hash_page(batch->vpn[i], batch->pte[i],
					batch->psize, batch->ssize, local);
	पूर्ण
पूर्ण

दीर्घ hpte_insert_repeating(अचिन्हित दीर्घ hash, अचिन्हित दीर्घ vpn,
			   अचिन्हित दीर्घ pa, अचिन्हित दीर्घ rflags,
			   अचिन्हित दीर्घ vflags, पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ hpte_group;
	दीर्घ slot;

repeat:
	hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;

	/* Insert पूर्णांकo the hash table, primary slot */
	slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa, rflags, vflags,
					psize, psize, ssize);

	/* Primary is full, try the secondary */
	अगर (unlikely(slot == -1)) अणु
		hpte_group = (~hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa, rflags,
						vflags | HPTE_V_SECONDARY,
						psize, psize, ssize);
		अगर (slot == -1) अणु
			अगर (mftb() & 0x1)
				hpte_group = (hash & htab_hash_mask) *
						HPTES_PER_GROUP;

			mmu_hash_ops.hpte_हटाओ(hpte_group);
			जाओ repeat;
		पूर्ण
	पूर्ण

	वापस slot;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
अटल व्योम kernel_map_linear_page(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ lmi)
अणु
	अचिन्हित दीर्घ hash;
	अचिन्हित दीर्घ vsid = get_kernel_vsid(vaddr, mmu_kernel_ssize);
	अचिन्हित दीर्घ vpn = hpt_vpn(vaddr, vsid, mmu_kernel_ssize);
	अचिन्हित दीर्घ mode = htab_convert_pte_flags(pgprot_val(PAGE_KERNEL), HPTE_USE_KERNEL_KEY);
	दीर्घ ret;

	hash = hpt_hash(vpn, PAGE_SHIFT, mmu_kernel_ssize);

	/* Don't create HPTE entries क्रम bad address */
	अगर (!vsid)
		वापस;

	ret = hpte_insert_repeating(hash, vpn, __pa(vaddr), mode,
				    HPTE_V_BOLTED,
				    mmu_linear_psize, mmu_kernel_ssize);

	BUG_ON (ret < 0);
	spin_lock(&linear_map_hash_lock);
	BUG_ON(linear_map_hash_slots[lmi] & 0x80);
	linear_map_hash_slots[lmi] = ret | 0x80;
	spin_unlock(&linear_map_hash_lock);
पूर्ण

अटल व्योम kernel_unmap_linear_page(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ lmi)
अणु
	अचिन्हित दीर्घ hash, hidx, slot;
	अचिन्हित दीर्घ vsid = get_kernel_vsid(vaddr, mmu_kernel_ssize);
	अचिन्हित दीर्घ vpn = hpt_vpn(vaddr, vsid, mmu_kernel_ssize);

	hash = hpt_hash(vpn, PAGE_SHIFT, mmu_kernel_ssize);
	spin_lock(&linear_map_hash_lock);
	BUG_ON(!(linear_map_hash_slots[lmi] & 0x80));
	hidx = linear_map_hash_slots[lmi] & 0x7f;
	linear_map_hash_slots[lmi] = 0;
	spin_unlock(&linear_map_hash_lock);
	अगर (hidx & _PTEIDX_SECONDARY)
		hash = ~hash;
	slot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	slot += hidx & _PTEIDX_GROUP_IX;
	mmu_hash_ops.hpte_invalidate(slot, vpn, mmu_linear_psize,
				     mmu_linear_psize,
				     mmu_kernel_ssize, 0);
पूर्ण

व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags, vaddr, lmi;
	पूर्णांक i;

	local_irq_save(flags);
	क्रम (i = 0; i < numpages; i++, page++) अणु
		vaddr = (अचिन्हित दीर्घ)page_address(page);
		lmi = __pa(vaddr) >> PAGE_SHIFT;
		अगर (lmi >= linear_map_hash_count)
			जारी;
		अगर (enable)
			kernel_map_linear_page(vaddr, lmi);
		अन्यथा
			kernel_unmap_linear_page(vaddr, lmi);
	पूर्ण
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */

व्योम hash__setup_initial_memory_limit(phys_addr_t first_memblock_base,
				phys_addr_t first_memblock_size)
अणु
	/*
	 * We करोn't currently support the first MEMBLOCK not mapping 0
	 * physical on those processors
	 */
	BUG_ON(first_memblock_base != 0);

	/*
	 * On भवized प्रणालीs the first entry is our RMA region aka VRMA,
	 * non-भवized 64-bit hash MMU प्रणालीs करोn't have a limitation
	 * on real mode access.
	 *
	 * For guests on platक्रमms beक्रमe POWER9, we clamp the it limit to 1G
	 * to aव्योम some funky things such as RTAS bugs etc...
	 *
	 * On POWER9 we limit to 1TB in हाल the host erroneously told us that
	 * the RMA was >1TB. Effective address bits 0:23 are treated as zero
	 * (meaning the access is aliased to zero i.e. addr = addr % 1TB)
	 * क्रम भव real mode addressing and so it करोesn't make sense to
	 * have an area larger than 1TB as it can't be addressed.
	 */
	अगर (!early_cpu_has_feature(CPU_FTR_HVMODE)) अणु
		ppc64_rma_size = first_memblock_size;
		अगर (!early_cpu_has_feature(CPU_FTR_ARCH_300))
			ppc64_rma_size = min_t(u64, ppc64_rma_size, 0x40000000);
		अन्यथा
			ppc64_rma_size = min_t(u64, ppc64_rma_size,
					       1UL << SID_SHIFT_1T);

		/* Finally limit subsequent allocations */
		memblock_set_current_limit(ppc64_rma_size);
	पूर्ण अन्यथा अणु
		ppc64_rma_size = अच_दीर्घ_उच्च;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक hpt_order_get(व्योम *data, u64 *val)
अणु
	*val = ppc64_pft_size;
	वापस 0;
पूर्ण

अटल पूर्णांक hpt_order_set(व्योम *data, u64 val)
अणु
	पूर्णांक ret;

	अगर (!mmu_hash_ops.resize_hpt)
		वापस -ENODEV;

	cpus_पढ़ो_lock();
	ret = mmu_hash_ops.resize_hpt(val);
	cpus_पढ़ो_unlock();

	वापस ret;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_hpt_order, hpt_order_get, hpt_order_set, "%llu\n");

अटल पूर्णांक __init hash64_debugfs(व्योम)
अणु
	debugfs_create_file("hpt_order", 0600, घातerpc_debugfs_root, शून्य,
			    &fops_hpt_order);
	वापस 0;
पूर्ण
machine_device_initcall(pseries, hash64_debugfs);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

व्योम __init prपूर्णांक_प्रणाली_hash_info(व्योम)
अणु
	pr_info("ppc64_pft_size    = 0x%llx\n", ppc64_pft_size);

	अगर (htab_hash_mask)
		pr_info("htab_hash_mask    = 0x%lx\n", htab_hash_mask);
पूर्ण

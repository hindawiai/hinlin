<शैली गुरु>
#समावेश <linux/gfp.h>
#समावेश <linux/initrd.h>
#समावेश <linux/ioport.h>
#समावेश <linux/swap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/swapfile.h>
#समावेश <linux/swapops.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/sched/task.h>

#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/init.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/page_types.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/dma.h>		/* क्रम MAX_DMA_PFN */
#समावेश <यंत्र/microcode.h>
#समावेश <यंत्र/kaslr.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/pti.h>
#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/memtype.h>

/*
 * We need to define the tracepoपूर्णांकs somewhere, and tlb.c
 * is only compiled when SMP=y.
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/tlb.h>

#समावेश "mm_internal.h"

/*
 * Tables translating between page_cache_type_t and pte encoding.
 *
 * The शेष values are defined अटलally as minimal supported mode;
 * WC and WT fall back to UC-.  pat_init() updates these values to support
 * more cache modes, WC and WT, when it is safe to करो so.  See pat_init()
 * क्रम the details.  Note, __early_ioremap() used during early boot-समय
 * takes pgprot_t (pte encoding) and करोes not use these tables.
 *
 *   Index पूर्णांकo __cachemode2pte_tbl[] is the cachemode.
 *
 *   Index पूर्णांकo __pte2cachemode_tbl[] are the caching attribute bits of the pte
 *   (_PAGE_PWT, _PAGE_PCD, _PAGE_PAT) at index bit positions 0, 1, 2.
 */
अटल uपूर्णांक16_t __cachemode2pte_tbl[_PAGE_CACHE_MODE_NUM] = अणु
	[_PAGE_CACHE_MODE_WB      ]	= 0         | 0        ,
	[_PAGE_CACHE_MODE_WC      ]	= 0         | _PAGE_PCD,
	[_PAGE_CACHE_MODE_UC_MINUS]	= 0         | _PAGE_PCD,
	[_PAGE_CACHE_MODE_UC      ]	= _PAGE_PWT | _PAGE_PCD,
	[_PAGE_CACHE_MODE_WT      ]	= 0         | _PAGE_PCD,
	[_PAGE_CACHE_MODE_WP      ]	= 0         | _PAGE_PCD,
पूर्ण;

अचिन्हित दीर्घ cachemode2protval(क्रमागत page_cache_mode pcm)
अणु
	अगर (likely(pcm == 0))
		वापस 0;
	वापस __cachemode2pte_tbl[pcm];
पूर्ण
EXPORT_SYMBOL(cachemode2protval);

अटल uपूर्णांक8_t __pte2cachemode_tbl[8] = अणु
	[__pte2cm_idx( 0        | 0         | 0        )] = _PAGE_CACHE_MODE_WB,
	[__pte2cm_idx(_PAGE_PWT | 0         | 0        )] = _PAGE_CACHE_MODE_UC_MINUS,
	[__pte2cm_idx( 0        | _PAGE_PCD | 0        )] = _PAGE_CACHE_MODE_UC_MINUS,
	[__pte2cm_idx(_PAGE_PWT | _PAGE_PCD | 0        )] = _PAGE_CACHE_MODE_UC,
	[__pte2cm_idx( 0        | 0         | _PAGE_PAT)] = _PAGE_CACHE_MODE_WB,
	[__pte2cm_idx(_PAGE_PWT | 0         | _PAGE_PAT)] = _PAGE_CACHE_MODE_UC_MINUS,
	[__pte2cm_idx(0         | _PAGE_PCD | _PAGE_PAT)] = _PAGE_CACHE_MODE_UC_MINUS,
	[__pte2cm_idx(_PAGE_PWT | _PAGE_PCD | _PAGE_PAT)] = _PAGE_CACHE_MODE_UC,
पूर्ण;

/* Check that the ग_लिखो-protect PAT entry is set क्रम ग_लिखो-protect */
bool x86_has_pat_wp(व्योम)
अणु
	वापस __pte2cachemode_tbl[_PAGE_CACHE_MODE_WP] == _PAGE_CACHE_MODE_WP;
पूर्ण

क्रमागत page_cache_mode pgprot2cachemode(pgprot_t pgprot)
अणु
	अचिन्हित दीर्घ masked;

	masked = pgprot_val(pgprot) & _PAGE_CACHE_MASK;
	अगर (likely(masked == 0))
		वापस 0;
	वापस __pte2cachemode_tbl[__pte2cm_idx(masked)];
पूर्ण

अटल अचिन्हित दीर्घ __initdata pgt_buf_start;
अटल अचिन्हित दीर्घ __initdata pgt_buf_end;
अटल अचिन्हित दीर्घ __initdata pgt_buf_top;

अटल अचिन्हित दीर्घ min_pfn_mapped;

अटल bool __initdata can_use_brk_pgt = true;

/*
 * Pages वापसed are alपढ़ोy directly mapped.
 *
 * Changing that is likely to अवरोध Xen, see commit:
 *
 *    279b706 x86,xen: पूर्णांकroduce x86_init.mapping.pagetable_reserve
 *
 * क्रम detailed inक्रमmation.
 */
__ref व्योम *alloc_low_pages(अचिन्हित पूर्णांक num)
अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक i;

	अगर (after_booपंचांगem) अणु
		अचिन्हित पूर्णांक order;

		order = get_order((अचिन्हित दीर्घ)num << PAGE_SHIFT);
		वापस (व्योम *)__get_मुक्त_pages(GFP_ATOMIC | __GFP_ZERO, order);
	पूर्ण

	अगर ((pgt_buf_end + num) > pgt_buf_top || !can_use_brk_pgt) अणु
		अचिन्हित दीर्घ ret = 0;

		अगर (min_pfn_mapped < max_pfn_mapped) अणु
			ret = memblock_find_in_range(
					min_pfn_mapped << PAGE_SHIFT,
					max_pfn_mapped << PAGE_SHIFT,
					PAGE_SIZE * num , PAGE_SIZE);
		पूर्ण
		अगर (ret)
			memblock_reserve(ret, PAGE_SIZE * num);
		अन्यथा अगर (can_use_brk_pgt)
			ret = __pa(extend_brk(PAGE_SIZE * num, PAGE_SIZE));

		अगर (!ret)
			panic("alloc_low_pages: can not alloc memory");

		pfn = ret >> PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		pfn = pgt_buf_end;
		pgt_buf_end += num;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		व्योम *adr;

		adr = __va((pfn + i) << PAGE_SHIFT);
		clear_page(adr);
	पूर्ण

	वापस __va(pfn << PAGE_SHIFT);
पूर्ण

/*
 * By शेष need to be able to allocate page tables below PGD firstly क्रम
 * the 0-ISA_END_ADDRESS range and secondly क्रम the initial PMD_SIZE mapping.
 * With KASLR memory अक्रमomization, depending on the machine e820 memory and the
 * PUD alignment, twice that many pages may be needed when KASLR memory
 * अक्रमomization is enabled.
 */

#अगर_अघोषित CONFIG_X86_5LEVEL
#घोषणा INIT_PGD_PAGE_TABLES    3
#अन्यथा
#घोषणा INIT_PGD_PAGE_TABLES    4
#पूर्ण_अगर

#अगर_अघोषित CONFIG_RANDOMIZE_MEMORY
#घोषणा INIT_PGD_PAGE_COUNT      (2 * INIT_PGD_PAGE_TABLES)
#अन्यथा
#घोषणा INIT_PGD_PAGE_COUNT      (4 * INIT_PGD_PAGE_TABLES)
#पूर्ण_अगर

#घोषणा INIT_PGT_BUF_SIZE	(INIT_PGD_PAGE_COUNT * PAGE_SIZE)
RESERVE_BRK(early_pgt_alloc, INIT_PGT_BUF_SIZE);
व्योम  __init early_alloc_pgt_buf(व्योम)
अणु
	अचिन्हित दीर्घ tables = INIT_PGT_BUF_SIZE;
	phys_addr_t base;

	base = __pa(extend_brk(tables, PAGE_SIZE));

	pgt_buf_start = base >> PAGE_SHIFT;
	pgt_buf_end = pgt_buf_start;
	pgt_buf_top = pgt_buf_start + (tables >> PAGE_SHIFT);
पूर्ण

पूर्णांक after_booपंचांगem;

early_param_on_off("gbpages", "nogbpages", direct_gbpages, CONFIG_X86_सूचीECT_GBPAGES);

काष्ठा map_range अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	अचिन्हित page_size_mask;
पूर्ण;

अटल पूर्णांक page_size_mask;

/*
 * Save some of cr4 feature set we're using (e.g.  Pentium 4MB
 * enable and PPro Global page enable), so that any CPU's that boot
 * up after us can get the correct flags. Invoked on the boot CPU.
 */
अटल अंतरभूत व्योम cr4_set_bits_and_update_boot(अचिन्हित दीर्घ mask)
अणु
	mmu_cr4_features |= mask;
	अगर (trampoline_cr4_features)
		*trampoline_cr4_features = mmu_cr4_features;
	cr4_set_bits(mask);
पूर्ण

अटल व्योम __init probe_page_size_mask(व्योम)
अणु
	/*
	 * For pagealloc debugging, identity mapping will use small pages.
	 * This will simplअगरy cpa(), which otherwise needs to support splitting
	 * large pages पूर्णांकo small in पूर्णांकerrupt context, etc.
	 */
	अगर (boot_cpu_has(X86_FEATURE_PSE) && !debug_pagealloc_enabled())
		page_size_mask |= 1 << PG_LEVEL_2M;
	अन्यथा
		direct_gbpages = 0;

	/* Enable PSE अगर available */
	अगर (boot_cpu_has(X86_FEATURE_PSE))
		cr4_set_bits_and_update_boot(X86_CR4_PSE);

	/* Enable PGE अगर available */
	__supported_pte_mask &= ~_PAGE_GLOBAL;
	अगर (boot_cpu_has(X86_FEATURE_PGE)) अणु
		cr4_set_bits_and_update_boot(X86_CR4_PGE);
		__supported_pte_mask |= _PAGE_GLOBAL;
	पूर्ण

	/* By the शेष is everything supported: */
	__शेष_kernel_pte_mask = __supported_pte_mask;
	/* Except when with PTI where the kernel is mostly non-Global: */
	अगर (cpu_feature_enabled(X86_FEATURE_PTI))
		__शेष_kernel_pte_mask &= ~_PAGE_GLOBAL;

	/* Enable 1 GB linear kernel mappings अगर available: */
	अगर (direct_gbpages && boot_cpu_has(X86_FEATURE_GBPAGES)) अणु
		prपूर्णांकk(KERN_INFO "Using GB pages for direct mapping\n");
		page_size_mask |= 1 << PG_LEVEL_1G;
	पूर्ण अन्यथा अणु
		direct_gbpages = 0;
	पूर्ण
पूर्ण

अटल व्योम setup_pcid(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_X86_64))
		वापस;

	अगर (!boot_cpu_has(X86_FEATURE_PCID))
		वापस;

	अगर (boot_cpu_has(X86_FEATURE_PGE)) अणु
		/*
		 * This can't be cr4_set_bits_and_update_boot() -- the
		 * trampoline code can't handle CR4.PCIDE and it wouldn't
		 * करो any good anyway.  Despite the name,
		 * cr4_set_bits_and_update_boot() करोesn't actually cause
		 * the bits in question to reमुख्य set all the way through
		 * the secondary boot यंत्र.
		 *
		 * Instead, we brute-क्रमce it and set CR4.PCIDE manually in
		 * start_secondary().
		 */
		cr4_set_bits(X86_CR4_PCIDE);

		/*
		 * INVPCID's single-context modes (2/3) only work अगर we set
		 * X86_CR4_PCIDE, *and* we INVPCID support.  It's unusable
		 * on प्रणालीs that have X86_CR4_PCIDE clear, or that have
		 * no INVPCID support at all.
		 */
		अगर (boot_cpu_has(X86_FEATURE_INVPCID))
			setup_क्रमce_cpu_cap(X86_FEATURE_INVPCID_SINGLE);
	पूर्ण अन्यथा अणु
		/*
		 * flush_tlb_all(), as currently implemented, won't work अगर
		 * PCID is on but PGE is not.  Since that combination
		 * करोesn't exist on real hardware, there's no reason to try
		 * to fully support it, but it's polite to aव्योम corrupting
		 * data अगर we're on an improperly configured VM.
		 */
		setup_clear_cpu_cap(X86_FEATURE_PCID);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_32
#घोषणा NR_RANGE_MR 3
#अन्यथा /* CONFIG_X86_64 */
#घोषणा NR_RANGE_MR 5
#पूर्ण_अगर

अटल पूर्णांक __meminit save_mr(काष्ठा map_range *mr, पूर्णांक nr_range,
			     अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			     अचिन्हित दीर्घ page_size_mask)
अणु
	अगर (start_pfn < end_pfn) अणु
		अगर (nr_range >= NR_RANGE_MR)
			panic("run out of range for init_memory_mapping\n");
		mr[nr_range].start = start_pfn<<PAGE_SHIFT;
		mr[nr_range].end   = end_pfn<<PAGE_SHIFT;
		mr[nr_range].page_size_mask = page_size_mask;
		nr_range++;
	पूर्ण

	वापस nr_range;
पूर्ण

/*
 * adjust the page_size_mask क्रम small range to go with
 *	big page size instead small one अगर nearby are ram too.
 */
अटल व्योम __ref adjust_range_page_size_mask(काष्ठा map_range *mr,
							 पूर्णांक nr_range)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_range; i++) अणु
		अगर ((page_size_mask & (1<<PG_LEVEL_2M)) &&
		    !(mr[i].page_size_mask & (1<<PG_LEVEL_2M))) अणु
			अचिन्हित दीर्घ start = round_करोwn(mr[i].start, PMD_SIZE);
			अचिन्हित दीर्घ end = round_up(mr[i].end, PMD_SIZE);

#अगर_घोषित CONFIG_X86_32
			अगर ((end >> PAGE_SHIFT) > max_low_pfn)
				जारी;
#पूर्ण_अगर

			अगर (memblock_is_region_memory(start, end - start))
				mr[i].page_size_mask |= 1<<PG_LEVEL_2M;
		पूर्ण
		अगर ((page_size_mask & (1<<PG_LEVEL_1G)) &&
		    !(mr[i].page_size_mask & (1<<PG_LEVEL_1G))) अणु
			अचिन्हित दीर्घ start = round_करोwn(mr[i].start, PUD_SIZE);
			अचिन्हित दीर्घ end = round_up(mr[i].end, PUD_SIZE);

			अगर (memblock_is_region_memory(start, end - start))
				mr[i].page_size_mask |= 1<<PG_LEVEL_1G;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *page_size_string(काष्ठा map_range *mr)
अणु
	अटल स्थिर अक्षर str_1g[] = "1G";
	अटल स्थिर अक्षर str_2m[] = "2M";
	अटल स्थिर अक्षर str_4m[] = "4M";
	अटल स्थिर अक्षर str_4k[] = "4k";

	अगर (mr->page_size_mask & (1<<PG_LEVEL_1G))
		वापस str_1g;
	/*
	 * 32-bit without PAE has a 4M large page size.
	 * PG_LEVEL_2M is misnamed, but we can at least
	 * prपूर्णांक out the right size in the string.
	 */
	अगर (IS_ENABLED(CONFIG_X86_32) &&
	    !IS_ENABLED(CONFIG_X86_PAE) &&
	    mr->page_size_mask & (1<<PG_LEVEL_2M))
		वापस str_4m;

	अगर (mr->page_size_mask & (1<<PG_LEVEL_2M))
		वापस str_2m;

	वापस str_4k;
पूर्ण

अटल पूर्णांक __meminit split_mem_range(काष्ठा map_range *mr, पूर्णांक nr_range,
				     अचिन्हित दीर्घ start,
				     अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ start_pfn, end_pfn, limit_pfn;
	अचिन्हित दीर्घ pfn;
	पूर्णांक i;

	limit_pfn = PFN_DOWN(end);

	/* head अगर not big page alignment ? */
	pfn = start_pfn = PFN_DOWN(start);
#अगर_घोषित CONFIG_X86_32
	/*
	 * Don't use a large page क्रम the first 2/4MB of memory
	 * because there are often fixed size MTRRs in there
	 * and overlapping MTRRs पूर्णांकo large pages can cause
	 * slowकरोwns.
	 */
	अगर (pfn == 0)
		end_pfn = PFN_DOWN(PMD_SIZE);
	अन्यथा
		end_pfn = round_up(pfn, PFN_DOWN(PMD_SIZE));
#अन्यथा /* CONFIG_X86_64 */
	end_pfn = round_up(pfn, PFN_DOWN(PMD_SIZE));
#पूर्ण_अगर
	अगर (end_pfn > limit_pfn)
		end_pfn = limit_pfn;
	अगर (start_pfn < end_pfn) अणु
		nr_range = save_mr(mr, nr_range, start_pfn, end_pfn, 0);
		pfn = end_pfn;
	पूर्ण

	/* big page (2M) range */
	start_pfn = round_up(pfn, PFN_DOWN(PMD_SIZE));
#अगर_घोषित CONFIG_X86_32
	end_pfn = round_करोwn(limit_pfn, PFN_DOWN(PMD_SIZE));
#अन्यथा /* CONFIG_X86_64 */
	end_pfn = round_up(pfn, PFN_DOWN(PUD_SIZE));
	अगर (end_pfn > round_करोwn(limit_pfn, PFN_DOWN(PMD_SIZE)))
		end_pfn = round_करोwn(limit_pfn, PFN_DOWN(PMD_SIZE));
#पूर्ण_अगर

	अगर (start_pfn < end_pfn) अणु
		nr_range = save_mr(mr, nr_range, start_pfn, end_pfn,
				page_size_mask & (1<<PG_LEVEL_2M));
		pfn = end_pfn;
	पूर्ण

#अगर_घोषित CONFIG_X86_64
	/* big page (1G) range */
	start_pfn = round_up(pfn, PFN_DOWN(PUD_SIZE));
	end_pfn = round_करोwn(limit_pfn, PFN_DOWN(PUD_SIZE));
	अगर (start_pfn < end_pfn) अणु
		nr_range = save_mr(mr, nr_range, start_pfn, end_pfn,
				page_size_mask &
				 ((1<<PG_LEVEL_2M)|(1<<PG_LEVEL_1G)));
		pfn = end_pfn;
	पूर्ण

	/* tail is not big page (1G) alignment */
	start_pfn = round_up(pfn, PFN_DOWN(PMD_SIZE));
	end_pfn = round_करोwn(limit_pfn, PFN_DOWN(PMD_SIZE));
	अगर (start_pfn < end_pfn) अणु
		nr_range = save_mr(mr, nr_range, start_pfn, end_pfn,
				page_size_mask & (1<<PG_LEVEL_2M));
		pfn = end_pfn;
	पूर्ण
#पूर्ण_अगर

	/* tail is not big page (2M) alignment */
	start_pfn = pfn;
	end_pfn = limit_pfn;
	nr_range = save_mr(mr, nr_range, start_pfn, end_pfn, 0);

	अगर (!after_booपंचांगem)
		adjust_range_page_size_mask(mr, nr_range);

	/* try to merge same page size and continuous */
	क्रम (i = 0; nr_range > 1 && i < nr_range - 1; i++) अणु
		अचिन्हित दीर्घ old_start;
		अगर (mr[i].end != mr[i+1].start ||
		    mr[i].page_size_mask != mr[i+1].page_size_mask)
			जारी;
		/* move it */
		old_start = mr[i].start;
		स_हटाओ(&mr[i], &mr[i+1],
			(nr_range - 1 - i) * माप(काष्ठा map_range));
		mr[i--].start = old_start;
		nr_range--;
	पूर्ण

	क्रम (i = 0; i < nr_range; i++)
		pr_debug(" [mem %#010lx-%#010lx] page %s\n",
				mr[i].start, mr[i].end - 1,
				page_size_string(&mr[i]));

	वापस nr_range;
पूर्ण

काष्ठा range pfn_mapped[E820_MAX_ENTRIES];
पूर्णांक nr_pfn_mapped;

अटल व्योम add_pfn_range_mapped(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	nr_pfn_mapped = add_range_with_merge(pfn_mapped, E820_MAX_ENTRIES,
					     nr_pfn_mapped, start_pfn, end_pfn);
	nr_pfn_mapped = clean_sort_range(pfn_mapped, E820_MAX_ENTRIES);

	max_pfn_mapped = max(max_pfn_mapped, end_pfn);

	अगर (start_pfn < (1UL<<(32-PAGE_SHIFT)))
		max_low_pfn_mapped = max(max_low_pfn_mapped,
					 min(end_pfn, 1UL<<(32-PAGE_SHIFT)));
पूर्ण

bool pfn_range_is_mapped(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_pfn_mapped; i++)
		अगर ((start_pfn >= pfn_mapped[i].start) &&
		    (end_pfn <= pfn_mapped[i].end))
			वापस true;

	वापस false;
पूर्ण

/*
 * Setup the direct mapping of the physical memory at PAGE_OFFSET.
 * This runs beक्रमe booपंचांगem is initialized and माला_लो pages directly from
 * the physical memory. To access them they are temporarily mapped.
 */
अचिन्हित दीर्घ __ref init_memory_mapping(अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ end, pgprot_t prot)
अणु
	काष्ठा map_range mr[NR_RANGE_MR];
	अचिन्हित दीर्घ ret = 0;
	पूर्णांक nr_range, i;

	pr_debug("init_memory_mapping: [mem %#010lx-%#010lx]\n",
	       start, end - 1);

	स_रखो(mr, 0, माप(mr));
	nr_range = split_mem_range(mr, 0, start, end);

	क्रम (i = 0; i < nr_range; i++)
		ret = kernel_physical_mapping_init(mr[i].start, mr[i].end,
						   mr[i].page_size_mask,
						   prot);

	add_pfn_range_mapped(start >> PAGE_SHIFT, ret >> PAGE_SHIFT);

	वापस ret >> PAGE_SHIFT;
पूर्ण

/*
 * We need to iterate through the E820 memory map and create direct mappings
 * क्रम only E820_TYPE_RAM and E820_KERN_RESERVED regions. We cannot simply
 * create direct mappings क्रम all pfns from [0 to max_low_pfn) and
 * [4GB to max_pfn) because of possible memory holes in high addresses
 * that cannot be marked as UC by fixed/variable range MTRRs.
 * Depending on the alignment of E820 ranges, this may possibly result
 * in using smaller size (i.e. 4K instead of 2M or 1G) page tables.
 *
 * init_mem_mapping() calls init_range_memory_mapping() with big range.
 * That range would have hole in the middle or ends, and only ram parts
 * will be mapped in init_range_memory_mapping().
 */
अटल अचिन्हित दीर्घ __init init_range_memory_mapping(
					   अचिन्हित दीर्घ r_start,
					   अचिन्हित दीर्घ r_end)
अणु
	अचिन्हित दीर्घ start_pfn, end_pfn;
	अचिन्हित दीर्घ mapped_ram_size = 0;
	पूर्णांक i;

	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start_pfn, &end_pfn, शून्य) अणु
		u64 start = clamp_val(PFN_PHYS(start_pfn), r_start, r_end);
		u64 end = clamp_val(PFN_PHYS(end_pfn), r_start, r_end);
		अगर (start >= end)
			जारी;

		/*
		 * अगर it is overlapping with brk pgt, we need to
		 * alloc pgt buf from memblock instead.
		 */
		can_use_brk_pgt = max(start, (u64)pgt_buf_end<<PAGE_SHIFT) >=
				    min(end, (u64)pgt_buf_top<<PAGE_SHIFT);
		init_memory_mapping(start, end, PAGE_KERNEL);
		mapped_ram_size += end - start;
		can_use_brk_pgt = true;
	पूर्ण

	वापस mapped_ram_size;
पूर्ण

अटल अचिन्हित दीर्घ __init get_new_step_size(अचिन्हित दीर्घ step_size)
अणु
	/*
	 * Initial mapped size is PMD_SIZE (2M).
	 * We can not set step_size to be PUD_SIZE (1G) yet.
	 * In worse हाल, when we cross the 1G boundary, and
	 * PG_LEVEL_2M is not set, we will need 1+1+512 pages (2M + 8k)
	 * to map 1G range with PTE. Hence we use one less than the
	 * dअगरference of page table level shअगरts.
	 *
	 * Don't need to worry about overflow in the top-करोwn हाल, on 32bit,
	 * when step_size is 0, round_करोwn() वापसs 0 क्रम start, and that
	 * turns it पूर्णांकo 0x100000000ULL.
	 * In the bottom-up हाल, round_up(x, 0) वापसs 0 though too, which
	 * needs to be taken पूर्णांकo consideration by the code below.
	 */
	वापस step_size << (PMD_SHIFT - PAGE_SHIFT - 1);
पूर्ण

/**
 * memory_map_top_करोwn - Map [map_start, map_end) top करोwn
 * @map_start: start address of the target memory range
 * @map_end: end address of the target memory range
 *
 * This function will setup direct mapping क्रम memory range
 * [map_start, map_end) in top-करोwn. That said, the page tables
 * will be allocated at the end of the memory, and we map the
 * memory in top-करोwn.
 */
अटल व्योम __init memory_map_top_करोwn(अचिन्हित दीर्घ map_start,
				       अचिन्हित दीर्घ map_end)
अणु
	अचिन्हित दीर्घ real_end, last_start;
	अचिन्हित दीर्घ step_size;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ mapped_ram_size = 0;

	/* xen has big range in reserved near end of ram, skip it at first.*/
	addr = memblock_find_in_range(map_start, map_end, PMD_SIZE, PMD_SIZE);
	real_end = addr + PMD_SIZE;

	/* step_size need to be small so pgt_buf from BRK could cover it */
	step_size = PMD_SIZE;
	max_pfn_mapped = 0; /* will get exact value next */
	min_pfn_mapped = real_end >> PAGE_SHIFT;
	last_start = real_end;

	/*
	 * We start from the top (end of memory) and go to the bottom.
	 * The memblock_find_in_range() माला_लो us a block of RAM from the
	 * end of RAM in [min_pfn_mapped, max_pfn_mapped) used as new pages
	 * क्रम page table.
	 */
	जबतक (last_start > map_start) अणु
		अचिन्हित दीर्घ start;

		अगर (last_start > step_size) अणु
			start = round_करोwn(last_start - 1, step_size);
			अगर (start < map_start)
				start = map_start;
		पूर्ण अन्यथा
			start = map_start;
		mapped_ram_size += init_range_memory_mapping(start,
							last_start);
		last_start = start;
		min_pfn_mapped = last_start >> PAGE_SHIFT;
		अगर (mapped_ram_size >= step_size)
			step_size = get_new_step_size(step_size);
	पूर्ण

	अगर (real_end < map_end)
		init_range_memory_mapping(real_end, map_end);
पूर्ण

/**
 * memory_map_bottom_up - Map [map_start, map_end) bottom up
 * @map_start: start address of the target memory range
 * @map_end: end address of the target memory range
 *
 * This function will setup direct mapping क्रम memory range
 * [map_start, map_end) in bottom-up. Since we have limited the
 * bottom-up allocation above the kernel, the page tables will
 * be allocated just above the kernel and we map the memory
 * in [map_start, map_end) in bottom-up.
 */
अटल व्योम __init memory_map_bottom_up(अचिन्हित दीर्घ map_start,
					अचिन्हित दीर्घ map_end)
अणु
	अचिन्हित दीर्घ next, start;
	अचिन्हित दीर्घ mapped_ram_size = 0;
	/* step_size need to be small so pgt_buf from BRK could cover it */
	अचिन्हित दीर्घ step_size = PMD_SIZE;

	start = map_start;
	min_pfn_mapped = start >> PAGE_SHIFT;

	/*
	 * We start from the bottom (@map_start) and go to the top (@map_end).
	 * The memblock_find_in_range() माला_लो us a block of RAM from the
	 * end of RAM in [min_pfn_mapped, max_pfn_mapped) used as new pages
	 * क्रम page table.
	 */
	जबतक (start < map_end) अणु
		अगर (step_size && map_end - start > step_size) अणु
			next = round_up(start + 1, step_size);
			अगर (next > map_end)
				next = map_end;
		पूर्ण अन्यथा अणु
			next = map_end;
		पूर्ण

		mapped_ram_size += init_range_memory_mapping(start, next);
		start = next;

		अगर (mapped_ram_size >= step_size)
			step_size = get_new_step_size(step_size);
	पूर्ण
पूर्ण

/*
 * The real mode trampoline, which is required क्रम bootstrapping CPUs
 * occupies only a small area under the low 1MB.  See reserve_real_mode()
 * क्रम details.
 *
 * If KASLR is disabled the first PGD entry of the direct mapping is copied
 * to map the real mode trampoline.
 *
 * If KASLR is enabled, copy only the PUD which covers the low 1MB
 * area. This limits the अक्रमomization granularity to 1GB क्रम both 4-level
 * and 5-level paging.
 */
अटल व्योम __init init_trampoline(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	अगर (!kaslr_memory_enabled())
		trampoline_pgd_entry = init_top_pgt[pgd_index(__PAGE_OFFSET)];
	अन्यथा
		init_trampoline_kaslr();
#पूर्ण_अगर
पूर्ण

व्योम __init init_mem_mapping(व्योम)
अणु
	अचिन्हित दीर्घ end;

	pti_check_bootसमय_disable();
	probe_page_size_mask();
	setup_pcid();

#अगर_घोषित CONFIG_X86_64
	end = max_pfn << PAGE_SHIFT;
#अन्यथा
	end = max_low_pfn << PAGE_SHIFT;
#पूर्ण_अगर

	/* the ISA range is always mapped regardless of memory holes */
	init_memory_mapping(0, ISA_END_ADDRESS, PAGE_KERNEL);

	/* Init the trampoline, possibly with KASLR memory offset */
	init_trampoline();

	/*
	 * If the allocation is in bottom-up direction, we setup direct mapping
	 * in bottom-up, otherwise we setup direct mapping in top-करोwn.
	 */
	अगर (memblock_bottom_up()) अणु
		अचिन्हित दीर्घ kernel_end = __pa_symbol(_end);

		/*
		 * we need two separate calls here. This is because we want to
		 * allocate page tables above the kernel. So we first map
		 * [kernel_end, end) to make memory above the kernel be mapped
		 * as soon as possible. And then use page tables allocated above
		 * the kernel to map [ISA_END_ADDRESS, kernel_end).
		 */
		memory_map_bottom_up(kernel_end, end);
		memory_map_bottom_up(ISA_END_ADDRESS, kernel_end);
	पूर्ण अन्यथा अणु
		memory_map_top_करोwn(ISA_END_ADDRESS, end);
	पूर्ण

#अगर_घोषित CONFIG_X86_64
	अगर (max_pfn > max_low_pfn) अणु
		/* can we preserve max_low_pfn ?*/
		max_low_pfn = max_pfn;
	पूर्ण
#अन्यथा
	early_ioremap_page_table_range_init();
#पूर्ण_अगर

	load_cr3(swapper_pg_dir);
	__flush_tlb_all();

	x86_init.hyper.init_mem_mapping();

	early_memtest(0, max_pfn_mapped << PAGE_SHIFT);
पूर्ण

/*
 * Initialize an mm_काष्ठा to be used during poking and a poपूर्णांकer to be used
 * during patching.
 */
व्योम __init poking_init(व्योम)
अणु
	spinlock_t *ptl;
	pte_t *ptep;

	poking_mm = copy_init_mm();
	BUG_ON(!poking_mm);

	/*
	 * Ranकरोmize the poking address, but make sure that the following page
	 * will be mapped at the same PMD. We need 2 pages, so find space क्रम 3,
	 * and adjust the address अगर the PMD ends after the first one.
	 */
	poking_addr = TASK_UNMAPPED_BASE;
	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE))
		poking_addr += (kaslr_get_अक्रमom_दीर्घ("Poking") & PAGE_MASK) %
			(TASK_SIZE - TASK_UNMAPPED_BASE - 3 * PAGE_SIZE);

	अगर (((poking_addr + PAGE_SIZE) & ~PMD_MASK) == 0)
		poking_addr += PAGE_SIZE;

	/*
	 * We need to trigger the allocation of the page-tables that will be
	 * needed क्रम poking now. Later, poking may be perक्रमmed in an atomic
	 * section, which might cause allocation to fail.
	 */
	ptep = get_locked_pte(poking_mm, poking_addr, &ptl);
	BUG_ON(!ptep);
	pte_unmap_unlock(ptep, ptl);
पूर्ण

/*
 * devmem_is_allowed() checks to see अगर /dev/mem access to a certain address
 * is valid. The argument is a physical page number.
 *
 * On x86, access has to be given to the first megabyte of RAM because that
 * area traditionally contains BIOS code and data regions used by X, करोsemu,
 * and similar apps. Since they map the entire memory range, the whole range
 * must be allowed (क्रम mapping), but any areas that would otherwise be
 * disallowed are flagged as being "zero filled" instead of rejected.
 * Access has to be given to non-kernel-ram areas as well, these contain the
 * PCI mmio resources as well as potential bios/acpi data regions.
 */
पूर्णांक devmem_is_allowed(अचिन्हित दीर्घ pagenr)
अणु
	अगर (region_पूर्णांकersects(PFN_PHYS(pagenr), PAGE_SIZE,
				IORESOURCE_SYSTEM_RAM, IORES_DESC_NONE)
			!= REGION_DISJOINT) अणु
		/*
		 * For disallowed memory regions in the low 1MB range,
		 * request that the page be shown as all zeros.
		 */
		अगर (pagenr < 256)
			वापस 2;

		वापस 0;
	पूर्ण

	/*
	 * This must follow RAM test, since System RAM is considered a
	 * restricted resource under CONFIG_STRICT_IOMEM.
	 */
	अगर (iomem_is_exclusive(pagenr << PAGE_SHIFT)) अणु
		/* Low 1MB bypasses iomem restrictions. */
		अगर (pagenr < 256)
			वापस 1;

		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

व्योम मुक्त_init_pages(स्थिर अक्षर *what, अचिन्हित दीर्घ begin, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ begin_aligned, end_aligned;

	/* Make sure boundaries are page aligned */
	begin_aligned = PAGE_ALIGN(begin);
	end_aligned   = end & PAGE_MASK;

	अगर (WARN_ON(begin_aligned != begin || end_aligned != end)) अणु
		begin = begin_aligned;
		end   = end_aligned;
	पूर्ण

	अगर (begin >= end)
		वापस;

	/*
	 * If debugging page accesses then करो not मुक्त this memory but
	 * mark them not present - any buggy init-section access will
	 * create a kernel page fault:
	 */
	अगर (debug_pagealloc_enabled()) अणु
		pr_info("debug: unmapping init [mem %#010lx-%#010lx]\n",
			begin, end - 1);
		/*
		 * Inक्रमm kmemleak about the hole in the memory since the
		 * corresponding pages will be unmapped.
		 */
		kmemleak_मुक्त_part((व्योम *)begin, end - begin);
		set_memory_np(begin, (end - begin) >> PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		/*
		 * We just marked the kernel text पढ़ो only above, now that
		 * we are going to मुक्त part of that, we need to make that
		 * ग_लिखोable and non-executable first.
		 */
		set_memory_nx(begin, (end - begin) >> PAGE_SHIFT);
		set_memory_rw(begin, (end - begin) >> PAGE_SHIFT);

		मुक्त_reserved_area((व्योम *)begin, (व्योम *)end,
				   POISON_FREE_INITMEM, what);
	पूर्ण
पूर्ण

/*
 * begin/end can be in the direct map or the "high kernel mapping"
 * used क्रम the kernel image only.  मुक्त_init_pages() will करो the
 * right thing क्रम either kind of address.
 */
व्योम मुक्त_kernel_image_pages(स्थिर अक्षर *what, व्योम *begin, व्योम *end)
अणु
	अचिन्हित दीर्घ begin_ul = (अचिन्हित दीर्घ)begin;
	अचिन्हित दीर्घ end_ul = (अचिन्हित दीर्घ)end;
	अचिन्हित दीर्घ len_pages = (end_ul - begin_ul) >> PAGE_SHIFT;

	मुक्त_init_pages(what, begin_ul, end_ul);

	/*
	 * PTI maps some of the kernel पूर्णांकo userspace.  For perक्रमmance,
	 * this includes some kernel areas that करो not contain secrets.
	 * Those areas might be adjacent to the parts of the kernel image
	 * being मुक्तd, which may contain secrets.  Remove the "high kernel
	 * image mapping" क्रम these मुक्तd areas, ensuring they are not even
	 * potentially vulnerable to Meltकरोwn regardless of the specअगरic
	 * optimizations PTI is currently using.
	 *
	 * The "noalias" prevents unmapping the direct map alias which is
	 * needed to access the मुक्तd pages.
	 *
	 * This is only valid क्रम 64bit kernels. 32bit has only one mapping
	 * which can't be treated in this way क्रम obvious reasons.
	 */
	अगर (IS_ENABLED(CONFIG_X86_64) && cpu_feature_enabled(X86_FEATURE_PTI))
		set_memory_np_noalias(begin_ul, len_pages);
पूर्ण

व्योम __ref मुक्त_iniपंचांगem(व्योम)
अणु
	e820__पुनः_स्मृतिate_tables();

	mem_encrypt_मुक्त_decrypted_mem();

	मुक्त_kernel_image_pages("unused kernel image (initmem)",
				&__init_begin, &__init_end);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INITRD
व्योम __init मुक्त_initrd_mem(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * end could be not aligned, and We can not align that,
	 * decompressor could be confused by aligned initrd_end
	 * We alपढ़ोy reserve the end partial page beक्रमe in
	 *   - i386_start_kernel()
	 *   - x86_64_start_kernel()
	 *   - relocate_initrd()
	 * So here We can करो PAGE_ALIGN() safely to get partial page to be मुक्तd
	 */
	मुक्त_init_pages("initrd", start, PAGE_ALIGN(end));
पूर्ण
#पूर्ण_अगर

/*
 * Calculate the precise size of the DMA zone (first 16 MB of RAM),
 * and pass it to the MM layer - to help it set zone watermarks more
 * accurately.
 *
 * Done on 64-bit प्रणालीs only क्रम the समय being, although 32-bit प्रणालीs
 * might benefit from this as well.
 */
व्योम __init memblock_find_dma_reserve(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	u64 nr_pages = 0, nr_मुक्त_pages = 0;
	अचिन्हित दीर्घ start_pfn, end_pfn;
	phys_addr_t start_addr, end_addr;
	पूर्णांक i;
	u64 u;

	/*
	 * Iterate over all memory ranges (मुक्त and reserved ones alike),
	 * to calculate the total number of pages in the first 16 MB of RAM:
	 */
	nr_pages = 0;
	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start_pfn, &end_pfn, शून्य) अणु
		start_pfn = min(start_pfn, MAX_DMA_PFN);
		end_pfn   = min(end_pfn,   MAX_DMA_PFN);

		nr_pages += end_pfn - start_pfn;
	पूर्ण

	/*
	 * Iterate over मुक्त memory ranges to calculate the number of मुक्त
	 * pages in the DMA zone, जबतक not counting potential partial
	 * pages at the beginning or the end of the range:
	 */
	nr_मुक्त_pages = 0;
	क्रम_each_मुक्त_mem_range(u, NUMA_NO_NODE, MEMBLOCK_NONE, &start_addr, &end_addr, शून्य) अणु
		start_pfn = min_t(अचिन्हित दीर्घ, PFN_UP(start_addr), MAX_DMA_PFN);
		end_pfn   = min_t(अचिन्हित दीर्घ, PFN_DOWN(end_addr), MAX_DMA_PFN);

		अगर (start_pfn < end_pfn)
			nr_मुक्त_pages += end_pfn - start_pfn;
	पूर्ण

	set_dma_reserve(nr_pages - nr_मुक्त_pages);
#पूर्ण_अगर
पूर्ण

व्योम __init zone_sizes_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES];

	स_रखो(max_zone_pfns, 0, माप(max_zone_pfns));

#अगर_घोषित CONFIG_ZONE_DMA
	max_zone_pfns[ZONE_DMA]		= min(MAX_DMA_PFN, max_low_pfn);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZONE_DMA32
	max_zone_pfns[ZONE_DMA32]	= min(MAX_DMA32_PFN, max_low_pfn);
#पूर्ण_अगर
	max_zone_pfns[ZONE_NORMAL]	= max_low_pfn;
#अगर_घोषित CONFIG_HIGHMEM
	max_zone_pfns[ZONE_HIGHMEM]	= max_pfn;
#पूर्ण_अगर

	मुक्त_area_init(max_zone_pfns);
पूर्ण

__visible DEFINE_PER_CPU_ALIGNED(काष्ठा tlb_state, cpu_tlbstate) = अणु
	.loaded_mm = &init_mm,
	.next_asid = 1,
	.cr4 = ~0UL,	/* fail hard अगर we screw up cr4 shaकरोw initialization */
पूर्ण;

व्योम update_cache_mode_entry(अचिन्हित entry, क्रमागत page_cache_mode cache)
अणु
	/* entry 0 MUST be WB (hardwired to speed up translations) */
	BUG_ON(!entry && cache != _PAGE_CACHE_MODE_WB);

	__cachemode2pte_tbl[cache] = __cm_idx2pte(entry);
	__pte2cachemode_tbl[entry] = cache;
पूर्ण

#अगर_घोषित CONFIG_SWAP
अचिन्हित दीर्घ max_swapfile_size(व्योम)
अणु
	अचिन्हित दीर्घ pages;

	pages = generic_max_swapfile_size();

	अगर (boot_cpu_has_bug(X86_BUG_L1TF) && l1tf_mitigation != L1TF_MITIGATION_OFF) अणु
		/* Limit the swap file size to MAX_PA/2 क्रम L1TF workaround */
		अचिन्हित दीर्घ दीर्घ l1tf_limit = l1tf_pfn_limit();
		/*
		 * We encode swap offsets also with 3 bits below those क्रम pfn
		 * which makes the usable limit higher.
		 */
#अगर CONFIG_PGTABLE_LEVELS > 2
		l1tf_limit <<= PAGE_SHIFT - SWP_OFFSET_FIRST_BIT;
#पूर्ण_अगर
		pages = min_t(अचिन्हित दीर्घ दीर्घ, l1tf_limit, pages);
	पूर्ण
	वापस pages;
पूर्ण
#पूर्ण_अगर

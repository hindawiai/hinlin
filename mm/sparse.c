<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sparse memory mappings.
 */
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/memblock.h>
#समावेश <linux/compiler.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>

#समावेश "internal.h"
#समावेश <यंत्र/dma.h>

/*
 * Permanent SPARSEMEM data:
 *
 * 1) mem_section	- memory sections, mem_map's क्रम valid memory
 */
#अगर_घोषित CONFIG_SPARSEMEM_EXTREME
काष्ठा mem_section **mem_section;
#अन्यथा
काष्ठा mem_section mem_section[NR_SECTION_ROOTS][SECTIONS_PER_ROOT]
	____cacheline_पूर्णांकernodealigned_in_smp;
#पूर्ण_अगर
EXPORT_SYMBOL(mem_section);

#अगर_घोषित NODE_NOT_IN_PAGE_FLAGS
/*
 * If we did not store the node number in the page then we have to
 * करो a lookup in the section_to_node_table in order to find which
 * node the page beदीर्घs to.
 */
#अगर MAX_NUMNODES <= 256
अटल u8 section_to_node_table[NR_MEM_SECTIONS] __cacheline_aligned;
#अन्यथा
अटल u16 section_to_node_table[NR_MEM_SECTIONS] __cacheline_aligned;
#पूर्ण_अगर

पूर्णांक page_to_nid(स्थिर काष्ठा page *page)
अणु
	वापस section_to_node_table[page_to_section(page)];
पूर्ण
EXPORT_SYMBOL(page_to_nid);

अटल व्योम set_section_nid(अचिन्हित दीर्घ section_nr, पूर्णांक nid)
अणु
	section_to_node_table[section_nr] = nid;
पूर्ण
#अन्यथा /* !NODE_NOT_IN_PAGE_FLAGS */
अटल अंतरभूत व्योम set_section_nid(अचिन्हित दीर्घ section_nr, पूर्णांक nid)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARSEMEM_EXTREME
अटल noअंतरभूत काष्ठा mem_section __ref *sparse_index_alloc(पूर्णांक nid)
अणु
	काष्ठा mem_section *section = शून्य;
	अचिन्हित दीर्घ array_size = SECTIONS_PER_ROOT *
				   माप(काष्ठा mem_section);

	अगर (slab_is_available()) अणु
		section = kzalloc_node(array_size, GFP_KERNEL, nid);
	पूर्ण अन्यथा अणु
		section = memblock_alloc_node(array_size, SMP_CACHE_BYTES,
					      nid);
		अगर (!section)
			panic("%s: Failed to allocate %lu bytes nid=%d\n",
			      __func__, array_size, nid);
	पूर्ण

	वापस section;
पूर्ण

अटल पूर्णांक __meminit sparse_index_init(अचिन्हित दीर्घ section_nr, पूर्णांक nid)
अणु
	अचिन्हित दीर्घ root = SECTION_NR_TO_ROOT(section_nr);
	काष्ठा mem_section *section;

	/*
	 * An existing section is possible in the sub-section hotplug
	 * हाल. First hot-add instantiates, follow-on hot-add reuses
	 * the existing section.
	 *
	 * The mem_hotplug_lock resolves the apparent race below.
	 */
	अगर (mem_section[root])
		वापस 0;

	section = sparse_index_alloc(nid);
	अगर (!section)
		वापस -ENOMEM;

	mem_section[root] = section;

	वापस 0;
पूर्ण
#अन्यथा /* !SPARSEMEM_EXTREME */
अटल अंतरभूत पूर्णांक sparse_index_init(अचिन्हित दीर्घ section_nr, पूर्णांक nid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARSEMEM_EXTREME
अचिन्हित दीर्घ __section_nr(काष्ठा mem_section *ms)
अणु
	अचिन्हित दीर्घ root_nr;
	काष्ठा mem_section *root = शून्य;

	क्रम (root_nr = 0; root_nr < NR_SECTION_ROOTS; root_nr++) अणु
		root = __nr_to_section(root_nr * SECTIONS_PER_ROOT);
		अगर (!root)
			जारी;

		अगर ((ms >= root) && (ms < (root + SECTIONS_PER_ROOT)))
		     अवरोध;
	पूर्ण

	VM_BUG_ON(!root);

	वापस (root_nr * SECTIONS_PER_ROOT) + (ms - root);
पूर्ण
#अन्यथा
अचिन्हित दीर्घ __section_nr(काष्ठा mem_section *ms)
अणु
	वापस (अचिन्हित दीर्घ)(ms - mem_section[0]);
पूर्ण
#पूर्ण_अगर

/*
 * During early boot, beक्रमe section_mem_map is used क्रम an actual
 * mem_map, we use section_mem_map to store the section's NUMA
 * node.  This keeps us from having to use another data काष्ठाure.  The
 * node inक्रमmation is cleared just beक्रमe we store the real mem_map.
 */
अटल अंतरभूत अचिन्हित दीर्घ sparse_encode_early_nid(पूर्णांक nid)
अणु
	वापस (nid << SECTION_NID_SHIFT);
पूर्ण

अटल अंतरभूत पूर्णांक sparse_early_nid(काष्ठा mem_section *section)
अणु
	वापस (section->section_mem_map >> SECTION_NID_SHIFT);
पूर्ण

/* Validate the physical addressing limitations of the model */
व्योम __meminit mminit_validate_memmodel_limits(अचिन्हित दीर्घ *start_pfn,
						अचिन्हित दीर्घ *end_pfn)
अणु
	अचिन्हित दीर्घ max_sparsemem_pfn = 1UL << (MAX_PHYSMEM_BITS-PAGE_SHIFT);

	/*
	 * Sanity checks - करो not allow an architecture to pass
	 * in larger pfns than the maximum scope of sparsemem:
	 */
	अगर (*start_pfn > max_sparsemem_pfn) अणु
		mminit_dprपूर्णांकk(MMINIT_WARNING, "pfnvalidation",
			"Start of range %lu -> %lu exceeds SPARSEMEM max %lu\n",
			*start_pfn, *end_pfn, max_sparsemem_pfn);
		WARN_ON_ONCE(1);
		*start_pfn = max_sparsemem_pfn;
		*end_pfn = max_sparsemem_pfn;
	पूर्ण अन्यथा अगर (*end_pfn > max_sparsemem_pfn) अणु
		mminit_dprपूर्णांकk(MMINIT_WARNING, "pfnvalidation",
			"End of range %lu -> %lu exceeds SPARSEMEM max %lu\n",
			*start_pfn, *end_pfn, max_sparsemem_pfn);
		WARN_ON_ONCE(1);
		*end_pfn = max_sparsemem_pfn;
	पूर्ण
पूर्ण

/*
 * There are a number of बार that we loop over NR_MEM_SECTIONS,
 * looking क्रम section_present() on each.  But, when we have very
 * large physical address spaces, NR_MEM_SECTIONS can also be
 * very large which makes the loops quite दीर्घ.
 *
 * Keeping track of this gives us an easy way to अवरोध out of
 * those loops early.
 */
अचिन्हित दीर्घ __highest_present_section_nr;
अटल व्योम section_mark_present(काष्ठा mem_section *ms)
अणु
	अचिन्हित दीर्घ section_nr = __section_nr(ms);

	अगर (section_nr > __highest_present_section_nr)
		__highest_present_section_nr = section_nr;

	ms->section_mem_map |= SECTION_MARKED_PRESENT;
पूर्ण

#घोषणा क्रम_each_present_section_nr(start, section_nr)		\
	क्रम (section_nr = next_present_section_nr(start-1);	\
	     ((section_nr != -1) &&				\
	      (section_nr <= __highest_present_section_nr));	\
	     section_nr = next_present_section_nr(section_nr))

अटल अंतरभूत अचिन्हित दीर्घ first_present_section_nr(व्योम)
अणु
	वापस next_present_section_nr(-1);
पूर्ण

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
अटल व्योम subsection_mask_set(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक idx = subsection_map_index(pfn);
	पूर्णांक end = subsection_map_index(pfn + nr_pages - 1);

	biपंचांगap_set(map, idx, end - idx + 1);
पूर्ण

व्योम __init subsection_map_init(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक end_sec = pfn_to_section_nr(pfn + nr_pages - 1);
	अचिन्हित दीर्घ nr, start_sec = pfn_to_section_nr(pfn);

	अगर (!nr_pages)
		वापस;

	क्रम (nr = start_sec; nr <= end_sec; nr++) अणु
		काष्ठा mem_section *ms;
		अचिन्हित दीर्घ pfns;

		pfns = min(nr_pages, PAGES_PER_SECTION
				- (pfn & ~PAGE_SECTION_MASK));
		ms = __nr_to_section(nr);
		subsection_mask_set(ms->usage->subsection_map, pfn, pfns);

		pr_debug("%s: sec: %lu pfns: %lu set(%d, %d)\n", __func__, nr,
				pfns, subsection_map_index(pfn),
				subsection_map_index(pfn + pfns - 1));

		pfn += pfns;
		nr_pages -= pfns;
	पूर्ण
पूर्ण
#अन्यथा
व्योम __init subsection_map_init(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
पूर्ण
#पूर्ण_अगर

/* Record a memory area against a node. */
अटल व्योम __init memory_present(पूर्णांक nid, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ pfn;

#अगर_घोषित CONFIG_SPARSEMEM_EXTREME
	अगर (unlikely(!mem_section)) अणु
		अचिन्हित दीर्घ size, align;

		size = माप(काष्ठा mem_section *) * NR_SECTION_ROOTS;
		align = 1 << (INTERNODE_CACHE_SHIFT);
		mem_section = memblock_alloc(size, align);
		अगर (!mem_section)
			panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
			      __func__, size, align);
	पूर्ण
#पूर्ण_अगर

	start &= PAGE_SECTION_MASK;
	mminit_validate_memmodel_limits(&start, &end);
	क्रम (pfn = start; pfn < end; pfn += PAGES_PER_SECTION) अणु
		अचिन्हित दीर्घ section = pfn_to_section_nr(pfn);
		काष्ठा mem_section *ms;

		sparse_index_init(section, nid);
		set_section_nid(section, nid);

		ms = __nr_to_section(section);
		अगर (!ms->section_mem_map) अणु
			ms->section_mem_map = sparse_encode_early_nid(nid) |
							SECTION_IS_ONLINE;
			section_mark_present(ms);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Mark all memblocks as present using memory_present().
 * This is a convenience function that is useful to mark all of the प्रणालीs
 * memory as present during initialization.
 */
अटल व्योम __init memblocks_present(व्योम)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक i, nid;

	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start, &end, &nid)
		memory_present(nid, start, end);
पूर्ण

/*
 * Subtle, we encode the real pfn पूर्णांकo the mem_map such that
 * the identity pfn - section_mem_map will वापस the actual
 * physical page frame number.
 */
अटल अचिन्हित दीर्घ sparse_encode_mem_map(काष्ठा page *mem_map, अचिन्हित दीर्घ pnum)
अणु
	अचिन्हित दीर्घ coded_mem_map =
		(अचिन्हित दीर्घ)(mem_map - (section_nr_to_pfn(pnum)));
	BUILD_BUG_ON(SECTION_MAP_LAST_BIT > (1UL<<PFN_SECTION_SHIFT));
	BUG_ON(coded_mem_map & ~SECTION_MAP_MASK);
	वापस coded_mem_map;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
/*
 * Decode mem_map from the coded memmap
 */
काष्ठा page *sparse_decode_mem_map(अचिन्हित दीर्घ coded_mem_map, अचिन्हित दीर्घ pnum)
अणु
	/* mask off the extra low bits of inक्रमmation */
	coded_mem_map &= SECTION_MAP_MASK;
	वापस ((काष्ठा page *)coded_mem_map) + section_nr_to_pfn(pnum);
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

अटल व्योम __meminit sparse_init_one_section(काष्ठा mem_section *ms,
		अचिन्हित दीर्घ pnum, काष्ठा page *mem_map,
		काष्ठा mem_section_usage *usage, अचिन्हित दीर्घ flags)
अणु
	ms->section_mem_map &= ~SECTION_MAP_MASK;
	ms->section_mem_map |= sparse_encode_mem_map(mem_map, pnum)
		| SECTION_HAS_MEM_MAP | flags;
	ms->usage = usage;
पूर्ण

अटल अचिन्हित दीर्घ usemap_size(व्योम)
अणु
	वापस BITS_TO_LONGS(SECTION_BLOCKFLAGS_BITS) * माप(अचिन्हित दीर्घ);
पूर्ण

माप_प्रकार mem_section_usage_size(व्योम)
अणु
	वापस माप(काष्ठा mem_section_usage) + usemap_size();
पूर्ण

अटल अंतरभूत phys_addr_t pgdat_to_phys(काष्ठा pglist_data *pgdat)
अणु
#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
	वापस __pa_symbol(pgdat);
#अन्यथा
	वापस __pa(pgdat);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
अटल काष्ठा mem_section_usage * __init
sparse_early_usemaps_alloc_pgdat_section(काष्ठा pglist_data *pgdat,
					 अचिन्हित दीर्घ size)
अणु
	काष्ठा mem_section_usage *usage;
	अचिन्हित दीर्घ goal, limit;
	पूर्णांक nid;
	/*
	 * A page may contain usemaps क्रम other sections preventing the
	 * page being मुक्तd and making a section unremovable जबतक
	 * other sections referencing the usemap reमुख्य active. Similarly,
	 * a pgdat can prevent a section being हटाओd. If section A
	 * contains a pgdat and section B contains the usemap, both
	 * sections become पूर्णांकer-dependent. This allocates usemaps
	 * from the same section as the pgdat where possible to aव्योम
	 * this problem.
	 */
	goal = pgdat_to_phys(pgdat) & (PAGE_SECTION_MASK << PAGE_SHIFT);
	limit = goal + (1UL << PA_SECTION_SHIFT);
	nid = early_pfn_to_nid(goal >> PAGE_SHIFT);
again:
	usage = memblock_alloc_try_nid(size, SMP_CACHE_BYTES, goal, limit, nid);
	अगर (!usage && limit) अणु
		limit = 0;
		जाओ again;
	पूर्ण
	वापस usage;
पूर्ण

अटल व्योम __init check_usemap_section_nr(पूर्णांक nid,
		काष्ठा mem_section_usage *usage)
अणु
	अचिन्हित दीर्घ usemap_snr, pgdat_snr;
	अटल अचिन्हित दीर्घ old_usemap_snr;
	अटल अचिन्हित दीर्घ old_pgdat_snr;
	काष्ठा pglist_data *pgdat = NODE_DATA(nid);
	पूर्णांक usemap_nid;

	/* First call */
	अगर (!old_usemap_snr) अणु
		old_usemap_snr = NR_MEM_SECTIONS;
		old_pgdat_snr = NR_MEM_SECTIONS;
	पूर्ण

	usemap_snr = pfn_to_section_nr(__pa(usage) >> PAGE_SHIFT);
	pgdat_snr = pfn_to_section_nr(pgdat_to_phys(pgdat) >> PAGE_SHIFT);
	अगर (usemap_snr == pgdat_snr)
		वापस;

	अगर (old_usemap_snr == usemap_snr && old_pgdat_snr == pgdat_snr)
		/* skip redundant message */
		वापस;

	old_usemap_snr = usemap_snr;
	old_pgdat_snr = pgdat_snr;

	usemap_nid = sparse_early_nid(__nr_to_section(usemap_snr));
	अगर (usemap_nid != nid) अणु
		pr_info("node %d must be removed before remove section %ld\n",
			nid, usemap_snr);
		वापस;
	पूर्ण
	/*
	 * There is a circular dependency.
	 * Some platक्रमms allow un-removable section because they will just
	 * gather other removable sections क्रम dynamic partitioning.
	 * Just notअगरy un-removable section's number here.
	 */
	pr_info("Section %ld and %ld (node %d) have a circular dependency on usemap and pgdat allocations\n",
		usemap_snr, pgdat_snr, nid);
पूर्ण
#अन्यथा
अटल काष्ठा mem_section_usage * __init
sparse_early_usemaps_alloc_pgdat_section(काष्ठा pglist_data *pgdat,
					 अचिन्हित दीर्घ size)
अणु
	वापस memblock_alloc_node(size, SMP_CACHE_BYTES, pgdat->node_id);
पूर्ण

अटल व्योम __init check_usemap_section_nr(पूर्णांक nid,
		काष्ठा mem_section_usage *usage)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTREMOVE */

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
अटल अचिन्हित दीर्घ __init section_map_size(व्योम)
अणु
	वापस ALIGN(माप(काष्ठा page) * PAGES_PER_SECTION, PMD_SIZE);
पूर्ण

#अन्यथा
अटल अचिन्हित दीर्घ __init section_map_size(व्योम)
अणु
	वापस PAGE_ALIGN(माप(काष्ठा page) * PAGES_PER_SECTION);
पूर्ण

काष्ठा page __init *__populate_section_memmap(अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages, पूर्णांक nid, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ size = section_map_size();
	काष्ठा page *map = sparse_buffer_alloc(size);
	phys_addr_t addr = __pa(MAX_DMA_ADDRESS);

	अगर (map)
		वापस map;

	map = memblock_alloc_try_nid_raw(size, size, addr,
					  MEMBLOCK_ALLOC_ACCESSIBLE, nid);
	अगर (!map)
		panic("%s: Failed to allocate %lu bytes align=0x%lx nid=%d from=%pa\n",
		      __func__, size, PAGE_SIZE, nid, &addr);

	वापस map;
पूर्ण
#पूर्ण_अगर /* !CONFIG_SPARSEMEM_VMEMMAP */

अटल व्योम *sparsemap_buf __meminitdata;
अटल व्योम *sparsemap_buf_end __meminitdata;

अटल अंतरभूत व्योम __meminit sparse_buffer_मुक्त(अचिन्हित दीर्घ size)
अणु
	WARN_ON(!sparsemap_buf || size == 0);
	memblock_मुक्त_early(__pa(sparsemap_buf), size);
पूर्ण

अटल व्योम __init sparse_buffer_init(अचिन्हित दीर्घ size, पूर्णांक nid)
अणु
	phys_addr_t addr = __pa(MAX_DMA_ADDRESS);
	WARN_ON(sparsemap_buf);	/* क्रमgot to call sparse_buffer_fini()? */
	/*
	 * Pre-allocated buffer is मुख्यly used by __populate_section_memmap
	 * and we want it to be properly aligned to the section size - this is
	 * especially the हाल क्रम VMEMMAP which maps memmap to PMDs
	 */
	sparsemap_buf = memblock_alloc_exact_nid_raw(size, section_map_size(),
					addr, MEMBLOCK_ALLOC_ACCESSIBLE, nid);
	sparsemap_buf_end = sparsemap_buf + size;
पूर्ण

अटल व्योम __init sparse_buffer_fini(व्योम)
अणु
	अचिन्हित दीर्घ size = sparsemap_buf_end - sparsemap_buf;

	अगर (sparsemap_buf && size > 0)
		sparse_buffer_मुक्त(size);
	sparsemap_buf = शून्य;
पूर्ण

व्योम * __meminit sparse_buffer_alloc(अचिन्हित दीर्घ size)
अणु
	व्योम *ptr = शून्य;

	अगर (sparsemap_buf) अणु
		ptr = (व्योम *) roundup((अचिन्हित दीर्घ)sparsemap_buf, size);
		अगर (ptr + size > sparsemap_buf_end)
			ptr = शून्य;
		अन्यथा अणु
			/* Free redundant aligned space */
			अगर ((अचिन्हित दीर्घ)(ptr - sparsemap_buf) > 0)
				sparse_buffer_मुक्त((अचिन्हित दीर्घ)(ptr - sparsemap_buf));
			sparsemap_buf = ptr + size;
		पूर्ण
	पूर्ण
	वापस ptr;
पूर्ण

व्योम __weak __meminit vmemmap_populate_prपूर्णांक_last(व्योम)
अणु
पूर्ण

/*
 * Initialize sparse on a specअगरic node. The node spans [pnum_begin, pnum_end)
 * And number of present sections in this node is map_count.
 */
अटल व्योम __init sparse_init_nid(पूर्णांक nid, अचिन्हित दीर्घ pnum_begin,
				   अचिन्हित दीर्घ pnum_end,
				   अचिन्हित दीर्घ map_count)
अणु
	काष्ठा mem_section_usage *usage;
	अचिन्हित दीर्घ pnum;
	काष्ठा page *map;

	usage = sparse_early_usemaps_alloc_pgdat_section(NODE_DATA(nid),
			mem_section_usage_size() * map_count);
	अगर (!usage) अणु
		pr_err("%s: node[%d] usemap allocation failed", __func__, nid);
		जाओ failed;
	पूर्ण
	sparse_buffer_init(map_count * section_map_size(), nid);
	क्रम_each_present_section_nr(pnum_begin, pnum) अणु
		अचिन्हित दीर्घ pfn = section_nr_to_pfn(pnum);

		अगर (pnum >= pnum_end)
			अवरोध;

		map = __populate_section_memmap(pfn, PAGES_PER_SECTION,
				nid, शून्य);
		अगर (!map) अणु
			pr_err("%s: node[%d] memory map backing failed. Some memory will not be available.",
			       __func__, nid);
			pnum_begin = pnum;
			sparse_buffer_fini();
			जाओ failed;
		पूर्ण
		check_usemap_section_nr(nid, usage);
		sparse_init_one_section(__nr_to_section(pnum), pnum, map, usage,
				SECTION_IS_EARLY);
		usage = (व्योम *) usage + mem_section_usage_size();
	पूर्ण
	sparse_buffer_fini();
	वापस;
failed:
	/* We failed to allocate, mark all the following pnums as not present */
	क्रम_each_present_section_nr(pnum_begin, pnum) अणु
		काष्ठा mem_section *ms;

		अगर (pnum >= pnum_end)
			अवरोध;
		ms = __nr_to_section(pnum);
		ms->section_mem_map = 0;
	पूर्ण
पूर्ण

/*
 * Allocate the accumulated non-linear sections, allocate a mem_map
 * क्रम each and record the physical to section mapping.
 */
व्योम __init sparse_init(व्योम)
अणु
	अचिन्हित दीर्घ pnum_end, pnum_begin, map_count = 1;
	पूर्णांक nid_begin;

	memblocks_present();

	pnum_begin = first_present_section_nr();
	nid_begin = sparse_early_nid(__nr_to_section(pnum_begin));

	/* Setup pageblock_order क्रम HUGETLB_PAGE_SIZE_VARIABLE */
	set_pageblock_order();

	क्रम_each_present_section_nr(pnum_begin + 1, pnum_end) अणु
		पूर्णांक nid = sparse_early_nid(__nr_to_section(pnum_end));

		अगर (nid == nid_begin) अणु
			map_count++;
			जारी;
		पूर्ण
		/* Init node with sections in range [pnum_begin, pnum_end) */
		sparse_init_nid(nid_begin, pnum_begin, pnum_end, map_count);
		nid_begin = nid;
		pnum_begin = pnum_end;
		map_count = 1;
	पूर्ण
	/* cover the last node */
	sparse_init_nid(nid_begin, pnum_begin, pnum_end, map_count);
	vmemmap_populate_prपूर्णांक_last();
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG

/* Mark all memory sections within the pfn range as online */
व्योम online_mem_sections(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = start_pfn; pfn < end_pfn; pfn += PAGES_PER_SECTION) अणु
		अचिन्हित दीर्घ section_nr = pfn_to_section_nr(pfn);
		काष्ठा mem_section *ms;

		/* onlining code should never touch invalid ranges */
		अगर (WARN_ON(!valid_section_nr(section_nr)))
			जारी;

		ms = __nr_to_section(section_nr);
		ms->section_mem_map |= SECTION_IS_ONLINE;
	पूर्ण
पूर्ण

/* Mark all memory sections within the pfn range as offline */
व्योम offline_mem_sections(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = start_pfn; pfn < end_pfn; pfn += PAGES_PER_SECTION) अणु
		अचिन्हित दीर्घ section_nr = pfn_to_section_nr(pfn);
		काष्ठा mem_section *ms;

		/*
		 * TODO this needs some द्विगुन checking. Offlining code makes
		 * sure to check pfn_valid but those checks might be just bogus
		 */
		अगर (WARN_ON(!valid_section_nr(section_nr)))
			जारी;

		ms = __nr_to_section(section_nr);
		ms->section_mem_map &= ~SECTION_IS_ONLINE;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
अटल काष्ठा page * __meminit populate_section_memmap(अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages, पूर्णांक nid, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	वापस __populate_section_memmap(pfn, nr_pages, nid, alपंचांगap);
पूर्ण

अटल व्योम depopulate_section_memmap(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) pfn_to_page(pfn);
	अचिन्हित दीर्घ end = start + nr_pages * माप(काष्ठा page);

	vmemmap_मुक्त(start, end, alपंचांगap);
पूर्ण
अटल व्योम मुक्त_map_booपंचांगem(काष्ठा page *memmap)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)memmap;
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)(memmap + PAGES_PER_SECTION);

	vmemmap_मुक्त(start, end, शून्य);
पूर्ण

अटल पूर्णांक clear_subsection_map(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	DECLARE_BITMAP(map, SUBSECTIONS_PER_SECTION) = अणु 0 पूर्ण;
	DECLARE_BITMAP(पंचांगp, SUBSECTIONS_PER_SECTION) = अणु 0 पूर्ण;
	काष्ठा mem_section *ms = __pfn_to_section(pfn);
	अचिन्हित दीर्घ *subsection_map = ms->usage
		? &ms->usage->subsection_map[0] : शून्य;

	subsection_mask_set(map, pfn, nr_pages);
	अगर (subsection_map)
		biपंचांगap_and(पंचांगp, map, subsection_map, SUBSECTIONS_PER_SECTION);

	अगर (WARN(!subsection_map || !biपंचांगap_equal(पंचांगp, map, SUBSECTIONS_PER_SECTION),
				"section already deactivated (%#lx + %ld)\n",
				pfn, nr_pages))
		वापस -EINVAL;

	biपंचांगap_xor(subsection_map, map, subsection_map, SUBSECTIONS_PER_SECTION);
	वापस 0;
पूर्ण

अटल bool is_subsection_map_empty(काष्ठा mem_section *ms)
अणु
	वापस biपंचांगap_empty(&ms->usage->subsection_map[0],
			    SUBSECTIONS_PER_SECTION);
पूर्ण

अटल पूर्णांक fill_subsection_map(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा mem_section *ms = __pfn_to_section(pfn);
	DECLARE_BITMAP(map, SUBSECTIONS_PER_SECTION) = अणु 0 पूर्ण;
	अचिन्हित दीर्घ *subsection_map;
	पूर्णांक rc = 0;

	subsection_mask_set(map, pfn, nr_pages);

	subsection_map = &ms->usage->subsection_map[0];

	अगर (biपंचांगap_empty(map, SUBSECTIONS_PER_SECTION))
		rc = -EINVAL;
	अन्यथा अगर (biपंचांगap_पूर्णांकersects(map, subsection_map, SUBSECTIONS_PER_SECTION))
		rc = -EEXIST;
	अन्यथा
		biपंचांगap_or(subsection_map, map, subsection_map,
				SUBSECTIONS_PER_SECTION);

	वापस rc;
पूर्ण
#अन्यथा
काष्ठा page * __meminit populate_section_memmap(अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages, पूर्णांक nid, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	वापस kvदो_स्मृति_node(array_size(माप(काष्ठा page),
					PAGES_PER_SECTION), GFP_KERNEL, nid);
पूर्ण

अटल व्योम depopulate_section_memmap(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	kvमुक्त(pfn_to_page(pfn));
पूर्ण

अटल व्योम मुक्त_map_booपंचांगem(काष्ठा page *memmap)
अणु
	अचिन्हित दीर्घ maps_section_nr, removing_section_nr, i;
	अचिन्हित दीर्घ magic, nr_pages;
	काष्ठा page *page = virt_to_page(memmap);

	nr_pages = PAGE_ALIGN(PAGES_PER_SECTION * माप(काष्ठा page))
		>> PAGE_SHIFT;

	क्रम (i = 0; i < nr_pages; i++, page++) अणु
		magic = (अचिन्हित दीर्घ) page->मुक्तlist;

		BUG_ON(magic == NODE_INFO);

		maps_section_nr = pfn_to_section_nr(page_to_pfn(page));
		removing_section_nr = page_निजी(page);

		/*
		 * When this function is called, the removing section is
		 * logical offlined state. This means all pages are isolated
		 * from page allocator. If removing section's memmap is placed
		 * on the same section, it must not be मुक्तd.
		 * If it is मुक्तd, page allocator may allocate it which will
		 * be हटाओd physically soon.
		 */
		अगर (maps_section_nr != removing_section_nr)
			put_page_booपंचांगem(page);
	पूर्ण
पूर्ण

अटल पूर्णांक clear_subsection_map(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	वापस 0;
पूर्ण

अटल bool is_subsection_map_empty(काष्ठा mem_section *ms)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक fill_subsection_map(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARSEMEM_VMEMMAP */

/*
 * To deactivate a memory region, there are 3 हालs to handle across
 * two configurations (SPARSEMEM_VMEMMAP=अणुy,nपूर्ण):
 *
 * 1. deactivation of a partial hot-added section (only possible in
 *    the SPARSEMEM_VMEMMAP=y हाल).
 *      a) section was present at memory init.
 *      b) section was hot-added post memory init.
 * 2. deactivation of a complete hot-added section.
 * 3. deactivation of a complete section from memory init.
 *
 * For 1, when subsection_map करोes not empty we will not be मुक्तing the
 * usage map, but still need to मुक्त the vmemmap range.
 *
 * For 2 and 3, the SPARSEMEM_VMEMMAP=अणुy,nपूर्ण हालs are unअगरied
 */
अटल व्योम section_deactivate(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	काष्ठा mem_section *ms = __pfn_to_section(pfn);
	bool section_is_early = early_section(ms);
	काष्ठा page *memmap = शून्य;
	bool empty;

	अगर (clear_subsection_map(pfn, nr_pages))
		वापस;

	empty = is_subsection_map_empty(ms);
	अगर (empty) अणु
		अचिन्हित दीर्घ section_nr = pfn_to_section_nr(pfn);

		/*
		 * When removing an early section, the usage map is kept (as the
		 * usage maps of other sections fall पूर्णांकo the same page). It
		 * will be re-used when re-adding the section - which is then no
		 * दीर्घer an early section. If the usage map is PageReserved, it
		 * was allocated during boot.
		 */
		अगर (!PageReserved(virt_to_page(ms->usage))) अणु
			kमुक्त(ms->usage);
			ms->usage = शून्य;
		पूर्ण
		memmap = sparse_decode_mem_map(ms->section_mem_map, section_nr);
		/*
		 * Mark the section invalid so that valid_section()
		 * वापस false. This prevents code from dereferencing
		 * ms->usage array.
		 */
		ms->section_mem_map &= ~SECTION_HAS_MEM_MAP;
	पूर्ण

	/*
	 * The memmap of early sections is always fully populated. See
	 * section_activate() and pfn_valid() .
	 */
	अगर (!section_is_early)
		depopulate_section_memmap(pfn, nr_pages, alपंचांगap);
	अन्यथा अगर (memmap)
		मुक्त_map_booपंचांगem(memmap);

	अगर (empty)
		ms->section_mem_map = (अचिन्हित दीर्घ)शून्य;
पूर्ण

अटल काष्ठा page * __meminit section_activate(पूर्णांक nid, अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	काष्ठा mem_section *ms = __pfn_to_section(pfn);
	काष्ठा mem_section_usage *usage = शून्य;
	काष्ठा page *memmap;
	पूर्णांक rc = 0;

	अगर (!ms->usage) अणु
		usage = kzalloc(mem_section_usage_size(), GFP_KERNEL);
		अगर (!usage)
			वापस ERR_PTR(-ENOMEM);
		ms->usage = usage;
	पूर्ण

	rc = fill_subsection_map(pfn, nr_pages);
	अगर (rc) अणु
		अगर (usage)
			ms->usage = शून्य;
		kमुक्त(usage);
		वापस ERR_PTR(rc);
	पूर्ण

	/*
	 * The early init code करोes not consider partially populated
	 * initial sections, it simply assumes that memory will never be
	 * referenced.  If we hot-add memory पूर्णांकo such a section then we
	 * करो not need to populate the memmap and can simply reuse what
	 * is alपढ़ोy there.
	 */
	अगर (nr_pages < PAGES_PER_SECTION && early_section(ms))
		वापस pfn_to_page(pfn);

	memmap = populate_section_memmap(pfn, nr_pages, nid, alपंचांगap);
	अगर (!memmap) अणु
		section_deactivate(pfn, nr_pages, alपंचांगap);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस memmap;
पूर्ण

/**
 * sparse_add_section - add a memory section, or populate an existing one
 * @nid: The node to add section on
 * @start_pfn: start pfn of the memory range
 * @nr_pages: number of pfns to add in the section
 * @alपंचांगap: device page map
 *
 * This is only पूर्णांकended क्रम hotplug.
 *
 * Note that only VMEMMAP supports sub-section aligned hotplug,
 * the proper alignment and size are gated by check_pfn_span().
 *
 *
 * Return:
 * * 0		- On success.
 * * -EEXIST	- Section has been present.
 * * -ENOMEM	- Out of memory.
 */
पूर्णांक __meminit sparse_add_section(पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ nr_pages, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ section_nr = pfn_to_section_nr(start_pfn);
	काष्ठा mem_section *ms;
	काष्ठा page *memmap;
	पूर्णांक ret;

	ret = sparse_index_init(section_nr, nid);
	अगर (ret < 0)
		वापस ret;

	memmap = section_activate(nid, start_pfn, nr_pages, alपंचांगap);
	अगर (IS_ERR(memmap))
		वापस PTR_ERR(memmap);

	/*
	 * Poison uninitialized काष्ठा pages in order to catch invalid flags
	 * combinations.
	 */
	page_init_poison(memmap, माप(काष्ठा page) * nr_pages);

	ms = __nr_to_section(section_nr);
	set_section_nid(section_nr, nid);
	section_mark_present(ms);

	/* Align memmap to section boundary in the subsection हाल */
	अगर (section_nr_to_pfn(section_nr) != start_pfn)
		memmap = pfn_to_page(section_nr_to_pfn(section_nr));
	sparse_init_one_section(ms, section_nr, memmap, ms->usage, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_FAILURE
अटल व्योम clear_hwpoisoned_pages(काष्ठा page *memmap, पूर्णांक nr_pages)
अणु
	पूर्णांक i;

	/*
	 * A further optimization is to have per section refcounted
	 * num_poisoned_pages.  But that would need more space per memmap, so
	 * क्रम now just करो a quick global check to speed up this routine in the
	 * असलence of bad pages.
	 */
	अगर (atomic_दीर्घ_पढ़ो(&num_poisoned_pages) == 0)
		वापस;

	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (PageHWPoison(&memmap[i])) अणु
			num_poisoned_pages_dec();
			ClearPageHWPoison(&memmap[i]);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम clear_hwpoisoned_pages(काष्ठा page *memmap, पूर्णांक nr_pages)
अणु
पूर्ण
#पूर्ण_अगर

व्योम sparse_हटाओ_section(काष्ठा mem_section *ms, अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages, अचिन्हित दीर्घ map_offset,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	clear_hwpoisoned_pages(pfn_to_page(pfn) + map_offset,
			nr_pages - map_offset);
	section_deactivate(pfn, nr_pages, alपंचांगap);
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 Advanced Micro Devices, Inc.
 *
 * Author: Joerg Roedel <joerg.roedel@amd.com>
 */

#घोषणा pr_fmt(fmt)	"DMA-API: " fmt

#समावेश <linux/sched/task_stack.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/sections.h>
#समावेश "debug.h"

#घोषणा HASH_SIZE       16384ULL
#घोषणा HASH_FN_SHIFT   13
#घोषणा HASH_FN_MASK    (HASH_SIZE - 1)

#घोषणा PREALLOC_DMA_DEBUG_ENTRIES (1 << 16)
/* If the pool runs out, add this many new entries at once */
#घोषणा DMA_DEBUG_DYNAMIC_ENTRIES (PAGE_SIZE / माप(काष्ठा dma_debug_entry))

क्रमागत अणु
	dma_debug_single,
	dma_debug_sg,
	dma_debug_coherent,
	dma_debug_resource,
पूर्ण;

क्रमागत map_err_types अणु
	MAP_ERR_CHECK_NOT_APPLICABLE,
	MAP_ERR_NOT_CHECKED,
	MAP_ERR_CHECKED,
पूर्ण;

#घोषणा DMA_DEBUG_STACKTRACE_ENTRIES 5

/**
 * काष्ठा dma_debug_entry - track a dma_map* or dma_alloc_coherent mapping
 * @list: node on pre-allocated मुक्त_entries list
 * @dev: 'dev' argument to dma_map_अणुpage|single|sgपूर्ण or dma_alloc_coherent
 * @size: length of the mapping
 * @type: single, page, sg, coherent
 * @direction: क्रमागत dma_data_direction
 * @sg_call_ents: 'nents' from dma_map_sg
 * @sg_mapped_ents: 'mapped_ents' from dma_map_sg
 * @pfn: page frame of the start address
 * @offset: offset of mapping relative to pfn
 * @map_err_type: track whether dma_mapping_error() was checked
 * @stacktrace: support backtraces when a violation is detected
 */
काष्ठा dma_debug_entry अणु
	काष्ठा list_head list;
	काष्ठा device    *dev;
	u64              dev_addr;
	u64              size;
	पूर्णांक              type;
	पूर्णांक              direction;
	पूर्णांक		 sg_call_ents;
	पूर्णांक		 sg_mapped_ents;
	अचिन्हित दीर्घ	 pfn;
	माप_प्रकार		 offset;
	क्रमागत map_err_types  map_err_type;
#अगर_घोषित CONFIG_STACKTRACE
	अचिन्हित पूर्णांक	stack_len;
	अचिन्हित दीर्घ	stack_entries[DMA_DEBUG_STACKTRACE_ENTRIES];
#पूर्ण_अगर
पूर्ण ____cacheline_aligned_in_smp;

प्रकार bool (*match_fn)(काष्ठा dma_debug_entry *, काष्ठा dma_debug_entry *);

काष्ठा hash_bucket अणु
	काष्ठा list_head list;
	spinlock_t lock;
पूर्ण;

/* Hash list to save the allocated dma addresses */
अटल काष्ठा hash_bucket dma_entry_hash[HASH_SIZE];
/* List of pre-allocated dma_debug_entry's */
अटल LIST_HEAD(मुक्त_entries);
/* Lock क्रम the list above */
अटल DEFINE_SPINLOCK(मुक्त_entries_lock);

/* Global disable flag - will be set in हाल of an error */
अटल bool global_disable __पढ़ो_mostly;

/* Early initialization disable flag, set at the end of dma_debug_init */
अटल bool dma_debug_initialized __पढ़ो_mostly;

अटल अंतरभूत bool dma_debug_disabled(व्योम)
अणु
	वापस global_disable || !dma_debug_initialized;
पूर्ण

/* Global error count */
अटल u32 error_count;

/* Global error show enable*/
अटल u32 show_all_errors __पढ़ो_mostly;
/* Number of errors to show */
अटल u32 show_num_errors = 1;

अटल u32 num_मुक्त_entries;
अटल u32 min_मुक्त_entries;
अटल u32 nr_total_entries;

/* number of pपुनः_स्मृतिated entries requested by kernel cmdline */
अटल u32 nr_pपुनः_स्मृति_entries = PREALLOC_DMA_DEBUG_ENTRIES;

/* per-driver filter related state */

#घोषणा NAME_MAX_LEN	64

अटल अक्षर                  current_driver_name[NAME_MAX_LEN] __पढ़ो_mostly;
अटल काष्ठा device_driver *current_driver                    __पढ़ो_mostly;

अटल DEFINE_RWLOCK(driver_name_lock);

अटल स्थिर अक्षर *स्थिर maperr2str[] = अणु
	[MAP_ERR_CHECK_NOT_APPLICABLE] = "dma map error check not applicable",
	[MAP_ERR_NOT_CHECKED] = "dma map error not checked",
	[MAP_ERR_CHECKED] = "dma map error checked",
पूर्ण;

अटल स्थिर अक्षर *type2name[] = अणु
	[dma_debug_single] = "single",
	[dma_debug_sg] = "scather-gather",
	[dma_debug_coherent] = "coherent",
	[dma_debug_resource] = "resource",
पूर्ण;

अटल स्थिर अक्षर *dir2name[] = अणु
	[DMA_BIसूचीECTIONAL]	= "DMA_BIDIRECTIONAL",
	[DMA_TO_DEVICE]		= "DMA_TO_DEVICE",
	[DMA_FROM_DEVICE]	= "DMA_FROM_DEVICE",
	[DMA_NONE]		= "DMA_NONE",
पूर्ण;

/*
 * The access to some variables in this macro is racy. We can't use atomic_t
 * here because all these variables are exported to debugfs. Some of them even
 * ग_लिखोable. This is also the reason why a lock won't help much. But anyway,
 * the races are no big deal. Here is why:
 *
 *   error_count: the addition is racy, but the worst thing that can happen is
 *                that we करोn't count some errors
 *   show_num_errors: the subtraction is racy. Also no big deal because in
 *                    worst हाल this will result in one warning more in the
 *                    प्रणाली log than the user configured. This variable is
 *                    ग_लिखोable via debugfs.
 */
अटल अंतरभूत व्योम dump_entry_trace(काष्ठा dma_debug_entry *entry)
अणु
#अगर_घोषित CONFIG_STACKTRACE
	अगर (entry) अणु
		pr_warn("Mapped at:\n");
		stack_trace_prपूर्णांक(entry->stack_entries, entry->stack_len, 0);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल bool driver_filter(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv;
	अचिन्हित दीर्घ flags;
	bool ret;

	/* driver filter off */
	अगर (likely(!current_driver_name[0]))
		वापस true;

	/* driver filter on and initialized */
	अगर (current_driver && dev && dev->driver == current_driver)
		वापस true;

	/* driver filter on, but we can't filter on a शून्य device... */
	अगर (!dev)
		वापस false;

	अगर (current_driver || !current_driver_name[0])
		वापस false;

	/* driver filter on but not yet initialized */
	drv = dev->driver;
	अगर (!drv)
		वापस false;

	/* lock to protect against change of current_driver_name */
	पढ़ो_lock_irqsave(&driver_name_lock, flags);

	ret = false;
	अगर (drv->name &&
	    म_भेदन(current_driver_name, drv->name, NAME_MAX_LEN - 1) == 0) अणु
		current_driver = drv;
		ret = true;
	पूर्ण

	पढ़ो_unlock_irqrestore(&driver_name_lock, flags);

	वापस ret;
पूर्ण

#घोषणा err_prपूर्णांकk(dev, entry, क्रमmat, arg...) करो अणु			\
		error_count += 1;					\
		अगर (driver_filter(dev) &&				\
		    (show_all_errors || show_num_errors > 0)) अणु		\
			WARN(1, pr_fmt("%s %s: ") क्रमmat,		\
			     dev ? dev_driver_string(dev) : "NULL",	\
			     dev ? dev_name(dev) : "NULL", ## arg);	\
			dump_entry_trace(entry);			\
		पूर्ण							\
		अगर (!show_all_errors && show_num_errors > 0)		\
			show_num_errors -= 1;				\
	पूर्ण जबतक (0);

/*
 * Hash related functions
 *
 * Every DMA-API request is saved पूर्णांकo a काष्ठा dma_debug_entry. To
 * have quick access to these काष्ठाs they are stored पूर्णांकo a hash.
 */
अटल पूर्णांक hash_fn(काष्ठा dma_debug_entry *entry)
अणु
	/*
	 * Hash function is based on the dma address.
	 * We use bits 20-27 here as the index पूर्णांकo the hash
	 */
	वापस (entry->dev_addr >> HASH_FN_SHIFT) & HASH_FN_MASK;
पूर्ण

/*
 * Request exclusive access to a hash bucket क्रम a given dma_debug_entry.
 */
अटल काष्ठा hash_bucket *get_hash_bucket(काष्ठा dma_debug_entry *entry,
					   अचिन्हित दीर्घ *flags)
	__acquires(&dma_entry_hash[idx].lock)
अणु
	पूर्णांक idx = hash_fn(entry);
	अचिन्हित दीर्घ __flags;

	spin_lock_irqsave(&dma_entry_hash[idx].lock, __flags);
	*flags = __flags;
	वापस &dma_entry_hash[idx];
पूर्ण

/*
 * Give up exclusive access to the hash bucket
 */
अटल व्योम put_hash_bucket(काष्ठा hash_bucket *bucket,
			    अचिन्हित दीर्घ flags)
	__releases(&bucket->lock)
अणु
	spin_unlock_irqrestore(&bucket->lock, flags);
पूर्ण

अटल bool exact_match(काष्ठा dma_debug_entry *a, काष्ठा dma_debug_entry *b)
अणु
	वापस ((a->dev_addr == b->dev_addr) &&
		(a->dev == b->dev)) ? true : false;
पूर्ण

अटल bool containing_match(काष्ठा dma_debug_entry *a,
			     काष्ठा dma_debug_entry *b)
अणु
	अगर (a->dev != b->dev)
		वापस false;

	अगर ((b->dev_addr <= a->dev_addr) &&
	    ((b->dev_addr + b->size) >= (a->dev_addr + a->size)))
		वापस true;

	वापस false;
पूर्ण

/*
 * Search a given entry in the hash bucket list
 */
अटल काष्ठा dma_debug_entry *__hash_bucket_find(काष्ठा hash_bucket *bucket,
						  काष्ठा dma_debug_entry *ref,
						  match_fn match)
अणु
	काष्ठा dma_debug_entry *entry, *ret = शून्य;
	पूर्णांक matches = 0, match_lvl, last_lvl = -1;

	list_क्रम_each_entry(entry, &bucket->list, list) अणु
		अगर (!match(ref, entry))
			जारी;

		/*
		 * Some drivers map the same physical address multiple
		 * बार. Without a hardware IOMMU this results in the
		 * same device addresses being put पूर्णांकo the dma-debug
		 * hash multiple बार too. This can result in false
		 * positives being reported. Thereक्रमe we implement a
		 * best-fit algorithm here which वापसs the entry from
		 * the hash which fits best to the reference value
		 * instead of the first-fit.
		 */
		matches += 1;
		match_lvl = 0;
		entry->size         == ref->size         ? ++match_lvl : 0;
		entry->type         == ref->type         ? ++match_lvl : 0;
		entry->direction    == ref->direction    ? ++match_lvl : 0;
		entry->sg_call_ents == ref->sg_call_ents ? ++match_lvl : 0;

		अगर (match_lvl == 4) अणु
			/* perfect-fit - वापस the result */
			वापस entry;
		पूर्ण अन्यथा अगर (match_lvl > last_lvl) अणु
			/*
			 * We found an entry that fits better then the
			 * previous one or it is the 1st match.
			 */
			last_lvl = match_lvl;
			ret      = entry;
		पूर्ण
	पूर्ण

	/*
	 * If we have multiple matches but no perfect-fit, just वापस
	 * शून्य.
	 */
	ret = (matches == 1) ? ret : शून्य;

	वापस ret;
पूर्ण

अटल काष्ठा dma_debug_entry *bucket_find_exact(काष्ठा hash_bucket *bucket,
						 काष्ठा dma_debug_entry *ref)
अणु
	वापस __hash_bucket_find(bucket, ref, exact_match);
पूर्ण

अटल काष्ठा dma_debug_entry *bucket_find_contain(काष्ठा hash_bucket **bucket,
						   काष्ठा dma_debug_entry *ref,
						   अचिन्हित दीर्घ *flags)
अणु

	अचिन्हित पूर्णांक max_range = dma_get_max_seg_size(ref->dev);
	काष्ठा dma_debug_entry *entry, index = *ref;
	अचिन्हित पूर्णांक range = 0;

	जबतक (range <= max_range) अणु
		entry = __hash_bucket_find(*bucket, ref, containing_match);

		अगर (entry)
			वापस entry;

		/*
		 * Nothing found, go back a hash bucket
		 */
		put_hash_bucket(*bucket, *flags);
		range          += (1 << HASH_FN_SHIFT);
		index.dev_addr -= (1 << HASH_FN_SHIFT);
		*bucket = get_hash_bucket(&index, flags);
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Add an entry to a hash bucket
 */
अटल व्योम hash_bucket_add(काष्ठा hash_bucket *bucket,
			    काष्ठा dma_debug_entry *entry)
अणु
	list_add_tail(&entry->list, &bucket->list);
पूर्ण

/*
 * Remove entry from a hash bucket list
 */
अटल व्योम hash_bucket_del(काष्ठा dma_debug_entry *entry)
अणु
	list_del(&entry->list);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ phys_addr(काष्ठा dma_debug_entry *entry)
अणु
	अगर (entry->type == dma_debug_resource)
		वापस __pfn_to_phys(entry->pfn) + entry->offset;

	वापस page_to_phys(pfn_to_page(entry->pfn)) + entry->offset;
पूर्ण

/*
 * Dump mapping entries क्रम debugging purposes
 */
व्योम debug_dma_dump_mappings(काष्ठा device *dev)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < HASH_SIZE; idx++) अणु
		काष्ठा hash_bucket *bucket = &dma_entry_hash[idx];
		काष्ठा dma_debug_entry *entry;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&bucket->lock, flags);

		list_क्रम_each_entry(entry, &bucket->list, list) अणु
			अगर (!dev || dev == entry->dev) अणु
				dev_info(entry->dev,
					 "%s idx %d P=%Lx N=%lx D=%Lx L=%Lx %s %s\n",
					 type2name[entry->type], idx,
					 phys_addr(entry), entry->pfn,
					 entry->dev_addr, entry->size,
					 dir2name[entry->direction],
					 maperr2str[entry->map_err_type]);
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&bucket->lock, flags);
		cond_resched();
	पूर्ण
पूर्ण

/*
 * For each mapping (initial cacheline in the हाल of
 * dma_alloc_coherent/dma_map_page, initial cacheline in each page of a
 * scatterlist, or the cacheline specअगरied in dma_map_single) insert
 * पूर्णांकo this tree using the cacheline as the key. At
 * dma_unmap_अणुsingle|sg|pageपूर्ण or dma_मुक्त_coherent delete the entry.  If
 * the entry alपढ़ोy exists at insertion समय add a tag as a reference
 * count क्रम the overlapping mappings.  For now, the overlap tracking
 * just ensures that 'unmaps' balance 'maps' beक्रमe marking the
 * cacheline idle, but we should also be flagging overlaps as an API
 * violation.
 *
 * Memory usage is mostly स्थिरrained by the maximum number of available
 * dma-debug entries in that we need a मुक्त dma_debug_entry beक्रमe
 * inserting पूर्णांकo the tree.  In the हाल of dma_map_page and
 * dma_alloc_coherent there is only one dma_debug_entry and one
 * dma_active_cacheline entry to track per event.  dma_map_sg(), on the
 * other hand, consumes a single dma_debug_entry, but inserts 'nents'
 * entries पूर्णांकo the tree.
 */
अटल RADIX_TREE(dma_active_cacheline, GFP_NOWAIT);
अटल DEFINE_SPINLOCK(radix_lock);
#घोषणा ACTIVE_CACHELINE_MAX_OVERLAP ((1 << RADIX_TREE_MAX_TAGS) - 1)
#घोषणा CACHELINE_PER_PAGE_SHIFT (PAGE_SHIFT - L1_CACHE_SHIFT)
#घोषणा CACHELINES_PER_PAGE (1 << CACHELINE_PER_PAGE_SHIFT)

अटल phys_addr_t to_cacheline_number(काष्ठा dma_debug_entry *entry)
अणु
	वापस (entry->pfn << CACHELINE_PER_PAGE_SHIFT) +
		(entry->offset >> L1_CACHE_SHIFT);
पूर्ण

अटल पूर्णांक active_cacheline_पढ़ो_overlap(phys_addr_t cln)
अणु
	पूर्णांक overlap = 0, i;

	क्रम (i = RADIX_TREE_MAX_TAGS - 1; i >= 0; i--)
		अगर (radix_tree_tag_get(&dma_active_cacheline, cln, i))
			overlap |= 1 << i;
	वापस overlap;
पूर्ण

अटल पूर्णांक active_cacheline_set_overlap(phys_addr_t cln, पूर्णांक overlap)
अणु
	पूर्णांक i;

	अगर (overlap > ACTIVE_CACHELINE_MAX_OVERLAP || overlap < 0)
		वापस overlap;

	क्रम (i = RADIX_TREE_MAX_TAGS - 1; i >= 0; i--)
		अगर (overlap & 1 << i)
			radix_tree_tag_set(&dma_active_cacheline, cln, i);
		अन्यथा
			radix_tree_tag_clear(&dma_active_cacheline, cln, i);

	वापस overlap;
पूर्ण

अटल व्योम active_cacheline_inc_overlap(phys_addr_t cln)
अणु
	पूर्णांक overlap = active_cacheline_पढ़ो_overlap(cln);

	overlap = active_cacheline_set_overlap(cln, ++overlap);

	/* If we overflowed the overlap counter then we're potentially
	 * leaking dma-mappings.
	 */
	WARN_ONCE(overlap > ACTIVE_CACHELINE_MAX_OVERLAP,
		  pr_fmt("exceeded %d overlapping mappings of cacheline %pa\n"),
		  ACTIVE_CACHELINE_MAX_OVERLAP, &cln);
पूर्ण

अटल पूर्णांक active_cacheline_dec_overlap(phys_addr_t cln)
अणु
	पूर्णांक overlap = active_cacheline_पढ़ो_overlap(cln);

	वापस active_cacheline_set_overlap(cln, --overlap);
पूर्ण

अटल पूर्णांक active_cacheline_insert(काष्ठा dma_debug_entry *entry)
अणु
	phys_addr_t cln = to_cacheline_number(entry);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	/* If the device is not writing memory then we करोn't have any
	 * concerns about the cpu consuming stale data.  This mitigates
	 * legitimate usages of overlapping mappings.
	 */
	अगर (entry->direction == DMA_TO_DEVICE)
		वापस 0;

	spin_lock_irqsave(&radix_lock, flags);
	rc = radix_tree_insert(&dma_active_cacheline, cln, entry);
	अगर (rc == -EEXIST)
		active_cacheline_inc_overlap(cln);
	spin_unlock_irqrestore(&radix_lock, flags);

	वापस rc;
पूर्ण

अटल व्योम active_cacheline_हटाओ(काष्ठा dma_debug_entry *entry)
अणु
	phys_addr_t cln = to_cacheline_number(entry);
	अचिन्हित दीर्घ flags;

	/* ...mirror the insert हाल */
	अगर (entry->direction == DMA_TO_DEVICE)
		वापस;

	spin_lock_irqsave(&radix_lock, flags);
	/* since we are counting overlaps the final put of the
	 * cacheline will occur when the overlap count is 0.
	 * active_cacheline_dec_overlap() वापसs -1 in that हाल
	 */
	अगर (active_cacheline_dec_overlap(cln) < 0)
		radix_tree_delete(&dma_active_cacheline, cln);
	spin_unlock_irqrestore(&radix_lock, flags);
पूर्ण

/*
 * Wrapper function क्रम adding an entry to the hash.
 * This function takes care of locking itself.
 */
अटल व्योम add_dma_entry(काष्ठा dma_debug_entry *entry)
अणु
	काष्ठा hash_bucket *bucket;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	bucket = get_hash_bucket(entry, &flags);
	hash_bucket_add(bucket, entry);
	put_hash_bucket(bucket, flags);

	rc = active_cacheline_insert(entry);
	अगर (rc == -ENOMEM) अणु
		pr_err("cacheline tracking ENOMEM, dma-debug disabled\n");
		global_disable = true;
	पूर्ण

	/* TODO: report -EEXIST errors here as overlapping mappings are
	 * not supported by the DMA API
	 */
पूर्ण

अटल पूर्णांक dma_debug_create_entries(gfp_t gfp)
अणु
	काष्ठा dma_debug_entry *entry;
	पूर्णांक i;

	entry = (व्योम *)get_zeroed_page(gfp);
	अगर (!entry)
		वापस -ENOMEM;

	क्रम (i = 0; i < DMA_DEBUG_DYNAMIC_ENTRIES; i++)
		list_add_tail(&entry[i].list, &मुक्त_entries);

	num_मुक्त_entries += DMA_DEBUG_DYNAMIC_ENTRIES;
	nr_total_entries += DMA_DEBUG_DYNAMIC_ENTRIES;

	वापस 0;
पूर्ण

अटल काष्ठा dma_debug_entry *__dma_entry_alloc(व्योम)
अणु
	काष्ठा dma_debug_entry *entry;

	entry = list_entry(मुक्त_entries.next, काष्ठा dma_debug_entry, list);
	list_del(&entry->list);
	स_रखो(entry, 0, माप(*entry));

	num_मुक्त_entries -= 1;
	अगर (num_मुक्त_entries < min_मुक्त_entries)
		min_मुक्त_entries = num_मुक्त_entries;

	वापस entry;
पूर्ण

अटल व्योम __dma_entry_alloc_check_leak(व्योम)
अणु
	u32 पंचांगp = nr_total_entries % nr_pपुनः_स्मृति_entries;

	/* Shout each समय we tick over some multiple of the initial pool */
	अगर (पंचांगp < DMA_DEBUG_DYNAMIC_ENTRIES) अणु
		pr_info("dma_debug_entry pool grown to %u (%u00%%)\n",
			nr_total_entries,
			(nr_total_entries / nr_pपुनः_स्मृति_entries));
	पूर्ण
पूर्ण

/* काष्ठा dma_entry allocator
 *
 * The next two functions implement the allocator क्रम
 * काष्ठा dma_debug_entries.
 */
अटल काष्ठा dma_debug_entry *dma_entry_alloc(व्योम)
अणु
	काष्ठा dma_debug_entry *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&मुक्त_entries_lock, flags);
	अगर (num_मुक्त_entries == 0) अणु
		अगर (dma_debug_create_entries(GFP_ATOMIC)) अणु
			global_disable = true;
			spin_unlock_irqrestore(&मुक्त_entries_lock, flags);
			pr_err("debugging out of memory - disabling\n");
			वापस शून्य;
		पूर्ण
		__dma_entry_alloc_check_leak();
	पूर्ण

	entry = __dma_entry_alloc();

	spin_unlock_irqrestore(&मुक्त_entries_lock, flags);

#अगर_घोषित CONFIG_STACKTRACE
	entry->stack_len = stack_trace_save(entry->stack_entries,
					    ARRAY_SIZE(entry->stack_entries),
					    1);
#पूर्ण_अगर
	वापस entry;
पूर्ण

अटल व्योम dma_entry_मुक्त(काष्ठा dma_debug_entry *entry)
अणु
	अचिन्हित दीर्घ flags;

	active_cacheline_हटाओ(entry);

	/*
	 * add to beginning of the list - this way the entries are
	 * more likely cache hot when they are पुनः_स्मृतिated.
	 */
	spin_lock_irqsave(&मुक्त_entries_lock, flags);
	list_add(&entry->list, &मुक्त_entries);
	num_मुक्त_entries += 1;
	spin_unlock_irqrestore(&मुक्त_entries_lock, flags);
पूर्ण

/*
 * DMA-API debugging init code
 *
 * The init code करोes two things:
 *   1. Initialize core data काष्ठाures
 *   2. Pपुनः_स्मृतिate a given number of dma_debug_entry काष्ठाs
 */

अटल sमाप_प्रकार filter_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[NAME_MAX_LEN + 1];
	अचिन्हित दीर्घ flags;
	पूर्णांक len;

	अगर (!current_driver_name[0])
		वापस 0;

	/*
	 * We can't copy to userspace directly because current_driver_name can
	 * only be पढ़ो under the driver_name_lock with irqs disabled. So
	 * create a temporary copy first.
	 */
	पढ़ो_lock_irqsave(&driver_name_lock, flags);
	len = scnम_लिखो(buf, NAME_MAX_LEN + 1, "%s\n", current_driver_name);
	पढ़ो_unlock_irqrestore(&driver_name_lock, flags);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार filter_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[NAME_MAX_LEN];
	अचिन्हित दीर्घ flags;
	माप_प्रकार len;
	पूर्णांक i;

	/*
	 * We can't copy from userspace directly. Access to
	 * current_driver_name is रक्षित with a ग_लिखो_lock with irqs
	 * disabled. Since copy_from_user can fault and may sleep we
	 * need to copy to temporary buffer first
	 */
	len = min(count, (माप_प्रकार)(NAME_MAX_LEN - 1));
	अगर (copy_from_user(buf, userbuf, len))
		वापस -EFAULT;

	buf[len] = 0;

	ग_लिखो_lock_irqsave(&driver_name_lock, flags);

	/*
	 * Now handle the string we got from userspace very carefully.
	 * The rules are:
	 *         - only use the first token we got
	 *         - token delimiter is everything looking like a space
	 *           अक्षरacter (' ', '\n', '\t' ...)
	 *
	 */
	अगर (!है_अक्षर_अंक(buf[0])) अणु
		/*
		 * If the first अक्षरacter userspace gave us is not
		 * alphanumerical then assume the filter should be
		 * चयनed off.
		 */
		अगर (current_driver_name[0])
			pr_info("switching off dma-debug driver filter\n");
		current_driver_name[0] = 0;
		current_driver = शून्य;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Now parse out the first token and use it as the name क्रम the
	 * driver to filter क्रम.
	 */
	क्रम (i = 0; i < NAME_MAX_LEN - 1; ++i) अणु
		current_driver_name[i] = buf[i];
		अगर (है_खाली(buf[i]) || buf[i] == ' ' || buf[i] == 0)
			अवरोध;
	पूर्ण
	current_driver_name[i] = 0;
	current_driver = शून्य;

	pr_info("enable driver filter for driver [%s]\n",
		current_driver_name);

out_unlock:
	ग_लिखो_unlock_irqrestore(&driver_name_lock, flags);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations filter_fops = अणु
	.पढ़ो  = filter_पढ़ो,
	.ग_लिखो = filter_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक dump_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < HASH_SIZE; idx++) अणु
		काष्ठा hash_bucket *bucket = &dma_entry_hash[idx];
		काष्ठा dma_debug_entry *entry;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&bucket->lock, flags);
		list_क्रम_each_entry(entry, &bucket->list, list) अणु
			seq_म_लिखो(seq,
				   "%s %s %s idx %d P=%llx N=%lx D=%llx L=%llx %s %s\n",
				   dev_name(entry->dev),
				   dev_driver_string(entry->dev),
				   type2name[entry->type], idx,
				   phys_addr(entry), entry->pfn,
				   entry->dev_addr, entry->size,
				   dir2name[entry->direction],
				   maperr2str[entry->map_err_type]);
		पूर्ण
		spin_unlock_irqrestore(&bucket->lock, flags);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dump);

अटल व्योम dma_debug_fs_init(व्योम)
अणु
	काष्ठा dentry *dentry = debugfs_create_dir("dma-api", शून्य);

	debugfs_create_bool("disabled", 0444, dentry, &global_disable);
	debugfs_create_u32("error_count", 0444, dentry, &error_count);
	debugfs_create_u32("all_errors", 0644, dentry, &show_all_errors);
	debugfs_create_u32("num_errors", 0644, dentry, &show_num_errors);
	debugfs_create_u32("num_free_entries", 0444, dentry, &num_मुक्त_entries);
	debugfs_create_u32("min_free_entries", 0444, dentry, &min_मुक्त_entries);
	debugfs_create_u32("nr_total_entries", 0444, dentry, &nr_total_entries);
	debugfs_create_file("driver_filter", 0644, dentry, शून्य, &filter_fops);
	debugfs_create_file("dump", 0444, dentry, शून्य, &dump_fops);
पूर्ण

अटल पूर्णांक device_dma_allocations(काष्ठा device *dev, काष्ठा dma_debug_entry **out_entry)
अणु
	काष्ठा dma_debug_entry *entry;
	अचिन्हित दीर्घ flags;
	पूर्णांक count = 0, i;

	क्रम (i = 0; i < HASH_SIZE; ++i) अणु
		spin_lock_irqsave(&dma_entry_hash[i].lock, flags);
		list_क्रम_each_entry(entry, &dma_entry_hash[i].list, list) अणु
			अगर (entry->dev == dev) अणु
				count += 1;
				*out_entry = entry;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&dma_entry_hash[i].lock, flags);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक dma_debug_device_change(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा dma_debug_entry *entry;
	पूर्णांक count;

	अगर (dma_debug_disabled())
		वापस 0;

	चयन (action) अणु
	हाल BUS_NOTIFY_UNBOUND_DRIVER:
		count = device_dma_allocations(dev, &entry);
		अगर (count == 0)
			अवरोध;
		err_prपूर्णांकk(dev, entry, "device driver has pending "
				"DMA allocations while released from device "
				"[count=%d]\n"
				"One of leaked entries details: "
				"[device address=0x%016llx] [size=%llu bytes] "
				"[mapped with %s] [mapped as %s]\n",
			count, entry->dev_addr, entry->size,
			dir2name[entry->direction], type2name[entry->type]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dma_debug_add_bus(काष्ठा bus_type *bus)
अणु
	काष्ठा notअगरier_block *nb;

	अगर (dma_debug_disabled())
		वापस;

	nb = kzalloc(माप(काष्ठा notअगरier_block), GFP_KERNEL);
	अगर (nb == शून्य) अणु
		pr_err("dma_debug_add_bus: out of memory\n");
		वापस;
	पूर्ण

	nb->notअगरier_call = dma_debug_device_change;

	bus_रेजिस्टर_notअगरier(bus, nb);
पूर्ण

अटल पूर्णांक dma_debug_init(व्योम)
अणु
	पूर्णांक i, nr_pages;

	/* Do not use dma_debug_initialized here, since we really want to be
	 * called to set dma_debug_initialized
	 */
	अगर (global_disable)
		वापस 0;

	क्रम (i = 0; i < HASH_SIZE; ++i) अणु
		INIT_LIST_HEAD(&dma_entry_hash[i].list);
		spin_lock_init(&dma_entry_hash[i].lock);
	पूर्ण

	dma_debug_fs_init();

	nr_pages = DIV_ROUND_UP(nr_pपुनः_स्मृति_entries, DMA_DEBUG_DYNAMIC_ENTRIES);
	क्रम (i = 0; i < nr_pages; ++i)
		dma_debug_create_entries(GFP_KERNEL);
	अगर (num_मुक्त_entries >= nr_pपुनः_स्मृति_entries) अणु
		pr_info("preallocated %d debug entries\n", nr_total_entries);
	पूर्ण अन्यथा अगर (num_मुक्त_entries > 0) अणु
		pr_warn("%d debug entries requested but only %d allocated\n",
			nr_pपुनः_स्मृति_entries, nr_total_entries);
	पूर्ण अन्यथा अणु
		pr_err("debugging out of memory error - disabled\n");
		global_disable = true;

		वापस 0;
	पूर्ण
	min_मुक्त_entries = num_मुक्त_entries;

	dma_debug_initialized = true;

	pr_info("debugging enabled by kernel config\n");
	वापस 0;
पूर्ण
core_initcall(dma_debug_init);

अटल __init पूर्णांक dma_debug_cmdline(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	अगर (म_भेदन(str, "off", 3) == 0) अणु
		pr_info("debugging disabled on kernel command line\n");
		global_disable = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल __init पूर्णांक dma_debug_entries_cmdline(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;
	अगर (!get_option(&str, &nr_pपुनः_स्मृति_entries))
		nr_pपुनः_स्मृति_entries = PREALLOC_DMA_DEBUG_ENTRIES;
	वापस 0;
पूर्ण

__setup("dma_debug=", dma_debug_cmdline);
__setup("dma_debug_entries=", dma_debug_entries_cmdline);

अटल व्योम check_unmap(काष्ठा dma_debug_entry *ref)
अणु
	काष्ठा dma_debug_entry *entry;
	काष्ठा hash_bucket *bucket;
	अचिन्हित दीर्घ flags;

	bucket = get_hash_bucket(ref, &flags);
	entry = bucket_find_exact(bucket, ref);

	अगर (!entry) अणु
		/* must drop lock beक्रमe calling dma_mapping_error */
		put_hash_bucket(bucket, flags);

		अगर (dma_mapping_error(ref->dev, ref->dev_addr)) अणु
			err_prपूर्णांकk(ref->dev, शून्य,
				   "device driver tries to free an "
				   "invalid DMA memory address\n");
		पूर्ण अन्यथा अणु
			err_prपूर्णांकk(ref->dev, शून्य,
				   "device driver tries to free DMA "
				   "memory it has not allocated [device "
				   "address=0x%016llx] [size=%llu bytes]\n",
				   ref->dev_addr, ref->size);
		पूर्ण
		वापस;
	पूर्ण

	अगर (ref->size != entry->size) अणु
		err_prपूर्णांकk(ref->dev, entry, "device driver frees "
			   "DMA memory with different size "
			   "[device address=0x%016llx] [map size=%llu bytes] "
			   "[unmap size=%llu bytes]\n",
			   ref->dev_addr, entry->size, ref->size);
	पूर्ण

	अगर (ref->type != entry->type) अणु
		err_prपूर्णांकk(ref->dev, entry, "device driver frees "
			   "DMA memory with wrong function "
			   "[device address=0x%016llx] [size=%llu bytes] "
			   "[mapped as %s] [unmapped as %s]\n",
			   ref->dev_addr, ref->size,
			   type2name[entry->type], type2name[ref->type]);
	पूर्ण अन्यथा अगर ((entry->type == dma_debug_coherent) &&
		   (phys_addr(ref) != phys_addr(entry))) अणु
		err_prपूर्णांकk(ref->dev, entry, "device driver frees "
			   "DMA memory with different CPU address "
			   "[device address=0x%016llx] [size=%llu bytes] "
			   "[cpu alloc address=0x%016llx] "
			   "[cpu free address=0x%016llx]",
			   ref->dev_addr, ref->size,
			   phys_addr(entry),
			   phys_addr(ref));
	पूर्ण

	अगर (ref->sg_call_ents && ref->type == dma_debug_sg &&
	    ref->sg_call_ents != entry->sg_call_ents) अणु
		err_prपूर्णांकk(ref->dev, entry, "device driver frees "
			   "DMA sg list with different entry count "
			   "[map count=%d] [unmap count=%d]\n",
			   entry->sg_call_ents, ref->sg_call_ents);
	पूर्ण

	/*
	 * This may be no bug in reality - but most implementations of the
	 * DMA API करोn't handle this properly, so check क्रम it here
	 */
	अगर (ref->direction != entry->direction) अणु
		err_prपूर्णांकk(ref->dev, entry, "device driver frees "
			   "DMA memory with different direction "
			   "[device address=0x%016llx] [size=%llu bytes] "
			   "[mapped with %s] [unmapped with %s]\n",
			   ref->dev_addr, ref->size,
			   dir2name[entry->direction],
			   dir2name[ref->direction]);
	पूर्ण

	/*
	 * Drivers should use dma_mapping_error() to check the वापसed
	 * addresses of dma_map_single() and dma_map_page().
	 * If not, prपूर्णांक this warning message. See Documentation/core-api/dma-api.rst.
	 */
	अगर (entry->map_err_type == MAP_ERR_NOT_CHECKED) अणु
		err_prपूर्णांकk(ref->dev, entry,
			   "device driver failed to check map error"
			   "[device address=0x%016llx] [size=%llu bytes] "
			   "[mapped as %s]",
			   ref->dev_addr, ref->size,
			   type2name[entry->type]);
	पूर्ण

	hash_bucket_del(entry);
	dma_entry_मुक्त(entry);

	put_hash_bucket(bucket, flags);
पूर्ण

अटल व्योम check_क्रम_stack(काष्ठा device *dev,
			    काष्ठा page *page, माप_प्रकार offset)
अणु
	व्योम *addr;
	काष्ठा vm_काष्ठा *stack_vm_area = task_stack_vm_area(current);

	अगर (!stack_vm_area) अणु
		/* Stack is direct-mapped. */
		अगर (PageHighMem(page))
			वापस;
		addr = page_address(page) + offset;
		अगर (object_is_on_stack(addr))
			err_prपूर्णांकk(dev, शून्य, "device driver maps memory from stack [addr=%p]\n", addr);
	पूर्ण अन्यथा अणु
		/* Stack is vदो_स्मृतिed. */
		पूर्णांक i;

		क्रम (i = 0; i < stack_vm_area->nr_pages; i++) अणु
			अगर (page != stack_vm_area->pages[i])
				जारी;

			addr = (u8 *)current->stack + i * PAGE_SIZE + offset;
			err_prपूर्णांकk(dev, शून्य, "device driver maps memory from stack [probable addr=%p]\n", addr);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत bool overlap(व्योम *addr, अचिन्हित दीर्घ len, व्योम *start, व्योम *end)
अणु
	अचिन्हित दीर्घ a1 = (अचिन्हित दीर्घ)addr;
	अचिन्हित दीर्घ b1 = a1 + len;
	अचिन्हित दीर्घ a2 = (अचिन्हित दीर्घ)start;
	अचिन्हित दीर्घ b2 = (अचिन्हित दीर्घ)end;

	वापस !(b1 <= a2 || a1 >= b2);
पूर्ण

अटल व्योम check_क्रम_illegal_area(काष्ठा device *dev, व्योम *addr, अचिन्हित दीर्घ len)
अणु
	अगर (overlap(addr, len, _stext, _etext) ||
	    overlap(addr, len, __start_rodata, __end_rodata))
		err_prपूर्णांकk(dev, शून्य, "device driver maps memory from kernel text or rodata [addr=%p] [len=%lu]\n", addr, len);
पूर्ण

अटल व्योम check_sync(काष्ठा device *dev,
		       काष्ठा dma_debug_entry *ref,
		       bool to_cpu)
अणु
	काष्ठा dma_debug_entry *entry;
	काष्ठा hash_bucket *bucket;
	अचिन्हित दीर्घ flags;

	bucket = get_hash_bucket(ref, &flags);

	entry = bucket_find_contain(&bucket, ref, &flags);

	अगर (!entry) अणु
		err_prपूर्णांकk(dev, शून्य, "device driver tries "
				"to sync DMA memory it has not allocated "
				"[device address=0x%016llx] [size=%llu bytes]\n",
				(अचिन्हित दीर्घ दीर्घ)ref->dev_addr, ref->size);
		जाओ out;
	पूर्ण

	अगर (ref->size > entry->size) अणु
		err_prपूर्णांकk(dev, entry, "device driver syncs"
				" DMA memory outside allocated range "
				"[device address=0x%016llx] "
				"[allocation size=%llu bytes] "
				"[sync offset+size=%llu]\n",
				entry->dev_addr, entry->size,
				ref->size);
	पूर्ण

	अगर (entry->direction == DMA_BIसूचीECTIONAL)
		जाओ out;

	अगर (ref->direction != entry->direction) अणु
		err_prपूर्णांकk(dev, entry, "device driver syncs "
				"DMA memory with different direction "
				"[device address=0x%016llx] [size=%llu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(अचिन्हित दीर्घ दीर्घ)ref->dev_addr, entry->size,
				dir2name[entry->direction],
				dir2name[ref->direction]);
	पूर्ण

	अगर (to_cpu && !(entry->direction == DMA_FROM_DEVICE) &&
		      !(ref->direction == DMA_TO_DEVICE))
		err_prपूर्णांकk(dev, entry, "device driver syncs "
				"device read-only DMA memory for cpu "
				"[device address=0x%016llx] [size=%llu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(अचिन्हित दीर्घ दीर्घ)ref->dev_addr, entry->size,
				dir2name[entry->direction],
				dir2name[ref->direction]);

	अगर (!to_cpu && !(entry->direction == DMA_TO_DEVICE) &&
		       !(ref->direction == DMA_FROM_DEVICE))
		err_prपूर्णांकk(dev, entry, "device driver syncs "
				"device write-only DMA memory to device "
				"[device address=0x%016llx] [size=%llu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(अचिन्हित दीर्घ दीर्घ)ref->dev_addr, entry->size,
				dir2name[entry->direction],
				dir2name[ref->direction]);

	अगर (ref->sg_call_ents && ref->type == dma_debug_sg &&
	    ref->sg_call_ents != entry->sg_call_ents) अणु
		err_prपूर्णांकk(ref->dev, entry, "device driver syncs "
			   "DMA sg list with different entry count "
			   "[map count=%d] [sync count=%d]\n",
			   entry->sg_call_ents, ref->sg_call_ents);
	पूर्ण

out:
	put_hash_bucket(bucket, flags);
पूर्ण

अटल व्योम check_sg_segment(काष्ठा device *dev, काष्ठा scatterlist *sg)
अणु
#अगर_घोषित CONFIG_DMA_API_DEBUG_SG
	अचिन्हित पूर्णांक max_seg = dma_get_max_seg_size(dev);
	u64 start, end, boundary = dma_get_seg_boundary(dev);

	/*
	 * Either the driver क्रमgot to set dma_parms appropriately, or
	 * whoever generated the list क्रमgot to check them.
	 */
	अगर (sg->length > max_seg)
		err_prपूर्णांकk(dev, शून्य, "mapping sg segment longer than device claims to support [len=%u] [max=%u]\n",
			   sg->length, max_seg);
	/*
	 * In some हालs this could potentially be the DMA API
	 * implementation's fault, but it would usually imply that
	 * the scatterlist was built inappropriately to begin with.
	 */
	start = sg_dma_address(sg);
	end = start + sg_dma_len(sg) - 1;
	अगर ((start ^ end) & ~boundary)
		err_prपूर्णांकk(dev, शून्य, "mapping sg segment across boundary [start=0x%016llx] [end=0x%016llx] [boundary=0x%016llx]\n",
			   start, end, boundary);
#पूर्ण_अगर
पूर्ण

व्योम debug_dma_map_single(काष्ठा device *dev, स्थिर व्योम *addr,
			    अचिन्हित दीर्घ len)
अणु
	अगर (unlikely(dma_debug_disabled()))
		वापस;

	अगर (!virt_addr_valid(addr))
		err_prपूर्णांकk(dev, शून्य, "device driver maps memory from invalid area [addr=%p] [len=%lu]\n",
			   addr, len);

	अगर (is_vदो_स्मृति_addr(addr))
		err_prपूर्णांकk(dev, शून्य, "device driver maps memory from vmalloc area [addr=%p] [len=%lu]\n",
			   addr, len);
पूर्ण
EXPORT_SYMBOL(debug_dma_map_single);

व्योम debug_dma_map_page(काष्ठा device *dev, काष्ठा page *page, माप_प्रकार offset,
			माप_प्रकार size, पूर्णांक direction, dma_addr_t dma_addr)
अणु
	काष्ठा dma_debug_entry *entry;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	अगर (dma_mapping_error(dev, dma_addr))
		वापस;

	entry = dma_entry_alloc();
	अगर (!entry)
		वापस;

	entry->dev       = dev;
	entry->type      = dma_debug_single;
	entry->pfn	 = page_to_pfn(page);
	entry->offset	 = offset;
	entry->dev_addr  = dma_addr;
	entry->size      = size;
	entry->direction = direction;
	entry->map_err_type = MAP_ERR_NOT_CHECKED;

	check_क्रम_stack(dev, page, offset);

	अगर (!PageHighMem(page)) अणु
		व्योम *addr = page_address(page) + offset;

		check_क्रम_illegal_area(dev, addr, size);
	पूर्ण

	add_dma_entry(entry);
पूर्ण

व्योम debug_dma_mapping_error(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	काष्ठा dma_debug_entry ref;
	काष्ठा dma_debug_entry *entry;
	काष्ठा hash_bucket *bucket;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	ref.dev = dev;
	ref.dev_addr = dma_addr;
	bucket = get_hash_bucket(&ref, &flags);

	list_क्रम_each_entry(entry, &bucket->list, list) अणु
		अगर (!exact_match(&ref, entry))
			जारी;

		/*
		 * The same physical address can be mapped multiple
		 * बार. Without a hardware IOMMU this results in the
		 * same device addresses being put पूर्णांकo the dma-debug
		 * hash multiple बार too. This can result in false
		 * positives being reported. Thereक्रमe we implement a
		 * best-fit algorithm here which updates the first entry
		 * from the hash which fits the reference value and is
		 * not currently listed as being checked.
		 */
		अगर (entry->map_err_type == MAP_ERR_NOT_CHECKED) अणु
			entry->map_err_type = MAP_ERR_CHECKED;
			अवरोध;
		पूर्ण
	पूर्ण

	put_hash_bucket(bucket, flags);
पूर्ण
EXPORT_SYMBOL(debug_dma_mapping_error);

व्योम debug_dma_unmap_page(काष्ठा device *dev, dma_addr_t addr,
			  माप_प्रकार size, पूर्णांक direction)
अणु
	काष्ठा dma_debug_entry ref = अणु
		.type           = dma_debug_single,
		.dev            = dev,
		.dev_addr       = addr,
		.size           = size,
		.direction      = direction,
	पूर्ण;

	अगर (unlikely(dma_debug_disabled()))
		वापस;
	check_unmap(&ref);
पूर्ण

व्योम debug_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
		      पूर्णांक nents, पूर्णांक mapped_ents, पूर्णांक direction)
अणु
	काष्ठा dma_debug_entry *entry;
	काष्ठा scatterlist *s;
	पूर्णांक i;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	क्रम_each_sg(sg, s, mapped_ents, i) अणु
		entry = dma_entry_alloc();
		अगर (!entry)
			वापस;

		entry->type           = dma_debug_sg;
		entry->dev            = dev;
		entry->pfn	      = page_to_pfn(sg_page(s));
		entry->offset	      = s->offset;
		entry->size           = sg_dma_len(s);
		entry->dev_addr       = sg_dma_address(s);
		entry->direction      = direction;
		entry->sg_call_ents   = nents;
		entry->sg_mapped_ents = mapped_ents;

		check_क्रम_stack(dev, sg_page(s), s->offset);

		अगर (!PageHighMem(sg_page(s))) अणु
			check_क्रम_illegal_area(dev, sg_virt(s), sg_dma_len(s));
		पूर्ण

		check_sg_segment(dev, s);

		add_dma_entry(entry);
	पूर्ण
पूर्ण

अटल पूर्णांक get_nr_mapped_entries(काष्ठा device *dev,
				 काष्ठा dma_debug_entry *ref)
अणु
	काष्ठा dma_debug_entry *entry;
	काष्ठा hash_bucket *bucket;
	अचिन्हित दीर्घ flags;
	पूर्णांक mapped_ents;

	bucket       = get_hash_bucket(ref, &flags);
	entry        = bucket_find_exact(bucket, ref);
	mapped_ents  = 0;

	अगर (entry)
		mapped_ents = entry->sg_mapped_ents;
	put_hash_bucket(bucket, flags);

	वापस mapped_ents;
पूर्ण

व्योम debug_dma_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			पूर्णांक nelems, पूर्णांक dir)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक mapped_ents = 0, i;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	क्रम_each_sg(sglist, s, nelems, i) अणु

		काष्ठा dma_debug_entry ref = अणु
			.type           = dma_debug_sg,
			.dev            = dev,
			.pfn		= page_to_pfn(sg_page(s)),
			.offset		= s->offset,
			.dev_addr       = sg_dma_address(s),
			.size           = sg_dma_len(s),
			.direction      = dir,
			.sg_call_ents   = nelems,
		पूर्ण;

		अगर (mapped_ents && i >= mapped_ents)
			अवरोध;

		अगर (!i)
			mapped_ents = get_nr_mapped_entries(dev, &ref);

		check_unmap(&ref);
	पूर्ण
पूर्ण

व्योम debug_dma_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
			      dma_addr_t dma_addr, व्योम *virt)
अणु
	काष्ठा dma_debug_entry *entry;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	अगर (unlikely(virt == शून्य))
		वापस;

	/* handle vदो_स्मृति and linear addresses */
	अगर (!is_vदो_स्मृति_addr(virt) && !virt_addr_valid(virt))
		वापस;

	entry = dma_entry_alloc();
	अगर (!entry)
		वापस;

	entry->type      = dma_debug_coherent;
	entry->dev       = dev;
	entry->offset	 = offset_in_page(virt);
	entry->size      = size;
	entry->dev_addr  = dma_addr;
	entry->direction = DMA_BIसूचीECTIONAL;

	अगर (is_vदो_स्मृति_addr(virt))
		entry->pfn = vदो_स्मृति_to_pfn(virt);
	अन्यथा
		entry->pfn = page_to_pfn(virt_to_page(virt));

	add_dma_entry(entry);
पूर्ण

व्योम debug_dma_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
			 व्योम *virt, dma_addr_t addr)
अणु
	काष्ठा dma_debug_entry ref = अणु
		.type           = dma_debug_coherent,
		.dev            = dev,
		.offset		= offset_in_page(virt),
		.dev_addr       = addr,
		.size           = size,
		.direction      = DMA_BIसूचीECTIONAL,
	पूर्ण;

	/* handle vदो_स्मृति and linear addresses */
	अगर (!is_vदो_स्मृति_addr(virt) && !virt_addr_valid(virt))
		वापस;

	अगर (is_vदो_स्मृति_addr(virt))
		ref.pfn = vदो_स्मृति_to_pfn(virt);
	अन्यथा
		ref.pfn = page_to_pfn(virt_to_page(virt));

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	check_unmap(&ref);
पूर्ण

व्योम debug_dma_map_resource(काष्ठा device *dev, phys_addr_t addr, माप_प्रकार size,
			    पूर्णांक direction, dma_addr_t dma_addr)
अणु
	काष्ठा dma_debug_entry *entry;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	entry = dma_entry_alloc();
	अगर (!entry)
		वापस;

	entry->type		= dma_debug_resource;
	entry->dev		= dev;
	entry->pfn		= PHYS_PFN(addr);
	entry->offset		= offset_in_page(addr);
	entry->size		= size;
	entry->dev_addr		= dma_addr;
	entry->direction	= direction;
	entry->map_err_type	= MAP_ERR_NOT_CHECKED;

	add_dma_entry(entry);
पूर्ण

व्योम debug_dma_unmap_resource(काष्ठा device *dev, dma_addr_t dma_addr,
			      माप_प्रकार size, पूर्णांक direction)
अणु
	काष्ठा dma_debug_entry ref = अणु
		.type           = dma_debug_resource,
		.dev            = dev,
		.dev_addr       = dma_addr,
		.size           = size,
		.direction      = direction,
	पूर्ण;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	check_unmap(&ref);
पूर्ण

व्योम debug_dma_sync_single_क्रम_cpu(काष्ठा device *dev, dma_addr_t dma_handle,
				   माप_प्रकार size, पूर्णांक direction)
अणु
	काष्ठा dma_debug_entry ref;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	ref.type         = dma_debug_single;
	ref.dev          = dev;
	ref.dev_addr     = dma_handle;
	ref.size         = size;
	ref.direction    = direction;
	ref.sg_call_ents = 0;

	check_sync(dev, &ref, true);
पूर्ण

व्योम debug_dma_sync_single_क्रम_device(काष्ठा device *dev,
				      dma_addr_t dma_handle, माप_प्रकार size,
				      पूर्णांक direction)
अणु
	काष्ठा dma_debug_entry ref;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	ref.type         = dma_debug_single;
	ref.dev          = dev;
	ref.dev_addr     = dma_handle;
	ref.size         = size;
	ref.direction    = direction;
	ref.sg_call_ents = 0;

	check_sync(dev, &ref, false);
पूर्ण

व्योम debug_dma_sync_sg_क्रम_cpu(काष्ठा device *dev, काष्ठा scatterlist *sg,
			       पूर्णांक nelems, पूर्णांक direction)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक mapped_ents = 0, i;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	क्रम_each_sg(sg, s, nelems, i) अणु

		काष्ठा dma_debug_entry ref = अणु
			.type           = dma_debug_sg,
			.dev            = dev,
			.pfn		= page_to_pfn(sg_page(s)),
			.offset		= s->offset,
			.dev_addr       = sg_dma_address(s),
			.size           = sg_dma_len(s),
			.direction      = direction,
			.sg_call_ents   = nelems,
		पूर्ण;

		अगर (!i)
			mapped_ents = get_nr_mapped_entries(dev, &ref);

		अगर (i >= mapped_ents)
			अवरोध;

		check_sync(dev, &ref, true);
	पूर्ण
पूर्ण

व्योम debug_dma_sync_sg_क्रम_device(काष्ठा device *dev, काष्ठा scatterlist *sg,
				  पूर्णांक nelems, पूर्णांक direction)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक mapped_ents = 0, i;

	अगर (unlikely(dma_debug_disabled()))
		वापस;

	क्रम_each_sg(sg, s, nelems, i) अणु

		काष्ठा dma_debug_entry ref = अणु
			.type           = dma_debug_sg,
			.dev            = dev,
			.pfn		= page_to_pfn(sg_page(s)),
			.offset		= s->offset,
			.dev_addr       = sg_dma_address(s),
			.size           = sg_dma_len(s),
			.direction      = direction,
			.sg_call_ents   = nelems,
		पूर्ण;
		अगर (!i)
			mapped_ents = get_nr_mapped_entries(dev, &ref);

		अगर (i >= mapped_ents)
			अवरोध;

		check_sync(dev, &ref, false);
	पूर्ण
पूर्ण

अटल पूर्णांक __init dma_debug_driver_setup(अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NAME_MAX_LEN - 1; ++i, ++str) अणु
		current_driver_name[i] = *str;
		अगर (*str == 0)
			अवरोध;
	पूर्ण

	अगर (current_driver_name[0])
		pr_info("enable driver filter for driver [%s]\n",
			current_driver_name);


	वापस 1;
पूर्ण
__setup("dma_debug_driver=", dma_debug_driver_setup);

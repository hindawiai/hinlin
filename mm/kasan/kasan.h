<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MM_KASAN_KASAN_H
#घोषणा __MM_KASAN_KASAN_H

#समावेश <linux/kasan.h>
#समावेश <linux/kfence.h>
#समावेश <linux/stackdepot.h>

#अगर_घोषित CONFIG_KASAN_HW_TAGS

#समावेश <linux/अटल_key.h>

DECLARE_STATIC_KEY_FALSE(kasan_flag_stacktrace);
बाह्य bool kasan_flag_async __ro_after_init;

अटल अंतरभूत bool kasan_stack_collection_enabled(व्योम)
अणु
	वापस अटल_branch_unlikely(&kasan_flag_stacktrace);
पूर्ण

अटल अंतरभूत bool kasan_async_mode_enabled(व्योम)
अणु
	वापस kasan_flag_async;
पूर्ण
#अन्यथा

अटल अंतरभूत bool kasan_stack_collection_enabled(व्योम)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool kasan_async_mode_enabled(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

बाह्य bool kasan_flag_panic __ro_after_init;
बाह्य bool kasan_flag_async __ro_after_init;

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
#घोषणा KASAN_GRANULE_SIZE	(1UL << KASAN_SHADOW_SCALE_SHIFT)
#अन्यथा
#समावेश <यंत्र/mte-kasan.h>
#घोषणा KASAN_GRANULE_SIZE	MTE_GRANULE_SIZE
#पूर्ण_अगर

#घोषणा KASAN_GRANULE_MASK	(KASAN_GRANULE_SIZE - 1)

#घोषणा KASAN_MEMORY_PER_SHADOW_PAGE	(KASAN_GRANULE_SIZE << PAGE_SHIFT)

#घोषणा KASAN_TAG_KERNEL	0xFF /* native kernel poपूर्णांकers tag */
#घोषणा KASAN_TAG_INVALID	0xFE /* inaccessible memory tag */
#घोषणा KASAN_TAG_MAX		0xFD /* maximum value क्रम अक्रमom tags */

#अगर_घोषित CONFIG_KASAN_HW_TAGS
#घोषणा KASAN_TAG_MIN		0xF0 /* minimum value क्रम अक्रमom tags */
#अन्यथा
#घोषणा KASAN_TAG_MIN		0x00 /* minimum value क्रम अक्रमom tags */
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN_GENERIC
#घोषणा KASAN_FREE_PAGE         0xFF  /* page was मुक्तd */
#घोषणा KASAN_PAGE_REDZONE      0xFE  /* redzone क्रम kदो_स्मृति_large allocations */
#घोषणा KASAN_KMALLOC_REDZONE   0xFC  /* redzone inside slub object */
#घोषणा KASAN_KMALLOC_FREE      0xFB  /* object was मुक्तd (kmem_cache_मुक्त/kमुक्त) */
#घोषणा KASAN_KMALLOC_FREETRACK 0xFA  /* object was मुक्तd and has मुक्त track set */
#अन्यथा
#घोषणा KASAN_FREE_PAGE         KASAN_TAG_INVALID
#घोषणा KASAN_PAGE_REDZONE      KASAN_TAG_INVALID
#घोषणा KASAN_KMALLOC_REDZONE   KASAN_TAG_INVALID
#घोषणा KASAN_KMALLOC_FREE      KASAN_TAG_INVALID
#घोषणा KASAN_KMALLOC_FREETRACK KASAN_TAG_INVALID
#पूर्ण_अगर

#घोषणा KASAN_GLOBAL_REDZONE    0xF9  /* redzone क्रम global variable */
#घोषणा KASAN_VMALLOC_INVALID   0xF8  /* unallocated space in vmapped page */

/*
 * Stack redzone shaकरोw values
 * (Those are compiler's ABI, don't change them)
 */
#घोषणा KASAN_STACK_LEFT        0xF1
#घोषणा KASAN_STACK_MID         0xF2
#घोषणा KASAN_STACK_RIGHT       0xF3
#घोषणा KASAN_STACK_PARTIAL     0xF4

/*
 * alloca redzone shaकरोw values
 */
#घोषणा KASAN_ALLOCA_LEFT	0xCA
#घोषणा KASAN_ALLOCA_RIGHT	0xCB

#घोषणा KASAN_ALLOCA_REDZONE_SIZE	32

/*
 * Stack frame marker (compiler ABI).
 */
#घोषणा KASAN_CURRENT_STACK_FRAME_MAGIC 0x41B58AB3

/* Don't अवरोध अक्रमconfig/all*config builds */
#अगर_अघोषित KASAN_ABI_VERSION
#घोषणा KASAN_ABI_VERSION 1
#पूर्ण_अगर

/* Metadata layout customization. */
#घोषणा META_BYTES_PER_BLOCK 1
#घोषणा META_BLOCKS_PER_ROW 16
#घोषणा META_BYTES_PER_ROW (META_BLOCKS_PER_ROW * META_BYTES_PER_BLOCK)
#घोषणा META_MEM_BYTES_PER_ROW (META_BYTES_PER_ROW * KASAN_GRANULE_SIZE)
#घोषणा META_ROWS_AROUND_ADDR 2

काष्ठा kasan_access_info अणु
	स्थिर व्योम *access_addr;
	स्थिर व्योम *first_bad_addr;
	माप_प्रकार access_size;
	bool is_ग_लिखो;
	अचिन्हित दीर्घ ip;
पूर्ण;

/* The layout of काष्ठा dictated by compiler */
काष्ठा kasan_source_location अणु
	स्थिर अक्षर *filename;
	पूर्णांक line_no;
	पूर्णांक column_no;
पूर्ण;

/* The layout of काष्ठा dictated by compiler */
काष्ठा kasan_global अणु
	स्थिर व्योम *beg;		/* Address of the beginning of the global variable. */
	माप_प्रकार size;			/* Size of the global variable. */
	माप_प्रकार size_with_redzone;	/* Size of the variable + size of the red zone. 32 bytes aligned */
	स्थिर व्योम *name;
	स्थिर व्योम *module_name;	/* Name of the module where the global variable is declared. */
	अचिन्हित दीर्घ has_dynamic_init;	/* This needed क्रम C++ */
#अगर KASAN_ABI_VERSION >= 4
	काष्ठा kasan_source_location *location;
#पूर्ण_अगर
#अगर KASAN_ABI_VERSION >= 5
	अक्षर *odr_indicator;
#पूर्ण_अगर
पूर्ण;

/**
 * Structures to keep alloc and मुक्त tracks *
 */

#घोषणा KASAN_STACK_DEPTH 64

काष्ठा kasan_track अणु
	u32 pid;
	depot_stack_handle_t stack;
पूर्ण;

#अगर_घोषित CONFIG_KASAN_SW_TAGS_IDENTIFY
#घोषणा KASAN_NR_FREE_STACKS 5
#अन्यथा
#घोषणा KASAN_NR_FREE_STACKS 1
#पूर्ण_अगर

काष्ठा kasan_alloc_meta अणु
	काष्ठा kasan_track alloc_track;
#अगर_घोषित CONFIG_KASAN_GENERIC
	/*
	 * The auxiliary stack is stored पूर्णांकo काष्ठा kasan_alloc_meta.
	 * The मुक्त stack is stored पूर्णांकo काष्ठा kasan_मुक्त_meta.
	 */
	depot_stack_handle_t aux_stack[2];
#अन्यथा
	काष्ठा kasan_track मुक्त_track[KASAN_NR_FREE_STACKS];
#पूर्ण_अगर
#अगर_घोषित CONFIG_KASAN_SW_TAGS_IDENTIFY
	u8 मुक्त_poपूर्णांकer_tag[KASAN_NR_FREE_STACKS];
	u8 मुक्त_track_idx;
#पूर्ण_अगर
पूर्ण;

काष्ठा qlist_node अणु
	काष्ठा qlist_node *next;
पूर्ण;

/*
 * Generic mode either stores मुक्त meta in the object itself or in the redzone
 * after the object. In the क्रमmer हाल मुक्त meta offset is 0, in the latter
 * हाल it has some sane value smaller than पूर्णांक_उच्च. Use पूर्णांक_उच्च as मुक्त meta
 * offset when मुक्त meta isn't present.
 */
#घोषणा KASAN_NO_FREE_META पूर्णांक_उच्च

काष्ठा kasan_मुक्त_meta अणु
#अगर_घोषित CONFIG_KASAN_GENERIC
	/* This field is used जबतक the object is in the quarantine.
	 * Otherwise it might be used क्रम the allocator मुक्तlist.
	 */
	काष्ठा qlist_node quarantine_link;
	काष्ठा kasan_track मुक्त_track;
#पूर्ण_अगर
पूर्ण;

काष्ठा kasan_alloc_meta *kasan_get_alloc_meta(काष्ठा kmem_cache *cache,
						स्थिर व्योम *object);
#अगर_घोषित CONFIG_KASAN_GENERIC
काष्ठा kasan_मुक्त_meta *kasan_get_मुक्त_meta(काष्ठा kmem_cache *cache,
						स्थिर व्योम *object);
#पूर्ण_अगर

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)

अटल अंतरभूत स्थिर व्योम *kasan_shaकरोw_to_mem(स्थिर व्योम *shaकरोw_addr)
अणु
	वापस (व्योम *)(((अचिन्हित दीर्घ)shaकरोw_addr - KASAN_SHADOW_OFFSET)
		<< KASAN_SHADOW_SCALE_SHIFT);
पूर्ण

अटल अंतरभूत bool addr_has_metadata(स्थिर व्योम *addr)
अणु
	वापस (addr >= kasan_shaकरोw_to_mem((व्योम *)KASAN_SHADOW_START));
पूर्ण

/**
 * kasan_check_range - Check memory region, and report अगर invalid access.
 * @addr: the accessed address
 * @size: the accessed size
 * @ग_लिखो: true अगर access is a ग_लिखो access
 * @ret_ip: वापस address
 * @वापस: true अगर access was valid, false अगर invalid
 */
bool kasan_check_range(अचिन्हित दीर्घ addr, माप_प्रकार size, bool ग_लिखो,
				अचिन्हित दीर्घ ret_ip);

#अन्यथा /* CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS */

अटल अंतरभूत bool addr_has_metadata(स्थिर व्योम *addr)
अणु
	वापस (is_vदो_स्मृति_addr(addr) || virt_addr_valid(addr));
पूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS */

#अगर defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)
व्योम kasan_prपूर्णांक_tags(u8 addr_tag, स्थिर व्योम *addr);
#अन्यथा
अटल अंतरभूत व्योम kasan_prपूर्णांक_tags(u8 addr_tag, स्थिर व्योम *addr) अणु पूर्ण
#पूर्ण_अगर

व्योम *kasan_find_first_bad_addr(व्योम *addr, माप_प्रकार size);
स्थिर अक्षर *kasan_get_bug_type(काष्ठा kasan_access_info *info);
व्योम kasan_metadata_fetch_row(अक्षर *buffer, व्योम *row);

#अगर defined(CONFIG_KASAN_GENERIC) && defined(CONFIG_KASAN_STACK)
व्योम kasan_prपूर्णांक_address_stack_frame(स्थिर व्योम *addr);
#अन्यथा
अटल अंतरभूत व्योम kasan_prपूर्णांक_address_stack_frame(स्थिर व्योम *addr) अणु पूर्ण
#पूर्ण_अगर

bool kasan_report(अचिन्हित दीर्घ addr, माप_प्रकार size,
		bool is_ग_लिखो, अचिन्हित दीर्घ ip);
व्योम kasan_report_invalid_मुक्त(व्योम *object, अचिन्हित दीर्घ ip);

काष्ठा page *kasan_addr_to_page(स्थिर व्योम *addr);

depot_stack_handle_t kasan_save_stack(gfp_t flags);
व्योम kasan_set_track(काष्ठा kasan_track *track, gfp_t flags);
व्योम kasan_set_मुक्त_info(काष्ठा kmem_cache *cache, व्योम *object, u8 tag);
काष्ठा kasan_track *kasan_get_मुक्त_track(काष्ठा kmem_cache *cache,
				व्योम *object, u8 tag);

#अगर defined(CONFIG_KASAN_GENERIC) && \
	(defined(CONFIG_SLAB) || defined(CONFIG_SLUB))
bool kasan_quarantine_put(काष्ठा kmem_cache *cache, व्योम *object);
व्योम kasan_quarantine_reduce(व्योम);
व्योम kasan_quarantine_हटाओ_cache(काष्ठा kmem_cache *cache);
#अन्यथा
अटल अंतरभूत bool kasan_quarantine_put(काष्ठा kmem_cache *cache, व्योम *object) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम kasan_quarantine_reduce(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_quarantine_हटाओ_cache(काष्ठा kmem_cache *cache) अणु पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_kasan_set_tag
अटल अंतरभूत स्थिर व्योम *arch_kasan_set_tag(स्थिर व्योम *addr, u8 tag)
अणु
	वापस addr;
पूर्ण
#पूर्ण_अगर
#अगर_अघोषित arch_kasan_get_tag
#घोषणा arch_kasan_get_tag(addr)	0
#पूर्ण_अगर

#घोषणा set_tag(addr, tag)	((व्योम *)arch_kasan_set_tag((addr), (tag)))
#घोषणा get_tag(addr)		arch_kasan_get_tag(addr)

#अगर_घोषित CONFIG_KASAN_HW_TAGS

#अगर_अघोषित arch_enable_tagging_sync
#घोषणा arch_enable_tagging_sync()
#पूर्ण_अगर
#अगर_अघोषित arch_enable_tagging_async
#घोषणा arch_enable_tagging_async()
#पूर्ण_अगर
#अगर_अघोषित arch_init_tags
#घोषणा arch_init_tags(max_tag)
#पूर्ण_अगर
#अगर_अघोषित arch_set_tagging_report_once
#घोषणा arch_set_tagging_report_once(state)
#पूर्ण_अगर
#अगर_अघोषित arch_क्रमce_async_tag_fault
#घोषणा arch_क्रमce_async_tag_fault()
#पूर्ण_अगर
#अगर_अघोषित arch_get_अक्रमom_tag
#घोषणा arch_get_अक्रमom_tag()	(0xFF)
#पूर्ण_अगर
#अगर_अघोषित arch_get_mem_tag
#घोषणा arch_get_mem_tag(addr)	(0xFF)
#पूर्ण_अगर
#अगर_अघोषित arch_set_mem_tag_range
#घोषणा arch_set_mem_tag_range(addr, size, tag, init) ((व्योम *)(addr))
#पूर्ण_अगर

#घोषणा hw_enable_tagging_sync()		arch_enable_tagging_sync()
#घोषणा hw_enable_tagging_async()		arch_enable_tagging_async()
#घोषणा hw_init_tags(max_tag)			arch_init_tags(max_tag)
#घोषणा hw_set_tagging_report_once(state)	arch_set_tagging_report_once(state)
#घोषणा hw_क्रमce_async_tag_fault()		arch_क्रमce_async_tag_fault()
#घोषणा hw_get_अक्रमom_tag()			arch_get_अक्रमom_tag()
#घोषणा hw_get_mem_tag(addr)			arch_get_mem_tag(addr)
#घोषणा hw_set_mem_tag_range(addr, size, tag, init) \
			arch_set_mem_tag_range((addr), (size), (tag), (init))

#अन्यथा /* CONFIG_KASAN_HW_TAGS */

#घोषणा hw_enable_tagging_sync()
#घोषणा hw_enable_tagging_async()
#घोषणा hw_set_tagging_report_once(state)

#पूर्ण_अगर /* CONFIG_KASAN_HW_TAGS */

#अगर defined(CONFIG_KASAN_HW_TAGS) && IS_ENABLED(CONFIG_KASAN_KUNIT_TEST)

व्योम kasan_set_tagging_report_once(bool state);
व्योम kasan_enable_tagging_sync(व्योम);
व्योम kasan_क्रमce_async_fault(व्योम);

#अन्यथा /* CONFIG_KASAN_HW_TAGS || CONFIG_KASAN_KUNIT_TEST */

अटल अंतरभूत व्योम kasan_set_tagging_report_once(bool state) अणु पूर्ण
अटल अंतरभूत व्योम kasan_enable_tagging_sync(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_क्रमce_async_fault(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_HW_TAGS || CONFIG_KASAN_KUNIT_TEST */

#अगर_घोषित CONFIG_KASAN_SW_TAGS
u8 kasan_अक्रमom_tag(व्योम);
#या_अगर defined(CONFIG_KASAN_HW_TAGS)
अटल अंतरभूत u8 kasan_अक्रमom_tag(व्योम) अणु वापस hw_get_अक्रमom_tag(); पूर्ण
#अन्यथा
अटल अंतरभूत u8 kasan_अक्रमom_tag(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN_HW_TAGS

अटल अंतरभूत व्योम kasan_poison(स्थिर व्योम *addr, माप_प्रकार size, u8 value, bool init)
अणु
	addr = kasan_reset_tag(addr);

	/* Skip KFENCE memory अगर called explicitly outside of sl*b. */
	अगर (is_kfence_address(addr))
		वापस;

	अगर (WARN_ON((अचिन्हित दीर्घ)addr & KASAN_GRANULE_MASK))
		वापस;
	अगर (WARN_ON(size & KASAN_GRANULE_MASK))
		वापस;

	hw_set_mem_tag_range((व्योम *)addr, size, value, init);
पूर्ण

अटल अंतरभूत व्योम kasan_unpoison(स्थिर व्योम *addr, माप_प्रकार size, bool init)
अणु
	u8 tag = get_tag(addr);

	addr = kasan_reset_tag(addr);

	/* Skip KFENCE memory अगर called explicitly outside of sl*b. */
	अगर (is_kfence_address(addr))
		वापस;

	अगर (WARN_ON((अचिन्हित दीर्घ)addr & KASAN_GRANULE_MASK))
		वापस;
	size = round_up(size, KASAN_GRANULE_SIZE);

	hw_set_mem_tag_range((व्योम *)addr, size, tag, init);
पूर्ण

अटल अंतरभूत bool kasan_byte_accessible(स्थिर व्योम *addr)
अणु
	u8 ptr_tag = get_tag(addr);
	u8 mem_tag = hw_get_mem_tag((व्योम *)addr);

	वापस ptr_tag == KASAN_TAG_KERNEL || ptr_tag == mem_tag;
पूर्ण

#अन्यथा /* CONFIG_KASAN_HW_TAGS */

/**
 * kasan_poison - mark the memory range as inaccessible
 * @addr - range start address, must be aligned to KASAN_GRANULE_SIZE
 * @size - range size, must be aligned to KASAN_GRANULE_SIZE
 * @value - value that's written to metadata क्रम the range
 * @init - whether to initialize the memory range (only क्रम hardware tag-based)
 *
 * The size माला_लो aligned to KASAN_GRANULE_SIZE beक्रमe marking the range.
 */
व्योम kasan_poison(स्थिर व्योम *addr, माप_प्रकार size, u8 value, bool init);

/**
 * kasan_unpoison - mark the memory range as accessible
 * @addr - range start address, must be aligned to KASAN_GRANULE_SIZE
 * @size - range size, can be unaligned
 * @init - whether to initialize the memory range (only क्रम hardware tag-based)
 *
 * For the tag-based modes, the @size माला_लो aligned to KASAN_GRANULE_SIZE beक्रमe
 * marking the range.
 * For the generic mode, the last granule of the memory range माला_लो partially
 * unpoisoned based on the @size.
 */
व्योम kasan_unpoison(स्थिर व्योम *addr, माप_प्रकार size, bool init);

bool kasan_byte_accessible(स्थिर व्योम *addr);

#पूर्ण_अगर /* CONFIG_KASAN_HW_TAGS */

#अगर_घोषित CONFIG_KASAN_GENERIC

/**
 * kasan_poison_last_granule - mark the last granule of the memory range as
 * inaccessible
 * @addr - range start address, must be aligned to KASAN_GRANULE_SIZE
 * @size - range size
 *
 * This function is only available क्रम the generic mode, as it's the only mode
 * that has partially poisoned memory granules.
 */
व्योम kasan_poison_last_granule(स्थिर व्योम *address, माप_प्रकार size);

#अन्यथा /* CONFIG_KASAN_GENERIC */

अटल अंतरभूत व्योम kasan_poison_last_granule(स्थिर व्योम *address, माप_प्रकार size) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_GENERIC */

/*
 * Exported functions क्रम पूर्णांकerfaces called from assembly or from generated
 * code. Declarations here to aव्योम warning about missing declarations.
 */
यंत्रlinkage व्योम kasan_unpoison_task_stack_below(स्थिर व्योम *watermark);
व्योम __asan_रेजिस्टर_globals(काष्ठा kasan_global *globals, माप_प्रकार size);
व्योम __asan_unरेजिस्टर_globals(काष्ठा kasan_global *globals, माप_प्रकार size);
व्योम __asan_handle_no_वापस(व्योम);
व्योम __asan_alloca_poison(अचिन्हित दीर्घ addr, माप_प्रकार size);
व्योम __asan_allocas_unpoison(स्थिर व्योम *stack_top, स्थिर व्योम *stack_bottom);

व्योम __asan_load1(अचिन्हित दीर्घ addr);
व्योम __asan_store1(अचिन्हित दीर्घ addr);
व्योम __asan_load2(अचिन्हित दीर्घ addr);
व्योम __asan_store2(अचिन्हित दीर्घ addr);
व्योम __asan_load4(अचिन्हित दीर्घ addr);
व्योम __asan_store4(अचिन्हित दीर्घ addr);
व्योम __asan_load8(अचिन्हित दीर्घ addr);
व्योम __asan_store8(अचिन्हित दीर्घ addr);
व्योम __asan_load16(अचिन्हित दीर्घ addr);
व्योम __asan_store16(अचिन्हित दीर्घ addr);
व्योम __asan_loadN(अचिन्हित दीर्घ addr, माप_प्रकार size);
व्योम __asan_storeN(अचिन्हित दीर्घ addr, माप_प्रकार size);

व्योम __asan_load1_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_store1_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_load2_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_store2_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_load4_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_store4_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_load8_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_store8_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_load16_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_store16_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_loadN_noपात(अचिन्हित दीर्घ addr, माप_प्रकार size);
व्योम __asan_storeN_noपात(अचिन्हित दीर्घ addr, माप_प्रकार size);

व्योम __asan_report_load1_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_store1_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_load2_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_store2_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_load4_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_store4_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_load8_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_store8_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_load16_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_store16_noपात(अचिन्हित दीर्घ addr);
व्योम __asan_report_load_n_noपात(अचिन्हित दीर्घ addr, माप_प्रकार size);
व्योम __asan_report_store_n_noपात(अचिन्हित दीर्घ addr, माप_प्रकार size);

व्योम __asan_set_shaकरोw_00(स्थिर व्योम *addr, माप_प्रकार size);
व्योम __asan_set_shaकरोw_f1(स्थिर व्योम *addr, माप_प्रकार size);
व्योम __asan_set_shaकरोw_f2(स्थिर व्योम *addr, माप_प्रकार size);
व्योम __asan_set_shaकरोw_f3(स्थिर व्योम *addr, माप_प्रकार size);
व्योम __asan_set_shaकरोw_f5(स्थिर व्योम *addr, माप_प्रकार size);
व्योम __asan_set_shaकरोw_f8(स्थिर व्योम *addr, माप_प्रकार size);

व्योम __hwasan_load1_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_store1_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_load2_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_store2_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_load4_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_store4_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_load8_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_store8_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_load16_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_store16_noपात(अचिन्हित दीर्घ addr);
व्योम __hwasan_loadN_noपात(अचिन्हित दीर्घ addr, माप_प्रकार size);
व्योम __hwasan_storeN_noपात(अचिन्हित दीर्घ addr, माप_प्रकार size);

व्योम __hwasan_tag_memory(अचिन्हित दीर्घ addr, u8 tag, अचिन्हित दीर्घ size);

#पूर्ण_अगर

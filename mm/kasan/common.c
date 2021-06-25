<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains common KASAN code.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 *
 * Some code borrowed from https://github.com/xairy/kasan-prototype by
 *        Andrey Konovalov <andreyknvl@gmail.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/linkage.h>
#समावेश <linux/memblock.h>
#समावेश <linux/memory.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/slab.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>

#समावेश "kasan.h"
#समावेश "../slab.h"

depot_stack_handle_t kasan_save_stack(gfp_t flags)
अणु
	अचिन्हित दीर्घ entries[KASAN_STACK_DEPTH];
	अचिन्हित पूर्णांक nr_entries;

	nr_entries = stack_trace_save(entries, ARRAY_SIZE(entries), 0);
	nr_entries = filter_irq_stacks(entries, nr_entries);
	वापस stack_depot_save(entries, nr_entries, flags);
पूर्ण

व्योम kasan_set_track(काष्ठा kasan_track *track, gfp_t flags)
अणु
	track->pid = current->pid;
	track->stack = kasan_save_stack(flags);
पूर्ण

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
व्योम kasan_enable_current(व्योम)
अणु
	current->kasan_depth++;
पूर्ण

व्योम kasan_disable_current(व्योम)
अणु
	current->kasan_depth--;
पूर्ण
#पूर्ण_अगर /* CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS */

व्योम __kasan_unpoison_range(स्थिर व्योम *address, माप_प्रकार size)
अणु
	kasan_unpoison(address, size, false);
पूर्ण

#अगर_घोषित CONFIG_KASAN_STACK
/* Unpoison the entire stack क्रम a task. */
व्योम kasan_unpoison_task_stack(काष्ठा task_काष्ठा *task)
अणु
	व्योम *base = task_stack_page(task);

	kasan_unpoison(base, THREAD_SIZE, false);
पूर्ण

/* Unpoison the stack क्रम the current task beyond a watermark sp value. */
यंत्रlinkage व्योम kasan_unpoison_task_stack_below(स्थिर व्योम *watermark)
अणु
	/*
	 * Calculate the task stack base address.  Aव्योम using 'current'
	 * because this function is called by early resume code which hasn't
	 * yet set up the percpu रेजिस्टर (%gs).
	 */
	व्योम *base = (व्योम *)((अचिन्हित दीर्घ)watermark & ~(THREAD_SIZE - 1));

	kasan_unpoison(base, watermark - base, false);
पूर्ण
#पूर्ण_अगर /* CONFIG_KASAN_STACK */

/*
 * Only allow cache merging when stack collection is disabled and no metadata
 * is present.
 */
slab_flags_t __kasan_never_merge(व्योम)
अणु
	अगर (kasan_stack_collection_enabled())
		वापस SLAB_KASAN;
	वापस 0;
पूर्ण

व्योम __kasan_alloc_pages(काष्ठा page *page, अचिन्हित पूर्णांक order, bool init)
अणु
	u8 tag;
	अचिन्हित दीर्घ i;

	अगर (unlikely(PageHighMem(page)))
		वापस;

	tag = kasan_अक्रमom_tag();
	क्रम (i = 0; i < (1 << order); i++)
		page_kasan_tag_set(page + i, tag);
	kasan_unpoison(page_address(page), PAGE_SIZE << order, init);
पूर्ण

व्योम __kasan_मुक्त_pages(काष्ठा page *page, अचिन्हित पूर्णांक order, bool init)
अणु
	अगर (likely(!PageHighMem(page)))
		kasan_poison(page_address(page), PAGE_SIZE << order,
			     KASAN_FREE_PAGE, init);
पूर्ण

/*
 * Adaptive redzone policy taken from the userspace AddressSanitizer runसमय.
 * For larger allocations larger redzones are used.
 */
अटल अंतरभूत अचिन्हित पूर्णांक optimal_redzone(अचिन्हित पूर्णांक object_size)
अणु
	वापस
		object_size <= 64        - 16   ? 16 :
		object_size <= 128       - 32   ? 32 :
		object_size <= 512       - 64   ? 64 :
		object_size <= 4096      - 128  ? 128 :
		object_size <= (1 << 14) - 256  ? 256 :
		object_size <= (1 << 15) - 512  ? 512 :
		object_size <= (1 << 16) - 1024 ? 1024 : 2048;
पूर्ण

व्योम __kasan_cache_create(काष्ठा kmem_cache *cache, अचिन्हित पूर्णांक *size,
			  slab_flags_t *flags)
अणु
	अचिन्हित पूर्णांक ok_size;
	अचिन्हित पूर्णांक optimal_size;

	/*
	 * SLAB_KASAN is used to mark caches as ones that are sanitized by
	 * KASAN. Currently this flag is used in two places:
	 * 1. In slab_ksize() when calculating the size of the accessible
	 *    memory within the object.
	 * 2. In slab_common.c to prevent merging of sanitized caches.
	 */
	*flags |= SLAB_KASAN;

	अगर (!kasan_stack_collection_enabled())
		वापस;

	ok_size = *size;

	/* Add alloc meta पूर्णांकo redzone. */
	cache->kasan_info.alloc_meta_offset = *size;
	*size += माप(काष्ठा kasan_alloc_meta);

	/*
	 * If alloc meta करोesn't fit, don't add it.
	 * This can only happen with SLAB, as it has KMALLOC_MAX_SIZE equal
	 * to KMALLOC_MAX_CACHE_SIZE and करोesn't fall back to page_alloc क्रम
	 * larger sizes.
	 */
	अगर (*size > KMALLOC_MAX_SIZE) अणु
		cache->kasan_info.alloc_meta_offset = 0;
		*size = ok_size;
		/* Continue, since मुक्त meta might still fit. */
	पूर्ण

	/* Only the generic mode uses मुक्त meta or flexible redzones. */
	अगर (!IS_ENABLED(CONFIG_KASAN_GENERIC)) अणु
		cache->kasan_info.मुक्त_meta_offset = KASAN_NO_FREE_META;
		वापस;
	पूर्ण

	/*
	 * Add मुक्त meta पूर्णांकo redzone when it's not possible to store
	 * it in the object. This is the हाल when:
	 * 1. Object is SLAB_TYPESAFE_BY_RCU, which means that it can
	 *    be touched after it was मुक्तd, or
	 * 2. Object has a स्थिरructor, which means it's expected to
	 *    retain its content until the next allocation, or
	 * 3. Object is too small.
	 * Otherwise cache->kasan_info.मुक्त_meta_offset = 0 is implied.
	 */
	अगर ((cache->flags & SLAB_TYPESAFE_BY_RCU) || cache->ctor ||
	    cache->object_size < माप(काष्ठा kasan_मुक्त_meta)) अणु
		ok_size = *size;

		cache->kasan_info.मुक्त_meta_offset = *size;
		*size += माप(काष्ठा kasan_मुक्त_meta);

		/* If मुक्त meta करोesn't fit, don't add it. */
		अगर (*size > KMALLOC_MAX_SIZE) अणु
			cache->kasan_info.मुक्त_meta_offset = KASAN_NO_FREE_META;
			*size = ok_size;
		पूर्ण
	पूर्ण

	/* Calculate size with optimal redzone. */
	optimal_size = cache->object_size + optimal_redzone(cache->object_size);
	/* Limit it with KMALLOC_MAX_SIZE (relevant क्रम SLAB only). */
	अगर (optimal_size > KMALLOC_MAX_SIZE)
		optimal_size = KMALLOC_MAX_SIZE;
	/* Use optimal size अगर the size with added metas is not large enough. */
	अगर (*size < optimal_size)
		*size = optimal_size;
पूर्ण

व्योम __kasan_cache_create_kदो_स्मृति(काष्ठा kmem_cache *cache)
अणु
	cache->kasan_info.is_kदो_स्मृति = true;
पूर्ण

माप_प्रकार __kasan_metadata_size(काष्ठा kmem_cache *cache)
अणु
	अगर (!kasan_stack_collection_enabled())
		वापस 0;
	वापस (cache->kasan_info.alloc_meta_offset ?
		माप(काष्ठा kasan_alloc_meta) : 0) +
		(cache->kasan_info.मुक्त_meta_offset ?
		माप(काष्ठा kasan_मुक्त_meta) : 0);
पूर्ण

काष्ठा kasan_alloc_meta *kasan_get_alloc_meta(काष्ठा kmem_cache *cache,
					      स्थिर व्योम *object)
अणु
	अगर (!cache->kasan_info.alloc_meta_offset)
		वापस शून्य;
	वापस kasan_reset_tag(object) + cache->kasan_info.alloc_meta_offset;
पूर्ण

#अगर_घोषित CONFIG_KASAN_GENERIC
काष्ठा kasan_मुक्त_meta *kasan_get_मुक्त_meta(काष्ठा kmem_cache *cache,
					    स्थिर व्योम *object)
अणु
	BUILD_BUG_ON(माप(काष्ठा kasan_मुक्त_meta) > 32);
	अगर (cache->kasan_info.मुक्त_meta_offset == KASAN_NO_FREE_META)
		वापस शून्य;
	वापस kasan_reset_tag(object) + cache->kasan_info.मुक्त_meta_offset;
पूर्ण
#पूर्ण_अगर

व्योम __kasan_poison_slab(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < compound_nr(page); i++)
		page_kasan_tag_reset(page + i);
	kasan_poison(page_address(page), page_size(page),
		     KASAN_KMALLOC_REDZONE, false);
पूर्ण

व्योम __kasan_unpoison_object_data(काष्ठा kmem_cache *cache, व्योम *object)
अणु
	kasan_unpoison(object, cache->object_size, false);
पूर्ण

व्योम __kasan_poison_object_data(काष्ठा kmem_cache *cache, व्योम *object)
अणु
	kasan_poison(object, round_up(cache->object_size, KASAN_GRANULE_SIZE),
			KASAN_KMALLOC_REDZONE, false);
पूर्ण

/*
 * This function assigns a tag to an object considering the following:
 * 1. A cache might have a स्थिरructor, which might save a poपूर्णांकer to a slab
 *    object somewhere (e.g. in the object itself). We preassign a tag क्रम
 *    each object in caches with स्थिरructors during slab creation and reuse
 *    the same tag each समय a particular object is allocated.
 * 2. A cache might be SLAB_TYPESAFE_BY_RCU, which means objects can be
 *    accessed after being मुक्तd. We preassign tags क्रम objects in these
 *    caches as well.
 * 3. For SLAB allocator we can't preassign tags अक्रमomly since the मुक्तlist
 *    is stored as an array of indexes instead of a linked list. Assign tags
 *    based on objects indexes, so that objects that are next to each other
 *    get dअगरferent tags.
 */
अटल अंतरभूत u8 assign_tag(काष्ठा kmem_cache *cache,
					स्थिर व्योम *object, bool init)
अणु
	अगर (IS_ENABLED(CONFIG_KASAN_GENERIC))
		वापस 0xff;

	/*
	 * If the cache neither has a स्थिरructor nor has SLAB_TYPESAFE_BY_RCU
	 * set, assign a tag when the object is being allocated (init == false).
	 */
	अगर (!cache->ctor && !(cache->flags & SLAB_TYPESAFE_BY_RCU))
		वापस init ? KASAN_TAG_KERNEL : kasan_अक्रमom_tag();

	/* For caches that either have a स्थिरructor or SLAB_TYPESAFE_BY_RCU: */
#अगर_घोषित CONFIG_SLAB
	/* For SLAB assign tags based on the object index in the मुक्तlist. */
	वापस (u8)obj_to_index(cache, virt_to_page(object), (व्योम *)object);
#अन्यथा
	/*
	 * For SLUB assign a अक्रमom tag during slab creation, otherwise reuse
	 * the alपढ़ोy asचिन्हित tag.
	 */
	वापस init ? kasan_अक्रमom_tag() : get_tag(object);
#पूर्ण_अगर
पूर्ण

व्योम * __must_check __kasan_init_slab_obj(काष्ठा kmem_cache *cache,
						स्थिर व्योम *object)
अणु
	काष्ठा kasan_alloc_meta *alloc_meta;

	अगर (kasan_stack_collection_enabled()) अणु
		alloc_meta = kasan_get_alloc_meta(cache, object);
		अगर (alloc_meta)
			__स_रखो(alloc_meta, 0, माप(*alloc_meta));
	पूर्ण

	/* Tag is ignored in set_tag() without CONFIG_KASAN_SW/HW_TAGS */
	object = set_tag(object, assign_tag(cache, object, true));

	वापस (व्योम *)object;
पूर्ण

अटल अंतरभूत bool ____kasan_slab_मुक्त(काष्ठा kmem_cache *cache, व्योम *object,
				अचिन्हित दीर्घ ip, bool quarantine, bool init)
अणु
	u8 tag;
	व्योम *tagged_object;

	tag = get_tag(object);
	tagged_object = object;
	object = kasan_reset_tag(object);

	अगर (is_kfence_address(object))
		वापस false;

	अगर (unlikely(nearest_obj(cache, virt_to_head_page(object), object) !=
	    object)) अणु
		kasan_report_invalid_मुक्त(tagged_object, ip);
		वापस true;
	पूर्ण

	/* RCU sद_असल could be legally used after मुक्त within the RCU period */
	अगर (unlikely(cache->flags & SLAB_TYPESAFE_BY_RCU))
		वापस false;

	अगर (!kasan_byte_accessible(tagged_object)) अणु
		kasan_report_invalid_मुक्त(tagged_object, ip);
		वापस true;
	पूर्ण

	kasan_poison(object, round_up(cache->object_size, KASAN_GRANULE_SIZE),
			KASAN_KMALLOC_FREE, init);

	अगर ((IS_ENABLED(CONFIG_KASAN_GENERIC) && !quarantine))
		वापस false;

	अगर (kasan_stack_collection_enabled())
		kasan_set_मुक्त_info(cache, object, tag);

	वापस kasan_quarantine_put(cache, object);
पूर्ण

bool __kasan_slab_मुक्त(काष्ठा kmem_cache *cache, व्योम *object,
				अचिन्हित दीर्घ ip, bool init)
अणु
	वापस ____kasan_slab_मुक्त(cache, object, ip, true, init);
पूर्ण

अटल अंतरभूत bool ____kasan_kमुक्त_large(व्योम *ptr, अचिन्हित दीर्घ ip)
अणु
	अगर (ptr != page_address(virt_to_head_page(ptr))) अणु
		kasan_report_invalid_मुक्त(ptr, ip);
		वापस true;
	पूर्ण

	अगर (!kasan_byte_accessible(ptr)) अणु
		kasan_report_invalid_मुक्त(ptr, ip);
		वापस true;
	पूर्ण

	/*
	 * The object will be poisoned by kasan_मुक्त_pages() or
	 * kasan_slab_मुक्त_mempool().
	 */

	वापस false;
पूर्ण

व्योम __kasan_kमुक्त_large(व्योम *ptr, अचिन्हित दीर्घ ip)
अणु
	____kasan_kमुक्त_large(ptr, ip);
पूर्ण

व्योम __kasan_slab_मुक्त_mempool(व्योम *ptr, अचिन्हित दीर्घ ip)
अणु
	काष्ठा page *page;

	page = virt_to_head_page(ptr);

	/*
	 * Even though this function is only called क्रम kmem_cache_alloc and
	 * kदो_स्मृति backed mempool allocations, those allocations can still be
	 * !PageSlab() when the size provided to kदो_स्मृति is larger than
	 * KMALLOC_MAX_SIZE, and kदो_स्मृति falls back onto page_alloc.
	 */
	अगर (unlikely(!PageSlab(page))) अणु
		अगर (____kasan_kमुक्त_large(ptr, ip))
			वापस;
		kasan_poison(ptr, page_size(page), KASAN_FREE_PAGE, false);
	पूर्ण अन्यथा अणु
		____kasan_slab_मुक्त(page->slab_cache, ptr, ip, false, false);
	पूर्ण
पूर्ण

अटल व्योम set_alloc_info(काष्ठा kmem_cache *cache, व्योम *object,
				gfp_t flags, bool is_kदो_स्मृति)
अणु
	काष्ठा kasan_alloc_meta *alloc_meta;

	/* Don't save alloc info क्रम kदो_स्मृति caches in kasan_slab_alloc(). */
	अगर (cache->kasan_info.is_kदो_स्मृति && !is_kदो_स्मृति)
		वापस;

	alloc_meta = kasan_get_alloc_meta(cache, object);
	अगर (alloc_meta)
		kasan_set_track(&alloc_meta->alloc_track, flags);
पूर्ण

व्योम * __must_check __kasan_slab_alloc(काष्ठा kmem_cache *cache,
					व्योम *object, gfp_t flags, bool init)
अणु
	u8 tag;
	व्योम *tagged_object;

	अगर (gfpflags_allow_blocking(flags))
		kasan_quarantine_reduce();

	अगर (unlikely(object == शून्य))
		वापस शून्य;

	अगर (is_kfence_address(object))
		वापस (व्योम *)object;

	/*
	 * Generate and assign अक्रमom tag क्रम tag-based modes.
	 * Tag is ignored in set_tag() क्रम the generic mode.
	 */
	tag = assign_tag(cache, object, false);
	tagged_object = set_tag(object, tag);

	/*
	 * Unpoison the whole object.
	 * For kदो_स्मृति() allocations, kasan_kदो_स्मृति() will करो precise poisoning.
	 */
	kasan_unpoison(tagged_object, cache->object_size, init);

	/* Save alloc info (अगर possible) क्रम non-kदो_स्मृति() allocations. */
	अगर (kasan_stack_collection_enabled())
		set_alloc_info(cache, (व्योम *)object, flags, false);

	वापस tagged_object;
पूर्ण

अटल अंतरभूत व्योम *____kasan_kदो_स्मृति(काष्ठा kmem_cache *cache,
				स्थिर व्योम *object, माप_प्रकार size, gfp_t flags)
अणु
	अचिन्हित दीर्घ redzone_start;
	अचिन्हित दीर्घ redzone_end;

	अगर (gfpflags_allow_blocking(flags))
		kasan_quarantine_reduce();

	अगर (unlikely(object == शून्य))
		वापस शून्य;

	अगर (is_kfence_address(kasan_reset_tag(object)))
		वापस (व्योम *)object;

	/*
	 * The object has alपढ़ोy been unpoisoned by kasan_slab_alloc() क्रम
	 * kदो_स्मृति() or by kasan_kपुनः_स्मृति() क्रम kपुनः_स्मृति().
	 */

	/*
	 * The redzone has byte-level precision क्रम the generic mode.
	 * Partially poison the last object granule to cover the unaligned
	 * part of the redzone.
	 */
	अगर (IS_ENABLED(CONFIG_KASAN_GENERIC))
		kasan_poison_last_granule((व्योम *)object, size);

	/* Poison the aligned part of the redzone. */
	redzone_start = round_up((अचिन्हित दीर्घ)(object + size),
				KASAN_GRANULE_SIZE);
	redzone_end = round_up((अचिन्हित दीर्घ)(object + cache->object_size),
				KASAN_GRANULE_SIZE);
	kasan_poison((व्योम *)redzone_start, redzone_end - redzone_start,
			   KASAN_KMALLOC_REDZONE, false);

	/*
	 * Save alloc info (अगर possible) क्रम kदो_स्मृति() allocations.
	 * This also reग_लिखोs the alloc info when called from kasan_kपुनः_स्मृति().
	 */
	अगर (kasan_stack_collection_enabled())
		set_alloc_info(cache, (व्योम *)object, flags, true);

	/* Keep the tag that was set by kasan_slab_alloc(). */
	वापस (व्योम *)object;
पूर्ण

व्योम * __must_check __kasan_kदो_स्मृति(काष्ठा kmem_cache *cache, स्थिर व्योम *object,
					माप_प्रकार size, gfp_t flags)
अणु
	वापस ____kasan_kदो_स्मृति(cache, object, size, flags);
पूर्ण
EXPORT_SYMBOL(__kasan_kदो_स्मृति);

व्योम * __must_check __kasan_kदो_स्मृति_large(स्थिर व्योम *ptr, माप_प्रकार size,
						gfp_t flags)
अणु
	अचिन्हित दीर्घ redzone_start;
	अचिन्हित दीर्घ redzone_end;

	अगर (gfpflags_allow_blocking(flags))
		kasan_quarantine_reduce();

	अगर (unlikely(ptr == शून्य))
		वापस शून्य;

	/*
	 * The object has alपढ़ोy been unpoisoned by kasan_alloc_pages() क्रम
	 * alloc_pages() or by kasan_kपुनः_स्मृति() क्रम kपुनः_स्मृति().
	 */

	/*
	 * The redzone has byte-level precision क्रम the generic mode.
	 * Partially poison the last object granule to cover the unaligned
	 * part of the redzone.
	 */
	अगर (IS_ENABLED(CONFIG_KASAN_GENERIC))
		kasan_poison_last_granule(ptr, size);

	/* Poison the aligned part of the redzone. */
	redzone_start = round_up((अचिन्हित दीर्घ)(ptr + size),
				KASAN_GRANULE_SIZE);
	redzone_end = (अचिन्हित दीर्घ)ptr + page_size(virt_to_page(ptr));
	kasan_poison((व्योम *)redzone_start, redzone_end - redzone_start,
		     KASAN_PAGE_REDZONE, false);

	वापस (व्योम *)ptr;
पूर्ण

व्योम * __must_check __kasan_kपुनः_स्मृति(स्थिर व्योम *object, माप_प्रकार size, gfp_t flags)
अणु
	काष्ठा page *page;

	अगर (unlikely(object == ZERO_SIZE_PTR))
		वापस (व्योम *)object;

	/*
	 * Unpoison the object's data.
	 * Part of it might alपढ़ोy have been unpoisoned, but it's unknown
	 * how big that part is.
	 */
	kasan_unpoison(object, size, false);

	page = virt_to_head_page(object);

	/* Piggy-back on kदो_स्मृति() instrumentation to poison the redzone. */
	अगर (unlikely(!PageSlab(page)))
		वापस __kasan_kदो_स्मृति_large(object, size, flags);
	अन्यथा
		वापस ____kasan_kदो_स्मृति(page->slab_cache, object, size, flags);
पूर्ण

bool __kasan_check_byte(स्थिर व्योम *address, अचिन्हित दीर्घ ip)
अणु
	अगर (!kasan_byte_accessible(address)) अणु
		kasan_report((अचिन्हित दीर्घ)address, 1, false, ip);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KASAN_H
#घोषणा _LINUX_KASAN_H

#समावेश <linux/अटल_key.h>
#समावेश <linux/types.h>

काष्ठा kmem_cache;
काष्ठा page;
काष्ठा vm_काष्ठा;
काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_KASAN

#समावेश <linux/linkage.h>
#समावेश <यंत्र/kasan.h>

/* kasan_data काष्ठा is used in KUnit tests क्रम KASAN expected failures */
काष्ठा kunit_kasan_expectation अणु
	bool report_expected;
	bool report_found;
पूर्ण;

#पूर्ण_अगर

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)

#समावेश <linux/pgtable.h>

/* Software KASAN implementations use shaकरोw memory. */

#अगर_घोषित CONFIG_KASAN_SW_TAGS
/* This matches KASAN_TAG_INVALID. */
#घोषणा KASAN_SHADOW_INIT 0xFE
#अन्यथा
#घोषणा KASAN_SHADOW_INIT 0
#पूर्ण_अगर

#अगर_अघोषित PTE_HWTABLE_PTRS
#घोषणा PTE_HWTABLE_PTRS 0
#पूर्ण_अगर

बाह्य अचिन्हित अक्षर kasan_early_shaकरोw_page[PAGE_SIZE];
बाह्य pte_t kasan_early_shaकरोw_pte[PTRS_PER_PTE + PTE_HWTABLE_PTRS];
बाह्य pmd_t kasan_early_shaकरोw_pmd[PTRS_PER_PMD];
बाह्य pud_t kasan_early_shaकरोw_pud[PTRS_PER_PUD];
बाह्य p4d_t kasan_early_shaकरोw_p4d[MAX_PTRS_PER_P4D];

पूर्णांक kasan_populate_early_shaकरोw(स्थिर व्योम *shaकरोw_start,
				स्थिर व्योम *shaकरोw_end);

अटल अंतरभूत व्योम *kasan_mem_to_shaकरोw(स्थिर व्योम *addr)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)addr >> KASAN_SHADOW_SCALE_SHIFT)
		+ KASAN_SHADOW_OFFSET;
पूर्ण

पूर्णांक kasan_add_zero_shaकरोw(व्योम *start, अचिन्हित दीर्घ size);
व्योम kasan_हटाओ_zero_shaकरोw(व्योम *start, अचिन्हित दीर्घ size);

/* Enable reporting bugs after kasan_disable_current() */
बाह्य व्योम kasan_enable_current(व्योम);

/* Disable reporting bugs क्रम current task */
बाह्य व्योम kasan_disable_current(व्योम);

#अन्यथा /* CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS */

अटल अंतरभूत पूर्णांक kasan_add_zero_shaकरोw(व्योम *start, अचिन्हित दीर्घ size)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम kasan_हटाओ_zero_shaकरोw(व्योम *start,
					अचिन्हित दीर्घ size)
अणुपूर्ण

अटल अंतरभूत व्योम kasan_enable_current(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kasan_disable_current(व्योम) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS */

#अगर_घोषित CONFIG_KASAN

काष्ठा kasan_cache अणु
	पूर्णांक alloc_meta_offset;
	पूर्णांक मुक्त_meta_offset;
	bool is_kदो_स्मृति;
पूर्ण;

#अगर_घोषित CONFIG_KASAN_HW_TAGS

DECLARE_STATIC_KEY_FALSE(kasan_flag_enabled);

अटल __always_अंतरभूत bool kasan_enabled(व्योम)
अणु
	वापस अटल_branch_likely(&kasan_flag_enabled);
पूर्ण

अटल अंतरभूत bool kasan_has_पूर्णांकegrated_init(व्योम)
अणु
	वापस kasan_enabled();
पूर्ण

#अन्यथा /* CONFIG_KASAN_HW_TAGS */

अटल अंतरभूत bool kasan_enabled(व्योम)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool kasan_has_पूर्णांकegrated_init(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_HW_TAGS */

slab_flags_t __kasan_never_merge(व्योम);
अटल __always_अंतरभूत slab_flags_t kasan_never_merge(व्योम)
अणु
	अगर (kasan_enabled())
		वापस __kasan_never_merge();
	वापस 0;
पूर्ण

व्योम __kasan_unpoison_range(स्थिर व्योम *addr, माप_प्रकार size);
अटल __always_अंतरभूत व्योम kasan_unpoison_range(स्थिर व्योम *addr, माप_प्रकार size)
अणु
	अगर (kasan_enabled())
		__kasan_unpoison_range(addr, size);
पूर्ण

व्योम __kasan_alloc_pages(काष्ठा page *page, अचिन्हित पूर्णांक order, bool init);
अटल __always_अंतरभूत व्योम kasan_alloc_pages(काष्ठा page *page,
						अचिन्हित पूर्णांक order, bool init)
अणु
	अगर (kasan_enabled())
		__kasan_alloc_pages(page, order, init);
पूर्ण

व्योम __kasan_मुक्त_pages(काष्ठा page *page, अचिन्हित पूर्णांक order, bool init);
अटल __always_अंतरभूत व्योम kasan_मुक्त_pages(काष्ठा page *page,
						अचिन्हित पूर्णांक order, bool init)
अणु
	अगर (kasan_enabled())
		__kasan_मुक्त_pages(page, order, init);
पूर्ण

व्योम __kasan_cache_create(काष्ठा kmem_cache *cache, अचिन्हित पूर्णांक *size,
				slab_flags_t *flags);
अटल __always_अंतरभूत व्योम kasan_cache_create(काष्ठा kmem_cache *cache,
				अचिन्हित पूर्णांक *size, slab_flags_t *flags)
अणु
	अगर (kasan_enabled())
		__kasan_cache_create(cache, size, flags);
पूर्ण

व्योम __kasan_cache_create_kदो_स्मृति(काष्ठा kmem_cache *cache);
अटल __always_अंतरभूत व्योम kasan_cache_create_kदो_स्मृति(काष्ठा kmem_cache *cache)
अणु
	अगर (kasan_enabled())
		__kasan_cache_create_kदो_स्मृति(cache);
पूर्ण

माप_प्रकार __kasan_metadata_size(काष्ठा kmem_cache *cache);
अटल __always_अंतरभूत माप_प्रकार kasan_metadata_size(काष्ठा kmem_cache *cache)
अणु
	अगर (kasan_enabled())
		वापस __kasan_metadata_size(cache);
	वापस 0;
पूर्ण

व्योम __kasan_poison_slab(काष्ठा page *page);
अटल __always_अंतरभूत व्योम kasan_poison_slab(काष्ठा page *page)
अणु
	अगर (kasan_enabled())
		__kasan_poison_slab(page);
पूर्ण

व्योम __kasan_unpoison_object_data(काष्ठा kmem_cache *cache, व्योम *object);
अटल __always_अंतरभूत व्योम kasan_unpoison_object_data(काष्ठा kmem_cache *cache,
							व्योम *object)
अणु
	अगर (kasan_enabled())
		__kasan_unpoison_object_data(cache, object);
पूर्ण

व्योम __kasan_poison_object_data(काष्ठा kmem_cache *cache, व्योम *object);
अटल __always_अंतरभूत व्योम kasan_poison_object_data(काष्ठा kmem_cache *cache,
							व्योम *object)
अणु
	अगर (kasan_enabled())
		__kasan_poison_object_data(cache, object);
पूर्ण

व्योम * __must_check __kasan_init_slab_obj(काष्ठा kmem_cache *cache,
					  स्थिर व्योम *object);
अटल __always_अंतरभूत व्योम * __must_check kasan_init_slab_obj(
				काष्ठा kmem_cache *cache, स्थिर व्योम *object)
अणु
	अगर (kasan_enabled())
		वापस __kasan_init_slab_obj(cache, object);
	वापस (व्योम *)object;
पूर्ण

bool __kasan_slab_मुक्त(काष्ठा kmem_cache *s, व्योम *object,
			अचिन्हित दीर्घ ip, bool init);
अटल __always_अंतरभूत bool kasan_slab_मुक्त(काष्ठा kmem_cache *s,
						व्योम *object, bool init)
अणु
	अगर (kasan_enabled())
		वापस __kasan_slab_मुक्त(s, object, _RET_IP_, init);
	वापस false;
पूर्ण

व्योम __kasan_kमुक्त_large(व्योम *ptr, अचिन्हित दीर्घ ip);
अटल __always_अंतरभूत व्योम kasan_kमुक्त_large(व्योम *ptr)
अणु
	अगर (kasan_enabled())
		__kasan_kमुक्त_large(ptr, _RET_IP_);
पूर्ण

व्योम __kasan_slab_मुक्त_mempool(व्योम *ptr, अचिन्हित दीर्घ ip);
अटल __always_अंतरभूत व्योम kasan_slab_मुक्त_mempool(व्योम *ptr)
अणु
	अगर (kasan_enabled())
		__kasan_slab_मुक्त_mempool(ptr, _RET_IP_);
पूर्ण

व्योम * __must_check __kasan_slab_alloc(काष्ठा kmem_cache *s,
				       व्योम *object, gfp_t flags, bool init);
अटल __always_अंतरभूत व्योम * __must_check kasan_slab_alloc(
		काष्ठा kmem_cache *s, व्योम *object, gfp_t flags, bool init)
अणु
	अगर (kasan_enabled())
		वापस __kasan_slab_alloc(s, object, flags, init);
	वापस object;
पूर्ण

व्योम * __must_check __kasan_kदो_स्मृति(काष्ठा kmem_cache *s, स्थिर व्योम *object,
				    माप_प्रकार size, gfp_t flags);
अटल __always_अंतरभूत व्योम * __must_check kasan_kदो_स्मृति(काष्ठा kmem_cache *s,
				स्थिर व्योम *object, माप_प्रकार size, gfp_t flags)
अणु
	अगर (kasan_enabled())
		वापस __kasan_kदो_स्मृति(s, object, size, flags);
	वापस (व्योम *)object;
पूर्ण

व्योम * __must_check __kasan_kदो_स्मृति_large(स्थिर व्योम *ptr,
					  माप_प्रकार size, gfp_t flags);
अटल __always_अंतरभूत व्योम * __must_check kasan_kदो_स्मृति_large(स्थिर व्योम *ptr,
						      माप_प्रकार size, gfp_t flags)
अणु
	अगर (kasan_enabled())
		वापस __kasan_kदो_स्मृति_large(ptr, size, flags);
	वापस (व्योम *)ptr;
पूर्ण

व्योम * __must_check __kasan_kपुनः_स्मृति(स्थिर व्योम *object,
				     माप_प्रकार new_size, gfp_t flags);
अटल __always_अंतरभूत व्योम * __must_check kasan_kपुनः_स्मृति(स्थिर व्योम *object,
						 माप_प्रकार new_size, gfp_t flags)
अणु
	अगर (kasan_enabled())
		वापस __kasan_kपुनः_स्मृति(object, new_size, flags);
	वापस (व्योम *)object;
पूर्ण

/*
 * Unlike kasan_check_पढ़ो/ग_लिखो(), kasan_check_byte() is perक्रमmed even क्रम
 * the hardware tag-based mode that करोesn't rely on compiler instrumentation.
 */
bool __kasan_check_byte(स्थिर व्योम *addr, अचिन्हित दीर्घ ip);
अटल __always_अंतरभूत bool kasan_check_byte(स्थिर व्योम *addr)
अणु
	अगर (kasan_enabled())
		वापस __kasan_check_byte(addr, _RET_IP_);
	वापस true;
पूर्ण


bool kasan_save_enable_multi_shot(व्योम);
व्योम kasan_restore_multi_shot(bool enabled);

#अन्यथा /* CONFIG_KASAN */

अटल अंतरभूत bool kasan_enabled(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool kasan_has_पूर्णांकegrated_init(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत slab_flags_t kasan_never_merge(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम kasan_unpoison_range(स्थिर व्योम *address, माप_प्रकार size) अणुपूर्ण
अटल अंतरभूत व्योम kasan_alloc_pages(काष्ठा page *page, अचिन्हित पूर्णांक order, bool init) अणुपूर्ण
अटल अंतरभूत व्योम kasan_मुक्त_pages(काष्ठा page *page, अचिन्हित पूर्णांक order, bool init) अणुपूर्ण
अटल अंतरभूत व्योम kasan_cache_create(काष्ठा kmem_cache *cache,
				      अचिन्हित पूर्णांक *size,
				      slab_flags_t *flags) अणुपूर्ण
अटल अंतरभूत व्योम kasan_cache_create_kदो_स्मृति(काष्ठा kmem_cache *cache) अणुपूर्ण
अटल अंतरभूत माप_प्रकार kasan_metadata_size(काष्ठा kmem_cache *cache) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम kasan_poison_slab(काष्ठा page *page) अणुपूर्ण
अटल अंतरभूत व्योम kasan_unpoison_object_data(काष्ठा kmem_cache *cache,
					व्योम *object) अणुपूर्ण
अटल अंतरभूत व्योम kasan_poison_object_data(काष्ठा kmem_cache *cache,
					व्योम *object) अणुपूर्ण
अटल अंतरभूत व्योम *kasan_init_slab_obj(काष्ठा kmem_cache *cache,
				स्थिर व्योम *object)
अणु
	वापस (व्योम *)object;
पूर्ण
अटल अंतरभूत bool kasan_slab_मुक्त(काष्ठा kmem_cache *s, व्योम *object, bool init)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम kasan_kमुक्त_large(व्योम *ptr) अणुपूर्ण
अटल अंतरभूत व्योम kasan_slab_मुक्त_mempool(व्योम *ptr) अणुपूर्ण
अटल अंतरभूत व्योम *kasan_slab_alloc(काष्ठा kmem_cache *s, व्योम *object,
				   gfp_t flags, bool init)
अणु
	वापस object;
पूर्ण
अटल अंतरभूत व्योम *kasan_kदो_स्मृति(काष्ठा kmem_cache *s, स्थिर व्योम *object,
				माप_प्रकार size, gfp_t flags)
अणु
	वापस (व्योम *)object;
पूर्ण
अटल अंतरभूत व्योम *kasan_kदो_स्मृति_large(स्थिर व्योम *ptr, माप_प्रकार size, gfp_t flags)
अणु
	वापस (व्योम *)ptr;
पूर्ण
अटल अंतरभूत व्योम *kasan_kपुनः_स्मृति(स्थिर व्योम *object, माप_प्रकार new_size,
				 gfp_t flags)
अणु
	वापस (व्योम *)object;
पूर्ण
अटल अंतरभूत bool kasan_check_byte(स्थिर व्योम *address)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* CONFIG_KASAN */

#अगर defined(CONFIG_KASAN) && defined(CONFIG_KASAN_STACK)
व्योम kasan_unpoison_task_stack(काष्ठा task_काष्ठा *task);
#अन्यथा
अटल अंतरभूत व्योम kasan_unpoison_task_stack(काष्ठा task_काष्ठा *task) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN_GENERIC

व्योम kasan_cache_shrink(काष्ठा kmem_cache *cache);
व्योम kasan_cache_shutकरोwn(काष्ठा kmem_cache *cache);
व्योम kasan_record_aux_stack(व्योम *ptr);

#अन्यथा /* CONFIG_KASAN_GENERIC */

अटल अंतरभूत व्योम kasan_cache_shrink(काष्ठा kmem_cache *cache) अणुपूर्ण
अटल अंतरभूत व्योम kasan_cache_shutकरोwn(काष्ठा kmem_cache *cache) अणुपूर्ण
अटल अंतरभूत व्योम kasan_record_aux_stack(व्योम *ptr) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_GENERIC */

#अगर defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)

अटल अंतरभूत व्योम *kasan_reset_tag(स्थिर व्योम *addr)
अणु
	वापस (व्योम *)arch_kasan_reset_tag(addr);
पूर्ण

/**
 * kasan_report - prपूर्णांक a report about a bad memory access detected by KASAN
 * @addr: address of the bad access
 * @size: size of the bad access
 * @is_ग_लिखो: whether the bad access is a ग_लिखो or a पढ़ो
 * @ip: inकाष्ठाion poपूर्णांकer क्रम the accessibility check or the bad access itself
 */
bool kasan_report(अचिन्हित दीर्घ addr, माप_प्रकार size,
		bool is_ग_लिखो, अचिन्हित दीर्घ ip);

#अन्यथा /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

अटल अंतरभूत व्योम *kasan_reset_tag(स्थिर व्योम *addr)
अणु
	वापस (व्योम *)addr;
पूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS*/

#अगर_घोषित CONFIG_KASAN_HW_TAGS

व्योम kasan_report_async(व्योम);

#पूर्ण_अगर /* CONFIG_KASAN_HW_TAGS */

#अगर_घोषित CONFIG_KASAN_SW_TAGS
व्योम __init kasan_init_sw_tags(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kasan_init_sw_tags(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN_HW_TAGS
व्योम kasan_init_hw_tags_cpu(व्योम);
व्योम __init kasan_init_hw_tags(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kasan_init_hw_tags_cpu(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_init_hw_tags(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN_VMALLOC

पूर्णांक kasan_populate_vदो_स्मृति(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size);
व्योम kasan_poison_vदो_स्मृति(स्थिर व्योम *start, अचिन्हित दीर्घ size);
व्योम kasan_unpoison_vदो_स्मृति(स्थिर व्योम *start, अचिन्हित दीर्घ size);
व्योम kasan_release_vदो_स्मृति(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			   अचिन्हित दीर्घ मुक्त_region_start,
			   अचिन्हित दीर्घ मुक्त_region_end);

#अन्यथा /* CONFIG_KASAN_VMALLOC */

अटल अंतरभूत पूर्णांक kasan_populate_vदो_स्मृति(अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kasan_poison_vदो_स्मृति(स्थिर व्योम *start, अचिन्हित दीर्घ size)
अणु पूर्ण
अटल अंतरभूत व्योम kasan_unpoison_vदो_स्मृति(स्थिर व्योम *start, अचिन्हित दीर्घ size)
अणु पूर्ण
अटल अंतरभूत व्योम kasan_release_vदो_स्मृति(अचिन्हित दीर्घ start,
					 अचिन्हित दीर्घ end,
					 अचिन्हित दीर्घ मुक्त_region_start,
					 अचिन्हित दीर्घ मुक्त_region_end) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_VMALLOC */

#अगर (defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)) && \
		!defined(CONFIG_KASAN_VMALLOC)

/*
 * These functions provide a special हाल to support backing module
 * allocations with real shaकरोw memory. With KASAN vदो_स्मृति, the special
 * हाल is unnecessary, as the work is handled in the generic हाल.
 */
पूर्णांक kasan_module_alloc(व्योम *addr, माप_प्रकार size);
व्योम kasan_मुक्त_shaकरोw(स्थिर काष्ठा vm_काष्ठा *vm);

#अन्यथा /* (CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS) && !CONFIG_KASAN_VMALLOC */

अटल अंतरभूत पूर्णांक kasan_module_alloc(व्योम *addr, माप_प्रकार size) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम kasan_मुक्त_shaकरोw(स्थिर काष्ठा vm_काष्ठा *vm) अणुपूर्ण

#पूर्ण_अगर /* (CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS) && !CONFIG_KASAN_VMALLOC */

#अगर_घोषित CONFIG_KASAN_INLINE
व्योम kasan_non_canonical_hook(अचिन्हित दीर्घ addr);
#अन्यथा /* CONFIG_KASAN_INLINE */
अटल अंतरभूत व्योम kasan_non_canonical_hook(अचिन्हित दीर्घ addr) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_KASAN_INLINE */

#पूर्ण_अगर /* LINUX_KASAN_H */

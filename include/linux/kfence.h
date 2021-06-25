<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Kernel Electric-Fence (KFENCE). Public पूर्णांकerface क्रम allocator and fault
 * handler पूर्णांकegration. For more info see Documentation/dev-tools/kfence.rst.
 *
 * Copyright (C) 2020, Google LLC.
 */

#अगर_अघोषित _LINUX_KFENCE_H
#घोषणा _LINUX_KFENCE_H

#समावेश <linux/mm.h>
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_KFENCE

/*
 * We allocate an even number of pages, as it simplअगरies calculations to map
 * address to metadata indices; effectively, the very first page serves as an
 * extended guard page, but otherwise has no special purpose.
 */
#घोषणा KFENCE_POOL_SIZE ((CONFIG_KFENCE_NUM_OBJECTS + 1) * 2 * PAGE_SIZE)
बाह्य अक्षर *__kfence_pool;

#अगर_घोषित CONFIG_KFENCE_STATIC_KEYS
#समावेश <linux/अटल_key.h>
DECLARE_STATIC_KEY_FALSE(kfence_allocation_key);
#अन्यथा
#समावेश <linux/atomic.h>
बाह्य atomic_t kfence_allocation_gate;
#पूर्ण_अगर

/**
 * is_kfence_address() - check अगर an address beदीर्घs to KFENCE pool
 * @addr: address to check
 *
 * Return: true or false depending on whether the address is within the KFENCE
 * object range.
 *
 * KFENCE objects live in a separate page range and are not to be पूर्णांकermixed
 * with regular heap objects (e.g. KFENCE objects must never be added to the
 * allocator मुक्तlists). Failing to करो so may and will result in heap
 * corruptions, thereक्रमe is_kfence_address() must be used to check whether
 * an object requires specअगरic handling.
 *
 * Note: This function may be used in fast-paths, and is perक्रमmance critical.
 * Future changes should take this पूर्णांकo account; क्रम instance, we want to aव्योम
 * पूर्णांकroducing another load and thereक्रमe need to keep KFENCE_POOL_SIZE a
 * स्थिरant (until immediate patching support is added to the kernel).
 */
अटल __always_अंतरभूत bool is_kfence_address(स्थिर व्योम *addr)
अणु
	/*
	 * The non-शून्य check is required in हाल the __kfence_pool poपूर्णांकer was
	 * never initialized; keep it in the slow-path after the range-check.
	 */
	वापस unlikely((अचिन्हित दीर्घ)((अक्षर *)addr - __kfence_pool) < KFENCE_POOL_SIZE && addr);
पूर्ण

/**
 * kfence_alloc_pool() - allocate the KFENCE pool via memblock
 */
व्योम __init kfence_alloc_pool(व्योम);

/**
 * kfence_init() - perक्रमm KFENCE initialization at boot समय
 *
 * Requires that kfence_alloc_pool() was called beक्रमe. This sets up the
 * allocation gate समयr, and requires that workqueues are available.
 */
व्योम __init kfence_init(व्योम);

/**
 * kfence_shutकरोwn_cache() - handle shutकरोwn_cache() क्रम KFENCE objects
 * @s: cache being shut करोwn
 *
 * Beक्रमe shutting करोwn a cache, one must ensure there are no reमुख्यing objects
 * allocated from it. Because KFENCE objects are not referenced from the cache
 * directly, we need to check them here.
 *
 * Note that shutकरोwn_cache() is पूर्णांकernal to SL*B, and kmem_cache_destroy() करोes
 * not वापस अगर allocated objects still exist: it prपूर्णांकs an error message and
 * simply पातs deकाष्ठाion of a cache, leaking memory.
 *
 * If the only such objects are KFENCE objects, we will not leak the entire
 * cache, but instead try to provide more useful debug info by making allocated
 * objects "zombie allocations". Objects may then still be used or मुक्तd (which
 * is handled gracefully), but usage will result in showing KFENCE error reports
 * which include stack traces to the user of the object, the original allocation
 * site, and caller to shutकरोwn_cache().
 */
व्योम kfence_shutकरोwn_cache(काष्ठा kmem_cache *s);

/*
 * Allocate a KFENCE object. Allocators must not call this function directly,
 * use kfence_alloc() instead.
 */
व्योम *__kfence_alloc(काष्ठा kmem_cache *s, माप_प्रकार size, gfp_t flags);

/**
 * kfence_alloc() - allocate a KFENCE object with a low probability
 * @s:     काष्ठा kmem_cache with object requirements
 * @size:  exact size of the object to allocate (can be less than @s->size
 *         e.g. क्रम kदो_स्मृति caches)
 * @flags: GFP flags
 *
 * Return:
 * * शून्य     - must proceed with allocating as usual,
 * * non-शून्य - poपूर्णांकer to a KFENCE object.
 *
 * kfence_alloc() should be inserted पूर्णांकo the heap allocation fast path,
 * allowing it to transparently वापस KFENCE-allocated objects with a low
 * probability using a अटल branch (the probability is controlled by the
 * kfence.sample_पूर्णांकerval boot parameter).
 */
अटल __always_अंतरभूत व्योम *kfence_alloc(काष्ठा kmem_cache *s, माप_प्रकार size, gfp_t flags)
अणु
#अगर_घोषित CONFIG_KFENCE_STATIC_KEYS
	अगर (अटल_branch_unlikely(&kfence_allocation_key))
#अन्यथा
	अगर (unlikely(!atomic_पढ़ो(&kfence_allocation_gate)))
#पूर्ण_अगर
		वापस __kfence_alloc(s, size, flags);
	वापस शून्य;
पूर्ण

/**
 * kfence_ksize() - get actual amount of memory allocated क्रम a KFENCE object
 * @addr: poपूर्णांकer to a heap object
 *
 * Return:
 * * 0     - not a KFENCE object, must call __ksize() instead,
 * * non-0 - this many bytes can be accessed without causing a memory error.
 *
 * kfence_ksize() वापसs the number of bytes requested क्रम a KFENCE object at
 * allocation समय. This number may be less than the object size of the
 * corresponding काष्ठा kmem_cache.
 */
माप_प्रकार kfence_ksize(स्थिर व्योम *addr);

/**
 * kfence_object_start() - find the beginning of a KFENCE object
 * @addr: address within a KFENCE-allocated object
 *
 * Return: address of the beginning of the object.
 *
 * SL[AU]B-allocated objects are laid out within a page one by one, so it is
 * easy to calculate the beginning of an object given a poपूर्णांकer inside it and
 * the object size. The same is not true क्रम KFENCE, which places a single
 * object at either end of the page. This helper function is used to find the
 * beginning of a KFENCE-allocated object.
 */
व्योम *kfence_object_start(स्थिर व्योम *addr);

/**
 * __kfence_मुक्त() - release a KFENCE heap object to KFENCE pool
 * @addr: object to be मुक्तd
 *
 * Requires: is_kfence_address(addr)
 *
 * Release a KFENCE object and mark it as मुक्तd.
 */
व्योम __kfence_मुक्त(व्योम *addr);

/**
 * kfence_मुक्त() - try to release an arbitrary heap object to KFENCE pool
 * @addr: object to be मुक्तd
 *
 * Return:
 * * false - object करोesn't beदीर्घ to KFENCE pool and was ignored,
 * * true  - object was released to KFENCE pool.
 *
 * Release a KFENCE object and mark it as मुक्तd. May be called on any object,
 * even non-KFENCE objects, to simplअगरy पूर्णांकegration of the hooks पूर्णांकo the
 * allocator's मुक्त codepath. The allocator must check the वापस value to
 * determine अगर it was a KFENCE object or not.
 */
अटल __always_अंतरभूत __must_check bool kfence_मुक्त(व्योम *addr)
अणु
	अगर (!is_kfence_address(addr))
		वापस false;
	__kfence_मुक्त(addr);
	वापस true;
पूर्ण

/**
 * kfence_handle_page_fault() - perक्रमm page fault handling क्रम KFENCE pages
 * @addr: faulting address
 * @is_ग_लिखो: is access a ग_लिखो
 * @regs: current काष्ठा pt_regs (can be शून्य, but shows full stack trace)
 *
 * Return:
 * * false - address outside KFENCE pool,
 * * true  - page fault handled by KFENCE, no additional handling required.
 *
 * A page fault inside KFENCE pool indicates a memory error, such as an
 * out-of-bounds access, a use-after-मुक्त or an invalid memory access. In these
 * हालs KFENCE prपूर्णांकs an error message and marks the offending page as
 * present, so that the kernel can proceed.
 */
bool __must_check kfence_handle_page_fault(अचिन्हित दीर्घ addr, bool is_ग_लिखो, काष्ठा pt_regs *regs);

#अन्यथा /* CONFIG_KFENCE */

अटल अंतरभूत bool is_kfence_address(स्थिर व्योम *addr) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम kfence_alloc_pool(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kfence_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kfence_shutकरोwn_cache(काष्ठा kmem_cache *s) अणु पूर्ण
अटल अंतरभूत व्योम *kfence_alloc(काष्ठा kmem_cache *s, माप_प्रकार size, gfp_t flags) अणु वापस शून्य; पूर्ण
अटल अंतरभूत माप_प्रकार kfence_ksize(स्थिर व्योम *addr) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम *kfence_object_start(स्थिर व्योम *addr) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम __kfence_मुक्त(व्योम *addr) अणु पूर्ण
अटल अंतरभूत bool __must_check kfence_मुक्त(व्योम *addr) अणु वापस false; पूर्ण
अटल अंतरभूत bool __must_check kfence_handle_page_fault(अचिन्हित दीर्घ addr, bool is_ग_लिखो,
							 काष्ठा pt_regs *regs)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_KFENCE_H */

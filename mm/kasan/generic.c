<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains core generic KASAN code.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 *
 * Some code borrowed from https://github.com/xairy/kasan-prototype by
 *        Andrey Konovalov <andreyknvl@gmail.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kfence.h>
#समावेश <linux/kmemleak.h>
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
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/bug.h>

#समावेश "kasan.h"
#समावेश "../slab.h"

/*
 * All functions below always अंतरभूतd so compiler could
 * perक्रमm better optimizations in each of __asan_loadX/__assn_storeX
 * depending on memory access size X.
 */

अटल __always_अंतरभूत bool memory_is_poisoned_1(अचिन्हित दीर्घ addr)
अणु
	s8 shaकरोw_value = *(s8 *)kasan_mem_to_shaकरोw((व्योम *)addr);

	अगर (unlikely(shaकरोw_value)) अणु
		s8 last_accessible_byte = addr & KASAN_GRANULE_MASK;
		वापस unlikely(last_accessible_byte >= shaकरोw_value);
	पूर्ण

	वापस false;
पूर्ण

अटल __always_अंतरभूत bool memory_is_poisoned_2_4_8(अचिन्हित दीर्घ addr,
						अचिन्हित दीर्घ size)
अणु
	u8 *shaकरोw_addr = (u8 *)kasan_mem_to_shaकरोw((व्योम *)addr);

	/*
	 * Access crosses 8(shaकरोw size)-byte boundary. Such access maps
	 * पूर्णांकo 2 shaकरोw bytes, so we need to check them both.
	 */
	अगर (unlikely(((addr + size - 1) & KASAN_GRANULE_MASK) < size - 1))
		वापस *shaकरोw_addr || memory_is_poisoned_1(addr + size - 1);

	वापस memory_is_poisoned_1(addr + size - 1);
पूर्ण

अटल __always_अंतरभूत bool memory_is_poisoned_16(अचिन्हित दीर्घ addr)
अणु
	u16 *shaकरोw_addr = (u16 *)kasan_mem_to_shaकरोw((व्योम *)addr);

	/* Unaligned 16-bytes access maps पूर्णांकo 3 shaकरोw bytes. */
	अगर (unlikely(!IS_ALIGNED(addr, KASAN_GRANULE_SIZE)))
		वापस *shaकरोw_addr || memory_is_poisoned_1(addr + 15);

	वापस *shaकरोw_addr;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ bytes_is_nonzero(स्थिर u8 *start,
					माप_प्रकार size)
अणु
	जबतक (size) अणु
		अगर (unlikely(*start))
			वापस (अचिन्हित दीर्घ)start;
		start++;
		size--;
	पूर्ण

	वापस 0;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ memory_is_nonzero(स्थिर व्योम *start,
						स्थिर व्योम *end)
अणु
	अचिन्हित पूर्णांक words;
	अचिन्हित दीर्घ ret;
	अचिन्हित पूर्णांक prefix = (अचिन्हित दीर्घ)start % 8;

	अगर (end - start <= 16)
		वापस bytes_is_nonzero(start, end - start);

	अगर (prefix) अणु
		prefix = 8 - prefix;
		ret = bytes_is_nonzero(start, prefix);
		अगर (unlikely(ret))
			वापस ret;
		start += prefix;
	पूर्ण

	words = (end - start) / 8;
	जबतक (words) अणु
		अगर (unlikely(*(u64 *)start))
			वापस bytes_is_nonzero(start, 8);
		start += 8;
		words--;
	पूर्ण

	वापस bytes_is_nonzero(start, (end - start) % 8);
पूर्ण

अटल __always_अंतरभूत bool memory_is_poisoned_n(अचिन्हित दीर्घ addr,
						माप_प्रकार size)
अणु
	अचिन्हित दीर्घ ret;

	ret = memory_is_nonzero(kasan_mem_to_shaकरोw((व्योम *)addr),
			kasan_mem_to_shaकरोw((व्योम *)addr + size - 1) + 1);

	अगर (unlikely(ret)) अणु
		अचिन्हित दीर्घ last_byte = addr + size - 1;
		s8 *last_shaकरोw = (s8 *)kasan_mem_to_shaकरोw((व्योम *)last_byte);

		अगर (unlikely(ret != (अचिन्हित दीर्घ)last_shaकरोw ||
			((दीर्घ)(last_byte & KASAN_GRANULE_MASK) >= *last_shaकरोw)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल __always_अंतरभूत bool memory_is_poisoned(अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	अगर (__builtin_स्थिरant_p(size)) अणु
		चयन (size) अणु
		हाल 1:
			वापस memory_is_poisoned_1(addr);
		हाल 2:
		हाल 4:
		हाल 8:
			वापस memory_is_poisoned_2_4_8(addr, size);
		हाल 16:
			वापस memory_is_poisoned_16(addr);
		शेष:
			BUILD_BUG();
		पूर्ण
	पूर्ण

	वापस memory_is_poisoned_n(addr, size);
पूर्ण

अटल __always_अंतरभूत bool check_region_अंतरभूत(अचिन्हित दीर्घ addr,
						माप_प्रकार size, bool ग_लिखो,
						अचिन्हित दीर्घ ret_ip)
अणु
	अगर (unlikely(size == 0))
		वापस true;

	अगर (unlikely(addr + size < addr))
		वापस !kasan_report(addr, size, ग_लिखो, ret_ip);

	अगर (unlikely((व्योम *)addr <
		kasan_shaकरोw_to_mem((व्योम *)KASAN_SHADOW_START))) अणु
		वापस !kasan_report(addr, size, ग_लिखो, ret_ip);
	पूर्ण

	अगर (likely(!memory_is_poisoned(addr, size)))
		वापस true;

	वापस !kasan_report(addr, size, ग_लिखो, ret_ip);
पूर्ण

bool kasan_check_range(अचिन्हित दीर्घ addr, माप_प्रकार size, bool ग_लिखो,
					अचिन्हित दीर्घ ret_ip)
अणु
	वापस check_region_अंतरभूत(addr, size, ग_लिखो, ret_ip);
पूर्ण

bool kasan_byte_accessible(स्थिर व्योम *addr)
अणु
	s8 shaकरोw_byte = READ_ONCE(*(s8 *)kasan_mem_to_shaकरोw(addr));

	वापस shaकरोw_byte >= 0 && shaकरोw_byte < KASAN_GRANULE_SIZE;
पूर्ण

व्योम kasan_cache_shrink(काष्ठा kmem_cache *cache)
अणु
	kasan_quarantine_हटाओ_cache(cache);
पूर्ण

व्योम kasan_cache_shutकरोwn(काष्ठा kmem_cache *cache)
अणु
	अगर (!__kmem_cache_empty(cache))
		kasan_quarantine_हटाओ_cache(cache);
पूर्ण

अटल व्योम रेजिस्टर_global(काष्ठा kasan_global *global)
अणु
	माप_प्रकार aligned_size = round_up(global->size, KASAN_GRANULE_SIZE);

	kasan_unpoison(global->beg, global->size, false);

	kasan_poison(global->beg + aligned_size,
		     global->size_with_redzone - aligned_size,
		     KASAN_GLOBAL_REDZONE, false);
पूर्ण

व्योम __asan_रेजिस्टर_globals(काष्ठा kasan_global *globals, माप_प्रकार size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		रेजिस्टर_global(&globals[i]);
पूर्ण
EXPORT_SYMBOL(__asan_रेजिस्टर_globals);

व्योम __asan_unरेजिस्टर_globals(काष्ठा kasan_global *globals, माप_प्रकार size)
अणु
पूर्ण
EXPORT_SYMBOL(__asan_unरेजिस्टर_globals);

#घोषणा DEFINE_ASAN_LOAD_STORE(size)					\
	व्योम __asan_load##size(अचिन्हित दीर्घ addr)			\
	अणु								\
		check_region_अंतरभूत(addr, size, false, _RET_IP_);	\
	पूर्ण								\
	EXPORT_SYMBOL(__asan_load##size);				\
	__alias(__asan_load##size)					\
	व्योम __asan_load##size##_noपात(अचिन्हित दीर्घ);		\
	EXPORT_SYMBOL(__asan_load##size##_noपात);			\
	व्योम __asan_store##size(अचिन्हित दीर्घ addr)			\
	अणु								\
		check_region_अंतरभूत(addr, size, true, _RET_IP_);	\
	पूर्ण								\
	EXPORT_SYMBOL(__asan_store##size);				\
	__alias(__asan_store##size)					\
	व्योम __asan_store##size##_noपात(अचिन्हित दीर्घ);		\
	EXPORT_SYMBOL(__asan_store##size##_noपात)

DEFINE_ASAN_LOAD_STORE(1);
DEFINE_ASAN_LOAD_STORE(2);
DEFINE_ASAN_LOAD_STORE(4);
DEFINE_ASAN_LOAD_STORE(8);
DEFINE_ASAN_LOAD_STORE(16);

व्योम __asan_loadN(अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	kasan_check_range(addr, size, false, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__asan_loadN);

__alias(__asan_loadN)
व्योम __asan_loadN_noपात(अचिन्हित दीर्घ, माप_प्रकार);
EXPORT_SYMBOL(__asan_loadN_noपात);

व्योम __asan_storeN(अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	kasan_check_range(addr, size, true, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__asan_storeN);

__alias(__asan_storeN)
व्योम __asan_storeN_noपात(अचिन्हित दीर्घ, माप_प्रकार);
EXPORT_SYMBOL(__asan_storeN_noपात);

/* to shut up compiler complaपूर्णांकs */
व्योम __asan_handle_no_वापस(व्योम) अणुपूर्ण
EXPORT_SYMBOL(__asan_handle_no_वापस);

/* Emitted by compiler to poison alloca()ed objects. */
व्योम __asan_alloca_poison(अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	माप_प्रकार rounded_up_size = round_up(size, KASAN_GRANULE_SIZE);
	माप_प्रकार padding_size = round_up(size, KASAN_ALLOCA_REDZONE_SIZE) -
			rounded_up_size;
	माप_प्रकार rounded_करोwn_size = round_करोwn(size, KASAN_GRANULE_SIZE);

	स्थिर व्योम *left_redzone = (स्थिर व्योम *)(addr -
			KASAN_ALLOCA_REDZONE_SIZE);
	स्थिर व्योम *right_redzone = (स्थिर व्योम *)(addr + rounded_up_size);

	WARN_ON(!IS_ALIGNED(addr, KASAN_ALLOCA_REDZONE_SIZE));

	kasan_unpoison((स्थिर व्योम *)(addr + rounded_करोwn_size),
			size - rounded_करोwn_size, false);
	kasan_poison(left_redzone, KASAN_ALLOCA_REDZONE_SIZE,
		     KASAN_ALLOCA_LEFT, false);
	kasan_poison(right_redzone, padding_size + KASAN_ALLOCA_REDZONE_SIZE,
		     KASAN_ALLOCA_RIGHT, false);
पूर्ण
EXPORT_SYMBOL(__asan_alloca_poison);

/* Emitted by compiler to unpoison alloca()ed areas when the stack unwinds. */
व्योम __asan_allocas_unpoison(स्थिर व्योम *stack_top, स्थिर व्योम *stack_bottom)
अणु
	अगर (unlikely(!stack_top || stack_top > stack_bottom))
		वापस;

	kasan_unpoison(stack_top, stack_bottom - stack_top, false);
पूर्ण
EXPORT_SYMBOL(__asan_allocas_unpoison);

/* Emitted by the compiler to [un]poison local variables. */
#घोषणा DEFINE_ASAN_SET_SHADOW(byte) \
	व्योम __asan_set_shaकरोw_##byte(स्थिर व्योम *addr, माप_प्रकार size)	\
	अणु								\
		__स_रखो((व्योम *)addr, 0x##byte, size);			\
	पूर्ण								\
	EXPORT_SYMBOL(__asan_set_shaकरोw_##byte)

DEFINE_ASAN_SET_SHADOW(00);
DEFINE_ASAN_SET_SHADOW(f1);
DEFINE_ASAN_SET_SHADOW(f2);
DEFINE_ASAN_SET_SHADOW(f3);
DEFINE_ASAN_SET_SHADOW(f5);
DEFINE_ASAN_SET_SHADOW(f8);

व्योम kasan_record_aux_stack(व्योम *addr)
अणु
	काष्ठा page *page = kasan_addr_to_page(addr);
	काष्ठा kmem_cache *cache;
	काष्ठा kasan_alloc_meta *alloc_meta;
	व्योम *object;

	अगर (is_kfence_address(addr) || !(page && PageSlab(page)))
		वापस;

	cache = page->slab_cache;
	object = nearest_obj(cache, page, addr);
	alloc_meta = kasan_get_alloc_meta(cache, object);
	अगर (!alloc_meta)
		वापस;

	alloc_meta->aux_stack[1] = alloc_meta->aux_stack[0];
	alloc_meta->aux_stack[0] = kasan_save_stack(GFP_NOWAIT);
पूर्ण

व्योम kasan_set_मुक्त_info(काष्ठा kmem_cache *cache,
				व्योम *object, u8 tag)
अणु
	काष्ठा kasan_मुक्त_meta *मुक्त_meta;

	मुक्त_meta = kasan_get_मुक्त_meta(cache, object);
	अगर (!मुक्त_meta)
		वापस;

	kasan_set_track(&मुक्त_meta->मुक्त_track, GFP_NOWAIT);
	/* The object was मुक्तd and has मुक्त track set. */
	*(u8 *)kasan_mem_to_shaकरोw(object) = KASAN_KMALLOC_FREETRACK;
पूर्ण

काष्ठा kasan_track *kasan_get_मुक्त_track(काष्ठा kmem_cache *cache,
				व्योम *object, u8 tag)
अणु
	अगर (*(u8 *)kasan_mem_to_shaकरोw(object) != KASAN_KMALLOC_FREETRACK)
		वापस शून्य;
	/* Free meta must be present with KASAN_KMALLOC_FREETRACK. */
	वापस &kasan_get_मुक्त_meta(cache, object)->मुक्त_track;
पूर्ण

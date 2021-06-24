<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains core software tag-based KASAN code.
 *
 * Copyright (c) 2018 Google, Inc.
 * Author: Andrey Konovalov <andreyknvl@google.com>
 */

#घोषणा pr_fmt(fmt) "kasan: " fmt

#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/linkage.h>
#समावेश <linux/memblock.h>
#समावेश <linux/memory.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>
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

अटल DEFINE_PER_CPU(u32, prng_state);

व्योम __init kasan_init_sw_tags(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		per_cpu(prng_state, cpu) = (u32)get_cycles();

	pr_info("KernelAddressSanitizer initialized\n");
पूर्ण

/*
 * If a preemption happens between this_cpu_पढ़ो and this_cpu_ग_लिखो, the only
 * side effect is that we'll give a few allocated in dअगरferent contexts objects
 * the same tag. Since tag-based KASAN is meant to be used a probabilistic
 * bug-detection debug feature, this करोesn't have signअगरicant negative impact.
 *
 * Ideally the tags use strong अक्रमomness to prevent any attempts to predict
 * them during explicit exploit attempts. But strong अक्रमomness is expensive,
 * and we did an पूर्णांकentional trade-off to use a PRNG. This non-atomic RMW
 * sequence has in fact positive effect, since पूर्णांकerrupts that अक्रमomly skew
 * PRNG at unpredictable poपूर्णांकs करो only good.
 */
u8 kasan_अक्रमom_tag(व्योम)
अणु
	u32 state = this_cpu_पढ़ो(prng_state);

	state = 1664525 * state + 1013904223;
	this_cpu_ग_लिखो(prng_state, state);

	वापस (u8)(state % (KASAN_TAG_MAX + 1));
पूर्ण

bool kasan_check_range(अचिन्हित दीर्घ addr, माप_प्रकार size, bool ग_लिखो,
				अचिन्हित दीर्घ ret_ip)
अणु
	u8 tag;
	u8 *shaकरोw_first, *shaकरोw_last, *shaकरोw;
	व्योम *untagged_addr;

	अगर (unlikely(size == 0))
		वापस true;

	अगर (unlikely(addr + size < addr))
		वापस !kasan_report(addr, size, ग_लिखो, ret_ip);

	tag = get_tag((स्थिर व्योम *)addr);

	/*
	 * Ignore accesses क्रम poपूर्णांकers tagged with 0xff (native kernel
	 * poपूर्णांकer tag) to suppress false positives caused by kmap.
	 *
	 * Some kernel code was written to account क्रम archs that करोn't keep
	 * high memory mapped all the समय, but rather map and unmap particular
	 * pages when needed. Instead of storing a poपूर्णांकer to the kernel memory,
	 * this code saves the address of the page काष्ठाure and offset within
	 * that page क्रम later use. Those pages are then mapped and unmapped
	 * with kmap/kunmap when necessary and virt_to_page is used to get the
	 * भव address of the page. For arm64 (that keeps the high memory
	 * mapped all the समय), kmap is turned पूर्णांकo a page_address call.

	 * The issue is that with use of the page_address + virt_to_page
	 * sequence the top byte value of the original poपूर्णांकer माला_लो lost (माला_लो
	 * set to KASAN_TAG_KERNEL (0xFF)).
	 */
	अगर (tag == KASAN_TAG_KERNEL)
		वापस true;

	untagged_addr = kasan_reset_tag((स्थिर व्योम *)addr);
	अगर (unlikely(untagged_addr <
			kasan_shaकरोw_to_mem((व्योम *)KASAN_SHADOW_START))) अणु
		वापस !kasan_report(addr, size, ग_लिखो, ret_ip);
	पूर्ण
	shaकरोw_first = kasan_mem_to_shaकरोw(untagged_addr);
	shaकरोw_last = kasan_mem_to_shaकरोw(untagged_addr + size - 1);
	क्रम (shaकरोw = shaकरोw_first; shaकरोw <= shaकरोw_last; shaकरोw++) अणु
		अगर (*shaकरोw != tag) अणु
			वापस !kasan_report(addr, size, ग_लिखो, ret_ip);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

bool kasan_byte_accessible(स्थिर व्योम *addr)
अणु
	u8 tag = get_tag(addr);
	व्योम *untagged_addr = kasan_reset_tag(addr);
	u8 shaकरोw_byte;

	अगर (untagged_addr < kasan_shaकरोw_to_mem((व्योम *)KASAN_SHADOW_START))
		वापस false;

	shaकरोw_byte = READ_ONCE(*(u8 *)kasan_mem_to_shaकरोw(untagged_addr));
	वापस tag == KASAN_TAG_KERNEL || tag == shaकरोw_byte;
पूर्ण

#घोषणा DEFINE_HWASAN_LOAD_STORE(size)					\
	व्योम __hwasan_load##size##_noपात(अचिन्हित दीर्घ addr)		\
	अणु								\
		kasan_check_range(addr, size, false, _RET_IP_);	\
	पूर्ण								\
	EXPORT_SYMBOL(__hwasan_load##size##_noपात);			\
	व्योम __hwasan_store##size##_noपात(अचिन्हित दीर्घ addr)		\
	अणु								\
		kasan_check_range(addr, size, true, _RET_IP_);		\
	पूर्ण								\
	EXPORT_SYMBOL(__hwasan_store##size##_noपात)

DEFINE_HWASAN_LOAD_STORE(1);
DEFINE_HWASAN_LOAD_STORE(2);
DEFINE_HWASAN_LOAD_STORE(4);
DEFINE_HWASAN_LOAD_STORE(8);
DEFINE_HWASAN_LOAD_STORE(16);

व्योम __hwasan_loadN_noपात(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	kasan_check_range(addr, size, false, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__hwasan_loadN_noपात);

व्योम __hwasan_storeN_noपात(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	kasan_check_range(addr, size, true, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__hwasan_storeN_noपात);

व्योम __hwasan_tag_memory(अचिन्हित दीर्घ addr, u8 tag, अचिन्हित दीर्घ size)
अणु
	kasan_poison((व्योम *)addr, size, tag, false);
पूर्ण
EXPORT_SYMBOL(__hwasan_tag_memory);

व्योम kasan_set_मुक्त_info(काष्ठा kmem_cache *cache,
				व्योम *object, u8 tag)
अणु
	काष्ठा kasan_alloc_meta *alloc_meta;
	u8 idx = 0;

	alloc_meta = kasan_get_alloc_meta(cache, object);
	अगर (!alloc_meta)
		वापस;

#अगर_घोषित CONFIG_KASAN_SW_TAGS_IDENTIFY
	idx = alloc_meta->मुक्त_track_idx;
	alloc_meta->मुक्त_poपूर्णांकer_tag[idx] = tag;
	alloc_meta->मुक्त_track_idx = (idx + 1) % KASAN_NR_FREE_STACKS;
#पूर्ण_अगर

	kasan_set_track(&alloc_meta->मुक्त_track[idx], GFP_NOWAIT);
पूर्ण

काष्ठा kasan_track *kasan_get_मुक्त_track(काष्ठा kmem_cache *cache,
				व्योम *object, u8 tag)
अणु
	काष्ठा kasan_alloc_meta *alloc_meta;
	पूर्णांक i = 0;

	alloc_meta = kasan_get_alloc_meta(cache, object);
	अगर (!alloc_meta)
		वापस शून्य;

#अगर_घोषित CONFIG_KASAN_SW_TAGS_IDENTIFY
	क्रम (i = 0; i < KASAN_NR_FREE_STACKS; i++) अणु
		अगर (alloc_meta->मुक्त_poपूर्णांकer_tag[i] == tag)
			अवरोध;
	पूर्ण
	अगर (i == KASAN_NR_FREE_STACKS)
		i = alloc_meta->मुक्त_track_idx;
#पूर्ण_अगर

	वापस &alloc_meta->मुक्त_track[i];
पूर्ण

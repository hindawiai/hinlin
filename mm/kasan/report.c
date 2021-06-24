<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains common KASAN error reporting code.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 *
 * Some code borrowed from https://github.com/xairy/kasan-prototype by
 *        Andrey Konovalov <andreyknvl@gmail.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/stackdepot.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/kasan.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/uaccess.h>
#समावेश <trace/events/error_report.h>

#समावेश <यंत्र/sections.h>

#समावेश <kunit/test.h>

#समावेश "kasan.h"
#समावेश "../slab.h"

अटल अचिन्हित दीर्घ kasan_flags;

#घोषणा KASAN_BIT_REPORTED	0
#घोषणा KASAN_BIT_MULTI_SHOT	1

bool kasan_save_enable_multi_shot(व्योम)
अणु
	वापस test_and_set_bit(KASAN_BIT_MULTI_SHOT, &kasan_flags);
पूर्ण
EXPORT_SYMBOL_GPL(kasan_save_enable_multi_shot);

व्योम kasan_restore_multi_shot(bool enabled)
अणु
	अगर (!enabled)
		clear_bit(KASAN_BIT_MULTI_SHOT, &kasan_flags);
पूर्ण
EXPORT_SYMBOL_GPL(kasan_restore_multi_shot);

अटल पूर्णांक __init kasan_set_multi_shot(अक्षर *str)
अणु
	set_bit(KASAN_BIT_MULTI_SHOT, &kasan_flags);
	वापस 1;
पूर्ण
__setup("kasan_multi_shot", kasan_set_multi_shot);

अटल व्योम prपूर्णांक_error_description(काष्ठा kasan_access_info *info)
अणु
	pr_err("BUG: KASAN: %s in %pS\n",
		kasan_get_bug_type(info), (व्योम *)info->ip);
	अगर (info->access_size)
		pr_err("%s of size %zu at addr %px by task %s/%d\n",
			info->is_ग_लिखो ? "Write" : "Read", info->access_size,
			info->access_addr, current->comm, task_pid_nr(current));
	अन्यथा
		pr_err("%s at addr %px by task %s/%d\n",
			info->is_ग_लिखो ? "Write" : "Read",
			info->access_addr, current->comm, task_pid_nr(current));
पूर्ण

अटल DEFINE_SPINLOCK(report_lock);

अटल व्योम start_report(अचिन्हित दीर्घ *flags)
अणु
	/*
	 * Make sure we करोn't end up in loop.
	 */
	kasan_disable_current();
	spin_lock_irqsave(&report_lock, *flags);
	pr_err("==================================================================\n");
पूर्ण

अटल व्योम end_report(अचिन्हित दीर्घ *flags, अचिन्हित दीर्घ addr)
अणु
	अगर (!kasan_async_mode_enabled())
		trace_error_report_end(ERROR_DETECTOR_KASAN, addr);
	pr_err("==================================================================\n");
	add_taपूर्णांक(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irqrestore(&report_lock, *flags);
	अगर (panic_on_warn && !test_bit(KASAN_BIT_MULTI_SHOT, &kasan_flags)) अणु
		/*
		 * This thपढ़ो may hit another WARN() in the panic path.
		 * Resetting this prevents additional WARN() from panicking the
		 * प्रणाली on this thपढ़ो.  Other thपढ़ोs are blocked by the
		 * panic_mutex in panic().
		 */
		panic_on_warn = 0;
		panic("panic_on_warn set ...\n");
	पूर्ण
#अगर_घोषित CONFIG_KASAN_HW_TAGS
	अगर (kasan_flag_panic)
		panic("kasan.fault=panic set ...\n");
#पूर्ण_अगर
	kasan_enable_current();
पूर्ण

अटल व्योम prपूर्णांक_stack(depot_stack_handle_t stack)
अणु
	अचिन्हित दीर्घ *entries;
	अचिन्हित पूर्णांक nr_entries;

	nr_entries = stack_depot_fetch(stack, &entries);
	stack_trace_prपूर्णांक(entries, nr_entries, 0);
पूर्ण

अटल व्योम prपूर्णांक_track(काष्ठा kasan_track *track, स्थिर अक्षर *prefix)
अणु
	pr_err("%s by task %u:\n", prefix, track->pid);
	अगर (track->stack) अणु
		prपूर्णांक_stack(track->stack);
	पूर्ण अन्यथा अणु
		pr_err("(stack is not available)\n");
	पूर्ण
पूर्ण

काष्ठा page *kasan_addr_to_page(स्थिर व्योम *addr)
अणु
	अगर ((addr >= (व्योम *)PAGE_OFFSET) &&
			(addr < high_memory))
		वापस virt_to_head_page(addr);
	वापस शून्य;
पूर्ण

अटल व्योम describe_object_addr(काष्ठा kmem_cache *cache, व्योम *object,
				स्थिर व्योम *addr)
अणु
	अचिन्हित दीर्घ access_addr = (अचिन्हित दीर्घ)addr;
	अचिन्हित दीर्घ object_addr = (अचिन्हित दीर्घ)object;
	स्थिर अक्षर *rel_type;
	पूर्णांक rel_bytes;

	pr_err("The buggy address belongs to the object at %px\n"
	       " which belongs to the cache %s of size %d\n",
		object, cache->name, cache->object_size);

	अगर (!addr)
		वापस;

	अगर (access_addr < object_addr) अणु
		rel_type = "to the left";
		rel_bytes = object_addr - access_addr;
	पूर्ण अन्यथा अगर (access_addr >= object_addr + cache->object_size) अणु
		rel_type = "to the right";
		rel_bytes = access_addr - (object_addr + cache->object_size);
	पूर्ण अन्यथा अणु
		rel_type = "inside";
		rel_bytes = access_addr - object_addr;
	पूर्ण

	pr_err("The buggy address is located %d bytes %s of\n"
	       " %d-byte region [%px, %px)\n",
		rel_bytes, rel_type, cache->object_size, (व्योम *)object_addr,
		(व्योम *)(object_addr + cache->object_size));
पूर्ण

अटल व्योम describe_object_stacks(काष्ठा kmem_cache *cache, व्योम *object,
					स्थिर व्योम *addr, u8 tag)
अणु
	काष्ठा kasan_alloc_meta *alloc_meta;
	काष्ठा kasan_track *मुक्त_track;

	alloc_meta = kasan_get_alloc_meta(cache, object);
	अगर (alloc_meta) अणु
		prपूर्णांक_track(&alloc_meta->alloc_track, "Allocated");
		pr_err("\n");
	पूर्ण

	मुक्त_track = kasan_get_मुक्त_track(cache, object, tag);
	अगर (मुक्त_track) अणु
		prपूर्णांक_track(मुक्त_track, "Freed");
		pr_err("\n");
	पूर्ण

#अगर_घोषित CONFIG_KASAN_GENERIC
	अगर (!alloc_meta)
		वापस;
	अगर (alloc_meta->aux_stack[0]) अणु
		pr_err("Last potentially related work creation:\n");
		prपूर्णांक_stack(alloc_meta->aux_stack[0]);
		pr_err("\n");
	पूर्ण
	अगर (alloc_meta->aux_stack[1]) अणु
		pr_err("Second to last potentially related work creation:\n");
		prपूर्णांक_stack(alloc_meta->aux_stack[1]);
		pr_err("\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम describe_object(काष्ठा kmem_cache *cache, व्योम *object,
				स्थिर व्योम *addr, u8 tag)
अणु
	अगर (kasan_stack_collection_enabled())
		describe_object_stacks(cache, object, addr, tag);
	describe_object_addr(cache, object, addr);
पूर्ण

अटल अंतरभूत bool kernel_or_module_addr(स्थिर व्योम *addr)
अणु
	अगर (addr >= (व्योम *)_stext && addr < (व्योम *)_end)
		वापस true;
	अगर (is_module_address((अचिन्हित दीर्घ)addr))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool init_task_stack_addr(स्थिर व्योम *addr)
अणु
	वापस addr >= (व्योम *)&init_thपढ़ो_जोड़.stack &&
		(addr <= (व्योम *)&init_thपढ़ो_जोड़.stack +
			माप(init_thपढ़ो_जोड़.stack));
पूर्ण

अटल व्योम prपूर्णांक_address_description(व्योम *addr, u8 tag)
अणु
	काष्ठा page *page = kasan_addr_to_page(addr);

	dump_stack();
	pr_err("\n");

	अगर (page && PageSlab(page)) अणु
		काष्ठा kmem_cache *cache = page->slab_cache;
		व्योम *object = nearest_obj(cache, page,	addr);

		describe_object(cache, object, addr, tag);
	पूर्ण

	अगर (kernel_or_module_addr(addr) && !init_task_stack_addr(addr)) अणु
		pr_err("The buggy address belongs to the variable:\n");
		pr_err(" %pS\n", addr);
	पूर्ण

	अगर (page) अणु
		pr_err("The buggy address belongs to the page:\n");
		dump_page(page, "kasan: bad access detected");
	पूर्ण

	kasan_prपूर्णांक_address_stack_frame(addr);
पूर्ण

अटल bool meta_row_is_guilty(स्थिर व्योम *row, स्थिर व्योम *addr)
अणु
	वापस (row <= addr) && (addr < row + META_MEM_BYTES_PER_ROW);
पूर्ण

अटल पूर्णांक meta_poपूर्णांकer_offset(स्थिर व्योम *row, स्थिर व्योम *addr)
अणु
	/*
	 * Memory state around the buggy address:
	 *  ff00ff00ff00ff00: 00 00 00 05 fe fe fe fe fe fe fe fe fe fe fe fe
	 *  ...
	 *
	 * The length of ">ff00ff00ff00ff00: " is
	 *    3 + (BITS_PER_LONG / 8) * 2 अक्षरs.
	 * The length of each granule metadata is 2 bytes
	 *    plus 1 byte क्रम space.
	 */
	वापस 3 + (BITS_PER_LONG / 8) * 2 +
		(addr - row) / KASAN_GRANULE_SIZE * 3 + 1;
पूर्ण

अटल व्योम prपूर्णांक_memory_metadata(स्थिर व्योम *addr)
अणु
	पूर्णांक i;
	व्योम *row;

	row = (व्योम *)round_करोwn((अचिन्हित दीर्घ)addr, META_MEM_BYTES_PER_ROW)
			- META_ROWS_AROUND_ADDR * META_MEM_BYTES_PER_ROW;

	pr_err("Memory state around the buggy address:\n");

	क्रम (i = -META_ROWS_AROUND_ADDR; i <= META_ROWS_AROUND_ADDR; i++) अणु
		अक्षर buffer[4 + (BITS_PER_LONG / 8) * 2];
		अक्षर metadata[META_BYTES_PER_ROW];

		snम_लिखो(buffer, माप(buffer),
				(i == 0) ? ">%px: " : " %px: ", row);

		/*
		 * We should not pass a shaकरोw poपूर्णांकer to generic
		 * function, because generic functions may try to
		 * access kasan mapping क्रम the passed address.
		 */
		kasan_metadata_fetch_row(&metadata[0], row);

		prपूर्णांक_hex_dump(KERN_ERR, buffer,
			DUMP_PREFIX_NONE, META_BYTES_PER_ROW, 1,
			metadata, META_BYTES_PER_ROW, 0);

		अगर (meta_row_is_guilty(row, addr))
			pr_err("%*c\n", meta_poपूर्णांकer_offset(row, addr), '^');

		row += META_MEM_BYTES_PER_ROW;
	पूर्ण
पूर्ण

अटल bool report_enabled(व्योम)
अणु
#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
	अगर (current->kasan_depth)
		वापस false;
#पूर्ण_अगर
	अगर (test_bit(KASAN_BIT_MULTI_SHOT, &kasan_flags))
		वापस true;
	वापस !test_and_set_bit(KASAN_BIT_REPORTED, &kasan_flags);
पूर्ण

#अगर IS_ENABLED(CONFIG_KUNIT)
अटल व्योम kasan_update_kunit_status(काष्ठा kunit *cur_test)
अणु
	काष्ठा kunit_resource *resource;
	काष्ठा kunit_kasan_expectation *kasan_data;

	resource = kunit_find_named_resource(cur_test, "kasan_data");

	अगर (!resource) अणु
		kunit_set_failure(cur_test);
		वापस;
	पूर्ण

	kasan_data = (काष्ठा kunit_kasan_expectation *)resource->data;
	WRITE_ONCE(kasan_data->report_found, true);
	kunit_put_resource(resource);
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_KUNIT) */

व्योम kasan_report_invalid_मुक्त(व्योम *object, अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags;
	u8 tag = get_tag(object);

	object = kasan_reset_tag(object);

#अगर IS_ENABLED(CONFIG_KUNIT)
	अगर (current->kunit_test)
		kasan_update_kunit_status(current->kunit_test);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_KUNIT) */

	start_report(&flags);
	pr_err("BUG: KASAN: double-free or invalid-free in %pS\n", (व्योम *)ip);
	kasan_prपूर्णांक_tags(tag, object);
	pr_err("\n");
	prपूर्णांक_address_description(object, tag);
	pr_err("\n");
	prपूर्णांक_memory_metadata(object);
	end_report(&flags, (अचिन्हित दीर्घ)object);
पूर्ण

#अगर_घोषित CONFIG_KASAN_HW_TAGS
व्योम kasan_report_async(व्योम)
अणु
	अचिन्हित दीर्घ flags;

#अगर IS_ENABLED(CONFIG_KUNIT)
	अगर (current->kunit_test)
		kasan_update_kunit_status(current->kunit_test);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_KUNIT) */

	start_report(&flags);
	pr_err("BUG: KASAN: invalid-access\n");
	pr_err("Asynchronous mode enabled: no access details available\n");
	pr_err("\n");
	dump_stack();
	end_report(&flags, 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_KASAN_HW_TAGS */

अटल व्योम __kasan_report(अचिन्हित दीर्घ addr, माप_प्रकार size, bool is_ग_लिखो,
				अचिन्हित दीर्घ ip)
अणु
	काष्ठा kasan_access_info info;
	व्योम *tagged_addr;
	व्योम *untagged_addr;
	अचिन्हित दीर्घ flags;

#अगर IS_ENABLED(CONFIG_KUNIT)
	अगर (current->kunit_test)
		kasan_update_kunit_status(current->kunit_test);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_KUNIT) */

	disable_trace_on_warning();

	tagged_addr = (व्योम *)addr;
	untagged_addr = kasan_reset_tag(tagged_addr);

	info.access_addr = tagged_addr;
	अगर (addr_has_metadata(untagged_addr))
		info.first_bad_addr =
			kasan_find_first_bad_addr(tagged_addr, size);
	अन्यथा
		info.first_bad_addr = untagged_addr;
	info.access_size = size;
	info.is_ग_लिखो = is_ग_लिखो;
	info.ip = ip;

	start_report(&flags);

	prपूर्णांक_error_description(&info);
	अगर (addr_has_metadata(untagged_addr))
		kasan_prपूर्णांक_tags(get_tag(tagged_addr), info.first_bad_addr);
	pr_err("\n");

	अगर (addr_has_metadata(untagged_addr)) अणु
		prपूर्णांक_address_description(untagged_addr, get_tag(tagged_addr));
		pr_err("\n");
		prपूर्णांक_memory_metadata(info.first_bad_addr);
	पूर्ण अन्यथा अणु
		dump_stack();
	पूर्ण

	end_report(&flags, addr);
पूर्ण

bool kasan_report(अचिन्हित दीर्घ addr, माप_प्रकार size, bool is_ग_लिखो,
			अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags = user_access_save();
	bool ret = false;

	अगर (likely(report_enabled())) अणु
		__kasan_report(addr, size, is_ग_लिखो, ip);
		ret = true;
	पूर्ण

	user_access_restore(flags);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_KASAN_INLINE
/*
 * With CONFIG_KASAN_INLINE, accesses to bogus poपूर्णांकers (outside the high
 * canonical half of the address space) cause out-of-bounds shaकरोw memory पढ़ोs
 * beक्रमe the actual access. For addresses in the low canonical half of the
 * address space, as well as most non-canonical addresses, that out-of-bounds
 * shaकरोw memory access lands in the non-canonical part of the address space.
 * Help the user figure out what the original bogus poपूर्णांकer was.
 */
व्योम kasan_non_canonical_hook(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ orig_addr;
	स्थिर अक्षर *bug_type;

	अगर (addr < KASAN_SHADOW_OFFSET)
		वापस;

	orig_addr = (addr - KASAN_SHADOW_OFFSET) << KASAN_SHADOW_SCALE_SHIFT;
	/*
	 * For faults near the shaकरोw address क्रम शून्य, we can be fairly certain
	 * that this is a KASAN shaकरोw memory access.
	 * For faults that correspond to shaकरोw क्रम low canonical addresses, we
	 * can still be pretty sure - that shaकरोw region is a fairly narrow
	 * chunk of the non-canonical address space.
	 * But faults that look like shaकरोw क्रम non-canonical addresses are a
	 * really large chunk of the address space. In that हाल, we still
	 * prपूर्णांक the decoded address, but make it clear that this is not
	 * necessarily what's actually going on.
	 */
	अगर (orig_addr < PAGE_SIZE)
		bug_type = "null-ptr-deref";
	अन्यथा अगर (orig_addr < TASK_SIZE)
		bug_type = "probably user-memory-access";
	अन्यथा
		bug_type = "maybe wild-memory-access";
	pr_alert("KASAN: %s in range [0x%016lx-0x%016lx]\n", bug_type,
		 orig_addr, orig_addr + KASAN_GRANULE_SIZE - 1);
पूर्ण
#पूर्ण_अगर

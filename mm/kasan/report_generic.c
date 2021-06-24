<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains generic KASAN specअगरic error reporting code.
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
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/slab.h>
#समावेश <linux/stackdepot.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/kasan.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/sections.h>

#समावेश "kasan.h"
#समावेश "../slab.h"

व्योम *kasan_find_first_bad_addr(व्योम *addr, माप_प्रकार size)
अणु
	व्योम *p = addr;

	जबतक (p < addr + size && !(*(u8 *)kasan_mem_to_shaकरोw(p)))
		p += KASAN_GRANULE_SIZE;
	वापस p;
पूर्ण

अटल स्थिर अक्षर *get_shaकरोw_bug_type(काष्ठा kasan_access_info *info)
अणु
	स्थिर अक्षर *bug_type = "unknown-crash";
	u8 *shaकरोw_addr;

	shaकरोw_addr = (u8 *)kasan_mem_to_shaकरोw(info->first_bad_addr);

	/*
	 * If shaकरोw byte value is in [0, KASAN_GRANULE_SIZE) we can look
	 * at the next shaकरोw byte to determine the type of the bad access.
	 */
	अगर (*shaकरोw_addr > 0 && *shaकरोw_addr <= KASAN_GRANULE_SIZE - 1)
		shaकरोw_addr++;

	चयन (*shaकरोw_addr) अणु
	हाल 0 ... KASAN_GRANULE_SIZE - 1:
		/*
		 * In theory it's still possible to see these shaकरोw values
		 * due to a data race in the kernel code.
		 */
		bug_type = "out-of-bounds";
		अवरोध;
	हाल KASAN_PAGE_REDZONE:
	हाल KASAN_KMALLOC_REDZONE:
		bug_type = "slab-out-of-bounds";
		अवरोध;
	हाल KASAN_GLOBAL_REDZONE:
		bug_type = "global-out-of-bounds";
		अवरोध;
	हाल KASAN_STACK_LEFT:
	हाल KASAN_STACK_MID:
	हाल KASAN_STACK_RIGHT:
	हाल KASAN_STACK_PARTIAL:
		bug_type = "stack-out-of-bounds";
		अवरोध;
	हाल KASAN_FREE_PAGE:
	हाल KASAN_KMALLOC_FREE:
	हाल KASAN_KMALLOC_FREETRACK:
		bug_type = "use-after-free";
		अवरोध;
	हाल KASAN_ALLOCA_LEFT:
	हाल KASAN_ALLOCA_RIGHT:
		bug_type = "alloca-out-of-bounds";
		अवरोध;
	हाल KASAN_VMALLOC_INVALID:
		bug_type = "vmalloc-out-of-bounds";
		अवरोध;
	पूर्ण

	वापस bug_type;
पूर्ण

अटल स्थिर अक्षर *get_wild_bug_type(काष्ठा kasan_access_info *info)
अणु
	स्थिर अक्षर *bug_type = "unknown-crash";

	अगर ((अचिन्हित दीर्घ)info->access_addr < PAGE_SIZE)
		bug_type = "null-ptr-deref";
	अन्यथा अगर ((अचिन्हित दीर्घ)info->access_addr < TASK_SIZE)
		bug_type = "user-memory-access";
	अन्यथा
		bug_type = "wild-memory-access";

	वापस bug_type;
पूर्ण

स्थिर अक्षर *kasan_get_bug_type(काष्ठा kasan_access_info *info)
अणु
	/*
	 * If access_size is a negative number, then it has reason to be
	 * defined as out-of-bounds bug type.
	 *
	 * Casting negative numbers to माप_प्रकार would indeed turn up as
	 * a large माप_प्रकार and its value will be larger than अच_दीर्घ_उच्च/2,
	 * so that this can qualअगरy as out-of-bounds.
	 */
	अगर (info->access_addr + info->access_size < info->access_addr)
		वापस "out-of-bounds";

	अगर (addr_has_metadata(info->access_addr))
		वापस get_shaकरोw_bug_type(info);
	वापस get_wild_bug_type(info);
पूर्ण

व्योम kasan_metadata_fetch_row(अक्षर *buffer, व्योम *row)
अणु
	स_नकल(buffer, kasan_mem_to_shaकरोw(row), META_BYTES_PER_ROW);
पूर्ण

#अगर_घोषित CONFIG_KASAN_STACK
अटल bool __must_check tokenize_frame_descr(स्थिर अक्षर **frame_descr,
					      अक्षर *token, माप_प्रकार max_tok_len,
					      अचिन्हित दीर्घ *value)
अणु
	स्थिर अक्षर *sep = म_अक्षर(*frame_descr, ' ');

	अगर (sep == शून्य)
		sep = *frame_descr + म_माप(*frame_descr);

	अगर (token != शून्य) अणु
		स्थिर माप_प्रकार tok_len = sep - *frame_descr;

		अगर (tok_len + 1 > max_tok_len) अणु
			pr_err("KASAN internal error: frame description too long: %s\n",
			       *frame_descr);
			वापस false;
		पूर्ण

		/* Copy token (+ 1 byte क्रम '\0'). */
		strscpy(token, *frame_descr, tok_len + 1);
	पूर्ण

	/* Advance frame_descr past separator. */
	*frame_descr = sep + 1;

	अगर (value != शून्य && kम_से_अदीर्घ(token, 10, value)) अणु
		pr_err("KASAN internal error: not a valid number: %s\n", token);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम prपूर्णांक_decoded_frame_descr(स्थिर अक्षर *frame_descr)
अणु
	/*
	 * We need to parse the following string:
	 *    "n alloc_1 alloc_2 ... alloc_n"
	 * where alloc_i looks like
	 *    "offset size len name"
	 * or "offset size len name:line".
	 */

	अक्षर token[64];
	अचिन्हित दीर्घ num_objects;

	अगर (!tokenize_frame_descr(&frame_descr, token, माप(token),
				  &num_objects))
		वापस;

	pr_err("\n");
	pr_err("this frame has %lu %s:\n", num_objects,
	       num_objects == 1 ? "object" : "objects");

	जबतक (num_objects--) अणु
		अचिन्हित दीर्घ offset;
		अचिन्हित दीर्घ size;

		/* access offset */
		अगर (!tokenize_frame_descr(&frame_descr, token, माप(token),
					  &offset))
			वापस;
		/* access size */
		अगर (!tokenize_frame_descr(&frame_descr, token, माप(token),
					  &size))
			वापस;
		/* name length (unused) */
		अगर (!tokenize_frame_descr(&frame_descr, शून्य, 0, शून्य))
			वापस;
		/* object name */
		अगर (!tokenize_frame_descr(&frame_descr, token, माप(token),
					  शून्य))
			वापस;

		/* Strip line number; without filename it's not very helpful. */
		strreplace(token, ':', '\0');

		/* Finally, prपूर्णांक object inक्रमmation. */
		pr_err(" [%lu, %lu) '%s'", offset, offset + size, token);
	पूर्ण
पूर्ण

अटल bool __must_check get_address_stack_frame_info(स्थिर व्योम *addr,
						      अचिन्हित दीर्घ *offset,
						      स्थिर अक्षर **frame_descr,
						      स्थिर व्योम **frame_pc)
अणु
	अचिन्हित दीर्घ aligned_addr;
	अचिन्हित दीर्घ mem_ptr;
	स्थिर u8 *shaकरोw_bottom;
	स्थिर u8 *shaकरोw_ptr;
	स्थिर अचिन्हित दीर्घ *frame;

	BUILD_BUG_ON(IS_ENABLED(CONFIG_STACK_GROWSUP));

	/*
	 * NOTE: We currently only support prपूर्णांकing frame inक्रमmation क्रम
	 * accesses to the task's own stack.
	 */
	अगर (!object_is_on_stack(addr))
		वापस false;

	aligned_addr = round_करोwn((अचिन्हित दीर्घ)addr, माप(दीर्घ));
	mem_ptr = round_करोwn(aligned_addr, KASAN_GRANULE_SIZE);
	shaकरोw_ptr = kasan_mem_to_shaकरोw((व्योम *)aligned_addr);
	shaकरोw_bottom = kasan_mem_to_shaकरोw(end_of_stack(current));

	जबतक (shaकरोw_ptr >= shaकरोw_bottom && *shaकरोw_ptr != KASAN_STACK_LEFT) अणु
		shaकरोw_ptr--;
		mem_ptr -= KASAN_GRANULE_SIZE;
	पूर्ण

	जबतक (shaकरोw_ptr >= shaकरोw_bottom && *shaकरोw_ptr == KASAN_STACK_LEFT) अणु
		shaकरोw_ptr--;
		mem_ptr -= KASAN_GRANULE_SIZE;
	पूर्ण

	अगर (shaकरोw_ptr < shaकरोw_bottom)
		वापस false;

	frame = (स्थिर अचिन्हित दीर्घ *)(mem_ptr + KASAN_GRANULE_SIZE);
	अगर (frame[0] != KASAN_CURRENT_STACK_FRAME_MAGIC) अणु
		pr_err("KASAN internal error: frame info validation failed; invalid marker: %lu\n",
		       frame[0]);
		वापस false;
	पूर्ण

	*offset = (अचिन्हित दीर्घ)addr - (अचिन्हित दीर्घ)frame;
	*frame_descr = (स्थिर अक्षर *)frame[1];
	*frame_pc = (व्योम *)frame[2];

	वापस true;
पूर्ण

व्योम kasan_prपूर्णांक_address_stack_frame(स्थिर व्योम *addr)
अणु
	अचिन्हित दीर्घ offset;
	स्थिर अक्षर *frame_descr;
	स्थिर व्योम *frame_pc;

	अगर (!get_address_stack_frame_info(addr, &offset, &frame_descr,
					  &frame_pc))
		वापस;

	/*
	 * get_address_stack_frame_info only वापसs true अगर the given addr is
	 * on the current task's stack.
	 */
	pr_err("\n");
	pr_err("addr %px is located in stack of task %s/%d at offset %lu in frame:\n",
	       addr, current->comm, task_pid_nr(current), offset);
	pr_err(" %pS\n", frame_pc);

	अगर (!frame_descr)
		वापस;

	prपूर्णांक_decoded_frame_descr(frame_descr);
पूर्ण
#पूर्ण_अगर /* CONFIG_KASAN_STACK */

#घोषणा DEFINE_ASAN_REPORT_LOAD(size)                     \
व्योम __asan_report_load##size##_noपात(अचिन्हित दीर्घ addr) \
अणु                                                         \
	kasan_report(addr, size, false, _RET_IP_);	  \
पूर्ण                                                         \
EXPORT_SYMBOL(__asan_report_load##size##_noपात)

#घोषणा DEFINE_ASAN_REPORT_STORE(size)                     \
व्योम __asan_report_store##size##_noपात(अचिन्हित दीर्घ addr) \
अणु                                                          \
	kasan_report(addr, size, true, _RET_IP_);	   \
पूर्ण                                                          \
EXPORT_SYMBOL(__asan_report_store##size##_noपात)

DEFINE_ASAN_REPORT_LOAD(1);
DEFINE_ASAN_REPORT_LOAD(2);
DEFINE_ASAN_REPORT_LOAD(4);
DEFINE_ASAN_REPORT_LOAD(8);
DEFINE_ASAN_REPORT_LOAD(16);
DEFINE_ASAN_REPORT_STORE(1);
DEFINE_ASAN_REPORT_STORE(2);
DEFINE_ASAN_REPORT_STORE(4);
DEFINE_ASAN_REPORT_STORE(8);
DEFINE_ASAN_REPORT_STORE(16);

व्योम __asan_report_load_n_noपात(अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	kasan_report(addr, size, false, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__asan_report_load_n_noपात);

व्योम __asan_report_store_n_noपात(अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	kasan_report(addr, size, true, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__asan_report_store_n_noपात);

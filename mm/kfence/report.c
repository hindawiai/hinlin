<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KFENCE reporting.
 *
 * Copyright (C) 2020, Google LLC.
 */

#समावेश <मानकतर्क.स>

#समावेश <linux/kernel.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/माला.स>
#समावेश <trace/events/error_report.h>

#समावेश <यंत्र/kfence.h>

#समावेश "kfence.h"

/* May be overridden by <यंत्र/kfence.h>. */
#अगर_अघोषित ARCH_FUNC_PREFIX
#घोषणा ARCH_FUNC_PREFIX ""
#पूर्ण_अगर

बाह्य bool no_hash_poपूर्णांकers;

/* Helper function to either prपूर्णांक to a seq_file or to console. */
__म_लिखो(2, 3)
अटल व्योम seq_con_म_लिखो(काष्ठा seq_file *seq, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	अगर (seq)
		seq_भ_लिखो(seq, fmt, args);
	अन्यथा
		vprपूर्णांकk(fmt, args);
	बहु_पूर्ण(args);
पूर्ण

/*
 * Get the number of stack entries to skip to get out of MM पूर्णांकernals. @type is
 * optional, and अगर set to शून्य, assumes an allocation or मुक्त stack.
 */
अटल पूर्णांक get_stack_skipnr(स्थिर अचिन्हित दीर्घ stack_entries[], पूर्णांक num_entries,
			    स्थिर क्रमागत kfence_error_type *type)
अणु
	अक्षर buf[64];
	पूर्णांक skipnr, fallback = 0;

	अगर (type) अणु
		/* Depending on error type, find dअगरferent stack entries. */
		चयन (*type) अणु
		हाल KFENCE_ERROR_UAF:
		हाल KFENCE_ERROR_OOB:
		हाल KFENCE_ERROR_INVALID:
			/*
			 * kfence_handle_page_fault() may be called with pt_regs
			 * set to शून्य; in that हाल we'll simply show the full
			 * stack trace.
			 */
			वापस 0;
		हाल KFENCE_ERROR_CORRUPTION:
		हाल KFENCE_ERROR_INVALID_FREE:
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (skipnr = 0; skipnr < num_entries; skipnr++) अणु
		पूर्णांक len = scnम_लिखो(buf, माप(buf), "%ps", (व्योम *)stack_entries[skipnr]);

		अगर (str_has_prefix(buf, ARCH_FUNC_PREFIX "kfence_") ||
		    str_has_prefix(buf, ARCH_FUNC_PREFIX "__kfence_") ||
		    !म_भेदन(buf, ARCH_FUNC_PREFIX "__slab_free", len)) अणु
			/*
			 * In हाल of tail calls from any of the below
			 * to any of the above.
			 */
			fallback = skipnr + 1;
		पूर्ण

		/* Also the *_bulk() variants by only checking prefixes. */
		अगर (str_has_prefix(buf, ARCH_FUNC_PREFIX "kfree") ||
		    str_has_prefix(buf, ARCH_FUNC_PREFIX "kmem_cache_free") ||
		    str_has_prefix(buf, ARCH_FUNC_PREFIX "__kmalloc") ||
		    str_has_prefix(buf, ARCH_FUNC_PREFIX "kmem_cache_alloc"))
			जाओ found;
	पूर्ण
	अगर (fallback < num_entries)
		वापस fallback;
found:
	skipnr++;
	वापस skipnr < num_entries ? skipnr : 0;
पूर्ण

अटल व्योम kfence_prपूर्णांक_stack(काष्ठा seq_file *seq, स्थिर काष्ठा kfence_metadata *meta,
			       bool show_alloc)
अणु
	स्थिर काष्ठा kfence_track *track = show_alloc ? &meta->alloc_track : &meta->मुक्त_track;

	अगर (track->num_stack_entries) अणु
		/* Skip allocation/मुक्त पूर्णांकernals stack. */
		पूर्णांक i = get_stack_skipnr(track->stack_entries, track->num_stack_entries, शून्य);

		/* stack_trace_seq_prपूर्णांक() करोes not exist; खोलो code our own. */
		क्रम (; i < track->num_stack_entries; i++)
			seq_con_म_लिखो(seq, " %pS\n", (व्योम *)track->stack_entries[i]);
	पूर्ण अन्यथा अणु
		seq_con_म_लिखो(seq, " no %s stack\n", show_alloc ? "allocation" : "deallocation");
	पूर्ण
पूर्ण

व्योम kfence_prपूर्णांक_object(काष्ठा seq_file *seq, स्थिर काष्ठा kfence_metadata *meta)
अणु
	स्थिर पूर्णांक size = असल(meta->size);
	स्थिर अचिन्हित दीर्घ start = meta->addr;
	स्थिर काष्ठा kmem_cache *स्थिर cache = meta->cache;

	lockdep_निश्चित_held(&meta->lock);

	अगर (meta->state == KFENCE_OBJECT_UNUSED) अणु
		seq_con_म_लिखो(seq, "kfence-#%td unused\n", meta - kfence_metadata);
		वापस;
	पूर्ण

	seq_con_म_लिखो(seq,
		       "kfence-#%td [0x%p-0x%p"
		       ", size=%d, cache=%s] allocated by task %d:\n",
		       meta - kfence_metadata, (व्योम *)start, (व्योम *)(start + size - 1), size,
		       (cache && cache->name) ? cache->name : "<destroyed>", meta->alloc_track.pid);
	kfence_prपूर्णांक_stack(seq, meta, true);

	अगर (meta->state == KFENCE_OBJECT_FREED) अणु
		seq_con_म_लिखो(seq, "\nfreed by task %d:\n", meta->मुक्त_track.pid);
		kfence_prपूर्णांक_stack(seq, meta, false);
	पूर्ण
पूर्ण

/*
 * Show bytes at @addr that are dअगरferent from the expected canary values, up to
 * @max_bytes.
 */
अटल व्योम prपूर्णांक_dअगरf_canary(अचिन्हित दीर्घ address, माप_प्रकार bytes_to_show,
			      स्थिर काष्ठा kfence_metadata *meta)
अणु
	स्थिर अचिन्हित दीर्घ show_until_addr = address + bytes_to_show;
	स्थिर u8 *cur, *end;

	/* Do not show contents of object nor पढ़ो पूर्णांकo following guard page. */
	end = (स्थिर u8 *)(address < meta->addr ? min(show_until_addr, meta->addr)
						: min(show_until_addr, PAGE_ALIGN(address)));

	pr_cont("[");
	क्रम (cur = (स्थिर u8 *)address; cur < end; cur++) अणु
		अगर (*cur == KFENCE_CANARY_PATTERN(cur))
			pr_cont(" .");
		अन्यथा अगर (no_hash_poपूर्णांकers)
			pr_cont(" 0x%02x", *cur);
		अन्यथा /* Do not leak kernel memory in non-debug builds. */
			pr_cont(" !");
	पूर्ण
	pr_cont(" ]");
पूर्ण

अटल स्थिर अक्षर *get_access_type(bool is_ग_लिखो)
अणु
	वापस is_ग_लिखो ? "write" : "read";
पूर्ण

व्योम kfence_report_error(अचिन्हित दीर्घ address, bool is_ग_लिखो, काष्ठा pt_regs *regs,
			 स्थिर काष्ठा kfence_metadata *meta, क्रमागत kfence_error_type type)
अणु
	अचिन्हित दीर्घ stack_entries[KFENCE_STACK_DEPTH] = अणु 0 पूर्ण;
	स्थिर सूचक_भेद_प्रकार object_index = meta ? meta - kfence_metadata : -1;
	पूर्णांक num_stack_entries;
	पूर्णांक skipnr = 0;

	अगर (regs) अणु
		num_stack_entries = stack_trace_save_regs(regs, stack_entries, KFENCE_STACK_DEPTH, 0);
	पूर्ण अन्यथा अणु
		num_stack_entries = stack_trace_save(stack_entries, KFENCE_STACK_DEPTH, 1);
		skipnr = get_stack_skipnr(stack_entries, num_stack_entries, &type);
	पूर्ण

	/* Require non-शून्य meta, except अगर KFENCE_ERROR_INVALID. */
	अगर (WARN_ON(type != KFENCE_ERROR_INVALID && !meta))
		वापस;

	अगर (meta)
		lockdep_निश्चित_held(&meta->lock);
	/*
	 * Because we may generate reports in prपूर्णांकk-unमित्रly parts of the
	 * kernel, such as scheduler code, the use of prपूर्णांकk() could deadlock.
	 * Until such समय that all prपूर्णांकing code here is safe in all parts of
	 * the kernel, accept the risk, and just get our message out (given the
	 * प्रणाली might alपढ़ोy behave unpredictably due to the memory error).
	 * As such, also disable lockdep to hide warnings, and aव्योम disabling
	 * lockdep क्रम the rest of the kernel.
	 */
	lockdep_off();

	pr_err("==================================================================\n");
	/* Prपूर्णांक report header. */
	चयन (type) अणु
	हाल KFENCE_ERROR_OOB: अणु
		स्थिर bool left_of_object = address < meta->addr;

		pr_err("BUG: KFENCE: out-of-bounds %s in %pS\n\n", get_access_type(is_ग_लिखो),
		       (व्योम *)stack_entries[skipnr]);
		pr_err("Out-of-bounds %s at 0x%p (%luB %s of kfence-#%td):\n",
		       get_access_type(is_ग_लिखो), (व्योम *)address,
		       left_of_object ? meta->addr - address : address - meta->addr,
		       left_of_object ? "left" : "right", object_index);
		अवरोध;
	पूर्ण
	हाल KFENCE_ERROR_UAF:
		pr_err("BUG: KFENCE: use-after-free %s in %pS\n\n", get_access_type(is_ग_लिखो),
		       (व्योम *)stack_entries[skipnr]);
		pr_err("Use-after-free %s at 0x%p (in kfence-#%td):\n",
		       get_access_type(is_ग_लिखो), (व्योम *)address, object_index);
		अवरोध;
	हाल KFENCE_ERROR_CORRUPTION:
		pr_err("BUG: KFENCE: memory corruption in %pS\n\n", (व्योम *)stack_entries[skipnr]);
		pr_err("Corrupted memory at 0x%p ", (व्योम *)address);
		prपूर्णांक_dअगरf_canary(address, 16, meta);
		pr_cont(" (in kfence-#%td):\n", object_index);
		अवरोध;
	हाल KFENCE_ERROR_INVALID:
		pr_err("BUG: KFENCE: invalid %s in %pS\n\n", get_access_type(is_ग_लिखो),
		       (व्योम *)stack_entries[skipnr]);
		pr_err("Invalid %s at 0x%p:\n", get_access_type(is_ग_लिखो),
		       (व्योम *)address);
		अवरोध;
	हाल KFENCE_ERROR_INVALID_FREE:
		pr_err("BUG: KFENCE: invalid free in %pS\n\n", (व्योम *)stack_entries[skipnr]);
		pr_err("Invalid free of 0x%p (in kfence-#%td):\n", (व्योम *)address,
		       object_index);
		अवरोध;
	पूर्ण

	/* Prपूर्णांक stack trace and object info. */
	stack_trace_prपूर्णांक(stack_entries + skipnr, num_stack_entries - skipnr, 0);

	अगर (meta) अणु
		pr_err("\n");
		kfence_prपूर्णांक_object(शून्य, meta);
	पूर्ण

	/* Prपूर्णांक report footer. */
	pr_err("\n");
	अगर (no_hash_poपूर्णांकers && regs)
		show_regs(regs);
	अन्यथा
		dump_stack_prपूर्णांक_info(KERN_ERR);
	trace_error_report_end(ERROR_DETECTOR_KFENCE, address);
	pr_err("==================================================================\n");

	lockdep_on();

	अगर (panic_on_warn)
		panic("panic_on_warn set ...\n");

	/* We encountered a memory safety error, taपूर्णांक the kernel! */
	add_taपूर्णांक(TAINT_BAD_PAGE, LOCKDEP_STILL_OK);
पूर्ण

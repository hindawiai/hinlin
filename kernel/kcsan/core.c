<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KCSAN core runसमय.
 *
 * Copyright (C) 2019, Google LLC.
 */

#घोषणा pr_fmt(fmt) "kcsan: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/percpu.h>
#समावेश <linux/preempt.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>

#समावेश "atomic.h"
#समावेश "encoding.h"
#समावेश "kcsan.h"

अटल bool kcsan_early_enable = IS_ENABLED(CONFIG_KCSAN_EARLY_ENABLE);
अचिन्हित पूर्णांक kcsan_udelay_task = CONFIG_KCSAN_UDELAY_TASK;
अचिन्हित पूर्णांक kcsan_udelay_पूर्णांकerrupt = CONFIG_KCSAN_UDELAY_INTERRUPT;
अटल दीर्घ kcsan_skip_watch = CONFIG_KCSAN_SKIP_WATCH;
अटल bool kcsan_पूर्णांकerrupt_watcher = IS_ENABLED(CONFIG_KCSAN_INTERRUPT_WATCHER);

#अगर_घोषित MODULE_PARAM_PREFIX
#अघोषित MODULE_PARAM_PREFIX
#पूर्ण_अगर
#घोषणा MODULE_PARAM_PREFIX "kcsan."
module_param_named(early_enable, kcsan_early_enable, bool, 0);
module_param_named(udelay_task, kcsan_udelay_task, uपूर्णांक, 0644);
module_param_named(udelay_पूर्णांकerrupt, kcsan_udelay_पूर्णांकerrupt, uपूर्णांक, 0644);
module_param_named(skip_watch, kcsan_skip_watch, दीर्घ, 0644);
module_param_named(पूर्णांकerrupt_watcher, kcsan_पूर्णांकerrupt_watcher, bool, 0444);

bool kcsan_enabled;

/* Per-CPU kcsan_ctx क्रम पूर्णांकerrupts */
अटल DEFINE_PER_CPU(काष्ठा kcsan_ctx, kcsan_cpu_ctx) = अणु
	.disable_count		= 0,
	.atomic_next		= 0,
	.atomic_nest_count	= 0,
	.in_flat_atomic		= false,
	.access_mask		= 0,
	.scoped_accesses	= अणुLIST_POISON1, शून्यपूर्ण,
पूर्ण;

/*
 * Helper macros to index पूर्णांकo adjacent slots, starting from address slot
 * itself, followed by the right and left slots.
 *
 * The purpose is 2-fold:
 *
 *	1. अगर during insertion the address slot is alपढ़ोy occupied, check अगर
 *	   any adjacent slots are मुक्त;
 *	2. accesses that straddle a slot boundary due to size that exceeds a
 *	   slot's range may check adjacent slots अगर any watchpoपूर्णांक matches.
 *
 * Note that accesses with very large size may still miss a watchpoपूर्णांक; however,
 * given this should be rare, this is a reasonable trade-off to make, since this
 * will aव्योम:
 *
 *	1. excessive contention between watchpoपूर्णांक checks and setup;
 *	2. larger number of simultaneous watchpoपूर्णांकs without sacrअगरicing
 *	   perक्रमmance.
 *
 * Example: SLOT_IDX values क्रम KCSAN_CHECK_ADJACENT=1, where i is [0, 1, 2]:
 *
 *   slot=0:  [ 1,  2,  0]
 *   slot=9:  [10, 11,  9]
 *   slot=63: [64, 65, 63]
 */
#घोषणा SLOT_IDX(slot, i) (slot + ((i + KCSAN_CHECK_ADJACENT) % NUM_SLOTS))

/*
 * SLOT_IDX_FAST is used in the fast-path. Not first checking the address's primary
 * slot (middle) is fine अगर we assume that races occur rarely. The set of
 * indices अणुSLOT_IDX(slot, i) | i in [0, NUM_SLOTS)पूर्ण is equivalent to
 * अणुSLOT_IDX_FAST(slot, i) | i in [0, NUM_SLOTS)पूर्ण.
 */
#घोषणा SLOT_IDX_FAST(slot, i) (slot + i)

/*
 * Watchpoपूर्णांकs, with each entry encoded as defined in encoding.h: in order to be
 * able to safely update and access a watchpoपूर्णांक without पूर्णांकroducing locking
 * overhead, we encode each watchpoपूर्णांक as a single atomic दीर्घ. The initial
 * zero-initialized state matches INVALID_WATCHPOINT.
 *
 * Add NUM_SLOTS-1 entries to account क्रम overflow; this helps aव्योम having to
 * use more complicated SLOT_IDX_FAST calculation with modulo in the fast-path.
 */
अटल atomic_दीर्घ_t watchpoपूर्णांकs[CONFIG_KCSAN_NUM_WATCHPOINTS + NUM_SLOTS-1];

/*
 * Inकाष्ठाions to skip watching counter, used in should_watch(). We use a
 * per-CPU counter to aव्योम excessive contention.
 */
अटल DEFINE_PER_CPU(दीर्घ, kcsan_skip);

/* For kcsan_pअक्रमom_u32_max(). */
अटल DEFINE_PER_CPU(u32, kcsan_अक्रम_state);

अटल __always_अंतरभूत atomic_दीर्घ_t *find_watchpoपूर्णांक(अचिन्हित दीर्घ addr,
						      माप_प्रकार size,
						      bool expect_ग_लिखो,
						      दीर्घ *encoded_watchpoपूर्णांक)
अणु
	स्थिर पूर्णांक slot = watchpoपूर्णांक_slot(addr);
	स्थिर अचिन्हित दीर्घ addr_masked = addr & WATCHPOINT_ADDR_MASK;
	atomic_दीर्घ_t *watchpoपूर्णांक;
	अचिन्हित दीर्घ wp_addr_masked;
	माप_प्रकार wp_size;
	bool is_ग_लिखो;
	पूर्णांक i;

	BUILD_BUG_ON(CONFIG_KCSAN_NUM_WATCHPOINTS < NUM_SLOTS);

	क्रम (i = 0; i < NUM_SLOTS; ++i) अणु
		watchpoपूर्णांक = &watchpoपूर्णांकs[SLOT_IDX_FAST(slot, i)];
		*encoded_watchpoपूर्णांक = atomic_दीर्घ_पढ़ो(watchpoपूर्णांक);
		अगर (!decode_watchpoपूर्णांक(*encoded_watchpoपूर्णांक, &wp_addr_masked,
				       &wp_size, &is_ग_लिखो))
			जारी;

		अगर (expect_ग_लिखो && !is_ग_लिखो)
			जारी;

		/* Check अगर the watchpoपूर्णांक matches the access. */
		अगर (matching_access(wp_addr_masked, wp_size, addr_masked, size))
			वापस watchpoपूर्णांक;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत atomic_दीर्घ_t *
insert_watchpoपूर्णांक(अचिन्हित दीर्घ addr, माप_प्रकार size, bool is_ग_लिखो)
अणु
	स्थिर पूर्णांक slot = watchpoपूर्णांक_slot(addr);
	स्थिर दीर्घ encoded_watchpoपूर्णांक = encode_watchpoपूर्णांक(addr, size, is_ग_लिखो);
	atomic_दीर्घ_t *watchpoपूर्णांक;
	पूर्णांक i;

	/* Check slot index logic, ensuring we stay within array bounds. */
	BUILD_BUG_ON(SLOT_IDX(0, 0) != KCSAN_CHECK_ADJACENT);
	BUILD_BUG_ON(SLOT_IDX(0, KCSAN_CHECK_ADJACENT+1) != 0);
	BUILD_BUG_ON(SLOT_IDX(CONFIG_KCSAN_NUM_WATCHPOINTS-1, KCSAN_CHECK_ADJACENT) != ARRAY_SIZE(watchpoपूर्णांकs)-1);
	BUILD_BUG_ON(SLOT_IDX(CONFIG_KCSAN_NUM_WATCHPOINTS-1, KCSAN_CHECK_ADJACENT+1) != ARRAY_SIZE(watchpoपूर्णांकs) - NUM_SLOTS);

	क्रम (i = 0; i < NUM_SLOTS; ++i) अणु
		दीर्घ expect_val = INVALID_WATCHPOINT;

		/* Try to acquire this slot. */
		watchpoपूर्णांक = &watchpoपूर्णांकs[SLOT_IDX(slot, i)];
		अगर (atomic_दीर्घ_try_cmpxchg_relaxed(watchpoपूर्णांक, &expect_val, encoded_watchpoपूर्णांक))
			वापस watchpoपूर्णांक;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Return true अगर watchpoपूर्णांक was successfully consumed, false otherwise.
 *
 * This may वापस false अगर:
 *
 *	1. another thपढ़ो alपढ़ोy consumed the watchpoपूर्णांक;
 *	2. the thपढ़ो that set up the watchpoपूर्णांक alपढ़ोy हटाओd it;
 *	3. the watchpoपूर्णांक was हटाओd and then re-used.
 */
अटल __always_अंतरभूत bool
try_consume_watchpoपूर्णांक(atomic_दीर्घ_t *watchpoपूर्णांक, दीर्घ encoded_watchpoपूर्णांक)
अणु
	वापस atomic_दीर्घ_try_cmpxchg_relaxed(watchpoपूर्णांक, &encoded_watchpoपूर्णांक, CONSUMED_WATCHPOINT);
पूर्ण

/* Return true अगर watchpoपूर्णांक was not touched, false अगर alपढ़ोy consumed. */
अटल अंतरभूत bool consume_watchpoपूर्णांक(atomic_दीर्घ_t *watchpoपूर्णांक)
अणु
	वापस atomic_दीर्घ_xchg_relaxed(watchpoपूर्णांक, CONSUMED_WATCHPOINT) != CONSUMED_WATCHPOINT;
पूर्ण

/* Remove the watchpoपूर्णांक -- its slot may be reused after. */
अटल अंतरभूत व्योम हटाओ_watchpoपूर्णांक(atomic_दीर्घ_t *watchpoपूर्णांक)
अणु
	atomic_दीर्घ_set(watchpoपूर्णांक, INVALID_WATCHPOINT);
पूर्ण

अटल __always_अंतरभूत काष्ठा kcsan_ctx *get_ctx(व्योम)
अणु
	/*
	 * In पूर्णांकerrupts, use raw_cpu_ptr to aव्योम unnecessary checks, that would
	 * also result in calls that generate warnings in uaccess regions.
	 */
	वापस in_task() ? &current->kcsan_ctx : raw_cpu_ptr(&kcsan_cpu_ctx);
पूर्ण

/* Check scoped accesses; never अंतरभूत because this is a slow-path! */
अटल noअंतरभूत व्योम kcsan_check_scoped_accesses(व्योम)
अणु
	काष्ठा kcsan_ctx *ctx = get_ctx();
	काष्ठा list_head *prev_save = ctx->scoped_accesses.prev;
	काष्ठा kcsan_scoped_access *scoped_access;

	ctx->scoped_accesses.prev = शून्य;  /* Aव्योम recursion. */
	list_क्रम_each_entry(scoped_access, &ctx->scoped_accesses, list)
		__kcsan_check_access(scoped_access->ptr, scoped_access->size, scoped_access->type);
	ctx->scoped_accesses.prev = prev_save;
पूर्ण

/* Rules क्रम generic atomic accesses. Called from fast-path. */
अटल __always_अंतरभूत bool
is_atomic(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक type, काष्ठा kcsan_ctx *ctx)
अणु
	अगर (type & KCSAN_ACCESS_ATOMIC)
		वापस true;

	/*
	 * Unless explicitly declared atomic, never consider an निश्चितion access
	 * as atomic. This allows using them also in atomic regions, such as
	 * seqlocks, without implicitly changing their semantics.
	 */
	अगर (type & KCSAN_ACCESS_ASSERT)
		वापस false;

	अगर (IS_ENABLED(CONFIG_KCSAN_ASSUME_PLAIN_WRITES_ATOMIC) &&
	    (type & KCSAN_ACCESS_WRITE) && size <= माप(दीर्घ) &&
	    !(type & KCSAN_ACCESS_COMPOUND) && IS_ALIGNED((अचिन्हित दीर्घ)ptr, size))
		वापस true; /* Assume aligned ग_लिखोs up to word size are atomic. */

	अगर (ctx->atomic_next > 0) अणु
		/*
		 * Because we करो not have separate contexts क्रम nested
		 * पूर्णांकerrupts, in हाल atomic_next is set, we simply assume that
		 * the outer पूर्णांकerrupt set atomic_next. In the worst हाल, we
		 * will conservatively consider operations as atomic. This is a
		 * reasonable trade-off to make, since this हाल should be
		 * extremely rare; however, even अगर extremely rare, it could
		 * lead to false positives otherwise.
		 */
		अगर ((hardirq_count() >> HARसूचीQ_SHIFT) < 2)
			--ctx->atomic_next; /* in task, or outer पूर्णांकerrupt */
		वापस true;
	पूर्ण

	वापस ctx->atomic_nest_count > 0 || ctx->in_flat_atomic;
पूर्ण

अटल __always_अंतरभूत bool
should_watch(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक type, काष्ठा kcsan_ctx *ctx)
अणु
	/*
	 * Never set up watchpoपूर्णांकs when memory operations are atomic.
	 *
	 * Need to check this first, beक्रमe kcsan_skip check below: (1) atomics
	 * should not count towards skipped inकाष्ठाions, and (2) to actually
	 * decrement kcsan_atomic_next क्रम consecutive inकाष्ठाion stream.
	 */
	अगर (is_atomic(ptr, size, type, ctx))
		वापस false;

	अगर (this_cpu_dec_वापस(kcsan_skip) >= 0)
		वापस false;

	/*
	 * NOTE: If we get here, kcsan_skip must always be reset in slow path
	 * via reset_kcsan_skip() to aव्योम underflow.
	 */

	/* this operation should be watched */
	वापस true;
पूर्ण

/*
 * Returns a pseuकरो-अक्रमom number in पूर्णांकerval [0, ep_ro). Simple linear
 * congruential generator, using स्थिरants from "Numerical Recipes".
 */
अटल u32 kcsan_pअक्रमom_u32_max(u32 ep_ro)
अणु
	u32 state = this_cpu_पढ़ो(kcsan_अक्रम_state);

	state = 1664525 * state + 1013904223;
	this_cpu_ग_लिखो(kcsan_अक्रम_state, state);

	वापस state % ep_ro;
पूर्ण

अटल अंतरभूत व्योम reset_kcsan_skip(व्योम)
अणु
	दीर्घ skip_count = kcsan_skip_watch -
			  (IS_ENABLED(CONFIG_KCSAN_SKIP_WATCH_RANDOMIZE) ?
				   kcsan_pअक्रमom_u32_max(kcsan_skip_watch) :
				   0);
	this_cpu_ग_लिखो(kcsan_skip, skip_count);
पूर्ण

अटल __always_अंतरभूत bool kcsan_is_enabled(व्योम)
अणु
	वापस READ_ONCE(kcsan_enabled) && get_ctx()->disable_count == 0;
पूर्ण

/* Introduce delay depending on context and configuration. */
अटल व्योम delay_access(पूर्णांक type)
अणु
	अचिन्हित पूर्णांक delay = in_task() ? kcsan_udelay_task : kcsan_udelay_पूर्णांकerrupt;
	/* For certain access types, skew the अक्रमom delay to be दीर्घer. */
	अचिन्हित पूर्णांक skew_delay_order =
		(type & (KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_ASSERT)) ? 1 : 0;

	delay -= IS_ENABLED(CONFIG_KCSAN_DELAY_RANDOMIZE) ?
			       kcsan_pअक्रमom_u32_max(delay >> skew_delay_order) :
			       0;
	udelay(delay);
पूर्ण

व्योम kcsan_save_irqtrace(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	task->kcsan_save_irqtrace = task->irqtrace;
#पूर्ण_अगर
पूर्ण

व्योम kcsan_restore_irqtrace(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	task->irqtrace = task->kcsan_save_irqtrace;
#पूर्ण_अगर
पूर्ण

/*
 * Pull everything together: check_access() below contains the perक्रमmance
 * critical operations; the fast-path (including check_access) functions should
 * all be inlinable by the instrumentation functions.
 *
 * The slow-path (kcsan_found_watchpoपूर्णांक, kcsan_setup_watchpoपूर्णांक) are
 * non-inlinable -- note that, we prefix these with "kcsan_" to ensure they can
 * be filtered from the stacktrace, as well as give them unique names क्रम the
 * UACCESS whitelist of objtool. Each function uses user_access_save/restore(),
 * since they करो not access any user memory, but instrumentation is still
 * emitted in UACCESS regions.
 */

अटल noअंतरभूत व्योम kcsan_found_watchpoपूर्णांक(स्थिर अस्थिर व्योम *ptr,
					    माप_प्रकार size,
					    पूर्णांक type,
					    atomic_दीर्घ_t *watchpoपूर्णांक,
					    दीर्घ encoded_watchpoपूर्णांक)
अणु
	अचिन्हित दीर्घ flags;
	bool consumed;

	अगर (!kcsan_is_enabled())
		वापस;

	/*
	 * The access_mask check relies on value-change comparison. To aव्योम
	 * reporting a race where e.g. the ग_लिखोr set up the watchpoपूर्णांक, but the
	 * पढ़ोer has access_mask!=0, we have to ignore the found watchpoपूर्णांक.
	 */
	अगर (get_ctx()->access_mask != 0)
		वापस;

	/*
	 * Consume the watchpoपूर्णांक as soon as possible, to minimize the chances
	 * of !consumed. Consuming the watchpoपूर्णांक must always be guarded by
	 * kcsan_is_enabled() check, as otherwise we might erroneously
	 * triggering reports when disabled.
	 */
	consumed = try_consume_watchpoपूर्णांक(watchpoपूर्णांक, encoded_watchpoपूर्णांक);

	/* keep this after try_consume_watchpoपूर्णांक */
	flags = user_access_save();

	अगर (consumed) अणु
		kcsan_save_irqtrace(current);
		kcsan_report(ptr, size, type, KCSAN_VALUE_CHANGE_MAYBE,
			     KCSAN_REPORT_CONSUMED_WATCHPOINT,
			     watchpoपूर्णांक - watchpoपूर्णांकs);
		kcsan_restore_irqtrace(current);
	पूर्ण अन्यथा अणु
		/*
		 * The other thपढ़ो may not prपूर्णांक any diagnostics, as it has
		 * alपढ़ोy हटाओd the watchpoपूर्णांक, or another thपढ़ो consumed
		 * the watchpoपूर्णांक beक्रमe this thपढ़ो.
		 */
		atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_REPORT_RACES]);
	पूर्ण

	अगर ((type & KCSAN_ACCESS_ASSERT) != 0)
		atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_ASSERT_FAILURES]);
	अन्यथा
		atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_DATA_RACES]);

	user_access_restore(flags);
पूर्ण

अटल noअंतरभूत व्योम
kcsan_setup_watchpoपूर्णांक(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक type)
अणु
	स्थिर bool is_ग_लिखो = (type & KCSAN_ACCESS_WRITE) != 0;
	स्थिर bool is_निश्चित = (type & KCSAN_ACCESS_ASSERT) != 0;
	atomic_दीर्घ_t *watchpoपूर्णांक;
	जोड़ अणु
		u8 _1;
		u16 _2;
		u32 _4;
		u64 _8;
	पूर्ण expect_value;
	अचिन्हित दीर्घ access_mask;
	क्रमागत kcsan_value_change value_change = KCSAN_VALUE_CHANGE_MAYBE;
	अचिन्हित दीर्घ ua_flags = user_access_save();
	अचिन्हित दीर्घ irq_flags = 0;

	/*
	 * Always reset kcsan_skip counter in slow-path to aव्योम underflow; see
	 * should_watch().
	 */
	reset_kcsan_skip();

	अगर (!kcsan_is_enabled())
		जाओ out;

	/*
	 * Special atomic rules: unlikely to be true, so we check them here in
	 * the slow-path, and not in the fast-path in is_atomic(). Call after
	 * kcsan_is_enabled(), as we may access memory that is not yet
	 * initialized during early boot.
	 */
	अगर (!is_निश्चित && kcsan_is_atomic_special(ptr))
		जाओ out;

	अगर (!check_encodable((अचिन्हित दीर्घ)ptr, size)) अणु
		atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_UNENCODABLE_ACCESSES]);
		जाओ out;
	पूर्ण

	/*
	 * Save and restore the IRQ state trace touched by KCSAN, since KCSAN's
	 * runसमय is entered क्रम every memory access, and potentially useful
	 * inक्रमmation is lost अगर dirtied by KCSAN.
	 */
	kcsan_save_irqtrace(current);
	अगर (!kcsan_पूर्णांकerrupt_watcher)
		local_irq_save(irq_flags);

	watchpoपूर्णांक = insert_watchpoपूर्णांक((अचिन्हित दीर्घ)ptr, size, is_ग_लिखो);
	अगर (watchpoपूर्णांक == शून्य) अणु
		/*
		 * Out of capacity: the size of 'watchpoints', and the frequency
		 * with which should_watch() वापसs true should be tweaked so
		 * that this हाल happens very rarely.
		 */
		atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_NO_CAPACITY]);
		जाओ out_unlock;
	पूर्ण

	atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_SETUP_WATCHPOINTS]);
	atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_USED_WATCHPOINTS]);

	/*
	 * Read the current value, to later check and infer a race अगर the data
	 * was modअगरied via a non-instrumented access, e.g. from a device.
	 */
	expect_value._8 = 0;
	चयन (size) अणु
	हाल 1:
		expect_value._1 = READ_ONCE(*(स्थिर u8 *)ptr);
		अवरोध;
	हाल 2:
		expect_value._2 = READ_ONCE(*(स्थिर u16 *)ptr);
		अवरोध;
	हाल 4:
		expect_value._4 = READ_ONCE(*(स्थिर u32 *)ptr);
		अवरोध;
	हाल 8:
		expect_value._8 = READ_ONCE(*(स्थिर u64 *)ptr);
		अवरोध;
	शेष:
		अवरोध; /* ignore; we करो not dअगरf the values */
	पूर्ण

	अगर (IS_ENABLED(CONFIG_KCSAN_DEBUG)) अणु
		kcsan_disable_current();
		pr_err("watching %s, size: %zu, addr: %px [slot: %d, encoded: %lx]\n",
		       is_ग_लिखो ? "write" : "read", size, ptr,
		       watchpoपूर्णांक_slot((अचिन्हित दीर्घ)ptr),
		       encode_watchpoपूर्णांक((अचिन्हित दीर्घ)ptr, size, is_ग_लिखो));
		kcsan_enable_current();
	पूर्ण

	/*
	 * Delay this thपढ़ो, to increase probability of observing a racy
	 * conflicting access.
	 */
	delay_access(type);

	/*
	 * Re-पढ़ो value, and check अगर it is as expected; अगर not, we infer a
	 * racy access.
	 */
	access_mask = get_ctx()->access_mask;
	चयन (size) अणु
	हाल 1:
		expect_value._1 ^= READ_ONCE(*(स्थिर u8 *)ptr);
		अगर (access_mask)
			expect_value._1 &= (u8)access_mask;
		अवरोध;
	हाल 2:
		expect_value._2 ^= READ_ONCE(*(स्थिर u16 *)ptr);
		अगर (access_mask)
			expect_value._2 &= (u16)access_mask;
		अवरोध;
	हाल 4:
		expect_value._4 ^= READ_ONCE(*(स्थिर u32 *)ptr);
		अगर (access_mask)
			expect_value._4 &= (u32)access_mask;
		अवरोध;
	हाल 8:
		expect_value._8 ^= READ_ONCE(*(स्थिर u64 *)ptr);
		अगर (access_mask)
			expect_value._8 &= (u64)access_mask;
		अवरोध;
	शेष:
		अवरोध; /* ignore; we करो not dअगरf the values */
	पूर्ण

	/* Were we able to observe a value-change? */
	अगर (expect_value._8 != 0)
		value_change = KCSAN_VALUE_CHANGE_TRUE;

	/* Check अगर this access raced with another. */
	अगर (!consume_watchpoपूर्णांक(watchpoपूर्णांक)) अणु
		/*
		 * Depending on the access type, map a value_change of MAYBE to
		 * TRUE (always report) or FALSE (never report).
		 */
		अगर (value_change == KCSAN_VALUE_CHANGE_MAYBE) अणु
			अगर (access_mask != 0) अणु
				/*
				 * For access with access_mask, we require a
				 * value-change, as it is likely that races on
				 * ~access_mask bits are expected.
				 */
				value_change = KCSAN_VALUE_CHANGE_FALSE;
			पूर्ण अन्यथा अगर (size > 8 || is_निश्चित) अणु
				/* Always assume a value-change. */
				value_change = KCSAN_VALUE_CHANGE_TRUE;
			पूर्ण
		पूर्ण

		/*
		 * No need to increment 'data_races' counter, as the racing
		 * thपढ़ो alपढ़ोy did.
		 *
		 * Count 'assert_failures' क्रम each failed ASSERT access,
		 * thereक्रमe both this thपढ़ो and the racing thपढ़ो may
		 * increment this counter.
		 */
		अगर (is_निश्चित && value_change == KCSAN_VALUE_CHANGE_TRUE)
			atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_ASSERT_FAILURES]);

		kcsan_report(ptr, size, type, value_change, KCSAN_REPORT_RACE_SIGNAL,
			     watchpoपूर्णांक - watchpoपूर्णांकs);
	पूर्ण अन्यथा अगर (value_change == KCSAN_VALUE_CHANGE_TRUE) अणु
		/* Inferring a race, since the value should not have changed. */

		atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_RACES_UNKNOWN_ORIGIN]);
		अगर (is_निश्चित)
			atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_ASSERT_FAILURES]);

		अगर (IS_ENABLED(CONFIG_KCSAN_REPORT_RACE_UNKNOWN_ORIGIN) || is_निश्चित)
			kcsan_report(ptr, size, type, KCSAN_VALUE_CHANGE_TRUE,
				     KCSAN_REPORT_RACE_UNKNOWN_ORIGIN,
				     watchpoपूर्णांक - watchpoपूर्णांकs);
	पूर्ण

	/*
	 * Remove watchpoपूर्णांक; must be after reporting, since the slot may be
	 * reused after this poपूर्णांक.
	 */
	हटाओ_watchpoपूर्णांक(watchpoपूर्णांक);
	atomic_दीर्घ_dec(&kcsan_counters[KCSAN_COUNTER_USED_WATCHPOINTS]);
out_unlock:
	अगर (!kcsan_पूर्णांकerrupt_watcher)
		local_irq_restore(irq_flags);
	kcsan_restore_irqtrace(current);
out:
	user_access_restore(ua_flags);
पूर्ण

अटल __always_अंतरभूत व्योम check_access(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size,
					 पूर्णांक type)
अणु
	स्थिर bool is_ग_लिखो = (type & KCSAN_ACCESS_WRITE) != 0;
	atomic_दीर्घ_t *watchpoपूर्णांक;
	दीर्घ encoded_watchpoपूर्णांक;

	/*
	 * Do nothing क्रम 0 sized check; this comparison will be optimized out
	 * क्रम स्थिरant sized instrumentation (__tsan_अणुपढ़ो,ग_लिखोपूर्णN).
	 */
	अगर (unlikely(size == 0))
		वापस;

	/*
	 * Aव्योम user_access_save in fast-path: find_watchpoपूर्णांक is safe without
	 * user_access_save, as the address that ptr poपूर्णांकs to is only used to
	 * check अगर a watchpoपूर्णांक exists; ptr is never dereferenced.
	 */
	watchpoपूर्णांक = find_watchpoपूर्णांक((अचिन्हित दीर्घ)ptr, size, !is_ग_लिखो,
				     &encoded_watchpoपूर्णांक);
	/*
	 * It is safe to check kcsan_is_enabled() after find_watchpoपूर्णांक in the
	 * slow-path, as दीर्घ as no state changes that cause a race to be
	 * detected and reported have occurred until kcsan_is_enabled() is
	 * checked.
	 */

	अगर (unlikely(watchpoपूर्णांक != शून्य))
		kcsan_found_watchpoपूर्णांक(ptr, size, type, watchpoपूर्णांक,
				       encoded_watchpoपूर्णांक);
	अन्यथा अणु
		काष्ठा kcsan_ctx *ctx = get_ctx(); /* Call only once in fast-path. */

		अगर (unlikely(should_watch(ptr, size, type, ctx)))
			kcsan_setup_watchpoपूर्णांक(ptr, size, type);
		अन्यथा अगर (unlikely(ctx->scoped_accesses.prev))
			kcsan_check_scoped_accesses();
	पूर्ण
पूर्ण

/* === Public पूर्णांकerface ===================================================== */

व्योम __init kcsan_init(व्योम)
अणु
	पूर्णांक cpu;

	BUG_ON(!in_task());

	क्रम_each_possible_cpu(cpu)
		per_cpu(kcsan_अक्रम_state, cpu) = (u32)get_cycles();

	/*
	 * We are in the init task, and no other tasks should be running;
	 * WRITE_ONCE without memory barrier is sufficient.
	 */
	अगर (kcsan_early_enable) अणु
		pr_info("enabled early\n");
		WRITE_ONCE(kcsan_enabled, true);
	पूर्ण
पूर्ण

/* === Exported पूर्णांकerface =================================================== */

व्योम kcsan_disable_current(व्योम)
अणु
	++get_ctx()->disable_count;
पूर्ण
EXPORT_SYMBOL(kcsan_disable_current);

व्योम kcsan_enable_current(व्योम)
अणु
	अगर (get_ctx()->disable_count-- == 0) अणु
		/*
		 * Warn अगर kcsan_enable_current() calls are unbalanced with
		 * kcsan_disable_current() calls, which causes disable_count to
		 * become negative and should not happen.
		 */
		kcsan_disable_current(); /* restore to 0, KCSAN still enabled */
		kcsan_disable_current(); /* disable to generate warning */
		WARN(1, "Unbalanced %s()", __func__);
		kcsan_enable_current();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kcsan_enable_current);

व्योम kcsan_enable_current_nowarn(व्योम)
अणु
	अगर (get_ctx()->disable_count-- == 0)
		kcsan_disable_current();
पूर्ण
EXPORT_SYMBOL(kcsan_enable_current_nowarn);

व्योम kcsan_nestable_atomic_begin(व्योम)
अणु
	/*
	 * Do *not* check and warn अगर we are in a flat atomic region: nestable
	 * and flat atomic regions are independent from each other.
	 * See include/linux/kcsan.h: काष्ठा kcsan_ctx comments क्रम more
	 * comments.
	 */

	++get_ctx()->atomic_nest_count;
पूर्ण
EXPORT_SYMBOL(kcsan_nestable_atomic_begin);

व्योम kcsan_nestable_atomic_end(व्योम)
अणु
	अगर (get_ctx()->atomic_nest_count-- == 0) अणु
		/*
		 * Warn अगर kcsan_nestable_atomic_end() calls are unbalanced with
		 * kcsan_nestable_atomic_begin() calls, which causes
		 * atomic_nest_count to become negative and should not happen.
		 */
		kcsan_nestable_atomic_begin(); /* restore to 0 */
		kcsan_disable_current(); /* disable to generate warning */
		WARN(1, "Unbalanced %s()", __func__);
		kcsan_enable_current();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kcsan_nestable_atomic_end);

व्योम kcsan_flat_atomic_begin(व्योम)
अणु
	get_ctx()->in_flat_atomic = true;
पूर्ण
EXPORT_SYMBOL(kcsan_flat_atomic_begin);

व्योम kcsan_flat_atomic_end(व्योम)
अणु
	get_ctx()->in_flat_atomic = false;
पूर्ण
EXPORT_SYMBOL(kcsan_flat_atomic_end);

व्योम kcsan_atomic_next(पूर्णांक n)
अणु
	get_ctx()->atomic_next = n;
पूर्ण
EXPORT_SYMBOL(kcsan_atomic_next);

व्योम kcsan_set_access_mask(अचिन्हित दीर्घ mask)
अणु
	get_ctx()->access_mask = mask;
पूर्ण
EXPORT_SYMBOL(kcsan_set_access_mask);

काष्ठा kcsan_scoped_access *
kcsan_begin_scoped_access(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक type,
			  काष्ठा kcsan_scoped_access *sa)
अणु
	काष्ठा kcsan_ctx *ctx = get_ctx();

	__kcsan_check_access(ptr, size, type);

	ctx->disable_count++; /* Disable KCSAN, in हाल list debugging is on. */

	INIT_LIST_HEAD(&sa->list);
	sa->ptr = ptr;
	sa->size = size;
	sa->type = type;

	अगर (!ctx->scoped_accesses.prev) /* Lazy initialize list head. */
		INIT_LIST_HEAD(&ctx->scoped_accesses);
	list_add(&sa->list, &ctx->scoped_accesses);

	ctx->disable_count--;
	वापस sa;
पूर्ण
EXPORT_SYMBOL(kcsan_begin_scoped_access);

व्योम kcsan_end_scoped_access(काष्ठा kcsan_scoped_access *sa)
अणु
	काष्ठा kcsan_ctx *ctx = get_ctx();

	अगर (WARN(!ctx->scoped_accesses.prev, "Unbalanced %s()?", __func__))
		वापस;

	ctx->disable_count++; /* Disable KCSAN, in हाल list debugging is on. */

	list_del(&sa->list);
	अगर (list_empty(&ctx->scoped_accesses))
		/*
		 * Ensure we करो not enter kcsan_check_scoped_accesses()
		 * slow-path अगर unnecessary, and aव्योमs requiring list_empty()
		 * in the fast-path (to aव्योम a READ_ONCE() and potential
		 * uaccess warning).
		 */
		ctx->scoped_accesses.prev = शून्य;

	ctx->disable_count--;

	__kcsan_check_access(sa->ptr, sa->size, sa->type);
पूर्ण
EXPORT_SYMBOL(kcsan_end_scoped_access);

व्योम __kcsan_check_access(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक type)
अणु
	check_access(ptr, size, type);
पूर्ण
EXPORT_SYMBOL(__kcsan_check_access);

/*
 * KCSAN uses the same instrumentation that is emitted by supported compilers
 * क्रम Thपढ़ोSanitizer (TSAN).
 *
 * When enabled, the compiler emits instrumentation calls (the functions
 * prefixed with "__tsan" below) क्रम all loads and stores that it generated;
 * अंतरभूत यंत्र is not instrumented.
 *
 * Note that, not all supported compiler versions distinguish aligned/unaligned
 * accesses, but e.g. recent versions of Clang करो. We simply alias the unaligned
 * version to the generic version, which can handle both.
 */

#घोषणा DEFINE_TSAN_READ_WRITE(size)                                           \
	व्योम __tsan_पढ़ो##size(व्योम *ptr);                                     \
	व्योम __tsan_पढ़ो##size(व्योम *ptr)                                      \
	अणु                                                                      \
		check_access(ptr, size, 0);                                    \
	पूर्ण                                                                      \
	EXPORT_SYMBOL(__tsan_पढ़ो##size);                                      \
	व्योम __tsan_unaligned_पढ़ो##size(व्योम *ptr)                            \
		__alias(__tsan_पढ़ो##size);                                    \
	EXPORT_SYMBOL(__tsan_unaligned_पढ़ो##size);                            \
	व्योम __tsan_ग_लिखो##size(व्योम *ptr);                                    \
	व्योम __tsan_ग_लिखो##size(व्योम *ptr)                                     \
	अणु                                                                      \
		check_access(ptr, size, KCSAN_ACCESS_WRITE);                   \
	पूर्ण                                                                      \
	EXPORT_SYMBOL(__tsan_ग_लिखो##size);                                     \
	व्योम __tsan_unaligned_ग_लिखो##size(व्योम *ptr)                           \
		__alias(__tsan_ग_लिखो##size);                                   \
	EXPORT_SYMBOL(__tsan_unaligned_ग_लिखो##size);                           \
	व्योम __tsan_पढ़ो_ग_लिखो##size(व्योम *ptr);                               \
	व्योम __tsan_पढ़ो_ग_लिखो##size(व्योम *ptr)                                \
	अणु                                                                      \
		check_access(ptr, size,                                        \
			     KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE);      \
	पूर्ण                                                                      \
	EXPORT_SYMBOL(__tsan_पढ़ो_ग_लिखो##size);                                \
	व्योम __tsan_unaligned_पढ़ो_ग_लिखो##size(व्योम *ptr)                      \
		__alias(__tsan_पढ़ो_ग_लिखो##size);                              \
	EXPORT_SYMBOL(__tsan_unaligned_पढ़ो_ग_लिखो##size)

DEFINE_TSAN_READ_WRITE(1);
DEFINE_TSAN_READ_WRITE(2);
DEFINE_TSAN_READ_WRITE(4);
DEFINE_TSAN_READ_WRITE(8);
DEFINE_TSAN_READ_WRITE(16);

व्योम __tsan_पढ़ो_range(व्योम *ptr, माप_प्रकार size);
व्योम __tsan_पढ़ो_range(व्योम *ptr, माप_प्रकार size)
अणु
	check_access(ptr, size, 0);
पूर्ण
EXPORT_SYMBOL(__tsan_पढ़ो_range);

व्योम __tsan_ग_लिखो_range(व्योम *ptr, माप_प्रकार size);
व्योम __tsan_ग_लिखो_range(व्योम *ptr, माप_प्रकार size)
अणु
	check_access(ptr, size, KCSAN_ACCESS_WRITE);
पूर्ण
EXPORT_SYMBOL(__tsan_ग_लिखो_range);

/*
 * Use of explicit अस्थिर is generally disallowed [1], however, अस्थिर is
 * still used in various concurrent context, whether in low-level
 * synchronization primitives or क्रम legacy reasons.
 * [1] https://lwn.net/Articles/233479/
 *
 * We only consider अस्थिर accesses atomic अगर they are aligned and would pass
 * the size-check of compileसमय_निश्चित_rwonce_type().
 */
#घोषणा DEFINE_TSAN_VOLATILE_READ_WRITE(size)                                  \
	व्योम __tsan_अस्थिर_पढ़ो##size(व्योम *ptr);                            \
	व्योम __tsan_अस्थिर_पढ़ो##size(व्योम *ptr)                             \
	अणु                                                                      \
		स्थिर bool is_atomic = size <= माप(दीर्घ दीर्घ) &&            \
				       IS_ALIGNED((अचिन्हित दीर्घ)ptr, size);   \
		अगर (IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS) && is_atomic)      \
			वापस;                                                \
		check_access(ptr, size, is_atomic ? KCSAN_ACCESS_ATOMIC : 0);  \
	पूर्ण                                                                      \
	EXPORT_SYMBOL(__tsan_अस्थिर_पढ़ो##size);                             \
	व्योम __tsan_unaligned_अस्थिर_पढ़ो##size(व्योम *ptr)                   \
		__alias(__tsan_अस्थिर_पढ़ो##size);                           \
	EXPORT_SYMBOL(__tsan_unaligned_अस्थिर_पढ़ो##size);                   \
	व्योम __tsan_अस्थिर_ग_लिखो##size(व्योम *ptr);                           \
	व्योम __tsan_अस्थिर_ग_लिखो##size(व्योम *ptr)                            \
	अणु                                                                      \
		स्थिर bool is_atomic = size <= माप(दीर्घ दीर्घ) &&            \
				       IS_ALIGNED((अचिन्हित दीर्घ)ptr, size);   \
		अगर (IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS) && is_atomic)      \
			वापस;                                                \
		check_access(ptr, size,                                        \
			     KCSAN_ACCESS_WRITE |                              \
				     (is_atomic ? KCSAN_ACCESS_ATOMIC : 0));   \
	पूर्ण                                                                      \
	EXPORT_SYMBOL(__tsan_अस्थिर_ग_लिखो##size);                            \
	व्योम __tsan_unaligned_अस्थिर_ग_लिखो##size(व्योम *ptr)                  \
		__alias(__tsan_अस्थिर_ग_लिखो##size);                          \
	EXPORT_SYMBOL(__tsan_unaligned_अस्थिर_ग_लिखो##size)

DEFINE_TSAN_VOLATILE_READ_WRITE(1);
DEFINE_TSAN_VOLATILE_READ_WRITE(2);
DEFINE_TSAN_VOLATILE_READ_WRITE(4);
DEFINE_TSAN_VOLATILE_READ_WRITE(8);
DEFINE_TSAN_VOLATILE_READ_WRITE(16);

/*
 * The below are not required by KCSAN, but can still be emitted by the
 * compiler.
 */
व्योम __tsan_func_entry(व्योम *call_pc);
व्योम __tsan_func_entry(व्योम *call_pc)
अणु
पूर्ण
EXPORT_SYMBOL(__tsan_func_entry);
व्योम __tsan_func_निकास(व्योम);
व्योम __tsan_func_निकास(व्योम)
अणु
पूर्ण
EXPORT_SYMBOL(__tsan_func_निकास);
व्योम __tsan_init(व्योम);
व्योम __tsan_init(व्योम)
अणु
पूर्ण
EXPORT_SYMBOL(__tsan_init);

/*
 * Instrumentation क्रम atomic builtins (__atomic_*, __sync_*).
 *
 * Normal kernel code _should not_ be using them directly, but some
 * architectures may implement some or all atomics using the compilers'
 * builtins.
 *
 * Note: If an architecture decides to fully implement atomics using the
 * builtins, because they are implicitly instrumented by KCSAN (and KASAN,
 * etc.), implementing the ARCH_ATOMIC पूर्णांकerface (to get instrumentation via
 * atomic-instrumented) is no दीर्घer necessary.
 *
 * TSAN instrumentation replaces atomic accesses with calls to any of the below
 * functions, whose job is to also execute the operation itself.
 */

#घोषणा DEFINE_TSAN_ATOMIC_LOAD_STORE(bits)                                                        \
	u##bits __tsan_atomic##bits##_load(स्थिर u##bits *ptr, पूर्णांक memorder);                      \
	u##bits __tsan_atomic##bits##_load(स्थिर u##bits *ptr, पूर्णांक memorder)                       \
	अणु                                                                                          \
		अगर (!IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS)) अणु                                    \
			check_access(ptr, bits / BITS_PER_BYTE, KCSAN_ACCESS_ATOMIC);              \
		पूर्ण                                                                                  \
		वापस __atomic_load_n(ptr, memorder);                                             \
	पूर्ण                                                                                          \
	EXPORT_SYMBOL(__tsan_atomic##bits##_load);                                                 \
	व्योम __tsan_atomic##bits##_store(u##bits *ptr, u##bits v, पूर्णांक memorder);                   \
	व्योम __tsan_atomic##bits##_store(u##bits *ptr, u##bits v, पूर्णांक memorder)                    \
	अणु                                                                                          \
		अगर (!IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS)) अणु                                    \
			check_access(ptr, bits / BITS_PER_BYTE,                                    \
				     KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ATOMIC);                    \
		पूर्ण                                                                                  \
		__atomic_store_n(ptr, v, memorder);                                                \
	पूर्ण                                                                                          \
	EXPORT_SYMBOL(__tsan_atomic##bits##_store)

#घोषणा DEFINE_TSAN_ATOMIC_RMW(op, bits, suffix)                                                   \
	u##bits __tsan_atomic##bits##_##op(u##bits *ptr, u##bits v, पूर्णांक memorder);                 \
	u##bits __tsan_atomic##bits##_##op(u##bits *ptr, u##bits v, पूर्णांक memorder)                  \
	अणु                                                                                          \
		अगर (!IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS)) अणु                                    \
			check_access(ptr, bits / BITS_PER_BYTE,                                    \
				     KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE |                  \
					     KCSAN_ACCESS_ATOMIC);                                 \
		पूर्ण                                                                                  \
		वापस __atomic_##op##suffix(ptr, v, memorder);                                    \
	पूर्ण                                                                                          \
	EXPORT_SYMBOL(__tsan_atomic##bits##_##op)

/*
 * Note: CAS operations are always classअगरied as ग_लिखो, even in हाल they
 * fail. We cannot perक्रमm check_access() after a ग_लिखो, as it might lead to
 * false positives, in हालs such as:
 *
 *	T0: __atomic_compare_exchange_n(&p->flag, &old, 1, ...)
 *
 *	T1: अगर (__atomic_load_n(&p->flag, ...)) अणु
 *		modअगरy *p;
 *		p->flag = 0;
 *	    पूर्ण
 *
 * The only करोwnside is that, अगर there are 3 thपढ़ोs, with one CAS that
 * succeeds, another CAS that fails, and an unmarked racing operation, we may
 * poपूर्णांक at the wrong CAS as the source of the race. However, अगर we assume that
 * all CAS can succeed in some other execution, the data race is still valid.
 */
#घोषणा DEFINE_TSAN_ATOMIC_CMPXCHG(bits, strength, weak)                                           \
	पूर्णांक __tsan_atomic##bits##_compare_exchange_##strength(u##bits *ptr, u##bits *exp,          \
							      u##bits val, पूर्णांक mo, पूर्णांक fail_mo);   \
	पूर्णांक __tsan_atomic##bits##_compare_exchange_##strength(u##bits *ptr, u##bits *exp,          \
							      u##bits val, पूर्णांक mo, पूर्णांक fail_mo)    \
	अणु                                                                                          \
		अगर (!IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS)) अणु                                    \
			check_access(ptr, bits / BITS_PER_BYTE,                                    \
				     KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE |                  \
					     KCSAN_ACCESS_ATOMIC);                                 \
		पूर्ण                                                                                  \
		वापस __atomic_compare_exchange_n(ptr, exp, val, weak, mo, fail_mo);              \
	पूर्ण                                                                                          \
	EXPORT_SYMBOL(__tsan_atomic##bits##_compare_exchange_##strength)

#घोषणा DEFINE_TSAN_ATOMIC_CMPXCHG_VAL(bits)                                                       \
	u##bits __tsan_atomic##bits##_compare_exchange_val(u##bits *ptr, u##bits exp, u##bits val, \
							   पूर्णांक mo, पूर्णांक fail_mo);                   \
	u##bits __tsan_atomic##bits##_compare_exchange_val(u##bits *ptr, u##bits exp, u##bits val, \
							   पूर्णांक mo, पूर्णांक fail_mo)                    \
	अणु                                                                                          \
		अगर (!IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS)) अणु                                    \
			check_access(ptr, bits / BITS_PER_BYTE,                                    \
				     KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE |                  \
					     KCSAN_ACCESS_ATOMIC);                                 \
		पूर्ण                                                                                  \
		__atomic_compare_exchange_n(ptr, &exp, val, 0, mo, fail_mo);                       \
		वापस exp;                                                                        \
	पूर्ण                                                                                          \
	EXPORT_SYMBOL(__tsan_atomic##bits##_compare_exchange_val)

#घोषणा DEFINE_TSAN_ATOMIC_OPS(bits)                                                               \
	DEFINE_TSAN_ATOMIC_LOAD_STORE(bits);                                                       \
	DEFINE_TSAN_ATOMIC_RMW(exchange, bits, _n);                                                \
	DEFINE_TSAN_ATOMIC_RMW(fetch_add, bits, );                                                 \
	DEFINE_TSAN_ATOMIC_RMW(fetch_sub, bits, );                                                 \
	DEFINE_TSAN_ATOMIC_RMW(fetch_and, bits, );                                                 \
	DEFINE_TSAN_ATOMIC_RMW(fetch_or, bits, );                                                  \
	DEFINE_TSAN_ATOMIC_RMW(fetch_xor, bits, );                                                 \
	DEFINE_TSAN_ATOMIC_RMW(fetch_nand, bits, );                                                \
	DEFINE_TSAN_ATOMIC_CMPXCHG(bits, strong, 0);                                               \
	DEFINE_TSAN_ATOMIC_CMPXCHG(bits, weak, 1);                                                 \
	DEFINE_TSAN_ATOMIC_CMPXCHG_VAL(bits)

DEFINE_TSAN_ATOMIC_OPS(8);
DEFINE_TSAN_ATOMIC_OPS(16);
DEFINE_TSAN_ATOMIC_OPS(32);
DEFINE_TSAN_ATOMIC_OPS(64);

व्योम __tsan_atomic_thपढ़ो_fence(पूर्णांक memorder);
व्योम __tsan_atomic_thपढ़ो_fence(पूर्णांक memorder)
अणु
	__atomic_thपढ़ो_fence(memorder);
पूर्ण
EXPORT_SYMBOL(__tsan_atomic_thपढ़ो_fence);

व्योम __tsan_atomic_संकेत_fence(पूर्णांक memorder);
व्योम __tsan_atomic_संकेत_fence(पूर्णांक memorder) अणु पूर्ण
EXPORT_SYMBOL(__tsan_atomic_संकेत_fence);

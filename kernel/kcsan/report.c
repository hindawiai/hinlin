<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KCSAN reporting.
 *
 * Copyright (C) 2019, Google LLC.
 */

#समावेश <linux/debug_locks.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/preempt.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/stacktrace.h>

#समावेश "kcsan.h"
#समावेश "encoding.h"

/*
 * Max. number of stack entries to show in the report.
 */
#घोषणा NUM_STACK_ENTRIES 64

/* Common access info. */
काष्ठा access_info अणु
	स्थिर अस्थिर व्योम	*ptr;
	माप_प्रकार			size;
	पूर्णांक			access_type;
	पूर्णांक			task_pid;
	पूर्णांक			cpu_id;
पूर्ण;

/*
 * Other thपढ़ो info: communicated from other racing thपढ़ो to thपढ़ो that set
 * up the watchpoपूर्णांक, which then prपूर्णांकs the complete report atomically.
 */
काष्ठा other_info अणु
	काष्ठा access_info	ai;
	अचिन्हित दीर्घ		stack_entries[NUM_STACK_ENTRIES];
	पूर्णांक			num_stack_entries;

	/*
	 * Optionally pass @current. Typically we करो not need to pass @current
	 * via @other_info since just @task_pid is sufficient. Passing @current
	 * has additional overhead.
	 *
	 * To safely pass @current, we must either use get_task_काष्ठा/
	 * put_task_काष्ठा, or stall the thपढ़ो that populated @other_info.
	 *
	 * We cannot rely on get_task_काष्ठा/put_task_काष्ठा in हाल
	 * release_report() races with a task being released, and would have to
	 * मुक्त it in release_report(). This may result in deadlock अगर we want
	 * to use KCSAN on the allocators.
	 *
	 * Since we also want to reliably prपूर्णांक held locks क्रम
	 * CONFIG_KCSAN_VERBOSE, the current implementation stalls the thपढ़ो
	 * that populated @other_info until it has been consumed.
	 */
	काष्ठा task_काष्ठा	*task;
पूर्ण;

/*
 * To never block any producers of काष्ठा other_info, we need as many elements
 * as we have watchpoपूर्णांकs (upper bound on concurrent races to report).
 */
अटल काष्ठा other_info other_infos[CONFIG_KCSAN_NUM_WATCHPOINTS + NUM_SLOTS-1];

/*
 * Inक्रमmation about reported races; used to rate limit reporting.
 */
काष्ठा report_समय अणु
	/*
	 * The last समय the race was reported.
	 */
	अचिन्हित दीर्घ समय;

	/*
	 * The frames of the 2 thपढ़ोs; अगर only 1 thपढ़ो is known, one frame
	 * will be 0.
	 */
	अचिन्हित दीर्घ frame1;
	अचिन्हित दीर्घ frame2;
पूर्ण;

/*
 * Since we also want to be able to debug allocators with KCSAN, to aव्योम
 * deadlock, report_बार cannot be dynamically resized with kपुनः_स्मृति in
 * rate_limit_report.
 *
 * Thereक्रमe, we use a fixed-size array, which at most will occupy a page. This
 * still adequately rate limits reports, assuming that a) number of unique data
 * races is not excessive, and b) occurrence of unique races within the
 * same समय winकरोw is limited.
 */
#घोषणा REPORT_TIMES_MAX (PAGE_SIZE / माप(काष्ठा report_समय))
#घोषणा REPORT_TIMES_SIZE                                                      \
	(CONFIG_KCSAN_REPORT_ONCE_IN_MS > REPORT_TIMES_MAX ?                   \
		 REPORT_TIMES_MAX :                                            \
		 CONFIG_KCSAN_REPORT_ONCE_IN_MS)
अटल काष्ठा report_समय report_बार[REPORT_TIMES_SIZE];

/*
 * Spinlock serializing report generation, and access to @other_infos. Although
 * it could make sense to have a finer-grained locking story क्रम @other_infos,
 * report generation needs to be serialized either way, so not much is gained.
 */
अटल DEFINE_RAW_SPINLOCK(report_lock);

/*
 * Checks अगर the race identअगरied by thपढ़ो frames frame1 and frame2 has
 * been reported since (now - KCSAN_REPORT_ONCE_IN_MS).
 */
अटल bool rate_limit_report(अचिन्हित दीर्घ frame1, अचिन्हित दीर्घ frame2)
अणु
	काष्ठा report_समय *use_entry = &report_बार[0];
	अचिन्हित दीर्घ invalid_beक्रमe;
	पूर्णांक i;

	BUILD_BUG_ON(CONFIG_KCSAN_REPORT_ONCE_IN_MS != 0 && REPORT_TIMES_SIZE == 0);

	अगर (CONFIG_KCSAN_REPORT_ONCE_IN_MS == 0)
		वापस false;

	invalid_beक्रमe = jअगरfies - msecs_to_jअगरfies(CONFIG_KCSAN_REPORT_ONCE_IN_MS);

	/* Check अगर a matching race report exists. */
	क्रम (i = 0; i < REPORT_TIMES_SIZE; ++i) अणु
		काष्ठा report_समय *rt = &report_बार[i];

		/*
		 * Must always select an entry क्रम use to store info as we
		 * cannot resize report_बार; at the end of the scan, use_entry
		 * will be the oldest entry, which ideally also happened beक्रमe
		 * KCSAN_REPORT_ONCE_IN_MS ago.
		 */
		अगर (समय_beक्रमe(rt->समय, use_entry->समय))
			use_entry = rt;

		/*
		 * Initially, no need to check any further as this entry as well
		 * as following entries have never been used.
		 */
		अगर (rt->समय == 0)
			अवरोध;

		/* Check अगर entry expired. */
		अगर (समय_beक्रमe(rt->समय, invalid_beक्रमe))
			जारी; /* beक्रमe KCSAN_REPORT_ONCE_IN_MS ago */

		/* Reported recently, check अगर race matches. */
		अगर ((rt->frame1 == frame1 && rt->frame2 == frame2) ||
		    (rt->frame1 == frame2 && rt->frame2 == frame1))
			वापस true;
	पूर्ण

	use_entry->समय = jअगरfies;
	use_entry->frame1 = frame1;
	use_entry->frame2 = frame2;
	वापस false;
पूर्ण

/*
 * Special rules to skip reporting.
 */
अटल bool
skip_report(क्रमागत kcsan_value_change value_change, अचिन्हित दीर्घ top_frame)
अणु
	/* Should never get here अगर value_change==FALSE. */
	WARN_ON_ONCE(value_change == KCSAN_VALUE_CHANGE_FALSE);

	/*
	 * The first call to skip_report always has value_change==TRUE, since we
	 * cannot know the value written of an instrumented access. For the 2nd
	 * call there are 6 हालs with CONFIG_KCSAN_REPORT_VALUE_CHANGE_ONLY:
	 *
	 * 1. पढ़ो watchpoपूर्णांक, conflicting ग_लिखो (value_change==TRUE): report;
	 * 2. पढ़ो watchpoपूर्णांक, conflicting ग_लिखो (value_change==MAYBE): skip;
	 * 3. ग_लिखो watchpoपूर्णांक, conflicting ग_लिखो (value_change==TRUE): report;
	 * 4. ग_लिखो watchpoपूर्णांक, conflicting ग_लिखो (value_change==MAYBE): skip;
	 * 5. ग_लिखो watchpoपूर्णांक, conflicting पढ़ो (value_change==MAYBE): skip;
	 * 6. ग_लिखो watchpoपूर्णांक, conflicting पढ़ो (value_change==TRUE): report;
	 *
	 * Cases 1-4 are पूर्णांकuitive and expected; हाल 5 ensures we करो not report
	 * data races where the ग_लिखो may have rewritten the same value; हाल 6
	 * is possible either अगर the size is larger than what we check value
	 * changes क्रम or the access type is KCSAN_ACCESS_ASSERT.
	 */
	अगर (IS_ENABLED(CONFIG_KCSAN_REPORT_VALUE_CHANGE_ONLY) &&
	    value_change == KCSAN_VALUE_CHANGE_MAYBE) अणु
		/*
		 * The access is a ग_लिखो, but the data value did not change.
		 *
		 * We opt-out of this filter क्रम certain functions at request of
		 * मुख्यtainers.
		 */
		अक्षर buf[64];
		पूर्णांक len = scnम_लिखो(buf, माप(buf), "%ps", (व्योम *)top_frame);

		अगर (!strnstr(buf, "rcu_", len) &&
		    !strnstr(buf, "_rcu", len) &&
		    !strnstr(buf, "_srcu", len))
			वापस true;
	पूर्ण

	वापस kcsan_skip_report_debugfs(top_frame);
पूर्ण

अटल स्थिर अक्षर *get_access_type(पूर्णांक type)
अणु
	अगर (type & KCSAN_ACCESS_ASSERT) अणु
		अगर (type & KCSAN_ACCESS_SCOPED) अणु
			अगर (type & KCSAN_ACCESS_WRITE)
				वापस "assert no accesses (scoped)";
			अन्यथा
				वापस "assert no writes (scoped)";
		पूर्ण अन्यथा अणु
			अगर (type & KCSAN_ACCESS_WRITE)
				वापस "assert no accesses";
			अन्यथा
				वापस "assert no writes";
		पूर्ण
	पूर्ण

	चयन (type) अणु
	हाल 0:
		वापस "read";
	हाल KCSAN_ACCESS_ATOMIC:
		वापस "read (marked)";
	हाल KCSAN_ACCESS_WRITE:
		वापस "write";
	हाल KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ATOMIC:
		वापस "write (marked)";
	हाल KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE:
		वापस "read-write";
	हाल KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ATOMIC:
		वापस "read-write (marked)";
	हाल KCSAN_ACCESS_SCOPED:
		वापस "read (scoped)";
	हाल KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_ATOMIC:
		वापस "read (marked, scoped)";
	हाल KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_WRITE:
		वापस "write (scoped)";
	हाल KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ATOMIC:
		वापस "write (marked, scoped)";
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *get_bug_type(पूर्णांक type)
अणु
	वापस (type & KCSAN_ACCESS_ASSERT) != 0 ? "assert: race" : "data-race";
पूर्ण

/* Return thपढ़ो description: in task or पूर्णांकerrupt. */
अटल स्थिर अक्षर *get_thपढ़ो_desc(पूर्णांक task_id)
अणु
	अगर (task_id != -1) अणु
		अटल अक्षर buf[32]; /* safe: रक्षित by report_lock */

		snम_लिखो(buf, माप(buf), "task %i", task_id);
		वापस buf;
	पूर्ण
	वापस "interrupt";
पूर्ण

/* Helper to skip KCSAN-related functions in stack-trace. */
अटल पूर्णांक get_stack_skipnr(स्थिर अचिन्हित दीर्घ stack_entries[], पूर्णांक num_entries)
अणु
	अक्षर buf[64];
	अक्षर *cur;
	पूर्णांक len, skip;

	क्रम (skip = 0; skip < num_entries; ++skip) अणु
		len = scnम_लिखो(buf, माप(buf), "%ps", (व्योम *)stack_entries[skip]);

		/* Never show tsan_* or अणुपढ़ो,ग_लिखोपूर्ण_once_size. */
		अगर (strnstr(buf, "tsan_", len) ||
		    strnstr(buf, "_once_size", len))
			जारी;

		cur = strnstr(buf, "kcsan_", len);
		अगर (cur) अणु
			cur += म_माप("kcsan_");
			अगर (!str_has_prefix(cur, "test"))
				जारी; /* KCSAN runसमय function. */
			/* KCSAN related test. */
		पूर्ण

		/*
		 * No match क्रम runसमय functions -- @skip entries to skip to
		 * get to first frame of पूर्णांकerest.
		 */
		अवरोध;
	पूर्ण

	वापस skip;
पूर्ण

/* Compares symbolized strings of addr1 and addr2. */
अटल पूर्णांक sym_म_भेद(व्योम *addr1, व्योम *addr2)
अणु
	अक्षर buf1[64];
	अक्षर buf2[64];

	snम_लिखो(buf1, माप(buf1), "%pS", addr1);
	snम_लिखो(buf2, माप(buf2), "%pS", addr2);

	वापस म_भेदन(buf1, buf2, माप(buf1));
पूर्ण

अटल व्योम prपूर्णांक_verbose_info(काष्ठा task_काष्ठा *task)
अणु
	अगर (!task)
		वापस;

	/* Restore IRQ state trace क्रम prपूर्णांकing. */
	kcsan_restore_irqtrace(task);

	pr_err("\n");
	debug_show_held_locks(task);
	prपूर्णांक_irqtrace_events(task);
पूर्ण

/*
 * Returns true अगर a report was generated, false otherwise.
 */
अटल bool prपूर्णांक_report(क्रमागत kcsan_value_change value_change,
			 क्रमागत kcsan_report_type type,
			 स्थिर काष्ठा access_info *ai,
			 स्थिर काष्ठा other_info *other_info)
अणु
	अचिन्हित दीर्घ stack_entries[NUM_STACK_ENTRIES] = अणु 0 पूर्ण;
	पूर्णांक num_stack_entries = stack_trace_save(stack_entries, NUM_STACK_ENTRIES, 1);
	पूर्णांक skipnr = get_stack_skipnr(stack_entries, num_stack_entries);
	अचिन्हित दीर्घ this_frame = stack_entries[skipnr];
	अचिन्हित दीर्घ other_frame = 0;
	पूर्णांक other_skipnr = 0; /* silence uninit warnings */

	/*
	 * Must check report filter rules beक्रमe starting to prपूर्णांक.
	 */
	अगर (skip_report(KCSAN_VALUE_CHANGE_TRUE, stack_entries[skipnr]))
		वापस false;

	अगर (type == KCSAN_REPORT_RACE_SIGNAL) अणु
		other_skipnr = get_stack_skipnr(other_info->stack_entries,
						other_info->num_stack_entries);
		other_frame = other_info->stack_entries[other_skipnr];

		/* @value_change is only known क्रम the other thपढ़ो */
		अगर (skip_report(value_change, other_frame))
			वापस false;
	पूर्ण

	अगर (rate_limit_report(this_frame, other_frame))
		वापस false;

	/* Prपूर्णांक report header. */
	pr_err("==================================================================\n");
	चयन (type) अणु
	हाल KCSAN_REPORT_RACE_SIGNAL: अणु
		पूर्णांक cmp;

		/*
		 * Order functions lexographically क्रम consistent bug titles.
		 * Do not prपूर्णांक offset of functions to keep title लघु.
		 */
		cmp = sym_म_भेद((व्योम *)other_frame, (व्योम *)this_frame);
		pr_err("BUG: KCSAN: %s in %ps / %ps\n",
		       get_bug_type(ai->access_type | other_info->ai.access_type),
		       (व्योम *)(cmp < 0 ? other_frame : this_frame),
		       (व्योम *)(cmp < 0 ? this_frame : other_frame));
	पूर्ण अवरोध;

	हाल KCSAN_REPORT_RACE_UNKNOWN_ORIGIN:
		pr_err("BUG: KCSAN: %s in %pS\n", get_bug_type(ai->access_type),
		       (व्योम *)this_frame);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	pr_err("\n");

	/* Prपूर्णांक inक्रमmation about the racing accesses. */
	चयन (type) अणु
	हाल KCSAN_REPORT_RACE_SIGNAL:
		pr_err("%s to 0x%px of %zu bytes by %s on cpu %i:\n",
		       get_access_type(other_info->ai.access_type), other_info->ai.ptr,
		       other_info->ai.size, get_thपढ़ो_desc(other_info->ai.task_pid),
		       other_info->ai.cpu_id);

		/* Prपूर्णांक the other thपढ़ो's stack trace. */
		stack_trace_prपूर्णांक(other_info->stack_entries + other_skipnr,
				  other_info->num_stack_entries - other_skipnr,
				  0);

		अगर (IS_ENABLED(CONFIG_KCSAN_VERBOSE))
			prपूर्णांक_verbose_info(other_info->task);

		pr_err("\n");
		pr_err("%s to 0x%px of %zu bytes by %s on cpu %i:\n",
		       get_access_type(ai->access_type), ai->ptr, ai->size,
		       get_thपढ़ो_desc(ai->task_pid), ai->cpu_id);
		अवरोध;

	हाल KCSAN_REPORT_RACE_UNKNOWN_ORIGIN:
		pr_err("race at unknown origin, with %s to 0x%px of %zu bytes by %s on cpu %i:\n",
		       get_access_type(ai->access_type), ai->ptr, ai->size,
		       get_thपढ़ो_desc(ai->task_pid), ai->cpu_id);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
	/* Prपूर्णांक stack trace of this thपढ़ो. */
	stack_trace_prपूर्णांक(stack_entries + skipnr, num_stack_entries - skipnr,
			  0);

	अगर (IS_ENABLED(CONFIG_KCSAN_VERBOSE))
		prपूर्णांक_verbose_info(current);

	/* Prपूर्णांक report footer. */
	pr_err("\n");
	pr_err("Reported by Kernel Concurrency Sanitizer on:\n");
	dump_stack_prपूर्णांक_info(KERN_DEFAULT);
	pr_err("==================================================================\n");

	वापस true;
पूर्ण

अटल व्योम release_report(अचिन्हित दीर्घ *flags, काष्ठा other_info *other_info)
अणु
	अगर (other_info)
		/*
		 * Use size to denote valid/invalid, since KCSAN entirely
		 * ignores 0-sized accesses.
		 */
		other_info->ai.size = 0;

	raw_spin_unlock_irqrestore(&report_lock, *flags);
पूर्ण

/*
 * Sets @other_info->task and aरुकोs consumption of @other_info.
 *
 * Precondition: report_lock is held.
 * Postcondition: report_lock is held.
 */
अटल व्योम set_other_info_task_blocking(अचिन्हित दीर्घ *flags,
					 स्थिर काष्ठा access_info *ai,
					 काष्ठा other_info *other_info)
अणु
	/*
	 * We may be instrumenting a code-path where current->state is alपढ़ोy
	 * something other than TASK_RUNNING.
	 */
	स्थिर bool is_running = current->state == TASK_RUNNING;
	/*
	 * To aव्योम deadlock in हाल we are in an पूर्णांकerrupt here and this is a
	 * race with a task on the same CPU (KCSAN_INTERRUPT_WATCHER), provide a
	 * समयout to ensure this works in all contexts.
	 *
	 * Aरुको approximately the worst हाल delay of the reporting thपढ़ो (अगर
	 * we are not पूर्णांकerrupted).
	 */
	पूर्णांक समयout = max(kcsan_udelay_task, kcsan_udelay_पूर्णांकerrupt);

	other_info->task = current;
	करो अणु
		अगर (is_running) अणु
			/*
			 * Let lockdep know the real task is sleeping, to prपूर्णांक
			 * the held locks (recall we turned lockdep off, so
			 * locking/unlocking @report_lock won't be recorded).
			 */
			set_current_state(TASK_UNINTERRUPTIBLE);
		पूर्ण
		raw_spin_unlock_irqrestore(&report_lock, *flags);
		/*
		 * We cannot call schedule() since we also cannot reliably
		 * determine अगर sleeping here is permitted -- see in_atomic().
		 */

		udelay(1);
		raw_spin_lock_irqsave(&report_lock, *flags);
		अगर (समयout-- < 0) अणु
			/*
			 * Abort. Reset @other_info->task to शून्य, since it
			 * appears the other thपढ़ो is still going to consume
			 * it. It will result in no verbose info prपूर्णांकed क्रम
			 * this task.
			 */
			other_info->task = शून्य;
			अवरोध;
		पूर्ण
		/*
		 * If invalid, or @ptr nor @current matches, then @other_info
		 * has been consumed and we may जारी. If not, retry.
		 */
	पूर्ण जबतक (other_info->ai.size && other_info->ai.ptr == ai->ptr &&
		 other_info->task == current);
	अगर (is_running)
		set_current_state(TASK_RUNNING);
पूर्ण

/* Populate @other_info; requires that the provided @other_info not in use. */
अटल व्योम prepare_report_producer(अचिन्हित दीर्घ *flags,
				    स्थिर काष्ठा access_info *ai,
				    काष्ठा other_info *other_info)
अणु
	raw_spin_lock_irqsave(&report_lock, *flags);

	/*
	 * The same @other_infos entry cannot be used concurrently, because
	 * there is a one-to-one mapping to watchpoपूर्णांक slots (@watchpoपूर्णांकs in
	 * core.c), and a watchpoपूर्णांक is only released क्रम reuse after reporting
	 * is करोne by the consumer of @other_info. Thereक्रमe, it is impossible
	 * क्रम another concurrent prepare_report_producer() to set the same
	 * @other_info, and are guaranteed exclusivity क्रम the @other_infos
	 * entry poपूर्णांकed to by @other_info.
	 *
	 * To check this property holds, size should never be non-zero here,
	 * because every consumer of काष्ठा other_info resets size to 0 in
	 * release_report().
	 */
	WARN_ON(other_info->ai.size);

	other_info->ai = *ai;
	other_info->num_stack_entries = stack_trace_save(other_info->stack_entries, NUM_STACK_ENTRIES, 2);

	अगर (IS_ENABLED(CONFIG_KCSAN_VERBOSE))
		set_other_info_task_blocking(flags, ai, other_info);

	raw_spin_unlock_irqrestore(&report_lock, *flags);
पूर्ण

/* Aरुकोs producer to fill @other_info and then वापसs. */
अटल bool prepare_report_consumer(अचिन्हित दीर्घ *flags,
				    स्थिर काष्ठा access_info *ai,
				    काष्ठा other_info *other_info)
अणु

	raw_spin_lock_irqsave(&report_lock, *flags);
	जबतक (!other_info->ai.size) अणु /* Aरुको valid @other_info. */
		raw_spin_unlock_irqrestore(&report_lock, *flags);
		cpu_relax();
		raw_spin_lock_irqsave(&report_lock, *flags);
	पूर्ण

	/* Should always have a matching access based on watchpoपूर्णांक encoding. */
	अगर (WARN_ON(!matching_access((अचिन्हित दीर्घ)other_info->ai.ptr & WATCHPOINT_ADDR_MASK, other_info->ai.size,
				     (अचिन्हित दीर्घ)ai->ptr & WATCHPOINT_ADDR_MASK, ai->size)))
		जाओ discard;

	अगर (!matching_access((अचिन्हित दीर्घ)other_info->ai.ptr, other_info->ai.size,
			     (अचिन्हित दीर्घ)ai->ptr, ai->size)) अणु
		/*
		 * If the actual accesses to not match, this was a false
		 * positive due to watchpoपूर्णांक encoding.
		 */
		atomic_दीर्घ_inc(&kcsan_counters[KCSAN_COUNTER_ENCODING_FALSE_POSITIVES]);
		जाओ discard;
	पूर्ण

	वापस true;

discard:
	release_report(flags, other_info);
	वापस false;
पूर्ण

/*
 * Depending on the report type either sets @other_info and वापसs false, or
 * aरुकोs @other_info and वापसs true. If @other_info is not required क्रम the
 * report type, simply acquires @report_lock and वापसs true.
 */
अटल noअंतरभूत bool prepare_report(अचिन्हित दीर्घ *flags,
				    क्रमागत kcsan_report_type type,
				    स्थिर काष्ठा access_info *ai,
				    काष्ठा other_info *other_info)
अणु
	चयन (type) अणु
	हाल KCSAN_REPORT_CONSUMED_WATCHPOINT:
		prepare_report_producer(flags, ai, other_info);
		वापस false;
	हाल KCSAN_REPORT_RACE_SIGNAL:
		वापस prepare_report_consumer(flags, ai, other_info);
	शेष:
		/* @other_info not required; just acquire @report_lock. */
		raw_spin_lock_irqsave(&report_lock, *flags);
		वापस true;
	पूर्ण
पूर्ण

व्योम kcsan_report(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक access_type,
		  क्रमागत kcsan_value_change value_change,
		  क्रमागत kcsan_report_type type, पूर्णांक watchpoपूर्णांक_idx)
अणु
	अचिन्हित दीर्घ flags = 0;
	स्थिर काष्ठा access_info ai = अणु
		.ptr		= ptr,
		.size		= size,
		.access_type	= access_type,
		.task_pid	= in_task() ? task_pid_nr(current) : -1,
		.cpu_id		= raw_smp_processor_id()
	पूर्ण;
	काष्ठा other_info *other_info = type == KCSAN_REPORT_RACE_UNKNOWN_ORIGIN
					? शून्य : &other_infos[watchpoपूर्णांक_idx];

	kcsan_disable_current();
	अगर (WARN_ON(watchpoपूर्णांक_idx < 0 || watchpoपूर्णांक_idx >= ARRAY_SIZE(other_infos)))
		जाओ out;

	/*
	 * Because we may generate reports when we're in scheduler code, the use
	 * of prपूर्णांकk() could deadlock. Until such समय that all prपूर्णांकing code
	 * called in prपूर्णांक_report() is scheduler-safe, accept the risk, and just
	 * get our message out. As such, also disable lockdep to hide the
	 * warning, and aव्योम disabling lockdep क्रम the rest of the kernel.
	 */
	lockdep_off();

	अगर (prepare_report(&flags, type, &ai, other_info)) अणु
		/*
		 * Never report अगर value_change is FALSE, only अगर we it is
		 * either TRUE or MAYBE. In हाल of MAYBE, further filtering may
		 * be करोne once we know the full stack trace in prपूर्णांक_report().
		 */
		bool reported = value_change != KCSAN_VALUE_CHANGE_FALSE &&
				prपूर्णांक_report(value_change, type, &ai, other_info);

		अगर (reported && panic_on_warn)
			panic("panic_on_warn set ...\n");

		release_report(&flags, other_info);
	पूर्ण

	lockdep_on();
out:
	kcsan_enable_current();
पूर्ण

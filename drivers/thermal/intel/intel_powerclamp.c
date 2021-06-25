<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_घातerclamp.c - package c-state idle injection
 *
 * Copyright (c) 2012, Intel Corporation.
 *
 * Authors:
 *     Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 *     Jacob Pan <jacob.jun.pan@linux.पूर्णांकel.com>
 *
 *	TODO:
 *           1. better handle wakeup from बाह्यal पूर्णांकerrupts, currently a fixed
 *              compensation is added to clamping duration when excessive amount
 *              of wakeups are observed during idle समय. the reason is that in
 *              हाल of बाह्यal पूर्णांकerrupts without need क्रम ack, clamping करोwn
 *              cpu in non-irq context करोes not reduce irq. क्रम majority of the
 *              हालs, clamping करोwn cpu करोes help reduce irq as well, we should
 *              be able to dअगरferentiate the two हालs and give a quantitative
 *              solution क्रम the irqs that we can control. perhaps based on
 *              get_cpu_ioरुको_समय_us()
 *
 *	     2. synchronization with other hw blocks
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/cpu.h>
#समावेश <linux/thermal.h>
#समावेश <linux/slab.h>
#समावेश <linux/tick.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched/rt.h>
#समावेश <uapi/linux/sched/types.h>

#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/mरुको.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/hardirq.h>

#घोषणा MAX_TARGET_RATIO (50U)
/* For each undisturbed clamping period (no extra wake ups during idle समय),
 * we increment the confidence counter क्रम the given target ratio.
 * CONFIDENCE_OK defines the level where runसमय calibration results are
 * valid.
 */
#घोषणा CONFIDENCE_OK (3)
/* Default idle injection duration, driver adjust sleep समय to meet target
 * idle ratio. Similar to frequency modulation.
 */
#घोषणा DEFAULT_DURATION_JIFFIES (6)

अटल अचिन्हित पूर्णांक target_mरुको;
अटल काष्ठा dentry *debug_dir;

/* user selected target */
अटल अचिन्हित पूर्णांक set_target_ratio;
अटल अचिन्हित पूर्णांक current_ratio;
अटल bool should_skip;
अटल bool reduce_irq;
अटल atomic_t idle_wakeup_counter;
अटल अचिन्हित पूर्णांक control_cpu; /* The cpu asचिन्हित to collect stat and update
				  * control parameters. शेष to BSP but BSP
				  * can be offlined.
				  */
अटल bool clamping;

काष्ठा घातerclamp_worker_data अणु
	काष्ठा kthपढ़ो_worker *worker;
	काष्ठा kthपढ़ो_work balancing_work;
	काष्ठा kthपढ़ो_delayed_work idle_injection_work;
	अचिन्हित पूर्णांक cpu;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक guard;
	अचिन्हित पूर्णांक winकरोw_size_now;
	अचिन्हित पूर्णांक target_ratio;
	अचिन्हित पूर्णांक duration_jअगरfies;
	bool clamping;
पूर्ण;

अटल काष्ठा घातerclamp_worker_data __percpu *worker_data;
अटल काष्ठा thermal_cooling_device *cooling_dev;
अटल अचिन्हित दीर्घ *cpu_clamping_mask;  /* bit map क्रम tracking per cpu
					   * clamping kthपढ़ो worker
					   */

अटल अचिन्हित पूर्णांक duration;
अटल अचिन्हित पूर्णांक pkg_cstate_ratio_cur;
अटल अचिन्हित पूर्णांक winकरोw_size;

अटल पूर्णांक duration_set(स्थिर अक्षर *arg, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ new_duration;

	ret = kम_से_अदीर्घ(arg, 10, &new_duration);
	अगर (ret)
		जाओ निकास;
	अगर (new_duration > 25 || new_duration < 6) अणु
		pr_err("Out of recommended range %lu, between 6-25ms\n",
			new_duration);
		ret = -EINVAL;
	पूर्ण

	duration = clamp(new_duration, 6ul, 25ul);
	smp_mb();

निकास:

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops duration_ops = अणु
	.set = duration_set,
	.get = param_get_पूर्णांक,
पूर्ण;


module_param_cb(duration, &duration_ops, &duration, 0644);
MODULE_PARM_DESC(duration, "forced idle time for each attempt in msec.");

काष्ठा घातerclamp_calibration_data अणु
	अचिन्हित दीर्घ confidence;  /* used क्रम calibration, basically a counter
				    * माला_लो incremented each समय a clamping
				    * period is completed without extra wakeups
				    * once that counter is reached given level,
				    * compensation is deemed usable.
				    */
	अचिन्हित दीर्घ steady_comp; /* steady state compensation used when
				    * no extra wakeups occurred.
				    */
	अचिन्हित दीर्घ dynamic_comp; /* compensate excessive wakeup from idle
				     * mostly from बाह्यal पूर्णांकerrupts.
				     */
पूर्ण;

अटल काष्ठा घातerclamp_calibration_data cal_data[MAX_TARGET_RATIO];

अटल पूर्णांक winकरोw_size_set(स्थिर अक्षर *arg, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ new_winकरोw_size;

	ret = kम_से_अदीर्घ(arg, 10, &new_winकरोw_size);
	अगर (ret)
		जाओ निकास_win;
	अगर (new_winकरोw_size > 10 || new_winकरोw_size < 2) अणु
		pr_err("Out of recommended window size %lu, between 2-10\n",
			new_winकरोw_size);
		ret = -EINVAL;
	पूर्ण

	winकरोw_size = clamp(new_winकरोw_size, 2ul, 10ul);
	smp_mb();

निकास_win:

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops winकरोw_size_ops = अणु
	.set = winकरोw_size_set,
	.get = param_get_पूर्णांक,
पूर्ण;

module_param_cb(winकरोw_size, &winकरोw_size_ops, &winकरोw_size, 0644);
MODULE_PARM_DESC(winकरोw_size, "sliding window in number of clamping cycles\n"
	"\tpowerclamp controls idle ratio within this window. larger\n"
	"\twindow size results in slower response time but more smooth\n"
	"\tclamping results. default to 2.");

अटल व्योम find_target_mरुको(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अचिन्हित पूर्णांक highest_cstate = 0;
	अचिन्हित पूर्णांक highest_subcstate = 0;
	पूर्णांक i;

	अगर (boot_cpu_data.cpuid_level < CPUID_MWAIT_LEAF)
		वापस;

	cpuid(CPUID_MWAIT_LEAF, &eax, &ebx, &ecx, &edx);

	अगर (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPORTED) ||
	    !(ecx & CPUID5_ECX_INTERRUPT_BREAK))
		वापस;

	edx >>= MWAIT_SUBSTATE_SIZE;
	क्रम (i = 0; i < 7 && edx; i++, edx >>= MWAIT_SUBSTATE_SIZE) अणु
		अगर (edx & MWAIT_SUBSTATE_MASK) अणु
			highest_cstate = i;
			highest_subcstate = edx & MWAIT_SUBSTATE_MASK;
		पूर्ण
	पूर्ण
	target_mरुको = (highest_cstate << MWAIT_SUBSTATE_SIZE) |
		(highest_subcstate - 1);

पूर्ण

काष्ठा pkg_cstate_info अणु
	bool skip;
	पूर्णांक msr_index;
	पूर्णांक cstate_id;
पूर्ण;

#घोषणा PKG_CSTATE_INIT(id) अणु				\
		.msr_index = MSR_PKG_C##id##_RESIDENCY, \
		.cstate_id = id				\
			पूर्ण

अटल काष्ठा pkg_cstate_info pkg_cstates[] = अणु
	PKG_CSTATE_INIT(2),
	PKG_CSTATE_INIT(3),
	PKG_CSTATE_INIT(6),
	PKG_CSTATE_INIT(7),
	PKG_CSTATE_INIT(8),
	PKG_CSTATE_INIT(9),
	PKG_CSTATE_INIT(10),
	अणुशून्यपूर्ण,
पूर्ण;

अटल bool has_pkg_state_counter(व्योम)
अणु
	u64 val;
	काष्ठा pkg_cstate_info *info = pkg_cstates;

	/* check अगर any one of the counter msrs exists */
	जबतक (info->msr_index) अणु
		अगर (!rdmsrl_safe(info->msr_index, &val))
			वापस true;
		info++;
	पूर्ण

	वापस false;
पूर्ण

अटल u64 pkg_state_counter(व्योम)
अणु
	u64 val;
	u64 count = 0;
	काष्ठा pkg_cstate_info *info = pkg_cstates;

	जबतक (info->msr_index) अणु
		अगर (!info->skip) अणु
			अगर (!rdmsrl_safe(info->msr_index, &val))
				count += val;
			अन्यथा
				info->skip = true;
		पूर्ण
		info++;
	पूर्ण

	वापस count;
पूर्ण

अटल अचिन्हित पूर्णांक get_compensation(पूर्णांक ratio)
अणु
	अचिन्हित पूर्णांक comp = 0;

	/* we only use compensation अगर all adjacent ones are good */
	अगर (ratio == 1 &&
		cal_data[ratio].confidence >= CONFIDENCE_OK &&
		cal_data[ratio + 1].confidence >= CONFIDENCE_OK &&
		cal_data[ratio + 2].confidence >= CONFIDENCE_OK) अणु
		comp = (cal_data[ratio].steady_comp +
			cal_data[ratio + 1].steady_comp +
			cal_data[ratio + 2].steady_comp) / 3;
	पूर्ण अन्यथा अगर (ratio == MAX_TARGET_RATIO - 1 &&
		cal_data[ratio].confidence >= CONFIDENCE_OK &&
		cal_data[ratio - 1].confidence >= CONFIDENCE_OK &&
		cal_data[ratio - 2].confidence >= CONFIDENCE_OK) अणु
		comp = (cal_data[ratio].steady_comp +
			cal_data[ratio - 1].steady_comp +
			cal_data[ratio - 2].steady_comp) / 3;
	पूर्ण अन्यथा अगर (cal_data[ratio].confidence >= CONFIDENCE_OK &&
		cal_data[ratio - 1].confidence >= CONFIDENCE_OK &&
		cal_data[ratio + 1].confidence >= CONFIDENCE_OK) अणु
		comp = (cal_data[ratio].steady_comp +
			cal_data[ratio - 1].steady_comp +
			cal_data[ratio + 1].steady_comp) / 3;
	पूर्ण

	/* REVISIT: simple penalty of द्विगुन idle injection */
	अगर (reduce_irq)
		comp = ratio;
	/* करो not exceed limit */
	अगर (comp + ratio >= MAX_TARGET_RATIO)
		comp = MAX_TARGET_RATIO - ratio - 1;

	वापस comp;
पूर्ण

अटल व्योम adjust_compensation(पूर्णांक target_ratio, अचिन्हित पूर्णांक win)
अणु
	पूर्णांक delta;
	काष्ठा घातerclamp_calibration_data *d = &cal_data[target_ratio];

	/*
	 * adjust compensations अगर confidence level has not been reached or
	 * there are too many wakeups during the last idle injection period, we
	 * cannot trust the data क्रम compensation.
	 */
	अगर (d->confidence >= CONFIDENCE_OK ||
		atomic_पढ़ो(&idle_wakeup_counter) >
		win * num_online_cpus())
		वापस;

	delta = set_target_ratio - current_ratio;
	/* filter out bad data */
	अगर (delta >= 0 && delta <= (1+target_ratio/10)) अणु
		अगर (d->steady_comp)
			d->steady_comp =
				roundup(delta+d->steady_comp, 2)/2;
		अन्यथा
			d->steady_comp = delta;
		d->confidence++;
	पूर्ण
पूर्ण

अटल bool घातerclamp_adjust_controls(अचिन्हित पूर्णांक target_ratio,
				अचिन्हित पूर्णांक guard, अचिन्हित पूर्णांक win)
अणु
	अटल u64 msr_last, tsc_last;
	u64 msr_now, tsc_now;
	u64 val64;

	/* check result क्रम the last winकरोw */
	msr_now = pkg_state_counter();
	tsc_now = rdtsc();

	/* calculate pkg cstate vs tsc ratio */
	अगर (!msr_last || !tsc_last)
		current_ratio = 1;
	अन्यथा अगर (tsc_now-tsc_last) अणु
		val64 = 100*(msr_now-msr_last);
		करो_भाग(val64, (tsc_now-tsc_last));
		current_ratio = val64;
	पूर्ण

	/* update record */
	msr_last = msr_now;
	tsc_last = tsc_now;

	adjust_compensation(target_ratio, win);
	/*
	 * too many बाह्यal पूर्णांकerrupts, set flag such
	 * that we can take measure later.
	 */
	reduce_irq = atomic_पढ़ो(&idle_wakeup_counter) >=
		2 * win * num_online_cpus();

	atomic_set(&idle_wakeup_counter, 0);
	/* अगर we are above target+guard, skip */
	वापस set_target_ratio + guard <= current_ratio;
पूर्ण

अटल व्योम clamp_balancing_func(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा घातerclamp_worker_data *w_data;
	पूर्णांक sleepसमय;
	अचिन्हित दीर्घ target_jअगरfies;
	अचिन्हित पूर्णांक compensated_ratio;
	पूर्णांक पूर्णांकerval; /* jअगरfies to sleep क्रम each attempt */

	w_data = container_of(work, काष्ठा घातerclamp_worker_data,
			      balancing_work);

	/*
	 * make sure user selected ratio करोes not take effect until
	 * the next round. adjust target_ratio अगर user has changed
	 * target such that we can converge quickly.
	 */
	w_data->target_ratio = READ_ONCE(set_target_ratio);
	w_data->guard = 1 + w_data->target_ratio / 20;
	w_data->winकरोw_size_now = winकरोw_size;
	w_data->duration_jअगरfies = msecs_to_jअगरfies(duration);
	w_data->count++;

	/*
	 * प्रणालीs may have dअगरferent ability to enter package level
	 * c-states, thus we need to compensate the injected idle ratio
	 * to achieve the actual target reported by the HW.
	 */
	compensated_ratio = w_data->target_ratio +
		get_compensation(w_data->target_ratio);
	अगर (compensated_ratio <= 0)
		compensated_ratio = 1;
	पूर्णांकerval = w_data->duration_jअगरfies * 100 / compensated_ratio;

	/* align idle समय */
	target_jअगरfies = roundup(jअगरfies, पूर्णांकerval);
	sleepसमय = target_jअगरfies - jअगरfies;
	अगर (sleepसमय <= 0)
		sleepसमय = 1;

	अगर (clamping && w_data->clamping && cpu_online(w_data->cpu))
		kthपढ़ो_queue_delayed_work(w_data->worker,
					   &w_data->idle_injection_work,
					   sleepसमय);
पूर्ण

अटल व्योम clamp_idle_injection_func(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा घातerclamp_worker_data *w_data;

	w_data = container_of(work, काष्ठा घातerclamp_worker_data,
			      idle_injection_work.work);

	/*
	 * only elected controlling cpu can collect stats and update
	 * control parameters.
	 */
	अगर (w_data->cpu == control_cpu &&
	    !(w_data->count % w_data->winकरोw_size_now)) अणु
		should_skip =
			घातerclamp_adjust_controls(w_data->target_ratio,
						   w_data->guard,
						   w_data->winकरोw_size_now);
		smp_mb();
	पूर्ण

	अगर (should_skip)
		जाओ balance;

	play_idle(jअगरfies_to_usecs(w_data->duration_jअगरfies));

balance:
	अगर (clamping && w_data->clamping && cpu_online(w_data->cpu))
		kthपढ़ो_queue_work(w_data->worker, &w_data->balancing_work);
पूर्ण

/*
 * 1 HZ polling जबतक clamping is active, useful क्रम userspace
 * to monitor actual idle ratio.
 */
अटल व्योम poll_pkg_cstate(काष्ठा work_काष्ठा *dummy);
अटल DECLARE_DELAYED_WORK(poll_pkg_cstate_work, poll_pkg_cstate);
अटल व्योम poll_pkg_cstate(काष्ठा work_काष्ठा *dummy)
अणु
	अटल u64 msr_last;
	अटल u64 tsc_last;

	u64 msr_now;
	u64 tsc_now;
	u64 val64;

	msr_now = pkg_state_counter();
	tsc_now = rdtsc();

	/* calculate pkg cstate vs tsc ratio */
	अगर (!msr_last || !tsc_last)
		pkg_cstate_ratio_cur = 1;
	अन्यथा अणु
		अगर (tsc_now - tsc_last) अणु
			val64 = 100 * (msr_now - msr_last);
			करो_भाग(val64, (tsc_now - tsc_last));
			pkg_cstate_ratio_cur = val64;
		पूर्ण
	पूर्ण

	/* update record */
	msr_last = msr_now;
	tsc_last = tsc_now;

	अगर (true == clamping)
		schedule_delayed_work(&poll_pkg_cstate_work, HZ);
पूर्ण

अटल व्योम start_घातer_clamp_worker(अचिन्हित दीर्घ cpu)
अणु
	काष्ठा घातerclamp_worker_data *w_data = per_cpu_ptr(worker_data, cpu);
	काष्ठा kthपढ़ो_worker *worker;

	worker = kthपढ़ो_create_worker_on_cpu(cpu, 0, "kidle_inj/%ld", cpu);
	अगर (IS_ERR(worker))
		वापस;

	w_data->worker = worker;
	w_data->count = 0;
	w_data->cpu = cpu;
	w_data->clamping = true;
	set_bit(cpu, cpu_clamping_mask);
	sched_set_fअगरo(worker->task);
	kthपढ़ो_init_work(&w_data->balancing_work, clamp_balancing_func);
	kthपढ़ो_init_delayed_work(&w_data->idle_injection_work,
				  clamp_idle_injection_func);
	kthपढ़ो_queue_work(w_data->worker, &w_data->balancing_work);
पूर्ण

अटल व्योम stop_घातer_clamp_worker(अचिन्हित दीर्घ cpu)
अणु
	काष्ठा घातerclamp_worker_data *w_data = per_cpu_ptr(worker_data, cpu);

	अगर (!w_data->worker)
		वापस;

	w_data->clamping = false;
	/*
	 * Make sure that all works that get queued after this poपूर्णांक see
	 * the clamping disabled. The counter part is not needed because
	 * there is an implicit memory barrier when the queued work
	 * is proceed.
	 */
	smp_wmb();
	kthपढ़ो_cancel_work_sync(&w_data->balancing_work);
	kthपढ़ो_cancel_delayed_work_sync(&w_data->idle_injection_work);
	/*
	 * The balancing work still might be queued here because
	 * the handling of the "clapming" variable, cancel, and queue
	 * operations are not synchronized via a lock. But it is not
	 * a big deal. The balancing work is fast and destroy kthपढ़ो
	 * will रुको क्रम it.
	 */
	clear_bit(w_data->cpu, cpu_clamping_mask);
	kthपढ़ो_destroy_worker(w_data->worker);

	w_data->worker = शून्य;
पूर्ण

अटल पूर्णांक start_घातer_clamp(व्योम)
अणु
	अचिन्हित दीर्घ cpu;

	set_target_ratio = clamp(set_target_ratio, 0U, MAX_TARGET_RATIO - 1);
	/* prevent cpu hotplug */
	get_online_cpus();

	/* prefer BSP */
	control_cpu = 0;
	अगर (!cpu_online(control_cpu))
		control_cpu = smp_processor_id();

	clamping = true;
	schedule_delayed_work(&poll_pkg_cstate_work, 0);

	/* start one kthपढ़ो worker per online cpu */
	क्रम_each_online_cpu(cpu) अणु
		start_घातer_clamp_worker(cpu);
	पूर्ण
	put_online_cpus();

	वापस 0;
पूर्ण

अटल व्योम end_घातer_clamp(व्योम)
अणु
	पूर्णांक i;

	/*
	 * Block requeuing in all the kthपढ़ो workers. They will flush and
	 * stop faster.
	 */
	clamping = false;
	अगर (biपंचांगap_weight(cpu_clamping_mask, num_possible_cpus())) अणु
		क्रम_each_set_bit(i, cpu_clamping_mask, num_possible_cpus()) अणु
			pr_debug("clamping worker for cpu %d alive, destroy\n",
				 i);
			stop_घातer_clamp_worker(i);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक घातerclamp_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अगर (clamping == false)
		वापस 0;
	start_घातer_clamp_worker(cpu);
	/* prefer BSP as controlling CPU */
	अगर (cpu == 0) अणु
		control_cpu = 0;
		smp_mb();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक घातerclamp_cpu_preकरोwn(अचिन्हित पूर्णांक cpu)
अणु
	अगर (clamping == false)
		वापस 0;

	stop_घातer_clamp_worker(cpu);
	अगर (cpu != control_cpu)
		वापस 0;

	control_cpu = cpumask_first(cpu_online_mask);
	अगर (control_cpu == cpu)
		control_cpu = cpumask_next(cpu, cpu_online_mask);
	smp_mb();
	वापस 0;
पूर्ण

अटल पूर्णांक घातerclamp_get_max_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	*state = MAX_TARGET_RATIO;

	वापस 0;
पूर्ण

अटल पूर्णांक घातerclamp_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	अगर (true == clamping)
		*state = pkg_cstate_ratio_cur;
	अन्यथा
		/* to save घातer, करो not poll idle ratio जबतक not clamping */
		*state = -1; /* indicates invalid state */

	वापस 0;
पूर्ण

अटल पूर्णांक घातerclamp_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ new_target_ratio)
अणु
	पूर्णांक ret = 0;

	new_target_ratio = clamp(new_target_ratio, 0UL,
				(अचिन्हित दीर्घ) (MAX_TARGET_RATIO-1));
	अगर (set_target_ratio == 0 && new_target_ratio > 0) अणु
		pr_info("Start idle injection to reduce power\n");
		set_target_ratio = new_target_ratio;
		ret = start_घातer_clamp();
		जाओ निकास_set;
	पूर्ण अन्यथा	अगर (set_target_ratio > 0 && new_target_ratio == 0) अणु
		pr_info("Stop forced idle injection\n");
		end_घातer_clamp();
		set_target_ratio = 0;
	पूर्ण अन्यथा	/* adjust currently running */ अणु
		set_target_ratio = new_target_ratio;
		/* make new set_target_ratio visible to other cpus */
		smp_mb();
	पूर्ण

निकास_set:
	वापस ret;
पूर्ण

/* bind to generic thermal layer as cooling device*/
अटल काष्ठा thermal_cooling_device_ops घातerclamp_cooling_ops = अणु
	.get_max_state = घातerclamp_get_max_state,
	.get_cur_state = घातerclamp_get_cur_state,
	.set_cur_state = घातerclamp_set_cur_state,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id __initस्थिर पूर्णांकel_घातerclamp_ids[] = अणु
	X86_MATCH_VENDOR_FEATURE(INTEL, X86_FEATURE_MWAIT, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, पूर्णांकel_घातerclamp_ids);

अटल पूर्णांक __init घातerclamp_probe(व्योम)
अणु

	अगर (!x86_match_cpu(पूर्णांकel_घातerclamp_ids)) अणु
		pr_err("CPU does not support MWAIT\n");
		वापस -ENODEV;
	पूर्ण

	/* The goal क्रम idle समय alignment is to achieve package cstate. */
	अगर (!has_pkg_state_counter()) अणु
		pr_info("No package C-state available\n");
		वापस -ENODEV;
	पूर्ण

	/* find the deepest mरुको value */
	find_target_mरुको();

	वापस 0;
पूर्ण

अटल पूर्णांक घातerclamp_debug_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	पूर्णांक i = 0;

	seq_म_लिखो(m, "controlling cpu: %d\n", control_cpu);
	seq_म_लिखो(m, "pct confidence steady dynamic (compensation)\n");
	क्रम (i = 0; i < MAX_TARGET_RATIO; i++) अणु
		seq_म_लिखो(m, "%d\t%lu\t%lu\t%lu\n",
			i,
			cal_data[i].confidence,
			cal_data[i].steady_comp,
			cal_data[i].dynamic_comp);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(घातerclamp_debug);

अटल अंतरभूत व्योम घातerclamp_create_debug_files(व्योम)
अणु
	debug_dir = debugfs_create_dir("intel_powerclamp", शून्य);

	debugfs_create_file("powerclamp_calib", S_IRUGO, debug_dir, cal_data,
			    &घातerclamp_debug_fops);
पूर्ण

अटल क्रमागत cpuhp_state hp_state;

अटल पूर्णांक __init घातerclamp_init(व्योम)
अणु
	पूर्णांक retval;
	पूर्णांक biपंचांगap_size;

	biपंचांगap_size = BITS_TO_LONGS(num_possible_cpus()) * माप(दीर्घ);
	cpu_clamping_mask = kzalloc(biपंचांगap_size, GFP_KERNEL);
	अगर (!cpu_clamping_mask)
		वापस -ENOMEM;

	/* probe cpu features and ids here */
	retval = घातerclamp_probe();
	अगर (retval)
		जाओ निकास_मुक्त;

	/* set शेष limit, maybe adjusted during runसमय based on feedback */
	winकरोw_size = 2;
	retval = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					   "thermal/intel_powerclamp:online",
					   घातerclamp_cpu_online,
					   घातerclamp_cpu_preकरोwn);
	अगर (retval < 0)
		जाओ निकास_मुक्त;

	hp_state = retval;

	worker_data = alloc_percpu(काष्ठा घातerclamp_worker_data);
	अगर (!worker_data) अणु
		retval = -ENOMEM;
		जाओ निकास_unरेजिस्टर;
	पूर्ण

	cooling_dev = thermal_cooling_device_रेजिस्टर("intel_powerclamp", शून्य,
						&घातerclamp_cooling_ops);
	अगर (IS_ERR(cooling_dev)) अणु
		retval = -ENODEV;
		जाओ निकास_मुक्त_thपढ़ो;
	पूर्ण

	अगर (!duration)
		duration = jअगरfies_to_msecs(DEFAULT_DURATION_JIFFIES);

	घातerclamp_create_debug_files();

	वापस 0;

निकास_मुक्त_thपढ़ो:
	मुक्त_percpu(worker_data);
निकास_unरेजिस्टर:
	cpuhp_हटाओ_state_nocalls(hp_state);
निकास_मुक्त:
	kमुक्त(cpu_clamping_mask);
	वापस retval;
पूर्ण
module_init(घातerclamp_init);

अटल व्योम __निकास घातerclamp_निकास(व्योम)
अणु
	end_घातer_clamp();
	cpuhp_हटाओ_state_nocalls(hp_state);
	मुक्त_percpu(worker_data);
	thermal_cooling_device_unरेजिस्टर(cooling_dev);
	kमुक्त(cpu_clamping_mask);

	cancel_delayed_work_sync(&poll_pkg_cstate_work);
	debugfs_हटाओ_recursive(debug_dir);
पूर्ण
module_निकास(घातerclamp_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arjan van de Ven <arjan@linux.intel.com>");
MODULE_AUTHOR("Jacob Pan <jacob.jun.pan@linux.intel.com>");
MODULE_DESCRIPTION("Package Level C-state Idle Injection for Intel CPUs");

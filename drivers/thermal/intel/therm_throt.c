<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Thermal throttle event support code (such as syslog messaging and rate
 * limiting) that was factored out from x86_64 (mce_पूर्णांकel.c) and i386 (p4.c).
 *
 * This allows consistent reporting of CPU thermal throttle events.
 *
 * Maपूर्णांकains a counter in /sys that keeps track of the number of thermal
 * events, such that the user knows how bad the thermal problem might be
 * (since the logging to syslog is rate limited).
 *
 * Author: Dmitriy Zavin (dmitriyz@google.com)
 *
 * Credits: Adapted from Zwane Mwaikambo's original code in mce_पूर्णांकel.c.
 *          Inspired by Ross Biro's and Al Borchers' counter code.
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/thermal.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/msr.h>

#समावेश "thermal_interrupt.h"

/* How दीर्घ to रुको between reporting thermal events */
#घोषणा CHECK_INTERVAL		(300 * HZ)

#घोषणा THERMAL_THROTTLING_EVENT	0
#घोषणा POWER_LIMIT_EVENT		1

/**
 * काष्ठा _thermal_state - Represent the current thermal event state
 * @next_check:			Stores the next बारtamp, when it is allowed
 *				to log the next warning message.
 * @last_पूर्णांकerrupt_समय:	Stores the बारtamp क्रम the last threshold
 *				high event.
 * @therm_work:			Delayed workqueue काष्ठाure
 * @count:			Stores the current running count क्रम thermal
 *				or घातer threshold पूर्णांकerrupts.
 * @last_count:			Stores the previous running count क्रम thermal
 *				or घातer threshold पूर्णांकerrupts.
 * @max_समय_ms:		This shows the maximum amount of समय CPU was
 *				in throttled state क्रम a single thermal
 *				threshold high to low state.
 * @total_समय_ms:		This is a cumulative समय during which CPU was
 *				in the throttled state.
 * @rate_control_active:	Set when a throttling message is logged.
 *				This is used क्रम the purpose of rate-control.
 * @new_event:			Stores the last high/low status of the
 *				THERM_STATUS_PROCHOT or
 *				THERM_STATUS_POWER_LIMIT.
 * @level:			Stores whether this _thermal_state instance is
 *				क्रम a CORE level or क्रम PACKAGE level.
 * @sample_index:		Index क्रम storing the next sample in the buffer
 *				temp_samples[].
 * @sample_count:		Total number of samples collected in the buffer
 *				temp_samples[].
 * @average:			The last moving average of temperature samples
 * @baseline_temp:		Temperature at which thermal threshold high
 *				पूर्णांकerrupt was generated.
 * @temp_samples:		Storage क्रम temperature samples to calculate
 *				moving average.
 *
 * This काष्ठाure is used to represent data related to thermal state क्रम a CPU.
 * There is a separate storage क्रम core and package level क्रम each CPU.
 */
काष्ठा _thermal_state अणु
	u64			next_check;
	u64			last_पूर्णांकerrupt_समय;
	काष्ठा delayed_work	therm_work;
	अचिन्हित दीर्घ		count;
	अचिन्हित दीर्घ		last_count;
	अचिन्हित दीर्घ		max_समय_ms;
	अचिन्हित दीर्घ		total_समय_ms;
	bool			rate_control_active;
	bool			new_event;
	u8			level;
	u8			sample_index;
	u8			sample_count;
	u8			average;
	u8			baseline_temp;
	u8			temp_samples[3];
पूर्ण;

काष्ठा thermal_state अणु
	काष्ठा _thermal_state core_throttle;
	काष्ठा _thermal_state core_घातer_limit;
	काष्ठा _thermal_state package_throttle;
	काष्ठा _thermal_state package_घातer_limit;
	काष्ठा _thermal_state core_thresh0;
	काष्ठा _thermal_state core_thresh1;
	काष्ठा _thermal_state pkg_thresh0;
	काष्ठा _thermal_state pkg_thresh1;
पूर्ण;

/* Callback to handle core threshold पूर्णांकerrupts */
पूर्णांक (*platक्रमm_thermal_notअगरy)(__u64 msr_val);
EXPORT_SYMBOL(platक्रमm_thermal_notअगरy);

/* Callback to handle core package threshold_पूर्णांकerrupts */
पूर्णांक (*platक्रमm_thermal_package_notअगरy)(__u64 msr_val);
EXPORT_SYMBOL_GPL(platक्रमm_thermal_package_notअगरy);

/* Callback support of rate control, वापस true, अगर
 * callback has rate control */
bool (*platक्रमm_thermal_package_rate_control)(व्योम);
EXPORT_SYMBOL_GPL(platक्रमm_thermal_package_rate_control);


अटल DEFINE_PER_CPU(काष्ठा thermal_state, thermal_state);

अटल atomic_t therm_throt_en	= ATOMIC_INIT(0);

अटल u32 lvtthmr_init __पढ़ो_mostly;

#अगर_घोषित CONFIG_SYSFS
#घोषणा define_therm_throt_device_one_ro(_name)				\
	अटल DEVICE_ATTR(_name, 0444,					\
			   therm_throt_device_show_##_name,		\
				   शून्य)				\

#घोषणा define_therm_throt_device_show_func(event, name)		\
									\
अटल sमाप_प्रकार therm_throt_device_show_##event##_##name(		\
			काष्ठा device *dev,				\
			काष्ठा device_attribute *attr,			\
			अक्षर *buf)					\
अणु									\
	अचिन्हित पूर्णांक cpu = dev->id;					\
	sमाप_प्रकार ret;							\
									\
	preempt_disable();	/* CPU hotplug */			\
	अगर (cpu_online(cpu)) अणु						\
		ret = प्र_लिखो(buf, "%lu\n",				\
			      per_cpu(thermal_state, cpu).event.name);	\
	पूर्ण अन्यथा								\
		ret = 0;						\
	preempt_enable();						\
									\
	वापस ret;							\
पूर्ण

define_therm_throt_device_show_func(core_throttle, count);
define_therm_throt_device_one_ro(core_throttle_count);

define_therm_throt_device_show_func(core_घातer_limit, count);
define_therm_throt_device_one_ro(core_घातer_limit_count);

define_therm_throt_device_show_func(package_throttle, count);
define_therm_throt_device_one_ro(package_throttle_count);

define_therm_throt_device_show_func(package_घातer_limit, count);
define_therm_throt_device_one_ro(package_घातer_limit_count);

define_therm_throt_device_show_func(core_throttle, max_समय_ms);
define_therm_throt_device_one_ro(core_throttle_max_समय_ms);

define_therm_throt_device_show_func(package_throttle, max_समय_ms);
define_therm_throt_device_one_ro(package_throttle_max_समय_ms);

define_therm_throt_device_show_func(core_throttle, total_समय_ms);
define_therm_throt_device_one_ro(core_throttle_total_समय_ms);

define_therm_throt_device_show_func(package_throttle, total_समय_ms);
define_therm_throt_device_one_ro(package_throttle_total_समय_ms);

अटल काष्ठा attribute *thermal_throttle_attrs[] = अणु
	&dev_attr_core_throttle_count.attr,
	&dev_attr_core_throttle_max_समय_ms.attr,
	&dev_attr_core_throttle_total_समय_ms.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group thermal_attr_group = अणु
	.attrs	= thermal_throttle_attrs,
	.name	= "thermal_throttle"
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSFS */

#घोषणा CORE_LEVEL	0
#घोषणा PACKAGE_LEVEL	1

#घोषणा THERM_THROT_POLL_INTERVAL	HZ
#घोषणा THERM_STATUS_PROCHOT_LOG	BIT(1)

#घोषणा THERM_STATUS_CLEAR_CORE_MASK (BIT(1) | BIT(3) | BIT(5) | BIT(7) | BIT(9) | BIT(11) | BIT(13) | BIT(15))
#घोषणा THERM_STATUS_CLEAR_PKG_MASK  (BIT(1) | BIT(3) | BIT(5) | BIT(7) | BIT(9) | BIT(11))

अटल व्योम clear_therm_status_log(पूर्णांक level)
अणु
	पूर्णांक msr;
	u64 mask, msr_val;

	अगर (level == CORE_LEVEL) अणु
		msr  = MSR_IA32_THERM_STATUS;
		mask = THERM_STATUS_CLEAR_CORE_MASK;
	पूर्ण अन्यथा अणु
		msr  = MSR_IA32_PACKAGE_THERM_STATUS;
		mask = THERM_STATUS_CLEAR_PKG_MASK;
	पूर्ण

	rdmsrl(msr, msr_val);
	msr_val &= mask;
	wrmsrl(msr, msr_val & ~THERM_STATUS_PROCHOT_LOG);
पूर्ण

अटल व्योम get_therm_status(पूर्णांक level, bool *proc_hot, u8 *temp)
अणु
	पूर्णांक msr;
	u64 msr_val;

	अगर (level == CORE_LEVEL)
		msr = MSR_IA32_THERM_STATUS;
	अन्यथा
		msr = MSR_IA32_PACKAGE_THERM_STATUS;

	rdmsrl(msr, msr_val);
	अगर (msr_val & THERM_STATUS_PROCHOT_LOG)
		*proc_hot = true;
	अन्यथा
		*proc_hot = false;

	*temp = (msr_val >> 16) & 0x7F;
पूर्ण

अटल व्योम __maybe_unused throttle_active_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा _thermal_state *state = container_of(to_delayed_work(work),
						काष्ठा _thermal_state, therm_work);
	अचिन्हित पूर्णांक i, avg, this_cpu = smp_processor_id();
	u64 now = get_jअगरfies_64();
	bool hot;
	u8 temp;

	get_therm_status(state->level, &hot, &temp);
	/* temperature value is offset from the max so lesser means hotter */
	अगर (!hot && temp > state->baseline_temp) अणु
		अगर (state->rate_control_active)
			pr_info("CPU%d: %s temperature/speed normal (total events = %lu)\n",
				this_cpu,
				state->level == CORE_LEVEL ? "Core" : "Package",
				state->count);

		state->rate_control_active = false;
		वापस;
	पूर्ण

	अगर (समय_beक्रमe64(now, state->next_check) &&
			  state->rate_control_active)
		जाओ re_arm;

	state->next_check = now + CHECK_INTERVAL;

	अगर (state->count != state->last_count) अणु
		/* There was one new thermal पूर्णांकerrupt */
		state->last_count = state->count;
		state->average = 0;
		state->sample_count = 0;
		state->sample_index = 0;
	पूर्ण

	state->temp_samples[state->sample_index] = temp;
	state->sample_count++;
	state->sample_index = (state->sample_index + 1) % ARRAY_SIZE(state->temp_samples);
	अगर (state->sample_count < ARRAY_SIZE(state->temp_samples))
		जाओ re_arm;

	avg = 0;
	क्रम (i = 0; i < ARRAY_SIZE(state->temp_samples); ++i)
		avg += state->temp_samples[i];

	avg /= ARRAY_SIZE(state->temp_samples);

	अगर (state->average > avg) अणु
		pr_warn("CPU%d: %s temperature is above threshold, cpu clock is throttled (total events = %lu)\n",
			this_cpu,
			state->level == CORE_LEVEL ? "Core" : "Package",
			state->count);
		state->rate_control_active = true;
	पूर्ण

	state->average = avg;

re_arm:
	clear_therm_status_log(state->level);
	schedule_delayed_work_on(this_cpu, &state->therm_work, THERM_THROT_POLL_INTERVAL);
पूर्ण

/***
 * therm_throt_process - Process thermal throttling event from पूर्णांकerrupt
 * @curr: Whether the condition is current or not (boolean), since the
 *        thermal पूर्णांकerrupt normally माला_लो called both when the thermal
 *        event begins and once the event has ended.
 *
 * This function is called by the thermal पूर्णांकerrupt after the
 * IRQ has been acknowledged.
 *
 * It will take care of rate limiting and prपूर्णांकing messages to the syslog.
 */
अटल व्योम therm_throt_process(bool new_event, पूर्णांक event, पूर्णांक level)
अणु
	काष्ठा _thermal_state *state;
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	bool old_event;
	u64 now;
	काष्ठा thermal_state *pstate = &per_cpu(thermal_state, this_cpu);

	now = get_jअगरfies_64();
	अगर (level == CORE_LEVEL) अणु
		अगर (event == THERMAL_THROTTLING_EVENT)
			state = &pstate->core_throttle;
		अन्यथा अगर (event == POWER_LIMIT_EVENT)
			state = &pstate->core_घातer_limit;
		अन्यथा
			वापस;
	पूर्ण अन्यथा अगर (level == PACKAGE_LEVEL) अणु
		अगर (event == THERMAL_THROTTLING_EVENT)
			state = &pstate->package_throttle;
		अन्यथा अगर (event == POWER_LIMIT_EVENT)
			state = &pstate->package_घातer_limit;
		अन्यथा
			वापस;
	पूर्ण अन्यथा
		वापस;

	old_event = state->new_event;
	state->new_event = new_event;

	अगर (new_event)
		state->count++;

	अगर (event != THERMAL_THROTTLING_EVENT)
		वापस;

	अगर (new_event && !state->last_पूर्णांकerrupt_समय) अणु
		bool hot;
		u8 temp;

		get_therm_status(state->level, &hot, &temp);
		/*
		 * Ignore लघु temperature spike as the प्रणाली is not बंद
		 * to PROCHOT. 10C offset is large enough to ignore. It is
		 * alपढ़ोy dropped from the high threshold temperature.
		 */
		अगर (temp > 10)
			वापस;

		state->baseline_temp = temp;
		state->last_पूर्णांकerrupt_समय = now;
		schedule_delayed_work_on(this_cpu, &state->therm_work, THERM_THROT_POLL_INTERVAL);
	पूर्ण अन्यथा अगर (old_event && state->last_पूर्णांकerrupt_समय) अणु
		अचिन्हित दीर्घ throttle_समय;

		throttle_समय = jअगरfies_delta_to_msecs(now - state->last_पूर्णांकerrupt_समय);
		अगर (throttle_समय > state->max_समय_ms)
			state->max_समय_ms = throttle_समय;
		state->total_समय_ms += throttle_समय;
		state->last_पूर्णांकerrupt_समय = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक thresh_event_valid(पूर्णांक level, पूर्णांक event)
अणु
	काष्ठा _thermal_state *state;
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	काष्ठा thermal_state *pstate = &per_cpu(thermal_state, this_cpu);
	u64 now = get_jअगरfies_64();

	अगर (level == PACKAGE_LEVEL)
		state = (event == 0) ? &pstate->pkg_thresh0 :
						&pstate->pkg_thresh1;
	अन्यथा
		state = (event == 0) ? &pstate->core_thresh0 :
						&pstate->core_thresh1;

	अगर (समय_beक्रमe64(now, state->next_check))
		वापस 0;

	state->next_check = now + CHECK_INTERVAL;

	वापस 1;
पूर्ण

अटल bool पूर्णांक_pln_enable;
अटल पूर्णांक __init पूर्णांक_pln_enable_setup(अक्षर *s)
अणु
	पूर्णांक_pln_enable = true;

	वापस 1;
पूर्ण
__setup("int_pln_enable", पूर्णांक_pln_enable_setup);

#अगर_घोषित CONFIG_SYSFS
/* Add/Remove thermal_throttle पूर्णांकerface क्रम CPU device: */
अटल पूर्णांक thermal_throttle_add_dev(काष्ठा device *dev, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err;
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

	err = sysfs_create_group(&dev->kobj, &thermal_attr_group);
	अगर (err)
		वापस err;

	अगर (cpu_has(c, X86_FEATURE_PLN) && पूर्णांक_pln_enable) अणु
		err = sysfs_add_file_to_group(&dev->kobj,
					      &dev_attr_core_घातer_limit_count.attr,
					      thermal_attr_group.name);
		अगर (err)
			जाओ del_group;
	पूर्ण

	अगर (cpu_has(c, X86_FEATURE_PTS)) अणु
		err = sysfs_add_file_to_group(&dev->kobj,
					      &dev_attr_package_throttle_count.attr,
					      thermal_attr_group.name);
		अगर (err)
			जाओ del_group;

		err = sysfs_add_file_to_group(&dev->kobj,
					      &dev_attr_package_throttle_max_समय_ms.attr,
					      thermal_attr_group.name);
		अगर (err)
			जाओ del_group;

		err = sysfs_add_file_to_group(&dev->kobj,
					      &dev_attr_package_throttle_total_समय_ms.attr,
					      thermal_attr_group.name);
		अगर (err)
			जाओ del_group;

		अगर (cpu_has(c, X86_FEATURE_PLN) && पूर्णांक_pln_enable) अणु
			err = sysfs_add_file_to_group(&dev->kobj,
					&dev_attr_package_घातer_limit_count.attr,
					thermal_attr_group.name);
			अगर (err)
				जाओ del_group;
		पूर्ण
	पूर्ण

	वापस 0;

del_group:
	sysfs_हटाओ_group(&dev->kobj, &thermal_attr_group);

	वापस err;
पूर्ण

अटल व्योम thermal_throttle_हटाओ_dev(काष्ठा device *dev)
अणु
	sysfs_हटाओ_group(&dev->kobj, &thermal_attr_group);
पूर्ण

/* Get notअगरied when a cpu comes on/off. Be hotplug मित्रly. */
अटल पूर्णांक thermal_throttle_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा thermal_state *state = &per_cpu(thermal_state, cpu);
	काष्ठा device *dev = get_cpu_device(cpu);
	u32 l;

	state->package_throttle.level = PACKAGE_LEVEL;
	state->core_throttle.level = CORE_LEVEL;

	INIT_DELAYED_WORK(&state->package_throttle.therm_work, throttle_active_work);
	INIT_DELAYED_WORK(&state->core_throttle.therm_work, throttle_active_work);

	/* Unmask the thermal vector after the above workqueues are initialized. */
	l = apic_पढ़ो(APIC_LVTTHMR);
	apic_ग_लिखो(APIC_LVTTHMR, l & ~APIC_LVT_MASKED);

	वापस thermal_throttle_add_dev(dev, cpu);
पूर्ण

अटल पूर्णांक thermal_throttle_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा thermal_state *state = &per_cpu(thermal_state, cpu);
	काष्ठा device *dev = get_cpu_device(cpu);
	u32 l;

	/* Mask the thermal vector beक्रमe draining evtl. pending work */
	l = apic_पढ़ो(APIC_LVTTHMR);
	apic_ग_लिखो(APIC_LVTTHMR, l | APIC_LVT_MASKED);

	cancel_delayed_work_sync(&state->package_throttle.therm_work);
	cancel_delayed_work_sync(&state->core_throttle.therm_work);

	state->package_throttle.rate_control_active = false;
	state->core_throttle.rate_control_active = false;

	thermal_throttle_हटाओ_dev(dev);
	वापस 0;
पूर्ण

अटल __init पूर्णांक thermal_throttle_init_device(व्योम)
अणु
	पूर्णांक ret;

	अगर (!atomic_पढ़ो(&therm_throt_en))
		वापस 0;

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "x86/therm:online",
				thermal_throttle_online,
				thermal_throttle_offline);
	वापस ret < 0 ? ret : 0;
पूर्ण
device_initcall(thermal_throttle_init_device);

#पूर्ण_अगर /* CONFIG_SYSFS */

अटल व्योम notअगरy_package_thresholds(__u64 msr_val)
अणु
	bool notअगरy_thres_0 = false;
	bool notअगरy_thres_1 = false;

	अगर (!platक्रमm_thermal_package_notअगरy)
		वापस;

	/* lower threshold check */
	अगर (msr_val & THERM_LOG_THRESHOLD0)
		notअगरy_thres_0 = true;
	/* higher threshold check */
	अगर (msr_val & THERM_LOG_THRESHOLD1)
		notअगरy_thres_1 = true;

	अगर (!notअगरy_thres_0 && !notअगरy_thres_1)
		वापस;

	अगर (platक्रमm_thermal_package_rate_control &&
		platक्रमm_thermal_package_rate_control()) अणु
		/* Rate control is implemented in callback */
		platक्रमm_thermal_package_notअगरy(msr_val);
		वापस;
	पूर्ण

	/* lower threshold reached */
	अगर (notअगरy_thres_0 && thresh_event_valid(PACKAGE_LEVEL, 0))
		platक्रमm_thermal_package_notअगरy(msr_val);
	/* higher threshold reached */
	अगर (notअगरy_thres_1 && thresh_event_valid(PACKAGE_LEVEL, 1))
		platक्रमm_thermal_package_notअगरy(msr_val);
पूर्ण

अटल व्योम notअगरy_thresholds(__u64 msr_val)
अणु
	/* check whether the पूर्णांकerrupt handler is defined;
	 * otherwise simply वापस
	 */
	अगर (!platक्रमm_thermal_notअगरy)
		वापस;

	/* lower threshold reached */
	अगर ((msr_val & THERM_LOG_THRESHOLD0) &&
			thresh_event_valid(CORE_LEVEL, 0))
		platक्रमm_thermal_notअगरy(msr_val);
	/* higher threshold reached */
	अगर ((msr_val & THERM_LOG_THRESHOLD1) &&
			thresh_event_valid(CORE_LEVEL, 1))
		platक्रमm_thermal_notअगरy(msr_val);
पूर्ण

/* Thermal transition पूर्णांकerrupt handler */
व्योम पूर्णांकel_thermal_पूर्णांकerrupt(व्योम)
अणु
	__u64 msr_val;

	अगर (अटल_cpu_has(X86_FEATURE_HWP))
		wrmsrl_safe(MSR_HWP_STATUS, 0);

	rdmsrl(MSR_IA32_THERM_STATUS, msr_val);

	/* Check क्रम violation of core thermal thresholds*/
	notअगरy_thresholds(msr_val);

	therm_throt_process(msr_val & THERM_STATUS_PROCHOT,
			    THERMAL_THROTTLING_EVENT,
			    CORE_LEVEL);

	अगर (this_cpu_has(X86_FEATURE_PLN) && पूर्णांक_pln_enable)
		therm_throt_process(msr_val & THERM_STATUS_POWER_LIMIT,
					POWER_LIMIT_EVENT,
					CORE_LEVEL);

	अगर (this_cpu_has(X86_FEATURE_PTS)) अणु
		rdmsrl(MSR_IA32_PACKAGE_THERM_STATUS, msr_val);
		/* check violations of package thermal thresholds */
		notअगरy_package_thresholds(msr_val);
		therm_throt_process(msr_val & PACKAGE_THERM_STATUS_PROCHOT,
					THERMAL_THROTTLING_EVENT,
					PACKAGE_LEVEL);
		अगर (this_cpu_has(X86_FEATURE_PLN) && पूर्णांक_pln_enable)
			therm_throt_process(msr_val &
					PACKAGE_THERM_STATUS_POWER_LIMIT,
					POWER_LIMIT_EVENT,
					PACKAGE_LEVEL);
	पूर्ण
पूर्ण

/* Thermal monitoring depends on APIC, ACPI and घड़ी modulation */
अटल पूर्णांक पूर्णांकel_thermal_supported(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_APIC))
		वापस 0;
	अगर (!cpu_has(c, X86_FEATURE_ACPI) || !cpu_has(c, X86_FEATURE_ACC))
		वापस 0;
	वापस 1;
पूर्ण

bool x86_thermal_enabled(व्योम)
अणु
	वापस atomic_पढ़ो(&therm_throt_en);
पूर्ण

व्योम __init therm_lvt_init(व्योम)
अणु
	/*
	 * This function is only called on boot CPU. Save the init thermal
	 * LVT value on BSP and use that value to restore APs' thermal LVT
	 * entry BIOS programmed later
	 */
	अगर (पूर्णांकel_thermal_supported(&boot_cpu_data))
		lvtthmr_init = apic_पढ़ो(APIC_LVTTHMR);
पूर्ण

व्योम पूर्णांकel_init_thermal(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक पंचांग2 = 0;
	u32 l, h;

	अगर (!पूर्णांकel_thermal_supported(c))
		वापस;

	/*
	 * First check अगर its enabled alपढ़ोy, in which हाल there might
	 * be some SMM goo which handles it, so we can't even put a handler
	 * since it might be delivered via SMI alपढ़ोy:
	 */
	rdmsr(MSR_IA32_MISC_ENABLE, l, h);

	h = lvtthmr_init;
	/*
	 * The initial value of thermal LVT entries on all APs always पढ़ोs
	 * 0x10000 because APs are woken up by BSP issuing INIT-SIPI-SIPI
	 * sequence to them and LVT रेजिस्टरs are reset to 0s except क्रम
	 * the mask bits which are set to 1s when APs receive INIT IPI.
	 * If BIOS takes over the thermal पूर्णांकerrupt and sets its पूर्णांकerrupt
	 * delivery mode to SMI (not fixed), it restores the value that the
	 * BIOS has programmed on AP based on BSP's info we saved since BIOS
	 * is always setting the same value क्रम all thपढ़ोs/cores.
	 */
	अगर ((h & APIC_DM_FIXED_MASK) != APIC_DM_FIXED)
		apic_ग_लिखो(APIC_LVTTHMR, lvtthmr_init);


	अगर ((l & MSR_IA32_MISC_ENABLE_TM1) && (h & APIC_DM_SMI)) अणु
		अगर (प्रणाली_state == SYSTEM_BOOTING)
			pr_debug("CPU%d: Thermal monitoring handled by SMI\n", cpu);
		वापस;
	पूर्ण

	/* early Pentium M models use dअगरferent method क्रम enabling TM2 */
	अगर (cpu_has(c, X86_FEATURE_TM2)) अणु
		अगर (c->x86 == 6 && (c->x86_model == 9 || c->x86_model == 13)) अणु
			rdmsr(MSR_THERM2_CTL, l, h);
			अगर (l & MSR_THERM2_CTL_TM_SELECT)
				पंचांग2 = 1;
		पूर्ण अन्यथा अगर (l & MSR_IA32_MISC_ENABLE_TM2)
			पंचांग2 = 1;
	पूर्ण

	/* We'll mask the thermal vector in the lapic till we're पढ़ोy: */
	h = THERMAL_APIC_VECTOR | APIC_DM_FIXED | APIC_LVT_MASKED;
	apic_ग_लिखो(APIC_LVTTHMR, h);

	rdmsr(MSR_IA32_THERM_INTERRUPT, l, h);
	अगर (cpu_has(c, X86_FEATURE_PLN) && !पूर्णांक_pln_enable)
		wrmsr(MSR_IA32_THERM_INTERRUPT,
			(l | (THERM_INT_LOW_ENABLE
			| THERM_INT_HIGH_ENABLE)) & ~THERM_INT_PLN_ENABLE, h);
	अन्यथा अगर (cpu_has(c, X86_FEATURE_PLN) && पूर्णांक_pln_enable)
		wrmsr(MSR_IA32_THERM_INTERRUPT,
			l | (THERM_INT_LOW_ENABLE
			| THERM_INT_HIGH_ENABLE | THERM_INT_PLN_ENABLE), h);
	अन्यथा
		wrmsr(MSR_IA32_THERM_INTERRUPT,
		      l | (THERM_INT_LOW_ENABLE | THERM_INT_HIGH_ENABLE), h);

	अगर (cpu_has(c, X86_FEATURE_PTS)) अणु
		rdmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
		अगर (cpu_has(c, X86_FEATURE_PLN) && !पूर्णांक_pln_enable)
			wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT,
				(l | (PACKAGE_THERM_INT_LOW_ENABLE
				| PACKAGE_THERM_INT_HIGH_ENABLE))
				& ~PACKAGE_THERM_INT_PLN_ENABLE, h);
		अन्यथा अगर (cpu_has(c, X86_FEATURE_PLN) && पूर्णांक_pln_enable)
			wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT,
				l | (PACKAGE_THERM_INT_LOW_ENABLE
				| PACKAGE_THERM_INT_HIGH_ENABLE
				| PACKAGE_THERM_INT_PLN_ENABLE), h);
		अन्यथा
			wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT,
			      l | (PACKAGE_THERM_INT_LOW_ENABLE
				| PACKAGE_THERM_INT_HIGH_ENABLE), h);
	पूर्ण

	rdmsr(MSR_IA32_MISC_ENABLE, l, h);
	wrmsr(MSR_IA32_MISC_ENABLE, l | MSR_IA32_MISC_ENABLE_TM1, h);

	pr_info_once("CPU0: Thermal monitoring enabled (%s)\n",
		      पंचांग2 ? "TM2" : "TM1");

	/* enable thermal throttle processing */
	atomic_set(&therm_throt_en, 1);
पूर्ण

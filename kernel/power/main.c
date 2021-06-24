<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/घातer/मुख्य.c - PM subप्रणाली core functionality.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 */

#समावेश <linux/export.h>
#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/pm-trace.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "power.h"

#अगर_घोषित CONFIG_PM_SLEEP

व्योम lock_प्रणाली_sleep(व्योम)
अणु
	current->flags |= PF_FREEZER_SKIP;
	mutex_lock(&प्रणाली_transition_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(lock_प्रणाली_sleep);

व्योम unlock_प्रणाली_sleep(व्योम)
अणु
	/*
	 * Don't use freezer_count() because we don't want the call to
	 * try_to_मुक्तze() here.
	 *
	 * Reason:
	 * Fundamentally, we just करोn't need it, because मुक्तzing condition
	 * करोesn't come पूर्णांकo effect until we release the
	 * प्रणाली_transition_mutex lock, since the मुक्तzer always works with
	 * प्रणाली_transition_mutex held.
	 *
	 * More importantly, in the हाल of hibernation,
	 * unlock_प्रणाली_sleep() माला_लो called in snapshot_पढ़ो() and
	 * snapshot_ग_लिखो() when the मुक्तzing condition is still in effect.
	 * Which means, अगर we use try_to_मुक्तze() here, it would make them
	 * enter the refrigerator, thus causing hibernation to lockup.
	 */
	current->flags &= ~PF_FREEZER_SKIP;
	mutex_unlock(&प्रणाली_transition_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(unlock_प्रणाली_sleep);

व्योम ksys_sync_helper(व्योम)
अणु
	kसमय_प्रकार start;
	दीर्घ elapsed_msecs;

	start = kसमय_get();
	ksys_sync();
	elapsed_msecs = kसमय_प्रकारo_ms(kसमय_sub(kसमय_get(), start));
	pr_info("Filesystems sync: %ld.%03ld seconds\n",
		elapsed_msecs / MSEC_PER_SEC, elapsed_msecs % MSEC_PER_SEC);
पूर्ण
EXPORT_SYMBOL_GPL(ksys_sync_helper);

/* Routines क्रम PM-transition notअगरications */

अटल BLOCKING_NOTIFIER_HEAD(pm_chain_head);

पूर्णांक रेजिस्टर_pm_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&pm_chain_head, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_pm_notअगरier);

पूर्णांक unरेजिस्टर_pm_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&pm_chain_head, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_pm_notअगरier);

पूर्णांक pm_notअगरier_call_chain_robust(अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn)
अणु
	पूर्णांक ret;

	ret = blocking_notअगरier_call_chain_robust(&pm_chain_head, val_up, val_करोwn, शून्य);

	वापस notअगरier_to_त्रुटि_सं(ret);
पूर्ण

पूर्णांक pm_notअगरier_call_chain(अचिन्हित दीर्घ val)
अणु
	वापस blocking_notअगरier_call_chain(&pm_chain_head, val, शून्य);
पूर्ण

/* If set, devices may be suspended and resumed asynchronously. */
पूर्णांक pm_async_enabled = 1;

अटल sमाप_प्रकार pm_async_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", pm_async_enabled);
पूर्ण

अटल sमाप_प्रकार pm_async_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	अगर (val > 1)
		वापस -EINVAL;

	pm_async_enabled = val;
	वापस n;
पूर्ण

घातer_attr(pm_async);

#अगर_घोषित CONFIG_SUSPEND
अटल sमाप_प्रकार mem_sleep_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			      अक्षर *buf)
अणु
	अक्षर *s = buf;
	suspend_state_t i;

	क्रम (i = PM_SUSPEND_MIN; i < PM_SUSPEND_MAX; i++)
		अगर (mem_sleep_states[i]) अणु
			स्थिर अक्षर *label = mem_sleep_states[i];

			अगर (mem_sleep_current == i)
				s += प्र_लिखो(s, "[%s] ", label);
			अन्यथा
				s += प्र_लिखो(s, "%s ", label);
		पूर्ण

	/* Convert the last space to a newline अगर needed. */
	अगर (s != buf)
		*(s-1) = '\n';

	वापस (s - buf);
पूर्ण

अटल suspend_state_t decode_suspend_state(स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	suspend_state_t state;
	अक्षर *p;
	पूर्णांक len;

	p = स_प्रथम(buf, '\n', n);
	len = p ? p - buf : n;

	क्रम (state = PM_SUSPEND_MIN; state < PM_SUSPEND_MAX; state++) अणु
		स्थिर अक्षर *label = mem_sleep_states[state];

		अगर (label && len == म_माप(label) && !म_भेदन(buf, label, len))
			वापस state;
	पूर्ण

	वापस PM_SUSPEND_ON;
पूर्ण

अटल sमाप_प्रकार mem_sleep_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	suspend_state_t state;
	पूर्णांक error;

	error = pm_स्वतःsleep_lock();
	अगर (error)
		वापस error;

	अगर (pm_स्वतःsleep_state() > PM_SUSPEND_ON) अणु
		error = -EBUSY;
		जाओ out;
	पूर्ण

	state = decode_suspend_state(buf, n);
	अगर (state < PM_SUSPEND_MAX && state > PM_SUSPEND_ON)
		mem_sleep_current = state;
	अन्यथा
		error = -EINVAL;

 out:
	pm_स्वतःsleep_unlock();
	वापस error ? error : n;
पूर्ण

घातer_attr(mem_sleep);

/*
 * sync_on_suspend: invoke ksys_sync_helper() beक्रमe suspend.
 *
 * show() वापसs whether ksys_sync_helper() is invoked beक्रमe suspend.
 * store() accepts 0 or 1.  0 disables ksys_sync_helper() and 1 enables it.
 */
bool sync_on_suspend_enabled = !IS_ENABLED(CONFIG_SUSPEND_SKIP_SYNC);

अटल sमाप_प्रकार sync_on_suspend_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", sync_on_suspend_enabled);
पूर्ण

अटल sमाप_प्रकार sync_on_suspend_store(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	अगर (val > 1)
		वापस -EINVAL;

	sync_on_suspend_enabled = !!val;
	वापस n;
पूर्ण

घातer_attr(sync_on_suspend);
#पूर्ण_अगर /* CONFIG_SUSPEND */

#अगर_घोषित CONFIG_PM_SLEEP_DEBUG
पूर्णांक pm_test_level = TEST_NONE;

अटल स्थिर अक्षर * स्थिर pm_tests[__TEST_AFTER_LAST] = अणु
	[TEST_NONE] = "none",
	[TEST_CORE] = "core",
	[TEST_CPUS] = "processors",
	[TEST_PLATFORM] = "platform",
	[TEST_DEVICES] = "devices",
	[TEST_FREEZER] = "freezer",
पूर्ण;

अटल sमाप_प्रकार pm_test_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
				अक्षर *buf)
अणु
	अक्षर *s = buf;
	पूर्णांक level;

	क्रम (level = TEST_FIRST; level <= TEST_MAX; level++)
		अगर (pm_tests[level]) अणु
			अगर (level == pm_test_level)
				s += प्र_लिखो(s, "[%s] ", pm_tests[level]);
			अन्यथा
				s += प्र_लिखो(s, "%s ", pm_tests[level]);
		पूर्ण

	अगर (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';

	वापस (s - buf);
पूर्ण

अटल sमाप_प्रकार pm_test_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	स्थिर अक्षर * स्थिर *s;
	पूर्णांक level;
	अक्षर *p;
	पूर्णांक len;
	पूर्णांक error = -EINVAL;

	p = स_प्रथम(buf, '\n', n);
	len = p ? p - buf : n;

	lock_प्रणाली_sleep();

	level = TEST_FIRST;
	क्रम (s = &pm_tests[level]; level <= TEST_MAX; s++, level++)
		अगर (*s && len == म_माप(*s) && !म_भेदन(buf, *s, len)) अणु
			pm_test_level = level;
			error = 0;
			अवरोध;
		पूर्ण

	unlock_प्रणाली_sleep();

	वापस error ? error : n;
पूर्ण

घातer_attr(pm_test);
#पूर्ण_अगर /* CONFIG_PM_SLEEP_DEBUG */

अटल अक्षर *suspend_step_name(क्रमागत suspend_stat_step step)
अणु
	चयन (step) अणु
	हाल SUSPEND_FREEZE:
		वापस "freeze";
	हाल SUSPEND_PREPARE:
		वापस "prepare";
	हाल SUSPEND_SUSPEND:
		वापस "suspend";
	हाल SUSPEND_SUSPEND_NOIRQ:
		वापस "suspend_noirq";
	हाल SUSPEND_RESUME_NOIRQ:
		वापस "resume_noirq";
	हाल SUSPEND_RESUME:
		वापस "resume";
	शेष:
		वापस "";
	पूर्ण
पूर्ण

#घोषणा suspend_attr(_name)					\
अटल sमाप_प्रकार _name##_show(काष्ठा kobject *kobj,		\
		काष्ठा kobj_attribute *attr, अक्षर *buf)		\
अणु								\
	वापस प्र_लिखो(buf, "%d\n", suspend_stats._name);	\
पूर्ण								\
अटल काष्ठा kobj_attribute _name = __ATTR_RO(_name)

suspend_attr(success);
suspend_attr(fail);
suspend_attr(failed_मुक्तze);
suspend_attr(failed_prepare);
suspend_attr(failed_suspend);
suspend_attr(failed_suspend_late);
suspend_attr(failed_suspend_noirq);
suspend_attr(failed_resume);
suspend_attr(failed_resume_early);
suspend_attr(failed_resume_noirq);

अटल sमाप_प्रकार last_failed_dev_show(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index;
	अक्षर *last_failed_dev = शून्य;

	index = suspend_stats.last_failed_dev + REC_FAILED_NUM - 1;
	index %= REC_FAILED_NUM;
	last_failed_dev = suspend_stats.failed_devs[index];

	वापस प्र_लिखो(buf, "%s\n", last_failed_dev);
पूर्ण
अटल काष्ठा kobj_attribute last_failed_dev = __ATTR_RO(last_failed_dev);

अटल sमाप_प्रकार last_failed_त्रुटि_सं_show(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index;
	पूर्णांक last_failed_त्रुटि_सं;

	index = suspend_stats.last_failed_त्रुटि_सं + REC_FAILED_NUM - 1;
	index %= REC_FAILED_NUM;
	last_failed_त्रुटि_सं = suspend_stats.त्रुटि_सं[index];

	वापस प्र_लिखो(buf, "%d\n", last_failed_त्रुटि_सं);
पूर्ण
अटल काष्ठा kobj_attribute last_failed_त्रुटि_सं = __ATTR_RO(last_failed_त्रुटि_सं);

अटल sमाप_प्रकार last_failed_step_show(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index;
	क्रमागत suspend_stat_step step;
	अक्षर *last_failed_step = शून्य;

	index = suspend_stats.last_failed_step + REC_FAILED_NUM - 1;
	index %= REC_FAILED_NUM;
	step = suspend_stats.failed_steps[index];
	last_failed_step = suspend_step_name(step);

	वापस प्र_लिखो(buf, "%s\n", last_failed_step);
पूर्ण
अटल काष्ठा kobj_attribute last_failed_step = __ATTR_RO(last_failed_step);

अटल काष्ठा attribute *suspend_attrs[] = अणु
	&success.attr,
	&fail.attr,
	&failed_मुक्तze.attr,
	&failed_prepare.attr,
	&failed_suspend.attr,
	&failed_suspend_late.attr,
	&failed_suspend_noirq.attr,
	&failed_resume.attr,
	&failed_resume_early.attr,
	&failed_resume_noirq.attr,
	&last_failed_dev.attr,
	&last_failed_त्रुटि_सं.attr,
	&last_failed_step.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group suspend_attr_group = अणु
	.name = "suspend_stats",
	.attrs = suspend_attrs,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक suspend_stats_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	पूर्णांक i, index, last_dev, last_त्रुटि_सं, last_step;

	last_dev = suspend_stats.last_failed_dev + REC_FAILED_NUM - 1;
	last_dev %= REC_FAILED_NUM;
	last_त्रुटि_सं = suspend_stats.last_failed_त्रुटि_सं + REC_FAILED_NUM - 1;
	last_त्रुटि_सं %= REC_FAILED_NUM;
	last_step = suspend_stats.last_failed_step + REC_FAILED_NUM - 1;
	last_step %= REC_FAILED_NUM;
	seq_म_लिखो(s, "%s: %d\n%s: %d\n%s: %d\n%s: %d\n%s: %d\n"
			"%s: %d\n%s: %d\n%s: %d\n%s: %d\n%s: %d\n",
			"success", suspend_stats.success,
			"fail", suspend_stats.fail,
			"failed_freeze", suspend_stats.failed_मुक्तze,
			"failed_prepare", suspend_stats.failed_prepare,
			"failed_suspend", suspend_stats.failed_suspend,
			"failed_suspend_late",
				suspend_stats.failed_suspend_late,
			"failed_suspend_noirq",
				suspend_stats.failed_suspend_noirq,
			"failed_resume", suspend_stats.failed_resume,
			"failed_resume_early",
				suspend_stats.failed_resume_early,
			"failed_resume_noirq",
				suspend_stats.failed_resume_noirq);
	seq_म_लिखो(s,	"failures:\n  last_failed_dev:\t%-s\n",
			suspend_stats.failed_devs[last_dev]);
	क्रम (i = 1; i < REC_FAILED_NUM; i++) अणु
		index = last_dev + REC_FAILED_NUM - i;
		index %= REC_FAILED_NUM;
		seq_म_लिखो(s, "\t\t\t%-s\n",
			suspend_stats.failed_devs[index]);
	पूर्ण
	seq_म_लिखो(s,	"  last_failed_errno:\t%-d\n",
			suspend_stats.त्रुटि_सं[last_त्रुटि_सं]);
	क्रम (i = 1; i < REC_FAILED_NUM; i++) अणु
		index = last_त्रुटि_सं + REC_FAILED_NUM - i;
		index %= REC_FAILED_NUM;
		seq_म_लिखो(s, "\t\t\t%-d\n",
			suspend_stats.त्रुटि_सं[index]);
	पूर्ण
	seq_म_लिखो(s,	"  last_failed_step:\t%-s\n",
			suspend_step_name(
				suspend_stats.failed_steps[last_step]));
	क्रम (i = 1; i < REC_FAILED_NUM; i++) अणु
		index = last_step + REC_FAILED_NUM - i;
		index %= REC_FAILED_NUM;
		seq_म_लिखो(s, "\t\t\t%-s\n",
			suspend_step_name(
				suspend_stats.failed_steps[index]));
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(suspend_stats);

अटल पूर्णांक __init pm_debugfs_init(व्योम)
अणु
	debugfs_create_file("suspend_stats", S_IFREG | S_IRUGO,
			शून्य, शून्य, &suspend_stats_fops);
	वापस 0;
पूर्ण

late_initcall(pm_debugfs_init);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM_SLEEP_DEBUG
/*
 * pm_prपूर्णांक_बार: prपूर्णांक समय taken by devices to suspend and resume.
 *
 * show() वापसs whether prपूर्णांकing of suspend and resume बार is enabled.
 * store() accepts 0 or 1.  0 disables prपूर्णांकing and 1 enables it.
 */
bool pm_prपूर्णांक_बार_enabled;

अटल sमाप_प्रकार pm_prपूर्णांक_बार_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", pm_prपूर्णांक_बार_enabled);
पूर्ण

अटल sमाप_प्रकार pm_prपूर्णांक_बार_store(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	अगर (val > 1)
		वापस -EINVAL;

	pm_prपूर्णांक_बार_enabled = !!val;
	वापस n;
पूर्ण

घातer_attr(pm_prपूर्णांक_बार);

अटल अंतरभूत व्योम pm_prपूर्णांक_बार_init(व्योम)
अणु
	pm_prपूर्णांक_बार_enabled = !!initcall_debug;
पूर्ण

अटल sमाप_प्रकार pm_wakeup_irq_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					अक्षर *buf)
अणु
	वापस pm_wakeup_irq ? प्र_लिखो(buf, "%u\n", pm_wakeup_irq) : -ENODATA;
पूर्ण

घातer_attr_ro(pm_wakeup_irq);

bool pm_debug_messages_on __पढ़ो_mostly;

अटल sमाप_प्रकार pm_debug_messages_show(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", pm_debug_messages_on);
पूर्ण

अटल sमाप_प्रकार pm_debug_messages_store(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	अगर (val > 1)
		वापस -EINVAL;

	pm_debug_messages_on = !!val;
	वापस n;
पूर्ण

घातer_attr(pm_debug_messages);

अटल पूर्णांक __init pm_debug_messages_setup(अक्षर *str)
अणु
	pm_debug_messages_on = true;
	वापस 1;
पूर्ण
__setup("pm_debug_messages", pm_debug_messages_setup);

/**
 * __pm_pr_dbg - Prपूर्णांक a suspend debug message to the kernel log.
 * @defer: Whether or not to use prपूर्णांकk_deferred() to prपूर्णांक the message.
 * @fmt: Message क्रमmat.
 *
 * The message will be emitted अगर enabled through the pm_debug_messages
 * sysfs attribute.
 */
व्योम __pm_pr_dbg(bool defer, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!pm_debug_messages_on)
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (defer)
		prपूर्णांकk_deferred(KERN_DEBUG "PM: %pV", &vaf);
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "PM: %pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण

#अन्यथा /* !CONFIG_PM_SLEEP_DEBUG */
अटल अंतरभूत व्योम pm_prपूर्णांक_बार_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP_DEBUG */

काष्ठा kobject *घातer_kobj;

/**
 * state - control प्रणाली sleep states.
 *
 * show() वापसs available sleep state labels, which may be "mem", "standby",
 * "freeze" and "disk" (hibernation).
 * See Documentation/admin-guide/pm/sleep-states.rst क्रम a description of
 * what they mean.
 *
 * store() accepts one of those strings, translates it पूर्णांकo the proper
 * क्रमागतerated value, and initiates a suspend transition.
 */
अटल sमाप_प्रकार state_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  अक्षर *buf)
अणु
	अक्षर *s = buf;
#अगर_घोषित CONFIG_SUSPEND
	suspend_state_t i;

	क्रम (i = PM_SUSPEND_MIN; i < PM_SUSPEND_MAX; i++)
		अगर (pm_states[i])
			s += प्र_लिखो(s,"%s ", pm_states[i]);

#पूर्ण_अगर
	अगर (hibernation_available())
		s += प्र_लिखो(s, "disk ");
	अगर (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';
	वापस (s - buf);
पूर्ण

अटल suspend_state_t decode_state(स्थिर अक्षर *buf, माप_प्रकार n)
अणु
#अगर_घोषित CONFIG_SUSPEND
	suspend_state_t state;
#पूर्ण_अगर
	अक्षर *p;
	पूर्णांक len;

	p = स_प्रथम(buf, '\n', n);
	len = p ? p - buf : n;

	/* Check hibernation first. */
	अगर (len == 4 && str_has_prefix(buf, "disk"))
		वापस PM_SUSPEND_MAX;

#अगर_घोषित CONFIG_SUSPEND
	क्रम (state = PM_SUSPEND_MIN; state < PM_SUSPEND_MAX; state++) अणु
		स्थिर अक्षर *label = pm_states[state];

		अगर (label && len == म_माप(label) && !म_भेदन(buf, label, len))
			वापस state;
	पूर्ण
#पूर्ण_अगर

	वापस PM_SUSPEND_ON;
पूर्ण

अटल sमाप_प्रकार state_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	suspend_state_t state;
	पूर्णांक error;

	error = pm_स्वतःsleep_lock();
	अगर (error)
		वापस error;

	अगर (pm_स्वतःsleep_state() > PM_SUSPEND_ON) अणु
		error = -EBUSY;
		जाओ out;
	पूर्ण

	state = decode_state(buf, n);
	अगर (state < PM_SUSPEND_MAX) अणु
		अगर (state == PM_SUSPEND_MEM)
			state = mem_sleep_current;

		error = pm_suspend(state);
	पूर्ण अन्यथा अगर (state == PM_SUSPEND_MAX) अणु
		error = hibernate();
	पूर्ण अन्यथा अणु
		error = -EINVAL;
	पूर्ण

 out:
	pm_स्वतःsleep_unlock();
	वापस error ? error : n;
पूर्ण

घातer_attr(state);

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * The 'wakeup_count' attribute, aदीर्घ with the functions defined in
 * drivers/base/घातer/wakeup.c, provides a means by which wakeup events can be
 * handled in a non-racy way.
 *
 * If a wakeup event occurs when the प्रणाली is in a sleep state, it simply is
 * woken up.  In turn, अगर an event that would wake the प्रणाली up from a sleep
 * state occurs when it is undergoing a transition to that sleep state, the
 * transition should be पातed.  Moreover, अगर such an event occurs when the
 * प्रणाली is in the working state, an attempt to start a transition to the
 * given sleep state should fail during certain period after the detection of
 * the event.  Using the 'state' attribute alone is not sufficient to satisfy
 * these requirements, because a wakeup event may occur exactly when 'state'
 * is being written to and may be delivered to user space right beक्रमe it is
 * frozen, so the event will reमुख्य only partially processed until the प्रणाली is
 * woken up by another event.  In particular, it won't cause the transition to
 * a sleep state to be पातed.
 *
 * This dअगरficulty may be overcome अगर user space uses 'wakeup_count' beक्रमe
 * writing to 'state'.  It first should read from 'wakeup_count' and store
 * the पढ़ो value.  Then, after carrying out its own preparations क्रम the प्रणाली
 * transition to a sleep state, it should ग_लिखो the stored value to
 * 'wakeup_count'.  If that fails, at least one wakeup event has occurred since
 * 'wakeup_count' was read and 'state' should not be written to.  Otherwise, it
 * is allowed to ग_लिखो to 'state', but the transition will be पातed अगर there
 * are any wakeup events detected after 'wakeup_count' was written to.
 */

अटल sमाप_प्रकार wakeup_count_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				अक्षर *buf)
अणु
	अचिन्हित पूर्णांक val;

	वापस pm_get_wakeup_count(&val, true) ?
		प्र_लिखो(buf, "%u\n", val) : -EINTR;
पूर्ण

अटल sमाप_प्रकार wakeup_count_store(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = pm_स्वतःsleep_lock();
	अगर (error)
		वापस error;

	अगर (pm_स्वतःsleep_state() > PM_SUSPEND_ON) अणु
		error = -EBUSY;
		जाओ out;
	पूर्ण

	error = -EINVAL;
	अगर (माला_पूछो(buf, "%u", &val) == 1) अणु
		अगर (pm_save_wakeup_count(val))
			error = n;
		अन्यथा
			pm_prपूर्णांक_active_wakeup_sources();
	पूर्ण

 out:
	pm_स्वतःsleep_unlock();
	वापस error;
पूर्ण

घातer_attr(wakeup_count);

#अगर_घोषित CONFIG_PM_AUTOSLEEP
अटल sमाप_प्रकार स्वतःsleep_show(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr,
			      अक्षर *buf)
अणु
	suspend_state_t state = pm_स्वतःsleep_state();

	अगर (state == PM_SUSPEND_ON)
		वापस प्र_लिखो(buf, "off\n");

#अगर_घोषित CONFIG_SUSPEND
	अगर (state < PM_SUSPEND_MAX)
		वापस प्र_लिखो(buf, "%s\n", pm_states[state] ?
					pm_states[state] : "error");
#पूर्ण_अगर
#अगर_घोषित CONFIG_HIBERNATION
	वापस प्र_लिखो(buf, "disk\n");
#अन्यथा
	वापस प्र_लिखो(buf, "error");
#पूर्ण_अगर
पूर्ण

अटल sमाप_प्रकार स्वतःsleep_store(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	suspend_state_t state = decode_state(buf, n);
	पूर्णांक error;

	अगर (state == PM_SUSPEND_ON
	    && म_भेद(buf, "off") && म_भेद(buf, "off\n"))
		वापस -EINVAL;

	अगर (state == PM_SUSPEND_MEM)
		state = mem_sleep_current;

	error = pm_स्वतःsleep_set_state(state);
	वापस error ? error : n;
पूर्ण

घातer_attr(स्वतःsleep);
#पूर्ण_अगर /* CONFIG_PM_AUTOSLEEP */

#अगर_घोषित CONFIG_PM_WAKELOCKS
अटल sमाप_प्रकार wake_lock_show(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr,
			      अक्षर *buf)
अणु
	वापस pm_show_wakelocks(buf, true);
पूर्ण

अटल sमाप_प्रकार wake_lock_store(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	पूर्णांक error = pm_wake_lock(buf);
	वापस error ? error : n;
पूर्ण

घातer_attr(wake_lock);

अटल sमाप_प्रकार wake_unlock_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				अक्षर *buf)
अणु
	वापस pm_show_wakelocks(buf, false);
पूर्ण

अटल sमाप_प्रकार wake_unlock_store(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	पूर्णांक error = pm_wake_unlock(buf);
	वापस error ? error : n;
पूर्ण

घातer_attr(wake_unlock);

#पूर्ण_अगर /* CONFIG_PM_WAKELOCKS */
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM_TRACE
पूर्णांक pm_trace_enabled;

अटल sमाप_प्रकार pm_trace_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", pm_trace_enabled);
पूर्ण

अटल sमाप_प्रकार
pm_trace_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	पूर्णांक val;

	अगर (माला_पूछो(buf, "%d", &val) == 1) अणु
		pm_trace_enabled = !!val;
		अगर (pm_trace_enabled) अणु
			pr_warn("PM: Enabling pm_trace changes system date and time during resume.\n"
				"PM: Correct system time has to be restored manually after resume.\n");
		पूर्ण
		वापस n;
	पूर्ण
	वापस -EINVAL;
पूर्ण

घातer_attr(pm_trace);

अटल sमाप_प्रकार pm_trace_dev_match_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *buf)
अणु
	वापस show_trace_dev_match(buf, PAGE_SIZE);
पूर्ण

घातer_attr_ro(pm_trace_dev_match);

#पूर्ण_अगर /* CONFIG_PM_TRACE */

#अगर_घोषित CONFIG_FREEZER
अटल sमाप_प्रकार pm_मुक्तze_समयout_show(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", मुक्तze_समयout_msecs);
पूर्ण

अटल sमाप_प्रकार pm_मुक्तze_समयout_store(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	मुक्तze_समयout_msecs = val;
	वापस n;
पूर्ण

घातer_attr(pm_मुक्तze_समयout);

#पूर्ण_अगर	/* CONFIG_FREEZER*/

अटल काष्ठा attribute * g[] = अणु
	&state_attr.attr,
#अगर_घोषित CONFIG_PM_TRACE
	&pm_trace_attr.attr,
	&pm_trace_dev_match_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM_SLEEP
	&pm_async_attr.attr,
	&wakeup_count_attr.attr,
#अगर_घोषित CONFIG_SUSPEND
	&mem_sleep_attr.attr,
	&sync_on_suspend_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM_AUTOSLEEP
	&स्वतःsleep_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM_WAKELOCKS
	&wake_lock_attr.attr,
	&wake_unlock_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM_SLEEP_DEBUG
	&pm_test_attr.attr,
	&pm_prपूर्णांक_बार_attr.attr,
	&pm_wakeup_irq_attr.attr,
	&pm_debug_messages_attr.attr,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_FREEZER
	&pm_मुक्तze_समयout_attr.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group attr_group = अणु
	.attrs = g,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_groups[] = अणु
	&attr_group,
#अगर_घोषित CONFIG_PM_SLEEP
	&suspend_attr_group,
#पूर्ण_अगर
	शून्य,
पूर्ण;

काष्ठा workqueue_काष्ठा *pm_wq;
EXPORT_SYMBOL_GPL(pm_wq);

अटल पूर्णांक __init pm_start_workqueue(व्योम)
अणु
	pm_wq = alloc_workqueue("pm", WQ_FREEZABLE, 0);

	वापस pm_wq ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक __init pm_init(व्योम)
अणु
	पूर्णांक error = pm_start_workqueue();
	अगर (error)
		वापस error;
	hibernate_image_size_init();
	hibernate_reserved_size_init();
	pm_states_init();
	घातer_kobj = kobject_create_and_add("power", शून्य);
	अगर (!घातer_kobj)
		वापस -ENOMEM;
	error = sysfs_create_groups(घातer_kobj, attr_groups);
	अगर (error)
		वापस error;
	pm_prपूर्णांक_बार_init();
	वापस pm_स्वतःsleep_init();
पूर्ण

core_initcall(pm_init);

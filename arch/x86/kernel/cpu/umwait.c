<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/syscore_ops.h>
#समावेश <linux/suspend.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/mरुको.h>

#घोषणा UMWAIT_C02_ENABLE	0

#घोषणा UMWAIT_CTRL_VAL(max_समय, c02_disable)				\
	(((max_समय) & MSR_IA32_UMWAIT_CONTROL_TIME_MASK) |		\
	((c02_disable) & MSR_IA32_UMWAIT_CONTROL_C02_DISABLE))

/*
 * Cache IA32_UMWAIT_CONTROL MSR. This is a प्रणालीwide control. By शेष,
 * umरुको max समय is 100000 in TSC-quanta and C0.2 is enabled
 */
अटल u32 umरुको_control_cached = UMWAIT_CTRL_VAL(100000, UMWAIT_C02_ENABLE);

/*
 * Cache the original IA32_UMWAIT_CONTROL MSR value which is configured by
 * hardware or BIOS beक्रमe kernel boot.
 */
अटल u32 orig_umरुको_control_cached __ro_after_init;

/*
 * Serialize access to umरुको_control_cached and IA32_UMWAIT_CONTROL MSR in
 * the sysfs ग_लिखो functions.
 */
अटल DEFINE_MUTEX(umरुको_lock);

अटल व्योम umरुको_update_control_msr(व्योम * unused)
अणु
	lockdep_निश्चित_irqs_disabled();
	wrmsr(MSR_IA32_UMWAIT_CONTROL, READ_ONCE(umरुको_control_cached), 0);
पूर्ण

/*
 * The CPU hotplug callback sets the control MSR to the global control
 * value.
 *
 * Disable पूर्णांकerrupts so the पढ़ो of umरुको_control_cached and the WRMSR
 * are रक्षित against a concurrent sysfs ग_लिखो. Otherwise the sysfs
 * ग_लिखो could update the cached value after it had been पढ़ो on this CPU
 * and issue the IPI beक्रमe the old value had been written. The IPI would
 * पूर्णांकerrupt, ग_लिखो the new value and after वापस from IPI the previous
 * value would be written by this CPU.
 *
 * With पूर्णांकerrupts disabled the upcoming CPU either sees the new control
 * value or the IPI is updating this CPU to the new control value after
 * पूर्णांकerrupts have been reenabled.
 */
अटल पूर्णांक umरुको_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	local_irq_disable();
	umरुको_update_control_msr(शून्य);
	local_irq_enable();
	वापस 0;
पूर्ण

/*
 * The CPU hotplug callback sets the control MSR to the original control
 * value.
 */
अटल पूर्णांक umरुको_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * This code is रक्षित by the CPU hotplug alपढ़ोy and
	 * orig_umरुको_control_cached is never changed after it caches
	 * the original control MSR value in umरुको_init(). So there
	 * is no race condition here.
	 */
	wrmsr(MSR_IA32_UMWAIT_CONTROL, orig_umरुको_control_cached, 0);

	वापस 0;
पूर्ण

/*
 * On resume, restore IA32_UMWAIT_CONTROL MSR on the boot processor which
 * is the only active CPU at this समय. The MSR is set up on the APs via the
 * CPU hotplug callback.
 *
 * This function is invoked on resume from suspend and hibernation. On
 * resume from suspend the restore should be not required, but we neither
 * trust the firmware nor करोes it matter अगर the same value is written
 * again.
 */
अटल व्योम umरुको_syscore_resume(व्योम)
अणु
	umरुको_update_control_msr(शून्य);
पूर्ण

अटल काष्ठा syscore_ops umरुको_syscore_ops = अणु
	.resume	= umरुको_syscore_resume,
पूर्ण;

/* sysfs पूर्णांकerface */

/*
 * When bit 0 in IA32_UMWAIT_CONTROL MSR is 1, C0.2 is disabled.
 * Otherwise, C0.2 is enabled.
 */
अटल अंतरभूत bool umरुको_ctrl_c02_enabled(u32 ctrl)
अणु
	वापस !(ctrl & MSR_IA32_UMWAIT_CONTROL_C02_DISABLE);
पूर्ण

अटल अंतरभूत u32 umरुको_ctrl_max_समय(u32 ctrl)
अणु
	वापस ctrl & MSR_IA32_UMWAIT_CONTROL_TIME_MASK;
पूर्ण

अटल अंतरभूत व्योम umरुको_update_control(u32 maxसमय, bool c02_enable)
अणु
	u32 ctrl = maxसमय & MSR_IA32_UMWAIT_CONTROL_TIME_MASK;

	अगर (!c02_enable)
		ctrl |= MSR_IA32_UMWAIT_CONTROL_C02_DISABLE;

	WRITE_ONCE(umरुको_control_cached, ctrl);
	/* Propagate to all CPUs */
	on_each_cpu(umरुको_update_control_msr, शून्य, 1);
पूर्ण

अटल sमाप_प्रकार
enable_c02_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 ctrl = READ_ONCE(umरुको_control_cached);

	वापस प्र_लिखो(buf, "%d\n", umरुको_ctrl_c02_enabled(ctrl));
पूर्ण

अटल sमाप_प्रकार enable_c02_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bool c02_enable;
	u32 ctrl;
	पूर्णांक ret;

	ret = kstrtobool(buf, &c02_enable);
	अगर (ret)
		वापस ret;

	mutex_lock(&umरुको_lock);

	ctrl = READ_ONCE(umरुको_control_cached);
	अगर (c02_enable != umरुको_ctrl_c02_enabled(ctrl))
		umरुको_update_control(ctrl, c02_enable);

	mutex_unlock(&umरुको_lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(enable_c02);

अटल sमाप_प्रकार
max_समय_show(काष्ठा device *kobj, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 ctrl = READ_ONCE(umरुको_control_cached);

	वापस प्र_लिखो(buf, "%u\n", umरुको_ctrl_max_समय(ctrl));
पूर्ण

अटल sमाप_प्रकार max_समय_store(काष्ठा device *kobj,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 max_समय, ctrl;
	पूर्णांक ret;

	ret = kstrtou32(buf, 0, &max_समय);
	अगर (ret)
		वापस ret;

	/* bits[1:0] must be zero */
	अगर (max_समय & ~MSR_IA32_UMWAIT_CONTROL_TIME_MASK)
		वापस -EINVAL;

	mutex_lock(&umरुको_lock);

	ctrl = READ_ONCE(umरुको_control_cached);
	अगर (max_समय != umरुको_ctrl_max_समय(ctrl))
		umरुको_update_control(max_समय, umरुको_ctrl_c02_enabled(ctrl));

	mutex_unlock(&umरुको_lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(max_समय);

अटल काष्ठा attribute *umरुको_attrs[] = अणु
	&dev_attr_enable_c02.attr,
	&dev_attr_max_समय.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group umरुको_attr_group = अणु
	.attrs = umरुको_attrs,
	.name = "umwait_control",
पूर्ण;

अटल पूर्णांक __init umरुको_init(व्योम)
अणु
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (!boot_cpu_has(X86_FEATURE_WAITPKG))
		वापस -ENODEV;

	/*
	 * Cache the original control MSR value beक्रमe the control MSR is
	 * changed. This is the only place where orig_umरुको_control_cached
	 * is modअगरied.
	 */
	rdmsrl(MSR_IA32_UMWAIT_CONTROL, orig_umरुको_control_cached);

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "umwait:online",
				umरुको_cpu_online, umरुको_cpu_offline);
	अगर (ret < 0) अणु
		/*
		 * On failure, the control MSR on all CPUs has the
		 * original control value.
		 */
		वापस ret;
	पूर्ण

	रेजिस्टर_syscore_ops(&umरुको_syscore_ops);

	/*
	 * Add umरुको control पूर्णांकerface. Ignore failure, so at least the
	 * शेष values are set up in हाल the machine manages to boot.
	 */
	dev = cpu_subsys.dev_root;
	वापस sysfs_create_group(&dev->kobj, &umरुको_attr_group);
पूर्ण
device_initcall(umरुको_init);

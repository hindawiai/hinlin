<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * x86_pkg_temp_thermal driver
 * Copyright (c) 2013, Intel Corporation.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/param.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#समावेश <linux/thermal.h>
#समावेश <linux/debugfs.h>

#समावेश <यंत्र/cpu_device_id.h>

#समावेश "thermal_interrupt.h"

/*
* Rate control delay: Idea is to पूर्णांकroduce denounce effect
* This should be दीर्घ enough to aव्योम reduce events, when
* threshold is set to a temperature, which is स्थिरantly
* violated, but at the लघु enough to take any action.
* The action can be हटाओ threshold or change it to next
* पूर्णांकeresting setting. Based on experiments, in around
* every 5 seconds under load will give us a signअगरicant
* temperature change.
*/
#घोषणा PKG_TEMP_THERMAL_NOTIFY_DELAY	5000
अटल पूर्णांक notअगरy_delay_ms = PKG_TEMP_THERMAL_NOTIFY_DELAY;
module_param(notअगरy_delay_ms, पूर्णांक, 0644);
MODULE_PARM_DESC(notअगरy_delay_ms,
	"User space notification delay in milli seconds.");

/* Number of trip poपूर्णांकs in thermal zone. Currently it can't
* be more than 2. MSR can allow setting and getting notअगरications
* क्रम only 2 thresholds. This define enक्रमces this, अगर there
* is some wrong values वापसed by cpuid क्रम number of thresholds.
*/
#घोषणा MAX_NUMBER_OF_TRIPS	2

काष्ठा zone_device अणु
	पूर्णांक				cpu;
	bool				work_scheduled;
	u32				tj_max;
	u32				msr_pkg_therm_low;
	u32				msr_pkg_therm_high;
	काष्ठा delayed_work		work;
	काष्ठा thermal_zone_device	*tzone;
	काष्ठा cpumask			cpumask;
पूर्ण;

अटल काष्ठा thermal_zone_params pkg_temp_tz_params = अणु
	.no_hwmon	= true,
पूर्ण;

/* Keep track of how many zone poपूर्णांकers we allocated in init() */
अटल पूर्णांक max_id __पढ़ो_mostly;
/* Array of zone poपूर्णांकers */
अटल काष्ठा zone_device **zones;
/* Serializes पूर्णांकerrupt notअगरication, work and hotplug */
अटल DEFINE_RAW_SPINLOCK(pkg_temp_lock);
/* Protects zone operation in the work function against hotplug removal */
अटल DEFINE_MUTEX(thermal_zone_mutex);

/* The dynamically asचिन्हित cpu hotplug state क्रम module_निकास() */
अटल क्रमागत cpuhp_state pkg_thermal_hp_state __पढ़ो_mostly;

/* Debug counters to show using debugfs */
अटल काष्ठा dentry *debugfs;
अटल अचिन्हित पूर्णांक pkg_पूर्णांकerrupt_cnt;
अटल अचिन्हित पूर्णांक pkg_work_cnt;

अटल व्योम pkg_temp_debugfs_init(व्योम)
अणु
	debugfs = debugfs_create_dir("pkg_temp_thermal", शून्य);

	debugfs_create_u32("pkg_thres_interrupt", S_IRUGO, debugfs,
			   &pkg_पूर्णांकerrupt_cnt);
	debugfs_create_u32("pkg_thres_work", S_IRUGO, debugfs,
			   &pkg_work_cnt);
पूर्ण

/*
 * Protection:
 *
 * - cpu hotplug: Read serialized by cpu hotplug lock
 *		  Write must hold pkg_temp_lock
 *
 * - Other callsites: Must hold pkg_temp_lock
 */
अटल काष्ठा zone_device *pkg_temp_thermal_get_dev(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक id = topology_logical_die_id(cpu);

	अगर (id >= 0 && id < max_id)
		वापस zones[id];
	वापस शून्य;
पूर्ण

/*
* tj-max is is पूर्णांकeresting because threshold is set relative to this
* temperature.
*/
अटल पूर्णांक get_tj_max(पूर्णांक cpu, u32 *tj_max)
अणु
	u32 eax, edx, val;
	पूर्णांक err;

	err = rdmsr_safe_on_cpu(cpu, MSR_IA32_TEMPERATURE_TARGET, &eax, &edx);
	अगर (err)
		वापस err;

	val = (eax >> 16) & 0xff;
	*tj_max = val * 1000;

	वापस val ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक sys_get_curr_temp(काष्ठा thermal_zone_device *tzd, पूर्णांक *temp)
अणु
	काष्ठा zone_device *zonedev = tzd->devdata;
	u32 eax, edx;

	rdmsr_on_cpu(zonedev->cpu, MSR_IA32_PACKAGE_THERM_STATUS,
			&eax, &edx);
	अगर (eax & 0x80000000) अणु
		*temp = zonedev->tj_max - ((eax >> 16) & 0x7f) * 1000;
		pr_debug("sys_get_curr_temp %d\n", *temp);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sys_get_trip_temp(काष्ठा thermal_zone_device *tzd,
			     पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा zone_device *zonedev = tzd->devdata;
	अचिन्हित दीर्घ thres_reg_value;
	u32 mask, shअगरt, eax, edx;
	पूर्णांक ret;

	अगर (trip >= MAX_NUMBER_OF_TRIPS)
		वापस -EINVAL;

	अगर (trip) अणु
		mask = THERM_MASK_THRESHOLD1;
		shअगरt = THERM_SHIFT_THRESHOLD1;
	पूर्ण अन्यथा अणु
		mask = THERM_MASK_THRESHOLD0;
		shअगरt = THERM_SHIFT_THRESHOLD0;
	पूर्ण

	ret = rdmsr_on_cpu(zonedev->cpu, MSR_IA32_PACKAGE_THERM_INTERRUPT,
			   &eax, &edx);
	अगर (ret < 0)
		वापस ret;

	thres_reg_value = (eax & mask) >> shअगरt;
	अगर (thres_reg_value)
		*temp = zonedev->tj_max - thres_reg_value * 1000;
	अन्यथा
		*temp = THERMAL_TEMP_INVALID;
	pr_debug("sys_get_trip_temp %d\n", *temp);

	वापस 0;
पूर्ण

अटल पूर्णांक
sys_set_trip_temp(काष्ठा thermal_zone_device *tzd, पूर्णांक trip, पूर्णांक temp)
अणु
	काष्ठा zone_device *zonedev = tzd->devdata;
	u32 l, h, mask, shअगरt, पूर्णांकr;
	पूर्णांक ret;

	अगर (trip >= MAX_NUMBER_OF_TRIPS || temp >= zonedev->tj_max)
		वापस -EINVAL;

	ret = rdmsr_on_cpu(zonedev->cpu, MSR_IA32_PACKAGE_THERM_INTERRUPT,
			   &l, &h);
	अगर (ret < 0)
		वापस ret;

	अगर (trip) अणु
		mask = THERM_MASK_THRESHOLD1;
		shअगरt = THERM_SHIFT_THRESHOLD1;
		पूर्णांकr = THERM_INT_THRESHOLD1_ENABLE;
	पूर्ण अन्यथा अणु
		mask = THERM_MASK_THRESHOLD0;
		shअगरt = THERM_SHIFT_THRESHOLD0;
		पूर्णांकr = THERM_INT_THRESHOLD0_ENABLE;
	पूर्ण
	l &= ~mask;
	/*
	* When users space sets a trip temperature == 0, which is indication
	* that, it is no दीर्घer पूर्णांकerested in receiving notअगरications.
	*/
	अगर (!temp) अणु
		l &= ~पूर्णांकr;
	पूर्ण अन्यथा अणु
		l |= (zonedev->tj_max - temp)/1000 << shअगरt;
		l |= पूर्णांकr;
	पूर्ण

	वापस wrmsr_on_cpu(zonedev->cpu, MSR_IA32_PACKAGE_THERM_INTERRUPT,
			l, h);
पूर्ण

अटल पूर्णांक sys_get_trip_type(काष्ठा thermal_zone_device *thermal, पूर्णांक trip,
			     क्रमागत thermal_trip_type *type)
अणु
	*type = THERMAL_TRIP_PASSIVE;
	वापस 0;
पूर्ण

/* Thermal zone callback registry */
अटल काष्ठा thermal_zone_device_ops tzone_ops = अणु
	.get_temp = sys_get_curr_temp,
	.get_trip_temp = sys_get_trip_temp,
	.get_trip_type = sys_get_trip_type,
	.set_trip_temp = sys_set_trip_temp,
पूर्ण;

अटल bool pkg_thermal_rate_control(व्योम)
अणु
	वापस true;
पूर्ण

/* Enable threshold पूर्णांकerrupt on local package/cpu */
अटल अंतरभूत व्योम enable_pkg_thres_पूर्णांकerrupt(व्योम)
अणु
	u8 thres_0, thres_1;
	u32 l, h;

	rdmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
	/* only enable/disable अगर it had valid threshold value */
	thres_0 = (l & THERM_MASK_THRESHOLD0) >> THERM_SHIFT_THRESHOLD0;
	thres_1 = (l & THERM_MASK_THRESHOLD1) >> THERM_SHIFT_THRESHOLD1;
	अगर (thres_0)
		l |= THERM_INT_THRESHOLD0_ENABLE;
	अगर (thres_1)
		l |= THERM_INT_THRESHOLD1_ENABLE;
	wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
पूर्ण

/* Disable threshold पूर्णांकerrupt on local package/cpu */
अटल अंतरभूत व्योम disable_pkg_thres_पूर्णांकerrupt(व्योम)
अणु
	u32 l, h;

	rdmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);

	l &= ~(THERM_INT_THRESHOLD0_ENABLE | THERM_INT_THRESHOLD1_ENABLE);
	wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
पूर्ण

अटल व्योम pkg_temp_thermal_threshold_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा thermal_zone_device *tzone = शून्य;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा zone_device *zonedev;
	u64 msr_val, wr_val;

	mutex_lock(&thermal_zone_mutex);
	raw_spin_lock_irq(&pkg_temp_lock);
	++pkg_work_cnt;

	zonedev = pkg_temp_thermal_get_dev(cpu);
	अगर (!zonedev) अणु
		raw_spin_unlock_irq(&pkg_temp_lock);
		mutex_unlock(&thermal_zone_mutex);
		वापस;
	पूर्ण
	zonedev->work_scheduled = false;

	rdmsrl(MSR_IA32_PACKAGE_THERM_STATUS, msr_val);
	wr_val = msr_val & ~(THERM_LOG_THRESHOLD0 | THERM_LOG_THRESHOLD1);
	अगर (wr_val != msr_val) अणु
		wrmsrl(MSR_IA32_PACKAGE_THERM_STATUS, wr_val);
		tzone = zonedev->tzone;
	पूर्ण

	enable_pkg_thres_पूर्णांकerrupt();
	raw_spin_unlock_irq(&pkg_temp_lock);

	/*
	 * If tzone is not शून्य, then thermal_zone_mutex will prevent the
	 * concurrent removal in the cpu offline callback.
	 */
	अगर (tzone)
		thermal_zone_device_update(tzone, THERMAL_EVENT_UNSPECIFIED);

	mutex_unlock(&thermal_zone_mutex);
पूर्ण

अटल व्योम pkg_thermal_schedule_work(पूर्णांक cpu, काष्ठा delayed_work *work)
अणु
	अचिन्हित दीर्घ ms = msecs_to_jअगरfies(notअगरy_delay_ms);

	schedule_delayed_work_on(cpu, work, ms);
पूर्ण

अटल पूर्णांक pkg_thermal_notअगरy(u64 msr_val)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा zone_device *zonedev;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pkg_temp_lock, flags);
	++pkg_पूर्णांकerrupt_cnt;

	disable_pkg_thres_पूर्णांकerrupt();

	/* Work is per package, so scheduling it once is enough. */
	zonedev = pkg_temp_thermal_get_dev(cpu);
	अगर (zonedev && !zonedev->work_scheduled) अणु
		zonedev->work_scheduled = true;
		pkg_thermal_schedule_work(zonedev->cpu, &zonedev->work);
	पूर्ण

	raw_spin_unlock_irqrestore(&pkg_temp_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pkg_temp_thermal_device_add(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक id = topology_logical_die_id(cpu);
	u32 tj_max, eax, ebx, ecx, edx;
	काष्ठा zone_device *zonedev;
	पूर्णांक thres_count, err;

	अगर (id >= max_id)
		वापस -ENOMEM;

	cpuid(6, &eax, &ebx, &ecx, &edx);
	thres_count = ebx & 0x07;
	अगर (!thres_count)
		वापस -ENODEV;

	thres_count = clamp_val(thres_count, 0, MAX_NUMBER_OF_TRIPS);

	err = get_tj_max(cpu, &tj_max);
	अगर (err)
		वापस err;

	zonedev = kzalloc(माप(*zonedev), GFP_KERNEL);
	अगर (!zonedev)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&zonedev->work, pkg_temp_thermal_threshold_work_fn);
	zonedev->cpu = cpu;
	zonedev->tj_max = tj_max;
	zonedev->tzone = thermal_zone_device_रेजिस्टर("x86_pkg_temp",
			thres_count,
			(thres_count == MAX_NUMBER_OF_TRIPS) ? 0x03 : 0x01,
			zonedev, &tzone_ops, &pkg_temp_tz_params, 0, 0);
	अगर (IS_ERR(zonedev->tzone)) अणु
		err = PTR_ERR(zonedev->tzone);
		kमुक्त(zonedev);
		वापस err;
	पूर्ण
	err = thermal_zone_device_enable(zonedev->tzone);
	अगर (err) अणु
		thermal_zone_device_unरेजिस्टर(zonedev->tzone);
		kमुक्त(zonedev);
		वापस err;
	पूर्ण
	/* Store MSR value क्रम package thermal पूर्णांकerrupt, to restore at निकास */
	rdmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, zonedev->msr_pkg_therm_low,
	      zonedev->msr_pkg_therm_high);

	cpumask_set_cpu(cpu, &zonedev->cpumask);
	raw_spin_lock_irq(&pkg_temp_lock);
	zones[id] = zonedev;
	raw_spin_unlock_irq(&pkg_temp_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pkg_thermal_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा zone_device *zonedev = pkg_temp_thermal_get_dev(cpu);
	bool lastcpu, was_target;
	पूर्णांक target;

	अगर (!zonedev)
		वापस 0;

	target = cpumask_any_but(&zonedev->cpumask, cpu);
	cpumask_clear_cpu(cpu, &zonedev->cpumask);
	lastcpu = target >= nr_cpu_ids;
	/*
	 * Remove the sysfs files, अगर this is the last cpu in the package
	 * beक्रमe करोing further cleanups.
	 */
	अगर (lastcpu) अणु
		काष्ठा thermal_zone_device *tzone = zonedev->tzone;

		/*
		 * We must protect against a work function calling
		 * thermal_zone_update, after/जबतक unरेजिस्टर. We null out
		 * the poपूर्णांकer under the zone mutex, so the worker function
		 * won't try to call.
		 */
		mutex_lock(&thermal_zone_mutex);
		zonedev->tzone = शून्य;
		mutex_unlock(&thermal_zone_mutex);

		thermal_zone_device_unरेजिस्टर(tzone);
	पूर्ण

	/* Protect against work and पूर्णांकerrupts */
	raw_spin_lock_irq(&pkg_temp_lock);

	/*
	 * Check whether this cpu was the current target and store the new
	 * one. When we drop the lock, then the पूर्णांकerrupt notअगरy function
	 * will see the new target.
	 */
	was_target = zonedev->cpu == cpu;
	zonedev->cpu = target;

	/*
	 * If this is the last CPU in the package हटाओ the package
	 * reference from the array and restore the पूर्णांकerrupt MSR. When we
	 * drop the lock neither the पूर्णांकerrupt notअगरy function nor the
	 * worker will see the package anymore.
	 */
	अगर (lastcpu) अणु
		zones[topology_logical_die_id(cpu)] = शून्य;
		/* After this poपूर्णांक nothing touches the MSR anymore. */
		wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT,
		      zonedev->msr_pkg_therm_low, zonedev->msr_pkg_therm_high);
	पूर्ण

	/*
	 * Check whether there is work scheduled and whether the work is
	 * targeted at the outgoing CPU.
	 */
	अगर (zonedev->work_scheduled && was_target) अणु
		/*
		 * To cancel the work we need to drop the lock, otherwise
		 * we might deadlock अगर the work needs to be flushed.
		 */
		raw_spin_unlock_irq(&pkg_temp_lock);
		cancel_delayed_work_sync(&zonedev->work);
		raw_spin_lock_irq(&pkg_temp_lock);
		/*
		 * If this is not the last cpu in the package and the work
		 * did not run after we dropped the lock above, then we
		 * need to reschedule the work, otherwise the पूर्णांकerrupt
		 * stays disabled क्रमever.
		 */
		अगर (!lastcpu && zonedev->work_scheduled)
			pkg_thermal_schedule_work(target, &zonedev->work);
	पूर्ण

	raw_spin_unlock_irq(&pkg_temp_lock);

	/* Final cleanup अगर this is the last cpu */
	अगर (lastcpu)
		kमुक्त(zonedev);
	वापस 0;
पूर्ण

अटल पूर्णांक pkg_thermal_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा zone_device *zonedev = pkg_temp_thermal_get_dev(cpu);
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

	/* Paranoia check */
	अगर (!cpu_has(c, X86_FEATURE_DTHERM) || !cpu_has(c, X86_FEATURE_PTS))
		वापस -ENODEV;

	/* If the package exists, nothing to करो */
	अगर (zonedev) अणु
		cpumask_set_cpu(cpu, &zonedev->cpumask);
		वापस 0;
	पूर्ण
	वापस pkg_temp_thermal_device_add(cpu);
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id __initस्थिर pkg_temp_thermal_ids[] = अणु
	X86_MATCH_VENDOR_FEATURE(INTEL, X86_FEATURE_PTS, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, pkg_temp_thermal_ids);

अटल पूर्णांक __init pkg_temp_thermal_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!x86_match_cpu(pkg_temp_thermal_ids))
		वापस -ENODEV;

	max_id = topology_max_packages() * topology_max_die_per_package();
	zones = kसुस्मृति(max_id, माप(काष्ठा zone_device *),
			   GFP_KERNEL);
	अगर (!zones)
		वापस -ENOMEM;

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "thermal/x86_pkg:online",
				pkg_thermal_cpu_online,	pkg_thermal_cpu_offline);
	अगर (ret < 0)
		जाओ err;

	/* Store the state क्रम module निकास */
	pkg_thermal_hp_state = ret;

	platक्रमm_thermal_package_notअगरy = pkg_thermal_notअगरy;
	platक्रमm_thermal_package_rate_control = pkg_thermal_rate_control;

	 /* Don't care अगर it fails */
	pkg_temp_debugfs_init();
	वापस 0;

err:
	kमुक्त(zones);
	वापस ret;
पूर्ण
module_init(pkg_temp_thermal_init)

अटल व्योम __निकास pkg_temp_thermal_निकास(व्योम)
अणु
	platक्रमm_thermal_package_notअगरy = शून्य;
	platक्रमm_thermal_package_rate_control = शून्य;

	cpuhp_हटाओ_state(pkg_thermal_hp_state);
	debugfs_हटाओ_recursive(debugfs);
	kमुक्त(zones);
पूर्ण
module_निकास(pkg_temp_thermal_निकास)

MODULE_DESCRIPTION("X86 PKG TEMP Thermal Driver");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");

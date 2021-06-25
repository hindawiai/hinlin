<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CPU subप्रणाली support
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpu.h>
#समावेश <linux/topology.h>
#समावेश <linux/device.h>
#समावेश <linux/node.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/percpu.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/tick.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/sched/isolation.h>

#समावेश "base.h"

अटल DEFINE_PER_CPU(काष्ठा device *, cpu_sys_devices);

अटल पूर्णांक cpu_subsys_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	/* ACPI style match is the only one that may succeed. */
	अगर (acpi_driver_match_device(dev, drv))
		वापस 1;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम change_cpu_under_node(काष्ठा cpu *cpu,
			अचिन्हित पूर्णांक from_nid, अचिन्हित पूर्णांक to_nid)
अणु
	पूर्णांक cpuid = cpu->dev.id;
	unरेजिस्टर_cpu_under_node(cpuid, from_nid);
	रेजिस्टर_cpu_under_node(cpuid, to_nid);
	cpu->node_id = to_nid;
पूर्ण

अटल पूर्णांक cpu_subsys_online(काष्ठा device *dev)
अणु
	काष्ठा cpu *cpu = container_of(dev, काष्ठा cpu, dev);
	पूर्णांक cpuid = dev->id;
	पूर्णांक from_nid, to_nid;
	पूर्णांक ret;

	from_nid = cpu_to_node(cpuid);
	अगर (from_nid == NUMA_NO_NODE)
		वापस -ENODEV;

	ret = cpu_device_up(dev);
	/*
	 * When hot adding memory to memoryless node and enabling a cpu
	 * on the node, node number of the cpu may पूर्णांकernally change.
	 */
	to_nid = cpu_to_node(cpuid);
	अगर (from_nid != to_nid)
		change_cpu_under_node(cpu, from_nid, to_nid);

	वापस ret;
पूर्ण

अटल पूर्णांक cpu_subsys_offline(काष्ठा device *dev)
अणु
	वापस cpu_device_करोwn(dev);
पूर्ण

व्योम unरेजिस्टर_cpu(काष्ठा cpu *cpu)
अणु
	पूर्णांक logical_cpu = cpu->dev.id;

	unरेजिस्टर_cpu_under_node(logical_cpu, cpu_to_node(logical_cpu));

	device_unरेजिस्टर(&cpu->dev);
	per_cpu(cpu_sys_devices, logical_cpu) = शून्य;
	वापस;
पूर्ण

#अगर_घोषित CONFIG_ARCH_CPU_PROBE_RELEASE
अटल sमाप_प्रकार cpu_probe_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	sमाप_प्रकार cnt;
	पूर्णांक ret;

	ret = lock_device_hotplug_sysfs();
	अगर (ret)
		वापस ret;

	cnt = arch_cpu_probe(buf, count);

	unlock_device_hotplug();
	वापस cnt;
पूर्ण

अटल sमाप_प्रकार cpu_release_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	sमाप_प्रकार cnt;
	पूर्णांक ret;

	ret = lock_device_hotplug_sysfs();
	अगर (ret)
		वापस ret;

	cnt = arch_cpu_release(buf, count);

	unlock_device_hotplug();
	वापस cnt;
पूर्ण

अटल DEVICE_ATTR(probe, S_IWUSR, शून्य, cpu_probe_store);
अटल DEVICE_ATTR(release, S_IWUSR, शून्य, cpu_release_store);
#पूर्ण_अगर /* CONFIG_ARCH_CPU_PROBE_RELEASE */
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

काष्ठा bus_type cpu_subsys = अणु
	.name = "cpu",
	.dev_name = "cpu",
	.match = cpu_subsys_match,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.online = cpu_subsys_online,
	.offline = cpu_subsys_offline,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL_GPL(cpu_subsys);

#अगर_घोषित CONFIG_KEXEC
#समावेश <linux/kexec.h>

अटल sमाप_प्रकार crash_notes_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा cpu *cpu = container_of(dev, काष्ठा cpu, dev);
	अचिन्हित दीर्घ दीर्घ addr;
	पूर्णांक cpunum;

	cpunum = cpu->dev.id;

	/*
	 * Might be पढ़ोing other cpu's data based on which cpu पढ़ो thपढ़ो
	 * has been scheduled. But cpu data (memory) is allocated once during
	 * boot up and this data करोes not change there after. Hence this
	 * operation should be safe. No locking required.
	 */
	addr = per_cpu_ptr_to_phys(per_cpu_ptr(crash_notes, cpunum));

	वापस sysfs_emit(buf, "%llx\n", addr);
पूर्ण
अटल DEVICE_ATTR_ADMIN_RO(crash_notes);

अटल sमाप_प्रकार crash_notes_size_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%zu\n", माप(note_buf_t));
पूर्ण
अटल DEVICE_ATTR_ADMIN_RO(crash_notes_size);

अटल काष्ठा attribute *crash_note_cpu_attrs[] = अणु
	&dev_attr_crash_notes.attr,
	&dev_attr_crash_notes_size.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group crash_note_cpu_attr_group = अणु
	.attrs = crash_note_cpu_attrs,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा attribute_group *common_cpu_attr_groups[] = अणु
#अगर_घोषित CONFIG_KEXEC
	&crash_note_cpu_attr_group,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hotplugable_cpu_attr_groups[] = अणु
#अगर_घोषित CONFIG_KEXEC
	&crash_note_cpu_attr_group,
#पूर्ण_अगर
	शून्य
पूर्ण;

/*
 * Prपूर्णांक cpu online, possible, present, and प्रणाली maps
 */

काष्ठा cpu_attr अणु
	काष्ठा device_attribute attr;
	स्थिर काष्ठा cpumask *स्थिर map;
पूर्ण;

अटल sमाप_प्रकार show_cpus_attr(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा cpu_attr *ca = container_of(attr, काष्ठा cpu_attr, attr);

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, ca->map);
पूर्ण

#घोषणा _CPU_ATTR(name, map) \
	अणु __ATTR(name, 0444, show_cpus_attr, शून्य), map पूर्ण

/* Keep in sync with cpu_subsys_attrs */
अटल काष्ठा cpu_attr cpu_attrs[] = अणु
	_CPU_ATTR(online, &__cpu_online_mask),
	_CPU_ATTR(possible, &__cpu_possible_mask),
	_CPU_ATTR(present, &__cpu_present_mask),
पूर्ण;

/*
 * Prपूर्णांक values क्रम NR_CPUS and offlined cpus
 */
अटल sमाप_प्रकार prपूर्णांक_cpus_kernel_max(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", NR_CPUS - 1);
पूर्ण
अटल DEVICE_ATTR(kernel_max, 0444, prपूर्णांक_cpus_kernel_max, शून्य);

/* arch-optional setting to enable display of offline cpus >= nr_cpu_ids */
अचिन्हित पूर्णांक total_cpus;

अटल sमाप_प्रकार prपूर्णांक_cpus_offline(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक len = 0;
	cpumask_var_t offline;

	/* display offline cpus < nr_cpu_ids */
	अगर (!alloc_cpumask_var(&offline, GFP_KERNEL))
		वापस -ENOMEM;
	cpumask_andnot(offline, cpu_possible_mask, cpu_online_mask);
	len += sysfs_emit_at(buf, len, "%*pbl", cpumask_pr_args(offline));
	मुक्त_cpumask_var(offline);

	/* display offline cpus >= nr_cpu_ids */
	अगर (total_cpus && nr_cpu_ids < total_cpus) अणु
		len += sysfs_emit_at(buf, len, ",");

		अगर (nr_cpu_ids == total_cpus-1)
			len += sysfs_emit_at(buf, len, "%u", nr_cpu_ids);
		अन्यथा
			len += sysfs_emit_at(buf, len, "%u-%d",
					     nr_cpu_ids, total_cpus - 1);
	पूर्ण

	len += sysfs_emit_at(buf, len, "\n");

	वापस len;
पूर्ण
अटल DEVICE_ATTR(offline, 0444, prपूर्णांक_cpus_offline, शून्य);

अटल sमाप_प्रकार prपूर्णांक_cpus_isolated(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक len;
	cpumask_var_t isolated;

	अगर (!alloc_cpumask_var(&isolated, GFP_KERNEL))
		वापस -ENOMEM;

	cpumask_andnot(isolated, cpu_possible_mask,
		       housekeeping_cpumask(HK_FLAG_DOMAIN));
	len = sysfs_emit(buf, "%*pbl\n", cpumask_pr_args(isolated));

	मुक्त_cpumask_var(isolated);

	वापस len;
पूर्ण
अटल DEVICE_ATTR(isolated, 0444, prपूर्णांक_cpus_isolated, शून्य);

#अगर_घोषित CONFIG_NO_HZ_FULL
अटल sमाप_प्रकार prपूर्णांक_cpus_nohz_full(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%*pbl\n", cpumask_pr_args(tick_nohz_full_mask));
पूर्ण
अटल DEVICE_ATTR(nohz_full, 0444, prपूर्णांक_cpus_nohz_full, शून्य);
#पूर्ण_अगर

अटल व्योम cpu_device_release(काष्ठा device *dev)
अणु
	/*
	 * This is an empty function to prevent the driver core from spitting a
	 * warning at us.  Yes, I know this is directly opposite of what the
	 * करोcumentation क्रम the driver core and kobjects say, and the author
	 * of this code has alपढ़ोy been खुलाally ridiculed क्रम करोing
	 * something as foolish as this.  However, at this poपूर्णांक in समय, it is
	 * the only way to handle the issue of अटलally allocated cpu
	 * devices.  The dअगरferent architectures will have their cpu device
	 * code reworked to properly handle this in the near future, so this
	 * function will then be changed to correctly मुक्त up the memory held
	 * by the cpu device.
	 *
	 * Never copy this way of करोing things, or you too will be made fun of
	 * on the linux-kernel list, you have been warned.
	 */
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CPU_AUTOPROBE
अटल sमाप_प्रकार prपूर्णांक_cpu_modalias(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	पूर्णांक len = 0;
	u32 i;

	len += sysfs_emit_at(buf, len,
			     "cpu:type:" CPU_FEATURE_TYPEFMT ":feature:",
			     CPU_FEATURE_TYPEVAL);

	क्रम (i = 0; i < MAX_CPU_FEATURES; i++)
		अगर (cpu_have_feature(i)) अणु
			अगर (len + माप(",XXXX\n") >= PAGE_SIZE) अणु
				WARN(1, "CPU features overflow page\n");
				अवरोध;
			पूर्ण
			len += sysfs_emit_at(buf, len, ",%04X", i);
		पूर्ण
	len += sysfs_emit_at(buf, len, "\n");
	वापस len;
पूर्ण

अटल पूर्णांक cpu_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	अक्षर *buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (buf) अणु
		prपूर्णांक_cpu_modalias(शून्य, शून्य, buf);
		add_uevent_var(env, "MODALIAS=%s", buf);
		kमुक्त(buf);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * रेजिस्टर_cpu - Setup a sysfs device क्रम a CPU.
 * @cpu - cpu->hotpluggable field set to 1 will generate a control file in
 *	  sysfs क्रम this CPU.
 * @num - CPU number to use when creating the device.
 *
 * Initialize and रेजिस्टर the CPU device.
 */
पूर्णांक रेजिस्टर_cpu(काष्ठा cpu *cpu, पूर्णांक num)
अणु
	पूर्णांक error;

	cpu->node_id = cpu_to_node(num);
	स_रखो(&cpu->dev, 0x00, माप(काष्ठा device));
	cpu->dev.id = num;
	cpu->dev.bus = &cpu_subsys;
	cpu->dev.release = cpu_device_release;
	cpu->dev.offline_disabled = !cpu->hotpluggable;
	cpu->dev.offline = !cpu_online(num);
	cpu->dev.of_node = of_get_cpu_node(num, शून्य);
#अगर_घोषित CONFIG_GENERIC_CPU_AUTOPROBE
	cpu->dev.bus->uevent = cpu_uevent;
#पूर्ण_अगर
	cpu->dev.groups = common_cpu_attr_groups;
	अगर (cpu->hotpluggable)
		cpu->dev.groups = hotplugable_cpu_attr_groups;
	error = device_रेजिस्टर(&cpu->dev);
	अगर (error) अणु
		put_device(&cpu->dev);
		वापस error;
	पूर्ण

	per_cpu(cpu_sys_devices, num) = &cpu->dev;
	रेजिस्टर_cpu_under_node(num, cpu_to_node(num));
	dev_pm_qos_expose_latency_limit(&cpu->dev,
					PM_QOS_RESUME_LATENCY_NO_CONSTRAINT);

	वापस 0;
पूर्ण

काष्ठा device *get_cpu_device(अचिन्हित cpu)
अणु
	अगर (cpu < nr_cpu_ids && cpu_possible(cpu))
		वापस per_cpu(cpu_sys_devices, cpu);
	अन्यथा
		वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(get_cpu_device);

अटल व्योम device_create_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

__म_लिखो(4, 0)
अटल काष्ठा device *
__cpu_device_create(काष्ठा device *parent, व्योम *drvdata,
		    स्थिर काष्ठा attribute_group **groups,
		    स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा device *dev = शून्य;
	पूर्णांक retval = -ENOMEM;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		जाओ error;

	device_initialize(dev);
	dev->parent = parent;
	dev->groups = groups;
	dev->release = device_create_release;
	device_set_pm_not_required(dev);
	dev_set_drvdata(dev, drvdata);

	retval = kobject_set_name_vargs(&dev->kobj, fmt, args);
	अगर (retval)
		जाओ error;

	retval = device_add(dev);
	अगर (retval)
		जाओ error;

	वापस dev;

error:
	put_device(dev);
	वापस ERR_PTR(retval);
पूर्ण

काष्ठा device *cpu_device_create(काष्ठा device *parent, व्योम *drvdata,
				 स्थिर काष्ठा attribute_group **groups,
				 स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vargs;
	काष्ठा device *dev;

	बहु_शुरू(vargs, fmt);
	dev = __cpu_device_create(parent, drvdata, groups, fmt, vargs);
	बहु_पूर्ण(vargs);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_device_create);

#अगर_घोषित CONFIG_GENERIC_CPU_AUTOPROBE
अटल DEVICE_ATTR(modalias, 0444, prपूर्णांक_cpu_modalias, शून्य);
#पूर्ण_अगर

अटल काष्ठा attribute *cpu_root_attrs[] = अणु
#अगर_घोषित CONFIG_ARCH_CPU_PROBE_RELEASE
	&dev_attr_probe.attr,
	&dev_attr_release.attr,
#पूर्ण_अगर
	&cpu_attrs[0].attr.attr,
	&cpu_attrs[1].attr.attr,
	&cpu_attrs[2].attr.attr,
	&dev_attr_kernel_max.attr,
	&dev_attr_offline.attr,
	&dev_attr_isolated.attr,
#अगर_घोषित CONFIG_NO_HZ_FULL
	&dev_attr_nohz_full.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_CPU_AUTOPROBE
	&dev_attr_modalias.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल काष्ठा attribute_group cpu_root_attr_group = अणु
	.attrs = cpu_root_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *cpu_root_attr_groups[] = अणु
	&cpu_root_attr_group,
	शून्य,
पूर्ण;

bool cpu_is_hotpluggable(अचिन्हित cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);
	वापस dev && container_of(dev, काष्ठा cpu, dev)->hotpluggable;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_is_hotpluggable);

#अगर_घोषित CONFIG_GENERIC_CPU_DEVICES
अटल DEFINE_PER_CPU(काष्ठा cpu, cpu_devices);
#पूर्ण_अगर

अटल व्योम __init cpu_dev_रेजिस्टर_generic(व्योम)
अणु
#अगर_घोषित CONFIG_GENERIC_CPU_DEVICES
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		अगर (रेजिस्टर_cpu(&per_cpu(cpu_devices, i), i))
			panic("Failed to register CPU device");
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CPU_VULNERABILITIES

sमाप_प्रकार __weak cpu_show_meltकरोwn(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार __weak cpu_show_spectre_v1(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार __weak cpu_show_spectre_v2(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार __weak cpu_show_spec_store_bypass(काष्ठा device *dev,
					  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार __weak cpu_show_l1tf(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार __weak cpu_show_mds(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार __weak cpu_show_tsx_async_पात(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार __weak cpu_show_itlb_multihit(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार __weak cpu_show_srbds(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Not affected\n");
पूर्ण

अटल DEVICE_ATTR(meltकरोwn, 0444, cpu_show_meltकरोwn, शून्य);
अटल DEVICE_ATTR(spectre_v1, 0444, cpu_show_spectre_v1, शून्य);
अटल DEVICE_ATTR(spectre_v2, 0444, cpu_show_spectre_v2, शून्य);
अटल DEVICE_ATTR(spec_store_bypass, 0444, cpu_show_spec_store_bypass, शून्य);
अटल DEVICE_ATTR(l1tf, 0444, cpu_show_l1tf, शून्य);
अटल DEVICE_ATTR(mds, 0444, cpu_show_mds, शून्य);
अटल DEVICE_ATTR(tsx_async_पात, 0444, cpu_show_tsx_async_पात, शून्य);
अटल DEVICE_ATTR(itlb_multihit, 0444, cpu_show_itlb_multihit, शून्य);
अटल DEVICE_ATTR(srbds, 0444, cpu_show_srbds, शून्य);

अटल काष्ठा attribute *cpu_root_vulnerabilities_attrs[] = अणु
	&dev_attr_meltकरोwn.attr,
	&dev_attr_spectre_v1.attr,
	&dev_attr_spectre_v2.attr,
	&dev_attr_spec_store_bypass.attr,
	&dev_attr_l1tf.attr,
	&dev_attr_mds.attr,
	&dev_attr_tsx_async_पात.attr,
	&dev_attr_itlb_multihit.attr,
	&dev_attr_srbds.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cpu_root_vulnerabilities_group = अणु
	.name  = "vulnerabilities",
	.attrs = cpu_root_vulnerabilities_attrs,
पूर्ण;

अटल व्योम __init cpu_रेजिस्टर_vulnerabilities(व्योम)
अणु
	अगर (sysfs_create_group(&cpu_subsys.dev_root->kobj,
			       &cpu_root_vulnerabilities_group))
		pr_err("Unable to register CPU vulnerabilities\n");
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम cpu_रेजिस्टर_vulnerabilities(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम __init cpu_dev_init(व्योम)
अणु
	अगर (subsys_प्रणाली_रेजिस्टर(&cpu_subsys, cpu_root_attr_groups))
		panic("Failed to register CPU subsystem");

	cpu_dev_रेजिस्टर_generic();
	cpu_रेजिस्टर_vulnerabilities();
पूर्ण

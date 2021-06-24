<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Uncore Frequency Setting
 * Copyright (c) 2019, Intel Corporation.
 * All rights reserved.
 *
 * Provide पूर्णांकerface to set MSR 620 at a granularity of per die. On CPU online,
 * one control CPU is identअगरied per die to पढ़ो/ग_लिखो limit. This control CPU
 * is changed, अगर the CPU state is changed to offline. When the last CPU is
 * offline in a die then हटाओ the sysfs object क्रम that die.
 * The majority of actual code is related to sysfs create and पढ़ो/ग_लिखो
 * attributes.
 *
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

#घोषणा MSR_UNCORE_RATIO_LIMIT			0x620
#घोषणा UNCORE_FREQ_KHZ_MULTIPLIER		100000

/**
 * काष्ठा uncore_data -	Encapsulate all uncore data
 * @stored_uncore_data:	Last user changed MSR 620 value, which will be restored
 *			on प्रणाली resume.
 * @initial_min_freq_khz: Sampled minimum uncore frequency at driver init
 * @initial_max_freq_khz: Sampled maximum uncore frequency at driver init
 * @control_cpu:	Designated CPU क्रम a die to पढ़ो/ग_लिखो
 * @valid:		Mark the data valid/invalid
 *
 * This काष्ठाure is used to encapsulate all data related to uncore sysfs
 * settings क्रम a die/package.
 */
काष्ठा uncore_data अणु
	काष्ठा kobject kobj;
	काष्ठा completion kobj_unरेजिस्टर;
	u64 stored_uncore_data;
	u32 initial_min_freq_khz;
	u32 initial_max_freq_khz;
	पूर्णांक control_cpu;
	bool valid;
पूर्ण;

#घोषणा to_uncore_data(a) container_of(a, काष्ठा uncore_data, kobj)

/* Max instances क्रम uncore data, one क्रम each die */
अटल पूर्णांक uncore_max_entries __पढ़ो_mostly;
/* Storage क्रम uncore data क्रम all instances */
अटल काष्ठा uncore_data *uncore_instances;
/* Root of the all uncore sysfs kobjs */
अटल काष्ठा kobject *uncore_root_kobj;
/* Stores the CPU mask of the target CPUs to use during uncore पढ़ो/ग_लिखो */
अटल cpumask_t uncore_cpu_mask;
/* CPU online callback रेजिस्टर instance */
अटल क्रमागत cpuhp_state uncore_hp_state __पढ़ो_mostly;
/* Mutex to control all mutual exclusions */
अटल DEFINE_MUTEX(uncore_lock);

काष्ठा uncore_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा kobject *kobj,
			काष्ठा attribute *attr, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा kobject *kobj,
			 काष्ठा attribute *attr, स्थिर अक्षर *c, sमाप_प्रकार count);
पूर्ण;

#घोषणा define_one_uncore_ro(_name) \
अटल काष्ठा uncore_attr _name = \
__ATTR(_name, 0444, show_##_name, शून्य)

#घोषणा define_one_uncore_rw(_name) \
अटल काष्ठा uncore_attr _name = \
__ATTR(_name, 0644, show_##_name, store_##_name)

#घोषणा show_uncore_data(member_name)					\
	अटल sमाप_प्रकार show_##member_name(काष्ठा kobject *kobj,         \
					  काष्ठा attribute *attr,	\
					  अक्षर *buf)			\
	अणु                                                               \
		काष्ठा uncore_data *data = to_uncore_data(kobj);	\
		वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",		\
				 data->member_name);			\
	पूर्ण								\
	define_one_uncore_ro(member_name)

show_uncore_data(initial_min_freq_khz);
show_uncore_data(initial_max_freq_khz);

/* Common function to पढ़ो MSR 0x620 and पढ़ो min/max */
अटल पूर्णांक uncore_पढ़ो_ratio(काष्ठा uncore_data *data, अचिन्हित पूर्णांक *min,
			     अचिन्हित पूर्णांक *max)
अणु
	u64 cap;
	पूर्णांक ret;

	अगर (data->control_cpu < 0)
		वापस -ENXIO;

	ret = rdmsrl_on_cpu(data->control_cpu, MSR_UNCORE_RATIO_LIMIT, &cap);
	अगर (ret)
		वापस ret;

	*max = (cap & 0x7F) * UNCORE_FREQ_KHZ_MULTIPLIER;
	*min = ((cap & GENMASK(14, 8)) >> 8) * UNCORE_FREQ_KHZ_MULTIPLIER;

	वापस 0;
पूर्ण

/* Common function to set min/max ratios to be used by sysfs callbacks */
अटल पूर्णांक uncore_ग_लिखो_ratio(काष्ठा uncore_data *data, अचिन्हित पूर्णांक input,
			      पूर्णांक set_max)
अणु
	पूर्णांक ret;
	u64 cap;

	mutex_lock(&uncore_lock);

	अगर (data->control_cpu < 0) अणु
		ret = -ENXIO;
		जाओ finish_ग_लिखो;
	पूर्ण

	input /= UNCORE_FREQ_KHZ_MULTIPLIER;
	अगर (!input || input > 0x7F) अणु
		ret = -EINVAL;
		जाओ finish_ग_लिखो;
	पूर्ण

	ret = rdmsrl_on_cpu(data->control_cpu, MSR_UNCORE_RATIO_LIMIT, &cap);
	अगर (ret)
		जाओ finish_ग_लिखो;

	अगर (set_max) अणु
		cap &= ~0x7F;
		cap |= input;
	पूर्ण अन्यथा  अणु
		cap &= ~GENMASK(14, 8);
		cap |= (input << 8);
	पूर्ण

	ret = wrmsrl_on_cpu(data->control_cpu, MSR_UNCORE_RATIO_LIMIT, cap);
	अगर (ret)
		जाओ finish_ग_लिखो;

	data->stored_uncore_data = cap;

finish_ग_लिखो:
	mutex_unlock(&uncore_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_min_max_freq_khz(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr,
				      स्थिर अक्षर *buf, sमाप_प्रकार count,
				      पूर्णांक min_max)
अणु
	काष्ठा uncore_data *data = to_uncore_data(kobj);
	अचिन्हित पूर्णांक input;

	अगर (kstrtouपूर्णांक(buf, 10, &input))
		वापस -EINVAL;

	uncore_ग_लिखो_ratio(data, input, min_max);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_min_max_freq_khz(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr,
				     अक्षर *buf, पूर्णांक min_max)
अणु
	काष्ठा uncore_data *data = to_uncore_data(kobj);
	अचिन्हित पूर्णांक min, max;
	पूर्णांक ret;

	mutex_lock(&uncore_lock);
	ret = uncore_पढ़ो_ratio(data, &min, &max);
	mutex_unlock(&uncore_lock);
	अगर (ret)
		वापस ret;

	अगर (min_max)
		वापस प्र_लिखो(buf, "%u\n", max);

	वापस प्र_लिखो(buf, "%u\n", min);
पूर्ण

#घोषणा store_uncore_min_max(name, min_max)				\
	अटल sमाप_प्रकार store_##name(काष्ठा kobject *kobj,		\
				    काष्ठा attribute *attr,		\
				    स्थिर अक्षर *buf, sमाप_प्रकार count)	\
	अणु                                                               \
									\
		वापस store_min_max_freq_khz(kobj, attr, buf, count,	\
					      min_max);			\
	पूर्ण

#घोषणा show_uncore_min_max(name, min_max)				\
	अटल sमाप_प्रकार show_##name(काष्ठा kobject *kobj,		\
				   काष्ठा attribute *attr, अक्षर *buf)	\
	अणु                                                               \
									\
		वापस show_min_max_freq_khz(kobj, attr, buf, min_max); \
	पूर्ण

store_uncore_min_max(min_freq_khz, 0);
store_uncore_min_max(max_freq_khz, 1);

show_uncore_min_max(min_freq_khz, 0);
show_uncore_min_max(max_freq_khz, 1);

define_one_uncore_rw(min_freq_khz);
define_one_uncore_rw(max_freq_khz);

अटल काष्ठा attribute *uncore_attrs[] = अणु
	&initial_min_freq_khz.attr,
	&initial_max_freq_khz.attr,
	&max_freq_khz.attr,
	&min_freq_khz.attr,
	शून्य
पूर्ण;

अटल व्योम uncore_sysfs_entry_release(काष्ठा kobject *kobj)
अणु
	काष्ठा uncore_data *data = to_uncore_data(kobj);

	complete(&data->kobj_unरेजिस्टर);
पूर्ण

अटल काष्ठा kobj_type uncore_ktype = अणु
	.release = uncore_sysfs_entry_release,
	.sysfs_ops = &kobj_sysfs_ops,
	.शेष_attrs = uncore_attrs,
पूर्ण;

/* Caller provides protection */
अटल काष्ठा uncore_data *uncore_get_instance(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक id = topology_logical_die_id(cpu);

	अगर (id >= 0 && id < uncore_max_entries)
		वापस &uncore_instances[id];

	वापस शून्य;
पूर्ण

अटल व्योम uncore_add_die_entry(पूर्णांक cpu)
अणु
	काष्ठा uncore_data *data;

	mutex_lock(&uncore_lock);
	data = uncore_get_instance(cpu);
	अगर (!data) अणु
		mutex_unlock(&uncore_lock);
		वापस;
	पूर्ण

	अगर (data->valid) अणु
		/* control cpu changed */
		data->control_cpu = cpu;
	पूर्ण अन्यथा अणु
		अक्षर str[64];
		पूर्णांक ret;

		स_रखो(data, 0, माप(*data));
		प्र_लिखो(str, "package_%02d_die_%02d",
			topology_physical_package_id(cpu),
			topology_die_id(cpu));

		uncore_पढ़ो_ratio(data, &data->initial_min_freq_khz,
				  &data->initial_max_freq_khz);

		init_completion(&data->kobj_unरेजिस्टर);

		ret = kobject_init_and_add(&data->kobj, &uncore_ktype,
					   uncore_root_kobj, str);
		अगर (!ret) अणु
			data->control_cpu = cpu;
			data->valid = true;
		पूर्ण
	पूर्ण
	mutex_unlock(&uncore_lock);
पूर्ण

/* Last CPU in this die is offline, make control cpu invalid */
अटल व्योम uncore_हटाओ_die_entry(पूर्णांक cpu)
अणु
	काष्ठा uncore_data *data;

	mutex_lock(&uncore_lock);
	data = uncore_get_instance(cpu);
	अगर (data)
		data->control_cpu = -1;
	mutex_unlock(&uncore_lock);
पूर्ण

अटल पूर्णांक uncore_event_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक target;

	/* Check अगर there is an online cpu in the package क्रम uncore MSR */
	target = cpumask_any_and(&uncore_cpu_mask, topology_die_cpumask(cpu));
	अगर (target < nr_cpu_ids)
		वापस 0;

	/* Use this CPU on this die as a control CPU */
	cpumask_set_cpu(cpu, &uncore_cpu_mask);
	uncore_add_die_entry(cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक uncore_event_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक target;

	/* Check अगर existing cpu is used क्रम uncore MSRs */
	अगर (!cpumask_test_and_clear_cpu(cpu, &uncore_cpu_mask))
		वापस 0;

	/* Find a new cpu to set uncore MSR */
	target = cpumask_any_but(topology_die_cpumask(cpu), cpu);

	अगर (target < nr_cpu_ids) अणु
		cpumask_set_cpu(target, &uncore_cpu_mask);
		uncore_add_die_entry(target);
	पूर्ण अन्यथा अणु
		uncore_हटाओ_die_entry(cpu);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uncore_pm_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ mode,
			    व्योम *_unused)
अणु
	पूर्णांक cpu;

	चयन (mode) अणु
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
	हाल PM_POST_SUSPEND:
		क्रम_each_cpu(cpu, &uncore_cpu_mask) अणु
			काष्ठा uncore_data *data;
			पूर्णांक ret;

			data = uncore_get_instance(cpu);
			अगर (!data || !data->valid || !data->stored_uncore_data)
				जारी;

			ret = wrmsrl_on_cpu(cpu, MSR_UNCORE_RATIO_LIMIT,
					    data->stored_uncore_data);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block uncore_pm_nb = अणु
	.notअगरier_call = uncore_pm_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_uncore_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_G,	शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X,	शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_D,	शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_X,	शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_X,	शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_D,	शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(SAPPHIRERAPIDS_X, शून्य),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init पूर्णांकel_uncore_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	पूर्णांक ret;

	id = x86_match_cpu(पूर्णांकel_uncore_cpu_ids);
	अगर (!id)
		वापस -ENODEV;

	uncore_max_entries = topology_max_packages() *
					topology_max_die_per_package();
	uncore_instances = kसुस्मृति(uncore_max_entries,
				   माप(*uncore_instances), GFP_KERNEL);
	अगर (!uncore_instances)
		वापस -ENOMEM;

	uncore_root_kobj = kobject_create_and_add("intel_uncore_frequency",
						  &cpu_subsys.dev_root->kobj);
	अगर (!uncore_root_kobj) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN,
				"platform/x86/uncore-freq:online",
				uncore_event_cpu_online,
				uncore_event_cpu_offline);
	अगर (ret < 0)
		जाओ err_rem_kobj;

	uncore_hp_state = ret;

	ret = रेजिस्टर_pm_notअगरier(&uncore_pm_nb);
	अगर (ret)
		जाओ err_rem_state;

	वापस 0;

err_rem_state:
	cpuhp_हटाओ_state(uncore_hp_state);
err_rem_kobj:
	kobject_put(uncore_root_kobj);
err_मुक्त:
	kमुक्त(uncore_instances);

	वापस ret;
पूर्ण
module_init(पूर्णांकel_uncore_init)

अटल व्योम __निकास पूर्णांकel_uncore_निकास(व्योम)
अणु
	पूर्णांक i;

	unरेजिस्टर_pm_notअगरier(&uncore_pm_nb);
	cpuhp_हटाओ_state(uncore_hp_state);
	क्रम (i = 0; i < uncore_max_entries; ++i) अणु
		अगर (uncore_instances[i].valid) अणु
			kobject_put(&uncore_instances[i].kobj);
			रुको_क्रम_completion(&uncore_instances[i].kobj_unरेजिस्टर);
		पूर्ण
	पूर्ण
	kobject_put(uncore_root_kobj);
	kमुक्त(uncore_instances);
पूर्ण
module_निकास(पूर्णांकel_uncore_निकास)

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Uncore Frequency Limits Driver");

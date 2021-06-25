<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Energy Model of devices
 *
 * Copyright (c) 2018-2020, Arm ltd.
 * Written by: Quentin Perret, Arm ltd.
 * Improvements provided by: Lukasz Luba, Arm ltd.
 */

#घोषणा pr_fmt(fmt) "energy_model: " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/energy_model.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/slab.h>

/*
 * Mutex serializing the registrations of perक्रमmance करोमुख्यs and letting
 * callbacks defined by drivers sleep.
 */
अटल DEFINE_MUTEX(em_pd_mutex);

अटल bool _is_cpu_device(काष्ठा device *dev)
अणु
	वापस (dev->bus == &cpu_subsys);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल काष्ठा dentry *rootdir;

अटल व्योम em_debug_create_ps(काष्ठा em_perf_state *ps, काष्ठा dentry *pd)
अणु
	काष्ठा dentry *d;
	अक्षर name[24];

	snम_लिखो(name, माप(name), "ps:%lu", ps->frequency);

	/* Create per-ps directory */
	d = debugfs_create_dir(name, pd);
	debugfs_create_uदीर्घ("frequency", 0444, d, &ps->frequency);
	debugfs_create_uदीर्घ("power", 0444, d, &ps->घातer);
	debugfs_create_uदीर्घ("cost", 0444, d, &ps->cost);
पूर्ण

अटल पूर्णांक em_debug_cpus_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	seq_म_लिखो(s, "%*pbl\n", cpumask_pr_args(to_cpumask(s->निजी)));

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(em_debug_cpus);

अटल पूर्णांक em_debug_units_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा em_perf_करोमुख्य *pd = s->निजी;
	अक्षर *units = pd->milliwatts ? "milliWatts" : "bogoWatts";

	seq_म_लिखो(s, "%s\n", units);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(em_debug_units);

अटल व्योम em_debug_create_pd(काष्ठा device *dev)
अणु
	काष्ठा dentry *d;
	पूर्णांक i;

	/* Create the directory of the perक्रमmance करोमुख्य */
	d = debugfs_create_dir(dev_name(dev), rootdir);

	अगर (_is_cpu_device(dev))
		debugfs_create_file("cpus", 0444, d, dev->em_pd->cpus,
				    &em_debug_cpus_fops);

	debugfs_create_file("units", 0444, d, dev->em_pd, &em_debug_units_fops);

	/* Create a sub-directory क्रम each perक्रमmance state */
	क्रम (i = 0; i < dev->em_pd->nr_perf_states; i++)
		em_debug_create_ps(&dev->em_pd->table[i], d);

पूर्ण

अटल व्योम em_debug_हटाओ_pd(काष्ठा device *dev)
अणु
	काष्ठा dentry *debug_dir;

	debug_dir = debugfs_lookup(dev_name(dev), rootdir);
	debugfs_हटाओ_recursive(debug_dir);
पूर्ण

अटल पूर्णांक __init em_debug_init(व्योम)
अणु
	/* Create /sys/kernel/debug/energy_model directory */
	rootdir = debugfs_create_dir("energy_model", शून्य);

	वापस 0;
पूर्ण
fs_initcall(em_debug_init);
#अन्यथा /* CONFIG_DEBUG_FS */
अटल व्योम em_debug_create_pd(काष्ठा device *dev) अणुपूर्ण
अटल व्योम em_debug_हटाओ_pd(काष्ठा device *dev) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक em_create_perf_table(काष्ठा device *dev, काष्ठा em_perf_करोमुख्य *pd,
				पूर्णांक nr_states, काष्ठा em_data_callback *cb)
अणु
	अचिन्हित दीर्घ opp_eff, prev_opp_eff = अच_दीर्घ_उच्च;
	अचिन्हित दीर्घ घातer, freq, prev_freq = 0;
	काष्ठा em_perf_state *table;
	पूर्णांक i, ret;
	u64 fmax;

	table = kसुस्मृति(nr_states, माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	/* Build the list of perक्रमmance states क्रम this perक्रमmance करोमुख्य */
	क्रम (i = 0, freq = 0; i < nr_states; i++, freq++) अणु
		/*
		 * active_घातer() is a driver callback which उच्चमानs 'freq' to
		 * lowest perक्रमmance state of 'dev' above 'freq' and updates
		 * 'power' and 'freq' accordingly.
		 */
		ret = cb->active_घातer(&घातer, &freq, dev);
		अगर (ret) अणु
			dev_err(dev, "EM: invalid perf. state: %d\n",
				ret);
			जाओ मुक्त_ps_table;
		पूर्ण

		/*
		 * We expect the driver callback to increase the frequency क्रम
		 * higher perक्रमmance states.
		 */
		अगर (freq <= prev_freq) अणु
			dev_err(dev, "EM: non-increasing freq: %lu\n",
				freq);
			जाओ मुक्त_ps_table;
		पूर्ण

		/*
		 * The घातer वापसed by active_state() is expected to be
		 * positive and to fit पूर्णांकo 16 bits.
		 */
		अगर (!घातer || घातer > EM_MAX_POWER) अणु
			dev_err(dev, "EM: invalid power: %lu\n",
				घातer);
			जाओ मुक्त_ps_table;
		पूर्ण

		table[i].घातer = घातer;
		table[i].frequency = prev_freq = freq;

		/*
		 * The hertz/watts efficiency ratio should decrease as the
		 * frequency grows on sane platक्रमms. But this isn't always
		 * true in practice so warn the user अगर a higher OPP is more
		 * घातer efficient than a lower one.
		 */
		opp_eff = freq / घातer;
		अगर (opp_eff >= prev_opp_eff)
			dev_dbg(dev, "EM: hertz/watts ratio non-monotonically decreasing: em_perf_state %d >= em_perf_state%d\n",
					i, i - 1);
		prev_opp_eff = opp_eff;
	पूर्ण

	/* Compute the cost of each perक्रमmance state. */
	fmax = (u64) table[nr_states - 1].frequency;
	क्रम (i = 0; i < nr_states; i++) अणु
		table[i].cost = भाग64_u64(fmax * table[i].घातer,
					  table[i].frequency);
	पूर्ण

	pd->table = table;
	pd->nr_perf_states = nr_states;

	वापस 0;

मुक्त_ps_table:
	kमुक्त(table);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक em_create_pd(काष्ठा device *dev, पूर्णांक nr_states,
			काष्ठा em_data_callback *cb, cpumask_t *cpus)
अणु
	काष्ठा em_perf_करोमुख्य *pd;
	काष्ठा device *cpu_dev;
	पूर्णांक cpu, ret;

	अगर (_is_cpu_device(dev)) अणु
		pd = kzalloc(माप(*pd) + cpumask_size(), GFP_KERNEL);
		अगर (!pd)
			वापस -ENOMEM;

		cpumask_copy(em_span_cpus(pd), cpus);
	पूर्ण अन्यथा अणु
		pd = kzalloc(माप(*pd), GFP_KERNEL);
		अगर (!pd)
			वापस -ENOMEM;
	पूर्ण

	ret = em_create_perf_table(dev, pd, nr_states, cb);
	अगर (ret) अणु
		kमुक्त(pd);
		वापस ret;
	पूर्ण

	अगर (_is_cpu_device(dev))
		क्रम_each_cpu(cpu, cpus) अणु
			cpu_dev = get_cpu_device(cpu);
			cpu_dev->em_pd = pd;
		पूर्ण

	dev->em_pd = pd;

	वापस 0;
पूर्ण

/**
 * em_pd_get() - Return the perक्रमmance करोमुख्य क्रम a device
 * @dev : Device to find the perक्रमmance करोमुख्य क्रम
 *
 * Returns the perक्रमmance करोमुख्य to which @dev beदीर्घs, or शून्य अगर it करोesn't
 * exist.
 */
काष्ठा em_perf_करोमुख्य *em_pd_get(काष्ठा device *dev)
अणु
	अगर (IS_ERR_OR_शून्य(dev))
		वापस शून्य;

	वापस dev->em_pd;
पूर्ण
EXPORT_SYMBOL_GPL(em_pd_get);

/**
 * em_cpu_get() - Return the perक्रमmance करोमुख्य क्रम a CPU
 * @cpu : CPU to find the perक्रमmance करोमुख्य क्रम
 *
 * Returns the perक्रमmance करोमुख्य to which @cpu beदीर्घs, or शून्य अगर it करोesn't
 * exist.
 */
काष्ठा em_perf_करोमुख्य *em_cpu_get(पूर्णांक cpu)
अणु
	काष्ठा device *cpu_dev;

	cpu_dev = get_cpu_device(cpu);
	अगर (!cpu_dev)
		वापस शून्य;

	वापस em_pd_get(cpu_dev);
पूर्ण
EXPORT_SYMBOL_GPL(em_cpu_get);

/**
 * em_dev_रेजिस्टर_perf_करोमुख्य() - Register the Energy Model (EM) क्रम a device
 * @dev		: Device क्रम which the EM is to रेजिस्टर
 * @nr_states	: Number of perक्रमmance states to रेजिस्टर
 * @cb		: Callback functions providing the data of the Energy Model
 * @cpus	: Poपूर्णांकer to cpumask_t, which in हाल of a CPU device is
 *		obligatory. It can be taken from i.e. 'policy->cpus'. For other
 *		type of devices this should be set to शून्य.
 * @milliwatts	: Flag indicating that the घातer values are in milliWatts or
 *		in some other scale. It must be set properly.
 *
 * Create Energy Model tables क्रम a perक्रमmance करोमुख्य using the callbacks
 * defined in cb.
 *
 * The @milliwatts is important to set with correct value. Some kernel
 * sub-प्रणालीs might rely on this flag and check अगर all devices in the EM are
 * using the same scale.
 *
 * If multiple clients रेजिस्टर the same perक्रमmance करोमुख्य, all but the first
 * registration will be ignored.
 *
 * Return 0 on success
 */
पूर्णांक em_dev_रेजिस्टर_perf_करोमुख्य(काष्ठा device *dev, अचिन्हित पूर्णांक nr_states,
				काष्ठा em_data_callback *cb, cpumask_t *cpus,
				bool milliwatts)
अणु
	अचिन्हित दीर्घ cap, prev_cap = 0;
	पूर्णांक cpu, ret;

	अगर (!dev || !nr_states || !cb)
		वापस -EINVAL;

	/*
	 * Use a mutex to serialize the registration of perक्रमmance करोमुख्यs and
	 * let the driver-defined callback functions sleep.
	 */
	mutex_lock(&em_pd_mutex);

	अगर (dev->em_pd) अणु
		ret = -EEXIST;
		जाओ unlock;
	पूर्ण

	अगर (_is_cpu_device(dev)) अणु
		अगर (!cpus) अणु
			dev_err(dev, "EM: invalid CPU mask\n");
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		क्रम_each_cpu(cpu, cpus) अणु
			अगर (em_cpu_get(cpu)) अणु
				dev_err(dev, "EM: exists for CPU%d\n", cpu);
				ret = -EEXIST;
				जाओ unlock;
			पूर्ण
			/*
			 * All CPUs of a करोमुख्य must have the same
			 * micro-architecture since they all share the same
			 * table.
			 */
			cap = arch_scale_cpu_capacity(cpu);
			अगर (prev_cap && prev_cap != cap) अणु
				dev_err(dev, "EM: CPUs of %*pbl must have the same capacity\n",
					cpumask_pr_args(cpus));

				ret = -EINVAL;
				जाओ unlock;
			पूर्ण
			prev_cap = cap;
		पूर्ण
	पूर्ण

	ret = em_create_pd(dev, nr_states, cb, cpus);
	अगर (ret)
		जाओ unlock;

	dev->em_pd->milliwatts = milliwatts;

	em_debug_create_pd(dev);
	dev_info(dev, "EM: created perf domain\n");

unlock:
	mutex_unlock(&em_pd_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(em_dev_रेजिस्टर_perf_करोमुख्य);

/**
 * em_dev_unरेजिस्टर_perf_करोमुख्य() - Unरेजिस्टर Energy Model (EM) क्रम a device
 * @dev		: Device क्रम which the EM is रेजिस्टरed
 *
 * Unरेजिस्टर the EM क्रम the specअगरied @dev (but not a CPU device).
 */
व्योम em_dev_unरेजिस्टर_perf_करोमुख्य(काष्ठा device *dev)
अणु
	अगर (IS_ERR_OR_शून्य(dev) || !dev->em_pd)
		वापस;

	अगर (_is_cpu_device(dev))
		वापस;

	/*
	 * The mutex separates all रेजिस्टर/unरेजिस्टर requests and protects
	 * from potential clean-up/setup issues in the debugfs directories.
	 * The debugfs directory name is the same as device's name.
	 */
	mutex_lock(&em_pd_mutex);
	em_debug_हटाओ_pd(dev);

	kमुक्त(dev->em_pd->table);
	kमुक्त(dev->em_pd);
	dev->em_pd = शून्य;
	mutex_unlock(&em_pd_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(em_dev_unरेजिस्टर_perf_करोमुख्य);

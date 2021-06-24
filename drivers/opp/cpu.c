<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic OPP helper पूर्णांकerface क्रम CPU device
 *
 * Copyright (C) 2009-2014 Texas Instruments Incorporated.
 *	Nishanth Menon
 *	Romit Dasgupta
 *	Kevin Hilman
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>

#समावेश "opp.h"

#अगर_घोषित CONFIG_CPU_FREQ

/**
 * dev_pm_opp_init_cpufreq_table() - create a cpufreq table क्रम a device
 * @dev:	device क्रम which we करो this operation
 * @table:	Cpufreq table वापसed back to caller
 *
 * Generate a cpufreq table क्रम a provided device- this assumes that the
 * opp table is alपढ़ोy initialized and पढ़ोy क्रम usage.
 *
 * This function allocates required memory क्रम the cpufreq table. It is
 * expected that the caller करोes the required मुख्यtenance such as मुक्तing
 * the table as required.
 *
 * Returns -EINVAL क्रम bad poपूर्णांकers, -ENODEV अगर the device is not found, -ENOMEM
 * अगर no memory available क्रम the operation (table is not populated), वापसs 0
 * अगर successful and table is populated.
 *
 * WARNING: It is  important क्रम the callers to ensure refreshing their copy of
 * the table अगर any of the mentioned functions have been invoked in the पूर्णांकerim.
 */
पूर्णांक dev_pm_opp_init_cpufreq_table(काष्ठा device *dev,
				  काष्ठा cpufreq_frequency_table **table)
अणु
	काष्ठा dev_pm_opp *opp;
	काष्ठा cpufreq_frequency_table *freq_table = शून्य;
	पूर्णांक i, max_opps, ret = 0;
	अचिन्हित दीर्घ rate;

	max_opps = dev_pm_opp_get_opp_count(dev);
	अगर (max_opps <= 0)
		वापस max_opps ? max_opps : -ENODATA;

	freq_table = kसुस्मृति((max_opps + 1), माप(*freq_table), GFP_KERNEL);
	अगर (!freq_table)
		वापस -ENOMEM;

	क्रम (i = 0, rate = 0; i < max_opps; i++, rate++) अणु
		/* find next rate */
		opp = dev_pm_opp_find_freq_उच्चमान(dev, &rate);
		अगर (IS_ERR(opp)) अणु
			ret = PTR_ERR(opp);
			जाओ out;
		पूर्ण
		freq_table[i].driver_data = i;
		freq_table[i].frequency = rate / 1000;

		/* Is Boost/turbo opp ? */
		अगर (dev_pm_opp_is_turbo(opp))
			freq_table[i].flags = CPUFREQ_BOOST_FREQ;

		dev_pm_opp_put(opp);
	पूर्ण

	freq_table[i].driver_data = i;
	freq_table[i].frequency = CPUFREQ_TABLE_END;

	*table = &freq_table[0];

out:
	अगर (ret)
		kमुक्त(freq_table);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_init_cpufreq_table);

/**
 * dev_pm_opp_मुक्त_cpufreq_table() - मुक्त the cpufreq table
 * @dev:	device क्रम which we करो this operation
 * @table:	table to मुक्त
 *
 * Free up the table allocated by dev_pm_opp_init_cpufreq_table
 */
व्योम dev_pm_opp_मुक्त_cpufreq_table(काष्ठा device *dev,
				   काष्ठा cpufreq_frequency_table **table)
अणु
	अगर (!table)
		वापस;

	kमुक्त(*table);
	*table = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_मुक्त_cpufreq_table);
#पूर्ण_अगर	/* CONFIG_CPU_FREQ */

व्योम _dev_pm_opp_cpumask_हटाओ_table(स्थिर काष्ठा cpumask *cpumask,
				      पूर्णांक last_cpu)
अणु
	काष्ठा device *cpu_dev;
	पूर्णांक cpu;

	WARN_ON(cpumask_empty(cpumask));

	क्रम_each_cpu(cpu, cpumask) अणु
		अगर (cpu == last_cpu)
			अवरोध;

		cpu_dev = get_cpu_device(cpu);
		अगर (!cpu_dev) अणु
			pr_err("%s: failed to get cpu%d device\n", __func__,
			       cpu);
			जारी;
		पूर्ण

		dev_pm_opp_हटाओ_table(cpu_dev);
	पूर्ण
पूर्ण

/**
 * dev_pm_opp_cpumask_हटाओ_table() - Removes OPP table क्रम @cpumask
 * @cpumask:	cpumask क्रम which OPP table needs to be हटाओd
 *
 * This हटाओs the OPP tables क्रम CPUs present in the @cpumask.
 * This should be used to हटाओ all the OPPs entries associated with
 * the cpus in @cpumask.
 */
व्योम dev_pm_opp_cpumask_हटाओ_table(स्थिर काष्ठा cpumask *cpumask)
अणु
	_dev_pm_opp_cpumask_हटाओ_table(cpumask, -1);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_cpumask_हटाओ_table);

/**
 * dev_pm_opp_set_sharing_cpus() - Mark OPP table as shared by few CPUs
 * @cpu_dev:	CPU device क्रम which we करो this operation
 * @cpumask:	cpumask of the CPUs which share the OPP table with @cpu_dev
 *
 * This marks OPP table of the @cpu_dev as shared by the CPUs present in
 * @cpumask.
 *
 * Returns -ENODEV अगर OPP table isn't alपढ़ोy present.
 */
पूर्णांक dev_pm_opp_set_sharing_cpus(काष्ठा device *cpu_dev,
				स्थिर काष्ठा cpumask *cpumask)
अणु
	काष्ठा opp_device *opp_dev;
	काष्ठा opp_table *opp_table;
	काष्ठा device *dev;
	पूर्णांक cpu, ret = 0;

	opp_table = _find_opp_table(cpu_dev);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	क्रम_each_cpu(cpu, cpumask) अणु
		अगर (cpu == cpu_dev->id)
			जारी;

		dev = get_cpu_device(cpu);
		अगर (!dev) अणु
			dev_err(cpu_dev, "%s: failed to get cpu%d device\n",
				__func__, cpu);
			जारी;
		पूर्ण

		opp_dev = _add_opp_dev(dev, opp_table);
		अगर (!opp_dev) अणु
			dev_err(dev, "%s: failed to add opp-dev for cpu%d device\n",
				__func__, cpu);
			जारी;
		पूर्ण

		/* Mark opp-table as multiple CPUs are sharing it now */
		opp_table->shared_opp = OPP_TABLE_ACCESS_SHARED;
	पूर्ण

	dev_pm_opp_put_opp_table(opp_table);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_set_sharing_cpus);

/**
 * dev_pm_opp_get_sharing_cpus() - Get cpumask of CPUs sharing OPPs with @cpu_dev
 * @cpu_dev:	CPU device क्रम which we करो this operation
 * @cpumask:	cpumask to update with inक्रमmation of sharing CPUs
 *
 * This updates the @cpumask with CPUs that are sharing OPPs with @cpu_dev.
 *
 * Returns -ENODEV अगर OPP table isn't alपढ़ोy present and -EINVAL अगर the OPP
 * table's status is access-unknown.
 */
पूर्णांक dev_pm_opp_get_sharing_cpus(काष्ठा device *cpu_dev, काष्ठा cpumask *cpumask)
अणु
	काष्ठा opp_device *opp_dev;
	काष्ठा opp_table *opp_table;
	पूर्णांक ret = 0;

	opp_table = _find_opp_table(cpu_dev);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	अगर (opp_table->shared_opp == OPP_TABLE_ACCESS_UNKNOWN) अणु
		ret = -EINVAL;
		जाओ put_opp_table;
	पूर्ण

	cpumask_clear(cpumask);

	अगर (opp_table->shared_opp == OPP_TABLE_ACCESS_SHARED) अणु
		mutex_lock(&opp_table->lock);
		list_क्रम_each_entry(opp_dev, &opp_table->dev_list, node)
			cpumask_set_cpu(opp_dev->dev->id, cpumask);
		mutex_unlock(&opp_table->lock);
	पूर्ण अन्यथा अणु
		cpumask_set_cpu(cpu_dev->id, cpumask);
	पूर्ण

put_opp_table:
	dev_pm_opp_put_opp_table(opp_table);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_sharing_cpus);

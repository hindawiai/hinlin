<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/cpufreq/freq_table.c
 *
 * Copyright (C) 2002 - 2003 Dominik Broकरोwski
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpufreq.h>
#समावेश <linux/module.h>

/*********************************************************************
 *                     FREQUENCY TABLE HELPERS                       *
 *********************************************************************/

bool policy_has_boost_freq(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *pos, *table = policy->freq_table;

	अगर (!table)
		वापस false;

	cpufreq_क्रम_each_valid_entry(pos, table)
		अगर (pos->flags & CPUFREQ_BOOST_FREQ)
			वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(policy_has_boost_freq);

पूर्णांक cpufreq_frequency_table_cpuinfo(काष्ठा cpufreq_policy *policy,
				    काष्ठा cpufreq_frequency_table *table)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक min_freq = ~0;
	अचिन्हित पूर्णांक max_freq = 0;
	अचिन्हित पूर्णांक freq;

	cpufreq_क्रम_each_valid_entry(pos, table) अणु
		freq = pos->frequency;

		अगर (!cpufreq_boost_enabled()
		    && (pos->flags & CPUFREQ_BOOST_FREQ))
			जारी;

		pr_debug("table entry %u: %u kHz\n", (पूर्णांक)(pos - table), freq);
		अगर (freq < min_freq)
			min_freq = freq;
		अगर (freq > max_freq)
			max_freq = freq;
	पूर्ण

	policy->min = policy->cpuinfo.min_freq = min_freq;
	policy->max = max_freq;
	/*
	 * If the driver has set its own cpuinfo.max_freq above max_freq, leave
	 * it as is.
	 */
	अगर (policy->cpuinfo.max_freq < max_freq)
		policy->max = policy->cpuinfo.max_freq = max_freq;

	अगर (policy->min == ~0)
		वापस -EINVAL;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक cpufreq_frequency_table_verअगरy(काष्ठा cpufreq_policy_data *policy,
				   काष्ठा cpufreq_frequency_table *table)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक freq, next_larger = ~0;
	bool found = false;

	pr_debug("request for verification of policy (%u - %u kHz) for cpu %u\n",
					policy->min, policy->max, policy->cpu);

	cpufreq_verअगरy_within_cpu_limits(policy);

	cpufreq_क्रम_each_valid_entry(pos, table) अणु
		freq = pos->frequency;

		अगर ((freq >= policy->min) && (freq <= policy->max)) अणु
			found = true;
			अवरोध;
		पूर्ण

		अगर ((next_larger > freq) && (freq > policy->max))
			next_larger = freq;
	पूर्ण

	अगर (!found) अणु
		policy->max = next_larger;
		cpufreq_verअगरy_within_cpu_limits(policy);
	पूर्ण

	pr_debug("verification lead to (%u - %u kHz) for cpu %u\n",
				policy->min, policy->max, policy->cpu);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_frequency_table_verअगरy);

/*
 * Generic routine to verअगरy policy & frequency table, requires driver to set
 * policy->freq_table prior to it.
 */
पूर्णांक cpufreq_generic_frequency_table_verअगरy(काष्ठा cpufreq_policy_data *policy)
अणु
	अगर (!policy->freq_table)
		वापस -ENODEV;

	वापस cpufreq_frequency_table_verअगरy(policy, policy->freq_table);
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_generic_frequency_table_verअगरy);

पूर्णांक cpufreq_table_index_unsorted(काष्ठा cpufreq_policy *policy,
				 अचिन्हित पूर्णांक target_freq,
				 अचिन्हित पूर्णांक relation)
अणु
	काष्ठा cpufreq_frequency_table optimal = अणु
		.driver_data = ~0,
		.frequency = 0,
	पूर्ण;
	काष्ठा cpufreq_frequency_table suboptimal = अणु
		.driver_data = ~0,
		.frequency = 0,
	पूर्ण;
	काष्ठा cpufreq_frequency_table *pos;
	काष्ठा cpufreq_frequency_table *table = policy->freq_table;
	अचिन्हित पूर्णांक freq, dअगरf, i = 0;
	पूर्णांक index;

	pr_debug("request for target %u kHz (relation: %u) for cpu %u\n",
					target_freq, relation, policy->cpu);

	चयन (relation) अणु
	हाल CPUFREQ_RELATION_H:
		suboptimal.frequency = ~0;
		अवरोध;
	हाल CPUFREQ_RELATION_L:
	हाल CPUFREQ_RELATION_C:
		optimal.frequency = ~0;
		अवरोध;
	पूर्ण

	cpufreq_क्रम_each_valid_entry_idx(pos, table, i) अणु
		freq = pos->frequency;

		अगर ((freq < policy->min) || (freq > policy->max))
			जारी;
		अगर (freq == target_freq) अणु
			optimal.driver_data = i;
			अवरोध;
		पूर्ण
		चयन (relation) अणु
		हाल CPUFREQ_RELATION_H:
			अगर (freq < target_freq) अणु
				अगर (freq >= optimal.frequency) अणु
					optimal.frequency = freq;
					optimal.driver_data = i;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (freq <= suboptimal.frequency) अणु
					suboptimal.frequency = freq;
					suboptimal.driver_data = i;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल CPUFREQ_RELATION_L:
			अगर (freq > target_freq) अणु
				अगर (freq <= optimal.frequency) अणु
					optimal.frequency = freq;
					optimal.driver_data = i;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (freq >= suboptimal.frequency) अणु
					suboptimal.frequency = freq;
					suboptimal.driver_data = i;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल CPUFREQ_RELATION_C:
			dअगरf = असल(freq - target_freq);
			अगर (dअगरf < optimal.frequency ||
			    (dअगरf == optimal.frequency &&
			     freq > table[optimal.driver_data].frequency)) अणु
				optimal.frequency = dअगरf;
				optimal.driver_data = i;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (optimal.driver_data > i) अणु
		अगर (suboptimal.driver_data > i) अणु
			WARN(1, "Invalid frequency table: %d\n", policy->cpu);
			वापस 0;
		पूर्ण

		index = suboptimal.driver_data;
	पूर्ण अन्यथा
		index = optimal.driver_data;

	pr_debug("target index is %u, freq is:%u kHz\n", index,
		 table[index].frequency);
	वापस index;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_table_index_unsorted);

पूर्णांक cpufreq_frequency_table_get_index(काष्ठा cpufreq_policy *policy,
		अचिन्हित पूर्णांक freq)
अणु
	काष्ठा cpufreq_frequency_table *pos, *table = policy->freq_table;
	पूर्णांक idx;

	अगर (unlikely(!table)) अणु
		pr_debug("%s: Unable to find frequency table\n", __func__);
		वापस -ENOENT;
	पूर्ण

	cpufreq_क्रम_each_valid_entry_idx(pos, table, idx)
		अगर (pos->frequency == freq)
			वापस idx;

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(cpufreq_frequency_table_get_index);

/*
 * show_available_freqs - show available frequencies क्रम the specअगरied CPU
 */
अटल sमाप_प्रकार show_available_freqs(काष्ठा cpufreq_policy *policy, अक्षर *buf,
				    bool show_boost)
अणु
	sमाप_प्रकार count = 0;
	काष्ठा cpufreq_frequency_table *pos, *table = policy->freq_table;

	अगर (!table)
		वापस -ENODEV;

	cpufreq_क्रम_each_valid_entry(pos, table) अणु
		/*
		 * show_boost = true and driver_data = BOOST freq
		 * display BOOST freqs
		 *
		 * show_boost = false and driver_data = BOOST freq
		 * show_boost = true and driver_data != BOOST freq
		 * जारी - करो not display anything
		 *
		 * show_boost = false and driver_data != BOOST freq
		 * display NON BOOST freqs
		 */
		अगर (show_boost ^ (pos->flags & CPUFREQ_BOOST_FREQ))
			जारी;

		count += प्र_लिखो(&buf[count], "%d ", pos->frequency);
	पूर्ण
	count += प्र_लिखो(&buf[count], "\n");

	वापस count;

पूर्ण

#घोषणा cpufreq_attr_available_freq(_name)	  \
काष्ठा freq_attr cpufreq_freq_attr_##_name##_freqs =     \
__ATTR_RO(_name##_frequencies)

/*
 * scaling_available_frequencies_show - show available normal frequencies क्रम
 * the specअगरied CPU
 */
अटल sमाप_प्रकार scaling_available_frequencies_show(काष्ठा cpufreq_policy *policy,
						  अक्षर *buf)
अणु
	वापस show_available_freqs(policy, buf, false);
पूर्ण
cpufreq_attr_available_freq(scaling_available);
EXPORT_SYMBOL_GPL(cpufreq_freq_attr_scaling_available_freqs);

/*
 * scaling_boost_frequencies_show - show available boost frequencies क्रम
 * the specअगरied CPU
 */
अटल sमाप_प्रकार scaling_boost_frequencies_show(काष्ठा cpufreq_policy *policy,
					      अक्षर *buf)
अणु
	वापस show_available_freqs(policy, buf, true);
पूर्ण
cpufreq_attr_available_freq(scaling_boost);
EXPORT_SYMBOL_GPL(cpufreq_freq_attr_scaling_boost_freqs);

काष्ठा freq_attr *cpufreq_generic_attr[] = अणु
	&cpufreq_freq_attr_scaling_available_freqs,
	शून्य,
पूर्ण;
EXPORT_SYMBOL_GPL(cpufreq_generic_attr);

अटल पूर्णांक set_freq_table_sorted(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *pos, *table = policy->freq_table;
	काष्ठा cpufreq_frequency_table *prev = शून्य;
	पूर्णांक ascending = 0;

	policy->freq_table_sorted = CPUFREQ_TABLE_UNSORTED;

	cpufreq_क्रम_each_valid_entry(pos, table) अणु
		अगर (!prev) अणु
			prev = pos;
			जारी;
		पूर्ण

		अगर (pos->frequency == prev->frequency) अणु
			pr_warn("Duplicate freq-table entries: %u\n",
				pos->frequency);
			वापस -EINVAL;
		पूर्ण

		/* Frequency increased from prev to pos */
		अगर (pos->frequency > prev->frequency) अणु
			/* But frequency was decreasing earlier */
			अगर (ascending < 0) अणु
				pr_debug("Freq table is unsorted\n");
				वापस 0;
			पूर्ण

			ascending++;
		पूर्ण अन्यथा अणु
			/* Frequency decreased from prev to pos */

			/* But frequency was increasing earlier */
			अगर (ascending > 0) अणु
				pr_debug("Freq table is unsorted\n");
				वापस 0;
			पूर्ण

			ascending--;
		पूर्ण

		prev = pos;
	पूर्ण

	अगर (ascending > 0)
		policy->freq_table_sorted = CPUFREQ_TABLE_SORTED_ASCENDING;
	अन्यथा
		policy->freq_table_sorted = CPUFREQ_TABLE_SORTED_DESCENDING;

	pr_debug("Freq table is sorted in %s order\n",
		 ascending > 0 ? "ascending" : "descending");

	वापस 0;
पूर्ण

पूर्णांक cpufreq_table_validate_and_sort(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret;

	अगर (!policy->freq_table)
		वापस 0;

	ret = cpufreq_frequency_table_cpuinfo(policy, policy->freq_table);
	अगर (ret)
		वापस ret;

	वापस set_freq_table_sorted(policy);
पूर्ण

MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("CPUfreq frequency table helpers");
MODULE_LICENSE("GPL");

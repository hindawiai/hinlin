<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  drivers/cpufreq/cpufreq_stats.c
 *
 *  Copyright (C) 2003-2004 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>.
 *  (C) 2004 Zou Nan hai <nanhai.zou@पूर्णांकel.com>.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/slab.h>

काष्ठा cpufreq_stats अणु
	अचिन्हित पूर्णांक total_trans;
	अचिन्हित दीर्घ दीर्घ last_समय;
	अचिन्हित पूर्णांक max_state;
	अचिन्हित पूर्णांक state_num;
	अचिन्हित पूर्णांक last_index;
	u64 *समय_in_state;
	अचिन्हित पूर्णांक *freq_table;
	अचिन्हित पूर्णांक *trans_table;

	/* Deferred reset */
	अचिन्हित पूर्णांक reset_pending;
	अचिन्हित दीर्घ दीर्घ reset_समय;
पूर्ण;

अटल व्योम cpufreq_stats_update(काष्ठा cpufreq_stats *stats,
				 अचिन्हित दीर्घ दीर्घ समय)
अणु
	अचिन्हित दीर्घ दीर्घ cur_समय = local_घड़ी();

	stats->समय_in_state[stats->last_index] += cur_समय - समय;
	stats->last_समय = cur_समय;
पूर्ण

अटल व्योम cpufreq_stats_reset_table(काष्ठा cpufreq_stats *stats)
अणु
	अचिन्हित पूर्णांक count = stats->max_state;

	स_रखो(stats->समय_in_state, 0, count * माप(u64));
	स_रखो(stats->trans_table, 0, count * count * माप(पूर्णांक));
	stats->last_समय = local_घड़ी();
	stats->total_trans = 0;

	/* Adjust क्रम the समय elapsed since reset was requested */
	WRITE_ONCE(stats->reset_pending, 0);
	/*
	 * Prevent the reset_समय पढ़ो from being reordered beक्रमe the
	 * reset_pending accesses in cpufreq_stats_record_transition().
	 */
	smp_rmb();
	cpufreq_stats_update(stats, READ_ONCE(stats->reset_समय));
पूर्ण

अटल sमाप_प्रकार show_total_trans(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा cpufreq_stats *stats = policy->stats;

	अगर (READ_ONCE(stats->reset_pending))
		वापस प्र_लिखो(buf, "%d\n", 0);
	अन्यथा
		वापस प्र_लिखो(buf, "%u\n", stats->total_trans);
पूर्ण
cpufreq_freq_attr_ro(total_trans);

अटल sमाप_प्रकार show_समय_in_state(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा cpufreq_stats *stats = policy->stats;
	bool pending = READ_ONCE(stats->reset_pending);
	अचिन्हित दीर्घ दीर्घ समय;
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < stats->state_num; i++) अणु
		अगर (pending) अणु
			अगर (i == stats->last_index) अणु
				/*
				 * Prevent the reset_समय पढ़ो from occurring
				 * beक्रमe the reset_pending पढ़ो above.
				 */
				smp_rmb();
				समय = local_घड़ी() - READ_ONCE(stats->reset_समय);
			पूर्ण अन्यथा अणु
				समय = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			समय = stats->समय_in_state[i];
			अगर (i == stats->last_index)
				समय += local_घड़ी() - stats->last_समय;
		पूर्ण

		len += प्र_लिखो(buf + len, "%u %llu\n", stats->freq_table[i],
			       nsec_to_घड़ी_प्रकार(समय));
	पूर्ण
	वापस len;
पूर्ण
cpufreq_freq_attr_ro(समय_in_state);

/* We करोn't care what is written to the attribute */
अटल sमाप_प्रकार store_reset(काष्ठा cpufreq_policy *policy, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	काष्ठा cpufreq_stats *stats = policy->stats;

	/*
	 * Defer resetting of stats to cpufreq_stats_record_transition() to
	 * aव्योम races.
	 */
	WRITE_ONCE(stats->reset_समय, local_घड़ी());
	/*
	 * The memory barrier below is to prevent the पढ़ोers of reset_समय from
	 * seeing a stale or partially updated value.
	 */
	smp_wmb();
	WRITE_ONCE(stats->reset_pending, 1);

	वापस count;
पूर्ण
cpufreq_freq_attr_wo(reset);

अटल sमाप_प्रकार show_trans_table(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा cpufreq_stats *stats = policy->stats;
	bool pending = READ_ONCE(stats->reset_pending);
	sमाप_प्रकार len = 0;
	पूर्णांक i, j, count;

	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "   From  :    To\n");
	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "         : ");
	क्रम (i = 0; i < stats->state_num; i++) अणु
		अगर (len >= PAGE_SIZE)
			अवरोध;
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%9u ",
				stats->freq_table[i]);
	पूर्ण
	अगर (len >= PAGE_SIZE)
		वापस PAGE_SIZE;

	len += scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");

	क्रम (i = 0; i < stats->state_num; i++) अणु
		अगर (len >= PAGE_SIZE)
			अवरोध;

		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%9u: ",
				stats->freq_table[i]);

		क्रम (j = 0; j < stats->state_num; j++) अणु
			अगर (len >= PAGE_SIZE)
				अवरोध;

			अगर (pending)
				count = 0;
			अन्यथा
				count = stats->trans_table[i * stats->max_state + j];

			len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%9u ", count);
		पूर्ण
		अगर (len >= PAGE_SIZE)
			अवरोध;
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");
	पूर्ण

	अगर (len >= PAGE_SIZE) अणु
		pr_warn_once("cpufreq transition table exceeds PAGE_SIZE. Disabling\n");
		वापस -EFBIG;
	पूर्ण
	वापस len;
पूर्ण
cpufreq_freq_attr_ro(trans_table);

अटल काष्ठा attribute *शेष_attrs[] = अणु
	&total_trans.attr,
	&समय_in_state.attr,
	&reset.attr,
	&trans_table.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group stats_attr_group = अणु
	.attrs = शेष_attrs,
	.name = "stats"
पूर्ण;

अटल पूर्णांक freq_table_get_index(काष्ठा cpufreq_stats *stats, अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक index;
	क्रम (index = 0; index < stats->max_state; index++)
		अगर (stats->freq_table[index] == freq)
			वापस index;
	वापस -1;
पूर्ण

व्योम cpufreq_stats_मुक्त_table(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_stats *stats = policy->stats;

	/* Alपढ़ोy मुक्तd */
	अगर (!stats)
		वापस;

	pr_debug("%s: Free stats table\n", __func__);

	sysfs_हटाओ_group(&policy->kobj, &stats_attr_group);
	kमुक्त(stats->समय_in_state);
	kमुक्त(stats);
	policy->stats = शून्य;
पूर्ण

व्योम cpufreq_stats_create_table(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक i = 0, count = 0, ret = -ENOMEM;
	काष्ठा cpufreq_stats *stats;
	अचिन्हित पूर्णांक alloc_size;
	काष्ठा cpufreq_frequency_table *pos;

	count = cpufreq_table_count_valid_entries(policy);
	अगर (!count)
		वापस;

	/* stats alपढ़ोy initialized */
	अगर (policy->stats)
		वापस;

	stats = kzalloc(माप(*stats), GFP_KERNEL);
	अगर (!stats)
		वापस;

	alloc_size = count * माप(पूर्णांक) + count * माप(u64);

	alloc_size += count * count * माप(पूर्णांक);

	/* Allocate memory क्रम समय_in_state/freq_table/trans_table in one go */
	stats->समय_in_state = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!stats->समय_in_state)
		जाओ मुक्त_stat;

	stats->freq_table = (अचिन्हित पूर्णांक *)(stats->समय_in_state + count);

	stats->trans_table = stats->freq_table + count;

	stats->max_state = count;

	/* Find valid-unique entries */
	cpufreq_क्रम_each_valid_entry(pos, policy->freq_table)
		अगर (freq_table_get_index(stats, pos->frequency) == -1)
			stats->freq_table[i++] = pos->frequency;

	stats->state_num = i;
	stats->last_समय = local_घड़ी();
	stats->last_index = freq_table_get_index(stats, policy->cur);

	policy->stats = stats;
	ret = sysfs_create_group(&policy->kobj, &stats_attr_group);
	अगर (!ret)
		वापस;

	/* We failed, release resources */
	policy->stats = शून्य;
	kमुक्त(stats->समय_in_state);
मुक्त_stat:
	kमुक्त(stats);
पूर्ण

व्योम cpufreq_stats_record_transition(काष्ठा cpufreq_policy *policy,
				     अचिन्हित पूर्णांक new_freq)
अणु
	काष्ठा cpufreq_stats *stats = policy->stats;
	पूर्णांक old_index, new_index;

	अगर (unlikely(!stats))
		वापस;

	अगर (unlikely(READ_ONCE(stats->reset_pending)))
		cpufreq_stats_reset_table(stats);

	old_index = stats->last_index;
	new_index = freq_table_get_index(stats, new_freq);

	/* We can't करो stats->समय_in_state[-1]= .. */
	अगर (unlikely(old_index == -1 || new_index == -1 || old_index == new_index))
		वापस;

	cpufreq_stats_update(stats, stats->last_समय);

	stats->last_index = new_index;
	stats->trans_table[old_index * stats->max_state + new_index]++;
	stats->total_trans++;
पूर्ण

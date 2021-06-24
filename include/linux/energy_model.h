<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ENERGY_MODEL_H
#घोषणा _LINUX_ENERGY_MODEL_H
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kobject.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched/cpufreq.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/types.h>

/**
 * em_perf_state - Perक्रमmance state of a perक्रमmance करोमुख्य
 * @frequency:	The frequency in KHz, क्रम consistency with CPUFreq
 * @घातer:	The घातer consumed at this level (by 1 CPU or by a रेजिस्टरed
 *		device). It can be a total घातer: अटल and dynamic.
 * @cost:	The cost coefficient associated with this level, used during
 *		energy calculation. Equal to: घातer * max_frequency / frequency
 */
काष्ठा em_perf_state अणु
	अचिन्हित दीर्घ frequency;
	अचिन्हित दीर्घ घातer;
	अचिन्हित दीर्घ cost;
पूर्ण;

/**
 * em_perf_करोमुख्य - Perक्रमmance करोमुख्य
 * @table:		List of perक्रमmance states, in ascending order
 * @nr_perf_states:	Number of perक्रमmance states
 * @milliwatts:		Flag indicating the घातer values are in milli-Watts
 *			or some other scale.
 * @cpus:		Cpumask covering the CPUs of the करोमुख्य. It's here
 *			क्रम perक्रमmance reasons to aव्योम potential cache
 *			misses during energy calculations in the scheduler
 *			and simplअगरies allocating/मुक्तing that memory region.
 *
 * In हाल of CPU device, a "performance domain" represents a group of CPUs
 * whose perक्रमmance is scaled together. All CPUs of a perक्रमmance करोमुख्य
 * must have the same micro-architecture. Perक्रमmance करोमुख्यs often have
 * a 1-to-1 mapping with CPUFreq policies. In हाल of other devices the @cpus
 * field is unused.
 */
काष्ठा em_perf_करोमुख्य अणु
	काष्ठा em_perf_state *table;
	पूर्णांक nr_perf_states;
	पूर्णांक milliwatts;
	अचिन्हित दीर्घ cpus[];
पूर्ण;

#घोषणा em_span_cpus(em) (to_cpumask((em)->cpus))

#अगर_घोषित CONFIG_ENERGY_MODEL
#घोषणा EM_MAX_POWER 0xFFFF

काष्ठा em_data_callback अणु
	/**
	 * active_घातer() - Provide घातer at the next perक्रमmance state of
	 *		a device
	 * @घातer	: Active घातer at the perक्रमmance state
	 *		(modअगरied)
	 * @freq	: Frequency at the perक्रमmance state in kHz
	 *		(modअगरied)
	 * @dev		: Device क्रम which we करो this operation (can be a CPU)
	 *
	 * active_घातer() must find the lowest perक्रमmance state of 'dev' above
	 * 'freq' and update 'power' and 'freq' to the matching active घातer
	 * and frequency.
	 *
	 * In हाल of CPUs, the घातer is the one of a single CPU in the करोमुख्य,
	 * expressed in milli-Watts or an असलtract scale. It is expected to
	 * fit in the [0, EM_MAX_POWER] range.
	 *
	 * Return 0 on success.
	 */
	पूर्णांक (*active_घातer)(अचिन्हित दीर्घ *घातer, अचिन्हित दीर्घ *freq,
			    काष्ठा device *dev);
पूर्ण;
#घोषणा EM_DATA_CB(_active_घातer_cb) अणु .active_घातer = &_active_घातer_cb पूर्ण

काष्ठा em_perf_करोमुख्य *em_cpu_get(पूर्णांक cpu);
काष्ठा em_perf_करोमुख्य *em_pd_get(काष्ठा device *dev);
पूर्णांक em_dev_रेजिस्टर_perf_करोमुख्य(काष्ठा device *dev, अचिन्हित पूर्णांक nr_states,
				काष्ठा em_data_callback *cb, cpumask_t *span,
				bool milliwatts);
व्योम em_dev_unरेजिस्टर_perf_करोमुख्य(काष्ठा device *dev);

/**
 * em_cpu_energy() - Estimates the energy consumed by the CPUs of a
		perक्रमmance करोमुख्य
 * @pd		: perक्रमmance करोमुख्य क्रम which energy has to be estimated
 * @max_util	: highest utilization among CPUs of the करोमुख्य
 * @sum_util	: sum of the utilization of all CPUs in the करोमुख्य
 *
 * This function must be used only क्रम CPU devices. There is no validation,
 * i.e. अगर the EM is a CPU type and has cpumask allocated. It is called from
 * the scheduler code quite frequently and that is why there is not checks.
 *
 * Return: the sum of the energy consumed by the CPUs of the करोमुख्य assuming
 * a capacity state satisfying the max utilization of the करोमुख्य.
 */
अटल अंतरभूत अचिन्हित दीर्घ em_cpu_energy(काष्ठा em_perf_करोमुख्य *pd,
				अचिन्हित दीर्घ max_util, अचिन्हित दीर्घ sum_util)
अणु
	अचिन्हित दीर्घ freq, scale_cpu;
	काष्ठा em_perf_state *ps;
	पूर्णांक i, cpu;

	अगर (!sum_util)
		वापस 0;

	/*
	 * In order to predict the perक्रमmance state, map the utilization of
	 * the most utilized CPU of the perक्रमmance करोमुख्य to a requested
	 * frequency, like schedutil.
	 */
	cpu = cpumask_first(to_cpumask(pd->cpus));
	scale_cpu = arch_scale_cpu_capacity(cpu);
	ps = &pd->table[pd->nr_perf_states - 1];
	freq = map_util_freq(max_util, ps->frequency, scale_cpu);

	/*
	 * Find the lowest perक्रमmance state of the Energy Model above the
	 * requested frequency.
	 */
	क्रम (i = 0; i < pd->nr_perf_states; i++) अणु
		ps = &pd->table[i];
		अगर (ps->frequency >= freq)
			अवरोध;
	पूर्ण

	/*
	 * The capacity of a CPU in the करोमुख्य at the perक्रमmance state (ps)
	 * can be computed as:
	 *
	 *             ps->freq * scale_cpu
	 *   ps->cap = --------------------                          (1)
	 *                 cpu_max_freq
	 *
	 * So, ignoring the costs of idle states (which are not available in
	 * the EM), the energy consumed by this CPU at that perक्रमmance state
	 * is estimated as:
	 *
	 *             ps->घातer * cpu_util
	 *   cpu_nrg = --------------------                          (2)
	 *                   ps->cap
	 *
	 * since 'cpu_util / ps->cap' represents its percentage of busy समय.
	 *
	 *   NOTE: Although the result of this computation actually is in
	 *         units of घातer, it can be manipulated as an energy value
	 *         over a scheduling period, since it is assumed to be
	 *         स्थिरant during that पूर्णांकerval.
	 *
	 * By injecting (1) in (2), 'cpu_nrg' can be re-expressed as a product
	 * of two terms:
	 *
	 *             ps->घातer * cpu_max_freq   cpu_util
	 *   cpu_nrg = ------------------------ * ---------          (3)
	 *                    ps->freq            scale_cpu
	 *
	 * The first term is अटल, and is stored in the em_perf_state काष्ठा
	 * as 'ps->cost'.
	 *
	 * Since all CPUs of the करोमुख्य have the same micro-architecture, they
	 * share the same 'ps->cost', and the same CPU capacity. Hence, the
	 * total energy of the करोमुख्य (which is the simple sum of the energy of
	 * all of its CPUs) can be factorized as:
	 *
	 *            ps->cost * \Sum cpu_util
	 *   pd_nrg = ------------------------                       (4)
	 *                  scale_cpu
	 */
	वापस ps->cost * sum_util / scale_cpu;
पूर्ण

/**
 * em_pd_nr_perf_states() - Get the number of perक्रमmance states of a perf.
 *				करोमुख्य
 * @pd		: perक्रमmance करोमुख्य क्रम which this must be करोne
 *
 * Return: the number of perक्रमmance states in the perक्रमmance करोमुख्य table
 */
अटल अंतरभूत पूर्णांक em_pd_nr_perf_states(काष्ठा em_perf_करोमुख्य *pd)
अणु
	वापस pd->nr_perf_states;
पूर्ण

#अन्यथा
काष्ठा em_data_callback अणुपूर्ण;
#घोषणा EM_DATA_CB(_active_घातer_cb) अणु पूर्ण

अटल अंतरभूत
पूर्णांक em_dev_रेजिस्टर_perf_करोमुख्य(काष्ठा device *dev, अचिन्हित पूर्णांक nr_states,
				काष्ठा em_data_callback *cb, cpumask_t *span,
				bool milliwatts)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम em_dev_unरेजिस्टर_perf_करोमुख्य(काष्ठा device *dev)
अणु
पूर्ण
अटल अंतरभूत काष्ठा em_perf_करोमुख्य *em_cpu_get(पूर्णांक cpu)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा em_perf_करोमुख्य *em_pd_get(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ em_cpu_energy(काष्ठा em_perf_करोमुख्य *pd,
			अचिन्हित दीर्घ max_util, अचिन्हित दीर्घ sum_util)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक em_pd_nr_perf_states(काष्ठा em_perf_करोमुख्य *pd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

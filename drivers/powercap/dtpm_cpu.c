<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2020 Linaro Limited
 *
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 *
 * The DTPM CPU is based on the energy model. It hooks the CPU in the
 * DTPM tree which in turns update the घातer number by propagating the
 * घातer number from the CPU energy model inक्रमmation to the parents.
 *
 * The association between the घातer and the perक्रमmance state, allows
 * to set the घातer of the CPU at the OPP granularity.
 *
 * The CPU hotplug is supported and the घातer numbers will be updated
 * अगर a CPU is hot plugged / unplugged.
 */
#समावेश <linux/cpumask.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/dtpm.h>
#समावेश <linux/energy_model.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/slab.h>
#समावेश <linux/units.h>

अटल काष्ठा dtpm *__parent;

अटल DEFINE_PER_CPU(काष्ठा dtpm *, dtpm_per_cpu);

काष्ठा dtpm_cpu अणु
	काष्ठा freq_qos_request qos_req;
	पूर्णांक cpu;
पूर्ण;

/*
 * When a new CPU is inserted at hotplug or boot समय, add the घातer
 * contribution and update the dtpm tree.
 */
अटल पूर्णांक घातer_add(काष्ठा dtpm *dtpm, काष्ठा em_perf_करोमुख्य *em)
अणु
	u64 घातer_min, घातer_max;

	घातer_min = em->table[0].घातer;
	घातer_min *= MICROWATT_PER_MILLIWATT;
	घातer_min += dtpm->घातer_min;

	घातer_max = em->table[em->nr_perf_states - 1].घातer;
	घातer_max *= MICROWATT_PER_MILLIWATT;
	घातer_max += dtpm->घातer_max;

	वापस dtpm_update_घातer(dtpm, घातer_min, घातer_max);
पूर्ण

/*
 * When a CPU is unplugged, हटाओ its घातer contribution from the
 * dtpm tree.
 */
अटल पूर्णांक घातer_sub(काष्ठा dtpm *dtpm, काष्ठा em_perf_करोमुख्य *em)
अणु
	u64 घातer_min, घातer_max;

	घातer_min = em->table[0].घातer;
	घातer_min *= MICROWATT_PER_MILLIWATT;
	घातer_min = dtpm->घातer_min - घातer_min;

	घातer_max = em->table[em->nr_perf_states - 1].घातer;
	घातer_max *= MICROWATT_PER_MILLIWATT;
	घातer_max = dtpm->घातer_max - घातer_max;

	वापस dtpm_update_घातer(dtpm, घातer_min, घातer_max);
पूर्ण

अटल u64 set_pd_घातer_limit(काष्ठा dtpm *dtpm, u64 घातer_limit)
अणु
	काष्ठा dtpm_cpu *dtpm_cpu = dtpm->निजी;
	काष्ठा em_perf_करोमुख्य *pd;
	काष्ठा cpumask cpus;
	अचिन्हित दीर्घ freq;
	u64 घातer;
	पूर्णांक i, nr_cpus;

	pd = em_cpu_get(dtpm_cpu->cpu);

	cpumask_and(&cpus, cpu_online_mask, to_cpumask(pd->cpus));

	nr_cpus = cpumask_weight(&cpus);

	क्रम (i = 0; i < pd->nr_perf_states; i++) अणु

		घातer = pd->table[i].घातer * MICROWATT_PER_MILLIWATT * nr_cpus;

		अगर (घातer > घातer_limit)
			अवरोध;
	पूर्ण

	freq = pd->table[i - 1].frequency;

	freq_qos_update_request(&dtpm_cpu->qos_req, freq);

	घातer_limit = pd->table[i - 1].घातer *
		MICROWATT_PER_MILLIWATT * nr_cpus;

	वापस घातer_limit;
पूर्ण

अटल u64 get_pd_घातer_uw(काष्ठा dtpm *dtpm)
अणु
	काष्ठा dtpm_cpu *dtpm_cpu = dtpm->निजी;
	काष्ठा em_perf_करोमुख्य *pd;
	काष्ठा cpumask cpus;
	अचिन्हित दीर्घ freq;
	पूर्णांक i, nr_cpus;

	pd = em_cpu_get(dtpm_cpu->cpu);
	freq = cpufreq_quick_get(dtpm_cpu->cpu);
	cpumask_and(&cpus, cpu_online_mask, to_cpumask(pd->cpus));
	nr_cpus = cpumask_weight(&cpus);

	क्रम (i = 0; i < pd->nr_perf_states; i++) अणु

		अगर (pd->table[i].frequency < freq)
			जारी;

		वापस pd->table[i].घातer *
			MICROWATT_PER_MILLIWATT * nr_cpus;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pd_release(काष्ठा dtpm *dtpm)
अणु
	काष्ठा dtpm_cpu *dtpm_cpu = dtpm->निजी;

	अगर (freq_qos_request_active(&dtpm_cpu->qos_req))
		freq_qos_हटाओ_request(&dtpm_cpu->qos_req);

	kमुक्त(dtpm_cpu);
पूर्ण

अटल काष्ठा dtpm_ops dtpm_ops = अणु
	.set_घातer_uw = set_pd_घातer_limit,
	.get_घातer_uw = get_pd_घातer_uw,
	.release = pd_release,
पूर्ण;

अटल पूर्णांक cpuhp_dtpm_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy;
	काष्ठा em_perf_करोमुख्य *pd;
	काष्ठा dtpm *dtpm;

	policy = cpufreq_cpu_get(cpu);

	अगर (!policy)
		वापस 0;

	pd = em_cpu_get(cpu);
	अगर (!pd)
		वापस -EINVAL;

	dtpm = per_cpu(dtpm_per_cpu, cpu);

	घातer_sub(dtpm, pd);

	अगर (cpumask_weight(policy->cpus) != 1)
		वापस 0;

	क्रम_each_cpu(cpu, policy->related_cpus)
		per_cpu(dtpm_per_cpu, cpu) = शून्य;

	dtpm_unरेजिस्टर(dtpm);

	वापस 0;
पूर्ण

अटल पूर्णांक cpuhp_dtpm_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा dtpm *dtpm;
	काष्ठा dtpm_cpu *dtpm_cpu;
	काष्ठा cpufreq_policy *policy;
	काष्ठा em_perf_करोमुख्य *pd;
	अक्षर name[CPUFREQ_NAME_LEN];
	पूर्णांक ret = -ENOMEM;

	policy = cpufreq_cpu_get(cpu);

	अगर (!policy)
		वापस 0;

	pd = em_cpu_get(cpu);
	अगर (!pd)
		वापस -EINVAL;

	dtpm = per_cpu(dtpm_per_cpu, cpu);
	अगर (dtpm)
		वापस घातer_add(dtpm, pd);

	dtpm = dtpm_alloc(&dtpm_ops);
	अगर (!dtpm)
		वापस -EINVAL;

	dtpm_cpu = kzalloc(माप(*dtpm_cpu), GFP_KERNEL);
	अगर (!dtpm_cpu)
		जाओ out_kमुक्त_dtpm;

	dtpm->निजी = dtpm_cpu;
	dtpm_cpu->cpu = cpu;

	क्रम_each_cpu(cpu, policy->related_cpus)
		per_cpu(dtpm_per_cpu, cpu) = dtpm;

	प्र_लिखो(name, "cpu%d", dtpm_cpu->cpu);

	ret = dtpm_रेजिस्टर(name, dtpm, __parent);
	अगर (ret)
		जाओ out_kमुक्त_dtpm_cpu;

	ret = घातer_add(dtpm, pd);
	अगर (ret)
		जाओ out_dtpm_unरेजिस्टर;

	ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs,
				   &dtpm_cpu->qos_req, FREQ_QOS_MAX,
				   pd->table[pd->nr_perf_states - 1].frequency);
	अगर (ret)
		जाओ out_घातer_sub;

	वापस 0;

out_घातer_sub:
	घातer_sub(dtpm, pd);

out_dtpm_unरेजिस्टर:
	dtpm_unरेजिस्टर(dtpm);
	dtpm_cpu = शून्य;
	dtpm = शून्य;

out_kमुक्त_dtpm_cpu:
	क्रम_each_cpu(cpu, policy->related_cpus)
		per_cpu(dtpm_per_cpu, cpu) = शून्य;
	kमुक्त(dtpm_cpu);

out_kमुक्त_dtpm:
	kमुक्त(dtpm);
	वापस ret;
पूर्ण

पूर्णांक dtpm_रेजिस्टर_cpu(काष्ठा dtpm *parent)
अणु
	__parent = parent;

	वापस cpuhp_setup_state(CPUHP_AP_DTPM_CPU_ONLINE,
				 "dtpm_cpu:online",
				 cpuhp_dtpm_cpu_online,
				 cpuhp_dtpm_cpu_offline);
पूर्ण

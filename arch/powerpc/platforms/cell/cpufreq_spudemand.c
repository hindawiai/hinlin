<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * spu aware cpufreq governor क्रम the cell processor
 *
 * तऊ Copyright IBM Corporation 2006-2008
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/spu.h>

#घोषणा POLL_TIME	100000		/* in तगs */
#घोषणा EXP		753		/* exp(-1) in fixed-poपूर्णांक */

काष्ठा spu_gov_info_काष्ठा अणु
	अचिन्हित दीर्घ busy_spus;	/* fixed-poपूर्णांक */
	काष्ठा cpufreq_policy *policy;
	काष्ठा delayed_work work;
	अचिन्हित पूर्णांक poll_पूर्णांक;		/* तगs */
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा spu_gov_info_काष्ठा, spu_gov_info);

अटल पूर्णांक calc_freq(काष्ठा spu_gov_info_काष्ठा *info)
अणु
	पूर्णांक cpu;
	पूर्णांक busy_spus;

	cpu = info->policy->cpu;
	busy_spus = atomic_पढ़ो(&cbe_spu_info[cpu_to_node(cpu)].busy_spus);

	info->busy_spus = calc_load(info->busy_spus, EXP, busy_spus * FIXED_1);
	pr_debug("cpu %d: busy_spus=%d, info->busy_spus=%ld\n",
			cpu, busy_spus, info->busy_spus);

	वापस info->policy->max * info->busy_spus / FIXED_1;
पूर्ण

अटल व्योम spu_gov_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा spu_gov_info_काष्ठा *info;
	पूर्णांक delay;
	अचिन्हित दीर्घ target_freq;

	info = container_of(work, काष्ठा spu_gov_info_काष्ठा, work.work);

	/* after cancel_delayed_work_sync we unset info->policy */
	BUG_ON(info->policy == शून्य);

	target_freq = calc_freq(info);
	__cpufreq_driver_target(info->policy, target_freq, CPUFREQ_RELATION_H);

	delay = usecs_to_jअगरfies(info->poll_पूर्णांक);
	schedule_delayed_work_on(info->policy->cpu, &info->work, delay);
पूर्ण

अटल व्योम spu_gov_init_work(काष्ठा spu_gov_info_काष्ठा *info)
अणु
	पूर्णांक delay = usecs_to_jअगरfies(info->poll_पूर्णांक);
	INIT_DEFERRABLE_WORK(&info->work, spu_gov_work);
	schedule_delayed_work_on(info->policy->cpu, &info->work, delay);
पूर्ण

अटल व्योम spu_gov_cancel_work(काष्ठा spu_gov_info_काष्ठा *info)
अणु
	cancel_delayed_work_sync(&info->work);
पूर्ण

अटल पूर्णांक spu_gov_start(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	काष्ठा spu_gov_info_काष्ठा *info = &per_cpu(spu_gov_info, cpu);
	काष्ठा spu_gov_info_काष्ठा *affected_info;
	पूर्णांक i;

	अगर (!cpu_online(cpu)) अणु
		prपूर्णांकk(KERN_ERR "cpu %d is not online\n", cpu);
		वापस -EINVAL;
	पूर्ण

	अगर (!policy->cur) अणु
		prपूर्णांकk(KERN_ERR "no cpu specified in policy\n");
		वापस -EINVAL;
	पूर्ण

	/* initialize spu_gov_info क्रम all affected cpus */
	क्रम_each_cpu(i, policy->cpus) अणु
		affected_info = &per_cpu(spu_gov_info, i);
		affected_info->policy = policy;
	पूर्ण

	info->poll_पूर्णांक = POLL_TIME;

	/* setup समयr */
	spu_gov_init_work(info);

	वापस 0;
पूर्ण

अटल व्योम spu_gov_stop(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	काष्ठा spu_gov_info_काष्ठा *info = &per_cpu(spu_gov_info, cpu);
	पूर्णांक i;

	/* cancel समयr */
	spu_gov_cancel_work(info);

	/* clean spu_gov_info क्रम all affected cpus */
	क्रम_each_cpu (i, policy->cpus) अणु
		info = &per_cpu(spu_gov_info, i);
		info->policy = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा cpufreq_governor spu_governor = अणु
	.name = "spudemand",
	.start = spu_gov_start,
	.stop = spu_gov_stop,
	.owner = THIS_MODULE,
पूर्ण;
cpufreq_governor_init(spu_governor);
cpufreq_governor_निकास(spu_governor);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Krafft <krafft@de.ibm.com>");

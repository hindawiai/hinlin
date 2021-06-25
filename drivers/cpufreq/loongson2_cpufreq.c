<शैली गुरु>
/*
 * Cpufreq driver क्रम the loongson-2 processors
 *
 * The 2E revision of loongson processor not support this feature.
 *
 * Copyright (C) 2006 - 2008 Lemote Inc. & Institute of Computing Technology
 * Author: Yanhua, yanh@lemote.com
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpufreq.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>	/* set_cpus_allowed() */
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/idle.h>

#समावेश <यंत्र/mach-loongson2ef/loongson.h>

अटल uपूर्णांक noरुको;

अटल व्योम (*saved_cpu_रुको) (व्योम);

अटल पूर्णांक loongson2_cpu_freq_notअगरier(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ val, व्योम *data);

अटल काष्ठा notअगरier_block loongson2_cpufreq_notअगरier_block = अणु
	.notअगरier_call = loongson2_cpu_freq_notअगरier
पूर्ण;

अटल पूर्णांक loongson2_cpu_freq_notअगरier(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ val, व्योम *data)
अणु
	अगर (val == CPUFREQ_POSTCHANGE)
		current_cpu_data.udelay_val = loops_per_jअगरfy;

	वापस 0;
पूर्ण

/*
 * Here we notअगरy other drivers of the proposed change and the final change.
 */
अटल पूर्णांक loongson2_cpufreq_target(काष्ठा cpufreq_policy *policy,
				     अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक freq;

	freq =
	    ((cpu_घड़ी_freq / 1000) *
	     loongson2_घड़ीmod_table[index].driver_data) / 8;

	/* setting the cpu frequency */
	loongson2_cpu_set_rate(freq);

	वापस 0;
पूर्ण

अटल पूर्णांक loongson2_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	rate = cpu_घड़ी_freq / 1000;
	अगर (!rate)
		वापस -EINVAL;

	/* घड़ी table init */
	क्रम (i = 2;
	     (loongson2_घड़ीmod_table[i].frequency != CPUFREQ_TABLE_END);
	     i++)
		loongson2_घड़ीmod_table[i].frequency = (rate * i) / 8;

	ret = loongson2_cpu_set_rate(rate);
	अगर (ret)
		वापस ret;

	cpufreq_generic_init(policy, &loongson2_घड़ीmod_table[0], 0);
	वापस 0;
पूर्ण

अटल पूर्णांक loongson2_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver loongson2_cpufreq_driver = अणु
	.name = "loongson2",
	.init = loongson2_cpufreq_cpu_init,
	.verअगरy = cpufreq_generic_frequency_table_verअगरy,
	.target_index = loongson2_cpufreq_target,
	.get = cpufreq_generic_get,
	.निकास = loongson2_cpufreq_निकास,
	.attr = cpufreq_generic_attr,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id platक्रमm_device_ids[] = अणु
	अणु
		.name = "loongson2_cpufreq",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, platक्रमm_device_ids);

अटल काष्ठा platक्रमm_driver platक्रमm_driver = अणु
	.driver = अणु
		.name = "loongson2_cpufreq",
	पूर्ण,
	.id_table = platक्रमm_device_ids,
पूर्ण;

/*
 * This is the simple version of Loongson-2 रुको, Maybe we need करो this in
 * पूर्णांकerrupt disabled context.
 */

अटल DEFINE_SPINLOCK(loongson2_रुको_lock);

अटल व्योम loongson2_cpu_रुको(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	u32 cpu_freq;

	spin_lock_irqsave(&loongson2_रुको_lock, flags);
	cpu_freq = पढ़ोl(LOONGSON_CHIPCFG);
	/* Put CPU पूर्णांकo रुको mode */
	ग_लिखोl(पढ़ोl(LOONGSON_CHIPCFG) & ~0x7, LOONGSON_CHIPCFG);
	/* Restore CPU state */
	ग_लिखोl(cpu_freq, LOONGSON_CHIPCFG);
	spin_unlock_irqrestore(&loongson2_रुको_lock, flags);
	local_irq_enable();
पूर्ण

अटल पूर्णांक __init cpufreq_init(व्योम)
अणु
	पूर्णांक ret;

	/* Register platक्रमm stuff */
	ret = platक्रमm_driver_रेजिस्टर(&platक्रमm_driver);
	अगर (ret)
		वापस ret;

	pr_info("Loongson-2F CPU frequency driver\n");

	cpufreq_रेजिस्टर_notअगरier(&loongson2_cpufreq_notअगरier_block,
				  CPUFREQ_TRANSITION_NOTIFIER);

	ret = cpufreq_रेजिस्टर_driver(&loongson2_cpufreq_driver);

	अगर (!ret && !noरुको) अणु
		saved_cpu_रुको = cpu_रुको;
		cpu_रुको = loongson2_cpu_रुको;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास cpufreq_निकास(व्योम)
अणु
	अगर (!noरुको && saved_cpu_रुको)
		cpu_रुको = saved_cpu_रुको;
	cpufreq_unरेजिस्टर_driver(&loongson2_cpufreq_driver);
	cpufreq_unरेजिस्टर_notअगरier(&loongson2_cpufreq_notअगरier_block,
				    CPUFREQ_TRANSITION_NOTIFIER);

	platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
पूर्ण

module_init(cpufreq_init);
module_निकास(cpufreq_निकास);

module_param(noरुको, uपूर्णांक, 0644);
MODULE_PARM_DESC(noरुको, "Disable Loongson-2F specific wait");

MODULE_AUTHOR("Yanhua <yanh@lemote.com>");
MODULE_DESCRIPTION("cpufreq driver for Loongson2F");
MODULE_LICENSE("GPL");

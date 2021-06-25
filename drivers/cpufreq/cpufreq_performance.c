<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/cpufreq/cpufreq_perक्रमmance.c
 *
 *  Copyright (C) 2002 - 2003 Dominik Broकरोwski <linux@broकरो.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

अटल व्योम cpufreq_gov_perक्रमmance_limits(काष्ठा cpufreq_policy *policy)
अणु
	pr_debug("setting to %u kHz\n", policy->max);
	__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);
पूर्ण

अटल काष्ठा cpufreq_governor cpufreq_gov_perक्रमmance = अणु
	.name		= "performance",
	.owner		= THIS_MODULE,
	.flags		= CPUFREQ_GOV_STRICT_TARGET,
	.limits		= cpufreq_gov_perक्रमmance_limits,
पूर्ण;

#अगर_घोषित CONFIG_CPU_FREQ_DEFAULT_GOV_PERFORMANCE
काष्ठा cpufreq_governor *cpufreq_शेष_governor(व्योम)
अणु
	वापस &cpufreq_gov_perक्रमmance;
पूर्ण
#पूर्ण_अगर
#अगर_अघोषित CONFIG_CPU_FREQ_GOV_PERFORMANCE_MODULE
काष्ठा cpufreq_governor *cpufreq_fallback_governor(व्योम)
अणु
	वापस &cpufreq_gov_perक्रमmance;
पूर्ण
#पूर्ण_अगर

MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("CPUfreq policy governor 'performance'");
MODULE_LICENSE("GPL");

cpufreq_governor_init(cpufreq_gov_perक्रमmance);
cpufreq_governor_निकास(cpufreq_gov_perक्रमmance);

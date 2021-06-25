<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/cpufreq/cpufreq_घातersave.c
 *
 * Copyright (C) 2002 - 2003 Dominik Broकरोwski <linux@broकरो.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

अटल व्योम cpufreq_gov_घातersave_limits(काष्ठा cpufreq_policy *policy)
अणु
	pr_debug("setting to %u kHz\n", policy->min);
	__cpufreq_driver_target(policy, policy->min, CPUFREQ_RELATION_L);
पूर्ण

अटल काष्ठा cpufreq_governor cpufreq_gov_घातersave = अणु
	.name		= "powersave",
	.limits		= cpufreq_gov_घातersave_limits,
	.owner		= THIS_MODULE,
	.flags		= CPUFREQ_GOV_STRICT_TARGET,
पूर्ण;

MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("CPUfreq policy governor 'powersave'");
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_CPU_FREQ_DEFAULT_GOV_POWERSAVE
काष्ठा cpufreq_governor *cpufreq_शेष_governor(व्योम)
अणु
	वापस &cpufreq_gov_घातersave;
पूर्ण
#पूर्ण_अगर

cpufreq_governor_init(cpufreq_gov_घातersave);
cpufreq_governor_निकास(cpufreq_gov_घातersave);

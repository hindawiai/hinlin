<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	sc520_freq.c: cpufreq driver क्रम the AMD Elan sc520
 *
 *	Copyright (C) 2005 Sean Young <sean@mess.org>
 *
 *	Based on elanfreq.c
 *
 *	2005-03-30: - initial revision
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <linux/delay.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/msr.h>

#घोषणा MMCR_BASE	0xfffef000	/* The शेष base address */
#घोषणा OFFS_CPUCTL	0x2   /* CPU Control Register */

अटल __u8 __iomem *cpuctl;

अटल काष्ठा cpufreq_frequency_table sc520_freq_table[] = अणु
	अणु0, 0x01,	100000पूर्ण,
	अणु0, 0x02,	133000पूर्ण,
	अणु0, 0,	CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक sc520_freq_get_cpu_frequency(अचिन्हित पूर्णांक cpu)
अणु
	u8 घड़ीspeed_reg = *cpuctl;

	चयन (घड़ीspeed_reg & 0x03) अणु
	शेष:
		pr_err("error: cpuctl register has unexpected value %02x\n",
		       घड़ीspeed_reg);
	हाल 0x01:
		वापस 100000;
	हाल 0x02:
		वापस 133000;
	पूर्ण
पूर्ण

अटल पूर्णांक sc520_freq_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक state)
अणु

	u8 घड़ीspeed_reg;

	local_irq_disable();

	घड़ीspeed_reg = *cpuctl & ~0x03;
	*cpuctl = घड़ीspeed_reg | sc520_freq_table[state].driver_data;

	local_irq_enable();

	वापस 0;
पूर्ण

/*
 *	Module init and निकास code
 */

अटल पूर्णांक sc520_freq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);

	/* capability check */
	अगर (c->x86_venकरोr != X86_VENDOR_AMD ||
	    c->x86 != 4 || c->x86_model != 9)
		वापस -ENODEV;

	/* cpuinfo and शेष policy values */
	policy->cpuinfo.transition_latency = 1000000; /* 1ms */
	policy->freq_table = sc520_freq_table;

	वापस 0;
पूर्ण


अटल काष्ठा cpufreq_driver sc520_freq_driver = अणु
	.get	= sc520_freq_get_cpu_frequency,
	.verअगरy	= cpufreq_generic_frequency_table_verअगरy,
	.target_index = sc520_freq_target,
	.init	= sc520_freq_cpu_init,
	.name	= "sc520_freq",
	.attr	= cpufreq_generic_attr,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id sc520_ids[] = अणु
	X86_MATCH_VENDOR_FAM_MODEL(AMD, 4, 9, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, sc520_ids);

अटल पूर्णांक __init sc520_freq_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!x86_match_cpu(sc520_ids))
		वापस -ENODEV;

	cpuctl = ioremap((अचिन्हित दीर्घ)(MMCR_BASE + OFFS_CPUCTL), 1);
	अगर (!cpuctl) अणु
		pr_err("sc520_freq: error: failed to remap memory\n");
		वापस -ENOMEM;
	पूर्ण

	err = cpufreq_रेजिस्टर_driver(&sc520_freq_driver);
	अगर (err)
		iounmap(cpuctl);

	वापस err;
पूर्ण


अटल व्योम __निकास sc520_freq_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&sc520_freq_driver);
	iounmap(cpuctl);
पूर्ण


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_DESCRIPTION("cpufreq driver for AMD's Elan sc520 CPU");

module_init(sc520_freq_init);
module_निकास(sc520_freq_निकास);


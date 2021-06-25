<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2011 Dmitry Eremin-Solenikov
 *  Copyright (C) 2002 - 2005 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 *  and                       Markus Demleitner <msdemlei@cl.uni-heidelberg.de>
 *
 * This driver adds basic cpufreq support क्रम SMU & 970FX based G5 Macs,
 * that is iMac G5 and latest single CPU desktop.
 */

#अघोषित DEBUG

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समय.स>
#समावेश <linux/of_device.h>

#घोषणा DBG(fmt...) pr_debug(fmt)

/* see 970FX user manual */

#घोषणा SCOM_PCR 0x0aa001			/* PCR scom addr */

#घोषणा PCR_HILO_SELECT		0x80000000U	/* 1 = PCR, 0 = PCRH */
#घोषणा PCR_SPEED_FULL		0x00000000U	/* 1:1 speed value */
#घोषणा PCR_SPEED_HALF		0x00020000U	/* 1:2 speed value */
#घोषणा PCR_SPEED_QUARTER	0x00040000U	/* 1:4 speed value */
#घोषणा PCR_SPEED_MASK		0x000e0000U	/* speed mask */
#घोषणा PCR_SPEED_SHIFT		17
#घोषणा PCR_FREQ_REQ_VALID	0x00010000U	/* freq request valid */
#घोषणा PCR_VOLT_REQ_VALID	0x00008000U	/* volt request valid */
#घोषणा PCR_TARGET_TIME_MASK	0x00006000U	/* target समय */
#घोषणा PCR_STATLAT_MASK	0x00001f00U	/* STATLAT value */
#घोषणा PCR_SNOOPLAT_MASK	0x000000f0U	/* SNOOPLAT value */
#घोषणा PCR_SNOOPACC_MASK	0x0000000fU	/* SNOOPACC value */

#घोषणा SCOM_PSR 0x408001			/* PSR scom addr */
/* warning: PSR is a 64 bits रेजिस्टर */
#घोषणा PSR_CMD_RECEIVED	0x2000000000000000U   /* command received */
#घोषणा PSR_CMD_COMPLETED	0x1000000000000000U   /* command completed */
#घोषणा PSR_CUR_SPEED_MASK	0x0300000000000000U   /* current speed */
#घोषणा PSR_CUR_SPEED_SHIFT	(56)

/*
 * The G5 only supports two frequencies (Quarter speed is not supported)
 */
#घोषणा CPUFREQ_HIGH                  0
#घोषणा CPUFREQ_LOW                   1

अटल काष्ठा cpufreq_frequency_table maple_cpu_freqs[] = अणु
	अणु0, CPUFREQ_HIGH,		0पूर्ण,
	अणु0, CPUFREQ_LOW,		0पूर्ण,
	अणु0, 0,				CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

/* Power mode data is an array of the 32 bits PCR values to use क्रम
 * the various frequencies, retrieved from the device-tree
 */
अटल पूर्णांक maple_pmode_cur;

अटल स्थिर u32 *maple_pmode_data;
अटल पूर्णांक maple_pmode_max;

/*
 * SCOM based frequency चयनing क्रम 970FX rev3
 */
अटल पूर्णांक maple_scom_चयन_freq(पूर्णांक speed_mode)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक to;

	local_irq_save(flags);

	/* Clear PCR high */
	scom970_ग_लिखो(SCOM_PCR, 0);
	/* Clear PCR low */
	scom970_ग_लिखो(SCOM_PCR, PCR_HILO_SELECT | 0);
	/* Set PCR low */
	scom970_ग_लिखो(SCOM_PCR, PCR_HILO_SELECT |
		      maple_pmode_data[speed_mode]);

	/* Wait क्रम completion */
	क्रम (to = 0; to < 10; to++) अणु
		अचिन्हित दीर्घ psr = scom970_पढ़ो(SCOM_PSR);

		अगर ((psr & PSR_CMD_RECEIVED) == 0 &&
		    (((psr >> PSR_CUR_SPEED_SHIFT) ^
		      (maple_pmode_data[speed_mode] >> PCR_SPEED_SHIFT)) & 0x3)
		    == 0)
			अवरोध;
		अगर (psr & PSR_CMD_COMPLETED)
			अवरोध;
		udelay(100);
	पूर्ण

	local_irq_restore(flags);

	maple_pmode_cur = speed_mode;
	ppc_proc_freq = maple_cpu_freqs[speed_mode].frequency * 1000ul;

	वापस 0;
पूर्ण

अटल पूर्णांक maple_scom_query_freq(व्योम)
अणु
	अचिन्हित दीर्घ psr = scom970_पढ़ो(SCOM_PSR);
	पूर्णांक i;

	क्रम (i = 0; i <= maple_pmode_max; i++)
		अगर ((((psr >> PSR_CUR_SPEED_SHIFT) ^
		      (maple_pmode_data[i] >> PCR_SPEED_SHIFT)) & 0x3) == 0)
			अवरोध;
	वापस i;
पूर्ण

/*
 * Common पूर्णांकerface to the cpufreq core
 */

अटल पूर्णांक maple_cpufreq_target(काष्ठा cpufreq_policy *policy,
	अचिन्हित पूर्णांक index)
अणु
	वापस maple_scom_चयन_freq(index);
पूर्ण

अटल अचिन्हित पूर्णांक maple_cpufreq_get_speed(अचिन्हित पूर्णांक cpu)
अणु
	वापस maple_cpu_freqs[maple_pmode_cur].frequency;
पूर्ण

अटल पूर्णांक maple_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	cpufreq_generic_init(policy, maple_cpu_freqs, 12000);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver maple_cpufreq_driver = अणु
	.name		= "maple",
	.flags		= CPUFREQ_CONST_LOOPS,
	.init		= maple_cpufreq_cpu_init,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= maple_cpufreq_target,
	.get		= maple_cpufreq_get_speed,
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक __init maple_cpufreq_init(व्योम)
अणु
	काष्ठा device_node *cpunode;
	अचिन्हित पूर्णांक psize;
	अचिन्हित दीर्घ max_freq;
	स्थिर u32 *valp;
	u32 pvr_hi;
	पूर्णांक rc = -ENODEV;

	/*
	 * Behave here like घातermac driver which checks machine compatibility
	 * to ease merging of two drivers in future.
	 */
	अगर (!of_machine_is_compatible("Momentum,Maple") &&
	    !of_machine_is_compatible("Momentum,Apache"))
		वापस 0;

	/* Get first CPU node */
	cpunode = of_cpu_device_node_get(0);
	अगर (cpunode == शून्य) अणु
		pr_err("Can't find any CPU 0 node\n");
		जाओ bail_noprops;
	पूर्ण

	/* Check 970FX क्रम now */
	/* we actually करोn't care on which CPU to access PVR */
	pvr_hi = PVR_VER(mfspr(SPRN_PVR));
	अगर (pvr_hi != 0x3c && pvr_hi != 0x44) अणु
		pr_err("Unsupported CPU version (%x)\n", pvr_hi);
		जाओ bail_noprops;
	पूर्ण

	/* Look क्रम the घातertune data in the device-tree */
	/*
	 * On Maple this property is provided by PIBS in dual-processor config,
	 * not provided by PIBS in CPU0 config and also not provided by SLOF,
	 * so YMMV
	 */
	maple_pmode_data = of_get_property(cpunode, "power-mode-data", &psize);
	अगर (!maple_pmode_data) अणु
		DBG("No power-mode-data !\n");
		जाओ bail_noprops;
	पूर्ण
	maple_pmode_max = psize / माप(u32) - 1;

	/*
	 * From what I see, घड़ी-frequency is always the maximal frequency.
	 * The current driver can not slew sysclk yet, so we really only deal
	 * with घातertune steps क्रम now. We also only implement full freq and
	 * half freq in this version. So far, I haven't yet seen a machine
	 * supporting anything अन्यथा.
	 */
	valp = of_get_property(cpunode, "clock-frequency", शून्य);
	अगर (!valp)
		जाओ bail_noprops;
	max_freq = (*valp)/1000;
	maple_cpu_freqs[0].frequency = max_freq;
	maple_cpu_freqs[1].frequency = max_freq/2;

	/* Force apply current frequency to make sure everything is in
	 * sync (voltage is right क्रम example). Firmware may leave us with
	 * a strange setting ...
	 */
	msleep(10);
	maple_pmode_cur = -1;
	maple_scom_चयन_freq(maple_scom_query_freq());

	pr_info("Registering Maple CPU frequency driver\n");
	pr_info("Low: %d Mhz, High: %d Mhz, Cur: %d MHz\n",
		maple_cpu_freqs[1].frequency/1000,
		maple_cpu_freqs[0].frequency/1000,
		maple_cpu_freqs[maple_pmode_cur].frequency/1000);

	rc = cpufreq_रेजिस्टर_driver(&maple_cpufreq_driver);

bail_noprops:
	of_node_put(cpunode);

	वापस rc;
पूर्ण

module_init(maple_cpufreq_init);


MODULE_LICENSE("GPL");

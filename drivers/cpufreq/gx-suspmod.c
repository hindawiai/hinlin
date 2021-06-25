<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	Cyrix MediaGX and NatSemi Geode Suspend Modulation
 *	(C) 2002 Zwane Mwaikambo <zwane@commfireservices.com>
 *	(C) 2002 Hiroshi Miura   <miura@da-cha.org>
 *	All Rights Reserved
 *
 *      The author(s) of this software shall not be held liable क्रम damages
 *      of any nature resulting due to the use of this software. This
 *      software is provided AS-IS with no warranties.
 *
 * Theoretical note:
 *
 *	(see Geode(पंचांग) CS5530 manual (rev.4.1) page.56)
 *
 *	CPU frequency control on NatSemi Geode GX1/GXLV processor and CS55x0
 *	are based on Suspend Modulation.
 *
 *	Suspend Modulation works by निश्चितing and de-निश्चितing the SUSP# pin
 *	to CPU(GX1/GXLV) क्रम configurable durations. When निश्चितing SUSP#
 *	the CPU enters an idle state. GX1 stops its core घड़ी when SUSP# is
 *	निश्चितed then घातer consumption is reduced.
 *
 *	Suspend Modulation's OFF/ON duration are configurable
 *	with 'Suspend Modulation OFF Count Register'
 *	and 'Suspend Modulation ON Count Register'.
 *	These रेजिस्टरs are 8bit counters that represent the number of
 *	32us पूर्णांकervals which the SUSP# pin is निश्चितed(ON)/de-निश्चितed(OFF)
 *	to the processor.
 *
 *	These counters define a ratio which is the effective frequency
 *	of operation of the प्रणाली.
 *
 *			       OFF Count
 *	F_eff = Fgx * ----------------------
 *	                OFF Count + ON Count
 *
 *	0 <= On Count, Off Count <= 255
 *
 *	From these limits, we can get रेजिस्टर values
 *
 *	off_duration + on_duration <= MAX_DURATION
 *	on_duration = off_duration * (stock_freq - freq) / freq
 *
 *      off_duration  =  (freq * DURATION) / stock_freq
 *      on_duration = DURATION - off_duration
 *
 *---------------------------------------------------------------------------
 *
 * ChangeLog:
 *	Dec. 12, 2003	Hiroshi Miura <miura@da-cha.org>
 *		- fix on/off रेजिस्टर mistake
 *		- fix cpu_khz calc when it stops cpu modulation.
 *
 *	Dec. 11, 2002	Hiroshi Miura <miura@da-cha.org>
 *		- reग_लिखो क्रम Cyrix MediaGX Cx5510/5520 and
 *		  NatSemi Geode Cs5530(A).
 *
 *	Jul. ??, 2002  Zwane Mwaikambo <zwane@commfireservices.com>
 *		- cs5530_mod patch क्रम 2.4.19-rc1.
 *
 *---------------------------------------------------------------------------
 *
 * Toकरो
 *	Test on machines with 5510, 5530, 5530A
 */

/************************************************************************
 *			Suspend Modulation - Definitions		*
 ************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/processor-cyrix.h>

/* PCI config रेजिस्टरs, all at F0 */
#घोषणा PCI_PMER1	0x80	/* घातer management enable रेजिस्टर 1 */
#घोषणा PCI_PMER2	0x81	/* घातer management enable रेजिस्टर 2 */
#घोषणा PCI_PMER3	0x82	/* घातer management enable रेजिस्टर 3 */
#घोषणा PCI_IRQTC	0x8c	/* irq speedup समयr counter रेजिस्टर:typical 2 to 4ms */
#घोषणा PCI_VIDTC	0x8d	/* video speedup समयr counter रेजिस्टर: typical 50 to 100ms */
#घोषणा PCI_MODOFF	0x94	/* suspend modulation OFF counter रेजिस्टर, 1 = 32us */
#घोषणा PCI_MODON	0x95	/* suspend modulation ON counter रेजिस्टर */
#घोषणा PCI_SUSCFG	0x96	/* suspend configuration रेजिस्टर */

/* PMER1 bits */
#घोषणा GPM		(1<<0)	/* global घातer management */
#घोषणा GIT		(1<<1)	/* globally enable PM device idle समयrs */
#घोषणा GTR		(1<<2)	/* globally enable IO traps */
#घोषणा IRQ_SPDUP	(1<<3)	/* disable घड़ी throttle during पूर्णांकerrupt handling */
#घोषणा VID_SPDUP	(1<<4)	/* disable घड़ी throttle during vga video handling */

/* SUSCFG bits */
#घोषणा SUSMOD		(1<<0)	/* enable/disable suspend modulation */
/* the below is supported only with cs5530 (after rev.1.2)/cs5530A */
#घोषणा SMISPDUP	(1<<1)	/* select how SMI re-enable suspend modulation: */
				/* IRQTC समयr or पढ़ो SMI speedup disable reg.(F1BAR[08-09h]) */
#घोषणा SUSCFG		(1<<2)	/* enable घातering करोwn a GXLV processor. "Special 3Volt Suspend" mode */
/* the below is supported only with cs5530A */
#घोषणा PWRSVE_ISA	(1<<3)	/* stop ISA घड़ी  */
#घोषणा PWRSVE		(1<<4)	/* active idle */

काष्ठा gxfreq_params अणु
	u8 on_duration;
	u8 off_duration;
	u8 pci_suscfg;
	u8 pci_pmer1;
	u8 pci_pmer2;
	काष्ठा pci_dev *cs55x0;
पूर्ण;

अटल काष्ठा gxfreq_params *gx_params;
अटल पूर्णांक stock_freq;

/* PCI bus घड़ी - शेषs to 30.000 अगर cpu_khz is not available */
अटल पूर्णांक pci_busclk;
module_param(pci_busclk, पूर्णांक, 0444);

/* maximum duration क्रम which the cpu may be suspended
 * (32us * MAX_DURATION). If no parameter is given, this शेषs
 * to 255.
 * Note that this leads to a maximum of 8 ms(!) where the CPU घड़ी
 * is suspended -- processing घातer is just 0.39% of what it used to be,
 * though. 781.25 kHz(!) क्रम a 200 MHz processor -- wow. */
अटल पूर्णांक max_duration = 255;
module_param(max_duration, पूर्णांक, 0444);

/* For the शेष policy, we want at least some processing घातer
 * - let's say 5%. (min = maxfreq / POLICY_MIN_DIV)
 */
#घोषणा POLICY_MIN_DIV 20


/**
 * we can detect a core multiplier from dir0_lsb
 * from GX1 datasheet p.56,
 *	MULT[3:0]:
 *	0000 = SYSCLK multiplied by 4 (test only)
 *	0001 = SYSCLK multiplied by 10
 *	0010 = SYSCLK multiplied by 4
 *	0011 = SYSCLK multiplied by 6
 *	0100 = SYSCLK multiplied by 9
 *	0101 = SYSCLK multiplied by 5
 *	0110 = SYSCLK multiplied by 7
 *	0111 = SYSCLK multiplied by 8
 *              of 33.3MHz
 **/
अटल पूर्णांक gx_freq_mult[16] = अणु
		4, 10, 4, 6, 9, 5, 7, 8,
		0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;


/****************************************************************
 *	Low Level chipset पूर्णांकerface				*
 ****************************************************************/
अटल काष्ठा pci_device_id gx_chipset_tbl[] __initdata = अणु
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5530_LEGACY), पूर्ण,
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5520), पूर्ण,
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5510), पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, gx_chipset_tbl);

अटल व्योम gx_ग_लिखो_byte(पूर्णांक reg, पूर्णांक value)
अणु
	pci_ग_लिखो_config_byte(gx_params->cs55x0, reg, value);
पूर्ण

/**
 * gx_detect_chipset:
 *
 **/
अटल काष्ठा pci_dev * __init gx_detect_chipset(व्योम)
अणु
	काष्ठा pci_dev *gx_pci = शून्य;

	/* detect which companion chip is used */
	क्रम_each_pci_dev(gx_pci) अणु
		अगर ((pci_match_id(gx_chipset_tbl, gx_pci)) != शून्य)
			वापस gx_pci;
	पूर्ण

	pr_debug("error: no supported chipset found!\n");
	वापस शून्य;
पूर्ण

/**
 * gx_get_cpuspeed:
 *
 * Finds out at which efficient frequency the Cyrix MediaGX/NatSemi
 * Geode CPU runs.
 */
अटल अचिन्हित पूर्णांक gx_get_cpuspeed(अचिन्हित पूर्णांक cpu)
अणु
	अगर ((gx_params->pci_suscfg & SUSMOD) == 0)
		वापस stock_freq;

	वापस (stock_freq * gx_params->off_duration)
		/ (gx_params->on_duration + gx_params->off_duration);
पूर्ण

/**
 *      gx_validate_speed:
 *      determine current cpu speed
 *
 **/

अटल अचिन्हित पूर्णांक gx_validate_speed(अचिन्हित पूर्णांक khz, u8 *on_duration,
		u8 *off_duration)
अणु
	अचिन्हित पूर्णांक i;
	u8 पंचांगp_on, पंचांगp_off;
	पूर्णांक old_पंचांगp_freq = stock_freq;
	पूर्णांक पंचांगp_freq;

	*off_duration = 1;
	*on_duration = 0;

	क्रम (i = max_duration; i > 0; i--) अणु
		पंचांगp_off = ((khz * i) / stock_freq) & 0xff;
		पंचांगp_on = i - पंचांगp_off;
		पंचांगp_freq = (stock_freq * पंचांगp_off) / i;
		/* अगर this relation is बंदr to khz, use this. If it's equal,
		 * prefer it, too - lower latency */
		अगर (असल(पंचांगp_freq - khz) <= असल(old_पंचांगp_freq - khz)) अणु
			*on_duration = पंचांगp_on;
			*off_duration = पंचांगp_off;
			old_पंचांगp_freq = पंचांगp_freq;
		पूर्ण
	पूर्ण

	वापस old_पंचांगp_freq;
पूर्ण


/**
 * gx_set_cpuspeed:
 * set cpu speed in khz.
 **/

अटल व्योम gx_set_cpuspeed(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक khz)
अणु
	u8 suscfg, pmer1;
	अचिन्हित पूर्णांक new_khz;
	अचिन्हित दीर्घ flags;
	काष्ठा cpufreq_freqs freqs;

	freqs.old = gx_get_cpuspeed(0);

	new_khz = gx_validate_speed(khz, &gx_params->on_duration,
			&gx_params->off_duration);

	freqs.new = new_khz;

	cpufreq_freq_transition_begin(policy, &freqs);
	local_irq_save(flags);

	अगर (new_khz != stock_freq) अणु
		/* अगर new khz == 100% of CPU speed, it is special हाल */
		चयन (gx_params->cs55x0->device) अणु
		हाल PCI_DEVICE_ID_CYRIX_5530_LEGACY:
			pmer1 = gx_params->pci_pmer1 | IRQ_SPDUP | VID_SPDUP;
			/* FIXME: need to test other values -- Zwane,Miura */
			/* typical 2 to 4ms */
			gx_ग_लिखो_byte(PCI_IRQTC, 4);
			/* typical 50 to 100ms */
			gx_ग_लिखो_byte(PCI_VIDTC, 100);
			gx_ग_लिखो_byte(PCI_PMER1, pmer1);

			अगर (gx_params->cs55x0->revision < 0x10) अणु
				/* CS5530(rev 1.2, 1.3) */
				suscfg = gx_params->pci_suscfg|SUSMOD;
			पूर्ण अन्यथा अणु
				/* CS5530A,B.. */
				suscfg = gx_params->pci_suscfg|SUSMOD|PWRSVE;
			पूर्ण
			अवरोध;
		हाल PCI_DEVICE_ID_CYRIX_5520:
		हाल PCI_DEVICE_ID_CYRIX_5510:
			suscfg = gx_params->pci_suscfg | SUSMOD;
			अवरोध;
		शेष:
			local_irq_restore(flags);
			pr_debug("fatal: try to set unknown chipset.\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		suscfg = gx_params->pci_suscfg & ~(SUSMOD);
		gx_params->off_duration = 0;
		gx_params->on_duration = 0;
		pr_debug("suspend modulation disabled: cpu runs 100%% speed.\n");
	पूर्ण

	gx_ग_लिखो_byte(PCI_MODOFF, gx_params->off_duration);
	gx_ग_लिखो_byte(PCI_MODON, gx_params->on_duration);

	gx_ग_लिखो_byte(PCI_SUSCFG, suscfg);
	pci_पढ़ो_config_byte(gx_params->cs55x0, PCI_SUSCFG, &suscfg);

	local_irq_restore(flags);

	gx_params->pci_suscfg = suscfg;

	cpufreq_freq_transition_end(policy, &freqs, 0);

	pr_debug("suspend modulation w/ duration of ON:%d us, OFF:%d us\n",
		gx_params->on_duration * 32, gx_params->off_duration * 32);
	pr_debug("suspend modulation w/ clock speed: %d kHz.\n", freqs.new);
पूर्ण

/****************************************************************
 *             High level functions                             *
 ****************************************************************/

/*
 *	cpufreq_gx_verअगरy: test अगर frequency range is valid
 *
 *	This function checks अगर a given frequency range in kHz is valid
 *      क्रम the hardware supported by the driver.
 */

अटल पूर्णांक cpufreq_gx_verअगरy(काष्ठा cpufreq_policy_data *policy)
अणु
	अचिन्हित पूर्णांक पंचांगp_freq = 0;
	u8 पंचांगp1, पंचांगp2;

	अगर (!stock_freq || !policy)
		वापस -EINVAL;

	policy->cpu = 0;
	cpufreq_verअगरy_within_limits(policy, (stock_freq / max_duration),
			stock_freq);

	/* it needs to be assured that at least one supported frequency is
	 * within policy->min and policy->max. If it is not, policy->max
	 * needs to be increased until one frequency is supported.
	 * policy->min may not be decreased, though. This way we guarantee a
	 * specअगरic processing capacity.
	 */
	पंचांगp_freq = gx_validate_speed(policy->min, &पंचांगp1, &पंचांगp2);
	अगर (पंचांगp_freq < policy->min)
		पंचांगp_freq += stock_freq / max_duration;
	policy->min = पंचांगp_freq;
	अगर (policy->min > policy->max)
		policy->max = पंचांगp_freq;
	पंचांगp_freq = gx_validate_speed(policy->max, &पंचांगp1, &पंचांगp2);
	अगर (पंचांगp_freq > policy->max)
		पंचांगp_freq -= stock_freq / max_duration;
	policy->max = पंचांगp_freq;
	अगर (policy->max < policy->min)
		policy->max = policy->min;
	cpufreq_verअगरy_within_limits(policy, (stock_freq / max_duration),
			stock_freq);

	वापस 0;
पूर्ण

/*
 *      cpufreq_gx_target:
 *
 */
अटल पूर्णांक cpufreq_gx_target(काष्ठा cpufreq_policy *policy,
			     अचिन्हित पूर्णांक target_freq,
			     अचिन्हित पूर्णांक relation)
अणु
	u8 पंचांगp1, पंचांगp2;
	अचिन्हित पूर्णांक पंचांगp_freq;

	अगर (!stock_freq || !policy)
		वापस -EINVAL;

	policy->cpu = 0;

	पंचांगp_freq = gx_validate_speed(target_freq, &पंचांगp1, &पंचांगp2);
	जबतक (पंचांगp_freq < policy->min) अणु
		पंचांगp_freq += stock_freq / max_duration;
		पंचांगp_freq = gx_validate_speed(पंचांगp_freq, &पंचांगp1, &पंचांगp2);
	पूर्ण
	जबतक (पंचांगp_freq > policy->max) अणु
		पंचांगp_freq -= stock_freq / max_duration;
		पंचांगp_freq = gx_validate_speed(पंचांगp_freq, &पंचांगp1, &पंचांगp2);
	पूर्ण

	gx_set_cpuspeed(policy, पंचांगp_freq);

	वापस 0;
पूर्ण

अटल पूर्णांक cpufreq_gx_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक maxfreq;

	अगर (!policy || policy->cpu != 0)
		वापस -ENODEV;

	/* determine maximum frequency */
	अगर (pci_busclk)
		maxfreq = pci_busclk * gx_freq_mult[getCx86(CX86_सूची1) & 0x0f];
	अन्यथा अगर (cpu_khz)
		maxfreq = cpu_khz;
	अन्यथा
		maxfreq = 30000 * gx_freq_mult[getCx86(CX86_सूची1) & 0x0f];

	stock_freq = maxfreq;

	pr_debug("cpu max frequency is %d.\n", maxfreq);

	/* setup basic काष्ठा क्रम cpufreq API */
	policy->cpu = 0;

	अगर (max_duration < POLICY_MIN_DIV)
		policy->min = maxfreq / max_duration;
	अन्यथा
		policy->min = maxfreq / POLICY_MIN_DIV;
	policy->max = maxfreq;
	policy->cpuinfo.min_freq = maxfreq / max_duration;
	policy->cpuinfo.max_freq = maxfreq;

	वापस 0;
पूर्ण

/*
 * cpufreq_gx_init:
 *   MediaGX/Geode GX initialize cpufreq driver
 */
अटल काष्ठा cpufreq_driver gx_suspmod_driver = अणु
	.flags		= CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING,
	.get		= gx_get_cpuspeed,
	.verअगरy		= cpufreq_gx_verअगरy,
	.target		= cpufreq_gx_target,
	.init		= cpufreq_gx_cpu_init,
	.name		= "gx-suspmod",
पूर्ण;

अटल पूर्णांक __init cpufreq_gx_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा gxfreq_params *params;
	काष्ठा pci_dev *gx_pci;

	/* Test अगर we have the right hardware */
	gx_pci = gx_detect_chipset();
	अगर (gx_pci == शून्य)
		वापस -ENODEV;

	/* check whether module parameters are sane */
	अगर (max_duration > 0xff)
		max_duration = 0xff;

	pr_debug("geode suspend modulation available.\n");

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (params == शून्य)
		वापस -ENOMEM;

	params->cs55x0 = gx_pci;
	gx_params = params;

	/* keep cs55x0 configurations */
	pci_पढ़ो_config_byte(params->cs55x0, PCI_SUSCFG, &(params->pci_suscfg));
	pci_पढ़ो_config_byte(params->cs55x0, PCI_PMER1, &(params->pci_pmer1));
	pci_पढ़ो_config_byte(params->cs55x0, PCI_PMER2, &(params->pci_pmer2));
	pci_पढ़ो_config_byte(params->cs55x0, PCI_MODON, &(params->on_duration));
	pci_पढ़ो_config_byte(params->cs55x0, PCI_MODOFF,
			&(params->off_duration));

	ret = cpufreq_रेजिस्टर_driver(&gx_suspmod_driver);
	अगर (ret) अणु
		kमुक्त(params);
		वापस ret;                   /* रेजिस्टर error! */
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cpufreq_gx_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&gx_suspmod_driver);
	pci_dev_put(gx_params->cs55x0);
	kमुक्त(gx_params);
पूर्ण

MODULE_AUTHOR("Hiroshi Miura <miura@da-cha.org>");
MODULE_DESCRIPTION("Cpufreq driver for Cyrix MediaGX and NatSemi Geode");
MODULE_LICENSE("GPL");

module_init(cpufreq_gx_init);
module_निकास(cpufreq_gx_निकास);


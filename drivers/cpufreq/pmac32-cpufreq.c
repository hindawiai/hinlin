<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 - 2005 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 *  Copyright (C) 2004        John Steele Scott <toojays@toojays.net>
 *
 * TODO: Need a big cleanup here. Basically, we need to have dअगरferent
 * cpufreq_driver काष्ठाures क्रम the dअगरferent type of HW instead of the
 * current mess. We also need to better deal with the detection of the
 * type of machine.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/keylargo.h>
#समावेश <यंत्र/चयन_to.h>

/* WARNING !!! This will cause calibrate_delay() to be called,
 * but this is an __init function ! So you MUST go edit
 * init/मुख्य.c to make it non-init beक्रमe enabling DEBUG_FREQ
 */
#अघोषित DEBUG_FREQ

बाह्य व्योम low_choose_7447a_dfs(पूर्णांक dfs);
बाह्य व्योम low_choose_750fx_pll(पूर्णांक pll);
बाह्य व्योम low_sleep_handler(व्योम);

/*
 * Currently, PowerMac cpufreq supports only high & low frequencies
 * that are set by the firmware
 */
अटल अचिन्हित पूर्णांक low_freq;
अटल अचिन्हित पूर्णांक hi_freq;
अटल अचिन्हित पूर्णांक cur_freq;
अटल अचिन्हित पूर्णांक sleep_freq;
अटल अचिन्हित दीर्घ transition_latency;

/*
 * Dअगरferent models uses dअगरferent mechanisms to चयन the frequency
 */
अटल पूर्णांक (*set_speed_proc)(पूर्णांक low_speed);
अटल अचिन्हित पूर्णांक (*get_speed_proc)(व्योम);

/*
 * Some definitions used by the various speedprocs
 */
अटल u32 voltage_gpio;
अटल u32 frequency_gpio;
अटल u32 slew_करोne_gpio;
अटल पूर्णांक no_schedule;
अटल पूर्णांक has_cpu_l2lve;
अटल पूर्णांक is_pmu_based;

/* There are only two frequency states क्रम each processor. Values
 * are in kHz क्रम the समय being.
 */
#घोषणा CPUFREQ_HIGH                  0
#घोषणा CPUFREQ_LOW                   1

अटल काष्ठा cpufreq_frequency_table pmac_cpu_freqs[] = अणु
	अणु0, CPUFREQ_HIGH,	0पूर्ण,
	अणु0, CPUFREQ_LOW,	0पूर्ण,
	अणु0, 0,			CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

अटल अंतरभूत व्योम local_delay(अचिन्हित दीर्घ ms)
अणु
	अगर (no_schedule)
		mdelay(ms);
	अन्यथा
		msleep(ms);
पूर्ण

#अगर_घोषित DEBUG_FREQ
अटल अंतरभूत व्योम debug_calc_bogomips(व्योम)
अणु
	/* This will cause a recalc of bogomips and display the
	 * result. We backup/restore the value to aव्योम affecting the
	 * core cpufreq framework's own calculation.
	 */
	अचिन्हित दीर्घ save_lpj = loops_per_jअगरfy;
	calibrate_delay();
	loops_per_jअगरfy = save_lpj;
पूर्ण
#पूर्ण_अगर /* DEBUG_FREQ */

/* Switch CPU speed under 750FX CPU control
 */
अटल पूर्णांक cpu_750fx_cpu_speed(पूर्णांक low_speed)
अणु
	u32 hid2;

	अगर (low_speed == 0) अणु
		/* ramping up, set voltage first */
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, voltage_gpio, 0x05);
		/* Make sure we sleep क्रम at least 1ms */
		local_delay(10);

		/* tweak L2 क्रम high voltage */
		अगर (has_cpu_l2lve) अणु
			hid2 = mfspr(SPRN_HID2);
			hid2 &= ~0x2000;
			mtspr(SPRN_HID2, hid2);
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	low_choose_750fx_pll(low_speed);
#पूर्ण_अगर
	अगर (low_speed == 1) अणु
		/* tweak L2 क्रम low voltage */
		अगर (has_cpu_l2lve) अणु
			hid2 = mfspr(SPRN_HID2);
			hid2 |= 0x2000;
			mtspr(SPRN_HID2, hid2);
		पूर्ण

		/* ramping करोwn, set voltage last */
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, voltage_gpio, 0x04);
		local_delay(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक cpu_750fx_get_cpu_speed(व्योम)
अणु
	अगर (mfspr(SPRN_HID1) & HID1_PS)
		वापस low_freq;
	अन्यथा
		वापस hi_freq;
पूर्ण

/* Switch CPU speed using DFS */
अटल पूर्णांक dfs_set_cpu_speed(पूर्णांक low_speed)
अणु
	अगर (low_speed == 0) अणु
		/* ramping up, set voltage first */
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, voltage_gpio, 0x05);
		/* Make sure we sleep क्रम at least 1ms */
		local_delay(1);
	पूर्ण

	/* set frequency */
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	low_choose_7447a_dfs(low_speed);
#पूर्ण_अगर
	udelay(100);

	अगर (low_speed == 1) अणु
		/* ramping करोwn, set voltage last */
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, voltage_gpio, 0x04);
		local_delay(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक dfs_get_cpu_speed(व्योम)
अणु
	अगर (mfspr(SPRN_HID1) & HID1_DFS)
		वापस low_freq;
	अन्यथा
		वापस hi_freq;
पूर्ण


/* Switch CPU speed using slewing GPIOs
 */
अटल पूर्णांक gpios_set_cpu_speed(पूर्णांक low_speed)
अणु
	पूर्णांक gpio, समयout = 0;

	/* If ramping up, set voltage first */
	अगर (low_speed == 0) अणु
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, voltage_gpio, 0x05);
		/* Delay is way too big but it's ok, we schedule */
		local_delay(10);
	पूर्ण

	/* Set frequency */
	gpio = 	pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य, frequency_gpio, 0);
	अगर (low_speed == ((gpio & 0x01) == 0))
		जाओ skip;

	pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, frequency_gpio,
			  low_speed ? 0x04 : 0x05);
	udelay(200);
	करो अणु
		अगर (++समयout > 100)
			अवरोध;
		local_delay(1);
		gpio = pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य, slew_करोne_gpio, 0);
	पूर्ण जबतक((gpio & 0x02) == 0);
 skip:
	/* If ramping करोwn, set voltage last */
	अगर (low_speed == 1) अणु
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, voltage_gpio, 0x04);
		/* Delay is way too big but it's ok, we schedule */
		local_delay(10);
	पूर्ण

#अगर_घोषित DEBUG_FREQ
	debug_calc_bogomips();
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Switch CPU speed under PMU control
 */
अटल पूर्णांक pmu_set_cpu_speed(पूर्णांक low_speed)
अणु
	काष्ठा adb_request req;
	अचिन्हित दीर्घ save_l2cr;
	अचिन्हित दीर्घ save_l3cr;
	अचिन्हित पूर्णांक pic_prio;
	अचिन्हित दीर्घ flags;

	preempt_disable();

#अगर_घोषित DEBUG_FREQ
	prपूर्णांकk(KERN_DEBUG "HID1, before: %x\n", mfspr(SPRN_HID1));
#पूर्ण_अगर
	pmu_suspend();

	/* Disable all पूर्णांकerrupt sources on खोलोpic */
 	pic_prio = mpic_cpu_get_priority();
	mpic_cpu_set_priority(0xf);

	/* Make sure the decrementer won't पूर्णांकerrupt us */
	यंत्र अस्थिर("mtdec %0" : : "r" (0x7fffffff));
	/* Make sure any pending DEC पूर्णांकerrupt occurring जबतक we did
	 * the above didn't re-enable the DEC */
	mb();
	यंत्र अस्थिर("mtdec %0" : : "r" (0x7fffffff));

	/* We can now disable MSR_EE */
	local_irq_save(flags);

	/* Giveup the FPU & vec */
	enable_kernel_fp();

#अगर_घोषित CONFIG_ALTIVEC
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		enable_kernel_altivec();
#पूर्ण_अगर /* CONFIG_ALTIVEC */

	/* Save & disable L2 and L3 caches */
	save_l3cr = _get_L3CR();	/* (वापसs -1 अगर not available) */
	save_l2cr = _get_L2CR();	/* (वापसs -1 अगर not available) */

	/* Send the new speed command. My assumption is that this command
	 * will cause PLL_CFG[0..3] to be changed next समय CPU goes to sleep
	 */
	pmu_request(&req, शून्य, 6, PMU_CPU_SPEED, 'W', 'O', 'O', 'F', low_speed);
	जबतक (!req.complete)
		pmu_poll();

	/* Prepare the northbridge क्रम the speed transition */
	pmac_call_feature(PMAC_FTR_SLEEP_STATE,शून्य,1,1);

	/* Call low level code to backup CPU state and recover from
	 * hardware reset
	 */
	low_sleep_handler();

	/* Restore the northbridge */
	pmac_call_feature(PMAC_FTR_SLEEP_STATE,शून्य,1,0);

	/* Restore L2 cache */
	अगर (save_l2cr != 0xffffffff && (save_l2cr & L2CR_L2E) != 0)
 		_set_L2CR(save_l2cr);
	/* Restore L3 cache */
	अगर (save_l3cr != 0xffffffff && (save_l3cr & L3CR_L3E) != 0)
 		_set_L3CR(save_l3cr);

	/* Restore userland MMU context */
	चयन_mmu_context(शून्य, current->active_mm, शून्य);

#अगर_घोषित DEBUG_FREQ
	prपूर्णांकk(KERN_DEBUG "HID1, after: %x\n", mfspr(SPRN_HID1));
#पूर्ण_अगर

	/* Restore low level PMU operations */
	pmu_unlock();

	/*
	 * Restore decrementer; we'll take a decrementer पूर्णांकerrupt
	 * as soon as पूर्णांकerrupts are re-enabled and the generic
	 * घड़ीevents code will reprogram it with the right value.
	 */
	set_dec(1);

	/* Restore पूर्णांकerrupts */
 	mpic_cpu_set_priority(pic_prio);

	/* Let पूर्णांकerrupts flow again ... */
	local_irq_restore(flags);

#अगर_घोषित DEBUG_FREQ
	debug_calc_bogomips();
#पूर्ण_अगर

	pmu_resume();

	preempt_enable();

	वापस 0;
पूर्ण

अटल पूर्णांक करो_set_cpu_speed(काष्ठा cpufreq_policy *policy, पूर्णांक speed_mode)
अणु
	अचिन्हित दीर्घ l3cr;
	अटल अचिन्हित दीर्घ prev_l3cr;

	अगर (speed_mode == CPUFREQ_LOW &&
	    cpu_has_feature(CPU_FTR_L3CR)) अणु
		l3cr = _get_L3CR();
		अगर (l3cr & L3CR_L3E) अणु
			prev_l3cr = l3cr;
			_set_L3CR(0);
		पूर्ण
	पूर्ण
	set_speed_proc(speed_mode == CPUFREQ_LOW);
	अगर (speed_mode == CPUFREQ_HIGH &&
	    cpu_has_feature(CPU_FTR_L3CR)) अणु
		l3cr = _get_L3CR();
		अगर ((prev_l3cr & L3CR_L3E) && l3cr != prev_l3cr)
			_set_L3CR(prev_l3cr);
	पूर्ण
	cur_freq = (speed_mode == CPUFREQ_HIGH) ? hi_freq : low_freq;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pmac_cpufreq_get_speed(अचिन्हित पूर्णांक cpu)
अणु
	वापस cur_freq;
पूर्ण

अटल पूर्णांक pmac_cpufreq_target(	काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक index)
अणु
	पूर्णांक		rc;

	rc = करो_set_cpu_speed(policy, index);

	ppc_proc_freq = cur_freq * 1000ul;
	वापस rc;
पूर्ण

अटल पूर्णांक pmac_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	cpufreq_generic_init(policy, pmac_cpu_freqs, transition_latency);
	वापस 0;
पूर्ण

अटल u32 पढ़ो_gpio(काष्ठा device_node *np)
अणु
	स्थिर u32 *reg = of_get_property(np, "reg", शून्य);
	u32 offset;

	अगर (reg == शून्य)
		वापस 0;
	/* That works क्रम all keylargos but shall be fixed properly
	 * some day... The problem is that it seems we can't rely
	 * on the "reg" property of the GPIO nodes, they are either
	 * relative to the base of KeyLargo or to the base of the
	 * GPIO space, and the device-tree करोesn't help.
	 */
	offset = *reg;
	अगर (offset < KEYLARGO_GPIO_LEVELS0)
		offset += KEYLARGO_GPIO_LEVELS0;
	वापस offset;
पूर्ण

अटल पूर्णांक pmac_cpufreq_suspend(काष्ठा cpufreq_policy *policy)
अणु
	/* Ok, this could be made a bit smarter, but let's be robust क्रम now. We
	 * always क्रमce a speed change to high speed beक्रमe sleep, to make sure
	 * we have appropriate voltage and/or bus speed क्रम the wakeup process,
	 * and to make sure our loops_per_jअगरfies are "good enough", that is will
	 * not cause too लघु delays अगर we sleep in low speed and wake in high
	 * speed..
	 */
	no_schedule = 1;
	sleep_freq = cur_freq;
	अगर (cur_freq == low_freq && !is_pmu_based)
		करो_set_cpu_speed(policy, CPUFREQ_HIGH);
	वापस 0;
पूर्ण

अटल पूर्णांक pmac_cpufreq_resume(काष्ठा cpufreq_policy *policy)
अणु
	/* If we resume, first check अगर we have a get() function */
	अगर (get_speed_proc)
		cur_freq = get_speed_proc();
	अन्यथा
		cur_freq = 0;

	/* We करोn't, hrm... we don't really know our speed here, best
	 * is that we क्रमce a चयन to whatever it was, which is
	 * probably high speed due to our suspend() routine
	 */
	करो_set_cpu_speed(policy, sleep_freq == low_freq ?
			 CPUFREQ_LOW : CPUFREQ_HIGH);

	ppc_proc_freq = cur_freq * 1000ul;

	no_schedule = 0;
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver pmac_cpufreq_driver = अणु
	.verअगरy 	= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= pmac_cpufreq_target,
	.get		= pmac_cpufreq_get_speed,
	.init		= pmac_cpufreq_cpu_init,
	.suspend	= pmac_cpufreq_suspend,
	.resume		= pmac_cpufreq_resume,
	.flags		= CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING,
	.attr		= cpufreq_generic_attr,
	.name		= "powermac",
पूर्ण;


अटल पूर्णांक pmac_cpufreq_init_MacRISC3(काष्ठा device_node *cpunode)
अणु
	काष्ठा device_node *volt_gpio_np = of_find_node_by_name(शून्य,
								"voltage-gpio");
	काष्ठा device_node *freq_gpio_np = of_find_node_by_name(शून्य,
								"frequency-gpio");
	काष्ठा device_node *slew_करोne_gpio_np = of_find_node_by_name(शून्य,
								     "slewing-done");
	स्थिर u32 *value;

	/*
	 * Check to see अगर it's GPIO driven or PMU only
	 *
	 * The way we extract the GPIO address is slightly hackish, but it
	 * works well enough क्रम now. We need to असलtract the whole GPIO
	 * stuff sooner or later anyway
	 */

	अगर (volt_gpio_np)
		voltage_gpio = पढ़ो_gpio(volt_gpio_np);
	अगर (freq_gpio_np)
		frequency_gpio = पढ़ो_gpio(freq_gpio_np);
	अगर (slew_करोne_gpio_np)
		slew_करोne_gpio = पढ़ो_gpio(slew_करोne_gpio_np);

	/* If we use the frequency GPIOs, calculate the min/max speeds based
	 * on the bus frequencies
	 */
	अगर (frequency_gpio && slew_करोne_gpio) अणु
		पूर्णांक lenp, rc;
		स्थिर u32 *freqs, *ratio;

		freqs = of_get_property(cpunode, "bus-frequencies", &lenp);
		lenp /= माप(u32);
		अगर (freqs == शून्य || lenp != 2) अणु
			pr_err("bus-frequencies incorrect or missing\n");
			वापस 1;
		पूर्ण
		ratio = of_get_property(cpunode, "processor-to-bus-ratio*2",
						शून्य);
		अगर (ratio == शून्य) अणु
			pr_err("processor-to-bus-ratio*2 missing\n");
			वापस 1;
		पूर्ण

		/* Get the min/max bus frequencies */
		low_freq = min(freqs[0], freqs[1]);
		hi_freq = max(freqs[0], freqs[1]);

		/* Grrrr.. It _seems_ that the device-tree is lying on the low bus
		 * frequency, it claims it to be around 84Mhz on some models जबतक
		 * it appears to be approx. 101Mhz on all. Let's hack around here...
		 * क्रमtunately, we करोn't need to be too precise
		 */
		अगर (low_freq < 98000000)
			low_freq = 101000000;

		/* Convert those to CPU core घड़ीs */
		low_freq = (low_freq * (*ratio)) / 2000;
		hi_freq = (hi_freq * (*ratio)) / 2000;

		/* Now we get the frequencies, we पढ़ो the GPIO to see what is out current
		 * speed
		 */
		rc = pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य, frequency_gpio, 0);
		cur_freq = (rc & 0x01) ? hi_freq : low_freq;

		set_speed_proc = gpios_set_cpu_speed;
		वापस 1;
	पूर्ण

	/* If we use the PMU, look क्रम the min & max frequencies in the
	 * device-tree
	 */
	value = of_get_property(cpunode, "min-clock-frequency", शून्य);
	अगर (!value)
		वापस 1;
	low_freq = (*value) / 1000;
	/* The PowerBook G4 12" (PowerBook6,1) has an error in the device-tree
	 * here */
	अगर (low_freq < 100000)
		low_freq *= 10;

	value = of_get_property(cpunode, "max-clock-frequency", शून्य);
	अगर (!value)
		वापस 1;
	hi_freq = (*value) / 1000;
	set_speed_proc = pmu_set_cpu_speed;
	is_pmu_based = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pmac_cpufreq_init_7447A(काष्ठा device_node *cpunode)
अणु
	काष्ठा device_node *volt_gpio_np;

	अगर (of_get_property(cpunode, "dynamic-power-step", शून्य) == शून्य)
		वापस 1;

	volt_gpio_np = of_find_node_by_name(शून्य, "cpu-vcore-select");
	अगर (volt_gpio_np)
		voltage_gpio = पढ़ो_gpio(volt_gpio_np);
	of_node_put(volt_gpio_np);
	अगर (!voltage_gpio)अणु
		pr_err("missing cpu-vcore-select gpio\n");
		वापस 1;
	पूर्ण

	/* OF only reports the high frequency */
	hi_freq = cur_freq;
	low_freq = cur_freq/2;

	/* Read actual frequency from CPU */
	cur_freq = dfs_get_cpu_speed();
	set_speed_proc = dfs_set_cpu_speed;
	get_speed_proc = dfs_get_cpu_speed;

	वापस 0;
पूर्ण

अटल पूर्णांक pmac_cpufreq_init_750FX(काष्ठा device_node *cpunode)
अणु
	काष्ठा device_node *volt_gpio_np;
	u32 pvr;
	स्थिर u32 *value;

	अगर (of_get_property(cpunode, "dynamic-power-step", शून्य) == शून्य)
		वापस 1;

	hi_freq = cur_freq;
	value = of_get_property(cpunode, "reduced-clock-frequency", शून्य);
	अगर (!value)
		वापस 1;
	low_freq = (*value) / 1000;

	volt_gpio_np = of_find_node_by_name(शून्य, "cpu-vcore-select");
	अगर (volt_gpio_np)
		voltage_gpio = पढ़ो_gpio(volt_gpio_np);

	of_node_put(volt_gpio_np);
	pvr = mfspr(SPRN_PVR);
	has_cpu_l2lve = !((pvr & 0xf00) == 0x100);

	set_speed_proc = cpu_750fx_cpu_speed;
	get_speed_proc = cpu_750fx_get_cpu_speed;
	cur_freq = cpu_750fx_get_cpu_speed();

	वापस 0;
पूर्ण

/* Currently, we support the following machines:
 *
 *  - Titanium PowerBook 1Ghz (PMU based, 667Mhz & 1Ghz)
 *  - Titanium PowerBook 800 (PMU based, 667Mhz & 800Mhz)
 *  - Titanium PowerBook 400 (PMU based, 300Mhz & 400Mhz)
 *  - Titanium PowerBook 500 (PMU based, 300Mhz & 500Mhz)
 *  - iBook2 500/600 (PMU based, 400Mhz & 500/600Mhz)
 *  - iBook2 700 (CPU based, 400Mhz & 700Mhz, support low voltage)
 *  - Recent MacRISC3 laptops
 *  - All new machines with 7447A CPUs
 */
अटल पूर्णांक __init pmac_cpufreq_setup(व्योम)
अणु
	काष्ठा device_node	*cpunode;
	स्थिर u32		*value;

	अगर (म_माला(boot_command_line, "nocpufreq"))
		वापस 0;

	/* Get first CPU node */
	cpunode = of_cpu_device_node_get(0);
	अगर (!cpunode)
		जाओ out;

	/* Get current cpu घड़ी freq */
	value = of_get_property(cpunode, "clock-frequency", शून्य);
	अगर (!value)
		जाओ out;
	cur_freq = (*value) / 1000;

	/*  Check क्रम 7447A based MacRISC3 */
	अगर (of_machine_is_compatible("MacRISC3") &&
	    of_get_property(cpunode, "dynamic-power-step", शून्य) &&
	    PVR_VER(mfspr(SPRN_PVR)) == 0x8003) अणु
		pmac_cpufreq_init_7447A(cpunode);

		/* Allow dynamic चयनing */
		transition_latency = 8000000;
		pmac_cpufreq_driver.flags &= ~CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING;
	/* Check क्रम other MacRISC3 machines */
	पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerBook3,4") ||
		   of_machine_is_compatible("PowerBook3,5") ||
		   of_machine_is_compatible("MacRISC3")) अणु
		pmac_cpufreq_init_MacRISC3(cpunode);
	/* Else check क्रम iBook2 500/600 */
	पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerBook4,1")) अणु
		hi_freq = cur_freq;
		low_freq = 400000;
		set_speed_proc = pmu_set_cpu_speed;
		is_pmu_based = 1;
	पूर्ण
	/* Else check क्रम TiPb 550 */
	अन्यथा अगर (of_machine_is_compatible("PowerBook3,3") && cur_freq == 550000) अणु
		hi_freq = cur_freq;
		low_freq = 500000;
		set_speed_proc = pmu_set_cpu_speed;
		is_pmu_based = 1;
	पूर्ण
	/* Else check क्रम TiPb 400 & 500 */
	अन्यथा अगर (of_machine_is_compatible("PowerBook3,2")) अणु
		/* We only know about the 400 MHz and the 500Mhz model
		 * they both have 300 MHz as low frequency
		 */
		अगर (cur_freq < 350000 || cur_freq > 550000)
			जाओ out;
		hi_freq = cur_freq;
		low_freq = 300000;
		set_speed_proc = pmu_set_cpu_speed;
		is_pmu_based = 1;
	पूर्ण
	/* Else check क्रम 750FX */
	अन्यथा अगर (PVR_VER(mfspr(SPRN_PVR)) == 0x7000)
		pmac_cpufreq_init_750FX(cpunode);
out:
	of_node_put(cpunode);
	अगर (set_speed_proc == शून्य)
		वापस -ENODEV;

	pmac_cpu_freqs[CPUFREQ_LOW].frequency = low_freq;
	pmac_cpu_freqs[CPUFREQ_HIGH].frequency = hi_freq;
	ppc_proc_freq = cur_freq * 1000ul;

	pr_info("Registering PowerMac CPU frequency driver\n");
	pr_info("Low: %d Mhz, High: %d Mhz, Boot: %d Mhz\n",
		low_freq/1000, hi_freq/1000, cur_freq/1000);

	वापस cpufreq_रेजिस्टर_driver(&pmac_cpufreq_driver);
पूर्ण

module_init(pmac_cpufreq_setup);


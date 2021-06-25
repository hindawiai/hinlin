<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
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
#समावेश <linux/of_device.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/smu.h>
#समावेश <यंत्र/pmac_pfunc.h>

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

अटल काष्ठा cpufreq_frequency_table g5_cpu_freqs[] = अणु
	अणु0, CPUFREQ_HIGH,	0पूर्ण,
	अणु0, CPUFREQ_LOW,	0पूर्ण,
	अणु0, 0,			CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

/* Power mode data is an array of the 32 bits PCR values to use क्रम
 * the various frequencies, retrieved from the device-tree
 */
अटल पूर्णांक g5_pmode_cur;

अटल व्योम (*g5_चयन_volt)(पूर्णांक speed_mode);
अटल पूर्णांक (*g5_चयन_freq)(पूर्णांक speed_mode);
अटल पूर्णांक (*g5_query_freq)(व्योम);

अटल अचिन्हित दीर्घ transition_latency;

#अगर_घोषित CONFIG_PMAC_SMU

अटल स्थिर u32 *g5_pmode_data;
अटल पूर्णांक g5_pmode_max;

अटल काष्ठा smu_sdbp_fvt *g5_fvt_table;	/* table of op. poपूर्णांकs */
अटल पूर्णांक g5_fvt_count;			/* number of op. poपूर्णांकs */
अटल पूर्णांक g5_fvt_cur;				/* current op. poपूर्णांक */

/*
 * SMU based voltage चयनing क्रम Neo2 platक्रमms
 */

अटल व्योम g5_smu_चयन_volt(पूर्णांक speed_mode)
अणु
	काष्ठा smu_simple_cmd	cmd;

	DECLARE_COMPLETION_ONSTACK(comp);
	smu_queue_simple(&cmd, SMU_CMD_POWER_COMMAND, 8, smu_करोne_complete,
			 &comp, 'V', 'S', 'L', 'E', 'W',
			 0xff, g5_fvt_cur+1, speed_mode);
	रुको_क्रम_completion(&comp);
पूर्ण

/*
 * Platक्रमm function based voltage/vdnap चयनing क्रम Neo2
 */

अटल काष्ठा pmf_function *pfunc_set_vdnap0;
अटल काष्ठा pmf_function *pfunc_vdnap0_complete;

अटल व्योम g5_vdnap_चयन_volt(पूर्णांक speed_mode)
अणु
	काष्ठा pmf_args args;
	u32 slew, करोne = 0;
	अचिन्हित दीर्घ समयout;

	slew = (speed_mode == CPUFREQ_LOW) ? 1 : 0;
	args.count = 1;
	args.u[0].p = &slew;

	pmf_call_one(pfunc_set_vdnap0, &args);

	/* It's an irq GPIO so we should be able to just block here,
	 * I'll do that later after I've properly tested the IRQ code क्रम
	 * platक्रमm functions
	 */
	समयout = jअगरfies + HZ/10;
	जबतक(!समय_after(jअगरfies, समयout)) अणु
		args.count = 1;
		args.u[0].p = &करोne;
		pmf_call_one(pfunc_vdnap0_complete, &args);
		अगर (करोne)
			अवरोध;
		usleep_range(1000, 1000);
	पूर्ण
	अगर (करोne == 0)
		pr_warn("Timeout in clock slewing !\n");
पूर्ण


/*
 * SCOM based frequency चयनing क्रम 970FX rev3
 */
अटल पूर्णांक g5_scom_चयन_freq(पूर्णांक speed_mode)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक to;

	/* If frequency is going up, first ramp up the voltage */
	अगर (speed_mode < g5_pmode_cur)
		g5_चयन_volt(speed_mode);

	local_irq_save(flags);

	/* Clear PCR high */
	scom970_ग_लिखो(SCOM_PCR, 0);
	/* Clear PCR low */
       	scom970_ग_लिखो(SCOM_PCR, PCR_HILO_SELECT | 0);
	/* Set PCR low */
	scom970_ग_लिखो(SCOM_PCR, PCR_HILO_SELECT |
		      g5_pmode_data[speed_mode]);

	/* Wait क्रम completion */
	क्रम (to = 0; to < 10; to++) अणु
		अचिन्हित दीर्घ psr = scom970_पढ़ो(SCOM_PSR);

		अगर ((psr & PSR_CMD_RECEIVED) == 0 &&
		    (((psr >> PSR_CUR_SPEED_SHIFT) ^
		      (g5_pmode_data[speed_mode] >> PCR_SPEED_SHIFT)) & 0x3)
		    == 0)
			अवरोध;
		अगर (psr & PSR_CMD_COMPLETED)
			अवरोध;
		udelay(100);
	पूर्ण

	local_irq_restore(flags);

	/* If frequency is going करोwn, last ramp the voltage */
	अगर (speed_mode > g5_pmode_cur)
		g5_चयन_volt(speed_mode);

	g5_pmode_cur = speed_mode;
	ppc_proc_freq = g5_cpu_freqs[speed_mode].frequency * 1000ul;

	वापस 0;
पूर्ण

अटल पूर्णांक g5_scom_query_freq(व्योम)
अणु
	अचिन्हित दीर्घ psr = scom970_पढ़ो(SCOM_PSR);
	पूर्णांक i;

	क्रम (i = 0; i <= g5_pmode_max; i++)
		अगर ((((psr >> PSR_CUR_SPEED_SHIFT) ^
		      (g5_pmode_data[i] >> PCR_SPEED_SHIFT)) & 0x3) == 0)
			अवरोध;
	वापस i;
पूर्ण

/*
 * Fake voltage चयनing क्रम platक्रमms with missing support
 */

अटल व्योम g5_dummy_चयन_volt(पूर्णांक speed_mode)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_PMAC_SMU */

/*
 * Platक्रमm function based voltage चयनing क्रम PowerMac7,2 & 7,3
 */

अटल काष्ठा pmf_function *pfunc_cpu0_volt_high;
अटल काष्ठा pmf_function *pfunc_cpu0_volt_low;
अटल काष्ठा pmf_function *pfunc_cpu1_volt_high;
अटल काष्ठा pmf_function *pfunc_cpu1_volt_low;

अटल व्योम g5_pfunc_चयन_volt(पूर्णांक speed_mode)
अणु
	अगर (speed_mode == CPUFREQ_HIGH) अणु
		अगर (pfunc_cpu0_volt_high)
			pmf_call_one(pfunc_cpu0_volt_high, शून्य);
		अगर (pfunc_cpu1_volt_high)
			pmf_call_one(pfunc_cpu1_volt_high, शून्य);
	पूर्ण अन्यथा अणु
		अगर (pfunc_cpu0_volt_low)
			pmf_call_one(pfunc_cpu0_volt_low, शून्य);
		अगर (pfunc_cpu1_volt_low)
			pmf_call_one(pfunc_cpu1_volt_low, शून्य);
	पूर्ण
	usleep_range(10000, 10000); /* should be faster , to fix */
पूर्ण

/*
 * Platक्रमm function based frequency चयनing क्रम PowerMac7,2 & 7,3
 */

अटल काष्ठा pmf_function *pfunc_cpu_setfreq_high;
अटल काष्ठा pmf_function *pfunc_cpu_setfreq_low;
अटल काष्ठा pmf_function *pfunc_cpu_getfreq;
अटल काष्ठा pmf_function *pfunc_slewing_करोne;

अटल पूर्णांक g5_pfunc_चयन_freq(पूर्णांक speed_mode)
अणु
	काष्ठा pmf_args args;
	u32 करोne = 0;
	अचिन्हित दीर्घ समयout;
	पूर्णांक rc;

	DBG("g5_pfunc_switch_freq(%d)\n", speed_mode);

	/* If frequency is going up, first ramp up the voltage */
	अगर (speed_mode < g5_pmode_cur)
		g5_चयन_volt(speed_mode);

	/* Do it */
	अगर (speed_mode == CPUFREQ_HIGH)
		rc = pmf_call_one(pfunc_cpu_setfreq_high, शून्य);
	अन्यथा
		rc = pmf_call_one(pfunc_cpu_setfreq_low, शून्य);

	अगर (rc)
		pr_warn("pfunc switch error %d\n", rc);

	/* It's an irq GPIO so we should be able to just block here,
	 * I'll do that later after I've properly tested the IRQ code क्रम
	 * platक्रमm functions
	 */
	समयout = jअगरfies + HZ/10;
	जबतक(!समय_after(jअगरfies, समयout)) अणु
		args.count = 1;
		args.u[0].p = &करोne;
		pmf_call_one(pfunc_slewing_करोne, &args);
		अगर (करोne)
			अवरोध;
		usleep_range(500, 500);
	पूर्ण
	अगर (करोne == 0)
		pr_warn("Timeout in clock slewing !\n");

	/* If frequency is going करोwn, last ramp the voltage */
	अगर (speed_mode > g5_pmode_cur)
		g5_चयन_volt(speed_mode);

	g5_pmode_cur = speed_mode;
	ppc_proc_freq = g5_cpu_freqs[speed_mode].frequency * 1000ul;

	वापस 0;
पूर्ण

अटल पूर्णांक g5_pfunc_query_freq(व्योम)
अणु
	काष्ठा pmf_args args;
	u32 val = 0;

	args.count = 1;
	args.u[0].p = &val;
	pmf_call_one(pfunc_cpu_getfreq, &args);
	वापस val ? CPUFREQ_HIGH : CPUFREQ_LOW;
पूर्ण


/*
 * Common पूर्णांकerface to the cpufreq core
 */

अटल पूर्णांक g5_cpufreq_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	वापस g5_चयन_freq(index);
पूर्ण

अटल अचिन्हित पूर्णांक g5_cpufreq_get_speed(अचिन्हित पूर्णांक cpu)
अणु
	वापस g5_cpu_freqs[g5_pmode_cur].frequency;
पूर्ण

अटल पूर्णांक g5_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	cpufreq_generic_init(policy, g5_cpu_freqs, transition_latency);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver g5_cpufreq_driver = अणु
	.name		= "powermac",
	.flags		= CPUFREQ_CONST_LOOPS,
	.init		= g5_cpufreq_cpu_init,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= g5_cpufreq_target,
	.get		= g5_cpufreq_get_speed,
	.attr 		= cpufreq_generic_attr,
पूर्ण;


#अगर_घोषित CONFIG_PMAC_SMU

अटल पूर्णांक __init g5_neo2_cpufreq_init(काष्ठा device_node *cpunode)
अणु
	अचिन्हित पूर्णांक psize, ssize;
	अचिन्हित दीर्घ max_freq;
	अक्षर *freq_method, *volt_method;
	स्थिर u32 *valp;
	u32 pvr_hi;
	पूर्णांक use_volts_vdnap = 0;
	पूर्णांक use_volts_smu = 0;
	पूर्णांक rc = -ENODEV;

	/* Check supported platक्रमms */
	अगर (of_machine_is_compatible("PowerMac8,1") ||
	    of_machine_is_compatible("PowerMac8,2") ||
	    of_machine_is_compatible("PowerMac9,1") ||
	    of_machine_is_compatible("PowerMac12,1"))
		use_volts_smu = 1;
	अन्यथा अगर (of_machine_is_compatible("PowerMac11,2"))
		use_volts_vdnap = 1;
	अन्यथा
		वापस -ENODEV;

	/* Check 970FX क्रम now */
	valp = of_get_property(cpunode, "cpu-version", शून्य);
	अगर (!valp) अणु
		DBG("No cpu-version property !\n");
		जाओ bail_noprops;
	पूर्ण
	pvr_hi = (*valp) >> 16;
	अगर (pvr_hi != 0x3c && pvr_hi != 0x44) अणु
		pr_err("Unsupported CPU version\n");
		जाओ bail_noprops;
	पूर्ण

	/* Look क्रम the घातertune data in the device-tree */
	g5_pmode_data = of_get_property(cpunode, "power-mode-data",&psize);
	अगर (!g5_pmode_data) अणु
		DBG("No power-mode-data !\n");
		जाओ bail_noprops;
	पूर्ण
	g5_pmode_max = psize / माप(u32) - 1;

	अगर (use_volts_smu) अणु
		स्थिर काष्ठा smu_sdbp_header *shdr;

		/* Look क्रम the FVT table */
		shdr = smu_get_sdb_partition(SMU_SDB_FVT_ID, शून्य);
		अगर (!shdr)
			जाओ bail_noprops;
		g5_fvt_table = (काष्ठा smu_sdbp_fvt *)&shdr[1];
		ssize = (shdr->len * माप(u32)) - माप(*shdr);
		g5_fvt_count = ssize / माप(*g5_fvt_table);
		g5_fvt_cur = 0;

		/* Sanity checking */
		अगर (g5_fvt_count < 1 || g5_pmode_max < 1)
			जाओ bail_noprops;

		g5_चयन_volt = g5_smu_चयन_volt;
		volt_method = "SMU";
	पूर्ण अन्यथा अगर (use_volts_vdnap) अणु
		काष्ठा device_node *root;

		root = of_find_node_by_path("/");
		अगर (root == शून्य) अणु
			pr_err("Can't find root of device tree\n");
			जाओ bail_noprops;
		पूर्ण
		pfunc_set_vdnap0 = pmf_find_function(root, "set-vdnap0");
		pfunc_vdnap0_complete =
			pmf_find_function(root, "slewing-done");
		of_node_put(root);
		अगर (pfunc_set_vdnap0 == शून्य ||
		    pfunc_vdnap0_complete == शून्य) अणु
			pr_err("Can't find required platform function\n");
			जाओ bail_noprops;
		पूर्ण

		g5_चयन_volt = g5_vdnap_चयन_volt;
		volt_method = "GPIO";
	पूर्ण अन्यथा अणु
		g5_चयन_volt = g5_dummy_चयन_volt;
		volt_method = "none";
	पूर्ण

	/*
	 * From what I see, घड़ी-frequency is always the maximal frequency.
	 * The current driver can not slew sysclk yet, so we really only deal
	 * with घातertune steps क्रम now. We also only implement full freq and
	 * half freq in this version. So far, I haven't yet seen a machine
	 * supporting anything अन्यथा.
	 */
	valp = of_get_property(cpunode, "clock-frequency", शून्य);
	अगर (!valp)
		वापस -ENODEV;
	max_freq = (*valp)/1000;
	g5_cpu_freqs[0].frequency = max_freq;
	g5_cpu_freqs[1].frequency = max_freq/2;

	/* Set callbacks */
	transition_latency = 12000;
	g5_चयन_freq = g5_scom_चयन_freq;
	g5_query_freq = g5_scom_query_freq;
	freq_method = "SCOM";

	/* Force apply current frequency to make sure everything is in
	 * sync (voltage is right क्रम example). Firmware may leave us with
	 * a strange setting ...
	 */
	g5_चयन_volt(CPUFREQ_HIGH);
	msleep(10);
	g5_pmode_cur = -1;
	g5_चयन_freq(g5_query_freq());

	pr_info("Registering G5 CPU frequency driver\n");
	pr_info("Frequency method: %s, Voltage method: %s\n",
		freq_method, volt_method);
	pr_info("Low: %d Mhz, High: %d Mhz, Cur: %d MHz\n",
		g5_cpu_freqs[1].frequency/1000,
		g5_cpu_freqs[0].frequency/1000,
		g5_cpu_freqs[g5_pmode_cur].frequency/1000);

	rc = cpufreq_रेजिस्टर_driver(&g5_cpufreq_driver);

	/* We keep the CPU node on hold... hopefully, Apple G5 करोn't have
	 * hotplug CPU with a dynamic device-tree ...
	 */
	वापस rc;

 bail_noprops:
	of_node_put(cpunode);

	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_PMAC_SMU */


अटल पूर्णांक __init g5_pm72_cpufreq_init(काष्ठा device_node *cpunode)
अणु
	काष्ठा device_node *cpuid = शून्य, *hwघड़ी = शून्य;
	स्थिर u8 *eeprom = शून्य;
	स्थिर u32 *valp;
	u64 max_freq, min_freq, ih, il;
	पूर्णांक has_volt = 1, rc = 0;

	DBG("cpufreq: Initializing for PowerMac7,2, PowerMac7,3 and"
	    " RackMac3,1...\n");

	/* Lookup the cpuid eeprom node */
        cpuid = of_find_node_by_path("/u3@0,f8000000/i2c@f8001000/cpuid@a0");
	अगर (cpuid != शून्य)
		eeprom = of_get_property(cpuid, "cpuid", शून्य);
	अगर (eeprom == शून्य) अणु
		pr_err("Can't find cpuid EEPROM !\n");
		rc = -ENODEV;
		जाओ bail;
	पूर्ण

	/* Lookup the i2c hwघड़ी */
	क्रम_each_node_by_name(hwघड़ी, "i2c-hwclock") अणु
		स्थिर अक्षर *loc = of_get_property(hwघड़ी,
				"hwctrl-location", शून्य);
		अगर (loc == शून्य)
			जारी;
		अगर (म_भेद(loc, "CPU CLOCK"))
			जारी;
		अगर (!of_get_property(hwघड़ी, "platform-get-frequency", शून्य))
			जारी;
		अवरोध;
	पूर्ण
	अगर (hwघड़ी == शून्य) अणु
		pr_err("Can't find i2c clock chip !\n");
		rc = -ENODEV;
		जाओ bail;
	पूर्ण

	DBG("cpufreq: i2c clock chip found: %pOF\n", hwघड़ी);

	/* Now get all the platक्रमm functions */
	pfunc_cpu_getfreq =
		pmf_find_function(hwघड़ी, "get-frequency");
	pfunc_cpu_setfreq_high =
		pmf_find_function(hwघड़ी, "set-frequency-high");
	pfunc_cpu_setfreq_low =
		pmf_find_function(hwघड़ी, "set-frequency-low");
	pfunc_slewing_करोne =
		pmf_find_function(hwघड़ी, "slewing-done");
	pfunc_cpu0_volt_high =
		pmf_find_function(hwघड़ी, "set-voltage-high-0");
	pfunc_cpu0_volt_low =
		pmf_find_function(hwघड़ी, "set-voltage-low-0");
	pfunc_cpu1_volt_high =
		pmf_find_function(hwघड़ी, "set-voltage-high-1");
	pfunc_cpu1_volt_low =
		pmf_find_function(hwघड़ी, "set-voltage-low-1");

	/* Check we have minimum requirements */
	अगर (pfunc_cpu_getfreq == शून्य || pfunc_cpu_setfreq_high == शून्य ||
	    pfunc_cpu_setfreq_low == शून्य || pfunc_slewing_करोne == शून्य) अणु
		pr_err("Can't find platform functions !\n");
		rc = -ENODEV;
		जाओ bail;
	पूर्ण

	/* Check that we have complete sets */
	अगर (pfunc_cpu0_volt_high == शून्य || pfunc_cpu0_volt_low == शून्य) अणु
		pmf_put_function(pfunc_cpu0_volt_high);
		pmf_put_function(pfunc_cpu0_volt_low);
		pfunc_cpu0_volt_high = pfunc_cpu0_volt_low = शून्य;
		has_volt = 0;
	पूर्ण
	अगर (!has_volt ||
	    pfunc_cpu1_volt_high == शून्य || pfunc_cpu1_volt_low == शून्य) अणु
		pmf_put_function(pfunc_cpu1_volt_high);
		pmf_put_function(pfunc_cpu1_volt_low);
		pfunc_cpu1_volt_high = pfunc_cpu1_volt_low = शून्य;
	पूर्ण

	/* Note: The device tree also contains a "platform-set-values"
	 * function क्रम which I haven't quite figured out the usage. It
	 * might have to be called on init and/or wakeup, I'm not too sure
	 * but things seem to work fine without it so far ...
	 */

	/* Get max frequency from device-tree */
	valp = of_get_property(cpunode, "clock-frequency", शून्य);
	अगर (!valp) अणु
		pr_err("Can't find CPU frequency !\n");
		rc = -ENODEV;
		जाओ bail;
	पूर्ण

	max_freq = (*valp)/1000;

	/* Now calculate reduced frequency by using the cpuid input freq
	 * ratio. This requires 64 bits math unless we are willing to lose
	 * some precision
	 */
	ih = *((u32 *)(eeprom + 0x10));
	il = *((u32 *)(eeprom + 0x20));

	/* Check क्रम machines with no useful settings */
	अगर (il == ih) अणु
		pr_warn("No low frequency mode available on this model !\n");
		rc = -ENODEV;
		जाओ bail;
	पूर्ण

	min_freq = 0;
	अगर (ih != 0 && il != 0)
		min_freq = (max_freq * il) / ih;

	/* Sanity check */
	अगर (min_freq >= max_freq || min_freq < 1000) अणु
		pr_err("Can't calculate low frequency !\n");
		rc = -ENXIO;
		जाओ bail;
	पूर्ण
	g5_cpu_freqs[0].frequency = max_freq;
	g5_cpu_freqs[1].frequency = min_freq;

	/* Based on a measurement on Xserve G5, rounded up. */
	transition_latency = 10 * NSEC_PER_MSEC;

	/* Set callbacks */
	g5_चयन_volt = g5_pfunc_चयन_volt;
	g5_चयन_freq = g5_pfunc_चयन_freq;
	g5_query_freq = g5_pfunc_query_freq;

	/* Force apply current frequency to make sure everything is in
	 * sync (voltage is right क्रम example). Firmware may leave us with
	 * a strange setting ...
	 */
	g5_चयन_volt(CPUFREQ_HIGH);
	msleep(10);
	g5_pmode_cur = -1;
	g5_चयन_freq(g5_query_freq());

	pr_info("Registering G5 CPU frequency driver\n");
	pr_info("Frequency method: i2c/pfunc, Voltage method: %s\n",
		has_volt ? "i2c/pfunc" : "none");
	pr_info("Low: %d Mhz, High: %d Mhz, Cur: %d MHz\n",
		g5_cpu_freqs[1].frequency/1000,
		g5_cpu_freqs[0].frequency/1000,
		g5_cpu_freqs[g5_pmode_cur].frequency/1000);

	rc = cpufreq_रेजिस्टर_driver(&g5_cpufreq_driver);
 bail:
	अगर (rc != 0) अणु
		pmf_put_function(pfunc_cpu_getfreq);
		pmf_put_function(pfunc_cpu_setfreq_high);
		pmf_put_function(pfunc_cpu_setfreq_low);
		pmf_put_function(pfunc_slewing_करोne);
		pmf_put_function(pfunc_cpu0_volt_high);
		pmf_put_function(pfunc_cpu0_volt_low);
		pmf_put_function(pfunc_cpu1_volt_high);
		pmf_put_function(pfunc_cpu1_volt_low);
	पूर्ण
	of_node_put(hwघड़ी);
	of_node_put(cpuid);
	of_node_put(cpunode);

	वापस rc;
पूर्ण

अटल पूर्णांक __init g5_cpufreq_init(व्योम)
अणु
	काष्ठा device_node *cpunode;
	पूर्णांक rc = 0;

	/* Get first CPU node */
	cpunode = of_cpu_device_node_get(0);
	अगर (cpunode == शून्य) अणु
		pr_err("Can't find any CPU node\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_machine_is_compatible("PowerMac7,2") ||
	    of_machine_is_compatible("PowerMac7,3") ||
	    of_machine_is_compatible("RackMac3,1"))
		rc = g5_pm72_cpufreq_init(cpunode);
#अगर_घोषित CONFIG_PMAC_SMU
	अन्यथा
		rc = g5_neo2_cpufreq_init(cpunode);
#पूर्ण_अगर /* CONFIG_PMAC_SMU */

	वापस rc;
पूर्ण

module_init(g5_cpufreq_init);


MODULE_LICENSE("GPL");

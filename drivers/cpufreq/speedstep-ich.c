<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2001  Dave Jones, Arjan van de ven.
 * (C) 2002 - 2003  Dominik Broकरोwski <linux@broकरो.de>
 *
 *  Based upon reverse engineered inक्रमmation, and on Intel करोcumentation
 *  क्रम chipsets ICH2-M and ICH3-M.
 *
 *  Many thanks to Ducrot Bruno क्रम finding and fixing the last
 *  "missing link" क्रम ICH2-M/ICH3-M support, and to Thomas Winkler
 *  क्रम extensive testing.
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 */


/*********************************************************************
 *                        SPEEDSTEP - DEFINITIONS                    *
 *********************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/cpu_device_id.h>

#समावेश "speedstep-lib.h"


/* speedstep_chipset:
 *   It is necessary to know which chipset is used. As accesses to
 * this device occur at various places in this module, we need a
 * अटल काष्ठा pci_dev * poपूर्णांकing to that device.
 */
अटल काष्ठा pci_dev *speedstep_chipset_dev;


/* speedstep_processor
 */
अटल क्रमागत speedstep_processor speedstep_processor;

अटल u32 pmbase;

/*
 *   There are only two frequency states क्रम each processor. Values
 * are in kHz क्रम the समय being.
 */
अटल काष्ठा cpufreq_frequency_table speedstep_freqs[] = अणु
	अणु0, SPEEDSTEP_HIGH,	0पूर्ण,
	अणु0, SPEEDSTEP_LOW,	0पूर्ण,
	अणु0, 0,			CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;


/**
 * speedstep_find_रेजिस्टर - पढ़ो the PMBASE address
 *
 * Returns: -ENODEV अगर no रेजिस्टर could be found
 */
अटल पूर्णांक speedstep_find_रेजिस्टर(व्योम)
अणु
	अगर (!speedstep_chipset_dev)
		वापस -ENODEV;

	/* get PMBASE */
	pci_पढ़ो_config_dword(speedstep_chipset_dev, 0x40, &pmbase);
	अगर (!(pmbase & 0x01)) अणु
		pr_err("could not find speedstep register\n");
		वापस -ENODEV;
	पूर्ण

	pmbase &= 0xFFFFFFFE;
	अगर (!pmbase) अणु
		pr_err("could not find speedstep register\n");
		वापस -ENODEV;
	पूर्ण

	pr_debug("pmbase is 0x%x\n", pmbase);
	वापस 0;
पूर्ण

/**
 * speedstep_set_state - set the SpeedStep state
 * @state: new processor frequency state (SPEEDSTEP_LOW or SPEEDSTEP_HIGH)
 *
 *   Tries to change the SpeedStep state.  Can be called from
 *   smp_call_function_single.
 */
अटल व्योम speedstep_set_state(अचिन्हित पूर्णांक state)
अणु
	u8 pm2_blk;
	u8 value;
	अचिन्हित दीर्घ flags;

	अगर (state > 0x1)
		वापस;

	/* Disable IRQs */
	local_irq_save(flags);

	/* पढ़ो state */
	value = inb(pmbase + 0x50);

	pr_debug("read at pmbase 0x%x + 0x50 returned 0x%x\n", pmbase, value);

	/* ग_लिखो new state */
	value &= 0xFE;
	value |= state;

	pr_debug("writing 0x%x to pmbase 0x%x + 0x50\n", value, pmbase);

	/* Disable bus master arbitration */
	pm2_blk = inb(pmbase + 0x20);
	pm2_blk |= 0x01;
	outb(pm2_blk, (pmbase + 0x20));

	/* Actual transition */
	outb(value, (pmbase + 0x50));

	/* Restore bus master arbitration */
	pm2_blk &= 0xfe;
	outb(pm2_blk, (pmbase + 0x20));

	/* check अगर transition was successful */
	value = inb(pmbase + 0x50);

	/* Enable IRQs */
	local_irq_restore(flags);

	pr_debug("read at pmbase 0x%x + 0x50 returned 0x%x\n", pmbase, value);

	अगर (state == (value & 0x1))
		pr_debug("change to %u MHz succeeded\n",
			speedstep_get_frequency(speedstep_processor) / 1000);
	अन्यथा
		pr_err("change failed - I/O error\n");

	वापस;
पूर्ण

/* Wrapper क्रम smp_call_function_single. */
अटल व्योम _speedstep_set_state(व्योम *_state)
अणु
	speedstep_set_state(*(अचिन्हित पूर्णांक *)_state);
पूर्ण

/**
 * speedstep_activate - activate SpeedStep control in the chipset
 *
 *   Tries to activate the SpeedStep status and control रेजिस्टरs.
 * Returns -EINVAL on an unsupported chipset, and zero on success.
 */
अटल पूर्णांक speedstep_activate(व्योम)
अणु
	u16 value = 0;

	अगर (!speedstep_chipset_dev)
		वापस -EINVAL;

	pci_पढ़ो_config_word(speedstep_chipset_dev, 0x00A0, &value);
	अगर (!(value & 0x08)) अणु
		value |= 0x08;
		pr_debug("activating SpeedStep (TM) registers\n");
		pci_ग_लिखो_config_word(speedstep_chipset_dev, 0x00A0, value);
	पूर्ण

	वापस 0;
पूर्ण


/**
 * speedstep_detect_chipset - detect the Southbridge which contains SpeedStep logic
 *
 *   Detects ICH2-M, ICH3-M and ICH4-M so far. The pci_dev poपूर्णांकs to
 * the LPC bridge / PM module which contains all घातer-management
 * functions. Returns the SPEEDSTEP_CHIPSET_-number क्रम the detected
 * chipset, or zero on failure.
 */
अटल अचिन्हित पूर्णांक speedstep_detect_chipset(व्योम)
अणु
	speedstep_chipset_dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			      PCI_DEVICE_ID_INTEL_82801DB_12,
			      PCI_ANY_ID, PCI_ANY_ID,
			      शून्य);
	अगर (speedstep_chipset_dev)
		वापस 4; /* 4-M */

	speedstep_chipset_dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			      PCI_DEVICE_ID_INTEL_82801CA_12,
			      PCI_ANY_ID, PCI_ANY_ID,
			      शून्य);
	अगर (speedstep_chipset_dev)
		वापस 3; /* 3-M */


	speedstep_chipset_dev = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			      PCI_DEVICE_ID_INTEL_82801BA_10,
			      PCI_ANY_ID, PCI_ANY_ID,
			      शून्य);
	अगर (speedstep_chipset_dev) अणु
		/* speedstep.c causes lockups on Dell Inspirons 8000 and
		 * 8100 which use a pretty old revision of the 82815
		 * host bridge. Abort on these प्रणालीs.
		 */
		काष्ठा pci_dev *hostbridge;

		hostbridge  = pci_get_subsys(PCI_VENDOR_ID_INTEL,
			      PCI_DEVICE_ID_INTEL_82815_MC,
			      PCI_ANY_ID, PCI_ANY_ID,
			      शून्य);

		अगर (!hostbridge)
			वापस 2; /* 2-M */

		अगर (hostbridge->revision < 5) अणु
			pr_debug("hostbridge does not support speedstep\n");
			speedstep_chipset_dev = शून्य;
			pci_dev_put(hostbridge);
			वापस 0;
		पूर्ण

		pci_dev_put(hostbridge);
		वापस 2; /* 2-M */
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम get_freq_data(व्योम *_speed)
अणु
	अचिन्हित पूर्णांक *speed = _speed;

	*speed = speedstep_get_frequency(speedstep_processor);
पूर्ण

अटल अचिन्हित पूर्णांक speedstep_get(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक speed;

	/* You're supposed to ensure CPU is online. */
	BUG_ON(smp_call_function_single(cpu, get_freq_data, &speed, 1));

	pr_debug("detected %u kHz as current frequency\n", speed);
	वापस speed;
पूर्ण

/**
 * speedstep_target - set a new CPUFreq policy
 * @policy: new policy
 * @index: index of target frequency
 *
 * Sets a new CPUFreq policy.
 */
अटल पूर्णांक speedstep_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक policy_cpu;

	policy_cpu = cpumask_any_and(policy->cpus, cpu_online_mask);

	smp_call_function_single(policy_cpu, _speedstep_set_state, &index,
				 true);

	वापस 0;
पूर्ण


काष्ठा get_freqs अणु
	काष्ठा cpufreq_policy *policy;
	पूर्णांक ret;
पूर्ण;

अटल व्योम get_freqs_on_cpu(व्योम *_get_freqs)
अणु
	काष्ठा get_freqs *get_freqs = _get_freqs;

	get_freqs->ret =
		speedstep_get_freqs(speedstep_processor,
			    &speedstep_freqs[SPEEDSTEP_LOW].frequency,
			    &speedstep_freqs[SPEEDSTEP_HIGH].frequency,
			    &get_freqs->policy->cpuinfo.transition_latency,
			    &speedstep_set_state);
पूर्ण

अटल पूर्णांक speedstep_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक policy_cpu;
	काष्ठा get_freqs gf;

	/* only run on CPU to be set, or on its sibling */
#अगर_घोषित CONFIG_SMP
	cpumask_copy(policy->cpus, topology_sibling_cpumask(policy->cpu));
#पूर्ण_अगर
	policy_cpu = cpumask_any_and(policy->cpus, cpu_online_mask);

	/* detect low and high frequency and transition latency */
	gf.policy = policy;
	smp_call_function_single(policy_cpu, get_freqs_on_cpu, &gf, 1);
	अगर (gf.ret)
		वापस gf.ret;

	policy->freq_table = speedstep_freqs;

	वापस 0;
पूर्ण


अटल काष्ठा cpufreq_driver speedstep_driver = अणु
	.name	= "speedstep-ich",
	.verअगरy	= cpufreq_generic_frequency_table_verअगरy,
	.target_index = speedstep_target,
	.init	= speedstep_cpu_init,
	.get	= speedstep_get,
	.attr	= cpufreq_generic_attr,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id ss_smi_ids[] = अणु
	X86_MATCH_VENDOR_FAM_MODEL(INTEL,  6, 0x8, 0),
	X86_MATCH_VENDOR_FAM_MODEL(INTEL,  6, 0xb, 0),
	X86_MATCH_VENDOR_FAM_MODEL(INTEL, 15, 0x2, 0),
	अणुपूर्ण
पूर्ण;

/**
 * speedstep_init - initializes the SpeedStep CPUFreq driver
 *
 *   Initializes the SpeedStep support. Returns -ENODEV on unsupported
 * devices, -EINVAL on problems during initiatization, and zero on
 * success.
 */
अटल पूर्णांक __init speedstep_init(व्योम)
अणु
	अगर (!x86_match_cpu(ss_smi_ids))
		वापस -ENODEV;

	/* detect processor */
	speedstep_processor = speedstep_detect_processor();
	अगर (!speedstep_processor) अणु
		pr_debug("Intel(R) SpeedStep(TM) capable processor "
				"not found\n");
		वापस -ENODEV;
	पूर्ण

	/* detect chipset */
	अगर (!speedstep_detect_chipset()) अणु
		pr_debug("Intel(R) SpeedStep(TM) for this chipset not "
				"(yet) available.\n");
		वापस -ENODEV;
	पूर्ण

	/* activate speedstep support */
	अगर (speedstep_activate()) अणु
		pci_dev_put(speedstep_chipset_dev);
		वापस -EINVAL;
	पूर्ण

	अगर (speedstep_find_रेजिस्टर())
		वापस -ENODEV;

	वापस cpufreq_रेजिस्टर_driver(&speedstep_driver);
पूर्ण


/**
 * speedstep_निकास - unरेजिस्टरs SpeedStep support
 *
 *   Unरेजिस्टरs SpeedStep support.
 */
अटल व्योम __निकास speedstep_निकास(व्योम)
अणु
	pci_dev_put(speedstep_chipset_dev);
	cpufreq_unरेजिस्टर_driver(&speedstep_driver);
पूर्ण


MODULE_AUTHOR("Dave Jones, Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("Speedstep driver for Intel mobile processors on chipsets "
		"with ICH-M southbridges.");
MODULE_LICENSE("GPL");

module_init(speedstep_init);
module_निकास(speedstep_निकास);

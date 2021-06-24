<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel SpeedStep SMI driver.
 *
 * (C) 2003  Hiroshi Miura <miura@da-cha.org>
 */


/*********************************************************************
 *                        SPEEDSTEP - DEFINITIONS                    *
 *********************************************************************/

#घोषणा pr_fmt(fmt) "cpufreq: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/ist.h>
#समावेश <यंत्र/cpu_device_id.h>

#समावेश "speedstep-lib.h"

/* speedstep प्रणाली management पूर्णांकerface port/command.
 *
 * These parameters are got from IST-SMI BIOS call.
 * If user gives it, these are used.
 *
 */
अटल पूर्णांक smi_port;
अटल पूर्णांक smi_cmd;
अटल अचिन्हित पूर्णांक smi_sig;

/* info about the processor */
अटल क्रमागत speedstep_processor speedstep_processor;

/*
 * There are only two frequency states क्रम each processor. Values
 * are in kHz क्रम the समय being.
 */
अटल काष्ठा cpufreq_frequency_table speedstep_freqs[] = अणु
	अणु0, SPEEDSTEP_HIGH,	0पूर्ण,
	अणु0, SPEEDSTEP_LOW,	0पूर्ण,
	अणु0, 0,			CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

#घोषणा GET_SPEEDSTEP_OWNER 0
#घोषणा GET_SPEEDSTEP_STATE 1
#घोषणा SET_SPEEDSTEP_STATE 2
#घोषणा GET_SPEEDSTEP_FREQS 4

/* how often shall the SMI call be tried अगर it failed, e.g. because
 * of DMA activity going on? */
#घोषणा SMI_TRIES 5

/**
 * speedstep_smi_ownership
 */
अटल पूर्णांक speedstep_smi_ownership(व्योम)
अणु
	u32 command, result, magic, dummy;
	u32 function = GET_SPEEDSTEP_OWNER;
	अचिन्हित अक्षर magic_data[] = "Copyright (c) 1999 Intel Corporation";

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);
	magic = virt_to_phys(magic_data);

	pr_debug("trying to obtain ownership with command %x at port %x\n",
			command, smi_port);

	__यंत्र__ __अस्थिर__(
		"push %%ebp\n"
		"out %%al, (%%dx)\n"
		"pop %%ebp\n"
		: "=D" (result),
		  "=a" (dummy), "=b" (dummy), "=c" (dummy), "=d" (dummy),
		  "=S" (dummy)
		: "a" (command), "b" (function), "c" (0), "d" (smi_port),
		  "D" (0), "S" (magic)
		: "memory"
	);

	pr_debug("result is %x\n", result);

	वापस result;
पूर्ण

/**
 * speedstep_smi_get_freqs - get SpeedStep preferred & current freq.
 * @low: the low frequency value is placed here
 * @high: the high frequency value is placed here
 *
 * Only available on later SpeedStep-enabled प्रणालीs, वापसs false results or
 * even hangs [cf. bugme.osdl.org # 1422] on earlier प्रणालीs. Empirical testing
 * shows that the latter occurs अगर !(ist_info.event & 0xFFFF).
 */
अटल पूर्णांक speedstep_smi_get_freqs(अचिन्हित पूर्णांक *low, अचिन्हित पूर्णांक *high)
अणु
	u32 command, result = 0, edi, high_mhz, low_mhz, dummy;
	u32 state = 0;
	u32 function = GET_SPEEDSTEP_FREQS;

	अगर (!(ist_info.event & 0xFFFF)) अणु
		pr_debug("bug #1422 -- can't read freqs from BIOS\n");
		वापस -ENODEV;
	पूर्ण

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);

	pr_debug("trying to determine frequencies with command %x at port %x\n",
			command, smi_port);

	__यंत्र__ __अस्थिर__(
		"push %%ebp\n"
		"out %%al, (%%dx)\n"
		"pop %%ebp"
		: "=a" (result),
		  "=b" (high_mhz),
		  "=c" (low_mhz),
		  "=d" (state), "=D" (edi), "=S" (dummy)
		: "a" (command),
		  "b" (function),
		  "c" (state),
		  "d" (smi_port), "S" (0), "D" (0)
	);

	pr_debug("result %x, low_freq %u, high_freq %u\n",
			result, low_mhz, high_mhz);

	/* पात अगर results are obviously incorrect... */
	अगर ((high_mhz + low_mhz) < 600)
		वापस -EINVAL;

	*high = high_mhz * 1000;
	*low  = low_mhz  * 1000;

	वापस result;
पूर्ण

/**
 * speedstep_set_state - set the SpeedStep state
 * @state: new processor frequency state (SPEEDSTEP_LOW or SPEEDSTEP_HIGH)
 *
 */
अटल व्योम speedstep_set_state(अचिन्हित पूर्णांक state)
अणु
	अचिन्हित पूर्णांक result = 0, command, new_state, dummy;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक function = SET_SPEEDSTEP_STATE;
	अचिन्हित पूर्णांक retry = 0;

	अगर (state > 0x1)
		वापस;

	/* Disable IRQs */
	preempt_disable();
	local_irq_save(flags);

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);

	pr_debug("trying to set frequency to state %u "
		"with command %x at port %x\n",
		state, command, smi_port);

	करो अणु
		अगर (retry) अणु
			/*
			 * We need to enable पूर्णांकerrupts, otherwise the blockage
			 * won't resolve.
			 *
			 * We disable preemption so that other processes करोn't
			 * run. If other processes were running, they could
			 * submit more DMA requests, making the blockage worse.
			 */
			pr_debug("retry %u, previous result %u, waiting...\n",
					retry, result);
			local_irq_enable();
			mdelay(retry * 50);
			local_irq_disable();
		पूर्ण
		retry++;
		__यंत्र__ __अस्थिर__(
			"push %%ebp\n"
			"out %%al, (%%dx)\n"
			"pop %%ebp"
			: "=b" (new_state), "=D" (result),
			  "=c" (dummy), "=a" (dummy),
			  "=d" (dummy), "=S" (dummy)
			: "a" (command), "b" (function), "c" (state),
			  "d" (smi_port), "S" (0), "D" (0)
			);
	पूर्ण जबतक ((new_state != state) && (retry <= SMI_TRIES));

	/* enable IRQs */
	local_irq_restore(flags);
	preempt_enable();

	अगर (new_state == state)
		pr_debug("change to %u MHz succeeded after %u tries "
			"with result %u\n",
			(speedstep_freqs[new_state].frequency / 1000),
			retry, result);
	अन्यथा
		pr_err("change to state %u failed with new_state %u and result %u\n",
		       state, new_state, result);

	वापस;
पूर्ण


/**
 * speedstep_target - set a new CPUFreq policy
 * @policy: new policy
 * @index: index of new freq
 *
 * Sets a new CPUFreq policy/freq.
 */
अटल पूर्णांक speedstep_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	speedstep_set_state(index);

	वापस 0;
पूर्ण


अटल पूर्णांक speedstep_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक *low, *high;

	/* capability check */
	अगर (policy->cpu != 0)
		वापस -ENODEV;

	result = speedstep_smi_ownership();
	अगर (result) अणु
		pr_debug("fails in acquiring ownership of a SMI interface.\n");
		वापस -EINVAL;
	पूर्ण

	/* detect low and high frequency */
	low = &speedstep_freqs[SPEEDSTEP_LOW].frequency;
	high = &speedstep_freqs[SPEEDSTEP_HIGH].frequency;

	result = speedstep_smi_get_freqs(low, high);
	अगर (result) अणु
		/* fall back to speedstep_lib.c dection mechanism:
		 * try both states out */
		pr_debug("could not detect low and high frequencies "
				"by SMI call.\n");
		result = speedstep_get_freqs(speedstep_processor,
				low, high,
				शून्य,
				&speedstep_set_state);

		अगर (result) अणु
			pr_debug("could not detect two different speeds"
					" -- aborting.\n");
			वापस result;
		पूर्ण अन्यथा
			pr_debug("workaround worked.\n");
	पूर्ण

	policy->freq_table = speedstep_freqs;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक speedstep_get(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpu)
		वापस -ENODEV;
	वापस speedstep_get_frequency(speedstep_processor);
पूर्ण


अटल पूर्णांक speedstep_resume(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक result = speedstep_smi_ownership();

	अगर (result)
		pr_debug("fails in re-acquiring ownership of a SMI interface.\n");

	वापस result;
पूर्ण

अटल काष्ठा cpufreq_driver speedstep_driver = अणु
	.name		= "speedstep-smi",
	.flags		= CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= speedstep_target,
	.init		= speedstep_cpu_init,
	.get		= speedstep_get,
	.resume		= speedstep_resume,
	.attr		= cpufreq_generic_attr,
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
 * BIOS, -EINVAL on problems during initiatization, and zero on
 * success.
 */
अटल पूर्णांक __init speedstep_init(व्योम)
अणु
	अगर (!x86_match_cpu(ss_smi_ids))
		वापस -ENODEV;

	speedstep_processor = speedstep_detect_processor();

	चयन (speedstep_processor) अणु
	हाल SPEEDSTEP_CPU_PIII_T:
	हाल SPEEDSTEP_CPU_PIII_C:
	हाल SPEEDSTEP_CPU_PIII_C_EARLY:
		अवरोध;
	शेष:
		speedstep_processor = 0;
	पूर्ण

	अगर (!speedstep_processor) अणु
		pr_debug("No supported Intel CPU detected.\n");
		वापस -ENODEV;
	पूर्ण

	pr_debug("signature:0x%.8x, command:0x%.8x, "
		"event:0x%.8x, perf_level:0x%.8x.\n",
		ist_info.signature, ist_info.command,
		ist_info.event, ist_info.perf_level);

	/* Error अगर no IST-SMI BIOS or no PARM
		 sig= 'ISGE' aka 'Intel Speedstep Gate E' */
	अगर ((ist_info.signature !=  0x47534943) && (
	    (smi_port == 0) || (smi_cmd == 0)))
		वापस -ENODEV;

	अगर (smi_sig == 1)
		smi_sig = 0x47534943;
	अन्यथा
		smi_sig = ist_info.signature;

	/* setup smi_port from MODLULE_PARM or BIOS */
	अगर ((smi_port > 0xff) || (smi_port < 0))
		वापस -EINVAL;
	अन्यथा अगर (smi_port == 0)
		smi_port = ist_info.command & 0xff;

	अगर ((smi_cmd > 0xff) || (smi_cmd < 0))
		वापस -EINVAL;
	अन्यथा अगर (smi_cmd == 0)
		smi_cmd = (ist_info.command >> 16) & 0xff;

	वापस cpufreq_रेजिस्टर_driver(&speedstep_driver);
पूर्ण


/**
 * speedstep_निकास - unरेजिस्टरs SpeedStep support
 *
 *   Unरेजिस्टरs SpeedStep support.
 */
अटल व्योम __निकास speedstep_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&speedstep_driver);
पूर्ण

module_param_hw(smi_port, पूर्णांक, ioport, 0444);
module_param(smi_cmd,  पूर्णांक, 0444);
module_param(smi_sig, uपूर्णांक, 0444);

MODULE_PARM_DESC(smi_port, "Override the BIOS-given IST port with this value "
		"-- Intel's default setting is 0xb2");
MODULE_PARM_DESC(smi_cmd, "Override the BIOS-given IST command with this value "
		"-- Intel's default setting is 0x82");
MODULE_PARM_DESC(smi_sig, "Set to 1 to fake the IST signature when using the "
		"SMI interface.");

MODULE_AUTHOR("Hiroshi Miura");
MODULE_DESCRIPTION("Speedstep driver for IST applet SMI interface.");
MODULE_LICENSE("GPL");

module_init(speedstep_init);
module_निकास(speedstep_निकास);

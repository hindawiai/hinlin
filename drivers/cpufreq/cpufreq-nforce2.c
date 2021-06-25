<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2004-2006  Sebastian Witt <se.witt@gmx.net>
 *
 *  Based upon reverse engineered inक्रमmation
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#घोषणा NFORCE2_XTAL 25
#घोषणा NFORCE2_BOOTFSB 0x48
#घोषणा NFORCE2_PLLENABLE 0xa8
#घोषणा NFORCE2_PLLREG 0xa4
#घोषणा NFORCE2_PLLADR 0xa0
#घोषणा NFORCE2_PLL(mul, भाग) (0x100000 | (mul << 8) | भाग)

#घोषणा NFORCE2_MIN_FSB 50
#घोषणा NFORCE2_SAFE_DISTANCE 50

/* Delay in ms between FSB changes */
/* #घोषणा NFORCE2_DELAY 10 */

/*
 * nक्रमce2_chipset:
 * FSB is changed using the chipset
 */
अटल काष्ठा pci_dev *nक्रमce2_dev;

/* fid:
 * multiplier * 10
 */
अटल पूर्णांक fid;

/* min_fsb, max_fsb:
 * minimum and maximum FSB (= FSB at boot समय)
 */
अटल पूर्णांक min_fsb;
अटल पूर्णांक max_fsb;

MODULE_AUTHOR("Sebastian Witt <se.witt@gmx.net>");
MODULE_DESCRIPTION("nForce2 FSB changing cpufreq driver");
MODULE_LICENSE("GPL");

module_param(fid, पूर्णांक, 0444);
module_param(min_fsb, पूर्णांक, 0444);

MODULE_PARM_DESC(fid, "CPU multiplier to use (11.5 = 115)");
MODULE_PARM_DESC(min_fsb,
		"Minimum FSB to use, if not defined: current FSB - 50");

/**
 * nक्रमce2_calc_fsb - calculate FSB
 * @pll: PLL value
 *
 *   Calculates FSB from PLL value
 */
अटल पूर्णांक nक्रमce2_calc_fsb(पूर्णांक pll)
अणु
	अचिन्हित अक्षर mul, भाग;

	mul = (pll >> 8) & 0xff;
	भाग = pll & 0xff;

	अगर (भाग > 0)
		वापस NFORCE2_XTAL * mul / भाग;

	वापस 0;
पूर्ण

/**
 * nक्रमce2_calc_pll - calculate PLL value
 * @fsb: FSB
 *
 *   Calculate PLL value क्रम given FSB
 */
अटल पूर्णांक nक्रमce2_calc_pll(अचिन्हित पूर्णांक fsb)
अणु
	अचिन्हित अक्षर xmul, xभाग;
	अचिन्हित अक्षर mul = 0, भाग = 0;
	पूर्णांक tried = 0;

	/* Try to calculate multiplier and भागider up to 4 बार */
	जबतक (((mul == 0) || (भाग == 0)) && (tried <= 3)) अणु
		क्रम (xभाग = 2; xभाग <= 0x80; xभाग++)
			क्रम (xmul = 1; xmul <= 0xfe; xmul++)
				अगर (nक्रमce2_calc_fsb(NFORCE2_PLL(xmul, xभाग)) ==
				    fsb + tried) अणु
					mul = xmul;
					भाग = xभाग;
				पूर्ण
		tried++;
	पूर्ण

	अगर ((mul == 0) || (भाग == 0))
		वापस -1;

	वापस NFORCE2_PLL(mul, भाग);
पूर्ण

/**
 * nक्रमce2_ग_लिखो_pll - ग_लिखो PLL value to chipset
 * @pll: PLL value
 *
 *   Writes new FSB PLL value to chipset
 */
अटल व्योम nक्रमce2_ग_लिखो_pll(पूर्णांक pll)
अणु
	पूर्णांक temp;

	/* Set the pll addr. to 0x00 */
	pci_ग_लिखो_config_dword(nक्रमce2_dev, NFORCE2_PLLADR, 0);

	/* Now ग_लिखो the value in all 64 रेजिस्टरs */
	क्रम (temp = 0; temp <= 0x3f; temp++)
		pci_ग_लिखो_config_dword(nक्रमce2_dev, NFORCE2_PLLREG, pll);
पूर्ण

/**
 * nक्रमce2_fsb_पढ़ो - Read FSB
 *
 *   Read FSB from chipset
 *   If bootfsb != 0, वापस FSB at boot-समय
 */
अटल अचिन्हित पूर्णांक nक्रमce2_fsb_पढ़ो(पूर्णांक bootfsb)
अणु
	काष्ठा pci_dev *nक्रमce2_sub5;
	u32 fsb, temp = 0;

	/* Get chipset boot FSB from subdevice 5 (FSB at boot-समय) */
	nक्रमce2_sub5 = pci_get_subsys(PCI_VENDOR_ID_NVIDIA, 0x01EF,
				PCI_ANY_ID, PCI_ANY_ID, शून्य);
	अगर (!nक्रमce2_sub5)
		वापस 0;

	pci_पढ़ो_config_dword(nक्रमce2_sub5, NFORCE2_BOOTFSB, &fsb);
	fsb /= 1000000;

	/* Check अगर PLL रेजिस्टर is alपढ़ोy set */
	pci_पढ़ो_config_byte(nक्रमce2_dev, NFORCE2_PLLENABLE, (u8 *)&temp);

	अगर (bootfsb || !temp)
		वापस fsb;

	/* Use PLL रेजिस्टर FSB value */
	pci_पढ़ो_config_dword(nक्रमce2_dev, NFORCE2_PLLREG, &temp);
	fsb = nक्रमce2_calc_fsb(temp);

	वापस fsb;
पूर्ण

/**
 * nक्रमce2_set_fsb - set new FSB
 * @fsb: New FSB
 *
 *   Sets new FSB
 */
अटल पूर्णांक nक्रमce2_set_fsb(अचिन्हित पूर्णांक fsb)
अणु
	u32 temp = 0;
	अचिन्हित पूर्णांक tfsb;
	पूर्णांक dअगरf;
	पूर्णांक pll = 0;

	अगर ((fsb > max_fsb) || (fsb < NFORCE2_MIN_FSB)) अणु
		pr_err("FSB %d is out of range!\n", fsb);
		वापस -EINVAL;
	पूर्ण

	tfsb = nक्रमce2_fsb_पढ़ो(0);
	अगर (!tfsb) अणु
		pr_err("Error while reading the FSB\n");
		वापस -EINVAL;
	पूर्ण

	/* First ग_लिखो? Then set actual value */
	pci_पढ़ो_config_byte(nक्रमce2_dev, NFORCE2_PLLENABLE, (u8 *)&temp);
	अगर (!temp) अणु
		pll = nक्रमce2_calc_pll(tfsb);

		अगर (pll < 0)
			वापस -EINVAL;

		nक्रमce2_ग_लिखो_pll(pll);
	पूर्ण

	/* Enable ग_लिखो access */
	temp = 0x01;
	pci_ग_लिखो_config_byte(nक्रमce2_dev, NFORCE2_PLLENABLE, (u8)temp);

	dअगरf = tfsb - fsb;

	अगर (!dअगरf)
		वापस 0;

	जबतक ((tfsb != fsb) && (tfsb <= max_fsb) && (tfsb >= min_fsb)) अणु
		अगर (dअगरf < 0)
			tfsb++;
		अन्यथा
			tfsb--;

		/* Calculate the PLL reg. value */
		pll = nक्रमce2_calc_pll(tfsb);
		अगर (pll == -1)
			वापस -EINVAL;

		nक्रमce2_ग_लिखो_pll(pll);
#अगर_घोषित NFORCE2_DELAY
		mdelay(NFORCE2_DELAY);
#पूर्ण_अगर
	पूर्ण

	temp = 0x40;
	pci_ग_लिखो_config_byte(nक्रमce2_dev, NFORCE2_PLLADR, (u8)temp);

	वापस 0;
पूर्ण

/**
 * nक्रमce2_get - get the CPU frequency
 * @cpu: CPU number
 *
 * Returns the CPU frequency
 */
अटल अचिन्हित पूर्णांक nक्रमce2_get(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpu)
		वापस 0;
	वापस nक्रमce2_fsb_पढ़ो(0) * fid * 100;
पूर्ण

/**
 * nक्रमce2_target - set a new CPUFreq policy
 * @policy: new policy
 * @target_freq: the target frequency
 * @relation: how that frequency relates to achieved frequency
 *  (CPUFREQ_RELATION_L or CPUFREQ_RELATION_H)
 *
 * Sets a new CPUFreq policy.
 */
अटल पूर्णांक nक्रमce2_target(काष्ठा cpufreq_policy *policy,
			  अचिन्हित पूर्णांक target_freq, अचिन्हित पूर्णांक relation)
अणु
/*        अचिन्हित दीर्घ         flags; */
	काष्ठा cpufreq_freqs freqs;
	अचिन्हित पूर्णांक target_fsb;

	अगर ((target_freq > policy->max) || (target_freq < policy->min))
		वापस -EINVAL;

	target_fsb = target_freq / (fid * 100);

	freqs.old = nक्रमce2_get(policy->cpu);
	freqs.new = target_fsb * fid * 100;

	अगर (freqs.old == freqs.new)
		वापस 0;

	pr_debug("Old CPU frequency %d kHz, new %d kHz\n",
	       freqs.old, freqs.new);

	cpufreq_freq_transition_begin(policy, &freqs);

	/* Disable IRQs */
	/* local_irq_save(flags); */

	अगर (nक्रमce2_set_fsb(target_fsb) < 0)
		pr_err("Changing FSB to %d failed\n", target_fsb);
	अन्यथा
		pr_debug("Changed FSB successfully to %d\n",
			target_fsb);

	/* Enable IRQs */
	/* local_irq_restore(flags); */

	cpufreq_freq_transition_end(policy, &freqs, 0);

	वापस 0;
पूर्ण

/**
 * nक्रमce2_verअगरy - verअगरies a new CPUFreq policy
 * @policy: new policy
 */
अटल पूर्णांक nक्रमce2_verअगरy(काष्ठा cpufreq_policy_data *policy)
अणु
	अचिन्हित पूर्णांक fsb_pol_max;

	fsb_pol_max = policy->max / (fid * 100);

	अगर (policy->min < (fsb_pol_max * fid * 100))
		policy->max = (fsb_pol_max + 1) * fid * 100;

	cpufreq_verअगरy_within_cpu_limits(policy);
	वापस 0;
पूर्ण

अटल पूर्णांक nक्रमce2_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक fsb;
	अचिन्हित पूर्णांक rfid;

	/* capability check */
	अगर (policy->cpu != 0)
		वापस -ENODEV;

	/* Get current FSB */
	fsb = nक्रमce2_fsb_पढ़ो(0);

	अगर (!fsb)
		वापस -EIO;

	/* FIX: Get FID from CPU */
	अगर (!fid) अणु
		अगर (!cpu_khz) अणु
			pr_warn("cpu_khz not set, can't calculate multiplier!\n");
			वापस -ENODEV;
		पूर्ण

		fid = cpu_khz / (fsb * 100);
		rfid = fid % 5;

		अगर (rfid) अणु
			अगर (rfid > 2)
				fid += 5 - rfid;
			अन्यथा
				fid -= rfid;
		पूर्ण
	पूर्ण

	pr_info("FSB currently at %i MHz, FID %d.%d\n",
		fsb, fid / 10, fid % 10);

	/* Set maximum FSB to FSB at boot समय */
	max_fsb = nक्रमce2_fsb_पढ़ो(1);

	अगर (!max_fsb)
		वापस -EIO;

	अगर (!min_fsb)
		min_fsb = max_fsb - NFORCE2_SAFE_DISTANCE;

	अगर (min_fsb < NFORCE2_MIN_FSB)
		min_fsb = NFORCE2_MIN_FSB;

	/* cpuinfo and शेष policy values */
	policy->min = policy->cpuinfo.min_freq = min_fsb * fid * 100;
	policy->max = policy->cpuinfo.max_freq = max_fsb * fid * 100;

	वापस 0;
पूर्ण

अटल पूर्णांक nक्रमce2_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver nक्रमce2_driver = अणु
	.name = "nforce2",
	.flags = CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING,
	.verअगरy = nक्रमce2_verअगरy,
	.target = nक्रमce2_target,
	.get = nक्रमce2_get,
	.init = nक्रमce2_cpu_init,
	.निकास = nक्रमce2_cpu_निकास,
पूर्ण;

#अगर_घोषित MODULE
अटल स्थिर काष्ठा pci_device_id nक्रमce2_ids[] = अणु
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE2 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, nक्रमce2_ids);
#पूर्ण_अगर

/**
 * nक्रमce2_detect_chipset - detect the Southbridge which contains FSB PLL logic
 *
 * Detects nForce2 A2 and C1 stepping
 *
 */
अटल पूर्णांक nक्रमce2_detect_chipset(व्योम)
अणु
	nक्रमce2_dev = pci_get_subsys(PCI_VENDOR_ID_NVIDIA,
					PCI_DEVICE_ID_NVIDIA_NFORCE2,
					PCI_ANY_ID, PCI_ANY_ID, शून्य);

	अगर (nक्रमce2_dev == शून्य)
		वापस -ENODEV;

	pr_info("Detected nForce2 chipset revision %X\n",
		nक्रमce2_dev->revision);
	pr_info("FSB changing is maybe unstable and can lead to crashes and data loss\n");

	वापस 0;
पूर्ण

/**
 * nक्रमce2_init - initializes the nForce2 CPUFreq driver
 *
 * Initializes the nForce2 FSB support. Returns -ENODEV on unsupported
 * devices, -EINVAL on problems during initialization, and zero on
 * success.
 */
अटल पूर्णांक __init nक्रमce2_init(व्योम)
अणु
	/* TODO: करो we need to detect the processor? */

	/* detect chipset */
	अगर (nक्रमce2_detect_chipset()) अणु
		pr_info("No nForce2 chipset\n");
		वापस -ENODEV;
	पूर्ण

	वापस cpufreq_रेजिस्टर_driver(&nक्रमce2_driver);
पूर्ण

/**
 * nक्रमce2_निकास - unरेजिस्टरs cpufreq module
 *
 *   Unरेजिस्टरs nForce2 FSB change support.
 */
अटल व्योम __निकास nक्रमce2_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&nक्रमce2_driver);
पूर्ण

module_init(nक्रमce2_init);
module_निकास(nक्रमce2_निकास);

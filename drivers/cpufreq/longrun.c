<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2002 - 2003  Dominik Broकरोwski <linux@broकरो.de>
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/समयx.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpu_device_id.h>

अटल काष्ठा cpufreq_driver	दीर्घrun_driver;

/**
 * दीर्घrun_अणुlow,highपूर्ण_freq is needed क्रम the conversion of cpufreq kHz
 * values पूर्णांकo per cent values. In TMTA microcode, the following is valid:
 * perक्रमmance_pctg = (current_freq - low_freq)/(high_freq - low_freq)
 */
अटल अचिन्हित पूर्णांक दीर्घrun_low_freq, दीर्घrun_high_freq;


/**
 * दीर्घrun_get_policy - get the current LongRun policy
 * @policy: काष्ठा cpufreq_policy where current policy is written पूर्णांकo
 *
 * Reads the current LongRun policy by access to MSR_TMTA_LONGRUN_FLAGS
 * and MSR_TMTA_LONGRUN_CTRL
 */
अटल व्योम दीर्घrun_get_policy(काष्ठा cpufreq_policy *policy)
अणु
	u32 msr_lo, msr_hi;

	rdmsr(MSR_TMTA_LONGRUN_FLAGS, msr_lo, msr_hi);
	pr_debug("longrun flags are %x - %x\n", msr_lo, msr_hi);
	अगर (msr_lo & 0x01)
		policy->policy = CPUFREQ_POLICY_PERFORMANCE;
	अन्यथा
		policy->policy = CPUFREQ_POLICY_POWERSAVE;

	rdmsr(MSR_TMTA_LONGRUN_CTRL, msr_lo, msr_hi);
	pr_debug("longrun ctrl is %x - %x\n", msr_lo, msr_hi);
	msr_lo &= 0x0000007F;
	msr_hi &= 0x0000007F;

	अगर (दीर्घrun_high_freq <= दीर्घrun_low_freq) अणु
		/* Assume degenerate Longrun table */
		policy->min = policy->max = दीर्घrun_high_freq;
	पूर्ण अन्यथा अणु
		policy->min = दीर्घrun_low_freq + msr_lo *
			((दीर्घrun_high_freq - दीर्घrun_low_freq) / 100);
		policy->max = दीर्घrun_low_freq + msr_hi *
			((दीर्घrun_high_freq - दीर्घrun_low_freq) / 100);
	पूर्ण
	policy->cpu = 0;
पूर्ण


/**
 * दीर्घrun_set_policy - sets a new CPUFreq policy
 * @policy: new policy
 *
 * Sets a new CPUFreq policy on LongRun-capable processors. This function
 * has to be called with cpufreq_driver locked.
 */
अटल पूर्णांक दीर्घrun_set_policy(काष्ठा cpufreq_policy *policy)
अणु
	u32 msr_lo, msr_hi;
	u32 pctg_lo, pctg_hi;

	अगर (!policy)
		वापस -EINVAL;

	अगर (दीर्घrun_high_freq <= दीर्घrun_low_freq) अणु
		/* Assume degenerate Longrun table */
		pctg_lo = pctg_hi = 100;
	पूर्ण अन्यथा अणु
		pctg_lo = (policy->min - दीर्घrun_low_freq) /
			((दीर्घrun_high_freq - दीर्घrun_low_freq) / 100);
		pctg_hi = (policy->max - दीर्घrun_low_freq) /
			((दीर्घrun_high_freq - दीर्घrun_low_freq) / 100);
	पूर्ण

	अगर (pctg_hi > 100)
		pctg_hi = 100;
	अगर (pctg_lo > pctg_hi)
		pctg_lo = pctg_hi;

	/* perक्रमmance or economy mode */
	rdmsr(MSR_TMTA_LONGRUN_FLAGS, msr_lo, msr_hi);
	msr_lo &= 0xFFFFFFFE;
	चयन (policy->policy) अणु
	हाल CPUFREQ_POLICY_PERFORMANCE:
		msr_lo |= 0x00000001;
		अवरोध;
	हाल CPUFREQ_POLICY_POWERSAVE:
		अवरोध;
	पूर्ण
	wrmsr(MSR_TMTA_LONGRUN_FLAGS, msr_lo, msr_hi);

	/* lower and upper boundary */
	rdmsr(MSR_TMTA_LONGRUN_CTRL, msr_lo, msr_hi);
	msr_lo &= 0xFFFFFF80;
	msr_hi &= 0xFFFFFF80;
	msr_lo |= pctg_lo;
	msr_hi |= pctg_hi;
	wrmsr(MSR_TMTA_LONGRUN_CTRL, msr_lo, msr_hi);

	वापस 0;
पूर्ण


/**
 * दीर्घrun_verअगरy_poliy - verअगरies a new CPUFreq policy
 * @policy: the policy to verअगरy
 *
 * Validates a new CPUFreq policy. This function has to be called with
 * cpufreq_driver locked.
 */
अटल पूर्णांक दीर्घrun_verअगरy_policy(काष्ठा cpufreq_policy_data *policy)
अणु
	अगर (!policy)
		वापस -EINVAL;

	policy->cpu = 0;
	cpufreq_verअगरy_within_cpu_limits(policy);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक दीर्घrun_get(अचिन्हित पूर्णांक cpu)
अणु
	u32 eax, ebx, ecx, edx;

	अगर (cpu)
		वापस 0;

	cpuid(0x80860007, &eax, &ebx, &ecx, &edx);
	pr_debug("cpuid eax is %u\n", eax);

	वापस eax * 1000;
पूर्ण

/**
 * दीर्घrun_determine_freqs - determines the lowest and highest possible core frequency
 * @low_freq: an पूर्णांक to put the lowest frequency पूर्णांकo
 * @high_freq: an पूर्णांक to put the highest frequency पूर्णांकo
 *
 * Determines the lowest and highest possible core frequencies on this CPU.
 * This is necessary to calculate the perक्रमmance percentage according to
 * TMTA rules:
 * perक्रमmance_pctg = (target_freq - low_freq)/(high_freq - low_freq)
 */
अटल पूर्णांक दीर्घrun_determine_freqs(अचिन्हित पूर्णांक *low_freq,
						      अचिन्हित पूर्णांक *high_freq)
अणु
	u32 msr_lo, msr_hi;
	u32 save_lo, save_hi;
	u32 eax, ebx, ecx, edx;
	u32 try_hi;
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);

	अगर (!low_freq || !high_freq)
		वापस -EINVAL;

	अगर (cpu_has(c, X86_FEATURE_LRTI)) अणु
		/* अगर the LongRun Table Interface is present, the
		 * detection is a bit easier:
		 * For minimum frequency, पढ़ो out the maximum
		 * level (msr_hi), ग_लिखो that पूर्णांकo "currently
		 * selected level", and पढ़ो out the frequency.
		 * For maximum frequency, पढ़ो out level zero.
		 */
		/* minimum */
		rdmsr(MSR_TMTA_LRTI_READOUT, msr_lo, msr_hi);
		wrmsr(MSR_TMTA_LRTI_READOUT, msr_hi, msr_hi);
		rdmsr(MSR_TMTA_LRTI_VOLT_MHZ, msr_lo, msr_hi);
		*low_freq = msr_lo * 1000; /* to kHz */

		/* maximum */
		wrmsr(MSR_TMTA_LRTI_READOUT, 0, msr_hi);
		rdmsr(MSR_TMTA_LRTI_VOLT_MHZ, msr_lo, msr_hi);
		*high_freq = msr_lo * 1000; /* to kHz */

		pr_debug("longrun table interface told %u - %u kHz\n",
				*low_freq, *high_freq);

		अगर (*low_freq > *high_freq)
			*low_freq = *high_freq;
		वापस 0;
	पूर्ण

	/* set the upper border to the value determined during TSC init */
	*high_freq = (cpu_khz / 1000);
	*high_freq = *high_freq * 1000;
	pr_debug("high frequency is %u kHz\n", *high_freq);

	/* get current borders */
	rdmsr(MSR_TMTA_LONGRUN_CTRL, msr_lo, msr_hi);
	save_lo = msr_lo & 0x0000007F;
	save_hi = msr_hi & 0x0000007F;

	/* अगर current perf_pctg is larger than 90%, we need to decrease the
	 * upper limit to make the calculation more accurate.
	 */
	cpuid(0x80860007, &eax, &ebx, &ecx, &edx);
	/* try decreasing in 10% steps, some processors react only
	 * on some barrier values */
	क्रम (try_hi = 80; try_hi > 0 && ecx > 90; try_hi -= 10) अणु
		/* set to 0 to try_hi perf_pctg */
		msr_lo &= 0xFFFFFF80;
		msr_hi &= 0xFFFFFF80;
		msr_hi |= try_hi;
		wrmsr(MSR_TMTA_LONGRUN_CTRL, msr_lo, msr_hi);

		/* पढ़ो out current core MHz and current perf_pctg */
		cpuid(0x80860007, &eax, &ebx, &ecx, &edx);

		/* restore values */
		wrmsr(MSR_TMTA_LONGRUN_CTRL, save_lo, save_hi);
	पूर्ण
	pr_debug("percentage is %u %%, freq is %u MHz\n", ecx, eax);

	/* perक्रमmance_pctg = (current_freq - low_freq)/(high_freq - low_freq)
	 * eqals
	 * low_freq * (1 - perf_pctg) = (cur_freq - high_freq * perf_pctg)
	 *
	 * high_freq * perf_pctg is stored tempoarily पूर्णांकo "ebx".
	 */
	ebx = (((cpu_khz / 1000) * ecx) / 100); /* to MHz */

	अगर ((ecx > 95) || (ecx == 0) || (eax < ebx))
		वापस -EIO;

	edx = ((eax - ebx) * 100) / (100 - ecx);
	*low_freq = edx * 1000; /* back to kHz */

	pr_debug("low frequency is %u kHz\n", *low_freq);

	अगर (*low_freq > *high_freq)
		*low_freq = *high_freq;

	वापस 0;
पूर्ण


अटल पूर्णांक दीर्घrun_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक result = 0;

	/* capability check */
	अगर (policy->cpu != 0)
		वापस -ENODEV;

	/* detect low and high frequency */
	result = दीर्घrun_determine_freqs(&दीर्घrun_low_freq, &दीर्घrun_high_freq);
	अगर (result)
		वापस result;

	/* cpuinfo and शेष policy values */
	policy->cpuinfo.min_freq = दीर्घrun_low_freq;
	policy->cpuinfo.max_freq = दीर्घrun_high_freq;
	दीर्घrun_get_policy(policy);

	वापस 0;
पूर्ण


अटल काष्ठा cpufreq_driver दीर्घrun_driver = अणु
	.flags		= CPUFREQ_CONST_LOOPS,
	.verअगरy		= दीर्घrun_verअगरy_policy,
	.setpolicy	= दीर्घrun_set_policy,
	.get		= दीर्घrun_get,
	.init		= दीर्घrun_cpu_init,
	.name		= "longrun",
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id दीर्घrun_ids[] = अणु
	X86_MATCH_VENDOR_FEATURE(TRANSMETA, X86_FEATURE_LONGRUN, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, दीर्घrun_ids);

/**
 * दीर्घrun_init - initializes the Transmeta Crusoe LongRun CPUFreq driver
 *
 * Initializes the LongRun support.
 */
अटल पूर्णांक __init दीर्घrun_init(व्योम)
अणु
	अगर (!x86_match_cpu(दीर्घrun_ids))
		वापस -ENODEV;
	वापस cpufreq_रेजिस्टर_driver(&दीर्घrun_driver);
पूर्ण


/**
 * दीर्घrun_निकास - unरेजिस्टरs LongRun support
 */
अटल व्योम __निकास दीर्घrun_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&दीर्घrun_driver);
पूर्ण


MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("LongRun driver for Transmeta Crusoe and "
		"Efficeon processors.");
MODULE_LICENSE("GPL");

module_init(दीर्घrun_init);
module_निकास(दीर्घrun_निकास);

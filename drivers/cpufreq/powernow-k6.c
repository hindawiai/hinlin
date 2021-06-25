<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  This file was based upon code in Powertweak Linux (http://घातertweak.sf.net)
 *  (C) 2000-2003  Dave Jones, Arjan van de Ven, Janne Pथअnkथअlथअ,
 *                 Dominik Broकरोwski.
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/msr.h>

#घोषणा POWERNOW_IOPORT 0xfff0          /* it करोesn't matter where, as दीर्घ
					   as it is unused */

अटल अचिन्हित पूर्णांक                     busfreq;   /* FSB, in 10 kHz */
अटल अचिन्हित पूर्णांक                     max_multiplier;

अटल अचिन्हित पूर्णांक			param_busfreq = 0;
अटल अचिन्हित पूर्णांक			param_max_multiplier = 0;

module_param_named(max_multiplier, param_max_multiplier, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_multiplier, "Maximum multiplier (allowed values: 20 30 35 40 45 50 55 60)");

module_param_named(bus_frequency, param_busfreq, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(bus_frequency, "Bus frequency in kHz");

/* Clock ratio multiplied by 10 - see table 27 in AMD#23446 */
अटल काष्ठा cpufreq_frequency_table घड़ी_ratio[] = अणु
	अणु0, 60,  /* 110 -> 6.0x */ 0पूर्ण,
	अणु0, 55,  /* 011 -> 5.5x */ 0पूर्ण,
	अणु0, 50,  /* 001 -> 5.0x */ 0पूर्ण,
	अणु0, 45,  /* 000 -> 4.5x */ 0पूर्ण,
	अणु0, 40,  /* 010 -> 4.0x */ 0पूर्ण,
	अणु0, 35,  /* 111 -> 3.5x */ 0पूर्ण,
	अणु0, 30,  /* 101 -> 3.0x */ 0पूर्ण,
	अणु0, 20,  /* 100 -> 2.0x */ 0पूर्ण,
	अणु0, 0, CPUFREQ_TABLE_ENDपूर्ण
पूर्ण;

अटल स्थिर u8 index_to_रेजिस्टर[8] = अणु 6, 3, 1, 0, 2, 7, 5, 4 पूर्ण;
अटल स्थिर u8 रेजिस्टर_to_index[8] = अणु 3, 2, 4, 1, 7, 6, 0, 5 पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित freq;
	अचिन्हित mult;
पूर्ण usual_frequency_table[] = अणु
	अणु 350000, 35 पूर्ण,	// 100   * 3.5
	अणु 400000, 40 पूर्ण,	// 100   * 4
	अणु 450000, 45 पूर्ण, // 100   * 4.5
	अणु 475000, 50 पूर्ण, //  95   * 5
	अणु 500000, 50 पूर्ण, // 100   * 5
	अणु 506250, 45 पूर्ण, // 112.5 * 4.5
	अणु 533500, 55 पूर्ण, //  97   * 5.5
	अणु 550000, 55 पूर्ण, // 100   * 5.5
	अणु 562500, 50 पूर्ण, // 112.5 * 5
	अणु 570000, 60 पूर्ण, //  95   * 6
	अणु 600000, 60 पूर्ण, // 100   * 6
	अणु 618750, 55 पूर्ण, // 112.5 * 5.5
	अणु 660000, 55 पूर्ण, // 120   * 5.5
	अणु 675000, 60 पूर्ण, // 112.5 * 6
	अणु 720000, 60 पूर्ण, // 120   * 6
पूर्ण;

#घोषणा FREQ_RANGE		3000

/**
 * घातernow_k6_get_cpu_multiplier - वापसs the current FSB multiplier
 *
 * Returns the current setting of the frequency multiplier. Core घड़ी
 * speed is frequency of the Front-Side Bus multiplied with this value.
 */
अटल पूर्णांक घातernow_k6_get_cpu_multiplier(व्योम)
अणु
	अचिन्हित दीर्घ invalue = 0;
	u32 msrval;

	local_irq_disable();

	msrval = POWERNOW_IOPORT + 0x1;
	wrmsr(MSR_K6_EPMR, msrval, 0); /* enable the PowerNow port */
	invalue = inl(POWERNOW_IOPORT + 0x8);
	msrval = POWERNOW_IOPORT + 0x0;
	wrmsr(MSR_K6_EPMR, msrval, 0); /* disable it again */

	local_irq_enable();

	वापस घड़ी_ratio[रेजिस्टर_to_index[(invalue >> 5)&7]].driver_data;
पूर्ण

अटल व्योम घातernow_k6_set_cpu_multiplier(अचिन्हित पूर्णांक best_i)
अणु
	अचिन्हित दीर्घ outvalue, invalue;
	अचिन्हित दीर्घ msrval;
	अचिन्हित दीर्घ cr0;

	/* we now need to transक्रमm best_i to the BVC क्रमmat, see AMD#23446 */

	/*
	 * The processor करोesn't respond to inquiry cycles जबतक changing the
	 * frequency, so we must disable cache.
	 */
	local_irq_disable();
	cr0 = पढ़ो_cr0();
	ग_लिखो_cr0(cr0 | X86_CR0_CD);
	wbinvd();

	outvalue = (1<<12) | (1<<10) | (1<<9) | (index_to_रेजिस्टर[best_i]<<5);

	msrval = POWERNOW_IOPORT + 0x1;
	wrmsr(MSR_K6_EPMR, msrval, 0); /* enable the PowerNow port */
	invalue = inl(POWERNOW_IOPORT + 0x8);
	invalue = invalue & 0x1f;
	outvalue = outvalue | invalue;
	outl(outvalue, (POWERNOW_IOPORT + 0x8));
	msrval = POWERNOW_IOPORT + 0x0;
	wrmsr(MSR_K6_EPMR, msrval, 0); /* disable it again */

	ग_लिखो_cr0(cr0);
	local_irq_enable();
पूर्ण

/**
 * घातernow_k6_target - set the PowerNow! multiplier
 * @best_i: घड़ी_ratio[best_i] is the target multiplier
 *
 *   Tries to change the PowerNow! multiplier
 */
अटल पूर्णांक घातernow_k6_target(काष्ठा cpufreq_policy *policy,
		अचिन्हित पूर्णांक best_i)
अणु

	अगर (घड़ी_ratio[best_i].driver_data > max_multiplier) अणु
		pr_err("invalid target frequency\n");
		वापस -EINVAL;
	पूर्ण

	घातernow_k6_set_cpu_multiplier(best_i);

	वापस 0;
पूर्ण

अटल पूर्णांक घातernow_k6_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक i, f;
	अचिन्हित khz;

	अगर (policy->cpu != 0)
		वापस -ENODEV;

	max_multiplier = 0;
	khz = cpu_khz;
	क्रम (i = 0; i < ARRAY_SIZE(usual_frequency_table); i++) अणु
		अगर (khz >= usual_frequency_table[i].freq - FREQ_RANGE &&
		    khz <= usual_frequency_table[i].freq + FREQ_RANGE) अणु
			khz = usual_frequency_table[i].freq;
			max_multiplier = usual_frequency_table[i].mult;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (param_max_multiplier) अणु
		cpufreq_क्रम_each_entry(pos, घड़ी_ratio)
			अगर (pos->driver_data == param_max_multiplier) अणु
				max_multiplier = param_max_multiplier;
				जाओ have_max_multiplier;
			पूर्ण
		pr_err("invalid max_multiplier parameter, valid parameters 20, 30, 35, 40, 45, 50, 55, 60\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!max_multiplier) अणु
		pr_warn("unknown frequency %u, cannot determine current multiplier\n",
			khz);
		pr_warn("use module parameters max_multiplier and bus_frequency\n");
		वापस -EOPNOTSUPP;
	पूर्ण

have_max_multiplier:
	param_max_multiplier = max_multiplier;

	अगर (param_busfreq) अणु
		अगर (param_busfreq >= 50000 && param_busfreq <= 150000) अणु
			busfreq = param_busfreq / 10;
			जाओ have_busfreq;
		पूर्ण
		pr_err("invalid bus_frequency parameter, allowed range 50000 - 150000 kHz\n");
		वापस -EINVAL;
	पूर्ण

	busfreq = khz / max_multiplier;
have_busfreq:
	param_busfreq = busfreq * 10;

	/* table init */
	cpufreq_क्रम_each_entry(pos, घड़ी_ratio) अणु
		f = pos->driver_data;
		अगर (f > max_multiplier)
			pos->frequency = CPUFREQ_ENTRY_INVALID;
		अन्यथा
			pos->frequency = busfreq * f;
	पूर्ण

	/* cpuinfo and शेष policy values */
	policy->cpuinfo.transition_latency = 500000;
	policy->freq_table = घड़ी_ratio;

	वापस 0;
पूर्ण


अटल पूर्णांक घातernow_k6_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; (घड़ी_ratio[i].frequency != CPUFREQ_TABLE_END); i++) अणु
		अगर (घड़ी_ratio[i].driver_data == max_multiplier) अणु
			काष्ठा cpufreq_freqs freqs;

			freqs.old = policy->cur;
			freqs.new = घड़ी_ratio[i].frequency;
			freqs.flags = 0;

			cpufreq_freq_transition_begin(policy, &freqs);
			घातernow_k6_target(policy, i);
			cpufreq_freq_transition_end(policy, &freqs, 0);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक घातernow_k6_get(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक ret;
	ret = (busfreq * घातernow_k6_get_cpu_multiplier());
	वापस ret;
पूर्ण

अटल काष्ठा cpufreq_driver घातernow_k6_driver = अणु
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= घातernow_k6_target,
	.init		= घातernow_k6_cpu_init,
	.निकास		= घातernow_k6_cpu_निकास,
	.get		= घातernow_k6_get,
	.name		= "powernow-k6",
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id घातernow_k6_ids[] = अणु
	X86_MATCH_VENDOR_FAM_MODEL(AMD, 5, 12, शून्य),
	X86_MATCH_VENDOR_FAM_MODEL(AMD, 5, 13, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, घातernow_k6_ids);

/**
 * घातernow_k6_init - initializes the k6 PowerNow! CPUFreq driver
 *
 *   Initializes the K6 PowerNow! support. Returns -ENODEV on unsupported
 * devices, -EINVAL or -ENOMEM on problems during initiatization, and zero
 * on success.
 */
अटल पूर्णांक __init घातernow_k6_init(व्योम)
अणु
	अगर (!x86_match_cpu(घातernow_k6_ids))
		वापस -ENODEV;

	अगर (!request_region(POWERNOW_IOPORT, 16, "PowerNow!")) अणु
		pr_info("PowerNow IOPORT region already used\n");
		वापस -EIO;
	पूर्ण

	अगर (cpufreq_रेजिस्टर_driver(&घातernow_k6_driver)) अणु
		release_region(POWERNOW_IOPORT, 16);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * घातernow_k6_निकास - unरेजिस्टरs AMD K6-2+/3+ PowerNow! support
 *
 *   Unरेजिस्टरs AMD K6-2+ / K6-3+ PowerNow! support.
 */
अटल व्योम __निकास घातernow_k6_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&घातernow_k6_driver);
	release_region(POWERNOW_IOPORT, 16);
पूर्ण


MODULE_AUTHOR("Arjan van de Ven, Dave Jones, "
		"Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("PowerNow! driver for AMD K6-2+ / K6-3+ processors.");
MODULE_LICENSE("GPL");

module_init(घातernow_k6_init);
module_निकास(घातernow_k6_निकास);

<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007 by Ralf Baechle
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/समय.स>

अटल u64 c0_hpt_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस पढ़ो_c0_count();
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_mips = अणु
	.name		= "MIPS",
	.पढ़ो		= c0_hpt_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u64 __maybe_unused notrace r4k_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस पढ़ो_c0_count();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rdhwr_count(व्योम)
अणु
	अचिन्हित पूर्णांक count;

	__यंत्र__ __अस्थिर__(
	"	.set push\n"
	"	.set mips32r2\n"
	"	rdhwr	%0, $2\n"
	"	.set pop\n"
	: "=r" (count));

	वापस count;
पूर्ण

अटल bool rdhwr_count_usable(व्योम)
अणु
	अचिन्हित पूर्णांक prev, curr, i;

	/*
	 * Older QEMUs have a broken implementation of RDHWR क्रम the CP0 count
	 * which always वापसs a स्थिरant value. Try to identअगरy this and करोn't
	 * use it in the VDSO अगर it is broken. This workaround can be हटाओd
	 * once the fix has been in QEMU stable क्रम a reasonable amount of समय.
	 */
	क्रम (i = 0, prev = rdhwr_count(); i < 100; i++) अणु
		curr = rdhwr_count();

		अगर (curr != prev)
			वापस true;

		prev = curr;
	पूर्ण

	pr_warn("Not using R4K clocksource in VDSO due to broken RDHWR\n");
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ

अटल bool __पढ़ो_mostly r4k_घड़ी_unstable;

अटल व्योम r4k_घड़ीsource_unstable(अक्षर *reason)
अणु
	अगर (r4k_घड़ी_unstable)
		वापस;

	r4k_घड़ी_unstable = true;

	pr_info("R4K timer is unstable due to %s\n", reason);

	घड़ीsource_mark_unstable(&घड़ीsource_mips);
पूर्ण

अटल पूर्णांक r4k_cpufreq_callback(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ val, व्योम *data)
अणु
	अगर (val == CPUFREQ_POSTCHANGE)
		r4k_घड़ीsource_unstable("CPU frequency change");

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block r4k_cpufreq_notअगरier = अणु
	.notअगरier_call  = r4k_cpufreq_callback,
पूर्ण;

अटल पूर्णांक __init r4k_रेजिस्टर_cpufreq_notअगरier(व्योम)
अणु
	वापस cpufreq_रेजिस्टर_notअगरier(&r4k_cpufreq_notअगरier,
					 CPUFREQ_TRANSITION_NOTIFIER);

पूर्ण
core_initcall(r4k_रेजिस्टर_cpufreq_notअगरier);

#पूर्ण_अगर /* !CONFIG_CPU_FREQ */

पूर्णांक __init init_r4k_घड़ीsource(व्योम)
अणु
	अगर (!cpu_has_counter || !mips_hpt_frequency)
		वापस -ENXIO;

	/* Calculate a somewhat reasonable rating value */
	घड़ीsource_mips.rating = 200 + mips_hpt_frequency / 10000000;

	/*
	 * R2 onwards makes the count accessible to user mode so it can be used
	 * by the VDSO (HWREna is configured by configure_hwrena()).
	 */
	अगर (cpu_has_mips_r2_r6 && rdhwr_count_usable())
		घड़ीsource_mips.vdso_घड़ी_mode = VDSO_CLOCKMODE_R4K;

	घड़ीsource_रेजिस्टर_hz(&घड़ीsource_mips, mips_hpt_frequency);

#अगर_अघोषित CONFIG_CPU_FREQ
	sched_घड़ी_रेजिस्टर(r4k_पढ़ो_sched_घड़ी, 32, mips_hpt_frequency);
#पूर्ण_अगर

	वापस 0;
पूर्ण

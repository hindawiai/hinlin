<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2010,2011       Thomas Renninger <trenn@suse.de>, Novell Inc.
 */

#अगर defined(__i386__) || defined(__x86_64__)

#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <सीमा.स>

#समावेश <cpufreq.h>

#समावेश "helpers/helpers.h"
#समावेश "idle_monitor/cpupower-monitor.h"

#घोषणा MSR_APERF	0xE8
#घोषणा MSR_MPERF	0xE7

#घोषणा RDPRU ".byte 0x0f, 0x01, 0xfd"
#घोषणा RDPRU_ECX_MPERF	0
#घोषणा RDPRU_ECX_APERF	1

#घोषणा MSR_TSC	0x10

#घोषणा MSR_AMD_HWCR 0xc0010015

क्रमागत mperf_id अणु C0 = 0, Cx, AVG_FREQ, MPERF_CSTATE_COUNT पूर्ण;

अटल पूर्णांक mperf_get_count_percent(अचिन्हित पूर्णांक self_id, द्विगुन *percent,
				   अचिन्हित पूर्णांक cpu);
अटल पूर्णांक mperf_get_count_freq(अचिन्हित पूर्णांक id, अचिन्हित दीर्घ दीर्घ *count,
				अचिन्हित पूर्णांक cpu);
अटल काष्ठा बारpec समय_start, समय_end;

अटल cstate_t mperf_cstates[MPERF_CSTATE_COUNT] = अणु
	अणु
		.name			= "C0",
		.desc			= N_("Processor Core not idle"),
		.id			= C0,
		.range			= RANGE_THREAD,
		.get_count_percent	= mperf_get_count_percent,
	पूर्ण,
	अणु
		.name			= "Cx",
		.desc			= N_("Processor Core in an idle state"),
		.id			= Cx,
		.range			= RANGE_THREAD,
		.get_count_percent	= mperf_get_count_percent,
	पूर्ण,

	अणु
		.name			= "Freq",
		.desc			= N_("Average Frequency (including boost) in MHz"),
		.id			= AVG_FREQ,
		.range			= RANGE_THREAD,
		.get_count		= mperf_get_count_freq,
	पूर्ण,
पूर्ण;

क्रमागत MAX_FREQ_MODE अणु MAX_FREQ_SYSFS, MAX_FREQ_TSC_REF पूर्ण;
अटल पूर्णांक max_freq_mode;
/*
 * The max frequency mperf is ticking at (in C0), either retrieved via:
 *   1) calculated after measurements अगर we know TSC ticks at mperf/P0 frequency
 *   2) cpufreq /sys/devices/.../cpu0/cpufreq/cpuinfo_max_freq at init समय
 * 1. Is preferred as it also works without cpufreq subप्रणाली (e.g. on Xen)
 */
अटल अचिन्हित दीर्घ max_frequency;

अटल अचिन्हित दीर्घ दीर्घ tsc_at_measure_start;
अटल अचिन्हित दीर्घ दीर्घ tsc_at_measure_end;
अटल अचिन्हित दीर्घ दीर्घ *mperf_previous_count;
अटल अचिन्हित दीर्घ दीर्घ *aperf_previous_count;
अटल अचिन्हित दीर्घ दीर्घ *mperf_current_count;
अटल अचिन्हित दीर्घ दीर्घ *aperf_current_count;

/* valid flag क्रम all CPUs. If a MSR पढ़ो failed it will be zero */
अटल पूर्णांक *is_valid;

अटल पूर्णांक mperf_get_tsc(अचिन्हित दीर्घ दीर्घ *tsc)
अणु
	पूर्णांक ret;

	ret = पढ़ो_msr(base_cpu, MSR_TSC, tsc);
	अगर (ret)
		dprपूर्णांक("Reading TSC MSR failed, returning %llu\n", *tsc);
	वापस ret;
पूर्ण

अटल पूर्णांक get_aperf_mperf(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ *aval,
				    अचिन्हित दीर्घ दीर्घ *mval)
अणु
	अचिन्हित दीर्घ low_a, high_a;
	अचिन्हित दीर्घ low_m, high_m;
	पूर्णांक ret;

	/*
	 * Running on the cpu from which we पढ़ो the रेजिस्टरs will
	 * prevent APERF/MPERF from going out of sync because of IPI
	 * latency पूर्णांकroduced by पढ़ो_msr()s.
	 */
	अगर (mperf_monitor.flags.per_cpu_schedule) अणु
		अगर (bind_cpu(cpu))
			वापस 1;
	पूर्ण

	अगर (cpuघातer_cpu_info.caps & CPUPOWER_CAP_AMD_RDPRU) अणु
		यंत्र अस्थिर(RDPRU
			     : "=a" (low_a), "=d" (high_a)
			     : "c" (RDPRU_ECX_APERF));
		यंत्र अस्थिर(RDPRU
			     : "=a" (low_m), "=d" (high_m)
			     : "c" (RDPRU_ECX_MPERF));

		*aval = ((low_a) | (high_a) << 32);
		*mval = ((low_m) | (high_m) << 32);

		वापस 0;
	पूर्ण

	ret  = पढ़ो_msr(cpu, MSR_APERF, aval);
	ret |= पढ़ो_msr(cpu, MSR_MPERF, mval);

	वापस ret;
पूर्ण

अटल पूर्णांक mperf_init_stats(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ aval, mval;
	पूर्णांक ret;

	ret = get_aperf_mperf(cpu, &aval, &mval);
	aperf_previous_count[cpu] = aval;
	mperf_previous_count[cpu] = mval;
	is_valid[cpu] = !ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mperf_measure_stats(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ aval, mval;
	पूर्णांक ret;

	ret = get_aperf_mperf(cpu, &aval, &mval);
	aperf_current_count[cpu] = aval;
	mperf_current_count[cpu] = mval;
	is_valid[cpu] = !ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mperf_get_count_percent(अचिन्हित पूर्णांक id, द्विगुन *percent,
				   अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ aperf_dअगरf, mperf_dअगरf, tsc_dअगरf;
	अचिन्हित दीर्घ दीर्घ समयdअगरf;

	अगर (!is_valid[cpu])
		वापस -1;

	अगर (id != C0 && id != Cx)
		वापस -1;

	mperf_dअगरf = mperf_current_count[cpu] - mperf_previous_count[cpu];
	aperf_dअगरf = aperf_current_count[cpu] - aperf_previous_count[cpu];

	अगर (max_freq_mode == MAX_FREQ_TSC_REF) अणु
		tsc_dअगरf = tsc_at_measure_end - tsc_at_measure_start;
		*percent = 100.0 * mperf_dअगरf / tsc_dअगरf;
		dprपूर्णांक("%s: TSC Ref - mperf_diff: %llu, tsc_diff: %llu\n",
		       mperf_cstates[id].name, mperf_dअगरf, tsc_dअगरf);
	पूर्ण अन्यथा अगर (max_freq_mode == MAX_FREQ_SYSFS) अणु
		समयdअगरf = max_frequency * बारpec_dअगरf_us(समय_start, समय_end);
		*percent = 100.0 * mperf_dअगरf / समयdअगरf;
		dprपूर्णांक("%s: MAXFREQ - mperf_diff: %llu, time_diff: %llu\n",
		       mperf_cstates[id].name, mperf_dअगरf, समयdअगरf);
	पूर्ण अन्यथा
		वापस -1;

	अगर (id == Cx)
		*percent = 100.0 - *percent;

	dprपूर्णांक("%s: previous: %llu - current: %llu - (%u)\n",
		mperf_cstates[id].name, mperf_dअगरf, aperf_dअगरf, cpu);
	dprपूर्णांक("%s: %f\n", mperf_cstates[id].name, *percent);
	वापस 0;
पूर्ण

अटल पूर्णांक mperf_get_count_freq(अचिन्हित पूर्णांक id, अचिन्हित दीर्घ दीर्घ *count,
				अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ aperf_dअगरf, mperf_dअगरf, समय_dअगरf, tsc_dअगरf;

	अगर (id != AVG_FREQ)
		वापस 1;

	अगर (!is_valid[cpu])
		वापस -1;

	mperf_dअगरf = mperf_current_count[cpu] - mperf_previous_count[cpu];
	aperf_dअगरf = aperf_current_count[cpu] - aperf_previous_count[cpu];

	अगर (max_freq_mode == MAX_FREQ_TSC_REF) अणु
		/* Calculate max_freq from TSC count */
		tsc_dअगरf = tsc_at_measure_end - tsc_at_measure_start;
		समय_dअगरf = बारpec_dअगरf_us(समय_start, समय_end);
		max_frequency = tsc_dअगरf / समय_dअगरf;
	पूर्ण

	*count = max_frequency * ((द्विगुन)aperf_dअगरf / mperf_dअगरf);
	dprपूर्णांक("%s: Average freq based on %s maximum frequency:\n",
	       mperf_cstates[id].name,
	       (max_freq_mode == MAX_FREQ_TSC_REF) ? "TSC calculated" : "sysfs read");
	dprपूर्णांक("max_frequency: %lu\n", max_frequency);
	dprपूर्णांक("aperf_diff: %llu\n", aperf_dअगरf);
	dprपूर्णांक("mperf_diff: %llu\n", mperf_dअगरf);
	dprपूर्णांक("avg freq:   %llu\n", *count);
	वापस 0;
पूर्ण

अटल पूर्णांक mperf_start(व्योम)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ दीर्घ dbg;

	घड़ी_समय_लो(CLOCK_REALTIME, &समय_start);
	mperf_get_tsc(&tsc_at_measure_start);

	क्रम (cpu = 0; cpu < cpu_count; cpu++)
		mperf_init_stats(cpu);

	mperf_get_tsc(&dbg);
	dprपूर्णांक("TSC diff: %llu\n", dbg - tsc_at_measure_start);
	वापस 0;
पूर्ण

अटल पूर्णांक mperf_stop(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ dbg;
	पूर्णांक cpu;

	क्रम (cpu = 0; cpu < cpu_count; cpu++)
		mperf_measure_stats(cpu);

	mperf_get_tsc(&tsc_at_measure_end);
	घड़ी_समय_लो(CLOCK_REALTIME, &समय_end);

	mperf_get_tsc(&dbg);
	dprपूर्णांक("TSC diff: %llu\n", dbg - tsc_at_measure_end);

	वापस 0;
पूर्ण

/*
 * Mperf रेजिस्टर is defined to tick at P0 (maximum) frequency
 *
 * Instead of पढ़ोing out P0 which can be tricky to पढ़ो out from HW,
 * we use TSC counter अगर it reliably ticks at P0/mperf frequency.
 *
 * Still try to fall back to:
 * /sys/devices/प्रणाली/cpu/cpu0/cpufreq/cpuinfo_max_freq
 * on older Intel HW without invariant TSC feature.
 * Or on AMD machines where TSC करोes not tick at P0 (करो not exist yet, but
 * it's still द्विगुन checked (MSR_AMD_HWCR)).
 *
 * On these machines the user would still get useful mperf
 * stats when acpi-cpufreq driver is loaded.
 */
अटल पूर्णांक init_maxfreq_mode(व्योम)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ दीर्घ hwcr;
	अचिन्हित दीर्घ min;

	अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_INV_TSC))
		जाओ use_sysfs;

	अगर (cpuघातer_cpu_info.venकरोr == X86_VENDOR_AMD ||
	    cpuघातer_cpu_info.venकरोr == X86_VENDOR_HYGON) अणु
		/* MSR_AMD_HWCR tells us whether TSC runs at P0/mperf
		 * freq.
		 * A test whether hwcr is accessable/available would be:
		 * (cpuघातer_cpu_info.family > 0x10 ||
		 *   cpuघातer_cpu_info.family == 0x10 &&
		 *   cpuघातer_cpu_info.model >= 0x2))
		 * This should be the हाल क्रम all aperf/mperf
		 * capable AMD machines and is thereक्रमe safe to test here.
		 * Compare with Linus kernel git commit: acf01734b1747b1ec4
		 */
		ret = पढ़ो_msr(0, MSR_AMD_HWCR, &hwcr);
		/*
		 * If the MSR पढ़ो failed, assume a Xen प्रणाली that did
		 * not explicitly provide access to it and assume TSC works
		*/
		अगर (ret != 0) अणु
			dprपूर्णांक("TSC read 0x%x failed - assume TSC working\n",
			       MSR_AMD_HWCR);
			वापस 0;
		पूर्ण अन्यथा अगर (1 & (hwcr >> 24)) अणु
			max_freq_mode = MAX_FREQ_TSC_REF;
			वापस 0;
		पूर्ण अन्यथा अणु /* Use sysfs max frequency अगर available */ पूर्ण
	पूर्ण अन्यथा अगर (cpuघातer_cpu_info.venकरोr == X86_VENDOR_INTEL) अणु
		/*
		 * On Intel we assume mperf (in C0) is ticking at same
		 * rate than TSC
		 */
		max_freq_mode = MAX_FREQ_TSC_REF;
		वापस 0;
	पूर्ण
use_sysfs:
	अगर (cpufreq_get_hardware_limits(0, &min, &max_frequency)) अणु
		dprपूर्णांक("Cannot retrieve max freq from cpufreq kernel "
		       "subsystem\n");
		वापस -1;
	पूर्ण
	max_freq_mode = MAX_FREQ_SYSFS;
	max_frequency /= 1000; /* Default स्वतःmatically to MHz value */
	वापस 0;
पूर्ण

/*
 * This monitor provides:
 *
 * 1) Average frequency a CPU resided in
 *    This always works अगर the CPU has aperf/mperf capabilities
 *
 * 2) C0 and Cx (any sleep state) समय a CPU resided in
 *    Works अगर mperf समयr stops ticking in sleep states which
 *    seem to be the हाल on all current HW.
 * Both is directly retrieved from HW रेजिस्टरs and is independent
 * from kernel statistics.
 */
काष्ठा cpuidle_monitor mperf_monitor;
काष्ठा cpuidle_monitor *mperf_रेजिस्टर(व्योम)
अणु
	अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_APERF))
		वापस शून्य;

	अगर (init_maxfreq_mode())
		वापस शून्य;

	अगर (cpuघातer_cpu_info.venकरोr == X86_VENDOR_AMD)
		mperf_monitor.flags.per_cpu_schedule = 1;

	/* Free this at program termination */
	is_valid = सुस्मृति(cpu_count, माप(पूर्णांक));
	mperf_previous_count = सुस्मृति(cpu_count, माप(अचिन्हित दीर्घ दीर्घ));
	aperf_previous_count = सुस्मृति(cpu_count, माप(अचिन्हित दीर्घ दीर्घ));
	mperf_current_count = सुस्मृति(cpu_count, माप(अचिन्हित दीर्घ दीर्घ));
	aperf_current_count = सुस्मृति(cpu_count, माप(अचिन्हित दीर्घ दीर्घ));

	mperf_monitor.name_len = म_माप(mperf_monitor.name);
	वापस &mperf_monitor;
पूर्ण

व्योम mperf_unरेजिस्टर(व्योम)
अणु
	मुक्त(mperf_previous_count);
	मुक्त(aperf_previous_count);
	मुक्त(mperf_current_count);
	मुक्त(aperf_current_count);
	मुक्त(is_valid);
पूर्ण

काष्ठा cpuidle_monitor mperf_monitor = अणु
	.name			= "Mperf",
	.hw_states_num		= MPERF_CSTATE_COUNT,
	.hw_states		= mperf_cstates,
	.start			= mperf_start,
	.stop			= mperf_stop,
	.करो_रेजिस्टर		= mperf_रेजिस्टर,
	.unरेजिस्टर		= mperf_unरेजिस्टर,
	.flags.needs_root	= 1,
	.overflow_s		= 922000000 /* 922337203 seconds TSC overflow
					       at 20GHz */
पूर्ण;
#पूर्ण_अगर /* #अगर defined(__i386__) || defined(__x86_64__) */

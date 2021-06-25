<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_pstate.c: Native P state management क्रम Intel processors
 *
 * (C) Copyright 2012 Intel Corporation
 * Author: Dirk Bअक्रमewie <dirk.j.bअक्रमewie@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/tick.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/cpufreq.h>
#समावेश <linux/list.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/acpi.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pm_qos.h>
#समावेश <trace/events/घातer.h>

#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

#घोषणा INTEL_PSTATE_SAMPLING_INTERVAL	(10 * NSEC_PER_MSEC)

#घोषणा INTEL_CPUFREQ_TRANSITION_LATENCY	20000
#घोषणा INTEL_CPUFREQ_TRANSITION_DELAY_HWP	5000
#घोषणा INTEL_CPUFREQ_TRANSITION_DELAY		500

#अगर_घोषित CONFIG_ACPI
#समावेश <acpi/processor.h>
#समावेश <acpi/cppc_acpi.h>
#पूर्ण_अगर

#घोषणा FRAC_BITS 8
#घोषणा पूर्णांक_tofp(X) ((पूर्णांक64_t)(X) << FRAC_BITS)
#घोषणा fp_toपूर्णांक(X) ((X) >> FRAC_BITS)

#घोषणा ONE_EIGHTH_FP ((पूर्णांक64_t)1 << (FRAC_BITS - 3))

#घोषणा EXT_BITS 6
#घोषणा EXT_FRAC_BITS (EXT_BITS + FRAC_BITS)
#घोषणा fp_ext_toपूर्णांक(X) ((X) >> EXT_FRAC_BITS)
#घोषणा पूर्णांक_ext_tofp(X) ((पूर्णांक64_t)(X) << EXT_FRAC_BITS)

अटल अंतरभूत पूर्णांक32_t mul_fp(पूर्णांक32_t x, पूर्णांक32_t y)
अणु
	वापस ((पूर्णांक64_t)x * (पूर्णांक64_t)y) >> FRAC_BITS;
पूर्ण

अटल अंतरभूत पूर्णांक32_t भाग_fp(s64 x, s64 y)
अणु
	वापस भाग64_s64((पूर्णांक64_t)x << FRAC_BITS, y);
पूर्ण

अटल अंतरभूत पूर्णांक उच्चमानing_fp(पूर्णांक32_t x)
अणु
	पूर्णांक mask, ret;

	ret = fp_toपूर्णांक(x);
	mask = (1 << FRAC_BITS) - 1;
	अगर (x & mask)
		ret += 1;
	वापस ret;
पूर्ण

अटल अंतरभूत u64 mul_ext_fp(u64 x, u64 y)
अणु
	वापस (x * y) >> EXT_FRAC_BITS;
पूर्ण

अटल अंतरभूत u64 भाग_ext_fp(u64 x, u64 y)
अणु
	वापस भाग64_u64(x << EXT_FRAC_BITS, y);
पूर्ण

/**
 * काष्ठा sample -	Store perक्रमmance sample
 * @core_avg_perf:	Ratio of APERF/MPERF which is the actual average
 *			perक्रमmance during last sample period
 * @busy_scaled:	Scaled busy value which is used to calculate next
 *			P state. This can be dअगरferent than core_avg_perf
 *			to account क्रम cpu idle period
 * @aperf:		Dअगरference of actual perक्रमmance frequency घड़ी count
 *			पढ़ो from APERF MSR between last and current sample
 * @mperf:		Dअगरference of maximum perक्रमmance frequency घड़ी count
 *			पढ़ो from MPERF MSR between last and current sample
 * @tsc:		Dअगरference of समय stamp counter between last and
 *			current sample
 * @समय:		Current समय from scheduler
 *
 * This काष्ठाure is used in the cpudata काष्ठाure to store perक्रमmance sample
 * data क्रम choosing next P State.
 */
काष्ठा sample अणु
	पूर्णांक32_t core_avg_perf;
	पूर्णांक32_t busy_scaled;
	u64 aperf;
	u64 mperf;
	u64 tsc;
	u64 समय;
पूर्ण;

/**
 * काष्ठा pstate_data - Store P state data
 * @current_pstate:	Current requested P state
 * @min_pstate:		Min P state possible क्रम this platक्रमm
 * @max_pstate:		Max P state possible क्रम this platक्रमm
 * @max_pstate_physical:This is physical Max P state क्रम a processor
 *			This can be higher than the max_pstate which can
 *			be limited by platक्रमm thermal design घातer limits
 * @scaling:		Scaling factor to  convert frequency to cpufreq
 *			frequency units
 * @turbo_pstate:	Max Turbo P state possible क्रम this platक्रमm
 * @max_freq:		@max_pstate frequency in cpufreq units
 * @turbo_freq:		@turbo_pstate frequency in cpufreq units
 *
 * Stores the per cpu model P state limits and current P state.
 */
काष्ठा pstate_data अणु
	पूर्णांक	current_pstate;
	पूर्णांक	min_pstate;
	पूर्णांक	max_pstate;
	पूर्णांक	max_pstate_physical;
	पूर्णांक	scaling;
	पूर्णांक	turbo_pstate;
	अचिन्हित पूर्णांक max_freq;
	अचिन्हित पूर्णांक turbo_freq;
पूर्ण;

/**
 * काष्ठा vid_data -	Stores voltage inक्रमmation data
 * @min:		VID data क्रम this platक्रमm corresponding to
 *			the lowest P state
 * @max:		VID data corresponding to the highest P State.
 * @turbo:		VID data क्रम turbo P state
 * @ratio:		Ratio of (vid max - vid min) /
 *			(max P state - Min P State)
 *
 * Stores the voltage data क्रम DVFS (Dynamic Voltage and Frequency Scaling)
 * This data is used in Atom platक्रमms, where in addition to target P state,
 * the voltage data needs to be specअगरied to select next P State.
 */
काष्ठा vid_data अणु
	पूर्णांक min;
	पूर्णांक max;
	पूर्णांक turbo;
	पूर्णांक32_t ratio;
पूर्ण;

/**
 * काष्ठा global_params - Global parameters, mostly tunable via sysfs.
 * @no_turbo:		Whether or not to use turbo P-states.
 * @turbo_disabled:	Whether or not turbo P-states are available at all,
 *			based on the MSR_IA32_MISC_ENABLE value and whether or
 *			not the maximum reported turbo P-state is dअगरferent from
 *			the maximum reported non-turbo one.
 * @turbo_disabled_mf:	The @turbo_disabled value reflected by cpuinfo.max_freq.
 * @min_perf_pct:	Minimum capacity limit in percent of the maximum turbo
 *			P-state capacity.
 * @max_perf_pct:	Maximum capacity limit in percent of the maximum turbo
 *			P-state capacity.
 */
काष्ठा global_params अणु
	bool no_turbo;
	bool turbo_disabled;
	bool turbo_disabled_mf;
	पूर्णांक max_perf_pct;
	पूर्णांक min_perf_pct;
पूर्ण;

/**
 * काष्ठा cpudata -	Per CPU instance data storage
 * @cpu:		CPU number क्रम this instance data
 * @policy:		CPUFreq policy value
 * @update_util:	CPUFreq utility callback inक्रमmation
 * @update_util_set:	CPUFreq utility callback is set
 * @ioरुको_boost:	ioरुको-related boost fraction
 * @last_update:	Time of the last update.
 * @pstate:		Stores P state limits क्रम this CPU
 * @vid:		Stores VID limits क्रम this CPU
 * @last_sample_समय:	Last Sample समय
 * @aperf_mperf_shअगरt:	APERF vs MPERF counting frequency dअगरference
 * @prev_aperf:		Last APERF value पढ़ो from APERF MSR
 * @prev_mperf:		Last MPERF value पढ़ो from MPERF MSR
 * @prev_tsc:		Last बारtamp counter (TSC) value
 * @prev_cummulative_ioरुको: IO Wait समय dअगरference from last and
 *			current sample
 * @sample:		Storage क्रम storing last Sample data
 * @min_perf_ratio:	Minimum capacity in terms of PERF or HWP ratios
 * @max_perf_ratio:	Maximum capacity in terms of PERF or HWP ratios
 * @acpi_perf_data:	Stores ACPI perf inक्रमmation पढ़ो from _PSS
 * @valid_pss_table:	Set to true क्रम valid ACPI _PSS entries found
 * @epp_घातersave:	Last saved HWP energy perक्रमmance preference
 *			(EPP) or energy perक्रमmance bias (EPB),
 *			when policy चयनed to perक्रमmance
 * @epp_policy:		Last saved policy used to set EPP/EPB
 * @epp_शेष:	Power on शेष HWP energy perक्रमmance
 *			preference/bias
 * @epp_cached		Cached HWP energy-perक्रमmance preference value
 * @hwp_req_cached:	Cached value of the last HWP Request MSR
 * @hwp_cap_cached:	Cached value of the last HWP Capabilities MSR
 * @last_io_update:	Last समय when IO wake flag was set
 * @sched_flags:	Store scheduler flags क्रम possible cross CPU update
 * @hwp_boost_min:	Last HWP boosted min perक्रमmance
 * @suspended:		Whether or not the driver has been suspended.
 *
 * This काष्ठाure stores per CPU instance data क्रम all CPUs.
 */
काष्ठा cpudata अणु
	पूर्णांक cpu;

	अचिन्हित पूर्णांक policy;
	काष्ठा update_util_data update_util;
	bool   update_util_set;

	काष्ठा pstate_data pstate;
	काष्ठा vid_data vid;

	u64	last_update;
	u64	last_sample_समय;
	u64	aperf_mperf_shअगरt;
	u64	prev_aperf;
	u64	prev_mperf;
	u64	prev_tsc;
	u64	prev_cummulative_ioरुको;
	काष्ठा sample sample;
	पूर्णांक32_t	min_perf_ratio;
	पूर्णांक32_t	max_perf_ratio;
#अगर_घोषित CONFIG_ACPI
	काष्ठा acpi_processor_perक्रमmance acpi_perf_data;
	bool valid_pss_table;
#पूर्ण_अगर
	अचिन्हित पूर्णांक ioरुको_boost;
	s16 epp_घातersave;
	s16 epp_policy;
	s16 epp_शेष;
	s16 epp_cached;
	u64 hwp_req_cached;
	u64 hwp_cap_cached;
	u64 last_io_update;
	अचिन्हित पूर्णांक sched_flags;
	u32 hwp_boost_min;
	bool suspended;
पूर्ण;

अटल काष्ठा cpudata **all_cpu_data;

/**
 * काष्ठा pstate_funcs - Per CPU model specअगरic callbacks
 * @get_max:		Callback to get maximum non turbo effective P state
 * @get_max_physical:	Callback to get maximum non turbo physical P state
 * @get_min:		Callback to get minimum P state
 * @get_turbo:		Callback to get turbo P state
 * @get_scaling:	Callback to get frequency scaling factor
 * @get_aperf_mperf_shअगरt: Callback to get the APERF vs MPERF frequency dअगरference
 * @get_val:		Callback to convert P state to actual MSR ग_लिखो value
 * @get_vid:		Callback to get VID data क्रम Atom platक्रमms
 *
 * Core and Atom CPU models have dअगरferent way to get P State limits. This
 * काष्ठाure is used to store those callbacks.
 */
काष्ठा pstate_funcs अणु
	पूर्णांक (*get_max)(व्योम);
	पूर्णांक (*get_max_physical)(व्योम);
	पूर्णांक (*get_min)(व्योम);
	पूर्णांक (*get_turbo)(व्योम);
	पूर्णांक (*get_scaling)(व्योम);
	पूर्णांक (*get_aperf_mperf_shअगरt)(व्योम);
	u64 (*get_val)(काष्ठा cpudata*, पूर्णांक pstate);
	व्योम (*get_vid)(काष्ठा cpudata *);
पूर्ण;

अटल काष्ठा pstate_funcs pstate_funcs __पढ़ो_mostly;

अटल पूर्णांक hwp_active __पढ़ो_mostly;
अटल पूर्णांक hwp_mode_bdw __पढ़ो_mostly;
अटल bool per_cpu_limits __पढ़ो_mostly;
अटल bool hwp_boost __पढ़ो_mostly;

अटल काष्ठा cpufreq_driver *पूर्णांकel_pstate_driver __पढ़ो_mostly;

#अगर_घोषित CONFIG_ACPI
अटल bool acpi_ppc;
#पूर्ण_अगर

अटल काष्ठा global_params global;

अटल DEFINE_MUTEX(पूर्णांकel_pstate_driver_lock);
अटल DEFINE_MUTEX(पूर्णांकel_pstate_limits_lock);

#अगर_घोषित CONFIG_ACPI

अटल bool पूर्णांकel_pstate_acpi_pm_profile_server(व्योम)
अणु
	अगर (acpi_gbl_FADT.preferred_profile == PM_ENTERPRISE_SERVER ||
	    acpi_gbl_FADT.preferred_profile == PM_PERFORMANCE_SERVER)
		वापस true;

	वापस false;
पूर्ण

अटल bool पूर्णांकel_pstate_get_ppc_enable_status(व्योम)
अणु
	अगर (पूर्णांकel_pstate_acpi_pm_profile_server())
		वापस true;

	वापस acpi_ppc;
पूर्ण

#अगर_घोषित CONFIG_ACPI_CPPC_LIB

/* The work item is needed to aव्योम CPU hotplug locking issues */
अटल व्योम पूर्णांकel_pstste_sched_iपंचांगt_work_fn(काष्ठा work_काष्ठा *work)
अणु
	sched_set_iपंचांगt_support();
पूर्ण

अटल DECLARE_WORK(sched_iपंचांगt_work, पूर्णांकel_pstste_sched_iपंचांगt_work_fn);

अटल व्योम पूर्णांकel_pstate_set_iपंचांगt_prio(पूर्णांक cpu)
अणु
	काष्ठा cppc_perf_caps cppc_perf;
	अटल u32 max_highest_perf = 0, min_highest_perf = U32_MAX;
	पूर्णांक ret;

	ret = cppc_get_perf_caps(cpu, &cppc_perf);
	अगर (ret)
		वापस;

	/*
	 * The priorities can be set regardless of whether or not
	 * sched_set_iपंचांगt_support(true) has been called and it is valid to
	 * update them at any समय after it has been called.
	 */
	sched_set_iपंचांगt_core_prio(cppc_perf.highest_perf, cpu);

	अगर (max_highest_perf <= min_highest_perf) अणु
		अगर (cppc_perf.highest_perf > max_highest_perf)
			max_highest_perf = cppc_perf.highest_perf;

		अगर (cppc_perf.highest_perf < min_highest_perf)
			min_highest_perf = cppc_perf.highest_perf;

		अगर (max_highest_perf > min_highest_perf) अणु
			/*
			 * This code can be run during CPU online under the
			 * CPU hotplug locks, so sched_set_iपंचांगt_support()
			 * cannot be called from here.  Queue up a work item
			 * to invoke it.
			 */
			schedule_work(&sched_iपंचांगt_work);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_get_cppc_guranteed(पूर्णांक cpu)
अणु
	काष्ठा cppc_perf_caps cppc_perf;
	पूर्णांक ret;

	ret = cppc_get_perf_caps(cpu, &cppc_perf);
	अगर (ret)
		वापस ret;

	अगर (cppc_perf.guaranteed_perf)
		वापस cppc_perf.guaranteed_perf;

	वापस cppc_perf.nominal_perf;
पूर्ण

#अन्यथा /* CONFIG_ACPI_CPPC_LIB */
अटल व्योम पूर्णांकel_pstate_set_iपंचांगt_prio(पूर्णांक cpu)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_CPPC_LIB */

अटल व्योम पूर्णांकel_pstate_init_acpi_perf_limits(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpudata *cpu;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (hwp_active) अणु
		पूर्णांकel_pstate_set_iपंचांगt_prio(policy->cpu);
		वापस;
	पूर्ण

	अगर (!पूर्णांकel_pstate_get_ppc_enable_status())
		वापस;

	cpu = all_cpu_data[policy->cpu];

	ret = acpi_processor_रेजिस्टर_perक्रमmance(&cpu->acpi_perf_data,
						  policy->cpu);
	अगर (ret)
		वापस;

	/*
	 * Check अगर the control value in _PSS is क्रम PERF_CTL MSR, which should
	 * guarantee that the states वापसed by it map to the states in our
	 * list directly.
	 */
	अगर (cpu->acpi_perf_data.control_रेजिस्टर.space_id !=
						ACPI_ADR_SPACE_FIXED_HARDWARE)
		जाओ err;

	/*
	 * If there is only one entry _PSS, simply ignore _PSS and जारी as
	 * usual without taking _PSS पूर्णांकo account
	 */
	अगर (cpu->acpi_perf_data.state_count < 2)
		जाओ err;

	pr_debug("CPU%u - ACPI _PSS perf data\n", policy->cpu);
	क्रम (i = 0; i < cpu->acpi_perf_data.state_count; i++) अणु
		pr_debug("     %cP%d: %u MHz, %u mW, 0x%x\n",
			 (i == cpu->acpi_perf_data.state ? '*' : ' '), i,
			 (u32) cpu->acpi_perf_data.states[i].core_frequency,
			 (u32) cpu->acpi_perf_data.states[i].घातer,
			 (u32) cpu->acpi_perf_data.states[i].control);
	पूर्ण

	/*
	 * The _PSS table करोesn't contain whole turbo frequency range.
	 * This just contains +1 MHZ above the max non turbo frequency,
	 * with control value corresponding to max turbo ratio. But
	 * when cpufreq set policy is called, it will call with this
	 * max frequency, which will cause a reduced perक्रमmance as
	 * this driver uses real max turbo frequency as the max
	 * frequency. So correct this frequency in _PSS table to
	 * correct max turbo frequency based on the turbo state.
	 * Also need to convert to MHz as _PSS freq is in MHz.
	 */
	अगर (!global.turbo_disabled)
		cpu->acpi_perf_data.states[0].core_frequency =
					policy->cpuinfo.max_freq / 1000;
	cpu->valid_pss_table = true;
	pr_debug("_PPC limits will be enforced\n");

	वापस;

 err:
	cpu->valid_pss_table = false;
	acpi_processor_unरेजिस्टर_perक्रमmance(policy->cpu);
पूर्ण

अटल व्योम पूर्णांकel_pstate_निकास_perf_limits(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpudata *cpu;

	cpu = all_cpu_data[policy->cpu];
	अगर (!cpu->valid_pss_table)
		वापस;

	acpi_processor_unरेजिस्टर_perक्रमmance(policy->cpu);
पूर्ण
#अन्यथा /* CONFIG_ACPI */
अटल अंतरभूत व्योम पूर्णांकel_pstate_init_acpi_perf_limits(काष्ठा cpufreq_policy *policy)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pstate_निकास_perf_limits(काष्ठा cpufreq_policy *policy)
अणु
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pstate_acpi_pm_profile_server(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

#अगर_अघोषित CONFIG_ACPI_CPPC_LIB
अटल पूर्णांक पूर्णांकel_pstate_get_cppc_guranteed(पूर्णांक cpu)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_CPPC_LIB */

अटल अंतरभूत व्योम update_turbo_state(व्योम)
अणु
	u64 misc_en;
	काष्ठा cpudata *cpu;

	cpu = all_cpu_data[0];
	rdmsrl(MSR_IA32_MISC_ENABLE, misc_en);
	global.turbo_disabled =
		(misc_en & MSR_IA32_MISC_ENABLE_TURBO_DISABLE ||
		 cpu->pstate.max_pstate == cpu->pstate.turbo_pstate);
पूर्ण

अटल पूर्णांक min_perf_pct_min(व्योम)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[0];
	पूर्णांक turbo_pstate = cpu->pstate.turbo_pstate;

	वापस turbo_pstate ?
		(cpu->pstate.min_pstate * 100 / turbo_pstate) : 0;
पूर्ण

अटल s16 पूर्णांकel_pstate_get_epb(काष्ठा cpudata *cpu_data)
अणु
	u64 epb;
	पूर्णांक ret;

	अगर (!boot_cpu_has(X86_FEATURE_EPB))
		वापस -ENXIO;

	ret = rdmsrl_on_cpu(cpu_data->cpu, MSR_IA32_ENERGY_PERF_BIAS, &epb);
	अगर (ret)
		वापस (s16)ret;

	वापस (s16)(epb & 0x0f);
पूर्ण

अटल s16 पूर्णांकel_pstate_get_epp(काष्ठा cpudata *cpu_data, u64 hwp_req_data)
अणु
	s16 epp;

	अगर (boot_cpu_has(X86_FEATURE_HWP_EPP)) अणु
		/*
		 * When hwp_req_data is 0, means that caller didn't पढ़ो
		 * MSR_HWP_REQUEST, so need to पढ़ो and get EPP.
		 */
		अगर (!hwp_req_data) अणु
			epp = rdmsrl_on_cpu(cpu_data->cpu, MSR_HWP_REQUEST,
					    &hwp_req_data);
			अगर (epp)
				वापस epp;
		पूर्ण
		epp = (hwp_req_data >> 24) & 0xff;
	पूर्ण अन्यथा अणु
		/* When there is no EPP present, HWP uses EPB settings */
		epp = पूर्णांकel_pstate_get_epb(cpu_data);
	पूर्ण

	वापस epp;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_set_epb(पूर्णांक cpu, s16 pref)
अणु
	u64 epb;
	पूर्णांक ret;

	अगर (!boot_cpu_has(X86_FEATURE_EPB))
		वापस -ENXIO;

	ret = rdmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS, &epb);
	अगर (ret)
		वापस ret;

	epb = (epb & ~0x0f) | pref;
	wrmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS, epb);

	वापस 0;
पूर्ण

/*
 * EPP/EPB display strings corresponding to EPP index in the
 * energy_perf_strings[]
 *	index		String
 *-------------------------------------
 *	0		शेष
 *	1		perक्रमmance
 *	2		balance_perक्रमmance
 *	3		balance_घातer
 *	4		घातer
 */
अटल स्थिर अक्षर * स्थिर energy_perf_strings[] = अणु
	"default",
	"performance",
	"balance_performance",
	"balance_power",
	"power",
	शून्य
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक epp_values[] = अणु
	HWP_EPP_PERFORMANCE,
	HWP_EPP_BALANCE_PERFORMANCE,
	HWP_EPP_BALANCE_POWERSAVE,
	HWP_EPP_POWERSAVE
पूर्ण;

अटल पूर्णांक पूर्णांकel_pstate_get_energy_pref_index(काष्ठा cpudata *cpu_data, पूर्णांक *raw_epp)
अणु
	s16 epp;
	पूर्णांक index = -EINVAL;

	*raw_epp = 0;
	epp = पूर्णांकel_pstate_get_epp(cpu_data, 0);
	अगर (epp < 0)
		वापस epp;

	अगर (boot_cpu_has(X86_FEATURE_HWP_EPP)) अणु
		अगर (epp == HWP_EPP_PERFORMANCE)
			वापस 1;
		अगर (epp == HWP_EPP_BALANCE_PERFORMANCE)
			वापस 2;
		अगर (epp == HWP_EPP_BALANCE_POWERSAVE)
			वापस 3;
		अगर (epp == HWP_EPP_POWERSAVE)
			वापस 4;
		*raw_epp = epp;
		वापस 0;
	पूर्ण अन्यथा अगर (boot_cpu_has(X86_FEATURE_EPB)) अणु
		/*
		 * Range:
		 *	0x00-0x03	:	Perक्रमmance
		 *	0x04-0x07	:	Balance perक्रमmance
		 *	0x08-0x0B	:	Balance घातer
		 *	0x0C-0x0F	:	Power
		 * The EPB is a 4 bit value, but our ranges restrict the
		 * value which can be set. Here only using top two bits
		 * effectively.
		 */
		index = (epp >> 2) + 1;
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_set_epp(काष्ठा cpudata *cpu, u32 epp)
अणु
	पूर्णांक ret;

	/*
	 * Use the cached HWP Request MSR value, because in the active mode the
	 * रेजिस्टर itself may be updated by पूर्णांकel_pstate_hwp_boost_up() or
	 * पूर्णांकel_pstate_hwp_boost_करोwn() at any समय.
	 */
	u64 value = READ_ONCE(cpu->hwp_req_cached);

	value &= ~GENMASK_ULL(31, 24);
	value |= (u64)epp << 24;
	/*
	 * The only other updater of hwp_req_cached in the active mode,
	 * पूर्णांकel_pstate_hwp_set(), is called under the same lock as this
	 * function, so it cannot run in parallel with the update below.
	 */
	WRITE_ONCE(cpu->hwp_req_cached, value);
	ret = wrmsrl_on_cpu(cpu->cpu, MSR_HWP_REQUEST, value);
	अगर (!ret)
		cpu->epp_cached = epp;

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_set_energy_pref_index(काष्ठा cpudata *cpu_data,
					      पूर्णांक pref_index, bool use_raw,
					      u32 raw_epp)
अणु
	पूर्णांक epp = -EINVAL;
	पूर्णांक ret;

	अगर (!pref_index)
		epp = cpu_data->epp_शेष;

	अगर (boot_cpu_has(X86_FEATURE_HWP_EPP)) अणु
		अगर (use_raw)
			epp = raw_epp;
		अन्यथा अगर (epp == -EINVAL)
			epp = epp_values[pref_index - 1];

		/*
		 * To aव्योम confusion, refuse to set EPP to any values dअगरferent
		 * from 0 (perक्रमmance) अगर the current policy is "performance",
		 * because those values would be overridden.
		 */
		अगर (epp > 0 && cpu_data->policy == CPUFREQ_POLICY_PERFORMANCE)
			वापस -EBUSY;

		ret = पूर्णांकel_pstate_set_epp(cpu_data, epp);
	पूर्ण अन्यथा अणु
		अगर (epp == -EINVAL)
			epp = (pref_index - 1) << 2;
		ret = पूर्णांकel_pstate_set_epb(cpu_data->cpu, epp);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_energy_perक्रमmance_available_preferences(
				काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	पूर्णांक i = 0;
	पूर्णांक ret = 0;

	जबतक (energy_perf_strings[i] != शून्य)
		ret += प्र_लिखो(&buf[ret], "%s ", energy_perf_strings[i++]);

	ret += प्र_लिखो(&buf[ret], "\n");

	वापस ret;
पूर्ण

cpufreq_freq_attr_ro(energy_perक्रमmance_available_preferences);

अटल काष्ठा cpufreq_driver पूर्णांकel_pstate;

अटल sमाप_प्रकार store_energy_perक्रमmance_preference(
		काष्ठा cpufreq_policy *policy, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];
	अक्षर str_preference[21];
	bool raw = false;
	sमाप_प्रकार ret;
	u32 epp = 0;

	ret = माला_पूछो(buf, "%20s", str_preference);
	अगर (ret != 1)
		वापस -EINVAL;

	ret = match_string(energy_perf_strings, -1, str_preference);
	अगर (ret < 0) अणु
		अगर (!boot_cpu_has(X86_FEATURE_HWP_EPP))
			वापस ret;

		ret = kstrtouपूर्णांक(buf, 10, &epp);
		अगर (ret)
			वापस ret;

		अगर (epp > 255)
			वापस -EINVAL;

		raw = true;
	पूर्ण

	/*
	 * This function runs with the policy R/W semaphore held, which
	 * guarantees that the driver poपूर्णांकer will not change जबतक it is
	 * running.
	 */
	अगर (!पूर्णांकel_pstate_driver)
		वापस -EAGAIN;

	mutex_lock(&पूर्णांकel_pstate_limits_lock);

	अगर (पूर्णांकel_pstate_driver == &पूर्णांकel_pstate) अणु
		ret = पूर्णांकel_pstate_set_energy_pref_index(cpu, ret, raw, epp);
	पूर्ण अन्यथा अणु
		/*
		 * In the passive mode the governor needs to be stopped on the
		 * target CPU beक्रमe the EPP update and restarted after it,
		 * which is super-heavy-weight, so make sure it is worth करोing
		 * upfront.
		 */
		अगर (!raw)
			epp = ret ? epp_values[ret - 1] : cpu->epp_शेष;

		अगर (cpu->epp_cached != epp) अणु
			पूर्णांक err;

			cpufreq_stop_governor(policy);
			ret = पूर्णांकel_pstate_set_epp(cpu, epp);
			err = cpufreq_start_governor(policy);
			अगर (!ret)
				ret = err;
		पूर्ण
	पूर्ण

	mutex_unlock(&पूर्णांकel_pstate_limits_lock);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार show_energy_perक्रमmance_preference(
				काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा cpudata *cpu_data = all_cpu_data[policy->cpu];
	पूर्णांक preference, raw_epp;

	preference = पूर्णांकel_pstate_get_energy_pref_index(cpu_data, &raw_epp);
	अगर (preference < 0)
		वापस preference;

	अगर (raw_epp)
		वापस  प्र_लिखो(buf, "%d\n", raw_epp);
	अन्यथा
		वापस  प्र_लिखो(buf, "%s\n", energy_perf_strings[preference]);
पूर्ण

cpufreq_freq_attr_rw(energy_perक्रमmance_preference);

अटल sमाप_प्रकार show_base_frequency(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा cpudata *cpu;
	u64 cap;
	पूर्णांक ratio;

	ratio = पूर्णांकel_pstate_get_cppc_guranteed(policy->cpu);
	अगर (ratio <= 0) अणु
		rdmsrl_on_cpu(policy->cpu, MSR_HWP_CAPABILITIES, &cap);
		ratio = HWP_GUARANTEED_PERF(cap);
	पूर्ण

	cpu = all_cpu_data[policy->cpu];

	वापस प्र_लिखो(buf, "%d\n", ratio * cpu->pstate.scaling);
पूर्ण

cpufreq_freq_attr_ro(base_frequency);

अटल काष्ठा freq_attr *hwp_cpufreq_attrs[] = अणु
	&energy_perक्रमmance_preference,
	&energy_perक्रमmance_available_preferences,
	&base_frequency,
	शून्य,
पूर्ण;

अटल व्योम __पूर्णांकel_pstate_get_hwp_cap(काष्ठा cpudata *cpu)
अणु
	u64 cap;

	rdmsrl_on_cpu(cpu->cpu, MSR_HWP_CAPABILITIES, &cap);
	WRITE_ONCE(cpu->hwp_cap_cached, cap);
	cpu->pstate.max_pstate = HWP_GUARANTEED_PERF(cap);
	cpu->pstate.turbo_pstate = HWP_HIGHEST_PERF(cap);
पूर्ण

अटल व्योम पूर्णांकel_pstate_get_hwp_cap(काष्ठा cpudata *cpu)
अणु
	__पूर्णांकel_pstate_get_hwp_cap(cpu);
	cpu->pstate.max_freq = cpu->pstate.max_pstate * cpu->pstate.scaling;
	cpu->pstate.turbo_freq = cpu->pstate.turbo_pstate * cpu->pstate.scaling;
पूर्ण

अटल व्योम पूर्णांकel_pstate_hwp_set(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpudata *cpu_data = all_cpu_data[cpu];
	पूर्णांक max, min;
	u64 value;
	s16 epp;

	max = cpu_data->max_perf_ratio;
	min = cpu_data->min_perf_ratio;

	अगर (cpu_data->policy == CPUFREQ_POLICY_PERFORMANCE)
		min = max;

	rdmsrl_on_cpu(cpu, MSR_HWP_REQUEST, &value);

	value &= ~HWP_MIN_PERF(~0L);
	value |= HWP_MIN_PERF(min);

	value &= ~HWP_MAX_PERF(~0L);
	value |= HWP_MAX_PERF(max);

	अगर (cpu_data->epp_policy == cpu_data->policy)
		जाओ skip_epp;

	cpu_data->epp_policy = cpu_data->policy;

	अगर (cpu_data->policy == CPUFREQ_POLICY_PERFORMANCE) अणु
		epp = पूर्णांकel_pstate_get_epp(cpu_data, value);
		cpu_data->epp_घातersave = epp;
		/* If EPP पढ़ो was failed, then करोn't try to ग_लिखो */
		अगर (epp < 0)
			जाओ skip_epp;

		epp = 0;
	पूर्ण अन्यथा अणु
		/* skip setting EPP, when saved value is invalid */
		अगर (cpu_data->epp_घातersave < 0)
			जाओ skip_epp;

		/*
		 * No need to restore EPP when it is not zero. This
		 * means:
		 *  - Policy is not changed
		 *  - user has manually changed
		 *  - Error पढ़ोing EPB
		 */
		epp = पूर्णांकel_pstate_get_epp(cpu_data, value);
		अगर (epp)
			जाओ skip_epp;

		epp = cpu_data->epp_घातersave;
	पूर्ण
	अगर (boot_cpu_has(X86_FEATURE_HWP_EPP)) अणु
		value &= ~GENMASK_ULL(31, 24);
		value |= (u64)epp << 24;
	पूर्ण अन्यथा अणु
		पूर्णांकel_pstate_set_epb(cpu, epp);
	पूर्ण
skip_epp:
	WRITE_ONCE(cpu_data->hwp_req_cached, value);
	wrmsrl_on_cpu(cpu, MSR_HWP_REQUEST, value);
पूर्ण

अटल व्योम पूर्णांकel_pstate_hwp_offline(काष्ठा cpudata *cpu)
अणु
	u64 value = READ_ONCE(cpu->hwp_req_cached);
	पूर्णांक min_perf;

	अगर (boot_cpu_has(X86_FEATURE_HWP_EPP)) अणु
		/*
		 * In हाल the EPP has been set to "performance" by the
		 * active mode "performance" scaling algorithm, replace that
		 * temporary value with the cached EPP one.
		 */
		value &= ~GENMASK_ULL(31, 24);
		value |= HWP_ENERGY_PERF_PREFERENCE(cpu->epp_cached);
		WRITE_ONCE(cpu->hwp_req_cached, value);
	पूर्ण

	value &= ~GENMASK_ULL(31, 0);
	min_perf = HWP_LOWEST_PERF(READ_ONCE(cpu->hwp_cap_cached));

	/* Set hwp_max = hwp_min */
	value |= HWP_MAX_PERF(min_perf);
	value |= HWP_MIN_PERF(min_perf);

	/* Set EPP to min */
	अगर (boot_cpu_has(X86_FEATURE_HWP_EPP))
		value |= HWP_ENERGY_PERF_PREFERENCE(HWP_EPP_POWERSAVE);

	wrmsrl_on_cpu(cpu->cpu, MSR_HWP_REQUEST, value);
पूर्ण

#घोषणा POWER_CTL_EE_ENABLE	1
#घोषणा POWER_CTL_EE_DISABLE	2

अटल पूर्णांक घातer_ctl_ee_state;

अटल व्योम set_घातer_ctl_ee_state(bool input)
अणु
	u64 घातer_ctl;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);
	rdmsrl(MSR_IA32_POWER_CTL, घातer_ctl);
	अगर (input) अणु
		घातer_ctl &= ~BIT(MSR_IA32_POWER_CTL_BIT_EE);
		घातer_ctl_ee_state = POWER_CTL_EE_ENABLE;
	पूर्ण अन्यथा अणु
		घातer_ctl |= BIT(MSR_IA32_POWER_CTL_BIT_EE);
		घातer_ctl_ee_state = POWER_CTL_EE_DISABLE;
	पूर्ण
	wrmsrl(MSR_IA32_POWER_CTL, घातer_ctl);
	mutex_unlock(&पूर्णांकel_pstate_driver_lock);
पूर्ण

अटल व्योम पूर्णांकel_pstate_hwp_enable(काष्ठा cpudata *cpudata);

अटल व्योम पूर्णांकel_pstate_hwp_reenable(काष्ठा cpudata *cpu)
अणु
	पूर्णांकel_pstate_hwp_enable(cpu);
	wrmsrl_on_cpu(cpu->cpu, MSR_HWP_REQUEST, READ_ONCE(cpu->hwp_req_cached));
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_suspend(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];

	pr_debug("CPU %d suspending\n", cpu->cpu);

	cpu->suspended = true;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_resume(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];

	pr_debug("CPU %d resuming\n", cpu->cpu);

	/* Only restore अगर the प्रणाली शेष is changed */
	अगर (घातer_ctl_ee_state == POWER_CTL_EE_ENABLE)
		set_घातer_ctl_ee_state(true);
	अन्यथा अगर (घातer_ctl_ee_state == POWER_CTL_EE_DISABLE)
		set_घातer_ctl_ee_state(false);

	अगर (cpu->suspended && hwp_active) अणु
		mutex_lock(&पूर्णांकel_pstate_limits_lock);

		/* Re-enable HWP, because "online" has not करोne that. */
		पूर्णांकel_pstate_hwp_reenable(cpu);

		mutex_unlock(&पूर्णांकel_pstate_limits_lock);
	पूर्ण

	cpu->suspended = false;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pstate_update_policies(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		cpufreq_update_policy(cpu);
पूर्ण

अटल व्योम पूर्णांकel_pstate_update_max_freq(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_acquire(cpu);
	काष्ठा cpudata *cpudata;

	अगर (!policy)
		वापस;

	cpudata = all_cpu_data[cpu];
	policy->cpuinfo.max_freq = global.turbo_disabled_mf ?
			cpudata->pstate.max_freq : cpudata->pstate.turbo_freq;

	refresh_frequency_limits(policy);

	cpufreq_cpu_release(policy);
पूर्ण

अटल व्योम पूर्णांकel_pstate_update_limits(अचिन्हित पूर्णांक cpu)
अणु
	mutex_lock(&पूर्णांकel_pstate_driver_lock);

	update_turbo_state();
	/*
	 * If turbo has been turned on or off globally, policy limits क्रम
	 * all CPUs need to be updated to reflect that.
	 */
	अगर (global.turbo_disabled_mf != global.turbo_disabled) अणु
		global.turbo_disabled_mf = global.turbo_disabled;
		arch_set_max_freq_ratio(global.turbo_disabled);
		क्रम_each_possible_cpu(cpu)
			पूर्णांकel_pstate_update_max_freq(cpu);
	पूर्ण अन्यथा अणु
		cpufreq_update_policy(cpu);
	पूर्ण

	mutex_unlock(&पूर्णांकel_pstate_driver_lock);
पूर्ण

/************************** sysfs begin ************************/
#घोषणा show_one(file_name, object)					\
	अटल sमाप_प्रकार show_##file_name					\
	(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)	\
	अणु								\
		वापस प्र_लिखो(buf, "%u\n", global.object);		\
	पूर्ण

अटल sमाप_प्रकार पूर्णांकel_pstate_show_status(अक्षर *buf);
अटल पूर्णांक पूर्णांकel_pstate_update_status(स्थिर अक्षर *buf, माप_प्रकार size);

अटल sमाप_प्रकार show_status(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार ret;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);
	ret = पूर्णांकel_pstate_show_status(buf);
	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_status(काष्ठा kobject *a, काष्ठा kobj_attribute *b,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर *p = स_प्रथम(buf, '\n', count);
	पूर्णांक ret;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);
	ret = पूर्णांकel_pstate_update_status(buf, p ? p - buf : count);
	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल sमाप_प्रकार show_turbo_pct(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpudata *cpu;
	पूर्णांक total, no_turbo, turbo_pct;
	uपूर्णांक32_t turbo_fp;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);

	अगर (!पूर्णांकel_pstate_driver) अणु
		mutex_unlock(&पूर्णांकel_pstate_driver_lock);
		वापस -EAGAIN;
	पूर्ण

	cpu = all_cpu_data[0];

	total = cpu->pstate.turbo_pstate - cpu->pstate.min_pstate + 1;
	no_turbo = cpu->pstate.max_pstate - cpu->pstate.min_pstate + 1;
	turbo_fp = भाग_fp(no_turbo, total);
	turbo_pct = 100 - fp_toपूर्णांक(mul_fp(turbo_fp, पूर्णांक_tofp(100)));

	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस प्र_लिखो(buf, "%u\n", turbo_pct);
पूर्ण

अटल sमाप_प्रकार show_num_pstates(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpudata *cpu;
	पूर्णांक total;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);

	अगर (!पूर्णांकel_pstate_driver) अणु
		mutex_unlock(&पूर्णांकel_pstate_driver_lock);
		वापस -EAGAIN;
	पूर्ण

	cpu = all_cpu_data[0];
	total = cpu->pstate.turbo_pstate - cpu->pstate.min_pstate + 1;

	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस प्र_लिखो(buf, "%u\n", total);
पूर्ण

अटल sमाप_प्रकार show_no_turbo(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार ret;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);

	अगर (!पूर्णांकel_pstate_driver) अणु
		mutex_unlock(&पूर्णांकel_pstate_driver_lock);
		वापस -EAGAIN;
	पूर्ण

	update_turbo_state();
	अगर (global.turbo_disabled)
		ret = प्र_लिखो(buf, "%u\n", global.turbo_disabled);
	अन्यथा
		ret = प्र_लिखो(buf, "%u\n", global.no_turbo);

	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_no_turbo(काष्ठा kobject *a, काष्ठा kobj_attribute *b,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &input);
	अगर (ret != 1)
		वापस -EINVAL;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);

	अगर (!पूर्णांकel_pstate_driver) अणु
		mutex_unlock(&पूर्णांकel_pstate_driver_lock);
		वापस -EAGAIN;
	पूर्ण

	mutex_lock(&पूर्णांकel_pstate_limits_lock);

	update_turbo_state();
	अगर (global.turbo_disabled) अणु
		pr_notice_once("Turbo disabled by BIOS or unavailable on processor\n");
		mutex_unlock(&पूर्णांकel_pstate_limits_lock);
		mutex_unlock(&पूर्णांकel_pstate_driver_lock);
		वापस -EPERM;
	पूर्ण

	global.no_turbo = clamp_t(पूर्णांक, input, 0, 1);

	अगर (global.no_turbo) अणु
		काष्ठा cpudata *cpu = all_cpu_data[0];
		पूर्णांक pct = cpu->pstate.max_pstate * 100 / cpu->pstate.turbo_pstate;

		/* Squash the global minimum पूर्णांकo the permitted range. */
		अगर (global.min_perf_pct > pct)
			global.min_perf_pct = pct;
	पूर्ण

	mutex_unlock(&पूर्णांकel_pstate_limits_lock);

	पूर्णांकel_pstate_update_policies();

	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस count;
पूर्ण

अटल व्योम update_qos_request(क्रमागत freq_qos_req_type type)
अणु
	काष्ठा freq_qos_request *req;
	काष्ठा cpufreq_policy *policy;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा cpudata *cpu = all_cpu_data[i];
		अचिन्हित पूर्णांक freq, perf_pct;

		policy = cpufreq_cpu_get(i);
		अगर (!policy)
			जारी;

		req = policy->driver_data;
		cpufreq_cpu_put(policy);

		अगर (!req)
			जारी;

		अगर (hwp_active)
			पूर्णांकel_pstate_get_hwp_cap(cpu);

		अगर (type == FREQ_QOS_MIN) अणु
			perf_pct = global.min_perf_pct;
		पूर्ण अन्यथा अणु
			req++;
			perf_pct = global.max_perf_pct;
		पूर्ण

		freq = DIV_ROUND_UP(cpu->pstate.turbo_freq * perf_pct, 100);

		अगर (freq_qos_update_request(req, freq) < 0)
			pr_warn("Failed to update freq constraint: CPU%d\n", i);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार store_max_perf_pct(काष्ठा kobject *a, काष्ठा kobj_attribute *b,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &input);
	अगर (ret != 1)
		वापस -EINVAL;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);

	अगर (!पूर्णांकel_pstate_driver) अणु
		mutex_unlock(&पूर्णांकel_pstate_driver_lock);
		वापस -EAGAIN;
	पूर्ण

	mutex_lock(&पूर्णांकel_pstate_limits_lock);

	global.max_perf_pct = clamp_t(पूर्णांक, input, global.min_perf_pct, 100);

	mutex_unlock(&पूर्णांकel_pstate_limits_lock);

	अगर (पूर्णांकel_pstate_driver == &पूर्णांकel_pstate)
		पूर्णांकel_pstate_update_policies();
	अन्यथा
		update_qos_request(FREQ_QOS_MAX);

	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार store_min_perf_pct(काष्ठा kobject *a, काष्ठा kobj_attribute *b,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &input);
	अगर (ret != 1)
		वापस -EINVAL;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);

	अगर (!पूर्णांकel_pstate_driver) अणु
		mutex_unlock(&पूर्णांकel_pstate_driver_lock);
		वापस -EAGAIN;
	पूर्ण

	mutex_lock(&पूर्णांकel_pstate_limits_lock);

	global.min_perf_pct = clamp_t(पूर्णांक, input,
				      min_perf_pct_min(), global.max_perf_pct);

	mutex_unlock(&पूर्णांकel_pstate_limits_lock);

	अगर (पूर्णांकel_pstate_driver == &पूर्णांकel_pstate)
		पूर्णांकel_pstate_update_policies();
	अन्यथा
		update_qos_request(FREQ_QOS_MIN);

	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_hwp_dynamic_boost(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", hwp_boost);
पूर्ण

अटल sमाप_प्रकार store_hwp_dynamic_boost(काष्ठा kobject *a,
				       काष्ठा kobj_attribute *b,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक input;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &input);
	अगर (ret)
		वापस ret;

	mutex_lock(&पूर्णांकel_pstate_driver_lock);
	hwp_boost = !!input;
	पूर्णांकel_pstate_update_policies();
	mutex_unlock(&पूर्णांकel_pstate_driver_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_energy_efficiency(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
				      अक्षर *buf)
अणु
	u64 घातer_ctl;
	पूर्णांक enable;

	rdmsrl(MSR_IA32_POWER_CTL, घातer_ctl);
	enable = !!(घातer_ctl & BIT(MSR_IA32_POWER_CTL_BIT_EE));
	वापस प्र_लिखो(buf, "%d\n", !enable);
पूर्ण

अटल sमाप_प्रकार store_energy_efficiency(काष्ठा kobject *a, काष्ठा kobj_attribute *b,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bool input;
	पूर्णांक ret;

	ret = kstrtobool(buf, &input);
	अगर (ret)
		वापस ret;

	set_घातer_ctl_ee_state(input);

	वापस count;
पूर्ण

show_one(max_perf_pct, max_perf_pct);
show_one(min_perf_pct, min_perf_pct);

define_one_global_rw(status);
define_one_global_rw(no_turbo);
define_one_global_rw(max_perf_pct);
define_one_global_rw(min_perf_pct);
define_one_global_ro(turbo_pct);
define_one_global_ro(num_pstates);
define_one_global_rw(hwp_dynamic_boost);
define_one_global_rw(energy_efficiency);

अटल काष्ठा attribute *पूर्णांकel_pstate_attributes[] = अणु
	&status.attr,
	&no_turbo.attr,
	&turbo_pct.attr,
	&num_pstates.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकel_pstate_attr_group = अणु
	.attrs = पूर्णांकel_pstate_attributes,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_pstate_cpu_ee_disable_ids[];

अटल काष्ठा kobject *पूर्णांकel_pstate_kobject;

अटल व्योम __init पूर्णांकel_pstate_sysfs_expose_params(व्योम)
अणु
	पूर्णांक rc;

	पूर्णांकel_pstate_kobject = kobject_create_and_add("intel_pstate",
						&cpu_subsys.dev_root->kobj);
	अगर (WARN_ON(!पूर्णांकel_pstate_kobject))
		वापस;

	rc = sysfs_create_group(पूर्णांकel_pstate_kobject, &पूर्णांकel_pstate_attr_group);
	अगर (WARN_ON(rc))
		वापस;

	/*
	 * If per cpu limits are enक्रमced there are no global limits, so
	 * वापस without creating max/min_perf_pct attributes
	 */
	अगर (per_cpu_limits)
		वापस;

	rc = sysfs_create_file(पूर्णांकel_pstate_kobject, &max_perf_pct.attr);
	WARN_ON(rc);

	rc = sysfs_create_file(पूर्णांकel_pstate_kobject, &min_perf_pct.attr);
	WARN_ON(rc);

	अगर (x86_match_cpu(पूर्णांकel_pstate_cpu_ee_disable_ids)) अणु
		rc = sysfs_create_file(पूर्णांकel_pstate_kobject, &energy_efficiency.attr);
		WARN_ON(rc);
	पूर्ण
पूर्ण

अटल व्योम __init पूर्णांकel_pstate_sysfs_हटाओ(व्योम)
अणु
	अगर (!पूर्णांकel_pstate_kobject)
		वापस;

	sysfs_हटाओ_group(पूर्णांकel_pstate_kobject, &पूर्णांकel_pstate_attr_group);

	अगर (!per_cpu_limits) अणु
		sysfs_हटाओ_file(पूर्णांकel_pstate_kobject, &max_perf_pct.attr);
		sysfs_हटाओ_file(पूर्णांकel_pstate_kobject, &min_perf_pct.attr);

		अगर (x86_match_cpu(पूर्णांकel_pstate_cpu_ee_disable_ids))
			sysfs_हटाओ_file(पूर्णांकel_pstate_kobject, &energy_efficiency.attr);
	पूर्ण

	kobject_put(पूर्णांकel_pstate_kobject);
पूर्ण

अटल व्योम पूर्णांकel_pstate_sysfs_expose_hwp_dynamic_boost(व्योम)
अणु
	पूर्णांक rc;

	अगर (!hwp_active)
		वापस;

	rc = sysfs_create_file(पूर्णांकel_pstate_kobject, &hwp_dynamic_boost.attr);
	WARN_ON_ONCE(rc);
पूर्ण

अटल व्योम पूर्णांकel_pstate_sysfs_hide_hwp_dynamic_boost(व्योम)
अणु
	अगर (!hwp_active)
		वापस;

	sysfs_हटाओ_file(पूर्णांकel_pstate_kobject, &hwp_dynamic_boost.attr);
पूर्ण

/************************** sysfs end ************************/

अटल व्योम पूर्णांकel_pstate_hwp_enable(काष्ठा cpudata *cpudata)
अणु
	/* First disable HWP notअगरication पूर्णांकerrupt as we करोn't process them */
	अगर (boot_cpu_has(X86_FEATURE_HWP_NOTIFY))
		wrmsrl_on_cpu(cpudata->cpu, MSR_HWP_INTERRUPT, 0x00);

	wrmsrl_on_cpu(cpudata->cpu, MSR_PM_ENABLE, 0x1);
	अगर (cpudata->epp_शेष == -EINVAL)
		cpudata->epp_शेष = पूर्णांकel_pstate_get_epp(cpudata, 0);
पूर्ण

अटल पूर्णांक atom_get_min_pstate(व्योम)
अणु
	u64 value;

	rdmsrl(MSR_ATOM_CORE_RATIOS, value);
	वापस (value >> 8) & 0x7F;
पूर्ण

अटल पूर्णांक atom_get_max_pstate(व्योम)
अणु
	u64 value;

	rdmsrl(MSR_ATOM_CORE_RATIOS, value);
	वापस (value >> 16) & 0x7F;
पूर्ण

अटल पूर्णांक atom_get_turbo_pstate(व्योम)
अणु
	u64 value;

	rdmsrl(MSR_ATOM_CORE_TURBO_RATIOS, value);
	वापस value & 0x7F;
पूर्ण

अटल u64 atom_get_val(काष्ठा cpudata *cpudata, पूर्णांक pstate)
अणु
	u64 val;
	पूर्णांक32_t vid_fp;
	u32 vid;

	val = (u64)pstate << 8;
	अगर (global.no_turbo && !global.turbo_disabled)
		val |= (u64)1 << 32;

	vid_fp = cpudata->vid.min + mul_fp(
		पूर्णांक_tofp(pstate - cpudata->pstate.min_pstate),
		cpudata->vid.ratio);

	vid_fp = clamp_t(पूर्णांक32_t, vid_fp, cpudata->vid.min, cpudata->vid.max);
	vid = उच्चमानing_fp(vid_fp);

	अगर (pstate > cpudata->pstate.max_pstate)
		vid = cpudata->vid.turbo;

	वापस val | vid;
पूर्ण

अटल पूर्णांक silvermont_get_scaling(व्योम)
अणु
	u64 value;
	पूर्णांक i;
	/* Defined in Table 35-6 from SDM (Sept 2015) */
	अटल पूर्णांक silvermont_freq_table[] = अणु
		83300, 100000, 133300, 116700, 80000पूर्ण;

	rdmsrl(MSR_FSB_FREQ, value);
	i = value & 0x7;
	WARN_ON(i > 4);

	वापस silvermont_freq_table[i];
पूर्ण

अटल पूर्णांक airmont_get_scaling(व्योम)
अणु
	u64 value;
	पूर्णांक i;
	/* Defined in Table 35-10 from SDM (Sept 2015) */
	अटल पूर्णांक airmont_freq_table[] = अणु
		83300, 100000, 133300, 116700, 80000,
		93300, 90000, 88900, 87500पूर्ण;

	rdmsrl(MSR_FSB_FREQ, value);
	i = value & 0xF;
	WARN_ON(i > 8);

	वापस airmont_freq_table[i];
पूर्ण

अटल व्योम atom_get_vid(काष्ठा cpudata *cpudata)
अणु
	u64 value;

	rdmsrl(MSR_ATOM_CORE_VIDS, value);
	cpudata->vid.min = पूर्णांक_tofp((value >> 8) & 0x7f);
	cpudata->vid.max = पूर्णांक_tofp((value >> 16) & 0x7f);
	cpudata->vid.ratio = भाग_fp(
		cpudata->vid.max - cpudata->vid.min,
		पूर्णांक_tofp(cpudata->pstate.max_pstate -
			cpudata->pstate.min_pstate));

	rdmsrl(MSR_ATOM_CORE_TURBO_VIDS, value);
	cpudata->vid.turbo = value & 0x7f;
पूर्ण

अटल पूर्णांक core_get_min_pstate(व्योम)
अणु
	u64 value;

	rdmsrl(MSR_PLATFORM_INFO, value);
	वापस (value >> 40) & 0xFF;
पूर्ण

अटल पूर्णांक core_get_max_pstate_physical(व्योम)
अणु
	u64 value;

	rdmsrl(MSR_PLATFORM_INFO, value);
	वापस (value >> 8) & 0xFF;
पूर्ण

अटल पूर्णांक core_get_tdp_ratio(u64 plat_info)
अणु
	/* Check how many TDP levels present */
	अगर (plat_info & 0x600000000) अणु
		u64 tdp_ctrl;
		u64 tdp_ratio;
		पूर्णांक tdp_msr;
		पूर्णांक err;

		/* Get the TDP level (0, 1, 2) to get ratios */
		err = rdmsrl_safe(MSR_CONFIG_TDP_CONTROL, &tdp_ctrl);
		अगर (err)
			वापस err;

		/* TDP MSR are continuous starting at 0x648 */
		tdp_msr = MSR_CONFIG_TDP_NOMINAL + (tdp_ctrl & 0x03);
		err = rdmsrl_safe(tdp_msr, &tdp_ratio);
		अगर (err)
			वापस err;

		/* For level 1 and 2, bits[23:16] contain the ratio */
		अगर (tdp_ctrl & 0x03)
			tdp_ratio >>= 16;

		tdp_ratio &= 0xff; /* ratios are only 8 bits दीर्घ */
		pr_debug("tdp_ratio %x\n", (पूर्णांक)tdp_ratio);

		वापस (पूर्णांक)tdp_ratio;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक core_get_max_pstate(व्योम)
अणु
	u64 tar;
	u64 plat_info;
	पूर्णांक max_pstate;
	पूर्णांक tdp_ratio;
	पूर्णांक err;

	rdmsrl(MSR_PLATFORM_INFO, plat_info);
	max_pstate = (plat_info >> 8) & 0xFF;

	tdp_ratio = core_get_tdp_ratio(plat_info);
	अगर (tdp_ratio <= 0)
		वापस max_pstate;

	अगर (hwp_active) अणु
		/* Turbo activation ratio is not used on HWP platक्रमms */
		वापस tdp_ratio;
	पूर्ण

	err = rdmsrl_safe(MSR_TURBO_ACTIVATION_RATIO, &tar);
	अगर (!err) अणु
		पूर्णांक tar_levels;

		/* Do some sanity checking क्रम safety */
		tar_levels = tar & 0xff;
		अगर (tdp_ratio - 1 == tar_levels) अणु
			max_pstate = tar_levels;
			pr_debug("max_pstate=TAC %x\n", max_pstate);
		पूर्ण
	पूर्ण

	वापस max_pstate;
पूर्ण

अटल पूर्णांक core_get_turbo_pstate(व्योम)
अणु
	u64 value;
	पूर्णांक nont, ret;

	rdmsrl(MSR_TURBO_RATIO_LIMIT, value);
	nont = core_get_max_pstate();
	ret = (value) & 255;
	अगर (ret <= nont)
		ret = nont;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक core_get_scaling(व्योम)
अणु
	वापस 100000;
पूर्ण

अटल u64 core_get_val(काष्ठा cpudata *cpudata, पूर्णांक pstate)
अणु
	u64 val;

	val = (u64)pstate << 8;
	अगर (global.no_turbo && !global.turbo_disabled)
		val |= (u64)1 << 32;

	वापस val;
पूर्ण

अटल पूर्णांक knl_get_aperf_mperf_shअगरt(व्योम)
अणु
	वापस 10;
पूर्ण

अटल पूर्णांक knl_get_turbo_pstate(व्योम)
अणु
	u64 value;
	पूर्णांक nont, ret;

	rdmsrl(MSR_TURBO_RATIO_LIMIT, value);
	nont = core_get_max_pstate();
	ret = (((value) >> 8) & 0xFF);
	अगर (ret <= nont)
		ret = nont;
	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_pstate_set_pstate(काष्ठा cpudata *cpu, पूर्णांक pstate)
अणु
	trace_cpu_frequency(pstate * cpu->pstate.scaling, cpu->cpu);
	cpu->pstate.current_pstate = pstate;
	/*
	 * Generally, there is no guarantee that this code will always run on
	 * the CPU being updated, so क्रमce the रेजिस्टर update to run on the
	 * right CPU.
	 */
	wrmsrl_on_cpu(cpu->cpu, MSR_IA32_PERF_CTL,
		      pstate_funcs.get_val(cpu, pstate));
पूर्ण

अटल व्योम पूर्णांकel_pstate_set_min_pstate(काष्ठा cpudata *cpu)
अणु
	पूर्णांकel_pstate_set_pstate(cpu, cpu->pstate.min_pstate);
पूर्ण

अटल व्योम पूर्णांकel_pstate_max_within_limits(काष्ठा cpudata *cpu)
अणु
	पूर्णांक pstate = max(cpu->pstate.min_pstate, cpu->max_perf_ratio);

	update_turbo_state();
	पूर्णांकel_pstate_set_pstate(cpu, pstate);
पूर्ण

अटल व्योम पूर्णांकel_pstate_get_cpu_pstates(काष्ठा cpudata *cpu)
अणु
	cpu->pstate.min_pstate = pstate_funcs.get_min();
	cpu->pstate.max_pstate_physical = pstate_funcs.get_max_physical();
	cpu->pstate.scaling = pstate_funcs.get_scaling();

	अगर (hwp_active && !hwp_mode_bdw) अणु
		__पूर्णांकel_pstate_get_hwp_cap(cpu);
	पूर्ण अन्यथा अणु
		cpu->pstate.max_pstate = pstate_funcs.get_max();
		cpu->pstate.turbo_pstate = pstate_funcs.get_turbo();
	पूर्ण

	cpu->pstate.max_freq = cpu->pstate.max_pstate * cpu->pstate.scaling;
	cpu->pstate.turbo_freq = cpu->pstate.turbo_pstate * cpu->pstate.scaling;

	अगर (pstate_funcs.get_aperf_mperf_shअगरt)
		cpu->aperf_mperf_shअगरt = pstate_funcs.get_aperf_mperf_shअगरt();

	अगर (pstate_funcs.get_vid)
		pstate_funcs.get_vid(cpu);

	पूर्णांकel_pstate_set_min_pstate(cpu);
पूर्ण

/*
 * Long hold समय will keep high perf limits क्रम दीर्घ समय,
 * which negatively impacts perf/watt क्रम some workloads,
 * like specघातer. 3ms is based on experiements on some
 * workoads.
 */
अटल पूर्णांक hwp_boost_hold_समय_ns = 3 * NSEC_PER_MSEC;

अटल अंतरभूत व्योम पूर्णांकel_pstate_hwp_boost_up(काष्ठा cpudata *cpu)
अणु
	u64 hwp_req = READ_ONCE(cpu->hwp_req_cached);
	u64 hwp_cap = READ_ONCE(cpu->hwp_cap_cached);
	u32 max_limit = (hwp_req & 0xff00) >> 8;
	u32 min_limit = (hwp_req & 0xff);
	u32 boost_level1;

	/*
	 * Cases to consider (User changes via sysfs or boot समय):
	 * If, P0 (Turbo max) = P1 (Guaranteed max) = min:
	 *	No boost, वापस.
	 * If, P0 (Turbo max) > P1 (Guaranteed max) = min:
	 *     Should result in one level boost only क्रम P0.
	 * If, P0 (Turbo max) = P1 (Guaranteed max) > min:
	 *     Should result in two level boost:
	 *         (min + p1)/2 and P1.
	 * If, P0 (Turbo max) > P1 (Guaranteed max) > min:
	 *     Should result in three level boost:
	 *        (min + p1)/2, P1 and P0.
	 */

	/* If max and min are equal or alपढ़ोy at max, nothing to boost */
	अगर (max_limit == min_limit || cpu->hwp_boost_min >= max_limit)
		वापस;

	अगर (!cpu->hwp_boost_min)
		cpu->hwp_boost_min = min_limit;

	/* level at half way mark between min and guranteed */
	boost_level1 = (HWP_GUARANTEED_PERF(hwp_cap) + min_limit) >> 1;

	अगर (cpu->hwp_boost_min < boost_level1)
		cpu->hwp_boost_min = boost_level1;
	अन्यथा अगर (cpu->hwp_boost_min < HWP_GUARANTEED_PERF(hwp_cap))
		cpu->hwp_boost_min = HWP_GUARANTEED_PERF(hwp_cap);
	अन्यथा अगर (cpu->hwp_boost_min == HWP_GUARANTEED_PERF(hwp_cap) &&
		 max_limit != HWP_GUARANTEED_PERF(hwp_cap))
		cpu->hwp_boost_min = max_limit;
	अन्यथा
		वापस;

	hwp_req = (hwp_req & ~GENMASK_ULL(7, 0)) | cpu->hwp_boost_min;
	wrmsrl(MSR_HWP_REQUEST, hwp_req);
	cpu->last_update = cpu->sample.समय;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pstate_hwp_boost_करोwn(काष्ठा cpudata *cpu)
अणु
	अगर (cpu->hwp_boost_min) अणु
		bool expired;

		/* Check अगर we are idle क्रम hold समय to boost करोwn */
		expired = समय_after64(cpu->sample.समय, cpu->last_update +
				       hwp_boost_hold_समय_ns);
		अगर (expired) अणु
			wrmsrl(MSR_HWP_REQUEST, cpu->hwp_req_cached);
			cpu->hwp_boost_min = 0;
		पूर्ण
	पूर्ण
	cpu->last_update = cpu->sample.समय;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pstate_update_util_hwp_local(काष्ठा cpudata *cpu,
						      u64 समय)
अणु
	cpu->sample.समय = समय;

	अगर (cpu->sched_flags & SCHED_CPUFREQ_IOWAIT) अणु
		bool करो_io = false;

		cpu->sched_flags = 0;
		/*
		 * Set ioरुको_boost flag and update समय. Since IO WAIT flag
		 * is set all the समय, we can't just conclude that there is
		 * some IO bound activity is scheduled on this CPU with just
		 * one occurrence. If we receive at least two in two
		 * consecutive ticks, then we treat as boost candidate.
		 */
		अगर (समय_beक्रमe64(समय, cpu->last_io_update + 2 * TICK_NSEC))
			करो_io = true;

		cpu->last_io_update = समय;

		अगर (करो_io)
			पूर्णांकel_pstate_hwp_boost_up(cpu);

	पूर्ण अन्यथा अणु
		पूर्णांकel_pstate_hwp_boost_करोwn(cpu);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pstate_update_util_hwp(काष्ठा update_util_data *data,
						u64 समय, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा cpudata *cpu = container_of(data, काष्ठा cpudata, update_util);

	cpu->sched_flags |= flags;

	अगर (smp_processor_id() == cpu->cpu)
		पूर्णांकel_pstate_update_util_hwp_local(cpu, समय);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pstate_calc_avg_perf(काष्ठा cpudata *cpu)
अणु
	काष्ठा sample *sample = &cpu->sample;

	sample->core_avg_perf = भाग_ext_fp(sample->aperf, sample->mperf);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pstate_sample(काष्ठा cpudata *cpu, u64 समय)
अणु
	u64 aperf, mperf;
	अचिन्हित दीर्घ flags;
	u64 tsc;

	local_irq_save(flags);
	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);
	tsc = rdtsc();
	अगर (cpu->prev_mperf == mperf || cpu->prev_tsc == tsc) अणु
		local_irq_restore(flags);
		वापस false;
	पूर्ण
	local_irq_restore(flags);

	cpu->last_sample_समय = cpu->sample.समय;
	cpu->sample.समय = समय;
	cpu->sample.aperf = aperf;
	cpu->sample.mperf = mperf;
	cpu->sample.tsc =  tsc;
	cpu->sample.aperf -= cpu->prev_aperf;
	cpu->sample.mperf -= cpu->prev_mperf;
	cpu->sample.tsc -= cpu->prev_tsc;

	cpu->prev_aperf = aperf;
	cpu->prev_mperf = mperf;
	cpu->prev_tsc = tsc;
	/*
	 * First समय this function is invoked in a given cycle, all of the
	 * previous sample data fields are equal to zero or stale and they must
	 * be populated with meaningful numbers क्रम things to work, so assume
	 * that sample.समय will always be reset beक्रमe setting the utilization
	 * update hook and make the caller skip the sample then.
	 */
	अगर (cpu->last_sample_समय) अणु
		पूर्णांकel_pstate_calc_avg_perf(cpu);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक32_t get_avg_frequency(काष्ठा cpudata *cpu)
अणु
	वापस mul_ext_fp(cpu->sample.core_avg_perf, cpu_khz);
पूर्ण

अटल अंतरभूत पूर्णांक32_t get_avg_pstate(काष्ठा cpudata *cpu)
अणु
	वापस mul_ext_fp(cpu->pstate.max_pstate_physical,
			  cpu->sample.core_avg_perf);
पूर्ण

अटल अंतरभूत पूर्णांक32_t get_target_pstate(काष्ठा cpudata *cpu)
अणु
	काष्ठा sample *sample = &cpu->sample;
	पूर्णांक32_t busy_frac;
	पूर्णांक target, avg_pstate;

	busy_frac = भाग_fp(sample->mperf << cpu->aperf_mperf_shअगरt,
			   sample->tsc);

	अगर (busy_frac < cpu->ioरुको_boost)
		busy_frac = cpu->ioरुको_boost;

	sample->busy_scaled = busy_frac * 100;

	target = global.no_turbo || global.turbo_disabled ?
			cpu->pstate.max_pstate : cpu->pstate.turbo_pstate;
	target += target >> 2;
	target = mul_fp(target, busy_frac);
	अगर (target < cpu->pstate.min_pstate)
		target = cpu->pstate.min_pstate;

	/*
	 * If the average P-state during the previous cycle was higher than the
	 * current target, add 50% of the dअगरference to the target to reduce
	 * possible perक्रमmance oscillations and offset possible perक्रमmance
	 * loss related to moving the workload from one CPU to another within
	 * a package/module.
	 */
	avg_pstate = get_avg_pstate(cpu);
	अगर (avg_pstate > target)
		target += (avg_pstate - target) >> 1;

	वापस target;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_prepare_request(काष्ठा cpudata *cpu, पूर्णांक pstate)
अणु
	पूर्णांक min_pstate = max(cpu->pstate.min_pstate, cpu->min_perf_ratio);
	पूर्णांक max_pstate = max(min_pstate, cpu->max_perf_ratio);

	वापस clamp_t(पूर्णांक, pstate, min_pstate, max_pstate);
पूर्ण

अटल व्योम पूर्णांकel_pstate_update_pstate(काष्ठा cpudata *cpu, पूर्णांक pstate)
अणु
	अगर (pstate == cpu->pstate.current_pstate)
		वापस;

	cpu->pstate.current_pstate = pstate;
	wrmsrl(MSR_IA32_PERF_CTL, pstate_funcs.get_val(cpu, pstate));
पूर्ण

अटल व्योम पूर्णांकel_pstate_adjust_pstate(काष्ठा cpudata *cpu)
अणु
	पूर्णांक from = cpu->pstate.current_pstate;
	काष्ठा sample *sample;
	पूर्णांक target_pstate;

	update_turbo_state();

	target_pstate = get_target_pstate(cpu);
	target_pstate = पूर्णांकel_pstate_prepare_request(cpu, target_pstate);
	trace_cpu_frequency(target_pstate * cpu->pstate.scaling, cpu->cpu);
	पूर्णांकel_pstate_update_pstate(cpu, target_pstate);

	sample = &cpu->sample;
	trace_pstate_sample(mul_ext_fp(100, sample->core_avg_perf),
		fp_toपूर्णांक(sample->busy_scaled),
		from,
		cpu->pstate.current_pstate,
		sample->mperf,
		sample->aperf,
		sample->tsc,
		get_avg_frequency(cpu),
		fp_toपूर्णांक(cpu->ioरुको_boost * 100));
पूर्ण

अटल व्योम पूर्णांकel_pstate_update_util(काष्ठा update_util_data *data, u64 समय,
				     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा cpudata *cpu = container_of(data, काष्ठा cpudata, update_util);
	u64 delta_ns;

	/* Don't allow remote callbacks */
	अगर (smp_processor_id() != cpu->cpu)
		वापस;

	delta_ns = समय - cpu->last_update;
	अगर (flags & SCHED_CPUFREQ_IOWAIT) अणु
		/* Start over अगर the CPU may have been idle. */
		अगर (delta_ns > TICK_NSEC) अणु
			cpu->ioरुको_boost = ONE_EIGHTH_FP;
		पूर्ण अन्यथा अगर (cpu->ioरुको_boost >= ONE_EIGHTH_FP) अणु
			cpu->ioरुको_boost <<= 1;
			अगर (cpu->ioरुको_boost > पूर्णांक_tofp(1))
				cpu->ioरुको_boost = पूर्णांक_tofp(1);
		पूर्ण अन्यथा अणु
			cpu->ioरुको_boost = ONE_EIGHTH_FP;
		पूर्ण
	पूर्ण अन्यथा अगर (cpu->ioरुको_boost) अणु
		/* Clear ioरुको_boost अगर the CPU may have been idle. */
		अगर (delta_ns > TICK_NSEC)
			cpu->ioरुको_boost = 0;
		अन्यथा
			cpu->ioरुको_boost >>= 1;
	पूर्ण
	cpu->last_update = समय;
	delta_ns = समय - cpu->sample.समय;
	अगर ((s64)delta_ns < INTEL_PSTATE_SAMPLING_INTERVAL)
		वापस;

	अगर (पूर्णांकel_pstate_sample(cpu, समय))
		पूर्णांकel_pstate_adjust_pstate(cpu);
पूर्ण

अटल काष्ठा pstate_funcs core_funcs = अणु
	.get_max = core_get_max_pstate,
	.get_max_physical = core_get_max_pstate_physical,
	.get_min = core_get_min_pstate,
	.get_turbo = core_get_turbo_pstate,
	.get_scaling = core_get_scaling,
	.get_val = core_get_val,
पूर्ण;

अटल स्थिर काष्ठा pstate_funcs silvermont_funcs = अणु
	.get_max = atom_get_max_pstate,
	.get_max_physical = atom_get_max_pstate,
	.get_min = atom_get_min_pstate,
	.get_turbo = atom_get_turbo_pstate,
	.get_val = atom_get_val,
	.get_scaling = silvermont_get_scaling,
	.get_vid = atom_get_vid,
पूर्ण;

अटल स्थिर काष्ठा pstate_funcs airmont_funcs = अणु
	.get_max = atom_get_max_pstate,
	.get_max_physical = atom_get_max_pstate,
	.get_min = atom_get_min_pstate,
	.get_turbo = atom_get_turbo_pstate,
	.get_val = atom_get_val,
	.get_scaling = airmont_get_scaling,
	.get_vid = atom_get_vid,
पूर्ण;

अटल स्थिर काष्ठा pstate_funcs knl_funcs = अणु
	.get_max = core_get_max_pstate,
	.get_max_physical = core_get_max_pstate_physical,
	.get_min = core_get_min_pstate,
	.get_turbo = knl_get_turbo_pstate,
	.get_aperf_mperf_shअगरt = knl_get_aperf_mperf_shअगरt,
	.get_scaling = core_get_scaling,
	.get_val = core_get_val,
पूर्ण;

#घोषणा X86_MATCH(model, policy)					 \
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL, 6, INTEL_FAM6_##model, \
					   X86_FEATURE_APERFMPERF, &policy)

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_pstate_cpu_ids[] = अणु
	X86_MATCH(SANDYBRIDGE,		core_funcs),
	X86_MATCH(SANDYBRIDGE_X,	core_funcs),
	X86_MATCH(ATOM_SILVERMONT,	silvermont_funcs),
	X86_MATCH(IVYBRIDGE,		core_funcs),
	X86_MATCH(HASWELL,		core_funcs),
	X86_MATCH(BROADWELL,		core_funcs),
	X86_MATCH(IVYBRIDGE_X,		core_funcs),
	X86_MATCH(HASWELL_X,		core_funcs),
	X86_MATCH(HASWELL_L,		core_funcs),
	X86_MATCH(HASWELL_G,		core_funcs),
	X86_MATCH(BROADWELL_G,		core_funcs),
	X86_MATCH(ATOM_AIRMONT,		airmont_funcs),
	X86_MATCH(SKYLAKE_L,		core_funcs),
	X86_MATCH(BROADWELL_X,		core_funcs),
	X86_MATCH(SKYLAKE,		core_funcs),
	X86_MATCH(BROADWELL_D,		core_funcs),
	X86_MATCH(XEON_PHI_KNL,		knl_funcs),
	X86_MATCH(XEON_PHI_KNM,		knl_funcs),
	X86_MATCH(ATOM_GOLDMONT,	core_funcs),
	X86_MATCH(ATOM_GOLDMONT_PLUS,	core_funcs),
	X86_MATCH(SKYLAKE_X,		core_funcs),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, पूर्णांकel_pstate_cpu_ids);

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_pstate_cpu_oob_ids[] __initस्थिर = अणु
	X86_MATCH(BROADWELL_D,		core_funcs),
	X86_MATCH(BROADWELL_X,		core_funcs),
	X86_MATCH(SKYLAKE_X,		core_funcs),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_pstate_cpu_ee_disable_ids[] = अणु
	X86_MATCH(KABYLAKE,		core_funcs),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_pstate_hwp_boost_ids[] = अणु
	X86_MATCH(SKYLAKE_X,		core_funcs),
	X86_MATCH(SKYLAKE,		core_funcs),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक पूर्णांकel_pstate_init_cpu(अचिन्हित पूर्णांक cpunum)
अणु
	काष्ठा cpudata *cpu;

	cpu = all_cpu_data[cpunum];

	अगर (!cpu) अणु
		cpu = kzalloc(माप(*cpu), GFP_KERNEL);
		अगर (!cpu)
			वापस -ENOMEM;

		all_cpu_data[cpunum] = cpu;

		cpu->cpu = cpunum;

		cpu->epp_शेष = -EINVAL;

		अगर (hwp_active) अणु
			स्थिर काष्ठा x86_cpu_id *id;

			पूर्णांकel_pstate_hwp_enable(cpu);

			id = x86_match_cpu(पूर्णांकel_pstate_hwp_boost_ids);
			अगर (id && पूर्णांकel_pstate_acpi_pm_profile_server())
				hwp_boost = true;
		पूर्ण
	पूर्ण अन्यथा अगर (hwp_active) अणु
		/*
		 * Re-enable HWP in हाल this happens after a resume from ACPI
		 * S3 अगर the CPU was offline during the whole प्रणाली/resume
		 * cycle.
		 */
		पूर्णांकel_pstate_hwp_reenable(cpu);
	पूर्ण

	cpu->epp_घातersave = -EINVAL;
	cpu->epp_policy = 0;

	पूर्णांकel_pstate_get_cpu_pstates(cpu);

	pr_debug("controlling: cpu %d\n", cpunum);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pstate_set_update_util_hook(अचिन्हित पूर्णांक cpu_num)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[cpu_num];

	अगर (hwp_active && !hwp_boost)
		वापस;

	अगर (cpu->update_util_set)
		वापस;

	/* Prevent पूर्णांकel_pstate_update_util() from using stale data. */
	cpu->sample.समय = 0;
	cpufreq_add_update_util_hook(cpu_num, &cpu->update_util,
				     (hwp_active ?
				      पूर्णांकel_pstate_update_util_hwp :
				      पूर्णांकel_pstate_update_util));
	cpu->update_util_set = true;
पूर्ण

अटल व्योम पूर्णांकel_pstate_clear_update_util_hook(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpudata *cpu_data = all_cpu_data[cpu];

	अगर (!cpu_data->update_util_set)
		वापस;

	cpufreq_हटाओ_update_util_hook(cpu);
	cpu_data->update_util_set = false;
	synchronize_rcu();
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_get_max_freq(काष्ठा cpudata *cpu)
अणु
	वापस global.turbo_disabled || global.no_turbo ?
			cpu->pstate.max_freq : cpu->pstate.turbo_freq;
पूर्ण

अटल व्योम पूर्णांकel_pstate_update_perf_limits(काष्ठा cpudata *cpu,
					    अचिन्हित पूर्णांक policy_min,
					    अचिन्हित पूर्णांक policy_max)
अणु
	पूर्णांक scaling = cpu->pstate.scaling;
	पूर्णांक32_t max_policy_perf, min_policy_perf;

	/*
	 * HWP needs some special consideration, because HWP_REQUEST uses
	 * असलtract values to represent perक्रमmance rather than pure ratios.
	 */
	अगर (hwp_active)
		पूर्णांकel_pstate_get_hwp_cap(cpu);

	max_policy_perf = policy_max / scaling;
	अगर (policy_max == policy_min) अणु
		min_policy_perf = max_policy_perf;
	पूर्ण अन्यथा अणु
		min_policy_perf = policy_min / scaling;
		min_policy_perf = clamp_t(पूर्णांक32_t, min_policy_perf,
					  0, max_policy_perf);
	पूर्ण

	pr_debug("cpu:%d min_policy_perf:%d max_policy_perf:%d\n",
		 cpu->cpu, min_policy_perf, max_policy_perf);

	/* Normalize user input to [min_perf, max_perf] */
	अगर (per_cpu_limits) अणु
		cpu->min_perf_ratio = min_policy_perf;
		cpu->max_perf_ratio = max_policy_perf;
	पूर्ण अन्यथा अणु
		पूर्णांक turbo_max = cpu->pstate.turbo_pstate;
		पूर्णांक32_t global_min, global_max;

		/* Global limits are in percent of the maximum turbo P-state. */
		global_max = DIV_ROUND_UP(turbo_max * global.max_perf_pct, 100);
		global_min = DIV_ROUND_UP(turbo_max * global.min_perf_pct, 100);
		global_min = clamp_t(पूर्णांक32_t, global_min, 0, global_max);

		pr_debug("cpu:%d global_min:%d global_max:%d\n", cpu->cpu,
			 global_min, global_max);

		cpu->min_perf_ratio = max(min_policy_perf, global_min);
		cpu->min_perf_ratio = min(cpu->min_perf_ratio, max_policy_perf);
		cpu->max_perf_ratio = min(max_policy_perf, global_max);
		cpu->max_perf_ratio = max(min_policy_perf, cpu->max_perf_ratio);

		/* Make sure min_perf <= max_perf */
		cpu->min_perf_ratio = min(cpu->min_perf_ratio,
					  cpu->max_perf_ratio);

	पूर्ण
	pr_debug("cpu:%d max_perf_ratio:%d min_perf_ratio:%d\n", cpu->cpu,
		 cpu->max_perf_ratio,
		 cpu->min_perf_ratio);
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_set_policy(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpudata *cpu;

	अगर (!policy->cpuinfo.max_freq)
		वापस -ENODEV;

	pr_debug("set_policy cpuinfo.max %u policy->max %u\n",
		 policy->cpuinfo.max_freq, policy->max);

	cpu = all_cpu_data[policy->cpu];
	cpu->policy = policy->policy;

	mutex_lock(&पूर्णांकel_pstate_limits_lock);

	पूर्णांकel_pstate_update_perf_limits(cpu, policy->min, policy->max);

	अगर (cpu->policy == CPUFREQ_POLICY_PERFORMANCE) अणु
		/*
		 * NOHZ_FULL CPUs need this as the governor callback may not
		 * be invoked on them.
		 */
		पूर्णांकel_pstate_clear_update_util_hook(policy->cpu);
		पूर्णांकel_pstate_max_within_limits(cpu);
	पूर्ण अन्यथा अणु
		पूर्णांकel_pstate_set_update_util_hook(policy->cpu);
	पूर्ण

	अगर (hwp_active) अणु
		/*
		 * When hwp_boost was active beक्रमe and dynamically it
		 * was turned off, in that हाल we need to clear the
		 * update util hook.
		 */
		अगर (!hwp_boost)
			पूर्णांकel_pstate_clear_update_util_hook(policy->cpu);
		पूर्णांकel_pstate_hwp_set(policy->cpu);
	पूर्ण

	mutex_unlock(&पूर्णांकel_pstate_limits_lock);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pstate_adjust_policy_max(काष्ठा cpudata *cpu,
					   काष्ठा cpufreq_policy_data *policy)
अणु
	अगर (!hwp_active &&
	    cpu->pstate.max_pstate_physical > cpu->pstate.max_pstate &&
	    policy->max < policy->cpuinfo.max_freq &&
	    policy->max > cpu->pstate.max_freq) अणु
		pr_debug("policy->max > max non turbo frequency\n");
		policy->max = policy->cpuinfo.max_freq;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pstate_verअगरy_cpu_policy(काष्ठा cpudata *cpu,
					   काष्ठा cpufreq_policy_data *policy)
अणु
	पूर्णांक max_freq;

	update_turbo_state();
	अगर (hwp_active) अणु
		पूर्णांकel_pstate_get_hwp_cap(cpu);
		max_freq = global.no_turbo || global.turbo_disabled ?
				cpu->pstate.max_freq : cpu->pstate.turbo_freq;
	पूर्ण अन्यथा अणु
		max_freq = पूर्णांकel_pstate_get_max_freq(cpu);
	पूर्ण
	cpufreq_verअगरy_within_limits(policy, policy->cpuinfo.min_freq, max_freq);

	पूर्णांकel_pstate_adjust_policy_max(cpu, policy);
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_verअगरy_policy(काष्ठा cpufreq_policy_data *policy)
अणु
	पूर्णांकel_pstate_verअगरy_cpu_policy(all_cpu_data[policy->cpu], policy);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_cpu_offline(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];

	pr_debug("CPU %d going offline\n", cpu->cpu);

	अगर (cpu->suspended)
		वापस 0;

	/*
	 * If the CPU is an SMT thपढ़ो and it goes offline with the perक्रमmance
	 * settings dअगरferent from the minimum, it will prevent its sibling
	 * from getting to lower perक्रमmance levels, so क्रमce the minimum
	 * perक्रमmance on CPU offline to prevent that from happening.
	 */
	अगर (hwp_active)
		पूर्णांकel_pstate_hwp_offline(cpu);
	अन्यथा
		पूर्णांकel_pstate_set_min_pstate(cpu);

	पूर्णांकel_pstate_निकास_perf_limits(policy);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_cpu_online(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];

	pr_debug("CPU %d going online\n", cpu->cpu);

	पूर्णांकel_pstate_init_acpi_perf_limits(policy);

	अगर (hwp_active) अणु
		/*
		 * Re-enable HWP and clear the "suspended" flag to let "resume"
		 * know that it need not करो that.
		 */
		पूर्णांकel_pstate_hwp_reenable(cpu);
		cpu->suspended = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pstate_stop_cpu(काष्ठा cpufreq_policy *policy)
अणु
	pr_debug("CPU %d stopping\n", policy->cpu);

	पूर्णांकel_pstate_clear_update_util_hook(policy->cpu);
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	pr_debug("CPU %d exiting\n", policy->cpu);

	policy->fast_चयन_possible = false;

	वापस 0;
पूर्ण

अटल पूर्णांक __पूर्णांकel_pstate_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpudata *cpu;
	पूर्णांक rc;

	rc = पूर्णांकel_pstate_init_cpu(policy->cpu);
	अगर (rc)
		वापस rc;

	cpu = all_cpu_data[policy->cpu];

	cpu->max_perf_ratio = 0xFF;
	cpu->min_perf_ratio = 0;

	/* cpuinfo and शेष policy values */
	policy->cpuinfo.min_freq = cpu->pstate.min_pstate * cpu->pstate.scaling;
	update_turbo_state();
	global.turbo_disabled_mf = global.turbo_disabled;
	policy->cpuinfo.max_freq = global.turbo_disabled ?
			cpu->pstate.max_freq : cpu->pstate.turbo_freq;

	policy->min = policy->cpuinfo.min_freq;
	policy->max = policy->cpuinfo.max_freq;

	पूर्णांकel_pstate_init_acpi_perf_limits(policy);

	policy->fast_चयन_possible = true;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	पूर्णांक ret = __पूर्णांकel_pstate_cpu_init(policy);

	अगर (ret)
		वापस ret;

	/*
	 * Set the policy to घातersave to provide a valid fallback value in हाल
	 * the शेष cpufreq governor is neither घातersave nor perक्रमmance.
	 */
	policy->policy = CPUFREQ_POLICY_POWERSAVE;

	अगर (hwp_active) अणु
		काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];

		cpu->epp_cached = पूर्णांकel_pstate_get_epp(cpu, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver पूर्णांकel_pstate = अणु
	.flags		= CPUFREQ_CONST_LOOPS,
	.verअगरy		= पूर्णांकel_pstate_verअगरy_policy,
	.setpolicy	= पूर्णांकel_pstate_set_policy,
	.suspend	= पूर्णांकel_pstate_suspend,
	.resume		= पूर्णांकel_pstate_resume,
	.init		= पूर्णांकel_pstate_cpu_init,
	.निकास		= पूर्णांकel_pstate_cpu_निकास,
	.stop_cpu	= पूर्णांकel_pstate_stop_cpu,
	.offline	= पूर्णांकel_pstate_cpu_offline,
	.online		= पूर्णांकel_pstate_cpu_online,
	.update_limits	= पूर्णांकel_pstate_update_limits,
	.name		= "intel_pstate",
पूर्ण;

अटल पूर्णांक पूर्णांकel_cpufreq_verअगरy_policy(काष्ठा cpufreq_policy_data *policy)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];

	पूर्णांकel_pstate_verअगरy_cpu_policy(cpu, policy);
	पूर्णांकel_pstate_update_perf_limits(cpu, policy->min, policy->max);

	वापस 0;
पूर्ण

/* Use of trace in passive mode:
 *
 * In passive mode the trace core_busy field (also known as the
 * perक्रमmance field, and lablelled as such on the graphs; also known as
 * core_avg_perf) is not needed and so is re-asचिन्हित to indicate अगर the
 * driver call was via the normal or fast चयन path. Various graphs
 * output from the पूर्णांकel_pstate_tracer.py utility that include core_busy
 * (or perक्रमmance or core_avg_perf) have a fixed y-axis from 0 to 100%,
 * so we use 10 to indicate the normal path through the driver, and
 * 90 to indicate the fast चयन path through the driver.
 * The scaled_busy field is not used, and is set to 0.
 */

#घोषणा	INTEL_PSTATE_TRACE_TARGET 10
#घोषणा	INTEL_PSTATE_TRACE_FAST_SWITCH 90

अटल व्योम पूर्णांकel_cpufreq_trace(काष्ठा cpudata *cpu, अचिन्हित पूर्णांक trace_type, पूर्णांक old_pstate)
अणु
	काष्ठा sample *sample;

	अगर (!trace_pstate_sample_enabled())
		वापस;

	अगर (!पूर्णांकel_pstate_sample(cpu, kसमय_get()))
		वापस;

	sample = &cpu->sample;
	trace_pstate_sample(trace_type,
		0,
		old_pstate,
		cpu->pstate.current_pstate,
		sample->mperf,
		sample->aperf,
		sample->tsc,
		get_avg_frequency(cpu),
		fp_toपूर्णांक(cpu->ioरुको_boost * 100));
पूर्ण

अटल व्योम पूर्णांकel_cpufreq_hwp_update(काष्ठा cpudata *cpu, u32 min, u32 max,
				     u32 desired, bool fast_चयन)
अणु
	u64 prev = READ_ONCE(cpu->hwp_req_cached), value = prev;

	value &= ~HWP_MIN_PERF(~0L);
	value |= HWP_MIN_PERF(min);

	value &= ~HWP_MAX_PERF(~0L);
	value |= HWP_MAX_PERF(max);

	value &= ~HWP_DESIRED_PERF(~0L);
	value |= HWP_DESIRED_PERF(desired);

	अगर (value == prev)
		वापस;

	WRITE_ONCE(cpu->hwp_req_cached, value);
	अगर (fast_चयन)
		wrmsrl(MSR_HWP_REQUEST, value);
	अन्यथा
		wrmsrl_on_cpu(cpu->cpu, MSR_HWP_REQUEST, value);
पूर्ण

अटल व्योम पूर्णांकel_cpufreq_perf_ctl_update(काष्ठा cpudata *cpu,
					  u32 target_pstate, bool fast_चयन)
अणु
	अगर (fast_चयन)
		wrmsrl(MSR_IA32_PERF_CTL,
		       pstate_funcs.get_val(cpu, target_pstate));
	अन्यथा
		wrmsrl_on_cpu(cpu->cpu, MSR_IA32_PERF_CTL,
			      pstate_funcs.get_val(cpu, target_pstate));
पूर्ण

अटल पूर्णांक पूर्णांकel_cpufreq_update_pstate(काष्ठा cpufreq_policy *policy,
				       पूर्णांक target_pstate, bool fast_चयन)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];
	पूर्णांक old_pstate = cpu->pstate.current_pstate;

	target_pstate = पूर्णांकel_pstate_prepare_request(cpu, target_pstate);
	अगर (hwp_active) अणु
		पूर्णांक max_pstate = policy->strict_target ?
					target_pstate : cpu->max_perf_ratio;

		पूर्णांकel_cpufreq_hwp_update(cpu, target_pstate, max_pstate, 0,
					 fast_चयन);
	पूर्ण अन्यथा अगर (target_pstate != old_pstate) अणु
		पूर्णांकel_cpufreq_perf_ctl_update(cpu, target_pstate, fast_चयन);
	पूर्ण

	cpu->pstate.current_pstate = target_pstate;

	पूर्णांकel_cpufreq_trace(cpu, fast_चयन ? INTEL_PSTATE_TRACE_FAST_SWITCH :
			    INTEL_PSTATE_TRACE_TARGET, old_pstate);

	वापस target_pstate;
पूर्ण

अटल पूर्णांक पूर्णांकel_cpufreq_target(काष्ठा cpufreq_policy *policy,
				अचिन्हित पूर्णांक target_freq,
				अचिन्हित पूर्णांक relation)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];
	काष्ठा cpufreq_freqs freqs;
	पूर्णांक target_pstate;

	update_turbo_state();

	freqs.old = policy->cur;
	freqs.new = target_freq;

	cpufreq_freq_transition_begin(policy, &freqs);

	चयन (relation) अणु
	हाल CPUFREQ_RELATION_L:
		target_pstate = DIV_ROUND_UP(freqs.new, cpu->pstate.scaling);
		अवरोध;
	हाल CPUFREQ_RELATION_H:
		target_pstate = freqs.new / cpu->pstate.scaling;
		अवरोध;
	शेष:
		target_pstate = DIV_ROUND_CLOSEST(freqs.new, cpu->pstate.scaling);
		अवरोध;
	पूर्ण

	target_pstate = पूर्णांकel_cpufreq_update_pstate(policy, target_pstate, false);

	freqs.new = target_pstate * cpu->pstate.scaling;

	cpufreq_freq_transition_end(policy, &freqs, false);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_cpufreq_fast_चयन(काष्ठा cpufreq_policy *policy,
					      अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[policy->cpu];
	पूर्णांक target_pstate;

	update_turbo_state();

	target_pstate = DIV_ROUND_UP(target_freq, cpu->pstate.scaling);

	target_pstate = पूर्णांकel_cpufreq_update_pstate(policy, target_pstate, true);

	वापस target_pstate * cpu->pstate.scaling;
पूर्ण

अटल व्योम पूर्णांकel_cpufreq_adjust_perf(अचिन्हित पूर्णांक cpunum,
				      अचिन्हित दीर्घ min_perf,
				      अचिन्हित दीर्घ target_perf,
				      अचिन्हित दीर्घ capacity)
अणु
	काष्ठा cpudata *cpu = all_cpu_data[cpunum];
	u64 hwp_cap = READ_ONCE(cpu->hwp_cap_cached);
	पूर्णांक old_pstate = cpu->pstate.current_pstate;
	पूर्णांक cap_pstate, min_pstate, max_pstate, target_pstate;

	update_turbo_state();
	cap_pstate = global.turbo_disabled ? HWP_GUARANTEED_PERF(hwp_cap) :
					     HWP_HIGHEST_PERF(hwp_cap);

	/* Optimization: Aव्योम unnecessary भागisions. */

	target_pstate = cap_pstate;
	अगर (target_perf < capacity)
		target_pstate = DIV_ROUND_UP(cap_pstate * target_perf, capacity);

	min_pstate = cap_pstate;
	अगर (min_perf < capacity)
		min_pstate = DIV_ROUND_UP(cap_pstate * min_perf, capacity);

	अगर (min_pstate < cpu->pstate.min_pstate)
		min_pstate = cpu->pstate.min_pstate;

	अगर (min_pstate < cpu->min_perf_ratio)
		min_pstate = cpu->min_perf_ratio;

	max_pstate = min(cap_pstate, cpu->max_perf_ratio);
	अगर (max_pstate < min_pstate)
		max_pstate = min_pstate;

	target_pstate = clamp_t(पूर्णांक, target_pstate, min_pstate, max_pstate);

	पूर्णांकel_cpufreq_hwp_update(cpu, min_pstate, max_pstate, target_pstate, true);

	cpu->pstate.current_pstate = target_pstate;
	पूर्णांकel_cpufreq_trace(cpu, INTEL_PSTATE_TRACE_FAST_SWITCH, old_pstate);
पूर्ण

अटल पूर्णांक पूर्णांकel_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा freq_qos_request *req;
	काष्ठा cpudata *cpu;
	काष्ठा device *dev;
	पूर्णांक ret, freq;

	dev = get_cpu_device(policy->cpu);
	अगर (!dev)
		वापस -ENODEV;

	ret = __पूर्णांकel_pstate_cpu_init(policy);
	अगर (ret)
		वापस ret;

	policy->cpuinfo.transition_latency = INTEL_CPUFREQ_TRANSITION_LATENCY;
	/* This reflects the पूर्णांकel_pstate_get_cpu_pstates() setting. */
	policy->cur = policy->cpuinfo.min_freq;

	req = kसुस्मृति(2, माप(*req), GFP_KERNEL);
	अगर (!req) अणु
		ret = -ENOMEM;
		जाओ pstate_निकास;
	पूर्ण

	cpu = all_cpu_data[policy->cpu];

	अगर (hwp_active) अणु
		u64 value;

		policy->transition_delay_us = INTEL_CPUFREQ_TRANSITION_DELAY_HWP;

		पूर्णांकel_pstate_get_hwp_cap(cpu);

		rdmsrl_on_cpu(cpu->cpu, MSR_HWP_REQUEST, &value);
		WRITE_ONCE(cpu->hwp_req_cached, value);

		cpu->epp_cached = पूर्णांकel_pstate_get_epp(cpu, value);
	पूर्ण अन्यथा अणु
		policy->transition_delay_us = INTEL_CPUFREQ_TRANSITION_DELAY;
	पूर्ण

	freq = DIV_ROUND_UP(cpu->pstate.turbo_freq * global.min_perf_pct, 100);

	ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs, req, FREQ_QOS_MIN,
				   freq);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to add min-freq constraint (%d)\n", ret);
		जाओ मुक्त_req;
	पूर्ण

	freq = DIV_ROUND_UP(cpu->pstate.turbo_freq * global.max_perf_pct, 100);

	ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs, req + 1, FREQ_QOS_MAX,
				   freq);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to add max-freq constraint (%d)\n", ret);
		जाओ हटाओ_min_req;
	पूर्ण

	policy->driver_data = req;

	वापस 0;

हटाओ_min_req:
	freq_qos_हटाओ_request(req);
मुक्त_req:
	kमुक्त(req);
pstate_निकास:
	पूर्णांकel_pstate_निकास_perf_limits(policy);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_cpufreq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा freq_qos_request *req;

	req = policy->driver_data;

	freq_qos_हटाओ_request(req + 1);
	freq_qos_हटाओ_request(req);
	kमुक्त(req);

	वापस पूर्णांकel_pstate_cpu_निकास(policy);
पूर्ण

अटल काष्ठा cpufreq_driver पूर्णांकel_cpufreq = अणु
	.flags		= CPUFREQ_CONST_LOOPS,
	.verअगरy		= पूर्णांकel_cpufreq_verअगरy_policy,
	.target		= पूर्णांकel_cpufreq_target,
	.fast_चयन	= पूर्णांकel_cpufreq_fast_चयन,
	.init		= पूर्णांकel_cpufreq_cpu_init,
	.निकास		= पूर्णांकel_cpufreq_cpu_निकास,
	.offline	= पूर्णांकel_pstate_cpu_offline,
	.online		= पूर्णांकel_pstate_cpu_online,
	.suspend	= पूर्णांकel_pstate_suspend,
	.resume		= पूर्णांकel_pstate_resume,
	.update_limits	= पूर्णांकel_pstate_update_limits,
	.name		= "intel_cpufreq",
पूर्ण;

अटल काष्ठा cpufreq_driver *शेष_driver;

अटल व्योम पूर्णांकel_pstate_driver_cleanup(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	get_online_cpus();
	क्रम_each_online_cpu(cpu) अणु
		अगर (all_cpu_data[cpu]) अणु
			अगर (पूर्णांकel_pstate_driver == &पूर्णांकel_pstate)
				पूर्णांकel_pstate_clear_update_util_hook(cpu);

			kमुक्त(all_cpu_data[cpu]);
			all_cpu_data[cpu] = शून्य;
		पूर्ण
	पूर्ण
	put_online_cpus();

	पूर्णांकel_pstate_driver = शून्य;
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_रेजिस्टर_driver(काष्ठा cpufreq_driver *driver)
अणु
	पूर्णांक ret;

	अगर (driver == &पूर्णांकel_pstate)
		पूर्णांकel_pstate_sysfs_expose_hwp_dynamic_boost();

	स_रखो(&global, 0, माप(global));
	global.max_perf_pct = 100;

	पूर्णांकel_pstate_driver = driver;
	ret = cpufreq_रेजिस्टर_driver(पूर्णांकel_pstate_driver);
	अगर (ret) अणु
		पूर्णांकel_pstate_driver_cleanup();
		वापस ret;
	पूर्ण

	global.min_perf_pct = min_perf_pct_min();

	वापस 0;
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_pstate_show_status(अक्षर *buf)
अणु
	अगर (!पूर्णांकel_pstate_driver)
		वापस प्र_लिखो(buf, "off\n");

	वापस प्र_लिखो(buf, "%s\n", पूर्णांकel_pstate_driver == &पूर्णांकel_pstate ?
					"active" : "passive");
पूर्ण

अटल पूर्णांक पूर्णांकel_pstate_update_status(स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अगर (size == 3 && !म_भेदन(buf, "off", size)) अणु
		अगर (!पूर्णांकel_pstate_driver)
			वापस -EINVAL;

		अगर (hwp_active)
			वापस -EBUSY;

		cpufreq_unरेजिस्टर_driver(पूर्णांकel_pstate_driver);
		पूर्णांकel_pstate_driver_cleanup();
		वापस 0;
	पूर्ण

	अगर (size == 6 && !म_भेदन(buf, "active", size)) अणु
		अगर (पूर्णांकel_pstate_driver) अणु
			अगर (पूर्णांकel_pstate_driver == &पूर्णांकel_pstate)
				वापस 0;

			cpufreq_unरेजिस्टर_driver(पूर्णांकel_pstate_driver);
		पूर्ण

		वापस पूर्णांकel_pstate_रेजिस्टर_driver(&पूर्णांकel_pstate);
	पूर्ण

	अगर (size == 7 && !म_भेदन(buf, "passive", size)) अणु
		अगर (पूर्णांकel_pstate_driver) अणु
			अगर (पूर्णांकel_pstate_driver == &पूर्णांकel_cpufreq)
				वापस 0;

			cpufreq_unरेजिस्टर_driver(पूर्णांकel_pstate_driver);
			पूर्णांकel_pstate_sysfs_hide_hwp_dynamic_boost();
		पूर्ण

		वापस पूर्णांकel_pstate_रेजिस्टर_driver(&पूर्णांकel_cpufreq);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक no_load __initdata;
अटल पूर्णांक no_hwp __initdata;
अटल पूर्णांक hwp_only __initdata;
अटल अचिन्हित पूर्णांक क्रमce_load __initdata;

अटल पूर्णांक __init पूर्णांकel_pstate_msrs_not_valid(व्योम)
अणु
	अगर (!pstate_funcs.get_max() ||
	    !pstate_funcs.get_min() ||
	    !pstate_funcs.get_turbo())
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम __init copy_cpu_funcs(काष्ठा pstate_funcs *funcs)
अणु
	pstate_funcs.get_max   = funcs->get_max;
	pstate_funcs.get_max_physical = funcs->get_max_physical;
	pstate_funcs.get_min   = funcs->get_min;
	pstate_funcs.get_turbo = funcs->get_turbo;
	pstate_funcs.get_scaling = funcs->get_scaling;
	pstate_funcs.get_val   = funcs->get_val;
	pstate_funcs.get_vid   = funcs->get_vid;
	pstate_funcs.get_aperf_mperf_shअगरt = funcs->get_aperf_mperf_shअगरt;
पूर्ण

#अगर_घोषित CONFIG_ACPI

अटल bool __init पूर्णांकel_pstate_no_acpi_pss(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		acpi_status status;
		जोड़ acpi_object *pss;
		काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
		काष्ठा acpi_processor *pr = per_cpu(processors, i);

		अगर (!pr)
			जारी;

		status = acpi_evaluate_object(pr->handle, "_PSS", शून्य, &buffer);
		अगर (ACPI_FAILURE(status))
			जारी;

		pss = buffer.poपूर्णांकer;
		अगर (pss && pss->type == ACPI_TYPE_PACKAGE) अणु
			kमुक्त(pss);
			वापस false;
		पूर्ण

		kमुक्त(pss);
	पूर्ण

	pr_debug("ACPI _PSS not found\n");
	वापस true;
पूर्ण

अटल bool __init पूर्णांकel_pstate_no_acpi_pcch(व्योम)
अणु
	acpi_status status;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, "\\_SB", &handle);
	अगर (ACPI_FAILURE(status))
		जाओ not_found;

	अगर (acpi_has_method(handle, "PCCH"))
		वापस false;

not_found:
	pr_debug("ACPI PCCH not found\n");
	वापस true;
पूर्ण

अटल bool __init पूर्णांकel_pstate_has_acpi_ppc(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा acpi_processor *pr = per_cpu(processors, i);

		अगर (!pr)
			जारी;
		अगर (acpi_has_method(pr->handle, "_PPC"))
			वापस true;
	पूर्ण
	pr_debug("ACPI _PPC not found\n");
	वापस false;
पूर्ण

क्रमागत अणु
	PSS,
	PPC,
पूर्ण;

/* Hardware venकरोr-specअगरic info that has its own घातer management modes */
अटल काष्ठा acpi_platक्रमm_list plat_info[] __initdata = अणु
	अणु"HP    ", "ProLiant", 0, ACPI_SIG_FADT, all_versions, शून्य, PSSपूर्ण,
	अणु"ORACLE", "X4-2    ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X4-2L   ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X4-2B   ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X3-2    ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X3-2L   ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X3-2B   ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X4470M2 ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X4270M3 ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X4270M2 ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X4170M2 ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X4170 M3", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X4275 M3", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "X6-2    ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु"ORACLE", "Sudbury ", 0, ACPI_SIG_FADT, all_versions, शून्य, PPCपूर्ण,
	अणु पूर्ण /* End */
पूर्ण;

#घोषणा BITMASK_OOB	(BIT(8) | BIT(18))

अटल bool __init पूर्णांकel_pstate_platक्रमm_pwr_mgmt_exists(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	u64 misc_pwr;
	पूर्णांक idx;

	id = x86_match_cpu(पूर्णांकel_pstate_cpu_oob_ids);
	अगर (id) अणु
		rdmsrl(MSR_MISC_PWR_MGMT, misc_pwr);
		अगर (misc_pwr & BITMASK_OOB) अणु
			pr_debug("Bit 8 or 18 in the MISC_PWR_MGMT MSR set\n");
			pr_debug("P states are controlled in Out of Band mode by the firmware/hardware\n");
			वापस true;
		पूर्ण
	पूर्ण

	idx = acpi_match_platक्रमm_list(plat_info);
	अगर (idx < 0)
		वापस false;

	चयन (plat_info[idx].data) अणु
	हाल PSS:
		अगर (!पूर्णांकel_pstate_no_acpi_pss())
			वापस false;

		वापस पूर्णांकel_pstate_no_acpi_pcch();
	हाल PPC:
		वापस पूर्णांकel_pstate_has_acpi_ppc() && !क्रमce_load;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम पूर्णांकel_pstate_request_control_from_smm(व्योम)
अणु
	/*
	 * It may be unsafe to request P-states control from SMM अगर _PPC support
	 * has not been enabled.
	 */
	अगर (acpi_ppc)
		acpi_processor_pstate_control();
पूर्ण
#अन्यथा /* CONFIG_ACPI not enabled */
अटल अंतरभूत bool पूर्णांकel_pstate_platक्रमm_pwr_mgmt_exists(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool पूर्णांकel_pstate_has_acpi_ppc(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम पूर्णांकel_pstate_request_control_from_smm(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

#घोषणा INTEL_PSTATE_HWP_BROADWELL	0x01

#घोषणा X86_MATCH_HWP(model, hwp_mode)					\
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL, 6, INTEL_FAM6_##model, \
					   X86_FEATURE_HWP, hwp_mode)

अटल स्थिर काष्ठा x86_cpu_id hwp_support_ids[] __initस्थिर = अणु
	X86_MATCH_HWP(BROADWELL_X,	INTEL_PSTATE_HWP_BROADWELL),
	X86_MATCH_HWP(BROADWELL_D,	INTEL_PSTATE_HWP_BROADWELL),
	X86_MATCH_HWP(ANY,		0),
	अणुपूर्ण
पूर्ण;

अटल bool पूर्णांकel_pstate_hwp_is_enabled(व्योम)
अणु
	u64 value;

	rdmsrl(MSR_PM_ENABLE, value);
	वापस !!(value & 0x1);
पूर्ण

अटल पूर्णांक __init पूर्णांकel_pstate_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	पूर्णांक rc;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_INTEL)
		वापस -ENODEV;

	अगर (no_load)
		वापस -ENODEV;

	id = x86_match_cpu(hwp_support_ids);
	अगर (id) अणु
		copy_cpu_funcs(&core_funcs);
		/*
		 * Aव्योम enabling HWP क्रम processors without EPP support,
		 * because that means incomplete HWP implementation which is a
		 * corner हाल and supporting it is generally problematic.
		 *
		 * If HWP is enabled alपढ़ोy, though, there is no choice but to
		 * deal with it.
		 */
		अगर ((!no_hwp && boot_cpu_has(X86_FEATURE_HWP_EPP)) ||
		    पूर्णांकel_pstate_hwp_is_enabled()) अणु
			hwp_active++;
			hwp_mode_bdw = id->driver_data;
			पूर्णांकel_pstate.attr = hwp_cpufreq_attrs;
			पूर्णांकel_cpufreq.attr = hwp_cpufreq_attrs;
			पूर्णांकel_cpufreq.flags |= CPUFREQ_NEED_UPDATE_LIMITS;
			पूर्णांकel_cpufreq.adjust_perf = पूर्णांकel_cpufreq_adjust_perf;
			अगर (!शेष_driver)
				शेष_driver = &पूर्णांकel_pstate;

			जाओ hwp_cpu_matched;
		पूर्ण
	पूर्ण अन्यथा अणु
		id = x86_match_cpu(पूर्णांकel_pstate_cpu_ids);
		अगर (!id) अणु
			pr_info("CPU model not supported\n");
			वापस -ENODEV;
		पूर्ण

		copy_cpu_funcs((काष्ठा pstate_funcs *)id->driver_data);
	पूर्ण

	अगर (पूर्णांकel_pstate_msrs_not_valid()) अणु
		pr_info("Invalid MSRs\n");
		वापस -ENODEV;
	पूर्ण
	/* Without HWP start in the passive mode. */
	अगर (!शेष_driver)
		शेष_driver = &पूर्णांकel_cpufreq;

hwp_cpu_matched:
	/*
	 * The Intel pstate driver will be ignored अगर the platक्रमm
	 * firmware has its own घातer management modes.
	 */
	अगर (पूर्णांकel_pstate_platक्रमm_pwr_mgmt_exists()) अणु
		pr_info("P-states controlled by the platform\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!hwp_active && hwp_only)
		वापस -ENOTSUPP;

	pr_info("Intel P-state driver initializing\n");

	all_cpu_data = vzalloc(array_size(माप(व्योम *), num_possible_cpus()));
	अगर (!all_cpu_data)
		वापस -ENOMEM;

	पूर्णांकel_pstate_request_control_from_smm();

	पूर्णांकel_pstate_sysfs_expose_params();

	mutex_lock(&पूर्णांकel_pstate_driver_lock);
	rc = पूर्णांकel_pstate_रेजिस्टर_driver(शेष_driver);
	mutex_unlock(&पूर्णांकel_pstate_driver_lock);
	अगर (rc) अणु
		पूर्णांकel_pstate_sysfs_हटाओ();
		वापस rc;
	पूर्ण

	अगर (hwp_active) अणु
		स्थिर काष्ठा x86_cpu_id *id;

		id = x86_match_cpu(पूर्णांकel_pstate_cpu_ee_disable_ids);
		अगर (id) अणु
			set_घातer_ctl_ee_state(false);
			pr_info("Disabling energy efficiency optimization\n");
		पूर्ण

		pr_info("HWP enabled\n");
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(पूर्णांकel_pstate_init);

अटल पूर्णांक __init पूर्णांकel_pstate_setup(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	अगर (!म_भेद(str, "disable"))
		no_load = 1;
	अन्यथा अगर (!म_भेद(str, "active"))
		शेष_driver = &पूर्णांकel_pstate;
	अन्यथा अगर (!म_भेद(str, "passive"))
		शेष_driver = &पूर्णांकel_cpufreq;

	अगर (!म_भेद(str, "no_hwp")) अणु
		pr_info("HWP disabled\n");
		no_hwp = 1;
	पूर्ण
	अगर (!म_भेद(str, "force"))
		क्रमce_load = 1;
	अगर (!म_भेद(str, "hwp_only"))
		hwp_only = 1;
	अगर (!म_भेद(str, "per_cpu_perf_limits"))
		per_cpu_limits = true;

#अगर_घोषित CONFIG_ACPI
	अगर (!म_भेद(str, "support_acpi_ppc"))
		acpi_ppc = true;
#पूर्ण_अगर

	वापस 0;
पूर्ण
early_param("intel_pstate", पूर्णांकel_pstate_setup);

MODULE_AUTHOR("Dirk Brandewie <dirk.j.brandewie@intel.com>");
MODULE_DESCRIPTION("'intel_pstate' - P state driver Intel Core processors");
MODULE_LICENSE("GPL");

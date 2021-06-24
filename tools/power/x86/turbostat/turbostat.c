<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * turbostat -- show CPU frequency and C-state residency
 * on modern Intel and AMD processors.
 *
 * Copyright (c) 2021 Intel Corporation.
 * Len Brown <len.brown@पूर्णांकel.com>
 */

#घोषणा _GNU_SOURCE
#समावेश MSRHEADER
#समावेश INTEL_FAMILY_HEADER
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <err.h>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/select.h>
#समावेश <sys/resource.h>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <sys/समय.स>
#समावेश <मानककोष.स>
#समावेश <getopt.h>
#समावेश <dirent.h>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <sched.h>
#समावेश <समय.स>
#समावेश <cpuid.h>
#समावेश <sys/capability.h>
#समावेश <त्रुटिसं.स>
#समावेश <गणित.स>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/unistd.h>
#समावेश <stdbool.h>

अक्षर *proc_stat = "/proc/stat";
खाता *outf;
पूर्णांक *fd_percpu;
पूर्णांक *fd_instr_count_percpu;
काष्ठा समयval पूर्णांकerval_tv = अणु 5, 0 पूर्ण;
काष्ठा बारpec पूर्णांकerval_ts = अणु 5, 0 पूर्ण;

/* Save original CPU model */
अचिन्हित पूर्णांक model_orig;

अचिन्हित पूर्णांक num_iterations;
अचिन्हित पूर्णांक debug;
अचिन्हित पूर्णांक quiet;
अचिन्हित पूर्णांक shown;
अचिन्हित पूर्णांक sums_need_wide_columns;
अचिन्हित पूर्णांक rapl_joules;
अचिन्हित पूर्णांक summary_only;
अचिन्हित पूर्णांक list_header_only;
अचिन्हित पूर्णांक dump_only;
अचिन्हित पूर्णांक करो_snb_cstates;
अचिन्हित पूर्णांक करो_knl_cstates;
अचिन्हित पूर्णांक करो_slm_cstates;
अचिन्हित पूर्णांक use_c1_residency_msr;
अचिन्हित पूर्णांक has_aperf;
अचिन्हित पूर्णांक has_epb;
अचिन्हित पूर्णांक करो_irtl_snb;
अचिन्हित पूर्णांक करो_irtl_hsw;
अचिन्हित पूर्णांक units = 1000000;	/* MHz etc */
अचिन्हित पूर्णांक genuine_पूर्णांकel;
अचिन्हित पूर्णांक authentic_amd;
अचिन्हित पूर्णांक hygon_genuine;
अचिन्हित पूर्णांक max_level, max_extended_level;
अचिन्हित पूर्णांक has_invariant_tsc;
अचिन्हित पूर्णांक करो_nhm_platक्रमm_info;
अचिन्हित पूर्णांक no_MSR_MISC_PWR_MGMT;
अचिन्हित पूर्णांक aperf_mperf_multiplier = 1;
द्विगुन bclk;
द्विगुन base_hz;
अचिन्हित पूर्णांक has_base_hz;
द्विगुन tsc_tweak = 1.0;
अचिन्हित पूर्णांक show_pkg_only;
अचिन्हित पूर्णांक show_core_only;
अक्षर *output_buffer, *outp;
अचिन्हित पूर्णांक करो_rapl;
अचिन्हित पूर्णांक करो_dts;
अचिन्हित पूर्णांक करो_pपंचांग;
अचिन्हित पूर्णांक करो_ipc;
अचिन्हित दीर्घ दीर्घ gfx_cur_rc6_ms;
अचिन्हित दीर्घ दीर्घ cpuidle_cur_cpu_lpi_us;
अचिन्हित दीर्घ दीर्घ cpuidle_cur_sys_lpi_us;
अचिन्हित पूर्णांक gfx_cur_mhz;
अचिन्हित पूर्णांक gfx_act_mhz;
अचिन्हित पूर्णांक tj_max;
अचिन्हित पूर्णांक tj_max_override;
पूर्णांक tcc_offset_bits;
द्विगुन rapl_घातer_units, rapl_समय_units;
द्विगुन rapl_dram_energy_units, rapl_energy_units;
द्विगुन rapl_joule_counter_range;
अचिन्हित पूर्णांक करो_core_perf_limit_reasons;
अचिन्हित पूर्णांक has_स्वतःmatic_cstate_conversion;
अचिन्हित पूर्णांक dis_cstate_prewake;
अचिन्हित पूर्णांक करो_gfx_perf_limit_reasons;
अचिन्हित पूर्णांक करो_ring_perf_limit_reasons;
अचिन्हित पूर्णांक crystal_hz;
अचिन्हित दीर्घ दीर्घ tsc_hz;
पूर्णांक base_cpu;
द्विगुन discover_bclk(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model);
अचिन्हित पूर्णांक has_hwp;		/* IA32_PM_ENABLE, IA32_HWP_CAPABILITIES */
			/* IA32_HWP_REQUEST, IA32_HWP_STATUS */
अचिन्हित पूर्णांक has_hwp_notअगरy;	/* IA32_HWP_INTERRUPT */
अचिन्हित पूर्णांक has_hwp_activity_winकरोw;	/* IA32_HWP_REQUEST[bits 41:32] */
अचिन्हित पूर्णांक has_hwp_epp;	/* IA32_HWP_REQUEST[bits 31:24] */
अचिन्हित पूर्णांक has_hwp_pkg;	/* IA32_HWP_REQUEST_PKG */
अचिन्हित पूर्णांक has_misc_feature_control;
अचिन्हित पूर्णांक first_counter_पढ़ो = 1;
पूर्णांक ignore_मानक_निवेश;

#घोषणा RAPL_PKG		(1 << 0)
					/* 0x610 MSR_PKG_POWER_LIMIT */
					/* 0x611 MSR_PKG_ENERGY_STATUS */
#घोषणा RAPL_PKG_PERF_STATUS	(1 << 1)
					/* 0x613 MSR_PKG_PERF_STATUS */
#घोषणा RAPL_PKG_POWER_INFO	(1 << 2)
					/* 0x614 MSR_PKG_POWER_INFO */

#घोषणा RAPL_DRAM		(1 << 3)
					/* 0x618 MSR_DRAM_POWER_LIMIT */
					/* 0x619 MSR_DRAM_ENERGY_STATUS */
#घोषणा RAPL_DRAM_PERF_STATUS	(1 << 4)
					/* 0x61b MSR_DRAM_PERF_STATUS */
#घोषणा RAPL_DRAM_POWER_INFO	(1 << 5)
					/* 0x61c MSR_DRAM_POWER_INFO */

#घोषणा RAPL_CORES_POWER_LIMIT	(1 << 6)
					/* 0x638 MSR_PP0_POWER_LIMIT */
#घोषणा RAPL_CORE_POLICY	(1 << 7)
					/* 0x63a MSR_PP0_POLICY */

#घोषणा RAPL_GFX		(1 << 8)
					/* 0x640 MSR_PP1_POWER_LIMIT */
					/* 0x641 MSR_PP1_ENERGY_STATUS */
					/* 0x642 MSR_PP1_POLICY */

#घोषणा RAPL_CORES_ENERGY_STATUS	(1 << 9)
					/* 0x639 MSR_PP0_ENERGY_STATUS */
#घोषणा RAPL_PER_CORE_ENERGY	(1 << 10)
					/* Indicates cores energy collection is per-core,
					 * not per-package. */
#घोषणा RAPL_AMD_F17H		(1 << 11)
					/* 0xc0010299 MSR_RAPL_PWR_UNIT */
					/* 0xc001029a MSR_CORE_ENERGY_STAT */
					/* 0xc001029b MSR_PKG_ENERGY_STAT */
#घोषणा RAPL_CORES (RAPL_CORES_ENERGY_STATUS | RAPL_CORES_POWER_LIMIT)
#घोषणा	TJMAX_DEFAULT	100

/* MSRs that are not yet in the kernel-provided header. */
#घोषणा MSR_RAPL_PWR_UNIT	0xc0010299
#घोषणा MSR_CORE_ENERGY_STAT	0xc001029a
#घोषणा MSR_PKG_ENERGY_STAT	0xc001029b

#घोषणा MAX(a, b) ((a) > (b) ? (a) : (b))

/*
 * buffer size used by माला_पूछो() क्रम added column names
 * Usually truncated to 7 अक्षरacters, but also handles 18 columns क्रम raw 64-bit counters
 */
#घोषणा	NAME_BYTES 20
#घोषणा PATH_BYTES 128

पूर्णांक backwards_count;
अक्षर *progname;

#घोषणा CPU_SUBSET_MAXCPUS	1024	/* need to use beक्रमe probe... */
cpu_set_t *cpu_present_set, *cpu_affinity_set, *cpu_subset;
माप_प्रकार cpu_present_setsize, cpu_affinity_setsize, cpu_subset_size;
#घोषणा MAX_ADDED_COUNTERS 8
#घोषणा MAX_ADDED_THREAD_COUNTERS 24
#घोषणा BITMASK_SIZE 32

काष्ठा thपढ़ो_data अणु
	काष्ठा समयval tv_begin;
	काष्ठा समयval tv_end;
	काष्ठा समयval tv_delta;
	अचिन्हित दीर्घ दीर्घ tsc;
	अचिन्हित दीर्घ दीर्घ aperf;
	अचिन्हित दीर्घ दीर्घ mperf;
	अचिन्हित दीर्घ दीर्घ c1;
	अचिन्हित दीर्घ दीर्घ instr_count;
	अचिन्हित दीर्घ दीर्घ irq_count;
	अचिन्हित पूर्णांक smi_count;
	अचिन्हित पूर्णांक cpu_id;
	अचिन्हित पूर्णांक apic_id;
	अचिन्हित पूर्णांक x2apic_id;
	अचिन्हित पूर्णांक flags;
	bool is_atom;
#घोषणा CPU_IS_FIRST_THREAD_IN_CORE	0x2
#घोषणा CPU_IS_FIRST_CORE_IN_PACKAGE	0x4
	अचिन्हित दीर्घ दीर्घ counter[MAX_ADDED_THREAD_COUNTERS];
पूर्ण *thपढ़ो_even, *thपढ़ो_odd;

काष्ठा core_data अणु
	अचिन्हित दीर्घ दीर्घ c3;
	अचिन्हित दीर्घ दीर्घ c6;
	अचिन्हित दीर्घ दीर्घ c7;
	अचिन्हित दीर्घ दीर्घ mc6_us;	/* duplicate as per-core क्रम now, even though per module */
	अचिन्हित पूर्णांक core_temp_c;
	अचिन्हित पूर्णांक core_energy;	/* MSR_CORE_ENERGY_STAT */
	अचिन्हित पूर्णांक core_id;
	अचिन्हित दीर्घ दीर्घ counter[MAX_ADDED_COUNTERS];
पूर्ण *core_even, *core_odd;

काष्ठा pkg_data अणु
	अचिन्हित दीर्घ दीर्घ pc2;
	अचिन्हित दीर्घ दीर्घ pc3;
	अचिन्हित दीर्घ दीर्घ pc6;
	अचिन्हित दीर्घ दीर्घ pc7;
	अचिन्हित दीर्घ दीर्घ pc8;
	अचिन्हित दीर्घ दीर्घ pc9;
	अचिन्हित दीर्घ दीर्घ pc10;
	अचिन्हित दीर्घ दीर्घ cpu_lpi;
	अचिन्हित दीर्घ दीर्घ sys_lpi;
	अचिन्हित दीर्घ दीर्घ pkg_wtd_core_c0;
	अचिन्हित दीर्घ दीर्घ pkg_any_core_c0;
	अचिन्हित दीर्घ दीर्घ pkg_any_gfxe_c0;
	अचिन्हित दीर्घ दीर्घ pkg_both_core_gfxe_c0;
	दीर्घ दीर्घ gfx_rc6_ms;
	अचिन्हित पूर्णांक gfx_mhz;
	अचिन्हित पूर्णांक gfx_act_mhz;
	अचिन्हित पूर्णांक package_id;
	अचिन्हित दीर्घ दीर्घ energy_pkg;	/* MSR_PKG_ENERGY_STATUS */
	अचिन्हित दीर्घ दीर्घ energy_dram;	/* MSR_DRAM_ENERGY_STATUS */
	अचिन्हित दीर्घ दीर्घ energy_cores;	/* MSR_PP0_ENERGY_STATUS */
	अचिन्हित दीर्घ दीर्घ energy_gfx;	/* MSR_PP1_ENERGY_STATUS */
	अचिन्हित दीर्घ दीर्घ rapl_pkg_perf_status;	/* MSR_PKG_PERF_STATUS */
	अचिन्हित दीर्घ दीर्घ rapl_dram_perf_status;	/* MSR_DRAM_PERF_STATUS */
	अचिन्हित पूर्णांक pkg_temp_c;
	अचिन्हित दीर्घ दीर्घ counter[MAX_ADDED_COUNTERS];
पूर्ण *package_even, *package_odd;

#घोषणा ODD_COUNTERS thपढ़ो_odd, core_odd, package_odd
#घोषणा EVEN_COUNTERS thपढ़ो_even, core_even, package_even

#घोषणा GET_THREAD(thपढ़ो_base, thपढ़ो_no, core_no, node_no, pkg_no)	      \
	((thपढ़ो_base) +						      \
	 ((pkg_no) *							      \
	  topo.nodes_per_pkg * topo.cores_per_node * topo.thपढ़ोs_per_core) + \
	 ((node_no) * topo.cores_per_node * topo.thपढ़ोs_per_core) +	      \
	 ((core_no) * topo.thपढ़ोs_per_core) +				      \
	 (thपढ़ो_no))

#घोषणा GET_CORE(core_base, core_no, node_no, pkg_no)			\
	((core_base) +							\
	 ((pkg_no) *  topo.nodes_per_pkg * topo.cores_per_node) +	\
	 ((node_no) * topo.cores_per_node) +				\
	 (core_no))

#घोषणा GET_PKG(pkg_base, pkg_no) (pkg_base + pkg_no)

क्रमागत counter_scope अणु SCOPE_CPU, SCOPE_CORE, SCOPE_PACKAGE पूर्ण;
क्रमागत counter_type अणु COUNTER_ITEMS, COUNTER_CYCLES, COUNTER_SECONDS, COUNTER_USEC पूर्ण;
क्रमागत counter_क्रमmat अणु FORMAT_RAW, FORMAT_DELTA, FORMAT_PERCENT पूर्ण;

काष्ठा msr_counter अणु
	अचिन्हित पूर्णांक msr_num;
	अक्षर name[NAME_BYTES];
	अक्षर path[PATH_BYTES];
	अचिन्हित पूर्णांक width;
	क्रमागत counter_type type;
	क्रमागत counter_क्रमmat क्रमmat;
	काष्ठा msr_counter *next;
	अचिन्हित पूर्णांक flags;
#घोषणा	FLAGS_HIDE	(1 << 0)
#घोषणा	FLAGS_SHOW	(1 << 1)
#घोषणा	SYSFS_PERCPU	(1 << 1)
पूर्ण;

/*
 * The accumulated sum of MSR is defined as a monotonic
 * increasing MSR, it will be accumulated periodically,
 * despite its रेजिस्टर's bit width.
 */
क्रमागत अणु
	IDX_PKG_ENERGY,
	IDX_DRAM_ENERGY,
	IDX_PP0_ENERGY,
	IDX_PP1_ENERGY,
	IDX_PKG_PERF,
	IDX_DRAM_PERF,
	IDX_COUNT,
पूर्ण;

पूर्णांक get_msr_sum(पूर्णांक cpu, off_t offset, अचिन्हित दीर्घ दीर्घ *msr);

काष्ठा msr_sum_array अणु
	/* get_msr_sum() = sum + (get_msr() - last) */
	काष्ठा अणु
		/*The accumulated MSR value is updated by the समयr */
		अचिन्हित दीर्घ दीर्घ sum;
		/*The MSR footprपूर्णांक recorded in last समयr */
		अचिन्हित दीर्घ दीर्घ last;
	पूर्ण entries[IDX_COUNT];
पूर्ण;

/* The percpu MSR sum array.*/
काष्ठा msr_sum_array *per_cpu_msr_sum;

off_t idx_to_offset(पूर्णांक idx)
अणु
	off_t offset;

	चयन (idx) अणु
	हाल IDX_PKG_ENERGY:
		अगर (करो_rapl & RAPL_AMD_F17H)
			offset = MSR_PKG_ENERGY_STAT;
		अन्यथा
			offset = MSR_PKG_ENERGY_STATUS;
		अवरोध;
	हाल IDX_DRAM_ENERGY:
		offset = MSR_DRAM_ENERGY_STATUS;
		अवरोध;
	हाल IDX_PP0_ENERGY:
		offset = MSR_PP0_ENERGY_STATUS;
		अवरोध;
	हाल IDX_PP1_ENERGY:
		offset = MSR_PP1_ENERGY_STATUS;
		अवरोध;
	हाल IDX_PKG_PERF:
		offset = MSR_PKG_PERF_STATUS;
		अवरोध;
	हाल IDX_DRAM_PERF:
		offset = MSR_DRAM_PERF_STATUS;
		अवरोध;
	शेष:
		offset = -1;
	पूर्ण
	वापस offset;
पूर्ण

पूर्णांक offset_to_idx(off_t offset)
अणु
	पूर्णांक idx;

	चयन (offset) अणु
	हाल MSR_PKG_ENERGY_STATUS:
	हाल MSR_PKG_ENERGY_STAT:
		idx = IDX_PKG_ENERGY;
		अवरोध;
	हाल MSR_DRAM_ENERGY_STATUS:
		idx = IDX_DRAM_ENERGY;
		अवरोध;
	हाल MSR_PP0_ENERGY_STATUS:
		idx = IDX_PP0_ENERGY;
		अवरोध;
	हाल MSR_PP1_ENERGY_STATUS:
		idx = IDX_PP1_ENERGY;
		अवरोध;
	हाल MSR_PKG_PERF_STATUS:
		idx = IDX_PKG_PERF;
		अवरोध;
	हाल MSR_DRAM_PERF_STATUS:
		idx = IDX_DRAM_PERF;
		अवरोध;
	शेष:
		idx = -1;
	पूर्ण
	वापस idx;
पूर्ण

पूर्णांक idx_valid(पूर्णांक idx)
अणु
	चयन (idx) अणु
	हाल IDX_PKG_ENERGY:
		वापस करो_rapl & (RAPL_PKG | RAPL_AMD_F17H);
	हाल IDX_DRAM_ENERGY:
		वापस करो_rapl & RAPL_DRAM;
	हाल IDX_PP0_ENERGY:
		वापस करो_rapl & RAPL_CORES_ENERGY_STATUS;
	हाल IDX_PP1_ENERGY:
		वापस करो_rapl & RAPL_GFX;
	हाल IDX_PKG_PERF:
		वापस करो_rapl & RAPL_PKG_PERF_STATUS;
	हाल IDX_DRAM_PERF:
		वापस करो_rapl & RAPL_DRAM_PERF_STATUS;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

काष्ठा sys_counters अणु
	अचिन्हित पूर्णांक added_thपढ़ो_counters;
	अचिन्हित पूर्णांक added_core_counters;
	अचिन्हित पूर्णांक added_package_counters;
	काष्ठा msr_counter *tp;
	काष्ठा msr_counter *cp;
	काष्ठा msr_counter *pp;
पूर्ण sys;

काष्ठा प्रणाली_summary अणु
	काष्ठा thपढ़ो_data thपढ़ोs;
	काष्ठा core_data cores;
	काष्ठा pkg_data packages;
पूर्ण average;

काष्ठा cpu_topology अणु
	पूर्णांक physical_package_id;
	पूर्णांक die_id;
	पूर्णांक logical_cpu_id;
	पूर्णांक physical_node_id;
	पूर्णांक logical_node_id;	/* 0-based count within the package */
	पूर्णांक physical_core_id;
	पूर्णांक thपढ़ो_id;
	cpu_set_t *put_ids;	/* Processing Unit/Thपढ़ो IDs */
पूर्ण *cpus;

काष्ठा topo_params अणु
	पूर्णांक num_packages;
	पूर्णांक num_die;
	पूर्णांक num_cpus;
	पूर्णांक num_cores;
	पूर्णांक max_cpu_num;
	पूर्णांक max_node_num;
	पूर्णांक nodes_per_pkg;
	पूर्णांक cores_per_node;
	पूर्णांक thपढ़ोs_per_core;
पूर्ण topo;

काष्ठा समयval tv_even, tv_odd, tv_delta;

पूर्णांक *irq_column_2_cpu;		/* /proc/पूर्णांकerrupts column numbers */
पूर्णांक *irqs_per_cpu;		/* indexed by cpu_num */

व्योम setup_all_buffers(व्योम);

अक्षर *sys_lpi_file;
अक्षर *sys_lpi_file_sysfs = "/sys/devices/system/cpu/cpuidle/low_power_idle_system_residency_us";
अक्षर *sys_lpi_file_debugfs = "/sys/kernel/debug/pmc_core/slp_s0_residency_usec";

पूर्णांक cpu_is_not_present(पूर्णांक cpu)
अणु
	वापस !CPU_ISSET_S(cpu, cpu_present_setsize, cpu_present_set);
पूर्ण

/*
 * run func(thपढ़ो, core, package) in topology order
 * skip non-present cpus
 */

पूर्णांक क्रम_all_cpus(पूर्णांक (func) (काष्ठा thपढ़ो_data *, काष्ठा core_data *, काष्ठा pkg_data *),
		 काष्ठा thपढ़ो_data *thपढ़ो_base, काष्ठा core_data *core_base, काष्ठा pkg_data *pkg_base)
अणु
	पूर्णांक retval, pkg_no, core_no, thपढ़ो_no, node_no;

	क्रम (pkg_no = 0; pkg_no < topo.num_packages; ++pkg_no) अणु
		क्रम (node_no = 0; node_no < topo.nodes_per_pkg; node_no++) अणु
			क्रम (core_no = 0; core_no < topo.cores_per_node; ++core_no) अणु
				क्रम (thपढ़ो_no = 0; thपढ़ो_no < topo.thपढ़ोs_per_core; ++thपढ़ो_no) अणु
					काष्ठा thपढ़ो_data *t;
					काष्ठा core_data *c;
					काष्ठा pkg_data *p;

					t = GET_THREAD(thपढ़ो_base, thपढ़ो_no, core_no, node_no, pkg_no);

					अगर (cpu_is_not_present(t->cpu_id))
						जारी;

					c = GET_CORE(core_base, core_no, node_no, pkg_no);
					p = GET_PKG(pkg_base, pkg_no);

					retval = func(t, c, p);
					अगर (retval)
						वापस retval;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cpu_migrate(पूर्णांक cpu)
अणु
	CPU_ZERO_S(cpu_affinity_setsize, cpu_affinity_set);
	CPU_SET_S(cpu, cpu_affinity_setsize, cpu_affinity_set);
	अगर (sched_setaffinity(0, cpu_affinity_setsize, cpu_affinity_set) == -1)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक get_msr_fd(पूर्णांक cpu)
अणु
	अक्षर pathname[32];
	पूर्णांक fd;

	fd = fd_percpu[cpu];

	अगर (fd)
		वापस fd;

	प्र_लिखो(pathname, "/dev/cpu/%d/msr", cpu);
	fd = खोलो(pathname, O_RDONLY);
	अगर (fd < 0)
		err(-1, "%s open failed, try chown or chmod +r /dev/cpu/*/msr, or run as root", pathname);

	fd_percpu[cpu] = fd;

	वापस fd;
पूर्ण

अटल दीर्घ perf_event_खोलो(काष्ठा perf_event_attr *hw_event, pid_t pid, पूर्णांक cpu, पूर्णांक group_fd, अचिन्हित दीर्घ flags)
अणु
	वापस syscall(__NR_perf_event_खोलो, hw_event, pid, cpu, group_fd, flags);
पूर्ण

अटल पूर्णांक perf_instr_count_खोलो(पूर्णांक cpu_num)
अणु
	काष्ठा perf_event_attr pea;
	पूर्णांक fd;

	स_रखो(&pea, 0, माप(काष्ठा perf_event_attr));
	pea.type = PERF_TYPE_HARDWARE;
	pea.size = माप(काष्ठा perf_event_attr);
	pea.config = PERF_COUNT_HW_INSTRUCTIONS;

	/* counter क्रम cpu_num, including user + kernel and all processes */
	fd = perf_event_खोलो(&pea, -1, cpu_num, -1, 0);
	अगर (fd == -1)
		err(-1, "cpu%d: perf instruction counter\n", cpu_num);

	वापस fd;
पूर्ण

पूर्णांक get_instr_count_fd(पूर्णांक cpu)
अणु
	अगर (fd_instr_count_percpu[cpu])
		वापस fd_instr_count_percpu[cpu];

	fd_instr_count_percpu[cpu] = perf_instr_count_खोलो(cpu);

	वापस fd_instr_count_percpu[cpu];
पूर्ण

पूर्णांक get_msr(पूर्णांक cpu, off_t offset, अचिन्हित दीर्घ दीर्घ *msr)
अणु
	sमाप_प्रकार retval;

	retval = pपढ़ो(get_msr_fd(cpu), msr, माप(*msr), offset);

	अगर (retval != माप *msr)
		err(-1, "cpu%d: msr offset 0x%llx read failed", cpu, (अचिन्हित दीर्घ दीर्घ)offset);

	वापस 0;
पूर्ण

/*
 * This list matches the column headers, except
 * 1. built-in only, the sysfs counters are not here -- we learn of those at run-समय
 * 2. Core and CPU are moved to the end, we can't have strings that contain them
 *    matching on them क्रम --show and --hide.
 */
काष्ठा msr_counter bic[] = अणु
	अणु 0x0, "usec" पूर्ण,
	अणु 0x0, "Time_Of_Day_Seconds" पूर्ण,
	अणु 0x0, "Package" पूर्ण,
	अणु 0x0, "Node" पूर्ण,
	अणु 0x0, "Avg_MHz" पूर्ण,
	अणु 0x0, "Busy%" पूर्ण,
	अणु 0x0, "Bzy_MHz" पूर्ण,
	अणु 0x0, "TSC_MHz" पूर्ण,
	अणु 0x0, "IRQ" पूर्ण,
	अणु 0x0, "SMI", "", 32, 0, FORMAT_DELTA, शून्य पूर्ण,
	अणु 0x0, "sysfs" पूर्ण,
	अणु 0x0, "CPU%c1" पूर्ण,
	अणु 0x0, "CPU%c3" पूर्ण,
	अणु 0x0, "CPU%c6" पूर्ण,
	अणु 0x0, "CPU%c7" पूर्ण,
	अणु 0x0, "ThreadC" पूर्ण,
	अणु 0x0, "CoreTmp" पूर्ण,
	अणु 0x0, "CoreCnt" पूर्ण,
	अणु 0x0, "PkgTmp" पूर्ण,
	अणु 0x0, "GFX%rc6" पूर्ण,
	अणु 0x0, "GFXMHz" पूर्ण,
	अणु 0x0, "Pkg%pc2" पूर्ण,
	अणु 0x0, "Pkg%pc3" पूर्ण,
	अणु 0x0, "Pkg%pc6" पूर्ण,
	अणु 0x0, "Pkg%pc7" पूर्ण,
	अणु 0x0, "Pkg%pc8" पूर्ण,
	अणु 0x0, "Pkg%pc9" पूर्ण,
	अणु 0x0, "Pk%pc10" पूर्ण,
	अणु 0x0, "CPU%LPI" पूर्ण,
	अणु 0x0, "SYS%LPI" पूर्ण,
	अणु 0x0, "PkgWatt" पूर्ण,
	अणु 0x0, "CorWatt" पूर्ण,
	अणु 0x0, "GFXWatt" पूर्ण,
	अणु 0x0, "PkgCnt" पूर्ण,
	अणु 0x0, "RAMWatt" पूर्ण,
	अणु 0x0, "PKG_%" पूर्ण,
	अणु 0x0, "RAM_%" पूर्ण,
	अणु 0x0, "Pkg_J" पूर्ण,
	अणु 0x0, "Cor_J" पूर्ण,
	अणु 0x0, "GFX_J" पूर्ण,
	अणु 0x0, "RAM_J" पूर्ण,
	अणु 0x0, "Mod%c6" पूर्ण,
	अणु 0x0, "Totl%C0" पूर्ण,
	अणु 0x0, "Any%C0" पूर्ण,
	अणु 0x0, "GFX%C0" पूर्ण,
	अणु 0x0, "CPUGFX%" पूर्ण,
	अणु 0x0, "Core" पूर्ण,
	अणु 0x0, "CPU" पूर्ण,
	अणु 0x0, "APIC" पूर्ण,
	अणु 0x0, "X2APIC" पूर्ण,
	अणु 0x0, "Die" पूर्ण,
	अणु 0x0, "GFXAMHz" पूर्ण,
	अणु 0x0, "IPC" पूर्ण,
पूर्ण;

#घोषणा MAX_BIC (माप(bic) / माप(काष्ठा msr_counter))
#घोषणा	BIC_USEC	(1ULL << 0)
#घोषणा	BIC_TOD		(1ULL << 1)
#घोषणा	BIC_Package	(1ULL << 2)
#घोषणा	BIC_Node	(1ULL << 3)
#घोषणा	BIC_Avg_MHz	(1ULL << 4)
#घोषणा	BIC_Busy	(1ULL << 5)
#घोषणा	BIC_Bzy_MHz	(1ULL << 6)
#घोषणा	BIC_TSC_MHz	(1ULL << 7)
#घोषणा	BIC_IRQ		(1ULL << 8)
#घोषणा	BIC_SMI		(1ULL << 9)
#घोषणा	BIC_sysfs	(1ULL << 10)
#घोषणा	BIC_CPU_c1	(1ULL << 11)
#घोषणा	BIC_CPU_c3	(1ULL << 12)
#घोषणा	BIC_CPU_c6	(1ULL << 13)
#घोषणा	BIC_CPU_c7	(1ULL << 14)
#घोषणा	BIC_Thपढ़ोC	(1ULL << 15)
#घोषणा	BIC_CoreTmp	(1ULL << 16)
#घोषणा	BIC_CoreCnt	(1ULL << 17)
#घोषणा	BIC_PkgTmp	(1ULL << 18)
#घोषणा	BIC_GFX_rc6	(1ULL << 19)
#घोषणा	BIC_GFXMHz	(1ULL << 20)
#घोषणा	BIC_Pkgpc2	(1ULL << 21)
#घोषणा	BIC_Pkgpc3	(1ULL << 22)
#घोषणा	BIC_Pkgpc6	(1ULL << 23)
#घोषणा	BIC_Pkgpc7	(1ULL << 24)
#घोषणा	BIC_Pkgpc8	(1ULL << 25)
#घोषणा	BIC_Pkgpc9	(1ULL << 26)
#घोषणा	BIC_Pkgpc10	(1ULL << 27)
#घोषणा BIC_CPU_LPI	(1ULL << 28)
#घोषणा BIC_SYS_LPI	(1ULL << 29)
#घोषणा	BIC_PkgWatt	(1ULL << 30)
#घोषणा	BIC_CorWatt	(1ULL << 31)
#घोषणा	BIC_GFXWatt	(1ULL << 32)
#घोषणा	BIC_PkgCnt	(1ULL << 33)
#घोषणा	BIC_RAMWatt	(1ULL << 34)
#घोषणा	BIC_PKG__	(1ULL << 35)
#घोषणा	BIC_RAM__	(1ULL << 36)
#घोषणा	BIC_Pkg_J	(1ULL << 37)
#घोषणा	BIC_Cor_J	(1ULL << 38)
#घोषणा	BIC_GFX_J	(1ULL << 39)
#घोषणा	BIC_RAM_J	(1ULL << 40)
#घोषणा	BIC_Mod_c6	(1ULL << 41)
#घोषणा	BIC_Totl_c0	(1ULL << 42)
#घोषणा	BIC_Any_c0	(1ULL << 43)
#घोषणा	BIC_GFX_c0	(1ULL << 44)
#घोषणा	BIC_CPUGFX	(1ULL << 45)
#घोषणा	BIC_Core	(1ULL << 46)
#घोषणा	BIC_CPU		(1ULL << 47)
#घोषणा	BIC_APIC	(1ULL << 48)
#घोषणा	BIC_X2APIC	(1ULL << 49)
#घोषणा	BIC_Die		(1ULL << 50)
#घोषणा	BIC_GFXACTMHz	(1ULL << 51)
#घोषणा	BIC_IPC		(1ULL << 52)

#घोषणा BIC_TOPOLOGY (BIC_Package | BIC_Node | BIC_CoreCnt | BIC_PkgCnt | BIC_Core | BIC_CPU | BIC_Die )
#घोषणा BIC_THERMAL_PWR ( BIC_CoreTmp | BIC_PkgTmp | BIC_PkgWatt | BIC_CorWatt | BIC_GFXWatt | BIC_RAMWatt | BIC_PKG__ | BIC_RAM__)
#घोषणा BIC_FREQUENCY ( BIC_Avg_MHz | BIC_Busy | BIC_Bzy_MHz | BIC_TSC_MHz | BIC_GFXMHz | BIC_GFXACTMHz )
#घोषणा BIC_IDLE ( BIC_sysfs | BIC_CPU_c1 | BIC_CPU_c3 | BIC_CPU_c6 | BIC_CPU_c7 | BIC_GFX_rc6 | BIC_Pkgpc2 | BIC_Pkgpc3 | BIC_Pkgpc6 | BIC_Pkgpc7 | BIC_Pkgpc8 | BIC_Pkgpc9 | BIC_Pkgpc10 | BIC_CPU_LPI | BIC_SYS_LPI | BIC_Mod_c6 | BIC_Totl_c0 | BIC_Any_c0 | BIC_GFX_c0 | BIC_CPUGFX)
#घोषणा BIC_OTHER ( BIC_IRQ | BIC_SMI | BIC_Thपढ़ोC | BIC_CoreTmp | BIC_IPC)

#घोषणा BIC_DISABLED_BY_DEFAULT	(BIC_USEC | BIC_TOD | BIC_APIC | BIC_X2APIC)

अचिन्हित दीर्घ दीर्घ bic_enabled = (0xFFFFFFFFFFFFFFFFULL & ~BIC_DISABLED_BY_DEFAULT);
अचिन्हित दीर्घ दीर्घ bic_present = BIC_USEC | BIC_TOD | BIC_sysfs | BIC_APIC | BIC_X2APIC;

#घोषणा DO_BIC(COUNTER_NAME) (bic_enabled & bic_present & COUNTER_NAME)
#घोषणा DO_BIC_READ(COUNTER_NAME) (bic_present & COUNTER_NAME)
#घोषणा ENABLE_BIC(COUNTER_NAME) (bic_enabled |= COUNTER_NAME)
#घोषणा BIC_PRESENT(COUNTER_BIT) (bic_present |= COUNTER_BIT)
#घोषणा BIC_NOT_PRESENT(COUNTER_BIT) (bic_present &= ~COUNTER_BIT)
#घोषणा BIC_IS_ENABLED(COUNTER_BIT) (bic_enabled & COUNTER_BIT)

#घोषणा MAX_DEFERRED 16
अक्षर *deferred_skip_names[MAX_DEFERRED];
पूर्णांक deferred_skip_index;

/*
 * HIDE_LIST - hide this list of counters, show the rest [शेष]
 * SHOW_LIST - show this list of counters, hide the rest
 */
क्रमागत show_hide_mode अणु SHOW_LIST, HIDE_LIST पूर्ण global_show_hide_mode = HIDE_LIST;

व्योम help(व्योम)
अणु
	ख_लिखो(outf,
		"Usage: turbostat [OPTIONS][(--interval seconds) | COMMAND ...]\n"
		"\n"
		"Turbostat forks the specified COMMAND and prints statistics\n"
		"when COMMAND completes.\n"
		"If no COMMAND is specified, turbostat wakes every 5-seconds\n"
		"to print statistics, until interrupted.\n"
		"  -a, --add	add a counter\n"
		"		  eg. --add msr0x10,u64,cpu,delta,MY_TSC\n"
		"  -c, --cpu	cpu-set	limit output to summary plus cpu-set:\n"
		"		  {core | package | j,k,l..m,n-p }\n"
		"  -d, --debug	displays usec, Time_Of_Day_Seconds and more debugging\n"
		"  -D, --Dump	displays the raw counter values\n"
		"  -e, --enable	[all | column]\n"
		"		shows all or the specified disabled column\n"
		"  -H, --hide [column|column,column,...]\n"
		"		hide the specified column(s)\n"
		"  -i, --interval sec.subsec\n"
		"		Override default 5-second measurement interval\n"
		"  -J, --Joules	displays energy in Joules instead of Watts\n"
		"  -l, --list	list column headers only\n"
		"  -n, --num_iterations num\n"
		"		number of the measurement iterations\n"
		"  -o, --out file\n"
		"		create or truncate \"file\" for all output\n"
		"  -q, --quiet	skip decoding system configuration header\n"
		"  -s, --show [column|column,column,...]\n"
		"		show only the specified column(s)\n"
		"  -S, --Summary\n"
		"		limits output to 1-line system summary per interval\n"
		"  -T, --TCC temperature\n"
		"		sets the Thermal Control Circuit temperature in\n"
		"		  degrees Celsius\n"
		"  -h, --help	print this help message\n"
		"  -v, --version	print version information\n" "\n" "For more help, run \"man turbostat\"\n");
पूर्ण

/*
 * bic_lookup
 * क्रम all the strings in comma separate name_list,
 * set the approprate bit in वापस value.
 */
अचिन्हित दीर्घ दीर्घ bic_lookup(अक्षर *name_list, क्रमागत show_hide_mode mode)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ retval = 0;

	जबतक (name_list) अणु
		अक्षर *comma;

		comma = म_अक्षर(name_list, ',');

		अगर (comma)
			*comma = '\0';

		अगर (!म_भेद(name_list, "all"))
			वापस ~0;
		अगर (!म_भेद(name_list, "topology"))
			वापस BIC_TOPOLOGY;
		अगर (!म_भेद(name_list, "power"))
			वापस BIC_THERMAL_PWR;
		अगर (!म_भेद(name_list, "idle"))
			वापस BIC_IDLE;
		अगर (!म_भेद(name_list, "frequency"))
			वापस BIC_FREQUENCY;
		अगर (!म_भेद(name_list, "other"))
			वापस BIC_OTHER;
		अगर (!म_भेद(name_list, "all"))
			वापस 0;

		क्रम (i = 0; i < MAX_BIC; ++i) अणु
			अगर (!म_भेद(name_list, bic[i].name)) अणु
				retval |= (1ULL << i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == MAX_BIC) अणु
			अगर (mode == SHOW_LIST) अणु
				ख_लिखो(मानक_त्रुटि, "Invalid counter name: %s\n", name_list);
				निकास(-1);
			पूर्ण
			deferred_skip_names[deferred_skip_index++] = name_list;
			अगर (debug)
				ख_लिखो(मानक_त्रुटि, "deferred \"%s\"\n", name_list);
			अगर (deferred_skip_index >= MAX_DEFERRED) अणु
				ख_लिखो(मानक_त्रुटि, "More than max %d un-recognized --skip options '%s'\n",
					MAX_DEFERRED, name_list);
				help();
				निकास(1);
			पूर्ण
		पूर्ण

		name_list = comma;
		अगर (name_list)
			name_list++;

	पूर्ण
	वापस retval;
पूर्ण

व्योम prपूर्णांक_header(अक्षर *delim)
अणु
	काष्ठा msr_counter *mp;
	पूर्णांक prपूर्णांकed = 0;

	अगर (DO_BIC(BIC_USEC))
		outp += प्र_लिखो(outp, "%susec", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_TOD))
		outp += प्र_लिखो(outp, "%sTime_Of_Day_Seconds", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Package))
		outp += प्र_लिखो(outp, "%sPackage", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Die))
		outp += प्र_लिखो(outp, "%sDie", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Node))
		outp += प्र_लिखो(outp, "%sNode", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Core))
		outp += प्र_लिखो(outp, "%sCore", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_CPU))
		outp += प्र_लिखो(outp, "%sCPU", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_APIC))
		outp += प्र_लिखो(outp, "%sAPIC", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_X2APIC))
		outp += प्र_लिखो(outp, "%sX2APIC", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Avg_MHz))
		outp += प्र_लिखो(outp, "%sAvg_MHz", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Busy))
		outp += प्र_लिखो(outp, "%sBusy%%", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Bzy_MHz))
		outp += प्र_लिखो(outp, "%sBzy_MHz", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_TSC_MHz))
		outp += प्र_लिखो(outp, "%sTSC_MHz", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_IPC))
		outp += प्र_लिखो(outp, "%sIPC", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_IRQ)) अणु
		अगर (sums_need_wide_columns)
			outp += प्र_लिखो(outp, "%s     IRQ", (prपूर्णांकed++ ? delim : ""));
		अन्यथा
			outp += प्र_लिखो(outp, "%sIRQ", (prपूर्णांकed++ ? delim : ""));
	पूर्ण

	अगर (DO_BIC(BIC_SMI))
		outp += प्र_लिखो(outp, "%sSMI", (prपूर्णांकed++ ? delim : ""));

	क्रम (mp = sys.tp; mp; mp = mp->next) अणु

		अगर (mp->क्रमmat == FORMAT_RAW) अणु
			अगर (mp->width == 64)
				outp += प्र_लिखो(outp, "%s%18.18s", (prपूर्णांकed++ ? delim : ""), mp->name);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%10.10s", (prपूर्णांकed++ ? delim : ""), mp->name);
		पूर्ण अन्यथा अणु
			अगर ((mp->type == COUNTER_ITEMS) && sums_need_wide_columns)
				outp += प्र_लिखो(outp, "%s%8s", (prपूर्णांकed++ ? delim : ""), mp->name);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%s", (prपूर्णांकed++ ? delim : ""), mp->name);
		पूर्ण
	पूर्ण

	अगर (DO_BIC(BIC_CPU_c1))
		outp += प्र_लिखो(outp, "%sCPU%%c1", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_CPU_c3))
		outp += प्र_लिखो(outp, "%sCPU%%c3", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_CPU_c6))
		outp += प्र_लिखो(outp, "%sCPU%%c6", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_CPU_c7))
		outp += प्र_लिखो(outp, "%sCPU%%c7", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_Mod_c6))
		outp += प्र_लिखो(outp, "%sMod%%c6", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_CoreTmp))
		outp += प्र_लिखो(outp, "%sCoreTmp", (prपूर्णांकed++ ? delim : ""));

	अगर (करो_rapl && !rapl_joules) अणु
		अगर (DO_BIC(BIC_CorWatt) && (करो_rapl & RAPL_PER_CORE_ENERGY))
			outp += प्र_लिखो(outp, "%sCorWatt", (prपूर्णांकed++ ? delim : ""));
	पूर्ण अन्यथा अगर (करो_rapl && rapl_joules) अणु
		अगर (DO_BIC(BIC_Cor_J) && (करो_rapl & RAPL_PER_CORE_ENERGY))
			outp += प्र_लिखो(outp, "%sCor_J", (prपूर्णांकed++ ? delim : ""));
	पूर्ण

	क्रम (mp = sys.cp; mp; mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW) अणु
			अगर (mp->width == 64)
				outp += प्र_लिखो(outp, "%s%18.18s", delim, mp->name);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%10.10s", delim, mp->name);
		पूर्ण अन्यथा अणु
			अगर ((mp->type == COUNTER_ITEMS) && sums_need_wide_columns)
				outp += प्र_लिखो(outp, "%s%8s", delim, mp->name);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%s", delim, mp->name);
		पूर्ण
	पूर्ण

	अगर (DO_BIC(BIC_PkgTmp))
		outp += प्र_लिखो(outp, "%sPkgTmp", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_GFX_rc6))
		outp += प्र_लिखो(outp, "%sGFX%%rc6", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_GFXMHz))
		outp += प्र_लिखो(outp, "%sGFXMHz", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_GFXACTMHz))
		outp += प्र_लिखो(outp, "%sGFXAMHz", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_Totl_c0))
		outp += प्र_लिखो(outp, "%sTotl%%C0", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Any_c0))
		outp += प्र_लिखो(outp, "%sAny%%C0", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_GFX_c0))
		outp += प्र_लिखो(outp, "%sGFX%%C0", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_CPUGFX))
		outp += प्र_लिखो(outp, "%sCPUGFX%%", (prपूर्णांकed++ ? delim : ""));

	अगर (DO_BIC(BIC_Pkgpc2))
		outp += प्र_लिखो(outp, "%sPkg%%pc2", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Pkgpc3))
		outp += प्र_लिखो(outp, "%sPkg%%pc3", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Pkgpc6))
		outp += प्र_लिखो(outp, "%sPkg%%pc6", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Pkgpc7))
		outp += प्र_लिखो(outp, "%sPkg%%pc7", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Pkgpc8))
		outp += प्र_लिखो(outp, "%sPkg%%pc8", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Pkgpc9))
		outp += प्र_लिखो(outp, "%sPkg%%pc9", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_Pkgpc10))
		outp += प्र_लिखो(outp, "%sPk%%pc10", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_CPU_LPI))
		outp += प्र_लिखो(outp, "%sCPU%%LPI", (prपूर्णांकed++ ? delim : ""));
	अगर (DO_BIC(BIC_SYS_LPI))
		outp += प्र_लिखो(outp, "%sSYS%%LPI", (prपूर्णांकed++ ? delim : ""));

	अगर (करो_rapl && !rapl_joules) अणु
		अगर (DO_BIC(BIC_PkgWatt))
			outp += प्र_लिखो(outp, "%sPkgWatt", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_CorWatt) && !(करो_rapl & RAPL_PER_CORE_ENERGY))
			outp += प्र_लिखो(outp, "%sCorWatt", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_GFXWatt))
			outp += प्र_लिखो(outp, "%sGFXWatt", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_RAMWatt))
			outp += प्र_लिखो(outp, "%sRAMWatt", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_PKG__))
			outp += प्र_लिखो(outp, "%sPKG_%%", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_RAM__))
			outp += प्र_लिखो(outp, "%sRAM_%%", (prपूर्णांकed++ ? delim : ""));
	पूर्ण अन्यथा अगर (करो_rapl && rapl_joules) अणु
		अगर (DO_BIC(BIC_Pkg_J))
			outp += प्र_लिखो(outp, "%sPkg_J", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_Cor_J) && !(करो_rapl & RAPL_PER_CORE_ENERGY))
			outp += प्र_लिखो(outp, "%sCor_J", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_GFX_J))
			outp += प्र_लिखो(outp, "%sGFX_J", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_RAM_J))
			outp += प्र_लिखो(outp, "%sRAM_J", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_PKG__))
			outp += प्र_लिखो(outp, "%sPKG_%%", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_RAM__))
			outp += प्र_लिखो(outp, "%sRAM_%%", (prपूर्णांकed++ ? delim : ""));
	पूर्ण
	क्रम (mp = sys.pp; mp; mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW) अणु
			अगर (mp->width == 64)
				outp += प्र_लिखो(outp, "%s%18.18s", delim, mp->name);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%10.10s", delim, mp->name);
		पूर्ण अन्यथा अणु
			अगर ((mp->type == COUNTER_ITEMS) && sums_need_wide_columns)
				outp += प्र_लिखो(outp, "%s%8s", delim, mp->name);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%s", delim, mp->name);
		पूर्ण
	पूर्ण

	outp += प्र_लिखो(outp, "\n");
पूर्ण

पूर्णांक dump_counters(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	पूर्णांक i;
	काष्ठा msr_counter *mp;

	outp += प्र_लिखो(outp, "t %p, c %p, p %p\n", t, c, p);

	अगर (t) अणु
		outp += प्र_लिखो(outp, "CPU: %d flags 0x%x\n", t->cpu_id, t->flags);
		outp += प्र_लिखो(outp, "TSC: %016llX\n", t->tsc);
		outp += प्र_लिखो(outp, "aperf: %016llX\n", t->aperf);
		outp += प्र_लिखो(outp, "mperf: %016llX\n", t->mperf);
		outp += प्र_लिखो(outp, "c1: %016llX\n", t->c1);

		अगर (DO_BIC(BIC_IPC))
			outp += प्र_लिखो(outp, "IPC: %lld\n", t->instr_count);

		अगर (DO_BIC(BIC_IRQ))
			outp += प्र_लिखो(outp, "IRQ: %lld\n", t->irq_count);
		अगर (DO_BIC(BIC_SMI))
			outp += प्र_लिखो(outp, "SMI: %d\n", t->smi_count);

		क्रम (i = 0, mp = sys.tp; mp; i++, mp = mp->next) अणु
			outp += प्र_लिखो(outp, "tADDED [%d] msr0x%x: %08llX\n", i, mp->msr_num, t->counter[i]);
		पूर्ण
	पूर्ण

	अगर (c) अणु
		outp += प्र_लिखो(outp, "core: %d\n", c->core_id);
		outp += प्र_लिखो(outp, "c3: %016llX\n", c->c3);
		outp += प्र_लिखो(outp, "c6: %016llX\n", c->c6);
		outp += प्र_लिखो(outp, "c7: %016llX\n", c->c7);
		outp += प्र_लिखो(outp, "DTS: %dC\n", c->core_temp_c);
		outp += प्र_लिखो(outp, "Joules: %0X\n", c->core_energy);

		क्रम (i = 0, mp = sys.cp; mp; i++, mp = mp->next) अणु
			outp += प्र_लिखो(outp, "cADDED [%d] msr0x%x: %08llX\n", i, mp->msr_num, c->counter[i]);
		पूर्ण
		outp += प्र_लिखो(outp, "mc6_us: %016llX\n", c->mc6_us);
	पूर्ण

	अगर (p) अणु
		outp += प्र_लिखो(outp, "package: %d\n", p->package_id);

		outp += प्र_लिखो(outp, "Weighted cores: %016llX\n", p->pkg_wtd_core_c0);
		outp += प्र_लिखो(outp, "Any cores: %016llX\n", p->pkg_any_core_c0);
		outp += प्र_लिखो(outp, "Any GFX: %016llX\n", p->pkg_any_gfxe_c0);
		outp += प्र_लिखो(outp, "CPU + GFX: %016llX\n", p->pkg_both_core_gfxe_c0);

		outp += प्र_लिखो(outp, "pc2: %016llX\n", p->pc2);
		अगर (DO_BIC(BIC_Pkgpc3))
			outp += प्र_लिखो(outp, "pc3: %016llX\n", p->pc3);
		अगर (DO_BIC(BIC_Pkgpc6))
			outp += प्र_लिखो(outp, "pc6: %016llX\n", p->pc6);
		अगर (DO_BIC(BIC_Pkgpc7))
			outp += प्र_लिखो(outp, "pc7: %016llX\n", p->pc7);
		outp += प्र_लिखो(outp, "pc8: %016llX\n", p->pc8);
		outp += प्र_लिखो(outp, "pc9: %016llX\n", p->pc9);
		outp += प्र_लिखो(outp, "pc10: %016llX\n", p->pc10);
		outp += प्र_लिखो(outp, "cpu_lpi: %016llX\n", p->cpu_lpi);
		outp += प्र_लिखो(outp, "sys_lpi: %016llX\n", p->sys_lpi);
		outp += प्र_लिखो(outp, "Joules PKG: %0llX\n", p->energy_pkg);
		outp += प्र_लिखो(outp, "Joules COR: %0llX\n", p->energy_cores);
		outp += प्र_लिखो(outp, "Joules GFX: %0llX\n", p->energy_gfx);
		outp += प्र_लिखो(outp, "Joules RAM: %0llX\n", p->energy_dram);
		outp += प्र_लिखो(outp, "Throttle PKG: %0llX\n", p->rapl_pkg_perf_status);
		outp += प्र_लिखो(outp, "Throttle RAM: %0llX\n", p->rapl_dram_perf_status);
		outp += प्र_लिखो(outp, "PTM: %dC\n", p->pkg_temp_c);

		क्रम (i = 0, mp = sys.pp; mp; i++, mp = mp->next) अणु
			outp += प्र_लिखो(outp, "pADDED [%d] msr0x%x: %08llX\n", i, mp->msr_num, p->counter[i]);
		पूर्ण
	पूर्ण

	outp += प्र_लिखो(outp, "\n");

	वापस 0;
पूर्ण

/*
 * column क्रमmatting convention & क्रमmats
 */
पूर्णांक क्रमmat_counters(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	द्विगुन पूर्णांकerval_भग्न, tsc;
	अक्षर *fmt8;
	पूर्णांक i;
	काष्ठा msr_counter *mp;
	अक्षर *delim = "\t";
	पूर्णांक prपूर्णांकed = 0;

	/* अगर showing only 1st thपढ़ो in core and this isn't one, bail out */
	अगर (show_core_only && !(t->flags & CPU_IS_FIRST_THREAD_IN_CORE))
		वापस 0;

	/* अगर showing only 1st thपढ़ो in pkg and this isn't one, bail out */
	अगर (show_pkg_only && !(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		वापस 0;

	/*अगर not summary line and --cpu is used */
	अगर ((t != &average.thपढ़ोs) && (cpu_subset && !CPU_ISSET_S(t->cpu_id, cpu_subset_size, cpu_subset)))
		वापस 0;

	अगर (DO_BIC(BIC_USEC)) अणु
		/* on each row, prपूर्णांक how many usec each बारtamp took to gather */
		काष्ठा समयval tv;

		समयrsub(&t->tv_end, &t->tv_begin, &tv);
		outp += प्र_लिखो(outp, "%5ld\t", tv.tv_sec * 1000000 + tv.tv_usec);
	पूर्ण

	/* Time_Of_Day_Seconds: on each row, prपूर्णांक sec.usec last बारtamp taken */
	अगर (DO_BIC(BIC_TOD))
		outp += प्र_लिखो(outp, "%10ld.%06ld\t", t->tv_end.tv_sec, t->tv_end.tv_usec);

	पूर्णांकerval_भग्न = t->tv_delta.tv_sec + t->tv_delta.tv_usec / 1000000.0;

	tsc = t->tsc * tsc_tweak;

	/* topo columns, prपूर्णांक blanks on 1st (average) line */
	अगर (t == &average.thपढ़ोs) अणु
		अगर (DO_BIC(BIC_Package))
			outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_Die))
			outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_Node))
			outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_Core))
			outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_CPU))
			outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_APIC))
			outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		अगर (DO_BIC(BIC_X2APIC))
			outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
	पूर्ण अन्यथा अणु
		अगर (DO_BIC(BIC_Package)) अणु
			अगर (p)
				outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), p->package_id);
			अन्यथा
				outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		पूर्ण
		अगर (DO_BIC(BIC_Die)) अणु
			अगर (c)
				outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), cpus[t->cpu_id].die_id);
			अन्यथा
				outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		पूर्ण
		अगर (DO_BIC(BIC_Node)) अणु
			अगर (t)
				outp += प्र_लिखो(outp, "%s%d",
						(prपूर्णांकed++ ? delim : ""), cpus[t->cpu_id].physical_node_id);
			अन्यथा
				outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		पूर्ण
		अगर (DO_BIC(BIC_Core)) अणु
			अगर (c)
				outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), c->core_id);
			अन्यथा
				outp += प्र_लिखो(outp, "%s-", (prपूर्णांकed++ ? delim : ""));
		पूर्ण
		अगर (DO_BIC(BIC_CPU))
			outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), t->cpu_id);
		अगर (DO_BIC(BIC_APIC))
			outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), t->apic_id);
		अगर (DO_BIC(BIC_X2APIC))
			outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), t->x2apic_id);
	पूर्ण

	अगर (DO_BIC(BIC_Avg_MHz))
		outp += प्र_लिखो(outp, "%s%.0f", (prपूर्णांकed++ ? delim : ""), 1.0 / units * t->aperf / पूर्णांकerval_भग्न);

	अगर (DO_BIC(BIC_Busy))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * t->mperf / tsc);

	अगर (DO_BIC(BIC_Bzy_MHz)) अणु
		अगर (has_base_hz)
			outp +=
			    प्र_लिखो(outp, "%s%.0f", (prपूर्णांकed++ ? delim : ""), base_hz / units * t->aperf / t->mperf);
		अन्यथा
			outp += प्र_लिखो(outp, "%s%.0f", (prपूर्णांकed++ ? delim : ""),
					tsc / units * t->aperf / t->mperf / पूर्णांकerval_भग्न);
	पूर्ण

	अगर (DO_BIC(BIC_TSC_MHz))
		outp += प्र_लिखो(outp, "%s%.0f", (prपूर्णांकed++ ? delim : ""), 1.0 * t->tsc / units / पूर्णांकerval_भग्न);

	अगर (DO_BIC(BIC_IPC))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 1.0 * t->instr_count / t->aperf);

	/* IRQ */
	अगर (DO_BIC(BIC_IRQ)) अणु
		अगर (sums_need_wide_columns)
			outp += प्र_लिखो(outp, "%s%8lld", (prपूर्णांकed++ ? delim : ""), t->irq_count);
		अन्यथा
			outp += प्र_लिखो(outp, "%s%lld", (prपूर्णांकed++ ? delim : ""), t->irq_count);
	पूर्ण

	/* SMI */
	अगर (DO_BIC(BIC_SMI))
		outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), t->smi_count);

	/* Added counters */
	क्रम (i = 0, mp = sys.tp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW) अणु
			अगर (mp->width == 32)
				outp +=
				    प्र_लिखो(outp, "%s0x%08x", (prपूर्णांकed++ ? delim : ""), (अचिन्हित पूर्णांक)t->counter[i]);
			अन्यथा
				outp += प्र_लिखो(outp, "%s0x%016llx", (prपूर्णांकed++ ? delim : ""), t->counter[i]);
		पूर्ण अन्यथा अगर (mp->क्रमmat == FORMAT_DELTA) अणु
			अगर ((mp->type == COUNTER_ITEMS) && sums_need_wide_columns)
				outp += प्र_लिखो(outp, "%s%8lld", (prपूर्णांकed++ ? delim : ""), t->counter[i]);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%lld", (prपूर्णांकed++ ? delim : ""), t->counter[i]);
		पूर्ण अन्यथा अगर (mp->क्रमmat == FORMAT_PERCENT) अणु
			अगर (mp->type == COUNTER_USEC)
				outp +=
				    प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""),
					    t->counter[i] / पूर्णांकerval_भग्न / 10000);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * t->counter[i] / tsc);
		पूर्ण
	पूर्ण

	/* C1 */
	अगर (DO_BIC(BIC_CPU_c1))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * t->c1 / tsc);

	/* prपूर्णांक per-core data only क्रम 1st thपढ़ो in core */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE))
		जाओ करोne;

	अगर (DO_BIC(BIC_CPU_c3))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * c->c3 / tsc);
	अगर (DO_BIC(BIC_CPU_c6))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * c->c6 / tsc);
	अगर (DO_BIC(BIC_CPU_c7))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * c->c7 / tsc);

	/* Mod%c6 */
	अगर (DO_BIC(BIC_Mod_c6))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * c->mc6_us / tsc);

	अगर (DO_BIC(BIC_CoreTmp))
		outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), c->core_temp_c);

	क्रम (i = 0, mp = sys.cp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW) अणु
			अगर (mp->width == 32)
				outp +=
				    प्र_लिखो(outp, "%s0x%08x", (prपूर्णांकed++ ? delim : ""), (अचिन्हित पूर्णांक)c->counter[i]);
			अन्यथा
				outp += प्र_लिखो(outp, "%s0x%016llx", (prपूर्णांकed++ ? delim : ""), c->counter[i]);
		पूर्ण अन्यथा अगर (mp->क्रमmat == FORMAT_DELTA) अणु
			अगर ((mp->type == COUNTER_ITEMS) && sums_need_wide_columns)
				outp += प्र_लिखो(outp, "%s%8lld", (prपूर्णांकed++ ? delim : ""), c->counter[i]);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%lld", (prपूर्णांकed++ ? delim : ""), c->counter[i]);
		पूर्ण अन्यथा अगर (mp->क्रमmat == FORMAT_PERCENT) अणु
			outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * c->counter[i] / tsc);
		पूर्ण
	पूर्ण

	fmt8 = "%s%.2f";

	अगर (DO_BIC(BIC_CorWatt) && (करो_rapl & RAPL_PER_CORE_ENERGY))
		outp +=
		    प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), c->core_energy * rapl_energy_units / पूर्णांकerval_भग्न);
	अगर (DO_BIC(BIC_Cor_J) && (करो_rapl & RAPL_PER_CORE_ENERGY))
		outp += प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), c->core_energy * rapl_energy_units);

	/* prपूर्णांक per-package data only क्रम 1st core in package */
	अगर (!(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		जाओ करोne;

	/* PkgTmp */
	अगर (DO_BIC(BIC_PkgTmp))
		outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), p->pkg_temp_c);

	/* GFXrc6 */
	अगर (DO_BIC(BIC_GFX_rc6)) अणु
		अगर (p->gfx_rc6_ms == -1) अणु	/* detect GFX counter reset */
			outp += प्र_लिखो(outp, "%s**.**", (prपूर्णांकed++ ? delim : ""));
		पूर्ण अन्यथा अणु
			outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""),
					p->gfx_rc6_ms / 10.0 / पूर्णांकerval_भग्न);
		पूर्ण
	पूर्ण

	/* GFXMHz */
	अगर (DO_BIC(BIC_GFXMHz))
		outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), p->gfx_mhz);

	/* GFXACTMHz */
	अगर (DO_BIC(BIC_GFXACTMHz))
		outp += प्र_लिखो(outp, "%s%d", (prपूर्णांकed++ ? delim : ""), p->gfx_act_mhz);

	/* Totl%C0, Any%C0 GFX%C0 CPUGFX% */
	अगर (DO_BIC(BIC_Totl_c0))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pkg_wtd_core_c0 / tsc);
	अगर (DO_BIC(BIC_Any_c0))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pkg_any_core_c0 / tsc);
	अगर (DO_BIC(BIC_GFX_c0))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pkg_any_gfxe_c0 / tsc);
	अगर (DO_BIC(BIC_CPUGFX))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pkg_both_core_gfxe_c0 / tsc);

	अगर (DO_BIC(BIC_Pkgpc2))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pc2 / tsc);
	अगर (DO_BIC(BIC_Pkgpc3))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pc3 / tsc);
	अगर (DO_BIC(BIC_Pkgpc6))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pc6 / tsc);
	अगर (DO_BIC(BIC_Pkgpc7))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pc7 / tsc);
	अगर (DO_BIC(BIC_Pkgpc8))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pc8 / tsc);
	अगर (DO_BIC(BIC_Pkgpc9))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pc9 / tsc);
	अगर (DO_BIC(BIC_Pkgpc10))
		outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->pc10 / tsc);

	अगर (DO_BIC(BIC_CPU_LPI))
		outp +=
		    प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->cpu_lpi / 1000000.0 / पूर्णांकerval_भग्न);
	अगर (DO_BIC(BIC_SYS_LPI))
		outp +=
		    प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->sys_lpi / 1000000.0 / पूर्णांकerval_भग्न);

	अगर (DO_BIC(BIC_PkgWatt))
		outp +=
		    प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), p->energy_pkg * rapl_energy_units / पूर्णांकerval_भग्न);
	अगर (DO_BIC(BIC_CorWatt) && !(करो_rapl & RAPL_PER_CORE_ENERGY))
		outp +=
		    प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), p->energy_cores * rapl_energy_units / पूर्णांकerval_भग्न);
	अगर (DO_BIC(BIC_GFXWatt))
		outp +=
		    प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), p->energy_gfx * rapl_energy_units / पूर्णांकerval_भग्न);
	अगर (DO_BIC(BIC_RAMWatt))
		outp +=
		    प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""),
			    p->energy_dram * rapl_dram_energy_units / पूर्णांकerval_भग्न);
	अगर (DO_BIC(BIC_Pkg_J))
		outp += प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), p->energy_pkg * rapl_energy_units);
	अगर (DO_BIC(BIC_Cor_J) && !(करो_rapl & RAPL_PER_CORE_ENERGY))
		outp += प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), p->energy_cores * rapl_energy_units);
	अगर (DO_BIC(BIC_GFX_J))
		outp += प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), p->energy_gfx * rapl_energy_units);
	अगर (DO_BIC(BIC_RAM_J))
		outp += प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""), p->energy_dram * rapl_dram_energy_units);
	अगर (DO_BIC(BIC_PKG__))
		outp +=
		    प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""),
			    100.0 * p->rapl_pkg_perf_status * rapl_समय_units / पूर्णांकerval_भग्न);
	अगर (DO_BIC(BIC_RAM__))
		outp +=
		    प्र_लिखो(outp, fmt8, (prपूर्णांकed++ ? delim : ""),
			    100.0 * p->rapl_dram_perf_status * rapl_समय_units / पूर्णांकerval_भग्न);

	क्रम (i = 0, mp = sys.pp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW) अणु
			अगर (mp->width == 32)
				outp +=
				    प्र_लिखो(outp, "%s0x%08x", (prपूर्णांकed++ ? delim : ""), (अचिन्हित पूर्णांक)p->counter[i]);
			अन्यथा
				outp += प्र_लिखो(outp, "%s0x%016llx", (prपूर्णांकed++ ? delim : ""), p->counter[i]);
		पूर्ण अन्यथा अगर (mp->क्रमmat == FORMAT_DELTA) अणु
			अगर ((mp->type == COUNTER_ITEMS) && sums_need_wide_columns)
				outp += प्र_लिखो(outp, "%s%8lld", (prपूर्णांकed++ ? delim : ""), p->counter[i]);
			अन्यथा
				outp += प्र_लिखो(outp, "%s%lld", (prपूर्णांकed++ ? delim : ""), p->counter[i]);
		पूर्ण अन्यथा अगर (mp->क्रमmat == FORMAT_PERCENT) अणु
			outp += प्र_लिखो(outp, "%s%.2f", (prपूर्णांकed++ ? delim : ""), 100.0 * p->counter[i] / tsc);
		पूर्ण
	पूर्ण

करोne:
	अगर (*(outp - 1) != '\n')
		outp += प्र_लिखो(outp, "\n");

	वापस 0;
पूर्ण

व्योम flush_output_मानक_निकास(व्योम)
अणु
	खाता *filep;

	अगर (outf == मानक_त्रुटि)
		filep = मानक_निकास;
	अन्यथा
		filep = outf;

	ख_माला_दो(output_buffer, filep);
	ख_साफ(filep);

	outp = output_buffer;
पूर्ण

व्योम flush_output_मानक_त्रुटि(व्योम)
अणु
	ख_माला_दो(output_buffer, outf);
	ख_साफ(outf);
	outp = output_buffer;
पूर्ण

व्योम क्रमmat_all_counters(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	अटल पूर्णांक prपूर्णांकed;

	अगर (!prपूर्णांकed || !summary_only)
		prपूर्णांक_header("\t");

	क्रमmat_counters(&average.thपढ़ोs, &average.cores, &average.packages);

	prपूर्णांकed = 1;

	अगर (summary_only)
		वापस;

	क्रम_all_cpus(क्रमmat_counters, t, c, p);
पूर्ण

#घोषणा DELTA_WRAP32(new, old)			\
	old = ((((अचिन्हित दीर्घ दीर्घ)new << 32) - ((अचिन्हित दीर्घ दीर्घ)old << 32)) >> 32);

पूर्णांक delta_package(काष्ठा pkg_data *new, काष्ठा pkg_data *old)
अणु
	पूर्णांक i;
	काष्ठा msr_counter *mp;

	अगर (DO_BIC(BIC_Totl_c0))
		old->pkg_wtd_core_c0 = new->pkg_wtd_core_c0 - old->pkg_wtd_core_c0;
	अगर (DO_BIC(BIC_Any_c0))
		old->pkg_any_core_c0 = new->pkg_any_core_c0 - old->pkg_any_core_c0;
	अगर (DO_BIC(BIC_GFX_c0))
		old->pkg_any_gfxe_c0 = new->pkg_any_gfxe_c0 - old->pkg_any_gfxe_c0;
	अगर (DO_BIC(BIC_CPUGFX))
		old->pkg_both_core_gfxe_c0 = new->pkg_both_core_gfxe_c0 - old->pkg_both_core_gfxe_c0;

	old->pc2 = new->pc2 - old->pc2;
	अगर (DO_BIC(BIC_Pkgpc3))
		old->pc3 = new->pc3 - old->pc3;
	अगर (DO_BIC(BIC_Pkgpc6))
		old->pc6 = new->pc6 - old->pc6;
	अगर (DO_BIC(BIC_Pkgpc7))
		old->pc7 = new->pc7 - old->pc7;
	old->pc8 = new->pc8 - old->pc8;
	old->pc9 = new->pc9 - old->pc9;
	old->pc10 = new->pc10 - old->pc10;
	old->cpu_lpi = new->cpu_lpi - old->cpu_lpi;
	old->sys_lpi = new->sys_lpi - old->sys_lpi;
	old->pkg_temp_c = new->pkg_temp_c;

	/* flag an error when rc6 counter resets/wraps */
	अगर (old->gfx_rc6_ms > new->gfx_rc6_ms)
		old->gfx_rc6_ms = -1;
	अन्यथा
		old->gfx_rc6_ms = new->gfx_rc6_ms - old->gfx_rc6_ms;

	old->gfx_mhz = new->gfx_mhz;
	old->gfx_act_mhz = new->gfx_act_mhz;

	old->energy_pkg = new->energy_pkg - old->energy_pkg;
	old->energy_cores = new->energy_cores - old->energy_cores;
	old->energy_gfx = new->energy_gfx - old->energy_gfx;
	old->energy_dram = new->energy_dram - old->energy_dram;
	old->rapl_pkg_perf_status = new->rapl_pkg_perf_status - old->rapl_pkg_perf_status;
	old->rapl_dram_perf_status = new->rapl_dram_perf_status - old->rapl_dram_perf_status;

	क्रम (i = 0, mp = sys.pp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			old->counter[i] = new->counter[i];
		अन्यथा
			old->counter[i] = new->counter[i] - old->counter[i];
	पूर्ण

	वापस 0;
पूर्ण

व्योम delta_core(काष्ठा core_data *new, काष्ठा core_data *old)
अणु
	पूर्णांक i;
	काष्ठा msr_counter *mp;

	old->c3 = new->c3 - old->c3;
	old->c6 = new->c6 - old->c6;
	old->c7 = new->c7 - old->c7;
	old->core_temp_c = new->core_temp_c;
	old->mc6_us = new->mc6_us - old->mc6_us;

	DELTA_WRAP32(new->core_energy, old->core_energy);

	क्रम (i = 0, mp = sys.cp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			old->counter[i] = new->counter[i];
		अन्यथा
			old->counter[i] = new->counter[i] - old->counter[i];
	पूर्ण
पूर्ण

पूर्णांक soft_c1_residency_display(पूर्णांक bic)
अणु
	अगर (!DO_BIC(BIC_CPU_c1) || use_c1_residency_msr)
		वापस 0;

	वापस DO_BIC_READ(bic);
पूर्ण

/*
 * old = new - old
 */
पूर्णांक delta_thपढ़ो(काष्ठा thपढ़ो_data *new, काष्ठा thपढ़ो_data *old, काष्ठा core_data *core_delta)
अणु
	पूर्णांक i;
	काष्ठा msr_counter *mp;

	/* we run cpuid just the 1st समय, copy the results */
	अगर (DO_BIC(BIC_APIC))
		new->apic_id = old->apic_id;
	अगर (DO_BIC(BIC_X2APIC))
		new->x2apic_id = old->x2apic_id;

	/*
	 * the बारtamps from start of measurement पूर्णांकerval are in "old"
	 * the बारtamp from end of measurement पूर्णांकerval are in "new"
	 * over-ग_लिखो old w/ new so we can prपूर्णांक end of पूर्णांकerval values
	 */

	समयrsub(&new->tv_begin, &old->tv_begin, &old->tv_delta);
	old->tv_begin = new->tv_begin;
	old->tv_end = new->tv_end;

	old->tsc = new->tsc - old->tsc;

	/* check क्रम TSC < 1 Mcycles over पूर्णांकerval */
	अगर (old->tsc < (1000 * 1000))
		errx(-3, "Insanely slow TSC rate, TSC stops in idle?\n"
		     "You can disable all c-states by booting with \"idle=poll\"\n"
		     "or just the deep ones with \"processor.max_cstate=1\"");

	old->c1 = new->c1 - old->c1;

	अगर (DO_BIC(BIC_Avg_MHz) || DO_BIC(BIC_Busy) || DO_BIC(BIC_Bzy_MHz) || soft_c1_residency_display(BIC_Avg_MHz)) अणु
		अगर ((new->aperf > old->aperf) && (new->mperf > old->mperf)) अणु
			old->aperf = new->aperf - old->aperf;
			old->mperf = new->mperf - old->mperf;
		पूर्ण अन्यथा अणु
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (use_c1_residency_msr) अणु
		/*
		 * Some models have a dedicated C1 residency MSR,
		 * which should be more accurate than the derivation below.
		 */
	पूर्ण अन्यथा अणु
		/*
		 * As counter collection is not atomic,
		 * it is possible क्रम mperf's non-halted cycles + idle states
		 * to exceed TSC's all cycles: show c1 = 0% in that हाल.
		 */
		अगर ((old->mperf + core_delta->c3 + core_delta->c6 + core_delta->c7) > (old->tsc * tsc_tweak))
			old->c1 = 0;
		अन्यथा अणु
			/* normal हाल, derive c1 */
			old->c1 = (old->tsc * tsc_tweak) - old->mperf - core_delta->c3
			    - core_delta->c6 - core_delta->c7;
		पूर्ण
	पूर्ण

	अगर (old->mperf == 0) अणु
		अगर (debug > 1)
			ख_लिखो(outf, "cpu%d MPERF 0!\n", old->cpu_id);
		old->mperf = 1;	/* भागide by 0 protection */
	पूर्ण

	अगर (DO_BIC(BIC_IPC))
		old->instr_count = new->instr_count - old->instr_count;

	अगर (DO_BIC(BIC_IRQ))
		old->irq_count = new->irq_count - old->irq_count;

	अगर (DO_BIC(BIC_SMI))
		old->smi_count = new->smi_count - old->smi_count;

	क्रम (i = 0, mp = sys.tp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			old->counter[i] = new->counter[i];
		अन्यथा
			old->counter[i] = new->counter[i] - old->counter[i];
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक delta_cpu(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c,
	      काष्ठा pkg_data *p, काष्ठा thपढ़ो_data *t2, काष्ठा core_data *c2, काष्ठा pkg_data *p2)
अणु
	पूर्णांक retval = 0;

	/* calculate core delta only क्रम 1st thपढ़ो in core */
	अगर (t->flags & CPU_IS_FIRST_THREAD_IN_CORE)
		delta_core(c, c2);

	/* always calculate thपढ़ो delta */
	retval = delta_thपढ़ो(t, t2, c2);	/* c2 is core delta */
	अगर (retval)
		वापस retval;

	/* calculate package delta only क्रम 1st core in package */
	अगर (t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE)
		retval = delta_package(p, p2);

	वापस retval;
पूर्ण

व्योम clear_counters(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	पूर्णांक i;
	काष्ठा msr_counter *mp;

	t->tv_begin.tv_sec = 0;
	t->tv_begin.tv_usec = 0;
	t->tv_end.tv_sec = 0;
	t->tv_end.tv_usec = 0;
	t->tv_delta.tv_sec = 0;
	t->tv_delta.tv_usec = 0;

	t->tsc = 0;
	t->aperf = 0;
	t->mperf = 0;
	t->c1 = 0;

	t->instr_count = 0;

	t->irq_count = 0;
	t->smi_count = 0;

	/* tells क्रमmat_counters to dump all fields from this set */
	t->flags = CPU_IS_FIRST_THREAD_IN_CORE | CPU_IS_FIRST_CORE_IN_PACKAGE;

	c->c3 = 0;
	c->c6 = 0;
	c->c7 = 0;
	c->mc6_us = 0;
	c->core_temp_c = 0;
	c->core_energy = 0;

	p->pkg_wtd_core_c0 = 0;
	p->pkg_any_core_c0 = 0;
	p->pkg_any_gfxe_c0 = 0;
	p->pkg_both_core_gfxe_c0 = 0;

	p->pc2 = 0;
	अगर (DO_BIC(BIC_Pkgpc3))
		p->pc3 = 0;
	अगर (DO_BIC(BIC_Pkgpc6))
		p->pc6 = 0;
	अगर (DO_BIC(BIC_Pkgpc7))
		p->pc7 = 0;
	p->pc8 = 0;
	p->pc9 = 0;
	p->pc10 = 0;
	p->cpu_lpi = 0;
	p->sys_lpi = 0;

	p->energy_pkg = 0;
	p->energy_dram = 0;
	p->energy_cores = 0;
	p->energy_gfx = 0;
	p->rapl_pkg_perf_status = 0;
	p->rapl_dram_perf_status = 0;
	p->pkg_temp_c = 0;

	p->gfx_rc6_ms = 0;
	p->gfx_mhz = 0;
	p->gfx_act_mhz = 0;
	क्रम (i = 0, mp = sys.tp; mp; i++, mp = mp->next)
		t->counter[i] = 0;

	क्रम (i = 0, mp = sys.cp; mp; i++, mp = mp->next)
		c->counter[i] = 0;

	क्रम (i = 0, mp = sys.pp; mp; i++, mp = mp->next)
		p->counter[i] = 0;
पूर्ण

पूर्णांक sum_counters(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	पूर्णांक i;
	काष्ठा msr_counter *mp;

	/* copy un-changing apic_id's */
	अगर (DO_BIC(BIC_APIC))
		average.thपढ़ोs.apic_id = t->apic_id;
	अगर (DO_BIC(BIC_X2APIC))
		average.thपढ़ोs.x2apic_id = t->x2apic_id;

	/* remember first tv_begin */
	अगर (average.thपढ़ोs.tv_begin.tv_sec == 0)
		average.thपढ़ोs.tv_begin = t->tv_begin;

	/* remember last tv_end */
	average.thपढ़ोs.tv_end = t->tv_end;

	average.thपढ़ोs.tsc += t->tsc;
	average.thपढ़ोs.aperf += t->aperf;
	average.thपढ़ोs.mperf += t->mperf;
	average.thपढ़ोs.c1 += t->c1;

	average.thपढ़ोs.instr_count += t->instr_count;

	average.thपढ़ोs.irq_count += t->irq_count;
	average.thपढ़ोs.smi_count += t->smi_count;

	क्रम (i = 0, mp = sys.tp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			जारी;
		average.thपढ़ोs.counter[i] += t->counter[i];
	पूर्ण

	/* sum per-core values only क्रम 1st thपढ़ो in core */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE))
		वापस 0;

	average.cores.c3 += c->c3;
	average.cores.c6 += c->c6;
	average.cores.c7 += c->c7;
	average.cores.mc6_us += c->mc6_us;

	average.cores.core_temp_c = MAX(average.cores.core_temp_c, c->core_temp_c);

	average.cores.core_energy += c->core_energy;

	क्रम (i = 0, mp = sys.cp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			जारी;
		average.cores.counter[i] += c->counter[i];
	पूर्ण

	/* sum per-pkg values only क्रम 1st core in pkg */
	अगर (!(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		वापस 0;

	अगर (DO_BIC(BIC_Totl_c0))
		average.packages.pkg_wtd_core_c0 += p->pkg_wtd_core_c0;
	अगर (DO_BIC(BIC_Any_c0))
		average.packages.pkg_any_core_c0 += p->pkg_any_core_c0;
	अगर (DO_BIC(BIC_GFX_c0))
		average.packages.pkg_any_gfxe_c0 += p->pkg_any_gfxe_c0;
	अगर (DO_BIC(BIC_CPUGFX))
		average.packages.pkg_both_core_gfxe_c0 += p->pkg_both_core_gfxe_c0;

	average.packages.pc2 += p->pc2;
	अगर (DO_BIC(BIC_Pkgpc3))
		average.packages.pc3 += p->pc3;
	अगर (DO_BIC(BIC_Pkgpc6))
		average.packages.pc6 += p->pc6;
	अगर (DO_BIC(BIC_Pkgpc7))
		average.packages.pc7 += p->pc7;
	average.packages.pc8 += p->pc8;
	average.packages.pc9 += p->pc9;
	average.packages.pc10 += p->pc10;

	average.packages.cpu_lpi = p->cpu_lpi;
	average.packages.sys_lpi = p->sys_lpi;

	average.packages.energy_pkg += p->energy_pkg;
	average.packages.energy_dram += p->energy_dram;
	average.packages.energy_cores += p->energy_cores;
	average.packages.energy_gfx += p->energy_gfx;

	average.packages.gfx_rc6_ms = p->gfx_rc6_ms;
	average.packages.gfx_mhz = p->gfx_mhz;
	average.packages.gfx_act_mhz = p->gfx_act_mhz;

	average.packages.pkg_temp_c = MAX(average.packages.pkg_temp_c, p->pkg_temp_c);

	average.packages.rapl_pkg_perf_status += p->rapl_pkg_perf_status;
	average.packages.rapl_dram_perf_status += p->rapl_dram_perf_status;

	क्रम (i = 0, mp = sys.pp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			जारी;
		average.packages.counter[i] += p->counter[i];
	पूर्ण
	वापस 0;
पूर्ण

/*
 * sum the counters क्रम all cpus in the प्रणाली
 * compute the weighted average
 */
व्योम compute_average(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	पूर्णांक i;
	काष्ठा msr_counter *mp;

	clear_counters(&average.thपढ़ोs, &average.cores, &average.packages);

	क्रम_all_cpus(sum_counters, t, c, p);

	/* Use the global समय delta क्रम the average. */
	average.thपढ़ोs.tv_delta = tv_delta;

	average.thपढ़ोs.tsc /= topo.num_cpus;
	average.thपढ़ोs.aperf /= topo.num_cpus;
	average.thपढ़ोs.mperf /= topo.num_cpus;
	average.thपढ़ोs.instr_count /= topo.num_cpus;
	average.thपढ़ोs.c1 /= topo.num_cpus;

	अगर (average.thपढ़ोs.irq_count > 9999999)
		sums_need_wide_columns = 1;

	average.cores.c3 /= topo.num_cores;
	average.cores.c6 /= topo.num_cores;
	average.cores.c7 /= topo.num_cores;
	average.cores.mc6_us /= topo.num_cores;

	अगर (DO_BIC(BIC_Totl_c0))
		average.packages.pkg_wtd_core_c0 /= topo.num_packages;
	अगर (DO_BIC(BIC_Any_c0))
		average.packages.pkg_any_core_c0 /= topo.num_packages;
	अगर (DO_BIC(BIC_GFX_c0))
		average.packages.pkg_any_gfxe_c0 /= topo.num_packages;
	अगर (DO_BIC(BIC_CPUGFX))
		average.packages.pkg_both_core_gfxe_c0 /= topo.num_packages;

	average.packages.pc2 /= topo.num_packages;
	अगर (DO_BIC(BIC_Pkgpc3))
		average.packages.pc3 /= topo.num_packages;
	अगर (DO_BIC(BIC_Pkgpc6))
		average.packages.pc6 /= topo.num_packages;
	अगर (DO_BIC(BIC_Pkgpc7))
		average.packages.pc7 /= topo.num_packages;

	average.packages.pc8 /= topo.num_packages;
	average.packages.pc9 /= topo.num_packages;
	average.packages.pc10 /= topo.num_packages;

	क्रम (i = 0, mp = sys.tp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			जारी;
		अगर (mp->type == COUNTER_ITEMS) अणु
			अगर (average.thपढ़ोs.counter[i] > 9999999)
				sums_need_wide_columns = 1;
			जारी;
		पूर्ण
		average.thपढ़ोs.counter[i] /= topo.num_cpus;
	पूर्ण
	क्रम (i = 0, mp = sys.cp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			जारी;
		अगर (mp->type == COUNTER_ITEMS) अणु
			अगर (average.cores.counter[i] > 9999999)
				sums_need_wide_columns = 1;
		पूर्ण
		average.cores.counter[i] /= topo.num_cores;
	पूर्ण
	क्रम (i = 0, mp = sys.pp; mp; i++, mp = mp->next) अणु
		अगर (mp->क्रमmat == FORMAT_RAW)
			जारी;
		अगर (mp->type == COUNTER_ITEMS) अणु
			अगर (average.packages.counter[i] > 9999999)
				sums_need_wide_columns = 1;
		पूर्ण
		average.packages.counter[i] /= topo.num_packages;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ rdtsc(व्योम)
अणु
	अचिन्हित पूर्णांक low, high;

	यंत्र अस्थिर ("rdtsc":"=a" (low), "=d"(high));

	वापस low | ((अचिन्हित दीर्घ दीर्घ)high) << 32;
पूर्ण

/*
 * Open a file, and निकास on failure
 */
खाता *ख_खोलो_or_die(स्थिर अक्षर *path, स्थिर अक्षर *mode)
अणु
	खाता *filep = ख_खोलो(path, mode);

	अगर (!filep)
		err(1, "%s: open failed", path);
	वापस filep;
पूर्ण

/*
 * snapshot_sysfs_counter()
 *
 * वापस snapshot of given counter
 */
अचिन्हित दीर्घ दीर्घ snapshot_sysfs_counter(अक्षर *path)
अणु
	खाता *fp;
	पूर्णांक retval;
	अचिन्हित दीर्घ दीर्घ counter;

	fp = ख_खोलो_or_die(path, "r");

	retval = ख_पूछो(fp, "%lld", &counter);
	अगर (retval != 1)
		err(1, "snapshot_sysfs_counter(%s)", path);

	ख_बंद(fp);

	वापस counter;
पूर्ण

पूर्णांक get_mp(पूर्णांक cpu, काष्ठा msr_counter *mp, अचिन्हित दीर्घ दीर्घ *counterp)
अणु
	अगर (mp->msr_num != 0) अणु
		अगर (get_msr(cpu, mp->msr_num, counterp))
			वापस -1;
	पूर्ण अन्यथा अणु
		अक्षर path[128 + PATH_BYTES];

		अगर (mp->flags & SYSFS_PERCPU) अणु
			प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/%s", cpu, mp->path);

			*counterp = snapshot_sysfs_counter(path);
		पूर्ण अन्यथा अणु
			*counterp = snapshot_sysfs_counter(mp->path);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक get_epb(पूर्णांक cpu)
अणु
	अक्षर path[128 + PATH_BYTES];
	अचिन्हित दीर्घ दीर्घ msr;
	पूर्णांक ret, epb = -1;
	खाता *fp;

	प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/power/energy_perf_bias", cpu);

	fp = ख_खोलो(path, "r");
	अगर (!fp)
		जाओ msr_fallback;

	ret = ख_पूछो(fp, "%d", &epb);
	अगर (ret != 1)
		err(1, "%s(%s)", __func__, path);

	ख_बंद(fp);

	वापस epb;

msr_fallback:
	get_msr(cpu, MSR_IA32_ENERGY_PERF_BIAS, &msr);

	वापस msr & 0xf;
पूर्ण

व्योम get_apic_id(काष्ठा thपढ़ो_data *t)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	अगर (DO_BIC(BIC_APIC)) अणु
		eax = ebx = ecx = edx = 0;
		__cpuid(1, eax, ebx, ecx, edx);

		t->apic_id = (ebx >> 24) & 0xff;
	पूर्ण

	अगर (!DO_BIC(BIC_X2APIC))
		वापस;

	अगर (authentic_amd || hygon_genuine) अणु
		अचिन्हित पूर्णांक topology_extensions;

		अगर (max_extended_level < 0x8000001e)
			वापस;

		eax = ebx = ecx = edx = 0;
		__cpuid(0x80000001, eax, ebx, ecx, edx);
		topology_extensions = ecx & (1 << 22);

		अगर (topology_extensions == 0)
			वापस;

		eax = ebx = ecx = edx = 0;
		__cpuid(0x8000001e, eax, ebx, ecx, edx);

		t->x2apic_id = eax;
		वापस;
	पूर्ण

	अगर (!genuine_पूर्णांकel)
		वापस;

	अगर (max_level < 0xb)
		वापस;

	ecx = 0;
	__cpuid(0xb, eax, ebx, ecx, edx);
	t->x2apic_id = edx;

	अगर (debug && (t->apic_id != (t->x2apic_id & 0xff)))
		ख_लिखो(outf, "cpu%d: BIOS BUG: apic 0x%x x2apic 0x%x\n", t->cpu_id, t->apic_id, t->x2apic_id);
पूर्ण

/*
 * get_counters(...)
 * migrate to cpu
 * acquire and record local counters क्रम that cpu
 */
पूर्णांक get_counters(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	पूर्णांक cpu = t->cpu_id;
	अचिन्हित दीर्घ दीर्घ msr;
	पूर्णांक aperf_mperf_retry_count = 0;
	काष्ठा msr_counter *mp;
	पूर्णांक i;

	अगर (cpu_migrate(cpu)) अणु
		ख_लिखो(outf, "get_counters: Could not migrate to CPU %d\n", cpu);
		वापस -1;
	पूर्ण

	समय_लोofday(&t->tv_begin, (काष्ठा समयzone *)शून्य);

	अगर (first_counter_पढ़ो)
		get_apic_id(t);
retry:
	t->tsc = rdtsc();	/* we are running on local CPU of पूर्णांकerest */

	अगर (DO_BIC(BIC_Avg_MHz) || DO_BIC(BIC_Busy) || DO_BIC(BIC_Bzy_MHz) || soft_c1_residency_display(BIC_Avg_MHz)) अणु
		अचिन्हित दीर्घ दीर्घ tsc_beक्रमe, tsc_between, tsc_after, aperf_समय, mperf_समय;

		/*
		 * The TSC, APERF and MPERF must be पढ़ो together क्रम
		 * APERF/MPERF and MPERF/TSC to give accurate results.
		 *
		 * Unक्रमtunately, APERF and MPERF are पढ़ो by
		 * inभागidual प्रणाली call, so delays may occur
		 * between them.  If the समय to पढ़ो them
		 * varies by a large amount, we re-पढ़ो them.
		 */

		/*
		 * This initial dummy APERF पढ़ो has been seen to
		 * reduce jitter in the subsequent पढ़ोs.
		 */

		अगर (get_msr(cpu, MSR_IA32_APERF, &t->aperf))
			वापस -3;

		t->tsc = rdtsc();	/* re-पढ़ो बंद to APERF */

		tsc_beक्रमe = t->tsc;

		अगर (get_msr(cpu, MSR_IA32_APERF, &t->aperf))
			वापस -3;

		tsc_between = rdtsc();

		अगर (get_msr(cpu, MSR_IA32_MPERF, &t->mperf))
			वापस -4;

		tsc_after = rdtsc();

		aperf_समय = tsc_between - tsc_beक्रमe;
		mperf_समय = tsc_after - tsc_between;

		/*
		 * If the प्रणाली call latency to पढ़ो APERF and MPERF
		 * dअगरfer by more than 2x, then try again.
		 */
		अगर ((aperf_समय > (2 * mperf_समय)) || (mperf_समय > (2 * aperf_समय))) अणु
			aperf_mperf_retry_count++;
			अगर (aperf_mperf_retry_count < 5)
				जाओ retry;
			अन्यथा
				warnx("cpu%d jitter %lld %lld", cpu, aperf_समय, mperf_समय);
		पूर्ण
		aperf_mperf_retry_count = 0;

		t->aperf = t->aperf * aperf_mperf_multiplier;
		t->mperf = t->mperf * aperf_mperf_multiplier;
	पूर्ण

	अगर (DO_BIC(BIC_IPC))
		अगर (पढ़ो(get_instr_count_fd(cpu), &t->instr_count, माप(दीर्घ दीर्घ)) != माप(दीर्घ दीर्घ))
			वापस -4;

	अगर (DO_BIC(BIC_IRQ))
		t->irq_count = irqs_per_cpu[cpu];
	अगर (DO_BIC(BIC_SMI)) अणु
		अगर (get_msr(cpu, MSR_SMI_COUNT, &msr))
			वापस -5;
		t->smi_count = msr & 0xFFFFFFFF;
	पूर्ण
	अगर (DO_BIC(BIC_CPU_c1) && use_c1_residency_msr) अणु
		अगर (get_msr(cpu, MSR_CORE_C1_RES, &t->c1))
			वापस -6;
	पूर्ण

	क्रम (i = 0, mp = sys.tp; mp; i++, mp = mp->next) अणु
		अगर (get_mp(cpu, mp, &t->counter[i]))
			वापस -10;
	पूर्ण

	/* collect core counters only क्रम 1st thपढ़ो in core */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE))
		जाओ करोne;

	अगर (DO_BIC(BIC_CPU_c3) || soft_c1_residency_display(BIC_CPU_c3)) अणु
		अगर (get_msr(cpu, MSR_CORE_C3_RESIDENCY, &c->c3))
			वापस -6;
	पूर्ण

	अगर ((DO_BIC(BIC_CPU_c6) || soft_c1_residency_display(BIC_CPU_c6)) && !करो_knl_cstates) अणु
		अगर (get_msr(cpu, MSR_CORE_C6_RESIDENCY, &c->c6))
			वापस -7;
	पूर्ण अन्यथा अगर (करो_knl_cstates || soft_c1_residency_display(BIC_CPU_c6)) अणु
		अगर (get_msr(cpu, MSR_KNL_CORE_C6_RESIDENCY, &c->c6))
			वापस -7;
	पूर्ण

	अगर (DO_BIC(BIC_CPU_c7) || soft_c1_residency_display(BIC_CPU_c7)) अणु
		अगर (get_msr(cpu, MSR_CORE_C7_RESIDENCY, &c->c7))
			वापस -8;
		अन्यथा अगर (t->is_atom) अणु
			/*
			 * For Atom CPUs that has core cstate deeper than c6,
			 * MSR_CORE_C6_RESIDENCY वापसs residency of cc6 and deeper.
			 * Minus CC7 (and deeper cstates) residency to get
			 * accturate cc6 residency.
			 */
			c->c6 -= c->c7;
		पूर्ण
	पूर्ण

	अगर (DO_BIC(BIC_Mod_c6))
		अगर (get_msr(cpu, MSR_MODULE_C6_RES_MS, &c->mc6_us))
			वापस -8;

	अगर (DO_BIC(BIC_CoreTmp)) अणु
		अगर (get_msr(cpu, MSR_IA32_THERM_STATUS, &msr))
			वापस -9;
		c->core_temp_c = tj_max - ((msr >> 16) & 0x7F);
	पूर्ण

	अगर (करो_rapl & RAPL_AMD_F17H) अणु
		अगर (get_msr(cpu, MSR_CORE_ENERGY_STAT, &msr))
			वापस -14;
		c->core_energy = msr & 0xFFFFFFFF;
	पूर्ण

	क्रम (i = 0, mp = sys.cp; mp; i++, mp = mp->next) अणु
		अगर (get_mp(cpu, mp, &c->counter[i]))
			वापस -10;
	पूर्ण

	/* collect package counters only क्रम 1st core in package */
	अगर (!(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		जाओ करोne;

	अगर (DO_BIC(BIC_Totl_c0)) अणु
		अगर (get_msr(cpu, MSR_PKG_WEIGHTED_CORE_C0_RES, &p->pkg_wtd_core_c0))
			वापस -10;
	पूर्ण
	अगर (DO_BIC(BIC_Any_c0)) अणु
		अगर (get_msr(cpu, MSR_PKG_ANY_CORE_C0_RES, &p->pkg_any_core_c0))
			वापस -11;
	पूर्ण
	अगर (DO_BIC(BIC_GFX_c0)) अणु
		अगर (get_msr(cpu, MSR_PKG_ANY_GFXE_C0_RES, &p->pkg_any_gfxe_c0))
			वापस -12;
	पूर्ण
	अगर (DO_BIC(BIC_CPUGFX)) अणु
		अगर (get_msr(cpu, MSR_PKG_BOTH_CORE_GFXE_C0_RES, &p->pkg_both_core_gfxe_c0))
			वापस -13;
	पूर्ण
	अगर (DO_BIC(BIC_Pkgpc3))
		अगर (get_msr(cpu, MSR_PKG_C3_RESIDENCY, &p->pc3))
			वापस -9;
	अगर (DO_BIC(BIC_Pkgpc6)) अणु
		अगर (करो_slm_cstates) अणु
			अगर (get_msr(cpu, MSR_ATOM_PKG_C6_RESIDENCY, &p->pc6))
				वापस -10;
		पूर्ण अन्यथा अणु
			अगर (get_msr(cpu, MSR_PKG_C6_RESIDENCY, &p->pc6))
				वापस -10;
		पूर्ण
	पूर्ण

	अगर (DO_BIC(BIC_Pkgpc2))
		अगर (get_msr(cpu, MSR_PKG_C2_RESIDENCY, &p->pc2))
			वापस -11;
	अगर (DO_BIC(BIC_Pkgpc7))
		अगर (get_msr(cpu, MSR_PKG_C7_RESIDENCY, &p->pc7))
			वापस -12;
	अगर (DO_BIC(BIC_Pkgpc8))
		अगर (get_msr(cpu, MSR_PKG_C8_RESIDENCY, &p->pc8))
			वापस -13;
	अगर (DO_BIC(BIC_Pkgpc9))
		अगर (get_msr(cpu, MSR_PKG_C9_RESIDENCY, &p->pc9))
			वापस -13;
	अगर (DO_BIC(BIC_Pkgpc10))
		अगर (get_msr(cpu, MSR_PKG_C10_RESIDENCY, &p->pc10))
			वापस -13;

	अगर (DO_BIC(BIC_CPU_LPI))
		p->cpu_lpi = cpuidle_cur_cpu_lpi_us;
	अगर (DO_BIC(BIC_SYS_LPI))
		p->sys_lpi = cpuidle_cur_sys_lpi_us;

	अगर (करो_rapl & RAPL_PKG) अणु
		अगर (get_msr_sum(cpu, MSR_PKG_ENERGY_STATUS, &msr))
			वापस -13;
		p->energy_pkg = msr;
	पूर्ण
	अगर (करो_rapl & RAPL_CORES_ENERGY_STATUS) अणु
		अगर (get_msr_sum(cpu, MSR_PP0_ENERGY_STATUS, &msr))
			वापस -14;
		p->energy_cores = msr;
	पूर्ण
	अगर (करो_rapl & RAPL_DRAM) अणु
		अगर (get_msr_sum(cpu, MSR_DRAM_ENERGY_STATUS, &msr))
			वापस -15;
		p->energy_dram = msr;
	पूर्ण
	अगर (करो_rapl & RAPL_GFX) अणु
		अगर (get_msr_sum(cpu, MSR_PP1_ENERGY_STATUS, &msr))
			वापस -16;
		p->energy_gfx = msr;
	पूर्ण
	अगर (करो_rapl & RAPL_PKG_PERF_STATUS) अणु
		अगर (get_msr_sum(cpu, MSR_PKG_PERF_STATUS, &msr))
			वापस -16;
		p->rapl_pkg_perf_status = msr;
	पूर्ण
	अगर (करो_rapl & RAPL_DRAM_PERF_STATUS) अणु
		अगर (get_msr_sum(cpu, MSR_DRAM_PERF_STATUS, &msr))
			वापस -16;
		p->rapl_dram_perf_status = msr;
	पूर्ण
	अगर (करो_rapl & RAPL_AMD_F17H) अणु
		अगर (get_msr_sum(cpu, MSR_PKG_ENERGY_STAT, &msr))
			वापस -13;
		p->energy_pkg = msr;
	पूर्ण
	अगर (DO_BIC(BIC_PkgTmp)) अणु
		अगर (get_msr(cpu, MSR_IA32_PACKAGE_THERM_STATUS, &msr))
			वापस -17;
		p->pkg_temp_c = tj_max - ((msr >> 16) & 0x7F);
	पूर्ण

	अगर (DO_BIC(BIC_GFX_rc6))
		p->gfx_rc6_ms = gfx_cur_rc6_ms;

	अगर (DO_BIC(BIC_GFXMHz))
		p->gfx_mhz = gfx_cur_mhz;

	अगर (DO_BIC(BIC_GFXACTMHz))
		p->gfx_act_mhz = gfx_act_mhz;

	क्रम (i = 0, mp = sys.pp; mp; i++, mp = mp->next) अणु
		अगर (get_mp(cpu, mp, &p->counter[i]))
			वापस -10;
	पूर्ण
करोne:
	समय_लोofday(&t->tv_end, (काष्ठा समयzone *)शून्य);

	वापस 0;
पूर्ण

/*
 * MSR_PKG_CST_CONFIG_CONTROL decoding क्रम pkg_cstate_limit:
 * If you change the values, note they are used both in comparisons
 * (>= PCL__7) and to index pkg_cstate_limit_strings[].
 */

#घोषणा PCLUKN 0		/* Unknown */
#घोषणा PCLRSV 1		/* Reserved */
#घोषणा PCL__0 2		/* PC0 */
#घोषणा PCL__1 3		/* PC1 */
#घोषणा PCL__2 4		/* PC2 */
#घोषणा PCL__3 5		/* PC3 */
#घोषणा PCL__4 6		/* PC4 */
#घोषणा PCL__6 7		/* PC6 */
#घोषणा PCL_6N 8		/* PC6 No Retention */
#घोषणा PCL_6R 9		/* PC6 Retention */
#घोषणा PCL__7 10		/* PC7 */
#घोषणा PCL_7S 11		/* PC7 Shrink */
#घोषणा PCL__8 12		/* PC8 */
#घोषणा PCL__9 13		/* PC9 */
#घोषणा PCL_10 14		/* PC10 */
#घोषणा PCLUNL 15		/* Unlimited */

पूर्णांक pkg_cstate_limit = PCLUKN;
अक्षर *pkg_cstate_limit_strings[] = अणु "reserved", "unknown", "pc0", "pc1", "pc2",
	"pc3", "pc4", "pc6", "pc6n", "pc6r", "pc7", "pc7s", "pc8", "pc9", "pc10", "unlimited"
पूर्ण;

पूर्णांक nhm_pkg_cstate_limits[16] =
    अणु PCL__0, PCL__1, PCL__3, PCL__6, PCL__7, PCLRSV, PCLRSV, PCLUNL, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCLRSV, PCLRSV
पूर्ण;

पूर्णांक snb_pkg_cstate_limits[16] =
    अणु PCL__0, PCL__2, PCL_6N, PCL_6R, PCL__7, PCL_7S, PCLRSV, PCLUNL, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCLRSV, PCLRSV
पूर्ण;

पूर्णांक hsw_pkg_cstate_limits[16] =
    अणु PCL__0, PCL__2, PCL__3, PCL__6, PCL__7, PCL_7S, PCL__8, PCL__9, PCLUNL, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCLRSV, PCLRSV
पूर्ण;

पूर्णांक slv_pkg_cstate_limits[16] =
    अणु PCL__0, PCL__1, PCLRSV, PCLRSV, PCL__4, PCLRSV, PCL__6, PCL__7, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCL__6, PCL__7
पूर्ण;

पूर्णांक amt_pkg_cstate_limits[16] =
    अणु PCLUNL, PCL__1, PCL__2, PCLRSV, PCLRSV, PCLRSV, PCL__6, PCL__7, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCLRSV, PCLRSV
पूर्ण;

पूर्णांक phi_pkg_cstate_limits[16] =
    अणु PCL__0, PCL__2, PCL_6N, PCL_6R, PCLRSV, PCLRSV, PCLRSV, PCLUNL, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCLRSV, PCLRSV
पूर्ण;

पूर्णांक glm_pkg_cstate_limits[16] =
    अणु PCLUNL, PCL__1, PCL__3, PCL__6, PCL__7, PCL_7S, PCL__8, PCL__9, PCL_10, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCLRSV, PCLRSV
पूर्ण;

पूर्णांक skx_pkg_cstate_limits[16] =
    अणु PCL__0, PCL__2, PCL_6N, PCL_6R, PCLRSV, PCLRSV, PCLRSV, PCLUNL, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCLRSV, PCLRSV
पूर्ण;

पूर्णांक icx_pkg_cstate_limits[16] =
    अणु PCL__0, PCL__2, PCL__6, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLUNL, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV, PCLRSV,
	PCLRSV, PCLRSV
पूर्ण;

अटल व्योम calculate_tsc_tweak()
अणु
	tsc_tweak = base_hz / tsc_hz;
पूर्ण

व्योम prewake_cstate_probe(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model);

अटल व्योम dump_nhm_platक्रमm_info(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक ratio;

	get_msr(base_cpu, MSR_PLATFORM_INFO, &msr);

	ख_लिखो(outf, "cpu%d: MSR_PLATFORM_INFO: 0x%08llx\n", base_cpu, msr);

	ratio = (msr >> 40) & 0xFF;
	ख_लिखो(outf, "%d * %.1f = %.1f MHz max efficiency frequency\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 8) & 0xFF;
	ख_लिखो(outf, "%d * %.1f = %.1f MHz base frequency\n", ratio, bclk, ratio * bclk);

	get_msr(base_cpu, MSR_IA32_POWER_CTL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_IA32_POWER_CTL: 0x%08llx (C1E auto-promotion: %sabled)\n",
		base_cpu, msr, msr & 0x2 ? "EN" : "DIS");

	/* C-state Pre-wake Disable (CSTATE_PREWAKE_DISABLE) */
	अगर (dis_cstate_prewake)
		ख_लिखो(outf, "C-state Pre-wake: %sabled\n", msr & 0x40000000 ? "DIS" : "EN");

	वापस;
पूर्ण

अटल व्योम dump_hsw_turbo_ratio_limits(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक ratio;

	get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT2, &msr);

	ख_लिखो(outf, "cpu%d: MSR_TURBO_RATIO_LIMIT2: 0x%08llx\n", base_cpu, msr);

	ratio = (msr >> 8) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 18 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 0) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 17 active cores\n", ratio, bclk, ratio * bclk);
	वापस;
पूर्ण

अटल व्योम dump_ivt_turbo_ratio_limits(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक ratio;

	get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT1, &msr);

	ख_लिखो(outf, "cpu%d: MSR_TURBO_RATIO_LIMIT1: 0x%08llx\n", base_cpu, msr);

	ratio = (msr >> 56) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 16 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 48) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 15 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 40) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 14 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 32) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 13 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 24) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 12 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 16) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 11 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 8) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 10 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 0) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 9 active cores\n", ratio, bclk, ratio * bclk);
	वापस;
पूर्ण

पूर्णांक has_turbo_ratio_group_limits(पूर्णांक family, पूर्णांक model)
अणु

	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_GOLDMONT:
	हाल INTEL_FAM6_SKYLAKE_X:
	हाल INTEL_FAM6_ICELAKE_X:
	हाल INTEL_FAM6_ATOM_GOLDMONT_D:
	हाल INTEL_FAM6_ATOM_TREMONT_D:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dump_turbo_ratio_limits(पूर्णांक family, पूर्णांक model)
अणु
	अचिन्हित दीर्घ दीर्घ msr, core_counts;
	अचिन्हित पूर्णांक ratio, group_size;

	get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT, &msr);
	ख_लिखो(outf, "cpu%d: MSR_TURBO_RATIO_LIMIT: 0x%08llx\n", base_cpu, msr);

	अगर (has_turbo_ratio_group_limits(family, model)) अणु
		get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT1, &core_counts);
		ख_लिखो(outf, "cpu%d: MSR_TURBO_RATIO_LIMIT1: 0x%08llx\n", base_cpu, core_counts);
	पूर्ण अन्यथा अणु
		core_counts = 0x0807060504030201;
	पूर्ण

	ratio = (msr >> 56) & 0xFF;
	group_size = (core_counts >> 56) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 48) & 0xFF;
	group_size = (core_counts >> 48) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 40) & 0xFF;
	group_size = (core_counts >> 40) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 32) & 0xFF;
	group_size = (core_counts >> 32) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 24) & 0xFF;
	group_size = (core_counts >> 24) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 16) & 0xFF;
	group_size = (core_counts >> 16) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 8) & 0xFF;
	group_size = (core_counts >> 8) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 0) & 0xFF;
	group_size = (core_counts >> 0) & 0xFF;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);
	वापस;
पूर्ण

अटल व्योम dump_atom_turbo_ratio_limits(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक ratio;

	get_msr(base_cpu, MSR_ATOM_CORE_RATIOS, &msr);
	ख_लिखो(outf, "cpu%d: MSR_ATOM_CORE_RATIOS: 0x%08llx\n", base_cpu, msr & 0xFFFFFFFF);

	ratio = (msr >> 0) & 0x3F;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz minimum operating frequency\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 8) & 0x3F;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz low frequency mode (LFM)\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 16) & 0x3F;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz base frequency\n", ratio, bclk, ratio * bclk);

	get_msr(base_cpu, MSR_ATOM_CORE_TURBO_RATIOS, &msr);
	ख_लिखो(outf, "cpu%d: MSR_ATOM_CORE_TURBO_RATIOS: 0x%08llx\n", base_cpu, msr & 0xFFFFFFFF);

	ratio = (msr >> 24) & 0x3F;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 4 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 16) & 0x3F;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 3 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 8) & 0x3F;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 2 active cores\n", ratio, bclk, ratio * bclk);

	ratio = (msr >> 0) & 0x3F;
	अगर (ratio)
		ख_लिखो(outf, "%d * %.1f = %.1f MHz max turbo 1 active core\n", ratio, bclk, ratio * bclk);
पूर्ण

अटल व्योम dump_knl_turbo_ratio_limits(व्योम)
अणु
	स्थिर अचिन्हित पूर्णांक buckets_no = 7;

	अचिन्हित दीर्घ दीर्घ msr;
	पूर्णांक delta_cores, delta_ratio;
	पूर्णांक i, b_nr;
	अचिन्हित पूर्णांक cores[buckets_no];
	अचिन्हित पूर्णांक ratio[buckets_no];

	get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT, &msr);

	ख_लिखो(outf, "cpu%d: MSR_TURBO_RATIO_LIMIT: 0x%08llx\n", base_cpu, msr);

	/*
	 * Turbo encoding in KNL is as follows:
	 * [0] -- Reserved
	 * [7:1] -- Base value of number of active cores of bucket 1.
	 * [15:8] -- Base value of freq ratio of bucket 1.
	 * [20:16] -- +ve delta of number of active cores of bucket 2.
	 * i.e. active cores of bucket 2 =
	 * active cores of bucket 1 + delta
	 * [23:21] -- Negative delta of freq ratio of bucket 2.
	 * i.e. freq ratio of bucket 2 =
	 * freq ratio of bucket 1 - delta
	 * [28:24]-- +ve delta of number of active cores of bucket 3.
	 * [31:29]-- -ve delta of freq ratio of bucket 3.
	 * [36:32]-- +ve delta of number of active cores of bucket 4.
	 * [39:37]-- -ve delta of freq ratio of bucket 4.
	 * [44:40]-- +ve delta of number of active cores of bucket 5.
	 * [47:45]-- -ve delta of freq ratio of bucket 5.
	 * [52:48]-- +ve delta of number of active cores of bucket 6.
	 * [55:53]-- -ve delta of freq ratio of bucket 6.
	 * [60:56]-- +ve delta of number of active cores of bucket 7.
	 * [63:61]-- -ve delta of freq ratio of bucket 7.
	 */

	b_nr = 0;
	cores[b_nr] = (msr & 0xFF) >> 1;
	ratio[b_nr] = (msr >> 8) & 0xFF;

	क्रम (i = 16; i < 64; i += 8) अणु
		delta_cores = (msr >> i) & 0x1F;
		delta_ratio = (msr >> (i + 5)) & 0x7;

		cores[b_nr + 1] = cores[b_nr] + delta_cores;
		ratio[b_nr + 1] = ratio[b_nr] - delta_ratio;
		b_nr++;
	पूर्ण

	क्रम (i = buckets_no - 1; i >= 0; i--)
		अगर (i > 0 ? ratio[i] != ratio[i - 1] : 1)
			ख_लिखो(outf,
				"%d * %.1f = %.1f MHz max turbo %d active cores\n",
				ratio[i], bclk, ratio[i] * bclk, cores[i]);
पूर्ण

अटल व्योम dump_nhm_cst_cfg(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	get_msr(base_cpu, MSR_PKG_CST_CONFIG_CONTROL, &msr);

	ख_लिखो(outf, "cpu%d: MSR_PKG_CST_CONFIG_CONTROL: 0x%08llx", base_cpu, msr);

	ख_लिखो(outf, " (%s%s%s%s%slocked, pkg-cstate-limit=%d (%s)",
		(msr & SNB_C3_AUTO_UNDEMOTE) ? "UNdemote-C3, " : "",
		(msr & SNB_C1_AUTO_UNDEMOTE) ? "UNdemote-C1, " : "",
		(msr & NHM_C3_AUTO_DEMOTE) ? "demote-C3, " : "",
		(msr & NHM_C1_AUTO_DEMOTE) ? "demote-C1, " : "",
		(msr & (1 << 15)) ? "" : "UN", (अचिन्हित पूर्णांक)msr & 0xF, pkg_cstate_limit_strings[pkg_cstate_limit]);

#घोषणा AUTOMATIC_CSTATE_CONVERSION		(1UL << 16)
	अगर (has_स्वतःmatic_cstate_conversion) अणु
		ख_लिखो(outf, ", automatic c-state conversion=%s", (msr & AUTOMATIC_CSTATE_CONVERSION) ? "on" : "off");
	पूर्ण

	ख_लिखो(outf, ")\n");

	वापस;
पूर्ण

अटल व्योम dump_config_tdp(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	get_msr(base_cpu, MSR_CONFIG_TDP_NOMINAL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_CONFIG_TDP_NOMINAL: 0x%08llx", base_cpu, msr);
	ख_लिखो(outf, " (base_ratio=%d)\n", (अचिन्हित पूर्णांक)msr & 0xFF);

	get_msr(base_cpu, MSR_CONFIG_TDP_LEVEL_1, &msr);
	ख_लिखो(outf, "cpu%d: MSR_CONFIG_TDP_LEVEL_1: 0x%08llx (", base_cpu, msr);
	अगर (msr) अणु
		ख_लिखो(outf, "PKG_MIN_PWR_LVL1=%d ", (अचिन्हित पूर्णांक)(msr >> 48) & 0x7FFF);
		ख_लिखो(outf, "PKG_MAX_PWR_LVL1=%d ", (अचिन्हित पूर्णांक)(msr >> 32) & 0x7FFF);
		ख_लिखो(outf, "LVL1_RATIO=%d ", (अचिन्हित पूर्णांक)(msr >> 16) & 0xFF);
		ख_लिखो(outf, "PKG_TDP_LVL1=%d", (अचिन्हित पूर्णांक)(msr) & 0x7FFF);
	पूर्ण
	ख_लिखो(outf, ")\n");

	get_msr(base_cpu, MSR_CONFIG_TDP_LEVEL_2, &msr);
	ख_लिखो(outf, "cpu%d: MSR_CONFIG_TDP_LEVEL_2: 0x%08llx (", base_cpu, msr);
	अगर (msr) अणु
		ख_लिखो(outf, "PKG_MIN_PWR_LVL2=%d ", (अचिन्हित पूर्णांक)(msr >> 48) & 0x7FFF);
		ख_लिखो(outf, "PKG_MAX_PWR_LVL2=%d ", (अचिन्हित पूर्णांक)(msr >> 32) & 0x7FFF);
		ख_लिखो(outf, "LVL2_RATIO=%d ", (अचिन्हित पूर्णांक)(msr >> 16) & 0xFF);
		ख_लिखो(outf, "PKG_TDP_LVL2=%d", (अचिन्हित पूर्णांक)(msr) & 0x7FFF);
	पूर्ण
	ख_लिखो(outf, ")\n");

	get_msr(base_cpu, MSR_CONFIG_TDP_CONTROL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_CONFIG_TDP_CONTROL: 0x%08llx (", base_cpu, msr);
	अगर ((msr) & 0x3)
		ख_लिखो(outf, "TDP_LEVEL=%d ", (अचिन्हित पूर्णांक)(msr) & 0x3);
	ख_लिखो(outf, " lock=%d", (अचिन्हित पूर्णांक)(msr >> 31) & 1);
	ख_लिखो(outf, ")\n");

	get_msr(base_cpu, MSR_TURBO_ACTIVATION_RATIO, &msr);
	ख_लिखो(outf, "cpu%d: MSR_TURBO_ACTIVATION_RATIO: 0x%08llx (", base_cpu, msr);
	ख_लिखो(outf, "MAX_NON_TURBO_RATIO=%d", (अचिन्हित पूर्णांक)(msr) & 0xFF);
	ख_लिखो(outf, " lock=%d", (अचिन्हित पूर्णांक)(msr >> 31) & 1);
	ख_लिखो(outf, ")\n");
पूर्ण

अचिन्हित पूर्णांक irtl_समय_units[] = अणु 1, 32, 1024, 32768, 1048576, 33554432, 0, 0 पूर्ण;

व्योम prपूर्णांक_irtl(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	get_msr(base_cpu, MSR_PKGC3_IRTL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_PKGC3_IRTL: 0x%08llx (", base_cpu, msr);
	ख_लिखो(outf, "%svalid, %lld ns)\n", msr & (1 << 15) ? "" : "NOT",
		(msr & 0x3FF) * irtl_समय_units[(msr >> 10) & 0x3]);

	get_msr(base_cpu, MSR_PKGC6_IRTL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_PKGC6_IRTL: 0x%08llx (", base_cpu, msr);
	ख_लिखो(outf, "%svalid, %lld ns)\n", msr & (1 << 15) ? "" : "NOT",
		(msr & 0x3FF) * irtl_समय_units[(msr >> 10) & 0x3]);

	get_msr(base_cpu, MSR_PKGC7_IRTL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_PKGC7_IRTL: 0x%08llx (", base_cpu, msr);
	ख_लिखो(outf, "%svalid, %lld ns)\n", msr & (1 << 15) ? "" : "NOT",
		(msr & 0x3FF) * irtl_समय_units[(msr >> 10) & 0x3]);

	अगर (!करो_irtl_hsw)
		वापस;

	get_msr(base_cpu, MSR_PKGC8_IRTL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_PKGC8_IRTL: 0x%08llx (", base_cpu, msr);
	ख_लिखो(outf, "%svalid, %lld ns)\n", msr & (1 << 15) ? "" : "NOT",
		(msr & 0x3FF) * irtl_समय_units[(msr >> 10) & 0x3]);

	get_msr(base_cpu, MSR_PKGC9_IRTL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_PKGC9_IRTL: 0x%08llx (", base_cpu, msr);
	ख_लिखो(outf, "%svalid, %lld ns)\n", msr & (1 << 15) ? "" : "NOT",
		(msr & 0x3FF) * irtl_समय_units[(msr >> 10) & 0x3]);

	get_msr(base_cpu, MSR_PKGC10_IRTL, &msr);
	ख_लिखो(outf, "cpu%d: MSR_PKGC10_IRTL: 0x%08llx (", base_cpu, msr);
	ख_लिखो(outf, "%svalid, %lld ns)\n", msr & (1 << 15) ? "" : "NOT",
		(msr & 0x3FF) * irtl_समय_units[(msr >> 10) & 0x3]);

पूर्ण

व्योम मुक्त_fd_percpu(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < topo.max_cpu_num + 1; ++i) अणु
		अगर (fd_percpu[i] != 0)
			बंद(fd_percpu[i]);
	पूर्ण

	मुक्त(fd_percpu);
पूर्ण

व्योम मुक्त_all_buffers(व्योम)
अणु
	पूर्णांक i;

	CPU_FREE(cpu_present_set);
	cpu_present_set = शून्य;
	cpu_present_setsize = 0;

	CPU_FREE(cpu_affinity_set);
	cpu_affinity_set = शून्य;
	cpu_affinity_setsize = 0;

	मुक्त(thपढ़ो_even);
	मुक्त(core_even);
	मुक्त(package_even);

	thपढ़ो_even = शून्य;
	core_even = शून्य;
	package_even = शून्य;

	मुक्त(thपढ़ो_odd);
	मुक्त(core_odd);
	मुक्त(package_odd);

	thपढ़ो_odd = शून्य;
	core_odd = शून्य;
	package_odd = शून्य;

	मुक्त(output_buffer);
	output_buffer = शून्य;
	outp = शून्य;

	मुक्त_fd_percpu();

	मुक्त(irq_column_2_cpu);
	मुक्त(irqs_per_cpu);

	क्रम (i = 0; i <= topo.max_cpu_num; ++i) अणु
		अगर (cpus[i].put_ids)
			CPU_FREE(cpus[i].put_ids);
	पूर्ण
	मुक्त(cpus);
पूर्ण

/*
 * Parse a file containing a single पूर्णांक.
 * Return 0 अगर file can not be खोलोed
 * Exit अगर file can be खोलोed, but can not be parsed
 */
पूर्णांक parse_पूर्णांक_file(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर path[PATH_MAX];
	खाता *filep;
	पूर्णांक value;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(path, माप(path), fmt, args);
	बहु_पूर्ण(args);
	filep = ख_खोलो(path, "r");
	अगर (!filep)
		वापस 0;
	अगर (ख_पूछो(filep, "%d", &value) != 1)
		err(1, "%s: failed to parse number from file", path);
	ख_बंद(filep);
	वापस value;
पूर्ण

/*
 * cpu_is_first_core_in_package(cpu)
 * वापस 1 अगर given CPU is 1st core in package
 */
पूर्णांक cpu_is_first_core_in_package(पूर्णांक cpu)
अणु
	वापस cpu == parse_पूर्णांक_file("/sys/devices/system/cpu/cpu%d/topology/core_siblings_list", cpu);
पूर्ण

पूर्णांक get_physical_package_id(पूर्णांक cpu)
अणु
	वापस parse_पूर्णांक_file("/sys/devices/system/cpu/cpu%d/topology/physical_package_id", cpu);
पूर्ण

पूर्णांक get_die_id(पूर्णांक cpu)
अणु
	वापस parse_पूर्णांक_file("/sys/devices/system/cpu/cpu%d/topology/die_id", cpu);
पूर्ण

पूर्णांक get_core_id(पूर्णांक cpu)
अणु
	वापस parse_पूर्णांक_file("/sys/devices/system/cpu/cpu%d/topology/core_id", cpu);
पूर्ण

व्योम set_node_data(व्योम)
अणु
	पूर्णांक pkg, node, lnode, cpu, cpux;
	पूर्णांक cpu_count;

	/* initialize logical_node_id */
	क्रम (cpu = 0; cpu <= topo.max_cpu_num; ++cpu)
		cpus[cpu].logical_node_id = -1;

	cpu_count = 0;
	क्रम (pkg = 0; pkg < topo.num_packages; pkg++) अणु
		lnode = 0;
		क्रम (cpu = 0; cpu <= topo.max_cpu_num; ++cpu) अणु
			अगर (cpus[cpu].physical_package_id != pkg)
				जारी;
			/* find a cpu with an unset logical_node_id */
			अगर (cpus[cpu].logical_node_id != -1)
				जारी;
			cpus[cpu].logical_node_id = lnode;
			node = cpus[cpu].physical_node_id;
			cpu_count++;
			/*
			 * find all matching cpus on this pkg and set
			 * the logical_node_id
			 */
			क्रम (cpux = cpu; cpux <= topo.max_cpu_num; cpux++) अणु
				अगर ((cpus[cpux].physical_package_id == pkg) && (cpus[cpux].physical_node_id == node)) अणु
					cpus[cpux].logical_node_id = lnode;
					cpu_count++;
				पूर्ण
			पूर्ण
			lnode++;
			अगर (lnode > topo.nodes_per_pkg)
				topo.nodes_per_pkg = lnode;
		पूर्ण
		अगर (cpu_count >= topo.max_cpu_num)
			अवरोध;
	पूर्ण
पूर्ण

पूर्णांक get_physical_node_id(काष्ठा cpu_topology *thiscpu)
अणु
	अक्षर path[80];
	खाता *filep;
	पूर्णांक i;
	पूर्णांक cpu = thiscpu->logical_cpu_id;

	क्रम (i = 0; i <= topo.max_cpu_num; i++) अणु
		प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/node%i/cpulist", cpu, i);
		filep = ख_खोलो(path, "r");
		अगर (!filep)
			जारी;
		ख_बंद(filep);
		वापस i;
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक get_thपढ़ो_siblings(काष्ठा cpu_topology *thiscpu)
अणु
	अक्षर path[80], अक्षरacter;
	खाता *filep;
	अचिन्हित दीर्घ map;
	पूर्णांक so, shअगरt, sib_core;
	पूर्णांक cpu = thiscpu->logical_cpu_id;
	पूर्णांक offset = topo.max_cpu_num + 1;
	माप_प्रकार size;
	पूर्णांक thपढ़ो_id = 0;

	thiscpu->put_ids = CPU_ALLOC((topo.max_cpu_num + 1));
	अगर (thiscpu->thपढ़ो_id < 0)
		thiscpu->thपढ़ो_id = thपढ़ो_id++;
	अगर (!thiscpu->put_ids)
		वापस -1;

	size = CPU_ALLOC_SIZE((topo.max_cpu_num + 1));
	CPU_ZERO_S(size, thiscpu->put_ids);

	प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/topology/thread_siblings", cpu);
	filep = ख_खोलो(path, "r");

	अगर (!filep) अणु
		warnx("%s: open failed", path);
		वापस -1;
	पूर्ण
	करो अणु
		offset -= BITMASK_SIZE;
		अगर (ख_पूछो(filep, "%lx%c", &map, &अक्षरacter) != 2)
			err(1, "%s: failed to parse file", path);
		क्रम (shअगरt = 0; shअगरt < BITMASK_SIZE; shअगरt++) अणु
			अगर ((map >> shअगरt) & 0x1) अणु
				so = shअगरt + offset;
				sib_core = get_core_id(so);
				अगर (sib_core == thiscpu->physical_core_id) अणु
					CPU_SET_S(so, size, thiscpu->put_ids);
					अगर ((so != cpu) && (cpus[so].thपढ़ो_id < 0))
						cpus[so].thपढ़ो_id = thपढ़ो_id++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण जबतक (!म_भेदन(&अक्षरacter, ",", 1));
	ख_बंद(filep);

	वापस CPU_COUNT_S(size, thiscpu->put_ids);
पूर्ण

/*
 * run func(thपढ़ो, core, package) in topology order
 * skip non-present cpus
 */

पूर्णांक क्रम_all_cpus_2(पूर्णांक (func) (काष्ठा thपढ़ो_data *, काष्ठा core_data *,
			       काष्ठा pkg_data *, काष्ठा thपढ़ो_data *, काष्ठा core_data *,
			       काष्ठा pkg_data *), काष्ठा thपढ़ो_data *thपढ़ो_base,
		   काष्ठा core_data *core_base, काष्ठा pkg_data *pkg_base,
		   काष्ठा thपढ़ो_data *thपढ़ो_base2, काष्ठा core_data *core_base2, काष्ठा pkg_data *pkg_base2)
अणु
	पूर्णांक retval, pkg_no, node_no, core_no, thपढ़ो_no;

	क्रम (pkg_no = 0; pkg_no < topo.num_packages; ++pkg_no) अणु
		क्रम (node_no = 0; node_no < topo.nodes_per_pkg; ++node_no) अणु
			क्रम (core_no = 0; core_no < topo.cores_per_node; ++core_no) अणु
				क्रम (thपढ़ो_no = 0; thपढ़ो_no < topo.thपढ़ोs_per_core; ++thपढ़ो_no) अणु
					काष्ठा thपढ़ो_data *t, *t2;
					काष्ठा core_data *c, *c2;
					काष्ठा pkg_data *p, *p2;

					t = GET_THREAD(thपढ़ो_base, thपढ़ो_no, core_no, node_no, pkg_no);

					अगर (cpu_is_not_present(t->cpu_id))
						जारी;

					t2 = GET_THREAD(thपढ़ो_base2, thपढ़ो_no, core_no, node_no, pkg_no);

					c = GET_CORE(core_base, core_no, node_no, pkg_no);
					c2 = GET_CORE(core_base2, core_no, node_no, pkg_no);

					p = GET_PKG(pkg_base, pkg_no);
					p2 = GET_PKG(pkg_base2, pkg_no);

					retval = func(t, c, p, t2, c2, p2);
					अगर (retval)
						वापस retval;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * run func(cpu) on every cpu in /proc/stat
 * वापस max_cpu number
 */
पूर्णांक क्रम_all_proc_cpus(पूर्णांक (func) (पूर्णांक))
अणु
	खाता *fp;
	पूर्णांक cpu_num;
	पूर्णांक retval;

	fp = ख_खोलो_or_die(proc_stat, "r");

	retval = ख_पूछो(fp, "cpu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d\n");
	अगर (retval != 0)
		err(1, "%s: failed to parse format", proc_stat);

	जबतक (1) अणु
		retval = ख_पूछो(fp, "cpu%u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d\n", &cpu_num);
		अगर (retval != 1)
			अवरोध;

		retval = func(cpu_num);
		अगर (retval) अणु
			ख_बंद(fp);
			वापस (retval);
		पूर्ण
	पूर्ण
	ख_बंद(fp);
	वापस 0;
पूर्ण

व्योम re_initialize(व्योम)
अणु
	मुक्त_all_buffers();
	setup_all_buffers();
	ख_लिखो(outf, "turbostat: re-initialized with num_cpus %d\n", topo.num_cpus);
पूर्ण

व्योम set_max_cpu_num(व्योम)
अणु
	खाता *filep;
	पूर्णांक base_cpu;
	अचिन्हित दीर्घ dummy;
	अक्षर pathname[64];

	base_cpu = sched_अ_लोpu();
	अगर (base_cpu < 0)
		err(1, "cannot find calling cpu ID");
	प्र_लिखो(pathname, "/sys/devices/system/cpu/cpu%d/topology/thread_siblings", base_cpu);

	filep = ख_खोलो_or_die(pathname, "r");
	topo.max_cpu_num = 0;
	जबतक (ख_पूछो(filep, "%lx,", &dummy) == 1)
		topo.max_cpu_num += BITMASK_SIZE;
	ख_बंद(filep);
	topo.max_cpu_num--;	/* 0 based */
पूर्ण

/*
 * count_cpus()
 * remember the last one seen, it will be the max
 */
पूर्णांक count_cpus(पूर्णांक cpu)
अणु
	topo.num_cpus++;
	वापस 0;
पूर्ण

पूर्णांक mark_cpu_present(पूर्णांक cpu)
अणु
	CPU_SET_S(cpu, cpu_present_setsize, cpu_present_set);
	वापस 0;
पूर्ण

पूर्णांक init_thपढ़ो_id(पूर्णांक cpu)
अणु
	cpus[cpu].thपढ़ो_id = -1;
	वापस 0;
पूर्ण

/*
 * snapshot_proc_पूर्णांकerrupts()
 *
 * पढ़ो and record summary of /proc/पूर्णांकerrupts
 *
 * वापस 1 अगर config change requires a restart, अन्यथा वापस 0
 */
पूर्णांक snapshot_proc_पूर्णांकerrupts(व्योम)
अणु
	अटल खाता *fp;
	पूर्णांक column, retval;

	अगर (fp == शून्य)
		fp = ख_खोलो_or_die("/proc/interrupts", "r");
	अन्यथा
		शुरुआत(fp);

	/* पढ़ो 1st line of /proc/पूर्णांकerrupts to get cpu* name क्रम each column */
	क्रम (column = 0; column < topo.num_cpus; ++column) अणु
		पूर्णांक cpu_number;

		retval = ख_पूछो(fp, " CPU%d", &cpu_number);
		अगर (retval != 1)
			अवरोध;

		अगर (cpu_number > topo.max_cpu_num) अणु
			warn("/proc/interrupts: cpu%d: > %d", cpu_number, topo.max_cpu_num);
			वापस 1;
		पूर्ण

		irq_column_2_cpu[column] = cpu_number;
		irqs_per_cpu[cpu_number] = 0;
	पूर्ण

	/* पढ़ो /proc/पूर्णांकerrupt count lines and sum up irqs per cpu */
	जबतक (1) अणु
		पूर्णांक column;
		अक्षर buf[64];

		retval = ख_पूछो(fp, " %s:", buf);	/* flush irq# "N:" */
		अगर (retval != 1)
			अवरोध;

		/* पढ़ो the count per cpu */
		क्रम (column = 0; column < topo.num_cpus; ++column) अणु

			पूर्णांक cpu_number, irq_count;

			retval = ख_पूछो(fp, " %d", &irq_count);
			अगर (retval != 1)
				अवरोध;

			cpu_number = irq_column_2_cpu[column];
			irqs_per_cpu[cpu_number] += irq_count;

		पूर्ण

		जबतक (अ_लो(fp) != '\n') ;	/* flush पूर्णांकerrupt description */

	पूर्ण
	वापस 0;
पूर्ण

/*
 * snapshot_gfx_rc6_ms()
 *
 * record snapshot of
 * /sys/class/drm/card0/घातer/rc6_residency_ms
 *
 * वापस 1 अगर config change requires a restart, अन्यथा वापस 0
 */
पूर्णांक snapshot_gfx_rc6_ms(व्योम)
अणु
	खाता *fp;
	पूर्णांक retval;

	fp = ख_खोलो_or_die("/sys/class/drm/card0/power/rc6_residency_ms", "r");

	retval = ख_पूछो(fp, "%lld", &gfx_cur_rc6_ms);
	अगर (retval != 1)
		err(1, "GFX rc6");

	ख_बंद(fp);

	वापस 0;
पूर्ण

/*
 * snapshot_gfx_mhz()
 *
 * record snapshot of
 * /sys/class/graphics/fb0/device/drm/card0/gt_cur_freq_mhz
 *
 * वापस 1 अगर config change requires a restart, अन्यथा वापस 0
 */
पूर्णांक snapshot_gfx_mhz(व्योम)
अणु
	अटल खाता *fp;
	पूर्णांक retval;

	अगर (fp == शून्य)
		fp = ख_खोलो_or_die("/sys/class/graphics/fb0/device/drm/card0/gt_cur_freq_mhz", "r");
	अन्यथा अणु
		शुरुआत(fp);
		ख_साफ(fp);
	पूर्ण

	retval = ख_पूछो(fp, "%d", &gfx_cur_mhz);
	अगर (retval != 1)
		err(1, "GFX MHz");

	वापस 0;
पूर्ण

/*
 * snapshot_gfx_cur_mhz()
 *
 * record snapshot of
 * /sys/class/graphics/fb0/device/drm/card0/gt_act_freq_mhz
 *
 * वापस 1 अगर config change requires a restart, अन्यथा वापस 0
 */
पूर्णांक snapshot_gfx_act_mhz(व्योम)
अणु
	अटल खाता *fp;
	पूर्णांक retval;

	अगर (fp == शून्य)
		fp = ख_खोलो_or_die("/sys/class/graphics/fb0/device/drm/card0/gt_act_freq_mhz", "r");
	अन्यथा अणु
		शुरुआत(fp);
		ख_साफ(fp);
	पूर्ण

	retval = ख_पूछो(fp, "%d", &gfx_act_mhz);
	अगर (retval != 1)
		err(1, "GFX ACT MHz");

	वापस 0;
पूर्ण

/*
 * snapshot_cpu_lpi()
 *
 * record snapshot of
 * /sys/devices/प्रणाली/cpu/cpuidle/low_घातer_idle_cpu_residency_us
 */
पूर्णांक snapshot_cpu_lpi_us(व्योम)
अणु
	खाता *fp;
	पूर्णांक retval;

	fp = ख_खोलो_or_die("/sys/devices/system/cpu/cpuidle/low_power_idle_cpu_residency_us", "r");

	retval = ख_पूछो(fp, "%lld", &cpuidle_cur_cpu_lpi_us);
	अगर (retval != 1) अणु
		ख_लिखो(मानक_त्रुटि, "Disabling Low Power Idle CPU output\n");
		BIC_NOT_PRESENT(BIC_CPU_LPI);
		ख_बंद(fp);
		वापस -1;
	पूर्ण

	ख_बंद(fp);

	वापस 0;
पूर्ण

/*
 * snapshot_sys_lpi()
 *
 * record snapshot of sys_lpi_file
 */
पूर्णांक snapshot_sys_lpi_us(व्योम)
अणु
	खाता *fp;
	पूर्णांक retval;

	fp = ख_खोलो_or_die(sys_lpi_file, "r");

	retval = ख_पूछो(fp, "%lld", &cpuidle_cur_sys_lpi_us);
	अगर (retval != 1) अणु
		ख_लिखो(मानक_त्रुटि, "Disabling Low Power Idle System output\n");
		BIC_NOT_PRESENT(BIC_SYS_LPI);
		ख_बंद(fp);
		वापस -1;
	पूर्ण
	ख_बंद(fp);

	वापस 0;
पूर्ण

/*
 * snapshot /proc and /sys files
 *
 * वापस 1 अगर configuration restart needed, अन्यथा वापस 0
 */
पूर्णांक snapshot_proc_sysfs_files(व्योम)
अणु
	अगर (DO_BIC(BIC_IRQ))
		अगर (snapshot_proc_पूर्णांकerrupts())
			वापस 1;

	अगर (DO_BIC(BIC_GFX_rc6))
		snapshot_gfx_rc6_ms();

	अगर (DO_BIC(BIC_GFXMHz))
		snapshot_gfx_mhz();

	अगर (DO_BIC(BIC_GFXACTMHz))
		snapshot_gfx_act_mhz();

	अगर (DO_BIC(BIC_CPU_LPI))
		snapshot_cpu_lpi_us();

	अगर (DO_BIC(BIC_SYS_LPI))
		snapshot_sys_lpi_us();

	वापस 0;
पूर्ण

पूर्णांक निकास_requested;

अटल व्योम संकेत_handler(पूर्णांक संकेत)
अणु
	चयन (संकेत) अणु
	हाल संक_विघ्न:
		निकास_requested = 1;
		अगर (debug)
			ख_लिखो(मानक_त्रुटि, " SIGINT\n");
		अवरोध;
	हाल SIGUSR1:
		अगर (debug > 1)
			ख_लिखो(मानक_त्रुटि, "SIGUSR1\n");
		अवरोध;
	पूर्ण
पूर्ण

व्योम setup_संकेत_handler(व्योम)
अणु
	काष्ठा sigaction sa;

	स_रखो(&sa, 0, माप(sa));

	sa.sa_handler = &संकेत_handler;

	अगर (sigaction(संक_विघ्न, &sa, शून्य) < 0)
		err(1, "sigaction SIGINT");
	अगर (sigaction(SIGUSR1, &sa, शून्य) < 0)
		err(1, "sigaction SIGUSR1");
पूर्ण

व्योम करो_sleep(व्योम)
अणु
	काष्ठा समयval tout;
	काष्ठा बारpec rest;
	fd_set पढ़ोfds;
	पूर्णांक retval;

	FD_ZERO(&पढ़ोfds);
	FD_SET(0, &पढ़ोfds);

	अगर (ignore_मानक_निवेश) अणु
		nanosleep(&पूर्णांकerval_ts, शून्य);
		वापस;
	पूर्ण

	tout = पूर्णांकerval_tv;
	retval = select(1, &पढ़ोfds, शून्य, शून्य, &tout);

	अगर (retval == 1) अणु
		चयन (अ_लो(मानक_निवेश)) अणु
		हाल 'q':
			निकास_requested = 1;
			अवरोध;
		हाल खातापूर्ण:
			/*
			 * 'stdin' is a pipe बंदd on the other end. There
			 * won't be any further input.
			 */
			ignore_मानक_निवेश = 1;
			/* Sleep the rest of the समय */
			rest.tv_sec = (tout.tv_sec + tout.tv_usec / 1000000);
			rest.tv_nsec = (tout.tv_usec % 1000000) * 1000;
			nanosleep(&rest, शून्य);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक get_msr_sum(पूर्णांक cpu, off_t offset, अचिन्हित दीर्घ दीर्घ *msr)
अणु
	पूर्णांक ret, idx;
	अचिन्हित दीर्घ दीर्घ msr_cur, msr_last;

	अगर (!per_cpu_msr_sum)
		वापस 1;

	idx = offset_to_idx(offset);
	अगर (idx < 0)
		वापस idx;
	/* get_msr_sum() = sum + (get_msr() - last) */
	ret = get_msr(cpu, offset, &msr_cur);
	अगर (ret)
		वापस ret;
	msr_last = per_cpu_msr_sum[cpu].entries[idx].last;
	DELTA_WRAP32(msr_cur, msr_last);
	*msr = msr_last + per_cpu_msr_sum[cpu].entries[idx].sum;

	वापस 0;
पूर्ण

समयr_t समयrid;

/* Timer callback, update the sum of MSRs periodically. */
अटल पूर्णांक update_msr_sum(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	पूर्णांक i, ret;
	पूर्णांक cpu = t->cpu_id;

	क्रम (i = IDX_PKG_ENERGY; i < IDX_COUNT; i++) अणु
		अचिन्हित दीर्घ दीर्घ msr_cur, msr_last;
		off_t offset;

		अगर (!idx_valid(i))
			जारी;
		offset = idx_to_offset(i);
		अगर (offset < 0)
			जारी;
		ret = get_msr(cpu, offset, &msr_cur);
		अगर (ret) अणु
			ख_लिखो(outf, "Can not update msr(0x%llx)\n", (अचिन्हित दीर्घ दीर्घ)offset);
			जारी;
		पूर्ण

		msr_last = per_cpu_msr_sum[cpu].entries[i].last;
		per_cpu_msr_sum[cpu].entries[i].last = msr_cur & 0xffffffff;

		DELTA_WRAP32(msr_cur, msr_last);
		per_cpu_msr_sum[cpu].entries[i].sum += msr_last;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम msr_record_handler(जोड़ sigval v)
अणु
	क्रम_all_cpus(update_msr_sum, EVEN_COUNTERS);
पूर्ण

व्योम msr_sum_record(व्योम)
अणु
	काष्ठा iसमयrspec its;
	काष्ठा sigevent sev;

	per_cpu_msr_sum = सुस्मृति(topo.max_cpu_num + 1, माप(काष्ठा msr_sum_array));
	अगर (!per_cpu_msr_sum) अणु
		ख_लिखो(outf, "Can not allocate memory for long time MSR.\n");
		वापस;
	पूर्ण
	/*
	 * Signal handler might be restricted, so use thपढ़ो notअगरier instead.
	 */
	स_रखो(&sev, 0, माप(काष्ठा sigevent));
	sev.sigev_notअगरy = SIGEV_THREAD;
	sev.sigev_notअगरy_function = msr_record_handler;

	sev.sigev_value.sival_ptr = &समयrid;
	अगर (समयr_create(CLOCK_REALTIME, &sev, &समयrid) == -1) अणु
		ख_लिखो(outf, "Can not create timer.\n");
		जाओ release_msr;
	पूर्ण

	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = 1;
	/*
	 * A wraparound समय has been calculated early.
	 * Some sources state that the peak घातer क्रम a
	 * microprocessor is usually 1.5 बार the TDP rating,
	 * use 2 * TDP क्रम safety.
	 */
	its.it_पूर्णांकerval.tv_sec = rapl_joule_counter_range / 2;
	its.it_पूर्णांकerval.tv_nsec = 0;

	अगर (समयr_समय_रखो(समयrid, 0, &its, शून्य) == -1) अणु
		ख_लिखो(outf, "Can not set timer.\n");
		जाओ release_समयr;
	पूर्ण
	वापस;

release_समयr:
	समयr_delete(समयrid);
release_msr:
	मुक्त(per_cpu_msr_sum);
पूर्ण

/*
 * set_my_sched_priority(pri)
 * वापस previous
 */
पूर्णांक set_my_sched_priority(पूर्णांक priority)
अणु
	पूर्णांक retval;
	पूर्णांक original_priority;

	त्रुटि_सं = 0;
	original_priority = getpriority(PRIO_PROCESS, 0);
	अगर (त्रुटि_सं && (original_priority == -1))
		err(त्रुटि_सं, "getpriority");

	retval = setpriority(PRIO_PROCESS, 0, priority);
	अगर (retval)
		err(retval, "setpriority(%d)", priority);

	त्रुटि_सं = 0;
	retval = getpriority(PRIO_PROCESS, 0);
	अगर (retval != priority)
		err(-1, "getpriority(%d) != setpriority(%d)", retval, priority);

	वापस original_priority;
पूर्ण

व्योम turbostat_loop()
अणु
	पूर्णांक retval;
	पूर्णांक restarted = 0;
	पूर्णांक करोne_iters = 0;

	setup_संकेत_handler();

	/*
	 * elevate own priority क्रम पूर्णांकerval mode
	 */
	set_my_sched_priority(-20);

restart:
	restarted++;

	snapshot_proc_sysfs_files();
	retval = क्रम_all_cpus(get_counters, EVEN_COUNTERS);
	first_counter_पढ़ो = 0;
	अगर (retval < -1) अणु
		निकास(retval);
	पूर्ण अन्यथा अगर (retval == -1) अणु
		अगर (restarted > 10) अणु
			निकास(retval);
		पूर्ण
		re_initialize();
		जाओ restart;
	पूर्ण
	restarted = 0;
	करोne_iters = 0;
	समय_लोofday(&tv_even, (काष्ठा समयzone *)शून्य);

	जबतक (1) अणु
		अगर (क्रम_all_proc_cpus(cpu_is_not_present)) अणु
			re_initialize();
			जाओ restart;
		पूर्ण
		करो_sleep();
		अगर (snapshot_proc_sysfs_files())
			जाओ restart;
		retval = क्रम_all_cpus(get_counters, ODD_COUNTERS);
		अगर (retval < -1) अणु
			निकास(retval);
		पूर्ण अन्यथा अगर (retval == -1) अणु
			re_initialize();
			जाओ restart;
		पूर्ण
		समय_लोofday(&tv_odd, (काष्ठा समयzone *)शून्य);
		समयrsub(&tv_odd, &tv_even, &tv_delta);
		अगर (क्रम_all_cpus_2(delta_cpu, ODD_COUNTERS, EVEN_COUNTERS)) अणु
			re_initialize();
			जाओ restart;
		पूर्ण
		compute_average(EVEN_COUNTERS);
		क्रमmat_all_counters(EVEN_COUNTERS);
		flush_output_मानक_निकास();
		अगर (निकास_requested)
			अवरोध;
		अगर (num_iterations && ++करोne_iters >= num_iterations)
			अवरोध;
		करो_sleep();
		अगर (snapshot_proc_sysfs_files())
			जाओ restart;
		retval = क्रम_all_cpus(get_counters, EVEN_COUNTERS);
		अगर (retval < -1) अणु
			निकास(retval);
		पूर्ण अन्यथा अगर (retval == -1) अणु
			re_initialize();
			जाओ restart;
		पूर्ण
		समय_लोofday(&tv_even, (काष्ठा समयzone *)शून्य);
		समयrsub(&tv_even, &tv_odd, &tv_delta);
		अगर (क्रम_all_cpus_2(delta_cpu, EVEN_COUNTERS, ODD_COUNTERS)) अणु
			re_initialize();
			जाओ restart;
		पूर्ण
		compute_average(ODD_COUNTERS);
		क्रमmat_all_counters(ODD_COUNTERS);
		flush_output_मानक_निकास();
		अगर (निकास_requested)
			अवरोध;
		अगर (num_iterations && ++करोne_iters >= num_iterations)
			अवरोध;
	पूर्ण
पूर्ण

व्योम check_dev_msr()
अणु
	काष्ठा stat sb;
	अक्षर pathname[32];

	प्र_लिखो(pathname, "/dev/cpu/%d/msr", base_cpu);
	अगर (stat(pathname, &sb))
		अगर (प्रणाली("/sbin/modprobe msr > /dev/null 2>&1"))
			err(-5, "no /dev/cpu/0/msr, Try \"# modprobe msr\" ");
पूर्ण

/*
 * check क्रम CAP_SYS_RAWIO
 * वापस 0 on success
 * वापस 1 on fail
 */
पूर्णांक check_क्रम_cap_sys_rawio(व्योम)
अणु
	cap_t caps;
	cap_flag_value_t cap_flag_value;

	caps = cap_get_proc();
	अगर (caps == शून्य)
		err(-6, "cap_get_proc\n");

	अगर (cap_get_flag(caps, CAP_SYS_RAWIO, CAP_EFFECTIVE, &cap_flag_value))
		err(-6, "cap_get\n");

	अगर (cap_flag_value != CAP_SET) अणु
		warnx("capget(CAP_SYS_RAWIO) failed," " try \"# setcap cap_sys_rawio=ep %s\"", progname);
		वापस 1;
	पूर्ण

	अगर (cap_मुक्त(caps) == -1)
		err(-6, "cap_free\n");

	वापस 0;
पूर्ण

व्योम check_permissions(व्योम)
अणु
	पूर्णांक करो_निकास = 0;
	अक्षर pathname[32];

	/* check क्रम CAP_SYS_RAWIO */
	करो_निकास += check_क्रम_cap_sys_rawio();

	/* test file permissions */
	प्र_लिखो(pathname, "/dev/cpu/%d/msr", base_cpu);
	अगर (euidaccess(pathname, R_OK)) अणु
		करो_निकास++;
		warn("/dev/cpu/0/msr open failed, try chown or chmod +r /dev/cpu/*/msr");
	पूर्ण

	/* अगर all अन्यथा fails, thell them to be root */
	अगर (करो_निकास)
		अगर (getuid() != 0)
			warnx("... or simply run as root");

	अगर (करो_निकास)
		निकास(-6);
पूर्ण

/*
 * NHM adds support क्रम additional MSRs:
 *
 * MSR_SMI_COUNT                   0x00000034
 *
 * MSR_PLATFORM_INFO               0x000000ce
 * MSR_PKG_CST_CONFIG_CONTROL     0x000000e2
 *
 * MSR_MISC_PWR_MGMT               0x000001aa
 *
 * MSR_PKG_C3_RESIDENCY            0x000003f8
 * MSR_PKG_C6_RESIDENCY            0x000003f9
 * MSR_CORE_C3_RESIDENCY           0x000003fc
 * MSR_CORE_C6_RESIDENCY           0x000003fd
 *
 * Side effect:
 * sets global pkg_cstate_limit to decode MSR_PKG_CST_CONFIG_CONTROL
 * sets has_misc_feature_control
 */
पूर्णांक probe_nhm_msrs(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक base_ratio;
	पूर्णांक *pkg_cstate_limits;

	अगर (!genuine_पूर्णांकel)
		वापस 0;

	अगर (family != 6)
		वापस 0;

	bclk = discover_bclk(family, model);

	चयन (model) अणु
	हाल INTEL_FAM6_NEHALEM:	/* Core i7 and i5 Processor - Clarksfield, Lynnfield, Jasper Forest */
	हाल INTEL_FAM6_NEHALEM_EX:	/* Nehalem-EX Xeon - Beckton */
		pkg_cstate_limits = nhm_pkg_cstate_limits;
		अवरोध;
	हाल INTEL_FAM6_SANDYBRIDGE:	/* SNB */
	हाल INTEL_FAM6_SANDYBRIDGE_X:	/* SNB Xeon */
	हाल INTEL_FAM6_IVYBRIDGE:	/* IVB */
	हाल INTEL_FAM6_IVYBRIDGE_X:	/* IVB Xeon */
		pkg_cstate_limits = snb_pkg_cstate_limits;
		has_misc_feature_control = 1;
		अवरोध;
	हाल INTEL_FAM6_HASWELL:	/* HSW */
	हाल INTEL_FAM6_HASWELL_G:	/* HSW */
	हाल INTEL_FAM6_HASWELL_X:	/* HSX */
	हाल INTEL_FAM6_HASWELL_L:	/* HSW */
	हाल INTEL_FAM6_BROADWELL:	/* BDW */
	हाल INTEL_FAM6_BROADWELL_G:	/* BDW */
	हाल INTEL_FAM6_BROADWELL_X:	/* BDX */
	हाल INTEL_FAM6_SKYLAKE_L:	/* SKL */
	हाल INTEL_FAM6_CANNONLAKE_L:	/* CNL */
		pkg_cstate_limits = hsw_pkg_cstate_limits;
		has_misc_feature_control = 1;
		अवरोध;
	हाल INTEL_FAM6_SKYLAKE_X:	/* SKX */
		pkg_cstate_limits = skx_pkg_cstate_limits;
		has_misc_feature_control = 1;
		अवरोध;
	हाल INTEL_FAM6_ICELAKE_X:	/* ICX */
		pkg_cstate_limits = icx_pkg_cstate_limits;
		has_misc_feature_control = 1;
		अवरोध;
	हाल INTEL_FAM6_ATOM_SILVERMONT:	/* BYT */
		no_MSR_MISC_PWR_MGMT = 1;
	हाल INTEL_FAM6_ATOM_SILVERMONT_D:	/* AVN */
		pkg_cstate_limits = slv_pkg_cstate_limits;
		अवरोध;
	हाल INTEL_FAM6_ATOM_AIRMONT:	/* AMT */
		pkg_cstate_limits = amt_pkg_cstate_limits;
		no_MSR_MISC_PWR_MGMT = 1;
		अवरोध;
	हाल INTEL_FAM6_XEON_PHI_KNL:	/* PHI */
		pkg_cstate_limits = phi_pkg_cstate_limits;
		अवरोध;
	हाल INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
	हाल INTEL_FAM6_ATOM_GOLDMONT_D:	/* DNV */
	हाल INTEL_FAM6_ATOM_TREMONT:	/* EHL */
	हाल INTEL_FAM6_ATOM_TREMONT_D:	/* JVL */
		pkg_cstate_limits = glm_pkg_cstate_limits;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	get_msr(base_cpu, MSR_PKG_CST_CONFIG_CONTROL, &msr);
	pkg_cstate_limit = pkg_cstate_limits[msr & 0xF];

	get_msr(base_cpu, MSR_PLATFORM_INFO, &msr);
	base_ratio = (msr >> 8) & 0xFF;

	base_hz = base_ratio * bclk * 1000000;
	has_base_hz = 1;
	वापस 1;
पूर्ण

/*
 * SLV client has support क्रम unique MSRs:
 *
 * MSR_CC6_DEMOTION_POLICY_CONFIG
 * MSR_MC6_DEMOTION_POLICY_CONFIG
 */

पूर्णांक has_slv_msrs(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_SILVERMONT:
	हाल INTEL_FAM6_ATOM_SILVERMONT_MID:
	हाल INTEL_FAM6_ATOM_AIRMONT_MID:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_dnv(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु

	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_GOLDMONT_D:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_bdx(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु

	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_BROADWELL_X:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_skx(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु

	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_SKYLAKE_X:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_icx(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु

	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_ICELAKE_X:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_ehl(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_TREMONT:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_jvl(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_TREMONT_D:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक has_turbo_ratio_limit(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (has_slv_msrs(family, model))
		वापस 0;

	चयन (model) अणु
		/* Nehalem compatible, but करो not include turbo-ratio limit support */
	हाल INTEL_FAM6_NEHALEM_EX:	/* Nehalem-EX Xeon - Beckton */
	हाल INTEL_FAM6_XEON_PHI_KNL:	/* PHI - Knights Landing (dअगरferent MSR definition) */
		वापस 0;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

पूर्णांक has_atom_turbo_ratio_limit(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (has_slv_msrs(family, model))
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक has_ivt_turbo_ratio_limit(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	अगर (family != 6)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_IVYBRIDGE_X:	/* IVB Xeon */
	हाल INTEL_FAM6_HASWELL_X:	/* HSW Xeon */
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक has_hsw_turbo_ratio_limit(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	अगर (family != 6)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_HASWELL_X:	/* HSW Xeon */
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक has_knl_turbo_ratio_limit(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	अगर (family != 6)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_XEON_PHI_KNL:	/* Knights Landing */
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक has_glm_turbo_ratio_limit(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	अगर (family != 6)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_GOLDMONT:
	हाल INTEL_FAM6_SKYLAKE_X:
	हाल INTEL_FAM6_ICELAKE_X:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक has_config_tdp(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	अगर (family != 6)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_IVYBRIDGE:	/* IVB */
	हाल INTEL_FAM6_HASWELL:	/* HSW */
	हाल INTEL_FAM6_HASWELL_X:	/* HSX */
	हाल INTEL_FAM6_HASWELL_L:	/* HSW */
	हाल INTEL_FAM6_HASWELL_G:	/* HSW */
	हाल INTEL_FAM6_BROADWELL:	/* BDW */
	हाल INTEL_FAM6_BROADWELL_G:	/* BDW */
	हाल INTEL_FAM6_BROADWELL_X:	/* BDX */
	हाल INTEL_FAM6_SKYLAKE_L:	/* SKL */
	हाल INTEL_FAM6_CANNONLAKE_L:	/* CNL */
	हाल INTEL_FAM6_SKYLAKE_X:	/* SKX */
	हाल INTEL_FAM6_ICELAKE_X:	/* ICX */

	हाल INTEL_FAM6_XEON_PHI_KNL:	/* Knights Landing */
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * tcc_offset_bits:
 * 0: Tcc Offset not supported (Default)
 * 6: Bit 29:24 of MSR_PLATFORM_INFO
 * 4: Bit 27:24 of MSR_PLATFORM_INFO
 */
व्योम check_tcc_offset(पूर्णांक model)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (!genuine_पूर्णांकel)
		वापस;

	चयन (model) अणु
	हाल INTEL_FAM6_SKYLAKE_L:
	हाल INTEL_FAM6_SKYLAKE:
	हाल INTEL_FAM6_KABYLAKE_L:
	हाल INTEL_FAM6_KABYLAKE:
	हाल INTEL_FAM6_ICELAKE_L:
	हाल INTEL_FAM6_ICELAKE:
	हाल INTEL_FAM6_TIGERLAKE_L:
	हाल INTEL_FAM6_TIGERLAKE:
	हाल INTEL_FAM6_COMETLAKE:
		अगर (!get_msr(base_cpu, MSR_PLATFORM_INFO, &msr)) अणु
			msr = (msr >> 30) & 1;
			अगर (msr)
				tcc_offset_bits = 6;
		पूर्ण
		वापस;
	शेष:
		वापस;
	पूर्ण
पूर्ण

अटल व्योम हटाओ_underbar(अक्षर *s)
अणु
	अक्षर *to = s;

	जबतक (*s) अणु
		अगर (*s != '_')
			*to++ = *s;
		s++;
	पूर्ण

	*to = 0;
पूर्ण

अटल व्योम dump_cstate_pstate_config_info(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!करो_nhm_platक्रमm_info)
		वापस;

	dump_nhm_platक्रमm_info();

	अगर (has_hsw_turbo_ratio_limit(family, model))
		dump_hsw_turbo_ratio_limits();

	अगर (has_ivt_turbo_ratio_limit(family, model))
		dump_ivt_turbo_ratio_limits();

	अगर (has_turbo_ratio_limit(family, model))
		dump_turbo_ratio_limits(family, model);

	अगर (has_atom_turbo_ratio_limit(family, model))
		dump_atom_turbo_ratio_limits();

	अगर (has_knl_turbo_ratio_limit(family, model))
		dump_knl_turbo_ratio_limits();

	अगर (has_config_tdp(family, model))
		dump_config_tdp();

	dump_nhm_cst_cfg();
पूर्ण

अटल व्योम dump_sysfs_file(अक्षर *path)
अणु
	खाता *input;
	अक्षर cpuidle_buf[64];

	input = ख_खोलो(path, "r");
	अगर (input == शून्य) अणु
		अगर (debug)
			ख_लिखो(outf, "NSFOD %s\n", path);
		वापस;
	पूर्ण
	अगर (!ख_माला_लो(cpuidle_buf, माप(cpuidle_buf), input))
		err(1, "%s: failed to read file", path);
	ख_बंद(input);

	ख_लिखो(outf, "%s: %s", म_खोजप(path, '/') + 1, cpuidle_buf);
पूर्ण

अटल व्योम dump_sysfs_cstate_config(व्योम)
अणु
	अक्षर path[64];
	अक्षर name_buf[16];
	अक्षर desc[64];
	खाता *input;
	पूर्णांक state;
	अक्षर *sp;

	अगर (access("/sys/devices/system/cpu/cpuidle", R_OK)) अणु
		ख_लिखो(outf, "cpuidle not loaded\n");
		वापस;
	पूर्ण

	dump_sysfs_file("/sys/devices/system/cpu/cpuidle/current_driver");
	dump_sysfs_file("/sys/devices/system/cpu/cpuidle/current_governor");
	dump_sysfs_file("/sys/devices/system/cpu/cpuidle/current_governor_ro");

	क्रम (state = 0; state < 10; ++state) अणु

		प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/cpuidle/state%d/name", base_cpu, state);
		input = ख_खोलो(path, "r");
		अगर (input == शून्य)
			जारी;
		अगर (!ख_माला_लो(name_buf, माप(name_buf), input))
			err(1, "%s: failed to read file", path);

		/* truncate "C1-HSW\n" to "C1", or truncate "C1\n" to "C1" */
		sp = म_अक्षर(name_buf, '-');
		अगर (!sp)
			sp = म_अक्षरnul(name_buf, '\n');
		*sp = '\0';
		ख_बंद(input);

		हटाओ_underbar(name_buf);

		प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/cpuidle/state%d/desc", base_cpu, state);
		input = ख_खोलो(path, "r");
		अगर (input == शून्य)
			जारी;
		अगर (!ख_माला_लो(desc, माप(desc), input))
			err(1, "%s: failed to read file", path);

		ख_लिखो(outf, "cpu%d: %s: %s", base_cpu, name_buf, desc);
		ख_बंद(input);
	पूर्ण
पूर्ण

अटल व्योम dump_sysfs_pstate_config(व्योम)
अणु
	अक्षर path[64];
	अक्षर driver_buf[64];
	अक्षर governor_buf[64];
	खाता *input;
	पूर्णांक turbo;

	प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_driver", base_cpu);
	input = ख_खोलो(path, "r");
	अगर (input == शून्य) अणु
		ख_लिखो(outf, "NSFOD %s\n", path);
		वापस;
	पूर्ण
	अगर (!ख_माला_लो(driver_buf, माप(driver_buf), input))
		err(1, "%s: failed to read file", path);
	ख_बंद(input);

	प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_governor", base_cpu);
	input = ख_खोलो(path, "r");
	अगर (input == शून्य) अणु
		ख_लिखो(outf, "NSFOD %s\n", path);
		वापस;
	पूर्ण
	अगर (!ख_माला_लो(governor_buf, माप(governor_buf), input))
		err(1, "%s: failed to read file", path);
	ख_बंद(input);

	ख_लिखो(outf, "cpu%d: cpufreq driver: %s", base_cpu, driver_buf);
	ख_लिखो(outf, "cpu%d: cpufreq governor: %s", base_cpu, governor_buf);

	प्र_लिखो(path, "/sys/devices/system/cpu/cpufreq/boost");
	input = ख_खोलो(path, "r");
	अगर (input != शून्य) अणु
		अगर (ख_पूछो(input, "%d", &turbo) != 1)
			err(1, "%s: failed to parse number from file", path);
		ख_लिखो(outf, "cpufreq boost: %d\n", turbo);
		ख_बंद(input);
	पूर्ण

	प्र_लिखो(path, "/sys/devices/system/cpu/intel_pstate/no_turbo");
	input = ख_खोलो(path, "r");
	अगर (input != शून्य) अणु
		अगर (ख_पूछो(input, "%d", &turbo) != 1)
			err(1, "%s: failed to parse number from file", path);
		ख_लिखो(outf, "cpufreq intel_pstate no_turbo: %d\n", turbo);
		ख_बंद(input);
	पूर्ण
पूर्ण

/*
 * prपूर्णांक_epb()
 * Decode the ENERGY_PERF_BIAS MSR
 */
पूर्णांक prपूर्णांक_epb(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	अक्षर *epb_string;
	पूर्णांक cpu, epb;

	अगर (!has_epb)
		वापस 0;

	cpu = t->cpu_id;

	/* EPB is per-package */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE) || !(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		वापस 0;

	अगर (cpu_migrate(cpu)) अणु
		ख_लिखो(outf, "print_epb: Could not migrate to CPU %d\n", cpu);
		वापस -1;
	पूर्ण

	epb = get_epb(cpu);
	अगर (epb < 0)
		वापस 0;

	चयन (epb) अणु
	हाल ENERGY_PERF_BIAS_PERFORMANCE:
		epb_string = "performance";
		अवरोध;
	हाल ENERGY_PERF_BIAS_NORMAL:
		epb_string = "balanced";
		अवरोध;
	हाल ENERGY_PERF_BIAS_POWERSAVE:
		epb_string = "powersave";
		अवरोध;
	शेष:
		epb_string = "custom";
		अवरोध;
	पूर्ण
	ख_लिखो(outf, "cpu%d: EPB: %d (%s)\n", cpu, epb, epb_string);

	वापस 0;
पूर्ण

/*
 * prपूर्णांक_hwp()
 * Decode the MSR_HWP_CAPABILITIES
 */
पूर्णांक prपूर्णांक_hwp(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	पूर्णांक cpu;

	अगर (!has_hwp)
		वापस 0;

	cpu = t->cpu_id;

	/* MSR_HWP_CAPABILITIES is per-package */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE) || !(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		वापस 0;

	अगर (cpu_migrate(cpu)) अणु
		ख_लिखो(outf, "print_hwp: Could not migrate to CPU %d\n", cpu);
		वापस -1;
	पूर्ण

	अगर (get_msr(cpu, MSR_PM_ENABLE, &msr))
		वापस 0;

	ख_लिखो(outf, "cpu%d: MSR_PM_ENABLE: 0x%08llx (%sHWP)\n", cpu, msr, (msr & (1 << 0)) ? "" : "No-");

	/* MSR_PM_ENABLE[1] == 1 अगर HWP is enabled and MSRs visible */
	अगर ((msr & (1 << 0)) == 0)
		वापस 0;

	अगर (get_msr(cpu, MSR_HWP_CAPABILITIES, &msr))
		वापस 0;

	ख_लिखो(outf, "cpu%d: MSR_HWP_CAPABILITIES: 0x%08llx "
		"(high %d guar %d eff %d low %d)\n",
		cpu, msr,
		(अचिन्हित पूर्णांक)HWP_HIGHEST_PERF(msr),
		(अचिन्हित पूर्णांक)HWP_GUARANTEED_PERF(msr),
		(अचिन्हित पूर्णांक)HWP_MOSTEFFICIENT_PERF(msr), (अचिन्हित पूर्णांक)HWP_LOWEST_PERF(msr));

	अगर (get_msr(cpu, MSR_HWP_REQUEST, &msr))
		वापस 0;

	ख_लिखो(outf, "cpu%d: MSR_HWP_REQUEST: 0x%08llx "
		"(min %d max %d des %d epp 0x%x window 0x%x pkg 0x%x)\n",
		cpu, msr,
		(अचिन्हित पूर्णांक)(((msr) >> 0) & 0xff),
		(अचिन्हित पूर्णांक)(((msr) >> 8) & 0xff),
		(अचिन्हित पूर्णांक)(((msr) >> 16) & 0xff),
		(अचिन्हित पूर्णांक)(((msr) >> 24) & 0xff),
		(अचिन्हित पूर्णांक)(((msr) >> 32) & 0xff3), (अचिन्हित पूर्णांक)(((msr) >> 42) & 0x1));

	अगर (has_hwp_pkg) अणु
		अगर (get_msr(cpu, MSR_HWP_REQUEST_PKG, &msr))
			वापस 0;

		ख_लिखो(outf, "cpu%d: MSR_HWP_REQUEST_PKG: 0x%08llx "
			"(min %d max %d des %d epp 0x%x window 0x%x)\n",
			cpu, msr,
			(अचिन्हित पूर्णांक)(((msr) >> 0) & 0xff),
			(अचिन्हित पूर्णांक)(((msr) >> 8) & 0xff),
			(अचिन्हित पूर्णांक)(((msr) >> 16) & 0xff),
			(अचिन्हित पूर्णांक)(((msr) >> 24) & 0xff), (अचिन्हित पूर्णांक)(((msr) >> 32) & 0xff3));
	पूर्ण
	अगर (has_hwp_notअगरy) अणु
		अगर (get_msr(cpu, MSR_HWP_INTERRUPT, &msr))
			वापस 0;

		ख_लिखो(outf, "cpu%d: MSR_HWP_INTERRUPT: 0x%08llx "
			"(%s_Guaranteed_Perf_Change, %s_Excursion_Min)\n",
			cpu, msr, ((msr) & 0x1) ? "EN" : "Dis", ((msr) & 0x2) ? "EN" : "Dis");
	पूर्ण
	अगर (get_msr(cpu, MSR_HWP_STATUS, &msr))
		वापस 0;

	ख_लिखो(outf, "cpu%d: MSR_HWP_STATUS: 0x%08llx "
		"(%sGuaranteed_Perf_Change, %sExcursion_Min)\n",
		cpu, msr, ((msr) & 0x1) ? "" : "No-", ((msr) & 0x2) ? "" : "No-");

	वापस 0;
पूर्ण

/*
 * prपूर्णांक_perf_limit()
 */
पूर्णांक prपूर्णांक_perf_limit(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	पूर्णांक cpu;

	cpu = t->cpu_id;

	/* per-package */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE) || !(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		वापस 0;

	अगर (cpu_migrate(cpu)) अणु
		ख_लिखो(outf, "print_perf_limit: Could not migrate to CPU %d\n", cpu);
		वापस -1;
	पूर्ण

	अगर (करो_core_perf_limit_reasons) अणु
		get_msr(cpu, MSR_CORE_PERF_LIMIT_REASONS, &msr);
		ख_लिखो(outf, "cpu%d: MSR_CORE_PERF_LIMIT_REASONS, 0x%08llx", cpu, msr);
		ख_लिखो(outf, " (Active: %s%s%s%s%s%s%s%s%s%s%s%s%s%s)",
			(msr & 1 << 15) ? "bit15, " : "",
			(msr & 1 << 14) ? "bit14, " : "",
			(msr & 1 << 13) ? "Transitions, " : "",
			(msr & 1 << 12) ? "MultiCoreTurbo, " : "",
			(msr & 1 << 11) ? "PkgPwrL2, " : "",
			(msr & 1 << 10) ? "PkgPwrL1, " : "",
			(msr & 1 << 9) ? "CorePwr, " : "",
			(msr & 1 << 8) ? "Amps, " : "",
			(msr & 1 << 6) ? "VR-Therm, " : "",
			(msr & 1 << 5) ? "Auto-HWP, " : "",
			(msr & 1 << 4) ? "Graphics, " : "",
			(msr & 1 << 2) ? "bit2, " : "",
			(msr & 1 << 1) ? "ThermStatus, " : "", (msr & 1 << 0) ? "PROCHOT, " : "");
		ख_लिखो(outf, " (Logged: %s%s%s%s%s%s%s%s%s%s%s%s%s%s)\n",
			(msr & 1 << 31) ? "bit31, " : "",
			(msr & 1 << 30) ? "bit30, " : "",
			(msr & 1 << 29) ? "Transitions, " : "",
			(msr & 1 << 28) ? "MultiCoreTurbo, " : "",
			(msr & 1 << 27) ? "PkgPwrL2, " : "",
			(msr & 1 << 26) ? "PkgPwrL1, " : "",
			(msr & 1 << 25) ? "CorePwr, " : "",
			(msr & 1 << 24) ? "Amps, " : "",
			(msr & 1 << 22) ? "VR-Therm, " : "",
			(msr & 1 << 21) ? "Auto-HWP, " : "",
			(msr & 1 << 20) ? "Graphics, " : "",
			(msr & 1 << 18) ? "bit18, " : "",
			(msr & 1 << 17) ? "ThermStatus, " : "", (msr & 1 << 16) ? "PROCHOT, " : "");

	पूर्ण
	अगर (करो_gfx_perf_limit_reasons) अणु
		get_msr(cpu, MSR_GFX_PERF_LIMIT_REASONS, &msr);
		ख_लिखो(outf, "cpu%d: MSR_GFX_PERF_LIMIT_REASONS, 0x%08llx", cpu, msr);
		ख_लिखो(outf, " (Active: %s%s%s%s%s%s%s%s)",
			(msr & 1 << 0) ? "PROCHOT, " : "",
			(msr & 1 << 1) ? "ThermStatus, " : "",
			(msr & 1 << 4) ? "Graphics, " : "",
			(msr & 1 << 6) ? "VR-Therm, " : "",
			(msr & 1 << 8) ? "Amps, " : "",
			(msr & 1 << 9) ? "GFXPwr, " : "",
			(msr & 1 << 10) ? "PkgPwrL1, " : "", (msr & 1 << 11) ? "PkgPwrL2, " : "");
		ख_लिखो(outf, " (Logged: %s%s%s%s%s%s%s%s)\n",
			(msr & 1 << 16) ? "PROCHOT, " : "",
			(msr & 1 << 17) ? "ThermStatus, " : "",
			(msr & 1 << 20) ? "Graphics, " : "",
			(msr & 1 << 22) ? "VR-Therm, " : "",
			(msr & 1 << 24) ? "Amps, " : "",
			(msr & 1 << 25) ? "GFXPwr, " : "",
			(msr & 1 << 26) ? "PkgPwrL1, " : "", (msr & 1 << 27) ? "PkgPwrL2, " : "");
	पूर्ण
	अगर (करो_ring_perf_limit_reasons) अणु
		get_msr(cpu, MSR_RING_PERF_LIMIT_REASONS, &msr);
		ख_लिखो(outf, "cpu%d: MSR_RING_PERF_LIMIT_REASONS, 0x%08llx", cpu, msr);
		ख_लिखो(outf, " (Active: %s%s%s%s%s%s)",
			(msr & 1 << 0) ? "PROCHOT, " : "",
			(msr & 1 << 1) ? "ThermStatus, " : "",
			(msr & 1 << 6) ? "VR-Therm, " : "",
			(msr & 1 << 8) ? "Amps, " : "",
			(msr & 1 << 10) ? "PkgPwrL1, " : "", (msr & 1 << 11) ? "PkgPwrL2, " : "");
		ख_लिखो(outf, " (Logged: %s%s%s%s%s%s)\n",
			(msr & 1 << 16) ? "PROCHOT, " : "",
			(msr & 1 << 17) ? "ThermStatus, " : "",
			(msr & 1 << 22) ? "VR-Therm, " : "",
			(msr & 1 << 24) ? "Amps, " : "",
			(msr & 1 << 26) ? "PkgPwrL1, " : "", (msr & 1 << 27) ? "PkgPwrL2, " : "");
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा	RAPL_POWER_GRANULARITY	0x7FFF	/* 15 bit घातer granularity */
#घोषणा	RAPL_TIME_GRANULARITY	0x3F	/* 6 bit समय granularity */

द्विगुन get_tdp_पूर्णांकel(अचिन्हित पूर्णांक model)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (करो_rapl & RAPL_PKG_POWER_INFO)
		अगर (!get_msr(base_cpu, MSR_PKG_POWER_INFO, &msr))
			वापस ((msr >> 0) & RAPL_POWER_GRANULARITY) * rapl_घातer_units;

	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_SILVERMONT:
	हाल INTEL_FAM6_ATOM_SILVERMONT_D:
		वापस 30.0;
	शेष:
		वापस 135.0;
	पूर्ण
पूर्ण

द्विगुन get_tdp_amd(अचिन्हित पूर्णांक family)
अणु
	/* This is the max stock TDP of HEDT/Server Fam17h+ chips */
	वापस 280.0;
पूर्ण

/*
 * rapl_dram_energy_units_probe()
 * Energy units are either hard-coded, or come from RAPL Energy Unit MSR.
 */
अटल द्विगुन rapl_dram_energy_units_probe(पूर्णांक model, द्विगुन rapl_energy_units)
अणु
	/* only called क्रम genuine_पूर्णांकel, family 6 */

	चयन (model) अणु
	हाल INTEL_FAM6_HASWELL_X:	/* HSX */
	हाल INTEL_FAM6_BROADWELL_X:	/* BDX */
	हाल INTEL_FAM6_SKYLAKE_X:	/* SKX */
	हाल INTEL_FAM6_XEON_PHI_KNL:	/* KNL */
		वापस (rapl_dram_energy_units = 15.3 / 1000000);
	शेष:
		वापस (rapl_energy_units);
	पूर्ण
पूर्ण

व्योम rapl_probe_पूर्णांकel(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक समय_unit;
	द्विगुन tdp;

	अगर (family != 6)
		वापस;

	चयन (model) अणु
	हाल INTEL_FAM6_SANDYBRIDGE:
	हाल INTEL_FAM6_IVYBRIDGE:
	हाल INTEL_FAM6_HASWELL:	/* HSW */
	हाल INTEL_FAM6_HASWELL_L:	/* HSW */
	हाल INTEL_FAM6_HASWELL_G:	/* HSW */
	हाल INTEL_FAM6_BROADWELL:	/* BDW */
	हाल INTEL_FAM6_BROADWELL_G:	/* BDW */
		करो_rapl = RAPL_PKG | RAPL_CORES | RAPL_CORE_POLICY | RAPL_GFX | RAPL_PKG_POWER_INFO;
		अगर (rapl_joules) अणु
			BIC_PRESENT(BIC_Pkg_J);
			BIC_PRESENT(BIC_Cor_J);
			BIC_PRESENT(BIC_GFX_J);
		पूर्ण अन्यथा अणु
			BIC_PRESENT(BIC_PkgWatt);
			BIC_PRESENT(BIC_CorWatt);
			BIC_PRESENT(BIC_GFXWatt);
		पूर्ण
		अवरोध;
	हाल INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
		करो_rapl = RAPL_PKG | RAPL_PKG_POWER_INFO;
		अगर (rapl_joules)
			BIC_PRESENT(BIC_Pkg_J);
		अन्यथा
			BIC_PRESENT(BIC_PkgWatt);
		अवरोध;
	हाल INTEL_FAM6_ATOM_TREMONT:	/* EHL */
		करो_rapl =
		    RAPL_PKG | RAPL_CORES | RAPL_CORE_POLICY | RAPL_DRAM | RAPL_DRAM_PERF_STATUS | RAPL_PKG_PERF_STATUS
		    | RAPL_GFX | RAPL_PKG_POWER_INFO;
		अगर (rapl_joules) अणु
			BIC_PRESENT(BIC_Pkg_J);
			BIC_PRESENT(BIC_Cor_J);
			BIC_PRESENT(BIC_RAM_J);
			BIC_PRESENT(BIC_GFX_J);
		पूर्ण अन्यथा अणु
			BIC_PRESENT(BIC_PkgWatt);
			BIC_PRESENT(BIC_CorWatt);
			BIC_PRESENT(BIC_RAMWatt);
			BIC_PRESENT(BIC_GFXWatt);
		पूर्ण
		अवरोध;
	हाल INTEL_FAM6_ATOM_TREMONT_D:	/* JVL */
		करो_rapl = RAPL_PKG | RAPL_PKG_PERF_STATUS | RAPL_PKG_POWER_INFO;
		BIC_PRESENT(BIC_PKG__);
		अगर (rapl_joules)
			BIC_PRESENT(BIC_Pkg_J);
		अन्यथा
			BIC_PRESENT(BIC_PkgWatt);
		अवरोध;
	हाल INTEL_FAM6_SKYLAKE_L:	/* SKL */
	हाल INTEL_FAM6_CANNONLAKE_L:	/* CNL */
		करो_rapl =
		    RAPL_PKG | RAPL_CORES | RAPL_CORE_POLICY | RAPL_DRAM | RAPL_DRAM_PERF_STATUS | RAPL_PKG_PERF_STATUS
		    | RAPL_GFX | RAPL_PKG_POWER_INFO;
		BIC_PRESENT(BIC_PKG__);
		BIC_PRESENT(BIC_RAM__);
		अगर (rapl_joules) अणु
			BIC_PRESENT(BIC_Pkg_J);
			BIC_PRESENT(BIC_Cor_J);
			BIC_PRESENT(BIC_RAM_J);
			BIC_PRESENT(BIC_GFX_J);
		पूर्ण अन्यथा अणु
			BIC_PRESENT(BIC_PkgWatt);
			BIC_PRESENT(BIC_CorWatt);
			BIC_PRESENT(BIC_RAMWatt);
			BIC_PRESENT(BIC_GFXWatt);
		पूर्ण
		अवरोध;
	हाल INTEL_FAM6_HASWELL_X:	/* HSX */
	हाल INTEL_FAM6_BROADWELL_X:	/* BDX */
	हाल INTEL_FAM6_SKYLAKE_X:	/* SKX */
	हाल INTEL_FAM6_ICELAKE_X:	/* ICX */
	हाल INTEL_FAM6_XEON_PHI_KNL:	/* KNL */
		करो_rapl =
		    RAPL_PKG | RAPL_DRAM | RAPL_DRAM_POWER_INFO | RAPL_DRAM_PERF_STATUS | RAPL_PKG_PERF_STATUS |
		    RAPL_PKG_POWER_INFO;
		BIC_PRESENT(BIC_PKG__);
		BIC_PRESENT(BIC_RAM__);
		अगर (rapl_joules) अणु
			BIC_PRESENT(BIC_Pkg_J);
			BIC_PRESENT(BIC_RAM_J);
		पूर्ण अन्यथा अणु
			BIC_PRESENT(BIC_PkgWatt);
			BIC_PRESENT(BIC_RAMWatt);
		पूर्ण
		अवरोध;
	हाल INTEL_FAM6_SANDYBRIDGE_X:
	हाल INTEL_FAM6_IVYBRIDGE_X:
		करो_rapl =
		    RAPL_PKG | RAPL_CORES | RAPL_CORE_POLICY | RAPL_DRAM | RAPL_DRAM_POWER_INFO | RAPL_PKG_PERF_STATUS |
		    RAPL_DRAM_PERF_STATUS | RAPL_PKG_POWER_INFO;
		BIC_PRESENT(BIC_PKG__);
		BIC_PRESENT(BIC_RAM__);
		अगर (rapl_joules) अणु
			BIC_PRESENT(BIC_Pkg_J);
			BIC_PRESENT(BIC_Cor_J);
			BIC_PRESENT(BIC_RAM_J);
		पूर्ण अन्यथा अणु
			BIC_PRESENT(BIC_PkgWatt);
			BIC_PRESENT(BIC_CorWatt);
			BIC_PRESENT(BIC_RAMWatt);
		पूर्ण
		अवरोध;
	हाल INTEL_FAM6_ATOM_SILVERMONT:	/* BYT */
	हाल INTEL_FAM6_ATOM_SILVERMONT_D:	/* AVN */
		करो_rapl = RAPL_PKG | RAPL_CORES;
		अगर (rapl_joules) अणु
			BIC_PRESENT(BIC_Pkg_J);
			BIC_PRESENT(BIC_Cor_J);
		पूर्ण अन्यथा अणु
			BIC_PRESENT(BIC_PkgWatt);
			BIC_PRESENT(BIC_CorWatt);
		पूर्ण
		अवरोध;
	हाल INTEL_FAM6_ATOM_GOLDMONT_D:	/* DNV */
		करो_rapl =
		    RAPL_PKG | RAPL_DRAM | RAPL_DRAM_POWER_INFO | RAPL_DRAM_PERF_STATUS | RAPL_PKG_PERF_STATUS |
		    RAPL_PKG_POWER_INFO | RAPL_CORES_ENERGY_STATUS;
		BIC_PRESENT(BIC_PKG__);
		BIC_PRESENT(BIC_RAM__);
		अगर (rapl_joules) अणु
			BIC_PRESENT(BIC_Pkg_J);
			BIC_PRESENT(BIC_Cor_J);
			BIC_PRESENT(BIC_RAM_J);
		पूर्ण अन्यथा अणु
			BIC_PRESENT(BIC_PkgWatt);
			BIC_PRESENT(BIC_CorWatt);
			BIC_PRESENT(BIC_RAMWatt);
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* units on package 0, verअगरy later other packages match */
	अगर (get_msr(base_cpu, MSR_RAPL_POWER_UNIT, &msr))
		वापस;

	rapl_घातer_units = 1.0 / (1 << (msr & 0xF));
	अगर (model == INTEL_FAM6_ATOM_SILVERMONT)
		rapl_energy_units = 1.0 * (1 << (msr >> 8 & 0x1F)) / 1000000;
	अन्यथा
		rapl_energy_units = 1.0 / (1 << (msr >> 8 & 0x1F));

	rapl_dram_energy_units = rapl_dram_energy_units_probe(model, rapl_energy_units);

	समय_unit = msr >> 16 & 0xF;
	अगर (समय_unit == 0)
		समय_unit = 0xA;

	rapl_समय_units = 1.0 / (1 << (समय_unit));

	tdp = get_tdp_पूर्णांकel(model);

	rapl_joule_counter_range = 0xFFFFFFFF * rapl_energy_units / tdp;
	अगर (!quiet)
		ख_लिखो(outf, "RAPL: %.0f sec. Joule Counter Range, at %.0f Watts\n", rapl_joule_counter_range, tdp);
पूर्ण

व्योम rapl_probe_amd(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अचिन्हित पूर्णांक has_rapl = 0;
	द्विगुन tdp;

	अगर (max_extended_level >= 0x80000007) अणु
		__cpuid(0x80000007, eax, ebx, ecx, edx);
		/* RAPL (Fam 17h+) */
		has_rapl = edx & (1 << 14);
	पूर्ण

	अगर (!has_rapl || family < 0x17)
		वापस;

	करो_rapl = RAPL_AMD_F17H | RAPL_PER_CORE_ENERGY;
	अगर (rapl_joules) अणु
		BIC_PRESENT(BIC_Pkg_J);
		BIC_PRESENT(BIC_Cor_J);
	पूर्ण अन्यथा अणु
		BIC_PRESENT(BIC_PkgWatt);
		BIC_PRESENT(BIC_CorWatt);
	पूर्ण

	अगर (get_msr(base_cpu, MSR_RAPL_PWR_UNIT, &msr))
		वापस;

	rapl_समय_units = ldexp(1.0, -(msr >> 16 & 0xf));
	rapl_energy_units = ldexp(1.0, -(msr >> 8 & 0x1f));
	rapl_घातer_units = ldexp(1.0, -(msr & 0xf));

	tdp = get_tdp_amd(family);

	rapl_joule_counter_range = 0xFFFFFFFF * rapl_energy_units / tdp;
	अगर (!quiet)
		ख_लिखो(outf, "RAPL: %.0f sec. Joule Counter Range, at %.0f Watts\n", rapl_joule_counter_range, tdp);
पूर्ण

/*
 * rapl_probe()
 *
 * sets करो_rapl, rapl_घातer_units, rapl_energy_units, rapl_समय_units
 */
व्योम rapl_probe(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (genuine_पूर्णांकel)
		rapl_probe_पूर्णांकel(family, model);
	अगर (authentic_amd || hygon_genuine)
		rapl_probe_amd(family, model);
पूर्ण

व्योम perf_limit_reasons_probe(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस;

	अगर (family != 6)
		वापस;

	चयन (model) अणु
	हाल INTEL_FAM6_HASWELL:	/* HSW */
	हाल INTEL_FAM6_HASWELL_L:	/* HSW */
	हाल INTEL_FAM6_HASWELL_G:	/* HSW */
		करो_gfx_perf_limit_reasons = 1;
	हाल INTEL_FAM6_HASWELL_X:	/* HSX */
		करो_core_perf_limit_reasons = 1;
		करो_ring_perf_limit_reasons = 1;
	शेष:
		वापस;
	पूर्ण
पूर्ण

व्योम स्वतःmatic_cstate_conversion_probe(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (is_skx(family, model) || is_bdx(family, model) || is_icx(family, model))
		has_स्वतःmatic_cstate_conversion = 1;
पूर्ण

व्योम prewake_cstate_probe(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (is_icx(family, model))
		dis_cstate_prewake = 1;
पूर्ण

पूर्णांक prपूर्णांक_thermal(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक dts, dts2;
	पूर्णांक cpu;

	अगर (!(करो_dts || करो_pपंचांग))
		वापस 0;

	cpu = t->cpu_id;

	/* DTS is per-core, no need to prपूर्णांक क्रम each thपढ़ो */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE))
		वापस 0;

	अगर (cpu_migrate(cpu)) अणु
		ख_लिखो(outf, "print_thermal: Could not migrate to CPU %d\n", cpu);
		वापस -1;
	पूर्ण

	अगर (करो_pपंचांग && (t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE)) अणु
		अगर (get_msr(cpu, MSR_IA32_PACKAGE_THERM_STATUS, &msr))
			वापस 0;

		dts = (msr >> 16) & 0x7F;
		ख_लिखो(outf, "cpu%d: MSR_IA32_PACKAGE_THERM_STATUS: 0x%08llx (%d C)\n", cpu, msr, tj_max - dts);

		अगर (get_msr(cpu, MSR_IA32_PACKAGE_THERM_INTERRUPT, &msr))
			वापस 0;

		dts = (msr >> 16) & 0x7F;
		dts2 = (msr >> 8) & 0x7F;
		ख_लिखो(outf, "cpu%d: MSR_IA32_PACKAGE_THERM_INTERRUPT: 0x%08llx (%d C, %d C)\n",
			cpu, msr, tj_max - dts, tj_max - dts2);
	पूर्ण

	अगर (करो_dts && debug) अणु
		अचिन्हित पूर्णांक resolution;

		अगर (get_msr(cpu, MSR_IA32_THERM_STATUS, &msr))
			वापस 0;

		dts = (msr >> 16) & 0x7F;
		resolution = (msr >> 27) & 0xF;
		ख_लिखो(outf, "cpu%d: MSR_IA32_THERM_STATUS: 0x%08llx (%d C +/- %d)\n",
			cpu, msr, tj_max - dts, resolution);

		अगर (get_msr(cpu, MSR_IA32_THERM_INTERRUPT, &msr))
			वापस 0;

		dts = (msr >> 16) & 0x7F;
		dts2 = (msr >> 8) & 0x7F;
		ख_लिखो(outf, "cpu%d: MSR_IA32_THERM_INTERRUPT: 0x%08llx (%d C, %d C)\n",
			cpu, msr, tj_max - dts, tj_max - dts2);
	पूर्ण

	वापस 0;
पूर्ण

व्योम prपूर्णांक_घातer_limit_msr(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ msr, अक्षर *label)
अणु
	ख_लिखो(outf, "cpu%d: %s: %sabled (%f Watts, %f sec, clamp %sabled)\n",
		cpu, label,
		((msr >> 15) & 1) ? "EN" : "DIS",
		((msr >> 0) & 0x7FFF) * rapl_घातer_units,
		(1.0 + (((msr >> 22) & 0x3) / 4.0)) * (1 << ((msr >> 17) & 0x1F)) * rapl_समय_units,
		(((msr >> 16) & 1) ? "EN" : "DIS"));

	वापस;
पूर्ण

पूर्णांक prपूर्णांक_rapl(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	स्थिर अक्षर *msr_name;
	पूर्णांक cpu;

	अगर (!करो_rapl)
		वापस 0;

	/* RAPL counters are per package, so prपूर्णांक only क्रम 1st thपढ़ो/package */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE) || !(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		वापस 0;

	cpu = t->cpu_id;
	अगर (cpu_migrate(cpu)) अणु
		ख_लिखो(outf, "print_rapl: Could not migrate to CPU %d\n", cpu);
		वापस -1;
	पूर्ण

	अगर (करो_rapl & RAPL_AMD_F17H) अणु
		msr_name = "MSR_RAPL_PWR_UNIT";
		अगर (get_msr(cpu, MSR_RAPL_PWR_UNIT, &msr))
			वापस -1;
	पूर्ण अन्यथा अणु
		msr_name = "MSR_RAPL_POWER_UNIT";
		अगर (get_msr(cpu, MSR_RAPL_POWER_UNIT, &msr))
			वापस -1;
	पूर्ण

	ख_लिखो(outf, "cpu%d: %s: 0x%08llx (%f Watts, %f Joules, %f sec.)\n", cpu, msr_name, msr,
		rapl_घातer_units, rapl_energy_units, rapl_समय_units);

	अगर (करो_rapl & RAPL_PKG_POWER_INFO) अणु

		अगर (get_msr(cpu, MSR_PKG_POWER_INFO, &msr))
			वापस -5;

		ख_लिखो(outf, "cpu%d: MSR_PKG_POWER_INFO: 0x%08llx (%.0f W TDP, RAPL %.0f - %.0f W, %f sec.)\n",
			cpu, msr,
			((msr >> 0) & RAPL_POWER_GRANULARITY) * rapl_घातer_units,
			((msr >> 16) & RAPL_POWER_GRANULARITY) * rapl_घातer_units,
			((msr >> 32) & RAPL_POWER_GRANULARITY) * rapl_घातer_units,
			((msr >> 48) & RAPL_TIME_GRANULARITY) * rapl_समय_units);

	पूर्ण
	अगर (करो_rapl & RAPL_PKG) अणु

		अगर (get_msr(cpu, MSR_PKG_POWER_LIMIT, &msr))
			वापस -9;

		ख_लिखो(outf, "cpu%d: MSR_PKG_POWER_LIMIT: 0x%08llx (%slocked)\n",
			cpu, msr, (msr >> 63) & 1 ? "" : "UN");

		prपूर्णांक_घातer_limit_msr(cpu, msr, "PKG Limit #1");
		ख_लिखो(outf, "cpu%d: PKG Limit #2: %sabled (%f Watts, %f* sec, clamp %sabled)\n",
			cpu,
			((msr >> 47) & 1) ? "EN" : "DIS",
			((msr >> 32) & 0x7FFF) * rapl_घातer_units,
			(1.0 + (((msr >> 54) & 0x3) / 4.0)) * (1 << ((msr >> 49) & 0x1F)) * rapl_समय_units,
			((msr >> 48) & 1) ? "EN" : "DIS");
	पूर्ण

	अगर (करो_rapl & RAPL_DRAM_POWER_INFO) अणु
		अगर (get_msr(cpu, MSR_DRAM_POWER_INFO, &msr))
			वापस -6;

		ख_लिखो(outf, "cpu%d: MSR_DRAM_POWER_INFO,: 0x%08llx (%.0f W TDP, RAPL %.0f - %.0f W, %f sec.)\n",
			cpu, msr,
			((msr >> 0) & RAPL_POWER_GRANULARITY) * rapl_घातer_units,
			((msr >> 16) & RAPL_POWER_GRANULARITY) * rapl_घातer_units,
			((msr >> 32) & RAPL_POWER_GRANULARITY) * rapl_घातer_units,
			((msr >> 48) & RAPL_TIME_GRANULARITY) * rapl_समय_units);
	पूर्ण
	अगर (करो_rapl & RAPL_DRAM) अणु
		अगर (get_msr(cpu, MSR_DRAM_POWER_LIMIT, &msr))
			वापस -9;
		ख_लिखो(outf, "cpu%d: MSR_DRAM_POWER_LIMIT: 0x%08llx (%slocked)\n",
			cpu, msr, (msr >> 31) & 1 ? "" : "UN");

		prपूर्णांक_घातer_limit_msr(cpu, msr, "DRAM Limit");
	पूर्ण
	अगर (करो_rapl & RAPL_CORE_POLICY) अणु
		अगर (get_msr(cpu, MSR_PP0_POLICY, &msr))
			वापस -7;

		ख_लिखो(outf, "cpu%d: MSR_PP0_POLICY: %lld\n", cpu, msr & 0xF);
	पूर्ण
	अगर (करो_rapl & RAPL_CORES_POWER_LIMIT) अणु
		अगर (get_msr(cpu, MSR_PP0_POWER_LIMIT, &msr))
			वापस -9;
		ख_लिखो(outf, "cpu%d: MSR_PP0_POWER_LIMIT: 0x%08llx (%slocked)\n",
			cpu, msr, (msr >> 31) & 1 ? "" : "UN");
		prपूर्णांक_घातer_limit_msr(cpu, msr, "Cores Limit");
	पूर्ण
	अगर (करो_rapl & RAPL_GFX) अणु
		अगर (get_msr(cpu, MSR_PP1_POLICY, &msr))
			वापस -8;

		ख_लिखो(outf, "cpu%d: MSR_PP1_POLICY: %lld\n", cpu, msr & 0xF);

		अगर (get_msr(cpu, MSR_PP1_POWER_LIMIT, &msr))
			वापस -9;
		ख_लिखो(outf, "cpu%d: MSR_PP1_POWER_LIMIT: 0x%08llx (%slocked)\n",
			cpu, msr, (msr >> 31) & 1 ? "" : "UN");
		prपूर्णांक_घातer_limit_msr(cpu, msr, "GFX Limit");
	पूर्ण
	वापस 0;
पूर्ण

/*
 * SNB adds support क्रम additional MSRs:
 *
 * MSR_PKG_C7_RESIDENCY            0x000003fa
 * MSR_CORE_C7_RESIDENCY           0x000003fe
 * MSR_PKG_C2_RESIDENCY            0x0000060d
 */

पूर्णांक has_snb_msrs(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_SANDYBRIDGE:
	हाल INTEL_FAM6_SANDYBRIDGE_X:
	हाल INTEL_FAM6_IVYBRIDGE:	/* IVB */
	हाल INTEL_FAM6_IVYBRIDGE_X:	/* IVB Xeon */
	हाल INTEL_FAM6_HASWELL:	/* HSW */
	हाल INTEL_FAM6_HASWELL_X:	/* HSW */
	हाल INTEL_FAM6_HASWELL_L:	/* HSW */
	हाल INTEL_FAM6_HASWELL_G:	/* HSW */
	हाल INTEL_FAM6_BROADWELL:	/* BDW */
	हाल INTEL_FAM6_BROADWELL_G:	/* BDW */
	हाल INTEL_FAM6_BROADWELL_X:	/* BDX */
	हाल INTEL_FAM6_SKYLAKE_L:	/* SKL */
	हाल INTEL_FAM6_CANNONLAKE_L:	/* CNL */
	हाल INTEL_FAM6_SKYLAKE_X:	/* SKX */
	हाल INTEL_FAM6_ICELAKE_X:	/* ICX */
	हाल INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
	हाल INTEL_FAM6_ATOM_GOLDMONT_D:	/* DNV */
	हाल INTEL_FAM6_ATOM_TREMONT:	/* EHL */
	हाल INTEL_FAM6_ATOM_TREMONT_D:	/* JVL */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * HSW ULT added support क्रम C8/C9/C10 MSRs:
 *
 * MSR_PKG_C8_RESIDENCY		0x00000630
 * MSR_PKG_C9_RESIDENCY		0x00000631
 * MSR_PKG_C10_RESIDENCY	0x00000632
 *
 * MSR_PKGC8_IRTL		0x00000633
 * MSR_PKGC9_IRTL		0x00000634
 * MSR_PKGC10_IRTL		0x00000635
 *
 */
पूर्णांक has_c8910_msrs(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_HASWELL_L:	/* HSW */
	हाल INTEL_FAM6_BROADWELL:	/* BDW */
	हाल INTEL_FAM6_SKYLAKE_L:	/* SKL */
	हाल INTEL_FAM6_CANNONLAKE_L:	/* CNL */
	हाल INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
	हाल INTEL_FAM6_ATOM_TREMONT:	/* EHL */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * SKL adds support क्रम additional MSRS:
 *
 * MSR_PKG_WEIGHTED_CORE_C0_RES    0x00000658
 * MSR_PKG_ANY_CORE_C0_RES         0x00000659
 * MSR_PKG_ANY_GFXE_C0_RES         0x0000065A
 * MSR_PKG_BOTH_CORE_GFXE_C0_RES   0x0000065B
 */
पूर्णांक has_skl_msrs(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_SKYLAKE_L:	/* SKL */
	हाल INTEL_FAM6_CANNONLAKE_L:	/* CNL */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_slm(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;
	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_SILVERMONT:	/* BYT */
	हाल INTEL_FAM6_ATOM_SILVERMONT_D:	/* AVN */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_knl(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;
	चयन (model) अणु
	हाल INTEL_FAM6_XEON_PHI_KNL:	/* KNL */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक is_cnl(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (!genuine_पूर्णांकel)
		वापस 0;

	चयन (model) अणु
	हाल INTEL_FAM6_CANNONLAKE_L:	/* CNL */
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक get_aperf_mperf_multiplier(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (is_knl(family, model))
		वापस 1024;
	वापस 1;
पूर्ण

#घोषणा SLM_BCLK_FREQS 5
द्विगुन slm_freq_table[SLM_BCLK_FREQS] = अणु 83.3, 100.0, 133.3, 116.7, 80.0 पूर्ण;

द्विगुन slm_bclk(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr = 3;
	अचिन्हित पूर्णांक i;
	द्विगुन freq;

	अगर (get_msr(base_cpu, MSR_FSB_FREQ, &msr))
		ख_लिखो(outf, "SLM BCLK: unknown\n");

	i = msr & 0xf;
	अगर (i >= SLM_BCLK_FREQS) अणु
		ख_लिखो(outf, "SLM BCLK[%d] invalid\n", i);
		i = 3;
	पूर्ण
	freq = slm_freq_table[i];

	अगर (!quiet)
		ख_लिखो(outf, "SLM BCLK: %.1f Mhz\n", freq);

	वापस freq;
पूर्ण

द्विगुन discover_bclk(अचिन्हित पूर्णांक family, अचिन्हित पूर्णांक model)
अणु
	अगर (has_snb_msrs(family, model) || is_knl(family, model))
		वापस 100.00;
	अन्यथा अगर (is_slm(family, model))
		वापस slm_bclk();
	अन्यथा
		वापस 133.33;
पूर्ण

पूर्णांक get_cpu_type(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	अगर (!genuine_पूर्णांकel)
		वापस 0;

	अगर (cpu_migrate(t->cpu_id)) अणु
		ख_लिखो(outf, "Could not migrate to CPU %d\n", t->cpu_id);
		वापस -1;
	पूर्ण

	अगर (max_level < 0x1a)
		वापस 0;

	__cpuid(0x1a, eax, ebx, ecx, edx);
	eax = (eax >> 24) & 0xFF;
	अगर (eax == 0x20)
		t->is_atom = true;
	वापस 0;
पूर्ण

/*
 * MSR_IA32_TEMPERATURE_TARGET indicates the temperature where
 * the Thermal Control Circuit (TCC) activates.
 * This is usually equal to tjMax.
 *
 * Older processors करो not have this MSR, so there we guess,
 * but also allow cmdline over-ride with -T.
 *
 * Several MSR temperature values are in units of degrees-C
 * below this value, including the Digital Thermal Sensor (DTS),
 * Package Thermal Management Sensor (PTM), and thermal event thresholds.
 */
पूर्णांक set_temperature_target(काष्ठा thपढ़ो_data *t, काष्ठा core_data *c, काष्ठा pkg_data *p)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक tcc_शेष, tcc_offset;
	पूर्णांक cpu;

	/* tj_max is used only क्रम dts or pपंचांग */
	अगर (!(करो_dts || करो_pपंचांग))
		वापस 0;

	/* this is a per-package concept */
	अगर (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE) || !(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		वापस 0;

	cpu = t->cpu_id;
	अगर (cpu_migrate(cpu)) अणु
		ख_लिखो(outf, "Could not migrate to CPU %d\n", cpu);
		वापस -1;
	पूर्ण

	अगर (tj_max_override != 0) अणु
		tj_max = tj_max_override;
		ख_लिखो(outf, "cpu%d: Using cmdline TCC Target (%d C)\n", cpu, tj_max);
		वापस 0;
	पूर्ण

	/* Temperature Target MSR is Nehalem and newer only */
	अगर (!करो_nhm_platक्रमm_info)
		जाओ guess;

	अगर (get_msr(base_cpu, MSR_IA32_TEMPERATURE_TARGET, &msr))
		जाओ guess;

	tcc_शेष = (msr >> 16) & 0xFF;

	अगर (!quiet) अणु
		चयन (tcc_offset_bits) अणु
		हाल 4:
			tcc_offset = (msr >> 24) & 0xF;
			ख_लिखो(outf, "cpu%d: MSR_IA32_TEMPERATURE_TARGET: 0x%08llx (%d C) (%d default - %d offset)\n",
				cpu, msr, tcc_शेष - tcc_offset, tcc_शेष, tcc_offset);
			अवरोध;
		हाल 6:
			tcc_offset = (msr >> 24) & 0x3F;
			ख_लिखो(outf, "cpu%d: MSR_IA32_TEMPERATURE_TARGET: 0x%08llx (%d C) (%d default - %d offset)\n",
				cpu, msr, tcc_शेष - tcc_offset, tcc_शेष, tcc_offset);
			अवरोध;
		शेष:
			ख_लिखो(outf, "cpu%d: MSR_IA32_TEMPERATURE_TARGET: 0x%08llx (%d C)\n", cpu, msr, tcc_शेष);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tcc_शेष)
		जाओ guess;

	tj_max = tcc_शेष;

	वापस 0;

guess:
	tj_max = TJMAX_DEFAULT;
	ख_लिखो(outf, "cpu%d: Guessing tjMax %d C, Please use -T to specify\n", cpu, tj_max);

	वापस 0;
पूर्ण

व्योम decode_feature_control_msr(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (!get_msr(base_cpu, MSR_IA32_FEAT_CTL, &msr))
		ख_लिखो(outf, "cpu%d: MSR_IA32_FEATURE_CONTROL: 0x%08llx (%sLocked %s)\n",
			base_cpu, msr, msr & FEAT_CTL_LOCKED ? "" : "UN-", msr & (1 << 18) ? "SGX" : "");
पूर्ण

व्योम decode_misc_enable_msr(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (!genuine_पूर्णांकel)
		वापस;

	अगर (!get_msr(base_cpu, MSR_IA32_MISC_ENABLE, &msr))
		ख_लिखो(outf, "cpu%d: MSR_IA32_MISC_ENABLE: 0x%08llx (%sTCC %sEIST %sMWAIT %sPREFETCH %sTURBO)\n",
			base_cpu, msr,
			msr & MSR_IA32_MISC_ENABLE_TM1 ? "" : "No-",
			msr & MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP ? "" : "No-",
			msr & MSR_IA32_MISC_ENABLE_MWAIT ? "" : "No-",
			msr & MSR_IA32_MISC_ENABLE_PREFETCH_DISABLE ? "No-" : "",
			msr & MSR_IA32_MISC_ENABLE_TURBO_DISABLE ? "No-" : "");
पूर्ण

व्योम decode_misc_feature_control(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (!has_misc_feature_control)
		वापस;

	अगर (!get_msr(base_cpu, MSR_MISC_FEATURE_CONTROL, &msr))
		ख_लिखो(outf,
			"cpu%d: MSR_MISC_FEATURE_CONTROL: 0x%08llx (%sL2-Prefetch %sL2-Prefetch-pair %sL1-Prefetch %sL1-IP-Prefetch)\n",
			base_cpu, msr, msr & (0 << 0) ? "No-" : "", msr & (1 << 0) ? "No-" : "",
			msr & (2 << 0) ? "No-" : "", msr & (3 << 0) ? "No-" : "");
पूर्ण

/*
 * Decode MSR_MISC_PWR_MGMT
 *
 * Decode the bits according to the Nehalem करोcumentation
 * bit[0] seems to जारी to have same meaning going क्रमward
 * bit[1] less so...
 */
व्योम decode_misc_pwr_mgmt_msr(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (!करो_nhm_platक्रमm_info)
		वापस;

	अगर (no_MSR_MISC_PWR_MGMT)
		वापस;

	अगर (!get_msr(base_cpu, MSR_MISC_PWR_MGMT, &msr))
		ख_लिखो(outf, "cpu%d: MSR_MISC_PWR_MGMT: 0x%08llx (%sable-EIST_Coordination %sable-EPB %sable-OOB)\n",
			base_cpu, msr,
			msr & (1 << 0) ? "DIS" : "EN", msr & (1 << 1) ? "EN" : "DIS", msr & (1 << 8) ? "EN" : "DIS");
पूर्ण

/*
 * Decode MSR_CC6_DEMOTION_POLICY_CONFIG, MSR_MC6_DEMOTION_POLICY_CONFIG
 *
 * This MSRs are present on Silvermont processors,
 * Intel Atom processor E3000 series (Baytrail), and मित्रs.
 */
व्योम decode_c6_demotion_policy_msr(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (!get_msr(base_cpu, MSR_CC6_DEMOTION_POLICY_CONFIG, &msr))
		ख_लिखो(outf, "cpu%d: MSR_CC6_DEMOTION_POLICY_CONFIG: 0x%08llx (%sable-CC6-Demotion)\n",
			base_cpu, msr, msr & (1 << 0) ? "EN" : "DIS");

	अगर (!get_msr(base_cpu, MSR_MC6_DEMOTION_POLICY_CONFIG, &msr))
		ख_लिखो(outf, "cpu%d: MSR_MC6_DEMOTION_POLICY_CONFIG: 0x%08llx (%sable-MC6-Demotion)\n",
			base_cpu, msr, msr & (1 << 0) ? "EN" : "DIS");
पूर्ण

/*
 * When models are the same, क्रम the purpose of turbostat, reuse
 */
अचिन्हित पूर्णांक पूर्णांकel_model_duplicates(अचिन्हित पूर्णांक model)
अणु

	चयन (model) अणु
	हाल INTEL_FAM6_NEHALEM_EP:	/* Core i7, Xeon 5500 series - Bloomfield, Gainstown NHM-EP */
	हाल INTEL_FAM6_NEHALEM:	/* Core i7 and i5 Processor - Clarksfield, Lynnfield, Jasper Forest */
	हाल 0x1F:		/* Core i7 and i5 Processor - Nehalem */
	हाल INTEL_FAM6_WESTMERE:	/* Wesपंचांगere Client - Clarkdale, Arअक्रमale */
	हाल INTEL_FAM6_WESTMERE_EP:	/* Wesपंचांगere EP - Gulftown */
		वापस INTEL_FAM6_NEHALEM;

	हाल INTEL_FAM6_NEHALEM_EX:	/* Nehalem-EX Xeon - Beckton */
	हाल INTEL_FAM6_WESTMERE_EX:	/* Wesपंचांगere-EX Xeon - Eagleton */
		वापस INTEL_FAM6_NEHALEM_EX;

	हाल INTEL_FAM6_XEON_PHI_KNM:
		वापस INTEL_FAM6_XEON_PHI_KNL;

	हाल INTEL_FAM6_BROADWELL_X:
	हाल INTEL_FAM6_BROADWELL_D:	/* BDX-DE */
		वापस INTEL_FAM6_BROADWELL_X;

	हाल INTEL_FAM6_SKYLAKE_L:
	हाल INTEL_FAM6_SKYLAKE:
	हाल INTEL_FAM6_KABYLAKE_L:
	हाल INTEL_FAM6_KABYLAKE:
	हाल INTEL_FAM6_COMETLAKE_L:
	हाल INTEL_FAM6_COMETLAKE:
		वापस INTEL_FAM6_SKYLAKE_L;

	हाल INTEL_FAM6_ICELAKE_L:
	हाल INTEL_FAM6_ICELAKE_NNPI:
	हाल INTEL_FAM6_TIGERLAKE_L:
	हाल INTEL_FAM6_TIGERLAKE:
	हाल INTEL_FAM6_ROCKETLAKE:
	हाल INTEL_FAM6_LAKEFIELD:
	हाल INTEL_FAM6_ALDERLAKE:
	हाल INTEL_FAM6_ALDERLAKE_L:
		वापस INTEL_FAM6_CANNONLAKE_L;

	हाल INTEL_FAM6_ATOM_TREMONT_L:
		वापस INTEL_FAM6_ATOM_TREMONT;

	हाल INTEL_FAM6_ICELAKE_D:
	हाल INTEL_FAM6_SAPPHIRERAPIDS_X:
		वापस INTEL_FAM6_ICELAKE_X;
	पूर्ण
	वापस model;
पूर्ण

व्योम prपूर्णांक_dev_latency(व्योम)
अणु
	अक्षर *path = "/dev/cpu_dma_latency";
	पूर्णांक fd;
	पूर्णांक value;
	पूर्णांक retval;

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0) अणु
		warn("fopen %s\n", path);
		वापस;
	पूर्ण

	retval = पढ़ो(fd, (व्योम *)&value, माप(पूर्णांक));
	अगर (retval != माप(पूर्णांक)) अणु
		warn("read %s\n", path);
		बंद(fd);
		वापस;
	पूर्ण
	ख_लिखो(outf, "/dev/cpu_dma_latency: %d usec (%s)\n", value, value == 2000000000 ? "default" : "constrained");

	बंद(fd);
पूर्ण

/*
 * Linux-perf manages the the HW inकाष्ठाions-retired counter
 * by enabling when requested, and hiding rollover
 */
व्योम linux_perf_init(व्योम)
अणु
	अगर (!BIC_IS_ENABLED(BIC_IPC))
		वापस;

	अगर (access("/proc/sys/kernel/perf_event_paranoid", F_OK))
		वापस;

	fd_instr_count_percpu = सुस्मृति(topo.max_cpu_num + 1, माप(पूर्णांक));
	अगर (fd_instr_count_percpu == शून्य)
		err(-1, "calloc fd_instr_count_percpu");

	BIC_PRESENT(BIC_IPC);
पूर्ण

व्योम process_cpuid()
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अचिन्हित पूर्णांक fms, family, model, stepping, ecx_flags, edx_flags;
	अचिन्हित पूर्णांक has_turbo;
	अचिन्हित दीर्घ दीर्घ ucode_patch = 0;

	eax = ebx = ecx = edx = 0;

	__cpuid(0, max_level, ebx, ecx, edx);

	अगर (ebx == 0x756e6547 && ecx == 0x6c65746e && edx == 0x49656e69)
		genuine_पूर्णांकel = 1;
	अन्यथा अगर (ebx == 0x68747541 && ecx == 0x444d4163 && edx == 0x69746e65)
		authentic_amd = 1;
	अन्यथा अगर (ebx == 0x6f677948 && ecx == 0x656e6975 && edx == 0x6e65476e)
		hygon_genuine = 1;

	अगर (!quiet)
		ख_लिखो(outf, "CPUID(0): %.4s%.4s%.4s 0x%x CPUID levels\n",
			(अक्षर *)&ebx, (अक्षर *)&edx, (अक्षर *)&ecx, max_level);

	__cpuid(1, fms, ebx, ecx, edx);
	family = (fms >> 8) & 0xf;
	model = (fms >> 4) & 0xf;
	stepping = fms & 0xf;
	अगर (family == 0xf)
		family += (fms >> 20) & 0xff;
	अगर (family >= 6)
		model += ((fms >> 16) & 0xf) << 4;
	ecx_flags = ecx;
	edx_flags = edx;

	अगर (get_msr(sched_अ_लोpu(), MSR_IA32_UCODE_REV, &ucode_patch))
		warnx("get_msr(UCODE)\n");

	/*
	 * check max extended function levels of CPUID.
	 * This is needed to check क्रम invariant TSC.
	 * This check is valid क्रम both Intel and AMD.
	 */
	ebx = ecx = edx = 0;
	__cpuid(0x80000000, max_extended_level, ebx, ecx, edx);

	अगर (!quiet) अणु
		ख_लिखो(outf, "CPUID(1): family:model:stepping 0x%x:%x:%x (%d:%d:%d) microcode 0x%x\n",
			family, model, stepping, family, model, stepping,
			(अचिन्हित पूर्णांक)((ucode_patch >> 32) & 0xFFFFFFFF));
		ख_लिखो(outf, "CPUID(0x80000000): max_extended_levels: 0x%x\n", max_extended_level);
		ख_लिखो(outf, "CPUID(1): %s %s %s %s %s %s %s %s %s %s\n",
			ecx_flags & (1 << 0) ? "SSE3" : "-",
			ecx_flags & (1 << 3) ? "MONITOR" : "-",
			ecx_flags & (1 << 6) ? "SMX" : "-",
			ecx_flags & (1 << 7) ? "EIST" : "-",
			ecx_flags & (1 << 8) ? "TM2" : "-",
			edx_flags & (1 << 4) ? "TSC" : "-",
			edx_flags & (1 << 5) ? "MSR" : "-",
			edx_flags & (1 << 22) ? "ACPI-TM" : "-",
			edx_flags & (1 << 28) ? "HT" : "-", edx_flags & (1 << 29) ? "TM" : "-");
	पूर्ण
	अगर (genuine_पूर्णांकel) अणु
		model_orig = model;
		model = पूर्णांकel_model_duplicates(model);
	पूर्ण

	अगर (!(edx_flags & (1 << 5)))
		errx(1, "CPUID: no MSR");

	अगर (max_extended_level >= 0x80000007) अणु

		/*
		 * Non-Stop TSC is advertised by CPUID.EAX=0x80000007: EDX.bit8
		 * this check is valid क्रम both Intel and AMD
		 */
		__cpuid(0x80000007, eax, ebx, ecx, edx);
		has_invariant_tsc = edx & (1 << 8);
	पूर्ण

	/*
	 * APERF/MPERF is advertised by CPUID.EAX=0x6: ECX.bit0
	 * this check is valid क्रम both Intel and AMD
	 */

	__cpuid(0x6, eax, ebx, ecx, edx);
	has_aperf = ecx & (1 << 0);
	अगर (has_aperf) अणु
		BIC_PRESENT(BIC_Avg_MHz);
		BIC_PRESENT(BIC_Busy);
		BIC_PRESENT(BIC_Bzy_MHz);
	पूर्ण
	करो_dts = eax & (1 << 0);
	अगर (करो_dts)
		BIC_PRESENT(BIC_CoreTmp);
	has_turbo = eax & (1 << 1);
	करो_pपंचांग = eax & (1 << 6);
	अगर (करो_pपंचांग)
		BIC_PRESENT(BIC_PkgTmp);
	has_hwp = eax & (1 << 7);
	has_hwp_notअगरy = eax & (1 << 8);
	has_hwp_activity_winकरोw = eax & (1 << 9);
	has_hwp_epp = eax & (1 << 10);
	has_hwp_pkg = eax & (1 << 11);
	has_epb = ecx & (1 << 3);

	अगर (!quiet)
		ख_लिखो(outf, "CPUID(6): %sAPERF, %sTURBO, %sDTS, %sPTM, %sHWP, "
			"%sHWPnotify, %sHWPwindow, %sHWPepp, %sHWPpkg, %sEPB\n",
			has_aperf ? "" : "No-",
			has_turbo ? "" : "No-",
			करो_dts ? "" : "No-",
			करो_pपंचांग ? "" : "No-",
			has_hwp ? "" : "No-",
			has_hwp_notअगरy ? "" : "No-",
			has_hwp_activity_winकरोw ? "" : "No-",
			has_hwp_epp ? "" : "No-", has_hwp_pkg ? "" : "No-", has_epb ? "" : "No-");

	अगर (!quiet)
		decode_misc_enable_msr();

	अगर (max_level >= 0x7 && !quiet) अणु
		पूर्णांक has_sgx;

		ecx = 0;

		__cpuid_count(0x7, 0, eax, ebx, ecx, edx);

		has_sgx = ebx & (1 << 2);
		ख_लिखो(outf, "CPUID(7): %sSGX\n", has_sgx ? "" : "No-");

		अगर (has_sgx)
			decode_feature_control_msr();
	पूर्ण

	अगर (max_level >= 0x15) अणु
		अचिन्हित पूर्णांक eax_crystal;
		अचिन्हित पूर्णांक ebx_tsc;

		/*
		 * CPUID 15H TSC/Crystal ratio, possibly Crystal Hz
		 */
		eax_crystal = ebx_tsc = crystal_hz = edx = 0;
		__cpuid(0x15, eax_crystal, ebx_tsc, crystal_hz, edx);

		अगर (ebx_tsc != 0) अणु

			अगर (!quiet && (ebx != 0))
				ख_लिखो(outf, "CPUID(0x15): eax_crystal: %d ebx_tsc: %d ecx_crystal_hz: %d\n",
					eax_crystal, ebx_tsc, crystal_hz);

			अगर (crystal_hz == 0)
				चयन (model) अणु
				हाल INTEL_FAM6_SKYLAKE_L:	/* SKL */
					crystal_hz = 24000000;	/* 24.0 MHz */
					अवरोध;
				हाल INTEL_FAM6_ATOM_GOLDMONT_D:	/* DNV */
					crystal_hz = 25000000;	/* 25.0 MHz */
					अवरोध;
				हाल INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
				हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
					crystal_hz = 19200000;	/* 19.2 MHz */
					अवरोध;
				शेष:
					crystal_hz = 0;
				पूर्ण

			अगर (crystal_hz) अणु
				tsc_hz = (अचिन्हित दीर्घ दीर्घ)crystal_hz *ebx_tsc / eax_crystal;
				अगर (!quiet)
					ख_लिखो(outf, "TSC: %lld MHz (%d Hz * %d / %d / 1000000)\n",
						tsc_hz / 1000000, crystal_hz, ebx_tsc, eax_crystal);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (max_level >= 0x16) अणु
		अचिन्हित पूर्णांक base_mhz, max_mhz, bus_mhz, edx;

		/*
		 * CPUID 16H Base MHz, Max MHz, Bus MHz
		 */
		base_mhz = max_mhz = bus_mhz = edx = 0;

		__cpuid(0x16, base_mhz, max_mhz, bus_mhz, edx);
		अगर (!quiet)
			ख_लिखो(outf, "CPUID(0x16): base_mhz: %d max_mhz: %d bus_mhz: %d\n",
				base_mhz, max_mhz, bus_mhz);
	पूर्ण

	अगर (has_aperf)
		aperf_mperf_multiplier = get_aperf_mperf_multiplier(family, model);

	BIC_PRESENT(BIC_IRQ);
	BIC_PRESENT(BIC_TSC_MHz);

	अगर (probe_nhm_msrs(family, model)) अणु
		करो_nhm_platक्रमm_info = 1;
		BIC_PRESENT(BIC_CPU_c1);
		BIC_PRESENT(BIC_CPU_c3);
		BIC_PRESENT(BIC_CPU_c6);
		BIC_PRESENT(BIC_SMI);
	पूर्ण
	करो_snb_cstates = has_snb_msrs(family, model);

	अगर (करो_snb_cstates)
		BIC_PRESENT(BIC_CPU_c7);

	करो_irtl_snb = has_snb_msrs(family, model);
	अगर (करो_snb_cstates && (pkg_cstate_limit >= PCL__2))
		BIC_PRESENT(BIC_Pkgpc2);
	अगर (pkg_cstate_limit >= PCL__3)
		BIC_PRESENT(BIC_Pkgpc3);
	अगर (pkg_cstate_limit >= PCL__6)
		BIC_PRESENT(BIC_Pkgpc6);
	अगर (करो_snb_cstates && (pkg_cstate_limit >= PCL__7))
		BIC_PRESENT(BIC_Pkgpc7);
	अगर (has_slv_msrs(family, model)) अणु
		BIC_NOT_PRESENT(BIC_Pkgpc2);
		BIC_NOT_PRESENT(BIC_Pkgpc3);
		BIC_PRESENT(BIC_Pkgpc6);
		BIC_NOT_PRESENT(BIC_Pkgpc7);
		BIC_PRESENT(BIC_Mod_c6);
		use_c1_residency_msr = 1;
	पूर्ण
	अगर (is_jvl(family, model)) अणु
		BIC_NOT_PRESENT(BIC_CPU_c3);
		BIC_NOT_PRESENT(BIC_CPU_c7);
		BIC_NOT_PRESENT(BIC_Pkgpc2);
		BIC_NOT_PRESENT(BIC_Pkgpc3);
		BIC_NOT_PRESENT(BIC_Pkgpc6);
		BIC_NOT_PRESENT(BIC_Pkgpc7);
	पूर्ण
	अगर (is_dnv(family, model)) अणु
		BIC_PRESENT(BIC_CPU_c1);
		BIC_NOT_PRESENT(BIC_CPU_c3);
		BIC_NOT_PRESENT(BIC_Pkgpc3);
		BIC_NOT_PRESENT(BIC_CPU_c7);
		BIC_NOT_PRESENT(BIC_Pkgpc7);
		use_c1_residency_msr = 1;
	पूर्ण
	अगर (is_skx(family, model) || is_icx(family, model)) अणु
		BIC_NOT_PRESENT(BIC_CPU_c3);
		BIC_NOT_PRESENT(BIC_Pkgpc3);
		BIC_NOT_PRESENT(BIC_CPU_c7);
		BIC_NOT_PRESENT(BIC_Pkgpc7);
	पूर्ण
	अगर (is_bdx(family, model)) अणु
		BIC_NOT_PRESENT(BIC_CPU_c7);
		BIC_NOT_PRESENT(BIC_Pkgpc7);
	पूर्ण
	अगर (has_c8910_msrs(family, model)) अणु
		अगर (pkg_cstate_limit >= PCL__8)
			BIC_PRESENT(BIC_Pkgpc8);
		अगर (pkg_cstate_limit >= PCL__9)
			BIC_PRESENT(BIC_Pkgpc9);
		अगर (pkg_cstate_limit >= PCL_10)
			BIC_PRESENT(BIC_Pkgpc10);
	पूर्ण
	करो_irtl_hsw = has_c8910_msrs(family, model);
	अगर (has_skl_msrs(family, model)) अणु
		BIC_PRESENT(BIC_Totl_c0);
		BIC_PRESENT(BIC_Any_c0);
		BIC_PRESENT(BIC_GFX_c0);
		BIC_PRESENT(BIC_CPUGFX);
	पूर्ण
	करो_slm_cstates = is_slm(family, model);
	करो_knl_cstates = is_knl(family, model);

	अगर (करो_slm_cstates || करो_knl_cstates || is_cnl(family, model) || is_ehl(family, model))
		BIC_NOT_PRESENT(BIC_CPU_c3);

	अगर (!quiet)
		decode_misc_pwr_mgmt_msr();

	अगर (!quiet && has_slv_msrs(family, model))
		decode_c6_demotion_policy_msr();

	rapl_probe(family, model);
	perf_limit_reasons_probe(family, model);
	स्वतःmatic_cstate_conversion_probe(family, model);

	check_tcc_offset(model_orig);

	अगर (!quiet)
		dump_cstate_pstate_config_info(family, model);

	अगर (!quiet)
		prपूर्णांक_dev_latency();
	अगर (!quiet)
		dump_sysfs_cstate_config();
	अगर (!quiet)
		dump_sysfs_pstate_config();

	अगर (has_skl_msrs(family, model) || is_ehl(family, model))
		calculate_tsc_tweak();

	अगर (!access("/sys/class/drm/card0/power/rc6_residency_ms", R_OK))
		BIC_PRESENT(BIC_GFX_rc6);

	अगर (!access("/sys/class/graphics/fb0/device/drm/card0/gt_cur_freq_mhz", R_OK))
		BIC_PRESENT(BIC_GFXMHz);

	अगर (!access("/sys/class/graphics/fb0/device/drm/card0/gt_act_freq_mhz", R_OK))
		BIC_PRESENT(BIC_GFXACTMHz);

	अगर (!access("/sys/devices/system/cpu/cpuidle/low_power_idle_cpu_residency_us", R_OK))
		BIC_PRESENT(BIC_CPU_LPI);
	अन्यथा
		BIC_NOT_PRESENT(BIC_CPU_LPI);

	अगर (!access(sys_lpi_file_sysfs, R_OK)) अणु
		sys_lpi_file = sys_lpi_file_sysfs;
		BIC_PRESENT(BIC_SYS_LPI);
	पूर्ण अन्यथा अगर (!access(sys_lpi_file_debugfs, R_OK)) अणु
		sys_lpi_file = sys_lpi_file_debugfs;
		BIC_PRESENT(BIC_SYS_LPI);
	पूर्ण अन्यथा अणु
		sys_lpi_file_sysfs = शून्य;
		BIC_NOT_PRESENT(BIC_SYS_LPI);
	पूर्ण

	अगर (!quiet)
		decode_misc_feature_control();

	वापस;
पूर्ण

/*
 * in /dev/cpu/ वापस success क्रम names that are numbers
 * ie. filter out ".", "..", "microcode".
 */
पूर्णांक dir_filter(स्थिर काष्ठा dirent *dirp)
अणु
	अगर (है_अंक(dirp->d_name[0]))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक खोलो_dev_cpu_msr(पूर्णांक dummy1)
अणु
	वापस 0;
पूर्ण

व्योम topology_probe()
अणु
	पूर्णांक i;
	पूर्णांक max_core_id = 0;
	पूर्णांक max_package_id = 0;
	पूर्णांक max_die_id = 0;
	पूर्णांक max_siblings = 0;

	/* Initialize num_cpus, max_cpu_num */
	set_max_cpu_num();
	topo.num_cpus = 0;
	क्रम_all_proc_cpus(count_cpus);
	अगर (!summary_only && topo.num_cpus > 1)
		BIC_PRESENT(BIC_CPU);

	अगर (debug > 1)
		ख_लिखो(outf, "num_cpus %d max_cpu_num %d\n", topo.num_cpus, topo.max_cpu_num);

	cpus = सुस्मृति(1, (topo.max_cpu_num + 1) * माप(काष्ठा cpu_topology));
	अगर (cpus == शून्य)
		err(1, "calloc cpus");

	/*
	 * Allocate and initialize cpu_present_set
	 */
	cpu_present_set = CPU_ALLOC((topo.max_cpu_num + 1));
	अगर (cpu_present_set == शून्य)
		err(3, "CPU_ALLOC");
	cpu_present_setsize = CPU_ALLOC_SIZE((topo.max_cpu_num + 1));
	CPU_ZERO_S(cpu_present_setsize, cpu_present_set);
	क्रम_all_proc_cpus(mark_cpu_present);

	/*
	 * Validate that all cpus in cpu_subset are also in cpu_present_set
	 */
	क्रम (i = 0; i < CPU_SUBSET_MAXCPUS; ++i) अणु
		अगर (CPU_ISSET_S(i, cpu_subset_size, cpu_subset))
			अगर (!CPU_ISSET_S(i, cpu_present_setsize, cpu_present_set))
				err(1, "cpu%d not present", i);
	पूर्ण

	/*
	 * Allocate and initialize cpu_affinity_set
	 */
	cpu_affinity_set = CPU_ALLOC((topo.max_cpu_num + 1));
	अगर (cpu_affinity_set == शून्य)
		err(3, "CPU_ALLOC");
	cpu_affinity_setsize = CPU_ALLOC_SIZE((topo.max_cpu_num + 1));
	CPU_ZERO_S(cpu_affinity_setsize, cpu_affinity_set);

	क्रम_all_proc_cpus(init_thपढ़ो_id);

	/*
	 * For online cpus
	 * find max_core_id, max_package_id
	 */
	क्रम (i = 0; i <= topo.max_cpu_num; ++i) अणु
		पूर्णांक siblings;

		अगर (cpu_is_not_present(i)) अणु
			अगर (debug > 1)
				ख_लिखो(outf, "cpu%d NOT PRESENT\n", i);
			जारी;
		पूर्ण

		cpus[i].logical_cpu_id = i;

		/* get package inक्रमmation */
		cpus[i].physical_package_id = get_physical_package_id(i);
		अगर (cpus[i].physical_package_id > max_package_id)
			max_package_id = cpus[i].physical_package_id;

		/* get die inक्रमmation */
		cpus[i].die_id = get_die_id(i);
		अगर (cpus[i].die_id > max_die_id)
			max_die_id = cpus[i].die_id;

		/* get numa node inक्रमmation */
		cpus[i].physical_node_id = get_physical_node_id(&cpus[i]);
		अगर (cpus[i].physical_node_id > topo.max_node_num)
			topo.max_node_num = cpus[i].physical_node_id;

		/* get core inक्रमmation */
		cpus[i].physical_core_id = get_core_id(i);
		अगर (cpus[i].physical_core_id > max_core_id)
			max_core_id = cpus[i].physical_core_id;

		/* get thपढ़ो inक्रमmation */
		siblings = get_thपढ़ो_siblings(&cpus[i]);
		अगर (siblings > max_siblings)
			max_siblings = siblings;
		अगर (cpus[i].thपढ़ो_id == 0)
			topo.num_cores++;
	पूर्ण

	topo.cores_per_node = max_core_id + 1;
	अगर (debug > 1)
		ख_लिखो(outf, "max_core_id %d, sizing for %d cores per package\n", max_core_id, topo.cores_per_node);
	अगर (!summary_only && topo.cores_per_node > 1)
		BIC_PRESENT(BIC_Core);

	topo.num_die = max_die_id + 1;
	अगर (debug > 1)
		ख_लिखो(outf, "max_die_id %d, sizing for %d die\n", max_die_id, topo.num_die);
	अगर (!summary_only && topo.num_die > 1)
		BIC_PRESENT(BIC_Die);

	topo.num_packages = max_package_id + 1;
	अगर (debug > 1)
		ख_लिखो(outf, "max_package_id %d, sizing for %d packages\n", max_package_id, topo.num_packages);
	अगर (!summary_only && topo.num_packages > 1)
		BIC_PRESENT(BIC_Package);

	set_node_data();
	अगर (debug > 1)
		ख_लिखो(outf, "nodes_per_pkg %d\n", topo.nodes_per_pkg);
	अगर (!summary_only && topo.nodes_per_pkg > 1)
		BIC_PRESENT(BIC_Node);

	topo.thपढ़ोs_per_core = max_siblings;
	अगर (debug > 1)
		ख_लिखो(outf, "max_siblings %d\n", max_siblings);

	अगर (debug < 1)
		वापस;

	क्रम (i = 0; i <= topo.max_cpu_num; ++i) अणु
		अगर (cpu_is_not_present(i))
			जारी;
		ख_लिखो(outf,
			"cpu %d pkg %d die %d node %d lnode %d core %d thread %d\n",
			i, cpus[i].physical_package_id, cpus[i].die_id,
			cpus[i].physical_node_id, cpus[i].logical_node_id, cpus[i].physical_core_id, cpus[i].thपढ़ो_id);
	पूर्ण

पूर्ण

व्योम allocate_counters(काष्ठा thपढ़ो_data **t, काष्ठा core_data **c, काष्ठा pkg_data **p)
अणु
	पूर्णांक i;
	पूर्णांक num_cores = topo.cores_per_node * topo.nodes_per_pkg * topo.num_packages;
	पूर्णांक num_thपढ़ोs = topo.thपढ़ोs_per_core * num_cores;

	*t = सुस्मृति(num_thपढ़ोs, माप(काष्ठा thपढ़ो_data));
	अगर (*t == शून्य)
		जाओ error;

	क्रम (i = 0; i < num_thपढ़ोs; i++)
		(*t)[i].cpu_id = -1;

	*c = सुस्मृति(num_cores, माप(काष्ठा core_data));
	अगर (*c == शून्य)
		जाओ error;

	क्रम (i = 0; i < num_cores; i++)
		(*c)[i].core_id = -1;

	*p = सुस्मृति(topo.num_packages, माप(काष्ठा pkg_data));
	अगर (*p == शून्य)
		जाओ error;

	क्रम (i = 0; i < topo.num_packages; i++)
		(*p)[i].package_id = i;

	वापस;
error:
	err(1, "calloc counters");
पूर्ण

/*
 * init_counter()
 *
 * set FIRST_THREAD_IN_CORE and FIRST_CORE_IN_PACKAGE
 */
व्योम init_counter(काष्ठा thपढ़ो_data *thपढ़ो_base, काष्ठा core_data *core_base, काष्ठा pkg_data *pkg_base, पूर्णांक cpu_id)
अणु
	पूर्णांक pkg_id = cpus[cpu_id].physical_package_id;
	पूर्णांक node_id = cpus[cpu_id].logical_node_id;
	पूर्णांक core_id = cpus[cpu_id].physical_core_id;
	पूर्णांक thपढ़ो_id = cpus[cpu_id].thपढ़ो_id;
	काष्ठा thपढ़ो_data *t;
	काष्ठा core_data *c;
	काष्ठा pkg_data *p;

	/* Workaround क्रम प्रणालीs where physical_node_id==-1
	 * and logical_node_id==(-1 - topo.num_cpus)
	 */
	अगर (node_id < 0)
		node_id = 0;

	t = GET_THREAD(thपढ़ो_base, thपढ़ो_id, core_id, node_id, pkg_id);
	c = GET_CORE(core_base, core_id, node_id, pkg_id);
	p = GET_PKG(pkg_base, pkg_id);

	t->cpu_id = cpu_id;
	अगर (thपढ़ो_id == 0) अणु
		t->flags |= CPU_IS_FIRST_THREAD_IN_CORE;
		अगर (cpu_is_first_core_in_package(cpu_id))
			t->flags |= CPU_IS_FIRST_CORE_IN_PACKAGE;
	पूर्ण

	c->core_id = core_id;
	p->package_id = pkg_id;
पूर्ण

पूर्णांक initialize_counters(पूर्णांक cpu_id)
अणु
	init_counter(EVEN_COUNTERS, cpu_id);
	init_counter(ODD_COUNTERS, cpu_id);
	वापस 0;
पूर्ण

व्योम allocate_output_buffer()
अणु
	output_buffer = सुस्मृति(1, (1 + topo.num_cpus) * 2048);
	outp = output_buffer;
	अगर (outp == शून्य)
		err(-1, "calloc output buffer");
पूर्ण

व्योम allocate_fd_percpu(व्योम)
अणु
	fd_percpu = सुस्मृति(topo.max_cpu_num + 1, माप(पूर्णांक));
	अगर (fd_percpu == शून्य)
		err(-1, "calloc fd_percpu");
पूर्ण

व्योम allocate_irq_buffers(व्योम)
अणु
	irq_column_2_cpu = सुस्मृति(topo.num_cpus, माप(पूर्णांक));
	अगर (irq_column_2_cpu == शून्य)
		err(-1, "calloc %d", topo.num_cpus);

	irqs_per_cpu = सुस्मृति(topo.max_cpu_num + 1, माप(पूर्णांक));
	अगर (irqs_per_cpu == शून्य)
		err(-1, "calloc %d", topo.max_cpu_num + 1);
पूर्ण

व्योम setup_all_buffers(व्योम)
अणु
	topology_probe();
	allocate_irq_buffers();
	allocate_fd_percpu();
	allocate_counters(&thपढ़ो_even, &core_even, &package_even);
	allocate_counters(&thपढ़ो_odd, &core_odd, &package_odd);
	allocate_output_buffer();
	क्रम_all_proc_cpus(initialize_counters);
पूर्ण

व्योम set_base_cpu(व्योम)
अणु
	base_cpu = sched_अ_लोpu();
	अगर (base_cpu < 0)
		err(-ENODEV, "No valid cpus found");

	अगर (debug > 1)
		ख_लिखो(outf, "base_cpu = %d\n", base_cpu);
पूर्ण

व्योम turbostat_init()
अणु
	setup_all_buffers();
	set_base_cpu();
	check_dev_msr();
	check_permissions();
	process_cpuid();
	linux_perf_init();

	अगर (!quiet)
		क्रम_all_cpus(prपूर्णांक_hwp, ODD_COUNTERS);

	अगर (!quiet)
		क्रम_all_cpus(prपूर्णांक_epb, ODD_COUNTERS);

	अगर (!quiet)
		क्रम_all_cpus(prपूर्णांक_perf_limit, ODD_COUNTERS);

	अगर (!quiet)
		क्रम_all_cpus(prपूर्णांक_rapl, ODD_COUNTERS);

	क्रम_all_cpus(set_temperature_target, ODD_COUNTERS);

	क्रम_all_cpus(get_cpu_type, ODD_COUNTERS);
	क्रम_all_cpus(get_cpu_type, EVEN_COUNTERS);

	अगर (!quiet)
		क्रम_all_cpus(prपूर्णांक_thermal, ODD_COUNTERS);

	अगर (!quiet && करो_irtl_snb)
		prपूर्णांक_irtl();
पूर्ण

पूर्णांक विभाजन_it(अक्षर **argv)
अणु
	pid_t child_pid;
	पूर्णांक status;

	snapshot_proc_sysfs_files();
	status = क्रम_all_cpus(get_counters, EVEN_COUNTERS);
	first_counter_पढ़ो = 0;
	अगर (status)
		निकास(status);
	/* clear affinity side-effect of get_counters() */
	sched_setaffinity(0, cpu_present_setsize, cpu_present_set);
	समय_लोofday(&tv_even, (काष्ठा समयzone *)शून्य);

	child_pid = विभाजन();
	अगर (!child_pid) अणु
		/* child */
		execvp(argv[0], argv);
		err(त्रुटि_सं, "exec %s", argv[0]);
	पूर्ण अन्यथा अणु

		/* parent */
		अगर (child_pid == -1)
			err(1, "fork");

		संकेत(संक_विघ्न, संक_छोड़ो);
		संकेत(SIGQUIT, संक_छोड़ो);
		अगर (रुकोpid(child_pid, &status, 0) == -1)
			err(status, "waitpid");

		अगर (WIFEXITED(status))
			status = WEXITSTATUS(status);
	पूर्ण
	/*
	 * n.b. विभाजन_it() करोes not check क्रम errors from क्रम_all_cpus()
	 * because re-starting is problematic when विभाजनing
	 */
	snapshot_proc_sysfs_files();
	क्रम_all_cpus(get_counters, ODD_COUNTERS);
	समय_लोofday(&tv_odd, (काष्ठा समयzone *)शून्य);
	समयrsub(&tv_odd, &tv_even, &tv_delta);
	अगर (क्रम_all_cpus_2(delta_cpu, ODD_COUNTERS, EVEN_COUNTERS))
		ख_लिखो(outf, "%s: Counter reset detected\n", progname);
	अन्यथा अणु
		compute_average(EVEN_COUNTERS);
		क्रमmat_all_counters(EVEN_COUNTERS);
	पूर्ण

	ख_लिखो(outf, "%.6f sec\n", tv_delta.tv_sec + tv_delta.tv_usec / 1000000.0);

	flush_output_मानक_त्रुटि();

	वापस status;
पूर्ण

पूर्णांक get_and_dump_counters(व्योम)
अणु
	पूर्णांक status;

	snapshot_proc_sysfs_files();
	status = क्रम_all_cpus(get_counters, ODD_COUNTERS);
	अगर (status)
		वापस status;

	status = क्रम_all_cpus(dump_counters, ODD_COUNTERS);
	अगर (status)
		वापस status;

	flush_output_मानक_निकास();

	वापस status;
पूर्ण

व्योम prपूर्णांक_version()
अणु
	ख_लिखो(outf, "turbostat version 21.05.04" " - Len Brown <lenb@kernel.org>\n");
पूर्ण

पूर्णांक add_counter(अचिन्हित पूर्णांक msr_num, अक्षर *path, अक्षर *name,
		अचिन्हित पूर्णांक width, क्रमागत counter_scope scope,
		क्रमागत counter_type type, क्रमागत counter_क्रमmat क्रमmat, पूर्णांक flags)
अणु
	काष्ठा msr_counter *msrp;

	msrp = सुस्मृति(1, माप(काष्ठा msr_counter));
	अगर (msrp == शून्य) अणु
		लिखो_त्रुटि("calloc");
		निकास(1);
	पूर्ण

	msrp->msr_num = msr_num;
	म_नकलन(msrp->name, name, NAME_BYTES - 1);
	अगर (path)
		म_नकलन(msrp->path, path, PATH_BYTES - 1);
	msrp->width = width;
	msrp->type = type;
	msrp->क्रमmat = क्रमmat;
	msrp->flags = flags;

	चयन (scope) अणु

	हाल SCOPE_CPU:
		msrp->next = sys.tp;
		sys.tp = msrp;
		sys.added_thपढ़ो_counters++;
		अगर (sys.added_thपढ़ो_counters > MAX_ADDED_THREAD_COUNTERS) अणु
			ख_लिखो(मानक_त्रुटि, "exceeded max %d added thread counters\n", MAX_ADDED_COUNTERS);
			निकास(-1);
		पूर्ण
		अवरोध;

	हाल SCOPE_CORE:
		msrp->next = sys.cp;
		sys.cp = msrp;
		sys.added_core_counters++;
		अगर (sys.added_core_counters > MAX_ADDED_COUNTERS) अणु
			ख_लिखो(मानक_त्रुटि, "exceeded max %d added core counters\n", MAX_ADDED_COUNTERS);
			निकास(-1);
		पूर्ण
		अवरोध;

	हाल SCOPE_PACKAGE:
		msrp->next = sys.pp;
		sys.pp = msrp;
		sys.added_package_counters++;
		अगर (sys.added_package_counters > MAX_ADDED_COUNTERS) अणु
			ख_लिखो(मानक_त्रुटि, "exceeded max %d added package counters\n", MAX_ADDED_COUNTERS);
			निकास(-1);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम parse_add_command(अक्षर *add_command)
अणु
	पूर्णांक msr_num = 0;
	अक्षर *path = शून्य;
	अक्षर name_buffer[NAME_BYTES] = "";
	पूर्णांक width = 64;
	पूर्णांक fail = 0;
	क्रमागत counter_scope scope = SCOPE_CPU;
	क्रमागत counter_type type = COUNTER_CYCLES;
	क्रमागत counter_क्रमmat क्रमmat = FORMAT_DELTA;

	जबतक (add_command) अणु

		अगर (माला_पूछो(add_command, "msr0x%x", &msr_num) == 1)
			जाओ next;

		अगर (माला_पूछो(add_command, "msr%d", &msr_num) == 1)
			जाओ next;

		अगर (*add_command == '/') अणु
			path = add_command;
			जाओ next;
		पूर्ण

		अगर (माला_पूछो(add_command, "u%d", &width) == 1) अणु
			अगर ((width == 32) || (width == 64))
				जाओ next;
			width = 64;
		पूर्ण
		अगर (!म_भेदन(add_command, "cpu", म_माप("cpu"))) अणु
			scope = SCOPE_CPU;
			जाओ next;
		पूर्ण
		अगर (!म_भेदन(add_command, "core", म_माप("core"))) अणु
			scope = SCOPE_CORE;
			जाओ next;
		पूर्ण
		अगर (!म_भेदन(add_command, "package", म_माप("package"))) अणु
			scope = SCOPE_PACKAGE;
			जाओ next;
		पूर्ण
		अगर (!म_भेदन(add_command, "cycles", म_माप("cycles"))) अणु
			type = COUNTER_CYCLES;
			जाओ next;
		पूर्ण
		अगर (!म_भेदन(add_command, "seconds", म_माप("seconds"))) अणु
			type = COUNTER_SECONDS;
			जाओ next;
		पूर्ण
		अगर (!म_भेदन(add_command, "usec", म_माप("usec"))) अणु
			type = COUNTER_USEC;
			जाओ next;
		पूर्ण
		अगर (!म_भेदन(add_command, "raw", म_माप("raw"))) अणु
			क्रमmat = FORMAT_RAW;
			जाओ next;
		पूर्ण
		अगर (!म_भेदन(add_command, "delta", म_माप("delta"))) अणु
			क्रमmat = FORMAT_DELTA;
			जाओ next;
		पूर्ण
		अगर (!म_भेदन(add_command, "percent", म_माप("percent"))) अणु
			क्रमmat = FORMAT_PERCENT;
			जाओ next;
		पूर्ण

		अगर (माला_पूछो(add_command, "%18s,%*s", name_buffer) == 1) अणु	/* 18 < NAME_BYTES */
			अक्षर *eos;

			eos = म_अक्षर(name_buffer, ',');
			अगर (eos)
				*eos = '\0';
			जाओ next;
		पूर्ण

next:
		add_command = म_अक्षर(add_command, ',');
		अगर (add_command) अणु
			*add_command = '\0';
			add_command++;
		पूर्ण

	पूर्ण
	अगर ((msr_num == 0) && (path == शून्य)) अणु
		ख_लिखो(मानक_त्रुटि, "--add: (msrDDD | msr0xXXX | /path_to_counter ) required\n");
		fail++;
	पूर्ण

	/* generate शेष column header */
	अगर (*name_buffer == '\0') अणु
		अगर (width == 32)
			प्र_लिखो(name_buffer, "M0x%x%s", msr_num, क्रमmat == FORMAT_PERCENT ? "%" : "");
		अन्यथा
			प्र_लिखो(name_buffer, "M0X%x%s", msr_num, क्रमmat == FORMAT_PERCENT ? "%" : "");
	पूर्ण

	अगर (add_counter(msr_num, path, name_buffer, width, scope, type, क्रमmat, 0))
		fail++;

	अगर (fail) अणु
		help();
		निकास(1);
	पूर्ण
पूर्ण

पूर्णांक is_deferred_skip(अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < deferred_skip_index; ++i)
		अगर (!म_भेद(name, deferred_skip_names[i]))
			वापस 1;
	वापस 0;
पूर्ण

व्योम probe_sysfs(व्योम)
अणु
	अक्षर path[64];
	अक्षर name_buf[16];
	खाता *input;
	पूर्णांक state;
	अक्षर *sp;

	अगर (!DO_BIC(BIC_sysfs))
		वापस;

	क्रम (state = 10; state >= 0; --state) अणु

		प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/cpuidle/state%d/name", base_cpu, state);
		input = ख_खोलो(path, "r");
		अगर (input == शून्य)
			जारी;
		अगर (!ख_माला_लो(name_buf, माप(name_buf), input))
			err(1, "%s: failed to read file", path);

		/* truncate "C1-HSW\n" to "C1", or truncate "C1\n" to "C1" */
		sp = म_अक्षर(name_buf, '-');
		अगर (!sp)
			sp = म_अक्षरnul(name_buf, '\n');
		*sp = '%';
		*(sp + 1) = '\0';

		हटाओ_underbar(name_buf);

		ख_बंद(input);

		प्र_लिखो(path, "cpuidle/state%d/time", state);

		अगर (is_deferred_skip(name_buf))
			जारी;

		add_counter(0, path, name_buf, 64, SCOPE_CPU, COUNTER_USEC, FORMAT_PERCENT, SYSFS_PERCPU);
	पूर्ण

	क्रम (state = 10; state >= 0; --state) अणु

		प्र_लिखो(path, "/sys/devices/system/cpu/cpu%d/cpuidle/state%d/name", base_cpu, state);
		input = ख_खोलो(path, "r");
		अगर (input == शून्य)
			जारी;
		अगर (!ख_माला_लो(name_buf, माप(name_buf), input))
			err(1, "%s: failed to read file", path);
		/* truncate "C1-HSW\n" to "C1", or truncate "C1\n" to "C1" */
		sp = म_अक्षर(name_buf, '-');
		अगर (!sp)
			sp = म_अक्षरnul(name_buf, '\n');
		*sp = '\0';
		ख_बंद(input);

		हटाओ_underbar(name_buf);

		प्र_लिखो(path, "cpuidle/state%d/usage", state);

		अगर (is_deferred_skip(name_buf))
			जारी;

		add_counter(0, path, name_buf, 64, SCOPE_CPU, COUNTER_ITEMS, FORMAT_DELTA, SYSFS_PERCPU);
	पूर्ण

पूर्ण

/*
 * parse cpuset with following syntax
 * 1,2,4..6,8-10 and set bits in cpu_subset
 */
व्योम parse_cpu_command(अक्षर *optarg)
अणु
	अचिन्हित पूर्णांक start, end;
	अक्षर *next;

	अगर (!म_भेद(optarg, "core")) अणु
		अगर (cpu_subset)
			जाओ error;
		show_core_only++;
		वापस;
	पूर्ण
	अगर (!म_भेद(optarg, "package")) अणु
		अगर (cpu_subset)
			जाओ error;
		show_pkg_only++;
		वापस;
	पूर्ण
	अगर (show_core_only || show_pkg_only)
		जाओ error;

	cpu_subset = CPU_ALLOC(CPU_SUBSET_MAXCPUS);
	अगर (cpu_subset == शून्य)
		err(3, "CPU_ALLOC");
	cpu_subset_size = CPU_ALLOC_SIZE(CPU_SUBSET_MAXCPUS);

	CPU_ZERO_S(cpu_subset_size, cpu_subset);

	next = optarg;

	जबतक (next && *next) अणु

		अगर (*next == '-')	/* no negative cpu numbers */
			जाओ error;

		start = म_से_अदीर्घ(next, &next, 10);

		अगर (start >= CPU_SUBSET_MAXCPUS)
			जाओ error;
		CPU_SET_S(start, cpu_subset_size, cpu_subset);

		अगर (*next == '\0')
			अवरोध;

		अगर (*next == ',') अणु
			next += 1;
			जारी;
		पूर्ण

		अगर (*next == '-') अणु
			next += 1;	/* start range */
		पूर्ण अन्यथा अगर (*next == '.') अणु
			next += 1;
			अगर (*next == '.')
				next += 1;	/* start range */
			अन्यथा
				जाओ error;
		पूर्ण

		end = म_से_अदीर्घ(next, &next, 10);
		अगर (end <= start)
			जाओ error;

		जबतक (++start <= end) अणु
			अगर (start >= CPU_SUBSET_MAXCPUS)
				जाओ error;
			CPU_SET_S(start, cpu_subset_size, cpu_subset);
		पूर्ण

		अगर (*next == ',')
			next += 1;
		अन्यथा अगर (*next != '\0')
			जाओ error;
	पूर्ण

	वापस;

error:
	ख_लिखो(मानक_त्रुटि, "\"--cpu %s\" malformed\n", optarg);
	help();
	निकास(-1);
पूर्ण

व्योम cmdline(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt;
	पूर्णांक option_index = 0;
	अटल काष्ठा option दीर्घ_options[] = अणु
		अणु "add", required_argument, 0, 'a' पूर्ण,
		अणु "cpu", required_argument, 0, 'c' पूर्ण,
		अणु "Dump", no_argument, 0, 'D' पूर्ण,
		अणु "debug", no_argument, 0, 'd' पूर्ण,	/* पूर्णांकernal, not करोcumented */
		अणु "enable", required_argument, 0, 'e' पूर्ण,
		अणु "interval", required_argument, 0, 'i' पूर्ण,
		अणु "IPC", no_argument, 0, 'I' पूर्ण,
		अणु "num_iterations", required_argument, 0, 'n' पूर्ण,
		अणु "help", no_argument, 0, 'h' पूर्ण,
		अणु "hide", required_argument, 0, 'H' पूर्ण,	// meh, -h taken by --help
		अणु "Joules", no_argument, 0, 'J' पूर्ण,
		अणु "list", no_argument, 0, 'l' पूर्ण,
		अणु "out", required_argument, 0, 'o' पूर्ण,
		अणु "quiet", no_argument, 0, 'q' पूर्ण,
		अणु "show", required_argument, 0, 's' पूर्ण,
		अणु "Summary", no_argument, 0, 'S' पूर्ण,
		अणु "TCC", required_argument, 0, 'T' पूर्ण,
		अणु "version", no_argument, 0, 'v' पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;

	progname = argv[0];

	जबतक ((opt = getopt_दीर्घ_only(argc, argv, "+C:c:Dde:hi:Jn:o:qST:v", दीर्घ_options, &option_index)) != -1) अणु
		चयन (opt) अणु
		हाल 'a':
			parse_add_command(optarg);
			अवरोध;
		हाल 'c':
			parse_cpu_command(optarg);
			अवरोध;
		हाल 'D':
			dump_only++;
			अवरोध;
		हाल 'e':
			/* --enable specअगरied counter */
			bic_enabled = bic_enabled | bic_lookup(optarg, SHOW_LIST);
			अवरोध;
		हाल 'd':
			debug++;
			ENABLE_BIC(BIC_DISABLED_BY_DEFAULT);
			अवरोध;
		हाल 'H':
			/*
			 * --hide: करो not show those specअगरied
			 *  multiple invocations simply clear more bits in enabled mask
			 */
			bic_enabled &= ~bic_lookup(optarg, HIDE_LIST);
			अवरोध;
		हाल 'h':
		शेष:
			help();
			निकास(1);
		हाल 'i':
			अणु
				द्विगुन पूर्णांकerval = म_से_भग्न(optarg, शून्य);

				अगर (पूर्णांकerval < 0.001) अणु
					ख_लिखो(outf, "interval %f seconds is too small\n", पूर्णांकerval);
					निकास(2);
				पूर्ण

				पूर्णांकerval_tv.tv_sec = पूर्णांकerval_ts.tv_sec = पूर्णांकerval;
				पूर्णांकerval_tv.tv_usec = (पूर्णांकerval - पूर्णांकerval_tv.tv_sec) * 1000000;
				पूर्णांकerval_ts.tv_nsec = (पूर्णांकerval - पूर्णांकerval_ts.tv_sec) * 1000000000;
			पूर्ण
			अवरोध;
		हाल 'J':
			rapl_joules++;
			अवरोध;
		हाल 'l':
			ENABLE_BIC(BIC_DISABLED_BY_DEFAULT);
			list_header_only++;
			quiet++;
			अवरोध;
		हाल 'o':
			outf = ख_खोलो_or_die(optarg, "w");
			अवरोध;
		हाल 'q':
			quiet = 1;
			अवरोध;
		हाल 'n':
			num_iterations = म_से_भग्न(optarg, शून्य);

			अगर (num_iterations <= 0) अणु
				ख_लिखो(outf, "iterations %d should be positive number\n", num_iterations);
				निकास(2);
			पूर्ण
			अवरोध;
		हाल 's':
			/*
			 * --show: show only those specअगरied
			 *  The 1st invocation will clear and replace the enabled mask
			 *  subsequent invocations can add to it.
			 */
			अगर (shown == 0)
				bic_enabled = bic_lookup(optarg, SHOW_LIST);
			अन्यथा
				bic_enabled |= bic_lookup(optarg, SHOW_LIST);
			shown = 1;
			अवरोध;
		हाल 'S':
			summary_only++;
			अवरोध;
		हाल 'T':
			tj_max_override = म_से_प(optarg);
			अवरोध;
		हाल 'v':
			prपूर्णांक_version();
			निकास(0);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	outf = मानक_त्रुटि;
	cmdline(argc, argv);

	अगर (!quiet)
		prपूर्णांक_version();

	probe_sysfs();

	turbostat_init();

	/* dump counters and निकास */
	अगर (dump_only)
		वापस get_and_dump_counters();

	/* list header and निकास */
	अगर (list_header_only) अणु
		prपूर्णांक_header(",");
		flush_output_मानक_निकास();
		वापस 0;
	पूर्ण

	msr_sum_record();
	/*
	 * अगर any params left, it must be a command to विभाजन
	 */
	अगर (argc - optind)
		वापस विभाजन_it(argv + optind);
	अन्यथा
		turbostat_loop();

	वापस 0;
पूर्ण

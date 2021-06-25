<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Contains CPU specअगरic errata definitions
 *
 * Copyright (C) 2014 ARM Ltd.
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/types.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/smp_plat.h>

अटल bool __maybe_unused
is_affected_midr_range(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक scope)
अणु
	स्थिर काष्ठा arm64_midr_revidr *fix;
	u32 midr = पढ़ो_cpuid_id(), revidr;

	WARN_ON(scope != SCOPE_LOCAL_CPU || preemptible());
	अगर (!is_midr_in_range(midr, &entry->midr_range))
		वापस false;

	midr &= MIDR_REVISION_MASK | MIDR_VARIANT_MASK;
	revidr = पढ़ो_cpuid(REVIDR_EL1);
	क्रम (fix = entry->fixed_revs; fix && fix->revidr_mask; fix++)
		अगर (midr == fix->midr_rv && (revidr & fix->revidr_mask))
			वापस false;

	वापस true;
पूर्ण

अटल bool __maybe_unused
is_affected_midr_range_list(स्थिर काष्ठा arm64_cpu_capabilities *entry,
			    पूर्णांक scope)
अणु
	WARN_ON(scope != SCOPE_LOCAL_CPU || preemptible());
	वापस is_midr_in_range_list(पढ़ो_cpuid_id(), entry->midr_range_list);
पूर्ण

अटल bool __maybe_unused
is_kryo_midr(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक scope)
अणु
	u32 model;

	WARN_ON(scope != SCOPE_LOCAL_CPU || preemptible());

	model = पढ़ो_cpuid_id();
	model &= MIDR_IMPLEMENTOR_MASK | (0xf00 << MIDR_PARTNUM_SHIFT) |
		 MIDR_ARCHITECTURE_MASK;

	वापस model == entry->midr_range.model;
पूर्ण

अटल bool
has_mismatched_cache_type(स्थिर काष्ठा arm64_cpu_capabilities *entry,
			  पूर्णांक scope)
अणु
	u64 mask = arm64_ftr_reg_ctrel0.strict_mask;
	u64 sys = arm64_ftr_reg_ctrel0.sys_val & mask;
	u64 ctr_raw, ctr_real;

	WARN_ON(scope != SCOPE_LOCAL_CPU || preemptible());

	/*
	 * We want to make sure that all the CPUs in the प्रणाली expose
	 * a consistent CTR_EL0 to make sure that applications behaves
	 * correctly with migration.
	 *
	 * If a CPU has CTR_EL0.IDC but करोes not advertise it via CTR_EL0 :
	 *
	 * 1) It is safe अगर the प्रणाली करोesn't support IDC, as CPU anyway
	 *    reports IDC = 0, consistent with the rest.
	 *
	 * 2) If the प्रणाली has IDC, it is still safe as we trap CTR_EL0
	 *    access on this CPU via the ARM64_HAS_CACHE_IDC capability.
	 *
	 * So, we need to make sure either the raw CTR_EL0 or the effective
	 * CTR_EL0 matches the प्रणाली's copy to allow a secondary CPU to boot.
	 */
	ctr_raw = पढ़ो_cpuid_cachetype() & mask;
	ctr_real = पढ़ो_cpuid_effective_cachetype() & mask;

	वापस (ctr_real != sys) && (ctr_raw != sys);
पूर्ण

अटल व्योम
cpu_enable_trap_ctr_access(स्थिर काष्ठा arm64_cpu_capabilities *cap)
अणु
	u64 mask = arm64_ftr_reg_ctrel0.strict_mask;
	bool enable_uct_trap = false;

	/* Trap CTR_EL0 access on this CPU, only अगर it has a mismatch */
	अगर ((पढ़ो_cpuid_cachetype() & mask) !=
	    (arm64_ftr_reg_ctrel0.sys_val & mask))
		enable_uct_trap = true;

	/* ... or अगर the प्रणाली is affected by an erratum */
	अगर (cap->capability == ARM64_WORKAROUND_1542419)
		enable_uct_trap = true;

	अगर (enable_uct_trap)
		sysreg_clear_set(sctlr_el1, SCTLR_EL1_UCT, 0);
पूर्ण

#अगर_घोषित CONFIG_ARM64_ERRATUM_1463225
अटल bool
has_cortex_a76_erratum_1463225(स्थिर काष्ठा arm64_cpu_capabilities *entry,
			       पूर्णांक scope)
अणु
	वापस is_affected_midr_range_list(entry, scope) && is_kernel_in_hyp_mode();
पूर्ण
#पूर्ण_अगर

अटल व्योम __maybe_unused
cpu_enable_cache_मुख्यt_trap(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	sysreg_clear_set(sctlr_el1, SCTLR_EL1_UCI, 0);
पूर्ण

#घोषणा CAP_MIDR_RANGE(model, v_min, r_min, v_max, r_max)	\
	.matches = is_affected_midr_range,			\
	.midr_range = MIDR_RANGE(model, v_min, r_min, v_max, r_max)

#घोषणा CAP_MIDR_ALL_VERSIONS(model)					\
	.matches = is_affected_midr_range,				\
	.midr_range = MIDR_ALL_VERSIONS(model)

#घोषणा MIDR_FIXED(rev, revidr_mask) \
	.fixed_revs = (काष्ठा arm64_midr_revidr[])अणुअणु (rev), (revidr_mask) पूर्ण, अणुपूर्णपूर्ण

#घोषणा ERRATA_MIDR_RANGE(model, v_min, r_min, v_max, r_max)		\
	.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,				\
	CAP_MIDR_RANGE(model, v_min, r_min, v_max, r_max)

#घोषणा CAP_MIDR_RANGE_LIST(list)				\
	.matches = is_affected_midr_range_list,			\
	.midr_range_list = list

/* Errata affecting a range of revisions of  given model variant */
#घोषणा ERRATA_MIDR_REV_RANGE(m, var, r_min, r_max)	 \
	ERRATA_MIDR_RANGE(m, var, r_min, var, r_max)

/* Errata affecting a single variant/revision of a model */
#घोषणा ERRATA_MIDR_REV(model, var, rev)	\
	ERRATA_MIDR_RANGE(model, var, rev, var, rev)

/* Errata affecting all variants/revisions of a given a model */
#घोषणा ERRATA_MIDR_ALL_VERSIONS(model)				\
	.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,			\
	CAP_MIDR_ALL_VERSIONS(model)

/* Errata affecting a list of midr ranges, with same work around */
#घोषणा ERRATA_MIDR_RANGE_LIST(midr_list)			\
	.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,			\
	CAP_MIDR_RANGE_LIST(midr_list)

अटल स्थिर __maybe_unused काष्ठा midr_range tx2_family_cpus[] = अणु
	MIDR_ALL_VERSIONS(MIDR_BRCM_VULCAN),
	MIDR_ALL_VERSIONS(MIDR_CAVIUM_THUNDERX2),
	अणुपूर्ण,
पूर्ण;

अटल bool __maybe_unused
needs_tx2_tvm_workaround(स्थिर काष्ठा arm64_cpu_capabilities *entry,
			 पूर्णांक scope)
अणु
	पूर्णांक i;

	अगर (!is_affected_midr_range_list(entry, scope) ||
	    !is_hyp_mode_available())
		वापस false;

	क्रम_each_possible_cpu(i) अणु
		अगर (MPIDR_AFFINITY_LEVEL(cpu_logical_map(i), 0) != 0)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool __maybe_unused
has_neoverse_n1_erratum_1542419(स्थिर काष्ठा arm64_cpu_capabilities *entry,
				पूर्णांक scope)
अणु
	u32 midr = पढ़ो_cpuid_id();
	bool has_dic = पढ़ो_cpuid_cachetype() & BIT(CTR_DIC_SHIFT);
	स्थिर काष्ठा midr_range range = MIDR_ALL_VERSIONS(MIDR_NEOVERSE_N1);

	WARN_ON(scope != SCOPE_LOCAL_CPU || preemptible());
	वापस is_midr_in_range(midr, &range) && has_dic;
पूर्ण

#अगर_घोषित CONFIG_ARM64_WORKAROUND_REPEAT_TLBI
अटल स्थिर काष्ठा arm64_cpu_capabilities arm64_repeat_tlbi_list[] = अणु
#अगर_घोषित CONFIG_QCOM_FALKOR_ERRATUM_1009
	अणु
		ERRATA_MIDR_REV(MIDR_QCOM_FALKOR_V1, 0, 0)
	पूर्ण,
	अणु
		.midr_range.model = MIDR_QCOM_KRYO,
		.matches = is_kryo_midr,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_1286807
	अणु
		ERRATA_MIDR_RANGE(MIDR_CORTEX_A76, 0, 0, 3, 0),
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CAVIUM_ERRATUM_27456
स्थिर काष्ठा midr_range cavium_erratum_27456_cpus[] = अणु
	/* Cavium ThunderX, T88 pass 1.x - 2.1 */
	MIDR_RANGE(MIDR_THUNDERX, 0, 0, 1, 1),
	/* Cavium ThunderX, T81 pass 1.0 */
	MIDR_REV(MIDR_THUNDERX_81XX, 0, 0),
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CAVIUM_ERRATUM_30115
अटल स्थिर काष्ठा midr_range cavium_erratum_30115_cpus[] = अणु
	/* Cavium ThunderX, T88 pass 1.x - 2.2 */
	MIDR_RANGE(MIDR_THUNDERX, 0, 0, 1, 2),
	/* Cavium ThunderX, T81 pass 1.0 - 1.2 */
	MIDR_REV_RANGE(MIDR_THUNDERX_81XX, 0, 0, 2),
	/* Cavium ThunderX, T83 pass 1.0 */
	MIDR_REV(MIDR_THUNDERX_83XX, 0, 0),
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_QCOM_FALKOR_ERRATUM_1003
अटल स्थिर काष्ठा arm64_cpu_capabilities qcom_erratum_1003_list[] = अणु
	अणु
		ERRATA_MIDR_REV(MIDR_QCOM_FALKOR_V1, 0, 0),
	पूर्ण,
	अणु
		.midr_range.model = MIDR_QCOM_KRYO,
		.matches = is_kryo_midr,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_WORKAROUND_CLEAN_CACHE
अटल स्थिर काष्ठा midr_range workaround_clean_cache[] = अणु
#अगर	defined(CONFIG_ARM64_ERRATUM_826319) || \
	defined(CONFIG_ARM64_ERRATUM_827319) || \
	defined(CONFIG_ARM64_ERRATUM_824069)
	/* Cortex-A53 r0p[012]: ARM errata 826319, 827319, 824069 */
	MIDR_REV_RANGE(MIDR_CORTEX_A53, 0, 0, 2),
#पूर्ण_अगर
#अगर_घोषित	CONFIG_ARM64_ERRATUM_819472
	/* Cortex-A53 r0p[01] : ARM errata 819472 */
	MIDR_REV_RANGE(MIDR_CORTEX_A53, 0, 0, 1),
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_ERRATUM_1418040
/*
 * - 1188873 affects r0p0 to r2p0
 * - 1418040 affects r0p0 to r3p1
 */
अटल स्थिर काष्ठा midr_range erratum_1418040_list[] = अणु
	/* Cortex-A76 r0p0 to r3p1 */
	MIDR_RANGE(MIDR_CORTEX_A76, 0, 0, 3, 1),
	/* Neoverse-N1 r0p0 to r3p1 */
	MIDR_RANGE(MIDR_NEOVERSE_N1, 0, 0, 3, 1),
	/* Kryo4xx Gold (rcpe to rfpf) => (r0p0 to r3p1) */
	MIDR_RANGE(MIDR_QCOM_KRYO_4XX_GOLD, 0xc, 0xe, 0xf, 0xf),
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_ERRATUM_845719
अटल स्थिर काष्ठा midr_range erratum_845719_list[] = अणु
	/* Cortex-A53 r0p[01234] */
	MIDR_REV_RANGE(MIDR_CORTEX_A53, 0, 0, 4),
	/* Brahma-B53 r0p[0] */
	MIDR_REV(MIDR_BRAHMA_B53, 0, 0),
	/* Kryo2XX Silver rAp4 */
	MIDR_REV(MIDR_QCOM_KRYO_2XX_SILVER, 0xa, 0x4),
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_ERRATUM_843419
अटल स्थिर काष्ठा arm64_cpu_capabilities erratum_843419_list[] = अणु
	अणु
		/* Cortex-A53 r0p[01234] */
		.matches = is_affected_midr_range,
		ERRATA_MIDR_REV_RANGE(MIDR_CORTEX_A53, 0, 0, 4),
		MIDR_FIXED(0x4, BIT(8)),
	पूर्ण,
	अणु
		/* Brahma-B53 r0p[0] */
		.matches = is_affected_midr_range,
		ERRATA_MIDR_REV(MIDR_BRAHMA_B53, 0, 0),
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_WORKAROUND_SPECULATIVE_AT
अटल स्थिर काष्ठा midr_range erratum_speculative_at_list[] = अणु
#अगर_घोषित CONFIG_ARM64_ERRATUM_1165522
	/* Cortex A76 r0p0 to r2p0 */
	MIDR_RANGE(MIDR_CORTEX_A76, 0, 0, 2, 0),
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_1319367
	MIDR_ALL_VERSIONS(MIDR_CORTEX_A57),
	MIDR_ALL_VERSIONS(MIDR_CORTEX_A72),
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_1530923
	/* Cortex A55 r0p0 to r2p0 */
	MIDR_RANGE(MIDR_CORTEX_A55, 0, 0, 2, 0),
	/* Kryo4xx Silver (rdpe => r1p0) */
	MIDR_REV(MIDR_QCOM_KRYO_4XX_SILVER, 0xd, 0xe),
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_ERRATUM_1463225
अटल स्थिर काष्ठा midr_range erratum_1463225[] = अणु
	/* Cortex-A76 r0p0 - r3p1 */
	MIDR_RANGE(MIDR_CORTEX_A76, 0, 0, 3, 1),
	/* Kryo4xx Gold (rcpe to rfpf) => (r0p0 to r3p1) */
	MIDR_RANGE(MIDR_QCOM_KRYO_4XX_GOLD, 0xc, 0xe, 0xf, 0xf),
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

स्थिर काष्ठा arm64_cpu_capabilities arm64_errata[] = अणु
#अगर_घोषित CONFIG_ARM64_WORKAROUND_CLEAN_CACHE
	अणु
		.desc = "ARM errata 826319, 827319, 824069, or 819472",
		.capability = ARM64_WORKAROUND_CLEAN_CACHE,
		ERRATA_MIDR_RANGE_LIST(workaround_clean_cache),
		.cpu_enable = cpu_enable_cache_मुख्यt_trap,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_832075
	अणु
	/* Cortex-A57 r0p0 - r1p2 */
		.desc = "ARM erratum 832075",
		.capability = ARM64_WORKAROUND_DEVICE_LOAD_ACQUIRE,
		ERRATA_MIDR_RANGE(MIDR_CORTEX_A57,
				  0, 0,
				  1, 2),
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_834220
	अणु
	/* Cortex-A57 r0p0 - r1p2 */
		.desc = "ARM erratum 834220",
		.capability = ARM64_WORKAROUND_834220,
		ERRATA_MIDR_RANGE(MIDR_CORTEX_A57,
				  0, 0,
				  1, 2),
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_843419
	अणु
		.desc = "ARM erratum 843419",
		.capability = ARM64_WORKAROUND_843419,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.matches = cpucap_multi_entry_cap_matches,
		.match_list = erratum_843419_list,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_845719
	अणु
		.desc = "ARM erratum 845719",
		.capability = ARM64_WORKAROUND_845719,
		ERRATA_MIDR_RANGE_LIST(erratum_845719_list),
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_ERRATUM_23154
	अणु
	/* Cavium ThunderX, pass 1.x */
		.desc = "Cavium erratum 23154",
		.capability = ARM64_WORKAROUND_CAVIUM_23154,
		ERRATA_MIDR_REV_RANGE(MIDR_THUNDERX, 0, 0, 1),
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_ERRATUM_27456
	अणु
		.desc = "Cavium erratum 27456",
		.capability = ARM64_WORKAROUND_CAVIUM_27456,
		ERRATA_MIDR_RANGE_LIST(cavium_erratum_27456_cpus),
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_ERRATUM_30115
	अणु
		.desc = "Cavium erratum 30115",
		.capability = ARM64_WORKAROUND_CAVIUM_30115,
		ERRATA_MIDR_RANGE_LIST(cavium_erratum_30115_cpus),
	पूर्ण,
#पूर्ण_अगर
	अणु
		.desc = "Mismatched cache type (CTR_EL0)",
		.capability = ARM64_MISMATCHED_CACHE_TYPE,
		.matches = has_mismatched_cache_type,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.cpu_enable = cpu_enable_trap_ctr_access,
	पूर्ण,
#अगर_घोषित CONFIG_QCOM_FALKOR_ERRATUM_1003
	अणु
		.desc = "Qualcomm Technologies Falkor/Kryo erratum 1003",
		.capability = ARM64_WORKAROUND_QCOM_FALKOR_E1003,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.matches = cpucap_multi_entry_cap_matches,
		.match_list = qcom_erratum_1003_list,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_WORKAROUND_REPEAT_TLBI
	अणु
		.desc = "Qualcomm erratum 1009, or ARM erratum 1286807",
		.capability = ARM64_WORKAROUND_REPEAT_TLBI,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.matches = cpucap_multi_entry_cap_matches,
		.match_list = arm64_repeat_tlbi_list,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_858921
	अणु
	/* Cortex-A73 all versions */
		.desc = "ARM erratum 858921",
		.capability = ARM64_WORKAROUND_858921,
		ERRATA_MIDR_ALL_VERSIONS(MIDR_CORTEX_A73),
	पूर्ण,
#पूर्ण_अगर
	अणु
		.desc = "Spectre-v2",
		.capability = ARM64_SPECTRE_V2,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.matches = has_spectre_v2,
		.cpu_enable = spectre_v2_enable_mitigation,
	पूर्ण,
#अगर_घोषित CONFIG_RANDOMIZE_BASE
	अणु
	/* Must come after the Spectre-v2 entry */
		.desc = "Spectre-v3a",
		.capability = ARM64_SPECTRE_V3A,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.matches = has_spectre_v3a,
		.cpu_enable = spectre_v3a_enable_mitigation,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.desc = "Spectre-v4",
		.capability = ARM64_SPECTRE_V4,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.matches = has_spectre_v4,
		.cpu_enable = spectre_v4_enable_mitigation,
	पूर्ण,
#अगर_घोषित CONFIG_ARM64_ERRATUM_1418040
	अणु
		.desc = "ARM erratum 1418040",
		.capability = ARM64_WORKAROUND_1418040,
		ERRATA_MIDR_RANGE_LIST(erratum_1418040_list),
		/*
		 * We need to allow affected CPUs to come in late, but
		 * also need the non-affected CPUs to be able to come
		 * in at any poपूर्णांक in समय. Wonderful.
		 */
		.type = ARM64_CPUCAP_WEAK_LOCAL_CPU_FEATURE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_WORKAROUND_SPECULATIVE_AT
	अणु
		.desc = "ARM errata 1165522, 1319367, or 1530923",
		.capability = ARM64_WORKAROUND_SPECULATIVE_AT,
		ERRATA_MIDR_RANGE_LIST(erratum_speculative_at_list),
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_1463225
	अणु
		.desc = "ARM erratum 1463225",
		.capability = ARM64_WORKAROUND_1463225,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.matches = has_cortex_a76_erratum_1463225,
		.midr_range_list = erratum_1463225,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_TX2_ERRATUM_219
	अणु
		.desc = "Cavium ThunderX2 erratum 219 (KVM guest sysreg trapping)",
		.capability = ARM64_WORKAROUND_CAVIUM_TX2_219_TVM,
		ERRATA_MIDR_RANGE_LIST(tx2_family_cpus),
		.matches = needs_tx2_tvm_workaround,
	पूर्ण,
	अणु
		.desc = "Cavium ThunderX2 erratum 219 (PRFM removal)",
		.capability = ARM64_WORKAROUND_CAVIUM_TX2_219_PRFM,
		ERRATA_MIDR_RANGE_LIST(tx2_family_cpus),
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_1542419
	अणु
		/* we depend on the firmware portion क्रम correctness */
		.desc = "ARM erratum 1542419 (kernel portion)",
		.capability = ARM64_WORKAROUND_1542419,
		.type = ARM64_CPUCAP_LOCAL_CPU_ERRATUM,
		.matches = has_neoverse_n1_erratum_1542419,
		.cpu_enable = cpu_enable_trap_ctr_access,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_ERRATUM_1508412
	अणु
		/* we depend on the firmware portion क्रम correctness */
		.desc = "ARM erratum 1508412 (kernel portion)",
		.capability = ARM64_WORKAROUND_1508412,
		ERRATA_MIDR_RANGE(MIDR_CORTEX_A77,
				  0, 0,
				  1, 0),
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NVIDIA_CARMEL_CNP_ERRATUM
	अणु
		/* NVIDIA Carmel */
		.desc = "NVIDIA Carmel CNP erratum",
		.capability = ARM64_WORKAROUND_NVIDIA_CARMEL_CNP,
		ERRATA_MIDR_ALL_VERSIONS(MIDR_NVIDIA_CARMEL),
	पूर्ण,
#पूर्ण_अगर
	अणु
	पूर्ण
पूर्ण;

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017, Nicholas Piggin, IBM Corporation
 */

#घोषणा pr_fmt(fmt) "dt-cpu-ftrs: " fmt

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/dt_cpu_ftrs.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/setup.h>


/* Device-tree visible स्थिरants follow */
#घोषणा ISA_V3_0B       3000
#घोषणा ISA_V3_1        3100

#घोषणा USABLE_PR               (1U << 0)
#घोषणा USABLE_OS               (1U << 1)
#घोषणा USABLE_HV               (1U << 2)

#घोषणा HV_SUPPORT_HFSCR        (1U << 0)
#घोषणा OS_SUPPORT_FSCR         (1U << 0)

/* For parsing, we define all bits set as "NONE" हाल */
#घोषणा HV_SUPPORT_NONE		0xffffffffU
#घोषणा OS_SUPPORT_NONE		0xffffffffU

काष्ठा dt_cpu_feature अणु
	स्थिर अक्षर *name;
	uपूर्णांक32_t isa;
	uपूर्णांक32_t usable_privilege;
	uपूर्णांक32_t hv_support;
	uपूर्णांक32_t os_support;
	uपूर्णांक32_t hfscr_bit_nr;
	uपूर्णांक32_t fscr_bit_nr;
	uपूर्णांक32_t hwcap_bit_nr;
	/* fdt parsing */
	अचिन्हित दीर्घ node;
	पूर्णांक enabled;
	पूर्णांक disabled;
पूर्ण;

#घोषणा MMU_FTRS_HASH_BASE (MMU_FTRS_POWER8)

#घोषणा COMMON_USER_BASE	(PPC_FEATURE_32 | PPC_FEATURE_64 | \
				 PPC_FEATURE_ARCH_2_06 |\
				 PPC_FEATURE_ICACHE_SNOOP)
#घोषणा COMMON_USER2_BASE	(PPC_FEATURE2_ARCH_2_07 | \
				 PPC_FEATURE2_ISEL)
/*
 * Set up the base CPU
 */

अटल पूर्णांक hv_mode;

अटल काष्ठा अणु
	u64	lpcr;
	u64	hfscr;
	u64	fscr;
	u64	pcr;
पूर्ण प्रणाली_रेजिस्टरs;

अटल व्योम (*init_pmu_रेजिस्टरs)(व्योम);

अटल व्योम __restore_cpu_cpufeatures(व्योम)
अणु
	mtspr(SPRN_LPCR, प्रणाली_रेजिस्टरs.lpcr);
	अगर (hv_mode) अणु
		mtspr(SPRN_LPID, 0);
		mtspr(SPRN_HFSCR, प्रणाली_रेजिस्टरs.hfscr);
		mtspr(SPRN_PCR, प्रणाली_रेजिस्टरs.pcr);
	पूर्ण
	mtspr(SPRN_FSCR, प्रणाली_रेजिस्टरs.fscr);

	अगर (init_pmu_रेजिस्टरs)
		init_pmu_रेजिस्टरs();
पूर्ण

अटल अक्षर dt_cpu_name[64];

अटल काष्ठा cpu_spec __initdata base_cpu_spec = अणु
	.cpu_name		= शून्य,
	.cpu_features		= CPU_FTRS_DT_CPU_BASE,
	.cpu_user_features	= COMMON_USER_BASE,
	.cpu_user_features2	= COMMON_USER2_BASE,
	.mmu_features		= 0,
	.icache_bsize		= 32, /* minimum block size, fixed by */
	.dcache_bsize		= 32, /* cache info init.             */
	.num_pmcs		= 0,
	.pmc_type		= PPC_PMC_DEFAULT,
	.oprofile_cpu_type	= शून्य,
	.cpu_setup		= शून्य,
	.cpu_restore		= __restore_cpu_cpufeatures,
	.machine_check_early	= शून्य,
	.platक्रमm		= शून्य,
पूर्ण;

अटल व्योम __init cpufeatures_setup_cpu(व्योम)
अणु
	set_cur_cpu_spec(&base_cpu_spec);

	cur_cpu_spec->pvr_mask = -1;
	cur_cpu_spec->pvr_value = mfspr(SPRN_PVR);

	/* Initialize the base environment -- clear FSCR/HFSCR.  */
	hv_mode = !!(mfmsr() & MSR_HV);
	अगर (hv_mode) अणु
		cur_cpu_spec->cpu_features |= CPU_FTR_HVMODE;
		mtspr(SPRN_HFSCR, 0);
	पूर्ण
	mtspr(SPRN_FSCR, 0);
	mtspr(SPRN_PCR, PCR_MASK);

	/*
	 * LPCR करोes not get cleared, to match behaviour with secondaries
	 * in __restore_cpu_cpufeatures. Once the idle code is fixed, this
	 * could clear LPCR too.
	 */
पूर्ण

अटल पूर्णांक __init feat_try_enable_unknown(काष्ठा dt_cpu_feature *f)
अणु
	अगर (f->hv_support == HV_SUPPORT_NONE) अणु
	पूर्ण अन्यथा अगर (f->hv_support & HV_SUPPORT_HFSCR) अणु
		u64 hfscr = mfspr(SPRN_HFSCR);
		hfscr |= 1UL << f->hfscr_bit_nr;
		mtspr(SPRN_HFSCR, hfscr);
	पूर्ण अन्यथा अणु
		/* Does not have a known recipe */
		वापस 0;
	पूर्ण

	अगर (f->os_support == OS_SUPPORT_NONE) अणु
	पूर्ण अन्यथा अगर (f->os_support & OS_SUPPORT_FSCR) अणु
		u64 fscr = mfspr(SPRN_FSCR);
		fscr |= 1UL << f->fscr_bit_nr;
		mtspr(SPRN_FSCR, fscr);
	पूर्ण अन्यथा अणु
		/* Does not have a known recipe */
		वापस 0;
	पूर्ण

	अगर ((f->usable_privilege & USABLE_PR) && (f->hwcap_bit_nr != -1)) अणु
		uपूर्णांक32_t word = f->hwcap_bit_nr / 32;
		uपूर्णांक32_t bit = f->hwcap_bit_nr % 32;

		अगर (word == 0)
			cur_cpu_spec->cpu_user_features |= 1U << bit;
		अन्यथा अगर (word == 1)
			cur_cpu_spec->cpu_user_features2 |= 1U << bit;
		अन्यथा
			pr_err("%s could not advertise to user (no hwcap bits)\n", f->name);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable(काष्ठा dt_cpu_feature *f)
अणु
	अगर (f->hv_support != HV_SUPPORT_NONE) अणु
		अगर (f->hfscr_bit_nr != -1) अणु
			u64 hfscr = mfspr(SPRN_HFSCR);
			hfscr |= 1UL << f->hfscr_bit_nr;
			mtspr(SPRN_HFSCR, hfscr);
		पूर्ण
	पूर्ण

	अगर (f->os_support != OS_SUPPORT_NONE) अणु
		अगर (f->fscr_bit_nr != -1) अणु
			u64 fscr = mfspr(SPRN_FSCR);
			fscr |= 1UL << f->fscr_bit_nr;
			mtspr(SPRN_FSCR, fscr);
		पूर्ण
	पूर्ण

	अगर ((f->usable_privilege & USABLE_PR) && (f->hwcap_bit_nr != -1)) अणु
		uपूर्णांक32_t word = f->hwcap_bit_nr / 32;
		uपूर्णांक32_t bit = f->hwcap_bit_nr % 32;

		अगर (word == 0)
			cur_cpu_spec->cpu_user_features |= 1U << bit;
		अन्यथा अगर (word == 1)
			cur_cpu_spec->cpu_user_features2 |= 1U << bit;
		अन्यथा
			pr_err("CPU feature: %s could not advertise to user (no hwcap bits)\n", f->name);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_disable(काष्ठा dt_cpu_feature *f)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __init feat_enable_hv(काष्ठा dt_cpu_feature *f)
अणु
	u64 lpcr;

	अगर (!hv_mode) अणु
		pr_err("CPU feature hypervisor present in device tree but HV mode not enabled in the CPU. Ignoring.\n");
		वापस 0;
	पूर्ण

	mtspr(SPRN_LPID, 0);

	lpcr = mfspr(SPRN_LPCR);
	lpcr &=  ~LPCR_LPES0; /* HV बाह्यal पूर्णांकerrupts */
	mtspr(SPRN_LPCR, lpcr);

	cur_cpu_spec->cpu_features |= CPU_FTR_HVMODE;

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_le(काष्ठा dt_cpu_feature *f)
अणु
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_TRUE_LE;
	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_smt(काष्ठा dt_cpu_feature *f)
अणु
	cur_cpu_spec->cpu_features |= CPU_FTR_SMT;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_SMT;
	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_idle_nap(काष्ठा dt_cpu_feature *f)
अणु
	u64 lpcr;

	/* Set PECE wakeup modes क्रम ISA 207 */
	lpcr = mfspr(SPRN_LPCR);
	lpcr |=  LPCR_PECE0;
	lpcr |=  LPCR_PECE1;
	lpcr |=  LPCR_PECE2;
	mtspr(SPRN_LPCR, lpcr);

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_idle_stop(काष्ठा dt_cpu_feature *f)
अणु
	u64 lpcr;

	/* Set PECE wakeup modes क्रम ISAv3.0B */
	lpcr = mfspr(SPRN_LPCR);
	lpcr |=  LPCR_PECE0;
	lpcr |=  LPCR_PECE1;
	lpcr |=  LPCR_PECE2;
	mtspr(SPRN_LPCR, lpcr);

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_mmu_hash(काष्ठा dt_cpu_feature *f)
अणु
	u64 lpcr;

	lpcr = mfspr(SPRN_LPCR);
	lpcr &= ~LPCR_ISL;

	/* VRMASD */
	lpcr |= LPCR_VPM0;
	lpcr &= ~LPCR_VPM1;
	lpcr |= 0x10UL << LPCR_VRMASD_SH; /* L=1 LP=00 */
	mtspr(SPRN_LPCR, lpcr);

	cur_cpu_spec->mmu_features |= MMU_FTRS_HASH_BASE;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_HAS_MMU;

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_mmu_hash_v3(काष्ठा dt_cpu_feature *f)
अणु
	u64 lpcr;

	lpcr = mfspr(SPRN_LPCR);
	lpcr &= ~(LPCR_ISL | LPCR_UPRT | LPCR_HR);
	mtspr(SPRN_LPCR, lpcr);

	cur_cpu_spec->mmu_features |= MMU_FTRS_HASH_BASE;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_HAS_MMU;

	वापस 1;
पूर्ण


अटल पूर्णांक __init feat_enable_mmu_radix(काष्ठा dt_cpu_feature *f)
अणु
#अगर_घोषित CONFIG_PPC_RADIX_MMU
	cur_cpu_spec->mmu_features |= MMU_FTR_TYPE_RADIX;
	cur_cpu_spec->mmu_features |= MMU_FTRS_HASH_BASE;
	cur_cpu_spec->mmu_features |= MMU_FTR_GTSE;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_HAS_MMU;

	वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init feat_enable_dscr(काष्ठा dt_cpu_feature *f)
अणु
	u64 lpcr;

	/*
	 * Linux relies on FSCR[DSCR] being clear, so that we can take the
	 * facility unavailable पूर्णांकerrupt and track the task's usage of DSCR.
	 * See facility_unavailable_exception().
	 * Clear the bit here so that feat_enable() करोesn't set it.
	 */
	f->fscr_bit_nr = -1;

	feat_enable(f);

	lpcr = mfspr(SPRN_LPCR);
	lpcr &= ~LPCR_DPFD;
	lpcr |=  (4UL << LPCR_DPFD_SH);
	mtspr(SPRN_LPCR, lpcr);

	वापस 1;
पूर्ण

अटल व्योम hfscr_pmu_enable(व्योम)
अणु
	u64 hfscr = mfspr(SPRN_HFSCR);
	hfscr |= PPC_BIT(60);
	mtspr(SPRN_HFSCR, hfscr);
पूर्ण

अटल व्योम init_pmu_घातer8(व्योम)
अणु
	अगर (hv_mode) अणु
		mtspr(SPRN_MMCRC, 0);
		mtspr(SPRN_MMCRH, 0);
	पूर्ण

	mtspr(SPRN_MMCRA, 0);
	mtspr(SPRN_MMCR0, 0);
	mtspr(SPRN_MMCR1, 0);
	mtspr(SPRN_MMCR2, 0);
	mtspr(SPRN_MMCRS, 0);
पूर्ण

अटल पूर्णांक __init feat_enable_mce_घातer8(काष्ठा dt_cpu_feature *f)
अणु
	cur_cpu_spec->platक्रमm = "power8";
	cur_cpu_spec->machine_check_early = __machine_check_early_realmode_p8;

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_pmu_घातer8(काष्ठा dt_cpu_feature *f)
अणु
	hfscr_pmu_enable();

	init_pmu_घातer8();
	init_pmu_रेजिस्टरs = init_pmu_घातer8;

	cur_cpu_spec->cpu_features |= CPU_FTR_MMCRA;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_PSERIES_PERFMON_COMPAT;
	अगर (pvr_version_is(PVR_POWER8E))
		cur_cpu_spec->cpu_features |= CPU_FTR_PMAO_BUG;

	cur_cpu_spec->num_pmcs		= 6;
	cur_cpu_spec->pmc_type		= PPC_PMC_IBM;
	cur_cpu_spec->oprofile_cpu_type	= "ppc64/power8";

	वापस 1;
पूर्ण

अटल व्योम init_pmu_घातer9(व्योम)
अणु
	अगर (hv_mode)
		mtspr(SPRN_MMCRC, 0);

	mtspr(SPRN_MMCRA, 0);
	mtspr(SPRN_MMCR0, 0);
	mtspr(SPRN_MMCR1, 0);
	mtspr(SPRN_MMCR2, 0);
पूर्ण

अटल पूर्णांक __init feat_enable_mce_घातer9(काष्ठा dt_cpu_feature *f)
अणु
	cur_cpu_spec->platक्रमm = "power9";
	cur_cpu_spec->machine_check_early = __machine_check_early_realmode_p9;

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_pmu_घातer9(काष्ठा dt_cpu_feature *f)
अणु
	hfscr_pmu_enable();

	init_pmu_घातer9();
	init_pmu_रेजिस्टरs = init_pmu_घातer9;

	cur_cpu_spec->cpu_features |= CPU_FTR_MMCRA;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_PSERIES_PERFMON_COMPAT;

	cur_cpu_spec->num_pmcs		= 6;
	cur_cpu_spec->pmc_type		= PPC_PMC_IBM;
	cur_cpu_spec->oprofile_cpu_type	= "ppc64/power9";

	वापस 1;
पूर्ण

अटल व्योम init_pmu_घातer10(व्योम)
अणु
	init_pmu_घातer9();

	mtspr(SPRN_MMCR3, 0);
	mtspr(SPRN_MMCRA, MMCRA_BHRB_DISABLE);
	mtspr(SPRN_MMCR0, MMCR0_PMCCEXT);
पूर्ण

अटल पूर्णांक __init feat_enable_pmu_घातer10(काष्ठा dt_cpu_feature *f)
अणु
	hfscr_pmu_enable();

	init_pmu_घातer10();
	init_pmu_रेजिस्टरs = init_pmu_घातer10;

	cur_cpu_spec->cpu_features |= CPU_FTR_MMCRA;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_PSERIES_PERFMON_COMPAT;

	cur_cpu_spec->num_pmcs          = 6;
	cur_cpu_spec->pmc_type          = PPC_PMC_IBM;
	cur_cpu_spec->oprofile_cpu_type = "ppc64/power10";

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_mce_घातer10(काष्ठा dt_cpu_feature *f)
अणु
	cur_cpu_spec->platक्रमm = "power10";
	cur_cpu_spec->machine_check_early = __machine_check_early_realmode_p10;

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_पंचांग(काष्ठा dt_cpu_feature *f)
अणु
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	feat_enable(f);
	cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_HTM_NOSC;
	वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init feat_enable_fp(काष्ठा dt_cpu_feature *f)
अणु
	feat_enable(f);
	cur_cpu_spec->cpu_features &= ~CPU_FTR_FPU_UNAVAILABLE;

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_vector(काष्ठा dt_cpu_feature *f)
अणु
#अगर_घोषित CONFIG_ALTIVEC
	feat_enable(f);
	cur_cpu_spec->cpu_features |= CPU_FTR_ALTIVEC;
	cur_cpu_spec->cpu_features |= CPU_FTR_VMX_COPY;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_HAS_ALTIVEC;

	वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init feat_enable_vsx(काष्ठा dt_cpu_feature *f)
अणु
#अगर_घोषित CONFIG_VSX
	feat_enable(f);
	cur_cpu_spec->cpu_features |= CPU_FTR_VSX;
	cur_cpu_spec->cpu_user_features |= PPC_FEATURE_HAS_VSX;

	वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init feat_enable_purr(काष्ठा dt_cpu_feature *f)
अणु
	cur_cpu_spec->cpu_features |= CPU_FTR_PURR | CPU_FTR_SPURR;

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_ebb(काष्ठा dt_cpu_feature *f)
अणु
	/*
	 * PPC_FEATURE2_EBB is enabled in PMU init code because it has
	 * historically been related to the PMU facility. This may have
	 * to be decoupled अगर EBB becomes more generic. For now, follow
	 * existing convention.
	 */
	f->hwcap_bit_nr = -1;
	feat_enable(f);

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_dbell(काष्ठा dt_cpu_feature *f)
अणु
	u64 lpcr;

	/* P9 has an HFSCR क्रम privileged state */
	feat_enable(f);

	cur_cpu_spec->cpu_features |= CPU_FTR_DBELL;

	lpcr = mfspr(SPRN_LPCR);
	lpcr |=  LPCR_PECEDH; /* hyp करोorbell wakeup */
	mtspr(SPRN_LPCR, lpcr);

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_hvi(काष्ठा dt_cpu_feature *f)
अणु
	u64 lpcr;

	/*
	 * POWER9 XIVE पूर्णांकerrupts including in OPAL XICS compatibility
	 * are always delivered as hypervisor भवization पूर्णांकerrupts (HVI)
	 * rather than EE.
	 *
	 * However LPES0 is not set here, in the chance that an EE करोes get
	 * delivered to the host somehow, the EE handler would not expect it
	 * to be delivered in LPES0 mode (e.g., using SRR[01]). This could
	 * happen अगर there is a bug in पूर्णांकerrupt controller code, or IC is
	 * misconfigured in प्रणालीsim.
	 */

	lpcr = mfspr(SPRN_LPCR);
	lpcr |= LPCR_HVICE;	/* enable hvi पूर्णांकerrupts */
	lpcr |= LPCR_HEIC;	/* disable ee पूर्णांकerrupts when MSR_HV */
	lpcr |= LPCR_PECE_HVEE; /* hvi can wake from stop */
	mtspr(SPRN_LPCR, lpcr);

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_large_ci(काष्ठा dt_cpu_feature *f)
अणु
	cur_cpu_spec->mmu_features |= MMU_FTR_CI_LARGE_PAGE;

	वापस 1;
पूर्ण

अटल पूर्णांक __init feat_enable_mma(काष्ठा dt_cpu_feature *f)
अणु
	u64 pcr;

	feat_enable(f);
	pcr = mfspr(SPRN_PCR);
	pcr &= ~PCR_MMA_DIS;
	mtspr(SPRN_PCR, pcr);

	वापस 1;
पूर्ण

काष्ठा dt_cpu_feature_match अणु
	स्थिर अक्षर *name;
	पूर्णांक (*enable)(काष्ठा dt_cpu_feature *f);
	u64 cpu_ftr_bit_mask;
पूर्ण;

अटल काष्ठा dt_cpu_feature_match __initdata
		dt_cpu_feature_match_table[] = अणु
	अणु"hypervisor", feat_enable_hv, 0पूर्ण,
	अणु"big-endian", feat_enable, 0पूर्ण,
	अणु"little-endian", feat_enable_le, CPU_FTR_REAL_LEपूर्ण,
	अणु"smt", feat_enable_smt, 0पूर्ण,
	अणु"interrupt-facilities", feat_enable, 0पूर्ण,
	अणु"system-call-vectored", feat_enable, 0पूर्ण,
	अणु"timer-facilities", feat_enable, 0पूर्ण,
	अणु"timer-facilities-v3", feat_enable, 0पूर्ण,
	अणु"debug-facilities", feat_enable, 0पूर्ण,
	अणु"come-from-address-register", feat_enable, CPU_FTR_CFARपूर्ण,
	अणु"branch-tracing", feat_enable, 0पूर्ण,
	अणु"floating-point", feat_enable_fp, 0पूर्ण,
	अणु"vector", feat_enable_vector, 0पूर्ण,
	अणु"vector-scalar", feat_enable_vsx, 0पूर्ण,
	अणु"vector-scalar-v3", feat_enable, 0पूर्ण,
	अणु"decimal-floating-point", feat_enable, 0पूर्ण,
	अणु"decimal-integer", feat_enable, 0पूर्ण,
	अणु"quadword-load-store", feat_enable, 0पूर्ण,
	अणु"vector-crypto", feat_enable, 0पूर्ण,
	अणु"mmu-hash", feat_enable_mmu_hash, 0पूर्ण,
	अणु"mmu-radix", feat_enable_mmu_radix, 0पूर्ण,
	अणु"mmu-hash-v3", feat_enable_mmu_hash_v3, 0पूर्ण,
	अणु"virtual-page-class-key-protection", feat_enable, 0पूर्ण,
	अणु"transactional-memory", feat_enable_पंचांग, CPU_FTR_TMपूर्ण,
	अणु"transactional-memory-v3", feat_enable_पंचांग, 0पूर्ण,
	अणु"tm-suspend-hypervisor-assist", feat_enable, CPU_FTR_P9_TM_HV_ASSISTपूर्ण,
	अणु"tm-suspend-xer-so-bug", feat_enable, CPU_FTR_P9_TM_XER_SO_BUGपूर्ण,
	अणु"idle-nap", feat_enable_idle_nap, 0पूर्ण,
	/* alignment-पूर्णांकerrupt-dsisr ignored */
	अणु"idle-stop", feat_enable_idle_stop, 0पूर्ण,
	अणु"machine-check-power8", feat_enable_mce_घातer8, 0पूर्ण,
	अणु"performance-monitor-power8", feat_enable_pmu_घातer8, 0पूर्ण,
	अणु"data-stream-control-register", feat_enable_dscr, CPU_FTR_DSCRपूर्ण,
	अणु"event-based-branch", feat_enable_ebb, 0पूर्ण,
	अणु"target-address-register", feat_enable, 0पूर्ण,
	अणु"branch-history-rolling-buffer", feat_enable, 0पूर्ण,
	अणु"control-register", feat_enable, CPU_FTR_CTRLपूर्ण,
	अणु"processor-control-facility", feat_enable_dbell, CPU_FTR_DBELLपूर्ण,
	अणु"processor-control-facility-v3", feat_enable_dbell, CPU_FTR_DBELLपूर्ण,
	अणु"processor-utilization-of-resources-register", feat_enable_purr, 0पूर्ण,
	अणु"no-execute", feat_enable, 0पूर्ण,
	अणु"strong-access-ordering", feat_enable, CPU_FTR_SAOपूर्ण,
	अणु"cache-inhibited-large-page", feat_enable_large_ci, 0पूर्ण,
	अणु"coprocessor-icswx", feat_enable, 0पूर्ण,
	अणु"hypervisor-virtualization-interrupt", feat_enable_hvi, 0पूर्ण,
	अणु"program-priority-register", feat_enable, CPU_FTR_HAS_PPRपूर्ण,
	अणु"wait", feat_enable, 0पूर्ण,
	अणु"atomic-memory-operations", feat_enable, 0पूर्ण,
	अणु"branch-v3", feat_enable, 0पूर्ण,
	अणु"copy-paste", feat_enable, 0पूर्ण,
	अणु"decimal-floating-point-v3", feat_enable, 0पूर्ण,
	अणु"decimal-integer-v3", feat_enable, 0पूर्ण,
	अणु"fixed-point-v3", feat_enable, 0पूर्ण,
	अणु"floating-point-v3", feat_enable, 0पूर्ण,
	अणु"group-start-register", feat_enable, 0पूर्ण,
	अणु"pc-relative-addressing", feat_enable, 0पूर्ण,
	अणु"machine-check-power9", feat_enable_mce_घातer9, 0पूर्ण,
	अणु"machine-check-power10", feat_enable_mce_घातer10, 0पूर्ण,
	अणु"performance-monitor-power9", feat_enable_pmu_घातer9, 0पूर्ण,
	अणु"performance-monitor-power10", feat_enable_pmu_घातer10, 0पूर्ण,
	अणु"event-based-branch-v3", feat_enable, 0पूर्ण,
	अणु"random-number-generator", feat_enable, 0पूर्ण,
	अणु"system-call-vectored", feat_disable, 0पूर्ण,
	अणु"trace-interrupt-v3", feat_enable, 0पूर्ण,
	अणु"vector-v3", feat_enable, 0पूर्ण,
	अणु"vector-binary128", feat_enable, 0पूर्ण,
	अणु"vector-binary16", feat_enable, 0पूर्ण,
	अणु"wait-v3", feat_enable, 0पूर्ण,
	अणु"prefix-instructions", feat_enable, 0पूर्ण,
	अणु"matrix-multiply-assist", feat_enable_mma, 0पूर्ण,
	अणु"debug-facilities-v31", feat_enable, CPU_FTR_DAWR1पूर्ण,
पूर्ण;

अटल bool __initdata using_dt_cpu_ftrs;
अटल bool __initdata enable_unknown = true;

अटल पूर्णांक __init dt_cpu_ftrs_parse(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;

	अगर (!म_भेद(str, "off"))
		using_dt_cpu_ftrs = false;
	अन्यथा अगर (!म_भेद(str, "known"))
		enable_unknown = false;
	अन्यथा
		वापस 1;

	वापस 0;
पूर्ण
early_param("dt_cpu_ftrs", dt_cpu_ftrs_parse);

अटल व्योम __init cpufeatures_setup_start(u32 isa)
अणु
	pr_info("setup for ISA %d\n", isa);

	अगर (isa >= ISA_V3_0B) अणु
		cur_cpu_spec->cpu_features |= CPU_FTR_ARCH_300;
		cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_ARCH_3_00;
	पूर्ण

	अगर (isa >= ISA_V3_1) अणु
		cur_cpu_spec->cpu_features |= CPU_FTR_ARCH_31;
		cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_ARCH_3_1;
	पूर्ण
पूर्ण

अटल bool __init cpufeatures_process_feature(काष्ठा dt_cpu_feature *f)
अणु
	स्थिर काष्ठा dt_cpu_feature_match *m;
	bool known = false;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dt_cpu_feature_match_table); i++) अणु
		m = &dt_cpu_feature_match_table[i];
		अगर (!म_भेद(f->name, m->name)) अणु
			known = true;
			अगर (m->enable(f)) अणु
				cur_cpu_spec->cpu_features |= m->cpu_ftr_bit_mask;
				अवरोध;
			पूर्ण

			pr_info("not enabling: %s (disabled or unsupported by kernel)\n",
				f->name);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (!known && (!enable_unknown || !feat_try_enable_unknown(f))) अणु
		pr_info("not enabling: %s (unknown and unsupported by kernel)\n",
			f->name);
		वापस false;
	पूर्ण

	अगर (known)
		pr_debug("enabling: %s\n", f->name);
	अन्यथा
		pr_debug("enabling: %s (unknown)\n", f->name);

	वापस true;
पूर्ण

/*
 * Handle POWER9 broadcast tlbie invalidation issue using
 * cpu feature flag.
 */
अटल __init व्योम update_tlbie_feature_flag(अचिन्हित दीर्घ pvr)
अणु
	अगर (PVR_VER(pvr) == PVR_POWER9) अणु
		/*
		 * Set the tlbie feature flag क्रम anything below
		 * Nimbus DD 2.3 and Cumulus DD 1.3
		 */
		अगर ((pvr & 0xe000) == 0) अणु
			/* Nimbus */
			अगर ((pvr & 0xfff) < 0x203)
				cur_cpu_spec->cpu_features |= CPU_FTR_P9_TLBIE_STQ_BUG;
		पूर्ण अन्यथा अगर ((pvr & 0xc000) == 0) अणु
			/* Cumulus */
			अगर ((pvr & 0xfff) < 0x103)
				cur_cpu_spec->cpu_features |= CPU_FTR_P9_TLBIE_STQ_BUG;
		पूर्ण अन्यथा अणु
			WARN_ONCE(1, "Unknown PVR");
			cur_cpu_spec->cpu_features |= CPU_FTR_P9_TLBIE_STQ_BUG;
		पूर्ण

		cur_cpu_spec->cpu_features |= CPU_FTR_P9_TLBIE_ERAT_BUG;
	पूर्ण
पूर्ण

अटल __init व्योम cpufeatures_cpu_quirks(व्योम)
अणु
	अचिन्हित दीर्घ version = mfspr(SPRN_PVR);

	/*
	 * Not all quirks can be derived from the cpufeatures device tree.
	 */
	अगर ((version & 0xffffefff) == 0x004e0200) अणु
		/* DD2.0 has no feature flag */
		cur_cpu_spec->cpu_features |= CPU_FTR_P9_RADIX_PREFETCH_BUG;
	पूर्ण अन्यथा अगर ((version & 0xffffefff) == 0x004e0201) अणु
		cur_cpu_spec->cpu_features |= CPU_FTR_POWER9_DD2_1;
		cur_cpu_spec->cpu_features |= CPU_FTR_P9_RADIX_PREFETCH_BUG;
	पूर्ण अन्यथा अगर ((version & 0xffffefff) == 0x004e0202) अणु
		cur_cpu_spec->cpu_features |= CPU_FTR_P9_TM_HV_ASSIST;
		cur_cpu_spec->cpu_features |= CPU_FTR_P9_TM_XER_SO_BUG;
		cur_cpu_spec->cpu_features |= CPU_FTR_POWER9_DD2_1;
	पूर्ण अन्यथा अगर ((version & 0xffff0000) == 0x004e0000) अणु
		/* DD2.1 and up have DD2_1 */
		cur_cpu_spec->cpu_features |= CPU_FTR_POWER9_DD2_1;
	पूर्ण

	अगर ((version & 0xffff0000) == 0x004e0000) अणु
		cur_cpu_spec->cpu_features &= ~(CPU_FTR_DAWR);
		cur_cpu_spec->cpu_features |= CPU_FTR_P9_TIDR;
	पूर्ण

	update_tlbie_feature_flag(version);
पूर्ण

अटल व्योम __init cpufeatures_setup_finished(व्योम)
अणु
	cpufeatures_cpu_quirks();

	अगर (hv_mode && !(cur_cpu_spec->cpu_features & CPU_FTR_HVMODE)) अणु
		pr_err("hypervisor not present in device tree but HV mode is enabled in the CPU. Enabling.\n");
		cur_cpu_spec->cpu_features |= CPU_FTR_HVMODE;
	पूर्ण

	/* Make sure घातerpc_base_platक्रमm is non-शून्य */
	घातerpc_base_platक्रमm = cur_cpu_spec->platक्रमm;

	प्रणाली_रेजिस्टरs.lpcr = mfspr(SPRN_LPCR);
	प्रणाली_रेजिस्टरs.hfscr = mfspr(SPRN_HFSCR);
	प्रणाली_रेजिस्टरs.fscr = mfspr(SPRN_FSCR);
	प्रणाली_रेजिस्टरs.pcr = mfspr(SPRN_PCR);

	pr_info("final cpu/mmu features = 0x%016lx 0x%08x\n",
		cur_cpu_spec->cpu_features, cur_cpu_spec->mmu_features);
पूर्ण

अटल पूर्णांक __init disabled_on_cmdline(व्योम)
अणु
	अचिन्हित दीर्घ root, chosen;
	स्थिर अक्षर *p;

	root = of_get_flat_dt_root();
	chosen = of_get_flat_dt_subnode_by_name(root, "chosen");
	अगर (chosen == -FDT_ERR_NOTFOUND)
		वापस false;

	p = of_get_flat_dt_prop(chosen, "bootargs", शून्य);
	अगर (!p)
		वापस false;

	अगर (म_माला(p, "dt_cpu_ftrs=off"))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक __init fdt_find_cpu_features(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
					पूर्णांक depth, व्योम *data)
अणु
	अगर (of_flat_dt_is_compatible(node, "ibm,powerpc-cpu-features")
	    && of_get_flat_dt_prop(node, "isa", शून्य))
		वापस 1;

	वापस 0;
पूर्ण

bool __init dt_cpu_ftrs_in_use(व्योम)
अणु
	वापस using_dt_cpu_ftrs;
पूर्ण

bool __init dt_cpu_ftrs_init(व्योम *fdt)
अणु
	using_dt_cpu_ftrs = false;

	/* Setup and verअगरy the FDT, अगर it fails we just bail */
	अगर (!early_init_dt_verअगरy(fdt))
		वापस false;

	अगर (!of_scan_flat_dt(fdt_find_cpu_features, शून्य))
		वापस false;

	अगर (disabled_on_cmdline())
		वापस false;

	cpufeatures_setup_cpu();

	using_dt_cpu_ftrs = true;
	वापस true;
पूर्ण

अटल पूर्णांक nr_dt_cpu_features;
अटल काष्ठा dt_cpu_feature *dt_cpu_features;

अटल पूर्णांक __init process_cpufeatures_node(अचिन्हित दीर्घ node,
					  स्थिर अक्षर *uname, पूर्णांक i)
अणु
	स्थिर __be32 *prop;
	काष्ठा dt_cpu_feature *f;
	पूर्णांक len;

	f = &dt_cpu_features[i];

	f->node = node;

	f->name = uname;

	prop = of_get_flat_dt_prop(node, "isa", &len);
	अगर (!prop) अणु
		pr_warn("%s: missing isa property\n", uname);
		वापस 0;
	पूर्ण
	f->isa = be32_to_cpup(prop);

	prop = of_get_flat_dt_prop(node, "usable-privilege", &len);
	अगर (!prop) अणु
		pr_warn("%s: missing usable-privilege property", uname);
		वापस 0;
	पूर्ण
	f->usable_privilege = be32_to_cpup(prop);

	prop = of_get_flat_dt_prop(node, "hv-support", &len);
	अगर (prop)
		f->hv_support = be32_to_cpup(prop);
	अन्यथा
		f->hv_support = HV_SUPPORT_NONE;

	prop = of_get_flat_dt_prop(node, "os-support", &len);
	अगर (prop)
		f->os_support = be32_to_cpup(prop);
	अन्यथा
		f->os_support = OS_SUPPORT_NONE;

	prop = of_get_flat_dt_prop(node, "hfscr-bit-nr", &len);
	अगर (prop)
		f->hfscr_bit_nr = be32_to_cpup(prop);
	अन्यथा
		f->hfscr_bit_nr = -1;
	prop = of_get_flat_dt_prop(node, "fscr-bit-nr", &len);
	अगर (prop)
		f->fscr_bit_nr = be32_to_cpup(prop);
	अन्यथा
		f->fscr_bit_nr = -1;
	prop = of_get_flat_dt_prop(node, "hwcap-bit-nr", &len);
	अगर (prop)
		f->hwcap_bit_nr = be32_to_cpup(prop);
	अन्यथा
		f->hwcap_bit_nr = -1;

	अगर (f->usable_privilege & USABLE_HV) अणु
		अगर (!(mfmsr() & MSR_HV)) अणु
			pr_warn("%s: HV feature passed to guest\n", uname);
			वापस 0;
		पूर्ण

		अगर (f->hv_support == HV_SUPPORT_NONE && f->hfscr_bit_nr != -1) अणु
			pr_warn("%s: unwanted hfscr_bit_nr\n", uname);
			वापस 0;
		पूर्ण

		अगर (f->hv_support == HV_SUPPORT_HFSCR) अणु
			अगर (f->hfscr_bit_nr == -1) अणु
				pr_warn("%s: missing hfscr_bit_nr\n", uname);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (f->hv_support != HV_SUPPORT_NONE || f->hfscr_bit_nr != -1) अणु
			pr_warn("%s: unwanted hv_support/hfscr_bit_nr\n", uname);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (f->usable_privilege & USABLE_OS) अणु
		अगर (f->os_support == OS_SUPPORT_NONE && f->fscr_bit_nr != -1) अणु
			pr_warn("%s: unwanted fscr_bit_nr\n", uname);
			वापस 0;
		पूर्ण

		अगर (f->os_support == OS_SUPPORT_FSCR) अणु
			अगर (f->fscr_bit_nr == -1) अणु
				pr_warn("%s: missing fscr_bit_nr\n", uname);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (f->os_support != OS_SUPPORT_NONE || f->fscr_bit_nr != -1) अणु
			pr_warn("%s: unwanted os_support/fscr_bit_nr\n", uname);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!(f->usable_privilege & USABLE_PR)) अणु
		अगर (f->hwcap_bit_nr != -1) अणु
			pr_warn("%s: unwanted hwcap_bit_nr\n", uname);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Do all the independent features in the first pass */
	अगर (!of_get_flat_dt_prop(node, "dependencies", &len)) अणु
		अगर (cpufeatures_process_feature(f))
			f->enabled = 1;
		अन्यथा
			f->disabled = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init cpufeatures_deps_enable(काष्ठा dt_cpu_feature *f)
अणु
	स्थिर __be32 *prop;
	पूर्णांक len;
	पूर्णांक nr_deps;
	पूर्णांक i;

	अगर (f->enabled || f->disabled)
		वापस;

	prop = of_get_flat_dt_prop(f->node, "dependencies", &len);
	अगर (!prop) अणु
		pr_warn("%s: missing dependencies property", f->name);
		वापस;
	पूर्ण

	nr_deps = len / माप(पूर्णांक);

	क्रम (i = 0; i < nr_deps; i++) अणु
		अचिन्हित दीर्घ phandle = be32_to_cpu(prop[i]);
		पूर्णांक j;

		क्रम (j = 0; j < nr_dt_cpu_features; j++) अणु
			काष्ठा dt_cpu_feature *d = &dt_cpu_features[j];

			अगर (of_get_flat_dt_phandle(d->node) == phandle) अणु
				cpufeatures_deps_enable(d);
				अगर (d->disabled) अणु
					f->disabled = 1;
					वापस;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cpufeatures_process_feature(f))
		f->enabled = 1;
	अन्यथा
		f->disabled = 1;
पूर्ण

अटल पूर्णांक __init scan_cpufeatures_subnodes(अचिन्हित दीर्घ node,
					  स्थिर अक्षर *uname,
					  व्योम *data)
अणु
	पूर्णांक *count = data;

	process_cpufeatures_node(node, uname, *count);

	(*count)++;

	वापस 0;
पूर्ण

अटल पूर्णांक __init count_cpufeatures_subnodes(अचिन्हित दीर्घ node,
					  स्थिर अक्षर *uname,
					  व्योम *data)
अणु
	पूर्णांक *count = data;

	(*count)++;

	वापस 0;
पूर्ण

अटल पूर्णांक __init dt_cpu_ftrs_scan_callback(अचिन्हित दीर्घ node, स्थिर अक्षर
					    *uname, पूर्णांक depth, व्योम *data)
अणु
	स्थिर __be32 *prop;
	पूर्णांक count, i;
	u32 isa;

	/* We are scanning "ibm,powerpc-cpu-features" nodes only */
	अगर (!of_flat_dt_is_compatible(node, "ibm,powerpc-cpu-features"))
		वापस 0;

	prop = of_get_flat_dt_prop(node, "isa", शून्य);
	अगर (!prop)
		/* We checked beक्रमe, "can't happen" */
		वापस 0;

	isa = be32_to_cpup(prop);

	/* Count and allocate space क्रम cpu features */
	of_scan_flat_dt_subnodes(node, count_cpufeatures_subnodes,
						&nr_dt_cpu_features);
	dt_cpu_features = memblock_alloc(माप(काष्ठा dt_cpu_feature) * nr_dt_cpu_features, PAGE_SIZE);
	अगर (!dt_cpu_features)
		panic("%s: Failed to allocate %zu bytes align=0x%lx\n",
		      __func__,
		      माप(काष्ठा dt_cpu_feature) * nr_dt_cpu_features,
		      PAGE_SIZE);

	cpufeatures_setup_start(isa);

	/* Scan nodes पूर्णांकo dt_cpu_features and enable those without deps  */
	count = 0;
	of_scan_flat_dt_subnodes(node, scan_cpufeatures_subnodes, &count);

	/* Recursive enable reमुख्यing features with dependencies */
	क्रम (i = 0; i < nr_dt_cpu_features; i++) अणु
		काष्ठा dt_cpu_feature *f = &dt_cpu_features[i];

		cpufeatures_deps_enable(f);
	पूर्ण

	prop = of_get_flat_dt_prop(node, "display-name", शून्य);
	अगर (prop && म_माप((अक्षर *)prop) != 0) अणु
		strlcpy(dt_cpu_name, (अक्षर *)prop, माप(dt_cpu_name));
		cur_cpu_spec->cpu_name = dt_cpu_name;
	पूर्ण

	cpufeatures_setup_finished();

	memblock_मुक्त(__pa(dt_cpu_features),
			माप(काष्ठा dt_cpu_feature)*nr_dt_cpu_features);

	वापस 0;
पूर्ण

व्योम __init dt_cpu_ftrs_scan(व्योम)
अणु
	अगर (!using_dt_cpu_ftrs)
		वापस;

	of_scan_flat_dt(dt_cpu_ftrs_scan_callback, शून्य);
पूर्ण

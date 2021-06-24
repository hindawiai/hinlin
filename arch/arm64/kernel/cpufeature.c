<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Contains CPU feature definitions
 *
 * Copyright (C) 2015 ARM Ltd.
 *
 * A note क्रम the weary kernel hacker: the code here is confusing and hard to
 * follow! That's partly because it's solving a nasty problem, but also because
 * there's a little bit of over-abstraction that tends to obscure what's going
 * on behind a maze of helper functions and macros.
 *
 * The basic problem is that hardware folks have started gluing together CPUs
 * with distinct architectural features; in some हालs even creating SoCs where
 * user-visible inकाष्ठाions are available only on a subset of the available
 * cores. We try to address this by snapshotting the feature रेजिस्टरs of the
 * boot CPU and comparing these with the feature रेजिस्टरs of each secondary
 * CPU when bringing them up. If there is a mismatch, then we update the
 * snapshot state to indicate the lowest-common denominator of the feature,
 * known as the "safe" value. This snapshot state can be queried to view the
 * "sanitised" value of a feature रेजिस्टर.
 *
 * The sanitised रेजिस्टर values are used to decide which capabilities we
 * have in the प्रणाली. These may be in the क्रमm of traditional "hwcaps"
 * advertised to userspace or पूर्णांकernal "cpucaps" which are used to configure
 * things like alternative patching and अटल keys. While a feature mismatch
 * may result in a TAINT_CPU_OUT_OF_SPEC kernel taपूर्णांक, a capability mismatch
 * may prevent a CPU from being onlined at all.
 *
 * Some implementation details worth remembering:
 *
 * - Mismatched features are *always* sanitised to a "safe" value, which
 *   usually indicates that the feature is not supported.
 *
 * - A mismatched feature marked with FTR_STRICT will cause a "SANITY CHECK"
 *   warning when onlining an offending CPU and the kernel will be taपूर्णांकed
 *   with TAINT_CPU_OUT_OF_SPEC.
 *
 * - Features marked as FTR_VISIBLE have their sanitised value visible to
 *   userspace. FTR_VISIBLE features in रेजिस्टरs that are only visible
 *   to EL0 by trapping *must* have a corresponding HWCAP so that late
 *   onlining of CPUs cannot lead to features disappearing at runसमय.
 *
 * - A "feature" is typically a 4-bit रेजिस्टर field. A "capability" is the
 *   high-level description derived from the sanitised field value.
 *
 * - Read the Arm ARM (DDI 0487F.a) section D13.1.3 ("Principles of the ID
 *   scheme क्रम fields in ID रेजिस्टरs") to understand when feature fields
 *   may be चिन्हित or अचिन्हित (FTR_SIGNED and FTR_UNSIGNED accordingly).
 *
 * - KVM exposes its own view of the feature रेजिस्टरs to guest operating
 *   प्रणालीs regardless of FTR_VISIBLE. This is typically driven from the
 *   sanitised रेजिस्टर values to allow भव CPUs to be migrated between
 *   arbitrary physical CPUs, but some features not present on the host are
 *   also advertised and emulated. Look at sys_reg_descs[] क्रम the gory
 *   details.
 *
 * - If the arm64_ftr_bits[] क्रम a रेजिस्टर has a missing field, then this
 *   field is treated as STRICT RES0, including क्रम पढ़ो_sanitised_ftr_reg().
 *   This is stronger than FTR_HIDDEN and can be used to hide features from
 *   KVM guests.
 */

#घोषणा pr_fmt(fmt) "CPU features: " fmt

#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/sort.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/types.h>
#समावेश <linux/minmax.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/kasan.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/kvm_host.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mte.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/virt.h>

/* Kernel representation of AT_HWCAP and AT_HWCAP2 */
अटल अचिन्हित दीर्घ elf_hwcap __पढ़ो_mostly;

#अगर_घोषित CONFIG_COMPAT
#घोषणा COMPAT_ELF_HWCAP_DEFAULT	\
				(COMPAT_HWCAP_HALF|COMPAT_HWCAP_THUMB|\
				 COMPAT_HWCAP_FAST_MULT|COMPAT_HWCAP_EDSP|\
				 COMPAT_HWCAP_TLS|COMPAT_HWCAP_IDIV|\
				 COMPAT_HWCAP_LPAE)
अचिन्हित पूर्णांक compat_elf_hwcap __पढ़ो_mostly = COMPAT_ELF_HWCAP_DEFAULT;
अचिन्हित पूर्णांक compat_elf_hwcap2 __पढ़ो_mostly;
#पूर्ण_अगर

DECLARE_BITMAP(cpu_hwcaps, ARM64_NCAPS);
EXPORT_SYMBOL(cpu_hwcaps);
अटल काष्ठा arm64_cpu_capabilities स्थिर __ro_after_init *cpu_hwcaps_ptrs[ARM64_NCAPS];

/* Need also bit क्रम ARM64_CB_PATCH */
DECLARE_BITMAP(boot_capabilities, ARM64_NPATCHABLE);

bool arm64_use_ng_mappings = false;
EXPORT_SYMBOL(arm64_use_ng_mappings);

/*
 * Flag to indicate अगर we have computed the प्रणाली wide
 * capabilities based on the boot समय active CPUs. This
 * will be used to determine अगर a new booting CPU should
 * go through the verअगरication process to make sure that it
 * supports the प्रणाली capabilities, without using a hotplug
 * notअगरier. This is also used to decide अगर we could use
 * the fast path क्रम checking स्थिरant CPU caps.
 */
DEFINE_STATIC_KEY_FALSE(arm64_स्थिर_caps_पढ़ोy);
EXPORT_SYMBOL(arm64_स्थिर_caps_पढ़ोy);
अटल अंतरभूत व्योम finalize_प्रणाली_capabilities(व्योम)
अणु
	अटल_branch_enable(&arm64_स्थिर_caps_पढ़ोy);
पूर्ण

व्योम dump_cpu_features(व्योम)
अणु
	/* file-wide pr_fmt adds "CPU features: " prefix */
	pr_emerg("0x%*pb\n", ARM64_NCAPS, &cpu_hwcaps);
पूर्ण

DEFINE_STATIC_KEY_ARRAY_FALSE(cpu_hwcap_keys, ARM64_NCAPS);
EXPORT_SYMBOL(cpu_hwcap_keys);

#घोषणा __ARM64_FTR_BITS(SIGNED, VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL) \
	अणु						\
		.sign = SIGNED,				\
		.visible = VISIBLE,			\
		.strict = STRICT,			\
		.type = TYPE,				\
		.shअगरt = SHIFT,				\
		.width = WIDTH,				\
		.safe_val = SAFE_VAL,			\
	पूर्ण

/* Define a feature with अचिन्हित values */
#घोषणा ARM64_FTR_BITS(VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL) \
	__ARM64_FTR_BITS(FTR_UNSIGNED, VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL)

/* Define a feature with a चिन्हित value */
#घोषणा S_ARM64_FTR_BITS(VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL) \
	__ARM64_FTR_BITS(FTR_SIGNED, VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL)

#घोषणा ARM64_FTR_END					\
	अणु						\
		.width = 0,				\
	पूर्ण

अटल व्योम cpu_enable_cnp(काष्ठा arm64_cpu_capabilities स्थिर *cap);

अटल bool __प्रणाली_matches_cap(अचिन्हित पूर्णांक n);

/*
 * NOTE: Any changes to the visibility of features should be kept in
 * sync with the करोcumentation of the CPU feature रेजिस्टर ABI.
 */
अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64isar0[] = अणु
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_RNDR_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_TLB_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_TS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_FHM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_DP_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_SM4_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_SM3_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_SHA3_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_RDM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_ATOMICS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_CRC32_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_SHA2_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_SHA1_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR0_AES_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64isar1[] = अणु
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_I8MM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_DGH_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_BF16_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_SPECRES_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_SB_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_FRINTTS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_PTR_AUTH),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_GPI_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_PTR_AUTH),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_GPA_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_LRCPC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_FCMA_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_JSCVT_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_PTR_AUTH),
		       FTR_STRICT, FTR_EXACT, ID_AA64ISAR1_API_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_PTR_AUTH),
		       FTR_STRICT, FTR_EXACT, ID_AA64ISAR1_APA_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ISAR1_DPB_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64pfr0[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR0_CSV3_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR0_CSV2_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR0_DIT_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR0_AMU_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR0_MPAM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR0_SEL2_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
				   FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR0_SVE_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR0_RAS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR0_GIC_SHIFT, 4, 0),
	S_ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR0_ASIMD_SHIFT, 4, ID_AA64PFR0_ASIMD_NI),
	S_ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR0_FP_SHIFT, 4, ID_AA64PFR0_FP_NI),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR0_EL3_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR0_EL2_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR0_EL1_SHIFT, 4, ID_AA64PFR0_EL1_64BIT_ONLY),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR0_EL0_SHIFT, 4, ID_AA64PFR0_EL0_64BIT_ONLY),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64pfr1[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR1_MPAMFRAC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR1_RASFRAC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_MTE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR1_MTE_SHIFT, 4, ID_AA64PFR1_MTE_NI),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64PFR1_SSBS_SHIFT, 4, ID_AA64PFR1_SSBS_PSTATE_NI),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_BTI),
				    FTR_STRICT, FTR_LOWER_SAFE, ID_AA64PFR1_BT_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64zfr0[] = अणु
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_F64MM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_F32MM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_I8MM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_SM4_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_SHA3_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_BF16_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_BITPERM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_AES_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE_IF_IS_ENABLED(CONFIG_ARM64_SVE),
		       FTR_STRICT, FTR_LOWER_SAFE, ID_AA64ZFR0_SVEVER_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64mmfr0[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_ECV_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_FGT_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_EXS_SHIFT, 4, 0),
	/*
	 * Page size not being supported at Stage-2 is not fatal. You
	 * just give up KVM अगर PAGE_SIZE isn't supported there. Go fix
	 * your favourite nesting hypervisor.
	 *
	 * There is a small corner हाल where the hypervisor explicitly
	 * advertises a given granule size at Stage-2 (value 2) on some
	 * vCPUs, and uses the fallback to Stage-1 (value 0) क्रम other
	 * vCPUs. Although this is not क्रमbidden by the architecture, it
	 * indicates that the hypervisor is being silly (or buggy).
	 *
	 * We make no efक्रमt to cope with this and pretend that अगर these
	 * fields are inconsistent across vCPUs, then it isn't worth
	 * trying to bring KVM up.
	 */
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_EXACT, ID_AA64MMFR0_TGRAN4_2_SHIFT, 4, 1),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_EXACT, ID_AA64MMFR0_TGRAN64_2_SHIFT, 4, 1),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_EXACT, ID_AA64MMFR0_TGRAN16_2_SHIFT, 4, 1),
	/*
	 * We alपढ़ोy refuse to boot CPUs that करोn't support our configured
	 * page size, so we can only detect mismatches क्रम a page size other
	 * than the one we're currently using. Unक्रमtunately, SoCs like this
	 * exist in the wild so, even though we करोn't like it, we'll have to go
	 * aदीर्घ with it and treat them as non-strict.
	 */
	S_ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_TGRAN4_SHIFT, 4, ID_AA64MMFR0_TGRAN4_NI),
	S_ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_TGRAN64_SHIFT, 4, ID_AA64MMFR0_TGRAN64_NI),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_TGRAN16_SHIFT, 4, ID_AA64MMFR0_TGRAN16_NI),

	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_BIGENDEL0_SHIFT, 4, 0),
	/* Linux shouldn't care about secure memory */
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_SNSMEM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_BIGENDEL_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_ASID_SHIFT, 4, 0),
	/*
	 * Dअगरfering PARange is fine as दीर्घ as all peripherals and memory are mapped
	 * within the minimum PARange of all CPUs
	 */
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64MMFR0_PARANGE_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64mmfr1[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_ETS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_TWED_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_XNX_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_HIGHER_SAFE, ID_AA64MMFR1_SPECSEI_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_PAN_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_LOR_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_HPD_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_VHE_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_VMIDBITS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR1_HADBS_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64mmfr2[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_E0PD_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_EVT_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_BBM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_TTL_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_FWB_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_IDS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_AT_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_ST_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_NV_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_CCIDX_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_LVA_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_IESB_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_LSM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_UAO_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64MMFR2_CNP_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_ctr[] = अणु
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_EXACT, 31, 1, 1), /* RES1 */
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, CTR_DIC_SHIFT, 1, 1),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, CTR_IDC_SHIFT, 1, 1),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_HIGHER_OR_ZERO_SAFE, CTR_CWG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_HIGHER_OR_ZERO_SAFE, CTR_ERG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, CTR_DMINLINE_SHIFT, 4, 1),
	/*
	 * Linux can handle dअगरfering I-cache policies. Userspace JITs will
	 * make use of *minLine.
	 * If we have dअगरfering I-cache policies, report it as the weakest - VIPT.
	 */
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_NONSTRICT, FTR_EXACT, CTR_L1IP_SHIFT, 2, ICACHE_POLICY_VIPT),	/* L1Ip */
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, CTR_IMINLINE_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल काष्ठा arm64_ftr_override __ro_after_init no_override = अणु पूर्ण;

काष्ठा arm64_ftr_reg arm64_ftr_reg_ctrel0 = अणु
	.name		= "SYS_CTR_EL0",
	.ftr_bits	= ftr_ctr,
	.override	= &no_override,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_mmfr0[] = अणु
	S_ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR0_INNERSHR_SHIFT, 4, 0xf),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR0_FCSE_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_MMFR0_AUXREG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR0_TCM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR0_SHARELVL_SHIFT, 4, 0),
	S_ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR0_OUTERSHR_SHIFT, 4, 0xf),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR0_PMSA_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR0_VMSA_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_aa64dfr0[] = अणु
	S_ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64DFR0_DOUBLELOCK_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_AA64DFR0_PMSVER_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64DFR0_CTX_CMPS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64DFR0_WRPS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_AA64DFR0_BRPS_SHIFT, 4, 0),
	/*
	 * We can instantiate multiple PMU instances with dअगरferent levels
	 * of support.
	 */
	S_ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_EXACT, ID_AA64DFR0_PMUVER_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_EXACT, ID_AA64DFR0_DEBUGVER_SHIFT, 4, 0x6),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_mvfr2[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, MVFR2_FPMISC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, MVFR2_SIMDMISC_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_dczid[] = अणु
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_EXACT, DCZID_DZP_SHIFT, 1, 1),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, DCZID_BS_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_isar0[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR0_DIVIDE_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR0_DEBUG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR0_COPROC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR0_CMPBRANCH_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR0_BITFIELD_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR0_BITCOUNT_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR0_SWAP_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_isar5[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR5_RDM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR5_CRC32_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR5_SHA2_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR5_SHA1_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR5_AES_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR5_SEVL_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_mmfr4[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR4_EVT_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR4_CCIDX_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR4_LSM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR4_HPDS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR4_CNP_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR4_XNX_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR4_AC2_SHIFT, 4, 0),

	/*
	 * SpecSEI = 1 indicates that the PE might generate an SError on an
	 * बाह्यal पात on speculative पढ़ो. It is safe to assume that an
	 * SError might be generated than it will not be. Hence it has been
	 * classअगरied as FTR_HIGHER_SAFE.
	 */
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_HIGHER_SAFE, ID_MMFR4_SPECSEI_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_isar4[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR4_SWP_FRAC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR4_PSR_M_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR4_SYNCH_PRIM_FRAC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR4_BARRIER_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR4_SMC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR4_WRITEBACK_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR4_WITHSHIFTS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR4_UNPRIV_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_mmfr5[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_MMFR5_ETS_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_isar6[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR6_I8MM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR6_BF16_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR6_SPECRES_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR6_SB_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR6_FHM_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR6_DP_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_ISAR6_JSCVT_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_pfr0[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR0_DIT_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_PFR0_CSV2_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR0_STATE3_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR0_STATE2_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR0_STATE1_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR0_STATE0_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_pfr1[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR1_GIC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR1_VIRT_FRAC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR1_SEC_FRAC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR1_GENTIMER_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR1_VIRTUALIZATION_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR1_MPROGMOD_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR1_SECURITY_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_PFR1_PROGMOD_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_pfr2[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_PFR2_SSBS_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE, ID_PFR2_CSV3_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_dfr0[] = अणु
	/* [31:28] TraceFilt */
	S_ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_DFR0_PERFMON_SHIFT, 4, 0xf),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_DFR0_MPROFDBG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_DFR0_MMAPTRC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_DFR0_COPTRC_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_DFR0_MMAPDBG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_DFR0_COPSDBG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_DFR0_COPDBG_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_id_dfr1[] = अणु
	S_ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, ID_DFR1_MTPMU_SHIFT, 4, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_zcr[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_NONSTRICT, FTR_LOWER_SAFE,
		ZCR_ELx_LEN_SHIFT, ZCR_ELx_LEN_SIZE, 0),	/* LEN */
	ARM64_FTR_END,
पूर्ण;

/*
 * Common ftr bits क्रम a 32bit रेजिस्टर with all hidden, strict
 * attributes, with 4bit feature fields and a शेष safe value of
 * 0. Covers the following 32bit रेजिस्टरs:
 * id_isar[1-4], id_mmfr[1-3], id_pfr1, mvfr[0-1]
 */
अटल स्थिर काष्ठा arm64_ftr_bits ftr_generic_32bits[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, 28, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, 24, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, 20, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, 16, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, 12, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, 8, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, 4, 4, 0),
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_LOWER_SAFE, 0, 4, 0),
	ARM64_FTR_END,
पूर्ण;

/* Table क्रम a single 32bit feature value */
अटल स्थिर काष्ठा arm64_ftr_bits ftr_single32[] = अणु
	ARM64_FTR_BITS(FTR_HIDDEN, FTR_STRICT, FTR_EXACT, 0, 32, 0),
	ARM64_FTR_END,
पूर्ण;

अटल स्थिर काष्ठा arm64_ftr_bits ftr_raz[] = अणु
	ARM64_FTR_END,
पूर्ण;

#घोषणा ARM64_FTR_REG_OVERRIDE(id, table, ovr) अणु		\
		.sys_id = id,					\
		.reg = 	&(काष्ठा arm64_ftr_reg)अणु		\
			.name = #id,				\
			.override = (ovr),			\
			.ftr_bits = &((table)[0]),		\
	पूर्णपूर्ण

#घोषणा ARM64_FTR_REG(id, table) ARM64_FTR_REG_OVERRIDE(id, table, &no_override)

काष्ठा arm64_ftr_override __ro_after_init id_aa64mmfr1_override;
काष्ठा arm64_ftr_override __ro_after_init id_aa64pfr1_override;
काष्ठा arm64_ftr_override __ro_after_init id_aa64isar1_override;

अटल स्थिर काष्ठा __ftr_reg_entry अणु
	u32			sys_id;
	काष्ठा arm64_ftr_reg 	*reg;
पूर्ण arm64_ftr_regs[] = अणु

	/* Op1 = 0, CRn = 0, CRm = 1 */
	ARM64_FTR_REG(SYS_ID_PFR0_EL1, ftr_id_pfr0),
	ARM64_FTR_REG(SYS_ID_PFR1_EL1, ftr_id_pfr1),
	ARM64_FTR_REG(SYS_ID_DFR0_EL1, ftr_id_dfr0),
	ARM64_FTR_REG(SYS_ID_MMFR0_EL1, ftr_id_mmfr0),
	ARM64_FTR_REG(SYS_ID_MMFR1_EL1, ftr_generic_32bits),
	ARM64_FTR_REG(SYS_ID_MMFR2_EL1, ftr_generic_32bits),
	ARM64_FTR_REG(SYS_ID_MMFR3_EL1, ftr_generic_32bits),

	/* Op1 = 0, CRn = 0, CRm = 2 */
	ARM64_FTR_REG(SYS_ID_ISAR0_EL1, ftr_id_isar0),
	ARM64_FTR_REG(SYS_ID_ISAR1_EL1, ftr_generic_32bits),
	ARM64_FTR_REG(SYS_ID_ISAR2_EL1, ftr_generic_32bits),
	ARM64_FTR_REG(SYS_ID_ISAR3_EL1, ftr_generic_32bits),
	ARM64_FTR_REG(SYS_ID_ISAR4_EL1, ftr_id_isar4),
	ARM64_FTR_REG(SYS_ID_ISAR5_EL1, ftr_id_isar5),
	ARM64_FTR_REG(SYS_ID_MMFR4_EL1, ftr_id_mmfr4),
	ARM64_FTR_REG(SYS_ID_ISAR6_EL1, ftr_id_isar6),

	/* Op1 = 0, CRn = 0, CRm = 3 */
	ARM64_FTR_REG(SYS_MVFR0_EL1, ftr_generic_32bits),
	ARM64_FTR_REG(SYS_MVFR1_EL1, ftr_generic_32bits),
	ARM64_FTR_REG(SYS_MVFR2_EL1, ftr_mvfr2),
	ARM64_FTR_REG(SYS_ID_PFR2_EL1, ftr_id_pfr2),
	ARM64_FTR_REG(SYS_ID_DFR1_EL1, ftr_id_dfr1),
	ARM64_FTR_REG(SYS_ID_MMFR5_EL1, ftr_id_mmfr5),

	/* Op1 = 0, CRn = 0, CRm = 4 */
	ARM64_FTR_REG(SYS_ID_AA64PFR0_EL1, ftr_id_aa64pfr0),
	ARM64_FTR_REG_OVERRIDE(SYS_ID_AA64PFR1_EL1, ftr_id_aa64pfr1,
			       &id_aa64pfr1_override),
	ARM64_FTR_REG(SYS_ID_AA64ZFR0_EL1, ftr_id_aa64zfr0),

	/* Op1 = 0, CRn = 0, CRm = 5 */
	ARM64_FTR_REG(SYS_ID_AA64DFR0_EL1, ftr_id_aa64dfr0),
	ARM64_FTR_REG(SYS_ID_AA64DFR1_EL1, ftr_raz),

	/* Op1 = 0, CRn = 0, CRm = 6 */
	ARM64_FTR_REG(SYS_ID_AA64ISAR0_EL1, ftr_id_aa64isar0),
	ARM64_FTR_REG_OVERRIDE(SYS_ID_AA64ISAR1_EL1, ftr_id_aa64isar1,
			       &id_aa64isar1_override),

	/* Op1 = 0, CRn = 0, CRm = 7 */
	ARM64_FTR_REG(SYS_ID_AA64MMFR0_EL1, ftr_id_aa64mmfr0),
	ARM64_FTR_REG_OVERRIDE(SYS_ID_AA64MMFR1_EL1, ftr_id_aa64mmfr1,
			       &id_aa64mmfr1_override),
	ARM64_FTR_REG(SYS_ID_AA64MMFR2_EL1, ftr_id_aa64mmfr2),

	/* Op1 = 0, CRn = 1, CRm = 2 */
	ARM64_FTR_REG(SYS_ZCR_EL1, ftr_zcr),

	/* Op1 = 3, CRn = 0, CRm = 0 */
	अणु SYS_CTR_EL0, &arm64_ftr_reg_ctrel0 पूर्ण,
	ARM64_FTR_REG(SYS_DCZID_EL0, ftr_dczid),

	/* Op1 = 3, CRn = 14, CRm = 0 */
	ARM64_FTR_REG(SYS_CNTFRQ_EL0, ftr_single32),
पूर्ण;

अटल पूर्णांक search_cmp_ftr_reg(स्थिर व्योम *id, स्थिर व्योम *regp)
अणु
	वापस (पूर्णांक)(अचिन्हित दीर्घ)id - (पूर्णांक)((स्थिर काष्ठा __ftr_reg_entry *)regp)->sys_id;
पूर्ण

/*
 * get_arm64_ftr_reg_nowarn - Looks up a feature रेजिस्टर entry using
 * its sys_reg() encoding. With the array arm64_ftr_regs sorted in the
 * ascending order of sys_id, we use binary search to find a matching
 * entry.
 *
 * वापसs - Upon success,  matching ftr_reg entry क्रम id.
 *         - शून्य on failure. It is upto the caller to decide
 *	     the impact of a failure.
 */
अटल काष्ठा arm64_ftr_reg *get_arm64_ftr_reg_nowarn(u32 sys_id)
अणु
	स्थिर काष्ठा __ftr_reg_entry *ret;

	ret = द्वा_खोज((स्थिर व्योम *)(अचिन्हित दीर्घ)sys_id,
			arm64_ftr_regs,
			ARRAY_SIZE(arm64_ftr_regs),
			माप(arm64_ftr_regs[0]),
			search_cmp_ftr_reg);
	अगर (ret)
		वापस ret->reg;
	वापस शून्य;
पूर्ण

/*
 * get_arm64_ftr_reg - Looks up a feature रेजिस्टर entry using
 * its sys_reg() encoding. This calls get_arm64_ftr_reg_nowarn().
 *
 * वापसs - Upon success,  matching ftr_reg entry क्रम id.
 *         - शून्य on failure but with an WARN_ON().
 */
अटल काष्ठा arm64_ftr_reg *get_arm64_ftr_reg(u32 sys_id)
अणु
	काष्ठा arm64_ftr_reg *reg;

	reg = get_arm64_ftr_reg_nowarn(sys_id);

	/*
	 * Requesting a non-existent रेजिस्टर search is an error. Warn
	 * and let the caller handle it.
	 */
	WARN_ON(!reg);
	वापस reg;
पूर्ण

अटल u64 arm64_ftr_set_value(स्थिर काष्ठा arm64_ftr_bits *ftrp, s64 reg,
			       s64 ftr_val)
अणु
	u64 mask = arm64_ftr_mask(ftrp);

	reg &= ~mask;
	reg |= (ftr_val << ftrp->shअगरt) & mask;
	वापस reg;
पूर्ण

अटल s64 arm64_ftr_safe_value(स्थिर काष्ठा arm64_ftr_bits *ftrp, s64 new,
				s64 cur)
अणु
	s64 ret = 0;

	चयन (ftrp->type) अणु
	हाल FTR_EXACT:
		ret = ftrp->safe_val;
		अवरोध;
	हाल FTR_LOWER_SAFE:
		ret = min(new, cur);
		अवरोध;
	हाल FTR_HIGHER_OR_ZERO_SAFE:
		अगर (!cur || !new)
			अवरोध;
		fallthrough;
	हाल FTR_HIGHER_SAFE:
		ret = max(new, cur);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __init sort_ftr_regs(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(arm64_ftr_regs); i++) अणु
		स्थिर काष्ठा arm64_ftr_reg *ftr_reg = arm64_ftr_regs[i].reg;
		स्थिर काष्ठा arm64_ftr_bits *ftr_bits = ftr_reg->ftr_bits;
		अचिन्हित पूर्णांक j = 0;

		/*
		 * Features here must be sorted in descending order with respect
		 * to their shअगरt values and should not overlap with each other.
		 */
		क्रम (; ftr_bits->width != 0; ftr_bits++, j++) अणु
			अचिन्हित पूर्णांक width = ftr_reg->ftr_bits[j].width;
			अचिन्हित पूर्णांक shअगरt = ftr_reg->ftr_bits[j].shअगरt;
			अचिन्हित पूर्णांक prev_shअगरt;

			WARN((shअगरt  + width) > 64,
				"%s has invalid feature at shift %d\n",
				ftr_reg->name, shअगरt);

			/*
			 * Skip the first feature. There is nothing to
			 * compare against क्रम now.
			 */
			अगर (j == 0)
				जारी;

			prev_shअगरt = ftr_reg->ftr_bits[j - 1].shअगरt;
			WARN((shअगरt + width) > prev_shअगरt,
				"%s has feature overlap at shift %d\n",
				ftr_reg->name, shअगरt);
		पूर्ण

		/*
		 * Skip the first रेजिस्टर. There is nothing to
		 * compare against क्रम now.
		 */
		अगर (i == 0)
			जारी;
		/*
		 * Registers here must be sorted in ascending order with respect
		 * to sys_id क्रम subsequent binary search in get_arm64_ftr_reg()
		 * to work correctly.
		 */
		BUG_ON(arm64_ftr_regs[i].sys_id < arm64_ftr_regs[i - 1].sys_id);
	पूर्ण
पूर्ण

/*
 * Initialise the CPU feature रेजिस्टर from Boot CPU values.
 * Also initiliases the strict_mask क्रम the रेजिस्टर.
 * Any bits that are not covered by an arm64_ftr_bits entry are considered
 * RES0 क्रम the प्रणाली-wide value, and must strictly match.
 */
अटल व्योम __init init_cpu_ftr_reg(u32 sys_reg, u64 new)
अणु
	u64 val = 0;
	u64 strict_mask = ~0x0ULL;
	u64 user_mask = 0;
	u64 valid_mask = 0;

	स्थिर काष्ठा arm64_ftr_bits *ftrp;
	काष्ठा arm64_ftr_reg *reg = get_arm64_ftr_reg(sys_reg);

	अगर (!reg)
		वापस;

	क्रम (ftrp = reg->ftr_bits; ftrp->width; ftrp++) अणु
		u64 ftr_mask = arm64_ftr_mask(ftrp);
		s64 ftr_new = arm64_ftr_value(ftrp, new);
		s64 ftr_ovr = arm64_ftr_value(ftrp, reg->override->val);

		अगर ((ftr_mask & reg->override->mask) == ftr_mask) अणु
			s64 पंचांगp = arm64_ftr_safe_value(ftrp, ftr_ovr, ftr_new);
			अक्षर *str = शून्य;

			अगर (ftr_ovr != पंचांगp) अणु
				/* Unsafe, हटाओ the override */
				reg->override->mask &= ~ftr_mask;
				reg->override->val &= ~ftr_mask;
				पंचांगp = ftr_ovr;
				str = "ignoring override";
			पूर्ण अन्यथा अगर (ftr_new != पंचांगp) अणु
				/* Override was valid */
				ftr_new = पंचांगp;
				str = "forced";
			पूर्ण अन्यथा अगर (ftr_ovr == पंचांगp) अणु
				/* Override was the safe value */
				str = "already set";
			पूर्ण

			अगर (str)
				pr_warn("%s[%d:%d]: %s to %llx\n",
					reg->name,
					ftrp->shअगरt + ftrp->width - 1,
					ftrp->shअगरt, str, पंचांगp);
		पूर्ण अन्यथा अगर ((ftr_mask & reg->override->val) == ftr_mask) अणु
			reg->override->val &= ~ftr_mask;
			pr_warn("%s[%d:%d]: impossible override, ignored\n",
				reg->name,
				ftrp->shअगरt + ftrp->width - 1,
				ftrp->shअगरt);
		पूर्ण

		val = arm64_ftr_set_value(ftrp, val, ftr_new);

		valid_mask |= ftr_mask;
		अगर (!ftrp->strict)
			strict_mask &= ~ftr_mask;
		अगर (ftrp->visible)
			user_mask |= ftr_mask;
		अन्यथा
			reg->user_val = arm64_ftr_set_value(ftrp,
							    reg->user_val,
							    ftrp->safe_val);
	पूर्ण

	val &= valid_mask;

	reg->sys_val = val;
	reg->strict_mask = strict_mask;
	reg->user_mask = user_mask;
पूर्ण

बाह्य स्थिर काष्ठा arm64_cpu_capabilities arm64_errata[];
अटल स्थिर काष्ठा arm64_cpu_capabilities arm64_features[];

अटल व्योम __init
init_cpu_hwcaps_indirect_list_from_array(स्थिर काष्ठा arm64_cpu_capabilities *caps)
अणु
	क्रम (; caps->matches; caps++) अणु
		अगर (WARN(caps->capability >= ARM64_NCAPS,
			"Invalid capability %d\n", caps->capability))
			जारी;
		अगर (WARN(cpu_hwcaps_ptrs[caps->capability],
			"Duplicate entry for capability %d\n",
			caps->capability))
			जारी;
		cpu_hwcaps_ptrs[caps->capability] = caps;
	पूर्ण
पूर्ण

अटल व्योम __init init_cpu_hwcaps_indirect_list(व्योम)
अणु
	init_cpu_hwcaps_indirect_list_from_array(arm64_features);
	init_cpu_hwcaps_indirect_list_from_array(arm64_errata);
पूर्ण

अटल व्योम __init setup_boot_cpu_capabilities(व्योम);

व्योम __init init_cpu_features(काष्ठा cpuinfo_arm64 *info)
अणु
	/* Beक्रमe we start using the tables, make sure it is sorted */
	sort_ftr_regs();

	init_cpu_ftr_reg(SYS_CTR_EL0, info->reg_ctr);
	init_cpu_ftr_reg(SYS_DCZID_EL0, info->reg_dczid);
	init_cpu_ftr_reg(SYS_CNTFRQ_EL0, info->reg_cntfrq);
	init_cpu_ftr_reg(SYS_ID_AA64DFR0_EL1, info->reg_id_aa64dfr0);
	init_cpu_ftr_reg(SYS_ID_AA64DFR1_EL1, info->reg_id_aa64dfr1);
	init_cpu_ftr_reg(SYS_ID_AA64ISAR0_EL1, info->reg_id_aa64isar0);
	init_cpu_ftr_reg(SYS_ID_AA64ISAR1_EL1, info->reg_id_aa64isar1);
	init_cpu_ftr_reg(SYS_ID_AA64MMFR0_EL1, info->reg_id_aa64mmfr0);
	init_cpu_ftr_reg(SYS_ID_AA64MMFR1_EL1, info->reg_id_aa64mmfr1);
	init_cpu_ftr_reg(SYS_ID_AA64MMFR2_EL1, info->reg_id_aa64mmfr2);
	init_cpu_ftr_reg(SYS_ID_AA64PFR0_EL1, info->reg_id_aa64pfr0);
	init_cpu_ftr_reg(SYS_ID_AA64PFR1_EL1, info->reg_id_aa64pfr1);
	init_cpu_ftr_reg(SYS_ID_AA64ZFR0_EL1, info->reg_id_aa64zfr0);

	अगर (id_aa64pfr0_32bit_el0(info->reg_id_aa64pfr0)) अणु
		init_cpu_ftr_reg(SYS_ID_DFR0_EL1, info->reg_id_dfr0);
		init_cpu_ftr_reg(SYS_ID_DFR1_EL1, info->reg_id_dfr1);
		init_cpu_ftr_reg(SYS_ID_ISAR0_EL1, info->reg_id_isar0);
		init_cpu_ftr_reg(SYS_ID_ISAR1_EL1, info->reg_id_isar1);
		init_cpu_ftr_reg(SYS_ID_ISAR2_EL1, info->reg_id_isar2);
		init_cpu_ftr_reg(SYS_ID_ISAR3_EL1, info->reg_id_isar3);
		init_cpu_ftr_reg(SYS_ID_ISAR4_EL1, info->reg_id_isar4);
		init_cpu_ftr_reg(SYS_ID_ISAR5_EL1, info->reg_id_isar5);
		init_cpu_ftr_reg(SYS_ID_ISAR6_EL1, info->reg_id_isar6);
		init_cpu_ftr_reg(SYS_ID_MMFR0_EL1, info->reg_id_mmfr0);
		init_cpu_ftr_reg(SYS_ID_MMFR1_EL1, info->reg_id_mmfr1);
		init_cpu_ftr_reg(SYS_ID_MMFR2_EL1, info->reg_id_mmfr2);
		init_cpu_ftr_reg(SYS_ID_MMFR3_EL1, info->reg_id_mmfr3);
		init_cpu_ftr_reg(SYS_ID_MMFR4_EL1, info->reg_id_mmfr4);
		init_cpu_ftr_reg(SYS_ID_MMFR5_EL1, info->reg_id_mmfr5);
		init_cpu_ftr_reg(SYS_ID_PFR0_EL1, info->reg_id_pfr0);
		init_cpu_ftr_reg(SYS_ID_PFR1_EL1, info->reg_id_pfr1);
		init_cpu_ftr_reg(SYS_ID_PFR2_EL1, info->reg_id_pfr2);
		init_cpu_ftr_reg(SYS_MVFR0_EL1, info->reg_mvfr0);
		init_cpu_ftr_reg(SYS_MVFR1_EL1, info->reg_mvfr1);
		init_cpu_ftr_reg(SYS_MVFR2_EL1, info->reg_mvfr2);
	पूर्ण

	अगर (id_aa64pfr0_sve(info->reg_id_aa64pfr0)) अणु
		init_cpu_ftr_reg(SYS_ZCR_EL1, info->reg_zcr);
		sve_init_vq_map();
	पूर्ण

	/*
	 * Initialize the indirect array of CPU hwcaps capabilities poपूर्णांकers
	 * beक्रमe we handle the boot CPU below.
	 */
	init_cpu_hwcaps_indirect_list();

	/*
	 * Detect and enable early CPU capabilities based on the boot CPU,
	 * after we have initialised the CPU feature infraकाष्ठाure.
	 */
	setup_boot_cpu_capabilities();
पूर्ण

अटल व्योम update_cpu_ftr_reg(काष्ठा arm64_ftr_reg *reg, u64 new)
अणु
	स्थिर काष्ठा arm64_ftr_bits *ftrp;

	क्रम (ftrp = reg->ftr_bits; ftrp->width; ftrp++) अणु
		s64 ftr_cur = arm64_ftr_value(ftrp, reg->sys_val);
		s64 ftr_new = arm64_ftr_value(ftrp, new);

		अगर (ftr_cur == ftr_new)
			जारी;
		/* Find a safe value */
		ftr_new = arm64_ftr_safe_value(ftrp, ftr_new, ftr_cur);
		reg->sys_val = arm64_ftr_set_value(ftrp, reg->sys_val, ftr_new);
	पूर्ण

पूर्ण

अटल पूर्णांक check_update_ftr_reg(u32 sys_id, पूर्णांक cpu, u64 val, u64 boot)
अणु
	काष्ठा arm64_ftr_reg *regp = get_arm64_ftr_reg(sys_id);

	अगर (!regp)
		वापस 0;

	update_cpu_ftr_reg(regp, val);
	अगर ((boot & regp->strict_mask) == (val & regp->strict_mask))
		वापस 0;
	pr_warn("SANITY CHECK: Unexpected variation in %s. Boot CPU: %#016llx, CPU%d: %#016llx\n",
			regp->name, boot, cpu, val);
	वापस 1;
पूर्ण

अटल व्योम relax_cpu_ftr_reg(u32 sys_id, पूर्णांक field)
अणु
	स्थिर काष्ठा arm64_ftr_bits *ftrp;
	काष्ठा arm64_ftr_reg *regp = get_arm64_ftr_reg(sys_id);

	अगर (!regp)
		वापस;

	क्रम (ftrp = regp->ftr_bits; ftrp->width; ftrp++) अणु
		अगर (ftrp->shअगरt == field) अणु
			regp->strict_mask &= ~arm64_ftr_mask(ftrp);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Bogus field? */
	WARN_ON(!ftrp->width);
पूर्ण

अटल पूर्णांक update_32bit_cpu_features(पूर्णांक cpu, काष्ठा cpuinfo_arm64 *info,
				     काष्ठा cpuinfo_arm64 *boot)
अणु
	पूर्णांक taपूर्णांक = 0;
	u64 pfr0 = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64PFR0_EL1);

	/*
	 * If we करोn't have AArch32 at all then skip the checks entirely
	 * as the रेजिस्टर values may be UNKNOWN and we're not going to be
	 * using them क्रम anything.
	 */
	अगर (!id_aa64pfr0_32bit_el0(pfr0))
		वापस taपूर्णांक;

	/*
	 * If we करोn't have AArch32 at EL1, then relax the strictness of
	 * EL1-dependent रेजिस्टर fields to aव्योम spurious sanity check fails.
	 */
	अगर (!id_aa64pfr0_32bit_el1(pfr0)) अणु
		relax_cpu_ftr_reg(SYS_ID_ISAR4_EL1, ID_ISAR4_SMC_SHIFT);
		relax_cpu_ftr_reg(SYS_ID_PFR1_EL1, ID_PFR1_VIRT_FRAC_SHIFT);
		relax_cpu_ftr_reg(SYS_ID_PFR1_EL1, ID_PFR1_SEC_FRAC_SHIFT);
		relax_cpu_ftr_reg(SYS_ID_PFR1_EL1, ID_PFR1_VIRTUALIZATION_SHIFT);
		relax_cpu_ftr_reg(SYS_ID_PFR1_EL1, ID_PFR1_SECURITY_SHIFT);
		relax_cpu_ftr_reg(SYS_ID_PFR1_EL1, ID_PFR1_PROGMOD_SHIFT);
	पूर्ण

	taपूर्णांक |= check_update_ftr_reg(SYS_ID_DFR0_EL1, cpu,
				      info->reg_id_dfr0, boot->reg_id_dfr0);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_DFR1_EL1, cpu,
				      info->reg_id_dfr1, boot->reg_id_dfr1);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_ISAR0_EL1, cpu,
				      info->reg_id_isar0, boot->reg_id_isar0);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_ISAR1_EL1, cpu,
				      info->reg_id_isar1, boot->reg_id_isar1);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_ISAR2_EL1, cpu,
				      info->reg_id_isar2, boot->reg_id_isar2);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_ISAR3_EL1, cpu,
				      info->reg_id_isar3, boot->reg_id_isar3);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_ISAR4_EL1, cpu,
				      info->reg_id_isar4, boot->reg_id_isar4);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_ISAR5_EL1, cpu,
				      info->reg_id_isar5, boot->reg_id_isar5);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_ISAR6_EL1, cpu,
				      info->reg_id_isar6, boot->reg_id_isar6);

	/*
	 * Regardless of the value of the AuxReg field, the AIFSR, ADFSR, and
	 * ACTLR क्रमmats could dअगरfer across CPUs and thereक्रमe would have to
	 * be trapped क्रम भवization anyway.
	 */
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_MMFR0_EL1, cpu,
				      info->reg_id_mmfr0, boot->reg_id_mmfr0);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_MMFR1_EL1, cpu,
				      info->reg_id_mmfr1, boot->reg_id_mmfr1);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_MMFR2_EL1, cpu,
				      info->reg_id_mmfr2, boot->reg_id_mmfr2);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_MMFR3_EL1, cpu,
				      info->reg_id_mmfr3, boot->reg_id_mmfr3);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_MMFR4_EL1, cpu,
				      info->reg_id_mmfr4, boot->reg_id_mmfr4);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_MMFR5_EL1, cpu,
				      info->reg_id_mmfr5, boot->reg_id_mmfr5);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_PFR0_EL1, cpu,
				      info->reg_id_pfr0, boot->reg_id_pfr0);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_PFR1_EL1, cpu,
				      info->reg_id_pfr1, boot->reg_id_pfr1);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_PFR2_EL1, cpu,
				      info->reg_id_pfr2, boot->reg_id_pfr2);
	taपूर्णांक |= check_update_ftr_reg(SYS_MVFR0_EL1, cpu,
				      info->reg_mvfr0, boot->reg_mvfr0);
	taपूर्णांक |= check_update_ftr_reg(SYS_MVFR1_EL1, cpu,
				      info->reg_mvfr1, boot->reg_mvfr1);
	taपूर्णांक |= check_update_ftr_reg(SYS_MVFR2_EL1, cpu,
				      info->reg_mvfr2, boot->reg_mvfr2);

	वापस taपूर्णांक;
पूर्ण

/*
 * Update प्रणाली wide CPU feature रेजिस्टरs with the values from a
 * non-boot CPU. Also perक्रमms SANITY checks to make sure that there
 * aren't any insane variations from that of the boot CPU.
 */
व्योम update_cpu_features(पूर्णांक cpu,
			 काष्ठा cpuinfo_arm64 *info,
			 काष्ठा cpuinfo_arm64 *boot)
अणु
	पूर्णांक taपूर्णांक = 0;

	/*
	 * The kernel can handle dअगरfering I-cache policies, but otherwise
	 * caches should look identical. Userspace JITs will make use of
	 * *minLine.
	 */
	taपूर्णांक |= check_update_ftr_reg(SYS_CTR_EL0, cpu,
				      info->reg_ctr, boot->reg_ctr);

	/*
	 * Userspace may perक्रमm DC ZVA inकाष्ठाions. Mismatched block sizes
	 * could result in too much or too little memory being zeroed अगर a
	 * process is preempted and migrated between CPUs.
	 */
	taपूर्णांक |= check_update_ftr_reg(SYS_DCZID_EL0, cpu,
				      info->reg_dczid, boot->reg_dczid);

	/* If dअगरferent, समयkeeping will be broken (especially with KVM) */
	taपूर्णांक |= check_update_ftr_reg(SYS_CNTFRQ_EL0, cpu,
				      info->reg_cntfrq, boot->reg_cntfrq);

	/*
	 * The kernel uses self-hosted debug features and expects CPUs to
	 * support identical debug features. We presently need CTX_CMPs, WRPs,
	 * and BRPs to be identical.
	 * ID_AA64DFR1 is currently RES0.
	 */
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64DFR0_EL1, cpu,
				      info->reg_id_aa64dfr0, boot->reg_id_aa64dfr0);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64DFR1_EL1, cpu,
				      info->reg_id_aa64dfr1, boot->reg_id_aa64dfr1);
	/*
	 * Even in big.LITTLE, processors should be identical inकाष्ठाion-set
	 * wise.
	 */
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64ISAR0_EL1, cpu,
				      info->reg_id_aa64isar0, boot->reg_id_aa64isar0);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64ISAR1_EL1, cpu,
				      info->reg_id_aa64isar1, boot->reg_id_aa64isar1);

	/*
	 * Dअगरfering PARange support is fine as दीर्घ as all peripherals and
	 * memory are mapped within the minimum PARange of all CPUs.
	 * Linux should not care about secure memory.
	 */
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64MMFR0_EL1, cpu,
				      info->reg_id_aa64mmfr0, boot->reg_id_aa64mmfr0);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64MMFR1_EL1, cpu,
				      info->reg_id_aa64mmfr1, boot->reg_id_aa64mmfr1);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64MMFR2_EL1, cpu,
				      info->reg_id_aa64mmfr2, boot->reg_id_aa64mmfr2);

	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64PFR0_EL1, cpu,
				      info->reg_id_aa64pfr0, boot->reg_id_aa64pfr0);
	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64PFR1_EL1, cpu,
				      info->reg_id_aa64pfr1, boot->reg_id_aa64pfr1);

	taपूर्णांक |= check_update_ftr_reg(SYS_ID_AA64ZFR0_EL1, cpu,
				      info->reg_id_aa64zfr0, boot->reg_id_aa64zfr0);

	अगर (id_aa64pfr0_sve(info->reg_id_aa64pfr0)) अणु
		taपूर्णांक |= check_update_ftr_reg(SYS_ZCR_EL1, cpu,
					info->reg_zcr, boot->reg_zcr);

		/* Probe vector lengths, unless we alपढ़ोy gave up on SVE */
		अगर (id_aa64pfr0_sve(पढ़ो_sanitised_ftr_reg(SYS_ID_AA64PFR0_EL1)) &&
		    !प्रणाली_capabilities_finalized())
			sve_update_vq_map();
	पूर्ण

	/*
	 * This relies on a sanitised view of the AArch64 ID रेजिस्टरs
	 * (e.g. SYS_ID_AA64PFR0_EL1), so we call it last.
	 */
	taपूर्णांक |= update_32bit_cpu_features(cpu, info, boot);

	/*
	 * Mismatched CPU features are a recipe क्रम disaster. Don't even
	 * pretend to support them.
	 */
	अगर (taपूर्णांक) अणु
		pr_warn_once("Unsupported CPU feature variation detected.\n");
		add_taपूर्णांक(TAINT_CPU_OUT_OF_SPEC, LOCKDEP_STILL_OK);
	पूर्ण
पूर्ण

u64 पढ़ो_sanitised_ftr_reg(u32 id)
अणु
	काष्ठा arm64_ftr_reg *regp = get_arm64_ftr_reg(id);

	अगर (!regp)
		वापस 0;
	वापस regp->sys_val;
पूर्ण
EXPORT_SYMBOL_GPL(पढ़ो_sanitised_ftr_reg);

#घोषणा पढ़ो_sysreg_हाल(r)	\
	हाल r:		val = पढ़ो_sysreg_s(r); अवरोध;

/*
 * __पढ़ो_sysreg_by_encoding() - Used by a STARTING cpu beक्रमe cpuinfo is populated.
 * Read the प्रणाली रेजिस्टर on the current CPU
 */
u64 __पढ़ो_sysreg_by_encoding(u32 sys_id)
अणु
	काष्ठा arm64_ftr_reg *regp;
	u64 val;

	चयन (sys_id) अणु
	पढ़ो_sysreg_हाल(SYS_ID_PFR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_PFR1_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_PFR2_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_DFR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_DFR1_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_MMFR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_MMFR1_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_MMFR2_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_MMFR3_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_MMFR4_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_MMFR5_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_ISAR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_ISAR1_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_ISAR2_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_ISAR3_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_ISAR4_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_ISAR5_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_ISAR6_EL1);
	पढ़ो_sysreg_हाल(SYS_MVFR0_EL1);
	पढ़ो_sysreg_हाल(SYS_MVFR1_EL1);
	पढ़ो_sysreg_हाल(SYS_MVFR2_EL1);

	पढ़ो_sysreg_हाल(SYS_ID_AA64PFR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64PFR1_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64ZFR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64DFR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64DFR1_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64MMFR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64MMFR1_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64MMFR2_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64ISAR0_EL1);
	पढ़ो_sysreg_हाल(SYS_ID_AA64ISAR1_EL1);

	पढ़ो_sysreg_हाल(SYS_CNTFRQ_EL0);
	पढ़ो_sysreg_हाल(SYS_CTR_EL0);
	पढ़ो_sysreg_हाल(SYS_DCZID_EL0);

	शेष:
		BUG();
		वापस 0;
	पूर्ण

	regp  = get_arm64_ftr_reg(sys_id);
	अगर (regp) अणु
		val &= ~regp->override->mask;
		val |= (regp->override->val & regp->override->mask);
	पूर्ण

	वापस val;
पूर्ण

#समावेश <linux/irqchip/arm-gic-v3.h>

अटल bool
feature_matches(u64 reg, स्थिर काष्ठा arm64_cpu_capabilities *entry)
अणु
	पूर्णांक val = cpuid_feature_extract_field(reg, entry->field_pos, entry->sign);

	वापस val >= entry->min_field_value;
पूर्ण

अटल bool
has_cpuid_feature(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक scope)
अणु
	u64 val;

	WARN_ON(scope == SCOPE_LOCAL_CPU && preemptible());
	अगर (scope == SCOPE_SYSTEM)
		val = पढ़ो_sanitised_ftr_reg(entry->sys_reg);
	अन्यथा
		val = __पढ़ो_sysreg_by_encoding(entry->sys_reg);

	वापस feature_matches(val, entry);
पूर्ण

अटल bool has_useable_gicv3_cpuअगर(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक scope)
अणु
	bool has_sre;

	अगर (!has_cpuid_feature(entry, scope))
		वापस false;

	has_sre = gic_enable_sre();
	अगर (!has_sre)
		pr_warn_once("%s present but disabled by higher exception level\n",
			     entry->desc);

	वापस has_sre;
पूर्ण

अटल bool has_no_hw_prefetch(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक __unused)
अणु
	u32 midr = पढ़ो_cpuid_id();

	/* Cavium ThunderX pass 1.x and 2.x */
	वापस midr_is_cpu_model_range(midr, MIDR_THUNDERX,
		MIDR_CPU_VAR_REV(0, 0),
		MIDR_CPU_VAR_REV(1, MIDR_REVISION_MASK));
पूर्ण

अटल bool has_no_fpsimd(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक __unused)
अणु
	u64 pfr0 = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64PFR0_EL1);

	वापस cpuid_feature_extract_चिन्हित_field(pfr0,
					ID_AA64PFR0_FP_SHIFT) < 0;
पूर्ण

अटल bool has_cache_idc(स्थिर काष्ठा arm64_cpu_capabilities *entry,
			  पूर्णांक scope)
अणु
	u64 ctr;

	अगर (scope == SCOPE_SYSTEM)
		ctr = arm64_ftr_reg_ctrel0.sys_val;
	अन्यथा
		ctr = पढ़ो_cpuid_effective_cachetype();

	वापस ctr & BIT(CTR_IDC_SHIFT);
पूर्ण

अटल व्योम cpu_emulate_effective_ctr(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	/*
	 * If the CPU exposes raw CTR_EL0.IDC = 0, जबतक effectively
	 * CTR_EL0.IDC = 1 (from CLIDR values), we need to trap accesses
	 * to the CTR_EL0 on this CPU and emulate it with the real/safe
	 * value.
	 */
	अगर (!(पढ़ो_cpuid_cachetype() & BIT(CTR_IDC_SHIFT)))
		sysreg_clear_set(sctlr_el1, SCTLR_EL1_UCT, 0);
पूर्ण

अटल bool has_cache_dic(स्थिर काष्ठा arm64_cpu_capabilities *entry,
			  पूर्णांक scope)
अणु
	u64 ctr;

	अगर (scope == SCOPE_SYSTEM)
		ctr = arm64_ftr_reg_ctrel0.sys_val;
	अन्यथा
		ctr = पढ़ो_cpuid_cachetype();

	वापस ctr & BIT(CTR_DIC_SHIFT);
पूर्ण

अटल bool __maybe_unused
has_useable_cnp(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक scope)
अणु
	/*
	 * Kdump isn't guaranteed to घातer-off all secondary CPUs, CNP
	 * may share TLB entries with a CPU stuck in the crashed
	 * kernel.
	 */
	अगर (is_kdump_kernel())
		वापस false;

	अगर (cpus_have_स्थिर_cap(ARM64_WORKAROUND_NVIDIA_CARMEL_CNP))
		वापस false;

	वापस has_cpuid_feature(entry, scope);
पूर्ण

/*
 * This check is triggered during the early boot beक्रमe the cpufeature
 * is initialised. Checking the status on the local CPU allows the boot
 * CPU to detect the need क्रम non-global mappings and thus aव्योमing a
 * pagetable re-ग_लिखो after all the CPUs are booted. This check will be
 * anyway run on inभागidual CPUs, allowing us to get the consistent
 * state once the SMP CPUs are up and thus make the चयन to non-global
 * mappings अगर required.
 */
bool kaslr_requires_kpti(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_RANDOMIZE_BASE))
		वापस false;

	/*
	 * E0PD करोes a similar job to KPTI so can be used instead
	 * where available.
	 */
	अगर (IS_ENABLED(CONFIG_ARM64_E0PD)) अणु
		u64 mmfr2 = पढ़ो_sysreg_s(SYS_ID_AA64MMFR2_EL1);
		अगर (cpuid_feature_extract_अचिन्हित_field(mmfr2,
						ID_AA64MMFR2_E0PD_SHIFT))
			वापस false;
	पूर्ण

	/*
	 * Systems affected by Cavium erratum 24756 are incompatible
	 * with KPTI.
	 */
	अगर (IS_ENABLED(CONFIG_CAVIUM_ERRATUM_27456)) अणु
		बाह्य स्थिर काष्ठा midr_range cavium_erratum_27456_cpus[];

		अगर (is_midr_in_range_list(पढ़ो_cpuid_id(),
					  cavium_erratum_27456_cpus))
			वापस false;
	पूर्ण

	वापस kaslr_offset() > 0;
पूर्ण

अटल bool __meltकरोwn_safe = true;
अटल पूर्णांक __kpti_क्रमced; /* 0: not क्रमced, >0: क्रमced on, <0: क्रमced off */

अटल bool unmap_kernel_at_el0(स्थिर काष्ठा arm64_cpu_capabilities *entry,
				पूर्णांक scope)
अणु
	/* List of CPUs that are not vulnerable and करोn't need KPTI */
	अटल स्थिर काष्ठा midr_range kpti_safe_list[] = अणु
		MIDR_ALL_VERSIONS(MIDR_CAVIUM_THUNDERX2),
		MIDR_ALL_VERSIONS(MIDR_BRCM_VULCAN),
		MIDR_ALL_VERSIONS(MIDR_BRAHMA_B53),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A35),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A53),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A55),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A57),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A72),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A73),
		MIDR_ALL_VERSIONS(MIDR_HISI_TSV110),
		MIDR_ALL_VERSIONS(MIDR_NVIDIA_CARMEL),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_2XX_GOLD),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_2XX_SILVER),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_3XX_SILVER),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_4XX_SILVER),
		अणु /* sentinel */ पूर्ण
	पूर्ण;
	अक्षर स्थिर *str = "kpti command line option";
	bool meltकरोwn_safe;

	meltकरोwn_safe = is_midr_in_range_list(पढ़ो_cpuid_id(), kpti_safe_list);

	/* Defer to CPU feature रेजिस्टरs */
	अगर (has_cpuid_feature(entry, scope))
		meltकरोwn_safe = true;

	अगर (!meltकरोwn_safe)
		__meltकरोwn_safe = false;

	/*
	 * For reasons that aren't entirely clear, enabling KPTI on Cavium
	 * ThunderX leads to apparent I-cache corruption of kernel text, which
	 * ends as well as you might imagine. Don't even try.
	 */
	अगर (cpus_have_स्थिर_cap(ARM64_WORKAROUND_CAVIUM_27456)) अणु
		str = "ARM64_WORKAROUND_CAVIUM_27456";
		__kpti_क्रमced = -1;
	पूर्ण

	/* Useful क्रम KASLR robustness */
	अगर (kaslr_requires_kpti()) अणु
		अगर (!__kpti_क्रमced) अणु
			str = "KASLR";
			__kpti_क्रमced = 1;
		पूर्ण
	पूर्ण

	अगर (cpu_mitigations_off() && !__kpti_क्रमced) अणु
		str = "mitigations=off";
		__kpti_क्रमced = -1;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_UNMAP_KERNEL_AT_EL0)) अणु
		pr_info_once("kernel page table isolation disabled by kernel configuration\n");
		वापस false;
	पूर्ण

	/* Forced? */
	अगर (__kpti_क्रमced) अणु
		pr_info_once("kernel page table isolation forced %s by %s\n",
			     __kpti_क्रमced > 0 ? "ON" : "OFF", str);
		वापस __kpti_क्रमced > 0;
	पूर्ण

	वापस !meltकरोwn_safe;
पूर्ण

#अगर_घोषित CONFIG_UNMAP_KERNEL_AT_EL0
अटल व्योम __nocfi
kpti_install_ng_mappings(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	प्रकार व्योम (kpti_remap_fn)(पूर्णांक, पूर्णांक, phys_addr_t);
	बाह्य kpti_remap_fn idmap_kpti_install_ng_mappings;
	kpti_remap_fn *remap_fn;

	पूर्णांक cpu = smp_processor_id();

	/*
	 * We करोn't need to rewrite the page-tables if either we've करोne
	 * it alपढ़ोy or we have KASLR enabled and thereक्रमe have not
	 * created any global mappings at all.
	 */
	अगर (arm64_use_ng_mappings)
		वापस;

	remap_fn = (व्योम *)__pa_symbol(function_nocfi(idmap_kpti_install_ng_mappings));

	cpu_install_idmap();
	remap_fn(cpu, num_online_cpus(), __pa_symbol(swapper_pg_dir));
	cpu_uninstall_idmap();

	अगर (!cpu)
		arm64_use_ng_mappings = true;

	वापस;
पूर्ण
#अन्यथा
अटल व्योम
kpti_install_ng_mappings(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_UNMAP_KERNEL_AT_EL0 */

अटल पूर्णांक __init parse_kpti(अक्षर *str)
अणु
	bool enabled;
	पूर्णांक ret = strtobool(str, &enabled);

	अगर (ret)
		वापस ret;

	__kpti_क्रमced = enabled ? 1 : -1;
	वापस 0;
पूर्ण
early_param("kpti", parse_kpti);

#अगर_घोषित CONFIG_ARM64_HW_AFDBM
अटल अंतरभूत व्योम __cpu_enable_hw_dbm(व्योम)
अणु
	u64 tcr = पढ़ो_sysreg(tcr_el1) | TCR_HD;

	ग_लिखो_sysreg(tcr, tcr_el1);
	isb();
	local_flush_tlb_all();
पूर्ण

अटल bool cpu_has_broken_dbm(व्योम)
अणु
	/* List of CPUs which have broken DBM support. */
	अटल स्थिर काष्ठा midr_range cpus[] = अणु
#अगर_घोषित CONFIG_ARM64_ERRATUM_1024718
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A55),
		/* Kryo4xx Silver (rdpe => r1p0) */
		MIDR_REV(MIDR_QCOM_KRYO_4XX_SILVER, 0xd, 0xe),
#पूर्ण_अगर
		अणुपूर्ण,
	पूर्ण;

	वापस is_midr_in_range_list(पढ़ो_cpuid_id(), cpus);
पूर्ण

अटल bool cpu_can_use_dbm(स्थिर काष्ठा arm64_cpu_capabilities *cap)
अणु
	वापस has_cpuid_feature(cap, SCOPE_LOCAL_CPU) &&
	       !cpu_has_broken_dbm();
पूर्ण

अटल व्योम cpu_enable_hw_dbm(काष्ठा arm64_cpu_capabilities स्थिर *cap)
अणु
	अगर (cpu_can_use_dbm(cap))
		__cpu_enable_hw_dbm();
पूर्ण

अटल bool has_hw_dbm(स्थिर काष्ठा arm64_cpu_capabilities *cap,
		       पूर्णांक __unused)
अणु
	अटल bool detected = false;
	/*
	 * DBM is a non-conflicting feature. i.e, the kernel can safely
	 * run a mix of CPUs with and without the feature. So, we
	 * unconditionally enable the capability to allow any late CPU
	 * to use the feature. We only enable the control bits on the
	 * CPU, अगर it actually supports.
	 *
	 * We have to make sure we prपूर्णांक the "feature" detection only
	 * when at least one CPU actually uses it. So check अगर this CPU
	 * can actually use it and prपूर्णांक the message exactly once.
	 *
	 * This is safe as all CPUs (including secondary CPUs - due to the
	 * LOCAL_CPU scope - and the hotplugged CPUs - via verअगरication)
	 * goes through the "matches" check exactly once. Also अगर a CPU
	 * matches the criteria, it is guaranteed that the CPU will turn
	 * the DBM on, as the capability is unconditionally enabled.
	 */
	अगर (!detected && cpu_can_use_dbm(cap)) अणु
		detected = true;
		pr_info("detected: Hardware dirty bit management\n");
	पूर्ण

	वापस true;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_AMU_EXTN

/*
 * The "amu_cpus" cpumask only संकेतs that the CPU implementation क्रम the
 * flagged CPUs supports the Activity Monitors Unit (AMU) but करोes not provide
 * inक्रमmation regarding all the events that it supports. When a CPU bit is
 * set in the cpumask, the user of this feature can only rely on the presence
 * of the 4 fixed counters क्रम that CPU. But this करोes not guarantee that the
 * counters are enabled or access to these counters is enabled by code
 * executed at higher exception levels (firmware).
 */
अटल काष्ठा cpumask amu_cpus __पढ़ो_mostly;

bool cpu_has_amu_feat(पूर्णांक cpu)
अणु
	वापस cpumask_test_cpu(cpu, &amu_cpus);
पूर्ण

पूर्णांक get_cpu_with_amu_feat(व्योम)
अणु
	वापस cpumask_any(&amu_cpus);
पूर्ण

अटल व्योम cpu_amu_enable(काष्ठा arm64_cpu_capabilities स्थिर *cap)
अणु
	अगर (has_cpuid_feature(cap, SCOPE_LOCAL_CPU)) अणु
		pr_info("detected CPU%d: Activity Monitors Unit (AMU)\n",
			smp_processor_id());
		cpumask_set_cpu(smp_processor_id(), &amu_cpus);
		update_freq_counters_refs();
	पूर्ण
पूर्ण

अटल bool has_amu(स्थिर काष्ठा arm64_cpu_capabilities *cap,
		    पूर्णांक __unused)
अणु
	/*
	 * The AMU extension is a non-conflicting feature: the kernel can
	 * safely run a mix of CPUs with and without support क्रम the
	 * activity monitors extension. Thereक्रमe, unconditionally enable
	 * the capability to allow any late CPU to use the feature.
	 *
	 * With this feature unconditionally enabled, the cpu_enable
	 * function will be called क्रम all CPUs that match the criteria,
	 * including secondary and hotplugged, marking this feature as
	 * present on that respective CPU. The enable function will also
	 * prपूर्णांक a detection message.
	 */

	वापस true;
पूर्ण
#अन्यथा
पूर्णांक get_cpu_with_amu_feat(व्योम)
अणु
	वापस nr_cpu_ids;
पूर्ण
#पूर्ण_अगर

अटल bool runs_at_el2(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक __unused)
अणु
	वापस is_kernel_in_hyp_mode();
पूर्ण

अटल व्योम cpu_copy_el2regs(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	/*
	 * Copy रेजिस्टर values that aren't redirected by hardware.
	 *
	 * Beक्रमe code patching, we only set tpidr_el1, all CPUs need to copy
	 * this value to tpidr_el2 beक्रमe we patch the code. Once we've करोne
	 * that, freshly-onlined CPUs will set tpidr_el2, so we करोn't need to
	 * करो anything here.
	 */
	अगर (!alternative_is_applied(ARM64_HAS_VIRT_HOST_EXTN))
		ग_लिखो_sysreg(पढ़ो_sysreg(tpidr_el1), tpidr_el2);
पूर्ण

अटल व्योम cpu_has_fwb(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	u64 val = पढ़ो_sysreg_s(SYS_CLIDR_EL1);

	/* Check that CLIDR_EL1.LOUअणुU,ISपूर्ण are both 0 */
	WARN_ON(val & (7 << 27 | 7 << 21));
पूर्ण

#अगर_घोषित CONFIG_ARM64_PAN
अटल व्योम cpu_enable_pan(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	/*
	 * We modअगरy PSTATE. This won't work from irq context as the PSTATE
	 * is discarded once we वापस from the exception.
	 */
	WARN_ON_ONCE(in_पूर्णांकerrupt());

	sysreg_clear_set(sctlr_el1, SCTLR_EL1_SPAN, 0);
	set_pstate_pan(1);
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM64_PAN */

#अगर_घोषित CONFIG_ARM64_RAS_EXTN
अटल व्योम cpu_clear_disr(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	/* Firmware may have left a deferred SError in this रेजिस्टर. */
	ग_लिखो_sysreg_s(0, SYS_DISR_EL1);
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM64_RAS_EXTN */

#अगर_घोषित CONFIG_ARM64_PTR_AUTH
अटल bool has_address_auth_cpucap(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक scope)
अणु
	पूर्णांक boot_val, sec_val;

	/* We करोn't expect to be called with SCOPE_SYSTEM */
	WARN_ON(scope == SCOPE_SYSTEM);
	/*
	 * The ptr-auth feature levels are not पूर्णांकercompatible with lower
	 * levels. Hence we must match ptr-auth feature level of the secondary
	 * CPUs with that of the boot CPU. The level of boot cpu is fetched
	 * from the sanitised रेजिस्टर whereas direct रेजिस्टर पढ़ो is करोne क्रम
	 * the secondary CPUs.
	 * The sanitised feature state is guaranteed to match that of the
	 * boot CPU as a mismatched secondary CPU is parked beक्रमe it माला_लो
	 * a chance to update the state, with the capability.
	 */
	boot_val = cpuid_feature_extract_field(पढ़ो_sanitised_ftr_reg(entry->sys_reg),
					       entry->field_pos, entry->sign);
	अगर (scope & SCOPE_BOOT_CPU)
		वापस boot_val >= entry->min_field_value;
	/* Now check क्रम the secondary CPUs with SCOPE_LOCAL_CPU scope */
	sec_val = cpuid_feature_extract_field(__पढ़ो_sysreg_by_encoding(entry->sys_reg),
					      entry->field_pos, entry->sign);
	वापस sec_val == boot_val;
पूर्ण

अटल bool has_address_auth_metacap(स्थिर काष्ठा arm64_cpu_capabilities *entry,
				     पूर्णांक scope)
अणु
	वापस has_address_auth_cpucap(cpu_hwcaps_ptrs[ARM64_HAS_ADDRESS_AUTH_ARCH], scope) ||
	       has_address_auth_cpucap(cpu_hwcaps_ptrs[ARM64_HAS_ADDRESS_AUTH_IMP_DEF], scope);
पूर्ण

अटल bool has_generic_auth(स्थिर काष्ठा arm64_cpu_capabilities *entry,
			     पूर्णांक __unused)
अणु
	वापस __प्रणाली_matches_cap(ARM64_HAS_GENERIC_AUTH_ARCH) ||
	       __प्रणाली_matches_cap(ARM64_HAS_GENERIC_AUTH_IMP_DEF);
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM64_PTR_AUTH */

#अगर_घोषित CONFIG_ARM64_E0PD
अटल व्योम cpu_enable_e0pd(काष्ठा arm64_cpu_capabilities स्थिर *cap)
अणु
	अगर (this_cpu_has_cap(ARM64_HAS_E0PD))
		sysreg_clear_set(tcr_el1, 0, TCR_E0PD1);
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM64_E0PD */

#अगर_घोषित CONFIG_ARM64_PSEUDO_NMI
अटल bool enable_pseuकरो_nmi;

अटल पूर्णांक __init early_enable_pseuकरो_nmi(अक्षर *p)
अणु
	वापस strtobool(p, &enable_pseuकरो_nmi);
पूर्ण
early_param("irqchip.gicv3_pseudo_nmi", early_enable_pseuकरो_nmi);

अटल bool can_use_gic_priorities(स्थिर काष्ठा arm64_cpu_capabilities *entry,
				   पूर्णांक scope)
अणु
	वापस enable_pseuकरो_nmi && has_useable_gicv3_cpuअगर(entry, scope);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_BTI
अटल व्योम bti_enable(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	/*
	 * Use of X16/X17 क्रम tail-calls and trampolines that jump to
	 * function entry poपूर्णांकs using BR is a requirement क्रम
	 * marking binaries with GNU_PROPERTY_AARCH64_FEATURE_1_BTI.
	 * So, be strict and क्रमbid other BRs using other रेजिस्टरs to
	 * jump onto a PACIxSP inकाष्ठाion:
	 */
	sysreg_clear_set(sctlr_el1, 0, SCTLR_EL1_BT0 | SCTLR_EL1_BT1);
	isb();
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM64_BTI */

#अगर_घोषित CONFIG_ARM64_MTE
अटल व्योम cpu_enable_mte(काष्ठा arm64_cpu_capabilities स्थिर *cap)
अणु
	/*
	 * Clear the tags in the zero page. This needs to be करोne via the
	 * linear map which has the Tagged attribute.
	 */
	अगर (!test_and_set_bit(PG_mte_tagged, &ZERO_PAGE(0)->flags))
		mte_clear_page_tags(lm_alias(empty_zero_page));

	kasan_init_hw_tags_cpu();
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM64_MTE */

#अगर_घोषित CONFIG_KVM
अटल bool is_kvm_रक्षित_mode(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक __unused)
अणु
	अगर (kvm_get_mode() != KVM_MODE_PROTECTED)
		वापस false;

	अगर (is_kernel_in_hyp_mode()) अणु
		pr_warn("Protected KVM not available with VHE\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM */

/* Internal helper functions to match cpu capability type */
अटल bool
cpucap_late_cpu_optional(स्थिर काष्ठा arm64_cpu_capabilities *cap)
अणु
	वापस !!(cap->type & ARM64_CPUCAP_OPTIONAL_FOR_LATE_CPU);
पूर्ण

अटल bool
cpucap_late_cpu_permitted(स्थिर काष्ठा arm64_cpu_capabilities *cap)
अणु
	वापस !!(cap->type & ARM64_CPUCAP_PERMITTED_FOR_LATE_CPU);
पूर्ण

अटल bool
cpucap_panic_on_conflict(स्थिर काष्ठा arm64_cpu_capabilities *cap)
अणु
	वापस !!(cap->type & ARM64_CPUCAP_PANIC_ON_CONFLICT);
पूर्ण

अटल स्थिर काष्ठा arm64_cpu_capabilities arm64_features[] = अणु
	अणु
		.desc = "GIC system register CPU interface",
		.capability = ARM64_HAS_SYSREG_GIC_CPUIF,
		.type = ARM64_CPUCAP_STRICT_BOOT_CPU_FEATURE,
		.matches = has_useable_gicv3_cpuअगर,
		.sys_reg = SYS_ID_AA64PFR0_EL1,
		.field_pos = ID_AA64PFR0_GIC_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = 1,
	पूर्ण,
#अगर_घोषित CONFIG_ARM64_PAN
	अणु
		.desc = "Privileged Access Never",
		.capability = ARM64_HAS_PAN,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64MMFR1_EL1,
		.field_pos = ID_AA64MMFR1_PAN_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = 1,
		.cpu_enable = cpu_enable_pan,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM64_PAN */
#अगर_घोषित CONFIG_ARM64_EPAN
	अणु
		.desc = "Enhanced Privileged Access Never",
		.capability = ARM64_HAS_EPAN,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64MMFR1_EL1,
		.field_pos = ID_AA64MMFR1_PAN_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = 3,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM64_EPAN */
#अगर_घोषित CONFIG_ARM64_LSE_ATOMICS
	अणु
		.desc = "LSE atomic instructions",
		.capability = ARM64_HAS_LSE_ATOMICS,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64ISAR0_EL1,
		.field_pos = ID_AA64ISAR0_ATOMICS_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = 2,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM64_LSE_ATOMICS */
	अणु
		.desc = "Software prefetching using PRFM",
		.capability = ARM64_HAS_NO_HW_PREFETCH,
		.type = ARM64_CPUCAP_WEAK_LOCAL_CPU_FEATURE,
		.matches = has_no_hw_prefetch,
	पूर्ण,
	अणु
		.desc = "Virtualization Host Extensions",
		.capability = ARM64_HAS_VIRT_HOST_EXTN,
		.type = ARM64_CPUCAP_STRICT_BOOT_CPU_FEATURE,
		.matches = runs_at_el2,
		.cpu_enable = cpu_copy_el2regs,
	पूर्ण,
	अणु
		.desc = "32-bit EL0 Support",
		.capability = ARM64_HAS_32BIT_EL0,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64PFR0_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64PFR0_EL0_SHIFT,
		.min_field_value = ID_AA64PFR0_EL0_32BIT_64BIT,
	पूर्ण,
#अगर_घोषित CONFIG_KVM
	अणु
		.desc = "32-bit EL1 Support",
		.capability = ARM64_HAS_32BIT_EL1,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64PFR0_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64PFR0_EL1_SHIFT,
		.min_field_value = ID_AA64PFR0_EL1_32BIT_64BIT,
	पूर्ण,
	अणु
		.desc = "Protected KVM",
		.capability = ARM64_KVM_PROTECTED_MODE,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = is_kvm_रक्षित_mode,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.desc = "Kernel page table isolation (KPTI)",
		.capability = ARM64_UNMAP_KERNEL_AT_EL0,
		.type = ARM64_CPUCAP_BOOT_RESTRICTED_CPU_LOCAL_FEATURE,
		/*
		 * The ID feature fields below are used to indicate that
		 * the CPU करोesn't need KPTI. See unmap_kernel_at_el0 क्रम
		 * more details.
		 */
		.sys_reg = SYS_ID_AA64PFR0_EL1,
		.field_pos = ID_AA64PFR0_CSV3_SHIFT,
		.min_field_value = 1,
		.matches = unmap_kernel_at_el0,
		.cpu_enable = kpti_install_ng_mappings,
	पूर्ण,
	अणु
		/* FP/SIMD is not implemented */
		.capability = ARM64_HAS_NO_FPSIMD,
		.type = ARM64_CPUCAP_BOOT_RESTRICTED_CPU_LOCAL_FEATURE,
		.min_field_value = 0,
		.matches = has_no_fpsimd,
	पूर्ण,
#अगर_घोषित CONFIG_ARM64_PMEM
	अणु
		.desc = "Data cache clean to Point of Persistence",
		.capability = ARM64_HAS_DCPOP,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64ISAR1_EL1,
		.field_pos = ID_AA64ISAR1_DPB_SHIFT,
		.min_field_value = 1,
	पूर्ण,
	अणु
		.desc = "Data cache clean to Point of Deep Persistence",
		.capability = ARM64_HAS_DCPODP,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64ISAR1_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64ISAR1_DPB_SHIFT,
		.min_field_value = 2,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_SVE
	अणु
		.desc = "Scalable Vector Extension",
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.capability = ARM64_SVE,
		.sys_reg = SYS_ID_AA64PFR0_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64PFR0_SVE_SHIFT,
		.min_field_value = ID_AA64PFR0_SVE,
		.matches = has_cpuid_feature,
		.cpu_enable = sve_kernel_enable,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM64_SVE */
#अगर_घोषित CONFIG_ARM64_RAS_EXTN
	अणु
		.desc = "RAS Extension Support",
		.capability = ARM64_HAS_RAS_EXTN,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64PFR0_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64PFR0_RAS_SHIFT,
		.min_field_value = ID_AA64PFR0_RAS_V1,
		.cpu_enable = cpu_clear_disr,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM64_RAS_EXTN */
#अगर_घोषित CONFIG_ARM64_AMU_EXTN
	अणु
		/*
		 * The feature is enabled by शेष अगर CONFIG_ARM64_AMU_EXTN=y.
		 * Thereक्रमe, करोn't provide .desc as we don't want the detection
		 * message to be shown until at least one CPU is detected to
		 * support the feature.
		 */
		.capability = ARM64_HAS_AMU_EXTN,
		.type = ARM64_CPUCAP_WEAK_LOCAL_CPU_FEATURE,
		.matches = has_amu,
		.sys_reg = SYS_ID_AA64PFR0_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64PFR0_AMU_SHIFT,
		.min_field_value = ID_AA64PFR0_AMU,
		.cpu_enable = cpu_amu_enable,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM64_AMU_EXTN */
	अणु
		.desc = "Data cache clean to the PoU not required for I/D coherence",
		.capability = ARM64_HAS_CACHE_IDC,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cache_idc,
		.cpu_enable = cpu_emulate_effective_ctr,
	पूर्ण,
	अणु
		.desc = "Instruction cache invalidation not required for I/D coherence",
		.capability = ARM64_HAS_CACHE_DIC,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cache_dic,
	पूर्ण,
	अणु
		.desc = "Stage-2 Force Write-Back",
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.capability = ARM64_HAS_STAGE2_FWB,
		.sys_reg = SYS_ID_AA64MMFR2_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64MMFR2_FWB_SHIFT,
		.min_field_value = 1,
		.matches = has_cpuid_feature,
		.cpu_enable = cpu_has_fwb,
	पूर्ण,
	अणु
		.desc = "ARMv8.4 Translation Table Level",
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.capability = ARM64_HAS_ARMv8_4_TTL,
		.sys_reg = SYS_ID_AA64MMFR2_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64MMFR2_TTL_SHIFT,
		.min_field_value = 1,
		.matches = has_cpuid_feature,
	पूर्ण,
	अणु
		.desc = "TLB range maintenance instructions",
		.capability = ARM64_HAS_TLB_RANGE,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64ISAR0_EL1,
		.field_pos = ID_AA64ISAR0_TLB_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = ID_AA64ISAR0_TLB_RANGE,
	पूर्ण,
#अगर_घोषित CONFIG_ARM64_HW_AFDBM
	अणु
		/*
		 * Since we turn this on always, we करोn't want the user to
		 * think that the feature is available when it may not be.
		 * So hide the description.
		 *
		 * .desc = "Hardware pagetable Dirty Bit Management",
		 *
		 */
		.type = ARM64_CPUCAP_WEAK_LOCAL_CPU_FEATURE,
		.capability = ARM64_HW_DBM,
		.sys_reg = SYS_ID_AA64MMFR1_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64MMFR1_HADBS_SHIFT,
		.min_field_value = 2,
		.matches = has_hw_dbm,
		.cpu_enable = cpu_enable_hw_dbm,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.desc = "CRC32 instructions",
		.capability = ARM64_HAS_CRC32,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64ISAR0_EL1,
		.field_pos = ID_AA64ISAR0_CRC32_SHIFT,
		.min_field_value = 1,
	पूर्ण,
	अणु
		.desc = "Speculative Store Bypassing Safe (SSBS)",
		.capability = ARM64_SSBS,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64PFR1_EL1,
		.field_pos = ID_AA64PFR1_SSBS_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = ID_AA64PFR1_SSBS_PSTATE_ONLY,
	पूर्ण,
#अगर_घोषित CONFIG_ARM64_CNP
	अणु
		.desc = "Common not Private translations",
		.capability = ARM64_HAS_CNP,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_useable_cnp,
		.sys_reg = SYS_ID_AA64MMFR2_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64MMFR2_CNP_SHIFT,
		.min_field_value = 1,
		.cpu_enable = cpu_enable_cnp,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.desc = "Speculation barrier (SB)",
		.capability = ARM64_HAS_SB,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64ISAR1_EL1,
		.field_pos = ID_AA64ISAR1_SB_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = 1,
	पूर्ण,
#अगर_घोषित CONFIG_ARM64_PTR_AUTH
	अणु
		.desc = "Address authentication (architected algorithm)",
		.capability = ARM64_HAS_ADDRESS_AUTH_ARCH,
		.type = ARM64_CPUCAP_BOOT_CPU_FEATURE,
		.sys_reg = SYS_ID_AA64ISAR1_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64ISAR1_APA_SHIFT,
		.min_field_value = ID_AA64ISAR1_APA_ARCHITECTED,
		.matches = has_address_auth_cpucap,
	पूर्ण,
	अणु
		.desc = "Address authentication (IMP DEF algorithm)",
		.capability = ARM64_HAS_ADDRESS_AUTH_IMP_DEF,
		.type = ARM64_CPUCAP_BOOT_CPU_FEATURE,
		.sys_reg = SYS_ID_AA64ISAR1_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64ISAR1_API_SHIFT,
		.min_field_value = ID_AA64ISAR1_API_IMP_DEF,
		.matches = has_address_auth_cpucap,
	पूर्ण,
	अणु
		.capability = ARM64_HAS_ADDRESS_AUTH,
		.type = ARM64_CPUCAP_BOOT_CPU_FEATURE,
		.matches = has_address_auth_metacap,
	पूर्ण,
	अणु
		.desc = "Generic authentication (architected algorithm)",
		.capability = ARM64_HAS_GENERIC_AUTH_ARCH,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.sys_reg = SYS_ID_AA64ISAR1_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64ISAR1_GPA_SHIFT,
		.min_field_value = ID_AA64ISAR1_GPA_ARCHITECTED,
		.matches = has_cpuid_feature,
	पूर्ण,
	अणु
		.desc = "Generic authentication (IMP DEF algorithm)",
		.capability = ARM64_HAS_GENERIC_AUTH_IMP_DEF,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.sys_reg = SYS_ID_AA64ISAR1_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64ISAR1_GPI_SHIFT,
		.min_field_value = ID_AA64ISAR1_GPI_IMP_DEF,
		.matches = has_cpuid_feature,
	पूर्ण,
	अणु
		.capability = ARM64_HAS_GENERIC_AUTH,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_generic_auth,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM64_PTR_AUTH */
#अगर_घोषित CONFIG_ARM64_PSEUDO_NMI
	अणु
		/*
		 * Depends on having GICv3
		 */
		.desc = "IRQ priority masking",
		.capability = ARM64_HAS_IRQ_PRIO_MASKING,
		.type = ARM64_CPUCAP_STRICT_BOOT_CPU_FEATURE,
		.matches = can_use_gic_priorities,
		.sys_reg = SYS_ID_AA64PFR0_EL1,
		.field_pos = ID_AA64PFR0_GIC_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = 1,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_E0PD
	अणु
		.desc = "E0PD",
		.capability = ARM64_HAS_E0PD,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.sys_reg = SYS_ID_AA64MMFR2_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64MMFR2_E0PD_SHIFT,
		.matches = has_cpuid_feature,
		.min_field_value = 1,
		.cpu_enable = cpu_enable_e0pd,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_RANDOM
	अणु
		.desc = "Random Number Generator",
		.capability = ARM64_HAS_RNG,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64ISAR0_EL1,
		.field_pos = ID_AA64ISAR0_RNDR_SHIFT,
		.sign = FTR_UNSIGNED,
		.min_field_value = 1,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_BTI
	अणु
		.desc = "Branch Target Identification",
		.capability = ARM64_BTI,
#अगर_घोषित CONFIG_ARM64_BTI_KERNEL
		.type = ARM64_CPUCAP_STRICT_BOOT_CPU_FEATURE,
#अन्यथा
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
#पूर्ण_अगर
		.matches = has_cpuid_feature,
		.cpu_enable = bti_enable,
		.sys_reg = SYS_ID_AA64PFR1_EL1,
		.field_pos = ID_AA64PFR1_BT_SHIFT,
		.min_field_value = ID_AA64PFR1_BT_BTI,
		.sign = FTR_UNSIGNED,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_MTE
	अणु
		.desc = "Memory Tagging Extension",
		.capability = ARM64_MTE,
		.type = ARM64_CPUCAP_STRICT_BOOT_CPU_FEATURE,
		.matches = has_cpuid_feature,
		.sys_reg = SYS_ID_AA64PFR1_EL1,
		.field_pos = ID_AA64PFR1_MTE_SHIFT,
		.min_field_value = ID_AA64PFR1_MTE,
		.sign = FTR_UNSIGNED,
		.cpu_enable = cpu_enable_mte,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_ARM64_MTE */
	अणु
		.desc = "RCpc load-acquire (LDAPR)",
		.capability = ARM64_HAS_LDAPR,
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,
		.sys_reg = SYS_ID_AA64ISAR1_EL1,
		.sign = FTR_UNSIGNED,
		.field_pos = ID_AA64ISAR1_LRCPC_SHIFT,
		.matches = has_cpuid_feature,
		.min_field_value = 1,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

#घोषणा HWCAP_CPUID_MATCH(reg, field, s, min_value)				\
		.matches = has_cpuid_feature,					\
		.sys_reg = reg,							\
		.field_pos = field,						\
		.sign = s,							\
		.min_field_value = min_value,

#घोषणा __HWCAP_CAP(name, cap_type, cap)					\
		.desc = name,							\
		.type = ARM64_CPUCAP_SYSTEM_FEATURE,				\
		.hwcap_type = cap_type,						\
		.hwcap = cap,							\

#घोषणा HWCAP_CAP(reg, field, s, min_value, cap_type, cap)			\
	अणु									\
		__HWCAP_CAP(#cap, cap_type, cap)				\
		HWCAP_CPUID_MATCH(reg, field, s, min_value)			\
	पूर्ण

#घोषणा HWCAP_MULTI_CAP(list, cap_type, cap)					\
	अणु									\
		__HWCAP_CAP(#cap, cap_type, cap)				\
		.matches = cpucap_multi_entry_cap_matches,			\
		.match_list = list,						\
	पूर्ण

#घोषणा HWCAP_CAP_MATCH(match, cap_type, cap)					\
	अणु									\
		__HWCAP_CAP(#cap, cap_type, cap)				\
		.matches = match,						\
	पूर्ण

#अगर_घोषित CONFIG_ARM64_PTR_AUTH
अटल स्थिर काष्ठा arm64_cpu_capabilities ptr_auth_hwcap_addr_matches[] = अणु
	अणु
		HWCAP_CPUID_MATCH(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_APA_SHIFT,
				  FTR_UNSIGNED, ID_AA64ISAR1_APA_ARCHITECTED)
	पूर्ण,
	अणु
		HWCAP_CPUID_MATCH(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_API_SHIFT,
				  FTR_UNSIGNED, ID_AA64ISAR1_API_IMP_DEF)
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा arm64_cpu_capabilities ptr_auth_hwcap_gen_matches[] = अणु
	अणु
		HWCAP_CPUID_MATCH(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_GPA_SHIFT,
				  FTR_UNSIGNED, ID_AA64ISAR1_GPA_ARCHITECTED)
	पूर्ण,
	अणु
		HWCAP_CPUID_MATCH(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_GPI_SHIFT,
				  FTR_UNSIGNED, ID_AA64ISAR1_GPI_IMP_DEF)
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा arm64_cpu_capabilities arm64_elf_hwcaps[] = अणु
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_AES_SHIFT, FTR_UNSIGNED, 2, CAP_HWCAP, KERNEL_HWCAP_PMULL),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_AES_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_AES),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_SHA1_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_SHA1),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_SHA2_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_SHA2),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_SHA2_SHIFT, FTR_UNSIGNED, 2, CAP_HWCAP, KERNEL_HWCAP_SHA512),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_CRC32_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_CRC32),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_ATOMICS_SHIFT, FTR_UNSIGNED, 2, CAP_HWCAP, KERNEL_HWCAP_ATOMICS),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_RDM_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_ASIMDRDM),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_SHA3_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_SHA3),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_SM3_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_SM3),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_SM4_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_SM4),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_DP_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_ASIMDDP),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_FHM_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_ASIMDFHM),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_TS_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_FLAGM),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_TS_SHIFT, FTR_UNSIGNED, 2, CAP_HWCAP, KERNEL_HWCAP_FLAGM2),
	HWCAP_CAP(SYS_ID_AA64ISAR0_EL1, ID_AA64ISAR0_RNDR_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_RNG),
	HWCAP_CAP(SYS_ID_AA64PFR0_EL1, ID_AA64PFR0_FP_SHIFT, FTR_SIGNED, 0, CAP_HWCAP, KERNEL_HWCAP_FP),
	HWCAP_CAP(SYS_ID_AA64PFR0_EL1, ID_AA64PFR0_FP_SHIFT, FTR_SIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_FPHP),
	HWCAP_CAP(SYS_ID_AA64PFR0_EL1, ID_AA64PFR0_ASIMD_SHIFT, FTR_SIGNED, 0, CAP_HWCAP, KERNEL_HWCAP_ASIMD),
	HWCAP_CAP(SYS_ID_AA64PFR0_EL1, ID_AA64PFR0_ASIMD_SHIFT, FTR_SIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_ASIMDHP),
	HWCAP_CAP(SYS_ID_AA64PFR0_EL1, ID_AA64PFR0_DIT_SHIFT, FTR_SIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_DIT),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_DPB_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_DCPOP),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_DPB_SHIFT, FTR_UNSIGNED, 2, CAP_HWCAP, KERNEL_HWCAP_DCPODP),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_JSCVT_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_JSCVT),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_FCMA_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_FCMA),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_LRCPC_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_LRCPC),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_LRCPC_SHIFT, FTR_UNSIGNED, 2, CAP_HWCAP, KERNEL_HWCAP_ILRCPC),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_FRINTTS_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_FRINT),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_SB_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_SB),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_BF16_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_BF16),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_DGH_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_DGH),
	HWCAP_CAP(SYS_ID_AA64ISAR1_EL1, ID_AA64ISAR1_I8MM_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_I8MM),
	HWCAP_CAP(SYS_ID_AA64MMFR2_EL1, ID_AA64MMFR2_AT_SHIFT, FTR_UNSIGNED, 1, CAP_HWCAP, KERNEL_HWCAP_USCAT),
#अगर_घोषित CONFIG_ARM64_SVE
	HWCAP_CAP(SYS_ID_AA64PFR0_EL1, ID_AA64PFR0_SVE_SHIFT, FTR_UNSIGNED, ID_AA64PFR0_SVE, CAP_HWCAP, KERNEL_HWCAP_SVE),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_SVEVER_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_SVEVER_SVE2, CAP_HWCAP, KERNEL_HWCAP_SVE2),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_AES_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_AES, CAP_HWCAP, KERNEL_HWCAP_SVEAES),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_AES_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_AES_PMULL, CAP_HWCAP, KERNEL_HWCAP_SVEPMULL),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_BITPERM_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_BITPERM, CAP_HWCAP, KERNEL_HWCAP_SVEBITPERM),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_BF16_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_BF16, CAP_HWCAP, KERNEL_HWCAP_SVEBF16),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_SHA3_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_SHA3, CAP_HWCAP, KERNEL_HWCAP_SVESHA3),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_SM4_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_SM4, CAP_HWCAP, KERNEL_HWCAP_SVESM4),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_I8MM_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_I8MM, CAP_HWCAP, KERNEL_HWCAP_SVEI8MM),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_F32MM_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_F32MM, CAP_HWCAP, KERNEL_HWCAP_SVEF32MM),
	HWCAP_CAP(SYS_ID_AA64ZFR0_EL1, ID_AA64ZFR0_F64MM_SHIFT, FTR_UNSIGNED, ID_AA64ZFR0_F64MM, CAP_HWCAP, KERNEL_HWCAP_SVEF64MM),
#पूर्ण_अगर
	HWCAP_CAP(SYS_ID_AA64PFR1_EL1, ID_AA64PFR1_SSBS_SHIFT, FTR_UNSIGNED, ID_AA64PFR1_SSBS_PSTATE_INSNS, CAP_HWCAP, KERNEL_HWCAP_SSBS),
#अगर_घोषित CONFIG_ARM64_BTI
	HWCAP_CAP(SYS_ID_AA64PFR1_EL1, ID_AA64PFR1_BT_SHIFT, FTR_UNSIGNED, ID_AA64PFR1_BT_BTI, CAP_HWCAP, KERNEL_HWCAP_BTI),
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_PTR_AUTH
	HWCAP_MULTI_CAP(ptr_auth_hwcap_addr_matches, CAP_HWCAP, KERNEL_HWCAP_PACA),
	HWCAP_MULTI_CAP(ptr_auth_hwcap_gen_matches, CAP_HWCAP, KERNEL_HWCAP_PACG),
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_MTE
	HWCAP_CAP(SYS_ID_AA64PFR1_EL1, ID_AA64PFR1_MTE_SHIFT, FTR_UNSIGNED, ID_AA64PFR1_MTE, CAP_HWCAP, KERNEL_HWCAP_MTE),
#पूर्ण_अगर /* CONFIG_ARM64_MTE */
	अणुपूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल bool compat_has_neon(स्थिर काष्ठा arm64_cpu_capabilities *cap, पूर्णांक scope)
अणु
	/*
	 * Check that all of MVFR1_EL1.अणुSIMDSP, SIMDInt, SIMDLSपूर्ण are available,
	 * in line with that of arm32 as in vfp_init(). We make sure that the
	 * check is future proof, by making sure value is non-zero.
	 */
	u32 mvfr1;

	WARN_ON(scope == SCOPE_LOCAL_CPU && preemptible());
	अगर (scope == SCOPE_SYSTEM)
		mvfr1 = पढ़ो_sanitised_ftr_reg(SYS_MVFR1_EL1);
	अन्यथा
		mvfr1 = पढ़ो_sysreg_s(SYS_MVFR1_EL1);

	वापस cpuid_feature_extract_अचिन्हित_field(mvfr1, MVFR1_SIMDSP_SHIFT) &&
		cpuid_feature_extract_अचिन्हित_field(mvfr1, MVFR1_SIMDINT_SHIFT) &&
		cpuid_feature_extract_अचिन्हित_field(mvfr1, MVFR1_SIMDLS_SHIFT);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा arm64_cpu_capabilities compat_elf_hwcaps[] = अणु
#अगर_घोषित CONFIG_COMPAT
	HWCAP_CAP_MATCH(compat_has_neon, CAP_COMPAT_HWCAP, COMPAT_HWCAP_NEON),
	HWCAP_CAP(SYS_MVFR1_EL1, MVFR1_SIMDFMAC_SHIFT, FTR_UNSIGNED, 1, CAP_COMPAT_HWCAP, COMPAT_HWCAP_VFPv4),
	/* Arm v8 mandates MVFR0.FPDP == अणु0, 2पूर्ण. So, piggy back on this क्रम the presence of VFP support */
	HWCAP_CAP(SYS_MVFR0_EL1, MVFR0_FPDP_SHIFT, FTR_UNSIGNED, 2, CAP_COMPAT_HWCAP, COMPAT_HWCAP_VFP),
	HWCAP_CAP(SYS_MVFR0_EL1, MVFR0_FPDP_SHIFT, FTR_UNSIGNED, 2, CAP_COMPAT_HWCAP, COMPAT_HWCAP_VFPv3),
	HWCAP_CAP(SYS_ID_ISAR5_EL1, ID_ISAR5_AES_SHIFT, FTR_UNSIGNED, 2, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_PMULL),
	HWCAP_CAP(SYS_ID_ISAR5_EL1, ID_ISAR5_AES_SHIFT, FTR_UNSIGNED, 1, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_AES),
	HWCAP_CAP(SYS_ID_ISAR5_EL1, ID_ISAR5_SHA1_SHIFT, FTR_UNSIGNED, 1, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_SHA1),
	HWCAP_CAP(SYS_ID_ISAR5_EL1, ID_ISAR5_SHA2_SHIFT, FTR_UNSIGNED, 1, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_SHA2),
	HWCAP_CAP(SYS_ID_ISAR5_EL1, ID_ISAR5_CRC32_SHIFT, FTR_UNSIGNED, 1, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_CRC32),
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;

अटल व्योम __init cap_set_elf_hwcap(स्थिर काष्ठा arm64_cpu_capabilities *cap)
अणु
	चयन (cap->hwcap_type) अणु
	हाल CAP_HWCAP:
		cpu_set_feature(cap->hwcap);
		अवरोध;
#अगर_घोषित CONFIG_COMPAT
	हाल CAP_COMPAT_HWCAP:
		compat_elf_hwcap |= (u32)cap->hwcap;
		अवरोध;
	हाल CAP_COMPAT_HWCAP2:
		compat_elf_hwcap2 |= (u32)cap->hwcap;
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

/* Check अगर we have a particular HWCAP enabled */
अटल bool cpus_have_elf_hwcap(स्थिर काष्ठा arm64_cpu_capabilities *cap)
अणु
	bool rc;

	चयन (cap->hwcap_type) अणु
	हाल CAP_HWCAP:
		rc = cpu_have_feature(cap->hwcap);
		अवरोध;
#अगर_घोषित CONFIG_COMPAT
	हाल CAP_COMPAT_HWCAP:
		rc = (compat_elf_hwcap & (u32)cap->hwcap) != 0;
		अवरोध;
	हाल CAP_COMPAT_HWCAP2:
		rc = (compat_elf_hwcap2 & (u32)cap->hwcap) != 0;
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON(1);
		rc = false;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम __init setup_elf_hwcaps(स्थिर काष्ठा arm64_cpu_capabilities *hwcaps)
अणु
	/* We support emulation of accesses to CPU ID feature रेजिस्टरs */
	cpu_set_named_feature(CPUID);
	क्रम (; hwcaps->matches; hwcaps++)
		अगर (hwcaps->matches(hwcaps, cpucap_शेष_scope(hwcaps)))
			cap_set_elf_hwcap(hwcaps);
पूर्ण

अटल व्योम update_cpu_capabilities(u16 scope_mask)
अणु
	पूर्णांक i;
	स्थिर काष्ठा arm64_cpu_capabilities *caps;

	scope_mask &= ARM64_CPUCAP_SCOPE_MASK;
	क्रम (i = 0; i < ARM64_NCAPS; i++) अणु
		caps = cpu_hwcaps_ptrs[i];
		अगर (!caps || !(caps->type & scope_mask) ||
		    cpus_have_cap(caps->capability) ||
		    !caps->matches(caps, cpucap_शेष_scope(caps)))
			जारी;

		अगर (caps->desc)
			pr_info("detected: %s\n", caps->desc);
		cpus_set_cap(caps->capability);

		अगर ((scope_mask & SCOPE_BOOT_CPU) && (caps->type & SCOPE_BOOT_CPU))
			set_bit(caps->capability, boot_capabilities);
	पूर्ण
पूर्ण

/*
 * Enable all the available capabilities on this CPU. The capabilities
 * with BOOT_CPU scope are handled separately and hence skipped here.
 */
अटल पूर्णांक cpu_enable_non_boot_scope_capabilities(व्योम *__unused)
अणु
	पूर्णांक i;
	u16 non_boot_scope = SCOPE_ALL & ~SCOPE_BOOT_CPU;

	क्रम_each_available_cap(i) अणु
		स्थिर काष्ठा arm64_cpu_capabilities *cap = cpu_hwcaps_ptrs[i];

		अगर (WARN_ON(!cap))
			जारी;

		अगर (!(cap->type & non_boot_scope))
			जारी;

		अगर (cap->cpu_enable)
			cap->cpu_enable(cap);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Run through the enabled capabilities and enable() it on all active
 * CPUs
 */
अटल व्योम __init enable_cpu_capabilities(u16 scope_mask)
अणु
	पूर्णांक i;
	स्थिर काष्ठा arm64_cpu_capabilities *caps;
	bool boot_scope;

	scope_mask &= ARM64_CPUCAP_SCOPE_MASK;
	boot_scope = !!(scope_mask & SCOPE_BOOT_CPU);

	क्रम (i = 0; i < ARM64_NCAPS; i++) अणु
		अचिन्हित पूर्णांक num;

		caps = cpu_hwcaps_ptrs[i];
		अगर (!caps || !(caps->type & scope_mask))
			जारी;
		num = caps->capability;
		अगर (!cpus_have_cap(num))
			जारी;

		/* Ensure cpus_have_स्थिर_cap(num) works */
		अटल_branch_enable(&cpu_hwcap_keys[num]);

		अगर (boot_scope && caps->cpu_enable)
			/*
			 * Capabilities with SCOPE_BOOT_CPU scope are finalised
			 * beक्रमe any secondary CPU boots. Thus, each secondary
			 * will enable the capability as appropriate via
			 * check_local_cpu_capabilities(). The only exception is
			 * the boot CPU, क्रम which the capability must be
			 * enabled here. This approach aव्योमs costly
			 * stop_machine() calls क्रम this हाल.
			 */
			caps->cpu_enable(caps);
	पूर्ण

	/*
	 * For all non-boot scope capabilities, use stop_machine()
	 * as it schedules the work allowing us to modअगरy PSTATE,
	 * instead of on_each_cpu() which uses an IPI, giving us a
	 * PSTATE that disappears when we वापस.
	 */
	अगर (!boot_scope)
		stop_machine(cpu_enable_non_boot_scope_capabilities,
			     शून्य, cpu_online_mask);
पूर्ण

/*
 * Run through the list of capabilities to check क्रम conflicts.
 * If the प्रणाली has alपढ़ोy detected a capability, take necessary
 * action on this CPU.
 */
अटल व्योम verअगरy_local_cpu_caps(u16 scope_mask)
अणु
	पूर्णांक i;
	bool cpu_has_cap, प्रणाली_has_cap;
	स्थिर काष्ठा arm64_cpu_capabilities *caps;

	scope_mask &= ARM64_CPUCAP_SCOPE_MASK;

	क्रम (i = 0; i < ARM64_NCAPS; i++) अणु
		caps = cpu_hwcaps_ptrs[i];
		अगर (!caps || !(caps->type & scope_mask))
			जारी;

		cpu_has_cap = caps->matches(caps, SCOPE_LOCAL_CPU);
		प्रणाली_has_cap = cpus_have_cap(caps->capability);

		अगर (प्रणाली_has_cap) अणु
			/*
			 * Check अगर the new CPU misses an advertised feature,
			 * which is not safe to miss.
			 */
			अगर (!cpu_has_cap && !cpucap_late_cpu_optional(caps))
				अवरोध;
			/*
			 * We have to issue cpu_enable() irrespective of
			 * whether the CPU has it or not, as it is enabeld
			 * प्रणाली wide. It is upto the call back to take
			 * appropriate action on this CPU.
			 */
			अगर (caps->cpu_enable)
				caps->cpu_enable(caps);
		पूर्ण अन्यथा अणु
			/*
			 * Check अगर the CPU has this capability अगर it isn't
			 * safe to have when the प्रणाली करोesn't.
			 */
			अगर (cpu_has_cap && !cpucap_late_cpu_permitted(caps))
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (i < ARM64_NCAPS) अणु
		pr_crit("CPU%d: Detected conflict for capability %d (%s), System: %d, CPU: %d\n",
			smp_processor_id(), caps->capability,
			caps->desc, प्रणाली_has_cap, cpu_has_cap);

		अगर (cpucap_panic_on_conflict(caps))
			cpu_panic_kernel();
		अन्यथा
			cpu_die_early();
	पूर्ण
पूर्ण

/*
 * Check क्रम CPU features that are used in early boot
 * based on the Boot CPU value.
 */
अटल व्योम check_early_cpu_features(व्योम)
अणु
	verअगरy_cpu_asid_bits();

	verअगरy_local_cpu_caps(SCOPE_BOOT_CPU);
पूर्ण

अटल व्योम
verअगरy_local_elf_hwcaps(स्थिर काष्ठा arm64_cpu_capabilities *caps)
अणु

	क्रम (; caps->matches; caps++)
		अगर (cpus_have_elf_hwcap(caps) && !caps->matches(caps, SCOPE_LOCAL_CPU)) अणु
			pr_crit("CPU%d: missing HWCAP: %s\n",
					smp_processor_id(), caps->desc);
			cpu_die_early();
		पूर्ण
पूर्ण

अटल व्योम verअगरy_sve_features(व्योम)
अणु
	u64 safe_zcr = पढ़ो_sanitised_ftr_reg(SYS_ZCR_EL1);
	u64 zcr = पढ़ो_zcr_features();

	अचिन्हित पूर्णांक safe_len = safe_zcr & ZCR_ELx_LEN_MASK;
	अचिन्हित पूर्णांक len = zcr & ZCR_ELx_LEN_MASK;

	अगर (len < safe_len || sve_verअगरy_vq_map()) अणु
		pr_crit("CPU%d: SVE: vector length support mismatch\n",
			smp_processor_id());
		cpu_die_early();
	पूर्ण

	/* Add checks on other ZCR bits here अगर necessary */
पूर्ण

अटल व्योम verअगरy_hyp_capabilities(व्योम)
अणु
	u64 safe_mmfr1, mmfr0, mmfr1;
	पूर्णांक parange, ipa_max;
	अचिन्हित पूर्णांक safe_vmid_bits, vmid_bits;

	अगर (!IS_ENABLED(CONFIG_KVM))
		वापस;

	safe_mmfr1 = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR1_EL1);
	mmfr0 = पढ़ो_cpuid(ID_AA64MMFR0_EL1);
	mmfr1 = पढ़ो_cpuid(ID_AA64MMFR1_EL1);

	/* Verअगरy VMID bits */
	safe_vmid_bits = get_vmid_bits(safe_mmfr1);
	vmid_bits = get_vmid_bits(mmfr1);
	अगर (vmid_bits < safe_vmid_bits) अणु
		pr_crit("CPU%d: VMID width mismatch\n", smp_processor_id());
		cpu_die_early();
	पूर्ण

	/* Verअगरy IPA range */
	parange = cpuid_feature_extract_अचिन्हित_field(mmfr0,
				ID_AA64MMFR0_PARANGE_SHIFT);
	ipa_max = id_aa64mmfr0_parange_to_phys_shअगरt(parange);
	अगर (ipa_max < get_kvm_ipa_limit()) अणु
		pr_crit("CPU%d: IPA range mismatch\n", smp_processor_id());
		cpu_die_early();
	पूर्ण
पूर्ण

/*
 * Run through the enabled प्रणाली capabilities and enable() it on this CPU.
 * The capabilities were decided based on the available CPUs at the boot समय.
 * Any new CPU should match the प्रणाली wide status of the capability. If the
 * new CPU करोesn't have a capability which the प्रणाली now has enabled, we
 * cannot करो anything to fix it up and could cause unexpected failures. So
 * we park the CPU.
 */
अटल व्योम verअगरy_local_cpu_capabilities(व्योम)
अणु
	/*
	 * The capabilities with SCOPE_BOOT_CPU are checked from
	 * check_early_cpu_features(), as they need to be verअगरied
	 * on all secondary CPUs.
	 */
	verअगरy_local_cpu_caps(SCOPE_ALL & ~SCOPE_BOOT_CPU);

	verअगरy_local_elf_hwcaps(arm64_elf_hwcaps);

	अगर (प्रणाली_supports_32bit_el0())
		verअगरy_local_elf_hwcaps(compat_elf_hwcaps);

	अगर (प्रणाली_supports_sve())
		verअगरy_sve_features();

	अगर (is_hyp_mode_available())
		verअगरy_hyp_capabilities();
पूर्ण

व्योम check_local_cpu_capabilities(व्योम)
अणु
	/*
	 * All secondary CPUs should conक्रमm to the early CPU features
	 * in use by the kernel based on boot CPU.
	 */
	check_early_cpu_features();

	/*
	 * If we haven't finalised the प्रणाली capabilities, this CPU माला_लो
	 * a chance to update the errata work arounds and local features.
	 * Otherwise, this CPU should verअगरy that it has all the प्रणाली
	 * advertised capabilities.
	 */
	अगर (!प्रणाली_capabilities_finalized())
		update_cpu_capabilities(SCOPE_LOCAL_CPU);
	अन्यथा
		verअगरy_local_cpu_capabilities();
पूर्ण

अटल व्योम __init setup_boot_cpu_capabilities(व्योम)
अणु
	/* Detect capabilities with either SCOPE_BOOT_CPU or SCOPE_LOCAL_CPU */
	update_cpu_capabilities(SCOPE_BOOT_CPU | SCOPE_LOCAL_CPU);
	/* Enable the SCOPE_BOOT_CPU capabilities alone right away */
	enable_cpu_capabilities(SCOPE_BOOT_CPU);
पूर्ण

bool this_cpu_has_cap(अचिन्हित पूर्णांक n)
अणु
	अगर (!WARN_ON(preemptible()) && n < ARM64_NCAPS) अणु
		स्थिर काष्ठा arm64_cpu_capabilities *cap = cpu_hwcaps_ptrs[n];

		अगर (cap)
			वापस cap->matches(cap, SCOPE_LOCAL_CPU);
	पूर्ण

	वापस false;
पूर्ण

/*
 * This helper function is used in a narrow winकरोw when,
 * - The प्रणाली wide safe रेजिस्टरs are set with all the SMP CPUs and,
 * - The SYSTEM_FEATURE cpu_hwcaps may not have been set.
 * In all other हालs cpus_have_अणुस्थिर_पूर्णcap() should be used.
 */
अटल bool __maybe_unused __प्रणाली_matches_cap(अचिन्हित पूर्णांक n)
अणु
	अगर (n < ARM64_NCAPS) अणु
		स्थिर काष्ठा arm64_cpu_capabilities *cap = cpu_hwcaps_ptrs[n];

		अगर (cap)
			वापस cap->matches(cap, SCOPE_SYSTEM);
	पूर्ण
	वापस false;
पूर्ण

व्योम cpu_set_feature(अचिन्हित पूर्णांक num)
अणु
	WARN_ON(num >= MAX_CPU_FEATURES);
	elf_hwcap |= BIT(num);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_set_feature);

bool cpu_have_feature(अचिन्हित पूर्णांक num)
अणु
	WARN_ON(num >= MAX_CPU_FEATURES);
	वापस elf_hwcap & BIT(num);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_have_feature);

अचिन्हित दीर्घ cpu_get_elf_hwcap(व्योम)
अणु
	/*
	 * We currently only populate the first 32 bits of AT_HWCAP. Please
	 * note that क्रम userspace compatibility we guarantee that bits 62
	 * and 63 will always be वापसed as 0.
	 */
	वापस lower_32_bits(elf_hwcap);
पूर्ण

अचिन्हित दीर्घ cpu_get_elf_hwcap2(व्योम)
अणु
	वापस upper_32_bits(elf_hwcap);
पूर्ण

अटल व्योम __init setup_प्रणाली_capabilities(व्योम)
अणु
	/*
	 * We have finalised the प्रणाली-wide safe feature
	 * रेजिस्टरs, finalise the capabilities that depend
	 * on it. Also enable all the available capabilities,
	 * that are not enabled alपढ़ोy.
	 */
	update_cpu_capabilities(SCOPE_SYSTEM);
	enable_cpu_capabilities(SCOPE_ALL & ~SCOPE_BOOT_CPU);
पूर्ण

व्योम __init setup_cpu_features(व्योम)
अणु
	u32 cwg;

	setup_प्रणाली_capabilities();
	setup_elf_hwcaps(arm64_elf_hwcaps);

	अगर (प्रणाली_supports_32bit_el0())
		setup_elf_hwcaps(compat_elf_hwcaps);

	अगर (प्रणाली_uses_ttbr0_pan())
		pr_info("emulated: Privileged Access Never (PAN) using TTBR0_EL1 switching\n");

	sve_setup();
	minsigstksz_setup();

	/* Advertise that we have computed the प्रणाली capabilities */
	finalize_प्रणाली_capabilities();

	/*
	 * Check क्रम sane CTR_EL0.CWG value.
	 */
	cwg = cache_type_cwg();
	अगर (!cwg)
		pr_warn("No Cache Writeback Granule information, assuming %d\n",
			ARCH_DMA_MINALIGN);
पूर्ण

अटल व्योम __maybe_unused cpu_enable_cnp(काष्ठा arm64_cpu_capabilities स्थिर *cap)
अणु
	cpu_replace_ttbr1(lm_alias(swapper_pg_dir));
पूर्ण

/*
 * We emulate only the following प्रणाली रेजिस्टर space.
 * Op0 = 0x3, CRn = 0x0, Op1 = 0x0, CRm = [0, 4 - 7]
 * See Table C5-6 System inकाष्ठाion encodings क्रम System रेजिस्टर accesses,
 * ARMv8 ARM(ARM DDI 0487A.f) क्रम more details.
 */
अटल अंतरभूत bool __attribute_स्थिर__ is_emulated(u32 id)
अणु
	वापस (sys_reg_Op0(id) == 0x3 &&
		sys_reg_CRn(id) == 0x0 &&
		sys_reg_Op1(id) == 0x0 &&
		(sys_reg_CRm(id) == 0 ||
		 ((sys_reg_CRm(id) >= 4) && (sys_reg_CRm(id) <= 7))));
पूर्ण

/*
 * With CRm == 0, reg should be one of :
 * MIDR_EL1, MPIDR_EL1 or REVIDR_EL1.
 */
अटल अंतरभूत पूर्णांक emulate_id_reg(u32 id, u64 *valp)
अणु
	चयन (id) अणु
	हाल SYS_MIDR_EL1:
		*valp = पढ़ो_cpuid_id();
		अवरोध;
	हाल SYS_MPIDR_EL1:
		*valp = SYS_MPIDR_SAFE_VAL;
		अवरोध;
	हाल SYS_REVIDR_EL1:
		/* IMPLEMENTATION DEFINED values are emulated with 0 */
		*valp = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक emulate_sys_reg(u32 id, u64 *valp)
अणु
	काष्ठा arm64_ftr_reg *regp;

	अगर (!is_emulated(id))
		वापस -EINVAL;

	अगर (sys_reg_CRm(id) == 0)
		वापस emulate_id_reg(id, valp);

	regp = get_arm64_ftr_reg_nowarn(id);
	अगर (regp)
		*valp = arm64_ftr_reg_user_value(regp);
	अन्यथा
		/*
		 * The untracked रेजिस्टरs are either IMPLEMENTATION DEFINED
		 * (e.g, ID_AFR0_EL1) or reserved RAZ.
		 */
		*valp = 0;
	वापस 0;
पूर्ण

पूर्णांक करो_emulate_mrs(काष्ठा pt_regs *regs, u32 sys_reg, u32 rt)
अणु
	पूर्णांक rc;
	u64 val;

	rc = emulate_sys_reg(sys_reg, &val);
	अगर (!rc) अणु
		pt_regs_ग_लिखो_reg(regs, rt, val);
		arm64_skip_faulting_inकाष्ठाion(regs, AARCH64_INSN_SIZE);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक emulate_mrs(काष्ठा pt_regs *regs, u32 insn)
अणु
	u32 sys_reg, rt;

	/*
	 * sys_reg values are defined as used in mrs/msr inकाष्ठाion.
	 * shअगरt the imm value to get the encoding.
	 */
	sys_reg = (u32)aarch64_insn_decode_immediate(AARCH64_INSN_IMM_16, insn) << 5;
	rt = aarch64_insn_decode_रेजिस्टर(AARCH64_INSN_REGTYPE_RT, insn);
	वापस करो_emulate_mrs(regs, sys_reg, rt);
पूर्ण

अटल काष्ठा undef_hook mrs_hook = अणु
	.instr_mask = 0xfff00000,
	.instr_val  = 0xd5300000,
	.pstate_mask = PSR_AA32_MODE_MASK,
	.pstate_val = PSR_MODE_EL0t,
	.fn = emulate_mrs,
पूर्ण;

अटल पूर्णांक __init enable_mrs_emulation(व्योम)
अणु
	रेजिस्टर_undef_hook(&mrs_hook);
	वापस 0;
पूर्ण

core_initcall(enable_mrs_emulation);

क्रमागत mitigation_state arm64_get_meltकरोwn_state(व्योम)
अणु
	अगर (__meltकरोwn_safe)
		वापस SPECTRE_UNAFFECTED;

	अगर (arm64_kernel_unmapped_at_el0())
		वापस SPECTRE_MITIGATED;

	वापस SPECTRE_VULNERABLE;
पूर्ण

sमाप_प्रकार cpu_show_meltकरोwn(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	चयन (arm64_get_meltकरोwn_state()) अणु
	हाल SPECTRE_UNAFFECTED:
		वापस प्र_लिखो(buf, "Not affected\n");

	हाल SPECTRE_MITIGATED:
		वापस प्र_लिखो(buf, "Mitigation: PTI\n");

	शेष:
		वापस प्र_लिखो(buf, "Vulnerable\n");
	पूर्ण
पूर्ण

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#अगर_अघोषित __ASM_CPUFEATURE_H
#घोषणा __ASM_CPUFEATURE_H

#समावेश <यंत्र/cpucaps.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/sysreg.h>

#घोषणा MAX_CPU_FEATURES	64
#घोषणा cpu_feature(x)		KERNEL_HWCAP_ ## x

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bug.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>

/*
 * CPU feature रेजिस्टर tracking
 *
 * The safe value of a CPUID feature field is dependent on the implications
 * of the values asचिन्हित to it by the architecture. Based on the relationship
 * between the values, the features are classअगरied पूर्णांकo 3 types - LOWER_SAFE,
 * HIGHER_SAFE and EXACT.
 *
 * The lowest value of all the CPUs is chosen क्रम LOWER_SAFE and highest
 * क्रम HIGHER_SAFE. It is expected that all CPUs have the same value क्रम
 * a field when EXACT is specअगरied, failing which, the safe value specअगरied
 * in the table is chosen.
 */

क्रमागत ftr_type अणु
	FTR_EXACT,			/* Use a predefined safe value */
	FTR_LOWER_SAFE,			/* Smaller value is safe */
	FTR_HIGHER_SAFE,		/* Bigger value is safe */
	FTR_HIGHER_OR_ZERO_SAFE,	/* Bigger value is safe, but 0 is biggest */
पूर्ण;

#घोषणा FTR_STRICT	true	/* SANITY check strict matching required */
#घोषणा FTR_NONSTRICT	false	/* SANITY check ignored */

#घोषणा FTR_SIGNED	true	/* Value should be treated as चिन्हित */
#घोषणा FTR_UNSIGNED	false	/* Value should be treated as अचिन्हित */

#घोषणा FTR_VISIBLE	true	/* Feature visible to the user space */
#घोषणा FTR_HIDDEN	false	/* Feature is hidden from the user */

#घोषणा FTR_VISIBLE_IF_IS_ENABLED(config)		\
	(IS_ENABLED(config) ? FTR_VISIBLE : FTR_HIDDEN)

काष्ठा arm64_ftr_bits अणु
	bool		sign;	/* Value is चिन्हित ? */
	bool		visible;
	bool		strict;	/* CPU Sanity check: strict matching required ? */
	क्रमागत ftr_type	type;
	u8		shअगरt;
	u8		width;
	s64		safe_val; /* safe value क्रम FTR_EXACT features */
पूर्ण;

/*
 * Describe the early feature override to the core override code:
 *
 * @val			Values that are to be merged पूर्णांकo the final
 *			sanitised value of the रेजिस्टर. Only the bitfields
 *			set to 1 in @mask are valid
 * @mask		Mask of the features that are overridden by @val
 *
 * A @mask field set to full-1 indicates that the corresponding field
 * in @val is a valid override.
 *
 * A @mask field set to full-0 with the corresponding @val field set
 * to full-0 denotes that this field has no override
 *
 * A @mask field set to full-0 with the corresponding @val field set
 * to full-1 denotes thath this field has an invalid override.
 */
काष्ठा arm64_ftr_override अणु
	u64		val;
	u64		mask;
पूर्ण;

/*
 * @arm64_ftr_reg - Feature रेजिस्टर
 * @strict_mask		Bits which should match across all CPUs क्रम sanity.
 * @sys_val		Safe value across the CPUs (प्रणाली view)
 */
काष्ठा arm64_ftr_reg अणु
	स्थिर अक्षर			*name;
	u64				strict_mask;
	u64				user_mask;
	u64				sys_val;
	u64				user_val;
	काष्ठा arm64_ftr_override	*override;
	स्थिर काष्ठा arm64_ftr_bits	*ftr_bits;
पूर्ण;

बाह्य काष्ठा arm64_ftr_reg arm64_ftr_reg_ctrel0;

/*
 * CPU capabilities:
 *
 * We use arm64_cpu_capabilities to represent प्रणाली features, errata work
 * arounds (both used पूर्णांकernally by kernel and tracked in cpu_hwcaps) and
 * ELF HWCAPs (which are exposed to user).
 *
 * To support प्रणालीs with heterogeneous CPUs, we need to make sure that we
 * detect the capabilities correctly on the प्रणाली and take appropriate
 * measures to ensure there are no incompatibilities.
 *
 * This comment tries to explain how we treat the capabilities.
 * Each capability has the following list of attributes :
 *
 * 1) Scope of Detection : The प्रणाली detects a given capability by
 *    perक्रमming some checks at runसमय. This could be, e.g, checking the
 *    value of a field in CPU ID feature रेजिस्टर or checking the cpu
 *    model. The capability provides a call back ( @matches() ) to
 *    perक्रमm the check. Scope defines how the checks should be perक्रमmed.
 *    There are three हालs:
 *
 *     a) SCOPE_LOCAL_CPU: check all the CPUs and "detect" अगर at least one
 *        matches. This implies, we have to run the check on all the
 *        booting CPUs, until the प्रणाली decides that state of the
 *        capability is finalised. (See section 2 below)
 *		Or
 *     b) SCOPE_SYSTEM: check all the CPUs and "detect" अगर all the CPUs
 *        matches. This implies, we run the check only once, when the
 *        प्रणाली decides to finalise the state of the capability. If the
 *        capability relies on a field in one of the CPU ID feature
 *        रेजिस्टरs, we use the sanitised value of the रेजिस्टर from the
 *        CPU feature infraकाष्ठाure to make the decision.
 *		Or
 *     c) SCOPE_BOOT_CPU: Check only on the primary boot CPU to detect the
 *        feature. This category is क्रम features that are "finalised"
 *        (or used) by the kernel very early even beक्रमe the SMP cpus
 *        are brought up.
 *
 *    The process of detection is usually denoted by "update" capability
 *    state in the code.
 *
 * 2) Finalise the state : The kernel should finalise the state of a
 *    capability at some poपूर्णांक during its execution and take necessary
 *    actions अगर any. Usually, this is करोne, after all the boot-समय
 *    enabled CPUs are brought up by the kernel, so that it can make
 *    better decision based on the available set of CPUs. However, there
 *    are some special हालs, where the action is taken during the early
 *    boot by the primary boot CPU. (e.g, running the kernel at EL2 with
 *    Virtualisation Host Extensions). The kernel usually disallows any
 *    changes to the state of a capability once it finalises the capability
 *    and takes any action, as it may be impossible to execute the actions
 *    safely. A CPU brought up after a capability is "finalised" is
 *    referred to as "Late CPU" w.r.t the capability. e.g, all secondary
 *    CPUs are treated "late CPUs" क्रम capabilities determined by the boot
 *    CPU.
 *
 *    At the moment there are two passes of finalising the capabilities.
 *      a) Boot CPU scope capabilities - Finalised by primary boot CPU via
 *         setup_boot_cpu_capabilities().
 *      b) Everything except (a) - Run via setup_प्रणाली_capabilities().
 *
 * 3) Verअगरication: When a CPU is brought online (e.g, by user or by the
 *    kernel), the kernel should make sure that it is safe to use the CPU,
 *    by verअगरying that the CPU is compliant with the state of the
 *    capabilities finalised alपढ़ोy. This happens via :
 *
 *	secondary_start_kernel()-> check_local_cpu_capabilities()
 *
 *    As explained in (2) above, capabilities could be finalised at
 *    dअगरferent poपूर्णांकs in the execution. Each newly booted CPU is verअगरied
 *    against the capabilities that have been finalised by the समय it
 *    boots.
 *
 *	a) SCOPE_BOOT_CPU : All CPUs are verअगरied against the capability
 *	except क्रम the primary boot CPU.
 *
 *	b) SCOPE_LOCAL_CPU, SCOPE_SYSTEM: All CPUs hotplugged on by the
 *	user after the kernel boot are verअगरied against the capability.
 *
 *    If there is a conflict, the kernel takes an action, based on the
 *    severity (e.g, a CPU could be prevented from booting or cause a
 *    kernel panic). The CPU is allowed to "affect" the state of the
 *    capability, अगर it has not been finalised alपढ़ोy. See section 5
 *    क्रम more details on conflicts.
 *
 * 4) Action: As mentioned in (2), the kernel can take an action क्रम each
 *    detected capability, on all CPUs on the प्रणाली. Appropriate actions
 *    include, turning on an architectural feature, modअगरying the control
 *    रेजिस्टरs (e.g, SCTLR, TCR etc.) or patching the kernel via
 *    alternatives. The kernel patching is batched and perक्रमmed at later
 *    poपूर्णांक. The actions are always initiated only after the capability
 *    is finalised. This is usally denoted by "enabling" the capability.
 *    The actions are initiated as follows :
 *	a) Action is triggered on all online CPUs, after the capability is
 *	finalised, invoked within the stop_machine() context from
 *	enable_cpu_capabilitie().
 *
 *	b) Any late CPU, brought up after (1), the action is triggered via:
 *
 *	  check_local_cpu_capabilities() -> verअगरy_local_cpu_capabilities()
 *
 * 5) Conflicts: Based on the state of the capability on a late CPU vs.
 *    the प्रणाली state, we could have the following combinations :
 *
 *		x-----------------------------x
 *		| Type  | System   | Late CPU |
 *		|-----------------------------|
 *		|  a    |   y      |    n     |
 *		|-----------------------------|
 *		|  b    |   n      |    y     |
 *		x-----------------------------x
 *
 *     Two separate flag bits are defined to indicate whether each kind of
 *     conflict can be allowed:
 *		ARM64_CPUCAP_OPTIONAL_FOR_LATE_CPU - Case(a) is allowed
 *		ARM64_CPUCAP_PERMITTED_FOR_LATE_CPU - Case(b) is allowed
 *
 *     Case (a) is not permitted क्रम a capability that the प्रणाली requires
 *     all CPUs to have in order क्रम the capability to be enabled. This is
 *     typical क्रम capabilities that represent enhanced functionality.
 *
 *     Case (b) is not permitted क्रम a capability that must be enabled
 *     during boot अगर any CPU in the प्रणाली requires it in order to run
 *     safely. This is typical क्रम erratum work arounds that cannot be
 *     enabled after the corresponding capability is finalised.
 *
 *     In some non-typical हालs either both (a) and (b), or neither,
 *     should be permitted. This can be described by including neither
 *     or both flags in the capability's type field.
 *
 *     In हाल of a conflict, the CPU is prevented from booting. If the
 *     ARM64_CPUCAP_PANIC_ON_CONFLICT flag is specअगरied क्रम the capability,
 *     then a kernel panic is triggered.
 */


/*
 * Decide how the capability is detected.
 * On any local CPU vs System wide vs the primary boot CPU
 */
#घोषणा ARM64_CPUCAP_SCOPE_LOCAL_CPU		((u16)BIT(0))
#घोषणा ARM64_CPUCAP_SCOPE_SYSTEM		((u16)BIT(1))
/*
 * The capabilitiy is detected on the Boot CPU and is used by kernel
 * during early boot. i.e, the capability should be "detected" and
 * "enabled" as early as possibly on all booting CPUs.
 */
#घोषणा ARM64_CPUCAP_SCOPE_BOOT_CPU		((u16)BIT(2))
#घोषणा ARM64_CPUCAP_SCOPE_MASK			\
	(ARM64_CPUCAP_SCOPE_SYSTEM	|	\
	 ARM64_CPUCAP_SCOPE_LOCAL_CPU	|	\
	 ARM64_CPUCAP_SCOPE_BOOT_CPU)

#घोषणा SCOPE_SYSTEM				ARM64_CPUCAP_SCOPE_SYSTEM
#घोषणा SCOPE_LOCAL_CPU				ARM64_CPUCAP_SCOPE_LOCAL_CPU
#घोषणा SCOPE_BOOT_CPU				ARM64_CPUCAP_SCOPE_BOOT_CPU
#घोषणा SCOPE_ALL				ARM64_CPUCAP_SCOPE_MASK

/*
 * Is it permitted क्रम a late CPU to have this capability when प्रणाली
 * hasn't alपढ़ोy enabled it ?
 */
#घोषणा ARM64_CPUCAP_PERMITTED_FOR_LATE_CPU	((u16)BIT(4))
/* Is it safe क्रम a late CPU to miss this capability when प्रणाली has it */
#घोषणा ARM64_CPUCAP_OPTIONAL_FOR_LATE_CPU	((u16)BIT(5))
/* Panic when a conflict is detected */
#घोषणा ARM64_CPUCAP_PANIC_ON_CONFLICT		((u16)BIT(6))

/*
 * CPU errata workarounds that need to be enabled at boot समय अगर one or
 * more CPUs in the प्रणाली requires it. When one of these capabilities
 * has been enabled, it is safe to allow any CPU to boot that करोesn't
 * require the workaround. However, it is not safe अगर a "late" CPU
 * requires a workaround and the प्रणाली hasn't enabled it alपढ़ोy.
 */
#घोषणा ARM64_CPUCAP_LOCAL_CPU_ERRATUM		\
	(ARM64_CPUCAP_SCOPE_LOCAL_CPU | ARM64_CPUCAP_OPTIONAL_FOR_LATE_CPU)
/*
 * CPU feature detected at boot समय based on प्रणाली-wide value of a
 * feature. It is safe क्रम a late CPU to have this feature even though
 * the प्रणाली hasn't enabled it, although the feature will not be used
 * by Linux in this हाल. If the प्रणाली has enabled this feature alपढ़ोy,
 * then every late CPU must have it.
 */
#घोषणा ARM64_CPUCAP_SYSTEM_FEATURE	\
	(ARM64_CPUCAP_SCOPE_SYSTEM | ARM64_CPUCAP_PERMITTED_FOR_LATE_CPU)
/*
 * CPU feature detected at boot समय based on feature of one or more CPUs.
 * All possible conflicts क्रम a late CPU are ignored.
 * NOTE: this means that a late CPU with the feature will *not* cause the
 * capability to be advertised by cpus_have_*cap()!
 */
#घोषणा ARM64_CPUCAP_WEAK_LOCAL_CPU_FEATURE		\
	(ARM64_CPUCAP_SCOPE_LOCAL_CPU		|	\
	 ARM64_CPUCAP_OPTIONAL_FOR_LATE_CPU	|	\
	 ARM64_CPUCAP_PERMITTED_FOR_LATE_CPU)

/*
 * CPU feature detected at boot समय, on one or more CPUs. A late CPU
 * is not allowed to have the capability when the प्रणाली करोesn't have it.
 * It is Ok क्रम a late CPU to miss the feature.
 */
#घोषणा ARM64_CPUCAP_BOOT_RESTRICTED_CPU_LOCAL_FEATURE	\
	(ARM64_CPUCAP_SCOPE_LOCAL_CPU		|	\
	 ARM64_CPUCAP_OPTIONAL_FOR_LATE_CPU)

/*
 * CPU feature used early in the boot based on the boot CPU. All secondary
 * CPUs must match the state of the capability as detected by the boot CPU. In
 * हाल of a conflict, a kernel panic is triggered.
 */
#घोषणा ARM64_CPUCAP_STRICT_BOOT_CPU_FEATURE		\
	(ARM64_CPUCAP_SCOPE_BOOT_CPU | ARM64_CPUCAP_PANIC_ON_CONFLICT)

/*
 * CPU feature used early in the boot based on the boot CPU. It is safe क्रम a
 * late CPU to have this feature even though the boot CPU hasn't enabled it,
 * although the feature will not be used by Linux in this हाल. If the boot CPU
 * has enabled this feature alपढ़ोy, then every late CPU must have it.
 */
#घोषणा ARM64_CPUCAP_BOOT_CPU_FEATURE                  \
	(ARM64_CPUCAP_SCOPE_BOOT_CPU | ARM64_CPUCAP_PERMITTED_FOR_LATE_CPU)

काष्ठा arm64_cpu_capabilities अणु
	स्थिर अक्षर *desc;
	u16 capability;
	u16 type;
	bool (*matches)(स्थिर काष्ठा arm64_cpu_capabilities *caps, पूर्णांक scope);
	/*
	 * Take the appropriate actions to configure this capability
	 * क्रम this CPU. If the capability is detected by the kernel
	 * this will be called on all the CPUs in the प्रणाली,
	 * including the hotplugged CPUs, regardless of whether the
	 * capability is available on that specअगरic CPU. This is
	 * useful क्रम some capabilities (e.g, working around CPU
	 * errata), where all the CPUs must take some action (e.g,
	 * changing प्रणाली control/configuration). Thus, अगर an action
	 * is required only अगर the CPU has the capability, then the
	 * routine must check it beक्रमe taking any action.
	 */
	व्योम (*cpu_enable)(स्थिर काष्ठा arm64_cpu_capabilities *cap);
	जोड़ अणु
		काष्ठा अणु	/* To be used क्रम erratum handling only */
			काष्ठा midr_range midr_range;
			स्थिर काष्ठा arm64_midr_revidr अणु
				u32 midr_rv;		/* revision/variant */
				u32 revidr_mask;
			पूर्ण * स्थिर fixed_revs;
		पूर्ण;

		स्थिर काष्ठा midr_range *midr_range_list;
		काष्ठा अणु	/* Feature रेजिस्टर checking */
			u32 sys_reg;
			u8 field_pos;
			u8 min_field_value;
			u8 hwcap_type;
			bool sign;
			अचिन्हित दीर्घ hwcap;
		पूर्ण;
	पूर्ण;

	/*
	 * An optional list of "matches/cpu_enable" pair क्रम the same
	 * "capability" of the same "type" as described by the parent.
	 * Only matches(), cpu_enable() and fields relevant to these
	 * methods are signअगरicant in the list. The cpu_enable is
	 * invoked only अगर the corresponding entry "matches()".
	 * However, अगर a cpu_enable() method is associated
	 * with multiple matches(), care should be taken that either
	 * the match criteria are mutually exclusive, or that the
	 * method is robust against being called multiple बार.
	 */
	स्थिर काष्ठा arm64_cpu_capabilities *match_list;
पूर्ण;

अटल अंतरभूत पूर्णांक cpucap_शेष_scope(स्थिर काष्ठा arm64_cpu_capabilities *cap)
अणु
	वापस cap->type & ARM64_CPUCAP_SCOPE_MASK;
पूर्ण

/*
 * Generic helper क्रम handling capabilities with multiple (match,enable) pairs
 * of call backs, sharing the same capability bit.
 * Iterate over each entry to see अगर at least one matches.
 */
अटल अंतरभूत bool
cpucap_multi_entry_cap_matches(स्थिर काष्ठा arm64_cpu_capabilities *entry,
			       पूर्णांक scope)
अणु
	स्थिर काष्ठा arm64_cpu_capabilities *caps;

	क्रम (caps = entry->match_list; caps->matches; caps++)
		अगर (caps->matches(caps, scope))
			वापस true;

	वापस false;
पूर्ण

अटल __always_अंतरभूत bool is_vhe_hyp_code(व्योम)
अणु
	/* Only defined क्रम code run in VHE hyp context */
	वापस __is_defined(__KVM_VHE_HYPERVISOR__);
पूर्ण

अटल __always_अंतरभूत bool is_nvhe_hyp_code(व्योम)
अणु
	/* Only defined क्रम code run in NVHE hyp context */
	वापस __is_defined(__KVM_NVHE_HYPERVISOR__);
पूर्ण

अटल __always_अंतरभूत bool is_hyp_code(व्योम)
अणु
	वापस is_vhe_hyp_code() || is_nvhe_hyp_code();
पूर्ण

बाह्य DECLARE_BITMAP(cpu_hwcaps, ARM64_NCAPS);
बाह्य काष्ठा अटल_key_false cpu_hwcap_keys[ARM64_NCAPS];
बाह्य काष्ठा अटल_key_false arm64_स्थिर_caps_पढ़ोy;

/* ARM64 CAPS + alternative_cb */
#घोषणा ARM64_NPATCHABLE (ARM64_NCAPS + 1)
बाह्य DECLARE_BITMAP(boot_capabilities, ARM64_NPATCHABLE);

#घोषणा क्रम_each_available_cap(cap)		\
	क्रम_each_set_bit(cap, cpu_hwcaps, ARM64_NCAPS)

bool this_cpu_has_cap(अचिन्हित पूर्णांक cap);
व्योम cpu_set_feature(अचिन्हित पूर्णांक num);
bool cpu_have_feature(अचिन्हित पूर्णांक num);
अचिन्हित दीर्घ cpu_get_elf_hwcap(व्योम);
अचिन्हित दीर्घ cpu_get_elf_hwcap2(व्योम);

#घोषणा cpu_set_named_feature(name) cpu_set_feature(cpu_feature(name))
#घोषणा cpu_have_named_feature(name) cpu_have_feature(cpu_feature(name))

अटल __always_अंतरभूत bool प्रणाली_capabilities_finalized(व्योम)
अणु
	वापस अटल_branch_likely(&arm64_स्थिर_caps_पढ़ोy);
पूर्ण

/*
 * Test क्रम a capability with a runसमय check.
 *
 * Beक्रमe the capability is detected, this वापसs false.
 */
अटल अंतरभूत bool cpus_have_cap(अचिन्हित पूर्णांक num)
अणु
	अगर (num >= ARM64_NCAPS)
		वापस false;
	वापस test_bit(num, cpu_hwcaps);
पूर्ण

/*
 * Test क्रम a capability without a runसमय check.
 *
 * Beक्रमe capabilities are finalized, this वापसs false.
 * After capabilities are finalized, this is patched to aव्योम a runसमय check.
 *
 * @num must be a compile-समय स्थिरant.
 */
अटल __always_अंतरभूत bool __cpus_have_स्थिर_cap(पूर्णांक num)
अणु
	अगर (num >= ARM64_NCAPS)
		वापस false;
	वापस अटल_branch_unlikely(&cpu_hwcap_keys[num]);
पूर्ण

/*
 * Test क्रम a capability without a runसमय check.
 *
 * Beक्रमe capabilities are finalized, this will BUG().
 * After capabilities are finalized, this is patched to aव्योम a runसमय check.
 *
 * @num must be a compile-समय स्थिरant.
 */
अटल __always_अंतरभूत bool cpus_have_final_cap(पूर्णांक num)
अणु
	अगर (प्रणाली_capabilities_finalized())
		वापस __cpus_have_स्थिर_cap(num);
	अन्यथा
		BUG();
पूर्ण

/*
 * Test क्रम a capability, possibly with a runसमय check क्रम non-hyp code.
 *
 * For hyp code, this behaves the same as cpus_have_final_cap().
 *
 * For non-hyp code:
 * Beक्रमe capabilities are finalized, this behaves as cpus_have_cap().
 * After capabilities are finalized, this is patched to aव्योम a runसमय check.
 *
 * @num must be a compile-समय स्थिरant.
 */
अटल __always_अंतरभूत bool cpus_have_स्थिर_cap(पूर्णांक num)
अणु
	अगर (is_hyp_code())
		वापस cpus_have_final_cap(num);
	अन्यथा अगर (प्रणाली_capabilities_finalized())
		वापस __cpus_have_स्थिर_cap(num);
	अन्यथा
		वापस cpus_have_cap(num);
पूर्ण

अटल अंतरभूत व्योम cpus_set_cap(अचिन्हित पूर्णांक num)
अणु
	अगर (num >= ARM64_NCAPS) अणु
		pr_warn("Attempt to set an illegal CPU capability (%d >= %d)\n",
			num, ARM64_NCAPS);
	पूर्ण अन्यथा अणु
		__set_bit(num, cpu_hwcaps);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक __attribute_स्थिर__
cpuid_feature_extract_चिन्हित_field_width(u64 features, पूर्णांक field, पूर्णांक width)
अणु
	वापस (s64)(features << (64 - width - field)) >> (64 - width);
पूर्ण

अटल अंतरभूत पूर्णांक __attribute_स्थिर__
cpuid_feature_extract_चिन्हित_field(u64 features, पूर्णांक field)
अणु
	वापस cpuid_feature_extract_चिन्हित_field_width(features, field, 4);
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__
cpuid_feature_extract_अचिन्हित_field_width(u64 features, पूर्णांक field, पूर्णांक width)
अणु
	वापस (u64)(features << (64 - width - field)) >> (64 - width);
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक __attribute_स्थिर__
cpuid_feature_extract_अचिन्हित_field(u64 features, पूर्णांक field)
अणु
	वापस cpuid_feature_extract_अचिन्हित_field_width(features, field, 4);
पूर्ण

/*
 * Fields that identअगरy the version of the Perक्रमmance Monitors Extension करो
 * not follow the standard ID scheme. See ARM DDI 0487E.a page D13-2825,
 * "Alternative ID scheme used for the Performance Monitors Extension version".
 */
अटल अंतरभूत u64 __attribute_स्थिर__
cpuid_feature_cap_perfmon_field(u64 features, पूर्णांक field, u64 cap)
अणु
	u64 val = cpuid_feature_extract_अचिन्हित_field(features, field);
	u64 mask = GENMASK_ULL(field + 3, field);

	/* Treat IMPLEMENTATION DEFINED functionality as unimplemented */
	अगर (val == 0xf)
		val = 0;

	अगर (val > cap) अणु
		features &= ~mask;
		features |= (cap << field) & mask;
	पूर्ण

	वापस features;
पूर्ण

अटल अंतरभूत u64 arm64_ftr_mask(स्थिर काष्ठा arm64_ftr_bits *ftrp)
अणु
	वापस (u64)GENMASK(ftrp->shअगरt + ftrp->width - 1, ftrp->shअगरt);
पूर्ण

अटल अंतरभूत u64 arm64_ftr_reg_user_value(स्थिर काष्ठा arm64_ftr_reg *reg)
अणु
	वापस (reg->user_val | (reg->sys_val & reg->user_mask));
पूर्ण

अटल अंतरभूत पूर्णांक __attribute_स्थिर__
cpuid_feature_extract_field_width(u64 features, पूर्णांक field, पूर्णांक width, bool sign)
अणु
	वापस (sign) ?
		cpuid_feature_extract_चिन्हित_field_width(features, field, width) :
		cpuid_feature_extract_अचिन्हित_field_width(features, field, width);
पूर्ण

अटल अंतरभूत पूर्णांक __attribute_स्थिर__
cpuid_feature_extract_field(u64 features, पूर्णांक field, bool sign)
अणु
	वापस cpuid_feature_extract_field_width(features, field, 4, sign);
पूर्ण

अटल अंतरभूत s64 arm64_ftr_value(स्थिर काष्ठा arm64_ftr_bits *ftrp, u64 val)
अणु
	वापस (s64)cpuid_feature_extract_field_width(val, ftrp->shअगरt, ftrp->width, ftrp->sign);
पूर्ण

अटल अंतरभूत bool id_aa64mmfr0_mixed_endian_el0(u64 mmfr0)
अणु
	वापस cpuid_feature_extract_अचिन्हित_field(mmfr0, ID_AA64MMFR0_BIGENDEL_SHIFT) == 0x1 ||
		cpuid_feature_extract_अचिन्हित_field(mmfr0, ID_AA64MMFR0_BIGENDEL0_SHIFT) == 0x1;
पूर्ण

अटल अंतरभूत bool id_aa64pfr0_32bit_el1(u64 pfr0)
अणु
	u32 val = cpuid_feature_extract_अचिन्हित_field(pfr0, ID_AA64PFR0_EL1_SHIFT);

	वापस val == ID_AA64PFR0_EL1_32BIT_64BIT;
पूर्ण

अटल अंतरभूत bool id_aa64pfr0_32bit_el0(u64 pfr0)
अणु
	u32 val = cpuid_feature_extract_अचिन्हित_field(pfr0, ID_AA64PFR0_EL0_SHIFT);

	वापस val == ID_AA64PFR0_EL0_32BIT_64BIT;
पूर्ण

अटल अंतरभूत bool id_aa64pfr0_sve(u64 pfr0)
अणु
	u32 val = cpuid_feature_extract_अचिन्हित_field(pfr0, ID_AA64PFR0_SVE_SHIFT);

	वापस val > 0;
पूर्ण

व्योम __init setup_cpu_features(व्योम);
व्योम check_local_cpu_capabilities(व्योम);

u64 पढ़ो_sanitised_ftr_reg(u32 id);
u64 __पढ़ो_sysreg_by_encoding(u32 sys_id);

अटल अंतरभूत bool cpu_supports_mixed_endian_el0(व्योम)
अणु
	वापस id_aa64mmfr0_mixed_endian_el0(पढ़ो_cpuid(ID_AA64MMFR0_EL1));
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_32bit_el0(व्योम)
अणु
	वापस cpus_have_स्थिर_cap(ARM64_HAS_32BIT_EL0);
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_4kb_granule(व्योम)
अणु
	u64 mmfr0;
	u32 val;

	mmfr0 =	पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	val = cpuid_feature_extract_अचिन्हित_field(mmfr0,
						ID_AA64MMFR0_TGRAN4_SHIFT);

	वापस val == ID_AA64MMFR0_TGRAN4_SUPPORTED;
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_64kb_granule(व्योम)
अणु
	u64 mmfr0;
	u32 val;

	mmfr0 =	पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	val = cpuid_feature_extract_अचिन्हित_field(mmfr0,
						ID_AA64MMFR0_TGRAN64_SHIFT);

	वापस val == ID_AA64MMFR0_TGRAN64_SUPPORTED;
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_16kb_granule(व्योम)
अणु
	u64 mmfr0;
	u32 val;

	mmfr0 =	पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	val = cpuid_feature_extract_अचिन्हित_field(mmfr0,
						ID_AA64MMFR0_TGRAN16_SHIFT);

	वापस val == ID_AA64MMFR0_TGRAN16_SUPPORTED;
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_mixed_endian_el0(व्योम)
अणु
	वापस id_aa64mmfr0_mixed_endian_el0(पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1));
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_mixed_endian(व्योम)
अणु
	u64 mmfr0;
	u32 val;

	mmfr0 =	पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	val = cpuid_feature_extract_अचिन्हित_field(mmfr0,
						ID_AA64MMFR0_BIGENDEL_SHIFT);

	वापस val == 0x1;
पूर्ण

अटल __always_अंतरभूत bool प्रणाली_supports_fpsimd(व्योम)
अणु
	वापस !cpus_have_स्थिर_cap(ARM64_HAS_NO_FPSIMD);
पूर्ण

अटल अंतरभूत bool प्रणाली_uses_hw_pan(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_PAN) &&
		cpus_have_स्थिर_cap(ARM64_HAS_PAN);
पूर्ण

अटल अंतरभूत bool प्रणाली_uses_ttbr0_pan(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_SW_TTBR0_PAN) &&
		!प्रणाली_uses_hw_pan();
पूर्ण

अटल __always_अंतरभूत bool प्रणाली_supports_sve(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_SVE) &&
		cpus_have_स्थिर_cap(ARM64_SVE);
पूर्ण

अटल __always_अंतरभूत bool प्रणाली_supports_cnp(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_CNP) &&
		cpus_have_स्थिर_cap(ARM64_HAS_CNP);
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_address_auth(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_PTR_AUTH) &&
		cpus_have_स्थिर_cap(ARM64_HAS_ADDRESS_AUTH);
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_generic_auth(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_PTR_AUTH) &&
		cpus_have_स्थिर_cap(ARM64_HAS_GENERIC_AUTH);
पूर्ण

अटल अंतरभूत bool प्रणाली_has_full_ptr_auth(व्योम)
अणु
	वापस प्रणाली_supports_address_auth() && प्रणाली_supports_generic_auth();
पूर्ण

अटल __always_अंतरभूत bool प्रणाली_uses_irq_prio_masking(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_PSEUDO_NMI) &&
	       cpus_have_स्थिर_cap(ARM64_HAS_IRQ_PRIO_MASKING);
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_mte(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_MTE) &&
		cpus_have_स्थिर_cap(ARM64_MTE);
पूर्ण

अटल अंतरभूत bool प्रणाली_has_prio_mask_debugging(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_DEBUG_PRIORITY_MASKING) &&
	       प्रणाली_uses_irq_prio_masking();
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_bti(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_BTI) && cpus_have_स्थिर_cap(ARM64_BTI);
पूर्ण

अटल अंतरभूत bool प्रणाली_supports_tlb_range(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_TLB_RANGE) &&
		cpus_have_स्थिर_cap(ARM64_HAS_TLB_RANGE);
पूर्ण

बाह्य पूर्णांक करो_emulate_mrs(काष्ठा pt_regs *regs, u32 sys_reg, u32 rt);

अटल अंतरभूत u32 id_aa64mmfr0_parange_to_phys_shअगरt(पूर्णांक parange)
अणु
	चयन (parange) अणु
	हाल 0: वापस 32;
	हाल 1: वापस 36;
	हाल 2: वापस 40;
	हाल 3: वापस 42;
	हाल 4: वापस 44;
	हाल 5: वापस 48;
	हाल 6: वापस 52;
	/*
	 * A future PE could use a value unknown to the kernel.
	 * However, by the "D10.1.4 Principles of the ID scheme
	 * क्रम fields in ID रेजिस्टरs", ARM DDI 0487C.a, any new
	 * value is guaranteed to be higher than what we know alपढ़ोy.
	 * As a safe limit, we वापस the limit supported by the kernel.
	 */
	शेष: वापस CONFIG_ARM64_PA_BITS;
	पूर्ण
पूर्ण

/* Check whether hardware update of the Access flag is supported */
अटल अंतरभूत bool cpu_has_hw_af(व्योम)
अणु
	u64 mmfr1;

	अगर (!IS_ENABLED(CONFIG_ARM64_HW_AFDBM))
		वापस false;

	mmfr1 = पढ़ो_cpuid(ID_AA64MMFR1_EL1);
	वापस cpuid_feature_extract_अचिन्हित_field(mmfr1,
						ID_AA64MMFR1_HADBS_SHIFT);
पूर्ण

अटल अंतरभूत bool cpu_has_pan(व्योम)
अणु
	u64 mmfr1 = पढ़ो_cpuid(ID_AA64MMFR1_EL1);
	वापस cpuid_feature_extract_अचिन्हित_field(mmfr1,
						    ID_AA64MMFR1_PAN_SHIFT);
पूर्ण

#अगर_घोषित CONFIG_ARM64_AMU_EXTN
/* Check whether the cpu supports the Activity Monitors Unit (AMU) */
बाह्य bool cpu_has_amu_feat(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत bool cpu_has_amu_feat(पूर्णांक cpu)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/* Get a cpu that supports the Activity Monitors Unit (AMU) */
बाह्य पूर्णांक get_cpu_with_amu_feat(व्योम);

अटल अंतरभूत अचिन्हित पूर्णांक get_vmid_bits(u64 mmfr1)
अणु
	पूर्णांक vmid_bits;

	vmid_bits = cpuid_feature_extract_अचिन्हित_field(mmfr1,
						ID_AA64MMFR1_VMIDBITS_SHIFT);
	अगर (vmid_bits == ID_AA64MMFR1_VMIDBITS_16)
		वापस 16;

	/*
	 * Return the शेष here even अगर any reserved
	 * value is fetched from the प्रणाली रेजिस्टर.
	 */
	वापस 8;
पूर्ण

बाह्य काष्ठा arm64_ftr_override id_aa64mmfr1_override;
बाह्य काष्ठा arm64_ftr_override id_aa64pfr1_override;
बाह्य काष्ठा arm64_ftr_override id_aa64isar1_override;

u32 get_kvm_ipa_limit(व्योम);
व्योम dump_cpu_features(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1994  Linus Torvalds
 *
 *  Cyrix stuff, June 1998 by:
 *	- Rafael R. Reilova (moved everything from head.S),
 *        <rreilova@ececs.uc.edu>
 *	- Channing Corn (tests & fixes),
 *	- Andrew D. Balsa (code cleanup).
 */
#समावेश <linux/init.h>
#समावेश <linux/utsname.h>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/nospec.h>
#समावेश <linux/prctl.h>
#समावेश <linux/sched/smt.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/spec-ctrl.h>
#समावेश <यंत्र/cmdline.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/processor-flags.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/vmx.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "cpu.h"

अटल व्योम __init spectre_v1_select_mitigation(व्योम);
अटल व्योम __init spectre_v2_select_mitigation(व्योम);
अटल व्योम __init ssb_select_mitigation(व्योम);
अटल व्योम __init l1tf_select_mitigation(व्योम);
अटल व्योम __init mds_select_mitigation(व्योम);
अटल व्योम __init mds_prपूर्णांक_mitigation(व्योम);
अटल व्योम __init taa_select_mitigation(व्योम);
अटल व्योम __init srbds_select_mitigation(व्योम);

/* The base value of the SPEC_CTRL MSR that always has to be preserved. */
u64 x86_spec_ctrl_base;
EXPORT_SYMBOL_GPL(x86_spec_ctrl_base);
अटल DEFINE_MUTEX(spec_ctrl_mutex);

/*
 * The venकरोr and possibly platक्रमm specअगरic bits which can be modअगरied in
 * x86_spec_ctrl_base.
 */
अटल u64 __ro_after_init x86_spec_ctrl_mask = SPEC_CTRL_IBRS;

/*
 * AMD specअगरic MSR info क्रम Speculative Store Bypass control.
 * x86_amd_ls_cfg_ssbd_mask is initialized in identअगरy_boot_cpu().
 */
u64 __ro_after_init x86_amd_ls_cfg_base;
u64 __ro_after_init x86_amd_ls_cfg_ssbd_mask;

/* Control conditional STIBP in चयन_to() */
DEFINE_STATIC_KEY_FALSE(चयन_to_cond_stibp);
/* Control conditional IBPB in चयन_mm() */
DEFINE_STATIC_KEY_FALSE(चयन_mm_cond_ibpb);
/* Control unconditional IBPB in चयन_mm() */
DEFINE_STATIC_KEY_FALSE(चयन_mm_always_ibpb);

/* Control MDS CPU buffer clear beक्रमe वापसing to user space */
DEFINE_STATIC_KEY_FALSE(mds_user_clear);
EXPORT_SYMBOL_GPL(mds_user_clear);
/* Control MDS CPU buffer clear beक्रमe idling (halt, mरुको) */
DEFINE_STATIC_KEY_FALSE(mds_idle_clear);
EXPORT_SYMBOL_GPL(mds_idle_clear);

व्योम __init check_bugs(व्योम)
अणु
	identअगरy_boot_cpu();

	/*
	 * identअगरy_boot_cpu() initialized SMT support inक्रमmation, let the
	 * core code know.
	 */
	cpu_smt_check_topology();

	अगर (!IS_ENABLED(CONFIG_SMP)) अणु
		pr_info("CPU: ");
		prपूर्णांक_cpu_info(&boot_cpu_data);
	पूर्ण

	/*
	 * Read the SPEC_CTRL MSR to account क्रम reserved bits which may
	 * have unknown values. AMD64_LS_CFG MSR is cached in the early AMD
	 * init code as it is not क्रमागतerated and depends on the family.
	 */
	अगर (boot_cpu_has(X86_FEATURE_MSR_SPEC_CTRL))
		rdmsrl(MSR_IA32_SPEC_CTRL, x86_spec_ctrl_base);

	/* Allow STIBP in MSR_SPEC_CTRL अगर supported */
	अगर (boot_cpu_has(X86_FEATURE_STIBP))
		x86_spec_ctrl_mask |= SPEC_CTRL_STIBP;

	/* Select the proper CPU mitigations beक्रमe patching alternatives: */
	spectre_v1_select_mitigation();
	spectre_v2_select_mitigation();
	ssb_select_mitigation();
	l1tf_select_mitigation();
	mds_select_mitigation();
	taa_select_mitigation();
	srbds_select_mitigation();

	/*
	 * As MDS and TAA mitigations are पूर्णांकer-related, prपूर्णांक MDS
	 * mitigation until after TAA mitigation selection is करोne.
	 */
	mds_prपूर्णांक_mitigation();

	arch_smt_update();

#अगर_घोषित CONFIG_X86_32
	/*
	 * Check whether we are able to run this kernel safely on SMP.
	 *
	 * - i386 is no दीर्घer supported.
	 * - In order to run on anything without a TSC, we need to be
	 *   compiled क्रम a i486.
	 */
	अगर (boot_cpu_data.x86 < 4)
		panic("Kernel requires i486+ for 'invlpg' and other features");

	init_utsname()->machine[1] =
		'0' + (boot_cpu_data.x86 > 6 ? 6 : boot_cpu_data.x86);
	alternative_inकाष्ठाions();

	fpu__init_check_bugs();
#अन्यथा /* CONFIG_X86_64 */
	alternative_inकाष्ठाions();

	/*
	 * Make sure the first 2MB area is not mapped by huge pages
	 * There are typically fixed size MTRRs in there and overlapping
	 * MTRRs पूर्णांकo large pages causes slow करोwns.
	 *
	 * Right now we करोn't करो that with gbpages because there seems
	 * very little benefit क्रम that हाल.
	 */
	अगर (!direct_gbpages)
		set_memory_4k((अचिन्हित दीर्घ)__va(0), 1);
#पूर्ण_अगर
पूर्ण

व्योम
x86_virt_spec_ctrl(u64 guest_spec_ctrl, u64 guest_virt_spec_ctrl, bool setguest)
अणु
	u64 msrval, guestval, hostval = x86_spec_ctrl_base;
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();

	/* Is MSR_SPEC_CTRL implemented ? */
	अगर (अटल_cpu_has(X86_FEATURE_MSR_SPEC_CTRL)) अणु
		/*
		 * Restrict guest_spec_ctrl to supported values. Clear the
		 * modअगरiable bits in the host base value and or the
		 * modअगरiable bits from the guest value.
		 */
		guestval = hostval & ~x86_spec_ctrl_mask;
		guestval |= guest_spec_ctrl & x86_spec_ctrl_mask;

		/* SSBD controlled in MSR_SPEC_CTRL */
		अगर (अटल_cpu_has(X86_FEATURE_SPEC_CTRL_SSBD) ||
		    अटल_cpu_has(X86_FEATURE_AMD_SSBD))
			hostval |= ssbd_tअगर_to_spec_ctrl(ti->flags);

		/* Conditional STIBP enabled? */
		अगर (अटल_branch_unlikely(&चयन_to_cond_stibp))
			hostval |= stibp_tअगर_to_spec_ctrl(ti->flags);

		अगर (hostval != guestval) अणु
			msrval = setguest ? guestval : hostval;
			wrmsrl(MSR_IA32_SPEC_CTRL, msrval);
		पूर्ण
	पूर्ण

	/*
	 * If SSBD is not handled in MSR_SPEC_CTRL on AMD, update
	 * MSR_AMD64_L2_CFG or MSR_VIRT_SPEC_CTRL अगर supported.
	 */
	अगर (!अटल_cpu_has(X86_FEATURE_LS_CFG_SSBD) &&
	    !अटल_cpu_has(X86_FEATURE_VIRT_SSBD))
		वापस;

	/*
	 * If the host has SSBD mitigation enabled, क्रमce it in the host's
	 * भव MSR value. If its not permanently enabled, evaluate
	 * current's TIF_SSBD thपढ़ो flag.
	 */
	अगर (अटल_cpu_has(X86_FEATURE_SPEC_STORE_BYPASS_DISABLE))
		hostval = SPEC_CTRL_SSBD;
	अन्यथा
		hostval = ssbd_tअगर_to_spec_ctrl(ti->flags);

	/* Sanitize the guest value */
	guestval = guest_virt_spec_ctrl & SPEC_CTRL_SSBD;

	अगर (hostval != guestval) अणु
		अचिन्हित दीर्घ tअगर;

		tअगर = setguest ? ssbd_spec_ctrl_to_tअगर(guestval) :
				 ssbd_spec_ctrl_to_tअगर(hostval);

		speculation_ctrl_update(tअगर);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(x86_virt_spec_ctrl);

अटल व्योम x86_amd_ssb_disable(व्योम)
अणु
	u64 msrval = x86_amd_ls_cfg_base | x86_amd_ls_cfg_ssbd_mask;

	अगर (boot_cpu_has(X86_FEATURE_VIRT_SSBD))
		wrmsrl(MSR_AMD64_VIRT_SPEC_CTRL, SPEC_CTRL_SSBD);
	अन्यथा अगर (boot_cpu_has(X86_FEATURE_LS_CFG_SSBD))
		wrmsrl(MSR_AMD64_LS_CFG, msrval);
पूर्ण

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"MDS: " fmt

/* Default mitigation क्रम MDS-affected CPUs */
अटल क्रमागत mds_mitigations mds_mitigation __ro_after_init = MDS_MITIGATION_FULL;
अटल bool mds_nosmt __ro_after_init = false;

अटल स्थिर अक्षर * स्थिर mds_strings[] = अणु
	[MDS_MITIGATION_OFF]	= "Vulnerable",
	[MDS_MITIGATION_FULL]	= "Mitigation: Clear CPU buffers",
	[MDS_MITIGATION_VMWERV]	= "Vulnerable: Clear CPU buffers attempted, no microcode",
पूर्ण;

अटल व्योम __init mds_select_mitigation(व्योम)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_MDS) || cpu_mitigations_off()) अणु
		mds_mitigation = MDS_MITIGATION_OFF;
		वापस;
	पूर्ण

	अगर (mds_mitigation == MDS_MITIGATION_FULL) अणु
		अगर (!boot_cpu_has(X86_FEATURE_MD_CLEAR))
			mds_mitigation = MDS_MITIGATION_VMWERV;

		अटल_branch_enable(&mds_user_clear);

		अगर (!boot_cpu_has(X86_BUG_MSBDS_ONLY) &&
		    (mds_nosmt || cpu_mitigations_स्वतः_nosmt()))
			cpu_smt_disable(false);
	पूर्ण
पूर्ण

अटल व्योम __init mds_prपूर्णांक_mitigation(व्योम)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_MDS) || cpu_mitigations_off())
		वापस;

	pr_info("%s\n", mds_strings[mds_mitigation]);
पूर्ण

अटल पूर्णांक __init mds_cmdline(अक्षर *str)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_MDS))
		वापस 0;

	अगर (!str)
		वापस -EINVAL;

	अगर (!म_भेद(str, "off"))
		mds_mitigation = MDS_MITIGATION_OFF;
	अन्यथा अगर (!म_भेद(str, "full"))
		mds_mitigation = MDS_MITIGATION_FULL;
	अन्यथा अगर (!म_भेद(str, "full,nosmt")) अणु
		mds_mitigation = MDS_MITIGATION_FULL;
		mds_nosmt = true;
	पूर्ण

	वापस 0;
पूर्ण
early_param("mds", mds_cmdline);

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"TAA: " fmt

क्रमागत taa_mitigations अणु
	TAA_MITIGATION_OFF,
	TAA_MITIGATION_UCODE_NEEDED,
	TAA_MITIGATION_VERW,
	TAA_MITIGATION_TSX_DISABLED,
पूर्ण;

/* Default mitigation क्रम TAA-affected CPUs */
अटल क्रमागत taa_mitigations taa_mitigation __ro_after_init = TAA_MITIGATION_VERW;
अटल bool taa_nosmt __ro_after_init;

अटल स्थिर अक्षर * स्थिर taa_strings[] = अणु
	[TAA_MITIGATION_OFF]		= "Vulnerable",
	[TAA_MITIGATION_UCODE_NEEDED]	= "Vulnerable: Clear CPU buffers attempted, no microcode",
	[TAA_MITIGATION_VERW]		= "Mitigation: Clear CPU buffers",
	[TAA_MITIGATION_TSX_DISABLED]	= "Mitigation: TSX disabled",
पूर्ण;

अटल व्योम __init taa_select_mitigation(व्योम)
अणु
	u64 ia32_cap;

	अगर (!boot_cpu_has_bug(X86_BUG_TAA)) अणु
		taa_mitigation = TAA_MITIGATION_OFF;
		वापस;
	पूर्ण

	/* TSX previously disabled by tsx=off */
	अगर (!boot_cpu_has(X86_FEATURE_RTM)) अणु
		taa_mitigation = TAA_MITIGATION_TSX_DISABLED;
		जाओ out;
	पूर्ण

	अगर (cpu_mitigations_off()) अणु
		taa_mitigation = TAA_MITIGATION_OFF;
		वापस;
	पूर्ण

	/*
	 * TAA mitigation via VERW is turned off अगर both
	 * tsx_async_पात=off and mds=off are specअगरied.
	 */
	अगर (taa_mitigation == TAA_MITIGATION_OFF &&
	    mds_mitigation == MDS_MITIGATION_OFF)
		जाओ out;

	अगर (boot_cpu_has(X86_FEATURE_MD_CLEAR))
		taa_mitigation = TAA_MITIGATION_VERW;
	अन्यथा
		taa_mitigation = TAA_MITIGATION_UCODE_NEEDED;

	/*
	 * VERW करोesn't clear the CPU buffers when MD_CLEAR=1 and MDS_NO=1.
	 * A microcode update fixes this behavior to clear CPU buffers. It also
	 * adds support क्रम MSR_IA32_TSX_CTRL which is क्रमागतerated by the
	 * ARCH_CAP_TSX_CTRL_MSR bit.
	 *
	 * On MDS_NO=1 CPUs अगर ARCH_CAP_TSX_CTRL_MSR is not set, microcode
	 * update is required.
	 */
	ia32_cap = x86_पढ़ो_arch_cap_msr();
	अगर ( (ia32_cap & ARCH_CAP_MDS_NO) &&
	    !(ia32_cap & ARCH_CAP_TSX_CTRL_MSR))
		taa_mitigation = TAA_MITIGATION_UCODE_NEEDED;

	/*
	 * TSX is enabled, select alternate mitigation क्रम TAA which is
	 * the same as MDS. Enable MDS अटल branch to clear CPU buffers.
	 *
	 * For guests that can't determine whether the correct microcode is
	 * present on host, enable the mitigation क्रम UCODE_NEEDED as well.
	 */
	अटल_branch_enable(&mds_user_clear);

	अगर (taa_nosmt || cpu_mitigations_स्वतः_nosmt())
		cpu_smt_disable(false);

	/*
	 * Update MDS mitigation, अगर necessary, as the mds_user_clear is
	 * now enabled क्रम TAA mitigation.
	 */
	अगर (mds_mitigation == MDS_MITIGATION_OFF &&
	    boot_cpu_has_bug(X86_BUG_MDS)) अणु
		mds_mitigation = MDS_MITIGATION_FULL;
		mds_select_mitigation();
	पूर्ण
out:
	pr_info("%s\n", taa_strings[taa_mitigation]);
पूर्ण

अटल पूर्णांक __init tsx_async_पात_parse_cmdline(अक्षर *str)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_TAA))
		वापस 0;

	अगर (!str)
		वापस -EINVAL;

	अगर (!म_भेद(str, "off")) अणु
		taa_mitigation = TAA_MITIGATION_OFF;
	पूर्ण अन्यथा अगर (!म_भेद(str, "full")) अणु
		taa_mitigation = TAA_MITIGATION_VERW;
	पूर्ण अन्यथा अगर (!म_भेद(str, "full,nosmt")) अणु
		taa_mitigation = TAA_MITIGATION_VERW;
		taa_nosmt = true;
	पूर्ण

	वापस 0;
पूर्ण
early_param("tsx_async_abort", tsx_async_पात_parse_cmdline);

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"SRBDS: " fmt

क्रमागत srbds_mitigations अणु
	SRBDS_MITIGATION_OFF,
	SRBDS_MITIGATION_UCODE_NEEDED,
	SRBDS_MITIGATION_FULL,
	SRBDS_MITIGATION_TSX_OFF,
	SRBDS_MITIGATION_HYPERVISOR,
पूर्ण;

अटल क्रमागत srbds_mitigations srbds_mitigation __ro_after_init = SRBDS_MITIGATION_FULL;

अटल स्थिर अक्षर * स्थिर srbds_strings[] = अणु
	[SRBDS_MITIGATION_OFF]		= "Vulnerable",
	[SRBDS_MITIGATION_UCODE_NEEDED]	= "Vulnerable: No microcode",
	[SRBDS_MITIGATION_FULL]		= "Mitigation: Microcode",
	[SRBDS_MITIGATION_TSX_OFF]	= "Mitigation: TSX disabled",
	[SRBDS_MITIGATION_HYPERVISOR]	= "Unknown: Dependent on hypervisor status",
पूर्ण;

अटल bool srbds_off;

व्योम update_srbds_msr(व्योम)
अणु
	u64 mcu_ctrl;

	अगर (!boot_cpu_has_bug(X86_BUG_SRBDS))
		वापस;

	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस;

	अगर (srbds_mitigation == SRBDS_MITIGATION_UCODE_NEEDED)
		वापस;

	rdmsrl(MSR_IA32_MCU_OPT_CTRL, mcu_ctrl);

	चयन (srbds_mitigation) अणु
	हाल SRBDS_MITIGATION_OFF:
	हाल SRBDS_MITIGATION_TSX_OFF:
		mcu_ctrl |= RNGDS_MITG_DIS;
		अवरोध;
	हाल SRBDS_MITIGATION_FULL:
		mcu_ctrl &= ~RNGDS_MITG_DIS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	wrmsrl(MSR_IA32_MCU_OPT_CTRL, mcu_ctrl);
पूर्ण

अटल व्योम __init srbds_select_mitigation(व्योम)
अणु
	u64 ia32_cap;

	अगर (!boot_cpu_has_bug(X86_BUG_SRBDS))
		वापस;

	/*
	 * Check to see अगर this is one of the MDS_NO प्रणालीs supporting
	 * TSX that are only exposed to SRBDS when TSX is enabled.
	 */
	ia32_cap = x86_पढ़ो_arch_cap_msr();
	अगर ((ia32_cap & ARCH_CAP_MDS_NO) && !boot_cpu_has(X86_FEATURE_RTM))
		srbds_mitigation = SRBDS_MITIGATION_TSX_OFF;
	अन्यथा अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		srbds_mitigation = SRBDS_MITIGATION_HYPERVISOR;
	अन्यथा अगर (!boot_cpu_has(X86_FEATURE_SRBDS_CTRL))
		srbds_mitigation = SRBDS_MITIGATION_UCODE_NEEDED;
	अन्यथा अगर (cpu_mitigations_off() || srbds_off)
		srbds_mitigation = SRBDS_MITIGATION_OFF;

	update_srbds_msr();
	pr_info("%s\n", srbds_strings[srbds_mitigation]);
पूर्ण

अटल पूर्णांक __init srbds_parse_cmdline(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	अगर (!boot_cpu_has_bug(X86_BUG_SRBDS))
		वापस 0;

	srbds_off = !म_भेद(str, "off");
	वापस 0;
पूर्ण
early_param("srbds", srbds_parse_cmdline);

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)     "Spectre V1 : " fmt

क्रमागत spectre_v1_mitigation अणु
	SPECTRE_V1_MITIGATION_NONE,
	SPECTRE_V1_MITIGATION_AUTO,
पूर्ण;

अटल क्रमागत spectre_v1_mitigation spectre_v1_mitigation __ro_after_init =
	SPECTRE_V1_MITIGATION_AUTO;

अटल स्थिर अक्षर * स्थिर spectre_v1_strings[] = अणु
	[SPECTRE_V1_MITIGATION_NONE] = "Vulnerable: __user pointer sanitization and usercopy barriers only; no swapgs barriers",
	[SPECTRE_V1_MITIGATION_AUTO] = "Mitigation: usercopy/swapgs barriers and __user pointer sanitization",
पूर्ण;

/*
 * Does SMAP provide full mitigation against speculative kernel access to
 * userspace?
 */
अटल bool smap_works_speculatively(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_SMAP))
		वापस false;

	/*
	 * On CPUs which are vulnerable to Meltकरोwn, SMAP करोes not
	 * prevent speculative access to user data in the L1 cache.
	 * Consider SMAP to be non-functional as a mitigation on these
	 * CPUs.
	 */
	अगर (boot_cpu_has(X86_BUG_CPU_MELTDOWN))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम __init spectre_v1_select_mitigation(व्योम)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_SPECTRE_V1) || cpu_mitigations_off()) अणु
		spectre_v1_mitigation = SPECTRE_V1_MITIGATION_NONE;
		वापस;
	पूर्ण

	अगर (spectre_v1_mitigation == SPECTRE_V1_MITIGATION_AUTO) अणु
		/*
		 * With Spectre v1, a user can speculatively control either
		 * path of a conditional swapgs with a user-controlled GS
		 * value.  The mitigation is to add lfences to both code paths.
		 *
		 * If FSGSBASE is enabled, the user can put a kernel address in
		 * GS, in which हाल SMAP provides no protection.
		 *
		 * If FSGSBASE is disabled, the user can only put a user space
		 * address in GS.  That makes an attack harder, but still
		 * possible अगर there's no SMAP protection.
		 */
		अगर (boot_cpu_has(X86_FEATURE_FSGSBASE) ||
		    !smap_works_speculatively()) अणु
			/*
			 * Mitigation can be provided from SWAPGS itself or
			 * PTI as the CR3 ग_लिखो in the Meltकरोwn mitigation
			 * is serializing.
			 *
			 * If neither is there, mitigate with an LFENCE to
			 * stop speculation through swapgs.
			 */
			अगर (boot_cpu_has_bug(X86_BUG_SWAPGS) &&
			    !boot_cpu_has(X86_FEATURE_PTI))
				setup_क्रमce_cpu_cap(X86_FEATURE_FENCE_SWAPGS_USER);

			/*
			 * Enable lfences in the kernel entry (non-swapgs)
			 * paths, to prevent user entry from speculatively
			 * skipping swapgs.
			 */
			setup_क्रमce_cpu_cap(X86_FEATURE_FENCE_SWAPGS_KERNEL);
		पूर्ण
	पूर्ण

	pr_info("%s\n", spectre_v1_strings[spectre_v1_mitigation]);
पूर्ण

अटल पूर्णांक __init nospectre_v1_cmdline(अक्षर *str)
अणु
	spectre_v1_mitigation = SPECTRE_V1_MITIGATION_NONE;
	वापस 0;
पूर्ण
early_param("nospectre_v1", nospectre_v1_cmdline);

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)     "Spectre V2 : " fmt

अटल क्रमागत spectre_v2_mitigation spectre_v2_enabled __ro_after_init =
	SPECTRE_V2_NONE;

अटल क्रमागत spectre_v2_user_mitigation spectre_v2_user_stibp __ro_after_init =
	SPECTRE_V2_USER_NONE;
अटल क्रमागत spectre_v2_user_mitigation spectre_v2_user_ibpb __ro_after_init =
	SPECTRE_V2_USER_NONE;

#अगर_घोषित CONFIG_RETPOLINE
अटल bool spectre_v2_bad_module;

bool retpoline_module_ok(bool has_retpoline)
अणु
	अगर (spectre_v2_enabled == SPECTRE_V2_NONE || has_retpoline)
		वापस true;

	pr_err("System may be vulnerable to spectre v2\n");
	spectre_v2_bad_module = true;
	वापस false;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *spectre_v2_module_string(व्योम)
अणु
	वापस spectre_v2_bad_module ? " - vulnerable module loaded" : "";
पूर्ण
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *spectre_v2_module_string(व्योम) अणु वापस ""; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool match_option(स्थिर अक्षर *arg, पूर्णांक arglen, स्थिर अक्षर *opt)
अणु
	पूर्णांक len = म_माप(opt);

	वापस len == arglen && !म_भेदन(arg, opt, len);
पूर्ण

/* The kernel command line selection क्रम spectre v2 */
क्रमागत spectre_v2_mitigation_cmd अणु
	SPECTRE_V2_CMD_NONE,
	SPECTRE_V2_CMD_AUTO,
	SPECTRE_V2_CMD_FORCE,
	SPECTRE_V2_CMD_RETPOLINE,
	SPECTRE_V2_CMD_RETPOLINE_GENERIC,
	SPECTRE_V2_CMD_RETPOLINE_AMD,
पूर्ण;

क्रमागत spectre_v2_user_cmd अणु
	SPECTRE_V2_USER_CMD_NONE,
	SPECTRE_V2_USER_CMD_AUTO,
	SPECTRE_V2_USER_CMD_FORCE,
	SPECTRE_V2_USER_CMD_PRCTL,
	SPECTRE_V2_USER_CMD_PRCTL_IBPB,
	SPECTRE_V2_USER_CMD_SECCOMP,
	SPECTRE_V2_USER_CMD_SECCOMP_IBPB,
पूर्ण;

अटल स्थिर अक्षर * स्थिर spectre_v2_user_strings[] = अणु
	[SPECTRE_V2_USER_NONE]			= "User space: Vulnerable",
	[SPECTRE_V2_USER_STRICT]		= "User space: Mitigation: STIBP protection",
	[SPECTRE_V2_USER_STRICT_PREFERRED]	= "User space: Mitigation: STIBP always-on protection",
	[SPECTRE_V2_USER_PRCTL]			= "User space: Mitigation: STIBP via prctl",
	[SPECTRE_V2_USER_SECCOMP]		= "User space: Mitigation: STIBP via seccomp and prctl",
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर			*option;
	क्रमागत spectre_v2_user_cmd	cmd;
	bool				secure;
पूर्ण v2_user_options[] __initस्थिर = अणु
	अणु "auto",		SPECTRE_V2_USER_CMD_AUTO,		false पूर्ण,
	अणु "off",		SPECTRE_V2_USER_CMD_NONE,		false पूर्ण,
	अणु "on",			SPECTRE_V2_USER_CMD_FORCE,		true  पूर्ण,
	अणु "prctl",		SPECTRE_V2_USER_CMD_PRCTL,		false पूर्ण,
	अणु "prctl,ibpb",		SPECTRE_V2_USER_CMD_PRCTL_IBPB,		false पूर्ण,
	अणु "seccomp",		SPECTRE_V2_USER_CMD_SECCOMP,		false पूर्ण,
	अणु "seccomp,ibpb",	SPECTRE_V2_USER_CMD_SECCOMP_IBPB,	false पूर्ण,
पूर्ण;

अटल व्योम __init spec_v2_user_prपूर्णांक_cond(स्थिर अक्षर *reason, bool secure)
अणु
	अगर (boot_cpu_has_bug(X86_BUG_SPECTRE_V2) != secure)
		pr_info("spectre_v2_user=%s forced on command line.\n", reason);
पूर्ण

अटल क्रमागत spectre_v2_user_cmd __init
spectre_v2_parse_user_cmdline(क्रमागत spectre_v2_mitigation_cmd v2_cmd)
अणु
	अक्षर arg[20];
	पूर्णांक ret, i;

	चयन (v2_cmd) अणु
	हाल SPECTRE_V2_CMD_NONE:
		वापस SPECTRE_V2_USER_CMD_NONE;
	हाल SPECTRE_V2_CMD_FORCE:
		वापस SPECTRE_V2_USER_CMD_FORCE;
	शेष:
		अवरोध;
	पूर्ण

	ret = cmdline_find_option(boot_command_line, "spectre_v2_user",
				  arg, माप(arg));
	अगर (ret < 0)
		वापस SPECTRE_V2_USER_CMD_AUTO;

	क्रम (i = 0; i < ARRAY_SIZE(v2_user_options); i++) अणु
		अगर (match_option(arg, ret, v2_user_options[i].option)) अणु
			spec_v2_user_prपूर्णांक_cond(v2_user_options[i].option,
						v2_user_options[i].secure);
			वापस v2_user_options[i].cmd;
		पूर्ण
	पूर्ण

	pr_err("Unknown user space protection option (%s). Switching to AUTO select\n", arg);
	वापस SPECTRE_V2_USER_CMD_AUTO;
पूर्ण

अटल व्योम __init
spectre_v2_user_select_mitigation(क्रमागत spectre_v2_mitigation_cmd v2_cmd)
अणु
	क्रमागत spectre_v2_user_mitigation mode = SPECTRE_V2_USER_NONE;
	bool smt_possible = IS_ENABLED(CONFIG_SMP);
	क्रमागत spectre_v2_user_cmd cmd;

	अगर (!boot_cpu_has(X86_FEATURE_IBPB) && !boot_cpu_has(X86_FEATURE_STIBP))
		वापस;

	अगर (cpu_smt_control == CPU_SMT_FORCE_DISABLED ||
	    cpu_smt_control == CPU_SMT_NOT_SUPPORTED)
		smt_possible = false;

	cmd = spectre_v2_parse_user_cmdline(v2_cmd);
	चयन (cmd) अणु
	हाल SPECTRE_V2_USER_CMD_NONE:
		जाओ set_mode;
	हाल SPECTRE_V2_USER_CMD_FORCE:
		mode = SPECTRE_V2_USER_STRICT;
		अवरोध;
	हाल SPECTRE_V2_USER_CMD_PRCTL:
	हाल SPECTRE_V2_USER_CMD_PRCTL_IBPB:
		mode = SPECTRE_V2_USER_PRCTL;
		अवरोध;
	हाल SPECTRE_V2_USER_CMD_AUTO:
	हाल SPECTRE_V2_USER_CMD_SECCOMP:
	हाल SPECTRE_V2_USER_CMD_SECCOMP_IBPB:
		अगर (IS_ENABLED(CONFIG_SECCOMP))
			mode = SPECTRE_V2_USER_SECCOMP;
		अन्यथा
			mode = SPECTRE_V2_USER_PRCTL;
		अवरोध;
	पूर्ण

	/* Initialize Indirect Branch Prediction Barrier */
	अगर (boot_cpu_has(X86_FEATURE_IBPB)) अणु
		setup_क्रमce_cpu_cap(X86_FEATURE_USE_IBPB);

		spectre_v2_user_ibpb = mode;
		चयन (cmd) अणु
		हाल SPECTRE_V2_USER_CMD_FORCE:
		हाल SPECTRE_V2_USER_CMD_PRCTL_IBPB:
		हाल SPECTRE_V2_USER_CMD_SECCOMP_IBPB:
			अटल_branch_enable(&चयन_mm_always_ibpb);
			spectre_v2_user_ibpb = SPECTRE_V2_USER_STRICT;
			अवरोध;
		हाल SPECTRE_V2_USER_CMD_PRCTL:
		हाल SPECTRE_V2_USER_CMD_AUTO:
		हाल SPECTRE_V2_USER_CMD_SECCOMP:
			अटल_branch_enable(&चयन_mm_cond_ibpb);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		pr_info("mitigation: Enabling %s Indirect Branch Prediction Barrier\n",
			अटल_key_enabled(&चयन_mm_always_ibpb) ?
			"always-on" : "conditional");
	पूर्ण

	/*
	 * If no STIBP, enhanced IBRS is enabled or SMT impossible, STIBP is not
	 * required.
	 */
	अगर (!boot_cpu_has(X86_FEATURE_STIBP) ||
	    !smt_possible ||
	    spectre_v2_enabled == SPECTRE_V2_IBRS_ENHANCED)
		वापस;

	/*
	 * At this poपूर्णांक, an STIBP mode other than "off" has been set.
	 * If STIBP support is not being क्रमced, check अगर STIBP always-on
	 * is preferred.
	 */
	अगर (mode != SPECTRE_V2_USER_STRICT &&
	    boot_cpu_has(X86_FEATURE_AMD_STIBP_ALWAYS_ON))
		mode = SPECTRE_V2_USER_STRICT_PREFERRED;

	spectre_v2_user_stibp = mode;

set_mode:
	pr_info("%s\n", spectre_v2_user_strings[mode]);
पूर्ण

अटल स्थिर अक्षर * स्थिर spectre_v2_strings[] = अणु
	[SPECTRE_V2_NONE]			= "Vulnerable",
	[SPECTRE_V2_RETPOLINE_GENERIC]		= "Mitigation: Full generic retpoline",
	[SPECTRE_V2_RETPOLINE_AMD]		= "Mitigation: Full AMD retpoline",
	[SPECTRE_V2_IBRS_ENHANCED]		= "Mitigation: Enhanced IBRS",
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *option;
	क्रमागत spectre_v2_mitigation_cmd cmd;
	bool secure;
पूर्ण mitigation_options[] __initस्थिर = अणु
	अणु "off",		SPECTRE_V2_CMD_NONE,		  false पूर्ण,
	अणु "on",			SPECTRE_V2_CMD_FORCE,		  true  पूर्ण,
	अणु "retpoline",		SPECTRE_V2_CMD_RETPOLINE,	  false पूर्ण,
	अणु "retpoline,amd",	SPECTRE_V2_CMD_RETPOLINE_AMD,	  false पूर्ण,
	अणु "retpoline,generic",	SPECTRE_V2_CMD_RETPOLINE_GENERIC, false पूर्ण,
	अणु "auto",		SPECTRE_V2_CMD_AUTO,		  false पूर्ण,
पूर्ण;

अटल व्योम __init spec_v2_prपूर्णांक_cond(स्थिर अक्षर *reason, bool secure)
अणु
	अगर (boot_cpu_has_bug(X86_BUG_SPECTRE_V2) != secure)
		pr_info("%s selected on command line.\n", reason);
पूर्ण

अटल क्रमागत spectre_v2_mitigation_cmd __init spectre_v2_parse_cmdline(व्योम)
अणु
	क्रमागत spectre_v2_mitigation_cmd cmd = SPECTRE_V2_CMD_AUTO;
	अक्षर arg[20];
	पूर्णांक ret, i;

	अगर (cmdline_find_option_bool(boot_command_line, "nospectre_v2") ||
	    cpu_mitigations_off())
		वापस SPECTRE_V2_CMD_NONE;

	ret = cmdline_find_option(boot_command_line, "spectre_v2", arg, माप(arg));
	अगर (ret < 0)
		वापस SPECTRE_V2_CMD_AUTO;

	क्रम (i = 0; i < ARRAY_SIZE(mitigation_options); i++) अणु
		अगर (!match_option(arg, ret, mitigation_options[i].option))
			जारी;
		cmd = mitigation_options[i].cmd;
		अवरोध;
	पूर्ण

	अगर (i >= ARRAY_SIZE(mitigation_options)) अणु
		pr_err("unknown option (%s). Switching to AUTO select\n", arg);
		वापस SPECTRE_V2_CMD_AUTO;
	पूर्ण

	अगर ((cmd == SPECTRE_V2_CMD_RETPOLINE ||
	     cmd == SPECTRE_V2_CMD_RETPOLINE_AMD ||
	     cmd == SPECTRE_V2_CMD_RETPOLINE_GENERIC) &&
	    !IS_ENABLED(CONFIG_RETPOLINE)) अणु
		pr_err("%s selected but not compiled in. Switching to AUTO select\n", mitigation_options[i].option);
		वापस SPECTRE_V2_CMD_AUTO;
	पूर्ण

	अगर (cmd == SPECTRE_V2_CMD_RETPOLINE_AMD &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_HYGON &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD) अणु
		pr_err("retpoline,amd selected but CPU is not AMD. Switching to AUTO select\n");
		वापस SPECTRE_V2_CMD_AUTO;
	पूर्ण

	spec_v2_prपूर्णांक_cond(mitigation_options[i].option,
			   mitigation_options[i].secure);
	वापस cmd;
पूर्ण

अटल व्योम __init spectre_v2_select_mitigation(व्योम)
अणु
	क्रमागत spectre_v2_mitigation_cmd cmd = spectre_v2_parse_cmdline();
	क्रमागत spectre_v2_mitigation mode = SPECTRE_V2_NONE;

	/*
	 * If the CPU is not affected and the command line mode is NONE or AUTO
	 * then nothing to करो.
	 */
	अगर (!boot_cpu_has_bug(X86_BUG_SPECTRE_V2) &&
	    (cmd == SPECTRE_V2_CMD_NONE || cmd == SPECTRE_V2_CMD_AUTO))
		वापस;

	चयन (cmd) अणु
	हाल SPECTRE_V2_CMD_NONE:
		वापस;

	हाल SPECTRE_V2_CMD_FORCE:
	हाल SPECTRE_V2_CMD_AUTO:
		अगर (boot_cpu_has(X86_FEATURE_IBRS_ENHANCED)) अणु
			mode = SPECTRE_V2_IBRS_ENHANCED;
			/* Force it so VMEXIT will restore correctly */
			x86_spec_ctrl_base |= SPEC_CTRL_IBRS;
			wrmsrl(MSR_IA32_SPEC_CTRL, x86_spec_ctrl_base);
			जाओ specv2_set_mode;
		पूर्ण
		अगर (IS_ENABLED(CONFIG_RETPOLINE))
			जाओ retpoline_स्वतः;
		अवरोध;
	हाल SPECTRE_V2_CMD_RETPOLINE_AMD:
		अगर (IS_ENABLED(CONFIG_RETPOLINE))
			जाओ retpoline_amd;
		अवरोध;
	हाल SPECTRE_V2_CMD_RETPOLINE_GENERIC:
		अगर (IS_ENABLED(CONFIG_RETPOLINE))
			जाओ retpoline_generic;
		अवरोध;
	हाल SPECTRE_V2_CMD_RETPOLINE:
		अगर (IS_ENABLED(CONFIG_RETPOLINE))
			जाओ retpoline_स्वतः;
		अवरोध;
	पूर्ण
	pr_err("Spectre mitigation: kernel not compiled with retpoline; no mitigation available!");
	वापस;

retpoline_स्वतः:
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD ||
	    boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON) अणु
	retpoline_amd:
		अगर (!boot_cpu_has(X86_FEATURE_LFENCE_RDTSC)) अणु
			pr_err("Spectre mitigation: LFENCE not serializing, switching to generic retpoline\n");
			जाओ retpoline_generic;
		पूर्ण
		mode = SPECTRE_V2_RETPOLINE_AMD;
		setup_क्रमce_cpu_cap(X86_FEATURE_RETPOLINE_AMD);
		setup_क्रमce_cpu_cap(X86_FEATURE_RETPOLINE);
	पूर्ण अन्यथा अणु
	retpoline_generic:
		mode = SPECTRE_V2_RETPOLINE_GENERIC;
		setup_क्रमce_cpu_cap(X86_FEATURE_RETPOLINE);
	पूर्ण

specv2_set_mode:
	spectre_v2_enabled = mode;
	pr_info("%s\n", spectre_v2_strings[mode]);

	/*
	 * If spectre v2 protection has been enabled, unconditionally fill
	 * RSB during a context चयन; this protects against two independent
	 * issues:
	 *
	 *	- RSB underflow (and चयन to BTB) on Skylake+
	 *	- SpectreRSB variant of spectre v2 on X86_BUG_SPECTRE_V2 CPUs
	 */
	setup_क्रमce_cpu_cap(X86_FEATURE_RSB_CTXSW);
	pr_info("Spectre v2 / SpectreRSB mitigation: Filling RSB on context switch\n");

	/*
	 * Retpoline means the kernel is safe because it has no indirect
	 * branches. Enhanced IBRS protects firmware too, so, enable restricted
	 * speculation around firmware calls only when Enhanced IBRS isn't
	 * supported.
	 *
	 * Use "mode" to check Enhanced IBRS instead of boot_cpu_has(), because
	 * the user might select retpoline on the kernel command line and अगर
	 * the CPU supports Enhanced IBRS, kernel might un-पूर्णांकentionally not
	 * enable IBRS around firmware calls.
	 */
	अगर (boot_cpu_has(X86_FEATURE_IBRS) && mode != SPECTRE_V2_IBRS_ENHANCED) अणु
		setup_क्रमce_cpu_cap(X86_FEATURE_USE_IBRS_FW);
		pr_info("Enabling Restricted Speculation for firmware calls\n");
	पूर्ण

	/* Set up IBPB and STIBP depending on the general spectre V2 command */
	spectre_v2_user_select_mitigation(cmd);
पूर्ण

अटल व्योम update_stibp_msr(व्योम * __unused)
अणु
	wrmsrl(MSR_IA32_SPEC_CTRL, x86_spec_ctrl_base);
पूर्ण

/* Update x86_spec_ctrl_base in हाल SMT state changed. */
अटल व्योम update_stibp_strict(व्योम)
अणु
	u64 mask = x86_spec_ctrl_base & ~SPEC_CTRL_STIBP;

	अगर (sched_smt_active())
		mask |= SPEC_CTRL_STIBP;

	अगर (mask == x86_spec_ctrl_base)
		वापस;

	pr_info("Update user space SMT mitigation: STIBP %s\n",
		mask & SPEC_CTRL_STIBP ? "always-on" : "off");
	x86_spec_ctrl_base = mask;
	on_each_cpu(update_stibp_msr, शून्य, 1);
पूर्ण

/* Update the अटल key controlling the evaluation of TIF_SPEC_IB */
अटल व्योम update_indir_branch_cond(व्योम)
अणु
	अगर (sched_smt_active())
		अटल_branch_enable(&चयन_to_cond_stibp);
	अन्यथा
		अटल_branch_disable(&चयन_to_cond_stibp);
पूर्ण

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) fmt

/* Update the अटल key controlling the MDS CPU buffer clear in idle */
अटल व्योम update_mds_branch_idle(व्योम)
अणु
	/*
	 * Enable the idle clearing अगर SMT is active on CPUs which are
	 * affected only by MSBDS and not any other MDS variant.
	 *
	 * The other variants cannot be mitigated when SMT is enabled, so
	 * clearing the buffers on idle just to prevent the Store Buffer
	 * repartitioning leak would be a winकरोw dressing exercise.
	 */
	अगर (!boot_cpu_has_bug(X86_BUG_MSBDS_ONLY))
		वापस;

	अगर (sched_smt_active())
		अटल_branch_enable(&mds_idle_clear);
	अन्यथा
		अटल_branch_disable(&mds_idle_clear);
पूर्ण

#घोषणा MDS_MSG_SMT "MDS CPU bug present and SMT on, data leak possible. See https://www.kernel.org/doc/html/latest/admin-guide/hw-vuln/mds.html for more details.\n"
#घोषणा TAA_MSG_SMT "TAA CPU bug present and SMT on, data leak possible. See https://www.kernel.org/doc/html/latest/admin-guide/hw-vuln/tsx_async_abort.html for more details.\n"

व्योम cpu_bugs_smt_update(व्योम)
अणु
	mutex_lock(&spec_ctrl_mutex);

	चयन (spectre_v2_user_stibp) अणु
	हाल SPECTRE_V2_USER_NONE:
		अवरोध;
	हाल SPECTRE_V2_USER_STRICT:
	हाल SPECTRE_V2_USER_STRICT_PREFERRED:
		update_stibp_strict();
		अवरोध;
	हाल SPECTRE_V2_USER_PRCTL:
	हाल SPECTRE_V2_USER_SECCOMP:
		update_indir_branch_cond();
		अवरोध;
	पूर्ण

	चयन (mds_mitigation) अणु
	हाल MDS_MITIGATION_FULL:
	हाल MDS_MITIGATION_VMWERV:
		अगर (sched_smt_active() && !boot_cpu_has(X86_BUG_MSBDS_ONLY))
			pr_warn_once(MDS_MSG_SMT);
		update_mds_branch_idle();
		अवरोध;
	हाल MDS_MITIGATION_OFF:
		अवरोध;
	पूर्ण

	चयन (taa_mitigation) अणु
	हाल TAA_MITIGATION_VERW:
	हाल TAA_MITIGATION_UCODE_NEEDED:
		अगर (sched_smt_active())
			pr_warn_once(TAA_MSG_SMT);
		अवरोध;
	हाल TAA_MITIGATION_TSX_DISABLED:
	हाल TAA_MITIGATION_OFF:
		अवरोध;
	पूर्ण

	mutex_unlock(&spec_ctrl_mutex);
पूर्ण

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"Speculative Store Bypass: " fmt

अटल क्रमागत ssb_mitigation ssb_mode __ro_after_init = SPEC_STORE_BYPASS_NONE;

/* The kernel command line selection */
क्रमागत ssb_mitigation_cmd अणु
	SPEC_STORE_BYPASS_CMD_NONE,
	SPEC_STORE_BYPASS_CMD_AUTO,
	SPEC_STORE_BYPASS_CMD_ON,
	SPEC_STORE_BYPASS_CMD_PRCTL,
	SPEC_STORE_BYPASS_CMD_SECCOMP,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ssb_strings[] = अणु
	[SPEC_STORE_BYPASS_NONE]	= "Vulnerable",
	[SPEC_STORE_BYPASS_DISABLE]	= "Mitigation: Speculative Store Bypass disabled",
	[SPEC_STORE_BYPASS_PRCTL]	= "Mitigation: Speculative Store Bypass disabled via prctl",
	[SPEC_STORE_BYPASS_SECCOMP]	= "Mitigation: Speculative Store Bypass disabled via prctl and seccomp",
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *option;
	क्रमागत ssb_mitigation_cmd cmd;
पूर्ण ssb_mitigation_options[]  __initस्थिर = अणु
	अणु "auto",	SPEC_STORE_BYPASS_CMD_AUTO पूर्ण,    /* Platक्रमm decides */
	अणु "on",		SPEC_STORE_BYPASS_CMD_ON पूर्ण,      /* Disable Speculative Store Bypass */
	अणु "off",	SPEC_STORE_BYPASS_CMD_NONE पूर्ण,    /* Don't touch Speculative Store Bypass */
	अणु "prctl",	SPEC_STORE_BYPASS_CMD_PRCTL पूर्ण,   /* Disable Speculative Store Bypass via prctl */
	अणु "seccomp",	SPEC_STORE_BYPASS_CMD_SECCOMP पूर्ण, /* Disable Speculative Store Bypass via prctl and seccomp */
पूर्ण;

अटल क्रमागत ssb_mitigation_cmd __init ssb_parse_cmdline(व्योम)
अणु
	क्रमागत ssb_mitigation_cmd cmd = SPEC_STORE_BYPASS_CMD_AUTO;
	अक्षर arg[20];
	पूर्णांक ret, i;

	अगर (cmdline_find_option_bool(boot_command_line, "nospec_store_bypass_disable") ||
	    cpu_mitigations_off()) अणु
		वापस SPEC_STORE_BYPASS_CMD_NONE;
	पूर्ण अन्यथा अणु
		ret = cmdline_find_option(boot_command_line, "spec_store_bypass_disable",
					  arg, माप(arg));
		अगर (ret < 0)
			वापस SPEC_STORE_BYPASS_CMD_AUTO;

		क्रम (i = 0; i < ARRAY_SIZE(ssb_mitigation_options); i++) अणु
			अगर (!match_option(arg, ret, ssb_mitigation_options[i].option))
				जारी;

			cmd = ssb_mitigation_options[i].cmd;
			अवरोध;
		पूर्ण

		अगर (i >= ARRAY_SIZE(ssb_mitigation_options)) अणु
			pr_err("unknown option (%s). Switching to AUTO select\n", arg);
			वापस SPEC_STORE_BYPASS_CMD_AUTO;
		पूर्ण
	पूर्ण

	वापस cmd;
पूर्ण

अटल क्रमागत ssb_mitigation __init __ssb_select_mitigation(व्योम)
अणु
	क्रमागत ssb_mitigation mode = SPEC_STORE_BYPASS_NONE;
	क्रमागत ssb_mitigation_cmd cmd;

	अगर (!boot_cpu_has(X86_FEATURE_SSBD))
		वापस mode;

	cmd = ssb_parse_cmdline();
	अगर (!boot_cpu_has_bug(X86_BUG_SPEC_STORE_BYPASS) &&
	    (cmd == SPEC_STORE_BYPASS_CMD_NONE ||
	     cmd == SPEC_STORE_BYPASS_CMD_AUTO))
		वापस mode;

	चयन (cmd) अणु
	हाल SPEC_STORE_BYPASS_CMD_AUTO:
	हाल SPEC_STORE_BYPASS_CMD_SECCOMP:
		/*
		 * Choose prctl+seccomp as the शेष mode अगर seccomp is
		 * enabled.
		 */
		अगर (IS_ENABLED(CONFIG_SECCOMP))
			mode = SPEC_STORE_BYPASS_SECCOMP;
		अन्यथा
			mode = SPEC_STORE_BYPASS_PRCTL;
		अवरोध;
	हाल SPEC_STORE_BYPASS_CMD_ON:
		mode = SPEC_STORE_BYPASS_DISABLE;
		अवरोध;
	हाल SPEC_STORE_BYPASS_CMD_PRCTL:
		mode = SPEC_STORE_BYPASS_PRCTL;
		अवरोध;
	हाल SPEC_STORE_BYPASS_CMD_NONE:
		अवरोध;
	पूर्ण

	/*
	 * If SSBD is controlled by the SPEC_CTRL MSR, then set the proper
	 * bit in the mask to allow guests to use the mitigation even in the
	 * हाल where the host करोes not enable it.
	 */
	अगर (अटल_cpu_has(X86_FEATURE_SPEC_CTRL_SSBD) ||
	    अटल_cpu_has(X86_FEATURE_AMD_SSBD)) अणु
		x86_spec_ctrl_mask |= SPEC_CTRL_SSBD;
	पूर्ण

	/*
	 * We have three CPU feature flags that are in play here:
	 *  - X86_BUG_SPEC_STORE_BYPASS - CPU is susceptible.
	 *  - X86_FEATURE_SSBD - CPU is able to turn off speculative store bypass
	 *  - X86_FEATURE_SPEC_STORE_BYPASS_DISABLE - engage the mitigation
	 */
	अगर (mode == SPEC_STORE_BYPASS_DISABLE) अणु
		setup_क्रमce_cpu_cap(X86_FEATURE_SPEC_STORE_BYPASS_DISABLE);
		/*
		 * Intel uses the SPEC CTRL MSR Bit(2) क्रम this, जबतक AMD may
		 * use a completely dअगरferent MSR and bit dependent on family.
		 */
		अगर (!अटल_cpu_has(X86_FEATURE_SPEC_CTRL_SSBD) &&
		    !अटल_cpu_has(X86_FEATURE_AMD_SSBD)) अणु
			x86_amd_ssb_disable();
		पूर्ण अन्यथा अणु
			x86_spec_ctrl_base |= SPEC_CTRL_SSBD;
			wrmsrl(MSR_IA32_SPEC_CTRL, x86_spec_ctrl_base);
		पूर्ण
	पूर्ण

	वापस mode;
पूर्ण

अटल व्योम ssb_select_mitigation(व्योम)
अणु
	ssb_mode = __ssb_select_mitigation();

	अगर (boot_cpu_has_bug(X86_BUG_SPEC_STORE_BYPASS))
		pr_info("%s\n", ssb_strings[ssb_mode]);
पूर्ण

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)     "Speculation prctl: " fmt

अटल व्योम task_update_spec_tअगर(काष्ठा task_काष्ठा *tsk)
अणु
	/* Force the update of the real TIF bits */
	set_tsk_thपढ़ो_flag(tsk, TIF_SPEC_FORCE_UPDATE);

	/*
	 * Immediately update the speculation control MSRs क्रम the current
	 * task, but क्रम a non-current task delay setting the CPU
	 * mitigation until it is scheduled next.
	 *
	 * This can only happen क्रम SECCOMP mitigation. For PRCTL it's
	 * always the current task.
	 */
	अगर (tsk == current)
		speculation_ctrl_update_current();
पूर्ण

अटल पूर्णांक ssb_prctl_set(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ ctrl)
अणु
	अगर (ssb_mode != SPEC_STORE_BYPASS_PRCTL &&
	    ssb_mode != SPEC_STORE_BYPASS_SECCOMP)
		वापस -ENXIO;

	चयन (ctrl) अणु
	हाल PR_SPEC_ENABLE:
		/* If speculation is क्रमce disabled, enable is not allowed */
		अगर (task_spec_ssb_क्रमce_disable(task))
			वापस -EPERM;
		task_clear_spec_ssb_disable(task);
		task_clear_spec_ssb_noexec(task);
		task_update_spec_tअगर(task);
		अवरोध;
	हाल PR_SPEC_DISABLE:
		task_set_spec_ssb_disable(task);
		task_clear_spec_ssb_noexec(task);
		task_update_spec_tअगर(task);
		अवरोध;
	हाल PR_SPEC_FORCE_DISABLE:
		task_set_spec_ssb_disable(task);
		task_set_spec_ssb_क्रमce_disable(task);
		task_clear_spec_ssb_noexec(task);
		task_update_spec_tअगर(task);
		अवरोध;
	हाल PR_SPEC_DISABLE_NOEXEC:
		अगर (task_spec_ssb_क्रमce_disable(task))
			वापस -EPERM;
		task_set_spec_ssb_disable(task);
		task_set_spec_ssb_noexec(task);
		task_update_spec_tअगर(task);
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool is_spec_ib_user_controlled(व्योम)
अणु
	वापस spectre_v2_user_ibpb == SPECTRE_V2_USER_PRCTL ||
		spectre_v2_user_ibpb == SPECTRE_V2_USER_SECCOMP ||
		spectre_v2_user_stibp == SPECTRE_V2_USER_PRCTL ||
		spectre_v2_user_stibp == SPECTRE_V2_USER_SECCOMP;
पूर्ण

अटल पूर्णांक ib_prctl_set(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ ctrl)
अणु
	चयन (ctrl) अणु
	हाल PR_SPEC_ENABLE:
		अगर (spectre_v2_user_ibpb == SPECTRE_V2_USER_NONE &&
		    spectre_v2_user_stibp == SPECTRE_V2_USER_NONE)
			वापस 0;

		/*
		 * With strict mode क्रम both IBPB and STIBP, the inकाष्ठाion
		 * code paths aव्योम checking this task flag and instead,
		 * unconditionally run the inकाष्ठाion. However, STIBP and IBPB
		 * are independent and either can be set to conditionally
		 * enabled regardless of the mode of the other.
		 *
		 * If either is set to conditional, allow the task flag to be
		 * updated, unless it was क्रमce-disabled by a previous prctl
		 * call. Currently, this is possible on an AMD CPU which has the
		 * feature X86_FEATURE_AMD_STIBP_ALWAYS_ON. In this हाल, अगर the
		 * kernel is booted with 'spectre_v2_user=seccomp', then
		 * spectre_v2_user_ibpb == SPECTRE_V2_USER_SECCOMP and
		 * spectre_v2_user_stibp == SPECTRE_V2_USER_STRICT_PREFERRED.
		 */
		अगर (!is_spec_ib_user_controlled() ||
		    task_spec_ib_क्रमce_disable(task))
			वापस -EPERM;

		task_clear_spec_ib_disable(task);
		task_update_spec_tअगर(task);
		अवरोध;
	हाल PR_SPEC_DISABLE:
	हाल PR_SPEC_FORCE_DISABLE:
		/*
		 * Indirect branch speculation is always allowed when
		 * mitigation is क्रमce disabled.
		 */
		अगर (spectre_v2_user_ibpb == SPECTRE_V2_USER_NONE &&
		    spectre_v2_user_stibp == SPECTRE_V2_USER_NONE)
			वापस -EPERM;

		अगर (!is_spec_ib_user_controlled())
			वापस 0;

		task_set_spec_ib_disable(task);
		अगर (ctrl == PR_SPEC_FORCE_DISABLE)
			task_set_spec_ib_क्रमce_disable(task);
		task_update_spec_tअगर(task);
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक arch_prctl_spec_ctrl_set(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ which,
			     अचिन्हित दीर्घ ctrl)
अणु
	चयन (which) अणु
	हाल PR_SPEC_STORE_BYPASS:
		वापस ssb_prctl_set(task, ctrl);
	हाल PR_SPEC_INसूचीECT_BRANCH:
		वापस ib_prctl_set(task, ctrl);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SECCOMP
व्योम arch_seccomp_spec_mitigate(काष्ठा task_काष्ठा *task)
अणु
	अगर (ssb_mode == SPEC_STORE_BYPASS_SECCOMP)
		ssb_prctl_set(task, PR_SPEC_FORCE_DISABLE);
	अगर (spectre_v2_user_ibpb == SPECTRE_V2_USER_SECCOMP ||
	    spectre_v2_user_stibp == SPECTRE_V2_USER_SECCOMP)
		ib_prctl_set(task, PR_SPEC_FORCE_DISABLE);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ssb_prctl_get(काष्ठा task_काष्ठा *task)
अणु
	चयन (ssb_mode) अणु
	हाल SPEC_STORE_BYPASS_DISABLE:
		वापस PR_SPEC_DISABLE;
	हाल SPEC_STORE_BYPASS_SECCOMP:
	हाल SPEC_STORE_BYPASS_PRCTL:
		अगर (task_spec_ssb_क्रमce_disable(task))
			वापस PR_SPEC_PRCTL | PR_SPEC_FORCE_DISABLE;
		अगर (task_spec_ssb_noexec(task))
			वापस PR_SPEC_PRCTL | PR_SPEC_DISABLE_NOEXEC;
		अगर (task_spec_ssb_disable(task))
			वापस PR_SPEC_PRCTL | PR_SPEC_DISABLE;
		वापस PR_SPEC_PRCTL | PR_SPEC_ENABLE;
	शेष:
		अगर (boot_cpu_has_bug(X86_BUG_SPEC_STORE_BYPASS))
			वापस PR_SPEC_ENABLE;
		वापस PR_SPEC_NOT_AFFECTED;
	पूर्ण
पूर्ण

अटल पूर्णांक ib_prctl_get(काष्ठा task_काष्ठा *task)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_SPECTRE_V2))
		वापस PR_SPEC_NOT_AFFECTED;

	अगर (spectre_v2_user_ibpb == SPECTRE_V2_USER_NONE &&
	    spectre_v2_user_stibp == SPECTRE_V2_USER_NONE)
		वापस PR_SPEC_ENABLE;
	अन्यथा अगर (is_spec_ib_user_controlled()) अणु
		अगर (task_spec_ib_क्रमce_disable(task))
			वापस PR_SPEC_PRCTL | PR_SPEC_FORCE_DISABLE;
		अगर (task_spec_ib_disable(task))
			वापस PR_SPEC_PRCTL | PR_SPEC_DISABLE;
		वापस PR_SPEC_PRCTL | PR_SPEC_ENABLE;
	पूर्ण अन्यथा अगर (spectre_v2_user_ibpb == SPECTRE_V2_USER_STRICT ||
	    spectre_v2_user_stibp == SPECTRE_V2_USER_STRICT ||
	    spectre_v2_user_stibp == SPECTRE_V2_USER_STRICT_PREFERRED)
		वापस PR_SPEC_DISABLE;
	अन्यथा
		वापस PR_SPEC_NOT_AFFECTED;
पूर्ण

पूर्णांक arch_prctl_spec_ctrl_get(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ which)
अणु
	चयन (which) अणु
	हाल PR_SPEC_STORE_BYPASS:
		वापस ssb_prctl_get(task);
	हाल PR_SPEC_INसूचीECT_BRANCH:
		वापस ib_prctl_get(task);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

व्योम x86_spec_ctrl_setup_ap(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_MSR_SPEC_CTRL))
		wrmsrl(MSR_IA32_SPEC_CTRL, x86_spec_ctrl_base);

	अगर (ssb_mode == SPEC_STORE_BYPASS_DISABLE)
		x86_amd_ssb_disable();
पूर्ण

bool itlb_multihit_kvm_mitigation;
EXPORT_SYMBOL_GPL(itlb_multihit_kvm_mitigation);

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"L1TF: " fmt

/* Default mitigation क्रम L1TF-affected CPUs */
क्रमागत l1tf_mitigations l1tf_mitigation __ro_after_init = L1TF_MITIGATION_FLUSH;
#अगर IS_ENABLED(CONFIG_KVM_INTEL)
EXPORT_SYMBOL_GPL(l1tf_mitigation);
#पूर्ण_अगर
क्रमागत vmx_l1d_flush_state l1tf_vmx_mitigation = VMENTER_L1D_FLUSH_AUTO;
EXPORT_SYMBOL_GPL(l1tf_vmx_mitigation);

/*
 * These CPUs all support 44bits physical address space पूर्णांकernally in the
 * cache but CPUID can report a smaller number of physical address bits.
 *
 * The L1TF mitigation uses the top most address bit क्रम the inversion of
 * non present PTEs. When the installed memory reaches पूर्णांकo the top most
 * address bit due to memory holes, which has been observed on machines
 * which report 36bits physical address bits and have 32G RAM installed,
 * then the mitigation range check in l1tf_select_mitigation() triggers.
 * This is a false positive because the mitigation is still possible due to
 * the fact that the cache uses 44bit पूर्णांकernally. Use the cache bits
 * instead of the reported physical bits and adjust them on the affected
 * machines to 44bit अगर the reported bits are less than 44.
 */
अटल व्योम override_cache_bits(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (c->x86 != 6)
		वापस;

	चयन (c->x86_model) अणु
	हाल INTEL_FAM6_NEHALEM:
	हाल INTEL_FAM6_WESTMERE:
	हाल INTEL_FAM6_SANDYBRIDGE:
	हाल INTEL_FAM6_IVYBRIDGE:
	हाल INTEL_FAM6_HASWELL:
	हाल INTEL_FAM6_HASWELL_L:
	हाल INTEL_FAM6_HASWELL_G:
	हाल INTEL_FAM6_BROADWELL:
	हाल INTEL_FAM6_BROADWELL_G:
	हाल INTEL_FAM6_SKYLAKE_L:
	हाल INTEL_FAM6_SKYLAKE:
	हाल INTEL_FAM6_KABYLAKE_L:
	हाल INTEL_FAM6_KABYLAKE:
		अगर (c->x86_cache_bits < 44)
			c->x86_cache_bits = 44;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init l1tf_select_mitigation(व्योम)
अणु
	u64 half_pa;

	अगर (!boot_cpu_has_bug(X86_BUG_L1TF))
		वापस;

	अगर (cpu_mitigations_off())
		l1tf_mitigation = L1TF_MITIGATION_OFF;
	अन्यथा अगर (cpu_mitigations_स्वतः_nosmt())
		l1tf_mitigation = L1TF_MITIGATION_FLUSH_NOSMT;

	override_cache_bits(&boot_cpu_data);

	चयन (l1tf_mitigation) अणु
	हाल L1TF_MITIGATION_OFF:
	हाल L1TF_MITIGATION_FLUSH_NOWARN:
	हाल L1TF_MITIGATION_FLUSH:
		अवरोध;
	हाल L1TF_MITIGATION_FLUSH_NOSMT:
	हाल L1TF_MITIGATION_FULL:
		cpu_smt_disable(false);
		अवरोध;
	हाल L1TF_MITIGATION_FULL_FORCE:
		cpu_smt_disable(true);
		अवरोध;
	पूर्ण

#अगर CONFIG_PGTABLE_LEVELS == 2
	pr_warn("Kernel not compiled for PAE. No mitigation for L1TF\n");
	वापस;
#पूर्ण_अगर

	half_pa = (u64)l1tf_pfn_limit() << PAGE_SHIFT;
	अगर (l1tf_mitigation != L1TF_MITIGATION_OFF &&
			e820__mapped_any(half_pa, ULदीर्घ_उच्च - half_pa, E820_TYPE_RAM)) अणु
		pr_warn("System has more than MAX_PA/2 memory. L1TF mitigation not effective.\n");
		pr_info("You may make it effective by booting the kernel with mem=%llu parameter.\n",
				half_pa);
		pr_info("However, doing so will make a part of your RAM unusable.\n");
		pr_info("Reading https://www.kernel.org/doc/html/latest/admin-guide/hw-vuln/l1tf.html might help you decide.\n");
		वापस;
	पूर्ण

	setup_क्रमce_cpu_cap(X86_FEATURE_L1TF_PTEINV);
पूर्ण

अटल पूर्णांक __init l1tf_cmdline(अक्षर *str)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_L1TF))
		वापस 0;

	अगर (!str)
		वापस -EINVAL;

	अगर (!म_भेद(str, "off"))
		l1tf_mitigation = L1TF_MITIGATION_OFF;
	अन्यथा अगर (!म_भेद(str, "flush,nowarn"))
		l1tf_mitigation = L1TF_MITIGATION_FLUSH_NOWARN;
	अन्यथा अगर (!म_भेद(str, "flush"))
		l1tf_mitigation = L1TF_MITIGATION_FLUSH;
	अन्यथा अगर (!म_भेद(str, "flush,nosmt"))
		l1tf_mitigation = L1TF_MITIGATION_FLUSH_NOSMT;
	अन्यथा अगर (!म_भेद(str, "full"))
		l1tf_mitigation = L1TF_MITIGATION_FULL;
	अन्यथा अगर (!म_भेद(str, "full,force"))
		l1tf_mitigation = L1TF_MITIGATION_FULL_FORCE;

	वापस 0;
पूर्ण
early_param("l1tf", l1tf_cmdline);

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) fmt

#अगर_घोषित CONFIG_SYSFS

#घोषणा L1TF_DEFAULT_MSG "Mitigation: PTE Inversion"

#अगर IS_ENABLED(CONFIG_KVM_INTEL)
अटल स्थिर अक्षर * स्थिर l1tf_vmx_states[] = अणु
	[VMENTER_L1D_FLUSH_AUTO]		= "auto",
	[VMENTER_L1D_FLUSH_NEVER]		= "vulnerable",
	[VMENTER_L1D_FLUSH_COND]		= "conditional cache flushes",
	[VMENTER_L1D_FLUSH_ALWAYS]		= "cache flushes",
	[VMENTER_L1D_FLUSH_EPT_DISABLED]	= "EPT disabled",
	[VMENTER_L1D_FLUSH_NOT_REQUIRED]	= "flush not necessary"
पूर्ण;

अटल sमाप_प्रकार l1tf_show_state(अक्षर *buf)
अणु
	अगर (l1tf_vmx_mitigation == VMENTER_L1D_FLUSH_AUTO)
		वापस प्र_लिखो(buf, "%s\n", L1TF_DEFAULT_MSG);

	अगर (l1tf_vmx_mitigation == VMENTER_L1D_FLUSH_EPT_DISABLED ||
	    (l1tf_vmx_mitigation == VMENTER_L1D_FLUSH_NEVER &&
	     sched_smt_active())) अणु
		वापस प्र_लिखो(buf, "%s; VMX: %s\n", L1TF_DEFAULT_MSG,
			       l1tf_vmx_states[l1tf_vmx_mitigation]);
	पूर्ण

	वापस प्र_लिखो(buf, "%s; VMX: %s, SMT %s\n", L1TF_DEFAULT_MSG,
		       l1tf_vmx_states[l1tf_vmx_mitigation],
		       sched_smt_active() ? "vulnerable" : "disabled");
पूर्ण

अटल sमाप_प्रकार itlb_multihit_show_state(अक्षर *buf)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_MSR_IA32_FEAT_CTL) ||
	    !boot_cpu_has(X86_FEATURE_VMX))
		वापस प्र_लिखो(buf, "KVM: Mitigation: VMX unsupported\n");
	अन्यथा अगर (!(cr4_पढ़ो_shaकरोw() & X86_CR4_VMXE))
		वापस प्र_लिखो(buf, "KVM: Mitigation: VMX disabled\n");
	अन्यथा अगर (itlb_multihit_kvm_mitigation)
		वापस प्र_लिखो(buf, "KVM: Mitigation: Split huge pages\n");
	अन्यथा
		वापस प्र_लिखो(buf, "KVM: Vulnerable\n");
पूर्ण
#अन्यथा
अटल sमाप_प्रकार l1tf_show_state(अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", L1TF_DEFAULT_MSG);
पूर्ण

अटल sमाप_प्रकार itlb_multihit_show_state(अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "Processor vulnerable\n");
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार mds_show_state(अक्षर *buf)
अणु
	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR)) अणु
		वापस प्र_लिखो(buf, "%s; SMT Host state unknown\n",
			       mds_strings[mds_mitigation]);
	पूर्ण

	अगर (boot_cpu_has(X86_BUG_MSBDS_ONLY)) अणु
		वापस प्र_लिखो(buf, "%s; SMT %s\n", mds_strings[mds_mitigation],
			       (mds_mitigation == MDS_MITIGATION_OFF ? "vulnerable" :
			        sched_smt_active() ? "mitigated" : "disabled"));
	पूर्ण

	वापस प्र_लिखो(buf, "%s; SMT %s\n", mds_strings[mds_mitigation],
		       sched_smt_active() ? "vulnerable" : "disabled");
पूर्ण

अटल sमाप_प्रकार tsx_async_पात_show_state(अक्षर *buf)
अणु
	अगर ((taa_mitigation == TAA_MITIGATION_TSX_DISABLED) ||
	    (taa_mitigation == TAA_MITIGATION_OFF))
		वापस प्र_लिखो(buf, "%s\n", taa_strings[taa_mitigation]);

	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR)) अणु
		वापस प्र_लिखो(buf, "%s; SMT Host state unknown\n",
			       taa_strings[taa_mitigation]);
	पूर्ण

	वापस प्र_लिखो(buf, "%s; SMT %s\n", taa_strings[taa_mitigation],
		       sched_smt_active() ? "vulnerable" : "disabled");
पूर्ण

अटल अक्षर *stibp_state(व्योम)
अणु
	अगर (spectre_v2_enabled == SPECTRE_V2_IBRS_ENHANCED)
		वापस "";

	चयन (spectre_v2_user_stibp) अणु
	हाल SPECTRE_V2_USER_NONE:
		वापस ", STIBP: disabled";
	हाल SPECTRE_V2_USER_STRICT:
		वापस ", STIBP: forced";
	हाल SPECTRE_V2_USER_STRICT_PREFERRED:
		वापस ", STIBP: always-on";
	हाल SPECTRE_V2_USER_PRCTL:
	हाल SPECTRE_V2_USER_SECCOMP:
		अगर (अटल_key_enabled(&चयन_to_cond_stibp))
			वापस ", STIBP: conditional";
	पूर्ण
	वापस "";
पूर्ण

अटल अक्षर *ibpb_state(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_IBPB)) अणु
		अगर (अटल_key_enabled(&चयन_mm_always_ibpb))
			वापस ", IBPB: always-on";
		अगर (अटल_key_enabled(&चयन_mm_cond_ibpb))
			वापस ", IBPB: conditional";
		वापस ", IBPB: disabled";
	पूर्ण
	वापस "";
पूर्ण

अटल sमाप_प्रकार srbds_show_state(अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", srbds_strings[srbds_mitigation]);
पूर्ण

अटल sमाप_प्रकार cpu_show_common(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       अक्षर *buf, अचिन्हित पूर्णांक bug)
अणु
	अगर (!boot_cpu_has_bug(bug))
		वापस प्र_लिखो(buf, "Not affected\n");

	चयन (bug) अणु
	हाल X86_BUG_CPU_MELTDOWN:
		अगर (boot_cpu_has(X86_FEATURE_PTI))
			वापस प्र_लिखो(buf, "Mitigation: PTI\n");

		अगर (hypervisor_is_type(X86_HYPER_XEN_PV))
			वापस प्र_लिखो(buf, "Unknown (XEN PV detected, hypervisor mitigation required)\n");

		अवरोध;

	हाल X86_BUG_SPECTRE_V1:
		वापस प्र_लिखो(buf, "%s\n", spectre_v1_strings[spectre_v1_mitigation]);

	हाल X86_BUG_SPECTRE_V2:
		वापस प्र_लिखो(buf, "%s%s%s%s%s%s\n", spectre_v2_strings[spectre_v2_enabled],
			       ibpb_state(),
			       boot_cpu_has(X86_FEATURE_USE_IBRS_FW) ? ", IBRS_FW" : "",
			       stibp_state(),
			       boot_cpu_has(X86_FEATURE_RSB_CTXSW) ? ", RSB filling" : "",
			       spectre_v2_module_string());

	हाल X86_BUG_SPEC_STORE_BYPASS:
		वापस प्र_लिखो(buf, "%s\n", ssb_strings[ssb_mode]);

	हाल X86_BUG_L1TF:
		अगर (boot_cpu_has(X86_FEATURE_L1TF_PTEINV))
			वापस l1tf_show_state(buf);
		अवरोध;

	हाल X86_BUG_MDS:
		वापस mds_show_state(buf);

	हाल X86_BUG_TAA:
		वापस tsx_async_पात_show_state(buf);

	हाल X86_BUG_ITLB_MULTIHIT:
		वापस itlb_multihit_show_state(buf);

	हाल X86_BUG_SRBDS:
		वापस srbds_show_state(buf);

	शेष:
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "Vulnerable\n");
पूर्ण

sमाप_प्रकार cpu_show_meltकरोwn(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_CPU_MELTDOWN);
पूर्ण

sमाप_प्रकार cpu_show_spectre_v1(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_SPECTRE_V1);
पूर्ण

sमाप_प्रकार cpu_show_spectre_v2(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_SPECTRE_V2);
पूर्ण

sमाप_प्रकार cpu_show_spec_store_bypass(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_SPEC_STORE_BYPASS);
पूर्ण

sमाप_प्रकार cpu_show_l1tf(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_L1TF);
पूर्ण

sमाप_प्रकार cpu_show_mds(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_MDS);
पूर्ण

sमाप_प्रकार cpu_show_tsx_async_पात(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_TAA);
पूर्ण

sमाप_प्रकार cpu_show_itlb_multihit(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_ITLB_MULTIHIT);
पूर्ण

sमाप_प्रकार cpu_show_srbds(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_common(dev, attr, buf, X86_BUG_SRBDS);
पूर्ण
#पूर्ण_अगर

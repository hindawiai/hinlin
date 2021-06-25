<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Transactional Synchronization Extensions (TSX) control.
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * Author:
 *	Pawan Gupta <pawan.kumar.gupta@linux.पूर्णांकel.com>
 */

#समावेश <linux/cpufeature.h>

#समावेश <यंत्र/cmdline.h>

#समावेश "cpu.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "tsx: " fmt

क्रमागत tsx_ctrl_states tsx_ctrl_state __ro_after_init = TSX_CTRL_NOT_SUPPORTED;

व्योम tsx_disable(व्योम)
अणु
	u64 tsx;

	rdmsrl(MSR_IA32_TSX_CTRL, tsx);

	/* Force all transactions to immediately पात */
	tsx |= TSX_CTRL_RTM_DISABLE;

	/*
	 * Ensure TSX support is not क्रमागतerated in CPUID.
	 * This is visible to userspace and will ensure they
	 * करो not waste resources trying TSX transactions that
	 * will always पात.
	 */
	tsx |= TSX_CTRL_CPUID_CLEAR;

	wrmsrl(MSR_IA32_TSX_CTRL, tsx);
पूर्ण

व्योम tsx_enable(व्योम)
अणु
	u64 tsx;

	rdmsrl(MSR_IA32_TSX_CTRL, tsx);

	/* Enable the RTM feature in the cpu */
	tsx &= ~TSX_CTRL_RTM_DISABLE;

	/*
	 * Ensure TSX support is क्रमागतerated in CPUID.
	 * This is visible to userspace and will ensure they
	 * can क्रमागतerate and use the TSX feature.
	 */
	tsx &= ~TSX_CTRL_CPUID_CLEAR;

	wrmsrl(MSR_IA32_TSX_CTRL, tsx);
पूर्ण

अटल bool __init tsx_ctrl_is_supported(व्योम)
अणु
	u64 ia32_cap = x86_पढ़ो_arch_cap_msr();

	/*
	 * TSX is controlled via MSR_IA32_TSX_CTRL.  However, support क्रम this
	 * MSR is क्रमागतerated by ARCH_CAP_TSX_MSR bit in MSR_IA32_ARCH_CAPABILITIES.
	 *
	 * TSX control (aka MSR_IA32_TSX_CTRL) is only available after a
	 * microcode update on CPUs that have their MSR_IA32_ARCH_CAPABILITIES
	 * bit MDS_NO=1. CPUs with MDS_NO=0 are not planned to get
	 * MSR_IA32_TSX_CTRL support even after a microcode update. Thus,
	 * tsx= cmdline requests will करो nothing on CPUs without
	 * MSR_IA32_TSX_CTRL support.
	 */
	वापस !!(ia32_cap & ARCH_CAP_TSX_CTRL_MSR);
पूर्ण

अटल क्रमागत tsx_ctrl_states x86_get_tsx_स्वतः_mode(व्योम)
अणु
	अगर (boot_cpu_has_bug(X86_BUG_TAA))
		वापस TSX_CTRL_DISABLE;

	वापस TSX_CTRL_ENABLE;
पूर्ण

व्योम __init tsx_init(व्योम)
अणु
	अक्षर arg[5] = अणुपूर्ण;
	पूर्णांक ret;

	अगर (!tsx_ctrl_is_supported())
		वापस;

	ret = cmdline_find_option(boot_command_line, "tsx", arg, माप(arg));
	अगर (ret >= 0) अणु
		अगर (!म_भेद(arg, "on")) अणु
			tsx_ctrl_state = TSX_CTRL_ENABLE;
		पूर्ण अन्यथा अगर (!म_भेद(arg, "off")) अणु
			tsx_ctrl_state = TSX_CTRL_DISABLE;
		पूर्ण अन्यथा अगर (!म_भेद(arg, "auto")) अणु
			tsx_ctrl_state = x86_get_tsx_स्वतः_mode();
		पूर्ण अन्यथा अणु
			tsx_ctrl_state = TSX_CTRL_DISABLE;
			pr_err("invalid option, defaulting to off\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/* tsx= not provided */
		अगर (IS_ENABLED(CONFIG_X86_INTEL_TSX_MODE_AUTO))
			tsx_ctrl_state = x86_get_tsx_स्वतः_mode();
		अन्यथा अगर (IS_ENABLED(CONFIG_X86_INTEL_TSX_MODE_OFF))
			tsx_ctrl_state = TSX_CTRL_DISABLE;
		अन्यथा
			tsx_ctrl_state = TSX_CTRL_ENABLE;
	पूर्ण

	अगर (tsx_ctrl_state == TSX_CTRL_DISABLE) अणु
		tsx_disable();

		/*
		 * tsx_disable() will change the state of the RTM and HLE CPUID
		 * bits. Clear them here since they are now expected to be not
		 * set.
		 */
		setup_clear_cpu_cap(X86_FEATURE_RTM);
		setup_clear_cpu_cap(X86_FEATURE_HLE);
	पूर्ण अन्यथा अगर (tsx_ctrl_state == TSX_CTRL_ENABLE) अणु

		/*
		 * HW शेषs TSX to be enabled at bootup.
		 * We may still need the TSX enable support
		 * during init क्रम special हालs like
		 * kexec after TSX is disabled.
		 */
		tsx_enable();

		/*
		 * tsx_enable() will change the state of the RTM and HLE CPUID
		 * bits. Force them here since they are now expected to be set.
		 */
		setup_क्रमce_cpu_cap(X86_FEATURE_RTM);
		setup_क्रमce_cpu_cap(X86_FEATURE_HLE);
	पूर्ण
पूर्ण

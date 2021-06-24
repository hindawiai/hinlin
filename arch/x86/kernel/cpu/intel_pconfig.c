<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel PCONFIG inकाष्ठाion support.
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Author:
 *	Kirill A. Shutemov <kirill.shutemov@linux.पूर्णांकel.com>
 */

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/पूर्णांकel_pconfig.h>

#घोषणा	PCONFIG_CPUID			0x1b

#घोषणा PCONFIG_CPUID_SUBLEAF_MASK	((1 << 12) - 1)

/* Subleaf type (EAX) क्रम PCONFIG CPUID leaf (0x1B) */
क्रमागत अणु
	PCONFIG_CPUID_SUBLEAF_INVALID	= 0,
	PCONFIG_CPUID_SUBLEAF_TARGETID	= 1,
पूर्ण;

/* Biपंचांगask of supported tarमाला_लो */
अटल u64 tarमाला_लो_supported __पढ़ो_mostly;

पूर्णांक pconfig_target_supported(क्रमागत pconfig_target target)
अणु
	/*
	 * We would need to re-think the implementation once we get > 64
	 * PCONFIG tarमाला_लो. Spec allows up to 2^32 tarमाला_लो.
	 */
	BUILD_BUG_ON(PCONFIG_TARGET_NR >= 64);

	अगर (WARN_ON_ONCE(target >= 64))
		वापस 0;
	वापस tarमाला_लो_supported & (1ULL << target);
पूर्ण

अटल पूर्णांक __init पूर्णांकel_pconfig_init(व्योम)
अणु
	पूर्णांक subleaf;

	अगर (!boot_cpu_has(X86_FEATURE_PCONFIG))
		वापस 0;

	/*
	 * Scan subleafs of PCONFIG CPUID leaf.
	 *
	 * Subleafs of the same type need not to be consecutive.
	 *
	 * Stop on the first invalid subleaf type. All subleafs after the first
	 * invalid are invalid too.
	 */
	क्रम (subleaf = 0; subleaf < पूर्णांक_उच्च; subleaf++) अणु
		काष्ठा cpuid_regs regs;

		cpuid_count(PCONFIG_CPUID, subleaf,
				&regs.eax, &regs.ebx, &regs.ecx, &regs.edx);

		चयन (regs.eax & PCONFIG_CPUID_SUBLEAF_MASK) अणु
		हाल PCONFIG_CPUID_SUBLEAF_INVALID:
			/* Stop on the first invalid subleaf */
			जाओ out;
		हाल PCONFIG_CPUID_SUBLEAF_TARGETID:
			/* Mark supported PCONFIG tarमाला_लो */
			अगर (regs.ebx < 64)
				tarमाला_लो_supported |= (1ULL << regs.ebx);
			अगर (regs.ecx < 64)
				tarमाला_लो_supported |= (1ULL << regs.ecx);
			अगर (regs.edx < 64)
				tarमाला_लो_supported |= (1ULL << regs.edx);
			अवरोध;
		शेष:
			/* Unknown CPUID.PCONFIG subleaf: ignore */
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस 0;
पूर्ण
arch_initcall(पूर्णांकel_pconfig_init);

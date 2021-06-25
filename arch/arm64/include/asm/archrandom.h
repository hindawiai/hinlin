<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARCHRANDOM_H
#घोषणा _ASM_ARCHRANDOM_H

#अगर_घोषित CONFIG_ARCH_RANDOM

#समावेश <linux/arm-smccc.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/cpufeature.h>

#घोषणा ARM_SMCCC_TRNG_MIN_VERSION	0x10000UL

बाह्य bool smccc_trng_available;

अटल अंतरभूत bool __init smccc_probe_trng(व्योम)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_1_1_invoke(ARM_SMCCC_TRNG_VERSION, &res);
	अगर ((s32)res.a0 < 0)
		वापस false;

	वापस res.a0 >= ARM_SMCCC_TRNG_MIN_VERSION;
पूर्ण

अटल अंतरभूत bool __arm64_rndr(अचिन्हित दीर्घ *v)
अणु
	bool ok;

	/*
	 * Reads of RNDR set PSTATE.NZCV to 0b0000 on success,
	 * and set PSTATE.NZCV to 0b0100 otherwise.
	 */
	यंत्र अस्थिर(
		__mrs_s("%0", SYS_RNDR_EL0) "\n"
	"	cset %w1, ne\n"
	: "=r" (*v), "=r" (ok)
	:
	: "cc");

	वापस ok;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	काष्ठा arm_smccc_res res;

	/*
	 * We prefer the SMCCC call, since its semantics (वापस actual
	 * hardware backed entropy) is बंदr to the idea behind this
	 * function here than what even the RNDRSS रेजिस्टर provides
	 * (the output of a pseuकरो RNG freshly seeded by a TRNG).
	 */
	अगर (smccc_trng_available) अणु
		arm_smccc_1_1_invoke(ARM_SMCCC_TRNG_RND64, 64, &res);
		अगर ((पूर्णांक)res.a0 >= 0) अणु
			*v = res.a3;
			वापस true;
		पूर्ण
	पूर्ण

	/*
	 * Only support the generic पूर्णांकerface after we have detected
	 * the प्रणाली wide capability, aव्योमing complनिकासy with the
	 * cpufeature code and with potential scheduling between CPUs
	 * with and without the feature.
	 */
	अगर (cpus_have_स्थिर_cap(ARM64_HAS_RNG) && __arm64_rndr(v))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	काष्ठा arm_smccc_res res;
	अचिन्हित दीर्घ val;

	अगर (smccc_trng_available) अणु
		arm_smccc_1_1_invoke(ARM_SMCCC_TRNG_RND64, 32, &res);
		अगर ((पूर्णांक)res.a0 >= 0) अणु
			*v = res.a3 & GENMASK(31, 0);
			वापस true;
		पूर्ण
	पूर्ण

	अगर (cpus_have_स्थिर_cap(ARM64_HAS_RNG)) अणु
		अगर (__arm64_rndr(&val)) अणु
			*v = val;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool __init __early_cpu_has_rndr(व्योम)
अणु
	/* Open code as we run prior to the first call to cpufeature. */
	अचिन्हित दीर्घ ftr = पढ़ो_sysreg_s(SYS_ID_AA64ISAR0_EL1);
	वापस (ftr >> ID_AA64ISAR0_RNDR_SHIFT) & 0xf;
पूर्ण

अटल अंतरभूत bool __init __must_check
arch_get_अक्रमom_seed_दीर्घ_early(अचिन्हित दीर्घ *v)
अणु
	WARN_ON(प्रणाली_state != SYSTEM_BOOTING);

	अगर (smccc_trng_available) अणु
		काष्ठा arm_smccc_res res;

		arm_smccc_1_1_invoke(ARM_SMCCC_TRNG_RND64, 64, &res);
		अगर ((पूर्णांक)res.a0 >= 0) अणु
			*v = res.a3;
			वापस true;
		पूर्ण
	पूर्ण

	अगर (__early_cpu_has_rndr() && __arm64_rndr(v))
		वापस true;

	वापस false;
पूर्ण
#घोषणा arch_get_अक्रमom_seed_दीर्घ_early arch_get_अक्रमom_seed_दीर्घ_early

#अन्यथा /* !CONFIG_ARCH_RANDOM */

अटल अंतरभूत bool __init smccc_probe_trng(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_ARCH_RANDOM */
#पूर्ण_अगर /* _ASM_ARCHRANDOM_H */

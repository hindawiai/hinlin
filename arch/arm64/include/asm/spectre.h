<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interface क्रम managing mitigations क्रम Spectre vulnerabilities.
 *
 * Copyright (C) 2020 Google LLC
 * Author: Will Deacon <will@kernel.org>
 */

#अगर_अघोषित __ASM_SPECTRE_H
#घोषणा __ASM_SPECTRE_H

#घोषणा BP_HARDEN_EL2_SLOTS 4
#घोषणा __BP_HARDEN_HYP_VECS_SZ	((BP_HARDEN_EL2_SLOTS - 1) * SZ_2K)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/percpu.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/virt.h>

/* Watch out, ordering is important here. */
क्रमागत mitigation_state अणु
	SPECTRE_UNAFFECTED,
	SPECTRE_MITIGATED,
	SPECTRE_VULNERABLE,
पूर्ण;

काष्ठा task_काष्ठा;

/*
 * Note: the order of this क्रमागत corresponds to __bp_harden_hyp_vecs and
 * we rely on having the direct vectors first.
 */
क्रमागत arm64_hyp_spectre_vector अणु
	/*
	 * Take exceptions directly to __kvm_hyp_vector. This must be
	 * 0 so that it used by शेष when mitigations are not needed.
	 */
	HYP_VECTOR_सूचीECT,

	/*
	 * Bounce via a slot in the hypervisor text mapping of
	 * __bp_harden_hyp_vecs, which contains an SMC call.
	 */
	HYP_VECTOR_SPECTRE_सूचीECT,

	/*
	 * Bounce via a slot in a special mapping of __bp_harden_hyp_vecs
	 * next to the idmap page.
	 */
	HYP_VECTOR_INसूचीECT,

	/*
	 * Bounce via a slot in a special mapping of __bp_harden_hyp_vecs
	 * next to the idmap page, which contains an SMC call.
	 */
	HYP_VECTOR_SPECTRE_INसूचीECT,
पूर्ण;

प्रकार व्योम (*bp_hardening_cb_t)(व्योम);

काष्ठा bp_hardening_data अणु
	क्रमागत arm64_hyp_spectre_vector	slot;
	bp_hardening_cb_t		fn;
पूर्ण;

DECLARE_PER_CPU_READ_MOSTLY(काष्ठा bp_hardening_data, bp_hardening_data);

अटल अंतरभूत व्योम arm64_apply_bp_hardening(व्योम)
अणु
	काष्ठा bp_hardening_data *d;

	अगर (!cpus_have_स्थिर_cap(ARM64_SPECTRE_V2))
		वापस;

	d = this_cpu_ptr(&bp_hardening_data);
	अगर (d->fn)
		d->fn();
पूर्ण

क्रमागत mitigation_state arm64_get_spectre_v2_state(व्योम);
bool has_spectre_v2(स्थिर काष्ठा arm64_cpu_capabilities *cap, पूर्णांक scope);
व्योम spectre_v2_enable_mitigation(स्थिर काष्ठा arm64_cpu_capabilities *__unused);

bool has_spectre_v3a(स्थिर काष्ठा arm64_cpu_capabilities *cap, पूर्णांक scope);
व्योम spectre_v3a_enable_mitigation(स्थिर काष्ठा arm64_cpu_capabilities *__unused);

क्रमागत mitigation_state arm64_get_spectre_v4_state(व्योम);
bool has_spectre_v4(स्थिर काष्ठा arm64_cpu_capabilities *cap, पूर्णांक scope);
व्योम spectre_v4_enable_mitigation(स्थिर काष्ठा arm64_cpu_capabilities *__unused);
व्योम spectre_v4_enable_task_mitigation(काष्ठा task_काष्ठा *tsk);

क्रमागत mitigation_state arm64_get_meltकरोwn_state(व्योम);

#पूर्ण_अगर	/* __ASSEMBLY__ */
#पूर्ण_अगर	/* __ASM_SPECTRE_H */

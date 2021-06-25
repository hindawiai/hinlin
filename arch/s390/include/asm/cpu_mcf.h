<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Counter facility support definitions क्रम the Linux perf
 *
 * Copyright IBM Corp. 2019
 * Author(s): Hendrik Brueckner <brueckner@linux.ibm.com>
 */
#अगर_अघोषित _ASM_S390_CPU_MCF_H
#घोषणा _ASM_S390_CPU_MCF_H

#समावेश <linux/perf_event.h>
#समावेश <यंत्र/cpu_mf.h>

क्रमागत cpumf_ctr_set अणु
	CPUMF_CTR_SET_BASIC   = 0,    /* Basic Counter Set */
	CPUMF_CTR_SET_USER    = 1,    /* Problem-State Counter Set */
	CPUMF_CTR_SET_CRYPTO  = 2,    /* Crypto-Activity Counter Set */
	CPUMF_CTR_SET_EXT     = 3,    /* Extended Counter Set */
	CPUMF_CTR_SET_MT_DIAG = 4,    /* MT-diagnostic Counter Set */

	/* Maximum number of counter sets */
	CPUMF_CTR_SET_MAX,
पूर्ण;

#घोषणा CPUMF_LCCTL_ENABLE_SHIFT    16
#घोषणा CPUMF_LCCTL_ACTCTL_SHIFT     0
अटल स्थिर u64 cpumf_ctr_ctl[CPUMF_CTR_SET_MAX] = अणु
	[CPUMF_CTR_SET_BASIC]	= 0x02,
	[CPUMF_CTR_SET_USER]	= 0x04,
	[CPUMF_CTR_SET_CRYPTO]	= 0x08,
	[CPUMF_CTR_SET_EXT]	= 0x01,
	[CPUMF_CTR_SET_MT_DIAG] = 0x20,
पूर्ण;

अटल अंतरभूत व्योम ctr_set_enable(u64 *state, पूर्णांक ctr_set)
अणु
	*state |= cpumf_ctr_ctl[ctr_set] << CPUMF_LCCTL_ENABLE_SHIFT;
पूर्ण
अटल अंतरभूत व्योम ctr_set_disable(u64 *state, पूर्णांक ctr_set)
अणु
	*state &= ~(cpumf_ctr_ctl[ctr_set] << CPUMF_LCCTL_ENABLE_SHIFT);
पूर्ण
अटल अंतरभूत व्योम ctr_set_start(u64 *state, पूर्णांक ctr_set)
अणु
	*state |= cpumf_ctr_ctl[ctr_set] << CPUMF_LCCTL_ACTCTL_SHIFT;
पूर्ण
अटल अंतरभूत व्योम ctr_set_stop(u64 *state, पूर्णांक ctr_set)
अणु
	*state &= ~(cpumf_ctr_ctl[ctr_set] << CPUMF_LCCTL_ACTCTL_SHIFT);
पूर्ण

अटल अंतरभूत व्योम ctr_set_multiple_enable(u64 *state, u64 ctrsets)
अणु
	*state |= ctrsets << CPUMF_LCCTL_ENABLE_SHIFT;
पूर्ण

अटल अंतरभूत व्योम ctr_set_multiple_disable(u64 *state, u64 ctrsets)
अणु
	*state &= ~(ctrsets << CPUMF_LCCTL_ENABLE_SHIFT);
पूर्ण

अटल अंतरभूत व्योम ctr_set_multiple_start(u64 *state, u64 ctrsets)
अणु
	*state |= ctrsets << CPUMF_LCCTL_ACTCTL_SHIFT;
पूर्ण

अटल अंतरभूत व्योम ctr_set_multiple_stop(u64 *state, u64 ctrsets)
अणु
	*state &= ~(ctrsets << CPUMF_LCCTL_ACTCTL_SHIFT);
पूर्ण

अटल अंतरभूत पूर्णांक ctr_stccपंचांग(क्रमागत cpumf_ctr_set set, u64 range, u64 *dest)
अणु
	चयन (set) अणु
	हाल CPUMF_CTR_SET_BASIC:
		वापस stccपंचांग(BASIC, range, dest);
	हाल CPUMF_CTR_SET_USER:
		वापस stccपंचांग(PROBLEM_STATE, range, dest);
	हाल CPUMF_CTR_SET_CRYPTO:
		वापस stccपंचांग(CRYPTO_ACTIVITY, range, dest);
	हाल CPUMF_CTR_SET_EXT:
		वापस stccपंचांग(EXTENDED, range, dest);
	हाल CPUMF_CTR_SET_MT_DIAG:
		वापस stccपंचांग(MT_DIAG_CLEARING, range, dest);
	हाल CPUMF_CTR_SET_MAX:
		वापस 3;
	पूर्ण
	वापस 3;
पूर्ण

काष्ठा cpu_cf_events अणु
	काष्ठा cpumf_ctr_info	info;
	atomic_t		ctr_set[CPUMF_CTR_SET_MAX];
	atomic64_t		alert;
	u64			state, tx_state;
	अचिन्हित पूर्णांक		flags;
	अचिन्हित पूर्णांक		txn_flags;
पूर्ण;
DECLARE_PER_CPU(काष्ठा cpu_cf_events, cpu_cf_events);

bool kernel_cpumcf_avail(व्योम);
पूर्णांक __kernel_cpumcf_begin(व्योम);
अचिन्हित दीर्घ kernel_cpumcf_alert(पूर्णांक clear);
व्योम __kernel_cpumcf_end(व्योम);

अटल अंतरभूत पूर्णांक kernel_cpumcf_begin(व्योम)
अणु
	अगर (!cpum_cf_avail())
		वापस -ENODEV;

	preempt_disable();
	वापस __kernel_cpumcf_begin();
पूर्ण
अटल अंतरभूत व्योम kernel_cpumcf_end(व्योम)
अणु
	__kernel_cpumcf_end();
	preempt_enable();
पूर्ण

/* Return true अगर store counter set multiple inकाष्ठाion is available */
अटल अंतरभूत पूर्णांक stccm_avail(व्योम)
अणु
	वापस test_facility(142);
पूर्ण

माप_प्रकार cpum_cf_ctrset_size(क्रमागत cpumf_ctr_set ctrset,
			   काष्ठा cpumf_ctr_info *info);
#पूर्ण_अगर /* _ASM_S390_CPU_MCF_H */

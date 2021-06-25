<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
//
// Code shared between 32 and 64 bit

#समावेश <यंत्र/spec-ctrl.h>

व्योम __चयन_to_xtra(काष्ठा task_काष्ठा *prev_p, काष्ठा task_काष्ठा *next_p);

/*
 * This needs to be अंतरभूत to optimize क्रम the common हाल where no extra
 * work needs to be करोne.
 */
अटल अंतरभूत व्योम चयन_to_extra(काष्ठा task_काष्ठा *prev,
				   काष्ठा task_काष्ठा *next)
अणु
	अचिन्हित दीर्घ next_tअगर = task_thपढ़ो_info(next)->flags;
	अचिन्हित दीर्घ prev_tअगर = task_thपढ़ो_info(prev)->flags;

	अगर (IS_ENABLED(CONFIG_SMP)) अणु
		/*
		 * Aव्योम __चयन_to_xtra() invocation when conditional
		 * STIBP is disabled and the only dअगरferent bit is
		 * TIF_SPEC_IB. For CONFIG_SMP=n TIF_SPEC_IB is not
		 * in the TIF_WORK_CTXSW masks.
		 */
		अगर (!अटल_branch_likely(&चयन_to_cond_stibp)) अणु
			prev_tअगर &= ~_TIF_SPEC_IB;
			next_tअगर &= ~_TIF_SPEC_IB;
		पूर्ण
	पूर्ण

	/*
	 * __चयन_to_xtra() handles debug रेजिस्टरs, i/o biपंचांगaps,
	 * speculation mitigations etc.
	 */
	अगर (unlikely(next_tअगर & _TIF_WORK_CTXSW_NEXT ||
		     prev_tअगर & _TIF_WORK_CTXSW_PREV))
		__चयन_to_xtra(prev, next);
पूर्ण

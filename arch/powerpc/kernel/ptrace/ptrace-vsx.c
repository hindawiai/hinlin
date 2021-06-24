<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/regset.h>

#समावेश <यंत्र/चयन_to.h>

#समावेश "ptrace-decl.h"

/*
 * Regardless of transactions, 'fp_state' holds the current running
 * value of all FPR रेजिस्टरs and 'ckfp_state' holds the last checkpoपूर्णांकed
 * value of all FPR रेजिस्टरs क्रम the current transaction.
 *
 * Userspace पूर्णांकerface buffer layout:
 *
 * काष्ठा data अणु
 *	u64	fpr[32];
 *	u64	fpscr;
 * पूर्ण;
 */
पूर्णांक fpr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    काष्ठा membuf to)
अणु
	u64 buf[33];
	पूर्णांक i;

	flush_fp_to_thपढ़ो(target);

	/* copy to local buffer then ग_लिखो that out */
	क्रम (i = 0; i < 32 ; i++)
		buf[i] = target->thपढ़ो.TS_FPR(i);
	buf[32] = target->thपढ़ो.fp_state.fpscr;
	वापस membuf_ग_लिखो(&to, buf, 33 * माप(u64));
पूर्ण

/*
 * Regardless of transactions, 'fp_state' holds the current running
 * value of all FPR रेजिस्टरs and 'ckfp_state' holds the last checkpoपूर्णांकed
 * value of all FPR रेजिस्टरs क्रम the current transaction.
 *
 * Userspace पूर्णांकerface buffer layout:
 *
 * काष्ठा data अणु
 *	u64	fpr[32];
 *	u64	fpscr;
 * पूर्ण;
 *
 */
पूर्णांक fpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	u64 buf[33];
	पूर्णांक i;

	flush_fp_to_thपढ़ो(target);

	क्रम (i = 0; i < 32 ; i++)
		buf[i] = target->thपढ़ो.TS_FPR(i);
	buf[32] = target->thपढ़ो.fp_state.fpscr;

	/* copy to local buffer then ग_लिखो that out */
	i = user_regset_copyin(&pos, &count, &kbuf, &ubuf, buf, 0, -1);
	अगर (i)
		वापस i;

	क्रम (i = 0; i < 32 ; i++)
		target->thपढ़ो.TS_FPR(i) = buf[i];
	target->thपढ़ो.fp_state.fpscr = buf[32];
	वापस 0;
पूर्ण

/*
 * Currently to set and and get all the vsx state, you need to call
 * the fp and VMX calls as well.  This only get/sets the lower 32
 * 128bit VSX रेजिस्टरs.
 */

पूर्णांक vsr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	flush_vsx_to_thपढ़ो(target);
	वापस target->thपढ़ो.used_vsr ? regset->n : 0;
पूर्ण

/*
 * Regardless of transactions, 'fp_state' holds the current running
 * value of all FPR रेजिस्टरs and 'ckfp_state' holds the last
 * checkpoपूर्णांकed value of all FPR रेजिस्टरs क्रम the current
 * transaction.
 *
 * Userspace पूर्णांकerface buffer layout:
 *
 * काष्ठा data अणु
 *	u64	vsx[32];
 * पूर्ण;
 */
पूर्णांक vsr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    काष्ठा membuf to)
अणु
	u64 buf[32];
	पूर्णांक i;

	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);
	flush_vsx_to_thपढ़ो(target);

	क्रम (i = 0; i < 32 ; i++)
		buf[i] = target->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET];

	वापस membuf_ग_लिखो(&to, buf, 32 * माप(द्विगुन));
पूर्ण

/*
 * Regardless of transactions, 'fp_state' holds the current running
 * value of all FPR रेजिस्टरs and 'ckfp_state' holds the last
 * checkpoपूर्णांकed value of all FPR रेजिस्टरs क्रम the current
 * transaction.
 *
 * Userspace पूर्णांकerface buffer layout:
 *
 * काष्ठा data अणु
 *	u64	vsx[32];
 * पूर्ण;
 */
पूर्णांक vsr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	u64 buf[32];
	पूर्णांक ret, i;

	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);
	flush_vsx_to_thपढ़ो(target);

	क्रम (i = 0; i < 32 ; i++)
		buf[i] = target->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET];

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 buf, 0, 32 * माप(द्विगुन));
	अगर (!ret)
		क्रम (i = 0; i < 32 ; i++)
			target->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET] = buf[i];

	वापस ret;
पूर्ण

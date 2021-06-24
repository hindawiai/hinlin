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
#अगर_घोषित CONFIG_PPC_FPU_REGS
	BUILD_BUG_ON(दुरत्व(काष्ठा thपढ़ो_fp_state, fpscr) !=
		     दुरत्व(काष्ठा thपढ़ो_fp_state, fpr[32]));

	flush_fp_to_thपढ़ो(target);

	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.fp_state, 33 * माप(u64));
#अन्यथा
	वापस membuf_ग_लिखो(&to, &empty_zero_page, 33 * माप(u64));
#पूर्ण_अगर
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
#अगर_घोषित CONFIG_PPC_FPU_REGS
	BUILD_BUG_ON(दुरत्व(काष्ठा thपढ़ो_fp_state, fpscr) !=
		     दुरत्व(काष्ठा thपढ़ो_fp_state, fpr[32]));

	flush_fp_to_thपढ़ो(target);

	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &target->thपढ़ो.fp_state, 0, -1);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

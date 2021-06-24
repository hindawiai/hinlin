<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/regset.h>

#समावेश <यंत्र/चयन_to.h>

#समावेश "ptrace-decl.h"

/*
 * For get_evrregs/set_evrregs functions 'data' has the following layout:
 *
 * काष्ठा अणु
 *   u32 evr[32];
 *   u64 acc;
 *   u32 spefscr;
 * पूर्ण
 */

पूर्णांक evr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	flush_spe_to_thपढ़ो(target);
	वापस target->thपढ़ो.used_spe ? regset->n : 0;
पूर्ण

पूर्णांक evr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    काष्ठा membuf to)
अणु
	flush_spe_to_thपढ़ो(target);

	membuf_ग_लिखो(&to, &target->thपढ़ो.evr, माप(target->thपढ़ो.evr));

	BUILD_BUG_ON(दुरत्व(काष्ठा thपढ़ो_काष्ठा, acc) + माप(u64) !=
		     दुरत्व(काष्ठा thपढ़ो_काष्ठा, spefscr));

	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.acc,
				माप(u64) + माप(u32));
पूर्ण

पूर्णांक evr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	flush_spe_to_thपढ़ो(target);

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.evr,
				 0, माप(target->thपढ़ो.evr));

	BUILD_BUG_ON(दुरत्व(काष्ठा thपढ़ो_काष्ठा, acc) + माप(u64) !=
		     दुरत्व(काष्ठा thपढ़ो_काष्ठा, spefscr));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.acc,
					 माप(target->thपढ़ो.evr), -1);

	वापस ret;
पूर्ण

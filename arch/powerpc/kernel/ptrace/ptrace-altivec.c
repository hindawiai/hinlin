<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/regset.h>
#समावेश <linux/elf.h>

#समावेश <यंत्र/चयन_to.h>

#समावेश "ptrace-decl.h"

/*
 * Get/set all the altivec रेजिस्टरs vr0..vr31, vscr, vrsave, in one go.
 * The transfer totals 34 quadword.  Quadwords 0-31 contain the
 * corresponding vector रेजिस्टरs.  Quadword 32 contains the vscr as the
 * last word (offset 12) within that quadword.  Quadword 33 contains the
 * vrsave as the first word (offset 0) within the quadword.
 *
 * This definition of the VMX state is compatible with the current PPC32
 * ptrace पूर्णांकerface.  This allows संकेत handling and ptrace to use the
 * same काष्ठाures.  This also simplअगरies the implementation of a bi-arch
 * (combined (32- and 64-bit) gdb.
 */

पूर्णांक vr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	flush_altivec_to_thपढ़ो(target);
	वापस target->thपढ़ो.used_vr ? regset->n : 0;
पूर्ण

/*
 * Regardless of transactions, 'vr_state' holds the current running
 * value of all the VMX रेजिस्टरs and 'ckvr_state' holds the last
 * checkpoपूर्णांकed value of all the VMX रेजिस्टरs क्रम the current
 * transaction to fall back on in हाल it पातs.
 *
 * Userspace पूर्णांकerface buffer layout:
 *
 * काष्ठा data अणु
 *	vector128	vr[32];
 *	vector128	vscr;
 *	vector128	vrsave;
 * पूर्ण;
 */
पूर्णांक vr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	   काष्ठा membuf to)
अणु
	जोड़ अणु
		elf_vrreg_t reg;
		u32 word;
	पूर्ण vrsave;

	flush_altivec_to_thपढ़ो(target);

	BUILD_BUG_ON(दुरत्व(काष्ठा thपढ़ो_vr_state, vscr) !=
		     दुरत्व(काष्ठा thपढ़ो_vr_state, vr[32]));

	membuf_ग_लिखो(&to, &target->thपढ़ो.vr_state, 33 * माप(vector128));
	/*
	 * Copy out only the low-order word of vrsave.
	 */
	स_रखो(&vrsave, 0, माप(vrsave));
	vrsave.word = target->thपढ़ो.vrsave;
	वापस membuf_ग_लिखो(&to, &vrsave, माप(vrsave));
पूर्ण

/*
 * Regardless of transactions, 'vr_state' holds the current running
 * value of all the VMX रेजिस्टरs and 'ckvr_state' holds the last
 * checkpoपूर्णांकed value of all the VMX रेजिस्टरs क्रम the current
 * transaction to fall back on in हाल it पातs.
 *
 * Userspace पूर्णांकerface buffer layout:
 *
 * काष्ठा data अणु
 *	vector128	vr[32];
 *	vector128	vscr;
 *	vector128	vrsave;
 * पूर्ण;
 */
पूर्णांक vr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	flush_altivec_to_thपढ़ो(target);

	BUILD_BUG_ON(दुरत्व(काष्ठा thपढ़ो_vr_state, vscr) !=
		     दुरत्व(काष्ठा thपढ़ो_vr_state, vr[32]));

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.vr_state, 0,
				 33 * माप(vector128));
	अगर (!ret && count > 0) अणु
		/*
		 * We use only the first word of vrsave.
		 */
		पूर्णांक start, end;
		जोड़ अणु
			elf_vrreg_t reg;
			u32 word;
		पूर्ण vrsave;
		स_रखो(&vrsave, 0, माप(vrsave));

		vrsave.word = target->thपढ़ो.vrsave;

		start = 33 * माप(vector128);
		end = start + माप(vrsave);
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &vrsave,
					 start, end);
		अगर (!ret)
			target->thपढ़ो.vrsave = vrsave.word;
	पूर्ण

	वापस ret;
पूर्ण

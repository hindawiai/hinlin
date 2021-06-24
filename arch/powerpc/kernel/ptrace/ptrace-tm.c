<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/regset.h>

#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/पंचांग.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

#समावेश "ptrace-decl.h"

व्योम flush_पंचांगregs_to_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	/*
	 * If task is not current, it will have been flushed alपढ़ोy to
	 * it's thपढ़ो_काष्ठा during __चयन_to().
	 *
	 * A reclaim flushes ALL the state or अगर not in TM save TM SPRs
	 * in the appropriate thपढ़ो काष्ठाures from live.
	 */

	अगर (!cpu_has_feature(CPU_FTR_TM) || tsk != current)
		वापस;

	अगर (MSR_TM_SUSPENDED(mfmsr())) अणु
		पंचांग_reclaim_current(TM_CAUSE_SIGNAL);
	पूर्ण अन्यथा अणु
		पंचांग_enable();
		पंचांग_save_sprs(&tsk->thपढ़ो);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ get_user_ckpt_msr(काष्ठा task_काष्ठा *task)
अणु
	वापस task->thपढ़ो.ckpt_regs.msr | task->thपढ़ो.fpexc_mode;
पूर्ण

अटल पूर्णांक set_user_ckpt_msr(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ msr)
अणु
	task->thपढ़ो.ckpt_regs.msr &= ~MSR_DEBUGCHANGE;
	task->thपढ़ो.ckpt_regs.msr |= msr & MSR_DEBUGCHANGE;
	वापस 0;
पूर्ण

अटल पूर्णांक set_user_ckpt_trap(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ trap)
अणु
	set_trap(&task->thपढ़ो.ckpt_regs, trap);
	वापस 0;
पूर्ण

/**
 * पंचांग_cgpr_active - get active number of रेजिस्टरs in CGPR
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 *
 * This function checks क्रम the active number of available
 * regisers in transaction checkpoपूर्णांकed GPR category.
 */
पूर्णांक पंचांग_cgpr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस 0;

	वापस regset->n;
पूर्ण

/**
 * पंचांग_cgpr_get - get CGPR रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @to:		Destination of copy.
 *
 * This function माला_लो transaction checkpoपूर्णांकed GPR रेजिस्टरs.
 *
 * When the transaction is active, 'ckpt_regs' holds all the checkpoपूर्णांकed
 * GPR रेजिस्टर values क्रम the current transaction to fall back on अगर it
 * पातs in between. This function माला_लो those checkpoपूर्णांकed GPR रेजिस्टरs.
 * The userspace पूर्णांकerface buffer layout is as follows.
 *
 * काष्ठा data अणु
 *	काष्ठा pt_regs ckpt_regs;
 * पूर्ण;
 */
पूर्णांक पंचांग_cgpr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		काष्ठा membuf to)
अणु
	काष्ठा membuf to_msr = membuf_at(&to, दुरत्व(काष्ठा pt_regs, msr));
#अगर_घोषित CONFIG_PPC64
	काष्ठा membuf to_softe = membuf_at(&to, दुरत्व(काष्ठा pt_regs, softe));
#पूर्ण_अगर

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);

	membuf_ग_लिखो(&to, &target->thपढ़ो.ckpt_regs, माप(काष्ठा user_pt_regs));

	membuf_store(&to_msr, get_user_ckpt_msr(target));
#अगर_घोषित CONFIG_PPC64
	membuf_store(&to_softe, 0x1ul);
#पूर्ण_अगर
	वापस membuf_zero(&to, ELF_NGREG * माप(अचिन्हित दीर्घ) -
			माप(काष्ठा user_pt_regs));
पूर्ण

/*
 * पंचांग_cgpr_set - set the CGPR रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @pos:	The buffer position.
 * @count:	Number of bytes to copy.
 * @kbuf:	Kernel buffer to copy पूर्णांकo.
 * @ubuf:	User buffer to copy from.
 *
 * This function sets in transaction checkpoपूर्णांकed GPR रेजिस्टरs.
 *
 * When the transaction is active, 'ckpt_regs' holds the checkpoपूर्णांकed
 * GPR रेजिस्टर values क्रम the current transaction to fall back on अगर it
 * पातs in between. This function sets those checkpoपूर्णांकed GPR रेजिस्टरs.
 * The userspace पूर्णांकerface buffer layout is as follows.
 *
 * काष्ठा data अणु
 *	काष्ठा pt_regs ckpt_regs;
 * पूर्ण;
 */
पूर्णांक पंचांग_cgpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित दीर्घ reg;
	पूर्णांक ret;

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.ckpt_regs,
				 0, PT_MSR * माप(reg));

	अगर (!ret && count > 0) अणु
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &reg,
					 PT_MSR * माप(reg),
					 (PT_MSR + 1) * माप(reg));
		अगर (!ret)
			ret = set_user_ckpt_msr(target, reg);
	पूर्ण

	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, orig_gpr3) !=
		     दुरत्व(काष्ठा pt_regs, msr) + माप(दीर्घ));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.ckpt_regs.orig_gpr3,
					 PT_ORIG_R3 * माप(reg),
					 (PT_MAX_PUT_REG + 1) * माप(reg));

	अगर (PT_MAX_PUT_REG + 1 < PT_TRAP && !ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						(PT_MAX_PUT_REG + 1) * माप(reg),
						PT_TRAP * माप(reg));

	अगर (!ret && count > 0) अणु
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &reg,
					 PT_TRAP * माप(reg),
					 (PT_TRAP + 1) * माप(reg));
		अगर (!ret)
			ret = set_user_ckpt_trap(target, reg);
	पूर्ण

	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						(PT_TRAP + 1) * माप(reg), -1);

	वापस ret;
पूर्ण

/**
 * पंचांग_cfpr_active - get active number of रेजिस्टरs in CFPR
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 *
 * This function checks क्रम the active number of available
 * regisers in transaction checkpoपूर्णांकed FPR category.
 */
पूर्णांक पंचांग_cfpr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस 0;

	वापस regset->n;
पूर्ण

/**
 * पंचांग_cfpr_get - get CFPR रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @to:		Destination of copy.
 *
 * This function माला_लो in transaction checkpoपूर्णांकed FPR रेजिस्टरs.
 *
 * When the transaction is active 'ckfp_state' holds the checkpoपूर्णांकed
 * values क्रम the current transaction to fall back on अगर it पातs
 * in between. This function माला_लो those checkpoपूर्णांकed FPR रेजिस्टरs.
 * The userspace पूर्णांकerface buffer layout is as follows.
 *
 * काष्ठा data अणु
 *	u64	fpr[32];
 *	u64	fpscr;
 *पूर्ण;
 */
पूर्णांक पंचांग_cfpr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		काष्ठा membuf to)
अणु
	u64 buf[33];
	पूर्णांक i;

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);

	/* copy to local buffer then ग_लिखो that out */
	क्रम (i = 0; i < 32 ; i++)
		buf[i] = target->thपढ़ो.TS_CKFPR(i);
	buf[32] = target->thपढ़ो.ckfp_state.fpscr;
	वापस membuf_ग_लिखो(&to, buf, माप(buf));
पूर्ण

/**
 * पंचांग_cfpr_set - set CFPR रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @pos:	The buffer position.
 * @count:	Number of bytes to copy.
 * @kbuf:	Kernel buffer to copy पूर्णांकo.
 * @ubuf:	User buffer to copy from.
 *
 * This function sets in transaction checkpoपूर्णांकed FPR रेजिस्टरs.
 *
 * When the transaction is active 'ckfp_state' holds the checkpoपूर्णांकed
 * FPR रेजिस्टर values क्रम the current transaction to fall back on
 * अगर it पातs in between. This function sets these checkpoपूर्णांकed
 * FPR रेजिस्टरs. The userspace पूर्णांकerface buffer layout is as follows.
 *
 * काष्ठा data अणु
 *	u64	fpr[32];
 *	u64	fpscr;
 *पूर्ण;
 */
पूर्णांक पंचांग_cfpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	u64 buf[33];
	पूर्णांक i;

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);

	क्रम (i = 0; i < 32; i++)
		buf[i] = target->thपढ़ो.TS_CKFPR(i);
	buf[32] = target->thपढ़ो.ckfp_state.fpscr;

	/* copy to local buffer then ग_लिखो that out */
	i = user_regset_copyin(&pos, &count, &kbuf, &ubuf, buf, 0, -1);
	अगर (i)
		वापस i;
	क्रम (i = 0; i < 32 ; i++)
		target->thपढ़ो.TS_CKFPR(i) = buf[i];
	target->thपढ़ो.ckfp_state.fpscr = buf[32];
	वापस 0;
पूर्ण

/**
 * पंचांग_cvmx_active - get active number of रेजिस्टरs in CVMX
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 *
 * This function checks क्रम the active number of available
 * regisers in checkpoपूर्णांकed VMX category.
 */
पूर्णांक पंचांग_cvmx_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस 0;

	वापस regset->n;
पूर्ण

/**
 * पंचांग_cvmx_get - get CMVX रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @to:		Destination of copy.
 *
 * This function माला_लो in transaction checkpoपूर्णांकed VMX रेजिस्टरs.
 *
 * When the transaction is active 'ckvr_state' and 'ckvrsave' hold
 * the checkpoपूर्णांकed values क्रम the current transaction to fall
 * back on अगर it पातs in between. The userspace पूर्णांकerface buffer
 * layout is as follows.
 *
 * काष्ठा data अणु
 *	vector128	vr[32];
 *	vector128	vscr;
 *	vector128	vrsave;
 *पूर्ण;
 */
पूर्णांक पंचांग_cvmx_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		काष्ठा membuf to)
अणु
	जोड़ अणु
		elf_vrreg_t reg;
		u32 word;
	पूर्ण vrsave;
	BUILD_BUG_ON(TVSO(vscr) != TVSO(vr[32]));

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	/* Flush the state */
	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);

	membuf_ग_लिखो(&to, &target->thपढ़ो.ckvr_state, 33 * माप(vector128));
	/*
	 * Copy out only the low-order word of vrsave.
	 */
	स_रखो(&vrsave, 0, माप(vrsave));
	vrsave.word = target->thपढ़ो.ckvrsave;
	वापस membuf_ग_लिखो(&to, &vrsave, माप(vrsave));
पूर्ण

/**
 * पंचांग_cvmx_set - set CMVX रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @pos:	The buffer position.
 * @count:	Number of bytes to copy.
 * @kbuf:	Kernel buffer to copy पूर्णांकo.
 * @ubuf:	User buffer to copy from.
 *
 * This function sets in transaction checkpoपूर्णांकed VMX रेजिस्टरs.
 *
 * When the transaction is active 'ckvr_state' and 'ckvrsave' hold
 * the checkpoपूर्णांकed values क्रम the current transaction to fall
 * back on अगर it पातs in between. The userspace पूर्णांकerface buffer
 * layout is as follows.
 *
 * काष्ठा data अणु
 *	vector128	vr[32];
 *	vector128	vscr;
 *	vector128	vrsave;
 *पूर्ण;
 */
पूर्णांक पंचांग_cvmx_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(TVSO(vscr) != TVSO(vr[32]));

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &target->thपढ़ो.ckvr_state,
				 0, 33 * माप(vector128));
	अगर (!ret && count > 0) अणु
		/*
		 * We use only the low-order word of vrsave.
		 */
		जोड़ अणु
			elf_vrreg_t reg;
			u32 word;
		पूर्ण vrsave;
		स_रखो(&vrsave, 0, माप(vrsave));
		vrsave.word = target->thपढ़ो.ckvrsave;
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &vrsave,
					 33 * माप(vector128), -1);
		अगर (!ret)
			target->thपढ़ो.ckvrsave = vrsave.word;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * पंचांग_cvsx_active - get active number of रेजिस्टरs in CVSX
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 *
 * This function checks क्रम the active number of available
 * regisers in transaction checkpoपूर्णांकed VSX category.
 */
पूर्णांक पंचांग_cvsx_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस 0;

	flush_vsx_to_thपढ़ो(target);
	वापस target->thपढ़ो.used_vsr ? regset->n : 0;
पूर्ण

/**
 * पंचांग_cvsx_get - get CVSX रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @to:		Destination of copy.
 *
 * This function माला_लो in transaction checkpoपूर्णांकed VSX रेजिस्टरs.
 *
 * When the transaction is active 'ckfp_state' holds the checkpoपूर्णांकed
 * values क्रम the current transaction to fall back on अगर it पातs
 * in between. This function माला_लो those checkpoपूर्णांकed VSX रेजिस्टरs.
 * The userspace पूर्णांकerface buffer layout is as follows.
 *
 * काष्ठा data अणु
 *	u64	vsx[32];
 *पूर्ण;
 */
पूर्णांक पंचांग_cvsx_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		काष्ठा membuf to)
अणु
	u64 buf[32];
	पूर्णांक i;

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	/* Flush the state */
	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);
	flush_vsx_to_thपढ़ो(target);

	क्रम (i = 0; i < 32 ; i++)
		buf[i] = target->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET];
	वापस membuf_ग_लिखो(&to, buf, 32 * माप(द्विगुन));
पूर्ण

/**
 * पंचांग_cvsx_set - set CFPR रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @pos:	The buffer position.
 * @count:	Number of bytes to copy.
 * @kbuf:	Kernel buffer to copy पूर्णांकo.
 * @ubuf:	User buffer to copy from.
 *
 * This function sets in transaction checkpoपूर्णांकed VSX रेजिस्टरs.
 *
 * When the transaction is active 'ckfp_state' holds the checkpoपूर्णांकed
 * VSX रेजिस्टर values क्रम the current transaction to fall back on
 * अगर it पातs in between. This function sets these checkpoपूर्णांकed
 * FPR रेजिस्टरs. The userspace पूर्णांकerface buffer layout is as follows.
 *
 * काष्ठा data अणु
 *	u64	vsx[32];
 *पूर्ण;
 */
पूर्णांक पंचांग_cvsx_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	u64 buf[32];
	पूर्णांक ret, i;

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	/* Flush the state */
	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);
	flush_vsx_to_thपढ़ो(target);

	क्रम (i = 0; i < 32 ; i++)
		buf[i] = target->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET];

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 buf, 0, 32 * माप(द्विगुन));
	अगर (!ret)
		क्रम (i = 0; i < 32 ; i++)
			target->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET] = buf[i];

	वापस ret;
पूर्ण

/**
 * पंचांग_spr_active - get active number of रेजिस्टरs in TM SPR
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 *
 * This function checks the active number of available
 * regisers in the transactional memory SPR category.
 */
पूर्णांक पंचांग_spr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	वापस regset->n;
पूर्ण

/**
 * पंचांग_spr_get - get the TM related SPR रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @to:		Destination of copy.
 *
 * This function माला_लो transactional memory related SPR रेजिस्टरs.
 * The userspace पूर्णांकerface buffer layout is as follows.
 *
 * काष्ठा अणु
 *	u64		पंचांग_tfhar;
 *	u64		पंचांग_texasr;
 *	u64		पंचांग_tfiar;
 * पूर्ण;
 */
पूर्णांक पंचांग_spr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       काष्ठा membuf to)
अणु
	/* Build tests */
	BUILD_BUG_ON(TSO(पंचांग_tfhar) + माप(u64) != TSO(पंचांग_texasr));
	BUILD_BUG_ON(TSO(पंचांग_texasr) + माप(u64) != TSO(पंचांग_tfiar));
	BUILD_BUG_ON(TSO(पंचांग_tfiar) + माप(u64) != TSO(ckpt_regs));

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	/* Flush the states */
	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);

	/* TFHAR रेजिस्टर */
	membuf_ग_लिखो(&to, &target->thपढ़ो.पंचांग_tfhar, माप(u64));
	/* TEXASR रेजिस्टर */
	membuf_ग_लिखो(&to, &target->thपढ़ो.पंचांग_texasr, माप(u64));
	/* TFIAR रेजिस्टर */
	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.पंचांग_tfiar, माप(u64));
पूर्ण

/**
 * पंचांग_spr_set - set the TM related SPR रेजिस्टरs
 * @target:	The target task.
 * @regset:	The user regset काष्ठाure.
 * @pos:	The buffer position.
 * @count:	Number of bytes to copy.
 * @kbuf:	Kernel buffer to copy पूर्णांकo.
 * @ubuf:	User buffer to copy from.
 *
 * This function sets transactional memory related SPR रेजिस्टरs.
 * The userspace पूर्णांकerface buffer layout is as follows.
 *
 * काष्ठा अणु
 *	u64		पंचांग_tfhar;
 *	u64		पंचांग_texasr;
 *	u64		पंचांग_tfiar;
 * पूर्ण;
 */
पूर्णांक पंचांग_spr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	/* Build tests */
	BUILD_BUG_ON(TSO(पंचांग_tfhar) + माप(u64) != TSO(पंचांग_texasr));
	BUILD_BUG_ON(TSO(पंचांग_texasr) + माप(u64) != TSO(पंचांग_tfiar));
	BUILD_BUG_ON(TSO(पंचांग_tfiar) + माप(u64) != TSO(ckpt_regs));

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	/* Flush the states */
	flush_पंचांगregs_to_thपढ़ो(target);
	flush_fp_to_thपढ़ो(target);
	flush_altivec_to_thपढ़ो(target);

	/* TFHAR रेजिस्टर */
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.पंचांग_tfhar, 0, माप(u64));

	/* TEXASR रेजिस्टर */
	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.पंचांग_texasr, माप(u64),
					 2 * माप(u64));

	/* TFIAR रेजिस्टर */
	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.पंचांग_tfiar,
					 2 * माप(u64), 3 * माप(u64));
	वापस ret;
पूर्ण

पूर्णांक पंचांग_tar_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस regset->n;

	वापस 0;
पूर्ण

पूर्णांक पंचांग_tar_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       काष्ठा membuf to)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.पंचांग_tar, माप(u64));
पूर्ण

पूर्णांक पंचांग_tar_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.पंचांग_tar, 0, माप(u64));
	वापस ret;
पूर्ण

पूर्णांक पंचांग_ppr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस regset->n;

	वापस 0;
पूर्ण


पूर्णांक पंचांग_ppr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       काष्ठा membuf to)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.पंचांग_ppr, माप(u64));
पूर्ण

पूर्णांक पंचांग_ppr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.पंचांग_ppr, 0, माप(u64));
	वापस ret;
पूर्ण

पूर्णांक पंचांग_dscr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस regset->n;

	वापस 0;
पूर्ण

पूर्णांक पंचांग_dscr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		काष्ठा membuf to)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.पंचांग_dscr, माप(u64));
पूर्ण

पूर्णांक पंचांग_dscr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस -ENODEV;

	अगर (!MSR_TM_ACTIVE(target->thपढ़ो.regs->msr))
		वापस -ENODATA;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.पंचांग_dscr, 0, माप(u64));
	वापस ret;
पूर्ण

पूर्णांक पंचांग_cgpr32_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		  काष्ठा membuf to)
अणु
	gpr32_get_common(target, regset, to,
				&target->thपढ़ो.ckpt_regs.gpr[0]);
	वापस membuf_zero(&to, ELF_NGREG * माप(u32));
पूर्ण

पूर्णांक पंचांग_cgpr32_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	वापस gpr32_set_common(target, regset, pos, count, kbuf, ubuf,
				&target->thपढ़ो.ckpt_regs.gpr[0]);
पूर्ण

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

/*
 * Set of msr bits that gdb can change on behalf of a process.
 */
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
#घोषणा MSR_DEBUGCHANGE	0
#अन्यथा
#घोषणा MSR_DEBUGCHANGE	(MSR_SE | MSR_BE)
#पूर्ण_अगर

/*
 * Max रेजिस्टर ग_लिखोable via put_reg
 */
#अगर_घोषित CONFIG_PPC32
#घोषणा PT_MAX_PUT_REG	PT_MQ
#अन्यथा
#घोषणा PT_MAX_PUT_REG	PT_CCR
#पूर्ण_अगर

#घोषणा TVSO(f)	(दुरत्व(काष्ठा thपढ़ो_vr_state, f))
#घोषणा TFSO(f)	(दुरत्व(काष्ठा thपढ़ो_fp_state, f))
#घोषणा TSO(f)	(दुरत्व(काष्ठा thपढ़ो_काष्ठा, f))

/*
 * These are our native regset flavors.
 */
क्रमागत घातerpc_regset अणु
	REGSET_GPR,
	REGSET_FPR,
#अगर_घोषित CONFIG_ALTIVEC
	REGSET_VMX,
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	REGSET_VSX,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPE
	REGSET_SPE,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	REGSET_TM_CGPR,		/* TM checkpoपूर्णांकed GPR रेजिस्टरs */
	REGSET_TM_CFPR,		/* TM checkpoपूर्णांकed FPR रेजिस्टरs */
	REGSET_TM_CVMX,		/* TM checkpoपूर्णांकed VMX रेजिस्टरs */
	REGSET_TM_CVSX,		/* TM checkpoपूर्णांकed VSX रेजिस्टरs */
	REGSET_TM_SPR,		/* TM specअगरic SPR रेजिस्टरs */
	REGSET_TM_CTAR,		/* TM checkpoपूर्णांकed TAR रेजिस्टर */
	REGSET_TM_CPPR,		/* TM checkpoपूर्णांकed PPR रेजिस्टर */
	REGSET_TM_CDSCR,	/* TM checkpoपूर्णांकed DSCR रेजिस्टर */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
	REGSET_PPR,		/* PPR रेजिस्टर */
	REGSET_DSCR,		/* DSCR रेजिस्टर */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	REGSET_TAR,		/* TAR रेजिस्टर */
	REGSET_EBB,		/* EBB रेजिस्टरs */
	REGSET_PMR,		/* Perक्रमmance Monitor Registers */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_MEM_KEYS
	REGSET_PKEY,		/* AMR रेजिस्टर */
#पूर्ण_अगर
पूर्ण;

/* ptrace-(no)vsx */

user_regset_get2_fn fpr_get;
पूर्णांक fpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);

/* ptrace-vsx */

पूर्णांक vsr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn vsr_get;
पूर्णांक vsr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);

/* ptrace-altivec */

पूर्णांक vr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn vr_get;
पूर्णांक vr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);

/* ptrace-spe */

पूर्णांक evr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn evr_get;
पूर्णांक evr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);

/* ptrace */

पूर्णांक gpr32_get_common(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to,
		     अचिन्हित दीर्घ *regs);
पूर्णांक gpr32_set_common(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf,
		     अचिन्हित दीर्घ *regs);

/* ptrace-पंचांग */

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
व्योम flush_पंचांगregs_to_thपढ़ो(काष्ठा task_काष्ठा *tsk);
#अन्यथा
अटल अंतरभूत व्योम flush_पंचांगregs_to_thपढ़ो(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक पंचांग_cgpr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn पंचांग_cgpr_get;
पूर्णांक पंचांग_cgpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);
पूर्णांक पंचांग_cfpr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn पंचांग_cfpr_get;
पूर्णांक पंचांग_cfpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);
पूर्णांक पंचांग_cvmx_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn पंचांग_cvmx_get;
पूर्णांक पंचांग_cvmx_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);
पूर्णांक पंचांग_cvsx_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn पंचांग_cvsx_get;
पूर्णांक पंचांग_cvsx_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);
पूर्णांक पंचांग_spr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn पंचांग_spr_get;
पूर्णांक पंचांग_spr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);
पूर्णांक पंचांग_tar_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn पंचांग_tar_get;
पूर्णांक पंचांग_tar_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);
पूर्णांक पंचांग_ppr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn पंचांग_ppr_get;
पूर्णांक पंचांग_ppr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);
पूर्णांक पंचांग_dscr_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset);
user_regset_get2_fn पंचांग_dscr_get;
पूर्णांक पंचांग_dscr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);
user_regset_get2_fn पंचांग_cgpr32_get;
पूर्णांक पंचांग_cgpr32_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);

/* ptrace-view */

पूर्णांक ptrace_get_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno, अचिन्हित दीर्घ *data);
पूर्णांक ptrace_put_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno, अचिन्हित दीर्घ data);

बाह्य स्थिर काष्ठा user_regset_view user_ppc_native_view;

/* ptrace-fpu */
पूर्णांक ptrace_get_fpr(काष्ठा task_काष्ठा *child, पूर्णांक index, अचिन्हित दीर्घ *data);
पूर्णांक ptrace_put_fpr(काष्ठा task_काष्ठा *child, पूर्णांक index, अचिन्हित दीर्घ data);

/* ptrace-(no)adv */
व्योम ppc_gethwdinfo(काष्ठा ppc_debug_info *dbginfo);
पूर्णांक ptrace_get_debugreg(काष्ठा task_काष्ठा *child, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ __user *datalp);
पूर्णांक ptrace_set_debugreg(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data);
दीर्घ ppc_set_hwdebug(काष्ठा task_काष्ठा *child, काष्ठा ppc_hw_अवरोधpoपूर्णांक *bp_info);
दीर्घ ppc_del_hwdebug(काष्ठा task_काष्ठा *child, दीर्घ data);

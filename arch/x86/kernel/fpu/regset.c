<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPU रेजिस्टर's regset असलtraction, क्रम ptrace, core dumps, etc.
 */
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/fpu/संकेत.स>
#समावेश <यंत्र/fpu/regset.h>
#समावेश <यंत्र/fpu/xstate.h>
#समावेश <linux/sched/task_stack.h>

/*
 * The xstateregs_active() routine is the same as the regset_fpregs_active() routine,
 * as the "regset->n" क्रम the xstate regset will be updated based on the feature
 * capabilities supported by the xsave.
 */
पूर्णांक regset_fpregs_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	वापस regset->n;
पूर्ण

पूर्णांक regset_xregset_fpregs_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (boot_cpu_has(X86_FEATURE_FXSR))
		वापस regset->n;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक xfpregs_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		काष्ठा membuf to)
अणु
	काष्ठा fpu *fpu = &target->thपढ़ो.fpu;

	अगर (!boot_cpu_has(X86_FEATURE_FXSR))
		वापस -ENODEV;

	fpu__prepare_पढ़ो(fpu);
	fpstate_sanitize_xstate(fpu);

	वापस membuf_ग_लिखो(&to, &fpu->state.fxsave, माप(काष्ठा fxregs_state));
पूर्ण

पूर्णांक xfpregs_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा fpu *fpu = &target->thपढ़ो.fpu;
	पूर्णांक ret;

	अगर (!boot_cpu_has(X86_FEATURE_FXSR))
		वापस -ENODEV;

	fpu__prepare_ग_लिखो(fpu);
	fpstate_sanitize_xstate(fpu);

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &fpu->state.fxsave, 0, -1);

	/*
	 * mxcsr reserved bits must be masked to zero क्रम security reasons.
	 */
	fpu->state.fxsave.mxcsr &= mxcsr_feature_mask;

	/*
	 * update the header bits in the xsave header, indicating the
	 * presence of FP and SSE state.
	 */
	अगर (boot_cpu_has(X86_FEATURE_XSAVE))
		fpu->state.xsave.header.xfeatures |= XFEATURE_MASK_FPSSE;

	वापस ret;
पूर्ण

पूर्णांक xstateregs_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		काष्ठा membuf to)
अणु
	काष्ठा fpu *fpu = &target->thपढ़ो.fpu;
	काष्ठा xregs_state *xsave;

	अगर (!boot_cpu_has(X86_FEATURE_XSAVE))
		वापस -ENODEV;

	xsave = &fpu->state.xsave;

	fpu__prepare_पढ़ो(fpu);

	अगर (using_compacted_क्रमmat()) अणु
		copy_xstate_to_kernel(to, xsave);
		वापस 0;
	पूर्ण अन्यथा अणु
		fpstate_sanitize_xstate(fpu);
		/*
		 * Copy the 48 bytes defined by the software पूर्णांकo the xsave
		 * area in the thपढ़ो काष्ठा, so that we can copy the whole
		 * area to user using one user_regset_copyout().
		 */
		स_नकल(&xsave->i387.sw_reserved, xstate_fx_sw_bytes, माप(xstate_fx_sw_bytes));

		/*
		 * Copy the xstate memory layout.
		 */
		वापस membuf_ग_लिखो(&to, xsave, fpu_user_xstate_size);
	पूर्ण
पूर्ण

पूर्णांक xstateregs_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा fpu *fpu = &target->thपढ़ो.fpu;
	काष्ठा xregs_state *xsave;
	पूर्णांक ret;

	अगर (!boot_cpu_has(X86_FEATURE_XSAVE))
		वापस -ENODEV;

	/*
	 * A whole standard-क्रमmat XSAVE buffer is needed:
	 */
	अगर ((pos != 0) || (count < fpu_user_xstate_size))
		वापस -EFAULT;

	xsave = &fpu->state.xsave;

	fpu__prepare_ग_लिखो(fpu);

	अगर (using_compacted_क्रमmat()) अणु
		अगर (kbuf)
			ret = copy_kernel_to_xstate(xsave, kbuf);
		अन्यथा
			ret = copy_user_to_xstate(xsave, ubuf);
	पूर्ण अन्यथा अणु
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, xsave, 0, -1);
		अगर (!ret)
			ret = validate_user_xstate_header(&xsave->header);
	पूर्ण

	/*
	 * mxcsr reserved bits must be masked to zero क्रम security reasons.
	 */
	xsave->i387.mxcsr &= mxcsr_feature_mask;

	/*
	 * In हाल of failure, mark all states as init:
	 */
	अगर (ret)
		fpstate_init(&fpu->state);

	वापस ret;
पूर्ण

#अगर defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION

/*
 * FPU tag word conversions.
 */

अटल अंतरभूत अचिन्हित लघु twd_i387_to_fxsr(अचिन्हित लघु twd)
अणु
	अचिन्हित पूर्णांक पंचांगp; /* to aव्योम 16 bit prefixes in the code */

	/* Transक्रमm each pair of bits पूर्णांकo 01 (valid) or 00 (empty) */
	पंचांगp = ~twd;
	पंचांगp = (पंचांगp | (पंचांगp>>1)) & 0x5555; /* 0V0V0V0V0V0V0V0V */
	/* and move the valid bits to the lower byte. */
	पंचांगp = (पंचांगp | (पंचांगp >> 1)) & 0x3333; /* 00VV00VV00VV00VV */
	पंचांगp = (पंचांगp | (पंचांगp >> 2)) & 0x0f0f; /* 0000VVVV0000VVVV */
	पंचांगp = (पंचांगp | (पंचांगp >> 4)) & 0x00ff; /* 00000000VVVVVVVV */

	वापस पंचांगp;
पूर्ण

#घोषणा FPREG_ADDR(f, n)	((व्योम *)&(f)->st_space + (n) * 16)
#घोषणा FP_EXP_TAG_VALID	0
#घोषणा FP_EXP_TAG_ZERO		1
#घोषणा FP_EXP_TAG_SPECIAL	2
#घोषणा FP_EXP_TAG_EMPTY	3

अटल अंतरभूत u32 twd_fxsr_to_i387(काष्ठा fxregs_state *fxsave)
अणु
	काष्ठा _fpxreg *st;
	u32 tos = (fxsave->swd >> 11) & 7;
	u32 twd = (अचिन्हित दीर्घ) fxsave->twd;
	u32 tag;
	u32 ret = 0xffff0000u;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++, twd >>= 1) अणु
		अगर (twd & 0x1) अणु
			st = FPREG_ADDR(fxsave, (i - tos) & 7);

			चयन (st->exponent & 0x7fff) अणु
			हाल 0x7fff:
				tag = FP_EXP_TAG_SPECIAL;
				अवरोध;
			हाल 0x0000:
				अगर (!st->signअगरicand[0] &&
				    !st->signअगरicand[1] &&
				    !st->signअगरicand[2] &&
				    !st->signअगरicand[3])
					tag = FP_EXP_TAG_ZERO;
				अन्यथा
					tag = FP_EXP_TAG_SPECIAL;
				अवरोध;
			शेष:
				अगर (st->signअगरicand[3] & 0x8000)
					tag = FP_EXP_TAG_VALID;
				अन्यथा
					tag = FP_EXP_TAG_SPECIAL;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			tag = FP_EXP_TAG_EMPTY;
		पूर्ण
		ret |= tag << (2 * i);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * FXSR भग्नing poपूर्णांक environment conversions.
 */

व्योम
convert_from_fxsr(काष्ठा user_i387_ia32_काष्ठा *env, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा fxregs_state *fxsave = &tsk->thपढ़ो.fpu.state.fxsave;
	काष्ठा _fpreg *to = (काष्ठा _fpreg *) &env->st_space[0];
	काष्ठा _fpxreg *from = (काष्ठा _fpxreg *) &fxsave->st_space[0];
	पूर्णांक i;

	env->cwd = fxsave->cwd | 0xffff0000u;
	env->swd = fxsave->swd | 0xffff0000u;
	env->twd = twd_fxsr_to_i387(fxsave);

#अगर_घोषित CONFIG_X86_64
	env->fip = fxsave->rip;
	env->foo = fxsave->rdp;
	/*
	 * should be actually ds/cs at fpu exception समय, but
	 * that inक्रमmation is not available in 64bit mode.
	 */
	env->fcs = task_pt_regs(tsk)->cs;
	अगर (tsk == current) अणु
		savesegment(ds, env->fos);
	पूर्ण अन्यथा अणु
		env->fos = tsk->thपढ़ो.ds;
	पूर्ण
	env->fos |= 0xffff0000;
#अन्यथा
	env->fip = fxsave->fip;
	env->fcs = (u16) fxsave->fcs | ((u32) fxsave->fop << 16);
	env->foo = fxsave->foo;
	env->fos = fxsave->fos;
#पूर्ण_अगर

	क्रम (i = 0; i < 8; ++i)
		स_नकल(&to[i], &from[i], माप(to[0]));
पूर्ण

व्योम convert_to_fxsr(काष्ठा fxregs_state *fxsave,
		     स्थिर काष्ठा user_i387_ia32_काष्ठा *env)

अणु
	काष्ठा _fpreg *from = (काष्ठा _fpreg *) &env->st_space[0];
	काष्ठा _fpxreg *to = (काष्ठा _fpxreg *) &fxsave->st_space[0];
	पूर्णांक i;

	fxsave->cwd = env->cwd;
	fxsave->swd = env->swd;
	fxsave->twd = twd_i387_to_fxsr(env->twd);
	fxsave->fop = (u16) ((u32) env->fcs >> 16);
#अगर_घोषित CONFIG_X86_64
	fxsave->rip = env->fip;
	fxsave->rdp = env->foo;
	/* cs and ds ignored */
#अन्यथा
	fxsave->fip = env->fip;
	fxsave->fcs = (env->fcs & 0xffff);
	fxsave->foo = env->foo;
	fxsave->fos = env->fos;
#पूर्ण_अगर

	क्रम (i = 0; i < 8; ++i)
		स_नकल(&to[i], &from[i], माप(from[0]));
पूर्ण

पूर्णांक fpregs_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       काष्ठा membuf to)
अणु
	काष्ठा fpu *fpu = &target->thपढ़ो.fpu;
	काष्ठा user_i387_ia32_काष्ठा env;

	fpu__prepare_पढ़ो(fpu);

	अगर (!boot_cpu_has(X86_FEATURE_FPU))
		वापस fpregs_soft_get(target, regset, to);

	अगर (!boot_cpu_has(X86_FEATURE_FXSR)) अणु
		वापस membuf_ग_लिखो(&to, &fpu->state.fsave,
				    माप(काष्ठा fregs_state));
	पूर्ण

	fpstate_sanitize_xstate(fpu);

	अगर (to.left == माप(env)) अणु
		convert_from_fxsr(to.p, target);
		वापस 0;
	पूर्ण

	convert_from_fxsr(&env, target);
	वापस membuf_ग_लिखो(&to, &env, माप(env));
पूर्ण

पूर्णांक fpregs_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा fpu *fpu = &target->thपढ़ो.fpu;
	काष्ठा user_i387_ia32_काष्ठा env;
	पूर्णांक ret;

	fpu__prepare_ग_लिखो(fpu);
	fpstate_sanitize_xstate(fpu);

	अगर (!boot_cpu_has(X86_FEATURE_FPU))
		वापस fpregs_soft_set(target, regset, pos, count, kbuf, ubuf);

	अगर (!boot_cpu_has(X86_FEATURE_FXSR))
		वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					  &fpu->state.fsave, 0,
					  -1);

	अगर (pos > 0 || count < माप(env))
		convert_from_fxsr(&env, target);

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &env, 0, -1);
	अगर (!ret)
		convert_to_fxsr(&target->thपढ़ो.fpu.state.fxsave, &env);

	/*
	 * update the header bit in the xsave header, indicating the
	 * presence of FP.
	 */
	अगर (boot_cpu_has(X86_FEATURE_XSAVE))
		fpu->state.xsave.header.xfeatures |= XFEATURE_MASK_FP;
	वापस ret;
पूर्ण

#पूर्ण_अगर	/* CONFIG_X86_32 || CONFIG_IA32_EMULATION */

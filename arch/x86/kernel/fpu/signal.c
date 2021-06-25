<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPU संकेत frame handling routines.
 */

#समावेश <linux/compat.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/fpu/संकेत.स>
#समावेश <यंत्र/fpu/regset.h>
#समावेश <यंत्र/fpu/xstate.h>

#समावेश <यंत्र/sigframe.h>
#समावेश <यंत्र/trace/fpu.h>

अटल काष्ठा _fpx_sw_bytes fx_sw_reserved, fx_sw_reserved_ia32;

/*
 * Check क्रम the presence of extended state inक्रमmation in the
 * user fpstate poपूर्णांकer in the sigcontext.
 */
अटल अंतरभूत पूर्णांक check_क्रम_xstate(काष्ठा fxregs_state __user *buf,
				   व्योम __user *fpstate,
				   काष्ठा _fpx_sw_bytes *fx_sw)
अणु
	पूर्णांक min_xstate_size = माप(काष्ठा fxregs_state) +
			      माप(काष्ठा xstate_header);
	अचिन्हित पूर्णांक magic2;

	अगर (__copy_from_user(fx_sw, &buf->sw_reserved[0], माप(*fx_sw)))
		वापस -1;

	/* Check क्रम the first magic field and other error scenarios. */
	अगर (fx_sw->magic1 != FP_XSTATE_MAGIC1 ||
	    fx_sw->xstate_size < min_xstate_size ||
	    fx_sw->xstate_size > fpu_user_xstate_size ||
	    fx_sw->xstate_size > fx_sw->extended_size)
		वापस -1;

	/*
	 * Check क्रम the presence of second magic word at the end of memory
	 * layout. This detects the हाल where the user just copied the legacy
	 * fpstate layout with out copying the extended state inक्रमmation
	 * in the memory layout.
	 */
	अगर (__get_user(magic2, (__u32 __user *)(fpstate + fx_sw->xstate_size))
	    || magic2 != FP_XSTATE_MAGIC2)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * Signal frame handlers.
 */
अटल अंतरभूत पूर्णांक save_fsave_header(काष्ठा task_काष्ठा *tsk, व्योम __user *buf)
अणु
	अगर (use_fxsr()) अणु
		काष्ठा xregs_state *xsave = &tsk->thपढ़ो.fpu.state.xsave;
		काष्ठा user_i387_ia32_काष्ठा env;
		काष्ठा _fpstate_32 __user *fp = buf;

		fpregs_lock();
		अगर (!test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
			copy_fxregs_to_kernel(&tsk->thपढ़ो.fpu);
		fpregs_unlock();

		convert_from_fxsr(&env, tsk);

		अगर (__copy_to_user(buf, &env, माप(env)) ||
		    __put_user(xsave->i387.swd, &fp->status) ||
		    __put_user(X86_FXSR_MAGIC, &fp->magic))
			वापस -1;
	पूर्ण अन्यथा अणु
		काष्ठा fregs_state __user *fp = buf;
		u32 swd;
		अगर (__get_user(swd, &fp->swd) || __put_user(swd, &fp->status))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक save_xstate_epilog(व्योम __user *buf, पूर्णांक ia32_frame)
अणु
	काष्ठा xregs_state __user *x = buf;
	काष्ठा _fpx_sw_bytes *sw_bytes;
	u32 xfeatures;
	पूर्णांक err;

	/* Setup the bytes not touched by the [f]xsave and reserved क्रम SW. */
	sw_bytes = ia32_frame ? &fx_sw_reserved_ia32 : &fx_sw_reserved;
	err = __copy_to_user(&x->i387.sw_reserved, sw_bytes, माप(*sw_bytes));

	अगर (!use_xsave())
		वापस err;

	err |= __put_user(FP_XSTATE_MAGIC2,
			  (__u32 __user *)(buf + fpu_user_xstate_size));

	/*
	 * Read the xfeatures which we copied (directly from the cpu or
	 * from the state in task काष्ठा) to the user buffers.
	 */
	err |= __get_user(xfeatures, (__u32 __user *)&x->header.xfeatures);

	/*
	 * For legacy compatible, we always set FP/SSE bits in the bit
	 * vector जबतक saving the state to the user context. This will
	 * enable us capturing any changes(during sigवापस) to
	 * the FP/SSE bits by the legacy applications which करोn't touch
	 * xfeatures in the xsave header.
	 *
	 * xsave aware apps can change the xfeatures in the xsave
	 * header as well as change any contents in the memory layout.
	 * xrestore as part of sigवापस will capture all the changes.
	 */
	xfeatures |= XFEATURE_MASK_FPSSE;

	err |= __put_user(xfeatures, (__u32 __user *)&x->header.xfeatures);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक copy_fpregs_to_sigframe(काष्ठा xregs_state __user *buf)
अणु
	पूर्णांक err;

	अगर (use_xsave())
		err = copy_xregs_to_user(buf);
	अन्यथा अगर (use_fxsr())
		err = copy_fxregs_to_user((काष्ठा fxregs_state __user *) buf);
	अन्यथा
		err = copy_fregs_to_user((काष्ठा fregs_state __user *) buf);

	अगर (unlikely(err) && __clear_user(buf, fpu_user_xstate_size))
		err = -EFAULT;
	वापस err;
पूर्ण

/*
 * Save the fpu, extended रेजिस्टर state to the user संकेत frame.
 *
 * 'buf_fx' is the 64-byte aligned poपूर्णांकer at which the [f|fx|x]save
 *  state is copied.
 *  'buf' points to the 'buf_fx' or to the fsave header followed by 'buf_fx'.
 *
 *	buf == buf_fx क्रम 64-bit frames and 32-bit fsave frame.
 *	buf != buf_fx क्रम 32-bit frames with fxstate.
 *
 * Try to save it directly to the user frame with disabled page fault handler.
 * If this fails then करो the slow path where the FPU state is first saved to
 * task's fpu->state and then copy it to the user frame poपूर्णांकed to by the
 * aligned poपूर्णांकer 'buf_fx'.
 *
 * If this is a 32-bit frame with fxstate, put a fsave header beक्रमe
 * the aligned state at 'buf_fx'.
 *
 * For [f]xsave state, update the SW reserved fields in the [f]xsave frame
 * indicating the असलence/presence of the extended state to the user.
 */
पूर्णांक copy_fpstate_to_sigframe(व्योम __user *buf, व्योम __user *buf_fx, पूर्णांक size)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	पूर्णांक ia32_fxstate = (buf != buf_fx);
	पूर्णांक ret;

	ia32_fxstate &= (IS_ENABLED(CONFIG_X86_32) ||
			 IS_ENABLED(CONFIG_IA32_EMULATION));

	अगर (!अटल_cpu_has(X86_FEATURE_FPU)) अणु
		काष्ठा user_i387_ia32_काष्ठा fp;
		fpregs_soft_get(current, शून्य, (काष्ठा membuf)अणु.p = &fp,
						.left = माप(fp)पूर्ण);
		वापस copy_to_user(buf, &fp, माप(fp)) ? -EFAULT : 0;
	पूर्ण

	अगर (!access_ok(buf, size))
		वापस -EACCES;
retry:
	/*
	 * Load the FPU रेजिस्टरs अगर they are not valid क्रम the current task.
	 * With a valid FPU state we can attempt to save the state directly to
	 * userland's stack frame which will likely succeed. If it करोes not,
	 * resolve the fault in the user memory and try again.
	 */
	fpregs_lock();
	अगर (test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
		__fpregs_load_activate();

	pagefault_disable();
	ret = copy_fpregs_to_sigframe(buf_fx);
	pagefault_enable();
	fpregs_unlock();

	अगर (ret) अणु
		अगर (!fault_in_pages_ग_लिखोable(buf_fx, fpu_user_xstate_size))
			जाओ retry;
		वापस -EFAULT;
	पूर्ण

	/* Save the fsave header क्रम the 32-bit frames. */
	अगर ((ia32_fxstate || !use_fxsr()) && save_fsave_header(tsk, buf))
		वापस -1;

	अगर (use_fxsr() && save_xstate_epilog(buf_fx, ia32_fxstate))
		वापस -1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
sanitize_restored_user_xstate(जोड़ fpregs_state *state,
			      काष्ठा user_i387_ia32_काष्ठा *ia32_env,
			      u64 user_xfeatures, पूर्णांक fx_only)
अणु
	काष्ठा xregs_state *xsave = &state->xsave;
	काष्ठा xstate_header *header = &xsave->header;

	अगर (use_xsave()) अणु
		/*
		 * Note: we करोn't need to zero the reserved bits in the
		 * xstate_header here because we either didn't copy them at all,
		 * or we checked earlier that they aren't set.
		 */

		/*
		 * 'user_xfeatures' might have bits clear which are
		 * set in header->xfeatures. This represents features that
		 * were in init state prior to a संकेत delivery, and need
		 * to be reset back to the init state.  Clear any user
		 * feature bits which are set in the kernel buffer to get
		 * them back to the init state.
		 *
		 * Supervisor state is unchanged by input from userspace.
		 * Ensure supervisor state bits stay set and supervisor
		 * state is not modअगरied.
		 */
		अगर (fx_only)
			header->xfeatures = XFEATURE_MASK_FPSSE;
		अन्यथा
			header->xfeatures &= user_xfeatures |
					     xfeatures_mask_supervisor();
	पूर्ण

	अगर (use_fxsr()) अणु
		/*
		 * mscsr reserved bits must be masked to zero क्रम security
		 * reasons.
		 */
		xsave->i387.mxcsr &= mxcsr_feature_mask;

		अगर (ia32_env)
			convert_to_fxsr(&state->fxsave, ia32_env);
	पूर्ण
पूर्ण

/*
 * Restore the extended state अगर present. Otherwise, restore the FP/SSE state.
 */
अटल पूर्णांक copy_user_to_fpregs_zeroing(व्योम __user *buf, u64 xbv, पूर्णांक fx_only)
अणु
	u64 init_bv;
	पूर्णांक r;

	अगर (use_xsave()) अणु
		अगर (fx_only) अणु
			init_bv = xfeatures_mask_user() & ~XFEATURE_MASK_FPSSE;

			r = copy_user_to_fxregs(buf);
			अगर (!r)
				copy_kernel_to_xregs(&init_fpstate.xsave, init_bv);
			वापस r;
		पूर्ण अन्यथा अणु
			init_bv = xfeatures_mask_user() & ~xbv;

			r = copy_user_to_xregs(buf, xbv);
			अगर (!r && unlikely(init_bv))
				copy_kernel_to_xregs(&init_fpstate.xsave, init_bv);
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अगर (use_fxsr()) अणु
		वापस copy_user_to_fxregs(buf);
	पूर्ण अन्यथा
		वापस copy_user_to_fregs(buf);
पूर्ण

अटल पूर्णांक __fpu__restore_sig(व्योम __user *buf, व्योम __user *buf_fx, पूर्णांक size)
अणु
	काष्ठा user_i387_ia32_काष्ठा *envp = शून्य;
	पूर्णांक state_size = fpu_kernel_xstate_size;
	पूर्णांक ia32_fxstate = (buf != buf_fx);
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा fpu *fpu = &tsk->thपढ़ो.fpu;
	काष्ठा user_i387_ia32_काष्ठा env;
	u64 user_xfeatures = 0;
	पूर्णांक fx_only = 0;
	पूर्णांक ret = 0;

	ia32_fxstate &= (IS_ENABLED(CONFIG_X86_32) ||
			 IS_ENABLED(CONFIG_IA32_EMULATION));

	अगर (!buf) अणु
		fpu__clear_user_states(fpu);
		वापस 0;
	पूर्ण

	अगर (!access_ok(buf, size)) अणु
		ret = -EACCES;
		जाओ out;
	पूर्ण

	अगर (!अटल_cpu_has(X86_FEATURE_FPU)) अणु
		ret = fpregs_soft_set(current, शून्य, 0,
				      माप(काष्ठा user_i387_ia32_काष्ठा),
				      शून्य, buf);
		जाओ out;
	पूर्ण

	अगर (use_xsave()) अणु
		काष्ठा _fpx_sw_bytes fx_sw_user;
		अगर (unlikely(check_क्रम_xstate(buf_fx, buf_fx, &fx_sw_user))) अणु
			/*
			 * Couldn't find the extended state inक्रमmation in the
			 * memory layout. Restore just the FP/SSE and init all
			 * the other extended state.
			 */
			state_size = माप(काष्ठा fxregs_state);
			fx_only = 1;
			trace_x86_fpu_xstate_check_failed(fpu);
		पूर्ण अन्यथा अणु
			state_size = fx_sw_user.xstate_size;
			user_xfeatures = fx_sw_user.xfeatures;
		पूर्ण
	पूर्ण

	अगर ((अचिन्हित दीर्घ)buf_fx % 64)
		fx_only = 1;

	अगर (!ia32_fxstate) अणु
		/*
		 * Attempt to restore the FPU रेजिस्टरs directly from user
		 * memory. For that to succeed, the user access cannot cause
		 * page faults. If it करोes, fall back to the slow path below,
		 * going through the kernel buffer with the enabled pagefault
		 * handler.
		 */
		fpregs_lock();
		pagefault_disable();
		ret = copy_user_to_fpregs_zeroing(buf_fx, user_xfeatures, fx_only);
		pagefault_enable();
		अगर (!ret) अणु

			/*
			 * Restore supervisor states: previous context चयन
			 * etc has करोne XSAVES and saved the supervisor states
			 * in the kernel buffer from which they can be restored
			 * now.
			 *
			 * We cannot करो a single XRSTORS here - which would
			 * be nice - because the rest of the FPU रेजिस्टरs are
			 * being restored from a user buffer directly. The
			 * single XRSTORS happens below, when the user buffer
			 * has been copied to the kernel one.
			 */
			अगर (test_thपढ़ो_flag(TIF_NEED_FPU_LOAD) &&
			    xfeatures_mask_supervisor())
				copy_kernel_to_xregs(&fpu->state.xsave,
						     xfeatures_mask_supervisor());
			fpregs_mark_activate();
			fpregs_unlock();
			वापस 0;
		पूर्ण

		/*
		 * The above did an FPU restore operation, restricted to
		 * the user portion of the रेजिस्टरs, and failed, but the
		 * microcode might have modअगरied the FPU रेजिस्टरs
		 * nevertheless.
		 *
		 * If the FPU रेजिस्टरs करो not beदीर्घ to current, then
		 * invalidate the FPU रेजिस्टर state otherwise the task might
		 * preempt current and वापस to user space with corrupted
		 * FPU रेजिस्टरs.
		 *
		 * In हाल current owns the FPU रेजिस्टरs then no further
		 * action is required. The fixup below will handle it
		 * correctly.
		 */
		अगर (test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
			__cpu_invalidate_fpregs_state();

		fpregs_unlock();
	पूर्ण अन्यथा अणु
		/*
		 * For 32-bit frames with fxstate, copy the fxstate so it can
		 * be reस्थिरructed later.
		 */
		ret = __copy_from_user(&env, buf, माप(env));
		अगर (ret)
			जाओ out;
		envp = &env;
	पूर्ण

	/*
	 * By setting TIF_NEED_FPU_LOAD it is ensured that our xstate is
	 * not modअगरied on context चयन and that the xstate is considered
	 * to be loaded again on वापस to userland (overriding last_cpu aव्योमs
	 * the optimisation).
	 */
	fpregs_lock();

	अगर (!test_thपढ़ो_flag(TIF_NEED_FPU_LOAD)) अणु

		/*
		 * Supervisor states are not modअगरied by user space input.  Save
		 * current supervisor states first and invalidate the FPU regs.
		 */
		अगर (xfeatures_mask_supervisor())
			copy_supervisor_to_kernel(&fpu->state.xsave);
		set_thपढ़ो_flag(TIF_NEED_FPU_LOAD);
	पूर्ण
	__fpu_invalidate_fpregs_state(fpu);
	fpregs_unlock();

	अगर (use_xsave() && !fx_only) अणु
		u64 init_bv = xfeatures_mask_user() & ~user_xfeatures;

		ret = copy_user_to_xstate(&fpu->state.xsave, buf_fx);
		अगर (ret)
			जाओ out;

		sanitize_restored_user_xstate(&fpu->state, envp, user_xfeatures,
					      fx_only);

		fpregs_lock();
		अगर (unlikely(init_bv))
			copy_kernel_to_xregs(&init_fpstate.xsave, init_bv);

		/*
		 * Restore previously saved supervisor xstates aदीर्घ with
		 * copied-in user xstates.
		 */
		ret = copy_kernel_to_xregs_err(&fpu->state.xsave,
					       user_xfeatures | xfeatures_mask_supervisor());

	पूर्ण अन्यथा अगर (use_fxsr()) अणु
		ret = __copy_from_user(&fpu->state.fxsave, buf_fx, state_size);
		अगर (ret) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		sanitize_restored_user_xstate(&fpu->state, envp, user_xfeatures,
					      fx_only);

		fpregs_lock();
		अगर (use_xsave()) अणु
			u64 init_bv;

			init_bv = xfeatures_mask_user() & ~XFEATURE_MASK_FPSSE;
			copy_kernel_to_xregs(&init_fpstate.xsave, init_bv);
		पूर्ण

		ret = copy_kernel_to_fxregs_err(&fpu->state.fxsave);
	पूर्ण अन्यथा अणु
		ret = __copy_from_user(&fpu->state.fsave, buf_fx, state_size);
		अगर (ret)
			जाओ out;

		fpregs_lock();
		ret = copy_kernel_to_fregs_err(&fpu->state.fsave);
	पूर्ण
	अगर (!ret)
		fpregs_mark_activate();
	अन्यथा
		fpregs_deactivate(fpu);
	fpregs_unlock();

out:
	अगर (ret)
		fpu__clear_user_states(fpu);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक xstate_sigframe_size(व्योम)
अणु
	वापस use_xsave() ? fpu_user_xstate_size + FP_XSTATE_MAGIC2_SIZE :
			fpu_user_xstate_size;
पूर्ण

/*
 * Restore FPU state from a sigframe:
 */
पूर्णांक fpu__restore_sig(व्योम __user *buf, पूर्णांक ia32_frame)
अणु
	व्योम __user *buf_fx = buf;
	पूर्णांक size = xstate_sigframe_size();

	अगर (ia32_frame && use_fxsr()) अणु
		buf_fx = buf + माप(काष्ठा fregs_state);
		size += माप(काष्ठा fregs_state);
	पूर्ण

	वापस __fpu__restore_sig(buf, buf_fx, size);
पूर्ण

अचिन्हित दीर्घ
fpu__alloc_mathframe(अचिन्हित दीर्घ sp, पूर्णांक ia32_frame,
		     अचिन्हित दीर्घ *buf_fx, अचिन्हित दीर्घ *size)
अणु
	अचिन्हित दीर्घ frame_size = xstate_sigframe_size();

	*buf_fx = sp = round_करोwn(sp - frame_size, 64);
	अगर (ia32_frame && use_fxsr()) अणु
		frame_size += माप(काष्ठा fregs_state);
		sp -= माप(काष्ठा fregs_state);
	पूर्ण

	*size = frame_size;

	वापस sp;
पूर्ण
/*
 * Prepare the SW reserved portion of the fxsave memory layout, indicating
 * the presence of the extended state inक्रमmation in the memory layout
 * poपूर्णांकed by the fpstate poपूर्णांकer in the sigcontext.
 * This will be saved when ever the FP and extended state context is
 * saved on the user stack during the संकेत handler delivery to the user.
 */
व्योम fpu__init_prepare_fx_sw_frame(व्योम)
अणु
	पूर्णांक size = fpu_user_xstate_size + FP_XSTATE_MAGIC2_SIZE;

	fx_sw_reserved.magic1 = FP_XSTATE_MAGIC1;
	fx_sw_reserved.extended_size = size;
	fx_sw_reserved.xfeatures = xfeatures_mask_user();
	fx_sw_reserved.xstate_size = fpu_user_xstate_size;

	अगर (IS_ENABLED(CONFIG_IA32_EMULATION) ||
	    IS_ENABLED(CONFIG_X86_32)) अणु
		पूर्णांक fsave_header_size = माप(काष्ठा fregs_state);

		fx_sw_reserved_ia32 = fx_sw_reserved;
		fx_sw_reserved_ia32.extended_size = size + fsave_header_size;
	पूर्ण
पूर्ण


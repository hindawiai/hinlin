<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/संकेत.c
 *
 * Copyright (C) 1995-2009 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/cache.h>
#समावेश <linux/compat.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/personality.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/sizes.h>
#समावेश <linux/माला.स>
#समावेश <linux/tracehook.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/संकेत32.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/vdso.h>

/*
 * Do a संकेत वापस; unकरो the संकेत stack. These are aligned to 128-bit.
 */
काष्ठा rt_sigframe अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
पूर्ण;

काष्ठा frame_record अणु
	u64 fp;
	u64 lr;
पूर्ण;

काष्ठा rt_sigframe_user_layout अणु
	काष्ठा rt_sigframe __user *sigframe;
	काष्ठा frame_record __user *next_frame;

	अचिन्हित दीर्घ size;	/* size of allocated sigframe data */
	अचिन्हित दीर्घ limit;	/* largest allowed size */

	अचिन्हित दीर्घ fpsimd_offset;
	अचिन्हित दीर्घ esr_offset;
	अचिन्हित दीर्घ sve_offset;
	अचिन्हित दीर्घ extra_offset;
	अचिन्हित दीर्घ end_offset;
पूर्ण;

#घोषणा BASE_SIGFRAME_SIZE round_up(माप(काष्ठा rt_sigframe), 16)
#घोषणा TERMINATOR_SIZE round_up(माप(काष्ठा _aarch64_ctx), 16)
#घोषणा EXTRA_CONTEXT_SIZE round_up(माप(काष्ठा extra_context), 16)

अटल व्योम init_user_layout(काष्ठा rt_sigframe_user_layout *user)
अणु
	स्थिर माप_प्रकार reserved_size =
		माप(user->sigframe->uc.uc_mcontext.__reserved);

	स_रखो(user, 0, माप(*user));
	user->size = दुरत्व(काष्ठा rt_sigframe, uc.uc_mcontext.__reserved);

	user->limit = user->size + reserved_size;

	user->limit -= TERMINATOR_SIZE;
	user->limit -= EXTRA_CONTEXT_SIZE;
	/* Reserve space क्रम extension and terminator ^ */
पूर्ण

अटल माप_प्रकार sigframe_size(काष्ठा rt_sigframe_user_layout स्थिर *user)
अणु
	वापस round_up(max(user->size, माप(काष्ठा rt_sigframe)), 16);
पूर्ण

/*
 * Sanity limit on the approximate maximum size of संकेत frame we'll
 * try to generate.  Stack alignment padding and the frame record are
 * not taken पूर्णांकo account.  This limit is not a guarantee and is
 * NOT ABI.
 */
#घोषणा SIGFRAME_MAXSZ SZ_64K

अटल पूर्णांक __sigframe_alloc(काष्ठा rt_sigframe_user_layout *user,
			    अचिन्हित दीर्घ *offset, माप_प्रकार size, bool extend)
अणु
	माप_प्रकार padded_size = round_up(size, 16);

	अगर (padded_size > user->limit - user->size &&
	    !user->extra_offset &&
	    extend) अणु
		पूर्णांक ret;

		user->limit += EXTRA_CONTEXT_SIZE;
		ret = __sigframe_alloc(user, &user->extra_offset,
				       माप(काष्ठा extra_context), false);
		अगर (ret) अणु
			user->limit -= EXTRA_CONTEXT_SIZE;
			वापस ret;
		पूर्ण

		/* Reserve space क्रम the __reserved[] terminator */
		user->size += TERMINATOR_SIZE;

		/*
		 * Allow expansion up to SIGFRAME_MAXSZ, ensuring space क्रम
		 * the terminator:
		 */
		user->limit = SIGFRAME_MAXSZ - TERMINATOR_SIZE;
	पूर्ण

	/* Still not enough space?  Bad luck! */
	अगर (padded_size > user->limit - user->size)
		वापस -ENOMEM;

	*offset = user->size;
	user->size += padded_size;

	वापस 0;
पूर्ण

/*
 * Allocate space क्रम an optional record of <size> bytes in the user
 * संकेत frame.  The offset from the संकेत frame base address to the
 * allocated block is asचिन्हित to *offset.
 */
अटल पूर्णांक sigframe_alloc(काष्ठा rt_sigframe_user_layout *user,
			  अचिन्हित दीर्घ *offset, माप_प्रकार size)
अणु
	वापस __sigframe_alloc(user, offset, size, true);
पूर्ण

/* Allocate the null terminator record and prevent further allocations */
अटल पूर्णांक sigframe_alloc_end(काष्ठा rt_sigframe_user_layout *user)
अणु
	पूर्णांक ret;

	/* Un-reserve the space reserved क्रम the terminator: */
	user->limit += TERMINATOR_SIZE;

	ret = sigframe_alloc(user, &user->end_offset,
			     माप(काष्ठा _aarch64_ctx));
	अगर (ret)
		वापस ret;

	/* Prevent further allocation: */
	user->limit = user->size;
	वापस 0;
पूर्ण

अटल व्योम __user *apply_user_offset(
	काष्ठा rt_sigframe_user_layout स्थिर *user, अचिन्हित दीर्घ offset)
अणु
	अक्षर __user *base = (अक्षर __user *)user->sigframe;

	वापस base + offset;
पूर्ण

अटल पूर्णांक preserve_fpsimd_context(काष्ठा fpsimd_context __user *ctx)
अणु
	काष्ठा user_fpsimd_state स्थिर *fpsimd =
		&current->thपढ़ो.uw.fpsimd_state;
	पूर्णांक err;

	/* copy the FP and status/control रेजिस्टरs */
	err = __copy_to_user(ctx->vregs, fpsimd->vregs, माप(fpsimd->vregs));
	__put_user_error(fpsimd->fpsr, &ctx->fpsr, err);
	__put_user_error(fpsimd->fpcr, &ctx->fpcr, err);

	/* copy the magic/size inक्रमmation */
	__put_user_error(FPSIMD_MAGIC, &ctx->head.magic, err);
	__put_user_error(माप(काष्ठा fpsimd_context), &ctx->head.size, err);

	वापस err ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक restore_fpsimd_context(काष्ठा fpsimd_context __user *ctx)
अणु
	काष्ठा user_fpsimd_state fpsimd;
	__u32 magic, size;
	पूर्णांक err = 0;

	/* check the magic/size inक्रमmation */
	__get_user_error(magic, &ctx->head.magic, err);
	__get_user_error(size, &ctx->head.size, err);
	अगर (err)
		वापस -EFAULT;
	अगर (magic != FPSIMD_MAGIC || size != माप(काष्ठा fpsimd_context))
		वापस -EINVAL;

	/* copy the FP and status/control रेजिस्टरs */
	err = __copy_from_user(fpsimd.vregs, ctx->vregs,
			       माप(fpsimd.vregs));
	__get_user_error(fpsimd.fpsr, &ctx->fpsr, err);
	__get_user_error(fpsimd.fpcr, &ctx->fpcr, err);

	clear_thपढ़ो_flag(TIF_SVE);

	/* load the hardware रेजिस्टरs from the fpsimd_state काष्ठाure */
	अगर (!err)
		fpsimd_update_current_state(&fpsimd);

	वापस err ? -EFAULT : 0;
पूर्ण


काष्ठा user_ctxs अणु
	काष्ठा fpsimd_context __user *fpsimd;
	काष्ठा sve_context __user *sve;
पूर्ण;

#अगर_घोषित CONFIG_ARM64_SVE

अटल पूर्णांक preserve_sve_context(काष्ठा sve_context __user *ctx)
अणु
	पूर्णांक err = 0;
	u16 reserved[ARRAY_SIZE(ctx->__reserved)];
	अचिन्हित पूर्णांक vl = current->thपढ़ो.sve_vl;
	अचिन्हित पूर्णांक vq = 0;

	अगर (test_thपढ़ो_flag(TIF_SVE))
		vq = sve_vq_from_vl(vl);

	स_रखो(reserved, 0, माप(reserved));

	__put_user_error(SVE_MAGIC, &ctx->head.magic, err);
	__put_user_error(round_up(SVE_SIG_CONTEXT_SIZE(vq), 16),
			 &ctx->head.size, err);
	__put_user_error(vl, &ctx->vl, err);
	BUILD_BUG_ON(माप(ctx->__reserved) != माप(reserved));
	err |= __copy_to_user(&ctx->__reserved, reserved, माप(reserved));

	अगर (vq) अणु
		/*
		 * This assumes that the SVE state has alपढ़ोy been saved to
		 * the task काष्ठा by calling the function
		 * fpsimd_संकेत_preserve_current_state().
		 */
		err |= __copy_to_user((अक्षर __user *)ctx + SVE_SIG_REGS_OFFSET,
				      current->thपढ़ो.sve_state,
				      SVE_SIG_REGS_SIZE(vq));
	पूर्ण

	वापस err ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक restore_sve_fpsimd_context(काष्ठा user_ctxs *user)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक vq;
	काष्ठा user_fpsimd_state fpsimd;
	काष्ठा sve_context sve;

	अगर (__copy_from_user(&sve, user->sve, माप(sve)))
		वापस -EFAULT;

	अगर (sve.vl != current->thपढ़ो.sve_vl)
		वापस -EINVAL;

	अगर (sve.head.size <= माप(*user->sve)) अणु
		clear_thपढ़ो_flag(TIF_SVE);
		जाओ fpsimd_only;
	पूर्ण

	vq = sve_vq_from_vl(sve.vl);

	अगर (sve.head.size < SVE_SIG_CONTEXT_SIZE(vq))
		वापस -EINVAL;

	/*
	 * Careful: we are about __copy_from_user() directly पूर्णांकo
	 * thपढ़ो.sve_state with preemption enabled, so protection is
	 * needed to prevent a racing context चयन from writing stale
	 * रेजिस्टरs back over the new data.
	 */

	fpsimd_flush_task_state(current);
	/* From now, fpsimd_thपढ़ो_चयन() won't touch thपढ़ो.sve_state */

	sve_alloc(current);
	err = __copy_from_user(current->thपढ़ो.sve_state,
			       (अक्षर __user स्थिर *)user->sve +
					SVE_SIG_REGS_OFFSET,
			       SVE_SIG_REGS_SIZE(vq));
	अगर (err)
		वापस -EFAULT;

	set_thपढ़ो_flag(TIF_SVE);

fpsimd_only:
	/* copy the FP and status/control रेजिस्टरs */
	/* restore_sigframe() alपढ़ोy checked that user->fpsimd != शून्य. */
	err = __copy_from_user(fpsimd.vregs, user->fpsimd->vregs,
			       माप(fpsimd.vregs));
	__get_user_error(fpsimd.fpsr, &user->fpsimd->fpsr, err);
	__get_user_error(fpsimd.fpcr, &user->fpsimd->fpcr, err);

	/* load the hardware रेजिस्टरs from the fpsimd_state काष्ठाure */
	अगर (!err)
		fpsimd_update_current_state(&fpsimd);

	वापस err ? -EFAULT : 0;
पूर्ण

#अन्यथा /* ! CONFIG_ARM64_SVE */

/* Turn any non-optimised out attempts to use these पूर्णांकo a link error: */
बाह्य पूर्णांक preserve_sve_context(व्योम __user *ctx);
बाह्य पूर्णांक restore_sve_fpsimd_context(काष्ठा user_ctxs *user);

#पूर्ण_अगर /* ! CONFIG_ARM64_SVE */


अटल पूर्णांक parse_user_sigframe(काष्ठा user_ctxs *user,
			       काष्ठा rt_sigframe __user *sf)
अणु
	काष्ठा sigcontext __user *स्थिर sc = &sf->uc.uc_mcontext;
	काष्ठा _aarch64_ctx __user *head;
	अक्षर __user *base = (अक्षर __user *)&sc->__reserved;
	माप_प्रकार offset = 0;
	माप_प्रकार limit = माप(sc->__reserved);
	bool have_extra_context = false;
	अक्षर स्थिर __user *स्थिर sfp = (अक्षर स्थिर __user *)sf;

	user->fpsimd = शून्य;
	user->sve = शून्य;

	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)base, 16))
		जाओ invalid;

	जबतक (1) अणु
		पूर्णांक err = 0;
		u32 magic, size;
		अक्षर स्थिर __user *userp;
		काष्ठा extra_context स्थिर __user *extra;
		u64 extra_datap;
		u32 extra_size;
		काष्ठा _aarch64_ctx स्थिर __user *end;
		u32 end_magic, end_size;

		अगर (limit - offset < माप(*head))
			जाओ invalid;

		अगर (!IS_ALIGNED(offset, 16))
			जाओ invalid;

		head = (काष्ठा _aarch64_ctx __user *)(base + offset);
		__get_user_error(magic, &head->magic, err);
		__get_user_error(size, &head->size, err);
		अगर (err)
			वापस err;

		अगर (limit - offset < size)
			जाओ invalid;

		चयन (magic) अणु
		हाल 0:
			अगर (size)
				जाओ invalid;

			जाओ करोne;

		हाल FPSIMD_MAGIC:
			अगर (!प्रणाली_supports_fpsimd())
				जाओ invalid;
			अगर (user->fpsimd)
				जाओ invalid;

			अगर (size < माप(*user->fpsimd))
				जाओ invalid;

			user->fpsimd = (काष्ठा fpsimd_context __user *)head;
			अवरोध;

		हाल ESR_MAGIC:
			/* ignore */
			अवरोध;

		हाल SVE_MAGIC:
			अगर (!प्रणाली_supports_sve())
				जाओ invalid;

			अगर (user->sve)
				जाओ invalid;

			अगर (size < माप(*user->sve))
				जाओ invalid;

			user->sve = (काष्ठा sve_context __user *)head;
			अवरोध;

		हाल EXTRA_MAGIC:
			अगर (have_extra_context)
				जाओ invalid;

			अगर (size < माप(*extra))
				जाओ invalid;

			userp = (अक्षर स्थिर __user *)head;

			extra = (काष्ठा extra_context स्थिर __user *)userp;
			userp += size;

			__get_user_error(extra_datap, &extra->datap, err);
			__get_user_error(extra_size, &extra->size, err);
			अगर (err)
				वापस err;

			/* Check क्रम the dummy terminator in __reserved[]: */

			अगर (limit - offset - size < TERMINATOR_SIZE)
				जाओ invalid;

			end = (काष्ठा _aarch64_ctx स्थिर __user *)userp;
			userp += TERMINATOR_SIZE;

			__get_user_error(end_magic, &end->magic, err);
			__get_user_error(end_size, &end->size, err);
			अगर (err)
				वापस err;

			अगर (end_magic || end_size)
				जाओ invalid;

			/* Prevent looping/repeated parsing of extra_context */
			have_extra_context = true;

			base = (__क्रमce व्योम __user *)extra_datap;
			अगर (!IS_ALIGNED((अचिन्हित दीर्घ)base, 16))
				जाओ invalid;

			अगर (!IS_ALIGNED(extra_size, 16))
				जाओ invalid;

			अगर (base != userp)
				जाओ invalid;

			/* Reject "unreasonably large" frames: */
			अगर (extra_size > sfp + SIGFRAME_MAXSZ - userp)
				जाओ invalid;

			/*
			 * Ignore trailing terminator in __reserved[]
			 * and start parsing extra data:
			 */
			offset = 0;
			limit = extra_size;

			अगर (!access_ok(base, limit))
				जाओ invalid;

			जारी;

		शेष:
			जाओ invalid;
		पूर्ण

		अगर (size < माप(*head))
			जाओ invalid;

		अगर (limit - offset < size)
			जाओ invalid;

		offset += size;
	पूर्ण

करोne:
	वापस 0;

invalid:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक restore_sigframe(काष्ठा pt_regs *regs,
			    काष्ठा rt_sigframe __user *sf)
अणु
	sigset_t set;
	पूर्णांक i, err;
	काष्ठा user_ctxs user;

	err = __copy_from_user(&set, &sf->uc.uc_sigmask, माप(set));
	अगर (err == 0)
		set_current_blocked(&set);

	क्रम (i = 0; i < 31; i++)
		__get_user_error(regs->regs[i], &sf->uc.uc_mcontext.regs[i],
				 err);
	__get_user_error(regs->sp, &sf->uc.uc_mcontext.sp, err);
	__get_user_error(regs->pc, &sf->uc.uc_mcontext.pc, err);
	__get_user_error(regs->pstate, &sf->uc.uc_mcontext.pstate, err);

	/*
	 * Aव्योम sys_rt_sigवापस() restarting.
	 */
	क्रमget_syscall(regs);

	err |= !valid_user_regs(&regs->user_regs, current);
	अगर (err == 0)
		err = parse_user_sigframe(&user, sf);

	अगर (err == 0 && प्रणाली_supports_fpsimd()) अणु
		अगर (!user.fpsimd)
			वापस -EINVAL;

		अगर (user.sve) अणु
			अगर (!प्रणाली_supports_sve())
				वापस -EINVAL;

			err = restore_sve_fpsimd_context(&user);
		पूर्ण अन्यथा अणु
			err = restore_fpsimd_context(user.fpsimd);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe __user *frame;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/*
	 * Since we stacked the संकेत on a 128-bit boundary, then 'sp' should
	 * be word aligned here.
	 */
	अगर (regs->sp & 15)
		जाओ badframe;

	frame = (काष्ठा rt_sigframe __user *)regs->sp;

	अगर (!access_ok(frame, माप (*frame)))
		जाओ badframe;

	अगर (restore_sigframe(regs, frame))
		जाओ badframe;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस regs->regs[0];

badframe:
	arm64_notअगरy_segfault(regs->sp);
	वापस 0;
पूर्ण

/*
 * Determine the layout of optional records in the संकेत frame
 *
 * add_all: अगर true, lays out the biggest possible संकेत frame क्रम
 *	this task; otherwise, generates a layout क्रम the current state
 *	of the task.
 */
अटल पूर्णांक setup_sigframe_layout(काष्ठा rt_sigframe_user_layout *user,
				 bool add_all)
अणु
	पूर्णांक err;

	err = sigframe_alloc(user, &user->fpsimd_offset,
			     माप(काष्ठा fpsimd_context));
	अगर (err)
		वापस err;

	/* fault inक्रमmation, अगर valid */
	अगर (add_all || current->thपढ़ो.fault_code) अणु
		err = sigframe_alloc(user, &user->esr_offset,
				     माप(काष्ठा esr_context));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (प्रणाली_supports_sve()) अणु
		अचिन्हित पूर्णांक vq = 0;

		अगर (add_all || test_thपढ़ो_flag(TIF_SVE)) अणु
			पूर्णांक vl = sve_max_vl;

			अगर (!add_all)
				vl = current->thपढ़ो.sve_vl;

			vq = sve_vq_from_vl(vl);
		पूर्ण

		err = sigframe_alloc(user, &user->sve_offset,
				     SVE_SIG_CONTEXT_SIZE(vq));
		अगर (err)
			वापस err;
	पूर्ण

	वापस sigframe_alloc_end(user);
पूर्ण

अटल पूर्णांक setup_sigframe(काष्ठा rt_sigframe_user_layout *user,
			  काष्ठा pt_regs *regs, sigset_t *set)
अणु
	पूर्णांक i, err = 0;
	काष्ठा rt_sigframe __user *sf = user->sigframe;

	/* set up the stack frame क्रम unwinding */
	__put_user_error(regs->regs[29], &user->next_frame->fp, err);
	__put_user_error(regs->regs[30], &user->next_frame->lr, err);

	क्रम (i = 0; i < 31; i++)
		__put_user_error(regs->regs[i], &sf->uc.uc_mcontext.regs[i],
				 err);
	__put_user_error(regs->sp, &sf->uc.uc_mcontext.sp, err);
	__put_user_error(regs->pc, &sf->uc.uc_mcontext.pc, err);
	__put_user_error(regs->pstate, &sf->uc.uc_mcontext.pstate, err);

	__put_user_error(current->thपढ़ो.fault_address, &sf->uc.uc_mcontext.fault_address, err);

	err |= __copy_to_user(&sf->uc.uc_sigmask, set, माप(*set));

	अगर (err == 0 && प्रणाली_supports_fpsimd()) अणु
		काष्ठा fpsimd_context __user *fpsimd_ctx =
			apply_user_offset(user, user->fpsimd_offset);
		err |= preserve_fpsimd_context(fpsimd_ctx);
	पूर्ण

	/* fault inक्रमmation, अगर valid */
	अगर (err == 0 && user->esr_offset) अणु
		काष्ठा esr_context __user *esr_ctx =
			apply_user_offset(user, user->esr_offset);

		__put_user_error(ESR_MAGIC, &esr_ctx->head.magic, err);
		__put_user_error(माप(*esr_ctx), &esr_ctx->head.size, err);
		__put_user_error(current->thपढ़ो.fault_code, &esr_ctx->esr, err);
	पूर्ण

	/* Scalable Vector Extension state, अगर present */
	अगर (प्रणाली_supports_sve() && err == 0 && user->sve_offset) अणु
		काष्ठा sve_context __user *sve_ctx =
			apply_user_offset(user, user->sve_offset);
		err |= preserve_sve_context(sve_ctx);
	पूर्ण

	अगर (err == 0 && user->extra_offset) अणु
		अक्षर __user *sfp = (अक्षर __user *)user->sigframe;
		अक्षर __user *userp =
			apply_user_offset(user, user->extra_offset);

		काष्ठा extra_context __user *extra;
		काष्ठा _aarch64_ctx __user *end;
		u64 extra_datap;
		u32 extra_size;

		extra = (काष्ठा extra_context __user *)userp;
		userp += EXTRA_CONTEXT_SIZE;

		end = (काष्ठा _aarch64_ctx __user *)userp;
		userp += TERMINATOR_SIZE;

		/*
		 * extra_datap is just written to the संकेत frame.
		 * The value माला_लो cast back to a व्योम __user *
		 * during sigवापस.
		 */
		extra_datap = (__क्रमce u64)userp;
		extra_size = sfp + round_up(user->size, 16) - userp;

		__put_user_error(EXTRA_MAGIC, &extra->head.magic, err);
		__put_user_error(EXTRA_CONTEXT_SIZE, &extra->head.size, err);
		__put_user_error(extra_datap, &extra->datap, err);
		__put_user_error(extra_size, &extra->size, err);

		/* Add the terminator */
		__put_user_error(0, &end->magic, err);
		__put_user_error(0, &end->size, err);
	पूर्ण

	/* set the "end" magic */
	अगर (err == 0) अणु
		काष्ठा _aarch64_ctx __user *end =
			apply_user_offset(user, user->end_offset);

		__put_user_error(0, &end->magic, err);
		__put_user_error(0, &end->size, err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक get_sigframe(काष्ठा rt_sigframe_user_layout *user,
			 काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp, sp_top;
	पूर्णांक err;

	init_user_layout(user);
	err = setup_sigframe_layout(user, false);
	अगर (err)
		वापस err;

	sp = sp_top = sigsp(regs->sp, ksig);

	sp = round_करोwn(sp - माप(काष्ठा frame_record), 16);
	user->next_frame = (काष्ठा frame_record __user *)sp;

	sp = round_करोwn(sp, 16) - sigframe_size(user);
	user->sigframe = (काष्ठा rt_sigframe __user *)sp;

	/*
	 * Check that we can actually ग_लिखो to the संकेत frame.
	 */
	अगर (!access_ok(user->sigframe, sp_top - sp))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम setup_वापस(काष्ठा pt_regs *regs, काष्ठा k_sigaction *ka,
			 काष्ठा rt_sigframe_user_layout *user, पूर्णांक usig)
अणु
	__sigrestore_t sigtramp;

	regs->regs[0] = usig;
	regs->sp = (अचिन्हित दीर्घ)user->sigframe;
	regs->regs[29] = (अचिन्हित दीर्घ)&user->next_frame->fp;
	regs->pc = (अचिन्हित दीर्घ)ka->sa.sa_handler;

	/*
	 * Signal delivery is a (wacky) indirect function call in
	 * userspace, so simulate the same setting of BTYPE as a BLR
	 * <रेजिस्टर containing the संकेत handler entry poपूर्णांक>.
	 * Signal delivery to a location in a PROT_BTI guarded page
	 * that is not a function entry poपूर्णांक will now trigger a
	 * संक_अवैध in userspace.
	 *
	 * If the संकेत handler entry poपूर्णांक is not in a PROT_BTI
	 * guarded page, this is harmless.
	 */
	अगर (प्रणाली_supports_bti()) अणु
		regs->pstate &= ~PSR_BTYPE_MASK;
		regs->pstate |= PSR_BTYPE_C;
	पूर्ण

	/* TCO (Tag Check Override) always cleared क्रम संकेत handlers */
	regs->pstate &= ~PSR_TCO_BIT;

	अगर (ka->sa.sa_flags & SA_RESTORER)
		sigtramp = ka->sa.sa_restorer;
	अन्यथा
		sigtramp = VDSO_SYMBOL(current->mm->context.vdso, sigtramp);

	regs->regs[30] = (अचिन्हित दीर्घ)sigtramp;
पूर्ण

अटल पूर्णांक setup_rt_frame(पूर्णांक usig, काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe_user_layout user;
	काष्ठा rt_sigframe __user *frame;
	पूर्णांक err = 0;

	fpsimd_संकेत_preserve_current_state();

	अगर (get_sigframe(&user, ksig, regs))
		वापस 1;

	frame = user.sigframe;

	__put_user_error(0, &frame->uc.uc_flags, err);
	__put_user_error(शून्य, &frame->uc.uc_link, err);

	err |= __save_altstack(&frame->uc.uc_stack, regs->sp);
	err |= setup_sigframe(&user, regs, set);
	अगर (err == 0) अणु
		setup_वापस(regs, &ksig->ka, &user, usig);
		अगर (ksig->ka.sa.sa_flags & SA_SIGINFO) अणु
			err |= copy_siginfo_to_user(&frame->info, &ksig->info);
			regs->regs[1] = (अचिन्हित दीर्घ)&frame->info;
			regs->regs[2] = (अचिन्हित दीर्घ)&frame->uc;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम setup_restart_syscall(काष्ठा pt_regs *regs)
अणु
	अगर (is_compat_task())
		compat_setup_restart_syscall(regs);
	अन्यथा
		regs->regs[8] = __NR_restart_syscall;
पूर्ण

/*
 * OK, we're invoking a handler
 */
अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक usig = ksig->sig;
	पूर्णांक ret;

	rseq_संकेत_deliver(ksig, regs);

	/*
	 * Set up the stack frame
	 */
	अगर (is_compat_task()) अणु
		अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
			ret = compat_setup_rt_frame(usig, ksig, oldset, regs);
		अन्यथा
			ret = compat_setup_frame(usig, ksig, oldset, regs);
	पूर्ण अन्यथा अणु
		ret = setup_rt_frame(usig, ksig, oldset, regs);
	पूर्ण

	/*
	 * Check that the resulting रेजिस्टरs are actually sane.
	 */
	ret |= !valid_user_regs(&regs->user_regs, current);

	/* Step पूर्णांकo the संकेत handler अगर we are stepping */
	संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLESTEP));
पूर्ण

/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 *
 * Note that we go through the संकेतs twice: once to check the संकेतs that
 * the kernel can handle, and then we build all the user-level संकेत handling
 * stack-frames in one go after that.
 */
अटल व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ जारी_addr = 0, restart_addr = 0;
	पूर्णांक retval = 0;
	काष्ठा kसंकेत ksig;
	bool syscall = in_syscall(regs);

	/*
	 * If we were from a प्रणाली call, check क्रम प्रणाली call restarting...
	 */
	अगर (syscall) अणु
		जारी_addr = regs->pc;
		restart_addr = जारी_addr - (compat_thumb_mode(regs) ? 2 : 4);
		retval = regs->regs[0];

		/*
		 * Aव्योम additional syscall restarting via ret_to_user.
		 */
		क्रमget_syscall(regs);

		/*
		 * Prepare क्रम प्रणाली call restart. We करो this here so that a
		 * debugger will see the alपढ़ोy changed PC.
		 */
		चयन (retval) अणु
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
		हाल -ERESTART_RESTARTBLOCK:
			regs->regs[0] = regs->orig_x0;
			regs->pc = restart_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Get the संकेत to deliver. When running under ptrace, at this poपूर्णांक
	 * the debugger may change all of our रेजिस्टरs.
	 */
	अगर (get_संकेत(&ksig)) अणु
		/*
		 * Depending on the संकेत settings, we may need to revert the
		 * decision to restart the प्रणाली call, but skip this अगर a
		 * debugger has chosen to restart at a dअगरferent PC.
		 */
		अगर (regs->pc == restart_addr &&
		    (retval == -ERESTARTNOHAND ||
		     retval == -ERESTART_RESTARTBLOCK ||
		     (retval == -ERESTARTSYS &&
		      !(ksig.ka.sa.sa_flags & SA_RESTART)))) अणु
			regs->regs[0] = -EINTR;
			regs->pc = जारी_addr;
		पूर्ण

		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	/*
	 * Handle restarting a dअगरferent प्रणाली call. As above, अगर a debugger
	 * has chosen to restart at a dअगरferent PC, ignore the restart.
	 */
	अगर (syscall && regs->pc == restart_addr) अणु
		अगर (retval == -ERESTART_RESTARTBLOCK)
			setup_restart_syscall(regs);
		user_शुरुआत_single_step(current);
	पूर्ण

	restore_saved_sigmask();
पूर्ण

यंत्रlinkage व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs,
				 अचिन्हित दीर्घ thपढ़ो_flags)
अणु
	करो अणु
		अगर (thपढ़ो_flags & _TIF_NEED_RESCHED) अणु
			/* Unmask Debug and SError क्रम the next task */
			local_daअगर_restore(DAIF_PROCCTX_NOIRQ);

			schedule();
		पूर्ण अन्यथा अणु
			local_daअगर_restore(DAIF_PROCCTX);

			अगर (thपढ़ो_flags & _TIF_UPROBE)
				uprobe_notअगरy_resume(regs);

			अगर (thपढ़ो_flags & _TIF_MTE_ASYNC_FAULT) अणु
				clear_thपढ़ो_flag(TIF_MTE_ASYNC_FAULT);
				send_sig_fault(संक_अंश, SEGV_MTEAERR,
					       (व्योम __user *)शून्य, current);
			पूर्ण

			अगर (thपढ़ो_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
				करो_संकेत(regs);

			अगर (thपढ़ो_flags & _TIF_NOTIFY_RESUME) अणु
				tracehook_notअगरy_resume(regs);
				rseq_handle_notअगरy_resume(शून्य, regs);
			पूर्ण

			अगर (thपढ़ो_flags & _TIF_FOREIGN_FPSTATE)
				fpsimd_restore_current_state();
		पूर्ण

		local_daअगर_mask();
		thपढ़ो_flags = READ_ONCE(current_thपढ़ो_info()->flags);
	पूर्ण जबतक (thपढ़ो_flags & _TIF_WORK_MASK);
पूर्ण

अचिन्हित दीर्घ __ro_after_init संकेत_minsigstksz;

/*
 * Determine the stack space required क्रम guaranteed संकेत devliery.
 * This function is used to populate AT_MINSIGSTKSZ at process startup.
 * cpufeatures setup is assumed to be complete.
 */
व्योम __init minsigstksz_setup(व्योम)
अणु
	काष्ठा rt_sigframe_user_layout user;

	init_user_layout(&user);

	/*
	 * If this fails, SIGFRAME_MAXSZ needs to be enlarged.  It won't
	 * be big enough, but it's our best guess:
	 */
	अगर (WARN_ON(setup_sigframe_layout(&user, true)))
		वापस;

	संकेत_minsigstksz = sigframe_size(&user) +
		round_up(माप(काष्ठा frame_record), 16) +
		16; /* max alignment padding */
पूर्ण

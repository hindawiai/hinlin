<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/संकेत.c
 *
 *  Copyright (C) 1995-2009 Russell King
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/personality.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/vfp.h>

#समावेश "signal.h"

बाह्य स्थिर अचिन्हित दीर्घ sigवापस_codes[17];

अटल अचिन्हित दीर्घ संकेत_वापस_offset;

#अगर_घोषित CONFIG_CRUNCH
अटल पूर्णांक preserve_crunch_context(काष्ठा crunch_sigframe __user *frame)
अणु
	अक्षर kbuf[माप(*frame) + 8];
	काष्ठा crunch_sigframe *kframe;

	/* the crunch context must be 64 bit aligned */
	kframe = (काष्ठा crunch_sigframe *)((अचिन्हित दीर्घ)(kbuf + 8) & ~7);
	kframe->magic = CRUNCH_MAGIC;
	kframe->size = CRUNCH_STORAGE_SIZE;
	crunch_task_copy(current_thपढ़ो_info(), &kframe->storage);
	वापस __copy_to_user(frame, kframe, माप(*frame));
पूर्ण

अटल पूर्णांक restore_crunch_context(अक्षर __user **auxp)
अणु
	काष्ठा crunch_sigframe __user *frame =
		(काष्ठा crunch_sigframe __user *)*auxp;
	अक्षर kbuf[माप(*frame) + 8];
	काष्ठा crunch_sigframe *kframe;

	/* the crunch context must be 64 bit aligned */
	kframe = (काष्ठा crunch_sigframe *)((अचिन्हित दीर्घ)(kbuf + 8) & ~7);
	अगर (__copy_from_user(kframe, frame, माप(*frame)))
		वापस -1;
	अगर (kframe->magic != CRUNCH_MAGIC ||
	    kframe->size != CRUNCH_STORAGE_SIZE)
		वापस -1;
	*auxp += CRUNCH_STORAGE_SIZE;
	crunch_task_restore(current_thपढ़ो_info(), &kframe->storage);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IWMMXT

अटल पूर्णांक preserve_iwmmxt_context(काष्ठा iwmmxt_sigframe __user *frame)
अणु
	अक्षर kbuf[माप(*frame) + 8];
	काष्ठा iwmmxt_sigframe *kframe;
	पूर्णांक err = 0;

	/* the iWMMXt context must be 64 bit aligned */
	kframe = (काष्ठा iwmmxt_sigframe *)((अचिन्हित दीर्घ)(kbuf + 8) & ~7);

	अगर (test_thपढ़ो_flag(TIF_USING_IWMMXT)) अणु
		kframe->magic = IWMMXT_MAGIC;
		kframe->size = IWMMXT_STORAGE_SIZE;
		iwmmxt_task_copy(current_thपढ़ो_info(), &kframe->storage);
	पूर्ण अन्यथा अणु
		/*
		 * For bug-compatibility with older kernels, some space
		 * has to be reserved क्रम iWMMXt even अगर it's not used.
		 * Set the magic and size appropriately so that properly
		 * written userspace can skip it reliably:
		 */
		*kframe = (काष्ठा iwmmxt_sigframe) अणु
			.magic = DUMMY_MAGIC,
			.size  = IWMMXT_STORAGE_SIZE,
		पूर्ण;
	पूर्ण

	err = __copy_to_user(frame, kframe, माप(*kframe));

	वापस err;
पूर्ण

अटल पूर्णांक restore_iwmmxt_context(अक्षर __user **auxp)
अणु
	काष्ठा iwmmxt_sigframe __user *frame =
		(काष्ठा iwmmxt_sigframe __user *)*auxp;
	अक्षर kbuf[माप(*frame) + 8];
	काष्ठा iwmmxt_sigframe *kframe;

	/* the iWMMXt context must be 64 bit aligned */
	kframe = (काष्ठा iwmmxt_sigframe *)((अचिन्हित दीर्घ)(kbuf + 8) & ~7);
	अगर (__copy_from_user(kframe, frame, माप(*frame)))
		वापस -1;

	/*
	 * For non-iWMMXt thपढ़ोs: a single iwmmxt_sigframe-sized dummy
	 * block is discarded क्रम compatibility with setup_sigframe() अगर
	 * present, but we करोn't mandate its presence.  If some other
	 * magic is here, it's not क्रम us:
	 */
	अगर (!test_thपढ़ो_flag(TIF_USING_IWMMXT) &&
	    kframe->magic != DUMMY_MAGIC)
		वापस 0;

	अगर (kframe->size != IWMMXT_STORAGE_SIZE)
		वापस -1;

	अगर (test_thपढ़ो_flag(TIF_USING_IWMMXT)) अणु
		अगर (kframe->magic != IWMMXT_MAGIC)
			वापस -1;

		iwmmxt_task_restore(current_thपढ़ो_info(), &kframe->storage);
	पूर्ण

	*auxp += IWMMXT_STORAGE_SIZE;
	वापस 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_VFP

अटल पूर्णांक preserve_vfp_context(काष्ठा vfp_sigframe __user *frame)
अणु
	काष्ठा vfp_sigframe kframe;
	पूर्णांक err = 0;

	स_रखो(&kframe, 0, माप(kframe));
	kframe.magic = VFP_MAGIC;
	kframe.size = VFP_STORAGE_SIZE;

	err = vfp_preserve_user_clear_hwstate(&kframe.ufp, &kframe.ufp_exc);
	अगर (err)
		वापस err;

	वापस __copy_to_user(frame, &kframe, माप(kframe));
पूर्ण

अटल पूर्णांक restore_vfp_context(अक्षर __user **auxp)
अणु
	काष्ठा vfp_sigframe frame;
	पूर्णांक err;

	err = __copy_from_user(&frame, *auxp, माप(frame));
	अगर (err)
		वापस err;

	अगर (frame.magic != VFP_MAGIC || frame.size != VFP_STORAGE_SIZE)
		वापस -EINVAL;

	*auxp += माप(frame);
	वापस vfp_restore_user_hwstate(&frame.ufp, &frame.ufp_exc);
पूर्ण

#पूर्ण_अगर

/*
 * Do a संकेत वापस; unकरो the संकेत stack.  These are aligned to 64-bit.
 */

अटल पूर्णांक restore_sigframe(काष्ठा pt_regs *regs, काष्ठा sigframe __user *sf)
अणु
	काष्ठा sigcontext context;
	अक्षर __user *aux;
	sigset_t set;
	पूर्णांक err;

	err = __copy_from_user(&set, &sf->uc.uc_sigmask, माप(set));
	अगर (err == 0)
		set_current_blocked(&set);

	err |= __copy_from_user(&context, &sf->uc.uc_mcontext, माप(context));
	अगर (err == 0) अणु
		regs->ARM_r0 = context.arm_r0;
		regs->ARM_r1 = context.arm_r1;
		regs->ARM_r2 = context.arm_r2;
		regs->ARM_r3 = context.arm_r3;
		regs->ARM_r4 = context.arm_r4;
		regs->ARM_r5 = context.arm_r5;
		regs->ARM_r6 = context.arm_r6;
		regs->ARM_r7 = context.arm_r7;
		regs->ARM_r8 = context.arm_r8;
		regs->ARM_r9 = context.arm_r9;
		regs->ARM_r10 = context.arm_r10;
		regs->ARM_fp = context.arm_fp;
		regs->ARM_ip = context.arm_ip;
		regs->ARM_sp = context.arm_sp;
		regs->ARM_lr = context.arm_lr;
		regs->ARM_pc = context.arm_pc;
		regs->ARM_cpsr = context.arm_cpsr;
	पूर्ण

	err |= !valid_user_regs(regs);

	aux = (अक्षर __user *) sf->uc.uc_regspace;
#अगर_घोषित CONFIG_CRUNCH
	अगर (err == 0)
		err |= restore_crunch_context(&aux);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IWMMXT
	अगर (err == 0)
		err |= restore_iwmmxt_context(&aux);
#पूर्ण_अगर
#अगर_घोषित CONFIG_VFP
	अगर (err == 0)
		err |= restore_vfp_context(&aux);
#पूर्ण_अगर

	वापस err;
पूर्ण

यंत्रlinkage पूर्णांक sys_sigवापस(काष्ठा pt_regs *regs)
अणु
	काष्ठा sigframe __user *frame;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/*
	 * Since we stacked the संकेत on a 64-bit boundary,
	 * then 'sp' should be word aligned here.  If it's
	 * not, then the user is trying to mess with us.
	 */
	अगर (regs->ARM_sp & 7)
		जाओ badframe;

	frame = (काष्ठा sigframe __user *)regs->ARM_sp;

	अगर (!access_ok(frame, माप (*frame)))
		जाओ badframe;

	अगर (restore_sigframe(regs, frame))
		जाओ badframe;

	वापस regs->ARM_r0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक sys_rt_sigवापस(काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/*
	 * Since we stacked the संकेत on a 64-bit boundary,
	 * then 'sp' should be word aligned here.  If it's
	 * not, then the user is trying to mess with us.
	 */
	अगर (regs->ARM_sp & 7)
		जाओ badframe;

	frame = (काष्ठा rt_sigframe __user *)regs->ARM_sp;

	अगर (!access_ok(frame, माप (*frame)))
		जाओ badframe;

	अगर (restore_sigframe(regs, &frame->sig))
		जाओ badframe;

	अगर (restore_altstack(&frame->sig.uc.uc_stack))
		जाओ badframe;

	वापस regs->ARM_r0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

अटल पूर्णांक
setup_sigframe(काष्ठा sigframe __user *sf, काष्ठा pt_regs *regs, sigset_t *set)
अणु
	काष्ठा aux_sigframe __user *aux;
	काष्ठा sigcontext context;
	पूर्णांक err = 0;

	context = (काष्ठा sigcontext) अणु
		.arm_r0        = regs->ARM_r0,
		.arm_r1        = regs->ARM_r1,
		.arm_r2        = regs->ARM_r2,
		.arm_r3        = regs->ARM_r3,
		.arm_r4        = regs->ARM_r4,
		.arm_r5        = regs->ARM_r5,
		.arm_r6        = regs->ARM_r6,
		.arm_r7        = regs->ARM_r7,
		.arm_r8        = regs->ARM_r8,
		.arm_r9        = regs->ARM_r9,
		.arm_r10       = regs->ARM_r10,
		.arm_fp        = regs->ARM_fp,
		.arm_ip        = regs->ARM_ip,
		.arm_sp        = regs->ARM_sp,
		.arm_lr        = regs->ARM_lr,
		.arm_pc        = regs->ARM_pc,
		.arm_cpsr      = regs->ARM_cpsr,

		.trap_no       = current->thपढ़ो.trap_no,
		.error_code    = current->thपढ़ो.error_code,
		.fault_address = current->thपढ़ो.address,
		.oldmask       = set->sig[0],
	पूर्ण;

	err |= __copy_to_user(&sf->uc.uc_mcontext, &context, माप(context));

	err |= __copy_to_user(&sf->uc.uc_sigmask, set, माप(*set));

	aux = (काष्ठा aux_sigframe __user *) sf->uc.uc_regspace;
#अगर_घोषित CONFIG_CRUNCH
	अगर (err == 0)
		err |= preserve_crunch_context(&aux->crunch);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IWMMXT
	अगर (err == 0)
		err |= preserve_iwmmxt_context(&aux->iwmmxt);
#पूर्ण_अगर
#अगर_घोषित CONFIG_VFP
	अगर (err == 0)
		err |= preserve_vfp_context(&aux->vfp);
#पूर्ण_अगर
	err |= __put_user(0, &aux->end_magic);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs, पूर्णांक framesize)
अणु
	अचिन्हित दीर्घ sp = sigsp(regs->ARM_sp, ksig);
	व्योम __user *frame;

	/*
	 * ATPCS B01 mandates 8-byte alignment
	 */
	frame = (व्योम __user *)((sp - framesize) & ~7);

	/*
	 * Check that we can actually ग_लिखो to the संकेत frame.
	 */
	अगर (!access_ok(frame, framesize))
		frame = शून्य;

	वापस frame;
पूर्ण

अटल पूर्णांक
setup_वापस(काष्ठा pt_regs *regs, काष्ठा kसंकेत *ksig,
	     अचिन्हित दीर्घ __user *rc, व्योम __user *frame)
अणु
	अचिन्हित दीर्घ handler = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;
	अचिन्हित दीर्घ handler_fdpic_GOT = 0;
	अचिन्हित दीर्घ retcode;
	अचिन्हित पूर्णांक idx, thumb = 0;
	अचिन्हित दीर्घ cpsr = regs->ARM_cpsr & ~(PSR_f | PSR_E_BIT);
	bool fdpic = IS_ENABLED(CONFIG_BINFMT_ELF_FDPIC) &&
		     (current->personality & FDPIC_FUNCPTRS);

	अगर (fdpic) अणु
		अचिन्हित दीर्घ __user *fdpic_func_desc =
					(अचिन्हित दीर्घ __user *)handler;
		अगर (__get_user(handler, &fdpic_func_desc[0]) ||
		    __get_user(handler_fdpic_GOT, &fdpic_func_desc[1]))
			वापस 1;
	पूर्ण

	cpsr |= PSR_ENDSTATE;

	/*
	 * Maybe we need to deliver a 32-bit संकेत to a 26-bit task.
	 */
	अगर (ksig->ka.sa.sa_flags & SA_THIRTYTWO)
		cpsr = (cpsr & ~MODE_MASK) | USR_MODE;

#अगर_घोषित CONFIG_ARM_THUMB
	अगर (elf_hwcap & HWCAP_THUMB) अणु
		/*
		 * The LSB of the handler determines अगर we're going to
		 * be using THUMB or ARM mode क्रम this संकेत handler.
		 */
		thumb = handler & 1;

		/*
		 * Clear the If-Then Thumb-2 execution state.  ARM spec
		 * requires this to be all 000s in ARM mode.  Snapdragon
		 * S4/Krait misbehaves on a Thumb=>ARM संकेत transition
		 * without this.
		 *
		 * We must करो this whenever we are running on a Thumb-2
		 * capable CPU, which includes ARMv6T2.  However, we elect
		 * to always करो this to simplअगरy the code; this field is
		 * marked UNK/SBZP क्रम older architectures.
		 */
		cpsr &= ~PSR_IT_MASK;

		अगर (thumb) अणु
			cpsr |= PSR_T_BIT;
		पूर्ण अन्यथा
			cpsr &= ~PSR_T_BIT;
	पूर्ण
#पूर्ण_अगर

	अगर (ksig->ka.sa.sa_flags & SA_RESTORER) अणु
		retcode = (अचिन्हित दीर्घ)ksig->ka.sa.sa_restorer;
		अगर (fdpic) अणु
			/*
			 * We need code to load the function descriptor.
			 * That code follows the standard sigवापस code
			 * (6 words), and is made of 3 + 2 words क्रम each
			 * variant. The 4th copied word is the actual FD
			 * address that the assembly code expects.
			 */
			idx = 6 + thumb * 3;
			अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
				idx += 5;
			अगर (__put_user(sigवापस_codes[idx],   rc  ) ||
			    __put_user(sigवापस_codes[idx+1], rc+1) ||
			    __put_user(sigवापस_codes[idx+2], rc+2) ||
			    __put_user(retcode,                rc+3))
				वापस 1;
			जाओ rc_finish;
		पूर्ण
	पूर्ण अन्यथा अणु
		idx = thumb << 1;
		अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
			idx += 3;

		/*
		 * Put the sigवापस code on the stack no matter which वापस
		 * mechanism we use in order to reमुख्य ABI compliant
		 */
		अगर (__put_user(sigवापस_codes[idx],   rc) ||
		    __put_user(sigवापस_codes[idx+1], rc+1))
			वापस 1;

rc_finish:
#अगर_घोषित CONFIG_MMU
		अगर (cpsr & MODE32_BIT) अणु
			काष्ठा mm_काष्ठा *mm = current->mm;

			/*
			 * 32-bit code can use the संकेत वापस page
			 * except when the MPU has रक्षित the vectors
			 * page from PL0
			 */
			retcode = mm->context.sigpage + संकेत_वापस_offset +
				  (idx << 2) + thumb;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			/*
			 * Ensure that the inकाष्ठाion cache sees
			 * the वापस code written onto the stack.
			 */
			flush_icache_range((अचिन्हित दीर्घ)rc,
					   (अचिन्हित दीर्घ)(rc + 3));

			retcode = ((अचिन्हित दीर्घ)rc) + thumb;
		पूर्ण
	पूर्ण

	regs->ARM_r0 = ksig->sig;
	regs->ARM_sp = (अचिन्हित दीर्घ)frame;
	regs->ARM_lr = retcode;
	regs->ARM_pc = handler;
	अगर (fdpic)
		regs->ARM_r9 = handler_fdpic_GOT;
	regs->ARM_cpsr = cpsr;

	वापस 0;
पूर्ण

अटल पूर्णांक
setup_frame(काष्ठा kसंकेत *ksig, sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा sigframe __user *frame = get_sigframe(ksig, regs, माप(*frame));
	पूर्णांक err = 0;

	अगर (!frame)
		वापस 1;

	/*
	 * Set uc.uc_flags to a value which sc.trap_no would never have.
	 */
	err = __put_user(0x5ac3c35a, &frame->uc.uc_flags);

	err |= setup_sigframe(frame, regs, set);
	अगर (err == 0)
		err = setup_वापस(regs, ksig, frame->retcode, frame);

	वापस err;
पूर्ण

अटल पूर्णांक
setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame = get_sigframe(ksig, regs, माप(*frame));
	पूर्णांक err = 0;

	अगर (!frame)
		वापस 1;

	err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	err |= __put_user(0, &frame->sig.uc.uc_flags);
	err |= __put_user(शून्य, &frame->sig.uc.uc_link);

	err |= __save_altstack(&frame->sig.uc.uc_stack, regs->ARM_sp);
	err |= setup_sigframe(&frame->sig, regs, set);
	अगर (err == 0)
		err = setup_वापस(regs, ksig, frame->sig.retcode, frame);

	अगर (err == 0) अणु
		/*
		 * For realसमय संकेतs we must also set the second and third
		 * arguments क्रम the संकेत handler.
		 *   -- Peter Maydell <pmaydell@chiark.greenend.org.uk> 2000-12-06
		 */
		regs->ARM_r1 = (अचिन्हित दीर्घ)&frame->info;
		regs->ARM_r2 = (अचिन्हित दीर्घ)&frame->sig.uc;
	पूर्ण

	वापस err;
पूर्ण

/*
 * OK, we're invoking a handler
 */	
अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक ret;

	/*
	 * Perक्रमm fixup क्रम the pre-संकेत frame.
	 */
	rseq_संकेत_deliver(ksig, regs);

	/*
	 * Set up the stack frame
	 */
	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		ret = setup_rt_frame(ksig, oldset, regs);
	अन्यथा
		ret = setup_frame(ksig, oldset, regs);

	/*
	 * Check that the resulting रेजिस्टरs are actually sane.
	 */
	ret |= !valid_user_regs(regs);

	संकेत_setup_करोne(ret, ksig, 0);
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
अटल पूर्णांक करो_संकेत(काष्ठा pt_regs *regs, पूर्णांक syscall)
अणु
	अचिन्हित पूर्णांक retval = 0, जारी_addr = 0, restart_addr = 0;
	काष्ठा kसंकेत ksig;
	पूर्णांक restart = 0;

	/*
	 * If we were from a प्रणाली call, check क्रम प्रणाली call restarting...
	 */
	अगर (syscall) अणु
		जारी_addr = regs->ARM_pc;
		restart_addr = जारी_addr - (thumb_mode(regs) ? 2 : 4);
		retval = regs->ARM_r0;

		/*
		 * Prepare क्रम प्रणाली call restart.  We करो this here so that a
		 * debugger will see the alपढ़ोy changed PSW.
		 */
		चयन (retval) अणु
		हाल -ERESTART_RESTARTBLOCK:
			restart -= 2;
			fallthrough;
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			restart++;
			regs->ARM_r0 = regs->ARM_ORIG_r0;
			regs->ARM_pc = restart_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Get the संकेत to deliver.  When running under ptrace, at this
	 * poपूर्णांक the debugger may change all our रेजिस्टरs ...
	 */
	/*
	 * Depending on the संकेत settings we may need to revert the
	 * decision to restart the प्रणाली call.  But skip this अगर a
	 * debugger has chosen to restart at a dअगरferent PC.
	 */
	अगर (get_संकेत(&ksig)) अणु
		/* handler */
		अगर (unlikely(restart) && regs->ARM_pc == restart_addr) अणु
			अगर (retval == -ERESTARTNOHAND ||
			    retval == -ERESTART_RESTARTBLOCK
			    || (retval == -ERESTARTSYS
				&& !(ksig.ka.sa.sa_flags & SA_RESTART))) अणु
				regs->ARM_r0 = -EINTR;
				regs->ARM_pc = जारी_addr;
			पूर्ण
		पूर्ण
		handle_संकेत(&ksig, regs);
	पूर्ण अन्यथा अणु
		/* no handler */
		restore_saved_sigmask();
		अगर (unlikely(restart) && regs->ARM_pc == restart_addr) अणु
			regs->ARM_pc = जारी_addr;
			वापस restart;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक
करो_work_pending(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक thपढ़ो_flags, पूर्णांक syscall)
अणु
	/*
	 * The assembly code enters us with IRQs off, but it hasn't
	 * inक्रमmed the tracing code of that क्रम efficiency reasons.
	 * Update the trace code with the current status.
	 */
	trace_hardirqs_off();
	करो अणु
		अगर (likely(thपढ़ो_flags & _TIF_NEED_RESCHED)) अणु
			schedule();
		पूर्ण अन्यथा अणु
			अगर (unlikely(!user_mode(regs)))
				वापस 0;
			local_irq_enable();
			अगर (thपढ़ो_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL)) अणु
				पूर्णांक restart = करो_संकेत(regs, syscall);
				अगर (unlikely(restart)) अणु
					/*
					 * Restart without handlers.
					 * Deal with it without leaving
					 * the kernel space.
					 */
					वापस restart;
				पूर्ण
				syscall = 0;
			पूर्ण अन्यथा अगर (thपढ़ो_flags & _TIF_UPROBE) अणु
				uprobe_notअगरy_resume(regs);
			पूर्ण अन्यथा अणु
				tracehook_notअगरy_resume(regs);
				rseq_handle_notअगरy_resume(शून्य, regs);
			पूर्ण
		पूर्ण
		local_irq_disable();
		thपढ़ो_flags = current_thपढ़ो_info()->flags;
	पूर्ण जबतक (thपढ़ो_flags & _TIF_WORK_MASK);
	वापस 0;
पूर्ण

काष्ठा page *get_संकेत_page(व्योम)
अणु
	अचिन्हित दीर्घ ptr;
	अचिन्हित offset;
	काष्ठा page *page;
	व्योम *addr;

	page = alloc_pages(GFP_KERNEL, 0);

	अगर (!page)
		वापस शून्य;

	addr = page_address(page);

	/* Poison the entire page */
	स_रखो32(addr, __opcode_to_mem_arm(0xe7fddef1),
		 PAGE_SIZE / माप(u32));

	/* Give the संकेत वापस code some अक्रमomness */
	offset = 0x200 + (get_अक्रमom_पूर्णांक() & 0x7fc);
	संकेत_वापस_offset = offset;

	/* Copy संकेत वापस handlers पूर्णांकo the page */
	स_नकल(addr + offset, sigवापस_codes, माप(sigवापस_codes));

	/* Flush out all inकाष्ठाions in this page */
	ptr = (अचिन्हित दीर्घ)addr;
	flush_icache_range(ptr, ptr + PAGE_SIZE);

	वापस page;
पूर्ण

/* Defer to generic check */
यंत्रlinkage व्योम addr_limit_check_failed(व्योम)
अणु
#अगर_घोषित CONFIG_MMU
	addr_limit_user_check();
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_DEBUG_RSEQ
यंत्रlinkage व्योम करो_rseq_syscall(काष्ठा pt_regs *regs)
अणु
	rseq_syscall(regs);
पूर्ण
#पूर्ण_अगर

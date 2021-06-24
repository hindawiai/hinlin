<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/sched/task.h>

#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fpu_emulator.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <linux/uaccess.h>

/**
 * काष्ठा emuframe - The 'emulation' frame काष्ठाure
 * @emul:	The inकाष्ठाion to 'emulate'.
 * @badinst:	A अवरोध inकाष्ठाion to cause a वापस to the kernel.
 *
 * This काष्ठाure defines the frames placed within the delay slot emulation
 * page in response to a call to mips_dsemul(). Each thपढ़ो may be allocated
 * only one frame at any given समय. The kernel stores within it the
 * inकाष्ठाion to be 'emulated' followed by a अवरोध inकाष्ठाion, then
 * executes the frame in user mode. The अवरोध causes a trap to the kernel
 * which leads to करो_dsemulret() being called unless the inकाष्ठाion in
 * @emul causes a trap itself, is a branch, or a संकेत is delivered to
 * the thपढ़ो. In these हालs the allocated frame will either be reused by
 * a subsequent delay slot 'emulation', or be मुक्तd during संकेत delivery or
 * upon thपढ़ो निकास.
 *
 * This approach is used because:
 *
 * - Actually emulating all inकाष्ठाions isn't feasible. We would need to
 *   be able to handle inकाष्ठाions from all revisions of the MIPS ISA,
 *   all ASEs & all venकरोr inकाष्ठाion set extensions. This would be a
 *   whole lot of work & continual मुख्यtenance burden as new inकाष्ठाions
 *   are पूर्णांकroduced, and in the हाल of some venकरोr extensions may not
 *   even be possible. Thus we need to take the approach of actually
 *   executing the inकाष्ठाion.
 *
 * - We must execute the inकाष्ठाion within user context. If we were to
 *   execute the inकाष्ठाion in kernel mode then it would have access to
 *   kernel resources without very careful checks, leaving us with a
 *   high potential क्रम security or stability issues to arise.
 *
 * - We used to place the frame on the users stack, but this requires
 *   that the stack be executable. This is bad क्रम security so the
 *   per-process page is now used instead.
 *
 * - The inकाष्ठाion in @emul may be something entirely invalid क्रम a
 *   delay slot. The user may (पूर्णांकentionally or otherwise) place a branch
 *   in a delay slot, or a kernel mode inकाष्ठाion, or something अन्यथा
 *   which generates an exception. Thus we can't rely upon the अवरोध in
 *   @badinst always being hit. For this reason we track the index of the
 *   frame allocated to each thपढ़ो, allowing us to clean it up at later
 *   poपूर्णांकs such as संकेत delivery or thपढ़ो निकास.
 *
 * - The user may generate a fake काष्ठा emuframe अगर they wish, invoking
 *   the BRK_MEMU अवरोध inकाष्ठाion themselves. We must thereक्रमe not
 *   trust that BRK_MEMU means there's actually a valid frame allocated
 *   to the thपढ़ो, and must not allow the user to करो anything they
 *   couldn't alपढ़ोy.
 */
काष्ठा emuframe अणु
	mips_inकाष्ठाion	emul;
	mips_inकाष्ठाion	badinst;
पूर्ण;

अटल स्थिर पूर्णांक emupage_frame_count = PAGE_SIZE / माप(काष्ठा emuframe);

अटल अंतरभूत __user काष्ठा emuframe *dsemul_page(व्योम)
अणु
	वापस (__user काष्ठा emuframe *)STACK_TOP;
पूर्ण

अटल पूर्णांक alloc_emuframe(व्योम)
अणु
	mm_context_t *mm_ctx = &current->mm->context;
	पूर्णांक idx;

retry:
	spin_lock(&mm_ctx->bd_emupage_lock);

	/* Ensure we have an allocation biपंचांगap */
	अगर (!mm_ctx->bd_emupage_allocmap) अणु
		mm_ctx->bd_emupage_allocmap =
			kसुस्मृति(BITS_TO_LONGS(emupage_frame_count),
					      माप(अचिन्हित दीर्घ),
				GFP_ATOMIC);

		अगर (!mm_ctx->bd_emupage_allocmap) अणु
			idx = BD_EMUFRAME_NONE;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/* Attempt to allocate a single bit/frame */
	idx = biपंचांगap_find_मुक्त_region(mm_ctx->bd_emupage_allocmap,
				      emupage_frame_count, 0);
	अगर (idx < 0) अणु
		/*
		 * Failed to allocate a frame. We'll रुको until one becomes
		 * available. We unlock the page so that other thपढ़ोs actually
		 * get the opportunity to मुक्त their frames, which means
		 * technically the result of biपंचांगap_full may be incorrect.
		 * However the worst हाल is that we repeat all this and end up
		 * back here again.
		 */
		spin_unlock(&mm_ctx->bd_emupage_lock);
		अगर (!रुको_event_समाप्तable(mm_ctx->bd_emupage_queue,
			!biपंचांगap_full(mm_ctx->bd_emupage_allocmap,
				     emupage_frame_count)))
			जाओ retry;

		/* Received a fatal संकेत - just give in */
		वापस BD_EMUFRAME_NONE;
	पूर्ण

	/* Success! */
	pr_debug("allocate emuframe %d to %d\n", idx, current->pid);
out_unlock:
	spin_unlock(&mm_ctx->bd_emupage_lock);
	वापस idx;
पूर्ण

अटल व्योम मुक्त_emuframe(पूर्णांक idx, काष्ठा mm_काष्ठा *mm)
अणु
	mm_context_t *mm_ctx = &mm->context;

	spin_lock(&mm_ctx->bd_emupage_lock);

	pr_debug("free emuframe %d from %d\n", idx, current->pid);
	biपंचांगap_clear(mm_ctx->bd_emupage_allocmap, idx, 1);

	/* If some thपढ़ो is रुकोing क्रम a frame, now's its chance */
	wake_up(&mm_ctx->bd_emupage_queue);

	spin_unlock(&mm_ctx->bd_emupage_lock);
पूर्ण

अटल bool within_emuframe(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)dsemul_page();

	अगर (regs->cp0_epc < base)
		वापस false;
	अगर (regs->cp0_epc >= (base + PAGE_SIZE))
		वापस false;

	वापस true;
पूर्ण

bool dsemul_thपढ़ो_cleanup(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक fr_idx;

	/* Clear any allocated frame, retrieving its index */
	fr_idx = atomic_xchg(&tsk->thपढ़ो.bd_emu_frame, BD_EMUFRAME_NONE);

	/* If no frame was allocated, we're करोne */
	अगर (fr_idx == BD_EMUFRAME_NONE)
		वापस false;

	task_lock(tsk);

	/* Free the frame that this thपढ़ो had allocated */
	अगर (tsk->mm)
		मुक्त_emuframe(fr_idx, tsk->mm);

	task_unlock(tsk);
	वापस true;
पूर्ण

bool dsemul_thपढ़ो_rollback(काष्ठा pt_regs *regs)
अणु
	काष्ठा emuframe __user *fr;
	पूर्णांक fr_idx;

	/* Do nothing अगर we're not executing from a frame */
	अगर (!within_emuframe(regs))
		वापस false;

	/* Find the frame being executed */
	fr_idx = atomic_पढ़ो(&current->thपढ़ो.bd_emu_frame);
	अगर (fr_idx == BD_EMUFRAME_NONE)
		वापस false;
	fr = &dsemul_page()[fr_idx];

	/*
	 * If the PC is at the emul inकाष्ठाion, roll back to the branch. If
	 * PC is at the badinst (अवरोध) inकाष्ठाion, we've alपढ़ोy emulated the
	 * inकाष्ठाion so progress to the जारी PC. If it's anything अन्यथा
	 * then something is amiss & the user has branched पूर्णांकo some other area
	 * of the emupage - we'll मुक्त the allocated frame anyway.
	 */
	अगर (msk_isa16_mode(regs->cp0_epc) == (अचिन्हित दीर्घ)&fr->emul)
		regs->cp0_epc = current->thपढ़ो.bd_emu_branch_pc;
	अन्यथा अगर (msk_isa16_mode(regs->cp0_epc) == (अचिन्हित दीर्घ)&fr->badinst)
		regs->cp0_epc = current->thपढ़ो.bd_emu_cont_pc;

	atomic_set(&current->thपढ़ो.bd_emu_frame, BD_EMUFRAME_NONE);
	मुक्त_emuframe(fr_idx, current->mm);
	वापस true;
पूर्ण

व्योम dsemul_mm_cleanup(काष्ठा mm_काष्ठा *mm)
अणु
	mm_context_t *mm_ctx = &mm->context;

	kमुक्त(mm_ctx->bd_emupage_allocmap);
पूर्ण

पूर्णांक mips_dsemul(काष्ठा pt_regs *regs, mips_inकाष्ठाion ir,
		अचिन्हित दीर्घ branch_pc, अचिन्हित दीर्घ cont_pc)
अणु
	पूर्णांक isa16 = get_isa16_mode(regs->cp0_epc);
	mips_inकाष्ठाion अवरोध_math;
	अचिन्हित दीर्घ fr_uaddr;
	काष्ठा emuframe fr;
	पूर्णांक fr_idx, ret;

	/* NOP is easy */
	अगर (ir == 0)
		वापस -1;

	/* microMIPS inकाष्ठाions */
	अगर (isa16) अणु
		जोड़ mips_inकाष्ठाion insn = अणु .word = ir पूर्ण;

		/* NOP16 aka MOVE16 $0, $0 */
		अगर ((ir >> 16) == MM_NOP16)
			वापस -1;

		/* ADDIUPC */
		अगर (insn.mm_a_क्रमmat.opcode == mm_addiupc_op) अणु
			अचिन्हित पूर्णांक rs;
			s32 v;

			rs = (((insn.mm_a_क्रमmat.rs + 0xe) & 0xf) + 2);
			v = regs->cp0_epc & ~3;
			v += insn.mm_a_क्रमmat.simmediate << 2;
			regs->regs[rs] = (दीर्घ)v;
			वापस -1;
		पूर्ण
	पूर्ण

	pr_debug("dsemul 0x%08lx cont at 0x%08lx\n", regs->cp0_epc, cont_pc);

	/* Allocate a frame अगर we करोn't alपढ़ोy have one */
	fr_idx = atomic_पढ़ो(&current->thपढ़ो.bd_emu_frame);
	अगर (fr_idx == BD_EMUFRAME_NONE)
		fr_idx = alloc_emuframe();
	अगर (fr_idx == BD_EMUFRAME_NONE)
		वापस SIGBUS;

	/* Retrieve the appropriately encoded अवरोध inकाष्ठाion */
	अवरोध_math = BREAK_MATH(isa16);

	/* Write the inकाष्ठाions to the frame */
	अगर (isa16) अणु
		जोड़ mips_inकाष्ठाion _emul = अणु
			.halfword = अणु ir >> 16, ir पूर्ण
		पूर्ण;
		जोड़ mips_inकाष्ठाion _badinst = अणु
			.halfword = अणु अवरोध_math >> 16, अवरोध_math पूर्ण
		पूर्ण;

		fr.emul = _emul.word;
		fr.badinst = _badinst.word;
	पूर्ण अन्यथा अणु
		fr.emul = ir;
		fr.badinst = अवरोध_math;
	पूर्ण

	/* Write the frame to user memory */
	fr_uaddr = (अचिन्हित दीर्घ)&dsemul_page()[fr_idx];
	ret = access_process_vm(current, fr_uaddr, &fr, माप(fr),
				FOLL_FORCE | FOLL_WRITE);
	अगर (unlikely(ret != माप(fr))) अणु
		MIPS_FPU_EMU_INC_STATS(errors);
		मुक्त_emuframe(fr_idx, current->mm);
		वापस SIGBUS;
	पूर्ण

	/* Record the PC of the branch, PC to जारी from & frame index */
	current->thपढ़ो.bd_emu_branch_pc = branch_pc;
	current->thपढ़ो.bd_emu_cont_pc = cont_pc;
	atomic_set(&current->thपढ़ो.bd_emu_frame, fr_idx);

	/* Change user रेजिस्टर context to execute the frame */
	regs->cp0_epc = fr_uaddr | isa16;

	वापस 0;
पूर्ण

bool करो_dsemulret(काष्ठा pt_regs *xcp)
अणु
	/* Cleanup the allocated frame, वापसing अगर there wasn't one */
	अगर (!dsemul_thपढ़ो_cleanup(current)) अणु
		MIPS_FPU_EMU_INC_STATS(errors);
		वापस false;
	पूर्ण

	/* Set EPC to वापस to post-branch inकाष्ठाion */
	xcp->cp0_epc = current->thपढ़ो.bd_emu_cont_pc;
	pr_debug("dsemulret to 0x%08lx\n", xcp->cp0_epc);
	MIPS_FPU_EMU_INC_STATS(ds_emul);
	वापस true;
पूर्ण

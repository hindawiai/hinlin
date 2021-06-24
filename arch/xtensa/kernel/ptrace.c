<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2007  Tensilica Inc.
 *
 * Joe Taylor	<joe@tensilica.com, joetylr@yahoo.com>
 * Chris Zankel <chris@zankel.net>
 * Scott Foehner<sfoehner@yahoo.com>,
 * Kevin Chea
 * Marc Gauthier<marc@tensilica.com> <marc@alumni.uwaterloo.ca>
 */

#समावेश <linux/audit.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/regset.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/security.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/uaccess.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

#समावेश <यंत्र/coprocessor.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>

अटल पूर्णांक gpr_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	काष्ठा user_pt_regs newregs = अणु
		.pc = regs->pc,
		.ps = regs->ps & ~(1 << PS_EXCM_BIT),
		.lbeg = regs->lbeg,
		.lend = regs->lend,
		.lcount = regs->lcount,
		.sar = regs->sar,
		.thपढ़ोptr = regs->thपढ़ोptr,
		.winकरोwbase = regs->winकरोwbase,
		.winकरोwstart = regs->winकरोwstart,
		.syscall = regs->syscall,
	पूर्ण;

	स_नकल(newregs.a,
	       regs->areg + XCHAL_NUM_AREGS - regs->winकरोwbase * 4,
	       regs->winकरोwbase * 16);
	स_नकल(newregs.a + regs->winकरोwbase * 4,
	       regs->areg,
	       (WSBITS - regs->winकरोwbase) * 16);

	वापस membuf_ग_लिखो(&to, &newregs, माप(newregs));
पूर्ण

अटल पूर्णांक gpr_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा user_pt_regs newregs = अणु0पूर्ण;
	काष्ठा pt_regs *regs;
	स्थिर u32 ps_mask = PS_CALLINC_MASK | PS_OWB_MASK;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &newregs, 0, -1);
	अगर (ret)
		वापस ret;

	अगर (newregs.winकरोwbase >= XCHAL_NUM_AREGS / 4)
		वापस -EINVAL;

	regs = task_pt_regs(target);
	regs->pc = newregs.pc;
	regs->ps = (regs->ps & ~ps_mask) | (newregs.ps & ps_mask);
	regs->lbeg = newregs.lbeg;
	regs->lend = newregs.lend;
	regs->lcount = newregs.lcount;
	regs->sar = newregs.sar;
	regs->thपढ़ोptr = newregs.thपढ़ोptr;

	अगर (newregs.syscall)
		regs->syscall = newregs.syscall;

	अगर (newregs.winकरोwbase != regs->winकरोwbase ||
	    newregs.winकरोwstart != regs->winकरोwstart) अणु
		u32 rotws, wmask;

		rotws = (((newregs.winकरोwstart |
			   (newregs.winकरोwstart << WSBITS)) >>
			  newregs.winकरोwbase) &
			 ((1 << WSBITS) - 1)) & ~1;
		wmask = ((rotws ? WSBITS + 1 - ffs(rotws) : 0) << 4) |
			(rotws & 0xF) | 1;
		regs->winकरोwbase = newregs.winकरोwbase;
		regs->winकरोwstart = newregs.winकरोwstart;
		regs->wmask = wmask;
	पूर्ण

	स_नकल(regs->areg + XCHAL_NUM_AREGS - newregs.winकरोwbase * 4,
	       newregs.a, newregs.winकरोwbase * 16);
	स_नकल(regs->areg, newregs.a + newregs.winकरोwbase * 4,
	       (WSBITS - newregs.winकरोwbase) * 16);

	वापस 0;
पूर्ण

अटल पूर्णांक tie_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	पूर्णांक ret;
	काष्ठा pt_regs *regs = task_pt_regs(target);
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(target);
	elf_xtregs_t *newregs = kzalloc(माप(elf_xtregs_t), GFP_KERNEL);

	अगर (!newregs)
		वापस -ENOMEM;

	newregs->opt = regs->xtregs_opt;
	newregs->user = ti->xtregs_user;

#अगर XTENSA_HAVE_COPROCESSORS
	/* Flush all coprocessor रेजिस्टरs to memory. */
	coprocessor_flush_all(ti);
	newregs->cp0 = ti->xtregs_cp.cp0;
	newregs->cp1 = ti->xtregs_cp.cp1;
	newregs->cp2 = ti->xtregs_cp.cp2;
	newregs->cp3 = ti->xtregs_cp.cp3;
	newregs->cp4 = ti->xtregs_cp.cp4;
	newregs->cp5 = ti->xtregs_cp.cp5;
	newregs->cp6 = ti->xtregs_cp.cp6;
	newregs->cp7 = ti->xtregs_cp.cp7;
#पूर्ण_अगर
	ret = membuf_ग_लिखो(&to, newregs, माप(*newregs));
	kमुक्त(newregs);
	वापस ret;
पूर्ण

अटल पूर्णांक tie_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा pt_regs *regs = task_pt_regs(target);
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(target);
	elf_xtregs_t *newregs = kzalloc(माप(elf_xtregs_t), GFP_KERNEL);

	अगर (!newregs)
		वापस -ENOMEM;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 newregs, 0, -1);

	अगर (ret)
		जाओ निकास;
	regs->xtregs_opt = newregs->opt;
	ti->xtregs_user = newregs->user;

#अगर XTENSA_HAVE_COPROCESSORS
	/* Flush all coprocessors beक्रमe we overग_लिखो them. */
	coprocessor_flush_all(ti);
	coprocessor_release_all(ti);
	ti->xtregs_cp.cp0 = newregs->cp0;
	ti->xtregs_cp.cp1 = newregs->cp1;
	ti->xtregs_cp.cp2 = newregs->cp2;
	ti->xtregs_cp.cp3 = newregs->cp3;
	ti->xtregs_cp.cp4 = newregs->cp4;
	ti->xtregs_cp.cp5 = newregs->cp5;
	ti->xtregs_cp.cp6 = newregs->cp6;
	ti->xtregs_cp.cp7 = newregs->cp7;
#पूर्ण_अगर
निकास:
	kमुक्त(newregs);
	वापस ret;
पूर्ण

क्रमागत xtensa_regset अणु
	REGSET_GPR,
	REGSET_TIE,
पूर्ण;

अटल स्थिर काष्ठा user_regset xtensa_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = माप(काष्ठा user_pt_regs) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = gpr_get,
		.set = gpr_set,
	पूर्ण,
	[REGSET_TIE] = अणु
		.core_note_type = NT_PRFPREG,
		.n = माप(elf_xtregs_t) / माप(u32),
		.size = माप(u32),
		.align = माप(u32),
		.regset_get = tie_get,
		.set = tie_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_xtensa_view = अणु
	.name = "xtensa",
	.e_machine = EM_XTENSA,
	.regsets = xtensa_regsets,
	.n = ARRAY_SIZE(xtensa_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &user_xtensa_view;
पूर्ण

व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	child->ptrace |= PT_SINGLESTEP;
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	child->ptrace &= ~PT_SINGLESTEP;
पूर्ण

/*
 * Called by kernel/ptrace.c when detaching to disable single stepping.
 */

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/* Nothing to करो.. */
पूर्ण

अटल पूर्णांक ptrace_getregs(काष्ठा task_काष्ठा *child, व्योम __user *uregs)
अणु
	वापस copy_regset_to_user(child, &user_xtensa_view, REGSET_GPR,
				   0, माप(xtensa_gregset_t), uregs);
पूर्ण

अटल पूर्णांक ptrace_setregs(काष्ठा task_काष्ठा *child, व्योम __user *uregs)
अणु
	वापस copy_regset_from_user(child, &user_xtensa_view, REGSET_GPR,
				     0, माप(xtensa_gregset_t), uregs);
पूर्ण

अटल पूर्णांक ptrace_getxregs(काष्ठा task_काष्ठा *child, व्योम __user *uregs)
अणु
	वापस copy_regset_to_user(child, &user_xtensa_view, REGSET_TIE,
				   0, माप(elf_xtregs_t), uregs);
पूर्ण

अटल पूर्णांक ptrace_setxregs(काष्ठा task_काष्ठा *child, व्योम __user *uregs)
अणु
	वापस copy_regset_from_user(child, &user_xtensa_view, REGSET_TIE,
				     0, माप(elf_xtregs_t), uregs);
पूर्ण

अटल पूर्णांक ptrace_peekusr(काष्ठा task_काष्ठा *child, दीर्घ regno,
			  दीर्घ __user *ret)
अणु
	काष्ठा pt_regs *regs;
	अचिन्हित दीर्घ पंचांगp;

	regs = task_pt_regs(child);
	पंचांगp = 0;  /* Default वापस value. */

	चयन(regno) अणु
	हाल REG_AR_BASE ... REG_AR_BASE + XCHAL_NUM_AREGS - 1:
		पंचांगp = regs->areg[regno - REG_AR_BASE];
		अवरोध;

	हाल REG_A_BASE ... REG_A_BASE + 15:
		पंचांगp = regs->areg[regno - REG_A_BASE];
		अवरोध;

	हाल REG_PC:
		पंचांगp = regs->pc;
		अवरोध;

	हाल REG_PS:
		/* Note: PS.EXCM is not set जबतक user task is running;
		 * its being set in regs is क्रम exception handling
		 * convenience.
		 */
		पंचांगp = (regs->ps & ~(1 << PS_EXCM_BIT));
		अवरोध;

	हाल REG_WB:
		अवरोध;		/* पंचांगp = 0 */

	हाल REG_WS:
		अणु
			अचिन्हित दीर्घ wb = regs->winकरोwbase;
			अचिन्हित दीर्घ ws = regs->winकरोwstart;
			पंचांगp = ((ws >> wb) | (ws << (WSBITS - wb))) &
				((1 << WSBITS) - 1);
			अवरोध;
		पूर्ण
	हाल REG_LBEG:
		पंचांगp = regs->lbeg;
		अवरोध;

	हाल REG_LEND:
		पंचांगp = regs->lend;
		अवरोध;

	हाल REG_LCOUNT:
		पंचांगp = regs->lcount;
		अवरोध;

	हाल REG_SAR:
		पंचांगp = regs->sar;
		अवरोध;

	हाल SYSCALL_NR:
		पंचांगp = regs->syscall;
		अवरोध;

	शेष:
		वापस -EIO;
	पूर्ण
	वापस put_user(पंचांगp, ret);
पूर्ण

अटल पूर्णांक ptrace_pokeusr(काष्ठा task_काष्ठा *child, दीर्घ regno, दीर्घ val)
अणु
	काष्ठा pt_regs *regs;
	regs = task_pt_regs(child);

	चयन (regno) अणु
	हाल REG_AR_BASE ... REG_AR_BASE + XCHAL_NUM_AREGS - 1:
		regs->areg[regno - REG_AR_BASE] = val;
		अवरोध;

	हाल REG_A_BASE ... REG_A_BASE + 15:
		regs->areg[regno - REG_A_BASE] = val;
		अवरोध;

	हाल REG_PC:
		regs->pc = val;
		अवरोध;

	हाल SYSCALL_NR:
		regs->syscall = val;
		अवरोध;

	शेष:
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
अटल व्योम ptrace_hbptriggered(काष्ठा perf_event *bp,
				काष्ठा perf_sample_data *data,
				काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	काष्ठा arch_hw_अवरोधpoपूर्णांक *bkpt = counter_arch_bp(bp);

	अगर (bp->attr.bp_type & HW_BREAKPOINT_X) अणु
		क्रम (i = 0; i < XCHAL_NUM_IBREAK; ++i)
			अगर (current->thपढ़ो.ptrace_bp[i] == bp)
				अवरोध;
		i <<= 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < XCHAL_NUM_DBREAK; ++i)
			अगर (current->thपढ़ो.ptrace_wp[i] == bp)
				अवरोध;
		i = (i << 1) | 1;
	पूर्ण

	क्रमce_sig_ptrace_त्रुटि_सं_trap(i, (व्योम __user *)bkpt->address);
पूर्ण

अटल काष्ठा perf_event *ptrace_hbp_create(काष्ठा task_काष्ठा *tsk, पूर्णांक type)
अणु
	काष्ठा perf_event_attr attr;

	ptrace_अवरोधpoपूर्णांक_init(&attr);

	/* Initialise fields to sane शेषs. */
	attr.bp_addr	= 0;
	attr.bp_len	= 1;
	attr.bp_type	= type;
	attr.disabled	= 1;

	वापस रेजिस्टर_user_hw_अवरोधpoपूर्णांक(&attr, ptrace_hbptriggered, शून्य,
					   tsk);
पूर्ण

/*
 * Address bit 0 choose inकाष्ठाion (0) or data (1) अवरोध रेजिस्टर, bits
 * 31..1 are the रेजिस्टर number.
 * Both PTRACE_GETHBPREGS and PTRACE_SETHBPREGS transfer two 32-bit words:
 * address (0) and control (1).
 * Inकाष्ठाion अवरोधpoपूर्णांक contorl word is 0 to clear अवरोधpoपूर्णांक, 1 to set.
 * Data अवरोधpoपूर्णांक control word bit 31 is 'trigger on store', bit 30 is
 * 'trigger on load, bits 29..0 are length. Length 0 is used to clear a
 * अवरोधpoपूर्णांक. To set a अवरोधpoपूर्णांक length must be a घातer of 2 in the range
 * 1..64 and the address must be length-aligned.
 */

अटल दीर्घ ptrace_gethbpregs(काष्ठा task_काष्ठा *child, दीर्घ addr,
			      दीर्घ __user *datap)
अणु
	काष्ठा perf_event *bp;
	u32 user_data[2] = अणु0पूर्ण;
	bool dअवरोध = addr & 1;
	अचिन्हित idx = addr >> 1;

	अगर ((!dअवरोध && idx >= XCHAL_NUM_IBREAK) ||
	    (dअवरोध && idx >= XCHAL_NUM_DBREAK))
		वापस -EINVAL;

	अगर (dअवरोध)
		bp = child->thपढ़ो.ptrace_wp[idx];
	अन्यथा
		bp = child->thपढ़ो.ptrace_bp[idx];

	अगर (bp) अणु
		user_data[0] = bp->attr.bp_addr;
		user_data[1] = bp->attr.disabled ? 0 : bp->attr.bp_len;
		अगर (dअवरोध) अणु
			अगर (bp->attr.bp_type & HW_BREAKPOINT_R)
				user_data[1] |= DBREAKC_LOAD_MASK;
			अगर (bp->attr.bp_type & HW_BREAKPOINT_W)
				user_data[1] |= DBREAKC_STOR_MASK;
		पूर्ण
	पूर्ण

	अगर (copy_to_user(datap, user_data, माप(user_data)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ ptrace_sethbpregs(काष्ठा task_काष्ठा *child, दीर्घ addr,
			      दीर्घ __user *datap)
अणु
	काष्ठा perf_event *bp;
	काष्ठा perf_event_attr attr;
	u32 user_data[2];
	bool dअवरोध = addr & 1;
	अचिन्हित idx = addr >> 1;
	पूर्णांक bp_type = 0;

	अगर ((!dअवरोध && idx >= XCHAL_NUM_IBREAK) ||
	    (dअवरोध && idx >= XCHAL_NUM_DBREAK))
		वापस -EINVAL;

	अगर (copy_from_user(user_data, datap, माप(user_data)))
		वापस -EFAULT;

	अगर (dअवरोध) अणु
		bp = child->thपढ़ो.ptrace_wp[idx];
		अगर (user_data[1] & DBREAKC_LOAD_MASK)
			bp_type |= HW_BREAKPOINT_R;
		अगर (user_data[1] & DBREAKC_STOR_MASK)
			bp_type |= HW_BREAKPOINT_W;
	पूर्ण अन्यथा अणु
		bp = child->thपढ़ो.ptrace_bp[idx];
		bp_type = HW_BREAKPOINT_X;
	पूर्ण

	अगर (!bp) अणु
		bp = ptrace_hbp_create(child,
				       bp_type ? bp_type : HW_BREAKPOINT_RW);
		अगर (IS_ERR(bp))
			वापस PTR_ERR(bp);
		अगर (dअवरोध)
			child->thपढ़ो.ptrace_wp[idx] = bp;
		अन्यथा
			child->thपढ़ो.ptrace_bp[idx] = bp;
	पूर्ण

	attr = bp->attr;
	attr.bp_addr = user_data[0];
	attr.bp_len = user_data[1] & ~(DBREAKC_LOAD_MASK | DBREAKC_STOR_MASK);
	attr.bp_type = bp_type;
	attr.disabled = !attr.bp_len;

	वापस modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
पूर्ण
#पूर्ण_अगर

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret = -EPERM;
	व्योम __user *datap = (व्योम __user *) data;

	चयन (request) अणु
	हाल PTRACE_PEEKUSR:	/* पढ़ो रेजिस्टर specअगरied by addr. */
		ret = ptrace_peekusr(child, addr, datap);
		अवरोध;

	हाल PTRACE_POKEUSR:	/* ग_लिखो रेजिस्टर specअगरied by addr. */
		ret = ptrace_pokeusr(child, addr, data);
		अवरोध;

	हाल PTRACE_GETREGS:
		ret = ptrace_getregs(child, datap);
		अवरोध;

	हाल PTRACE_SETREGS:
		ret = ptrace_setregs(child, datap);
		अवरोध;

	हाल PTRACE_GETXTREGS:
		ret = ptrace_getxregs(child, datap);
		अवरोध;

	हाल PTRACE_SETXTREGS:
		ret = ptrace_setxregs(child, datap);
		अवरोध;
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	हाल PTRACE_GETHBPREGS:
		ret = ptrace_gethbpregs(child, addr, datap);
		अवरोध;

	हाल PTRACE_SETHBPREGS:
		ret = ptrace_sethbpregs(child, addr, datap);
		अवरोध;
#पूर्ण_अगर
	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs);
पूर्णांक करो_syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	अगर (regs->syscall == NO_SYSCALL)
		regs->areg[2] = -ENOSYS;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE) &&
	    tracehook_report_syscall_entry(regs)) अणु
		regs->areg[2] = -ENOSYS;
		regs->syscall = NO_SYSCALL;
		वापस 0;
	पूर्ण

	अगर (regs->syscall == NO_SYSCALL ||
	    secure_computing() == -1) अणु
		करो_syscall_trace_leave(regs);
		वापस 0;
	पूर्ण

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_enter(regs, syscall_get_nr(current, regs));

	audit_syscall_entry(regs->syscall, regs->areg[6],
			    regs->areg[3], regs->areg[4],
			    regs->areg[5]);
	वापस 1;
पूर्ण

व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	पूर्णांक step;

	audit_syscall_निकास(regs);

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_निकास(regs, regs_वापस_value(regs));

	step = test_thपढ़ो_flag(TIF_SINGLESTEP);

	अगर (step || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, step);
पूर्ण

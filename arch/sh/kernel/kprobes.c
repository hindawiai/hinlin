<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Kernel probes (kprobes) क्रम SuperH
 *
 * Copyright (C) 2007 Chris Smith <chris.smith@st.com>
 * Copyright (C) 2006 Lineo Solutions, Inc.
 */
#समावेश <linux/kprobes.h>
#समावेश <linux/extable.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/preempt.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/uaccess.h>

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

अटल DEFINE_PER_CPU(काष्ठा kprobe, saved_current_opcode);
अटल DEFINE_PER_CPU(काष्ठा kprobe, saved_next_opcode);
अटल DEFINE_PER_CPU(काष्ठा kprobe, saved_next_opcode2);

#घोषणा OPCODE_JMP(x)	(((x) & 0xF0FF) == 0x402b)
#घोषणा OPCODE_JSR(x)	(((x) & 0xF0FF) == 0x400b)
#घोषणा OPCODE_BRA(x)	(((x) & 0xF000) == 0xa000)
#घोषणा OPCODE_BRAF(x)	(((x) & 0xF0FF) == 0x0023)
#घोषणा OPCODE_BSR(x)	(((x) & 0xF000) == 0xb000)
#घोषणा OPCODE_BSRF(x)	(((x) & 0xF0FF) == 0x0003)

#घोषणा OPCODE_BF_S(x)	(((x) & 0xFF00) == 0x8f00)
#घोषणा OPCODE_BT_S(x)	(((x) & 0xFF00) == 0x8d00)

#घोषणा OPCODE_BF(x)	(((x) & 0xFF00) == 0x8b00)
#घोषणा OPCODE_BT(x)	(((x) & 0xFF00) == 0x8900)

#घोषणा OPCODE_RTS(x)	(((x) & 0x000F) == 0x000b)
#घोषणा OPCODE_RTE(x)	(((x) & 0xFFFF) == 0x002b)

पूर्णांक __kprobes arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	kprobe_opcode_t opcode = *(kprobe_opcode_t *) (p->addr);

	अगर (OPCODE_RTE(opcode))
		वापस -EFAULT;	/* Bad अवरोधpoपूर्णांक */

	p->opcode = opcode;

	वापस 0;
पूर्ण

व्योम __kprobes arch_copy_kprobe(काष्ठा kprobe *p)
अणु
	स_नकल(p->ainsn.insn, p->addr, MAX_INSN_SIZE * माप(kprobe_opcode_t));
	p->opcode = *p->addr;
पूर्ण

व्योम __kprobes arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	*p->addr = BREAKPOINT_INSTRUCTION;
	flush_icache_range((अचिन्हित दीर्घ)p->addr,
			   (अचिन्हित दीर्घ)p->addr + माप(kprobe_opcode_t));
पूर्ण

व्योम __kprobes arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	*p->addr = p->opcode;
	flush_icache_range((अचिन्हित दीर्घ)p->addr,
			   (अचिन्हित दीर्घ)p->addr + माप(kprobe_opcode_t));
पूर्ण

पूर्णांक __kprobes arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	अगर (*p->addr == BREAKPOINT_INSTRUCTION)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * If an illegal slot inकाष्ठाion exception occurs क्रम an address
 * containing a kprobe, हटाओ the probe.
 *
 * Returns 0 अगर the exception was handled successfully, 1 otherwise.
 */
पूर्णांक __kprobes kprobe_handle_illslot(अचिन्हित दीर्घ pc)
अणु
	काष्ठा kprobe *p = get_kprobe((kprobe_opcode_t *) pc + 1);

	अगर (p != शून्य) अणु
		prपूर्णांकk("Warning: removing kprobe from delay slot: 0x%.8x\n",
		       (अचिन्हित पूर्णांक)pc + 2);
		unरेजिस्टर_kprobe(p);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

व्योम __kprobes arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *saved = this_cpu_ptr(&saved_next_opcode);

	अगर (saved->addr) अणु
		arch_disarm_kprobe(p);
		arch_disarm_kprobe(saved);

		saved->addr = शून्य;
		saved->opcode = 0;

		saved = this_cpu_ptr(&saved_next_opcode2);
		अगर (saved->addr) अणु
			arch_disarm_kprobe(saved);

			saved->addr = शून्य;
			saved->opcode = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __kprobes save_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	kcb->prev_kprobe.kp = kprobe_running();
	kcb->prev_kprobe.status = kcb->kprobe_status;
पूर्ण

अटल व्योम __kprobes restore_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, kcb->prev_kprobe.kp);
	kcb->kprobe_status = kcb->prev_kprobe.status;
पूर्ण

अटल व्योम __kprobes set_current_kprobe(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
					 काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, p);
पूर्ण

/*
 * Singlestep is implemented by disabling the current kprobe and setting one
 * on the next inकाष्ठाion, following branches. Two probes are set अगर the
 * branch is conditional.
 */
अटल व्योम __kprobes prepare_singlestep(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	__this_cpu_ग_लिखो(saved_current_opcode.addr, (kprobe_opcode_t *)regs->pc);

	अगर (p != शून्य) अणु
		काष्ठा kprobe *op1, *op2;

		arch_disarm_kprobe(p);

		op1 = this_cpu_ptr(&saved_next_opcode);
		op2 = this_cpu_ptr(&saved_next_opcode2);

		अगर (OPCODE_JSR(p->opcode) || OPCODE_JMP(p->opcode)) अणु
			अचिन्हित पूर्णांक reg_nr = ((p->opcode >> 8) & 0x000F);
			op1->addr = (kprobe_opcode_t *) regs->regs[reg_nr];
		पूर्ण अन्यथा अगर (OPCODE_BRA(p->opcode) || OPCODE_BSR(p->opcode)) अणु
			अचिन्हित दीर्घ disp = (p->opcode & 0x0FFF);
			op1->addr =
			    (kprobe_opcode_t *) (regs->pc + 4 + disp * 2);

		पूर्ण अन्यथा अगर (OPCODE_BRAF(p->opcode) || OPCODE_BSRF(p->opcode)) अणु
			अचिन्हित पूर्णांक reg_nr = ((p->opcode >> 8) & 0x000F);
			op1->addr =
			    (kprobe_opcode_t *) (regs->pc + 4 +
						 regs->regs[reg_nr]);

		पूर्ण अन्यथा अगर (OPCODE_RTS(p->opcode)) अणु
			op1->addr = (kprobe_opcode_t *) regs->pr;

		पूर्ण अन्यथा अगर (OPCODE_BF(p->opcode) || OPCODE_BT(p->opcode)) अणु
			अचिन्हित दीर्घ disp = (p->opcode & 0x00FF);
			/* हाल 1 */
			op1->addr = p->addr + 1;
			/* हाल 2 */
			op2->addr =
			    (kprobe_opcode_t *) (regs->pc + 4 + disp * 2);
			op2->opcode = *(op2->addr);
			arch_arm_kprobe(op2);

		पूर्ण अन्यथा अगर (OPCODE_BF_S(p->opcode) || OPCODE_BT_S(p->opcode)) अणु
			अचिन्हित दीर्घ disp = (p->opcode & 0x00FF);
			/* हाल 1 */
			op1->addr = p->addr + 2;
			/* हाल 2 */
			op2->addr =
			    (kprobe_opcode_t *) (regs->pc + 4 + disp * 2);
			op2->opcode = *(op2->addr);
			arch_arm_kprobe(op2);

		पूर्ण अन्यथा अणु
			op1->addr = p->addr + 1;
		पूर्ण

		op1->opcode = *(op1->addr);
		arch_arm_kprobe(op1);
	पूर्ण
पूर्ण

/* Called with kretprobe_lock held */
व्योम __kprobes arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				      काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *) regs->pr;
	ri->fp = शून्य;

	/* Replace the वापस addr with trampoline addr */
	regs->pr = (अचिन्हित दीर्घ)kretprobe_trampoline;
पूर्ण

अटल पूर्णांक __kprobes kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *p;
	पूर्णांक ret = 0;
	kprobe_opcode_t *addr = शून्य;
	काष्ठा kprobe_ctlblk *kcb;

	/*
	 * We करोn't want to be preempted क्रम the entire
	 * duration of kprobe processing
	 */
	preempt_disable();
	kcb = get_kprobe_ctlblk();

	addr = (kprobe_opcode_t *) (regs->pc);

	/* Check we're not actually recursing */
	अगर (kprobe_running()) अणु
		p = get_kprobe(addr);
		अगर (p) अणु
			अगर (kcb->kprobe_status == KPROBE_HIT_SS &&
			    *p->ainsn.insn == BREAKPOINT_INSTRUCTION) अणु
				जाओ no_kprobe;
			पूर्ण
			/* We have reentered the kprobe_handler(), since
			 * another probe was hit जबतक within the handler.
			 * We here save the original kprobes variables and
			 * just single step on the inकाष्ठाion of the new probe
			 * without calling any user handlers.
			 */
			save_previous_kprobe(kcb);
			set_current_kprobe(p, regs, kcb);
			kprobes_inc_nmissed_count(p);
			prepare_singlestep(p, regs);
			kcb->kprobe_status = KPROBE_REENTER;
			वापस 1;
		पूर्ण
		जाओ no_kprobe;
	पूर्ण

	p = get_kprobe(addr);
	अगर (!p) अणु
		/* Not one of ours: let kernel handle it */
		अगर (*(kprobe_opcode_t *)addr != BREAKPOINT_INSTRUCTION) अणु
			/*
			 * The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd right
			 * after we hit it. Another cpu has हटाओd
			 * either a probepoपूर्णांक or a debugger अवरोधpoपूर्णांक
			 * at this address. In either हाल, no further
			 * handling of this पूर्णांकerrupt is appropriate.
			 */
			ret = 1;
		पूर्ण

		जाओ no_kprobe;
	पूर्ण

	set_current_kprobe(p, regs, kcb);
	kcb->kprobe_status = KPROBE_HIT_ACTIVE;

	अगर (p->pre_handler && p->pre_handler(p, regs)) अणु
		/* handler has alपढ़ोy set things up, so skip ss setup */
		reset_current_kprobe();
		preempt_enable_no_resched();
		वापस 1;
	पूर्ण

	prepare_singlestep(p, regs);
	kcb->kprobe_status = KPROBE_HIT_SS;
	वापस 1;

no_kprobe:
	preempt_enable_no_resched();
	वापस ret;
पूर्ण

/*
 * For function-वापस probes, init_kprobes() establishes a probepoपूर्णांक
 * here. When a retprobed function वापसs, this probe is hit and
 * trampoline_probe_handler() runs, calling the kretprobe's handler.
 */
अटल व्योम __used kretprobe_trampoline_holder(व्योम)
अणु
	यंत्र अस्थिर (".globl kretprobe_trampoline\n"
		      "kretprobe_trampoline:\n\t"
		      "nop\n");
पूर्ण

/*
 * Called when we hit the probe poपूर्णांक at kretprobe_trampoline
 */
पूर्णांक __kprobes trampoline_probe_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	regs->pc = __kretprobe_trampoline_handler(regs, &kretprobe_trampoline, शून्य);

	वापस 1;
पूर्ण

अटल पूर्णांक __kprobes post_kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	kprobe_opcode_t *addr = शून्य;
	काष्ठा kprobe *p = शून्य;

	अगर (!cur)
		वापस 0;

	अगर ((kcb->kprobe_status != KPROBE_REENTER) && cur->post_handler) अणु
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		cur->post_handler(cur, regs, 0);
	पूर्ण

	p = this_cpu_ptr(&saved_next_opcode);
	अगर (p->addr) अणु
		arch_disarm_kprobe(p);
		p->addr = शून्य;
		p->opcode = 0;

		addr = __this_cpu_पढ़ो(saved_current_opcode.addr);
		__this_cpu_ग_लिखो(saved_current_opcode.addr, शून्य);

		p = get_kprobe(addr);
		arch_arm_kprobe(p);

		p = this_cpu_ptr(&saved_next_opcode2);
		अगर (p->addr) अणु
			arch_disarm_kprobe(p);
			p->addr = शून्य;
			p->opcode = 0;
		पूर्ण
	पूर्ण

	/* Restore back the original saved kprobes variables and जारी. */
	अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
		restore_previous_kprobe(kcb);
		जाओ out;
	पूर्ण

	reset_current_kprobe();

out:
	preempt_enable_no_resched();

	वापस 1;
पूर्ण

पूर्णांक __kprobes kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	स्थिर काष्ठा exception_table_entry *entry;

	चयन (kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		/*
		 * We are here because the inकाष्ठाion being single
		 * stepped caused a page fault. We reset the current
		 * kprobe, poपूर्णांक the pc back to the probe address
		 * and allow the page fault handler to जारी as a
		 * normal page fault.
		 */
		regs->pc = (अचिन्हित दीर्घ)cur->addr;
		अगर (kcb->kprobe_status == KPROBE_REENTER)
			restore_previous_kprobe(kcb);
		अन्यथा
			reset_current_kprobe();
		preempt_enable_no_resched();
		अवरोध;
	हाल KPROBE_HIT_ACTIVE:
	हाल KPROBE_HIT_SSDONE:
		/*
		 * We increment the nmissed count क्रम accounting,
		 * we can also use npre/npostfault count क्रम accounting
		 * these specअगरic fault हालs.
		 */
		kprobes_inc_nmissed_count(cur);

		/*
		 * We come here because inकाष्ठाions in the pre/post
		 * handler caused the page_fault, this could happen
		 * अगर handler tries to access user space by
		 * copy_from_user(), get_user() etc. Let the
		 * user-specअगरied handler try to fix it first.
		 */
		अगर (cur->fault_handler && cur->fault_handler(cur, regs, trapnr))
			वापस 1;

		/*
		 * In हाल the user-specअगरied fault handler वापसed
		 * zero, try to fix up.
		 */
		अगर ((entry = search_exception_tables(regs->pc)) != शून्य) अणु
			regs->pc = entry->fixup;
			वापस 1;
		पूर्ण

		/*
		 * fixup_exception() could not handle it,
		 * Let करो_page_fault() fix it.
		 */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wrapper routine to क्रम handling exceptions.
 */
पूर्णांक __kprobes kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				       अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा kprobe *p = शून्य;
	काष्ठा die_args *args = (काष्ठा die_args *)data;
	पूर्णांक ret = NOTIFY_DONE;
	kprobe_opcode_t *addr = शून्य;
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	addr = (kprobe_opcode_t *) (args->regs->pc);
	अगर (val == DIE_TRAP &&
	    args->trapnr == (BREAKPOINT_INSTRUCTION & 0xff)) अणु
		अगर (!kprobe_running()) अणु
			अगर (kprobe_handler(args->regs)) अणु
				ret = NOTIFY_STOP;
			पूर्ण अन्यथा अणु
				/* Not a kprobe trap */
				ret = NOTIFY_DONE;
			पूर्ण
		पूर्ण अन्यथा अणु
			p = get_kprobe(addr);
			अगर ((kcb->kprobe_status == KPROBE_HIT_SS) ||
			    (kcb->kprobe_status == KPROBE_REENTER)) अणु
				अगर (post_kprobe_handler(args->regs))
					ret = NOTIFY_STOP;
			पूर्ण अन्यथा अणु
				अगर (kprobe_handler(args->regs))
					ret = NOTIFY_STOP;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा kprobe trampoline_p = अणु
	.addr = (kprobe_opcode_t *)&kretprobe_trampoline,
	.pre_handler = trampoline_probe_handler
पूर्ण;

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	वापस रेजिस्टर_kprobe(&trampoline_p);
पूर्ण

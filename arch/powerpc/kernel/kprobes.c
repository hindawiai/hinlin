<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Kernel Probes (KProbes)
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 *
 * 2002-Oct	Created by Vamsi Krishna S <vamsi_krishna@in.ibm.com> Kernel
 *		Probes initial implementation ( includes contributions from
 *		Rusty Russell).
 * 2004-July	Suparna Bhattaअक्षरya <suparna@in.ibm.com> added jumper probes
 *		पूर्णांकerface to access function arguments.
 * 2004-Nov	Ananth N Mavinakayanahalli <ananth@in.ibm.com> kprobes port
 *		क्रम PPC64
 */

#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/preempt.h>
#समावेश <linux/extable.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/inst.h>
#समावेश <linux/uaccess.h>

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

काष्ठा kretprobe_blackpoपूर्णांक kretprobe_blacklist[] = अणुअणुशून्य, शून्यपूर्णपूर्ण;

bool arch_within_kprobe_blacklist(अचिन्हित दीर्घ addr)
अणु
	वापस  (addr >= (अचिन्हित दीर्घ)__kprobes_text_start &&
		 addr < (अचिन्हित दीर्घ)__kprobes_text_end) ||
		(addr >= (अचिन्हित दीर्घ)_stext &&
		 addr < (अचिन्हित दीर्घ)__head_end);
पूर्ण

kprobe_opcode_t *kprobe_lookup_name(स्थिर अक्षर *name, अचिन्हित पूर्णांक offset)
अणु
	kprobe_opcode_t *addr = शून्य;

#अगर_घोषित PPC64_ELF_ABI_v2
	/* PPC64 ABIv2 needs local entry poपूर्णांक */
	addr = (kprobe_opcode_t *)kallsyms_lookup_name(name);
	अगर (addr && !offset) अणु
#अगर_घोषित CONFIG_KPROBES_ON_FTRACE
		अचिन्हित दीर्घ faddr;
		/*
		 * Per livepatch.h, ftrace location is always within the first
		 * 16 bytes of a function on घातerpc with -mprofile-kernel.
		 */
		faddr = ftrace_location_range((अचिन्हित दीर्घ)addr,
					      (अचिन्हित दीर्घ)addr + 16);
		अगर (faddr)
			addr = (kprobe_opcode_t *)faddr;
		अन्यथा
#पूर्ण_अगर
			addr = (kprobe_opcode_t *)ppc_function_entry(addr);
	पूर्ण
#या_अगर defined(PPC64_ELF_ABI_v1)
	/*
	 * 64bit घातerpc ABIv1 uses function descriptors:
	 * - Check क्रम the करोt variant of the symbol first.
	 * - If that fails, try looking up the symbol provided.
	 *
	 * This ensures we always get to the actual symbol and not
	 * the descriptor.
	 *
	 * Also handle <module:symbol> क्रमmat.
	 */
	अक्षर करोt_name[MODULE_NAME_LEN + 1 + KSYM_NAME_LEN];
	bool करोt_appended = false;
	स्थिर अक्षर *c;
	sमाप_प्रकार ret = 0;
	पूर्णांक len = 0;

	अगर ((c = strnchr(name, MODULE_NAME_LEN, ':')) != शून्य) अणु
		c++;
		len = c - name;
		स_नकल(करोt_name, name, len);
	पूर्ण अन्यथा
		c = name;

	अगर (*c != '\0' && *c != '.') अणु
		करोt_name[len++] = '.';
		करोt_appended = true;
	पूर्ण
	ret = strscpy(करोt_name + len, c, KSYM_NAME_LEN);
	अगर (ret > 0)
		addr = (kprobe_opcode_t *)kallsyms_lookup_name(करोt_name);

	/* Fallback to the original non-करोt symbol lookup */
	अगर (!addr && करोt_appended)
		addr = (kprobe_opcode_t *)kallsyms_lookup_name(name);
#अन्यथा
	addr = (kprobe_opcode_t *)kallsyms_lookup_name(name);
#पूर्ण_अगर

	वापस addr;
पूर्ण

पूर्णांक arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	पूर्णांक ret = 0;
	काष्ठा kprobe *prev;
	काष्ठा ppc_inst insn = ppc_inst_पढ़ो((काष्ठा ppc_inst *)p->addr);

	अगर ((अचिन्हित दीर्घ)p->addr & 0x03) अणु
		prपूर्णांकk("Attempt to register kprobe at an unaligned address\n");
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (IS_MTMSRD(insn) || IS_RFID(insn) || IS_RFI(insn)) अणु
		prपूर्णांकk("Cannot register a kprobe on rfi/rfid or mtmsr[d]\n");
		ret = -EINVAL;
	पूर्ण अन्यथा अगर ((अचिन्हित दीर्घ)p->addr & ~PAGE_MASK &&
		   ppc_inst_prefixed(ppc_inst_पढ़ो((काष्ठा ppc_inst *)(p->addr - 1)))) अणु
		prपूर्णांकk("Cannot register a kprobe on the second word of prefixed instruction\n");
		ret = -EINVAL;
	पूर्ण
	preempt_disable();
	prev = get_kprobe(p->addr - 1);
	preempt_enable_no_resched();
	अगर (prev &&
	    ppc_inst_prefixed(ppc_inst_पढ़ो((काष्ठा ppc_inst *)prev->ainsn.insn))) अणु
		prपूर्णांकk("Cannot register a kprobe on the second word of prefixed instruction\n");
		ret = -EINVAL;
	पूर्ण

	/* insn must be on a special executable page on ppc64.  This is
	 * not explicitly required on ppc32 (right now), but it करोesn't hurt */
	अगर (!ret) अणु
		p->ainsn.insn = get_insn_slot();
		अगर (!p->ainsn.insn)
			ret = -ENOMEM;
	पूर्ण

	अगर (!ret) अणु
		patch_inकाष्ठाion((काष्ठा ppc_inst *)p->ainsn.insn, insn);
		p->opcode = ppc_inst_val(insn);
	पूर्ण

	p->ainsn.boostable = 0;
	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(arch_prepare_kprobe);

व्योम arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	patch_inकाष्ठाion((काष्ठा ppc_inst *)p->addr, ppc_inst(BREAKPOINT_INSTRUCTION));
पूर्ण
NOKPROBE_SYMBOL(arch_arm_kprobe);

व्योम arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	patch_inकाष्ठाion((काष्ठा ppc_inst *)p->addr, ppc_inst(p->opcode));
पूर्ण
NOKPROBE_SYMBOL(arch_disarm_kprobe);

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->ainsn.insn) अणु
		मुक्त_insn_slot(p->ainsn.insn, 0);
		p->ainsn.insn = शून्य;
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(arch_हटाओ_kprobe);

अटल nokprobe_अंतरभूत व्योम prepare_singlestep(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	enable_single_step(regs);

	/*
	 * On घातerpc we should single step on the original
	 * inकाष्ठाion even अगर the probed insn is a trap
	 * variant as values in regs could play a part in
	 * अगर the trap is taken or not
	 */
	regs->nip = (अचिन्हित दीर्घ)p->ainsn.insn;
पूर्ण

अटल nokprobe_अंतरभूत व्योम save_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	kcb->prev_kprobe.kp = kprobe_running();
	kcb->prev_kprobe.status = kcb->kprobe_status;
	kcb->prev_kprobe.saved_msr = kcb->kprobe_saved_msr;
पूर्ण

अटल nokprobe_अंतरभूत व्योम restore_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, kcb->prev_kprobe.kp);
	kcb->kprobe_status = kcb->prev_kprobe.status;
	kcb->kprobe_saved_msr = kcb->prev_kprobe.saved_msr;
पूर्ण

अटल nokprobe_अंतरभूत व्योम set_current_kprobe(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
				काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, p);
	kcb->kprobe_saved_msr = regs->msr;
पूर्ण

bool arch_kprobe_on_func_entry(अचिन्हित दीर्घ offset)
अणु
#अगर_घोषित PPC64_ELF_ABI_v2
#अगर_घोषित CONFIG_KPROBES_ON_FTRACE
	वापस offset <= 16;
#अन्यथा
	वापस offset <= 8;
#पूर्ण_अगर
#अन्यथा
	वापस !offset;
#पूर्ण_अगर
पूर्ण

व्योम arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	ri->ret_addr = (kprobe_opcode_t *)regs->link;
	ri->fp = शून्य;

	/* Replace the वापस addr with trampoline addr */
	regs->link = (अचिन्हित दीर्घ)kretprobe_trampoline;
पूर्ण
NOKPROBE_SYMBOL(arch_prepare_kretprobe);

अटल पूर्णांक try_to_emulate(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;
	काष्ठा ppc_inst insn = ppc_inst_पढ़ो((काष्ठा ppc_inst *)p->ainsn.insn);

	/* regs->nip is also adjusted अगर emulate_step वापसs 1 */
	ret = emulate_step(regs, insn);
	अगर (ret > 0) अणु
		/*
		 * Once this inकाष्ठाion has been boosted
		 * successfully, set the boostable flag
		 */
		अगर (unlikely(p->ainsn.boostable == 0))
			p->ainsn.boostable = 1;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		/*
		 * We करोn't allow kprobes on mपंचांगsr(d)/rfi(d), etc.
		 * So, we should never get here... but, its still
		 * good to catch them, just in हाल...
		 */
		prपूर्णांकk("Can't step on instruction %s\n", ppc_inst_as_str(insn));
		BUG();
	पूर्ण अन्यथा अणु
		/*
		 * If we haven't previously emulated this inकाष्ठाion, then it
		 * can't be boosted. Note it down so we don't try to करो so again.
		 *
		 * If, however, we had emulated this inकाष्ठाion in the past,
		 * then this is just an error with the current run (क्रम
		 * instance, exceptions due to a load/store). We वापस 0 so
		 * that this is now single-stepped, but जारी to try
		 * emulating it in subsequent probe hits.
		 */
		अगर (unlikely(p->ainsn.boostable != 1))
			p->ainsn.boostable = -1;
	पूर्ण

	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(try_to_emulate);

पूर्णांक kprobe_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *p;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक *addr = (अचिन्हित पूर्णांक *)regs->nip;
	काष्ठा kprobe_ctlblk *kcb;

	अगर (user_mode(regs))
		वापस 0;

	अगर (!(regs->msr & MSR_IR) || !(regs->msr & MSR_DR))
		वापस 0;

	/*
	 * We करोn't want to be preempted क्रम the entire
	 * duration of kprobe processing
	 */
	preempt_disable();
	kcb = get_kprobe_ctlblk();

	p = get_kprobe(addr);
	अगर (!p) अणु
		अचिन्हित पूर्णांक instr;

		अगर (get_kernel_nofault(instr, addr))
			जाओ no_kprobe;

		अगर (instr != BREAKPOINT_INSTRUCTION) अणु
			/*
			 * PowerPC has multiple variants of the "trap"
			 * inकाष्ठाion. If the current inकाष्ठाion is a
			 * trap variant, it could beदीर्घ to someone अन्यथा
			 */
			अगर (is_trap(instr))
				जाओ no_kprobe;
			/*
			 * The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd right
			 * after we hit it.  Another cpu has हटाओd
			 * either a probepoपूर्णांक or a debugger अवरोधpoपूर्णांक
			 * at this address.  In either हाल, no further
			 * handling of this पूर्णांकerrupt is appropriate.
			 */
			ret = 1;
		पूर्ण
		/* Not one of ours: let kernel handle it */
		जाओ no_kprobe;
	पूर्ण

	/* Check we're not actually recursing */
	अगर (kprobe_running()) अणु
		kprobe_opcode_t insn = *p->ainsn.insn;
		अगर (kcb->kprobe_status == KPROBE_HIT_SS && is_trap(insn)) अणु
			/* Turn off 'trace' bits */
			regs->msr &= ~MSR_SINGLESTEP;
			regs->msr |= kcb->kprobe_saved_msr;
			जाओ no_kprobe;
		पूर्ण

		/*
		 * We have reentered the kprobe_handler(), since another probe
		 * was hit जबतक within the handler. We here save the original
		 * kprobes variables and just single step on the inकाष्ठाion of
		 * the new probe without calling any user handlers.
		 */
		save_previous_kprobe(kcb);
		set_current_kprobe(p, regs, kcb);
		kprobes_inc_nmissed_count(p);
		kcb->kprobe_status = KPROBE_REENTER;
		अगर (p->ainsn.boostable >= 0) अणु
			ret = try_to_emulate(p, regs);

			अगर (ret > 0) अणु
				restore_previous_kprobe(kcb);
				preempt_enable_no_resched();
				वापस 1;
			पूर्ण
		पूर्ण
		prepare_singlestep(p, regs);
		वापस 1;
	पूर्ण

	kcb->kprobe_status = KPROBE_HIT_ACTIVE;
	set_current_kprobe(p, regs, kcb);
	अगर (p->pre_handler && p->pre_handler(p, regs)) अणु
		/* handler changed execution path, so skip ss setup */
		reset_current_kprobe();
		preempt_enable_no_resched();
		वापस 1;
	पूर्ण

	अगर (p->ainsn.boostable >= 0) अणु
		ret = try_to_emulate(p, regs);

		अगर (ret > 0) अणु
			अगर (p->post_handler)
				p->post_handler(p, regs, 0);

			kcb->kprobe_status = KPROBE_HIT_SSDONE;
			reset_current_kprobe();
			preempt_enable_no_resched();
			वापस 1;
		पूर्ण
	पूर्ण
	prepare_singlestep(p, regs);
	kcb->kprobe_status = KPROBE_HIT_SS;
	वापस 1;

no_kprobe:
	preempt_enable_no_resched();
	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(kprobe_handler);

/*
 * Function वापस probe trampoline:
 * 	- init_kprobes() establishes a probepoपूर्णांक here
 * 	- When the probed function वापसs, this probe
 * 		causes the handlers to fire
 */
यंत्र(".global kretprobe_trampoline\n"
	".type kretprobe_trampoline, @function\n"
	"kretprobe_trampoline:\n"
	"nop\n"
	"blr\n"
	".size kretprobe_trampoline, .-kretprobe_trampoline\n");

/*
 * Called when the probe at kretprobe trampoline is hit
 */
अटल पूर्णांक trampoline_probe_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_ret_address;

	orig_ret_address = __kretprobe_trampoline_handler(regs, &kretprobe_trampoline, शून्य);
	/*
	 * We get here through one of two paths:
	 * 1. by taking a trap -> kprobe_handler() -> here
	 * 2. by optprobe branch -> optimized_callback() -> opt_pre_handler() -> here
	 *
	 * When going back through (1), we need regs->nip to be setup properly
	 * as it is used to determine the वापस address from the trap.
	 * For (2), since nip is not honoured with optprobes, we instead setup
	 * the link रेजिस्टर properly so that the subsequent 'blr' in
	 * kretprobe_trampoline jumps back to the right inकाष्ठाion.
	 *
	 * For nip, we should set the address to the previous inकाष्ठाion since
	 * we end up emulating it in kprobe_handler(), which increments the nip
	 * again.
	 */
	regs->nip = orig_ret_address - 4;
	regs->link = orig_ret_address;

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(trampoline_probe_handler);

/*
 * Called after single-stepping.  p->addr is the address of the
 * inकाष्ठाion whose first byte has been replaced by the "breakpoint"
 * inकाष्ठाion.  To aव्योम the SMP problems that can occur when we
 * temporarily put back the original opcode to single-step, we
 * single-stepped a copy of the inकाष्ठाion.  The address of this
 * copy is p->ainsn.insn.
 */
पूर्णांक kprobe_post_handler(काष्ठा pt_regs *regs)
अणु
	पूर्णांक len;
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर (!cur || user_mode(regs))
		वापस 0;

	len = ppc_inst_len(ppc_inst_पढ़ो((काष्ठा ppc_inst *)cur->ainsn.insn));
	/* make sure we got here क्रम inकाष्ठाion we have a kprobe on */
	अगर (((अचिन्हित दीर्घ)cur->ainsn.insn + len) != regs->nip)
		वापस 0;

	अगर ((kcb->kprobe_status != KPROBE_REENTER) && cur->post_handler) अणु
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		cur->post_handler(cur, regs, 0);
	पूर्ण

	/* Adjust nip to after the single-stepped inकाष्ठाion */
	regs->nip = (अचिन्हित दीर्घ)cur->addr + len;
	regs->msr |= kcb->kprobe_saved_msr;

	/*Restore back the original saved kprobes variables and जारी. */
	अगर (kcb->kprobe_status == KPROBE_REENTER) अणु
		restore_previous_kprobe(kcb);
		जाओ out;
	पूर्ण
	reset_current_kprobe();
out:
	preempt_enable_no_resched();

	/*
	 * अगर somebody अन्यथा is singlestepping across a probe poपूर्णांक, msr
	 * will have DE/SE set, in which हाल, जारी the reमुख्यing processing
	 * of करो_debug, as अगर this is not a probe hit.
	 */
	अगर (regs->msr & MSR_SINGLESTEP)
		वापस 0;

	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(kprobe_post_handler);

पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	स्थिर काष्ठा exception_table_entry *entry;

	चयन(kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SS:
	हाल KPROBE_REENTER:
		/*
		 * We are here because the inकाष्ठाion being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the nip poपूर्णांकs back to the probe address
		 * and allow the page fault handler to जारी as a
		 * normal page fault.
		 */
		regs->nip = (अचिन्हित दीर्घ)cur->addr;
		regs->msr &= ~MSR_SINGLESTEP; /* Turn off 'trace' bits */
		regs->msr |= kcb->kprobe_saved_msr;
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
		अगर ((entry = search_exception_tables(regs->nip)) != शून्य) अणु
			regs->nip = extable_fixup(entry);
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
NOKPROBE_SYMBOL(kprobe_fault_handler);

अचिन्हित दीर्घ arch_deref_entry_poपूर्णांक(व्योम *entry)
अणु
#अगर_घोषित PPC64_ELF_ABI_v1
	अगर (!kernel_text_address((अचिन्हित दीर्घ)entry))
		वापस ppc_global_function_entry(entry);
	अन्यथा
#पूर्ण_अगर
		वापस (अचिन्हित दीर्घ)entry;
पूर्ण
NOKPROBE_SYMBOL(arch_deref_entry_poपूर्णांक);

अटल काष्ठा kprobe trampoline_p = अणु
	.addr = (kprobe_opcode_t *) &kretprobe_trampoline,
	.pre_handler = trampoline_probe_handler
पूर्ण;

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	वापस रेजिस्टर_kprobe(&trampoline_p);
पूर्ण

पूर्णांक arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->addr == (kprobe_opcode_t *)&kretprobe_trampoline)
		वापस 1;

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(arch_trampoline_kprobe);

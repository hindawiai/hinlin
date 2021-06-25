<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Code क्रम Kernel probes Jump optimization.
 *
 * Copyright 2017, Anju T, IBM Corp.
 */

#समावेश <linux/kprobes.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/inst.h>

#घोषणा TMPL_CALL_HDLR_IDX	\
	(optprobe_ढाँचा_call_handler - optprobe_ढाँचा_entry)
#घोषणा TMPL_EMULATE_IDX	\
	(optprobe_ढाँचा_call_emulate - optprobe_ढाँचा_entry)
#घोषणा TMPL_RET_IDX		\
	(optprobe_ढाँचा_ret - optprobe_ढाँचा_entry)
#घोषणा TMPL_OP_IDX		\
	(optprobe_ढाँचा_op_address - optprobe_ढाँचा_entry)
#घोषणा TMPL_INSN_IDX		\
	(optprobe_ढाँचा_insn - optprobe_ढाँचा_entry)
#घोषणा TMPL_END_IDX		\
	(optprobe_ढाँचा_end - optprobe_ढाँचा_entry)

DEFINE_INSN_CACHE_OPS(ppc_optinsn);

अटल bool insn_page_in_use;

अटल व्योम *__ppc_alloc_insn_page(व्योम)
अणु
	अगर (insn_page_in_use)
		वापस शून्य;
	insn_page_in_use = true;
	वापस &optinsn_slot;
पूर्ण

अटल व्योम __ppc_मुक्त_insn_page(व्योम *page __maybe_unused)
अणु
	insn_page_in_use = false;
पूर्ण

काष्ठा kprobe_insn_cache kprobe_ppc_optinsn_slots = अणु
	.mutex = __MUTEX_INITIALIZER(kprobe_ppc_optinsn_slots.mutex),
	.pages = LIST_HEAD_INIT(kprobe_ppc_optinsn_slots.pages),
	/* insn_size initialized later */
	.alloc = __ppc_alloc_insn_page,
	.मुक्त = __ppc_मुक्त_insn_page,
	.nr_garbage = 0,
पूर्ण;

/*
 * Check अगर we can optimize this probe. Returns NIP post-emulation अगर this can
 * be optimized and 0 otherwise.
 */
अटल अचिन्हित दीर्घ can_optimize(काष्ठा kprobe *p)
अणु
	काष्ठा pt_regs regs;
	काष्ठा inकाष्ठाion_op op;
	अचिन्हित दीर्घ nip = 0;

	/*
	 * kprobe placed क्रम kretprobe during boot समय
	 * has a 'nop' inकाष्ठाion, which can be emulated.
	 * So further checks can be skipped.
	 */
	अगर (p->addr == (kprobe_opcode_t *)&kretprobe_trampoline)
		वापस (अचिन्हित दीर्घ)p->addr + माप(kprobe_opcode_t);

	/*
	 * We only support optimizing kernel addresses, but not
	 * module addresses.
	 *
	 * FIXME: Optimize kprobes placed in module addresses.
	 */
	अगर (!is_kernel_addr((अचिन्हित दीर्घ)p->addr))
		वापस 0;

	स_रखो(&regs, 0, माप(काष्ठा pt_regs));
	regs.nip = (अचिन्हित दीर्घ)p->addr;
	regs.trap = 0x0;
	regs.msr = MSR_KERNEL;

	/*
	 * Kprobe placed in conditional branch inकाष्ठाions are
	 * not optimized, as we can't predict the nip prior with
	 * dummy pt_regs and can not ensure that the वापस branch
	 * from detour buffer falls in the range of address (i.e 32MB).
	 * A branch back from trampoline is set up in the detour buffer
	 * to the nip वापसed by the analyse_instr() here.
	 *
	 * Ensure that the inकाष्ठाion is not a conditional branch,
	 * and that can be emulated.
	 */
	अगर (!is_conditional_branch(ppc_inst_पढ़ो((काष्ठा ppc_inst *)p->ainsn.insn)) &&
	    analyse_instr(&op, &regs,
			  ppc_inst_पढ़ो((काष्ठा ppc_inst *)p->ainsn.insn)) == 1) अणु
		emulate_update_regs(&regs, &op);
		nip = regs.nip;
	पूर्ण

	वापस nip;
पूर्ण

अटल व्योम optimized_callback(काष्ठा optimized_kprobe *op,
			       काष्ठा pt_regs *regs)
अणु
	/* This is possible अगर op is under delayed unoptimizing */
	अगर (kprobe_disabled(&op->kp))
		वापस;

	preempt_disable();

	अगर (kprobe_running()) अणु
		kprobes_inc_nmissed_count(&op->kp);
	पूर्ण अन्यथा अणु
		__this_cpu_ग_लिखो(current_kprobe, &op->kp);
		regs->nip = (अचिन्हित दीर्घ)op->kp.addr;
		get_kprobe_ctlblk()->kprobe_status = KPROBE_HIT_ACTIVE;
		opt_pre_handler(&op->kp, regs);
		__this_cpu_ग_लिखो(current_kprobe, शून्य);
	पूर्ण

	preempt_enable_no_resched();
पूर्ण
NOKPROBE_SYMBOL(optimized_callback);

व्योम arch_हटाओ_optimized_kprobe(काष्ठा optimized_kprobe *op)
अणु
	अगर (op->optinsn.insn) अणु
		मुक्त_ppc_optinsn_slot(op->optinsn.insn, 1);
		op->optinsn.insn = शून्य;
	पूर्ण
पूर्ण

अटल व्योम patch_imm32_load_insns(अचिन्हित दीर्घ val, पूर्णांक reg, kprobe_opcode_t *addr)
अणु
	patch_inकाष्ठाion((काष्ठा ppc_inst *)addr,
			  ppc_inst(PPC_RAW_LIS(reg, IMM_H(val))));
	addr++;

	patch_inकाष्ठाion((काष्ठा ppc_inst *)addr,
			  ppc_inst(PPC_RAW_ORI(reg, reg, IMM_L(val))));
पूर्ण

/*
 * Generate inकाष्ठाions to load provided immediate 64-bit value
 * to रेजिस्टर 'reg' and patch these instructions at 'addr'.
 */
अटल व्योम patch_imm64_load_insns(अचिन्हित दीर्घ दीर्घ val, पूर्णांक reg, kprobe_opcode_t *addr)
अणु
	/* lis reg,(op)@highest */
	patch_inकाष्ठाion((काष्ठा ppc_inst *)addr,
			  ppc_inst(PPC_INST_ADDIS | ___PPC_RT(reg) |
				   ((val >> 48) & 0xffff)));
	addr++;

	/* ori reg,reg,(op)@higher */
	patch_inकाष्ठाion((काष्ठा ppc_inst *)addr,
			  ppc_inst(PPC_INST_ORI | ___PPC_RA(reg) |
				   ___PPC_RS(reg) | ((val >> 32) & 0xffff)));
	addr++;

	/* rldicr reg,reg,32,31 */
	patch_inकाष्ठाion((काष्ठा ppc_inst *)addr,
			  ppc_inst(PPC_INST_RLDICR | ___PPC_RA(reg) |
				   ___PPC_RS(reg) | __PPC_SH64(32) | __PPC_ME64(31)));
	addr++;

	/* oris reg,reg,(op)@h */
	patch_inकाष्ठाion((काष्ठा ppc_inst *)addr,
			  ppc_inst(PPC_INST_ORIS | ___PPC_RA(reg) |
				   ___PPC_RS(reg) | ((val >> 16) & 0xffff)));
	addr++;

	/* ori reg,reg,(op)@l */
	patch_inकाष्ठाion((काष्ठा ppc_inst *)addr,
			  ppc_inst(PPC_INST_ORI | ___PPC_RA(reg) |
				   ___PPC_RS(reg) | (val & 0xffff)));
पूर्ण

अटल व्योम patch_imm_load_insns(अचिन्हित दीर्घ val, पूर्णांक reg, kprobe_opcode_t *addr)
अणु
	अगर (IS_ENABLED(CONFIG_PPC64))
		patch_imm64_load_insns(val, reg, addr);
	अन्यथा
		patch_imm32_load_insns(val, reg, addr);
पूर्ण

पूर्णांक arch_prepare_optimized_kprobe(काष्ठा optimized_kprobe *op, काष्ठा kprobe *p)
अणु
	काष्ठा ppc_inst branch_op_callback, branch_emulate_step, temp;
	kprobe_opcode_t *op_callback_addr, *emulate_step_addr, *buff;
	दीर्घ b_offset;
	अचिन्हित दीर्घ nip, size;
	पूर्णांक rc, i;

	kprobe_ppc_optinsn_slots.insn_size = MAX_OPTINSN_SIZE;

	nip = can_optimize(p);
	अगर (!nip)
		वापस -EILSEQ;

	/* Allocate inकाष्ठाion slot क्रम detour buffer */
	buff = get_ppc_optinsn_slot();
	अगर (!buff)
		वापस -ENOMEM;

	/*
	 * OPTPROBE uses 'b' inकाष्ठाion to branch to optinsn.insn.
	 *
	 * The target address has to be relatively nearby, to permit use
	 * of branch inकाष्ठाion in घातerpc, because the address is specअगरied
	 * in an immediate field in the inकाष्ठाion opcode itself, ie 24 bits
	 * in the opcode specअगरy the address. Thereक्रमe the address should
	 * be within 32MB on either side of the current inकाष्ठाion.
	 */
	b_offset = (अचिन्हित दीर्घ)buff - (अचिन्हित दीर्घ)p->addr;
	अगर (!is_offset_in_branch_range(b_offset))
		जाओ error;

	/* Check अगर the वापस address is also within 32MB range */
	b_offset = (अचिन्हित दीर्घ)(buff + TMPL_RET_IDX) -
			(अचिन्हित दीर्घ)nip;
	अगर (!is_offset_in_branch_range(b_offset))
		जाओ error;

	/* Setup ढाँचा */
	/* We can optimize this via patch_inकाष्ठाion_winकरोw later */
	size = (TMPL_END_IDX * माप(kprobe_opcode_t)) / माप(पूर्णांक);
	pr_devel("Copying template to %p, size %lu\n", buff, size);
	क्रम (i = 0; i < size; i++) अणु
		rc = patch_inकाष्ठाion((काष्ठा ppc_inst *)(buff + i),
				       ppc_inst(*(optprobe_ढाँचा_entry + i)));
		अगर (rc < 0)
			जाओ error;
	पूर्ण

	/*
	 * Fixup the ढाँचा with inकाष्ठाions to:
	 * 1. load the address of the actual probepoपूर्णांक
	 */
	patch_imm_load_insns((अचिन्हित दीर्घ)op, 3, buff + TMPL_OP_IDX);

	/*
	 * 2. branch to optimized_callback() and emulate_step()
	 */
	op_callback_addr = (kprobe_opcode_t *)ppc_kallsyms_lookup_name("optimized_callback");
	emulate_step_addr = (kprobe_opcode_t *)ppc_kallsyms_lookup_name("emulate_step");
	अगर (!op_callback_addr || !emulate_step_addr) अणु
		WARN(1, "Unable to lookup optimized_callback()/emulate_step()\n");
		जाओ error;
	पूर्ण

	rc = create_branch(&branch_op_callback,
			   (काष्ठा ppc_inst *)(buff + TMPL_CALL_HDLR_IDX),
			   (अचिन्हित दीर्घ)op_callback_addr,
			   BRANCH_SET_LINK);

	rc |= create_branch(&branch_emulate_step,
			    (काष्ठा ppc_inst *)(buff + TMPL_EMULATE_IDX),
			    (अचिन्हित दीर्घ)emulate_step_addr,
			    BRANCH_SET_LINK);

	अगर (rc)
		जाओ error;

	patch_inकाष्ठाion((काष्ठा ppc_inst *)(buff + TMPL_CALL_HDLR_IDX),
			  branch_op_callback);
	patch_inकाष्ठाion((काष्ठा ppc_inst *)(buff + TMPL_EMULATE_IDX),
			  branch_emulate_step);

	/*
	 * 3. load inकाष्ठाion to be emulated पूर्णांकo relevant रेजिस्टर, and
	 */
	temp = ppc_inst_पढ़ो((काष्ठा ppc_inst *)p->ainsn.insn);
	patch_imm_load_insns(ppc_inst_as_uदीर्घ(temp), 4, buff + TMPL_INSN_IDX);

	/*
	 * 4. branch back from trampoline
	 */
	patch_branch((काष्ठा ppc_inst *)(buff + TMPL_RET_IDX), (अचिन्हित दीर्घ)nip, 0);

	flush_icache_range((अचिन्हित दीर्घ)buff,
			   (अचिन्हित दीर्घ)(&buff[TMPL_END_IDX]));

	op->optinsn.insn = buff;

	वापस 0;

error:
	मुक्त_ppc_optinsn_slot(buff, 0);
	वापस -दुस्फल;

पूर्ण

पूर्णांक arch_prepared_optinsn(काष्ठा arch_optimized_insn *optinsn)
अणु
	वापस optinsn->insn != शून्य;
पूर्ण

/*
 * On घातerpc, Optprobes always replaces one inकाष्ठाion (4 bytes
 * aligned and 4 bytes दीर्घ). It is impossible to encounter another
 * kprobe in this address range. So always वापस 0.
 */
पूर्णांक arch_check_optimized_kprobe(काष्ठा optimized_kprobe *op)
अणु
	वापस 0;
पूर्ण

व्योम arch_optimize_kprobes(काष्ठा list_head *oplist)
अणु
	काष्ठा ppc_inst instr;
	काष्ठा optimized_kprobe *op;
	काष्ठा optimized_kprobe *पंचांगp;

	list_क्रम_each_entry_safe(op, पंचांगp, oplist, list) अणु
		/*
		 * Backup inकाष्ठाions which will be replaced
		 * by jump address
		 */
		स_नकल(op->optinsn.copied_insn, op->kp.addr,
					       RELATIVEJUMP_SIZE);
		create_branch(&instr,
			      (काष्ठा ppc_inst *)op->kp.addr,
			      (अचिन्हित दीर्घ)op->optinsn.insn, 0);
		patch_inकाष्ठाion((काष्ठा ppc_inst *)op->kp.addr, instr);
		list_del_init(&op->list);
	पूर्ण
पूर्ण

व्योम arch_unoptimize_kprobe(काष्ठा optimized_kprobe *op)
अणु
	arch_arm_kprobe(&op->kp);
पूर्ण

व्योम arch_unoptimize_kprobes(काष्ठा list_head *oplist,
			     काष्ठा list_head *करोne_list)
अणु
	काष्ठा optimized_kprobe *op;
	काष्ठा optimized_kprobe *पंचांगp;

	list_क्रम_each_entry_safe(op, पंचांगp, oplist, list) अणु
		arch_unoptimize_kprobe(op);
		list_move(&op->list, करोne_list);
	पूर्ण
पूर्ण

पूर्णांक arch_within_optimized_kprobe(काष्ठा optimized_kprobe *op,
				 अचिन्हित दीर्घ addr)
अणु
	वापस ((अचिन्हित दीर्घ)op->kp.addr <= addr &&
		(अचिन्हित दीर्घ)op->kp.addr + RELATIVEJUMP_SIZE > addr);
पूर्ण

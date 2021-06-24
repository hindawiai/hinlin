<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Rabin Vincent <rabin at rab.in>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/notअगरier.h>

#समावेश <यंत्र/opcodes.h>
#समावेश <यंत्र/traps.h>

#समावेश "../decode.h"
#समावेश "../decode-arm.h"
#समावेश "core.h"

#घोषणा UPROBE_TRAP_NR	अच_पूर्णांक_उच्च

bool is_swbp_insn(uprobe_opcode_t *insn)
अणु
	वापस (__mem_to_opcode_arm(*insn) & 0x0fffffff) ==
		(UPROBE_SWBP_ARM_INSN & 0x0fffffff);
पूर्ण

पूर्णांक set_swbp(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm,
	     अचिन्हित दीर्घ vaddr)
अणु
	वापस uprobe_ग_लिखो_opcode(auprobe, mm, vaddr,
		   __opcode_to_mem_arm(auprobe->bpinsn));
पूर्ण

bool arch_uprobe_ignore(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अगर (!auprobe->asi.insn_check_cc(regs->ARM_cpsr)) अणु
		regs->ARM_pc += 4;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool arch_uprobe_skip_sstep(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	probes_opcode_t opcode;

	अगर (!auprobe->simulate)
		वापस false;

	opcode = __mem_to_opcode_arm(*(अचिन्हित पूर्णांक *) auprobe->insn);

	auprobe->asi.insn_singlestep(opcode, &auprobe->asi, regs);

	वापस true;
पूर्ण

अचिन्हित दीर्घ
arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline_vaddr,
				  काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_ret_vaddr;

	orig_ret_vaddr = regs->ARM_lr;
	/* Replace the वापस addr with trampoline addr */
	regs->ARM_lr = trampoline_vaddr;
	वापस orig_ret_vaddr;
पूर्ण

पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm,
			     अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक insn;
	अचिन्हित पूर्णांक bpinsn;
	क्रमागत probes_insn ret;

	/* Thumb not yet support */
	अगर (addr & 0x3)
		वापस -EINVAL;

	insn = __mem_to_opcode_arm(*(अचिन्हित पूर्णांक *)auprobe->insn);
	auprobe->ixol[0] = __opcode_to_mem_arm(insn);
	auprobe->ixol[1] = __opcode_to_mem_arm(UPROBE_SS_ARM_INSN);

	ret = arm_probes_decode_insn(insn, &auprobe->asi, false,
				     uprobes_probes_actions, शून्य);
	चयन (ret) अणु
	हाल INSN_REJECTED:
		वापस -EINVAL;

	हाल INSN_GOOD_NO_SLOT:
		auprobe->simulate = true;
		अवरोध;

	हाल INSN_GOOD:
	शेष:
		अवरोध;
	पूर्ण

	bpinsn = UPROBE_SWBP_ARM_INSN & 0x0fffffff;
	अगर (insn >= 0xe0000000)
		bpinsn |= 0xe0000000;  /* Unconditional inकाष्ठाion */
	अन्यथा
		bpinsn |= insn & 0xf0000000;  /* Copy condition from insn */

	auprobe->bpinsn = bpinsn;

	वापस 0;
पूर्ण

व्योम arch_uprobe_copy_ixol(काष्ठा page *page, अचिन्हित दीर्घ vaddr,
			   व्योम *src, अचिन्हित दीर्घ len)
अणु
	व्योम *xol_page_kaddr = kmap_atomic(page);
	व्योम *dst = xol_page_kaddr + (vaddr & ~PAGE_MASK);

	preempt_disable();

	/* Initialize the slot */
	स_नकल(dst, src, len);

	/* flush caches (dcache/icache) */
	flush_uprobe_xol_access(page, vaddr, dst, len);

	preempt_enable();

	kunmap_atomic(xol_page_kaddr);
पूर्ण


पूर्णांक arch_uprobe_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	अगर (auprobe->prehandler)
		auprobe->prehandler(auprobe, &utask->autask, regs);

	utask->autask.saved_trap_no = current->thपढ़ो.trap_no;
	current->thपढ़ो.trap_no = UPROBE_TRAP_NR;
	regs->ARM_pc = utask->xol_vaddr;

	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	WARN_ON_ONCE(current->thपढ़ो.trap_no != UPROBE_TRAP_NR);

	current->thपढ़ो.trap_no = utask->autask.saved_trap_no;
	regs->ARM_pc = utask->vaddr + 4;

	अगर (auprobe->posthandler)
		auprobe->posthandler(auprobe, &utask->autask, regs);

	वापस 0;
पूर्ण

bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *t)
अणु
	अगर (t->thपढ़ो.trap_no != UPROBE_TRAP_NR)
		वापस true;

	वापस false;
पूर्ण

व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	current->thपढ़ो.trap_no = utask->autask.saved_trap_no;
	inकाष्ठाion_poपूर्णांकer_set(regs, utask->vaddr);
पूर्ण

पूर्णांक arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ val, व्योम *data)
अणु
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक uprobe_trap_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	instr &= 0x0fffffff;
	अगर (instr == (UPROBE_SWBP_ARM_INSN & 0x0fffffff))
		uprobe_pre_sstep_notअगरier(regs);
	अन्यथा अगर (instr == (UPROBE_SS_ARM_INSN & 0x0fffffff))
		uprobe_post_sstep_notअगरier(regs);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अचिन्हित दीर्घ uprobe_get_swbp_addr(काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

अटल काष्ठा undef_hook uprobes_arm_अवरोध_hook = अणु
	.instr_mask	= 0x0fffffff,
	.instr_val	= (UPROBE_SWBP_ARM_INSN & 0x0fffffff),
	.cpsr_mask	= (PSR_T_BIT | MODE_MASK),
	.cpsr_val	= USR_MODE,
	.fn		= uprobe_trap_handler,
पूर्ण;

अटल काष्ठा undef_hook uprobes_arm_ss_hook = अणु
	.instr_mask	= 0x0fffffff,
	.instr_val	= (UPROBE_SS_ARM_INSN & 0x0fffffff),
	.cpsr_mask	= (PSR_T_BIT | MODE_MASK),
	.cpsr_val	= USR_MODE,
	.fn		= uprobe_trap_handler,
पूर्ण;

अटल पूर्णांक arch_uprobes_init(व्योम)
अणु
	रेजिस्टर_undef_hook(&uprobes_arm_अवरोध_hook);
	रेजिस्टर_undef_hook(&uprobes_arm_ss_hook);

	वापस 0;
पूर्ण
device_initcall(arch_uprobes_init);

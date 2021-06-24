<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/highस्मृति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/uprobes.h>

#समावेश "decode-insn.h"

#घोषणा UPROBE_TRAP_NR	अच_पूर्णांक_उच्च

bool is_swbp_insn(uprobe_opcode_t *insn)
अणु
#अगर_घोषित CONFIG_RISCV_ISA_C
	वापस (*insn & 0xffff) == UPROBE_SWBP_INSN;
#अन्यथा
	वापस *insn == UPROBE_SWBP_INSN;
#पूर्ण_अगर
पूर्ण

अचिन्हित दीर्घ uprobe_get_swbp_addr(काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm,
			     अचिन्हित दीर्घ addr)
अणु
	probe_opcode_t opcode;

	opcode = *(probe_opcode_t *)(&auprobe->insn[0]);

	auprobe->insn_size = GET_INSN_LENGTH(opcode);

	चयन (riscv_probe_decode_insn(&opcode, &auprobe->api)) अणु
	हाल INSN_REJECTED:
		वापस -EINVAL;

	हाल INSN_GOOD_NO_SLOT:
		auprobe->simulate = true;
		अवरोध;

	हाल INSN_GOOD:
		auprobe->simulate = false;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	utask->autask.saved_cause = current->thपढ़ो.bad_cause;
	current->thपढ़ो.bad_cause = UPROBE_TRAP_NR;

	inकाष्ठाion_poपूर्णांकer_set(regs, utask->xol_vaddr);

	regs->status &= ~SR_SPIE;

	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	WARN_ON_ONCE(current->thपढ़ो.bad_cause != UPROBE_TRAP_NR);

	inकाष्ठाion_poपूर्णांकer_set(regs, utask->vaddr + auprobe->insn_size);

	regs->status |= SR_SPIE;

	वापस 0;
पूर्ण

bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *t)
अणु
	अगर (t->thपढ़ो.bad_cause != UPROBE_TRAP_NR)
		वापस true;

	वापस false;
पूर्ण

bool arch_uprobe_skip_sstep(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	probe_opcode_t insn;
	अचिन्हित दीर्घ addr;

	अगर (!auprobe->simulate)
		वापस false;

	insn = *(probe_opcode_t *)(&auprobe->insn[0]);
	addr = inकाष्ठाion_poपूर्णांकer(regs);

	अगर (auprobe->api.handler)
		auprobe->api.handler(insn, addr, regs);

	वापस true;
पूर्ण

व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	/*
	 * Task has received a fatal संकेत, so reset back to probbed
	 * address.
	 */
	inकाष्ठाion_poपूर्णांकer_set(regs, utask->vaddr);

	regs->status &= ~SR_SPIE;
पूर्ण

bool arch_uretprobe_is_alive(काष्ठा वापस_instance *ret, क्रमागत rp_check ctx,
		काष्ठा pt_regs *regs)
अणु
	अगर (ctx == RP_CHECK_CHAIN_CALL)
		वापस regs->sp <= ret->stack;
	अन्यथा
		वापस regs->sp < ret->stack;
पूर्ण

अचिन्हित दीर्घ
arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline_vaddr,
				  काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ra;

	ra = regs->ra;

	regs->ra = trampoline_vaddr;

	वापस ra;
पूर्ण

पूर्णांक arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ val, व्योम *data)
अणु
	वापस NOTIFY_DONE;
पूर्ण

bool uprobe_अवरोधpoपूर्णांक_handler(काष्ठा pt_regs *regs)
अणु
	अगर (uprobe_pre_sstep_notअगरier(regs))
		वापस true;

	वापस false;
पूर्ण

bool uprobe_single_step_handler(काष्ठा pt_regs *regs)
अणु
	अगर (uprobe_post_sstep_notअगरier(regs))
		वापस true;

	वापस false;
पूर्ण

व्योम arch_uprobe_copy_ixol(काष्ठा page *page, अचिन्हित दीर्घ vaddr,
			   व्योम *src, अचिन्हित दीर्घ len)
अणु
	/* Initialize the slot */
	व्योम *kaddr = kmap_atomic(page);
	व्योम *dst = kaddr + (vaddr & ~PAGE_MASK);

	स_नकल(dst, src, len);

	/* Add eअवरोध behind opcode to simulate singlestep */
	अगर (vaddr) अणु
		dst += GET_INSN_LENGTH(*(probe_opcode_t *)src);
		*(uprobe_opcode_t *)dst = __BUG_INSN_32;
	पूर्ण

	kunmap_atomic(kaddr);

	/*
	 * We probably need flush_icache_user_page() but it needs vma.
	 * This should work on most of architectures by शेष. If
	 * architecture needs to करो something dअगरferent it can define
	 * its own version of the function.
	 */
	flush_dcache_page(page);
पूर्ण

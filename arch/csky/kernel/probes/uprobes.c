<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2016 Pratyush Anand <panand@redhat.com>
 */
#समावेश <linux/highस्मृति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/uprobes.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "decode-insn.h"

#घोषणा UPROBE_TRAP_NR	अच_पूर्णांक_उच्च

bool is_swbp_insn(uprobe_opcode_t *insn)
अणु
	वापस (*insn & 0xffff) == UPROBE_SWBP_INSN;
पूर्ण

अचिन्हित दीर्घ uprobe_get_swbp_addr(काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr)
अणु
	probe_opcode_t insn;

	insn = *(probe_opcode_t *)(&auprobe->insn[0]);

	auprobe->insn_size = is_insn32(insn) ? 4 : 2;

	चयन (csky_probe_decode_insn(&insn, &auprobe->api)) अणु
	हाल INSN_REJECTED:
		वापस -EINVAL;

	हाल INSN_GOOD_NO_SLOT:
		auprobe->simulate = true;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	utask->autask.saved_trap_no = current->thपढ़ो.trap_no;
	current->thपढ़ो.trap_no = UPROBE_TRAP_NR;

	inकाष्ठाion_poपूर्णांकer_set(regs, utask->xol_vaddr);

	user_enable_single_step(current);

	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	WARN_ON_ONCE(current->thपढ़ो.trap_no != UPROBE_TRAP_NR);

	inकाष्ठाion_poपूर्णांकer_set(regs, utask->vaddr + auprobe->insn_size);

	user_disable_single_step(current);

	वापस 0;
पूर्ण

bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *t)
अणु
	अगर (t->thपढ़ो.trap_no != UPROBE_TRAP_NR)
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

	user_disable_single_step(current);
पूर्ण

bool arch_uretprobe_is_alive(काष्ठा वापस_instance *ret, क्रमागत rp_check ctx,
		काष्ठा pt_regs *regs)
अणु
	अगर (ctx == RP_CHECK_CHAIN_CALL)
		वापस regs->usp <= ret->stack;
	अन्यथा
		वापस regs->usp < ret->stack;
पूर्ण

अचिन्हित दीर्घ
arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline_vaddr,
				  काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ra;

	ra = regs->lr;

	regs->lr = trampoline_vaddr;

	वापस ra;
पूर्ण

पूर्णांक arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ val, व्योम *data)
अणु
	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक uprobe_अवरोधpoपूर्णांक_handler(काष्ठा pt_regs *regs)
अणु
	अगर (uprobe_pre_sstep_notअगरier(regs))
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक uprobe_single_step_handler(काष्ठा pt_regs *regs)
अणु
	अगर (uprobe_post_sstep_notअगरier(regs))
		वापस 1;

	वापस 0;
पूर्ण

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

#घोषणा UPROBE_INV_FAULT_CODE	अच_पूर्णांक_उच्च

व्योम arch_uprobe_copy_ixol(काष्ठा page *page, अचिन्हित दीर्घ vaddr,
		व्योम *src, अचिन्हित दीर्घ len)
अणु
	व्योम *xol_page_kaddr = kmap_atomic(page);
	व्योम *dst = xol_page_kaddr + (vaddr & ~PAGE_MASK);

	/* Initialize the slot */
	स_नकल(dst, src, len);

	/* flush caches (dcache/icache) */
	sync_icache_aliases(dst, len);

	kunmap_atomic(xol_page_kaddr);
पूर्ण

अचिन्हित दीर्घ uprobe_get_swbp_addr(काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr)
अणु
	probe_opcode_t insn;

	/* TODO: Currently we करो not support AARCH32 inकाष्ठाion probing */
	अगर (mm->context.flags & MMCF_AARCH32)
		वापस -EOPNOTSUPP;
	अन्यथा अगर (!IS_ALIGNED(addr, AARCH64_INSN_SIZE))
		वापस -EINVAL;

	insn = *(probe_opcode_t *)(&auprobe->insn[0]);

	चयन (arm_probe_decode_insn(insn, &auprobe->api)) अणु
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

	/* Initialize with an invalid fault code to detect अगर ol insn trapped */
	current->thपढ़ो.fault_code = UPROBE_INV_FAULT_CODE;

	/* Inकाष्ठाion poपूर्णांकs to execute ol */
	inकाष्ठाion_poपूर्णांकer_set(regs, utask->xol_vaddr);

	user_enable_single_step(current);

	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	WARN_ON_ONCE(current->thपढ़ो.fault_code != UPROBE_INV_FAULT_CODE);

	/* Inकाष्ठाion poपूर्णांकs to execute next to अवरोधpoपूर्णांक address */
	inकाष्ठाion_poपूर्णांकer_set(regs, utask->vaddr + 4);

	user_disable_single_step(current);

	वापस 0;
पूर्ण
bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *t)
अणु
	/*
	 * Between arch_uprobe_pre_xol and arch_uprobe_post_xol, अगर an xol
	 * insn itself is trapped, then detect the हाल with the help of
	 * invalid fault code which is being set in arch_uprobe_pre_xol
	 */
	अगर (t->thपढ़ो.fault_code != UPROBE_INV_FAULT_CODE)
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
	/*
	 * If a simple branch inकाष्ठाion (B) was called क्रम retprobed
	 * assembly label then वापस true even when regs->sp and ret->stack
	 * are same. It will ensure that cleanup and reporting of वापस
	 * instances corresponding to callee label is करोne when
	 * handle_trampoline क्रम called function is executed.
	 */
	अगर (ctx == RP_CHECK_CHAIN_CALL)
		वापस regs->sp <= ret->stack;
	अन्यथा
		वापस regs->sp < ret->stack;
पूर्ण

अचिन्हित दीर्घ
arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline_vaddr,
				  काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_ret_vaddr;

	orig_ret_vaddr = procedure_link_poपूर्णांकer(regs);
	/* Replace the वापस addr with trampoline addr */
	procedure_link_poपूर्णांकer_set(regs, trampoline_vaddr);

	वापस orig_ret_vaddr;
पूर्ण

पूर्णांक arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ val, व्योम *data)
अणु
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक uprobe_अवरोधpoपूर्णांक_handler(काष्ठा pt_regs *regs,
		अचिन्हित पूर्णांक esr)
अणु
	अगर (uprobe_pre_sstep_notअगरier(regs))
		वापस DBG_HOOK_HANDLED;

	वापस DBG_HOOK_ERROR;
पूर्ण

अटल पूर्णांक uprobe_single_step_handler(काष्ठा pt_regs *regs,
		अचिन्हित पूर्णांक esr)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	WARN_ON(utask && (inकाष्ठाion_poपूर्णांकer(regs) != utask->xol_vaddr + 4));
	अगर (uprobe_post_sstep_notअगरier(regs))
		वापस DBG_HOOK_HANDLED;

	वापस DBG_HOOK_ERROR;
पूर्ण

/* uprobe अवरोधpoपूर्णांक handler hook */
अटल काष्ठा अवरोध_hook uprobes_अवरोध_hook = अणु
	.imm = UPROBES_BRK_IMM,
	.fn = uprobe_अवरोधpoपूर्णांक_handler,
पूर्ण;

/* uprobe single step handler hook */
अटल काष्ठा step_hook uprobes_step_hook = अणु
	.fn = uprobe_single_step_handler,
पूर्ण;

अटल पूर्णांक __init arch_init_uprobes(व्योम)
अणु
	रेजिस्टर_user_अवरोध_hook(&uprobes_अवरोध_hook);
	रेजिस्टर_user_step_hook(&uprobes_step_hook);

	वापस 0;
पूर्ण

device_initcall(arch_init_uprobes);

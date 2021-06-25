<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Here's a sample kernel module showing the use of kprobes to dump a
 * stack trace and selected रेजिस्टरs when kernel_clone() is called.
 *
 * For more inक्रमmation on theory of operation of kprobes, see
 * Documentation/trace/kprobes.rst
 *
 * You will see the trace data in /var/log/messages and on the console
 * whenever kernel_clone() is invoked to create a new process.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kprobes.h>

#घोषणा MAX_SYMBOL_LEN	64
अटल अक्षर symbol[MAX_SYMBOL_LEN] = "kernel_clone";
module_param_string(symbol, symbol, माप(symbol), 0644);

/* For each probe you need to allocate a kprobe काष्ठाure */
अटल काष्ठा kprobe kp = अणु
	.symbol_name	= symbol,
पूर्ण;

/* kprobe pre_handler: called just beक्रमe the probed inकाष्ठाion is executed */
अटल पूर्णांक __kprobes handler_pre(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_X86
	pr_info("<%s> pre_handler: p->addr = 0x%p, ip = %lx, flags = 0x%lx\n",
		p->symbol_name, p->addr, regs->ip, regs->flags);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC
	pr_info("<%s> pre_handler: p->addr = 0x%p, nip = 0x%lx, msr = 0x%lx\n",
		p->symbol_name, p->addr, regs->nip, regs->msr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MIPS
	pr_info("<%s> pre_handler: p->addr = 0x%p, epc = 0x%lx, status = 0x%lx\n",
		p->symbol_name, p->addr, regs->cp0_epc, regs->cp0_status);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64
	pr_info("<%s> pre_handler: p->addr = 0x%p, pc = 0x%lx,"
			" pstate = 0x%lx\n",
		p->symbol_name, p->addr, (दीर्घ)regs->pc, (दीर्घ)regs->pstate);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM
	pr_info("<%s> pre_handler: p->addr = 0x%p, pc = 0x%lx, cpsr = 0x%lx\n",
		p->symbol_name, p->addr, (दीर्घ)regs->ARM_pc, (दीर्घ)regs->ARM_cpsr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_RISCV
	pr_info("<%s> pre_handler: p->addr = 0x%p, pc = 0x%lx, status = 0x%lx\n",
		p->symbol_name, p->addr, regs->epc, regs->status);
#पूर्ण_अगर
#अगर_घोषित CONFIG_S390
	pr_info("<%s> pre_handler: p->addr, 0x%p, ip = 0x%lx, flags = 0x%lx\n",
		p->symbol_name, p->addr, regs->psw.addr, regs->flags);
#पूर्ण_अगर

	/* A dump_stack() here will give a stack backtrace */
	वापस 0;
पूर्ण

/* kprobe post_handler: called after the probed inकाष्ठाion is executed */
अटल व्योम __kprobes handler_post(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
				अचिन्हित दीर्घ flags)
अणु
#अगर_घोषित CONFIG_X86
	pr_info("<%s> post_handler: p->addr = 0x%p, flags = 0x%lx\n",
		p->symbol_name, p->addr, regs->flags);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC
	pr_info("<%s> post_handler: p->addr = 0x%p, msr = 0x%lx\n",
		p->symbol_name, p->addr, regs->msr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MIPS
	pr_info("<%s> post_handler: p->addr = 0x%p, status = 0x%lx\n",
		p->symbol_name, p->addr, regs->cp0_status);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64
	pr_info("<%s> post_handler: p->addr = 0x%p, pstate = 0x%lx\n",
		p->symbol_name, p->addr, (दीर्घ)regs->pstate);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM
	pr_info("<%s> post_handler: p->addr = 0x%p, cpsr = 0x%lx\n",
		p->symbol_name, p->addr, (दीर्घ)regs->ARM_cpsr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_RISCV
	pr_info("<%s> post_handler: p->addr = 0x%p, status = 0x%lx\n",
		p->symbol_name, p->addr, regs->status);
#पूर्ण_अगर
#अगर_घोषित CONFIG_S390
	pr_info("<%s> pre_handler: p->addr, 0x%p, flags = 0x%lx\n",
		p->symbol_name, p->addr, regs->flags);
#पूर्ण_अगर
पूर्ण

/*
 * fault_handler: this is called अगर an exception is generated क्रम any
 * inकाष्ठाion within the pre- or post-handler, or when Kprobes
 * single-steps the probed inकाष्ठाion.
 */
अटल पूर्णांक handler_fault(काष्ठा kprobe *p, काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	pr_info("fault_handler: p->addr = 0x%p, trap #%dn", p->addr, trapnr);
	/* Return 0 because we करोn't handle the fault. */
	वापस 0;
पूर्ण
/* NOKPROBE_SYMBOL() is also available */
NOKPROBE_SYMBOL(handler_fault);

अटल पूर्णांक __init kprobe_init(व्योम)
अणु
	पूर्णांक ret;
	kp.pre_handler = handler_pre;
	kp.post_handler = handler_post;
	kp.fault_handler = handler_fault;

	ret = रेजिस्टर_kprobe(&kp);
	अगर (ret < 0) अणु
		pr_err("register_kprobe failed, returned %d\n", ret);
		वापस ret;
	पूर्ण
	pr_info("Planted kprobe at %p\n", kp.addr);
	वापस 0;
पूर्ण

अटल व्योम __निकास kprobe_निकास(व्योम)
अणु
	unरेजिस्टर_kprobe(&kp);
	pr_info("kprobe at %p unregistered\n", kp.addr);
पूर्ण

module_init(kprobe_init)
module_निकास(kprobe_निकास)
MODULE_LICENSE("GPL");

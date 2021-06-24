<शैली गुरु>
/*
 * Copyright (C) 2001 - 2003 Jeff Dike (jdike@addtoit.com)
 * Licensed under the GPL
 */

#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/kallsyms.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sysrq.h>

/* This is declared by <linux/sched.h> */
व्योम show_regs(काष्ठा pt_regs *regs)
अणु
        prपूर्णांकk("\n");
        prपूर्णांकk("EIP: %04lx:[<%08lx>] CPU: %d %s", 
	       0xffff & PT_REGS_CS(regs), PT_REGS_IP(regs),
	       smp_processor_id(), prपूर्णांक_taपूर्णांकed());
        अगर (PT_REGS_CS(regs) & 3)
                prपूर्णांकk(" ESP: %04lx:%08lx", 0xffff & PT_REGS_SS(regs),
		       PT_REGS_SP(regs));
        prपूर्णांकk(" EFLAGS: %08lx\n    %s\n", PT_REGS_EFLAGS(regs),
	       prपूर्णांक_taपूर्णांकed());
        prपूर्णांकk("EAX: %08lx EBX: %08lx ECX: %08lx EDX: %08lx\n",
               PT_REGS_AX(regs), PT_REGS_BX(regs), 
	       PT_REGS_CX(regs), PT_REGS_DX(regs));
        prपूर्णांकk("ESI: %08lx EDI: %08lx EBP: %08lx",
	       PT_REGS_SI(regs), PT_REGS_DI(regs), PT_REGS_BP(regs));
        prपूर्णांकk(" DS: %04lx ES: %04lx\n",
	       0xffff & PT_REGS_DS(regs), 
	       0xffff & PT_REGS_ES(regs));
पूर्ण

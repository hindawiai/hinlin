<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC traps.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 *
 *  Here we handle the अवरोध vectors not used by the प्रणाली call
 *  mechanism, as well as some general stack/रेजिस्टर dumping
 *  things.
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/extable.h>
#समावेश <linux/kmod.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/unwinder.h>
#समावेश <यंत्र/sections.h>

पूर्णांक kstack_depth_to_prपूर्णांक = 0x180;
पूर्णांक lwa_flag;
अचिन्हित दीर्घ __user *lwa_addr;

व्योम prपूर्णांक_trace(व्योम *data, अचिन्हित दीर्घ addr, पूर्णांक reliable)
अणु
	स्थिर अक्षर *loglvl = data;

	prपूर्णांकk("%s[<%p>] %s%pS\n", loglvl, (व्योम *) addr, reliable ? "" : "? ",
	       (व्योम *) addr);
पूर्ण

/* displays a लघु stack trace */
व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *esp, स्थिर अक्षर *loglvl)
अणु
	अगर (esp == शून्य)
		esp = (अचिन्हित दीर्घ *)&esp;

	prपूर्णांकk("%sCall trace:\n", loglvl);
	unwind_stack((व्योम *)loglvl, esp, prपूर्णांक_trace);
पूर्ण

व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	पूर्णांक in_kernel = 1;
	अचिन्हित दीर्घ esp;

	esp = (अचिन्हित दीर्घ)(regs->sp);
	अगर (user_mode(regs))
		in_kernel = 0;

	prपूर्णांकk("CPU #: %d\n"
	       "   PC: %08lx    SR: %08lx    SP: %08lx\n",
	       smp_processor_id(), regs->pc, regs->sr, regs->sp);
	prपूर्णांकk("GPR00: %08lx GPR01: %08lx GPR02: %08lx GPR03: %08lx\n",
	       0L, regs->gpr[1], regs->gpr[2], regs->gpr[3]);
	prपूर्णांकk("GPR04: %08lx GPR05: %08lx GPR06: %08lx GPR07: %08lx\n",
	       regs->gpr[4], regs->gpr[5], regs->gpr[6], regs->gpr[7]);
	prपूर्णांकk("GPR08: %08lx GPR09: %08lx GPR10: %08lx GPR11: %08lx\n",
	       regs->gpr[8], regs->gpr[9], regs->gpr[10], regs->gpr[11]);
	prपूर्णांकk("GPR12: %08lx GPR13: %08lx GPR14: %08lx GPR15: %08lx\n",
	       regs->gpr[12], regs->gpr[13], regs->gpr[14], regs->gpr[15]);
	prपूर्णांकk("GPR16: %08lx GPR17: %08lx GPR18: %08lx GPR19: %08lx\n",
	       regs->gpr[16], regs->gpr[17], regs->gpr[18], regs->gpr[19]);
	prपूर्णांकk("GPR20: %08lx GPR21: %08lx GPR22: %08lx GPR23: %08lx\n",
	       regs->gpr[20], regs->gpr[21], regs->gpr[22], regs->gpr[23]);
	prपूर्णांकk("GPR24: %08lx GPR25: %08lx GPR26: %08lx GPR27: %08lx\n",
	       regs->gpr[24], regs->gpr[25], regs->gpr[26], regs->gpr[27]);
	prपूर्णांकk("GPR28: %08lx GPR29: %08lx GPR30: %08lx GPR31: %08lx\n",
	       regs->gpr[28], regs->gpr[29], regs->gpr[30], regs->gpr[31]);
	prपूर्णांकk("  RES: %08lx oGPR11: %08lx\n",
	       regs->gpr[11], regs->orig_gpr11);

	prपूर्णांकk("Process %s (pid: %d, stackpage=%08lx)\n",
	       current->comm, current->pid, (अचिन्हित दीर्घ)current);
	/*
	 * When in-kernel, we also prपूर्णांक out the stack and code at the
	 * समय of the fault..
	 */
	अगर (in_kernel) अणु

		prपूर्णांकk("\nStack: ");
		show_stack(शून्य, (अचिन्हित दीर्घ *)esp, KERN_EMERG);

		prपूर्णांकk("\nCode: ");
		अगर (regs->pc < PAGE_OFFSET)
			जाओ bad;

		क्रम (i = -24; i < 24; i++) अणु
			अचिन्हित अक्षर c;
			अगर (__get_user(c, &((अचिन्हित अक्षर *)regs->pc)[i])) अणु
bad:
				prपूर्णांकk(" Bad PC value.");
				अवरोध;
			पूर्ण

			अगर (i == 0)
				prपूर्णांकk("(%02x) ", c);
			अन्यथा
				prपूर्णांकk("%02x ", c);
		पूर्ण
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

व्योम nommu_dump_state(काष्ठा pt_regs *regs,
		      अचिन्हित दीर्घ ea, अचिन्हित दीर्घ vector)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ addr, stack = regs->sp;

	prपूर्णांकk("\n\r[nommu_dump_state] :: ea %lx, vector %lx\n\r", ea, vector);

	prपूर्णांकk("CPU #: %d\n"
	       "   PC: %08lx    SR: %08lx    SP: %08lx\n",
	       0, regs->pc, regs->sr, regs->sp);
	prपूर्णांकk("GPR00: %08lx GPR01: %08lx GPR02: %08lx GPR03: %08lx\n",
	       0L, regs->gpr[1], regs->gpr[2], regs->gpr[3]);
	prपूर्णांकk("GPR04: %08lx GPR05: %08lx GPR06: %08lx GPR07: %08lx\n",
	       regs->gpr[4], regs->gpr[5], regs->gpr[6], regs->gpr[7]);
	prपूर्णांकk("GPR08: %08lx GPR09: %08lx GPR10: %08lx GPR11: %08lx\n",
	       regs->gpr[8], regs->gpr[9], regs->gpr[10], regs->gpr[11]);
	prपूर्णांकk("GPR12: %08lx GPR13: %08lx GPR14: %08lx GPR15: %08lx\n",
	       regs->gpr[12], regs->gpr[13], regs->gpr[14], regs->gpr[15]);
	prपूर्णांकk("GPR16: %08lx GPR17: %08lx GPR18: %08lx GPR19: %08lx\n",
	       regs->gpr[16], regs->gpr[17], regs->gpr[18], regs->gpr[19]);
	prपूर्णांकk("GPR20: %08lx GPR21: %08lx GPR22: %08lx GPR23: %08lx\n",
	       regs->gpr[20], regs->gpr[21], regs->gpr[22], regs->gpr[23]);
	prपूर्णांकk("GPR24: %08lx GPR25: %08lx GPR26: %08lx GPR27: %08lx\n",
	       regs->gpr[24], regs->gpr[25], regs->gpr[26], regs->gpr[27]);
	prपूर्णांकk("GPR28: %08lx GPR29: %08lx GPR30: %08lx GPR31: %08lx\n",
	       regs->gpr[28], regs->gpr[29], regs->gpr[30], regs->gpr[31]);
	prपूर्णांकk("  RES: %08lx oGPR11: %08lx\n",
	       regs->gpr[11], regs->orig_gpr11);

	prपूर्णांकk("Process %s (pid: %d, stackpage=%08lx)\n",
	       ((काष्ठा task_काष्ठा *)(__pa(current)))->comm,
	       ((काष्ठा task_काष्ठा *)(__pa(current)))->pid,
	       (अचिन्हित दीर्घ)current);

	prपूर्णांकk("\nStack: ");
	prपूर्णांकk("Stack dump [0x%08lx]:\n", (अचिन्हित दीर्घ)stack);
	क्रम (i = 0; i < kstack_depth_to_prपूर्णांक; i++) अणु
		अगर (((दीर्घ)stack & (THREAD_SIZE - 1)) == 0)
			अवरोध;
		stack++;

		prपूर्णांकk("%lx :: sp + %02d: 0x%08lx\n", stack, i * 4,
		       *((अचिन्हित दीर्घ *)(__pa(stack))));
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Call Trace:   ");
	i = 1;
	जबतक (((दीर्घ)stack & (THREAD_SIZE - 1)) != 0) अणु
		addr = *((अचिन्हित दीर्घ *)__pa(stack));
		stack++;

		अगर (kernel_text_address(addr)) अणु
			अगर (i && ((i % 6) == 0))
				prपूर्णांकk("\n ");
			prपूर्णांकk(" [<%08lx>]", addr);
			i++;
		पूर्ण
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("\nCode: ");

	क्रम (i = -24; i < 24; i++) अणु
		अचिन्हित अक्षर c;
		c = ((अचिन्हित अक्षर *)(__pa(regs->pc)))[i];

		अगर (i == 0)
			prपूर्णांकk("(%02x) ", c);
		अन्यथा
			prपूर्णांकk("%02x ", c);
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

/* This is normally the 'Oops' routine */
व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु

	console_verbose();
	prपूर्णांकk("\n%s#: %04lx\n", str, err & 0xffff);
	show_रेजिस्टरs(regs);
#अगर_घोषित CONFIG_JUMP_UPON_UNHANDLED_EXCEPTION
	prपूर्णांकk("\n\nUNHANDLED_EXCEPTION: entering infinite loop\n");

	/* shut करोwn पूर्णांकerrupts */
	local_irq_disable();

	__यंत्र__ __अस्थिर__("l.nop   1");
	करो अणुपूर्ण जबतक (1);
#पूर्ण_अगर
	करो_निकास(संक_अंश);
पूर्ण

/* This is normally the 'Oops' routine */
व्योम die_अगर_kernel(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अगर (user_mode(regs))
		वापस;

	die(str, regs, err);
पूर्ण

व्योम unhandled_exception(काष्ठा pt_regs *regs, पूर्णांक ea, पूर्णांक vector)
अणु
	prपूर्णांकk("Unable to handle exception at EA =0x%x, vector 0x%x",
	       ea, vector);
	die("Oops", regs, 9);
पूर्ण

व्योम __init trap_init(व्योम)
अणु
	/* Nothing needs to be करोne */
पूर्ण

यंत्रlinkage व्योम करो_trap(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	क्रमce_sig_fault(SIGTRAP, TRAP_BRKPT, (व्योम __user *)regs->pc);
पूर्ण

यंत्रlinkage व्योम करो_unaligned_access(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	अगर (user_mode(regs)) अणु
		/* Send a SIGBUS */
		क्रमce_sig_fault(SIGBUS, BUS_ADRALN, (व्योम __user *)address);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("KERNEL: Unaligned Access 0x%.8lx\n", address);
		show_रेजिस्टरs(regs);
		die("Die:", regs, address);
	पूर्ण

पूर्ण

यंत्रlinkage व्योम करो_bus_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	अगर (user_mode(regs)) अणु
		/* Send a SIGBUS */
		क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *)address);
	पूर्ण अन्यथा अणु		/* Kernel mode */
		prपूर्णांकk("KERNEL: Bus error (SIGBUS) 0x%.8lx\n", address);
		show_रेजिस्टरs(regs);
		die("Die:", regs, address);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक in_delay_slot(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_OPENRISC_NO_SPR_SR_DSX
	/* No delay slot flag, करो the old way */
	अचिन्हित पूर्णांक op, insn;

	insn = *((अचिन्हित पूर्णांक *)regs->pc);
	op = insn >> 26;
	चयन (op) अणु
	हाल 0x00: /* l.j */
	हाल 0x01: /* l.jal */
	हाल 0x03: /* l.bnf */
	हाल 0x04: /* l.bf */
	हाल 0x11: /* l.jr */
	हाल 0x12: /* l.jalr */
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
#अन्यथा
	वापस mfspr(SPR_SR) & SPR_SR_DSX;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम adjust_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	पूर्णांक displacement;
	अचिन्हित पूर्णांक rb, op, jmp;

	अगर (unlikely(in_delay_slot(regs))) अणु
		/* In delay slot, inकाष्ठाion at pc is a branch, simulate it */
		jmp = *((अचिन्हित पूर्णांक *)regs->pc);

		displacement = sign_extend32(((jmp) & 0x3ffffff) << 2, 27);
		rb = (jmp & 0x0000ffff) >> 11;
		op = jmp >> 26;

		चयन (op) अणु
		हाल 0x00: /* l.j */
			regs->pc += displacement;
			वापस;
		हाल 0x01: /* l.jal */
			regs->pc += displacement;
			regs->gpr[9] = regs->pc + 8;
			वापस;
		हाल 0x03: /* l.bnf */
			अगर (regs->sr & SPR_SR_F)
				regs->pc += 8;
			अन्यथा
				regs->pc += displacement;
			वापस;
		हाल 0x04: /* l.bf */
			अगर (regs->sr & SPR_SR_F)
				regs->pc += displacement;
			अन्यथा
				regs->pc += 8;
			वापस;
		हाल 0x11: /* l.jr */
			regs->pc = regs->gpr[rb];
			वापस;
		हाल 0x12: /* l.jalr */
			regs->pc = regs->gpr[rb];
			regs->gpr[9] = regs->pc + 8;
			वापस;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		regs->pc += 4;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम simulate_lwa(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
				अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित पूर्णांक ra, rd;
	अचिन्हित दीर्घ value;
	अचिन्हित दीर्घ orig_pc;
	दीर्घ imm;

	स्थिर काष्ठा exception_table_entry *entry;

	orig_pc = regs->pc;
	adjust_pc(regs, address);

	ra = (insn >> 16) & 0x1f;
	rd = (insn >> 21) & 0x1f;
	imm = (लघु)insn;
	lwa_addr = (अचिन्हित दीर्घ __user *)(regs->gpr[ra] + imm);

	अगर ((अचिन्हित दीर्घ)lwa_addr & 0x3) अणु
		करो_unaligned_access(regs, address);
		वापस;
	पूर्ण

	अगर (get_user(value, lwa_addr)) अणु
		अगर (user_mode(regs)) अणु
			क्रमce_sig(संक_अंश);
			वापस;
		पूर्ण

		अगर ((entry = search_exception_tables(orig_pc))) अणु
			regs->pc = entry->fixup;
			वापस;
		पूर्ण

		/* kernel access in kernel space, load it directly */
		value = *((अचिन्हित दीर्घ *)lwa_addr);
	पूर्ण

	lwa_flag = 1;
	regs->gpr[rd] = value;
पूर्ण

अटल अंतरभूत व्योम simulate_swa(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
				अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित दीर्घ __user *vaddr;
	अचिन्हित दीर्घ orig_pc;
	अचिन्हित पूर्णांक ra, rb;
	दीर्घ imm;

	स्थिर काष्ठा exception_table_entry *entry;

	orig_pc = regs->pc;
	adjust_pc(regs, address);

	ra = (insn >> 16) & 0x1f;
	rb = (insn >> 11) & 0x1f;
	imm = (लघु)(((insn & 0x2200000) >> 10) | (insn & 0x7ff));
	vaddr = (अचिन्हित दीर्घ __user *)(regs->gpr[ra] + imm);

	अगर (!lwa_flag || vaddr != lwa_addr) अणु
		regs->sr &= ~SPR_SR_F;
		वापस;
	पूर्ण

	अगर ((अचिन्हित दीर्घ)vaddr & 0x3) अणु
		करो_unaligned_access(regs, address);
		वापस;
	पूर्ण

	अगर (put_user(regs->gpr[rb], vaddr)) अणु
		अगर (user_mode(regs)) अणु
			क्रमce_sig(संक_अंश);
			वापस;
		पूर्ण

		अगर ((entry = search_exception_tables(orig_pc))) अणु
			regs->pc = entry->fixup;
			वापस;
		पूर्ण

		/* kernel access in kernel space, store it directly */
		*((अचिन्हित दीर्घ *)vaddr) = regs->gpr[rb];
	पूर्ण

	lwa_flag = 0;
	regs->sr |= SPR_SR_F;
पूर्ण

#घोषणा INSN_LWA	0x1b
#घोषणा INSN_SWA	0x33

यंत्रlinkage व्योम करो_illegal_inकाष्ठाion(काष्ठा pt_regs *regs,
				       अचिन्हित दीर्घ address)
अणु
	अचिन्हित पूर्णांक op;
	अचिन्हित पूर्णांक insn = *((अचिन्हित पूर्णांक *)address);

	op = insn >> 26;

	चयन (op) अणु
	हाल INSN_LWA:
		simulate_lwa(regs, address, insn);
		वापस;

	हाल INSN_SWA:
		simulate_swa(regs, address, insn);
		वापस;

	शेष:
		अवरोध;
	पूर्ण

	अगर (user_mode(regs)) अणु
		/* Send a संक_अवैध */
		क्रमce_sig_fault(संक_अवैध, ILL_ILLOPC, (व्योम __user *)address);
	पूर्ण अन्यथा अणु		/* Kernel mode */
		prपूर्णांकk("KERNEL: Illegal instruction (SIGILL) 0x%.8lx\n",
		       address);
		show_रेजिस्टरs(regs);
		die("Die:", regs, address);
	पूर्ण
पूर्ण

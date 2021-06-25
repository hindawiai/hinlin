<शैली गुरु>
/*
 * Copyright 2003 PathScale, Inc.
 * Copyright (C) 2003 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 *
 * Licensed under the GPL
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#घोषणा __FRAME_OFFSETS
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace-abi.h>

/*
 * determines which flags the user has access to.
 * 1 = access 0 = no access
 */
#घोषणा FLAG_MASK 0x44dd5UL

अटल स्थिर पूर्णांक reg_offsets[] =
अणु
	[R8 >> 3] = HOST_R8,
	[R9 >> 3] = HOST_R9,
	[R10 >> 3] = HOST_R10,
	[R11 >> 3] = HOST_R11,
	[R12 >> 3] = HOST_R12,
	[R13 >> 3] = HOST_R13,
	[R14 >> 3] = HOST_R14,
	[R15 >> 3] = HOST_R15,
	[RIP >> 3] = HOST_IP,
	[RSP >> 3] = HOST_SP,
	[RAX >> 3] = HOST_AX,
	[RBX >> 3] = HOST_BX,
	[RCX >> 3] = HOST_CX,
	[RDX >> 3] = HOST_DX,
	[RSI >> 3] = HOST_SI,
	[RDI >> 3] = HOST_DI,
	[RBP >> 3] = HOST_BP,
	[CS >> 3] = HOST_CS,
	[SS >> 3] = HOST_SS,
	[FS_BASE >> 3] = HOST_FS_BASE,
	[GS_BASE >> 3] = HOST_GS_BASE,
	[DS >> 3] = HOST_DS,
	[ES >> 3] = HOST_ES,
	[FS >> 3] = HOST_FS,
	[GS >> 3] = HOST_GS,
	[EFLAGS >> 3] = HOST_EFLAGS,
	[ORIG_RAX >> 3] = HOST_ORIG_AX,
पूर्ण;

पूर्णांक putreg(काष्ठा task_काष्ठा *child, पूर्णांक regno, अचिन्हित दीर्घ value)
अणु
	चयन (regno) अणु
	हाल R8:
	हाल R9:
	हाल R10:
	हाल R11:
	हाल R12:
	हाल R13:
	हाल R14:
	हाल R15:
	हाल RIP:
	हाल RSP:
	हाल RAX:
	हाल RBX:
	हाल RCX:
	हाल RDX:
	हाल RSI:
	हाल RDI:
	हाल RBP:
		अवरोध;

	हाल ORIG_RAX:
		/* Update the syscall number. */
		UPT_SYSCALL_NR(&child->thपढ़ो.regs.regs) = value;
		अवरोध;

	हाल FS:
	हाल GS:
	हाल DS:
	हाल ES:
	हाल SS:
	हाल CS:
		अगर (value && (value & 3) != 3)
			वापस -EIO;
		value &= 0xffff;
		अवरोध;

	हाल FS_BASE:
	हाल GS_BASE:
		अगर (!((value >> 48) == 0 || (value >> 48) == 0xffff))
			वापस -EIO;
		अवरोध;

	हाल EFLAGS:
		value &= FLAG_MASK;
		child->thपढ़ो.regs.regs.gp[HOST_EFLAGS] |= value;
		वापस 0;

	शेष:
		panic("Bad register in putreg(): %d\n", regno);
	पूर्ण

	child->thपढ़ो.regs.regs.gp[reg_offsets[regno >> 3]] = value;
	वापस 0;
पूर्ण

पूर्णांक poke_user(काष्ठा task_काष्ठा *child, दीर्घ addr, दीर्घ data)
अणु
	अगर ((addr & 3) || addr < 0)
		वापस -EIO;

	अगर (addr < MAX_REG_OFFSET)
		वापस putreg(child, addr, data);
	अन्यथा अगर ((addr >= दुरत्व(काष्ठा user, u_debugreg[0])) &&
		(addr <= दुरत्व(काष्ठा user, u_debugreg[7]))) अणु
		addr -= दुरत्व(काष्ठा user, u_debugreg[0]);
		addr = addr >> 3;
		अगर ((addr == 4) || (addr == 5))
			वापस -EIO;
		child->thपढ़ो.arch.debugregs[addr] = data;
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अचिन्हित दीर्घ getreg(काष्ठा task_काष्ठा *child, पूर्णांक regno)
अणु
	अचिन्हित दीर्घ mask = ~0UL;

	चयन (regno) अणु
	हाल R8:
	हाल R9:
	हाल R10:
	हाल R11:
	हाल R12:
	हाल R13:
	हाल R14:
	हाल R15:
	हाल RIP:
	हाल RSP:
	हाल RAX:
	हाल RBX:
	हाल RCX:
	हाल RDX:
	हाल RSI:
	हाल RDI:
	हाल RBP:
	हाल ORIG_RAX:
	हाल EFLAGS:
	हाल FS_BASE:
	हाल GS_BASE:
		अवरोध;
	हाल FS:
	हाल GS:
	हाल DS:
	हाल ES:
	हाल SS:
	हाल CS:
		mask = 0xffff;
		अवरोध;
	शेष:
		panic("Bad register in getreg: %d\n", regno);
	पूर्ण
	वापस mask & child->thपढ़ो.regs.regs.gp[reg_offsets[regno >> 3]];
पूर्ण

पूर्णांक peek_user(काष्ठा task_काष्ठा *child, दीर्घ addr, दीर्घ data)
अणु
	/* पढ़ो the word at location addr in the USER area. */
	अचिन्हित दीर्घ पंचांगp;

	अगर ((addr & 3) || addr < 0)
		वापस -EIO;

	पंचांगp = 0;  /* Default वापस condition */
	अगर (addr < MAX_REG_OFFSET)
		पंचांगp = getreg(child, addr);
	अन्यथा अगर ((addr >= दुरत्व(काष्ठा user, u_debugreg[0])) &&
		(addr <= दुरत्व(काष्ठा user, u_debugreg[7]))) अणु
		addr -= दुरत्व(काष्ठा user, u_debugreg[0]);
		addr = addr >> 2;
		पंचांगp = child->thपढ़ो.arch.debugregs[addr];
	पूर्ण
	वापस put_user(पंचांगp, (अचिन्हित दीर्घ *) data);
पूर्ण

/* XXX Mostly copied from sys-i386 */
पूर्णांक is_syscall(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित लघु instr;
	पूर्णांक n;

	n = copy_from_user(&instr, (व्योम __user *) addr, माप(instr));
	अगर (n) अणु
		/*
		 * access_process_vm() grants access to vsyscall and stub,
		 * जबतक copy_from_user करोesn't. Maybe access_process_vm is
		 * slow, but that करोesn't matter, since it will be called only
		 * in हाल of singlestepping, अगर copy_from_user failed.
		 */
		n = access_process_vm(current, addr, &instr, माप(instr),
				FOLL_FORCE);
		अगर (n != माप(instr)) अणु
			prपूर्णांकk("is_syscall : failed to read instruction from "
			       "0x%lx\n", addr);
			वापस 1;
		पूर्ण
	पूर्ण
	/* sysenter */
	वापस instr == 0x050f;
पूर्ण

अटल पूर्णांक get_fpregs(काष्ठा user_i387_काष्ठा __user *buf, काष्ठा task_काष्ठा *child)
अणु
	पूर्णांक err, n, cpu = ((काष्ठा thपढ़ो_info *) child->stack)->cpu;
	काष्ठा user_i387_काष्ठा fpregs;

	err = save_i387_रेजिस्टरs(userspace_pid[cpu],
				  (अचिन्हित दीर्घ *) &fpregs);
	अगर (err)
		वापस err;

	n = copy_to_user(buf, &fpregs, माप(fpregs));
	अगर (n > 0)
		वापस -EFAULT;

	वापस n;
पूर्ण

अटल पूर्णांक set_fpregs(काष्ठा user_i387_काष्ठा __user *buf, काष्ठा task_काष्ठा *child)
अणु
	पूर्णांक n, cpu = ((काष्ठा thपढ़ो_info *) child->stack)->cpu;
	काष्ठा user_i387_काष्ठा fpregs;

	n = copy_from_user(&fpregs, buf, माप(fpregs));
	अगर (n > 0)
		वापस -EFAULT;

	वापस restore_i387_रेजिस्टरs(userspace_pid[cpu],
				      (अचिन्हित दीर्घ *) &fpregs);
पूर्ण

दीर्घ subarch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		    अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret = -EIO;
	व्योम __user *datap = (व्योम __user *) data;

	चयन (request) अणु
	हाल PTRACE_GETFPREGS: /* Get the child FPU state. */
		ret = get_fpregs(datap, child);
		अवरोध;
	हाल PTRACE_SETFPREGS: /* Set the child FPU state. */
		ret = set_fpregs(datap, child);
		अवरोध;
	हाल PTRACE_ARCH_PRCTL:
		/* XXX Calls ptrace on the host - needs some SMP thinking */
		ret = arch_prctl(child, data, (व्योम __user *) addr);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

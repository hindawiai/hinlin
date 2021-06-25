<शैली गुरु>
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace-abi.h>
#समावेश <skas.h>

बाह्य पूर्णांक arch_चयन_tls(काष्ठा task_काष्ठा *to);

व्योम arch_चयन_to(काष्ठा task_काष्ठा *to)
अणु
	पूर्णांक err = arch_चयन_tls(to);
	अगर (!err)
		वापस;

	अगर (err != -EINVAL)
		prपूर्णांकk(KERN_WARNING "arch_switch_tls failed, errno %d, "
		       "not EINVAL\n", -err);
	अन्यथा
		prपूर्णांकk(KERN_WARNING "arch_switch_tls failed, errno = EINVAL\n");
पूर्ण

पूर्णांक is_syscall(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित लघु instr;
	पूर्णांक n;

	n = copy_from_user(&instr, (व्योम __user *) addr, माप(instr));
	अगर (n) अणु
		/* access_process_vm() grants access to vsyscall and stub,
		 * जबतक copy_from_user करोesn't. Maybe access_process_vm is
		 * slow, but that करोesn't matter, since it will be called only
		 * in हाल of singlestepping, अगर copy_from_user failed.
		 */
		n = access_process_vm(current, addr, &instr, माप(instr),
				FOLL_FORCE);
		अगर (n != माप(instr)) अणु
			prपूर्णांकk(KERN_ERR "is_syscall : failed to read "
			       "instruction from 0x%lx\n", addr);
			वापस 1;
		पूर्ण
	पूर्ण
	/* पूर्णांक 0x80 or sysenter */
	वापस (instr == 0x80cd) || (instr == 0x340f);
पूर्ण

/* determines which flags the user has access to. */
/* 1 = access 0 = no access */
#घोषणा FLAG_MASK 0x00044dd5

अटल स्थिर पूर्णांक reg_offsets[] = अणु
	[EBX] = HOST_BX,
	[ECX] = HOST_CX,
	[EDX] = HOST_DX,
	[ESI] = HOST_SI,
	[EDI] = HOST_DI,
	[EBP] = HOST_BP,
	[EAX] = HOST_AX,
	[DS] = HOST_DS,
	[ES] = HOST_ES,
	[FS] = HOST_FS,
	[GS] = HOST_GS,
	[EIP] = HOST_IP,
	[CS] = HOST_CS,
	[EFL] = HOST_EFLAGS,
	[UESP] = HOST_SP,
	[SS] = HOST_SS,
	[ORIG_EAX] = HOST_ORIG_AX,
पूर्ण;

पूर्णांक putreg(काष्ठा task_काष्ठा *child, पूर्णांक regno, अचिन्हित दीर्घ value)
अणु
	regno >>= 2;
	चयन (regno) अणु
	हाल EBX:
	हाल ECX:
	हाल EDX:
	हाल ESI:
	हाल EDI:
	हाल EBP:
	हाल EAX:
	हाल EIP:
	हाल UESP:
		अवरोध;
	हाल ORIG_EAX:
		/* Update the syscall number. */
		UPT_SYSCALL_NR(&child->thपढ़ो.regs.regs) = value;
		अवरोध;
	हाल FS:
		अगर (value && (value & 3) != 3)
			वापस -EIO;
		अवरोध;
	हाल GS:
		अगर (value && (value & 3) != 3)
			वापस -EIO;
		अवरोध;
	हाल DS:
	हाल ES:
		अगर (value && (value & 3) != 3)
			वापस -EIO;
		value &= 0xffff;
		अवरोध;
	हाल SS:
	हाल CS:
		अगर ((value & 3) != 3)
			वापस -EIO;
		value &= 0xffff;
		अवरोध;
	हाल EFL:
		value &= FLAG_MASK;
		child->thपढ़ो.regs.regs.gp[HOST_EFLAGS] |= value;
		वापस 0;
	शेष :
		panic("Bad register in putreg() : %d\n", regno);
	पूर्ण
	child->thपढ़ो.regs.regs.gp[reg_offsets[regno]] = value;
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
		addr = addr >> 2;
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

	regno >>= 2;
	चयन (regno) अणु
	हाल FS:
	हाल GS:
	हाल DS:
	हाल ES:
	हाल SS:
	हाल CS:
		mask = 0xffff;
		अवरोध;
	हाल EIP:
	हाल UESP:
	हाल EAX:
	हाल EBX:
	हाल ECX:
	हाल EDX:
	हाल ESI:
	हाल EDI:
	हाल EBP:
	हाल EFL:
	हाल ORIG_EAX:
		अवरोध;
	शेष:
		panic("Bad register in getreg() : %d\n", regno);
	पूर्ण
	वापस mask & child->thपढ़ो.regs.regs.gp[reg_offsets[regno]];
पूर्ण

/* पढ़ो the word at location addr in the USER area. */
पूर्णांक peek_user(काष्ठा task_काष्ठा *child, दीर्घ addr, दीर्घ data)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर ((addr & 3) || addr < 0)
		वापस -EIO;

	पंचांगp = 0;  /* Default वापस condition */
	अगर (addr < MAX_REG_OFFSET) अणु
		पंचांगp = getreg(child, addr);
	पूर्ण
	अन्यथा अगर ((addr >= दुरत्व(काष्ठा user, u_debugreg[0])) &&
		 (addr <= दुरत्व(काष्ठा user, u_debugreg[7]))) अणु
		addr -= दुरत्व(काष्ठा user, u_debugreg[0]);
		addr = addr >> 2;
		पंचांगp = child->thपढ़ो.arch.debugregs[addr];
	पूर्ण
	वापस put_user(पंचांगp, (अचिन्हित दीर्घ __user *) data);
पूर्ण

अटल पूर्णांक get_fpregs(काष्ठा user_i387_काष्ठा __user *buf, काष्ठा task_काष्ठा *child)
अणु
	पूर्णांक err, n, cpu = task_cpu(child);
	काष्ठा user_i387_काष्ठा fpregs;

	err = save_i387_रेजिस्टरs(userspace_pid[cpu],
				  (अचिन्हित दीर्घ *) &fpregs);
	अगर (err)
		वापस err;

	n = copy_to_user(buf, &fpregs, माप(fpregs));
	अगर(n > 0)
		वापस -EFAULT;

	वापस n;
पूर्ण

अटल पूर्णांक set_fpregs(काष्ठा user_i387_काष्ठा __user *buf, काष्ठा task_काष्ठा *child)
अणु
	पूर्णांक n, cpu = task_cpu(child);
	काष्ठा user_i387_काष्ठा fpregs;

	n = copy_from_user(&fpregs, buf, माप(fpregs));
	अगर (n > 0)
		वापस -EFAULT;

	वापस restore_i387_रेजिस्टरs(userspace_pid[cpu],
				    (अचिन्हित दीर्घ *) &fpregs);
पूर्ण

अटल पूर्णांक get_fpxregs(काष्ठा user_fxsr_काष्ठा __user *buf, काष्ठा task_काष्ठा *child)
अणु
	पूर्णांक err, n, cpu = task_cpu(child);
	काष्ठा user_fxsr_काष्ठा fpregs;

	err = save_fpx_रेजिस्टरs(userspace_pid[cpu], (अचिन्हित दीर्घ *) &fpregs);
	अगर (err)
		वापस err;

	n = copy_to_user(buf, &fpregs, माप(fpregs));
	अगर(n > 0)
		वापस -EFAULT;

	वापस n;
पूर्ण

अटल पूर्णांक set_fpxregs(काष्ठा user_fxsr_काष्ठा __user *buf, काष्ठा task_काष्ठा *child)
अणु
	पूर्णांक n, cpu = task_cpu(child);
	काष्ठा user_fxsr_काष्ठा fpregs;

	n = copy_from_user(&fpregs, buf, माप(fpregs));
	अगर (n > 0)
		वापस -EFAULT;

	वापस restore_fpx_रेजिस्टरs(userspace_pid[cpu],
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
	हाल PTRACE_GETFPXREGS: /* Get the child FPU state. */
		ret = get_fpxregs(datap, child);
		अवरोध;
	हाल PTRACE_SETFPXREGS: /* Set the child FPU state. */
		ret = set_fpxregs(datap, child);
		अवरोध;
	शेष:
		ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

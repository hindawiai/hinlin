<शैली गुरु>
/*
 * ptrace क्रम 32-bit processes running on a 64-bit kernel.
 *
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Derived from "arch/m68k/kernel/ptrace.c"
 *  Copyright (C) 1994 by Hamish Macकरोnald
 *  Taken from linux/kernel/ptrace.c and modअगरied क्रम M680x0.
 *  linux/kernel/ptrace.c is by Ross Biro 1/23/92, edited by Linus Torvalds
 *
 * Modअगरied by Cort Dougan (cort@hq.fsmद_असल.com)
 * and Paul Mackerras (paulus@samba.org).
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of
 * this archive क्रम more details.
 */

#समावेश <linux/ptrace.h>
#समावेश <linux/regset.h>
#समावेश <linux/compat.h>

#समावेश <यंत्र/चयन_to.h>

#समावेश "ptrace-decl.h"

/*
 * करोes not yet catch संकेतs sent when the child dies.
 * in निकास.c or in संकेत.c.
 */

/* Macros to workout the correct index क्रम the FPR in the thपढ़ो काष्ठा */
#घोषणा FPRNUMBER(i) (((i) - PT_FPR0) >> 1)
#घोषणा FPRHALF(i) (((i) - PT_FPR0) & 1)
#घोषणा FPRINDEX(i) TS_FPRWIDTH * FPRNUMBER(i) * 2 + FPRHALF(i)

दीर्घ compat_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			compat_uदीर्घ_t caddr, compat_uदीर्घ_t cdata)
अणु
	अचिन्हित दीर्घ addr = caddr;
	अचिन्हित दीर्घ data = cdata;
	पूर्णांक ret;

	चयन (request) अणु
	/*
	 * Read 4 bytes of the other process' storage
	 *  data is a poपूर्णांकer specअगरying where the user wants the
	 *	4 bytes copied पूर्णांकo
	 *  addr is a poपूर्णांकer in the user's storage that contains an 8 byte
	 *	address in the other process of the 4 bytes that is to be पढ़ो
	 * (this is run in a 32-bit process looking at a 64-bit process)
	 * when I and D space are separate, these will need to be fixed.
	 */
	हाल PPC_PTRACE_PEEKTEXT_3264:
	हाल PPC_PTRACE_PEEKDATA_3264: अणु
		u32 पंचांगp;
		पूर्णांक copied;
		u32 __user * addrOthers;

		ret = -EIO;

		/* Get the addr in the other process that we want to पढ़ो */
		अगर (get_user(addrOthers, (u32 __user * __user *)addr) != 0)
			अवरोध;

		copied = ptrace_access_vm(child, (u64)addrOthers, &पंचांगp,
				माप(पंचांगp), FOLL_FORCE);
		अगर (copied != माप(पंचांगp))
			अवरोध;
		ret = put_user(पंचांगp, (u32 __user *)data);
		अवरोध;
	पूर्ण

	/* Read a रेजिस्टर (specअगरied by ADDR) out of the "user area" */
	हाल PTRACE_PEEKUSR: अणु
		पूर्णांक index;
		अचिन्हित दीर्घ पंचांगp;

		ret = -EIO;
		/* convert to index and check */
		index = (अचिन्हित दीर्घ) addr >> 2;
		अगर ((addr & 3) || (index > PT_FPSCR32))
			अवरोध;

		अगर (index < PT_FPR0) अणु
			ret = ptrace_get_reg(child, index, &पंचांगp);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			flush_fp_to_thपढ़ो(child);
			/*
			 * the user space code considers the भग्नing poपूर्णांक
			 * to be an array of अचिन्हित पूर्णांक (32 bits) - the
			 * index passed in is based on this assumption.
			 */
			पंचांगp = ((अचिन्हित पूर्णांक *)child->thपढ़ो.fp_state.fpr)
				[FPRINDEX(index)];
		पूर्ण
		ret = put_user((अचिन्हित पूर्णांक)पंचांगp, (u32 __user *)data);
		अवरोध;
	पूर्ण
  
	/*
	 * Read 4 bytes out of the other process' pt_regs area
	 *  data is a poपूर्णांकer specअगरying where the user wants the
	 *	4 bytes copied पूर्णांकo
	 *  addr is the offset पूर्णांकo the other process' pt_regs काष्ठाure
	 *	that is to be पढ़ो
	 * (this is run in a 32-bit process looking at a 64-bit process)
	 */
	हाल PPC_PTRACE_PEEKUSR_3264: अणु
		u32 index;
		u32 reg32bits;
		u64 पंचांगp;
		u32 numReg;
		u32 part;

		ret = -EIO;
		/* Determine which रेजिस्टर the user wants */
		index = (u64)addr >> 2;
		numReg = index / 2;
		/* Determine which part of the रेजिस्टर the user wants */
		अगर (index % 2)
			part = 1;  /* want the 2nd half of the रेजिस्टर (right-most). */
		अन्यथा
			part = 0;  /* want the 1st half of the रेजिस्टर (left-most). */

		/* Validate the input - check to see अगर address is on the wrong boundary
		 * or beyond the end of the user area
		 */
		अगर ((addr & 3) || numReg > PT_FPSCR)
			अवरोध;

		अगर (numReg >= PT_FPR0) अणु
			flush_fp_to_thपढ़ो(child);
			/* get 64 bit FPR */
			पंचांगp = child->thपढ़ो.fp_state.fpr[numReg - PT_FPR0][0];
		पूर्ण अन्यथा अणु /* रेजिस्टर within PT_REGS काष्ठा */
			अचिन्हित दीर्घ पंचांगp2;
			ret = ptrace_get_reg(child, numReg, &पंचांगp2);
			अगर (ret)
				अवरोध;
			पंचांगp = पंचांगp2;
		पूर्ण 
		reg32bits = ((u32*)&पंचांगp)[part];
		ret = put_user(reg32bits, (u32 __user *)data);
		अवरोध;
	पूर्ण

	/*
	 * Write 4 bytes पूर्णांकo the other process' storage
	 *  data is the 4 bytes that the user wants written
	 *  addr is a poपूर्णांकer in the user's storage that contains an
	 *	8 byte address in the other process where the 4 bytes
	 *	that is to be written
	 * (this is run in a 32-bit process looking at a 64-bit process)
	 * when I and D space are separate, these will need to be fixed.
	 */
	हाल PPC_PTRACE_POKETEXT_3264:
	हाल PPC_PTRACE_POKEDATA_3264: अणु
		u32 पंचांगp = data;
		u32 __user * addrOthers;

		/* Get the addr in the other process that we want to ग_लिखो पूर्णांकo */
		ret = -EIO;
		अगर (get_user(addrOthers, (u32 __user * __user *)addr) != 0)
			अवरोध;
		ret = 0;
		अगर (ptrace_access_vm(child, (u64)addrOthers, &पंचांगp,
					माप(पंचांगp),
					FOLL_FORCE | FOLL_WRITE) == माप(पंचांगp))
			अवरोध;
		ret = -EIO;
		अवरोध;
	पूर्ण

	/* ग_लिखो the word at location addr in the USER area */
	हाल PTRACE_POKEUSR: अणु
		अचिन्हित दीर्घ index;

		ret = -EIO;
		/* convert to index and check */
		index = (अचिन्हित दीर्घ) addr >> 2;
		अगर ((addr & 3) || (index > PT_FPSCR32))
			अवरोध;

		अगर (index < PT_FPR0) अणु
			ret = ptrace_put_reg(child, index, data);
		पूर्ण अन्यथा अणु
			flush_fp_to_thपढ़ो(child);
			/*
			 * the user space code considers the भग्नing poपूर्णांक
			 * to be an array of अचिन्हित पूर्णांक (32 bits) - the
			 * index passed in is based on this assumption.
			 */
			((अचिन्हित पूर्णांक *)child->thपढ़ो.fp_state.fpr)
				[FPRINDEX(index)] = data;
			ret = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * Write 4 bytes पूर्णांकo the other process' pt_regs area
	 *  data is the 4 bytes that the user wants written
	 *  addr is the offset पूर्णांकo the other process' pt_regs काष्ठाure
	 *	that is to be written पूर्णांकo
	 * (this is run in a 32-bit process looking at a 64-bit process)
	 */
	हाल PPC_PTRACE_POKEUSR_3264: अणु
		u32 index;
		u32 numReg;

		ret = -EIO;
		/* Determine which रेजिस्टर the user wants */
		index = (u64)addr >> 2;
		numReg = index / 2;

		/*
		 * Validate the input - check to see अगर address is on the
		 * wrong boundary or beyond the end of the user area
		 */
		अगर ((addr & 3) || (numReg > PT_FPSCR))
			अवरोध;
		अगर (numReg < PT_FPR0) अणु
			अचिन्हित दीर्घ freg;
			ret = ptrace_get_reg(child, numReg, &freg);
			अगर (ret)
				अवरोध;
			अगर (index % 2)
				freg = (freg & ~0xfffffffful) | (data & 0xfffffffful);
			अन्यथा
				freg = (freg & 0xfffffffful) | (data << 32);
			ret = ptrace_put_reg(child, numReg, freg);
		पूर्ण अन्यथा अणु
			u64 *पंचांगp;
			flush_fp_to_thपढ़ो(child);
			/* get 64 bit FPR ... */
			पंचांगp = &child->thपढ़ो.fp_state.fpr[numReg - PT_FPR0][0];
			/* ... ग_लिखो the 32 bit part we want */
			((u32 *)पंचांगp)[index % 2] = data;
			ret = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल PTRACE_GET_DEBUGREG: अणु
#अगर_अघोषित CONFIG_PPC_ADV_DEBUG_REGS
		अचिन्हित दीर्घ dabr_fake;
#पूर्ण_अगर
		ret = -EINVAL;
		/* We only support one DABR and no IABRS at the moment */
		अगर (addr > 0)
			अवरोध;
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
		ret = put_user(child->thपढ़ो.debug.dac1, (u32 __user *)data);
#अन्यथा
		dabr_fake = (
			(child->thपढ़ो.hw_brk[0].address & (~HW_BRK_TYPE_DABR)) |
			(child->thपढ़ो.hw_brk[0].type & HW_BRK_TYPE_DABR));
		ret = put_user(dabr_fake, (u32 __user *)data);
#पूर्ण_अगर
		अवरोध;
	पूर्ण

	हाल PTRACE_GETREGS:	/* Get all pt_regs from the child. */
		वापस copy_regset_to_user(
			child, task_user_regset_view(current), 0,
			0, PT_REGS_COUNT * माप(compat_दीर्घ_t),
			compat_ptr(data));

	हाल PTRACE_SETREGS:	/* Set all gp regs in the child. */
		वापस copy_regset_from_user(
			child, task_user_regset_view(current), 0,
			0, PT_REGS_COUNT * माप(compat_दीर्घ_t),
			compat_ptr(data));

	हाल PTRACE_GETFPREGS:
	हाल PTRACE_SETFPREGS:
	हाल PTRACE_GETVRREGS:
	हाल PTRACE_SETVRREGS:
	हाल PTRACE_GETVSRREGS:
	हाल PTRACE_SETVSRREGS:
	हाल PTRACE_GETREGS64:
	हाल PTRACE_SETREGS64:
	हाल PTRACE_KILL:
	हाल PTRACE_SINGLESTEP:
	हाल PTRACE_DETACH:
	हाल PTRACE_SET_DEBUGREG:
	हाल PTRACE_SYSCALL:
	हाल PTRACE_CONT:
	हाल PPC_PTRACE_GETHWDBGINFO:
	हाल PPC_PTRACE_SETHWDEBUG:
	हाल PPC_PTRACE_DELHWDEBUG:
		ret = arch_ptrace(child, request, addr, data);
		अवरोध;

	शेष:
		ret = compat_ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

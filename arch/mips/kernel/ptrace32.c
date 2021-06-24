<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1992 Ross Biro
 * Copyright (C) Linus Torvalds
 * Copyright (C) 1994, 95, 96, 97, 98, 2000 Ralf Baechle
 * Copyright (C) 1996 David S. Miller
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999 MIPS Technologies, Inc.
 * Copyright (C) 2000 Ulf Carlsson
 *
 * At this समय Linux/MIPS64 only supports syscall tracing, even क्रम 32-bit
 * binaries.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/smp.h>
#समावेश <linux/security.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/syscall.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/bootinfo.h>

/*
 * Tracing a 32-bit process with a 64-bit strace and vice versa will not
 * work.  I करोn't know how to fix this.
 */
दीर्घ compat_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			compat_uदीर्घ_t caddr, compat_uदीर्घ_t cdata)
अणु
	पूर्णांक addr = caddr;
	पूर्णांक data = cdata;
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
	हाल PTRACE_PEEKTEXT_3264:
	हाल PTRACE_PEEKDATA_3264: अणु
		u32 पंचांगp;
		पूर्णांक copied;
		u32 __user * addrOthers;

		ret = -EIO;

		/* Get the addr in the other process that we want to पढ़ो */
		अगर (get_user(addrOthers, (u32 __user * __user *) (अचिन्हित दीर्घ) addr) != 0)
			अवरोध;

		copied = ptrace_access_vm(child, (u64)addrOthers, &पंचांगp,
				माप(पंचांगp), FOLL_FORCE);
		अगर (copied != माप(पंचांगp))
			अवरोध;
		ret = put_user(पंचांगp, (u32 __user *) (अचिन्हित दीर्घ) data);
		अवरोध;
	पूर्ण

	/* Read the word at location addr in the USER area. */
	हाल PTRACE_PEEKUSR: अणु
		काष्ठा pt_regs *regs;
		अचिन्हित पूर्णांक पंचांगp;

		regs = task_pt_regs(child);
		ret = 0;  /* Default वापस value. */

		चयन (addr) अणु
		हाल 0 ... 31:
			पंचांगp = regs->regs[addr];
			अवरोध;
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
		हाल FPR_BASE ... FPR_BASE + 31: अणु
			जोड़ fpureg *fregs;

			अगर (!tsk_used_math(child)) अणु
				/* FP not yet used */
				पंचांगp = -1;
				अवरोध;
			पूर्ण
			fregs = get_fpu_regs(child);
			अगर (test_tsk_thपढ़ो_flag(child, TIF_32BIT_FPREGS)) अणु
				/*
				 * The odd रेजिस्टरs are actually the high
				 * order bits of the values stored in the even
				 * रेजिस्टरs.
				 */
				पंचांगp = get_fpr32(&fregs[(addr & ~1) - FPR_BASE],
						addr & 1);
				अवरोध;
			पूर्ण
			पंचांगp = get_fpr64(&fregs[addr - FPR_BASE], 0);
			अवरोध;
		पूर्ण
		हाल FPC_CSR:
			पंचांगp = child->thपढ़ो.fpu.fcr31;
			अवरोध;
		हाल FPC_EIR:
			/* implementation / version रेजिस्टर */
			पंचांगp = boot_cpu_data.fpu_id;
			अवरोध;
#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */
		हाल PC:
			पंचांगp = regs->cp0_epc;
			अवरोध;
		हाल CAUSE:
			पंचांगp = regs->cp0_cause;
			अवरोध;
		हाल BADVADDR:
			पंचांगp = regs->cp0_badvaddr;
			अवरोध;
		हाल MMHI:
			पंचांगp = regs->hi;
			अवरोध;
		हाल MMLO:
			पंचांगp = regs->lo;
			अवरोध;
		हाल DSP_BASE ... DSP_BASE + 5: अणु
			dspreg_t *dregs;

			अगर (!cpu_has_dsp) अणु
				पंचांगp = 0;
				ret = -EIO;
				जाओ out;
			पूर्ण
			dregs = __get_dsp_regs(child);
			पंचांगp = dregs[addr - DSP_BASE];
			अवरोध;
		पूर्ण
		हाल DSP_CONTROL:
			अगर (!cpu_has_dsp) अणु
				पंचांगp = 0;
				ret = -EIO;
				जाओ out;
			पूर्ण
			पंचांगp = child->thपढ़ो.dsp.dspcontrol;
			अवरोध;
		शेष:
			पंचांगp = 0;
			ret = -EIO;
			जाओ out;
		पूर्ण
		ret = put_user(पंचांगp, (अचिन्हित __user *) (अचिन्हित दीर्घ) data);
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
	हाल PTRACE_POKETEXT_3264:
	हाल PTRACE_POKEDATA_3264: अणु
		u32 __user * addrOthers;

		/* Get the addr in the other process that we want to ग_लिखो पूर्णांकo */
		ret = -EIO;
		अगर (get_user(addrOthers, (u32 __user * __user *) (अचिन्हित दीर्घ) addr) != 0)
			अवरोध;
		ret = 0;
		अगर (ptrace_access_vm(child, (u64)addrOthers, &data,
					माप(data),
					FOLL_FORCE | FOLL_WRITE) == माप(data))
			अवरोध;
		ret = -EIO;
		अवरोध;
	पूर्ण

	हाल PTRACE_POKEUSR: अणु
		काष्ठा pt_regs *regs;
		ret = 0;
		regs = task_pt_regs(child);

		चयन (addr) अणु
		हाल 0 ... 31:
			regs->regs[addr] = data;
			/* System call number may have been changed */
			अगर (addr == 2)
				mips_syscall_update_nr(child, regs);
			अन्यथा अगर (addr == 4 &&
				 mips_syscall_is_indirect(child, regs))
				mips_syscall_update_nr(child, regs);
			अवरोध;
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
		हाल FPR_BASE ... FPR_BASE + 31: अणु
			जोड़ fpureg *fregs = get_fpu_regs(child);

			अगर (!tsk_used_math(child)) अणु
				/* FP not yet used  */
				स_रखो(&child->thपढ़ो.fpu, ~0,
				       माप(child->thपढ़ो.fpu));
				child->thपढ़ो.fpu.fcr31 = 0;
			पूर्ण
			अगर (test_tsk_thपढ़ो_flag(child, TIF_32BIT_FPREGS)) अणु
				/*
				 * The odd रेजिस्टरs are actually the high
				 * order bits of the values stored in the even
				 * रेजिस्टरs.
				 */
				set_fpr32(&fregs[(addr & ~1) - FPR_BASE],
					  addr & 1, data);
				अवरोध;
			पूर्ण
			set_fpr64(&fregs[addr - FPR_BASE], 0, data);
			अवरोध;
		पूर्ण
		हाल FPC_CSR:
			child->thपढ़ो.fpu.fcr31 = data;
			अवरोध;
#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */
		हाल PC:
			regs->cp0_epc = data;
			अवरोध;
		हाल MMHI:
			regs->hi = data;
			अवरोध;
		हाल MMLO:
			regs->lo = data;
			अवरोध;
		हाल DSP_BASE ... DSP_BASE + 5: अणु
			dspreg_t *dregs;

			अगर (!cpu_has_dsp) अणु
				ret = -EIO;
				अवरोध;
			पूर्ण

			dregs = __get_dsp_regs(child);
			dregs[addr - DSP_BASE] = data;
			अवरोध;
		पूर्ण
		हाल DSP_CONTROL:
			अगर (!cpu_has_dsp) अणु
				ret = -EIO;
				अवरोध;
			पूर्ण
			child->thपढ़ो.dsp.dspcontrol = data;
			अवरोध;
		शेष:
			/* The rest are not allowed. */
			ret = -EIO;
			अवरोध;
		पूर्ण
		अवरोध;
		पूर्ण

	हाल PTRACE_GETREGS:
		ret = ptrace_getregs(child,
				(काष्ठा user_pt_regs __user *) (__u64) data);
		अवरोध;

	हाल PTRACE_SETREGS:
		ret = ptrace_setregs(child,
				(काष्ठा user_pt_regs __user *) (__u64) data);
		अवरोध;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	हाल PTRACE_GETFPREGS:
		ret = ptrace_getfpregs(child, (__u32 __user *) (__u64) data);
		अवरोध;

	हाल PTRACE_SETFPREGS:
		ret = ptrace_setfpregs(child, (__u32 __user *) (__u64) data);
		अवरोध;
#पूर्ण_अगर
	हाल PTRACE_GET_THREAD_AREA:
		ret = put_user(task_thपढ़ो_info(child)->tp_value,
				(अचिन्हित पूर्णांक __user *) (अचिन्हित दीर्घ) data);
		अवरोध;

	हाल PTRACE_GET_THREAD_AREA_3264:
		ret = put_user(task_thपढ़ो_info(child)->tp_value,
				(अचिन्हित दीर्घ __user *) (अचिन्हित दीर्घ) data);
		अवरोध;

	हाल PTRACE_GET_WATCH_REGS:
		ret = ptrace_get_watch_regs(child,
			(काष्ठा pt_watch_regs __user *) (अचिन्हित दीर्घ) addr);
		अवरोध;

	हाल PTRACE_SET_WATCH_REGS:
		ret = ptrace_set_watch_regs(child,
			(काष्ठा pt_watch_regs __user *) (अचिन्हित दीर्घ) addr);
		अवरोध;

	शेष:
		ret = compat_ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

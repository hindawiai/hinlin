<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2014 Lemote Corporation.
 *   written by Huacai Chen <chenhc@lemote.com>
 *
 * based on arch/mips/cavium-octeon/cpu.c
 * Copyright (C) 2009 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/cop2.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/unaligned-emul.h>

अटल पूर्णांक loongson_cu2_call(काष्ठा notअगरier_block *nfb, अचिन्हित दीर्घ action,
	व्योम *data)
अणु
	अचिन्हित पूर्णांक res, fpu_owned;
	अचिन्हित दीर्घ ra, value, value_next;
	जोड़ mips_inकाष्ठाion insn;
	पूर्णांक fr = !test_thपढ़ो_flag(TIF_32BIT_FPREGS);
	काष्ठा pt_regs *regs = (काष्ठा pt_regs *)data;
	व्योम __user *addr = (व्योम __user *)regs->cp0_badvaddr;
	अचिन्हित पूर्णांक __user *pc = (अचिन्हित पूर्णांक __user *)exception_epc(regs);

	ra = regs->regs[31];
	__get_user(insn.word, pc);

	चयन (action) अणु
	हाल CU2_EXCEPTION:
		preempt_disable();
		fpu_owned = __is_fpu_owner();
		अगर (!fr)
			set_c0_status(ST0_CU1 | ST0_CU2);
		अन्यथा
			set_c0_status(ST0_CU1 | ST0_CU2 | ST0_FR);
		enable_fpu_hazard();
		KSTK_STATUS(current) |= (ST0_CU1 | ST0_CU2);
		अगर (fr)
			KSTK_STATUS(current) |= ST0_FR;
		अन्यथा
			KSTK_STATUS(current) &= ~ST0_FR;
		/* If FPU is owned, we needn't init or restore fp */
		अगर (!fpu_owned) अणु
			set_thपढ़ो_flag(TIF_USEDFPU);
			init_fp_ctx(current);
			_restore_fp(current);
		पूर्ण
		preempt_enable();

		वापस NOTIFY_STOP;	/* Don't call शेष notअगरier */

	हाल CU2_LWC2_OP:
		अगर (insn.loongson3_lswc2_क्रमmat.ls == 0)
			जाओ sigbus;

		अगर (insn.loongson3_lswc2_क्रमmat.fr == 0) अणु	/* gslq */
			अगर (!access_ok(addr, 16))
				जाओ sigbus;

			LoadDW(addr, value, res);
			अगर (res)
				जाओ fault;

			LoadDW(addr + 8, value_next, res);
			अगर (res)
				जाओ fault;

			regs->regs[insn.loongson3_lswc2_क्रमmat.rt] = value;
			regs->regs[insn.loongson3_lswc2_क्रमmat.rq] = value_next;
			compute_वापस_epc(regs);
		पूर्ण अन्यथा अणु					/* gslqc1 */
			अगर (!access_ok(addr, 16))
				जाओ sigbus;

			lose_fpu(1);
			LoadDW(addr, value, res);
			अगर (res)
				जाओ fault;

			LoadDW(addr + 8, value_next, res);
			अगर (res)
				जाओ fault;

			set_fpr64(&current->thपढ़ो.fpu.fpr[insn.loongson3_lswc2_क्रमmat.rt], 0, value);
			set_fpr64(&current->thपढ़ो.fpu.fpr[insn.loongson3_lswc2_क्रमmat.rq], 0, value_next);
			compute_वापस_epc(regs);
			own_fpu(1);
		पूर्ण
		वापस NOTIFY_STOP;	/* Don't call शेष notअगरier */

	हाल CU2_SWC2_OP:
		अगर (insn.loongson3_lswc2_क्रमmat.ls == 0)
			जाओ sigbus;

		अगर (insn.loongson3_lswc2_क्रमmat.fr == 0) अणु	/* gssq */
			अगर (!access_ok(addr, 16))
				जाओ sigbus;

			/* ग_लिखो upper 8 bytes first */
			value_next = regs->regs[insn.loongson3_lswc2_क्रमmat.rq];

			StoreDW(addr + 8, value_next, res);
			अगर (res)
				जाओ fault;
			value = regs->regs[insn.loongson3_lswc2_क्रमmat.rt];

			StoreDW(addr, value, res);
			अगर (res)
				जाओ fault;

			compute_वापस_epc(regs);
		पूर्ण अन्यथा अणु					/* gssqc1 */
			अगर (!access_ok(addr, 16))
				जाओ sigbus;

			lose_fpu(1);
			value_next = get_fpr64(&current->thपढ़ो.fpu.fpr[insn.loongson3_lswc2_क्रमmat.rq], 0);

			StoreDW(addr + 8, value_next, res);
			अगर (res)
				जाओ fault;

			value = get_fpr64(&current->thपढ़ो.fpu.fpr[insn.loongson3_lswc2_क्रमmat.rt], 0);

			StoreDW(addr, value, res);
			अगर (res)
				जाओ fault;

			compute_वापस_epc(regs);
			own_fpu(1);
		पूर्ण
		वापस NOTIFY_STOP;	/* Don't call शेष notअगरier */

	हाल CU2_LDC2_OP:
		चयन (insn.loongson3_lsdc2_क्रमmat.opcode1) अणु
		/*
		 * Loongson-3 overridden ldc2 inकाष्ठाions.
		 * opcode1              inकाष्ठाion
		 *   0x1          gslhx: load 2 bytes to GPR
		 *   0x2          gslwx: load 4 bytes to GPR
		 *   0x3          gsldx: load 8 bytes to GPR
		 *   0x6	  gslwxc1: load 4 bytes to FPR
		 *   0x7	  gsldxc1: load 8 bytes to FPR
		 */
		हाल 0x1:
			अगर (!access_ok(addr, 2))
				जाओ sigbus;

			LoadHW(addr, value, res);
			अगर (res)
				जाओ fault;

			compute_वापस_epc(regs);
			regs->regs[insn.loongson3_lsdc2_क्रमmat.rt] = value;
			अवरोध;
		हाल 0x2:
			अगर (!access_ok(addr, 4))
				जाओ sigbus;

			LoadW(addr, value, res);
			अगर (res)
				जाओ fault;

			compute_वापस_epc(regs);
			regs->regs[insn.loongson3_lsdc2_क्रमmat.rt] = value;
			अवरोध;
		हाल 0x3:
			अगर (!access_ok(addr, 8))
				जाओ sigbus;

			LoadDW(addr, value, res);
			अगर (res)
				जाओ fault;

			compute_वापस_epc(regs);
			regs->regs[insn.loongson3_lsdc2_क्रमmat.rt] = value;
			अवरोध;
		हाल 0x6:
			die_अगर_kernel("Unaligned FP access in kernel code", regs);
			BUG_ON(!used_math());
			अगर (!access_ok(addr, 4))
				जाओ sigbus;

			lose_fpu(1);
			LoadW(addr, value, res);
			अगर (res)
				जाओ fault;

			set_fpr64(&current->thपढ़ो.fpu.fpr[insn.loongson3_lsdc2_क्रमmat.rt], 0, value);
			compute_वापस_epc(regs);
			own_fpu(1);

			अवरोध;
		हाल 0x7:
			die_अगर_kernel("Unaligned FP access in kernel code", regs);
			BUG_ON(!used_math());
			अगर (!access_ok(addr, 8))
				जाओ sigbus;

			lose_fpu(1);
			LoadDW(addr, value, res);
			अगर (res)
				जाओ fault;

			set_fpr64(&current->thपढ़ो.fpu.fpr[insn.loongson3_lsdc2_क्रमmat.rt], 0, value);
			compute_वापस_epc(regs);
			own_fpu(1);
			अवरोध;

		पूर्ण
		वापस NOTIFY_STOP;	/* Don't call शेष notअगरier */

	हाल CU2_SDC2_OP:
		चयन (insn.loongson3_lsdc2_क्रमmat.opcode1) अणु
		/*
		 * Loongson-3 overridden sdc2 inकाष्ठाions.
		 * opcode1              inकाष्ठाion
		 *   0x1          gsshx: store 2 bytes from GPR
		 *   0x2          gsswx: store 4 bytes from GPR
		 *   0x3          gssdx: store 8 bytes from GPR
		 *   0x6          gsswxc1: store 4 bytes from FPR
		 *   0x7          gssdxc1: store 8 bytes from FPR
		 */
		हाल 0x1:
			अगर (!access_ok(addr, 2))
				जाओ sigbus;

			compute_वापस_epc(regs);
			value = regs->regs[insn.loongson3_lsdc2_क्रमmat.rt];

			StoreHW(addr, value, res);
			अगर (res)
				जाओ fault;

			अवरोध;
		हाल 0x2:
			अगर (!access_ok(addr, 4))
				जाओ sigbus;

			compute_वापस_epc(regs);
			value = regs->regs[insn.loongson3_lsdc2_क्रमmat.rt];

			StoreW(addr, value, res);
			अगर (res)
				जाओ fault;

			अवरोध;
		हाल 0x3:
			अगर (!access_ok(addr, 8))
				जाओ sigbus;

			compute_वापस_epc(regs);
			value = regs->regs[insn.loongson3_lsdc2_क्रमmat.rt];

			StoreDW(addr, value, res);
			अगर (res)
				जाओ fault;

			अवरोध;

		हाल 0x6:
			die_अगर_kernel("Unaligned FP access in kernel code", regs);
			BUG_ON(!used_math());

			अगर (!access_ok(addr, 4))
				जाओ sigbus;

			lose_fpu(1);
			value = get_fpr64(&current->thपढ़ो.fpu.fpr[insn.loongson3_lsdc2_क्रमmat.rt], 0);

			StoreW(addr, value, res);
			अगर (res)
				जाओ fault;

			compute_वापस_epc(regs);
			own_fpu(1);

			अवरोध;
		हाल 0x7:
			die_अगर_kernel("Unaligned FP access in kernel code", regs);
			BUG_ON(!used_math());

			अगर (!access_ok(addr, 8))
				जाओ sigbus;

			lose_fpu(1);
			value = get_fpr64(&current->thपढ़ो.fpu.fpr[insn.loongson3_lsdc2_क्रमmat.rt], 0);

			StoreDW(addr, value, res);
			अगर (res)
				जाओ fault;

			compute_वापस_epc(regs);
			own_fpu(1);

			अवरोध;
		पूर्ण
		वापस NOTIFY_STOP;	/* Don't call शेष notअगरier */
	पूर्ण

	वापस NOTIFY_OK;		/* Let शेष notअगरier send संकेतs */

fault:
	/* roll back jump/branch */
	regs->regs[31] = ra;
	regs->cp0_epc = (अचिन्हित दीर्घ)pc;
	/* Did we have an exception handler installed? */
	अगर (fixup_exception(regs))
		वापस NOTIFY_STOP;	/* Don't call शेष notअगरier */

	die_अगर_kernel("Unhandled kernel unaligned access", regs);
	क्रमce_sig(संक_अंश);

	वापस NOTIFY_STOP;	/* Don't call शेष notअगरier */

sigbus:
	die_अगर_kernel("Unhandled kernel unaligned access", regs);
	क्रमce_sig(SIGBUS);

	वापस NOTIFY_STOP;	/* Don't call शेष notअगरier */
पूर्ण

अटल पूर्णांक __init loongson_cu2_setup(व्योम)
अणु
	वापस cu2_notअगरier(loongson_cu2_call, 0);
पूर्ण
early_initcall(loongson_cu2_setup);

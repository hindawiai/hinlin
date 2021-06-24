<शैली गुरु>
/*
 * Handle unaligned accesses by emulation.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1998, 1999, 2002 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) 2014 Imagination Technologies Ltd.
 *
 * This file contains exception handler क्रम address error exception with the
 * special capability to execute faulting inकाष्ठाions in software.  The
 * handler करोes not try to handle the हाल when the program counter poपूर्णांकs
 * to an address not aligned to a word boundary.
 *
 * Putting data to unaligned addresses is a bad practice even on Intel where
 * only the perक्रमmance is affected.  Much worse is that such code is non-
 * portable.  Due to several programs that die on MIPS due to alignment
 * problems I decided to implement this handler anyway though I originally
 * didn't पूर्णांकend to करो this at all क्रम user code.
 *
 * For now I enable fixing of address errors by शेष to make lअगरe easier.
 * I however पूर्णांकend to disable this somewhen in the future when the alignment
 * problems with user programs have been fixed.	 For programmers this is the
 * right way to go.
 *
 * Fixing address errors is a per process option.  The option is inherited
 * across विभाजन(2) and execve(2) calls.	If you really want to use the
 * option in your user programs - I discourage the use of the software
 * emulation strongly - use the following code in your userland stuff:
 *
 * #समावेश <sys/sysmips.h>
 *
 * ...
 * sysmips(MIPS_FIXADE, x);
 * ...
 *
 * The argument x is 0 क्रम disabling software emulation, enabled otherwise.
 *
 * Below a little program to play around with this feature.
 *
 * #समावेश <मानकपन.स>
 * #समावेश <sys/sysmips.h>
 *
 * काष्ठा foo अणु
 *	   अचिन्हित अक्षर bar[8];
 * पूर्ण;
 *
 * मुख्य(पूर्णांक argc, अक्षर *argv[])
 * अणु
 *	   काष्ठा foo x = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण;
 *	   अचिन्हित पूर्णांक *p = (अचिन्हित पूर्णांक *) (x.bar + 3);
 *	   पूर्णांक i;
 *
 *	   अगर (argc > 1)
 *		   sysmips(MIPS_FIXADE, म_से_प(argv[1]));
 *
 *	   म_लिखो("*p = %08lx\n", *p);
 *
 *	   *p = 0xdeadface;
 *
 *	   क्रम(i = 0; i <= 7; i++)
 *	   म_लिखो("%02x ", x.bar[i]);
 *	   म_लिखो("\n");
 * पूर्ण
 *
 * Coprocessor loads are not supported; I think this हाल is unimportant
 * in the practice.
 *
 * TODO: Handle ndc (attempted store to द्विगुनword in uncached memory)
 *	 exception क्रम the R6000.
 *	 A store crossing a page boundary might be executed only partially.
 *	 Unकरो the partial store in this हाल.
 */
#समावेश <linux/context_tracking.h>
#समावेश <linux/mm.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/cop2.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/fpu_emulator.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/unaligned-emul.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <linux/uaccess.h>

#समावेश "access-helper.h"

क्रमागत अणु
	UNALIGNED_ACTION_QUIET,
	UNALIGNED_ACTION_SIGNAL,
	UNALIGNED_ACTION_SHOW,
पूर्ण;
#अगर_घोषित CONFIG_DEBUG_FS
अटल u32 unaligned_inकाष्ठाions;
अटल u32 unaligned_action;
#अन्यथा
#घोषणा unaligned_action UNALIGNED_ACTION_QUIET
#पूर्ण_अगर
बाह्य व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs);

अटल व्योम emulate_load_store_insn(काष्ठा pt_regs *regs,
	व्योम __user *addr, अचिन्हित पूर्णांक *pc)
अणु
	अचिन्हित दीर्घ origpc, orig31, value;
	जोड़ mips_inकाष्ठाion insn;
	अचिन्हित पूर्णांक res;
	bool user = user_mode(regs);

	origpc = (अचिन्हित दीर्घ)pc;
	orig31 = regs->regs[31];

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);

	/*
	 * This load never faults.
	 */
	__get_inst32(&insn.word, pc, user);

	चयन (insn.i_क्रमmat.opcode) अणु
		/*
		 * These are inकाष्ठाions that a compiler करोesn't generate.  We
		 * can assume thereक्रमe that the code is MIPS-aware and
		 * really buggy.  Emulating these inकाष्ठाions would अवरोध the
		 * semantics anyway.
		 */
	हाल ll_op:
	हाल lld_op:
	हाल sc_op:
	हाल scd_op:

		/*
		 * For these inकाष्ठाions the only way to create an address
		 * error is an attempted access to kernel/supervisor address
		 * space.
		 */
	हाल ldl_op:
	हाल ldr_op:
	हाल lwl_op:
	हाल lwr_op:
	हाल sdl_op:
	हाल sdr_op:
	हाल swl_op:
	हाल swr_op:
	हाल lb_op:
	हाल lbu_op:
	हाल sb_op:
		जाओ sigbus;

		/*
		 * The reमुख्यing opcodes are the ones that are really of
		 * पूर्णांकerest.
		 */
	हाल spec3_op:
		अगर (insn.dsp_क्रमmat.func == lx_op) अणु
			चयन (insn.dsp_क्रमmat.op) अणु
			हाल lwx_op:
				अगर (user && !access_ok(addr, 4))
					जाओ sigbus;
				LoadW(addr, value, res);
				अगर (res)
					जाओ fault;
				compute_वापस_epc(regs);
				regs->regs[insn.dsp_क्रमmat.rd] = value;
				अवरोध;
			हाल lhx_op:
				अगर (user && !access_ok(addr, 2))
					जाओ sigbus;
				LoadHW(addr, value, res);
				अगर (res)
					जाओ fault;
				compute_वापस_epc(regs);
				regs->regs[insn.dsp_क्रमmat.rd] = value;
				अवरोध;
			शेष:
				जाओ sigill;
			पूर्ण
		पूर्ण
#अगर_घोषित CONFIG_EVA
		अन्यथा अणु
			/*
			 * we can land here only from kernel accessing user
			 * memory, so we need to "switch" the address limit to
			 * user space, so that address check can work properly.
			 */
			चयन (insn.spec3_क्रमmat.func) अणु
			हाल lhe_op:
				अगर (!access_ok(addr, 2))
					जाओ sigbus;
				LoadHWE(addr, value, res);
				अगर (res)
					जाओ fault;
				compute_वापस_epc(regs);
				regs->regs[insn.spec3_क्रमmat.rt] = value;
				अवरोध;
			हाल lwe_op:
				अगर (!access_ok(addr, 4))
					जाओ sigbus;
				LoadWE(addr, value, res);
				अगर (res)
					जाओ fault;
				compute_वापस_epc(regs);
				regs->regs[insn.spec3_क्रमmat.rt] = value;
				अवरोध;
			हाल lhue_op:
				अगर (!access_ok(addr, 2))
					जाओ sigbus;
				LoadHWUE(addr, value, res);
				अगर (res)
					जाओ fault;
				compute_वापस_epc(regs);
				regs->regs[insn.spec3_क्रमmat.rt] = value;
				अवरोध;
			हाल she_op:
				अगर (!access_ok(addr, 2))
					जाओ sigbus;
				compute_वापस_epc(regs);
				value = regs->regs[insn.spec3_क्रमmat.rt];
				StoreHWE(addr, value, res);
				अगर (res)
					जाओ fault;
				अवरोध;
			हाल swe_op:
				अगर (!access_ok(addr, 4))
					जाओ sigbus;
				compute_वापस_epc(regs);
				value = regs->regs[insn.spec3_क्रमmat.rt];
				StoreWE(addr, value, res);
				अगर (res)
					जाओ fault;
				अवरोध;
			शेष:
				जाओ sigill;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	हाल lh_op:
		अगर (user && !access_ok(addr, 2))
			जाओ sigbus;

		अगर (IS_ENABLED(CONFIG_EVA) && user)
			LoadHWE(addr, value, res);
		अन्यथा
			LoadHW(addr, value, res);

		अगर (res)
			जाओ fault;
		compute_वापस_epc(regs);
		regs->regs[insn.i_क्रमmat.rt] = value;
		अवरोध;

	हाल lw_op:
		अगर (user && !access_ok(addr, 4))
			जाओ sigbus;

		अगर (IS_ENABLED(CONFIG_EVA) && user)
			LoadWE(addr, value, res);
		अन्यथा
			LoadW(addr, value, res);

		अगर (res)
			जाओ fault;
		compute_वापस_epc(regs);
		regs->regs[insn.i_क्रमmat.rt] = value;
		अवरोध;

	हाल lhu_op:
		अगर (user && !access_ok(addr, 2))
			जाओ sigbus;

		अगर (IS_ENABLED(CONFIG_EVA) && user)
			LoadHWUE(addr, value, res);
		अन्यथा
			LoadHWU(addr, value, res);

		अगर (res)
			जाओ fault;
		compute_वापस_epc(regs);
		regs->regs[insn.i_क्रमmat.rt] = value;
		अवरोध;

	हाल lwu_op:
#अगर_घोषित CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * अगर we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
		 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
		 * inकाष्ठाions on 32-bit kernels.
		 */
		अगर (user && !access_ok(addr, 4))
			जाओ sigbus;

		LoadWU(addr, value, res);
		अगर (res)
			जाओ fault;
		compute_वापस_epc(regs);
		regs->regs[insn.i_क्रमmat.rt] = value;
		अवरोध;
#पूर्ण_अगर /* CONFIG_64BIT */

		/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
		जाओ sigill;

	हाल ld_op:
#अगर_घोषित CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * अगर we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
		 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
		 * inकाष्ठाions on 32-bit kernels.
		 */
		अगर (user && !access_ok(addr, 8))
			जाओ sigbus;

		LoadDW(addr, value, res);
		अगर (res)
			जाओ fault;
		compute_वापस_epc(regs);
		regs->regs[insn.i_क्रमmat.rt] = value;
		अवरोध;
#पूर्ण_अगर /* CONFIG_64BIT */

		/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
		जाओ sigill;

	हाल sh_op:
		अगर (user && !access_ok(addr, 2))
			जाओ sigbus;

		compute_वापस_epc(regs);
		value = regs->regs[insn.i_क्रमmat.rt];

		अगर (IS_ENABLED(CONFIG_EVA) && user)
			StoreHWE(addr, value, res);
		अन्यथा
			StoreHW(addr, value, res);

		अगर (res)
			जाओ fault;
		अवरोध;

	हाल sw_op:
		अगर (user && !access_ok(addr, 4))
			जाओ sigbus;

		compute_वापस_epc(regs);
		value = regs->regs[insn.i_क्रमmat.rt];

		अगर (IS_ENABLED(CONFIG_EVA) && user)
			StoreWE(addr, value, res);
		अन्यथा
			StoreW(addr, value, res);

		अगर (res)
			जाओ fault;
		अवरोध;

	हाल sd_op:
#अगर_घोषित CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * अगर we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
		 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
		 * inकाष्ठाions on 32-bit kernels.
		 */
		अगर (user && !access_ok(addr, 8))
			जाओ sigbus;

		compute_वापस_epc(regs);
		value = regs->regs[insn.i_क्रमmat.rt];
		StoreDW(addr, value, res);
		अगर (res)
			जाओ fault;
		अवरोध;
#पूर्ण_अगर /* CONFIG_64BIT */

		/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
		जाओ sigill;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

	हाल lwc1_op:
	हाल ldc1_op:
	हाल swc1_op:
	हाल sdc1_op:
	हाल cop1x_op: अणु
		व्योम __user *fault_addr = शून्य;

		die_अगर_kernel("Unaligned FP access in kernel code", regs);
		BUG_ON(!used_math());

		res = fpu_emulator_cop1Handler(regs, &current->thपढ़ो.fpu, 1,
					       &fault_addr);
		own_fpu(1);	/* Restore FPU state. */

		/* Signal अगर something went wrong. */
		process_fpemu_वापस(res, fault_addr, 0);

		अगर (res == 0)
			अवरोध;
		वापस;
	पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */

#अगर_घोषित CONFIG_CPU_HAS_MSA

	हाल msa_op: अणु
		अचिन्हित पूर्णांक wd, preempted;
		क्रमागत msa_2b_fmt df;
		जोड़ fpureg *fpr;

		अगर (!cpu_has_msa)
			जाओ sigill;

		/*
		 * If we've reached this poपूर्णांक then userland should have taken
		 * the MSA disabled exception & initialised vector context at
		 * some poपूर्णांक in the past.
		 */
		BUG_ON(!thपढ़ो_msa_context_live());

		df = insn.msa_mi10_क्रमmat.df;
		wd = insn.msa_mi10_क्रमmat.wd;
		fpr = &current->thपढ़ो.fpu.fpr[wd];

		चयन (insn.msa_mi10_क्रमmat.func) अणु
		हाल msa_ld_op:
			अगर (!access_ok(addr, माप(*fpr)))
				जाओ sigbus;

			करो अणु
				/*
				 * If we have live MSA context keep track of
				 * whether we get preempted in order to aव्योम
				 * the रेजिस्टर context we load being clobbered
				 * by the live context as it's saved during
				 * preemption. If we करोn't have live context
				 * then it can't be saved to clobber the value
				 * we load.
				 */
				preempted = test_thपढ़ो_flag(TIF_USEDMSA);

				res = __copy_from_user_inatomic(fpr, addr,
								माप(*fpr));
				अगर (res)
					जाओ fault;

				/*
				 * Update the hardware रेजिस्टर अगर it is in use
				 * by the task in this quantum, in order to
				 * aव्योम having to save & restore the whole
				 * vector context.
				 */
				preempt_disable();
				अगर (test_thपढ़ो_flag(TIF_USEDMSA)) अणु
					ग_लिखो_msa_wr(wd, fpr, df);
					preempted = 0;
				पूर्ण
				preempt_enable();
			पूर्ण जबतक (preempted);
			अवरोध;

		हाल msa_st_op:
			अगर (!access_ok(addr, माप(*fpr)))
				जाओ sigbus;

			/*
			 * Update from the hardware रेजिस्टर अगर it is in use by
			 * the task in this quantum, in order to aव्योम having to
			 * save & restore the whole vector context.
			 */
			preempt_disable();
			अगर (test_thपढ़ो_flag(TIF_USEDMSA))
				पढ़ो_msa_wr(wd, fpr, df);
			preempt_enable();

			res = __copy_to_user_inatomic(addr, fpr, माप(*fpr));
			अगर (res)
				जाओ fault;
			अवरोध;

		शेष:
			जाओ sigbus;
		पूर्ण

		compute_वापस_epc(regs);
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_HAS_MSA */

#अगर_अघोषित CONFIG_CPU_MIPSR6
	/*
	 * COP2 is available to implementor क्रम application specअगरic use.
	 * It's up to applications to रेजिस्टर a notअगरier chain and करो
	 * whatever they have to करो, including possible sending of संकेतs.
	 *
	 * This inकाष्ठाion has been पुनः_स्मृतिated in Release 6
	 */
	हाल lwc2_op:
		cu2_notअगरier_call_chain(CU2_LWC2_OP, regs);
		अवरोध;

	हाल ldc2_op:
		cu2_notअगरier_call_chain(CU2_LDC2_OP, regs);
		अवरोध;

	हाल swc2_op:
		cu2_notअगरier_call_chain(CU2_SWC2_OP, regs);
		अवरोध;

	हाल sdc2_op:
		cu2_notअगरier_call_chain(CU2_SDC2_OP, regs);
		अवरोध;
#पूर्ण_अगर
	शेष:
		/*
		 * Pheeee...  We encountered an yet unknown inकाष्ठाion or
		 * cache coherence problem.  Die sucker, die ...
		 */
		जाओ sigill;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	unaligned_inकाष्ठाions++;
#पूर्ण_अगर

	वापस;

fault:
	/* roll back jump/branch */
	regs->cp0_epc = origpc;
	regs->regs[31] = orig31;
	/* Did we have an exception handler installed? */
	अगर (fixup_exception(regs))
		वापस;

	die_अगर_kernel("Unhandled kernel unaligned access", regs);
	क्रमce_sig(संक_अंश);

	वापस;

sigbus:
	die_अगर_kernel("Unhandled kernel unaligned access", regs);
	क्रमce_sig(SIGBUS);

	वापस;

sigill:
	die_अगर_kernel
	    ("Unhandled kernel unaligned access or invalid instruction", regs);
	क्रमce_sig(संक_अवैध);
पूर्ण

/* Recode table from 16-bit रेजिस्टर notation to 32-bit GPR. */
स्थिर पूर्णांक reg16to32[] = अणु 16, 17, 2, 3, 4, 5, 6, 7 पूर्ण;

/* Recode table from 16-bit STORE रेजिस्टर notation to 32-bit GPR. */
अटल स्थिर पूर्णांक reg16to32st[] = अणु 0, 17, 2, 3, 4, 5, 6, 7 पूर्ण;

अटल व्योम emulate_load_store_microMIPS(काष्ठा pt_regs *regs,
					 व्योम __user *addr)
अणु
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक res;
	पूर्णांक i;
	अचिन्हित पूर्णांक reg = 0, rvar;
	अचिन्हित दीर्घ orig31;
	u16 __user *pc16;
	u16 halfword;
	अचिन्हित पूर्णांक word;
	अचिन्हित दीर्घ origpc, contpc;
	जोड़ mips_inकाष्ठाion insn;
	काष्ठा mm_decoded_insn mminsn;
	bool user = user_mode(regs);

	origpc = regs->cp0_epc;
	orig31 = regs->regs[31];

	mminsn.micro_mips_mode = 1;

	/*
	 * This load never faults.
	 */
	pc16 = (अचिन्हित लघु __user *)msk_isa16_mode(regs->cp0_epc);
	__get_user(halfword, pc16);
	pc16++;
	contpc = regs->cp0_epc + 2;
	word = ((अचिन्हित पूर्णांक)halfword << 16);
	mminsn.pc_inc = 2;

	अगर (!mm_insn_16bit(halfword)) अणु
		__get_user(halfword, pc16);
		pc16++;
		contpc = regs->cp0_epc + 4;
		mminsn.pc_inc = 4;
		word |= halfword;
	पूर्ण
	mminsn.insn = word;

	अगर (get_user(halfword, pc16))
		जाओ fault;
	mminsn.next_pc_inc = 2;
	word = ((अचिन्हित पूर्णांक)halfword << 16);

	अगर (!mm_insn_16bit(halfword)) अणु
		pc16++;
		अगर (get_user(halfword, pc16))
			जाओ fault;
		mminsn.next_pc_inc = 4;
		word |= halfword;
	पूर्ण
	mminsn.next_insn = word;

	insn = (जोड़ mips_inकाष्ठाion)(mminsn.insn);
	अगर (mm_isBranchInstr(regs, mminsn, &contpc))
		insn = (जोड़ mips_inकाष्ठाion)(mminsn.next_insn);

	/*  Parse inकाष्ठाion to find what to करो */

	चयन (insn.mm_i_क्रमmat.opcode) अणु

	हाल mm_pool32a_op:
		चयन (insn.mm_x_क्रमmat.func) अणु
		हाल mm_lwxs_op:
			reg = insn.mm_x_क्रमmat.rd;
			जाओ loadW;
		पूर्ण

		जाओ sigbus;

	हाल mm_pool32b_op:
		चयन (insn.mm_m_क्रमmat.func) अणु
		हाल mm_lwp_func:
			reg = insn.mm_m_क्रमmat.rd;
			अगर (reg == 31)
				जाओ sigbus;

			अगर (user && !access_ok(addr, 8))
				जाओ sigbus;

			LoadW(addr, value, res);
			अगर (res)
				जाओ fault;
			regs->regs[reg] = value;
			addr += 4;
			LoadW(addr, value, res);
			अगर (res)
				जाओ fault;
			regs->regs[reg + 1] = value;
			जाओ success;

		हाल mm_swp_func:
			reg = insn.mm_m_क्रमmat.rd;
			अगर (reg == 31)
				जाओ sigbus;

			अगर (user && !access_ok(addr, 8))
				जाओ sigbus;

			value = regs->regs[reg];
			StoreW(addr, value, res);
			अगर (res)
				जाओ fault;
			addr += 4;
			value = regs->regs[reg + 1];
			StoreW(addr, value, res);
			अगर (res)
				जाओ fault;
			जाओ success;

		हाल mm_ldp_func:
#अगर_घोषित CONFIG_64BIT
			reg = insn.mm_m_क्रमmat.rd;
			अगर (reg == 31)
				जाओ sigbus;

			अगर (user && !access_ok(addr, 16))
				जाओ sigbus;

			LoadDW(addr, value, res);
			अगर (res)
				जाओ fault;
			regs->regs[reg] = value;
			addr += 8;
			LoadDW(addr, value, res);
			अगर (res)
				जाओ fault;
			regs->regs[reg + 1] = value;
			जाओ success;
#पूर्ण_अगर /* CONFIG_64BIT */

			जाओ sigill;

		हाल mm_sdp_func:
#अगर_घोषित CONFIG_64BIT
			reg = insn.mm_m_क्रमmat.rd;
			अगर (reg == 31)
				जाओ sigbus;

			अगर (user && !access_ok(addr, 16))
				जाओ sigbus;

			value = regs->regs[reg];
			StoreDW(addr, value, res);
			अगर (res)
				जाओ fault;
			addr += 8;
			value = regs->regs[reg + 1];
			StoreDW(addr, value, res);
			अगर (res)
				जाओ fault;
			जाओ success;
#पूर्ण_अगर /* CONFIG_64BIT */

			जाओ sigill;

		हाल mm_lwm32_func:
			reg = insn.mm_m_क्रमmat.rd;
			rvar = reg & 0xf;
			अगर ((rvar > 9) || !reg)
				जाओ sigill;
			अगर (reg & 0x10) अणु
				अगर (user && !access_ok(addr, 4 * (rvar + 1)))
					जाओ sigbus;
			पूर्ण अन्यथा अणु
				अगर (user && !access_ok(addr, 4 * rvar))
					जाओ sigbus;
			पूर्ण
			अगर (rvar == 9)
				rvar = 8;
			क्रम (i = 16; rvar; rvar--, i++) अणु
				LoadW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 4;
				regs->regs[i] = value;
			पूर्ण
			अगर ((reg & 0xf) == 9) अणु
				LoadW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 4;
				regs->regs[30] = value;
			पूर्ण
			अगर (reg & 0x10) अणु
				LoadW(addr, value, res);
				अगर (res)
					जाओ fault;
				regs->regs[31] = value;
			पूर्ण
			जाओ success;

		हाल mm_swm32_func:
			reg = insn.mm_m_क्रमmat.rd;
			rvar = reg & 0xf;
			अगर ((rvar > 9) || !reg)
				जाओ sigill;
			अगर (reg & 0x10) अणु
				अगर (user && !access_ok(addr, 4 * (rvar + 1)))
					जाओ sigbus;
			पूर्ण अन्यथा अणु
				अगर (user && !access_ok(addr, 4 * rvar))
					जाओ sigbus;
			पूर्ण
			अगर (rvar == 9)
				rvar = 8;
			क्रम (i = 16; rvar; rvar--, i++) अणु
				value = regs->regs[i];
				StoreW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 4;
			पूर्ण
			अगर ((reg & 0xf) == 9) अणु
				value = regs->regs[30];
				StoreW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 4;
			पूर्ण
			अगर (reg & 0x10) अणु
				value = regs->regs[31];
				StoreW(addr, value, res);
				अगर (res)
					जाओ fault;
			पूर्ण
			जाओ success;

		हाल mm_ldm_func:
#अगर_घोषित CONFIG_64BIT
			reg = insn.mm_m_क्रमmat.rd;
			rvar = reg & 0xf;
			अगर ((rvar > 9) || !reg)
				जाओ sigill;
			अगर (reg & 0x10) अणु
				अगर (user && !access_ok(addr, 8 * (rvar + 1)))
					जाओ sigbus;
			पूर्ण अन्यथा अणु
				अगर (user && !access_ok(addr, 8 * rvar))
					जाओ sigbus;
			पूर्ण
			अगर (rvar == 9)
				rvar = 8;

			क्रम (i = 16; rvar; rvar--, i++) अणु
				LoadDW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 4;
				regs->regs[i] = value;
			पूर्ण
			अगर ((reg & 0xf) == 9) अणु
				LoadDW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 8;
				regs->regs[30] = value;
			पूर्ण
			अगर (reg & 0x10) अणु
				LoadDW(addr, value, res);
				अगर (res)
					जाओ fault;
				regs->regs[31] = value;
			पूर्ण
			जाओ success;
#पूर्ण_अगर /* CONFIG_64BIT */

			जाओ sigill;

		हाल mm_sdm_func:
#अगर_घोषित CONFIG_64BIT
			reg = insn.mm_m_क्रमmat.rd;
			rvar = reg & 0xf;
			अगर ((rvar > 9) || !reg)
				जाओ sigill;
			अगर (reg & 0x10) अणु
				अगर (user && !access_ok(addr, 8 * (rvar + 1)))
					जाओ sigbus;
			पूर्ण अन्यथा अणु
				अगर (user && !access_ok(addr, 8 * rvar))
					जाओ sigbus;
			पूर्ण
			अगर (rvar == 9)
				rvar = 8;

			क्रम (i = 16; rvar; rvar--, i++) अणु
				value = regs->regs[i];
				StoreDW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 8;
			पूर्ण
			अगर ((reg & 0xf) == 9) अणु
				value = regs->regs[30];
				StoreDW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 8;
			पूर्ण
			अगर (reg & 0x10) अणु
				value = regs->regs[31];
				StoreDW(addr, value, res);
				अगर (res)
					जाओ fault;
			पूर्ण
			जाओ success;
#पूर्ण_अगर /* CONFIG_64BIT */

			जाओ sigill;

			/*  LWC2, SWC2, LDC2, SDC2 are not serviced */
		पूर्ण

		जाओ sigbus;

	हाल mm_pool32c_op:
		चयन (insn.mm_m_क्रमmat.func) अणु
		हाल mm_lwu_func:
			reg = insn.mm_m_क्रमmat.rd;
			जाओ loadWU;
		पूर्ण

		/*  LL,SC,LLD,SCD are not serviced */
		जाओ sigbus;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	हाल mm_pool32f_op:
		चयन (insn.mm_x_क्रमmat.func) अणु
		हाल mm_lwxc1_func:
		हाल mm_swxc1_func:
		हाल mm_ldxc1_func:
		हाल mm_sdxc1_func:
			जाओ fpu_emul;
		पूर्ण

		जाओ sigbus;

	हाल mm_ldc132_op:
	हाल mm_sdc132_op:
	हाल mm_lwc132_op:
	हाल mm_swc132_op: अणु
		व्योम __user *fault_addr = शून्य;

fpu_emul:
		/* roll back jump/branch */
		regs->cp0_epc = origpc;
		regs->regs[31] = orig31;

		die_अगर_kernel("Unaligned FP access in kernel code", regs);
		BUG_ON(!used_math());
		BUG_ON(!is_fpu_owner());

		res = fpu_emulator_cop1Handler(regs, &current->thपढ़ो.fpu, 1,
					       &fault_addr);
		own_fpu(1);	/* restore FPU state */

		/* If something went wrong, संकेत */
		process_fpemu_वापस(res, fault_addr, 0);

		अगर (res == 0)
			जाओ success;
		वापस;
	पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */

	हाल mm_lh32_op:
		reg = insn.mm_i_क्रमmat.rt;
		जाओ loadHW;

	हाल mm_lhu32_op:
		reg = insn.mm_i_क्रमmat.rt;
		जाओ loadHWU;

	हाल mm_lw32_op:
		reg = insn.mm_i_क्रमmat.rt;
		जाओ loadW;

	हाल mm_sh32_op:
		reg = insn.mm_i_क्रमmat.rt;
		जाओ storeHW;

	हाल mm_sw32_op:
		reg = insn.mm_i_क्रमmat.rt;
		जाओ storeW;

	हाल mm_ld32_op:
		reg = insn.mm_i_क्रमmat.rt;
		जाओ loadDW;

	हाल mm_sd32_op:
		reg = insn.mm_i_क्रमmat.rt;
		जाओ storeDW;

	हाल mm_pool16c_op:
		चयन (insn.mm16_m_क्रमmat.func) अणु
		हाल mm_lwm16_op:
			reg = insn.mm16_m_क्रमmat.rlist;
			rvar = reg + 1;
			अगर (user && !access_ok(addr, 4 * rvar))
				जाओ sigbus;

			क्रम (i = 16; rvar; rvar--, i++) अणु
				LoadW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 4;
				regs->regs[i] = value;
			पूर्ण
			LoadW(addr, value, res);
			अगर (res)
				जाओ fault;
			regs->regs[31] = value;

			जाओ success;

		हाल mm_swm16_op:
			reg = insn.mm16_m_क्रमmat.rlist;
			rvar = reg + 1;
			अगर (user && !access_ok(addr, 4 * rvar))
				जाओ sigbus;

			क्रम (i = 16; rvar; rvar--, i++) अणु
				value = regs->regs[i];
				StoreW(addr, value, res);
				अगर (res)
					जाओ fault;
				addr += 4;
			पूर्ण
			value = regs->regs[31];
			StoreW(addr, value, res);
			अगर (res)
				जाओ fault;

			जाओ success;

		पूर्ण

		जाओ sigbus;

	हाल mm_lhu16_op:
		reg = reg16to32[insn.mm16_rb_क्रमmat.rt];
		जाओ loadHWU;

	हाल mm_lw16_op:
		reg = reg16to32[insn.mm16_rb_क्रमmat.rt];
		जाओ loadW;

	हाल mm_sh16_op:
		reg = reg16to32st[insn.mm16_rb_क्रमmat.rt];
		जाओ storeHW;

	हाल mm_sw16_op:
		reg = reg16to32st[insn.mm16_rb_क्रमmat.rt];
		जाओ storeW;

	हाल mm_lwsp16_op:
		reg = insn.mm16_r5_क्रमmat.rt;
		जाओ loadW;

	हाल mm_swsp16_op:
		reg = insn.mm16_r5_क्रमmat.rt;
		जाओ storeW;

	हाल mm_lwgp16_op:
		reg = reg16to32[insn.mm16_r3_क्रमmat.rt];
		जाओ loadW;

	शेष:
		जाओ sigill;
	पूर्ण

loadHW:
	अगर (user && !access_ok(addr, 2))
		जाओ sigbus;

	LoadHW(addr, value, res);
	अगर (res)
		जाओ fault;
	regs->regs[reg] = value;
	जाओ success;

loadHWU:
	अगर (user && !access_ok(addr, 2))
		जाओ sigbus;

	LoadHWU(addr, value, res);
	अगर (res)
		जाओ fault;
	regs->regs[reg] = value;
	जाओ success;

loadW:
	अगर (user && !access_ok(addr, 4))
		जाओ sigbus;

	LoadW(addr, value, res);
	अगर (res)
		जाओ fault;
	regs->regs[reg] = value;
	जाओ success;

loadWU:
#अगर_घोषित CONFIG_64BIT
	/*
	 * A 32-bit kernel might be running on a 64-bit processor.  But
	 * अगर we're on a 32-bit processor and an i-cache incoherency
	 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
	 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
	 * inकाष्ठाions on 32-bit kernels.
	 */
	अगर (user && !access_ok(addr, 4))
		जाओ sigbus;

	LoadWU(addr, value, res);
	अगर (res)
		जाओ fault;
	regs->regs[reg] = value;
	जाओ success;
#पूर्ण_अगर /* CONFIG_64BIT */

	/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
	जाओ sigill;

loadDW:
#अगर_घोषित CONFIG_64BIT
	/*
	 * A 32-bit kernel might be running on a 64-bit processor.  But
	 * अगर we're on a 32-bit processor and an i-cache incoherency
	 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
	 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
	 * inकाष्ठाions on 32-bit kernels.
	 */
	अगर (user && !access_ok(addr, 8))
		जाओ sigbus;

	LoadDW(addr, value, res);
	अगर (res)
		जाओ fault;
	regs->regs[reg] = value;
	जाओ success;
#पूर्ण_अगर /* CONFIG_64BIT */

	/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
	जाओ sigill;

storeHW:
	अगर (user && !access_ok(addr, 2))
		जाओ sigbus;

	value = regs->regs[reg];
	StoreHW(addr, value, res);
	अगर (res)
		जाओ fault;
	जाओ success;

storeW:
	अगर (user && !access_ok(addr, 4))
		जाओ sigbus;

	value = regs->regs[reg];
	StoreW(addr, value, res);
	अगर (res)
		जाओ fault;
	जाओ success;

storeDW:
#अगर_घोषित CONFIG_64BIT
	/*
	 * A 32-bit kernel might be running on a 64-bit processor.  But
	 * अगर we're on a 32-bit processor and an i-cache incoherency
	 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
	 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
	 * inकाष्ठाions on 32-bit kernels.
	 */
	अगर (user && !access_ok(addr, 8))
		जाओ sigbus;

	value = regs->regs[reg];
	StoreDW(addr, value, res);
	अगर (res)
		जाओ fault;
	जाओ success;
#पूर्ण_अगर /* CONFIG_64BIT */

	/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
	जाओ sigill;

success:
	regs->cp0_epc = contpc;	/* advance or branch */

#अगर_घोषित CONFIG_DEBUG_FS
	unaligned_inकाष्ठाions++;
#पूर्ण_अगर
	वापस;

fault:
	/* roll back jump/branch */
	regs->cp0_epc = origpc;
	regs->regs[31] = orig31;
	/* Did we have an exception handler installed? */
	अगर (fixup_exception(regs))
		वापस;

	die_अगर_kernel("Unhandled kernel unaligned access", regs);
	क्रमce_sig(संक_अंश);

	वापस;

sigbus:
	die_अगर_kernel("Unhandled kernel unaligned access", regs);
	क्रमce_sig(SIGBUS);

	वापस;

sigill:
	die_अगर_kernel
	    ("Unhandled kernel unaligned access or invalid instruction", regs);
	क्रमce_sig(संक_अवैध);
पूर्ण

अटल व्योम emulate_load_store_MIPS16e(काष्ठा pt_regs *regs, व्योम __user * addr)
अणु
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक res;
	पूर्णांक reg;
	अचिन्हित दीर्घ orig31;
	u16 __user *pc16;
	अचिन्हित दीर्घ origpc;
	जोड़ mips16e_inकाष्ठाion mips16inst, oldinst;
	अचिन्हित पूर्णांक opcode;
	पूर्णांक extended = 0;
	bool user = user_mode(regs);

	origpc = regs->cp0_epc;
	orig31 = regs->regs[31];
	pc16 = (अचिन्हित लघु __user *)msk_isa16_mode(origpc);
	/*
	 * This load never faults.
	 */
	__get_user(mips16inst.full, pc16);
	oldinst = mips16inst;

	/* skip EXTEND inकाष्ठाion */
	अगर (mips16inst.ri.opcode == MIPS16e_extend_op) अणु
		extended = 1;
		pc16++;
		__get_user(mips16inst.full, pc16);
	पूर्ण अन्यथा अगर (delay_slot(regs)) अणु
		/*  skip jump inकाष्ठाions */
		/*  JAL/JALX are 32 bits but have OPCODE in first लघु पूर्णांक */
		अगर (mips16inst.ri.opcode == MIPS16e_jal_op)
			pc16++;
		pc16++;
		अगर (get_user(mips16inst.full, pc16))
			जाओ sigbus;
	पूर्ण

	opcode = mips16inst.ri.opcode;
	चयन (opcode) अणु
	हाल MIPS16e_i64_op:	/* I64 or RI64 inकाष्ठाion */
		चयन (mips16inst.i64.func) अणु	/* I64/RI64 func field check */
		हाल MIPS16e_ldpc_func:
		हाल MIPS16e_ldsp_func:
			reg = reg16to32[mips16inst.ri64.ry];
			जाओ loadDW;

		हाल MIPS16e_sdsp_func:
			reg = reg16to32[mips16inst.ri64.ry];
			जाओ ग_लिखोDW;

		हाल MIPS16e_sdrasp_func:
			reg = 29;	/* GPRSP */
			जाओ ग_लिखोDW;
		पूर्ण

		जाओ sigbus;

	हाल MIPS16e_swsp_op:
		reg = reg16to32[mips16inst.ri.rx];
		अगर (extended && cpu_has_mips16e2)
			चयन (mips16inst.ri.imm >> 5) अणु
			हाल 0:		/* SWSP */
			हाल 1:		/* SWGP */
				अवरोध;
			हाल 2:		/* SHGP */
				opcode = MIPS16e_sh_op;
				अवरोध;
			शेष:
				जाओ sigbus;
			पूर्ण
		अवरोध;

	हाल MIPS16e_lwpc_op:
		reg = reg16to32[mips16inst.ri.rx];
		अवरोध;

	हाल MIPS16e_lwsp_op:
		reg = reg16to32[mips16inst.ri.rx];
		अगर (extended && cpu_has_mips16e2)
			चयन (mips16inst.ri.imm >> 5) अणु
			हाल 0:		/* LWSP */
			हाल 1:		/* LWGP */
				अवरोध;
			हाल 2:		/* LHGP */
				opcode = MIPS16e_lh_op;
				अवरोध;
			हाल 4:		/* LHUGP */
				opcode = MIPS16e_lhu_op;
				अवरोध;
			शेष:
				जाओ sigbus;
			पूर्ण
		अवरोध;

	हाल MIPS16e_i8_op:
		अगर (mips16inst.i8.func != MIPS16e_swrasp_func)
			जाओ sigbus;
		reg = 29;	/* GPRSP */
		अवरोध;

	शेष:
		reg = reg16to32[mips16inst.rri.ry];
		अवरोध;
	पूर्ण

	चयन (opcode) अणु

	हाल MIPS16e_lb_op:
	हाल MIPS16e_lbu_op:
	हाल MIPS16e_sb_op:
		जाओ sigbus;

	हाल MIPS16e_lh_op:
		अगर (user && !access_ok(addr, 2))
			जाओ sigbus;

		LoadHW(addr, value, res);
		अगर (res)
			जाओ fault;
		MIPS16e_compute_वापस_epc(regs, &oldinst);
		regs->regs[reg] = value;
		अवरोध;

	हाल MIPS16e_lhu_op:
		अगर (user && !access_ok(addr, 2))
			जाओ sigbus;

		LoadHWU(addr, value, res);
		अगर (res)
			जाओ fault;
		MIPS16e_compute_वापस_epc(regs, &oldinst);
		regs->regs[reg] = value;
		अवरोध;

	हाल MIPS16e_lw_op:
	हाल MIPS16e_lwpc_op:
	हाल MIPS16e_lwsp_op:
		अगर (user && !access_ok(addr, 4))
			जाओ sigbus;

		LoadW(addr, value, res);
		अगर (res)
			जाओ fault;
		MIPS16e_compute_वापस_epc(regs, &oldinst);
		regs->regs[reg] = value;
		अवरोध;

	हाल MIPS16e_lwu_op:
#अगर_घोषित CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * अगर we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
		 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
		 * inकाष्ठाions on 32-bit kernels.
		 */
		अगर (user && !access_ok(addr, 4))
			जाओ sigbus;

		LoadWU(addr, value, res);
		अगर (res)
			जाओ fault;
		MIPS16e_compute_वापस_epc(regs, &oldinst);
		regs->regs[reg] = value;
		अवरोध;
#पूर्ण_अगर /* CONFIG_64BIT */

		/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
		जाओ sigill;

	हाल MIPS16e_ld_op:
loadDW:
#अगर_घोषित CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * अगर we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
		 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
		 * inकाष्ठाions on 32-bit kernels.
		 */
		अगर (user && !access_ok(addr, 8))
			जाओ sigbus;

		LoadDW(addr, value, res);
		अगर (res)
			जाओ fault;
		MIPS16e_compute_वापस_epc(regs, &oldinst);
		regs->regs[reg] = value;
		अवरोध;
#पूर्ण_अगर /* CONFIG_64BIT */

		/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
		जाओ sigill;

	हाल MIPS16e_sh_op:
		अगर (user && !access_ok(addr, 2))
			जाओ sigbus;

		MIPS16e_compute_वापस_epc(regs, &oldinst);
		value = regs->regs[reg];
		StoreHW(addr, value, res);
		अगर (res)
			जाओ fault;
		अवरोध;

	हाल MIPS16e_sw_op:
	हाल MIPS16e_swsp_op:
	हाल MIPS16e_i8_op:	/* actually - MIPS16e_swrasp_func */
		अगर (user && !access_ok(addr, 4))
			जाओ sigbus;

		MIPS16e_compute_वापस_epc(regs, &oldinst);
		value = regs->regs[reg];
		StoreW(addr, value, res);
		अगर (res)
			जाओ fault;
		अवरोध;

	हाल MIPS16e_sd_op:
ग_लिखोDW:
#अगर_घोषित CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * अगर we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit inकाष्ठाion here the sdl/sdr
		 * would blow up, so क्रम now we करोn't handle unaligned 64-bit
		 * inकाष्ठाions on 32-bit kernels.
		 */
		अगर (user && !access_ok(addr, 8))
			जाओ sigbus;

		MIPS16e_compute_वापस_epc(regs, &oldinst);
		value = regs->regs[reg];
		StoreDW(addr, value, res);
		अगर (res)
			जाओ fault;
		अवरोध;
#पूर्ण_अगर /* CONFIG_64BIT */

		/* Cannot handle 64-bit inकाष्ठाions in 32-bit kernel */
		जाओ sigill;

	शेष:
		/*
		 * Pheeee...  We encountered an yet unknown inकाष्ठाion or
		 * cache coherence problem.  Die sucker, die ...
		 */
		जाओ sigill;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	unaligned_inकाष्ठाions++;
#पूर्ण_अगर

	वापस;

fault:
	/* roll back jump/branch */
	regs->cp0_epc = origpc;
	regs->regs[31] = orig31;
	/* Did we have an exception handler installed? */
	अगर (fixup_exception(regs))
		वापस;

	die_अगर_kernel("Unhandled kernel unaligned access", regs);
	क्रमce_sig(संक_अंश);

	वापस;

sigbus:
	die_अगर_kernel("Unhandled kernel unaligned access", regs);
	क्रमce_sig(SIGBUS);

	वापस;

sigill:
	die_अगर_kernel
	    ("Unhandled kernel unaligned access or invalid instruction", regs);
	क्रमce_sig(संक_अवैध);
पूर्ण

यंत्रlinkage व्योम करो_ade(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state;
	अचिन्हित पूर्णांक *pc;

	prev_state = exception_enter();
	perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS,
			1, regs, regs->cp0_badvaddr);
	/*
	 * Did we catch a fault trying to load an inकाष्ठाion?
	 */
	अगर (regs->cp0_badvaddr == regs->cp0_epc)
		जाओ sigbus;

	अगर (user_mode(regs) && !test_thपढ़ो_flag(TIF_FIXADE))
		जाओ sigbus;
	अगर (unaligned_action == UNALIGNED_ACTION_SIGNAL)
		जाओ sigbus;

	/*
	 * Do branch emulation only अगर we didn't क्रमward the exception.
	 * This is all so but ugly ...
	 */

	/*
	 * Are we running in microMIPS mode?
	 */
	अगर (get_isa16_mode(regs->cp0_epc)) अणु
		/*
		 * Did we catch a fault trying to load an inकाष्ठाion in
		 * 16-bit mode?
		 */
		अगर (regs->cp0_badvaddr == msk_isa16_mode(regs->cp0_epc))
			जाओ sigbus;
		अगर (unaligned_action == UNALIGNED_ACTION_SHOW)
			show_रेजिस्टरs(regs);

		अगर (cpu_has_mmips) अणु
			emulate_load_store_microMIPS(regs,
				(व्योम __user *)regs->cp0_badvaddr);
			वापस;
		पूर्ण

		अगर (cpu_has_mips16) अणु
			emulate_load_store_MIPS16e(regs,
				(व्योम __user *)regs->cp0_badvaddr);
			वापस;
		पूर्ण

		जाओ sigbus;
	पूर्ण

	अगर (unaligned_action == UNALIGNED_ACTION_SHOW)
		show_रेजिस्टरs(regs);
	pc = (अचिन्हित पूर्णांक *)exception_epc(regs);

	emulate_load_store_insn(regs, (व्योम __user *)regs->cp0_badvaddr, pc);

	वापस;

sigbus:
	die_अगर_kernel("Kernel unaligned instruction access", regs);
	क्रमce_sig(SIGBUS);

	/*
	 * XXX On वापस from the संकेत handler we should advance the epc
	 */
	exception_निकास(prev_state);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक __init debugfs_unaligned(व्योम)
अणु
	debugfs_create_u32("unaligned_instructions", S_IRUGO, mips_debugfs_dir,
			   &unaligned_inकाष्ठाions);
	debugfs_create_u32("unaligned_action", S_IRUGO | S_IWUSR,
			   mips_debugfs_dir, &unaligned_action);
	वापस 0;
पूर्ण
arch_initcall(debugfs_unaligned);
#पूर्ण_अगर

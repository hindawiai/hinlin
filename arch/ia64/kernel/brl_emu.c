<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Emulation of the "brl" inकाष्ठाion क्रम IA64 processors that
 *  करोn't support it in hardware.
 *  Author: Stephan Zeisset, Intel Corp. <Stephan.Zeisset@पूर्णांकel.com>
 *
 *    02/22/02	D. Mosberger	Clear si_flgs, si_isr, and si_imm to aव्योम
 *				leaking kernel bits.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>

बाह्य अक्षर ia64_set_b1, ia64_set_b2, ia64_set_b3, ia64_set_b4, ia64_set_b5;

काष्ठा illegal_op_वापस अणु
	अचिन्हित दीर्घ fkt, arg1, arg2, arg3;
पूर्ण;

/*
 *  The unimplemented bits of a भव address must be set
 *  to the value of the most signअगरicant implemented bit.
 *  unimpl_va_mask includes all unimplemented bits and
 *  the most signअगरicant implemented bit, so the result
 *  of an and operation with the mask must be all 0's
 *  or all 1's क्रम the address to be valid.
 */
#घोषणा unimplemented_भव_address(va) (						\
	((va) & local_cpu_data->unimpl_va_mask) != 0 &&					\
	((va) & local_cpu_data->unimpl_va_mask) != local_cpu_data->unimpl_va_mask	\
)

/*
 *  The unimplemented bits of a physical address must be 0.
 *  unimpl_pa_mask includes all unimplemented bits, so the result
 *  of an and operation with the mask must be all 0's क्रम the
 *  address to be valid.
 */
#घोषणा unimplemented_physical_address(pa) (		\
	((pa) & local_cpu_data->unimpl_pa_mask) != 0	\
)

/*
 *  Handle an illegal operation fault that was caused by an
 *  unimplemented "brl" inकाष्ठाion.
 *  If we are not successful (e.g because the illegal operation
 *  wasn't caused by a "brl" after all), we वापस -1.
 *  If we are successful, we वापस either 0 or the address
 *  of a "fixup" function क्रम manipulating preserved रेजिस्टर
 *  state.
 */

काष्ठा illegal_op_वापस
ia64_emulate_brl (काष्ठा pt_regs *regs, अचिन्हित दीर्घ ar_ec)
अणु
	अचिन्हित दीर्घ bundle[2];
	अचिन्हित दीर्घ opcode, btype, qp, offset, cpl;
	अचिन्हित दीर्घ next_ip;
	काष्ठा illegal_op_वापस rv;
	दीर्घ पंचांगp_taken, unimplemented_address;

	rv.fkt = (अचिन्हित दीर्घ) -1;

	/*
	 *  Decode the inकाष्ठाion bundle.
	 */

	अगर (copy_from_user(bundle, (व्योम *) (regs->cr_iip), माप(bundle)))
		वापस rv;

	next_ip = (अचिन्हित दीर्घ) regs->cr_iip + 16;

	/* "brl" must be in slot 2. */
	अगर (ia64_psr(regs)->ri != 1) वापस rv;

	/* Must be "mlx" ढाँचा */
	अगर ((bundle[0] & 0x1e) != 0x4) वापस rv;

	opcode = (bundle[1] >> 60);
	btype = ((bundle[1] >> 29) & 0x7);
	qp = ((bundle[1] >> 23) & 0x3f);
	offset = ((bundle[1] & 0x0800000000000000L) << 4)
		| ((bundle[1] & 0x00fffff000000000L) >> 32)
		| ((bundle[1] & 0x00000000007fffffL) << 40)
		| ((bundle[0] & 0xffff000000000000L) >> 24);

	पंचांगp_taken = regs->pr & (1L << qp);

	चयन(opcode) अणु

		हाल 0xC:
			/*
			 *  Long Branch.
			 */
			अगर (btype != 0) वापस rv;
			rv.fkt = 0;
			अगर (!(पंचांगp_taken)) अणु
				/*
				 *  Qualअगरying predicate is 0.
				 *  Skip inकाष्ठाion.
				 */
				regs->cr_iip = next_ip;
				ia64_psr(regs)->ri = 0;
				वापस rv;
			पूर्ण
			अवरोध;

		हाल 0xD:
			/*
			 *  Long Call.
			 */
			rv.fkt = 0;
			अगर (!(पंचांगp_taken)) अणु
				/*
				 *  Qualअगरying predicate is 0.
				 *  Skip inकाष्ठाion.
				 */
				regs->cr_iip = next_ip;
				ia64_psr(regs)->ri = 0;
				वापस rv;
			पूर्ण

			/*
			 *  BR[btype] = IP+16
			 */
			चयन(btype) अणु
				हाल 0:
					regs->b0 = next_ip;
					अवरोध;
				हाल 1:
					rv.fkt = (अचिन्हित दीर्घ) &ia64_set_b1;
					अवरोध;
				हाल 2:
					rv.fkt = (अचिन्हित दीर्घ) &ia64_set_b2;
					अवरोध;
				हाल 3:
					rv.fkt = (अचिन्हित दीर्घ) &ia64_set_b3;
					अवरोध;
				हाल 4:
					rv.fkt = (अचिन्हित दीर्घ) &ia64_set_b4;
					अवरोध;
				हाल 5:
					rv.fkt = (अचिन्हित दीर्घ) &ia64_set_b5;
					अवरोध;
				हाल 6:
					regs->b6 = next_ip;
					अवरोध;
				हाल 7:
					regs->b7 = next_ip;
					अवरोध;
			पूर्ण
			rv.arg1 = next_ip;

			/*
			 *  AR[PFS].pfm = CFM
			 *  AR[PFS].pec = AR[EC]
			 *  AR[PFS].ppl = PSR.cpl
			 */
			cpl = ia64_psr(regs)->cpl;
			regs->ar_pfs = ((regs->cr_अगरs & 0x3fffffffff)
					| (ar_ec << 52) | (cpl << 62));

			/*
			 *  CFM.sof -= CFM.sol
			 *  CFM.sol = 0
			 *  CFM.sor = 0
			 *  CFM.rrb.gr = 0
			 *  CFM.rrb.fr = 0
			 *  CFM.rrb.pr = 0
			 */
			regs->cr_अगरs = ((regs->cr_अगरs & 0xffffffc00000007f)
					- ((regs->cr_अगरs >> 7) & 0x7f));

			अवरोध;

		शेष:
			/*
			 *  Unknown opcode.
			 */
			वापस rv;

	पूर्ण

	regs->cr_iip += offset;
	ia64_psr(regs)->ri = 0;

	अगर (ia64_psr(regs)->it == 0)
		unimplemented_address = unimplemented_physical_address(regs->cr_iip);
	अन्यथा
		unimplemented_address = unimplemented_भव_address(regs->cr_iip);

	अगर (unimplemented_address) अणु
		/*
		 *  The target address contains unimplemented bits.
		 */
		prपूर्णांकk(KERN_DEBUG "Woah! Unimplemented Instruction Address Trap!\n");
		क्रमce_sig_fault(संक_अवैध, ILL_BADIADDR, (व्योम __user *)शून्य,
				0, 0, 0);
	पूर्ण अन्यथा अगर (ia64_psr(regs)->tb) अणु
		/*
		 *  Branch Tracing is enabled.
		 *  Force a taken branch संकेत.
		 */
		क्रमce_sig_fault(SIGTRAP, TRAP_BRANCH, (व्योम __user *)शून्य,
				0, 0, 0);
	पूर्ण अन्यथा अगर (ia64_psr(regs)->ss) अणु
		/*
		 *  Single Step is enabled.
		 *  Force a trace संकेत.
		 */
		क्रमce_sig_fault(SIGTRAP, TRAP_TRACE, (व्योम __user *)शून्य,
				0, 0, 0);
	पूर्ण
	वापस rv;
पूर्ण

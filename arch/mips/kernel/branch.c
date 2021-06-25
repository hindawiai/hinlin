<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 97, 2000, 2001 by Ralf Baechle
 * Copyright (C) 2001 MIPS Technologies, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/export.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/fpu_emulator.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/mips-r2-to-r6-emul.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/uaccess.h>

#समावेश "probes-common.h"

/*
 * Calculate and वापस exception PC in हाल of branch delay slot
 * क्रम microMIPS and MIPS16e. It करोes not clear the ISA mode bit.
 */
पूर्णांक __isa_exception_epc(काष्ठा pt_regs *regs)
अणु
	अचिन्हित लघु inst;
	दीर्घ epc = regs->cp0_epc;

	/* Calculate exception PC in branch delay slot. */
	अगर (__get_user(inst, (u16 __user *) msk_isa16_mode(epc))) अणु
		/* This should never happen because delay slot was checked. */
		क्रमce_sig(संक_अंश);
		वापस epc;
	पूर्ण
	अगर (cpu_has_mips16) अणु
		जोड़ mips16e_inकाष्ठाion inst_mips16e;

		inst_mips16e.full = inst;
		अगर (inst_mips16e.ri.opcode == MIPS16e_jal_op)
			epc += 4;
		अन्यथा
			epc += 2;
	पूर्ण अन्यथा अगर (mm_insn_16bit(inst))
		epc += 2;
	अन्यथा
		epc += 4;

	वापस epc;
पूर्ण

/* (microMIPS) Convert 16-bit रेजिस्टर encoding to 32-bit रेजिस्टर encoding. */
अटल स्थिर अचिन्हित पूर्णांक reg16to32map[8] = अणु16, 17, 2, 3, 4, 5, 6, 7पूर्ण;

पूर्णांक __mm_isBranchInstr(काष्ठा pt_regs *regs, काष्ठा mm_decoded_insn dec_insn,
		       अचिन्हित दीर्घ *contpc)
अणु
	जोड़ mips_inकाष्ठाion insn = (जोड़ mips_inकाष्ठाion)dec_insn.insn;
	पूर्णांक __maybe_unused bc_false = 0;

	अगर (!cpu_has_mmips)
		वापस 0;

	चयन (insn.mm_i_क्रमmat.opcode) अणु
	हाल mm_pool32a_op:
		अगर ((insn.mm_i_क्रमmat.simmediate & MM_POOL32A_MINOR_MASK) ==
		    mm_pool32axf_op) अणु
			चयन (insn.mm_i_क्रमmat.simmediate >>
				MM_POOL32A_MINOR_SHIFT) अणु
			हाल mm_jalr_op:
			हाल mm_jalrhb_op:
			हाल mm_jalrs_op:
			हाल mm_jalrshb_op:
				अगर (insn.mm_i_क्रमmat.rt != 0)	/* Not mm_jr */
					regs->regs[insn.mm_i_क्रमmat.rt] =
						regs->cp0_epc +
						dec_insn.pc_inc +
						dec_insn.next_pc_inc;
				*contpc = regs->regs[insn.mm_i_क्रमmat.rs];
				वापस 1;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल mm_pool32i_op:
		चयन (insn.mm_i_क्रमmat.rt) अणु
		हाल mm_bltzals_op:
		हाल mm_bltzal_op:
			regs->regs[31] = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
			fallthrough;
		हाल mm_bltz_op:
			अगर ((दीर्घ)regs->regs[insn.mm_i_क्रमmat.rs] < 0)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_क्रमmat.simmediate << 1);
			अन्यथा
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			वापस 1;
		हाल mm_bgezals_op:
		हाल mm_bgezal_op:
			regs->regs[31] = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			fallthrough;
		हाल mm_bgez_op:
			अगर ((दीर्घ)regs->regs[insn.mm_i_क्रमmat.rs] >= 0)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_क्रमmat.simmediate << 1);
			अन्यथा
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			वापस 1;
		हाल mm_blez_op:
			अगर ((दीर्घ)regs->regs[insn.mm_i_क्रमmat.rs] <= 0)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_क्रमmat.simmediate << 1);
			अन्यथा
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			वापस 1;
		हाल mm_bgtz_op:
			अगर ((दीर्घ)regs->regs[insn.mm_i_क्रमmat.rs] <= 0)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_क्रमmat.simmediate << 1);
			अन्यथा
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			वापस 1;
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
		हाल mm_bc2f_op:
		हाल mm_bc1f_op: अणु
			अचिन्हित पूर्णांक fcr31;
			अचिन्हित पूर्णांक bit;

			bc_false = 1;
			fallthrough;
		हाल mm_bc2t_op:
		हाल mm_bc1t_op:
			preempt_disable();
			अगर (is_fpu_owner())
			        fcr31 = पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);
			अन्यथा
				fcr31 = current->thपढ़ो.fpu.fcr31;
			preempt_enable();

			अगर (bc_false)
				fcr31 = ~fcr31;

			bit = (insn.mm_i_क्रमmat.rs >> 2);
			bit += (bit != 0);
			bit += 23;
			अगर (fcr31 & (1 << bit))
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_क्रमmat.simmediate << 1);
			अन्यथा
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc + dec_insn.next_pc_inc;
			वापस 1;
		पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */
		पूर्ण
		अवरोध;
	हाल mm_pool16c_op:
		चयन (insn.mm_i_क्रमmat.rt) अणु
		हाल mm_jalr16_op:
		हाल mm_jalrs16_op:
			regs->regs[31] = regs->cp0_epc +
				dec_insn.pc_inc + dec_insn.next_pc_inc;
			fallthrough;
		हाल mm_jr16_op:
			*contpc = regs->regs[insn.mm_i_क्रमmat.rs];
			वापस 1;
		पूर्ण
		अवरोध;
	हाल mm_beqz16_op:
		अगर ((दीर्घ)regs->regs[reg16to32map[insn.mm_b1_क्रमmat.rs]] == 0)
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.mm_b1_क्रमmat.simmediate << 1);
		अन्यथा
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc + dec_insn.next_pc_inc;
		वापस 1;
	हाल mm_bnez16_op:
		अगर ((दीर्घ)regs->regs[reg16to32map[insn.mm_b1_क्रमmat.rs]] != 0)
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.mm_b1_क्रमmat.simmediate << 1);
		अन्यथा
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc + dec_insn.next_pc_inc;
		वापस 1;
	हाल mm_b16_op:
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			 (insn.mm_b0_क्रमmat.simmediate << 1);
		वापस 1;
	हाल mm_beq32_op:
		अगर (regs->regs[insn.mm_i_क्रमmat.rs] ==
		    regs->regs[insn.mm_i_क्रमmat.rt])
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.mm_i_क्रमmat.simmediate << 1);
		अन्यथा
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		वापस 1;
	हाल mm_bne32_op:
		अगर (regs->regs[insn.mm_i_क्रमmat.rs] !=
		    regs->regs[insn.mm_i_क्रमmat.rt])
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.mm_i_क्रमmat.simmediate << 1);
		अन्यथा
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc + dec_insn.next_pc_inc;
		वापस 1;
	हाल mm_jalx32_op:
		regs->regs[31] = regs->cp0_epc +
			dec_insn.pc_inc + dec_insn.next_pc_inc;
		*contpc = regs->cp0_epc + dec_insn.pc_inc;
		*contpc >>= 28;
		*contpc <<= 28;
		*contpc |= (insn.j_क्रमmat.target << 2);
		वापस 1;
	हाल mm_jals32_op:
	हाल mm_jal32_op:
		regs->regs[31] = regs->cp0_epc +
			dec_insn.pc_inc + dec_insn.next_pc_inc;
		fallthrough;
	हाल mm_j32_op:
		*contpc = regs->cp0_epc + dec_insn.pc_inc;
		*contpc >>= 27;
		*contpc <<= 27;
		*contpc |= (insn.j_क्रमmat.target << 1);
		set_isa16_mode(*contpc);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Compute वापस address and emulate branch in microMIPS mode after an
 * exception only. It करोes not handle compact branches/jumps and cannot
 * be used in पूर्णांकerrupt context. (Compact branches/jumps करो not cause
 * exceptions.)
 */
पूर्णांक __microMIPS_compute_वापस_epc(काष्ठा pt_regs *regs)
अणु
	u16 __user *pc16;
	u16 halfword;
	अचिन्हित पूर्णांक word;
	अचिन्हित दीर्घ contpc;
	काष्ठा mm_decoded_insn mminsn = अणु 0 पूर्ण;

	mminsn.micro_mips_mode = 1;

	/* This load never faults. */
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
		जाओ sigsegv;
	mminsn.next_pc_inc = 2;
	word = ((अचिन्हित पूर्णांक)halfword << 16);

	अगर (!mm_insn_16bit(halfword)) अणु
		pc16++;
		अगर (get_user(halfword, pc16))
			जाओ sigsegv;
		mminsn.next_pc_inc = 4;
		word |= halfword;
	पूर्ण
	mminsn.next_insn = word;

	mm_isBranchInstr(regs, mminsn, &contpc);

	regs->cp0_epc = contpc;

	वापस 0;

sigsegv:
	क्रमce_sig(संक_अंश);
	वापस -EFAULT;
पूर्ण

/*
 * Compute वापस address and emulate branch in MIPS16e mode after an
 * exception only. It करोes not handle compact branches/jumps and cannot
 * be used in पूर्णांकerrupt context. (Compact branches/jumps करो not cause
 * exceptions.)
 */
पूर्णांक __MIPS16e_compute_वापस_epc(काष्ठा pt_regs *regs)
अणु
	u16 __user *addr;
	जोड़ mips16e_inकाष्ठाion inst;
	u16 inst2;
	u32 fullinst;
	दीर्घ epc;

	epc = regs->cp0_epc;

	/* Read the inकाष्ठाion. */
	addr = (u16 __user *)msk_isa16_mode(epc);
	अगर (__get_user(inst.full, addr)) अणु
		क्रमce_sig(संक_अंश);
		वापस -EFAULT;
	पूर्ण

	चयन (inst.ri.opcode) अणु
	हाल MIPS16e_extend_op:
		regs->cp0_epc += 4;
		वापस 0;

		/*
		 *  JAL and JALX in MIPS16e mode
		 */
	हाल MIPS16e_jal_op:
		addr += 1;
		अगर (__get_user(inst2, addr)) अणु
			क्रमce_sig(संक_अंश);
			वापस -EFAULT;
		पूर्ण
		fullinst = ((अचिन्हित)inst.full << 16) | inst2;
		regs->regs[31] = epc + 6;
		epc += 4;
		epc >>= 28;
		epc <<= 28;
		/*
		 * JAL:5 X:1 TARGET[20-16]:5 TARGET[25:21]:5 TARGET[15:0]:16
		 *
		 * ......TARGET[15:0].................TARGET[20:16]...........
		 * ......TARGET[25:21]
		 */
		epc |=
		    ((fullinst & 0xffff) << 2) | ((fullinst & 0x3e00000) >> 3) |
		    ((fullinst & 0x1f0000) << 7);
		अगर (!inst.jal.x)
			set_isa16_mode(epc);	/* Set ISA mode bit. */
		regs->cp0_epc = epc;
		वापस 0;

		/*
		 *  J(AL)R(C)
		 */
	हाल MIPS16e_rr_op:
		अगर (inst.rr.func == MIPS16e_jr_func) अणु

			अगर (inst.rr.ra)
				regs->cp0_epc = regs->regs[31];
			अन्यथा
				regs->cp0_epc =
				    regs->regs[reg16to32[inst.rr.rx]];

			अगर (inst.rr.l) अणु
				अगर (inst.rr.nd)
					regs->regs[31] = epc + 2;
				अन्यथा
					regs->regs[31] = epc + 4;
			पूर्ण
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * All other हालs have no branch delay slot and are 16-bits.
	 * Branches करो not cause an exception.
	 */
	regs->cp0_epc += 2;

	वापस 0;
पूर्ण

/**
 * __compute_वापस_epc_क्रम_insn - Computes the वापस address and करो emulate
 *				    branch simulation, अगर required.
 *
 * @regs:	Poपूर्णांकer to pt_regs
 * @insn:	branch inकाष्ठाion to decode
 * Return:	-EFAULT on error and क्रमces संक_अवैध, and on success
 *		वापसs 0 or BRANCH_LIKELY_TAKEN as appropriate after
 *		evaluating the branch.
 *
 * MIPS R6 Compact branches and क्रमbidden slots:
 *	Compact branches करो not throw exceptions because they करो
 *	not have delay slots. The क्रमbidden slot inकाष्ठाion ($PC+4)
 *	is only executed अगर the branch was not taken. Otherwise the
 *	क्रमbidden slot is skipped entirely. This means that the
 *	only possible reason to be here because of a MIPS R6 compact
 *	branch inकाष्ठाion is that the क्रमbidden slot has thrown one.
 *	In that हाल the branch was not taken, so the EPC can be safely
 *	set to EPC + 8.
 */
पूर्णांक __compute_वापस_epc_क्रम_insn(काष्ठा pt_regs *regs,
				   जोड़ mips_inकाष्ठाion insn)
अणु
	दीर्घ epc = regs->cp0_epc;
	अचिन्हित पूर्णांक dspcontrol;
	पूर्णांक ret = 0;

	चयन (insn.i_क्रमmat.opcode) अणु
	/*
	 * jr and jalr are in r_क्रमmat क्रमmat.
	 */
	हाल spec_op:
		चयन (insn.r_क्रमmat.func) अणु
		हाल jalr_op:
			regs->regs[insn.r_क्रमmat.rd] = epc + 8;
			fallthrough;
		हाल jr_op:
			अगर (NO_R6EMU && insn.r_क्रमmat.func == jr_op)
				जाओ sigill_r2r6;
			regs->cp0_epc = regs->regs[insn.r_क्रमmat.rs];
			अवरोध;
		पूर्ण
		अवरोध;

	/*
	 * This group contains:
	 * bltz_op, bgez_op, bltzl_op, bgezl_op,
	 * bltzal_op, bgezal_op, bltzall_op, bgezall_op.
	 */
	हाल bcond_op:
		चयन (insn.i_क्रमmat.rt) अणु
		हाल bltzl_op:
			अगर (NO_R6EMU)
				जाओ sigill_r2r6;
			fallthrough;
		हाल bltz_op:
			अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] < 0) अणु
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
				अगर (insn.i_क्रमmat.rt == bltzl_op)
					ret = BRANCH_LIKELY_TAKEN;
			पूर्ण अन्यथा
				epc += 8;
			regs->cp0_epc = epc;
			अवरोध;

		हाल bgezl_op:
			अगर (NO_R6EMU)
				जाओ sigill_r2r6;
			fallthrough;
		हाल bgez_op:
			अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] >= 0) अणु
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
				अगर (insn.i_क्रमmat.rt == bgezl_op)
					ret = BRANCH_LIKELY_TAKEN;
			पूर्ण अन्यथा
				epc += 8;
			regs->cp0_epc = epc;
			अवरोध;

		हाल bltzal_op:
		हाल bltzall_op:
			अगर (NO_R6EMU && (insn.i_क्रमmat.rs ||
			    insn.i_क्रमmat.rt == bltzall_op))
				जाओ sigill_r2r6;
			regs->regs[31] = epc + 8;
			/*
			 * OK we are here either because we hit a NAL
			 * inकाष्ठाion or because we are emulating an
			 * old bltzalअणु,lपूर्ण one. Let's figure out what the
			 * हाल really is.
			 */
			अगर (!insn.i_क्रमmat.rs) अणु
				/*
				 * NAL or BLTZAL with rs == 0
				 * Doesn't matter अगर we are R6 or not. The
				 * result is the same
				 */
				regs->cp0_epc += 4 +
					(insn.i_क्रमmat.simmediate << 2);
				अवरोध;
			पूर्ण
			/* Now करो the real thing क्रम non-R6 BLTZALअणु,Lपूर्ण */
			अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] < 0) अणु
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
				अगर (insn.i_क्रमmat.rt == bltzall_op)
					ret = BRANCH_LIKELY_TAKEN;
			पूर्ण अन्यथा
				epc += 8;
			regs->cp0_epc = epc;
			अवरोध;

		हाल bgezal_op:
		हाल bgezall_op:
			अगर (NO_R6EMU && (insn.i_क्रमmat.rs ||
			    insn.i_क्रमmat.rt == bgezall_op))
				जाओ sigill_r2r6;
			regs->regs[31] = epc + 8;
			/*
			 * OK we are here either because we hit a BAL
			 * inकाष्ठाion or because we are emulating an
			 * old bgezalअणु,lपूर्ण one. Let's figure out what the
			 * हाल really is.
			 */
			अगर (!insn.i_क्रमmat.rs) अणु
				/*
				 * BAL or BGEZAL with rs == 0
				 * Doesn't matter अगर we are R6 or not. The
				 * result is the same
				 */
				regs->cp0_epc += 4 +
					(insn.i_क्रमmat.simmediate << 2);
				अवरोध;
			पूर्ण
			/* Now करो the real thing क्रम non-R6 BGEZALअणु,Lपूर्ण */
			अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] >= 0) अणु
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
				अगर (insn.i_क्रमmat.rt == bgezall_op)
					ret = BRANCH_LIKELY_TAKEN;
			पूर्ण अन्यथा
				epc += 8;
			regs->cp0_epc = epc;
			अवरोध;

		हाल bposge32_op:
			अगर (!cpu_has_dsp)
				जाओ sigill_dsp;

			dspcontrol = rddsp(0x01);

			अगर (dspcontrol >= 32) अणु
				epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			पूर्ण अन्यथा
				epc += 8;
			regs->cp0_epc = epc;
			अवरोध;
		पूर्ण
		अवरोध;

	/*
	 * These are unconditional and in j_क्रमmat.
	 */
	हाल jalx_op:
	हाल jal_op:
		regs->regs[31] = regs->cp0_epc + 8;
		fallthrough;
	हाल j_op:
		epc += 4;
		epc >>= 28;
		epc <<= 28;
		epc |= (insn.j_क्रमmat.target << 2);
		regs->cp0_epc = epc;
		अगर (insn.i_क्रमmat.opcode == jalx_op)
			set_isa16_mode(regs->cp0_epc);
		अवरोध;

	/*
	 * These are conditional and in i_क्रमmat.
	 */
	हाल beql_op:
		अगर (NO_R6EMU)
			जाओ sigill_r2r6;
		fallthrough;
	हाल beq_op:
		अगर (regs->regs[insn.i_क्रमmat.rs] ==
		    regs->regs[insn.i_क्रमmat.rt]) अणु
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अगर (insn.i_क्रमmat.opcode == beql_op)
				ret = BRANCH_LIKELY_TAKEN;
		पूर्ण अन्यथा
			epc += 8;
		regs->cp0_epc = epc;
		अवरोध;

	हाल bnel_op:
		अगर (NO_R6EMU)
			जाओ sigill_r2r6;
		fallthrough;
	हाल bne_op:
		अगर (regs->regs[insn.i_क्रमmat.rs] !=
		    regs->regs[insn.i_क्रमmat.rt]) अणु
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अगर (insn.i_क्रमmat.opcode == bnel_op)
				ret = BRANCH_LIKELY_TAKEN;
		पूर्ण अन्यथा
			epc += 8;
		regs->cp0_epc = epc;
		अवरोध;

	हाल blezl_op: /* not really i_क्रमmat */
		अगर (!insn.i_क्रमmat.rt && NO_R6EMU)
			जाओ sigill_r2r6;
		fallthrough;
	हाल blez_op:
		/*
		 * Compact branches क्रम R6 क्रम the
		 * blez and blezl opcodes.
		 * BLEZ  | rs = 0 | rt != 0  == BLEZALC
		 * BLEZ  | rs = rt != 0      == BGEZALC
		 * BLEZ  | rs != 0 | rt != 0 == BGEUC
		 * BLEZL | rs = 0 | rt != 0  == BLEZC
		 * BLEZL | rs = rt != 0      == BGEZC
		 * BLEZL | rs != 0 | rt != 0 == BGEC
		 *
		 * For real BLEZअणु,Lपूर्ण, rt is always 0.
		 */

		अगर (cpu_has_mips_r6 && insn.i_क्रमmat.rt) अणु
			अगर ((insn.i_क्रमmat.opcode == blez_op) &&
			    ((!insn.i_क्रमmat.rs && insn.i_क्रमmat.rt) ||
			     (insn.i_क्रमmat.rs == insn.i_क्रमmat.rt)))
				regs->regs[31] = epc + 4;
			regs->cp0_epc += 8;
			अवरोध;
		पूर्ण
		/* rt field assumed to be zero */
		अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] <= 0) अणु
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अगर (insn.i_क्रमmat.opcode == blezl_op)
				ret = BRANCH_LIKELY_TAKEN;
		पूर्ण अन्यथा
			epc += 8;
		regs->cp0_epc = epc;
		अवरोध;

	हाल bgtzl_op:
		अगर (!insn.i_क्रमmat.rt && NO_R6EMU)
			जाओ sigill_r2r6;
		fallthrough;
	हाल bgtz_op:
		/*
		 * Compact branches क्रम R6 क्रम the
		 * bgtz and bgtzl opcodes.
		 * BGTZ  | rs = 0 | rt != 0  == BGTZALC
		 * BGTZ  | rs = rt != 0      == BLTZALC
		 * BGTZ  | rs != 0 | rt != 0 == BLTUC
		 * BGTZL | rs = 0 | rt != 0  == BGTZC
		 * BGTZL | rs = rt != 0      == BLTZC
		 * BGTZL | rs != 0 | rt != 0 == BLTC
		 *
		 * *ZALC varपूर्णांक क्रम BGTZ &&& rt != 0
		 * For real GTZअणु,Lपूर्ण, rt is always 0.
		 */
		अगर (cpu_has_mips_r6 && insn.i_क्रमmat.rt) अणु
			अगर ((insn.i_क्रमmat.opcode == blez_op) &&
			    ((!insn.i_क्रमmat.rs && insn.i_क्रमmat.rt) ||
			    (insn.i_क्रमmat.rs == insn.i_क्रमmat.rt)))
				regs->regs[31] = epc + 4;
			regs->cp0_epc += 8;
			अवरोध;
		पूर्ण

		/* rt field assumed to be zero */
		अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] > 0) अणु
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
			अगर (insn.i_क्रमmat.opcode == bgtzl_op)
				ret = BRANCH_LIKELY_TAKEN;
		पूर्ण अन्यथा
			epc += 8;
		regs->cp0_epc = epc;
		अवरोध;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	/*
	 * And now the FPA/cp1 branch inकाष्ठाions.
	 */
	हाल cop1_op: अणु
		अचिन्हित पूर्णांक bit, fcr31, reg;

		अगर (cpu_has_mips_r6 &&
		    ((insn.i_क्रमmat.rs == bc1eqz_op) ||
		     (insn.i_क्रमmat.rs == bc1nez_op))) अणु
			अगर (!init_fp_ctx(current))
				lose_fpu(1);
			reg = insn.i_क्रमmat.rt;
			bit = get_fpr32(&current->thपढ़ो.fpu.fpr[reg], 0) & 0x1;
			अगर (insn.i_क्रमmat.rs == bc1eqz_op)
				bit = !bit;
			own_fpu(1);
			अगर (bit)
				epc = epc + 4 +
					(insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				epc += 8;
			regs->cp0_epc = epc;

			अवरोध;
		पूर्ण अन्यथा अणु

			preempt_disable();
			अगर (is_fpu_owner())
			        fcr31 = पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);
			अन्यथा
				fcr31 = current->thपढ़ो.fpu.fcr31;
			preempt_enable();

			bit = (insn.i_क्रमmat.rt >> 2);
			bit += (bit != 0);
			bit += 23;
			चयन (insn.i_क्रमmat.rt & 3) अणु
			हाल 0: /* bc1f */
			हाल 2: /* bc1fl */
				अगर (~fcr31 & (1 << bit)) अणु
					epc = epc + 4 +
						(insn.i_क्रमmat.simmediate << 2);
					अगर (insn.i_क्रमmat.rt == 2)
						ret = BRANCH_LIKELY_TAKEN;
				पूर्ण अन्यथा
					epc += 8;
				regs->cp0_epc = epc;
				अवरोध;

			हाल 1: /* bc1t */
			हाल 3: /* bc1tl */
				अगर (fcr31 & (1 << bit)) अणु
					epc = epc + 4 +
						(insn.i_क्रमmat.simmediate << 2);
					अगर (insn.i_क्रमmat.rt == 3)
						ret = BRANCH_LIKELY_TAKEN;
				पूर्ण अन्यथा
					epc += 8;
				regs->cp0_epc = epc;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */

#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
	हाल lwc2_op: /* This is bbit0 on Octeon */
		अगर ((regs->regs[insn.i_क्रमmat.rs] & (1ull<<insn.i_क्रमmat.rt))
		     == 0)
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			epc += 8;
		regs->cp0_epc = epc;
		अवरोध;
	हाल ldc2_op: /* This is bbit032 on Octeon */
		अगर ((regs->regs[insn.i_क्रमmat.rs] &
		    (1ull<<(insn.i_क्रमmat.rt+32))) == 0)
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			epc += 8;
		regs->cp0_epc = epc;
		अवरोध;
	हाल swc2_op: /* This is bbit1 on Octeon */
		अगर (regs->regs[insn.i_क्रमmat.rs] & (1ull<<insn.i_क्रमmat.rt))
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			epc += 8;
		regs->cp0_epc = epc;
		अवरोध;
	हाल sdc2_op: /* This is bbit132 on Octeon */
		अगर (regs->regs[insn.i_क्रमmat.rs] &
		    (1ull<<(insn.i_क्रमmat.rt+32)))
			epc = epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			epc += 8;
		regs->cp0_epc = epc;
		अवरोध;
#अन्यथा
	हाल bc6_op:
		/* Only valid क्रम MIPS R6 */
		अगर (!cpu_has_mips_r6)
			जाओ sigill_r6;
		regs->cp0_epc += 8;
		अवरोध;
	हाल balc6_op:
		अगर (!cpu_has_mips_r6)
			जाओ sigill_r6;
		/* Compact branch: BALC */
		regs->regs[31] = epc + 4;
		epc += 4 + (insn.i_क्रमmat.simmediate << 2);
		regs->cp0_epc = epc;
		अवरोध;
	हाल pop66_op:
		अगर (!cpu_has_mips_r6)
			जाओ sigill_r6;
		/* Compact branch: BEQZC || JIC */
		regs->cp0_epc += 8;
		अवरोध;
	हाल pop76_op:
		अगर (!cpu_has_mips_r6)
			जाओ sigill_r6;
		/* Compact branch: BNEZC || JIALC */
		अगर (!insn.i_क्रमmat.rs) अणु
			/* JIALC: set $31/ra */
			regs->regs[31] = epc + 4;
		पूर्ण
		regs->cp0_epc += 8;
		अवरोध;
#पूर्ण_अगर
	हाल pop10_op:
	हाल pop30_op:
		/* Only valid क्रम MIPS R6 */
		अगर (!cpu_has_mips_r6)
			जाओ sigill_r6;
		/*
		 * Compact branches:
		 * bovc, beqc, beqzalc, bnvc, bnec, bnezlac
		 */
		अगर (insn.i_क्रमmat.rt && !insn.i_क्रमmat.rs)
			regs->regs[31] = epc + 4;
		regs->cp0_epc += 8;
		अवरोध;
	पूर्ण

	वापस ret;

sigill_dsp:
	pr_debug("%s: DSP branch but not DSP ASE - sending SIGILL.\n",
		 current->comm);
	क्रमce_sig(संक_अवैध);
	वापस -EFAULT;
sigill_r2r6:
	pr_debug("%s: R2 branch but r2-to-r6 emulator is not present - sending SIGILL.\n",
		 current->comm);
	क्रमce_sig(संक_अवैध);
	वापस -EFAULT;
sigill_r6:
	pr_debug("%s: R6 branch but no MIPSr6 ISA support - sending SIGILL.\n",
		 current->comm);
	क्रमce_sig(संक_अवैध);
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL_GPL(__compute_वापस_epc_क्रम_insn);

पूर्णांक __compute_वापस_epc(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक __user *addr;
	दीर्घ epc;
	जोड़ mips_inकाष्ठाion insn;

	epc = regs->cp0_epc;
	अगर (epc & 3)
		जाओ unaligned;

	/*
	 * Read the inकाष्ठाion
	 */
	addr = (अचिन्हित पूर्णांक __user *) epc;
	अगर (__get_user(insn.word, addr)) अणु
		क्रमce_sig(संक_अंश);
		वापस -EFAULT;
	पूर्ण

	वापस __compute_वापस_epc_क्रम_insn(regs, insn);

unaligned:
	prपूर्णांकk("%s: unaligned epc - sending SIGBUS.\n", current->comm);
	क्रमce_sig(SIGBUS);
	वापस -EFAULT;
पूर्ण

#अगर (defined CONFIG_KPROBES) || (defined CONFIG_UPROBES)

पूर्णांक __insn_is_compact_branch(जोड़ mips_inकाष्ठाion insn)
अणु
	अगर (!cpu_has_mips_r6)
		वापस 0;

	चयन (insn.i_क्रमmat.opcode) अणु
	हाल blezl_op:
	हाल bgtzl_op:
	हाल blez_op:
	हाल bgtz_op:
		/*
		 * blez[l] and bgtz[l] opcodes with non-zero rt
		 * are MIPS R6 compact branches
		 */
		अगर (insn.i_क्रमmat.rt)
			वापस 1;
		अवरोध;
	हाल bc6_op:
	हाल balc6_op:
	हाल pop10_op:
	हाल pop30_op:
	हाल pop66_op:
	हाल pop76_op:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__insn_is_compact_branch);

#पूर्ण_अगर  /* CONFIG_KPROBES || CONFIG_UPROBES */

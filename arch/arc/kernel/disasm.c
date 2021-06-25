<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * several functions that help पूर्णांकerpret ARC inकाष्ठाions
 * used क्रम unaligned accesses, kprobes and kgdb
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/types.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/disयंत्र.h>

#अगर defined(CONFIG_KGDB) || defined(CONFIG_ARC_EMUL_UNALIGNED) || \
	defined(CONFIG_KPROBES)

/* disयंत्र_instr: Analyses inकाष्ठाion at addr, stores
 * findings in *state
 */
व्योम __kprobes disयंत्र_instr(अचिन्हित दीर्घ addr, काष्ठा disयंत्र_state *state,
	पूर्णांक userspace, काष्ठा pt_regs *regs, काष्ठा callee_regs *cregs)
अणु
	पूर्णांक fieldA = 0;
	पूर्णांक fieldC = 0, fieldCisReg = 0;
	uपूर्णांक16_t word1 = 0, word0 = 0;
	पूर्णांक subopcode, is_linked, op_क्रमmat;
	uपूर्णांक16_t *ins_ptr;
	uपूर्णांक16_t ins_buf[4];
	पूर्णांक bytes_not_copied = 0;

	स_रखो(state, 0, माप(काष्ठा disयंत्र_state));

	/* This fetches the upper part of the 32 bit inकाष्ठाion
	 * in both the हालs of Little Endian or Big Endian configurations. */
	अगर (userspace) अणु
		bytes_not_copied = copy_from_user(ins_buf,
						(स्थिर व्योम __user *) addr, 8);
		अगर (bytes_not_copied > 6)
			जाओ fault;
		ins_ptr = ins_buf;
	पूर्ण अन्यथा अणु
		ins_ptr = (uपूर्णांक16_t *) addr;
	पूर्ण

	word1 = *((uपूर्णांक16_t *)addr);

	state->major_opcode = (word1 >> 11) & 0x1F;

	/* Check अगर the inकाष्ठाion is 32 bit or 16 bit inकाष्ठाion */
	अगर (state->major_opcode < 0x0B) अणु
		अगर (bytes_not_copied > 4)
			जाओ fault;
		state->instr_len = 4;
		word0 = *((uपूर्णांक16_t *)(addr+2));
		state->words[0] = (word1 << 16) | word0;
	पूर्ण अन्यथा अणु
		state->instr_len = 2;
		state->words[0] = word1;
	पूर्ण

	/* Read the second word in हाल of limm */
	word1 = *((uपूर्णांक16_t *)(addr + state->instr_len));
	word0 = *((uपूर्णांक16_t *)(addr + state->instr_len + 2));
	state->words[1] = (word1 << 16) | word0;

	चयन (state->major_opcode) अणु
	हाल op_Bcc:
		state->is_branch = 1;

		/* unconditional branch s25, conditional branch s21 */
		fieldA = (IS_BIT(state->words[0], 16)) ?
			FIELD_s25(state->words[0]) :
			FIELD_s21(state->words[0]);

		state->delay_slot = IS_BIT(state->words[0], 5);
		state->target = fieldA + (addr & ~0x3);
		state->flow = direct_jump;
		अवरोध;

	हाल op_BLcc:
		अगर (IS_BIT(state->words[0], 16)) अणु
			/* Branch and Link*/
			/* unconditional branch s25, conditional branch s21 */
			fieldA = (IS_BIT(state->words[0], 17)) ?
				(FIELD_s25(state->words[0]) & ~0x3) :
				FIELD_s21(state->words[0]);

			state->flow = direct_call;
		पूर्ण अन्यथा अणु
			/*Branch On Compare */
			fieldA = FIELD_s9(state->words[0]) & ~0x3;
			state->flow = direct_jump;
		पूर्ण

		state->delay_slot = IS_BIT(state->words[0], 5);
		state->target = fieldA + (addr & ~0x3);
		state->is_branch = 1;
		अवरोध;

	हाल op_LD:  /* LD<zz> a,[b,s9] */
		state->ग_लिखो = 0;
		state->di = BITS(state->words[0], 11, 11);
		अगर (state->di)
			अवरोध;
		state->x = BITS(state->words[0], 6, 6);
		state->zz = BITS(state->words[0], 7, 8);
		state->aa = BITS(state->words[0], 9, 10);
		state->wb_reg = FIELD_B(state->words[0]);
		अगर (state->wb_reg == REG_LIMM) अणु
			state->instr_len += 4;
			state->aa = 0;
			state->src1 = state->words[1];
		पूर्ण अन्यथा अणु
			state->src1 = get_reg(state->wb_reg, regs, cregs);
		पूर्ण
		state->src2 = FIELD_s9(state->words[0]);
		state->dest = FIELD_A(state->words[0]);
		state->pref = (state->dest == REG_LIMM);
		अवरोध;

	हाल op_ST:
		state->ग_लिखो = 1;
		state->di = BITS(state->words[0], 5, 5);
		अगर (state->di)
			अवरोध;
		state->aa = BITS(state->words[0], 3, 4);
		state->zz = BITS(state->words[0], 1, 2);
		state->src1 = FIELD_C(state->words[0]);
		अगर (state->src1 == REG_LIMM) अणु
			state->instr_len += 4;
			state->src1 = state->words[1];
		पूर्ण अन्यथा अणु
			state->src1 = get_reg(state->src1, regs, cregs);
		पूर्ण
		state->wb_reg = FIELD_B(state->words[0]);
		अगर (state->wb_reg == REG_LIMM) अणु
			state->aa = 0;
			state->instr_len += 4;
			state->src2 = state->words[1];
		पूर्ण अन्यथा अणु
			state->src2 = get_reg(state->wb_reg, regs, cregs);
		पूर्ण
		state->src3 = FIELD_s9(state->words[0]);
		अवरोध;

	हाल op_MAJOR_4:
		subopcode = MINOR_OPCODE(state->words[0]);
		चयन (subopcode) अणु
		हाल 32:	/* Jcc */
		हाल 33:	/* Jcc.D */
		हाल 34:	/* JLcc */
		हाल 35:	/* JLcc.D */
			is_linked = 0;

			अगर (subopcode == 33 || subopcode == 35)
				state->delay_slot = 1;

			अगर (subopcode == 34 || subopcode == 35)
				is_linked = 1;

			fieldCisReg = 0;
			op_क्रमmat = BITS(state->words[0], 22, 23);
			अगर (op_क्रमmat == 0 || ((op_क्रमmat == 3) &&
				(!IS_BIT(state->words[0], 5)))) अणु
				fieldC = FIELD_C(state->words[0]);

				अगर (fieldC == REG_LIMM) अणु
					fieldC = state->words[1];
					state->instr_len += 4;
				पूर्ण अन्यथा अणु
					fieldCisReg = 1;
				पूर्ण
			पूर्ण अन्यथा अगर (op_क्रमmat == 1 || ((op_क्रमmat == 3)
				&& (IS_BIT(state->words[0], 5)))) अणु
				fieldC = FIELD_C(state->words[0]);
			पूर्ण अन्यथा  अणु
				/* op_क्रमmat == 2 */
				fieldC = FIELD_s12(state->words[0]);
			पूर्ण

			अगर (!fieldCisReg) अणु
				state->target = fieldC;
				state->flow = is_linked ?
					direct_call : direct_jump;
			पूर्ण अन्यथा अणु
				state->target = get_reg(fieldC, regs, cregs);
				state->flow = is_linked ?
					indirect_call : indirect_jump;
			पूर्ण
			state->is_branch = 1;
			अवरोध;

		हाल 40:	/* LPcc */
			अगर (BITS(state->words[0], 22, 23) == 3) अणु
				/* Conditional LPcc u7 */
				fieldC = FIELD_C(state->words[0]);

				fieldC = fieldC << 1;
				fieldC += (addr & ~0x03);
				state->is_branch = 1;
				state->flow = direct_jump;
				state->target = fieldC;
			पूर्ण
			/* For Unconditional lp, next pc is the fall through
			 * which is updated */
			अवरोध;

		हाल 48 ... 55:	/* LD a,[b,c] */
			state->di = BITS(state->words[0], 15, 15);
			अगर (state->di)
				अवरोध;
			state->x = BITS(state->words[0], 16, 16);
			state->zz = BITS(state->words[0], 17, 18);
			state->aa = BITS(state->words[0], 22, 23);
			state->wb_reg = FIELD_B(state->words[0]);
			अगर (state->wb_reg == REG_LIMM) अणु
				state->instr_len += 4;
				state->src1 = state->words[1];
			पूर्ण अन्यथा अणु
				state->src1 = get_reg(state->wb_reg, regs,
						cregs);
			पूर्ण
			state->src2 = FIELD_C(state->words[0]);
			अगर (state->src2 == REG_LIMM) अणु
				state->instr_len += 4;
				state->src2 = state->words[1];
			पूर्ण अन्यथा अणु
				state->src2 = get_reg(state->src2, regs,
					cregs);
			पूर्ण
			state->dest = FIELD_A(state->words[0]);
			अगर (state->dest == REG_LIMM)
				state->pref = 1;
			अवरोध;

		हाल 10:	/* MOV */
			/* still need to check क्रम limm to extract instr len */
			/* MOV is special हाल because it only takes 2 args */
			चयन (BITS(state->words[0], 22, 23)) अणु
			हाल 0: /* OP a,b,c */
				अगर (FIELD_C(state->words[0]) == REG_LIMM)
					state->instr_len += 4;
				अवरोध;
			हाल 1: /* OP a,b,u6 */
				अवरोध;
			हाल 2: /* OP b,b,s12 */
				अवरोध;
			हाल 3: /* OP.cc b,b,c/u6 */
				अगर ((!IS_BIT(state->words[0], 5)) &&
				    (FIELD_C(state->words[0]) == REG_LIMM))
					state->instr_len += 4;
				अवरोध;
			पूर्ण
			अवरोध;


		शेष:
			/* Not a Load, Jump or Loop inकाष्ठाion */
			/* still need to check क्रम limm to extract instr len */
			चयन (BITS(state->words[0], 22, 23)) अणु
			हाल 0: /* OP a,b,c */
				अगर ((FIELD_B(state->words[0]) == REG_LIMM) ||
				    (FIELD_C(state->words[0]) == REG_LIMM))
					state->instr_len += 4;
				अवरोध;
			हाल 1: /* OP a,b,u6 */
				अवरोध;
			हाल 2: /* OP b,b,s12 */
				अवरोध;
			हाल 3: /* OP.cc b,b,c/u6 */
				अगर ((!IS_BIT(state->words[0], 5)) &&
				   ((FIELD_B(state->words[0]) == REG_LIMM) ||
				    (FIELD_C(state->words[0]) == REG_LIMM)))
					state->instr_len += 4;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	/* 16 Bit Inकाष्ठाions */
	हाल op_LD_ADD: /* LD_S|LDB_S|LDW_S a,[b,c] */
		state->zz = BITS(state->words[0], 3, 4);
		state->src1 = get_reg(FIELD_S_B(state->words[0]), regs, cregs);
		state->src2 = get_reg(FIELD_S_C(state->words[0]), regs, cregs);
		state->dest = FIELD_S_A(state->words[0]);
		अवरोध;

	हाल op_ADD_MOV_CMP:
		/* check क्रम limm, ignore mov_s h,b (== mov_s 0,b) */
		अगर ((BITS(state->words[0], 3, 4) < 3) &&
		    (FIELD_S_H(state->words[0]) == REG_LIMM))
			state->instr_len += 4;
		अवरोध;

	हाल op_S:
		subopcode = BITS(state->words[0], 5, 7);
		चयन (subopcode) अणु
		हाल 0:	/* j_s */
		हाल 1:	/* j_s.d */
		हाल 2:	/* jl_s */
		हाल 3:	/* jl_s.d */
			state->target = get_reg(FIELD_S_B(state->words[0]),
						regs, cregs);
			state->delay_slot = subopcode & 1;
			state->flow = (subopcode >= 2) ?
				direct_call : indirect_jump;
			अवरोध;
		हाल 7:
			चयन (BITS(state->words[0], 8, 10)) अणु
			हाल 4:	/* jeq_s [blink] */
			हाल 5:	/* jne_s [blink] */
			हाल 6:	/* j_s [blink] */
			हाल 7:	/* j_s.d [blink] */
				state->delay_slot = (subopcode == 7);
				state->flow = indirect_jump;
				state->target = get_reg(31, regs, cregs);
			शेष:
				अवरोध;
			पूर्ण
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल op_LD_S:	/* LD_S c, [b, u7] */
		state->src1 = get_reg(FIELD_S_B(state->words[0]), regs, cregs);
		state->src2 = FIELD_S_u7(state->words[0]);
		state->dest = FIELD_S_C(state->words[0]);
		अवरोध;

	हाल op_LDB_S:
	हाल op_STB_S:
		/* no further handling required as byte accesses should not
		 * cause an unaligned access exception */
		state->zz = 1;
		अवरोध;

	हाल op_LDWX_S:	/* LDWX_S c, [b, u6] */
		state->x = 1;
		fallthrough;

	हाल op_LDW_S:	/* LDW_S c, [b, u6] */
		state->zz = 2;
		state->src1 = get_reg(FIELD_S_B(state->words[0]), regs, cregs);
		state->src2 = FIELD_S_u6(state->words[0]);
		state->dest = FIELD_S_C(state->words[0]);
		अवरोध;

	हाल op_ST_S:	/* ST_S c, [b, u7] */
		state->ग_लिखो = 1;
		state->src1 = get_reg(FIELD_S_C(state->words[0]), regs, cregs);
		state->src2 = get_reg(FIELD_S_B(state->words[0]), regs, cregs);
		state->src3 = FIELD_S_u7(state->words[0]);
		अवरोध;

	हाल op_STW_S:	/* STW_S c,[b,u6] */
		state->ग_लिखो = 1;
		state->zz = 2;
		state->src1 = get_reg(FIELD_S_C(state->words[0]), regs, cregs);
		state->src2 = get_reg(FIELD_S_B(state->words[0]), regs, cregs);
		state->src3 = FIELD_S_u6(state->words[0]);
		अवरोध;

	हाल op_SP:	/* LD_S|LDB_S b,[sp,u7], ST_S|STB_S b,[sp,u7] */
		/* note: we are ignoring possibility of:
		 * ADD_S, SUB_S, PUSH_S, POP_S as these should not
		 * cause unaliged exception anyway */
		state->ग_लिखो = BITS(state->words[0], 6, 6);
		state->zz = BITS(state->words[0], 5, 5);
		अगर (state->zz)
			अवरोध;	/* byte accesses should not come here */
		अगर (!state->ग_लिखो) अणु
			state->src1 = get_reg(28, regs, cregs);
			state->src2 = FIELD_S_u7(state->words[0]);
			state->dest = FIELD_S_B(state->words[0]);
		पूर्ण अन्यथा अणु
			state->src1 = get_reg(FIELD_S_B(state->words[0]), regs,
					cregs);
			state->src2 = get_reg(28, regs, cregs);
			state->src3 = FIELD_S_u7(state->words[0]);
		पूर्ण
		अवरोध;

	हाल op_GP:	/* LD_S|LDB_S|LDW_S r0,[gp,s11/s9/s10] */
		/* note: ADD_S r0, gp, s11 is ignored */
		state->zz = BITS(state->words[0], 9, 10);
		state->src1 = get_reg(26, regs, cregs);
		state->src2 = state->zz ? FIELD_S_s10(state->words[0]) :
			FIELD_S_s11(state->words[0]);
		state->dest = 0;
		अवरोध;

	हाल op_Pcl:	/* LD_S b,[pcl,u10] */
		state->src1 = regs->ret & ~3;
		state->src2 = FIELD_S_u10(state->words[0]);
		state->dest = FIELD_S_B(state->words[0]);
		अवरोध;

	हाल op_BR_S:
		state->target = FIELD_S_s8(state->words[0]) + (addr & ~0x03);
		state->flow = direct_jump;
		state->is_branch = 1;
		अवरोध;

	हाल op_B_S:
		fieldA = (BITS(state->words[0], 9, 10) == 3) ?
			FIELD_S_s7(state->words[0]) :
			FIELD_S_s10(state->words[0]);
		state->target = fieldA + (addr & ~0x03);
		state->flow = direct_jump;
		state->is_branch = 1;
		अवरोध;

	हाल op_BL_S:
		state->target = FIELD_S_s13(state->words[0]) + (addr & ~0x03);
		state->flow = direct_call;
		state->is_branch = 1;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (bytes_not_copied <= (8 - state->instr_len))
		वापस;

fault:	state->fault = 1;
पूर्ण

दीर्घ __kprobes get_reg(पूर्णांक reg, काष्ठा pt_regs *regs,
		       काष्ठा callee_regs *cregs)
अणु
	दीर्घ *p;

	अगर (reg <= 12) अणु
		p = &regs->r0;
		वापस p[-reg];
	पूर्ण

	अगर (cregs && (reg <= 25)) अणु
		p = &cregs->r13;
		वापस p[13-reg];
	पूर्ण

	अगर (reg == 26)
		वापस regs->r26;
	अगर (reg == 27)
		वापस regs->fp;
	अगर (reg == 28)
		वापस regs->sp;
	अगर (reg == 31)
		वापस regs->blink;

	वापस 0;
पूर्ण

व्योम __kprobes set_reg(पूर्णांक reg, दीर्घ val, काष्ठा pt_regs *regs,
		काष्ठा callee_regs *cregs)
अणु
	दीर्घ *p;

	चयन (reg) अणु
	हाल 0 ... 12:
		p = &regs->r0;
		p[-reg] = val;
		अवरोध;
	हाल 13 ... 25:
		अगर (cregs) अणु
			p = &cregs->r13;
			p[13-reg] = val;
		पूर्ण
		अवरोध;
	हाल 26:
		regs->r26 = val;
		अवरोध;
	हाल 27:
		regs->fp = val;
		अवरोध;
	हाल 28:
		regs->sp = val;
		अवरोध;
	हाल 31:
		regs->blink = val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Disassembles the insn at @pc and sets @next_pc to next PC (which could be
 * @pc +2/4/6 (ARCompact ISA allows मुक्त पूर्णांकermixing of 16/32 bit insns).
 *
 * If @pc is a branch
 *	-@tgt_अगर_br is set to branch target.
 *	-If branch has delay slot, @next_pc updated with actual next PC.
 */
पूर्णांक __kprobes disयंत्र_next_pc(अचिन्हित दीर्घ pc, काष्ठा pt_regs *regs,
			     काष्ठा callee_regs *cregs,
			     अचिन्हित दीर्घ *next_pc, अचिन्हित दीर्घ *tgt_अगर_br)
अणु
	काष्ठा disयंत्र_state instr;

	स_रखो(&instr, 0, माप(काष्ठा disयंत्र_state));
	disयंत्र_instr(pc, &instr, 0, regs, cregs);

	*next_pc = pc + instr.instr_len;

	/* Inकाष्ठाion with possible two tarमाला_लो branch, jump and loop */
	अगर (instr.is_branch)
		*tgt_अगर_br = instr.target;

	/* For the inकाष्ठाions with delay slots, the fall through is the
	 * inकाष्ठाion following the inकाष्ठाion in delay slot.
	 */
	 अगर (instr.delay_slot) अणु
		काष्ठा disयंत्र_state instr_d;

		disयंत्र_instr(*next_pc, &instr_d, 0, regs, cregs);

		*next_pc += instr_d.instr_len;
	 पूर्ण

	 /* Zero Overhead Loop - end of the loop */
	अगर (!(regs->status32 & STATUS32_L) && (*next_pc == regs->lp_end)
		&& (regs->lp_count > 1)) अणु
		*next_pc = regs->lp_start;
	पूर्ण

	वापस instr.is_branch;
पूर्ण

#पूर्ण_अगर /* CONFIG_KGDB || CONFIG_ARC_EMUL_UNALIGNED || CONFIG_KPROBES */

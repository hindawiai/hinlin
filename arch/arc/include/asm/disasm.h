<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * several functions that help पूर्णांकerpret ARC inकाष्ठाions
 * used क्रम unaligned accesses, kprobes and kgdb
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ARC_DISASM_H__
#घोषणा __ARC_DISASM_H__

क्रमागत अणु
	op_Bcc = 0, op_BLcc = 1, op_LD = 2, op_ST = 3, op_MAJOR_4 = 4,
	op_MAJOR_5 = 5, op_LD_ADD = 12, op_ADD_SUB_SHIFT = 13,
	op_ADD_MOV_CMP = 14, op_S = 15, op_LD_S = 16, op_LDB_S = 17,
	op_LDW_S = 18, op_LDWX_S = 19, op_ST_S = 20, op_STB_S = 21,
	op_STW_S = 22, op_Su5 = 23, op_SP = 24, op_GP = 25,
	op_Pcl = 26, op_MOV_S = 27, op_ADD_CMP = 28, op_BR_S = 29,
	op_B_S = 30, op_BL_S = 31
पूर्ण;

क्रमागत flow अणु
	noflow,
	direct_jump,
	direct_call,
	indirect_jump,
	indirect_call,
	invalid_instr
पूर्ण;

#घोषणा IS_BIT(word, n)		((word) & (1<<n))
#घोषणा BITS(word, s, e)	(((word) >> (s)) & (~((-2) << ((e) - (s)))))

#घोषणा MAJOR_OPCODE(word)	(BITS((word), 27, 31))
#घोषणा MINOR_OPCODE(word)	(BITS((word), 16, 21))
#घोषणा FIELD_A(word)		(BITS((word), 0, 5))
#घोषणा FIELD_B(word)		((BITS((word), 12, 14)<<3) | \
				(BITS((word), 24, 26)))
#घोषणा FIELD_C(word)		(BITS((word), 6, 11))
#घोषणा FIELD_u6(word)		FIELDC(word)
#घोषणा FIELD_s12(word)		sign_extend(((BITS((word), 0, 5) << 6) | \
					BITS((word), 6, 11)), 12)

/* note that क्रम BL/BRcc these two macro's need another AND statement to mask
 * out bit 1 (make the result a multiple of 4) */
#घोषणा FIELD_s9(word)		sign_extend(((BITS(word, 15, 15) << 8) | \
					BITS(word, 16, 23)), 9)
#घोषणा FIELD_s21(word)		sign_extend(((BITS(word, 6, 15) << 11) | \
					(BITS(word, 17, 26) << 1)), 12)
#घोषणा FIELD_s25(word)		sign_extend(((BITS(word, 0, 3) << 21) | \
					(BITS(word, 6, 15) << 11) | \
					(BITS(word, 17, 26) << 1)), 12)

/* note: these operate on 16 bits! */
#घोषणा FIELD_S_A(word)		((BITS((word), 2, 2)<<3) | BITS((word), 0, 2))
#घोषणा FIELD_S_B(word)		((BITS((word), 10, 10)<<3) | \
				BITS((word), 8, 10))
#घोषणा FIELD_S_C(word)		((BITS((word), 7, 7)<<3) | BITS((word), 5, 7))
#घोषणा FIELD_S_H(word)		((BITS((word), 0, 2)<<3) | BITS((word), 5, 8))
#घोषणा FIELD_S_u5(word)	(BITS((word), 0, 4))
#घोषणा FIELD_S_u6(word)	(BITS((word), 0, 4) << 1)
#घोषणा FIELD_S_u7(word)	(BITS((word), 0, 4) << 2)
#घोषणा FIELD_S_u10(word)	(BITS((word), 0, 7) << 2)
#घोषणा FIELD_S_s7(word)	sign_extend(BITS((word), 0, 5) << 1, 9)
#घोषणा FIELD_S_s8(word)	sign_extend(BITS((word), 0, 7) << 1, 9)
#घोषणा FIELD_S_s9(word)	sign_extend(BITS((word), 0, 8), 9)
#घोषणा FIELD_S_s10(word)	sign_extend(BITS((word), 0, 8) << 1, 10)
#घोषणा FIELD_S_s11(word)	sign_extend(BITS((word), 0, 8) << 2, 11)
#घोषणा FIELD_S_s13(word)	sign_extend(BITS((word), 0, 10) << 2, 13)

#घोषणा STATUS32_L		0x00000100
#घोषणा REG_LIMM		62

काष्ठा disयंत्र_state अणु
	/* generic info */
	अचिन्हित दीर्घ words[2];
	पूर्णांक instr_len;
	पूर्णांक major_opcode;
	/* info क्रम branch/jump */
	पूर्णांक is_branch;
	पूर्णांक target;
	पूर्णांक delay_slot;
	क्रमागत flow flow;
	/* info क्रम load/store */
	पूर्णांक src1, src2, src3, dest, wb_reg;
	पूर्णांक zz, aa, x, pref, di;
	पूर्णांक fault, ग_लिखो;
पूर्ण;

अटल अंतरभूत पूर्णांक sign_extend(पूर्णांक value, पूर्णांक bits)
अणु
	अगर (IS_BIT(value, (bits - 1)))
		value |= (0xffffffff << bits);

	वापस value;
पूर्ण

अटल अंतरभूत पूर्णांक is_लघु_instr(अचिन्हित दीर्घ addr)
अणु
	uपूर्णांक16_t word = *((uपूर्णांक16_t *)addr);
	पूर्णांक opcode = (word >> 11) & 0x1F;
	वापस (opcode >= 0x0B);
पूर्ण

व्योम disयंत्र_instr(अचिन्हित दीर्घ addr, काष्ठा disयंत्र_state *state,
	पूर्णांक userspace, काष्ठा pt_regs *regs, काष्ठा callee_regs *cregs);
पूर्णांक disयंत्र_next_pc(अचिन्हित दीर्घ pc, काष्ठा pt_regs *regs, काष्ठा callee_regs
	*cregs, अचिन्हित दीर्घ *fall_thru, अचिन्हित दीर्घ *target);
दीर्घ get_reg(पूर्णांक reg, काष्ठा pt_regs *regs, काष्ठा callee_regs *cregs);
व्योम set_reg(पूर्णांक reg, दीर्घ val, काष्ठा pt_regs *regs,
		काष्ठा callee_regs *cregs);

#पूर्ण_अगर	/* __ARC_DISASM_H__ */

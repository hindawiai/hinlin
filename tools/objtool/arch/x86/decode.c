<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#घोषणा unlikely(cond) (cond)
#समावेश <यंत्र/insn.h>
#समावेश "../../../arch/x86/lib/inat.c"
#समावेश "../../../arch/x86/lib/insn.c"

#घोषणा CONFIG_64BIT 1
#समावेश <यंत्र/nops.h>

#समावेश <यंत्र/orc_types.h>
#समावेश <objtool/check.h>
#समावेश <objtool/elf.h>
#समावेश <objtool/arch.h>
#समावेश <objtool/warn.h>
#समावेश <objtool/endianness.h>
#समावेश <arch/elf.h>

अटल पूर्णांक is_x86_64(स्थिर काष्ठा elf *elf)
अणु
	चयन (elf->ehdr.e_machine) अणु
	हाल EM_X86_64:
		वापस 1;
	हाल EM_386:
		वापस 0;
	शेष:
		WARN("unexpected ELF machine type %d", elf->ehdr.e_machine);
		वापस -1;
	पूर्ण
पूर्ण

bool arch_callee_saved_reg(अचिन्हित अक्षर reg)
अणु
	चयन (reg) अणु
	हाल CFI_BP:
	हाल CFI_BX:
	हाल CFI_R12:
	हाल CFI_R13:
	हाल CFI_R14:
	हाल CFI_R15:
		वापस true;

	हाल CFI_AX:
	हाल CFI_CX:
	हाल CFI_DX:
	हाल CFI_SI:
	हाल CFI_DI:
	हाल CFI_SP:
	हाल CFI_R8:
	हाल CFI_R9:
	हाल CFI_R10:
	हाल CFI_R11:
	हाल CFI_RA:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ arch_dest_reloc_offset(पूर्णांक addend)
अणु
	वापस addend + 4;
पूर्ण

अचिन्हित दीर्घ arch_jump_destination(काष्ठा inकाष्ठाion *insn)
अणु
	वापस insn->offset + insn->len + insn->immediate;
पूर्ण

#घोषणा ADD_OP(op) \
	अगर (!(op = सुस्मृति(1, माप(*op)))) \
		वापस -1; \
	अन्यथा क्रम (list_add_tail(&op->list, ops_list); op; op = शून्य)

/*
 * Helpers to decode ModRM/SIB:
 *
 * r/m| AX  CX  DX  BX |  SP |  BP |  SI  DI |
 *    | R8  R9 R10 R11 | R12 | R13 | R14 R15 |
 * Mod+----------------+-----+-----+---------+
 * 00 |    [r/m]       |[SIB]|[IP+]|  [r/m]  |
 * 01 |  [r/m + d8]    |[S+d]|   [r/m + d8]  |
 * 10 |  [r/m + d32]   |[S+D]|   [r/m + d32] |
 * 11 |                   r/ m               |
 */

#घोषणा mod_is_mem()	(modrm_mod != 3)
#घोषणा mod_is_reg()	(modrm_mod == 3)

#घोषणा is_RIP()   ((modrm_rm & 7) == CFI_BP && modrm_mod == 0)
#घोषणा have_SIB() ((modrm_rm & 7) == CFI_SP && mod_is_mem())

#घोषणा rm_is(reg) (have_SIB() ? \
		    sib_base == (reg) && sib_index == CFI_SP : \
		    modrm_rm == (reg))

#घोषणा rm_is_mem(reg)	(mod_is_mem() && !is_RIP() && rm_is(reg))
#घोषणा rm_is_reg(reg)	(mod_is_reg() && modrm_rm == (reg))

पूर्णांक arch_decode_inकाष्ठाion(स्थिर काष्ठा elf *elf, स्थिर काष्ठा section *sec,
			    अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक maxlen,
			    अचिन्हित पूर्णांक *len, क्रमागत insn_type *type,
			    अचिन्हित दीर्घ *immediate,
			    काष्ठा list_head *ops_list)
अणु
	काष्ठा insn insn;
	पूर्णांक x86_64, ret;
	अचिन्हित अक्षर op1, op2,
		      rex = 0, rex_b = 0, rex_r = 0, rex_w = 0, rex_x = 0,
		      modrm = 0, modrm_mod = 0, modrm_rm = 0, modrm_reg = 0,
		      sib = 0, /* sib_scale = 0, */ sib_index = 0, sib_base = 0;
	काष्ठा stack_op *op = शून्य;
	काष्ठा symbol *sym;
	u64 imm;

	x86_64 = is_x86_64(elf);
	अगर (x86_64 == -1)
		वापस -1;

	ret = insn_decode(&insn, sec->data->d_buf + offset, maxlen,
			  x86_64 ? INSN_MODE_64 : INSN_MODE_32);
	अगर (ret < 0) अणु
		WARN("can't decode instruction at %s:0x%lx", sec->name, offset);
		वापस -1;
	पूर्ण

	*len = insn.length;
	*type = INSN_OTHER;

	अगर (insn.vex_prefix.nbytes)
		वापस 0;

	op1 = insn.opcode.bytes[0];
	op2 = insn.opcode.bytes[1];

	अगर (insn.rex_prefix.nbytes) अणु
		rex = insn.rex_prefix.bytes[0];
		rex_w = X86_REX_W(rex) >> 3;
		rex_r = X86_REX_R(rex) >> 2;
		rex_x = X86_REX_X(rex) >> 1;
		rex_b = X86_REX_B(rex);
	पूर्ण

	अगर (insn.modrm.nbytes) अणु
		modrm = insn.modrm.bytes[0];
		modrm_mod = X86_MODRM_MOD(modrm);
		modrm_reg = X86_MODRM_REG(modrm) + 8*rex_r;
		modrm_rm  = X86_MODRM_RM(modrm)  + 8*rex_b;
	पूर्ण

	अगर (insn.sib.nbytes) अणु
		sib = insn.sib.bytes[0];
		/* sib_scale = X86_SIB_SCALE(sib); */
		sib_index = X86_SIB_INDEX(sib) + 8*rex_x;
		sib_base  = X86_SIB_BASE(sib)  + 8*rex_b;
	पूर्ण

	चयन (op1) अणु

	हाल 0x1:
	हाल 0x29:
		अगर (rex_w && rm_is_reg(CFI_SP)) अणु

			/* add/sub reg, %rsp */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_ADD;
				op->src.reg = modrm_reg;
				op->dest.type = OP_DEST_REG;
				op->dest.reg = CFI_SP;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 0x50 ... 0x57:

		/* push reg */
		ADD_OP(op) अणु
			op->src.type = OP_SRC_REG;
			op->src.reg = (op1 & 0x7) + 8*rex_b;
			op->dest.type = OP_DEST_PUSH;
		पूर्ण

		अवरोध;

	हाल 0x58 ... 0x5f:

		/* pop reg */
		ADD_OP(op) अणु
			op->src.type = OP_SRC_POP;
			op->dest.type = OP_DEST_REG;
			op->dest.reg = (op1 & 0x7) + 8*rex_b;
		पूर्ण

		अवरोध;

	हाल 0x68:
	हाल 0x6a:
		/* push immediate */
		ADD_OP(op) अणु
			op->src.type = OP_SRC_CONST;
			op->dest.type = OP_DEST_PUSH;
		पूर्ण
		अवरोध;

	हाल 0x70 ... 0x7f:
		*type = INSN_JUMP_CONDITIONAL;
		अवरोध;

	हाल 0x80 ... 0x83:
		/*
		 * 1000 00sw : mod OP r/m : immediate
		 *
		 * s - sign extend immediate
		 * w - imm8 / imm32
		 *
		 * OP: 000 ADD    100 AND
		 *     001 OR     101 SUB
		 *     010 ADC    110 XOR
		 *     011 SBB    111 CMP
		 */

		/* 64bit only */
		अगर (!rex_w)
			अवरोध;

		/* %rsp target only */
		अगर (!rm_is_reg(CFI_SP))
			अवरोध;

		imm = insn.immediate.value;
		अगर (op1 & 2) अणु /* sign extend */
			अगर (op1 & 1) अणु /* imm32 */
				imm <<= 32;
				imm = (s64)imm >> 32;
			पूर्ण अन्यथा अणु /* imm8 */
				imm <<= 56;
				imm = (s64)imm >> 56;
			पूर्ण
		पूर्ण

		चयन (modrm_reg & 7) अणु
		हाल 5:
			imm = -imm;
			/* fallthrough */
		हाल 0:
			/* add/sub imm, %rsp */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_ADD;
				op->src.reg = CFI_SP;
				op->src.offset = imm;
				op->dest.type = OP_DEST_REG;
				op->dest.reg = CFI_SP;
			पूर्ण
			अवरोध;

		हाल 4:
			/* and imm, %rsp */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_AND;
				op->src.reg = CFI_SP;
				op->src.offset = insn.immediate.value;
				op->dest.type = OP_DEST_REG;
				op->dest.reg = CFI_SP;
			पूर्ण
			अवरोध;

		शेष:
			/* WARN ? */
			अवरोध;
		पूर्ण

		अवरोध;

	हाल 0x89:
		अगर (!rex_w)
			अवरोध;

		अगर (modrm_reg == CFI_SP) अणु

			अगर (mod_is_reg()) अणु
				/* mov %rsp, reg */
				ADD_OP(op) अणु
					op->src.type = OP_SRC_REG;
					op->src.reg = CFI_SP;
					op->dest.type = OP_DEST_REG;
					op->dest.reg = modrm_rm;
				पूर्ण
				अवरोध;

			पूर्ण अन्यथा अणु
				/* skip RIP relative displacement */
				अगर (is_RIP())
					अवरोध;

				/* skip nontrivial SIB */
				अगर (have_SIB()) अणु
					modrm_rm = sib_base;
					अगर (sib_index != CFI_SP)
						अवरोध;
				पूर्ण

				/* mov %rsp, disp(%reg) */
				ADD_OP(op) अणु
					op->src.type = OP_SRC_REG;
					op->src.reg = CFI_SP;
					op->dest.type = OP_DEST_REG_INसूचीECT;
					op->dest.reg = modrm_rm;
					op->dest.offset = insn.displacement.value;
				पूर्ण
				अवरोध;
			पूर्ण

			अवरोध;
		पूर्ण

		अगर (rm_is_reg(CFI_SP)) अणु

			/* mov reg, %rsp */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_REG;
				op->src.reg = modrm_reg;
				op->dest.type = OP_DEST_REG;
				op->dest.reg = CFI_SP;
			पूर्ण
			अवरोध;
		पूर्ण

		/* fallthrough */
	हाल 0x88:
		अगर (!rex_w)
			अवरोध;

		अगर (rm_is_mem(CFI_BP)) अणु

			/* mov reg, disp(%rbp) */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_REG;
				op->src.reg = modrm_reg;
				op->dest.type = OP_DEST_REG_INसूचीECT;
				op->dest.reg = CFI_BP;
				op->dest.offset = insn.displacement.value;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (rm_is_mem(CFI_SP)) अणु

			/* mov reg, disp(%rsp) */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_REG;
				op->src.reg = modrm_reg;
				op->dest.type = OP_DEST_REG_INसूचीECT;
				op->dest.reg = CFI_SP;
				op->dest.offset = insn.displacement.value;
			पूर्ण
			अवरोध;
		पूर्ण

		अवरोध;

	हाल 0x8b:
		अगर (!rex_w)
			अवरोध;

		अगर (rm_is_mem(CFI_BP)) अणु

			/* mov disp(%rbp), reg */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_REG_INसूचीECT;
				op->src.reg = CFI_BP;
				op->src.offset = insn.displacement.value;
				op->dest.type = OP_DEST_REG;
				op->dest.reg = modrm_reg;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (rm_is_mem(CFI_SP)) अणु

			/* mov disp(%rsp), reg */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_REG_INसूचीECT;
				op->src.reg = CFI_SP;
				op->src.offset = insn.displacement.value;
				op->dest.type = OP_DEST_REG;
				op->dest.reg = modrm_reg;
			पूर्ण
			अवरोध;
		पूर्ण

		अवरोध;

	हाल 0x8d:
		अगर (mod_is_reg()) अणु
			WARN("invalid LEA encoding at %s:0x%lx", sec->name, offset);
			अवरोध;
		पूर्ण

		/* skip non 64bit ops */
		अगर (!rex_w)
			अवरोध;

		/* skip RIP relative displacement */
		अगर (is_RIP())
			अवरोध;

		/* skip nontrivial SIB */
		अगर (have_SIB()) अणु
			modrm_rm = sib_base;
			अगर (sib_index != CFI_SP)
				अवरोध;
		पूर्ण

		/* lea disp(%src), %dst */
		ADD_OP(op) अणु
			op->src.offset = insn.displacement.value;
			अगर (!op->src.offset) अणु
				/* lea (%src), %dst */
				op->src.type = OP_SRC_REG;
			पूर्ण अन्यथा अणु
				/* lea disp(%src), %dst */
				op->src.type = OP_SRC_ADD;
			पूर्ण
			op->src.reg = modrm_rm;
			op->dest.type = OP_DEST_REG;
			op->dest.reg = modrm_reg;
		पूर्ण
		अवरोध;

	हाल 0x8f:
		/* pop to mem */
		ADD_OP(op) अणु
			op->src.type = OP_SRC_POP;
			op->dest.type = OP_DEST_MEM;
		पूर्ण
		अवरोध;

	हाल 0x90:
		*type = INSN_NOP;
		अवरोध;

	हाल 0x9c:
		/* pushf */
		ADD_OP(op) अणु
			op->src.type = OP_SRC_CONST;
			op->dest.type = OP_DEST_PUSHF;
		पूर्ण
		अवरोध;

	हाल 0x9d:
		/* popf */
		ADD_OP(op) अणु
			op->src.type = OP_SRC_POPF;
			op->dest.type = OP_DEST_MEM;
		पूर्ण
		अवरोध;

	हाल 0x0f:

		अगर (op2 == 0x01) अणु

			अगर (modrm == 0xca)
				*type = INSN_CLAC;
			अन्यथा अगर (modrm == 0xcb)
				*type = INSN_STAC;

		पूर्ण अन्यथा अगर (op2 >= 0x80 && op2 <= 0x8f) अणु

			*type = INSN_JUMP_CONDITIONAL;

		पूर्ण अन्यथा अगर (op2 == 0x05 || op2 == 0x07 || op2 == 0x34 ||
			   op2 == 0x35) अणु

			/* sysenter, sysret */
			*type = INSN_CONTEXT_SWITCH;

		पूर्ण अन्यथा अगर (op2 == 0x0b || op2 == 0xb9) अणु

			/* ud2 */
			*type = INSN_BUG;

		पूर्ण अन्यथा अगर (op2 == 0x0d || op2 == 0x1f) अणु

			/* nopl/nopw */
			*type = INSN_NOP;

		पूर्ण अन्यथा अगर (op2 == 0xa0 || op2 == 0xa8) अणु

			/* push fs/gs */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_CONST;
				op->dest.type = OP_DEST_PUSH;
			पूर्ण

		पूर्ण अन्यथा अगर (op2 == 0xa1 || op2 == 0xa9) अणु

			/* pop fs/gs */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_POP;
				op->dest.type = OP_DEST_MEM;
			पूर्ण
		पूर्ण

		अवरोध;

	हाल 0xc9:
		/*
		 * leave
		 *
		 * equivalent to:
		 * mov bp, sp
		 * pop bp
		 */
		ADD_OP(op) अणु
			op->src.type = OP_SRC_REG;
			op->src.reg = CFI_BP;
			op->dest.type = OP_DEST_REG;
			op->dest.reg = CFI_SP;
		पूर्ण
		ADD_OP(op) अणु
			op->src.type = OP_SRC_POP;
			op->dest.type = OP_DEST_REG;
			op->dest.reg = CFI_BP;
		पूर्ण
		अवरोध;

	हाल 0xe3:
		/* jecxz/jrcxz */
		*type = INSN_JUMP_CONDITIONAL;
		अवरोध;

	हाल 0xe9:
	हाल 0xeb:
		*type = INSN_JUMP_UNCONDITIONAL;
		अवरोध;

	हाल 0xc2:
	हाल 0xc3:
		*type = INSN_RETURN;
		अवरोध;

	हाल 0xcf: /* iret */
		/*
		 * Handle sync_core(), which has an IRET to self.
		 * All other IRET are in STT_NONE entry code.
		 */
		sym = find_symbol_containing(sec, offset);
		अगर (sym && sym->type == STT_FUNC) अणु
			ADD_OP(op) अणु
				/* add $40, %rsp */
				op->src.type = OP_SRC_ADD;
				op->src.reg = CFI_SP;
				op->src.offset = 5*8;
				op->dest.type = OP_DEST_REG;
				op->dest.reg = CFI_SP;
			पूर्ण
			अवरोध;
		पूर्ण

		/* fallthrough */

	हाल 0xca: /* retf */
	हाल 0xcb: /* retf */
		*type = INSN_CONTEXT_SWITCH;
		अवरोध;

	हाल 0xe8:
		*type = INSN_CALL;
		/*
		 * For the impact on the stack, a CALL behaves like
		 * a PUSH of an immediate value (the वापस address).
		 */
		ADD_OP(op) अणु
			op->src.type = OP_SRC_CONST;
			op->dest.type = OP_DEST_PUSH;
		पूर्ण
		अवरोध;

	हाल 0xfc:
		*type = INSN_CLD;
		अवरोध;

	हाल 0xfd:
		*type = INSN_STD;
		अवरोध;

	हाल 0xff:
		अगर (modrm_reg == 2 || modrm_reg == 3)

			*type = INSN_CALL_DYNAMIC;

		अन्यथा अगर (modrm_reg == 4)

			*type = INSN_JUMP_DYNAMIC;

		अन्यथा अगर (modrm_reg == 5)

			/* jmpf */
			*type = INSN_CONTEXT_SWITCH;

		अन्यथा अगर (modrm_reg == 6) अणु

			/* push from mem */
			ADD_OP(op) अणु
				op->src.type = OP_SRC_CONST;
				op->dest.type = OP_DEST_PUSH;
			पूर्ण
		पूर्ण

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	*immediate = insn.immediate.nbytes ? insn.immediate.value : 0;

	वापस 0;
पूर्ण

व्योम arch_initial_func_cfi_state(काष्ठा cfi_init_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CFI_NUM_REGS; i++) अणु
		state->regs[i].base = CFI_UNDEFINED;
		state->regs[i].offset = 0;
	पूर्ण

	/* initial CFA (call frame address) */
	state->cfa.base = CFI_SP;
	state->cfa.offset = 8;

	/* initial RA (वापस address) */
	state->regs[CFI_RA].base = CFI_CFA;
	state->regs[CFI_RA].offset = -8;
पूर्ण

स्थिर अक्षर *arch_nop_insn(पूर्णांक len)
अणु
	अटल स्थिर अक्षर nops[5][5] = अणु
		अणु BYTES_NOP1 पूर्ण,
		अणु BYTES_NOP2 पूर्ण,
		अणु BYTES_NOP3 पूर्ण,
		अणु BYTES_NOP4 पूर्ण,
		अणु BYTES_NOP5 पूर्ण,
	पूर्ण;

	अगर (len < 1 || len > 5) अणु
		WARN("invalid NOP size: %d\n", len);
		वापस शून्य;
	पूर्ण

	वापस nops[len-1];
पूर्ण

/* यंत्र/alternative.h ? */

#घोषणा ALTINSTR_FLAG_INV	(1 << 15)
#घोषणा ALT_NOT(feat)		((feat) | ALTINSTR_FLAG_INV)

काष्ठा alt_instr अणु
	s32 instr_offset;	/* original inकाष्ठाion */
	s32 repl_offset;	/* offset to replacement inकाष्ठाion */
	u16 cpuid;		/* cpuid bit set क्रम replacement */
	u8  inम_माप;		/* length of original inकाष्ठाion */
	u8  replacementlen;	/* length of new inकाष्ठाion */
पूर्ण __packed;

अटल पूर्णांक elf_add_alternative(काष्ठा elf *elf,
			       काष्ठा inकाष्ठाion *orig, काष्ठा symbol *sym,
			       पूर्णांक cpuid, u8 orig_len, u8 repl_len)
अणु
	स्थिर पूर्णांक size = माप(काष्ठा alt_instr);
	काष्ठा alt_instr *alt;
	काष्ठा section *sec;
	Elf_Scn *s;

	sec = find_section_by_name(elf, ".altinstructions");
	अगर (!sec) अणु
		sec = elf_create_section(elf, ".altinstructions",
					 SHF_WRITE, size, 0);

		अगर (!sec) अणु
			WARN_ELF("elf_create_section");
			वापस -1;
		पूर्ण
	पूर्ण

	s = elf_माला_लोcn(elf->elf, sec->idx);
	अगर (!s) अणु
		WARN_ELF("elf_getscn");
		वापस -1;
	पूर्ण

	sec->data = elf_newdata(s);
	अगर (!sec->data) अणु
		WARN_ELF("elf_newdata");
		वापस -1;
	पूर्ण

	sec->data->d_size = size;
	sec->data->d_align = 1;

	alt = sec->data->d_buf = दो_स्मृति(size);
	अगर (!sec->data->d_buf) अणु
		लिखो_त्रुटि("malloc");
		वापस -1;
	पूर्ण
	स_रखो(sec->data->d_buf, 0, size);

	अगर (elf_add_reloc_to_insn(elf, sec, sec->sh.sh_size,
				  R_X86_64_PC32, orig->sec, orig->offset)) अणु
		WARN("elf_create_reloc: alt_instr::instr_offset");
		वापस -1;
	पूर्ण

	अगर (elf_add_reloc(elf, sec, sec->sh.sh_size + 4,
			  R_X86_64_PC32, sym, 0)) अणु
		WARN("elf_create_reloc: alt_instr::repl_offset");
		वापस -1;
	पूर्ण

	alt->cpuid = bswap_अगर_needed(cpuid);
	alt->inम_माप = orig_len;
	alt->replacementlen = repl_len;

	sec->sh.sh_size += size;
	sec->changed = true;

	वापस 0;
पूर्ण

#घोषणा X86_FEATURE_RETPOLINE                ( 7*32+12)

पूर्णांक arch_reग_लिखो_retpolines(काष्ठा objtool_file *file)
अणु
	काष्ठा inकाष्ठाion *insn;
	काष्ठा reloc *reloc;
	काष्ठा symbol *sym;
	अक्षर name[32] = "";

	list_क्रम_each_entry(insn, &file->retpoline_call_list, call_node) अणु

		अगर (insn->type != INSN_JUMP_DYNAMIC &&
		    insn->type != INSN_CALL_DYNAMIC)
			जारी;

		अगर (!म_भेद(insn->sec->name, ".text.__x86.indirect_thunk"))
			जारी;

		reloc = insn->reloc;

		प्र_लिखो(name, "__x86_indirect_alt_%s_%s",
			insn->type == INSN_JUMP_DYNAMIC ? "jmp" : "call",
			reloc->sym->name + 21);

		sym = find_symbol_by_name(file->elf, name);
		अगर (!sym) अणु
			sym = elf_create_undef_symbol(file->elf, name);
			अगर (!sym) अणु
				WARN("elf_create_undef_symbol");
				वापस -1;
			पूर्ण
		पूर्ण

		अगर (elf_add_alternative(file->elf, insn, sym,
					ALT_NOT(X86_FEATURE_RETPOLINE), 5, 5)) अणु
			WARN("elf_add_alternative");
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक arch_decode_hपूर्णांक_reg(काष्ठा inकाष्ठाion *insn, u8 sp_reg)
अणु
	काष्ठा cfi_reg *cfa = &insn->cfi.cfa;

	चयन (sp_reg) अणु
	हाल ORC_REG_UNDEFINED:
		cfa->base = CFI_UNDEFINED;
		अवरोध;
	हाल ORC_REG_SP:
		cfa->base = CFI_SP;
		अवरोध;
	हाल ORC_REG_BP:
		cfa->base = CFI_BP;
		अवरोध;
	हाल ORC_REG_SP_INसूचीECT:
		cfa->base = CFI_SP_INसूचीECT;
		अवरोध;
	हाल ORC_REG_R10:
		cfa->base = CFI_R10;
		अवरोध;
	हाल ORC_REG_R13:
		cfa->base = CFI_R13;
		अवरोध;
	हाल ORC_REG_DI:
		cfa->base = CFI_DI;
		अवरोध;
	हाल ORC_REG_DX:
		cfa->base = CFI_DX;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

bool arch_is_retpoline(काष्ठा symbol *sym)
अणु
	वापस !म_भेदन(sym->name, "__x86_indirect_", 15);
पूर्ण

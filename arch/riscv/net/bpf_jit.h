<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common functionality क्रम RV32 and RV64 BPF JIT compilers
 *
 * Copyright (c) 2019 Bjथघrn Tथघpel <bjorn.topel@gmail.com>
 *
 */

#अगर_अघोषित _BPF_JIT_H
#घोषणा _BPF_JIT_H

#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <यंत्र/cacheflush.h>

अटल अंतरभूत bool rvc_enabled(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_RISCV_ISA_C);
पूर्ण

क्रमागत अणु
	RV_REG_ZERO =	0,	/* The स्थिरant value 0 */
	RV_REG_RA =	1,	/* Return address */
	RV_REG_SP =	2,	/* Stack poपूर्णांकer */
	RV_REG_GP =	3,	/* Global poपूर्णांकer */
	RV_REG_TP =	4,	/* Thपढ़ो poपूर्णांकer */
	RV_REG_T0 =	5,	/* Temporaries */
	RV_REG_T1 =	6,
	RV_REG_T2 =	7,
	RV_REG_FP =	8,	/* Saved रेजिस्टर/frame poपूर्णांकer */
	RV_REG_S1 =	9,	/* Saved रेजिस्टर */
	RV_REG_A0 =	10,	/* Function argument/वापस values */
	RV_REG_A1 =	11,	/* Function arguments */
	RV_REG_A2 =	12,
	RV_REG_A3 =	13,
	RV_REG_A4 =	14,
	RV_REG_A5 =	15,
	RV_REG_A6 =	16,
	RV_REG_A7 =	17,
	RV_REG_S2 =	18,	/* Saved रेजिस्टरs */
	RV_REG_S3 =	19,
	RV_REG_S4 =	20,
	RV_REG_S5 =	21,
	RV_REG_S6 =	22,
	RV_REG_S7 =	23,
	RV_REG_S8 =	24,
	RV_REG_S9 =	25,
	RV_REG_S10 =	26,
	RV_REG_S11 =	27,
	RV_REG_T3 =	28,	/* Temporaries */
	RV_REG_T4 =	29,
	RV_REG_T5 =	30,
	RV_REG_T6 =	31,
पूर्ण;

अटल अंतरभूत bool is_creg(u8 reg)
अणु
	वापस (1 << reg) & (BIT(RV_REG_FP) |
			     BIT(RV_REG_S1) |
			     BIT(RV_REG_A0) |
			     BIT(RV_REG_A1) |
			     BIT(RV_REG_A2) |
			     BIT(RV_REG_A3) |
			     BIT(RV_REG_A4) |
			     BIT(RV_REG_A5));
पूर्ण

काष्ठा rv_jit_context अणु
	काष्ठा bpf_prog *prog;
	u16 *insns;		/* RV insns */
	पूर्णांक ninsns;
	पूर्णांक epilogue_offset;
	पूर्णांक *offset;		/* BPF to RV */
	अचिन्हित दीर्घ flags;
	पूर्णांक stack_size;
पूर्ण;

/* Convert from ninsns to bytes. */
अटल अंतरभूत पूर्णांक ninsns_rvoff(पूर्णांक ninsns)
अणु
	वापस ninsns << 1;
पूर्ण

काष्ठा rv_jit_data अणु
	काष्ठा bpf_binary_header *header;
	u8 *image;
	काष्ठा rv_jit_context ctx;
पूर्ण;

अटल अंतरभूत व्योम bpf_fill_ill_insns(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	स_रखो(area, 0, size);
पूर्ण

अटल अंतरभूत व्योम bpf_flush_icache(व्योम *start, व्योम *end)
अणु
	flush_icache_range((अचिन्हित दीर्घ)start, (अचिन्हित दीर्घ)end);
पूर्ण

/* Emit a 4-byte riscv inकाष्ठाion. */
अटल अंतरभूत व्योम emit(स्थिर u32 insn, काष्ठा rv_jit_context *ctx)
अणु
	अगर (ctx->insns) अणु
		ctx->insns[ctx->ninsns] = insn;
		ctx->insns[ctx->ninsns + 1] = (insn >> 16);
	पूर्ण

	ctx->ninsns += 2;
पूर्ण

/* Emit a 2-byte riscv compressed inकाष्ठाion. */
अटल अंतरभूत व्योम emitc(स्थिर u16 insn, काष्ठा rv_jit_context *ctx)
अणु
	BUILD_BUG_ON(!rvc_enabled());

	अगर (ctx->insns)
		ctx->insns[ctx->ninsns] = insn;

	ctx->ninsns++;
पूर्ण

अटल अंतरभूत पूर्णांक epilogue_offset(काष्ठा rv_jit_context *ctx)
अणु
	पूर्णांक to = ctx->epilogue_offset, from = ctx->ninsns;

	वापस ninsns_rvoff(to - from);
पूर्ण

/* Return -1 or inverted cond. */
अटल अंतरभूत पूर्णांक invert_bpf_cond(u8 cond)
अणु
	चयन (cond) अणु
	हाल BPF_JEQ:
		वापस BPF_JNE;
	हाल BPF_JGT:
		वापस BPF_JLE;
	हाल BPF_JLT:
		वापस BPF_JGE;
	हाल BPF_JGE:
		वापस BPF_JLT;
	हाल BPF_JLE:
		वापस BPF_JGT;
	हाल BPF_JNE:
		वापस BPF_JEQ;
	हाल BPF_JSGT:
		वापस BPF_JSLE;
	हाल BPF_JSLT:
		वापस BPF_JSGE;
	हाल BPF_JSGE:
		वापस BPF_JSLT;
	हाल BPF_JSLE:
		वापस BPF_JSGT;
	पूर्ण
	वापस -1;
पूर्ण

अटल अंतरभूत bool is_6b_पूर्णांक(दीर्घ val)
अणु
	वापस -(1L << 5) <= val && val < (1L << 5);
पूर्ण

अटल अंतरभूत bool is_7b_uपूर्णांक(अचिन्हित दीर्घ val)
अणु
	वापस val < (1UL << 7);
पूर्ण

अटल अंतरभूत bool is_8b_uपूर्णांक(अचिन्हित दीर्घ val)
अणु
	वापस val < (1UL << 8);
पूर्ण

अटल अंतरभूत bool is_9b_uपूर्णांक(अचिन्हित दीर्घ val)
अणु
	वापस val < (1UL << 9);
पूर्ण

अटल अंतरभूत bool is_10b_पूर्णांक(दीर्घ val)
अणु
	वापस -(1L << 9) <= val && val < (1L << 9);
पूर्ण

अटल अंतरभूत bool is_10b_uपूर्णांक(अचिन्हित दीर्घ val)
अणु
	वापस val < (1UL << 10);
पूर्ण

अटल अंतरभूत bool is_12b_पूर्णांक(दीर्घ val)
अणु
	वापस -(1L << 11) <= val && val < (1L << 11);
पूर्ण

अटल अंतरभूत पूर्णांक is_12b_check(पूर्णांक off, पूर्णांक insn)
अणु
	अगर (!is_12b_पूर्णांक(off)) अणु
		pr_err("bpf-jit: insn=%d 12b < offset=%d not supported yet!\n",
		       insn, (पूर्णांक)off);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool is_13b_पूर्णांक(दीर्घ val)
अणु
	वापस -(1L << 12) <= val && val < (1L << 12);
पूर्ण

अटल अंतरभूत bool is_21b_पूर्णांक(दीर्घ val)
अणु
	वापस -(1L << 20) <= val && val < (1L << 20);
पूर्ण

अटल अंतरभूत पूर्णांक rv_offset(पूर्णांक insn, पूर्णांक off, काष्ठा rv_jit_context *ctx)
अणु
	पूर्णांक from, to;

	off++; /* BPF branch is from PC+1, RV is from PC */
	from = (insn > 0) ? ctx->offset[insn - 1] : 0;
	to = (insn + off > 0) ? ctx->offset[insn + off - 1] : 0;
	वापस ninsns_rvoff(to - from);
पूर्ण

/* Inकाष्ठाion क्रमmats. */

अटल अंतरभूत u32 rv_r_insn(u8 funct7, u8 rs2, u8 rs1, u8 funct3, u8 rd,
			    u8 opcode)
अणु
	वापस (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) |
		(rd << 7) | opcode;
पूर्ण

अटल अंतरभूत u32 rv_i_insn(u16 imm11_0, u8 rs1, u8 funct3, u8 rd, u8 opcode)
अणु
	वापस (imm11_0 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) |
		opcode;
पूर्ण

अटल अंतरभूत u32 rv_s_insn(u16 imm11_0, u8 rs2, u8 rs1, u8 funct3, u8 opcode)
अणु
	u8 imm11_5 = imm11_0 >> 5, imm4_0 = imm11_0 & 0x1f;

	वापस (imm11_5 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) |
		(imm4_0 << 7) | opcode;
पूर्ण

अटल अंतरभूत u32 rv_b_insn(u16 imm12_1, u8 rs2, u8 rs1, u8 funct3, u8 opcode)
अणु
	u8 imm12 = ((imm12_1 & 0x800) >> 5) | ((imm12_1 & 0x3f0) >> 4);
	u8 imm4_1 = ((imm12_1 & 0xf) << 1) | ((imm12_1 & 0x400) >> 10);

	वापस (imm12 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) |
		(imm4_1 << 7) | opcode;
पूर्ण

अटल अंतरभूत u32 rv_u_insn(u32 imm31_12, u8 rd, u8 opcode)
अणु
	वापस (imm31_12 << 12) | (rd << 7) | opcode;
पूर्ण

अटल अंतरभूत u32 rv_j_insn(u32 imm20_1, u8 rd, u8 opcode)
अणु
	u32 imm;

	imm = (imm20_1 & 0x80000) | ((imm20_1 & 0x3ff) << 9) |
		((imm20_1 & 0x400) >> 2) | ((imm20_1 & 0x7f800) >> 11);

	वापस (imm << 12) | (rd << 7) | opcode;
पूर्ण

अटल अंतरभूत u32 rv_amo_insn(u8 funct5, u8 aq, u8 rl, u8 rs2, u8 rs1,
			      u8 funct3, u8 rd, u8 opcode)
अणु
	u8 funct7 = (funct5 << 2) | (aq << 1) | rl;

	वापस rv_r_insn(funct7, rs2, rs1, funct3, rd, opcode);
पूर्ण

/* RISC-V compressed inकाष्ठाion क्रमmats. */

अटल अंतरभूत u16 rv_cr_insn(u8 funct4, u8 rd, u8 rs2, u8 op)
अणु
	वापस (funct4 << 12) | (rd << 7) | (rs2 << 2) | op;
पूर्ण

अटल अंतरभूत u16 rv_ci_insn(u8 funct3, u32 imm6, u8 rd, u8 op)
अणु
	u32 imm;

	imm = ((imm6 & 0x20) << 7) | ((imm6 & 0x1f) << 2);
	वापस (funct3 << 13) | (rd << 7) | op | imm;
पूर्ण

अटल अंतरभूत u16 rv_css_insn(u8 funct3, u32 uimm, u8 rs2, u8 op)
अणु
	वापस (funct3 << 13) | (uimm << 7) | (rs2 << 2) | op;
पूर्ण

अटल अंतरभूत u16 rv_ciw_insn(u8 funct3, u32 uimm, u8 rd, u8 op)
अणु
	वापस (funct3 << 13) | (uimm << 5) | ((rd & 0x7) << 2) | op;
पूर्ण

अटल अंतरभूत u16 rv_cl_insn(u8 funct3, u32 imm_hi, u8 rs1, u32 imm_lo, u8 rd,
			     u8 op)
अणु
	वापस (funct3 << 13) | (imm_hi << 10) | ((rs1 & 0x7) << 7) |
		(imm_lo << 5) | ((rd & 0x7) << 2) | op;
पूर्ण

अटल अंतरभूत u16 rv_cs_insn(u8 funct3, u32 imm_hi, u8 rs1, u32 imm_lo, u8 rs2,
			     u8 op)
अणु
	वापस (funct3 << 13) | (imm_hi << 10) | ((rs1 & 0x7) << 7) |
		(imm_lo << 5) | ((rs2 & 0x7) << 2) | op;
पूर्ण

अटल अंतरभूत u16 rv_ca_insn(u8 funct6, u8 rd, u8 funct2, u8 rs2, u8 op)
अणु
	वापस (funct6 << 10) | ((rd & 0x7) << 7) | (funct2 << 5) |
		((rs2 & 0x7) << 2) | op;
पूर्ण

अटल अंतरभूत u16 rv_cb_insn(u8 funct3, u32 imm6, u8 funct2, u8 rd, u8 op)
अणु
	u32 imm;

	imm = ((imm6 & 0x20) << 7) | ((imm6 & 0x1f) << 2);
	वापस (funct3 << 13) | (funct2 << 10) | ((rd & 0x7) << 7) | op | imm;
पूर्ण

/* Inकाष्ठाions shared by both RV32 and RV64. */

अटल अंतरभूत u32 rv_addi(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 0, rd, 0x13);
पूर्ण

अटल अंतरभूत u32 rv_andi(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 7, rd, 0x13);
पूर्ण

अटल अंतरभूत u32 rv_ori(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 6, rd, 0x13);
पूर्ण

अटल अंतरभूत u32 rv_xori(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 4, rd, 0x13);
पूर्ण

अटल अंतरभूत u32 rv_slli(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 1, rd, 0x13);
पूर्ण

अटल अंतरभूत u32 rv_srli(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 5, rd, 0x13);
पूर्ण

अटल अंतरभूत u32 rv_srai(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(0x400 | imm11_0, rs1, 5, rd, 0x13);
पूर्ण

अटल अंतरभूत u32 rv_lui(u8 rd, u32 imm31_12)
अणु
	वापस rv_u_insn(imm31_12, rd, 0x37);
पूर्ण

अटल अंतरभूत u32 rv_auipc(u8 rd, u32 imm31_12)
अणु
	वापस rv_u_insn(imm31_12, rd, 0x17);
पूर्ण

अटल अंतरभूत u32 rv_add(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 0, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_sub(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0x20, rs2, rs1, 0, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_sltu(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 3, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_and(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 7, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_or(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 6, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_xor(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 4, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_sll(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 1, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_srl(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 5, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_sra(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0x20, rs2, rs1, 5, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_mul(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(1, rs2, rs1, 0, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_mulhu(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(1, rs2, rs1, 3, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_भागu(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(1, rs2, rs1, 5, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_remu(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(1, rs2, rs1, 7, rd, 0x33);
पूर्ण

अटल अंतरभूत u32 rv_jal(u8 rd, u32 imm20_1)
अणु
	वापस rv_j_insn(imm20_1, rd, 0x6f);
पूर्ण

अटल अंतरभूत u32 rv_jalr(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 0, rd, 0x67);
पूर्ण

अटल अंतरभूत u32 rv_beq(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_b_insn(imm12_1, rs2, rs1, 0, 0x63);
पूर्ण

अटल अंतरभूत u32 rv_bne(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_b_insn(imm12_1, rs2, rs1, 1, 0x63);
पूर्ण

अटल अंतरभूत u32 rv_bltu(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_b_insn(imm12_1, rs2, rs1, 6, 0x63);
पूर्ण

अटल अंतरभूत u32 rv_bgtu(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_bltu(rs2, rs1, imm12_1);
पूर्ण

अटल अंतरभूत u32 rv_bgeu(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_b_insn(imm12_1, rs2, rs1, 7, 0x63);
पूर्ण

अटल अंतरभूत u32 rv_bleu(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_bgeu(rs2, rs1, imm12_1);
पूर्ण

अटल अंतरभूत u32 rv_blt(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_b_insn(imm12_1, rs2, rs1, 4, 0x63);
पूर्ण

अटल अंतरभूत u32 rv_bgt(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_blt(rs2, rs1, imm12_1);
पूर्ण

अटल अंतरभूत u32 rv_bge(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_b_insn(imm12_1, rs2, rs1, 5, 0x63);
पूर्ण

अटल अंतरभूत u32 rv_ble(u8 rs1, u8 rs2, u16 imm12_1)
अणु
	वापस rv_bge(rs2, rs1, imm12_1);
पूर्ण

अटल अंतरभूत u32 rv_lw(u8 rd, u16 imm11_0, u8 rs1)
अणु
	वापस rv_i_insn(imm11_0, rs1, 2, rd, 0x03);
पूर्ण

अटल अंतरभूत u32 rv_lbu(u8 rd, u16 imm11_0, u8 rs1)
अणु
	वापस rv_i_insn(imm11_0, rs1, 4, rd, 0x03);
पूर्ण

अटल अंतरभूत u32 rv_lhu(u8 rd, u16 imm11_0, u8 rs1)
अणु
	वापस rv_i_insn(imm11_0, rs1, 5, rd, 0x03);
पूर्ण

अटल अंतरभूत u32 rv_sb(u8 rs1, u16 imm11_0, u8 rs2)
अणु
	वापस rv_s_insn(imm11_0, rs2, rs1, 0, 0x23);
पूर्ण

अटल अंतरभूत u32 rv_sh(u8 rs1, u16 imm11_0, u8 rs2)
अणु
	वापस rv_s_insn(imm11_0, rs2, rs1, 1, 0x23);
पूर्ण

अटल अंतरभूत u32 rv_sw(u8 rs1, u16 imm11_0, u8 rs2)
अणु
	वापस rv_s_insn(imm11_0, rs2, rs1, 2, 0x23);
पूर्ण

अटल अंतरभूत u32 rv_amoadd_w(u8 rd, u8 rs2, u8 rs1, u8 aq, u8 rl)
अणु
	वापस rv_amo_insn(0, aq, rl, rs2, rs1, 2, rd, 0x2f);
पूर्ण

/* RVC instrutions. */

अटल अंतरभूत u16 rvc_addi4spn(u8 rd, u32 imm10)
अणु
	u32 imm;

	imm = ((imm10 & 0x30) << 2) | ((imm10 & 0x3c0) >> 4) |
		((imm10 & 0x4) >> 1) | ((imm10 & 0x8) >> 3);
	वापस rv_ciw_insn(0x0, imm, rd, 0x0);
पूर्ण

अटल अंतरभूत u16 rvc_lw(u8 rd, u32 imm7, u8 rs1)
अणु
	u32 imm_hi, imm_lo;

	imm_hi = (imm7 & 0x38) >> 3;
	imm_lo = ((imm7 & 0x4) >> 1) | ((imm7 & 0x40) >> 6);
	वापस rv_cl_insn(0x2, imm_hi, rs1, imm_lo, rd, 0x0);
पूर्ण

अटल अंतरभूत u16 rvc_sw(u8 rs1, u32 imm7, u8 rs2)
अणु
	u32 imm_hi, imm_lo;

	imm_hi = (imm7 & 0x38) >> 3;
	imm_lo = ((imm7 & 0x4) >> 1) | ((imm7 & 0x40) >> 6);
	वापस rv_cs_insn(0x6, imm_hi, rs1, imm_lo, rs2, 0x0);
पूर्ण

अटल अंतरभूत u16 rvc_addi(u8 rd, u32 imm6)
अणु
	वापस rv_ci_insn(0, imm6, rd, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_li(u8 rd, u32 imm6)
अणु
	वापस rv_ci_insn(0x2, imm6, rd, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_addi16sp(u32 imm10)
अणु
	u32 imm;

	imm = ((imm10 & 0x200) >> 4) | (imm10 & 0x10) | ((imm10 & 0x40) >> 3) |
		((imm10 & 0x180) >> 6) | ((imm10 & 0x20) >> 5);
	वापस rv_ci_insn(0x3, imm, RV_REG_SP, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_lui(u8 rd, u32 imm6)
अणु
	वापस rv_ci_insn(0x3, imm6, rd, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_srli(u8 rd, u32 imm6)
अणु
	वापस rv_cb_insn(0x4, imm6, 0, rd, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_srai(u8 rd, u32 imm6)
अणु
	वापस rv_cb_insn(0x4, imm6, 0x1, rd, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_andi(u8 rd, u32 imm6)
अणु
	वापस rv_cb_insn(0x4, imm6, 0x2, rd, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_sub(u8 rd, u8 rs)
अणु
	वापस rv_ca_insn(0x23, rd, 0, rs, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_xor(u8 rd, u8 rs)
अणु
	वापस rv_ca_insn(0x23, rd, 0x1, rs, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_or(u8 rd, u8 rs)
अणु
	वापस rv_ca_insn(0x23, rd, 0x2, rs, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_and(u8 rd, u8 rs)
अणु
	वापस rv_ca_insn(0x23, rd, 0x3, rs, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_slli(u8 rd, u32 imm6)
अणु
	वापस rv_ci_insn(0, imm6, rd, 0x2);
पूर्ण

अटल अंतरभूत u16 rvc_lwsp(u8 rd, u32 imm8)
अणु
	u32 imm;

	imm = ((imm8 & 0xc0) >> 6) | (imm8 & 0x3c);
	वापस rv_ci_insn(0x2, imm, rd, 0x2);
पूर्ण

अटल अंतरभूत u16 rvc_jr(u8 rs1)
अणु
	वापस rv_cr_insn(0x8, rs1, RV_REG_ZERO, 0x2);
पूर्ण

अटल अंतरभूत u16 rvc_mv(u8 rd, u8 rs)
अणु
	वापस rv_cr_insn(0x8, rd, rs, 0x2);
पूर्ण

अटल अंतरभूत u16 rvc_jalr(u8 rs1)
अणु
	वापस rv_cr_insn(0x9, rs1, RV_REG_ZERO, 0x2);
पूर्ण

अटल अंतरभूत u16 rvc_add(u8 rd, u8 rs)
अणु
	वापस rv_cr_insn(0x9, rd, rs, 0x2);
पूर्ण

अटल अंतरभूत u16 rvc_swsp(u32 imm8, u8 rs2)
अणु
	u32 imm;

	imm = (imm8 & 0x3c) | ((imm8 & 0xc0) >> 6);
	वापस rv_css_insn(0x6, imm, rs2, 0x2);
पूर्ण

/*
 * RV64-only inकाष्ठाions.
 *
 * These inकाष्ठाions are not available on RV32.  Wrap them below a #अगर to
 * ensure that the RV32 JIT करोesn't emit any of these inकाष्ठाions.
 */

#अगर __riscv_xlen == 64

अटल अंतरभूत u32 rv_addiw(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 0, rd, 0x1b);
पूर्ण

अटल अंतरभूत u32 rv_slliw(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 1, rd, 0x1b);
पूर्ण

अटल अंतरभूत u32 rv_srliw(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(imm11_0, rs1, 5, rd, 0x1b);
पूर्ण

अटल अंतरभूत u32 rv_sraiw(u8 rd, u8 rs1, u16 imm11_0)
अणु
	वापस rv_i_insn(0x400 | imm11_0, rs1, 5, rd, 0x1b);
पूर्ण

अटल अंतरभूत u32 rv_addw(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 0, rd, 0x3b);
पूर्ण

अटल अंतरभूत u32 rv_subw(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0x20, rs2, rs1, 0, rd, 0x3b);
पूर्ण

अटल अंतरभूत u32 rv_sllw(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 1, rd, 0x3b);
पूर्ण

अटल अंतरभूत u32 rv_srlw(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0, rs2, rs1, 5, rd, 0x3b);
पूर्ण

अटल अंतरभूत u32 rv_sraw(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(0x20, rs2, rs1, 5, rd, 0x3b);
पूर्ण

अटल अंतरभूत u32 rv_mulw(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(1, rs2, rs1, 0, rd, 0x3b);
पूर्ण

अटल अंतरभूत u32 rv_भागuw(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(1, rs2, rs1, 5, rd, 0x3b);
पूर्ण

अटल अंतरभूत u32 rv_remuw(u8 rd, u8 rs1, u8 rs2)
अणु
	वापस rv_r_insn(1, rs2, rs1, 7, rd, 0x3b);
पूर्ण

अटल अंतरभूत u32 rv_ld(u8 rd, u16 imm11_0, u8 rs1)
अणु
	वापस rv_i_insn(imm11_0, rs1, 3, rd, 0x03);
पूर्ण

अटल अंतरभूत u32 rv_lwu(u8 rd, u16 imm11_0, u8 rs1)
अणु
	वापस rv_i_insn(imm11_0, rs1, 6, rd, 0x03);
पूर्ण

अटल अंतरभूत u32 rv_sd(u8 rs1, u16 imm11_0, u8 rs2)
अणु
	वापस rv_s_insn(imm11_0, rs2, rs1, 3, 0x23);
पूर्ण

अटल अंतरभूत u32 rv_amoadd_d(u8 rd, u8 rs2, u8 rs1, u8 aq, u8 rl)
अणु
	वापस rv_amo_insn(0, aq, rl, rs2, rs1, 3, rd, 0x2f);
पूर्ण

/* RV64-only RVC inकाष्ठाions. */

अटल अंतरभूत u16 rvc_ld(u8 rd, u32 imm8, u8 rs1)
अणु
	u32 imm_hi, imm_lo;

	imm_hi = (imm8 & 0x38) >> 3;
	imm_lo = (imm8 & 0xc0) >> 6;
	वापस rv_cl_insn(0x3, imm_hi, rs1, imm_lo, rd, 0x0);
पूर्ण

अटल अंतरभूत u16 rvc_sd(u8 rs1, u32 imm8, u8 rs2)
अणु
	u32 imm_hi, imm_lo;

	imm_hi = (imm8 & 0x38) >> 3;
	imm_lo = (imm8 & 0xc0) >> 6;
	वापस rv_cs_insn(0x7, imm_hi, rs1, imm_lo, rs2, 0x0);
पूर्ण

अटल अंतरभूत u16 rvc_subw(u8 rd, u8 rs)
अणु
	वापस rv_ca_insn(0x27, rd, 0, rs, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_addiw(u8 rd, u32 imm6)
अणु
	वापस rv_ci_insn(0x1, imm6, rd, 0x1);
पूर्ण

अटल अंतरभूत u16 rvc_ldsp(u8 rd, u32 imm9)
अणु
	u32 imm;

	imm = ((imm9 & 0x1c0) >> 6) | (imm9 & 0x38);
	वापस rv_ci_insn(0x3, imm, rd, 0x2);
पूर्ण

अटल अंतरभूत u16 rvc_sdsp(u32 imm9, u8 rs2)
अणु
	u32 imm;

	imm = (imm9 & 0x38) | ((imm9 & 0x1c0) >> 6);
	वापस rv_css_insn(0x7, imm, rs2, 0x2);
पूर्ण

#पूर्ण_अगर /* __riscv_xlen == 64 */

/* Helper functions that emit RVC inकाष्ठाions when possible. */

अटल अंतरभूत व्योम emit_jalr(u8 rd, u8 rs, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rd == RV_REG_RA && rs && !imm)
		emitc(rvc_jalr(rs), ctx);
	अन्यथा अगर (rvc_enabled() && !rd && rs && !imm)
		emitc(rvc_jr(rs), ctx);
	अन्यथा
		emit(rv_jalr(rd, rs, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_mv(u8 rd, u8 rs, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rd && rs)
		emitc(rvc_mv(rd, rs), ctx);
	अन्यथा
		emit(rv_addi(rd, rs, 0), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_add(u8 rd, u8 rs1, u8 rs2, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rd && rd == rs1 && rs2)
		emitc(rvc_add(rd, rs2), ctx);
	अन्यथा
		emit(rv_add(rd, rs1, rs2), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_addi(u8 rd, u8 rs, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rd == RV_REG_SP && rd == rs && is_10b_पूर्णांक(imm) && imm && !(imm & 0xf))
		emitc(rvc_addi16sp(imm), ctx);
	अन्यथा अगर (rvc_enabled() && is_creg(rd) && rs == RV_REG_SP && is_10b_uपूर्णांक(imm) &&
		 !(imm & 0x3) && imm)
		emitc(rvc_addi4spn(rd, imm), ctx);
	अन्यथा अगर (rvc_enabled() && rd && rd == rs && imm && is_6b_पूर्णांक(imm))
		emitc(rvc_addi(rd, imm), ctx);
	अन्यथा
		emit(rv_addi(rd, rs, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_li(u8 rd, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rd && is_6b_पूर्णांक(imm))
		emitc(rvc_li(rd, imm), ctx);
	अन्यथा
		emit(rv_addi(rd, RV_REG_ZERO, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_lui(u8 rd, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rd && rd != RV_REG_SP && is_6b_पूर्णांक(imm) && imm)
		emitc(rvc_lui(rd, imm), ctx);
	अन्यथा
		emit(rv_lui(rd, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_slli(u8 rd, u8 rs, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rd && rd == rs && imm && (u32)imm < __riscv_xlen)
		emitc(rvc_slli(rd, imm), ctx);
	अन्यथा
		emit(rv_slli(rd, rs, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_andi(u8 rd, u8 rs, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && is_creg(rd) && rd == rs && is_6b_पूर्णांक(imm))
		emitc(rvc_andi(rd, imm), ctx);
	अन्यथा
		emit(rv_andi(rd, rs, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_srli(u8 rd, u8 rs, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && is_creg(rd) && rd == rs && imm && (u32)imm < __riscv_xlen)
		emitc(rvc_srli(rd, imm), ctx);
	अन्यथा
		emit(rv_srli(rd, rs, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_srai(u8 rd, u8 rs, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && is_creg(rd) && rd == rs && imm && (u32)imm < __riscv_xlen)
		emitc(rvc_srai(rd, imm), ctx);
	अन्यथा
		emit(rv_srai(rd, rs, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_sub(u8 rd, u8 rs1, u8 rs2, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && is_creg(rd) && rd == rs1 && is_creg(rs2))
		emitc(rvc_sub(rd, rs2), ctx);
	अन्यथा
		emit(rv_sub(rd, rs1, rs2), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_or(u8 rd, u8 rs1, u8 rs2, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && is_creg(rd) && rd == rs1 && is_creg(rs2))
		emitc(rvc_or(rd, rs2), ctx);
	अन्यथा
		emit(rv_or(rd, rs1, rs2), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_and(u8 rd, u8 rs1, u8 rs2, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && is_creg(rd) && rd == rs1 && is_creg(rs2))
		emitc(rvc_and(rd, rs2), ctx);
	अन्यथा
		emit(rv_and(rd, rs1, rs2), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_xor(u8 rd, u8 rs1, u8 rs2, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && is_creg(rd) && rd == rs1 && is_creg(rs2))
		emitc(rvc_xor(rd, rs2), ctx);
	अन्यथा
		emit(rv_xor(rd, rs1, rs2), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_lw(u8 rd, s32 off, u8 rs1, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rs1 == RV_REG_SP && rd && is_8b_uपूर्णांक(off) && !(off & 0x3))
		emitc(rvc_lwsp(rd, off), ctx);
	अन्यथा अगर (rvc_enabled() && is_creg(rd) && is_creg(rs1) && is_7b_uपूर्णांक(off) && !(off & 0x3))
		emitc(rvc_lw(rd, off, rs1), ctx);
	अन्यथा
		emit(rv_lw(rd, off, rs1), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_sw(u8 rs1, s32 off, u8 rs2, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rs1 == RV_REG_SP && is_8b_uपूर्णांक(off) && !(off & 0x3))
		emitc(rvc_swsp(off, rs2), ctx);
	अन्यथा अगर (rvc_enabled() && is_creg(rs1) && is_creg(rs2) && is_7b_uपूर्णांक(off) && !(off & 0x3))
		emitc(rvc_sw(rs1, off, rs2), ctx);
	अन्यथा
		emit(rv_sw(rs1, off, rs2), ctx);
पूर्ण

/* RV64-only helper functions. */
#अगर __riscv_xlen == 64

अटल अंतरभूत व्योम emit_addiw(u8 rd, u8 rs, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rd && rd == rs && is_6b_पूर्णांक(imm))
		emitc(rvc_addiw(rd, imm), ctx);
	अन्यथा
		emit(rv_addiw(rd, rs, imm), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_ld(u8 rd, s32 off, u8 rs1, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rs1 == RV_REG_SP && rd && is_9b_uपूर्णांक(off) && !(off & 0x7))
		emitc(rvc_ldsp(rd, off), ctx);
	अन्यथा अगर (rvc_enabled() && is_creg(rd) && is_creg(rs1) && is_8b_uपूर्णांक(off) && !(off & 0x7))
		emitc(rvc_ld(rd, off, rs1), ctx);
	अन्यथा
		emit(rv_ld(rd, off, rs1), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_sd(u8 rs1, s32 off, u8 rs2, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && rs1 == RV_REG_SP && is_9b_uपूर्णांक(off) && !(off & 0x7))
		emitc(rvc_sdsp(off, rs2), ctx);
	अन्यथा अगर (rvc_enabled() && is_creg(rs1) && is_creg(rs2) && is_8b_uपूर्णांक(off) && !(off & 0x7))
		emitc(rvc_sd(rs1, off, rs2), ctx);
	अन्यथा
		emit(rv_sd(rs1, off, rs2), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_subw(u8 rd, u8 rs1, u8 rs2, काष्ठा rv_jit_context *ctx)
अणु
	अगर (rvc_enabled() && is_creg(rd) && rd == rs1 && is_creg(rs2))
		emitc(rvc_subw(rd, rs2), ctx);
	अन्यथा
		emit(rv_subw(rd, rs1, rs2), ctx);
पूर्ण

#पूर्ण_अगर /* __riscv_xlen == 64 */

व्योम bpf_jit_build_prologue(काष्ठा rv_jit_context *ctx);
व्योम bpf_jit_build_epilogue(काष्ठा rv_jit_context *ctx);

पूर्णांक bpf_jit_emit_insn(स्थिर काष्ठा bpf_insn *insn, काष्ठा rv_jit_context *ctx,
		      bool extra_pass);

#पूर्ण_अगर /* _BPF_JIT_H */

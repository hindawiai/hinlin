<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * A small micro-assembler. It is पूर्णांकentionally kept simple, करोes only
 * support a subset of inकाष्ठाions, and करोes not try to hide pipeline
 * effects like branch delay slots.
 *
 * Copyright (C) 2004, 2005, 2006, 2008	 Thiemo Seufer
 * Copyright (C) 2005, 2007  Maciej W. Rozycki
 * Copyright (C) 2006  Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2012, 2013  MIPS Technologies, Inc.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/uयंत्र.h>

#घोषणा RS_MASK		0x1f
#घोषणा RS_SH		21
#घोषणा RT_MASK		0x1f
#घोषणा RT_SH		16
#घोषणा SCIMM_MASK	0xfffff
#घोषणा SCIMM_SH	6

/* This macro sets the non-variable bits of an inकाष्ठाion. */
#घोषणा M(a, b, c, d, e, f)					\
	((a) << OP_SH						\
	 | (b) << RS_SH						\
	 | (c) << RT_SH						\
	 | (d) << RD_SH						\
	 | (e) << RE_SH						\
	 | (f) << FUNC_SH)

/* This macro sets the non-variable bits of an R6 inकाष्ठाion. */
#घोषणा M6(a, b, c, d, e)					\
	((a) << OP_SH						\
	 | (b) << RS_SH						\
	 | (c) << RT_SH						\
	 | (d) << SIMM9_SH					\
	 | (e) << FUNC_SH)

#समावेश "uasm.c"

अटल स्थिर काष्ठा insn insn_table[insn_invalid] = अणु
	[insn_addiu]	= अणुM(addiu_op, 0, 0, 0, 0, 0), RS | RT | SIMMपूर्ण,
	[insn_addu]	= अणुM(spec_op, 0, 0, 0, 0, addu_op), RS | RT | RDपूर्ण,
	[insn_and]	= अणुM(spec_op, 0, 0, 0, 0, and_op), RS | RT | RDपूर्ण,
	[insn_andi]	= अणुM(andi_op, 0, 0, 0, 0, 0), RS | RT | UIMMपूर्ण,
	[insn_bbit0]	= अणुM(lwc2_op, 0, 0, 0, 0, 0), RS | RT | BIMMपूर्ण,
	[insn_bbit1]	= अणुM(swc2_op, 0, 0, 0, 0, 0), RS | RT | BIMMपूर्ण,
	[insn_beq]	= अणुM(beq_op, 0, 0, 0, 0, 0), RS | RT | BIMMपूर्ण,
	[insn_beql]	= अणुM(beql_op, 0, 0, 0, 0, 0), RS | RT | BIMMपूर्ण,
	[insn_bgez]	= अणुM(bcond_op, 0, bgez_op, 0, 0, 0), RS | BIMMपूर्ण,
	[insn_bgezl]	= अणुM(bcond_op, 0, bgezl_op, 0, 0, 0), RS | BIMMपूर्ण,
	[insn_bgtz]	= अणुM(bgtz_op, 0, 0, 0, 0, 0), RS | BIMMपूर्ण,
	[insn_blez]	= अणुM(blez_op, 0, 0, 0, 0, 0), RS | BIMMपूर्ण,
	[insn_bltz]	= अणुM(bcond_op, 0, bltz_op, 0, 0, 0), RS | BIMMपूर्ण,
	[insn_bltzl]	= अणुM(bcond_op, 0, bltzl_op, 0, 0, 0), RS | BIMMपूर्ण,
	[insn_bne]	= अणुM(bne_op, 0, 0, 0, 0, 0), RS | RT | BIMMपूर्ण,
	[insn_अवरोध]	= अणुM(spec_op, 0, 0, 0, 0, अवरोध_op), SCIMMपूर्ण,
#अगर_अघोषित CONFIG_CPU_MIPSR6
	[insn_cache]	= अणुM(cache_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
#अन्यथा
	[insn_cache]	= अणुM6(spec3_op, 0, 0, 0, cache6_op),  RS | RT | SIMM9पूर्ण,
#पूर्ण_अगर
	[insn_cfc1]	= अणुM(cop1_op, cfc_op, 0, 0, 0, 0), RT | RDपूर्ण,
	[insn_cfcmsa]	= अणुM(msa_op, 0, msa_cfc_op, 0, 0, msa_elm_op), RD | REपूर्ण,
	[insn_ctc1]	= अणुM(cop1_op, ctc_op, 0, 0, 0, 0), RT | RDपूर्ण,
	[insn_ctcmsa]	= अणुM(msa_op, 0, msa_ctc_op, 0, 0, msa_elm_op), RD | REपूर्ण,
	[insn_daddiu]	= अणुM(daddiu_op, 0, 0, 0, 0, 0), RS | RT | SIMMपूर्ण,
	[insn_daddu]	= अणुM(spec_op, 0, 0, 0, 0, daddu_op), RS | RT | RDपूर्ण,
	[insn_dभागu]	= अणुM(spec_op, 0, 0, 0, 0, dभागu_op), RS | RTपूर्ण,
	[insn_dभागu_r6]	= अणुM(spec_op, 0, 0, 0, dभागu_dभागu6_op, dभागu_op),
				RS | RT | RDपूर्ण,
	[insn_di]	= अणुM(cop0_op, mfmc0_op, 0, 12, 0, 0), RTपूर्ण,
	[insn_dins]	= अणुM(spec3_op, 0, 0, 0, 0, dins_op), RS | RT | RD | REपूर्ण,
	[insn_dinsm]	= अणुM(spec3_op, 0, 0, 0, 0, dinsm_op), RS | RT | RD | REपूर्ण,
	[insn_dinsu]	= अणुM(spec3_op, 0, 0, 0, 0, dinsu_op), RS | RT | RD | REपूर्ण,
	[insn_भागu]	= अणुM(spec_op, 0, 0, 0, 0, भागu_op), RS | RTपूर्ण,
	[insn_भागu_r6]	= अणुM(spec_op, 0, 0, 0, भागu_भागu6_op, भागu_op),
				RS | RT | RDपूर्ण,
	[insn_dmfc0]	= अणुM(cop0_op, dmfc_op, 0, 0, 0, 0), RT | RD | SETपूर्ण,
	[insn_dmodu]	= अणुM(spec_op, 0, 0, 0, dभागu_dmodu_op, dभागu_op),
				RS | RT | RDपूर्ण,
	[insn_dmtc0]	= अणुM(cop0_op, dmtc_op, 0, 0, 0, 0), RT | RD | SETपूर्ण,
	[insn_dmultu]	= अणुM(spec_op, 0, 0, 0, 0, dmultu_op), RS | RTपूर्ण,
	[insn_dmulu]	= अणुM(spec_op, 0, 0, 0, dmult_dmul_op, dmultu_op),
				RS | RT | RDपूर्ण,
	[insn_drotr]	= अणुM(spec_op, 1, 0, 0, 0, dsrl_op), RT | RD | REपूर्ण,
	[insn_drotr32]	= अणुM(spec_op, 1, 0, 0, 0, dsrl32_op), RT | RD | REपूर्ण,
	[insn_dsbh]	= अणुM(spec3_op, 0, 0, 0, dsbh_op, dbshfl_op), RT | RDपूर्ण,
	[insn_dshd]	= अणुM(spec3_op, 0, 0, 0, dshd_op, dbshfl_op), RT | RDपूर्ण,
	[insn_dsll]	= अणुM(spec_op, 0, 0, 0, 0, dsll_op), RT | RD | REपूर्ण,
	[insn_dsll32]	= अणुM(spec_op, 0, 0, 0, 0, dsll32_op), RT | RD | REपूर्ण,
	[insn_dsllv]	= अणुM(spec_op, 0, 0, 0, 0, dsllv_op),  RS | RT | RDपूर्ण,
	[insn_dsra]	= अणुM(spec_op, 0, 0, 0, 0, dsra_op), RT | RD | REपूर्ण,
	[insn_dsra32]	= अणुM(spec_op, 0, 0, 0, 0, dsra32_op), RT | RD | REपूर्ण,
	[insn_dsrav]	= अणुM(spec_op, 0, 0, 0, 0, dsrav_op),  RS | RT | RDपूर्ण,
	[insn_dsrl]	= अणुM(spec_op, 0, 0, 0, 0, dsrl_op), RT | RD | REपूर्ण,
	[insn_dsrl32]	= अणुM(spec_op, 0, 0, 0, 0, dsrl32_op), RT | RD | REपूर्ण,
	[insn_dsrlv]	= अणुM(spec_op, 0, 0, 0, 0, dsrlv_op),  RS | RT | RDपूर्ण,
	[insn_dsubu]	= अणुM(spec_op, 0, 0, 0, 0, dsubu_op), RS | RT | RDपूर्ण,
	[insn_eret]	= अणुM(cop0_op, cop_op, 0, 0, 0, eret_op),  0पूर्ण,
	[insn_ext]	= अणुM(spec3_op, 0, 0, 0, 0, ext_op), RS | RT | RD | REपूर्ण,
	[insn_ins]	= अणुM(spec3_op, 0, 0, 0, 0, ins_op), RS | RT | RD | REपूर्ण,
	[insn_j]	= अणुM(j_op, 0, 0, 0, 0, 0),  JIMMपूर्ण,
	[insn_jal]	= अणुM(jal_op, 0, 0, 0, 0, 0),	JIMMपूर्ण,
	[insn_jalr]	= अणुM(spec_op, 0, 0, 0, 0, jalr_op), RS | RDपूर्ण,
#अगर_अघोषित CONFIG_CPU_MIPSR6
	[insn_jr]	= अणुM(spec_op, 0, 0, 0, 0, jr_op),  RSपूर्ण,
#अन्यथा
	[insn_jr]	= अणुM(spec_op, 0, 0, 0, 0, jalr_op),  RSपूर्ण,
#पूर्ण_अगर
	[insn_lb]	= अणुM(lb_op, 0, 0, 0, 0, 0), RS | RT | SIMMपूर्ण,
	[insn_lbu]	= अणुM(lbu_op, 0, 0, 0, 0, 0), RS | RT | SIMMपूर्ण,
	[insn_ld]	= अणुM(ld_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_lddir]	= अणुM(lwc2_op, 0, 0, 0, lddir_op, mult_op), RS | RT | RDपूर्ण,
	[insn_ldpte]	= अणुM(lwc2_op, 0, 0, 0, ldpte_op, mult_op), RS | RDपूर्ण,
	[insn_ldx]	= अणुM(spec3_op, 0, 0, 0, ldx_op, lx_op), RS | RT | RDपूर्ण,
	[insn_lh]	= अणुM(lh_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_lhu]	= अणुM(lhu_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
#अगर_अघोषित CONFIG_CPU_MIPSR6
	[insn_ll]	= अणुM(ll_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_lld]	= अणुM(lld_op, 0, 0, 0, 0, 0),	RS | RT | SIMMपूर्ण,
#अन्यथा
	[insn_ll]	= अणुM6(spec3_op, 0, 0, 0, ll6_op),  RS | RT | SIMM9पूर्ण,
	[insn_lld]	= अणुM6(spec3_op, 0, 0, 0, lld6_op),  RS | RT | SIMM9पूर्ण,
#पूर्ण_अगर
	[insn_lui]	= अणुM(lui_op, 0, 0, 0, 0, 0),	RT | SIMMपूर्ण,
	[insn_lw]	= अणुM(lw_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_lwu]	= अणुM(lwu_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_lwx]	= अणुM(spec3_op, 0, 0, 0, lwx_op, lx_op), RS | RT | RDपूर्ण,
	[insn_mfc0]	= अणुM(cop0_op, mfc_op, 0, 0, 0, 0),  RT | RD | SETपूर्ण,
	[insn_mfhc0]	= अणुM(cop0_op, mfhc0_op, 0, 0, 0, 0),  RT | RD | SETपूर्ण,
	[insn_mfhi]	= अणुM(spec_op, 0, 0, 0, 0, mfhi_op), RDपूर्ण,
	[insn_mflo]	= अणुM(spec_op, 0, 0, 0, 0, mflo_op), RDपूर्ण,
	[insn_modu]	= अणुM(spec_op, 0, 0, 0, भागu_modu_op, भागu_op),
				RS | RT | RDपूर्ण,
	[insn_movn]	= अणुM(spec_op, 0, 0, 0, 0, movn_op), RS | RT | RDपूर्ण,
	[insn_movz]	= अणुM(spec_op, 0, 0, 0, 0, movz_op), RS | RT | RDपूर्ण,
	[insn_mtc0]	= अणुM(cop0_op, mtc_op, 0, 0, 0, 0),  RT | RD | SETपूर्ण,
	[insn_mthc0]	= अणुM(cop0_op, mthc0_op, 0, 0, 0, 0),  RT | RD | SETपूर्ण,
	[insn_mthi]	= अणुM(spec_op, 0, 0, 0, 0, mthi_op), RSपूर्ण,
	[insn_mtlo]	= अणुM(spec_op, 0, 0, 0, 0, mtlo_op), RSपूर्ण,
	[insn_mulu]	= अणुM(spec_op, 0, 0, 0, multu_mulu_op, multu_op),
				RS | RT | RDपूर्ण,
#अगर_अघोषित CONFIG_CPU_MIPSR6
	[insn_mul]	= अणुM(spec2_op, 0, 0, 0, 0, mul_op), RS | RT | RDपूर्ण,
#अन्यथा
	[insn_mul]	= अणुM(spec_op, 0, 0, 0, mult_mul_op, mult_op), RS | RT | RDपूर्ण,
#पूर्ण_अगर
	[insn_multu]	= अणुM(spec_op, 0, 0, 0, 0, multu_op), RS | RTपूर्ण,
	[insn_nor]	= अणुM(spec_op, 0, 0, 0, 0, nor_op),  RS | RT | RDपूर्ण,
	[insn_or]	= अणुM(spec_op, 0, 0, 0, 0, or_op),  RS | RT | RDपूर्ण,
	[insn_ori]	= अणुM(ori_op, 0, 0, 0, 0, 0),	RS | RT | UIMMपूर्ण,
#अगर_अघोषित CONFIG_CPU_MIPSR6
	[insn_pref]	= अणुM(pref_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
#अन्यथा
	[insn_pref]	= अणुM6(spec3_op, 0, 0, 0, pref6_op),  RS | RT | SIMM9पूर्ण,
#पूर्ण_अगर
	[insn_rfe]	= अणुM(cop0_op, cop_op, 0, 0, 0, rfe_op),  0पूर्ण,
	[insn_rotr]	= अणुM(spec_op, 1, 0, 0, 0, srl_op),  RT | RD | REपूर्ण,
	[insn_sb]	= अणुM(sb_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
#अगर_अघोषित CONFIG_CPU_MIPSR6
	[insn_sc]	= अणुM(sc_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_scd]	= अणुM(scd_op, 0, 0, 0, 0, 0),	RS | RT | SIMMपूर्ण,
#अन्यथा
	[insn_sc]	= अणुM6(spec3_op, 0, 0, 0, sc6_op),  RS | RT | SIMM9पूर्ण,
	[insn_scd]	= अणुM6(spec3_op, 0, 0, 0, scd6_op),  RS | RT | SIMM9पूर्ण,
#पूर्ण_अगर
	[insn_sd]	= अणुM(sd_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_seleqz]	= अणुM(spec_op, 0, 0, 0, 0, seleqz_op), RS | RT | RDपूर्ण,
	[insn_selnez]	= अणुM(spec_op, 0, 0, 0, 0, selnez_op), RS | RT | RDपूर्ण,
	[insn_sh]	= अणुM(sh_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_sll]	= अणुM(spec_op, 0, 0, 0, 0, sll_op),  RT | RD | REपूर्ण,
	[insn_sllv]	= अणुM(spec_op, 0, 0, 0, 0, sllv_op),  RS | RT | RDपूर्ण,
	[insn_slt]	= अणुM(spec_op, 0, 0, 0, 0, slt_op),  RS | RT | RDपूर्ण,
	[insn_slti]	= अणुM(slti_op, 0, 0, 0, 0, 0), RS | RT | SIMMपूर्ण,
	[insn_sltiu]	= अणुM(sltiu_op, 0, 0, 0, 0, 0), RS | RT | SIMMपूर्ण,
	[insn_sltu]	= अणुM(spec_op, 0, 0, 0, 0, sltu_op), RS | RT | RDपूर्ण,
	[insn_sra]	= अणुM(spec_op, 0, 0, 0, 0, sra_op),  RT | RD | REपूर्ण,
	[insn_srav]	= अणुM(spec_op, 0, 0, 0, 0, srav_op), RS | RT | RDपूर्ण,
	[insn_srl]	= अणुM(spec_op, 0, 0, 0, 0, srl_op),  RT | RD | REपूर्ण,
	[insn_srlv]	= अणुM(spec_op, 0, 0, 0, 0, srlv_op),  RS | RT | RDपूर्ण,
	[insn_subu]	= अणुM(spec_op, 0, 0, 0, 0, subu_op),	RS | RT | RDपूर्ण,
	[insn_sw]	= अणुM(sw_op, 0, 0, 0, 0, 0),  RS | RT | SIMMपूर्ण,
	[insn_sync]	= अणुM(spec_op, 0, 0, 0, 0, sync_op), REपूर्ण,
	[insn_syscall]	= अणुM(spec_op, 0, 0, 0, 0, syscall_op), SCIMMपूर्ण,
	[insn_tlbp]	= अणुM(cop0_op, cop_op, 0, 0, 0, tlbp_op),  0पूर्ण,
	[insn_tlbr]	= अणुM(cop0_op, cop_op, 0, 0, 0, tlbr_op),  0पूर्ण,
	[insn_tlbwi]	= अणुM(cop0_op, cop_op, 0, 0, 0, tlbwi_op),  0पूर्ण,
	[insn_tlbwr]	= अणुM(cop0_op, cop_op, 0, 0, 0, tlbwr_op),  0पूर्ण,
	[insn_रुको]	= अणुM(cop0_op, cop_op, 0, 0, 0, रुको_op), SCIMMपूर्ण,
	[insn_wsbh]	= अणुM(spec3_op, 0, 0, 0, wsbh_op, bshfl_op), RT | RDपूर्ण,
	[insn_xor]	= अणुM(spec_op, 0, 0, 0, 0, xor_op),  RS | RT | RDपूर्ण,
	[insn_xori]	= अणुM(xori_op, 0, 0, 0, 0, 0),  RS | RT | UIMMपूर्ण,
	[insn_yield]	= अणुM(spec3_op, 0, 0, 0, 0, yield_op), RS | RDपूर्ण,
पूर्ण;

#अघोषित M

अटल अंतरभूत u32 build_bimm(s32 arg)
अणु
	WARN(arg > 0x1ffff || arg < -0x20000,
	     KERN_WARNING "Micro-assembler field overflow\n");

	WARN(arg & 0x3, KERN_WARNING "Invalid micro-assembler branch target\n");

	वापस ((arg < 0) ? (1 << 15) : 0) | ((arg >> 2) & 0x7fff);
पूर्ण

अटल अंतरभूत u32 build_jimm(u32 arg)
अणु
	WARN(arg & ~(JIMM_MASK << 2),
	     KERN_WARNING "Micro-assembler field overflow\n");

	वापस (arg >> 2) & JIMM_MASK;
पूर्ण

/*
 * The order of opcode arguments is implicitly left to right,
 * starting with RS and ending with FUNC or IMM.
 */
अटल व्योम build_insn(u32 **buf, क्रमागत opcode opc, ...)
अणु
	स्थिर काष्ठा insn *ip;
	बहु_सूची ap;
	u32 op;

	अगर (opc < 0 || opc >= insn_invalid ||
	    (opc == insn_daddiu && r4k_daddiu_bug()) ||
	    (insn_table[opc].match == 0 && insn_table[opc].fields == 0))
		panic("Unsupported Micro-assembler instruction %d", opc);

	ip = &insn_table[opc];

	op = ip->match;
	बहु_शुरू(ap, opc);
	अगर (ip->fields & RS)
		op |= build_rs(बहु_तर्क(ap, u32));
	अगर (ip->fields & RT)
		op |= build_rt(बहु_तर्क(ap, u32));
	अगर (ip->fields & RD)
		op |= build_rd(बहु_तर्क(ap, u32));
	अगर (ip->fields & RE)
		op |= build_re(बहु_तर्क(ap, u32));
	अगर (ip->fields & SIMM)
		op |= build_simm(बहु_तर्क(ap, s32));
	अगर (ip->fields & UIMM)
		op |= build_uimm(बहु_तर्क(ap, u32));
	अगर (ip->fields & BIMM)
		op |= build_bimm(बहु_तर्क(ap, s32));
	अगर (ip->fields & JIMM)
		op |= build_jimm(बहु_तर्क(ap, u32));
	अगर (ip->fields & FUNC)
		op |= build_func(बहु_तर्क(ap, u32));
	अगर (ip->fields & SET)
		op |= build_set(बहु_तर्क(ap, u32));
	अगर (ip->fields & SCIMM)
		op |= build_scimm(बहु_तर्क(ap, u32));
	अगर (ip->fields & SIMM9)
		op |= build_scimm9(बहु_तर्क(ap, u32));
	बहु_पूर्ण(ap);

	**buf = op;
	(*buf)++;
पूर्ण

अटल अंतरभूत व्योम
__resolve_relocs(काष्ठा uयंत्र_reloc *rel, काष्ठा uयंत्र_label *lab)
अणु
	दीर्घ laddr = (दीर्घ)lab->addr;
	दीर्घ raddr = (दीर्घ)rel->addr;

	चयन (rel->type) अणु
	हाल R_MIPS_PC16:
		*rel->addr |= build_bimm(laddr - (raddr + 4));
		अवरोध;

	शेष:
		panic("Unsupported Micro-assembler relocation %d",
		      rel->type);
	पूर्ण
पूर्ण

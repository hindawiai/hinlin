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
 * Copyright (C) 2012, 2013   MIPS Technologies, Inc.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/uयंत्र.h>

#घोषणा RS_MASK		0x1f
#घोषणा RS_SH		16
#घोषणा RT_MASK		0x1f
#घोषणा RT_SH		21
#घोषणा SCIMM_MASK	0x3ff
#घोषणा SCIMM_SH	16

/* This macro sets the non-variable bits of an inकाष्ठाion. */
#घोषणा M(a, b, c, d, e, f)					\
	((a) << OP_SH						\
	 | (b) << RT_SH						\
	 | (c) << RS_SH						\
	 | (d) << RD_SH						\
	 | (e) << RE_SH						\
	 | (f) << FUNC_SH)

#समावेश "uasm.c"

अटल स्थिर काष्ठा insn insn_table_MM[insn_invalid] = अणु
	[insn_addu]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_addu32_op), RT | RS | RDपूर्ण,
	[insn_addiu]	= अणुM(mm_addiu32_op, 0, 0, 0, 0, 0), RT | RS | SIMMपूर्ण,
	[insn_and]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_and_op), RT | RS | RDपूर्ण,
	[insn_andi]	= अणुM(mm_andi32_op, 0, 0, 0, 0, 0), RT | RS | UIMMपूर्ण,
	[insn_beq]	= अणुM(mm_beq32_op, 0, 0, 0, 0, 0), RS | RT | BIMMपूर्ण,
	[insn_beql]	= अणु0, 0पूर्ण,
	[insn_bgez]	= अणुM(mm_pool32i_op, mm_bgez_op, 0, 0, 0, 0), RS | BIMMपूर्ण,
	[insn_bgezl]	= अणु0, 0पूर्ण,
	[insn_bltz]	= अणुM(mm_pool32i_op, mm_bltz_op, 0, 0, 0, 0), RS | BIMMपूर्ण,
	[insn_bltzl]	= अणु0, 0पूर्ण,
	[insn_bne]	= अणुM(mm_bne32_op, 0, 0, 0, 0, 0), RT | RS | BIMMपूर्ण,
	[insn_cache]	= अणुM(mm_pool32b_op, 0, 0, mm_cache_func, 0, 0), RT | RS | SIMMपूर्ण,
	[insn_cfc1]	= अणुM(mm_pool32f_op, 0, 0, 0, mm_cfc1_op, mm_32f_73_op), RT | RSपूर्ण,
	[insn_cfcmsa]	= अणुM(mm_pool32s_op, 0, msa_cfc_op, 0, 0, mm_32s_elm_op), RD | REपूर्ण,
	[insn_ctc1]	= अणुM(mm_pool32f_op, 0, 0, 0, mm_ctc1_op, mm_32f_73_op), RT | RSपूर्ण,
	[insn_ctcmsa]	= अणुM(mm_pool32s_op, 0, msa_ctc_op, 0, 0, mm_32s_elm_op), RD | REपूर्ण,
	[insn_daddu]	= अणु0, 0पूर्ण,
	[insn_daddiu]	= अणु0, 0पूर्ण,
	[insn_di]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_di_op, mm_pool32axf_op), RSपूर्ण,
	[insn_भागu]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_भागu_op, mm_pool32axf_op), RT | RSपूर्ण,
	[insn_dmfc0]	= अणु0, 0पूर्ण,
	[insn_dmtc0]	= अणु0, 0पूर्ण,
	[insn_dsll]	= अणु0, 0पूर्ण,
	[insn_dsll32]	= अणु0, 0पूर्ण,
	[insn_dsra]	= अणु0, 0पूर्ण,
	[insn_dsrl]	= अणु0, 0पूर्ण,
	[insn_dsrl32]	= अणु0, 0पूर्ण,
	[insn_drotr]	= अणु0, 0पूर्ण,
	[insn_drotr32]	= अणु0, 0पूर्ण,
	[insn_dsubu]	= अणु0, 0पूर्ण,
	[insn_eret]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_eret_op, mm_pool32axf_op), 0पूर्ण,
	[insn_ins]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_ins_op), RT | RS | RD | REपूर्ण,
	[insn_ext]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_ext_op), RT | RS | RD | REपूर्ण,
	[insn_j]	= अणुM(mm_j32_op, 0, 0, 0, 0, 0), JIMMपूर्ण,
	[insn_jal]	= अणुM(mm_jal32_op, 0, 0, 0, 0, 0), JIMMपूर्ण,
	[insn_jalr]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_jalr_op, mm_pool32axf_op), RT | RSपूर्ण,
	[insn_jr]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_jalr_op, mm_pool32axf_op), RSपूर्ण,
	[insn_lb]	= अणुM(mm_lb32_op, 0, 0, 0, 0, 0), RT | RS | SIMMपूर्ण,
	[insn_ld]	= अणु0, 0पूर्ण,
	[insn_lh]	= अणुM(mm_lh32_op, 0, 0, 0, 0, 0), RT | RS | SIMMपूर्ण,
	[insn_ll]	= अणुM(mm_pool32c_op, 0, 0, (mm_ll_func << 1), 0, 0), RS | RT | SIMMपूर्ण,
	[insn_lld]	= अणु0, 0पूर्ण,
	[insn_lui]	= अणुM(mm_pool32i_op, mm_lui_op, 0, 0, 0, 0), RS | SIMMपूर्ण,
	[insn_lw]	= अणुM(mm_lw32_op, 0, 0, 0, 0, 0), RT | RS | SIMMपूर्ण,
	[insn_mfc0]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_mfc0_op, mm_pool32axf_op), RT | RS | RDपूर्ण,
	[insn_mfhi]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_mfhi32_op, mm_pool32axf_op), RSपूर्ण,
	[insn_mflo]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_mflo32_op, mm_pool32axf_op), RSपूर्ण,
	[insn_mtc0]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_mtc0_op, mm_pool32axf_op), RT | RS | RDपूर्ण,
	[insn_mthi]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_mthi32_op, mm_pool32axf_op), RSपूर्ण,
	[insn_mtlo]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_mtlo32_op, mm_pool32axf_op), RSपूर्ण,
	[insn_mul]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_mul_op), RT | RS | RDपूर्ण,
	[insn_or]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_or32_op), RT | RS | RDपूर्ण,
	[insn_ori]	= अणुM(mm_ori32_op, 0, 0, 0, 0, 0), RT | RS | UIMMपूर्ण,
	[insn_pref]	= अणुM(mm_pool32c_op, 0, 0, (mm_pref_func << 1), 0, 0), RT | RS | SIMMपूर्ण,
	[insn_rfe]	= अणु0, 0पूर्ण,
	[insn_sc]	= अणुM(mm_pool32c_op, 0, 0, (mm_sc_func << 1), 0, 0), RT | RS | SIMMपूर्ण,
	[insn_scd]	= अणु0, 0पूर्ण,
	[insn_sd]	= अणु0, 0पूर्ण,
	[insn_sll]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_sll32_op), RT | RS | RDपूर्ण,
	[insn_sllv]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_sllv32_op), RT | RS | RDपूर्ण,
	[insn_slt]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_slt_op), RT | RS | RDपूर्ण,
	[insn_sltiu]	= अणुM(mm_sltiu32_op, 0, 0, 0, 0, 0), RT | RS | SIMMपूर्ण,
	[insn_sltu]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_sltu_op), RT | RS | RDपूर्ण,
	[insn_sra]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_sra_op), RT | RS | RDपूर्ण,
	[insn_srav]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_srav_op), RT | RS | RDपूर्ण,
	[insn_srl]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_srl32_op), RT | RS | RDपूर्ण,
	[insn_srlv]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_srlv32_op), RT | RS | RDपूर्ण,
	[insn_rotr]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_rotr_op), RT | RS | RDपूर्ण,
	[insn_subu]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_subu32_op), RT | RS | RDपूर्ण,
	[insn_sw]	= अणुM(mm_sw32_op, 0, 0, 0, 0, 0), RT | RS | SIMMपूर्ण,
	[insn_sync]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_sync_op, mm_pool32axf_op), RSपूर्ण,
	[insn_tlbp]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_tlbp_op, mm_pool32axf_op), 0पूर्ण,
	[insn_tlbr]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_tlbr_op, mm_pool32axf_op), 0पूर्ण,
	[insn_tlbwi]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_tlbwi_op, mm_pool32axf_op), 0पूर्ण,
	[insn_tlbwr]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_tlbwr_op, mm_pool32axf_op), 0पूर्ण,
	[insn_रुको]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_रुको_op, mm_pool32axf_op), SCIMMपूर्ण,
	[insn_wsbh]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_wsbh_op, mm_pool32axf_op), RT | RSपूर्ण,
	[insn_xor]	= अणुM(mm_pool32a_op, 0, 0, 0, 0, mm_xor32_op), RT | RS | RDपूर्ण,
	[insn_xori]	= अणुM(mm_xori32_op, 0, 0, 0, 0, 0), RT | RS | UIMMपूर्ण,
	[insn_dins]	= अणु0, 0पूर्ण,
	[insn_dinsm]	= अणु0, 0पूर्ण,
	[insn_syscall]	= अणुM(mm_pool32a_op, 0, 0, 0, mm_syscall_op, mm_pool32axf_op), SCIMMपूर्ण,
	[insn_bbit0]	= अणु0, 0पूर्ण,
	[insn_bbit1]	= अणु0, 0पूर्ण,
	[insn_lwx]	= अणु0, 0पूर्ण,
	[insn_ldx]	= अणु0, 0पूर्ण,
पूर्ण;

#अघोषित M

अटल अंतरभूत u32 build_bimm(s32 arg)
अणु
	WARN(arg > 0xffff || arg < -0x10000,
	     KERN_WARNING "Micro-assembler field overflow\n");

	WARN(arg & 0x3, KERN_WARNING "Invalid micro-assembler branch target\n");

	वापस ((arg < 0) ? (1 << 15) : 0) | ((arg >> 1) & 0x7fff);
पूर्ण

अटल अंतरभूत u32 build_jimm(u32 arg)
अणु

	WARN(arg & ~((JIMM_MASK << 2) | 1),
	     KERN_WARNING "Micro-assembler field overflow\n");

	वापस (arg >> 1) & JIMM_MASK;
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
	    (insn_table_MM[opc].match == 0 && insn_table_MM[opc].fields == 0))
		panic("Unsupported Micro-assembler instruction %d", opc);

	ip = &insn_table_MM[opc];

	op = ip->match;
	बहु_शुरू(ap, opc);
	अगर (ip->fields & RS) अणु
		अगर (opc == insn_mfc0 || opc == insn_mtc0 ||
		    opc == insn_cfc1 || opc == insn_ctc1)
			op |= build_rt(बहु_तर्क(ap, u32));
		अन्यथा
			op |= build_rs(बहु_तर्क(ap, u32));
	पूर्ण
	अगर (ip->fields & RT) अणु
		अगर (opc == insn_mfc0 || opc == insn_mtc0 ||
		    opc == insn_cfc1 || opc == insn_ctc1)
			op |= build_rs(बहु_तर्क(ap, u32));
		अन्यथा
			op |= build_rt(बहु_तर्क(ap, u32));
	पूर्ण
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
	बहु_पूर्ण(ap);

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
	**buf = ((op & 0xffff) << 16) | (op >> 16);
#अन्यथा
	**buf = op;
#पूर्ण_अगर
	(*buf)++;
पूर्ण

अटल अंतरभूत व्योम
__resolve_relocs(काष्ठा uयंत्र_reloc *rel, काष्ठा uयंत्र_label *lab)
अणु
	दीर्घ laddr = (दीर्घ)lab->addr;
	दीर्घ raddr = (दीर्घ)rel->addr;

	चयन (rel->type) अणु
	हाल R_MIPS_PC16:
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
		*rel->addr |= (build_bimm(laddr - (raddr + 4)) << 16);
#अन्यथा
		*rel->addr |= build_bimm(laddr - (raddr + 4));
#पूर्ण_अगर
		अवरोध;

	शेष:
		panic("Unsupported Micro-assembler relocation %d",
		      rel->type);
	पूर्ण
पूर्ण

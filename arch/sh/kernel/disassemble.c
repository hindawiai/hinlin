<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Disassemble SuperH inकाष्ठाions.
 *
 * Copyright (C) 1999 kaz Kojima
 * Copyright (C) 2008 Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/ptrace.h>

/*
 * Format of an inकाष्ठाion in memory.
 */
प्रकार क्रमागत अणु
	HEX_0, HEX_1, HEX_2, HEX_3, HEX_4, HEX_5, HEX_6, HEX_7,
	HEX_8, HEX_9, HEX_A, HEX_B, HEX_C, HEX_D, HEX_E, HEX_F,
	REG_N, REG_M, REG_NM, REG_B,
	BRANCH_12, BRANCH_8,
	DISP_8, DISP_4,
	IMM_4, IMM_4BY2, IMM_4BY4, PCRELIMM_8BY2, PCRELIMM_8BY4,
	IMM_8, IMM_8BY2, IMM_8BY4,
पूर्ण sh_nibble_type;

प्रकार क्रमागत अणु
	A_END, A_BDISP12, A_BDISP8,
	A_DEC_M, A_DEC_N,
	A_DISP_GBR, A_DISP_PC, A_DISP_REG_M, A_DISP_REG_N,
	A_GBR,
	A_IMM,
	A_INC_M, A_INC_N,
	A_IND_M, A_IND_N, A_IND_R0_REG_M, A_IND_R0_REG_N,
	A_MACH, A_MACL,
	A_PR, A_R0, A_R0_GBR, A_REG_M, A_REG_N, A_REG_B,
	A_SR, A_VBR, A_SSR, A_SPC, A_SGR, A_DBR,
	F_REG_N, F_REG_M, D_REG_N, D_REG_M,
	X_REG_N, /* Only used क्रम argument parsing */
	X_REG_M, /* Only used क्रम argument parsing */
	DX_REG_N, DX_REG_M, V_REG_N, V_REG_M,
	FD_REG_N,
	XMTRX_M4,
	F_FR0,
	FPUL_N, FPUL_M, FPSCR_N, FPSCR_M,
पूर्ण sh_arg_type;

अटल काष्ठा sh_opcode_info अणु
	अक्षर *name;
	sh_arg_type arg[7];
	sh_nibble_type nibbles[4];
पूर्ण sh_table[] = अणु
	अणु"add",अणुA_IMM,A_REG_Nपूर्ण,अणुHEX_7,REG_N,IMM_8पूर्णपूर्ण,
	अणु"add",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_Cपूर्णपूर्ण,
	अणु"addc",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_Eपूर्णपूर्ण,
	अणु"addv",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_Fपूर्णपूर्ण,
	अणु"and",अणुA_IMM,A_R0पूर्ण,अणुHEX_C,HEX_9,IMM_8पूर्णपूर्ण,
	अणु"and",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_9पूर्णपूर्ण,
	अणु"and.b",अणुA_IMM,A_R0_GBRपूर्ण,अणुHEX_C,HEX_D,IMM_8पूर्णपूर्ण,
	अणु"bra",अणुA_BDISP12पूर्ण,अणुHEX_A,BRANCH_12पूर्णपूर्ण,
	अणु"bsr",अणुA_BDISP12पूर्ण,अणुHEX_B,BRANCH_12पूर्णपूर्ण,
	अणु"bt",अणुA_BDISP8पूर्ण,अणुHEX_8,HEX_9,BRANCH_8पूर्णपूर्ण,
	अणु"bf",अणुA_BDISP8पूर्ण,अणुHEX_8,HEX_B,BRANCH_8पूर्णपूर्ण,
	अणु"bt.s",अणुA_BDISP8पूर्ण,अणुHEX_8,HEX_D,BRANCH_8पूर्णपूर्ण,
	अणु"bt/s",अणुA_BDISP8पूर्ण,अणुHEX_8,HEX_D,BRANCH_8पूर्णपूर्ण,
	अणु"bf.s",अणुA_BDISP8पूर्ण,अणुHEX_8,HEX_F,BRANCH_8पूर्णपूर्ण,
	अणु"bf/s",अणुA_BDISP8पूर्ण,अणुHEX_8,HEX_F,BRANCH_8पूर्णपूर्ण,
	अणु"clrmac",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_2,HEX_8पूर्णपूर्ण,
	अणु"clrs",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_4,HEX_8पूर्णपूर्ण,
	अणु"clrt",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_0,HEX_8पूर्णपूर्ण,
	अणु"cmp/eq",अणुA_IMM,A_R0पूर्ण,अणुHEX_8,HEX_8,IMM_8पूर्णपूर्ण,
	अणु"cmp/eq",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_0पूर्णपूर्ण,
	अणु"cmp/ge",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_3पूर्णपूर्ण,
	अणु"cmp/gt",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"cmp/hi",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_6पूर्णपूर्ण,
	अणु"cmp/hs",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_2पूर्णपूर्ण,
	अणु"cmp/pl",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_5पूर्णपूर्ण,
	अणु"cmp/pz",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_1पूर्णपूर्ण,
	अणु"cmp/str",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_Cपूर्णपूर्ण,
	अणु"div0s",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"div0u",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_1,HEX_9पूर्णपूर्ण,
	अणु"div1",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_4पूर्णपूर्ण,
	अणु"exts.b",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_Eपूर्णपूर्ण,
	अणु"exts.w",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_Fपूर्णपूर्ण,
	अणु"extu.b",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_Cपूर्णपूर्ण,
	अणु"extu.w",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_Dपूर्णपूर्ण,
	अणु"jmp",अणुA_IND_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_Bपूर्णपूर्ण,
	अणु"jsr",अणुA_IND_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_Bपूर्णपूर्ण,
	अणु"ldc",अणुA_REG_N,A_SRपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_Eपूर्णपूर्ण,
	अणु"ldc",अणुA_REG_N,A_GBRपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_Eपूर्णपूर्ण,
	अणु"ldc",अणुA_REG_N,A_VBRपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_Eपूर्णपूर्ण,
	अणु"ldc",अणुA_REG_N,A_SSRपूर्ण,अणुHEX_4,REG_N,HEX_3,HEX_Eपूर्णपूर्ण,
	अणु"ldc",अणुA_REG_N,A_SPCपूर्ण,अणुHEX_4,REG_N,HEX_4,HEX_Eपूर्णपूर्ण,
	अणु"ldc",अणुA_REG_N,A_DBRपूर्ण,अणुHEX_4,REG_N,HEX_7,HEX_Eपूर्णपूर्ण,
	अणु"ldc",अणुA_REG_N,A_REG_Bपूर्ण,अणुHEX_4,REG_N,REG_B,HEX_Eपूर्णपूर्ण,
	अणु"ldc.l",अणुA_INC_N,A_SRपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_7पूर्णपूर्ण,
	अणु"ldc.l",अणुA_INC_N,A_GBRपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_7पूर्णपूर्ण,
	अणु"ldc.l",अणुA_INC_N,A_VBRपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_7पूर्णपूर्ण,
	अणु"ldc.l",अणुA_INC_N,A_SSRपूर्ण,अणुHEX_4,REG_N,HEX_3,HEX_7पूर्णपूर्ण,
	अणु"ldc.l",अणुA_INC_N,A_SPCपूर्ण,अणुHEX_4,REG_N,HEX_4,HEX_7पूर्णपूर्ण,
	अणु"ldc.l",अणुA_INC_N,A_DBRपूर्ण,अणुHEX_4,REG_N,HEX_7,HEX_7पूर्णपूर्ण,
	अणु"ldc.l",अणुA_INC_N,A_REG_Bपूर्ण,अणुHEX_4,REG_N,REG_B,HEX_7पूर्णपूर्ण,
	अणु"lds",अणुA_REG_N,A_MACHपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_Aपूर्णपूर्ण,
	अणु"lds",अणुA_REG_N,A_MACLपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_Aपूर्णपूर्ण,
	अणु"lds",अणुA_REG_N,A_PRपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_Aपूर्णपूर्ण,
	अणु"lds",अणुA_REG_M,FPUL_Nपूर्ण,अणुHEX_4,REG_M,HEX_5,HEX_Aपूर्णपूर्ण,
	अणु"lds",अणुA_REG_M,FPSCR_Nपूर्ण,अणुHEX_4,REG_M,HEX_6,HEX_Aपूर्णपूर्ण,
	अणु"lds.l",अणुA_INC_N,A_MACHपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_6पूर्णपूर्ण,
	अणु"lds.l",अणुA_INC_N,A_MACLपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_6पूर्णपूर्ण,
	अणु"lds.l",अणुA_INC_N,A_PRपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_6पूर्णपूर्ण,
	अणु"lds.l",अणुA_INC_M,FPUL_Nपूर्ण,अणुHEX_4,REG_M,HEX_5,HEX_6पूर्णपूर्ण,
	अणु"lds.l",अणुA_INC_M,FPSCR_Nपूर्ण,अणुHEX_4,REG_M,HEX_6,HEX_6पूर्णपूर्ण,
	अणु"ldtlb",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_3,HEX_8पूर्णपूर्ण,
	अणु"mac.w",अणुA_INC_M,A_INC_Nपूर्ण,अणुHEX_4,REG_N,REG_M,HEX_Fपूर्णपूर्ण,
	अणु"mov",अणुA_IMM,A_REG_Nपूर्ण,अणुHEX_E,REG_N,IMM_8पूर्णपूर्ण,
	अणु"mov",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_3पूर्णपूर्ण,
	अणु"mov.b",अणु A_REG_M,A_IND_R0_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_4पूर्णपूर्ण,
	अणु"mov.b",अणु A_REG_M,A_DEC_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_4पूर्णपूर्ण,
	अणु"mov.b",अणु A_REG_M,A_IND_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_0पूर्णपूर्ण,
	अणु"mov.b",अणुA_DISP_REG_M,A_R0पूर्ण,अणुHEX_8,HEX_4,REG_M,IMM_4पूर्णपूर्ण,
	अणु"mov.b",अणुA_DISP_GBR,A_R0पूर्ण,अणुHEX_C,HEX_4,IMM_8पूर्णपूर्ण,
	अणु"mov.b",अणुA_IND_R0_REG_M,A_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_Cपूर्णपूर्ण,
	अणु"mov.b",अणुA_INC_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_4पूर्णपूर्ण,
	अणु"mov.b",अणुA_IND_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_0पूर्णपूर्ण,
	अणु"mov.b",अणुA_R0,A_DISP_REG_Mपूर्ण,अणुHEX_8,HEX_0,REG_M,IMM_4पूर्णपूर्ण,
	अणु"mov.b",अणुA_R0,A_DISP_GBRपूर्ण,अणुHEX_C,HEX_0,IMM_8पूर्णपूर्ण,
	अणु"mov.l",अणु A_REG_M,A_DISP_REG_Nपूर्ण,अणुHEX_1,REG_N,REG_M,IMM_4BY4पूर्णपूर्ण,
	अणु"mov.l",अणु A_REG_M,A_IND_R0_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_6पूर्णपूर्ण,
	अणु"mov.l",अणु A_REG_M,A_DEC_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_6पूर्णपूर्ण,
	अणु"mov.l",अणु A_REG_M,A_IND_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_2पूर्णपूर्ण,
	अणु"mov.l",अणुA_DISP_REG_M,A_REG_Nपूर्ण,अणुHEX_5,REG_N,REG_M,IMM_4BY4पूर्णपूर्ण,
	अणु"mov.l",अणुA_DISP_GBR,A_R0पूर्ण,अणुHEX_C,HEX_6,IMM_8BY4पूर्णपूर्ण,
	अणु"mov.l",अणुA_DISP_PC,A_REG_Nपूर्ण,अणुHEX_D,REG_N,PCRELIMM_8BY4पूर्णपूर्ण,
	अणु"mov.l",अणुA_IND_R0_REG_M,A_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_Eपूर्णपूर्ण,
	अणु"mov.l",अणुA_INC_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_6पूर्णपूर्ण,
	अणु"mov.l",अणुA_IND_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_2पूर्णपूर्ण,
	अणु"mov.l",अणुA_R0,A_DISP_GBRपूर्ण,अणुHEX_C,HEX_2,IMM_8BY4पूर्णपूर्ण,
	अणु"mov.w",अणु A_REG_M,A_IND_R0_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_5पूर्णपूर्ण,
	अणु"mov.w",अणु A_REG_M,A_DEC_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_5पूर्णपूर्ण,
	अणु"mov.w",अणु A_REG_M,A_IND_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_1पूर्णपूर्ण,
	अणु"mov.w",अणुA_DISP_REG_M,A_R0पूर्ण,अणुHEX_8,HEX_5,REG_M,IMM_4BY2पूर्णपूर्ण,
	अणु"mov.w",अणुA_DISP_GBR,A_R0पूर्ण,अणुHEX_C,HEX_5,IMM_8BY2पूर्णपूर्ण,
	अणु"mov.w",अणुA_DISP_PC,A_REG_Nपूर्ण,अणुHEX_9,REG_N,PCRELIMM_8BY2पूर्णपूर्ण,
	अणु"mov.w",अणुA_IND_R0_REG_M,A_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_Dपूर्णपूर्ण,
	अणु"mov.w",अणुA_INC_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_5पूर्णपूर्ण,
	अणु"mov.w",अणुA_IND_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_1पूर्णपूर्ण,
	अणु"mov.w",अणुA_R0,A_DISP_REG_Mपूर्ण,अणुHEX_8,HEX_1,REG_M,IMM_4BY2पूर्णपूर्ण,
	अणु"mov.w",अणुA_R0,A_DISP_GBRपूर्ण,अणुHEX_C,HEX_1,IMM_8BY2पूर्णपूर्ण,
	अणु"mova",अणुA_DISP_PC,A_R0पूर्ण,अणुHEX_C,HEX_7,PCRELIMM_8BY4पूर्णपूर्ण,
	अणु"movca.l",अणुA_R0,A_IND_Nपूर्ण,अणुHEX_0,REG_N,HEX_C,HEX_3पूर्णपूर्ण,
	अणु"movt",अणुA_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_2,HEX_9पूर्णपूर्ण,
	अणु"muls",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_Fपूर्णपूर्ण,
	अणु"mul.l",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"mulu",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_Eपूर्णपूर्ण,
	अणु"neg",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_Bपूर्णपूर्ण,
	अणु"negc",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_Aपूर्णपूर्ण,
	अणु"nop",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_0,HEX_9पूर्णपूर्ण,
	अणु"not",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"ocbi",अणुA_IND_Nपूर्ण,अणुHEX_0,REG_N,HEX_9,HEX_3पूर्णपूर्ण,
	अणु"ocbp",अणुA_IND_Nपूर्ण,अणुHEX_0,REG_N,HEX_A,HEX_3पूर्णपूर्ण,
	अणु"ocbwb",अणुA_IND_Nपूर्ण,अणुHEX_0,REG_N,HEX_B,HEX_3पूर्णपूर्ण,
	अणु"or",अणुA_IMM,A_R0पूर्ण,अणुHEX_C,HEX_B,IMM_8पूर्णपूर्ण,
	अणु"or",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_Bपूर्णपूर्ण,
	अणु"or.b",अणुA_IMM,A_R0_GBRपूर्ण,अणुHEX_C,HEX_F,IMM_8पूर्णपूर्ण,
	अणु"pref",अणुA_IND_Nपूर्ण,अणुHEX_0,REG_N,HEX_8,HEX_3पूर्णपूर्ण,
	अणु"rotcl",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_4पूर्णपूर्ण,
	अणु"rotcr",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_5पूर्णपूर्ण,
	अणु"rotl",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_4पूर्णपूर्ण,
	अणु"rotr",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_5पूर्णपूर्ण,
	अणु"rte",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_2,HEX_Bपूर्णपूर्ण,
	अणु"rts",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_0,HEX_Bपूर्णपूर्ण,
	अणु"sets",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_5,HEX_8पूर्णपूर्ण,
	अणु"sett",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_1,HEX_8पूर्णपूर्ण,
	अणु"shad",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_4,REG_N,REG_M,HEX_Cपूर्णपूर्ण,
	अणु"shld",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_4,REG_N,REG_M,HEX_Dपूर्णपूर्ण,
	अणु"shal",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_0पूर्णपूर्ण,
	अणु"shar",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_1पूर्णपूर्ण,
	अणु"shll",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_0पूर्णपूर्ण,
	अणु"shll16",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_8पूर्णपूर्ण,
	अणु"shll2",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_8पूर्णपूर्ण,
	अणु"shll8",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_8पूर्णपूर्ण,
	अणु"shlr",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_1पूर्णपूर्ण,
	अणु"shlr16",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_9पूर्णपूर्ण,
	अणु"shlr2",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_9पूर्णपूर्ण,
	अणु"shlr8",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_9पूर्णपूर्ण,
	अणु"sleep",अणु0पूर्ण,अणुHEX_0,HEX_0,HEX_1,HEX_Bपूर्णपूर्ण,
	अणु"stc",अणुA_SR,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_0,HEX_2पूर्णपूर्ण,
	अणु"stc",अणुA_GBR,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_1,HEX_2पूर्णपूर्ण,
	अणु"stc",अणुA_VBR,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_2,HEX_2पूर्णपूर्ण,
	अणु"stc",अणुA_SSR,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_3,HEX_2पूर्णपूर्ण,
	अणु"stc",अणुA_SPC,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_4,HEX_2पूर्णपूर्ण,
	अणु"stc",अणुA_SGR,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_6,HEX_2पूर्णपूर्ण,
	अणु"stc",अणुA_DBR,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_7,HEX_2पूर्णपूर्ण,
	अणु"stc",अणुA_REG_B,A_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_B,HEX_2पूर्णपूर्ण,
	अणु"stc.l",अणुA_SR,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_3पूर्णपूर्ण,
	अणु"stc.l",अणुA_GBR,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_3पूर्णपूर्ण,
	अणु"stc.l",अणुA_VBR,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_3पूर्णपूर्ण,
	अणु"stc.l",अणुA_SSR,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_3,HEX_3पूर्णपूर्ण,
	अणु"stc.l",अणुA_SPC,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_4,HEX_3पूर्णपूर्ण,
	अणु"stc.l",अणुA_SGR,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_6,HEX_3पूर्णपूर्ण,
	अणु"stc.l",अणुA_DBR,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_7,HEX_3पूर्णपूर्ण,
	अणु"stc.l",अणुA_REG_B,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,REG_B,HEX_3पूर्णपूर्ण,
	अणु"sts",अणुA_MACH,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_0,HEX_Aपूर्णपूर्ण,
	अणु"sts",अणुA_MACL,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_1,HEX_Aपूर्णपूर्ण,
	अणु"sts",अणुA_PR,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_2,HEX_Aपूर्णपूर्ण,
	अणु"sts",अणुFPUL_M,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_5,HEX_Aपूर्णपूर्ण,
	अणु"sts",अणुFPSCR_M,A_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_6,HEX_Aपूर्णपूर्ण,
	अणु"sts.l",अणुA_MACH,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_0,HEX_2पूर्णपूर्ण,
	अणु"sts.l",अणुA_MACL,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_2पूर्णपूर्ण,
	अणु"sts.l",अणुA_PR,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_2,HEX_2पूर्णपूर्ण,
	अणु"sts.l",अणुFPUL_M,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_5,HEX_2पूर्णपूर्ण,
	अणु"sts.l",अणुFPSCR_M,A_DEC_Nपूर्ण,अणुHEX_4,REG_N,HEX_6,HEX_2पूर्णपूर्ण,
	अणु"sub",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_8पूर्णपूर्ण,
	अणु"subc",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_Aपूर्णपूर्ण,
	अणु"subv",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_Bपूर्णपूर्ण,
	अणु"swap.b",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_8पूर्णपूर्ण,
	अणु"swap.w",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_6,REG_N,REG_M,HEX_9पूर्णपूर्ण,
	अणु"tas.b",अणुA_IND_Nपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_Bपूर्णपूर्ण,
	अणु"trapa",अणुA_IMMपूर्ण,अणुHEX_C,HEX_3,IMM_8पूर्णपूर्ण,
	अणु"tst",अणुA_IMM,A_R0पूर्ण,अणुHEX_C,HEX_8,IMM_8पूर्णपूर्ण,
	अणु"tst",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_8पूर्णपूर्ण,
	अणु"tst.b",अणुA_IMM,A_R0_GBRपूर्ण,अणुHEX_C,HEX_C,IMM_8पूर्णपूर्ण,
	अणु"xor",अणुA_IMM,A_R0पूर्ण,अणुHEX_C,HEX_A,IMM_8पूर्णपूर्ण,
	अणु"xor",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_Aपूर्णपूर्ण,
	अणु"xor.b",अणुA_IMM,A_R0_GBRपूर्ण,अणुHEX_C,HEX_E,IMM_8पूर्णपूर्ण,
	अणु"xtrct",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_2,REG_N,REG_M,HEX_Dपूर्णपूर्ण,
	अणु"mul.l",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"dt",अणुA_REG_Nपूर्ण,अणुHEX_4,REG_N,HEX_1,HEX_0पूर्णपूर्ण,
	अणु"dmuls.l",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_Dपूर्णपूर्ण,
	अणु"dmulu.l",अणु A_REG_M,A_REG_Nपूर्ण,अणुHEX_3,REG_N,REG_M,HEX_5पूर्णपूर्ण,
	अणु"mac.l",अणुA_INC_M,A_INC_Nपूर्ण,अणुHEX_0,REG_N,REG_M,HEX_Fपूर्णपूर्ण,
	अणु"braf",अणुA_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_2,HEX_3पूर्णपूर्ण,
	अणु"bsrf",अणुA_REG_Nपूर्ण,अणुHEX_0,REG_N,HEX_0,HEX_3पूर्णपूर्ण,
	अणु"fabs",अणुFD_REG_Nपूर्ण,अणुHEX_F,REG_N,HEX_5,HEX_Dपूर्णपूर्ण,
	अणु"fadd",अणुF_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_0पूर्णपूर्ण,
	अणु"fadd",अणुD_REG_M,D_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_0पूर्णपूर्ण,
	अणु"fcmp/eq",अणुF_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_4पूर्णपूर्ण,
	अणु"fcmp/eq",अणुD_REG_M,D_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_4पूर्णपूर्ण,
	अणु"fcmp/gt",अणुF_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_5पूर्णपूर्ण,
	अणु"fcmp/gt",अणुD_REG_M,D_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_5पूर्णपूर्ण,
	अणु"fcnvds",अणुD_REG_N,FPUL_Mपूर्ण,अणुHEX_F,REG_N,HEX_B,HEX_Dपूर्णपूर्ण,
	अणु"fcnvsd",अणुFPUL_M,D_REG_Nपूर्ण,अणुHEX_F,REG_N,HEX_A,HEX_Dपूर्णपूर्ण,
	अणु"fdiv",अणुF_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_3पूर्णपूर्ण,
	अणु"fdiv",अणुD_REG_M,D_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_3पूर्णपूर्ण,
	अणु"fipr",अणुV_REG_M,V_REG_Nपूर्ण,अणुHEX_F,REG_NM,HEX_E,HEX_Dपूर्णपूर्ण,
	अणु"fldi0",अणुF_REG_Nपूर्ण,अणुHEX_F,REG_N,HEX_8,HEX_Dपूर्णपूर्ण,
	अणु"fldi1",अणुF_REG_Nपूर्ण,अणुHEX_F,REG_N,HEX_9,HEX_Dपूर्णपूर्ण,
	अणु"flds",अणुF_REG_N,FPUL_Mपूर्ण,अणुHEX_F,REG_N,HEX_1,HEX_Dपूर्णपूर्ण,
	अणु"float",अणुFPUL_M,FD_REG_Nपूर्ण,अणुHEX_F,REG_N,HEX_2,HEX_Dपूर्णपूर्ण,
	अणु"fmac",अणुF_FR0,F_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Eपूर्णपूर्ण,
	अणु"fmov",अणुF_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Cपूर्णपूर्ण,
	अणु"fmov",अणुDX_REG_M,DX_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Cपूर्णपूर्ण,
	अणु"fmov",अणुA_IND_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_8पूर्णपूर्ण,
	अणु"fmov",अणुA_IND_M,DX_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_8पूर्णपूर्ण,
	अणु"fmov",अणुF_REG_M,A_IND_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Aपूर्णपूर्ण,
	अणु"fmov",अणुDX_REG_M,A_IND_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Aपूर्णपूर्ण,
	अणु"fmov",अणुA_INC_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_9पूर्णपूर्ण,
	अणु"fmov",अणुA_INC_M,DX_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_9पूर्णपूर्ण,
	अणु"fmov",अणुF_REG_M,A_DEC_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Bपूर्णपूर्ण,
	अणु"fmov",अणुDX_REG_M,A_DEC_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Bपूर्णपूर्ण,
	अणु"fmov",अणुA_IND_R0_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_6पूर्णपूर्ण,
	अणु"fmov",अणुA_IND_R0_REG_M,DX_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_6पूर्णपूर्ण,
	अणु"fmov",अणुF_REG_M,A_IND_R0_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"fmov",अणुDX_REG_M,A_IND_R0_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"fmov.d",अणुA_IND_M,DX_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_8पूर्णपूर्ण,
	अणु"fmov.d",अणुDX_REG_M,A_IND_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Aपूर्णपूर्ण,
	अणु"fmov.d",अणुA_INC_M,DX_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_9पूर्णपूर्ण,
	अणु"fmov.d",अणुDX_REG_M,A_DEC_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Bपूर्णपूर्ण,
	अणु"fmov.d",अणुA_IND_R0_REG_M,DX_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_6पूर्णपूर्ण,
	अणु"fmov.d",अणुDX_REG_M,A_IND_R0_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"fmov.s",अणुA_IND_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_8पूर्णपूर्ण,
	अणु"fmov.s",अणुF_REG_M,A_IND_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Aपूर्णपूर्ण,
	अणु"fmov.s",अणुA_INC_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_9पूर्णपूर्ण,
	अणु"fmov.s",अणुF_REG_M,A_DEC_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_Bपूर्णपूर्ण,
	अणु"fmov.s",अणुA_IND_R0_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_6पूर्णपूर्ण,
	अणु"fmov.s",अणुF_REG_M,A_IND_R0_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_7पूर्णपूर्ण,
	अणु"fmul",अणुF_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_2पूर्णपूर्ण,
	अणु"fmul",अणुD_REG_M,D_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_2पूर्णपूर्ण,
	अणु"fneg",अणुFD_REG_Nपूर्ण,अणुHEX_F,REG_N,HEX_4,HEX_Dपूर्णपूर्ण,
	अणु"frchg",अणु0पूर्ण,अणुHEX_F,HEX_B,HEX_F,HEX_Dपूर्णपूर्ण,
	अणु"fschg",अणु0पूर्ण,अणुHEX_F,HEX_3,HEX_F,HEX_Dपूर्णपूर्ण,
	अणु"fsqrt",अणुFD_REG_Nपूर्ण,अणुHEX_F,REG_N,HEX_6,HEX_Dपूर्णपूर्ण,
	अणु"fsts",अणुFPUL_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,HEX_0,HEX_Dपूर्णपूर्ण,
	अणु"fsub",अणुF_REG_M,F_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_1पूर्णपूर्ण,
	अणु"fsub",अणुD_REG_M,D_REG_Nपूर्ण,अणुHEX_F,REG_N,REG_M,HEX_1पूर्णपूर्ण,
	अणु"ftrc",अणुFD_REG_N,FPUL_Mपूर्ण,अणुHEX_F,REG_N,HEX_3,HEX_Dपूर्णपूर्ण,
	अणु"ftrv",अणुXMTRX_M4,V_REG_Nपूर्ण,अणुHEX_F,REG_NM,HEX_F,HEX_Dपूर्णपूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल व्योम prपूर्णांक_sh_insn(u32 memaddr, u16 insn)
अणु
	पूर्णांक relmask = ~0;
	पूर्णांक nibs[4] = अणु (insn >> 12) & 0xf, (insn >> 8) & 0xf, (insn >> 4) & 0xf, insn & 0xfपूर्ण;
	पूर्णांक lastsp;
	काष्ठा sh_opcode_info *op = sh_table;

	क्रम (; op->name; op++) अणु
		पूर्णांक n;
		पूर्णांक imm = 0;
		पूर्णांक rn = 0;
		पूर्णांक rm = 0;
		पूर्णांक rb = 0;
		पूर्णांक disp_pc;
		पूर्णांक disp_pc_addr = 0;

		क्रम (n = 0; n < 4; n++) अणु
			पूर्णांक i = op->nibbles[n];

			अगर (i < 16) अणु
				अगर (nibs[n] == i)
					जारी;
				जाओ fail;
			पूर्ण
			चयन (i) अणु
			हाल BRANCH_8:
				imm = (nibs[2] << 4) | (nibs[3]);
				अगर (imm & 0x80)
					imm |= ~0xff;
				imm = ((अक्षर)imm) * 2 + 4 ;
				जाओ ok;
			हाल BRANCH_12:
				imm = ((nibs[1]) << 8) | (nibs[2] << 4) | (nibs[3]);
				अगर (imm & 0x800)
					imm |= ~0xfff;
				imm = imm * 2 + 4;
				जाओ ok;
			हाल IMM_4:
				imm = nibs[3];
				जाओ ok;
			हाल IMM_4BY2:
				imm = nibs[3] <<1;
				जाओ ok;
			हाल IMM_4BY4:
				imm = nibs[3] <<2;
				जाओ ok;
			हाल IMM_8:
				imm = (nibs[2] << 4) | nibs[3];
				जाओ ok;
			हाल PCRELIMM_8BY2:
				imm = ((nibs[2] << 4) | nibs[3]) <<1;
				relmask = ~1;
				जाओ ok;
			हाल PCRELIMM_8BY4:
				imm = ((nibs[2] << 4) | nibs[3]) <<2;
				relmask = ~3;
				जाओ ok;
			हाल IMM_8BY2:
				imm = ((nibs[2] << 4) | nibs[3]) <<1;
				जाओ ok;
			हाल IMM_8BY4:
				imm = ((nibs[2] << 4) | nibs[3]) <<2;
				जाओ ok;
			हाल DISP_8:
				imm = (nibs[2] << 4) | (nibs[3]);
				जाओ ok;
			हाल DISP_4:
				imm = nibs[3];
				जाओ ok;
			हाल REG_N:
				rn = nibs[n];
				अवरोध;
			हाल REG_M:
				rm = nibs[n];
				अवरोध;
			हाल REG_NM:
				rn = (nibs[n] & 0xc) >> 2;
				rm = (nibs[n] & 0x3);
				अवरोध;
			हाल REG_B:
				rb = nibs[n] & 0x07;
				अवरोध;
			शेष:
				वापस;
			पूर्ण
		पूर्ण

	ok:
		pr_cont("%-8s  ", op->name);
		lastsp = (op->arg[0] == A_END);
		disp_pc = 0;
		क्रम (n = 0; n < 6 && op->arg[n] != A_END; n++) अणु
			अगर (n && op->arg[1] != A_END)
				pr_cont(", ");
			चयन (op->arg[n]) अणु
			हाल A_IMM:
				pr_cont("#%d", (अक्षर)(imm));
				अवरोध;
			हाल A_R0:
				pr_cont("r0");
				अवरोध;
			हाल A_REG_N:
				pr_cont("r%d", rn);
				अवरोध;
			हाल A_INC_N:
				pr_cont("@r%d+", rn);
				अवरोध;
			हाल A_DEC_N:
				pr_cont("@-r%d", rn);
				अवरोध;
			हाल A_IND_N:
				pr_cont("@r%d", rn);
				अवरोध;
			हाल A_DISP_REG_N:
				pr_cont("@(%d,r%d)", imm, rn);
				अवरोध;
			हाल A_REG_M:
				pr_cont("r%d", rm);
				अवरोध;
			हाल A_INC_M:
				pr_cont("@r%d+", rm);
				अवरोध;
			हाल A_DEC_M:
				pr_cont("@-r%d", rm);
				अवरोध;
			हाल A_IND_M:
				pr_cont("@r%d", rm);
				अवरोध;
			हाल A_DISP_REG_M:
				pr_cont("@(%d,r%d)", imm, rm);
				अवरोध;
			हाल A_REG_B:
				pr_cont("r%d_bank", rb);
				अवरोध;
			हाल A_DISP_PC:
				disp_pc = 1;
				disp_pc_addr = imm + 4 + (memaddr & relmask);
				pr_cont("%08x <%pS>", disp_pc_addr,
					(व्योम *)disp_pc_addr);
				अवरोध;
			हाल A_IND_R0_REG_N:
				pr_cont("@(r0,r%d)", rn);
				अवरोध;
			हाल A_IND_R0_REG_M:
				pr_cont("@(r0,r%d)", rm);
				अवरोध;
			हाल A_DISP_GBR:
				pr_cont("@(%d,gbr)", imm);
				अवरोध;
			हाल A_R0_GBR:
				pr_cont("@(r0,gbr)");
				अवरोध;
			हाल A_BDISP12:
			हाल A_BDISP8:
				pr_cont("%08x", imm + memaddr);
				अवरोध;
			हाल A_SR:
				pr_cont("sr");
				अवरोध;
			हाल A_GBR:
				pr_cont("gbr");
				अवरोध;
			हाल A_VBR:
				pr_cont("vbr");
				अवरोध;
			हाल A_SSR:
				pr_cont("ssr");
				अवरोध;
			हाल A_SPC:
				pr_cont("spc");
				अवरोध;
			हाल A_MACH:
				pr_cont("mach");
				अवरोध;
			हाल A_MACL:
				pr_cont("macl");
				अवरोध;
			हाल A_PR:
				pr_cont("pr");
				अवरोध;
			हाल A_SGR:
				pr_cont("sgr");
				अवरोध;
			हाल A_DBR:
				pr_cont("dbr");
				अवरोध;
			हाल FD_REG_N:
			हाल F_REG_N:
				pr_cont("fr%d", rn);
				अवरोध;
			हाल F_REG_M:
				pr_cont("fr%d", rm);
				अवरोध;
			हाल DX_REG_N:
				अगर (rn & 1) अणु
					pr_cont("xd%d", rn & ~1);
					अवरोध;
				पूर्ण
				fallthrough;
			हाल D_REG_N:
				pr_cont("dr%d", rn);
				अवरोध;
			हाल DX_REG_M:
				अगर (rm & 1) अणु
					pr_cont("xd%d", rm & ~1);
					अवरोध;
				पूर्ण
				fallthrough;
			हाल D_REG_M:
				pr_cont("dr%d", rm);
				अवरोध;
			हाल FPSCR_M:
			हाल FPSCR_N:
				pr_cont("fpscr");
				अवरोध;
			हाल FPUL_M:
			हाल FPUL_N:
				pr_cont("fpul");
				अवरोध;
			हाल F_FR0:
				pr_cont("fr0");
				अवरोध;
			हाल V_REG_N:
				pr_cont("fv%d", rn*4);
				अवरोध;
			हाल V_REG_M:
				pr_cont("fv%d", rm*4);
				अवरोध;
			हाल XMTRX_M4:
				pr_cont("xmtrx");
				अवरोध;
			शेष:
				वापस;
			पूर्ण
		पूर्ण

		अगर (disp_pc && म_भेद(op->name, "mova") != 0) अणु
			u32 val;

			अगर (relmask == ~1)
				__get_user(val, (u16 *)disp_pc_addr);
			अन्यथा
				__get_user(val, (u32 *)disp_pc_addr);

			pr_cont("  ! %08x <%pS>", val, (व्योम *)val);
		पूर्ण

		वापस;
	fail:
		;

	पूर्ण

	pr_info(".word 0x%x%x%x%x", nibs[0], nibs[1], nibs[2], nibs[3]);
पूर्ण

व्योम show_code(काष्ठा pt_regs *regs)
अणु
	अचिन्हित लघु *pc = (अचिन्हित लघु *)regs->pc;
	दीर्घ i;

	अगर (regs->pc & 0x1)
		वापस;

	pr_info("Code:\n");

	क्रम (i = -3 ; i < 6 ; i++) अणु
		अचिन्हित लघु insn;

		अगर (__get_user(insn, pc + i)) अणु
			pr_err(" (Bad address in pc)\n");
			अवरोध;
		पूर्ण

		pr_info("%s%08lx:  ", (i ? "  " : "->"),
			(अचिन्हित दीर्घ)(pc + i));
		prपूर्णांक_sh_insn((अचिन्हित दीर्घ)(pc + i), insn);
		pr_cont("\n");
	पूर्ण

	pr_info("\n");
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Disassemble s390 inकाष्ठाions.
 *
 * Copyright IBM Corp. 2007
 * Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/reboot.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/dis.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/irq.h>

/* Type of opeअक्रम */
#घोषणा OPERAND_GPR	0x1	/* Opeअक्रम prपूर्णांकed as %rx */
#घोषणा OPERAND_FPR	0x2	/* Opeअक्रम prपूर्णांकed as %fx */
#घोषणा OPERAND_AR	0x4	/* Opeअक्रम prपूर्णांकed as %ax */
#घोषणा OPERAND_CR	0x8	/* Opeअक्रम prपूर्णांकed as %cx */
#घोषणा OPERAND_VR	0x10	/* Opeअक्रम prपूर्णांकed as %vx */
#घोषणा OPERAND_DISP	0x20	/* Opeअक्रम prपूर्णांकed as displacement */
#घोषणा OPERAND_BASE	0x40	/* Opeअक्रम prपूर्णांकed as base रेजिस्टर */
#घोषणा OPERAND_INDEX	0x80	/* Opeअक्रम prपूर्णांकed as index रेजिस्टर */
#घोषणा OPERAND_PCREL	0x100	/* Opeअक्रम prपूर्णांकed as pc-relative symbol */
#घोषणा OPERAND_SIGNED	0x200	/* Opeअक्रम prपूर्णांकed as चिन्हित value */
#घोषणा OPERAND_LENGTH	0x400	/* Opeअक्रम prपूर्णांकed as length (+1) */

काष्ठा s390_opeअक्रम अणु
	अचिन्हित अक्षर bits;	/* The number of bits in the opeअक्रम. */
	अचिन्हित अक्षर shअगरt;	/* The number of bits to shअगरt. */
	अचिन्हित लघु flags;	/* One bit syntax flags. */
पूर्ण;

काष्ठा s390_insn अणु
	जोड़ अणु
		स्थिर अक्षर name[5];
		काष्ठा अणु
			अचिन्हित अक्षर zero;
			अचिन्हित पूर्णांक offset;
		पूर्ण __packed;
	पूर्ण;
	अचिन्हित अक्षर opfrag;
	अचिन्हित अक्षर क्रमmat;
पूर्ण;

काष्ठा s390_opcode_offset अणु
	अचिन्हित अक्षर opcode;
	अचिन्हित अक्षर mask;
	अचिन्हित अक्षर byte;
	अचिन्हित लघु offset;
	अचिन्हित लघु count;
पूर्ण __packed;

क्रमागत अणु
	UNUSED,
	A_8,	/* Access reg. starting at position 8 */
	A_12,	/* Access reg. starting at position 12 */
	A_24,	/* Access reg. starting at position 24 */
	A_28,	/* Access reg. starting at position 28 */
	B_16,	/* Base रेजिस्टर starting at position 16 */
	B_32,	/* Base रेजिस्टर starting at position 32 */
	C_8,	/* Control reg. starting at position 8 */
	C_12,	/* Control reg. starting at position 12 */
	D20_20, /* 20 bit displacement starting at 20 */
	D_20,	/* Displacement starting at position 20 */
	D_36,	/* Displacement starting at position 36 */
	F_8,	/* FPR starting at position 8 */
	F_12,	/* FPR starting at position 12 */
	F_16,	/* FPR starting at position 16 */
	F_24,	/* FPR starting at position 24 */
	F_28,	/* FPR starting at position 28 */
	F_32,	/* FPR starting at position 32 */
	I8_8,	/* 8 bit चिन्हित value starting at 8 */
	I8_32,	/* 8 bit चिन्हित value starting at 32 */
	I16_16, /* 16 bit चिन्हित value starting at 16 */
	I16_32, /* 16 bit चिन्हित value starting at 32 */
	I32_16, /* 32 bit चिन्हित value starting at 16 */
	J12_12, /* 12 bit PC relative offset at 12 */
	J16_16, /* 16 bit PC relative offset at 16 */
	J16_32, /* 16 bit PC relative offset at 32 */
	J24_24, /* 24 bit PC relative offset at 24 */
	J32_16, /* 32 bit PC relative offset at 16 */
	L4_8,	/* 4 bit length starting at position 8 */
	L4_12,	/* 4 bit length starting at position 12 */
	L8_8,	/* 8 bit length starting at position 8 */
	R_8,	/* GPR starting at position 8 */
	R_12,	/* GPR starting at position 12 */
	R_16,	/* GPR starting at position 16 */
	R_24,	/* GPR starting at position 24 */
	R_28,	/* GPR starting at position 28 */
	U4_8,	/* 4 bit अचिन्हित value starting at 8 */
	U4_12,	/* 4 bit अचिन्हित value starting at 12 */
	U4_16,	/* 4 bit अचिन्हित value starting at 16 */
	U4_20,	/* 4 bit अचिन्हित value starting at 20 */
	U4_24,	/* 4 bit अचिन्हित value starting at 24 */
	U4_28,	/* 4 bit अचिन्हित value starting at 28 */
	U4_32,	/* 4 bit अचिन्हित value starting at 32 */
	U4_36,	/* 4 bit अचिन्हित value starting at 36 */
	U8_8,	/* 8 bit अचिन्हित value starting at 8 */
	U8_16,	/* 8 bit अचिन्हित value starting at 16 */
	U8_24,	/* 8 bit अचिन्हित value starting at 24 */
	U8_28,	/* 8 bit अचिन्हित value starting at 28 */
	U8_32,	/* 8 bit अचिन्हित value starting at 32 */
	U12_16, /* 12 bit अचिन्हित value starting at 16 */
	U16_16, /* 16 bit अचिन्हित value starting at 16 */
	U16_32, /* 16 bit अचिन्हित value starting at 32 */
	U32_16, /* 32 bit अचिन्हित value starting at 16 */
	VX_12,	/* Vector index रेजिस्टर starting at position 12 */
	V_8,	/* Vector reg. starting at position 8 */
	V_12,	/* Vector reg. starting at position 12 */
	V_16,	/* Vector reg. starting at position 16 */
	V_32,	/* Vector reg. starting at position 32 */
	X_12,	/* Index रेजिस्टर starting at position 12 */
पूर्ण;

अटल स्थिर काष्ठा s390_opeअक्रम opeअक्रमs[] = अणु
	[UNUSED] = अणु  0,  0, 0 पूर्ण,
	[A_8]	 = अणु  4,  8, OPERAND_AR पूर्ण,
	[A_12]	 = अणु  4, 12, OPERAND_AR पूर्ण,
	[A_24]	 = अणु  4, 24, OPERAND_AR पूर्ण,
	[A_28]	 = अणु  4, 28, OPERAND_AR पूर्ण,
	[B_16]	 = अणु  4, 16, OPERAND_BASE | OPERAND_GPR पूर्ण,
	[B_32]	 = अणु  4, 32, OPERAND_BASE | OPERAND_GPR पूर्ण,
	[C_8]	 = अणु  4,  8, OPERAND_CR पूर्ण,
	[C_12]	 = अणु  4, 12, OPERAND_CR पूर्ण,
	[D20_20] = अणु 20, 20, OPERAND_DISP | OPERAND_SIGNED पूर्ण,
	[D_20]	 = अणु 12, 20, OPERAND_DISP पूर्ण,
	[D_36]	 = अणु 12, 36, OPERAND_DISP पूर्ण,
	[F_8]	 = अणु  4,  8, OPERAND_FPR पूर्ण,
	[F_12]	 = अणु  4, 12, OPERAND_FPR पूर्ण,
	[F_16]	 = अणु  4, 16, OPERAND_FPR पूर्ण,
	[F_24]	 = अणु  4, 24, OPERAND_FPR पूर्ण,
	[F_28]	 = अणु  4, 28, OPERAND_FPR पूर्ण,
	[F_32]	 = अणु  4, 32, OPERAND_FPR पूर्ण,
	[I8_8]	 = अणु  8,  8, OPERAND_SIGNED पूर्ण,
	[I8_32]	 = अणु  8, 32, OPERAND_SIGNED पूर्ण,
	[I16_16] = अणु 16, 16, OPERAND_SIGNED पूर्ण,
	[I16_32] = अणु 16, 32, OPERAND_SIGNED पूर्ण,
	[I32_16] = अणु 32, 16, OPERAND_SIGNED पूर्ण,
	[J12_12] = अणु 12, 12, OPERAND_PCREL पूर्ण,
	[J16_16] = अणु 16, 16, OPERAND_PCREL पूर्ण,
	[J16_32] = अणु 16, 32, OPERAND_PCREL पूर्ण,
	[J24_24] = अणु 24, 24, OPERAND_PCREL पूर्ण,
	[J32_16] = अणु 32, 16, OPERAND_PCREL पूर्ण,
	[L4_8]	 = अणु  4,  8, OPERAND_LENGTH पूर्ण,
	[L4_12]	 = अणु  4, 12, OPERAND_LENGTH पूर्ण,
	[L8_8]	 = अणु  8,  8, OPERAND_LENGTH पूर्ण,
	[R_8]	 = अणु  4,  8, OPERAND_GPR पूर्ण,
	[R_12]	 = अणु  4, 12, OPERAND_GPR पूर्ण,
	[R_16]	 = अणु  4, 16, OPERAND_GPR पूर्ण,
	[R_24]	 = अणु  4, 24, OPERAND_GPR पूर्ण,
	[R_28]	 = अणु  4, 28, OPERAND_GPR पूर्ण,
	[U4_8]	 = अणु  4,  8, 0 पूर्ण,
	[U4_12]	 = अणु  4, 12, 0 पूर्ण,
	[U4_16]	 = अणु  4, 16, 0 पूर्ण,
	[U4_20]	 = अणु  4, 20, 0 पूर्ण,
	[U4_24]	 = अणु  4, 24, 0 पूर्ण,
	[U4_28]	 = अणु  4, 28, 0 पूर्ण,
	[U4_32]	 = अणु  4, 32, 0 पूर्ण,
	[U4_36]	 = अणु  4, 36, 0 पूर्ण,
	[U8_8]	 = अणु  8,  8, 0 पूर्ण,
	[U8_16]	 = अणु  8, 16, 0 पूर्ण,
	[U8_24]	 = अणु  8, 24, 0 पूर्ण,
	[U8_28]	 = अणु  8, 28, 0 पूर्ण,
	[U8_32]	 = अणु  8, 32, 0 पूर्ण,
	[U12_16] = अणु 12, 16, 0 पूर्ण,
	[U16_16] = अणु 16, 16, 0 पूर्ण,
	[U16_32] = अणु 16, 32, 0 पूर्ण,
	[U32_16] = अणु 32, 16, 0 पूर्ण,
	[VX_12]	 = अणु  4, 12, OPERAND_INDEX | OPERAND_VR पूर्ण,
	[V_8]	 = अणु  4,  8, OPERAND_VR पूर्ण,
	[V_12]	 = अणु  4, 12, OPERAND_VR पूर्ण,
	[V_16]	 = अणु  4, 16, OPERAND_VR पूर्ण,
	[V_32]	 = अणु  4, 32, OPERAND_VR पूर्ण,
	[X_12]	 = अणु  4, 12, OPERAND_INDEX | OPERAND_GPR पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर क्रमmats[][6] = अणु
	[INSTR_E]	     = अणु 0, 0, 0, 0, 0, 0 पूर्ण,
	[INSTR_IE_UU]	     = अणु U4_24, U4_28, 0, 0, 0, 0 पूर्ण,
	[INSTR_MII_UPP]	     = अणु U4_8, J12_12, J24_24 पूर्ण,
	[INSTR_RIE_R0IU]     = अणु R_8, I16_16, U4_32, 0, 0, 0 पूर्ण,
	[INSTR_RIE_R0UU]     = अणु R_8, U16_16, U4_32, 0, 0, 0 पूर्ण,
	[INSTR_RIE_RRI0]     = अणु R_8, R_12, I16_16, 0, 0, 0 पूर्ण,
	[INSTR_RIE_RRP]	     = अणु R_8, R_12, J16_16, 0, 0, 0 पूर्ण,
	[INSTR_RIE_RRPU]     = अणु R_8, R_12, U4_32, J16_16, 0, 0 पूर्ण,
	[INSTR_RIE_RRUUU]    = अणु R_8, R_12, U8_16, U8_24, U8_32, 0 पूर्ण,
	[INSTR_RIE_RUI0]     = अणु R_8, I16_16, U4_12, 0, 0, 0 पूर्ण,
	[INSTR_RIE_RUPI]     = अणु R_8, I8_32, U4_12, J16_16, 0, 0 पूर्ण,
	[INSTR_RIE_RUPU]     = अणु R_8, U8_32, U4_12, J16_16, 0, 0 पूर्ण,
	[INSTR_RIL_RI]	     = अणु R_8, I32_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_RIL_RP]	     = अणु R_8, J32_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_RIL_RU]	     = अणु R_8, U32_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_RIL_UP]	     = अणु U4_8, J32_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_RIS_RURDI]    = अणु R_8, I8_32, U4_12, D_20, B_16, 0 पूर्ण,
	[INSTR_RIS_RURDU]    = अणु R_8, U8_32, U4_12, D_20, B_16, 0 पूर्ण,
	[INSTR_RI_RI]	     = अणु R_8, I16_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_RI_RP]	     = अणु R_8, J16_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_RI_RU]	     = अणु R_8, U16_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_RI_UP]	     = अणु U4_8, J16_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_00]	     = अणु 0, 0, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_AA]	     = अणु A_24, A_28, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_AR]	     = अणु A_24, R_28, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_F0]	     = अणु F_24, 0, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_FF]	     = अणु F_24, F_28, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_FR]	     = अणु F_24, R_28, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_R0]	     = अणु R_24, 0, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_RA]	     = अणु R_24, A_28, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_RF]	     = अणु R_24, F_28, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRE_RR]	     = अणु R_24, R_28, 0, 0, 0, 0 पूर्ण,
	[INSTR_RRF_0UFF]     = अणु F_24, F_28, U4_20, 0, 0, 0 पूर्ण,
	[INSTR_RRF_0URF]     = अणु R_24, F_28, U4_20, 0, 0, 0 पूर्ण,
	[INSTR_RRF_F0FF]     = अणु F_16, F_24, F_28, 0, 0, 0 पूर्ण,
	[INSTR_RRF_F0FF2]    = अणु F_24, F_16, F_28, 0, 0, 0 पूर्ण,
	[INSTR_RRF_F0FR]     = अणु F_24, F_16, R_28, 0, 0, 0 पूर्ण,
	[INSTR_RRF_FFRU]     = अणु F_24, F_16, R_28, U4_20, 0, 0 पूर्ण,
	[INSTR_RRF_FUFF]     = अणु F_24, F_16, F_28, U4_20, 0, 0 पूर्ण,
	[INSTR_RRF_FUFF2]    = अणु F_24, F_28, F_16, U4_20, 0, 0 पूर्ण,
	[INSTR_RRF_R0RR]     = अणु R_24, R_16, R_28, 0, 0, 0 पूर्ण,
	[INSTR_RRF_R0RR2]    = अणु R_24, R_28, R_16, 0, 0, 0 पूर्ण,
	[INSTR_RRF_RURR]     = अणु R_24, R_28, R_16, U4_20, 0, 0 पूर्ण,
	[INSTR_RRF_RURR2]    = अणु R_24, R_16, R_28, U4_20, 0, 0 पूर्ण,
	[INSTR_RRF_U0FF]     = अणु F_24, U4_16, F_28, 0, 0, 0 पूर्ण,
	[INSTR_RRF_U0RF]     = अणु R_24, U4_16, F_28, 0, 0, 0 पूर्ण,
	[INSTR_RRF_U0RR]     = अणु R_24, R_28, U4_16, 0, 0, 0 पूर्ण,
	[INSTR_RRF_URR]	     = अणु R_24, R_28, U8_16, 0, 0, 0 पूर्ण,
	[INSTR_RRF_UUFF]     = अणु F_24, U4_16, F_28, U4_20, 0, 0 पूर्ण,
	[INSTR_RRF_UUFR]     = अणु F_24, U4_16, R_28, U4_20, 0, 0 पूर्ण,
	[INSTR_RRF_UURF]     = अणु R_24, U4_16, F_28, U4_20, 0, 0 पूर्ण,
	[INSTR_RRS_RRRDU]    = अणु R_8, R_12, U4_32, D_20, B_16 पूर्ण,
	[INSTR_RR_FF]	     = अणु F_8, F_12, 0, 0, 0, 0 पूर्ण,
	[INSTR_RR_R0]	     = अणु R_8,  0, 0, 0, 0, 0 पूर्ण,
	[INSTR_RR_RR]	     = अणु R_8, R_12, 0, 0, 0, 0 पूर्ण,
	[INSTR_RR_U0]	     = अणु U8_8,	0, 0, 0, 0, 0 पूर्ण,
	[INSTR_RR_UR]	     = अणु U4_8, R_12, 0, 0, 0, 0 पूर्ण,
	[INSTR_RSI_RRP]	     = अणु R_8, R_12, J16_16, 0, 0, 0 पूर्ण,
	[INSTR_RSL_LRDFU]    = अणु F_32, D_20, L8_8, B_16, U4_36, 0 पूर्ण,
	[INSTR_RSL_R0RD]     = अणु D_20, L4_8, B_16, 0, 0, 0 पूर्ण,
	[INSTR_RSY_AARD]     = अणु A_8, A_12, D20_20, B_16, 0, 0 पूर्ण,
	[INSTR_RSY_CCRD]     = अणु C_8, C_12, D20_20, B_16, 0, 0 पूर्ण,
	[INSTR_RSY_RDRU]     = अणु R_8, D20_20, B_16, U4_12, 0, 0 पूर्ण,
	[INSTR_RSY_RRRD]     = अणु R_8, R_12, D20_20, B_16, 0, 0 पूर्ण,
	[INSTR_RSY_RURD]     = अणु R_8, U4_12, D20_20, B_16, 0, 0 पूर्ण,
	[INSTR_RSY_RURD2]    = अणु R_8, D20_20, B_16, U4_12, 0, 0 पूर्ण,
	[INSTR_RS_AARD]	     = अणु A_8, A_12, D_20, B_16, 0, 0 पूर्ण,
	[INSTR_RS_CCRD]	     = अणु C_8, C_12, D_20, B_16, 0, 0 पूर्ण,
	[INSTR_RS_R0RD]	     = अणु R_8, D_20, B_16, 0, 0, 0 पूर्ण,
	[INSTR_RS_RRRD]	     = अणु R_8, R_12, D_20, B_16, 0, 0 पूर्ण,
	[INSTR_RS_RURD]	     = अणु R_8, U4_12, D_20, B_16, 0, 0 पूर्ण,
	[INSTR_RXE_FRRD]     = अणु F_8, D_20, X_12, B_16, 0, 0 पूर्ण,
	[INSTR_RXE_RRRDU]    = अणु R_8, D_20, X_12, B_16, U4_32, 0 पूर्ण,
	[INSTR_RXF_FRRDF]    = अणु F_32, F_8, D_20, X_12, B_16, 0 पूर्ण,
	[INSTR_RXY_FRRD]     = अणु F_8, D20_20, X_12, B_16, 0, 0 पूर्ण,
	[INSTR_RXY_RRRD]     = अणु R_8, D20_20, X_12, B_16, 0, 0 पूर्ण,
	[INSTR_RXY_URRD]     = अणु U4_8, D20_20, X_12, B_16, 0, 0 पूर्ण,
	[INSTR_RX_FRRD]	     = अणु F_8, D_20, X_12, B_16, 0, 0 पूर्ण,
	[INSTR_RX_RRRD]	     = अणु R_8, D_20, X_12, B_16, 0, 0 पूर्ण,
	[INSTR_RX_URRD]	     = अणु U4_8, D_20, X_12, B_16, 0, 0 पूर्ण,
	[INSTR_SIL_RDI]	     = अणु D_20, B_16, I16_32, 0, 0, 0 पूर्ण,
	[INSTR_SIL_RDU]	     = अणु D_20, B_16, U16_32, 0, 0, 0 पूर्ण,
	[INSTR_SIY_IRD]	     = अणु D20_20, B_16, I8_8, 0, 0, 0 पूर्ण,
	[INSTR_SIY_URD]	     = अणु D20_20, B_16, U8_8, 0, 0, 0 पूर्ण,
	[INSTR_SI_RD]	     = अणु D_20, B_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_SI_URD]	     = अणु D_20, B_16, U8_8, 0, 0, 0 पूर्ण,
	[INSTR_SMI_U0RDP]    = अणु U4_8, J16_32, D_20, B_16, 0, 0 पूर्ण,
	[INSTR_SSE_RDRD]     = अणु D_20, B_16, D_36, B_32, 0, 0 पूर्ण,
	[INSTR_SSF_RRDRD]    = अणु D_20, B_16, D_36, B_32, R_8, 0 पूर्ण,
	[INSTR_SSF_RRDRD2]   = अणु R_8, D_20, B_16, D_36, B_32, 0 पूर्ण,
	[INSTR_SS_L0RDRD]    = अणु D_20, L8_8, B_16, D_36, B_32, 0 पूर्ण,
	[INSTR_SS_L2RDRD]    = अणु D_20, B_16, D_36, L8_8, B_32, 0 पूर्ण,
	[INSTR_SS_LIRDRD]    = अणु D_20, L4_8, B_16, D_36, B_32, U4_12 पूर्ण,
	[INSTR_SS_LLRDRD]    = अणु D_20, L4_8, B_16, D_36, L4_12, B_32 पूर्ण,
	[INSTR_SS_RRRDRD]    = अणु D_20, R_8, B_16, D_36, B_32, R_12 पूर्ण,
	[INSTR_SS_RRRDRD2]   = अणु R_8, D_20, B_16, R_12, D_36, B_32 पूर्ण,
	[INSTR_SS_RRRDRD3]   = अणु R_8, R_12, D_20, B_16, D_36, B_32 पूर्ण,
	[INSTR_S_00]	     = अणु 0, 0, 0, 0, 0, 0 पूर्ण,
	[INSTR_S_RD]	     = अणु D_20, B_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_VRI_V0IU]     = अणु V_8, I16_16, U4_32, 0, 0, 0 पूर्ण,
	[INSTR_VRI_V0U]	     = अणु V_8, U16_16, 0, 0, 0, 0 पूर्ण,
	[INSTR_VRI_V0UU2]    = अणु V_8, U16_16, U4_32, 0, 0, 0 पूर्ण,
	[INSTR_VRI_V0UUU]    = अणु V_8, U8_16, U8_24, U4_32, 0, 0 पूर्ण,
	[INSTR_VRI_VR0UU]    = अणु V_8, R_12, U8_28, U4_24, 0, 0 पूर्ण,
	[INSTR_VRI_VVUU]     = अणु V_8, V_12, U16_16, U4_32, 0, 0 पूर्ण,
	[INSTR_VRI_VVUUU]    = अणु V_8, V_12, U12_16, U4_32, U4_28, 0 पूर्ण,
	[INSTR_VRI_VVUUU2]   = अणु V_8, V_12, U8_28, U8_16, U4_24, 0 पूर्ण,
	[INSTR_VRI_VVV0U]    = अणु V_8, V_12, V_16, U8_24, 0, 0 पूर्ण,
	[INSTR_VRI_VVV0UU]   = अणु V_8, V_12, V_16, U8_24, U4_32, 0 पूर्ण,
	[INSTR_VRI_VVV0UU2]  = अणु V_8, V_12, V_16, U8_28, U4_24, 0 पूर्ण,
	[INSTR_VRR_0V]	     = अणु V_12, 0, 0, 0, 0, 0 पूर्ण,
	[INSTR_VRR_0VV0U]    = अणु V_12, V_16, U4_24, 0, 0, 0 पूर्ण,
	[INSTR_VRR_RV0UU]    = अणु R_8, V_12, U4_24, U4_28, 0, 0 पूर्ण,
	[INSTR_VRR_VRR]	     = अणु V_8, R_12, R_16, 0, 0, 0 पूर्ण,
	[INSTR_VRR_VV]	     = अणु V_8, V_12, 0, 0, 0, 0 पूर्ण,
	[INSTR_VRR_VV0U]     = अणु V_8, V_12, U4_32, 0, 0, 0 पूर्ण,
	[INSTR_VRR_VV0U0U]   = अणु V_8, V_12, U4_32, U4_24, 0, 0 पूर्ण,
	[INSTR_VRR_VV0UU2]   = अणु V_8, V_12, U4_32, U4_28, 0, 0 पूर्ण,
	[INSTR_VRR_VV0UUU]   = अणु V_8, V_12, U4_32, U4_28, U4_24, 0 पूर्ण,
	[INSTR_VRR_VVV]	     = अणु V_8, V_12, V_16, 0, 0, 0 पूर्ण,
	[INSTR_VRR_VVV0U]    = अणु V_8, V_12, V_16, U4_32, 0, 0 पूर्ण,
	[INSTR_VRR_VVV0U0U]  = अणु V_8, V_12, V_16, U4_32, U4_24, 0 पूर्ण,
	[INSTR_VRR_VVV0UU]   = अणु V_8, V_12, V_16, U4_32, U4_28, 0 पूर्ण,
	[INSTR_VRR_VVV0UUU]  = अणु V_8, V_12, V_16, U4_32, U4_28, U4_24 पूर्ण,
	[INSTR_VRR_VVV0V]    = अणु V_8, V_12, V_16, V_32, 0, 0 पूर्ण,
	[INSTR_VRR_VVVU0UV]  = अणु V_8, V_12, V_16, V_32, U4_28, U4_20 पूर्ण,
	[INSTR_VRR_VVVU0V]   = अणु V_8, V_12, V_16, V_32, U4_20, 0 पूर्ण,
	[INSTR_VRR_VVVUU0V]  = अणु V_8, V_12, V_16, V_32, U4_20, U4_24 पूर्ण,
	[INSTR_VRS_RRDV]     = अणु V_32, R_12, D_20, B_16, 0, 0 पूर्ण,
	[INSTR_VRS_RVRDU]    = अणु R_8, V_12, D_20, B_16, U4_32, 0 पूर्ण,
	[INSTR_VRS_VRRD]     = अणु V_8, R_12, D_20, B_16, 0, 0 पूर्ण,
	[INSTR_VRS_VRRDU]    = अणु V_8, R_12, D_20, B_16, U4_32, 0 पूर्ण,
	[INSTR_VRS_VVRDU]    = अणु V_8, V_12, D_20, B_16, U4_32, 0 पूर्ण,
	[INSTR_VRV_VVXRDU]   = अणु V_8, D_20, VX_12, B_16, U4_32, 0 पूर्ण,
	[INSTR_VRX_VRRDU]    = अणु V_8, D_20, X_12, B_16, U4_32, 0 पूर्ण,
	[INSTR_VRX_VV]	     = अणु V_8, V_12, 0, 0, 0, 0 पूर्ण,
	[INSTR_VSI_URDV]     = अणु V_32, D_20, B_16, U8_8, 0, 0 पूर्ण,
पूर्ण;

अटल अक्षर दीर्घ_insn_name[][7] = LONG_INSN_INITIALIZER;
अटल काष्ठा s390_insn opcode[] = OPCODE_TABLE_INITIALIZER;
अटल काष्ठा s390_opcode_offset opcode_offset[] = OPCODE_OFFSET_INITIALIZER;

/* Extracts an opeअक्रम value from an inकाष्ठाion.  */
अटल अचिन्हित पूर्णांक extract_opeअक्रम(अचिन्हित अक्षर *code,
				    स्थिर काष्ठा s390_opeअक्रम *opeअक्रम)
अणु
	अचिन्हित अक्षर *cp;
	अचिन्हित पूर्णांक val;
	पूर्णांक bits;

	/* Extract fragments of the opeअक्रम byte क्रम byte.  */
	cp = code + opeअक्रम->shअगरt / 8;
	bits = (opeअक्रम->shअगरt & 7) + opeअक्रम->bits;
	val = 0;
	करो अणु
		val <<= 8;
		val |= (अचिन्हित पूर्णांक) *cp++;
		bits -= 8;
	पूर्ण जबतक (bits > 0);
	val >>= -bits;
	val &= ((1U << (opeअक्रम->bits - 1)) << 1) - 1;

	/* Check क्रम special दीर्घ displacement हाल.  */
	अगर (opeअक्रम->bits == 20 && opeअक्रम->shअगरt == 20)
		val = (val & 0xff) << 12 | (val & 0xfff00) >> 8;

	/* Check क्रम रेजिस्टर extensions bits क्रम vector रेजिस्टरs. */
	अगर (opeअक्रम->flags & OPERAND_VR) अणु
		अगर (opeअक्रम->shअगरt == 8)
			val |= (code[4] & 8) << 1;
		अन्यथा अगर (opeअक्रम->shअगरt == 12)
			val |= (code[4] & 4) << 2;
		अन्यथा अगर (opeअक्रम->shअगरt == 16)
			val |= (code[4] & 2) << 3;
		अन्यथा अगर (opeअक्रम->shअगरt == 32)
			val |= (code[4] & 1) << 4;
	पूर्ण

	/* Sign extend value अगर the opeअक्रम is चिन्हित or pc relative.  */
	अगर ((opeअक्रम->flags & (OPERAND_SIGNED | OPERAND_PCREL)) &&
	    (val & (1U << (opeअक्रम->bits - 1))))
		val |= (-1U << (opeअक्रम->bits - 1)) << 1;

	/* Double value अगर the opeअक्रम is pc relative.	*/
	अगर (opeअक्रम->flags & OPERAND_PCREL)
		val <<= 1;

	/* Length x in an inकाष्ठाions has real length x + 1.  */
	अगर (opeअक्रम->flags & OPERAND_LENGTH)
		val++;
	वापस val;
पूर्ण

काष्ठा s390_insn *find_insn(अचिन्हित अक्षर *code)
अणु
	काष्ठा s390_opcode_offset *entry;
	काष्ठा s390_insn *insn;
	अचिन्हित अक्षर opfrag;
	पूर्णांक i;

	/* Search the opcode offset table to find an entry which
	 * matches the beginning of the opcode. If there is no match
	 * the last entry will be used, which is the शेष entry क्रम
	 * unknown inकाष्ठाions as well as 1-byte opcode inकाष्ठाions.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(opcode_offset); i++) अणु
		entry = &opcode_offset[i];
		अगर (entry->opcode == code[0])
			अवरोध;
	पूर्ण

	opfrag = *(code + entry->byte) & entry->mask;

	insn = &opcode[entry->offset];
	क्रम (i = 0; i < entry->count; i++) अणु
		अगर (insn->opfrag == opfrag)
			वापस insn;
		insn++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक prपूर्णांक_insn(अक्षर *buffer, अचिन्हित अक्षर *code, अचिन्हित दीर्घ addr)
अणु
	काष्ठा s390_insn *insn;
	स्थिर अचिन्हित अक्षर *ops;
	स्थिर काष्ठा s390_opeअक्रम *opeअक्रम;
	अचिन्हित पूर्णांक value;
	अक्षर separator;
	अक्षर *ptr;
	पूर्णांक i;

	ptr = buffer;
	insn = find_insn(code);
	अगर (insn) अणु
		अगर (insn->zero == 0)
			ptr += प्र_लिखो(ptr, "%.7s\t",
				       दीर्घ_insn_name[insn->offset]);
		अन्यथा
			ptr += प्र_लिखो(ptr, "%.5s\t", insn->name);
		/* Extract the opeअक्रमs. */
		separator = 0;
		क्रम (ops = क्रमmats[insn->क्रमmat], i = 0;
		     *ops != 0 && i < 6; ops++, i++) अणु
			opeअक्रम = opeअक्रमs + *ops;
			value = extract_opeअक्रम(code, opeअक्रम);
			अगर ((opeअक्रम->flags & OPERAND_INDEX)  && value == 0)
				जारी;
			अगर ((opeअक्रम->flags & OPERAND_BASE) &&
			    value == 0 && separator == '(') अणु
				separator = ',';
				जारी;
			पूर्ण
			अगर (separator)
				ptr += प्र_लिखो(ptr, "%c", separator);
			अगर (opeअक्रम->flags & OPERAND_GPR)
				ptr += प्र_लिखो(ptr, "%%r%i", value);
			अन्यथा अगर (opeअक्रम->flags & OPERAND_FPR)
				ptr += प्र_लिखो(ptr, "%%f%i", value);
			अन्यथा अगर (opeअक्रम->flags & OPERAND_AR)
				ptr += प्र_लिखो(ptr, "%%a%i", value);
			अन्यथा अगर (opeअक्रम->flags & OPERAND_CR)
				ptr += प्र_लिखो(ptr, "%%c%i", value);
			अन्यथा अगर (opeअक्रम->flags & OPERAND_VR)
				ptr += प्र_लिखो(ptr, "%%v%i", value);
			अन्यथा अगर (opeअक्रम->flags & OPERAND_PCREL) अणु
				व्योम *pcrel = (व्योम *)((पूर्णांक)value + addr);

				ptr += प्र_लिखो(ptr, "%px", pcrel);
			पूर्ण अन्यथा अगर (opeअक्रम->flags & OPERAND_SIGNED)
				ptr += प्र_लिखो(ptr, "%i", value);
			अन्यथा
				ptr += प्र_लिखो(ptr, "%u", value);
			अगर (opeअक्रम->flags & OPERAND_DISP)
				separator = '(';
			अन्यथा अगर (opeअक्रम->flags & OPERAND_BASE) अणु
				ptr += प्र_लिखो(ptr, ")");
				separator = ',';
			पूर्ण अन्यथा
				separator = ',';
		पूर्ण
	पूर्ण अन्यथा
		ptr += प्र_लिखो(ptr, "unknown");
	वापस (पूर्णांक) (ptr - buffer);
पूर्ण

अटल पूर्णांक copy_from_regs(काष्ठा pt_regs *regs, व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	अगर (user_mode(regs)) अणु
		अगर (copy_from_user(dst, (अक्षर __user *)src, len))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (copy_from_kernel_nofault(dst, src, len))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

व्योम show_code(काष्ठा pt_regs *regs)
अणु
	अक्षर *mode = user_mode(regs) ? "User" : "Krnl";
	अचिन्हित अक्षर code[64];
	अक्षर buffer[128], *ptr;
	अचिन्हित दीर्घ addr;
	पूर्णांक start, end, opsize, hops, i;

	/* Get a snapshot of the 64 bytes surrounding the fault address. */
	क्रम (start = 32; start && regs->psw.addr >= 34 - start; start -= 2) अणु
		addr = regs->psw.addr - 34 + start;
		अगर (copy_from_regs(regs, code + start - 2, (व्योम *)addr, 2))
			अवरोध;
	पूर्ण
	क्रम (end = 32; end < 64; end += 2) अणु
		addr = regs->psw.addr + end - 32;
		अगर (copy_from_regs(regs, code + end, (व्योम *)addr, 2))
			अवरोध;
	पूर्ण
	/* Code snapshot useable ? */
	अगर ((regs->psw.addr & 1) || start >= end) अणु
		prपूर्णांकk("%s Code: Bad PSW.\n", mode);
		वापस;
	पूर्ण
	/* Find a starting poपूर्णांक क्रम the disassembly. */
	जबतक (start < 32) अणु
		क्रम (i = 0, hops = 0; start + i < 32 && hops < 3; hops++) अणु
			अगर (!find_insn(code + start + i))
				अवरोध;
			i += insn_length(code[start + i]);
		पूर्ण
		अगर (start + i == 32)
			/* Looks good, sequence ends at PSW. */
			अवरोध;
		start += 2;
	पूर्ण
	/* Decode the inकाष्ठाions. */
	ptr = buffer;
	ptr += प्र_लिखो(ptr, "%s Code:", mode);
	hops = 0;
	जबतक (start < end && hops < 8) अणु
		opsize = insn_length(code[start]);
		अगर  (start + opsize == 32)
			*ptr++ = '#';
		अन्यथा अगर (start == 32)
			*ptr++ = '>';
		अन्यथा
			*ptr++ = ' ';
		addr = regs->psw.addr + start - 32;
		ptr += प्र_लिखो(ptr, "%px: ", (व्योम *)addr);
		अगर (start + opsize >= end)
			अवरोध;
		क्रम (i = 0; i < opsize; i++)
			ptr += प्र_लिखो(ptr, "%02x", code[start + i]);
		*ptr++ = '\t';
		अगर (i < 6)
			*ptr++ = '\t';
		ptr += prपूर्णांक_insn(ptr, code + start, addr);
		start += opsize;
		pr_cont("%s", buffer);
		ptr = buffer;
		ptr += प्र_लिखो(ptr, "\n          ");
		hops++;
	पूर्ण
	pr_cont("\n");
पूर्ण

व्योम prपूर्णांक_fn_code(अचिन्हित अक्षर *code, अचिन्हित दीर्घ len)
अणु
	अक्षर buffer[128], *ptr;
	पूर्णांक opsize, i;

	जबतक (len) अणु
		ptr = buffer;
		opsize = insn_length(*code);
		अगर (opsize > len)
			अवरोध;
		ptr += प्र_लिखो(ptr, "%px: ", code);
		क्रम (i = 0; i < opsize; i++)
			ptr += प्र_लिखो(ptr, "%02x", code[i]);
		*ptr++ = '\t';
		अगर (i < 4)
			*ptr++ = '\t';
		ptr += prपूर्णांक_insn(ptr, code, (अचिन्हित दीर्घ) code);
		*ptr++ = '\n';
		*ptr++ = 0;
		prपूर्णांकk("%s", buffer);
		code += opsize;
		len -= opsize;
	पूर्ण
पूर्ण

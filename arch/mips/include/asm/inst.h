<शैली गुरु>
/*
 * Format of an inकाष्ठाion in memory.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 2000 by Ralf Baechle
 * Copyright (C) 2006 by Thiemo Seufer
 */
#अगर_अघोषित _ASM_INST_H
#घोषणा _ASM_INST_H

#समावेश <uapi/यंत्र/inst.h>

/* HACHACHAHCAHC ...  */

/* In हाल some other massaging is needed, keep MIPSInst as wrapper */

#घोषणा MIPSInst(x) x

#घोषणा I_OPCODE_SFT	26
#घोषणा MIPSInst_OPCODE(x) (MIPSInst(x) >> I_OPCODE_SFT)

#घोषणा I_JTARGET_SFT	0
#घोषणा MIPSInst_JTARGET(x) (MIPSInst(x) & 0x03ffffff)

#घोषणा I_RS_SFT	21
#घोषणा MIPSInst_RS(x) ((MIPSInst(x) & 0x03e00000) >> I_RS_SFT)

#घोषणा I_RT_SFT	16
#घोषणा MIPSInst_RT(x) ((MIPSInst(x) & 0x001f0000) >> I_RT_SFT)

#घोषणा I_IMM_SFT	0
#घोषणा MIPSInst_SIMM(x) ((पूर्णांक)((लघु)(MIPSInst(x) & 0xffff)))
#घोषणा MIPSInst_UIMM(x) (MIPSInst(x) & 0xffff)

#घोषणा I_CACHEOP_SFT	18
#घोषणा MIPSInst_CACHEOP(x) ((MIPSInst(x) & 0x001c0000) >> I_CACHEOP_SFT)

#घोषणा I_CACHESEL_SFT	16
#घोषणा MIPSInst_CACHESEL(x) ((MIPSInst(x) & 0x00030000) >> I_CACHESEL_SFT)

#घोषणा I_RD_SFT	11
#घोषणा MIPSInst_RD(x) ((MIPSInst(x) & 0x0000f800) >> I_RD_SFT)

#घोषणा I_RE_SFT	6
#घोषणा MIPSInst_RE(x) ((MIPSInst(x) & 0x000007c0) >> I_RE_SFT)

#घोषणा I_FUNC_SFT	0
#घोषणा MIPSInst_FUNC(x) (MIPSInst(x) & 0x0000003f)

#घोषणा I_FFMT_SFT	21
#घोषणा MIPSInst_FFMT(x) ((MIPSInst(x) & 0x01e00000) >> I_FFMT_SFT)

#घोषणा I_FT_SFT	16
#घोषणा MIPSInst_FT(x) ((MIPSInst(x) & 0x001f0000) >> I_FT_SFT)

#घोषणा I_FS_SFT	11
#घोषणा MIPSInst_FS(x) ((MIPSInst(x) & 0x0000f800) >> I_FS_SFT)

#घोषणा I_FD_SFT	6
#घोषणा MIPSInst_FD(x) ((MIPSInst(x) & 0x000007c0) >> I_FD_SFT)

#घोषणा I_FR_SFT	21
#घोषणा MIPSInst_FR(x) ((MIPSInst(x) & 0x03e00000) >> I_FR_SFT)

#घोषणा I_FMA_FUNC_SFT	3
#घोषणा MIPSInst_FMA_FUNC(x) ((MIPSInst(x) & 0x00000038) >> I_FMA_FUNC_SFT)

#घोषणा I_FMA_FFMT_SFT	0
#घोषणा MIPSInst_FMA_FFMT(x) (MIPSInst(x) & 0x00000007)

प्रकार अचिन्हित पूर्णांक mips_inकाष्ठाion;

/* microMIPS inकाष्ठाion decode काष्ठाure. Do NOT export!!! */
काष्ठा mm_decoded_insn अणु
	mips_inकाष्ठाion insn;
	mips_inकाष्ठाion next_insn;
	पूर्णांक pc_inc;
	पूर्णांक next_pc_inc;
	पूर्णांक micro_mips_mode;
पूर्ण;

/* Recode table from 16-bit रेजिस्टर notation to 32-bit GPR. Do NOT export!!! */
बाह्य स्थिर पूर्णांक reg16to32[];

#पूर्ण_अगर /* _ASM_INST_H */

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/csr.h>

#घोषणा INSN_MATCH_LB			0x3
#घोषणा INSN_MASK_LB			0x707f
#घोषणा INSN_MATCH_LH			0x1003
#घोषणा INSN_MASK_LH			0x707f
#घोषणा INSN_MATCH_LW			0x2003
#घोषणा INSN_MASK_LW			0x707f
#घोषणा INSN_MATCH_LD			0x3003
#घोषणा INSN_MASK_LD			0x707f
#घोषणा INSN_MATCH_LBU			0x4003
#घोषणा INSN_MASK_LBU			0x707f
#घोषणा INSN_MATCH_LHU			0x5003
#घोषणा INSN_MASK_LHU			0x707f
#घोषणा INSN_MATCH_LWU			0x6003
#घोषणा INSN_MASK_LWU			0x707f
#घोषणा INSN_MATCH_SB			0x23
#घोषणा INSN_MASK_SB			0x707f
#घोषणा INSN_MATCH_SH			0x1023
#घोषणा INSN_MASK_SH			0x707f
#घोषणा INSN_MATCH_SW			0x2023
#घोषणा INSN_MASK_SW			0x707f
#घोषणा INSN_MATCH_SD			0x3023
#घोषणा INSN_MASK_SD			0x707f

#घोषणा INSN_MATCH_FLW			0x2007
#घोषणा INSN_MASK_FLW			0x707f
#घोषणा INSN_MATCH_FLD			0x3007
#घोषणा INSN_MASK_FLD			0x707f
#घोषणा INSN_MATCH_FLQ			0x4007
#घोषणा INSN_MASK_FLQ			0x707f
#घोषणा INSN_MATCH_FSW			0x2027
#घोषणा INSN_MASK_FSW			0x707f
#घोषणा INSN_MATCH_FSD			0x3027
#घोषणा INSN_MASK_FSD			0x707f
#घोषणा INSN_MATCH_FSQ			0x4027
#घोषणा INSN_MASK_FSQ			0x707f

#घोषणा INSN_MATCH_C_LD			0x6000
#घोषणा INSN_MASK_C_LD			0xe003
#घोषणा INSN_MATCH_C_SD			0xe000
#घोषणा INSN_MASK_C_SD			0xe003
#घोषणा INSN_MATCH_C_LW			0x4000
#घोषणा INSN_MASK_C_LW			0xe003
#घोषणा INSN_MATCH_C_SW			0xc000
#घोषणा INSN_MASK_C_SW			0xe003
#घोषणा INSN_MATCH_C_LDSP		0x6002
#घोषणा INSN_MASK_C_LDSP		0xe003
#घोषणा INSN_MATCH_C_SDSP		0xe002
#घोषणा INSN_MASK_C_SDSP		0xe003
#घोषणा INSN_MATCH_C_LWSP		0x4002
#घोषणा INSN_MASK_C_LWSP		0xe003
#घोषणा INSN_MATCH_C_SWSP		0xc002
#घोषणा INSN_MASK_C_SWSP		0xe003

#घोषणा INSN_MATCH_C_FLD		0x2000
#घोषणा INSN_MASK_C_FLD			0xe003
#घोषणा INSN_MATCH_C_FLW		0x6000
#घोषणा INSN_MASK_C_FLW			0xe003
#घोषणा INSN_MATCH_C_FSD		0xa000
#घोषणा INSN_MASK_C_FSD			0xe003
#घोषणा INSN_MATCH_C_FSW		0xe000
#घोषणा INSN_MASK_C_FSW			0xe003
#घोषणा INSN_MATCH_C_FLDSP		0x2002
#घोषणा INSN_MASK_C_FLDSP		0xe003
#घोषणा INSN_MATCH_C_FSDSP		0xa002
#घोषणा INSN_MASK_C_FSDSP		0xe003
#घोषणा INSN_MATCH_C_FLWSP		0x6002
#घोषणा INSN_MASK_C_FLWSP		0xe003
#घोषणा INSN_MATCH_C_FSWSP		0xe002
#घोषणा INSN_MASK_C_FSWSP		0xe003

#घोषणा INSN_LEN(insn)			((((insn) & 0x3) < 0x3) ? 2 : 4)

#अगर defined(CONFIG_64BIT)
#घोषणा LOG_REGBYTES			3
#घोषणा XLEN				64
#अन्यथा
#घोषणा LOG_REGBYTES			2
#घोषणा XLEN				32
#पूर्ण_अगर
#घोषणा REGBYTES			(1 << LOG_REGBYTES)
#घोषणा XLEN_MINUS_16			((XLEN) - 16)

#घोषणा SH_RD				7
#घोषणा SH_RS1				15
#घोषणा SH_RS2				20
#घोषणा SH_RS2C				2

#घोषणा RV_X(x, s, n)			(((x) >> (s)) & ((1 << (n)) - 1))
#घोषणा RVC_LW_IMM(x)			((RV_X(x, 6, 1) << 2) | \
					 (RV_X(x, 10, 3) << 3) | \
					 (RV_X(x, 5, 1) << 6))
#घोषणा RVC_LD_IMM(x)			((RV_X(x, 10, 3) << 3) | \
					 (RV_X(x, 5, 2) << 6))
#घोषणा RVC_LWSP_IMM(x)			((RV_X(x, 4, 3) << 2) | \
					 (RV_X(x, 12, 1) << 5) | \
					 (RV_X(x, 2, 2) << 6))
#घोषणा RVC_LDSP_IMM(x)			((RV_X(x, 5, 2) << 3) | \
					 (RV_X(x, 12, 1) << 5) | \
					 (RV_X(x, 2, 3) << 6))
#घोषणा RVC_SWSP_IMM(x)			((RV_X(x, 9, 4) << 2) | \
					 (RV_X(x, 7, 2) << 6))
#घोषणा RVC_SDSP_IMM(x)			((RV_X(x, 10, 3) << 3) | \
					 (RV_X(x, 7, 3) << 6))
#घोषणा RVC_RS1S(insn)			(8 + RV_X(insn, SH_RD, 3))
#घोषणा RVC_RS2S(insn)			(8 + RV_X(insn, SH_RS2C, 3))
#घोषणा RVC_RS2(insn)			RV_X(insn, SH_RS2C, 5)

#घोषणा SHIFT_RIGHT(x, y)		\
	((y) < 0 ? ((x) << -(y)) : ((x) >> (y)))

#घोषणा REG_MASK			\
	((1 << (5 + LOG_REGBYTES)) - (1 << LOG_REGBYTES))

#घोषणा REG_OFFSET(insn, pos)		\
	(SHIFT_RIGHT((insn), (pos) - LOG_REGBYTES) & REG_MASK)

#घोषणा REG_PTR(insn, pos, regs)	\
	(uदीर्घ *)((uदीर्घ)(regs) + REG_OFFSET(insn, pos))

#घोषणा GET_RM(insn)			(((insn) >> 12) & 7)

#घोषणा GET_RS1(insn, regs)		(*REG_PTR(insn, SH_RS1, regs))
#घोषणा GET_RS2(insn, regs)		(*REG_PTR(insn, SH_RS2, regs))
#घोषणा GET_RS1S(insn, regs)		(*REG_PTR(RVC_RS1S(insn), 0, regs))
#घोषणा GET_RS2S(insn, regs)		(*REG_PTR(RVC_RS2S(insn), 0, regs))
#घोषणा GET_RS2C(insn, regs)		(*REG_PTR(insn, SH_RS2C, regs))
#घोषणा GET_SP(regs)			(*REG_PTR(2, 0, regs))
#घोषणा SET_RD(insn, regs, val)		(*REG_PTR(insn, SH_RD, regs) = (val))
#घोषणा IMM_I(insn)			((s32)(insn) >> 20)
#घोषणा IMM_S(insn)			(((s32)(insn) >> 25 << 5) | \
					 (s32)(((insn) >> 7) & 0x1f))
#घोषणा MASK_FUNCT3			0x7000

#घोषणा GET_PRECISION(insn) (((insn) >> 25) & 3)
#घोषणा GET_RM(insn) (((insn) >> 12) & 7)
#घोषणा PRECISION_S 0
#घोषणा PRECISION_D 1

#घोषणा STR(x) XSTR(x)
#घोषणा XSTR(x) #x

#घोषणा DECLARE_UNPRIVILEGED_LOAD_FUNCTION(type, insn)			\
अटल अंतरभूत type load_##type(स्थिर type *addr)			\
अणु									\
	type val;							\
	यंत्र (#insn " %0, %1"						\
	: "=&r" (val) : "m" (*addr));					\
	वापस val;							\
पूर्ण

#घोषणा DECLARE_UNPRIVILEGED_STORE_FUNCTION(type, insn)			\
अटल अंतरभूत व्योम store_##type(type *addr, type val)			\
अणु									\
	यंत्र अस्थिर (#insn " %0, %1\n"					\
	: : "r" (val), "m" (*addr));					\
पूर्ण

DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u8, lbu)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u16, lhu)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(s8, lb)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(s16, lh)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(s32, lw)
DECLARE_UNPRIVILEGED_STORE_FUNCTION(u8, sb)
DECLARE_UNPRIVILEGED_STORE_FUNCTION(u16, sh)
DECLARE_UNPRIVILEGED_STORE_FUNCTION(u32, sw)
#अगर defined(CONFIG_64BIT)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u32, lwu)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u64, ld)
DECLARE_UNPRIVILEGED_STORE_FUNCTION(u64, sd)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(uदीर्घ, ld)
#अन्यथा
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u32, lw)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(uदीर्घ, lw)

अटल अंतरभूत u64 load_u64(स्थिर u64 *addr)
अणु
	वापस load_u32((u32 *)addr)
		+ ((u64)load_u32((u32 *)addr + 1) << 32);
पूर्ण

अटल अंतरभूत व्योम store_u64(u64 *addr, u64 val)
अणु
	store_u32((u32 *)addr, val);
	store_u32((u32 *)addr + 1, val >> 32);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत uदीर्घ get_insn(uदीर्घ mepc)
अणु
	रेजिस्टर uदीर्घ __mepc यंत्र ("a2") = mepc;
	uदीर्घ val, rvc_mask = 3, पंचांगp;

	यंत्र ("and %[tmp], %[addr], 2\n"
		"bnez %[tmp], 1f\n"
#अगर defined(CONFIG_64BIT)
		STR(LWU) " %[insn], (%[addr])\n"
#अन्यथा
		STR(LW) " %[insn], (%[addr])\n"
#पूर्ण_अगर
		"and %[tmp], %[insn], %[rvc_mask]\n"
		"beq %[tmp], %[rvc_mask], 2f\n"
		"sll %[insn], %[insn], %[xlen_minus_16]\n"
		"srl %[insn], %[insn], %[xlen_minus_16]\n"
		"j 2f\n"
		"1:\n"
		"lhu %[insn], (%[addr])\n"
		"and %[tmp], %[insn], %[rvc_mask]\n"
		"bne %[tmp], %[rvc_mask], 2f\n"
		"lhu %[tmp], 2(%[addr])\n"
		"sll %[tmp], %[tmp], 16\n"
		"add %[insn], %[insn], %[tmp]\n"
		"2:"
	: [insn] "=&r" (val), [पंचांगp] "=&r" (पंचांगp)
	: [addr] "r" (__mepc), [rvc_mask] "r" (rvc_mask),
	  [xlen_minus_16] "i" (XLEN_MINUS_16));

	वापस val;
पूर्ण

जोड़ reg_data अणु
	u8 data_bytes[8];
	uदीर्घ data_uदीर्घ;
	u64 data_u64;
पूर्ण;

पूर्णांक handle_misaligned_load(काष्ठा pt_regs *regs)
अणु
	जोड़ reg_data val;
	अचिन्हित दीर्घ epc = regs->epc;
	अचिन्हित दीर्घ insn = get_insn(epc);
	अचिन्हित दीर्घ addr = csr_पढ़ो(mtval);
	पूर्णांक i, fp = 0, shअगरt = 0, len = 0;

	regs->epc = 0;

	अगर ((insn & INSN_MASK_LW) == INSN_MATCH_LW) अणु
		len = 4;
		shअगरt = 8 * (माप(अचिन्हित दीर्घ) - len);
#अगर defined(CONFIG_64BIT)
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_LD) == INSN_MATCH_LD) अणु
		len = 8;
		shअगरt = 8 * (माप(अचिन्हित दीर्घ) - len);
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_LWU) == INSN_MATCH_LWU) अणु
		len = 4;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_FLD) == INSN_MATCH_FLD) अणु
		fp = 1;
		len = 8;
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_FLW) == INSN_MATCH_FLW) अणु
		fp = 1;
		len = 4;
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_LH) == INSN_MATCH_LH) अणु
		len = 2;
		shअगरt = 8 * (माप(अचिन्हित दीर्घ) - len);
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_LHU) == INSN_MATCH_LHU) अणु
		len = 2;
#अगर defined(CONFIG_64BIT)
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_LD) == INSN_MATCH_C_LD) अणु
		len = 8;
		shअगरt = 8 * (माप(अचिन्हित दीर्घ) - len);
		insn = RVC_RS2S(insn) << SH_RD;
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_LDSP) == INSN_MATCH_C_LDSP &&
		   ((insn >> SH_RD) & 0x1f)) अणु
		len = 8;
		shअगरt = 8 * (माप(अचिन्हित दीर्घ) - len);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_LW) == INSN_MATCH_C_LW) अणु
		len = 4;
		shअगरt = 8 * (माप(अचिन्हित दीर्घ) - len);
		insn = RVC_RS2S(insn) << SH_RD;
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_LWSP) == INSN_MATCH_C_LWSP &&
		   ((insn >> SH_RD) & 0x1f)) अणु
		len = 4;
		shअगरt = 8 * (माप(अचिन्हित दीर्घ) - len);
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_FLD) == INSN_MATCH_C_FLD) अणु
		fp = 1;
		len = 8;
		insn = RVC_RS2S(insn) << SH_RD;
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_FLDSP) == INSN_MATCH_C_FLDSP) अणु
		fp = 1;
		len = 8;
#अगर defined(CONFIG_32BIT)
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_FLW) == INSN_MATCH_C_FLW) अणु
		fp = 1;
		len = 4;
		insn = RVC_RS2S(insn) << SH_RD;
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_FLWSP) == INSN_MATCH_C_FLWSP) अणु
		fp = 1;
		len = 4;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		regs->epc = epc;
		वापस -1;
	पूर्ण

	val.data_u64 = 0;
	क्रम (i = 0; i < len; i++)
		val.data_bytes[i] = load_u8((व्योम *)(addr + i));

	अगर (fp)
		वापस -1;
	SET_RD(insn, regs, val.data_uदीर्घ << shअगरt >> shअगरt);

	regs->epc = epc + INSN_LEN(insn);

	वापस 0;
पूर्ण

पूर्णांक handle_misaligned_store(काष्ठा pt_regs *regs)
अणु
	जोड़ reg_data val;
	अचिन्हित दीर्घ epc = regs->epc;
	अचिन्हित दीर्घ insn = get_insn(epc);
	अचिन्हित दीर्घ addr = csr_पढ़ो(mtval);
	पूर्णांक i, len = 0;

	regs->epc = 0;

	val.data_uदीर्घ = GET_RS2(insn, regs);

	अगर ((insn & INSN_MASK_SW) == INSN_MATCH_SW) अणु
		len = 4;
#अगर defined(CONFIG_64BIT)
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_SD) == INSN_MATCH_SD) अणु
		len = 8;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_SH) == INSN_MATCH_SH) अणु
		len = 2;
#अगर defined(CONFIG_64BIT)
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_SD) == INSN_MATCH_C_SD) अणु
		len = 8;
		val.data_uदीर्घ = GET_RS2S(insn, regs);
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_SDSP) == INSN_MATCH_C_SDSP &&
		   ((insn >> SH_RD) & 0x1f)) अणु
		len = 8;
		val.data_uदीर्घ = GET_RS2C(insn, regs);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_SW) == INSN_MATCH_C_SW) अणु
		len = 4;
		val.data_uदीर्घ = GET_RS2S(insn, regs);
	पूर्ण अन्यथा अगर ((insn & INSN_MASK_C_SWSP) == INSN_MATCH_C_SWSP &&
		   ((insn >> SH_RD) & 0x1f)) अणु
		len = 4;
		val.data_uदीर्घ = GET_RS2C(insn, regs);
	पूर्ण अन्यथा अणु
		regs->epc = epc;
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < len; i++)
		store_u8((व्योम *)(addr + i), val.data_bytes[i]);

	regs->epc = epc + INSN_LEN(insn);

	वापस 0;
पूर्ण

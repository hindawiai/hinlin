<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2004 Paul Mackerras <paulus@au.ibm.com>, IBM
 */
#समावेश <यंत्र/inst.h>

काष्ठा pt_regs;

/*
 * We करोn't allow single-stepping an mपंचांगsrd that would clear
 * MSR_RI, since that would make the exception unrecoverable.
 * Since we need to single-step to proceed from a अवरोधpoपूर्णांक,
 * we करोn't allow putting a अवरोधpoपूर्णांक on an mपंचांगsrd inकाष्ठाion.
 * Similarly we करोn't allow अवरोधpoपूर्णांकs on rfid inकाष्ठाions.
 * These macros tell us अगर an inकाष्ठाion is a mपंचांगsrd or rfid.
 * Note that IS_MTMSRD वापसs true क्रम both an mपंचांगsr (32-bit)
 * and an mपंचांगsrd (64-bit).
 */
#घोषणा IS_MTMSRD(instr)	((ppc_inst_val(instr) & 0xfc0007be) == 0x7c000124)
#घोषणा IS_RFID(instr)		((ppc_inst_val(instr) & 0xfc0007fe) == 0x4c000024)
#घोषणा IS_RFI(instr)		((ppc_inst_val(instr) & 0xfc0007fe) == 0x4c000064)

क्रमागत inकाष्ठाion_type अणु
	COMPUTE,		/* arith/logical/CR op, etc. */
	LOAD,			/* load and store types need to be contiguous */
	LOAD_MULTI,
	LOAD_FP,
	LOAD_VMX,
	LOAD_VSX,
	STORE,
	STORE_MULTI,
	STORE_FP,
	STORE_VMX,
	STORE_VSX,
	LARX,
	STCX,
	BRANCH,
	MFSPR,
	MTSPR,
	CACHEOP,
	BARRIER,
	SYSCALL,
	SYSCALL_VECTORED_0,
	MFMSR,
	MTMSR,
	RFI,
	INTERRUPT,
	UNKNOWN
पूर्ण;

#घोषणा INSTR_TYPE_MASK	0x1f

#घोषणा OP_IS_LOAD(type)	((LOAD <= (type) && (type) <= LOAD_VSX) || (type) == LARX)
#घोषणा OP_IS_STORE(type)	((STORE <= (type) && (type) <= STORE_VSX) || (type) == STCX)
#घोषणा OP_IS_LOAD_STORE(type)	(LOAD <= (type) && (type) <= STCX)

/* Compute flags, ORed in with type */
#घोषणा SETREG		0x20
#घोषणा SETCC		0x40
#घोषणा SETXER		0x80

/* Branch flags, ORed in with type */
#घोषणा SETLK		0x20
#घोषणा BRTAKEN		0x40
#घोषणा DECCTR		0x80

/* Load/store flags, ORed in with type */
#घोषणा SIGNEXT		0x20
#घोषणा UPDATE		0x40	/* matches bit in opcode 31 inकाष्ठाions */
#घोषणा BYTEREV		0x80
#घोषणा FPCONV		0x100

/* Barrier type field, ORed in with type */
#घोषणा BARRIER_MASK	0xe0
#घोषणा BARRIER_SYNC	0x00
#घोषणा BARRIER_ISYNC	0x20
#घोषणा BARRIER_EIEIO	0x40
#घोषणा BARRIER_LWSYNC	0x60
#घोषणा BARRIER_PTESYNC	0x80

/* Cacheop values, ORed in with type */
#घोषणा CACHEOP_MASK	0x700
#घोषणा DCBST		0
#घोषणा DCBF		0x100
#घोषणा DCBTST		0x200
#घोषणा DCBT		0x300
#घोषणा ICBI		0x400
#घोषणा DCBZ		0x500

/* VSX flags values */
#घोषणा VSX_FPCONV	1	/* करो भग्नing poपूर्णांक SP/DP conversion */
#घोषणा VSX_SPLAT	2	/* store loaded value पूर्णांकo all elements */
#घोषणा VSX_LDLEFT	4	/* load VSX रेजिस्टर from left */
#घोषणा VSX_CHECK_VEC	8	/* check MSR_VEC not MSR_VSX क्रम reg >= 32 */

/* Prefixed flag, ORed in with type */
#घोषणा PREFIXED       0x800

/* Size field in type word */
#घोषणा SIZE(n)		((n) << 12)
#घोषणा GETSIZE(w)	((w) >> 12)

#घोषणा GETTYPE(t)	((t) & INSTR_TYPE_MASK)
#घोषणा GETLENGTH(t)   (((t) & PREFIXED) ? 8 : 4)

#घोषणा MKOP(t, f, s)	((t) | (f) | SIZE(s))

/* Prefix inकाष्ठाion opeअक्रमs */
#घोषणा GET_PREFIX_RA(i)	(((i) >> 16) & 0x1f)
#घोषणा GET_PREFIX_R(i)		((i) & (1ul << 20))

बाह्य s32 patch__exec_instr;

काष्ठा inकाष्ठाion_op अणु
	पूर्णांक type;
	पूर्णांक reg;
	अचिन्हित दीर्घ val;
	/* For LOAD/STORE/LARX/STCX */
	अचिन्हित दीर्घ ea;
	पूर्णांक update_reg;
	/* For MFSPR */
	पूर्णांक spr;
	u32 ccval;
	u32 xerval;
	u8 element_size;	/* क्रम VSX/VMX loads/stores */
	u8 vsx_flags;
पूर्ण;

जोड़ vsx_reg अणु
	u8	b[16];
	u16	h[8];
	u32	w[4];
	अचिन्हित दीर्घ d[2];
	भग्न	fp[4];
	द्विगुन	dp[2];
	__vector128 v;
पूर्ण;

/*
 * Decode an inकाष्ठाion, and वापस inक्रमmation about it in *op
 * without changing *regs.
 *
 * Return value is 1 अगर the inकाष्ठाion can be emulated just by
 * updating *regs with the inक्रमmation in *op, -1 अगर we need the
 * GPRs but *regs करोesn't contain the full रेजिस्टर set, or 0
 * otherwise.
 */
बाह्य पूर्णांक analyse_instr(काष्ठा inकाष्ठाion_op *op, स्थिर काष्ठा pt_regs *regs,
			 काष्ठा ppc_inst instr);

/*
 * Emulate an inकाष्ठाion that can be executed just by updating
 * fields in *regs.
 */
व्योम emulate_update_regs(काष्ठा pt_regs *reg, काष्ठा inकाष्ठाion_op *op);

/*
 * Emulate inकाष्ठाions that cause a transfer of control,
 * arithmetic/logical inकाष्ठाions, loads and stores,
 * cache operations and barriers.
 *
 * Returns 1 अगर the inकाष्ठाion was emulated successfully,
 * 0 अगर it could not be emulated, or -1 क्रम an inकाष्ठाion that
 * should not be emulated (rfid, mपंचांगsrd clearing MSR_RI, etc.).
 */
बाह्य पूर्णांक emulate_step(काष्ठा pt_regs *regs, काष्ठा ppc_inst instr);

/*
 * Emulate a load or store inकाष्ठाion by पढ़ोing/writing the
 * memory of the current process.  FP/VMX/VSX रेजिस्टरs are assumed
 * to hold live values अगर the appropriate enable bit in regs->msr is
 * set; otherwise this will use the saved values in the thपढ़ो काष्ठा
 * क्रम user-mode accesses.
 */
बाह्य पूर्णांक emulate_loadstore(काष्ठा pt_regs *regs, काष्ठा inकाष्ठाion_op *op);

बाह्य व्योम emulate_vsx_load(काष्ठा inकाष्ठाion_op *op, जोड़ vsx_reg *reg,
			     स्थिर व्योम *mem, bool cross_endian);
बाह्य व्योम emulate_vsx_store(काष्ठा inकाष्ठाion_op *op,
			      स्थिर जोड़ vsx_reg *reg, व्योम *mem,
			      bool cross_endian);
बाह्य पूर्णांक emulate_dcbz(अचिन्हित दीर्घ ea, काष्ठा pt_regs *regs);

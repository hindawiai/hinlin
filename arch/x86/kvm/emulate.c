<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 * emulate.c
 *
 * Generic x86 (32-bit and 64-bit) inकाष्ठाion decoder and emulator.
 *
 * Copyright (c) 2005 Keir Fraser
 *
 * Linux coding style, mod r/m decoder, segment base fixes, real-mode
 * privileged inकाष्ठाions:
 *
 * Copyright (C) 2006 Qumranet
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 *   Avi Kivity <avi@qumranet.com>
 *   Yaniv Kamay <yaniv@qumranet.com>
 *
 * From: xen-unstable 10676:af9809f51f81a3c43f276f00c81a52ef558afda4
 */

#समावेश <linux/kvm_host.h>
#समावेश "kvm_cache_regs.h"
#समावेश "kvm_emulate.h"
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/nospec-branch.h>

#समावेश "x86.h"
#समावेश "tss.h"
#समावेश "mmu.h"
#समावेश "pmu.h"

/*
 * Opeअक्रम types
 */
#घोषणा OpNone             0ull
#घोषणा OpImplicit         1ull  /* No generic decode */
#घोषणा OpReg              2ull  /* Register */
#घोषणा OpMem              3ull  /* Memory */
#घोषणा OpAcc              4ull  /* Accumulator: AL/AX/EAX/RAX */
#घोषणा OpDI               5ull  /* ES:DI/EDI/RDI */
#घोषणा OpMem64            6ull  /* Memory, 64-bit */
#घोषणा OpImmUByte         7ull  /* Zero-extended 8-bit immediate */
#घोषणा OpDX               8ull  /* DX रेजिस्टर */
#घोषणा OpCL               9ull  /* CL रेजिस्टर (क्रम shअगरts) */
#घोषणा OpImmByte         10ull  /* 8-bit sign extended immediate */
#घोषणा OpOne             11ull  /* Implied 1 */
#घोषणा OpImm             12ull  /* Sign extended up to 32-bit immediate */
#घोषणा OpMem16           13ull  /* Memory opeअक्रम (16-bit). */
#घोषणा OpMem32           14ull  /* Memory opeअक्रम (32-bit). */
#घोषणा OpImmU            15ull  /* Immediate opeअक्रम, zero extended */
#घोषणा OpSI              16ull  /* SI/ESI/RSI */
#घोषणा OpImmFAddr        17ull  /* Immediate far address */
#घोषणा OpMemFAddr        18ull  /* Far address in memory */
#घोषणा OpImmU16          19ull  /* Immediate opeअक्रम, 16 bits, zero extended */
#घोषणा OpES              20ull  /* ES */
#घोषणा OpCS              21ull  /* CS */
#घोषणा OpSS              22ull  /* SS */
#घोषणा OpDS              23ull  /* DS */
#घोषणा OpFS              24ull  /* FS */
#घोषणा OpGS              25ull  /* GS */
#घोषणा OpMem8            26ull  /* 8-bit zero extended memory opeअक्रम */
#घोषणा OpImm64           27ull  /* Sign extended 16/32/64-bit immediate */
#घोषणा OpXLat            28ull  /* memory at BX/EBX/RBX + zero-extended AL */
#घोषणा OpAccLo           29ull  /* Low part of extended acc (AX/AX/EAX/RAX) */
#घोषणा OpAccHi           30ull  /* High part of extended acc (-/DX/EDX/RDX) */

#घोषणा OpBits             5  /* Width of opeअक्रम field */
#घोषणा OpMask             ((1ull << OpBits) - 1)

/*
 * Opcode effective-address decode tables.
 * Note that we only emulate inकाष्ठाions that have at least one memory
 * opeअक्रम (excluding implicit stack references). We assume that stack
 * references and inकाष्ठाion fetches will never occur in special memory
 * areas that require emulation. So, क्रम example, 'mov <imm>,<reg>' need
 * not be handled.
 */

/* Opeअक्रम sizes: 8-bit opeअक्रमs or specअगरied/overridden size. */
#घोषणा ByteOp      (1<<0)	/* 8-bit opeअक्रमs. */
/* Destination opeअक्रम type. */
#घोषणा DstShअगरt    1
#घोषणा ImplicitOps (OpImplicit << DstShअगरt)
#घोषणा DstReg      (OpReg << DstShअगरt)
#घोषणा DstMem      (OpMem << DstShअगरt)
#घोषणा DstAcc      (OpAcc << DstShअगरt)
#घोषणा DstDI       (OpDI << DstShअगरt)
#घोषणा DstMem64    (OpMem64 << DstShअगरt)
#घोषणा DstMem16    (OpMem16 << DstShअगरt)
#घोषणा DstImmUByte (OpImmUByte << DstShअगरt)
#घोषणा DstDX       (OpDX << DstShअगरt)
#घोषणा DstAccLo    (OpAccLo << DstShअगरt)
#घोषणा DstMask     (OpMask << DstShअगरt)
/* Source opeअक्रम type. */
#घोषणा SrcShअगरt    6
#घोषणा SrcNone     (OpNone << SrcShअगरt)
#घोषणा SrcReg      (OpReg << SrcShअगरt)
#घोषणा SrcMem      (OpMem << SrcShअगरt)
#घोषणा SrcMem16    (OpMem16 << SrcShअगरt)
#घोषणा SrcMem32    (OpMem32 << SrcShअगरt)
#घोषणा SrcImm      (OpImm << SrcShअगरt)
#घोषणा SrcImmByte  (OpImmByte << SrcShअगरt)
#घोषणा SrcOne      (OpOne << SrcShअगरt)
#घोषणा SrcImmUByte (OpImmUByte << SrcShअगरt)
#घोषणा SrcImmU     (OpImmU << SrcShअगरt)
#घोषणा SrcSI       (OpSI << SrcShअगरt)
#घोषणा SrcXLat     (OpXLat << SrcShअगरt)
#घोषणा SrcImmFAddr (OpImmFAddr << SrcShअगरt)
#घोषणा SrcMemFAddr (OpMemFAddr << SrcShअगरt)
#घोषणा SrcAcc      (OpAcc << SrcShअगरt)
#घोषणा SrcImmU16   (OpImmU16 << SrcShअगरt)
#घोषणा SrcImm64    (OpImm64 << SrcShअगरt)
#घोषणा SrcDX       (OpDX << SrcShअगरt)
#घोषणा SrcMem8     (OpMem8 << SrcShअगरt)
#घोषणा SrcAccHi    (OpAccHi << SrcShअगरt)
#घोषणा SrcMask     (OpMask << SrcShअगरt)
#घोषणा BitOp       (1<<11)
#घोषणा MemAbs      (1<<12)      /* Memory opeअक्रम is असलolute displacement */
#घोषणा String      (1<<13)     /* String inकाष्ठाion (rep capable) */
#घोषणा Stack       (1<<14)     /* Stack inकाष्ठाion (push/pop) */
#घोषणा GroupMask   (7<<15)     /* Opcode uses one of the group mechanisms */
#घोषणा Group       (1<<15)     /* Bits 3:5 of modrm byte extend opcode */
#घोषणा GroupDual   (2<<15)     /* Alternate decoding of mod == 3 */
#घोषणा Prefix      (3<<15)     /* Inकाष्ठाion varies with 66/f2/f3 prefix */
#घोषणा RMExt       (4<<15)     /* Opcode extension in ModRM r/m अगर mod == 3 */
#घोषणा Escape      (5<<15)     /* Escape to coprocessor inकाष्ठाion */
#घोषणा InstrDual   (6<<15)     /* Alternate inकाष्ठाion decoding of mod == 3 */
#घोषणा ModeDual    (7<<15)     /* Dअगरferent inकाष्ठाion क्रम 32/64 bit */
#घोषणा Sse         (1<<18)     /* SSE Vector inकाष्ठाion */
/* Generic ModRM decode. */
#घोषणा ModRM       (1<<19)
/* Destination is only written; never पढ़ो. */
#घोषणा Mov         (1<<20)
/* Misc flags */
#घोषणा Prot        (1<<21) /* inकाष्ठाion generates #UD अगर not in prot-mode */
#घोषणा EmulateOnUD (1<<22) /* Emulate अगर unsupported by the host */
#घोषणा NoAccess    (1<<23) /* Don't access memory (lea/invlpg/verr etc) */
#घोषणा Op3264      (1<<24) /* Opeअक्रम is 64b in दीर्घ mode, 32b otherwise */
#घोषणा Undefined   (1<<25) /* No Such Inकाष्ठाion */
#घोषणा Lock        (1<<26) /* lock prefix is allowed क्रम the inकाष्ठाion */
#घोषणा Priv        (1<<27) /* inकाष्ठाion generates #GP अगर current CPL != 0 */
#घोषणा No64	    (1<<28)
#घोषणा PageTable   (1 << 29)   /* inकाष्ठाion used to ग_लिखो page table */
#घोषणा NotImpl     (1 << 30)   /* inकाष्ठाion is not implemented */
/* Source 2 opeअक्रम type */
#घोषणा Src2Shअगरt   (31)
#घोषणा Src2None    (OpNone << Src2Shअगरt)
#घोषणा Src2Mem     (OpMem << Src2Shअगरt)
#घोषणा Src2CL      (OpCL << Src2Shअगरt)
#घोषणा Src2ImmByte (OpImmByte << Src2Shअगरt)
#घोषणा Src2One     (OpOne << Src2Shअगरt)
#घोषणा Src2Imm     (OpImm << Src2Shअगरt)
#घोषणा Src2ES      (OpES << Src2Shअगरt)
#घोषणा Src2CS      (OpCS << Src2Shअगरt)
#घोषणा Src2SS      (OpSS << Src2Shअगरt)
#घोषणा Src2DS      (OpDS << Src2Shअगरt)
#घोषणा Src2FS      (OpFS << Src2Shअगरt)
#घोषणा Src2GS      (OpGS << Src2Shअगरt)
#घोषणा Src2Mask    (OpMask << Src2Shअगरt)
#घोषणा Mmx         ((u64)1 << 40)  /* MMX Vector inकाष्ठाion */
#घोषणा AlignMask   ((u64)7 << 41)
#घोषणा Aligned     ((u64)1 << 41)  /* Explicitly aligned (e.g. MOVDQA) */
#घोषणा Unaligned   ((u64)2 << 41)  /* Explicitly unaligned (e.g. MOVDQU) */
#घोषणा Avx         ((u64)3 << 41)  /* Advanced Vector Extensions */
#घोषणा Aligned16   ((u64)4 << 41)  /* Aligned to 16 byte boundary (e.g. FXSAVE) */
#घोषणा Fastop      ((u64)1 << 44)  /* Use opcode::u.fastop */
#घोषणा NoWrite     ((u64)1 << 45)  /* No ग_लिखोback */
#घोषणा SrcWrite    ((u64)1 << 46)  /* Write back src opeअक्रम */
#घोषणा NoMod	    ((u64)1 << 47)  /* Mod field is ignored */
#घोषणा Intercept   ((u64)1 << 48)  /* Has valid पूर्णांकercept field */
#घोषणा CheckPerm   ((u64)1 << 49)  /* Has valid check_perm field */
#घोषणा PrivUD      ((u64)1 << 51)  /* #UD instead of #GP on CPL > 0 */
#घोषणा NearBranch  ((u64)1 << 52)  /* Near branches */
#घोषणा No16	    ((u64)1 << 53)  /* No 16 bit opeअक्रम */
#घोषणा IncSP       ((u64)1 << 54)  /* SP is incremented beक्रमe ModRM calc */
#घोषणा TwoMemOp    ((u64)1 << 55)  /* Inकाष्ठाion has two memory opeअक्रम */

#घोषणा DstXacc     (DstAccLo | SrcAccHi | SrcWrite)

#घोषणा X2(x...) x, x
#घोषणा X3(x...) X2(x), x
#घोषणा X4(x...) X2(x), X2(x)
#घोषणा X5(x...) X4(x), x
#घोषणा X6(x...) X4(x), X2(x)
#घोषणा X7(x...) X4(x), X3(x)
#घोषणा X8(x...) X4(x), X4(x)
#घोषणा X16(x...) X8(x), X8(x)

#घोषणा NR_FASTOP (ilog2(माप(uदीर्घ)) + 1)
#घोषणा FASTOP_SIZE 8

काष्ठा opcode अणु
	u64 flags : 56;
	u64 पूर्णांकercept : 8;
	जोड़ अणु
		पूर्णांक (*execute)(काष्ठा x86_emulate_ctxt *ctxt);
		स्थिर काष्ठा opcode *group;
		स्थिर काष्ठा group_dual *gdual;
		स्थिर काष्ठा gprefix *gprefix;
		स्थिर काष्ठा escape *esc;
		स्थिर काष्ठा instr_dual *idual;
		स्थिर काष्ठा mode_dual *mdual;
		व्योम (*fastop)(काष्ठा fastop *fake);
	पूर्ण u;
	पूर्णांक (*check_perm)(काष्ठा x86_emulate_ctxt *ctxt);
पूर्ण;

काष्ठा group_dual अणु
	काष्ठा opcode mod012[8];
	काष्ठा opcode mod3[8];
पूर्ण;

काष्ठा gprefix अणु
	काष्ठा opcode pfx_no;
	काष्ठा opcode pfx_66;
	काष्ठा opcode pfx_f2;
	काष्ठा opcode pfx_f3;
पूर्ण;

काष्ठा escape अणु
	काष्ठा opcode op[8];
	काष्ठा opcode high[64];
पूर्ण;

काष्ठा instr_dual अणु
	काष्ठा opcode mod012;
	काष्ठा opcode mod3;
पूर्ण;

काष्ठा mode_dual अणु
	काष्ठा opcode mode32;
	काष्ठा opcode mode64;
पूर्ण;

#घोषणा EFLG_RESERVED_ZEROS_MASK 0xffc0802a

क्रमागत x86_transfer_type अणु
	X86_TRANSFER_NONE,
	X86_TRANSFER_CALL_JMP,
	X86_TRANSFER_RET,
	X86_TRANSFER_TASK_SWITCH,
पूर्ण;

अटल uदीर्घ reg_पढ़ो(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित nr)
अणु
	अगर (!(ctxt->regs_valid & (1 << nr))) अणु
		ctxt->regs_valid |= 1 << nr;
		ctxt->_regs[nr] = ctxt->ops->पढ़ो_gpr(ctxt, nr);
	पूर्ण
	वापस ctxt->_regs[nr];
पूर्ण

अटल uदीर्घ *reg_ग_लिखो(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित nr)
अणु
	ctxt->regs_valid |= 1 << nr;
	ctxt->regs_dirty |= 1 << nr;
	वापस &ctxt->_regs[nr];
पूर्ण

अटल uदीर्घ *reg_rmw(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित nr)
अणु
	reg_पढ़ो(ctxt, nr);
	वापस reg_ग_लिखो(ctxt, nr);
पूर्ण

अटल व्योम ग_लिखोback_रेजिस्टरs(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अचिन्हित reg;

	क्रम_each_set_bit(reg, (uदीर्घ *)&ctxt->regs_dirty, 16)
		ctxt->ops->ग_लिखो_gpr(ctxt, reg, ctxt->_regs[reg]);
पूर्ण

अटल व्योम invalidate_रेजिस्टरs(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->regs_dirty = 0;
	ctxt->regs_valid = 0;
पूर्ण

/*
 * These EFLAGS bits are restored from saved value during emulation, and
 * any changes are written back to the saved value after emulation.
 */
#घोषणा EFLAGS_MASK (X86_EFLAGS_OF|X86_EFLAGS_SF|X86_EFLAGS_ZF|X86_EFLAGS_AF|\
		     X86_EFLAGS_PF|X86_EFLAGS_CF)

#अगर_घोषित CONFIG_X86_64
#घोषणा ON64(x) x
#अन्यथा
#घोषणा ON64(x)
#पूर्ण_अगर

/*
 * fastop functions have a special calling convention:
 *
 * dst:    rax        (in/out)
 * src:    rdx        (in/out)
 * src2:   rcx        (in)
 * flags:  rflags     (in/out)
 * ex:     rsi        (in:fastop poपूर्णांकer, out:zero अगर exception)
 *
 * Moreover, they are all exactly FASTOP_SIZE bytes दीर्घ, so functions क्रम
 * dअगरferent opeअक्रम sizes can be reached by calculation, rather than a jump
 * table (which would be bigger than the code).
 */
अटल पूर्णांक fastop(काष्ठा x86_emulate_ctxt *ctxt, fastop_t fop);

#घोषणा __FOP_FUNC(name) \
	".align " __stringअगरy(FASTOP_SIZE) " \n\t" \
	".type " name ", @function \n\t" \
	name ":\n\t"

#घोषणा FOP_FUNC(name) \
	__FOP_FUNC(#name)

#घोषणा __FOP_RET(name) \
	"ret \n\t" \
	".size " name ", .-" name "\n\t"

#घोषणा FOP_RET(name) \
	__FOP_RET(#name)

#घोषणा FOP_START(op) \
	बाह्य व्योम em_##op(काष्ठा fastop *fake); \
	यंत्र(".pushsection .text, \"ax\" \n\t" \
	    ".global em_" #op " \n\t" \
	    ".align " __stringअगरy(FASTOP_SIZE) " \n\t" \
	    "em_" #op ":\n\t"

#घोषणा FOP_END \
	    ".popsection")

#घोषणा __FOPNOP(name) \
	__FOP_FUNC(name) \
	__FOP_RET(name)

#घोषणा FOPNOP() \
	__FOPNOP(__stringअगरy(__UNIQUE_ID(nop)))

#घोषणा FOP1E(op,  dst) \
	__FOP_FUNC(#op "_" #dst) \
	"10: " #op " %" #dst " \n\t" \
	__FOP_RET(#op "_" #dst)

#घोषणा FOP1EEX(op,  dst) \
	FOP1E(op, dst) _ASM_EXTABLE(10b, kvm_fastop_exception)

#घोषणा FASTOP1(op) \
	FOP_START(op) \
	FOP1E(op##b, al) \
	FOP1E(op##w, ax) \
	FOP1E(op##l, eax) \
	ON64(FOP1E(op##q, rax))	\
	FOP_END

/* 1-opeअक्रम, using src2 (क्रम MUL/DIV r/m) */
#घोषणा FASTOP1SRC2(op, name) \
	FOP_START(name) \
	FOP1E(op, cl) \
	FOP1E(op, cx) \
	FOP1E(op, ecx) \
	ON64(FOP1E(op, rcx)) \
	FOP_END

/* 1-opeअक्रम, using src2 (क्रम MUL/DIV r/m), with exceptions */
#घोषणा FASTOP1SRC2EX(op, name) \
	FOP_START(name) \
	FOP1EEX(op, cl) \
	FOP1EEX(op, cx) \
	FOP1EEX(op, ecx) \
	ON64(FOP1EEX(op, rcx)) \
	FOP_END

#घोषणा FOP2E(op,  dst, src)	   \
	__FOP_FUNC(#op "_" #dst "_" #src) \
	#op " %" #src ", %" #dst " \n\t" \
	__FOP_RET(#op "_" #dst "_" #src)

#घोषणा FASTOP2(op) \
	FOP_START(op) \
	FOP2E(op##b, al, dl) \
	FOP2E(op##w, ax, dx) \
	FOP2E(op##l, eax, edx) \
	ON64(FOP2E(op##q, rax, rdx)) \
	FOP_END

/* 2 opeअक्रम, word only */
#घोषणा FASTOP2W(op) \
	FOP_START(op) \
	FOPNOP() \
	FOP2E(op##w, ax, dx) \
	FOP2E(op##l, eax, edx) \
	ON64(FOP2E(op##q, rax, rdx)) \
	FOP_END

/* 2 opeअक्रम, src is CL */
#घोषणा FASTOP2CL(op) \
	FOP_START(op) \
	FOP2E(op##b, al, cl) \
	FOP2E(op##w, ax, cl) \
	FOP2E(op##l, eax, cl) \
	ON64(FOP2E(op##q, rax, cl)) \
	FOP_END

/* 2 opeअक्रम, src and dest are reversed */
#घोषणा FASTOP2R(op, name) \
	FOP_START(name) \
	FOP2E(op##b, dl, al) \
	FOP2E(op##w, dx, ax) \
	FOP2E(op##l, edx, eax) \
	ON64(FOP2E(op##q, rdx, rax)) \
	FOP_END

#घोषणा FOP3E(op,  dst, src, src2) \
	__FOP_FUNC(#op "_" #dst "_" #src "_" #src2) \
	#op " %" #src2 ", %" #src ", %" #dst " \n\t"\
	__FOP_RET(#op "_" #dst "_" #src "_" #src2)

/* 3-opeअक्रम, word-only, src2=cl */
#घोषणा FASTOP3WCL(op) \
	FOP_START(op) \
	FOPNOP() \
	FOP3E(op##w, ax, dx, cl) \
	FOP3E(op##l, eax, edx, cl) \
	ON64(FOP3E(op##q, rax, rdx, cl)) \
	FOP_END

/* Special हाल क्रम SETcc - 1 inकाष्ठाion per cc */
#घोषणा FOP_SETCC(op) \
	".align 4 \n\t" \
	".type " #op ", @function \n\t" \
	#op ": \n\t" \
	#op " %al \n\t" \
	__FOP_RET(#op)

यंत्र(".pushsection .fixup, \"ax\"\n"
    ".global kvm_fastop_exception \n"
    "kvm_fastop_exception: xor %esi, %esi; ret\n"
    ".popsection");

FOP_START(setcc)
FOP_SETCC(seto)
FOP_SETCC(setno)
FOP_SETCC(setc)
FOP_SETCC(setnc)
FOP_SETCC(setz)
FOP_SETCC(setnz)
FOP_SETCC(setbe)
FOP_SETCC(setnbe)
FOP_SETCC(sets)
FOP_SETCC(setns)
FOP_SETCC(setp)
FOP_SETCC(setnp)
FOP_SETCC(setl)
FOP_SETCC(setnl)
FOP_SETCC(setle)
FOP_SETCC(setnle)
FOP_END;

FOP_START(salc)
FOP_FUNC(salc)
"pushf; sbb %al, %al; popf \n\t"
FOP_RET(salc)
FOP_END;

/*
 * XXX: inoutclob user must know where the argument is being expanded.
 *      Relying on CONFIG_CC_HAS_ASM_GOTO would allow us to हटाओ _fault.
 */
#घोषणा यंत्र_safe(insn, inoutclob...) \
(अणु \
	पूर्णांक _fault = 0; \
 \
	यंत्र अस्थिर("1:" insn "\n" \
	             "2:\n" \
	             ".pushsection .fixup, \"ax\"\n" \
	             "3: movl $1, %[_fault]\n" \
	             "   jmp  2b\n" \
	             ".popsection\n" \
	             _ASM_EXTABLE(1b, 3b) \
	             : [_fault] "+qm"(_fault) inoutclob ); \
 \
	_fault ? X86EMUL_UNHANDLEABLE : X86EMUL_CONTINUE; \
पूर्ण)

अटल पूर्णांक emulator_check_पूर्णांकercept(काष्ठा x86_emulate_ctxt *ctxt,
				    क्रमागत x86_पूर्णांकercept पूर्णांकercept,
				    क्रमागत x86_पूर्णांकercept_stage stage)
अणु
	काष्ठा x86_inकाष्ठाion_info info = अणु
		.पूर्णांकercept  = पूर्णांकercept,
		.rep_prefix = ctxt->rep_prefix,
		.modrm_mod  = ctxt->modrm_mod,
		.modrm_reg  = ctxt->modrm_reg,
		.modrm_rm   = ctxt->modrm_rm,
		.src_val    = ctxt->src.val64,
		.dst_val    = ctxt->dst.val64,
		.src_bytes  = ctxt->src.bytes,
		.dst_bytes  = ctxt->dst.bytes,
		.ad_bytes   = ctxt->ad_bytes,
		.next_rip   = ctxt->eip,
	पूर्ण;

	वापस ctxt->ops->पूर्णांकercept(ctxt, &info, stage);
पूर्ण

अटल व्योम assign_masked(uदीर्घ *dest, uदीर्घ src, uदीर्घ mask)
अणु
	*dest = (*dest & ~mask) | (src & mask);
पूर्ण

अटल व्योम assign_रेजिस्टर(अचिन्हित दीर्घ *reg, u64 val, पूर्णांक bytes)
अणु
	/* The 4-byte हाल *is* correct: in 64-bit mode we zero-extend. */
	चयन (bytes) अणु
	हाल 1:
		*(u8 *)reg = (u8)val;
		अवरोध;
	हाल 2:
		*(u16 *)reg = (u16)val;
		अवरोध;
	हाल 4:
		*reg = (u32)val;
		अवरोध;	/* 64b: zero-extend */
	हाल 8:
		*reg = val;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ad_mask(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस (1UL << (ctxt->ad_bytes << 3)) - 1;
पूर्ण

अटल uदीर्घ stack_mask(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u16 sel;
	काष्ठा desc_काष्ठा ss;

	अगर (ctxt->mode == X86EMUL_MODE_PROT64)
		वापस ~0UL;
	ctxt->ops->get_segment(ctxt, &sel, &ss, शून्य, VCPU_SREG_SS);
	वापस ~0U >> ((ss.d ^ 1) * 16);  /* d=0: 0xffff; d=1: 0xffffffff */
पूर्ण

अटल पूर्णांक stack_size(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस (__fls(stack_mask(ctxt)) + 1) >> 3;
पूर्ण

/* Access/update address held in a रेजिस्टर, based on addressing mode. */
अटल अंतरभूत अचिन्हित दीर्घ
address_mask(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित दीर्घ reg)
अणु
	अगर (ctxt->ad_bytes == माप(अचिन्हित दीर्घ))
		वापस reg;
	अन्यथा
		वापस reg & ad_mask(ctxt);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
रेजिस्टर_address(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक reg)
अणु
	वापस address_mask(ctxt, reg_पढ़ो(ctxt, reg));
पूर्ण

अटल व्योम masked_increment(uदीर्घ *reg, uदीर्घ mask, पूर्णांक inc)
अणु
	assign_masked(reg, *reg + inc, mask);
पूर्ण

अटल अंतरभूत व्योम
रेजिस्टर_address_increment(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक reg, पूर्णांक inc)
अणु
	uदीर्घ *preg = reg_rmw(ctxt, reg);

	assign_रेजिस्टर(preg, *preg + inc, ctxt->ad_bytes);
पूर्ण

अटल व्योम rsp_increment(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक inc)
अणु
	masked_increment(reg_rmw(ctxt, VCPU_REGS_RSP), stack_mask(ctxt), inc);
पूर्ण

अटल u32 desc_limit_scaled(काष्ठा desc_काष्ठा *desc)
अणु
	u32 limit = get_desc_limit(desc);

	वापस desc->g ? (limit << 12) | 0xfff : limit;
पूर्ण

अटल अचिन्हित दीर्घ seg_base(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक seg)
अणु
	अगर (ctxt->mode == X86EMUL_MODE_PROT64 && seg < VCPU_SREG_FS)
		वापस 0;

	वापस ctxt->ops->get_cached_segment_base(ctxt, seg);
पूर्ण

अटल पूर्णांक emulate_exception(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक vec,
			     u32 error, bool valid)
अणु
	WARN_ON(vec > 0x1f);
	ctxt->exception.vector = vec;
	ctxt->exception.error_code = error;
	ctxt->exception.error_code_valid = valid;
	वापस X86EMUL_PROPAGATE_FAULT;
पूर्ण

अटल पूर्णांक emulate_db(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस emulate_exception(ctxt, DB_VECTOR, 0, false);
पूर्ण

अटल पूर्णांक emulate_gp(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक err)
अणु
	वापस emulate_exception(ctxt, GP_VECTOR, err, true);
पूर्ण

अटल पूर्णांक emulate_ss(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक err)
अणु
	वापस emulate_exception(ctxt, SS_VECTOR, err, true);
पूर्ण

अटल पूर्णांक emulate_ud(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस emulate_exception(ctxt, UD_VECTOR, 0, false);
पूर्ण

अटल पूर्णांक emulate_ts(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक err)
अणु
	वापस emulate_exception(ctxt, TS_VECTOR, err, true);
पूर्ण

अटल पूर्णांक emulate_de(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस emulate_exception(ctxt, DE_VECTOR, 0, false);
पूर्ण

अटल पूर्णांक emulate_nm(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस emulate_exception(ctxt, NM_VECTOR, 0, false);
पूर्ण

अटल u16 get_segment_selector(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित seg)
अणु
	u16 selector;
	काष्ठा desc_काष्ठा desc;

	ctxt->ops->get_segment(ctxt, &selector, &desc, शून्य, seg);
	वापस selector;
पूर्ण

अटल व्योम set_segment_selector(काष्ठा x86_emulate_ctxt *ctxt, u16 selector,
				 अचिन्हित seg)
अणु
	u16 dummy;
	u32 base3;
	काष्ठा desc_काष्ठा desc;

	ctxt->ops->get_segment(ctxt, &dummy, &desc, &base3, seg);
	ctxt->ops->set_segment(ctxt, selector, &desc, base3, seg);
पूर्ण

अटल अंतरभूत u8 ctxt_virt_addr_bits(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस (ctxt->ops->get_cr(ctxt, 4) & X86_CR4_LA57) ? 57 : 48;
पूर्ण

अटल अंतरभूत bool emul_is_noncanonical_address(u64 la,
						काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस get_canonical(la, ctxt_virt_addr_bits(ctxt)) != la;
पूर्ण

/*
 * x86 defines three classes of vector inकाष्ठाions: explicitly
 * aligned, explicitly unaligned, and the rest, which change behaviour
 * depending on whether they're AVX encoded or not.
 *
 * Also included is CMPXCHG16B which is not a vector inकाष्ठाion, yet it is
 * subject to the same check.  FXSAVE and FXRSTOR are checked here too as their
 * 512 bytes of data must be aligned to a 16 byte boundary.
 */
अटल अचिन्हित insn_alignment(काष्ठा x86_emulate_ctxt *ctxt, अचिन्हित size)
अणु
	u64 alignment = ctxt->d & AlignMask;

	अगर (likely(size < 16))
		वापस 1;

	चयन (alignment) अणु
	हाल Unaligned:
	हाल Avx:
		वापस 1;
	हाल Aligned16:
		वापस 16;
	हाल Aligned:
	शेष:
		वापस size;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत पूर्णांक __linearize(काष्ठा x86_emulate_ctxt *ctxt,
				       काष्ठा segmented_address addr,
				       अचिन्हित *max_size, अचिन्हित size,
				       bool ग_लिखो, bool fetch,
				       क्रमागत x86emul_mode mode, uदीर्घ *linear)
अणु
	काष्ठा desc_काष्ठा desc;
	bool usable;
	uदीर्घ la;
	u32 lim;
	u16 sel;
	u8  va_bits;

	la = seg_base(ctxt, addr.seg) + addr.ea;
	*max_size = 0;
	चयन (mode) अणु
	हाल X86EMUL_MODE_PROT64:
		*linear = la;
		va_bits = ctxt_virt_addr_bits(ctxt);
		अगर (get_canonical(la, va_bits) != la)
			जाओ bad;

		*max_size = min_t(u64, ~0u, (1ull << va_bits) - la);
		अगर (size > *max_size)
			जाओ bad;
		अवरोध;
	शेष:
		*linear = la = (u32)la;
		usable = ctxt->ops->get_segment(ctxt, &sel, &desc, शून्य,
						addr.seg);
		अगर (!usable)
			जाओ bad;
		/* code segment in रक्षित mode or पढ़ो-only data segment */
		अगर ((((ctxt->mode != X86EMUL_MODE_REAL) && (desc.type & 8))
					|| !(desc.type & 2)) && ग_लिखो)
			जाओ bad;
		/* unपढ़ोable code segment */
		अगर (!fetch && (desc.type & 8) && !(desc.type & 2))
			जाओ bad;
		lim = desc_limit_scaled(&desc);
		अगर (!(desc.type & 8) && (desc.type & 4)) अणु
			/* expand-करोwn segment */
			अगर (addr.ea <= lim)
				जाओ bad;
			lim = desc.d ? 0xffffffff : 0xffff;
		पूर्ण
		अगर (addr.ea > lim)
			जाओ bad;
		अगर (lim == 0xffffffff)
			*max_size = ~0u;
		अन्यथा अणु
			*max_size = (u64)lim + 1 - addr.ea;
			अगर (size > *max_size)
				जाओ bad;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (la & (insn_alignment(ctxt, size) - 1))
		वापस emulate_gp(ctxt, 0);
	वापस X86EMUL_CONTINUE;
bad:
	अगर (addr.seg == VCPU_SREG_SS)
		वापस emulate_ss(ctxt, 0);
	अन्यथा
		वापस emulate_gp(ctxt, 0);
पूर्ण

अटल पूर्णांक linearize(काष्ठा x86_emulate_ctxt *ctxt,
		     काष्ठा segmented_address addr,
		     अचिन्हित size, bool ग_लिखो,
		     uदीर्घ *linear)
अणु
	अचिन्हित max_size;
	वापस __linearize(ctxt, addr, &max_size, size, ग_लिखो, false,
			   ctxt->mode, linear);
पूर्ण

अटल अंतरभूत पूर्णांक assign_eip(काष्ठा x86_emulate_ctxt *ctxt, uदीर्घ dst,
			     क्रमागत x86emul_mode mode)
अणु
	uदीर्घ linear;
	पूर्णांक rc;
	अचिन्हित max_size;
	काष्ठा segmented_address addr = अणु .seg = VCPU_SREG_CS,
					   .ea = dst पूर्ण;

	अगर (ctxt->op_bytes != माप(अचिन्हित दीर्घ))
		addr.ea = dst & ((1UL << (ctxt->op_bytes << 3)) - 1);
	rc = __linearize(ctxt, addr, &max_size, 1, false, true, mode, &linear);
	अगर (rc == X86EMUL_CONTINUE)
		ctxt->_eip = addr.ea;
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक assign_eip_near(काष्ठा x86_emulate_ctxt *ctxt, uदीर्घ dst)
अणु
	वापस assign_eip(ctxt, dst, ctxt->mode);
पूर्ण

अटल पूर्णांक assign_eip_far(काष्ठा x86_emulate_ctxt *ctxt, uदीर्घ dst,
			  स्थिर काष्ठा desc_काष्ठा *cs_desc)
अणु
	क्रमागत x86emul_mode mode = ctxt->mode;
	पूर्णांक rc;

#अगर_घोषित CONFIG_X86_64
	अगर (ctxt->mode >= X86EMUL_MODE_PROT16) अणु
		अगर (cs_desc->l) अणु
			u64 efer = 0;

			ctxt->ops->get_msr(ctxt, MSR_EFER, &efer);
			अगर (efer & EFER_LMA)
				mode = X86EMUL_MODE_PROT64;
		पूर्ण अन्यथा
			mode = X86EMUL_MODE_PROT32; /* temporary value */
	पूर्ण
#पूर्ण_अगर
	अगर (mode == X86EMUL_MODE_PROT16 || mode == X86EMUL_MODE_PROT32)
		mode = cs_desc->d ? X86EMUL_MODE_PROT32 : X86EMUL_MODE_PROT16;
	rc = assign_eip(ctxt, dst, mode);
	अगर (rc == X86EMUL_CONTINUE)
		ctxt->mode = mode;
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक jmp_rel(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक rel)
अणु
	वापस assign_eip_near(ctxt, ctxt->_eip + rel);
पूर्ण

अटल पूर्णांक linear_पढ़ो_प्रणाली(काष्ठा x86_emulate_ctxt *ctxt, uदीर्घ linear,
			      व्योम *data, अचिन्हित size)
अणु
	वापस ctxt->ops->पढ़ो_std(ctxt, linear, data, size, &ctxt->exception, true);
पूर्ण

अटल पूर्णांक linear_ग_लिखो_प्रणाली(काष्ठा x86_emulate_ctxt *ctxt,
			       uदीर्घ linear, व्योम *data,
			       अचिन्हित पूर्णांक size)
अणु
	वापस ctxt->ops->ग_लिखो_std(ctxt, linear, data, size, &ctxt->exception, true);
पूर्ण

अटल पूर्णांक segmented_पढ़ो_std(काष्ठा x86_emulate_ctxt *ctxt,
			      काष्ठा segmented_address addr,
			      व्योम *data,
			      अचिन्हित size)
अणु
	पूर्णांक rc;
	uदीर्घ linear;

	rc = linearize(ctxt, addr, size, false, &linear);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	वापस ctxt->ops->पढ़ो_std(ctxt, linear, data, size, &ctxt->exception, false);
पूर्ण

अटल पूर्णांक segmented_ग_लिखो_std(काष्ठा x86_emulate_ctxt *ctxt,
			       काष्ठा segmented_address addr,
			       व्योम *data,
			       अचिन्हित पूर्णांक size)
अणु
	पूर्णांक rc;
	uदीर्घ linear;

	rc = linearize(ctxt, addr, size, true, &linear);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	वापस ctxt->ops->ग_लिखो_std(ctxt, linear, data, size, &ctxt->exception, false);
पूर्ण

/*
 * Prefetch the reमुख्यing bytes of the inकाष्ठाion without crossing page
 * boundary अगर they are not in fetch_cache yet.
 */
अटल पूर्णांक __करो_insn_fetch_bytes(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक op_size)
अणु
	पूर्णांक rc;
	अचिन्हित size, max_size;
	अचिन्हित दीर्घ linear;
	पूर्णांक cur_size = ctxt->fetch.end - ctxt->fetch.data;
	काष्ठा segmented_address addr = अणु .seg = VCPU_SREG_CS,
					   .ea = ctxt->eip + cur_size पूर्ण;

	/*
	 * We करो not know exactly how many bytes will be needed, and
	 * __linearize is expensive, so fetch as much as possible.  We
	 * just have to aव्योम going beyond the 15 byte limit, the end
	 * of the segment, or the end of the page.
	 *
	 * __linearize is called with size 0 so that it करोes not करो any
	 * boundary check itself.  Instead, we use max_size to check
	 * against op_size.
	 */
	rc = __linearize(ctxt, addr, &max_size, 0, false, true, ctxt->mode,
			 &linear);
	अगर (unlikely(rc != X86EMUL_CONTINUE))
		वापस rc;

	size = min_t(अचिन्हित, 15UL ^ cur_size, max_size);
	size = min_t(अचिन्हित, size, PAGE_SIZE - offset_in_page(linear));

	/*
	 * One inकाष्ठाion can only straddle two pages,
	 * and one has been loaded at the beginning of
	 * x86_decode_insn.  So, अगर not enough bytes
	 * still, we must have hit the 15-byte boundary.
	 */
	अगर (unlikely(size < op_size))
		वापस emulate_gp(ctxt, 0);

	rc = ctxt->ops->fetch(ctxt, linear, ctxt->fetch.end,
			      size, &ctxt->exception);
	अगर (unlikely(rc != X86EMUL_CONTINUE))
		वापस rc;
	ctxt->fetch.end += size;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल __always_अंतरभूत पूर्णांक करो_insn_fetch_bytes(काष्ठा x86_emulate_ctxt *ctxt,
					       अचिन्हित size)
अणु
	अचिन्हित करोne_size = ctxt->fetch.end - ctxt->fetch.ptr;

	अगर (unlikely(करोne_size < size))
		वापस __करो_insn_fetch_bytes(ctxt, size - करोne_size);
	अन्यथा
		वापस X86EMUL_CONTINUE;
पूर्ण

/* Fetch next part of the inकाष्ठाion being emulated. */
#घोषणा insn_fetch(_type, _ctxt)					\
(अणु	_type _x;							\
									\
	rc = करो_insn_fetch_bytes(_ctxt, माप(_type));			\
	अगर (rc != X86EMUL_CONTINUE)					\
		जाओ करोne;						\
	ctxt->_eip += माप(_type);					\
	स_नकल(&_x, ctxt->fetch.ptr, माप(_type));			\
	ctxt->fetch.ptr += माप(_type);				\
	_x;								\
पूर्ण)

#घोषणा insn_fetch_arr(_arr, _size, _ctxt)				\
(अणु									\
	rc = करो_insn_fetch_bytes(_ctxt, _size);				\
	अगर (rc != X86EMUL_CONTINUE)					\
		जाओ करोne;						\
	ctxt->_eip += (_size);						\
	स_नकल(_arr, ctxt->fetch.ptr, _size);				\
	ctxt->fetch.ptr += (_size);					\
पूर्ण)

/*
 * Given the 'reg' portion of a ModRM byte, and a रेजिस्टर block, वापस a
 * poपूर्णांकer पूर्णांकo the block that addresses the relevant रेजिस्टर.
 * @highbyte_regs specअगरies whether to decode AH,CH,DH,BH.
 */
अटल व्योम *decode_रेजिस्टर(काष्ठा x86_emulate_ctxt *ctxt, u8 modrm_reg,
			     पूर्णांक byteop)
अणु
	व्योम *p;
	पूर्णांक highbyte_regs = (ctxt->rex_prefix == 0) && byteop;

	अगर (highbyte_regs && modrm_reg >= 4 && modrm_reg < 8)
		p = (अचिन्हित अक्षर *)reg_rmw(ctxt, modrm_reg & 3) + 1;
	अन्यथा
		p = reg_rmw(ctxt, modrm_reg);
	वापस p;
पूर्ण

अटल पूर्णांक पढ़ो_descriptor(काष्ठा x86_emulate_ctxt *ctxt,
			   काष्ठा segmented_address addr,
			   u16 *size, अचिन्हित दीर्घ *address, पूर्णांक op_bytes)
अणु
	पूर्णांक rc;

	अगर (op_bytes == 2)
		op_bytes = 3;
	*address = 0;
	rc = segmented_पढ़ो_std(ctxt, addr, size, 2);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	addr.ea += 2;
	rc = segmented_पढ़ो_std(ctxt, addr, address, op_bytes);
	वापस rc;
पूर्ण

FASTOP2(add);
FASTOP2(or);
FASTOP2(adc);
FASTOP2(sbb);
FASTOP2(and);
FASTOP2(sub);
FASTOP2(xor);
FASTOP2(cmp);
FASTOP2(test);

FASTOP1SRC2(mul, mul_ex);
FASTOP1SRC2(imul, imul_ex);
FASTOP1SRC2EX(भाग, भाग_ex);
FASTOP1SRC2EX(iभाग, iभाग_ex);

FASTOP3WCL(shld);
FASTOP3WCL(shrd);

FASTOP2W(imul);

FASTOP1(not);
FASTOP1(neg);
FASTOP1(inc);
FASTOP1(dec);

FASTOP2CL(rol);
FASTOP2CL(ror);
FASTOP2CL(rcl);
FASTOP2CL(rcr);
FASTOP2CL(shl);
FASTOP2CL(shr);
FASTOP2CL(sar);

FASTOP2W(bsf);
FASTOP2W(bsr);
FASTOP2W(bt);
FASTOP2W(bts);
FASTOP2W(btr);
FASTOP2W(btc);

FASTOP2(xadd);

FASTOP2R(cmp, cmp_r);

अटल पूर्णांक em_bsf_c(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/* If src is zero, करो not ग_लिखोback, but update flags */
	अगर (ctxt->src.val == 0)
		ctxt->dst.type = OP_NONE;
	वापस fastop(ctxt, em_bsf);
पूर्ण

अटल पूर्णांक em_bsr_c(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/* If src is zero, करो not ग_लिखोback, but update flags */
	अगर (ctxt->src.val == 0)
		ctxt->dst.type = OP_NONE;
	वापस fastop(ctxt, em_bsr);
पूर्ण

अटल __always_अंतरभूत u8 test_cc(अचिन्हित पूर्णांक condition, अचिन्हित दीर्घ flags)
अणु
	u8 rc;
	व्योम (*fop)(व्योम) = (व्योम *)em_setcc + 4 * (condition & 0xf);

	flags = (flags & EFLAGS_MASK) | X86_EFLAGS_IF;
	यंत्र("push %[flags]; popf; " CALL_NOSPEC
	    : "=a"(rc) : [thunk_target]"r"(fop), [flags]"r"(flags));
	वापस rc;
पूर्ण

अटल व्योम fetch_रेजिस्टर_opeअक्रम(काष्ठा opeअक्रम *op)
अणु
	चयन (op->bytes) अणु
	हाल 1:
		op->val = *(u8 *)op->addr.reg;
		अवरोध;
	हाल 2:
		op->val = *(u16 *)op->addr.reg;
		अवरोध;
	हाल 4:
		op->val = *(u32 *)op->addr.reg;
		अवरोध;
	हाल 8:
		op->val = *(u64 *)op->addr.reg;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम emulator_get_fpu(व्योम)
अणु
	fpregs_lock();

	fpregs_निश्चित_state_consistent();
	अगर (test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
		चयन_fpu_वापस();
पूर्ण

अटल व्योम emulator_put_fpu(व्योम)
अणु
	fpregs_unlock();
पूर्ण

अटल व्योम पढ़ो_sse_reg(sse128_t *data, पूर्णांक reg)
अणु
	emulator_get_fpu();
	चयन (reg) अणु
	हाल 0: यंत्र("movdqa %%xmm0, %0" : "=m"(*data)); अवरोध;
	हाल 1: यंत्र("movdqa %%xmm1, %0" : "=m"(*data)); अवरोध;
	हाल 2: यंत्र("movdqa %%xmm2, %0" : "=m"(*data)); अवरोध;
	हाल 3: यंत्र("movdqa %%xmm3, %0" : "=m"(*data)); अवरोध;
	हाल 4: यंत्र("movdqa %%xmm4, %0" : "=m"(*data)); अवरोध;
	हाल 5: यंत्र("movdqa %%xmm5, %0" : "=m"(*data)); अवरोध;
	हाल 6: यंत्र("movdqa %%xmm6, %0" : "=m"(*data)); अवरोध;
	हाल 7: यंत्र("movdqa %%xmm7, %0" : "=m"(*data)); अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल 8: यंत्र("movdqa %%xmm8, %0" : "=m"(*data)); अवरोध;
	हाल 9: यंत्र("movdqa %%xmm9, %0" : "=m"(*data)); अवरोध;
	हाल 10: यंत्र("movdqa %%xmm10, %0" : "=m"(*data)); अवरोध;
	हाल 11: यंत्र("movdqa %%xmm11, %0" : "=m"(*data)); अवरोध;
	हाल 12: यंत्र("movdqa %%xmm12, %0" : "=m"(*data)); अवरोध;
	हाल 13: यंत्र("movdqa %%xmm13, %0" : "=m"(*data)); अवरोध;
	हाल 14: यंत्र("movdqa %%xmm14, %0" : "=m"(*data)); अवरोध;
	हाल 15: यंत्र("movdqa %%xmm15, %0" : "=m"(*data)); अवरोध;
#पूर्ण_अगर
	शेष: BUG();
	पूर्ण
	emulator_put_fpu();
पूर्ण

अटल व्योम ग_लिखो_sse_reg(sse128_t *data, पूर्णांक reg)
अणु
	emulator_get_fpu();
	चयन (reg) अणु
	हाल 0: यंत्र("movdqa %0, %%xmm0" : : "m"(*data)); अवरोध;
	हाल 1: यंत्र("movdqa %0, %%xmm1" : : "m"(*data)); अवरोध;
	हाल 2: यंत्र("movdqa %0, %%xmm2" : : "m"(*data)); अवरोध;
	हाल 3: यंत्र("movdqa %0, %%xmm3" : : "m"(*data)); अवरोध;
	हाल 4: यंत्र("movdqa %0, %%xmm4" : : "m"(*data)); अवरोध;
	हाल 5: यंत्र("movdqa %0, %%xmm5" : : "m"(*data)); अवरोध;
	हाल 6: यंत्र("movdqa %0, %%xmm6" : : "m"(*data)); अवरोध;
	हाल 7: यंत्र("movdqa %0, %%xmm7" : : "m"(*data)); अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल 8: यंत्र("movdqa %0, %%xmm8" : : "m"(*data)); अवरोध;
	हाल 9: यंत्र("movdqa %0, %%xmm9" : : "m"(*data)); अवरोध;
	हाल 10: यंत्र("movdqa %0, %%xmm10" : : "m"(*data)); अवरोध;
	हाल 11: यंत्र("movdqa %0, %%xmm11" : : "m"(*data)); अवरोध;
	हाल 12: यंत्र("movdqa %0, %%xmm12" : : "m"(*data)); अवरोध;
	हाल 13: यंत्र("movdqa %0, %%xmm13" : : "m"(*data)); अवरोध;
	हाल 14: यंत्र("movdqa %0, %%xmm14" : : "m"(*data)); अवरोध;
	हाल 15: यंत्र("movdqa %0, %%xmm15" : : "m"(*data)); अवरोध;
#पूर्ण_अगर
	शेष: BUG();
	पूर्ण
	emulator_put_fpu();
पूर्ण

अटल व्योम पढ़ो_mmx_reg(u64 *data, पूर्णांक reg)
अणु
	emulator_get_fpu();
	चयन (reg) अणु
	हाल 0: यंत्र("movq %%mm0, %0" : "=m"(*data)); अवरोध;
	हाल 1: यंत्र("movq %%mm1, %0" : "=m"(*data)); अवरोध;
	हाल 2: यंत्र("movq %%mm2, %0" : "=m"(*data)); अवरोध;
	हाल 3: यंत्र("movq %%mm3, %0" : "=m"(*data)); अवरोध;
	हाल 4: यंत्र("movq %%mm4, %0" : "=m"(*data)); अवरोध;
	हाल 5: यंत्र("movq %%mm5, %0" : "=m"(*data)); अवरोध;
	हाल 6: यंत्र("movq %%mm6, %0" : "=m"(*data)); अवरोध;
	हाल 7: यंत्र("movq %%mm7, %0" : "=m"(*data)); अवरोध;
	शेष: BUG();
	पूर्ण
	emulator_put_fpu();
पूर्ण

अटल व्योम ग_लिखो_mmx_reg(u64 *data, पूर्णांक reg)
अणु
	emulator_get_fpu();
	चयन (reg) अणु
	हाल 0: यंत्र("movq %0, %%mm0" : : "m"(*data)); अवरोध;
	हाल 1: यंत्र("movq %0, %%mm1" : : "m"(*data)); अवरोध;
	हाल 2: यंत्र("movq %0, %%mm2" : : "m"(*data)); अवरोध;
	हाल 3: यंत्र("movq %0, %%mm3" : : "m"(*data)); अवरोध;
	हाल 4: यंत्र("movq %0, %%mm4" : : "m"(*data)); अवरोध;
	हाल 5: यंत्र("movq %0, %%mm5" : : "m"(*data)); अवरोध;
	हाल 6: यंत्र("movq %0, %%mm6" : : "m"(*data)); अवरोध;
	हाल 7: यंत्र("movq %0, %%mm7" : : "m"(*data)); अवरोध;
	शेष: BUG();
	पूर्ण
	emulator_put_fpu();
पूर्ण

अटल पूर्णांक em_fninit(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (ctxt->ops->get_cr(ctxt, 0) & (X86_CR0_TS | X86_CR0_EM))
		वापस emulate_nm(ctxt);

	emulator_get_fpu();
	यंत्र अस्थिर("fninit");
	emulator_put_fpu();
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_fnstcw(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u16 fcw;

	अगर (ctxt->ops->get_cr(ctxt, 0) & (X86_CR0_TS | X86_CR0_EM))
		वापस emulate_nm(ctxt);

	emulator_get_fpu();
	यंत्र अस्थिर("fnstcw %0": "+m"(fcw));
	emulator_put_fpu();

	ctxt->dst.val = fcw;

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_fnstsw(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u16 fsw;

	अगर (ctxt->ops->get_cr(ctxt, 0) & (X86_CR0_TS | X86_CR0_EM))
		वापस emulate_nm(ctxt);

	emulator_get_fpu();
	यंत्र अस्थिर("fnstsw %0": "+m"(fsw));
	emulator_put_fpu();

	ctxt->dst.val = fsw;

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल व्योम decode_रेजिस्टर_opeअक्रम(काष्ठा x86_emulate_ctxt *ctxt,
				    काष्ठा opeअक्रम *op)
अणु
	अचिन्हित reg = ctxt->modrm_reg;

	अगर (!(ctxt->d & ModRM))
		reg = (ctxt->b & 7) | ((ctxt->rex_prefix & 1) << 3);

	अगर (ctxt->d & Sse) अणु
		op->type = OP_XMM;
		op->bytes = 16;
		op->addr.xmm = reg;
		पढ़ो_sse_reg(&op->vec_val, reg);
		वापस;
	पूर्ण
	अगर (ctxt->d & Mmx) अणु
		reg &= 7;
		op->type = OP_MM;
		op->bytes = 8;
		op->addr.mm = reg;
		वापस;
	पूर्ण

	op->type = OP_REG;
	op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
	op->addr.reg = decode_रेजिस्टर(ctxt, reg, ctxt->d & ByteOp);

	fetch_रेजिस्टर_opeअक्रम(op);
	op->orig_val = op->val;
पूर्ण

अटल व्योम adjust_modrm_seg(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक base_reg)
अणु
	अगर (base_reg == VCPU_REGS_RSP || base_reg == VCPU_REGS_RBP)
		ctxt->modrm_seg = VCPU_SREG_SS;
पूर्ण

अटल पूर्णांक decode_modrm(काष्ठा x86_emulate_ctxt *ctxt,
			काष्ठा opeअक्रम *op)
अणु
	u8 sib;
	पूर्णांक index_reg, base_reg, scale;
	पूर्णांक rc = X86EMUL_CONTINUE;
	uदीर्घ modrm_ea = 0;

	ctxt->modrm_reg = ((ctxt->rex_prefix << 1) & 8); /* REX.R */
	index_reg = (ctxt->rex_prefix << 2) & 8; /* REX.X */
	base_reg = (ctxt->rex_prefix << 3) & 8; /* REX.B */

	ctxt->modrm_mod = (ctxt->modrm & 0xc0) >> 6;
	ctxt->modrm_reg |= (ctxt->modrm & 0x38) >> 3;
	ctxt->modrm_rm = base_reg | (ctxt->modrm & 0x07);
	ctxt->modrm_seg = VCPU_SREG_DS;

	अगर (ctxt->modrm_mod == 3 || (ctxt->d & NoMod)) अणु
		op->type = OP_REG;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.reg = decode_रेजिस्टर(ctxt, ctxt->modrm_rm,
				ctxt->d & ByteOp);
		अगर (ctxt->d & Sse) अणु
			op->type = OP_XMM;
			op->bytes = 16;
			op->addr.xmm = ctxt->modrm_rm;
			पढ़ो_sse_reg(&op->vec_val, ctxt->modrm_rm);
			वापस rc;
		पूर्ण
		अगर (ctxt->d & Mmx) अणु
			op->type = OP_MM;
			op->bytes = 8;
			op->addr.mm = ctxt->modrm_rm & 7;
			वापस rc;
		पूर्ण
		fetch_रेजिस्टर_opeअक्रम(op);
		वापस rc;
	पूर्ण

	op->type = OP_MEM;

	अगर (ctxt->ad_bytes == 2) अणु
		अचिन्हित bx = reg_पढ़ो(ctxt, VCPU_REGS_RBX);
		अचिन्हित bp = reg_पढ़ो(ctxt, VCPU_REGS_RBP);
		अचिन्हित si = reg_पढ़ो(ctxt, VCPU_REGS_RSI);
		अचिन्हित di = reg_पढ़ो(ctxt, VCPU_REGS_RDI);

		/* 16-bit ModR/M decode. */
		चयन (ctxt->modrm_mod) अणु
		हाल 0:
			अगर (ctxt->modrm_rm == 6)
				modrm_ea += insn_fetch(u16, ctxt);
			अवरोध;
		हाल 1:
			modrm_ea += insn_fetch(s8, ctxt);
			अवरोध;
		हाल 2:
			modrm_ea += insn_fetch(u16, ctxt);
			अवरोध;
		पूर्ण
		चयन (ctxt->modrm_rm) अणु
		हाल 0:
			modrm_ea += bx + si;
			अवरोध;
		हाल 1:
			modrm_ea += bx + di;
			अवरोध;
		हाल 2:
			modrm_ea += bp + si;
			अवरोध;
		हाल 3:
			modrm_ea += bp + di;
			अवरोध;
		हाल 4:
			modrm_ea += si;
			अवरोध;
		हाल 5:
			modrm_ea += di;
			अवरोध;
		हाल 6:
			अगर (ctxt->modrm_mod != 0)
				modrm_ea += bp;
			अवरोध;
		हाल 7:
			modrm_ea += bx;
			अवरोध;
		पूर्ण
		अगर (ctxt->modrm_rm == 2 || ctxt->modrm_rm == 3 ||
		    (ctxt->modrm_rm == 6 && ctxt->modrm_mod != 0))
			ctxt->modrm_seg = VCPU_SREG_SS;
		modrm_ea = (u16)modrm_ea;
	पूर्ण अन्यथा अणु
		/* 32/64-bit ModR/M decode. */
		अगर ((ctxt->modrm_rm & 7) == 4) अणु
			sib = insn_fetch(u8, ctxt);
			index_reg |= (sib >> 3) & 7;
			base_reg |= sib & 7;
			scale = sib >> 6;

			अगर ((base_reg & 7) == 5 && ctxt->modrm_mod == 0)
				modrm_ea += insn_fetch(s32, ctxt);
			अन्यथा अणु
				modrm_ea += reg_पढ़ो(ctxt, base_reg);
				adjust_modrm_seg(ctxt, base_reg);
				/* Increment ESP on POP [ESP] */
				अगर ((ctxt->d & IncSP) &&
				    base_reg == VCPU_REGS_RSP)
					modrm_ea += ctxt->op_bytes;
			पूर्ण
			अगर (index_reg != 4)
				modrm_ea += reg_पढ़ो(ctxt, index_reg) << scale;
		पूर्ण अन्यथा अगर ((ctxt->modrm_rm & 7) == 5 && ctxt->modrm_mod == 0) अणु
			modrm_ea += insn_fetch(s32, ctxt);
			अगर (ctxt->mode == X86EMUL_MODE_PROT64)
				ctxt->rip_relative = 1;
		पूर्ण अन्यथा अणु
			base_reg = ctxt->modrm_rm;
			modrm_ea += reg_पढ़ो(ctxt, base_reg);
			adjust_modrm_seg(ctxt, base_reg);
		पूर्ण
		चयन (ctxt->modrm_mod) अणु
		हाल 1:
			modrm_ea += insn_fetch(s8, ctxt);
			अवरोध;
		हाल 2:
			modrm_ea += insn_fetch(s32, ctxt);
			अवरोध;
		पूर्ण
	पूर्ण
	op->addr.mem.ea = modrm_ea;
	अगर (ctxt->ad_bytes != 8)
		ctxt->memop.addr.mem.ea = (u32)ctxt->memop.addr.mem.ea;

करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक decode_असल(काष्ठा x86_emulate_ctxt *ctxt,
		      काष्ठा opeअक्रम *op)
अणु
	पूर्णांक rc = X86EMUL_CONTINUE;

	op->type = OP_MEM;
	चयन (ctxt->ad_bytes) अणु
	हाल 2:
		op->addr.mem.ea = insn_fetch(u16, ctxt);
		अवरोध;
	हाल 4:
		op->addr.mem.ea = insn_fetch(u32, ctxt);
		अवरोध;
	हाल 8:
		op->addr.mem.ea = insn_fetch(u64, ctxt);
		अवरोध;
	पूर्ण
करोne:
	वापस rc;
पूर्ण

अटल व्योम fetch_bit_opeअक्रम(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	दीर्घ sv = 0, mask;

	अगर (ctxt->dst.type == OP_MEM && ctxt->src.type == OP_REG) अणु
		mask = ~((दीर्घ)ctxt->dst.bytes * 8 - 1);

		अगर (ctxt->src.bytes == 2)
			sv = (s16)ctxt->src.val & (s16)mask;
		अन्यथा अगर (ctxt->src.bytes == 4)
			sv = (s32)ctxt->src.val & (s32)mask;
		अन्यथा
			sv = (s64)ctxt->src.val & (s64)mask;

		ctxt->dst.addr.mem.ea = address_mask(ctxt,
					   ctxt->dst.addr.mem.ea + (sv >> 3));
	पूर्ण

	/* only subword offset */
	ctxt->src.val &= (ctxt->dst.bytes << 3) - 1;
पूर्ण

अटल पूर्णांक पढ़ो_emulated(काष्ठा x86_emulate_ctxt *ctxt,
			 अचिन्हित दीर्घ addr, व्योम *dest, अचिन्हित size)
अणु
	पूर्णांक rc;
	काष्ठा पढ़ो_cache *mc = &ctxt->mem_पढ़ो;

	अगर (mc->pos < mc->end)
		जाओ पढ़ो_cached;

	WARN_ON((mc->end + size) >= माप(mc->data));

	rc = ctxt->ops->पढ़ो_emulated(ctxt, addr, mc->data + mc->end, size,
				      &ctxt->exception);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	mc->end += size;

पढ़ो_cached:
	स_नकल(dest, mc->data + mc->pos, size);
	mc->pos += size;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक segmented_पढ़ो(काष्ठा x86_emulate_ctxt *ctxt,
			  काष्ठा segmented_address addr,
			  व्योम *data,
			  अचिन्हित size)
अणु
	पूर्णांक rc;
	uदीर्घ linear;

	rc = linearize(ctxt, addr, size, false, &linear);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	वापस पढ़ो_emulated(ctxt, linear, data, size);
पूर्ण

अटल पूर्णांक segmented_ग_लिखो(काष्ठा x86_emulate_ctxt *ctxt,
			   काष्ठा segmented_address addr,
			   स्थिर व्योम *data,
			   अचिन्हित size)
अणु
	पूर्णांक rc;
	uदीर्घ linear;

	rc = linearize(ctxt, addr, size, true, &linear);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	वापस ctxt->ops->ग_लिखो_emulated(ctxt, linear, data, size,
					 &ctxt->exception);
पूर्ण

अटल पूर्णांक segmented_cmpxchg(काष्ठा x86_emulate_ctxt *ctxt,
			     काष्ठा segmented_address addr,
			     स्थिर व्योम *orig_data, स्थिर व्योम *data,
			     अचिन्हित size)
अणु
	पूर्णांक rc;
	uदीर्घ linear;

	rc = linearize(ctxt, addr, size, true, &linear);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	वापस ctxt->ops->cmpxchg_emulated(ctxt, linear, orig_data, data,
					   size, &ctxt->exception);
पूर्ण

अटल पूर्णांक pio_in_emulated(काष्ठा x86_emulate_ctxt *ctxt,
			   अचिन्हित पूर्णांक size, अचिन्हित लघु port,
			   व्योम *dest)
अणु
	काष्ठा पढ़ो_cache *rc = &ctxt->io_पढ़ो;

	अगर (rc->pos == rc->end) अणु /* refill pio पढ़ो ahead */
		अचिन्हित पूर्णांक in_page, n;
		अचिन्हित पूर्णांक count = ctxt->rep_prefix ?
			address_mask(ctxt, reg_पढ़ो(ctxt, VCPU_REGS_RCX)) : 1;
		in_page = (ctxt->eflags & X86_EFLAGS_DF) ?
			offset_in_page(reg_पढ़ो(ctxt, VCPU_REGS_RDI)) :
			PAGE_SIZE - offset_in_page(reg_पढ़ो(ctxt, VCPU_REGS_RDI));
		n = min3(in_page, (अचिन्हित पूर्णांक)माप(rc->data) / size, count);
		अगर (n == 0)
			n = 1;
		rc->pos = rc->end = 0;
		अगर (!ctxt->ops->pio_in_emulated(ctxt, size, port, rc->data, n))
			वापस 0;
		rc->end = n * size;
	पूर्ण

	अगर (ctxt->rep_prefix && (ctxt->d & String) &&
	    !(ctxt->eflags & X86_EFLAGS_DF)) अणु
		ctxt->dst.data = rc->data + rc->pos;
		ctxt->dst.type = OP_MEM_STR;
		ctxt->dst.count = (rc->end - rc->pos) / size;
		rc->pos = rc->end;
	पूर्ण अन्यथा अणु
		स_नकल(dest, rc->data + rc->pos, size);
		rc->pos += size;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक पढ़ो_पूर्णांकerrupt_descriptor(काष्ठा x86_emulate_ctxt *ctxt,
				     u16 index, काष्ठा desc_काष्ठा *desc)
अणु
	काष्ठा desc_ptr dt;
	uदीर्घ addr;

	ctxt->ops->get_idt(ctxt, &dt);

	अगर (dt.size < index * 8 + 7)
		वापस emulate_gp(ctxt, index << 3 | 0x2);

	addr = dt.address + index * 8;
	वापस linear_पढ़ो_प्रणाली(ctxt, addr, desc, माप(*desc));
पूर्ण

अटल व्योम get_descriptor_table_ptr(काष्ठा x86_emulate_ctxt *ctxt,
				     u16 selector, काष्ठा desc_ptr *dt)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	u32 base3 = 0;

	अगर (selector & 1 << 2) अणु
		काष्ठा desc_काष्ठा desc;
		u16 sel;

		स_रखो(dt, 0, माप(*dt));
		अगर (!ops->get_segment(ctxt, &sel, &desc, &base3,
				      VCPU_SREG_LDTR))
			वापस;

		dt->size = desc_limit_scaled(&desc); /* what अगर limit > 65535? */
		dt->address = get_desc_base(&desc) | ((u64)base3 << 32);
	पूर्ण अन्यथा
		ops->get_gdt(ctxt, dt);
पूर्ण

अटल पूर्णांक get_descriptor_ptr(काष्ठा x86_emulate_ctxt *ctxt,
			      u16 selector, uदीर्घ *desc_addr_p)
अणु
	काष्ठा desc_ptr dt;
	u16 index = selector >> 3;
	uदीर्घ addr;

	get_descriptor_table_ptr(ctxt, selector, &dt);

	अगर (dt.size < index * 8 + 7)
		वापस emulate_gp(ctxt, selector & 0xfffc);

	addr = dt.address + index * 8;

#अगर_घोषित CONFIG_X86_64
	अगर (addr >> 32 != 0) अणु
		u64 efer = 0;

		ctxt->ops->get_msr(ctxt, MSR_EFER, &efer);
		अगर (!(efer & EFER_LMA))
			addr &= (u32)-1;
	पूर्ण
#पूर्ण_अगर

	*desc_addr_p = addr;
	वापस X86EMUL_CONTINUE;
पूर्ण

/* allowed just क्रम 8 bytes segments */
अटल पूर्णांक पढ़ो_segment_descriptor(काष्ठा x86_emulate_ctxt *ctxt,
				   u16 selector, काष्ठा desc_काष्ठा *desc,
				   uदीर्घ *desc_addr_p)
अणु
	पूर्णांक rc;

	rc = get_descriptor_ptr(ctxt, selector, desc_addr_p);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	वापस linear_पढ़ो_प्रणाली(ctxt, *desc_addr_p, desc, माप(*desc));
पूर्ण

/* allowed just क्रम 8 bytes segments */
अटल पूर्णांक ग_लिखो_segment_descriptor(काष्ठा x86_emulate_ctxt *ctxt,
				    u16 selector, काष्ठा desc_काष्ठा *desc)
अणु
	पूर्णांक rc;
	uदीर्घ addr;

	rc = get_descriptor_ptr(ctxt, selector, &addr);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	वापस linear_ग_लिखो_प्रणाली(ctxt, addr, desc, माप(*desc));
पूर्ण

अटल पूर्णांक __load_segment_descriptor(काष्ठा x86_emulate_ctxt *ctxt,
				     u16 selector, पूर्णांक seg, u8 cpl,
				     क्रमागत x86_transfer_type transfer,
				     काष्ठा desc_काष्ठा *desc)
अणु
	काष्ठा desc_काष्ठा seg_desc, old_desc;
	u8 dpl, rpl;
	अचिन्हित err_vec = GP_VECTOR;
	u32 err_code = 0;
	bool null_selector = !(selector & ~0x3); /* 0000-0003 are null */
	uदीर्घ desc_addr;
	पूर्णांक ret;
	u16 dummy;
	u32 base3 = 0;

	स_रखो(&seg_desc, 0, माप(seg_desc));

	अगर (ctxt->mode == X86EMUL_MODE_REAL) अणु
		/* set real mode segment descriptor (keep limit etc. क्रम
		 * unreal mode) */
		ctxt->ops->get_segment(ctxt, &dummy, &seg_desc, शून्य, seg);
		set_desc_base(&seg_desc, selector << 4);
		जाओ load;
	पूर्ण अन्यथा अगर (seg <= VCPU_SREG_GS && ctxt->mode == X86EMUL_MODE_VM86) अणु
		/* VM86 needs a clean new segment descriptor */
		set_desc_base(&seg_desc, selector << 4);
		set_desc_limit(&seg_desc, 0xffff);
		seg_desc.type = 3;
		seg_desc.p = 1;
		seg_desc.s = 1;
		seg_desc.dpl = 3;
		जाओ load;
	पूर्ण

	rpl = selector & 3;

	/* TR should be in GDT only */
	अगर (seg == VCPU_SREG_TR && (selector & (1 << 2)))
		जाओ exception;

	/* शून्य selector is not valid क्रम TR, CS and (except क्रम दीर्घ mode) SS */
	अगर (null_selector) अणु
		अगर (seg == VCPU_SREG_CS || seg == VCPU_SREG_TR)
			जाओ exception;

		अगर (seg == VCPU_SREG_SS) अणु
			अगर (ctxt->mode != X86EMUL_MODE_PROT64 || rpl != cpl)
				जाओ exception;

			/*
			 * ctxt->ops->set_segment expects the CPL to be in
			 * SS.DPL, so fake an expand-up 32-bit data segment.
			 */
			seg_desc.type = 3;
			seg_desc.p = 1;
			seg_desc.s = 1;
			seg_desc.dpl = cpl;
			seg_desc.d = 1;
			seg_desc.g = 1;
		पूर्ण

		/* Skip all following checks */
		जाओ load;
	पूर्ण

	ret = पढ़ो_segment_descriptor(ctxt, selector, &seg_desc, &desc_addr);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	err_code = selector & 0xfffc;
	err_vec = (transfer == X86_TRANSFER_TASK_SWITCH) ? TS_VECTOR :
							   GP_VECTOR;

	/* can't load प्रणाली descriptor पूर्णांकo segment selector */
	अगर (seg <= VCPU_SREG_GS && !seg_desc.s) अणु
		अगर (transfer == X86_TRANSFER_CALL_JMP)
			वापस X86EMUL_UNHANDLEABLE;
		जाओ exception;
	पूर्ण

	अगर (!seg_desc.p) अणु
		err_vec = (seg == VCPU_SREG_SS) ? SS_VECTOR : NP_VECTOR;
		जाओ exception;
	पूर्ण

	dpl = seg_desc.dpl;

	चयन (seg) अणु
	हाल VCPU_SREG_SS:
		/*
		 * segment is not a writable data segment or segment
		 * selector's RPL != CPL or segment selector's RPL != CPL
		 */
		अगर (rpl != cpl || (seg_desc.type & 0xa) != 0x2 || dpl != cpl)
			जाओ exception;
		अवरोध;
	हाल VCPU_SREG_CS:
		अगर (!(seg_desc.type & 8))
			जाओ exception;

		अगर (seg_desc.type & 4) अणु
			/* conक्रमming */
			अगर (dpl > cpl)
				जाओ exception;
		पूर्ण अन्यथा अणु
			/* nonconक्रमming */
			अगर (rpl > cpl || dpl != cpl)
				जाओ exception;
		पूर्ण
		/* in दीर्घ-mode d/b must be clear अगर l is set */
		अगर (seg_desc.d && seg_desc.l) अणु
			u64 efer = 0;

			ctxt->ops->get_msr(ctxt, MSR_EFER, &efer);
			अगर (efer & EFER_LMA)
				जाओ exception;
		पूर्ण

		/* CS(RPL) <- CPL */
		selector = (selector & 0xfffc) | cpl;
		अवरोध;
	हाल VCPU_SREG_TR:
		अगर (seg_desc.s || (seg_desc.type != 1 && seg_desc.type != 9))
			जाओ exception;
		old_desc = seg_desc;
		seg_desc.type |= 2; /* busy */
		ret = ctxt->ops->cmpxchg_emulated(ctxt, desc_addr, &old_desc, &seg_desc,
						  माप(seg_desc), &ctxt->exception);
		अगर (ret != X86EMUL_CONTINUE)
			वापस ret;
		अवरोध;
	हाल VCPU_SREG_LDTR:
		अगर (seg_desc.s || seg_desc.type != 2)
			जाओ exception;
		अवरोध;
	शेष: /*  DS, ES, FS, or GS */
		/*
		 * segment is not a data or पढ़ोable code segment or
		 * ((segment is a data or nonconक्रमming code segment)
		 * and (both RPL and CPL > DPL))
		 */
		अगर ((seg_desc.type & 0xa) == 0x8 ||
		    (((seg_desc.type & 0xc) != 0xc) &&
		     (rpl > dpl && cpl > dpl)))
			जाओ exception;
		अवरोध;
	पूर्ण

	अगर (seg_desc.s) अणु
		/* mark segment as accessed */
		अगर (!(seg_desc.type & 1)) अणु
			seg_desc.type |= 1;
			ret = ग_लिखो_segment_descriptor(ctxt, selector,
						       &seg_desc);
			अगर (ret != X86EMUL_CONTINUE)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (ctxt->mode == X86EMUL_MODE_PROT64) अणु
		ret = linear_पढ़ो_प्रणाली(ctxt, desc_addr+8, &base3, माप(base3));
		अगर (ret != X86EMUL_CONTINUE)
			वापस ret;
		अगर (emul_is_noncanonical_address(get_desc_base(&seg_desc) |
				((u64)base3 << 32), ctxt))
			वापस emulate_gp(ctxt, 0);
	पूर्ण
load:
	ctxt->ops->set_segment(ctxt, selector, &seg_desc, base3, seg);
	अगर (desc)
		*desc = seg_desc;
	वापस X86EMUL_CONTINUE;
exception:
	वापस emulate_exception(ctxt, err_vec, err_code, true);
पूर्ण

अटल पूर्णांक load_segment_descriptor(काष्ठा x86_emulate_ctxt *ctxt,
				   u16 selector, पूर्णांक seg)
अणु
	u8 cpl = ctxt->ops->cpl(ctxt);

	/*
	 * None of MOV, POP and LSS can load a शून्य selector in CPL=3, but
	 * they can load it at CPL<3 (Intel's manual says only LSS can,
	 * but it's wrong).
	 *
	 * However, the Intel manual says that putting IST=1/DPL=3 in
	 * an पूर्णांकerrupt gate will result in SS=3 (the AMD manual instead
	 * says it करोesn't), so allow SS=3 in __load_segment_descriptor
	 * and only क्रमbid it here.
	 */
	अगर (seg == VCPU_SREG_SS && selector == 3 &&
	    ctxt->mode == X86EMUL_MODE_PROT64)
		वापस emulate_exception(ctxt, GP_VECTOR, 0, true);

	वापस __load_segment_descriptor(ctxt, selector, seg, cpl,
					 X86_TRANSFER_NONE, शून्य);
पूर्ण

अटल व्योम ग_लिखो_रेजिस्टर_opeअक्रम(काष्ठा opeअक्रम *op)
अणु
	वापस assign_रेजिस्टर(op->addr.reg, op->val, op->bytes);
पूर्ण

अटल पूर्णांक ग_लिखोback(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा opeअक्रम *op)
अणु
	चयन (op->type) अणु
	हाल OP_REG:
		ग_लिखो_रेजिस्टर_opeअक्रम(op);
		अवरोध;
	हाल OP_MEM:
		अगर (ctxt->lock_prefix)
			वापस segmented_cmpxchg(ctxt,
						 op->addr.mem,
						 &op->orig_val,
						 &op->val,
						 op->bytes);
		अन्यथा
			वापस segmented_ग_लिखो(ctxt,
					       op->addr.mem,
					       &op->val,
					       op->bytes);
		अवरोध;
	हाल OP_MEM_STR:
		वापस segmented_ग_लिखो(ctxt,
				       op->addr.mem,
				       op->data,
				       op->bytes * op->count);
		अवरोध;
	हाल OP_XMM:
		ग_लिखो_sse_reg(&op->vec_val, op->addr.xmm);
		अवरोध;
	हाल OP_MM:
		ग_लिखो_mmx_reg(&op->mm_val, op->addr.mm);
		अवरोध;
	हाल OP_NONE:
		/* no ग_लिखोback */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक push(काष्ठा x86_emulate_ctxt *ctxt, व्योम *data, पूर्णांक bytes)
अणु
	काष्ठा segmented_address addr;

	rsp_increment(ctxt, -bytes);
	addr.ea = reg_पढ़ो(ctxt, VCPU_REGS_RSP) & stack_mask(ctxt);
	addr.seg = VCPU_SREG_SS;

	वापस segmented_ग_लिखो(ctxt, addr, data, bytes);
पूर्ण

अटल पूर्णांक em_push(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस push(ctxt, &ctxt->src.val, ctxt->op_bytes);
पूर्ण

अटल पूर्णांक emulate_pop(काष्ठा x86_emulate_ctxt *ctxt,
		       व्योम *dest, पूर्णांक len)
अणु
	पूर्णांक rc;
	काष्ठा segmented_address addr;

	addr.ea = reg_पढ़ो(ctxt, VCPU_REGS_RSP) & stack_mask(ctxt);
	addr.seg = VCPU_SREG_SS;
	rc = segmented_पढ़ो(ctxt, addr, dest, len);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	rsp_increment(ctxt, len);
	वापस rc;
पूर्ण

अटल पूर्णांक em_pop(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस emulate_pop(ctxt, &ctxt->dst.val, ctxt->op_bytes);
पूर्ण

अटल पूर्णांक emulate_popf(काष्ठा x86_emulate_ctxt *ctxt,
			व्योम *dest, पूर्णांक len)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ val, change_mask;
	पूर्णांक iopl = (ctxt->eflags & X86_EFLAGS_IOPL) >> X86_EFLAGS_IOPL_BIT;
	पूर्णांक cpl = ctxt->ops->cpl(ctxt);

	rc = emulate_pop(ctxt, &val, len);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	change_mask = X86_EFLAGS_CF | X86_EFLAGS_PF | X86_EFLAGS_AF |
		      X86_EFLAGS_ZF | X86_EFLAGS_SF | X86_EFLAGS_OF |
		      X86_EFLAGS_TF | X86_EFLAGS_DF | X86_EFLAGS_NT |
		      X86_EFLAGS_AC | X86_EFLAGS_ID;

	चयन(ctxt->mode) अणु
	हाल X86EMUL_MODE_PROT64:
	हाल X86EMUL_MODE_PROT32:
	हाल X86EMUL_MODE_PROT16:
		अगर (cpl == 0)
			change_mask |= X86_EFLAGS_IOPL;
		अगर (cpl <= iopl)
			change_mask |= X86_EFLAGS_IF;
		अवरोध;
	हाल X86EMUL_MODE_VM86:
		अगर (iopl < 3)
			वापस emulate_gp(ctxt, 0);
		change_mask |= X86_EFLAGS_IF;
		अवरोध;
	शेष: /* real mode */
		change_mask |= (X86_EFLAGS_IOPL | X86_EFLAGS_IF);
		अवरोध;
	पूर्ण

	*(अचिन्हित दीर्घ *)dest =
		(ctxt->eflags & ~change_mask) | (val & change_mask);

	वापस rc;
पूर्ण

अटल पूर्णांक em_popf(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->dst.type = OP_REG;
	ctxt->dst.addr.reg = &ctxt->eflags;
	ctxt->dst.bytes = ctxt->op_bytes;
	वापस emulate_popf(ctxt, &ctxt->dst.val, ctxt->op_bytes);
पूर्ण

अटल पूर्णांक em_enter(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;
	अचिन्हित frame_size = ctxt->src.val;
	अचिन्हित nesting_level = ctxt->src2.val & 31;
	uदीर्घ rbp;

	अगर (nesting_level)
		वापस X86EMUL_UNHANDLEABLE;

	rbp = reg_पढ़ो(ctxt, VCPU_REGS_RBP);
	rc = push(ctxt, &rbp, stack_size(ctxt));
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	assign_masked(reg_rmw(ctxt, VCPU_REGS_RBP), reg_पढ़ो(ctxt, VCPU_REGS_RSP),
		      stack_mask(ctxt));
	assign_masked(reg_rmw(ctxt, VCPU_REGS_RSP),
		      reg_पढ़ो(ctxt, VCPU_REGS_RSP) - frame_size,
		      stack_mask(ctxt));
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_leave(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	assign_masked(reg_rmw(ctxt, VCPU_REGS_RSP), reg_पढ़ो(ctxt, VCPU_REGS_RBP),
		      stack_mask(ctxt));
	वापस emulate_pop(ctxt, reg_rmw(ctxt, VCPU_REGS_RBP), ctxt->op_bytes);
पूर्ण

अटल पूर्णांक em_push_sreg(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक seg = ctxt->src2.val;

	ctxt->src.val = get_segment_selector(ctxt, seg);
	अगर (ctxt->op_bytes == 4) अणु
		rsp_increment(ctxt, -2);
		ctxt->op_bytes = 2;
	पूर्ण

	वापस em_push(ctxt);
पूर्ण

अटल पूर्णांक em_pop_sreg(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक seg = ctxt->src2.val;
	अचिन्हित दीर्घ selector;
	पूर्णांक rc;

	rc = emulate_pop(ctxt, &selector, 2);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	अगर (ctxt->modrm_reg == VCPU_SREG_SS)
		ctxt->पूर्णांकerruptibility = KVM_X86_SHADOW_INT_MOV_SS;
	अगर (ctxt->op_bytes > 2)
		rsp_increment(ctxt, ctxt->op_bytes - 2);

	rc = load_segment_descriptor(ctxt, (u16)selector, seg);
	वापस rc;
पूर्ण

अटल पूर्णांक em_pusha(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अचिन्हित दीर्घ old_esp = reg_पढ़ो(ctxt, VCPU_REGS_RSP);
	पूर्णांक rc = X86EMUL_CONTINUE;
	पूर्णांक reg = VCPU_REGS_RAX;

	जबतक (reg <= VCPU_REGS_RDI) अणु
		(reg == VCPU_REGS_RSP) ?
		(ctxt->src.val = old_esp) : (ctxt->src.val = reg_पढ़ो(ctxt, reg));

		rc = em_push(ctxt);
		अगर (rc != X86EMUL_CONTINUE)
			वापस rc;

		++reg;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक em_pushf(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->src.val = (अचिन्हित दीर्घ)ctxt->eflags & ~X86_EFLAGS_VM;
	वापस em_push(ctxt);
पूर्ण

अटल पूर्णांक em_popa(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc = X86EMUL_CONTINUE;
	पूर्णांक reg = VCPU_REGS_RDI;
	u32 val;

	जबतक (reg >= VCPU_REGS_RAX) अणु
		अगर (reg == VCPU_REGS_RSP) अणु
			rsp_increment(ctxt, ctxt->op_bytes);
			--reg;
		पूर्ण

		rc = emulate_pop(ctxt, &val, ctxt->op_bytes);
		अगर (rc != X86EMUL_CONTINUE)
			अवरोध;
		assign_रेजिस्टर(reg_rmw(ctxt, reg), val, ctxt->op_bytes);
		--reg;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक __emulate_पूर्णांक_real(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक irq)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	पूर्णांक rc;
	काष्ठा desc_ptr dt;
	gva_t cs_addr;
	gva_t eip_addr;
	u16 cs, eip;

	/* TODO: Add limit checks */
	ctxt->src.val = ctxt->eflags;
	rc = em_push(ctxt);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	ctxt->eflags &= ~(X86_EFLAGS_IF | X86_EFLAGS_TF | X86_EFLAGS_AC);

	ctxt->src.val = get_segment_selector(ctxt, VCPU_SREG_CS);
	rc = em_push(ctxt);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	ctxt->src.val = ctxt->_eip;
	rc = em_push(ctxt);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	ops->get_idt(ctxt, &dt);

	eip_addr = dt.address + (irq << 2);
	cs_addr = dt.address + (irq << 2) + 2;

	rc = linear_पढ़ो_प्रणाली(ctxt, cs_addr, &cs, 2);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	rc = linear_पढ़ो_प्रणाली(ctxt, eip_addr, &eip, 2);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	rc = load_segment_descriptor(ctxt, cs, VCPU_SREG_CS);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	ctxt->_eip = eip;

	वापस rc;
पूर्ण

पूर्णांक emulate_पूर्णांक_real(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक irq)
अणु
	पूर्णांक rc;

	invalidate_रेजिस्टरs(ctxt);
	rc = __emulate_पूर्णांक_real(ctxt, irq);
	अगर (rc == X86EMUL_CONTINUE)
		ग_लिखोback_रेजिस्टरs(ctxt);
	वापस rc;
पूर्ण

अटल पूर्णांक emulate_पूर्णांक(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक irq)
अणु
	चयन(ctxt->mode) अणु
	हाल X86EMUL_MODE_REAL:
		वापस __emulate_पूर्णांक_real(ctxt, irq);
	हाल X86EMUL_MODE_VM86:
	हाल X86EMUL_MODE_PROT16:
	हाल X86EMUL_MODE_PROT32:
	हाल X86EMUL_MODE_PROT64:
	शेष:
		/* Protected mode पूर्णांकerrupts unimplemented yet */
		वापस X86EMUL_UNHANDLEABLE;
	पूर्ण
पूर्ण

अटल पूर्णांक emulate_iret_real(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc = X86EMUL_CONTINUE;
	अचिन्हित दीर्घ temp_eip = 0;
	अचिन्हित दीर्घ temp_eflags = 0;
	अचिन्हित दीर्घ cs = 0;
	अचिन्हित दीर्घ mask = X86_EFLAGS_CF | X86_EFLAGS_PF | X86_EFLAGS_AF |
			     X86_EFLAGS_ZF | X86_EFLAGS_SF | X86_EFLAGS_TF |
			     X86_EFLAGS_IF | X86_EFLAGS_DF | X86_EFLAGS_OF |
			     X86_EFLAGS_IOPL | X86_EFLAGS_NT | X86_EFLAGS_RF |
			     X86_EFLAGS_AC | X86_EFLAGS_ID |
			     X86_EFLAGS_FIXED;
	अचिन्हित दीर्घ vm86_mask = X86_EFLAGS_VM | X86_EFLAGS_VIF |
				  X86_EFLAGS_VIP;

	/* TODO: Add stack limit check */

	rc = emulate_pop(ctxt, &temp_eip, ctxt->op_bytes);

	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	अगर (temp_eip & ~0xffff)
		वापस emulate_gp(ctxt, 0);

	rc = emulate_pop(ctxt, &cs, ctxt->op_bytes);

	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	rc = emulate_pop(ctxt, &temp_eflags, ctxt->op_bytes);

	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	rc = load_segment_descriptor(ctxt, (u16)cs, VCPU_SREG_CS);

	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	ctxt->_eip = temp_eip;

	अगर (ctxt->op_bytes == 4)
		ctxt->eflags = ((temp_eflags & mask) | (ctxt->eflags & vm86_mask));
	अन्यथा अगर (ctxt->op_bytes == 2) अणु
		ctxt->eflags &= ~0xffff;
		ctxt->eflags |= temp_eflags;
	पूर्ण

	ctxt->eflags &= ~EFLG_RESERVED_ZEROS_MASK; /* Clear reserved zeros */
	ctxt->eflags |= X86_EFLAGS_FIXED;
	ctxt->ops->set_nmi_mask(ctxt, false);

	वापस rc;
पूर्ण

अटल पूर्णांक em_iret(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	चयन(ctxt->mode) अणु
	हाल X86EMUL_MODE_REAL:
		वापस emulate_iret_real(ctxt);
	हाल X86EMUL_MODE_VM86:
	हाल X86EMUL_MODE_PROT16:
	हाल X86EMUL_MODE_PROT32:
	हाल X86EMUL_MODE_PROT64:
	शेष:
		/* iret from रक्षित mode unimplemented yet */
		वापस X86EMUL_UNHANDLEABLE;
	पूर्ण
पूर्ण

अटल पूर्णांक em_jmp_far(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;
	अचिन्हित लघु sel;
	काष्ठा desc_काष्ठा new_desc;
	u8 cpl = ctxt->ops->cpl(ctxt);

	स_नकल(&sel, ctxt->src.valptr + ctxt->op_bytes, 2);

	rc = __load_segment_descriptor(ctxt, sel, VCPU_SREG_CS, cpl,
				       X86_TRANSFER_CALL_JMP,
				       &new_desc);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	rc = assign_eip_far(ctxt, ctxt->src.val, &new_desc);
	/* Error handling is not implemented. */
	अगर (rc != X86EMUL_CONTINUE)
		वापस X86EMUL_UNHANDLEABLE;

	वापस rc;
पूर्ण

अटल पूर्णांक em_jmp_असल(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस assign_eip_near(ctxt, ctxt->src.val);
पूर्ण

अटल पूर्णांक em_call_near_असल(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;
	दीर्घ पूर्णांक old_eip;

	old_eip = ctxt->_eip;
	rc = assign_eip_near(ctxt, ctxt->src.val);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	ctxt->src.val = old_eip;
	rc = em_push(ctxt);
	वापस rc;
पूर्ण

अटल पूर्णांक em_cmpxchg8b(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 old = ctxt->dst.orig_val64;

	अगर (ctxt->dst.bytes == 16)
		वापस X86EMUL_UNHANDLEABLE;

	अगर (((u32) (old >> 0) != (u32) reg_पढ़ो(ctxt, VCPU_REGS_RAX)) ||
	    ((u32) (old >> 32) != (u32) reg_पढ़ो(ctxt, VCPU_REGS_RDX))) अणु
		*reg_ग_लिखो(ctxt, VCPU_REGS_RAX) = (u32) (old >> 0);
		*reg_ग_लिखो(ctxt, VCPU_REGS_RDX) = (u32) (old >> 32);
		ctxt->eflags &= ~X86_EFLAGS_ZF;
	पूर्ण अन्यथा अणु
		ctxt->dst.val64 = ((u64)reg_पढ़ो(ctxt, VCPU_REGS_RCX) << 32) |
			(u32) reg_पढ़ो(ctxt, VCPU_REGS_RBX);

		ctxt->eflags |= X86_EFLAGS_ZF;
	पूर्ण
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_ret(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ eip;

	rc = emulate_pop(ctxt, &eip, ctxt->op_bytes);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	वापस assign_eip_near(ctxt, eip);
पूर्ण

अटल पूर्णांक em_ret_far(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ eip, cs;
	पूर्णांक cpl = ctxt->ops->cpl(ctxt);
	काष्ठा desc_काष्ठा new_desc;

	rc = emulate_pop(ctxt, &eip, ctxt->op_bytes);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	rc = emulate_pop(ctxt, &cs, ctxt->op_bytes);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	/* Outer-privilege level वापस is not implemented */
	अगर (ctxt->mode >= X86EMUL_MODE_PROT16 && (cs & 3) > cpl)
		वापस X86EMUL_UNHANDLEABLE;
	rc = __load_segment_descriptor(ctxt, (u16)cs, VCPU_SREG_CS, cpl,
				       X86_TRANSFER_RET,
				       &new_desc);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	rc = assign_eip_far(ctxt, eip, &new_desc);
	/* Error handling is not implemented. */
	अगर (rc != X86EMUL_CONTINUE)
		वापस X86EMUL_UNHANDLEABLE;

	वापस rc;
पूर्ण

अटल पूर्णांक em_ret_far_imm(काष्ठा x86_emulate_ctxt *ctxt)
अणु
        पूर्णांक rc;

        rc = em_ret_far(ctxt);
        अगर (rc != X86EMUL_CONTINUE)
                वापस rc;
        rsp_increment(ctxt, ctxt->src.val);
        वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_cmpxchg(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/* Save real source value, then compare EAX against destination. */
	ctxt->dst.orig_val = ctxt->dst.val;
	ctxt->dst.val = reg_पढ़ो(ctxt, VCPU_REGS_RAX);
	ctxt->src.orig_val = ctxt->src.val;
	ctxt->src.val = ctxt->dst.orig_val;
	fastop(ctxt, em_cmp);

	अगर (ctxt->eflags & X86_EFLAGS_ZF) अणु
		/* Success: ग_लिखो back to memory; no update of EAX */
		ctxt->src.type = OP_NONE;
		ctxt->dst.val = ctxt->src.orig_val;
	पूर्ण अन्यथा अणु
		/* Failure: ग_लिखो the value we saw to EAX. */
		ctxt->src.type = OP_REG;
		ctxt->src.addr.reg = reg_rmw(ctxt, VCPU_REGS_RAX);
		ctxt->src.val = ctxt->dst.orig_val;
		/* Create ग_लिखो-cycle to dest by writing the same value */
		ctxt->dst.val = ctxt->dst.orig_val;
	पूर्ण
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_lseg(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक seg = ctxt->src2.val;
	अचिन्हित लघु sel;
	पूर्णांक rc;

	स_नकल(&sel, ctxt->src.valptr + ctxt->op_bytes, 2);

	rc = load_segment_descriptor(ctxt, sel, seg);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	ctxt->dst.val = ctxt->src.val;
	वापस rc;
पूर्ण

अटल पूर्णांक emulator_has_दीर्घmode(काष्ठा x86_emulate_ctxt *ctxt)
अणु
#अगर_घोषित CONFIG_X86_64
	वापस ctxt->ops->guest_has_दीर्घ_mode(ctxt);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल व्योम rsm_set_desc_flags(काष्ठा desc_काष्ठा *desc, u32 flags)
अणु
	desc->g    = (flags >> 23) & 1;
	desc->d    = (flags >> 22) & 1;
	desc->l    = (flags >> 21) & 1;
	desc->avl  = (flags >> 20) & 1;
	desc->p    = (flags >> 15) & 1;
	desc->dpl  = (flags >> 13) & 3;
	desc->s    = (flags >> 12) & 1;
	desc->type = (flags >>  8) & 15;
पूर्ण

अटल पूर्णांक rsm_load_seg_32(काष्ठा x86_emulate_ctxt *ctxt, स्थिर अक्षर *smstate,
			   पूर्णांक n)
अणु
	काष्ठा desc_काष्ठा desc;
	पूर्णांक offset;
	u16 selector;

	selector = GET_SMSTATE(u32, smstate, 0x7fa8 + n * 4);

	अगर (n < 3)
		offset = 0x7f84 + n * 12;
	अन्यथा
		offset = 0x7f2c + (n - 3) * 12;

	set_desc_base(&desc,      GET_SMSTATE(u32, smstate, offset + 8));
	set_desc_limit(&desc,     GET_SMSTATE(u32, smstate, offset + 4));
	rsm_set_desc_flags(&desc, GET_SMSTATE(u32, smstate, offset));
	ctxt->ops->set_segment(ctxt, selector, &desc, 0, n);
	वापस X86EMUL_CONTINUE;
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल पूर्णांक rsm_load_seg_64(काष्ठा x86_emulate_ctxt *ctxt, स्थिर अक्षर *smstate,
			   पूर्णांक n)
अणु
	काष्ठा desc_काष्ठा desc;
	पूर्णांक offset;
	u16 selector;
	u32 base3;

	offset = 0x7e00 + n * 16;

	selector =                GET_SMSTATE(u16, smstate, offset);
	rsm_set_desc_flags(&desc, GET_SMSTATE(u16, smstate, offset + 2) << 8);
	set_desc_limit(&desc,     GET_SMSTATE(u32, smstate, offset + 4));
	set_desc_base(&desc,      GET_SMSTATE(u32, smstate, offset + 8));
	base3 =                   GET_SMSTATE(u32, smstate, offset + 12);

	ctxt->ops->set_segment(ctxt, selector, &desc, base3, n);
	वापस X86EMUL_CONTINUE;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rsm_enter_रक्षित_mode(काष्ठा x86_emulate_ctxt *ctxt,
				    u64 cr0, u64 cr3, u64 cr4)
अणु
	पूर्णांक bad;
	u64 pcid;

	/* In order to later set CR4.PCIDE, CR3[11:0] must be zero.  */
	pcid = 0;
	अगर (cr4 & X86_CR4_PCIDE) अणु
		pcid = cr3 & 0xfff;
		cr3 &= ~0xfff;
	पूर्ण

	bad = ctxt->ops->set_cr(ctxt, 3, cr3);
	अगर (bad)
		वापस X86EMUL_UNHANDLEABLE;

	/*
	 * First enable PAE, दीर्घ mode needs it beक्रमe CR0.PG = 1 is set.
	 * Then enable रक्षित mode.	However, PCID cannot be enabled
	 * अगर EFER.LMA=0, so set it separately.
	 */
	bad = ctxt->ops->set_cr(ctxt, 4, cr4 & ~X86_CR4_PCIDE);
	अगर (bad)
		वापस X86EMUL_UNHANDLEABLE;

	bad = ctxt->ops->set_cr(ctxt, 0, cr0);
	अगर (bad)
		वापस X86EMUL_UNHANDLEABLE;

	अगर (cr4 & X86_CR4_PCIDE) अणु
		bad = ctxt->ops->set_cr(ctxt, 4, cr4);
		अगर (bad)
			वापस X86EMUL_UNHANDLEABLE;
		अगर (pcid) अणु
			bad = ctxt->ops->set_cr(ctxt, 3, cr3 | pcid);
			अगर (bad)
				वापस X86EMUL_UNHANDLEABLE;
		पूर्ण

	पूर्ण

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक rsm_load_state_32(काष्ठा x86_emulate_ctxt *ctxt,
			     स्थिर अक्षर *smstate)
अणु
	काष्ठा desc_काष्ठा desc;
	काष्ठा desc_ptr dt;
	u16 selector;
	u32 val, cr0, cr3, cr4;
	पूर्णांक i;

	cr0 =                      GET_SMSTATE(u32, smstate, 0x7ffc);
	cr3 =                      GET_SMSTATE(u32, smstate, 0x7ff8);
	ctxt->eflags =             GET_SMSTATE(u32, smstate, 0x7ff4) | X86_EFLAGS_FIXED;
	ctxt->_eip =               GET_SMSTATE(u32, smstate, 0x7ff0);

	क्रम (i = 0; i < 8; i++)
		*reg_ग_लिखो(ctxt, i) = GET_SMSTATE(u32, smstate, 0x7fd0 + i * 4);

	val = GET_SMSTATE(u32, smstate, 0x7fcc);

	अगर (ctxt->ops->set_dr(ctxt, 6, val))
		वापस X86EMUL_UNHANDLEABLE;

	val = GET_SMSTATE(u32, smstate, 0x7fc8);

	अगर (ctxt->ops->set_dr(ctxt, 7, val))
		वापस X86EMUL_UNHANDLEABLE;

	selector =                 GET_SMSTATE(u32, smstate, 0x7fc4);
	set_desc_base(&desc,       GET_SMSTATE(u32, smstate, 0x7f64));
	set_desc_limit(&desc,      GET_SMSTATE(u32, smstate, 0x7f60));
	rsm_set_desc_flags(&desc,  GET_SMSTATE(u32, smstate, 0x7f5c));
	ctxt->ops->set_segment(ctxt, selector, &desc, 0, VCPU_SREG_TR);

	selector =                 GET_SMSTATE(u32, smstate, 0x7fc0);
	set_desc_base(&desc,       GET_SMSTATE(u32, smstate, 0x7f80));
	set_desc_limit(&desc,      GET_SMSTATE(u32, smstate, 0x7f7c));
	rsm_set_desc_flags(&desc,  GET_SMSTATE(u32, smstate, 0x7f78));
	ctxt->ops->set_segment(ctxt, selector, &desc, 0, VCPU_SREG_LDTR);

	dt.address =               GET_SMSTATE(u32, smstate, 0x7f74);
	dt.size =                  GET_SMSTATE(u32, smstate, 0x7f70);
	ctxt->ops->set_gdt(ctxt, &dt);

	dt.address =               GET_SMSTATE(u32, smstate, 0x7f58);
	dt.size =                  GET_SMSTATE(u32, smstate, 0x7f54);
	ctxt->ops->set_idt(ctxt, &dt);

	क्रम (i = 0; i < 6; i++) अणु
		पूर्णांक r = rsm_load_seg_32(ctxt, smstate, i);
		अगर (r != X86EMUL_CONTINUE)
			वापस r;
	पूर्ण

	cr4 = GET_SMSTATE(u32, smstate, 0x7f14);

	ctxt->ops->set_smbase(ctxt, GET_SMSTATE(u32, smstate, 0x7ef8));

	वापस rsm_enter_रक्षित_mode(ctxt, cr0, cr3, cr4);
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल पूर्णांक rsm_load_state_64(काष्ठा x86_emulate_ctxt *ctxt,
			     स्थिर अक्षर *smstate)
अणु
	काष्ठा desc_काष्ठा desc;
	काष्ठा desc_ptr dt;
	u64 val, cr0, cr3, cr4;
	u32 base3;
	u16 selector;
	पूर्णांक i, r;

	क्रम (i = 0; i < 16; i++)
		*reg_ग_लिखो(ctxt, i) = GET_SMSTATE(u64, smstate, 0x7ff8 - i * 8);

	ctxt->_eip   = GET_SMSTATE(u64, smstate, 0x7f78);
	ctxt->eflags = GET_SMSTATE(u32, smstate, 0x7f70) | X86_EFLAGS_FIXED;

	val = GET_SMSTATE(u64, smstate, 0x7f68);

	अगर (ctxt->ops->set_dr(ctxt, 6, val))
		वापस X86EMUL_UNHANDLEABLE;

	val = GET_SMSTATE(u64, smstate, 0x7f60);

	अगर (ctxt->ops->set_dr(ctxt, 7, val))
		वापस X86EMUL_UNHANDLEABLE;

	cr0 =                       GET_SMSTATE(u64, smstate, 0x7f58);
	cr3 =                       GET_SMSTATE(u64, smstate, 0x7f50);
	cr4 =                       GET_SMSTATE(u64, smstate, 0x7f48);
	ctxt->ops->set_smbase(ctxt, GET_SMSTATE(u32, smstate, 0x7f00));
	val =                       GET_SMSTATE(u64, smstate, 0x7ed0);

	अगर (ctxt->ops->set_msr(ctxt, MSR_EFER, val & ~EFER_LMA))
		वापस X86EMUL_UNHANDLEABLE;

	selector =                  GET_SMSTATE(u32, smstate, 0x7e90);
	rsm_set_desc_flags(&desc,   GET_SMSTATE(u32, smstate, 0x7e92) << 8);
	set_desc_limit(&desc,       GET_SMSTATE(u32, smstate, 0x7e94));
	set_desc_base(&desc,        GET_SMSTATE(u32, smstate, 0x7e98));
	base3 =                     GET_SMSTATE(u32, smstate, 0x7e9c);
	ctxt->ops->set_segment(ctxt, selector, &desc, base3, VCPU_SREG_TR);

	dt.size =                   GET_SMSTATE(u32, smstate, 0x7e84);
	dt.address =                GET_SMSTATE(u64, smstate, 0x7e88);
	ctxt->ops->set_idt(ctxt, &dt);

	selector =                  GET_SMSTATE(u32, smstate, 0x7e70);
	rsm_set_desc_flags(&desc,   GET_SMSTATE(u32, smstate, 0x7e72) << 8);
	set_desc_limit(&desc,       GET_SMSTATE(u32, smstate, 0x7e74));
	set_desc_base(&desc,        GET_SMSTATE(u32, smstate, 0x7e78));
	base3 =                     GET_SMSTATE(u32, smstate, 0x7e7c);
	ctxt->ops->set_segment(ctxt, selector, &desc, base3, VCPU_SREG_LDTR);

	dt.size =                   GET_SMSTATE(u32, smstate, 0x7e64);
	dt.address =                GET_SMSTATE(u64, smstate, 0x7e68);
	ctxt->ops->set_gdt(ctxt, &dt);

	r = rsm_enter_रक्षित_mode(ctxt, cr0, cr3, cr4);
	अगर (r != X86EMUL_CONTINUE)
		वापस r;

	क्रम (i = 0; i < 6; i++) अणु
		r = rsm_load_seg_64(ctxt, smstate, i);
		अगर (r != X86EMUL_CONTINUE)
			वापस r;
	पूर्ण

	वापस X86EMUL_CONTINUE;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक em_rsm(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अचिन्हित दीर्घ cr0, cr4, efer;
	अक्षर buf[512];
	u64 smbase;
	पूर्णांक ret;

	अगर ((ctxt->ops->get_hflags(ctxt) & X86EMUL_SMM_MASK) == 0)
		वापस emulate_ud(ctxt);

	smbase = ctxt->ops->get_smbase(ctxt);

	ret = ctxt->ops->पढ़ो_phys(ctxt, smbase + 0xfe00, buf, माप(buf));
	अगर (ret != X86EMUL_CONTINUE)
		वापस X86EMUL_UNHANDLEABLE;

	अगर ((ctxt->ops->get_hflags(ctxt) & X86EMUL_SMM_INSIDE_NMI_MASK) == 0)
		ctxt->ops->set_nmi_mask(ctxt, false);

	ctxt->ops->set_hflags(ctxt, ctxt->ops->get_hflags(ctxt) &
		~(X86EMUL_SMM_INSIDE_NMI_MASK | X86EMUL_SMM_MASK));

	/*
	 * Get back to real mode, to prepare a safe state in which to load
	 * CR0/CR3/CR4/EFER.  It's all a bit more complicated अगर the vCPU
	 * supports दीर्घ mode.
	 */
	अगर (emulator_has_दीर्घmode(ctxt)) अणु
		काष्ठा desc_काष्ठा cs_desc;

		/* Zero CR4.PCIDE beक्रमe CR0.PG.  */
		cr4 = ctxt->ops->get_cr(ctxt, 4);
		अगर (cr4 & X86_CR4_PCIDE)
			ctxt->ops->set_cr(ctxt, 4, cr4 & ~X86_CR4_PCIDE);

		/* A 32-bit code segment is required to clear EFER.LMA.  */
		स_रखो(&cs_desc, 0, माप(cs_desc));
		cs_desc.type = 0xb;
		cs_desc.s = cs_desc.g = cs_desc.p = 1;
		ctxt->ops->set_segment(ctxt, 0, &cs_desc, 0, VCPU_SREG_CS);
	पूर्ण

	/* For the 64-bit हाल, this will clear EFER.LMA.  */
	cr0 = ctxt->ops->get_cr(ctxt, 0);
	अगर (cr0 & X86_CR0_PE)
		ctxt->ops->set_cr(ctxt, 0, cr0 & ~(X86_CR0_PG | X86_CR0_PE));

	अगर (emulator_has_दीर्घmode(ctxt)) अणु
		/* Clear CR4.PAE beक्रमe clearing EFER.LME. */
		cr4 = ctxt->ops->get_cr(ctxt, 4);
		अगर (cr4 & X86_CR4_PAE)
			ctxt->ops->set_cr(ctxt, 4, cr4 & ~X86_CR4_PAE);

		/* And finally go back to 32-bit mode.  */
		efer = 0;
		ctxt->ops->set_msr(ctxt, MSR_EFER, efer);
	पूर्ण

	/*
	 * Give pre_leave_smm() a chance to make ISA-specअगरic changes to the
	 * vCPU state (e.g. enter guest mode) beक्रमe loading state from the SMM
	 * state-save area.
	 */
	अगर (ctxt->ops->pre_leave_smm(ctxt, buf))
		वापस X86EMUL_UNHANDLEABLE;

#अगर_घोषित CONFIG_X86_64
	अगर (emulator_has_दीर्घmode(ctxt))
		ret = rsm_load_state_64(ctxt, buf);
	अन्यथा
#पूर्ण_अगर
		ret = rsm_load_state_32(ctxt, buf);

	अगर (ret != X86EMUL_CONTINUE) अणु
		/* FIXME: should triple fault */
		वापस X86EMUL_UNHANDLEABLE;
	पूर्ण

	ctxt->ops->post_leave_smm(ctxt);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल व्योम
setup_syscalls_segments(काष्ठा x86_emulate_ctxt *ctxt,
			काष्ठा desc_काष्ठा *cs, काष्ठा desc_काष्ठा *ss)
अणु
	cs->l = 0;		/* will be adjusted later */
	set_desc_base(cs, 0);	/* flat segment */
	cs->g = 1;		/* 4kb granularity */
	set_desc_limit(cs, 0xfffff);	/* 4GB limit */
	cs->type = 0x0b;	/* Read, Execute, Accessed */
	cs->s = 1;
	cs->dpl = 0;		/* will be adjusted later */
	cs->p = 1;
	cs->d = 1;
	cs->avl = 0;

	set_desc_base(ss, 0);	/* flat segment */
	set_desc_limit(ss, 0xfffff);	/* 4GB limit */
	ss->g = 1;		/* 4kb granularity */
	ss->s = 1;
	ss->type = 0x03;	/* Read/Write, Accessed */
	ss->d = 1;		/* 32bit stack segment */
	ss->dpl = 0;
	ss->p = 1;
	ss->l = 0;
	ss->avl = 0;
पूर्ण

अटल bool venकरोr_पूर्णांकel(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u32 eax, ebx, ecx, edx;

	eax = ecx = 0;
	ctxt->ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx, true);
	वापस is_guest_venकरोr_पूर्णांकel(ebx, ecx, edx);
पूर्ण

अटल bool em_syscall_is_enabled(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	u32 eax, ebx, ecx, edx;

	/*
	 * syscall should always be enabled in दीर्घmode - so only become
	 * venकरोr specअगरic (cpuid) अगर other modes are active...
	 */
	अगर (ctxt->mode == X86EMUL_MODE_PROT64)
		वापस true;

	eax = 0x00000000;
	ecx = 0x00000000;
	ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx, true);
	/*
	 * remark: Intel CPUs only support "syscall" in 64bit दीर्घmode. Also a
	 * 64bit guest with a 32bit compat-app running will #UD !! While this
	 * behaviour can be fixed (by emulating) पूर्णांकo AMD response - CPUs of
	 * AMD can't behave like Intel.
	 */
	अगर (is_guest_venकरोr_पूर्णांकel(ebx, ecx, edx))
		वापस false;

	अगर (is_guest_venकरोr_amd(ebx, ecx, edx) ||
	    is_guest_venकरोr_hygon(ebx, ecx, edx))
		वापस true;

	/*
	 * शेष: (not Intel, not AMD, not Hygon), apply Intel's
	 * stricter rules...
	 */
	वापस false;
पूर्ण

अटल पूर्णांक em_syscall(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	काष्ठा desc_काष्ठा cs, ss;
	u64 msr_data;
	u16 cs_sel, ss_sel;
	u64 efer = 0;

	/* syscall is not available in real mode */
	अगर (ctxt->mode == X86EMUL_MODE_REAL ||
	    ctxt->mode == X86EMUL_MODE_VM86)
		वापस emulate_ud(ctxt);

	अगर (!(em_syscall_is_enabled(ctxt)))
		वापस emulate_ud(ctxt);

	ops->get_msr(ctxt, MSR_EFER, &efer);
	अगर (!(efer & EFER_SCE))
		वापस emulate_ud(ctxt);

	setup_syscalls_segments(ctxt, &cs, &ss);
	ops->get_msr(ctxt, MSR_STAR, &msr_data);
	msr_data >>= 32;
	cs_sel = (u16)(msr_data & 0xfffc);
	ss_sel = (u16)(msr_data + 8);

	अगर (efer & EFER_LMA) अणु
		cs.d = 0;
		cs.l = 1;
	पूर्ण
	ops->set_segment(ctxt, cs_sel, &cs, 0, VCPU_SREG_CS);
	ops->set_segment(ctxt, ss_sel, &ss, 0, VCPU_SREG_SS);

	*reg_ग_लिखो(ctxt, VCPU_REGS_RCX) = ctxt->_eip;
	अगर (efer & EFER_LMA) अणु
#अगर_घोषित CONFIG_X86_64
		*reg_ग_लिखो(ctxt, VCPU_REGS_R11) = ctxt->eflags;

		ops->get_msr(ctxt,
			     ctxt->mode == X86EMUL_MODE_PROT64 ?
			     MSR_LSTAR : MSR_CSTAR, &msr_data);
		ctxt->_eip = msr_data;

		ops->get_msr(ctxt, MSR_SYSCALL_MASK, &msr_data);
		ctxt->eflags &= ~msr_data;
		ctxt->eflags |= X86_EFLAGS_FIXED;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* legacy mode */
		ops->get_msr(ctxt, MSR_STAR, &msr_data);
		ctxt->_eip = (u32)msr_data;

		ctxt->eflags &= ~(X86_EFLAGS_VM | X86_EFLAGS_IF);
	पूर्ण

	ctxt->tf = (ctxt->eflags & X86_EFLAGS_TF) != 0;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_sysenter(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	काष्ठा desc_काष्ठा cs, ss;
	u64 msr_data;
	u16 cs_sel, ss_sel;
	u64 efer = 0;

	ops->get_msr(ctxt, MSR_EFER, &efer);
	/* inject #GP अगर in real mode */
	अगर (ctxt->mode == X86EMUL_MODE_REAL)
		वापस emulate_gp(ctxt, 0);

	/*
	 * Not recognized on AMD in compat mode (but is recognized in legacy
	 * mode).
	 */
	अगर ((ctxt->mode != X86EMUL_MODE_PROT64) && (efer & EFER_LMA)
	    && !venकरोr_पूर्णांकel(ctxt))
		वापस emulate_ud(ctxt);

	/* sysenter/sysनिकास have not been tested in 64bit mode. */
	अगर (ctxt->mode == X86EMUL_MODE_PROT64)
		वापस X86EMUL_UNHANDLEABLE;

	ops->get_msr(ctxt, MSR_IA32_SYSENTER_CS, &msr_data);
	अगर ((msr_data & 0xfffc) == 0x0)
		वापस emulate_gp(ctxt, 0);

	setup_syscalls_segments(ctxt, &cs, &ss);
	ctxt->eflags &= ~(X86_EFLAGS_VM | X86_EFLAGS_IF);
	cs_sel = (u16)msr_data & ~SEGMENT_RPL_MASK;
	ss_sel = cs_sel + 8;
	अगर (efer & EFER_LMA) अणु
		cs.d = 0;
		cs.l = 1;
	पूर्ण

	ops->set_segment(ctxt, cs_sel, &cs, 0, VCPU_SREG_CS);
	ops->set_segment(ctxt, ss_sel, &ss, 0, VCPU_SREG_SS);

	ops->get_msr(ctxt, MSR_IA32_SYSENTER_EIP, &msr_data);
	ctxt->_eip = (efer & EFER_LMA) ? msr_data : (u32)msr_data;

	ops->get_msr(ctxt, MSR_IA32_SYSENTER_ESP, &msr_data);
	*reg_ग_लिखो(ctxt, VCPU_REGS_RSP) = (efer & EFER_LMA) ? msr_data :
							      (u32)msr_data;
	अगर (efer & EFER_LMA)
		ctxt->mode = X86EMUL_MODE_PROT64;

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_sysनिकास(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	काष्ठा desc_काष्ठा cs, ss;
	u64 msr_data, rcx, rdx;
	पूर्णांक usermode;
	u16 cs_sel = 0, ss_sel = 0;

	/* inject #GP अगर in real mode or Virtual 8086 mode */
	अगर (ctxt->mode == X86EMUL_MODE_REAL ||
	    ctxt->mode == X86EMUL_MODE_VM86)
		वापस emulate_gp(ctxt, 0);

	setup_syscalls_segments(ctxt, &cs, &ss);

	अगर ((ctxt->rex_prefix & 0x8) != 0x0)
		usermode = X86EMUL_MODE_PROT64;
	अन्यथा
		usermode = X86EMUL_MODE_PROT32;

	rcx = reg_पढ़ो(ctxt, VCPU_REGS_RCX);
	rdx = reg_पढ़ो(ctxt, VCPU_REGS_RDX);

	cs.dpl = 3;
	ss.dpl = 3;
	ops->get_msr(ctxt, MSR_IA32_SYSENTER_CS, &msr_data);
	चयन (usermode) अणु
	हाल X86EMUL_MODE_PROT32:
		cs_sel = (u16)(msr_data + 16);
		अगर ((msr_data & 0xfffc) == 0x0)
			वापस emulate_gp(ctxt, 0);
		ss_sel = (u16)(msr_data + 24);
		rcx = (u32)rcx;
		rdx = (u32)rdx;
		अवरोध;
	हाल X86EMUL_MODE_PROT64:
		cs_sel = (u16)(msr_data + 32);
		अगर (msr_data == 0x0)
			वापस emulate_gp(ctxt, 0);
		ss_sel = cs_sel + 8;
		cs.d = 0;
		cs.l = 1;
		अगर (emul_is_noncanonical_address(rcx, ctxt) ||
		    emul_is_noncanonical_address(rdx, ctxt))
			वापस emulate_gp(ctxt, 0);
		अवरोध;
	पूर्ण
	cs_sel |= SEGMENT_RPL_MASK;
	ss_sel |= SEGMENT_RPL_MASK;

	ops->set_segment(ctxt, cs_sel, &cs, 0, VCPU_SREG_CS);
	ops->set_segment(ctxt, ss_sel, &ss, 0, VCPU_SREG_SS);

	ctxt->_eip = rdx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RSP) = rcx;

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल bool emulator_bad_iopl(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक iopl;
	अगर (ctxt->mode == X86EMUL_MODE_REAL)
		वापस false;
	अगर (ctxt->mode == X86EMUL_MODE_VM86)
		वापस true;
	iopl = (ctxt->eflags & X86_EFLAGS_IOPL) >> X86_EFLAGS_IOPL_BIT;
	वापस ctxt->ops->cpl(ctxt) > iopl;
पूर्ण

#घोषणा VMWARE_PORT_VMPORT	(0x5658)
#घोषणा VMWARE_PORT_VMRPC	(0x5659)

अटल bool emulator_io_port_access_allowed(काष्ठा x86_emulate_ctxt *ctxt,
					    u16 port, u16 len)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	काष्ठा desc_काष्ठा tr_seg;
	u32 base3;
	पूर्णांक r;
	u16 tr, io_biपंचांगap_ptr, perm, bit_idx = port & 0x7;
	अचिन्हित mask = (1 << len) - 1;
	अचिन्हित दीर्घ base;

	/*
	 * VMware allows access to these ports even अगर denied
	 * by TSS I/O permission biपंचांगap. Mimic behavior.
	 */
	अगर (enable_vmware_backकरोor &&
	    ((port == VMWARE_PORT_VMPORT) || (port == VMWARE_PORT_VMRPC)))
		वापस true;

	ops->get_segment(ctxt, &tr, &tr_seg, &base3, VCPU_SREG_TR);
	अगर (!tr_seg.p)
		वापस false;
	अगर (desc_limit_scaled(&tr_seg) < 103)
		वापस false;
	base = get_desc_base(&tr_seg);
#अगर_घोषित CONFIG_X86_64
	base |= ((u64)base3) << 32;
#पूर्ण_अगर
	r = ops->पढ़ो_std(ctxt, base + 102, &io_biपंचांगap_ptr, 2, शून्य, true);
	अगर (r != X86EMUL_CONTINUE)
		वापस false;
	अगर (io_biपंचांगap_ptr + port/8 > desc_limit_scaled(&tr_seg))
		वापस false;
	r = ops->पढ़ो_std(ctxt, base + io_biपंचांगap_ptr + port/8, &perm, 2, शून्य, true);
	अगर (r != X86EMUL_CONTINUE)
		वापस false;
	अगर ((perm >> bit_idx) & mask)
		वापस false;
	वापस true;
पूर्ण

अटल bool emulator_io_permited(काष्ठा x86_emulate_ctxt *ctxt,
				 u16 port, u16 len)
अणु
	अगर (ctxt->perm_ok)
		वापस true;

	अगर (emulator_bad_iopl(ctxt))
		अगर (!emulator_io_port_access_allowed(ctxt, port, len))
			वापस false;

	ctxt->perm_ok = true;

	वापस true;
पूर्ण

अटल व्योम string_रेजिस्टरs_quirk(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/*
	 * Intel CPUs mask the counter and poपूर्णांकers in quite strange
	 * manner when ECX is zero due to REP-string optimizations.
	 */
#अगर_घोषित CONFIG_X86_64
	अगर (ctxt->ad_bytes != 4 || !venकरोr_पूर्णांकel(ctxt))
		वापस;

	*reg_ग_लिखो(ctxt, VCPU_REGS_RCX) = 0;

	चयन (ctxt->b) अणु
	हाल 0xa4:	/* movsb */
	हाल 0xa5:	/* movsd/w */
		*reg_rmw(ctxt, VCPU_REGS_RSI) &= (u32)-1;
		fallthrough;
	हाल 0xaa:	/* stosb */
	हाल 0xab:	/* stosd/w */
		*reg_rmw(ctxt, VCPU_REGS_RDI) &= (u32)-1;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम save_state_to_tss16(काष्ठा x86_emulate_ctxt *ctxt,
				काष्ठा tss_segment_16 *tss)
अणु
	tss->ip = ctxt->_eip;
	tss->flag = ctxt->eflags;
	tss->ax = reg_पढ़ो(ctxt, VCPU_REGS_RAX);
	tss->cx = reg_पढ़ो(ctxt, VCPU_REGS_RCX);
	tss->dx = reg_पढ़ो(ctxt, VCPU_REGS_RDX);
	tss->bx = reg_पढ़ो(ctxt, VCPU_REGS_RBX);
	tss->sp = reg_पढ़ो(ctxt, VCPU_REGS_RSP);
	tss->bp = reg_पढ़ो(ctxt, VCPU_REGS_RBP);
	tss->si = reg_पढ़ो(ctxt, VCPU_REGS_RSI);
	tss->di = reg_पढ़ो(ctxt, VCPU_REGS_RDI);

	tss->es = get_segment_selector(ctxt, VCPU_SREG_ES);
	tss->cs = get_segment_selector(ctxt, VCPU_SREG_CS);
	tss->ss = get_segment_selector(ctxt, VCPU_SREG_SS);
	tss->ds = get_segment_selector(ctxt, VCPU_SREG_DS);
	tss->ldt = get_segment_selector(ctxt, VCPU_SREG_LDTR);
पूर्ण

अटल पूर्णांक load_state_from_tss16(काष्ठा x86_emulate_ctxt *ctxt,
				 काष्ठा tss_segment_16 *tss)
अणु
	पूर्णांक ret;
	u8 cpl;

	ctxt->_eip = tss->ip;
	ctxt->eflags = tss->flag | 2;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RAX) = tss->ax;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RCX) = tss->cx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RDX) = tss->dx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RBX) = tss->bx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RSP) = tss->sp;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RBP) = tss->bp;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RSI) = tss->si;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RDI) = tss->di;

	/*
	 * SDM says that segment selectors are loaded beक्रमe segment
	 * descriptors
	 */
	set_segment_selector(ctxt, tss->ldt, VCPU_SREG_LDTR);
	set_segment_selector(ctxt, tss->es, VCPU_SREG_ES);
	set_segment_selector(ctxt, tss->cs, VCPU_SREG_CS);
	set_segment_selector(ctxt, tss->ss, VCPU_SREG_SS);
	set_segment_selector(ctxt, tss->ds, VCPU_SREG_DS);

	cpl = tss->cs & 3;

	/*
	 * Now load segment descriptors. If fault happens at this stage
	 * it is handled in a context of new task
	 */
	ret = __load_segment_descriptor(ctxt, tss->ldt, VCPU_SREG_LDTR, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->es, VCPU_SREG_ES, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->cs, VCPU_SREG_CS, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->ss, VCPU_SREG_SS, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->ds, VCPU_SREG_DS, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक task_चयन_16(काष्ठा x86_emulate_ctxt *ctxt,
			  u16 tss_selector, u16 old_tss_sel,
			  uदीर्घ old_tss_base, काष्ठा desc_काष्ठा *new_desc)
अणु
	काष्ठा tss_segment_16 tss_seg;
	पूर्णांक ret;
	u32 new_tss_base = get_desc_base(new_desc);

	ret = linear_पढ़ो_प्रणाली(ctxt, old_tss_base, &tss_seg, माप(tss_seg));
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	save_state_to_tss16(ctxt, &tss_seg);

	ret = linear_ग_लिखो_प्रणाली(ctxt, old_tss_base, &tss_seg, माप(tss_seg));
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	ret = linear_पढ़ो_प्रणाली(ctxt, new_tss_base, &tss_seg, माप(tss_seg));
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	अगर (old_tss_sel != 0xffff) अणु
		tss_seg.prev_task_link = old_tss_sel;

		ret = linear_ग_लिखो_प्रणाली(ctxt, new_tss_base,
					  &tss_seg.prev_task_link,
					  माप(tss_seg.prev_task_link));
		अगर (ret != X86EMUL_CONTINUE)
			वापस ret;
	पूर्ण

	वापस load_state_from_tss16(ctxt, &tss_seg);
पूर्ण

अटल व्योम save_state_to_tss32(काष्ठा x86_emulate_ctxt *ctxt,
				काष्ठा tss_segment_32 *tss)
अणु
	/* CR3 and ldt selector are not saved पूर्णांकentionally */
	tss->eip = ctxt->_eip;
	tss->eflags = ctxt->eflags;
	tss->eax = reg_पढ़ो(ctxt, VCPU_REGS_RAX);
	tss->ecx = reg_पढ़ो(ctxt, VCPU_REGS_RCX);
	tss->edx = reg_पढ़ो(ctxt, VCPU_REGS_RDX);
	tss->ebx = reg_पढ़ो(ctxt, VCPU_REGS_RBX);
	tss->esp = reg_पढ़ो(ctxt, VCPU_REGS_RSP);
	tss->ebp = reg_पढ़ो(ctxt, VCPU_REGS_RBP);
	tss->esi = reg_पढ़ो(ctxt, VCPU_REGS_RSI);
	tss->edi = reg_पढ़ो(ctxt, VCPU_REGS_RDI);

	tss->es = get_segment_selector(ctxt, VCPU_SREG_ES);
	tss->cs = get_segment_selector(ctxt, VCPU_SREG_CS);
	tss->ss = get_segment_selector(ctxt, VCPU_SREG_SS);
	tss->ds = get_segment_selector(ctxt, VCPU_SREG_DS);
	tss->fs = get_segment_selector(ctxt, VCPU_SREG_FS);
	tss->gs = get_segment_selector(ctxt, VCPU_SREG_GS);
पूर्ण

अटल पूर्णांक load_state_from_tss32(काष्ठा x86_emulate_ctxt *ctxt,
				 काष्ठा tss_segment_32 *tss)
अणु
	पूर्णांक ret;
	u8 cpl;

	अगर (ctxt->ops->set_cr(ctxt, 3, tss->cr3))
		वापस emulate_gp(ctxt, 0);
	ctxt->_eip = tss->eip;
	ctxt->eflags = tss->eflags | 2;

	/* General purpose रेजिस्टरs */
	*reg_ग_लिखो(ctxt, VCPU_REGS_RAX) = tss->eax;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RCX) = tss->ecx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RDX) = tss->edx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RBX) = tss->ebx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RSP) = tss->esp;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RBP) = tss->ebp;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RSI) = tss->esi;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RDI) = tss->edi;

	/*
	 * SDM says that segment selectors are loaded beक्रमe segment
	 * descriptors.  This is important because CPL checks will
	 * use CS.RPL.
	 */
	set_segment_selector(ctxt, tss->ldt_selector, VCPU_SREG_LDTR);
	set_segment_selector(ctxt, tss->es, VCPU_SREG_ES);
	set_segment_selector(ctxt, tss->cs, VCPU_SREG_CS);
	set_segment_selector(ctxt, tss->ss, VCPU_SREG_SS);
	set_segment_selector(ctxt, tss->ds, VCPU_SREG_DS);
	set_segment_selector(ctxt, tss->fs, VCPU_SREG_FS);
	set_segment_selector(ctxt, tss->gs, VCPU_SREG_GS);

	/*
	 * If we're चयनing between Protected Mode and VM86, we need to make
	 * sure to update the mode beक्रमe loading the segment descriptors so
	 * that the selectors are पूर्णांकerpreted correctly.
	 */
	अगर (ctxt->eflags & X86_EFLAGS_VM) अणु
		ctxt->mode = X86EMUL_MODE_VM86;
		cpl = 3;
	पूर्ण अन्यथा अणु
		ctxt->mode = X86EMUL_MODE_PROT32;
		cpl = tss->cs & 3;
	पूर्ण

	/*
	 * Now load segment descriptors. If fault happens at this stage
	 * it is handled in a context of new task
	 */
	ret = __load_segment_descriptor(ctxt, tss->ldt_selector, VCPU_SREG_LDTR,
					cpl, X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->es, VCPU_SREG_ES, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->cs, VCPU_SREG_CS, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->ss, VCPU_SREG_SS, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->ds, VCPU_SREG_DS, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->fs, VCPU_SREG_FS, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = __load_segment_descriptor(ctxt, tss->gs, VCPU_SREG_GS, cpl,
					X86_TRANSFER_TASK_SWITCH, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक task_चयन_32(काष्ठा x86_emulate_ctxt *ctxt,
			  u16 tss_selector, u16 old_tss_sel,
			  uदीर्घ old_tss_base, काष्ठा desc_काष्ठा *new_desc)
अणु
	काष्ठा tss_segment_32 tss_seg;
	पूर्णांक ret;
	u32 new_tss_base = get_desc_base(new_desc);
	u32 eip_offset = दुरत्व(काष्ठा tss_segment_32, eip);
	u32 ldt_sel_offset = दुरत्व(काष्ठा tss_segment_32, ldt_selector);

	ret = linear_पढ़ो_प्रणाली(ctxt, old_tss_base, &tss_seg, माप(tss_seg));
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	save_state_to_tss32(ctxt, &tss_seg);

	/* Only GP रेजिस्टरs and segment selectors are saved */
	ret = linear_ग_लिखो_प्रणाली(ctxt, old_tss_base + eip_offset, &tss_seg.eip,
				  ldt_sel_offset - eip_offset);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	ret = linear_पढ़ो_प्रणाली(ctxt, new_tss_base, &tss_seg, माप(tss_seg));
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	अगर (old_tss_sel != 0xffff) अणु
		tss_seg.prev_task_link = old_tss_sel;

		ret = linear_ग_लिखो_प्रणाली(ctxt, new_tss_base,
					  &tss_seg.prev_task_link,
					  माप(tss_seg.prev_task_link));
		अगर (ret != X86EMUL_CONTINUE)
			वापस ret;
	पूर्ण

	वापस load_state_from_tss32(ctxt, &tss_seg);
पूर्ण

अटल पूर्णांक emulator_करो_task_चयन(काष्ठा x86_emulate_ctxt *ctxt,
				   u16 tss_selector, पूर्णांक idt_index, पूर्णांक reason,
				   bool has_error_code, u32 error_code)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	काष्ठा desc_काष्ठा curr_tss_desc, next_tss_desc;
	पूर्णांक ret;
	u16 old_tss_sel = get_segment_selector(ctxt, VCPU_SREG_TR);
	uदीर्घ old_tss_base =
		ops->get_cached_segment_base(ctxt, VCPU_SREG_TR);
	u32 desc_limit;
	uदीर्घ desc_addr, dr7;

	/* FIXME: old_tss_base == ~0 ? */

	ret = पढ़ो_segment_descriptor(ctxt, tss_selector, &next_tss_desc, &desc_addr);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;
	ret = पढ़ो_segment_descriptor(ctxt, old_tss_sel, &curr_tss_desc, &desc_addr);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	/* FIXME: check that next_tss_desc is tss */

	/*
	 * Check privileges. The three हालs are task चयन caused by...
	 *
	 * 1. jmp/call/पूर्णांक to task gate: Check against DPL of the task gate
	 * 2. Exception/IRQ/iret: No check is perक्रमmed
	 * 3. jmp/call to TSS/task-gate: No check is perक्रमmed since the
	 *    hardware checks it beक्रमe निकासing.
	 */
	अगर (reason == TASK_SWITCH_GATE) अणु
		अगर (idt_index != -1) अणु
			/* Software पूर्णांकerrupts */
			काष्ठा desc_काष्ठा task_gate_desc;
			पूर्णांक dpl;

			ret = पढ़ो_पूर्णांकerrupt_descriptor(ctxt, idt_index,
							&task_gate_desc);
			अगर (ret != X86EMUL_CONTINUE)
				वापस ret;

			dpl = task_gate_desc.dpl;
			अगर ((tss_selector & 3) > dpl || ops->cpl(ctxt) > dpl)
				वापस emulate_gp(ctxt, (idt_index << 3) | 0x2);
		पूर्ण
	पूर्ण

	desc_limit = desc_limit_scaled(&next_tss_desc);
	अगर (!next_tss_desc.p ||
	    ((desc_limit < 0x67 && (next_tss_desc.type & 8)) ||
	     desc_limit < 0x2b)) अणु
		वापस emulate_ts(ctxt, tss_selector & 0xfffc);
	पूर्ण

	अगर (reason == TASK_SWITCH_IRET || reason == TASK_SWITCH_JMP) अणु
		curr_tss_desc.type &= ~(1 << 1); /* clear busy flag */
		ग_लिखो_segment_descriptor(ctxt, old_tss_sel, &curr_tss_desc);
	पूर्ण

	अगर (reason == TASK_SWITCH_IRET)
		ctxt->eflags = ctxt->eflags & ~X86_EFLAGS_NT;

	/* set back link to prev task only अगर NT bit is set in eflags
	   note that old_tss_sel is not used after this poपूर्णांक */
	अगर (reason != TASK_SWITCH_CALL && reason != TASK_SWITCH_GATE)
		old_tss_sel = 0xffff;

	अगर (next_tss_desc.type & 8)
		ret = task_चयन_32(ctxt, tss_selector, old_tss_sel,
				     old_tss_base, &next_tss_desc);
	अन्यथा
		ret = task_चयन_16(ctxt, tss_selector, old_tss_sel,
				     old_tss_base, &next_tss_desc);
	अगर (ret != X86EMUL_CONTINUE)
		वापस ret;

	अगर (reason == TASK_SWITCH_CALL || reason == TASK_SWITCH_GATE)
		ctxt->eflags = ctxt->eflags | X86_EFLAGS_NT;

	अगर (reason != TASK_SWITCH_IRET) अणु
		next_tss_desc.type |= (1 << 1); /* set busy flag */
		ग_लिखो_segment_descriptor(ctxt, tss_selector, &next_tss_desc);
	पूर्ण

	ops->set_cr(ctxt, 0,  ops->get_cr(ctxt, 0) | X86_CR0_TS);
	ops->set_segment(ctxt, tss_selector, &next_tss_desc, 0, VCPU_SREG_TR);

	अगर (has_error_code) अणु
		ctxt->op_bytes = ctxt->ad_bytes = (next_tss_desc.type & 8) ? 4 : 2;
		ctxt->lock_prefix = 0;
		ctxt->src.val = (अचिन्हित दीर्घ) error_code;
		ret = em_push(ctxt);
	पूर्ण

	ops->get_dr(ctxt, 7, &dr7);
	ops->set_dr(ctxt, 7, dr7 & ~(DR_LOCAL_ENABLE_MASK | DR_LOCAL_SLOWDOWN));

	वापस ret;
पूर्ण

पूर्णांक emulator_task_चयन(काष्ठा x86_emulate_ctxt *ctxt,
			 u16 tss_selector, पूर्णांक idt_index, पूर्णांक reason,
			 bool has_error_code, u32 error_code)
अणु
	पूर्णांक rc;

	invalidate_रेजिस्टरs(ctxt);
	ctxt->_eip = ctxt->eip;
	ctxt->dst.type = OP_NONE;

	rc = emulator_करो_task_चयन(ctxt, tss_selector, idt_index, reason,
				     has_error_code, error_code);

	अगर (rc == X86EMUL_CONTINUE) अणु
		ctxt->eip = ctxt->_eip;
		ग_लिखोback_रेजिस्टरs(ctxt);
	पूर्ण

	वापस (rc == X86EMUL_UNHANDLEABLE) ? EMULATION_FAILED : EMULATION_OK;
पूर्ण

अटल व्योम string_addr_inc(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक reg,
		काष्ठा opeअक्रम *op)
अणु
	पूर्णांक df = (ctxt->eflags & X86_EFLAGS_DF) ? -op->count : op->count;

	रेजिस्टर_address_increment(ctxt, reg, df * op->bytes);
	op->addr.mem.ea = रेजिस्टर_address(ctxt, reg);
पूर्ण

अटल पूर्णांक em_das(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u8 al, old_al;
	bool af, cf, old_cf;

	cf = ctxt->eflags & X86_EFLAGS_CF;
	al = ctxt->dst.val;

	old_al = al;
	old_cf = cf;
	cf = false;
	af = ctxt->eflags & X86_EFLAGS_AF;
	अगर ((al & 0x0f) > 9 || af) अणु
		al -= 6;
		cf = old_cf | (al >= 250);
		af = true;
	पूर्ण अन्यथा अणु
		af = false;
	पूर्ण
	अगर (old_al > 0x99 || old_cf) अणु
		al -= 0x60;
		cf = true;
	पूर्ण

	ctxt->dst.val = al;
	/* Set PF, ZF, SF */
	ctxt->src.type = OP_IMM;
	ctxt->src.val = 0;
	ctxt->src.bytes = 1;
	fastop(ctxt, em_or);
	ctxt->eflags &= ~(X86_EFLAGS_AF | X86_EFLAGS_CF);
	अगर (cf)
		ctxt->eflags |= X86_EFLAGS_CF;
	अगर (af)
		ctxt->eflags |= X86_EFLAGS_AF;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_aam(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u8 al, ah;

	अगर (ctxt->src.val == 0)
		वापस emulate_de(ctxt);

	al = ctxt->dst.val & 0xff;
	ah = al / ctxt->src.val;
	al %= ctxt->src.val;

	ctxt->dst.val = (ctxt->dst.val & 0xffff0000) | al | (ah << 8);

	/* Set PF, ZF, SF */
	ctxt->src.type = OP_IMM;
	ctxt->src.val = 0;
	ctxt->src.bytes = 1;
	fastop(ctxt, em_or);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_aad(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u8 al = ctxt->dst.val & 0xff;
	u8 ah = (ctxt->dst.val >> 8) & 0xff;

	al = (al + (ah * ctxt->src.val)) & 0xff;

	ctxt->dst.val = (ctxt->dst.val & 0xffff0000) | al;

	/* Set PF, ZF, SF */
	ctxt->src.type = OP_IMM;
	ctxt->src.val = 0;
	ctxt->src.bytes = 1;
	fastop(ctxt, em_or);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_call(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;
	दीर्घ rel = ctxt->src.val;

	ctxt->src.val = (अचिन्हित दीर्घ)ctxt->_eip;
	rc = jmp_rel(ctxt, rel);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	वापस em_push(ctxt);
पूर्ण

अटल पूर्णांक em_call_far(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u16 sel, old_cs;
	uदीर्घ old_eip;
	पूर्णांक rc;
	काष्ठा desc_काष्ठा old_desc, new_desc;
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	पूर्णांक cpl = ctxt->ops->cpl(ctxt);
	क्रमागत x86emul_mode prev_mode = ctxt->mode;

	old_eip = ctxt->_eip;
	ops->get_segment(ctxt, &old_cs, &old_desc, शून्य, VCPU_SREG_CS);

	स_नकल(&sel, ctxt->src.valptr + ctxt->op_bytes, 2);
	rc = __load_segment_descriptor(ctxt, sel, VCPU_SREG_CS, cpl,
				       X86_TRANSFER_CALL_JMP, &new_desc);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	rc = assign_eip_far(ctxt, ctxt->src.val, &new_desc);
	अगर (rc != X86EMUL_CONTINUE)
		जाओ fail;

	ctxt->src.val = old_cs;
	rc = em_push(ctxt);
	अगर (rc != X86EMUL_CONTINUE)
		जाओ fail;

	ctxt->src.val = old_eip;
	rc = em_push(ctxt);
	/* If we failed, we taपूर्णांकed the memory, but the very least we should
	   restore cs */
	अगर (rc != X86EMUL_CONTINUE) अणु
		pr_warn_once("faulting far call emulation tainted memory\n");
		जाओ fail;
	पूर्ण
	वापस rc;
fail:
	ops->set_segment(ctxt, old_cs, &old_desc, 0, VCPU_SREG_CS);
	ctxt->mode = prev_mode;
	वापस rc;

पूर्ण

अटल पूर्णांक em_ret_near_imm(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ eip;

	rc = emulate_pop(ctxt, &eip, ctxt->op_bytes);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	rc = assign_eip_near(ctxt, eip);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	rsp_increment(ctxt, ctxt->src.val);
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_xchg(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/* Write back the रेजिस्टर source. */
	ctxt->src.val = ctxt->dst.val;
	ग_लिखो_रेजिस्टर_opeअक्रम(&ctxt->src);

	/* Write back the memory destination with implicit LOCK prefix. */
	ctxt->dst.val = ctxt->src.orig_val;
	ctxt->lock_prefix = 1;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_imul_3op(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->dst.val = ctxt->src2.val;
	वापस fastop(ctxt, em_imul);
पूर्ण

अटल पूर्णांक em_cwd(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->dst.type = OP_REG;
	ctxt->dst.bytes = ctxt->src.bytes;
	ctxt->dst.addr.reg = reg_rmw(ctxt, VCPU_REGS_RDX);
	ctxt->dst.val = ~((ctxt->src.val >> (ctxt->src.bytes * 8 - 1)) - 1);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_rdpid(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 tsc_aux = 0;

	अगर (ctxt->ops->get_msr(ctxt, MSR_TSC_AUX, &tsc_aux))
		वापस emulate_ud(ctxt);
	ctxt->dst.val = tsc_aux;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_rdtsc(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 tsc = 0;

	ctxt->ops->get_msr(ctxt, MSR_IA32_TSC, &tsc);
	*reg_ग_लिखो(ctxt, VCPU_REGS_RAX) = (u32)tsc;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RDX) = tsc >> 32;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_rdpmc(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 pmc;

	अगर (ctxt->ops->पढ़ो_pmc(ctxt, reg_पढ़ो(ctxt, VCPU_REGS_RCX), &pmc))
		वापस emulate_gp(ctxt, 0);
	*reg_ग_लिखो(ctxt, VCPU_REGS_RAX) = (u32)pmc;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RDX) = pmc >> 32;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_mov(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	स_नकल(ctxt->dst.valptr, ctxt->src.valptr, माप(ctxt->src.valptr));
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_movbe(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u16 पंचांगp;

	अगर (!ctxt->ops->guest_has_movbe(ctxt))
		वापस emulate_ud(ctxt);

	चयन (ctxt->op_bytes) अणु
	हाल 2:
		/*
		 * From MOVBE definition: "...When the opeअक्रम size is 16 bits,
		 * the upper word of the destination रेजिस्टर reमुख्यs unchanged
		 * ..."
		 *
		 * Both casting ->valptr and ->val to u16 अवरोधs strict aliasing
		 * rules so we have to करो the operation almost per hand.
		 */
		पंचांगp = (u16)ctxt->src.val;
		ctxt->dst.val &= ~0xffffUL;
		ctxt->dst.val |= (अचिन्हित दीर्घ)swab16(पंचांगp);
		अवरोध;
	हाल 4:
		ctxt->dst.val = swab32((u32)ctxt->src.val);
		अवरोध;
	हाल 8:
		ctxt->dst.val = swab64(ctxt->src.val);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_cr_ग_लिखो(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (ctxt->ops->set_cr(ctxt, ctxt->modrm_reg, ctxt->src.val))
		वापस emulate_gp(ctxt, 0);

	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_dr_ग_लिखो(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अचिन्हित दीर्घ val;

	अगर (ctxt->mode == X86EMUL_MODE_PROT64)
		val = ctxt->src.val & ~0ULL;
	अन्यथा
		val = ctxt->src.val & ~0U;

	/* #UD condition is alपढ़ोy handled. */
	अगर (ctxt->ops->set_dr(ctxt, ctxt->modrm_reg, val) < 0)
		वापस emulate_gp(ctxt, 0);

	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_wrmsr(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 msr_index = reg_पढ़ो(ctxt, VCPU_REGS_RCX);
	u64 msr_data;
	पूर्णांक r;

	msr_data = (u32)reg_पढ़ो(ctxt, VCPU_REGS_RAX)
		| ((u64)reg_पढ़ो(ctxt, VCPU_REGS_RDX) << 32);
	r = ctxt->ops->set_msr(ctxt, msr_index, msr_data);

	अगर (r == X86EMUL_IO_NEEDED)
		वापस r;

	अगर (r > 0)
		वापस emulate_gp(ctxt, 0);

	वापस r < 0 ? X86EMUL_UNHANDLEABLE : X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_rdmsr(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 msr_index = reg_पढ़ो(ctxt, VCPU_REGS_RCX);
	u64 msr_data;
	पूर्णांक r;

	r = ctxt->ops->get_msr(ctxt, msr_index, &msr_data);

	अगर (r == X86EMUL_IO_NEEDED)
		वापस r;

	अगर (r)
		वापस emulate_gp(ctxt, 0);

	*reg_ग_लिखो(ctxt, VCPU_REGS_RAX) = (u32)msr_data;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RDX) = msr_data >> 32;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_store_sreg(काष्ठा x86_emulate_ctxt *ctxt, पूर्णांक segment)
अणु
	अगर (segment > VCPU_SREG_GS &&
	    (ctxt->ops->get_cr(ctxt, 4) & X86_CR4_UMIP) &&
	    ctxt->ops->cpl(ctxt) > 0)
		वापस emulate_gp(ctxt, 0);

	ctxt->dst.val = get_segment_selector(ctxt, segment);
	अगर (ctxt->dst.bytes == 4 && ctxt->dst.type == OP_MEM)
		ctxt->dst.bytes = 2;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_mov_rm_sreg(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (ctxt->modrm_reg > VCPU_SREG_GS)
		वापस emulate_ud(ctxt);

	वापस em_store_sreg(ctxt, ctxt->modrm_reg);
पूर्ण

अटल पूर्णांक em_mov_sreg_rm(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u16 sel = ctxt->src.val;

	अगर (ctxt->modrm_reg == VCPU_SREG_CS || ctxt->modrm_reg > VCPU_SREG_GS)
		वापस emulate_ud(ctxt);

	अगर (ctxt->modrm_reg == VCPU_SREG_SS)
		ctxt->पूर्णांकerruptibility = KVM_X86_SHADOW_INT_MOV_SS;

	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस load_segment_descriptor(ctxt, sel, ctxt->modrm_reg);
पूर्ण

अटल पूर्णांक em_sldt(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस em_store_sreg(ctxt, VCPU_SREG_LDTR);
पूर्ण

अटल पूर्णांक em_lldt(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u16 sel = ctxt->src.val;

	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस load_segment_descriptor(ctxt, sel, VCPU_SREG_LDTR);
पूर्ण

अटल पूर्णांक em_str(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस em_store_sreg(ctxt, VCPU_SREG_TR);
पूर्ण

अटल पूर्णांक em_ltr(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u16 sel = ctxt->src.val;

	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस load_segment_descriptor(ctxt, sel, VCPU_SREG_TR);
पूर्ण

अटल पूर्णांक em_invlpg(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;
	uदीर्घ linear;

	rc = linearize(ctxt, ctxt->src.addr.mem, 1, false, &linear);
	अगर (rc == X86EMUL_CONTINUE)
		ctxt->ops->invlpg(ctxt, linear);
	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_clts(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	uदीर्घ cr0;

	cr0 = ctxt->ops->get_cr(ctxt, 0);
	cr0 &= ~X86_CR0_TS;
	ctxt->ops->set_cr(ctxt, 0, cr0);
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_hypercall(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc = ctxt->ops->fix_hypercall(ctxt);

	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	/* Let the processor re-execute the fixed hypercall */
	ctxt->_eip = ctxt->eip;
	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक emulate_store_desc_ptr(काष्ठा x86_emulate_ctxt *ctxt,
				  व्योम (*get)(काष्ठा x86_emulate_ctxt *ctxt,
					      काष्ठा desc_ptr *ptr))
अणु
	काष्ठा desc_ptr desc_ptr;

	अगर ((ctxt->ops->get_cr(ctxt, 4) & X86_CR4_UMIP) &&
	    ctxt->ops->cpl(ctxt) > 0)
		वापस emulate_gp(ctxt, 0);

	अगर (ctxt->mode == X86EMUL_MODE_PROT64)
		ctxt->op_bytes = 8;
	get(ctxt, &desc_ptr);
	अगर (ctxt->op_bytes == 2) अणु
		ctxt->op_bytes = 4;
		desc_ptr.address &= 0x00ffffff;
	पूर्ण
	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस segmented_ग_लिखो_std(ctxt, ctxt->dst.addr.mem,
				   &desc_ptr, 2 + ctxt->op_bytes);
पूर्ण

अटल पूर्णांक em_sgdt(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस emulate_store_desc_ptr(ctxt, ctxt->ops->get_gdt);
पूर्ण

अटल पूर्णांक em_sidt(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस emulate_store_desc_ptr(ctxt, ctxt->ops->get_idt);
पूर्ण

अटल पूर्णांक em_lgdt_lidt(काष्ठा x86_emulate_ctxt *ctxt, bool lgdt)
अणु
	काष्ठा desc_ptr desc_ptr;
	पूर्णांक rc;

	अगर (ctxt->mode == X86EMUL_MODE_PROT64)
		ctxt->op_bytes = 8;
	rc = पढ़ो_descriptor(ctxt, ctxt->src.addr.mem,
			     &desc_ptr.size, &desc_ptr.address,
			     ctxt->op_bytes);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;
	अगर (ctxt->mode == X86EMUL_MODE_PROT64 &&
	    emul_is_noncanonical_address(desc_ptr.address, ctxt))
		वापस emulate_gp(ctxt, 0);
	अगर (lgdt)
		ctxt->ops->set_gdt(ctxt, &desc_ptr);
	अन्यथा
		ctxt->ops->set_idt(ctxt, &desc_ptr);
	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_lgdt(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस em_lgdt_lidt(ctxt, true);
पूर्ण

अटल पूर्णांक em_lidt(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस em_lgdt_lidt(ctxt, false);
पूर्ण

अटल पूर्णांक em_smsw(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर ((ctxt->ops->get_cr(ctxt, 4) & X86_CR4_UMIP) &&
	    ctxt->ops->cpl(ctxt) > 0)
		वापस emulate_gp(ctxt, 0);

	अगर (ctxt->dst.type == OP_MEM)
		ctxt->dst.bytes = 2;
	ctxt->dst.val = ctxt->ops->get_cr(ctxt, 0);
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_lmsw(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->ops->set_cr(ctxt, 0, (ctxt->ops->get_cr(ctxt, 0) & ~0x0eul)
			  | (ctxt->src.val & 0x0f));
	ctxt->dst.type = OP_NONE;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_loop(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc = X86EMUL_CONTINUE;

	रेजिस्टर_address_increment(ctxt, VCPU_REGS_RCX, -1);
	अगर ((address_mask(ctxt, reg_पढ़ो(ctxt, VCPU_REGS_RCX)) != 0) &&
	    (ctxt->b == 0xe2 || test_cc(ctxt->b ^ 0x5, ctxt->eflags)))
		rc = jmp_rel(ctxt, ctxt->src.val);

	वापस rc;
पूर्ण

अटल पूर्णांक em_jcxz(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc = X86EMUL_CONTINUE;

	अगर (address_mask(ctxt, reg_पढ़ो(ctxt, VCPU_REGS_RCX)) == 0)
		rc = jmp_rel(ctxt, ctxt->src.val);

	वापस rc;
पूर्ण

अटल पूर्णांक em_in(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (!pio_in_emulated(ctxt, ctxt->dst.bytes, ctxt->src.val,
			     &ctxt->dst.val))
		वापस X86EMUL_IO_NEEDED;

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_out(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->ops->pio_out_emulated(ctxt, ctxt->src.bytes, ctxt->dst.val,
				    &ctxt->src.val, 1);
	/* Disable ग_लिखोback. */
	ctxt->dst.type = OP_NONE;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_cli(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (emulator_bad_iopl(ctxt))
		वापस emulate_gp(ctxt, 0);

	ctxt->eflags &= ~X86_EFLAGS_IF;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_sti(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (emulator_bad_iopl(ctxt))
		वापस emulate_gp(ctxt, 0);

	ctxt->पूर्णांकerruptibility = KVM_X86_SHADOW_INT_STI;
	ctxt->eflags |= X86_EFLAGS_IF;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_cpuid(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u32 eax, ebx, ecx, edx;
	u64 msr = 0;

	ctxt->ops->get_msr(ctxt, MSR_MISC_FEATURES_ENABLES, &msr);
	अगर (msr & MSR_MISC_FEATURES_ENABLES_CPUID_FAULT &&
	    ctxt->ops->cpl(ctxt)) अणु
		वापस emulate_gp(ctxt, 0);
	पूर्ण

	eax = reg_पढ़ो(ctxt, VCPU_REGS_RAX);
	ecx = reg_पढ़ो(ctxt, VCPU_REGS_RCX);
	ctxt->ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx, false);
	*reg_ग_लिखो(ctxt, VCPU_REGS_RAX) = eax;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RBX) = ebx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RCX) = ecx;
	*reg_ग_लिखो(ctxt, VCPU_REGS_RDX) = edx;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_sahf(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u32 flags;

	flags = X86_EFLAGS_CF | X86_EFLAGS_PF | X86_EFLAGS_AF | X86_EFLAGS_ZF |
		X86_EFLAGS_SF;
	flags &= *reg_rmw(ctxt, VCPU_REGS_RAX) >> 8;

	ctxt->eflags &= ~0xffUL;
	ctxt->eflags |= flags | X86_EFLAGS_FIXED;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_lahf(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	*reg_rmw(ctxt, VCPU_REGS_RAX) &= ~0xff00UL;
	*reg_rmw(ctxt, VCPU_REGS_RAX) |= (ctxt->eflags & 0xff) << 8;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_bswap(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	चयन (ctxt->op_bytes) अणु
#अगर_घोषित CONFIG_X86_64
	हाल 8:
		यंत्र("bswap %0" : "+r"(ctxt->dst.val));
		अवरोध;
#पूर्ण_अगर
	शेष:
		यंत्र("bswap %0" : "+r"(*(u32 *)&ctxt->dst.val));
		अवरोध;
	पूर्ण
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_clflush(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/* emulating clflush regardless of cpuid */
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_clflushopt(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/* emulating clflushopt regardless of cpuid */
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक em_movsxd(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->dst.val = (s32) ctxt->src.val;
	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक check_fxsr(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (!ctxt->ops->guest_has_fxsr(ctxt))
		वापस emulate_ud(ctxt);

	अगर (ctxt->ops->get_cr(ctxt, 0) & (X86_CR0_TS | X86_CR0_EM))
		वापस emulate_nm(ctxt);

	/*
	 * Don't emulate a हाल that should never be hit, instead of working
	 * around a lack of fxsave64/fxrstor64 on old compilers.
	 */
	अगर (ctxt->mode >= X86EMUL_MODE_PROT64)
		वापस X86EMUL_UNHANDLEABLE;

	वापस X86EMUL_CONTINUE;
पूर्ण

/*
 * Hardware करोesn't save and restore XMM 0-7 without CR4.OSFXSR, but करोes save
 * and restore MXCSR.
 */
अटल माप_प्रकार __fxstate_size(पूर्णांक nregs)
अणु
	वापस दुरत्व(काष्ठा fxregs_state, xmm_space[0]) + nregs * 16;
पूर्ण

अटल अंतरभूत माप_प्रकार fxstate_size(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	bool cr4_osfxsr;
	अगर (ctxt->mode == X86EMUL_MODE_PROT64)
		वापस __fxstate_size(16);

	cr4_osfxsr = ctxt->ops->get_cr(ctxt, 4) & X86_CR4_OSFXSR;
	वापस __fxstate_size(cr4_osfxsr ? 8 : 0);
पूर्ण

/*
 * FXSAVE and FXRSTOR have 4 dअगरferent क्रमmats depending on execution mode,
 *  1) 16 bit mode
 *  2) 32 bit mode
 *     - like (1), but FIP and FDP (foo) are only 16 bit.  At least Intel CPUs
 *       preserve whole 32 bit values, though, so (1) and (2) are the same wrt.
 *       save and restore
 *  3) 64-bit mode with REX.W prefix
 *     - like (2), but XMM 8-15 are being saved and restored
 *  4) 64-bit mode without REX.W prefix
 *     - like (3), but FIP and FDP are 64 bit
 *
 * Emulation uses (3) क्रम (1) and (2) and preserves XMM 8-15 to reach the
 * desired result.  (4) is not emulated.
 *
 * Note: Guest and host CPUID.(EAX=07H,ECX=0H):EBX[bit 13] (deprecate FPU CS
 * and FPU DS) should match.
 */
अटल पूर्णांक em_fxsave(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	काष्ठा fxregs_state fx_state;
	पूर्णांक rc;

	rc = check_fxsr(ctxt);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	emulator_get_fpu();

	rc = यंत्र_safe("fxsave %[fx]", , [fx] "+m"(fx_state));

	emulator_put_fpu();

	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	वापस segmented_ग_लिखो_std(ctxt, ctxt->memop.addr.mem, &fx_state,
		                   fxstate_size(ctxt));
पूर्ण

/*
 * FXRSTOR might restore XMM रेजिस्टरs not provided by the guest. Fill
 * in the host रेजिस्टरs (via FXSAVE) instead, so they won't be modअगरied.
 * (preemption has to stay disabled until FXRSTOR).
 *
 * Use noअंतरभूत to keep the stack क्रम other functions called by callers small.
 */
अटल noअंतरभूत पूर्णांक fxregs_fixup(काष्ठा fxregs_state *fx_state,
				 स्थिर माप_प्रकार used_size)
अणु
	काष्ठा fxregs_state fx_पंचांगp;
	पूर्णांक rc;

	rc = यंत्र_safe("fxsave %[fx]", , [fx] "+m"(fx_पंचांगp));
	स_नकल((व्योम *)fx_state + used_size, (व्योम *)&fx_पंचांगp + used_size,
	       __fxstate_size(16) - used_size);

	वापस rc;
पूर्ण

अटल पूर्णांक em_fxrstor(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	काष्ठा fxregs_state fx_state;
	पूर्णांक rc;
	माप_प्रकार size;

	rc = check_fxsr(ctxt);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	size = fxstate_size(ctxt);
	rc = segmented_पढ़ो_std(ctxt, ctxt->memop.addr.mem, &fx_state, size);
	अगर (rc != X86EMUL_CONTINUE)
		वापस rc;

	emulator_get_fpu();

	अगर (size < __fxstate_size(16)) अणु
		rc = fxregs_fixup(&fx_state, size);
		अगर (rc != X86EMUL_CONTINUE)
			जाओ out;
	पूर्ण

	अगर (fx_state.mxcsr >> 16) अणु
		rc = emulate_gp(ctxt, 0);
		जाओ out;
	पूर्ण

	अगर (rc == X86EMUL_CONTINUE)
		rc = यंत्र_safe("fxrstor %[fx]", : [fx] "m"(fx_state));

out:
	emulator_put_fpu();

	वापस rc;
पूर्ण

अटल पूर्णांक em_xsetbv(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u32 eax, ecx, edx;

	eax = reg_पढ़ो(ctxt, VCPU_REGS_RAX);
	edx = reg_पढ़ो(ctxt, VCPU_REGS_RDX);
	ecx = reg_पढ़ो(ctxt, VCPU_REGS_RCX);

	अगर (ctxt->ops->set_xcr(ctxt, ecx, ((u64)edx << 32) | eax))
		वापस emulate_gp(ctxt, 0);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल bool valid_cr(पूर्णांक nr)
अणु
	चयन (nr) अणु
	हाल 0:
	हाल 2 ... 4:
	हाल 8:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक check_cr_access(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (!valid_cr(ctxt->modrm_reg))
		वापस emulate_ud(ctxt);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक check_dr7_gd(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अचिन्हित दीर्घ dr7;

	ctxt->ops->get_dr(ctxt, 7, &dr7);

	/* Check अगर DR7.Global_Enable is set */
	वापस dr7 & (1 << 13);
पूर्ण

अटल पूर्णांक check_dr_पढ़ो(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक dr = ctxt->modrm_reg;
	u64 cr4;

	अगर (dr > 7)
		वापस emulate_ud(ctxt);

	cr4 = ctxt->ops->get_cr(ctxt, 4);
	अगर ((cr4 & X86_CR4_DE) && (dr == 4 || dr == 5))
		वापस emulate_ud(ctxt);

	अगर (check_dr7_gd(ctxt)) अणु
		uदीर्घ dr6;

		ctxt->ops->get_dr(ctxt, 6, &dr6);
		dr6 &= ~DR_TRAP_BITS;
		dr6 |= DR6_BD | DR6_ACTIVE_LOW;
		ctxt->ops->set_dr(ctxt, 6, dr6);
		वापस emulate_db(ctxt);
	पूर्ण

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक check_dr_ग_लिखो(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 new_val = ctxt->src.val64;
	पूर्णांक dr = ctxt->modrm_reg;

	अगर ((dr == 6 || dr == 7) && (new_val & 0xffffffff00000000ULL))
		वापस emulate_gp(ctxt, 0);

	वापस check_dr_पढ़ो(ctxt);
पूर्ण

अटल पूर्णांक check_svme(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 efer = 0;

	ctxt->ops->get_msr(ctxt, MSR_EFER, &efer);

	अगर (!(efer & EFER_SVME))
		वापस emulate_ud(ctxt);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक check_svme_pa(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 rax = reg_पढ़ो(ctxt, VCPU_REGS_RAX);

	/* Valid physical address? */
	अगर (rax & 0xffff000000000000ULL)
		वापस emulate_gp(ctxt, 0);

	वापस check_svme(ctxt);
पूर्ण

अटल पूर्णांक check_rdtsc(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 cr4 = ctxt->ops->get_cr(ctxt, 4);

	अगर (cr4 & X86_CR4_TSD && ctxt->ops->cpl(ctxt))
		वापस emulate_ud(ctxt);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक check_rdpmc(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	u64 cr4 = ctxt->ops->get_cr(ctxt, 4);
	u64 rcx = reg_पढ़ो(ctxt, VCPU_REGS_RCX);

	/*
	 * VMware allows access to these Pseduo-PMCs even when पढ़ो via RDPMC
	 * in Ring3 when CR4.PCE=0.
	 */
	अगर (enable_vmware_backकरोor && is_vmware_backकरोor_pmc(rcx))
		वापस X86EMUL_CONTINUE;

	अगर ((!(cr4 & X86_CR4_PCE) && ctxt->ops->cpl(ctxt)) ||
	    ctxt->ops->check_pmc(ctxt, rcx))
		वापस emulate_gp(ctxt, 0);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक check_perm_in(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->dst.bytes = min(ctxt->dst.bytes, 4u);
	अगर (!emulator_io_permited(ctxt, ctxt->src.val, ctxt->dst.bytes))
		वापस emulate_gp(ctxt, 0);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल पूर्णांक check_perm_out(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ctxt->src.bytes = min(ctxt->src.bytes, 4u);
	अगर (!emulator_io_permited(ctxt, ctxt->dst.val, ctxt->src.bytes))
		वापस emulate_gp(ctxt, 0);

	वापस X86EMUL_CONTINUE;
पूर्ण

#घोषणा D(_y) अणु .flags = (_y) पूर्ण
#घोषणा DI(_y, _i) अणु .flags = (_y)|Intercept, .पूर्णांकercept = x86_पूर्णांकercept_##_i पूर्ण
#घोषणा DIP(_y, _i, _p) अणु .flags = (_y)|Intercept|CheckPerm, \
		      .पूर्णांकercept = x86_पूर्णांकercept_##_i, .check_perm = (_p) पूर्ण
#घोषणा N    D(NotImpl)
#घोषणा EXT(_f, _e) अणु .flags = ((_f) | RMExt), .u.group = (_e) पूर्ण
#घोषणा G(_f, _g) अणु .flags = ((_f) | Group | ModRM), .u.group = (_g) पूर्ण
#घोषणा GD(_f, _g) अणु .flags = ((_f) | GroupDual | ModRM), .u.gdual = (_g) पूर्ण
#घोषणा ID(_f, _i) अणु .flags = ((_f) | InstrDual | ModRM), .u.idual = (_i) पूर्ण
#घोषणा MD(_f, _m) अणु .flags = ((_f) | ModeDual), .u.mdual = (_m) पूर्ण
#घोषणा E(_f, _e) अणु .flags = ((_f) | Escape | ModRM), .u.esc = (_e) पूर्ण
#घोषणा I(_f, _e) अणु .flags = (_f), .u.execute = (_e) पूर्ण
#घोषणा F(_f, _e) अणु .flags = (_f) | Fastop, .u.fastop = (_e) पूर्ण
#घोषणा II(_f, _e, _i) \
	अणु .flags = (_f)|Intercept, .u.execute = (_e), .पूर्णांकercept = x86_पूर्णांकercept_##_i पूर्ण
#घोषणा IIP(_f, _e, _i, _p) \
	अणु .flags = (_f)|Intercept|CheckPerm, .u.execute = (_e), \
	  .पूर्णांकercept = x86_पूर्णांकercept_##_i, .check_perm = (_p) पूर्ण
#घोषणा GP(_f, _g) अणु .flags = ((_f) | Prefix), .u.gprefix = (_g) पूर्ण

#घोषणा D2bv(_f)      D((_f) | ByteOp), D(_f)
#घोषणा D2bvIP(_f, _i, _p) DIP((_f) | ByteOp, _i, _p), DIP(_f, _i, _p)
#घोषणा I2bv(_f, _e)  I((_f) | ByteOp, _e), I(_f, _e)
#घोषणा F2bv(_f, _e)  F((_f) | ByteOp, _e), F(_f, _e)
#घोषणा I2bvIP(_f, _e, _i, _p) \
	IIP((_f) | ByteOp, _e, _i, _p), IIP(_f, _e, _i, _p)

#घोषणा F6ALU(_f, _e) F2bv((_f) | DstMem | SrcReg | ModRM, _e),		\
		F2bv(((_f) | DstReg | SrcMem | ModRM) & ~Lock, _e),	\
		F2bv(((_f) & ~Lock) | DstAcc | SrcImm, _e)

अटल स्थिर काष्ठा opcode group7_rm0[] = अणु
	N,
	I(SrcNone | Priv | EmulateOnUD,	em_hypercall),
	N, N, N, N, N, N,
पूर्ण;

अटल स्थिर काष्ठा opcode group7_rm1[] = अणु
	DI(SrcNone | Priv, monitor),
	DI(SrcNone | Priv, mरुको),
	N, N, N, N, N, N,
पूर्ण;

अटल स्थिर काष्ठा opcode group7_rm2[] = अणु
	N,
	II(ImplicitOps | Priv,			em_xsetbv,	xsetbv),
	N, N, N, N, N, N,
पूर्ण;

अटल स्थिर काष्ठा opcode group7_rm3[] = अणु
	DIP(SrcNone | Prot | Priv,		vmrun,		check_svme_pa),
	II(SrcNone  | Prot | EmulateOnUD,	em_hypercall,	vmmcall),
	DIP(SrcNone | Prot | Priv,		vmload,		check_svme_pa),
	DIP(SrcNone | Prot | Priv,		vmsave,		check_svme_pa),
	DIP(SrcNone | Prot | Priv,		stgi,		check_svme),
	DIP(SrcNone | Prot | Priv,		clgi,		check_svme),
	DIP(SrcNone | Prot | Priv,		skinit,		check_svme),
	DIP(SrcNone | Prot | Priv,		invlpga,	check_svme),
पूर्ण;

अटल स्थिर काष्ठा opcode group7_rm7[] = अणु
	N,
	DIP(SrcNone, rdtscp, check_rdtsc),
	N, N, N, N, N, N,
पूर्ण;

अटल स्थिर काष्ठा opcode group1[] = अणु
	F(Lock, em_add),
	F(Lock | PageTable, em_or),
	F(Lock, em_adc),
	F(Lock, em_sbb),
	F(Lock | PageTable, em_and),
	F(Lock, em_sub),
	F(Lock, em_xor),
	F(NoWrite, em_cmp),
पूर्ण;

अटल स्थिर काष्ठा opcode group1A[] = अणु
	I(DstMem | SrcNone | Mov | Stack | IncSP | TwoMemOp, em_pop), N, N, N, N, N, N, N,
पूर्ण;

अटल स्थिर काष्ठा opcode group2[] = अणु
	F(DstMem | ModRM, em_rol),
	F(DstMem | ModRM, em_ror),
	F(DstMem | ModRM, em_rcl),
	F(DstMem | ModRM, em_rcr),
	F(DstMem | ModRM, em_shl),
	F(DstMem | ModRM, em_shr),
	F(DstMem | ModRM, em_shl),
	F(DstMem | ModRM, em_sar),
पूर्ण;

अटल स्थिर काष्ठा opcode group3[] = अणु
	F(DstMem | SrcImm | NoWrite, em_test),
	F(DstMem | SrcImm | NoWrite, em_test),
	F(DstMem | SrcNone | Lock, em_not),
	F(DstMem | SrcNone | Lock, em_neg),
	F(DstXacc | Src2Mem, em_mul_ex),
	F(DstXacc | Src2Mem, em_imul_ex),
	F(DstXacc | Src2Mem, em_भाग_ex),
	F(DstXacc | Src2Mem, em_iभाग_ex),
पूर्ण;

अटल स्थिर काष्ठा opcode group4[] = अणु
	F(ByteOp | DstMem | SrcNone | Lock, em_inc),
	F(ByteOp | DstMem | SrcNone | Lock, em_dec),
	N, N, N, N, N, N,
पूर्ण;

अटल स्थिर काष्ठा opcode group5[] = अणु
	F(DstMem | SrcNone | Lock,		em_inc),
	F(DstMem | SrcNone | Lock,		em_dec),
	I(SrcMem | NearBranch,			em_call_near_असल),
	I(SrcMemFAddr | ImplicitOps,		em_call_far),
	I(SrcMem | NearBranch,			em_jmp_असल),
	I(SrcMemFAddr | ImplicitOps,		em_jmp_far),
	I(SrcMem | Stack | TwoMemOp,		em_push), D(Undefined),
पूर्ण;

अटल स्थिर काष्ठा opcode group6[] = अणु
	II(Prot | DstMem,	   em_sldt, sldt),
	II(Prot | DstMem,	   em_str, str),
	II(Prot | Priv | SrcMem16, em_lldt, lldt),
	II(Prot | Priv | SrcMem16, em_ltr, ltr),
	N, N, N, N,
पूर्ण;

अटल स्थिर काष्ठा group_dual group7 = अणु अणु
	II(Mov | DstMem,			em_sgdt, sgdt),
	II(Mov | DstMem,			em_sidt, sidt),
	II(SrcMem | Priv,			em_lgdt, lgdt),
	II(SrcMem | Priv,			em_lidt, lidt),
	II(SrcNone | DstMem | Mov,		em_smsw, smsw), N,
	II(SrcMem16 | Mov | Priv,		em_lmsw, lmsw),
	II(SrcMem | ByteOp | Priv | NoAccess,	em_invlpg, invlpg),
पूर्ण, अणु
	EXT(0, group7_rm0),
	EXT(0, group7_rm1),
	EXT(0, group7_rm2),
	EXT(0, group7_rm3),
	II(SrcNone | DstMem | Mov,		em_smsw, smsw), N,
	II(SrcMem16 | Mov | Priv,		em_lmsw, lmsw),
	EXT(0, group7_rm7),
पूर्ण पूर्ण;

अटल स्थिर काष्ठा opcode group8[] = अणु
	N, N, N, N,
	F(DstMem | SrcImmByte | NoWrite,		em_bt),
	F(DstMem | SrcImmByte | Lock | PageTable,	em_bts),
	F(DstMem | SrcImmByte | Lock,			em_btr),
	F(DstMem | SrcImmByte | Lock | PageTable,	em_btc),
पूर्ण;

/*
 * The "memory" destination is actually always a रेजिस्टर, since we come
 * from the रेजिस्टर हाल of group9.
 */
अटल स्थिर काष्ठा gprefix pfx_0f_c7_7 = अणु
	N, N, N, II(DstMem | ModRM | Op3264 | EmulateOnUD, em_rdpid, rdpid),
पूर्ण;


अटल स्थिर काष्ठा group_dual group9 = अणु अणु
	N, I(DstMem64 | Lock | PageTable, em_cmpxchg8b), N, N, N, N, N, N,
पूर्ण, अणु
	N, N, N, N, N, N, N,
	GP(0, &pfx_0f_c7_7),
पूर्ण पूर्ण;

अटल स्थिर काष्ठा opcode group11[] = अणु
	I(DstMem | SrcImm | Mov | PageTable, em_mov),
	X7(D(Undefined)),
पूर्ण;

अटल स्थिर काष्ठा gprefix pfx_0f_ae_7 = अणु
	I(SrcMem | ByteOp, em_clflush), I(SrcMem | ByteOp, em_clflushopt), N, N,
पूर्ण;

अटल स्थिर काष्ठा group_dual group15 = अणु अणु
	I(ModRM | Aligned16, em_fxsave),
	I(ModRM | Aligned16, em_fxrstor),
	N, N, N, N, N, GP(0, &pfx_0f_ae_7),
पूर्ण, अणु
	N, N, N, N, N, N, N, N,
पूर्ण पूर्ण;

अटल स्थिर काष्ठा gprefix pfx_0f_6f_0f_7f = अणु
	I(Mmx, em_mov), I(Sse | Aligned, em_mov), N, I(Sse | Unaligned, em_mov),
पूर्ण;

अटल स्थिर काष्ठा instr_dual instr_dual_0f_2b = अणु
	I(0, em_mov), N
पूर्ण;

अटल स्थिर काष्ठा gprefix pfx_0f_2b = अणु
	ID(0, &instr_dual_0f_2b), ID(0, &instr_dual_0f_2b), N, N,
पूर्ण;

अटल स्थिर काष्ठा gprefix pfx_0f_10_0f_11 = अणु
	I(Unaligned, em_mov), I(Unaligned, em_mov), N, N,
पूर्ण;

अटल स्थिर काष्ठा gprefix pfx_0f_28_0f_29 = अणु
	I(Aligned, em_mov), I(Aligned, em_mov), N, N,
पूर्ण;

अटल स्थिर काष्ठा gprefix pfx_0f_e7 = अणु
	N, I(Sse, em_mov), N, N,
पूर्ण;

अटल स्थिर काष्ठा escape escape_d9 = अणु अणु
	N, N, N, N, N, N, N, I(DstMem16 | Mov, em_fnstcw),
पूर्ण, अणु
	/* 0xC0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xC8 - 0xCF */
	N, N, N, N, N, N, N, N,
	/* 0xD0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xD8 - 0xDF */
	N, N, N, N, N, N, N, N,
	/* 0xE0 - 0xE7 */
	N, N, N, N, N, N, N, N,
	/* 0xE8 - 0xEF */
	N, N, N, N, N, N, N, N,
	/* 0xF0 - 0xF7 */
	N, N, N, N, N, N, N, N,
	/* 0xF8 - 0xFF */
	N, N, N, N, N, N, N, N,
पूर्ण पूर्ण;

अटल स्थिर काष्ठा escape escape_db = अणु अणु
	N, N, N, N, N, N, N, N,
पूर्ण, अणु
	/* 0xC0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xC8 - 0xCF */
	N, N, N, N, N, N, N, N,
	/* 0xD0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xD8 - 0xDF */
	N, N, N, N, N, N, N, N,
	/* 0xE0 - 0xE7 */
	N, N, N, I(ImplicitOps, em_fninit), N, N, N, N,
	/* 0xE8 - 0xEF */
	N, N, N, N, N, N, N, N,
	/* 0xF0 - 0xF7 */
	N, N, N, N, N, N, N, N,
	/* 0xF8 - 0xFF */
	N, N, N, N, N, N, N, N,
पूर्ण पूर्ण;

अटल स्थिर काष्ठा escape escape_dd = अणु अणु
	N, N, N, N, N, N, N, I(DstMem16 | Mov, em_fnstsw),
पूर्ण, अणु
	/* 0xC0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xC8 - 0xCF */
	N, N, N, N, N, N, N, N,
	/* 0xD0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xD8 - 0xDF */
	N, N, N, N, N, N, N, N,
	/* 0xE0 - 0xE7 */
	N, N, N, N, N, N, N, N,
	/* 0xE8 - 0xEF */
	N, N, N, N, N, N, N, N,
	/* 0xF0 - 0xF7 */
	N, N, N, N, N, N, N, N,
	/* 0xF8 - 0xFF */
	N, N, N, N, N, N, N, N,
पूर्ण पूर्ण;

अटल स्थिर काष्ठा instr_dual instr_dual_0f_c3 = अणु
	I(DstMem | SrcReg | ModRM | No16 | Mov, em_mov), N
पूर्ण;

अटल स्थिर काष्ठा mode_dual mode_dual_63 = अणु
	N, I(DstReg | SrcMem32 | ModRM | Mov, em_movsxd)
पूर्ण;

अटल स्थिर काष्ठा opcode opcode_table[256] = अणु
	/* 0x00 - 0x07 */
	F6ALU(Lock, em_add),
	I(ImplicitOps | Stack | No64 | Src2ES, em_push_sreg),
	I(ImplicitOps | Stack | No64 | Src2ES, em_pop_sreg),
	/* 0x08 - 0x0F */
	F6ALU(Lock | PageTable, em_or),
	I(ImplicitOps | Stack | No64 | Src2CS, em_push_sreg),
	N,
	/* 0x10 - 0x17 */
	F6ALU(Lock, em_adc),
	I(ImplicitOps | Stack | No64 | Src2SS, em_push_sreg),
	I(ImplicitOps | Stack | No64 | Src2SS, em_pop_sreg),
	/* 0x18 - 0x1F */
	F6ALU(Lock, em_sbb),
	I(ImplicitOps | Stack | No64 | Src2DS, em_push_sreg),
	I(ImplicitOps | Stack | No64 | Src2DS, em_pop_sreg),
	/* 0x20 - 0x27 */
	F6ALU(Lock | PageTable, em_and), N, N,
	/* 0x28 - 0x2F */
	F6ALU(Lock, em_sub), N, I(ByteOp | DstAcc | No64, em_das),
	/* 0x30 - 0x37 */
	F6ALU(Lock, em_xor), N, N,
	/* 0x38 - 0x3F */
	F6ALU(NoWrite, em_cmp), N, N,
	/* 0x40 - 0x4F */
	X8(F(DstReg, em_inc)), X8(F(DstReg, em_dec)),
	/* 0x50 - 0x57 */
	X8(I(SrcReg | Stack, em_push)),
	/* 0x58 - 0x5F */
	X8(I(DstReg | Stack, em_pop)),
	/* 0x60 - 0x67 */
	I(ImplicitOps | Stack | No64, em_pusha),
	I(ImplicitOps | Stack | No64, em_popa),
	N, MD(ModRM, &mode_dual_63),
	N, N, N, N,
	/* 0x68 - 0x6F */
	I(SrcImm | Mov | Stack, em_push),
	I(DstReg | SrcMem | ModRM | Src2Imm, em_imul_3op),
	I(SrcImmByte | Mov | Stack, em_push),
	I(DstReg | SrcMem | ModRM | Src2ImmByte, em_imul_3op),
	I2bvIP(DstDI | SrcDX | Mov | String | Unaligned, em_in, ins, check_perm_in), /* insb, insw/insd */
	I2bvIP(SrcSI | DstDX | String, em_out, outs, check_perm_out), /* outsb, outsw/outsd */
	/* 0x70 - 0x7F */
	X16(D(SrcImmByte | NearBranch)),
	/* 0x80 - 0x87 */
	G(ByteOp | DstMem | SrcImm, group1),
	G(DstMem | SrcImm, group1),
	G(ByteOp | DstMem | SrcImm | No64, group1),
	G(DstMem | SrcImmByte, group1),
	F2bv(DstMem | SrcReg | ModRM | NoWrite, em_test),
	I2bv(DstMem | SrcReg | ModRM | Lock | PageTable, em_xchg),
	/* 0x88 - 0x8F */
	I2bv(DstMem | SrcReg | ModRM | Mov | PageTable, em_mov),
	I2bv(DstReg | SrcMem | ModRM | Mov, em_mov),
	I(DstMem | SrcNone | ModRM | Mov | PageTable, em_mov_rm_sreg),
	D(ModRM | SrcMem | NoAccess | DstReg),
	I(ImplicitOps | SrcMem16 | ModRM, em_mov_sreg_rm),
	G(0, group1A),
	/* 0x90 - 0x97 */
	DI(SrcAcc | DstReg, छोड़ो), X7(D(SrcAcc | DstReg)),
	/* 0x98 - 0x9F */
	D(DstAcc | SrcNone), I(ImplicitOps | SrcAcc, em_cwd),
	I(SrcImmFAddr | No64, em_call_far), N,
	II(ImplicitOps | Stack, em_pushf, pushf),
	II(ImplicitOps | Stack, em_popf, popf),
	I(ImplicitOps, em_sahf), I(ImplicitOps, em_lahf),
	/* 0xA0 - 0xA7 */
	I2bv(DstAcc | SrcMem | Mov | MemAbs, em_mov),
	I2bv(DstMem | SrcAcc | Mov | MemAbs | PageTable, em_mov),
	I2bv(SrcSI | DstDI | Mov | String | TwoMemOp, em_mov),
	F2bv(SrcSI | DstDI | String | NoWrite | TwoMemOp, em_cmp_r),
	/* 0xA8 - 0xAF */
	F2bv(DstAcc | SrcImm | NoWrite, em_test),
	I2bv(SrcAcc | DstDI | Mov | String, em_mov),
	I2bv(SrcSI | DstAcc | Mov | String, em_mov),
	F2bv(SrcAcc | DstDI | String | NoWrite, em_cmp_r),
	/* 0xB0 - 0xB7 */
	X8(I(ByteOp | DstReg | SrcImm | Mov, em_mov)),
	/* 0xB8 - 0xBF */
	X8(I(DstReg | SrcImm64 | Mov, em_mov)),
	/* 0xC0 - 0xC7 */
	G(ByteOp | Src2ImmByte, group2), G(Src2ImmByte, group2),
	I(ImplicitOps | NearBranch | SrcImmU16, em_ret_near_imm),
	I(ImplicitOps | NearBranch, em_ret),
	I(DstReg | SrcMemFAddr | ModRM | No64 | Src2ES, em_lseg),
	I(DstReg | SrcMemFAddr | ModRM | No64 | Src2DS, em_lseg),
	G(ByteOp, group11), G(0, group11),
	/* 0xC8 - 0xCF */
	I(Stack | SrcImmU16 | Src2ImmByte, em_enter), I(Stack, em_leave),
	I(ImplicitOps | SrcImmU16, em_ret_far_imm),
	I(ImplicitOps, em_ret_far),
	D(ImplicitOps), DI(SrcImmByte, पूर्णांकn),
	D(ImplicitOps | No64), II(ImplicitOps, em_iret, iret),
	/* 0xD0 - 0xD7 */
	G(Src2One | ByteOp, group2), G(Src2One, group2),
	G(Src2CL | ByteOp, group2), G(Src2CL, group2),
	I(DstAcc | SrcImmUByte | No64, em_aam),
	I(DstAcc | SrcImmUByte | No64, em_aad),
	F(DstAcc | ByteOp | No64, em_salc),
	I(DstAcc | SrcXLat | ByteOp, em_mov),
	/* 0xD8 - 0xDF */
	N, E(0, &escape_d9), N, E(0, &escape_db), N, E(0, &escape_dd), N, N,
	/* 0xE0 - 0xE7 */
	X3(I(SrcImmByte | NearBranch, em_loop)),
	I(SrcImmByte | NearBranch, em_jcxz),
	I2bvIP(SrcImmUByte | DstAcc, em_in,  in,  check_perm_in),
	I2bvIP(SrcAcc | DstImmUByte, em_out, out, check_perm_out),
	/* 0xE8 - 0xEF */
	I(SrcImm | NearBranch, em_call), D(SrcImm | ImplicitOps | NearBranch),
	I(SrcImmFAddr | No64, em_jmp_far),
	D(SrcImmByte | ImplicitOps | NearBranch),
	I2bvIP(SrcDX | DstAcc, em_in,  in,  check_perm_in),
	I2bvIP(SrcAcc | DstDX, em_out, out, check_perm_out),
	/* 0xF0 - 0xF7 */
	N, DI(ImplicitOps, icebp), N, N,
	DI(ImplicitOps | Priv, hlt), D(ImplicitOps),
	G(ByteOp, group3), G(0, group3),
	/* 0xF8 - 0xFF */
	D(ImplicitOps), D(ImplicitOps),
	I(ImplicitOps, em_cli), I(ImplicitOps, em_sti),
	D(ImplicitOps), D(ImplicitOps), G(0, group4), G(0, group5),
पूर्ण;

अटल स्थिर काष्ठा opcode twobyte_table[256] = अणु
	/* 0x00 - 0x0F */
	G(0, group6), GD(0, &group7), N, N,
	N, I(ImplicitOps | EmulateOnUD, em_syscall),
	II(ImplicitOps | Priv, em_clts, clts), N,
	DI(ImplicitOps | Priv, invd), DI(ImplicitOps | Priv, wbinvd), N, N,
	N, D(ImplicitOps | ModRM | SrcMem | NoAccess), N, N,
	/* 0x10 - 0x1F */
	GP(ModRM | DstReg | SrcMem | Mov | Sse, &pfx_0f_10_0f_11),
	GP(ModRM | DstMem | SrcReg | Mov | Sse, &pfx_0f_10_0f_11),
	N, N, N, N, N, N,
	D(ImplicitOps | ModRM | SrcMem | NoAccess), /* 4 * prefetch + 4 * reserved NOP */
	D(ImplicitOps | ModRM | SrcMem | NoAccess), N, N,
	D(ImplicitOps | ModRM | SrcMem | NoAccess), /* 8 * reserved NOP */
	D(ImplicitOps | ModRM | SrcMem | NoAccess), /* 8 * reserved NOP */
	D(ImplicitOps | ModRM | SrcMem | NoAccess), /* 8 * reserved NOP */
	D(ImplicitOps | ModRM | SrcMem | NoAccess), /* NOP + 7 * reserved NOP */
	/* 0x20 - 0x2F */
	DIP(ModRM | DstMem | Priv | Op3264 | NoMod, cr_पढ़ो, check_cr_access),
	DIP(ModRM | DstMem | Priv | Op3264 | NoMod, dr_पढ़ो, check_dr_पढ़ो),
	IIP(ModRM | SrcMem | Priv | Op3264 | NoMod, em_cr_ग_लिखो, cr_ग_लिखो,
						check_cr_access),
	IIP(ModRM | SrcMem | Priv | Op3264 | NoMod, em_dr_ग_लिखो, dr_ग_लिखो,
						check_dr_ग_लिखो),
	N, N, N, N,
	GP(ModRM | DstReg | SrcMem | Mov | Sse, &pfx_0f_28_0f_29),
	GP(ModRM | DstMem | SrcReg | Mov | Sse, &pfx_0f_28_0f_29),
	N, GP(ModRM | DstMem | SrcReg | Mov | Sse, &pfx_0f_2b),
	N, N, N, N,
	/* 0x30 - 0x3F */
	II(ImplicitOps | Priv, em_wrmsr, wrmsr),
	IIP(ImplicitOps, em_rdtsc, rdtsc, check_rdtsc),
	II(ImplicitOps | Priv, em_rdmsr, rdmsr),
	IIP(ImplicitOps, em_rdpmc, rdpmc, check_rdpmc),
	I(ImplicitOps | EmulateOnUD, em_sysenter),
	I(ImplicitOps | Priv | EmulateOnUD, em_sysनिकास),
	N, N,
	N, N, N, N, N, N, N, N,
	/* 0x40 - 0x4F */
	X16(D(DstReg | SrcMem | ModRM)),
	/* 0x50 - 0x5F */
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,
	/* 0x60 - 0x6F */
	N, N, N, N,
	N, N, N, N,
	N, N, N, N,
	N, N, N, GP(SrcMem | DstReg | ModRM | Mov, &pfx_0f_6f_0f_7f),
	/* 0x70 - 0x7F */
	N, N, N, N,
	N, N, N, N,
	N, N, N, N,
	N, N, N, GP(SrcReg | DstMem | ModRM | Mov, &pfx_0f_6f_0f_7f),
	/* 0x80 - 0x8F */
	X16(D(SrcImm | NearBranch)),
	/* 0x90 - 0x9F */
	X16(D(ByteOp | DstMem | SrcNone | ModRM| Mov)),
	/* 0xA0 - 0xA7 */
	I(Stack | Src2FS, em_push_sreg), I(Stack | Src2FS, em_pop_sreg),
	II(ImplicitOps, em_cpuid, cpuid),
	F(DstMem | SrcReg | ModRM | BitOp | NoWrite, em_bt),
	F(DstMem | SrcReg | Src2ImmByte | ModRM, em_shld),
	F(DstMem | SrcReg | Src2CL | ModRM, em_shld), N, N,
	/* 0xA8 - 0xAF */
	I(Stack | Src2GS, em_push_sreg), I(Stack | Src2GS, em_pop_sreg),
	II(EmulateOnUD | ImplicitOps, em_rsm, rsm),
	F(DstMem | SrcReg | ModRM | BitOp | Lock | PageTable, em_bts),
	F(DstMem | SrcReg | Src2ImmByte | ModRM, em_shrd),
	F(DstMem | SrcReg | Src2CL | ModRM, em_shrd),
	GD(0, &group15), F(DstReg | SrcMem | ModRM, em_imul),
	/* 0xB0 - 0xB7 */
	I2bv(DstMem | SrcReg | ModRM | Lock | PageTable | SrcWrite, em_cmpxchg),
	I(DstReg | SrcMemFAddr | ModRM | Src2SS, em_lseg),
	F(DstMem | SrcReg | ModRM | BitOp | Lock, em_btr),
	I(DstReg | SrcMemFAddr | ModRM | Src2FS, em_lseg),
	I(DstReg | SrcMemFAddr | ModRM | Src2GS, em_lseg),
	D(DstReg | SrcMem8 | ModRM | Mov), D(DstReg | SrcMem16 | ModRM | Mov),
	/* 0xB8 - 0xBF */
	N, N,
	G(BitOp, group8),
	F(DstMem | SrcReg | ModRM | BitOp | Lock | PageTable, em_btc),
	I(DstReg | SrcMem | ModRM, em_bsf_c),
	I(DstReg | SrcMem | ModRM, em_bsr_c),
	D(DstReg | SrcMem8 | ModRM | Mov), D(DstReg | SrcMem16 | ModRM | Mov),
	/* 0xC0 - 0xC7 */
	F2bv(DstMem | SrcReg | ModRM | SrcWrite | Lock, em_xadd),
	N, ID(0, &instr_dual_0f_c3),
	N, N, N, GD(0, &group9),
	/* 0xC8 - 0xCF */
	X8(I(DstReg, em_bswap)),
	/* 0xD0 - 0xDF */
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,
	/* 0xE0 - 0xEF */
	N, N, N, N, N, N, N, GP(SrcReg | DstMem | ModRM | Mov, &pfx_0f_e7),
	N, N, N, N, N, N, N, N,
	/* 0xF0 - 0xFF */
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N
पूर्ण;

अटल स्थिर काष्ठा instr_dual instr_dual_0f_38_f0 = अणु
	I(DstReg | SrcMem | Mov, em_movbe), N
पूर्ण;

अटल स्थिर काष्ठा instr_dual instr_dual_0f_38_f1 = अणु
	I(DstMem | SrcReg | Mov, em_movbe), N
पूर्ण;

अटल स्थिर काष्ठा gprefix three_byte_0f_38_f0 = अणु
	ID(0, &instr_dual_0f_38_f0), N, N, N
पूर्ण;

अटल स्थिर काष्ठा gprefix three_byte_0f_38_f1 = अणु
	ID(0, &instr_dual_0f_38_f1), N, N, N
पूर्ण;

/*
 * Insns below are selected by the prefix which indexed by the third opcode
 * byte.
 */
अटल स्थिर काष्ठा opcode opcode_map_0f_38[256] = अणु
	/* 0x00 - 0x7f */
	X16(N), X16(N), X16(N), X16(N), X16(N), X16(N), X16(N), X16(N),
	/* 0x80 - 0xef */
	X16(N), X16(N), X16(N), X16(N), X16(N), X16(N), X16(N),
	/* 0xf0 - 0xf1 */
	GP(EmulateOnUD | ModRM, &three_byte_0f_38_f0),
	GP(EmulateOnUD | ModRM, &three_byte_0f_38_f1),
	/* 0xf2 - 0xff */
	N, N, X4(N), X8(N)
पूर्ण;

#अघोषित D
#अघोषित N
#अघोषित G
#अघोषित GD
#अघोषित I
#अघोषित GP
#अघोषित EXT
#अघोषित MD
#अघोषित ID

#अघोषित D2bv
#अघोषित D2bvIP
#अघोषित I2bv
#अघोषित I2bvIP
#अघोषित I6ALU

अटल अचिन्हित imm_size(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अचिन्हित size;

	size = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
	अगर (size == 8)
		size = 4;
	वापस size;
पूर्ण

अटल पूर्णांक decode_imm(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा opeअक्रम *op,
		      अचिन्हित size, bool sign_extension)
अणु
	पूर्णांक rc = X86EMUL_CONTINUE;

	op->type = OP_IMM;
	op->bytes = size;
	op->addr.mem.ea = ctxt->_eip;
	/* NB. Immediates are sign-extended as necessary. */
	चयन (op->bytes) अणु
	हाल 1:
		op->val = insn_fetch(s8, ctxt);
		अवरोध;
	हाल 2:
		op->val = insn_fetch(s16, ctxt);
		अवरोध;
	हाल 4:
		op->val = insn_fetch(s32, ctxt);
		अवरोध;
	हाल 8:
		op->val = insn_fetch(s64, ctxt);
		अवरोध;
	पूर्ण
	अगर (!sign_extension) अणु
		चयन (op->bytes) अणु
		हाल 1:
			op->val &= 0xff;
			अवरोध;
		हाल 2:
			op->val &= 0xffff;
			अवरोध;
		हाल 4:
			op->val &= 0xffffffff;
			अवरोध;
		पूर्ण
	पूर्ण
करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक decode_opeअक्रम(काष्ठा x86_emulate_ctxt *ctxt, काष्ठा opeअक्रम *op,
			  अचिन्हित d)
अणु
	पूर्णांक rc = X86EMUL_CONTINUE;

	चयन (d) अणु
	हाल OpReg:
		decode_रेजिस्टर_opeअक्रम(ctxt, op);
		अवरोध;
	हाल OpImmUByte:
		rc = decode_imm(ctxt, op, 1, false);
		अवरोध;
	हाल OpMem:
		ctxt->memop.bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
	mem_common:
		*op = ctxt->memop;
		ctxt->memopp = op;
		अगर (ctxt->d & BitOp)
			fetch_bit_opeअक्रम(ctxt);
		op->orig_val = op->val;
		अवरोध;
	हाल OpMem64:
		ctxt->memop.bytes = (ctxt->op_bytes == 8) ? 16 : 8;
		जाओ mem_common;
	हाल OpAcc:
		op->type = OP_REG;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.reg = reg_rmw(ctxt, VCPU_REGS_RAX);
		fetch_रेजिस्टर_opeअक्रम(op);
		op->orig_val = op->val;
		अवरोध;
	हाल OpAccLo:
		op->type = OP_REG;
		op->bytes = (ctxt->d & ByteOp) ? 2 : ctxt->op_bytes;
		op->addr.reg = reg_rmw(ctxt, VCPU_REGS_RAX);
		fetch_रेजिस्टर_opeअक्रम(op);
		op->orig_val = op->val;
		अवरोध;
	हाल OpAccHi:
		अगर (ctxt->d & ByteOp) अणु
			op->type = OP_NONE;
			अवरोध;
		पूर्ण
		op->type = OP_REG;
		op->bytes = ctxt->op_bytes;
		op->addr.reg = reg_rmw(ctxt, VCPU_REGS_RDX);
		fetch_रेजिस्टर_opeअक्रम(op);
		op->orig_val = op->val;
		अवरोध;
	हाल OpDI:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.mem.ea =
			रेजिस्टर_address(ctxt, VCPU_REGS_RDI);
		op->addr.mem.seg = VCPU_SREG_ES;
		op->val = 0;
		op->count = 1;
		अवरोध;
	हाल OpDX:
		op->type = OP_REG;
		op->bytes = 2;
		op->addr.reg = reg_rmw(ctxt, VCPU_REGS_RDX);
		fetch_रेजिस्टर_opeअक्रम(op);
		अवरोध;
	हाल OpCL:
		op->type = OP_IMM;
		op->bytes = 1;
		op->val = reg_पढ़ो(ctxt, VCPU_REGS_RCX) & 0xff;
		अवरोध;
	हाल OpImmByte:
		rc = decode_imm(ctxt, op, 1, true);
		अवरोध;
	हाल OpOne:
		op->type = OP_IMM;
		op->bytes = 1;
		op->val = 1;
		अवरोध;
	हाल OpImm:
		rc = decode_imm(ctxt, op, imm_size(ctxt), true);
		अवरोध;
	हाल OpImm64:
		rc = decode_imm(ctxt, op, ctxt->op_bytes, true);
		अवरोध;
	हाल OpMem8:
		ctxt->memop.bytes = 1;
		अगर (ctxt->memop.type == OP_REG) अणु
			ctxt->memop.addr.reg = decode_रेजिस्टर(ctxt,
					ctxt->modrm_rm, true);
			fetch_रेजिस्टर_opeअक्रम(&ctxt->memop);
		पूर्ण
		जाओ mem_common;
	हाल OpMem16:
		ctxt->memop.bytes = 2;
		जाओ mem_common;
	हाल OpMem32:
		ctxt->memop.bytes = 4;
		जाओ mem_common;
	हाल OpImmU16:
		rc = decode_imm(ctxt, op, 2, false);
		अवरोध;
	हाल OpImmU:
		rc = decode_imm(ctxt, op, imm_size(ctxt), false);
		अवरोध;
	हाल OpSI:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.mem.ea =
			रेजिस्टर_address(ctxt, VCPU_REGS_RSI);
		op->addr.mem.seg = ctxt->seg_override;
		op->val = 0;
		op->count = 1;
		अवरोध;
	हाल OpXLat:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addr.mem.ea =
			address_mask(ctxt,
				reg_पढ़ो(ctxt, VCPU_REGS_RBX) +
				(reg_पढ़ो(ctxt, VCPU_REGS_RAX) & 0xff));
		op->addr.mem.seg = ctxt->seg_override;
		op->val = 0;
		अवरोध;
	हाल OpImmFAddr:
		op->type = OP_IMM;
		op->addr.mem.ea = ctxt->_eip;
		op->bytes = ctxt->op_bytes + 2;
		insn_fetch_arr(op->valptr, op->bytes, ctxt);
		अवरोध;
	हाल OpMemFAddr:
		ctxt->memop.bytes = ctxt->op_bytes + 2;
		जाओ mem_common;
	हाल OpES:
		op->type = OP_IMM;
		op->val = VCPU_SREG_ES;
		अवरोध;
	हाल OpCS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_CS;
		अवरोध;
	हाल OpSS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_SS;
		अवरोध;
	हाल OpDS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_DS;
		अवरोध;
	हाल OpFS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_FS;
		अवरोध;
	हाल OpGS:
		op->type = OP_IMM;
		op->val = VCPU_SREG_GS;
		अवरोध;
	हाल OpImplicit:
		/* Special inकाष्ठाions करो their own opeअक्रम decoding. */
	शेष:
		op->type = OP_NONE; /* Disable ग_लिखोback. */
		अवरोध;
	पूर्ण

करोne:
	वापस rc;
पूर्ण

पूर्णांक x86_decode_insn(काष्ठा x86_emulate_ctxt *ctxt, व्योम *insn, पूर्णांक insn_len, पूर्णांक emulation_type)
अणु
	पूर्णांक rc = X86EMUL_CONTINUE;
	पूर्णांक mode = ctxt->mode;
	पूर्णांक def_op_bytes, def_ad_bytes, goffset, simd_prefix;
	bool op_prefix = false;
	bool has_seg_override = false;
	काष्ठा opcode opcode;
	u16 dummy;
	काष्ठा desc_काष्ठा desc;

	ctxt->memop.type = OP_NONE;
	ctxt->memopp = शून्य;
	ctxt->_eip = ctxt->eip;
	ctxt->fetch.ptr = ctxt->fetch.data;
	ctxt->fetch.end = ctxt->fetch.data + insn_len;
	ctxt->opcode_len = 1;
	ctxt->पूर्णांकercept = x86_पूर्णांकercept_none;
	अगर (insn_len > 0)
		स_नकल(ctxt->fetch.data, insn, insn_len);
	अन्यथा अणु
		rc = __करो_insn_fetch_bytes(ctxt, 1);
		अगर (rc != X86EMUL_CONTINUE)
			जाओ करोne;
	पूर्ण

	चयन (mode) अणु
	हाल X86EMUL_MODE_REAL:
	हाल X86EMUL_MODE_VM86:
		def_op_bytes = def_ad_bytes = 2;
		ctxt->ops->get_segment(ctxt, &dummy, &desc, शून्य, VCPU_SREG_CS);
		अगर (desc.d)
			def_op_bytes = def_ad_bytes = 4;
		अवरोध;
	हाल X86EMUL_MODE_PROT16:
		def_op_bytes = def_ad_bytes = 2;
		अवरोध;
	हाल X86EMUL_MODE_PROT32:
		def_op_bytes = def_ad_bytes = 4;
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल X86EMUL_MODE_PROT64:
		def_op_bytes = 4;
		def_ad_bytes = 8;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस EMULATION_FAILED;
	पूर्ण

	ctxt->op_bytes = def_op_bytes;
	ctxt->ad_bytes = def_ad_bytes;

	/* Legacy prefixes. */
	क्रम (;;) अणु
		चयन (ctxt->b = insn_fetch(u8, ctxt)) अणु
		हाल 0x66:	/* opeअक्रम-size override */
			op_prefix = true;
			/* चयन between 2/4 bytes */
			ctxt->op_bytes = def_op_bytes ^ 6;
			अवरोध;
		हाल 0x67:	/* address-size override */
			अगर (mode == X86EMUL_MODE_PROT64)
				/* चयन between 4/8 bytes */
				ctxt->ad_bytes = def_ad_bytes ^ 12;
			अन्यथा
				/* चयन between 2/4 bytes */
				ctxt->ad_bytes = def_ad_bytes ^ 6;
			अवरोध;
		हाल 0x26:	/* ES override */
			has_seg_override = true;
			ctxt->seg_override = VCPU_SREG_ES;
			अवरोध;
		हाल 0x2e:	/* CS override */
			has_seg_override = true;
			ctxt->seg_override = VCPU_SREG_CS;
			अवरोध;
		हाल 0x36:	/* SS override */
			has_seg_override = true;
			ctxt->seg_override = VCPU_SREG_SS;
			अवरोध;
		हाल 0x3e:	/* DS override */
			has_seg_override = true;
			ctxt->seg_override = VCPU_SREG_DS;
			अवरोध;
		हाल 0x64:	/* FS override */
			has_seg_override = true;
			ctxt->seg_override = VCPU_SREG_FS;
			अवरोध;
		हाल 0x65:	/* GS override */
			has_seg_override = true;
			ctxt->seg_override = VCPU_SREG_GS;
			अवरोध;
		हाल 0x40 ... 0x4f: /* REX */
			अगर (mode != X86EMUL_MODE_PROT64)
				जाओ करोne_prefixes;
			ctxt->rex_prefix = ctxt->b;
			जारी;
		हाल 0xf0:	/* LOCK */
			ctxt->lock_prefix = 1;
			अवरोध;
		हाल 0xf2:	/* REPNE/REPNZ */
		हाल 0xf3:	/* REP/REPE/REPZ */
			ctxt->rep_prefix = ctxt->b;
			अवरोध;
		शेष:
			जाओ करोne_prefixes;
		पूर्ण

		/* Any legacy prefix after a REX prefix nullअगरies its effect. */

		ctxt->rex_prefix = 0;
	पूर्ण

करोne_prefixes:

	/* REX prefix. */
	अगर (ctxt->rex_prefix & 8)
		ctxt->op_bytes = 8;	/* REX.W */

	/* Opcode byte(s). */
	opcode = opcode_table[ctxt->b];
	/* Two-byte opcode? */
	अगर (ctxt->b == 0x0f) अणु
		ctxt->opcode_len = 2;
		ctxt->b = insn_fetch(u8, ctxt);
		opcode = twobyte_table[ctxt->b];

		/* 0F_38 opcode map */
		अगर (ctxt->b == 0x38) अणु
			ctxt->opcode_len = 3;
			ctxt->b = insn_fetch(u8, ctxt);
			opcode = opcode_map_0f_38[ctxt->b];
		पूर्ण
	पूर्ण
	ctxt->d = opcode.flags;

	अगर (ctxt->d & ModRM)
		ctxt->modrm = insn_fetch(u8, ctxt);

	/* vex-prefix inकाष्ठाions are not implemented */
	अगर (ctxt->opcode_len == 1 && (ctxt->b == 0xc5 || ctxt->b == 0xc4) &&
	    (mode == X86EMUL_MODE_PROT64 || (ctxt->modrm & 0xc0) == 0xc0)) अणु
		ctxt->d = NotImpl;
	पूर्ण

	जबतक (ctxt->d & GroupMask) अणु
		चयन (ctxt->d & GroupMask) अणु
		हाल Group:
			goffset = (ctxt->modrm >> 3) & 7;
			opcode = opcode.u.group[goffset];
			अवरोध;
		हाल GroupDual:
			goffset = (ctxt->modrm >> 3) & 7;
			अगर ((ctxt->modrm >> 6) == 3)
				opcode = opcode.u.gdual->mod3[goffset];
			अन्यथा
				opcode = opcode.u.gdual->mod012[goffset];
			अवरोध;
		हाल RMExt:
			goffset = ctxt->modrm & 7;
			opcode = opcode.u.group[goffset];
			अवरोध;
		हाल Prefix:
			अगर (ctxt->rep_prefix && op_prefix)
				वापस EMULATION_FAILED;
			simd_prefix = op_prefix ? 0x66 : ctxt->rep_prefix;
			चयन (simd_prefix) अणु
			हाल 0x00: opcode = opcode.u.gprefix->pfx_no; अवरोध;
			हाल 0x66: opcode = opcode.u.gprefix->pfx_66; अवरोध;
			हाल 0xf2: opcode = opcode.u.gprefix->pfx_f2; अवरोध;
			हाल 0xf3: opcode = opcode.u.gprefix->pfx_f3; अवरोध;
			पूर्ण
			अवरोध;
		हाल Escape:
			अगर (ctxt->modrm > 0xbf) अणु
				माप_प्रकार size = ARRAY_SIZE(opcode.u.esc->high);
				u32 index = array_index_nospec(
					ctxt->modrm - 0xc0, size);

				opcode = opcode.u.esc->high[index];
			पूर्ण अन्यथा अणु
				opcode = opcode.u.esc->op[(ctxt->modrm >> 3) & 7];
			पूर्ण
			अवरोध;
		हाल InstrDual:
			अगर ((ctxt->modrm >> 6) == 3)
				opcode = opcode.u.idual->mod3;
			अन्यथा
				opcode = opcode.u.idual->mod012;
			अवरोध;
		हाल ModeDual:
			अगर (ctxt->mode == X86EMUL_MODE_PROT64)
				opcode = opcode.u.mdual->mode64;
			अन्यथा
				opcode = opcode.u.mdual->mode32;
			अवरोध;
		शेष:
			वापस EMULATION_FAILED;
		पूर्ण

		ctxt->d &= ~(u64)GroupMask;
		ctxt->d |= opcode.flags;
	पूर्ण

	/* Unrecognised? */
	अगर (ctxt->d == 0)
		वापस EMULATION_FAILED;

	ctxt->execute = opcode.u.execute;

	अगर (unlikely(emulation_type & EMULTYPE_TRAP_UD) &&
	    likely(!(ctxt->d & EmulateOnUD)))
		वापस EMULATION_FAILED;

	अगर (unlikely(ctxt->d &
	    (NotImpl|Stack|Op3264|Sse|Mmx|Intercept|CheckPerm|NearBranch|
	     No16))) अणु
		/*
		 * These are copied unconditionally here, and checked unconditionally
		 * in x86_emulate_insn.
		 */
		ctxt->check_perm = opcode.check_perm;
		ctxt->पूर्णांकercept = opcode.पूर्णांकercept;

		अगर (ctxt->d & NotImpl)
			वापस EMULATION_FAILED;

		अगर (mode == X86EMUL_MODE_PROT64) अणु
			अगर (ctxt->op_bytes == 4 && (ctxt->d & Stack))
				ctxt->op_bytes = 8;
			अन्यथा अगर (ctxt->d & NearBranch)
				ctxt->op_bytes = 8;
		पूर्ण

		अगर (ctxt->d & Op3264) अणु
			अगर (mode == X86EMUL_MODE_PROT64)
				ctxt->op_bytes = 8;
			अन्यथा
				ctxt->op_bytes = 4;
		पूर्ण

		अगर ((ctxt->d & No16) && ctxt->op_bytes == 2)
			ctxt->op_bytes = 4;

		अगर (ctxt->d & Sse)
			ctxt->op_bytes = 16;
		अन्यथा अगर (ctxt->d & Mmx)
			ctxt->op_bytes = 8;
	पूर्ण

	/* ModRM and SIB bytes. */
	अगर (ctxt->d & ModRM) अणु
		rc = decode_modrm(ctxt, &ctxt->memop);
		अगर (!has_seg_override) अणु
			has_seg_override = true;
			ctxt->seg_override = ctxt->modrm_seg;
		पूर्ण
	पूर्ण अन्यथा अगर (ctxt->d & MemAbs)
		rc = decode_असल(ctxt, &ctxt->memop);
	अगर (rc != X86EMUL_CONTINUE)
		जाओ करोne;

	अगर (!has_seg_override)
		ctxt->seg_override = VCPU_SREG_DS;

	ctxt->memop.addr.mem.seg = ctxt->seg_override;

	/*
	 * Decode and fetch the source opeअक्रम: रेजिस्टर, memory
	 * or immediate.
	 */
	rc = decode_opeअक्रम(ctxt, &ctxt->src, (ctxt->d >> SrcShअगरt) & OpMask);
	अगर (rc != X86EMUL_CONTINUE)
		जाओ करोne;

	/*
	 * Decode and fetch the second source opeअक्रम: रेजिस्टर, memory
	 * or immediate.
	 */
	rc = decode_opeअक्रम(ctxt, &ctxt->src2, (ctxt->d >> Src2Shअगरt) & OpMask);
	अगर (rc != X86EMUL_CONTINUE)
		जाओ करोne;

	/* Decode and fetch the destination opeअक्रम: रेजिस्टर or memory. */
	rc = decode_opeअक्रम(ctxt, &ctxt->dst, (ctxt->d >> DstShअगरt) & OpMask);

	अगर (ctxt->rip_relative && likely(ctxt->memopp))
		ctxt->memopp->addr.mem.ea = address_mask(ctxt,
					ctxt->memopp->addr.mem.ea + ctxt->_eip);

करोne:
	अगर (rc == X86EMUL_PROPAGATE_FAULT)
		ctxt->have_exception = true;
	वापस (rc != X86EMUL_CONTINUE) ? EMULATION_FAILED : EMULATION_OK;
पूर्ण

bool x86_page_table_writing_insn(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	वापस ctxt->d & PageTable;
पूर्ण

अटल bool string_insn_completed(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	/* The second termination condition only applies क्रम REPE
	 * and REPNE. Test अगर the repeat string operation prefix is
	 * REPE/REPZ or REPNE/REPNZ and अगर it's the हाल it tests the
	 * corresponding termination condition according to:
	 * 	- अगर REPE/REPZ and ZF = 0 then करोne
	 * 	- अगर REPNE/REPNZ and ZF = 1 then करोne
	 */
	अगर (((ctxt->b == 0xa6) || (ctxt->b == 0xa7) ||
	     (ctxt->b == 0xae) || (ctxt->b == 0xaf))
	    && (((ctxt->rep_prefix == REPE_PREFIX) &&
		 ((ctxt->eflags & X86_EFLAGS_ZF) == 0))
		|| ((ctxt->rep_prefix == REPNE_PREFIX) &&
		    ((ctxt->eflags & X86_EFLAGS_ZF) == X86_EFLAGS_ZF))))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक flush_pending_x87_faults(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	पूर्णांक rc;

	emulator_get_fpu();
	rc = यंत्र_safe("fwait");
	emulator_put_fpu();

	अगर (unlikely(rc != X86EMUL_CONTINUE))
		वापस emulate_exception(ctxt, MF_VECTOR, 0, false);

	वापस X86EMUL_CONTINUE;
पूर्ण

अटल व्योम fetch_possible_mmx_opeअक्रम(काष्ठा opeअक्रम *op)
अणु
	अगर (op->type == OP_MM)
		पढ़ो_mmx_reg(&op->mm_val, op->addr.mm);
पूर्ण

अटल पूर्णांक fastop(काष्ठा x86_emulate_ctxt *ctxt, fastop_t fop)
अणु
	uदीर्घ flags = (ctxt->eflags & EFLAGS_MASK) | X86_EFLAGS_IF;

	अगर (!(ctxt->d & ByteOp))
		fop += __ffs(ctxt->dst.bytes) * FASTOP_SIZE;

	यंत्र("push %[flags]; popf; " CALL_NOSPEC " ; pushf; pop %[flags]\n"
	    : "+a"(ctxt->dst.val), "+d"(ctxt->src.val), [flags]"+D"(flags),
	      [thunk_target]"+S"(fop), ASM_CALL_CONSTRAINT
	    : "c"(ctxt->src2.val));

	ctxt->eflags = (ctxt->eflags & ~EFLAGS_MASK) | (flags & EFLAGS_MASK);
	अगर (!fop) /* exception is वापसed in fop variable */
		वापस emulate_de(ctxt);
	वापस X86EMUL_CONTINUE;
पूर्ण

व्योम init_decode_cache(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	स_रखो(&ctxt->rip_relative, 0,
	       (व्योम *)&ctxt->modrm - (व्योम *)&ctxt->rip_relative);

	ctxt->io_पढ़ो.pos = 0;
	ctxt->io_पढ़ो.end = 0;
	ctxt->mem_पढ़ो.end = 0;
पूर्ण

पूर्णांक x86_emulate_insn(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	स्थिर काष्ठा x86_emulate_ops *ops = ctxt->ops;
	पूर्णांक rc = X86EMUL_CONTINUE;
	पूर्णांक saved_dst_type = ctxt->dst.type;
	अचिन्हित emul_flags;

	ctxt->mem_पढ़ो.pos = 0;

	/* LOCK prefix is allowed only with some inकाष्ठाions */
	अगर (ctxt->lock_prefix && (!(ctxt->d & Lock) || ctxt->dst.type != OP_MEM)) अणु
		rc = emulate_ud(ctxt);
		जाओ करोne;
	पूर्ण

	अगर ((ctxt->d & SrcMask) == SrcMemFAddr && ctxt->src.type != OP_MEM) अणु
		rc = emulate_ud(ctxt);
		जाओ करोne;
	पूर्ण

	emul_flags = ctxt->ops->get_hflags(ctxt);
	अगर (unlikely(ctxt->d &
		     (No64|Undefined|Sse|Mmx|Intercept|CheckPerm|Priv|Prot|String))) अणु
		अगर ((ctxt->mode == X86EMUL_MODE_PROT64 && (ctxt->d & No64)) ||
				(ctxt->d & Undefined)) अणु
			rc = emulate_ud(ctxt);
			जाओ करोne;
		पूर्ण

		अगर (((ctxt->d & (Sse|Mmx)) && ((ops->get_cr(ctxt, 0) & X86_CR0_EM)))
		    || ((ctxt->d & Sse) && !(ops->get_cr(ctxt, 4) & X86_CR4_OSFXSR))) अणु
			rc = emulate_ud(ctxt);
			जाओ करोne;
		पूर्ण

		अगर ((ctxt->d & (Sse|Mmx)) && (ops->get_cr(ctxt, 0) & X86_CR0_TS)) अणु
			rc = emulate_nm(ctxt);
			जाओ करोne;
		पूर्ण

		अगर (ctxt->d & Mmx) अणु
			rc = flush_pending_x87_faults(ctxt);
			अगर (rc != X86EMUL_CONTINUE)
				जाओ करोne;
			/*
			 * Now that we know the fpu is exception safe, we can fetch
			 * opeअक्रमs from it.
			 */
			fetch_possible_mmx_opeअक्रम(&ctxt->src);
			fetch_possible_mmx_opeअक्रम(&ctxt->src2);
			अगर (!(ctxt->d & Mov))
				fetch_possible_mmx_opeअक्रम(&ctxt->dst);
		पूर्ण

		अगर (unlikely(emul_flags & X86EMUL_GUEST_MASK) && ctxt->पूर्णांकercept) अणु
			rc = emulator_check_पूर्णांकercept(ctxt, ctxt->पूर्णांकercept,
						      X86_ICPT_PRE_EXCEPT);
			अगर (rc != X86EMUL_CONTINUE)
				जाओ करोne;
		पूर्ण

		/* Inकाष्ठाion can only be executed in रक्षित mode */
		अगर ((ctxt->d & Prot) && ctxt->mode < X86EMUL_MODE_PROT16) अणु
			rc = emulate_ud(ctxt);
			जाओ करोne;
		पूर्ण

		/* Privileged inकाष्ठाion can be executed only in CPL=0 */
		अगर ((ctxt->d & Priv) && ops->cpl(ctxt)) अणु
			अगर (ctxt->d & PrivUD)
				rc = emulate_ud(ctxt);
			अन्यथा
				rc = emulate_gp(ctxt, 0);
			जाओ करोne;
		पूर्ण

		/* Do inकाष्ठाion specअगरic permission checks */
		अगर (ctxt->d & CheckPerm) अणु
			rc = ctxt->check_perm(ctxt);
			अगर (rc != X86EMUL_CONTINUE)
				जाओ करोne;
		पूर्ण

		अगर (unlikely(emul_flags & X86EMUL_GUEST_MASK) && (ctxt->d & Intercept)) अणु
			rc = emulator_check_पूर्णांकercept(ctxt, ctxt->पूर्णांकercept,
						      X86_ICPT_POST_EXCEPT);
			अगर (rc != X86EMUL_CONTINUE)
				जाओ करोne;
		पूर्ण

		अगर (ctxt->rep_prefix && (ctxt->d & String)) अणु
			/* All REP prefixes have the same first termination condition */
			अगर (address_mask(ctxt, reg_पढ़ो(ctxt, VCPU_REGS_RCX)) == 0) अणु
				string_रेजिस्टरs_quirk(ctxt);
				ctxt->eip = ctxt->_eip;
				ctxt->eflags &= ~X86_EFLAGS_RF;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((ctxt->src.type == OP_MEM) && !(ctxt->d & NoAccess)) अणु
		rc = segmented_पढ़ो(ctxt, ctxt->src.addr.mem,
				    ctxt->src.valptr, ctxt->src.bytes);
		अगर (rc != X86EMUL_CONTINUE)
			जाओ करोne;
		ctxt->src.orig_val64 = ctxt->src.val64;
	पूर्ण

	अगर (ctxt->src2.type == OP_MEM) अणु
		rc = segmented_पढ़ो(ctxt, ctxt->src2.addr.mem,
				    &ctxt->src2.val, ctxt->src2.bytes);
		अगर (rc != X86EMUL_CONTINUE)
			जाओ करोne;
	पूर्ण

	अगर ((ctxt->d & DstMask) == ImplicitOps)
		जाओ special_insn;


	अगर ((ctxt->dst.type == OP_MEM) && !(ctxt->d & Mov)) अणु
		/* optimisation - aव्योम slow emulated पढ़ो अगर Mov */
		rc = segmented_पढ़ो(ctxt, ctxt->dst.addr.mem,
				   &ctxt->dst.val, ctxt->dst.bytes);
		अगर (rc != X86EMUL_CONTINUE) अणु
			अगर (!(ctxt->d & NoWrite) &&
			    rc == X86EMUL_PROPAGATE_FAULT &&
			    ctxt->exception.vector == PF_VECTOR)
				ctxt->exception.error_code |= PFERR_WRITE_MASK;
			जाओ करोne;
		पूर्ण
	पूर्ण
	/* Copy full 64-bit value क्रम CMPXCHG8B.  */
	ctxt->dst.orig_val64 = ctxt->dst.val64;

special_insn:

	अगर (unlikely(emul_flags & X86EMUL_GUEST_MASK) && (ctxt->d & Intercept)) अणु
		rc = emulator_check_पूर्णांकercept(ctxt, ctxt->पूर्णांकercept,
					      X86_ICPT_POST_MEMACCESS);
		अगर (rc != X86EMUL_CONTINUE)
			जाओ करोne;
	पूर्ण

	अगर (ctxt->rep_prefix && (ctxt->d & String))
		ctxt->eflags |= X86_EFLAGS_RF;
	अन्यथा
		ctxt->eflags &= ~X86_EFLAGS_RF;

	अगर (ctxt->execute) अणु
		अगर (ctxt->d & Fastop)
			rc = fastop(ctxt, ctxt->fop);
		अन्यथा
			rc = ctxt->execute(ctxt);
		अगर (rc != X86EMUL_CONTINUE)
			जाओ करोne;
		जाओ ग_लिखोback;
	पूर्ण

	अगर (ctxt->opcode_len == 2)
		जाओ twobyte_insn;
	अन्यथा अगर (ctxt->opcode_len == 3)
		जाओ threebyte_insn;

	चयन (ctxt->b) अणु
	हाल 0x70 ... 0x7f: /* jcc (लघु) */
		अगर (test_cc(ctxt->b, ctxt->eflags))
			rc = jmp_rel(ctxt, ctxt->src.val);
		अवरोध;
	हाल 0x8d: /* lea r16/r32, m */
		ctxt->dst.val = ctxt->src.addr.mem.ea;
		अवरोध;
	हाल 0x90 ... 0x97: /* nop / xchg reg, rax */
		अगर (ctxt->dst.addr.reg == reg_rmw(ctxt, VCPU_REGS_RAX))
			ctxt->dst.type = OP_NONE;
		अन्यथा
			rc = em_xchg(ctxt);
		अवरोध;
	हाल 0x98: /* cbw/cwde/cdqe */
		चयन (ctxt->op_bytes) अणु
		हाल 2: ctxt->dst.val = (s8)ctxt->dst.val; अवरोध;
		हाल 4: ctxt->dst.val = (s16)ctxt->dst.val; अवरोध;
		हाल 8: ctxt->dst.val = (s32)ctxt->dst.val; अवरोध;
		पूर्ण
		अवरोध;
	हाल 0xcc:		/* पूर्णांक3 */
		rc = emulate_पूर्णांक(ctxt, 3);
		अवरोध;
	हाल 0xcd:		/* पूर्णांक n */
		rc = emulate_पूर्णांक(ctxt, ctxt->src.val);
		अवरोध;
	हाल 0xce:		/* पूर्णांकo */
		अगर (ctxt->eflags & X86_EFLAGS_OF)
			rc = emulate_पूर्णांक(ctxt, 4);
		अवरोध;
	हाल 0xe9: /* jmp rel */
	हाल 0xeb: /* jmp rel लघु */
		rc = jmp_rel(ctxt, ctxt->src.val);
		ctxt->dst.type = OP_NONE; /* Disable ग_लिखोback. */
		अवरोध;
	हाल 0xf4:              /* hlt */
		ctxt->ops->halt(ctxt);
		अवरोध;
	हाल 0xf5:	/* cmc */
		/* complement carry flag from eflags reg */
		ctxt->eflags ^= X86_EFLAGS_CF;
		अवरोध;
	हाल 0xf8: /* clc */
		ctxt->eflags &= ~X86_EFLAGS_CF;
		अवरोध;
	हाल 0xf9: /* stc */
		ctxt->eflags |= X86_EFLAGS_CF;
		अवरोध;
	हाल 0xfc: /* cld */
		ctxt->eflags &= ~X86_EFLAGS_DF;
		अवरोध;
	हाल 0xfd: /* std */
		ctxt->eflags |= X86_EFLAGS_DF;
		अवरोध;
	शेष:
		जाओ cannot_emulate;
	पूर्ण

	अगर (rc != X86EMUL_CONTINUE)
		जाओ करोne;

ग_लिखोback:
	अगर (ctxt->d & SrcWrite) अणु
		BUG_ON(ctxt->src.type == OP_MEM || ctxt->src.type == OP_MEM_STR);
		rc = ग_लिखोback(ctxt, &ctxt->src);
		अगर (rc != X86EMUL_CONTINUE)
			जाओ करोne;
	पूर्ण
	अगर (!(ctxt->d & NoWrite)) अणु
		rc = ग_लिखोback(ctxt, &ctxt->dst);
		अगर (rc != X86EMUL_CONTINUE)
			जाओ करोne;
	पूर्ण

	/*
	 * restore dst type in हाल the decoding will be reused
	 * (happens क्रम string inकाष्ठाion )
	 */
	ctxt->dst.type = saved_dst_type;

	अगर ((ctxt->d & SrcMask) == SrcSI)
		string_addr_inc(ctxt, VCPU_REGS_RSI, &ctxt->src);

	अगर ((ctxt->d & DstMask) == DstDI)
		string_addr_inc(ctxt, VCPU_REGS_RDI, &ctxt->dst);

	अगर (ctxt->rep_prefix && (ctxt->d & String)) अणु
		अचिन्हित पूर्णांक count;
		काष्ठा पढ़ो_cache *r = &ctxt->io_पढ़ो;
		अगर ((ctxt->d & SrcMask) == SrcSI)
			count = ctxt->src.count;
		अन्यथा
			count = ctxt->dst.count;
		रेजिस्टर_address_increment(ctxt, VCPU_REGS_RCX, -count);

		अगर (!string_insn_completed(ctxt)) अणु
			/*
			 * Re-enter guest when pio पढ़ो ahead buffer is empty
			 * or, अगर it is not used, after each 1024 iteration.
			 */
			अगर ((r->end != 0 || reg_पढ़ो(ctxt, VCPU_REGS_RCX) & 0x3ff) &&
			    (r->end == 0 || r->end != r->pos)) अणु
				/*
				 * Reset पढ़ो cache. Usually happens beक्रमe
				 * decode, but since inकाष्ठाion is restarted
				 * we have to करो it here.
				 */
				ctxt->mem_पढ़ो.end = 0;
				ग_लिखोback_रेजिस्टरs(ctxt);
				वापस EMULATION_RESTART;
			पूर्ण
			जाओ करोne; /* skip rip ग_लिखोback */
		पूर्ण
		ctxt->eflags &= ~X86_EFLAGS_RF;
	पूर्ण

	ctxt->eip = ctxt->_eip;
	अगर (ctxt->mode != X86EMUL_MODE_PROT64)
		ctxt->eip = (u32)ctxt->_eip;

करोne:
	अगर (rc == X86EMUL_PROPAGATE_FAULT) अणु
		WARN_ON(ctxt->exception.vector > 0x1f);
		ctxt->have_exception = true;
	पूर्ण
	अगर (rc == X86EMUL_INTERCEPTED)
		वापस EMULATION_INTERCEPTED;

	अगर (rc == X86EMUL_CONTINUE)
		ग_लिखोback_रेजिस्टरs(ctxt);

	वापस (rc == X86EMUL_UNHANDLEABLE) ? EMULATION_FAILED : EMULATION_OK;

twobyte_insn:
	चयन (ctxt->b) अणु
	हाल 0x09:		/* wbinvd */
		(ctxt->ops->wbinvd)(ctxt);
		अवरोध;
	हाल 0x08:		/* invd */
	हाल 0x0d:		/* GrpP (prefetch) */
	हाल 0x18:		/* Grp16 (prefetch/nop) */
	हाल 0x1f:		/* nop */
		अवरोध;
	हाल 0x20: /* mov cr, reg */
		ctxt->dst.val = ops->get_cr(ctxt, ctxt->modrm_reg);
		अवरोध;
	हाल 0x21: /* mov from dr to reg */
		ops->get_dr(ctxt, ctxt->modrm_reg, &ctxt->dst.val);
		अवरोध;
	हाल 0x40 ... 0x4f:	/* cmov */
		अगर (test_cc(ctxt->b, ctxt->eflags))
			ctxt->dst.val = ctxt->src.val;
		अन्यथा अगर (ctxt->op_bytes != 4)
			ctxt->dst.type = OP_NONE; /* no ग_लिखोback */
		अवरोध;
	हाल 0x80 ... 0x8f: /* jnz rel, etc*/
		अगर (test_cc(ctxt->b, ctxt->eflags))
			rc = jmp_rel(ctxt, ctxt->src.val);
		अवरोध;
	हाल 0x90 ... 0x9f:     /* setcc r/m8 */
		ctxt->dst.val = test_cc(ctxt->b, ctxt->eflags);
		अवरोध;
	हाल 0xb6 ... 0xb7:	/* movzx */
		ctxt->dst.bytes = ctxt->op_bytes;
		ctxt->dst.val = (ctxt->src.bytes == 1) ? (u8) ctxt->src.val
						       : (u16) ctxt->src.val;
		अवरोध;
	हाल 0xbe ... 0xbf:	/* movsx */
		ctxt->dst.bytes = ctxt->op_bytes;
		ctxt->dst.val = (ctxt->src.bytes == 1) ? (s8) ctxt->src.val :
							(s16) ctxt->src.val;
		अवरोध;
	शेष:
		जाओ cannot_emulate;
	पूर्ण

threebyte_insn:

	अगर (rc != X86EMUL_CONTINUE)
		जाओ करोne;

	जाओ ग_लिखोback;

cannot_emulate:
	वापस EMULATION_FAILED;
पूर्ण

व्योम emulator_invalidate_रेजिस्टर_cache(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	invalidate_रेजिस्टरs(ctxt);
पूर्ण

व्योम emulator_ग_लिखोback_रेजिस्टर_cache(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	ग_लिखोback_रेजिस्टरs(ctxt);
पूर्ण

bool emulator_can_use_gpa(काष्ठा x86_emulate_ctxt *ctxt)
अणु
	अगर (ctxt->rep_prefix && (ctxt->d & String))
		वापस false;

	अगर (ctxt->d & TwoMemOp)
		वापस false;

	वापस true;
पूर्ण

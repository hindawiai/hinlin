<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Architecture-specअगरic unaligned trap handling.
 *
 * Copyright (C) 1999-2002, 2004 Hewlett-Packard Co
 *	Stephane Eranian <eranian@hpl.hp.com>
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * 2002/12/09   Fix rotating रेजिस्टर handling (off-by-1 error, missing fr-rotation).  Fix
 *		get_rse_reg() to not leak kernel bits to user-level (पढ़ोing an out-of-frame
 *		stacked रेजिस्टर वापसs an undefined value; it करोes NOT trigger a
 *		"rsvd register fault").
 * 2001/10/11	Fix unaligned access to rotating रेजिस्टरs in s/w pipelined loops.
 * 2001/08/13	Correct size of extended भग्नs (भग्न_fsz) from 16 to 10 bytes.
 * 2001/01/17	Add support emulation of unaligned kernel accesses.
 */
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/tty.h>
#समावेश <linux/extable.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/rse.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/unaligned.h>

बाह्य पूर्णांक die_अगर_kernel(अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err);

#अघोषित DEBUG_UNALIGNED_TRAP

#अगर_घोषित DEBUG_UNALIGNED_TRAP
# define DPRINT(a...)	करो अणु prपूर्णांकk("%s %u: ", __func__, __LINE__); prपूर्णांकk (a); पूर्ण जबतक (0)
# define DDUMP(str,vp,len)	dump(str, vp, len)

अटल व्योम
dump (स्थिर अक्षर *str, व्योम *vp, माप_प्रकार len)
अणु
	अचिन्हित अक्षर *cp = vp;
	पूर्णांक i;

	prपूर्णांकk("%s", str);
	क्रम (i = 0; i < len; ++i)
		prपूर्णांकk (" %02x", *cp++);
	prपूर्णांकk("\n");
पूर्ण
#अन्यथा
# define DPRINT(a...)
# define DDUMP(str,vp,len)
#पूर्ण_अगर

#घोषणा IA64_FIRST_STACKED_GR	32
#घोषणा IA64_FIRST_ROTATING_FR	32
#घोषणा SIGN_EXT9		0xffffffffffffff00ul

/*
 *  sysctl settable hook which tells the kernel whether to honor the
 *  IA64_THREAD_UAC_NOPRINT prctl.  Because this is user settable, we want
 *  to allow the super user to enable/disable this क्रम security reasons
 *  (i.e. करोn't allow attacker to fill up logs with unaligned accesses).
 */
पूर्णांक no_unaligned_warning;
पूर्णांक unaligned_dump_stack;

/*
 * For M-unit:
 *
 *  opcode |   m  |   x6    |
 * --------|------|---------|
 * [40-37] | [36] | [35:30] |
 * --------|------|---------|
 *     4   |   1  |    6    | = 11 bits
 * --------------------------
 * However bits [31:30] are not directly useful to distinguish between
 * load/store so we can use [35:32] instead, which gives the following
 * mask ([40:32]) using 9 bits. The 'e' comes from the fact that we defer
 * checking the m-bit until later in the load/store emulation.
 */
#घोषणा IA64_OPCODE_MASK	0x1ef
#घोषणा IA64_OPCODE_SHIFT	32

/*
 * Table C-28 Integer Load/Store
 *
 * We ignore [35:32]= 0x6, 0x7, 0xE, 0xF
 *
 * ld8.fill, st8.fill  MUST be aligned because the RNATs are based on
 * the address (bits [8:3]), so we must failed.
 */
#घोषणा LD_OP            0x080
#घोषणा LDS_OP           0x081
#घोषणा LDA_OP           0x082
#घोषणा LDSA_OP          0x083
#घोषणा LDBIAS_OP        0x084
#घोषणा LDACQ_OP         0x085
/* 0x086, 0x087 are not relevant */
#घोषणा LDCCLR_OP        0x088
#घोषणा LDCNC_OP         0x089
#घोषणा LDCCLRACQ_OP     0x08a
#घोषणा ST_OP            0x08c
#घोषणा STREL_OP         0x08d
/* 0x08e,0x8f are not relevant */

/*
 * Table C-29 Integer Load +Reg
 *
 * we use the ld->m (bit [36:36]) field to determine whether or not we have
 * a load/store of this क्रमm.
 */

/*
 * Table C-30 Integer Load/Store +Imm
 *
 * We ignore [35:32]= 0x6, 0x7, 0xE, 0xF
 *
 * ld8.fill, st8.fill  must be aligned because the Nat रेजिस्टर are based on
 * the address, so we must fail and the program must be fixed.
 */
#घोषणा LD_IMM_OP            0x0a0
#घोषणा LDS_IMM_OP           0x0a1
#घोषणा LDA_IMM_OP           0x0a2
#घोषणा LDSA_IMM_OP          0x0a3
#घोषणा LDBIAS_IMM_OP        0x0a4
#घोषणा LDACQ_IMM_OP         0x0a5
/* 0x0a6, 0xa7 are not relevant */
#घोषणा LDCCLR_IMM_OP        0x0a8
#घोषणा LDCNC_IMM_OP         0x0a9
#घोषणा LDCCLRACQ_IMM_OP     0x0aa
#घोषणा ST_IMM_OP            0x0ac
#घोषणा STREL_IMM_OP         0x0ad
/* 0x0ae,0xaf are not relevant */

/*
 * Table C-32 Floating-poपूर्णांक Load/Store
 */
#घोषणा LDF_OP           0x0c0
#घोषणा LDFS_OP          0x0c1
#घोषणा LDFA_OP          0x0c2
#घोषणा LDFSA_OP         0x0c3
/* 0x0c6 is irrelevant */
#घोषणा LDFCCLR_OP       0x0c8
#घोषणा LDFCNC_OP        0x0c9
/* 0x0cb is irrelevant  */
#घोषणा STF_OP           0x0cc

/*
 * Table C-33 Floating-poपूर्णांक Load +Reg
 *
 * we use the ld->m (bit [36:36]) field to determine whether or not we have
 * a load/store of this क्रमm.
 */

/*
 * Table C-34 Floating-poपूर्णांक Load/Store +Imm
 */
#घोषणा LDF_IMM_OP       0x0e0
#घोषणा LDFS_IMM_OP      0x0e1
#घोषणा LDFA_IMM_OP      0x0e2
#घोषणा LDFSA_IMM_OP     0x0e3
/* 0x0e6 is irrelevant */
#घोषणा LDFCCLR_IMM_OP   0x0e8
#घोषणा LDFCNC_IMM_OP    0x0e9
#घोषणा STF_IMM_OP       0x0ec

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ	 qp:6;	/* [0:5]   */
	अचिन्हित दीर्घ    r1:7;	/* [6:12]  */
	अचिन्हित दीर्घ   imm:7;	/* [13:19] */
	अचिन्हित दीर्घ    r3:7;	/* [20:26] */
	अचिन्हित दीर्घ     x:1;  /* [27:27] */
	अचिन्हित दीर्घ  hपूर्णांक:2;	/* [28:29] */
	अचिन्हित दीर्घ x6_sz:2;	/* [30:31] */
	अचिन्हित दीर्घ x6_op:4;	/* [32:35], x6 = x6_sz|x6_op */
	अचिन्हित दीर्घ     m:1;	/* [36:36] */
	अचिन्हित दीर्घ    op:4;	/* [37:40] */
	अचिन्हित दीर्घ   pad:23; /* [41:63] */
पूर्ण load_store_t;


प्रकार क्रमागत अणु
	UPD_IMMEDIATE,	/* ldXZ r1=[r3],imm(9) */
	UPD_REG		/* ldXZ r1=[r3],r2     */
पूर्ण update_t;

/*
 * We use tables to keep track of the offsets of रेजिस्टरs in the saved state.
 * This way we save having big चयन/हाल statements.
 *
 * We use bit 0 to indicate चयन_stack or pt_regs.
 * The offset is simply shअगरted by 1 bit.
 * A 2-byte value should be enough to hold any kind of offset
 *
 * In हाल the calling convention changes (and thus pt_regs/चयन_stack)
 * simply use RSW instead of RPT or vice-versa.
 */

#घोषणा RPO(x)	((माप_प्रकार) &((काष्ठा pt_regs *)0)->x)
#घोषणा RSO(x)	((माप_प्रकार) &((काष्ठा चयन_stack *)0)->x)

#घोषणा RPT(x)		(RPO(x) << 1)
#घोषणा RSW(x)		(1| RSO(x)<<1)

#घोषणा GR_OFFS(x)	(gr_info[x]>>1)
#घोषणा GR_IN_SW(x)	(gr_info[x] & 0x1)

#घोषणा FR_OFFS(x)	(fr_info[x]>>1)
#घोषणा FR_IN_SW(x)	(fr_info[x] & 0x1)

अटल u16 gr_info[32]=अणु
	0,			/* r0 is पढ़ो-only : WE SHOULD NEVER GET THIS */

	RPT(r1), RPT(r2), RPT(r3),

	RSW(r4), RSW(r5), RSW(r6), RSW(r7),

	RPT(r8), RPT(r9), RPT(r10), RPT(r11),
	RPT(r12), RPT(r13), RPT(r14), RPT(r15),

	RPT(r16), RPT(r17), RPT(r18), RPT(r19),
	RPT(r20), RPT(r21), RPT(r22), RPT(r23),
	RPT(r24), RPT(r25), RPT(r26), RPT(r27),
	RPT(r28), RPT(r29), RPT(r30), RPT(r31)
पूर्ण;

अटल u16 fr_info[32]=अणु
	0,			/* स्थिरant : WE SHOULD NEVER GET THIS */
	0,			/* स्थिरant : WE SHOULD NEVER GET THIS */

	RSW(f2), RSW(f3), RSW(f4), RSW(f5),

	RPT(f6), RPT(f7), RPT(f8), RPT(f9),
	RPT(f10), RPT(f11),

	RSW(f12), RSW(f13), RSW(f14),
	RSW(f15), RSW(f16), RSW(f17), RSW(f18), RSW(f19),
	RSW(f20), RSW(f21), RSW(f22), RSW(f23), RSW(f24),
	RSW(f25), RSW(f26), RSW(f27), RSW(f28), RSW(f29),
	RSW(f30), RSW(f31)
पूर्ण;

/* Invalidate ALAT entry क्रम पूर्णांकeger रेजिस्टर REGNO.  */
अटल व्योम
invala_gr (पूर्णांक regno)
अणु
#	define F(reg)	हाल reg: ia64_invala_gr(reg); अवरोध

	चयन (regno) अणु
		F(  0); F(  1); F(  2); F(  3); F(  4); F(  5); F(  6); F(  7);
		F(  8); F(  9); F( 10); F( 11); F( 12); F( 13); F( 14); F( 15);
		F( 16); F( 17); F( 18); F( 19); F( 20); F( 21); F( 22); F( 23);
		F( 24); F( 25); F( 26); F( 27); F( 28); F( 29); F( 30); F( 31);
		F( 32); F( 33); F( 34); F( 35); F( 36); F( 37); F( 38); F( 39);
		F( 40); F( 41); F( 42); F( 43); F( 44); F( 45); F( 46); F( 47);
		F( 48); F( 49); F( 50); F( 51); F( 52); F( 53); F( 54); F( 55);
		F( 56); F( 57); F( 58); F( 59); F( 60); F( 61); F( 62); F( 63);
		F( 64); F( 65); F( 66); F( 67); F( 68); F( 69); F( 70); F( 71);
		F( 72); F( 73); F( 74); F( 75); F( 76); F( 77); F( 78); F( 79);
		F( 80); F( 81); F( 82); F( 83); F( 84); F( 85); F( 86); F( 87);
		F( 88); F( 89); F( 90); F( 91); F( 92); F( 93); F( 94); F( 95);
		F( 96); F( 97); F( 98); F( 99); F(100); F(101); F(102); F(103);
		F(104); F(105); F(106); F(107); F(108); F(109); F(110); F(111);
		F(112); F(113); F(114); F(115); F(116); F(117); F(118); F(119);
		F(120); F(121); F(122); F(123); F(124); F(125); F(126); F(127);
	पूर्ण
#	undef F
पूर्ण

/* Invalidate ALAT entry क्रम भग्नing-poपूर्णांक रेजिस्टर REGNO.  */
अटल व्योम
invala_fr (पूर्णांक regno)
अणु
#	define F(reg)	हाल reg: ia64_invala_fr(reg); अवरोध

	चयन (regno) अणु
		F(  0); F(  1); F(  2); F(  3); F(  4); F(  5); F(  6); F(  7);
		F(  8); F(  9); F( 10); F( 11); F( 12); F( 13); F( 14); F( 15);
		F( 16); F( 17); F( 18); F( 19); F( 20); F( 21); F( 22); F( 23);
		F( 24); F( 25); F( 26); F( 27); F( 28); F( 29); F( 30); F( 31);
		F( 32); F( 33); F( 34); F( 35); F( 36); F( 37); F( 38); F( 39);
		F( 40); F( 41); F( 42); F( 43); F( 44); F( 45); F( 46); F( 47);
		F( 48); F( 49); F( 50); F( 51); F( 52); F( 53); F( 54); F( 55);
		F( 56); F( 57); F( 58); F( 59); F( 60); F( 61); F( 62); F( 63);
		F( 64); F( 65); F( 66); F( 67); F( 68); F( 69); F( 70); F( 71);
		F( 72); F( 73); F( 74); F( 75); F( 76); F( 77); F( 78); F( 79);
		F( 80); F( 81); F( 82); F( 83); F( 84); F( 85); F( 86); F( 87);
		F( 88); F( 89); F( 90); F( 91); F( 92); F( 93); F( 94); F( 95);
		F( 96); F( 97); F( 98); F( 99); F(100); F(101); F(102); F(103);
		F(104); F(105); F(106); F(107); F(108); F(109); F(110); F(111);
		F(112); F(113); F(114); F(115); F(116); F(117); F(118); F(119);
		F(120); F(121); F(122); F(123); F(124); F(125); F(126); F(127);
	पूर्ण
#	undef F
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
rotate_reg (अचिन्हित दीर्घ sor, अचिन्हित दीर्घ rrb, अचिन्हित दीर्घ reg)
अणु
	reg += rrb;
	अगर (reg >= sor)
		reg -= sor;
	वापस reg;
पूर्ण

अटल व्योम
set_rse_reg (काष्ठा pt_regs *regs, अचिन्हित दीर्घ r1, अचिन्हित दीर्घ val, पूर्णांक nat)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *) regs - 1;
	अचिन्हित दीर्घ *bsp, *bspstore, *addr, *rnat_addr, *ubs_end;
	अचिन्हित दीर्घ *kbs = (व्योम *) current + IA64_RBS_OFFSET;
	अचिन्हित दीर्घ rnats, nat_mask;
	अचिन्हित दीर्घ on_kbs;
	दीर्घ sof = (regs->cr_अगरs) & 0x7f;
	दीर्घ sor = 8 * ((regs->cr_अगरs >> 14) & 0xf);
	दीर्घ rrb_gr = (regs->cr_अगरs >> 18) & 0x7f;
	दीर्घ ridx = r1 - 32;

	अगर (ridx >= sof) अणु
		/* this should never happen, as the "rsvd register fault" has higher priority */
		DPRINT("ignoring write to r%lu; only %lu registers are allocated!\n", r1, sof);
		वापस;
	पूर्ण

	अगर (ridx < sor)
		ridx = rotate_reg(sor, rrb_gr, ridx);

	DPRINT("r%lu, sw.bspstore=%lx pt.bspstore=%lx sof=%ld sol=%ld ridx=%ld\n",
	       r1, sw->ar_bspstore, regs->ar_bspstore, sof, (regs->cr_अगरs >> 7) & 0x7f, ridx);

	on_kbs = ia64_rse_num_regs(kbs, (अचिन्हित दीर्घ *) sw->ar_bspstore);
	addr = ia64_rse_skip_regs((अचिन्हित दीर्घ *) sw->ar_bspstore, -sof + ridx);
	अगर (addr >= kbs) अणु
		/* the रेजिस्टर is on the kernel backing store: easy... */
		rnat_addr = ia64_rse_rnat_addr(addr);
		अगर ((अचिन्हित दीर्घ) rnat_addr >= sw->ar_bspstore)
			rnat_addr = &sw->ar_rnat;
		nat_mask = 1UL << ia64_rse_slot_num(addr);

		*addr = val;
		अगर (nat)
			*rnat_addr |=  nat_mask;
		अन्यथा
			*rnat_addr &= ~nat_mask;
		वापस;
	पूर्ण

	अगर (!user_stack(current, regs)) अणु
		DPRINT("ignoring kernel write to r%lu; register isn't on the kernel RBS!", r1);
		वापस;
	पूर्ण

	bspstore = (अचिन्हित दीर्घ *)regs->ar_bspstore;
	ubs_end = ia64_rse_skip_regs(bspstore, on_kbs);
	bsp     = ia64_rse_skip_regs(ubs_end, -sof);
	addr    = ia64_rse_skip_regs(bsp, ridx);

	DPRINT("ubs_end=%p bsp=%p addr=%p\n", (व्योम *) ubs_end, (व्योम *) bsp, (व्योम *) addr);

	ia64_poke(current, sw, (अचिन्हित दीर्घ) ubs_end, (अचिन्हित दीर्घ) addr, val);

	rnat_addr = ia64_rse_rnat_addr(addr);

	ia64_peek(current, sw, (अचिन्हित दीर्घ) ubs_end, (अचिन्हित दीर्घ) rnat_addr, &rnats);
	DPRINT("rnat @%p = 0x%lx nat=%d old nat=%ld\n",
	       (व्योम *) rnat_addr, rnats, nat, (rnats >> ia64_rse_slot_num(addr)) & 1);

	nat_mask = 1UL << ia64_rse_slot_num(addr);
	अगर (nat)
		rnats |=  nat_mask;
	अन्यथा
		rnats &= ~nat_mask;
	ia64_poke(current, sw, (अचिन्हित दीर्घ) ubs_end, (अचिन्हित दीर्घ) rnat_addr, rnats);

	DPRINT("rnat changed to @%p = 0x%lx\n", (व्योम *) rnat_addr, rnats);
पूर्ण


अटल व्योम
get_rse_reg (काष्ठा pt_regs *regs, अचिन्हित दीर्घ r1, अचिन्हित दीर्घ *val, पूर्णांक *nat)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *) regs - 1;
	अचिन्हित दीर्घ *bsp, *addr, *rnat_addr, *ubs_end, *bspstore;
	अचिन्हित दीर्घ *kbs = (व्योम *) current + IA64_RBS_OFFSET;
	अचिन्हित दीर्घ rnats, nat_mask;
	अचिन्हित दीर्घ on_kbs;
	दीर्घ sof = (regs->cr_अगरs) & 0x7f;
	दीर्घ sor = 8 * ((regs->cr_अगरs >> 14) & 0xf);
	दीर्घ rrb_gr = (regs->cr_अगरs >> 18) & 0x7f;
	दीर्घ ridx = r1 - 32;

	अगर (ridx >= sof) अणु
		/* पढ़ो of out-of-frame रेजिस्टर वापसs an undefined value; 0 in our हाल.  */
		DPRINT("ignoring read from r%lu; only %lu registers are allocated!\n", r1, sof);
		जाओ fail;
	पूर्ण

	अगर (ridx < sor)
		ridx = rotate_reg(sor, rrb_gr, ridx);

	DPRINT("r%lu, sw.bspstore=%lx pt.bspstore=%lx sof=%ld sol=%ld ridx=%ld\n",
	       r1, sw->ar_bspstore, regs->ar_bspstore, sof, (regs->cr_अगरs >> 7) & 0x7f, ridx);

	on_kbs = ia64_rse_num_regs(kbs, (अचिन्हित दीर्घ *) sw->ar_bspstore);
	addr = ia64_rse_skip_regs((अचिन्हित दीर्घ *) sw->ar_bspstore, -sof + ridx);
	अगर (addr >= kbs) अणु
		/* the रेजिस्टर is on the kernel backing store: easy... */
		*val = *addr;
		अगर (nat) अणु
			rnat_addr = ia64_rse_rnat_addr(addr);
			अगर ((अचिन्हित दीर्घ) rnat_addr >= sw->ar_bspstore)
				rnat_addr = &sw->ar_rnat;
			nat_mask = 1UL << ia64_rse_slot_num(addr);
			*nat = (*rnat_addr & nat_mask) != 0;
		पूर्ण
		वापस;
	पूर्ण

	अगर (!user_stack(current, regs)) अणु
		DPRINT("ignoring kernel read of r%lu; register isn't on the RBS!", r1);
		जाओ fail;
	पूर्ण

	bspstore = (अचिन्हित दीर्घ *)regs->ar_bspstore;
	ubs_end = ia64_rse_skip_regs(bspstore, on_kbs);
	bsp     = ia64_rse_skip_regs(ubs_end, -sof);
	addr    = ia64_rse_skip_regs(bsp, ridx);

	DPRINT("ubs_end=%p bsp=%p addr=%p\n", (व्योम *) ubs_end, (व्योम *) bsp, (व्योम *) addr);

	ia64_peek(current, sw, (अचिन्हित दीर्घ) ubs_end, (अचिन्हित दीर्घ) addr, val);

	अगर (nat) अणु
		rnat_addr = ia64_rse_rnat_addr(addr);
		nat_mask = 1UL << ia64_rse_slot_num(addr);

		DPRINT("rnat @%p = 0x%lx\n", (व्योम *) rnat_addr, rnats);

		ia64_peek(current, sw, (अचिन्हित दीर्घ) ubs_end, (अचिन्हित दीर्घ) rnat_addr, &rnats);
		*nat = (rnats & nat_mask) != 0;
	पूर्ण
	वापस;

  fail:
	*val = 0;
	अगर (nat)
		*nat = 0;
	वापस;
पूर्ण


अटल व्योम
setreg (अचिन्हित दीर्घ regnum, अचिन्हित दीर्घ val, पूर्णांक nat, काष्ठा pt_regs *regs)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *) regs - 1;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ biपंचांगask;
	अचिन्हित दीर्घ *unat;

	/*
	 * First takes care of stacked रेजिस्टरs
	 */
	अगर (regnum >= IA64_FIRST_STACKED_GR) अणु
		set_rse_reg(regs, regnum, val, nat);
		वापस;
	पूर्ण

	/*
	 * Using r0 as a target उठाओs a General Exception fault which has higher priority
	 * than the Unaligned Reference fault.
	 */

	/*
	 * Now look at रेजिस्टरs in [0-31] range and init correct UNAT
	 */
	अगर (GR_IN_SW(regnum)) अणु
		addr = (अचिन्हित दीर्घ)sw;
		unat = &sw->ar_unat;
	पूर्ण अन्यथा अणु
		addr = (अचिन्हित दीर्घ)regs;
		unat = &sw->caller_unat;
	पूर्ण
	DPRINT("tmp_base=%lx switch_stack=%s offset=%d\n",
	       addr, unat==&sw->ar_unat ? "yes":"no", GR_OFFS(regnum));
	/*
	 * add offset from base of काष्ठा
	 * and करो it !
	 */
	addr += GR_OFFS(regnum);

	*(अचिन्हित दीर्घ *)addr = val;

	/*
	 * We need to clear the corresponding UNAT bit to fully emulate the load
	 * UNAT bit_pos = GR[r3]अणु8:3पूर्ण क्रमm EAS-2.4
	 */
	biपंचांगask   = 1UL << (addr >> 3 & 0x3f);
	DPRINT("*0x%lx=0x%lx NaT=%d prev_unat @%p=%lx\n", addr, val, nat, (व्योम *) unat, *unat);
	अगर (nat) अणु
		*unat |= biपंचांगask;
	पूर्ण अन्यथा अणु
		*unat &= ~biपंचांगask;
	पूर्ण
	DPRINT("*0x%lx=0x%lx NaT=%d new unat: %p=%lx\n", addr, val, nat, (व्योम *) unat,*unat);
पूर्ण

/*
 * Return the (rotated) index क्रम भग्नing poपूर्णांक रेजिस्टर REGNUM (REGNUM must be in the
 * range from 32-127, result is in the range from 0-95.
 */
अटल अंतरभूत अचिन्हित दीर्घ
fph_index (काष्ठा pt_regs *regs, दीर्घ regnum)
अणु
	अचिन्हित दीर्घ rrb_fr = (regs->cr_अगरs >> 25) & 0x7f;
	वापस rotate_reg(96, rrb_fr, (regnum - IA64_FIRST_ROTATING_FR));
पूर्ण

अटल व्योम
setfpreg (अचिन्हित दीर्घ regnum, काष्ठा ia64_fpreg *fpval, काष्ठा pt_regs *regs)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)regs - 1;
	अचिन्हित दीर्घ addr;

	/*
	 * From EAS-2.5: FPDisableFault has higher priority than Unaligned
	 * Fault. Thus, when we get here, we know the partition is enabled.
	 * To update f32-f127, there are three choices:
	 *
	 *	(1) save f32-f127 to thपढ़ो.fph and update the values there
	 *	(2) use a gigantic चयन statement to directly access the रेजिस्टरs
	 *	(3) generate code on the fly to update the desired रेजिस्टर
	 *
	 * For now, we are using approach (1).
	 */
	अगर (regnum >= IA64_FIRST_ROTATING_FR) अणु
		ia64_sync_fph(current);
		current->thपढ़ो.fph[fph_index(regs, regnum)] = *fpval;
	पूर्ण अन्यथा अणु
		/*
		 * pt_regs or चयन_stack ?
		 */
		अगर (FR_IN_SW(regnum)) अणु
			addr = (अचिन्हित दीर्घ)sw;
		पूर्ण अन्यथा अणु
			addr = (अचिन्हित दीर्घ)regs;
		पूर्ण

		DPRINT("tmp_base=%lx offset=%d\n", addr, FR_OFFS(regnum));

		addr += FR_OFFS(regnum);
		*(काष्ठा ia64_fpreg *)addr = *fpval;

		/*
		 * mark the low partition as being used now
		 *
		 * It is highly unlikely that this bit is not alपढ़ोy set, but
		 * let's करो it क्रम safety.
		 */
		regs->cr_ipsr |= IA64_PSR_MFL;
	पूर्ण
पूर्ण

/*
 * Those 2 अंतरभूत functions generate the spilled versions of the स्थिरant भग्नing poपूर्णांक
 * रेजिस्टरs which can be used with stfX
 */
अटल अंतरभूत व्योम
भग्न_spill_f0 (काष्ठा ia64_fpreg *final)
अणु
	ia64_stf_spill(final, 0);
पूर्ण

अटल अंतरभूत व्योम
भग्न_spill_f1 (काष्ठा ia64_fpreg *final)
अणु
	ia64_stf_spill(final, 1);
पूर्ण

अटल व्योम
getfpreg (अचिन्हित दीर्घ regnum, काष्ठा ia64_fpreg *fpval, काष्ठा pt_regs *regs)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *) regs - 1;
	अचिन्हित दीर्घ addr;

	/*
	 * From EAS-2.5: FPDisableFault has higher priority than
	 * Unaligned Fault. Thus, when we get here, we know the partition is
	 * enabled.
	 *
	 * When regnum > 31, the रेजिस्टर is still live and we need to क्रमce a save
	 * to current->thपढ़ो.fph to get access to it.  See discussion in setfpreg()
	 * क्रम reasons and other ways of करोing this.
	 */
	अगर (regnum >= IA64_FIRST_ROTATING_FR) अणु
		ia64_flush_fph(current);
		*fpval = current->thपढ़ो.fph[fph_index(regs, regnum)];
	पूर्ण अन्यथा अणु
		/*
		 * f0 = 0.0, f1= 1.0. Those रेजिस्टरs are स्थिरant and are thus
		 * not saved, we must generate their spilled क्रमm on the fly
		 */
		चयन(regnum) अणु
		हाल 0:
			भग्न_spill_f0(fpval);
			अवरोध;
		हाल 1:
			भग्न_spill_f1(fpval);
			अवरोध;
		शेष:
			/*
			 * pt_regs or चयन_stack ?
			 */
			addr =  FR_IN_SW(regnum) ? (अचिन्हित दीर्घ)sw
						 : (अचिन्हित दीर्घ)regs;

			DPRINT("is_sw=%d tmp_base=%lx offset=0x%x\n",
			       FR_IN_SW(regnum), addr, FR_OFFS(regnum));

			addr  += FR_OFFS(regnum);
			*fpval = *(काष्ठा ia64_fpreg *)addr;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम
getreg (अचिन्हित दीर्घ regnum, अचिन्हित दीर्घ *val, पूर्णांक *nat, काष्ठा pt_regs *regs)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *) regs - 1;
	अचिन्हित दीर्घ addr, *unat;

	अगर (regnum >= IA64_FIRST_STACKED_GR) अणु
		get_rse_reg(regs, regnum, val, nat);
		वापस;
	पूर्ण

	/*
	 * take care of r0 (पढ़ो-only always evaluate to 0)
	 */
	अगर (regnum == 0) अणु
		*val = 0;
		अगर (nat)
			*nat = 0;
		वापस;
	पूर्ण

	/*
	 * Now look at रेजिस्टरs in [0-31] range and init correct UNAT
	 */
	अगर (GR_IN_SW(regnum)) अणु
		addr = (अचिन्हित दीर्घ)sw;
		unat = &sw->ar_unat;
	पूर्ण अन्यथा अणु
		addr = (अचिन्हित दीर्घ)regs;
		unat = &sw->caller_unat;
	पूर्ण

	DPRINT("addr_base=%lx offset=0x%x\n", addr,  GR_OFFS(regnum));

	addr += GR_OFFS(regnum);

	*val  = *(अचिन्हित दीर्घ *)addr;

	/*
	 * करो it only when requested
	 */
	अगर (nat)
		*nat  = (*unat >> (addr >> 3 & 0x3f)) & 0x1UL;
पूर्ण

अटल व्योम
emulate_load_updates (update_t type, load_store_t ld, काष्ठा pt_regs *regs, अचिन्हित दीर्घ अगरa)
अणु
	/*
	 * IMPORTANT:
	 * Given the way we handle unaligned speculative loads, we should
	 * not get to this poपूर्णांक in the code but we keep this sanity check,
	 * just in हाल.
	 */
	अगर (ld.x6_op == 1 || ld.x6_op == 3) अणु
		prपूर्णांकk(KERN_ERR "%s: register update on speculative load, error\n", __func__);
		अगर (die_अगर_kernel("unaligned reference on speculative load with register update\n",
				  regs, 30))
			वापस;
	पूर्ण


	/*
	 * at this poपूर्णांक, we know that the base रेजिस्टर to update is valid i.e.,
	 * it's not r0
	 */
	अगर (type == UPD_IMMEDIATE) अणु
		अचिन्हित दीर्घ imm;

		/*
		 * Load +Imm: ldXZ r1=[r3],imm(9)
		 *
		 *
		 * क्रमm imm9: [13:19] contain the first 7 bits
		 */
		imm = ld.x << 7 | ld.imm;

		/*
		 * sign extend (1+8bits) अगर m set
		 */
		अगर (ld.m) imm |= SIGN_EXT9;

		/*
		 * अगरa == r3 and we know that the NaT bit on r3 was clear so
		 * we can directly use अगरa.
		 */
		अगरa += imm;

		setreg(ld.r3, अगरa, 0, regs);

		DPRINT("ld.x=%d ld.m=%d imm=%ld r3=0x%lx\n", ld.x, ld.m, imm, अगरa);

	पूर्ण अन्यथा अगर (ld.m) अणु
		अचिन्हित दीर्घ r2;
		पूर्णांक nat_r2;

		/*
		 * Load +Reg Opcode: ldXZ r1=[r3],r2
		 *
		 * Note: that we update r3 even in the हाल of ldfX.a
		 * (where the load करोes not happen)
		 *
		 * The way the load algorithm works, we know that r3 करोes not
		 * have its NaT bit set (would have gotten NaT consumption
		 * beक्रमe getting the unaligned fault). So we can use अगरa
		 * which equals r3 at this poपूर्णांक.
		 *
		 * IMPORTANT:
		 * The above statement holds ONLY because we know that we
		 * never reach this code when trying to करो a ldX.s.
		 * If we ever make it to here on an ldfX.s then
		 */
		getreg(ld.imm, &r2, &nat_r2, regs);

		अगरa += r2;

		/*
		 * propagate Nat r2 -> r3
		 */
		setreg(ld.r3, अगरa, nat_r2, regs);

		DPRINT("imm=%d r2=%ld r3=0x%lx nat_r2=%d\n",ld.imm, r2, अगरa, nat_r2);
	पूर्ण
पूर्ण


अटल पूर्णांक
emulate_load_पूर्णांक (अचिन्हित दीर्घ अगरa, load_store_t ld, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक len = 1 << ld.x6_sz;
	अचिन्हित दीर्घ val = 0;

	/*
	 * r0, as target, करोesn't need to be checked because Illegal Inकाष्ठाion
	 * faults have higher priority than unaligned faults.
	 *
	 * r0 cannot be found as the base as it would never generate an
	 * unaligned reference.
	 */

	/*
	 * ldX.a we will emulate load and also invalidate the ALAT entry.
	 * See comment below क्रम explanation on how we handle ldX.a
	 */

	अगर (len != 2 && len != 4 && len != 8) अणु
		DPRINT("unknown size: x6=%d\n", ld.x6_sz);
		वापस -1;
	पूर्ण
	/* this assumes little-endian byte-order: */
	अगर (copy_from_user(&val, (व्योम __user *) अगरa, len))
		वापस -1;
	setreg(ld.r1, val, 0, regs);

	/*
	 * check क्रम updates on any kind of loads
	 */
	अगर (ld.op == 0x5 || ld.m)
		emulate_load_updates(ld.op == 0x5 ? UPD_IMMEDIATE: UPD_REG, ld, regs, अगरa);

	/*
	 * handling of various loads (based on EAS2.4):
	 *
	 * ldX.acq (ordered load):
	 *	- acquire semantics would have been used, so क्रमce fence instead.
	 *
	 * ldX.c.clr (check load and clear):
	 *	- अगर we get to this handler, it's because the entry was not in the ALAT.
	 *	  Thereक्रमe the operation reverts to a normal load
	 *
	 * ldX.c.nc (check load no clear):
	 *	- same as previous one
	 *
	 * ldX.c.clr.acq (ordered check load and clear):
	 *	- same as above क्रम c.clr part. The load needs to have acquire semantics. So
	 *	  we use the fence semantics which is stronger and thus ensures correctness.
	 *
	 * ldX.a (advanced load):
	 *	- suppose ldX.a r1=[r3]. If we get to the unaligned trap it's because the
	 *	  address करोesn't match requested size alignment. This means that we would
	 *	  possibly need more than one load to get the result.
	 *
	 *	  The load part can be handled just like a normal load, however the dअगरficult
	 *	  part is to get the right thing पूर्णांकo the ALAT. The critical piece of inक्रमmation
	 *	  in the base address of the load & size. To करो that, a ld.a must be executed,
	 *	  clearly any address can be pushed पूर्णांकo the table by using ld1.a r1=[r3]. Now
	 *	  अगर we use the same target रेजिस्टर, we will be okay क्रम the check.a inकाष्ठाion.
	 *	  If we look at the store, basically a stX [r3]=r1 checks the ALAT  क्रम any entry
	 *	  which would overlap within [r3,r3+X] (the size of the load was store in the
	 *	  ALAT). If such an entry is found the entry is invalidated. But this is not good
	 *	  enough, take the following example:
	 *		r3=3
	 *		ld4.a r1=[r3]
	 *
	 *	  Could be emulated by करोing:
	 *		ld1.a r1=[r3],1
	 *		store to temporary;
	 *		ld1.a r1=[r3],1
	 *		store & shअगरt to temporary;
	 *		ld1.a r1=[r3],1
	 *		store & shअगरt to temporary;
	 *		ld1.a r1=[r3]
	 *		store & shअगरt to temporary;
	 *		r1=temporary
	 *
	 *	  So in this हाल, you would get the right value is r1 but the wrong info in
	 *	  the ALAT.  Notice that you could करो it in reverse to finish with address 3
	 *	  but you would still get the size wrong.  To get the size right, one needs to
	 *	  execute exactly the same kind of load. You could करो it from a aligned
	 *	  temporary location, but you would get the address wrong.
	 *
	 *	  So no matter what, it is not possible to emulate an advanced load
	 *	  correctly. But is that really critical ?
	 *
	 *	  We will always convert ld.a पूर्णांकo a normal load with ALAT invalidated.  This
	 *	  will enable compiler to करो optimization where certain code path after ld.a
	 *	  is not required to have ld.c/chk.a, e.g., code path with no पूर्णांकervening stores.
	 *
	 *	  If there is a store after the advanced load, one must either करो a ld.c.* or
	 *	  chk.a.* to reuse the value stored in the ALAT. Both can "fail" (meaning no
	 *	  entry found in ALAT), and that's perfectly ok because:
	 *
	 *		- ld.c.*, अगर the entry is not present a  normal load is executed
	 *		- chk.a.*, अगर the entry is not present, execution jumps to recovery code
	 *
	 *	  In either हाल, the load can be potentially retried in another क्रमm.
	 *
	 *	  ALAT must be invalidated क्रम the रेजिस्टर (so that chk.a or ld.c करोn't pick
	 *	  up a stale entry later). The रेजिस्टर base update MUST also be perक्रमmed.
	 */

	/*
	 * when the load has the .acq completer then
	 * use ordering fence.
	 */
	अगर (ld.x6_op == 0x5 || ld.x6_op == 0xa)
		mb();

	/*
	 * invalidate ALAT entry in हाल of advanced load
	 */
	अगर (ld.x6_op == 0x2)
		invala_gr(ld.r1);

	वापस 0;
पूर्ण

अटल पूर्णांक
emulate_store_पूर्णांक (अचिन्हित दीर्घ अगरa, load_store_t ld, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ r2;
	अचिन्हित पूर्णांक len = 1 << ld.x6_sz;

	/*
	 * अगर we get to this handler, Nat bits on both r3 and r2 have alपढ़ोy
	 * been checked. so we करोn't need to करो it
	 *
	 * extract the value to be stored
	 */
	getreg(ld.imm, &r2, शून्य, regs);

	/*
	 * we rely on the macros in unaligned.h क्रम now i.e.,
	 * we let the compiler figure out how to पढ़ो memory gracefully.
	 *
	 * We need this चयन/हाल because the way the अंतरभूत function
	 * works. The code is optimized by the compiler and looks like
	 * a single चयन/हाल.
	 */
	DPRINT("st%d [%lx]=%lx\n", len, अगरa, r2);

	अगर (len != 2 && len != 4 && len != 8) अणु
		DPRINT("unknown size: x6=%d\n", ld.x6_sz);
		वापस -1;
	पूर्ण

	/* this assumes little-endian byte-order: */
	अगर (copy_to_user((व्योम __user *) अगरa, &r2, len))
		वापस -1;

	/*
	 * stX [r3]=r2,imm(9)
	 *
	 * NOTE:
	 * ld.r3 can never be r0, because r0 would not generate an
	 * unaligned access.
	 */
	अगर (ld.op == 0x5) अणु
		अचिन्हित दीर्घ imm;

		/*
		 * क्रमm imm9: [12:6] contain first 7bits
		 */
		imm = ld.x << 7 | ld.r1;
		/*
		 * sign extend (8bits) अगर m set
		 */
		अगर (ld.m) imm |= SIGN_EXT9;
		/*
		 * अगरa == r3 (NaT is necessarily cleared)
		 */
		अगरa += imm;

		DPRINT("imm=%lx r3=%lx\n", imm, अगरa);

		setreg(ld.r3, अगरa, 0, regs);
	पूर्ण
	/*
	 * we करोn't have alat_invalidate_multiple() so we need
	 * to करो the complete flush :-<<
	 */
	ia64_invala();

	/*
	 * stX.rel: use fence instead of release
	 */
	अगर (ld.x6_op == 0xd)
		mb();

	वापस 0;
पूर्ण

/*
 * भग्नing poपूर्णांक operations sizes in bytes
 */
अटल स्थिर अचिन्हित अक्षर भग्न_fsz[4]=अणु
	10, /* extended precision (e) */
	8,  /* पूर्णांकeger (8)            */
	4,  /* single precision (s)   */
	8   /* द्विगुन precision (d)   */
पूर्ण;

अटल अंतरभूत व्योम
mem2भग्न_extended (काष्ठा ia64_fpreg *init, काष्ठा ia64_fpreg *final)
अणु
	ia64_ldfe(6, init);
	ia64_stop();
	ia64_stf_spill(final, 6);
पूर्ण

अटल अंतरभूत व्योम
mem2भग्न_पूर्णांकeger (काष्ठा ia64_fpreg *init, काष्ठा ia64_fpreg *final)
अणु
	ia64_ldf8(6, init);
	ia64_stop();
	ia64_stf_spill(final, 6);
पूर्ण

अटल अंतरभूत व्योम
mem2भग्न_single (काष्ठा ia64_fpreg *init, काष्ठा ia64_fpreg *final)
अणु
	ia64_ldfs(6, init);
	ia64_stop();
	ia64_stf_spill(final, 6);
पूर्ण

अटल अंतरभूत व्योम
mem2भग्न_द्विगुन (काष्ठा ia64_fpreg *init, काष्ठा ia64_fpreg *final)
अणु
	ia64_ldfd(6, init);
	ia64_stop();
	ia64_stf_spill(final, 6);
पूर्ण

अटल अंतरभूत व्योम
भग्न2mem_extended (काष्ठा ia64_fpreg *init, काष्ठा ia64_fpreg *final)
अणु
	ia64_ldf_fill(6, init);
	ia64_stop();
	ia64_stfe(final, 6);
पूर्ण

अटल अंतरभूत व्योम
भग्न2mem_पूर्णांकeger (काष्ठा ia64_fpreg *init, काष्ठा ia64_fpreg *final)
अणु
	ia64_ldf_fill(6, init);
	ia64_stop();
	ia64_stf8(final, 6);
पूर्ण

अटल अंतरभूत व्योम
भग्न2mem_single (काष्ठा ia64_fpreg *init, काष्ठा ia64_fpreg *final)
अणु
	ia64_ldf_fill(6, init);
	ia64_stop();
	ia64_stfs(final, 6);
पूर्ण

अटल अंतरभूत व्योम
भग्न2mem_द्विगुन (काष्ठा ia64_fpreg *init, काष्ठा ia64_fpreg *final)
अणु
	ia64_ldf_fill(6, init);
	ia64_stop();
	ia64_stfd(final, 6);
पूर्ण

अटल पूर्णांक
emulate_load_भग्नpair (अचिन्हित दीर्घ अगरa, load_store_t ld, काष्ठा pt_regs *regs)
अणु
	काष्ठा ia64_fpreg fpr_init[2];
	काष्ठा ia64_fpreg fpr_final[2];
	अचिन्हित दीर्घ len = भग्न_fsz[ld.x6_sz];

	/*
	 * fr0 & fr1 करोn't need to be checked because Illegal Inकाष्ठाion faults have
	 * higher priority than unaligned faults.
	 *
	 * r0 cannot be found as the base as it would never generate an unaligned
	 * reference.
	 */

	/*
	 * make sure we get clean buffers
	 */
	स_रखो(&fpr_init, 0, माप(fpr_init));
	स_रखो(&fpr_final, 0, माप(fpr_final));

	/*
	 * ldfpX.a: we करोn't try to emulate anything but we must
	 * invalidate the ALAT entry and execute updates, अगर any.
	 */
	अगर (ld.x6_op != 0x2) अणु
		/*
		 * This assumes little-endian byte-order.  Note that there is no "ldfpe"
		 * inकाष्ठाion:
		 */
		अगर (copy_from_user(&fpr_init[0], (व्योम __user *) अगरa, len)
		    || copy_from_user(&fpr_init[1], (व्योम __user *) (अगरa + len), len))
			वापस -1;

		DPRINT("ld.r1=%d ld.imm=%d x6_sz=%d\n", ld.r1, ld.imm, ld.x6_sz);
		DDUMP("frp_init =", &fpr_init, 2*len);
		/*
		 * XXX fixme
		 * Could optimize अंतरभूतs by using ldfpX & 2 spills
		 */
		चयन( ld.x6_sz ) अणु
			हाल 0:
				mem2भग्न_extended(&fpr_init[0], &fpr_final[0]);
				mem2भग्न_extended(&fpr_init[1], &fpr_final[1]);
				अवरोध;
			हाल 1:
				mem2भग्न_पूर्णांकeger(&fpr_init[0], &fpr_final[0]);
				mem2भग्न_पूर्णांकeger(&fpr_init[1], &fpr_final[1]);
				अवरोध;
			हाल 2:
				mem2भग्न_single(&fpr_init[0], &fpr_final[0]);
				mem2भग्न_single(&fpr_init[1], &fpr_final[1]);
				अवरोध;
			हाल 3:
				mem2भग्न_द्विगुन(&fpr_init[0], &fpr_final[0]);
				mem2भग्न_द्विगुन(&fpr_init[1], &fpr_final[1]);
				अवरोध;
		पूर्ण
		DDUMP("fpr_final =", &fpr_final, 2*len);
		/*
		 * XXX fixme
		 *
		 * A possible optimization would be to drop fpr_final and directly
		 * use the storage from the saved context i.e., the actual final
		 * destination (pt_regs, चयन_stack or thपढ़ो काष्ठाure).
		 */
		setfpreg(ld.r1, &fpr_final[0], regs);
		setfpreg(ld.imm, &fpr_final[1], regs);
	पूर्ण

	/*
	 * Check क्रम updates: only immediate updates are available क्रम this
	 * inकाष्ठाion.
	 */
	अगर (ld.m) अणु
		/*
		 * the immediate is implicit given the ldsz of the operation:
		 * single: 8 (2x4) and क्रम  all others it's 16 (2x8)
		 */
		अगरa += len<<1;

		/*
		 * IMPORTANT:
		 * the fact that we क्रमce the NaT of r3 to zero is ONLY valid
		 * as दीर्घ as we करोn't come here with a ldfpX.s.
		 * For this reason we keep this sanity check
		 */
		अगर (ld.x6_op == 1 || ld.x6_op == 3)
			prपूर्णांकk(KERN_ERR "%s: register update on speculative load pair, error\n",
			       __func__);

		setreg(ld.r3, अगरa, 0, regs);
	पूर्ण

	/*
	 * Invalidate ALAT entries, अगर any, क्रम both रेजिस्टरs.
	 */
	अगर (ld.x6_op == 0x2) अणु
		invala_fr(ld.r1);
		invala_fr(ld.imm);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक
emulate_load_भग्न (अचिन्हित दीर्घ अगरa, load_store_t ld, काष्ठा pt_regs *regs)
अणु
	काष्ठा ia64_fpreg fpr_init;
	काष्ठा ia64_fpreg fpr_final;
	अचिन्हित दीर्घ len = भग्न_fsz[ld.x6_sz];

	/*
	 * fr0 & fr1 करोn't need to be checked because Illegal Inकाष्ठाion
	 * faults have higher priority than unaligned faults.
	 *
	 * r0 cannot be found as the base as it would never generate an
	 * unaligned reference.
	 */

	/*
	 * make sure we get clean buffers
	 */
	स_रखो(&fpr_init,0, माप(fpr_init));
	स_रखो(&fpr_final,0, माप(fpr_final));

	/*
	 * ldfX.a we करोn't try to emulate anything but we must
	 * invalidate the ALAT entry.
	 * See comments in ldX क्रम descriptions on how the various loads are handled.
	 */
	अगर (ld.x6_op != 0x2) अणु
		अगर (copy_from_user(&fpr_init, (व्योम __user *) अगरa, len))
			वापस -1;

		DPRINT("ld.r1=%d x6_sz=%d\n", ld.r1, ld.x6_sz);
		DDUMP("fpr_init =", &fpr_init, len);
		/*
		 * we only करो something क्रम x6_op=अणु0,8,9पूर्ण
		 */
		चयन( ld.x6_sz ) अणु
			हाल 0:
				mem2भग्न_extended(&fpr_init, &fpr_final);
				अवरोध;
			हाल 1:
				mem2भग्न_पूर्णांकeger(&fpr_init, &fpr_final);
				अवरोध;
			हाल 2:
				mem2भग्न_single(&fpr_init, &fpr_final);
				अवरोध;
			हाल 3:
				mem2भग्न_द्विगुन(&fpr_init, &fpr_final);
				अवरोध;
		पूर्ण
		DDUMP("fpr_final =", &fpr_final, len);
		/*
		 * XXX fixme
		 *
		 * A possible optimization would be to drop fpr_final and directly
		 * use the storage from the saved context i.e., the actual final
		 * destination (pt_regs, चयन_stack or thपढ़ो काष्ठाure).
		 */
		setfpreg(ld.r1, &fpr_final, regs);
	पूर्ण

	/*
	 * check क्रम updates on any loads
	 */
	अगर (ld.op == 0x7 || ld.m)
		emulate_load_updates(ld.op == 0x7 ? UPD_IMMEDIATE: UPD_REG, ld, regs, अगरa);

	/*
	 * invalidate ALAT entry in हाल of advanced भग्नing poपूर्णांक loads
	 */
	अगर (ld.x6_op == 0x2)
		invala_fr(ld.r1);

	वापस 0;
पूर्ण


अटल पूर्णांक
emulate_store_भग्न (अचिन्हित दीर्घ अगरa, load_store_t ld, काष्ठा pt_regs *regs)
अणु
	काष्ठा ia64_fpreg fpr_init;
	काष्ठा ia64_fpreg fpr_final;
	अचिन्हित दीर्घ len = भग्न_fsz[ld.x6_sz];

	/*
	 * make sure we get clean buffers
	 */
	स_रखो(&fpr_init,0, माप(fpr_init));
	स_रखो(&fpr_final,0, माप(fpr_final));

	/*
	 * अगर we get to this handler, Nat bits on both r3 and r2 have alपढ़ोy
	 * been checked. so we करोn't need to करो it
	 *
	 * extract the value to be stored
	 */
	getfpreg(ld.imm, &fpr_init, regs);
	/*
	 * during this step, we extract the spilled रेजिस्टरs from the saved
	 * context i.e., we refill. Then we store (no spill) to temporary
	 * aligned location
	 */
	चयन( ld.x6_sz ) अणु
		हाल 0:
			भग्न2mem_extended(&fpr_init, &fpr_final);
			अवरोध;
		हाल 1:
			भग्न2mem_पूर्णांकeger(&fpr_init, &fpr_final);
			अवरोध;
		हाल 2:
			भग्न2mem_single(&fpr_init, &fpr_final);
			अवरोध;
		हाल 3:
			भग्न2mem_द्विगुन(&fpr_init, &fpr_final);
			अवरोध;
	पूर्ण
	DPRINT("ld.r1=%d x6_sz=%d\n", ld.r1, ld.x6_sz);
	DDUMP("fpr_init =", &fpr_init, len);
	DDUMP("fpr_final =", &fpr_final, len);

	अगर (copy_to_user((व्योम __user *) अगरa, &fpr_final, len))
		वापस -1;

	/*
	 * stfX [r3]=r2,imm(9)
	 *
	 * NOTE:
	 * ld.r3 can never be r0, because r0 would not generate an
	 * unaligned access.
	 */
	अगर (ld.op == 0x7) अणु
		अचिन्हित दीर्घ imm;

		/*
		 * क्रमm imm9: [12:6] contain first 7bits
		 */
		imm = ld.x << 7 | ld.r1;
		/*
		 * sign extend (8bits) अगर m set
		 */
		अगर (ld.m)
			imm |= SIGN_EXT9;
		/*
		 * अगरa == r3 (NaT is necessarily cleared)
		 */
		अगरa += imm;

		DPRINT("imm=%lx r3=%lx\n", imm, अगरa);

		setreg(ld.r3, अगरa, 0, regs);
	पूर्ण
	/*
	 * we करोn't have alat_invalidate_multiple() so we need
	 * to करो the complete flush :-<<
	 */
	ia64_invala();

	वापस 0;
पूर्ण

/*
 * Make sure we log the unaligned access, so that user/sysadmin can notice it and
 * eventually fix the program.  However, we करोn't want to करो that क्रम every access so we
 * pace it with jअगरfies.
 */
अटल DEFINE_RATELIMIT_STATE(logging_rate_limit, 5 * HZ, 5);

व्योम
ia64_handle_unaligned (अचिन्हित दीर्घ अगरa, काष्ठा pt_regs *regs)
अणु
	काष्ठा ia64_psr *ipsr = ia64_psr(regs);
	mm_segment_t old_fs = get_fs();
	अचिन्हित दीर्घ bundle[2];
	अचिन्हित दीर्घ opcode;
	स्थिर काष्ठा exception_table_entry *eh = शून्य;
	जोड़ अणु
		अचिन्हित दीर्घ l;
		load_store_t insn;
	पूर्ण u;
	पूर्णांक ret = -1;

	अगर (ia64_psr(regs)->be) अणु
		/* we करोn't support big-endian accesses */
		अगर (die_अगर_kernel("big-endian unaligned accesses are not supported", regs, 0))
			वापस;
		जाओ क्रमce_sigbus;
	पूर्ण

	/*
	 * Treat kernel accesses क्रम which there is an exception handler entry the same as
	 * user-level unaligned accesses.  Otherwise, a clever program could trick this
	 * handler पूर्णांकo पढ़ोing an arbitrary kernel addresses...
	 */
	अगर (!user_mode(regs))
		eh = search_exception_tables(regs->cr_iip + ia64_psr(regs)->ri);
	अगर (user_mode(regs) || eh) अणु
		अगर ((current->thपढ़ो.flags & IA64_THREAD_UAC_SIGBUS) != 0)
			जाओ क्रमce_sigbus;

		अगर (!no_unaligned_warning &&
		    !(current->thपढ़ो.flags & IA64_THREAD_UAC_NOPRINT) &&
		    __ratelimit(&logging_rate_limit))
		अणु
			अक्षर buf[200];	/* comm[] is at most 16 bytes... */
			माप_प्रकार len;

			len = प्र_लिखो(buf, "%s(%d): unaligned access to 0x%016lx, "
				      "ip=0x%016lx\n\r", current->comm,
				      task_pid_nr(current),
				      अगरa, regs->cr_iip + ipsr->ri);
			/*
			 * Don't call tty_write_message() if we're in the kernel; we might
			 * be holding locks...
			 */
			अगर (user_mode(regs)) अणु
				काष्ठा tty_काष्ठा *tty = get_current_tty();
				tty_ग_लिखो_message(tty, buf);
				tty_kref_put(tty);
			पूर्ण
			buf[len-1] = '\0';	/* drop '\r' */
			/* watch क्रम command names containing %s */
			prपूर्णांकk(KERN_WARNING "%s", buf);
		पूर्ण अन्यथा अणु
			अगर (no_unaligned_warning) अणु
				prपूर्णांकk_once(KERN_WARNING "%s(%d) encountered an "
				       "unaligned exception which required\n"
				       "kernel assistance, which degrades "
				       "the performance of the application.\n"
				       "Unaligned exception warnings have "
				       "been disabled by the system "
				       "administrator\n"
				       "echo 0 > /proc/sys/kernel/ignore-"
				       "unaligned-usertrap to re-enable\n",
				       current->comm, task_pid_nr(current));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (__ratelimit(&logging_rate_limit)) अणु
			prपूर्णांकk(KERN_WARNING "kernel unaligned access to 0x%016lx, ip=0x%016lx\n",
			       अगरa, regs->cr_iip + ipsr->ri);
			अगर (unaligned_dump_stack)
				dump_stack();
		पूर्ण
		set_fs(KERNEL_DS);
	पूर्ण

	DPRINT("iip=%lx ifa=%lx isr=%lx (ei=%d, sp=%d)\n",
	       regs->cr_iip, अगरa, regs->cr_ipsr, ipsr->ri, ipsr->it);

	अगर (__copy_from_user(bundle, (व्योम __user *) regs->cr_iip, 16))
		जाओ failure;

	/*
	 * extract the inकाष्ठाion from the bundle given the slot number
	 */
	चयन (ipsr->ri) अणु
	      शेष:
	      हाल 0: u.l = (bundle[0] >>  5); अवरोध;
	      हाल 1: u.l = (bundle[0] >> 46) | (bundle[1] << 18); अवरोध;
	      हाल 2: u.l = (bundle[1] >> 23); अवरोध;
	पूर्ण
	opcode = (u.l >> IA64_OPCODE_SHIFT) & IA64_OPCODE_MASK;

	DPRINT("opcode=%lx ld.qp=%d ld.r1=%d ld.imm=%d ld.r3=%d ld.x=%d ld.hint=%d "
	       "ld.x6=0x%x ld.m=%d ld.op=%d\n", opcode, u.insn.qp, u.insn.r1, u.insn.imm,
	       u.insn.r3, u.insn.x, u.insn.hपूर्णांक, u.insn.x6_sz, u.insn.m, u.insn.op);

	/*
	 * IMPORTANT:
	 * Notice that the चयन statement DOES not cover all possible inकाष्ठाions
	 * that DO generate unaligned references. This is made on purpose because क्रम some
	 * inकाष्ठाions it DOES NOT make sense to try and emulate the access. Someबार it
	 * is WRONG to try and emulate. Here is a list of inकाष्ठाion we करोn't emulate i.e.,
	 * the program will get a संकेत and die:
	 *
	 *	load/store:
	 *		- ldX.spill
	 *		- stX.spill
	 *	Reason: RNATs are based on addresses
	 *		- ld16
	 *		- st16
	 *	Reason: ld16 and st16 are supposed to occur in a single
	 *		memory op
	 *
	 *	synchronization:
	 *		- cmpxchg
	 *		- fetchadd
	 *		- xchg
	 *	Reason: ATOMIC operations cannot be emulated properly using multiple
	 *	        inकाष्ठाions.
	 *
	 *	speculative loads:
	 *		- ldX.sZ
	 *	Reason: side effects, code must be पढ़ोy to deal with failure so simpler
	 *		to let the load fail.
	 * ---------------------------------------------------------------------------------
	 * XXX fixme
	 *
	 * I would like to get rid of this चयन हाल and करो something
	 * more elegant.
	 */
	चयन (opcode) अणु
	      हाल LDS_OP:
	      हाल LDSA_OP:
		अगर (u.insn.x)
			/* oops, really a semaphore op (cmpxchg, etc) */
			जाओ failure;
		fallthrough;
	      हाल LDS_IMM_OP:
	      हाल LDSA_IMM_OP:
	      हाल LDFS_OP:
	      हाल LDFSA_OP:
	      हाल LDFS_IMM_OP:
		/*
		 * The inकाष्ठाion will be retried with deferred exceptions turned on, and
		 * we should get Nat bit installed
		 *
		 * IMPORTANT: When PSR_ED is set, the रेजिस्टर & immediate update क्रमms
		 * are actually executed even though the operation failed. So we करोn't
		 * need to take care of this.
		 */
		DPRINT("forcing PSR_ED\n");
		regs->cr_ipsr |= IA64_PSR_ED;
		जाओ करोne;

	      हाल LD_OP:
	      हाल LDA_OP:
	      हाल LDBIAS_OP:
	      हाल LDACQ_OP:
	      हाल LDCCLR_OP:
	      हाल LDCNC_OP:
	      हाल LDCCLRACQ_OP:
		अगर (u.insn.x)
			/* oops, really a semaphore op (cmpxchg, etc) */
			जाओ failure;
		fallthrough;
	      हाल LD_IMM_OP:
	      हाल LDA_IMM_OP:
	      हाल LDBIAS_IMM_OP:
	      हाल LDACQ_IMM_OP:
	      हाल LDCCLR_IMM_OP:
	      हाल LDCNC_IMM_OP:
	      हाल LDCCLRACQ_IMM_OP:
		ret = emulate_load_पूर्णांक(अगरa, u.insn, regs);
		अवरोध;

	      हाल ST_OP:
	      हाल STREL_OP:
		अगर (u.insn.x)
			/* oops, really a semaphore op (cmpxchg, etc) */
			जाओ failure;
		fallthrough;
	      हाल ST_IMM_OP:
	      हाल STREL_IMM_OP:
		ret = emulate_store_पूर्णांक(अगरa, u.insn, regs);
		अवरोध;

	      हाल LDF_OP:
	      हाल LDFA_OP:
	      हाल LDFCCLR_OP:
	      हाल LDFCNC_OP:
		अगर (u.insn.x)
			ret = emulate_load_भग्नpair(अगरa, u.insn, regs);
		अन्यथा
			ret = emulate_load_भग्न(अगरa, u.insn, regs);
		अवरोध;

	      हाल LDF_IMM_OP:
	      हाल LDFA_IMM_OP:
	      हाल LDFCCLR_IMM_OP:
	      हाल LDFCNC_IMM_OP:
		ret = emulate_load_भग्न(अगरa, u.insn, regs);
		अवरोध;

	      हाल STF_OP:
	      हाल STF_IMM_OP:
		ret = emulate_store_भग्न(अगरa, u.insn, regs);
		अवरोध;

	      शेष:
		जाओ failure;
	पूर्ण
	DPRINT("ret=%d\n", ret);
	अगर (ret)
		जाओ failure;

	अगर (ipsr->ri == 2)
		/*
		 * given today's architecture this हाल is not likely to happen because a
		 * memory access inकाष्ठाion (M) can never be in the last slot of a
		 * bundle. But let's keep it क्रम now.
		 */
		regs->cr_iip += 16;
	ipsr->ri = (ipsr->ri + 1) & 0x3;

	DPRINT("ipsr->ri=%d iip=%lx\n", ipsr->ri, regs->cr_iip);
  करोne:
	set_fs(old_fs);		/* restore original address limit */
	वापस;

  failure:
	/* something went wrong... */
	अगर (!user_mode(regs)) अणु
		अगर (eh) अणु
			ia64_handle_exception(regs, eh);
			जाओ करोne;
		पूर्ण
		अगर (die_अगर_kernel("error during unaligned kernel access\n", regs, ret))
			वापस;
		/* NOT_REACHED */
	पूर्ण
  क्रमce_sigbus:
	क्रमce_sig_fault(SIGBUS, BUS_ADRALN, (व्योम __user *) अगरa,
			0, 0, 0);
	जाओ करोne;
पूर्ण

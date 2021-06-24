<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/probes/kprobes/actions-thumb.c
 *
 * Copyright (C) 2011 Jon Medhurst <tixy@yxit.co.uk>.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kprobes.h>

#समावेश "../decode-thumb.h"
#समावेश "core.h"
#समावेश "checkers.h"

/* These emulation encodings are functionally equivalent... */
#घोषणा t32_emulate_rd8rn16rm0ra12_noflags \
		t32_emulate_rdlo12rdhi8rn16rm0_noflags

/* t32 thumb actions */

अटल व्योम __kprobes
t32_simulate_table_branch(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;

	अचिन्हित दीर्घ rnv = (rn == 15) ? pc : regs->uregs[rn];
	अचिन्हित दीर्घ rmv = regs->uregs[rm];
	अचिन्हित पूर्णांक halfwords;

	अगर (insn & 0x10) /* TBH */
		halfwords = ((u16 *)rnv)[rmv];
	अन्यथा /* TBB */
		halfwords = ((u8 *)rnv)[rmv];

	regs->ARM_pc = pc + 2 * halfwords;
पूर्ण

अटल व्योम __kprobes
t32_simulate_mrs(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rd = (insn >> 8) & 0xf;
	अचिन्हित दीर्घ mask = 0xf8ff03df; /* Mask out execution state */
	regs->uregs[rd] = regs->ARM_cpsr & mask;
पूर्ण

अटल व्योम __kprobes
t32_simulate_cond_branch(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc;

	दीर्घ offset = insn & 0x7ff;		/* imm11 */
	offset += (insn & 0x003f0000) >> 5;	/* imm6 */
	offset += (insn & 0x00002000) << 4;	/* J1 */
	offset += (insn & 0x00000800) << 7;	/* J2 */
	offset -= (insn & 0x04000000) >> 7;	/* Apply sign bit */

	regs->ARM_pc = pc + (offset * 2);
पूर्ण

अटल क्रमागत probes_insn __kprobes
t32_decode_cond_branch(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *d)
अणु
	पूर्णांक cc = (insn >> 22) & 0xf;
	asi->insn_check_cc = probes_condition_checks[cc];
	asi->insn_handler = t32_simulate_cond_branch;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण

अटल व्योम __kprobes
t32_simulate_branch(probes_opcode_t insn,
		    काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc;

	दीर्घ offset = insn & 0x7ff;		/* imm11 */
	offset += (insn & 0x03ff0000) >> 5;	/* imm10 */
	offset += (insn & 0x00002000) << 9;	/* J1 */
	offset += (insn & 0x00000800) << 10;	/* J2 */
	अगर (insn & 0x04000000)
		offset -= 0x00800000; /* Apply sign bit */
	अन्यथा
		offset ^= 0x00600000; /* Invert J1 and J2 */

	अगर (insn & (1 << 14)) अणु
		/* BL or BLX */
		regs->ARM_lr = regs->ARM_pc | 1;
		अगर (!(insn & (1 << 12))) अणु
			/* BLX so चयन to ARM mode */
			regs->ARM_cpsr &= ~PSR_T_BIT;
			pc &= ~3;
		पूर्ण
	पूर्ण

	regs->ARM_pc = pc + (offset * 2);
पूर्ण

अटल व्योम __kprobes
t32_simulate_ldr_literal(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = regs->ARM_pc & ~3;
	पूर्णांक rt = (insn >> 12) & 0xf;
	अचिन्हित दीर्घ rtv;

	दीर्घ offset = insn & 0xfff;
	अगर (insn & 0x00800000)
		addr += offset;
	अन्यथा
		addr -= offset;

	अगर (insn & 0x00400000) अणु
		/* LDR */
		rtv = *(अचिन्हित दीर्घ *)addr;
		अगर (rt == 15) अणु
			bx_ग_लिखो_pc(rtv, regs);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (insn & 0x00200000) अणु
		/* LDRH */
		अगर (insn & 0x01000000)
			rtv = *(s16 *)addr;
		अन्यथा
			rtv = *(u16 *)addr;
	पूर्ण अन्यथा अणु
		/* LDRB */
		अगर (insn & 0x01000000)
			rtv = *(s8 *)addr;
		अन्यथा
			rtv = *(u8 *)addr;
	पूर्ण

	regs->uregs[rt] = rtv;
पूर्ण

अटल क्रमागत probes_insn __kprobes
t32_decode_ldmsपंचांग(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *d)
अणु
	क्रमागत probes_insn ret = kprobe_decode_ldmsपंचांग(insn, asi, d);

	/* Fixup modअगरied inकाष्ठाion to have halfwords in correct order...*/
	insn = __mem_to_opcode_arm(asi->insn[0]);
	((u16 *)asi->insn)[0] = __opcode_to_mem_thumb16(insn >> 16);
	((u16 *)asi->insn)[1] = __opcode_to_mem_thumb16(insn & 0xffff);

	वापस ret;
पूर्ण

अटल व्योम __kprobes
t32_emulate_ldrdstrd(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc & ~3;
	पूर्णांक rt1 = (insn >> 12) & 0xf;
	पूर्णांक rt2 = (insn >> 8) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rt1v यंत्र("r0") = regs->uregs[rt1];
	रेजिस्टर अचिन्हित दीर्घ rt2v यंत्र("r1") = regs->uregs[rt2];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = (rn == 15) ? pc
							  : regs->uregs[rn];

	__यंत्र__ __अस्थिर__ (
		"blx    %[fn]"
		: "=r" (rt1v), "=r" (rt2v), "=r" (rnv)
		: "0" (rt1v), "1" (rt2v), "2" (rnv), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	अगर (rn != 15)
		regs->uregs[rn] = rnv; /* Writeback base रेजिस्टर */
	regs->uregs[rt1] = rt1v;
	regs->uregs[rt2] = rt2v;
पूर्ण

अटल व्योम __kprobes
t32_emulate_ldrstr(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rt = (insn >> 12) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rtv यंत्र("r0") = regs->uregs[rt];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];

	__यंत्र__ __अस्थिर__ (
		"blx    %[fn]"
		: "=r" (rtv), "=r" (rnv)
		: "0" (rtv), "1" (rnv), "r" (rmv), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rn] = rnv; /* Writeback base रेजिस्टर */
	अगर (rt == 15) /* Can't be true for a STR as they aren't allowed */
		bx_ग_लिखो_pc(rtv, regs);
	अन्यथा
		regs->uregs[rt] = rtv;
पूर्ण

अटल व्योम __kprobes
t32_emulate_rd8rn16rm0_rwflags(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rd = (insn >> 8) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdv यंत्र("r1") = regs->uregs[rd];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];
	अचिन्हित दीर्घ cpsr = regs->ARM_cpsr;

	__यंत्र__ __अस्थिर__ (
		"msr	cpsr_fs, %[cpsr]	\n\t"
		"blx    %[fn]			\n\t"
		"mrs	%[cpsr], cpsr		\n\t"
		: "=r" (rdv), [cpsr] "=r" (cpsr)
		: "0" (rdv), "r" (rnv), "r" (rmv),
		  "1" (cpsr), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rd] = rdv;
	regs->ARM_cpsr = (regs->ARM_cpsr & ~APSR_MASK) | (cpsr & APSR_MASK);
पूर्ण

अटल व्योम __kprobes
t32_emulate_rd8pc16_noflags(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc;
	पूर्णांक rd = (insn >> 8) & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdv यंत्र("r1") = regs->uregs[rd];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = pc & ~3;

	__यंत्र__ __अस्थिर__ (
		"blx    %[fn]"
		: "=r" (rdv)
		: "0" (rdv), "r" (rnv), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rd] = rdv;
पूर्ण

अटल व्योम __kprobes
t32_emulate_rd8rn16_noflags(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rd = (insn >> 8) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdv यंत्र("r1") = regs->uregs[rd];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = regs->uregs[rn];

	__यंत्र__ __अस्थिर__ (
		"blx    %[fn]"
		: "=r" (rdv)
		: "0" (rdv), "r" (rnv), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rd] = rdv;
पूर्ण

अटल व्योम __kprobes
t32_emulate_rdlo12rdhi8rn16rm0_noflags(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		काष्ठा pt_regs *regs)
अणु
	पूर्णांक rdlo = (insn >> 12) & 0xf;
	पूर्णांक rdhi = (insn >> 8) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdlov यंत्र("r0") = regs->uregs[rdlo];
	रेजिस्टर अचिन्हित दीर्घ rdhiv यंत्र("r1") = regs->uregs[rdhi];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];

	__यंत्र__ __अस्थिर__ (
		"blx    %[fn]"
		: "=r" (rdlov), "=r" (rdhiv)
		: "0" (rdlov), "1" (rdhiv), "r" (rnv), "r" (rmv),
		  [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rdlo] = rdlov;
	regs->uregs[rdhi] = rdhiv;
पूर्ण
/* t16 thumb actions */

अटल व्योम __kprobes
t16_simulate_bxblx(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc + 2;
	पूर्णांक rm = (insn >> 3) & 0xf;
	अचिन्हित दीर्घ rmv = (rm == 15) ? pc : regs->uregs[rm];

	अगर (insn & (1 << 7)) /* BLX ? */
		regs->ARM_lr = regs->ARM_pc | 1;

	bx_ग_लिखो_pc(rmv, regs);
पूर्ण

अटल व्योम __kprobes
t16_simulate_ldr_literal(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ *base = (अचिन्हित दीर्घ *)((regs->ARM_pc + 2) & ~3);
	दीर्घ index = insn & 0xff;
	पूर्णांक rt = (insn >> 8) & 0x7;
	regs->uregs[rt] = base[index];
पूर्ण

अटल व्योम __kprobes
t16_simulate_ldrstr_sp_relative(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ* base = (अचिन्हित दीर्घ *)regs->ARM_sp;
	दीर्घ index = insn & 0xff;
	पूर्णांक rt = (insn >> 8) & 0x7;
	अगर (insn & 0x800) /* LDR */
		regs->uregs[rt] = base[index];
	अन्यथा /* STR */
		base[index] = regs->uregs[rt];
पूर्ण

अटल व्योम __kprobes
t16_simulate_reladr(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ base = (insn & 0x800) ? regs->ARM_sp
					    : ((regs->ARM_pc + 2) & ~3);
	दीर्घ offset = insn & 0xff;
	पूर्णांक rt = (insn >> 8) & 0x7;
	regs->uregs[rt] = base + offset * 4;
पूर्ण

अटल व्योम __kprobes
t16_simulate_add_sp_imm(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	दीर्घ imm = insn & 0x7f;
	अगर (insn & 0x80) /* SUB */
		regs->ARM_sp -= imm * 4;
	अन्यथा /* ADD */
		regs->ARM_sp += imm * 4;
पूर्ण

अटल व्योम __kprobes
t16_simulate_cbz(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rn = insn & 0x7;
	probes_opcode_t nonzero = regs->uregs[rn] ? insn : ~insn;
	अगर (nonzero & 0x800) अणु
		दीर्घ i = insn & 0x200;
		दीर्घ imm5 = insn & 0xf8;
		अचिन्हित दीर्घ pc = regs->ARM_pc + 2;
		regs->ARM_pc = pc + (i >> 3) + (imm5 >> 2);
	पूर्ण
पूर्ण

अटल व्योम __kprobes
t16_simulate_it(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	/*
	 * The 8 IT state bits are split पूर्णांकo two parts in CPSR:
	 *	ITSTATE<1:0> are in CPSR<26:25>
	 *	ITSTATE<7:2> are in CPSR<15:10>
	 * The new IT state is in the lower byte of insn.
	 */
	अचिन्हित दीर्घ cpsr = regs->ARM_cpsr;
	cpsr &= ~PSR_IT_MASK;
	cpsr |= (insn & 0xfc) << 8;
	cpsr |= (insn & 0x03) << 25;
	regs->ARM_cpsr = cpsr;
पूर्ण

अटल व्योम __kprobes
t16_singlestep_it(probes_opcode_t insn,
		  काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	regs->ARM_pc += 2;
	t16_simulate_it(insn, asi, regs);
पूर्ण

अटल क्रमागत probes_insn __kprobes
t16_decode_it(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *d)
अणु
	asi->insn_singlestep = t16_singlestep_it;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण

अटल व्योम __kprobes
t16_simulate_cond_branch(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc + 2;
	दीर्घ offset = insn & 0x7f;
	offset -= insn & 0x80; /* Apply sign bit */
	regs->ARM_pc = pc + (offset * 2);
पूर्ण

अटल क्रमागत probes_insn __kprobes
t16_decode_cond_branch(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *d)
अणु
	पूर्णांक cc = (insn >> 8) & 0xf;
	asi->insn_check_cc = probes_condition_checks[cc];
	asi->insn_handler = t16_simulate_cond_branch;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण

अटल व्योम __kprobes
t16_simulate_branch(probes_opcode_t insn,
		   काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc + 2;
	दीर्घ offset = insn & 0x3ff;
	offset -= insn & 0x400; /* Apply sign bit */
	regs->ARM_pc = pc + (offset * 2);
पूर्ण

अटल अचिन्हित दीर्घ __kprobes
t16_emulate_loregs(probes_opcode_t insn,
		   काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ oldcpsr = regs->ARM_cpsr;
	अचिन्हित दीर्घ newcpsr;

	__यंत्र__ __अस्थिर__ (
		"msr	cpsr_fs, %[oldcpsr]	\n\t"
		"ldmia	%[regs], {r0-r7}	\n\t"
		"blx	%[fn]			\n\t"
		"stmia	%[regs], {r0-r7}	\n\t"
		"mrs	%[newcpsr], cpsr	\n\t"
		: [newcpsr] "=r" (newcpsr)
		: [oldcpsr] "r" (oldcpsr), [regs] "r" (regs),
		  [fn] "r" (asi->insn_fn)
		: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
		  "lr", "memory", "cc"
		);

	वापस (oldcpsr & ~APSR_MASK) | (newcpsr & APSR_MASK);
पूर्ण

अटल व्योम __kprobes
t16_emulate_loregs_rwflags(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	regs->ARM_cpsr = t16_emulate_loregs(insn, asi, regs);
पूर्ण

अटल व्योम __kprobes
t16_emulate_loregs_noitrwflags(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ cpsr = t16_emulate_loregs(insn, asi, regs);
	अगर (!in_it_block(cpsr))
		regs->ARM_cpsr = cpsr;
पूर्ण

अटल व्योम __kprobes
t16_emulate_hiregs(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc + 2;
	पूर्णांक rdn = (insn & 0x7) | ((insn & 0x80) >> 4);
	पूर्णांक rm = (insn >> 3) & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdnv यंत्र("r1");
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r0");
	अचिन्हित दीर्घ cpsr = regs->ARM_cpsr;

	rdnv = (rdn == 15) ? pc : regs->uregs[rdn];
	rmv = (rm == 15) ? pc : regs->uregs[rm];

	__यंत्र__ __अस्थिर__ (
		"msr	cpsr_fs, %[cpsr]	\n\t"
		"blx    %[fn]			\n\t"
		"mrs	%[cpsr], cpsr		\n\t"
		: "=r" (rdnv), [cpsr] "=r" (cpsr)
		: "0" (rdnv), "r" (rmv), "1" (cpsr), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	अगर (rdn == 15)
		rdnv &= ~1;

	regs->uregs[rdn] = rdnv;
	regs->ARM_cpsr = (regs->ARM_cpsr & ~APSR_MASK) | (cpsr & APSR_MASK);
पूर्ण

अटल क्रमागत probes_insn __kprobes
t16_decode_hiregs(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *d)
अणु
	insn &= ~0x00ff;
	insn |= 0x001; /* Set Rdn = R1 and Rm = R0 */
	((u16 *)asi->insn)[0] = __opcode_to_mem_thumb16(insn);
	asi->insn_handler = t16_emulate_hiregs;
	वापस INSN_GOOD;
पूर्ण

अटल व्योम __kprobes
t16_emulate_push(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	__यंत्र__ __अस्थिर__ (
		"ldr	r9, [%[regs], #13*4]	\n\t"
		"ldr	r8, [%[regs], #14*4]	\n\t"
		"ldmia	%[regs], {r0-r7}	\n\t"
		"blx	%[fn]			\n\t"
		"str	r9, [%[regs], #13*4]	\n\t"
		:
		: [regs] "r" (regs), [fn] "r" (asi->insn_fn)
		: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9",
		  "lr", "memory", "cc"
		);
पूर्ण

अटल क्रमागत probes_insn __kprobes
t16_decode_push(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *d)
अणु
	/*
	 * To simulate a PUSH we use a Thumb-2 "STMDB R9!, {registers}"
	 * and call it with R9=SP and LR in the रेजिस्टर list represented
	 * by R8.
	 */
	/* 1st half STMDB R9!,अणुपूर्ण */
	((u16 *)asi->insn)[0] = __opcode_to_mem_thumb16(0xe929);
	/* 2nd half (रेजिस्टर list) */
	((u16 *)asi->insn)[1] = __opcode_to_mem_thumb16(insn & 0x1ff);
	asi->insn_handler = t16_emulate_push;
	वापस INSN_GOOD;
पूर्ण

अटल व्योम __kprobes
t16_emulate_pop_nopc(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	__यंत्र__ __अस्थिर__ (
		"ldr	r9, [%[regs], #13*4]	\n\t"
		"ldmia	%[regs], {r0-r7}	\n\t"
		"blx	%[fn]			\n\t"
		"stmia	%[regs], {r0-r7}	\n\t"
		"str	r9, [%[regs], #13*4]	\n\t"
		:
		: [regs] "r" (regs), [fn] "r" (asi->insn_fn)
		: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r9",
		  "lr", "memory", "cc"
		);
पूर्ण

अटल व्योम __kprobes
t16_emulate_pop_pc(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	रेजिस्टर अचिन्हित दीर्घ pc यंत्र("r8");

	__यंत्र__ __अस्थिर__ (
		"ldr	r9, [%[regs], #13*4]	\n\t"
		"ldmia	%[regs], {r0-r7}	\n\t"
		"blx	%[fn]			\n\t"
		"stmia	%[regs], {r0-r7}	\n\t"
		"str	r9, [%[regs], #13*4]	\n\t"
		: "=r" (pc)
		: [regs] "r" (regs), [fn] "r" (asi->insn_fn)
		: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r9",
		  "lr", "memory", "cc"
		);

	bx_ग_लिखो_pc(pc, regs);
पूर्ण

अटल क्रमागत probes_insn __kprobes
t16_decode_pop(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *d)
अणु
	/*
	 * To simulate a POP we use a Thumb-2 "LDMDB R9!, {registers}"
	 * and call it with R9=SP and PC in the रेजिस्टर list represented
	 * by R8.
	 */
	/* 1st half LDMIA R9!,अणुपूर्ण */
	((u16 *)asi->insn)[0] = __opcode_to_mem_thumb16(0xe8b9);
	/* 2nd half (रेजिस्टर list) */
	((u16 *)asi->insn)[1] = __opcode_to_mem_thumb16(insn & 0x1ff);
	asi->insn_handler = insn & 0x100 ? t16_emulate_pop_pc
					 : t16_emulate_pop_nopc;
	वापस INSN_GOOD;
पूर्ण

स्थिर जोड़ decode_action kprobes_t16_actions[NUM_PROBES_T16_ACTIONS] = अणु
	[PROBES_T16_ADD_SP] = अणु.handler = t16_simulate_add_sp_immपूर्ण,
	[PROBES_T16_CBZ] = अणु.handler = t16_simulate_cbzपूर्ण,
	[PROBES_T16_SIGN_EXTEND] = अणु.handler = t16_emulate_loregs_rwflagsपूर्ण,
	[PROBES_T16_PUSH] = अणु.decoder = t16_decode_pushपूर्ण,
	[PROBES_T16_POP] = अणु.decoder = t16_decode_popपूर्ण,
	[PROBES_T16_SEV] = अणु.handler = probes_emulate_noneपूर्ण,
	[PROBES_T16_WFE] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_T16_IT] = अणु.decoder = t16_decode_itपूर्ण,
	[PROBES_T16_CMP] = अणु.handler = t16_emulate_loregs_rwflagsपूर्ण,
	[PROBES_T16_ADDSUB] = अणु.handler = t16_emulate_loregs_noitrwflagsपूर्ण,
	[PROBES_T16_LOGICAL] = अणु.handler = t16_emulate_loregs_noitrwflagsपूर्ण,
	[PROBES_T16_LDR_LIT] = अणु.handler = t16_simulate_ldr_literalपूर्ण,
	[PROBES_T16_BLX] = अणु.handler = t16_simulate_bxblxपूर्ण,
	[PROBES_T16_HIREGOPS] = अणु.decoder = t16_decode_hiregsपूर्ण,
	[PROBES_T16_LDRHSTRH] = अणु.handler = t16_emulate_loregs_rwflagsपूर्ण,
	[PROBES_T16_LDRSTR] = अणु.handler = t16_simulate_ldrstr_sp_relativeपूर्ण,
	[PROBES_T16_ADR] = अणु.handler = t16_simulate_reladrपूर्ण,
	[PROBES_T16_LDMSTM] = अणु.handler = t16_emulate_loregs_rwflagsपूर्ण,
	[PROBES_T16_BRANCH_COND] = अणु.decoder = t16_decode_cond_branchपूर्ण,
	[PROBES_T16_BRANCH] = अणु.handler = t16_simulate_branchपूर्ण,
पूर्ण;

स्थिर जोड़ decode_action kprobes_t32_actions[NUM_PROBES_T32_ACTIONS] = अणु
	[PROBES_T32_LDMSTM] = अणु.decoder = t32_decode_ldmsपंचांगपूर्ण,
	[PROBES_T32_LDRDSTRD] = अणु.handler = t32_emulate_ldrdstrdपूर्ण,
	[PROBES_T32_TABLE_BRANCH] = अणु.handler = t32_simulate_table_branchपूर्ण,
	[PROBES_T32_TST] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_MOV] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_ADDSUB] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_LOGICAL] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_CMP] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_ADDWSUBW_PC] = अणु.handler = t32_emulate_rd8pc16_noflags,पूर्ण,
	[PROBES_T32_ADDWSUBW] = अणु.handler = t32_emulate_rd8rn16_noflagsपूर्ण,
	[PROBES_T32_MOVW] = अणु.handler = t32_emulate_rd8rn16_noflagsपूर्ण,
	[PROBES_T32_SAT] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_BITFIELD] = अणु.handler = t32_emulate_rd8rn16_noflagsपूर्ण,
	[PROBES_T32_SEV] = अणु.handler = probes_emulate_noneपूर्ण,
	[PROBES_T32_WFE] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_T32_MRS] = अणु.handler = t32_simulate_mrsपूर्ण,
	[PROBES_T32_BRANCH_COND] = अणु.decoder = t32_decode_cond_branchपूर्ण,
	[PROBES_T32_BRANCH] = अणु.handler = t32_simulate_branchपूर्ण,
	[PROBES_T32_PLDI] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_T32_LDR_LIT] = अणु.handler = t32_simulate_ldr_literalपूर्ण,
	[PROBES_T32_LDRSTR] = अणु.handler = t32_emulate_ldrstrपूर्ण,
	[PROBES_T32_SIGN_EXTEND] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_MEDIA] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_REVERSE] = अणु.handler = t32_emulate_rd8rn16_noflagsपूर्ण,
	[PROBES_T32_MUL_ADD] = अणु.handler = t32_emulate_rd8rn16rm0_rwflagsपूर्ण,
	[PROBES_T32_MUL_ADD2] = अणु.handler = t32_emulate_rd8rn16rm0ra12_noflagsपूर्ण,
	[PROBES_T32_MUL_ADD_LONG] = अणु
		.handler = t32_emulate_rdlo12rdhi8rn16rm0_noflagsपूर्ण,
पूर्ण;

स्थिर काष्ठा decode_checker *kprobes_t32_checkers[] = अणुt32_stack_checker, शून्यपूर्ण;
स्थिर काष्ठा decode_checker *kprobes_t16_checkers[] = अणुt16_stack_checker, शून्यपूर्ण;

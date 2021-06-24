<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/probes/kprobes/actions-arm.c
 *
 * Copyright (C) 2006, 2007 Motorola Inc.
 */

/*
 * We करो not have hardware single-stepping on ARM, This
 * efक्रमt is further complicated by the ARM not having a
 * "next PC" रेजिस्टर.  Inकाष्ठाions that change the PC
 * can't be safely single-stepped in a MP environment, so
 * we have a lot of work to करो:
 *
 * In the prepare phase:
 *   *) If it is an inकाष्ठाion that करोes anything
 *      with the CPU mode, we reject it क्रम a kprobe.
 *      (This is out of laziness rather than need.  The
 *      inकाष्ठाions could be simulated.)
 *
 *   *) Otherwise, decode the inकाष्ठाion rewriting its
 *      रेजिस्टरs to take fixed, ordered रेजिस्टरs and
 *      setting a handler क्रम it to run the inकाष्ठाion.
 *
 * In the execution phase by an inकाष्ठाion's handler:
 *
 *   *) If the PC is written to by the inकाष्ठाion, the
 *      inकाष्ठाion must be fully simulated in software.
 *
 *   *) Otherwise, a modअगरied क्रमm of the inकाष्ठाion is
 *      directly executed.  Its handler calls the
 *      inकाष्ठाion in insn[0].  In insn[1] is a
 *      "mov pc, lr" to वापस.
 *
 *      Beक्रमe calling, load up the reordered रेजिस्टरs
 *      from the original inकाष्ठाion's रेजिस्टरs.  If one
 *      of the original input रेजिस्टरs is the PC, compute
 *      and adjust the appropriate input रेजिस्टर.
 *
 *	After call completes, copy the output रेजिस्टरs to
 *      the original inकाष्ठाion's original रेजिस्टरs.
 *
 * We करोn't use a real अवरोधpoपूर्णांक inकाष्ठाion since that
 * would have us in the kernel go from SVC mode to SVC
 * mode losing the link रेजिस्टर.  Instead we use an
 * undefined inकाष्ठाion.  To simplअगरy processing, the
 * undefined inकाष्ठाion used क्रम kprobes must be reserved
 * exclusively क्रम kprobes use.
 *
 * TODO: अगरdef out some inकाष्ठाion decoding based on architecture.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>

#समावेश "../decode-arm.h"
#समावेश "core.h"
#समावेश "checkers.h"

#अगर  __LINUX_ARM_ARCH__ >= 6
#घोषणा BLX(reg)	"blx	"reg"		\n\t"
#अन्यथा
#घोषणा BLX(reg)	"mov	lr, pc		\n\t"	\
			"mov	pc, "reg"	\n\t"
#पूर्ण_अगर

अटल व्योम __kprobes
emulate_ldrdstrd(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc + 4;
	पूर्णांक rt = (insn >> 12) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rtv यंत्र("r0") = regs->uregs[rt];
	रेजिस्टर अचिन्हित दीर्घ rt2v यंत्र("r1") = regs->uregs[rt+1];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = (rn == 15) ? pc
							  : regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];

	__यंत्र__ __अस्थिर__ (
		BLX("%[fn]")
		: "=r" (rtv), "=r" (rt2v), "=r" (rnv)
		: "0" (rtv), "1" (rt2v), "2" (rnv), "r" (rmv),
		  [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rt] = rtv;
	regs->uregs[rt+1] = rt2v;
	अगर (is_ग_लिखोback(insn))
		regs->uregs[rn] = rnv;
पूर्ण

अटल व्योम __kprobes
emulate_ldr(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc + 4;
	पूर्णांक rt = (insn >> 12) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rtv यंत्र("r0");
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = (rn == 15) ? pc
							  : regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];

	__यंत्र__ __अस्थिर__ (
		BLX("%[fn]")
		: "=r" (rtv), "=r" (rnv)
		: "1" (rnv), "r" (rmv), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	अगर (rt == 15)
		load_ग_लिखो_pc(rtv, regs);
	अन्यथा
		regs->uregs[rt] = rtv;

	अगर (is_ग_लिखोback(insn))
		regs->uregs[rn] = rnv;
पूर्ण

अटल व्योम __kprobes
emulate_str(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ rtpc = regs->ARM_pc - 4 + str_pc_offset;
	अचिन्हित दीर्घ rnpc = regs->ARM_pc + 4;
	पूर्णांक rt = (insn >> 12) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rtv यंत्र("r0") = (rt == 15) ? rtpc
							  : regs->uregs[rt];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = (rn == 15) ? rnpc
							  : regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];

	__यंत्र__ __अस्थिर__ (
		BLX("%[fn]")
		: "=r" (rnv)
		: "r" (rtv), "0" (rnv), "r" (rmv), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	अगर (is_ग_लिखोback(insn))
		regs->uregs[rn] = rnv;
पूर्ण

अटल व्योम __kprobes
emulate_rd12rn16rm0rs8_rwflags(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->ARM_pc + 4;
	पूर्णांक rd = (insn >> 12) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;
	पूर्णांक rs = (insn >> 8) & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdv यंत्र("r0") = regs->uregs[rd];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = (rn == 15) ? pc
							  : regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = (rm == 15) ? pc
							  : regs->uregs[rm];
	रेजिस्टर अचिन्हित दीर्घ rsv यंत्र("r1") = regs->uregs[rs];
	अचिन्हित दीर्घ cpsr = regs->ARM_cpsr;

	__यंत्र__ __अस्थिर__ (
		"msr	cpsr_fs, %[cpsr]	\n\t"
		BLX("%[fn]")
		"mrs	%[cpsr], cpsr		\n\t"
		: "=r" (rdv), [cpsr] "=r" (cpsr)
		: "0" (rdv), "r" (rnv), "r" (rmv), "r" (rsv),
		  "1" (cpsr), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	अगर (rd == 15)
		alu_ग_लिखो_pc(rdv, regs);
	अन्यथा
		regs->uregs[rd] = rdv;
	regs->ARM_cpsr = (regs->ARM_cpsr & ~APSR_MASK) | (cpsr & APSR_MASK);
पूर्ण

अटल व्योम __kprobes
emulate_rd12rn16rm0_rwflags_nopc(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rd = (insn >> 12) & 0xf;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक rm = insn & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdv यंत्र("r0") = regs->uregs[rd];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r2") = regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];
	अचिन्हित दीर्घ cpsr = regs->ARM_cpsr;

	__यंत्र__ __अस्थिर__ (
		"msr	cpsr_fs, %[cpsr]	\n\t"
		BLX("%[fn]")
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
emulate_rd16rn12rm0rs8_rwflags_nopc(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi,
	काष्ठा pt_regs *regs)
अणु
	पूर्णांक rd = (insn >> 16) & 0xf;
	पूर्णांक rn = (insn >> 12) & 0xf;
	पूर्णांक rm = insn & 0xf;
	पूर्णांक rs = (insn >> 8) & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdv यंत्र("r2") = regs->uregs[rd];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r0") = regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];
	रेजिस्टर अचिन्हित दीर्घ rsv यंत्र("r1") = regs->uregs[rs];
	अचिन्हित दीर्घ cpsr = regs->ARM_cpsr;

	__यंत्र__ __अस्थिर__ (
		"msr	cpsr_fs, %[cpsr]	\n\t"
		BLX("%[fn]")
		"mrs	%[cpsr], cpsr		\n\t"
		: "=r" (rdv), [cpsr] "=r" (cpsr)
		: "0" (rdv), "r" (rnv), "r" (rmv), "r" (rsv),
		  "1" (cpsr), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rd] = rdv;
	regs->ARM_cpsr = (regs->ARM_cpsr & ~APSR_MASK) | (cpsr & APSR_MASK);
पूर्ण

अटल व्योम __kprobes
emulate_rd12rm0_noflags_nopc(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rd = (insn >> 12) & 0xf;
	पूर्णांक rm = insn & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdv यंत्र("r0") = regs->uregs[rd];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r3") = regs->uregs[rm];

	__यंत्र__ __अस्थिर__ (
		BLX("%[fn]")
		: "=r" (rdv)
		: "0" (rdv), "r" (rmv), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rd] = rdv;
पूर्ण

अटल व्योम __kprobes
emulate_rdlo12rdhi16rn0rm8_rwflags_nopc(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi,
	काष्ठा pt_regs *regs)
अणु
	पूर्णांक rdlo = (insn >> 12) & 0xf;
	पूर्णांक rdhi = (insn >> 16) & 0xf;
	पूर्णांक rn = insn & 0xf;
	पूर्णांक rm = (insn >> 8) & 0xf;

	रेजिस्टर अचिन्हित दीर्घ rdlov यंत्र("r0") = regs->uregs[rdlo];
	रेजिस्टर अचिन्हित दीर्घ rdhiv यंत्र("r2") = regs->uregs[rdhi];
	रेजिस्टर अचिन्हित दीर्घ rnv यंत्र("r3") = regs->uregs[rn];
	रेजिस्टर अचिन्हित दीर्घ rmv यंत्र("r1") = regs->uregs[rm];
	अचिन्हित दीर्घ cpsr = regs->ARM_cpsr;

	__यंत्र__ __अस्थिर__ (
		"msr	cpsr_fs, %[cpsr]	\n\t"
		BLX("%[fn]")
		"mrs	%[cpsr], cpsr		\n\t"
		: "=r" (rdlov), "=r" (rdhiv), [cpsr] "=r" (cpsr)
		: "0" (rdlov), "1" (rdhiv), "r" (rnv), "r" (rmv),
		  "2" (cpsr), [fn] "r" (asi->insn_fn)
		: "lr", "memory", "cc"
	);

	regs->uregs[rdlo] = rdlov;
	regs->uregs[rdhi] = rdhiv;
	regs->ARM_cpsr = (regs->ARM_cpsr & ~APSR_MASK) | (cpsr & APSR_MASK);
पूर्ण

स्थिर जोड़ decode_action kprobes_arm_actions[NUM_PROBES_ARM_ACTIONS] = अणु
	[PROBES_PRELOAD_IMM] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_PRELOAD_REG] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_BRANCH_IMM] = अणु.handler = simulate_blx1पूर्ण,
	[PROBES_MRS] = अणु.handler = simulate_mrsपूर्ण,
	[PROBES_BRANCH_REG] = अणु.handler = simulate_blx2bxपूर्ण,
	[PROBES_CLZ] = अणु.handler = emulate_rd12rm0_noflags_nopcपूर्ण,
	[PROBES_SATURATING_ARITHMETIC] = अणु
		.handler = emulate_rd12rn16rm0_rwflags_nopcपूर्ण,
	[PROBES_MUL1] = अणु.handler = emulate_rdlo12rdhi16rn0rm8_rwflags_nopcपूर्ण,
	[PROBES_MUL2] = अणु.handler = emulate_rd16rn12rm0rs8_rwflags_nopcपूर्ण,
	[PROBES_SWP] = अणु.handler = emulate_rd12rn16rm0_rwflags_nopcपूर्ण,
	[PROBES_LDRSTRD] = अणु.handler = emulate_ldrdstrdपूर्ण,
	[PROBES_LOAD_EXTRA] = अणु.handler = emulate_ldrपूर्ण,
	[PROBES_LOAD] = अणु.handler = emulate_ldrपूर्ण,
	[PROBES_STORE_EXTRA] = अणु.handler = emulate_strपूर्ण,
	[PROBES_STORE] = अणु.handler = emulate_strपूर्ण,
	[PROBES_MOV_IP_SP] = अणु.handler = simulate_mov_ipspपूर्ण,
	[PROBES_DATA_PROCESSING_REG] = अणु
		.handler = emulate_rd12rn16rm0rs8_rwflagsपूर्ण,
	[PROBES_DATA_PROCESSING_IMM] = अणु
		.handler = emulate_rd12rn16rm0rs8_rwflagsपूर्ण,
	[PROBES_MOV_HALFWORD] = अणु.handler = emulate_rd12rm0_noflags_nopcपूर्ण,
	[PROBES_SEV] = अणु.handler = probes_emulate_noneपूर्ण,
	[PROBES_WFE] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_SATURATE] = अणु.handler = emulate_rd12rn16rm0_rwflags_nopcपूर्ण,
	[PROBES_REV] = अणु.handler = emulate_rd12rm0_noflags_nopcपूर्ण,
	[PROBES_MMI] = अणु.handler = emulate_rd12rn16rm0_rwflags_nopcपूर्ण,
	[PROBES_PACK] = अणु.handler = emulate_rd12rn16rm0_rwflags_nopcपूर्ण,
	[PROBES_EXTEND] = अणु.handler = emulate_rd12rm0_noflags_nopcपूर्ण,
	[PROBES_EXTEND_ADD] = अणु.handler = emulate_rd12rn16rm0_rwflags_nopcपूर्ण,
	[PROBES_MUL_ADD_LONG] = अणु
		.handler = emulate_rdlo12rdhi16rn0rm8_rwflags_nopcपूर्ण,
	[PROBES_MUL_ADD] = अणु.handler = emulate_rd16rn12rm0rs8_rwflags_nopcपूर्ण,
	[PROBES_BITFIELD] = अणु.handler = emulate_rd12rm0_noflags_nopcपूर्ण,
	[PROBES_BRANCH] = अणु.handler = simulate_bblपूर्ण,
	[PROBES_LDMSTM] = अणु.decoder = kprobe_decode_ldmsपंचांगपूर्ण
पूर्ण;

स्थिर काष्ठा decode_checker *kprobes_arm_checkers[] = अणुarm_stack_checker, arm_regs_checker, शून्यपूर्ण;

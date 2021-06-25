<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/probes/kprobes/actions-common.c
 *
 * Copyright (C) 2011 Jon Medhurst <tixy@yxit.co.uk>.
 *
 * Some contents moved here from arch/arm/include/यंत्र/kprobes-arm.c which is
 * Copyright (C) 2006, 2007 Motorola Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <यंत्र/opcodes.h>

#समावेश "core.h"


अटल व्योम __kprobes simulate_ldm1sपंचांग1(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		काष्ठा pt_regs *regs)
अणु
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक lbit = insn & (1 << 20);
	पूर्णांक wbit = insn & (1 << 21);
	पूर्णांक ubit = insn & (1 << 23);
	पूर्णांक pbit = insn & (1 << 24);
	दीर्घ *addr = (दीर्घ *)regs->uregs[rn];
	पूर्णांक reg_bit_vector;
	पूर्णांक reg_count;

	reg_count = 0;
	reg_bit_vector = insn & 0xffff;
	जबतक (reg_bit_vector) अणु
		reg_bit_vector &= (reg_bit_vector - 1);
		++reg_count;
	पूर्ण

	अगर (!ubit)
		addr -= reg_count;
	addr += (!pbit == !ubit);

	reg_bit_vector = insn & 0xffff;
	जबतक (reg_bit_vector) अणु
		पूर्णांक reg = __ffs(reg_bit_vector);
		reg_bit_vector &= (reg_bit_vector - 1);
		अगर (lbit)
			regs->uregs[reg] = *addr++;
		अन्यथा
			*addr++ = regs->uregs[reg];
	पूर्ण

	अगर (wbit) अणु
		अगर (!ubit)
			addr -= reg_count;
		addr -= (!pbit == !ubit);
		regs->uregs[rn] = (दीर्घ)addr;
	पूर्ण
पूर्ण

अटल व्योम __kprobes simulate_sपंचांग1_pc(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi,
	काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = regs->ARM_pc - 4;

	regs->ARM_pc = (दीर्घ)addr + str_pc_offset;
	simulate_ldm1sपंचांग1(insn, asi, regs);
	regs->ARM_pc = (दीर्घ)addr + 4;
पूर्ण

अटल व्योम __kprobes simulate_ldm1_pc(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi,
	काष्ठा pt_regs *regs)
अणु
	simulate_ldm1sपंचांग1(insn, asi, regs);
	load_ग_लिखो_pc(regs->ARM_pc, regs);
पूर्ण

अटल व्योम __kprobes
emulate_generic_r0_12_noflags(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	रेजिस्टर व्योम *rregs यंत्र("r1") = regs;
	रेजिस्टर व्योम *rfn यंत्र("lr") = asi->insn_fn;

	__यंत्र__ __अस्थिर__ (
		"stmdb	sp!, {%[regs], r11}	\n\t"
		"ldmia	%[regs], {r0-r12}	\n\t"
#अगर __LINUX_ARM_ARCH__ >= 6
		"blx	%[fn]			\n\t"
#अन्यथा
		"str	%[fn], [sp, #-4]!	\n\t"
		"adr	lr, 1f			\n\t"
		"ldr	pc, [sp], #4		\n\t"
		"1:				\n\t"
#पूर्ण_अगर
		"ldr	lr, [sp], #4		\n\t" /* lr = regs */
		"stmia	lr, {r0-r12}		\n\t"
		"ldr	r11, [sp], #4		\n\t"
		: [regs] "=r" (rregs), [fn] "=r" (rfn)
		: "0" (rregs), "1" (rfn)
		: "r0", "r2", "r3", "r4", "r5", "r6", "r7",
		  "r8", "r9", "r10", "r12", "memory", "cc"
		);
पूर्ण

अटल व्योम __kprobes
emulate_generic_r2_14_noflags(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	emulate_generic_r0_12_noflags(insn, asi,
		(काष्ठा pt_regs *)(regs->uregs+2));
पूर्ण

अटल व्योम __kprobes
emulate_ldm_r3_15(probes_opcode_t insn,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs)
अणु
	emulate_generic_r0_12_noflags(insn, asi,
		(काष्ठा pt_regs *)(regs->uregs+3));
	load_ग_लिखो_pc(regs->ARM_pc, regs);
पूर्ण

क्रमागत probes_insn __kprobes
kprobe_decode_ldmsपंचांग(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	probes_insn_handler_t *handler = 0;
	अचिन्हित reglist = insn & 0xffff;
	पूर्णांक is_ldm = insn & 0x100000;
	पूर्णांक rn = (insn >> 16) & 0xf;

	अगर (rn <= 12 && (reglist & 0xe000) == 0) अणु
		/* Inकाष्ठाion only uses रेजिस्टरs in the range R0..R12 */
		handler = emulate_generic_r0_12_noflags;

	पूर्ण अन्यथा अगर (rn >= 2 && (reglist & 0x8003) == 0) अणु
		/* Inकाष्ठाion only uses रेजिस्टरs in the range R2..R14 */
		rn -= 2;
		reglist >>= 2;
		handler = emulate_generic_r2_14_noflags;

	पूर्ण अन्यथा अगर (rn >= 3 && (reglist & 0x0007) == 0) अणु
		/* Inकाष्ठाion only uses रेजिस्टरs in the range R3..R15 */
		अगर (is_ldm && (reglist & 0x8000)) अणु
			rn -= 3;
			reglist >>= 3;
			handler = emulate_ldm_r3_15;
		पूर्ण
	पूर्ण

	अगर (handler) अणु
		/* We can emulate the inकाष्ठाion in (possibly) modअगरied क्रमm */
		asi->insn[0] = __opcode_to_mem_arm((insn & 0xfff00000) |
						   (rn << 16) | reglist);
		asi->insn_handler = handler;
		वापस INSN_GOOD;
	पूर्ण

	/* Fallback to slower simulation... */
	अगर (reglist & 0x8000)
		handler = is_ldm ? simulate_ldm1_pc : simulate_sपंचांग1_pc;
	अन्यथा
		handler = simulate_ldm1sपंचांग1;
	asi->insn_handler = handler;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण


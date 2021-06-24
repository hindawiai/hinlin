<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hyp portion of the (not much of an) Emulation layer क्रम 32bit guests.
 *
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * based on arch/arm/kvm/emulate.c
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>

/*
 * stolen from arch/arm/kernel/opcodes.c
 *
 * condition code lookup table
 * index पूर्णांकo the table is test code: EQ, NE, ... LT, GT, AL, NV
 *
 * bit position in लघु is condition code: NZCV
 */
अटल स्थिर अचिन्हित लघु cc_map[16] = अणु
	0xF0F0,			/* EQ == Z set            */
	0x0F0F,			/* NE                     */
	0xCCCC,			/* CS == C set            */
	0x3333,			/* CC                     */
	0xFF00,			/* MI == N set            */
	0x00FF,			/* PL                     */
	0xAAAA,			/* VS == V set            */
	0x5555,			/* VC                     */
	0x0C0C,			/* HI == C set && Z clear */
	0xF3F3,			/* LS == C clear || Z set */
	0xAA55,			/* GE == (N==V)           */
	0x55AA,			/* LT == (N!=V)           */
	0x0A05,			/* GT == (!Z && (N==V))   */
	0xF5FA,			/* LE == (Z || (N!=V))    */
	0xFFFF,			/* AL always              */
	0			/* NV                     */
पूर्ण;

/*
 * Check अगर a trapped inकाष्ठाion should have been executed or not.
 */
bool kvm_condition_valid32(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ cpsr;
	u32 cpsr_cond;
	पूर्णांक cond;

	/* Top two bits non-zero?  Unconditional. */
	अगर (kvm_vcpu_get_esr(vcpu) >> 30)
		वापस true;

	/* Is condition field valid? */
	cond = kvm_vcpu_get_condition(vcpu);
	अगर (cond == 0xE)
		वापस true;

	cpsr = *vcpu_cpsr(vcpu);

	अगर (cond < 0) अणु
		/* This can happen in Thumb mode: examine IT state. */
		अचिन्हित दीर्घ it;

		it = ((cpsr >> 8) & 0xFC) | ((cpsr >> 25) & 0x3);

		/* it == 0 => unconditional. */
		अगर (it == 0)
			वापस true;

		/* The cond क्रम this insn works out as the top 4 bits. */
		cond = (it >> 4);
	पूर्ण

	cpsr_cond = cpsr >> 28;

	अगर (!((cc_map[cond] >> cpsr_cond) & 1))
		वापस false;

	वापस true;
पूर्ण

/**
 * adjust_itstate - adjust ITSTATE when emulating inकाष्ठाions in IT-block
 * @vcpu:	The VCPU poपूर्णांकer
 *
 * When exceptions occur जबतक inकाष्ठाions are executed in Thumb IF-THEN
 * blocks, the ITSTATE field of the CPSR is not advanced (updated), so we have
 * to करो this little bit of work manually. The fields map like this:
 *
 * IT[7:0] -> CPSR[26:25],CPSR[15:10]
 */
अटल व्योम kvm_adjust_itstate(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ itbits, cond;
	अचिन्हित दीर्घ cpsr = *vcpu_cpsr(vcpu);
	bool is_arm = !(cpsr & PSR_AA32_T_BIT);

	अगर (is_arm || !(cpsr & PSR_AA32_IT_MASK))
		वापस;

	cond = (cpsr & 0xe000) >> 13;
	itbits = (cpsr & 0x1c00) >> (10 - 2);
	itbits |= (cpsr & (0x3 << 25)) >> 25;

	/* Perक्रमm ITAdvance (see page A2-52 in ARM DDI 0406C) */
	अगर ((itbits & 0x7) == 0)
		itbits = cond = 0;
	अन्यथा
		itbits = (itbits << 1) & 0x1f;

	cpsr &= ~PSR_AA32_IT_MASK;
	cpsr |= cond << 13;
	cpsr |= (itbits & 0x1c) << (10 - 2);
	cpsr |= (itbits & 0x3) << 25;
	*vcpu_cpsr(vcpu) = cpsr;
पूर्ण

/**
 * kvm_skip_instr - skip a trapped inकाष्ठाion and proceed to the next
 * @vcpu: The vcpu poपूर्णांकer
 */
व्योम kvm_skip_instr32(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 pc = *vcpu_pc(vcpu);
	bool is_thumb;

	is_thumb = !!(*vcpu_cpsr(vcpu) & PSR_AA32_T_BIT);
	अगर (is_thumb && !kvm_vcpu_trap_il_is32bit(vcpu))
		pc += 2;
	अन्यथा
		pc += 4;

	*vcpu_pc(vcpu) = pc;

	kvm_adjust_itstate(vcpu);
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/probes/decode.c
 *
 * Copyright (C) 2011 Jon Medhurst <tixy@yxit.co.uk>.
 *
 * Some contents moved here from arch/arm/include/यंत्र/kprobes-arm.c which is
 * Copyright (C) 2006, 2007 Motorola Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/bug.h>

#समावेश "decode.h"


#अगर_अघोषित find_str_pc_offset

/*
 * For STR and STM inकाष्ठाions, an ARM core may choose to use either
 * a +8 or a +12 displacement from the current inकाष्ठाion's address.
 * Whichever value is chosen क्रम a given core, it must be the same क्रम
 * both inकाष्ठाions and may not change.  This function measures it.
 */

पूर्णांक str_pc_offset;

व्योम __init find_str_pc_offset(व्योम)
अणु
	पूर्णांक addr, scratch, ret;

	__यंत्र__ (
		"sub	%[ret], pc, #4		\n\t"
		"str	pc, %[addr]		\n\t"
		"ldr	%[scr], %[addr]		\n\t"
		"sub	%[ret], %[scr], %[ret]	\n\t"
		: [ret] "=r" (ret), [scr] "=r" (scratch), [addr] "+m" (addr));

	str_pc_offset = ret;
पूर्ण

#पूर्ण_अगर /* !find_str_pc_offset */


#अगर_अघोषित test_load_ग_लिखो_pc_पूर्णांकerworking

bool load_ग_लिखो_pc_पूर्णांकerworks;

व्योम __init test_load_ग_लिखो_pc_पूर्णांकerworking(व्योम)
अणु
	पूर्णांक arch = cpu_architecture();
	BUG_ON(arch == CPU_ARCH_UNKNOWN);
	load_ग_लिखो_pc_पूर्णांकerworks = arch >= CPU_ARCH_ARMv5T;
पूर्ण

#पूर्ण_अगर /* !test_load_ग_लिखो_pc_पूर्णांकerworking */


#अगर_अघोषित test_alu_ग_लिखो_pc_पूर्णांकerworking

bool alu_ग_लिखो_pc_पूर्णांकerworks;

व्योम __init test_alu_ग_लिखो_pc_पूर्णांकerworking(व्योम)
अणु
	पूर्णांक arch = cpu_architecture();
	BUG_ON(arch == CPU_ARCH_UNKNOWN);
	alu_ग_लिखो_pc_पूर्णांकerworks = arch >= CPU_ARCH_ARMv7;
पूर्ण

#पूर्ण_अगर /* !test_alu_ग_लिखो_pc_पूर्णांकerworking */


व्योम __init arm_probes_decode_init(व्योम)
अणु
	find_str_pc_offset();
	test_load_ग_लिखो_pc_पूर्णांकerworking();
	test_alu_ग_लिखो_pc_पूर्णांकerworking();
पूर्ण


अटल अचिन्हित दीर्घ __kprobes __check_eq(अचिन्हित दीर्घ cpsr)
अणु
	वापस cpsr & PSR_Z_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_ne(अचिन्हित दीर्घ cpsr)
अणु
	वापस (~cpsr) & PSR_Z_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_cs(अचिन्हित दीर्घ cpsr)
अणु
	वापस cpsr & PSR_C_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_cc(अचिन्हित दीर्घ cpsr)
अणु
	वापस (~cpsr) & PSR_C_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_mi(अचिन्हित दीर्घ cpsr)
अणु
	वापस cpsr & PSR_N_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_pl(अचिन्हित दीर्घ cpsr)
अणु
	वापस (~cpsr) & PSR_N_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_vs(अचिन्हित दीर्घ cpsr)
अणु
	वापस cpsr & PSR_V_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_vc(अचिन्हित दीर्घ cpsr)
अणु
	वापस (~cpsr) & PSR_V_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_hi(अचिन्हित दीर्घ cpsr)
अणु
	cpsr &= ~(cpsr >> 1); /* PSR_C_BIT &= ~PSR_Z_BIT */
	वापस cpsr & PSR_C_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_ls(अचिन्हित दीर्घ cpsr)
अणु
	cpsr &= ~(cpsr >> 1); /* PSR_C_BIT &= ~PSR_Z_BIT */
	वापस (~cpsr) & PSR_C_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_ge(अचिन्हित दीर्घ cpsr)
अणु
	cpsr ^= (cpsr << 3); /* PSR_N_BIT ^= PSR_V_BIT */
	वापस (~cpsr) & PSR_N_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_lt(अचिन्हित दीर्घ cpsr)
अणु
	cpsr ^= (cpsr << 3); /* PSR_N_BIT ^= PSR_V_BIT */
	वापस cpsr & PSR_N_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_gt(अचिन्हित दीर्घ cpsr)
अणु
	अचिन्हित दीर्घ temp = cpsr ^ (cpsr << 3); /* PSR_N_BIT ^= PSR_V_BIT */
	temp |= (cpsr << 1);			 /* PSR_N_BIT |= PSR_Z_BIT */
	वापस (~temp) & PSR_N_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_le(अचिन्हित दीर्घ cpsr)
अणु
	अचिन्हित दीर्घ temp = cpsr ^ (cpsr << 3); /* PSR_N_BIT ^= PSR_V_BIT */
	temp |= (cpsr << 1);			 /* PSR_N_BIT |= PSR_Z_BIT */
	वापस temp & PSR_N_BIT;
पूर्ण

अटल अचिन्हित दीर्घ __kprobes __check_al(अचिन्हित दीर्घ cpsr)
अणु
	वापस true;
पूर्ण

probes_check_cc * स्थिर probes_condition_checks[16] = अणु
	&__check_eq, &__check_ne, &__check_cs, &__check_cc,
	&__check_mi, &__check_pl, &__check_vs, &__check_vc,
	&__check_hi, &__check_ls, &__check_ge, &__check_lt,
	&__check_gt, &__check_le, &__check_al, &__check_al
पूर्ण;


व्योम __kprobes probes_simulate_nop(probes_opcode_t opcode,
	काष्ठा arch_probes_insn *asi,
	काष्ठा pt_regs *regs)
अणु
पूर्ण

व्योम __kprobes probes_emulate_none(probes_opcode_t opcode,
	काष्ठा arch_probes_insn *asi,
	काष्ठा pt_regs *regs)
अणु
	asi->insn_fn();
पूर्ण

/*
 * Prepare an inकाष्ठाion slot to receive an inकाष्ठाion क्रम emulating.
 * This is करोne by placing a subroutine वापस after the location where the
 * inकाष्ठाion will be placed. We also modअगरy ARM inकाष्ठाions to be
 * unconditional as the condition code will alपढ़ोy be checked beक्रमe any
 * emulation handler is called.
 */
अटल probes_opcode_t __kprobes
prepare_emulated_insn(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		      bool thumb)
अणु
#अगर_घोषित CONFIG_THUMB2_KERNEL
	अगर (thumb) अणु
		u16 *thumb_insn = (u16 *)asi->insn;
		/* Thumb bx lr */
		thumb_insn[1] = __opcode_to_mem_thumb16(0x4770);
		thumb_insn[2] = __opcode_to_mem_thumb16(0x4770);
		वापस insn;
	पूर्ण
	asi->insn[1] = __opcode_to_mem_arm(0xe12fff1e); /* ARM bx lr */
#अन्यथा
	asi->insn[1] = __opcode_to_mem_arm(0xe1a0f00e); /* mov pc, lr */
#पूर्ण_अगर
	/* Make an ARM inकाष्ठाion unconditional */
	अगर (insn < 0xe0000000)
		insn = (insn | 0xe0000000) & ~0x10000000;
	वापस insn;
पूर्ण

/*
 * Write a (probably modअगरied) inकाष्ठाion पूर्णांकo the slot previously prepared by
 * prepare_emulated_insn
 */
अटल व्योम  __kprobes
set_emulated_insn(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		  bool thumb)
अणु
#अगर_घोषित CONFIG_THUMB2_KERNEL
	अगर (thumb) अणु
		u16 *ip = (u16 *)asi->insn;
		अगर (is_wide_inकाष्ठाion(insn))
			*ip++ = __opcode_to_mem_thumb16(insn >> 16);
		*ip++ = __opcode_to_mem_thumb16(insn);
		वापस;
	पूर्ण
#पूर्ण_अगर
	asi->insn[0] = __opcode_to_mem_arm(insn);
पूर्ण

/*
 * When we modअगरy the रेजिस्टर numbers encoded in an inकाष्ठाion to be emulated,
 * the new values come from this define. For ARM and 32-bit Thumb inकाष्ठाions
 * this gives...
 *
 *	bit position	  16  12   8   4   0
 *	---------------+---+---+---+---+---+
 *	रेजिस्टर	 r2  r0  r1  --  r3
 */
#घोषणा INSN_NEW_BITS		0x00020103

/* Each nibble has same value as that at INSN_NEW_BITS bit 16 */
#घोषणा INSN_SAMEAS16_BITS	0x22222222

/*
 * Validate and modअगरy each of the रेजिस्टरs encoded in an inकाष्ठाion.
 *
 * Each nibble in regs contains a value from क्रमागत decode_reg_type. For each
 * non-zero value, the corresponding nibble in pinsn is validated and modअगरied
 * according to the type.
 */
अटल bool __kprobes decode_regs(probes_opcode_t *pinsn, u32 regs, bool modअगरy)
अणु
	probes_opcode_t insn = *pinsn;
	probes_opcode_t mask = 0xf; /* Start at least signअगरicant nibble */

	क्रम (; regs != 0; regs >>= 4, mask <<= 4) अणु

		probes_opcode_t new_bits = INSN_NEW_BITS;

		चयन (regs & 0xf) अणु

		हाल REG_TYPE_NONE:
			/* Nibble not a रेजिस्टर, skip to next */
			जारी;

		हाल REG_TYPE_ANY:
			/* Any रेजिस्टर is allowed */
			अवरोध;

		हाल REG_TYPE_SAMEAS16:
			/* Replace रेजिस्टर with same as at bit position 16 */
			new_bits = INSN_SAMEAS16_BITS;
			अवरोध;

		हाल REG_TYPE_SP:
			/* Only allow SP (R13) */
			अगर ((insn ^ 0xdddddddd) & mask)
				जाओ reject;
			अवरोध;

		हाल REG_TYPE_PC:
			/* Only allow PC (R15) */
			अगर ((insn ^ 0xffffffff) & mask)
				जाओ reject;
			अवरोध;

		हाल REG_TYPE_NOSP:
			/* Reject SP (R13) */
			अगर (((insn ^ 0xdddddddd) & mask) == 0)
				जाओ reject;
			अवरोध;

		हाल REG_TYPE_NOSPPC:
		हाल REG_TYPE_NOSPPCX:
			/* Reject SP and PC (R13 and R15) */
			अगर (((insn ^ 0xdddddddd) & 0xdddddddd & mask) == 0)
				जाओ reject;
			अवरोध;

		हाल REG_TYPE_NOPCWB:
			अगर (!is_ग_लिखोback(insn))
				अवरोध; /* No ग_लिखोback, so any रेजिस्टर is OK */
			fallthrough;
		हाल REG_TYPE_NOPC:
		हाल REG_TYPE_NOPCX:
			/* Reject PC (R15) */
			अगर (((insn ^ 0xffffffff) & mask) == 0)
				जाओ reject;
			अवरोध;
		पूर्ण

		/* Replace value of nibble with new रेजिस्टर number... */
		insn &= ~mask;
		insn |= new_bits & mask;
	पूर्ण

	अगर (modअगरy)
		*pinsn = insn;

	वापस true;

reject:
	वापस false;
पूर्ण

अटल स्थिर पूर्णांक decode_काष्ठा_sizes[NUM_DECODE_TYPES] = अणु
	[DECODE_TYPE_TABLE]	= माप(काष्ठा decode_table),
	[DECODE_TYPE_CUSTOM]	= माप(काष्ठा decode_custom),
	[DECODE_TYPE_SIMULATE]	= माप(काष्ठा decode_simulate),
	[DECODE_TYPE_EMULATE]	= माप(काष्ठा decode_emulate),
	[DECODE_TYPE_OR]	= माप(काष्ठा decode_or),
	[DECODE_TYPE_REJECT]	= माप(काष्ठा decode_reject)
पूर्ण;

अटल पूर्णांक run_checkers(स्थिर काष्ठा decode_checker *checkers[],
		पूर्णांक action, probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	स्थिर काष्ठा decode_checker **p;

	अगर (!checkers)
		वापस INSN_GOOD;

	p = checkers;
	जबतक (*p != शून्य) अणु
		पूर्णांक retval;
		probes_check_t *checker_func = (*p)[action].checker;

		retval = INSN_GOOD;
		अगर (checker_func)
			retval = checker_func(insn, asi, h);
		अगर (retval == INSN_REJECTED)
			वापस retval;
		p++;
	पूर्ण
	वापस INSN_GOOD;
पूर्ण

/*
 * probes_decode_insn operates on data tables in order to decode an ARM
 * architecture inकाष्ठाion onto which a kprobe has been placed.
 *
 * These inकाष्ठाion decoding tables are a concatenation of entries each
 * of which consist of one of the following काष्ठाs:
 *
 *	decode_table
 *	decode_custom
 *	decode_simulate
 *	decode_emulate
 *	decode_or
 *	decode_reject
 *
 * Each of these starts with a काष्ठा decode_header which has the following
 * fields:
 *
 *	type_regs
 *	mask
 *	value
 *
 * The least signअगरicant DECODE_TYPE_BITS of type_regs contains a value
 * from क्रमागत decode_type, this indicates which of the decode_* काष्ठाs
 * the entry contains. The value DECODE_TYPE_END indicates the end of the
 * table.
 *
 * When the table is parsed, each entry is checked in turn to see अगर it
 * matches the inकाष्ठाion to be decoded using the test:
 *
 *	(insn & mask) == value
 *
 * If no match is found beक्रमe the end of the table is reached then decoding
 * fails with INSN_REJECTED.
 *
 * When a match is found, decode_regs() is called to validate and modअगरy each
 * of the रेजिस्टरs encoded in the inकाष्ठाion; the data it uses to करो this
 * is (type_regs >> DECODE_TYPE_BITS). A validation failure will cause decoding
 * to fail with INSN_REJECTED.
 *
 * Once the inकाष्ठाion has passed the above tests, further processing
 * depends on the type of the table entry's decode काष्ठा.
 *
 */
पूर्णांक __kprobes
probes_decode_insn(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		   स्थिर जोड़ decode_item *table, bool thumb,
		   bool emulate, स्थिर जोड़ decode_action *actions,
		   स्थिर काष्ठा decode_checker *checkers[])
अणु
	स्थिर काष्ठा decode_header *h = (काष्ठा decode_header *)table;
	स्थिर काष्ठा decode_header *next;
	bool matched = false;
	/*
	 * @insn can be modअगरied by decode_regs. Save its original
	 * value क्रम checkers.
	 */
	probes_opcode_t origin_insn = insn;

	/*
	 * stack_space is initialized to 0 here. Checker functions
	 * should update is value अगर they find this is a stack store
	 * inकाष्ठाion: positive value means bytes of stack usage,
	 * negitive value means unable to determine stack usage
	 * अटलally. For inकाष्ठाion करोesn't store to stack, checker
	 * करो nothing with it.
	 */
	asi->stack_space = 0;

	/*
	 * Similarly to stack_space, रेजिस्टर_usage_flags is filled by
	 * checkers. Its शेष value is set to ~0, which is 'all
	 * रेजिस्टरs are used', to prevent any potential optimization.
	 */
	asi->रेजिस्टर_usage_flags = ~0UL;

	अगर (emulate)
		insn = prepare_emulated_insn(insn, asi, thumb);

	क्रम (;; h = next) अणु
		क्रमागत decode_type type = h->type_regs.bits & DECODE_TYPE_MASK;
		u32 regs = h->type_regs.bits >> DECODE_TYPE_BITS;

		अगर (type == DECODE_TYPE_END)
			वापस INSN_REJECTED;

		next = (काष्ठा decode_header *)
				((uपूर्णांकptr_t)h + decode_काष्ठा_sizes[type]);

		अगर (!matched && (insn & h->mask.bits) != h->value.bits)
			जारी;

		अगर (!decode_regs(&insn, regs, emulate))
			वापस INSN_REJECTED;

		चयन (type) अणु

		हाल DECODE_TYPE_TABLE: अणु
			काष्ठा decode_table *d = (काष्ठा decode_table *)h;
			next = (काष्ठा decode_header *)d->table.table;
			अवरोध;
		पूर्ण

		हाल DECODE_TYPE_CUSTOM: अणु
			पूर्णांक err;
			काष्ठा decode_custom *d = (काष्ठा decode_custom *)h;
			पूर्णांक action = d->decoder.action;

			err = run_checkers(checkers, action, origin_insn, asi, h);
			अगर (err == INSN_REJECTED)
				वापस INSN_REJECTED;
			वापस actions[action].decoder(insn, asi, h);
		पूर्ण

		हाल DECODE_TYPE_SIMULATE: अणु
			पूर्णांक err;
			काष्ठा decode_simulate *d = (काष्ठा decode_simulate *)h;
			पूर्णांक action = d->handler.action;

			err = run_checkers(checkers, action, origin_insn, asi, h);
			अगर (err == INSN_REJECTED)
				वापस INSN_REJECTED;
			asi->insn_handler = actions[action].handler;
			वापस INSN_GOOD_NO_SLOT;
		पूर्ण

		हाल DECODE_TYPE_EMULATE: अणु
			पूर्णांक err;
			काष्ठा decode_emulate *d = (काष्ठा decode_emulate *)h;
			पूर्णांक action = d->handler.action;

			err = run_checkers(checkers, action, origin_insn, asi, h);
			अगर (err == INSN_REJECTED)
				वापस INSN_REJECTED;

			अगर (!emulate)
				वापस actions[action].decoder(insn, asi, h);

			asi->insn_handler = actions[action].handler;
			set_emulated_insn(insn, asi, thumb);
			वापस INSN_GOOD;
		पूर्ण

		हाल DECODE_TYPE_OR:
			matched = true;
			अवरोध;

		हाल DECODE_TYPE_REJECT:
		शेष:
			वापस INSN_REJECTED;
		पूर्ण
	पूर्ण
पूर्ण

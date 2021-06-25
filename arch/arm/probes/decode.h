<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/probes/decode.h
 *
 * Copyright (C) 2011 Jon Medhurst <tixy@yxit.co.uk>.
 *
 * Some contents moved here from arch/arm/include/यंत्र/kprobes.h which is
 * Copyright (C) 2006, 2007 Motorola Inc.
 */

#अगर_अघोषित _ARM_KERNEL_PROBES_H
#घोषणा  _ARM_KERNEL_PROBES_H

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <यंत्र/probes.h>
#समावेश <यंत्र/kprobes.h>

व्योम __init arm_probes_decode_init(व्योम);

बाह्य probes_check_cc * स्थिर probes_condition_checks[16];

#अगर __LINUX_ARM_ARCH__ >= 7

/* str_pc_offset is architecturally defined from ARMv7 onwards */
#घोषणा str_pc_offset 8
#घोषणा find_str_pc_offset()

#अन्यथा /* __LINUX_ARM_ARCH__ < 7 */

/* We need a run-समय check to determine str_pc_offset */
बाह्य पूर्णांक str_pc_offset;
व्योम __init find_str_pc_offset(व्योम);

#पूर्ण_अगर


/*
 * Update ITSTATE after normal execution of an IT block inकाष्ठाion.
 *
 * The 8 IT state bits are split पूर्णांकo two parts in CPSR:
 *	ITSTATE<1:0> are in CPSR<26:25>
 *	ITSTATE<7:2> are in CPSR<15:10>
 */
अटल अंतरभूत अचिन्हित दीर्घ it_advance(अचिन्हित दीर्घ cpsr)
	अणु
	अगर ((cpsr & 0x06000400) == 0) अणु
		/* ITSTATE<2:0> == 0 means end of IT block, so clear IT state */
		cpsr &= ~PSR_IT_MASK;
	पूर्ण अन्यथा अणु
		/* We need to shअगरt left ITSTATE<4:0> */
		स्थिर अचिन्हित दीर्घ mask = 0x06001c00;  /* Mask ITSTATE<4:0> */
		अचिन्हित दीर्घ it = cpsr & mask;
		it <<= 1;
		it |= it >> (27 - 10);  /* Carry ITSTATE<2> to correct place */
		it &= mask;
		cpsr &= ~mask;
		cpsr |= it;
	पूर्ण
	वापस cpsr;
पूर्ण

अटल अंतरभूत व्योम __kprobes bx_ग_लिखो_pc(दीर्घ pcv, काष्ठा pt_regs *regs)
अणु
	दीर्घ cpsr = regs->ARM_cpsr;
	अगर (pcv & 0x1) अणु
		cpsr |= PSR_T_BIT;
		pcv &= ~0x1;
	पूर्ण अन्यथा अणु
		cpsr &= ~PSR_T_BIT;
		pcv &= ~0x2;	/* Aव्योम UNPREDICTABLE address allignment */
	पूर्ण
	regs->ARM_cpsr = cpsr;
	regs->ARM_pc = pcv;
पूर्ण


#अगर __LINUX_ARM_ARCH__ >= 6

/* Kernels built क्रम >= ARMv6 should never run on <= ARMv5 hardware, so... */
#घोषणा load_ग_लिखो_pc_पूर्णांकerworks true
#घोषणा test_load_ग_लिखो_pc_पूर्णांकerworking()

#अन्यथा /* __LINUX_ARM_ARCH__ < 6 */

/* We need run-समय testing to determine अगर load_ग_लिखो_pc() should पूर्णांकerwork. */
बाह्य bool load_ग_लिखो_pc_पूर्णांकerworks;
व्योम __init test_load_ग_लिखो_pc_पूर्णांकerworking(व्योम);

#पूर्ण_अगर

अटल अंतरभूत व्योम __kprobes load_ग_लिखो_pc(दीर्घ pcv, काष्ठा pt_regs *regs)
अणु
	अगर (load_ग_लिखो_pc_पूर्णांकerworks)
		bx_ग_लिखो_pc(pcv, regs);
	अन्यथा
		regs->ARM_pc = pcv;
पूर्ण


#अगर __LINUX_ARM_ARCH__ >= 7

#घोषणा alu_ग_लिखो_pc_पूर्णांकerworks true
#घोषणा test_alu_ग_लिखो_pc_पूर्णांकerworking()

#या_अगर __LINUX_ARM_ARCH__ <= 5

/* Kernels built क्रम <= ARMv5 should never run on >= ARMv6 hardware, so... */
#घोषणा alu_ग_लिखो_pc_पूर्णांकerworks false
#घोषणा test_alu_ग_लिखो_pc_पूर्णांकerworking()

#अन्यथा /* __LINUX_ARM_ARCH__ == 6 */

/* We could be an ARMv6 binary on ARMv7 hardware so we need a run-समय check. */
बाह्य bool alu_ग_लिखो_pc_पूर्णांकerworks;
व्योम __init test_alu_ग_लिखो_pc_पूर्णांकerworking(व्योम);

#पूर्ण_अगर /* __LINUX_ARM_ARCH__ == 6 */

अटल अंतरभूत व्योम __kprobes alu_ग_लिखो_pc(दीर्घ pcv, काष्ठा pt_regs *regs)
अणु
	अगर (alu_ग_लिखो_pc_पूर्णांकerworks)
		bx_ग_लिखो_pc(pcv, regs);
	अन्यथा
		regs->ARM_pc = pcv;
पूर्ण


/*
 * Test अगर load/store inकाष्ठाions ग_लिखोback the address रेजिस्टर.
 * अगर P (bit 24) == 0 or W (bit 21) == 1
 */
#घोषणा is_ग_लिखोback(insn) ((insn ^ 0x01000000) & 0x01200000)

/*
 * The following definitions and macros are used to build inकाष्ठाion
 * decoding tables क्रम use by probes_decode_insn.
 *
 * These tables are a concatenation of entries each of which consist of one of
 * the decode_* काष्ठाs. All of the fields in every type of decode काष्ठाure
 * are of the जोड़ type decode_item, thereक्रमe the entire decode table can be
 * viewed as an array of these and declared like:
 *
 *	अटल स्थिर जोड़ decode_item table_name[] = अणुपूर्ण;
 *
 * In order to स्थिरruct each entry in the table, macros are used to
 * initialise a number of sequential decode_item values in a layout which
 * matches the relevant काष्ठा. E.g. DECODE_SIMULATE initialise a काष्ठा
 * decode_simulate by initialising four decode_item objects like this...
 *
 *	अणु.bits = _typeपूर्ण,
 *	अणु.bits = _maskपूर्ण,
 *	अणु.bits = _valueपूर्ण,
 *	अणु.action = _handlerपूर्ण,
 *
 * Initialising a specअगरied member of the जोड़ means that the compiler
 * will produce a warning अगर the argument is of an incorrect type.
 *
 * Below is a list of each of the macros used to initialise entries and a
 * description of the action perक्रमmed when that entry is matched to an
 * inकाष्ठाion. A match is found when (inकाष्ठाion & mask) == value.
 *
 * DECODE_TABLE(mask, value, table)
 *	Inकाष्ठाion decoding jumps to parsing the new sub-table 'table'.
 *
 * DECODE_CUSTOM(mask, value, decoder)
 *	The value of 'decoder' is used as an index पूर्णांकo the array of
 *	action functions, and the retrieved decoder function is invoked
 *	to complete decoding of the inकाष्ठाion.
 *
 * DECODE_SIMULATE(mask, value, handler)
 *	The probes inकाष्ठाion handler is set to the value found by
 *	indexing पूर्णांकo the action array using the value of 'handler'. This
 *	will be used to simulate the inकाष्ठाion when the probe is hit.
 *	Decoding वापसs with INSN_GOOD_NO_SLOT.
 *
 * DECODE_EMULATE(mask, value, handler)
 *	The probes inकाष्ठाion handler is set to the value found by
 *	indexing पूर्णांकo the action array using the value of 'handler'. This
 *	will be used to emulate the inकाष्ठाion when the probe is hit. The
 *	modअगरied inकाष्ठाion (see below) is placed in the probes inकाष्ठाion
 *	slot so it may be called by the emulation code. Decoding वापसs
 *	with INSN_GOOD.
 *
 * DECODE_REJECT(mask, value)
 *	Inकाष्ठाion decoding fails with INSN_REJECTED
 *
 * DECODE_OR(mask, value)
 *	This allows the mask/value test of multiple table entries to be
 *	logically ORed. Once an 'or' entry is matched the decoding action to
 *	be perक्रमmed is that of the next entry which isn't an 'or'. E.g.
 *
 *		DECODE_OR	(mask1, value1)
 *		DECODE_OR	(mask2, value2)
 *		DECODE_SIMULATE	(mask3, value3, simulation_handler)
 *
 *	This means that अगर any of the three mask/value pairs match the
 *	inकाष्ठाion being decoded, then 'simulation_handler' will be used
 *	क्रम it.
 *
 * Both the SIMULATE and EMULATE macros have a second क्रमm which take an
 * additional 'regs' argument.
 *
 *	DECODE_SIMULATEX(mask, value, handler, regs)
 *	DECODE_EMULATEX	(mask, value, handler, regs)
 *
 * These are used to specअगरy what kind of CPU रेजिस्टर is encoded in each of the
 * least signअगरicant 5 nibbles of the inकाष्ठाion being decoded. The regs value
 * is specअगरied using the REGS macro, this takes any of the REG_TYPE_* values
 * from क्रमागत decode_reg_type as arguments; only the '*' part of the name is
 * given. E.g.
 *
 *	REGS(0, ANY, NOPC, 0, ANY)
 *
 * This indicates an inकाष्ठाion is encoded like:
 *
 *	bits 19..16	ignore
 *	bits 15..12	any रेजिस्टर allowed here
 *	bits 11.. 8	any रेजिस्टर except PC allowed here
 *	bits  7.. 4	ignore
 *	bits  3.. 0	any रेजिस्टर allowed here
 *
 * This रेजिस्टर specअगरication is checked after a decode table entry is found to
 * match an inकाष्ठाion (through the mask/value test). Any invalid रेजिस्टर then
 * found in the inकाष्ठाion will cause decoding to fail with INSN_REJECTED. In
 * the above example this would happen अगर bits 11..8 of the inकाष्ठाion were
 * 1111, indicating R15 or PC.
 *
 * As well as checking क्रम legal combinations of रेजिस्टरs, this data is also
 * used to modअगरy the रेजिस्टरs encoded in the inकाष्ठाions so that an
 * emulation routines can use it. (See decode_regs() and INSN_NEW_BITS.)
 *
 * Here is a real example which matches ARM inकाष्ठाions of the क्रमm
 * "AND <Rd>,<Rn>,<Rm>,<shift> <Rs>"
 *
 *	DECODE_EMULATEX	(0x0e000090, 0x00000010, PROBES_DATA_PROCESSING_REG,
 *						 REGS(ANY, ANY, NOPC, 0, ANY)),
 *						      ^    ^    ^        ^
 *						      Rn   Rd   Rs       Rm
 *
 * Decoding the inकाष्ठाion "AND R4, R5, R6, ASL R15" will be rejected because
 * Rs == R15
 *
 * Decoding the inकाष्ठाion "AND R4, R5, R6, ASL R7" will be accepted and the
 * inकाष्ठाion will be modअगरied to "AND R0, R2, R3, ASL R1" and then placed पूर्णांकo
 * the kprobes inकाष्ठाion slot. This can then be called later by the handler
 * function emulate_rd12rn16rm0rs8_rwflags (a poपूर्णांकer to which is retrieved from
 * the indicated slot in the action array), in order to simulate the inकाष्ठाion.
 */

क्रमागत decode_type अणु
	DECODE_TYPE_END,
	DECODE_TYPE_TABLE,
	DECODE_TYPE_CUSTOM,
	DECODE_TYPE_SIMULATE,
	DECODE_TYPE_EMULATE,
	DECODE_TYPE_OR,
	DECODE_TYPE_REJECT,
	NUM_DECODE_TYPES /* Must be last क्रमागत */
पूर्ण;

#घोषणा DECODE_TYPE_BITS	4
#घोषणा DECODE_TYPE_MASK	((1 << DECODE_TYPE_BITS) - 1)

क्रमागत decode_reg_type अणु
	REG_TYPE_NONE = 0, /* Not a रेजिस्टर, ignore */
	REG_TYPE_ANY,	   /* Any रेजिस्टर allowed */
	REG_TYPE_SAMEAS16, /* Register should be same as that at bits 19..16 */
	REG_TYPE_SP,	   /* Register must be SP */
	REG_TYPE_PC,	   /* Register must be PC */
	REG_TYPE_NOSP,	   /* Register must not be SP */
	REG_TYPE_NOSPPC,   /* Register must not be SP or PC */
	REG_TYPE_NOPC,	   /* Register must not be PC */
	REG_TYPE_NOPCWB,   /* No PC अगर load/store ग_लिखो-back flag also set */

	/* The following types are used when the encoding क्रम PC indicates
	 * another inकाष्ठाion क्रमm. This distiction only matters क्रम test
	 * हाल coverage checks.
	 */
	REG_TYPE_NOPCX,	   /* Register must not be PC */
	REG_TYPE_NOSPPCX,  /* Register must not be SP or PC */

	/* Alias to allow '0' arg to be used in REGS macro. */
	REG_TYPE_0 = REG_TYPE_NONE
पूर्ण;

#घोषणा REGS(r16, r12, r8, r4, r0)	\
	(((REG_TYPE_##r16) << 16) +	\
	((REG_TYPE_##r12) << 12) +	\
	((REG_TYPE_##r8) << 8) +	\
	((REG_TYPE_##r4) << 4) +	\
	(REG_TYPE_##r0))

जोड़ decode_item अणु
	u32			bits;
	स्थिर जोड़ decode_item	*table;
	पूर्णांक			action;
पूर्ण;

काष्ठा decode_header;
प्रकार क्रमागत probes_insn (probes_custom_decode_t)(probes_opcode_t,
						  काष्ठा arch_probes_insn *,
						  स्थिर काष्ठा decode_header *);

जोड़ decode_action अणु
	probes_insn_handler_t	*handler;
	probes_custom_decode_t	*decoder;
पूर्ण;

प्रकार क्रमागत probes_insn (probes_check_t)(probes_opcode_t,
					   काष्ठा arch_probes_insn *,
					   स्थिर काष्ठा decode_header *);

काष्ठा decode_checker अणु
	probes_check_t	*checker;
पूर्ण;

#घोषणा DECODE_END			\
	अणु.bits = DECODE_TYPE_ENDपूर्ण


काष्ठा decode_header अणु
	जोड़ decode_item	type_regs;
	जोड़ decode_item	mask;
	जोड़ decode_item	value;
पूर्ण;

#घोषणा DECODE_HEADER(_type, _mask, _value, _regs)		\
	अणु.bits = (_type) | ((_regs) << DECODE_TYPE_BITS)पूर्ण,	\
	अणु.bits = (_mask)पूर्ण,					\
	अणु.bits = (_value)पूर्ण


काष्ठा decode_table अणु
	काष्ठा decode_header	header;
	जोड़ decode_item	table;
पूर्ण;

#घोषणा DECODE_TABLE(_mask, _value, _table)			\
	DECODE_HEADER(DECODE_TYPE_TABLE, _mask, _value, 0),	\
	अणु.table = (_table)पूर्ण


काष्ठा decode_custom अणु
	काष्ठा decode_header	header;
	जोड़ decode_item	decoder;
पूर्ण;

#घोषणा DECODE_CUSTOM(_mask, _value, _decoder)			\
	DECODE_HEADER(DECODE_TYPE_CUSTOM, _mask, _value, 0),	\
	अणु.action = (_decoder)पूर्ण


काष्ठा decode_simulate अणु
	काष्ठा decode_header	header;
	जोड़ decode_item	handler;
पूर्ण;

#घोषणा DECODE_SIMULATEX(_mask, _value, _handler, _regs)		\
	DECODE_HEADER(DECODE_TYPE_SIMULATE, _mask, _value, _regs),	\
	अणु.action = (_handler)पूर्ण

#घोषणा DECODE_SIMULATE(_mask, _value, _handler)	\
	DECODE_SIMULATEX(_mask, _value, _handler, 0)


काष्ठा decode_emulate अणु
	काष्ठा decode_header	header;
	जोड़ decode_item	handler;
पूर्ण;

#घोषणा DECODE_EMULATEX(_mask, _value, _handler, _regs)			\
	DECODE_HEADER(DECODE_TYPE_EMULATE, _mask, _value, _regs),	\
	अणु.action = (_handler)पूर्ण

#घोषणा DECODE_EMULATE(_mask, _value, _handler)		\
	DECODE_EMULATEX(_mask, _value, _handler, 0)


काष्ठा decode_or अणु
	काष्ठा decode_header	header;
पूर्ण;

#घोषणा DECODE_OR(_mask, _value)				\
	DECODE_HEADER(DECODE_TYPE_OR, _mask, _value, 0)

क्रमागत probes_insn अणु
	INSN_REJECTED,
	INSN_GOOD,
	INSN_GOOD_NO_SLOT
पूर्ण;

काष्ठा decode_reject अणु
	काष्ठा decode_header	header;
पूर्ण;

#घोषणा DECODE_REJECT(_mask, _value)				\
	DECODE_HEADER(DECODE_TYPE_REJECT, _mask, _value, 0)

probes_insn_handler_t probes_simulate_nop;
probes_insn_handler_t probes_emulate_none;

पूर्णांक __kprobes
probes_decode_insn(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर जोड़ decode_item *table, bool thumb, bool emulate,
		स्थिर जोड़ decode_action *actions,
		स्थिर काष्ठा decode_checker **checkers);

#पूर्ण_अगर

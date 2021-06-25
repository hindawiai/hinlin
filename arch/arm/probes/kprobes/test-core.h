<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/probes/kprobes/test-core.h
 *
 * Copyright (C) 2011 Jon Medhurst <tixy@yxit.co.uk>.
 */

#घोषणा VERBOSE 0 /* Set to '1' क्रम more logging of test हालs */

#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा NORMAL_ISA "16"
#अन्यथा
#घोषणा NORMAL_ISA "32"
#पूर्ण_अगर


/* Flags used in kprobe_test_flags */
#घोषणा TEST_FLAG_NO_ITBLOCK	(1<<0)
#घोषणा TEST_FLAG_FULL_ITBLOCK	(1<<1)
#घोषणा TEST_FLAG_NARROW_INSTR	(1<<2)

बाह्य पूर्णांक kprobe_test_flags;
बाह्य पूर्णांक kprobe_test_cc_position;


#घोषणा TEST_MEMORY_SIZE 256


/*
 * Test हाल काष्ठाures.
 *
 * The arguments given to test हालs can be one of three types.
 *
 *   ARG_TYPE_REG
 *	Load a रेजिस्टर with the given value.
 *
 *   ARG_TYPE_PTR
 *	Load a रेजिस्टर with a poपूर्णांकer पूर्णांकo the stack buffer (SP + given value).
 *
 *   ARG_TYPE_MEM
 *	Store the given value पूर्णांकo the stack buffer at [SP+index].
 *
 */

#घोषणा	ARG_TYPE_END		0
#घोषणा	ARG_TYPE_REG		1
#घोषणा	ARG_TYPE_PTR		2
#घोषणा	ARG_TYPE_MEM		3
#घोषणा	ARG_TYPE_REG_MASKED	4

#घोषणा ARG_FLAG_UNSUPPORTED	0x01
#घोषणा ARG_FLAG_SUPPORTED	0x02
#घोषणा ARG_FLAG_THUMB		0x10	/* Must be 16 so TEST_ISA can be used */
#घोषणा ARG_FLAG_ARM		0x20	/* Must be 32 so TEST_ISA can be used */

काष्ठा test_arg अणु
	u8	type;		/* ARG_TYPE_x */
	u8	_padding[7];
पूर्ण;

काष्ठा test_arg_regptr अणु
	u8	type;		/* ARG_TYPE_REG or ARG_TYPE_PTR or ARG_TYPE_REG_MASKED */
	u8	reg;
	u8	_padding[2];
	u32	val;
पूर्ण;

काष्ठा test_arg_mem अणु
	u8	type;		/* ARG_TYPE_MEM */
	u8	index;
	u8	_padding[2];
	u32	val;
पूर्ण;

काष्ठा test_arg_end अणु
	u8	type;		/* ARG_TYPE_END */
	u8	flags;		/* ARG_FLAG_x */
	u16	code_offset;
	u16	branch_offset;
	u16	end_offset;
पूर्ण;


/*
 * Building blocks क्रम test हालs.
 *
 * Each test हाल is wrapped between TESTCASE_START and TESTCASE_END.
 *
 * To specअगरy arguments क्रम a test हाल the TEST_ARG_अणुREG,PTR,MEMपूर्ण macros are
 * used followed by a terminating TEST_ARG_END.
 *
 * After this, the inकाष्ठाion to be tested is defined with TEST_INSTRUCTION.
 * Or क्रम branches, TEST_BRANCH_B and TEST_BRANCH_F (branch क्रमwards/backwards).
 *
 * Some specअगरic test हालs may make use of other custom स्थिरructs.
 */

#अगर VERBOSE
#घोषणा verbose(fmt, ...) pr_info(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा verbose(fmt, ...)
#पूर्ण_अगर

#घोषणा TEST_GROUP(title)					\
	verbose("\n");						\
	verbose(title"\n");					\
	verbose("---------------------------------------------------------\n");

#घोषणा TESTCASE_START(title)					\
	__यंत्र__ __अस्थिर__ (					\
	".syntax unified				\n\t"	\
	"bl	__kprobes_test_case_start		\n\t"	\
	".pushsection .rodata				\n\t"	\
	"10:						\n\t"	\
	/* करोn't use .asciz here as 'title' may be */		\
	/* multiple strings to be concatenated.  */		\
	".ascii "#title"				\n\t"	\
	".byte	0					\n\t"	\
	".popsection					\n\t"	\
	".word	10b					\n\t"

#घोषणा	TEST_ARG_REG(reg, val)					\
	".byte	"__stringअगरy(ARG_TYPE_REG)"		\n\t"	\
	".byte	"#reg"					\n\t"	\
	".short	0					\n\t"	\
	".word	"#val"					\n\t"

#घोषणा	TEST_ARG_PTR(reg, val)					\
	".byte	"__stringअगरy(ARG_TYPE_PTR)"		\n\t"	\
	".byte	"#reg"					\n\t"	\
	".short	0					\n\t"	\
	".word	"#val"					\n\t"

#घोषणा	TEST_ARG_MEM(index, val)				\
	".byte	"__stringअगरy(ARG_TYPE_MEM)"		\n\t"	\
	".byte	"#index"				\n\t"	\
	".short	0					\n\t"	\
	".word	"#val"					\n\t"

#घोषणा	TEST_ARG_REG_MASKED(reg, val)				\
	".byte	"__stringअगरy(ARG_TYPE_REG_MASKED)"	\n\t"	\
	".byte	"#reg"					\n\t"	\
	".short	0					\n\t"	\
	".word	"#val"					\n\t"

#घोषणा	TEST_ARG_END(flags)					\
	".byte	"__stringअगरy(ARG_TYPE_END)"		\n\t"	\
	".byte	"TEST_ISA flags"			\n\t"	\
	".short	50f-0f					\n\t"	\
	".short	2f-0f					\n\t"	\
	".short	99f-0f					\n\t"	\
	".code "TEST_ISA"				\n\t"	\
	"0:						\n\t"

#घोषणा TEST_INSTRUCTION(inकाष्ठाion)				\
	"50:	nop					\n\t"	\
	"1:	"inकाष्ठाion"				\n\t"	\
	"	nop					\n\t"

#घोषणा TEST_BRANCH_F(inकाष्ठाion)				\
	TEST_INSTRUCTION(inकाष्ठाion)				\
	"	b	99f				\n\t"	\
	"2:	nop					\n\t"

#घोषणा TEST_BRANCH_B(inकाष्ठाion)				\
	"	b	50f				\n\t"	\
	"	b	99f				\n\t"	\
	"2:	nop					\n\t"	\
	"	b	99f				\n\t"	\
	TEST_INSTRUCTION(inकाष्ठाion)

#घोषणा TEST_BRANCH_FX(inकाष्ठाion, codex)			\
	TEST_INSTRUCTION(inकाष्ठाion)				\
	"	b	99f				\n\t"	\
	codex"						\n\t"	\
	"	b	99f				\n\t"	\
	"2:	nop					\n\t"

#घोषणा TEST_BRANCH_BX(inकाष्ठाion, codex)			\
	"	b	50f				\n\t"	\
	"	b	99f				\n\t"	\
	"2:	nop					\n\t"	\
	"	b	99f				\n\t"	\
	codex"						\n\t"	\
	TEST_INSTRUCTION(inकाष्ठाion)

#घोषणा TESTCASE_END						\
	"2:						\n\t"	\
	"99:						\n\t"	\
	"	bl __kprobes_test_case_end_"TEST_ISA"	\n\t"	\
	".code "NORMAL_ISA"				\n\t"	\
	: :							\
	: "r0", "r1", "r2", "r3", "ip", "lr", "memory", "cc"	\
	);


/*
 * Macros to define test हालs.
 *
 * Those of the क्रमm TEST_अणुR,P,Mपूर्ण* can be used to define test हालs
 * which take combinations of the three basic types of arguments. E.g.
 *
 *   TEST_R	One रेजिस्टर argument
 *   TEST_RR	Two रेजिस्टर arguments
 *   TEST_RPR	A रेजिस्टर, a poपूर्णांकer, then a रेजिस्टर argument
 *
 * For testing inकाष्ठाions which may branch, there are macros TEST_BF_*
 * and TEST_BB_* क्रम branching क्रमwards and backwards.
 *
 * TEST_SUPPORTED and TEST_UNSUPPORTED करोn't cause the code to be executed,
 * the just verअगरy that a kprobe is or is not allowed on the given inकाष्ठाion.
 */

#घोषणा TEST(code)				\
	TESTCASE_START(code)			\
	TEST_ARG_END("")			\
	TEST_INSTRUCTION(code)			\
	TESTCASE_END

#घोषणा TEST_UNSUPPORTED(code)					\
	TESTCASE_START(code)					\
	TEST_ARG_END("|"__stringअगरy(ARG_FLAG_UNSUPPORTED))	\
	TEST_INSTRUCTION(code)					\
	TESTCASE_END

#घोषणा TEST_SUPPORTED(code)					\
	TESTCASE_START(code)					\
	TEST_ARG_END("|"__stringअगरy(ARG_FLAG_SUPPORTED))	\
	TEST_INSTRUCTION(code)					\
	TESTCASE_END

#घोषणा TEST_R(code1, reg, val, code2)			\
	TESTCASE_START(code1 #reg code2)		\
	TEST_ARG_REG(reg, val)				\
	TEST_ARG_END("")				\
	TEST_INSTRUCTION(code1 #reg code2)		\
	TESTCASE_END

#घोषणा TEST_RR(code1, reg1, val1, code2, reg2, val2, code3)	\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3)		\
	TEST_ARG_REG(reg1, val1)				\
	TEST_ARG_REG(reg2, val2)				\
	TEST_ARG_END("")					\
	TEST_INSTRUCTION(code1 #reg1 code2 #reg2 code3)		\
	TESTCASE_END

#घोषणा TEST_RRR(code1, reg1, val1, code2, reg2, val2, code3, reg3, val3, code4)\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3 #reg3 code4)		\
	TEST_ARG_REG(reg1, val1)						\
	TEST_ARG_REG(reg2, val2)						\
	TEST_ARG_REG(reg3, val3)						\
	TEST_ARG_END("")							\
	TEST_INSTRUCTION(code1 #reg1 code2 #reg2 code3 #reg3 code4)		\
	TESTCASE_END

#घोषणा TEST_RRRR(code1, reg1, val1, code2, reg2, val2, code3, reg3, val3, code4, reg4, val4)	\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3 #reg3 code4 #reg4)		\
	TEST_ARG_REG(reg1, val1)						\
	TEST_ARG_REG(reg2, val2)						\
	TEST_ARG_REG(reg3, val3)						\
	TEST_ARG_REG(reg4, val4)						\
	TEST_ARG_END("")							\
	TEST_INSTRUCTION(code1 #reg1 code2 #reg2 code3 #reg3 code4 #reg4)	\
	TESTCASE_END

#घोषणा TEST_P(code1, reg1, val1, code2)	\
	TESTCASE_START(code1 #reg1 code2)	\
	TEST_ARG_PTR(reg1, val1)		\
	TEST_ARG_END("")			\
	TEST_INSTRUCTION(code1 #reg1 code2)	\
	TESTCASE_END

#घोषणा TEST_PR(code1, reg1, val1, code2, reg2, val2, code3)	\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3)		\
	TEST_ARG_PTR(reg1, val1)				\
	TEST_ARG_REG(reg2, val2)				\
	TEST_ARG_END("")					\
	TEST_INSTRUCTION(code1 #reg1 code2 #reg2 code3)		\
	TESTCASE_END

#घोषणा TEST_RP(code1, reg1, val1, code2, reg2, val2, code3)	\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3)		\
	TEST_ARG_REG(reg1, val1)				\
	TEST_ARG_PTR(reg2, val2)				\
	TEST_ARG_END("")					\
	TEST_INSTRUCTION(code1 #reg1 code2 #reg2 code3)		\
	TESTCASE_END

#घोषणा TEST_PRR(code1, reg1, val1, code2, reg2, val2, code3, reg3, val3, code4)\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3 #reg3 code4)		\
	TEST_ARG_PTR(reg1, val1)						\
	TEST_ARG_REG(reg2, val2)						\
	TEST_ARG_REG(reg3, val3)						\
	TEST_ARG_END("")							\
	TEST_INSTRUCTION(code1 #reg1 code2 #reg2 code3 #reg3 code4)		\
	TESTCASE_END

#घोषणा TEST_RPR(code1, reg1, val1, code2, reg2, val2, code3, reg3, val3, code4)\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3 #reg3 code4)		\
	TEST_ARG_REG(reg1, val1)						\
	TEST_ARG_PTR(reg2, val2)						\
	TEST_ARG_REG(reg3, val3)						\
	TEST_ARG_END("")							\
	TEST_INSTRUCTION(code1 #reg1 code2 #reg2 code3 #reg3 code4)		\
	TESTCASE_END

#घोषणा TEST_RRP(code1, reg1, val1, code2, reg2, val2, code3, reg3, val3, code4)\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3 #reg3 code4)		\
	TEST_ARG_REG(reg1, val1)						\
	TEST_ARG_REG(reg2, val2)						\
	TEST_ARG_PTR(reg3, val3)						\
	TEST_ARG_END("")							\
	TEST_INSTRUCTION(code1 #reg1 code2 #reg2 code3 #reg3 code4)		\
	TESTCASE_END

#घोषणा TEST_BF_P(code1, reg1, val1, code2)	\
	TESTCASE_START(code1 #reg1 code2)	\
	TEST_ARG_PTR(reg1, val1)		\
	TEST_ARG_END("")			\
	TEST_BRANCH_F(code1 #reg1 code2)	\
	TESTCASE_END

#घोषणा TEST_BF(code)				\
	TESTCASE_START(code)			\
	TEST_ARG_END("")			\
	TEST_BRANCH_F(code)			\
	TESTCASE_END

#घोषणा TEST_BB(code)				\
	TESTCASE_START(code)			\
	TEST_ARG_END("")			\
	TEST_BRANCH_B(code)			\
	TESTCASE_END

#घोषणा TEST_BF_R(code1, reg, val, code2)	\
	TESTCASE_START(code1 #reg code2)	\
	TEST_ARG_REG(reg, val)			\
	TEST_ARG_END("")			\
	TEST_BRANCH_F(code1 #reg code2)		\
	TESTCASE_END

#घोषणा TEST_BB_R(code1, reg, val, code2)	\
	TESTCASE_START(code1 #reg code2)	\
	TEST_ARG_REG(reg, val)			\
	TEST_ARG_END("")			\
	TEST_BRANCH_B(code1 #reg code2)		\
	TESTCASE_END

#घोषणा TEST_BF_RR(code1, reg1, val1, code2, reg2, val2, code3)	\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3)		\
	TEST_ARG_REG(reg1, val1)				\
	TEST_ARG_REG(reg2, val2)				\
	TEST_ARG_END("")					\
	TEST_BRANCH_F(code1 #reg1 code2 #reg2 code3)		\
	TESTCASE_END

#घोषणा TEST_BF_X(code, codex)			\
	TESTCASE_START(code)			\
	TEST_ARG_END("")			\
	TEST_BRANCH_FX(code, codex)		\
	TESTCASE_END

#घोषणा TEST_BB_X(code, codex)			\
	TESTCASE_START(code)			\
	TEST_ARG_END("")			\
	TEST_BRANCH_BX(code, codex)		\
	TESTCASE_END

#घोषणा TEST_BF_RX(code1, reg, val, code2, codex)	\
	TESTCASE_START(code1 #reg code2)		\
	TEST_ARG_REG(reg, val)				\
	TEST_ARG_END("")				\
	TEST_BRANCH_FX(code1 #reg code2, codex)		\
	TESTCASE_END

#घोषणा TEST_X(code, codex)			\
	TESTCASE_START(code)			\
	TEST_ARG_END("")			\
	TEST_INSTRUCTION(code)			\
	"	b	99f		\n\t"	\
	"	"codex"			\n\t"	\
	TESTCASE_END

#घोषणा TEST_RX(code1, reg, val, code2, codex)		\
	TESTCASE_START(code1 #reg code2)		\
	TEST_ARG_REG(reg, val)				\
	TEST_ARG_END("")				\
	TEST_INSTRUCTION(code1 __stringअगरy(reg) code2)	\
	"	b	99f		\n\t"		\
	"	"codex"			\n\t"		\
	TESTCASE_END

#घोषणा TEST_RRX(code1, reg1, val1, code2, reg2, val2, code3, codex)		\
	TESTCASE_START(code1 #reg1 code2 #reg2 code3)				\
	TEST_ARG_REG(reg1, val1)						\
	TEST_ARG_REG(reg2, val2)						\
	TEST_ARG_END("")							\
	TEST_INSTRUCTION(code1 __stringअगरy(reg1) code2 __stringअगरy(reg2) code3)	\
	"	b	99f		\n\t"					\
	"	"codex"			\n\t"					\
	TESTCASE_END

#घोषणा TEST_RMASKED(code1, reg, mask, code2)		\
	TESTCASE_START(code1 #reg code2)		\
	TEST_ARG_REG_MASKED(reg, mask)			\
	TEST_ARG_END("")				\
	TEST_INSTRUCTION(code1 #reg code2)		\
	TESTCASE_END

/*
 * We ignore the state of the imprecise पात disable flag (CPSR.A) because this
 * can change अक्रमomly as the kernel करोesn't take care to preserve or initialise
 * this across context चयनes. Also, with Security Extensions, the flag may
 * not be under control of the kernel; क्रम this reason we ignore the state of
 * the FIQ disable flag CPSR.F as well.
 */
#घोषणा PSR_IGNORE_BITS (PSR_A_BIT | PSR_F_BIT)


/*
 * Macros क्रम defining space directives spपढ़ो over multiple lines.
 * These are required so the compiler guesses better the length of अंतरभूत यंत्र
 * code and will spill the literal pool early enough to aव्योम generating PC
 * relative loads with out of range offsets.
 */
#घोषणा TWICE(x)	x x
#घोषणा SPACE_0x8	TWICE(".space 4\n\t")
#घोषणा SPACE_0x10	TWICE(SPACE_0x8)
#घोषणा SPACE_0x20	TWICE(SPACE_0x10)
#घोषणा SPACE_0x40	TWICE(SPACE_0x20)
#घोषणा SPACE_0x80	TWICE(SPACE_0x40)
#घोषणा SPACE_0x100	TWICE(SPACE_0x80)
#घोषणा SPACE_0x200	TWICE(SPACE_0x100)
#घोषणा SPACE_0x400	TWICE(SPACE_0x200)
#घोषणा SPACE_0x800	TWICE(SPACE_0x400)
#घोषणा SPACE_0x1000	TWICE(SPACE_0x800)


/* Various values used in test हालs... */
#घोषणा N(val)	(val ^ 0xffffffff)
#घोषणा VAL1	0x12345678
#घोषणा VAL2	N(VAL1)
#घोषणा VAL3	0xa5f801
#घोषणा VAL4	N(VAL3)
#घोषणा VALM	0x456789ab
#घोषणा VALR	0xdeaddead
#घोषणा HH1	0x0123fecb
#घोषणा HH2	0xa9874567


#अगर_घोषित CONFIG_THUMB2_KERNEL
व्योम kprobe_thumb16_test_हालs(व्योम);
व्योम kprobe_thumb32_test_हालs(व्योम);
#अन्यथा
व्योम kprobe_arm_test_हालs(व्योम);
#पूर्ण_अगर

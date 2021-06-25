<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *
 *  Derived from "include/asm-i386/timex.h"
 *    Copyright (C) 1992, Linus Torvalds
 */

#अगर_अघोषित _ASM_S390_TIMEX_H
#घोषणा _ASM_S390_TIMEX_H

#समावेश <linux/preempt.h>
#समावेश <linux/समय64.h>
#समावेश <यंत्र/lowcore.h>

/* The value of the TOD घड़ी क्रम 1.1.1970. */
#घोषणा TOD_UNIX_EPOCH 0x7d91048bca000000ULL

बाह्य u64 घड़ी_comparator_max;

जोड़ tod_घड़ी अणु
	__uपूर्णांक128_t val;
	काष्ठा अणु
		__uपूर्णांक128_t ei	:  8; /* epoch index */
		__uपूर्णांक128_t tod : 64; /* bits 0-63 of tod घड़ी */
		__uपूर्णांक128_t	: 40;
		__uपूर्णांक128_t pf	: 16; /* programmable field */
	पूर्ण;
	काष्ठा अणु
		__uपूर्णांक128_t eitod : 72; /* epoch index + bits 0-63 tod घड़ी */
		__uपूर्णांक128_t	  : 56;
	पूर्ण;
	काष्ठा अणु
		__uपूर्णांक128_t us	: 60; /* micro-seconds */
		__uपूर्णांक128_t sus	: 12; /* sub-microseconds */
		__uपूर्णांक128_t	: 56;
	पूर्ण;
पूर्ण __packed;

/* Inline functions क्रम घड़ी रेजिस्टर access. */
अटल अंतरभूत पूर्णांक set_tod_घड़ी(__u64 समय)
अणु
	पूर्णांक cc;

	यंत्र अस्थिर(
		"   sck   %1\n"
		"   ipm   %0\n"
		"   srl   %0,28\n"
		: "=d" (cc) : "Q" (समय) : "cc");
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक store_tod_घड़ी_ext_cc(जोड़ tod_घड़ी *clk)
अणु
	पूर्णांक cc;

	यंत्र अस्थिर(
		"   stcke  %1\n"
		"   ipm   %0\n"
		"   srl   %0,28\n"
		: "=d" (cc), "=Q" (*clk) : : "cc");
	वापस cc;
पूर्ण

अटल अंतरभूत व्योम store_tod_घड़ी_ext(जोड़ tod_घड़ी *tod)
अणु
	यंत्र अस्थिर("stcke %0" : "=Q" (*tod) : : "cc");
पूर्ण

अटल अंतरभूत व्योम set_घड़ी_comparator(__u64 समय)
अणु
	यंत्र अस्थिर("sckc %0" : : "Q" (समय));
पूर्ण

अटल अंतरभूत व्योम set_tod_programmable_field(u16 val)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र("0") = val;

	यंत्र अस्थिर("sckpf" : : "d" (reg0));
पूर्ण

व्योम घड़ी_comparator_work(व्योम);

व्योम __init समय_early_init(व्योम);

बाह्य अचिन्हित अक्षर ptff_function_mask[16];

/* Function codes क्रम the ptff inकाष्ठाion. */
#घोषणा PTFF_QAF	0x00	/* query available functions */
#घोषणा PTFF_QTO	0x01	/* query tod offset */
#घोषणा PTFF_QSI	0x02	/* query steering inक्रमmation */
#घोषणा PTFF_QUI	0x04	/* query UTC inक्रमmation */
#घोषणा PTFF_ATO	0x40	/* adjust tod offset */
#घोषणा PTFF_STO	0x41	/* set tod offset */
#घोषणा PTFF_SFS	0x42	/* set fine steering rate */
#घोषणा PTFF_SGS	0x43	/* set gross steering rate */

/* Query TOD offset result */
काष्ठा ptff_qto अणु
	अचिन्हित दीर्घ physical_घड़ी;
	अचिन्हित दीर्घ tod_offset;
	अचिन्हित दीर्घ logical_tod_offset;
	अचिन्हित दीर्घ tod_epoch_dअगरference;
पूर्ण __packed;

अटल अंतरभूत पूर्णांक ptff_query(अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित अक्षर *ptr;

	ptr = ptff_function_mask + (nr >> 3);
	वापस (*ptr & (0x80 >> (nr & 7))) != 0;
पूर्ण

/* Query UTC inक्रमmation result */
काष्ठा ptff_qui अणु
	अचिन्हित पूर्णांक पंचांग : 2;
	अचिन्हित पूर्णांक ts : 2;
	अचिन्हित पूर्णांक : 28;
	अचिन्हित पूर्णांक pad_0x04;
	अचिन्हित दीर्घ leap_event;
	लघु old_leap;
	लघु new_leap;
	अचिन्हित पूर्णांक pad_0x14;
	अचिन्हित दीर्घ prt[5];
	अचिन्हित दीर्घ cst[3];
	अचिन्हित पूर्णांक skew;
	अचिन्हित पूर्णांक pad_0x5c[41];
पूर्ण __packed;

/*
 * ptff - Perक्रमm timing facility function
 * @ptff_block: Poपूर्णांकer to ptff parameter block
 * @len: Length of parameter block
 * @func: Function code
 * Returns: Condition code (0 on success)
 */
#घोषणा ptff(ptff_block, len, func)					\
(अणु									\
	काष्ठा addrtype अणु अक्षर _[len]; पूर्ण;				\
	रेजिस्टर अचिन्हित पूर्णांक reg0 यंत्र("0") = func;			\
	रेजिस्टर अचिन्हित दीर्घ reg1 यंत्र("1") = (अचिन्हित दीर्घ) (ptff_block);\
	पूर्णांक rc;								\
									\
	यंत्र अस्थिर(							\
		"	.word	0x0104\n"				\
		"	ipm	%0\n"					\
		"	srl	%0,28\n"				\
		: "=d" (rc), "+m" (*(काष्ठा addrtype *) reg1)		\
		: "d" (reg0), "d" (reg1) : "cc");			\
	rc;								\
पूर्ण)

अटल अंतरभूत अचिन्हित दीर्घ local_tick_disable(व्योम)
अणु
	अचिन्हित दीर्घ old;

	old = S390_lowcore.घड़ी_comparator;
	S390_lowcore.घड़ी_comparator = घड़ी_comparator_max;
	set_घड़ी_comparator(S390_lowcore.घड़ी_comparator);
	वापस old;
पूर्ण

अटल अंतरभूत व्योम local_tick_enable(अचिन्हित दीर्घ comp)
अणु
	S390_lowcore.घड़ी_comparator = comp;
	set_घड़ी_comparator(S390_lowcore.घड़ी_comparator);
पूर्ण

#घोषणा CLOCK_TICK_RATE		1193180 /* Underlying HZ */

प्रकार अचिन्हित दीर्घ cycles_t;

अटल अंतरभूत अचिन्हित दीर्घ get_tod_घड़ी(व्योम)
अणु
	जोड़ tod_घड़ी clk;

	store_tod_घड़ी_ext(&clk);
	वापस clk.tod;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_tod_घड़ी_fast(व्योम)
अणु
#अगर_घोषित CONFIG_HAVE_MARCH_Z9_109_FEATURES
	अचिन्हित दीर्घ clk;

	यंत्र अस्थिर("stckf %0" : "=Q" (clk) : : "cc");
	वापस clk;
#अन्यथा
	वापस get_tod_घड़ी();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
	वापस (cycles_t) get_tod_घड़ी() >> 2;
पूर्ण

पूर्णांक get_phys_घड़ी(अचिन्हित दीर्घ *घड़ी);
व्योम init_cpu_समयr(व्योम);

बाह्य जोड़ tod_घड़ी tod_घड़ी_base;

/**
 * get_घड़ी_monotonic - वापसs current समय in घड़ी rate units
 *
 * The घड़ी and tod_घड़ी_base get changed via stop_machine.
 * Thereक्रमe preemption must be disabled, otherwise the वापसed
 * value is not guaranteed to be monotonic.
 */
अटल अंतरभूत अचिन्हित दीर्घ get_tod_घड़ी_monotonic(व्योम)
अणु
	अचिन्हित दीर्घ tod;

	preempt_disable_notrace();
	tod = get_tod_घड़ी() - tod_घड़ी_base.tod;
	preempt_enable_notrace();
	वापस tod;
पूर्ण

/**
 * tod_to_ns - convert a TOD क्रमmat value to nanoseconds
 * @todval: to be converted TOD क्रमmat value
 * Returns: number of nanoseconds that correspond to the TOD क्रमmat value
 *
 * Converting a 64 Bit TOD क्रमmat value to nanoseconds means that the value
 * must be भागided by 4.096. In order to achieve that we multiply with 125
 * and भागide by 512:
 *
 *    ns = (todval * 125) >> 9;
 *
 * In order to aव्योम an overflow with the multiplication we can reग_लिखो this.
 * With a split todval == 2^9 * th + tl (th upper 55 bits, tl lower 9 bits)
 * we end up with
 *
 *    ns = ((2^9 * th + tl) * 125 ) >> 9;
 * -> ns = (th * 125) + ((tl * 125) >> 9);
 *
 */
अटल अंतरभूत अचिन्हित दीर्घ tod_to_ns(अचिन्हित दीर्घ todval)
अणु
	वापस ((todval >> 9) * 125) + (((todval & 0x1ff) * 125) >> 9);
पूर्ण

/**
 * tod_after - compare two 64 bit TOD values
 * @a: first 64 bit TOD बारtamp
 * @b: second 64 bit TOD बारtamp
 *
 * Returns: true अगर a is later than b
 */
अटल अंतरभूत पूर्णांक tod_after(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	अगर (MACHINE_HAS_SCC)
		वापस (दीर्घ) a > (दीर्घ) b;
	वापस a > b;
पूर्ण

/**
 * tod_after_eq - compare two 64 bit TOD values
 * @a: first 64 bit TOD बारtamp
 * @b: second 64 bit TOD बारtamp
 *
 * Returns: true अगर a is later than b
 */
अटल अंतरभूत पूर्णांक tod_after_eq(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	अगर (MACHINE_HAS_SCC)
		वापस (दीर्घ) a >= (दीर्घ) b;
	वापस a >= b;
पूर्ण

#पूर्ण_अगर

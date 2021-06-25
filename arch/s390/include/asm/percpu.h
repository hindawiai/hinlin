<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_S390_PERCPU__
#घोषणा __ARCH_S390_PERCPU__

#समावेश <linux/preempt.h>
#समावेश <यंत्र/cmpxchg.h>

/*
 * s390 uses its own implementation क्रम per cpu data, the offset of
 * the cpu local data area is cached in the cpu's lowcore memory.
 */
#घोषणा __my_cpu_offset S390_lowcore.percpu_offset

/*
 * For 64 bit module code, the module may be more than 4G above the
 * per cpu area, use weak definitions to क्रमce the compiler to
 * generate बाह्यal references.
 */
#अगर defined(MODULE)
#घोषणा ARCH_NEEDS_WEAK_PER_CPU
#पूर्ण_अगर

/*
 * We use a compare-and-swap loop since that uses less cpu cycles than
 * disabling and enabling पूर्णांकerrupts like the generic variant would करो.
 */
#घोषणा arch_this_cpu_to_op_simple(pcp, val, op)			\
(अणु									\
	प्रकार typeof(pcp) pcp_op_T__;					\
	pcp_op_T__ old__, new__, prev__;				\
	pcp_op_T__ *ptr__;						\
	preempt_disable_notrace();					\
	ptr__ = raw_cpu_ptr(&(pcp));					\
	prev__ = *ptr__;						\
	करो अणु								\
		old__ = prev__;						\
		new__ = old__ op (val);					\
		prev__ = cmpxchg(ptr__, old__, new__);			\
	पूर्ण जबतक (prev__ != old__);					\
	preempt_enable_notrace();					\
	new__;								\
पूर्ण)

#घोषणा this_cpu_add_1(pcp, val)	arch_this_cpu_to_op_simple(pcp, val, +)
#घोषणा this_cpu_add_2(pcp, val)	arch_this_cpu_to_op_simple(pcp, val, +)
#घोषणा this_cpu_add_वापस_1(pcp, val) arch_this_cpu_to_op_simple(pcp, val, +)
#घोषणा this_cpu_add_वापस_2(pcp, val) arch_this_cpu_to_op_simple(pcp, val, +)
#घोषणा this_cpu_and_1(pcp, val)	arch_this_cpu_to_op_simple(pcp, val, &)
#घोषणा this_cpu_and_2(pcp, val)	arch_this_cpu_to_op_simple(pcp, val, &)
#घोषणा this_cpu_or_1(pcp, val)		arch_this_cpu_to_op_simple(pcp, val, |)
#घोषणा this_cpu_or_2(pcp, val)		arch_this_cpu_to_op_simple(pcp, val, |)

#अगर_अघोषित CONFIG_HAVE_MARCH_Z196_FEATURES

#घोषणा this_cpu_add_4(pcp, val)	arch_this_cpu_to_op_simple(pcp, val, +)
#घोषणा this_cpu_add_8(pcp, val)	arch_this_cpu_to_op_simple(pcp, val, +)
#घोषणा this_cpu_add_वापस_4(pcp, val) arch_this_cpu_to_op_simple(pcp, val, +)
#घोषणा this_cpu_add_वापस_8(pcp, val) arch_this_cpu_to_op_simple(pcp, val, +)
#घोषणा this_cpu_and_4(pcp, val)	arch_this_cpu_to_op_simple(pcp, val, &)
#घोषणा this_cpu_and_8(pcp, val)	arch_this_cpu_to_op_simple(pcp, val, &)
#घोषणा this_cpu_or_4(pcp, val)		arch_this_cpu_to_op_simple(pcp, val, |)
#घोषणा this_cpu_or_8(pcp, val)		arch_this_cpu_to_op_simple(pcp, val, |)

#अन्यथा /* CONFIG_HAVE_MARCH_Z196_FEATURES */

#घोषणा arch_this_cpu_add(pcp, val, op1, op2, szcast)			\
अणु									\
	प्रकार typeof(pcp) pcp_op_T__; 				\
	pcp_op_T__ val__ = (val);					\
	pcp_op_T__ old__, *ptr__;					\
	preempt_disable_notrace();					\
	ptr__ = raw_cpu_ptr(&(pcp)); 				\
	अगर (__builtin_स्थिरant_p(val__) &&				\
	    ((szcast)val__ > -129) && ((szcast)val__ < 128)) अणु		\
		यंत्र अस्थिर(						\
			op2 "   %[ptr__],%[val__]\n"			\
			: [ptr__] "+Q" (*ptr__) 			\
			: [val__] "i" ((szcast)val__)			\
			: "cc");					\
	पूर्ण अन्यथा अणु							\
		यंत्र अस्थिर(						\
			op1 "   %[old__],%[val__],%[ptr__]\n"		\
			: [old__] "=d" (old__), [ptr__] "+Q" (*ptr__)	\
			: [val__] "d" (val__)				\
			: "cc");					\
	पूर्ण								\
	preempt_enable_notrace();					\
पूर्ण

#घोषणा this_cpu_add_4(pcp, val) arch_this_cpu_add(pcp, val, "laa", "asi", पूर्णांक)
#घोषणा this_cpu_add_8(pcp, val) arch_this_cpu_add(pcp, val, "laag", "agsi", दीर्घ)

#घोषणा arch_this_cpu_add_वापस(pcp, val, op)				\
(अणु									\
	प्रकार typeof(pcp) pcp_op_T__; 				\
	pcp_op_T__ val__ = (val);					\
	pcp_op_T__ old__, *ptr__;					\
	preempt_disable_notrace();					\
	ptr__ = raw_cpu_ptr(&(pcp));	 				\
	यंत्र अस्थिर(							\
		op "    %[old__],%[val__],%[ptr__]\n"			\
		: [old__] "=d" (old__), [ptr__] "+Q" (*ptr__)		\
		: [val__] "d" (val__)					\
		: "cc");						\
	preempt_enable_notrace();						\
	old__ + val__;							\
पूर्ण)

#घोषणा this_cpu_add_वापस_4(pcp, val) arch_this_cpu_add_वापस(pcp, val, "laa")
#घोषणा this_cpu_add_वापस_8(pcp, val) arch_this_cpu_add_वापस(pcp, val, "laag")

#घोषणा arch_this_cpu_to_op(pcp, val, op)				\
अणु									\
	प्रकार typeof(pcp) pcp_op_T__; 				\
	pcp_op_T__ val__ = (val);					\
	pcp_op_T__ old__, *ptr__;					\
	preempt_disable_notrace();					\
	ptr__ = raw_cpu_ptr(&(pcp));	 				\
	यंत्र अस्थिर(							\
		op "    %[old__],%[val__],%[ptr__]\n"			\
		: [old__] "=d" (old__), [ptr__] "+Q" (*ptr__)		\
		: [val__] "d" (val__)					\
		: "cc");						\
	preempt_enable_notrace();					\
पूर्ण

#घोषणा this_cpu_and_4(pcp, val)	arch_this_cpu_to_op(pcp, val, "lan")
#घोषणा this_cpu_and_8(pcp, val)	arch_this_cpu_to_op(pcp, val, "lang")
#घोषणा this_cpu_or_4(pcp, val)		arch_this_cpu_to_op(pcp, val, "lao")
#घोषणा this_cpu_or_8(pcp, val)		arch_this_cpu_to_op(pcp, val, "laog")

#पूर्ण_अगर /* CONFIG_HAVE_MARCH_Z196_FEATURES */

#घोषणा arch_this_cpu_cmpxchg(pcp, oval, nval)				\
(अणु									\
	प्रकार typeof(pcp) pcp_op_T__;					\
	pcp_op_T__ ret__;						\
	pcp_op_T__ *ptr__;						\
	preempt_disable_notrace();					\
	ptr__ = raw_cpu_ptr(&(pcp));					\
	ret__ = cmpxchg(ptr__, oval, nval);				\
	preempt_enable_notrace();					\
	ret__;								\
पूर्ण)

#घोषणा this_cpu_cmpxchg_1(pcp, oval, nval) arch_this_cpu_cmpxchg(pcp, oval, nval)
#घोषणा this_cpu_cmpxchg_2(pcp, oval, nval) arch_this_cpu_cmpxchg(pcp, oval, nval)
#घोषणा this_cpu_cmpxchg_4(pcp, oval, nval) arch_this_cpu_cmpxchg(pcp, oval, nval)
#घोषणा this_cpu_cmpxchg_8(pcp, oval, nval) arch_this_cpu_cmpxchg(pcp, oval, nval)

#घोषणा arch_this_cpu_xchg(pcp, nval)					\
(अणु									\
	typeof(pcp) *ptr__;						\
	typeof(pcp) ret__;						\
	preempt_disable_notrace();					\
	ptr__ = raw_cpu_ptr(&(pcp));					\
	ret__ = xchg(ptr__, nval);					\
	preempt_enable_notrace();					\
	ret__;								\
पूर्ण)

#घोषणा this_cpu_xchg_1(pcp, nval) arch_this_cpu_xchg(pcp, nval)
#घोषणा this_cpu_xchg_2(pcp, nval) arch_this_cpu_xchg(pcp, nval)
#घोषणा this_cpu_xchg_4(pcp, nval) arch_this_cpu_xchg(pcp, nval)
#घोषणा this_cpu_xchg_8(pcp, nval) arch_this_cpu_xchg(pcp, nval)

#घोषणा arch_this_cpu_cmpxchg_द्विगुन(pcp1, pcp2, o1, o2, n1, n2)	\
(अणु									\
	typeof(pcp1) o1__ = (o1), n1__ = (n1);				\
	typeof(pcp2) o2__ = (o2), n2__ = (n2);				\
	typeof(pcp1) *p1__;						\
	typeof(pcp2) *p2__;						\
	पूर्णांक ret__;							\
	preempt_disable_notrace();					\
	p1__ = raw_cpu_ptr(&(pcp1));					\
	p2__ = raw_cpu_ptr(&(pcp2));					\
	ret__ = __cmpxchg_द्विगुन(p1__, p2__, o1__, o2__, n1__, n2__);	\
	preempt_enable_notrace();					\
	ret__;								\
पूर्ण)

#घोषणा this_cpu_cmpxchg_द्विगुन_8 arch_this_cpu_cmpxchg_द्विगुन

#समावेश <यंत्र-generic/percpu.h>

#पूर्ण_अगर /* __ARCH_S390_PERCPU__ */

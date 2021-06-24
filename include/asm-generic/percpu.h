<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_PERCPU_H_
#घोषणा _ASM_GENERIC_PERCPU_H_

#समावेश <linux/compiler.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/percpu-defs.h>

#अगर_घोषित CONFIG_SMP

/*
 * per_cpu_offset() is the offset that has to be added to a
 * percpu variable to get to the instance क्रम a certain processor.
 *
 * Most arches use the __per_cpu_offset array क्रम those offsets but
 * some arches have their own ways of determining the offset (x86_64, s390).
 */
#अगर_अघोषित __per_cpu_offset
बाह्य अचिन्हित दीर्घ __per_cpu_offset[NR_CPUS];

#घोषणा per_cpu_offset(x) (__per_cpu_offset[x])
#पूर्ण_अगर

/*
 * Determine the offset क्रम the currently active processor.
 * An arch may define __my_cpu_offset to provide a more effective
 * means of obtaining the offset to the per cpu variables of the
 * current processor.
 */
#अगर_अघोषित __my_cpu_offset
#घोषणा __my_cpu_offset per_cpu_offset(raw_smp_processor_id())
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_PREEMPT
#घोषणा my_cpu_offset per_cpu_offset(smp_processor_id())
#अन्यथा
#घोषणा my_cpu_offset __my_cpu_offset
#पूर्ण_अगर

/*
 * Arch may define arch_raw_cpu_ptr() to provide more efficient address
 * translations क्रम raw_cpu_ptr().
 */
#अगर_अघोषित arch_raw_cpu_ptr
#घोषणा arch_raw_cpu_ptr(ptr) SHIFT_PERCPU_PTR(ptr, __my_cpu_offset)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_SETUP_PER_CPU_AREA
बाह्य व्योम setup_per_cpu_areas(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर	/* SMP */

#अगर_अघोषित PER_CPU_BASE_SECTION
#अगर_घोषित CONFIG_SMP
#घोषणा PER_CPU_BASE_SECTION ".data..percpu"
#अन्यथा
#घोषणा PER_CPU_BASE_SECTION ".data"
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित PER_CPU_ATTRIBUTES
#घोषणा PER_CPU_ATTRIBUTES
#पूर्ण_अगर

#घोषणा raw_cpu_generic_पढ़ो(pcp)					\
(अणु									\
	*raw_cpu_ptr(&(pcp));						\
पूर्ण)

#घोषणा raw_cpu_generic_to_op(pcp, val, op)				\
करो अणु									\
	*raw_cpu_ptr(&(pcp)) op val;					\
पूर्ण जबतक (0)

#घोषणा raw_cpu_generic_add_वापस(pcp, val)				\
(अणु									\
	typeof(pcp) *__p = raw_cpu_ptr(&(pcp));				\
									\
	*__p += val;							\
	*__p;								\
पूर्ण)

#घोषणा raw_cpu_generic_xchg(pcp, nval)					\
(अणु									\
	typeof(pcp) *__p = raw_cpu_ptr(&(pcp));				\
	typeof(pcp) __ret;						\
	__ret = *__p;							\
	*__p = nval;							\
	__ret;								\
पूर्ण)

#घोषणा raw_cpu_generic_cmpxchg(pcp, oval, nval)			\
(अणु									\
	typeof(pcp) *__p = raw_cpu_ptr(&(pcp));				\
	typeof(pcp) __ret;						\
	__ret = *__p;							\
	अगर (__ret == (oval))						\
		*__p = nval;						\
	__ret;								\
पूर्ण)

#घोषणा raw_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2) \
(अणु									\
	typeof(pcp1) *__p1 = raw_cpu_ptr(&(pcp1));			\
	typeof(pcp2) *__p2 = raw_cpu_ptr(&(pcp2));			\
	पूर्णांक __ret = 0;							\
	अगर (*__p1 == (oval1) && *__p2  == (oval2)) अणु			\
		*__p1 = nval1;						\
		*__p2 = nval2;						\
		__ret = 1;						\
	पूर्ण								\
	(__ret);							\
पूर्ण)

#घोषणा __this_cpu_generic_पढ़ो_nopreempt(pcp)				\
(अणु									\
	typeof(pcp) ___ret;						\
	preempt_disable_notrace();					\
	___ret = READ_ONCE(*raw_cpu_ptr(&(pcp)));			\
	preempt_enable_notrace();					\
	___ret;								\
पूर्ण)

#घोषणा __this_cpu_generic_पढ़ो_noirq(pcp)				\
(अणु									\
	typeof(pcp) ___ret;						\
	अचिन्हित दीर्घ ___flags;						\
	raw_local_irq_save(___flags);					\
	___ret = raw_cpu_generic_पढ़ो(pcp);				\
	raw_local_irq_restore(___flags);				\
	___ret;								\
पूर्ण)

#घोषणा this_cpu_generic_पढ़ो(pcp)					\
(अणु									\
	typeof(pcp) __ret;						\
	अगर (__native_word(pcp))						\
		__ret = __this_cpu_generic_पढ़ो_nopreempt(pcp);		\
	अन्यथा								\
		__ret = __this_cpu_generic_पढ़ो_noirq(pcp);		\
	__ret;								\
पूर्ण)

#घोषणा this_cpu_generic_to_op(pcp, val, op)				\
करो अणु									\
	अचिन्हित दीर्घ __flags;						\
	raw_local_irq_save(__flags);					\
	raw_cpu_generic_to_op(pcp, val, op);				\
	raw_local_irq_restore(__flags);					\
पूर्ण जबतक (0)


#घोषणा this_cpu_generic_add_वापस(pcp, val)				\
(अणु									\
	typeof(pcp) __ret;						\
	अचिन्हित दीर्घ __flags;						\
	raw_local_irq_save(__flags);					\
	__ret = raw_cpu_generic_add_वापस(pcp, val);			\
	raw_local_irq_restore(__flags);					\
	__ret;								\
पूर्ण)

#घोषणा this_cpu_generic_xchg(pcp, nval)				\
(अणु									\
	typeof(pcp) __ret;						\
	अचिन्हित दीर्घ __flags;						\
	raw_local_irq_save(__flags);					\
	__ret = raw_cpu_generic_xchg(pcp, nval);			\
	raw_local_irq_restore(__flags);					\
	__ret;								\
पूर्ण)

#घोषणा this_cpu_generic_cmpxchg(pcp, oval, nval)			\
(अणु									\
	typeof(pcp) __ret;						\
	अचिन्हित दीर्घ __flags;						\
	raw_local_irq_save(__flags);					\
	__ret = raw_cpu_generic_cmpxchg(pcp, oval, nval);		\
	raw_local_irq_restore(__flags);					\
	__ret;								\
पूर्ण)

#घोषणा this_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)	\
(अणु									\
	पूर्णांक __ret;							\
	अचिन्हित दीर्घ __flags;						\
	raw_local_irq_save(__flags);					\
	__ret = raw_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2,		\
			oval1, oval2, nval1, nval2);			\
	raw_local_irq_restore(__flags);					\
	__ret;								\
पूर्ण)

#अगर_अघोषित raw_cpu_पढ़ो_1
#घोषणा raw_cpu_पढ़ो_1(pcp)		raw_cpu_generic_पढ़ो(pcp)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_पढ़ो_2
#घोषणा raw_cpu_पढ़ो_2(pcp)		raw_cpu_generic_पढ़ो(pcp)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_पढ़ो_4
#घोषणा raw_cpu_पढ़ो_4(pcp)		raw_cpu_generic_पढ़ो(pcp)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_पढ़ो_8
#घोषणा raw_cpu_पढ़ो_8(pcp)		raw_cpu_generic_पढ़ो(pcp)
#पूर्ण_अगर

#अगर_अघोषित raw_cpu_ग_लिखो_1
#घोषणा raw_cpu_ग_लिखो_1(pcp, val)	raw_cpu_generic_to_op(pcp, val, =)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_ग_लिखो_2
#घोषणा raw_cpu_ग_लिखो_2(pcp, val)	raw_cpu_generic_to_op(pcp, val, =)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_ग_लिखो_4
#घोषणा raw_cpu_ग_लिखो_4(pcp, val)	raw_cpu_generic_to_op(pcp, val, =)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_ग_लिखो_8
#घोषणा raw_cpu_ग_लिखो_8(pcp, val)	raw_cpu_generic_to_op(pcp, val, =)
#पूर्ण_अगर

#अगर_अघोषित raw_cpu_add_1
#घोषणा raw_cpu_add_1(pcp, val)		raw_cpu_generic_to_op(pcp, val, +=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_add_2
#घोषणा raw_cpu_add_2(pcp, val)		raw_cpu_generic_to_op(pcp, val, +=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_add_4
#घोषणा raw_cpu_add_4(pcp, val)		raw_cpu_generic_to_op(pcp, val, +=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_add_8
#घोषणा raw_cpu_add_8(pcp, val)		raw_cpu_generic_to_op(pcp, val, +=)
#पूर्ण_अगर

#अगर_अघोषित raw_cpu_and_1
#घोषणा raw_cpu_and_1(pcp, val)		raw_cpu_generic_to_op(pcp, val, &=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_and_2
#घोषणा raw_cpu_and_2(pcp, val)		raw_cpu_generic_to_op(pcp, val, &=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_and_4
#घोषणा raw_cpu_and_4(pcp, val)		raw_cpu_generic_to_op(pcp, val, &=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_and_8
#घोषणा raw_cpu_and_8(pcp, val)		raw_cpu_generic_to_op(pcp, val, &=)
#पूर्ण_अगर

#अगर_अघोषित raw_cpu_or_1
#घोषणा raw_cpu_or_1(pcp, val)		raw_cpu_generic_to_op(pcp, val, |=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_or_2
#घोषणा raw_cpu_or_2(pcp, val)		raw_cpu_generic_to_op(pcp, val, |=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_or_4
#घोषणा raw_cpu_or_4(pcp, val)		raw_cpu_generic_to_op(pcp, val, |=)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_or_8
#घोषणा raw_cpu_or_8(pcp, val)		raw_cpu_generic_to_op(pcp, val, |=)
#पूर्ण_अगर

#अगर_अघोषित raw_cpu_add_वापस_1
#घोषणा raw_cpu_add_वापस_1(pcp, val)	raw_cpu_generic_add_वापस(pcp, val)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_add_वापस_2
#घोषणा raw_cpu_add_वापस_2(pcp, val)	raw_cpu_generic_add_वापस(pcp, val)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_add_वापस_4
#घोषणा raw_cpu_add_वापस_4(pcp, val)	raw_cpu_generic_add_वापस(pcp, val)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_add_वापस_8
#घोषणा raw_cpu_add_वापस_8(pcp, val)	raw_cpu_generic_add_वापस(pcp, val)
#पूर्ण_अगर

#अगर_अघोषित raw_cpu_xchg_1
#घोषणा raw_cpu_xchg_1(pcp, nval)	raw_cpu_generic_xchg(pcp, nval)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_xchg_2
#घोषणा raw_cpu_xchg_2(pcp, nval)	raw_cpu_generic_xchg(pcp, nval)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_xchg_4
#घोषणा raw_cpu_xchg_4(pcp, nval)	raw_cpu_generic_xchg(pcp, nval)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_xchg_8
#घोषणा raw_cpu_xchg_8(pcp, nval)	raw_cpu_generic_xchg(pcp, nval)
#पूर्ण_अगर

#अगर_अघोषित raw_cpu_cmpxchg_1
#घोषणा raw_cpu_cmpxchg_1(pcp, oval, nval) \
	raw_cpu_generic_cmpxchg(pcp, oval, nval)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_cmpxchg_2
#घोषणा raw_cpu_cmpxchg_2(pcp, oval, nval) \
	raw_cpu_generic_cmpxchg(pcp, oval, nval)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_cmpxchg_4
#घोषणा raw_cpu_cmpxchg_4(pcp, oval, nval) \
	raw_cpu_generic_cmpxchg(pcp, oval, nval)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_cmpxchg_8
#घोषणा raw_cpu_cmpxchg_8(pcp, oval, nval) \
	raw_cpu_generic_cmpxchg(pcp, oval, nval)
#पूर्ण_अगर

#अगर_अघोषित raw_cpu_cmpxchg_द्विगुन_1
#घोषणा raw_cpu_cmpxchg_द्विगुन_1(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	raw_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_cmpxchg_द्विगुन_2
#घोषणा raw_cpu_cmpxchg_द्विगुन_2(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	raw_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_cmpxchg_द्विगुन_4
#घोषणा raw_cpu_cmpxchg_द्विगुन_4(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	raw_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)
#पूर्ण_अगर
#अगर_अघोषित raw_cpu_cmpxchg_द्विगुन_8
#घोषणा raw_cpu_cmpxchg_द्विगुन_8(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	raw_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_पढ़ो_1
#घोषणा this_cpu_पढ़ो_1(pcp)		this_cpu_generic_पढ़ो(pcp)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_पढ़ो_2
#घोषणा this_cpu_पढ़ो_2(pcp)		this_cpu_generic_पढ़ो(pcp)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_पढ़ो_4
#घोषणा this_cpu_पढ़ो_4(pcp)		this_cpu_generic_पढ़ो(pcp)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_पढ़ो_8
#घोषणा this_cpu_पढ़ो_8(pcp)		this_cpu_generic_पढ़ो(pcp)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_ग_लिखो_1
#घोषणा this_cpu_ग_लिखो_1(pcp, val)	this_cpu_generic_to_op(pcp, val, =)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_ग_लिखो_2
#घोषणा this_cpu_ग_लिखो_2(pcp, val)	this_cpu_generic_to_op(pcp, val, =)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_ग_लिखो_4
#घोषणा this_cpu_ग_लिखो_4(pcp, val)	this_cpu_generic_to_op(pcp, val, =)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_ग_लिखो_8
#घोषणा this_cpu_ग_लिखो_8(pcp, val)	this_cpu_generic_to_op(pcp, val, =)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_add_1
#घोषणा this_cpu_add_1(pcp, val)	this_cpu_generic_to_op(pcp, val, +=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_add_2
#घोषणा this_cpu_add_2(pcp, val)	this_cpu_generic_to_op(pcp, val, +=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_add_4
#घोषणा this_cpu_add_4(pcp, val)	this_cpu_generic_to_op(pcp, val, +=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_add_8
#घोषणा this_cpu_add_8(pcp, val)	this_cpu_generic_to_op(pcp, val, +=)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_and_1
#घोषणा this_cpu_and_1(pcp, val)	this_cpu_generic_to_op(pcp, val, &=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_and_2
#घोषणा this_cpu_and_2(pcp, val)	this_cpu_generic_to_op(pcp, val, &=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_and_4
#घोषणा this_cpu_and_4(pcp, val)	this_cpu_generic_to_op(pcp, val, &=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_and_8
#घोषणा this_cpu_and_8(pcp, val)	this_cpu_generic_to_op(pcp, val, &=)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_or_1
#घोषणा this_cpu_or_1(pcp, val)		this_cpu_generic_to_op(pcp, val, |=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_or_2
#घोषणा this_cpu_or_2(pcp, val)		this_cpu_generic_to_op(pcp, val, |=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_or_4
#घोषणा this_cpu_or_4(pcp, val)		this_cpu_generic_to_op(pcp, val, |=)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_or_8
#घोषणा this_cpu_or_8(pcp, val)		this_cpu_generic_to_op(pcp, val, |=)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_add_वापस_1
#घोषणा this_cpu_add_वापस_1(pcp, val)	this_cpu_generic_add_वापस(pcp, val)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_add_वापस_2
#घोषणा this_cpu_add_वापस_2(pcp, val)	this_cpu_generic_add_वापस(pcp, val)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_add_वापस_4
#घोषणा this_cpu_add_वापस_4(pcp, val)	this_cpu_generic_add_वापस(pcp, val)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_add_वापस_8
#घोषणा this_cpu_add_वापस_8(pcp, val)	this_cpu_generic_add_वापस(pcp, val)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_xchg_1
#घोषणा this_cpu_xchg_1(pcp, nval)	this_cpu_generic_xchg(pcp, nval)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_xchg_2
#घोषणा this_cpu_xchg_2(pcp, nval)	this_cpu_generic_xchg(pcp, nval)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_xchg_4
#घोषणा this_cpu_xchg_4(pcp, nval)	this_cpu_generic_xchg(pcp, nval)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_xchg_8
#घोषणा this_cpu_xchg_8(pcp, nval)	this_cpu_generic_xchg(pcp, nval)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_cmpxchg_1
#घोषणा this_cpu_cmpxchg_1(pcp, oval, nval) \
	this_cpu_generic_cmpxchg(pcp, oval, nval)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_cmpxchg_2
#घोषणा this_cpu_cmpxchg_2(pcp, oval, nval) \
	this_cpu_generic_cmpxchg(pcp, oval, nval)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_cmpxchg_4
#घोषणा this_cpu_cmpxchg_4(pcp, oval, nval) \
	this_cpu_generic_cmpxchg(pcp, oval, nval)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_cmpxchg_8
#घोषणा this_cpu_cmpxchg_8(pcp, oval, nval) \
	this_cpu_generic_cmpxchg(pcp, oval, nval)
#पूर्ण_अगर

#अगर_अघोषित this_cpu_cmpxchg_द्विगुन_1
#घोषणा this_cpu_cmpxchg_द्विगुन_1(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	this_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_cmpxchg_द्विगुन_2
#घोषणा this_cpu_cmpxchg_द्विगुन_2(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	this_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_cmpxchg_द्विगुन_4
#घोषणा this_cpu_cmpxchg_द्विगुन_4(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	this_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)
#पूर्ण_अगर
#अगर_अघोषित this_cpu_cmpxchg_द्विगुन_8
#घोषणा this_cpu_cmpxchg_द्विगुन_8(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	this_cpu_generic_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_PERCPU_H_ */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/percpu-defs.h - basic definitions क्रम percpu areas
 *
 * DO NOT INCLUDE सूचीECTLY OUTSIDE PERCPU IMPLEMENTATION PROPER.
 *
 * This file is separate from linux/percpu.h to aव्योम cyclic inclusion
 * dependency from arch header files.  Only to be included from
 * यंत्र/percpu.h.
 *
 * This file includes macros necessary to declare percpu sections and
 * variables, and definitions of percpu accessors and operations.  It
 * should provide enough percpu features to arch header files even when
 * they can only include यंत्र/percpu.h to aव्योम cyclic inclusion dependency.
 */

#अगर_अघोषित _LINUX_PERCPU_DEFS_H
#घोषणा _LINUX_PERCPU_DEFS_H

#अगर_घोषित CONFIG_SMP

#अगर_घोषित MODULE
#घोषणा PER_CPU_SHARED_ALIGNED_SECTION ""
#घोषणा PER_CPU_ALIGNED_SECTION ""
#अन्यथा
#घोषणा PER_CPU_SHARED_ALIGNED_SECTION "..shared_aligned"
#घोषणा PER_CPU_ALIGNED_SECTION "..shared_aligned"
#पूर्ण_अगर
#घोषणा PER_CPU_FIRST_SECTION "..first"

#अन्यथा

#घोषणा PER_CPU_SHARED_ALIGNED_SECTION ""
#घोषणा PER_CPU_ALIGNED_SECTION "..shared_aligned"
#घोषणा PER_CPU_FIRST_SECTION ""

#पूर्ण_अगर

/*
 * Base implementations of per-CPU variable declarations and definitions, where
 * the section in which the variable is to be placed is provided by the
 * 'sec' argument.  This may be used to affect the parameters governing the
 * variable's storage.
 *
 * NOTE!  The sections क्रम the DECLARE and क्रम the DEFINE must match, lest
 * linkage errors occur due the compiler generating the wrong code to access
 * that section.
 */
#घोषणा __PCPU_ATTRS(sec)						\
	__percpu __attribute__((section(PER_CPU_BASE_SECTION sec)))	\
	PER_CPU_ATTRIBUTES

#घोषणा __PCPU_DUMMY_ATTRS						\
	__section(".discard") __attribute__((unused))

/*
 * s390 and alpha modules require percpu variables to be defined as
 * weak to क्रमce the compiler to generate GOT based बाह्यal
 * references क्रम them.  This is necessary because percpu sections
 * will be located outside of the usually addressable area.
 *
 * This definition माला_दो the following two extra restrictions when
 * defining percpu variables.
 *
 * 1. The symbol must be globally unique, even the अटल ones.
 * 2. Static percpu variables cannot be defined inside a function.
 *
 * Archs which need weak percpu definitions should define
 * ARCH_NEEDS_WEAK_PER_CPU in यंत्र/percpu.h when necessary.
 *
 * To ensure that the generic code observes the above two
 * restrictions, अगर CONFIG_DEBUG_FORCE_WEAK_PER_CPU is set weak
 * definition is used क्रम all हालs.
 */
#अगर defined(ARCH_NEEDS_WEAK_PER_CPU) || defined(CONFIG_DEBUG_FORCE_WEAK_PER_CPU)
/*
 * __pcpu_scope_* dummy variable is used to enक्रमce scope.  It
 * receives the अटल modअगरier when it's used in front of
 * DEFINE_PER_CPU() and will trigger build failure अगर
 * DECLARE_PER_CPU() is used क्रम the same variable.
 *
 * __pcpu_unique_* dummy variable is used to enक्रमce symbol uniqueness
 * such that hidden weak symbol collision, which will cause unrelated
 * variables to share the same address, can be detected during build.
 */
#घोषणा DECLARE_PER_CPU_SECTION(type, name, sec)			\
	बाह्य __PCPU_DUMMY_ATTRS अक्षर __pcpu_scope_##name;		\
	बाह्य __PCPU_ATTRS(sec) __typeof__(type) name

#घोषणा DEFINE_PER_CPU_SECTION(type, name, sec)				\
	__PCPU_DUMMY_ATTRS अक्षर __pcpu_scope_##name;			\
	बाह्य __PCPU_DUMMY_ATTRS अक्षर __pcpu_unique_##name;		\
	__PCPU_DUMMY_ATTRS अक्षर __pcpu_unique_##name;			\
	बाह्य __PCPU_ATTRS(sec) __typeof__(type) name;			\
	__PCPU_ATTRS(sec) __weak __typeof__(type) name
#अन्यथा
/*
 * Normal declaration and definition macros.
 */
#घोषणा DECLARE_PER_CPU_SECTION(type, name, sec)			\
	बाह्य __PCPU_ATTRS(sec) __typeof__(type) name

#घोषणा DEFINE_PER_CPU_SECTION(type, name, sec)				\
	__PCPU_ATTRS(sec) __typeof__(type) name
#पूर्ण_अगर

/*
 * Variant on the per-CPU variable declaration/definition theme used क्रम
 * ordinary per-CPU variables.
 */
#घोषणा DECLARE_PER_CPU(type, name)					\
	DECLARE_PER_CPU_SECTION(type, name, "")

#घोषणा DEFINE_PER_CPU(type, name)					\
	DEFINE_PER_CPU_SECTION(type, name, "")

/*
 * Declaration/definition used क्रम per-CPU variables that must come first in
 * the set of variables.
 */
#घोषणा DECLARE_PER_CPU_FIRST(type, name)				\
	DECLARE_PER_CPU_SECTION(type, name, PER_CPU_FIRST_SECTION)

#घोषणा DEFINE_PER_CPU_FIRST(type, name)				\
	DEFINE_PER_CPU_SECTION(type, name, PER_CPU_FIRST_SECTION)

/*
 * Declaration/definition used क्रम per-CPU variables that must be cacheline
 * aligned under SMP conditions so that, whilst a particular instance of the
 * data corresponds to a particular CPU, inefficiencies due to direct access by
 * other CPUs are reduced by preventing the data from unnecessarily spanning
 * cachelines.
 *
 * An example of this would be statistical data, where each CPU's set of data
 * is updated by that CPU alone, but the data from across all CPUs is collated
 * by a CPU processing a पढ़ो from a proc file.
 */
#घोषणा DECLARE_PER_CPU_SHARED_ALIGNED(type, name)			\
	DECLARE_PER_CPU_SECTION(type, name, PER_CPU_SHARED_ALIGNED_SECTION) \
	____cacheline_aligned_in_smp

#घोषणा DEFINE_PER_CPU_SHARED_ALIGNED(type, name)			\
	DEFINE_PER_CPU_SECTION(type, name, PER_CPU_SHARED_ALIGNED_SECTION) \
	____cacheline_aligned_in_smp

#घोषणा DECLARE_PER_CPU_ALIGNED(type, name)				\
	DECLARE_PER_CPU_SECTION(type, name, PER_CPU_ALIGNED_SECTION)	\
	____cacheline_aligned

#घोषणा DEFINE_PER_CPU_ALIGNED(type, name)				\
	DEFINE_PER_CPU_SECTION(type, name, PER_CPU_ALIGNED_SECTION)	\
	____cacheline_aligned

/*
 * Declaration/definition used क्रम per-CPU variables that must be page aligned.
 */
#घोषणा DECLARE_PER_CPU_PAGE_ALIGNED(type, name)			\
	DECLARE_PER_CPU_SECTION(type, name, "..page_aligned")		\
	__aligned(PAGE_SIZE)

#घोषणा DEFINE_PER_CPU_PAGE_ALIGNED(type, name)				\
	DEFINE_PER_CPU_SECTION(type, name, "..page_aligned")		\
	__aligned(PAGE_SIZE)

/*
 * Declaration/definition used क्रम per-CPU variables that must be पढ़ो mostly.
 */
#घोषणा DECLARE_PER_CPU_READ_MOSTLY(type, name)			\
	DECLARE_PER_CPU_SECTION(type, name, "..read_mostly")

#घोषणा DEFINE_PER_CPU_READ_MOSTLY(type, name)				\
	DEFINE_PER_CPU_SECTION(type, name, "..read_mostly")

/*
 * Declaration/definition used क्रम per-CPU variables that should be accessed
 * as decrypted when memory encryption is enabled in the guest.
 */
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
#घोषणा DECLARE_PER_CPU_DECRYPTED(type, name)				\
	DECLARE_PER_CPU_SECTION(type, name, "..decrypted")

#घोषणा DEFINE_PER_CPU_DECRYPTED(type, name)				\
	DEFINE_PER_CPU_SECTION(type, name, "..decrypted")
#अन्यथा
#घोषणा DEFINE_PER_CPU_DECRYPTED(type, name)	DEFINE_PER_CPU(type, name)
#पूर्ण_अगर

/*
 * Intermodule exports क्रम per-CPU variables.  sparse क्रममाला_लो about
 * address space across EXPORT_SYMBOL(), change EXPORT_SYMBOL() to
 * noop अगर __CHECKER__.
 */
#अगर_अघोषित __CHECKER__
#घोषणा EXPORT_PER_CPU_SYMBOL(var) EXPORT_SYMBOL(var)
#घोषणा EXPORT_PER_CPU_SYMBOL_GPL(var) EXPORT_SYMBOL_GPL(var)
#अन्यथा
#घोषणा EXPORT_PER_CPU_SYMBOL(var)
#घोषणा EXPORT_PER_CPU_SYMBOL_GPL(var)
#पूर्ण_अगर

/*
 * Accessors and operations.
 */
#अगर_अघोषित __ASSEMBLY__

/*
 * __verअगरy_pcpu_ptr() verअगरies @ptr is a percpu poपूर्णांकer without evaluating
 * @ptr and is invoked once beक्रमe a percpu area is accessed by all
 * accessors and operations.  This is perक्रमmed in the generic part of
 * percpu and arch overrides करोn't need to worry about it; however, अगर an
 * arch wants to implement an arch-specअगरic percpu accessor or operation,
 * it may use __verअगरy_pcpu_ptr() to verअगरy the parameters.
 *
 * + 0 is required in order to convert the poपूर्णांकer type from a
 * potential array type to a poपूर्णांकer to a single item of the array.
 */
#घोषणा __verअगरy_pcpu_ptr(ptr)						\
करो अणु									\
	स्थिर व्योम __percpu *__vpp_verअगरy = (typeof((ptr) + 0))शून्य;	\
	(व्योम)__vpp_verअगरy;						\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_SMP

/*
 * Add an offset to a poपूर्णांकer but keep the poपूर्णांकer as-is.  Use RELOC_HIDE()
 * to prevent the compiler from making incorrect assumptions about the
 * poपूर्णांकer value.  The weird cast keeps both GCC and sparse happy.
 */
#घोषणा SHIFT_PERCPU_PTR(__p, __offset)					\
	RELOC_HIDE((typeof(*(__p)) __kernel __क्रमce *)(__p), (__offset))

#घोषणा per_cpu_ptr(ptr, cpu)						\
(अणु									\
	__verअगरy_pcpu_ptr(ptr);						\
	SHIFT_PERCPU_PTR((ptr), per_cpu_offset((cpu)));			\
पूर्ण)

#घोषणा raw_cpu_ptr(ptr)						\
(अणु									\
	__verअगरy_pcpu_ptr(ptr);						\
	arch_raw_cpu_ptr(ptr);						\
पूर्ण)

#अगर_घोषित CONFIG_DEBUG_PREEMPT
#घोषणा this_cpu_ptr(ptr)						\
(अणु									\
	__verअगरy_pcpu_ptr(ptr);						\
	SHIFT_PERCPU_PTR(ptr, my_cpu_offset);				\
पूर्ण)
#अन्यथा
#घोषणा this_cpu_ptr(ptr) raw_cpu_ptr(ptr)
#पूर्ण_अगर

#अन्यथा	/* CONFIG_SMP */

#घोषणा VERIFY_PERCPU_PTR(__p)						\
(अणु									\
	__verअगरy_pcpu_ptr(__p);						\
	(typeof(*(__p)) __kernel __क्रमce *)(__p);			\
पूर्ण)

#घोषणा per_cpu_ptr(ptr, cpu)	(अणु (व्योम)(cpu); VERIFY_PERCPU_PTR(ptr); पूर्ण)
#घोषणा raw_cpu_ptr(ptr)	per_cpu_ptr(ptr, 0)
#घोषणा this_cpu_ptr(ptr)	raw_cpu_ptr(ptr)

#पूर्ण_अगर	/* CONFIG_SMP */

#घोषणा per_cpu(var, cpu)	(*per_cpu_ptr(&(var), cpu))

/*
 * Must be an lvalue. Since @var must be a simple identअगरier,
 * we क्रमce a syntax error here अगर it isn't.
 */
#घोषणा get_cpu_var(var)						\
(*(अणु									\
	preempt_disable();						\
	this_cpu_ptr(&var);						\
पूर्ण))

/*
 * The weird & is necessary because sparse considers (व्योम)(var) to be
 * a direct dereference of percpu variable (var).
 */
#घोषणा put_cpu_var(var)						\
करो अणु									\
	(व्योम)&(var);							\
	preempt_enable();						\
पूर्ण जबतक (0)

#घोषणा get_cpu_ptr(var)						\
(अणु									\
	preempt_disable();						\
	this_cpu_ptr(var);						\
पूर्ण)

#घोषणा put_cpu_ptr(var)						\
करो अणु									\
	(व्योम)(var);							\
	preempt_enable();						\
पूर्ण जबतक (0)

/*
 * Branching function to split up a function पूर्णांकo a set of functions that
 * are called क्रम dअगरferent scalar sizes of the objects handled.
 */

बाह्य व्योम __bad_size_call_parameter(व्योम);

#अगर_घोषित CONFIG_DEBUG_PREEMPT
बाह्य व्योम __this_cpu_preempt_check(स्थिर अक्षर *op);
#अन्यथा
अटल अंतरभूत व्योम __this_cpu_preempt_check(स्थिर अक्षर *op) अणु पूर्ण
#पूर्ण_अगर

#घोषणा __pcpu_size_call_वापस(stem, variable)				\
(अणु									\
	typeof(variable) pscr_ret__;					\
	__verअगरy_pcpu_ptr(&(variable));					\
	चयन(माप(variable)) अणु					\
	हाल 1: pscr_ret__ = stem##1(variable); अवरोध;			\
	हाल 2: pscr_ret__ = stem##2(variable); अवरोध;			\
	हाल 4: pscr_ret__ = stem##4(variable); अवरोध;			\
	हाल 8: pscr_ret__ = stem##8(variable); अवरोध;			\
	शेष:							\
		__bad_size_call_parameter(); अवरोध;			\
	पूर्ण								\
	pscr_ret__;							\
पूर्ण)

#घोषणा __pcpu_size_call_वापस2(stem, variable, ...)			\
(अणु									\
	typeof(variable) pscr2_ret__;					\
	__verअगरy_pcpu_ptr(&(variable));					\
	चयन(माप(variable)) अणु					\
	हाल 1: pscr2_ret__ = stem##1(variable, __VA_ARGS__); अवरोध;	\
	हाल 2: pscr2_ret__ = stem##2(variable, __VA_ARGS__); अवरोध;	\
	हाल 4: pscr2_ret__ = stem##4(variable, __VA_ARGS__); अवरोध;	\
	हाल 8: pscr2_ret__ = stem##8(variable, __VA_ARGS__); अवरोध;	\
	शेष:							\
		__bad_size_call_parameter(); अवरोध;			\
	पूर्ण								\
	pscr2_ret__;							\
पूर्ण)

/*
 * Special handling क्रम cmpxchg_द्विगुन.  cmpxchg_द्विगुन is passed two
 * percpu variables.  The first has to be aligned to a द्विगुन word
 * boundary and the second has to follow directly thereafter.
 * We enक्रमce this on all architectures even अगर they करोn't support
 * a द्विगुन cmpxchg inकाष्ठाion, since it's a cheap requirement, and it
 * aव्योमs अवरोधing the requirement क्रम architectures with the inकाष्ठाion.
 */
#घोषणा __pcpu_द्विगुन_call_वापस_bool(stem, pcp1, pcp2, ...)		\
(अणु									\
	bool pdcrb_ret__;						\
	__verअगरy_pcpu_ptr(&(pcp1));					\
	BUILD_BUG_ON(माप(pcp1) != माप(pcp2));			\
	VM_BUG_ON((अचिन्हित दीर्घ)(&(pcp1)) % (2 * माप(pcp1)));	\
	VM_BUG_ON((अचिन्हित दीर्घ)(&(pcp2)) !=				\
		  (अचिन्हित दीर्घ)(&(pcp1)) + माप(pcp1));		\
	चयन(माप(pcp1)) अणु						\
	हाल 1: pdcrb_ret__ = stem##1(pcp1, pcp2, __VA_ARGS__); अवरोध;	\
	हाल 2: pdcrb_ret__ = stem##2(pcp1, pcp2, __VA_ARGS__); अवरोध;	\
	हाल 4: pdcrb_ret__ = stem##4(pcp1, pcp2, __VA_ARGS__); अवरोध;	\
	हाल 8: pdcrb_ret__ = stem##8(pcp1, pcp2, __VA_ARGS__); अवरोध;	\
	शेष:							\
		__bad_size_call_parameter(); अवरोध;			\
	पूर्ण								\
	pdcrb_ret__;							\
पूर्ण)

#घोषणा __pcpu_size_call(stem, variable, ...)				\
करो अणु									\
	__verअगरy_pcpu_ptr(&(variable));					\
	चयन(माप(variable)) अणु					\
		हाल 1: stem##1(variable, __VA_ARGS__);अवरोध;		\
		हाल 2: stem##2(variable, __VA_ARGS__);अवरोध;		\
		हाल 4: stem##4(variable, __VA_ARGS__);अवरोध;		\
		हाल 8: stem##8(variable, __VA_ARGS__);अवरोध;		\
		शेष: 						\
			__bad_size_call_parameter();अवरोध;		\
	पूर्ण								\
पूर्ण जबतक (0)

/*
 * this_cpu operations (C) 2008-2013 Christoph Lameter <cl@linux.com>
 *
 * Optimized manipulation क्रम memory allocated through the per cpu
 * allocator or क्रम addresses of per cpu variables.
 *
 * These operation guarantee exclusivity of access क्रम other operations
 * on the *same* processor. The assumption is that per cpu data is only
 * accessed by a single processor instance (the current one).
 *
 * The arch code can provide optimized implementation by defining macros
 * क्रम certain scalar sizes. F.e. provide this_cpu_add_2() to provide per
 * cpu atomic operations क्रम 2 byte sized RMW actions. If arch code करोes
 * not provide operations क्रम a scalar size then the fallback in the
 * generic code will be used.
 *
 * cmpxchg_द्विगुन replaces two adjacent scalars at once.  The first two
 * parameters are per cpu variables which have to be of the same size.  A
 * truth value is वापसed to indicate success or failure (since a द्विगुन
 * रेजिस्टर result is dअगरficult to handle).  There is very limited hardware
 * support क्रम these operations, so only certain sizes may work.
 */

/*
 * Operations क्रम contexts where we करो not want to करो any checks क्रम
 * preemptions.  Unless strictly necessary, always use [__]this_cpu_*()
 * instead.
 *
 * If there is no other protection through preempt disable and/or disabling
 * पूर्णांकerupts then one of these RMW operations can show unexpected behavior
 * because the execution thपढ़ो was rescheduled on another processor or an
 * पूर्णांकerrupt occurred and the same percpu variable was modअगरied from the
 * पूर्णांकerrupt context.
 */
#घोषणा raw_cpu_पढ़ो(pcp)		__pcpu_size_call_वापस(raw_cpu_पढ़ो_, pcp)
#घोषणा raw_cpu_ग_लिखो(pcp, val)		__pcpu_size_call(raw_cpu_ग_लिखो_, pcp, val)
#घोषणा raw_cpu_add(pcp, val)		__pcpu_size_call(raw_cpu_add_, pcp, val)
#घोषणा raw_cpu_and(pcp, val)		__pcpu_size_call(raw_cpu_and_, pcp, val)
#घोषणा raw_cpu_or(pcp, val)		__pcpu_size_call(raw_cpu_or_, pcp, val)
#घोषणा raw_cpu_add_वापस(pcp, val)	__pcpu_size_call_वापस2(raw_cpu_add_वापस_, pcp, val)
#घोषणा raw_cpu_xchg(pcp, nval)		__pcpu_size_call_वापस2(raw_cpu_xchg_, pcp, nval)
#घोषणा raw_cpu_cmpxchg(pcp, oval, nval) \
	__pcpu_size_call_वापस2(raw_cpu_cmpxchg_, pcp, oval, nval)
#घोषणा raw_cpu_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	__pcpu_द्विगुन_call_वापस_bool(raw_cpu_cmpxchg_द्विगुन_, pcp1, pcp2, oval1, oval2, nval1, nval2)

#घोषणा raw_cpu_sub(pcp, val)		raw_cpu_add(pcp, -(val))
#घोषणा raw_cpu_inc(pcp)		raw_cpu_add(pcp, 1)
#घोषणा raw_cpu_dec(pcp)		raw_cpu_sub(pcp, 1)
#घोषणा raw_cpu_sub_वापस(pcp, val)	raw_cpu_add_वापस(pcp, -(typeof(pcp))(val))
#घोषणा raw_cpu_inc_वापस(pcp)		raw_cpu_add_वापस(pcp, 1)
#घोषणा raw_cpu_dec_वापस(pcp)		raw_cpu_add_वापस(pcp, -1)

/*
 * Operations क्रम contexts that are safe from preemption/पूर्णांकerrupts.  These
 * operations verअगरy that preemption is disabled.
 */
#घोषणा __this_cpu_पढ़ो(pcp)						\
(अणु									\
	__this_cpu_preempt_check("read");				\
	raw_cpu_पढ़ो(pcp);						\
पूर्ण)

#घोषणा __this_cpu_ग_लिखो(pcp, val)					\
(अणु									\
	__this_cpu_preempt_check("write");				\
	raw_cpu_ग_लिखो(pcp, val);					\
पूर्ण)

#घोषणा __this_cpu_add(pcp, val)					\
(अणु									\
	__this_cpu_preempt_check("add");				\
	raw_cpu_add(pcp, val);						\
पूर्ण)

#घोषणा __this_cpu_and(pcp, val)					\
(अणु									\
	__this_cpu_preempt_check("and");				\
	raw_cpu_and(pcp, val);						\
पूर्ण)

#घोषणा __this_cpu_or(pcp, val)						\
(अणु									\
	__this_cpu_preempt_check("or");					\
	raw_cpu_or(pcp, val);						\
पूर्ण)

#घोषणा __this_cpu_add_वापस(pcp, val)					\
(अणु									\
	__this_cpu_preempt_check("add_return");				\
	raw_cpu_add_वापस(pcp, val);					\
पूर्ण)

#घोषणा __this_cpu_xchg(pcp, nval)					\
(अणु									\
	__this_cpu_preempt_check("xchg");				\
	raw_cpu_xchg(pcp, nval);					\
पूर्ण)

#घोषणा __this_cpu_cmpxchg(pcp, oval, nval)				\
(अणु									\
	__this_cpu_preempt_check("cmpxchg");				\
	raw_cpu_cmpxchg(pcp, oval, nval);				\
पूर्ण)

#घोषणा __this_cpu_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2) \
(अणु	__this_cpu_preempt_check("cmpxchg_double");			\
	raw_cpu_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2);	\
पूर्ण)

#घोषणा __this_cpu_sub(pcp, val)	__this_cpu_add(pcp, -(typeof(pcp))(val))
#घोषणा __this_cpu_inc(pcp)		__this_cpu_add(pcp, 1)
#घोषणा __this_cpu_dec(pcp)		__this_cpu_sub(pcp, 1)
#घोषणा __this_cpu_sub_वापस(pcp, val)	__this_cpu_add_वापस(pcp, -(typeof(pcp))(val))
#घोषणा __this_cpu_inc_वापस(pcp)	__this_cpu_add_वापस(pcp, 1)
#घोषणा __this_cpu_dec_वापस(pcp)	__this_cpu_add_वापस(pcp, -1)

/*
 * Operations with implied preemption/पूर्णांकerrupt protection.  These
 * operations can be used without worrying about preemption or पूर्णांकerrupt.
 */
#घोषणा this_cpu_पढ़ो(pcp)		__pcpu_size_call_वापस(this_cpu_पढ़ो_, pcp)
#घोषणा this_cpu_ग_लिखो(pcp, val)	__pcpu_size_call(this_cpu_ग_लिखो_, pcp, val)
#घोषणा this_cpu_add(pcp, val)		__pcpu_size_call(this_cpu_add_, pcp, val)
#घोषणा this_cpu_and(pcp, val)		__pcpu_size_call(this_cpu_and_, pcp, val)
#घोषणा this_cpu_or(pcp, val)		__pcpu_size_call(this_cpu_or_, pcp, val)
#घोषणा this_cpu_add_वापस(pcp, val)	__pcpu_size_call_वापस2(this_cpu_add_वापस_, pcp, val)
#घोषणा this_cpu_xchg(pcp, nval)	__pcpu_size_call_वापस2(this_cpu_xchg_, pcp, nval)
#घोषणा this_cpu_cmpxchg(pcp, oval, nval) \
	__pcpu_size_call_वापस2(this_cpu_cmpxchg_, pcp, oval, nval)
#घोषणा this_cpu_cmpxchg_द्विगुन(pcp1, pcp2, oval1, oval2, nval1, nval2) \
	__pcpu_द्विगुन_call_वापस_bool(this_cpu_cmpxchg_द्विगुन_, pcp1, pcp2, oval1, oval2, nval1, nval2)

#घोषणा this_cpu_sub(pcp, val)		this_cpu_add(pcp, -(typeof(pcp))(val))
#घोषणा this_cpu_inc(pcp)		this_cpu_add(pcp, 1)
#घोषणा this_cpu_dec(pcp)		this_cpu_sub(pcp, 1)
#घोषणा this_cpu_sub_वापस(pcp, val)	this_cpu_add_वापस(pcp, -(typeof(pcp))(val))
#घोषणा this_cpu_inc_वापस(pcp)	this_cpu_add_वापस(pcp, 1)
#घोषणा this_cpu_dec_वापस(pcp)	this_cpu_add_वापस(pcp, -1)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _LINUX_PERCPU_DEFS_H */

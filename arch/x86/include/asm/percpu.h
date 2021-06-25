<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PERCPU_H
#घोषणा _ASM_X86_PERCPU_H

#अगर_घोषित CONFIG_X86_64
#घोषणा __percpu_seg		gs
#अन्यथा
#घोषणा __percpu_seg		fs
#पूर्ण_अगर

#अगर_घोषित __ASSEMBLY__

#अगर_घोषित CONFIG_SMP
#घोषणा PER_CPU_VAR(var)	%__percpu_seg:var
#अन्यथा /* ! SMP */
#घोषणा PER_CPU_VAR(var)	var
#पूर्ण_अगर	/* SMP */

#अगर_घोषित CONFIG_X86_64_SMP
#घोषणा INIT_PER_CPU_VAR(var)  init_per_cpu__##var
#अन्यथा
#घोषणा INIT_PER_CPU_VAR(var)  var
#पूर्ण_अगर

#अन्यथा /* ...!ASSEMBLY */

#समावेश <linux/kernel.h>
#समावेश <linux/stringअगरy.h>

#अगर_घोषित CONFIG_SMP
#घोषणा __percpu_prefix		"%%"__stringअगरy(__percpu_seg)":"
#घोषणा __my_cpu_offset		this_cpu_पढ़ो(this_cpu_off)

/*
 * Compared to the generic __my_cpu_offset version, the following
 * saves one inकाष्ठाion and aव्योमs clobbering a temp रेजिस्टर.
 */
#घोषणा arch_raw_cpu_ptr(ptr)				\
(अणु							\
	अचिन्हित दीर्घ tcp_ptr__;			\
	यंत्र अस्थिर("add " __percpu_arg(1) ", %0"	\
		     : "=r" (tcp_ptr__)			\
		     : "m" (this_cpu_off), "0" (ptr));	\
	(typeof(*(ptr)) __kernel __क्रमce *)tcp_ptr__;	\
पूर्ण)
#अन्यथा
#घोषणा __percpu_prefix		""
#पूर्ण_अगर

#घोषणा __percpu_arg(x)		__percpu_prefix "%" #x

/*
 * Initialized poपूर्णांकers to per-cpu variables needed क्रम the boot
 * processor need to use these macros to get the proper address
 * offset from __per_cpu_load on SMP.
 *
 * There also must be an entry in vmlinux_64.lds.S
 */
#घोषणा DECLARE_INIT_PER_CPU(var) \
       बाह्य typeof(var) init_per_cpu_var(var)

#अगर_घोषित CONFIG_X86_64_SMP
#घोषणा init_per_cpu_var(var)  init_per_cpu__##var
#अन्यथा
#घोषणा init_per_cpu_var(var)  var
#पूर्ण_अगर

/* For arch-specअगरic code, we can use direct single-insn ops (they
 * करोn't give an lvalue though). */

#घोषणा __pcpu_type_1 u8
#घोषणा __pcpu_type_2 u16
#घोषणा __pcpu_type_4 u32
#घोषणा __pcpu_type_8 u64

#घोषणा __pcpu_cast_1(val) ((u8)(((अचिन्हित दीर्घ) val) & 0xff))
#घोषणा __pcpu_cast_2(val) ((u16)(((अचिन्हित दीर्घ) val) & 0xffff))
#घोषणा __pcpu_cast_4(val) ((u32)(((अचिन्हित दीर्घ) val) & 0xffffffff))
#घोषणा __pcpu_cast_8(val) ((u64)(val))

#घोषणा __pcpu_op1_1(op, dst) op "b " dst
#घोषणा __pcpu_op1_2(op, dst) op "w " dst
#घोषणा __pcpu_op1_4(op, dst) op "l " dst
#घोषणा __pcpu_op1_8(op, dst) op "q " dst

#घोषणा __pcpu_op2_1(op, src, dst) op "b " src ", " dst
#घोषणा __pcpu_op2_2(op, src, dst) op "w " src ", " dst
#घोषणा __pcpu_op2_4(op, src, dst) op "l " src ", " dst
#घोषणा __pcpu_op2_8(op, src, dst) op "q " src ", " dst

#घोषणा __pcpu_reg_1(mod, x) mod "q" (x)
#घोषणा __pcpu_reg_2(mod, x) mod "r" (x)
#घोषणा __pcpu_reg_4(mod, x) mod "r" (x)
#घोषणा __pcpu_reg_8(mod, x) mod "r" (x)

#घोषणा __pcpu_reg_imm_1(x) "qi" (x)
#घोषणा __pcpu_reg_imm_2(x) "ri" (x)
#घोषणा __pcpu_reg_imm_4(x) "ri" (x)
#घोषणा __pcpu_reg_imm_8(x) "re" (x)

#घोषणा percpu_to_op(size, qual, op, _var, _val)			\
करो अणु									\
	__pcpu_type_##size pto_val__ = __pcpu_cast_##size(_val);	\
	अगर (0) अणु		                                        \
		typeof(_var) pto_पंचांगp__;					\
		pto_पंचांगp__ = (_val);					\
		(व्योम)pto_पंचांगp__;					\
	पूर्ण								\
	यंत्र qual(__pcpu_op2_##size(op, "%[val]", __percpu_arg([var]))	\
	    : [var] "+m" (_var)						\
	    : [val] __pcpu_reg_imm_##size(pto_val__));			\
पूर्ण जबतक (0)

#घोषणा percpu_unary_op(size, qual, op, _var)				\
(अणु									\
	यंत्र qual (__pcpu_op1_##size(op, __percpu_arg([var]))		\
	    : [var] "+m" (_var));					\
पूर्ण)

/*
 * Generate a percpu add to memory inकाष्ठाion and optimize code
 * अगर one is added or subtracted.
 */
#घोषणा percpu_add_op(size, qual, var, val)				\
करो अणु									\
	स्थिर पूर्णांक pao_ID__ = (__builtin_स्थिरant_p(val) &&		\
			      ((val) == 1 || (val) == -1)) ?		\
				(पूर्णांक)(val) : 0;				\
	अगर (0) अणु							\
		typeof(var) pao_पंचांगp__;					\
		pao_पंचांगp__ = (val);					\
		(व्योम)pao_पंचांगp__;					\
	पूर्ण								\
	अगर (pao_ID__ == 1)						\
		percpu_unary_op(size, qual, "inc", var);		\
	अन्यथा अगर (pao_ID__ == -1)					\
		percpu_unary_op(size, qual, "dec", var);		\
	अन्यथा								\
		percpu_to_op(size, qual, "add", var, val);		\
पूर्ण जबतक (0)

#घोषणा percpu_from_op(size, qual, op, _var)				\
(अणु									\
	__pcpu_type_##size pfo_val__;					\
	यंत्र qual (__pcpu_op2_##size(op, __percpu_arg([var]), "%[val]")	\
	    : [val] __pcpu_reg_##size("=", pfo_val__)			\
	    : [var] "m" (_var));					\
	(typeof(_var))(अचिन्हित दीर्घ) pfo_val__;			\
पूर्ण)

#घोषणा percpu_stable_op(size, op, _var)				\
(अणु									\
	__pcpu_type_##size pfo_val__;					\
	यंत्र(__pcpu_op2_##size(op, __percpu_arg(P[var]), "%[val]")	\
	    : [val] __pcpu_reg_##size("=", pfo_val__)			\
	    : [var] "p" (&(_var)));					\
	(typeof(_var))(अचिन्हित दीर्घ) pfo_val__;			\
पूर्ण)

/*
 * Add वापस operation
 */
#घोषणा percpu_add_वापस_op(size, qual, _var, _val)			\
(अणु									\
	__pcpu_type_##size paro_पंचांगp__ = __pcpu_cast_##size(_val);	\
	यंत्र qual (__pcpu_op2_##size("xadd", "%[tmp]",			\
				     __percpu_arg([var]))		\
		  : [पंचांगp] __pcpu_reg_##size("+", paro_पंचांगp__),		\
		    [var] "+m" (_var)					\
		  : : "memory");					\
	(typeof(_var))(अचिन्हित दीर्घ) (paro_पंचांगp__ + _val);		\
पूर्ण)

/*
 * xchg is implemented using cmpxchg without a lock prefix. xchg is
 * expensive due to the implied lock prefix.  The processor cannot prefetch
 * cachelines अगर xchg is used.
 */
#घोषणा percpu_xchg_op(size, qual, _var, _nval)				\
(अणु									\
	__pcpu_type_##size pxo_old__;					\
	__pcpu_type_##size pxo_new__ = __pcpu_cast_##size(_nval);	\
	यंत्र qual (__pcpu_op2_##size("mov", __percpu_arg([var]),		\
				    "%[oval]")				\
		  "\n1:\t"						\
		  __pcpu_op2_##size("cmpxchg", "%[nval]",		\
				    __percpu_arg([var]))		\
		  "\n\tjnz 1b"						\
		  : [oval] "=&a" (pxo_old__),				\
		    [var] "+m" (_var)					\
		  : [nval] __pcpu_reg_##size(, pxo_new__)		\
		  : "memory");						\
	(typeof(_var))(अचिन्हित दीर्घ) pxo_old__;			\
पूर्ण)

/*
 * cmpxchg has no such implied lock semantics as a result it is much
 * more efficient क्रम cpu local operations.
 */
#घोषणा percpu_cmpxchg_op(size, qual, _var, _oval, _nval)		\
(अणु									\
	__pcpu_type_##size pco_old__ = __pcpu_cast_##size(_oval);	\
	__pcpu_type_##size pco_new__ = __pcpu_cast_##size(_nval);	\
	यंत्र qual (__pcpu_op2_##size("cmpxchg", "%[nval]",		\
				    __percpu_arg([var]))		\
		  : [oval] "+a" (pco_old__),				\
		    [var] "+m" (_var)					\
		  : [nval] __pcpu_reg_##size(, pco_new__)		\
		  : "memory");						\
	(typeof(_var))(अचिन्हित दीर्घ) pco_old__;			\
पूर्ण)

/*
 * this_cpu_पढ़ो() makes gcc load the percpu variable every समय it is
 * accessed जबतक this_cpu_पढ़ो_stable() allows the value to be cached.
 * this_cpu_पढ़ो_stable() is more efficient and can be used अगर its value
 * is guaranteed to be valid across cpus.  The current users include
 * get_current() and get_thपढ़ो_info() both of which are actually
 * per-thपढ़ो variables implemented as per-cpu variables and thus
 * stable क्रम the duration of the respective task.
 */
#घोषणा this_cpu_पढ़ो_stable_1(pcp)	percpu_stable_op(1, "mov", pcp)
#घोषणा this_cpu_पढ़ो_stable_2(pcp)	percpu_stable_op(2, "mov", pcp)
#घोषणा this_cpu_पढ़ो_stable_4(pcp)	percpu_stable_op(4, "mov", pcp)
#घोषणा this_cpu_पढ़ो_stable_8(pcp)	percpu_stable_op(8, "mov", pcp)
#घोषणा this_cpu_पढ़ो_stable(pcp)	__pcpu_size_call_वापस(this_cpu_पढ़ो_stable_, pcp)

#घोषणा raw_cpu_पढ़ो_1(pcp)		percpu_from_op(1, , "mov", pcp)
#घोषणा raw_cpu_पढ़ो_2(pcp)		percpu_from_op(2, , "mov", pcp)
#घोषणा raw_cpu_पढ़ो_4(pcp)		percpu_from_op(4, , "mov", pcp)

#घोषणा raw_cpu_ग_लिखो_1(pcp, val)	percpu_to_op(1, , "mov", (pcp), val)
#घोषणा raw_cpu_ग_लिखो_2(pcp, val)	percpu_to_op(2, , "mov", (pcp), val)
#घोषणा raw_cpu_ग_लिखो_4(pcp, val)	percpu_to_op(4, , "mov", (pcp), val)
#घोषणा raw_cpu_add_1(pcp, val)		percpu_add_op(1, , (pcp), val)
#घोषणा raw_cpu_add_2(pcp, val)		percpu_add_op(2, , (pcp), val)
#घोषणा raw_cpu_add_4(pcp, val)		percpu_add_op(4, , (pcp), val)
#घोषणा raw_cpu_and_1(pcp, val)		percpu_to_op(1, , "and", (pcp), val)
#घोषणा raw_cpu_and_2(pcp, val)		percpu_to_op(2, , "and", (pcp), val)
#घोषणा raw_cpu_and_4(pcp, val)		percpu_to_op(4, , "and", (pcp), val)
#घोषणा raw_cpu_or_1(pcp, val)		percpu_to_op(1, , "or", (pcp), val)
#घोषणा raw_cpu_or_2(pcp, val)		percpu_to_op(2, , "or", (pcp), val)
#घोषणा raw_cpu_or_4(pcp, val)		percpu_to_op(4, , "or", (pcp), val)

/*
 * raw_cpu_xchg() can use a load-store since it is not required to be
 * IRQ-safe.
 */
#घोषणा raw_percpu_xchg_op(var, nval)					\
(अणु									\
	typeof(var) pxo_ret__ = raw_cpu_पढ़ो(var);			\
	raw_cpu_ग_लिखो(var, (nval));					\
	pxo_ret__;							\
पूर्ण)

#घोषणा raw_cpu_xchg_1(pcp, val)	raw_percpu_xchg_op(pcp, val)
#घोषणा raw_cpu_xchg_2(pcp, val)	raw_percpu_xchg_op(pcp, val)
#घोषणा raw_cpu_xchg_4(pcp, val)	raw_percpu_xchg_op(pcp, val)

#घोषणा this_cpu_पढ़ो_1(pcp)		percpu_from_op(1, अस्थिर, "mov", pcp)
#घोषणा this_cpu_पढ़ो_2(pcp)		percpu_from_op(2, अस्थिर, "mov", pcp)
#घोषणा this_cpu_पढ़ो_4(pcp)		percpu_from_op(4, अस्थिर, "mov", pcp)
#घोषणा this_cpu_ग_लिखो_1(pcp, val)	percpu_to_op(1, अस्थिर, "mov", (pcp), val)
#घोषणा this_cpu_ग_लिखो_2(pcp, val)	percpu_to_op(2, अस्थिर, "mov", (pcp), val)
#घोषणा this_cpu_ग_लिखो_4(pcp, val)	percpu_to_op(4, अस्थिर, "mov", (pcp), val)
#घोषणा this_cpu_add_1(pcp, val)	percpu_add_op(1, अस्थिर, (pcp), val)
#घोषणा this_cpu_add_2(pcp, val)	percpu_add_op(2, अस्थिर, (pcp), val)
#घोषणा this_cpu_add_4(pcp, val)	percpu_add_op(4, अस्थिर, (pcp), val)
#घोषणा this_cpu_and_1(pcp, val)	percpu_to_op(1, अस्थिर, "and", (pcp), val)
#घोषणा this_cpu_and_2(pcp, val)	percpu_to_op(2, अस्थिर, "and", (pcp), val)
#घोषणा this_cpu_and_4(pcp, val)	percpu_to_op(4, अस्थिर, "and", (pcp), val)
#घोषणा this_cpu_or_1(pcp, val)		percpu_to_op(1, अस्थिर, "or", (pcp), val)
#घोषणा this_cpu_or_2(pcp, val)		percpu_to_op(2, अस्थिर, "or", (pcp), val)
#घोषणा this_cpu_or_4(pcp, val)		percpu_to_op(4, अस्थिर, "or", (pcp), val)
#घोषणा this_cpu_xchg_1(pcp, nval)	percpu_xchg_op(1, अस्थिर, pcp, nval)
#घोषणा this_cpu_xchg_2(pcp, nval)	percpu_xchg_op(2, अस्थिर, pcp, nval)
#घोषणा this_cpu_xchg_4(pcp, nval)	percpu_xchg_op(4, अस्थिर, pcp, nval)

#घोषणा raw_cpu_add_वापस_1(pcp, val)		percpu_add_वापस_op(1, , pcp, val)
#घोषणा raw_cpu_add_वापस_2(pcp, val)		percpu_add_वापस_op(2, , pcp, val)
#घोषणा raw_cpu_add_वापस_4(pcp, val)		percpu_add_वापस_op(4, , pcp, val)
#घोषणा raw_cpu_cmpxchg_1(pcp, oval, nval)	percpu_cmpxchg_op(1, , pcp, oval, nval)
#घोषणा raw_cpu_cmpxchg_2(pcp, oval, nval)	percpu_cmpxchg_op(2, , pcp, oval, nval)
#घोषणा raw_cpu_cmpxchg_4(pcp, oval, nval)	percpu_cmpxchg_op(4, , pcp, oval, nval)

#घोषणा this_cpu_add_वापस_1(pcp, val)		percpu_add_वापस_op(1, अस्थिर, pcp, val)
#घोषणा this_cpu_add_वापस_2(pcp, val)		percpu_add_वापस_op(2, अस्थिर, pcp, val)
#घोषणा this_cpu_add_वापस_4(pcp, val)		percpu_add_वापस_op(4, अस्थिर, pcp, val)
#घोषणा this_cpu_cmpxchg_1(pcp, oval, nval)	percpu_cmpxchg_op(1, अस्थिर, pcp, oval, nval)
#घोषणा this_cpu_cmpxchg_2(pcp, oval, nval)	percpu_cmpxchg_op(2, अस्थिर, pcp, oval, nval)
#घोषणा this_cpu_cmpxchg_4(pcp, oval, nval)	percpu_cmpxchg_op(4, अस्थिर, pcp, oval, nval)

#अगर_घोषित CONFIG_X86_CMPXCHG64
#घोषणा percpu_cmpxchg8b_द्विगुन(pcp1, pcp2, o1, o2, n1, n2)		\
(अणु									\
	bool __ret;							\
	typeof(pcp1) __o1 = (o1), __n1 = (n1);				\
	typeof(pcp2) __o2 = (o2), __n2 = (n2);				\
	यंत्र अस्थिर("cmpxchg8b "__percpu_arg(1)			\
		     CC_SET(z)						\
		     : CC_OUT(z) (__ret), "+m" (pcp1), "+m" (pcp2), "+a" (__o1), "+d" (__o2) \
		     : "b" (__n1), "c" (__n2));				\
	__ret;								\
पूर्ण)

#घोषणा raw_cpu_cmpxchg_द्विगुन_4	percpu_cmpxchg8b_द्विगुन
#घोषणा this_cpu_cmpxchg_द्विगुन_4	percpu_cmpxchg8b_द्विगुन
#पूर्ण_अगर /* CONFIG_X86_CMPXCHG64 */

/*
 * Per cpu atomic 64 bit operations are only available under 64 bit.
 * 32 bit must fall back to generic operations.
 */
#अगर_घोषित CONFIG_X86_64
#घोषणा raw_cpu_पढ़ो_8(pcp)			percpu_from_op(8, , "mov", pcp)
#घोषणा raw_cpu_ग_लिखो_8(pcp, val)		percpu_to_op(8, , "mov", (pcp), val)
#घोषणा raw_cpu_add_8(pcp, val)			percpu_add_op(8, , (pcp), val)
#घोषणा raw_cpu_and_8(pcp, val)			percpu_to_op(8, , "and", (pcp), val)
#घोषणा raw_cpu_or_8(pcp, val)			percpu_to_op(8, , "or", (pcp), val)
#घोषणा raw_cpu_add_वापस_8(pcp, val)		percpu_add_वापस_op(8, , pcp, val)
#घोषणा raw_cpu_xchg_8(pcp, nval)		raw_percpu_xchg_op(pcp, nval)
#घोषणा raw_cpu_cmpxchg_8(pcp, oval, nval)	percpu_cmpxchg_op(8, , pcp, oval, nval)

#घोषणा this_cpu_पढ़ो_8(pcp)			percpu_from_op(8, अस्थिर, "mov", pcp)
#घोषणा this_cpu_ग_लिखो_8(pcp, val)		percpu_to_op(8, अस्थिर, "mov", (pcp), val)
#घोषणा this_cpu_add_8(pcp, val)		percpu_add_op(8, अस्थिर, (pcp), val)
#घोषणा this_cpu_and_8(pcp, val)		percpu_to_op(8, अस्थिर, "and", (pcp), val)
#घोषणा this_cpu_or_8(pcp, val)			percpu_to_op(8, अस्थिर, "or", (pcp), val)
#घोषणा this_cpu_add_वापस_8(pcp, val)		percpu_add_वापस_op(8, अस्थिर, pcp, val)
#घोषणा this_cpu_xchg_8(pcp, nval)		percpu_xchg_op(8, अस्थिर, pcp, nval)
#घोषणा this_cpu_cmpxchg_8(pcp, oval, nval)	percpu_cmpxchg_op(8, अस्थिर, pcp, oval, nval)

/*
 * Pretty complex macro to generate cmpxchg16 inकाष्ठाion.  The inकाष्ठाion
 * is not supported on early AMD64 processors so we must be able to emulate
 * it in software.  The address used in the cmpxchg16 inकाष्ठाion must be
 * aligned to a 16 byte boundary.
 */
#घोषणा percpu_cmpxchg16b_द्विगुन(pcp1, pcp2, o1, o2, n1, n2)		\
(अणु									\
	bool __ret;							\
	typeof(pcp1) __o1 = (o1), __n1 = (n1);				\
	typeof(pcp2) __o2 = (o2), __n2 = (n2);				\
	alternative_io("leaq %P1,%%rsi\n\tcall this_cpu_cmpxchg16b_emu\n\t", \
		       "cmpxchg16b " __percpu_arg(1) "\n\tsetz %0\n\t",	\
		       X86_FEATURE_CX16,				\
		       ASM_OUTPUT2("=a" (__ret), "+m" (pcp1),		\
				   "+m" (pcp2), "+d" (__o2)),		\
		       "b" (__n1), "c" (__n2), "a" (__o1) : "rsi");	\
	__ret;								\
पूर्ण)

#घोषणा raw_cpu_cmpxchg_द्विगुन_8	percpu_cmpxchg16b_द्विगुन
#घोषणा this_cpu_cmpxchg_द्विगुन_8	percpu_cmpxchg16b_द्विगुन

#पूर्ण_अगर

अटल __always_अंतरभूत bool x86_this_cpu_स्थिरant_test_bit(अचिन्हित पूर्णांक nr,
                        स्थिर अचिन्हित दीर्घ __percpu *addr)
अणु
	अचिन्हित दीर्घ __percpu *a =
		(अचिन्हित दीर्घ __percpu *)addr + nr / BITS_PER_LONG;

#अगर_घोषित CONFIG_X86_64
	वापस ((1UL << (nr % BITS_PER_LONG)) & raw_cpu_पढ़ो_8(*a)) != 0;
#अन्यथा
	वापस ((1UL << (nr % BITS_PER_LONG)) & raw_cpu_पढ़ो_4(*a)) != 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool x86_this_cpu_variable_test_bit(पूर्णांक nr,
                        स्थिर अचिन्हित दीर्घ __percpu *addr)
अणु
	bool oldbit;

	यंत्र अस्थिर("btl "__percpu_arg(2)",%1"
			CC_SET(c)
			: CC_OUT(c) (oldbit)
			: "m" (*(अचिन्हित दीर्घ __percpu *)addr), "Ir" (nr));

	वापस oldbit;
पूर्ण

#घोषणा x86_this_cpu_test_bit(nr, addr)			\
	(__builtin_स्थिरant_p((nr))			\
	 ? x86_this_cpu_स्थिरant_test_bit((nr), (addr))	\
	 : x86_this_cpu_variable_test_bit((nr), (addr)))


#समावेश <यंत्र-generic/percpu.h>

/* We can use this directly क्रम local CPU (faster). */
DECLARE_PER_CPU_READ_MOSTLY(अचिन्हित दीर्घ, this_cpu_off);

#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_SMP

/*
 * Define the "EARLY_PER_CPU" macros.  These are used क्रम some per_cpu
 * variables that are initialized and accessed beक्रमe there are per_cpu
 * areas allocated.
 */

#घोषणा	DEFINE_EARLY_PER_CPU(_type, _name, _initvalue)			\
	DEFINE_PER_CPU(_type, _name) = _initvalue;			\
	__typeof__(_type) _name##_early_map[NR_CPUS] __initdata =	\
				अणु [0 ... NR_CPUS-1] = _initvalue पूर्ण;	\
	__typeof__(_type) *_name##_early_ptr __refdata = _name##_early_map

#घोषणा DEFINE_EARLY_PER_CPU_READ_MOSTLY(_type, _name, _initvalue)	\
	DEFINE_PER_CPU_READ_MOSTLY(_type, _name) = _initvalue;		\
	__typeof__(_type) _name##_early_map[NR_CPUS] __initdata =	\
				अणु [0 ... NR_CPUS-1] = _initvalue पूर्ण;	\
	__typeof__(_type) *_name##_early_ptr __refdata = _name##_early_map

#घोषणा EXPORT_EARLY_PER_CPU_SYMBOL(_name)			\
	EXPORT_PER_CPU_SYMBOL(_name)

#घोषणा DECLARE_EARLY_PER_CPU(_type, _name)			\
	DECLARE_PER_CPU(_type, _name);				\
	बाह्य __typeof__(_type) *_name##_early_ptr;		\
	बाह्य __typeof__(_type)  _name##_early_map[]

#घोषणा DECLARE_EARLY_PER_CPU_READ_MOSTLY(_type, _name)		\
	DECLARE_PER_CPU_READ_MOSTLY(_type, _name);		\
	बाह्य __typeof__(_type) *_name##_early_ptr;		\
	बाह्य __typeof__(_type)  _name##_early_map[]

#घोषणा	early_per_cpu_ptr(_name) (_name##_early_ptr)
#घोषणा	early_per_cpu_map(_name, _idx) (_name##_early_map[_idx])
#घोषणा	early_per_cpu(_name, _cpu) 				\
	*(early_per_cpu_ptr(_name) ?				\
		&early_per_cpu_ptr(_name)[_cpu] :		\
		&per_cpu(_name, _cpu))

#अन्यथा	/* !CONFIG_SMP */
#घोषणा	DEFINE_EARLY_PER_CPU(_type, _name, _initvalue)		\
	DEFINE_PER_CPU(_type, _name) = _initvalue

#घोषणा DEFINE_EARLY_PER_CPU_READ_MOSTLY(_type, _name, _initvalue)	\
	DEFINE_PER_CPU_READ_MOSTLY(_type, _name) = _initvalue

#घोषणा EXPORT_EARLY_PER_CPU_SYMBOL(_name)			\
	EXPORT_PER_CPU_SYMBOL(_name)

#घोषणा DECLARE_EARLY_PER_CPU(_type, _name)			\
	DECLARE_PER_CPU(_type, _name)

#घोषणा DECLARE_EARLY_PER_CPU_READ_MOSTLY(_type, _name)		\
	DECLARE_PER_CPU_READ_MOSTLY(_type, _name)

#घोषणा	early_per_cpu(_name, _cpu) per_cpu(_name, _cpu)
#घोषणा	early_per_cpu_ptr(_name) शून्य
/* no early_per_cpu_map() */

#पूर्ण_अगर	/* !CONFIG_SMP */

#पूर्ण_अगर /* _ASM_X86_PERCPU_H */

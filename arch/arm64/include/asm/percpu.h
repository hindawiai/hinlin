<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 ARM Ltd.
 */
#अगर_अघोषित __ASM_PERCPU_H
#घोषणा __ASM_PERCPU_H

#समावेश <linux/preempt.h>

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/stack_poपूर्णांकer.h>

अटल अंतरभूत व्योम set_my_cpu_offset(अचिन्हित दीर्घ off)
अणु
	यंत्र अस्थिर(ALTERNATIVE("msr tpidr_el1, %0",
				 "msr tpidr_el2, %0",
				 ARM64_HAS_VIRT_HOST_EXTN)
			:: "r" (off) : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __hyp_my_cpu_offset(व्योम)
अणु
	/*
	 * Non-VHE hyp code runs with preemption disabled. No need to hazard
	 * the रेजिस्टर access against barrier() as in __kern_my_cpu_offset.
	 */
	वापस पढ़ो_sysreg(tpidr_el2);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __kern_my_cpu_offset(व्योम)
अणु
	अचिन्हित दीर्घ off;

	/*
	 * We want to allow caching the value, so aव्योम using अस्थिर and
	 * instead use a fake stack पढ़ो to hazard against barrier().
	 */
	यंत्र(ALTERNATIVE("mrs %0, tpidr_el1",
			"mrs %0, tpidr_el2",
			ARM64_HAS_VIRT_HOST_EXTN)
		: "=r" (off) :
		"Q" (*(स्थिर अचिन्हित दीर्घ *)current_stack_poपूर्णांकer));

	वापस off;
पूर्ण

#अगर_घोषित __KVM_NVHE_HYPERVISOR__
#घोषणा __my_cpu_offset __hyp_my_cpu_offset()
#अन्यथा
#घोषणा __my_cpu_offset __kern_my_cpu_offset()
#पूर्ण_अगर

#घोषणा PERCPU_RW_OPS(sz)						\
अटल अंतरभूत अचिन्हित दीर्घ __percpu_पढ़ो_##sz(व्योम *ptr)		\
अणु									\
	वापस READ_ONCE(*(u##sz *)ptr);				\
पूर्ण									\
									\
अटल अंतरभूत व्योम __percpu_ग_लिखो_##sz(व्योम *ptr, अचिन्हित दीर्घ val)	\
अणु									\
	WRITE_ONCE(*(u##sz *)ptr, (u##sz)val);				\
पूर्ण

#घोषणा __PERCPU_OP_CASE(w, sfx, name, sz, op_llsc, op_lse)		\
अटल अंतरभूत व्योम							\
__percpu_##name##_हाल_##sz(व्योम *ptr, अचिन्हित दीर्घ val)		\
अणु									\
	अचिन्हित पूर्णांक loop;						\
	u##sz पंचांगp;							\
									\
	यंत्र अस्थिर (ARM64_LSE_ATOMIC_INSN(				\
	/* LL/SC */							\
	"1:	ldxr" #sfx "\t%" #w "[tmp], %[ptr]\n"			\
		#op_llsc "\t%" #w "[tmp], %" #w "[tmp], %" #w "[val]\n"	\
	"	stxr" #sfx "\t%w[loop], %" #w "[tmp], %[ptr]\n"		\
	"	cbnz	%w[loop], 1b",					\
	/* LSE atomics */						\
		#op_lse "\t%" #w "[val], %[ptr]\n"			\
		__nops(3))						\
	: [loop] "=&r" (loop), [पंचांगp] "=&r" (पंचांगp),			\
	  [ptr] "+Q"(*(u##sz *)ptr)					\
	: [val] "r" ((u##sz)(val)));					\
पूर्ण

#घोषणा __PERCPU_RET_OP_CASE(w, sfx, name, sz, op_llsc, op_lse)		\
अटल अंतरभूत u##sz							\
__percpu_##name##_वापस_हाल_##sz(व्योम *ptr, अचिन्हित दीर्घ val)	\
अणु									\
	अचिन्हित पूर्णांक loop;						\
	u##sz ret;							\
									\
	यंत्र अस्थिर (ARM64_LSE_ATOMIC_INSN(				\
	/* LL/SC */							\
	"1:	ldxr" #sfx "\t%" #w "[ret], %[ptr]\n"			\
		#op_llsc "\t%" #w "[ret], %" #w "[ret], %" #w "[val]\n"	\
	"	stxr" #sfx "\t%w[loop], %" #w "[ret], %[ptr]\n"		\
	"	cbnz	%w[loop], 1b",					\
	/* LSE atomics */						\
		#op_lse "\t%" #w "[val], %" #w "[ret], %[ptr]\n"	\
		#op_llsc "\t%" #w "[ret], %" #w "[ret], %" #w "[val]\n"	\
		__nops(2))						\
	: [loop] "=&r" (loop), [ret] "=&r" (ret),			\
	  [ptr] "+Q"(*(u##sz *)ptr)					\
	: [val] "r" ((u##sz)(val)));					\
									\
	वापस ret;							\
पूर्ण

#घोषणा PERCPU_OP(name, op_llsc, op_lse)				\
	__PERCPU_OP_CASE(w, b, name,  8, op_llsc, op_lse)		\
	__PERCPU_OP_CASE(w, h, name, 16, op_llsc, op_lse)		\
	__PERCPU_OP_CASE(w,  , name, 32, op_llsc, op_lse)		\
	__PERCPU_OP_CASE( ,  , name, 64, op_llsc, op_lse)

#घोषणा PERCPU_RET_OP(name, op_llsc, op_lse)				\
	__PERCPU_RET_OP_CASE(w, b, name,  8, op_llsc, op_lse)		\
	__PERCPU_RET_OP_CASE(w, h, name, 16, op_llsc, op_lse)		\
	__PERCPU_RET_OP_CASE(w,  , name, 32, op_llsc, op_lse)		\
	__PERCPU_RET_OP_CASE( ,  , name, 64, op_llsc, op_lse)

PERCPU_RW_OPS(8)
PERCPU_RW_OPS(16)
PERCPU_RW_OPS(32)
PERCPU_RW_OPS(64)
PERCPU_OP(add, add, stadd)
PERCPU_OP(andnot, bic, stclr)
PERCPU_OP(or, orr, stset)
PERCPU_RET_OP(add, add, ldadd)

#अघोषित PERCPU_RW_OPS
#अघोषित __PERCPU_OP_CASE
#अघोषित __PERCPU_RET_OP_CASE
#अघोषित PERCPU_OP
#अघोषित PERCPU_RET_OP

/*
 * It would be nice to aव्योम the conditional call पूर्णांकo the scheduler when
 * re-enabling preemption क्रम preemptible kernels, but करोing that in a way
 * which builds inside a module would mean messing directly with the preempt
 * count. If you करो this, peterz and tglx will hunt you करोwn.
 */
#घोषणा this_cpu_cmpxchg_द्विगुन_8(ptr1, ptr2, o1, o2, n1, n2)		\
(अणु									\
	पूर्णांक __ret;							\
	preempt_disable_notrace();					\
	__ret = cmpxchg_द्विगुन_local(	raw_cpu_ptr(&(ptr1)),		\
					raw_cpu_ptr(&(ptr2)),		\
					o1, o2, n1, n2);		\
	preempt_enable_notrace();					\
	__ret;								\
पूर्ण)

#घोषणा _pcp_protect(op, pcp, ...)					\
(अणु									\
	preempt_disable_notrace();					\
	op(raw_cpu_ptr(&(pcp)), __VA_ARGS__);				\
	preempt_enable_notrace();					\
पूर्ण)

#घोषणा _pcp_protect_वापस(op, pcp, args...)				\
(अणु									\
	typeof(pcp) __retval;						\
	preempt_disable_notrace();					\
	__retval = (typeof(pcp))op(raw_cpu_ptr(&(pcp)), ##args);	\
	preempt_enable_notrace();					\
	__retval;							\
पूर्ण)

#घोषणा this_cpu_पढ़ो_1(pcp)		\
	_pcp_protect_वापस(__percpu_पढ़ो_8, pcp)
#घोषणा this_cpu_पढ़ो_2(pcp)		\
	_pcp_protect_वापस(__percpu_पढ़ो_16, pcp)
#घोषणा this_cpu_पढ़ो_4(pcp)		\
	_pcp_protect_वापस(__percpu_पढ़ो_32, pcp)
#घोषणा this_cpu_पढ़ो_8(pcp)		\
	_pcp_protect_वापस(__percpu_पढ़ो_64, pcp)

#घोषणा this_cpu_ग_लिखो_1(pcp, val)	\
	_pcp_protect(__percpu_ग_लिखो_8, pcp, (अचिन्हित दीर्घ)val)
#घोषणा this_cpu_ग_लिखो_2(pcp, val)	\
	_pcp_protect(__percpu_ग_लिखो_16, pcp, (अचिन्हित दीर्घ)val)
#घोषणा this_cpu_ग_लिखो_4(pcp, val)	\
	_pcp_protect(__percpu_ग_लिखो_32, pcp, (अचिन्हित दीर्घ)val)
#घोषणा this_cpu_ग_लिखो_8(pcp, val)	\
	_pcp_protect(__percpu_ग_लिखो_64, pcp, (अचिन्हित दीर्घ)val)

#घोषणा this_cpu_add_1(pcp, val)	\
	_pcp_protect(__percpu_add_हाल_8, pcp, val)
#घोषणा this_cpu_add_2(pcp, val)	\
	_pcp_protect(__percpu_add_हाल_16, pcp, val)
#घोषणा this_cpu_add_4(pcp, val)	\
	_pcp_protect(__percpu_add_हाल_32, pcp, val)
#घोषणा this_cpu_add_8(pcp, val)	\
	_pcp_protect(__percpu_add_हाल_64, pcp, val)

#घोषणा this_cpu_add_वापस_1(pcp, val)	\
	_pcp_protect_वापस(__percpu_add_वापस_हाल_8, pcp, val)
#घोषणा this_cpu_add_वापस_2(pcp, val)	\
	_pcp_protect_वापस(__percpu_add_वापस_हाल_16, pcp, val)
#घोषणा this_cpu_add_वापस_4(pcp, val)	\
	_pcp_protect_वापस(__percpu_add_वापस_हाल_32, pcp, val)
#घोषणा this_cpu_add_वापस_8(pcp, val)	\
	_pcp_protect_वापस(__percpu_add_वापस_हाल_64, pcp, val)

#घोषणा this_cpu_and_1(pcp, val)	\
	_pcp_protect(__percpu_andnot_हाल_8, pcp, ~val)
#घोषणा this_cpu_and_2(pcp, val)	\
	_pcp_protect(__percpu_andnot_हाल_16, pcp, ~val)
#घोषणा this_cpu_and_4(pcp, val)	\
	_pcp_protect(__percpu_andnot_हाल_32, pcp, ~val)
#घोषणा this_cpu_and_8(pcp, val)	\
	_pcp_protect(__percpu_andnot_हाल_64, pcp, ~val)

#घोषणा this_cpu_or_1(pcp, val)		\
	_pcp_protect(__percpu_or_हाल_8, pcp, val)
#घोषणा this_cpu_or_2(pcp, val)		\
	_pcp_protect(__percpu_or_हाल_16, pcp, val)
#घोषणा this_cpu_or_4(pcp, val)		\
	_pcp_protect(__percpu_or_हाल_32, pcp, val)
#घोषणा this_cpu_or_8(pcp, val)		\
	_pcp_protect(__percpu_or_हाल_64, pcp, val)

#घोषणा this_cpu_xchg_1(pcp, val)	\
	_pcp_protect_वापस(xchg_relaxed, pcp, val)
#घोषणा this_cpu_xchg_2(pcp, val)	\
	_pcp_protect_वापस(xchg_relaxed, pcp, val)
#घोषणा this_cpu_xchg_4(pcp, val)	\
	_pcp_protect_वापस(xchg_relaxed, pcp, val)
#घोषणा this_cpu_xchg_8(pcp, val)	\
	_pcp_protect_वापस(xchg_relaxed, pcp, val)

#घोषणा this_cpu_cmpxchg_1(pcp, o, n)	\
	_pcp_protect_वापस(cmpxchg_relaxed, pcp, o, n)
#घोषणा this_cpu_cmpxchg_2(pcp, o, n)	\
	_pcp_protect_वापस(cmpxchg_relaxed, pcp, o, n)
#घोषणा this_cpu_cmpxchg_4(pcp, o, n)	\
	_pcp_protect_वापस(cmpxchg_relaxed, pcp, o, n)
#घोषणा this_cpu_cmpxchg_8(pcp, o, n)	\
	_pcp_protect_वापस(cmpxchg_relaxed, pcp, o, n)

#अगर_घोषित __KVM_NVHE_HYPERVISOR__
बाह्य अचिन्हित दीर्घ __hyp_per_cpu_offset(अचिन्हित पूर्णांक cpu);
#घोषणा __per_cpu_offset
#घोषणा per_cpu_offset(cpu)	__hyp_per_cpu_offset((cpu))
#पूर्ण_अगर

#समावेश <यंत्र-generic/percpu.h>

/* Redefine macros क्रम nVHE hyp under DEBUG_PREEMPT to aव्योम its dependencies. */
#अगर defined(__KVM_NVHE_HYPERVISOR__) && defined(CONFIG_DEBUG_PREEMPT)
#अघोषित	this_cpu_ptr
#घोषणा	this_cpu_ptr		raw_cpu_ptr
#अघोषित	__this_cpu_पढ़ो
#घोषणा	__this_cpu_पढ़ो		raw_cpu_पढ़ो
#अघोषित	__this_cpu_ग_लिखो
#घोषणा	__this_cpu_ग_लिखो	raw_cpu_ग_लिखो
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_PERCPU_H */

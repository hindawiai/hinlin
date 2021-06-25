<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_BARRIER_H
#घोषणा __ASM_BARRIER_H

#समावेश <यंत्र/alternative.h>

#अगर_अघोषित __ASSEMBLY__

/* The synchronize caches inकाष्ठाion executes as a nop on प्रणालीs in
   which all memory references are perक्रमmed in order. */
#घोषणा synchronize_caches() यंत्र अस्थिर("sync" \
	ALTERNATIVE(ALT_COND_NO_SMP, INSN_NOP) \
	: : : "memory")

#अगर defined(CONFIG_SMP)
#घोषणा mb()		करो अणु synchronize_caches(); पूर्ण जबतक (0)
#घोषणा rmb()		mb()
#घोषणा wmb()		mb()
#घोषणा dma_rmb()	mb()
#घोषणा dma_wmb()	mb()
#अन्यथा
#घोषणा mb()		barrier()
#घोषणा rmb()		barrier()
#घोषणा wmb()		barrier()
#घोषणा dma_rmb()	barrier()
#घोषणा dma_wmb()	barrier()
#पूर्ण_अगर

#घोषणा __smp_mb()	mb()
#घोषणा __smp_rmb()	mb()
#घोषणा __smp_wmb()	mb()

#घोषणा __smp_store_release(p, v)					\
करो अणु									\
	typeof(p) __p = (p);						\
        जोड़ अणु typeof(*p) __val; अक्षर __c[1]; पूर्ण __u =			\
                अणु .__val = (__क्रमce typeof(*p)) (v) पूर्ण;			\
	compileसमय_निश्चित_atomic_type(*p);				\
	चयन (माप(*p)) अणु						\
	हाल 1:								\
		यंत्र अस्थिर("stb,ma %0,0(%1)"				\
				: : "r"(*(__u8 *)__u.__c), "r"(__p)	\
				: "memory");				\
		अवरोध;							\
	हाल 2:								\
		यंत्र अस्थिर("sth,ma %0,0(%1)"				\
				: : "r"(*(__u16 *)__u.__c), "r"(__p)	\
				: "memory");				\
		अवरोध;							\
	हाल 4:								\
		यंत्र अस्थिर("stw,ma %0,0(%1)"				\
				: : "r"(*(__u32 *)__u.__c), "r"(__p)	\
				: "memory");				\
		अवरोध;							\
	हाल 8:								\
		अगर (IS_ENABLED(CONFIG_64BIT))				\
			यंत्र अस्थिर("std,ma %0,0(%1)"			\
				: : "r"(*(__u64 *)__u.__c), "r"(__p)	\
				: "memory");				\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __smp_load_acquire(p)						\
(अणु									\
	जोड़ अणु typeof(*p) __val; अक्षर __c[1]; पूर्ण __u;			\
	typeof(p) __p = (p);						\
	compileसमय_निश्चित_atomic_type(*p);				\
	चयन (माप(*p)) अणु						\
	हाल 1:								\
		यंत्र अस्थिर("ldb,ma 0(%1),%0"				\
				: "=r"(*(__u8 *)__u.__c) : "r"(__p)	\
				: "memory");				\
		अवरोध;							\
	हाल 2:								\
		यंत्र अस्थिर("ldh,ma 0(%1),%0"				\
				: "=r"(*(__u16 *)__u.__c) : "r"(__p)	\
				: "memory");				\
		अवरोध;							\
	हाल 4:								\
		यंत्र अस्थिर("ldw,ma 0(%1),%0"				\
				: "=r"(*(__u32 *)__u.__c) : "r"(__p)	\
				: "memory");				\
		अवरोध;							\
	हाल 8:								\
		अगर (IS_ENABLED(CONFIG_64BIT))				\
			यंत्र अस्थिर("ldd,ma 0(%1),%0"			\
				: "=r"(*(__u64 *)__u.__c) : "r"(__p)	\
				: "memory");				\
		अवरोध;							\
	पूर्ण								\
	__u.__val;							\
पूर्ण)
#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_BARRIER_H */

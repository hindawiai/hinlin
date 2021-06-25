<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/barrier.h
 *
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_BARRIER_H
#घोषणा __ASM_BARRIER_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/kasan-checks.h>

#घोषणा __nops(n)	".rept	" #n "\nnop\n.endr\n"
#घोषणा nops(n)		यंत्र अस्थिर(__nops(n))

#घोषणा sev()		यंत्र अस्थिर("sev" : : : "memory")
#घोषणा wfe()		यंत्र अस्थिर("wfe" : : : "memory")
#घोषणा wfi()		यंत्र अस्थिर("wfi" : : : "memory")

#घोषणा isb()		यंत्र अस्थिर("isb" : : : "memory")
#घोषणा dmb(opt)	यंत्र अस्थिर("dmb " #opt : : : "memory")
#घोषणा dsb(opt)	यंत्र अस्थिर("dsb " #opt : : : "memory")

#घोषणा psb_csync()	यंत्र अस्थिर("hint #17" : : : "memory")
#घोषणा tsb_csync()	यंत्र अस्थिर("hint #18" : : : "memory")
#घोषणा csdb()		यंत्र अस्थिर("hint #20" : : : "memory")

#अगर_घोषित CONFIG_ARM64_PSEUDO_NMI
#घोषणा pmr_sync()						\
	करो अणु							\
		बाह्य काष्ठा अटल_key_false gic_pmr_sync;	\
								\
		अगर (अटल_branch_unlikely(&gic_pmr_sync))	\
			dsb(sy);				\
	पूर्ण जबतक(0)
#अन्यथा
#घोषणा pmr_sync()	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा mb()		dsb(sy)
#घोषणा rmb()		dsb(ld)
#घोषणा wmb()		dsb(st)

#घोषणा dma_mb()	dmb(osh)
#घोषणा dma_rmb()	dmb(oshld)
#घोषणा dma_wmb()	dmb(oshst)

/*
 * Generate a mask क्रम array_index__nospec() that is ~0UL when 0 <= idx < sz
 * and 0 otherwise.
 */
#घोषणा array_index_mask_nospec array_index_mask_nospec
अटल अंतरभूत अचिन्हित दीर्घ array_index_mask_nospec(अचिन्हित दीर्घ idx,
						    अचिन्हित दीर्घ sz)
अणु
	अचिन्हित दीर्घ mask;

	यंत्र अस्थिर(
	"	cmp	%1, %2\n"
	"	sbc	%0, xzr, xzr\n"
	: "=r" (mask)
	: "r" (idx), "Ir" (sz)
	: "cc");

	csdb();
	वापस mask;
पूर्ण

/*
 * Ensure that पढ़ोs of the counter are treated the same as memory पढ़ोs
 * क्रम the purposes of ordering by subsequent memory barriers.
 *
 * This insanity brought to you by speculative प्रणाली रेजिस्टर पढ़ोs,
 * out-of-order memory accesses, sequence locks and Thomas Gleixner.
 *
 * https://lore.kernel.org/r/alpine.DEB.2.21.1902081950260.1662@nanos.tec.linutronix.de/
 */
#घोषणा arch_counter_enक्रमce_ordering(val) करो अणु				\
	u64 पंचांगp, _val = (val);						\
									\
	यंत्र अस्थिर(							\
	"	eor	%0, %1, %1\n"					\
	"	add	%0, sp, %0\n"					\
	"	ldr	xzr, [%0]"					\
	: "=r" (पंचांगp) : "r" (_val));					\
पूर्ण जबतक (0)

#घोषणा __smp_mb()	dmb(ish)
#घोषणा __smp_rmb()	dmb(ishld)
#घोषणा __smp_wmb()	dmb(ishst)

#घोषणा __smp_store_release(p, v)					\
करो अणु									\
	typeof(p) __p = (p);						\
	जोड़ अणु __unqual_scalar_typeof(*p) __val; अक्षर __c[1]; पूर्ण __u =	\
		अणु .__val = (__क्रमce __unqual_scalar_typeof(*p)) (v) पूर्ण;	\
	compileसमय_निश्चित_atomic_type(*p);				\
	kasan_check_ग_लिखो(__p, माप(*p));				\
	चयन (माप(*p)) अणु						\
	हाल 1:								\
		यंत्र अस्थिर ("stlrb %w1, %0"				\
				: "=Q" (*__p)				\
				: "r" (*(__u8 *)__u.__c)		\
				: "memory");				\
		अवरोध;							\
	हाल 2:								\
		यंत्र अस्थिर ("stlrh %w1, %0"				\
				: "=Q" (*__p)				\
				: "r" (*(__u16 *)__u.__c)		\
				: "memory");				\
		अवरोध;							\
	हाल 4:								\
		यंत्र अस्थिर ("stlr %w1, %0"				\
				: "=Q" (*__p)				\
				: "r" (*(__u32 *)__u.__c)		\
				: "memory");				\
		अवरोध;							\
	हाल 8:								\
		यंत्र अस्थिर ("stlr %1, %0"				\
				: "=Q" (*__p)				\
				: "r" (*(__u64 *)__u.__c)		\
				: "memory");				\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __smp_load_acquire(p)						\
(अणु									\
	जोड़ अणु __unqual_scalar_typeof(*p) __val; अक्षर __c[1]; पूर्ण __u;	\
	typeof(p) __p = (p);						\
	compileसमय_निश्चित_atomic_type(*p);				\
	kasan_check_पढ़ो(__p, माप(*p));				\
	चयन (माप(*p)) अणु						\
	हाल 1:								\
		यंत्र अस्थिर ("ldarb %w0, %1"				\
			: "=r" (*(__u8 *)__u.__c)			\
			: "Q" (*__p) : "memory");			\
		अवरोध;							\
	हाल 2:								\
		यंत्र अस्थिर ("ldarh %w0, %1"				\
			: "=r" (*(__u16 *)__u.__c)			\
			: "Q" (*__p) : "memory");			\
		अवरोध;							\
	हाल 4:								\
		यंत्र अस्थिर ("ldar %w0, %1"				\
			: "=r" (*(__u32 *)__u.__c)			\
			: "Q" (*__p) : "memory");			\
		अवरोध;							\
	हाल 8:								\
		यंत्र अस्थिर ("ldar %0, %1"				\
			: "=r" (*(__u64 *)__u.__c)			\
			: "Q" (*__p) : "memory");			\
		अवरोध;							\
	पूर्ण								\
	(typeof(*p))__u.__val;						\
पूर्ण)

#घोषणा smp_cond_load_relaxed(ptr, cond_expr)				\
(अणु									\
	typeof(ptr) __PTR = (ptr);					\
	__unqual_scalar_typeof(*ptr) VAL;				\
	क्रम (;;) अणु							\
		VAL = READ_ONCE(*__PTR);				\
		अगर (cond_expr)						\
			अवरोध;						\
		__cmpरुको_relaxed(__PTR, VAL);				\
	पूर्ण								\
	(typeof(*ptr))VAL;						\
पूर्ण)

#घोषणा smp_cond_load_acquire(ptr, cond_expr)				\
(अणु									\
	typeof(ptr) __PTR = (ptr);					\
	__unqual_scalar_typeof(*ptr) VAL;				\
	क्रम (;;) अणु							\
		VAL = smp_load_acquire(__PTR);				\
		अगर (cond_expr)						\
			अवरोध;						\
		__cmpरुको_relaxed(__PTR, VAL);				\
	पूर्ण								\
	(typeof(*ptr))VAL;						\
पूर्ण)

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* __ASM_BARRIER_H */

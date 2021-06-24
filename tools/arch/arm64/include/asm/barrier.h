<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_ASM_AARCH64_BARRIER_H
#घोषणा _TOOLS_LINUX_ASM_AARCH64_BARRIER_H

/*
 * From tools/perf/perf-sys.h, last modअगरied in:
 * f428ebd184c82a7914b2aa7e9f868918aaf7ea78 perf tools: Fix AAAAARGH64 memory barriers
 *
 * XXX: arch/arm64/include/यंत्र/barrier.h in the kernel sources use dsb, is this
 * a हाल like क्रम arm32 where we करो things dअगरferently in userspace?
 */

#घोषणा mb()		यंत्र अस्थिर("dmb ish" ::: "memory")
#घोषणा wmb()		यंत्र अस्थिर("dmb ishst" ::: "memory")
#घोषणा rmb()		यंत्र अस्थिर("dmb ishld" ::: "memory")

/*
 * Kernel uses dmb variants on arm64 क्रम smp_*() barriers. Pretty much the same
 * implementation as above mb()/wmb()/rmb(), though क्रम the latter kernel uses
 * dsb. In any हाल, should above mb()/wmb()/rmb() change, make sure the below
 * smp_*() करोn't.
 */
#घोषणा smp_mb()	यंत्र अस्थिर("dmb ish" ::: "memory")
#घोषणा smp_wmb()	यंत्र अस्थिर("dmb ishst" ::: "memory")
#घोषणा smp_rmb()	यंत्र अस्थिर("dmb ishld" ::: "memory")

#घोषणा smp_store_release(p, v)						\
करो अणु									\
	जोड़ अणु typeof(*p) __val; अक्षर __c[1]; पूर्ण __u =			\
		अणु .__val = (v) पूर्ण; 					\
									\
	चयन (माप(*p)) अणु						\
	हाल 1:								\
		यंत्र अस्थिर ("stlrb %w1, %0"				\
				: "=Q" (*p)				\
				: "r" (*(__u8_alias_t *)__u.__c)	\
				: "memory");				\
		अवरोध;							\
	हाल 2:								\
		यंत्र अस्थिर ("stlrh %w1, %0"				\
				: "=Q" (*p)				\
				: "r" (*(__u16_alias_t *)__u.__c)	\
				: "memory");				\
		अवरोध;							\
	हाल 4:								\
		यंत्र अस्थिर ("stlr %w1, %0"				\
				: "=Q" (*p)				\
				: "r" (*(__u32_alias_t *)__u.__c)	\
				: "memory");				\
		अवरोध;							\
	हाल 8:								\
		यंत्र अस्थिर ("stlr %1, %0"				\
				: "=Q" (*p)				\
				: "r" (*(__u64_alias_t *)__u.__c)	\
				: "memory");				\
		अवरोध;							\
	शेष:							\
		/* Only to shut up gcc ... */				\
		mb();							\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा smp_load_acquire(p)						\
(अणु									\
	जोड़ अणु typeof(*p) __val; अक्षर __c[1]; पूर्ण __u =			\
		अणु .__c = अणु 0 पूर्ण पूर्ण;					\
									\
	चयन (माप(*p)) अणु						\
	हाल 1:								\
		यंत्र अस्थिर ("ldarb %w0, %1"				\
			: "=r" (*(__u8_alias_t *)__u.__c)		\
			: "Q" (*p) : "memory");				\
		अवरोध;							\
	हाल 2:								\
		यंत्र अस्थिर ("ldarh %w0, %1"				\
			: "=r" (*(__u16_alias_t *)__u.__c)		\
			: "Q" (*p) : "memory");				\
		अवरोध;							\
	हाल 4:								\
		यंत्र अस्थिर ("ldar %w0, %1"				\
			: "=r" (*(__u32_alias_t *)__u.__c)		\
			: "Q" (*p) : "memory");				\
		अवरोध;							\
	हाल 8:								\
		यंत्र अस्थिर ("ldar %0, %1"				\
			: "=r" (*(__u64_alias_t *)__u.__c)		\
			: "Q" (*p) : "memory");				\
		अवरोध;							\
	शेष:							\
		/* Only to shut up gcc ... */				\
		mb();							\
		अवरोध;							\
	पूर्ण								\
	__u.__val;							\
पूर्ण)

#पूर्ण_अगर /* _TOOLS_LINUX_ASM_AARCH64_BARRIER_H */

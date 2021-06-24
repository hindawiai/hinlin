<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_ATOMIC64_32_H
#घोषणा _ASM_X86_ATOMIC64_32_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
//#समावेश <यंत्र/cmpxchg.h>

/* An 64bit atomic type */

प्रकार काष्ठा अणु
	s64 __aligned(8) counter;
पूर्ण atomic64_t;

#घोषणा ATOMIC64_INIT(val)	अणु (val) पूर्ण

#घोषणा __ATOMIC64_DECL(sym) व्योम atomic64_##sym(atomic64_t *, ...)
#अगर_अघोषित ATOMIC64_EXPORT
#घोषणा ATOMIC64_DECL_ONE __ATOMIC64_DECL
#अन्यथा
#घोषणा ATOMIC64_DECL_ONE(sym) __ATOMIC64_DECL(sym); \
	ATOMIC64_EXPORT(atomic64_##sym)
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_CMPXCHG64
#घोषणा __alternative_atomic64(f, g, out, in...) \
	यंत्र अस्थिर("call %P[func]" \
		     : out : [func] "i" (atomic64_##g##_cx8), ## in)

#घोषणा ATOMIC64_DECL(sym) ATOMIC64_DECL_ONE(sym##_cx8)
#अन्यथा
#घोषणा __alternative_atomic64(f, g, out, in...) \
	alternative_call(atomic64_##f##_386, atomic64_##g##_cx8, \
			 X86_FEATURE_CX8, ASM_OUTPUT2(out), ## in)

#घोषणा ATOMIC64_DECL(sym) ATOMIC64_DECL_ONE(sym##_cx8); \
	ATOMIC64_DECL_ONE(sym##_386)

ATOMIC64_DECL_ONE(add_386);
ATOMIC64_DECL_ONE(sub_386);
ATOMIC64_DECL_ONE(inc_386);
ATOMIC64_DECL_ONE(dec_386);
#पूर्ण_अगर

#घोषणा alternative_atomic64(f, out, in...) \
	__alternative_atomic64(f, f, ASM_OUTPUT2(out), ## in)

ATOMIC64_DECL(पढ़ो);
ATOMIC64_DECL(set);
ATOMIC64_DECL(xchg);
ATOMIC64_DECL(add_वापस);
ATOMIC64_DECL(sub_वापस);
ATOMIC64_DECL(inc_वापस);
ATOMIC64_DECL(dec_वापस);
ATOMIC64_DECL(dec_अगर_positive);
ATOMIC64_DECL(inc_not_zero);
ATOMIC64_DECL(add_unless);

#अघोषित ATOMIC64_DECL
#अघोषित ATOMIC64_DECL_ONE
#अघोषित __ATOMIC64_DECL
#अघोषित ATOMIC64_EXPORT

/**
 * arch_atomic64_cmpxchg - cmpxchg atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 * @o: expected value
 * @n: new value
 *
 * Atomically sets @v to @n अगर it was equal to @o and वापसs
 * the old value.
 */

अटल अंतरभूत s64 arch_atomic64_cmpxchg(atomic64_t *v, s64 o, s64 n)
अणु
	वापस arch_cmpxchg64(&v->counter, o, n);
पूर्ण
#घोषणा arch_atomic64_cmpxchg arch_atomic64_cmpxchg

/**
 * arch_atomic64_xchg - xchg atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 * @n: value to assign
 *
 * Atomically xchgs the value of @v to @n and वापसs
 * the old value.
 */
अटल अंतरभूत s64 arch_atomic64_xchg(atomic64_t *v, s64 n)
अणु
	s64 o;
	अचिन्हित high = (अचिन्हित)(n >> 32);
	अचिन्हित low = (अचिन्हित)n;
	alternative_atomic64(xchg, "=&A" (o),
			     "S" (v), "b" (low), "c" (high)
			     : "memory");
	वापस o;
पूर्ण
#घोषणा arch_atomic64_xchg arch_atomic64_xchg

/**
 * arch_atomic64_set - set atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 * @i: value to assign
 *
 * Atomically sets the value of @v to @n.
 */
अटल अंतरभूत व्योम arch_atomic64_set(atomic64_t *v, s64 i)
अणु
	अचिन्हित high = (अचिन्हित)(i >> 32);
	अचिन्हित low = (अचिन्हित)i;
	alternative_atomic64(set, /* no output */,
			     "S" (v), "b" (low), "c" (high)
			     : "eax", "edx", "memory");
पूर्ण

/**
 * arch_atomic64_पढ़ो - पढ़ो atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically पढ़ोs the value of @v and वापसs it.
 */
अटल अंतरभूत s64 arch_atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	s64 r;
	alternative_atomic64(पढ़ो, "=&A" (r), "c" (v) : "memory");
	वापस r;
पूर्ण

/**
 * arch_atomic64_add_वापस - add and वापस
 * @i: पूर्णांकeger value to add
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically adds @i to @v and वापसs @i + *@v
 */
अटल अंतरभूत s64 arch_atomic64_add_वापस(s64 i, atomic64_t *v)
अणु
	alternative_atomic64(add_वापस,
			     ASM_OUTPUT2("+A" (i), "+c" (v)),
			     ASM_NO_INPUT_CLOBBER("memory"));
	वापस i;
पूर्ण
#घोषणा arch_atomic64_add_वापस arch_atomic64_add_वापस

/*
 * Other variants with dअगरferent arithmetic चालकs:
 */
अटल अंतरभूत s64 arch_atomic64_sub_वापस(s64 i, atomic64_t *v)
अणु
	alternative_atomic64(sub_वापस,
			     ASM_OUTPUT2("+A" (i), "+c" (v)),
			     ASM_NO_INPUT_CLOBBER("memory"));
	वापस i;
पूर्ण
#घोषणा arch_atomic64_sub_वापस arch_atomic64_sub_वापस

अटल अंतरभूत s64 arch_atomic64_inc_वापस(atomic64_t *v)
अणु
	s64 a;
	alternative_atomic64(inc_वापस, "=&A" (a),
			     "S" (v) : "memory", "ecx");
	वापस a;
पूर्ण
#घोषणा arch_atomic64_inc_वापस arch_atomic64_inc_वापस

अटल अंतरभूत s64 arch_atomic64_dec_वापस(atomic64_t *v)
अणु
	s64 a;
	alternative_atomic64(dec_वापस, "=&A" (a),
			     "S" (v) : "memory", "ecx");
	वापस a;
पूर्ण
#घोषणा arch_atomic64_dec_वापस arch_atomic64_dec_वापस

/**
 * arch_atomic64_add - add पूर्णांकeger to atomic64 variable
 * @i: पूर्णांकeger value to add
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically adds @i to @v.
 */
अटल अंतरभूत s64 arch_atomic64_add(s64 i, atomic64_t *v)
अणु
	__alternative_atomic64(add, add_वापस,
			       ASM_OUTPUT2("+A" (i), "+c" (v)),
			       ASM_NO_INPUT_CLOBBER("memory"));
	वापस i;
पूर्ण

/**
 * arch_atomic64_sub - subtract the atomic64 variable
 * @i: पूर्णांकeger value to subtract
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically subtracts @i from @v.
 */
अटल अंतरभूत s64 arch_atomic64_sub(s64 i, atomic64_t *v)
अणु
	__alternative_atomic64(sub, sub_वापस,
			       ASM_OUTPUT2("+A" (i), "+c" (v)),
			       ASM_NO_INPUT_CLOBBER("memory"));
	वापस i;
पूर्ण

/**
 * arch_atomic64_inc - increment atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically increments @v by 1.
 */
अटल अंतरभूत व्योम arch_atomic64_inc(atomic64_t *v)
अणु
	__alternative_atomic64(inc, inc_वापस, /* no output */,
			       "S" (v) : "memory", "eax", "ecx", "edx");
पूर्ण
#घोषणा arch_atomic64_inc arch_atomic64_inc

/**
 * arch_atomic64_dec - decrement atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically decrements @v by 1.
 */
अटल अंतरभूत व्योम arch_atomic64_dec(atomic64_t *v)
अणु
	__alternative_atomic64(dec, dec_वापस, /* no output */,
			       "S" (v) : "memory", "eax", "ecx", "edx");
पूर्ण
#घोषणा arch_atomic64_dec arch_atomic64_dec

/**
 * arch_atomic64_add_unless - add unless the number is a given value
 * @v: poपूर्णांकer of type atomic64_t
 * @a: the amount to add to v...
 * @u: ...unless v is equal to u.
 *
 * Atomically adds @a to @v, so दीर्घ as it was not @u.
 * Returns non-zero अगर the add was करोne, zero otherwise.
 */
अटल अंतरभूत पूर्णांक arch_atomic64_add_unless(atomic64_t *v, s64 a, s64 u)
अणु
	अचिन्हित low = (अचिन्हित)u;
	अचिन्हित high = (अचिन्हित)(u >> 32);
	alternative_atomic64(add_unless,
			     ASM_OUTPUT2("+A" (a), "+c" (low), "+D" (high)),
			     "S" (v) : "memory");
	वापस (पूर्णांक)a;
पूर्ण
#घोषणा arch_atomic64_add_unless arch_atomic64_add_unless

अटल अंतरभूत पूर्णांक arch_atomic64_inc_not_zero(atomic64_t *v)
अणु
	पूर्णांक r;
	alternative_atomic64(inc_not_zero, "=&a" (r),
			     "S" (v) : "ecx", "edx", "memory");
	वापस r;
पूर्ण
#घोषणा arch_atomic64_inc_not_zero arch_atomic64_inc_not_zero

अटल अंतरभूत s64 arch_atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	s64 r;
	alternative_atomic64(dec_अगर_positive, "=&A" (r),
			     "S" (v) : "ecx", "memory");
	वापस r;
पूर्ण
#घोषणा arch_atomic64_dec_अगर_positive arch_atomic64_dec_अगर_positive

#अघोषित alternative_atomic64
#अघोषित __alternative_atomic64

अटल अंतरभूत व्योम arch_atomic64_and(s64 i, atomic64_t *v)
अणु
	s64 old, c = 0;

	जबतक ((old = arch_atomic64_cmpxchg(v, c, c & i)) != c)
		c = old;
पूर्ण

अटल अंतरभूत s64 arch_atomic64_fetch_and(s64 i, atomic64_t *v)
अणु
	s64 old, c = 0;

	जबतक ((old = arch_atomic64_cmpxchg(v, c, c & i)) != c)
		c = old;

	वापस old;
पूर्ण
#घोषणा arch_atomic64_fetch_and arch_atomic64_fetch_and

अटल अंतरभूत व्योम arch_atomic64_or(s64 i, atomic64_t *v)
अणु
	s64 old, c = 0;

	जबतक ((old = arch_atomic64_cmpxchg(v, c, c | i)) != c)
		c = old;
पूर्ण

अटल अंतरभूत s64 arch_atomic64_fetch_or(s64 i, atomic64_t *v)
अणु
	s64 old, c = 0;

	जबतक ((old = arch_atomic64_cmpxchg(v, c, c | i)) != c)
		c = old;

	वापस old;
पूर्ण
#घोषणा arch_atomic64_fetch_or arch_atomic64_fetch_or

अटल अंतरभूत व्योम arch_atomic64_xor(s64 i, atomic64_t *v)
अणु
	s64 old, c = 0;

	जबतक ((old = arch_atomic64_cmpxchg(v, c, c ^ i)) != c)
		c = old;
पूर्ण

अटल अंतरभूत s64 arch_atomic64_fetch_xor(s64 i, atomic64_t *v)
अणु
	s64 old, c = 0;

	जबतक ((old = arch_atomic64_cmpxchg(v, c, c ^ i)) != c)
		c = old;

	वापस old;
पूर्ण
#घोषणा arch_atomic64_fetch_xor arch_atomic64_fetch_xor

अटल अंतरभूत s64 arch_atomic64_fetch_add(s64 i, atomic64_t *v)
अणु
	s64 old, c = 0;

	जबतक ((old = arch_atomic64_cmpxchg(v, c, c + i)) != c)
		c = old;

	वापस old;
पूर्ण
#घोषणा arch_atomic64_fetch_add arch_atomic64_fetch_add

#घोषणा arch_atomic64_fetch_sub(i, v)	arch_atomic64_fetch_add(-(i), (v))

#पूर्ण_अगर /* _ASM_X86_ATOMIC64_32_H */

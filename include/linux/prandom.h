<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/pअक्रमom.h
 *
 * Include file क्रम the fast pseuकरो-अक्रमom 32-bit
 * generation.
 */
#अगर_अघोषित _LINUX_PRANDOM_H
#घोषणा _LINUX_PRANDOM_H

#समावेश <linux/types.h>
#समावेश <linux/percpu.h>

u32 pअक्रमom_u32(व्योम);
व्योम pअक्रमom_bytes(व्योम *buf, माप_प्रकार nbytes);
व्योम pअक्रमom_seed(u32 seed);
व्योम pअक्रमom_reseed_late(व्योम);

DECLARE_PER_CPU(अचिन्हित दीर्घ, net_अक्रम_noise);

#घोषणा PRANDOM_ADD_NOISE(a, b, c, d) \
	pअक्रमom_u32_add_noise((अचिन्हित दीर्घ)(a), (अचिन्हित दीर्घ)(b), \
			      (अचिन्हित दीर्घ)(c), (अचिन्हित दीर्घ)(d))

#अगर BITS_PER_LONG == 64
/*
 * The core SipHash round function.  Each line can be executed in
 * parallel given enough CPU resources.
 */
#घोषणा PRND_SIPROUND(v0, v1, v2, v3) ( \
	v0 += v1, v1 = rol64(v1, 13),  v2 += v3, v3 = rol64(v3, 16), \
	v1 ^= v0, v0 = rol64(v0, 32),  v3 ^= v2,                     \
	v0 += v3, v3 = rol64(v3, 21),  v2 += v1, v1 = rol64(v1, 17), \
	v3 ^= v0,                      v1 ^= v2, v2 = rol64(v2, 32)  \
)

#घोषणा PRND_K0 (0x736f6d6570736575 ^ 0x6c7967656e657261)
#घोषणा PRND_K1 (0x646f72616e646f6d ^ 0x7465646279746573)

#या_अगर BITS_PER_LONG == 32
/*
 * On 32-bit machines, we use HSipHash, a reduced-width version of SipHash.
 * This is weaker, but 32-bit machines are not used क्रम high-traffic
 * applications, so there is less output क्रम an attacker to analyze.
 */
#घोषणा PRND_SIPROUND(v0, v1, v2, v3) ( \
	v0 += v1, v1 = rol32(v1,  5),  v2 += v3, v3 = rol32(v3,  8), \
	v1 ^= v0, v0 = rol32(v0, 16),  v3 ^= v2,                     \
	v0 += v3, v3 = rol32(v3,  7),  v2 += v1, v1 = rol32(v1, 13), \
	v3 ^= v0,                      v1 ^= v2, v2 = rol32(v2, 16)  \
)
#घोषणा PRND_K0 0x6c796765
#घोषणा PRND_K1 0x74656462

#अन्यथा
#त्रुटि Unsupported BITS_PER_LONG
#पूर्ण_अगर

अटल अंतरभूत व्योम pअक्रमom_u32_add_noise(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b,
					 अचिन्हित दीर्घ c, अचिन्हित दीर्घ d)
अणु
	/*
	 * This is not used cryptographically; it's just
	 * a convenient 4-word hash function. (3 xor, 2 add, 2 rol)
	 */
	a ^= raw_cpu_पढ़ो(net_अक्रम_noise);
	PRND_SIPROUND(a, b, c, d);
	raw_cpu_ग_लिखो(net_अक्रम_noise, d);
पूर्ण

काष्ठा rnd_state अणु
	__u32 s1, s2, s3, s4;
पूर्ण;

u32 pअक्रमom_u32_state(काष्ठा rnd_state *state);
व्योम pअक्रमom_bytes_state(काष्ठा rnd_state *state, व्योम *buf, माप_प्रकार nbytes);
व्योम pअक्रमom_seed_full_state(काष्ठा rnd_state __percpu *pcpu_state);

#घोषणा pअक्रमom_init_once(pcpu_state)			\
	DO_ONCE(pअक्रमom_seed_full_state, (pcpu_state))

/**
 * pअक्रमom_u32_max - वापसs a pseuकरो-अक्रमom number in पूर्णांकerval [0, ep_ro)
 * @ep_ro: right खोलो पूर्णांकerval endpoपूर्णांक
 *
 * Returns a pseuकरो-अक्रमom number that is in पूर्णांकerval [0, ep_ro). Note
 * that the result depends on PRNG being well distributed in [0, ~0U]
 * u32 space. Here we use maximally equidistributed combined Tausworthe
 * generator, that is, pअक्रमom_u32(). This is useful when requesting a
 * अक्रमom index of an array containing ep_ro elements, क्रम example.
 *
 * Returns: pseuकरो-अक्रमom number in पूर्णांकerval [0, ep_ro)
 */
अटल अंतरभूत u32 pअक्रमom_u32_max(u32 ep_ro)
अणु
	वापस (u32)(((u64) pअक्रमom_u32() * ep_ro) >> 32);
पूर्ण

/*
 * Handle minimum values क्रम seeds
 */
अटल अंतरभूत u32 __seed(u32 x, u32 m)
अणु
	वापस (x < m) ? x + m : x;
पूर्ण

/**
 * pअक्रमom_seed_state - set seed क्रम pअक्रमom_u32_state().
 * @state: poपूर्णांकer to state काष्ठाure to receive the seed.
 * @seed: arbitrary 64-bit value to use as a seed.
 */
अटल अंतरभूत व्योम pअक्रमom_seed_state(काष्ठा rnd_state *state, u64 seed)
अणु
	u32 i = (seed >> 32) ^ (seed << 10) ^ seed;

	state->s1 = __seed(i,   2U);
	state->s2 = __seed(i,   8U);
	state->s3 = __seed(i,  16U);
	state->s4 = __seed(i, 128U);
	PRANDOM_ADD_NOISE(state, i, 0, 0);
पूर्ण

/* Pseuकरो अक्रमom number generator from numerical recipes. */
अटल अंतरभूत u32 next_pseuकरो_अक्रमom32(u32 seed)
अणु
	वापस seed * 1664525 + 1013904223;
पूर्ण

#पूर्ण_अगर

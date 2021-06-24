<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_घोषित __KERNEL__
# include <linux/crush/hash.h>
#अन्यथा
# include "hash.h"
#पूर्ण_अगर

/*
 * Robert Jenkins' function क्रम mixing 32-bit values
 * https://burtleburtle.net/bob/hash/evahash.hपंचांगl
 * a, b = अक्रमom bits, c = input and output
 */
#घोषणा crush_hashmix(a, b, c) करो अणु			\
		a = a-b;  a = a-c;  a = a^(c>>13);	\
		b = b-c;  b = b-a;  b = b^(a<<8);	\
		c = c-a;  c = c-b;  c = c^(b>>13);	\
		a = a-b;  a = a-c;  a = a^(c>>12);	\
		b = b-c;  b = b-a;  b = b^(a<<16);	\
		c = c-a;  c = c-b;  c = c^(b>>5);	\
		a = a-b;  a = a-c;  a = a^(c>>3);	\
		b = b-c;  b = b-a;  b = b^(a<<10);	\
		c = c-a;  c = c-b;  c = c^(b>>15);	\
	पूर्ण जबतक (0)

#घोषणा crush_hash_seed 1315423911

अटल __u32 crush_hash32_rjenkins1(__u32 a)
अणु
	__u32 hash = crush_hash_seed ^ a;
	__u32 b = a;
	__u32 x = 231232;
	__u32 y = 1232;
	crush_hashmix(b, x, hash);
	crush_hashmix(y, a, hash);
	वापस hash;
पूर्ण

अटल __u32 crush_hash32_rjenkins1_2(__u32 a, __u32 b)
अणु
	__u32 hash = crush_hash_seed ^ a ^ b;
	__u32 x = 231232;
	__u32 y = 1232;
	crush_hashmix(a, b, hash);
	crush_hashmix(x, a, hash);
	crush_hashmix(b, y, hash);
	वापस hash;
पूर्ण

अटल __u32 crush_hash32_rjenkins1_3(__u32 a, __u32 b, __u32 c)
अणु
	__u32 hash = crush_hash_seed ^ a ^ b ^ c;
	__u32 x = 231232;
	__u32 y = 1232;
	crush_hashmix(a, b, hash);
	crush_hashmix(c, x, hash);
	crush_hashmix(y, a, hash);
	crush_hashmix(b, x, hash);
	crush_hashmix(y, c, hash);
	वापस hash;
पूर्ण

अटल __u32 crush_hash32_rjenkins1_4(__u32 a, __u32 b, __u32 c, __u32 d)
अणु
	__u32 hash = crush_hash_seed ^ a ^ b ^ c ^ d;
	__u32 x = 231232;
	__u32 y = 1232;
	crush_hashmix(a, b, hash);
	crush_hashmix(c, d, hash);
	crush_hashmix(a, x, hash);
	crush_hashmix(y, b, hash);
	crush_hashmix(c, x, hash);
	crush_hashmix(y, d, hash);
	वापस hash;
पूर्ण

अटल __u32 crush_hash32_rjenkins1_5(__u32 a, __u32 b, __u32 c, __u32 d,
				      __u32 e)
अणु
	__u32 hash = crush_hash_seed ^ a ^ b ^ c ^ d ^ e;
	__u32 x = 231232;
	__u32 y = 1232;
	crush_hashmix(a, b, hash);
	crush_hashmix(c, d, hash);
	crush_hashmix(e, x, hash);
	crush_hashmix(y, a, hash);
	crush_hashmix(b, x, hash);
	crush_hashmix(y, c, hash);
	crush_hashmix(d, x, hash);
	crush_hashmix(y, e, hash);
	वापस hash;
पूर्ण


__u32 crush_hash32(पूर्णांक type, __u32 a)
अणु
	चयन (type) अणु
	हाल CRUSH_HASH_RJENKINS1:
		वापस crush_hash32_rjenkins1(a);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

__u32 crush_hash32_2(पूर्णांक type, __u32 a, __u32 b)
अणु
	चयन (type) अणु
	हाल CRUSH_HASH_RJENKINS1:
		वापस crush_hash32_rjenkins1_2(a, b);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

__u32 crush_hash32_3(पूर्णांक type, __u32 a, __u32 b, __u32 c)
अणु
	चयन (type) अणु
	हाल CRUSH_HASH_RJENKINS1:
		वापस crush_hash32_rjenkins1_3(a, b, c);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

__u32 crush_hash32_4(पूर्णांक type, __u32 a, __u32 b, __u32 c, __u32 d)
अणु
	चयन (type) अणु
	हाल CRUSH_HASH_RJENKINS1:
		वापस crush_hash32_rjenkins1_4(a, b, c, d);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

__u32 crush_hash32_5(पूर्णांक type, __u32 a, __u32 b, __u32 c, __u32 d, __u32 e)
अणु
	चयन (type) अणु
	हाल CRUSH_HASH_RJENKINS1:
		वापस crush_hash32_rjenkins1_5(a, b, c, d, e);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

स्थिर अक्षर *crush_hash_name(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल CRUSH_HASH_RJENKINS1:
		वापस "rjenkins1";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

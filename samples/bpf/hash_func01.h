<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1
 *
 * Based on Paul Hsieh's (LGPG 2.1) hash function
 * From: http://www.azillionmonkeys.com/qed/hash.hपंचांगl
 */

#घोषणा get16bits(d) (*((स्थिर __u16 *) (d)))

अटल __always_अंतरभूत
__u32 SuperFastHash (स्थिर अक्षर *data, पूर्णांक len, __u32 initval) अणु
	__u32 hash = initval;
	__u32 पंचांगp;
	पूर्णांक rem;

	अगर (len <= 0 || data == शून्य) वापस 0;

	rem = len & 3;
	len >>= 2;

	/* Main loop */
#आशय clang loop unroll(full)
	क्रम (;len > 0; len--) अणु
		hash  += get16bits (data);
		पंचांगp    = (get16bits (data+2) << 11) ^ hash;
		hash   = (hash << 16) ^ पंचांगp;
		data  += 2*माप (__u16);
		hash  += hash >> 11;
	पूर्ण

	/* Handle end हालs */
	चयन (rem) अणु
        हाल 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= ((चिन्हित अक्षर)data[माप (__u16)]) << 18;
                hash += hash >> 11;
                अवरोध;
        हाल 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                अवरोध;
        हाल 1: hash += (चिन्हित अक्षर)*data;
                hash ^= hash << 10;
                hash += hash >> 1;
	पूर्ण

	/* Force "avalanching" of final 127 bits */
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 4;
	hash += hash >> 17;
	hash ^= hash << 25;
	hash += hash >> 6;

	वापस hash;
पूर्ण

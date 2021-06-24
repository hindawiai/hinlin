<शैली गुरु>

#समावेश <linux/ceph/types.h>
#समावेश <linux/module.h>

/*
 * Robert Jenkin's hash function.
 * https://burtleburtle.net/bob/hash/evahash.hपंचांगl
 * This is in the खुला करोमुख्य.
 */
#घोषणा mix(a, b, c)						\
	करो अणु							\
		a = a - b;  a = a - c;  a = a ^ (c >> 13);	\
		b = b - c;  b = b - a;  b = b ^ (a << 8);	\
		c = c - a;  c = c - b;  c = c ^ (b >> 13);	\
		a = a - b;  a = a - c;  a = a ^ (c >> 12);	\
		b = b - c;  b = b - a;  b = b ^ (a << 16);	\
		c = c - a;  c = c - b;  c = c ^ (b >> 5);	\
		a = a - b;  a = a - c;  a = a ^ (c >> 3);	\
		b = b - c;  b = b - a;  b = b ^ (a << 10);	\
		c = c - a;  c = c - b;  c = c ^ (b >> 15);	\
	पूर्ण जबतक (0)

अचिन्हित पूर्णांक ceph_str_hash_rjenkins(स्थिर अक्षर *str, अचिन्हित पूर्णांक length)
अणु
	स्थिर अचिन्हित अक्षर *k = (स्थिर अचिन्हित अक्षर *)str;
	__u32 a, b, c;  /* the पूर्णांकernal state */
	__u32 len;      /* how many key bytes still need mixing */

	/* Set up the पूर्णांकernal state */
	len = length;
	a = 0x9e3779b9;      /* the golden ratio; an arbitrary value */
	b = a;
	c = 0;               /* variable initialization of पूर्णांकernal state */

	/* handle most of the key */
	जबतक (len >= 12) अणु
		a = a + (k[0] + ((__u32)k[1] << 8) + ((__u32)k[2] << 16) +
			 ((__u32)k[3] << 24));
		b = b + (k[4] + ((__u32)k[5] << 8) + ((__u32)k[6] << 16) +
			 ((__u32)k[7] << 24));
		c = c + (k[8] + ((__u32)k[9] << 8) + ((__u32)k[10] << 16) +
			 ((__u32)k[11] << 24));
		mix(a, b, c);
		k = k + 12;
		len = len - 12;
	पूर्ण

	/* handle the last 11 bytes */
	c = c + length;
	चयन (len) अणु
	हाल 11:
		c = c + ((__u32)k[10] << 24);
		fallthrough;
	हाल 10:
		c = c + ((__u32)k[9] << 16);
		fallthrough;
	हाल 9:
		c = c + ((__u32)k[8] << 8);
		/* the first byte of c is reserved क्रम the length */
		fallthrough;
	हाल 8:
		b = b + ((__u32)k[7] << 24);
		fallthrough;
	हाल 7:
		b = b + ((__u32)k[6] << 16);
		fallthrough;
	हाल 6:
		b = b + ((__u32)k[5] << 8);
		fallthrough;
	हाल 5:
		b = b + k[4];
		fallthrough;
	हाल 4:
		a = a + ((__u32)k[3] << 24);
		fallthrough;
	हाल 3:
		a = a + ((__u32)k[2] << 16);
		fallthrough;
	हाल 2:
		a = a + ((__u32)k[1] << 8);
		fallthrough;
	हाल 1:
		a = a + k[0];
		/* हाल 0: nothing left to add */
	पूर्ण
	mix(a, b, c);

	वापस c;
पूर्ण

/*
 * linux dcache hash
 */
अचिन्हित पूर्णांक ceph_str_hash_linux(स्थिर अक्षर *str, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित दीर्घ hash = 0;
	अचिन्हित अक्षर c;

	जबतक (length--) अणु
		c = *str++;
		hash = (hash + (c << 4) + (c >> 4)) * 11;
	पूर्ण
	वापस hash;
पूर्ण


अचिन्हित पूर्णांक ceph_str_hash(पूर्णांक type, स्थिर अक्षर *s, अचिन्हित पूर्णांक len)
अणु
	चयन (type) अणु
	हाल CEPH_STR_HASH_LINUX:
		वापस ceph_str_hash_linux(s, len);
	हाल CEPH_STR_HASH_RJENKINS:
		वापस ceph_str_hash_rjenkins(s, len);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_str_hash);

स्थिर अक्षर *ceph_str_hash_name(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल CEPH_STR_HASH_LINUX:
		वापस "linux";
	हाल CEPH_STR_HASH_RJENKINS:
		वापस "rjenkins";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_str_hash_name);

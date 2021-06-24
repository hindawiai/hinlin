<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/hash.c
 *
 * Copyright (C) 2002 by Theoकरोre Ts'o
 */

#समावेश <linux/fs.h>
#समावेश <linux/unicode.h>
#समावेश <linux/compiler.h>
#समावेश <linux/bitops.h>
#समावेश "ext4.h"

#घोषणा DELTA 0x9E3779B9

अटल व्योम TEA_transक्रमm(__u32 buf[4], __u32 स्थिर in[])
अणु
	__u32	sum = 0;
	__u32	b0 = buf[0], b1 = buf[1];
	__u32	a = in[0], b = in[1], c = in[2], d = in[3];
	पूर्णांक	n = 16;

	करो अणु
		sum += DELTA;
		b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);
		b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);
	पूर्ण जबतक (--n);

	buf[0] += b0;
	buf[1] += b1;
पूर्ण

/* F, G and H are basic MD4 functions: selection, majority, parity */
#घोषणा F(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
#घोषणा G(x, y, z) (((x) & (y)) + (((x) ^ (y)) & (z)))
#घोषणा H(x, y, z) ((x) ^ (y) ^ (z))

/*
 * The generic round function.  The application is so specअगरic that
 * we करोn't bother protecting all the arguments with parens, as is generally
 * good macro practice, in favor of extra legibility.
 * Rotation is separate from addition to prevent recomputation
 */
#घोषणा ROUND(f, a, b, c, d, x, s)	\
	(a += f(b, c, d) + x, a = rol32(a, s))
#घोषणा K1 0
#घोषणा K2 013240474631UL
#घोषणा K3 015666365641UL

/*
 * Basic cut-करोwn MD4 transक्रमm.  Returns only 32 bits of result.
 */
अटल __u32 half_md4_transक्रमm(__u32 buf[4], __u32 स्थिर in[8])
अणु
	__u32 a = buf[0], b = buf[1], c = buf[2], d = buf[3];

	/* Round 1 */
	ROUND(F, a, b, c, d, in[0] + K1,  3);
	ROUND(F, d, a, b, c, in[1] + K1,  7);
	ROUND(F, c, d, a, b, in[2] + K1, 11);
	ROUND(F, b, c, d, a, in[3] + K1, 19);
	ROUND(F, a, b, c, d, in[4] + K1,  3);
	ROUND(F, d, a, b, c, in[5] + K1,  7);
	ROUND(F, c, d, a, b, in[6] + K1, 11);
	ROUND(F, b, c, d, a, in[7] + K1, 19);

	/* Round 2 */
	ROUND(G, a, b, c, d, in[1] + K2,  3);
	ROUND(G, d, a, b, c, in[3] + K2,  5);
	ROUND(G, c, d, a, b, in[5] + K2,  9);
	ROUND(G, b, c, d, a, in[7] + K2, 13);
	ROUND(G, a, b, c, d, in[0] + K2,  3);
	ROUND(G, d, a, b, c, in[2] + K2,  5);
	ROUND(G, c, d, a, b, in[4] + K2,  9);
	ROUND(G, b, c, d, a, in[6] + K2, 13);

	/* Round 3 */
	ROUND(H, a, b, c, d, in[3] + K3,  3);
	ROUND(H, d, a, b, c, in[7] + K3,  9);
	ROUND(H, c, d, a, b, in[2] + K3, 11);
	ROUND(H, b, c, d, a, in[6] + K3, 15);
	ROUND(H, a, b, c, d, in[1] + K3,  3);
	ROUND(H, d, a, b, c, in[5] + K3,  9);
	ROUND(H, c, d, a, b, in[0] + K3, 11);
	ROUND(H, b, c, d, a, in[4] + K3, 15);

	buf[0] += a;
	buf[1] += b;
	buf[2] += c;
	buf[3] += d;

	वापस buf[1]; /* "most hashed" word */
पूर्ण
#अघोषित ROUND
#अघोषित K1
#अघोषित K2
#अघोषित K3
#अघोषित F
#अघोषित G
#अघोषित H

/* The old legacy hash */
अटल __u32 dx_hack_hash_अचिन्हित(स्थिर अक्षर *name, पूर्णांक len)
अणु
	__u32 hash, hash0 = 0x12a3fe2d, hash1 = 0x37abe8f9;
	स्थिर अचिन्हित अक्षर *ucp = (स्थिर अचिन्हित अक्षर *) name;

	जबतक (len--) अणु
		hash = hash1 + (hash0 ^ (((पूर्णांक) *ucp++) * 7152373));

		अगर (hash & 0x80000000)
			hash -= 0x7fffffff;
		hash1 = hash0;
		hash0 = hash;
	पूर्ण
	वापस hash0 << 1;
पूर्ण

अटल __u32 dx_hack_hash_चिन्हित(स्थिर अक्षर *name, पूर्णांक len)
अणु
	__u32 hash, hash0 = 0x12a3fe2d, hash1 = 0x37abe8f9;
	स्थिर चिन्हित अक्षर *scp = (स्थिर चिन्हित अक्षर *) name;

	जबतक (len--) अणु
		hash = hash1 + (hash0 ^ (((पूर्णांक) *scp++) * 7152373));

		अगर (hash & 0x80000000)
			hash -= 0x7fffffff;
		hash1 = hash0;
		hash0 = hash;
	पूर्ण
	वापस hash0 << 1;
पूर्ण

अटल व्योम str2hashbuf_चिन्हित(स्थिर अक्षर *msg, पूर्णांक len, __u32 *buf, पूर्णांक num)
अणु
	__u32	pad, val;
	पूर्णांक	i;
	स्थिर चिन्हित अक्षर *scp = (स्थिर चिन्हित अक्षर *) msg;

	pad = (__u32)len | ((__u32)len << 8);
	pad |= pad << 16;

	val = pad;
	अगर (len > num*4)
		len = num * 4;
	क्रम (i = 0; i < len; i++) अणु
		val = ((पूर्णांक) scp[i]) + (val << 8);
		अगर ((i % 4) == 3) अणु
			*buf++ = val;
			val = pad;
			num--;
		पूर्ण
	पूर्ण
	अगर (--num >= 0)
		*buf++ = val;
	जबतक (--num >= 0)
		*buf++ = pad;
पूर्ण

अटल व्योम str2hashbuf_अचिन्हित(स्थिर अक्षर *msg, पूर्णांक len, __u32 *buf, पूर्णांक num)
अणु
	__u32	pad, val;
	पूर्णांक	i;
	स्थिर अचिन्हित अक्षर *ucp = (स्थिर अचिन्हित अक्षर *) msg;

	pad = (__u32)len | ((__u32)len << 8);
	pad |= pad << 16;

	val = pad;
	अगर (len > num*4)
		len = num * 4;
	क्रम (i = 0; i < len; i++) अणु
		val = ((पूर्णांक) ucp[i]) + (val << 8);
		अगर ((i % 4) == 3) अणु
			*buf++ = val;
			val = pad;
			num--;
		पूर्ण
	पूर्ण
	अगर (--num >= 0)
		*buf++ = val;
	जबतक (--num >= 0)
		*buf++ = pad;
पूर्ण

/*
 * Returns the hash of a filename.  If len is 0 and name is शून्य, then
 * this function can be used to test whether or not a hash version is
 * supported.
 *
 * The seed is an 4 दीर्घword (32 bits) "secret" which can be used to
 * uniquअगरy a hash.  If the seed is all zero's, then some शेष seed
 * may be used.
 *
 * A particular hash version specअगरies whether or not the seed is
 * represented, and whether or not the वापसed hash is 32 bits or 64
 * bits.  32 bit hashes will वापस 0 क्रम the minor hash.
 */
अटल पूर्णांक __ext4fs_dirhash(स्थिर काष्ठा inode *dir, स्थिर अक्षर *name, पूर्णांक len,
			    काष्ठा dx_hash_info *hinfo)
अणु
	__u32	hash;
	__u32	minor_hash = 0;
	स्थिर अक्षर	*p;
	पूर्णांक		i;
	__u32		in[8], buf[4];
	व्योम		(*str2hashbuf)(स्थिर अक्षर *, पूर्णांक, __u32 *, पूर्णांक) =
				str2hashbuf_चिन्हित;

	/* Initialize the शेष seed क्रम the hash checksum functions */
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;

	/* Check to see अगर the seed is all zero's */
	अगर (hinfo->seed) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर (hinfo->seed[i]) अणु
				स_नकल(buf, hinfo->seed, माप(buf));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (hinfo->hash_version) अणु
	हाल DX_HASH_LEGACY_UNSIGNED:
		hash = dx_hack_hash_अचिन्हित(name, len);
		अवरोध;
	हाल DX_HASH_LEGACY:
		hash = dx_hack_hash_चिन्हित(name, len);
		अवरोध;
	हाल DX_HASH_HALF_MD4_UNSIGNED:
		str2hashbuf = str2hashbuf_अचिन्हित;
		fallthrough;
	हाल DX_HASH_HALF_MD4:
		p = name;
		जबतक (len > 0) अणु
			(*str2hashbuf)(p, len, in, 8);
			half_md4_transक्रमm(buf, in);
			len -= 32;
			p += 32;
		पूर्ण
		minor_hash = buf[2];
		hash = buf[1];
		अवरोध;
	हाल DX_HASH_TEA_UNSIGNED:
		str2hashbuf = str2hashbuf_अचिन्हित;
		fallthrough;
	हाल DX_HASH_TEA:
		p = name;
		जबतक (len > 0) अणु
			(*str2hashbuf)(p, len, in, 4);
			TEA_transक्रमm(buf, in);
			len -= 16;
			p += 16;
		पूर्ण
		hash = buf[0];
		minor_hash = buf[1];
		अवरोध;
	हाल DX_HASH_SIPHASH:
	अणु
		काष्ठा qstr qname = QSTR_INIT(name, len);
		__u64	combined_hash;

		अगर (fscrypt_has_encryption_key(dir)) अणु
			combined_hash = fscrypt_fname_siphash(dir, &qname);
		पूर्ण अन्यथा अणु
			ext4_warning_inode(dir, "Siphash requires key");
			वापस -1;
		पूर्ण

		hash = (__u32)(combined_hash >> 32);
		minor_hash = (__u32)combined_hash;
		अवरोध;
	पूर्ण
	शेष:
		hinfo->hash = 0;
		वापस -1;
	पूर्ण
	hash = hash & ~1;
	अगर (hash == (EXT4_HTREE_खातापूर्ण_32BIT << 1))
		hash = (EXT4_HTREE_खातापूर्ण_32BIT - 1) << 1;
	hinfo->hash = hash;
	hinfo->minor_hash = minor_hash;
	वापस 0;
पूर्ण

पूर्णांक ext4fs_dirhash(स्थिर काष्ठा inode *dir, स्थिर अक्षर *name, पूर्णांक len,
		   काष्ठा dx_hash_info *hinfo)
अणु
#अगर_घोषित CONFIG_UNICODE
	स्थिर काष्ठा unicode_map *um = dir->i_sb->s_encoding;
	पूर्णांक r, dlen;
	अचिन्हित अक्षर *buff;
	काष्ठा qstr qstr = अणु.name = name, .len = len पूर्ण;

	अगर (len && IS_CASEFOLDED(dir) && um &&
	   (!IS_ENCRYPTED(dir) || fscrypt_has_encryption_key(dir))) अणु
		buff = kzalloc(माप(अक्षर) * PATH_MAX, GFP_KERNEL);
		अगर (!buff)
			वापस -ENOMEM;

		dlen = utf8_हालfold(um, &qstr, buff, PATH_MAX);
		अगर (dlen < 0) अणु
			kमुक्त(buff);
			जाओ opaque_seq;
		पूर्ण

		r = __ext4fs_dirhash(dir, buff, dlen, hinfo);

		kमुक्त(buff);
		वापस r;
	पूर्ण
opaque_seq:
#पूर्ण_अगर
	वापस __ext4fs_dirhash(dir, name, len, hinfo);
पूर्ण

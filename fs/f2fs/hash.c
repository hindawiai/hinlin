<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/hash.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 *
 * Portions of this code from linux/fs/ext3/hash.c
 *
 * Copyright (C) 2002 by Theoकरोre Ts'o
 */
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/unicode.h>

#समावेश "f2fs.h"

/*
 * Hashing code copied from ext3
 */
#घोषणा DELTA 0x9E3779B9

अटल व्योम TEA_transक्रमm(अचिन्हित पूर्णांक buf[4], अचिन्हित पूर्णांक स्थिर in[])
अणु
	__u32 sum = 0;
	__u32 b0 = buf[0], b1 = buf[1];
	__u32 a = in[0], b = in[1], c = in[2], d = in[3];
	पूर्णांक n = 16;

	करो अणु
		sum += DELTA;
		b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);
		b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);
	पूर्ण जबतक (--n);

	buf[0] += b0;
	buf[1] += b1;
पूर्ण

अटल व्योम str2hashbuf(स्थिर अचिन्हित अक्षर *msg, माप_प्रकार len,
				अचिन्हित पूर्णांक *buf, पूर्णांक num)
अणु
	अचिन्हित pad, val;
	पूर्णांक i;

	pad = (__u32)len | ((__u32)len << 8);
	pad |= pad << 16;

	val = pad;
	अगर (len > num * 4)
		len = num * 4;
	क्रम (i = 0; i < len; i++) अणु
		अगर ((i % 4) == 0)
			val = pad;
		val = msg[i] + (val << 8);
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

अटल u32 TEA_hash_name(स्थिर u8 *p, माप_प्रकार len)
अणु
	__u32 in[8], buf[4];

	/* Initialize the शेष seed क्रम the hash checksum functions */
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;

	जबतक (1) अणु
		str2hashbuf(p, len, in, 4);
		TEA_transक्रमm(buf, in);
		p += 16;
		अगर (len <= 16)
			अवरोध;
		len -= 16;
	पूर्ण
	वापस buf[0] & ~F2FS_HASH_COL_BIT;
पूर्ण

/*
 * Compute @fname->hash.  For all directories, @fname->disk_name must be set.
 * For हालfolded directories, @fname->usr_fname must be set, and also
 * @fname->cf_name अगर the filename is valid Unicode.
 */
व्योम f2fs_hash_filename(स्थिर काष्ठा inode *dir, काष्ठा f2fs_filename *fname)
अणु
	स्थिर u8 *name = fname->disk_name.name;
	माप_प्रकार len = fname->disk_name.len;

	WARN_ON_ONCE(!name);

	अगर (is_करोt_करोtकरोt(name, len)) अणु
		fname->hash = 0;
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_UNICODE
	अगर (IS_CASEFOLDED(dir)) अणु
		/*
		 * If the हालfolded name is provided, hash it instead of the
		 * on-disk name.  If the हालfolded name is *not* provided, that
		 * should only be because the name wasn't valid Unicode, so fall
		 * back to treating the name as an opaque byte sequence.  Note
		 * that to handle encrypted directories, the fallback must use
		 * usr_fname (plaपूर्णांकext) rather than disk_name (ciphertext).
		 */
		WARN_ON_ONCE(!fname->usr_fname->name);
		अगर (fname->cf_name.name) अणु
			name = fname->cf_name.name;
			len = fname->cf_name.len;
		पूर्ण अन्यथा अणु
			name = fname->usr_fname->name;
			len = fname->usr_fname->len;
		पूर्ण
		अगर (IS_ENCRYPTED(dir)) अणु
			काष्ठा qstr पंचांगp = QSTR_INIT(name, len);

			fname->hash =
				cpu_to_le32(fscrypt_fname_siphash(dir, &पंचांगp));
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	fname->hash = cpu_to_le32(TEA_hash_name(name, len));
पूर्ण

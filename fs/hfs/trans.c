<शैली गुरु>
/*
 *  linux/fs/hfs/trans.c
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * This file contains routines क्रम converting between the Macपूर्णांकosh
 * अक्षरacter set and various other encodings.  This includes dealing
 * with ':' vs. '/' as the path-element separator.
 */

#समावेश <linux/types.h>
#समावेश <linux/nls.h>

#समावेश "hfs_fs.h"

/*================ Global functions ================*/

/*
 * hfs_mac2asc()
 *
 * Given a 'Pascal String' (a string preceded by a length byte) in
 * the Macपूर्णांकosh अक्षरacter set produce the corresponding filename using
 * the 'trivial' name-mangling scheme, वापसing the length of the
 * mangled filename.  Note that the output string is not शून्य
 * terminated.
 *
 * The name-mangling works as follows:
 * The अक्षरacter '/', which is illegal in Linux filenames is replaced
 * by ':' which never appears in HFS filenames.	 All other अक्षरacters
 * are passed unchanged from input to output.
 */
पूर्णांक hfs_mac2asc(काष्ठा super_block *sb, अक्षर *out, स्थिर काष्ठा hfs_name *in)
अणु
	काष्ठा nls_table *nls_disk = HFS_SB(sb)->nls_disk;
	काष्ठा nls_table *nls_io = HFS_SB(sb)->nls_io;
	स्थिर अक्षर *src;
	अक्षर *dst;
	पूर्णांक srclen, dstlen, size;

	src = in->name;
	srclen = in->len;
	अगर (srclen > HFS_NAMELEN)
		srclen = HFS_NAMELEN;
	dst = out;
	dstlen = HFS_MAX_NAMELEN;
	अगर (nls_io) अणु
		ब_अक्षर_प्रकार ch;

		जबतक (srclen > 0) अणु
			अगर (nls_disk) अणु
				size = nls_disk->अक्षर2uni(src, srclen, &ch);
				अगर (size <= 0) अणु
					ch = '?';
					size = 1;
				पूर्ण
				src += size;
				srclen -= size;
			पूर्ण अन्यथा अणु
				ch = *src++;
				srclen--;
			पूर्ण
			अगर (ch == '/')
				ch = ':';
			size = nls_io->uni2अक्षर(ch, dst, dstlen);
			अगर (size < 0) अणु
				अगर (size == -ENAMETOOLONG)
					जाओ out;
				*dst = '?';
				size = 1;
			पूर्ण
			dst += size;
			dstlen -= size;
		पूर्ण
	पूर्ण अन्यथा अणु
		अक्षर ch;

		जबतक (--srclen >= 0)
			*dst++ = (ch = *src++) == '/' ? ':' : ch;
	पूर्ण
out:
	वापस dst - out;
पूर्ण

/*
 * hfs_asc2mac()
 *
 * Given an ASCII string (not null-terminated) and its length,
 * generate the corresponding filename in the Macपूर्णांकosh अक्षरacter set
 * using the 'trivial' name-mangling scheme, वापसing the length of
 * the mangled filename.  Note that the output string is not शून्य
 * terminated.
 *
 * This routine is a inverse to hfs_mac2triv().
 * A ':' is replaced by a '/'.
 */
व्योम hfs_asc2mac(काष्ठा super_block *sb, काष्ठा hfs_name *out, स्थिर काष्ठा qstr *in)
अणु
	काष्ठा nls_table *nls_disk = HFS_SB(sb)->nls_disk;
	काष्ठा nls_table *nls_io = HFS_SB(sb)->nls_io;
	स्थिर अक्षर *src;
	अक्षर *dst;
	पूर्णांक srclen, dstlen, size;

	src = in->name;
	srclen = in->len;
	dst = out->name;
	dstlen = HFS_NAMELEN;
	अगर (nls_io) अणु
		ब_अक्षर_प्रकार ch;

		जबतक (srclen > 0) अणु
			size = nls_io->अक्षर2uni(src, srclen, &ch);
			अगर (size < 0) अणु
				ch = '?';
				size = 1;
			पूर्ण
			src += size;
			srclen -= size;
			अगर (ch == ':')
				ch = '/';
			अगर (nls_disk) अणु
				size = nls_disk->uni2अक्षर(ch, dst, dstlen);
				अगर (size < 0) अणु
					अगर (size == -ENAMETOOLONG)
						जाओ out;
					*dst = '?';
					size = 1;
				पूर्ण
				dst += size;
				dstlen -= size;
			पूर्ण अन्यथा अणु
				*dst++ = ch > 0xff ? '?' : ch;
				dstlen--;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अक्षर ch;

		अगर (dstlen > srclen)
			dstlen = srclen;
		जबतक (--dstlen >= 0)
			*dst++ = (ch = *src++) == ':' ? '/' : ch;
	पूर्ण
out:
	out->len = dst - (अक्षर *)out->name;
	dstlen = HFS_NAMELEN - out->len;
	जबतक (--dstlen >= 0)
		*dst++ = 0;
पूर्ण

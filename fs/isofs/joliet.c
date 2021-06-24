<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/isofs/joliet.c
 *
 *  (C) 1996 Gorकरोn Chaffee
 *
 *  Joliet: Microsoft's Unicode extensions to iso9660
 */

#समावेश <linux/types.h>
#समावेश <linux/nls.h>
#समावेश "isofs.h"

/*
 * Convert Unicode 16 to UTF-8 or ASCII.
 */
अटल पूर्णांक
uni16_to_x8(अचिन्हित अक्षर *ascii, __be16 *uni, पूर्णांक len, काष्ठा nls_table *nls)
अणु
	__be16 *ip, ch;
	अचिन्हित अक्षर *op;

	ip = uni;
	op = ascii;

	जबतक ((ch = get_unaligned(ip)) && len) अणु
		पूर्णांक llen;
		llen = nls->uni2अक्षर(be16_to_cpu(ch), op, NLS_MAX_CHARSET_SIZE);
		अगर (llen > 0)
			op += llen;
		अन्यथा
			*op++ = '?';
		ip++;

		len--;
	पूर्ण
	*op = 0;
	वापस (op - ascii);
पूर्ण

पूर्णांक
get_joliet_filename(काष्ठा iso_directory_record * de, अचिन्हित अक्षर *outname, काष्ठा inode * inode)
अणु
	अचिन्हित अक्षर utf8;
	काष्ठा nls_table *nls;
	अचिन्हित अक्षर len = 0;

	utf8 = ISOFS_SB(inode->i_sb)->s_utf8;
	nls = ISOFS_SB(inode->i_sb)->s_nls_ioअक्षरset;

	अगर (utf8) अणु
		len = utf16s_to_utf8s((स्थिर ब_अक्षर_प्रकार *) de->name,
				de->name_len[0] >> 1, UTF16_BIG_ENDIAN,
				outname, PAGE_SIZE);
	पूर्ण अन्यथा अणु
		len = uni16_to_x8(outname, (__be16 *) de->name,
				de->name_len[0] >> 1, nls);
	पूर्ण
	अगर ((len > 2) && (outname[len-2] == ';') && (outname[len-1] == '1'))
		len -= 2;

	/*
	 * Winकरोws करोesn't like periods at the end of a name,
	 * so neither करो we
	 */
	जबतक (len >= 2 && (outname[len-1] == '.'))
		len--;

	वापस len;
पूर्ण

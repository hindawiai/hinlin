<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_unicode.h"
#समावेश "jfs_debug.h"

/*
 * NAME:	jfs_strfromUCS()
 *
 * FUNCTION:	Convert little-endian unicode string to अक्षरacter string
 *
 */
पूर्णांक jfs_strfromUCS_le(अक्षर *to, स्थिर __le16 * from,
		      पूर्णांक len, काष्ठा nls_table *codepage)
अणु
	पूर्णांक i;
	पूर्णांक outlen = 0;
	अटल पूर्णांक warn_again = 5;	/* Only warn up to 5 बार total */
	पूर्णांक warn = !!warn_again;	/* once per string */

	अगर (codepage) अणु
		क्रम (i = 0; (i < len) && from[i]; i++) अणु
			पूर्णांक अक्षरlen;
			अक्षरlen =
			    codepage->uni2अक्षर(le16_to_cpu(from[i]),
					       &to[outlen],
					       NLS_MAX_CHARSET_SIZE);
			अगर (अक्षरlen > 0)
				outlen += अक्षरlen;
			अन्यथा
				to[outlen++] = '?';
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; (i < len) && from[i]; i++) अणु
			अगर (unlikely(le16_to_cpu(from[i]) & 0xff00)) अणु
				to[i] = '?';
				अगर (unlikely(warn)) अणु
					warn--;
					warn_again--;
					prपूर्णांकk(KERN_ERR
			"non-latin1 character 0x%x found in JFS file name\n",
					       le16_to_cpu(from[i]));
					prपूर्णांकk(KERN_ERR
				"mount with iocharset=utf8 to access\n");
				पूर्ण

			पूर्ण
			अन्यथा
				to[i] = (अक्षर) (le16_to_cpu(from[i]));
		पूर्ण
		outlen = i;
	पूर्ण
	to[outlen] = 0;
	वापस outlen;
पूर्ण

/*
 * NAME:	jfs_strtoUCS()
 *
 * FUNCTION:	Convert अक्षरacter string to unicode string
 *
 */
अटल पूर्णांक jfs_strtoUCS(ब_अक्षर_प्रकार * to, स्थिर अचिन्हित अक्षर *from, पूर्णांक len,
		काष्ठा nls_table *codepage)
अणु
	पूर्णांक अक्षरlen;
	पूर्णांक i;

	अगर (codepage) अणु
		क्रम (i = 0; len && *from; i++, from += अक्षरlen, len -= अक्षरlen)
		अणु
			अक्षरlen = codepage->अक्षर2uni(from, len, &to[i]);
			अगर (अक्षरlen < 1) अणु
				jfs_err("jfs_strtoUCS: char2uni returned %d.",
					अक्षरlen);
				jfs_err("charset = %s, char = 0x%x",
					codepage->अक्षरset, *from);
				वापस अक्षरlen;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; (i < len) && from[i]; i++)
			to[i] = (ब_अक्षर_प्रकार) from[i];
	पूर्ण

	to[i] = 0;
	वापस i;
पूर्ण

/*
 * NAME:	get_UCSname()
 *
 * FUNCTION:	Allocate and translate to unicode string
 *
 */
पूर्णांक get_UCSname(काष्ठा component_name * uniName, काष्ठा dentry *dentry)
अणु
	काष्ठा nls_table *nls_tab = JFS_SBI(dentry->d_sb)->nls_tab;
	पूर्णांक length = dentry->d_name.len;

	अगर (length > JFS_NAME_MAX)
		वापस -ENAMETOOLONG;

	uniName->name =
	    kदो_स्मृति_array(length + 1, माप(ब_अक्षर_प्रकार), GFP_NOFS);

	अगर (uniName->name == शून्य)
		वापस -ENOMEM;

	uniName->namlen = jfs_strtoUCS(uniName->name, dentry->d_name.name,
				       length, nls_tab);

	अगर (uniName->namlen < 0) अणु
		kमुक्त(uniName->name);
		वापस uniName->namlen;
	पूर्ण

	वापस 0;
पूर्ण

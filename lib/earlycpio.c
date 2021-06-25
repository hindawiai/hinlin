<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2012 Intel Corporation; author H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * earlycpio.c
 *
 * Find a specअगरic cpio member; must precede any compressed content.
 * This is used to locate data items in the initramfs used by the
 * kernel itself during early boot (beक्रमe the मुख्य initramfs is
 * decompressed.)  It is the responsibility of the initramfs creator
 * to ensure that these items are uncompressed at the head of the
 * blob.  Depending on the boot loader or package tool that may be a
 * separate file or part of the same file.
 */

#समावेश <linux/earlycpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

क्रमागत cpio_fields अणु
	C_MAGIC,
	C_INO,
	C_MODE,
	C_UID,
	C_GID,
	C_NLINK,
	C_MTIME,
	C_खाताSIZE,
	C_MAJ,
	C_MIN,
	C_RMAJ,
	C_RMIN,
	C_NAMESIZE,
	C_CHKSUM,
	C_NFIELDS
पूर्ण;

/**
 * find_cpio_data - Search क्रम files in an uncompressed cpio
 * @path:       The directory to search क्रम, including a slash at the end
 * @data:       Poपूर्णांकer to the cpio archive or a header inside
 * @len:        Reमुख्यing length of the cpio based on data poपूर्णांकer
 * @nextoff:    When a matching file is found, this is the offset from the
 *              beginning of the cpio to the beginning of the next file, not the
 *              matching file itself. It can be used to iterate through the cpio
 *              to find all files inside of a directory path.
 *
 * Return:      &काष्ठा cpio_data containing the address, length and
 *              filename (with the directory path cut off) of the found file.
 *              If you search क्रम a filename and not क्रम files in a directory,
 *              pass the असलolute path of the filename in the cpio and make sure
 *              the match वापसed an empty filename string.
 */

काष्ठा cpio_data find_cpio_data(स्थिर अक्षर *path, व्योम *data,
				माप_प्रकार len,  दीर्घ *nextoff)
अणु
	स्थिर माप_प्रकार cpio_header_len = 8*C_NFIELDS - 2;
	काष्ठा cpio_data cd = अणु शून्य, 0, "" पूर्ण;
	स्थिर अक्षर *p, *dptr, *nptr;
	अचिन्हित पूर्णांक ch[C_NFIELDS], *chp, v;
	अचिन्हित अक्षर c, x;
	माप_प्रकार mypathsize = म_माप(path);
	पूर्णांक i, j;

	p = data;

	जबतक (len > cpio_header_len) अणु
		अगर (!*p) अणु
			/* All cpio headers need to be 4-byte aligned */
			p += 4;
			len -= 4;
			जारी;
		पूर्ण

		j = 6;		/* The magic field is only 6 अक्षरacters */
		chp = ch;
		क्रम (i = C_NFIELDS; i; i--) अणु
			v = 0;
			जबतक (j--) अणु
				v <<= 4;
				c = *p++;

				x = c - '0';
				अगर (x < 10) अणु
					v += x;
					जारी;
				पूर्ण

				x = (c | 0x20) - 'a';
				अगर (x < 6) अणु
					v += x + 10;
					जारी;
				पूर्ण

				जाओ quit; /* Invalid hexadecimal */
			पूर्ण
			*chp++ = v;
			j = 8;	/* All other fields are 8 अक्षरacters */
		पूर्ण

		अगर ((ch[C_MAGIC] - 0x070701) > 1)
			जाओ quit; /* Invalid magic */

		len -= cpio_header_len;

		dptr = PTR_ALIGN(p + ch[C_NAMESIZE], 4);
		nptr = PTR_ALIGN(dptr + ch[C_खाताSIZE], 4);

		अगर (nptr > p + len || dptr < p || nptr < dptr)
			जाओ quit; /* Buffer overrun */

		अगर ((ch[C_MODE] & 0170000) == 0100000 &&
		    ch[C_NAMESIZE] >= mypathsize &&
		    !स_भेद(p, path, mypathsize)) अणु

			अगर (nextoff)
				*nextoff = (दीर्घ)nptr - (दीर्घ)data;

			अगर (ch[C_NAMESIZE] - mypathsize >= MAX_CPIO_खाता_NAME) अणु
				pr_warn(
				"File %s exceeding MAX_CPIO_FILE_NAME [%d]\n",
				p, MAX_CPIO_खाता_NAME);
			पूर्ण
			strlcpy(cd.name, p + mypathsize, MAX_CPIO_खाता_NAME);

			cd.data = (व्योम *)dptr;
			cd.size = ch[C_खाताSIZE];
			वापस cd; /* Found it! */
		पूर्ण
		len -= (nptr - p);
		p = nptr;
	पूर्ण

quit:
	वापस cd;
पूर्ण

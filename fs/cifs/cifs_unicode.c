<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   fs/cअगरs/cअगरs_unicode.c
 *
 *   Copyright (c) International Business Machines  Corp., 2000,2009
 *   Modअगरied by Steve French (sfrench@us.ibm.com)
 */
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश "cifs_fs_sb.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_uniupr.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifs_debug.h"

पूर्णांक cअगरs_remap(काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	पूर्णांक map_type;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MAP_SFM_CHR)
		map_type = SFM_MAP_UNI_RSVD;
	अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR)
		map_type = SFU_MAP_UNI_RSVD;
	अन्यथा
		map_type = NO_MAP_UNI_RSVD;

	वापस map_type;
पूर्ण

/* Convert अक्षरacter using the SFU - "Services for Unix" remapping range */
अटल bool
convert_sfu_अक्षर(स्थिर __u16 src_अक्षर, अक्षर *target)
अणु
	/*
	 * BB: Cannot handle remapping UNI_SLASH until all the calls to
	 *     build_path_from_dentry are modअगरied, as they use slash as
	 *     separator.
	 */
	चयन (src_अक्षर) अणु
	हाल UNI_COLON:
		*target = ':';
		अवरोध;
	हाल UNI_ASTERISK:
		*target = '*';
		अवरोध;
	हाल UNI_QUESTION:
		*target = '?';
		अवरोध;
	हाल UNI_PIPE:
		*target = '|';
		अवरोध;
	हाल UNI_GRTRTHAN:
		*target = '>';
		अवरोध;
	हाल UNI_LESSTHAN:
		*target = '<';
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Convert अक्षरacter using the SFM - "Services for Mac" remapping range */
अटल bool
convert_sfm_अक्षर(स्थिर __u16 src_अक्षर, अक्षर *target)
अणु
	अगर (src_अक्षर >= 0xF001 && src_अक्षर <= 0xF01F) अणु
		*target = src_अक्षर - 0xF000;
		वापस true;
	पूर्ण
	चयन (src_अक्षर) अणु
	हाल SFM_COLON:
		*target = ':';
		अवरोध;
	हाल SFM_DOUBLEQUOTE:
		*target = '"';
		अवरोध;
	हाल SFM_ASTERISK:
		*target = '*';
		अवरोध;
	हाल SFM_QUESTION:
		*target = '?';
		अवरोध;
	हाल SFM_PIPE:
		*target = '|';
		अवरोध;
	हाल SFM_GRTRTHAN:
		*target = '>';
		अवरोध;
	हाल SFM_LESSTHAN:
		*target = '<';
		अवरोध;
	हाल SFM_SPACE:
		*target = ' ';
		अवरोध;
	हाल SFM_PERIOD:
		*target = '.';
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण


/*
 * cअगरs_mapअक्षर - convert a host-endian अक्षर to proper अक्षर in codepage
 * @target - where converted अक्षरacter should be copied
 * @src_अक्षर - 2 byte host-endian source अक्षरacter
 * @cp - codepage to which अक्षरacter should be converted
 * @map_type - How should the 7 NTFS/SMB reserved अक्षरacters be mapped to UCS2?
 *
 * This function handles the conversion of a single अक्षरacter. It is the
 * responsibility of the caller to ensure that the target buffer is large
 * enough to hold the result of the conversion (at least NLS_MAX_CHARSET_SIZE).
 */
अटल पूर्णांक
cअगरs_mapअक्षर(अक्षर *target, स्थिर __u16 *from, स्थिर काष्ठा nls_table *cp,
	     पूर्णांक maptype)
अणु
	पूर्णांक len = 1;
	__u16 src_अक्षर;

	src_अक्षर = *from;

	अगर ((maptype == SFM_MAP_UNI_RSVD) && convert_sfm_अक्षर(src_अक्षर, target))
		वापस len;
	अन्यथा अगर ((maptype == SFU_MAP_UNI_RSVD) &&
		  convert_sfu_अक्षर(src_अक्षर, target))
		वापस len;

	/* अगर अक्षरacter not one of seven in special remap set */
	len = cp->uni2अक्षर(src_अक्षर, target, NLS_MAX_CHARSET_SIZE);
	अगर (len <= 0)
		जाओ surrogate_pair;

	वापस len;

surrogate_pair:
	/* convert SURROGATE_PAIR and IVS */
	अगर (म_भेद(cp->अक्षरset, "utf8"))
		जाओ unknown;
	len = utf16s_to_utf8s(from, 3, UTF16_LITTLE_ENDIAN, target, 6);
	अगर (len <= 0)
		जाओ unknown;
	वापस len;

unknown:
	*target = '?';
	len = 1;
	वापस len;
पूर्ण

/*
 * cअगरs_from_utf16 - convert utf16le string to local अक्षरset
 * @to - destination buffer
 * @from - source buffer
 * @tolen - destination buffer size (in bytes)
 * @fromlen - source buffer size (in bytes)
 * @codepage - codepage to which अक्षरacters should be converted
 * @mapअक्षर - should अक्षरacters be remapped according to the mapअक्षरs option?
 *
 * Convert a little-endian utf16le string (as sent by the server) to a string
 * in the provided codepage. The tolen and fromlen parameters are to ensure
 * that the code करोesn't walk off of the end of the buffer (which is always
 * a danger अगर the alignment of the source buffer is off). The destination
 * string is always properly null terminated and fits in the destination
 * buffer. Returns the length of the destination string in bytes (including
 * null terminator).
 *
 * Note that some winकरोws versions actually send multiword UTF-16 अक्षरacters
 * instead of straight UTF16-2. The linux nls routines however aren't able to
 * deal with those अक्षरacters properly. In the event that we get some of
 * those अक्षरacters, they won't be translated properly.
 */
पूर्णांक
cअगरs_from_utf16(अक्षर *to, स्थिर __le16 *from, पूर्णांक tolen, पूर्णांक fromlen,
		स्थिर काष्ठा nls_table *codepage, पूर्णांक map_type)
अणु
	पूर्णांक i, अक्षरlen, safelen;
	पूर्णांक outlen = 0;
	पूर्णांक nullsize = nls_nullsize(codepage);
	पूर्णांक fromwords = fromlen / 2;
	अक्षर पंचांगp[NLS_MAX_CHARSET_SIZE];
	__u16 fपंचांगp[3];		/* fपंचांगp[3] = 3array x 2bytes = 6bytes UTF-16 */

	/*
	 * because the अक्षरs can be of varying widths, we need to take care
	 * not to overflow the destination buffer when we get बंद to the
	 * end of it. Until we get to this offset, we करोn't need to check
	 * क्रम overflow however.
	 */
	safelen = tolen - (NLS_MAX_CHARSET_SIZE + nullsize);

	क्रम (i = 0; i < fromwords; i++) अणु
		fपंचांगp[0] = get_unaligned_le16(&from[i]);
		अगर (fपंचांगp[0] == 0)
			अवरोध;
		अगर (i + 1 < fromwords)
			fपंचांगp[1] = get_unaligned_le16(&from[i + 1]);
		अन्यथा
			fपंचांगp[1] = 0;
		अगर (i + 2 < fromwords)
			fपंचांगp[2] = get_unaligned_le16(&from[i + 2]);
		अन्यथा
			fपंचांगp[2] = 0;

		/*
		 * check to see अगर converting this अक्षरacter might make the
		 * conversion bleed पूर्णांकo the null terminator
		 */
		अगर (outlen >= safelen) अणु
			अक्षरlen = cअगरs_mapअक्षर(पंचांगp, fपंचांगp, codepage, map_type);
			अगर ((outlen + अक्षरlen) > (tolen - nullsize))
				अवरोध;
		पूर्ण

		/* put converted अक्षर पूर्णांकo 'to' buffer */
		अक्षरlen = cअगरs_mapअक्षर(&to[outlen], fपंचांगp, codepage, map_type);
		outlen += अक्षरlen;

		/* अक्षरlen (=bytes of UTF-8 क्रम 1 अक्षरacter)
		 * 4bytes UTF-8(surrogate pair) is अक्षरlen=4
		 *   (4bytes UTF-16 code)
		 * 7-8bytes UTF-8(IVS) is अक्षरlen=3+4 or 4+4
		 *   (2 UTF-8 pairs भागided to 2 UTF-16 pairs) */
		अगर (अक्षरlen == 4)
			i++;
		अन्यथा अगर (अक्षरlen >= 5)
			/* 5-6bytes UTF-8 */
			i += 2;
	पूर्ण

	/* properly null-terminate string */
	क्रम (i = 0; i < nullsize; i++)
		to[outlen++] = 0;

	वापस outlen;
पूर्ण

/*
 * NAME:	cअगरs_strtoUTF16()
 *
 * FUNCTION:	Convert अक्षरacter string to unicode string
 *
 */
पूर्णांक
cअगरs_strtoUTF16(__le16 *to, स्थिर अक्षर *from, पूर्णांक len,
	      स्थिर काष्ठा nls_table *codepage)
अणु
	पूर्णांक अक्षरlen;
	पूर्णांक i;
	ब_अक्षर_प्रकार ब_अक्षर_प्रकारo; /* needed to quiet sparse */

	/* special हाल क्रम utf8 to handle no plane0 अक्षरs */
	अगर (!म_भेद(codepage->अक्षरset, "utf8")) अणु
		/*
		 * convert utf8 -> utf16, we assume we have enough space
		 * as caller should have assumed conversion करोes not overflow
		 * in destination len is length in ब_अक्षर_प्रकार units (16bits)
		 */
		i  = utf8s_to_utf16s(from, len, UTF16_LITTLE_ENDIAN,
				       (ब_अक्षर_प्रकार *) to, len);

		/* अगर success terminate and निकास */
		अगर (i >= 0)
			जाओ success;
		/*
		 * अगर fails fall back to UCS encoding as this
		 * function should not वापस negative values
		 * currently can fail only अगर source contains
		 * invalid encoded अक्षरacters
		 */
	पूर्ण

	क्रम (i = 0; len && *from; i++, from += अक्षरlen, len -= अक्षरlen) अणु
		अक्षरlen = codepage->अक्षर2uni(from, len, &ब_अक्षर_प्रकारo);
		अगर (अक्षरlen < 1) अणु
			cअगरs_dbg(VFS, "strtoUTF16: char2uni of 0x%x returned %d\n",
				 *from, अक्षरlen);
			/* A question mark */
			ब_अक्षर_प्रकारo = 0x003f;
			अक्षरlen = 1;
		पूर्ण
		put_unaligned_le16(ब_अक्षर_प्रकारo, &to[i]);
	पूर्ण

success:
	put_unaligned_le16(0, &to[i]);
	वापस i;
पूर्ण

/*
 * cअगरs_utf16_bytes - how दीर्घ will a string be after conversion?
 * @utf16 - poपूर्णांकer to input string
 * @maxbytes - करोn't go past this many bytes of input string
 * @codepage - destination codepage
 *
 * Walk a utf16le string and वापस the number of bytes that the string will
 * be after being converted to the given अक्षरset, not including any null
 * termination required. Don't walk past maxbytes in the source buffer.
 */
पूर्णांक
cअगरs_utf16_bytes(स्थिर __le16 *from, पूर्णांक maxbytes,
		स्थिर काष्ठा nls_table *codepage)
अणु
	पूर्णांक i;
	पूर्णांक अक्षरlen, outlen = 0;
	पूर्णांक maxwords = maxbytes / 2;
	अक्षर पंचांगp[NLS_MAX_CHARSET_SIZE];
	__u16 fपंचांगp[3];

	क्रम (i = 0; i < maxwords; i++) अणु
		fपंचांगp[0] = get_unaligned_le16(&from[i]);
		अगर (fपंचांगp[0] == 0)
			अवरोध;
		अगर (i + 1 < maxwords)
			fपंचांगp[1] = get_unaligned_le16(&from[i + 1]);
		अन्यथा
			fपंचांगp[1] = 0;
		अगर (i + 2 < maxwords)
			fपंचांगp[2] = get_unaligned_le16(&from[i + 2]);
		अन्यथा
			fपंचांगp[2] = 0;

		अक्षरlen = cअगरs_mapअक्षर(पंचांगp, fपंचांगp, codepage, NO_MAP_UNI_RSVD);
		outlen += अक्षरlen;
	पूर्ण

	वापस outlen;
पूर्ण

/*
 * cअगरs_strndup_from_utf16 - copy a string from wire क्रमmat to the local
 * codepage
 * @src - source string
 * @maxlen - करोn't walk past this many bytes in the source string
 * @is_unicode - is this a unicode string?
 * @codepage - destination codepage
 *
 * Take a string given by the server, convert it to the local codepage and
 * put it in a new buffer. Returns a poपूर्णांकer to the new string or शून्य on
 * error.
 */
अक्षर *
cअगरs_strndup_from_utf16(स्थिर अक्षर *src, स्थिर पूर्णांक maxlen,
			स्थिर bool is_unicode, स्थिर काष्ठा nls_table *codepage)
अणु
	पूर्णांक len;
	अक्षर *dst;

	अगर (is_unicode) अणु
		len = cअगरs_utf16_bytes((__le16 *) src, maxlen, codepage);
		len += nls_nullsize(codepage);
		dst = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!dst)
			वापस शून्य;
		cअगरs_from_utf16(dst, (__le16 *) src, len, maxlen, codepage,
			       NO_MAP_UNI_RSVD);
	पूर्ण अन्यथा अणु
		len = strnlen(src, maxlen);
		len++;
		dst = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!dst)
			वापस शून्य;
		strlcpy(dst, src, len);
	पूर्ण

	वापस dst;
पूर्ण

अटल __le16 convert_to_sfu_अक्षर(अक्षर src_अक्षर)
अणु
	__le16 dest_अक्षर;

	चयन (src_अक्षर) अणु
	हाल ':':
		dest_अक्षर = cpu_to_le16(UNI_COLON);
		अवरोध;
	हाल '*':
		dest_अक्षर = cpu_to_le16(UNI_ASTERISK);
		अवरोध;
	हाल '?':
		dest_अक्षर = cpu_to_le16(UNI_QUESTION);
		अवरोध;
	हाल '<':
		dest_अक्षर = cpu_to_le16(UNI_LESSTHAN);
		अवरोध;
	हाल '>':
		dest_अक्षर = cpu_to_le16(UNI_GRTRTHAN);
		अवरोध;
	हाल '|':
		dest_अक्षर = cpu_to_le16(UNI_PIPE);
		अवरोध;
	शेष:
		dest_अक्षर = 0;
	पूर्ण

	वापस dest_अक्षर;
पूर्ण

अटल __le16 convert_to_sfm_अक्षर(अक्षर src_अक्षर, bool end_of_string)
अणु
	__le16 dest_अक्षर;

	अगर (src_अक्षर >= 0x01 && src_अक्षर <= 0x1F) अणु
		dest_अक्षर = cpu_to_le16(src_अक्षर + 0xF000);
		वापस dest_अक्षर;
	पूर्ण
	चयन (src_अक्षर) अणु
	हाल ':':
		dest_अक्षर = cpu_to_le16(SFM_COLON);
		अवरोध;
	हाल '"':
		dest_अक्षर = cpu_to_le16(SFM_DOUBLEQUOTE);
		अवरोध;
	हाल '*':
		dest_अक्षर = cpu_to_le16(SFM_ASTERISK);
		अवरोध;
	हाल '?':
		dest_अक्षर = cpu_to_le16(SFM_QUESTION);
		अवरोध;
	हाल '<':
		dest_अक्षर = cpu_to_le16(SFM_LESSTHAN);
		अवरोध;
	हाल '>':
		dest_अक्षर = cpu_to_le16(SFM_GRTRTHAN);
		अवरोध;
	हाल '|':
		dest_अक्षर = cpu_to_le16(SFM_PIPE);
		अवरोध;
	हाल '.':
		अगर (end_of_string)
			dest_अक्षर = cpu_to_le16(SFM_PERIOD);
		अन्यथा
			dest_अक्षर = 0;
		अवरोध;
	हाल ' ':
		अगर (end_of_string)
			dest_अक्षर = cpu_to_le16(SFM_SPACE);
		अन्यथा
			dest_अक्षर = 0;
		अवरोध;
	शेष:
		dest_अक्षर = 0;
	पूर्ण

	वापस dest_अक्षर;
पूर्ण

/*
 * Convert 16 bit Unicode pathname to wire क्रमmat from string in current code
 * page. Conversion may involve remapping up the six अक्षरacters that are
 * only legal in POSIX-like OS (अगर they are present in the string). Path
 * names are little endian 16 bit Unicode on the wire
 */
पूर्णांक
cअगरsConvertToUTF16(__le16 *target, स्थिर अक्षर *source, पूर्णांक srclen,
		 स्थिर काष्ठा nls_table *cp, पूर्णांक map_अक्षरs)
अणु
	पूर्णांक i, अक्षरlen;
	पूर्णांक j = 0;
	अक्षर src_अक्षर;
	__le16 dst_अक्षर;
	ब_अक्षर_प्रकार पंचांगp;
	ब_अक्षर_प्रकार *ब_अक्षर_प्रकारo;	/* UTF-16 */
	पूर्णांक ret;
	unicode_t u;

	अगर (map_अक्षरs == NO_MAP_UNI_RSVD)
		वापस cअगरs_strtoUTF16(target, source, PATH_MAX, cp);

	ब_अक्षर_प्रकारo = kzalloc(6, GFP_KERNEL);

	क्रम (i = 0; i < srclen; j++) अणु
		src_अक्षर = source[i];
		अक्षरlen = 1;

		/* check अगर end of string */
		अगर (src_अक्षर == 0)
			जाओ ctoUTF16_out;

		/* see अगर we must remap this अक्षर */
		अगर (map_अक्षरs == SFU_MAP_UNI_RSVD)
			dst_अक्षर = convert_to_sfu_अक्षर(src_अक्षर);
		अन्यथा अगर (map_अक्षरs == SFM_MAP_UNI_RSVD) अणु
			bool end_of_string;

			/**
			 * Remap spaces and periods found at the end of every
			 * component of the path. The special हालs of '.' and
			 * '..' करो not need to be dealt with explicitly because
			 * they are addressed in namei.c:link_path_walk().
			 **/
			अगर ((i == srclen - 1) || (source[i+1] == '\\'))
				end_of_string = true;
			अन्यथा
				end_of_string = false;

			dst_अक्षर = convert_to_sfm_अक्षर(src_अक्षर, end_of_string);
		पूर्ण अन्यथा
			dst_अक्षर = 0;
		/*
		 * FIXME: We can not handle remapping backslash (UNI_SLASH)
		 * until all the calls to build_path_from_dentry are modअगरied,
		 * as they use backslash as separator.
		 */
		अगर (dst_अक्षर == 0) अणु
			अक्षरlen = cp->अक्षर2uni(source + i, srclen - i, &पंचांगp);
			dst_अक्षर = cpu_to_le16(पंचांगp);

			/*
			 * अगर no match, use question mark, which at least in
			 * some हालs serves as wild card
			 */
			अगर (अक्षरlen > 0)
				जाओ ctoUTF16;

			/* convert SURROGATE_PAIR */
			अगर (म_भेद(cp->अक्षरset, "utf8") || !ब_अक्षर_प्रकारo)
				जाओ unknown;
			अगर (*(source + i) & 0x80) अणु
				अक्षरlen = utf8_to_utf32(source + i, 6, &u);
				अगर (अक्षरlen < 0)
					जाओ unknown;
			पूर्ण अन्यथा
				जाओ unknown;
			ret  = utf8s_to_utf16s(source + i, अक्षरlen,
					       UTF16_LITTLE_ENDIAN,
					       ब_अक्षर_प्रकारo, 6);
			अगर (ret < 0)
				जाओ unknown;

			i += अक्षरlen;
			dst_अक्षर = cpu_to_le16(*ब_अक्षर_प्रकारo);
			अगर (अक्षरlen <= 3)
				/* 1-3bytes UTF-8 to 2bytes UTF-16 */
				put_unaligned(dst_अक्षर, &target[j]);
			अन्यथा अगर (अक्षरlen == 4) अणु
				/* 4bytes UTF-8(surrogate pair) to 4bytes UTF-16
				 * 7-8bytes UTF-8(IVS) भागided to 2 UTF-16
				 *   (अक्षरlen=3+4 or 4+4) */
				put_unaligned(dst_अक्षर, &target[j]);
				dst_अक्षर = cpu_to_le16(*(ब_अक्षर_प्रकारo + 1));
				j++;
				put_unaligned(dst_अक्षर, &target[j]);
			पूर्ण अन्यथा अगर (अक्षरlen >= 5) अणु
				/* 5-6bytes UTF-8 to 6bytes UTF-16 */
				put_unaligned(dst_अक्षर, &target[j]);
				dst_अक्षर = cpu_to_le16(*(ब_अक्षर_प्रकारo + 1));
				j++;
				put_unaligned(dst_अक्षर, &target[j]);
				dst_अक्षर = cpu_to_le16(*(ब_अक्षर_प्रकारo + 2));
				j++;
				put_unaligned(dst_अक्षर, &target[j]);
			पूर्ण
			जारी;

unknown:
			dst_अक्षर = cpu_to_le16(0x003f);
			अक्षरlen = 1;
		पूर्ण

ctoUTF16:
		/*
		 * अक्षरacter may take more than one byte in the source string,
		 * but will take exactly two bytes in the target string
		 */
		i += अक्षरlen;
		put_unaligned(dst_अक्षर, &target[j]);
	पूर्ण

ctoUTF16_out:
	put_unaligned(0, &target[j]); /* Null terminate target unicode string */
	kमुक्त(ब_अक्षर_प्रकारo);
	वापस j;
पूर्ण

/*
 * cअगरs_local_to_utf16_bytes - how दीर्घ will a string be after conversion?
 * @from - poपूर्णांकer to input string
 * @maxbytes - करोn't go past this many bytes of input string
 * @codepage - source codepage
 *
 * Walk a string and वापस the number of bytes that the string will
 * be after being converted to the given अक्षरset, not including any null
 * termination required. Don't walk past maxbytes in the source buffer.
 */

अटल पूर्णांक
cअगरs_local_to_utf16_bytes(स्थिर अक्षर *from, पूर्णांक len,
			  स्थिर काष्ठा nls_table *codepage)
अणु
	पूर्णांक अक्षरlen;
	पूर्णांक i;
	ब_अक्षर_प्रकार ब_अक्षर_प्रकारo;

	क्रम (i = 0; len && *from; i++, from += अक्षरlen, len -= अक्षरlen) अणु
		अक्षरlen = codepage->अक्षर2uni(from, len, &ब_अक्षर_प्रकारo);
		/* Failed conversion शेषs to a question mark */
		अगर (अक्षरlen < 1)
			अक्षरlen = 1;
	पूर्ण
	वापस 2 * i; /* UTF16 अक्षरacters are two bytes */
पूर्ण

/*
 * cअगरs_strndup_to_utf16 - copy a string to wire क्रमmat from the local codepage
 * @src - source string
 * @maxlen - करोn't walk past this many bytes in the source string
 * @utf16_len - the length of the allocated string in bytes (including null)
 * @cp - source codepage
 * @remap - map special अक्षरs
 *
 * Take a string convert it from the local codepage to UTF16 and
 * put it in a new buffer. Returns a poपूर्णांकer to the new string or शून्य on
 * error.
 */
__le16 *
cअगरs_strndup_to_utf16(स्थिर अक्षर *src, स्थिर पूर्णांक maxlen, पूर्णांक *utf16_len,
		      स्थिर काष्ठा nls_table *cp, पूर्णांक remap)
अणु
	पूर्णांक len;
	__le16 *dst;

	len = cअगरs_local_to_utf16_bytes(src, maxlen, cp);
	len += 2; /* शून्य */
	dst = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!dst) अणु
		*utf16_len = 0;
		वापस शून्य;
	पूर्ण
	cअगरsConvertToUTF16(dst, src, म_माप(src), cp, remap);
	*utf16_len = len;
	वापस dst;
पूर्ण

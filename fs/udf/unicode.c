<शैली गुरु>
/*
 * unicode.c
 *
 * PURPOSE
 *	Routines क्रम converting between UTF-8 and OSTA Compressed Unicode.
 *      Also handles filename mangling
 *
 * DESCRIPTION
 *	OSTA Compressed Unicode is explained in the OSTA UDF specअगरication.
 *		http://www.osta.org/
 *	UTF-8 is explained in the IETF RFC XXXX.
 *		ftp://ftp.पूर्णांकernic.net/rfc/rfcxxxx.txt
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 */

#समावेश "udfdecl.h"

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>	/* क्रम स_रखो */
#समावेश <linux/nls.h>
#समावेश <linux/crc-itu-t.h>
#समावेश <linux/slab.h>

#समावेश "udf_sb.h"

#घोषणा PLANE_SIZE 0x10000
#घोषणा UNICODE_MAX 0x10ffff
#घोषणा SURROGATE_MASK 0xfffff800
#घोषणा SURROGATE_PAIR 0x0000d800
#घोषणा SURROGATE_LOW  0x00000400
#घोषणा SURROGATE_अक्षर_बिटS 10
#घोषणा SURROGATE_CHAR_MASK ((1 << SURROGATE_अक्षर_बिटS) - 1)

#घोषणा ILLEGAL_CHAR_MARK	'_'
#घोषणा EXT_MARK		'.'
#घोषणा CRC_MARK		'#'
#घोषणा EXT_SIZE		5
/* Number of अक्षरs we need to store generated CRC to make filename unique */
#घोषणा CRC_LEN			5

अटल unicode_t get_utf16_अक्षर(स्थिर uपूर्णांक8_t *str_i, पूर्णांक str_i_max_len,
				पूर्णांक str_i_idx, पूर्णांक u_ch, unicode_t *ret)
अणु
	unicode_t c;
	पूर्णांक start_idx = str_i_idx;

	/* Expand OSTA compressed Unicode to Unicode */
	c = str_i[str_i_idx++];
	अगर (u_ch > 1)
		c = (c << 8) | str_i[str_i_idx++];
	अगर ((c & SURROGATE_MASK) == SURROGATE_PAIR) अणु
		unicode_t next;

		/* Trailing surrogate अक्षर */
		अगर (str_i_idx >= str_i_max_len) अणु
			c = UNICODE_MAX + 1;
			जाओ out;
		पूर्ण

		/* Low surrogate must follow the high one... */
		अगर (c & SURROGATE_LOW) अणु
			c = UNICODE_MAX + 1;
			जाओ out;
		पूर्ण

		WARN_ON_ONCE(u_ch != 2);
		next = str_i[str_i_idx++] << 8;
		next |= str_i[str_i_idx++];
		अगर ((next & SURROGATE_MASK) != SURROGATE_PAIR ||
		    !(next & SURROGATE_LOW)) अणु
			c = UNICODE_MAX + 1;
			जाओ out;
		पूर्ण

		c = PLANE_SIZE +
		    ((c & SURROGATE_CHAR_MASK) << SURROGATE_अक्षर_बिटS) +
		    (next & SURROGATE_CHAR_MASK);
	पूर्ण
out:
	*ret = c;
	वापस str_i_idx - start_idx;
पूर्ण


अटल पूर्णांक udf_name_conv_अक्षर(uपूर्णांक8_t *str_o, पूर्णांक str_o_max_len,
			      पूर्णांक *str_o_idx,
			      स्थिर uपूर्णांक8_t *str_i, पूर्णांक str_i_max_len,
			      पूर्णांक *str_i_idx,
			      पूर्णांक u_ch, पूर्णांक *needsCRC,
			      पूर्णांक (*conv_f)(ब_अक्षर_प्रकार, अचिन्हित अक्षर *, पूर्णांक),
			      पूर्णांक translate)
अणु
	unicode_t c;
	पूर्णांक illChar = 0;
	पूर्णांक len, gotch = 0;

	जबतक (!gotch && *str_i_idx < str_i_max_len) अणु
		अगर (*str_o_idx >= str_o_max_len) अणु
			*needsCRC = 1;
			वापस gotch;
		पूर्ण

		len = get_utf16_अक्षर(str_i, str_i_max_len, *str_i_idx, u_ch,
				     &c);
		/* These अक्षरs cannot be converted. Replace them. */
		अगर (c == 0 || c > UNICODE_MAX || (conv_f && c > MAX_WCHAR_T) ||
		    (translate && c == '/')) अणु
			illChar = 1;
			अगर (!translate)
				gotch = 1;
		पूर्ण अन्यथा अगर (illChar)
			अवरोध;
		अन्यथा
			gotch = 1;
		*str_i_idx += len;
	पूर्ण
	अगर (illChar) अणु
		*needsCRC = 1;
		c = ILLEGAL_CHAR_MARK;
		gotch = 1;
	पूर्ण
	अगर (gotch) अणु
		अगर (conv_f) अणु
			len = conv_f(c, &str_o[*str_o_idx],
				     str_o_max_len - *str_o_idx);
		पूर्ण अन्यथा अणु
			len = utf32_to_utf8(c, &str_o[*str_o_idx],
					    str_o_max_len - *str_o_idx);
			अगर (len < 0)
				len = -ENAMETOOLONG;
		पूर्ण
		/* Valid अक्षरacter? */
		अगर (len >= 0)
			*str_o_idx += len;
		अन्यथा अगर (len == -ENAMETOOLONG) अणु
			*needsCRC = 1;
			gotch = 0;
		पूर्ण अन्यथा अणु
			str_o[(*str_o_idx)++] = ILLEGAL_CHAR_MARK;
			*needsCRC = 1;
		पूर्ण
	पूर्ण
	वापस gotch;
पूर्ण

अटल पूर्णांक udf_name_from_CS0(काष्ठा super_block *sb,
			     uपूर्णांक8_t *str_o, पूर्णांक str_max_len,
			     स्थिर uपूर्णांक8_t *ocu, पूर्णांक ocu_len,
			     पूर्णांक translate)
अणु
	uपूर्णांक32_t c;
	uपूर्णांक8_t cmp_id;
	पूर्णांक idx, len;
	पूर्णांक u_ch;
	पूर्णांक needsCRC = 0;
	पूर्णांक ext_i_len, ext_max_len;
	पूर्णांक str_o_len = 0;	/* Length of resulting output */
	पूर्णांक ext_o_len = 0;	/* Extension output length */
	पूर्णांक ext_crc_len = 0;	/* Extension output length अगर used with CRC */
	पूर्णांक i_ext = -1;		/* Extension position in input buffer */
	पूर्णांक o_crc = 0;		/* Righपंचांगost possible output pos क्रम CRC+ext */
	अचिन्हित लघु valueCRC;
	uपूर्णांक8_t ext[EXT_SIZE * NLS_MAX_CHARSET_SIZE + 1];
	uपूर्णांक8_t crc[CRC_LEN];
	पूर्णांक (*conv_f)(ब_अक्षर_प्रकार, अचिन्हित अक्षर *, पूर्णांक);

	अगर (str_max_len <= 0)
		वापस 0;

	अगर (ocu_len == 0) अणु
		स_रखो(str_o, 0, str_max_len);
		वापस 0;
	पूर्ण

	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_NLS_MAP))
		conv_f = UDF_SB(sb)->s_nls_map->uni2अक्षर;
	अन्यथा
		conv_f = शून्य;

	cmp_id = ocu[0];
	अगर (cmp_id != 8 && cmp_id != 16) अणु
		स_रखो(str_o, 0, str_max_len);
		pr_err("unknown compression code (%u)\n", cmp_id);
		वापस -EINVAL;
	पूर्ण
	u_ch = cmp_id >> 3;

	ocu++;
	ocu_len--;

	अगर (ocu_len % u_ch) अणु
		pr_err("incorrect filename length (%d)\n", ocu_len + 1);
		वापस -EINVAL;
	पूर्ण

	अगर (translate) अणु
		/* Look क्रम extension */
		क्रम (idx = ocu_len - u_ch, ext_i_len = 0;
		     (idx >= 0) && (ext_i_len < EXT_SIZE);
		     idx -= u_ch, ext_i_len++) अणु
			c = ocu[idx];
			अगर (u_ch > 1)
				c = (c << 8) | ocu[idx + 1];

			अगर (c == EXT_MARK) अणु
				अगर (ext_i_len)
					i_ext = idx;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i_ext >= 0) अणु
			/* Convert extension */
			ext_max_len = min_t(पूर्णांक, माप(ext), str_max_len);
			ext[ext_o_len++] = EXT_MARK;
			idx = i_ext + u_ch;
			जबतक (udf_name_conv_अक्षर(ext, ext_max_len, &ext_o_len,
						  ocu, ocu_len, &idx,
						  u_ch, &needsCRC,
						  conv_f, translate)) अणु
				अगर ((ext_o_len + CRC_LEN) < str_max_len)
					ext_crc_len = ext_o_len;
			पूर्ण
		पूर्ण
	पूर्ण

	idx = 0;
	जबतक (1) अणु
		अगर (translate && (idx == i_ext)) अणु
			अगर (str_o_len > (str_max_len - ext_o_len))
				needsCRC = 1;
			अवरोध;
		पूर्ण

		अगर (!udf_name_conv_अक्षर(str_o, str_max_len, &str_o_len,
					ocu, ocu_len, &idx,
					u_ch, &needsCRC, conv_f, translate))
			अवरोध;

		अगर (translate &&
		    (str_o_len <= (str_max_len - ext_o_len - CRC_LEN)))
			o_crc = str_o_len;
	पूर्ण

	अगर (translate) अणु
		अगर (str_o_len <= 2 && str_o[0] == '.' &&
		    (str_o_len == 1 || str_o[1] == '.'))
			needsCRC = 1;
		अगर (needsCRC) अणु
			str_o_len = o_crc;
			valueCRC = crc_itu_t(0, ocu, ocu_len);
			crc[0] = CRC_MARK;
			crc[1] = hex_asc_upper_hi(valueCRC >> 8);
			crc[2] = hex_asc_upper_lo(valueCRC >> 8);
			crc[3] = hex_asc_upper_hi(valueCRC);
			crc[4] = hex_asc_upper_lo(valueCRC);
			len = min_t(पूर्णांक, CRC_LEN, str_max_len - str_o_len);
			स_नकल(&str_o[str_o_len], crc, len);
			str_o_len += len;
			ext_o_len = ext_crc_len;
		पूर्ण
		अगर (ext_o_len > 0) अणु
			स_नकल(&str_o[str_o_len], ext, ext_o_len);
			str_o_len += ext_o_len;
		पूर्ण
	पूर्ण

	वापस str_o_len;
पूर्ण

अटल पूर्णांक udf_name_to_CS0(काष्ठा super_block *sb,
			   uपूर्णांक8_t *ocu, पूर्णांक ocu_max_len,
			   स्थिर uपूर्णांक8_t *str_i, पूर्णांक str_len)
अणु
	पूर्णांक i, len;
	अचिन्हित पूर्णांक max_val;
	पूर्णांक u_len, u_ch;
	unicode_t uni_अक्षर;
	पूर्णांक (*conv_f)(स्थिर अचिन्हित अक्षर *, पूर्णांक, ब_अक्षर_प्रकार *);

	अगर (ocu_max_len <= 0)
		वापस 0;

	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_NLS_MAP))
		conv_f = UDF_SB(sb)->s_nls_map->अक्षर2uni;
	अन्यथा
		conv_f = शून्य;

	स_रखो(ocu, 0, ocu_max_len);
	ocu[0] = 8;
	max_val = 0xff;
	u_ch = 1;

try_again:
	u_len = 1;
	क्रम (i = 0; i < str_len; i += len) अणु
		/* Name didn't fit? */
		अगर (u_len + u_ch > ocu_max_len)
			वापस 0;
		अगर (conv_f) अणु
			ब_अक्षर_प्रकार wअक्षर;

			len = conv_f(&str_i[i], str_len - i, &wअक्षर);
			अगर (len > 0)
				uni_अक्षर = wअक्षर;
		पूर्ण अन्यथा अणु
			len = utf8_to_utf32(&str_i[i], str_len - i,
					    &uni_अक्षर);
		पूर्ण
		/* Invalid अक्षरacter, deal with it */
		अगर (len <= 0 || uni_अक्षर > UNICODE_MAX) अणु
			len = 1;
			uni_अक्षर = '?';
		पूर्ण

		अगर (uni_अक्षर > max_val) अणु
			unicode_t c;

			अगर (max_val == 0xff) अणु
				max_val = 0xffff;
				ocu[0] = 0x10;
				u_ch = 2;
				जाओ try_again;
			पूर्ण
			/*
			 * Use UTF-16 encoding क्रम अक्षरs outside we
			 * cannot encode directly.
			 */
			अगर (u_len + 2 * u_ch > ocu_max_len)
				वापस 0;

			uni_अक्षर -= PLANE_SIZE;
			c = SURROGATE_PAIR |
			    ((uni_अक्षर >> SURROGATE_अक्षर_बिटS) &
			     SURROGATE_CHAR_MASK);
			ocu[u_len++] = (uपूर्णांक8_t)(c >> 8);
			ocu[u_len++] = (uपूर्णांक8_t)(c & 0xff);
			uni_अक्षर = SURROGATE_PAIR | SURROGATE_LOW |
					(uni_अक्षर & SURROGATE_CHAR_MASK);
		पूर्ण

		अगर (max_val == 0xffff)
			ocu[u_len++] = (uपूर्णांक8_t)(uni_अक्षर >> 8);
		ocu[u_len++] = (uपूर्णांक8_t)(uni_अक्षर & 0xff);
	पूर्ण

	वापस u_len;
पूर्ण

/*
 * Convert CS0 dstring to output अक्षरset. Warning: This function may truncate
 * input string अगर it is too दीर्घ as it is used क्रम inक्रमmational strings only
 * and it is better to truncate the string than to refuse mounting a media.
 */
पूर्णांक udf_dstrCS0toChar(काष्ठा super_block *sb, uपूर्णांक8_t *utf_o, पूर्णांक o_len,
		      स्थिर uपूर्णांक8_t *ocu_i, पूर्णांक i_len)
अणु
	पूर्णांक s_len = 0;

	अगर (i_len > 0) अणु
		s_len = ocu_i[i_len - 1];
		अगर (s_len >= i_len) अणु
			pr_warn("incorrect dstring lengths (%d/%d),"
				" truncating\n", s_len, i_len);
			s_len = i_len - 1;
			/* 2-byte encoding? Need to round properly... */
			अगर (ocu_i[0] == 16)
				s_len -= (s_len - 1) & 2;
		पूर्ण
	पूर्ण

	वापस udf_name_from_CS0(sb, utf_o, o_len, ocu_i, s_len, 0);
पूर्ण

पूर्णांक udf_get_filename(काष्ठा super_block *sb, स्थिर uपूर्णांक8_t *sname, पूर्णांक slen,
		     uपूर्णांक8_t *dname, पूर्णांक dlen)
अणु
	पूर्णांक ret;

	अगर (!slen)
		वापस -EIO;

	अगर (dlen <= 0)
		वापस 0;

	ret = udf_name_from_CS0(sb, dname, dlen, sname, slen, 1);
	/* Zero length filename isn't valid... */
	अगर (ret == 0)
		ret = -EINVAL;
	वापस ret;
पूर्ण

पूर्णांक udf_put_filename(काष्ठा super_block *sb, स्थिर uपूर्णांक8_t *sname, पूर्णांक slen,
		     uपूर्णांक8_t *dname, पूर्णांक dlen)
अणु
	वापस udf_name_to_CS0(sb, dname, dlen, sname, slen);
पूर्ण


<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lib/hexdump.c
 */

#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/minmax.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/unaligned.h>

स्थिर अक्षर hex_asc[] = "0123456789abcdef";
EXPORT_SYMBOL(hex_asc);
स्थिर अक्षर hex_asc_upper[] = "0123456789ABCDEF";
EXPORT_SYMBOL(hex_asc_upper);

/**
 * hex_to_bin - convert a hex digit to its real value
 * @ch: ascii अक्षरacter represents hex digit
 *
 * hex_to_bin() converts one hex digit to its actual value or -1 in हाल of bad
 * input.
 */
पूर्णांक hex_to_bin(अक्षर ch)
अणु
	अगर ((ch >= '0') && (ch <= '9'))
		वापस ch - '0';
	ch = छोटे(ch);
	अगर ((ch >= 'a') && (ch <= 'f'))
		वापस ch - 'a' + 10;
	वापस -1;
पूर्ण
EXPORT_SYMBOL(hex_to_bin);

/**
 * hex2bin - convert an ascii hexadecimal string to its binary representation
 * @dst: binary result
 * @src: ascii hexadecimal string
 * @count: result length
 *
 * Return 0 on success, -EINVAL in हाल of bad input.
 */
पूर्णांक hex2bin(u8 *dst, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	जबतक (count--) अणु
		पूर्णांक hi = hex_to_bin(*src++);
		पूर्णांक lo = hex_to_bin(*src++);

		अगर ((hi < 0) || (lo < 0))
			वापस -EINVAL;

		*dst++ = (hi << 4) | lo;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(hex2bin);

/**
 * bin2hex - convert binary data to an ascii hexadecimal string
 * @dst: ascii hexadecimal result
 * @src: binary data
 * @count: binary data length
 */
अक्षर *bin2hex(अक्षर *dst, स्थिर व्योम *src, माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *_src = src;

	जबतक (count--)
		dst = hex_byte_pack(dst, *_src++);
	वापस dst;
पूर्ण
EXPORT_SYMBOL(bin2hex);

/**
 * hex_dump_to_buffer - convert a blob of data to "hex ASCII" in memory
 * @buf: data blob to dump
 * @len: number of bytes in the @buf
 * @rowsize: number of bytes to prपूर्णांक per line; must be 16 or 32
 * @groupsize: number of bytes to prपूर्णांक at a समय (1, 2, 4, 8; शेष = 1)
 * @linebuf: where to put the converted data
 * @linebuflen: total size of @linebuf, including space क्रम terminating NUL
 * @ascii: include ASCII after the hex output
 *
 * hex_dump_to_buffer() works on one "line" of output at a समय, i.e.,
 * 16 or 32 bytes of input data converted to hex + ASCII output.
 *
 * Given a buffer of u8 data, hex_dump_to_buffer() converts the input data
 * to a hex + ASCII dump at the supplied memory location.
 * The converted output is always NUL-terminated.
 *
 * E.g.:
 *   hex_dump_to_buffer(frame->data, frame->len, 16, 1,
 *			linebuf, माप(linebuf), true);
 *
 * example output buffer:
 * 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f  @ABCDEFGHIJKLMNO
 *
 * Return:
 * The amount of bytes placed in the buffer without terminating NUL. If the
 * output was truncated, then the वापस value is the number of bytes
 * (excluding the terminating NUL) which would have been written to the final
 * string अगर enough space had been available.
 */
पूर्णांक hex_dump_to_buffer(स्थिर व्योम *buf, माप_प्रकार len, पूर्णांक rowsize, पूर्णांक groupsize,
		       अक्षर *linebuf, माप_प्रकार linebuflen, bool ascii)
अणु
	स्थिर u8 *ptr = buf;
	पूर्णांक ngroups;
	u8 ch;
	पूर्णांक j, lx = 0;
	पूर्णांक ascii_column;
	पूर्णांक ret;

	अगर (rowsize != 16 && rowsize != 32)
		rowsize = 16;

	अगर (len > rowsize)		/* limit to one line at a समय */
		len = rowsize;
	अगर (!is_घातer_of_2(groupsize) || groupsize > 8)
		groupsize = 1;
	अगर ((len % groupsize) != 0)	/* no mixed size output */
		groupsize = 1;

	ngroups = len / groupsize;
	ascii_column = rowsize * 2 + rowsize / groupsize + 1;

	अगर (!linebuflen)
		जाओ overflow1;

	अगर (!len)
		जाओ nil;

	अगर (groupsize == 8) अणु
		स्थिर u64 *ptr8 = buf;

		क्रम (j = 0; j < ngroups; j++) अणु
			ret = snम_लिखो(linebuf + lx, linebuflen - lx,
				       "%s%16.16llx", j ? " " : "",
				       get_unaligned(ptr8 + j));
			अगर (ret >= linebuflen - lx)
				जाओ overflow1;
			lx += ret;
		पूर्ण
	पूर्ण अन्यथा अगर (groupsize == 4) अणु
		स्थिर u32 *ptr4 = buf;

		क्रम (j = 0; j < ngroups; j++) अणु
			ret = snम_लिखो(linebuf + lx, linebuflen - lx,
				       "%s%8.8x", j ? " " : "",
				       get_unaligned(ptr4 + j));
			अगर (ret >= linebuflen - lx)
				जाओ overflow1;
			lx += ret;
		पूर्ण
	पूर्ण अन्यथा अगर (groupsize == 2) अणु
		स्थिर u16 *ptr2 = buf;

		क्रम (j = 0; j < ngroups; j++) अणु
			ret = snम_लिखो(linebuf + lx, linebuflen - lx,
				       "%s%4.4x", j ? " " : "",
				       get_unaligned(ptr2 + j));
			अगर (ret >= linebuflen - lx)
				जाओ overflow1;
			lx += ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (j = 0; j < len; j++) अणु
			अगर (linebuflen < lx + 2)
				जाओ overflow2;
			ch = ptr[j];
			linebuf[lx++] = hex_asc_hi(ch);
			अगर (linebuflen < lx + 2)
				जाओ overflow2;
			linebuf[lx++] = hex_asc_lo(ch);
			अगर (linebuflen < lx + 2)
				जाओ overflow2;
			linebuf[lx++] = ' ';
		पूर्ण
		अगर (j)
			lx--;
	पूर्ण
	अगर (!ascii)
		जाओ nil;

	जबतक (lx < ascii_column) अणु
		अगर (linebuflen < lx + 2)
			जाओ overflow2;
		linebuf[lx++] = ' ';
	पूर्ण
	क्रम (j = 0; j < len; j++) अणु
		अगर (linebuflen < lx + 2)
			जाओ overflow2;
		ch = ptr[j];
		linebuf[lx++] = (isascii(ch) && है_छाप(ch)) ? ch : '.';
	पूर्ण
nil:
	linebuf[lx] = '\0';
	वापस lx;
overflow2:
	linebuf[lx++] = '\0';
overflow1:
	वापस ascii ? ascii_column + len : (groupsize * 2 + 1) * ngroups - 1;
पूर्ण
EXPORT_SYMBOL(hex_dump_to_buffer);

#अगर_घोषित CONFIG_PRINTK
/**
 * prपूर्णांक_hex_dump - prपूर्णांक a text hex dump to syslog क्रम a binary blob of data
 * @level: kernel log level (e.g. KERN_DEBUG)
 * @prefix_str: string to prefix each line with;
 *  caller supplies trailing spaces क्रम alignment अगर desired
 * @prefix_type: controls whether prefix of an offset, address, or none
 *  is prपूर्णांकed (%DUMP_PREFIX_OFFSET, %DUMP_PREFIX_ADDRESS, %DUMP_PREFIX_NONE)
 * @rowsize: number of bytes to prपूर्णांक per line; must be 16 or 32
 * @groupsize: number of bytes to prपूर्णांक at a समय (1, 2, 4, 8; शेष = 1)
 * @buf: data blob to dump
 * @len: number of bytes in the @buf
 * @ascii: include ASCII after the hex output
 *
 * Given a buffer of u8 data, prपूर्णांक_hex_dump() prपूर्णांकs a hex + ASCII dump
 * to the kernel log at the specअगरied kernel log level, with an optional
 * leading prefix.
 *
 * prपूर्णांक_hex_dump() works on one "line" of output at a समय, i.e.,
 * 16 or 32 bytes of input data converted to hex + ASCII output.
 * prपूर्णांक_hex_dump() iterates over the entire input @buf, अवरोधing it पूर्णांकo
 * "line size" chunks to क्रमmat and prपूर्णांक.
 *
 * E.g.:
 *   prपूर्णांक_hex_dump(KERN_DEBUG, "raw data: ", DUMP_PREFIX_ADDRESS,
 *		    16, 1, frame->data, frame->len, true);
 *
 * Example output using %DUMP_PREFIX_OFFSET and 1-byte mode:
 * 0009ab42: 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f  @ABCDEFGHIJKLMNO
 * Example output using %DUMP_PREFIX_ADDRESS and 4-byte mode:
 * ffffffff88089af0: 73727170 77767574 7b7a7978 7f7e7d7c  pqrstuvwxyzअणु|पूर्ण~.
 */
व्योम prपूर्णांक_hex_dump(स्थिर अक्षर *level, स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
		    पूर्णांक rowsize, पूर्णांक groupsize,
		    स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
	स्थिर u8 *ptr = buf;
	पूर्णांक i, linelen, reमुख्यing = len;
	अचिन्हित अक्षर linebuf[32 * 3 + 2 + 32 + 1];

	अगर (rowsize != 16 && rowsize != 32)
		rowsize = 16;

	क्रम (i = 0; i < len; i += rowsize) अणु
		linelen = min(reमुख्यing, rowsize);
		reमुख्यing -= rowsize;

		hex_dump_to_buffer(ptr + i, linelen, rowsize, groupsize,
				   linebuf, माप(linebuf), ascii);

		चयन (prefix_type) अणु
		हाल DUMP_PREFIX_ADDRESS:
			prपूर्णांकk("%s%s%p: %s\n",
			       level, prefix_str, ptr + i, linebuf);
			अवरोध;
		हाल DUMP_PREFIX_OFFSET:
			prपूर्णांकk("%s%s%.8x: %s\n", level, prefix_str, i, linebuf);
			अवरोध;
		शेष:
			prपूर्णांकk("%s%s%s\n", level, prefix_str, linebuf);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(prपूर्णांक_hex_dump);

#पूर्ण_अगर /* defined(CONFIG_PRINTK) */

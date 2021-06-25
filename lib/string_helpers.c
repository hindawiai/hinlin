<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Helpers क्रम क्रमmatting and prपूर्णांकing strings
 *
 * Copyright 31 August 2008 James Bottomley
 * Copyright (C) 2013, Intel Corporation
 */
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/export.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/string_helpers.h>

/**
 * string_get_size - get the size in the specअगरied units
 * @size:	The size to be converted in blocks
 * @blk_size:	Size of the block (use 1 क्रम size in bytes)
 * @units:	units to use (घातers of 1000 or 1024)
 * @buf:	buffer to क्रमmat to
 * @len:	length of buffer
 *
 * This function वापसs a string क्रमmatted to 3 signअगरicant figures
 * giving the size in the required units.  @buf should have room क्रम
 * at least 9 bytes and will always be zero terminated.
 *
 */
व्योम string_get_size(u64 size, u64 blk_size, स्थिर क्रमागत string_size_units units,
		     अक्षर *buf, पूर्णांक len)
अणु
	अटल स्थिर अक्षर *स्थिर units_10[] = अणु
		"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर units_2[] = अणु
		"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर *स्थिर units_str[] = अणु
		[STRING_UNITS_10] = units_10,
		[STRING_UNITS_2] = units_2,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक भागisor[] = अणु
		[STRING_UNITS_10] = 1000,
		[STRING_UNITS_2] = 1024,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक rounding[] = अणु 500, 50, 5 पूर्ण;
	पूर्णांक i = 0, j;
	u32 reमुख्यder = 0, sf_cap;
	अक्षर पंचांगp[8];
	स्थिर अक्षर *unit;

	पंचांगp[0] = '\0';

	अगर (blk_size == 0)
		size = 0;
	अगर (size == 0)
		जाओ out;

	/* This is Napier's algorithm.  Reduce the original block size to
	 *
	 * coefficient * भागisor[units]^i
	 *
	 * we करो the reduction so both coefficients are just under 32 bits so
	 * that multiplying them together won't overflow 64 bits and we keep
	 * as much precision as possible in the numbers.
	 *
	 * Note: it's safe to throw away the reमुख्यders here because all the
	 * precision is in the coefficients.
	 */
	जबतक (blk_size >> 32) अणु
		करो_भाग(blk_size, भागisor[units]);
		i++;
	पूर्ण

	जबतक (size >> 32) अणु
		करो_भाग(size, भागisor[units]);
		i++;
	पूर्ण

	/* now perक्रमm the actual multiplication keeping i as the sum of the
	 * two logarithms */
	size *= blk_size;

	/* and logarithmically reduce it until it's just under the भागisor */
	जबतक (size >= भागisor[units]) अणु
		reमुख्यder = करो_भाग(size, भागisor[units]);
		i++;
	पूर्ण

	/* work out in j how many digits of precision we need from the
	 * reमुख्यder */
	sf_cap = size;
	क्रम (j = 0; sf_cap*10 < 1000; j++)
		sf_cap *= 10;

	अगर (units == STRING_UNITS_2) अणु
		/* express the reमुख्यder as a decimal.  It's currently the
		 * numerator of a fraction whose denominator is
		 * भागisor[units], which is 1 << 10 क्रम STRING_UNITS_2 */
		reमुख्यder *= 1000;
		reमुख्यder >>= 10;
	पूर्ण

	/* add a 5 to the digit below what will be prपूर्णांकed to ensure
	 * an arithmetical round up and carry it through to size */
	reमुख्यder += rounding[j];
	अगर (reमुख्यder >= 1000) अणु
		reमुख्यder -= 1000;
		size += 1;
	पूर्ण

	अगर (j) अणु
		snम_लिखो(पंचांगp, माप(पंचांगp), ".%03u", reमुख्यder);
		पंचांगp[j+1] = '\0';
	पूर्ण

 out:
	अगर (i >= ARRAY_SIZE(units_2))
		unit = "UNK";
	अन्यथा
		unit = units_str[units][i];

	snम_लिखो(buf, len, "%u%s %s", (u32)size,
		 पंचांगp, unit);
पूर्ण
EXPORT_SYMBOL(string_get_size);

अटल bool unescape_space(अक्षर **src, अक्षर **dst)
अणु
	अक्षर *p = *dst, *q = *src;

	चयन (*q) अणु
	हाल 'n':
		*p = '\n';
		अवरोध;
	हाल 'r':
		*p = '\r';
		अवरोध;
	हाल 't':
		*p = '\t';
		अवरोध;
	हाल 'v':
		*p = '\v';
		अवरोध;
	हाल 'f':
		*p = '\f';
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	*dst += 1;
	*src += 1;
	वापस true;
पूर्ण

अटल bool unescape_octal(अक्षर **src, अक्षर **dst)
अणु
	अक्षर *p = *dst, *q = *src;
	u8 num;

	अगर (है_अष्टक(*q) == 0)
		वापस false;

	num = (*q++) & 7;
	जबतक (num < 32 && है_अष्टक(*q) && (q - *src < 3)) अणु
		num <<= 3;
		num += (*q++) & 7;
	पूर्ण
	*p = num;
	*dst += 1;
	*src = q;
	वापस true;
पूर्ण

अटल bool unescape_hex(अक्षर **src, अक्षर **dst)
अणु
	अक्षर *p = *dst, *q = *src;
	पूर्णांक digit;
	u8 num;

	अगर (*q++ != 'x')
		वापस false;

	num = digit = hex_to_bin(*q++);
	अगर (digit < 0)
		वापस false;

	digit = hex_to_bin(*q);
	अगर (digit >= 0) अणु
		q++;
		num = (num << 4) | digit;
	पूर्ण
	*p = num;
	*dst += 1;
	*src = q;
	वापस true;
पूर्ण

अटल bool unescape_special(अक्षर **src, अक्षर **dst)
अणु
	अक्षर *p = *dst, *q = *src;

	चयन (*q) अणु
	हाल '\"':
		*p = '\"';
		अवरोध;
	हाल '\\':
		*p = '\\';
		अवरोध;
	हाल 'a':
		*p = '\a';
		अवरोध;
	हाल 'e':
		*p = '\e';
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	*dst += 1;
	*src += 1;
	वापस true;
पूर्ण

/**
 * string_unescape - unquote अक्षरacters in the given string
 * @src:	source buffer (escaped)
 * @dst:	destination buffer (unescaped)
 * @size:	size of the destination buffer (0 to unlimit)
 * @flags:	combination of the flags.
 *
 * Description:
 * The function unquotes अक्षरacters in the given string.
 *
 * Because the size of the output will be the same as or less than the size of
 * the input, the transक्रमmation may be perक्रमmed in place.
 *
 * Caller must provide valid source and destination poपूर्णांकers. Be aware that
 * destination buffer will always be शून्य-terminated. Source string must be
 * शून्य-terminated as well.  The supported flags are::
 *
 *	UNESCAPE_SPACE:
 *		'\f' - क्रमm feed
 *		'\n' - new line
 *		'\r' - carriage वापस
 *		'\t' - horizontal tab
 *		'\v' - vertical tab
 *	UNESCAPE_OCTAL:
 *		'\NNN' - byte with octal value NNN (1 to 3 digits)
 *	UNESCAPE_HEX:
 *		'\xHH' - byte with hexadecimal value HH (1 to 2 digits)
 *	UNESCAPE_SPECIAL:
 *		'\"' - द्विगुन quote
 *		'\\' - backslash
 *		'\a' - alert (BEL)
 *		'\e' - escape
 *	UNESCAPE_ANY:
 *		all previous together
 *
 * Return:
 * The amount of the अक्षरacters processed to the destination buffer excluding
 * trailing '\0' is वापसed.
 */
पूर्णांक string_unescape(अक्षर *src, अक्षर *dst, माप_प्रकार size, अचिन्हित पूर्णांक flags)
अणु
	अक्षर *out = dst;

	जबतक (*src && --size) अणु
		अगर (src[0] == '\\' && src[1] != '\0' && size > 1) अणु
			src++;
			size--;

			अगर (flags & UNESCAPE_SPACE &&
					unescape_space(&src, &out))
				जारी;

			अगर (flags & UNESCAPE_OCTAL &&
					unescape_octal(&src, &out))
				जारी;

			अगर (flags & UNESCAPE_HEX &&
					unescape_hex(&src, &out))
				जारी;

			अगर (flags & UNESCAPE_SPECIAL &&
					unescape_special(&src, &out))
				जारी;

			*out++ = '\\';
		पूर्ण
		*out++ = *src++;
	पूर्ण
	*out = '\0';

	वापस out - dst;
पूर्ण
EXPORT_SYMBOL(string_unescape);

अटल bool escape_passthrough(अचिन्हित अक्षर c, अक्षर **dst, अक्षर *end)
अणु
	अक्षर *out = *dst;

	अगर (out < end)
		*out = c;
	*dst = out + 1;
	वापस true;
पूर्ण

अटल bool escape_space(अचिन्हित अक्षर c, अक्षर **dst, अक्षर *end)
अणु
	अक्षर *out = *dst;
	अचिन्हित अक्षर to;

	चयन (c) अणु
	हाल '\n':
		to = 'n';
		अवरोध;
	हाल '\r':
		to = 'r';
		अवरोध;
	हाल '\t':
		to = 't';
		अवरोध;
	हाल '\v':
		to = 'v';
		अवरोध;
	हाल '\f':
		to = 'f';
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (out < end)
		*out = '\\';
	++out;
	अगर (out < end)
		*out = to;
	++out;

	*dst = out;
	वापस true;
पूर्ण

अटल bool escape_special(अचिन्हित अक्षर c, अक्षर **dst, अक्षर *end)
अणु
	अक्षर *out = *dst;
	अचिन्हित अक्षर to;

	चयन (c) अणु
	हाल '\\':
		to = '\\';
		अवरोध;
	हाल '\a':
		to = 'a';
		अवरोध;
	हाल '\e':
		to = 'e';
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (out < end)
		*out = '\\';
	++out;
	अगर (out < end)
		*out = to;
	++out;

	*dst = out;
	वापस true;
पूर्ण

अटल bool escape_null(अचिन्हित अक्षर c, अक्षर **dst, अक्षर *end)
अणु
	अक्षर *out = *dst;

	अगर (c)
		वापस false;

	अगर (out < end)
		*out = '\\';
	++out;
	अगर (out < end)
		*out = '0';
	++out;

	*dst = out;
	वापस true;
पूर्ण

अटल bool escape_octal(अचिन्हित अक्षर c, अक्षर **dst, अक्षर *end)
अणु
	अक्षर *out = *dst;

	अगर (out < end)
		*out = '\\';
	++out;
	अगर (out < end)
		*out = ((c >> 6) & 0x07) + '0';
	++out;
	अगर (out < end)
		*out = ((c >> 3) & 0x07) + '0';
	++out;
	अगर (out < end)
		*out = ((c >> 0) & 0x07) + '0';
	++out;

	*dst = out;
	वापस true;
पूर्ण

अटल bool escape_hex(अचिन्हित अक्षर c, अक्षर **dst, अक्षर *end)
अणु
	अक्षर *out = *dst;

	अगर (out < end)
		*out = '\\';
	++out;
	अगर (out < end)
		*out = 'x';
	++out;
	अगर (out < end)
		*out = hex_asc_hi(c);
	++out;
	अगर (out < end)
		*out = hex_asc_lo(c);
	++out;

	*dst = out;
	वापस true;
पूर्ण

/**
 * string_escape_mem - quote अक्षरacters in the given memory buffer
 * @src:	source buffer (unescaped)
 * @isz:	source buffer size
 * @dst:	destination buffer (escaped)
 * @osz:	destination buffer size
 * @flags:	combination of the flags
 * @only:	शून्य-terminated string containing अक्षरacters used to limit
 *		the selected escape class. If अक्षरacters are included in @only
 *		that would not normally be escaped by the classes selected
 *		in @flags, they will be copied to @dst unescaped.
 *
 * Description:
 * The process of escaping byte buffer includes several parts. They are applied
 * in the following sequence.
 *
 *	1. The अक्षरacter is matched to the prपूर्णांकable class, अगर asked, and in
 *	   हाल of match it passes through to the output.
 *	2. The अक्षरacter is not matched to the one from @only string and thus
 *	   must go as-is to the output.
 *	3. The अक्षरacter is checked अगर it falls पूर्णांकo the class given by @flags.
 *	   %ESCAPE_OCTAL and %ESCAPE_HEX are going last since they cover any
 *	   अक्षरacter. Note that they actually can't go together, otherwise
 *	   %ESCAPE_HEX will be ignored.
 *
 * Caller must provide valid source and destination poपूर्णांकers. Be aware that
 * destination buffer will not be शून्य-terminated, thus caller have to append
 * it अगर needs.   The supported flags are::
 *
 *	%ESCAPE_SPACE: (special white space, not space itself)
 *		'\f' - क्रमm feed
 *		'\n' - new line
 *		'\r' - carriage वापस
 *		'\t' - horizontal tab
 *		'\v' - vertical tab
 *	%ESCAPE_SPECIAL:
 *		'\\' - backslash
 *		'\a' - alert (BEL)
 *		'\e' - escape
 *	%ESCAPE_शून्य:
 *		'\0' - null
 *	%ESCAPE_OCTAL:
 *		'\NNN' - byte with octal value NNN (3 digits)
 *	%ESCAPE_ANY:
 *		all previous together
 *	%ESCAPE_NP:
 *		escape only non-prपूर्णांकable अक्षरacters (checked by है_छाप)
 *	%ESCAPE_ANY_NP:
 *		all previous together
 *	%ESCAPE_HEX:
 *		'\xHH' - byte with hexadecimal value HH (2 digits)
 *
 * Return:
 * The total size of the escaped output that would be generated क्रम
 * the given input and flags. To check whether the output was
 * truncated, compare the वापस value to osz. There is room left in
 * dst क्रम a '\0' terminator अगर and only अगर ret < osz.
 */
पूर्णांक string_escape_mem(स्थिर अक्षर *src, माप_प्रकार isz, अक्षर *dst, माप_प्रकार osz,
		      अचिन्हित पूर्णांक flags, स्थिर अक्षर *only)
अणु
	अक्षर *p = dst;
	अक्षर *end = p + osz;
	bool is_dict = only && *only;

	जबतक (isz--) अणु
		अचिन्हित अक्षर c = *src++;

		/*
		 * Apply rules in the following sequence:
		 *	- the अक्षरacter is prपूर्णांकable, when @flags has
		 *	  %ESCAPE_NP bit set
		 *	- the @only string is supplied and करोes not contain a
		 *	  अक्षरacter under question
		 *	- the अक्षरacter करोesn't fall पूर्णांकo a class of symbols
		 *	  defined by given @flags
		 * In these हालs we just pass through a अक्षरacter to the
		 * output buffer.
		 */
		अगर ((flags & ESCAPE_NP && है_छाप(c)) ||
		    (is_dict && !म_अक्षर(only, c))) अणु
			/* करो nothing */
		पूर्ण अन्यथा अणु
			अगर (flags & ESCAPE_SPACE && escape_space(c, &p, end))
				जारी;

			अगर (flags & ESCAPE_SPECIAL && escape_special(c, &p, end))
				जारी;

			अगर (flags & ESCAPE_शून्य && escape_null(c, &p, end))
				जारी;

			/* ESCAPE_OCTAL and ESCAPE_HEX always go last */
			अगर (flags & ESCAPE_OCTAL && escape_octal(c, &p, end))
				जारी;

			अगर (flags & ESCAPE_HEX && escape_hex(c, &p, end))
				जारी;
		पूर्ण

		escape_passthrough(c, &p, end);
	पूर्ण

	वापस p - dst;
पूर्ण
EXPORT_SYMBOL(string_escape_mem);

पूर्णांक string_escape_mem_ascii(स्थिर अक्षर *src, माप_प्रकार isz, अक्षर *dst,
					माप_प्रकार osz)
अणु
	अक्षर *p = dst;
	अक्षर *end = p + osz;

	जबतक (isz--) अणु
		अचिन्हित अक्षर c = *src++;

		अगर (!है_छाप(c) || !isascii(c) || c == '"' || c == '\\')
			escape_hex(c, &p, end);
		अन्यथा
			escape_passthrough(c, &p, end);
	पूर्ण

	वापस p - dst;
पूर्ण
EXPORT_SYMBOL(string_escape_mem_ascii);

/*
 * Return an allocated string that has been escaped of special अक्षरacters
 * and द्विगुन quotes, making it safe to log in quotes.
 */
अक्षर *kstrdup_quotable(स्थिर अक्षर *src, gfp_t gfp)
अणु
	माप_प्रकार slen, dlen;
	अक्षर *dst;
	स्थिर पूर्णांक flags = ESCAPE_HEX;
	स्थिर अक्षर esc[] = "\f\n\r\t\v\a\e\\\"";

	अगर (!src)
		वापस शून्य;
	slen = म_माप(src);

	dlen = string_escape_mem(src, slen, शून्य, 0, flags, esc);
	dst = kदो_स्मृति(dlen + 1, gfp);
	अगर (!dst)
		वापस शून्य;

	WARN_ON(string_escape_mem(src, slen, dst, dlen, flags, esc) != dlen);
	dst[dlen] = '\0';

	वापस dst;
पूर्ण
EXPORT_SYMBOL_GPL(kstrdup_quotable);

/*
 * Returns allocated शून्य-terminated string containing process
 * command line, with पूर्णांकer-argument शून्यs replaced with spaces,
 * and other special अक्षरacters escaped.
 */
अक्षर *kstrdup_quotable_cmdline(काष्ठा task_काष्ठा *task, gfp_t gfp)
अणु
	अक्षर *buffer, *quoted;
	पूर्णांक i, res;

	buffer = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buffer)
		वापस शून्य;

	res = get_cmdline(task, buffer, PAGE_SIZE - 1);
	buffer[res] = '\0';

	/* Collapse trailing शून्यs, leave res poपूर्णांकing to last non-शून्य. */
	जबतक (--res >= 0 && buffer[res] == '\0')
		;

	/* Replace पूर्णांकer-argument शून्यs. */
	क्रम (i = 0; i <= res; i++)
		अगर (buffer[i] == '\0')
			buffer[i] = ' ';

	/* Make sure result is prपूर्णांकable. */
	quoted = kstrdup_quotable(buffer, gfp);
	kमुक्त(buffer);
	वापस quoted;
पूर्ण
EXPORT_SYMBOL_GPL(kstrdup_quotable_cmdline);

/*
 * Returns allocated शून्य-terminated string containing pathname,
 * with special अक्षरacters escaped, able to be safely logged. If
 * there is an error, the leading अक्षरacter will be "<".
 */
अक्षर *kstrdup_quotable_file(काष्ठा file *file, gfp_t gfp)
अणु
	अक्षर *temp, *pathname;

	अगर (!file)
		वापस kstrdup("<unknown>", gfp);

	/* We add 11 spaces क्रम ' (deleted)' to be appended */
	temp = kदो_स्मृति(PATH_MAX + 11, GFP_KERNEL);
	अगर (!temp)
		वापस kstrdup("<no_memory>", gfp);

	pathname = file_path(file, temp, PATH_MAX + 11);
	अगर (IS_ERR(pathname))
		pathname = kstrdup("<too_long>", gfp);
	अन्यथा
		pathname = kstrdup_quotable(pathname, gfp);

	kमुक्त(temp);
	वापस pathname;
पूर्ण
EXPORT_SYMBOL_GPL(kstrdup_quotable_file);

/**
 * kमुक्त_strarray - मुक्त a number of dynamically allocated strings contained
 *                  in an array and the array itself
 *
 * @array: Dynamically allocated array of strings to मुक्त.
 * @n: Number of strings (starting from the beginning of the array) to मुक्त.
 *
 * Passing a non-शून्य @array and @n == 0 as well as शून्य @array are valid
 * use-हालs. If @array is शून्य, the function करोes nothing.
 */
व्योम kमुक्त_strarray(अक्षर **array, माप_प्रकार n)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!array)
		वापस;

	क्रम (i = 0; i < n; i++)
		kमुक्त(array[i]);
	kमुक्त(array);
पूर्ण
EXPORT_SYMBOL_GPL(kमुक्त_strarray);

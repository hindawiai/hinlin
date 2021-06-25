<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * seq_buf.c
 *
 * Copyright (C) 2014 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 * The seq_buf is a handy tool that allows you to pass a descriptor around
 * to a buffer that other functions can ग_लिखो to. It is similar to the
 * seq_file functionality but has some dअगरferences.
 *
 * To use it, the seq_buf must be initialized with seq_buf_init().
 * This will set up the counters within the descriptor. You can call
 * seq_buf_init() more than once to reset the seq_buf to start
 * from scratch.
 */
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/seq_buf.h>

/**
 * seq_buf_can_fit - can the new data fit in the current buffer?
 * @s: the seq_buf descriptor
 * @len: The length to see अगर it can fit in the current buffer
 *
 * Returns true अगर there's enough unused space in the seq_buf buffer
 * to fit the amount of new data according to @len.
 */
अटल bool seq_buf_can_fit(काष्ठा seq_buf *s, माप_प्रकार len)
अणु
	वापस s->len + len <= s->size;
पूर्ण

/**
 * seq_buf_prपूर्णांक_seq - move the contents of seq_buf पूर्णांकo a seq_file
 * @m: the seq_file descriptor that is the destination
 * @s: the seq_buf descriptor that is the source.
 *
 * Returns zero on success, non zero otherwise
 */
पूर्णांक seq_buf_prपूर्णांक_seq(काष्ठा seq_file *m, काष्ठा seq_buf *s)
अणु
	अचिन्हित पूर्णांक len = seq_buf_used(s);

	वापस seq_ग_लिखो(m, s->buffer, len);
पूर्ण

/**
 * seq_buf_भ_लिखो - sequence prपूर्णांकing of inक्रमmation.
 * @s: seq_buf descriptor
 * @fmt: म_लिखो क्रमmat string
 * @args: बहु_सूची of arguments from a म_लिखो() type function
 *
 * Writes a vnम_लिखो() क्रमmat पूर्णांकo the sequencce buffer.
 *
 * Returns zero on success, -1 on overflow.
 */
पूर्णांक seq_buf_भ_लिखो(काष्ठा seq_buf *s, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक len;

	WARN_ON(s->size == 0);

	अगर (s->len < s->size) अणु
		len = vsnम_लिखो(s->buffer + s->len, s->size - s->len, fmt, args);
		अगर (s->len + len < s->size) अणु
			s->len += len;
			वापस 0;
		पूर्ण
	पूर्ण
	seq_buf_set_overflow(s);
	वापस -1;
पूर्ण

/**
 * seq_buf_म_लिखो - sequence prपूर्णांकing of inक्रमmation
 * @s: seq_buf descriptor
 * @fmt: म_लिखो क्रमmat string
 *
 * Writes a म_लिखो() क्रमmat पूर्णांकo the sequence buffer.
 *
 * Returns zero on success, -1 on overflow.
 */
पूर्णांक seq_buf_म_लिखो(काष्ठा seq_buf *s, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	बहु_शुरू(ap, fmt);
	ret = seq_buf_भ_लिखो(s, fmt, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(seq_buf_म_लिखो);

#अगर_घोषित CONFIG_BINARY_PRINTF
/**
 * seq_buf_bम_लिखो - Write the म_लिखो string from binary arguments
 * @s: seq_buf descriptor
 * @fmt: The क्रमmat string क्रम the @binary arguments
 * @binary: The binary arguments क्रम @fmt.
 *
 * When recording in a fast path, a म_लिखो may be recorded with just
 * saving the क्रमmat and the arguments as they were passed to the
 * function, instead of wasting cycles converting the arguments पूर्णांकo
 * ASCII अक्षरacters. Instead, the arguments are saved in a 32 bit
 * word array that is defined by the क्रमmat string स्थिरraपूर्णांकs.
 *
 * This function will take the क्रमmat and the binary array and finish
 * the conversion पूर्णांकo the ASCII string within the buffer.
 *
 * Returns zero on success, -1 on overflow.
 */
पूर्णांक seq_buf_bम_लिखो(काष्ठा seq_buf *s, स्थिर अक्षर *fmt, स्थिर u32 *binary)
अणु
	अचिन्हित पूर्णांक len = seq_buf_buffer_left(s);
	पूर्णांक ret;

	WARN_ON(s->size == 0);

	अगर (s->len < s->size) अणु
		ret = bstr_म_लिखो(s->buffer + s->len, len, fmt, binary);
		अगर (s->len + ret < s->size) अणु
			s->len += ret;
			वापस 0;
		पूर्ण
	पूर्ण
	seq_buf_set_overflow(s);
	वापस -1;
पूर्ण
#पूर्ण_अगर /* CONFIG_BINARY_PRINTF */

/**
 * seq_buf_माला_दो - sequence prपूर्णांकing of simple string
 * @s: seq_buf descriptor
 * @str: simple string to record
 *
 * Copy a simple string पूर्णांकo the sequence buffer.
 *
 * Returns zero on success, -1 on overflow
 */
पूर्णांक seq_buf_माला_दो(काष्ठा seq_buf *s, स्थिर अक्षर *str)
अणु
	माप_प्रकार len = म_माप(str);

	WARN_ON(s->size == 0);

	/* Add 1 to len क्रम the trailing null byte which must be there */
	len += 1;

	अगर (seq_buf_can_fit(s, len)) अणु
		स_नकल(s->buffer + s->len, str, len);
		/* Don't count the trailing null byte against the capacity */
		s->len += len - 1;
		वापस 0;
	पूर्ण
	seq_buf_set_overflow(s);
	वापस -1;
पूर्ण

/**
 * seq_buf_अ_दो - sequence prपूर्णांकing of simple अक्षरacter
 * @s: seq_buf descriptor
 * @c: simple अक्षरacter to record
 *
 * Copy a single अक्षरacter पूर्णांकo the sequence buffer.
 *
 * Returns zero on success, -1 on overflow
 */
पूर्णांक seq_buf_अ_दो(काष्ठा seq_buf *s, अचिन्हित अक्षर c)
अणु
	WARN_ON(s->size == 0);

	अगर (seq_buf_can_fit(s, 1)) अणु
		s->buffer[s->len++] = c;
		वापस 0;
	पूर्ण
	seq_buf_set_overflow(s);
	वापस -1;
पूर्ण

/**
 * seq_buf_puपंचांगem - ग_लिखो raw data पूर्णांकo the sequenc buffer
 * @s: seq_buf descriptor
 * @mem: The raw memory to copy पूर्णांकo the buffer
 * @len: The length of the raw memory to copy (in bytes)
 *
 * There may be हालs where raw memory needs to be written पूर्णांकo the
 * buffer and a म_नकल() would not work. Using this function allows
 * क्रम such हालs.
 *
 * Returns zero on success, -1 on overflow
 */
पूर्णांक seq_buf_puपंचांगem(काष्ठा seq_buf *s, स्थिर व्योम *mem, अचिन्हित पूर्णांक len)
अणु
	WARN_ON(s->size == 0);

	अगर (seq_buf_can_fit(s, len)) अणु
		स_नकल(s->buffer + s->len, mem, len);
		s->len += len;
		वापस 0;
	पूर्ण
	seq_buf_set_overflow(s);
	वापस -1;
पूर्ण

#घोषणा MAX_MEMHEX_BYTES	8U
#घोषणा HEX_CHARS		(MAX_MEMHEX_BYTES*2 + 1)

/**
 * seq_buf_puपंचांगem_hex - ग_लिखो raw memory पूर्णांकo the buffer in ASCII hex
 * @s: seq_buf descriptor
 * @mem: The raw memory to ग_लिखो its hex ASCII representation of
 * @len: The length of the raw memory to copy (in bytes)
 *
 * This is similar to seq_buf_puपंचांगem() except instead of just copying the
 * raw memory पूर्णांकo the buffer it ग_लिखोs its ASCII representation of it
 * in hex अक्षरacters.
 *
 * Returns zero on success, -1 on overflow
 */
पूर्णांक seq_buf_puपंचांगem_hex(काष्ठा seq_buf *s, स्थिर व्योम *mem,
		       अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर hex[HEX_CHARS];
	स्थिर अचिन्हित अक्षर *data = mem;
	अचिन्हित पूर्णांक start_len;
	पूर्णांक i, j;

	WARN_ON(s->size == 0);

	जबतक (len) अणु
		start_len = min(len, HEX_CHARS - 1);
#अगर_घोषित __BIG_ENDIAN
		क्रम (i = 0, j = 0; i < start_len; i++) अणु
#अन्यथा
		क्रम (i = start_len-1, j = 0; i >= 0; i--) अणु
#पूर्ण_अगर
			hex[j++] = hex_asc_hi(data[i]);
			hex[j++] = hex_asc_lo(data[i]);
		पूर्ण
		अगर (WARN_ON_ONCE(j == 0 || j/2 > len))
			अवरोध;

		/* j increments twice per loop */
		len -= j / 2;
		hex[j++] = ' ';

		seq_buf_puपंचांगem(s, hex, j);
		अगर (seq_buf_has_overflowed(s))
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * seq_buf_path - copy a path पूर्णांकo the sequence buffer
 * @s: seq_buf descriptor
 * @path: path to ग_लिखो पूर्णांकo the sequence buffer.
 * @esc: set of अक्षरacters to escape in the output
 *
 * Write a path name पूर्णांकo the sequence buffer.
 *
 * Returns the number of written bytes on success, -1 on overflow
 */
पूर्णांक seq_buf_path(काष्ठा seq_buf *s, स्थिर काष्ठा path *path, स्थिर अक्षर *esc)
अणु
	अक्षर *buf;
	माप_प्रकार size = seq_buf_get_buf(s, &buf);
	पूर्णांक res = -1;

	WARN_ON(s->size == 0);

	अगर (size) अणु
		अक्षर *p = d_path(path, buf, size);
		अगर (!IS_ERR(p)) अणु
			अक्षर *end = mangle_path(buf, p, esc);
			अगर (end)
				res = end - buf;
		पूर्ण
	पूर्ण
	seq_buf_commit(s, res);

	वापस res;
पूर्ण

/**
 * seq_buf_to_user - copy the squence buffer to user space
 * @s: seq_buf descriptor
 * @ubuf: The userspace memory location to copy to
 * @cnt: The amount to copy
 *
 * Copies the sequence buffer पूर्णांकo the userspace memory poपूर्णांकed to
 * by @ubuf. It starts from the last पढ़ो position (@s->पढ़ोpos)
 * and ग_लिखोs up to @cnt अक्षरacters or till it reaches the end of
 * the content in the buffer (@s->len), which ever comes first.
 *
 * On success, it वापसs a positive number of the number of bytes
 * it copied.
 *
 * On failure it वापसs -EBUSY अगर all of the content in the
 * sequence has been alपढ़ोy पढ़ो, which includes nothing in the
 * sequence (@s->len == @s->पढ़ोpos).
 *
 * Returns -EFAULT अगर the copy to userspace fails.
 */
पूर्णांक seq_buf_to_user(काष्ठा seq_buf *s, अक्षर __user *ubuf, पूर्णांक cnt)
अणु
	पूर्णांक len;
	पूर्णांक ret;

	अगर (!cnt)
		वापस 0;

	len = seq_buf_used(s);

	अगर (len <= s->पढ़ोpos)
		वापस -EBUSY;

	len -= s->पढ़ोpos;
	अगर (cnt > len)
		cnt = len;
	ret = copy_to_user(ubuf, s->buffer + s->पढ़ोpos, cnt);
	अगर (ret == cnt)
		वापस -EFAULT;

	cnt -= ret;

	s->पढ़ोpos += cnt;
	वापस cnt;
पूर्ण

/**
 * seq_buf_hex_dump - prपूर्णांक क्रमmatted hex dump पूर्णांकo the sequence buffer
 * @s: seq_buf descriptor
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
 * Function is an analogue of prपूर्णांक_hex_dump() and thus has similar पूर्णांकerface.
 *
 * linebuf size is maximal length क्रम one line.
 * 32 * 3 - maximum bytes per line, each prपूर्णांकed पूर्णांकo 2 अक्षरs + 1 क्रम
 *	separating space
 * 2 - spaces separating hex dump and ascii representation
 * 32 - ascii representation
 * 1 - terminating '\0'
 *
 * Returns zero on success, -1 on overflow
 */
पूर्णांक seq_buf_hex_dump(काष्ठा seq_buf *s, स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
		     पूर्णांक rowsize, पूर्णांक groupsize,
		     स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
	स्थिर u8 *ptr = buf;
	पूर्णांक i, linelen, reमुख्यing = len;
	अचिन्हित अक्षर linebuf[32 * 3 + 2 + 32 + 1];
	पूर्णांक ret;

	अगर (rowsize != 16 && rowsize != 32)
		rowsize = 16;

	क्रम (i = 0; i < len; i += rowsize) अणु
		linelen = min(reमुख्यing, rowsize);
		reमुख्यing -= rowsize;

		hex_dump_to_buffer(ptr + i, linelen, rowsize, groupsize,
				   linebuf, माप(linebuf), ascii);

		चयन (prefix_type) अणु
		हाल DUMP_PREFIX_ADDRESS:
			ret = seq_buf_म_लिखो(s, "%s%p: %s\n",
			       prefix_str, ptr + i, linebuf);
			अवरोध;
		हाल DUMP_PREFIX_OFFSET:
			ret = seq_buf_म_लिखो(s, "%s%.8x: %s\n",
					     prefix_str, i, linebuf);
			अवरोध;
		शेष:
			ret = seq_buf_म_लिखो(s, "%s%s\n", prefix_str, linebuf);
			अवरोध;
		पूर्ण
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

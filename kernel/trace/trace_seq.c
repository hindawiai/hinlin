<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_seq.c
 *
 * Copyright (C) 2008-2014 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 * The trace_seq is a handy tool that allows you to pass a descriptor around
 * to a buffer that other functions can ग_लिखो to. It is similar to the
 * seq_file functionality but has some dअगरferences.
 *
 * To use it, the trace_seq must be initialized with trace_seq_init().
 * This will set up the counters within the descriptor. You can call
 * trace_seq_init() more than once to reset the trace_seq to start
 * from scratch.
 * 
 * The buffer size is currently PAGE_SIZE, although it may become dynamic
 * in the future.
 *
 * A ग_लिखो to the buffer will either succeed or fail. That is, unlike
 * प्र_लिखो() there will not be a partial ग_लिखो (well it may ग_लिखो पूर्णांकo
 * the buffer but it wont update the poपूर्णांकers). This allows users to
 * try to ग_लिखो something पूर्णांकo the trace_seq buffer and अगर it fails
 * they can flush it and try again.
 *
 */
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/trace_seq.h>

/* How much buffer is left on the trace_seq? */
#घोषणा TRACE_SEQ_BUF_LEFT(s) seq_buf_buffer_left(&(s)->seq)

/*
 * trace_seq should work with being initialized with 0s.
 */
अटल अंतरभूत व्योम __trace_seq_init(काष्ठा trace_seq *s)
अणु
	अगर (unlikely(!s->seq.size))
		trace_seq_init(s);
पूर्ण

/**
 * trace_prपूर्णांक_seq - move the contents of trace_seq पूर्णांकo a seq_file
 * @m: the seq_file descriptor that is the destination
 * @s: the trace_seq descriptor that is the source.
 *
 * Returns 0 on success and non zero on error. If it succeeds to
 * ग_लिखो to the seq_file it will reset the trace_seq, otherwise
 * it करोes not modअगरy the trace_seq to let the caller try again.
 */
पूर्णांक trace_prपूर्णांक_seq(काष्ठा seq_file *m, काष्ठा trace_seq *s)
अणु
	पूर्णांक ret;

	__trace_seq_init(s);

	ret = seq_buf_prपूर्णांक_seq(m, &s->seq);

	/*
	 * Only reset this buffer अगर we successfully wrote to the
	 * seq_file buffer. This lets the caller try again or
	 * करो something अन्यथा with the contents.
	 */
	अगर (!ret)
		trace_seq_init(s);

	वापस ret;
पूर्ण

/**
 * trace_seq_म_लिखो - sequence prपूर्णांकing of trace inक्रमmation
 * @s: trace sequence descriptor
 * @fmt: म_लिखो क्रमmat string
 *
 * The tracer may use either sequence operations or its own
 * copy to user routines. To simplअगरy क्रमmatting of a trace
 * trace_seq_म_लिखो() is used to store strings पूर्णांकo a special
 * buffer (@s). Then the output may be either used by
 * the sequencer or pulled पूर्णांकo another buffer.
 */
व्योम trace_seq_म_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, ...)
अणु
	अचिन्हित पूर्णांक save_len = s->seq.len;
	बहु_सूची ap;

	अगर (s->full)
		वापस;

	__trace_seq_init(s);

	बहु_शुरू(ap, fmt);
	seq_buf_भ_लिखो(&s->seq, fmt, ap);
	बहु_पूर्ण(ap);

	/* If we can't write it all, don't bother writing anything */
	अगर (unlikely(seq_buf_has_overflowed(&s->seq))) अणु
		s->seq.len = save_len;
		s->full = 1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_म_लिखो);

/**
 * trace_seq_biपंचांगask - ग_लिखो a biपंचांगask array in its ASCII representation
 * @s:		trace sequence descriptor
 * @maskp:	poपूर्णांकs to an array of अचिन्हित दीर्घs that represent a biपंचांगask
 * @nmaskbits:	The number of bits that are valid in @maskp
 *
 * Writes a ASCII representation of a biपंचांगask string पूर्णांकo @s.
 */
व्योम trace_seq_biपंचांगask(काष्ठा trace_seq *s, स्थिर अचिन्हित दीर्घ *maskp,
		      पूर्णांक nmaskbits)
अणु
	अचिन्हित पूर्णांक save_len = s->seq.len;

	अगर (s->full)
		वापस;

	__trace_seq_init(s);

	seq_buf_म_लिखो(&s->seq, "%*pb", nmaskbits, maskp);

	अगर (unlikely(seq_buf_has_overflowed(&s->seq))) अणु
		s->seq.len = save_len;
		s->full = 1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_biपंचांगask);

/**
 * trace_seq_भ_लिखो - sequence prपूर्णांकing of trace inक्रमmation
 * @s: trace sequence descriptor
 * @fmt: म_लिखो क्रमmat string
 *
 * The tracer may use either sequence operations or its own
 * copy to user routines. To simplअगरy क्रमmatting of a trace
 * trace_seq_म_लिखो is used to store strings पूर्णांकo a special
 * buffer (@s). Then the output may be either used by
 * the sequencer or pulled पूर्णांकo another buffer.
 */
व्योम trace_seq_भ_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	अचिन्हित पूर्णांक save_len = s->seq.len;

	अगर (s->full)
		वापस;

	__trace_seq_init(s);

	seq_buf_भ_लिखो(&s->seq, fmt, args);

	/* If we can't write it all, don't bother writing anything */
	अगर (unlikely(seq_buf_has_overflowed(&s->seq))) अणु
		s->seq.len = save_len;
		s->full = 1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_भ_लिखो);

/**
 * trace_seq_bम_लिखो - Write the म_लिखो string from binary arguments
 * @s: trace sequence descriptor
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
 */
व्योम trace_seq_bम_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, स्थिर u32 *binary)
अणु
	अचिन्हित पूर्णांक save_len = s->seq.len;

	अगर (s->full)
		वापस;

	__trace_seq_init(s);

	seq_buf_bम_लिखो(&s->seq, fmt, binary);

	/* If we can't write it all, don't bother writing anything */
	अगर (unlikely(seq_buf_has_overflowed(&s->seq))) अणु
		s->seq.len = save_len;
		s->full = 1;
		वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_bम_लिखो);

/**
 * trace_seq_माला_दो - trace sequence prपूर्णांकing of simple string
 * @s: trace sequence descriptor
 * @str: simple string to record
 *
 * The tracer may use either the sequence operations or its own
 * copy to user routines. This function records a simple string
 * पूर्णांकo a special buffer (@s) क्रम later retrieval by a sequencer
 * or other mechanism.
 */
व्योम trace_seq_माला_दो(काष्ठा trace_seq *s, स्थिर अक्षर *str)
अणु
	अचिन्हित पूर्णांक len = म_माप(str);

	अगर (s->full)
		वापस;

	__trace_seq_init(s);

	अगर (len > TRACE_SEQ_BUF_LEFT(s)) अणु
		s->full = 1;
		वापस;
	पूर्ण

	seq_buf_puपंचांगem(&s->seq, str, len);
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_माला_दो);

/**
 * trace_seq_अ_दो - trace sequence prपूर्णांकing of simple अक्षरacter
 * @s: trace sequence descriptor
 * @c: simple अक्षरacter to record
 *
 * The tracer may use either the sequence operations or its own
 * copy to user routines. This function records a simple अक्षरacter
 * पूर्णांकo a special buffer (@s) क्रम later retrieval by a sequencer
 * or other mechanism.
 */
व्योम trace_seq_अ_दो(काष्ठा trace_seq *s, अचिन्हित अक्षर c)
अणु
	अगर (s->full)
		वापस;

	__trace_seq_init(s);

	अगर (TRACE_SEQ_BUF_LEFT(s) < 1) अणु
		s->full = 1;
		वापस;
	पूर्ण

	seq_buf_अ_दो(&s->seq, c);
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_अ_दो);

/**
 * trace_seq_puपंचांगem - ग_लिखो raw data पूर्णांकo the trace_seq buffer
 * @s: trace sequence descriptor
 * @mem: The raw memory to copy पूर्णांकo the buffer
 * @len: The length of the raw memory to copy (in bytes)
 *
 * There may be हालs where raw memory needs to be written पूर्णांकo the
 * buffer and a म_नकल() would not work. Using this function allows
 * क्रम such हालs.
 */
व्योम trace_seq_puपंचांगem(काष्ठा trace_seq *s, स्थिर व्योम *mem, अचिन्हित पूर्णांक len)
अणु
	अगर (s->full)
		वापस;

	__trace_seq_init(s);

	अगर (len > TRACE_SEQ_BUF_LEFT(s)) अणु
		s->full = 1;
		वापस;
	पूर्ण

	seq_buf_puपंचांगem(&s->seq, mem, len);
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_puपंचांगem);

/**
 * trace_seq_puपंचांगem_hex - ग_लिखो raw memory पूर्णांकo the buffer in ASCII hex
 * @s: trace sequence descriptor
 * @mem: The raw memory to ग_लिखो its hex ASCII representation of
 * @len: The length of the raw memory to copy (in bytes)
 *
 * This is similar to trace_seq_puपंचांगem() except instead of just copying the
 * raw memory पूर्णांकo the buffer it ग_लिखोs its ASCII representation of it
 * in hex अक्षरacters.
 */
व्योम trace_seq_puपंचांगem_hex(काष्ठा trace_seq *s, स्थिर व्योम *mem,
			 अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक save_len = s->seq.len;

	अगर (s->full)
		वापस;

	__trace_seq_init(s);

	/* Each byte is represented by two अक्षरs */
	अगर (len * 2 > TRACE_SEQ_BUF_LEFT(s)) अणु
		s->full = 1;
		वापस;
	पूर्ण

	/* The added spaces can still cause an overflow */
	seq_buf_puपंचांगem_hex(&s->seq, mem, len);

	अगर (unlikely(seq_buf_has_overflowed(&s->seq))) अणु
		s->seq.len = save_len;
		s->full = 1;
		वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_puपंचांगem_hex);

/**
 * trace_seq_path - copy a path पूर्णांकo the sequence buffer
 * @s: trace sequence descriptor
 * @path: path to ग_लिखो पूर्णांकo the sequence buffer.
 *
 * Write a path name पूर्णांकo the sequence buffer.
 *
 * Returns 1 अगर we successfully written all the contents to
 *   the buffer.
 * Returns 0 अगर we the length to ग_लिखो is bigger than the
 *   reserved buffer space. In this हाल, nothing माला_लो written.
 */
पूर्णांक trace_seq_path(काष्ठा trace_seq *s, स्थिर काष्ठा path *path)
अणु
	अचिन्हित पूर्णांक save_len = s->seq.len;

	अगर (s->full)
		वापस 0;

	__trace_seq_init(s);

	अगर (TRACE_SEQ_BUF_LEFT(s) < 1) अणु
		s->full = 1;
		वापस 0;
	पूर्ण

	seq_buf_path(&s->seq, path, "\n");

	अगर (unlikely(seq_buf_has_overflowed(&s->seq))) अणु
		s->seq.len = save_len;
		s->full = 1;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_path);

/**
 * trace_seq_to_user - copy the sequence buffer to user space
 * @s: trace sequence descriptor
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
पूर्णांक trace_seq_to_user(काष्ठा trace_seq *s, अक्षर __user *ubuf, पूर्णांक cnt)
अणु
	__trace_seq_init(s);
	वापस seq_buf_to_user(&s->seq, ubuf, cnt);
पूर्ण
EXPORT_SYMBOL_GPL(trace_seq_to_user);

पूर्णांक trace_seq_hex_dump(काष्ठा trace_seq *s, स्थिर अक्षर *prefix_str,
		       पूर्णांक prefix_type, पूर्णांक rowsize, पूर्णांक groupsize,
		       स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
	अचिन्हित पूर्णांक save_len = s->seq.len;

	अगर (s->full)
		वापस 0;

	__trace_seq_init(s);

	अगर (TRACE_SEQ_BUF_LEFT(s) < 1) अणु
		s->full = 1;
		वापस 0;
	पूर्ण

	seq_buf_hex_dump(&(s->seq), prefix_str,
		   prefix_type, rowsize, groupsize,
		   buf, len, ascii);

	अगर (unlikely(seq_buf_has_overflowed(&s->seq))) अणु
		s->seq.len = save_len;
		s->full = 1;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL(trace_seq_hex_dump);

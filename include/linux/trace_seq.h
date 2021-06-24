<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TRACE_SEQ_H
#घोषणा _LINUX_TRACE_SEQ_H

#समावेश <linux/seq_buf.h>

#समावेश <यंत्र/page.h>

/*
 * Trace sequences are used to allow a function to call several other functions
 * to create a string of data to use (up to a max of PAGE_SIZE).
 */

काष्ठा trace_seq अणु
	अक्षर			buffer[PAGE_SIZE];
	काष्ठा seq_buf		seq;
	पूर्णांक			full;
पूर्ण;

अटल अंतरभूत व्योम
trace_seq_init(काष्ठा trace_seq *s)
अणु
	seq_buf_init(&s->seq, s->buffer, PAGE_SIZE);
	s->full = 0;
पूर्ण

/**
 * trace_seq_used - amount of actual data written to buffer
 * @s: trace sequence descriptor
 *
 * Returns the amount of data written to the buffer.
 *
 * IMPORTANT!
 *
 * Use this instead of @s->seq.len अगर you need to pass the amount
 * of data from the buffer to another buffer (userspace, or what not).
 * The @s->seq.len on overflow is bigger than the buffer size and
 * using it can cause access to undefined memory.
 */
अटल अंतरभूत पूर्णांक trace_seq_used(काष्ठा trace_seq *s)
अणु
	वापस seq_buf_used(&s->seq);
पूर्ण

/**
 * trace_seq_buffer_ptr - वापस poपूर्णांकer to next location in buffer
 * @s: trace sequence descriptor
 *
 * Returns the poपूर्णांकer to the buffer where the next ग_लिखो to
 * the buffer will happen. This is useful to save the location
 * that is about to be written to and then वापस the result
 * of that ग_लिखो.
 */
अटल अंतरभूत अक्षर *
trace_seq_buffer_ptr(काष्ठा trace_seq *s)
अणु
	वापस s->buffer + seq_buf_used(&s->seq);
पूर्ण

/**
 * trace_seq_has_overflowed - वापस true अगर the trace_seq took too much
 * @s: trace sequence descriptor
 *
 * Returns true अगर too much data was added to the trace_seq and it is
 * now full and will not take anymore.
 */
अटल अंतरभूत bool trace_seq_has_overflowed(काष्ठा trace_seq *s)
अणु
	वापस s->full || seq_buf_has_overflowed(&s->seq);
पूर्ण

/*
 * Currently only defined when tracing is enabled.
 */
#अगर_घोषित CONFIG_TRACING
बाह्य __म_लिखो(2, 3)
व्योम trace_seq_म_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 0)
व्योम trace_seq_भ_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, बहु_सूची args);
बाह्य व्योम
trace_seq_bम_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, स्थिर u32 *binary);
बाह्य पूर्णांक trace_prपूर्णांक_seq(काष्ठा seq_file *m, काष्ठा trace_seq *s);
बाह्य पूर्णांक trace_seq_to_user(काष्ठा trace_seq *s, अक्षर __user *ubuf,
			     पूर्णांक cnt);
बाह्य व्योम trace_seq_माला_दो(काष्ठा trace_seq *s, स्थिर अक्षर *str);
बाह्य व्योम trace_seq_अ_दो(काष्ठा trace_seq *s, अचिन्हित अक्षर c);
बाह्य व्योम trace_seq_puपंचांगem(काष्ठा trace_seq *s, स्थिर व्योम *mem, अचिन्हित पूर्णांक len);
बाह्य व्योम trace_seq_puपंचांगem_hex(काष्ठा trace_seq *s, स्थिर व्योम *mem,
				अचिन्हित पूर्णांक len);
बाह्य पूर्णांक trace_seq_path(काष्ठा trace_seq *s, स्थिर काष्ठा path *path);

बाह्य व्योम trace_seq_biपंचांगask(काष्ठा trace_seq *s, स्थिर अचिन्हित दीर्घ *maskp,
			     पूर्णांक nmaskbits);

बाह्य पूर्णांक trace_seq_hex_dump(काष्ठा trace_seq *s, स्थिर अक्षर *prefix_str,
			      पूर्णांक prefix_type, पूर्णांक rowsize, पूर्णांक groupsize,
			      स्थिर व्योम *buf, माप_प्रकार len, bool ascii);

#अन्यथा /* CONFIG_TRACING */
अटल अंतरभूत व्योम trace_seq_म_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, ...)
अणु
पूर्ण
अटल अंतरभूत व्योम
trace_seq_bम_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, स्थिर u32 *binary)
अणु
पूर्ण

अटल अंतरभूत व्योम
trace_seq_biपंचांगask(काष्ठा trace_seq *s, स्थिर अचिन्हित दीर्घ *maskp,
		  पूर्णांक nmaskbits)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक trace_prपूर्णांक_seq(काष्ठा seq_file *m, काष्ठा trace_seq *s)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक trace_seq_to_user(काष्ठा trace_seq *s, अक्षर __user *ubuf,
				    पूर्णांक cnt)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम trace_seq_माला_दो(काष्ठा trace_seq *s, स्थिर अक्षर *str)
अणु
पूर्ण
अटल अंतरभूत व्योम trace_seq_अ_दो(काष्ठा trace_seq *s, अचिन्हित अक्षर c)
अणु
पूर्ण
अटल अंतरभूत व्योम
trace_seq_puपंचांगem(काष्ठा trace_seq *s, स्थिर व्योम *mem, अचिन्हित पूर्णांक len)
अणु
पूर्ण
अटल अंतरभूत व्योम trace_seq_puपंचांगem_hex(काष्ठा trace_seq *s, स्थिर व्योम *mem,
				       अचिन्हित पूर्णांक len)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक trace_seq_path(काष्ठा trace_seq *s, स्थिर काष्ठा path *path)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRACING */

#पूर्ण_अगर /* _LINUX_TRACE_SEQ_H */

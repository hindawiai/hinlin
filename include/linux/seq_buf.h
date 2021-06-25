<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SEQ_BUF_H
#घोषणा _LINUX_SEQ_BUF_H

#समावेश <linux/fs.h>

/*
 * Trace sequences are used to allow a function to call several other functions
 * to create a string of data to use.
 */

/**
 * seq_buf - seq buffer काष्ठाure
 * @buffer:	poपूर्णांकer to the buffer
 * @size:	size of the buffer
 * @len:	the amount of data inside the buffer
 * @पढ़ोpos:	The next position to पढ़ो in the buffer.
 */
काष्ठा seq_buf अणु
	अक्षर			*buffer;
	माप_प्रकार			size;
	माप_प्रकार			len;
	loff_t			पढ़ोpos;
पूर्ण;

अटल अंतरभूत व्योम seq_buf_clear(काष्ठा seq_buf *s)
अणु
	s->len = 0;
	s->पढ़ोpos = 0;
पूर्ण

अटल अंतरभूत व्योम
seq_buf_init(काष्ठा seq_buf *s, अक्षर *buf, अचिन्हित पूर्णांक size)
अणु
	s->buffer = buf;
	s->size = size;
	seq_buf_clear(s);
पूर्ण

/*
 * seq_buf have a buffer that might overflow. When this happens
 * the len and size are set to be equal.
 */
अटल अंतरभूत bool
seq_buf_has_overflowed(काष्ठा seq_buf *s)
अणु
	वापस s->len > s->size;
पूर्ण

अटल अंतरभूत व्योम
seq_buf_set_overflow(काष्ठा seq_buf *s)
अणु
	s->len = s->size + 1;
पूर्ण

/*
 * How much buffer is left on the seq_buf?
 */
अटल अंतरभूत अचिन्हित पूर्णांक
seq_buf_buffer_left(काष्ठा seq_buf *s)
अणु
	अगर (seq_buf_has_overflowed(s))
		वापस 0;

	वापस s->size - s->len;
पूर्ण

/* How much buffer was written? */
अटल अंतरभूत अचिन्हित पूर्णांक seq_buf_used(काष्ठा seq_buf *s)
अणु
	वापस min(s->len, s->size);
पूर्ण

/**
 * seq_buf_terminate - Make sure buffer is nul terminated
 * @s: the seq_buf descriptor to terminate.
 *
 * This makes sure that the buffer in @s is nul terminated and
 * safe to पढ़ो as a string.
 *
 * Note, अगर this is called when the buffer has overflowed, then
 * the last byte of the buffer is zeroed, and the len will still
 * poपूर्णांक passed it.
 *
 * After this function is called, s->buffer is safe to use
 * in string operations.
 */
अटल अंतरभूत व्योम seq_buf_terminate(काष्ठा seq_buf *s)
अणु
	अगर (WARN_ON(s->size == 0))
		वापस;

	अगर (seq_buf_buffer_left(s))
		s->buffer[s->len] = 0;
	अन्यथा
		s->buffer[s->size - 1] = 0;
पूर्ण

/**
 * seq_buf_get_buf - get buffer to ग_लिखो arbitrary data to
 * @s: the seq_buf handle
 * @bufp: the beginning of the buffer is stored here
 *
 * Return the number of bytes available in the buffer, or zero अगर
 * there's no space.
 */
अटल अंतरभूत माप_प्रकार seq_buf_get_buf(काष्ठा seq_buf *s, अक्षर **bufp)
अणु
	WARN_ON(s->len > s->size + 1);

	अगर (s->len < s->size) अणु
		*bufp = s->buffer + s->len;
		वापस s->size - s->len;
	पूर्ण

	*bufp = शून्य;
	वापस 0;
पूर्ण

/**
 * seq_buf_commit - commit data to the buffer
 * @s: the seq_buf handle
 * @num: the number of bytes to commit
 *
 * Commit @num bytes of data written to a buffer previously acquired
 * by seq_buf_get.  To संकेत an error condition, or that the data
 * didn't fit in the available space, pass a negative @num value.
 */
अटल अंतरभूत व्योम seq_buf_commit(काष्ठा seq_buf *s, पूर्णांक num)
अणु
	अगर (num < 0) अणु
		seq_buf_set_overflow(s);
	पूर्ण अन्यथा अणु
		/* num must be negative on overflow */
		BUG_ON(s->len + num > s->size);
		s->len += num;
	पूर्ण
पूर्ण

बाह्य __म_लिखो(2, 3)
पूर्णांक seq_buf_म_लिखो(काष्ठा seq_buf *s, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 0)
पूर्णांक seq_buf_भ_लिखो(काष्ठा seq_buf *s, स्थिर अक्षर *fmt, बहु_सूची args);
बाह्य पूर्णांक seq_buf_prपूर्णांक_seq(काष्ठा seq_file *m, काष्ठा seq_buf *s);
बाह्य पूर्णांक seq_buf_to_user(काष्ठा seq_buf *s, अक्षर __user *ubuf,
			   पूर्णांक cnt);
बाह्य पूर्णांक seq_buf_माला_दो(काष्ठा seq_buf *s, स्थिर अक्षर *str);
बाह्य पूर्णांक seq_buf_अ_दो(काष्ठा seq_buf *s, अचिन्हित अक्षर c);
बाह्य पूर्णांक seq_buf_puपंचांगem(काष्ठा seq_buf *s, स्थिर व्योम *mem, अचिन्हित पूर्णांक len);
बाह्य पूर्णांक seq_buf_puपंचांगem_hex(काष्ठा seq_buf *s, स्थिर व्योम *mem,
			      अचिन्हित पूर्णांक len);
बाह्य पूर्णांक seq_buf_path(काष्ठा seq_buf *s, स्थिर काष्ठा path *path, स्थिर अक्षर *esc);
बाह्य पूर्णांक seq_buf_hex_dump(काष्ठा seq_buf *s, स्थिर अक्षर *prefix_str,
			    पूर्णांक prefix_type, पूर्णांक rowsize, पूर्णांक groupsize,
			    स्थिर व्योम *buf, माप_प्रकार len, bool ascii);

#अगर_घोषित CONFIG_BINARY_PRINTF
बाह्य पूर्णांक
seq_buf_bम_लिखो(काष्ठा seq_buf *s, स्थिर अक्षर *fmt, स्थिर u32 *binary);
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SEQ_BUF_H */

<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */
#समावेश "trace-seq.h"

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>

#समावेश <यंत्र/bug.h>
#समावेश "event-parse.h"
#समावेश "event-utils.h"

/*
 * The TRACE_SEQ_POISON is to catch the use of using
 * a trace_seq काष्ठाure after it was destroyed.
 */
#घोषणा TRACE_SEQ_POISON	((व्योम *)0xdeadbeef)
#घोषणा TRACE_SEQ_CHECK(s)						\
करो अणु									\
	अगर (WARN_ONCE((s)->buffer == TRACE_SEQ_POISON,			\
		      "Usage of trace_seq after it was destroyed"))	\
		(s)->state = TRACE_SEQ__BUFFER_POISONED;		\
पूर्ण जबतक (0)

#घोषणा TRACE_SEQ_CHECK_RET_N(s, n)		\
करो अणु						\
	TRACE_SEQ_CHECK(s);			\
	अगर ((s)->state != TRACE_SEQ__GOOD)	\
		वापस n; 			\
पूर्ण जबतक (0)

#घोषणा TRACE_SEQ_CHECK_RET(s)   TRACE_SEQ_CHECK_RET_N(s, )
#घोषणा TRACE_SEQ_CHECK_RET0(s)  TRACE_SEQ_CHECK_RET_N(s, 0)

/**
 * trace_seq_init - initialize the trace_seq काष्ठाure
 * @s: a poपूर्णांकer to the trace_seq काष्ठाure to initialize
 */
व्योम trace_seq_init(काष्ठा trace_seq *s)
अणु
	s->len = 0;
	s->पढ़ोpos = 0;
	s->buffer_size = TRACE_SEQ_BUF_SIZE;
	s->buffer = दो_स्मृति(s->buffer_size);
	अगर (s->buffer != शून्य)
		s->state = TRACE_SEQ__GOOD;
	अन्यथा
		s->state = TRACE_SEQ__MEM_ALLOC_FAILED;
पूर्ण

/**
 * trace_seq_reset - re-initialize the trace_seq काष्ठाure
 * @s: a poपूर्णांकer to the trace_seq काष्ठाure to reset
 */
व्योम trace_seq_reset(काष्ठा trace_seq *s)
अणु
	अगर (!s)
		वापस;
	TRACE_SEQ_CHECK(s);
	s->len = 0;
	s->पढ़ोpos = 0;
पूर्ण

/**
 * trace_seq_destroy - मुक्त up memory of a trace_seq
 * @s: a poपूर्णांकer to the trace_seq to मुक्त the buffer
 *
 * Only मुक्तs the buffer, not the trace_seq काष्ठा itself.
 */
व्योम trace_seq_destroy(काष्ठा trace_seq *s)
अणु
	अगर (!s)
		वापस;
	TRACE_SEQ_CHECK_RET(s);
	मुक्त(s->buffer);
	s->buffer = TRACE_SEQ_POISON;
पूर्ण

अटल व्योम expand_buffer(काष्ठा trace_seq *s)
अणु
	अक्षर *buf;

	buf = पुनः_स्मृति(s->buffer, s->buffer_size + TRACE_SEQ_BUF_SIZE);
	अगर (WARN_ONCE(!buf, "Can't allocate trace_seq buffer memory")) अणु
		s->state = TRACE_SEQ__MEM_ALLOC_FAILED;
		वापस;
	पूर्ण

	s->buffer = buf;
	s->buffer_size += TRACE_SEQ_BUF_SIZE;
पूर्ण

/**
 * trace_seq_म_लिखो - sequence prपूर्णांकing of trace inक्रमmation
 * @s: trace sequence descriptor
 * @fmt: म_लिखो क्रमmat string
 *
 * It वापसs 0 अगर the trace oversizes the buffer's मुक्त
 * space, the number of अक्षरacters prपूर्णांकed, or a negative
 * value in हाल of an error.
 *
 * The tracer may use either sequence operations or its own
 * copy to user routines. To simplअगरy क्रमmating of a trace
 * trace_seq_म_लिखो is used to store strings पूर्णांकo a special
 * buffer (@s). Then the output may be either used by
 * the sequencer or pulled पूर्णांकo another buffer.
 */
पूर्णांक
trace_seq_म_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक len;
	पूर्णांक ret;

 try_again:
	TRACE_SEQ_CHECK_RET0(s);

	len = (s->buffer_size - 1) - s->len;

	बहु_शुरू(ap, fmt);
	ret = vsnम_लिखो(s->buffer + s->len, len, fmt, ap);
	बहु_पूर्ण(ap);

	अगर (ret >= len) अणु
		expand_buffer(s);
		जाओ try_again;
	पूर्ण

	अगर (ret > 0)
		s->len += ret;

	वापस ret;
पूर्ण

/**
 * trace_seq_भ_लिखो - sequence prपूर्णांकing of trace inक्रमmation
 * @s: trace sequence descriptor
 * @fmt: म_लिखो क्रमmat string
 *
 * It वापसs 0 अगर the trace oversizes the buffer's मुक्त
 * space, the number of अक्षरacters prपूर्णांकed, or a negative
 * value in हाल of an error.
 * *
 * The tracer may use either sequence operations or its own
 * copy to user routines. To simplअगरy क्रमmating of a trace
 * trace_seq_म_लिखो is used to store strings पूर्णांकo a special
 * buffer (@s). Then the output may be either used by
 * the sequencer or pulled पूर्णांकo another buffer.
 */
पूर्णांक
trace_seq_भ_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक len;
	पूर्णांक ret;

 try_again:
	TRACE_SEQ_CHECK_RET0(s);

	len = (s->buffer_size - 1) - s->len;

	ret = vsnम_लिखो(s->buffer + s->len, len, fmt, args);

	अगर (ret >= len) अणु
		expand_buffer(s);
		जाओ try_again;
	पूर्ण

	अगर (ret > 0)
		s->len += ret;

	वापस ret;
पूर्ण

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
पूर्णांक trace_seq_माला_दो(काष्ठा trace_seq *s, स्थिर अक्षर *str)
अणु
	पूर्णांक len;

	TRACE_SEQ_CHECK_RET0(s);

	len = म_माप(str);

	जबतक (len > ((s->buffer_size - 1) - s->len))
		expand_buffer(s);

	TRACE_SEQ_CHECK_RET0(s);

	स_नकल(s->buffer + s->len, str, len);
	s->len += len;

	वापस len;
पूर्ण

पूर्णांक trace_seq_अ_दो(काष्ठा trace_seq *s, अचिन्हित अक्षर c)
अणु
	TRACE_SEQ_CHECK_RET0(s);

	जबतक (s->len >= (s->buffer_size - 1))
		expand_buffer(s);

	TRACE_SEQ_CHECK_RET0(s);

	s->buffer[s->len++] = c;

	वापस 1;
पूर्ण

व्योम trace_seq_terminate(काष्ठा trace_seq *s)
अणु
	TRACE_SEQ_CHECK_RET(s);

	/* There's always one अक्षरacter left on the buffer */
	s->buffer[s->len] = 0;
पूर्ण

पूर्णांक trace_seq_करो_ख_लिखो(काष्ठा trace_seq *s, खाता *fp)
अणु
	TRACE_SEQ_CHECK(s);

	चयन (s->state) अणु
	हाल TRACE_SEQ__GOOD:
		वापस ख_लिखो(fp, "%.*s", s->len, s->buffer);
	हाल TRACE_SEQ__BUFFER_POISONED:
		ख_लिखो(fp, "%s\n", "Usage of trace_seq after it was destroyed");
		अवरोध;
	हाल TRACE_SEQ__MEM_ALLOC_FAILED:
		ख_लिखो(fp, "%s\n", "Can't allocate trace_seq buffer memory");
		अवरोध;
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक trace_seq_करो_म_लिखो(काष्ठा trace_seq *s)
अणु
	वापस trace_seq_करो_ख_लिखो(s, मानक_निकास);
पूर्ण

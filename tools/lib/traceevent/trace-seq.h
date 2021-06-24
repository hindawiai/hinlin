<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */

#अगर_अघोषित _TRACE_SEQ_H
#घोषणा _TRACE_SEQ_H

#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>

/* ----------------------- trace_seq ----------------------- */

#अगर_अघोषित TRACE_SEQ_BUF_SIZE
#घोषणा TRACE_SEQ_BUF_SIZE 4096
#पूर्ण_अगर

क्रमागत trace_seq_fail अणु
	TRACE_SEQ__GOOD,
	TRACE_SEQ__BUFFER_POISONED,
	TRACE_SEQ__MEM_ALLOC_FAILED,
पूर्ण;

/*
 * Trace sequences are used to allow a function to call several other functions
 * to create a string of data to use (up to a max of PAGE_SIZE).
 */

काष्ठा trace_seq अणु
	अक्षर			*buffer;
	अचिन्हित पूर्णांक		buffer_size;
	अचिन्हित पूर्णांक		len;
	अचिन्हित पूर्णांक		पढ़ोpos;
	क्रमागत trace_seq_fail	state;
पूर्ण;

व्योम trace_seq_init(काष्ठा trace_seq *s);
व्योम trace_seq_reset(काष्ठा trace_seq *s);
व्योम trace_seq_destroy(काष्ठा trace_seq *s);

बाह्य पूर्णांक trace_seq_म_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 2, 3)));
बाह्य पूर्णांक trace_seq_भ_लिखो(काष्ठा trace_seq *s, स्थिर अक्षर *fmt, बहु_सूची args)
	__attribute__ ((क्रमmat (म_लिखो, 2, 0)));

बाह्य पूर्णांक trace_seq_माला_दो(काष्ठा trace_seq *s, स्थिर अक्षर *str);
बाह्य पूर्णांक trace_seq_अ_दो(काष्ठा trace_seq *s, अचिन्हित अक्षर c);

बाह्य व्योम trace_seq_terminate(काष्ठा trace_seq *s);

बाह्य पूर्णांक trace_seq_करो_ख_लिखो(काष्ठा trace_seq *s, खाता *fp);
बाह्य पूर्णांक trace_seq_करो_म_लिखो(काष्ठा trace_seq *s);

#पूर्ण_अगर /* _TRACE_SEQ_H */

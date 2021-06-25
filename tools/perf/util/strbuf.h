<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_STRBUF_H
#घोषणा __PERF_STRBUF_H

/*
 * Strbuf's can be use in many ways: as a byte array, or to store arbitrary
 * दीर्घ, overflow safe strings.
 *
 * Strbufs has some invariants that are very important to keep in mind:
 *
 * 1. the ->buf member is always दो_स्मृति-ed, hence strbuf's can be used to
 *    build complex strings/buffers whose final size isn't easily known.
 *
 *    It is NOT legal to copy the ->buf poपूर्णांकer away.
 *    `strbuf_detach' is the operation that detaches a buffer from its shell
 *    जबतक keeping the shell valid wrt its invariants.
 *
 * 2. the ->buf member is a byte array that has at least ->len + 1 bytes
 *    allocated. The extra byte is used to store a '\0', allowing the ->buf
 *    member to be a valid C-string. Every strbuf function ensure this
 *    invariant is preserved.
 *
 *    Note that it is OK to "play" with the buffer directly अगर you work it
 *    that way:
 *
 *    strbuf_grow(sb, SOME_SIZE);
 *       ... Here, the memory array starting at sb->buf, and of length
 *       ... strbuf_avail(sb) is all yours, and you are sure that
 *       ... strbuf_avail(sb) is at least SOME_SIZE.
 *    strbuf_setlen(sb, sb->len + SOME_OTHER_SIZE);
 *
 *    Of course, SOME_OTHER_SIZE must be smaller or equal to strbuf_avail(sb).
 *
 *    Doing so is safe, though अगर it has to be करोne in many places, adding the
 *    missing API to the strbuf module is the way to go.
 *
 *    XXX: करो _not_ assume that the area that is yours is of size ->alloc - 1
 *         even अगर it's true in the current implementation. Alloc is somehow a
 *         "private" member that should not be messed with.
 */

#समावेश <निश्चित.स>
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <linux/compiler.h>
#समावेश <sys/types.h>

बाह्य अक्षर strbuf_slopbuf[];
काष्ठा strbuf अणु
	माप_प्रकार alloc;
	माप_प्रकार len;
	अक्षर *buf;
पूर्ण;

#घोषणा STRBUF_INIT  अणु 0, 0, strbuf_slopbuf पूर्ण

/*----- strbuf lअगरe cycle -----*/
पूर्णांक strbuf_init(काष्ठा strbuf *buf, sमाप_प्रकार hपूर्णांक);
व्योम strbuf_release(काष्ठा strbuf *buf);
अक्षर *strbuf_detach(काष्ठा strbuf *buf, माप_प्रकार *);

/*----- strbuf size related -----*/
अटल अंतरभूत sमाप_प्रकार strbuf_avail(स्थिर काष्ठा strbuf *sb) अणु
	वापस sb->alloc ? sb->alloc - sb->len - 1 : 0;
पूर्ण

पूर्णांक strbuf_grow(काष्ठा strbuf *buf, माप_प्रकार);

अटल अंतरभूत पूर्णांक strbuf_setlen(काष्ठा strbuf *sb, माप_प्रकार len) अणु
	अगर (!sb->alloc) अणु
		पूर्णांक ret = strbuf_grow(sb, 0);
		अगर (ret)
			वापस ret;
	पूर्ण
	निश्चित(len < sb->alloc);
	sb->len = len;
	sb->buf[len] = '\0';
	वापस 0;
पूर्ण

/*----- add data in your buffer -----*/
पूर्णांक strbuf_addch(काष्ठा strbuf *sb, पूर्णांक c);

पूर्णांक strbuf_add(काष्ठा strbuf *buf, स्थिर व्योम *, माप_प्रकार);
अटल अंतरभूत पूर्णांक strbuf_addstr(काष्ठा strbuf *sb, स्थिर अक्षर *s) अणु
	वापस strbuf_add(sb, s, म_माप(s));
पूर्ण

पूर्णांक strbuf_addf(काष्ठा strbuf *sb, स्थिर अक्षर *fmt, ...) __म_लिखो(2, 3);

/* XXX: अगर पढ़ो fails, any partial पढ़ो is unकरोne */
sमाप_प्रकार strbuf_पढ़ो(काष्ठा strbuf *, पूर्णांक fd, sमाप_प्रकार hपूर्णांक);

#पूर्ण_अगर /* __PERF_STRBUF_H */

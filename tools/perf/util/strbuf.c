<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "cache.h"
#समावेश "debug.h"
#समावेश "strbuf.h"
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

/*
 * Used as the शेष ->buf value, so that people can always assume
 * buf is non शून्य and ->buf is NUL terminated even क्रम a freshly
 * initialized strbuf.
 */
अक्षर strbuf_slopbuf[1];

पूर्णांक strbuf_init(काष्ठा strbuf *sb, sमाप_प्रकार hपूर्णांक)
अणु
	sb->alloc = sb->len = 0;
	sb->buf = strbuf_slopbuf;
	अगर (hपूर्णांक)
		वापस strbuf_grow(sb, hपूर्णांक);
	वापस 0;
पूर्ण

व्योम strbuf_release(काष्ठा strbuf *sb)
अणु
	अगर (sb->alloc) अणु
		zमुक्त(&sb->buf);
		strbuf_init(sb, 0);
	पूर्ण
पूर्ण

अक्षर *strbuf_detach(काष्ठा strbuf *sb, माप_प्रकार *sz)
अणु
	अक्षर *res = sb->alloc ? sb->buf : शून्य;
	अगर (sz)
		*sz = sb->len;
	strbuf_init(sb, 0);
	वापस res;
पूर्ण

पूर्णांक strbuf_grow(काष्ठा strbuf *sb, माप_प्रकार extra)
अणु
	अक्षर *buf;
	माप_प्रकार nr = sb->len + extra + 1;

	अगर (nr < sb->alloc)
		वापस 0;

	अगर (nr <= sb->len)
		वापस -E2BIG;

	अगर (alloc_nr(sb->alloc) > nr)
		nr = alloc_nr(sb->alloc);

	/*
	 * Note that sb->buf == strbuf_slopbuf अगर sb->alloc == 0, and it is
	 * a अटल variable. Thus we have to aव्योम passing it to पुनः_स्मृति.
	 */
	buf = पुनः_स्मृति(sb->alloc ? sb->buf : शून्य, nr * माप(*buf));
	अगर (!buf)
		वापस -ENOMEM;

	sb->buf = buf;
	sb->alloc = nr;
	वापस 0;
पूर्ण

पूर्णांक strbuf_addch(काष्ठा strbuf *sb, पूर्णांक c)
अणु
	पूर्णांक ret = strbuf_grow(sb, 1);
	अगर (ret)
		वापस ret;

	sb->buf[sb->len++] = c;
	sb->buf[sb->len] = '\0';
	वापस 0;
पूर्ण

पूर्णांक strbuf_add(काष्ठा strbuf *sb, स्थिर व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक ret = strbuf_grow(sb, len);
	अगर (ret)
		वापस ret;

	स_नकल(sb->buf + sb->len, data, len);
	वापस strbuf_setlen(sb, sb->len + len);
पूर्ण

अटल पूर्णांक strbuf_addv(काष्ठा strbuf *sb, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	पूर्णांक len, ret;
	बहु_सूची ap_saved;

	अगर (!strbuf_avail(sb)) अणु
		ret = strbuf_grow(sb, 64);
		अगर (ret)
			वापस ret;
	पूर्ण

	va_copy(ap_saved, ap);
	len = vsnम_लिखो(sb->buf + sb->len, sb->alloc - sb->len, fmt, ap);
	अगर (len < 0) अणु
		बहु_पूर्ण(ap_saved);
		वापस len;
	पूर्ण
	अगर (len > strbuf_avail(sb)) अणु
		ret = strbuf_grow(sb, len);
		अगर (ret) अणु
			बहु_पूर्ण(ap_saved);
			वापस ret;
		पूर्ण
		len = vsnम_लिखो(sb->buf + sb->len, sb->alloc - sb->len, fmt, ap_saved);
		अगर (len > strbuf_avail(sb)) अणु
			pr_debug("this should not happen, your vsnprintf is broken");
			बहु_पूर्ण(ap_saved);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	बहु_पूर्ण(ap_saved);
	वापस strbuf_setlen(sb, sb->len + len);
पूर्ण

पूर्णांक strbuf_addf(काष्ठा strbuf *sb, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	बहु_शुरू(ap, fmt);
	ret = strbuf_addv(sb, fmt, ap);
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण

sमाप_प्रकार strbuf_पढ़ो(काष्ठा strbuf *sb, पूर्णांक fd, sमाप_प्रकार hपूर्णांक)
अणु
	माप_प्रकार oldlen = sb->len;
	माप_प्रकार oldalloc = sb->alloc;
	पूर्णांक ret;

	ret = strbuf_grow(sb, hपूर्णांक ? hपूर्णांक : 8192);
	अगर (ret)
		वापस ret;

	क्रम (;;) अणु
		sमाप_प्रकार cnt;

		cnt = पढ़ो(fd, sb->buf + sb->len, sb->alloc - sb->len - 1);
		अगर (cnt < 0) अणु
			अगर (oldalloc == 0)
				strbuf_release(sb);
			अन्यथा
				strbuf_setlen(sb, oldlen);
			वापस cnt;
		पूर्ण
		अगर (!cnt)
			अवरोध;
		sb->len += cnt;
		ret = strbuf_grow(sb, 8192);
		अगर (ret)
			वापस ret;
	पूर्ण

	sb->buf[sb->len] = '\0';
	वापस sb->len - oldlen;
पूर्ण

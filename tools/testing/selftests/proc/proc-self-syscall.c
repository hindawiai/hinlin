<शैली गुरु>
/*
 * Copyright तऊ 2018 Alexey Dobriyan <aकरोbriyan@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>

अटल अंतरभूत sमाप_प्रकार sys_पढ़ो(पूर्णांक fd, व्योम *buf, माप_प्रकार len)
अणु
	वापस syscall(SYS_पढ़ो, fd, buf, len);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	अक्षर buf1[64];
	अक्षर buf2[64];
	पूर्णांक fd;
	sमाप_प्रकार rv;

	fd = खोलो("/proc/self/syscall", O_RDONLY);
	अगर (fd == -1) अणु
		अगर (त्रुटि_सं == ENOENT)
			वापस 4;
		वापस 1;
	पूर्ण

	/* Do direct प्रणाली call as libc can wrap anything. */
	snम_लिखो(buf1, माप(buf1), "%ld 0x%lx 0x%lx 0x%lx",
		 (दीर्घ)SYS_पढ़ो, (दीर्घ)fd, (दीर्घ)buf2, (दीर्घ)माप(buf2));

	स_रखो(buf2, 0, माप(buf2));
	rv = sys_पढ़ो(fd, buf2, माप(buf2));
	अगर (rv < 0)
		वापस 1;
	अगर (rv < म_माप(buf1))
		वापस 1;
	अगर (म_भेदन(buf1, buf2, म_माप(buf1)) != 0)
		वापस 1;

	वापस 0;
पूर्ण

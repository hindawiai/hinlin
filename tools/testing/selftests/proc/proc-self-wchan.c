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
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>

पूर्णांक मुख्य(व्योम)
अणु
	अक्षर buf[64];
	पूर्णांक fd;

	fd = खोलो("/proc/self/wchan", O_RDONLY);
	अगर (fd == -1) अणु
		अगर (त्रुटि_सं == ENOENT)
			वापस 4;
		वापस 1;
	पूर्ण

	buf[0] = '\0';
	अगर (पढ़ो(fd, buf, माप(buf)) != 1)
		वापस 1;
	अगर (buf[0] != '0')
		वापस 1;
	वापस 0;
पूर्ण

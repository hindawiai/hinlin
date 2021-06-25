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
// Test that खोलो(/proc/*/fd/*) खोलोs the same file.
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक fd0, fd1, fd2;
	काष्ठा stat st0, st1, st2;
	अक्षर buf[64];
	पूर्णांक rv;

	fd0 = खोलो("/", O_सूचीECTORY|O_RDONLY);
	निश्चित(fd0 >= 0);

	snम_लिखो(buf, माप(buf), "/proc/self/fd/%u", fd0);
	fd1 = खोलो(buf, O_RDONLY);
	निश्चित(fd1 >= 0);

	snम_लिखो(buf, माप(buf), "/proc/thread-self/fd/%u", fd0);
	fd2 = खोलो(buf, O_RDONLY);
	निश्चित(fd2 >= 0);

	rv = ख_स्थिति(fd0, &st0);
	निश्चित(rv == 0);
	rv = ख_स्थिति(fd1, &st1);
	निश्चित(rv == 0);
	rv = ख_स्थिति(fd2, &st2);
	निश्चित(rv == 0);

	निश्चित(st0.st_dev == st1.st_dev);
	निश्चित(st0.st_ino == st1.st_ino);

	निश्चित(st0.st_dev == st2.st_dev);
	निश्चित(st0.st_ino == st2.st_ino);

	वापस 0;
पूर्ण

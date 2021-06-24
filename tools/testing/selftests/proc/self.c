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
// Test that /proc/self gives correct TGID.
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>

#समावेश "proc.h"

पूर्णांक मुख्य(व्योम)
अणु
	अक्षर buf1[64], buf2[64];
	pid_t pid;
	sमाप_प्रकार rv;

	pid = sys_getpid();
	snम_लिखो(buf1, माप(buf1), "%u", pid);

	rv = पढ़ोlink("/proc/self", buf2, माप(buf2));
	निश्चित(rv == म_माप(buf1));
	buf2[rv] = '\0';
	निश्चित(streq(buf1, buf2));

	वापस 0;
पूर्ण

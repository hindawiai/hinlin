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
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश "proc.h"

अटल व्योम proc_upसमय(पूर्णांक fd, uपूर्णांक64_t *upसमय, uपूर्णांक64_t *idle)
अणु
	uपूर्णांक64_t val1, val2;
	अक्षर buf[64], *p;
	sमाप_प्रकार rv;

	/* save "p < end" checks */
	स_रखो(buf, 0, माप(buf));
	rv = pपढ़ो(fd, buf, माप(buf), 0);
	निश्चित(0 <= rv && rv <= माप(buf));
	buf[माप(buf) - 1] = '\0';

	p = buf;

	val1 = xम_से_अदीर्घl(p, &p);
	निश्चित(p[0] == '.');
	निश्चित('0' <= p[1] && p[1] <= '9');
	निश्चित('0' <= p[2] && p[2] <= '9');
	निश्चित(p[3] == ' ');

	val2 = (p[1] - '0') * 10 + p[2] - '0';
	*upसमय = val1 * 100 + val2;

	p += 4;

	val1 = xम_से_अदीर्घl(p, &p);
	निश्चित(p[0] == '.');
	निश्चित('0' <= p[1] && p[1] <= '9');
	निश्चित('0' <= p[2] && p[2] <= '9');
	निश्चित(p[3] == '\n');

	val2 = (p[1] - '0') * 10 + p[2] - '0';
	*idle = val1 * 100 + val2;

	निश्चित(p + 4 == buf + rv);
पूर्ण

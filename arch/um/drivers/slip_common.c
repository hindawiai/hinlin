<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश "slip_common.h"
#समावेश <net_user.h>

पूर्णांक slip_proto_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slip_proto *slip)
अणु
	पूर्णांक i, n, size, start;

	अगर(slip->more > 0)अणु
		i = 0;
		जबतक(i < slip->more)अणु
			size = slip_unesc(slip->ibuf[i++], slip->ibuf,
					  &slip->pos, &slip->esc);
			अगर(size)अणु
				स_नकल(buf, slip->ibuf, size);
				स_हटाओ(slip->ibuf, &slip->ibuf[i],
					slip->more - i);
				slip->more = slip->more - i;
				वापस size;
			पूर्ण
		पूर्ण
		slip->more = 0;
	पूर्ण

	n = net_पढ़ो(fd, &slip->ibuf[slip->pos],
		     माप(slip->ibuf) - slip->pos);
	अगर(n <= 0)
		वापस n;

	start = slip->pos;
	क्रम(i = 0; i < n; i++)अणु
		size = slip_unesc(slip->ibuf[start + i], slip->ibuf,&slip->pos,
				  &slip->esc);
		अगर(size)अणु
			स_नकल(buf, slip->ibuf, size);
			स_हटाओ(slip->ibuf, &slip->ibuf[start+i+1],
				n - (i + 1));
			slip->more = n - (i + 1);
			वापस size;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक slip_proto_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slip_proto *slip)
अणु
	पूर्णांक actual, n;

	actual = slip_esc(buf, slip->obuf, len);
	n = net_ग_लिखो(fd, slip->obuf, actual);
	अगर(n < 0)
		वापस n;
	अन्यथा वापस len;
पूर्ण

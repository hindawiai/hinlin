<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_SLIP_COMMON_H
#घोषणा __UM_SLIP_COMMON_H

#घोषणा BUF_SIZE 1500
 /* two bytes each क्रम a (pathological) max packet of escaped अक्षरs +  *
  * terminating END अक्षर + initial END अक्षर                            */
#घोषणा ENC_BUF_SIZE (2 * BUF_SIZE + 2)

/* SLIP protocol अक्षरacters. */
#घोषणा SLIP_END             0300	/* indicates end of frame	*/
#घोषणा SLIP_ESC             0333	/* indicates byte stuffing	*/
#घोषणा SLIP_ESC_END         0334	/* ESC ESC_END means END 'data'	*/
#घोषणा SLIP_ESC_ESC         0335	/* ESC ESC_ESC means ESC 'data'	*/

अटल अंतरभूत पूर्णांक slip_unesc(अचिन्हित अक्षर c, अचिन्हित अक्षर *buf, पूर्णांक *pos,
                             पूर्णांक *esc)
अणु
	पूर्णांक ret;

	चयन(c)अणु
	हाल SLIP_END:
		*esc = 0;
		ret=*pos;
		*pos=0;
		वापस(ret);
	हाल SLIP_ESC:
		*esc = 1;
		वापस(0);
	हाल SLIP_ESC_ESC:
		अगर(*esc)अणु
			*esc = 0;
			c = SLIP_ESC;
		पूर्ण
		अवरोध;
	हाल SLIP_ESC_END:
		अगर(*esc)अणु
			*esc = 0;
			c = SLIP_END;
		पूर्ण
		अवरोध;
	पूर्ण
	buf[(*pos)++] = c;
	वापस(0);
पूर्ण

अटल अंतरभूत पूर्णांक slip_esc(अचिन्हित अक्षर *s, अचिन्हित अक्षर *d, पूर्णांक len)
अणु
	अचिन्हित अक्षर *ptr = d;
	अचिन्हित अक्षर c;

	/*
	 * Send an initial END अक्षरacter to flush out any
	 * data that may have accumulated in the receiver
	 * due to line noise.
	 */

	*ptr++ = SLIP_END;

	/*
	 * For each byte in the packet, send the appropriate
	 * अक्षरacter sequence, according to the SLIP protocol.
	 */

	जबतक (len-- > 0) अणु
		चयन(c = *s++) अणु
		हाल SLIP_END:
			*ptr++ = SLIP_ESC;
			*ptr++ = SLIP_ESC_END;
			अवरोध;
		हाल SLIP_ESC:
			*ptr++ = SLIP_ESC;
			*ptr++ = SLIP_ESC_ESC;
			अवरोध;
		शेष:
			*ptr++ = c;
			अवरोध;
		पूर्ण
	पूर्ण
	*ptr++ = SLIP_END;
	वापस (ptr - d);
पूर्ण

काष्ठा slip_proto अणु
	अचिन्हित अक्षर ibuf[ENC_BUF_SIZE];
	अचिन्हित अक्षर obuf[ENC_BUF_SIZE];
	पूर्णांक more; /* more data: करो not पढ़ो fd until ibuf has been drained */
	पूर्णांक pos;
	पूर्णांक esc;
पूर्ण;

अटल अंतरभूत व्योम slip_proto_init(काष्ठा slip_proto * slip)
अणु
	स_रखो(slip->ibuf, 0, माप(slip->ibuf));
	स_रखो(slip->obuf, 0, माप(slip->obuf));
	slip->more = 0;
	slip->pos = 0;
	slip->esc = 0;
पूर्ण

बाह्य पूर्णांक slip_proto_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len,
			   काष्ठा slip_proto *slip);
बाह्य पूर्णांक slip_proto_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len,
			    काष्ठा slip_proto *slip);

#पूर्ण_अगर

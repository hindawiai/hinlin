<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AV7110_IPACK_H_
#घोषणा _AV7110_IPACK_H_

बाह्य पूर्णांक av7110_ipack_init(काष्ठा ipack *p, पूर्णांक size,
			     व्योम (*func)(u8 *buf,  पूर्णांक size, व्योम *priv));

बाह्य व्योम av7110_ipack_reset(काष्ठा ipack *p);
बाह्य पूर्णांक  av7110_ipack_instant_repack(स्थिर u8 *buf, पूर्णांक count, काष्ठा ipack *p);
बाह्य व्योम av7110_ipack_मुक्त(काष्ठा ipack * p);
बाह्य व्योम av7110_ipack_flush(काष्ठा ipack *p);

#पूर्ण_अगर

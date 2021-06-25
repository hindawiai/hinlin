<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश "soc_common.h"
#समावेश "sa11xx_base.h"

काष्ठा sa1111_pcmcia_socket अणु
	काष्ठा soc_pcmcia_socket soc;
	काष्ठा sa1111_dev *dev;
	काष्ठा sa1111_pcmcia_socket *next;
पूर्ण;

अटल अंतरभूत काष्ठा sa1111_pcmcia_socket *to_skt(काष्ठा soc_pcmcia_socket *s)
अणु
	वापस container_of(s, काष्ठा sa1111_pcmcia_socket, soc);
पूर्ण

पूर्णांक sa1111_pcmcia_add(काष्ठा sa1111_dev *dev, काष्ठा pcmcia_low_level *ops,
	पूर्णांक (*add)(काष्ठा soc_pcmcia_socket *));

बाह्य व्योम sa1111_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *, काष्ठा pcmcia_state *);
बाह्य पूर्णांक sa1111_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *, स्थिर socket_state_t *);

बाह्य पूर्णांक pcmcia_badge4_init(काष्ठा sa1111_dev *);
बाह्य पूर्णांक pcmcia_jornada720_init(काष्ठा sa1111_dev *);
बाह्य पूर्णांक pcmcia_lubbock_init(काष्ठा sa1111_dev *);
बाह्य पूर्णांक pcmcia_neponset_init(काष्ठा sa1111_dev *);


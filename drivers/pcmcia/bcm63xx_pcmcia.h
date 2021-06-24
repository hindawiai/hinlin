<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_PCMCIA_H_
#घोषणा BCM63XX_PCMCIA_H_

#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <pcmcia/ss.h>
#समावेश <bcm63xx_dev_pcmcia.h>

/* socket polling rate in ms */
#घोषणा BCM63XX_PCMCIA_POLL_RATE	500

क्रमागत अणु
	CARD_CARDBUS = (1 << 0),
	CARD_PCCARD = (1 << 1),
	CARD_5V = (1 << 2),
	CARD_3V = (1 << 3),
	CARD_XV = (1 << 4),
	CARD_YV = (1 << 5),
पूर्ण;

काष्ठा bcm63xx_pcmcia_socket अणु
	काष्ठा pcmcia_socket socket;

	/* platक्रमm specअगरic data */
	काष्ठा bcm63xx_pcmcia_platक्रमm_data *pd;

	/* all regs access are रक्षित by this spinlock */
	spinlock_t lock;

	/* pcmcia रेजिस्टरs resource */
	काष्ठा resource *reg_res;

	/* base remapped address of रेजिस्टरs */
	व्योम __iomem *base;

	/* whether a card is detected at the moment */
	पूर्णांक card_detected;

	/* type of detected card (mask of above क्रमागत) */
	u8 card_type;

	/* keep last socket status to implement event reporting */
	अचिन्हित पूर्णांक old_status;

	/* backup of requested socket state */
	socket_state_t requested_state;

	/* समयr used क्रम socket status polling */
	काष्ठा समयr_list समयr;

	/* attribute/common memory resources */
	काष्ठा resource *attr_res;
	काष्ठा resource *common_res;
	काष्ठा resource *io_res;

	/* base address of io memory */
	व्योम __iomem *io_base;
पूर्ण;

#पूर्ण_अगर /* BCM63XX_PCMCIA_H_ */

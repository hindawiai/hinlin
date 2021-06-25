<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * omap-mailbox: पूर्णांकerprocessor communication module क्रम OMAP
 */

#अगर_अघोषित OMAP_MAILBOX_H
#घोषणा OMAP_MAILBOX_H

प्रकार uपूर्णांकptr_t mbox_msg_t;

#घोषणा omap_mbox_message(data) (u32)(mbox_msg_t)(data)

प्रकार पूर्णांक __bitwise omap_mbox_irq_t;
#घोषणा IRQ_TX ((__क्रमce omap_mbox_irq_t) 1)
#घोषणा IRQ_RX ((__क्रमce omap_mbox_irq_t) 2)

काष्ठा mbox_chan;
काष्ठा mbox_client;

काष्ठा mbox_chan *omap_mbox_request_channel(काष्ठा mbox_client *cl,
					    स्थिर अक्षर *chan_name);

व्योम omap_mbox_enable_irq(काष्ठा mbox_chan *chan, omap_mbox_irq_t irq);
व्योम omap_mbox_disable_irq(काष्ठा mbox_chan *chan, omap_mbox_irq_t irq);

#पूर्ण_अगर /* OMAP_MAILBOX_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013-2014 Linaro Ltd.
 * Author: Jassi Brar <jassisinghbrar@gmail.com>
 */

#अगर_अघोषित __MAILBOX_CLIENT_H
#घोषणा __MAILBOX_CLIENT_H

#समावेश <linux/of.h>
#समावेश <linux/device.h>

काष्ठा mbox_chan;

/**
 * काष्ठा mbox_client - User of a mailbox
 * @dev:		The client device
 * @tx_block:		If the mbox_send_message should block until data is
 *			transmitted.
 * @tx_tout:		Max block period in ms beक्रमe TX is assumed failure
 * @knows_txकरोne:	If the client could run the TX state machine. Usually
 *			अगर the client receives some ACK packet क्रम transmission.
 *			Unused अगर the controller alपढ़ोy has TX_Done/RTR IRQ.
 * @rx_callback:	Atomic callback to provide client the data received
 * @tx_prepare: 	Atomic callback to ask client to prepare the payload
 *			beक्रमe initiating the transmission अगर required.
 * @tx_करोne:		Atomic callback to tell client of data transmission
 */
काष्ठा mbox_client अणु
	काष्ठा device *dev;
	bool tx_block;
	अचिन्हित दीर्घ tx_tout;
	bool knows_txकरोne;

	व्योम (*rx_callback)(काष्ठा mbox_client *cl, व्योम *mssg);
	व्योम (*tx_prepare)(काष्ठा mbox_client *cl, व्योम *mssg);
	व्योम (*tx_करोne)(काष्ठा mbox_client *cl, व्योम *mssg, पूर्णांक r);
पूर्ण;

काष्ठा mbox_chan *mbox_request_channel_byname(काष्ठा mbox_client *cl,
					      स्थिर अक्षर *name);
काष्ठा mbox_chan *mbox_request_channel(काष्ठा mbox_client *cl, पूर्णांक index);
पूर्णांक mbox_send_message(काष्ठा mbox_chan *chan, व्योम *mssg);
पूर्णांक mbox_flush(काष्ठा mbox_chan *chan, अचिन्हित दीर्घ समयout);
व्योम mbox_client_txकरोne(काष्ठा mbox_chan *chan, पूर्णांक r); /* atomic */
bool mbox_client_peek_data(काष्ठा mbox_chan *chan); /* atomic */
व्योम mbox_मुक्त_channel(काष्ठा mbox_chan *chan); /* may sleep */

#पूर्ण_अगर /* __MAILBOX_CLIENT_H */

<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
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
 *
 */

#समावेश <linux/firmware.h>
#समावेश "rsi_usb.h"

/**
 * rsi_usb_rx_thपढ़ो() - This is a kernel thपढ़ो to receive the packets from
 *			 the USB device.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: None.
 */
व्योम rsi_usb_rx_thपढ़ो(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा rsi_91x_usbdev *dev = (काष्ठा rsi_91x_usbdev *)adapter->rsi_dev;
	पूर्णांक status;
	काष्ठा sk_buff *skb;

	करो अणु
		rsi_रुको_event(&dev->rx_thपढ़ो.event, EVENT_WAIT_FOREVER);
		rsi_reset_event(&dev->rx_thपढ़ो.event);

		जबतक (true) अणु
			अगर (atomic_पढ़ो(&dev->rx_thपढ़ो.thपढ़ो_करोne))
				जाओ out;

			skb = skb_dequeue(&dev->rx_q);
			अगर (!skb)
				अवरोध;
			status = rsi_पढ़ो_pkt(common, skb->data, 0);
			अगर (status) अणु
				rsi_dbg(ERR_ZONE, "%s: Failed To read data",
					__func__);
				अवरोध;
			पूर्ण
			dev_kमुक्त_skb(skb);
		पूर्ण
	पूर्ण जबतक (1);

out:
	rsi_dbg(INFO_ZONE, "%s: Terminated thread\n", __func__);
	skb_queue_purge(&dev->rx_q);
	complete_and_निकास(&dev->rx_thपढ़ो.completion, 0);
पूर्ण


<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth HCI UART driver
 *
 *  Copyright (C) 2000-2001  Qualcomm Incorporated
 *  Copyright (C) 2002-2003  Maxim Krasnyansky <maxk@qualcomm.com>
 *  Copyright (C) 2004-2005  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/poll.h>

#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/skbuff.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"

काष्ठा h4_काष्ठा अणु
	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff_head txq;
पूर्ण;

/* Initialize protocol */
अटल पूर्णांक h4_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा h4_काष्ठा *h4;

	BT_DBG("hu %p", hu);

	h4 = kzalloc(माप(*h4), GFP_KERNEL);
	अगर (!h4)
		वापस -ENOMEM;

	skb_queue_head_init(&h4->txq);

	hu->priv = h4;
	वापस 0;
पूर्ण

/* Flush protocol data */
अटल पूर्णांक h4_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा h4_काष्ठा *h4 = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&h4->txq);

	वापस 0;
पूर्ण

/* Close protocol */
अटल पूर्णांक h4_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा h4_काष्ठा *h4 = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&h4->txq);

	kमुक्त_skb(h4->rx_skb);

	hu->priv = शून्य;
	kमुक्त(h4);

	वापस 0;
पूर्ण

/* Enqueue frame क्रम transmission (padding, crc, etc) */
अटल पूर्णांक h4_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा h4_काष्ठा *h4 = hu->priv;

	BT_DBG("hu %p skb %p", hu, skb);

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);
	skb_queue_tail(&h4->txq, skb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा h4_recv_pkt h4_recv_pkts[] = अणु
	अणु H4_RECV_ACL,   .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_SCO,   .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_EVENT, .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_ISO,   .recv = hci_recv_frame पूर्ण,
पूर्ण;

/* Recv data */
अटल पूर्णांक h4_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा h4_काष्ठा *h4 = hu->priv;

	अगर (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		वापस -EUNATCH;

	h4->rx_skb = h4_recv_buf(hu->hdev, h4->rx_skb, data, count,
				 h4_recv_pkts, ARRAY_SIZE(h4_recv_pkts));
	अगर (IS_ERR(h4->rx_skb)) अणु
		पूर्णांक err = PTR_ERR(h4->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		h4->rx_skb = शून्य;
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा sk_buff *h4_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा h4_काष्ठा *h4 = hu->priv;
	वापस skb_dequeue(&h4->txq);
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto h4p = अणु
	.id		= HCI_UART_H4,
	.name		= "H4",
	.खोलो		= h4_खोलो,
	.बंद		= h4_बंद,
	.recv		= h4_recv,
	.enqueue	= h4_enqueue,
	.dequeue	= h4_dequeue,
	.flush		= h4_flush,
पूर्ण;

पूर्णांक __init h4_init(व्योम)
अणु
	वापस hci_uart_रेजिस्टर_proto(&h4p);
पूर्ण

पूर्णांक __निकास h4_deinit(व्योम)
अणु
	वापस hci_uart_unरेजिस्टर_proto(&h4p);
पूर्ण

काष्ठा sk_buff *h4_recv_buf(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb,
			    स्थिर अचिन्हित अक्षर *buffer, पूर्णांक count,
			    स्थिर काष्ठा h4_recv_pkt *pkts, पूर्णांक pkts_count)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	u8 alignment = hu->alignment ? hu->alignment : 1;

	/* Check क्रम error from previous call */
	अगर (IS_ERR(skb))
		skb = शून्य;

	जबतक (count) अणु
		पूर्णांक i, len;

		/* हटाओ padding bytes from buffer */
		क्रम (; hu->padding && count > 0; hu->padding--) अणु
			count--;
			buffer++;
		पूर्ण
		अगर (!count)
			अवरोध;

		अगर (!skb) अणु
			क्रम (i = 0; i < pkts_count; i++) अणु
				अगर (buffer[0] != (&pkts[i])->type)
					जारी;

				skb = bt_skb_alloc((&pkts[i])->maxlen,
						   GFP_ATOMIC);
				अगर (!skb)
					वापस ERR_PTR(-ENOMEM);

				hci_skb_pkt_type(skb) = (&pkts[i])->type;
				hci_skb_expect(skb) = (&pkts[i])->hlen;
				अवरोध;
			पूर्ण

			/* Check क्रम invalid packet type */
			अगर (!skb)
				वापस ERR_PTR(-EILSEQ);

			count -= 1;
			buffer += 1;
		पूर्ण

		len = min_t(uपूर्णांक, hci_skb_expect(skb) - skb->len, count);
		skb_put_data(skb, buffer, len);

		count -= len;
		buffer += len;

		/* Check क्रम partial packet */
		अगर (skb->len < hci_skb_expect(skb))
			जारी;

		क्रम (i = 0; i < pkts_count; i++) अणु
			अगर (hci_skb_pkt_type(skb) == (&pkts[i])->type)
				अवरोध;
		पूर्ण

		अगर (i >= pkts_count) अणु
			kमुक्त_skb(skb);
			वापस ERR_PTR(-EILSEQ);
		पूर्ण

		अगर (skb->len == (&pkts[i])->hlen) अणु
			u16 dlen;

			चयन ((&pkts[i])->lsize) अणु
			हाल 0:
				/* No variable data length */
				dlen = 0;
				अवरोध;
			हाल 1:
				/* Single octet variable length */
				dlen = skb->data[(&pkts[i])->loff];
				hci_skb_expect(skb) += dlen;

				अगर (skb_tailroom(skb) < dlen) अणु
					kमुक्त_skb(skb);
					वापस ERR_PTR(-EMSGSIZE);
				पूर्ण
				अवरोध;
			हाल 2:
				/* Double octet variable length */
				dlen = get_unaligned_le16(skb->data +
							  (&pkts[i])->loff);
				hci_skb_expect(skb) += dlen;

				अगर (skb_tailroom(skb) < dlen) अणु
					kमुक्त_skb(skb);
					वापस ERR_PTR(-EMSGSIZE);
				पूर्ण
				अवरोध;
			शेष:
				/* Unsupported variable length */
				kमुक्त_skb(skb);
				वापस ERR_PTR(-EILSEQ);
			पूर्ण

			अगर (!dlen) अणु
				hu->padding = (skb->len - 1) % alignment;
				hu->padding = (alignment - hu->padding) % alignment;

				/* No more data, complete frame */
				(&pkts[i])->recv(hdev, skb);
				skb = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			hu->padding = (skb->len - 1) % alignment;
			hu->padding = (alignment - hu->padding) % alignment;

			/* Complete frame */
			(&pkts[i])->recv(hdev, skb);
			skb = शून्य;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(h4_recv_buf);

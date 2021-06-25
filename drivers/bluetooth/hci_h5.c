<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth HCI Three-wire UART driver
 *
 *  Copyright (C) 2012  Intel Corporation
 */

#समावेश <linux/acpi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of_device.h>
#समावेश <linux/serdev.h>
#समावेश <linux/skbuff.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btrtl.h"
#समावेश "hci_uart.h"

#घोषणा HCI_3WIRE_ACK_PKT	0
#घोषणा HCI_3WIRE_LINK_PKT	15

/* Sliding winकरोw size */
#घोषणा H5_TX_WIN_MAX		4

#घोषणा H5_ACK_TIMEOUT	msecs_to_jअगरfies(250)
#घोषणा H5_SYNC_TIMEOUT	msecs_to_jअगरfies(100)

/*
 * Maximum Three-wire packet:
 *     4 byte header + max value क्रम 12-bit length + 2 bytes क्रम CRC
 */
#घोषणा H5_MAX_LEN (4 + 0xfff + 2)

/* Convenience macros क्रम पढ़ोing Three-wire header values */
#घोषणा H5_HDR_SEQ(hdr)		((hdr)[0] & 0x07)
#घोषणा H5_HDR_ACK(hdr)		(((hdr)[0] >> 3) & 0x07)
#घोषणा H5_HDR_CRC(hdr)		(((hdr)[0] >> 6) & 0x01)
#घोषणा H5_HDR_RELIABLE(hdr)	(((hdr)[0] >> 7) & 0x01)
#घोषणा H5_HDR_PKT_TYPE(hdr)	((hdr)[1] & 0x0f)
#घोषणा H5_HDR_LEN(hdr)		((((hdr)[1] >> 4) & 0x0f) + ((hdr)[2] << 4))

#घोषणा SLIP_DELIMITER	0xc0
#घोषणा SLIP_ESC	0xdb
#घोषणा SLIP_ESC_DELIM	0xdc
#घोषणा SLIP_ESC_ESC	0xdd

/* H5 state flags */
क्रमागत अणु
	H5_RX_ESC,	/* SLIP escape mode */
	H5_TX_ACK_REQ,	/* Pending ack to send */
पूर्ण;

काष्ठा h5 अणु
	/* Must be the first member, hci_serdev.c expects this. */
	काष्ठा hci_uart		serdev_hu;

	काष्ठा sk_buff_head	unack;		/* Unack'ed packets queue */
	काष्ठा sk_buff_head	rel;		/* Reliable packets queue */
	काष्ठा sk_buff_head	unrel;		/* Unreliable packets queue */

	अचिन्हित दीर्घ		flags;

	काष्ठा sk_buff		*rx_skb;	/* Receive buffer */
	माप_प्रकार			rx_pending;	/* Expecting more bytes */
	u8			rx_ack;		/* Last ack number received */

	पूर्णांक			(*rx_func)(काष्ठा hci_uart *hu, u8 c);

	काष्ठा समयr_list	समयr;		/* Retransmission समयr */
	काष्ठा hci_uart		*hu;		/* Parent HCI UART */

	u8			tx_seq;		/* Next seq number to send */
	u8			tx_ack;		/* Next ack number to send */
	u8			tx_win;		/* Sliding winकरोw size */

	क्रमागत अणु
		H5_UNINITIALIZED,
		H5_INITIALIZED,
		H5_ACTIVE,
	पूर्ण state;

	क्रमागत अणु
		H5_AWAKE,
		H5_SLEEPING,
		H5_WAKING_UP,
	पूर्ण sleep;

	स्थिर काष्ठा h5_vnd *vnd;
	स्थिर अक्षर *id;

	काष्ठा gpio_desc *enable_gpio;
	काष्ठा gpio_desc *device_wake_gpio;
पूर्ण;

काष्ठा h5_vnd अणु
	पूर्णांक (*setup)(काष्ठा h5 *h5);
	व्योम (*खोलो)(काष्ठा h5 *h5);
	व्योम (*बंद)(काष्ठा h5 *h5);
	पूर्णांक (*suspend)(काष्ठा h5 *h5);
	पूर्णांक (*resume)(काष्ठा h5 *h5);
	स्थिर काष्ठा acpi_gpio_mapping *acpi_gpio_map;
पूर्ण;

अटल व्योम h5_reset_rx(काष्ठा h5 *h5);

अटल व्योम h5_link_control(काष्ठा hci_uart *hu, स्थिर व्योम *data, माप_प्रकार len)
अणु
	काष्ठा h5 *h5 = hu->priv;
	काष्ठा sk_buff *nskb;

	nskb = alloc_skb(3, GFP_ATOMIC);
	अगर (!nskb)
		वापस;

	hci_skb_pkt_type(nskb) = HCI_3WIRE_LINK_PKT;

	skb_put_data(nskb, data, len);

	skb_queue_tail(&h5->unrel, nskb);
पूर्ण

अटल u8 h5_cfg_field(काष्ठा h5 *h5)
अणु
	/* Sliding winकरोw size (first 3 bits) */
	वापस h5->tx_win & 0x07;
पूर्ण

अटल व्योम h5_समयd_event(काष्ठा समयr_list *t)
अणु
	स्थिर अचिन्हित अक्षर sync_req[] = अणु 0x01, 0x7e पूर्ण;
	अचिन्हित अक्षर conf_req[3] = अणु 0x03, 0xfc पूर्ण;
	काष्ठा h5 *h5 = from_समयr(h5, t, समयr);
	काष्ठा hci_uart *hu = h5->hu;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	BT_DBG("%s", hu->hdev->name);

	अगर (h5->state == H5_UNINITIALIZED)
		h5_link_control(hu, sync_req, माप(sync_req));

	अगर (h5->state == H5_INITIALIZED) अणु
		conf_req[2] = h5_cfg_field(h5);
		h5_link_control(hu, conf_req, माप(conf_req));
	पूर्ण

	अगर (h5->state != H5_ACTIVE) अणु
		mod_समयr(&h5->समयr, jअगरfies + H5_SYNC_TIMEOUT);
		जाओ wakeup;
	पूर्ण

	अगर (h5->sleep != H5_AWAKE) अणु
		h5->sleep = H5_SLEEPING;
		जाओ wakeup;
	पूर्ण

	BT_DBG("hu %p retransmitting %u pkts", hu, h5->unack.qlen);

	spin_lock_irqsave_nested(&h5->unack.lock, flags, SINGLE_DEPTH_NESTING);

	जबतक ((skb = __skb_dequeue_tail(&h5->unack)) != शून्य) अणु
		h5->tx_seq = (h5->tx_seq - 1) & 0x07;
		skb_queue_head(&h5->rel, skb);
	पूर्ण

	spin_unlock_irqrestore(&h5->unack.lock, flags);

wakeup:
	hci_uart_tx_wakeup(hu);
पूर्ण

अटल व्योम h5_peer_reset(काष्ठा hci_uart *hu)
अणु
	काष्ठा h5 *h5 = hu->priv;

	bt_dev_err(hu->hdev, "Peer device has reset");

	h5->state = H5_UNINITIALIZED;

	del_समयr(&h5->समयr);

	skb_queue_purge(&h5->rel);
	skb_queue_purge(&h5->unrel);
	skb_queue_purge(&h5->unack);

	h5->tx_seq = 0;
	h5->tx_ack = 0;

	/* Send reset request to upper stack */
	hci_reset_dev(hu->hdev);
पूर्ण

अटल पूर्णांक h5_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा h5 *h5;
	स्थिर अचिन्हित अक्षर sync[] = अणु 0x01, 0x7e पूर्ण;

	BT_DBG("hu %p", hu);

	अगर (hu->serdev) अणु
		h5 = serdev_device_get_drvdata(hu->serdev);
	पूर्ण अन्यथा अणु
		h5 = kzalloc(माप(*h5), GFP_KERNEL);
		अगर (!h5)
			वापस -ENOMEM;
	पूर्ण

	hu->priv = h5;
	h5->hu = hu;

	skb_queue_head_init(&h5->unack);
	skb_queue_head_init(&h5->rel);
	skb_queue_head_init(&h5->unrel);

	h5_reset_rx(h5);

	समयr_setup(&h5->समयr, h5_समयd_event, 0);

	h5->tx_win = H5_TX_WIN_MAX;

	अगर (h5->vnd && h5->vnd->खोलो)
		h5->vnd->खोलो(h5);

	set_bit(HCI_UART_INIT_PENDING, &hu->hdev_flags);

	/* Send initial sync request */
	h5_link_control(hu, sync, माप(sync));
	mod_समयr(&h5->समयr, jअगरfies + H5_SYNC_TIMEOUT);

	वापस 0;
पूर्ण

अटल पूर्णांक h5_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा h5 *h5 = hu->priv;

	del_समयr_sync(&h5->समयr);

	skb_queue_purge(&h5->unack);
	skb_queue_purge(&h5->rel);
	skb_queue_purge(&h5->unrel);

	kमुक्त_skb(h5->rx_skb);
	h5->rx_skb = शून्य;

	अगर (h5->vnd && h5->vnd->बंद)
		h5->vnd->बंद(h5);

	अगर (!hu->serdev)
		kमुक्त(h5);

	वापस 0;
पूर्ण

अटल पूर्णांक h5_setup(काष्ठा hci_uart *hu)
अणु
	काष्ठा h5 *h5 = hu->priv;

	अगर (h5->vnd && h5->vnd->setup)
		वापस h5->vnd->setup(h5);

	वापस 0;
पूर्ण

अटल व्योम h5_pkt_cull(काष्ठा h5 *h5)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, to_हटाओ;
	u8 seq;

	spin_lock_irqsave(&h5->unack.lock, flags);

	to_हटाओ = skb_queue_len(&h5->unack);
	अगर (to_हटाओ == 0)
		जाओ unlock;

	seq = h5->tx_seq;

	जबतक (to_हटाओ > 0) अणु
		अगर (h5->rx_ack == seq)
			अवरोध;

		to_हटाओ--;
		seq = (seq - 1) & 0x07;
	पूर्ण

	अगर (seq != h5->rx_ack)
		BT_ERR("Controller acked invalid packet");

	i = 0;
	skb_queue_walk_safe(&h5->unack, skb, पंचांगp) अणु
		अगर (i++ >= to_हटाओ)
			अवरोध;

		__skb_unlink(skb, &h5->unack);
		kमुक्त_skb(skb);
	पूर्ण

	अगर (skb_queue_empty(&h5->unack))
		del_समयr(&h5->समयr);

unlock:
	spin_unlock_irqrestore(&h5->unack.lock, flags);
पूर्ण

अटल व्योम h5_handle_पूर्णांकernal_rx(काष्ठा hci_uart *hu)
अणु
	काष्ठा h5 *h5 = hu->priv;
	स्थिर अचिन्हित अक्षर sync_req[] = अणु 0x01, 0x7e पूर्ण;
	स्थिर अचिन्हित अक्षर sync_rsp[] = अणु 0x02, 0x7d पूर्ण;
	अचिन्हित अक्षर conf_req[3] = अणु 0x03, 0xfc पूर्ण;
	स्थिर अचिन्हित अक्षर conf_rsp[] = अणु 0x04, 0x7b पूर्ण;
	स्थिर अचिन्हित अक्षर wakeup_req[] = अणु 0x05, 0xfa पूर्ण;
	स्थिर अचिन्हित अक्षर woken_req[] = अणु 0x06, 0xf9 पूर्ण;
	स्थिर अचिन्हित अक्षर sleep_req[] = अणु 0x07, 0x78 पूर्ण;
	स्थिर अचिन्हित अक्षर *hdr = h5->rx_skb->data;
	स्थिर अचिन्हित अक्षर *data = &h5->rx_skb->data[4];

	BT_DBG("%s", hu->hdev->name);

	अगर (H5_HDR_PKT_TYPE(hdr) != HCI_3WIRE_LINK_PKT)
		वापस;

	अगर (H5_HDR_LEN(hdr) < 2)
		वापस;

	conf_req[2] = h5_cfg_field(h5);

	अगर (स_भेद(data, sync_req, 2) == 0) अणु
		अगर (h5->state == H5_ACTIVE)
			h5_peer_reset(hu);
		h5_link_control(hu, sync_rsp, 2);
	पूर्ण अन्यथा अगर (स_भेद(data, sync_rsp, 2) == 0) अणु
		अगर (h5->state == H5_ACTIVE)
			h5_peer_reset(hu);
		h5->state = H5_INITIALIZED;
		h5_link_control(hu, conf_req, 3);
	पूर्ण अन्यथा अगर (स_भेद(data, conf_req, 2) == 0) अणु
		h5_link_control(hu, conf_rsp, 2);
		h5_link_control(hu, conf_req, 3);
	पूर्ण अन्यथा अगर (स_भेद(data, conf_rsp, 2) == 0) अणु
		अगर (H5_HDR_LEN(hdr) > 2)
			h5->tx_win = (data[2] & 0x07);
		BT_DBG("Three-wire init complete. tx_win %u", h5->tx_win);
		h5->state = H5_ACTIVE;
		hci_uart_init_पढ़ोy(hu);
		वापस;
	पूर्ण अन्यथा अगर (स_भेद(data, sleep_req, 2) == 0) अणु
		BT_DBG("Peer went to sleep");
		h5->sleep = H5_SLEEPING;
		वापस;
	पूर्ण अन्यथा अगर (स_भेद(data, woken_req, 2) == 0) अणु
		BT_DBG("Peer woke up");
		h5->sleep = H5_AWAKE;
	पूर्ण अन्यथा अगर (स_भेद(data, wakeup_req, 2) == 0) अणु
		BT_DBG("Peer requested wakeup");
		h5_link_control(hu, woken_req, 2);
		h5->sleep = H5_AWAKE;
	पूर्ण अन्यथा अणु
		BT_DBG("Link Control: 0x%02hhx 0x%02hhx", data[0], data[1]);
		वापस;
	पूर्ण

	hci_uart_tx_wakeup(hu);
पूर्ण

अटल व्योम h5_complete_rx_pkt(काष्ठा hci_uart *hu)
अणु
	काष्ठा h5 *h5 = hu->priv;
	स्थिर अचिन्हित अक्षर *hdr = h5->rx_skb->data;

	अगर (H5_HDR_RELIABLE(hdr)) अणु
		h5->tx_ack = (h5->tx_ack + 1) % 8;
		set_bit(H5_TX_ACK_REQ, &h5->flags);
		hci_uart_tx_wakeup(hu);
	पूर्ण

	h5->rx_ack = H5_HDR_ACK(hdr);

	h5_pkt_cull(h5);

	चयन (H5_HDR_PKT_TYPE(hdr)) अणु
	हाल HCI_EVENT_PKT:
	हाल HCI_ACLDATA_PKT:
	हाल HCI_SCODATA_PKT:
	हाल HCI_ISODATA_PKT:
		hci_skb_pkt_type(h5->rx_skb) = H5_HDR_PKT_TYPE(hdr);

		/* Remove Three-wire header */
		skb_pull(h5->rx_skb, 4);

		hci_recv_frame(hu->hdev, h5->rx_skb);
		h5->rx_skb = शून्य;

		अवरोध;

	शेष:
		h5_handle_पूर्णांकernal_rx(hu);
		अवरोध;
	पूर्ण

	h5_reset_rx(h5);
पूर्ण

अटल पूर्णांक h5_rx_crc(काष्ठा hci_uart *hu, अचिन्हित अक्षर c)
अणु
	h5_complete_rx_pkt(hu);

	वापस 0;
पूर्ण

अटल पूर्णांक h5_rx_payload(काष्ठा hci_uart *hu, अचिन्हित अक्षर c)
अणु
	काष्ठा h5 *h5 = hu->priv;
	स्थिर अचिन्हित अक्षर *hdr = h5->rx_skb->data;

	अगर (H5_HDR_CRC(hdr)) अणु
		h5->rx_func = h5_rx_crc;
		h5->rx_pending = 2;
	पूर्ण अन्यथा अणु
		h5_complete_rx_pkt(hu);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक h5_rx_3wire_hdr(काष्ठा hci_uart *hu, अचिन्हित अक्षर c)
अणु
	काष्ठा h5 *h5 = hu->priv;
	स्थिर अचिन्हित अक्षर *hdr = h5->rx_skb->data;

	BT_DBG("%s rx: seq %u ack %u crc %u rel %u type %u len %u",
	       hu->hdev->name, H5_HDR_SEQ(hdr), H5_HDR_ACK(hdr),
	       H5_HDR_CRC(hdr), H5_HDR_RELIABLE(hdr), H5_HDR_PKT_TYPE(hdr),
	       H5_HDR_LEN(hdr));

	अगर (((hdr[0] + hdr[1] + hdr[2] + hdr[3]) & 0xff) != 0xff) अणु
		bt_dev_err(hu->hdev, "Invalid header checksum");
		h5_reset_rx(h5);
		वापस 0;
	पूर्ण

	अगर (H5_HDR_RELIABLE(hdr) && H5_HDR_SEQ(hdr) != h5->tx_ack) अणु
		bt_dev_err(hu->hdev, "Out-of-order packet arrived (%u != %u)",
			   H5_HDR_SEQ(hdr), h5->tx_ack);
		h5_reset_rx(h5);
		वापस 0;
	पूर्ण

	अगर (h5->state != H5_ACTIVE &&
	    H5_HDR_PKT_TYPE(hdr) != HCI_3WIRE_LINK_PKT) अणु
		bt_dev_err(hu->hdev, "Non-link packet received in non-active state");
		h5_reset_rx(h5);
		वापस 0;
	पूर्ण

	h5->rx_func = h5_rx_payload;
	h5->rx_pending = H5_HDR_LEN(hdr);

	वापस 0;
पूर्ण

अटल पूर्णांक h5_rx_pkt_start(काष्ठा hci_uart *hu, अचिन्हित अक्षर c)
अणु
	काष्ठा h5 *h5 = hu->priv;

	अगर (c == SLIP_DELIMITER)
		वापस 1;

	h5->rx_func = h5_rx_3wire_hdr;
	h5->rx_pending = 4;

	h5->rx_skb = bt_skb_alloc(H5_MAX_LEN, GFP_ATOMIC);
	अगर (!h5->rx_skb) अणु
		bt_dev_err(hu->hdev, "Can't allocate mem for new packet");
		h5_reset_rx(h5);
		वापस -ENOMEM;
	पूर्ण

	h5->rx_skb->dev = (व्योम *)hu->hdev;

	वापस 0;
पूर्ण

अटल पूर्णांक h5_rx_delimiter(काष्ठा hci_uart *hu, अचिन्हित अक्षर c)
अणु
	काष्ठा h5 *h5 = hu->priv;

	अगर (c == SLIP_DELIMITER)
		h5->rx_func = h5_rx_pkt_start;

	वापस 1;
पूर्ण

अटल व्योम h5_unslip_one_byte(काष्ठा h5 *h5, अचिन्हित अक्षर c)
अणु
	स्थिर u8 delim = SLIP_DELIMITER, esc = SLIP_ESC;
	स्थिर u8 *byte = &c;

	अगर (!test_bit(H5_RX_ESC, &h5->flags) && c == SLIP_ESC) अणु
		set_bit(H5_RX_ESC, &h5->flags);
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(H5_RX_ESC, &h5->flags)) अणु
		चयन (c) अणु
		हाल SLIP_ESC_DELIM:
			byte = &delim;
			अवरोध;
		हाल SLIP_ESC_ESC:
			byte = &esc;
			अवरोध;
		शेष:
			BT_ERR("Invalid esc byte 0x%02hhx", c);
			h5_reset_rx(h5);
			वापस;
		पूर्ण
	पूर्ण

	skb_put_data(h5->rx_skb, byte, 1);
	h5->rx_pending--;

	BT_DBG("unslipped 0x%02hhx, rx_pending %zu", *byte, h5->rx_pending);
पूर्ण

अटल व्योम h5_reset_rx(काष्ठा h5 *h5)
अणु
	अगर (h5->rx_skb) अणु
		kमुक्त_skb(h5->rx_skb);
		h5->rx_skb = शून्य;
	पूर्ण

	h5->rx_func = h5_rx_delimiter;
	h5->rx_pending = 0;
	clear_bit(H5_RX_ESC, &h5->flags);
पूर्ण

अटल पूर्णांक h5_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा h5 *h5 = hu->priv;
	स्थिर अचिन्हित अक्षर *ptr = data;

	BT_DBG("%s pending %zu count %d", hu->hdev->name, h5->rx_pending,
	       count);

	जबतक (count > 0) अणु
		पूर्णांक processed;

		अगर (h5->rx_pending > 0) अणु
			अगर (*ptr == SLIP_DELIMITER) अणु
				bt_dev_err(hu->hdev, "Too short H5 packet");
				h5_reset_rx(h5);
				जारी;
			पूर्ण

			h5_unslip_one_byte(h5, *ptr);

			ptr++; count--;
			जारी;
		पूर्ण

		processed = h5->rx_func(hu, *ptr);
		अगर (processed < 0)
			वापस processed;

		ptr += processed;
		count -= processed;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक h5_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा h5 *h5 = hu->priv;

	अगर (skb->len > 0xfff) अणु
		bt_dev_err(hu->hdev, "Packet too long (%u bytes)", skb->len);
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (h5->state != H5_ACTIVE) अणु
		bt_dev_err(hu->hdev, "Ignoring HCI data in non-active state");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_ACLDATA_PKT:
	हाल HCI_COMMAND_PKT:
		skb_queue_tail(&h5->rel, skb);
		अवरोध;

	हाल HCI_SCODATA_PKT:
	हाल HCI_ISODATA_PKT:
		skb_queue_tail(&h5->unrel, skb);
		अवरोध;

	शेष:
		bt_dev_err(hu->hdev, "Unknown packet type %u", hci_skb_pkt_type(skb));
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम h5_slip_delim(काष्ठा sk_buff *skb)
अणु
	स्थिर अक्षर delim = SLIP_DELIMITER;

	skb_put_data(skb, &delim, 1);
पूर्ण

अटल व्योम h5_slip_one_byte(काष्ठा sk_buff *skb, u8 c)
अणु
	स्थिर अक्षर esc_delim[2] = अणु SLIP_ESC, SLIP_ESC_DELIM पूर्ण;
	स्थिर अक्षर esc_esc[2] = अणु SLIP_ESC, SLIP_ESC_ESC पूर्ण;

	चयन (c) अणु
	हाल SLIP_DELIMITER:
		skb_put_data(skb, &esc_delim, 2);
		अवरोध;
	हाल SLIP_ESC:
		skb_put_data(skb, &esc_esc, 2);
		अवरोध;
	शेष:
		skb_put_data(skb, &c, 1);
	पूर्ण
पूर्ण

अटल bool valid_packet_type(u8 type)
अणु
	चयन (type) अणु
	हाल HCI_ACLDATA_PKT:
	हाल HCI_COMMAND_PKT:
	हाल HCI_SCODATA_PKT:
	हाल HCI_ISODATA_PKT:
	हाल HCI_3WIRE_LINK_PKT:
	हाल HCI_3WIRE_ACK_PKT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *h5_prepare_pkt(काष्ठा hci_uart *hu, u8 pkt_type,
				      स्थिर u8 *data, माप_प्रकार len)
अणु
	काष्ठा h5 *h5 = hu->priv;
	काष्ठा sk_buff *nskb;
	u8 hdr[4];
	पूर्णांक i;

	अगर (!valid_packet_type(pkt_type)) अणु
		bt_dev_err(hu->hdev, "Unknown packet type %u", pkt_type);
		वापस शून्य;
	पूर्ण

	/*
	 * Max len of packet: (original len + 4 (H5 hdr) + 2 (crc)) * 2
	 * (because bytes 0xc0 and 0xdb are escaped, worst हाल is when
	 * the packet is all made of 0xc0 and 0xdb) + 2 (0xc0
	 * delimiters at start and end).
	 */
	nskb = alloc_skb((len + 6) * 2 + 2, GFP_ATOMIC);
	अगर (!nskb)
		वापस शून्य;

	hci_skb_pkt_type(nskb) = pkt_type;

	h5_slip_delim(nskb);

	hdr[0] = h5->tx_ack << 3;
	clear_bit(H5_TX_ACK_REQ, &h5->flags);

	/* Reliable packet? */
	अगर (pkt_type == HCI_ACLDATA_PKT || pkt_type == HCI_COMMAND_PKT) अणु
		hdr[0] |= 1 << 7;
		hdr[0] |= h5->tx_seq;
		h5->tx_seq = (h5->tx_seq + 1) % 8;
	पूर्ण

	hdr[1] = pkt_type | ((len & 0x0f) << 4);
	hdr[2] = len >> 4;
	hdr[3] = ~((hdr[0] + hdr[1] + hdr[2]) & 0xff);

	BT_DBG("%s tx: seq %u ack %u crc %u rel %u type %u len %u",
	       hu->hdev->name, H5_HDR_SEQ(hdr), H5_HDR_ACK(hdr),
	       H5_HDR_CRC(hdr), H5_HDR_RELIABLE(hdr), H5_HDR_PKT_TYPE(hdr),
	       H5_HDR_LEN(hdr));

	क्रम (i = 0; i < 4; i++)
		h5_slip_one_byte(nskb, hdr[i]);

	क्रम (i = 0; i < len; i++)
		h5_slip_one_byte(nskb, data[i]);

	h5_slip_delim(nskb);

	वापस nskb;
पूर्ण

अटल काष्ठा sk_buff *h5_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा h5 *h5 = hu->priv;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb, *nskb;

	अगर (h5->sleep != H5_AWAKE) अणु
		स्थिर अचिन्हित अक्षर wakeup_req[] = अणु 0x05, 0xfa पूर्ण;

		अगर (h5->sleep == H5_WAKING_UP)
			वापस शून्य;

		h5->sleep = H5_WAKING_UP;
		BT_DBG("Sending wakeup request");

		mod_समयr(&h5->समयr, jअगरfies + HZ / 100);
		वापस h5_prepare_pkt(hu, HCI_3WIRE_LINK_PKT, wakeup_req, 2);
	पूर्ण

	skb = skb_dequeue(&h5->unrel);
	अगर (skb) अणु
		nskb = h5_prepare_pkt(hu, hci_skb_pkt_type(skb),
				      skb->data, skb->len);
		अगर (nskb) अणु
			kमुक्त_skb(skb);
			वापस nskb;
		पूर्ण

		skb_queue_head(&h5->unrel, skb);
		bt_dev_err(hu->hdev, "Could not dequeue pkt because alloc_skb failed");
	पूर्ण

	spin_lock_irqsave_nested(&h5->unack.lock, flags, SINGLE_DEPTH_NESTING);

	अगर (h5->unack.qlen >= h5->tx_win)
		जाओ unlock;

	skb = skb_dequeue(&h5->rel);
	अगर (skb) अणु
		nskb = h5_prepare_pkt(hu, hci_skb_pkt_type(skb),
				      skb->data, skb->len);
		अगर (nskb) अणु
			__skb_queue_tail(&h5->unack, skb);
			mod_समयr(&h5->समयr, jअगरfies + H5_ACK_TIMEOUT);
			spin_unlock_irqrestore(&h5->unack.lock, flags);
			वापस nskb;
		पूर्ण

		skb_queue_head(&h5->rel, skb);
		bt_dev_err(hu->hdev, "Could not dequeue pkt because alloc_skb failed");
	पूर्ण

unlock:
	spin_unlock_irqrestore(&h5->unack.lock, flags);

	अगर (test_bit(H5_TX_ACK_REQ, &h5->flags))
		वापस h5_prepare_pkt(hu, HCI_3WIRE_ACK_PKT, शून्य, 0);

	वापस शून्य;
पूर्ण

अटल पूर्णांक h5_flush(काष्ठा hci_uart *hu)
अणु
	BT_DBG("hu %p", hu);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto h5p = अणु
	.id		= HCI_UART_3WIRE,
	.name		= "Three-wire (H5)",
	.खोलो		= h5_खोलो,
	.बंद		= h5_बंद,
	.setup		= h5_setup,
	.recv		= h5_recv,
	.enqueue	= h5_enqueue,
	.dequeue	= h5_dequeue,
	.flush		= h5_flush,
पूर्ण;

अटल पूर्णांक h5_serdev_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा device *dev = &serdev->dev;
	काष्ठा h5 *h5;

	h5 = devm_kzalloc(dev, माप(*h5), GFP_KERNEL);
	अगर (!h5)
		वापस -ENOMEM;

	h5->hu = &h5->serdev_hu;
	h5->serdev_hu.serdev = serdev;
	serdev_device_set_drvdata(serdev, h5);

	अगर (has_acpi_companion(dev)) अणु
		स्थिर काष्ठा acpi_device_id *match;

		match = acpi_match_device(dev->driver->acpi_match_table, dev);
		अगर (!match)
			वापस -ENODEV;

		h5->vnd = (स्थिर काष्ठा h5_vnd *)match->driver_data;
		h5->id  = (अक्षर *)match->id;

		अगर (h5->vnd->acpi_gpio_map)
			devm_acpi_dev_add_driver_gpios(dev,
						       h5->vnd->acpi_gpio_map);
	पूर्ण अन्यथा अणु
		स्थिर व्योम *data;

		data = of_device_get_match_data(dev);
		अगर (!data)
			वापस -ENODEV;

		h5->vnd = (स्थिर काष्ठा h5_vnd *)data;
	पूर्ण


	h5->enable_gpio = devm_gpiod_get_optional(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(h5->enable_gpio))
		वापस PTR_ERR(h5->enable_gpio);

	h5->device_wake_gpio = devm_gpiod_get_optional(dev, "device-wake",
						       GPIOD_OUT_LOW);
	अगर (IS_ERR(h5->device_wake_gpio))
		वापस PTR_ERR(h5->device_wake_gpio);

	वापस hci_uart_रेजिस्टर_device(&h5->serdev_hu, &h5p);
पूर्ण

अटल व्योम h5_serdev_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा h5 *h5 = serdev_device_get_drvdata(serdev);

	hci_uart_unरेजिस्टर_device(&h5->serdev_hu);
पूर्ण

अटल पूर्णांक __maybe_unused h5_serdev_suspend(काष्ठा device *dev)
अणु
	काष्ठा h5 *h5 = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (h5->vnd && h5->vnd->suspend)
		ret = h5->vnd->suspend(h5);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused h5_serdev_resume(काष्ठा device *dev)
अणु
	काष्ठा h5 *h5 = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (h5->vnd && h5->vnd->resume)
		ret = h5->vnd->resume(h5);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_BT_HCIUART_RTL
अटल पूर्णांक h5_btrtl_setup(काष्ठा h5 *h5)
अणु
	काष्ठा btrtl_device_info *btrtl_dev;
	काष्ठा sk_buff *skb;
	__le32 baudrate_data;
	u32 device_baudrate;
	अचिन्हित पूर्णांक controller_baudrate;
	bool flow_control;
	पूर्णांक err;

	btrtl_dev = btrtl_initialize(h5->hu->hdev, h5->id);
	अगर (IS_ERR(btrtl_dev))
		वापस PTR_ERR(btrtl_dev);

	err = btrtl_get_uart_settings(h5->hu->hdev, btrtl_dev,
				      &controller_baudrate, &device_baudrate,
				      &flow_control);
	अगर (err)
		जाओ out_मुक्त;

	baudrate_data = cpu_to_le32(device_baudrate);
	skb = __hci_cmd_sync(h5->hu->hdev, 0xfc17, माप(baudrate_data),
			     &baudrate_data, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		rtl_dev_err(h5->hu->hdev, "set baud rate command failed\n");
		err = PTR_ERR(skb);
		जाओ out_मुक्त;
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
	/* Give the device some समय to set up the new baudrate. */
	usleep_range(10000, 20000);

	serdev_device_set_baudrate(h5->hu->serdev, controller_baudrate);
	serdev_device_set_flow_control(h5->hu->serdev, flow_control);

	err = btrtl_करोwnload_firmware(h5->hu->hdev, btrtl_dev);
	/* Give the device some समय beक्रमe the hci-core sends it a reset */
	usleep_range(10000, 20000);

	/* Enable controller to करो both LE scan and BR/EDR inquiry
	 * simultaneously.
	 */
	set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &h5->hu->hdev->quirks);

out_मुक्त:
	btrtl_मुक्त(btrtl_dev);

	वापस err;
पूर्ण

अटल व्योम h5_btrtl_खोलो(काष्ठा h5 *h5)
अणु
	/* Devices always start with these fixed parameters */
	serdev_device_set_flow_control(h5->hu->serdev, false);
	serdev_device_set_parity(h5->hu->serdev, SERDEV_PARITY_EVEN);
	serdev_device_set_baudrate(h5->hu->serdev, 115200);

	/* The controller needs up to 500ms to wakeup */
	gpiod_set_value_cansleep(h5->enable_gpio, 1);
	gpiod_set_value_cansleep(h5->device_wake_gpio, 1);
	msleep(500);
पूर्ण

अटल व्योम h5_btrtl_बंद(काष्ठा h5 *h5)
अणु
	gpiod_set_value_cansleep(h5->device_wake_gpio, 0);
	gpiod_set_value_cansleep(h5->enable_gpio, 0);
पूर्ण

/* Suspend/resume support. On many devices the RTL BT device loses घातer during
 * suspend/resume, causing it to lose its firmware and all state. So we simply
 * turn it off on suspend and reprobe on resume.  This mirrors how RTL devices
 * are handled in the USB driver, where the USB_QUIRK_RESET_RESUME is used which
 * also causes a reprobe on resume.
 */
अटल पूर्णांक h5_btrtl_suspend(काष्ठा h5 *h5)
अणु
	serdev_device_set_flow_control(h5->hu->serdev, false);
	gpiod_set_value_cansleep(h5->device_wake_gpio, 0);
	gpiod_set_value_cansleep(h5->enable_gpio, 0);
	वापस 0;
पूर्ण

काष्ठा h5_btrtl_reprobe अणु
	काष्ठा device *dev;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल व्योम h5_btrtl_reprobe_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा h5_btrtl_reprobe *reprobe =
		container_of(work, काष्ठा h5_btrtl_reprobe, work);
	पूर्णांक ret;

	ret = device_reprobe(reprobe->dev);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(reprobe->dev, "Reprobe error %d\n", ret);

	put_device(reprobe->dev);
	kमुक्त(reprobe);
	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक h5_btrtl_resume(काष्ठा h5 *h5)
अणु
	काष्ठा h5_btrtl_reprobe *reprobe;

	reprobe = kzalloc(माप(*reprobe), GFP_KERNEL);
	अगर (!reprobe)
		वापस -ENOMEM;

	__module_get(THIS_MODULE);

	INIT_WORK(&reprobe->work, h5_btrtl_reprobe_worker);
	reprobe->dev = get_device(&h5->hu->serdev->dev);
	queue_work(प्रणाली_दीर्घ_wq, &reprobe->work);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_gpio_params btrtl_device_wake_gpios = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params btrtl_enable_gpios = अणु 1, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params btrtl_host_wake_gpios = अणु 2, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_mapping acpi_btrtl_gpios[] = अणु
	अणु "device-wake-gpios", &btrtl_device_wake_gpios, 1 पूर्ण,
	अणु "enable-gpios", &btrtl_enable_gpios, 1 पूर्ण,
	अणु "host-wake-gpios", &btrtl_host_wake_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा h5_vnd rtl_vnd = अणु
	.setup		= h5_btrtl_setup,
	.खोलो		= h5_btrtl_खोलो,
	.बंद		= h5_btrtl_बंद,
	.suspend	= h5_btrtl_suspend,
	.resume		= h5_btrtl_resume,
	.acpi_gpio_map	= acpi_btrtl_gpios,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id h5_acpi_match[] = अणु
#अगर_घोषित CONFIG_BT_HCIUART_RTL
	अणु "OBDA0623", (kernel_uदीर्घ_t)&rtl_vnd पूर्ण,
	अणु "OBDA8723", (kernel_uदीर्घ_t)&rtl_vnd पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, h5_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops h5_serdev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(h5_serdev_suspend, h5_serdev_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id rtl_bluetooth_of_match[] = अणु
#अगर_घोषित CONFIG_BT_HCIUART_RTL
	अणु .compatible = "realtek,rtl8822cs-bt",
	  .data = (स्थिर व्योम *)&rtl_vnd पूर्ण,
	अणु .compatible = "realtek,rtl8723bs-bt",
	  .data = (स्थिर व्योम *)&rtl_vnd पूर्ण,
	अणु .compatible = "realtek,rtl8723ds-bt",
	  .data = (स्थिर व्योम *)&rtl_vnd पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rtl_bluetooth_of_match);

अटल काष्ठा serdev_device_driver h5_serdev_driver = अणु
	.probe = h5_serdev_probe,
	.हटाओ = h5_serdev_हटाओ,
	.driver = अणु
		.name = "hci_uart_h5",
		.acpi_match_table = ACPI_PTR(h5_acpi_match),
		.pm = &h5_serdev_pm_ops,
		.of_match_table = rtl_bluetooth_of_match,
	पूर्ण,
पूर्ण;

पूर्णांक __init h5_init(व्योम)
अणु
	serdev_device_driver_रेजिस्टर(&h5_serdev_driver);
	वापस hci_uart_रेजिस्टर_proto(&h5p);
पूर्ण

पूर्णांक __निकास h5_deinit(व्योम)
अणु
	serdev_device_driver_unरेजिस्टर(&h5_serdev_driver);
	वापस hci_uart_unरेजिस्टर_proto(&h5p);
पूर्ण

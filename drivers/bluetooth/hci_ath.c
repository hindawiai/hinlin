<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Atheros Communication Bluetooth HCIATH3K UART protocol
 *
 *  HCIATH3K (HCI Atheros AR300x Protocol) is a Atheros Communication's
 *  घातer management protocol extension to H4 to support AR300x Bluetooth Chip.
 *
 *  Copyright (c) 2009-2010 Atheros Communications Inc.
 *
 *  Acknowledgements:
 *  This file is based on hci_h4.c, which was written
 *  by Maxim Krasnyansky and Marcel Holपंचांगann.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/skbuff.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"

काष्ठा ath_काष्ठा अणु
	काष्ठा hci_uart *hu;
	अचिन्हित पूर्णांक cur_sleep;

	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff_head txq;
	काष्ठा work_काष्ठा ctxtsw;
पूर्ण;

#घोषणा OP_WRITE_TAG	0x01

#घोषणा INDEX_BDADDR	0x01

काष्ठा ath_venकरोr_cmd अणु
	__u8 opcode;
	__le16 index;
	__u8 len;
	__u8 data[251];
पूर्ण __packed;

अटल पूर्णांक ath_wakeup_ar3k(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक status = tty->driver->ops->tiocmget(tty);

	अगर (status & TIOCM_CTS)
		वापस status;

	/* Clear RTS first */
	tty->driver->ops->tiocmget(tty);
	tty->driver->ops->tiocmset(tty, 0x00, TIOCM_RTS);
	msleep(20);

	/* Set RTS, wake up board */
	tty->driver->ops->tiocmget(tty);
	tty->driver->ops->tiocmset(tty, TIOCM_RTS, 0x00);
	msleep(20);

	status = tty->driver->ops->tiocmget(tty);
	वापस status;
पूर्ण

अटल व्योम ath_hci_uart_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक status;
	काष्ठा ath_काष्ठा *ath;
	काष्ठा hci_uart *hu;
	काष्ठा tty_काष्ठा *tty;

	ath = container_of(work, काष्ठा ath_काष्ठा, ctxtsw);

	hu = ath->hu;
	tty = hu->tty;

	/* verअगरy and wake up controller */
	अगर (ath->cur_sleep) अणु
		status = ath_wakeup_ar3k(tty);
		अगर (!(status & TIOCM_CTS))
			वापस;
	पूर्ण

	/* Ready to send Data */
	clear_bit(HCI_UART_SENDING, &hu->tx_state);
	hci_uart_tx_wakeup(hu);
पूर्ण

अटल पूर्णांक ath_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा ath_काष्ठा *ath;

	BT_DBG("hu %p", hu);

	अगर (!hci_uart_has_flow_control(hu))
		वापस -EOPNOTSUPP;

	ath = kzalloc(माप(*ath), GFP_KERNEL);
	अगर (!ath)
		वापस -ENOMEM;

	skb_queue_head_init(&ath->txq);

	hu->priv = ath;
	ath->hu = hu;

	INIT_WORK(&ath->ctxtsw, ath_hci_uart_work);

	वापस 0;
पूर्ण

अटल पूर्णांक ath_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा ath_काष्ठा *ath = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ath->txq);

	kमुक्त_skb(ath->rx_skb);

	cancel_work_sync(&ath->ctxtsw);

	hu->priv = शून्य;
	kमुक्त(ath);

	वापस 0;
पूर्ण

अटल पूर्णांक ath_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा ath_काष्ठा *ath = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ath->txq);

	वापस 0;
पूर्ण

अटल पूर्णांक ath_venकरोr_cmd(काष्ठा hci_dev *hdev, uपूर्णांक8_t opcode, uपूर्णांक16_t index,
			  स्थिर व्योम *data, माप_प्रकार dlen)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ath_venकरोr_cmd cmd;

	अगर (dlen > माप(cmd.data))
		वापस -EINVAL;

	cmd.opcode = opcode;
	cmd.index = cpu_to_le16(index);
	cmd.len = dlen;
	स_नकल(cmd.data, data, dlen);

	skb = __hci_cmd_sync(hdev, 0xfc0b, dlen + 4, &cmd, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक ath_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	वापस ath_venकरोr_cmd(hdev, OP_WRITE_TAG, INDEX_BDADDR, bdaddr,
			      माप(*bdaddr));
पूर्ण

अटल पूर्णांक ath_setup(काष्ठा hci_uart *hu)
अणु
	BT_DBG("hu %p", hu);

	hu->hdev->set_bdaddr = ath_set_bdaddr;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा h4_recv_pkt ath_recv_pkts[] = अणु
	अणु H4_RECV_ACL,   .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_SCO,   .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_EVENT, .recv = hci_recv_frame पूर्ण,
पूर्ण;

अटल पूर्णांक ath_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा ath_काष्ठा *ath = hu->priv;

	ath->rx_skb = h4_recv_buf(hu->hdev, ath->rx_skb, data, count,
				  ath_recv_pkts, ARRAY_SIZE(ath_recv_pkts));
	अगर (IS_ERR(ath->rx_skb)) अणु
		पूर्णांक err = PTR_ERR(ath->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		ath->rx_skb = शून्य;
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

#घोषणा HCI_OP_ATH_SLEEP 0xFC04

अटल पूर्णांक ath_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath_काष्ठा *ath = hu->priv;

	अगर (hci_skb_pkt_type(skb) == HCI_SCODATA_PKT) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	/* Update घातer management enable flag with parameters of
	 * HCI sleep enable venकरोr specअगरic HCI command.
	 */
	अगर (hci_skb_pkt_type(skb) == HCI_COMMAND_PKT) अणु
		काष्ठा hci_command_hdr *hdr = (व्योम *)skb->data;

		अगर (__le16_to_cpu(hdr->opcode) == HCI_OP_ATH_SLEEP)
			ath->cur_sleep = skb->data[HCI_COMMAND_HDR_SIZE];
	पूर्ण

	BT_DBG("hu %p skb %p", hu, skb);

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	skb_queue_tail(&ath->txq, skb);
	set_bit(HCI_UART_SENDING, &hu->tx_state);

	schedule_work(&ath->ctxtsw);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *ath_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा ath_काष्ठा *ath = hu->priv;

	वापस skb_dequeue(&ath->txq);
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto athp = अणु
	.id		= HCI_UART_ATH3K,
	.name		= "ATH3K",
	.manufacturer	= 69,
	.खोलो		= ath_खोलो,
	.बंद		= ath_बंद,
	.flush		= ath_flush,
	.setup		= ath_setup,
	.recv		= ath_recv,
	.enqueue	= ath_enqueue,
	.dequeue	= ath_dequeue,
पूर्ण;

पूर्णांक __init ath_init(व्योम)
अणु
	वापस hci_uart_रेजिस्टर_proto(&athp);
पूर्ण

पूर्णांक __निकास ath_deinit(व्योम)
अणु
	वापस hci_uart_unरेजिस्टर_proto(&athp);
पूर्ण

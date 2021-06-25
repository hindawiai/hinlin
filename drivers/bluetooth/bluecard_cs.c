<शैली गुरु>
/*
 *
 *  Bluetooth driver क्रम the Anycom BlueCard (LSE039/LSE041)
 *
 *  Copyright (C) 2001-2002  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 *
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation;
 *
 *  Software distributed under the License is distributed on an "AS
 *  IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 *  implied. See the License क्रम the specअगरic language governing
 *  rights and limitations under the License.
 *
 *  The initial developer of the original code is David A. Hinds
 *  <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 *  are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 */

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/रुको.h>

#समावेश <linux/skbuff.h>
#समावेश <linux/पन.स>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>



/* ======================== Module parameters ======================== */


MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth driver for the Anycom BlueCard (LSE039/LSE041)");
MODULE_LICENSE("GPL");



/* ======================== Local काष्ठाures ======================== */


काष्ठा bluecard_info अणु
	काष्ठा pcmcia_device *p_dev;

	काष्ठा hci_dev *hdev;

	spinlock_t lock;		/* For serializing operations */
	काष्ठा समयr_list समयr;	/* For LED control */

	काष्ठा sk_buff_head txq;
	अचिन्हित दीर्घ tx_state;

	अचिन्हित दीर्घ rx_state;
	अचिन्हित दीर्घ rx_count;
	काष्ठा sk_buff *rx_skb;

	अचिन्हित अक्षर ctrl_reg;
	अचिन्हित दीर्घ hw_state;		/* Status of the hardware and LED control */
पूर्ण;


अटल पूर्णांक bluecard_config(काष्ठा pcmcia_device *link);
अटल व्योम bluecard_release(काष्ठा pcmcia_device *link);

अटल व्योम bluecard_detach(काष्ठा pcmcia_device *p_dev);


/* Default baud rate: 57600, 115200, 230400 or 460800 */
#घोषणा DEFAULT_BAUD_RATE  230400


/* Hardware states */
#घोषणा CARD_READY             1
#घोषणा CARD_ACTIVITY	       2
#घोषणा CARD_HAS_PCCARD_ID     4
#घोषणा CARD_HAS_POWER_LED     5
#घोषणा CARD_HAS_ACTIVITY_LED  6

/* Transmit states  */
#घोषणा XMIT_SENDING         1
#घोषणा XMIT_WAKEUP          2
#घोषणा XMIT_BUFFER_NUMBER   5	/* unset = buffer one, set = buffer two */
#घोषणा XMIT_BUF_ONE_READY   6
#घोषणा XMIT_BUF_TWO_READY   7
#घोषणा XMIT_SENDING_READY   8

/* Receiver states */
#घोषणा RECV_WAIT_PACKET_TYPE   0
#घोषणा RECV_WAIT_EVENT_HEADER  1
#घोषणा RECV_WAIT_ACL_HEADER    2
#घोषणा RECV_WAIT_SCO_HEADER    3
#घोषणा RECV_WAIT_DATA          4

/* Special packet types */
#घोषणा PKT_BAUD_RATE_57600   0x80
#घोषणा PKT_BAUD_RATE_115200  0x81
#घोषणा PKT_BAUD_RATE_230400  0x82
#घोषणा PKT_BAUD_RATE_460800  0x83


/* These are the रेजिस्टर offsets */
#घोषणा REG_COMMAND     0x20
#घोषणा REG_INTERRUPT   0x21
#घोषणा REG_CONTROL     0x22
#घोषणा REG_RX_CONTROL  0x24
#घोषणा REG_CARD_RESET  0x30
#घोषणा REG_LED_CTRL    0x30

/* REG_COMMAND */
#घोषणा REG_COMMAND_TX_BUF_ONE  0x01
#घोषणा REG_COMMAND_TX_BUF_TWO  0x02
#घोषणा REG_COMMAND_RX_BUF_ONE  0x04
#घोषणा REG_COMMAND_RX_BUF_TWO  0x08
#घोषणा REG_COMMAND_RX_WIN_ONE  0x00
#घोषणा REG_COMMAND_RX_WIN_TWO  0x10

/* REG_CONTROL */
#घोषणा REG_CONTROL_BAUD_RATE_57600   0x00
#घोषणा REG_CONTROL_BAUD_RATE_115200  0x01
#घोषणा REG_CONTROL_BAUD_RATE_230400  0x02
#घोषणा REG_CONTROL_BAUD_RATE_460800  0x03
#घोषणा REG_CONTROL_RTS               0x04
#घोषणा REG_CONTROL_BT_ON             0x08
#घोषणा REG_CONTROL_BT_RESET          0x10
#घोषणा REG_CONTROL_BT_RES_PU         0x20
#घोषणा REG_CONTROL_INTERRUPT         0x40
#घोषणा REG_CONTROL_CARD_RESET        0x80

/* REG_RX_CONTROL */
#घोषणा RTS_LEVEL_SHIFT_BITS  0x02



/* ======================== LED handling routines ======================== */


अटल व्योम bluecard_activity_led_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा bluecard_info *info = from_समयr(info, t, समयr);
	अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;

	अगर (test_bit(CARD_ACTIVITY, &(info->hw_state))) अणु
		/* leave LED in inactive state क्रम HZ/10 क्रम blink effect */
		clear_bit(CARD_ACTIVITY, &(info->hw_state));
		mod_समयr(&(info->समयr), jअगरfies + HZ / 10);
	पूर्ण

	/* Disable activity LED, enable घातer LED */
	outb(0x08 | 0x20, iobase + 0x30);
पूर्ण


अटल व्योम bluecard_enable_activity_led(काष्ठा bluecard_info *info)
अणु
	अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;

	/* करोn't disturb running blink समयr */
	अगर (समयr_pending(&(info->समयr)))
		वापस;

	set_bit(CARD_ACTIVITY, &(info->hw_state));

	अगर (test_bit(CARD_HAS_ACTIVITY_LED, &(info->hw_state))) अणु
		/* Enable activity LED, keep घातer LED enabled */
		outb(0x18 | 0x60, iobase + 0x30);
	पूर्ण अन्यथा अणु
		/* Disable घातer LED */
		outb(0x00, iobase + 0x30);
	पूर्ण

	/* Stop the LED after HZ/10 */
	mod_समयr(&(info->समयr), jअगरfies + HZ / 10);
पूर्ण



/* ======================== Interrupt handling ======================== */


अटल पूर्णांक bluecard_ग_लिखो(अचिन्हित पूर्णांक iobase, अचिन्हित पूर्णांक offset, __u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i, actual;

	actual = (len > 15) ? 15 : len;

	outb_p(actual, iobase + offset);

	क्रम (i = 0; i < actual; i++)
		outb_p(buf[i], iobase + offset + i + 1);

	वापस actual;
पूर्ण


अटल व्योम bluecard_ग_लिखो_wakeup(काष्ठा bluecard_info *info)
अणु
	अगर (!info) अणु
		BT_ERR("Unknown device");
		वापस;
	पूर्ण

	अगर (!test_bit(XMIT_SENDING_READY, &(info->tx_state)))
		वापस;

	अगर (test_and_set_bit(XMIT_SENDING, &(info->tx_state))) अणु
		set_bit(XMIT_WAKEUP, &(info->tx_state));
		वापस;
	पूर्ण

	करो अणु
		अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;
		अचिन्हित पूर्णांक offset;
		अचिन्हित अक्षर command;
		अचिन्हित दीर्घ पढ़ोy_bit;
		रेजिस्टर काष्ठा sk_buff *skb;
		पूर्णांक len;

		clear_bit(XMIT_WAKEUP, &(info->tx_state));

		अगर (!pcmcia_dev_present(info->p_dev))
			वापस;

		अगर (test_bit(XMIT_BUFFER_NUMBER, &(info->tx_state))) अणु
			अगर (!test_bit(XMIT_BUF_TWO_READY, &(info->tx_state)))
				अवरोध;
			offset = 0x10;
			command = REG_COMMAND_TX_BUF_TWO;
			पढ़ोy_bit = XMIT_BUF_TWO_READY;
		पूर्ण अन्यथा अणु
			अगर (!test_bit(XMIT_BUF_ONE_READY, &(info->tx_state)))
				अवरोध;
			offset = 0x00;
			command = REG_COMMAND_TX_BUF_ONE;
			पढ़ोy_bit = XMIT_BUF_ONE_READY;
		पूर्ण

		skb = skb_dequeue(&(info->txq));
		अगर (!skb)
			अवरोध;

		अगर (hci_skb_pkt_type(skb) & 0x80) अणु
			/* Disable RTS */
			info->ctrl_reg |= REG_CONTROL_RTS;
			outb(info->ctrl_reg, iobase + REG_CONTROL);
		पूर्ण

		/* Activate LED */
		bluecard_enable_activity_led(info);

		/* Send frame */
		len = bluecard_ग_लिखो(iobase, offset, skb->data, skb->len);

		/* Tell the FPGA to send the data */
		outb_p(command, iobase + REG_COMMAND);

		/* Mark the buffer as dirty */
		clear_bit(पढ़ोy_bit, &(info->tx_state));

		अगर (hci_skb_pkt_type(skb) & 0x80) अणु
			DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
			DEFINE_WAIT(रुको);

			अचिन्हित अक्षर baud_reg;

			चयन (hci_skb_pkt_type(skb)) अणु
			हाल PKT_BAUD_RATE_460800:
				baud_reg = REG_CONTROL_BAUD_RATE_460800;
				अवरोध;
			हाल PKT_BAUD_RATE_230400:
				baud_reg = REG_CONTROL_BAUD_RATE_230400;
				अवरोध;
			हाल PKT_BAUD_RATE_115200:
				baud_reg = REG_CONTROL_BAUD_RATE_115200;
				अवरोध;
			हाल PKT_BAUD_RATE_57600:
			शेष:
				baud_reg = REG_CONTROL_BAUD_RATE_57600;
				अवरोध;
			पूर्ण

			/* Wait until the command reaches the baseband */
			mdelay(100);

			/* Set baud on baseband */
			info->ctrl_reg &= ~0x03;
			info->ctrl_reg |= baud_reg;
			outb(info->ctrl_reg, iobase + REG_CONTROL);

			/* Enable RTS */
			info->ctrl_reg &= ~REG_CONTROL_RTS;
			outb(info->ctrl_reg, iobase + REG_CONTROL);

			/* Wait beक्रमe the next HCI packet can be send */
			mdelay(1000);
		पूर्ण

		अगर (len == skb->len) अणु
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			skb_pull(skb, len);
			skb_queue_head(&(info->txq), skb);
		पूर्ण

		info->hdev->stat.byte_tx += len;

		/* Change buffer */
		change_bit(XMIT_BUFFER_NUMBER, &(info->tx_state));

	पूर्ण जबतक (test_bit(XMIT_WAKEUP, &(info->tx_state)));

	clear_bit(XMIT_SENDING, &(info->tx_state));
पूर्ण


अटल पूर्णांक bluecard_पढ़ो(अचिन्हित पूर्णांक iobase, अचिन्हित पूर्णांक offset, __u8 *buf, पूर्णांक size)
अणु
	पूर्णांक i, n, len;

	outb(REG_COMMAND_RX_WIN_ONE, iobase + REG_COMMAND);

	len = inb(iobase + offset);
	n = 0;
	i = 1;

	जबतक (n < len) अणु

		अगर (i == 16) अणु
			outb(REG_COMMAND_RX_WIN_TWO, iobase + REG_COMMAND);
			i = 0;
		पूर्ण

		buf[n] = inb(iobase + offset + i);

		n++;
		i++;

	पूर्ण

	वापस len;
पूर्ण


अटल व्योम bluecard_receive(काष्ठा bluecard_info *info,
			     अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक iobase;
	अचिन्हित अक्षर buf[31];
	पूर्णांक i, len;

	अगर (!info) अणु
		BT_ERR("Unknown device");
		वापस;
	पूर्ण

	iobase = info->p_dev->resource[0]->start;

	अगर (test_bit(XMIT_SENDING_READY, &(info->tx_state)))
		bluecard_enable_activity_led(info);

	len = bluecard_पढ़ो(iobase, offset, buf, माप(buf));

	क्रम (i = 0; i < len; i++) अणु

		/* Allocate packet */
		अगर (!info->rx_skb) अणु
			info->rx_state = RECV_WAIT_PACKET_TYPE;
			info->rx_count = 0;
			info->rx_skb = bt_skb_alloc(HCI_MAX_FRAME_SIZE, GFP_ATOMIC);
			अगर (!info->rx_skb) अणु
				BT_ERR("Can't allocate mem for new packet");
				वापस;
			पूर्ण
		पूर्ण

		अगर (info->rx_state == RECV_WAIT_PACKET_TYPE) अणु

			hci_skb_pkt_type(info->rx_skb) = buf[i];

			चयन (hci_skb_pkt_type(info->rx_skb)) अणु

			हाल 0x00:
				/* init packet */
				अगर (offset != 0x00) अणु
					set_bit(XMIT_BUF_ONE_READY, &(info->tx_state));
					set_bit(XMIT_BUF_TWO_READY, &(info->tx_state));
					set_bit(XMIT_SENDING_READY, &(info->tx_state));
					bluecard_ग_लिखो_wakeup(info);
				पूर्ण

				kमुक्त_skb(info->rx_skb);
				info->rx_skb = शून्य;
				अवरोध;

			हाल HCI_EVENT_PKT:
				info->rx_state = RECV_WAIT_EVENT_HEADER;
				info->rx_count = HCI_EVENT_HDR_SIZE;
				अवरोध;

			हाल HCI_ACLDATA_PKT:
				info->rx_state = RECV_WAIT_ACL_HEADER;
				info->rx_count = HCI_ACL_HDR_SIZE;
				अवरोध;

			हाल HCI_SCODATA_PKT:
				info->rx_state = RECV_WAIT_SCO_HEADER;
				info->rx_count = HCI_SCO_HDR_SIZE;
				अवरोध;

			शेष:
				/* unknown packet */
				BT_ERR("Unknown HCI packet with type 0x%02x received",
				       hci_skb_pkt_type(info->rx_skb));
				info->hdev->stat.err_rx++;

				kमुक्त_skb(info->rx_skb);
				info->rx_skb = शून्य;
				अवरोध;

			पूर्ण

		पूर्ण अन्यथा अणु

			skb_put_u8(info->rx_skb, buf[i]);
			info->rx_count--;

			अगर (info->rx_count == 0) अणु

				पूर्णांक dlen;
				काष्ठा hci_event_hdr *eh;
				काष्ठा hci_acl_hdr *ah;
				काष्ठा hci_sco_hdr *sh;

				चयन (info->rx_state) अणु

				हाल RECV_WAIT_EVENT_HEADER:
					eh = hci_event_hdr(info->rx_skb);
					info->rx_state = RECV_WAIT_DATA;
					info->rx_count = eh->plen;
					अवरोध;

				हाल RECV_WAIT_ACL_HEADER:
					ah = hci_acl_hdr(info->rx_skb);
					dlen = __le16_to_cpu(ah->dlen);
					info->rx_state = RECV_WAIT_DATA;
					info->rx_count = dlen;
					अवरोध;

				हाल RECV_WAIT_SCO_HEADER:
					sh = hci_sco_hdr(info->rx_skb);
					info->rx_state = RECV_WAIT_DATA;
					info->rx_count = sh->dlen;
					अवरोध;

				हाल RECV_WAIT_DATA:
					hci_recv_frame(info->hdev, info->rx_skb);
					info->rx_skb = शून्य;
					अवरोध;

				पूर्ण

			पूर्ण

		पूर्ण


	पूर्ण

	info->hdev->stat.byte_rx += len;
पूर्ण


अटल irqवापस_t bluecard_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_inst)
अणु
	काष्ठा bluecard_info *info = dev_inst;
	अचिन्हित पूर्णांक iobase;
	अचिन्हित अक्षर reg;

	अगर (!info || !info->hdev)
		/* our irq handler is shared */
		वापस IRQ_NONE;

	अगर (!test_bit(CARD_READY, &(info->hw_state)))
		वापस IRQ_HANDLED;

	iobase = info->p_dev->resource[0]->start;

	spin_lock(&(info->lock));

	/* Disable पूर्णांकerrupt */
	info->ctrl_reg &= ~REG_CONTROL_INTERRUPT;
	outb(info->ctrl_reg, iobase + REG_CONTROL);

	reg = inb(iobase + REG_INTERRUPT);

	अगर ((reg != 0x00) && (reg != 0xff)) अणु

		अगर (reg & 0x04) अणु
			bluecard_receive(info, 0x00);
			outb(0x04, iobase + REG_INTERRUPT);
			outb(REG_COMMAND_RX_BUF_ONE, iobase + REG_COMMAND);
		पूर्ण

		अगर (reg & 0x08) अणु
			bluecard_receive(info, 0x10);
			outb(0x08, iobase + REG_INTERRUPT);
			outb(REG_COMMAND_RX_BUF_TWO, iobase + REG_COMMAND);
		पूर्ण

		अगर (reg & 0x01) अणु
			set_bit(XMIT_BUF_ONE_READY, &(info->tx_state));
			outb(0x01, iobase + REG_INTERRUPT);
			bluecard_ग_लिखो_wakeup(info);
		पूर्ण

		अगर (reg & 0x02) अणु
			set_bit(XMIT_BUF_TWO_READY, &(info->tx_state));
			outb(0x02, iobase + REG_INTERRUPT);
			bluecard_ग_लिखो_wakeup(info);
		पूर्ण

	पूर्ण

	/* Enable पूर्णांकerrupt */
	info->ctrl_reg |= REG_CONTROL_INTERRUPT;
	outb(info->ctrl_reg, iobase + REG_CONTROL);

	spin_unlock(&(info->lock));

	वापस IRQ_HANDLED;
पूर्ण



/* ======================== Device specअगरic HCI commands ======================== */


अटल पूर्णांक bluecard_hci_set_baud_rate(काष्ठा hci_dev *hdev, पूर्णांक baud)
अणु
	काष्ठा bluecard_info *info = hci_get_drvdata(hdev);
	काष्ठा sk_buff *skb;

	/* Ericsson baud rate command */
	अचिन्हित अक्षर cmd[] = अणु HCI_COMMAND_PKT, 0x09, 0xfc, 0x01, 0x03 पूर्ण;

	skb = bt_skb_alloc(HCI_MAX_FRAME_SIZE, GFP_KERNEL);
	अगर (!skb) अणु
		BT_ERR("Can't allocate mem for new packet");
		वापस -1;
	पूर्ण

	चयन (baud) अणु
	हाल 460800:
		cmd[4] = 0x00;
		hci_skb_pkt_type(skb) = PKT_BAUD_RATE_460800;
		अवरोध;
	हाल 230400:
		cmd[4] = 0x01;
		hci_skb_pkt_type(skb) = PKT_BAUD_RATE_230400;
		अवरोध;
	हाल 115200:
		cmd[4] = 0x02;
		hci_skb_pkt_type(skb) = PKT_BAUD_RATE_115200;
		अवरोध;
	हाल 57600:
	शेष:
		cmd[4] = 0x03;
		hci_skb_pkt_type(skb) = PKT_BAUD_RATE_57600;
		अवरोध;
	पूर्ण

	skb_put_data(skb, cmd, माप(cmd));

	skb_queue_tail(&(info->txq), skb);

	bluecard_ग_लिखो_wakeup(info);

	वापस 0;
पूर्ण



/* ======================== HCI पूर्णांकerface ======================== */


अटल पूर्णांक bluecard_hci_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bluecard_info *info = hci_get_drvdata(hdev);

	/* Drop TX queue */
	skb_queue_purge(&(info->txq));

	वापस 0;
पूर्ण


अटल पूर्णांक bluecard_hci_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bluecard_info *info = hci_get_drvdata(hdev);
	अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;

	अगर (test_bit(CARD_HAS_PCCARD_ID, &(info->hw_state)))
		bluecard_hci_set_baud_rate(hdev, DEFAULT_BAUD_RATE);

	/* Enable घातer LED */
	outb(0x08 | 0x20, iobase + 0x30);

	वापस 0;
पूर्ण


अटल पूर्णांक bluecard_hci_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bluecard_info *info = hci_get_drvdata(hdev);
	अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;

	bluecard_hci_flush(hdev);

	/* Stop LED समयr */
	del_समयr_sync(&(info->समयr));

	/* Disable घातer LED */
	outb(0x00, iobase + 0x30);

	वापस 0;
पूर्ण


अटल पूर्णांक bluecard_hci_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bluecard_info *info = hci_get_drvdata(hdev);

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		अवरोध;
	हाल HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		अवरोध;
	हाल HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		अवरोध;
	पूर्ण

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);
	skb_queue_tail(&(info->txq), skb);

	bluecard_ग_लिखो_wakeup(info);

	वापस 0;
पूर्ण



/* ======================== Card services HCI पूर्णांकeraction ======================== */


अटल पूर्णांक bluecard_खोलो(काष्ठा bluecard_info *info)
अणु
	अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;
	काष्ठा hci_dev *hdev;
	अचिन्हित अक्षर id;

	spin_lock_init(&(info->lock));

	समयr_setup(&info->समयr, bluecard_activity_led_समयout, 0);

	skb_queue_head_init(&(info->txq));

	info->rx_state = RECV_WAIT_PACKET_TYPE;
	info->rx_count = 0;
	info->rx_skb = शून्य;

	/* Initialize HCI device */
	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		BT_ERR("Can't allocate HCI device");
		वापस -ENOMEM;
	पूर्ण

	info->hdev = hdev;

	hdev->bus = HCI_PCCARD;
	hci_set_drvdata(hdev, info);
	SET_HCIDEV_DEV(hdev, &info->p_dev->dev);

	hdev->खोलो  = bluecard_hci_खोलो;
	hdev->बंद = bluecard_hci_बंद;
	hdev->flush = bluecard_hci_flush;
	hdev->send  = bluecard_hci_send_frame;

	id = inb(iobase + 0x30);

	अगर ((id & 0x0f) == 0x02)
		set_bit(CARD_HAS_PCCARD_ID, &(info->hw_state));

	अगर (id & 0x10)
		set_bit(CARD_HAS_POWER_LED, &(info->hw_state));

	अगर (id & 0x20)
		set_bit(CARD_HAS_ACTIVITY_LED, &(info->hw_state));

	/* Reset card */
	info->ctrl_reg = REG_CONTROL_BT_RESET | REG_CONTROL_CARD_RESET;
	outb(info->ctrl_reg, iobase + REG_CONTROL);

	/* Turn FPGA off */
	outb(0x80, iobase + 0x30);

	/* Wait some समय */
	msleep(10);

	/* Turn FPGA on */
	outb(0x00, iobase + 0x30);

	/* Activate card */
	info->ctrl_reg = REG_CONTROL_BT_ON | REG_CONTROL_BT_RES_PU;
	outb(info->ctrl_reg, iobase + REG_CONTROL);

	/* Enable पूर्णांकerrupt */
	outb(0xff, iobase + REG_INTERRUPT);
	info->ctrl_reg |= REG_CONTROL_INTERRUPT;
	outb(info->ctrl_reg, iobase + REG_CONTROL);

	अगर ((id & 0x0f) == 0x03) अणु
		/* Disable RTS */
		info->ctrl_reg |= REG_CONTROL_RTS;
		outb(info->ctrl_reg, iobase + REG_CONTROL);

		/* Set baud rate */
		info->ctrl_reg |= 0x03;
		outb(info->ctrl_reg, iobase + REG_CONTROL);

		/* Enable RTS */
		info->ctrl_reg &= ~REG_CONTROL_RTS;
		outb(info->ctrl_reg, iobase + REG_CONTROL);

		set_bit(XMIT_BUF_ONE_READY, &(info->tx_state));
		set_bit(XMIT_BUF_TWO_READY, &(info->tx_state));
		set_bit(XMIT_SENDING_READY, &(info->tx_state));
	पूर्ण

	/* Start the RX buffers */
	outb(REG_COMMAND_RX_BUF_ONE, iobase + REG_COMMAND);
	outb(REG_COMMAND_RX_BUF_TWO, iobase + REG_COMMAND);

	/* Signal that the hardware is पढ़ोy */
	set_bit(CARD_READY, &(info->hw_state));

	/* Drop TX queue */
	skb_queue_purge(&(info->txq));

	/* Control the poपूर्णांक at which RTS is enabled */
	outb((0x0f << RTS_LEVEL_SHIFT_BITS) | 1, iobase + REG_RX_CONTROL);

	/* Timeout beक्रमe it is safe to send the first HCI packet */
	msleep(1250);

	/* Register HCI device */
	अगर (hci_रेजिस्टर_dev(hdev) < 0) अणु
		BT_ERR("Can't register HCI device");
		info->hdev = शून्य;
		hci_मुक्त_dev(hdev);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक bluecard_बंद(काष्ठा bluecard_info *info)
अणु
	अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;
	काष्ठा hci_dev *hdev = info->hdev;

	अगर (!hdev)
		वापस -ENODEV;

	bluecard_hci_बंद(hdev);

	clear_bit(CARD_READY, &(info->hw_state));

	/* Reset card */
	info->ctrl_reg = REG_CONTROL_BT_RESET | REG_CONTROL_CARD_RESET;
	outb(info->ctrl_reg, iobase + REG_CONTROL);

	/* Turn FPGA off */
	outb(0x80, iobase + 0x30);

	hci_unरेजिस्टर_dev(hdev);
	hci_मुक्त_dev(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक bluecard_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा bluecard_info *info;

	/* Create new info device */
	info = devm_kzalloc(&link->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->p_dev = link;
	link->priv = info;

	link->config_flags |= CONF_ENABLE_IRQ;

	वापस bluecard_config(link);
पूर्ण


अटल व्योम bluecard_detach(काष्ठा pcmcia_device *link)
अणु
	bluecard_release(link);
पूर्ण


अटल पूर्णांक bluecard_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा bluecard_info *info = link->priv;
	पूर्णांक i, n;

	link->config_index = 0x20;

	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	link->resource[0]->end = 64;
	link->io_lines = 6;

	क्रम (n = 0; n < 0x400; n += 0x40) अणु
		link->resource[0]->start = n ^ 0x300;
		i = pcmcia_request_io(link);
		अगर (i == 0)
			अवरोध;
	पूर्ण

	अगर (i != 0)
		जाओ failed;

	i = pcmcia_request_irq(link, bluecard_पूर्णांकerrupt);
	अगर (i != 0)
		जाओ failed;

	i = pcmcia_enable_device(link);
	अगर (i != 0)
		जाओ failed;

	अगर (bluecard_खोलो(info) != 0)
		जाओ failed;

	वापस 0;

failed:
	bluecard_release(link);
	वापस -ENODEV;
पूर्ण


अटल व्योम bluecard_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा bluecard_info *info = link->priv;

	bluecard_बंद(info);

	del_समयr_sync(&(info->समयr));

	pcmcia_disable_device(link);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id bluecard_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID12("BlueCard", "LSE041", 0xbaf16fbf, 0x657cc15e),
	PCMCIA_DEVICE_PROD_ID12("BTCFCARD", "LSE139", 0xe3987764, 0x2524b59c),
	PCMCIA_DEVICE_PROD_ID12("WSS", "LSE039", 0x0a0736ec, 0x24e6dfab),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, bluecard_ids);

अटल काष्ठा pcmcia_driver bluecard_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "bluecard_cs",
	.probe		= bluecard_probe,
	.हटाओ		= bluecard_detach,
	.id_table	= bluecard_ids,
पूर्ण;
module_pcmcia_driver(bluecard_driver);

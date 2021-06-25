<शैली गुरु>
/*
 *
 *  A driver क्रम Nokia Connectivity Card DTL-1 devices
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
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>
#समावेश <linux/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/पन.स>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>



/* ======================== Module parameters ======================== */


MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth driver for Nokia Connectivity Card DTL-1");
MODULE_LICENSE("GPL");



/* ======================== Local काष्ठाures ======================== */


काष्ठा dtl1_info अणु
	काष्ठा pcmcia_device *p_dev;

	काष्ठा hci_dev *hdev;

	spinlock_t lock;		/* For serializing operations */

	अचिन्हित दीर्घ flowmask;		/* HCI flow mask */
	पूर्णांक ri_latch;

	काष्ठा sk_buff_head txq;
	अचिन्हित दीर्घ tx_state;

	अचिन्हित दीर्घ rx_state;
	अचिन्हित दीर्घ rx_count;
	काष्ठा sk_buff *rx_skb;
पूर्ण;


अटल पूर्णांक dtl1_config(काष्ठा pcmcia_device *link);


/* Transmit states  */
#घोषणा XMIT_SENDING  1
#घोषणा XMIT_WAKEUP   2
#घोषणा XMIT_WAITING  8

/* Receiver States */
#घोषणा RECV_WAIT_NSH   0
#घोषणा RECV_WAIT_DATA  1


काष्ठा nsh अणु
	u8 type;
	u8 zero;
	u16 len;
पूर्ण __packed;	/* Nokia Specअगरic Header */

#घोषणा NSHL  4				/* Nokia Specअगरic Header Length */



/* ======================== Interrupt handling ======================== */


अटल पूर्णांक dtl1_ग_लिखो(अचिन्हित पूर्णांक iobase, पूर्णांक fअगरo_size, __u8 *buf, पूर्णांक len)
अणु
	पूर्णांक actual = 0;

	/* Tx FIFO should be empty */
	अगर (!(inb(iobase + UART_LSR) & UART_LSR_THRE))
		वापस 0;

	/* Fill FIFO with current frame */
	जबतक ((fअगरo_size-- > 0) && (actual < len)) अणु
		/* Transmit next byte */
		outb(buf[actual], iobase + UART_TX);
		actual++;
	पूर्ण

	वापस actual;
पूर्ण


अटल व्योम dtl1_ग_लिखो_wakeup(काष्ठा dtl1_info *info)
अणु
	अगर (!info) अणु
		BT_ERR("Unknown device");
		वापस;
	पूर्ण

	अगर (test_bit(XMIT_WAITING, &(info->tx_state))) अणु
		set_bit(XMIT_WAKEUP, &(info->tx_state));
		वापस;
	पूर्ण

	अगर (test_and_set_bit(XMIT_SENDING, &(info->tx_state))) अणु
		set_bit(XMIT_WAKEUP, &(info->tx_state));
		वापस;
	पूर्ण

	करो अणु
		अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;
		रेजिस्टर काष्ठा sk_buff *skb;
		पूर्णांक len;

		clear_bit(XMIT_WAKEUP, &(info->tx_state));

		अगर (!pcmcia_dev_present(info->p_dev))
			वापस;

		skb = skb_dequeue(&(info->txq));
		अगर (!skb)
			अवरोध;

		/* Send frame */
		len = dtl1_ग_लिखो(iobase, 32, skb->data, skb->len);

		अगर (len == skb->len) अणु
			set_bit(XMIT_WAITING, &(info->tx_state));
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			skb_pull(skb, len);
			skb_queue_head(&(info->txq), skb);
		पूर्ण

		info->hdev->stat.byte_tx += len;

	पूर्ण जबतक (test_bit(XMIT_WAKEUP, &(info->tx_state)));

	clear_bit(XMIT_SENDING, &(info->tx_state));
पूर्ण


अटल व्योम dtl1_control(काष्ठा dtl1_info *info, काष्ठा sk_buff *skb)
अणु
	u8 flowmask = *(u8 *)skb->data;
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "Bluetooth: Nokia control data =");
	क्रम (i = 0; i < skb->len; i++)
		prपूर्णांकk(" %02x", skb->data[i]);

	prपूर्णांकk("\n");

	/* transition to active state */
	अगर (((info->flowmask & 0x07) == 0) && ((flowmask & 0x07) != 0)) अणु
		clear_bit(XMIT_WAITING, &(info->tx_state));
		dtl1_ग_लिखो_wakeup(info);
	पूर्ण

	info->flowmask = flowmask;

	kमुक्त_skb(skb);
पूर्ण


अटल व्योम dtl1_receive(काष्ठा dtl1_info *info)
अणु
	अचिन्हित पूर्णांक iobase;
	काष्ठा nsh *nsh;
	पूर्णांक boguscount = 0;

	अगर (!info) अणु
		BT_ERR("Unknown device");
		वापस;
	पूर्ण

	iobase = info->p_dev->resource[0]->start;

	करो अणु
		info->hdev->stat.byte_rx++;

		/* Allocate packet */
		अगर (info->rx_skb == शून्य) अणु
			info->rx_skb = bt_skb_alloc(HCI_MAX_FRAME_SIZE, GFP_ATOMIC);
			अगर (!info->rx_skb) अणु
				BT_ERR("Can't allocate mem for new packet");
				info->rx_state = RECV_WAIT_NSH;
				info->rx_count = NSHL;
				वापस;
			पूर्ण
		पूर्ण

		skb_put_u8(info->rx_skb, inb(iobase + UART_RX));
		nsh = (काष्ठा nsh *)info->rx_skb->data;

		info->rx_count--;

		अगर (info->rx_count == 0) अणु

			चयन (info->rx_state) अणु
			हाल RECV_WAIT_NSH:
				info->rx_state = RECV_WAIT_DATA;
				info->rx_count = nsh->len + (nsh->len & 0x0001);
				अवरोध;
			हाल RECV_WAIT_DATA:
				hci_skb_pkt_type(info->rx_skb) = nsh->type;

				/* हटाओ PAD byte अगर it exists */
				अगर (nsh->len & 0x0001) अणु
					info->rx_skb->tail--;
					info->rx_skb->len--;
				पूर्ण

				/* हटाओ NSH */
				skb_pull(info->rx_skb, NSHL);

				चयन (hci_skb_pkt_type(info->rx_skb)) अणु
				हाल 0x80:
					/* control data क्रम the Nokia Card */
					dtl1_control(info, info->rx_skb);
					अवरोध;
				हाल 0x82:
				हाल 0x83:
				हाल 0x84:
					/* send frame to the HCI layer */
					hci_skb_pkt_type(info->rx_skb) &= 0x0f;
					hci_recv_frame(info->hdev, info->rx_skb);
					अवरोध;
				शेष:
					/* unknown packet */
					BT_ERR("Unknown HCI packet with type 0x%02x received",
					       hci_skb_pkt_type(info->rx_skb));
					kमुक्त_skb(info->rx_skb);
					अवरोध;
				पूर्ण

				info->rx_state = RECV_WAIT_NSH;
				info->rx_count = NSHL;
				info->rx_skb = शून्य;
				अवरोध;
			पूर्ण

		पूर्ण

		/* Make sure we करोn't stay here too दीर्घ */
		अगर (boguscount++ > 32)
			अवरोध;

	पूर्ण जबतक (inb(iobase + UART_LSR) & UART_LSR_DR);
पूर्ण


अटल irqवापस_t dtl1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_inst)
अणु
	काष्ठा dtl1_info *info = dev_inst;
	अचिन्हित पूर्णांक iobase;
	अचिन्हित अक्षर msr;
	पूर्णांक boguscount = 0;
	पूर्णांक iir, lsr;
	irqवापस_t r = IRQ_NONE;

	अगर (!info || !info->hdev)
		/* our irq handler is shared */
		वापस IRQ_NONE;

	iobase = info->p_dev->resource[0]->start;

	spin_lock(&(info->lock));

	iir = inb(iobase + UART_IIR) & UART_IIR_ID;
	जबतक (iir) अणु

		r = IRQ_HANDLED;
		/* Clear पूर्णांकerrupt */
		lsr = inb(iobase + UART_LSR);

		चयन (iir) अणु
		हाल UART_IIR_RLSI:
			BT_ERR("RLSI");
			अवरोध;
		हाल UART_IIR_RDI:
			/* Receive पूर्णांकerrupt */
			dtl1_receive(info);
			अवरोध;
		हाल UART_IIR_THRI:
			अगर (lsr & UART_LSR_THRE) अणु
				/* Transmitter पढ़ोy क्रम data */
				dtl1_ग_लिखो_wakeup(info);
			पूर्ण
			अवरोध;
		शेष:
			BT_ERR("Unhandled IIR=%#x", iir);
			अवरोध;
		पूर्ण

		/* Make sure we करोn't stay here too दीर्घ */
		अगर (boguscount++ > 100)
			अवरोध;

		iir = inb(iobase + UART_IIR) & UART_IIR_ID;

	पूर्ण

	msr = inb(iobase + UART_MSR);

	अगर (info->ri_latch ^ (msr & UART_MSR_RI)) अणु
		info->ri_latch = msr & UART_MSR_RI;
		clear_bit(XMIT_WAITING, &(info->tx_state));
		dtl1_ग_लिखो_wakeup(info);
		r = IRQ_HANDLED;
	पूर्ण

	spin_unlock(&(info->lock));

	वापस r;
पूर्ण



/* ======================== HCI पूर्णांकerface ======================== */


अटल पूर्णांक dtl1_hci_खोलो(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक dtl1_hci_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा dtl1_info *info = hci_get_drvdata(hdev);

	/* Drop TX queue */
	skb_queue_purge(&(info->txq));

	वापस 0;
पूर्ण


अटल पूर्णांक dtl1_hci_बंद(काष्ठा hci_dev *hdev)
अणु
	dtl1_hci_flush(hdev);

	वापस 0;
पूर्ण


अटल पूर्णांक dtl1_hci_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा dtl1_info *info = hci_get_drvdata(hdev);
	काष्ठा sk_buff *s;
	काष्ठा nsh nsh;

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		nsh.type = 0x81;
		अवरोध;
	हाल HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		nsh.type = 0x82;
		अवरोध;
	हाल HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		nsh.type = 0x83;
		अवरोध;
	शेष:
		वापस -EILSEQ;
	पूर्ण

	nsh.zero = 0;
	nsh.len = skb->len;

	s = bt_skb_alloc(NSHL + skb->len + 1, GFP_ATOMIC);
	अगर (!s)
		वापस -ENOMEM;

	skb_reserve(s, NSHL);
	skb_copy_from_linear_data(skb, skb_put(s, skb->len), skb->len);
	अगर (skb->len & 0x0001)
		skb_put_u8(s, 0);	/* PAD */

	/* Prepend skb with Nokia frame header and queue */
	स_नकल(skb_push(s, NSHL), &nsh, NSHL);
	skb_queue_tail(&(info->txq), s);

	dtl1_ग_लिखो_wakeup(info);

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण



/* ======================== Card services HCI पूर्णांकeraction ======================== */


अटल पूर्णांक dtl1_खोलो(काष्ठा dtl1_info *info)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;
	काष्ठा hci_dev *hdev;

	spin_lock_init(&(info->lock));

	skb_queue_head_init(&(info->txq));

	info->rx_state = RECV_WAIT_NSH;
	info->rx_count = NSHL;
	info->rx_skb = शून्य;

	set_bit(XMIT_WAITING, &(info->tx_state));

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

	hdev->खोलो  = dtl1_hci_खोलो;
	hdev->बंद = dtl1_hci_बंद;
	hdev->flush = dtl1_hci_flush;
	hdev->send  = dtl1_hci_send_frame;

	spin_lock_irqsave(&(info->lock), flags);

	/* Reset UART */
	outb(0, iobase + UART_MCR);

	/* Turn off पूर्णांकerrupts */
	outb(0, iobase + UART_IER);

	/* Initialize UART */
	outb(UART_LCR_WLEN8, iobase + UART_LCR);	/* Reset DLAB */
	outb((UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2), iobase + UART_MCR);

	info->ri_latch = inb(info->p_dev->resource[0]->start + UART_MSR)
				& UART_MSR_RI;

	/* Turn on पूर्णांकerrupts */
	outb(UART_IER_RLSI | UART_IER_RDI | UART_IER_THRI, iobase + UART_IER);

	spin_unlock_irqrestore(&(info->lock), flags);

	/* Timeout beक्रमe it is safe to send the first HCI packet */
	msleep(2000);

	/* Register HCI device */
	अगर (hci_रेजिस्टर_dev(hdev) < 0) अणु
		BT_ERR("Can't register HCI device");
		info->hdev = शून्य;
		hci_मुक्त_dev(hdev);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक dtl1_बंद(काष्ठा dtl1_info *info)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;
	काष्ठा hci_dev *hdev = info->hdev;

	अगर (!hdev)
		वापस -ENODEV;

	dtl1_hci_बंद(hdev);

	spin_lock_irqsave(&(info->lock), flags);

	/* Reset UART */
	outb(0, iobase + UART_MCR);

	/* Turn off पूर्णांकerrupts */
	outb(0, iobase + UART_IER);

	spin_unlock_irqrestore(&(info->lock), flags);

	hci_unरेजिस्टर_dev(hdev);
	hci_मुक्त_dev(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक dtl1_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा dtl1_info *info;

	/* Create new info device */
	info = devm_kzalloc(&link->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->p_dev = link;
	link->priv = info;

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	वापस dtl1_config(link);
पूर्ण


अटल व्योम dtl1_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा dtl1_info *info = link->priv;

	dtl1_बंद(info);
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक dtl1_confcheck(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	अगर ((p_dev->resource[1]->end) || (p_dev->resource[1]->end < 8))
		वापस -ENODEV;

	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;

	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक dtl1_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा dtl1_info *info = link->priv;
	पूर्णांक ret;

	/* Look क्रम a generic full-sized winकरोw */
	link->resource[0]->end = 8;
	ret = pcmcia_loop_config(link, dtl1_confcheck, शून्य);
	अगर (ret)
		जाओ failed;

	ret = pcmcia_request_irq(link, dtl1_पूर्णांकerrupt);
	अगर (ret)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	ret = dtl1_खोलो(info);
	अगर (ret)
		जाओ failed;

	वापस 0;

failed:
	dtl1_detach(link);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id dtl1_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID12("Nokia Mobile Phones", "DTL-1", 0xe1bfdd64, 0xe168480d),
	PCMCIA_DEVICE_PROD_ID12("Nokia Mobile Phones", "DTL-4", 0xe1bfdd64, 0x9102bc82),
	PCMCIA_DEVICE_PROD_ID12("Socket", "CF", 0xb38bcc2e, 0x44ebf863),
	PCMCIA_DEVICE_PROD_ID12("Socket", "CF+ Personal Network Card", 0xb38bcc2e, 0xe732bae3),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, dtl1_ids);

अटल काष्ठा pcmcia_driver dtl1_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "dtl1_cs",
	.probe		= dtl1_probe,
	.हटाओ		= dtl1_detach,
	.id_table	= dtl1_ids,
पूर्ण;
module_pcmcia_driver(dtl1_driver);

<शैली गुरु>
/*
 *
 *  Driver क्रम the 3Com Bluetooth PCMCIA card
 *
 *  Copyright (C) 2001-2002  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 *                           Jose Orlanकरो Pereira <jop@di.uminho.pt>
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

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>



/* ======================== Module parameters ======================== */


MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth driver for the 3Com Bluetooth PCMCIA card");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("BT3CPCC.bin");



/* ======================== Local काष्ठाures ======================== */


काष्ठा bt3c_info अणु
	काष्ठा pcmcia_device *p_dev;

	काष्ठा hci_dev *hdev;

	spinlock_t lock;		/* For serializing operations */

	काष्ठा sk_buff_head txq;
	अचिन्हित दीर्घ tx_state;

	अचिन्हित दीर्घ rx_state;
	अचिन्हित दीर्घ rx_count;
	काष्ठा sk_buff *rx_skb;
पूर्ण;


अटल पूर्णांक bt3c_config(काष्ठा pcmcia_device *link);
अटल व्योम bt3c_release(काष्ठा pcmcia_device *link);

अटल व्योम bt3c_detach(काष्ठा pcmcia_device *p_dev);


/* Transmit states  */
#घोषणा XMIT_SENDING  1
#घोषणा XMIT_WAKEUP   2
#घोषणा XMIT_WAITING  8

/* Receiver states */
#घोषणा RECV_WAIT_PACKET_TYPE   0
#घोषणा RECV_WAIT_EVENT_HEADER  1
#घोषणा RECV_WAIT_ACL_HEADER    2
#घोषणा RECV_WAIT_SCO_HEADER    3
#घोषणा RECV_WAIT_DATA          4



/* ======================== Special I/O functions ======================== */


#घोषणा DATA_L   0
#घोषणा DATA_H   1
#घोषणा ADDR_L   2
#घोषणा ADDR_H   3
#घोषणा CONTROL  4


अटल अंतरभूत व्योम bt3c_address(अचिन्हित पूर्णांक iobase, अचिन्हित लघु addr)
अणु
	outb(addr & 0xff, iobase + ADDR_L);
	outb((addr >> 8) & 0xff, iobase + ADDR_H);
पूर्ण


अटल अंतरभूत व्योम bt3c_put(अचिन्हित पूर्णांक iobase, अचिन्हित लघु value)
अणु
	outb(value & 0xff, iobase + DATA_L);
	outb((value >> 8) & 0xff, iobase + DATA_H);
पूर्ण


अटल अंतरभूत व्योम bt3c_io_ग_लिखो(अचिन्हित पूर्णांक iobase, अचिन्हित लघु addr, अचिन्हित लघु value)
अणु
	bt3c_address(iobase, addr);
	bt3c_put(iobase, value);
पूर्ण


अटल अंतरभूत अचिन्हित लघु bt3c_get(अचिन्हित पूर्णांक iobase)
अणु
	अचिन्हित लघु value = inb(iobase + DATA_L);

	value |= inb(iobase + DATA_H) << 8;

	वापस value;
पूर्ण


अटल अंतरभूत अचिन्हित लघु bt3c_पढ़ो(अचिन्हित पूर्णांक iobase, अचिन्हित लघु addr)
अणु
	bt3c_address(iobase, addr);

	वापस bt3c_get(iobase);
पूर्ण



/* ======================== Interrupt handling ======================== */


अटल पूर्णांक bt3c_ग_लिखो(अचिन्हित पूर्णांक iobase, पूर्णांक fअगरo_size, __u8 *buf, पूर्णांक len)
अणु
	पूर्णांक actual = 0;

	bt3c_address(iobase, 0x7080);

	/* Fill FIFO with current frame */
	जबतक (actual < len) अणु
		/* Transmit next byte */
		bt3c_put(iobase, buf[actual]);
		actual++;
	पूर्ण

	bt3c_io_ग_लिखो(iobase, 0x7005, actual);

	वापस actual;
पूर्ण


अटल व्योम bt3c_ग_लिखो_wakeup(काष्ठा bt3c_info *info)
अणु
	अगर (!info) अणु
		BT_ERR("Unknown device");
		वापस;
	पूर्ण

	अगर (test_and_set_bit(XMIT_SENDING, &(info->tx_state)))
		वापस;

	करो अणु
		अचिन्हित पूर्णांक iobase = info->p_dev->resource[0]->start;
		रेजिस्टर काष्ठा sk_buff *skb;
		पूर्णांक len;

		अगर (!pcmcia_dev_present(info->p_dev))
			अवरोध;

		skb = skb_dequeue(&(info->txq));
		अगर (!skb) अणु
			clear_bit(XMIT_SENDING, &(info->tx_state));
			अवरोध;
		पूर्ण

		/* Send frame */
		len = bt3c_ग_लिखो(iobase, 256, skb->data, skb->len);

		अगर (len != skb->len)
			BT_ERR("Very strange");

		kमुक्त_skb(skb);

		info->hdev->stat.byte_tx += len;

	पूर्ण जबतक (0);
पूर्ण


अटल व्योम bt3c_receive(काष्ठा bt3c_info *info)
अणु
	अचिन्हित पूर्णांक iobase;
	पूर्णांक size = 0, avail;

	अगर (!info) अणु
		BT_ERR("Unknown device");
		वापस;
	पूर्ण

	iobase = info->p_dev->resource[0]->start;

	avail = bt3c_पढ़ो(iobase, 0x7006);

	bt3c_address(iobase, 0x7480);
	जबतक (size < avail) अणु
		size++;
		info->hdev->stat.byte_rx++;

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

			hci_skb_pkt_type(info->rx_skb) = inb(iobase + DATA_L);
			inb(iobase + DATA_H);

			चयन (hci_skb_pkt_type(info->rx_skb)) अणु

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
				/* Unknown packet */
				BT_ERR("Unknown HCI packet with type 0x%02x received",
				       hci_skb_pkt_type(info->rx_skb));
				info->hdev->stat.err_rx++;

				kमुक्त_skb(info->rx_skb);
				info->rx_skb = शून्य;
				अवरोध;

			पूर्ण

		पूर्ण अन्यथा अणु

			__u8 x = inb(iobase + DATA_L);

			skb_put_u8(info->rx_skb, x);
			inb(iobase + DATA_H);
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

	bt3c_io_ग_लिखो(iobase, 0x7006, 0x0000);
पूर्ण


अटल irqवापस_t bt3c_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_inst)
अणु
	काष्ठा bt3c_info *info = dev_inst;
	अचिन्हित पूर्णांक iobase;
	पूर्णांक iir;
	irqवापस_t r = IRQ_NONE;

	अगर (!info || !info->hdev)
		/* our irq handler is shared */
		वापस IRQ_NONE;

	iobase = info->p_dev->resource[0]->start;

	spin_lock(&(info->lock));

	iir = inb(iobase + CONTROL);
	अगर (iir & 0x80) अणु
		पूर्णांक stat = bt3c_पढ़ो(iobase, 0x7001);

		अगर ((stat & 0xff) == 0x7f) अणु
			BT_ERR("Very strange (stat=0x%04x)", stat);
		पूर्ण अन्यथा अगर ((stat & 0xff) != 0xff) अणु
			अगर (stat & 0x0020) अणु
				पूर्णांक status = bt3c_पढ़ो(iobase, 0x7002) & 0x10;
				bt_dev_info(info->hdev, "Antenna %s",
							status ? "out" : "in");
			पूर्ण
			अगर (stat & 0x0001)
				bt3c_receive(info);
			अगर (stat & 0x0002) अणु
				clear_bit(XMIT_SENDING, &(info->tx_state));
				bt3c_ग_लिखो_wakeup(info);
			पूर्ण

			bt3c_io_ग_लिखो(iobase, 0x7001, 0x0000);

			outb(iir, iobase + CONTROL);
		पूर्ण
		r = IRQ_HANDLED;
	पूर्ण

	spin_unlock(&(info->lock));

	वापस r;
पूर्ण



/* ======================== HCI पूर्णांकerface ======================== */


अटल पूर्णांक bt3c_hci_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bt3c_info *info = hci_get_drvdata(hdev);

	/* Drop TX queue */
	skb_queue_purge(&(info->txq));

	वापस 0;
पूर्ण


अटल पूर्णांक bt3c_hci_खोलो(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक bt3c_hci_बंद(काष्ठा hci_dev *hdev)
अणु
	bt3c_hci_flush(hdev);

	वापस 0;
पूर्ण


अटल पूर्णांक bt3c_hci_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bt3c_info *info = hci_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;

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

	spin_lock_irqsave(&(info->lock), flags);

	bt3c_ग_लिखो_wakeup(info);

	spin_unlock_irqrestore(&(info->lock), flags);

	वापस 0;
पूर्ण



/* ======================== Card services HCI पूर्णांकeraction ======================== */


अटल पूर्णांक bt3c_load_firmware(काष्ठा bt3c_info *info,
			      स्थिर अचिन्हित अक्षर *firmware,
			      पूर्णांक count)
अणु
	अक्षर *ptr = (अक्षर *) firmware;
	अक्षर b[9];
	अचिन्हित पूर्णांक iobase, पंचांगp, tn;
	अचिन्हित दीर्घ size, addr, fcs;
	पूर्णांक i, err = 0;

	iobase = info->p_dev->resource[0]->start;

	/* Reset */
	bt3c_io_ग_लिखो(iobase, 0x8040, 0x0404);
	bt3c_io_ग_लिखो(iobase, 0x8040, 0x0400);

	udelay(1);

	bt3c_io_ग_लिखो(iobase, 0x8040, 0x0404);

	udelay(17);

	/* Load */
	जबतक (count) अणु
		अगर (ptr[0] != 'S') अणु
			BT_ERR("Bad address in firmware");
			err = -EFAULT;
			जाओ error;
		पूर्ण

		स_रखो(b, 0, माप(b));
		स_नकल(b, ptr + 2, 2);
		अगर (kम_से_अदीर्घ(b, 16, &size) < 0)
			वापस -EINVAL;

		स_रखो(b, 0, माप(b));
		स_नकल(b, ptr + 4, 8);
		अगर (kम_से_अदीर्घ(b, 16, &addr) < 0)
			वापस -EINVAL;

		स_रखो(b, 0, माप(b));
		स_नकल(b, ptr + (size * 2) + 2, 2);
		अगर (kम_से_अदीर्घ(b, 16, &fcs) < 0)
			वापस -EINVAL;

		स_रखो(b, 0, माप(b));
		क्रम (पंचांगp = 0, i = 0; i < size; i++) अणु
			स_नकल(b, ptr + (i * 2) + 2, 2);
			अगर (kstrtouपूर्णांक(b, 16, &tn))
				वापस -EINVAL;
			पंचांगp += tn;
		पूर्ण

		अगर (((पंचांगp + fcs) & 0xff) != 0xff) अणु
			BT_ERR("Checksum error in firmware");
			err = -EILSEQ;
			जाओ error;
		पूर्ण

		अगर (ptr[1] == '3') अणु
			bt3c_address(iobase, addr);

			स_रखो(b, 0, माप(b));
			क्रम (i = 0; i < (size - 4) / 2; i++) अणु
				स_नकल(b, ptr + (i * 4) + 12, 4);
				अगर (kstrtouपूर्णांक(b, 16, &पंचांगp))
					वापस -EINVAL;
				bt3c_put(iobase, पंचांगp);
			पूर्ण
		पूर्ण

		ptr   += (size * 2) + 6;
		count -= (size * 2) + 6;
	पूर्ण

	udelay(17);

	/* Boot */
	bt3c_address(iobase, 0x3000);
	outb(inb(iobase + CONTROL) | 0x40, iobase + CONTROL);

error:
	udelay(17);

	/* Clear */
	bt3c_io_ग_लिखो(iobase, 0x7006, 0x0000);
	bt3c_io_ग_लिखो(iobase, 0x7005, 0x0000);
	bt3c_io_ग_लिखो(iobase, 0x7001, 0x0000);

	वापस err;
पूर्ण


अटल पूर्णांक bt3c_खोलो(काष्ठा bt3c_info *info)
अणु
	स्थिर काष्ठा firmware *firmware;
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	spin_lock_init(&(info->lock));

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

	hdev->खोलो  = bt3c_hci_खोलो;
	hdev->बंद = bt3c_hci_बंद;
	hdev->flush = bt3c_hci_flush;
	hdev->send  = bt3c_hci_send_frame;

	/* Load firmware */
	err = request_firmware(&firmware, "BT3CPCC.bin", &info->p_dev->dev);
	अगर (err < 0) अणु
		BT_ERR("Firmware request failed");
		जाओ error;
	पूर्ण

	err = bt3c_load_firmware(info, firmware->data, firmware->size);

	release_firmware(firmware);

	अगर (err < 0) अणु
		BT_ERR("Firmware loading failed");
		जाओ error;
	पूर्ण

	/* Timeout beक्रमe it is safe to send the first HCI packet */
	msleep(1000);

	/* Register HCI device */
	err = hci_रेजिस्टर_dev(hdev);
	अगर (err < 0) अणु
		BT_ERR("Can't register HCI device");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	info->hdev = शून्य;
	hci_मुक्त_dev(hdev);
	वापस err;
पूर्ण


अटल पूर्णांक bt3c_बंद(काष्ठा bt3c_info *info)
अणु
	काष्ठा hci_dev *hdev = info->hdev;

	अगर (!hdev)
		वापस -ENODEV;

	bt3c_hci_बंद(hdev);

	hci_unरेजिस्टर_dev(hdev);
	hci_मुक्त_dev(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक bt3c_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा bt3c_info *info;

	/* Create new info device */
	info = devm_kzalloc(&link->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->p_dev = link;
	link->priv = info;

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_VPP |
		CONF_AUTO_SET_IO;

	वापस bt3c_config(link);
पूर्ण


अटल व्योम bt3c_detach(काष्ठा pcmcia_device *link)
अणु
	bt3c_release(link);
पूर्ण

अटल पूर्णांक bt3c_check_config(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	पूर्णांक *try = priv_data;

	अगर (!try)
		p_dev->io_lines = 16;

	अगर ((p_dev->resource[0]->end != 8) || (p_dev->resource[0]->start == 0))
		वापस -EINVAL;

	p_dev->resource[0]->end = 8;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;

	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक bt3c_check_config_notpicky(काष्ठा pcmcia_device *p_dev,
				      व्योम *priv_data)
अणु
	अटल अचिन्हित पूर्णांक base[5] = अणु 0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x0 पूर्ण;
	पूर्णांक j;

	अगर (p_dev->io_lines > 3)
		वापस -ENODEV;

	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->resource[0]->end = 8;

	क्रम (j = 0; j < 5; j++) अणु
		p_dev->resource[0]->start = base[j];
		p_dev->io_lines = base[j] ? 16 : 3;
		अगर (!pcmcia_request_io(p_dev))
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक bt3c_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा bt3c_info *info = link->priv;
	पूर्णांक i;
	अचिन्हित दीर्घ try;

	/* First pass: look क्रम a config entry that looks normal.
	 * Two tries: without IO aliases, then with aliases
	 */
	क्रम (try = 0; try < 2; try++)
		अगर (!pcmcia_loop_config(link, bt3c_check_config, (व्योम *) try))
			जाओ found_port;

	/* Second pass: try to find an entry that isn't picky about
	 * its base address, then try to grab any standard serial port
	 * address, and finally try to get any मुक्त port.
	 */
	अगर (!pcmcia_loop_config(link, bt3c_check_config_notpicky, शून्य))
		जाओ found_port;

	BT_ERR("No usable port range found");
	जाओ failed;

found_port:
	i = pcmcia_request_irq(link, &bt3c_पूर्णांकerrupt);
	अगर (i != 0)
		जाओ failed;

	i = pcmcia_enable_device(link);
	अगर (i != 0)
		जाओ failed;

	अगर (bt3c_खोलो(info) != 0)
		जाओ failed;

	वापस 0;

failed:
	bt3c_release(link);
	वापस -ENODEV;
पूर्ण


अटल व्योम bt3c_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा bt3c_info *info = link->priv;

	bt3c_बंद(info);

	pcmcia_disable_device(link);
पूर्ण


अटल स्थिर काष्ठा pcmcia_device_id bt3c_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID13("3COM", "Bluetooth PC Card", 0xefce0a31, 0xd4ce9b02),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, bt3c_ids);

अटल काष्ठा pcmcia_driver bt3c_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "bt3c_cs",
	.probe		= bt3c_probe,
	.हटाओ		= bt3c_detach,
	.id_table	= bt3c_ids,
पूर्ण;
module_pcmcia_driver(bt3c_driver);

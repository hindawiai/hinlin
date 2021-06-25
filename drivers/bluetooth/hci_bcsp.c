<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth HCI UART driver
 *
 *  Copyright (C) 2002-2003  Fabrizio Gennari <fabrizio.gennari@philips.com>
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
#समावेश <linux/bitrev.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"

अटल bool txcrc = true;
अटल bool hciextn = true;

#घोषणा BCSP_TXWINSIZE	4

#घोषणा BCSP_ACK_PKT	0x05
#घोषणा BCSP_LE_PKT	0x06

काष्ठा bcsp_काष्ठा अणु
	काष्ठा sk_buff_head unack;	/* Unack'ed packets queue */
	काष्ठा sk_buff_head rel;	/* Reliable packets queue */
	काष्ठा sk_buff_head unrel;	/* Unreliable packets queue */

	अचिन्हित दीर्घ rx_count;
	काष्ठा	sk_buff *rx_skb;
	u8	rxseq_txack;		/* rxseq == txack. */
	u8	rxack;			/* Last packet sent by us that the peer ack'ed */
	काष्ठा	समयr_list tbcsp;
	काष्ठा	hci_uart *hu;

	क्रमागत अणु
		BCSP_W4_PKT_DELIMITER,
		BCSP_W4_PKT_START,
		BCSP_W4_BCSP_HDR,
		BCSP_W4_DATA,
		BCSP_W4_CRC
	पूर्ण rx_state;

	क्रमागत अणु
		BCSP_ESCSTATE_NOESC,
		BCSP_ESCSTATE_ESC
	पूर्ण rx_esc_state;

	u8	use_crc;
	u16	message_crc;
	u8	txack_req;		/* Do we need to send ack's to the peer? */

	/* Reliable packet sequence number - used to assign seq to each rel pkt. */
	u8	msgq_txseq;
पूर्ण;

/* ---- BCSP CRC calculation ---- */

/* Table क्रम calculating CRC क्रम polynomial 0x1021, LSB processed first,
 * initial value 0xffff, bits shअगरted in reverse order.
 */

अटल स्थिर u16 crc_table[] = अणु
	0x0000, 0x1081, 0x2102, 0x3183,
	0x4204, 0x5285, 0x6306, 0x7387,
	0x8408, 0x9489, 0xa50a, 0xb58b,
	0xc60c, 0xd68d, 0xe70e, 0xf78f
पूर्ण;

/* Initialise the crc calculator */
#घोषणा BCSP_CRC_INIT(x) x = 0xffff

/* Update crc with next data byte
 *
 * Implementation note
 *     The data byte is treated as two nibbles.  The crc is generated
 *     in reverse, i.e., bits are fed पूर्णांकo the रेजिस्टर from the top.
 */
अटल व्योम bcsp_crc_update(u16 *crc, u8 d)
अणु
	u16 reg = *crc;

	reg = (reg >> 4) ^ crc_table[(reg ^ d) & 0x000f];
	reg = (reg >> 4) ^ crc_table[(reg ^ (d >> 4)) & 0x000f];

	*crc = reg;
पूर्ण

/* ---- BCSP core ---- */

अटल व्योम bcsp_slip_msgdelim(काष्ठा sk_buff *skb)
अणु
	स्थिर अक्षर pkt_delim = 0xc0;

	skb_put_data(skb, &pkt_delim, 1);
पूर्ण

अटल व्योम bcsp_slip_one_byte(काष्ठा sk_buff *skb, u8 c)
अणु
	स्थिर अक्षर esc_c0[2] = अणु 0xdb, 0xdc पूर्ण;
	स्थिर अक्षर esc_db[2] = अणु 0xdb, 0xdd पूर्ण;

	चयन (c) अणु
	हाल 0xc0:
		skb_put_data(skb, &esc_c0, 2);
		अवरोध;
	हाल 0xdb:
		skb_put_data(skb, &esc_db, 2);
		अवरोध;
	शेष:
		skb_put_data(skb, &c, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक bcsp_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा bcsp_काष्ठा *bcsp = hu->priv;

	अगर (skb->len > 0xFFF) अणु
		BT_ERR("Packet too long");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_ACLDATA_PKT:
	हाल HCI_COMMAND_PKT:
		skb_queue_tail(&bcsp->rel, skb);
		अवरोध;

	हाल HCI_SCODATA_PKT:
		skb_queue_tail(&bcsp->unrel, skb);
		अवरोध;

	शेष:
		BT_ERR("Unknown packet type");
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *bcsp_prepare_pkt(काष्ठा bcsp_काष्ठा *bcsp, u8 *data,
					पूर्णांक len, पूर्णांक pkt_type)
अणु
	काष्ठा sk_buff *nskb;
	u8 hdr[4], chan;
	u16 BCSP_CRC_INIT(bcsp_txmsg_crc);
	पूर्णांक rel, i;

	चयन (pkt_type) अणु
	हाल HCI_ACLDATA_PKT:
		chan = 6;	/* BCSP ACL channel */
		rel = 1;	/* reliable channel */
		अवरोध;
	हाल HCI_COMMAND_PKT:
		chan = 5;	/* BCSP cmd/evt channel */
		rel = 1;	/* reliable channel */
		अवरोध;
	हाल HCI_SCODATA_PKT:
		chan = 7;	/* BCSP SCO channel */
		rel = 0;	/* unreliable channel */
		अवरोध;
	हाल BCSP_LE_PKT:
		chan = 1;	/* BCSP LE channel */
		rel = 0;	/* unreliable channel */
		अवरोध;
	हाल BCSP_ACK_PKT:
		chan = 0;	/* BCSP पूर्णांकernal channel */
		rel = 0;	/* unreliable channel */
		अवरोध;
	शेष:
		BT_ERR("Unknown packet type");
		वापस शून्य;
	पूर्ण

	अगर (hciextn && chan == 5) अणु
		__le16 opcode = ((काष्ठा hci_command_hdr *)data)->opcode;

		/* Venकरोr specअगरic commands */
		अगर (hci_opcode_ogf(__le16_to_cpu(opcode)) == 0x3f) अणु
			u8 desc = *(data + HCI_COMMAND_HDR_SIZE);

			अगर ((desc & 0xf0) == 0xc0) अणु
				data += HCI_COMMAND_HDR_SIZE + 1;
				len  -= HCI_COMMAND_HDR_SIZE + 1;
				chan = desc & 0x0f;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Max len of packet: (original len +4(bcsp hdr) +2(crc))*2
	 * (because bytes 0xc0 and 0xdb are escaped, worst हाल is
	 * when the packet is all made of 0xc0 and 0xdb :) )
	 * + 2 (0xc0 delimiters at start and end).
	 */

	nskb = alloc_skb((len + 6) * 2 + 2, GFP_ATOMIC);
	अगर (!nskb)
		वापस शून्य;

	hci_skb_pkt_type(nskb) = pkt_type;

	bcsp_slip_msgdelim(nskb);

	hdr[0] = bcsp->rxseq_txack << 3;
	bcsp->txack_req = 0;
	BT_DBG("We request packet no %u to card", bcsp->rxseq_txack);

	अगर (rel) अणु
		hdr[0] |= 0x80 + bcsp->msgq_txseq;
		BT_DBG("Sending packet with seqno %u", bcsp->msgq_txseq);
		bcsp->msgq_txseq = (bcsp->msgq_txseq + 1) & 0x07;
	पूर्ण

	अगर (bcsp->use_crc)
		hdr[0] |= 0x40;

	hdr[1] = ((len << 4) & 0xff) | chan;
	hdr[2] = len >> 4;
	hdr[3] = ~(hdr[0] + hdr[1] + hdr[2]);

	/* Put BCSP header */
	क्रम (i = 0; i < 4; i++) अणु
		bcsp_slip_one_byte(nskb, hdr[i]);

		अगर (bcsp->use_crc)
			bcsp_crc_update(&bcsp_txmsg_crc, hdr[i]);
	पूर्ण

	/* Put payload */
	क्रम (i = 0; i < len; i++) अणु
		bcsp_slip_one_byte(nskb, data[i]);

		अगर (bcsp->use_crc)
			bcsp_crc_update(&bcsp_txmsg_crc, data[i]);
	पूर्ण

	/* Put CRC */
	अगर (bcsp->use_crc) अणु
		bcsp_txmsg_crc = bitrev16(bcsp_txmsg_crc);
		bcsp_slip_one_byte(nskb, (u8)((bcsp_txmsg_crc >> 8) & 0x00ff));
		bcsp_slip_one_byte(nskb, (u8)(bcsp_txmsg_crc & 0x00ff));
	पूर्ण

	bcsp_slip_msgdelim(nskb);
	वापस nskb;
पूर्ण

/* This is a reग_लिखो of pkt_avail in ABCSP */
अटल काष्ठा sk_buff *bcsp_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcsp_काष्ठा *bcsp = hu->priv;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;

	/* First of all, check क्रम unreliable messages in the queue,
	 * since they have priority
	 */

	skb = skb_dequeue(&bcsp->unrel);
	अगर (skb != शून्य) अणु
		काष्ठा sk_buff *nskb;

		nskb = bcsp_prepare_pkt(bcsp, skb->data, skb->len,
					hci_skb_pkt_type(skb));
		अगर (nskb) अणु
			kमुक्त_skb(skb);
			वापस nskb;
		पूर्ण अन्यथा अणु
			skb_queue_head(&bcsp->unrel, skb);
			BT_ERR("Could not dequeue pkt because alloc_skb failed");
		पूर्ण
	पूर्ण

	/* Now, try to send a reliable pkt. We can only send a
	 * reliable packet अगर the number of packets sent but not yet ack'ed
	 * is < than the winsize
	 */

	spin_lock_irqsave_nested(&bcsp->unack.lock, flags, SINGLE_DEPTH_NESTING);

	अगर (bcsp->unack.qlen < BCSP_TXWINSIZE) अणु
		skb = skb_dequeue(&bcsp->rel);
		अगर (skb != शून्य) अणु
			काष्ठा sk_buff *nskb;

			nskb = bcsp_prepare_pkt(bcsp, skb->data, skb->len,
						hci_skb_pkt_type(skb));
			अगर (nskb) अणु
				__skb_queue_tail(&bcsp->unack, skb);
				mod_समयr(&bcsp->tbcsp, jअगरfies + HZ / 4);
				spin_unlock_irqrestore(&bcsp->unack.lock, flags);
				वापस nskb;
			पूर्ण अन्यथा अणु
				skb_queue_head(&bcsp->rel, skb);
				BT_ERR("Could not dequeue pkt because alloc_skb failed");
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&bcsp->unack.lock, flags);

	/* We could not send a reliable packet, either because there are
	 * none or because there are too many unack'ed pkts. Did we receive
	 * any packets we have not acknowledged yet ?
	 */

	अगर (bcsp->txack_req) अणु
		/* अगर so, craft an empty ACK pkt and send it on BCSP unreliable
		 * channel 0
		 */
		काष्ठा sk_buff *nskb = bcsp_prepare_pkt(bcsp, शून्य, 0, BCSP_ACK_PKT);
		वापस nskb;
	पूर्ण

	/* We have nothing to send */
	वापस शून्य;
पूर्ण

अटल पूर्णांक bcsp_flush(काष्ठा hci_uart *hu)
अणु
	BT_DBG("hu %p", hu);
	वापस 0;
पूर्ण

/* Remove ack'ed packets */
अटल व्योम bcsp_pkt_cull(काष्ठा bcsp_काष्ठा *bcsp)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, pkts_to_be_हटाओd;
	u8 seqno;

	spin_lock_irqsave(&bcsp->unack.lock, flags);

	pkts_to_be_हटाओd = skb_queue_len(&bcsp->unack);
	seqno = bcsp->msgq_txseq;

	जबतक (pkts_to_be_हटाओd) अणु
		अगर (bcsp->rxack == seqno)
			अवरोध;
		pkts_to_be_हटाओd--;
		seqno = (seqno - 1) & 0x07;
	पूर्ण

	अगर (bcsp->rxack != seqno)
		BT_ERR("Peer acked invalid packet");

	BT_DBG("Removing %u pkts out of %u, up to seqno %u",
	       pkts_to_be_हटाओd, skb_queue_len(&bcsp->unack),
	       (seqno - 1) & 0x07);

	i = 0;
	skb_queue_walk_safe(&bcsp->unack, skb, पंचांगp) अणु
		अगर (i >= pkts_to_be_हटाओd)
			अवरोध;
		i++;

		__skb_unlink(skb, &bcsp->unack);
		kमुक्त_skb(skb);
	पूर्ण

	अगर (skb_queue_empty(&bcsp->unack))
		del_समयr(&bcsp->tbcsp);

	spin_unlock_irqrestore(&bcsp->unack.lock, flags);

	अगर (i != pkts_to_be_हटाओd)
		BT_ERR("Removed only %u out of %u pkts", i, pkts_to_be_हटाओd);
पूर्ण

/* Handle BCSP link-establishment packets. When we
 * detect a "sync" packet, symptom that the BT module has reset,
 * we करो nothing :) (yet)
 */
अटल व्योम bcsp_handle_le_pkt(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcsp_काष्ठा *bcsp = hu->priv;
	u8 conf_pkt[4]     = अणु 0xad, 0xef, 0xac, 0xed पूर्ण;
	u8 conf_rsp_pkt[4] = अणु 0xde, 0xad, 0xd0, 0xd0 पूर्ण;
	u8 sync_pkt[4]     = अणु 0xda, 0xdc, 0xed, 0xed पूर्ण;

	/* spot "conf" pkts and reply with a "conf rsp" pkt */
	अगर (bcsp->rx_skb->data[1] >> 4 == 4 && bcsp->rx_skb->data[2] == 0 &&
	    !स_भेद(&bcsp->rx_skb->data[4], conf_pkt, 4)) अणु
		काष्ठा sk_buff *nskb = alloc_skb(4, GFP_ATOMIC);

		BT_DBG("Found a LE conf pkt");
		अगर (!nskb)
			वापस;
		skb_put_data(nskb, conf_rsp_pkt, 4);
		hci_skb_pkt_type(nskb) = BCSP_LE_PKT;

		skb_queue_head(&bcsp->unrel, nskb);
		hci_uart_tx_wakeup(hu);
	पूर्ण
	/* Spot "sync" pkts. If we find one...disaster! */
	अन्यथा अगर (bcsp->rx_skb->data[1] >> 4 == 4 && bcsp->rx_skb->data[2] == 0 &&
		 !स_भेद(&bcsp->rx_skb->data[4], sync_pkt, 4)) अणु
		BT_ERR("Found a LE sync pkt, card has reset");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bcsp_unslip_one_byte(काष्ठा bcsp_काष्ठा *bcsp, अचिन्हित अक्षर byte)
अणु
	स्थिर u8 c0 = 0xc0, db = 0xdb;

	चयन (bcsp->rx_esc_state) अणु
	हाल BCSP_ESCSTATE_NOESC:
		चयन (byte) अणु
		हाल 0xdb:
			bcsp->rx_esc_state = BCSP_ESCSTATE_ESC;
			अवरोध;
		शेष:
			skb_put_data(bcsp->rx_skb, &byte, 1);
			अगर ((bcsp->rx_skb->data[0] & 0x40) != 0 &&
			    bcsp->rx_state != BCSP_W4_CRC)
				bcsp_crc_update(&bcsp->message_crc, byte);
			bcsp->rx_count--;
		पूर्ण
		अवरोध;

	हाल BCSP_ESCSTATE_ESC:
		चयन (byte) अणु
		हाल 0xdc:
			skb_put_data(bcsp->rx_skb, &c0, 1);
			अगर ((bcsp->rx_skb->data[0] & 0x40) != 0 &&
			    bcsp->rx_state != BCSP_W4_CRC)
				bcsp_crc_update(&bcsp->message_crc, 0xc0);
			bcsp->rx_esc_state = BCSP_ESCSTATE_NOESC;
			bcsp->rx_count--;
			अवरोध;

		हाल 0xdd:
			skb_put_data(bcsp->rx_skb, &db, 1);
			अगर ((bcsp->rx_skb->data[0] & 0x40) != 0 &&
			    bcsp->rx_state != BCSP_W4_CRC)
				bcsp_crc_update(&bcsp->message_crc, 0xdb);
			bcsp->rx_esc_state = BCSP_ESCSTATE_NOESC;
			bcsp->rx_count--;
			अवरोध;

		शेष:
			BT_ERR("Invalid byte %02x after esc byte", byte);
			kमुक्त_skb(bcsp->rx_skb);
			bcsp->rx_skb = शून्य;
			bcsp->rx_state = BCSP_W4_PKT_DELIMITER;
			bcsp->rx_count = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bcsp_complete_rx_pkt(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcsp_काष्ठा *bcsp = hu->priv;
	पूर्णांक pass_up = 0;

	अगर (bcsp->rx_skb->data[0] & 0x80) अणु	/* reliable pkt */
		BT_DBG("Received seqno %u from card", bcsp->rxseq_txack);

		/* check the rx sequence number is as expected */
		अगर ((bcsp->rx_skb->data[0] & 0x07) == bcsp->rxseq_txack) अणु
			bcsp->rxseq_txack++;
			bcsp->rxseq_txack %= 0x8;
		पूर्ण अन्यथा अणु
			/* handle re-transmitted packet or
			 * when packet was missed
			 */
			BT_ERR("Out-of-order packet arrived, got %u expected %u",
			       bcsp->rx_skb->data[0] & 0x07, bcsp->rxseq_txack);

			/* करो not process out-of-order packet payload */
			pass_up = 2;
		पूर्ण

		/* send current txack value to all received reliable packets */
		bcsp->txack_req = 1;

		/* If needed, transmit an ack pkt */
		hci_uart_tx_wakeup(hu);
	पूर्ण

	bcsp->rxack = (bcsp->rx_skb->data[0] >> 3) & 0x07;
	BT_DBG("Request for pkt %u from card", bcsp->rxack);

	/* handle received ACK indications,
	 * including those from out-of-order packets
	 */
	bcsp_pkt_cull(bcsp);

	अगर (pass_up != 2) अणु
		अगर ((bcsp->rx_skb->data[1] & 0x0f) == 6 &&
		    (bcsp->rx_skb->data[0] & 0x80)) अणु
			hci_skb_pkt_type(bcsp->rx_skb) = HCI_ACLDATA_PKT;
			pass_up = 1;
		पूर्ण अन्यथा अगर ((bcsp->rx_skb->data[1] & 0x0f) == 5 &&
			   (bcsp->rx_skb->data[0] & 0x80)) अणु
			hci_skb_pkt_type(bcsp->rx_skb) = HCI_EVENT_PKT;
			pass_up = 1;
		पूर्ण अन्यथा अगर ((bcsp->rx_skb->data[1] & 0x0f) == 7) अणु
			hci_skb_pkt_type(bcsp->rx_skb) = HCI_SCODATA_PKT;
			pass_up = 1;
		पूर्ण अन्यथा अगर ((bcsp->rx_skb->data[1] & 0x0f) == 1 &&
			   !(bcsp->rx_skb->data[0] & 0x80)) अणु
			bcsp_handle_le_pkt(hu);
			pass_up = 0;
		पूर्ण अन्यथा अणु
			pass_up = 0;
		पूर्ण
	पूर्ण

	अगर (pass_up == 0) अणु
		काष्ठा hci_event_hdr hdr;
		u8 desc = (bcsp->rx_skb->data[1] & 0x0f);

		अगर (desc != 0 && desc != 1) अणु
			अगर (hciextn) अणु
				desc |= 0xc0;
				skb_pull(bcsp->rx_skb, 4);
				स_नकल(skb_push(bcsp->rx_skb, 1), &desc, 1);

				hdr.evt = 0xff;
				hdr.plen = bcsp->rx_skb->len;
				स_नकल(skb_push(bcsp->rx_skb, HCI_EVENT_HDR_SIZE), &hdr, HCI_EVENT_HDR_SIZE);
				hci_skb_pkt_type(bcsp->rx_skb) = HCI_EVENT_PKT;

				hci_recv_frame(hu->hdev, bcsp->rx_skb);
			पूर्ण अन्यथा अणु
				BT_ERR("Packet for unknown channel (%u %s)",
				       bcsp->rx_skb->data[1] & 0x0f,
				       bcsp->rx_skb->data[0] & 0x80 ?
				       "reliable" : "unreliable");
				kमुक्त_skb(bcsp->rx_skb);
			पूर्ण
		पूर्ण अन्यथा
			kमुक्त_skb(bcsp->rx_skb);
	पूर्ण अन्यथा अगर (pass_up == 1) अणु
		/* Pull out BCSP hdr */
		skb_pull(bcsp->rx_skb, 4);

		hci_recv_frame(hu->hdev, bcsp->rx_skb);
	पूर्ण अन्यथा अणु
		/* ignore packet payload of alपढ़ोy ACKed re-transmitted
		 * packets or when a packet was missed in the BCSP winकरोw
		 */
		kमुक्त_skb(bcsp->rx_skb);
	पूर्ण

	bcsp->rx_state = BCSP_W4_PKT_DELIMITER;
	bcsp->rx_skb = शून्य;
पूर्ण

अटल u16 bscp_get_crc(काष्ठा bcsp_काष्ठा *bcsp)
अणु
	वापस get_unaligned_be16(&bcsp->rx_skb->data[bcsp->rx_skb->len - 2]);
पूर्ण

/* Recv data */
अटल पूर्णांक bcsp_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा bcsp_काष्ठा *bcsp = hu->priv;
	स्थिर अचिन्हित अक्षर *ptr;

	BT_DBG("hu %p count %d rx_state %d rx_count %ld",
	       hu, count, bcsp->rx_state, bcsp->rx_count);

	ptr = data;
	जबतक (count) अणु
		अगर (bcsp->rx_count) अणु
			अगर (*ptr == 0xc0) अणु
				BT_ERR("Short BCSP packet");
				kमुक्त_skb(bcsp->rx_skb);
				bcsp->rx_skb = शून्य;
				bcsp->rx_state = BCSP_W4_PKT_START;
				bcsp->rx_count = 0;
			पूर्ण अन्यथा
				bcsp_unslip_one_byte(bcsp, *ptr);

			ptr++; count--;
			जारी;
		पूर्ण

		चयन (bcsp->rx_state) अणु
		हाल BCSP_W4_BCSP_HDR:
			अगर ((0xff & (u8)~(bcsp->rx_skb->data[0] + bcsp->rx_skb->data[1] +
			    bcsp->rx_skb->data[2])) != bcsp->rx_skb->data[3]) अणु
				BT_ERR("Error in BCSP hdr checksum");
				kमुक्त_skb(bcsp->rx_skb);
				bcsp->rx_skb = शून्य;
				bcsp->rx_state = BCSP_W4_PKT_DELIMITER;
				bcsp->rx_count = 0;
				जारी;
			पूर्ण
			bcsp->rx_state = BCSP_W4_DATA;
			bcsp->rx_count = (bcsp->rx_skb->data[1] >> 4) +
					(bcsp->rx_skb->data[2] << 4);	/* May be 0 */
			जारी;

		हाल BCSP_W4_DATA:
			अगर (bcsp->rx_skb->data[0] & 0x40) अणु	/* pkt with crc */
				bcsp->rx_state = BCSP_W4_CRC;
				bcsp->rx_count = 2;
			पूर्ण अन्यथा
				bcsp_complete_rx_pkt(hu);
			जारी;

		हाल BCSP_W4_CRC:
			अगर (bitrev16(bcsp->message_crc) != bscp_get_crc(bcsp)) अणु
				BT_ERR("Checksum failed: computed %04x received %04x",
				       bitrev16(bcsp->message_crc),
				       bscp_get_crc(bcsp));

				kमुक्त_skb(bcsp->rx_skb);
				bcsp->rx_skb = शून्य;
				bcsp->rx_state = BCSP_W4_PKT_DELIMITER;
				bcsp->rx_count = 0;
				जारी;
			पूर्ण
			skb_trim(bcsp->rx_skb, bcsp->rx_skb->len - 2);
			bcsp_complete_rx_pkt(hu);
			जारी;

		हाल BCSP_W4_PKT_DELIMITER:
			चयन (*ptr) अणु
			हाल 0xc0:
				bcsp->rx_state = BCSP_W4_PKT_START;
				अवरोध;
			शेष:
				/*BT_ERR("Ignoring byte %02x", *ptr);*/
				अवरोध;
			पूर्ण
			ptr++; count--;
			अवरोध;

		हाल BCSP_W4_PKT_START:
			चयन (*ptr) अणु
			हाल 0xc0:
				ptr++; count--;
				अवरोध;

			शेष:
				bcsp->rx_state = BCSP_W4_BCSP_HDR;
				bcsp->rx_count = 4;
				bcsp->rx_esc_state = BCSP_ESCSTATE_NOESC;
				BCSP_CRC_INIT(bcsp->message_crc);

				/* Do not increment ptr or decrement count
				 * Allocate packet. Max len of a BCSP pkt=
				 * 0xFFF (payload) +4 (header) +2 (crc)
				 */

				bcsp->rx_skb = bt_skb_alloc(0x1005, GFP_ATOMIC);
				अगर (!bcsp->rx_skb) अणु
					BT_ERR("Can't allocate mem for new packet");
					bcsp->rx_state = BCSP_W4_PKT_DELIMITER;
					bcsp->rx_count = 0;
					वापस 0;
				पूर्ण
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

	/* Arrange to retransmit all messages in the relq. */
अटल व्योम bcsp_समयd_event(काष्ठा समयr_list *t)
अणु
	काष्ठा bcsp_काष्ठा *bcsp = from_समयr(bcsp, t, tbcsp);
	काष्ठा hci_uart *hu = bcsp->hu;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	BT_DBG("hu %p retransmitting %u pkts", hu, bcsp->unack.qlen);

	spin_lock_irqsave_nested(&bcsp->unack.lock, flags, SINGLE_DEPTH_NESTING);

	जबतक ((skb = __skb_dequeue_tail(&bcsp->unack)) != शून्य) अणु
		bcsp->msgq_txseq = (bcsp->msgq_txseq - 1) & 0x07;
		skb_queue_head(&bcsp->rel, skb);
	पूर्ण

	spin_unlock_irqrestore(&bcsp->unack.lock, flags);

	hci_uart_tx_wakeup(hu);
पूर्ण

अटल पूर्णांक bcsp_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcsp_काष्ठा *bcsp;

	BT_DBG("hu %p", hu);

	bcsp = kzalloc(माप(*bcsp), GFP_KERNEL);
	अगर (!bcsp)
		वापस -ENOMEM;

	hu->priv = bcsp;
	bcsp->hu = hu;
	skb_queue_head_init(&bcsp->unack);
	skb_queue_head_init(&bcsp->rel);
	skb_queue_head_init(&bcsp->unrel);

	समयr_setup(&bcsp->tbcsp, bcsp_समयd_event, 0);

	bcsp->rx_state = BCSP_W4_PKT_DELIMITER;

	अगर (txcrc)
		bcsp->use_crc = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक bcsp_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcsp_काष्ठा *bcsp = hu->priv;

	del_समयr_sync(&bcsp->tbcsp);

	hu->priv = शून्य;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&bcsp->unack);
	skb_queue_purge(&bcsp->rel);
	skb_queue_purge(&bcsp->unrel);

	अगर (bcsp->rx_skb) अणु
		kमुक्त_skb(bcsp->rx_skb);
		bcsp->rx_skb = शून्य;
	पूर्ण

	kमुक्त(bcsp);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto bcsp = अणु
	.id		= HCI_UART_BCSP,
	.name		= "BCSP",
	.खोलो		= bcsp_खोलो,
	.बंद		= bcsp_बंद,
	.enqueue	= bcsp_enqueue,
	.dequeue	= bcsp_dequeue,
	.recv		= bcsp_recv,
	.flush		= bcsp_flush
पूर्ण;

पूर्णांक __init bcsp_init(व्योम)
अणु
	वापस hci_uart_रेजिस्टर_proto(&bcsp);
पूर्ण

पूर्णांक __निकास bcsp_deinit(व्योम)
अणु
	वापस hci_uart_unरेजिस्टर_proto(&bcsp);
पूर्ण

module_param(txcrc, bool, 0644);
MODULE_PARM_DESC(txcrc, "Transmit CRC with every BCSP packet");

module_param(hciextn, bool, 0644);
MODULE_PARM_DESC(hciextn, "Convert HCI Extensions into BCSP packets");

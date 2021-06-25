<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *  Generic Bluetooth HCI UART driver
 *
 *  Copyright (C) 2015-2018  Intel Corporation
 */

#समावेश <यंत्र/unaligned.h>

काष्ठा h4_recv_pkt अणु
	u8  type;	/* Packet type */
	u8  hlen;	/* Header length */
	u8  loff;	/* Data length offset in header */
	u8  lsize;	/* Data length field size */
	u16 maxlen;	/* Max overall packet length */
	पूर्णांक (*recv)(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
पूर्ण;

#घोषणा H4_RECV_ACL \
	.type = HCI_ACLDATA_PKT, \
	.hlen = HCI_ACL_HDR_SIZE, \
	.loff = 2, \
	.lsize = 2, \
	.maxlen = HCI_MAX_FRAME_SIZE \

#घोषणा H4_RECV_SCO \
	.type = HCI_SCODATA_PKT, \
	.hlen = HCI_SCO_HDR_SIZE, \
	.loff = 2, \
	.lsize = 1, \
	.maxlen = HCI_MAX_SCO_SIZE

#घोषणा H4_RECV_EVENT \
	.type = HCI_EVENT_PKT, \
	.hlen = HCI_EVENT_HDR_SIZE, \
	.loff = 1, \
	.lsize = 1, \
	.maxlen = HCI_MAX_EVENT_SIZE

अटल अंतरभूत काष्ठा sk_buff *h4_recv_buf(काष्ठा hci_dev *hdev,
					  काष्ठा sk_buff *skb,
					  स्थिर अचिन्हित अक्षर *buffer,
					  पूर्णांक count,
					  स्थिर काष्ठा h4_recv_pkt *pkts,
					  पूर्णांक pkts_count)
अणु
	/* Check क्रम error from previous call */
	अगर (IS_ERR(skb))
		skb = शून्य;

	जबतक (count) अणु
		पूर्णांक i, len;

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
				/* No more data, complete frame */
				(&pkts[i])->recv(hdev, skb);
				skb = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Complete frame */
			(&pkts[i])->recv(hdev, skb);
			skb = शून्य;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण

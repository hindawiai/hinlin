<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/अगर_arp.h>

#समावेश <net/6lowpan.h>
#समावेश <net/mac802154.h>
#समावेश <net/ieee802154_netdev.h>

#समावेश "6lowpan_i.h"

#घोषणा LOWPAN_DISPATCH_FIRST		0xc0
#घोषणा LOWPAN_DISPATCH_FRAG_MASK	0xf8

#घोषणा LOWPAN_DISPATCH_NALP		0x00
#घोषणा LOWPAN_DISPATCH_ESC		0x40
#घोषणा LOWPAN_DISPATCH_HC1		0x42
#घोषणा LOWPAN_DISPATCH_DFF		0x43
#घोषणा LOWPAN_DISPATCH_BC0		0x50
#घोषणा LOWPAN_DISPATCH_MESH		0x80

अटल पूर्णांक lowpan_give_skb_to_device(काष्ठा sk_buff *skb)
अणु
	skb->protocol = htons(ETH_P_IPV6);
	skb->dev->stats.rx_packets++;
	skb->dev->stats.rx_bytes += skb->len;

	वापस netअगर_rx(skb);
पूर्ण

अटल पूर्णांक lowpan_rx_handlers_result(काष्ठा sk_buff *skb, lowpan_rx_result res)
अणु
	चयन (res) अणु
	हाल RX_CONTINUE:
		/* nobody cared about this packet */
		net_warn_ratelimited("%s: received unknown dispatch\n",
				     __func__);

		fallthrough;
	हाल RX_DROP_UNUSABLE:
		kमुक्त_skb(skb);

		fallthrough;
	हाल RX_DROP:
		वापस NET_RX_DROP;
	हाल RX_QUEUED:
		वापस lowpan_give_skb_to_device(skb);
	शेष:
		अवरोध;
	पूर्ण

	वापस NET_RX_DROP;
पूर्ण

अटल अंतरभूत bool lowpan_is_frag1(u8 dispatch)
अणु
	वापस (dispatch & LOWPAN_DISPATCH_FRAG_MASK) == LOWPAN_DISPATCH_FRAG1;
पूर्ण

अटल अंतरभूत bool lowpan_is_fragn(u8 dispatch)
अणु
	वापस (dispatch & LOWPAN_DISPATCH_FRAG_MASK) == LOWPAN_DISPATCH_FRAGN;
पूर्ण

अटल lowpan_rx_result lowpan_rx_h_frag(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	अगर (!(lowpan_is_frag1(*skb_network_header(skb)) ||
	      lowpan_is_fragn(*skb_network_header(skb))))
		वापस RX_CONTINUE;

	ret = lowpan_frag_rcv(skb, *skb_network_header(skb) &
			      LOWPAN_DISPATCH_FRAG_MASK);
	अगर (ret == 1)
		वापस RX_QUEUED;

	/* Packet is मुक्तd by lowpan_frag_rcv on error or put पूर्णांकo the frag
	 * bucket.
	 */
	वापस RX_DROP;
पूर्ण

पूर्णांक lowpan_iphc_decompress(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee802154_hdr hdr;

	अगर (ieee802154_hdr_peek_addrs(skb, &hdr) < 0)
		वापस -EINVAL;

	वापस lowpan_header_decompress(skb, skb->dev, &hdr.dest, &hdr.source);
पूर्ण

अटल lowpan_rx_result lowpan_rx_h_iphc(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	अगर (!lowpan_is_iphc(*skb_network_header(skb)))
		वापस RX_CONTINUE;

	/* Setting datagram_offset to zero indicates non frag handling
	 * जबतक करोing lowpan_header_decompress.
	 */
	lowpan_802154_cb(skb)->d_size = 0;

	ret = lowpan_iphc_decompress(skb);
	अगर (ret < 0)
		वापस RX_DROP_UNUSABLE;

	वापस RX_QUEUED;
पूर्ण

lowpan_rx_result lowpan_rx_h_ipv6(काष्ठा sk_buff *skb)
अणु
	अगर (!lowpan_is_ipv6(*skb_network_header(skb)))
		वापस RX_CONTINUE;

	/* Pull off the 1-byte of 6lowpan header. */
	skb_pull(skb, 1);
	वापस RX_QUEUED;
पूर्ण

अटल अंतरभूत bool lowpan_is_esc(u8 dispatch)
अणु
	वापस dispatch == LOWPAN_DISPATCH_ESC;
पूर्ण

अटल lowpan_rx_result lowpan_rx_h_esc(काष्ठा sk_buff *skb)
अणु
	अगर (!lowpan_is_esc(*skb_network_header(skb)))
		वापस RX_CONTINUE;

	net_warn_ratelimited("%s: %s\n", skb->dev->name,
			     "6LoWPAN ESC not supported\n");

	वापस RX_DROP_UNUSABLE;
पूर्ण

अटल अंतरभूत bool lowpan_is_hc1(u8 dispatch)
अणु
	वापस dispatch == LOWPAN_DISPATCH_HC1;
पूर्ण

अटल lowpan_rx_result lowpan_rx_h_hc1(काष्ठा sk_buff *skb)
अणु
	अगर (!lowpan_is_hc1(*skb_network_header(skb)))
		वापस RX_CONTINUE;

	net_warn_ratelimited("%s: %s\n", skb->dev->name,
			     "6LoWPAN HC1 not supported\n");

	वापस RX_DROP_UNUSABLE;
पूर्ण

अटल अंतरभूत bool lowpan_is_dff(u8 dispatch)
अणु
	वापस dispatch == LOWPAN_DISPATCH_DFF;
पूर्ण

अटल lowpan_rx_result lowpan_rx_h_dff(काष्ठा sk_buff *skb)
अणु
	अगर (!lowpan_is_dff(*skb_network_header(skb)))
		वापस RX_CONTINUE;

	net_warn_ratelimited("%s: %s\n", skb->dev->name,
			     "6LoWPAN DFF not supported\n");

	वापस RX_DROP_UNUSABLE;
पूर्ण

अटल अंतरभूत bool lowpan_is_bc0(u8 dispatch)
अणु
	वापस dispatch == LOWPAN_DISPATCH_BC0;
पूर्ण

अटल lowpan_rx_result lowpan_rx_h_bc0(काष्ठा sk_buff *skb)
अणु
	अगर (!lowpan_is_bc0(*skb_network_header(skb)))
		वापस RX_CONTINUE;

	net_warn_ratelimited("%s: %s\n", skb->dev->name,
			     "6LoWPAN BC0 not supported\n");

	वापस RX_DROP_UNUSABLE;
पूर्ण

अटल अंतरभूत bool lowpan_is_mesh(u8 dispatch)
अणु
	वापस (dispatch & LOWPAN_DISPATCH_FIRST) == LOWPAN_DISPATCH_MESH;
पूर्ण

अटल lowpan_rx_result lowpan_rx_h_mesh(काष्ठा sk_buff *skb)
अणु
	अगर (!lowpan_is_mesh(*skb_network_header(skb)))
		वापस RX_CONTINUE;

	net_warn_ratelimited("%s: %s\n", skb->dev->name,
			     "6LoWPAN MESH not supported\n");

	वापस RX_DROP_UNUSABLE;
पूर्ण

अटल पूर्णांक lowpan_invoke_rx_handlers(काष्ठा sk_buff *skb)
अणु
	lowpan_rx_result res;

#घोषणा CALL_RXH(rxh)			\
	करो अणु				\
		res = rxh(skb);	\
		अगर (res != RX_CONTINUE)	\
			जाओ rxh_next;	\
	पूर्ण जबतक (0)

	/* likely at first */
	CALL_RXH(lowpan_rx_h_iphc);
	CALL_RXH(lowpan_rx_h_frag);
	CALL_RXH(lowpan_rx_h_ipv6);
	CALL_RXH(lowpan_rx_h_esc);
	CALL_RXH(lowpan_rx_h_hc1);
	CALL_RXH(lowpan_rx_h_dff);
	CALL_RXH(lowpan_rx_h_bc0);
	CALL_RXH(lowpan_rx_h_mesh);

rxh_next:
	वापस lowpan_rx_handlers_result(skb, res);
#अघोषित CALL_RXH
पूर्ण

अटल अंतरभूत bool lowpan_is_nalp(u8 dispatch)
अणु
	वापस (dispatch & LOWPAN_DISPATCH_FIRST) == LOWPAN_DISPATCH_NALP;
पूर्ण

/* Lookup क्रम reserved dispatch values at:
 * https://www.iana.org/assignments/_6lowpan-parameters/_6lowpan-parameters.xhपंचांगl#_6lowpan-parameters-1
 *
 * Last Updated: 2015-01-22
 */
अटल अंतरभूत bool lowpan_is_reserved(u8 dispatch)
अणु
	वापस ((dispatch >= 0x44 && dispatch <= 0x4F) ||
		(dispatch >= 0x51 && dispatch <= 0x5F) ||
		(dispatch >= 0xc8 && dispatch <= 0xdf) ||
		dispatch >= 0xe8);
पूर्ण

/* lowpan_rx_h_check checks on generic 6LoWPAN requirements
 * in MAC and 6LoWPAN header.
 *
 * Don't manipulate the skb here, it could be shared buffer.
 */
अटल अंतरभूत bool lowpan_rx_h_check(काष्ठा sk_buff *skb)
अणु
	__le16 fc = ieee802154_get_fc_from_skb(skb);

	/* check on ieee802154 conक्रमm 6LoWPAN header */
	अगर (!ieee802154_is_data(fc) ||
	    !ieee802154_skb_is_पूर्णांकra_pan_addressing(fc, skb))
		वापस false;

	/* check अगर we can dereference the dispatch */
	अगर (unlikely(!skb->len))
		वापस false;

	अगर (lowpan_is_nalp(*skb_network_header(skb)) ||
	    lowpan_is_reserved(*skb_network_header(skb)))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक lowpan_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *wdev,
		      काष्ठा packet_type *pt, काष्ठा net_device *orig_wdev)
अणु
	काष्ठा net_device *ldev;

	अगर (wdev->type != ARPHRD_IEEE802154 ||
	    skb->pkt_type == PACKET_OTHERHOST ||
	    !lowpan_rx_h_check(skb))
		जाओ drop;

	ldev = wdev->ieee802154_ptr->lowpan_dev;
	अगर (!ldev || !netअगर_running(ldev))
		जाओ drop;

	/* Replacing skb->dev and followed rx handlers will manipulate skb. */
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;
	skb->dev = ldev;

	/* When receive frag1 it's likely that we manipulate the buffer.
	 * When recevie iphc we manipulate the data buffer. So we need
	 * to unshare the buffer.
	 */
	अगर (lowpan_is_frag1(*skb_network_header(skb)) ||
	    lowpan_is_iphc(*skb_network_header(skb))) अणु
		skb = skb_unshare(skb, GFP_ATOMIC);
		अगर (!skb)
			जाओ out;
	पूर्ण

	वापस lowpan_invoke_rx_handlers(skb);

drop:
	kमुक्त_skb(skb);
out:
	वापस NET_RX_DROP;
पूर्ण

अटल काष्ठा packet_type lowpan_packet_type = अणु
	.type = htons(ETH_P_IEEE802154),
	.func = lowpan_rcv,
पूर्ण;

व्योम lowpan_rx_init(व्योम)
अणु
	dev_add_pack(&lowpan_packet_type);
पूर्ण

व्योम lowpan_rx_निकास(व्योम)
अणु
	dev_हटाओ_pack(&lowpan_packet_type);
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <net/6lowpan.h>
#समावेश <net/ndisc.h>
#समावेश <net/ieee802154_netdev.h>
#समावेश <net/mac802154.h>

#समावेश "6lowpan_i.h"

#घोषणा LOWPAN_FRAG1_HEAD_SIZE	0x4
#घोषणा LOWPAN_FRAGN_HEAD_SIZE	0x5

काष्ठा lowpan_addr_info अणु
	काष्ठा ieee802154_addr daddr;
	काष्ठा ieee802154_addr saddr;
पूर्ण;

अटल अंतरभूत काष्ठा
lowpan_addr_info *lowpan_skb_priv(स्थिर काष्ठा sk_buff *skb)
अणु
	WARN_ON_ONCE(skb_headroom(skb) < माप(काष्ठा lowpan_addr_info));
	वापस (काष्ठा lowpan_addr_info *)(skb->data -
			माप(काष्ठा lowpan_addr_info));
पूर्ण

/* This callback will be called from AF_PACKET and IPv6 stack, the AF_PACKET
 * sockets gives an 8 byte array क्रम addresses only!
 *
 * TODO I think AF_PACKET DGRAM (sending/receiving) RAW (sending) makes no
 * sense here. We should disable it, the right use-हाल would be AF_INET6
 * RAW/DGRAM sockets.
 */
पूर्णांक lowpan_header_create(काष्ठा sk_buff *skb, काष्ठा net_device *ldev,
			 अचिन्हित लघु type, स्थिर व्योम *daddr,
			 स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा wpan_dev *wpan_dev = lowpan_802154_dev(ldev)->wdev->ieee802154_ptr;
	काष्ठा lowpan_addr_info *info = lowpan_skb_priv(skb);
	काष्ठा lowpan_802154_neigh *llneigh = शून्य;
	स्थिर काष्ठा ipv6hdr *hdr = ipv6_hdr(skb);
	काष्ठा neighbour *n;

	अगर (!daddr)
		वापस -EINVAL;

	/* TODO:
	 * अगर this package isn't ipv6 one, where should it be routed?
	 */
	अगर (type != ETH_P_IPV6)
		वापस 0;

	/* पूर्णांकra-pan communication */
	info->saddr.pan_id = wpan_dev->pan_id;
	info->daddr.pan_id = info->saddr.pan_id;

	अगर (!स_भेद(daddr, ldev->broadcast, EUI64_ADDR_LEN)) अणु
		info->daddr.लघु_addr = cpu_to_le16(IEEE802154_ADDR_BROADCAST);
		info->daddr.mode = IEEE802154_ADDR_SHORT;
	पूर्ण अन्यथा अणु
		__le16 लघु_addr = cpu_to_le16(IEEE802154_ADDR_SHORT_UNSPEC);

		n = neigh_lookup(&nd_tbl, &hdr->daddr, ldev);
		अगर (n) अणु
			llneigh = lowpan_802154_neigh(neighbour_priv(n));
			पढ़ो_lock_bh(&n->lock);
			लघु_addr = llneigh->लघु_addr;
			पढ़ो_unlock_bh(&n->lock);
		पूर्ण

		अगर (llneigh &&
		    lowpan_802154_is_valid_src_लघु_addr(लघु_addr)) अणु
			info->daddr.लघु_addr = लघु_addr;
			info->daddr.mode = IEEE802154_ADDR_SHORT;
		पूर्ण अन्यथा अणु
			info->daddr.mode = IEEE802154_ADDR_LONG;
			ieee802154_be64_to_le64(&info->daddr.extended_addr,
						daddr);
		पूर्ण

		अगर (n)
			neigh_release(n);
	पूर्ण

	अगर (!saddr) अणु
		अगर (lowpan_802154_is_valid_src_लघु_addr(wpan_dev->लघु_addr)) अणु
			info->saddr.mode = IEEE802154_ADDR_SHORT;
			info->saddr.लघु_addr = wpan_dev->लघु_addr;
		पूर्ण अन्यथा अणु
			info->saddr.mode = IEEE802154_ADDR_LONG;
			info->saddr.extended_addr = wpan_dev->extended_addr;
		पूर्ण
	पूर्ण अन्यथा अणु
		info->saddr.mode = IEEE802154_ADDR_LONG;
		ieee802154_be64_to_le64(&info->saddr.extended_addr, saddr);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff*
lowpan_alloc_frag(काष्ठा sk_buff *skb, पूर्णांक size,
		  स्थिर काष्ठा ieee802154_hdr *master_hdr, bool frag1)
अणु
	काष्ठा net_device *wdev = lowpan_802154_dev(skb->dev)->wdev;
	काष्ठा sk_buff *frag;
	पूर्णांक rc;

	frag = alloc_skb(wdev->needed_headroom + wdev->needed_tailroom + size,
			 GFP_ATOMIC);

	अगर (likely(frag)) अणु
		frag->dev = wdev;
		frag->priority = skb->priority;
		skb_reserve(frag, wdev->needed_headroom);
		skb_reset_network_header(frag);
		*mac_cb(frag) = *mac_cb(skb);

		अगर (frag1) अणु
			skb_put_data(frag, skb_mac_header(skb), skb->mac_len);
		पूर्ण अन्यथा अणु
			rc = wpan_dev_hard_header(frag, wdev,
						  &master_hdr->dest,
						  &master_hdr->source, size);
			अगर (rc < 0) अणु
				kमुक्त_skb(frag);
				वापस ERR_PTR(rc);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		frag = ERR_PTR(-ENOMEM);
	पूर्ण

	वापस frag;
पूर्ण

अटल पूर्णांक
lowpan_xmit_fragment(काष्ठा sk_buff *skb, स्थिर काष्ठा ieee802154_hdr *wpan_hdr,
		     u8 *frag_hdr, पूर्णांक frag_hdrlen,
		     पूर्णांक offset, पूर्णांक len, bool frag1)
अणु
	काष्ठा sk_buff *frag;

	raw_dump_अंतरभूत(__func__, " fragment header", frag_hdr, frag_hdrlen);

	frag = lowpan_alloc_frag(skb, frag_hdrlen + len, wpan_hdr, frag1);
	अगर (IS_ERR(frag))
		वापस PTR_ERR(frag);

	skb_put_data(frag, frag_hdr, frag_hdrlen);
	skb_put_data(frag, skb_network_header(skb) + offset, len);

	raw_dump_table(__func__, " fragment dump", frag->data, frag->len);

	वापस dev_queue_xmit(frag);
पूर्ण

अटल पूर्णांक
lowpan_xmit_fragmented(काष्ठा sk_buff *skb, काष्ठा net_device *ldev,
		       स्थिर काष्ठा ieee802154_hdr *wpan_hdr, u16 dgram_size,
		       u16 dgram_offset)
अणु
	__be16 frag_tag;
	u8 frag_hdr[5];
	पूर्णांक frag_cap, frag_len, payload_cap, rc;
	पूर्णांक skb_unprocessed, skb_offset;

	frag_tag = htons(lowpan_802154_dev(ldev)->fragment_tag);
	lowpan_802154_dev(ldev)->fragment_tag++;

	frag_hdr[0] = LOWPAN_DISPATCH_FRAG1 | ((dgram_size >> 8) & 0x07);
	frag_hdr[1] = dgram_size & 0xff;
	स_नकल(frag_hdr + 2, &frag_tag, माप(frag_tag));

	payload_cap = ieee802154_max_payload(wpan_hdr);

	frag_len = round_करोwn(payload_cap - LOWPAN_FRAG1_HEAD_SIZE -
			      skb_network_header_len(skb), 8);

	skb_offset = skb_network_header_len(skb);
	skb_unprocessed = skb->len - skb->mac_len - skb_offset;

	rc = lowpan_xmit_fragment(skb, wpan_hdr, frag_hdr,
				  LOWPAN_FRAG1_HEAD_SIZE, 0,
				  frag_len + skb_network_header_len(skb),
				  true);
	अगर (rc) अणु
		pr_debug("%s unable to send FRAG1 packet (tag: %d)",
			 __func__, ntohs(frag_tag));
		जाओ err;
	पूर्ण

	frag_hdr[0] &= ~LOWPAN_DISPATCH_FRAG1;
	frag_hdr[0] |= LOWPAN_DISPATCH_FRAGN;
	frag_cap = round_करोwn(payload_cap - LOWPAN_FRAGN_HEAD_SIZE, 8);

	करो अणु
		dgram_offset += frag_len;
		skb_offset += frag_len;
		skb_unprocessed -= frag_len;
		frag_len = min(frag_cap, skb_unprocessed);

		frag_hdr[4] = dgram_offset >> 3;

		rc = lowpan_xmit_fragment(skb, wpan_hdr, frag_hdr,
					  LOWPAN_FRAGN_HEAD_SIZE, skb_offset,
					  frag_len, false);
		अगर (rc) अणु
			pr_debug("%s unable to send a FRAGN packet. (tag: %d, offset: %d)\n",
				 __func__, ntohs(frag_tag), skb_offset);
			जाओ err;
		पूर्ण
	पूर्ण जबतक (skb_unprocessed > frag_cap);

	ldev->stats.tx_packets++;
	ldev->stats.tx_bytes += dgram_size;
	consume_skb(skb);
	वापस NET_XMIT_SUCCESS;

err:
	kमुक्त_skb(skb);
	वापस rc;
पूर्ण

अटल पूर्णांक lowpan_header(काष्ठा sk_buff *skb, काष्ठा net_device *ldev,
			 u16 *dgram_size, u16 *dgram_offset)
अणु
	काष्ठा wpan_dev *wpan_dev = lowpan_802154_dev(ldev)->wdev->ieee802154_ptr;
	काष्ठा ieee802154_mac_cb *cb = mac_cb_init(skb);
	काष्ठा lowpan_addr_info info;

	स_नकल(&info, lowpan_skb_priv(skb), माप(info));

	*dgram_size = skb->len;
	lowpan_header_compress(skb, ldev, &info.daddr, &info.saddr);
	/* dgram_offset = (saved bytes after compression) + lowpan header len */
	*dgram_offset = (*dgram_size - skb->len) + skb_network_header_len(skb);

	cb->type = IEEE802154_FC_TYPE_DATA;

	अगर (info.daddr.mode == IEEE802154_ADDR_SHORT &&
	    ieee802154_is_broadcast_लघु_addr(info.daddr.लघु_addr))
		cb->ackreq = false;
	अन्यथा
		cb->ackreq = wpan_dev->ackreq;

	वापस wpan_dev_hard_header(skb, lowpan_802154_dev(ldev)->wdev,
				    &info.daddr, &info.saddr, 0);
पूर्ण

netdev_tx_t lowpan_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ldev)
अणु
	काष्ठा ieee802154_hdr wpan_hdr;
	पूर्णांक max_single, ret;
	u16 dgram_size, dgram_offset;

	pr_debug("package xmit\n");

	WARN_ON_ONCE(skb->len > IPV6_MIN_MTU);

	/* We must take a copy of the skb beक्रमe we modअगरy/replace the ipv6
	 * header as the header could be used अन्यथाwhere
	 */
	अगर (unlikely(skb_headroom(skb) < ldev->needed_headroom ||
		     skb_tailroom(skb) < ldev->needed_tailroom)) अणु
		काष्ठा sk_buff *nskb;

		nskb = skb_copy_expand(skb, ldev->needed_headroom,
				       ldev->needed_tailroom, GFP_ATOMIC);
		अगर (likely(nskb)) अणु
			consume_skb(skb);
			skb = nskb;
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
			वापस NET_XMIT_DROP;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb = skb_unshare(skb, GFP_ATOMIC);
		अगर (!skb)
			वापस NET_XMIT_DROP;
	पूर्ण

	ret = lowpan_header(skb, ldev, &dgram_size, &dgram_offset);
	अगर (ret < 0) अणु
		kमुक्त_skb(skb);
		वापस NET_XMIT_DROP;
	पूर्ण

	अगर (ieee802154_hdr_peek(skb, &wpan_hdr) < 0) अणु
		kमुक्त_skb(skb);
		वापस NET_XMIT_DROP;
	पूर्ण

	max_single = ieee802154_max_payload(&wpan_hdr);

	अगर (skb_tail_poपूर्णांकer(skb) - skb_network_header(skb) <= max_single) अणु
		skb->dev = lowpan_802154_dev(ldev)->wdev;
		ldev->stats.tx_packets++;
		ldev->stats.tx_bytes += dgram_size;
		वापस dev_queue_xmit(skb);
	पूर्ण अन्यथा अणु
		netdev_tx_t rc;

		pr_debug("frame is too big, fragmentation is needed\n");
		rc = lowpan_xmit_fragmented(skb, ldev, &wpan_hdr, dgram_size,
					    dgram_offset);

		वापस rc < 0 ? NET_XMIT_DROP : rc;
	पूर्ण
पूर्ण

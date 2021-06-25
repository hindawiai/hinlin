<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IPv4 over IEEE 1394, per RFC 2734
 * IPv6 over IEEE 1394, per RFC 3146
 *
 * Copyright (C) 2009 Jay Fenlason <fenlason@redhat.com>
 *
 * based on eth1394 by Ben Collins et al
 */

#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/unaligned.h>
#समावेश <net/arp.h>
#समावेश <net/firewire.h>

/* rx limits */
#घोषणा FWNET_MAX_FRAGMENTS		30 /* arbitrary, > TX queue depth */
#घोषणा FWNET_ISO_PAGE_COUNT		(PAGE_SIZE < 16*1024 ? 4 : 2)

/* tx limits */
#घोषणा FWNET_MAX_QUEUED_DATAGRAMS	20 /* < 64 = number of tlabels */
#घोषणा FWNET_MIN_QUEUED_DATAGRAMS	10 /* should keep AT DMA busy enough */
#घोषणा FWNET_TX_QUEUE_LEN		FWNET_MAX_QUEUED_DATAGRAMS /* ? */

#घोषणा IEEE1394_BROADCAST_CHANNEL	31
#घोषणा IEEE1394_ALL_NODES		(0xffc0 | 0x003f)
#घोषणा IEEE1394_MAX_PAYLOAD_S100	512
#घोषणा FWNET_NO_FIFO_ADDR		(~0ULL)

#घोषणा IANA_SPECIFIER_ID		0x00005eU
#घोषणा RFC2734_SW_VERSION		0x000001U
#घोषणा RFC3146_SW_VERSION		0x000002U

#घोषणा IEEE1394_GASP_HDR_SIZE	8

#घोषणा RFC2374_UNFRAG_HDR_SIZE	4
#घोषणा RFC2374_FRAG_HDR_SIZE	8
#घोषणा RFC2374_FRAG_OVERHEAD	4

#घोषणा RFC2374_HDR_UNFRAG	0	/* unfragmented		*/
#घोषणा RFC2374_HDR_FIRSTFRAG	1	/* first fragment	*/
#घोषणा RFC2374_HDR_LASTFRAG	2	/* last fragment	*/
#घोषणा RFC2374_HDR_INTFRAG	3	/* पूर्णांकerior fragment	*/

अटल bool fwnet_hwaddr_is_multicast(u8 *ha)
अणु
	वापस !!(*ha & 1);
पूर्ण

/* IPv4 and IPv6 encapsulation header */
काष्ठा rfc2734_header अणु
	u32 w0;
	u32 w1;
पूर्ण;

#घोषणा fwnet_get_hdr_lf(h)		(((h)->w0 & 0xc0000000) >> 30)
#घोषणा fwnet_get_hdr_ether_type(h)	(((h)->w0 & 0x0000ffff))
#घोषणा fwnet_get_hdr_dg_size(h)	((((h)->w0 & 0x0fff0000) >> 16) + 1)
#घोषणा fwnet_get_hdr_fg_off(h)		(((h)->w0 & 0x00000fff))
#घोषणा fwnet_get_hdr_dgl(h)		(((h)->w1 & 0xffff0000) >> 16)

#घोषणा fwnet_set_hdr_lf(lf)		((lf) << 30)
#घोषणा fwnet_set_hdr_ether_type(et)	(et)
#घोषणा fwnet_set_hdr_dg_size(dgs)	(((dgs) - 1) << 16)
#घोषणा fwnet_set_hdr_fg_off(fgo)	(fgo)

#घोषणा fwnet_set_hdr_dgl(dgl)		((dgl) << 16)

अटल अंतरभूत व्योम fwnet_make_uf_hdr(काष्ठा rfc2734_header *hdr,
		अचिन्हित ether_type)
अणु
	hdr->w0 = fwnet_set_hdr_lf(RFC2374_HDR_UNFRAG)
		  | fwnet_set_hdr_ether_type(ether_type);
पूर्ण

अटल अंतरभूत व्योम fwnet_make_ff_hdr(काष्ठा rfc2734_header *hdr,
		अचिन्हित ether_type, अचिन्हित dg_size, अचिन्हित dgl)
अणु
	hdr->w0 = fwnet_set_hdr_lf(RFC2374_HDR_FIRSTFRAG)
		  | fwnet_set_hdr_dg_size(dg_size)
		  | fwnet_set_hdr_ether_type(ether_type);
	hdr->w1 = fwnet_set_hdr_dgl(dgl);
पूर्ण

अटल अंतरभूत व्योम fwnet_make_sf_hdr(काष्ठा rfc2734_header *hdr,
		अचिन्हित lf, अचिन्हित dg_size, अचिन्हित fg_off, अचिन्हित dgl)
अणु
	hdr->w0 = fwnet_set_hdr_lf(lf)
		  | fwnet_set_hdr_dg_size(dg_size)
		  | fwnet_set_hdr_fg_off(fg_off);
	hdr->w1 = fwnet_set_hdr_dgl(dgl);
पूर्ण

/* This list keeps track of what parts of the datagram have been filled in */
काष्ठा fwnet_fragment_info अणु
	काष्ठा list_head fi_link;
	u16 offset;
	u16 len;
पूर्ण;

काष्ठा fwnet_partial_datagram अणु
	काष्ठा list_head pd_link;
	काष्ठा list_head fi_list;
	काष्ठा sk_buff *skb;
	/* FIXME Why not use skb->data? */
	अक्षर *pbuf;
	u16 datagram_label;
	u16 ether_type;
	u16 datagram_size;
पूर्ण;

अटल DEFINE_MUTEX(fwnet_device_mutex);
अटल LIST_HEAD(fwnet_device_list);

काष्ठा fwnet_device अणु
	काष्ठा list_head dev_link;
	spinlock_t lock;
	क्रमागत अणु
		FWNET_BROADCAST_ERROR,
		FWNET_BROADCAST_RUNNING,
		FWNET_BROADCAST_STOPPED,
	पूर्ण broadcast_state;
	काष्ठा fw_iso_context *broadcast_rcv_context;
	काष्ठा fw_iso_buffer broadcast_rcv_buffer;
	व्योम **broadcast_rcv_buffer_ptrs;
	अचिन्हित broadcast_rcv_next_ptr;
	अचिन्हित num_broadcast_rcv_ptrs;
	अचिन्हित rcv_buffer_size;
	/*
	 * This value is the maximum unfragmented datagram size that can be
	 * sent by the hardware.  It alपढ़ोy has the GASP overhead and the
	 * unfragmented datagram header overhead calculated पूर्णांकo it.
	 */
	अचिन्हित broadcast_xmt_max_payload;
	u16 broadcast_xmt_datagramlabel;

	/*
	 * The CSR address that remote nodes must send datagrams to क्रम us to
	 * receive them.
	 */
	काष्ठा fw_address_handler handler;
	u64 local_fअगरo;

	/* Number of tx datagrams that have been queued but not yet acked */
	पूर्णांक queued_datagrams;

	पूर्णांक peer_count;
	काष्ठा list_head peer_list;
	काष्ठा fw_card *card;
	काष्ठा net_device *netdev;
पूर्ण;

काष्ठा fwnet_peer अणु
	काष्ठा list_head peer_link;
	काष्ठा fwnet_device *dev;
	u64 guid;

	/* guarded by dev->lock */
	काष्ठा list_head pd_list; /* received partial datagrams */
	अचिन्हित pdg_size;        /* pd_list size */

	u16 datagram_label;       /* outgoing datagram label */
	u16 max_payload;          /* includes RFC2374_FRAG_HDR_SIZE overhead */
	पूर्णांक node_id;
	पूर्णांक generation;
	अचिन्हित speed;
पूर्ण;

/* This is our task काष्ठा. It's used क्रम the packet complete callback.  */
काष्ठा fwnet_packet_task अणु
	काष्ठा fw_transaction transaction;
	काष्ठा rfc2734_header hdr;
	काष्ठा sk_buff *skb;
	काष्ठा fwnet_device *dev;

	पूर्णांक outstanding_pkts;
	u64 fअगरo_addr;
	u16 dest_node;
	u16 max_payload;
	u8 generation;
	u8 speed;
	u8 enqueued;
पूर्ण;

/*
 * Get fअगरo address embedded in hwaddr
 */
अटल __u64 fwnet_hwaddr_fअगरo(जोड़ fwnet_hwaddr *ha)
अणु
	वापस (u64)get_unaligned_be16(&ha->uc.fअगरo_hi) << 32
	       | get_unaligned_be32(&ha->uc.fअगरo_lo);
पूर्ण

/*
 * saddr == शून्य means use device source address.
 * daddr == शून्य means leave destination address (eg unresolved arp).
 */
अटल पूर्णांक fwnet_header_create(काष्ठा sk_buff *skb, काष्ठा net_device *net,
			अचिन्हित लघु type, स्थिर व्योम *daddr,
			स्थिर व्योम *saddr, अचिन्हित len)
अणु
	काष्ठा fwnet_header *h;

	h = skb_push(skb, माप(*h));
	put_unaligned_be16(type, &h->h_proto);

	अगर (net->flags & (IFF_LOOPBACK | IFF_NOARP)) अणु
		स_रखो(h->h_dest, 0, net->addr_len);

		वापस net->hard_header_len;
	पूर्ण

	अगर (daddr) अणु
		स_नकल(h->h_dest, daddr, net->addr_len);

		वापस net->hard_header_len;
	पूर्ण

	वापस -net->hard_header_len;
पूर्ण

अटल पूर्णांक fwnet_header_cache(स्थिर काष्ठा neighbour *neigh,
			      काष्ठा hh_cache *hh, __be16 type)
अणु
	काष्ठा net_device *net;
	काष्ठा fwnet_header *h;

	अगर (type == cpu_to_be16(ETH_P_802_3))
		वापस -1;
	net = neigh->dev;
	h = (काष्ठा fwnet_header *)((u8 *)hh->hh_data + HH_DATA_OFF(माप(*h)));
	h->h_proto = type;
	स_नकल(h->h_dest, neigh->ha, net->addr_len);

	/* Pairs with the READ_ONCE() in neigh_resolve_output(),
	 * neigh_hh_output() and neigh_update_hhs().
	 */
	smp_store_release(&hh->hh_len, FWNET_HLEN);

	वापस 0;
पूर्ण

/* Called by Address Resolution module to notअगरy changes in address. */
अटल व्योम fwnet_header_cache_update(काष्ठा hh_cache *hh,
		स्थिर काष्ठा net_device *net, स्थिर अचिन्हित अक्षर *haddr)
अणु
	स_नकल((u8 *)hh->hh_data + HH_DATA_OFF(FWNET_HLEN), haddr, net->addr_len);
पूर्ण

अटल पूर्णांक fwnet_header_parse(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr)
अणु
	स_नकल(haddr, skb->dev->dev_addr, FWNET_ALEN);

	वापस FWNET_ALEN;
पूर्ण

अटल स्थिर काष्ठा header_ops fwnet_header_ops = अणु
	.create         = fwnet_header_create,
	.cache		= fwnet_header_cache,
	.cache_update	= fwnet_header_cache_update,
	.parse          = fwnet_header_parse,
पूर्ण;

/* FIXME: is this correct क्रम all हालs? */
अटल bool fwnet_frag_overlap(काष्ठा fwnet_partial_datagram *pd,
			       अचिन्हित offset, अचिन्हित len)
अणु
	काष्ठा fwnet_fragment_info *fi;
	अचिन्हित end = offset + len;

	list_क्रम_each_entry(fi, &pd->fi_list, fi_link)
		अगर (offset < fi->offset + fi->len && end > fi->offset)
			वापस true;

	वापस false;
पूर्ण

/* Assumes that new fragment करोes not overlap any existing fragments */
अटल काष्ठा fwnet_fragment_info *fwnet_frag_new(
	काष्ठा fwnet_partial_datagram *pd, अचिन्हित offset, अचिन्हित len)
अणु
	काष्ठा fwnet_fragment_info *fi, *fi2, *new;
	काष्ठा list_head *list;

	list = &pd->fi_list;
	list_क्रम_each_entry(fi, &pd->fi_list, fi_link) अणु
		अगर (fi->offset + fi->len == offset) अणु
			/* The new fragment can be tacked on to the end */
			/* Did the new fragment plug a hole? */
			fi2 = list_entry(fi->fi_link.next,
					 काष्ठा fwnet_fragment_info, fi_link);
			अगर (fi->offset + fi->len == fi2->offset) अणु
				/* glue fragments together */
				fi->len += len + fi2->len;
				list_del(&fi2->fi_link);
				kमुक्त(fi2);
			पूर्ण अन्यथा अणु
				fi->len += len;
			पूर्ण

			वापस fi;
		पूर्ण
		अगर (offset + len == fi->offset) अणु
			/* The new fragment can be tacked on to the beginning */
			/* Did the new fragment plug a hole? */
			fi2 = list_entry(fi->fi_link.prev,
					 काष्ठा fwnet_fragment_info, fi_link);
			अगर (fi2->offset + fi2->len == fi->offset) अणु
				/* glue fragments together */
				fi2->len += fi->len + len;
				list_del(&fi->fi_link);
				kमुक्त(fi);

				वापस fi2;
			पूर्ण
			fi->offset = offset;
			fi->len += len;

			वापस fi;
		पूर्ण
		अगर (offset > fi->offset + fi->len) अणु
			list = &fi->fi_link;
			अवरोध;
		पूर्ण
		अगर (offset + len < fi->offset) अणु
			list = fi->fi_link.prev;
			अवरोध;
		पूर्ण
	पूर्ण

	new = kदो_स्मृति(माप(*new), GFP_ATOMIC);
	अगर (!new)
		वापस शून्य;

	new->offset = offset;
	new->len = len;
	list_add(&new->fi_link, list);

	वापस new;
पूर्ण

अटल काष्ठा fwnet_partial_datagram *fwnet_pd_new(काष्ठा net_device *net,
		काष्ठा fwnet_peer *peer, u16 datagram_label, अचिन्हित dg_size,
		व्योम *frag_buf, अचिन्हित frag_off, अचिन्हित frag_len)
अणु
	काष्ठा fwnet_partial_datagram *new;
	काष्ठा fwnet_fragment_info *fi;

	new = kदो_स्मृति(माप(*new), GFP_ATOMIC);
	अगर (!new)
		जाओ fail;

	INIT_LIST_HEAD(&new->fi_list);
	fi = fwnet_frag_new(new, frag_off, frag_len);
	अगर (fi == शून्य)
		जाओ fail_w_new;

	new->datagram_label = datagram_label;
	new->datagram_size = dg_size;
	new->skb = dev_alloc_skb(dg_size + LL_RESERVED_SPACE(net));
	अगर (new->skb == शून्य)
		जाओ fail_w_fi;

	skb_reserve(new->skb, LL_RESERVED_SPACE(net));
	new->pbuf = skb_put(new->skb, dg_size);
	स_नकल(new->pbuf + frag_off, frag_buf, frag_len);
	list_add_tail(&new->pd_link, &peer->pd_list);

	वापस new;

fail_w_fi:
	kमुक्त(fi);
fail_w_new:
	kमुक्त(new);
fail:
	वापस शून्य;
पूर्ण

अटल काष्ठा fwnet_partial_datagram *fwnet_pd_find(काष्ठा fwnet_peer *peer,
						    u16 datagram_label)
अणु
	काष्ठा fwnet_partial_datagram *pd;

	list_क्रम_each_entry(pd, &peer->pd_list, pd_link)
		अगर (pd->datagram_label == datagram_label)
			वापस pd;

	वापस शून्य;
पूर्ण


अटल व्योम fwnet_pd_delete(काष्ठा fwnet_partial_datagram *old)
अणु
	काष्ठा fwnet_fragment_info *fi, *n;

	list_क्रम_each_entry_safe(fi, n, &old->fi_list, fi_link)
		kमुक्त(fi);

	list_del(&old->pd_link);
	dev_kमुक्त_skb_any(old->skb);
	kमुक्त(old);
पूर्ण

अटल bool fwnet_pd_update(काष्ठा fwnet_peer *peer,
		काष्ठा fwnet_partial_datagram *pd, व्योम *frag_buf,
		अचिन्हित frag_off, अचिन्हित frag_len)
अणु
	अगर (fwnet_frag_new(pd, frag_off, frag_len) == शून्य)
		वापस false;

	स_नकल(pd->pbuf + frag_off, frag_buf, frag_len);

	/*
	 * Move list entry to beginning of list so that oldest partial
	 * datagrams percolate to the end of the list
	 */
	list_move_tail(&pd->pd_link, &peer->pd_list);

	वापस true;
पूर्ण

अटल bool fwnet_pd_is_complete(काष्ठा fwnet_partial_datagram *pd)
अणु
	काष्ठा fwnet_fragment_info *fi;

	fi = list_entry(pd->fi_list.next, काष्ठा fwnet_fragment_info, fi_link);

	वापस fi->len == pd->datagram_size;
पूर्ण

/* caller must hold dev->lock */
अटल काष्ठा fwnet_peer *fwnet_peer_find_by_guid(काष्ठा fwnet_device *dev,
						  u64 guid)
अणु
	काष्ठा fwnet_peer *peer;

	list_क्रम_each_entry(peer, &dev->peer_list, peer_link)
		अगर (peer->guid == guid)
			वापस peer;

	वापस शून्य;
पूर्ण

/* caller must hold dev->lock */
अटल काष्ठा fwnet_peer *fwnet_peer_find_by_node_id(काष्ठा fwnet_device *dev,
						पूर्णांक node_id, पूर्णांक generation)
अणु
	काष्ठा fwnet_peer *peer;

	list_क्रम_each_entry(peer, &dev->peer_list, peer_link)
		अगर (peer->node_id    == node_id &&
		    peer->generation == generation)
			वापस peer;

	वापस शून्य;
पूर्ण

/* See IEEE 1394-2008 table 6-4, table 8-8, table 16-18. */
अटल अचिन्हित fwnet_max_payload(अचिन्हित max_rec, अचिन्हित speed)
अणु
	max_rec = min(max_rec, speed + 8);
	max_rec = clamp(max_rec, 8U, 11U); /* 512...4096 */

	वापस (1 << (max_rec + 1)) - RFC2374_FRAG_HDR_SIZE;
पूर्ण


अटल पूर्णांक fwnet_finish_incoming_packet(काष्ठा net_device *net,
					काष्ठा sk_buff *skb, u16 source_node_id,
					bool is_broadcast, u16 ether_type)
अणु
	काष्ठा fwnet_device *dev;
	पूर्णांक status;
	__be64 guid;

	चयन (ether_type) अणु
	हाल ETH_P_ARP:
	हाल ETH_P_IP:
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल ETH_P_IPV6:
#पूर्ण_अगर
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	dev = netdev_priv(net);
	/* Write metadata, and then pass to the receive level */
	skb->dev = net;
	skb->ip_summed = CHECKSUM_NONE;

	/*
	 * Parse the encapsulation header. This actually करोes the job of
	 * converting to an ethernet-like pseuकरो frame header.
	 */
	guid = cpu_to_be64(dev->card->guid);
	अगर (dev_hard_header(skb, net, ether_type,
			   is_broadcast ? net->broadcast : net->dev_addr,
			   शून्य, skb->len) >= 0) अणु
		काष्ठा fwnet_header *eth;
		u16 *rawp;
		__be16 protocol;

		skb_reset_mac_header(skb);
		skb_pull(skb, माप(*eth));
		eth = (काष्ठा fwnet_header *)skb_mac_header(skb);
		अगर (fwnet_hwaddr_is_multicast(eth->h_dest)) अणु
			अगर (स_भेद(eth->h_dest, net->broadcast,
				   net->addr_len) == 0)
				skb->pkt_type = PACKET_BROADCAST;
#अगर 0
			अन्यथा
				skb->pkt_type = PACKET_MULTICAST;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			अगर (स_भेद(eth->h_dest, net->dev_addr, net->addr_len))
				skb->pkt_type = PACKET_OTHERHOST;
		पूर्ण
		अगर (ntohs(eth->h_proto) >= ETH_P_802_3_MIN) अणु
			protocol = eth->h_proto;
		पूर्ण अन्यथा अणु
			rawp = (u16 *)skb->data;
			अगर (*rawp == 0xffff)
				protocol = htons(ETH_P_802_3);
			अन्यथा
				protocol = htons(ETH_P_802_2);
		पूर्ण
		skb->protocol = protocol;
	पूर्ण
	status = netअगर_rx(skb);
	अगर (status == NET_RX_DROP) अणु
		net->stats.rx_errors++;
		net->stats.rx_dropped++;
	पूर्ण अन्यथा अणु
		net->stats.rx_packets++;
		net->stats.rx_bytes += skb->len;
	पूर्ण

	वापस 0;

 err:
	net->stats.rx_errors++;
	net->stats.rx_dropped++;

	dev_kमुक्त_skb_any(skb);

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक fwnet_incoming_packet(काष्ठा fwnet_device *dev, __be32 *buf, पूर्णांक len,
				 पूर्णांक source_node_id, पूर्णांक generation,
				 bool is_broadcast)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net_device *net = dev->netdev;
	काष्ठा rfc2734_header hdr;
	अचिन्हित lf;
	अचिन्हित दीर्घ flags;
	काष्ठा fwnet_peer *peer;
	काष्ठा fwnet_partial_datagram *pd;
	पूर्णांक fg_off;
	पूर्णांक dg_size;
	u16 datagram_label;
	पूर्णांक retval;
	u16 ether_type;

	अगर (len <= RFC2374_UNFRAG_HDR_SIZE)
		वापस 0;

	hdr.w0 = be32_to_cpu(buf[0]);
	lf = fwnet_get_hdr_lf(&hdr);
	अगर (lf == RFC2374_HDR_UNFRAG) अणु
		/*
		 * An unfragmented datagram has been received by the ieee1394
		 * bus. Build an skbuff around it so we can pass it to the
		 * high level network layer.
		 */
		ether_type = fwnet_get_hdr_ether_type(&hdr);
		buf++;
		len -= RFC2374_UNFRAG_HDR_SIZE;

		skb = dev_alloc_skb(len + LL_RESERVED_SPACE(net));
		अगर (unlikely(!skb)) अणु
			net->stats.rx_dropped++;

			वापस -ENOMEM;
		पूर्ण
		skb_reserve(skb, LL_RESERVED_SPACE(net));
		skb_put_data(skb, buf, len);

		वापस fwnet_finish_incoming_packet(net, skb, source_node_id,
						    is_broadcast, ether_type);
	पूर्ण

	/* A datagram fragment has been received, now the fun begins. */

	अगर (len <= RFC2374_FRAG_HDR_SIZE)
		वापस 0;

	hdr.w1 = ntohl(buf[1]);
	buf += 2;
	len -= RFC2374_FRAG_HDR_SIZE;
	अगर (lf == RFC2374_HDR_FIRSTFRAG) अणु
		ether_type = fwnet_get_hdr_ether_type(&hdr);
		fg_off = 0;
	पूर्ण अन्यथा अणु
		ether_type = 0;
		fg_off = fwnet_get_hdr_fg_off(&hdr);
	पूर्ण
	datagram_label = fwnet_get_hdr_dgl(&hdr);
	dg_size = fwnet_get_hdr_dg_size(&hdr);

	अगर (fg_off + len > dg_size)
		वापस 0;

	spin_lock_irqsave(&dev->lock, flags);

	peer = fwnet_peer_find_by_node_id(dev, source_node_id, generation);
	अगर (!peer) अणु
		retval = -ENOENT;
		जाओ fail;
	पूर्ण

	pd = fwnet_pd_find(peer, datagram_label);
	अगर (pd == शून्य) अणु
		जबतक (peer->pdg_size >= FWNET_MAX_FRAGMENTS) अणु
			/* हटाओ the oldest */
			fwnet_pd_delete(list_first_entry(&peer->pd_list,
				काष्ठा fwnet_partial_datagram, pd_link));
			peer->pdg_size--;
		पूर्ण
		pd = fwnet_pd_new(net, peer, datagram_label,
				  dg_size, buf, fg_off, len);
		अगर (pd == शून्य) अणु
			retval = -ENOMEM;
			जाओ fail;
		पूर्ण
		peer->pdg_size++;
	पूर्ण अन्यथा अणु
		अगर (fwnet_frag_overlap(pd, fg_off, len) ||
		    pd->datagram_size != dg_size) अणु
			/*
			 * Dअगरfering datagram sizes or overlapping fragments,
			 * discard old datagram and start a new one.
			 */
			fwnet_pd_delete(pd);
			pd = fwnet_pd_new(net, peer, datagram_label,
					  dg_size, buf, fg_off, len);
			अगर (pd == शून्य) अणु
				peer->pdg_size--;
				retval = -ENOMEM;
				जाओ fail;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!fwnet_pd_update(peer, pd, buf, fg_off, len)) अणु
				/*
				 * Couldn't save off fragment anyway
				 * so might as well obliterate the
				 * datagram now.
				 */
				fwnet_pd_delete(pd);
				peer->pdg_size--;
				retval = -ENOMEM;
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण /* new datagram or add to existing one */

	अगर (lf == RFC2374_HDR_FIRSTFRAG)
		pd->ether_type = ether_type;

	अगर (fwnet_pd_is_complete(pd)) अणु
		ether_type = pd->ether_type;
		peer->pdg_size--;
		skb = skb_get(pd->skb);
		fwnet_pd_delete(pd);

		spin_unlock_irqrestore(&dev->lock, flags);

		वापस fwnet_finish_incoming_packet(net, skb, source_node_id,
						    false, ether_type);
	पूर्ण
	/*
	 * Datagram is not complete, we're करोne क्रम the
	 * moment.
	 */
	retval = 0;
 fail:
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस retval;
पूर्ण

अटल व्योम fwnet_receive_packet(काष्ठा fw_card *card, काष्ठा fw_request *r,
		पूर्णांक tcode, पूर्णांक destination, पूर्णांक source, पूर्णांक generation,
		अचिन्हित दीर्घ दीर्घ offset, व्योम *payload, माप_प्रकार length,
		व्योम *callback_data)
अणु
	काष्ठा fwnet_device *dev = callback_data;
	पूर्णांक rcode;

	अगर (destination == IEEE1394_ALL_NODES) अणु
		kमुक्त(r);

		वापस;
	पूर्ण

	अगर (offset != dev->handler.offset)
		rcode = RCODE_ADDRESS_ERROR;
	अन्यथा अगर (tcode != TCODE_WRITE_BLOCK_REQUEST)
		rcode = RCODE_TYPE_ERROR;
	अन्यथा अगर (fwnet_incoming_packet(dev, payload, length,
				       source, generation, false) != 0) अणु
		dev_err(&dev->netdev->dev, "incoming packet failure\n");
		rcode = RCODE_CONFLICT_ERROR;
	पूर्ण अन्यथा
		rcode = RCODE_COMPLETE;

	fw_send_response(card, r, rcode);
पूर्ण

अटल पूर्णांक gasp_source_id(__be32 *p)
अणु
	वापस be32_to_cpu(p[0]) >> 16;
पूर्ण

अटल u32 gasp_specअगरier_id(__be32 *p)
अणु
	वापस (be32_to_cpu(p[0]) & 0xffff) << 8 |
	       (be32_to_cpu(p[1]) & 0xff000000) >> 24;
पूर्ण

अटल u32 gasp_version(__be32 *p)
अणु
	वापस be32_to_cpu(p[1]) & 0xffffff;
पूर्ण

अटल व्योम fwnet_receive_broadcast(काष्ठा fw_iso_context *context,
		u32 cycle, माप_प्रकार header_length, व्योम *header, व्योम *data)
अणु
	काष्ठा fwnet_device *dev;
	काष्ठा fw_iso_packet packet;
	__be16 *hdr_ptr;
	__be32 *buf_ptr;
	पूर्णांक retval;
	u32 length;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ flags;

	dev = data;
	hdr_ptr = header;
	length = be16_to_cpup(hdr_ptr);

	spin_lock_irqsave(&dev->lock, flags);

	offset = dev->rcv_buffer_size * dev->broadcast_rcv_next_ptr;
	buf_ptr = dev->broadcast_rcv_buffer_ptrs[dev->broadcast_rcv_next_ptr++];
	अगर (dev->broadcast_rcv_next_ptr == dev->num_broadcast_rcv_ptrs)
		dev->broadcast_rcv_next_ptr = 0;

	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (length > IEEE1394_GASP_HDR_SIZE &&
	    gasp_specअगरier_id(buf_ptr) == IANA_SPECIFIER_ID &&
	    (gasp_version(buf_ptr) == RFC2734_SW_VERSION
#अगर IS_ENABLED(CONFIG_IPV6)
	     || gasp_version(buf_ptr) == RFC3146_SW_VERSION
#पूर्ण_अगर
	    ))
		fwnet_incoming_packet(dev, buf_ptr + 2,
				      length - IEEE1394_GASP_HDR_SIZE,
				      gasp_source_id(buf_ptr),
				      context->card->generation, true);

	packet.payload_length = dev->rcv_buffer_size;
	packet.पूर्णांकerrupt = 1;
	packet.skip = 0;
	packet.tag = 3;
	packet.sy = 0;
	packet.header_length = IEEE1394_GASP_HDR_SIZE;

	spin_lock_irqsave(&dev->lock, flags);

	retval = fw_iso_context_queue(dev->broadcast_rcv_context, &packet,
				      &dev->broadcast_rcv_buffer, offset);

	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (retval >= 0)
		fw_iso_context_queue_flush(dev->broadcast_rcv_context);
	अन्यथा
		dev_err(&dev->netdev->dev, "requeue failed\n");
पूर्ण

अटल काष्ठा kmem_cache *fwnet_packet_task_cache;

अटल व्योम fwnet_मुक्त_ptask(काष्ठा fwnet_packet_task *ptask)
अणु
	dev_kमुक्त_skb_any(ptask->skb);
	kmem_cache_मुक्त(fwnet_packet_task_cache, ptask);
पूर्ण

/* Caller must hold dev->lock. */
अटल व्योम dec_queued_datagrams(काष्ठा fwnet_device *dev)
अणु
	अगर (--dev->queued_datagrams == FWNET_MIN_QUEUED_DATAGRAMS)
		netअगर_wake_queue(dev->netdev);
पूर्ण

अटल पूर्णांक fwnet_send_packet(काष्ठा fwnet_packet_task *ptask);

अटल व्योम fwnet_transmit_packet_करोne(काष्ठा fwnet_packet_task *ptask)
अणु
	काष्ठा fwnet_device *dev = ptask->dev;
	काष्ठा sk_buff *skb = ptask->skb;
	अचिन्हित दीर्घ flags;
	bool मुक्त;

	spin_lock_irqsave(&dev->lock, flags);

	ptask->outstanding_pkts--;

	/* Check whether we or the networking TX soft-IRQ is last user. */
	मुक्त = (ptask->outstanding_pkts == 0 && ptask->enqueued);
	अगर (मुक्त)
		dec_queued_datagrams(dev);

	अगर (ptask->outstanding_pkts == 0) अणु
		dev->netdev->stats.tx_packets++;
		dev->netdev->stats.tx_bytes += skb->len;
	पूर्ण

	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (ptask->outstanding_pkts > 0) अणु
		u16 dg_size;
		u16 fg_off;
		u16 datagram_label;
		u16 lf;

		/* Update the ptask to poपूर्णांक to the next fragment and send it */
		lf = fwnet_get_hdr_lf(&ptask->hdr);
		चयन (lf) अणु
		हाल RFC2374_HDR_LASTFRAG:
		हाल RFC2374_HDR_UNFRAG:
		शेष:
			dev_err(&dev->netdev->dev,
				"outstanding packet %x lf %x, header %x,%x\n",
				ptask->outstanding_pkts, lf, ptask->hdr.w0,
				ptask->hdr.w1);
			BUG();

		हाल RFC2374_HDR_FIRSTFRAG:
			/* Set frag type here क्रम future पूर्णांकerior fragments */
			dg_size = fwnet_get_hdr_dg_size(&ptask->hdr);
			fg_off = ptask->max_payload - RFC2374_FRAG_HDR_SIZE;
			datagram_label = fwnet_get_hdr_dgl(&ptask->hdr);
			अवरोध;

		हाल RFC2374_HDR_INTFRAG:
			dg_size = fwnet_get_hdr_dg_size(&ptask->hdr);
			fg_off = fwnet_get_hdr_fg_off(&ptask->hdr)
				  + ptask->max_payload - RFC2374_FRAG_HDR_SIZE;
			datagram_label = fwnet_get_hdr_dgl(&ptask->hdr);
			अवरोध;
		पूर्ण

		अगर (ptask->dest_node == IEEE1394_ALL_NODES) अणु
			skb_pull(skb,
				 ptask->max_payload + IEEE1394_GASP_HDR_SIZE);
		पूर्ण अन्यथा अणु
			skb_pull(skb, ptask->max_payload);
		पूर्ण
		अगर (ptask->outstanding_pkts > 1) अणु
			fwnet_make_sf_hdr(&ptask->hdr, RFC2374_HDR_INTFRAG,
					  dg_size, fg_off, datagram_label);
		पूर्ण अन्यथा अणु
			fwnet_make_sf_hdr(&ptask->hdr, RFC2374_HDR_LASTFRAG,
					  dg_size, fg_off, datagram_label);
			ptask->max_payload = skb->len + RFC2374_FRAG_HDR_SIZE;
		पूर्ण
		fwnet_send_packet(ptask);
	पूर्ण

	अगर (मुक्त)
		fwnet_मुक्त_ptask(ptask);
पूर्ण

अटल व्योम fwnet_transmit_packet_failed(काष्ठा fwnet_packet_task *ptask)
अणु
	काष्ठा fwnet_device *dev = ptask->dev;
	अचिन्हित दीर्घ flags;
	bool मुक्त;

	spin_lock_irqsave(&dev->lock, flags);

	/* One fragment failed; करोn't try to send reमुख्यing fragments. */
	ptask->outstanding_pkts = 0;

	/* Check whether we or the networking TX soft-IRQ is last user. */
	मुक्त = ptask->enqueued;
	अगर (मुक्त)
		dec_queued_datagrams(dev);

	dev->netdev->stats.tx_dropped++;
	dev->netdev->stats.tx_errors++;

	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (मुक्त)
		fwnet_मुक्त_ptask(ptask);
पूर्ण

अटल व्योम fwnet_ग_लिखो_complete(काष्ठा fw_card *card, पूर्णांक rcode,
				 व्योम *payload, माप_प्रकार length, व्योम *data)
अणु
	काष्ठा fwnet_packet_task *ptask = data;
	अटल अचिन्हित दीर्घ j;
	अटल पूर्णांक last_rcode, errors_skipped;

	अगर (rcode == RCODE_COMPLETE) अणु
		fwnet_transmit_packet_करोne(ptask);
	पूर्ण अन्यथा अणु
		अगर (prपूर्णांकk_समयd_ratelimit(&j,  1000) || rcode != last_rcode) अणु
			dev_err(&ptask->dev->netdev->dev,
				"fwnet_write_complete failed: %x (skipped %d)\n",
				rcode, errors_skipped);

			errors_skipped = 0;
			last_rcode = rcode;
		पूर्ण अन्यथा अणु
			errors_skipped++;
		पूर्ण
		fwnet_transmit_packet_failed(ptask);
	पूर्ण
पूर्ण

अटल पूर्णांक fwnet_send_packet(काष्ठा fwnet_packet_task *ptask)
अणु
	काष्ठा fwnet_device *dev;
	अचिन्हित tx_len;
	काष्ठा rfc2734_header *bufhdr;
	अचिन्हित दीर्घ flags;
	bool मुक्त;

	dev = ptask->dev;
	tx_len = ptask->max_payload;
	चयन (fwnet_get_hdr_lf(&ptask->hdr)) अणु
	हाल RFC2374_HDR_UNFRAG:
		bufhdr = skb_push(ptask->skb, RFC2374_UNFRAG_HDR_SIZE);
		put_unaligned_be32(ptask->hdr.w0, &bufhdr->w0);
		अवरोध;

	हाल RFC2374_HDR_FIRSTFRAG:
	हाल RFC2374_HDR_INTFRAG:
	हाल RFC2374_HDR_LASTFRAG:
		bufhdr = skb_push(ptask->skb, RFC2374_FRAG_HDR_SIZE);
		put_unaligned_be32(ptask->hdr.w0, &bufhdr->w0);
		put_unaligned_be32(ptask->hdr.w1, &bufhdr->w1);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
	अगर (ptask->dest_node == IEEE1394_ALL_NODES) अणु
		u8 *p;
		पूर्णांक generation;
		पूर्णांक node_id;
		अचिन्हित पूर्णांक sw_version;

		/* ptask->generation may not have been set yet */
		generation = dev->card->generation;
		smp_rmb();
		node_id = dev->card->node_id;

		चयन (ptask->skb->protocol) अणु
		शेष:
			sw_version = RFC2734_SW_VERSION;
			अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
		हाल htons(ETH_P_IPV6):
			sw_version = RFC3146_SW_VERSION;
#पूर्ण_अगर
		पूर्ण

		p = skb_push(ptask->skb, IEEE1394_GASP_HDR_SIZE);
		put_unaligned_be32(node_id << 16 | IANA_SPECIFIER_ID >> 8, p);
		put_unaligned_be32((IANA_SPECIFIER_ID & 0xff) << 24
						| sw_version, &p[4]);

		/* We should not transmit अगर broadcast_channel.valid == 0. */
		fw_send_request(dev->card, &ptask->transaction,
				TCODE_STREAM_DATA,
				fw_stream_packet_destination_id(3,
						IEEE1394_BROADCAST_CHANNEL, 0),
				generation, SCODE_100, 0ULL, ptask->skb->data,
				tx_len + 8, fwnet_ग_लिखो_complete, ptask);

		spin_lock_irqsave(&dev->lock, flags);

		/* If the AT tasklet alपढ़ोy ran, we may be last user. */
		मुक्त = (ptask->outstanding_pkts == 0 && !ptask->enqueued);
		अगर (!मुक्त)
			ptask->enqueued = true;
		अन्यथा
			dec_queued_datagrams(dev);

		spin_unlock_irqrestore(&dev->lock, flags);

		जाओ out;
	पूर्ण

	fw_send_request(dev->card, &ptask->transaction,
			TCODE_WRITE_BLOCK_REQUEST, ptask->dest_node,
			ptask->generation, ptask->speed, ptask->fअगरo_addr,
			ptask->skb->data, tx_len, fwnet_ग_लिखो_complete, ptask);

	spin_lock_irqsave(&dev->lock, flags);

	/* If the AT tasklet alपढ़ोy ran, we may be last user. */
	मुक्त = (ptask->outstanding_pkts == 0 && !ptask->enqueued);
	अगर (!मुक्त)
		ptask->enqueued = true;
	अन्यथा
		dec_queued_datagrams(dev);

	spin_unlock_irqrestore(&dev->lock, flags);

	netअगर_trans_update(dev->netdev);
 out:
	अगर (मुक्त)
		fwnet_मुक्त_ptask(ptask);

	वापस 0;
पूर्ण

अटल व्योम fwnet_fअगरo_stop(काष्ठा fwnet_device *dev)
अणु
	अगर (dev->local_fअगरo == FWNET_NO_FIFO_ADDR)
		वापस;

	fw_core_हटाओ_address_handler(&dev->handler);
	dev->local_fअगरo = FWNET_NO_FIFO_ADDR;
पूर्ण

अटल पूर्णांक fwnet_fअगरo_start(काष्ठा fwnet_device *dev)
अणु
	पूर्णांक retval;

	अगर (dev->local_fअगरo != FWNET_NO_FIFO_ADDR)
		वापस 0;

	dev->handler.length = 4096;
	dev->handler.address_callback = fwnet_receive_packet;
	dev->handler.callback_data = dev;

	retval = fw_core_add_address_handler(&dev->handler,
					     &fw_high_memory_region);
	अगर (retval < 0)
		वापस retval;

	dev->local_fअगरo = dev->handler.offset;

	वापस 0;
पूर्ण

अटल व्योम __fwnet_broadcast_stop(काष्ठा fwnet_device *dev)
अणु
	अचिन्हित u;

	अगर (dev->broadcast_state != FWNET_BROADCAST_ERROR) अणु
		क्रम (u = 0; u < FWNET_ISO_PAGE_COUNT; u++)
			kunmap(dev->broadcast_rcv_buffer.pages[u]);
		fw_iso_buffer_destroy(&dev->broadcast_rcv_buffer, dev->card);
	पूर्ण
	अगर (dev->broadcast_rcv_context) अणु
		fw_iso_context_destroy(dev->broadcast_rcv_context);
		dev->broadcast_rcv_context = शून्य;
	पूर्ण
	kमुक्त(dev->broadcast_rcv_buffer_ptrs);
	dev->broadcast_rcv_buffer_ptrs = शून्य;
	dev->broadcast_state = FWNET_BROADCAST_ERROR;
पूर्ण

अटल व्योम fwnet_broadcast_stop(काष्ठा fwnet_device *dev)
अणु
	अगर (dev->broadcast_state == FWNET_BROADCAST_ERROR)
		वापस;
	fw_iso_context_stop(dev->broadcast_rcv_context);
	__fwnet_broadcast_stop(dev);
पूर्ण

अटल पूर्णांक fwnet_broadcast_start(काष्ठा fwnet_device *dev)
अणु
	काष्ठा fw_iso_context *context;
	पूर्णांक retval;
	अचिन्हित num_packets;
	अचिन्हित max_receive;
	काष्ठा fw_iso_packet packet;
	अचिन्हित दीर्घ offset;
	व्योम **ptrptr;
	अचिन्हित u;

	अगर (dev->broadcast_state != FWNET_BROADCAST_ERROR)
		वापस 0;

	max_receive = 1U << (dev->card->max_receive + 1);
	num_packets = (FWNET_ISO_PAGE_COUNT * PAGE_SIZE) / max_receive;

	ptrptr = kदो_स्मृति_array(num_packets, माप(व्योम *), GFP_KERNEL);
	अगर (!ptrptr) अणु
		retval = -ENOMEM;
		जाओ failed;
	पूर्ण
	dev->broadcast_rcv_buffer_ptrs = ptrptr;

	context = fw_iso_context_create(dev->card, FW_ISO_CONTEXT_RECEIVE,
					IEEE1394_BROADCAST_CHANNEL,
					dev->card->link_speed, 8,
					fwnet_receive_broadcast, dev);
	अगर (IS_ERR(context)) अणु
		retval = PTR_ERR(context);
		जाओ failed;
	पूर्ण

	retval = fw_iso_buffer_init(&dev->broadcast_rcv_buffer, dev->card,
				    FWNET_ISO_PAGE_COUNT, DMA_FROM_DEVICE);
	अगर (retval < 0)
		जाओ failed;

	dev->broadcast_state = FWNET_BROADCAST_STOPPED;

	क्रम (u = 0; u < FWNET_ISO_PAGE_COUNT; u++) अणु
		व्योम *ptr;
		अचिन्हित v;

		ptr = kmap(dev->broadcast_rcv_buffer.pages[u]);
		क्रम (v = 0; v < num_packets / FWNET_ISO_PAGE_COUNT; v++)
			*ptrptr++ = (व्योम *) ((अक्षर *)ptr + v * max_receive);
	पूर्ण
	dev->broadcast_rcv_context = context;

	packet.payload_length = max_receive;
	packet.पूर्णांकerrupt = 1;
	packet.skip = 0;
	packet.tag = 3;
	packet.sy = 0;
	packet.header_length = IEEE1394_GASP_HDR_SIZE;
	offset = 0;

	क्रम (u = 0; u < num_packets; u++) अणु
		retval = fw_iso_context_queue(context, &packet,
				&dev->broadcast_rcv_buffer, offset);
		अगर (retval < 0)
			जाओ failed;

		offset += max_receive;
	पूर्ण
	dev->num_broadcast_rcv_ptrs = num_packets;
	dev->rcv_buffer_size = max_receive;
	dev->broadcast_rcv_next_ptr = 0U;
	retval = fw_iso_context_start(context, -1, 0,
			FW_ISO_CONTEXT_MATCH_ALL_TAGS); /* ??? sync */
	अगर (retval < 0)
		जाओ failed;

	/* FIXME: adjust it according to the min. speed of all known peers? */
	dev->broadcast_xmt_max_payload = IEEE1394_MAX_PAYLOAD_S100
			- IEEE1394_GASP_HDR_SIZE - RFC2374_UNFRAG_HDR_SIZE;
	dev->broadcast_state = FWNET_BROADCAST_RUNNING;

	वापस 0;

 failed:
	__fwnet_broadcast_stop(dev);
	वापस retval;
पूर्ण

अटल व्योम set_carrier_state(काष्ठा fwnet_device *dev)
अणु
	अगर (dev->peer_count > 1)
		netअगर_carrier_on(dev->netdev);
	अन्यथा
		netअगर_carrier_off(dev->netdev);
पूर्ण

/* अगरup */
अटल पूर्णांक fwnet_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा fwnet_device *dev = netdev_priv(net);
	पूर्णांक ret;

	ret = fwnet_broadcast_start(dev);
	अगर (ret)
		वापस ret;

	netअगर_start_queue(net);

	spin_lock_irq(&dev->lock);
	set_carrier_state(dev);
	spin_unlock_irq(&dev->lock);

	वापस 0;
पूर्ण

/* अगरकरोwn */
अटल पूर्णांक fwnet_stop(काष्ठा net_device *net)
अणु
	काष्ठा fwnet_device *dev = netdev_priv(net);

	netअगर_stop_queue(net);
	fwnet_broadcast_stop(dev);

	वापस 0;
पूर्ण

अटल netdev_tx_t fwnet_tx(काष्ठा sk_buff *skb, काष्ठा net_device *net)
अणु
	काष्ठा fwnet_header hdr_buf;
	काष्ठा fwnet_device *dev = netdev_priv(net);
	__be16 proto;
	u16 dest_node;
	अचिन्हित max_payload;
	u16 dg_size;
	u16 *datagram_label_ptr;
	काष्ठा fwnet_packet_task *ptask;
	काष्ठा fwnet_peer *peer;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* Can this happen? */
	अगर (netअगर_queue_stopped(dev->netdev)) अणु
		spin_unlock_irqrestore(&dev->lock, flags);

		वापस NETDEV_TX_BUSY;
	पूर्ण

	ptask = kmem_cache_alloc(fwnet_packet_task_cache, GFP_ATOMIC);
	अगर (ptask == शून्य)
		जाओ fail;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ fail;

	/*
	 * Make a copy of the driver-specअगरic header.
	 * We might need to rebuild the header on tx failure.
	 */
	स_नकल(&hdr_buf, skb->data, माप(hdr_buf));
	proto = hdr_buf.h_proto;

	चयन (proto) अणु
	हाल htons(ETH_P_ARP):
	हाल htons(ETH_P_IP):
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
#पूर्ण_अगर
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण

	skb_pull(skb, माप(hdr_buf));
	dg_size = skb->len;

	/*
	 * Set the transmission type क्रम the packet.  ARP packets and IP
	 * broadcast packets are sent via GASP.
	 */
	अगर (fwnet_hwaddr_is_multicast(hdr_buf.h_dest)) अणु
		max_payload        = dev->broadcast_xmt_max_payload;
		datagram_label_ptr = &dev->broadcast_xmt_datagramlabel;

		ptask->fअगरo_addr   = FWNET_NO_FIFO_ADDR;
		ptask->generation  = 0;
		ptask->dest_node   = IEEE1394_ALL_NODES;
		ptask->speed       = SCODE_100;
	पूर्ण अन्यथा अणु
		जोड़ fwnet_hwaddr *ha = (जोड़ fwnet_hwaddr *)hdr_buf.h_dest;
		__be64 guid = get_unaligned(&ha->uc.uniq_id);
		u8 generation;

		peer = fwnet_peer_find_by_guid(dev, be64_to_cpu(guid));
		अगर (!peer)
			जाओ fail;

		generation         = peer->generation;
		dest_node          = peer->node_id;
		max_payload        = peer->max_payload;
		datagram_label_ptr = &peer->datagram_label;

		ptask->fअगरo_addr   = fwnet_hwaddr_fअगरo(ha);
		ptask->generation  = generation;
		ptask->dest_node   = dest_node;
		ptask->speed       = peer->speed;
	पूर्ण

	ptask->hdr.w0 = 0;
	ptask->hdr.w1 = 0;
	ptask->skb = skb;
	ptask->dev = dev;

	/* Does it all fit in one packet? */
	अगर (dg_size <= max_payload) अणु
		fwnet_make_uf_hdr(&ptask->hdr, ntohs(proto));
		ptask->outstanding_pkts = 1;
		max_payload = dg_size + RFC2374_UNFRAG_HDR_SIZE;
	पूर्ण अन्यथा अणु
		u16 datagram_label;

		max_payload -= RFC2374_FRAG_OVERHEAD;
		datagram_label = (*datagram_label_ptr)++;
		fwnet_make_ff_hdr(&ptask->hdr, ntohs(proto), dg_size,
				  datagram_label);
		ptask->outstanding_pkts = DIV_ROUND_UP(dg_size, max_payload);
		max_payload += RFC2374_FRAG_HDR_SIZE;
	पूर्ण

	अगर (++dev->queued_datagrams == FWNET_MAX_QUEUED_DATAGRAMS)
		netअगर_stop_queue(dev->netdev);

	spin_unlock_irqrestore(&dev->lock, flags);

	ptask->max_payload = max_payload;
	ptask->enqueued    = 0;

	fwnet_send_packet(ptask);

	वापस NETDEV_TX_OK;

 fail:
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (ptask)
		kmem_cache_मुक्त(fwnet_packet_task_cache, ptask);

	अगर (skb != शून्य)
		dev_kमुक्त_skb(skb);

	net->stats.tx_dropped++;
	net->stats.tx_errors++;

	/*
	 * FIXME: According to a patch from 2003-02-26, "वापसing non-zero
	 * causes serious problems" here, allegedly.  Beक्रमe that patch,
	 * -ERRNO was वापसed which is not appropriate under Linux 2.6.
	 * Perhaps more needs to be करोne?  Stop the queue in serious
	 * conditions and restart it अन्यथाwhere?
	 */
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops fwnet_ethtool_ops = अणु
	.get_link	= ethtool_op_get_link,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops fwnet_netdev_ops = अणु
	.nकरो_खोलो       = fwnet_खोलो,
	.nकरो_stop	= fwnet_stop,
	.nकरो_start_xmit = fwnet_tx,
पूर्ण;

अटल व्योम fwnet_init_dev(काष्ठा net_device *net)
अणु
	net->header_ops		= &fwnet_header_ops;
	net->netdev_ops		= &fwnet_netdev_ops;
	net->watchकरोg_समयo	= 2 * HZ;
	net->flags		= IFF_BROADCAST | IFF_MULTICAST;
	net->features		= NETIF_F_HIGHDMA;
	net->addr_len		= FWNET_ALEN;
	net->hard_header_len	= FWNET_HLEN;
	net->type		= ARPHRD_IEEE1394;
	net->tx_queue_len	= FWNET_TX_QUEUE_LEN;
	net->ethtool_ops	= &fwnet_ethtool_ops;
पूर्ण

/* caller must hold fwnet_device_mutex */
अटल काष्ठा fwnet_device *fwnet_dev_find(काष्ठा fw_card *card)
अणु
	काष्ठा fwnet_device *dev;

	list_क्रम_each_entry(dev, &fwnet_device_list, dev_link)
		अगर (dev->card == card)
			वापस dev;

	वापस शून्य;
पूर्ण

अटल पूर्णांक fwnet_add_peer(काष्ठा fwnet_device *dev,
			  काष्ठा fw_unit *unit, काष्ठा fw_device *device)
अणु
	काष्ठा fwnet_peer *peer;

	peer = kदो_स्मृति(माप(*peer), GFP_KERNEL);
	अगर (!peer)
		वापस -ENOMEM;

	dev_set_drvdata(&unit->device, peer);

	peer->dev = dev;
	peer->guid = (u64)device->config_rom[3] << 32 | device->config_rom[4];
	INIT_LIST_HEAD(&peer->pd_list);
	peer->pdg_size = 0;
	peer->datagram_label = 0;
	peer->speed = device->max_speed;
	peer->max_payload = fwnet_max_payload(device->max_rec, peer->speed);

	peer->generation = device->generation;
	smp_rmb();
	peer->node_id = device->node_id;

	spin_lock_irq(&dev->lock);
	list_add_tail(&peer->peer_link, &dev->peer_list);
	dev->peer_count++;
	set_carrier_state(dev);
	spin_unlock_irq(&dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक fwnet_probe(काष्ठा fw_unit *unit,
		       स्थिर काष्ठा ieee1394_device_id *id)
अणु
	काष्ठा fw_device *device = fw_parent_device(unit);
	काष्ठा fw_card *card = device->card;
	काष्ठा net_device *net;
	bool allocated_netdev = false;
	काष्ठा fwnet_device *dev;
	पूर्णांक ret;
	जोड़ fwnet_hwaddr *ha;

	mutex_lock(&fwnet_device_mutex);

	dev = fwnet_dev_find(card);
	अगर (dev) अणु
		net = dev->netdev;
		जाओ have_dev;
	पूर्ण

	net = alloc_netdev(माप(*dev), "firewire%d", NET_NAME_UNKNOWN,
			   fwnet_init_dev);
	अगर (net == शून्य) अणु
		mutex_unlock(&fwnet_device_mutex);
		वापस -ENOMEM;
	पूर्ण

	allocated_netdev = true;
	SET_NETDEV_DEV(net, card->device);
	dev = netdev_priv(net);

	spin_lock_init(&dev->lock);
	dev->broadcast_state = FWNET_BROADCAST_ERROR;
	dev->broadcast_rcv_context = शून्य;
	dev->broadcast_xmt_max_payload = 0;
	dev->broadcast_xmt_datagramlabel = 0;
	dev->local_fअगरo = FWNET_NO_FIFO_ADDR;
	dev->queued_datagrams = 0;
	INIT_LIST_HEAD(&dev->peer_list);
	dev->card = card;
	dev->netdev = net;

	ret = fwnet_fअगरo_start(dev);
	अगर (ret < 0)
		जाओ out;
	dev->local_fअगरo = dev->handler.offset;

	/*
	 * शेष MTU: RFC 2734 cl. 4, RFC 3146 cl. 4
	 * maximum MTU: RFC 2734 cl. 4.2, fragment encapsulation header's
	 *              maximum possible datagram_size + 1 = 0xfff + 1
	 */
	net->mtu = 1500U;
	net->min_mtu = ETH_MIN_MTU;
	net->max_mtu = 4096U;

	/* Set our hardware address जबतक we're at it */
	ha = (जोड़ fwnet_hwaddr *)net->dev_addr;
	put_unaligned_be64(card->guid, &ha->uc.uniq_id);
	ha->uc.max_rec = dev->card->max_receive;
	ha->uc.sspd = dev->card->link_speed;
	put_unaligned_be16(dev->local_fअगरo >> 32, &ha->uc.fअगरo_hi);
	put_unaligned_be32(dev->local_fअगरo & 0xffffffff, &ha->uc.fअगरo_lo);

	स_रखो(net->broadcast, -1, net->addr_len);

	ret = रेजिस्टर_netdev(net);
	अगर (ret)
		जाओ out;

	list_add_tail(&dev->dev_link, &fwnet_device_list);
	dev_notice(&net->dev, "IP over IEEE 1394 on card %s\n",
		   dev_name(card->device));
 have_dev:
	ret = fwnet_add_peer(dev, unit, device);
	अगर (ret && allocated_netdev) अणु
		unरेजिस्टर_netdev(net);
		list_del(&dev->dev_link);
 out:
		fwnet_fअगरo_stop(dev);
		मुक्त_netdev(net);
	पूर्ण

	mutex_unlock(&fwnet_device_mutex);

	वापस ret;
पूर्ण

/*
 * FIXME पात partially sent fragmented datagrams,
 * discard partially received fragmented datagrams
 */
अटल व्योम fwnet_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा fw_device *device = fw_parent_device(unit);
	काष्ठा fwnet_peer *peer = dev_get_drvdata(&unit->device);
	पूर्णांक generation;

	generation = device->generation;

	spin_lock_irq(&peer->dev->lock);
	peer->node_id    = device->node_id;
	peer->generation = generation;
	spin_unlock_irq(&peer->dev->lock);
पूर्ण

अटल व्योम fwnet_हटाओ_peer(काष्ठा fwnet_peer *peer, काष्ठा fwnet_device *dev)
अणु
	काष्ठा fwnet_partial_datagram *pd, *pd_next;

	spin_lock_irq(&dev->lock);
	list_del(&peer->peer_link);
	dev->peer_count--;
	set_carrier_state(dev);
	spin_unlock_irq(&dev->lock);

	list_क्रम_each_entry_safe(pd, pd_next, &peer->pd_list, pd_link)
		fwnet_pd_delete(pd);

	kमुक्त(peer);
पूर्ण

अटल व्योम fwnet_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा fwnet_peer *peer = dev_get_drvdata(&unit->device);
	काष्ठा fwnet_device *dev = peer->dev;
	काष्ठा net_device *net;
	पूर्णांक i;

	mutex_lock(&fwnet_device_mutex);

	net = dev->netdev;

	fwnet_हटाओ_peer(peer, dev);

	अगर (list_empty(&dev->peer_list)) अणु
		unरेजिस्टर_netdev(net);

		fwnet_fअगरo_stop(dev);

		क्रम (i = 0; dev->queued_datagrams && i < 5; i++)
			ssleep(1);
		WARN_ON(dev->queued_datagrams);
		list_del(&dev->dev_link);

		मुक्त_netdev(net);
	पूर्ण

	mutex_unlock(&fwnet_device_mutex);
पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id fwnet_id_table[] = अणु
	अणु
		.match_flags  = IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.specअगरier_id = IANA_SPECIFIER_ID,
		.version      = RFC2734_SW_VERSION,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IPV6)
	अणु
		.match_flags  = IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.specअगरier_id = IANA_SPECIFIER_ID,
		.version      = RFC3146_SW_VERSION,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा fw_driver fwnet_driver = अणु
	.driver = अणु
		.owner  = THIS_MODULE,
		.name   = KBUILD_MODNAME,
		.bus    = &fw_bus_type,
	पूर्ण,
	.probe    = fwnet_probe,
	.update   = fwnet_update,
	.हटाओ   = fwnet_हटाओ,
	.id_table = fwnet_id_table,
पूर्ण;

अटल स्थिर u32 rfc2374_unit_directory_data[] = अणु
	0x00040000,	/* directory_length		*/
	0x1200005e,	/* unit_specअगरier_id: IANA	*/
	0x81000003,	/* textual descriptor offset	*/
	0x13000001,	/* unit_sw_version: RFC 2734	*/
	0x81000005,	/* textual descriptor offset	*/
	0x00030000,	/* descriptor_length		*/
	0x00000000,	/* text				*/
	0x00000000,	/* minimal ASCII, en		*/
	0x49414e41,	/* I A N A			*/
	0x00030000,	/* descriptor_length		*/
	0x00000000,	/* text				*/
	0x00000000,	/* minimal ASCII, en		*/
	0x49507634,	/* I P v 4			*/
पूर्ण;

अटल काष्ठा fw_descriptor rfc2374_unit_directory = अणु
	.length = ARRAY_SIZE(rfc2374_unit_directory_data),
	.key    = (CSR_सूचीECTORY | CSR_UNIT) << 24,
	.data   = rfc2374_unit_directory_data
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल स्थिर u32 rfc3146_unit_directory_data[] = अणु
	0x00040000,	/* directory_length		*/
	0x1200005e,	/* unit_specअगरier_id: IANA	*/
	0x81000003,	/* textual descriptor offset	*/
	0x13000002,	/* unit_sw_version: RFC 3146	*/
	0x81000005,	/* textual descriptor offset	*/
	0x00030000,	/* descriptor_length		*/
	0x00000000,	/* text				*/
	0x00000000,	/* minimal ASCII, en		*/
	0x49414e41,	/* I A N A			*/
	0x00030000,	/* descriptor_length		*/
	0x00000000,	/* text				*/
	0x00000000,	/* minimal ASCII, en		*/
	0x49507636,	/* I P v 6			*/
पूर्ण;

अटल काष्ठा fw_descriptor rfc3146_unit_directory = अणु
	.length = ARRAY_SIZE(rfc3146_unit_directory_data),
	.key    = (CSR_सूचीECTORY | CSR_UNIT) << 24,
	.data   = rfc3146_unit_directory_data
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init fwnet_init(व्योम)
अणु
	पूर्णांक err;

	err = fw_core_add_descriptor(&rfc2374_unit_directory);
	अगर (err)
		वापस err;

#अगर IS_ENABLED(CONFIG_IPV6)
	err = fw_core_add_descriptor(&rfc3146_unit_directory);
	अगर (err)
		जाओ out;
#पूर्ण_अगर

	fwnet_packet_task_cache = kmem_cache_create("packet_task",
			माप(काष्ठा fwnet_packet_task), 0, 0, शून्य);
	अगर (!fwnet_packet_task_cache) अणु
		err = -ENOMEM;
		जाओ out2;
	पूर्ण

	err = driver_रेजिस्टर(&fwnet_driver.driver);
	अगर (!err)
		वापस 0;

	kmem_cache_destroy(fwnet_packet_task_cache);
out2:
#अगर IS_ENABLED(CONFIG_IPV6)
	fw_core_हटाओ_descriptor(&rfc3146_unit_directory);
out:
#पूर्ण_अगर
	fw_core_हटाओ_descriptor(&rfc2374_unit_directory);

	वापस err;
पूर्ण
module_init(fwnet_init);

अटल व्योम __निकास fwnet_cleanup(व्योम)
अणु
	driver_unरेजिस्टर(&fwnet_driver.driver);
	kmem_cache_destroy(fwnet_packet_task_cache);
#अगर IS_ENABLED(CONFIG_IPV6)
	fw_core_हटाओ_descriptor(&rfc3146_unit_directory);
#पूर्ण_अगर
	fw_core_हटाओ_descriptor(&rfc2374_unit_directory);
पूर्ण
module_निकास(fwnet_cleanup);

MODULE_AUTHOR("Jay Fenlason <fenlason@redhat.com>");
MODULE_DESCRIPTION("IP over IEEE1394 as per RFC 2734/3146");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(ieee1394, fwnet_id_table);

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Martin Hundebथचll <martin@hundeboll.net>
 */

#समावेश "fragmentation.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/minmax.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "hard-interface.h"
#समावेश "originator.h"
#समावेश "routing.h"
#समावेश "send.h"

/**
 * batadv_frag_clear_chain() - delete entries in the fragment buffer chain
 * @head: head of chain with entries.
 * @dropped: whether the chain is cleared because all fragments are dropped
 *
 * Free fragments in the passed hlist. Should be called with appropriate lock.
 */
अटल व्योम batadv_frag_clear_chain(काष्ठा hlist_head *head, bool dropped)
अणु
	काष्ठा batadv_frag_list_entry *entry;
	काष्ठा hlist_node *node;

	hlist_क्रम_each_entry_safe(entry, node, head, list) अणु
		hlist_del(&entry->list);

		अगर (dropped)
			kमुक्त_skb(entry->skb);
		अन्यथा
			consume_skb(entry->skb);

		kमुक्त(entry);
	पूर्ण
पूर्ण

/**
 * batadv_frag_purge_orig() - मुक्त fragments associated to an orig
 * @orig_node: originator to मुक्त fragments from
 * @check_cb: optional function to tell अगर an entry should be purged
 */
व्योम batadv_frag_purge_orig(काष्ठा batadv_orig_node *orig_node,
			    bool (*check_cb)(काष्ठा batadv_frag_table_entry *))
अणु
	काष्ठा batadv_frag_table_entry *chain;
	u8 i;

	क्रम (i = 0; i < BATADV_FRAG_BUFFER_COUNT; i++) अणु
		chain = &orig_node->fragments[i];
		spin_lock_bh(&chain->lock);

		अगर (!check_cb || check_cb(chain)) अणु
			batadv_frag_clear_chain(&chain->fragment_list, true);
			chain->size = 0;
		पूर्ण

		spin_unlock_bh(&chain->lock);
	पूर्ण
पूर्ण

/**
 * batadv_frag_size_limit() - maximum possible size of packet to be fragmented
 *
 * Return: the maximum size of payload that can be fragmented.
 */
अटल पूर्णांक batadv_frag_size_limit(व्योम)
अणु
	पूर्णांक limit = BATADV_FRAG_MAX_FRAG_SIZE;

	limit -= माप(काष्ठा batadv_frag_packet);
	limit *= BATADV_FRAG_MAX_FRAGMENTS;

	वापस limit;
पूर्ण

/**
 * batadv_frag_init_chain() - check and prepare fragment chain क्रम new fragment
 * @chain: chain in fragments table to init
 * @seqno: sequence number of the received fragment
 *
 * Make chain पढ़ोy क्रम a fragment with sequence number "seqno". Delete existing
 * entries अगर they have an "old" sequence number.
 *
 * Caller must hold chain->lock.
 *
 * Return: true अगर chain is empty and the caller can just insert the new
 * fragment without searching क्रम the right position.
 */
अटल bool batadv_frag_init_chain(काष्ठा batadv_frag_table_entry *chain,
				   u16 seqno)
अणु
	lockdep_निश्चित_held(&chain->lock);

	अगर (chain->seqno == seqno)
		वापस false;

	अगर (!hlist_empty(&chain->fragment_list))
		batadv_frag_clear_chain(&chain->fragment_list, true);

	chain->size = 0;
	chain->seqno = seqno;

	वापस true;
पूर्ण

/**
 * batadv_frag_insert_packet() - insert a fragment पूर्णांकo a fragment chain
 * @orig_node: originator that the fragment was received from
 * @skb: skb to insert
 * @chain_out: list head to attach complete chains of fragments to
 *
 * Insert a new fragment पूर्णांकo the reverse ordered chain in the right table
 * entry. The hash table entry is cleared अगर "old" fragments exist in it.
 *
 * Return: true अगर skb is buffered, false on error. If the chain has all the
 * fragments needed to merge the packet, the chain is moved to the passed head
 * to aव्योम locking the chain in the table.
 */
अटल bool batadv_frag_insert_packet(काष्ठा batadv_orig_node *orig_node,
				      काष्ठा sk_buff *skb,
				      काष्ठा hlist_head *chain_out)
अणु
	काष्ठा batadv_frag_table_entry *chain;
	काष्ठा batadv_frag_list_entry *frag_entry_new = शून्य, *frag_entry_curr;
	काष्ठा batadv_frag_list_entry *frag_entry_last = शून्य;
	काष्ठा batadv_frag_packet *frag_packet;
	u8 bucket;
	u16 seqno, hdr_size = माप(काष्ठा batadv_frag_packet);
	bool ret = false;

	/* Linearize packet to aव्योम linearizing 16 packets in a row when करोing
	 * the later merge. Non-linear merge should be added to हटाओ this
	 * linearization.
	 */
	अगर (skb_linearize(skb) < 0)
		जाओ err;

	frag_packet = (काष्ठा batadv_frag_packet *)skb->data;
	seqno = ntohs(frag_packet->seqno);
	bucket = seqno % BATADV_FRAG_BUFFER_COUNT;

	frag_entry_new = kदो_स्मृति(माप(*frag_entry_new), GFP_ATOMIC);
	अगर (!frag_entry_new)
		जाओ err;

	frag_entry_new->skb = skb;
	frag_entry_new->no = frag_packet->no;

	/* Select entry in the "chain table" and delete any prior fragments
	 * with another sequence number. batadv_frag_init_chain() वापसs true,
	 * अगर the list is empty at वापस.
	 */
	chain = &orig_node->fragments[bucket];
	spin_lock_bh(&chain->lock);
	अगर (batadv_frag_init_chain(chain, seqno)) अणु
		hlist_add_head(&frag_entry_new->list, &chain->fragment_list);
		chain->size = skb->len - hdr_size;
		chain->बारtamp = jअगरfies;
		chain->total_size = ntohs(frag_packet->total_size);
		ret = true;
		जाओ out;
	पूर्ण

	/* Find the position क्रम the new fragment. */
	hlist_क्रम_each_entry(frag_entry_curr, &chain->fragment_list, list) अणु
		/* Drop packet अगर fragment alपढ़ोy exists. */
		अगर (frag_entry_curr->no == frag_entry_new->no)
			जाओ err_unlock;

		/* Order fragments from highest to lowest. */
		अगर (frag_entry_curr->no < frag_entry_new->no) अणु
			hlist_add_beक्रमe(&frag_entry_new->list,
					 &frag_entry_curr->list);
			chain->size += skb->len - hdr_size;
			chain->बारtamp = jअगरfies;
			ret = true;
			जाओ out;
		पूर्ण

		/* store current entry because it could be the last in list */
		frag_entry_last = frag_entry_curr;
	पूर्ण

	/* Reached the end of the list, so insert after 'frag_entry_last'. */
	अगर (likely(frag_entry_last)) अणु
		hlist_add_behind(&frag_entry_new->list, &frag_entry_last->list);
		chain->size += skb->len - hdr_size;
		chain->बारtamp = jअगरfies;
		ret = true;
	पूर्ण

out:
	अगर (chain->size > batadv_frag_size_limit() ||
	    chain->total_size != ntohs(frag_packet->total_size) ||
	    chain->total_size > batadv_frag_size_limit()) अणु
		/* Clear chain अगर total size of either the list or the packet
		 * exceeds the maximum size of one merged packet. Don't allow
		 * packets to have dअगरferent total_size.
		 */
		batadv_frag_clear_chain(&chain->fragment_list, true);
		chain->size = 0;
	पूर्ण अन्यथा अगर (ntohs(frag_packet->total_size) == chain->size) अणु
		/* All fragments received. Hand over chain to caller. */
		hlist_move_list(&chain->fragment_list, chain_out);
		chain->size = 0;
	पूर्ण

err_unlock:
	spin_unlock_bh(&chain->lock);

err:
	अगर (!ret) अणु
		kमुक्त(frag_entry_new);
		kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * batadv_frag_merge_packets() - merge a chain of fragments
 * @chain: head of chain with fragments
 *
 * Expand the first skb in the chain and copy the content of the reमुख्यing
 * skb's पूर्णांकo the expanded one. After करोing so, clear the chain.
 *
 * Return: the merged skb or शून्य on error.
 */
अटल काष्ठा sk_buff *
batadv_frag_merge_packets(काष्ठा hlist_head *chain)
अणु
	काष्ठा batadv_frag_packet *packet;
	काष्ठा batadv_frag_list_entry *entry;
	काष्ठा sk_buff *skb_out;
	पूर्णांक size, hdr_size = माप(काष्ठा batadv_frag_packet);
	bool dropped = false;

	/* Remove first entry, as this is the destination क्रम the rest of the
	 * fragments.
	 */
	entry = hlist_entry(chain->first, काष्ठा batadv_frag_list_entry, list);
	hlist_del(&entry->list);
	skb_out = entry->skb;
	kमुक्त(entry);

	packet = (काष्ठा batadv_frag_packet *)skb_out->data;
	size = ntohs(packet->total_size) + hdr_size;

	/* Make room क्रम the rest of the fragments. */
	अगर (pskb_expand_head(skb_out, 0, size - skb_out->len, GFP_ATOMIC) < 0) अणु
		kमुक्त_skb(skb_out);
		skb_out = शून्य;
		dropped = true;
		जाओ मुक्त;
	पूर्ण

	/* Move the existing MAC header to just beक्रमe the payload. (Override
	 * the fragment header.)
	 */
	skb_pull(skb_out, hdr_size);
	skb_out->ip_summed = CHECKSUM_NONE;
	स_हटाओ(skb_out->data - ETH_HLEN, skb_mac_header(skb_out), ETH_HLEN);
	skb_set_mac_header(skb_out, -ETH_HLEN);
	skb_reset_network_header(skb_out);
	skb_reset_transport_header(skb_out);

	/* Copy the payload of the each fragment पूर्णांकo the last skb */
	hlist_क्रम_each_entry(entry, chain, list) अणु
		size = entry->skb->len - hdr_size;
		skb_put_data(skb_out, entry->skb->data + hdr_size, size);
	पूर्ण

मुक्त:
	/* Locking is not needed, because 'chain' is not part of any orig. */
	batadv_frag_clear_chain(chain, dropped);
	वापस skb_out;
पूर्ण

/**
 * batadv_frag_skb_buffer() - buffer fragment क्रम later merge
 * @skb: skb to buffer
 * @orig_node_src: originator that the skb is received from
 *
 * Add fragment to buffer and merge fragments अगर possible.
 *
 * There are three possible outcomes: 1) Packet is merged: Return true and
 * set *skb to merged packet; 2) Packet is buffered: Return true and set *skb
 * to शून्य; 3) Error: Return false and मुक्त skb.
 *
 * Return: true when the packet is merged or buffered, false when skb is not
 * used.
 */
bool batadv_frag_skb_buffer(काष्ठा sk_buff **skb,
			    काष्ठा batadv_orig_node *orig_node_src)
अणु
	काष्ठा sk_buff *skb_out = शून्य;
	काष्ठा hlist_head head = HLIST_HEAD_INIT;
	bool ret = false;

	/* Add packet to buffer and table entry अगर merge is possible. */
	अगर (!batadv_frag_insert_packet(orig_node_src, *skb, &head))
		जाओ out_err;

	/* Leave अगर more fragments are needed to merge. */
	अगर (hlist_empty(&head))
		जाओ out;

	skb_out = batadv_frag_merge_packets(&head);
	अगर (!skb_out)
		जाओ out_err;

out:
	ret = true;
out_err:
	*skb = skb_out;
	वापस ret;
पूर्ण

/**
 * batadv_frag_skb_fwd() - क्रमward fragments that would exceed MTU when merged
 * @skb: skb to क्रमward
 * @recv_अगर: पूर्णांकerface that the skb is received on
 * @orig_node_src: originator that the skb is received from
 *
 * Look up the next-hop of the fragments payload and check अगर the merged packet
 * will exceed the MTU towards the next-hop. If so, the fragment is क्रमwarded
 * without merging it.
 *
 * Return: true अगर the fragment is consumed/क्रमwarded, false otherwise.
 */
bool batadv_frag_skb_fwd(काष्ठा sk_buff *skb,
			 काष्ठा batadv_hard_अगरace *recv_अगर,
			 काष्ठा batadv_orig_node *orig_node_src)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	काष्ठा batadv_orig_node *orig_node_dst;
	काष्ठा batadv_neigh_node *neigh_node = शून्य;
	काष्ठा batadv_frag_packet *packet;
	u16 total_size;
	bool ret = false;

	packet = (काष्ठा batadv_frag_packet *)skb->data;
	orig_node_dst = batadv_orig_hash_find(bat_priv, packet->dest);
	अगर (!orig_node_dst)
		जाओ out;

	neigh_node = batadv_find_router(bat_priv, orig_node_dst, recv_अगर);
	अगर (!neigh_node)
		जाओ out;

	/* Forward the fragment, अगर the merged packet would be too big to
	 * be assembled.
	 */
	total_size = ntohs(packet->total_size);
	अगर (total_size > neigh_node->अगर_incoming->net_dev->mtu) अणु
		batadv_inc_counter(bat_priv, BATADV_CNT_FRAG_FWD);
		batadv_add_counter(bat_priv, BATADV_CNT_FRAG_FWD_BYTES,
				   skb->len + ETH_HLEN);

		packet->ttl--;
		batadv_send_unicast_skb(skb, neigh_node);
		ret = true;
	पूर्ण

out:
	अगर (orig_node_dst)
		batadv_orig_node_put(orig_node_dst);
	अगर (neigh_node)
		batadv_neigh_node_put(neigh_node);
	वापस ret;
पूर्ण

/**
 * batadv_frag_create() - create a fragment from skb
 * @net_dev: outgoing device क्रम fragment
 * @skb: skb to create fragment from
 * @frag_head: header to use in new fragment
 * @fragment_size: size of new fragment
 *
 * Split the passed skb पूर्णांकo two fragments: A new one with size matching the
 * passed mtu and the old one with the rest. The new skb contains data from the
 * tail of the old skb.
 *
 * Return: the new fragment, शून्य on error.
 */
अटल काष्ठा sk_buff *batadv_frag_create(काष्ठा net_device *net_dev,
					  काष्ठा sk_buff *skb,
					  काष्ठा batadv_frag_packet *frag_head,
					  अचिन्हित पूर्णांक fragment_size)
अणु
	अचिन्हित पूर्णांक ll_reserved = LL_RESERVED_SPACE(net_dev);
	अचिन्हित पूर्णांक tailroom = net_dev->needed_tailroom;
	काष्ठा sk_buff *skb_fragment;
	अचिन्हित पूर्णांक header_size = माप(*frag_head);
	अचिन्हित पूर्णांक mtu = fragment_size + header_size;

	skb_fragment = dev_alloc_skb(ll_reserved + mtu + tailroom);
	अगर (!skb_fragment)
		जाओ err;

	skb_fragment->priority = skb->priority;

	/* Eat the last mtu-bytes of the skb */
	skb_reserve(skb_fragment, ll_reserved + header_size);
	skb_split(skb, skb_fragment, skb->len - fragment_size);

	/* Add the header */
	skb_push(skb_fragment, header_size);
	स_नकल(skb_fragment->data, frag_head, header_size);

err:
	वापस skb_fragment;
पूर्ण

/**
 * batadv_frag_send_packet() - create up to 16 fragments from the passed skb
 * @skb: skb to create fragments from
 * @orig_node: final destination of the created fragments
 * @neigh_node: next-hop of the created fragments
 *
 * Return: the netdev tx status or a negative त्रुटि_सं code on a failure
 */
पूर्णांक batadv_frag_send_packet(काष्ठा sk_buff *skb,
			    काष्ठा batadv_orig_node *orig_node,
			    काष्ठा batadv_neigh_node *neigh_node)
अणु
	काष्ठा net_device *net_dev = neigh_node->अगर_incoming->net_dev;
	काष्ठा batadv_priv *bat_priv;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_frag_packet frag_header;
	काष्ठा sk_buff *skb_fragment;
	अचिन्हित पूर्णांक mtu = net_dev->mtu;
	अचिन्हित पूर्णांक header_size = माप(frag_header);
	अचिन्हित पूर्णांक max_fragment_size, num_fragments;
	पूर्णांक ret;

	/* To aव्योम merge and refragmentation at next-hops we never send
	 * fragments larger than BATADV_FRAG_MAX_FRAG_SIZE
	 */
	mtu = min_t(अचिन्हित पूर्णांक, mtu, BATADV_FRAG_MAX_FRAG_SIZE);
	max_fragment_size = mtu - header_size;

	अगर (skb->len == 0 || max_fragment_size == 0)
		वापस -EINVAL;

	num_fragments = (skb->len - 1) / max_fragment_size + 1;
	max_fragment_size = (skb->len - 1) / num_fragments + 1;

	/* Don't even try to fragment, अगर we need more than 16 fragments */
	अगर (num_fragments > BATADV_FRAG_MAX_FRAGMENTS) अणु
		ret = -EAGAIN;
		जाओ मुक्त_skb;
	पूर्ण

	bat_priv = orig_node->bat_priv;
	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर) अणु
		ret = -EINVAL;
		जाओ मुक्त_skb;
	पूर्ण

	/* Create one header to be copied to all fragments */
	frag_header.packet_type = BATADV_UNICAST_FRAG;
	frag_header.version = BATADV_COMPAT_VERSION;
	frag_header.ttl = BATADV_TTL;
	frag_header.seqno = htons(atomic_inc_वापस(&bat_priv->frag_seqno));
	frag_header.reserved = 0;
	frag_header.no = 0;
	frag_header.total_size = htons(skb->len);

	/* skb->priority values from 256->263 are magic values to
	 * directly indicate a specअगरic 802.1d priority.  This is used
	 * to allow 802.1d priority to be passed directly in from VLAN
	 * tags, etc.
	 */
	अगर (skb->priority >= 256 && skb->priority <= 263)
		frag_header.priority = skb->priority - 256;
	अन्यथा
		frag_header.priority = 0;

	ether_addr_copy(frag_header.orig, primary_अगर->net_dev->dev_addr);
	ether_addr_copy(frag_header.dest, orig_node->orig);

	/* Eat and send fragments from the tail of skb */
	जबतक (skb->len > max_fragment_size) अणु
		/* The initial check in this function should cover this हाल */
		अगर (unlikely(frag_header.no == BATADV_FRAG_MAX_FRAGMENTS - 1)) अणु
			ret = -EINVAL;
			जाओ put_primary_अगर;
		पूर्ण

		skb_fragment = batadv_frag_create(net_dev, skb, &frag_header,
						  max_fragment_size);
		अगर (!skb_fragment) अणु
			ret = -ENOMEM;
			जाओ put_primary_अगर;
		पूर्ण

		batadv_inc_counter(bat_priv, BATADV_CNT_FRAG_TX);
		batadv_add_counter(bat_priv, BATADV_CNT_FRAG_TX_BYTES,
				   skb_fragment->len + ETH_HLEN);
		ret = batadv_send_unicast_skb(skb_fragment, neigh_node);
		अगर (ret != NET_XMIT_SUCCESS) अणु
			ret = NET_XMIT_DROP;
			जाओ put_primary_अगर;
		पूर्ण

		frag_header.no++;
	पूर्ण

	/* make sure that there is at least enough head क्रम the fragmentation
	 * and ethernet headers
	 */
	ret = skb_cow_head(skb, ETH_HLEN + header_size);
	अगर (ret < 0)
		जाओ put_primary_अगर;

	skb_push(skb, header_size);
	स_नकल(skb->data, &frag_header, header_size);

	/* Send the last fragment */
	batadv_inc_counter(bat_priv, BATADV_CNT_FRAG_TX);
	batadv_add_counter(bat_priv, BATADV_CNT_FRAG_TX_BYTES,
			   skb->len + ETH_HLEN);
	ret = batadv_send_unicast_skb(skb, neigh_node);
	/* skb was consumed */
	skb = शून्य;

put_primary_अगर:
	batadv_hardअगर_put(primary_अगर);
मुक्त_skb:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

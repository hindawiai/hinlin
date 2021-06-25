<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Simon Wunderlich
 */

#समावेश "bridge_loop_avoidance.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/crc16.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/jhash.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <net/arp.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "hard-interface.h"
#समावेश "hash.h"
#समावेश "log.h"
#समावेश "netlink.h"
#समावेश "originator.h"
#समावेश "soft-interface.h"
#समावेश "translation-table.h"

अटल स्थिर u8 batadv_announce_mac[4] = अणु0x43, 0x05, 0x43, 0x05पूर्ण;

अटल व्योम batadv_bla_periodic_work(काष्ठा work_काष्ठा *work);
अटल व्योम
batadv_bla_send_announce(काष्ठा batadv_priv *bat_priv,
			 काष्ठा batadv_bla_backbone_gw *backbone_gw);

/**
 * batadv_choose_claim() - choose the right bucket क्रम a claim.
 * @data: data to hash
 * @size: size of the hash table
 *
 * Return: the hash index of the claim
 */
अटल अंतरभूत u32 batadv_choose_claim(स्थिर व्योम *data, u32 size)
अणु
	काष्ठा batadv_bla_claim *claim = (काष्ठा batadv_bla_claim *)data;
	u32 hash = 0;

	hash = jhash(&claim->addr, माप(claim->addr), hash);
	hash = jhash(&claim->vid, माप(claim->vid), hash);

	वापस hash % size;
पूर्ण

/**
 * batadv_choose_backbone_gw() - choose the right bucket क्रम a backbone gateway.
 * @data: data to hash
 * @size: size of the hash table
 *
 * Return: the hash index of the backbone gateway
 */
अटल अंतरभूत u32 batadv_choose_backbone_gw(स्थिर व्योम *data, u32 size)
अणु
	स्थिर काष्ठा batadv_bla_backbone_gw *gw;
	u32 hash = 0;

	gw = (काष्ठा batadv_bla_backbone_gw *)data;
	hash = jhash(&gw->orig, माप(gw->orig), hash);
	hash = jhash(&gw->vid, माप(gw->vid), hash);

	वापस hash % size;
पूर्ण

/**
 * batadv_compare_backbone_gw() - compare address and vid of two backbone gws
 * @node: list node of the first entry to compare
 * @data2: poपूर्णांकer to the second backbone gateway
 *
 * Return: true अगर the backbones have the same data, false otherwise
 */
अटल bool batadv_compare_backbone_gw(स्थिर काष्ठा hlist_node *node,
				       स्थिर व्योम *data2)
अणु
	स्थिर व्योम *data1 = container_of(node, काष्ठा batadv_bla_backbone_gw,
					 hash_entry);
	स्थिर काष्ठा batadv_bla_backbone_gw *gw1 = data1;
	स्थिर काष्ठा batadv_bla_backbone_gw *gw2 = data2;

	अगर (!batadv_compare_eth(gw1->orig, gw2->orig))
		वापस false;

	अगर (gw1->vid != gw2->vid)
		वापस false;

	वापस true;
पूर्ण

/**
 * batadv_compare_claim() - compare address and vid of two claims
 * @node: list node of the first entry to compare
 * @data2: poपूर्णांकer to the second claims
 *
 * Return: true अगर the claim have the same data, 0 otherwise
 */
अटल bool batadv_compare_claim(स्थिर काष्ठा hlist_node *node,
				 स्थिर व्योम *data2)
अणु
	स्थिर व्योम *data1 = container_of(node, काष्ठा batadv_bla_claim,
					 hash_entry);
	स्थिर काष्ठा batadv_bla_claim *cl1 = data1;
	स्थिर काष्ठा batadv_bla_claim *cl2 = data2;

	अगर (!batadv_compare_eth(cl1->addr, cl2->addr))
		वापस false;

	अगर (cl1->vid != cl2->vid)
		वापस false;

	वापस true;
पूर्ण

/**
 * batadv_backbone_gw_release() - release backbone gw from lists and queue क्रम
 *  मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the backbone gw
 */
अटल व्योम batadv_backbone_gw_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;

	backbone_gw = container_of(ref, काष्ठा batadv_bla_backbone_gw,
				   refcount);

	kमुक्त_rcu(backbone_gw, rcu);
पूर्ण

/**
 * batadv_backbone_gw_put() - decrement the backbone gw refcounter and possibly
 *  release it
 * @backbone_gw: backbone gateway to be मुक्त'd
 */
अटल व्योम batadv_backbone_gw_put(काष्ठा batadv_bla_backbone_gw *backbone_gw)
अणु
	kref_put(&backbone_gw->refcount, batadv_backbone_gw_release);
पूर्ण

/**
 * batadv_claim_release() - release claim from lists and queue क्रम मुक्त after
 *  rcu grace period
 * @ref: kref poपूर्णांकer of the claim
 */
अटल व्योम batadv_claim_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_bla_claim *claim;
	काष्ठा batadv_bla_backbone_gw *old_backbone_gw;

	claim = container_of(ref, काष्ठा batadv_bla_claim, refcount);

	spin_lock_bh(&claim->backbone_lock);
	old_backbone_gw = claim->backbone_gw;
	claim->backbone_gw = शून्य;
	spin_unlock_bh(&claim->backbone_lock);

	spin_lock_bh(&old_backbone_gw->crc_lock);
	old_backbone_gw->crc ^= crc16(0, claim->addr, ETH_ALEN);
	spin_unlock_bh(&old_backbone_gw->crc_lock);

	batadv_backbone_gw_put(old_backbone_gw);

	kमुक्त_rcu(claim, rcu);
पूर्ण

/**
 * batadv_claim_put() - decrement the claim refcounter and possibly release it
 * @claim: claim to be मुक्त'd
 */
अटल व्योम batadv_claim_put(काष्ठा batadv_bla_claim *claim)
अणु
	kref_put(&claim->refcount, batadv_claim_release);
पूर्ण

/**
 * batadv_claim_hash_find() - looks क्रम a claim in the claim hash
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @data: search data (may be local/अटल data)
 *
 * Return: claim अगर found or शून्य otherwise.
 */
अटल काष्ठा batadv_bla_claim *
batadv_claim_hash_find(काष्ठा batadv_priv *bat_priv,
		       काष्ठा batadv_bla_claim *data)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->bla.claim_hash;
	काष्ठा hlist_head *head;
	काष्ठा batadv_bla_claim *claim;
	काष्ठा batadv_bla_claim *claim_पंचांगp = शून्य;
	पूर्णांक index;

	अगर (!hash)
		वापस शून्य;

	index = batadv_choose_claim(data, hash->size);
	head = &hash->table[index];

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(claim, head, hash_entry) अणु
		अगर (!batadv_compare_claim(&claim->hash_entry, data))
			जारी;

		अगर (!kref_get_unless_zero(&claim->refcount))
			जारी;

		claim_पंचांगp = claim;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस claim_पंचांगp;
पूर्ण

/**
 * batadv_backbone_hash_find() - looks क्रम a backbone gateway in the hash
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the address of the originator
 * @vid: the VLAN ID
 *
 * Return: backbone gateway अगर found or शून्य otherwise
 */
अटल काष्ठा batadv_bla_backbone_gw *
batadv_backbone_hash_find(काष्ठा batadv_priv *bat_priv, u8 *addr,
			  अचिन्हित लघु vid)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->bla.backbone_hash;
	काष्ठा hlist_head *head;
	काष्ठा batadv_bla_backbone_gw search_entry, *backbone_gw;
	काष्ठा batadv_bla_backbone_gw *backbone_gw_पंचांगp = शून्य;
	पूर्णांक index;

	अगर (!hash)
		वापस शून्य;

	ether_addr_copy(search_entry.orig, addr);
	search_entry.vid = vid;

	index = batadv_choose_backbone_gw(&search_entry, hash->size);
	head = &hash->table[index];

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(backbone_gw, head, hash_entry) अणु
		अगर (!batadv_compare_backbone_gw(&backbone_gw->hash_entry,
						&search_entry))
			जारी;

		अगर (!kref_get_unless_zero(&backbone_gw->refcount))
			जारी;

		backbone_gw_पंचांगp = backbone_gw;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस backbone_gw_पंचांगp;
पूर्ण

/**
 * batadv_bla_del_backbone_claims() - delete all claims क्रम a backbone
 * @backbone_gw: backbone gateway where the claims should be हटाओd
 */
अटल व्योम
batadv_bla_del_backbone_claims(काष्ठा batadv_bla_backbone_gw *backbone_gw)
अणु
	काष्ठा batadv_hashtable *hash;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा hlist_head *head;
	काष्ठा batadv_bla_claim *claim;
	पूर्णांक i;
	spinlock_t *list_lock;	/* protects ग_लिखो access to the hash lists */

	hash = backbone_gw->bat_priv->bla.claim_hash;
	अगर (!hash)
		वापस;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(claim, node_पंचांगp,
					  head, hash_entry) अणु
			अगर (claim->backbone_gw != backbone_gw)
				जारी;

			batadv_claim_put(claim);
			hlist_del_rcu(&claim->hash_entry);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण

	/* all claims gone, initialize CRC */
	spin_lock_bh(&backbone_gw->crc_lock);
	backbone_gw->crc = BATADV_BLA_CRC_INIT;
	spin_unlock_bh(&backbone_gw->crc_lock);
पूर्ण

/**
 * batadv_bla_send_claim() - sends a claim frame according to the provided info
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @mac: the mac address to be announced within the claim
 * @vid: the VLAN ID
 * @claimtype: the type of the claim (CLAIM, UNCLAIM, ANNOUNCE, ...)
 */
अटल व्योम batadv_bla_send_claim(काष्ठा batadv_priv *bat_priv, u8 *mac,
				  अचिन्हित लघु vid, पूर्णांक claimtype)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr *ethhdr;
	काष्ठा batadv_hard_अगरace *primary_अगर;
	काष्ठा net_device *soft_अगरace;
	u8 *hw_src;
	काष्ठा batadv_bla_claim_dst local_claim_dest;
	__be32 zeroip = 0;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		वापस;

	स_नकल(&local_claim_dest, &bat_priv->bla.claim_dest,
	       माप(local_claim_dest));
	local_claim_dest.type = claimtype;

	soft_अगरace = primary_अगर->soft_अगरace;

	skb = arp_create(ARPOP_REPLY, ETH_P_ARP,
			 /* IP DST: 0.0.0.0 */
			 zeroip,
			 primary_अगर->soft_अगरace,
			 /* IP SRC: 0.0.0.0 */
			 zeroip,
			 /* Ethernet DST: Broadcast */
			 शून्य,
			 /* Ethernet SRC/HW SRC:  originator mac */
			 primary_अगर->net_dev->dev_addr,
			 /* HW DST: FF:43:05:XX:YY:YY
			  * with XX   = claim type
			  * and YY:YY = group id
			  */
			 (u8 *)&local_claim_dest);

	अगर (!skb)
		जाओ out;

	ethhdr = (काष्ठा ethhdr *)skb->data;
	hw_src = (u8 *)ethhdr + ETH_HLEN + माप(काष्ठा arphdr);

	/* now we pretend that the client would have sent this ... */
	चयन (claimtype) अणु
	हाल BATADV_CLAIM_TYPE_CLAIM:
		/* normal claim frame
		 * set Ethernet SRC to the clients mac
		 */
		ether_addr_copy(ethhdr->h_source, mac);
		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): CLAIM %pM on vid %d\n", __func__, mac,
			   batadv_prपूर्णांक_vid(vid));
		अवरोध;
	हाल BATADV_CLAIM_TYPE_UNCLAIM:
		/* unclaim frame
		 * set HW SRC to the clients mac
		 */
		ether_addr_copy(hw_src, mac);
		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): UNCLAIM %pM on vid %d\n", __func__, mac,
			   batadv_prपूर्णांक_vid(vid));
		अवरोध;
	हाल BATADV_CLAIM_TYPE_ANNOUNCE:
		/* announcement frame
		 * set HW SRC to the special mac containg the crc
		 */
		ether_addr_copy(hw_src, mac);
		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): ANNOUNCE of %pM on vid %d\n", __func__,
			   ethhdr->h_source, batadv_prपूर्णांक_vid(vid));
		अवरोध;
	हाल BATADV_CLAIM_TYPE_REQUEST:
		/* request frame
		 * set HW SRC and header destination to the receiving backbone
		 * gws mac
		 */
		ether_addr_copy(hw_src, mac);
		ether_addr_copy(ethhdr->h_dest, mac);
		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): REQUEST of %pM to %pM on vid %d\n", __func__,
			   ethhdr->h_source, ethhdr->h_dest,
			   batadv_prपूर्णांक_vid(vid));
		अवरोध;
	हाल BATADV_CLAIM_TYPE_LOOPDETECT:
		ether_addr_copy(ethhdr->h_source, mac);
		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): LOOPDETECT of %pM to %pM on vid %d\n",
			   __func__, ethhdr->h_source, ethhdr->h_dest,
			   batadv_prपूर्णांक_vid(vid));

		अवरोध;
	पूर्ण

	अगर (vid & BATADV_VLAN_HAS_TAG) अणु
		skb = vlan_insert_tag(skb, htons(ETH_P_8021Q),
				      vid & VLAN_VID_MASK);
		अगर (!skb)
			जाओ out;
	पूर्ण

	skb_reset_mac_header(skb);
	skb->protocol = eth_type_trans(skb, soft_अगरace);
	batadv_inc_counter(bat_priv, BATADV_CNT_RX);
	batadv_add_counter(bat_priv, BATADV_CNT_RX_BYTES,
			   skb->len + ETH_HLEN);

	netअगर_rx_any_context(skb);
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
पूर्ण

/**
 * batadv_bla_loopdetect_report() - worker क्रम reporting the loop
 * @work: work queue item
 *
 * Throws an uevent, as the loopdetect check function can't करो that itself
 * since the kernel may sleep जबतक throwing uevents.
 */
अटल व्योम batadv_bla_loopdetect_report(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	काष्ठा batadv_priv *bat_priv;
	अक्षर vid_str[6] = अणु '\0' पूर्ण;

	backbone_gw = container_of(work, काष्ठा batadv_bla_backbone_gw,
				   report_work);
	bat_priv = backbone_gw->bat_priv;

	batadv_info(bat_priv->soft_अगरace,
		    "Possible loop on VLAN %d detected which can't be handled by BLA - please check your network setup!\n",
		    batadv_prपूर्णांक_vid(backbone_gw->vid));
	snम_लिखो(vid_str, माप(vid_str), "%d",
		 batadv_prपूर्णांक_vid(backbone_gw->vid));
	vid_str[माप(vid_str) - 1] = 0;

	batadv_throw_uevent(bat_priv, BATADV_UEV_BLA, BATADV_UEV_LOOPDETECT,
			    vid_str);

	batadv_backbone_gw_put(backbone_gw);
पूर्ण

/**
 * batadv_bla_get_backbone_gw() - finds or creates a backbone gateway
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the mac address of the originator
 * @vid: the VLAN ID
 * @own_backbone: set अगर the requested backbone is local
 *
 * Return: the (possibly created) backbone gateway or शून्य on error
 */
अटल काष्ठा batadv_bla_backbone_gw *
batadv_bla_get_backbone_gw(काष्ठा batadv_priv *bat_priv, u8 *orig,
			   अचिन्हित लघु vid, bool own_backbone)
अणु
	काष्ठा batadv_bla_backbone_gw *entry;
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक hash_added;

	entry = batadv_backbone_hash_find(bat_priv, orig, vid);

	अगर (entry)
		वापस entry;

	batadv_dbg(BATADV_DBG_BLA, bat_priv,
		   "%s(): not found (%pM, %d), creating new entry\n", __func__,
		   orig, batadv_prपूर्णांक_vid(vid));

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस शून्य;

	entry->vid = vid;
	entry->lastसमय = jअगरfies;
	entry->crc = BATADV_BLA_CRC_INIT;
	entry->bat_priv = bat_priv;
	spin_lock_init(&entry->crc_lock);
	atomic_set(&entry->request_sent, 0);
	atomic_set(&entry->रुको_periods, 0);
	ether_addr_copy(entry->orig, orig);
	INIT_WORK(&entry->report_work, batadv_bla_loopdetect_report);
	kref_init(&entry->refcount);

	kref_get(&entry->refcount);
	hash_added = batadv_hash_add(bat_priv->bla.backbone_hash,
				     batadv_compare_backbone_gw,
				     batadv_choose_backbone_gw, entry,
				     &entry->hash_entry);

	अगर (unlikely(hash_added != 0)) अणु
		/* hash failed, मुक्त the काष्ठाure */
		kमुक्त(entry);
		वापस शून्य;
	पूर्ण

	/* this is a gateway now, हटाओ any TT entry on this VLAN */
	orig_node = batadv_orig_hash_find(bat_priv, orig);
	अगर (orig_node) अणु
		batadv_tt_global_del_orig(bat_priv, orig_node, vid,
					  "became a backbone gateway");
		batadv_orig_node_put(orig_node);
	पूर्ण

	अगर (own_backbone) अणु
		batadv_bla_send_announce(bat_priv, entry);

		/* this will be decreased in the worker thपढ़ो */
		atomic_inc(&entry->request_sent);
		atomic_set(&entry->रुको_periods, BATADV_BLA_WAIT_PERIODS);
		atomic_inc(&bat_priv->bla.num_requests);
	पूर्ण

	वापस entry;
पूर्ण

/**
 * batadv_bla_update_own_backbone_gw() - updates the own backbone gw क्रम a VLAN
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: the selected primary पूर्णांकerface
 * @vid: VLAN identअगरier
 *
 * update or add the own backbone gw to make sure we announce
 * where we receive other backbone gws
 */
अटल व्योम
batadv_bla_update_own_backbone_gw(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_hard_अगरace *primary_अगर,
				  अचिन्हित लघु vid)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;

	backbone_gw = batadv_bla_get_backbone_gw(bat_priv,
						 primary_अगर->net_dev->dev_addr,
						 vid, true);
	अगर (unlikely(!backbone_gw))
		वापस;

	backbone_gw->lastसमय = jअगरfies;
	batadv_backbone_gw_put(backbone_gw);
पूर्ण

/**
 * batadv_bla_answer_request() - answer a bla request by sending own claims
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: पूर्णांकerface where the request came on
 * @vid: the vid where the request came on
 *
 * Repeat all of our own claims, and finally send an ANNOUNCE frame
 * to allow the requester another check अगर the CRC is correct now.
 */
अटल व्योम batadv_bla_answer_request(काष्ठा batadv_priv *bat_priv,
				      काष्ठा batadv_hard_अगरace *primary_अगर,
				      अचिन्हित लघु vid)
अणु
	काष्ठा hlist_head *head;
	काष्ठा batadv_hashtable *hash;
	काष्ठा batadv_bla_claim *claim;
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	पूर्णांक i;

	batadv_dbg(BATADV_DBG_BLA, bat_priv,
		   "%s(): received a claim request, send all of our own claims again\n",
		   __func__);

	backbone_gw = batadv_backbone_hash_find(bat_priv,
						primary_अगर->net_dev->dev_addr,
						vid);
	अगर (!backbone_gw)
		वापस;

	hash = bat_priv->bla.claim_hash;
	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(claim, head, hash_entry) अणु
			/* only own claims are पूर्णांकeresting */
			अगर (claim->backbone_gw != backbone_gw)
				जारी;

			batadv_bla_send_claim(bat_priv, claim->addr, claim->vid,
					      BATADV_CLAIM_TYPE_CLAIM);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/* finally, send an announcement frame */
	batadv_bla_send_announce(bat_priv, backbone_gw);
	batadv_backbone_gw_put(backbone_gw);
पूर्ण

/**
 * batadv_bla_send_request() - send a request to repeat claims
 * @backbone_gw: the backbone gateway from whom we are out of sync
 *
 * When the crc is wrong, ask the backbone gateway क्रम a full table update.
 * After the request, it will repeat all of his own claims and finally
 * send an announcement claim with which we can check again.
 */
अटल व्योम batadv_bla_send_request(काष्ठा batadv_bla_backbone_gw *backbone_gw)
अणु
	/* first, हटाओ all old entries */
	batadv_bla_del_backbone_claims(backbone_gw);

	batadv_dbg(BATADV_DBG_BLA, backbone_gw->bat_priv,
		   "Sending REQUEST to %pM\n", backbone_gw->orig);

	/* send request */
	batadv_bla_send_claim(backbone_gw->bat_priv, backbone_gw->orig,
			      backbone_gw->vid, BATADV_CLAIM_TYPE_REQUEST);

	/* no local broadcasts should be sent or received, क्रम now. */
	अगर (!atomic_पढ़ो(&backbone_gw->request_sent)) अणु
		atomic_inc(&backbone_gw->bat_priv->bla.num_requests);
		atomic_set(&backbone_gw->request_sent, 1);
	पूर्ण
पूर्ण

/**
 * batadv_bla_send_announce() - Send an announcement frame
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @backbone_gw: our backbone gateway which should be announced
 */
अटल व्योम batadv_bla_send_announce(काष्ठा batadv_priv *bat_priv,
				     काष्ठा batadv_bla_backbone_gw *backbone_gw)
अणु
	u8 mac[ETH_ALEN];
	__be16 crc;

	स_नकल(mac, batadv_announce_mac, 4);
	spin_lock_bh(&backbone_gw->crc_lock);
	crc = htons(backbone_gw->crc);
	spin_unlock_bh(&backbone_gw->crc_lock);
	स_नकल(&mac[4], &crc, 2);

	batadv_bla_send_claim(bat_priv, mac, backbone_gw->vid,
			      BATADV_CLAIM_TYPE_ANNOUNCE);
पूर्ण

/**
 * batadv_bla_add_claim() - Adds a claim in the claim hash
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @mac: the mac address of the claim
 * @vid: the VLAN ID of the frame
 * @backbone_gw: the backbone gateway which claims it
 */
अटल व्योम batadv_bla_add_claim(काष्ठा batadv_priv *bat_priv,
				 स्थिर u8 *mac, स्थिर अचिन्हित लघु vid,
				 काष्ठा batadv_bla_backbone_gw *backbone_gw)
अणु
	काष्ठा batadv_bla_backbone_gw *old_backbone_gw;
	काष्ठा batadv_bla_claim *claim;
	काष्ठा batadv_bla_claim search_claim;
	bool हटाओ_crc = false;
	पूर्णांक hash_added;

	ether_addr_copy(search_claim.addr, mac);
	search_claim.vid = vid;
	claim = batadv_claim_hash_find(bat_priv, &search_claim);

	/* create a new claim entry अगर it करोes not exist yet. */
	अगर (!claim) अणु
		claim = kzalloc(माप(*claim), GFP_ATOMIC);
		अगर (!claim)
			वापस;

		ether_addr_copy(claim->addr, mac);
		spin_lock_init(&claim->backbone_lock);
		claim->vid = vid;
		claim->lastसमय = jअगरfies;
		kref_get(&backbone_gw->refcount);
		claim->backbone_gw = backbone_gw;
		kref_init(&claim->refcount);

		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): adding new entry %pM, vid %d to hash ...\n",
			   __func__, mac, batadv_prपूर्णांक_vid(vid));

		kref_get(&claim->refcount);
		hash_added = batadv_hash_add(bat_priv->bla.claim_hash,
					     batadv_compare_claim,
					     batadv_choose_claim, claim,
					     &claim->hash_entry);

		अगर (unlikely(hash_added != 0)) अणु
			/* only local changes happened. */
			kमुक्त(claim);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		claim->lastसमय = jअगरfies;
		अगर (claim->backbone_gw == backbone_gw)
			/* no need to रेजिस्टर a new backbone */
			जाओ claim_मुक्त_ref;

		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): changing ownership for %pM, vid %d to gw %pM\n",
			   __func__, mac, batadv_prपूर्णांक_vid(vid),
			   backbone_gw->orig);

		हटाओ_crc = true;
	पूर्ण

	/* replace backbone_gw atomically and adjust reference counters */
	spin_lock_bh(&claim->backbone_lock);
	old_backbone_gw = claim->backbone_gw;
	kref_get(&backbone_gw->refcount);
	claim->backbone_gw = backbone_gw;
	spin_unlock_bh(&claim->backbone_lock);

	अगर (हटाओ_crc) अणु
		/* हटाओ claim address from old backbone_gw */
		spin_lock_bh(&old_backbone_gw->crc_lock);
		old_backbone_gw->crc ^= crc16(0, claim->addr, ETH_ALEN);
		spin_unlock_bh(&old_backbone_gw->crc_lock);
	पूर्ण

	batadv_backbone_gw_put(old_backbone_gw);

	/* add claim address to new backbone_gw */
	spin_lock_bh(&backbone_gw->crc_lock);
	backbone_gw->crc ^= crc16(0, claim->addr, ETH_ALEN);
	spin_unlock_bh(&backbone_gw->crc_lock);
	backbone_gw->lastसमय = jअगरfies;

claim_मुक्त_ref:
	batadv_claim_put(claim);
पूर्ण

/**
 * batadv_bla_claim_get_backbone_gw() - Get valid reference क्रम backbone_gw of
 *  claim
 * @claim: claim whose backbone_gw should be वापसed
 *
 * Return: valid reference to claim::backbone_gw
 */
अटल काष्ठा batadv_bla_backbone_gw *
batadv_bla_claim_get_backbone_gw(काष्ठा batadv_bla_claim *claim)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;

	spin_lock_bh(&claim->backbone_lock);
	backbone_gw = claim->backbone_gw;
	kref_get(&backbone_gw->refcount);
	spin_unlock_bh(&claim->backbone_lock);

	वापस backbone_gw;
पूर्ण

/**
 * batadv_bla_del_claim() - delete a claim from the claim hash
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @mac: mac address of the claim to be हटाओd
 * @vid: VLAN id क्रम the claim to be हटाओd
 */
अटल व्योम batadv_bla_del_claim(काष्ठा batadv_priv *bat_priv,
				 स्थिर u8 *mac, स्थिर अचिन्हित लघु vid)
अणु
	काष्ठा batadv_bla_claim search_claim, *claim;
	काष्ठा batadv_bla_claim *claim_हटाओd_entry;
	काष्ठा hlist_node *claim_हटाओd_node;

	ether_addr_copy(search_claim.addr, mac);
	search_claim.vid = vid;
	claim = batadv_claim_hash_find(bat_priv, &search_claim);
	अगर (!claim)
		वापस;

	batadv_dbg(BATADV_DBG_BLA, bat_priv, "%s(): %pM, vid %d\n", __func__,
		   mac, batadv_prपूर्णांक_vid(vid));

	claim_हटाओd_node = batadv_hash_हटाओ(bat_priv->bla.claim_hash,
						batadv_compare_claim,
						batadv_choose_claim, claim);
	अगर (!claim_हटाओd_node)
		जाओ मुक्त_claim;

	/* reference from the hash is gone */
	claim_हटाओd_entry = hlist_entry(claim_हटाओd_node,
					  काष्ठा batadv_bla_claim, hash_entry);
	batadv_claim_put(claim_हटाओd_entry);

मुक्त_claim:
	/* करोn't need the reference from hash_find() anymore */
	batadv_claim_put(claim);
पूर्ण

/**
 * batadv_handle_announce() - check क्रम ANNOUNCE frame
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @an_addr: announcement mac address (ARP Sender HW address)
 * @backbone_addr: originator address of the sender (Ethernet source MAC)
 * @vid: the VLAN ID of the frame
 *
 * Return: true अगर handled
 */
अटल bool batadv_handle_announce(काष्ठा batadv_priv *bat_priv, u8 *an_addr,
				   u8 *backbone_addr, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	u16 backbone_crc, crc;

	अगर (स_भेद(an_addr, batadv_announce_mac, 4) != 0)
		वापस false;

	backbone_gw = batadv_bla_get_backbone_gw(bat_priv, backbone_addr, vid,
						 false);

	अगर (unlikely(!backbone_gw))
		वापस true;

	/* handle as ANNOUNCE frame */
	backbone_gw->lastसमय = jअगरfies;
	crc = ntohs(*((__क्रमce __be16 *)(&an_addr[4])));

	batadv_dbg(BATADV_DBG_BLA, bat_priv,
		   "%s(): ANNOUNCE vid %d (sent by %pM)... CRC = %#.4x\n",
		   __func__, batadv_prपूर्णांक_vid(vid), backbone_gw->orig, crc);

	spin_lock_bh(&backbone_gw->crc_lock);
	backbone_crc = backbone_gw->crc;
	spin_unlock_bh(&backbone_gw->crc_lock);

	अगर (backbone_crc != crc) अणु
		batadv_dbg(BATADV_DBG_BLA, backbone_gw->bat_priv,
			   "%s(): CRC FAILED for %pM/%d (my = %#.4x, sent = %#.4x)\n",
			   __func__, backbone_gw->orig,
			   batadv_prपूर्णांक_vid(backbone_gw->vid),
			   backbone_crc, crc);

		batadv_bla_send_request(backbone_gw);
	पूर्ण अन्यथा अणु
		/* अगर we have sent a request and the crc was OK,
		 * we can allow traffic again.
		 */
		अगर (atomic_पढ़ो(&backbone_gw->request_sent)) अणु
			atomic_dec(&backbone_gw->bat_priv->bla.num_requests);
			atomic_set(&backbone_gw->request_sent, 0);
		पूर्ण
	पूर्ण

	batadv_backbone_gw_put(backbone_gw);
	वापस true;
पूर्ण

/**
 * batadv_handle_request() - check क्रम REQUEST frame
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: the primary hard पूर्णांकerface of this baपंचांगan soft पूर्णांकerface
 * @backbone_addr: backbone address to be requested (ARP sender HW MAC)
 * @ethhdr: ethernet header of a packet
 * @vid: the VLAN ID of the frame
 *
 * Return: true अगर handled
 */
अटल bool batadv_handle_request(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_hard_अगरace *primary_अगर,
				  u8 *backbone_addr, काष्ठा ethhdr *ethhdr,
				  अचिन्हित लघु vid)
अणु
	/* check क्रम REQUEST frame */
	अगर (!batadv_compare_eth(backbone_addr, ethhdr->h_dest))
		वापस false;

	/* sanity check, this should not happen on a normal चयन,
	 * we ignore it in this हाल.
	 */
	अगर (!batadv_compare_eth(ethhdr->h_dest, primary_अगर->net_dev->dev_addr))
		वापस true;

	batadv_dbg(BATADV_DBG_BLA, bat_priv,
		   "%s(): REQUEST vid %d (sent by %pM)...\n",
		   __func__, batadv_prपूर्णांक_vid(vid), ethhdr->h_source);

	batadv_bla_answer_request(bat_priv, primary_अगर, vid);
	वापस true;
पूर्ण

/**
 * batadv_handle_unclaim() - check क्रम UNCLAIM frame
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: the primary hard पूर्णांकerface of this baपंचांगan soft पूर्णांकerface
 * @backbone_addr: originator address of the backbone (Ethernet source)
 * @claim_addr: Client to be unclaimed (ARP sender HW MAC)
 * @vid: the VLAN ID of the frame
 *
 * Return: true अगर handled
 */
अटल bool batadv_handle_unclaim(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_hard_अगरace *primary_अगर,
				  u8 *backbone_addr, u8 *claim_addr,
				  अचिन्हित लघु vid)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;

	/* unclaim in any हाल अगर it is our own */
	अगर (primary_अगर && batadv_compare_eth(backbone_addr,
					     primary_अगर->net_dev->dev_addr))
		batadv_bla_send_claim(bat_priv, claim_addr, vid,
				      BATADV_CLAIM_TYPE_UNCLAIM);

	backbone_gw = batadv_backbone_hash_find(bat_priv, backbone_addr, vid);

	अगर (!backbone_gw)
		वापस true;

	/* this must be an UNCLAIM frame */
	batadv_dbg(BATADV_DBG_BLA, bat_priv,
		   "%s(): UNCLAIM %pM on vid %d (sent by %pM)...\n", __func__,
		   claim_addr, batadv_prपूर्णांक_vid(vid), backbone_gw->orig);

	batadv_bla_del_claim(bat_priv, claim_addr, vid);
	batadv_backbone_gw_put(backbone_gw);
	वापस true;
पूर्ण

/**
 * batadv_handle_claim() - check क्रम CLAIM frame
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: the primary hard पूर्णांकerface of this baपंचांगan soft पूर्णांकerface
 * @backbone_addr: originator address of the backbone (Ethernet Source)
 * @claim_addr: client mac address to be claimed (ARP sender HW MAC)
 * @vid: the VLAN ID of the frame
 *
 * Return: true अगर handled
 */
अटल bool batadv_handle_claim(काष्ठा batadv_priv *bat_priv,
				काष्ठा batadv_hard_अगरace *primary_अगर,
				u8 *backbone_addr, u8 *claim_addr,
				अचिन्हित लघु vid)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;

	/* रेजिस्टर the gateway अगर not yet available, and add the claim. */

	backbone_gw = batadv_bla_get_backbone_gw(bat_priv, backbone_addr, vid,
						 false);

	अगर (unlikely(!backbone_gw))
		वापस true;

	/* this must be a CLAIM frame */
	batadv_bla_add_claim(bat_priv, claim_addr, vid, backbone_gw);
	अगर (batadv_compare_eth(backbone_addr, primary_अगर->net_dev->dev_addr))
		batadv_bla_send_claim(bat_priv, claim_addr, vid,
				      BATADV_CLAIM_TYPE_CLAIM);

	/* TODO: we could call something like tt_local_del() here. */

	batadv_backbone_gw_put(backbone_gw);
	वापस true;
पूर्ण

/**
 * batadv_check_claim_group() - check क्रम claim group membership
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: the primary पूर्णांकerface of this baपंचांगan पूर्णांकerface
 * @hw_src: the Hardware source in the ARP Header
 * @hw_dst: the Hardware destination in the ARP Header
 * @ethhdr: poपूर्णांकer to the Ethernet header of the claim frame
 *
 * checks अगर it is a claim packet and अगर it's on the same group.
 * This function also applies the group ID of the sender
 * अगर it is in the same mesh.
 *
 * Return:
 *	2  - अगर it is a claim packet and on the same group
 *	1  - अगर is a claim packet from another group
 *	0  - अगर it is not a claim packet
 */
अटल पूर्णांक batadv_check_claim_group(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_hard_अगरace *primary_अगर,
				    u8 *hw_src, u8 *hw_dst,
				    काष्ठा ethhdr *ethhdr)
अणु
	u8 *backbone_addr;
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_bla_claim_dst *bla_dst, *bla_dst_own;

	bla_dst = (काष्ठा batadv_bla_claim_dst *)hw_dst;
	bla_dst_own = &bat_priv->bla.claim_dest;

	/* अगर announcement packet, use the source,
	 * otherwise assume it is in the hw_src
	 */
	चयन (bla_dst->type) अणु
	हाल BATADV_CLAIM_TYPE_CLAIM:
		backbone_addr = hw_src;
		अवरोध;
	हाल BATADV_CLAIM_TYPE_REQUEST:
	हाल BATADV_CLAIM_TYPE_ANNOUNCE:
	हाल BATADV_CLAIM_TYPE_UNCLAIM:
		backbone_addr = ethhdr->h_source;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/* करोn't accept claim frames from ourselves */
	अगर (batadv_compare_eth(backbone_addr, primary_अगर->net_dev->dev_addr))
		वापस 0;

	/* अगर its alपढ़ोy the same group, it is fine. */
	अगर (bla_dst->group == bla_dst_own->group)
		वापस 2;

	/* lets see अगर this originator is in our mesh */
	orig_node = batadv_orig_hash_find(bat_priv, backbone_addr);

	/* करोnt accept claims from gateways which are not in
	 * the same mesh or group.
	 */
	अगर (!orig_node)
		वापस 1;

	/* अगर our mesh मित्रs mac is bigger, use it क्रम ourselves. */
	अगर (ntohs(bla_dst->group) > ntohs(bla_dst_own->group)) अणु
		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "taking other backbones claim group: %#.4x\n",
			   ntohs(bla_dst->group));
		bla_dst_own->group = bla_dst->group;
	पूर्ण

	batadv_orig_node_put(orig_node);

	वापस 2;
पूर्ण

/**
 * batadv_bla_process_claim() - Check अगर this is a claim frame, and process it
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: the primary hard पूर्णांकerface of this baपंचांगan soft पूर्णांकerface
 * @skb: the frame to be checked
 *
 * Return: true अगर it was a claim frame, otherwise वापस false to
 * tell the callee that it can use the frame on its own.
 */
अटल bool batadv_bla_process_claim(काष्ठा batadv_priv *bat_priv,
				     काष्ठा batadv_hard_अगरace *primary_अगर,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_bla_claim_dst *bla_dst, *bla_dst_own;
	u8 *hw_src, *hw_dst;
	काष्ठा vlan_hdr *vhdr, vhdr_buf;
	काष्ठा ethhdr *ethhdr;
	काष्ठा arphdr *arphdr;
	अचिन्हित लघु vid;
	पूर्णांक vlan_depth = 0;
	__be16 proto;
	पूर्णांक headlen;
	पूर्णांक ret;

	vid = batadv_get_vid(skb, 0);
	ethhdr = eth_hdr(skb);

	proto = ethhdr->h_proto;
	headlen = ETH_HLEN;
	अगर (vid & BATADV_VLAN_HAS_TAG) अणु
		/* Traverse the VLAN/Ethertypes.
		 *
		 * At this poपूर्णांक it is known that the first protocol is a VLAN
		 * header, so start checking at the encapsulated protocol.
		 *
		 * The depth of the VLAN headers is recorded to drop BLA claim
		 * frames encapsulated पूर्णांकo multiple VLAN headers (QinQ).
		 */
		करो अणु
			vhdr = skb_header_poपूर्णांकer(skb, headlen, VLAN_HLEN,
						  &vhdr_buf);
			अगर (!vhdr)
				वापस false;

			proto = vhdr->h_vlan_encapsulated_proto;
			headlen += VLAN_HLEN;
			vlan_depth++;
		पूर्ण जबतक (proto == htons(ETH_P_8021Q));
	पूर्ण

	अगर (proto != htons(ETH_P_ARP))
		वापस false; /* not a claim frame */

	/* this must be a ARP frame. check अगर it is a claim. */

	अगर (unlikely(!pskb_may_pull(skb, headlen + arp_hdr_len(skb->dev))))
		वापस false;

	/* pskb_may_pull() may have modअगरied the poपूर्णांकers, get ethhdr again */
	ethhdr = eth_hdr(skb);
	arphdr = (काष्ठा arphdr *)((u8 *)ethhdr + headlen);

	/* Check whether the ARP frame carries a valid
	 * IP inक्रमmation
	 */
	अगर (arphdr->ar_hrd != htons(ARPHRD_ETHER))
		वापस false;
	अगर (arphdr->ar_pro != htons(ETH_P_IP))
		वापस false;
	अगर (arphdr->ar_hln != ETH_ALEN)
		वापस false;
	अगर (arphdr->ar_pln != 4)
		वापस false;

	hw_src = (u8 *)arphdr + माप(काष्ठा arphdr);
	hw_dst = hw_src + ETH_ALEN + 4;
	bla_dst = (काष्ठा batadv_bla_claim_dst *)hw_dst;
	bla_dst_own = &bat_priv->bla.claim_dest;

	/* check अगर it is a claim frame in general */
	अगर (स_भेद(bla_dst->magic, bla_dst_own->magic,
		   माप(bla_dst->magic)) != 0)
		वापस false;

	/* check अगर there is a claim frame encapsulated deeper in (QinQ) and
	 * drop that, as this is not supported by BLA but should also not be
	 * sent via the mesh.
	 */
	अगर (vlan_depth > 1)
		वापस true;

	/* Let the loopdetect frames on the mesh in any हाल. */
	अगर (bla_dst->type == BATADV_CLAIM_TYPE_LOOPDETECT)
		वापस false;

	/* check अगर it is a claim frame. */
	ret = batadv_check_claim_group(bat_priv, primary_अगर, hw_src, hw_dst,
				       ethhdr);
	अगर (ret == 1)
		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): received a claim frame from another group. From: %pM on vid %d ...(hw_src %pM, hw_dst %pM)\n",
			   __func__, ethhdr->h_source, batadv_prपूर्णांक_vid(vid),
			   hw_src, hw_dst);

	अगर (ret < 2)
		वापस !!ret;

	/* become a backbone gw ourselves on this vlan अगर not happened yet */
	batadv_bla_update_own_backbone_gw(bat_priv, primary_अगर, vid);

	/* check क्रम the dअगरferent types of claim frames ... */
	चयन (bla_dst->type) अणु
	हाल BATADV_CLAIM_TYPE_CLAIM:
		अगर (batadv_handle_claim(bat_priv, primary_अगर, hw_src,
					ethhdr->h_source, vid))
			वापस true;
		अवरोध;
	हाल BATADV_CLAIM_TYPE_UNCLAIM:
		अगर (batadv_handle_unclaim(bat_priv, primary_अगर,
					  ethhdr->h_source, hw_src, vid))
			वापस true;
		अवरोध;

	हाल BATADV_CLAIM_TYPE_ANNOUNCE:
		अगर (batadv_handle_announce(bat_priv, hw_src, ethhdr->h_source,
					   vid))
			वापस true;
		अवरोध;
	हाल BATADV_CLAIM_TYPE_REQUEST:
		अगर (batadv_handle_request(bat_priv, primary_अगर, hw_src, ethhdr,
					  vid))
			वापस true;
		अवरोध;
	पूर्ण

	batadv_dbg(BATADV_DBG_BLA, bat_priv,
		   "%s(): ERROR - this looks like a claim frame, but is useless. eth src %pM on vid %d ...(hw_src %pM, hw_dst %pM)\n",
		   __func__, ethhdr->h_source, batadv_prपूर्णांक_vid(vid), hw_src,
		   hw_dst);
	वापस true;
पूर्ण

/**
 * batadv_bla_purge_backbone_gw() - Remove backbone gateways after a समयout or
 *  immediately
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @now: whether the whole hash shall be wiped now
 *
 * Check when we last heard from other nodes, and हटाओ them in हाल of
 * a समय out, or clean all backbone gws अगर now is set.
 */
अटल व्योम batadv_bla_purge_backbone_gw(काष्ठा batadv_priv *bat_priv, पूर्णांक now)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा hlist_head *head;
	काष्ठा batadv_hashtable *hash;
	spinlock_t *list_lock;	/* protects ग_लिखो access to the hash lists */
	पूर्णांक i;

	hash = bat_priv->bla.backbone_hash;
	अगर (!hash)
		वापस;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(backbone_gw, node_पंचांगp,
					  head, hash_entry) अणु
			अगर (now)
				जाओ purge_now;
			अगर (!batadv_has_समयd_out(backbone_gw->lastसमय,
						  BATADV_BLA_BACKBONE_TIMEOUT))
				जारी;

			batadv_dbg(BATADV_DBG_BLA, backbone_gw->bat_priv,
				   "%s(): backbone gw %pM timed out\n",
				   __func__, backbone_gw->orig);

purge_now:
			/* करोn't रुको क्रम the pending request anymore */
			अगर (atomic_पढ़ो(&backbone_gw->request_sent))
				atomic_dec(&bat_priv->bla.num_requests);

			batadv_bla_del_backbone_claims(backbone_gw);

			hlist_del_rcu(&backbone_gw->hash_entry);
			batadv_backbone_gw_put(backbone_gw);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण
पूर्ण

/**
 * batadv_bla_purge_claims() - Remove claims after a समयout or immediately
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: the selected primary पूर्णांकerface, may be शून्य अगर now is set
 * @now: whether the whole hash shall be wiped now
 *
 * Check when we heard last समय from our own claims, and हटाओ them in हाल of
 * a समय out, or clean all claims अगर now is set
 */
अटल व्योम batadv_bla_purge_claims(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_hard_अगरace *primary_अगर,
				    पूर्णांक now)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	काष्ठा batadv_bla_claim *claim;
	काष्ठा hlist_head *head;
	काष्ठा batadv_hashtable *hash;
	पूर्णांक i;

	hash = bat_priv->bla.claim_hash;
	अगर (!hash)
		वापस;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(claim, head, hash_entry) अणु
			backbone_gw = batadv_bla_claim_get_backbone_gw(claim);
			अगर (now)
				जाओ purge_now;

			अगर (!batadv_compare_eth(backbone_gw->orig,
						primary_अगर->net_dev->dev_addr))
				जाओ skip;

			अगर (!batadv_has_समयd_out(claim->lastसमय,
						  BATADV_BLA_CLAIM_TIMEOUT))
				जाओ skip;

			batadv_dbg(BATADV_DBG_BLA, bat_priv,
				   "%s(): timed out.\n", __func__);

purge_now:
			batadv_dbg(BATADV_DBG_BLA, bat_priv,
				   "%s(): %pM, vid %d\n", __func__,
				   claim->addr, claim->vid);

			batadv_handle_unclaim(bat_priv, primary_अगर,
					      backbone_gw->orig,
					      claim->addr, claim->vid);
skip:
			batadv_backbone_gw_put(backbone_gw);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/**
 * batadv_bla_update_orig_address() - Update the backbone gateways when the own
 *  originator address changes
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: the new selected primary_अगर
 * @oldअगर: the old primary पूर्णांकerface, may be शून्य
 */
व्योम batadv_bla_update_orig_address(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_hard_अगरace *primary_अगर,
				    काष्ठा batadv_hard_अगरace *oldअगर)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	काष्ठा hlist_head *head;
	काष्ठा batadv_hashtable *hash;
	__be16 group;
	पूर्णांक i;

	/* reset bridge loop aव्योमance group id */
	group = htons(crc16(0, primary_अगर->net_dev->dev_addr, ETH_ALEN));
	bat_priv->bla.claim_dest.group = group;

	/* purge everything when bridge loop aव्योमance is turned off */
	अगर (!atomic_पढ़ो(&bat_priv->bridge_loop_aव्योमance))
		oldअगर = शून्य;

	अगर (!oldअगर) अणु
		batadv_bla_purge_claims(bat_priv, शून्य, 1);
		batadv_bla_purge_backbone_gw(bat_priv, 1);
		वापस;
	पूर्ण

	hash = bat_priv->bla.backbone_hash;
	अगर (!hash)
		वापस;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(backbone_gw, head, hash_entry) अणु
			/* own orig still holds the old value. */
			अगर (!batadv_compare_eth(backbone_gw->orig,
						oldअगर->net_dev->dev_addr))
				जारी;

			ether_addr_copy(backbone_gw->orig,
					primary_अगर->net_dev->dev_addr);
			/* send an announce frame so others will ask क्रम our
			 * claims and update their tables.
			 */
			batadv_bla_send_announce(bat_priv, backbone_gw);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/**
 * batadv_bla_send_loopdetect() - send a loopdetect frame
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @backbone_gw: the backbone gateway क्रम which a loop should be detected
 *
 * To detect loops that the bridge loop aव्योमance can't handle, send a loop
 * detection packet on the backbone. Unlike other BLA frames, this frame will
 * be allowed on the mesh by other nodes. If it is received on the mesh, this
 * indicates that there is a loop.
 */
अटल व्योम
batadv_bla_send_loopdetect(काष्ठा batadv_priv *bat_priv,
			   काष्ठा batadv_bla_backbone_gw *backbone_gw)
अणु
	batadv_dbg(BATADV_DBG_BLA, bat_priv, "Send loopdetect frame for vid %d\n",
		   backbone_gw->vid);
	batadv_bla_send_claim(bat_priv, bat_priv->bla.loopdetect_addr,
			      backbone_gw->vid, BATADV_CLAIM_TYPE_LOOPDETECT);
पूर्ण

/**
 * batadv_bla_status_update() - purge bla पूर्णांकerfaces अगर necessary
 * @net_dev: the soft पूर्णांकerface net device
 */
व्योम batadv_bla_status_update(काष्ठा net_device *net_dev)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(net_dev);
	काष्ठा batadv_hard_अगरace *primary_अगर;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		वापस;

	/* this function alपढ़ोy purges everything when bla is disabled,
	 * so just call that one.
	 */
	batadv_bla_update_orig_address(bat_priv, primary_अगर, primary_अगर);
	batadv_hardअगर_put(primary_अगर);
पूर्ण

/**
 * batadv_bla_periodic_work() - perक्रमms periodic bla work
 * @work: kernel work काष्ठा
 *
 * periodic work to करो:
 *  * purge काष्ठाures when they are too old
 *  * send announcements
 */
अटल व्योम batadv_bla_periodic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_priv *bat_priv;
	काष्ठा batadv_priv_bla *priv_bla;
	काष्ठा hlist_head *head;
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	काष्ठा batadv_hashtable *hash;
	काष्ठा batadv_hard_अगरace *primary_अगर;
	bool send_loopdetect = false;
	पूर्णांक i;

	delayed_work = to_delayed_work(work);
	priv_bla = container_of(delayed_work, काष्ठा batadv_priv_bla, work);
	bat_priv = container_of(priv_bla, काष्ठा batadv_priv, bla);
	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ out;

	batadv_bla_purge_claims(bat_priv, primary_अगर, 0);
	batadv_bla_purge_backbone_gw(bat_priv, 0);

	अगर (!atomic_पढ़ो(&bat_priv->bridge_loop_aव्योमance))
		जाओ out;

	अगर (atomic_dec_and_test(&bat_priv->bla.loopdetect_next)) अणु
		/* set a new अक्रमom mac address क्रम the next bridge loop
		 * detection frames. Set the locally administered bit to aव्योम
		 * collisions with users mac addresses.
		 */
		eth_अक्रमom_addr(bat_priv->bla.loopdetect_addr);
		bat_priv->bla.loopdetect_addr[0] = 0xba;
		bat_priv->bla.loopdetect_addr[1] = 0xbe;
		bat_priv->bla.loopdetect_lastसमय = jअगरfies;
		atomic_set(&bat_priv->bla.loopdetect_next,
			   BATADV_BLA_LOOPDETECT_PERIODS);

		/* mark क्रम sending loop detect on all VLANs */
		send_loopdetect = true;
	पूर्ण

	hash = bat_priv->bla.backbone_hash;
	अगर (!hash)
		जाओ out;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(backbone_gw, head, hash_entry) अणु
			अगर (!batadv_compare_eth(backbone_gw->orig,
						primary_अगर->net_dev->dev_addr))
				जारी;

			backbone_gw->lastसमय = jअगरfies;

			batadv_bla_send_announce(bat_priv, backbone_gw);
			अगर (send_loopdetect)
				batadv_bla_send_loopdetect(bat_priv,
							   backbone_gw);

			/* request_sent is only set after creation to aव्योम
			 * problems when we are not yet known as backbone gw
			 * in the backbone.
			 *
			 * We can reset this now after we रुकोed some periods
			 * to give bridge क्रमward delays and bla group क्रमming
			 * some grace समय.
			 */

			अगर (atomic_पढ़ो(&backbone_gw->request_sent) == 0)
				जारी;

			अगर (!atomic_dec_and_test(&backbone_gw->रुको_periods))
				जारी;

			atomic_dec(&backbone_gw->bat_priv->bla.num_requests);
			atomic_set(&backbone_gw->request_sent, 0);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);

	queue_delayed_work(batadv_event_workqueue, &bat_priv->bla.work,
			   msecs_to_jअगरfies(BATADV_BLA_PERIOD_LENGTH));
पूर्ण

/* The hash क्रम claim and backbone hash receive the same key because they
 * are getting initialized by hash_new with the same key. Reinitializing
 * them with to dअगरferent keys to allow nested locking without generating
 * lockdep warnings
 */
अटल काष्ठा lock_class_key batadv_claim_hash_lock_class_key;
अटल काष्ठा lock_class_key batadv_backbone_hash_lock_class_key;

/**
 * batadv_bla_init() - initialize all bla काष्ठाures
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 on success, < 0 on error.
 */
पूर्णांक batadv_bla_init(काष्ठा batadv_priv *bat_priv)
अणु
	पूर्णांक i;
	u8 claim_dest[ETH_ALEN] = अणु0xff, 0x43, 0x05, 0x00, 0x00, 0x00पूर्ण;
	काष्ठा batadv_hard_अगरace *primary_अगर;
	u16 crc;
	अचिन्हित दीर्घ entryसमय;

	spin_lock_init(&bat_priv->bla.bcast_duplist_lock);

	batadv_dbg(BATADV_DBG_BLA, bat_priv, "bla hash registering\n");

	/* setting claim destination address */
	स_नकल(&bat_priv->bla.claim_dest.magic, claim_dest, 3);
	bat_priv->bla.claim_dest.type = 0;
	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (primary_अगर) अणु
		crc = crc16(0, primary_अगर->net_dev->dev_addr, ETH_ALEN);
		bat_priv->bla.claim_dest.group = htons(crc);
		batadv_hardअगर_put(primary_अगर);
	पूर्ण अन्यथा अणु
		bat_priv->bla.claim_dest.group = 0; /* will be set later */
	पूर्ण

	/* initialize the duplicate list */
	entryसमय = jअगरfies - msecs_to_jअगरfies(BATADV_DUPLIST_TIMEOUT);
	क्रम (i = 0; i < BATADV_DUPLIST_SIZE; i++)
		bat_priv->bla.bcast_duplist[i].entryसमय = entryसमय;
	bat_priv->bla.bcast_duplist_curr = 0;

	atomic_set(&bat_priv->bla.loopdetect_next,
		   BATADV_BLA_LOOPDETECT_PERIODS);

	अगर (bat_priv->bla.claim_hash)
		वापस 0;

	bat_priv->bla.claim_hash = batadv_hash_new(128);
	bat_priv->bla.backbone_hash = batadv_hash_new(32);

	अगर (!bat_priv->bla.claim_hash || !bat_priv->bla.backbone_hash)
		वापस -ENOMEM;

	batadv_hash_set_lock_class(bat_priv->bla.claim_hash,
				   &batadv_claim_hash_lock_class_key);
	batadv_hash_set_lock_class(bat_priv->bla.backbone_hash,
				   &batadv_backbone_hash_lock_class_key);

	batadv_dbg(BATADV_DBG_BLA, bat_priv, "bla hashes initialized\n");

	INIT_DELAYED_WORK(&bat_priv->bla.work, batadv_bla_periodic_work);

	queue_delayed_work(batadv_event_workqueue, &bat_priv->bla.work,
			   msecs_to_jअगरfies(BATADV_BLA_PERIOD_LENGTH));
	वापस 0;
पूर्ण

/**
 * batadv_bla_check_duplist() - Check अगर a frame is in the broadcast dup.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: contains the multicast packet to be checked
 * @payload_ptr: poपूर्णांकer to position inside the head buffer of the skb
 *  marking the start of the data to be CRC'ed
 * @orig: originator mac address, शून्य अगर unknown
 *
 * Check अगर it is on our broadcast list. Another gateway might have sent the
 * same packet because it is connected to the same backbone, so we have to
 * हटाओ this duplicate.
 *
 * This is perक्रमmed by checking the CRC, which will tell us
 * with a good chance that it is the same packet. If it is furthermore
 * sent by another host, drop it. We allow equal packets from
 * the same host however as this might be पूर्णांकended.
 *
 * Return: true अगर a packet is in the duplicate list, false otherwise.
 */
अटल bool batadv_bla_check_duplist(काष्ठा batadv_priv *bat_priv,
				     काष्ठा sk_buff *skb, u8 *payload_ptr,
				     स्थिर u8 *orig)
अणु
	काष्ठा batadv_bcast_duplist_entry *entry;
	bool ret = false;
	पूर्णांक i, curr;
	__be32 crc;

	/* calculate the crc ... */
	crc = batadv_skb_crc32(skb, payload_ptr);

	spin_lock_bh(&bat_priv->bla.bcast_duplist_lock);

	क्रम (i = 0; i < BATADV_DUPLIST_SIZE; i++) अणु
		curr = (bat_priv->bla.bcast_duplist_curr + i);
		curr %= BATADV_DUPLIST_SIZE;
		entry = &bat_priv->bla.bcast_duplist[curr];

		/* we can stop searching अगर the entry is too old ;
		 * later entries will be even older
		 */
		अगर (batadv_has_समयd_out(entry->entryसमय,
					 BATADV_DUPLIST_TIMEOUT))
			अवरोध;

		अगर (entry->crc != crc)
			जारी;

		/* are the originators both known and not anonymous? */
		अगर (orig && !is_zero_ether_addr(orig) &&
		    !is_zero_ether_addr(entry->orig)) अणु
			/* If known, check अगर the new frame came from
			 * the same originator:
			 * We are safe to take identical frames from the
			 * same orig, अगर known, as multiplications in
			 * the mesh are detected via the (orig, seqno) pair.
			 * So we can be a bit more liberal here and allow
			 * identical frames from the same orig which the source
			 * host might have sent multiple बार on purpose.
			 */
			अगर (batadv_compare_eth(entry->orig, orig))
				जारी;
		पूर्ण

		/* this entry seems to match: same crc, not too old,
		 * and from another gw. thereक्रमe वापस true to क्रमbid it.
		 */
		ret = true;
		जाओ out;
	पूर्ण
	/* not found, add a new entry (overग_लिखो the oldest entry)
	 * and allow it, its the first occurrence.
	 */
	curr = (bat_priv->bla.bcast_duplist_curr + BATADV_DUPLIST_SIZE - 1);
	curr %= BATADV_DUPLIST_SIZE;
	entry = &bat_priv->bla.bcast_duplist[curr];
	entry->crc = crc;
	entry->entryसमय = jअगरfies;

	/* known originator */
	अगर (orig)
		ether_addr_copy(entry->orig, orig);
	/* anonymous originator */
	अन्यथा
		eth_zero_addr(entry->orig);

	bat_priv->bla.bcast_duplist_curr = curr;

out:
	spin_unlock_bh(&bat_priv->bla.bcast_duplist_lock);

	वापस ret;
पूर्ण

/**
 * batadv_bla_check_ucast_duplist() - Check अगर a frame is in the broadcast dup.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: contains the multicast packet to be checked, decapsulated from a
 *  unicast_packet
 *
 * Check अगर it is on our broadcast list. Another gateway might have sent the
 * same packet because it is connected to the same backbone, so we have to
 * हटाओ this duplicate.
 *
 * Return: true अगर a packet is in the duplicate list, false otherwise.
 */
अटल bool batadv_bla_check_ucast_duplist(काष्ठा batadv_priv *bat_priv,
					   काष्ठा sk_buff *skb)
अणु
	वापस batadv_bla_check_duplist(bat_priv, skb, (u8 *)skb->data, शून्य);
पूर्ण

/**
 * batadv_bla_check_bcast_duplist() - Check अगर a frame is in the broadcast dup.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: contains the bcast_packet to be checked
 *
 * Check अगर it is on our broadcast list. Another gateway might have sent the
 * same packet because it is connected to the same backbone, so we have to
 * हटाओ this duplicate.
 *
 * Return: true अगर a packet is in the duplicate list, false otherwise.
 */
bool batadv_bla_check_bcast_duplist(काष्ठा batadv_priv *bat_priv,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_bcast_packet *bcast_packet;
	u8 *payload_ptr;

	bcast_packet = (काष्ठा batadv_bcast_packet *)skb->data;
	payload_ptr = (u8 *)(bcast_packet + 1);

	वापस batadv_bla_check_duplist(bat_priv, skb, payload_ptr,
					bcast_packet->orig);
पूर्ण

/**
 * batadv_bla_is_backbone_gw_orig() - Check अगर the originator is a gateway क्रम
 *  the VLAN identअगरied by vid.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: originator mac address
 * @vid: VLAN identअगरier
 *
 * Return: true अगर orig is a backbone क्रम this vid, false otherwise.
 */
bool batadv_bla_is_backbone_gw_orig(काष्ठा batadv_priv *bat_priv, u8 *orig,
				    अचिन्हित लघु vid)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->bla.backbone_hash;
	काष्ठा hlist_head *head;
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	पूर्णांक i;

	अगर (!atomic_पढ़ो(&bat_priv->bridge_loop_aव्योमance))
		वापस false;

	अगर (!hash)
		वापस false;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(backbone_gw, head, hash_entry) अणु
			अगर (batadv_compare_eth(backbone_gw->orig, orig) &&
			    backbone_gw->vid == vid) अणु
				rcu_पढ़ो_unlock();
				वापस true;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	वापस false;
पूर्ण

/**
 * batadv_bla_is_backbone_gw() - check अगर originator is a backbone gw क्रम a VLAN
 * @skb: the frame to be checked
 * @orig_node: the orig_node of the frame
 * @hdr_size: maximum length of the frame
 *
 * Return: true अगर the orig_node is also a gateway on the soft पूर्णांकerface,
 * otherwise it वापसs false.
 */
bool batadv_bla_is_backbone_gw(काष्ठा sk_buff *skb,
			       काष्ठा batadv_orig_node *orig_node, पूर्णांक hdr_size)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	अचिन्हित लघु vid;

	अगर (!atomic_पढ़ो(&orig_node->bat_priv->bridge_loop_aव्योमance))
		वापस false;

	/* first, find out the vid. */
	अगर (!pskb_may_pull(skb, hdr_size + ETH_HLEN))
		वापस false;

	vid = batadv_get_vid(skb, hdr_size);

	/* see अगर this originator is a backbone gw क्रम this VLAN */
	backbone_gw = batadv_backbone_hash_find(orig_node->bat_priv,
						orig_node->orig, vid);
	अगर (!backbone_gw)
		वापस false;

	batadv_backbone_gw_put(backbone_gw);
	वापस true;
पूर्ण

/**
 * batadv_bla_मुक्त() - मुक्त all bla काष्ठाures
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * क्रम softपूर्णांकerface मुक्त or module unload
 */
व्योम batadv_bla_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर;

	cancel_delayed_work_sync(&bat_priv->bla.work);
	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);

	अगर (bat_priv->bla.claim_hash) अणु
		batadv_bla_purge_claims(bat_priv, primary_अगर, 1);
		batadv_hash_destroy(bat_priv->bla.claim_hash);
		bat_priv->bla.claim_hash = शून्य;
	पूर्ण
	अगर (bat_priv->bla.backbone_hash) अणु
		batadv_bla_purge_backbone_gw(bat_priv, 1);
		batadv_hash_destroy(bat_priv->bla.backbone_hash);
		bat_priv->bla.backbone_hash = शून्य;
	पूर्ण
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
पूर्ण

/**
 * batadv_bla_loopdetect_check() - check and handle a detected loop
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the packet to check
 * @primary_अगर: पूर्णांकerface where the request came on
 * @vid: the VLAN ID of the frame
 *
 * Checks अगर this packet is a loop detect frame which has been sent by us,
 * throws an uevent and logs the event अगर that is the हाल.
 *
 * Return: true अगर it is a loop detect frame which is to be dropped, false
 * otherwise.
 */
अटल bool
batadv_bla_loopdetect_check(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			    काष्ठा batadv_hard_अगरace *primary_अगर,
			    अचिन्हित लघु vid)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	काष्ठा ethhdr *ethhdr;
	bool ret;

	ethhdr = eth_hdr(skb);

	/* Only check क्रम the MAC address and skip more checks here क्रम
	 * perक्रमmance reasons - this function is on the hotpath, after all.
	 */
	अगर (!batadv_compare_eth(ethhdr->h_source,
				bat_priv->bla.loopdetect_addr))
		वापस false;

	/* If the packet came too late, करोn't क्रमward it on the mesh
	 * but करोn't consider that as loop. It might be a coincidence.
	 */
	अगर (batadv_has_समयd_out(bat_priv->bla.loopdetect_lastसमय,
				 BATADV_BLA_LOOPDETECT_TIMEOUT))
		वापस true;

	backbone_gw = batadv_bla_get_backbone_gw(bat_priv,
						 primary_अगर->net_dev->dev_addr,
						 vid, true);
	अगर (unlikely(!backbone_gw))
		वापस true;

	ret = queue_work(batadv_event_workqueue, &backbone_gw->report_work);

	/* backbone_gw is unreferenced in the report work function
	 * अगर queue_work() call was successful
	 */
	अगर (!ret)
		batadv_backbone_gw_put(backbone_gw);

	वापस true;
पूर्ण

/**
 * batadv_bla_rx() - check packets coming from the mesh.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the frame to be checked
 * @vid: the VLAN ID of the frame
 * @packet_type: the baपंचांगan packet type this frame came in
 *
 * batadv_bla_rx aव्योमance checks अगर:
 *  * we have to race क्रम a claim
 *  * अगर the frame is allowed on the LAN
 *
 * In these हालs, the skb is further handled by this function
 *
 * Return: true अगर handled, otherwise it वापसs false and the caller shall
 * further process the skb.
 */
bool batadv_bla_rx(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		   अचिन्हित लघु vid, पूर्णांक packet_type)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	काष्ठा ethhdr *ethhdr;
	काष्ठा batadv_bla_claim search_claim, *claim = शून्य;
	काष्ठा batadv_hard_अगरace *primary_अगर;
	bool own_claim;
	bool ret;

	ethhdr = eth_hdr(skb);

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ handled;

	अगर (!atomic_पढ़ो(&bat_priv->bridge_loop_aव्योमance))
		जाओ allow;

	अगर (batadv_bla_loopdetect_check(bat_priv, skb, primary_अगर, vid))
		जाओ handled;

	अगर (unlikely(atomic_पढ़ो(&bat_priv->bla.num_requests)))
		/* करोn't allow multicast packets जबतक requests are in flight */
		अगर (is_multicast_ether_addr(ethhdr->h_dest))
			/* Both broadcast flooding or multicast-via-unicasts
			 * delivery might send to multiple backbone gateways
			 * sharing the same LAN and thereक्रमe need to coordinate
			 * which backbone gateway क्रमwards पूर्णांकo the LAN,
			 * by claiming the payload source address.
			 *
			 * Broadcast flooding and multicast-via-unicasts
			 * delivery use the following two baपंचांगan packet types.
			 * Note: explicitly exclude BATADV_UNICAST_4ADDR,
			 * as the DHCP gateway feature will send explicitly
			 * to only one BLA gateway, so the claiming process
			 * should be aव्योमed there.
			 */
			अगर (packet_type == BATADV_BCAST ||
			    packet_type == BATADV_UNICAST)
				जाओ handled;

	/* potential duplicates from क्रमeign BLA backbone gateways via
	 * multicast-in-unicast packets
	 */
	अगर (is_multicast_ether_addr(ethhdr->h_dest) &&
	    packet_type == BATADV_UNICAST &&
	    batadv_bla_check_ucast_duplist(bat_priv, skb))
		जाओ handled;

	ether_addr_copy(search_claim.addr, ethhdr->h_source);
	search_claim.vid = vid;
	claim = batadv_claim_hash_find(bat_priv, &search_claim);

	अगर (!claim) अणु
		/* possible optimization: race क्रम a claim */
		/* No claim exists yet, claim it क्रम us!
		 */

		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "%s(): Unclaimed MAC %pM found. Claim it. Local: %s\n",
			   __func__, ethhdr->h_source,
			   batadv_is_my_client(bat_priv,
					       ethhdr->h_source, vid) ?
			   "yes" : "no");
		batadv_handle_claim(bat_priv, primary_अगर,
				    primary_अगर->net_dev->dev_addr,
				    ethhdr->h_source, vid);
		जाओ allow;
	पूर्ण

	/* अगर it is our own claim ... */
	backbone_gw = batadv_bla_claim_get_backbone_gw(claim);
	own_claim = batadv_compare_eth(backbone_gw->orig,
				       primary_अगर->net_dev->dev_addr);
	batadv_backbone_gw_put(backbone_gw);

	अगर (own_claim) अणु
		/* ... allow it in any हाल */
		claim->lastसमय = jअगरfies;
		जाओ allow;
	पूर्ण

	/* अगर it is a multicast ... */
	अगर (is_multicast_ether_addr(ethhdr->h_dest) &&
	    (packet_type == BATADV_BCAST || packet_type == BATADV_UNICAST)) अणु
		/* ... drop it. the responsible gateway is in अक्षरge.
		 *
		 * We need to check packet type because with the gateway
		 * feature, broadcasts (like DHCP requests) may be sent
		 * using a unicast 4 address packet type. See comment above.
		 */
		जाओ handled;
	पूर्ण अन्यथा अणु
		/* seems the client considers us as its best gateway.
		 * send a claim and update the claim table
		 * immediately.
		 */
		batadv_handle_claim(bat_priv, primary_अगर,
				    primary_अगर->net_dev->dev_addr,
				    ethhdr->h_source, vid);
		जाओ allow;
	पूर्ण
allow:
	batadv_bla_update_own_backbone_gw(bat_priv, primary_अगर, vid);
	ret = false;
	जाओ out;

handled:
	kमुक्त_skb(skb);
	ret = true;

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (claim)
		batadv_claim_put(claim);
	वापस ret;
पूर्ण

/**
 * batadv_bla_tx() - check packets going पूर्णांकo the mesh
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the frame to be checked
 * @vid: the VLAN ID of the frame
 *
 * batadv_bla_tx checks अगर:
 *  * a claim was received which has to be processed
 *  * the frame is allowed on the mesh
 *
 * in these हालs, the skb is further handled by this function.
 *
 * This call might पुनः_स्मृतिate skb data.
 *
 * Return: true अगर handled, otherwise it वापसs false and the caller shall
 * further process the skb.
 */
bool batadv_bla_tx(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		   अचिन्हित लघु vid)
अणु
	काष्ठा ethhdr *ethhdr;
	काष्ठा batadv_bla_claim search_claim, *claim = शून्य;
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	काष्ठा batadv_hard_अगरace *primary_अगर;
	bool client_roamed;
	bool ret = false;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ out;

	अगर (!atomic_पढ़ो(&bat_priv->bridge_loop_aव्योमance))
		जाओ allow;

	अगर (batadv_bla_process_claim(bat_priv, primary_अगर, skb))
		जाओ handled;

	ethhdr = eth_hdr(skb);

	अगर (unlikely(atomic_पढ़ो(&bat_priv->bla.num_requests)))
		/* करोn't allow broadcasts जबतक requests are in flight */
		अगर (is_multicast_ether_addr(ethhdr->h_dest))
			जाओ handled;

	ether_addr_copy(search_claim.addr, ethhdr->h_source);
	search_claim.vid = vid;

	claim = batadv_claim_hash_find(bat_priv, &search_claim);

	/* अगर no claim exists, allow it. */
	अगर (!claim)
		जाओ allow;

	/* check अगर we are responsible. */
	backbone_gw = batadv_bla_claim_get_backbone_gw(claim);
	client_roamed = batadv_compare_eth(backbone_gw->orig,
					   primary_अगर->net_dev->dev_addr);
	batadv_backbone_gw_put(backbone_gw);

	अगर (client_roamed) अणु
		/* अगर yes, the client has roamed and we have
		 * to unclaim it.
		 */
		अगर (batadv_has_समयd_out(claim->lastसमय, 100)) अणु
			/* only unclaim अगर the last claim entry is
			 * older than 100 ms to make sure we really
			 * have a roaming client here.
			 */
			batadv_dbg(BATADV_DBG_BLA, bat_priv, "%s(): Roaming client %pM detected. Unclaim it.\n",
				   __func__, ethhdr->h_source);
			batadv_handle_unclaim(bat_priv, primary_अगर,
					      primary_अगर->net_dev->dev_addr,
					      ethhdr->h_source, vid);
			जाओ allow;
		पूर्ण अन्यथा अणु
			batadv_dbg(BATADV_DBG_BLA, bat_priv, "%s(): Race for claim %pM detected. Drop packet.\n",
				   __func__, ethhdr->h_source);
			जाओ handled;
		पूर्ण
	पूर्ण

	/* check अगर it is a multicast/broadcast frame */
	अगर (is_multicast_ether_addr(ethhdr->h_dest)) अणु
		/* drop it. the responsible gateway has क्रमwarded it पूर्णांकo
		 * the backbone network.
		 */
		जाओ handled;
	पूर्ण अन्यथा अणु
		/* we must allow it. at least अगर we are
		 * responsible क्रम the DESTINATION.
		 */
		जाओ allow;
	पूर्ण
allow:
	batadv_bla_update_own_backbone_gw(bat_priv, primary_अगर, vid);
	ret = false;
	जाओ out;
handled:
	ret = true;
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (claim)
		batadv_claim_put(claim);
	वापस ret;
पूर्ण

/**
 * batadv_bla_claim_dump_entry() - dump one entry of the claim table
 * to a netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @primary_अगर: primary पूर्णांकerface
 * @claim: entry to dump
 *
 * Return: 0 or error code.
 */
अटल पूर्णांक
batadv_bla_claim_dump_entry(काष्ठा sk_buff *msg, u32 portid,
			    काष्ठा netlink_callback *cb,
			    काष्ठा batadv_hard_अगरace *primary_अगर,
			    काष्ठा batadv_bla_claim *claim)
अणु
	u8 *primary_addr = primary_अगर->net_dev->dev_addr;
	u16 backbone_crc;
	bool is_own;
	व्योम *hdr;
	पूर्णांक ret = -EINVAL;

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_BLA_CLAIM);
	अगर (!hdr) अणु
		ret = -ENOBUFS;
		जाओ out;
	पूर्ण

	genl_dump_check_consistent(cb, hdr);

	is_own = batadv_compare_eth(claim->backbone_gw->orig,
				    primary_addr);

	spin_lock_bh(&claim->backbone_gw->crc_lock);
	backbone_crc = claim->backbone_gw->crc;
	spin_unlock_bh(&claim->backbone_gw->crc_lock);

	अगर (is_own)
		अगर (nla_put_flag(msg, BATADV_ATTR_BLA_OWN)) अणु
			genlmsg_cancel(msg, hdr);
			जाओ out;
		पूर्ण

	अगर (nla_put(msg, BATADV_ATTR_BLA_ADDRESS, ETH_ALEN, claim->addr) ||
	    nla_put_u16(msg, BATADV_ATTR_BLA_VID, claim->vid) ||
	    nla_put(msg, BATADV_ATTR_BLA_BACKBONE, ETH_ALEN,
		    claim->backbone_gw->orig) ||
	    nla_put_u16(msg, BATADV_ATTR_BLA_CRC,
			backbone_crc)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	genlmsg_end(msg, hdr);
	ret = 0;

out:
	वापस ret;
पूर्ण

/**
 * batadv_bla_claim_dump_bucket() - dump one bucket of the claim table
 * to a netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @primary_अगर: primary पूर्णांकerface
 * @hash: hash to dump
 * @bucket: bucket index to dump
 * @idx_skip: How many entries to skip
 *
 * Return: always 0.
 */
अटल पूर्णांक
batadv_bla_claim_dump_bucket(काष्ठा sk_buff *msg, u32 portid,
			     काष्ठा netlink_callback *cb,
			     काष्ठा batadv_hard_अगरace *primary_अगर,
			     काष्ठा batadv_hashtable *hash, अचिन्हित पूर्णांक bucket,
			     पूर्णांक *idx_skip)
अणु
	काष्ठा batadv_bla_claim *claim;
	पूर्णांक idx = 0;
	पूर्णांक ret = 0;

	spin_lock_bh(&hash->list_locks[bucket]);
	cb->seq = atomic_पढ़ो(&hash->generation) << 1 | 1;

	hlist_क्रम_each_entry(claim, &hash->table[bucket], hash_entry) अणु
		अगर (idx++ < *idx_skip)
			जारी;

		ret = batadv_bla_claim_dump_entry(msg, portid, cb,
						  primary_अगर, claim);
		अगर (ret) अणु
			*idx_skip = idx - 1;
			जाओ unlock;
		पूर्ण
	पूर्ण

	*idx_skip = 0;
unlock:
	spin_unlock_bh(&hash->list_locks[bucket]);
	वापस ret;
पूर्ण

/**
 * batadv_bla_claim_dump() - dump claim table to a netlink socket
 * @msg: buffer क्रम the message
 * @cb: callback काष्ठाure containing arguments
 *
 * Return: message length.
 */
पूर्णांक batadv_bla_claim_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा batadv_hashtable *hash;
	काष्ठा batadv_priv *bat_priv;
	पूर्णांक bucket = cb->args[0];
	पूर्णांक idx = cb->args[1];
	पूर्णांक अगरindex;
	पूर्णांक ret = 0;

	अगरindex = batadv_netlink_get_अगरindex(cb->nlh,
					     BATADV_ATTR_MESH_IFINDEX);
	अगर (!अगरindex)
		वापस -EINVAL;

	soft_अगरace = dev_get_by_index(net, अगरindex);
	अगर (!soft_अगरace || !batadv_softअगर_is_valid(soft_अगरace)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	bat_priv = netdev_priv(soft_अगरace);
	hash = bat_priv->bla.claim_hash;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर || primary_अगर->अगर_status != BATADV_IF_ACTIVE) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	जबतक (bucket < hash->size) अणु
		अगर (batadv_bla_claim_dump_bucket(msg, portid, cb, primary_अगर,
						 hash, bucket, &idx))
			अवरोध;
		bucket++;
	पूर्ण

	cb->args[0] = bucket;
	cb->args[1] = idx;

	ret = msg->len;

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);

	अगर (soft_अगरace)
		dev_put(soft_अगरace);

	वापस ret;
पूर्ण

/**
 * batadv_bla_backbone_dump_entry() - dump one entry of the backbone table to a
 *  netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @primary_अगर: primary पूर्णांकerface
 * @backbone_gw: entry to dump
 *
 * Return: 0 or error code.
 */
अटल पूर्णांक
batadv_bla_backbone_dump_entry(काष्ठा sk_buff *msg, u32 portid,
			       काष्ठा netlink_callback *cb,
			       काष्ठा batadv_hard_अगरace *primary_अगर,
			       काष्ठा batadv_bla_backbone_gw *backbone_gw)
अणु
	u8 *primary_addr = primary_अगर->net_dev->dev_addr;
	u16 backbone_crc;
	bool is_own;
	पूर्णांक msecs;
	व्योम *hdr;
	पूर्णांक ret = -EINVAL;

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_BLA_BACKBONE);
	अगर (!hdr) अणु
		ret = -ENOBUFS;
		जाओ out;
	पूर्ण

	genl_dump_check_consistent(cb, hdr);

	is_own = batadv_compare_eth(backbone_gw->orig, primary_addr);

	spin_lock_bh(&backbone_gw->crc_lock);
	backbone_crc = backbone_gw->crc;
	spin_unlock_bh(&backbone_gw->crc_lock);

	msecs = jअगरfies_to_msecs(jअगरfies - backbone_gw->lastसमय);

	अगर (is_own)
		अगर (nla_put_flag(msg, BATADV_ATTR_BLA_OWN)) अणु
			genlmsg_cancel(msg, hdr);
			जाओ out;
		पूर्ण

	अगर (nla_put(msg, BATADV_ATTR_BLA_BACKBONE, ETH_ALEN,
		    backbone_gw->orig) ||
	    nla_put_u16(msg, BATADV_ATTR_BLA_VID, backbone_gw->vid) ||
	    nla_put_u16(msg, BATADV_ATTR_BLA_CRC,
			backbone_crc) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS, msecs)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	genlmsg_end(msg, hdr);
	ret = 0;

out:
	वापस ret;
पूर्ण

/**
 * batadv_bla_backbone_dump_bucket() - dump one bucket of the backbone table to
 *  a netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @primary_अगर: primary पूर्णांकerface
 * @hash: hash to dump
 * @bucket: bucket index to dump
 * @idx_skip: How many entries to skip
 *
 * Return: always 0.
 */
अटल पूर्णांक
batadv_bla_backbone_dump_bucket(काष्ठा sk_buff *msg, u32 portid,
				काष्ठा netlink_callback *cb,
				काष्ठा batadv_hard_अगरace *primary_अगर,
				काष्ठा batadv_hashtable *hash,
				अचिन्हित पूर्णांक bucket, पूर्णांक *idx_skip)
अणु
	काष्ठा batadv_bla_backbone_gw *backbone_gw;
	पूर्णांक idx = 0;
	पूर्णांक ret = 0;

	spin_lock_bh(&hash->list_locks[bucket]);
	cb->seq = atomic_पढ़ो(&hash->generation) << 1 | 1;

	hlist_क्रम_each_entry(backbone_gw, &hash->table[bucket], hash_entry) अणु
		अगर (idx++ < *idx_skip)
			जारी;

		ret = batadv_bla_backbone_dump_entry(msg, portid, cb,
						     primary_अगर, backbone_gw);
		अगर (ret) अणु
			*idx_skip = idx - 1;
			जाओ unlock;
		पूर्ण
	पूर्ण

	*idx_skip = 0;
unlock:
	spin_unlock_bh(&hash->list_locks[bucket]);
	वापस ret;
पूर्ण

/**
 * batadv_bla_backbone_dump() - dump backbone table to a netlink socket
 * @msg: buffer क्रम the message
 * @cb: callback काष्ठाure containing arguments
 *
 * Return: message length.
 */
पूर्णांक batadv_bla_backbone_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा batadv_hashtable *hash;
	काष्ठा batadv_priv *bat_priv;
	पूर्णांक bucket = cb->args[0];
	पूर्णांक idx = cb->args[1];
	पूर्णांक अगरindex;
	पूर्णांक ret = 0;

	अगरindex = batadv_netlink_get_अगरindex(cb->nlh,
					     BATADV_ATTR_MESH_IFINDEX);
	अगर (!अगरindex)
		वापस -EINVAL;

	soft_अगरace = dev_get_by_index(net, अगरindex);
	अगर (!soft_अगरace || !batadv_softअगर_is_valid(soft_अगरace)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	bat_priv = netdev_priv(soft_अगरace);
	hash = bat_priv->bla.backbone_hash;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर || primary_अगर->अगर_status != BATADV_IF_ACTIVE) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	जबतक (bucket < hash->size) अणु
		अगर (batadv_bla_backbone_dump_bucket(msg, portid, cb, primary_अगर,
						    hash, bucket, &idx))
			अवरोध;
		bucket++;
	पूर्ण

	cb->args[0] = bucket;
	cb->args[1] = idx;

	ret = msg->len;

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);

	अगर (soft_अगरace)
		dev_put(soft_अगरace);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_BATMAN_ADV_DAT
/**
 * batadv_bla_check_claim() - check अगर address is claimed
 *
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: mac address of which the claim status is checked
 * @vid: the VLAN ID
 *
 * addr is checked अगर this address is claimed by the local device itself.
 *
 * Return: true अगर bla is disabled or the mac is claimed by the device,
 * false अगर the device addr is alपढ़ोy claimed by another gateway
 */
bool batadv_bla_check_claim(काष्ठा batadv_priv *bat_priv,
			    u8 *addr, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_bla_claim search_claim;
	काष्ठा batadv_bla_claim *claim = शून्य;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	bool ret = true;

	अगर (!atomic_पढ़ो(&bat_priv->bridge_loop_aव्योमance))
		वापस ret;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		वापस ret;

	/* First look अगर the mac address is claimed */
	ether_addr_copy(search_claim.addr, addr);
	search_claim.vid = vid;

	claim = batadv_claim_hash_find(bat_priv, &search_claim);

	/* If there is a claim and we are not owner of the claim,
	 * वापस false.
	 */
	अगर (claim) अणु
		अगर (!batadv_compare_eth(claim->backbone_gw->orig,
					primary_अगर->net_dev->dev_addr))
			ret = false;
		batadv_claim_put(claim);
	पूर्ण

	batadv_hardअगर_put(primary_अगर);
	वापस ret;
पूर्ण
#पूर्ण_अगर

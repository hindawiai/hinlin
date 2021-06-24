<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Antonio Quartulli
 */

#समावेश "distributed-arp-table.h"
#समावेश "main.h"

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/udp.h>
#समावेश <linux/workqueue.h>
#समावेश <net/arp.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bridge_loop_avoidance.h"
#समावेश "hard-interface.h"
#समावेश "hash.h"
#समावेश "log.h"
#समावेश "netlink.h"
#समावेश "originator.h"
#समावेश "send.h"
#समावेश "soft-interface.h"
#समावेश "translation-table.h"
#समावेश "tvlv.h"

क्रमागत batadv_bootpop अणु
	BATADV_BOOTREPLY	= 2,
पूर्ण;

क्रमागत batadv_boothtype अणु
	BATADV_HTYPE_ETHERNET	= 1,
पूर्ण;

क्रमागत batadv_dhcpoptioncode अणु
	BATADV_DHCP_OPT_PAD		= 0,
	BATADV_DHCP_OPT_MSG_TYPE	= 53,
	BATADV_DHCP_OPT_END		= 255,
पूर्ण;

क्रमागत batadv_dhcptype अणु
	BATADV_DHCPACK		= 5,
पूर्ण;

/* अणु 99, 130, 83, 99 पूर्ण */
#घोषणा BATADV_DHCP_MAGIC 1669485411

काष्ठा batadv_dhcp_packet अणु
	__u8 op;
	__u8 htype;
	__u8 hlen;
	__u8 hops;
	__be32 xid;
	__be16 secs;
	__be16 flags;
	__be32 ciaddr;
	__be32 yiaddr;
	__be32 siaddr;
	__be32 giaddr;
	__u8 chaddr[16];
	__u8 sname[64];
	__u8 file[128];
	__be32 magic;
	/* __u8 options[]; */
पूर्ण;

#घोषणा BATADV_DHCP_YIADDR_LEN माप(((काष्ठा batadv_dhcp_packet *)0)->yiaddr)
#घोषणा BATADV_DHCP_CHADDR_LEN माप(((काष्ठा batadv_dhcp_packet *)0)->chaddr)

अटल व्योम batadv_dat_purge(काष्ठा work_काष्ठा *work);

/**
 * batadv_dat_start_समयr() - initialise the DAT periodic worker
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_dat_start_समयr(काष्ठा batadv_priv *bat_priv)
अणु
	INIT_DELAYED_WORK(&bat_priv->dat.work, batadv_dat_purge);
	queue_delayed_work(batadv_event_workqueue, &bat_priv->dat.work,
			   msecs_to_jअगरfies(10000));
पूर्ण

/**
 * batadv_dat_entry_release() - release dat_entry from lists and queue क्रम मुक्त
 *  after rcu grace period
 * @ref: kref poपूर्णांकer of the dat_entry
 */
अटल व्योम batadv_dat_entry_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_dat_entry *dat_entry;

	dat_entry = container_of(ref, काष्ठा batadv_dat_entry, refcount);

	kमुक्त_rcu(dat_entry, rcu);
पूर्ण

/**
 * batadv_dat_entry_put() - decrement the dat_entry refcounter and possibly
 *  release it
 * @dat_entry: dat_entry to be मुक्त'd
 */
अटल व्योम batadv_dat_entry_put(काष्ठा batadv_dat_entry *dat_entry)
अणु
	kref_put(&dat_entry->refcount, batadv_dat_entry_release);
पूर्ण

/**
 * batadv_dat_to_purge() - check whether a dat_entry has to be purged or not
 * @dat_entry: the entry to check
 *
 * Return: true अगर the entry has to be purged now, false otherwise.
 */
अटल bool batadv_dat_to_purge(काष्ठा batadv_dat_entry *dat_entry)
अणु
	वापस batadv_has_समयd_out(dat_entry->last_update,
				    BATADV_DAT_ENTRY_TIMEOUT);
पूर्ण

/**
 * __batadv_dat_purge() - delete entries from the DAT local storage
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @to_purge: function in अक्षरge to decide whether an entry has to be purged or
 *	      not. This function takes the dat_entry as argument and has to
 *	      वापसs a boolean value: true is the entry has to be deleted,
 *	      false otherwise
 *
 * Loops over each entry in the DAT local storage and deletes it अगर and only अगर
 * the to_purge function passed as argument वापसs true.
 */
अटल व्योम __batadv_dat_purge(काष्ठा batadv_priv *bat_priv,
			       bool (*to_purge)(काष्ठा batadv_dat_entry *))
अणु
	spinlock_t *list_lock; /* protects ग_लिखो access to the hash lists */
	काष्ठा batadv_dat_entry *dat_entry;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा hlist_head *head;
	u32 i;

	अगर (!bat_priv->dat.hash)
		वापस;

	क्रम (i = 0; i < bat_priv->dat.hash->size; i++) अणु
		head = &bat_priv->dat.hash->table[i];
		list_lock = &bat_priv->dat.hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(dat_entry, node_पंचांगp, head,
					  hash_entry) अणु
			/* अगर a helper function has been passed as parameter,
			 * ask it अगर the entry has to be purged or not
			 */
			अगर (to_purge && !to_purge(dat_entry))
				जारी;

			hlist_del_rcu(&dat_entry->hash_entry);
			batadv_dat_entry_put(dat_entry);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण
पूर्ण

/**
 * batadv_dat_purge() - periodic task that deletes old entries from the local
 *  DAT hash table
 * @work: kernel work काष्ठा
 */
अटल व्योम batadv_dat_purge(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_priv_dat *priv_dat;
	काष्ठा batadv_priv *bat_priv;

	delayed_work = to_delayed_work(work);
	priv_dat = container_of(delayed_work, काष्ठा batadv_priv_dat, work);
	bat_priv = container_of(priv_dat, काष्ठा batadv_priv, dat);

	__batadv_dat_purge(bat_priv, batadv_dat_to_purge);
	batadv_dat_start_समयr(bat_priv);
पूर्ण

/**
 * batadv_compare_dat() - comparing function used in the local DAT hash table
 * @node: node in the local table
 * @data2: second object to compare the node to
 *
 * Return: true अगर the two entries are the same, false otherwise.
 */
अटल bool batadv_compare_dat(स्थिर काष्ठा hlist_node *node, स्थिर व्योम *data2)
अणु
	स्थिर व्योम *data1 = container_of(node, काष्ठा batadv_dat_entry,
					 hash_entry);

	वापस स_भेद(data1, data2, माप(__be32)) == 0;
पूर्ण

/**
 * batadv_arp_hw_src() - extract the hw_src field from an ARP packet
 * @skb: ARP packet
 * @hdr_size: size of the possible header beक्रमe the ARP packet
 *
 * Return: the value of the hw_src field in the ARP packet.
 */
अटल u8 *batadv_arp_hw_src(काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	u8 *addr;

	addr = (u8 *)(skb->data + hdr_size);
	addr += ETH_HLEN + माप(काष्ठा arphdr);

	वापस addr;
पूर्ण

/**
 * batadv_arp_ip_src() - extract the ip_src field from an ARP packet
 * @skb: ARP packet
 * @hdr_size: size of the possible header beक्रमe the ARP packet
 *
 * Return: the value of the ip_src field in the ARP packet.
 */
अटल __be32 batadv_arp_ip_src(काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	वापस *(__क्रमce __be32 *)(batadv_arp_hw_src(skb, hdr_size) + ETH_ALEN);
पूर्ण

/**
 * batadv_arp_hw_dst() - extract the hw_dst field from an ARP packet
 * @skb: ARP packet
 * @hdr_size: size of the possible header beक्रमe the ARP packet
 *
 * Return: the value of the hw_dst field in the ARP packet.
 */
अटल u8 *batadv_arp_hw_dst(काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	वापस batadv_arp_hw_src(skb, hdr_size) + ETH_ALEN + 4;
पूर्ण

/**
 * batadv_arp_ip_dst() - extract the ip_dst field from an ARP packet
 * @skb: ARP packet
 * @hdr_size: size of the possible header beक्रमe the ARP packet
 *
 * Return: the value of the ip_dst field in the ARP packet.
 */
अटल __be32 batadv_arp_ip_dst(काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	u8 *dst = batadv_arp_hw_src(skb, hdr_size) + ETH_ALEN * 2 + 4;

	वापस *(__क्रमce __be32 *)dst;
पूर्ण

/**
 * batadv_hash_dat() - compute the hash value क्रम an IP address
 * @data: data to hash
 * @size: size of the hash table
 *
 * Return: the selected index in the hash table क्रम the given data.
 */
अटल u32 batadv_hash_dat(स्थिर व्योम *data, u32 size)
अणु
	u32 hash = 0;
	स्थिर काष्ठा batadv_dat_entry *dat = data;
	स्थिर अचिन्हित अक्षर *key;
	__be16 vid;
	u32 i;

	key = (__क्रमce स्थिर अचिन्हित अक्षर *)&dat->ip;
	क्रम (i = 0; i < माप(dat->ip); i++) अणु
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	पूर्ण

	vid = htons(dat->vid);
	key = (__क्रमce स्थिर अचिन्हित अक्षर *)&vid;
	क्रम (i = 0; i < माप(dat->vid); i++) अणु
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	पूर्ण

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	वापस hash % size;
पूर्ण

/**
 * batadv_dat_entry_hash_find() - look क्रम a given dat_entry in the local hash
 * table
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ip: search key
 * @vid: VLAN identअगरier
 *
 * Return: the dat_entry अगर found, शून्य otherwise.
 */
अटल काष्ठा batadv_dat_entry *
batadv_dat_entry_hash_find(काष्ठा batadv_priv *bat_priv, __be32 ip,
			   अचिन्हित लघु vid)
अणु
	काष्ठा hlist_head *head;
	काष्ठा batadv_dat_entry to_find, *dat_entry, *dat_entry_पंचांगp = शून्य;
	काष्ठा batadv_hashtable *hash = bat_priv->dat.hash;
	u32 index;

	अगर (!hash)
		वापस शून्य;

	to_find.ip = ip;
	to_find.vid = vid;

	index = batadv_hash_dat(&to_find, hash->size);
	head = &hash->table[index];

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(dat_entry, head, hash_entry) अणु
		अगर (dat_entry->ip != ip)
			जारी;

		अगर (!kref_get_unless_zero(&dat_entry->refcount))
			जारी;

		dat_entry_पंचांगp = dat_entry;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस dat_entry_पंचांगp;
पूर्ण

/**
 * batadv_dat_entry_add() - add a new dat entry or update it अगर alपढ़ोy exists
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ip: ipv4 to add/edit
 * @mac_addr: mac address to assign to the given ipv4
 * @vid: VLAN identअगरier
 */
अटल व्योम batadv_dat_entry_add(काष्ठा batadv_priv *bat_priv, __be32 ip,
				 u8 *mac_addr, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_dat_entry *dat_entry;
	पूर्णांक hash_added;

	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip, vid);
	/* अगर this entry is alपढ़ोy known, just update it */
	अगर (dat_entry) अणु
		अगर (!batadv_compare_eth(dat_entry->mac_addr, mac_addr))
			ether_addr_copy(dat_entry->mac_addr, mac_addr);
		dat_entry->last_update = jअगरfies;
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "Entry updated: %pI4 %pM (vid: %d)\n",
			   &dat_entry->ip, dat_entry->mac_addr,
			   batadv_prपूर्णांक_vid(vid));
		जाओ out;
	पूर्ण

	dat_entry = kदो_स्मृति(माप(*dat_entry), GFP_ATOMIC);
	अगर (!dat_entry)
		जाओ out;

	dat_entry->ip = ip;
	dat_entry->vid = vid;
	ether_addr_copy(dat_entry->mac_addr, mac_addr);
	dat_entry->last_update = jअगरfies;
	kref_init(&dat_entry->refcount);

	kref_get(&dat_entry->refcount);
	hash_added = batadv_hash_add(bat_priv->dat.hash, batadv_compare_dat,
				     batadv_hash_dat, dat_entry,
				     &dat_entry->hash_entry);

	अगर (unlikely(hash_added != 0)) अणु
		/* हटाओ the reference क्रम the hash */
		batadv_dat_entry_put(dat_entry);
		जाओ out;
	पूर्ण

	batadv_dbg(BATADV_DBG_DAT, bat_priv, "New entry added: %pI4 %pM (vid: %d)\n",
		   &dat_entry->ip, dat_entry->mac_addr, batadv_prपूर्णांक_vid(vid));

out:
	अगर (dat_entry)
		batadv_dat_entry_put(dat_entry);
पूर्ण

#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG

/**
 * batadv_dbg_arp() - prपूर्णांक a debug message containing all the ARP packet
 *  details
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: ARP packet
 * @hdr_size: size of the possible header beक्रमe the ARP packet
 * @msg: message to prपूर्णांक together with the debugging inक्रमmation
 */
अटल व्योम batadv_dbg_arp(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			   पूर्णांक hdr_size, अक्षर *msg)
अणु
	काष्ठा batadv_unicast_4addr_packet *unicast_4addr_packet;
	काष्ठा batadv_bcast_packet *bcast_pkt;
	u8 *orig_addr;
	__be32 ip_src, ip_dst;

	अगर (msg)
		batadv_dbg(BATADV_DBG_DAT, bat_priv, "%s\n", msg);

	ip_src = batadv_arp_ip_src(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);
	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "ARP MSG = [src: %pM-%pI4 dst: %pM-%pI4]\n",
		   batadv_arp_hw_src(skb, hdr_size), &ip_src,
		   batadv_arp_hw_dst(skb, hdr_size), &ip_dst);

	अगर (hdr_size < माप(काष्ठा batadv_unicast_packet))
		वापस;

	unicast_4addr_packet = (काष्ठा batadv_unicast_4addr_packet *)skb->data;

	चयन (unicast_4addr_packet->u.packet_type) अणु
	हाल BATADV_UNICAST:
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "* encapsulated within a UNICAST packet\n");
		अवरोध;
	हाल BATADV_UNICAST_4ADDR:
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "* encapsulated within a UNICAST_4ADDR packet (src: %pM)\n",
			   unicast_4addr_packet->src);
		चयन (unicast_4addr_packet->subtype) अणु
		हाल BATADV_P_DAT_DHT_PUT:
			batadv_dbg(BATADV_DBG_DAT, bat_priv, "* type: DAT_DHT_PUT\n");
			अवरोध;
		हाल BATADV_P_DAT_DHT_GET:
			batadv_dbg(BATADV_DBG_DAT, bat_priv, "* type: DAT_DHT_GET\n");
			अवरोध;
		हाल BATADV_P_DAT_CACHE_REPLY:
			batadv_dbg(BATADV_DBG_DAT, bat_priv,
				   "* type: DAT_CACHE_REPLY\n");
			अवरोध;
		हाल BATADV_P_DATA:
			batadv_dbg(BATADV_DBG_DAT, bat_priv, "* type: DATA\n");
			अवरोध;
		शेष:
			batadv_dbg(BATADV_DBG_DAT, bat_priv, "* type: Unknown (%u)!\n",
				   unicast_4addr_packet->u.packet_type);
		पूर्ण
		अवरोध;
	हाल BATADV_BCAST:
		bcast_pkt = (काष्ठा batadv_bcast_packet *)unicast_4addr_packet;
		orig_addr = bcast_pkt->orig;
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "* encapsulated within a BCAST packet (src: %pM)\n",
			   orig_addr);
		अवरोध;
	शेष:
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "* encapsulated within an unknown packet type (0x%x)\n",
			   unicast_4addr_packet->u.packet_type);
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम batadv_dbg_arp(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			   पूर्णांक hdr_size, अक्षर *msg)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_BATMAN_ADV_DEBUG */

/**
 * batadv_is_orig_node_eligible() - check whether a node can be a DHT candidate
 * @res: the array with the alपढ़ोy selected candidates
 * @select: number of alपढ़ोy selected candidates
 * @पंचांगp_max: address of the currently evaluated node
 * @max: current round max address
 * @last_max: address of the last selected candidate
 * @candidate: orig_node under evaluation
 * @max_orig_node: last selected candidate
 *
 * Return: true अगर the node has been elected as next candidate or false
 * otherwise.
 */
अटल bool batadv_is_orig_node_eligible(काष्ठा batadv_dat_candidate *res,
					 पूर्णांक select, batadv_dat_addr_t पंचांगp_max,
					 batadv_dat_addr_t max,
					 batadv_dat_addr_t last_max,
					 काष्ठा batadv_orig_node *candidate,
					 काष्ठा batadv_orig_node *max_orig_node)
अणु
	bool ret = false;
	पूर्णांक j;

	/* check अगर orig node candidate is running DAT */
	अगर (!test_bit(BATADV_ORIG_CAPA_HAS_DAT, &candidate->capabilities))
		जाओ out;

	/* Check अगर this node has alपढ़ोy been selected... */
	क्रम (j = 0; j < select; j++)
		अगर (res[j].orig_node == candidate)
			अवरोध;
	/* ..and possibly skip it */
	अगर (j < select)
		जाओ out;
	/* sanity check: has it alपढ़ोy been selected? This should not happen */
	अगर (पंचांगp_max > last_max)
		जाओ out;
	/* check अगर during this iteration an originator with a बंदr dht
	 * address has alपढ़ोy been found
	 */
	अगर (पंचांगp_max < max)
		जाओ out;
	/* this is an hash collision with the temporary selected node. Choose
	 * the one with the lowest address
	 */
	अगर (पंचांगp_max == max && max_orig_node &&
	    batadv_compare_eth(candidate->orig, max_orig_node->orig))
		जाओ out;

	ret = true;
out:
	वापस ret;
पूर्ण

/**
 * batadv_choose_next_candidate() - select the next DHT candidate
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @cands: candidates array
 * @select: number of candidates alपढ़ोy present in the array
 * @ip_key: key to look up in the DHT
 * @last_max: poपूर्णांकer where the address of the selected candidate will be saved
 */
अटल व्योम batadv_choose_next_candidate(काष्ठा batadv_priv *bat_priv,
					 काष्ठा batadv_dat_candidate *cands,
					 पूर्णांक select, batadv_dat_addr_t ip_key,
					 batadv_dat_addr_t *last_max)
अणु
	batadv_dat_addr_t max = 0;
	batadv_dat_addr_t पंचांगp_max = 0;
	काष्ठा batadv_orig_node *orig_node, *max_orig_node = शून्य;
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	काष्ठा hlist_head *head;
	पूर्णांक i;

	/* अगर no node is eligible as candidate, leave the candidate type as
	 * NOT_FOUND
	 */
	cands[select].type = BATADV_DAT_CANDIDATE_NOT_FOUND;

	/* iterate over the originator list and find the node with the बंदst
	 * dat_address which has not been selected yet
	 */
	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(orig_node, head, hash_entry) अणु
			/* the dht space is a ring using अचिन्हित addresses */
			पंचांगp_max = BATADV_DAT_ADDR_MAX - orig_node->dat_addr +
				  ip_key;

			अगर (!batadv_is_orig_node_eligible(cands, select,
							  पंचांगp_max, max,
							  *last_max, orig_node,
							  max_orig_node))
				जारी;

			अगर (!kref_get_unless_zero(&orig_node->refcount))
				जारी;

			max = पंचांगp_max;
			अगर (max_orig_node)
				batadv_orig_node_put(max_orig_node);
			max_orig_node = orig_node;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	अगर (max_orig_node) अणु
		cands[select].type = BATADV_DAT_CANDIDATE_ORIG;
		cands[select].orig_node = max_orig_node;
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "dat_select_candidates() %d: selected %pM addr=%u dist=%u\n",
			   select, max_orig_node->orig, max_orig_node->dat_addr,
			   max);
	पूर्ण
	*last_max = max;
पूर्ण

/**
 * batadv_dat_select_candidates() - select the nodes which the DHT message has
 *  to be sent to
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ip_dst: ipv4 to look up in the DHT
 * @vid: VLAN identअगरier
 *
 * An originator O is selected अगर and only अगर its DHT_ID value is one of three
 * बंदst values (from the LEFT, with wrap around अगर needed) then the hash
 * value of the key. ip_dst is the key.
 *
 * Return: the candidate array of size BATADV_DAT_CANDIDATE_NUM.
 */
अटल काष्ठा batadv_dat_candidate *
batadv_dat_select_candidates(काष्ठा batadv_priv *bat_priv, __be32 ip_dst,
			     अचिन्हित लघु vid)
अणु
	पूर्णांक select;
	batadv_dat_addr_t last_max = BATADV_DAT_ADDR_MAX, ip_key;
	काष्ठा batadv_dat_candidate *res;
	काष्ठा batadv_dat_entry dat;

	अगर (!bat_priv->orig_hash)
		वापस शून्य;

	res = kदो_स्मृति_array(BATADV_DAT_CANDIDATES_NUM, माप(*res),
			    GFP_ATOMIC);
	अगर (!res)
		वापस शून्य;

	dat.ip = ip_dst;
	dat.vid = vid;
	ip_key = (batadv_dat_addr_t)batadv_hash_dat(&dat,
						    BATADV_DAT_ADDR_MAX);

	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "%s(): IP=%pI4 hash(IP)=%u\n", __func__, &ip_dst,
		   ip_key);

	क्रम (select = 0; select < BATADV_DAT_CANDIDATES_NUM; select++)
		batadv_choose_next_candidate(bat_priv, res, select, ip_key,
					     &last_max);

	वापस res;
पूर्ण

/**
 * batadv_dat_क्रमward_data() - copy and send payload to the selected candidates
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: payload to send
 * @ip: the DHT key
 * @vid: VLAN identअगरier
 * @packet_subtype: unicast4addr packet subtype to use
 *
 * This function copies the skb with pskb_copy() and is sent as a unicast packet
 * to each of the selected candidates.
 *
 * Return: true अगर the packet is sent to at least one candidate, false
 * otherwise.
 */
अटल bool batadv_dat_क्रमward_data(काष्ठा batadv_priv *bat_priv,
				    काष्ठा sk_buff *skb, __be32 ip,
				    अचिन्हित लघु vid, पूर्णांक packet_subtype)
अणु
	पूर्णांक i;
	bool ret = false;
	पूर्णांक send_status;
	काष्ठा batadv_neigh_node *neigh_node = शून्य;
	काष्ठा sk_buff *पंचांगp_skb;
	काष्ठा batadv_dat_candidate *cand;

	cand = batadv_dat_select_candidates(bat_priv, ip, vid);
	अगर (!cand)
		जाओ out;

	batadv_dbg(BATADV_DBG_DAT, bat_priv, "DHT_SEND for %pI4\n", &ip);

	क्रम (i = 0; i < BATADV_DAT_CANDIDATES_NUM; i++) अणु
		अगर (cand[i].type == BATADV_DAT_CANDIDATE_NOT_FOUND)
			जारी;

		neigh_node = batadv_orig_router_get(cand[i].orig_node,
						    BATADV_IF_DEFAULT);
		अगर (!neigh_node)
			जाओ मुक्त_orig;

		पंचांगp_skb = pskb_copy_क्रम_clone(skb, GFP_ATOMIC);
		अगर (!batadv_send_skb_prepare_unicast_4addr(bat_priv, पंचांगp_skb,
							   cand[i].orig_node,
							   packet_subtype)) अणु
			kमुक्त_skb(पंचांगp_skb);
			जाओ मुक्त_neigh;
		पूर्ण

		send_status = batadv_send_unicast_skb(पंचांगp_skb, neigh_node);
		अगर (send_status == NET_XMIT_SUCCESS) अणु
			/* count the sent packet */
			चयन (packet_subtype) अणु
			हाल BATADV_P_DAT_DHT_GET:
				batadv_inc_counter(bat_priv,
						   BATADV_CNT_DAT_GET_TX);
				अवरोध;
			हाल BATADV_P_DAT_DHT_PUT:
				batadv_inc_counter(bat_priv,
						   BATADV_CNT_DAT_PUT_TX);
				अवरोध;
			पूर्ण

			/* packet sent to a candidate: वापस true */
			ret = true;
		पूर्ण
मुक्त_neigh:
		batadv_neigh_node_put(neigh_node);
मुक्त_orig:
		batadv_orig_node_put(cand[i].orig_node);
	पूर्ण

out:
	kमुक्त(cand);
	वापस ret;
पूर्ण

/**
 * batadv_dat_tvlv_container_update() - update the dat tvlv container after dat
 *  setting change
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_dat_tvlv_container_update(काष्ठा batadv_priv *bat_priv)
अणु
	अक्षर dat_mode;

	dat_mode = atomic_पढ़ो(&bat_priv->distributed_arp_table);

	चयन (dat_mode) अणु
	हाल 0:
		batadv_tvlv_container_unरेजिस्टर(bat_priv, BATADV_TVLV_DAT, 1);
		अवरोध;
	हाल 1:
		batadv_tvlv_container_रेजिस्टर(bat_priv, BATADV_TVLV_DAT, 1,
					       शून्य, 0);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * batadv_dat_status_update() - update the dat tvlv container after dat
 *  setting change
 * @net_dev: the soft पूर्णांकerface net device
 */
व्योम batadv_dat_status_update(काष्ठा net_device *net_dev)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(net_dev);

	batadv_dat_tvlv_container_update(bat_priv);
पूर्ण

/**
 * batadv_dat_tvlv_ogm_handler_v1() - process incoming dat tvlv container
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node of the ogm
 * @flags: flags indicating the tvlv state (see batadv_tvlv_handler_flags)
 * @tvlv_value: tvlv buffer containing the gateway data
 * @tvlv_value_len: tvlv buffer length
 */
अटल व्योम batadv_dat_tvlv_ogm_handler_v1(काष्ठा batadv_priv *bat_priv,
					   काष्ठा batadv_orig_node *orig,
					   u8 flags,
					   व्योम *tvlv_value, u16 tvlv_value_len)
अणु
	अगर (flags & BATADV_TVLV_HANDLER_OGM_CIFNOTFND)
		clear_bit(BATADV_ORIG_CAPA_HAS_DAT, &orig->capabilities);
	अन्यथा
		set_bit(BATADV_ORIG_CAPA_HAS_DAT, &orig->capabilities);
पूर्ण

/**
 * batadv_dat_hash_मुक्त() - मुक्त the local DAT hash table
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_dat_hash_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	अगर (!bat_priv->dat.hash)
		वापस;

	__batadv_dat_purge(bat_priv, शून्य);

	batadv_hash_destroy(bat_priv->dat.hash);

	bat_priv->dat.hash = शून्य;
पूर्ण

/**
 * batadv_dat_init() - initialise the DAT पूर्णांकernals
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 in हाल of success, a negative error code otherwise
 */
पूर्णांक batadv_dat_init(काष्ठा batadv_priv *bat_priv)
अणु
	अगर (bat_priv->dat.hash)
		वापस 0;

	bat_priv->dat.hash = batadv_hash_new(1024);

	अगर (!bat_priv->dat.hash)
		वापस -ENOMEM;

	batadv_dat_start_समयr(bat_priv);

	batadv_tvlv_handler_रेजिस्टर(bat_priv, batadv_dat_tvlv_ogm_handler_v1,
				     शून्य, BATADV_TVLV_DAT, 1,
				     BATADV_TVLV_HANDLER_OGM_CIFNOTFND);
	batadv_dat_tvlv_container_update(bat_priv);
	वापस 0;
पूर्ण

/**
 * batadv_dat_मुक्त() - मुक्त the DAT पूर्णांकernals
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_dat_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	batadv_tvlv_container_unरेजिस्टर(bat_priv, BATADV_TVLV_DAT, 1);
	batadv_tvlv_handler_unरेजिस्टर(bat_priv, BATADV_TVLV_DAT, 1);

	cancel_delayed_work_sync(&bat_priv->dat.work);

	batadv_dat_hash_मुक्त(bat_priv);
पूर्ण

/**
 * batadv_dat_cache_dump_entry() - dump one entry of the DAT cache table to a
 *  netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @dat_entry: entry to dump
 *
 * Return: 0 or error code.
 */
अटल पूर्णांक
batadv_dat_cache_dump_entry(काष्ठा sk_buff *msg, u32 portid,
			    काष्ठा netlink_callback *cb,
			    काष्ठा batadv_dat_entry *dat_entry)
अणु
	पूर्णांक msecs;
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_DAT_CACHE);
	अगर (!hdr)
		वापस -ENOBUFS;

	genl_dump_check_consistent(cb, hdr);

	msecs = jअगरfies_to_msecs(jअगरfies - dat_entry->last_update);

	अगर (nla_put_in_addr(msg, BATADV_ATTR_DAT_CACHE_IP4ADDRESS,
			    dat_entry->ip) ||
	    nla_put(msg, BATADV_ATTR_DAT_CACHE_HWADDRESS, ETH_ALEN,
		    dat_entry->mac_addr) ||
	    nla_put_u16(msg, BATADV_ATTR_DAT_CACHE_VID, dat_entry->vid) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS, msecs)) अणु
		genlmsg_cancel(msg, hdr);
		वापस -EMSGSIZE;
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस 0;
पूर्ण

/**
 * batadv_dat_cache_dump_bucket() - dump one bucket of the DAT cache table to
 *  a netlink socket
 * @msg: buffer क्रम the message
 * @portid: netlink port
 * @cb: Control block containing additional options
 * @hash: hash to dump
 * @bucket: bucket index to dump
 * @idx_skip: How many entries to skip
 *
 * Return: 0 or error code.
 */
अटल पूर्णांक
batadv_dat_cache_dump_bucket(काष्ठा sk_buff *msg, u32 portid,
			     काष्ठा netlink_callback *cb,
			     काष्ठा batadv_hashtable *hash, अचिन्हित पूर्णांक bucket,
			     पूर्णांक *idx_skip)
अणु
	काष्ठा batadv_dat_entry *dat_entry;
	पूर्णांक idx = 0;

	spin_lock_bh(&hash->list_locks[bucket]);
	cb->seq = atomic_पढ़ो(&hash->generation) << 1 | 1;

	hlist_क्रम_each_entry(dat_entry, &hash->table[bucket], hash_entry) अणु
		अगर (idx < *idx_skip)
			जाओ skip;

		अगर (batadv_dat_cache_dump_entry(msg, portid, cb, dat_entry)) अणु
			spin_unlock_bh(&hash->list_locks[bucket]);
			*idx_skip = idx;

			वापस -EMSGSIZE;
		पूर्ण

skip:
		idx++;
	पूर्ण
	spin_unlock_bh(&hash->list_locks[bucket]);

	वापस 0;
पूर्ण

/**
 * batadv_dat_cache_dump() - dump DAT cache table to a netlink socket
 * @msg: buffer क्रम the message
 * @cb: callback काष्ठाure containing arguments
 *
 * Return: message length.
 */
पूर्णांक batadv_dat_cache_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
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
	hash = bat_priv->dat.hash;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर || primary_अगर->अगर_status != BATADV_IF_ACTIVE) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	जबतक (bucket < hash->size) अणु
		अगर (batadv_dat_cache_dump_bucket(msg, portid, cb, hash, bucket,
						 &idx))
			अवरोध;

		bucket++;
		idx = 0;
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
 * batadv_arp_get_type() - parse an ARP packet and माला_लो the type
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: packet to analyse
 * @hdr_size: size of the possible header beक्रमe the ARP packet in the skb
 *
 * Return: the ARP type अगर the skb contains a valid ARP packet, 0 otherwise.
 */
अटल u16 batadv_arp_get_type(काष्ठा batadv_priv *bat_priv,
			       काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	काष्ठा arphdr *arphdr;
	काष्ठा ethhdr *ethhdr;
	__be32 ip_src, ip_dst;
	u8 *hw_src, *hw_dst;
	u16 type = 0;

	/* pull the ethernet header */
	अगर (unlikely(!pskb_may_pull(skb, hdr_size + ETH_HLEN)))
		जाओ out;

	ethhdr = (काष्ठा ethhdr *)(skb->data + hdr_size);

	अगर (ethhdr->h_proto != htons(ETH_P_ARP))
		जाओ out;

	/* pull the ARP payload */
	अगर (unlikely(!pskb_may_pull(skb, hdr_size + ETH_HLEN +
				    arp_hdr_len(skb->dev))))
		जाओ out;

	arphdr = (काष्ठा arphdr *)(skb->data + hdr_size + ETH_HLEN);

	/* check whether the ARP packet carries a valid IP inक्रमmation */
	अगर (arphdr->ar_hrd != htons(ARPHRD_ETHER))
		जाओ out;

	अगर (arphdr->ar_pro != htons(ETH_P_IP))
		जाओ out;

	अगर (arphdr->ar_hln != ETH_ALEN)
		जाओ out;

	अगर (arphdr->ar_pln != 4)
		जाओ out;

	/* Check क्रम bad reply/request. If the ARP message is not sane, DAT
	 * will simply ignore it
	 */
	ip_src = batadv_arp_ip_src(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);
	अगर (ipv4_is_loopback(ip_src) || ipv4_is_multicast(ip_src) ||
	    ipv4_is_loopback(ip_dst) || ipv4_is_multicast(ip_dst) ||
	    ipv4_is_zeronet(ip_src) || ipv4_is_lbcast(ip_src) ||
	    ipv4_is_zeronet(ip_dst) || ipv4_is_lbcast(ip_dst))
		जाओ out;

	hw_src = batadv_arp_hw_src(skb, hdr_size);
	अगर (is_zero_ether_addr(hw_src) || is_multicast_ether_addr(hw_src))
		जाओ out;

	/* करोn't care about the destination MAC address in ARP requests */
	अगर (arphdr->ar_op != htons(ARPOP_REQUEST)) अणु
		hw_dst = batadv_arp_hw_dst(skb, hdr_size);
		अगर (is_zero_ether_addr(hw_dst) ||
		    is_multicast_ether_addr(hw_dst))
			जाओ out;
	पूर्ण

	type = ntohs(arphdr->ar_op);
out:
	वापस type;
पूर्ण

/**
 * batadv_dat_get_vid() - extract the VLAN identअगरier from skb अगर any
 * @skb: the buffer containing the packet to extract the VID from
 * @hdr_size: the size of the baपंचांगan-adv header encapsulating the packet
 *
 * Return: If the packet embedded in the skb is vlan tagged this function
 * वापसs the VID with the BATADV_VLAN_HAS_TAG flag. Otherwise BATADV_NO_FLAGS
 * is वापसed.
 */
अटल अचिन्हित लघु batadv_dat_get_vid(काष्ठा sk_buff *skb, पूर्णांक *hdr_size)
अणु
	अचिन्हित लघु vid;

	vid = batadv_get_vid(skb, *hdr_size);

	/* ARP parsing functions jump क्रमward of hdr_size + ETH_HLEN.
	 * If the header contained in the packet is a VLAN one (which is दीर्घer)
	 * hdr_size is updated so that the functions will still skip the
	 * correct amount of bytes.
	 */
	अगर (vid & BATADV_VLAN_HAS_TAG)
		*hdr_size += VLAN_HLEN;

	वापस vid;
पूर्ण

/**
 * batadv_dat_arp_create_reply() - create an ARP Reply
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ip_src: ARP sender IP
 * @ip_dst: ARP target IP
 * @hw_src: Ethernet source and ARP sender MAC
 * @hw_dst: Ethernet destination and ARP target MAC
 * @vid: VLAN identअगरier (optional, set to zero otherwise)
 *
 * Creates an ARP Reply from the given values, optionally encapsulated in a
 * VLAN header.
 *
 * Return: An skb containing an ARP Reply.
 */
अटल काष्ठा sk_buff *
batadv_dat_arp_create_reply(काष्ठा batadv_priv *bat_priv, __be32 ip_src,
			    __be32 ip_dst, u8 *hw_src, u8 *hw_dst,
			    अचिन्हित लघु vid)
अणु
	काष्ठा sk_buff *skb;

	skb = arp_create(ARPOP_REPLY, ETH_P_ARP, ip_dst, bat_priv->soft_अगरace,
			 ip_src, hw_dst, hw_src, hw_dst);
	अगर (!skb)
		वापस शून्य;

	skb_reset_mac_header(skb);

	अगर (vid & BATADV_VLAN_HAS_TAG)
		skb = vlan_insert_tag(skb, htons(ETH_P_8021Q),
				      vid & VLAN_VID_MASK);

	वापस skb;
पूर्ण

/**
 * batadv_dat_snoop_outgoing_arp_request() - snoop the ARP request and try to
 * answer using DAT
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: packet to check
 *
 * Return: true अगर the message has been sent to the dht candidates, false
 * otherwise. In हाल of a positive वापस value the message has to be enqueued
 * to permit the fallback.
 */
bool batadv_dat_snoop_outgoing_arp_request(काष्ठा batadv_priv *bat_priv,
					   काष्ठा sk_buff *skb)
अणु
	u16 type = 0;
	__be32 ip_dst, ip_src;
	u8 *hw_src;
	bool ret = false;
	काष्ठा batadv_dat_entry *dat_entry = शून्य;
	काष्ठा sk_buff *skb_new;
	काष्ठा net_device *soft_अगरace = bat_priv->soft_अगरace;
	पूर्णांक hdr_size = 0;
	अचिन्हित लघु vid;

	अगर (!atomic_पढ़ो(&bat_priv->distributed_arp_table))
		जाओ out;

	vid = batadv_dat_get_vid(skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, skb, hdr_size);
	/* If the node माला_लो an ARP_REQUEST it has to send a DHT_GET unicast
	 * message to the selected DHT candidates
	 */
	अगर (type != ARPOP_REQUEST)
		जाओ out;

	batadv_dbg_arp(bat_priv, skb, hdr_size, "Parsing outgoing ARP REQUEST");

	ip_src = batadv_arp_ip_src(skb, hdr_size);
	hw_src = batadv_arp_hw_src(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);

	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);

	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip_dst, vid);
	अगर (dat_entry) अणु
		/* If the ARP request is destined क्रम a local client the local
		 * client will answer itself. DAT would only generate a
		 * duplicate packet.
		 *
		 * Moreover, अगर the soft-पूर्णांकerface is enslaved पूर्णांकo a bridge, an
		 * additional DAT answer may trigger kernel warnings about
		 * a packet coming from the wrong port.
		 */
		अगर (batadv_is_my_client(bat_priv, dat_entry->mac_addr, vid)) अणु
			ret = true;
			जाओ out;
		पूर्ण

		/* If BLA is enabled, only send ARP replies अगर we have claimed
		 * the destination क्रम the ARP request or अगर no one अन्यथा of
		 * the backbone gws beदीर्घing to our backbone has claimed the
		 * destination.
		 */
		अगर (!batadv_bla_check_claim(bat_priv,
					    dat_entry->mac_addr, vid)) अणु
			batadv_dbg(BATADV_DBG_DAT, bat_priv,
				   "Device %pM claimed by another backbone gw. Don't send ARP reply!",
				   dat_entry->mac_addr);
			ret = true;
			जाओ out;
		पूर्ण

		skb_new = batadv_dat_arp_create_reply(bat_priv, ip_dst, ip_src,
						      dat_entry->mac_addr,
						      hw_src, vid);
		अगर (!skb_new)
			जाओ out;

		skb_new->protocol = eth_type_trans(skb_new, soft_अगरace);

		batadv_inc_counter(bat_priv, BATADV_CNT_RX);
		batadv_add_counter(bat_priv, BATADV_CNT_RX_BYTES,
				   skb->len + ETH_HLEN + hdr_size);

		netअगर_rx(skb_new);
		batadv_dbg(BATADV_DBG_DAT, bat_priv, "ARP request replied locally\n");
		ret = true;
	पूर्ण अन्यथा अणु
		/* Send the request to the DHT */
		ret = batadv_dat_क्रमward_data(bat_priv, skb, ip_dst, vid,
					      BATADV_P_DAT_DHT_GET);
	पूर्ण
out:
	अगर (dat_entry)
		batadv_dat_entry_put(dat_entry);
	वापस ret;
पूर्ण

/**
 * batadv_dat_snoop_incoming_arp_request() - snoop the ARP request and try to
 * answer using the local DAT storage
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: packet to check
 * @hdr_size: size of the encapsulation header
 *
 * Return: true अगर the request has been answered, false otherwise.
 */
bool batadv_dat_snoop_incoming_arp_request(काष्ठा batadv_priv *bat_priv,
					   काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	u16 type;
	__be32 ip_src, ip_dst;
	u8 *hw_src;
	काष्ठा sk_buff *skb_new;
	काष्ठा batadv_dat_entry *dat_entry = शून्य;
	bool ret = false;
	अचिन्हित लघु vid;
	पूर्णांक err;

	अगर (!atomic_पढ़ो(&bat_priv->distributed_arp_table))
		जाओ out;

	vid = batadv_dat_get_vid(skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, skb, hdr_size);
	अगर (type != ARPOP_REQUEST)
		जाओ out;

	hw_src = batadv_arp_hw_src(skb, hdr_size);
	ip_src = batadv_arp_ip_src(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);

	batadv_dbg_arp(bat_priv, skb, hdr_size, "Parsing incoming ARP REQUEST");

	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);

	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip_dst, vid);
	अगर (!dat_entry)
		जाओ out;

	skb_new = batadv_dat_arp_create_reply(bat_priv, ip_dst, ip_src,
					      dat_entry->mac_addr, hw_src, vid);
	अगर (!skb_new)
		जाओ out;

	/* To preserve backwards compatibility, the node has choose the outgoing
	 * क्रमmat based on the incoming request packet type. The assumption is
	 * that a node not using the 4addr packet क्रमmat करोesn't support it.
	 */
	अगर (hdr_size == माप(काष्ठा batadv_unicast_4addr_packet))
		err = batadv_send_skb_via_tt_4addr(bat_priv, skb_new,
						   BATADV_P_DAT_CACHE_REPLY,
						   शून्य, vid);
	अन्यथा
		err = batadv_send_skb_via_tt(bat_priv, skb_new, शून्य, vid);

	अगर (err != NET_XMIT_DROP) अणु
		batadv_inc_counter(bat_priv, BATADV_CNT_DAT_CACHED_REPLY_TX);
		ret = true;
	पूर्ण
out:
	अगर (dat_entry)
		batadv_dat_entry_put(dat_entry);
	अगर (ret)
		kमुक्त_skb(skb);
	वापस ret;
पूर्ण

/**
 * batadv_dat_snoop_outgoing_arp_reply() - snoop the ARP reply and fill the DHT
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: packet to check
 */
व्योम batadv_dat_snoop_outgoing_arp_reply(काष्ठा batadv_priv *bat_priv,
					 काष्ठा sk_buff *skb)
अणु
	u16 type;
	__be32 ip_src, ip_dst;
	u8 *hw_src, *hw_dst;
	पूर्णांक hdr_size = 0;
	अचिन्हित लघु vid;

	अगर (!atomic_पढ़ो(&bat_priv->distributed_arp_table))
		वापस;

	vid = batadv_dat_get_vid(skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, skb, hdr_size);
	अगर (type != ARPOP_REPLY)
		वापस;

	batadv_dbg_arp(bat_priv, skb, hdr_size, "Parsing outgoing ARP REPLY");

	hw_src = batadv_arp_hw_src(skb, hdr_size);
	ip_src = batadv_arp_ip_src(skb, hdr_size);
	hw_dst = batadv_arp_hw_dst(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);

	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);
	batadv_dat_entry_add(bat_priv, ip_dst, hw_dst, vid);

	/* Send the ARP reply to the candidates क्रम both the IP addresses that
	 * the node obtained from the ARP reply
	 */
	batadv_dat_क्रमward_data(bat_priv, skb, ip_src, vid,
				BATADV_P_DAT_DHT_PUT);
	batadv_dat_क्रमward_data(bat_priv, skb, ip_dst, vid,
				BATADV_P_DAT_DHT_PUT);
पूर्ण

/**
 * batadv_dat_snoop_incoming_arp_reply() - snoop the ARP reply and fill the
 *  local DAT storage only
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: packet to check
 * @hdr_size: size of the encapsulation header
 *
 * Return: true अगर the packet was snooped and consumed by DAT. False अगर the
 * packet has to be delivered to the पूर्णांकerface
 */
bool batadv_dat_snoop_incoming_arp_reply(काष्ठा batadv_priv *bat_priv,
					 काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	काष्ठा batadv_dat_entry *dat_entry = शून्य;
	u16 type;
	__be32 ip_src, ip_dst;
	u8 *hw_src, *hw_dst;
	bool dropped = false;
	अचिन्हित लघु vid;

	अगर (!atomic_पढ़ो(&bat_priv->distributed_arp_table))
		जाओ out;

	vid = batadv_dat_get_vid(skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, skb, hdr_size);
	अगर (type != ARPOP_REPLY)
		जाओ out;

	batadv_dbg_arp(bat_priv, skb, hdr_size, "Parsing incoming ARP REPLY");

	hw_src = batadv_arp_hw_src(skb, hdr_size);
	ip_src = batadv_arp_ip_src(skb, hdr_size);
	hw_dst = batadv_arp_hw_dst(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);

	/* If ip_dst is alपढ़ोy in cache and has the right mac address,
	 * drop this frame अगर this ARP reply is destined क्रम us because it's
	 * most probably an ARP reply generated by another node of the DHT.
	 * We have most probably received alपढ़ोy a reply earlier. Delivering
	 * this frame would lead to द्विगुनd receive of an ARP reply.
	 */
	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip_src, vid);
	अगर (dat_entry && batadv_compare_eth(hw_src, dat_entry->mac_addr)) अणु
		batadv_dbg(BATADV_DBG_DAT, bat_priv, "Doubled ARP reply removed: ARP MSG = [src: %pM-%pI4 dst: %pM-%pI4]; dat_entry: %pM-%pI4\n",
			   hw_src, &ip_src, hw_dst, &ip_dst,
			   dat_entry->mac_addr,	&dat_entry->ip);
		dropped = true;
	पूर्ण

	/* Update our पूर्णांकernal cache with both the IP addresses the node got
	 * within the ARP reply
	 */
	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);
	batadv_dat_entry_add(bat_priv, ip_dst, hw_dst, vid);

	अगर (dropped)
		जाओ out;

	/* If BLA is enabled, only क्रमward ARP replies अगर we have claimed the
	 * source of the ARP reply or अगर no one अन्यथा of the same backbone has
	 * alपढ़ोy claimed that client. This prevents that dअगरferent gateways
	 * to the same backbone all क्रमward the ARP reply leading to multiple
	 * replies in the backbone.
	 */
	अगर (!batadv_bla_check_claim(bat_priv, hw_src, vid)) अणु
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "Device %pM claimed by another backbone gw. Drop ARP reply.\n",
			   hw_src);
		dropped = true;
		जाओ out;
	पूर्ण

	/* अगर this REPLY is directed to a client of mine, let's deliver the
	 * packet to the पूर्णांकerface
	 */
	dropped = !batadv_is_my_client(bat_priv, hw_dst, vid);

	/* अगर this REPLY is sent on behalf of a client of mine, let's drop the
	 * packet because the client will reply by itself
	 */
	dropped |= batadv_is_my_client(bat_priv, hw_src, vid);
out:
	अगर (dropped)
		kमुक्त_skb(skb);
	अगर (dat_entry)
		batadv_dat_entry_put(dat_entry);
	/* अगर dropped == false -> deliver to the पूर्णांकerface */
	वापस dropped;
पूर्ण

/**
 * batadv_dat_check_dhcp_ipudp() - check skb क्रम IP+UDP headers valid क्रम DHCP
 * @skb: the packet to check
 * @ip_src: a buffer to store the IPv4 source address in
 *
 * Checks whether the given skb has an IP and UDP header valid क्रम a DHCP
 * message from a DHCP server. And अगर so, stores the IPv4 source address in
 * the provided buffer.
 *
 * Return: True अगर valid, false otherwise.
 */
अटल bool
batadv_dat_check_dhcp_ipudp(काष्ठा sk_buff *skb, __be32 *ip_src)
अणु
	अचिन्हित पूर्णांक offset = skb_network_offset(skb);
	काष्ठा udphdr *udphdr, _udphdr;
	काष्ठा iphdr *iphdr, _iphdr;

	iphdr = skb_header_poपूर्णांकer(skb, offset, माप(_iphdr), &_iphdr);
	अगर (!iphdr || iphdr->version != 4 || iphdr->ihl * 4 < माप(_iphdr))
		वापस false;

	अगर (iphdr->protocol != IPPROTO_UDP)
		वापस false;

	offset += iphdr->ihl * 4;
	skb_set_transport_header(skb, offset);

	udphdr = skb_header_poपूर्णांकer(skb, offset, माप(_udphdr), &_udphdr);
	अगर (!udphdr || udphdr->source != htons(67))
		वापस false;

	*ip_src = get_unaligned(&iphdr->saddr);

	वापस true;
पूर्ण

/**
 * batadv_dat_check_dhcp() - examine packet क्रम valid DHCP message
 * @skb: the packet to check
 * @proto: ethernet protocol hपूर्णांक (behind a potential vlan)
 * @ip_src: a buffer to store the IPv4 source address in
 *
 * Checks whether the given skb is a valid DHCP packet. And अगर so, stores the
 * IPv4 source address in the provided buffer.
 *
 * Caller needs to ensure that the skb network header is set correctly.
 *
 * Return: If skb is a valid DHCP packet, then वापसs its op code
 * (e.g. BOOTREPLY vs. BOOTREQUEST). Otherwise वापसs -EINVAL.
 */
अटल पूर्णांक
batadv_dat_check_dhcp(काष्ठा sk_buff *skb, __be16 proto, __be32 *ip_src)
अणु
	__be32 *magic, _magic;
	अचिन्हित पूर्णांक offset;
	काष्ठा अणु
		__u8 op;
		__u8 htype;
		__u8 hlen;
		__u8 hops;
	पूर्ण *dhcp_h, _dhcp_h;

	अगर (proto != htons(ETH_P_IP))
		वापस -EINVAL;

	अगर (!batadv_dat_check_dhcp_ipudp(skb, ip_src))
		वापस -EINVAL;

	offset = skb_transport_offset(skb) + माप(काष्ठा udphdr);
	अगर (skb->len < offset + माप(काष्ठा batadv_dhcp_packet))
		वापस -EINVAL;

	dhcp_h = skb_header_poपूर्णांकer(skb, offset, माप(_dhcp_h), &_dhcp_h);
	अगर (!dhcp_h || dhcp_h->htype != BATADV_HTYPE_ETHERNET ||
	    dhcp_h->hlen != ETH_ALEN)
		वापस -EINVAL;

	offset += दुरत्व(काष्ठा batadv_dhcp_packet, magic);

	magic = skb_header_poपूर्णांकer(skb, offset, माप(_magic), &_magic);
	अगर (!magic || get_unaligned(magic) != htonl(BATADV_DHCP_MAGIC))
		वापस -EINVAL;

	वापस dhcp_h->op;
पूर्ण

/**
 * batadv_dat_get_dhcp_message_type() - get message type of a DHCP packet
 * @skb: the DHCP packet to parse
 *
 * Iterates over the DHCP options of the given DHCP packet to find a
 * DHCP Message Type option and parse it.
 *
 * Caller needs to ensure that the given skb is a valid DHCP packet and
 * that the skb transport header is set correctly.
 *
 * Return: The found DHCP message type value, अगर found. -EINVAL otherwise.
 */
अटल पूर्णांक batadv_dat_get_dhcp_message_type(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक offset = skb_transport_offset(skb) + माप(काष्ठा udphdr);
	u8 *type, _type;
	काष्ठा अणु
		u8 type;
		u8 len;
	पूर्ण *tl, _tl;

	offset += माप(काष्ठा batadv_dhcp_packet);

	जबतक ((tl = skb_header_poपूर्णांकer(skb, offset, माप(_tl), &_tl))) अणु
		अगर (tl->type == BATADV_DHCP_OPT_MSG_TYPE)
			अवरोध;

		अगर (tl->type == BATADV_DHCP_OPT_END)
			अवरोध;

		अगर (tl->type == BATADV_DHCP_OPT_PAD)
			offset++;
		अन्यथा
			offset += tl->len + माप(_tl);
	पूर्ण

	/* Option Overload Code not supported */
	अगर (!tl || tl->type != BATADV_DHCP_OPT_MSG_TYPE ||
	    tl->len != माप(_type))
		वापस -EINVAL;

	offset += माप(_tl);

	type = skb_header_poपूर्णांकer(skb, offset, माप(_type), &_type);
	अगर (!type)
		वापस -EINVAL;

	वापस *type;
पूर्ण

/**
 * batadv_dat_dhcp_get_yiaddr() - get yiaddr from a DHCP packet
 * @skb: the DHCP packet to parse
 * @buf: a buffer to store the yiaddr in
 *
 * Caller needs to ensure that the given skb is a valid DHCP packet and
 * that the skb transport header is set correctly.
 *
 * Return: True on success, false otherwise.
 */
अटल bool batadv_dat_dhcp_get_yiaddr(काष्ठा sk_buff *skb, __be32 *buf)
अणु
	अचिन्हित पूर्णांक offset = skb_transport_offset(skb) + माप(काष्ठा udphdr);
	__be32 *yiaddr;

	offset += दुरत्व(काष्ठा batadv_dhcp_packet, yiaddr);
	yiaddr = skb_header_poपूर्णांकer(skb, offset, BATADV_DHCP_YIADDR_LEN, buf);

	अगर (!yiaddr)
		वापस false;

	अगर (yiaddr != buf)
		*buf = get_unaligned(yiaddr);

	वापस true;
पूर्ण

/**
 * batadv_dat_get_dhcp_chaddr() - get chaddr from a DHCP packet
 * @skb: the DHCP packet to parse
 * @buf: a buffer to store the chaddr in
 *
 * Caller needs to ensure that the given skb is a valid DHCP packet and
 * that the skb transport header is set correctly.
 *
 * Return: True on success, false otherwise
 */
अटल bool batadv_dat_get_dhcp_chaddr(काष्ठा sk_buff *skb, u8 *buf)
अणु
	अचिन्हित पूर्णांक offset = skb_transport_offset(skb) + माप(काष्ठा udphdr);
	u8 *chaddr;

	offset += दुरत्व(काष्ठा batadv_dhcp_packet, chaddr);
	chaddr = skb_header_poपूर्णांकer(skb, offset, BATADV_DHCP_CHADDR_LEN, buf);

	अगर (!chaddr)
		वापस false;

	अगर (chaddr != buf)
		स_नकल(buf, chaddr, BATADV_DHCP_CHADDR_LEN);

	वापस true;
पूर्ण

/**
 * batadv_dat_put_dhcp() - माला_दो addresses from a DHCP packet पूर्णांकo the DHT and
 *  DAT cache
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @chaddr: the DHCP client MAC address
 * @yiaddr: the DHCP client IP address
 * @hw_dst: the DHCP server MAC address
 * @ip_dst: the DHCP server IP address
 * @vid: VLAN identअगरier
 *
 * Adds given MAC/IP pairs to the local DAT cache and propagates them further
 * पूर्णांकo the DHT.
 *
 * For the DHT propagation, client MAC + IP will appear as the ARP Reply
 * transmitter (and hw_dst/ip_dst as the target).
 */
अटल व्योम batadv_dat_put_dhcp(काष्ठा batadv_priv *bat_priv, u8 *chaddr,
				__be32 yiaddr, u8 *hw_dst, __be32 ip_dst,
				अचिन्हित लघु vid)
अणु
	काष्ठा sk_buff *skb;

	skb = batadv_dat_arp_create_reply(bat_priv, yiaddr, ip_dst, chaddr,
					  hw_dst, vid);
	अगर (!skb)
		वापस;

	skb_set_network_header(skb, ETH_HLEN);

	batadv_dat_entry_add(bat_priv, yiaddr, chaddr, vid);
	batadv_dat_entry_add(bat_priv, ip_dst, hw_dst, vid);

	batadv_dat_क्रमward_data(bat_priv, skb, yiaddr, vid,
				BATADV_P_DAT_DHT_PUT);
	batadv_dat_क्रमward_data(bat_priv, skb, ip_dst, vid,
				BATADV_P_DAT_DHT_PUT);

	consume_skb(skb);

	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "Snooped from outgoing DHCPACK (server address): %pI4, %pM (vid: %i)\n",
		   &ip_dst, hw_dst, batadv_prपूर्णांक_vid(vid));
	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "Snooped from outgoing DHCPACK (client address): %pI4, %pM (vid: %i)\n",
		   &yiaddr, chaddr, batadv_prपूर्णांक_vid(vid));
पूर्ण

/**
 * batadv_dat_check_dhcp_ack() - examine packet क्रम valid DHCP message
 * @skb: the packet to check
 * @proto: ethernet protocol hपूर्णांक (behind a potential vlan)
 * @ip_src: a buffer to store the IPv4 source address in
 * @chaddr: a buffer to store the DHCP Client Hardware Address in
 * @yiaddr: a buffer to store the DHCP Your IP Address in
 *
 * Checks whether the given skb is a valid DHCPACK. And अगर so, stores the
 * IPv4 server source address (ip_src), client MAC address (chaddr) and client
 * IPv4 address (yiaddr) in the provided buffers.
 *
 * Caller needs to ensure that the skb network header is set correctly.
 *
 * Return: True अगर the skb is a valid DHCPACK. False otherwise.
 */
अटल bool
batadv_dat_check_dhcp_ack(काष्ठा sk_buff *skb, __be16 proto, __be32 *ip_src,
			  u8 *chaddr, __be32 *yiaddr)
अणु
	पूर्णांक type;

	type = batadv_dat_check_dhcp(skb, proto, ip_src);
	अगर (type != BATADV_BOOTREPLY)
		वापस false;

	type = batadv_dat_get_dhcp_message_type(skb);
	अगर (type != BATADV_DHCPACK)
		वापस false;

	अगर (!batadv_dat_dhcp_get_yiaddr(skb, yiaddr))
		वापस false;

	अगर (!batadv_dat_get_dhcp_chaddr(skb, chaddr))
		वापस false;

	वापस true;
पूर्ण

/**
 * batadv_dat_snoop_outgoing_dhcp_ack() - snoop DHCPACK and fill DAT with it
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the packet to snoop
 * @proto: ethernet protocol hपूर्णांक (behind a potential vlan)
 * @vid: VLAN identअगरier
 *
 * This function first checks whether the given skb is a valid DHCPACK. If
 * so then its source MAC and IP as well as its DHCP Client Hardware Address
 * field and DHCP Your IP Address field are added to the local DAT cache and
 * propagated पूर्णांकo the DHT.
 *
 * Caller needs to ensure that the skb mac and network headers are set
 * correctly.
 */
व्योम batadv_dat_snoop_outgoing_dhcp_ack(काष्ठा batadv_priv *bat_priv,
					काष्ठा sk_buff *skb,
					__be16 proto,
					अचिन्हित लघु vid)
अणु
	u8 chaddr[BATADV_DHCP_CHADDR_LEN];
	__be32 ip_src, yiaddr;

	अगर (!atomic_पढ़ो(&bat_priv->distributed_arp_table))
		वापस;

	अगर (!batadv_dat_check_dhcp_ack(skb, proto, &ip_src, chaddr, &yiaddr))
		वापस;

	batadv_dat_put_dhcp(bat_priv, chaddr, yiaddr, eth_hdr(skb)->h_source,
			    ip_src, vid);
पूर्ण

/**
 * batadv_dat_snoop_incoming_dhcp_ack() - snoop DHCPACK and fill DAT cache
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the packet to snoop
 * @hdr_size: header size, up to the tail of the baपंचांगan-adv header
 *
 * This function first checks whether the given skb is a valid DHCPACK. If
 * so then its source MAC and IP as well as its DHCP Client Hardware Address
 * field and DHCP Your IP Address field are added to the local DAT cache.
 */
व्योम batadv_dat_snoop_incoming_dhcp_ack(काष्ठा batadv_priv *bat_priv,
					काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	u8 chaddr[BATADV_DHCP_CHADDR_LEN];
	काष्ठा ethhdr *ethhdr;
	__be32 ip_src, yiaddr;
	अचिन्हित लघु vid;
	__be16 proto;
	u8 *hw_src;

	अगर (!atomic_पढ़ो(&bat_priv->distributed_arp_table))
		वापस;

	अगर (unlikely(!pskb_may_pull(skb, hdr_size + ETH_HLEN)))
		वापस;

	ethhdr = (काष्ठा ethhdr *)(skb->data + hdr_size);
	skb_set_network_header(skb, hdr_size + ETH_HLEN);
	proto = ethhdr->h_proto;

	अगर (!batadv_dat_check_dhcp_ack(skb, proto, &ip_src, chaddr, &yiaddr))
		वापस;

	hw_src = ethhdr->h_source;
	vid = batadv_dat_get_vid(skb, &hdr_size);

	batadv_dat_entry_add(bat_priv, yiaddr, chaddr, vid);
	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);

	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "Snooped from incoming DHCPACK (server address): %pI4, %pM (vid: %i)\n",
		   &ip_src, hw_src, batadv_prपूर्णांक_vid(vid));
	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "Snooped from incoming DHCPACK (client address): %pI4, %pM (vid: %i)\n",
		   &yiaddr, chaddr, batadv_prपूर्णांक_vid(vid));
पूर्ण

/**
 * batadv_dat_drop_broadcast_packet() - check अगर an ARP request has to be
 *  dropped (because the node has alपढ़ोy obtained the reply via DAT) or not
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @क्रमw_packet: the broadcast packet
 *
 * Return: true अगर the node can drop the packet, false otherwise.
 */
bool batadv_dat_drop_broadcast_packet(काष्ठा batadv_priv *bat_priv,
				      काष्ठा batadv_क्रमw_packet *क्रमw_packet)
अणु
	u16 type;
	__be32 ip_dst;
	काष्ठा batadv_dat_entry *dat_entry = शून्य;
	bool ret = false;
	पूर्णांक hdr_size = माप(काष्ठा batadv_bcast_packet);
	अचिन्हित लघु vid;

	अगर (!atomic_पढ़ो(&bat_priv->distributed_arp_table))
		जाओ out;

	/* If this packet is an ARP_REQUEST and the node alपढ़ोy has the
	 * inक्रमmation that it is going to ask, then the packet can be dropped
	 */
	अगर (batadv_क्रमw_packet_is_rebroadcast(क्रमw_packet))
		जाओ out;

	vid = batadv_dat_get_vid(क्रमw_packet->skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, क्रमw_packet->skb, hdr_size);
	अगर (type != ARPOP_REQUEST)
		जाओ out;

	ip_dst = batadv_arp_ip_dst(क्रमw_packet->skb, hdr_size);
	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip_dst, vid);
	/* check अगर the node alपढ़ोy got this entry */
	अगर (!dat_entry) अणु
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "ARP Request for %pI4: fallback\n", &ip_dst);
		जाओ out;
	पूर्ण

	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "ARP Request for %pI4: fallback prevented\n", &ip_dst);
	ret = true;

out:
	अगर (dat_entry)
		batadv_dat_entry_put(dat_entry);
	वापस ret;
पूर्ण

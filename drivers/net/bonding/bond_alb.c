<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_bonding.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <net/ipx.h>
#समावेश <net/arp.h>
#समावेश <net/ipv6.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <net/bonding.h>
#समावेश <net/bond_alb.h>

अटल स्थिर u8 mac_v6_allmcast[ETH_ALEN + 2] __दीर्घ_aligned = अणु
	0x33, 0x33, 0x00, 0x00, 0x00, 0x01
पूर्ण;
अटल स्थिर पूर्णांक alb_delta_in_ticks = HZ / ALB_TIMER_TICKS_PER_SEC;

#आशय pack(1)
काष्ठा learning_pkt अणु
	u8 mac_dst[ETH_ALEN];
	u8 mac_src[ETH_ALEN];
	__be16 type;
	u8 padding[ETH_ZLEN - ETH_HLEN];
पूर्ण;

काष्ठा arp_pkt अणु
	__be16  hw_addr_space;
	__be16  prot_addr_space;
	u8      hw_addr_len;
	u8      prot_addr_len;
	__be16  op_code;
	u8      mac_src[ETH_ALEN];	/* sender hardware address */
	__be32  ip_src;			/* sender IP address */
	u8      mac_dst[ETH_ALEN];	/* target hardware address */
	__be32  ip_dst;			/* target IP address */
पूर्ण;
#आशय pack()

/* Forward declaration */
अटल व्योम alb_send_learning_packets(काष्ठा slave *slave, u8 mac_addr[],
				      bool strict_match);
अटल व्योम rlb_purge_src_ip(काष्ठा bonding *bond, काष्ठा arp_pkt *arp);
अटल व्योम rlb_src_unlink(काष्ठा bonding *bond, u32 index);
अटल व्योम rlb_src_link(काष्ठा bonding *bond, u32 ip_src_hash,
			 u32 ip_dst_hash);

अटल अंतरभूत u8 _simple_hash(स्थिर u8 *hash_start, पूर्णांक hash_size)
अणु
	पूर्णांक i;
	u8 hash = 0;

	क्रम (i = 0; i < hash_size; i++)
		hash ^= hash_start[i];

	वापस hash;
पूर्ण

/*********************** tlb specअगरic functions ***************************/

अटल अंतरभूत व्योम tlb_init_table_entry(काष्ठा tlb_client_info *entry, पूर्णांक save_load)
अणु
	अगर (save_load) अणु
		entry->load_history = 1 + entry->tx_bytes /
				      BOND_TLB_REBALANCE_INTERVAL;
		entry->tx_bytes = 0;
	पूर्ण

	entry->tx_slave = शून्य;
	entry->next = TLB_शून्य_INDEX;
	entry->prev = TLB_शून्य_INDEX;
पूर्ण

अटल अंतरभूत व्योम tlb_init_slave(काष्ठा slave *slave)
अणु
	SLAVE_TLB_INFO(slave).load = 0;
	SLAVE_TLB_INFO(slave).head = TLB_शून्य_INDEX;
पूर्ण

अटल व्योम __tlb_clear_slave(काष्ठा bonding *bond, काष्ठा slave *slave,
			 पूर्णांक save_load)
अणु
	काष्ठा tlb_client_info *tx_hash_table;
	u32 index;

	/* clear slave from tx_hashtbl */
	tx_hash_table = BOND_ALB_INFO(bond).tx_hashtbl;

	/* skip this अगर we've alपढ़ोy मुक्तd the tx hash table */
	अगर (tx_hash_table) अणु
		index = SLAVE_TLB_INFO(slave).head;
		जबतक (index != TLB_शून्य_INDEX) अणु
			u32 next_index = tx_hash_table[index].next;
			tlb_init_table_entry(&tx_hash_table[index], save_load);
			index = next_index;
		पूर्ण
	पूर्ण

	tlb_init_slave(slave);
पूर्ण

अटल व्योम tlb_clear_slave(काष्ठा bonding *bond, काष्ठा slave *slave,
			 पूर्णांक save_load)
अणु
	spin_lock_bh(&bond->mode_lock);
	__tlb_clear_slave(bond, slave, save_load);
	spin_unlock_bh(&bond->mode_lock);
पूर्ण

/* Must be called beक्रमe starting the monitor समयr */
अटल पूर्णांक tlb_initialize(काष्ठा bonding *bond)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	पूर्णांक size = TLB_HASH_TABLE_SIZE * माप(काष्ठा tlb_client_info);
	काष्ठा tlb_client_info *new_hashtbl;
	पूर्णांक i;

	new_hashtbl = kzalloc(size, GFP_KERNEL);
	अगर (!new_hashtbl)
		वापस -ENOMEM;

	spin_lock_bh(&bond->mode_lock);

	bond_info->tx_hashtbl = new_hashtbl;

	क्रम (i = 0; i < TLB_HASH_TABLE_SIZE; i++)
		tlb_init_table_entry(&bond_info->tx_hashtbl[i], 0);

	spin_unlock_bh(&bond->mode_lock);

	वापस 0;
पूर्ण

/* Must be called only after all slaves have been released */
अटल व्योम tlb_deinitialize(काष्ठा bonding *bond)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));

	spin_lock_bh(&bond->mode_lock);

	kमुक्त(bond_info->tx_hashtbl);
	bond_info->tx_hashtbl = शून्य;

	spin_unlock_bh(&bond->mode_lock);
पूर्ण

अटल दीर्घ दीर्घ compute_gap(काष्ठा slave *slave)
अणु
	वापस (s64) (slave->speed << 20) - /* Convert to Megabit per sec */
	       (s64) (SLAVE_TLB_INFO(slave).load << 3); /* Bytes to bits */
पूर्ण

अटल काष्ठा slave *tlb_get_least_loaded_slave(काष्ठा bonding *bond)
अणु
	काष्ठा slave *slave, *least_loaded;
	काष्ठा list_head *iter;
	दीर्घ दीर्घ max_gap;

	least_loaded = शून्य;
	max_gap = Lदीर्घ_न्यून;

	/* Find the slave with the largest gap */
	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (bond_slave_can_tx(slave)) अणु
			दीर्घ दीर्घ gap = compute_gap(slave);

			अगर (max_gap < gap) अणु
				least_loaded = slave;
				max_gap = gap;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस least_loaded;
पूर्ण

अटल काष्ठा slave *__tlb_choose_channel(काष्ठा bonding *bond, u32 hash_index,
						u32 skb_len)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा tlb_client_info *hash_table;
	काष्ठा slave *asचिन्हित_slave;

	hash_table = bond_info->tx_hashtbl;
	asचिन्हित_slave = hash_table[hash_index].tx_slave;
	अगर (!asचिन्हित_slave) अणु
		asचिन्हित_slave = tlb_get_least_loaded_slave(bond);

		अगर (asचिन्हित_slave) अणु
			काष्ठा tlb_slave_info *slave_info =
				&(SLAVE_TLB_INFO(asचिन्हित_slave));
			u32 next_index = slave_info->head;

			hash_table[hash_index].tx_slave = asचिन्हित_slave;
			hash_table[hash_index].next = next_index;
			hash_table[hash_index].prev = TLB_शून्य_INDEX;

			अगर (next_index != TLB_शून्य_INDEX)
				hash_table[next_index].prev = hash_index;

			slave_info->head = hash_index;
			slave_info->load +=
				hash_table[hash_index].load_history;
		पूर्ण
	पूर्ण

	अगर (asचिन्हित_slave)
		hash_table[hash_index].tx_bytes += skb_len;

	वापस asचिन्हित_slave;
पूर्ण

अटल काष्ठा slave *tlb_choose_channel(काष्ठा bonding *bond, u32 hash_index,
					u32 skb_len)
अणु
	काष्ठा slave *tx_slave;

	/* We करोn't need to disable softirq here, beहाल
	 * tlb_choose_channel() is only called by bond_alb_xmit()
	 * which alपढ़ोy has softirq disabled.
	 */
	spin_lock(&bond->mode_lock);
	tx_slave = __tlb_choose_channel(bond, hash_index, skb_len);
	spin_unlock(&bond->mode_lock);

	वापस tx_slave;
पूर्ण

/*********************** rlb specअगरic functions ***************************/

/* when an ARP REPLY is received from a client update its info
 * in the rx_hashtbl
 */
अटल व्योम rlb_update_entry_from_arp(काष्ठा bonding *bond, काष्ठा arp_pkt *arp)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा rlb_client_info *client_info;
	u32 hash_index;

	spin_lock_bh(&bond->mode_lock);

	hash_index = _simple_hash((u8 *)&(arp->ip_src), माप(arp->ip_src));
	client_info = &(bond_info->rx_hashtbl[hash_index]);

	अगर ((client_info->asचिन्हित) &&
	    (client_info->ip_src == arp->ip_dst) &&
	    (client_info->ip_dst == arp->ip_src) &&
	    (!ether_addr_equal_64bits(client_info->mac_dst, arp->mac_src))) अणु
		/* update the clients MAC address */
		ether_addr_copy(client_info->mac_dst, arp->mac_src);
		client_info->ntt = 1;
		bond_info->rx_ntt = 1;
	पूर्ण

	spin_unlock_bh(&bond->mode_lock);
पूर्ण

अटल पूर्णांक rlb_arp_recv(स्थिर काष्ठा sk_buff *skb, काष्ठा bonding *bond,
			काष्ठा slave *slave)
अणु
	काष्ठा arp_pkt *arp, _arp;

	अगर (skb->protocol != cpu_to_be16(ETH_P_ARP))
		जाओ out;

	arp = skb_header_poपूर्णांकer(skb, 0, माप(_arp), &_arp);
	अगर (!arp)
		जाओ out;

	/* We received an ARP from arp->ip_src.
	 * We might have used this IP address previously (on the bonding host
	 * itself or on a प्रणाली that is bridged together with the bond).
	 * However, अगर arp->mac_src is dअगरferent than what is stored in
	 * rx_hashtbl, some other host is now using the IP and we must prevent
	 * sending out client updates with this IP address and the old MAC
	 * address.
	 * Clean up all hash table entries that have this address as ip_src but
	 * have a dअगरferent mac_src.
	 */
	rlb_purge_src_ip(bond, arp);

	अगर (arp->op_code == htons(ARPOP_REPLY)) अणु
		/* update rx hash table क्रम this ARP */
		rlb_update_entry_from_arp(bond, arp);
		slave_dbg(bond->dev, slave->dev, "Server received an ARP Reply from client\n");
	पूर्ण
out:
	वापस RX_HANDLER_ANOTHER;
पूर्ण

/* Caller must hold rcu_पढ़ो_lock() */
अटल काष्ठा slave *__rlb_next_rx_slave(काष्ठा bonding *bond)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा slave *beक्रमe = शून्य, *rx_slave = शून्य, *slave;
	काष्ठा list_head *iter;
	bool found = false;

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (!bond_slave_can_tx(slave))
			जारी;
		अगर (!found) अणु
			अगर (!beक्रमe || beक्रमe->speed < slave->speed)
				beक्रमe = slave;
		पूर्ण अन्यथा अणु
			अगर (!rx_slave || rx_slave->speed < slave->speed)
				rx_slave = slave;
		पूर्ण
		अगर (slave == bond_info->rx_slave)
			found = true;
	पूर्ण
	/* we didn't find anything after the current or we have something
	 * better beक्रमe and up to the current slave
	 */
	अगर (!rx_slave || (beक्रमe && rx_slave->speed < beक्रमe->speed))
		rx_slave = beक्रमe;

	अगर (rx_slave)
		bond_info->rx_slave = rx_slave;

	वापस rx_slave;
पूर्ण

/* Caller must hold RTNL, rcu_पढ़ो_lock is obtained only to silence checkers */
अटल काष्ठा slave *rlb_next_rx_slave(काष्ठा bonding *bond)
अणु
	काष्ठा slave *rx_slave;

	ASSERT_RTNL();

	rcu_पढ़ो_lock();
	rx_slave = __rlb_next_rx_slave(bond);
	rcu_पढ़ो_unlock();

	वापस rx_slave;
पूर्ण

/* teach the चयन the mac of a disabled slave
 * on the primary क्रम fault tolerance
 *
 * Caller must hold RTNL
 */
अटल व्योम rlb_teach_disabled_mac_on_primary(काष्ठा bonding *bond, u8 addr[])
अणु
	काष्ठा slave *curr_active = rtnl_dereference(bond->curr_active_slave);

	अगर (!curr_active)
		वापस;

	अगर (!bond->alb_info.primary_is_promisc) अणु
		अगर (!dev_set_promiscuity(curr_active->dev, 1))
			bond->alb_info.primary_is_promisc = 1;
		अन्यथा
			bond->alb_info.primary_is_promisc = 0;
	पूर्ण

	bond->alb_info.rlb_promisc_समयout_counter = 0;

	alb_send_learning_packets(curr_active, addr, true);
पूर्ण

/* slave being हटाओd should not be active at this poपूर्णांक
 *
 * Caller must hold rtnl.
 */
अटल व्योम rlb_clear_slave(काष्ठा bonding *bond, काष्ठा slave *slave)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा rlb_client_info *rx_hash_table;
	u32 index, next_index;

	/* clear slave from rx_hashtbl */
	spin_lock_bh(&bond->mode_lock);

	rx_hash_table = bond_info->rx_hashtbl;
	index = bond_info->rx_hashtbl_used_head;
	क्रम (; index != RLB_शून्य_INDEX; index = next_index) अणु
		next_index = rx_hash_table[index].used_next;
		अगर (rx_hash_table[index].slave == slave) अणु
			काष्ठा slave *asचिन्हित_slave = rlb_next_rx_slave(bond);

			अगर (asचिन्हित_slave) अणु
				rx_hash_table[index].slave = asचिन्हित_slave;
				अगर (is_valid_ether_addr(rx_hash_table[index].mac_dst)) अणु
					bond_info->rx_hashtbl[index].ntt = 1;
					bond_info->rx_ntt = 1;
					/* A slave has been हटाओd from the
					 * table because it is either disabled
					 * or being released. We must retry the
					 * update to aव्योम clients from not
					 * being updated & disconnecting when
					 * there is stress
					 */
					bond_info->rlb_update_retry_counter =
						RLB_UPDATE_RETRY;
				पूर्ण
			पूर्ण अन्यथा अणु  /* there is no active slave */
				rx_hash_table[index].slave = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&bond->mode_lock);

	अगर (slave != rtnl_dereference(bond->curr_active_slave))
		rlb_teach_disabled_mac_on_primary(bond, slave->dev->dev_addr);
पूर्ण

अटल व्योम rlb_update_client(काष्ठा rlb_client_info *client_info)
अणु
	पूर्णांक i;

	अगर (!client_info->slave || !is_valid_ether_addr(client_info->mac_dst))
		वापस;

	क्रम (i = 0; i < RLB_ARP_BURST_SIZE; i++) अणु
		काष्ठा sk_buff *skb;

		skb = arp_create(ARPOP_REPLY, ETH_P_ARP,
				 client_info->ip_dst,
				 client_info->slave->dev,
				 client_info->ip_src,
				 client_info->mac_dst,
				 client_info->slave->dev->dev_addr,
				 client_info->mac_dst);
		अगर (!skb) अणु
			slave_err(client_info->slave->bond->dev,
				  client_info->slave->dev,
				  "failed to create an ARP packet\n");
			जारी;
		पूर्ण

		skb->dev = client_info->slave->dev;

		अगर (client_info->vlan_id) अणु
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       client_info->vlan_id);
		पूर्ण

		arp_xmit(skb);
	पूर्ण
पूर्ण

/* sends ARP REPLIES that update the clients that need updating */
अटल व्योम rlb_update_rx_clients(काष्ठा bonding *bond)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा rlb_client_info *client_info;
	u32 hash_index;

	spin_lock_bh(&bond->mode_lock);

	hash_index = bond_info->rx_hashtbl_used_head;
	क्रम (; hash_index != RLB_शून्य_INDEX;
	     hash_index = client_info->used_next) अणु
		client_info = &(bond_info->rx_hashtbl[hash_index]);
		अगर (client_info->ntt) अणु
			rlb_update_client(client_info);
			अगर (bond_info->rlb_update_retry_counter == 0)
				client_info->ntt = 0;
		पूर्ण
	पूर्ण

	/* करो not update the entries again until this counter is zero so that
	 * not to confuse the clients.
	 */
	bond_info->rlb_update_delay_counter = RLB_UPDATE_DELAY;

	spin_unlock_bh(&bond->mode_lock);
पूर्ण

/* The slave was asचिन्हित a new mac address - update the clients */
अटल व्योम rlb_req_update_slave_clients(काष्ठा bonding *bond, काष्ठा slave *slave)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा rlb_client_info *client_info;
	पूर्णांक ntt = 0;
	u32 hash_index;

	spin_lock_bh(&bond->mode_lock);

	hash_index = bond_info->rx_hashtbl_used_head;
	क्रम (; hash_index != RLB_शून्य_INDEX;
	     hash_index = client_info->used_next) अणु
		client_info = &(bond_info->rx_hashtbl[hash_index]);

		अगर ((client_info->slave == slave) &&
		    is_valid_ether_addr(client_info->mac_dst)) अणु
			client_info->ntt = 1;
			ntt = 1;
		पूर्ण
	पूर्ण

	/* update the team's flag only after the whole iteration */
	अगर (ntt) अणु
		bond_info->rx_ntt = 1;
		/* fasten the change */
		bond_info->rlb_update_retry_counter = RLB_UPDATE_RETRY;
	पूर्ण

	spin_unlock_bh(&bond->mode_lock);
पूर्ण

/* mark all clients using src_ip to be updated */
अटल व्योम rlb_req_update_subnet_clients(काष्ठा bonding *bond, __be32 src_ip)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा rlb_client_info *client_info;
	u32 hash_index;

	spin_lock(&bond->mode_lock);

	hash_index = bond_info->rx_hashtbl_used_head;
	क्रम (; hash_index != RLB_शून्य_INDEX;
	     hash_index = client_info->used_next) अणु
		client_info = &(bond_info->rx_hashtbl[hash_index]);

		अगर (!client_info->slave) अणु
			netdev_err(bond->dev, "found a client with no channel in the client's hash table\n");
			जारी;
		पूर्ण
		/* update all clients using this src_ip, that are not asचिन्हित
		 * to the team's address (curr_active_slave) and have a known
		 * unicast mac address.
		 */
		अगर ((client_info->ip_src == src_ip) &&
		    !ether_addr_equal_64bits(client_info->slave->dev->dev_addr,
					     bond->dev->dev_addr) &&
		    is_valid_ether_addr(client_info->mac_dst)) अणु
			client_info->ntt = 1;
			bond_info->rx_ntt = 1;
		पूर्ण
	पूर्ण

	spin_unlock(&bond->mode_lock);
पूर्ण

अटल काष्ठा slave *rlb_choose_channel(काष्ठा sk_buff *skb,
					काष्ठा bonding *bond,
					स्थिर काष्ठा arp_pkt *arp)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा slave *asचिन्हित_slave, *curr_active_slave;
	काष्ठा rlb_client_info *client_info;
	u32 hash_index = 0;

	spin_lock(&bond->mode_lock);

	curr_active_slave = rcu_dereference(bond->curr_active_slave);

	hash_index = _simple_hash((u8 *)&arp->ip_dst, माप(arp->ip_dst));
	client_info = &(bond_info->rx_hashtbl[hash_index]);

	अगर (client_info->asचिन्हित) अणु
		अगर ((client_info->ip_src == arp->ip_src) &&
		    (client_info->ip_dst == arp->ip_dst)) अणु
			/* the entry is alपढ़ोy asचिन्हित to this client */
			अगर (!is_broadcast_ether_addr(arp->mac_dst)) अणु
				/* update mac address from arp */
				ether_addr_copy(client_info->mac_dst, arp->mac_dst);
			पूर्ण
			ether_addr_copy(client_info->mac_src, arp->mac_src);

			asचिन्हित_slave = client_info->slave;
			अगर (asचिन्हित_slave) अणु
				spin_unlock(&bond->mode_lock);
				वापस asचिन्हित_slave;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* the entry is alपढ़ोy asचिन्हित to some other client,
			 * move the old client to primary (curr_active_slave) so
			 * that the new client can be asचिन्हित to this entry.
			 */
			अगर (curr_active_slave &&
			    client_info->slave != curr_active_slave) अणु
				client_info->slave = curr_active_slave;
				rlb_update_client(client_info);
			पूर्ण
		पूर्ण
	पूर्ण
	/* assign a new slave */
	asचिन्हित_slave = __rlb_next_rx_slave(bond);

	अगर (asचिन्हित_slave) अणु
		अगर (!(client_info->asचिन्हित &&
		      client_info->ip_src == arp->ip_src)) अणु
			/* ip_src is going to be updated,
			 * fix the src hash list
			 */
			u32 hash_src = _simple_hash((u8 *)&arp->ip_src,
						    माप(arp->ip_src));
			rlb_src_unlink(bond, hash_index);
			rlb_src_link(bond, hash_src, hash_index);
		पूर्ण

		client_info->ip_src = arp->ip_src;
		client_info->ip_dst = arp->ip_dst;
		/* arp->mac_dst is broadcast क्रम arp reqeusts.
		 * will be updated with clients actual unicast mac address
		 * upon receiving an arp reply.
		 */
		ether_addr_copy(client_info->mac_dst, arp->mac_dst);
		ether_addr_copy(client_info->mac_src, arp->mac_src);
		client_info->slave = asचिन्हित_slave;

		अगर (is_valid_ether_addr(client_info->mac_dst)) अणु
			client_info->ntt = 1;
			bond->alb_info.rx_ntt = 1;
		पूर्ण अन्यथा अणु
			client_info->ntt = 0;
		पूर्ण

		अगर (vlan_get_tag(skb, &client_info->vlan_id))
			client_info->vlan_id = 0;

		अगर (!client_info->asचिन्हित) अणु
			u32 prev_tbl_head = bond_info->rx_hashtbl_used_head;
			bond_info->rx_hashtbl_used_head = hash_index;
			client_info->used_next = prev_tbl_head;
			अगर (prev_tbl_head != RLB_शून्य_INDEX) अणु
				bond_info->rx_hashtbl[prev_tbl_head].used_prev =
					hash_index;
			पूर्ण
			client_info->asचिन्हित = 1;
		पूर्ण
	पूर्ण

	spin_unlock(&bond->mode_lock);

	वापस asचिन्हित_slave;
पूर्ण

/* chooses (and वापसs) transmit channel क्रम arp reply
 * करोes not choose channel क्रम other arp types since they are
 * sent on the curr_active_slave
 */
अटल काष्ठा slave *rlb_arp_xmit(काष्ठा sk_buff *skb, काष्ठा bonding *bond)
अणु
	काष्ठा slave *tx_slave = शून्य;
	काष्ठा arp_pkt *arp;

	अगर (!pskb_network_may_pull(skb, माप(*arp)))
		वापस शून्य;
	arp = (काष्ठा arp_pkt *)skb_network_header(skb);

	/* Don't modअगरy or load balance ARPs that करो not originate locally
	 * (e.g.,arrive via a bridge).
	 */
	अगर (!bond_slave_has_mac_rx(bond, arp->mac_src))
		वापस शून्य;

	अगर (arp->op_code == htons(ARPOP_REPLY)) अणु
		/* the arp must be sent on the selected rx channel */
		tx_slave = rlb_choose_channel(skb, bond, arp);
		अगर (tx_slave)
			bond_hw_addr_copy(arp->mac_src, tx_slave->dev->dev_addr,
					  tx_slave->dev->addr_len);
		netdev_dbg(bond->dev, "(slave %s): Server sent ARP Reply packet\n",
			   tx_slave ? tx_slave->dev->name : "NULL");
	पूर्ण अन्यथा अगर (arp->op_code == htons(ARPOP_REQUEST)) अणु
		/* Create an entry in the rx_hashtbl क्रम this client as a
		 * place holder.
		 * When the arp reply is received the entry will be updated
		 * with the correct unicast address of the client.
		 */
		tx_slave = rlb_choose_channel(skb, bond, arp);

		/* The ARP reply packets must be delayed so that
		 * they can cancel out the influence of the ARP request.
		 */
		bond->alb_info.rlb_update_delay_counter = RLB_UPDATE_DELAY;

		/* arp requests are broadcast and are sent on the primary
		 * the arp request will collapse all clients on the subnet to
		 * the primary slave. We must रेजिस्टर these clients to be
		 * updated with their asचिन्हित mac.
		 */
		rlb_req_update_subnet_clients(bond, arp->ip_src);
		netdev_dbg(bond->dev, "(slave %s): Server sent ARP Request packet\n",
			   tx_slave ? tx_slave->dev->name : "NULL");
	पूर्ण

	वापस tx_slave;
पूर्ण

अटल व्योम rlb_rebalance(काष्ठा bonding *bond)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा slave *asचिन्हित_slave;
	काष्ठा rlb_client_info *client_info;
	पूर्णांक ntt;
	u32 hash_index;

	spin_lock_bh(&bond->mode_lock);

	ntt = 0;
	hash_index = bond_info->rx_hashtbl_used_head;
	क्रम (; hash_index != RLB_शून्य_INDEX;
	     hash_index = client_info->used_next) अणु
		client_info = &(bond_info->rx_hashtbl[hash_index]);
		asचिन्हित_slave = __rlb_next_rx_slave(bond);
		अगर (asचिन्हित_slave && (client_info->slave != asचिन्हित_slave)) अणु
			client_info->slave = asचिन्हित_slave;
			अगर (!is_zero_ether_addr(client_info->mac_dst)) अणु
				client_info->ntt = 1;
				ntt = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* update the team's flag only after the whole iteration */
	अगर (ntt)
		bond_info->rx_ntt = 1;
	spin_unlock_bh(&bond->mode_lock);
पूर्ण

/* Caller must hold mode_lock */
अटल व्योम rlb_init_table_entry_dst(काष्ठा rlb_client_info *entry)
अणु
	entry->used_next = RLB_शून्य_INDEX;
	entry->used_prev = RLB_शून्य_INDEX;
	entry->asचिन्हित = 0;
	entry->slave = शून्य;
	entry->vlan_id = 0;
पूर्ण
अटल व्योम rlb_init_table_entry_src(काष्ठा rlb_client_info *entry)
अणु
	entry->src_first = RLB_शून्य_INDEX;
	entry->src_prev = RLB_शून्य_INDEX;
	entry->src_next = RLB_शून्य_INDEX;
पूर्ण

अटल व्योम rlb_init_table_entry(काष्ठा rlb_client_info *entry)
अणु
	स_रखो(entry, 0, माप(काष्ठा rlb_client_info));
	rlb_init_table_entry_dst(entry);
	rlb_init_table_entry_src(entry);
पूर्ण

अटल व्योम rlb_delete_table_entry_dst(काष्ठा bonding *bond, u32 index)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	u32 next_index = bond_info->rx_hashtbl[index].used_next;
	u32 prev_index = bond_info->rx_hashtbl[index].used_prev;

	अगर (index == bond_info->rx_hashtbl_used_head)
		bond_info->rx_hashtbl_used_head = next_index;
	अगर (prev_index != RLB_शून्य_INDEX)
		bond_info->rx_hashtbl[prev_index].used_next = next_index;
	अगर (next_index != RLB_शून्य_INDEX)
		bond_info->rx_hashtbl[next_index].used_prev = prev_index;
पूर्ण

/* unlink a rlb hash table entry from the src list */
अटल व्योम rlb_src_unlink(काष्ठा bonding *bond, u32 index)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	u32 next_index = bond_info->rx_hashtbl[index].src_next;
	u32 prev_index = bond_info->rx_hashtbl[index].src_prev;

	bond_info->rx_hashtbl[index].src_next = RLB_शून्य_INDEX;
	bond_info->rx_hashtbl[index].src_prev = RLB_शून्य_INDEX;

	अगर (next_index != RLB_शून्य_INDEX)
		bond_info->rx_hashtbl[next_index].src_prev = prev_index;

	अगर (prev_index == RLB_शून्य_INDEX)
		वापस;

	/* is prev_index poपूर्णांकing to the head of this list? */
	अगर (bond_info->rx_hashtbl[prev_index].src_first == index)
		bond_info->rx_hashtbl[prev_index].src_first = next_index;
	अन्यथा
		bond_info->rx_hashtbl[prev_index].src_next = next_index;

पूर्ण

अटल व्योम rlb_delete_table_entry(काष्ठा bonding *bond, u32 index)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा rlb_client_info *entry = &(bond_info->rx_hashtbl[index]);

	rlb_delete_table_entry_dst(bond, index);
	rlb_init_table_entry_dst(entry);

	rlb_src_unlink(bond, index);
पूर्ण

/* add the rx_hashtbl[ip_dst_hash] entry to the list
 * of entries with identical ip_src_hash
 */
अटल व्योम rlb_src_link(काष्ठा bonding *bond, u32 ip_src_hash, u32 ip_dst_hash)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	u32 next;

	bond_info->rx_hashtbl[ip_dst_hash].src_prev = ip_src_hash;
	next = bond_info->rx_hashtbl[ip_src_hash].src_first;
	bond_info->rx_hashtbl[ip_dst_hash].src_next = next;
	अगर (next != RLB_शून्य_INDEX)
		bond_info->rx_hashtbl[next].src_prev = ip_dst_hash;
	bond_info->rx_hashtbl[ip_src_hash].src_first = ip_dst_hash;
पूर्ण

/* deletes all rx_hashtbl entries with arp->ip_src अगर their mac_src करोes
 * not match arp->mac_src
 */
अटल व्योम rlb_purge_src_ip(काष्ठा bonding *bond, काष्ठा arp_pkt *arp)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	u32 ip_src_hash = _simple_hash((u8 *)&(arp->ip_src), माप(arp->ip_src));
	u32 index;

	spin_lock_bh(&bond->mode_lock);

	index = bond_info->rx_hashtbl[ip_src_hash].src_first;
	जबतक (index != RLB_शून्य_INDEX) अणु
		काष्ठा rlb_client_info *entry = &(bond_info->rx_hashtbl[index]);
		u32 next_index = entry->src_next;
		अगर (entry->ip_src == arp->ip_src &&
		    !ether_addr_equal_64bits(arp->mac_src, entry->mac_src))
				rlb_delete_table_entry(bond, index);
		index = next_index;
	पूर्ण
	spin_unlock_bh(&bond->mode_lock);
पूर्ण

अटल पूर्णांक rlb_initialize(काष्ठा bonding *bond)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा rlb_client_info	*new_hashtbl;
	पूर्णांक size = RLB_HASH_TABLE_SIZE * माप(काष्ठा rlb_client_info);
	पूर्णांक i;

	new_hashtbl = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!new_hashtbl)
		वापस -1;

	spin_lock_bh(&bond->mode_lock);

	bond_info->rx_hashtbl = new_hashtbl;

	bond_info->rx_hashtbl_used_head = RLB_शून्य_INDEX;

	क्रम (i = 0; i < RLB_HASH_TABLE_SIZE; i++)
		rlb_init_table_entry(bond_info->rx_hashtbl + i);

	spin_unlock_bh(&bond->mode_lock);

	/* रेजिस्टर to receive ARPs */
	bond->recv_probe = rlb_arp_recv;

	वापस 0;
पूर्ण

अटल व्योम rlb_deinitialize(काष्ठा bonding *bond)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));

	spin_lock_bh(&bond->mode_lock);

	kमुक्त(bond_info->rx_hashtbl);
	bond_info->rx_hashtbl = शून्य;
	bond_info->rx_hashtbl_used_head = RLB_शून्य_INDEX;

	spin_unlock_bh(&bond->mode_lock);
पूर्ण

अटल व्योम rlb_clear_vlan(काष्ठा bonding *bond, अचिन्हित लघु vlan_id)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	u32 curr_index;

	spin_lock_bh(&bond->mode_lock);

	curr_index = bond_info->rx_hashtbl_used_head;
	जबतक (curr_index != RLB_शून्य_INDEX) अणु
		काष्ठा rlb_client_info *curr = &(bond_info->rx_hashtbl[curr_index]);
		u32 next_index = bond_info->rx_hashtbl[curr_index].used_next;

		अगर (curr->vlan_id == vlan_id)
			rlb_delete_table_entry(bond, curr_index);

		curr_index = next_index;
	पूर्ण

	spin_unlock_bh(&bond->mode_lock);
पूर्ण

/*********************** tlb/rlb shared functions *********************/

अटल व्योम alb_send_lp_vid(काष्ठा slave *slave, u8 mac_addr[],
			    __be16 vlan_proto, u16 vid)
अणु
	काष्ठा learning_pkt pkt;
	काष्ठा sk_buff *skb;
	पूर्णांक size = माप(काष्ठा learning_pkt);

	स_रखो(&pkt, 0, size);
	ether_addr_copy(pkt.mac_dst, mac_addr);
	ether_addr_copy(pkt.mac_src, mac_addr);
	pkt.type = cpu_to_be16(ETH_P_LOOPBACK);

	skb = dev_alloc_skb(size);
	अगर (!skb)
		वापस;

	skb_put_data(skb, &pkt, size);

	skb_reset_mac_header(skb);
	skb->network_header = skb->mac_header + ETH_HLEN;
	skb->protocol = pkt.type;
	skb->priority = TC_PRIO_CONTROL;
	skb->dev = slave->dev;

	slave_dbg(slave->bond->dev, slave->dev,
		  "Send learning packet: mac %pM vlan %d\n", mac_addr, vid);

	अगर (vid)
		__vlan_hwaccel_put_tag(skb, vlan_proto, vid);

	dev_queue_xmit(skb);
पूर्ण

काष्ठा alb_walk_data अणु
	काष्ठा bonding *bond;
	काष्ठा slave *slave;
	u8 *mac_addr;
	bool strict_match;
पूर्ण;

अटल पूर्णांक alb_upper_dev_walk(काष्ठा net_device *upper,
			      काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा alb_walk_data *data = (काष्ठा alb_walk_data *)priv->data;
	bool strict_match = data->strict_match;
	काष्ठा bonding *bond = data->bond;
	काष्ठा slave *slave = data->slave;
	u8 *mac_addr = data->mac_addr;
	काष्ठा bond_vlan_tag *tags;

	अगर (is_vlan_dev(upper) &&
	    bond->dev->lower_level == upper->lower_level - 1) अणु
		अगर (upper->addr_assign_type == NET_ADDR_STOLEN) अणु
			alb_send_lp_vid(slave, mac_addr,
					vlan_dev_vlan_proto(upper),
					vlan_dev_vlan_id(upper));
		पूर्ण अन्यथा अणु
			alb_send_lp_vid(slave, upper->dev_addr,
					vlan_dev_vlan_proto(upper),
					vlan_dev_vlan_id(upper));
		पूर्ण
	पूर्ण

	/* If this is a macvlan device, then only send updates
	 * when strict_match is turned off.
	 */
	अगर (netअगर_is_macvlan(upper) && !strict_match) अणु
		tags = bond_verअगरy_device_path(bond->dev, upper, 0);
		अगर (IS_ERR_OR_शून्य(tags))
			BUG();
		alb_send_lp_vid(slave, upper->dev_addr,
				tags[0].vlan_proto, tags[0].vlan_id);
		kमुक्त(tags);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम alb_send_learning_packets(काष्ठा slave *slave, u8 mac_addr[],
				      bool strict_match)
अणु
	काष्ठा bonding *bond = bond_get_bond_by_slave(slave);
	काष्ठा netdev_nested_priv priv;
	काष्ठा alb_walk_data data = अणु
		.strict_match = strict_match,
		.mac_addr = mac_addr,
		.slave = slave,
		.bond = bond,
	पूर्ण;

	priv.data = (व्योम *)&data;
	/* send untagged */
	alb_send_lp_vid(slave, mac_addr, 0, 0);

	/* loop through all devices and see अगर we need to send a packet
	 * क्रम that device.
	 */
	rcu_पढ़ो_lock();
	netdev_walk_all_upper_dev_rcu(bond->dev, alb_upper_dev_walk, &priv);
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक alb_set_slave_mac_addr(काष्ठा slave *slave, u8 addr[],
				  अचिन्हित पूर्णांक len)
अणु
	काष्ठा net_device *dev = slave->dev;
	काष्ठा sockaddr_storage ss;

	अगर (BOND_MODE(slave->bond) == BOND_MODE_TLB) अणु
		स_नकल(dev->dev_addr, addr, len);
		वापस 0;
	पूर्ण

	/* क्रम rlb each slave must have a unique hw mac addresses so that
	 * each slave will receive packets destined to a dअगरferent mac
	 */
	स_नकल(ss.__data, addr, len);
	ss.ss_family = dev->type;
	अगर (dev_set_mac_address(dev, (काष्ठा sockaddr *)&ss, शून्य)) अणु
		slave_err(slave->bond->dev, dev, "dev_set_mac_address on slave failed! ALB mode requires that the base driver support setting the hw address also when the network device's interface is open\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/* Swap MAC addresses between two slaves.
 *
 * Called with RTNL held, and no other locks.
 */
अटल व्योम alb_swap_mac_addr(काष्ठा slave *slave1, काष्ठा slave *slave2)
अणु
	u8 पंचांगp_mac_addr[MAX_ADDR_LEN];

	bond_hw_addr_copy(पंचांगp_mac_addr, slave1->dev->dev_addr,
			  slave1->dev->addr_len);
	alb_set_slave_mac_addr(slave1, slave2->dev->dev_addr,
			       slave2->dev->addr_len);
	alb_set_slave_mac_addr(slave2, पंचांगp_mac_addr,
			       slave1->dev->addr_len);

पूर्ण

/* Send learning packets after MAC address swap.
 *
 * Called with RTNL and no other locks
 */
अटल व्योम alb_fasten_mac_swap(काष्ठा bonding *bond, काष्ठा slave *slave1,
				काष्ठा slave *slave2)
अणु
	पूर्णांक slaves_state_dअगरfer = (bond_slave_can_tx(slave1) != bond_slave_can_tx(slave2));
	काष्ठा slave *disabled_slave = शून्य;

	ASSERT_RTNL();

	/* fasten the change in the चयन */
	अगर (bond_slave_can_tx(slave1)) अणु
		alb_send_learning_packets(slave1, slave1->dev->dev_addr, false);
		अगर (bond->alb_info.rlb_enabled) अणु
			/* inक्रमm the clients that the mac address
			 * has changed
			 */
			rlb_req_update_slave_clients(bond, slave1);
		पूर्ण
	पूर्ण अन्यथा अणु
		disabled_slave = slave1;
	पूर्ण

	अगर (bond_slave_can_tx(slave2)) अणु
		alb_send_learning_packets(slave2, slave2->dev->dev_addr, false);
		अगर (bond->alb_info.rlb_enabled) अणु
			/* inक्रमm the clients that the mac address
			 * has changed
			 */
			rlb_req_update_slave_clients(bond, slave2);
		पूर्ण
	पूर्ण अन्यथा अणु
		disabled_slave = slave2;
	पूर्ण

	अगर (bond->alb_info.rlb_enabled && slaves_state_dअगरfer) अणु
		/* A disabled slave was asचिन्हित an active mac addr */
		rlb_teach_disabled_mac_on_primary(bond,
						  disabled_slave->dev->dev_addr);
	पूर्ण
पूर्ण

/**
 * alb_change_hw_addr_on_detach
 * @bond: bonding we're working on
 * @slave: the slave that was just detached
 *
 * We assume that @slave was alपढ़ोy detached from the slave list.
 *
 * If @slave's permanent hw address is dअगरferent both from its current
 * address and from @bond's address, then somewhere in the bond there's
 * a slave that has @slave's permanet address as its current address.
 * We'll make sure that slave no longer uses @slave's permanent address.
 *
 * Caller must hold RTNL and no other locks
 */
अटल व्योम alb_change_hw_addr_on_detach(काष्ठा bonding *bond, काष्ठा slave *slave)
अणु
	पूर्णांक perm_curr_dअगरf;
	पूर्णांक perm_bond_dअगरf;
	काष्ठा slave *found_slave;

	perm_curr_dअगरf = !ether_addr_equal_64bits(slave->perm_hwaddr,
						  slave->dev->dev_addr);
	perm_bond_dअगरf = !ether_addr_equal_64bits(slave->perm_hwaddr,
						  bond->dev->dev_addr);

	अगर (perm_curr_dअगरf && perm_bond_dअगरf) अणु
		found_slave = bond_slave_has_mac(bond, slave->perm_hwaddr);

		अगर (found_slave) अणु
			alb_swap_mac_addr(slave, found_slave);
			alb_fasten_mac_swap(bond, slave, found_slave);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * alb_handle_addr_collision_on_attach
 * @bond: bonding we're working on
 * @slave: the slave that was just attached
 *
 * checks uniqueness of slave's mac address and handles the हाल the
 * new slave uses the bonds mac address.
 *
 * If the permanent hw address of @slave is @bond's hw address, we need to
 * find a dअगरferent hw address to give @slave, that isn't in use by any other
 * slave in the bond. This address must be, of course, one of the permanent
 * addresses of the other slaves.
 *
 * We go over the slave list, and क्रम each slave there we compare its
 * permanent hw address with the current address of all the other slaves.
 * If no match was found, then we've found a slave with a permanent address
 * that isn't used by any other slave in the bond, so we can assign it to
 * @slave.
 *
 * assumption: this function is called beक्रमe @slave is attached to the
 *	       bond slave list.
 */
अटल पूर्णांक alb_handle_addr_collision_on_attach(काष्ठा bonding *bond, काष्ठा slave *slave)
अणु
	काष्ठा slave *has_bond_addr = rcu_access_poपूर्णांकer(bond->curr_active_slave);
	काष्ठा slave *पंचांगp_slave1, *मुक्त_mac_slave = शून्य;
	काष्ठा list_head *iter;

	अगर (!bond_has_slaves(bond)) अणु
		/* this is the first slave */
		वापस 0;
	पूर्ण

	/* अगर slave's mac address differs from bond's mac address
	 * check uniqueness of slave's mac address against the other
	 * slaves in the bond.
	 */
	अगर (!ether_addr_equal_64bits(slave->perm_hwaddr, bond->dev->dev_addr)) अणु
		अगर (!bond_slave_has_mac(bond, slave->dev->dev_addr))
			वापस 0;

		/* Try setting slave mac to bond address and fall-through
		 * to code handling that situation below...
		 */
		alb_set_slave_mac_addr(slave, bond->dev->dev_addr,
				       bond->dev->addr_len);
	पूर्ण

	/* The slave's address is equal to the address of the bond.
	 * Search क्रम a spare address in the bond क्रम this slave.
	 */
	bond_क्रम_each_slave(bond, पंचांगp_slave1, iter) अणु
		अगर (!bond_slave_has_mac(bond, पंचांगp_slave1->perm_hwaddr)) अणु
			/* no slave has पंचांगp_slave1's perm addr
			 * as its curr addr
			 */
			मुक्त_mac_slave = पंचांगp_slave1;
			अवरोध;
		पूर्ण

		अगर (!has_bond_addr) अणु
			अगर (ether_addr_equal_64bits(पंचांगp_slave1->dev->dev_addr,
						    bond->dev->dev_addr)) अणु

				has_bond_addr = पंचांगp_slave1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (मुक्त_mac_slave) अणु
		alb_set_slave_mac_addr(slave, मुक्त_mac_slave->perm_hwaddr,
				       मुक्त_mac_slave->dev->addr_len);

		slave_warn(bond->dev, slave->dev, "the slave hw address is in use by the bond; giving it the hw address of %s\n",
			   मुक्त_mac_slave->dev->name);

	पूर्ण अन्यथा अगर (has_bond_addr) अणु
		slave_err(bond->dev, slave->dev, "the slave hw address is in use by the bond; couldn't find a slave with a free hw address to give it (this should not have happened)\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * alb_set_mac_address
 * @bond: bonding we're working on
 * @addr: MAC address to set
 *
 * In TLB mode all slaves are configured to the bond's hw address, but set
 * their dev_addr field to dअगरferent addresses (based on their permanent hw
 * addresses).
 *
 * For each slave, this function sets the पूर्णांकerface to the new address and then
 * changes its dev_addr field to its previous value.
 *
 * Unwinding assumes bond's mac address has not yet changed.
 */
अटल पूर्णांक alb_set_mac_address(काष्ठा bonding *bond, व्योम *addr)
अणु
	काष्ठा slave *slave, *rollback_slave;
	काष्ठा list_head *iter;
	काष्ठा sockaddr_storage ss;
	अक्षर पंचांगp_addr[MAX_ADDR_LEN];
	पूर्णांक res;

	अगर (bond->alb_info.rlb_enabled)
		वापस 0;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		/* save net_device's current hw address */
		bond_hw_addr_copy(पंचांगp_addr, slave->dev->dev_addr,
				  slave->dev->addr_len);

		res = dev_set_mac_address(slave->dev, addr, शून्य);

		/* restore net_device's hw address */
		bond_hw_addr_copy(slave->dev->dev_addr, पंचांगp_addr,
				  slave->dev->addr_len);

		अगर (res)
			जाओ unwind;
	पूर्ण

	वापस 0;

unwind:
	स_नकल(ss.__data, bond->dev->dev_addr, bond->dev->addr_len);
	ss.ss_family = bond->dev->type;

	/* unwind from head to the slave that failed */
	bond_क्रम_each_slave(bond, rollback_slave, iter) अणु
		अगर (rollback_slave == slave)
			अवरोध;
		bond_hw_addr_copy(पंचांगp_addr, rollback_slave->dev->dev_addr,
				  rollback_slave->dev->addr_len);
		dev_set_mac_address(rollback_slave->dev,
				    (काष्ठा sockaddr *)&ss, शून्य);
		bond_hw_addr_copy(rollback_slave->dev->dev_addr, पंचांगp_addr,
				  rollback_slave->dev->addr_len);
	पूर्ण

	वापस res;
पूर्ण

/************************ exported alb funcions ************************/

पूर्णांक bond_alb_initialize(काष्ठा bonding *bond, पूर्णांक rlb_enabled)
अणु
	पूर्णांक res;

	res = tlb_initialize(bond);
	अगर (res)
		वापस res;

	अगर (rlb_enabled) अणु
		bond->alb_info.rlb_enabled = 1;
		res = rlb_initialize(bond);
		अगर (res) अणु
			tlb_deinitialize(bond);
			वापस res;
		पूर्ण
	पूर्ण अन्यथा अणु
		bond->alb_info.rlb_enabled = 0;
	पूर्ण

	वापस 0;
पूर्ण

व्योम bond_alb_deinitialize(काष्ठा bonding *bond)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));

	tlb_deinitialize(bond);

	अगर (bond_info->rlb_enabled)
		rlb_deinitialize(bond);
पूर्ण

अटल netdev_tx_t bond_करो_alb_xmit(काष्ठा sk_buff *skb, काष्ठा bonding *bond,
				    काष्ठा slave *tx_slave)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा ethhdr *eth_data = eth_hdr(skb);

	अगर (!tx_slave) अणु
		/* unbalanced or unasचिन्हित, send through primary */
		tx_slave = rcu_dereference(bond->curr_active_slave);
		अगर (bond->params.tlb_dynamic_lb)
			bond_info->unbalanced_load += skb->len;
	पूर्ण

	अगर (tx_slave && bond_slave_can_tx(tx_slave)) अणु
		अगर (tx_slave != rcu_access_poपूर्णांकer(bond->curr_active_slave)) अणु
			ether_addr_copy(eth_data->h_source,
					tx_slave->dev->dev_addr);
		पूर्ण

		वापस bond_dev_queue_xmit(bond, skb, tx_slave->dev);
	पूर्ण

	अगर (tx_slave && bond->params.tlb_dynamic_lb) अणु
		spin_lock(&bond->mode_lock);
		__tlb_clear_slave(bond, tx_slave, 0);
		spin_unlock(&bond->mode_lock);
	पूर्ण

	/* no suitable पूर्णांकerface, frame not sent */
	वापस bond_tx_drop(bond->dev, skb);
पूर्ण

काष्ठा slave *bond_xmit_tlb_slave_get(काष्ठा bonding *bond,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा slave *tx_slave = शून्य;
	काष्ठा ethhdr *eth_data;
	u32 hash_index;

	skb_reset_mac_header(skb);
	eth_data = eth_hdr(skb);

	/* Do not TX balance any multicast or broadcast */
	अगर (!is_multicast_ether_addr(eth_data->h_dest)) अणु
		चयन (skb->protocol) अणु
		हाल htons(ETH_P_IP):
		हाल htons(ETH_P_IPX):
		    /* In हाल of IPX, it will falback to L2 hash */
		हाल htons(ETH_P_IPV6):
			hash_index = bond_xmit_hash(bond, skb);
			अगर (bond->params.tlb_dynamic_lb) अणु
				tx_slave = tlb_choose_channel(bond,
							      hash_index & 0xFF,
							      skb->len);
			पूर्ण अन्यथा अणु
				काष्ठा bond_up_slave *slaves;
				अचिन्हित पूर्णांक count;

				slaves = rcu_dereference(bond->usable_slaves);
				count = slaves ? READ_ONCE(slaves->count) : 0;
				अगर (likely(count))
					tx_slave = slaves->arr[hash_index %
							       count];
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	वापस tx_slave;
पूर्ण

netdev_tx_t bond_tlb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *tx_slave;

	tx_slave = bond_xmit_tlb_slave_get(bond, skb);
	वापस bond_करो_alb_xmit(skb, bond, tx_slave);
पूर्ण

काष्ठा slave *bond_xmit_alb_slave_get(काष्ठा bonding *bond,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	अटल स्थिर __be32 ip_bcast = htonl(0xffffffff);
	काष्ठा slave *tx_slave = शून्य;
	स्थिर u8 *hash_start = शून्य;
	bool करो_tx_balance = true;
	काष्ठा ethhdr *eth_data;
	u32 hash_index = 0;
	पूर्णांक hash_size = 0;

	skb_reset_mac_header(skb);
	eth_data = eth_hdr(skb);

	चयन (ntohs(skb->protocol)) अणु
	हाल ETH_P_IP: अणु
		स्थिर काष्ठा iphdr *iph;

		अगर (is_broadcast_ether_addr(eth_data->h_dest) ||
		    !pskb_network_may_pull(skb, माप(*iph))) अणु
			करो_tx_balance = false;
			अवरोध;
		पूर्ण
		iph = ip_hdr(skb);
		अगर (iph->daddr == ip_bcast || iph->protocol == IPPROTO_IGMP) अणु
			करो_tx_balance = false;
			अवरोध;
		पूर्ण
		hash_start = (अक्षर *)&(iph->daddr);
		hash_size = माप(iph->daddr);
		अवरोध;
	पूर्ण
	हाल ETH_P_IPV6: अणु
		स्थिर काष्ठा ipv6hdr *ip6hdr;

		/* IPv6 करोesn't really use broadcast mac address, but leave
		 * that here just in हाल.
		 */
		अगर (is_broadcast_ether_addr(eth_data->h_dest)) अणु
			करो_tx_balance = false;
			अवरोध;
		पूर्ण

		/* IPv6 uses all-nodes multicast as an equivalent to
		 * broadcasts in IPv4.
		 */
		अगर (ether_addr_equal_64bits(eth_data->h_dest, mac_v6_allmcast)) अणु
			करो_tx_balance = false;
			अवरोध;
		पूर्ण

		अगर (!pskb_network_may_pull(skb, माप(*ip6hdr))) अणु
			करो_tx_balance = false;
			अवरोध;
		पूर्ण
		/* Additionally, DAD probes should not be tx-balanced as that
		 * will lead to false positives क्रम duplicate addresses and
		 * prevent address configuration from working.
		 */
		ip6hdr = ipv6_hdr(skb);
		अगर (ipv6_addr_any(&ip6hdr->saddr)) अणु
			करो_tx_balance = false;
			अवरोध;
		पूर्ण

		hash_start = (अक्षर *)&ip6hdr->daddr;
		hash_size = माप(ip6hdr->daddr);
		अवरोध;
	पूर्ण
	हाल ETH_P_IPX: अणु
		स्थिर काष्ठा ipxhdr *ipxhdr;

		अगर (pskb_network_may_pull(skb, माप(*ipxhdr))) अणु
			करो_tx_balance = false;
			अवरोध;
		पूर्ण
		ipxhdr = (काष्ठा ipxhdr *)skb_network_header(skb);

		अगर (ipxhdr->ipx_checksum != IPX_NO_CHECKSUM) अणु
			/* something is wrong with this packet */
			करो_tx_balance = false;
			अवरोध;
		पूर्ण

		अगर (ipxhdr->ipx_type != IPX_TYPE_NCP) अणु
			/* The only protocol worth balancing in
			 * this family since it has an "ARP" like
			 * mechanism
			 */
			करो_tx_balance = false;
			अवरोध;
		पूर्ण

		eth_data = eth_hdr(skb);
		hash_start = (अक्षर *)eth_data->h_dest;
		hash_size = ETH_ALEN;
		अवरोध;
	पूर्ण
	हाल ETH_P_ARP:
		करो_tx_balance = false;
		अगर (bond_info->rlb_enabled)
			tx_slave = rlb_arp_xmit(skb, bond);
		अवरोध;
	शेष:
		करो_tx_balance = false;
		अवरोध;
	पूर्ण

	अगर (करो_tx_balance) अणु
		अगर (bond->params.tlb_dynamic_lb) अणु
			hash_index = _simple_hash(hash_start, hash_size);
			tx_slave = tlb_choose_channel(bond, hash_index, skb->len);
		पूर्ण अन्यथा अणु
			/*
			 * करो_tx_balance means we are मुक्त to select the tx_slave
			 * So we करो exactly what tlb would करो क्रम hash selection
			 */

			काष्ठा bond_up_slave *slaves;
			अचिन्हित पूर्णांक count;

			slaves = rcu_dereference(bond->usable_slaves);
			count = slaves ? READ_ONCE(slaves->count) : 0;
			अगर (likely(count))
				tx_slave = slaves->arr[bond_xmit_hash(bond, skb) %
						       count];
		पूर्ण
	पूर्ण
	वापस tx_slave;
पूर्ण

netdev_tx_t bond_alb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *tx_slave = शून्य;

	tx_slave = bond_xmit_alb_slave_get(bond, skb);
	वापस bond_करो_alb_xmit(skb, bond, tx_slave);
पूर्ण

व्योम bond_alb_monitor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bonding *bond = container_of(work, काष्ठा bonding,
					    alb_work.work);
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	अगर (!bond_has_slaves(bond)) अणु
		bond_info->tx_rebalance_counter = 0;
		bond_info->lp_counter = 0;
		जाओ re_arm;
	पूर्ण

	rcu_पढ़ो_lock();

	bond_info->tx_rebalance_counter++;
	bond_info->lp_counter++;

	/* send learning packets */
	अगर (bond_info->lp_counter >= BOND_ALB_LP_TICKS(bond)) अणु
		bool strict_match;

		bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
			/* If updating current_active, use all currently
			 * user mac addreses (!strict_match).  Otherwise, only
			 * use mac of the slave device.
			 * In RLB mode, we always use strict matches.
			 */
			strict_match = (slave != rcu_access_poपूर्णांकer(bond->curr_active_slave) ||
					bond_info->rlb_enabled);
			alb_send_learning_packets(slave, slave->dev->dev_addr,
						  strict_match);
		पूर्ण
		bond_info->lp_counter = 0;
	पूर्ण

	/* rebalance tx traffic */
	अगर (bond_info->tx_rebalance_counter >= BOND_TLB_REBALANCE_TICKS) अणु
		bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
			tlb_clear_slave(bond, slave, 1);
			अगर (slave == rcu_access_poपूर्णांकer(bond->curr_active_slave)) अणु
				SLAVE_TLB_INFO(slave).load =
					bond_info->unbalanced_load /
						BOND_TLB_REBALANCE_INTERVAL;
				bond_info->unbalanced_load = 0;
			पूर्ण
		पूर्ण
		bond_info->tx_rebalance_counter = 0;
	पूर्ण

	अगर (bond_info->rlb_enabled) अणु
		अगर (bond_info->primary_is_promisc &&
		    (++bond_info->rlb_promisc_समयout_counter >= RLB_PROMISC_TIMEOUT)) अणु

			/* dev_set_promiscuity requires rtnl and
			 * nothing अन्यथा.  Aव्योम race with bond_बंद.
			 */
			rcu_पढ़ो_unlock();
			अगर (!rtnl_trylock())
				जाओ re_arm;

			bond_info->rlb_promisc_समयout_counter = 0;

			/* If the primary was set to promiscuous mode
			 * because a slave was disabled then
			 * it can now leave promiscuous mode.
			 */
			dev_set_promiscuity(rtnl_dereference(bond->curr_active_slave)->dev,
					    -1);
			bond_info->primary_is_promisc = 0;

			rtnl_unlock();
			rcu_पढ़ो_lock();
		पूर्ण

		अगर (bond_info->rlb_rebalance) अणु
			bond_info->rlb_rebalance = 0;
			rlb_rebalance(bond);
		पूर्ण

		/* check अगर clients need updating */
		अगर (bond_info->rx_ntt) अणु
			अगर (bond_info->rlb_update_delay_counter) अणु
				--bond_info->rlb_update_delay_counter;
			पूर्ण अन्यथा अणु
				rlb_update_rx_clients(bond);
				अगर (bond_info->rlb_update_retry_counter)
					--bond_info->rlb_update_retry_counter;
				अन्यथा
					bond_info->rx_ntt = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
re_arm:
	queue_delayed_work(bond->wq, &bond->alb_work, alb_delta_in_ticks);
पूर्ण

/* assumption: called beक्रमe the slave is attached to the bond
 * and not locked by the bond lock
 */
पूर्णांक bond_alb_init_slave(काष्ठा bonding *bond, काष्ठा slave *slave)
अणु
	पूर्णांक res;

	res = alb_set_slave_mac_addr(slave, slave->perm_hwaddr,
				     slave->dev->addr_len);
	अगर (res)
		वापस res;

	res = alb_handle_addr_collision_on_attach(bond, slave);
	अगर (res)
		वापस res;

	tlb_init_slave(slave);

	/* order a rebalance ASAP */
	bond->alb_info.tx_rebalance_counter = BOND_TLB_REBALANCE_TICKS;

	अगर (bond->alb_info.rlb_enabled)
		bond->alb_info.rlb_rebalance = 1;

	वापस 0;
पूर्ण

/* Remove slave from tlb and rlb hash tables, and fix up MAC addresses
 * अगर necessary.
 *
 * Caller must hold RTNL and no other locks
 */
व्योम bond_alb_deinit_slave(काष्ठा bonding *bond, काष्ठा slave *slave)
अणु
	अगर (bond_has_slaves(bond))
		alb_change_hw_addr_on_detach(bond, slave);

	tlb_clear_slave(bond, slave, 0);

	अगर (bond->alb_info.rlb_enabled) अणु
		bond->alb_info.rx_slave = शून्य;
		rlb_clear_slave(bond, slave);
	पूर्ण

पूर्ण

व्योम bond_alb_handle_link_change(काष्ठा bonding *bond, काष्ठा slave *slave, अक्षर link)
अणु
	काष्ठा alb_bond_info *bond_info = &(BOND_ALB_INFO(bond));

	अगर (link == BOND_LINK_DOWN) अणु
		tlb_clear_slave(bond, slave, 0);
		अगर (bond->alb_info.rlb_enabled)
			rlb_clear_slave(bond, slave);
	पूर्ण अन्यथा अगर (link == BOND_LINK_UP) अणु
		/* order a rebalance ASAP */
		bond_info->tx_rebalance_counter = BOND_TLB_REBALANCE_TICKS;
		अगर (bond->alb_info.rlb_enabled) अणु
			bond->alb_info.rlb_rebalance = 1;
			/* If the updelay module parameter is smaller than the
			 * क्रमwarding delay of the चयन the rebalance will
			 * not work because the rebalance arp replies will
			 * not be क्रमwarded to the clients..
			 */
		पूर्ण
	पूर्ण

	अगर (bond_is_nondyn_tlb(bond)) अणु
		अगर (bond_update_slave_arr(bond, शून्य))
			pr_err("Failed to build slave-array for TLB mode.\n");
	पूर्ण
पूर्ण

/**
 * bond_alb_handle_active_change - assign new curr_active_slave
 * @bond: our bonding काष्ठा
 * @new_slave: new slave to assign
 *
 * Set the bond->curr_active_slave to @new_slave and handle
 * mac address swapping and promiscuity changes as needed.
 *
 * Caller must hold RTNL
 */
व्योम bond_alb_handle_active_change(काष्ठा bonding *bond, काष्ठा slave *new_slave)
अणु
	काष्ठा slave *swap_slave;
	काष्ठा slave *curr_active;

	curr_active = rtnl_dereference(bond->curr_active_slave);
	अगर (curr_active == new_slave)
		वापस;

	अगर (curr_active && bond->alb_info.primary_is_promisc) अणु
		dev_set_promiscuity(curr_active->dev, -1);
		bond->alb_info.primary_is_promisc = 0;
		bond->alb_info.rlb_promisc_समयout_counter = 0;
	पूर्ण

	swap_slave = curr_active;
	rcu_assign_poपूर्णांकer(bond->curr_active_slave, new_slave);

	अगर (!new_slave || !bond_has_slaves(bond))
		वापस;

	/* set the new curr_active_slave to the bonds mac address
	 * i.e. swap mac addresses of old curr_active_slave and new curr_active_slave
	 */
	अगर (!swap_slave)
		swap_slave = bond_slave_has_mac(bond, bond->dev->dev_addr);

	/* Arrange क्रम swap_slave and new_slave to temporarily be
	 * ignored so we can mess with their MAC addresses without
	 * fear of पूर्णांकerference from transmit activity.
	 */
	अगर (swap_slave)
		tlb_clear_slave(bond, swap_slave, 1);
	tlb_clear_slave(bond, new_slave, 1);

	/* in TLB mode, the slave might flip करोwn/up with the old dev_addr,
	 * and thus filter bond->dev_addr's packets, so force bond's mac
	 */
	अगर (BOND_MODE(bond) == BOND_MODE_TLB) अणु
		काष्ठा sockaddr_storage ss;
		u8 पंचांगp_addr[MAX_ADDR_LEN];

		bond_hw_addr_copy(पंचांगp_addr, new_slave->dev->dev_addr,
				  new_slave->dev->addr_len);

		bond_hw_addr_copy(ss.__data, bond->dev->dev_addr,
				  bond->dev->addr_len);
		ss.ss_family = bond->dev->type;
		/* we करोn't care if it can't change its mac, best efक्रमt */
		dev_set_mac_address(new_slave->dev, (काष्ठा sockaddr *)&ss,
				    शून्य);

		bond_hw_addr_copy(new_slave->dev->dev_addr, पंचांगp_addr,
				  new_slave->dev->addr_len);
	पूर्ण

	/* curr_active_slave must be set beक्रमe calling alb_swap_mac_addr */
	अगर (swap_slave) अणु
		/* swap mac address */
		alb_swap_mac_addr(swap_slave, new_slave);
		alb_fasten_mac_swap(bond, swap_slave, new_slave);
	पूर्ण अन्यथा अणु
		/* set the new_slave to the bond mac address */
		alb_set_slave_mac_addr(new_slave, bond->dev->dev_addr,
				       bond->dev->addr_len);
		alb_send_learning_packets(new_slave, bond->dev->dev_addr,
					  false);
	पूर्ण
पूर्ण

/* Called with RTNL */
पूर्णांक bond_alb_set_mac_address(काष्ठा net_device *bond_dev, व्योम *addr)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा sockaddr_storage *ss = addr;
	काष्ठा slave *curr_active;
	काष्ठा slave *swap_slave;
	पूर्णांक res;

	अगर (!is_valid_ether_addr(ss->__data))
		वापस -EADDRNOTAVAIL;

	res = alb_set_mac_address(bond, addr);
	अगर (res)
		वापस res;

	bond_hw_addr_copy(bond_dev->dev_addr, ss->__data, bond_dev->addr_len);

	/* If there is no curr_active_slave there is nothing अन्यथा to करो.
	 * Otherwise we'll need to pass the new address to it and handle
	 * duplications.
	 */
	curr_active = rtnl_dereference(bond->curr_active_slave);
	अगर (!curr_active)
		वापस 0;

	swap_slave = bond_slave_has_mac(bond, bond_dev->dev_addr);

	अगर (swap_slave) अणु
		alb_swap_mac_addr(swap_slave, curr_active);
		alb_fasten_mac_swap(bond, swap_slave, curr_active);
	पूर्ण अन्यथा अणु
		alb_set_slave_mac_addr(curr_active, bond_dev->dev_addr,
				       bond_dev->addr_len);

		alb_send_learning_packets(curr_active,
					  bond_dev->dev_addr, false);
		अगर (bond->alb_info.rlb_enabled) अणु
			/* inक्रमm clients mac address has changed */
			rlb_req_update_slave_clients(bond, curr_active);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम bond_alb_clear_vlan(काष्ठा bonding *bond, अचिन्हित लघु vlan_id)
अणु
	अगर (bond->alb_info.rlb_enabled)
		rlb_clear_vlan(bond, vlan_id);
पूर्ण


<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित _NET_BOND_ALB_H
#घोषणा _NET_BOND_ALB_H

#समावेश <linux/अगर_ether.h>

काष्ठा bonding;
काष्ठा slave;

#घोषणा BOND_ALB_INFO(bond)   ((bond)->alb_info)
#घोषणा SLAVE_TLB_INFO(slave) ((slave)->tlb_info)

#घोषणा ALB_TIMER_TICKS_PER_SEC	    10	/* should be a भागisor of HZ */
#घोषणा BOND_TLB_REBALANCE_INTERVAL 10	/* In seconds, periodic re-balancing.
					 * Used क्रम भागision - never set
					 * to zero !!!
					 */
#घोषणा BOND_ALB_DEFAULT_LP_INTERVAL 1
#घोषणा BOND_ALB_LP_INTERVAL(bond) (bond->params.lp_पूर्णांकerval)	/* In seconds, periodic send of
								 * learning packets to the चयन
								 */

#घोषणा BOND_TLB_REBALANCE_TICKS (BOND_TLB_REBALANCE_INTERVAL \
				  * ALB_TIMER_TICKS_PER_SEC)

#घोषणा BOND_ALB_LP_TICKS(bond) (BOND_ALB_LP_INTERVAL(bond) \
			   * ALB_TIMER_TICKS_PER_SEC)

#घोषणा TLB_HASH_TABLE_SIZE 256	/* The size of the clients hash table.
				 * Note that this value MUST NOT be smaller
				 * because the key hash table is BYTE wide !
				 */


#घोषणा TLB_शून्य_INDEX		0xffffffff

/* rlb defs */
#घोषणा RLB_HASH_TABLE_SIZE	256
#घोषणा RLB_शून्य_INDEX		0xffffffff
#घोषणा RLB_UPDATE_DELAY	(2*ALB_TIMER_TICKS_PER_SEC) /* 2 seconds */
#घोषणा RLB_ARP_BURST_SIZE	2
#घोषणा RLB_UPDATE_RETRY	3 /* 3-ticks - must be smaller than the rlb
				   * rebalance पूर्णांकerval (5 min).
				   */
/* RLB_PROMISC_TIMEOUT = 10 sec equals the समय that the current slave is
 * promiscuous after failover
 */
#घोषणा RLB_PROMISC_TIMEOUT	(10*ALB_TIMER_TICKS_PER_SEC)


काष्ठा tlb_client_info अणु
	काष्ठा slave *tx_slave;	/* A poपूर्णांकer to slave used क्रम transmiting
				 * packets to a Client that the Hash function
				 * gave this entry index.
				 */
	u32 tx_bytes;		/* Each Client accumulates the BytesTx that
				 * were transmitted to it, and after each
				 * CallBack the LoadHistory is भागided
				 * by the balance पूर्णांकerval
				 */
	u32 load_history;	/* This field contains the amount of Bytes
				 * that were transmitted to this client by
				 * the server on the previous balance
				 * पूर्णांकerval in Bps.
				 */
	u32 next;		/* The next Hash table entry index, asचिन्हित
				 * to use the same adapter क्रम transmit.
				 */
	u32 prev;		/* The previous Hash table entry index,
				 * asचिन्हित to use the same
				 */
पूर्ण;

/* -------------------------------------------------------------------------
 * काष्ठा rlb_client_info contains all info related to a specअगरic rx client
 * connection. This is the Clients Hash Table entry काष्ठा.
 * Note that this is not a proper hash table; अगर a new client's IP address
 * hash collides with an existing client entry, the old entry is replaced.
 *
 * There is a linked list (linked by the used_next and used_prev members)
 * linking all the used entries of the hash table. This allows updating
 * all the clients without walking over all the unused elements of the table.
 *
 * There are also linked lists of entries with identical hash(ip_src). These
 * allow cleaning up the table from ip_src<->mac_src associations that have
 * become outdated and would cause sending out invalid ARP updates to the
 * network. These are linked by the (src_next and src_prev members).
 * -------------------------------------------------------------------------
 */
काष्ठा rlb_client_info अणु
	__be32 ip_src;		/* the server IP address */
	__be32 ip_dst;		/* the client IP address */
	u8  mac_src[ETH_ALEN];	/* the server MAC address */
	u8  mac_dst[ETH_ALEN];	/* the client MAC address */

	/* list of used hash table entries, starting at rx_hashtbl_used_head */
	u32 used_next;
	u32 used_prev;

	/* ip_src based hashing */
	u32 src_next;	/* next entry with same hash(ip_src) */
	u32 src_prev;	/* prev entry with same hash(ip_src) */
	u32 src_first;	/* first entry with hash(ip_src) == this entry's index */

	u8  asचिन्हित;		/* checking whether this entry is asचिन्हित */
	u8  ntt;		/* flag - need to transmit client info */
	काष्ठा slave *slave;	/* the slave asचिन्हित to this client */
	अचिन्हित लघु vlan_id;	/* VLAN tag associated with IP address */
पूर्ण;

काष्ठा tlb_slave_info अणु
	u32 head;	/* Index to the head of the bi-directional clients
			 * hash table entries list. The entries in the list
			 * are the entries that were asचिन्हित to use this
			 * slave क्रम transmit.
			 */
	u32 load;	/* Each slave sums the loadHistory of all clients
			 * asचिन्हित to it
			 */
पूर्ण;

काष्ठा alb_bond_info अणु
	काष्ठा tlb_client_info	*tx_hashtbl; /* Dynamically allocated */
	u32			unbalanced_load;
	पूर्णांक			tx_rebalance_counter;
	पूर्णांक			lp_counter;
	/* -------- rlb parameters -------- */
	पूर्णांक rlb_enabled;
	काष्ठा rlb_client_info	*rx_hashtbl;	/* Receive hash table */
	u32			rx_hashtbl_used_head;
	u8			rx_ntt;	/* flag - need to transmit
					 * to all rx clients
					 */
	काष्ठा slave		*rx_slave;/* last slave to xmit from */
	u8			primary_is_promisc;	   /* boolean */
	u32			rlb_promisc_समयout_counter;/* counts primary
							     * promiscuity समय
							     */
	u32			rlb_update_delay_counter;
	u32			rlb_update_retry_counter;/* counter of retries
							  * of client update
							  */
	u8			rlb_rebalance;	/* flag - indicates that the
						 * rx traffic should be
						 * rebalanced
						 */
पूर्ण;

पूर्णांक bond_alb_initialize(काष्ठा bonding *bond, पूर्णांक rlb_enabled);
व्योम bond_alb_deinitialize(काष्ठा bonding *bond);
पूर्णांक bond_alb_init_slave(काष्ठा bonding *bond, काष्ठा slave *slave);
व्योम bond_alb_deinit_slave(काष्ठा bonding *bond, काष्ठा slave *slave);
व्योम bond_alb_handle_link_change(काष्ठा bonding *bond, काष्ठा slave *slave, अक्षर link);
व्योम bond_alb_handle_active_change(काष्ठा bonding *bond, काष्ठा slave *new_slave);
पूर्णांक bond_alb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *bond_dev);
पूर्णांक bond_tlb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *bond_dev);
काष्ठा slave *bond_xmit_alb_slave_get(काष्ठा bonding *bond,
				      काष्ठा sk_buff *skb);
काष्ठा slave *bond_xmit_tlb_slave_get(काष्ठा bonding *bond,
				      काष्ठा sk_buff *skb);
व्योम bond_alb_monitor(काष्ठा work_काष्ठा *);
पूर्णांक bond_alb_set_mac_address(काष्ठा net_device *bond_dev, व्योम *addr);
व्योम bond_alb_clear_vlan(काष्ठा bonding *bond, अचिन्हित लघु vlan_id);
#पूर्ण_अगर /* _NET_BOND_ALB_H */


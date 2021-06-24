<शैली गुरु>
/*
 * Bond several ethernet पूर्णांकerfaces पूर्णांकo a Cisco, running 'Etherchannel'.
 *
 * Portions are (c) Copyright 1995 Simon "Guru Aleph-Null" Janes
 * NCM: Network and Communications Management, Inc.
 *
 * BUT, I'm the one who modअगरied it क्रम ethernet, so:
 * (c) Copyright 1999, Thomas Davis, tadavis@lbl.gov
 *
 *	This software may be used and distributed according to the terms
 *	of the GNU Public License, incorporated herein by reference.
 *
 */

#अगर_अघोषित _NET_BONDING_H
#घोषणा _NET_BONDING_H

#समावेश <linux/समयr.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अगर_bonding.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/in6.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/reciprocal_भाग.h>
#समावेश <linux/अगर_link.h>

#समावेश <net/bond_3ad.h>
#समावेश <net/bond_alb.h>
#समावेश <net/bond_options.h>

#घोषणा BOND_MAX_ARP_TARGETS	16

#घोषणा BOND_DEFAULT_MIIMON	100

#अगर_अघोषित __दीर्घ_aligned
#घोषणा __दीर्घ_aligned __attribute__((aligned((माप(दीर्घ)))))
#पूर्ण_अगर

#घोषणा slave_info(bond_dev, slave_dev, fmt, ...) \
	netdev_info(bond_dev, "(slave %s): " fmt, (slave_dev)->name, ##__VA_ARGS__)
#घोषणा slave_warn(bond_dev, slave_dev, fmt, ...) \
	netdev_warn(bond_dev, "(slave %s): " fmt, (slave_dev)->name, ##__VA_ARGS__)
#घोषणा slave_dbg(bond_dev, slave_dev, fmt, ...) \
	netdev_dbg(bond_dev, "(slave %s): " fmt, (slave_dev)->name, ##__VA_ARGS__)
#घोषणा slave_err(bond_dev, slave_dev, fmt, ...) \
	netdev_err(bond_dev, "(slave %s): " fmt, (slave_dev)->name, ##__VA_ARGS__)

#घोषणा BOND_MODE(bond) ((bond)->params.mode)

/* slave list primitives */
#घोषणा bond_slave_list(bond) (&(bond)->dev->adj_list.lower)

#घोषणा bond_has_slaves(bond) !list_empty(bond_slave_list(bond))

/* IMPORTANT: bond_first/last_slave can वापस शून्य in हाल of an empty list */
#घोषणा bond_first_slave(bond) \
	(bond_has_slaves(bond) ? \
		netdev_adjacent_get_निजी(bond_slave_list(bond)->next) : \
		शून्य)
#घोषणा bond_last_slave(bond) \
	(bond_has_slaves(bond) ? \
		netdev_adjacent_get_निजी(bond_slave_list(bond)->prev) : \
		शून्य)

/* Caller must have rcu_पढ़ो_lock */
#घोषणा bond_first_slave_rcu(bond) \
	netdev_lower_get_first_निजी_rcu(bond->dev)

#घोषणा bond_is_first_slave(bond, pos) (pos == bond_first_slave(bond))
#घोषणा bond_is_last_slave(bond, pos) (pos == bond_last_slave(bond))

/**
 * bond_क्रम_each_slave - iterate over all slaves
 * @bond:	the bond holding this list
 * @pos:	current slave
 * @iter:	list_head * iterator
 *
 * Caller must hold RTNL
 */
#घोषणा bond_क्रम_each_slave(bond, pos, iter) \
	netdev_क्रम_each_lower_निजी((bond)->dev, pos, iter)

/* Caller must have rcu_पढ़ो_lock */
#घोषणा bond_क्रम_each_slave_rcu(bond, pos, iter) \
	netdev_क्रम_each_lower_निजी_rcu((bond)->dev, pos, iter)

#घोषणा BOND_XFRM_FEATURES (NETIF_F_HW_ESP | NETIF_F_HW_ESP_TX_CSUM | \
			    NETIF_F_GSO_ESP)

#घोषणा BOND_TLS_FEATURES (NETIF_F_HW_TLS_TX | NETIF_F_HW_TLS_RX)

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
बाह्य atomic_t netpoll_block_tx;

अटल अंतरभूत व्योम block_netpoll_tx(व्योम)
अणु
	atomic_inc(&netpoll_block_tx);
पूर्ण

अटल अंतरभूत व्योम unblock_netpoll_tx(व्योम)
अणु
	atomic_dec(&netpoll_block_tx);
पूर्ण

अटल अंतरभूत पूर्णांक is_netpoll_tx_blocked(काष्ठा net_device *dev)
अणु
	अगर (unlikely(netpoll_tx_running(dev)))
		वापस atomic_पढ़ो(&netpoll_block_tx);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा block_netpoll_tx()
#घोषणा unblock_netpoll_tx()
#घोषणा is_netpoll_tx_blocked(dev) (0)
#पूर्ण_अगर

काष्ठा bond_params अणु
	पूर्णांक mode;
	पूर्णांक xmit_policy;
	पूर्णांक miimon;
	u8 num_peer_notअगर;
	पूर्णांक arp_पूर्णांकerval;
	पूर्णांक arp_validate;
	पूर्णांक arp_all_tarमाला_लो;
	पूर्णांक use_carrier;
	पूर्णांक fail_over_mac;
	पूर्णांक updelay;
	पूर्णांक करोwndelay;
	पूर्णांक peer_notअगर_delay;
	पूर्णांक lacp_fast;
	अचिन्हित पूर्णांक min_links;
	पूर्णांक ad_select;
	अक्षर primary[IFNAMSIZ];
	पूर्णांक primary_reselect;
	__be32 arp_tarमाला_लो[BOND_MAX_ARP_TARGETS];
	पूर्णांक tx_queues;
	पूर्णांक all_slaves_active;
	पूर्णांक resend_igmp;
	पूर्णांक lp_पूर्णांकerval;
	पूर्णांक packets_per_slave;
	पूर्णांक tlb_dynamic_lb;
	काष्ठा reciprocal_value reciprocal_packets_per_slave;
	u16 ad_actor_sys_prio;
	u16 ad_user_port_key;

	/* 2 bytes of padding : see ether_addr_equal_64bits() */
	u8 ad_actor_प्रणाली[ETH_ALEN + 2];
पूर्ण;

काष्ठा bond_parm_tbl अणु
	अक्षर *modename;
	पूर्णांक mode;
पूर्ण;

काष्ठा slave अणु
	काष्ठा net_device *dev; /* first - useful क्रम panic debug */
	काष्ठा bonding *bond; /* our master */
	पूर्णांक    delay;
	/* all three in jअगरfies */
	अचिन्हित दीर्घ last_link_up;
	अचिन्हित दीर्घ last_rx;
	अचिन्हित दीर्घ target_last_arp_rx[BOND_MAX_ARP_TARGETS];
	s8     link;		/* one of BOND_LINK_XXXX */
	s8     link_new_state;	/* one of BOND_LINK_XXXX */
	u8     backup:1,   /* indicates backup slave. Value corresponds with
			      BOND_STATE_ACTIVE and BOND_STATE_BACKUP */
	       inactive:1, /* indicates inactive slave */
	       should_notअगरy:1, /* indicates whether the state changed */
	       should_notअगरy_link:1; /* indicates whether the link changed */
	u8     duplex;
	u32    original_mtu;
	u32    link_failure_count;
	u32    speed;
	u16    queue_id;
	u8     perm_hwaddr[MAX_ADDR_LEN];
	काष्ठा ad_slave_info *ad_info;
	काष्ठा tlb_slave_info tlb_info;
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	काष्ठा netpoll *np;
#पूर्ण_अगर
	काष्ठा delayed_work notअगरy_work;
	काष्ठा kobject kobj;
	काष्ठा rtnl_link_stats64 slave_stats;
पूर्ण;

अटल अंतरभूत काष्ठा slave *to_slave(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा slave, kobj);
पूर्ण

काष्ठा bond_up_slave अणु
	अचिन्हित पूर्णांक	count;
	काष्ठा rcu_head rcu;
	काष्ठा slave	*arr[];
पूर्ण;

/*
 * Link pseuकरो-state only used पूर्णांकernally by monitors
 */
#घोषणा BOND_LINK_NOCHANGE -1

/*
 * Here are the locking policies क्रम the two bonding locks:
 * Get rcu_पढ़ो_lock when पढ़ोing or RTNL when writing slave list.
 */
काष्ठा bonding अणु
	काष्ठा   net_device *dev; /* first - useful क्रम panic debug */
	काष्ठा   slave __rcu *curr_active_slave;
	काष्ठा   slave __rcu *current_arp_slave;
	काष्ठा   slave __rcu *primary_slave;
	काष्ठा   bond_up_slave __rcu *usable_slaves;
	काष्ठा   bond_up_slave __rcu *all_slaves;
	bool     क्रमce_primary;
	s32      slave_cnt; /* never change this value outside the attach/detach wrappers */
	पूर्णांक     (*recv_probe)(स्थिर काष्ठा sk_buff *, काष्ठा bonding *,
			      काष्ठा slave *);
	/* mode_lock is used क्रम mode-specअगरic locking needs, currently used by:
	 * 3ad mode (4) - protect against running bond_3ad_unbind_slave() and
	 *                bond_3ad_state_machine_handler() concurrently and also
	 *                the access to the state machine shared variables.
	 * TLB mode (5) - to sync the use and modअगरications of its hash table
	 * ALB mode (6) - to sync the use and modअगरications of its hash table
	 */
	spinlock_t mode_lock;
	spinlock_t stats_lock;
	u8	 send_peer_notअगर;
	u8       igmp_retrans;
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा   proc_dir_entry *proc_entry;
	अक्षर     proc_file_name[IFNAMSIZ];
#पूर्ण_अगर /* CONFIG_PROC_FS */
	काष्ठा   list_head bond_list;
	u32      rr_tx_counter;
	काष्ठा   ad_bond_info ad_info;
	काष्ठा   alb_bond_info alb_info;
	काष्ठा   bond_params params;
	काष्ठा   workqueue_काष्ठा *wq;
	काष्ठा   delayed_work mii_work;
	काष्ठा   delayed_work arp_work;
	काष्ठा   delayed_work alb_work;
	काष्ठा   delayed_work ad_work;
	काष्ठा   delayed_work mcast_work;
	काष्ठा   delayed_work slave_arr_work;
#अगर_घोषित CONFIG_DEBUG_FS
	/* debugging support via debugfs */
	काष्ठा	 dentry *debug_dir;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
	काष्ठा rtnl_link_stats64 bond_stats;
#अगर_घोषित CONFIG_XFRM_OFFLOAD
	काष्ठा xfrm_state *xs;
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */
पूर्ण;

#घोषणा bond_slave_get_rcu(dev) \
	((काष्ठा slave *) rcu_dereference(dev->rx_handler_data))

#घोषणा bond_slave_get_rtnl(dev) \
	((काष्ठा slave *) rtnl_dereference(dev->rx_handler_data))

व्योम bond_queue_slave_event(काष्ठा slave *slave);
व्योम bond_lower_state_changed(काष्ठा slave *slave);

काष्ठा bond_vlan_tag अणु
	__be16		vlan_proto;
	अचिन्हित लघु	vlan_id;
पूर्ण;

bool bond_sk_check(काष्ठा bonding *bond);

/**
 * Returns शून्य अगर the net_device करोes not beदीर्घ to any of the bond's slaves
 *
 * Caller must hold bond lock क्रम पढ़ो
 */
अटल अंतरभूत काष्ठा slave *bond_get_slave_by_dev(काष्ठा bonding *bond,
						  काष्ठा net_device *slave_dev)
अणु
	वापस netdev_lower_dev_get_निजी(bond->dev, slave_dev);
पूर्ण

अटल अंतरभूत काष्ठा bonding *bond_get_bond_by_slave(काष्ठा slave *slave)
अणु
	वापस slave->bond;
पूर्ण

अटल अंतरभूत bool bond_should_override_tx_queue(काष्ठा bonding *bond)
अणु
	वापस BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP ||
	       BOND_MODE(bond) == BOND_MODE_ROUNDROBIN;
पूर्ण

अटल अंतरभूत bool bond_is_lb(स्थिर काष्ठा bonding *bond)
अणु
	वापस BOND_MODE(bond) == BOND_MODE_TLB ||
	       BOND_MODE(bond) == BOND_MODE_ALB;
पूर्ण

अटल अंतरभूत bool bond_needs_speed_duplex(स्थिर काष्ठा bonding *bond)
अणु
	वापस BOND_MODE(bond) == BOND_MODE_8023AD || bond_is_lb(bond);
पूर्ण

अटल अंतरभूत bool bond_is_nondyn_tlb(स्थिर काष्ठा bonding *bond)
अणु
	वापस (bond_is_lb(bond) && bond->params.tlb_dynamic_lb == 0);
पूर्ण

अटल अंतरभूत bool bond_mode_can_use_xmit_hash(स्थिर काष्ठा bonding *bond)
अणु
	वापस (BOND_MODE(bond) == BOND_MODE_8023AD ||
		BOND_MODE(bond) == BOND_MODE_XOR ||
		BOND_MODE(bond) == BOND_MODE_TLB ||
		BOND_MODE(bond) == BOND_MODE_ALB);
पूर्ण

अटल अंतरभूत bool bond_mode_uses_xmit_hash(स्थिर काष्ठा bonding *bond)
अणु
	वापस (BOND_MODE(bond) == BOND_MODE_8023AD ||
		BOND_MODE(bond) == BOND_MODE_XOR ||
		bond_is_nondyn_tlb(bond));
पूर्ण

अटल अंतरभूत bool bond_mode_uses_arp(पूर्णांक mode)
अणु
	वापस mode != BOND_MODE_8023AD && mode != BOND_MODE_TLB &&
	       mode != BOND_MODE_ALB;
पूर्ण

अटल अंतरभूत bool bond_mode_uses_primary(पूर्णांक mode)
अणु
	वापस mode == BOND_MODE_ACTIVEBACKUP || mode == BOND_MODE_TLB ||
	       mode == BOND_MODE_ALB;
पूर्ण

अटल अंतरभूत bool bond_uses_primary(काष्ठा bonding *bond)
अणु
	वापस bond_mode_uses_primary(BOND_MODE(bond));
पूर्ण

अटल अंतरभूत काष्ठा net_device *bond_option_active_slave_get_rcu(काष्ठा bonding *bond)
अणु
	काष्ठा slave *slave = rcu_dereference(bond->curr_active_slave);

	वापस bond_uses_primary(bond) && slave ? slave->dev : शून्य;
पूर्ण

अटल अंतरभूत bool bond_slave_is_up(काष्ठा slave *slave)
अणु
	वापस netअगर_running(slave->dev) && netअगर_carrier_ok(slave->dev);
पूर्ण

अटल अंतरभूत व्योम bond_set_active_slave(काष्ठा slave *slave)
अणु
	अगर (slave->backup) अणु
		slave->backup = 0;
		bond_queue_slave_event(slave);
		bond_lower_state_changed(slave);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bond_set_backup_slave(काष्ठा slave *slave)
अणु
	अगर (!slave->backup) अणु
		slave->backup = 1;
		bond_queue_slave_event(slave);
		bond_lower_state_changed(slave);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bond_set_slave_state(काष्ठा slave *slave,
					पूर्णांक slave_state, bool notअगरy)
अणु
	अगर (slave->backup == slave_state)
		वापस;

	slave->backup = slave_state;
	अगर (notअगरy) अणु
		bond_lower_state_changed(slave);
		bond_queue_slave_event(slave);
		slave->should_notअगरy = 0;
	पूर्ण अन्यथा अणु
		अगर (slave->should_notअगरy)
			slave->should_notअगरy = 0;
		अन्यथा
			slave->should_notअगरy = 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bond_slave_state_change(काष्ठा bonding *bond)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *पंचांगp;

	bond_क्रम_each_slave(bond, पंचांगp, iter) अणु
		अगर (पंचांगp->link == BOND_LINK_UP)
			bond_set_active_slave(पंचांगp);
		अन्यथा अगर (पंचांगp->link == BOND_LINK_DOWN)
			bond_set_backup_slave(पंचांगp);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bond_slave_state_notअगरy(काष्ठा bonding *bond)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *पंचांगp;

	bond_क्रम_each_slave(bond, पंचांगp, iter) अणु
		अगर (पंचांगp->should_notअगरy) अणु
			bond_lower_state_changed(पंचांगp);
			पंचांगp->should_notअगरy = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक bond_slave_state(काष्ठा slave *slave)
अणु
	वापस slave->backup;
पूर्ण

अटल अंतरभूत bool bond_is_active_slave(काष्ठा slave *slave)
अणु
	वापस !bond_slave_state(slave);
पूर्ण

अटल अंतरभूत bool bond_slave_can_tx(काष्ठा slave *slave)
अणु
	वापस bond_slave_is_up(slave) && slave->link == BOND_LINK_UP &&
	       bond_is_active_slave(slave);
पूर्ण

अटल अंतरभूत bool bond_is_active_slave_dev(स्थिर काष्ठा net_device *slave_dev)
अणु
	काष्ठा slave *slave;
	bool active;

	rcu_पढ़ो_lock();
	slave = bond_slave_get_rcu(slave_dev);
	active = bond_is_active_slave(slave);
	rcu_पढ़ो_unlock();

	वापस active;
पूर्ण

अटल अंतरभूत व्योम bond_hw_addr_copy(u8 *dst, स्थिर u8 *src, अचिन्हित पूर्णांक len)
अणु
	अगर (len == ETH_ALEN) अणु
		ether_addr_copy(dst, src);
		वापस;
	पूर्ण

	स_नकल(dst, src, len);
पूर्ण

#घोषणा BOND_PRI_RESELECT_ALWAYS	0
#घोषणा BOND_PRI_RESELECT_BETTER	1
#घोषणा BOND_PRI_RESELECT_FAILURE	2

#घोषणा BOND_FOM_NONE			0
#घोषणा BOND_FOM_ACTIVE			1
#घोषणा BOND_FOM_FOLLOW			2

#घोषणा BOND_ARP_TARGETS_ANY		0
#घोषणा BOND_ARP_TARGETS_ALL		1

#घोषणा BOND_ARP_VALIDATE_NONE		0
#घोषणा BOND_ARP_VALIDATE_ACTIVE	(1 << BOND_STATE_ACTIVE)
#घोषणा BOND_ARP_VALIDATE_BACKUP	(1 << BOND_STATE_BACKUP)
#घोषणा BOND_ARP_VALIDATE_ALL		(BOND_ARP_VALIDATE_ACTIVE | \
					 BOND_ARP_VALIDATE_BACKUP)
#घोषणा BOND_ARP_FILTER			(BOND_ARP_VALIDATE_ALL + 1)
#घोषणा BOND_ARP_FILTER_ACTIVE		(BOND_ARP_VALIDATE_ACTIVE | \
					 BOND_ARP_FILTER)
#घोषणा BOND_ARP_FILTER_BACKUP		(BOND_ARP_VALIDATE_BACKUP | \
					 BOND_ARP_FILTER)

#घोषणा BOND_SLAVE_NOTIFY_NOW		true
#घोषणा BOND_SLAVE_NOTIFY_LATER		false

अटल अंतरभूत पूर्णांक slave_करो_arp_validate(काष्ठा bonding *bond,
					काष्ठा slave *slave)
अणु
	वापस bond->params.arp_validate & (1 << bond_slave_state(slave));
पूर्ण

अटल अंतरभूत पूर्णांक slave_करो_arp_validate_only(काष्ठा bonding *bond)
अणु
	वापस bond->params.arp_validate & BOND_ARP_FILTER;
पूर्ण

अटल अंतरभूत पूर्णांक bond_is_ip_target_ok(__be32 addr)
अणु
	वापस !ipv4_is_lbcast(addr) && !ipv4_is_zeronet(addr);
पूर्ण

/* Get the oldest arp which we've received on this slave for bond's
 * arp_tarमाला_लो.
 */
अटल अंतरभूत अचिन्हित दीर्घ slave_oldest_target_arp_rx(काष्ठा bonding *bond,
						       काष्ठा slave *slave)
अणु
	पूर्णांक i = 1;
	अचिन्हित दीर्घ ret = slave->target_last_arp_rx[0];

	क्रम (; (i < BOND_MAX_ARP_TARGETS) && bond->params.arp_tarमाला_लो[i]; i++)
		अगर (समय_beक्रमe(slave->target_last_arp_rx[i], ret))
			ret = slave->target_last_arp_rx[i];

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ slave_last_rx(काष्ठा bonding *bond,
					काष्ठा slave *slave)
अणु
	अगर (bond->params.arp_all_tarमाला_लो == BOND_ARP_TARGETS_ALL)
		वापस slave_oldest_target_arp_rx(bond, slave);

	वापस slave->last_rx;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल अंतरभूत netdev_tx_t bond_netpoll_send_skb(स्थिर काष्ठा slave *slave,
					 काष्ठा sk_buff *skb)
अणु
	वापस netpoll_send_skb(slave->np, skb);
पूर्ण
#अन्यथा
अटल अंतरभूत netdev_tx_t bond_netpoll_send_skb(स्थिर काष्ठा slave *slave,
					 काष्ठा sk_buff *skb)
अणु
	BUG();
	वापस NETDEV_TX_OK;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम bond_set_slave_inactive_flags(काष्ठा slave *slave,
						 bool notअगरy)
अणु
	अगर (!bond_is_lb(slave->bond))
		bond_set_slave_state(slave, BOND_STATE_BACKUP, notअगरy);
	अगर (!slave->bond->params.all_slaves_active)
		slave->inactive = 1;
पूर्ण

अटल अंतरभूत व्योम bond_set_slave_active_flags(काष्ठा slave *slave,
					       bool notअगरy)
अणु
	bond_set_slave_state(slave, BOND_STATE_ACTIVE, notअगरy);
	slave->inactive = 0;
पूर्ण

अटल अंतरभूत bool bond_is_slave_inactive(काष्ठा slave *slave)
अणु
	वापस slave->inactive;
पूर्ण

अटल अंतरभूत व्योम bond_propose_link_state(काष्ठा slave *slave, पूर्णांक state)
अणु
	slave->link_new_state = state;
पूर्ण

अटल अंतरभूत व्योम bond_commit_link_state(काष्ठा slave *slave, bool notअगरy)
अणु
	अगर (slave->link_new_state == BOND_LINK_NOCHANGE)
		वापस;

	slave->link = slave->link_new_state;
	अगर (notअगरy) अणु
		bond_queue_slave_event(slave);
		bond_lower_state_changed(slave);
		slave->should_notअगरy_link = 0;
	पूर्ण अन्यथा अणु
		अगर (slave->should_notअगरy_link)
			slave->should_notअगरy_link = 0;
		अन्यथा
			slave->should_notअगरy_link = 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bond_set_slave_link_state(काष्ठा slave *slave, पूर्णांक state,
					     bool notअगरy)
अणु
	bond_propose_link_state(slave, state);
	bond_commit_link_state(slave, notअगरy);
पूर्ण

अटल अंतरभूत व्योम bond_slave_link_notअगरy(काष्ठा bonding *bond)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *पंचांगp;

	bond_क्रम_each_slave(bond, पंचांगp, iter) अणु
		अगर (पंचांगp->should_notअगरy_link) अणु
			bond_queue_slave_event(पंचांगp);
			bond_lower_state_changed(पंचांगp);
			पंचांगp->should_notअगरy_link = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत __be32 bond_confirm_addr(काष्ठा net_device *dev, __be32 dst, __be32 local)
अणु
	काष्ठा in_device *in_dev;
	__be32 addr = 0;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(dev);

	अगर (in_dev)
		addr = inet_confirm_addr(dev_net(dev), in_dev, dst, local,
					 RT_SCOPE_HOST);
	rcu_पढ़ो_unlock();
	वापस addr;
पूर्ण

काष्ठा bond_net अणु
	काष्ठा net		*net;	/* Associated network namespace */
	काष्ठा list_head	dev_list;
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry	*proc_dir;
#पूर्ण_अगर
	काष्ठा class_attribute	class_attr_bonding_masters;
पूर्ण;

पूर्णांक bond_arp_rcv(स्थिर काष्ठा sk_buff *skb, काष्ठा bonding *bond, काष्ठा slave *slave);
netdev_tx_t bond_dev_queue_xmit(काष्ठा bonding *bond, काष्ठा sk_buff *skb, काष्ठा net_device *slave_dev);
पूर्णांक bond_create(काष्ठा net *net, स्थिर अक्षर *name);
पूर्णांक bond_create_sysfs(काष्ठा bond_net *net);
व्योम bond_destroy_sysfs(काष्ठा bond_net *net);
व्योम bond_prepare_sysfs_group(काष्ठा bonding *bond);
पूर्णांक bond_sysfs_slave_add(काष्ठा slave *slave);
व्योम bond_sysfs_slave_del(काष्ठा slave *slave);
पूर्णांक bond_enslave(काष्ठा net_device *bond_dev, काष्ठा net_device *slave_dev,
		 काष्ठा netlink_ext_ack *extack);
पूर्णांक bond_release(काष्ठा net_device *bond_dev, काष्ठा net_device *slave_dev);
u32 bond_xmit_hash(काष्ठा bonding *bond, काष्ठा sk_buff *skb);
पूर्णांक bond_set_carrier(काष्ठा bonding *bond);
व्योम bond_select_active_slave(काष्ठा bonding *bond);
व्योम bond_change_active_slave(काष्ठा bonding *bond, काष्ठा slave *new_active);
व्योम bond_create_debugfs(व्योम);
व्योम bond_destroy_debugfs(व्योम);
व्योम bond_debug_रेजिस्टर(काष्ठा bonding *bond);
व्योम bond_debug_unरेजिस्टर(काष्ठा bonding *bond);
व्योम bond_debug_reरेजिस्टर(काष्ठा bonding *bond);
स्थिर अक्षर *bond_mode_name(पूर्णांक mode);
व्योम bond_setup(काष्ठा net_device *bond_dev);
अचिन्हित पूर्णांक bond_get_num_tx_queues(व्योम);
पूर्णांक bond_netlink_init(व्योम);
व्योम bond_netlink_fini(व्योम);
काष्ठा net_device *bond_option_active_slave_get_rcu(काष्ठा bonding *bond);
स्थिर अक्षर *bond_slave_link_status(s8 link);
काष्ठा bond_vlan_tag *bond_verअगरy_device_path(काष्ठा net_device *start_dev,
					      काष्ठा net_device *end_dev,
					      पूर्णांक level);
पूर्णांक bond_update_slave_arr(काष्ठा bonding *bond, काष्ठा slave *skipslave);
व्योम bond_slave_arr_work_rearm(काष्ठा bonding *bond, अचिन्हित दीर्घ delay);
व्योम bond_work_init_all(काष्ठा bonding *bond);

#अगर_घोषित CONFIG_PROC_FS
व्योम bond_create_proc_entry(काष्ठा bonding *bond);
व्योम bond_हटाओ_proc_entry(काष्ठा bonding *bond);
व्योम bond_create_proc_dir(काष्ठा bond_net *bn);
व्योम bond_destroy_proc_dir(काष्ठा bond_net *bn);
#अन्यथा
अटल अंतरभूत व्योम bond_create_proc_entry(काष्ठा bonding *bond)
अणु
पूर्ण

अटल अंतरभूत व्योम bond_हटाओ_proc_entry(काष्ठा bonding *bond)
अणु
पूर्ण

अटल अंतरभूत व्योम bond_create_proc_dir(काष्ठा bond_net *bn)
अणु
पूर्ण

अटल अंतरभूत व्योम bond_destroy_proc_dir(काष्ठा bond_net *bn)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा slave *bond_slave_has_mac(काष्ठा bonding *bond,
					       स्थिर u8 *mac)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *पंचांगp;

	bond_क्रम_each_slave(bond, पंचांगp, iter)
		अगर (ether_addr_equal_64bits(mac, पंचांगp->dev->dev_addr))
			वापस पंचांगp;

	वापस शून्य;
पूर्ण

/* Caller must hold rcu_पढ़ो_lock() क्रम पढ़ो */
अटल अंतरभूत काष्ठा slave *bond_slave_has_mac_rcu(काष्ठा bonding *bond,
					       स्थिर u8 *mac)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *पंचांगp;

	bond_क्रम_each_slave_rcu(bond, पंचांगp, iter)
		अगर (ether_addr_equal_64bits(mac, पंचांगp->dev->dev_addr))
			वापस पंचांगp;

	वापस शून्य;
पूर्ण

/* Caller must hold rcu_पढ़ो_lock() क्रम पढ़ो */
अटल अंतरभूत bool bond_slave_has_mac_rx(काष्ठा bonding *bond, स्थिर u8 *mac)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *पंचांगp;
	काष्ठा netdev_hw_addr *ha;

	bond_क्रम_each_slave_rcu(bond, पंचांगp, iter)
		अगर (ether_addr_equal_64bits(mac, पंचांगp->dev->dev_addr))
			वापस true;

	अगर (netdev_uc_empty(bond->dev))
		वापस false;

	netdev_क्रम_each_uc_addr(ha, bond->dev)
		अगर (ether_addr_equal_64bits(mac, ha->addr))
			वापस true;

	वापस false;
पूर्ण

/* Check अगर the ip is present in arp ip list, or first मुक्त slot अगर ip == 0
 * Returns -1 अगर not found, index अगर found
 */
अटल अंतरभूत पूर्णांक bond_get_tarमाला_लो_ip(__be32 *tarमाला_लो, __be32 ip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BOND_MAX_ARP_TARGETS; i++)
		अगर (tarमाला_लो[i] == ip)
			वापस i;
		अन्यथा अगर (tarमाला_लो[i] == 0)
			अवरोध;

	वापस -1;
पूर्ण

/* exported from bond_मुख्य.c */
बाह्य अचिन्हित पूर्णांक bond_net_id;
बाह्य स्थिर काष्ठा bond_parm_tbl bond_lacp_tbl[];
बाह्य स्थिर काष्ठा bond_parm_tbl xmit_hashtype_tbl[];
बाह्य स्थिर काष्ठा bond_parm_tbl arp_validate_tbl[];
बाह्य स्थिर काष्ठा bond_parm_tbl arp_all_tarमाला_लो_tbl[];
बाह्य स्थिर काष्ठा bond_parm_tbl fail_over_mac_tbl[];
बाह्य स्थिर काष्ठा bond_parm_tbl pri_reselect_tbl[];
बाह्य काष्ठा bond_parm_tbl ad_select_tbl[];

/* exported from bond_netlink.c */
बाह्य काष्ठा rtnl_link_ops bond_link_ops;

/* exported from bond_sysfs_slave.c */
बाह्य स्थिर काष्ठा sysfs_ops slave_sysfs_ops;

अटल अंतरभूत netdev_tx_t bond_tx_drop(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	atomic_दीर्घ_inc(&dev->tx_dropped);
	dev_kमुक्त_skb_any(skb);
	वापस NET_XMIT_DROP;
पूर्ण

#पूर्ण_अगर /* _NET_BONDING_H */

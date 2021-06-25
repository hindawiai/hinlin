<शैली गुरु>
/*
 * originally based on the dummy device.
 *
 * Copyright 1999, Thomas Davis, tadavis@lbl.gov.
 * Licensed under the GPL. Based on dummy.c, and eql.c devices.
 *
 * bonding.c: an Ethernet Bonding driver
 *
 * This is useful to talk to a Cisco EtherChannel compatible equipment:
 *	Cisco 5500
 *	Sun Trunking (Solaris)
 *	Alteon AceDirector Trunks
 *	Linux Bonding
 *	and probably many L2 चयनes ...
 *
 * How it works:
 *    अगरconfig bond0 ipaddress neपंचांगask up
 *      will setup a network device, with an ip address.  No mac address
 *	will be asचिन्हित at this समय.  The hw mac address will come from
 *	the first slave bonded to the channel.  All slaves will then use
 *	this hw mac address.
 *
 *    अगरconfig bond0 करोwn
 *         will release all slaves, marking them as करोwn.
 *
 *    अगरenslave bond0 eth0
 *	will attach eth0 to bond0 as a slave.  eth0 hw mac address will either
 *	a: be used as initial mac address
 *	b: अगर a hw mac address alपढ़ोy is there, eth0's hw mac address
 *	   will then be set from bond0.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <net/ip.h>
#समावेश <linux/ip.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/socket.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/inet.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/smp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/arp.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_bonding.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/preempt.h>
#समावेश <net/route.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/rculist.h>
#समावेश <net/flow_dissector.h>
#समावेश <net/xfrm.h>
#समावेश <net/bonding.h>
#समावेश <net/bond_3ad.h>
#समावेश <net/bond_alb.h>
#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
#समावेश <net/tls.h>
#पूर्ण_अगर

#समावेश "bonding_priv.h"

/*---------------------------- Module parameters ----------------------------*/

/* monitor all links that often (in milliseconds). <=0 disables monitoring */

अटल पूर्णांक max_bonds	= BOND_DEFAULT_MAX_BONDS;
अटल पूर्णांक tx_queues	= BOND_DEFAULT_TX_QUEUES;
अटल पूर्णांक num_peer_notअगर = 1;
अटल पूर्णांक miimon;
अटल पूर्णांक updelay;
अटल पूर्णांक करोwndelay;
अटल पूर्णांक use_carrier	= 1;
अटल अक्षर *mode;
अटल अक्षर *primary;
अटल अक्षर *primary_reselect;
अटल अक्षर *lacp_rate;
अटल पूर्णांक min_links;
अटल अक्षर *ad_select;
अटल अक्षर *xmit_hash_policy;
अटल पूर्णांक arp_पूर्णांकerval;
अटल अक्षर *arp_ip_target[BOND_MAX_ARP_TARGETS];
अटल अक्षर *arp_validate;
अटल अक्षर *arp_all_tarमाला_लो;
अटल अक्षर *fail_over_mac;
अटल पूर्णांक all_slaves_active;
अटल काष्ठा bond_params bonding_शेषs;
अटल पूर्णांक resend_igmp = BOND_DEFAULT_RESEND_IGMP;
अटल पूर्णांक packets_per_slave = 1;
अटल पूर्णांक lp_पूर्णांकerval = BOND_ALB_DEFAULT_LP_INTERVAL;

module_param(max_bonds, पूर्णांक, 0);
MODULE_PARM_DESC(max_bonds, "Max number of bonded devices");
module_param(tx_queues, पूर्णांक, 0);
MODULE_PARM_DESC(tx_queues, "Max number of transmit queues (default = 16)");
module_param_named(num_grat_arp, num_peer_notअगर, पूर्णांक, 0644);
MODULE_PARM_DESC(num_grat_arp, "Number of peer notifications to send on "
			       "failover event (alias of num_unsol_na)");
module_param_named(num_unsol_na, num_peer_notअगर, पूर्णांक, 0644);
MODULE_PARM_DESC(num_unsol_na, "Number of peer notifications to send on "
			       "failover event (alias of num_grat_arp)");
module_param(miimon, पूर्णांक, 0);
MODULE_PARM_DESC(miimon, "Link check interval in milliseconds");
module_param(updelay, पूर्णांक, 0);
MODULE_PARM_DESC(updelay, "Delay before considering link up, in milliseconds");
module_param(करोwndelay, पूर्णांक, 0);
MODULE_PARM_DESC(करोwndelay, "Delay before considering link down, "
			    "in milliseconds");
module_param(use_carrier, पूर्णांक, 0);
MODULE_PARM_DESC(use_carrier, "Use netif_carrier_ok (vs MII ioctls) in miimon; "
			      "0 for off, 1 for on (default)");
module_param(mode, अक्षरp, 0);
MODULE_PARM_DESC(mode, "Mode of operation; 0 for balance-rr, "
		       "1 for active-backup, 2 for balance-xor, "
		       "3 for broadcast, 4 for 802.3ad, 5 for balance-tlb, "
		       "6 for balance-alb");
module_param(primary, अक्षरp, 0);
MODULE_PARM_DESC(primary, "Primary network device to use");
module_param(primary_reselect, अक्षरp, 0);
MODULE_PARM_DESC(primary_reselect, "Reselect primary slave "
				   "once it comes up; "
				   "0 for always (default), "
				   "1 for only if speed of primary is "
				   "better, "
				   "2 for only on active slave "
				   "failure");
module_param(lacp_rate, अक्षरp, 0);
MODULE_PARM_DESC(lacp_rate, "LACPDU tx rate to request from 802.3ad partner; "
			    "0 for slow, 1 for fast");
module_param(ad_select, अक्षरp, 0);
MODULE_PARM_DESC(ad_select, "802.3ad aggregation selection logic; "
			    "0 for stable (default), 1 for bandwidth, "
			    "2 for count");
module_param(min_links, पूर्णांक, 0);
MODULE_PARM_DESC(min_links, "Minimum number of available links before turning on carrier");

module_param(xmit_hash_policy, अक्षरp, 0);
MODULE_PARM_DESC(xmit_hash_policy, "balance-alb, balance-tlb, balance-xor, 802.3ad hashing method; "
				   "0 for layer 2 (default), 1 for layer 3+4, "
				   "2 for layer 2+3, 3 for encap layer 2+3, "
				   "4 for encap layer 3+4, 5 for vlan+srcmac");
module_param(arp_पूर्णांकerval, पूर्णांक, 0);
MODULE_PARM_DESC(arp_पूर्णांकerval, "arp interval in milliseconds");
module_param_array(arp_ip_target, अक्षरp, शून्य, 0);
MODULE_PARM_DESC(arp_ip_target, "arp targets in n.n.n.n form");
module_param(arp_validate, अक्षरp, 0);
MODULE_PARM_DESC(arp_validate, "validate src/dst of ARP probes; "
			       "0 for none (default), 1 for active, "
			       "2 for backup, 3 for all");
module_param(arp_all_tarमाला_लो, अक्षरp, 0);
MODULE_PARM_DESC(arp_all_tarमाला_लो, "fail on any/all arp targets timeout; 0 for any (default), 1 for all");
module_param(fail_over_mac, अक्षरp, 0);
MODULE_PARM_DESC(fail_over_mac, "For active-backup, do not set all slaves to "
				"the same MAC; 0 for none (default), "
				"1 for active, 2 for follow");
module_param(all_slaves_active, पूर्णांक, 0);
MODULE_PARM_DESC(all_slaves_active, "Keep all frames received on an interface "
				     "by setting active flag for all slaves; "
				     "0 for never (default), 1 for always.");
module_param(resend_igmp, पूर्णांक, 0);
MODULE_PARM_DESC(resend_igmp, "Number of IGMP membership reports to send on "
			      "link failure");
module_param(packets_per_slave, पूर्णांक, 0);
MODULE_PARM_DESC(packets_per_slave, "Packets to send per slave in balance-rr "
				    "mode; 0 for a random slave, 1 packet per "
				    "slave (default), >1 packets per slave.");
module_param(lp_पूर्णांकerval, uपूर्णांक, 0);
MODULE_PARM_DESC(lp_पूर्णांकerval, "The number of seconds between instances where "
			      "the bonding driver sends learning packets to "
			      "each slaves peer switch. The default is 1.");

/*----------------------------- Global variables ----------------------------*/

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
atomic_t netpoll_block_tx = ATOMIC_INIT(0);
#पूर्ण_अगर

अचिन्हित पूर्णांक bond_net_id __पढ़ो_mostly;

अटल स्थिर काष्ठा flow_dissector_key flow_keys_bonding_keys[] = अणु
	अणु
		.key_id = FLOW_DISSECTOR_KEY_CONTROL,
		.offset = दुरत्व(काष्ठा flow_keys, control),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_BASIC,
		.offset = दुरत्व(काष्ठा flow_keys, basic),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_IPV4_ADDRS,
		.offset = दुरत्व(काष्ठा flow_keys, addrs.v4addrs),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_IPV6_ADDRS,
		.offset = दुरत्व(काष्ठा flow_keys, addrs.v6addrs),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_TIPC,
		.offset = दुरत्व(काष्ठा flow_keys, addrs.tipckey),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_PORTS,
		.offset = दुरत्व(काष्ठा flow_keys, ports),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_ICMP,
		.offset = दुरत्व(काष्ठा flow_keys, icmp),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_VLAN,
		.offset = दुरत्व(काष्ठा flow_keys, vlan),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_FLOW_LABEL,
		.offset = दुरत्व(काष्ठा flow_keys, tags),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_GRE_KEYID,
		.offset = दुरत्व(काष्ठा flow_keys, keyid),
	पूर्ण,
पूर्ण;

अटल काष्ठा flow_dissector flow_keys_bonding __पढ़ो_mostly;

/*-------------------------- Forward declarations ---------------------------*/

अटल पूर्णांक bond_init(काष्ठा net_device *bond_dev);
अटल व्योम bond_uninit(काष्ठा net_device *bond_dev);
अटल व्योम bond_get_stats(काष्ठा net_device *bond_dev,
			   काष्ठा rtnl_link_stats64 *stats);
अटल व्योम bond_slave_arr_handler(काष्ठा work_काष्ठा *work);
अटल bool bond_समय_in_पूर्णांकerval(काष्ठा bonding *bond, अचिन्हित दीर्घ last_act,
				  पूर्णांक mod);
अटल व्योम bond_netdev_notअगरy_work(काष्ठा work_काष्ठा *work);

/*---------------------------- General routines -----------------------------*/

स्थिर अक्षर *bond_mode_name(पूर्णांक mode)
अणु
	अटल स्थिर अक्षर *names[] = अणु
		[BOND_MODE_ROUNDROBIN] = "load balancing (round-robin)",
		[BOND_MODE_ACTIVEBACKUP] = "fault-tolerance (active-backup)",
		[BOND_MODE_XOR] = "load balancing (xor)",
		[BOND_MODE_BROADCAST] = "fault-tolerance (broadcast)",
		[BOND_MODE_8023AD] = "IEEE 802.3ad Dynamic link aggregation",
		[BOND_MODE_TLB] = "transmit load balancing",
		[BOND_MODE_ALB] = "adaptive load balancing",
	पूर्ण;

	अगर (mode < BOND_MODE_ROUNDROBIN || mode > BOND_MODE_ALB)
		वापस "unknown";

	वापस names[mode];
पूर्ण

/**
 * bond_dev_queue_xmit - Prepare skb क्रम xmit.
 *
 * @bond: bond device that got this skb क्रम tx.
 * @skb: hw accel VLAN tagged skb to transmit
 * @slave_dev: slave that is supposed to xmit this skbuff
 */
netdev_tx_t bond_dev_queue_xmit(काष्ठा bonding *bond, काष्ठा sk_buff *skb,
			काष्ठा net_device *slave_dev)
अणु
	skb->dev = slave_dev;

	BUILD_BUG_ON(माप(skb->queue_mapping) !=
		     माप(qdisc_skb_cb(skb)->slave_dev_queue_mapping));
	skb_set_queue_mapping(skb, qdisc_skb_cb(skb)->slave_dev_queue_mapping);

	अगर (unlikely(netpoll_tx_running(bond->dev)))
		वापस bond_netpoll_send_skb(bond_get_slave_by_dev(bond, slave_dev), skb);

	वापस dev_queue_xmit(skb);
पूर्ण

bool bond_sk_check(काष्ठा bonding *bond)
अणु
	चयन (BOND_MODE(bond)) अणु
	हाल BOND_MODE_8023AD:
	हाल BOND_MODE_XOR:
		अगर (bond->params.xmit_policy == BOND_XMIT_POLICY_LAYER34)
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*---------------------------------- VLAN -----------------------------------*/

/* In the following 2 functions, bond_vlan_rx_add_vid and bond_vlan_rx_समाप्त_vid,
 * We करोn't protect the slave list iteration with a lock because:
 * a. This operation is perक्रमmed in IOCTL context,
 * b. The operation is रक्षित by the RTNL semaphore in the 8021q code,
 * c. Holding a lock with BH disabled जबतक directly calling a base driver
 *    entry poपूर्णांक is generally a BAD idea.
 *
 * The design of synchronization/protection क्रम this operation in the 8021q
 * module is good क्रम one or more VLAN devices over a single physical device
 * and cannot be extended क्रम a teaming solution like bonding, so there is a
 * potential race condition here where a net device from the vlan group might
 * be referenced (either by a base driver or the 8021q code) जबतक it is being
 * हटाओd from the प्रणाली. However, it turns out we're not making matters
 * worse, and अगर it works क्रम regular VLAN usage it will work here too.
*/

/**
 * bond_vlan_rx_add_vid - Propagates adding an id to slaves
 * @bond_dev: bonding net device that got called
 * @proto: network protocol ID
 * @vid: vlan id being added
 */
अटल पूर्णांक bond_vlan_rx_add_vid(काष्ठा net_device *bond_dev,
				__be16 proto, u16 vid)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *slave, *rollback_slave;
	काष्ठा list_head *iter;
	पूर्णांक res;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		res = vlan_vid_add(slave->dev, proto, vid);
		अगर (res)
			जाओ unwind;
	पूर्ण

	वापस 0;

unwind:
	/* unwind to the slave that failed */
	bond_क्रम_each_slave(bond, rollback_slave, iter) अणु
		अगर (rollback_slave == slave)
			अवरोध;

		vlan_vid_del(rollback_slave->dev, proto, vid);
	पूर्ण

	वापस res;
पूर्ण

/**
 * bond_vlan_rx_समाप्त_vid - Propagates deleting an id to slaves
 * @bond_dev: bonding net device that got called
 * @proto: network protocol ID
 * @vid: vlan id being हटाओd
 */
अटल पूर्णांक bond_vlan_rx_समाप्त_vid(काष्ठा net_device *bond_dev,
				 __be16 proto, u16 vid)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	bond_क्रम_each_slave(bond, slave, iter)
		vlan_vid_del(slave->dev, proto, vid);

	अगर (bond_is_lb(bond))
		bond_alb_clear_vlan(bond, vid);

	वापस 0;
पूर्ण

/*---------------------------------- XFRM -----------------------------------*/

#अगर_घोषित CONFIG_XFRM_OFFLOAD
/**
 * bond_ipsec_add_sa - program device with a security association
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल पूर्णांक bond_ipsec_add_sa(काष्ठा xfrm_state *xs)
अणु
	काष्ठा net_device *bond_dev = xs->xso.dev;
	काष्ठा bonding *bond;
	काष्ठा slave *slave;

	अगर (!bond_dev)
		वापस -EINVAL;

	bond = netdev_priv(bond_dev);
	slave = rcu_dereference(bond->curr_active_slave);
	xs->xso.real_dev = slave->dev;
	bond->xs = xs;

	अगर (!(slave->dev->xfrmdev_ops
	      && slave->dev->xfrmdev_ops->xकरो_dev_state_add)) अणु
		slave_warn(bond_dev, slave->dev, "Slave does not support ipsec offload\n");
		वापस -EINVAL;
	पूर्ण

	वापस slave->dev->xfrmdev_ops->xकरो_dev_state_add(xs);
पूर्ण

/**
 * bond_ipsec_del_sa - clear out this specअगरic SA
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल व्योम bond_ipsec_del_sa(काष्ठा xfrm_state *xs)
अणु
	काष्ठा net_device *bond_dev = xs->xso.dev;
	काष्ठा bonding *bond;
	काष्ठा slave *slave;

	अगर (!bond_dev)
		वापस;

	bond = netdev_priv(bond_dev);
	slave = rcu_dereference(bond->curr_active_slave);

	अगर (!slave)
		वापस;

	xs->xso.real_dev = slave->dev;

	अगर (!(slave->dev->xfrmdev_ops
	      && slave->dev->xfrmdev_ops->xकरो_dev_state_delete)) अणु
		slave_warn(bond_dev, slave->dev, "%s: no slave xdo_dev_state_delete\n", __func__);
		वापस;
	पूर्ण

	slave->dev->xfrmdev_ops->xकरो_dev_state_delete(xs);
पूर्ण

/**
 * bond_ipsec_offload_ok - can this packet use the xfrm hw offload
 * @skb: current data packet
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल bool bond_ipsec_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *xs)
अणु
	काष्ठा net_device *bond_dev = xs->xso.dev;
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *curr_active = rcu_dereference(bond->curr_active_slave);
	काष्ठा net_device *slave_dev = curr_active->dev;

	अगर (BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP)
		वापस true;

	अगर (!(slave_dev->xfrmdev_ops
	      && slave_dev->xfrmdev_ops->xकरो_dev_offload_ok)) अणु
		slave_warn(bond_dev, slave_dev, "%s: no slave xdo_dev_offload_ok\n", __func__);
		वापस false;
	पूर्ण

	xs->xso.real_dev = slave_dev;
	वापस slave_dev->xfrmdev_ops->xकरो_dev_offload_ok(skb, xs);
पूर्ण

अटल स्थिर काष्ठा xfrmdev_ops bond_xfrmdev_ops = अणु
	.xकरो_dev_state_add = bond_ipsec_add_sa,
	.xकरो_dev_state_delete = bond_ipsec_del_sa,
	.xकरो_dev_offload_ok = bond_ipsec_offload_ok,
पूर्ण;
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */

/*------------------------------- Link status -------------------------------*/

/* Set the carrier state क्रम the master according to the state of its
 * slaves.  If any slaves are up, the master is up.  In 802.3ad mode,
 * करो special 802.3ad magic.
 *
 * Returns zero अगर carrier state करोes not change, nonzero अगर it करोes.
 */
पूर्णांक bond_set_carrier(काष्ठा bonding *bond)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	अगर (!bond_has_slaves(bond))
		जाओ करोwn;

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD)
		वापस bond_3ad_set_carrier(bond);

	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (slave->link == BOND_LINK_UP) अणु
			अगर (!netअगर_carrier_ok(bond->dev)) अणु
				netअगर_carrier_on(bond->dev);
				वापस 1;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

करोwn:
	अगर (netअगर_carrier_ok(bond->dev)) अणु
		netअगर_carrier_off(bond->dev);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Get link speed and duplex from the slave's base driver
 * using ethtool. If क्रम some reason the call fails or the
 * values are invalid, set speed and duplex to -1,
 * and वापस. Return 1 अगर speed or duplex settings are
 * UNKNOWN; 0 otherwise.
 */
अटल पूर्णांक bond_update_speed_duplex(काष्ठा slave *slave)
अणु
	काष्ठा net_device *slave_dev = slave->dev;
	काष्ठा ethtool_link_ksettings ecmd;
	पूर्णांक res;

	slave->speed = SPEED_UNKNOWN;
	slave->duplex = DUPLEX_UNKNOWN;

	res = __ethtool_get_link_ksettings(slave_dev, &ecmd);
	अगर (res < 0)
		वापस 1;
	अगर (ecmd.base.speed == 0 || ecmd.base.speed == ((__u32)-1))
		वापस 1;
	चयन (ecmd.base.duplex) अणु
	हाल DUPLEX_FULL:
	हाल DUPLEX_HALF:
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण

	slave->speed = ecmd.base.speed;
	slave->duplex = ecmd.base.duplex;

	वापस 0;
पूर्ण

स्थिर अक्षर *bond_slave_link_status(s8 link)
अणु
	चयन (link) अणु
	हाल BOND_LINK_UP:
		वापस "up";
	हाल BOND_LINK_FAIL:
		वापस "going down";
	हाल BOND_LINK_DOWN:
		वापस "down";
	हाल BOND_LINK_BACK:
		वापस "going back";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

/* अगर <dev> supports MII link status reporting, check its link status.
 *
 * We either करो MII/ETHTOOL ioctls, or check netअगर_carrier_ok(),
 * depending upon the setting of the use_carrier parameter.
 *
 * Return either BMSR_LSTATUS, meaning that the link is up (or we
 * can't tell and just pretend it is), or 0, meaning that the link is
 * करोwn.
 *
 * If reporting is non-zero, instead of faking link up, वापस -1 अगर
 * both ETHTOOL and MII ioctls fail (meaning the device करोes not
 * support them).  If use_carrier is set, वापस whatever it says.
 * It'd be nice अगर there was a good way to tell अगर a driver supports
 * netअगर_carrier, but there really isn't.
 */
अटल पूर्णांक bond_check_dev_link(काष्ठा bonding *bond,
			       काष्ठा net_device *slave_dev, पूर्णांक reporting)
अणु
	स्थिर काष्ठा net_device_ops *slave_ops = slave_dev->netdev_ops;
	पूर्णांक (*ioctl)(काष्ठा net_device *, काष्ठा अगरreq *, पूर्णांक);
	काष्ठा अगरreq अगरr;
	काष्ठा mii_ioctl_data *mii;

	अगर (!reporting && !netअगर_running(slave_dev))
		वापस 0;

	अगर (bond->params.use_carrier)
		वापस netअगर_carrier_ok(slave_dev) ? BMSR_LSTATUS : 0;

	/* Try to get link status using Ethtool first. */
	अगर (slave_dev->ethtool_ops->get_link)
		वापस slave_dev->ethtool_ops->get_link(slave_dev) ?
			BMSR_LSTATUS : 0;

	/* Ethtool can't be used, fallback to MII ioctls. */
	ioctl = slave_ops->nकरो_करो_ioctl;
	अगर (ioctl) अणु
		/* TODO: set poपूर्णांकer to correct ioctl on a per team member
		 *       bases to make this more efficient. that is, once
		 *       we determine the correct ioctl, we will always
		 *       call it and not the others क्रम that team
		 *       member.
		 */

		/* We cannot assume that SIOCGMIIPHY will also पढ़ो a
		 * रेजिस्टर; not all network drivers (e.g., e100)
		 * support that.
		 */

		/* Yes, the mii is overlaid on the अगरreq.अगरr_अगरru */
		म_नकलन(अगरr.अगरr_name, slave_dev->name, IFNAMSIZ);
		mii = अगर_mii(&अगरr);
		अगर (ioctl(slave_dev, &अगरr, SIOCGMIIPHY) == 0) अणु
			mii->reg_num = MII_BMSR;
			अगर (ioctl(slave_dev, &अगरr, SIOCGMIIREG) == 0)
				वापस mii->val_out & BMSR_LSTATUS;
		पूर्ण
	पूर्ण

	/* If reporting, report that either there's no dev->करो_ioctl,
	 * or both SIOCGMIIREG and get_link failed (meaning that we
	 * cannot report link status).  If not reporting, pretend
	 * we're ok.
	 */
	वापस reporting ? -1 : BMSR_LSTATUS;
पूर्ण

/*----------------------------- Multicast list ------------------------------*/

/* Push the promiscuity flag करोwn to appropriate slaves */
अटल पूर्णांक bond_set_promiscuity(काष्ठा bonding *bond, पूर्णांक inc)
अणु
	काष्ठा list_head *iter;
	पूर्णांक err = 0;

	अगर (bond_uses_primary(bond)) अणु
		काष्ठा slave *curr_active = rtnl_dereference(bond->curr_active_slave);

		अगर (curr_active)
			err = dev_set_promiscuity(curr_active->dev, inc);
	पूर्ण अन्यथा अणु
		काष्ठा slave *slave;

		bond_क्रम_each_slave(bond, slave, iter) अणु
			err = dev_set_promiscuity(slave->dev, inc);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* Push the allmulti flag करोwn to all slaves */
अटल पूर्णांक bond_set_allmulti(काष्ठा bonding *bond, पूर्णांक inc)
अणु
	काष्ठा list_head *iter;
	पूर्णांक err = 0;

	अगर (bond_uses_primary(bond)) अणु
		काष्ठा slave *curr_active = rtnl_dereference(bond->curr_active_slave);

		अगर (curr_active)
			err = dev_set_allmulti(curr_active->dev, inc);
	पूर्ण अन्यथा अणु
		काष्ठा slave *slave;

		bond_क्रम_each_slave(bond, slave, iter) अणु
			err = dev_set_allmulti(slave->dev, inc);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* Retrieve the list of रेजिस्टरed multicast addresses क्रम the bonding
 * device and retransmit an IGMP JOIN request to the current active
 * slave.
 */
अटल व्योम bond_resend_igmp_join_requests_delayed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bonding *bond = container_of(work, काष्ठा bonding,
					    mcast_work.work);

	अगर (!rtnl_trylock()) अणु
		queue_delayed_work(bond->wq, &bond->mcast_work, 1);
		वापस;
	पूर्ण
	call_netdevice_notअगरiers(NETDEV_RESEND_IGMP, bond->dev);

	अगर (bond->igmp_retrans > 1) अणु
		bond->igmp_retrans--;
		queue_delayed_work(bond->wq, &bond->mcast_work, HZ/5);
	पूर्ण
	rtnl_unlock();
पूर्ण

/* Flush bond's hardware addresses from slave */
अटल व्योम bond_hw_addr_flush(काष्ठा net_device *bond_dev,
			       काष्ठा net_device *slave_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);

	dev_uc_unsync(slave_dev, bond_dev);
	dev_mc_unsync(slave_dev, bond_dev);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		/* del lacpdu mc addr from mc list */
		u8 lacpdu_multicast[ETH_ALEN] = MULTICAST_LACPDU_ADDR;

		dev_mc_del(slave_dev, lacpdu_multicast);
	पूर्ण
पूर्ण

/*--------------------------- Active slave change ---------------------------*/

/* Update the hardware address list and promisc/allmulti क्रम the new and
 * old active slaves (अगर any).  Modes that are not using primary keep all
 * slaves up date at all बार; only the modes that use primary need to call
 * this function to swap these settings during a failover.
 */
अटल व्योम bond_hw_addr_swap(काष्ठा bonding *bond, काष्ठा slave *new_active,
			      काष्ठा slave *old_active)
अणु
	अगर (old_active) अणु
		अगर (bond->dev->flags & IFF_PROMISC)
			dev_set_promiscuity(old_active->dev, -1);

		अगर (bond->dev->flags & IFF_ALLMULTI)
			dev_set_allmulti(old_active->dev, -1);

		bond_hw_addr_flush(bond->dev, old_active->dev);
	पूर्ण

	अगर (new_active) अणु
		/* FIXME: Signal errors upstream. */
		अगर (bond->dev->flags & IFF_PROMISC)
			dev_set_promiscuity(new_active->dev, 1);

		अगर (bond->dev->flags & IFF_ALLMULTI)
			dev_set_allmulti(new_active->dev, 1);

		netअगर_addr_lock_bh(bond->dev);
		dev_uc_sync(new_active->dev, bond->dev);
		dev_mc_sync(new_active->dev, bond->dev);
		netअगर_addr_unlock_bh(bond->dev);
	पूर्ण
पूर्ण

/**
 * bond_set_dev_addr - clone slave's address to bond
 * @bond_dev: bond net device
 * @slave_dev: slave net device
 *
 * Should be called with RTNL held.
 */
अटल पूर्णांक bond_set_dev_addr(काष्ठा net_device *bond_dev,
			     काष्ठा net_device *slave_dev)
अणु
	पूर्णांक err;

	slave_dbg(bond_dev, slave_dev, "bond_dev=%p slave_dev=%p slave_dev->addr_len=%d\n",
		  bond_dev, slave_dev, slave_dev->addr_len);
	err = dev_pre_changeaddr_notअगरy(bond_dev, slave_dev->dev_addr, शून्य);
	अगर (err)
		वापस err;

	स_नकल(bond_dev->dev_addr, slave_dev->dev_addr, slave_dev->addr_len);
	bond_dev->addr_assign_type = NET_ADDR_STOLEN;
	call_netdevice_notअगरiers(NETDEV_CHANGEADDR, bond_dev);
	वापस 0;
पूर्ण

अटल काष्ठा slave *bond_get_old_active(काष्ठा bonding *bond,
					 काष्ठा slave *new_active)
अणु
	काष्ठा slave *slave;
	काष्ठा list_head *iter;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (slave == new_active)
			जारी;

		अगर (ether_addr_equal(bond->dev->dev_addr, slave->dev->dev_addr))
			वापस slave;
	पूर्ण

	वापस शून्य;
पूर्ण

/* bond_करो_fail_over_mac
 *
 * Perक्रमm special MAC address swapping क्रम fail_over_mac settings
 *
 * Called with RTNL
 */
अटल व्योम bond_करो_fail_over_mac(काष्ठा bonding *bond,
				  काष्ठा slave *new_active,
				  काष्ठा slave *old_active)
अणु
	u8 पंचांगp_mac[MAX_ADDR_LEN];
	काष्ठा sockaddr_storage ss;
	पूर्णांक rv;

	चयन (bond->params.fail_over_mac) अणु
	हाल BOND_FOM_ACTIVE:
		अगर (new_active) अणु
			rv = bond_set_dev_addr(bond->dev, new_active->dev);
			अगर (rv)
				slave_err(bond->dev, new_active->dev, "Error %d setting bond MAC from slave\n",
					  -rv);
		पूर्ण
		अवरोध;
	हाल BOND_FOM_FOLLOW:
		/* अगर new_active && old_active, swap them
		 * अगर just old_active, करो nothing (going to no active slave)
		 * अगर just new_active, set new_active to bond's MAC
		 */
		अगर (!new_active)
			वापस;

		अगर (!old_active)
			old_active = bond_get_old_active(bond, new_active);

		अगर (old_active) अणु
			bond_hw_addr_copy(पंचांगp_mac, new_active->dev->dev_addr,
					  new_active->dev->addr_len);
			bond_hw_addr_copy(ss.__data,
					  old_active->dev->dev_addr,
					  old_active->dev->addr_len);
			ss.ss_family = new_active->dev->type;
		पूर्ण अन्यथा अणु
			bond_hw_addr_copy(ss.__data, bond->dev->dev_addr,
					  bond->dev->addr_len);
			ss.ss_family = bond->dev->type;
		पूर्ण

		rv = dev_set_mac_address(new_active->dev,
					 (काष्ठा sockaddr *)&ss, शून्य);
		अगर (rv) अणु
			slave_err(bond->dev, new_active->dev, "Error %d setting MAC of new active slave\n",
				  -rv);
			जाओ out;
		पूर्ण

		अगर (!old_active)
			जाओ out;

		bond_hw_addr_copy(ss.__data, पंचांगp_mac,
				  new_active->dev->addr_len);
		ss.ss_family = old_active->dev->type;

		rv = dev_set_mac_address(old_active->dev,
					 (काष्ठा sockaddr *)&ss, शून्य);
		अगर (rv)
			slave_err(bond->dev, old_active->dev, "Error %d setting MAC of old active slave\n",
				  -rv);
out:
		अवरोध;
	शेष:
		netdev_err(bond->dev, "bond_do_fail_over_mac impossible: bad policy %d\n",
			   bond->params.fail_over_mac);
		अवरोध;
	पूर्ण

पूर्ण

अटल काष्ठा slave *bond_choose_primary_or_current(काष्ठा bonding *bond)
अणु
	काष्ठा slave *prim = rtnl_dereference(bond->primary_slave);
	काष्ठा slave *curr = rtnl_dereference(bond->curr_active_slave);

	अगर (!prim || prim->link != BOND_LINK_UP) अणु
		अगर (!curr || curr->link != BOND_LINK_UP)
			वापस शून्य;
		वापस curr;
	पूर्ण

	अगर (bond->क्रमce_primary) अणु
		bond->क्रमce_primary = false;
		वापस prim;
	पूर्ण

	अगर (!curr || curr->link != BOND_LINK_UP)
		वापस prim;

	/* At this poपूर्णांक, prim and curr are both up */
	चयन (bond->params.primary_reselect) अणु
	हाल BOND_PRI_RESELECT_ALWAYS:
		वापस prim;
	हाल BOND_PRI_RESELECT_BETTER:
		अगर (prim->speed < curr->speed)
			वापस curr;
		अगर (prim->speed == curr->speed && prim->duplex <= curr->duplex)
			वापस curr;
		वापस prim;
	हाल BOND_PRI_RESELECT_FAILURE:
		वापस curr;
	शेष:
		netdev_err(bond->dev, "impossible primary_reselect %d\n",
			   bond->params.primary_reselect);
		वापस curr;
	पूर्ण
पूर्ण

/**
 * bond_find_best_slave - select the best available slave to be the active one
 * @bond: our bonding काष्ठा
 */
अटल काष्ठा slave *bond_find_best_slave(काष्ठा bonding *bond)
अणु
	काष्ठा slave *slave, *bestslave = शून्य;
	काष्ठा list_head *iter;
	पूर्णांक mपूर्णांकime = bond->params.updelay;

	slave = bond_choose_primary_or_current(bond);
	अगर (slave)
		वापस slave;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (slave->link == BOND_LINK_UP)
			वापस slave;
		अगर (slave->link == BOND_LINK_BACK && bond_slave_is_up(slave) &&
		    slave->delay < mपूर्णांकime) अणु
			mपूर्णांकime = slave->delay;
			bestslave = slave;
		पूर्ण
	पूर्ण

	वापस bestslave;
पूर्ण

अटल bool bond_should_notअगरy_peers(काष्ठा bonding *bond)
अणु
	काष्ठा slave *slave;

	rcu_पढ़ो_lock();
	slave = rcu_dereference(bond->curr_active_slave);
	rcu_पढ़ो_unlock();

	netdev_dbg(bond->dev, "bond_should_notify_peers: slave %s\n",
		   slave ? slave->dev->name : "NULL");

	अगर (!slave || !bond->send_peer_notअगर ||
	    bond->send_peer_notअगर %
	    max(1, bond->params.peer_notअगर_delay) != 0 ||
	    !netअगर_carrier_ok(bond->dev) ||
	    test_bit(__LINK_STATE_LINKWATCH_PENDING, &slave->dev->state))
		वापस false;

	वापस true;
पूर्ण

/**
 * bond_change_active_slave - change the active slave पूर्णांकo the specअगरied one
 * @bond: our bonding काष्ठा
 * @new_active: the new slave to make the active one
 *
 * Set the new slave to the bond's settings and unset them on the old
 * curr_active_slave.
 * Setting include flags, mc-list, promiscuity, allmulti, etc.
 *
 * If @new's link state is %BOND_LINK_BACK we'll set it to %BOND_LINK_UP,
 * because it is apparently the best available slave we have, even though its
 * updelay hasn't समयd out yet.
 *
 * Caller must hold RTNL.
 */
व्योम bond_change_active_slave(काष्ठा bonding *bond, काष्ठा slave *new_active)
अणु
	काष्ठा slave *old_active;

	ASSERT_RTNL();

	old_active = rtnl_dereference(bond->curr_active_slave);

	अगर (old_active == new_active)
		वापस;

#अगर_घोषित CONFIG_XFRM_OFFLOAD
	अगर (old_active && bond->xs)
		bond_ipsec_del_sa(bond->xs);
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */

	अगर (new_active) अणु
		new_active->last_link_up = jअगरfies;

		अगर (new_active->link == BOND_LINK_BACK) अणु
			अगर (bond_uses_primary(bond)) अणु
				slave_info(bond->dev, new_active->dev, "making interface the new active one %d ms earlier\n",
					   (bond->params.updelay - new_active->delay) * bond->params.miimon);
			पूर्ण

			new_active->delay = 0;
			bond_set_slave_link_state(new_active, BOND_LINK_UP,
						  BOND_SLAVE_NOTIFY_NOW);

			अगर (BOND_MODE(bond) == BOND_MODE_8023AD)
				bond_3ad_handle_link_change(new_active, BOND_LINK_UP);

			अगर (bond_is_lb(bond))
				bond_alb_handle_link_change(bond, new_active, BOND_LINK_UP);
		पूर्ण अन्यथा अणु
			अगर (bond_uses_primary(bond)) अणु
				slave_info(bond->dev, new_active->dev, "making interface the new active one\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (bond_uses_primary(bond))
		bond_hw_addr_swap(bond, new_active, old_active);

	अगर (bond_is_lb(bond)) अणु
		bond_alb_handle_active_change(bond, new_active);
		अगर (old_active)
			bond_set_slave_inactive_flags(old_active,
						      BOND_SLAVE_NOTIFY_NOW);
		अगर (new_active)
			bond_set_slave_active_flags(new_active,
						    BOND_SLAVE_NOTIFY_NOW);
	पूर्ण अन्यथा अणु
		rcu_assign_poपूर्णांकer(bond->curr_active_slave, new_active);
	पूर्ण

	अगर (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP) अणु
		अगर (old_active)
			bond_set_slave_inactive_flags(old_active,
						      BOND_SLAVE_NOTIFY_NOW);

		अगर (new_active) अणु
			bool should_notअगरy_peers = false;

			bond_set_slave_active_flags(new_active,
						    BOND_SLAVE_NOTIFY_NOW);

			अगर (bond->params.fail_over_mac)
				bond_करो_fail_over_mac(bond, new_active,
						      old_active);

			अगर (netअगर_running(bond->dev)) अणु
				bond->send_peer_notअगर =
					bond->params.num_peer_notअगर *
					max(1, bond->params.peer_notअगर_delay);
				should_notअगरy_peers =
					bond_should_notअगरy_peers(bond);
			पूर्ण

			call_netdevice_notअगरiers(NETDEV_BONDING_FAILOVER, bond->dev);
			अगर (should_notअगरy_peers) अणु
				bond->send_peer_notअगर--;
				call_netdevice_notअगरiers(NETDEV_NOTIFY_PEERS,
							 bond->dev);
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_XFRM_OFFLOAD
	अगर (new_active && bond->xs) अणु
		xfrm_dev_state_flush(dev_net(bond->dev), bond->dev, true);
		bond_ipsec_add_sa(bond->xs);
	पूर्ण
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */

	/* resend IGMP joins since active slave has changed or
	 * all were sent on curr_active_slave.
	 * resend only अगर bond is brought up with the affected
	 * bonding modes and the retransmission is enabled
	 */
	अगर (netअगर_running(bond->dev) && (bond->params.resend_igmp > 0) &&
	    ((bond_uses_primary(bond) && new_active) ||
	     BOND_MODE(bond) == BOND_MODE_ROUNDROBIN)) अणु
		bond->igmp_retrans = bond->params.resend_igmp;
		queue_delayed_work(bond->wq, &bond->mcast_work, 1);
	पूर्ण
पूर्ण

/**
 * bond_select_active_slave - select a new active slave, अगर needed
 * @bond: our bonding काष्ठा
 *
 * This functions should be called when one of the following occurs:
 * - The old curr_active_slave has been released or lost its link.
 * - The primary_slave has got its link back.
 * - A slave has got its link back and there's no old curr_active_slave.
 *
 * Caller must hold RTNL.
 */
व्योम bond_select_active_slave(काष्ठा bonding *bond)
अणु
	काष्ठा slave *best_slave;
	पूर्णांक rv;

	ASSERT_RTNL();

	best_slave = bond_find_best_slave(bond);
	अगर (best_slave != rtnl_dereference(bond->curr_active_slave)) अणु
		bond_change_active_slave(bond, best_slave);
		rv = bond_set_carrier(bond);
		अगर (!rv)
			वापस;

		अगर (netअगर_carrier_ok(bond->dev))
			netdev_info(bond->dev, "active interface up!\n");
		अन्यथा
			netdev_info(bond->dev, "now running without any active interface!\n");
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल अंतरभूत पूर्णांक slave_enable_netpoll(काष्ठा slave *slave)
अणु
	काष्ठा netpoll *np;
	पूर्णांक err = 0;

	np = kzalloc(माप(*np), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!np)
		जाओ out;

	err = __netpoll_setup(np, slave->dev);
	अगर (err) अणु
		kमुक्त(np);
		जाओ out;
	पूर्ण
	slave->np = np;
out:
	वापस err;
पूर्ण
अटल अंतरभूत व्योम slave_disable_netpoll(काष्ठा slave *slave)
अणु
	काष्ठा netpoll *np = slave->np;

	अगर (!np)
		वापस;

	slave->np = शून्य;

	__netpoll_मुक्त(np);
पूर्ण

अटल व्योम bond_poll_controller(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *slave = शून्य;
	काष्ठा list_head *iter;
	काष्ठा ad_info ad_info;

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD)
		अगर (bond_3ad_get_active_agg_info(bond, &ad_info))
			वापस;

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (!bond_slave_is_up(slave))
			जारी;

		अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
			काष्ठा aggregator *agg =
			    SLAVE_AD_INFO(slave)->port.aggregator;

			अगर (agg &&
			    agg->aggregator_identअगरier != ad_info.aggregator_id)
				जारी;
		पूर्ण

		netpoll_poll_dev(slave->dev);
	पूर्ण
पूर्ण

अटल व्योम bond_netpoll_cleanup(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	bond_क्रम_each_slave(bond, slave, iter)
		अगर (bond_slave_is_up(slave))
			slave_disable_netpoll(slave);
पूर्ण

अटल पूर्णांक bond_netpoll_setup(काष्ठा net_device *dev, काष्ठा netpoll_info *ni)
अणु
	काष्ठा bonding *bond = netdev_priv(dev);
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	पूर्णांक err = 0;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		err = slave_enable_netpoll(slave);
		अगर (err) अणु
			bond_netpoll_cleanup(dev);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक slave_enable_netpoll(काष्ठा slave *slave)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम slave_disable_netpoll(काष्ठा slave *slave)
अणु
पूर्ण
अटल व्योम bond_netpoll_cleanup(काष्ठा net_device *bond_dev)
अणु
पूर्ण
#पूर्ण_अगर

/*---------------------------------- IOCTL ----------------------------------*/

अटल netdev_features_t bond_fix_features(काष्ठा net_device *dev,
					   netdev_features_t features)
अणु
	काष्ठा bonding *bond = netdev_priv(dev);
	काष्ठा list_head *iter;
	netdev_features_t mask;
	काष्ठा slave *slave;

#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
	अगर (bond_sk_check(bond))
		features |= BOND_TLS_FEATURES;
	अन्यथा
		features &= ~BOND_TLS_FEATURES;
#पूर्ण_अगर

	mask = features;

	features &= ~NETIF_F_ONE_FOR_ALL;
	features |= NETIF_F_ALL_FOR_ALL;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		features = netdev_increment_features(features,
						     slave->dev->features,
						     mask);
	पूर्ण
	features = netdev_add_tso_features(features, mask);

	वापस features;
पूर्ण

#घोषणा BOND_VLAN_FEATURES	(NETIF_F_HW_CSUM | NETIF_F_SG | \
				 NETIF_F_FRAGLIST | NETIF_F_GSO_SOFTWARE | \
				 NETIF_F_HIGHDMA | NETIF_F_LRO)

#घोषणा BOND_ENC_FEATURES	(NETIF_F_HW_CSUM | NETIF_F_SG | \
				 NETIF_F_RXCSUM | NETIF_F_GSO_SOFTWARE)

#घोषणा BOND_MPLS_FEATURES	(NETIF_F_HW_CSUM | NETIF_F_SG | \
				 NETIF_F_GSO_SOFTWARE)


अटल व्योम bond_compute_features(काष्ठा bonding *bond)
अणु
	अचिन्हित पूर्णांक dst_release_flag = IFF_XMIT_DST_RELEASE |
					IFF_XMIT_DST_RELEASE_PERM;
	netdev_features_t vlan_features = BOND_VLAN_FEATURES;
	netdev_features_t enc_features  = BOND_ENC_FEATURES;
#अगर_घोषित CONFIG_XFRM_OFFLOAD
	netdev_features_t xfrm_features  = BOND_XFRM_FEATURES;
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */
	netdev_features_t mpls_features  = BOND_MPLS_FEATURES;
	काष्ठा net_device *bond_dev = bond->dev;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	अचिन्हित लघु max_hard_header_len = ETH_HLEN;
	अचिन्हित पूर्णांक gso_max_size = GSO_MAX_SIZE;
	u16 gso_max_segs = GSO_MAX_SEGS;

	अगर (!bond_has_slaves(bond))
		जाओ करोne;
	vlan_features &= NETIF_F_ALL_FOR_ALL;
	mpls_features &= NETIF_F_ALL_FOR_ALL;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		vlan_features = netdev_increment_features(vlan_features,
			slave->dev->vlan_features, BOND_VLAN_FEATURES);

		enc_features = netdev_increment_features(enc_features,
							 slave->dev->hw_enc_features,
							 BOND_ENC_FEATURES);

#अगर_घोषित CONFIG_XFRM_OFFLOAD
		xfrm_features = netdev_increment_features(xfrm_features,
							  slave->dev->hw_enc_features,
							  BOND_XFRM_FEATURES);
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */

		mpls_features = netdev_increment_features(mpls_features,
							  slave->dev->mpls_features,
							  BOND_MPLS_FEATURES);

		dst_release_flag &= slave->dev->priv_flags;
		अगर (slave->dev->hard_header_len > max_hard_header_len)
			max_hard_header_len = slave->dev->hard_header_len;

		gso_max_size = min(gso_max_size, slave->dev->gso_max_size);
		gso_max_segs = min(gso_max_segs, slave->dev->gso_max_segs);
	पूर्ण
	bond_dev->hard_header_len = max_hard_header_len;

करोne:
	bond_dev->vlan_features = vlan_features;
	bond_dev->hw_enc_features = enc_features | NETIF_F_GSO_ENCAP_ALL |
				    NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_HW_VLAN_STAG_TX;
#अगर_घोषित CONFIG_XFRM_OFFLOAD
	bond_dev->hw_enc_features |= xfrm_features;
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */
	bond_dev->mpls_features = mpls_features;
	bond_dev->gso_max_segs = gso_max_segs;
	netअगर_set_gso_max_size(bond_dev, gso_max_size);

	bond_dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
	अगर ((bond_dev->priv_flags & IFF_XMIT_DST_RELEASE_PERM) &&
	    dst_release_flag == (IFF_XMIT_DST_RELEASE | IFF_XMIT_DST_RELEASE_PERM))
		bond_dev->priv_flags |= IFF_XMIT_DST_RELEASE;

	netdev_change_features(bond_dev);
पूर्ण

अटल व्योम bond_setup_by_slave(काष्ठा net_device *bond_dev,
				काष्ठा net_device *slave_dev)
अणु
	bond_dev->header_ops	    = slave_dev->header_ops;

	bond_dev->type		    = slave_dev->type;
	bond_dev->hard_header_len   = slave_dev->hard_header_len;
	bond_dev->needed_headroom   = slave_dev->needed_headroom;
	bond_dev->addr_len	    = slave_dev->addr_len;

	स_नकल(bond_dev->broadcast, slave_dev->broadcast,
		slave_dev->addr_len);
पूर्ण

/* On bonding slaves other than the currently active slave, suppress
 * duplicates except क्रम alb non-mcast/bcast.
 */
अटल bool bond_should_deliver_exact_match(काष्ठा sk_buff *skb,
					    काष्ठा slave *slave,
					    काष्ठा bonding *bond)
अणु
	अगर (bond_is_slave_inactive(slave)) अणु
		अगर (BOND_MODE(bond) == BOND_MODE_ALB &&
		    skb->pkt_type != PACKET_BROADCAST &&
		    skb->pkt_type != PACKET_MULTICAST)
			वापस false;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल rx_handler_result_t bond_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा slave *slave;
	काष्ठा bonding *bond;
	पूर्णांक (*recv_probe)(स्थिर काष्ठा sk_buff *, काष्ठा bonding *,
			  काष्ठा slave *);
	पूर्णांक ret = RX_HANDLER_ANOTHER;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस RX_HANDLER_CONSUMED;

	*pskb = skb;

	slave = bond_slave_get_rcu(skb->dev);
	bond = slave->bond;

	recv_probe = READ_ONCE(bond->recv_probe);
	अगर (recv_probe) अणु
		ret = recv_probe(skb, bond, slave);
		अगर (ret == RX_HANDLER_CONSUMED) अणु
			consume_skb(skb);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * For packets determined by bond_should_deliver_exact_match() call to
	 * be suppressed we want to make an exception क्रम link-local packets.
	 * This is necessary क्रम e.g. LLDP daemons to be able to monitor
	 * inactive slave links without being क्रमced to bind to them
	 * explicitly.
	 *
	 * At the same समय, packets that are passed to the bonding master
	 * (including link-local ones) can have their originating पूर्णांकerface
	 * determined via PACKET_ORIGDEV socket option.
	 */
	अगर (bond_should_deliver_exact_match(skb, slave, bond)) अणु
		अगर (is_link_local_ether_addr(eth_hdr(skb)->h_dest))
			वापस RX_HANDLER_PASS;
		वापस RX_HANDLER_EXACT;
	पूर्ण

	skb->dev = bond->dev;

	अगर (BOND_MODE(bond) == BOND_MODE_ALB &&
	    netअगर_is_bridge_port(bond->dev) &&
	    skb->pkt_type == PACKET_HOST) अणु

		अगर (unlikely(skb_cow_head(skb,
					  skb->data - skb_mac_header(skb)))) अणु
			kमुक्त_skb(skb);
			वापस RX_HANDLER_CONSUMED;
		पूर्ण
		bond_hw_addr_copy(eth_hdr(skb)->h_dest, bond->dev->dev_addr,
				  bond->dev->addr_len);
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत netdev_lag_tx_type bond_lag_tx_type(काष्ठा bonding *bond)
अणु
	चयन (BOND_MODE(bond)) अणु
	हाल BOND_MODE_ROUNDROBIN:
		वापस NETDEV_LAG_TX_TYPE_ROUNDROBIN;
	हाल BOND_MODE_ACTIVEBACKUP:
		वापस NETDEV_LAG_TX_TYPE_ACTIVEBACKUP;
	हाल BOND_MODE_BROADCAST:
		वापस NETDEV_LAG_TX_TYPE_BROADCAST;
	हाल BOND_MODE_XOR:
	हाल BOND_MODE_8023AD:
		वापस NETDEV_LAG_TX_TYPE_HASH;
	शेष:
		वापस NETDEV_LAG_TX_TYPE_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत netdev_lag_hash bond_lag_hash_type(काष्ठा bonding *bond,
					       क्रमागत netdev_lag_tx_type type)
अणु
	अगर (type != NETDEV_LAG_TX_TYPE_HASH)
		वापस NETDEV_LAG_HASH_NONE;

	चयन (bond->params.xmit_policy) अणु
	हाल BOND_XMIT_POLICY_LAYER2:
		वापस NETDEV_LAG_HASH_L2;
	हाल BOND_XMIT_POLICY_LAYER34:
		वापस NETDEV_LAG_HASH_L34;
	हाल BOND_XMIT_POLICY_LAYER23:
		वापस NETDEV_LAG_HASH_L23;
	हाल BOND_XMIT_POLICY_ENCAP23:
		वापस NETDEV_LAG_HASH_E23;
	हाल BOND_XMIT_POLICY_ENCAP34:
		वापस NETDEV_LAG_HASH_E34;
	हाल BOND_XMIT_POLICY_VLAN_SRCMAC:
		वापस NETDEV_LAG_HASH_VLAN_SRCMAC;
	शेष:
		वापस NETDEV_LAG_HASH_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक bond_master_upper_dev_link(काष्ठा bonding *bond, काष्ठा slave *slave,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_lag_upper_info lag_upper_info;
	क्रमागत netdev_lag_tx_type type;

	type = bond_lag_tx_type(bond);
	lag_upper_info.tx_type = type;
	lag_upper_info.hash_type = bond_lag_hash_type(bond, type);

	वापस netdev_master_upper_dev_link(slave->dev, bond->dev, slave,
					    &lag_upper_info, extack);
पूर्ण

अटल व्योम bond_upper_dev_unlink(काष्ठा bonding *bond, काष्ठा slave *slave)
अणु
	netdev_upper_dev_unlink(slave->dev, bond->dev);
	slave->dev->flags &= ~IFF_SLAVE;
पूर्ण

अटल व्योम slave_kobj_release(काष्ठा kobject *kobj)
अणु
	काष्ठा slave *slave = to_slave(kobj);
	काष्ठा bonding *bond = bond_get_bond_by_slave(slave);

	cancel_delayed_work_sync(&slave->notअगरy_work);
	अगर (BOND_MODE(bond) == BOND_MODE_8023AD)
		kमुक्त(SLAVE_AD_INFO(slave));

	kमुक्त(slave);
पूर्ण

अटल काष्ठा kobj_type slave_ktype = अणु
	.release = slave_kobj_release,
#अगर_घोषित CONFIG_SYSFS
	.sysfs_ops = &slave_sysfs_ops,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक bond_kobj_init(काष्ठा slave *slave)
अणु
	पूर्णांक err;

	err = kobject_init_and_add(&slave->kobj, &slave_ktype,
				   &(slave->dev->dev.kobj), "bonding_slave");
	अगर (err)
		kobject_put(&slave->kobj);

	वापस err;
पूर्ण

अटल काष्ठा slave *bond_alloc_slave(काष्ठा bonding *bond,
				      काष्ठा net_device *slave_dev)
अणु
	काष्ठा slave *slave = शून्य;

	slave = kzalloc(माप(*slave), GFP_KERNEL);
	अगर (!slave)
		वापस शून्य;

	slave->bond = bond;
	slave->dev = slave_dev;
	INIT_DELAYED_WORK(&slave->notअगरy_work, bond_netdev_notअगरy_work);

	अगर (bond_kobj_init(slave))
		वापस शून्य;

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		SLAVE_AD_INFO(slave) = kzalloc(माप(काष्ठा ad_slave_info),
					       GFP_KERNEL);
		अगर (!SLAVE_AD_INFO(slave)) अणु
			kobject_put(&slave->kobj);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस slave;
पूर्ण

अटल व्योम bond_fill_अगरbond(काष्ठा bonding *bond, काष्ठा अगरbond *info)
अणु
	info->bond_mode = BOND_MODE(bond);
	info->miimon = bond->params.miimon;
	info->num_slaves = bond->slave_cnt;
पूर्ण

अटल व्योम bond_fill_अगरslave(काष्ठा slave *slave, काष्ठा अगरslave *info)
अणु
	म_नकल(info->slave_name, slave->dev->name);
	info->link = slave->link;
	info->state = bond_slave_state(slave);
	info->link_failure_count = slave->link_failure_count;
पूर्ण

अटल व्योम bond_netdev_notअगरy_work(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा slave *slave = container_of(_work, काष्ठा slave,
					   notअगरy_work.work);

	अगर (rtnl_trylock()) अणु
		काष्ठा netdev_bonding_info binfo;

		bond_fill_अगरslave(slave, &binfo.slave);
		bond_fill_अगरbond(slave->bond, &binfo.master);
		netdev_bonding_info_change(slave->dev, &binfo);
		rtnl_unlock();
	पूर्ण अन्यथा अणु
		queue_delayed_work(slave->bond->wq, &slave->notअगरy_work, 1);
	पूर्ण
पूर्ण

व्योम bond_queue_slave_event(काष्ठा slave *slave)
अणु
	queue_delayed_work(slave->bond->wq, &slave->notअगरy_work, 0);
पूर्ण

व्योम bond_lower_state_changed(काष्ठा slave *slave)
अणु
	काष्ठा netdev_lag_lower_state_info info;

	info.link_up = slave->link == BOND_LINK_UP ||
		       slave->link == BOND_LINK_FAIL;
	info.tx_enabled = bond_is_active_slave(slave);
	netdev_lower_state_changed(slave->dev, &info);
पूर्ण

/* enslave device <slave> to bond device <master> */
पूर्णांक bond_enslave(काष्ठा net_device *bond_dev, काष्ठा net_device *slave_dev,
		 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	स्थिर काष्ठा net_device_ops *slave_ops = slave_dev->netdev_ops;
	काष्ठा slave *new_slave = शून्य, *prev_slave;
	काष्ठा sockaddr_storage ss;
	पूर्णांक link_reporting;
	पूर्णांक res = 0, i;

	अगर (!bond->params.use_carrier &&
	    slave_dev->ethtool_ops->get_link == शून्य &&
	    slave_ops->nकरो_करो_ioctl == शून्य) अणु
		slave_warn(bond_dev, slave_dev, "no link monitoring support\n");
	पूर्ण

	/* alपढ़ोy in-use? */
	अगर (netdev_is_rx_handler_busy(slave_dev)) अणु
		NL_SET_ERR_MSG(extack, "Device is in use and cannot be enslaved");
		slave_err(bond_dev, slave_dev,
			  "Error: Device is in use and cannot be enslaved\n");
		वापस -EBUSY;
	पूर्ण

	अगर (bond_dev == slave_dev) अणु
		NL_SET_ERR_MSG(extack, "Cannot enslave bond to itself.");
		netdev_err(bond_dev, "cannot enslave bond to itself.\n");
		वापस -EPERM;
	पूर्ण

	/* vlan challenged mutual exclusion */
	/* no need to lock since we're रक्षित by rtnl_lock */
	अगर (slave_dev->features & NETIF_F_VLAN_CHALLENGED) अणु
		slave_dbg(bond_dev, slave_dev, "is NETIF_F_VLAN_CHALLENGED\n");
		अगर (vlan_uses_dev(bond_dev)) अणु
			NL_SET_ERR_MSG(extack, "Can not enslave VLAN challenged device to VLAN enabled bond");
			slave_err(bond_dev, slave_dev, "Error: cannot enslave VLAN challenged slave on VLAN enabled bond\n");
			वापस -EPERM;
		पूर्ण अन्यथा अणु
			slave_warn(bond_dev, slave_dev, "enslaved VLAN challenged slave. Adding VLANs will be blocked as long as it is part of bond.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		slave_dbg(bond_dev, slave_dev, "is !NETIF_F_VLAN_CHALLENGED\n");
	पूर्ण

	अगर (slave_dev->features & NETIF_F_HW_ESP)
		slave_dbg(bond_dev, slave_dev, "is esp-hw-offload capable\n");

	/* Old अगरenslave binaries are no दीर्घer supported.  These can
	 * be identअगरied with moderate accuracy by the state of the slave:
	 * the current अगरenslave will set the पूर्णांकerface करोwn prior to
	 * enslaving it; the old अगरenslave will not.
	 */
	अगर (slave_dev->flags & IFF_UP) अणु
		NL_SET_ERR_MSG(extack, "Device can not be enslaved while up");
		slave_err(bond_dev, slave_dev, "slave is up - this may be due to an out of date ifenslave\n");
		वापस -EPERM;
	पूर्ण

	/* set bonding device ether type by slave - bonding netdevices are
	 * created with ether_setup, so when the slave type is not ARPHRD_ETHER
	 * there is a need to override some of the type dependent attribs/funcs.
	 *
	 * bond ether type mutual exclusion - करोn't allow slaves of dissimilar
	 * ether type (eg ARPHRD_ETHER and ARPHRD_INFINIBAND) share the same bond
	 */
	अगर (!bond_has_slaves(bond)) अणु
		अगर (bond_dev->type != slave_dev->type) अणु
			slave_dbg(bond_dev, slave_dev, "change device type from %d to %d\n",
				  bond_dev->type, slave_dev->type);

			res = call_netdevice_notअगरiers(NETDEV_PRE_TYPE_CHANGE,
						       bond_dev);
			res = notअगरier_to_त्रुटि_सं(res);
			अगर (res) अणु
				slave_err(bond_dev, slave_dev, "refused to change device type\n");
				वापस -EBUSY;
			पूर्ण

			/* Flush unicast and multicast addresses */
			dev_uc_flush(bond_dev);
			dev_mc_flush(bond_dev);

			अगर (slave_dev->type != ARPHRD_ETHER)
				bond_setup_by_slave(bond_dev, slave_dev);
			अन्यथा अणु
				ether_setup(bond_dev);
				bond_dev->priv_flags &= ~IFF_TX_SKB_SHARING;
			पूर्ण

			call_netdevice_notअगरiers(NETDEV_POST_TYPE_CHANGE,
						 bond_dev);
		पूर्ण
	पूर्ण अन्यथा अगर (bond_dev->type != slave_dev->type) अणु
		NL_SET_ERR_MSG(extack, "Device type is different from other slaves");
		slave_err(bond_dev, slave_dev, "ether type (%d) is different from other slaves (%d), can not enslave it\n",
			  slave_dev->type, bond_dev->type);
		वापस -EINVAL;
	पूर्ण

	अगर (slave_dev->type == ARPHRD_INFINIBAND &&
	    BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP) अणु
		NL_SET_ERR_MSG(extack, "Only active-backup mode is supported for infiniband slaves");
		slave_warn(bond_dev, slave_dev, "Type (%d) supports only active-backup mode\n",
			   slave_dev->type);
		res = -EOPNOTSUPP;
		जाओ err_unकरो_flags;
	पूर्ण

	अगर (!slave_ops->nकरो_set_mac_address ||
	    slave_dev->type == ARPHRD_INFINIBAND) अणु
		slave_warn(bond_dev, slave_dev, "The slave device specified does not support setting the MAC address\n");
		अगर (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP &&
		    bond->params.fail_over_mac != BOND_FOM_ACTIVE) अणु
			अगर (!bond_has_slaves(bond)) अणु
				bond->params.fail_over_mac = BOND_FOM_ACTIVE;
				slave_warn(bond_dev, slave_dev, "Setting fail_over_mac to active for active-backup mode\n");
			पूर्ण अन्यथा अणु
				NL_SET_ERR_MSG(extack, "Slave device does not support setting the MAC address, but fail_over_mac is not set to active");
				slave_err(bond_dev, slave_dev, "The slave device specified does not support setting the MAC address, but fail_over_mac is not set to active\n");
				res = -EOPNOTSUPP;
				जाओ err_unकरो_flags;
			पूर्ण
		पूर्ण
	पूर्ण

	call_netdevice_notअगरiers(NETDEV_JOIN, slave_dev);

	/* If this is the first slave, then we need to set the master's hardware
	 * address to be the same as the slave's.
	 */
	अगर (!bond_has_slaves(bond) &&
	    bond->dev->addr_assign_type == NET_ADDR_RANDOM) अणु
		res = bond_set_dev_addr(bond->dev, slave_dev);
		अगर (res)
			जाओ err_unकरो_flags;
	पूर्ण

	new_slave = bond_alloc_slave(bond, slave_dev);
	अगर (!new_slave) अणु
		res = -ENOMEM;
		जाओ err_unकरो_flags;
	पूर्ण

	/* Set the new_slave's queue_id to be zero.  Queue ID mapping
	 * is set via sysfs or module option अगर desired.
	 */
	new_slave->queue_id = 0;

	/* Save slave's original mtu and then set it to match the bond */
	new_slave->original_mtu = slave_dev->mtu;
	res = dev_set_mtu(slave_dev, bond->dev->mtu);
	अगर (res) अणु
		slave_err(bond_dev, slave_dev, "Error %d calling dev_set_mtu\n", res);
		जाओ err_मुक्त;
	पूर्ण

	/* Save slave's original ("permanent") mac address क्रम modes
	 * that need it, and क्रम restoring it upon release, and then
	 * set it to the master's address
	 */
	bond_hw_addr_copy(new_slave->perm_hwaddr, slave_dev->dev_addr,
			  slave_dev->addr_len);

	अगर (!bond->params.fail_over_mac ||
	    BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP) अणु
		/* Set slave to master's mac address.  The application alपढ़ोy
		 * set the master's mac address to that of the first slave
		 */
		स_नकल(ss.__data, bond_dev->dev_addr, bond_dev->addr_len);
		ss.ss_family = slave_dev->type;
		res = dev_set_mac_address(slave_dev, (काष्ठा sockaddr *)&ss,
					  extack);
		अगर (res) अणु
			slave_err(bond_dev, slave_dev, "Error %d calling set_mac_address\n", res);
			जाओ err_restore_mtu;
		पूर्ण
	पूर्ण

	/* set slave flag beक्रमe खोलो to prevent IPv6 addrconf */
	slave_dev->flags |= IFF_SLAVE;

	/* खोलो the slave since the application बंदd it */
	res = dev_खोलो(slave_dev, extack);
	अगर (res) अणु
		slave_err(bond_dev, slave_dev, "Opening slave failed\n");
		जाओ err_restore_mac;
	पूर्ण

	slave_dev->priv_flags |= IFF_BONDING;
	/* initialize slave stats */
	dev_get_stats(new_slave->dev, &new_slave->slave_stats);

	अगर (bond_is_lb(bond)) अणु
		/* bond_alb_init_slave() must be called beक्रमe all other stages since
		 * it might fail and we करो not want to have to unकरो everything
		 */
		res = bond_alb_init_slave(bond, new_slave);
		अगर (res)
			जाओ err_बंद;
	पूर्ण

	res = vlan_vids_add_by_dev(slave_dev, bond_dev);
	अगर (res) अणु
		slave_err(bond_dev, slave_dev, "Couldn't add bond vlan ids\n");
		जाओ err_बंद;
	पूर्ण

	prev_slave = bond_last_slave(bond);

	new_slave->delay = 0;
	new_slave->link_failure_count = 0;

	अगर (bond_update_speed_duplex(new_slave) &&
	    bond_needs_speed_duplex(bond))
		new_slave->link = BOND_LINK_DOWN;

	new_slave->last_rx = jअगरfies -
		(msecs_to_jअगरfies(bond->params.arp_पूर्णांकerval) + 1);
	क्रम (i = 0; i < BOND_MAX_ARP_TARGETS; i++)
		new_slave->target_last_arp_rx[i] = new_slave->last_rx;

	अगर (bond->params.miimon && !bond->params.use_carrier) अणु
		link_reporting = bond_check_dev_link(bond, slave_dev, 1);

		अगर ((link_reporting == -1) && !bond->params.arp_पूर्णांकerval) अणु
			/* miimon is set but a bonded network driver
			 * करोes not support ETHTOOL/MII and
			 * arp_पूर्णांकerval is not set.  Note: अगर
			 * use_carrier is enabled, we will never go
			 * here (because netअगर_carrier is always
			 * supported); thus, we करोn't need to change
			 * the messages क्रम netअगर_carrier.
			 */
			slave_warn(bond_dev, slave_dev, "MII and ETHTOOL support not available for slave, and arp_interval/arp_ip_target module parameters not specified, thus bonding will not detect link failures! see bonding.txt for details\n");
		पूर्ण अन्यथा अगर (link_reporting == -1) अणु
			/* unable get link status using mii/ethtool */
			slave_warn(bond_dev, slave_dev, "can't get link status from slave; the network driver associated with this interface does not support MII or ETHTOOL link status reporting, thus miimon has no effect on this interface\n");
		पूर्ण
	पूर्ण

	/* check क्रम initial state */
	new_slave->link = BOND_LINK_NOCHANGE;
	अगर (bond->params.miimon) अणु
		अगर (bond_check_dev_link(bond, slave_dev, 0) == BMSR_LSTATUS) अणु
			अगर (bond->params.updelay) अणु
				bond_set_slave_link_state(new_slave,
							  BOND_LINK_BACK,
							  BOND_SLAVE_NOTIFY_NOW);
				new_slave->delay = bond->params.updelay;
			पूर्ण अन्यथा अणु
				bond_set_slave_link_state(new_slave,
							  BOND_LINK_UP,
							  BOND_SLAVE_NOTIFY_NOW);
			पूर्ण
		पूर्ण अन्यथा अणु
			bond_set_slave_link_state(new_slave, BOND_LINK_DOWN,
						  BOND_SLAVE_NOTIFY_NOW);
		पूर्ण
	पूर्ण अन्यथा अगर (bond->params.arp_पूर्णांकerval) अणु
		bond_set_slave_link_state(new_slave,
					  (netअगर_carrier_ok(slave_dev) ?
					  BOND_LINK_UP : BOND_LINK_DOWN),
					  BOND_SLAVE_NOTIFY_NOW);
	पूर्ण अन्यथा अणु
		bond_set_slave_link_state(new_slave, BOND_LINK_UP,
					  BOND_SLAVE_NOTIFY_NOW);
	पूर्ण

	अगर (new_slave->link != BOND_LINK_DOWN)
		new_slave->last_link_up = jअगरfies;
	slave_dbg(bond_dev, slave_dev, "Initial state of slave is BOND_LINK_%s\n",
		  new_slave->link == BOND_LINK_DOWN ? "DOWN" :
		  (new_slave->link == BOND_LINK_UP ? "UP" : "BACK"));

	अगर (bond_uses_primary(bond) && bond->params.primary[0]) अणु
		/* अगर there is a primary slave, remember it */
		अगर (म_भेद(bond->params.primary, new_slave->dev->name) == 0) अणु
			rcu_assign_poपूर्णांकer(bond->primary_slave, new_slave);
			bond->क्रमce_primary = true;
		पूर्ण
	पूर्ण

	चयन (BOND_MODE(bond)) अणु
	हाल BOND_MODE_ACTIVEBACKUP:
		bond_set_slave_inactive_flags(new_slave,
					      BOND_SLAVE_NOTIFY_NOW);
		अवरोध;
	हाल BOND_MODE_8023AD:
		/* in 802.3ad mode, the पूर्णांकernal mechanism
		 * will activate the slaves in the selected
		 * aggregator
		 */
		bond_set_slave_inactive_flags(new_slave, BOND_SLAVE_NOTIFY_NOW);
		/* अगर this is the first slave */
		अगर (!prev_slave) अणु
			SLAVE_AD_INFO(new_slave)->id = 1;
			/* Initialize AD with the number of बार that the AD समयr is called in 1 second
			 * can be called only after the mac address of the bond is set
			 */
			bond_3ad_initialize(bond, 1000/AD_TIMER_INTERVAL);
		पूर्ण अन्यथा अणु
			SLAVE_AD_INFO(new_slave)->id =
				SLAVE_AD_INFO(prev_slave)->id + 1;
		पूर्ण

		bond_3ad_bind_slave(new_slave);
		अवरोध;
	हाल BOND_MODE_TLB:
	हाल BOND_MODE_ALB:
		bond_set_active_slave(new_slave);
		bond_set_slave_inactive_flags(new_slave, BOND_SLAVE_NOTIFY_NOW);
		अवरोध;
	शेष:
		slave_dbg(bond_dev, slave_dev, "This slave is always active in trunk mode\n");

		/* always active in trunk mode */
		bond_set_active_slave(new_slave);

		/* In trunking mode there is little meaning to curr_active_slave
		 * anyway (it holds no special properties of the bond device),
		 * so we can change it without calling change_active_पूर्णांकerface()
		 */
		अगर (!rcu_access_poपूर्णांकer(bond->curr_active_slave) &&
		    new_slave->link == BOND_LINK_UP)
			rcu_assign_poपूर्णांकer(bond->curr_active_slave, new_slave);

		अवरोध;
	पूर्ण /* चयन(bond_mode) */

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	अगर (bond->dev->npinfo) अणु
		अगर (slave_enable_netpoll(new_slave)) अणु
			slave_info(bond_dev, slave_dev, "master_dev is using netpoll, but new slave device does not support netpoll\n");
			res = -EBUSY;
			जाओ err_detach;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (!(bond_dev->features & NETIF_F_LRO))
		dev_disable_lro(slave_dev);

	res = netdev_rx_handler_रेजिस्टर(slave_dev, bond_handle_frame,
					 new_slave);
	अगर (res) अणु
		slave_dbg(bond_dev, slave_dev, "Error %d calling netdev_rx_handler_register\n", res);
		जाओ err_detach;
	पूर्ण

	res = bond_master_upper_dev_link(bond, new_slave, extack);
	अगर (res) अणु
		slave_dbg(bond_dev, slave_dev, "Error %d calling bond_master_upper_dev_link\n", res);
		जाओ err_unरेजिस्टर;
	पूर्ण

	bond_lower_state_changed(new_slave);

	res = bond_sysfs_slave_add(new_slave);
	अगर (res) अणु
		slave_dbg(bond_dev, slave_dev, "Error %d calling bond_sysfs_slave_add\n", res);
		जाओ err_upper_unlink;
	पूर्ण

	/* If the mode uses primary, then the following is handled by
	 * bond_change_active_slave().
	 */
	अगर (!bond_uses_primary(bond)) अणु
		/* set promiscuity level to new slave */
		अगर (bond_dev->flags & IFF_PROMISC) अणु
			res = dev_set_promiscuity(slave_dev, 1);
			अगर (res)
				जाओ err_sysfs_del;
		पूर्ण

		/* set allmulti level to new slave */
		अगर (bond_dev->flags & IFF_ALLMULTI) अणु
			res = dev_set_allmulti(slave_dev, 1);
			अगर (res) अणु
				अगर (bond_dev->flags & IFF_PROMISC)
					dev_set_promiscuity(slave_dev, -1);
				जाओ err_sysfs_del;
			पूर्ण
		पूर्ण

		netअगर_addr_lock_bh(bond_dev);
		dev_mc_sync_multiple(slave_dev, bond_dev);
		dev_uc_sync_multiple(slave_dev, bond_dev);
		netअगर_addr_unlock_bh(bond_dev);

		अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
			/* add lacpdu mc addr to mc list */
			u8 lacpdu_multicast[ETH_ALEN] = MULTICAST_LACPDU_ADDR;

			dev_mc_add(slave_dev, lacpdu_multicast);
		पूर्ण
	पूर्ण

	bond->slave_cnt++;
	bond_compute_features(bond);
	bond_set_carrier(bond);

	अगर (bond_uses_primary(bond)) अणु
		block_netpoll_tx();
		bond_select_active_slave(bond);
		unblock_netpoll_tx();
	पूर्ण

	अगर (bond_mode_can_use_xmit_hash(bond))
		bond_update_slave_arr(bond, शून्य);


	slave_info(bond_dev, slave_dev, "Enslaving as %s interface with %s link\n",
		   bond_is_active_slave(new_slave) ? "an active" : "a backup",
		   new_slave->link != BOND_LINK_DOWN ? "an up" : "a down");

	/* enslave is successful */
	bond_queue_slave_event(new_slave);
	वापस 0;

/* Unकरो stages on error */
err_sysfs_del:
	bond_sysfs_slave_del(new_slave);

err_upper_unlink:
	bond_upper_dev_unlink(bond, new_slave);

err_unरेजिस्टर:
	netdev_rx_handler_unरेजिस्टर(slave_dev);

err_detach:
	vlan_vids_del_by_dev(slave_dev, bond_dev);
	अगर (rcu_access_poपूर्णांकer(bond->primary_slave) == new_slave)
		RCU_INIT_POINTER(bond->primary_slave, शून्य);
	अगर (rcu_access_poपूर्णांकer(bond->curr_active_slave) == new_slave) अणु
		block_netpoll_tx();
		bond_change_active_slave(bond, शून्य);
		bond_select_active_slave(bond);
		unblock_netpoll_tx();
	पूर्ण
	/* either primary_slave or curr_active_slave might've changed */
	synchronize_rcu();
	slave_disable_netpoll(new_slave);

err_बंद:
	अगर (!netअगर_is_bond_master(slave_dev))
		slave_dev->priv_flags &= ~IFF_BONDING;
	dev_बंद(slave_dev);

err_restore_mac:
	slave_dev->flags &= ~IFF_SLAVE;
	अगर (!bond->params.fail_over_mac ||
	    BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP) अणु
		/* XXX TODO - fom follow mode needs to change master's
		 * MAC अगर this slave's MAC is in use by the bond, or at
		 * least prपूर्णांक a warning.
		 */
		bond_hw_addr_copy(ss.__data, new_slave->perm_hwaddr,
				  new_slave->dev->addr_len);
		ss.ss_family = slave_dev->type;
		dev_set_mac_address(slave_dev, (काष्ठा sockaddr *)&ss, शून्य);
	पूर्ण

err_restore_mtu:
	dev_set_mtu(slave_dev, new_slave->original_mtu);

err_मुक्त:
	kobject_put(&new_slave->kobj);

err_unकरो_flags:
	/* Enslave of first slave has failed and we need to fix master's mac */
	अगर (!bond_has_slaves(bond)) अणु
		अगर (ether_addr_equal_64bits(bond_dev->dev_addr,
					    slave_dev->dev_addr))
			eth_hw_addr_अक्रमom(bond_dev);
		अगर (bond_dev->type != ARPHRD_ETHER) अणु
			dev_बंद(bond_dev);
			ether_setup(bond_dev);
			bond_dev->flags |= IFF_MASTER;
			bond_dev->priv_flags &= ~IFF_TX_SKB_SHARING;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

/* Try to release the slave device <slave> from the bond device <master>
 * It is legal to access curr_active_slave without a lock because all the function
 * is RTNL-locked. If "all" is true it means that the function is being called
 * जबतक destroying a bond पूर्णांकerface and all slaves are being released.
 *
 * The rules क्रम slave state should be:
 *   क्रम Active/Backup:
 *     Active stays on all backups go करोwn
 *   क्रम Bonded connections:
 *     The first up पूर्णांकerface should be left on and all others करोwned.
 */
अटल पूर्णांक __bond_release_one(काष्ठा net_device *bond_dev,
			      काष्ठा net_device *slave_dev,
			      bool all, bool unरेजिस्टर)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *slave, *oldcurrent;
	काष्ठा sockaddr_storage ss;
	पूर्णांक old_flags = bond_dev->flags;
	netdev_features_t old_features = bond_dev->features;

	/* slave is not a slave or master is not master of this slave */
	अगर (!(slave_dev->flags & IFF_SLAVE) ||
	    !netdev_has_upper_dev(slave_dev, bond_dev)) अणु
		slave_dbg(bond_dev, slave_dev, "cannot release slave\n");
		वापस -EINVAL;
	पूर्ण

	block_netpoll_tx();

	slave = bond_get_slave_by_dev(bond, slave_dev);
	अगर (!slave) अणु
		/* not a slave of this bond */
		slave_info(bond_dev, slave_dev, "interface not enslaved\n");
		unblock_netpoll_tx();
		वापस -EINVAL;
	पूर्ण

	bond_set_slave_inactive_flags(slave, BOND_SLAVE_NOTIFY_NOW);

	bond_sysfs_slave_del(slave);

	/* recompute stats just beक्रमe removing the slave */
	bond_get_stats(bond->dev, &bond->bond_stats);

	bond_upper_dev_unlink(bond, slave);
	/* unरेजिस्टर rx_handler early so bond_handle_frame wouldn't be called
	 * क्रम this slave anymore.
	 */
	netdev_rx_handler_unरेजिस्टर(slave_dev);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD)
		bond_3ad_unbind_slave(slave);

	अगर (bond_mode_can_use_xmit_hash(bond))
		bond_update_slave_arr(bond, slave);

	slave_info(bond_dev, slave_dev, "Releasing %s interface\n",
		    bond_is_active_slave(slave) ? "active" : "backup");

	oldcurrent = rcu_access_poपूर्णांकer(bond->curr_active_slave);

	RCU_INIT_POINTER(bond->current_arp_slave, शून्य);

	अगर (!all && (!bond->params.fail_over_mac ||
		     BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP)) अणु
		अगर (ether_addr_equal_64bits(bond_dev->dev_addr, slave->perm_hwaddr) &&
		    bond_has_slaves(bond))
			slave_warn(bond_dev, slave_dev, "the permanent HWaddr of slave - %pM - is still in use by bond - set the HWaddr of slave to a different address to avoid conflicts\n",
				   slave->perm_hwaddr);
	पूर्ण

	अगर (rtnl_dereference(bond->primary_slave) == slave)
		RCU_INIT_POINTER(bond->primary_slave, शून्य);

	अगर (oldcurrent == slave)
		bond_change_active_slave(bond, शून्य);

	अगर (bond_is_lb(bond)) अणु
		/* Must be called only after the slave has been
		 * detached from the list and the curr_active_slave
		 * has been cleared (अगर our_slave == old_current),
		 * but beक्रमe a new active slave is selected.
		 */
		bond_alb_deinit_slave(bond, slave);
	पूर्ण

	अगर (all) अणु
		RCU_INIT_POINTER(bond->curr_active_slave, शून्य);
	पूर्ण अन्यथा अगर (oldcurrent == slave) अणु
		/* Note that we hold RTNL over this sequence, so there
		 * is no concern that another slave add/हटाओ event
		 * will पूर्णांकerfere.
		 */
		bond_select_active_slave(bond);
	पूर्ण

	अगर (!bond_has_slaves(bond)) अणु
		bond_set_carrier(bond);
		eth_hw_addr_अक्रमom(bond_dev);
	पूर्ण

	unblock_netpoll_tx();
	synchronize_rcu();
	bond->slave_cnt--;

	अगर (!bond_has_slaves(bond)) अणु
		call_netdevice_notअगरiers(NETDEV_CHANGEADDR, bond->dev);
		call_netdevice_notअगरiers(NETDEV_RELEASE, bond->dev);
	पूर्ण

	bond_compute_features(bond);
	अगर (!(bond_dev->features & NETIF_F_VLAN_CHALLENGED) &&
	    (old_features & NETIF_F_VLAN_CHALLENGED))
		slave_info(bond_dev, slave_dev, "last VLAN challenged slave left bond - VLAN blocking is removed\n");

	vlan_vids_del_by_dev(slave_dev, bond_dev);

	/* If the mode uses primary, then this हाल was handled above by
	 * bond_change_active_slave(..., शून्य)
	 */
	अगर (!bond_uses_primary(bond)) अणु
		/* unset promiscuity level from slave
		 * NOTE: The NETDEV_CHANGEADDR call above may change the value
		 * of the IFF_PROMISC flag in the bond_dev, but we need the
		 * value of that flag beक्रमe that change, as that was the value
		 * when this slave was attached, so we cache at the start of the
		 * function and use it here. Same goes क्रम ALLMULTI below
		 */
		अगर (old_flags & IFF_PROMISC)
			dev_set_promiscuity(slave_dev, -1);

		/* unset allmulti level from slave */
		अगर (old_flags & IFF_ALLMULTI)
			dev_set_allmulti(slave_dev, -1);

		bond_hw_addr_flush(bond_dev, slave_dev);
	पूर्ण

	slave_disable_netpoll(slave);

	/* बंद slave beक्रमe restoring its mac address */
	dev_बंद(slave_dev);

	अगर (bond->params.fail_over_mac != BOND_FOM_ACTIVE ||
	    BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP) अणु
		/* restore original ("permanent") mac address */
		bond_hw_addr_copy(ss.__data, slave->perm_hwaddr,
				  slave->dev->addr_len);
		ss.ss_family = slave_dev->type;
		dev_set_mac_address(slave_dev, (काष्ठा sockaddr *)&ss, शून्य);
	पूर्ण

	अगर (unरेजिस्टर)
		__dev_set_mtu(slave_dev, slave->original_mtu);
	अन्यथा
		dev_set_mtu(slave_dev, slave->original_mtu);

	अगर (!netअगर_is_bond_master(slave_dev))
		slave_dev->priv_flags &= ~IFF_BONDING;

	kobject_put(&slave->kobj);

	वापस 0;
पूर्ण

/* A wrapper used because of nकरो_del_link */
पूर्णांक bond_release(काष्ठा net_device *bond_dev, काष्ठा net_device *slave_dev)
अणु
	वापस __bond_release_one(bond_dev, slave_dev, false, false);
पूर्ण

/* First release a slave and then destroy the bond अगर no more slaves are left.
 * Must be under rtnl_lock when this function is called.
 */
अटल पूर्णांक bond_release_and_destroy(काष्ठा net_device *bond_dev,
				    काष्ठा net_device *slave_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	पूर्णांक ret;

	ret = __bond_release_one(bond_dev, slave_dev, false, true);
	अगर (ret == 0 && !bond_has_slaves(bond) &&
	    bond_dev->reg_state != NETREG_UNREGISTERING) अणु
		bond_dev->priv_flags |= IFF_DISABLE_NETPOLL;
		netdev_info(bond_dev, "Destroying bond\n");
		bond_हटाओ_proc_entry(bond);
		unरेजिस्टर_netdevice(bond_dev);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम bond_info_query(काष्ठा net_device *bond_dev, काष्ठा अगरbond *info)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	bond_fill_अगरbond(bond, info);
पूर्ण

अटल पूर्णांक bond_slave_info_query(काष्ठा net_device *bond_dev, काष्ठा अगरslave *info)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा list_head *iter;
	पूर्णांक i = 0, res = -ENODEV;
	काष्ठा slave *slave;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (i++ == (पूर्णांक)info->slave_id) अणु
			res = 0;
			bond_fill_अगरslave(slave, info);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

/*-------------------------------- Monitoring -------------------------------*/

/* called with rcu_पढ़ो_lock() */
अटल पूर्णांक bond_miimon_inspect(काष्ठा bonding *bond)
अणु
	पूर्णांक link_state, commit = 0;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	bool ignore_updelay;

	ignore_updelay = !rcu_dereference(bond->curr_active_slave);

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		bond_propose_link_state(slave, BOND_LINK_NOCHANGE);

		link_state = bond_check_dev_link(bond, slave->dev, 0);

		चयन (slave->link) अणु
		हाल BOND_LINK_UP:
			अगर (link_state)
				जारी;

			bond_propose_link_state(slave, BOND_LINK_FAIL);
			commit++;
			slave->delay = bond->params.करोwndelay;
			अगर (slave->delay) अणु
				slave_info(bond->dev, slave->dev, "link status down for %sinterface, disabling it in %d ms\n",
					   (BOND_MODE(bond) ==
					    BOND_MODE_ACTIVEBACKUP) ?
					    (bond_is_active_slave(slave) ?
					     "active " : "backup ") : "",
					   bond->params.करोwndelay * bond->params.miimon);
			पूर्ण
			fallthrough;
		हाल BOND_LINK_FAIL:
			अगर (link_state) अणु
				/* recovered beक्रमe करोwndelay expired */
				bond_propose_link_state(slave, BOND_LINK_UP);
				slave->last_link_up = jअगरfies;
				slave_info(bond->dev, slave->dev, "link status up again after %d ms\n",
					   (bond->params.करोwndelay - slave->delay) *
					   bond->params.miimon);
				commit++;
				जारी;
			पूर्ण

			अगर (slave->delay <= 0) अणु
				bond_propose_link_state(slave, BOND_LINK_DOWN);
				commit++;
				जारी;
			पूर्ण

			slave->delay--;
			अवरोध;

		हाल BOND_LINK_DOWN:
			अगर (!link_state)
				जारी;

			bond_propose_link_state(slave, BOND_LINK_BACK);
			commit++;
			slave->delay = bond->params.updelay;

			अगर (slave->delay) अणु
				slave_info(bond->dev, slave->dev, "link status up, enabling it in %d ms\n",
					   ignore_updelay ? 0 :
					   bond->params.updelay *
					   bond->params.miimon);
			पूर्ण
			fallthrough;
		हाल BOND_LINK_BACK:
			अगर (!link_state) अणु
				bond_propose_link_state(slave, BOND_LINK_DOWN);
				slave_info(bond->dev, slave->dev, "link status down again after %d ms\n",
					   (bond->params.updelay - slave->delay) *
					   bond->params.miimon);
				commit++;
				जारी;
			पूर्ण

			अगर (ignore_updelay)
				slave->delay = 0;

			अगर (slave->delay <= 0) अणु
				bond_propose_link_state(slave, BOND_LINK_UP);
				commit++;
				ignore_updelay = false;
				जारी;
			पूर्ण

			slave->delay--;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस commit;
पूर्ण

अटल व्योम bond_miimon_link_change(काष्ठा bonding *bond,
				    काष्ठा slave *slave,
				    अक्षर link)
अणु
	चयन (BOND_MODE(bond)) अणु
	हाल BOND_MODE_8023AD:
		bond_3ad_handle_link_change(slave, link);
		अवरोध;
	हाल BOND_MODE_TLB:
	हाल BOND_MODE_ALB:
		bond_alb_handle_link_change(bond, slave, link);
		अवरोध;
	हाल BOND_MODE_XOR:
		bond_update_slave_arr(bond, शून्य);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bond_miimon_commit(काष्ठा bonding *bond)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *slave, *primary;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		चयन (slave->link_new_state) अणु
		हाल BOND_LINK_NOCHANGE:
			/* For 802.3ad mode, check current slave speed and
			 * duplex again in हाल its port was disabled after
			 * invalid speed/duplex reporting but recovered beक्रमe
			 * link monitoring could make a decision on the actual
			 * link status
			 */
			अगर (BOND_MODE(bond) == BOND_MODE_8023AD &&
			    slave->link == BOND_LINK_UP)
				bond_3ad_adapter_speed_duplex_changed(slave);
			जारी;

		हाल BOND_LINK_UP:
			अगर (bond_update_speed_duplex(slave) &&
			    bond_needs_speed_duplex(bond)) अणु
				slave->link = BOND_LINK_DOWN;
				अगर (net_ratelimit())
					slave_warn(bond->dev, slave->dev,
						   "failed to get link speed/duplex\n");
				जारी;
			पूर्ण
			bond_set_slave_link_state(slave, BOND_LINK_UP,
						  BOND_SLAVE_NOTIFY_NOW);
			slave->last_link_up = jअगरfies;

			primary = rtnl_dereference(bond->primary_slave);
			अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
				/* prevent it from being the active one */
				bond_set_backup_slave(slave);
			पूर्ण अन्यथा अगर (BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP) अणु
				/* make it immediately active */
				bond_set_active_slave(slave);
			पूर्ण

			slave_info(bond->dev, slave->dev, "link status definitely up, %u Mbps %s duplex\n",
				   slave->speed == SPEED_UNKNOWN ? 0 : slave->speed,
				   slave->duplex ? "full" : "half");

			bond_miimon_link_change(bond, slave, BOND_LINK_UP);

			अगर (!bond->curr_active_slave || slave == primary)
				जाओ करो_failover;

			जारी;

		हाल BOND_LINK_DOWN:
			अगर (slave->link_failure_count < अच_पूर्णांक_उच्च)
				slave->link_failure_count++;

			bond_set_slave_link_state(slave, BOND_LINK_DOWN,
						  BOND_SLAVE_NOTIFY_NOW);

			अगर (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP ||
			    BOND_MODE(bond) == BOND_MODE_8023AD)
				bond_set_slave_inactive_flags(slave,
							      BOND_SLAVE_NOTIFY_NOW);

			slave_info(bond->dev, slave->dev, "link status definitely down, disabling slave\n");

			bond_miimon_link_change(bond, slave, BOND_LINK_DOWN);

			अगर (slave == rcu_access_poपूर्णांकer(bond->curr_active_slave))
				जाओ करो_failover;

			जारी;

		शेष:
			slave_err(bond->dev, slave->dev, "invalid new link %d on slave\n",
				  slave->link_new_state);
			bond_propose_link_state(slave, BOND_LINK_NOCHANGE);

			जारी;
		पूर्ण

करो_failover:
		block_netpoll_tx();
		bond_select_active_slave(bond);
		unblock_netpoll_tx();
	पूर्ण

	bond_set_carrier(bond);
पूर्ण

/* bond_mii_monitor
 *
 * Really a wrapper that splits the mii monitor पूर्णांकo two phases: an
 * inspection, then (अगर inspection indicates something needs to be करोne)
 * an acquisition of appropriate locks followed by a commit phase to
 * implement whatever link state changes are indicated.
 */
अटल व्योम bond_mii_monitor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bonding *bond = container_of(work, काष्ठा bonding,
					    mii_work.work);
	bool should_notअगरy_peers = false;
	bool commit;
	अचिन्हित दीर्घ delay;
	काष्ठा slave *slave;
	काष्ठा list_head *iter;

	delay = msecs_to_jअगरfies(bond->params.miimon);

	अगर (!bond_has_slaves(bond))
		जाओ re_arm;

	rcu_पढ़ो_lock();
	should_notअगरy_peers = bond_should_notअगरy_peers(bond);
	commit = !!bond_miimon_inspect(bond);
	अगर (bond->send_peer_notअगर) अणु
		rcu_पढ़ो_unlock();
		अगर (rtnl_trylock()) अणु
			bond->send_peer_notअगर--;
			rtnl_unlock();
		पूर्ण
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (commit) अणु
		/* Race aव्योमance with bond_बंद cancel of workqueue */
		अगर (!rtnl_trylock()) अणु
			delay = 1;
			should_notअगरy_peers = false;
			जाओ re_arm;
		पूर्ण

		bond_क्रम_each_slave(bond, slave, iter) अणु
			bond_commit_link_state(slave, BOND_SLAVE_NOTIFY_LATER);
		पूर्ण
		bond_miimon_commit(bond);

		rtnl_unlock();	/* might sleep, hold no other locks */
	पूर्ण

re_arm:
	अगर (bond->params.miimon)
		queue_delayed_work(bond->wq, &bond->mii_work, delay);

	अगर (should_notअगरy_peers) अणु
		अगर (!rtnl_trylock())
			वापस;
		call_netdevice_notअगरiers(NETDEV_NOTIFY_PEERS, bond->dev);
		rtnl_unlock();
	पूर्ण
पूर्ण

अटल पूर्णांक bond_upper_dev_walk(काष्ठा net_device *upper,
			       काष्ठा netdev_nested_priv *priv)
अणु
	__be32 ip = *(__be32 *)priv->data;

	वापस ip == bond_confirm_addr(upper, 0, ip);
पूर्ण

अटल bool bond_has_this_ip(काष्ठा bonding *bond, __be32 ip)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)&ip,
	पूर्ण;
	bool ret = false;

	अगर (ip == bond_confirm_addr(bond->dev, 0, ip))
		वापस true;

	rcu_पढ़ो_lock();
	अगर (netdev_walk_all_upper_dev_rcu(bond->dev, bond_upper_dev_walk, &priv))
		ret = true;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* We go to the (large) trouble of VLAN tagging ARP frames because
 * चयनes in VLAN mode (especially अगर ports are configured as
 * "native" to a VLAN) might not pass non-tagged frames.
 */
अटल व्योम bond_arp_send(काष्ठा slave *slave, पूर्णांक arp_op, __be32 dest_ip,
			  __be32 src_ip, काष्ठा bond_vlan_tag *tags)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा bond_vlan_tag *outer_tag = tags;
	काष्ठा net_device *slave_dev = slave->dev;
	काष्ठा net_device *bond_dev = slave->bond->dev;

	slave_dbg(bond_dev, slave_dev, "arp %d on slave: dst %pI4 src %pI4\n",
		  arp_op, &dest_ip, &src_ip);

	skb = arp_create(arp_op, ETH_P_ARP, dest_ip, slave_dev, src_ip,
			 शून्य, slave_dev->dev_addr, शून्य);

	अगर (!skb) अणु
		net_err_ratelimited("ARP packet allocation failed\n");
		वापस;
	पूर्ण

	अगर (!tags || tags->vlan_proto == VLAN_N_VID)
		जाओ xmit;

	tags++;

	/* Go through all the tags backwards and add them to the packet */
	जबतक (tags->vlan_proto != VLAN_N_VID) अणु
		अगर (!tags->vlan_id) अणु
			tags++;
			जारी;
		पूर्ण

		slave_dbg(bond_dev, slave_dev, "inner tag: proto %X vid %X\n",
			  ntohs(outer_tag->vlan_proto), tags->vlan_id);
		skb = vlan_insert_tag_set_proto(skb, tags->vlan_proto,
						tags->vlan_id);
		अगर (!skb) अणु
			net_err_ratelimited("failed to insert inner VLAN tag\n");
			वापस;
		पूर्ण

		tags++;
	पूर्ण
	/* Set the outer tag */
	अगर (outer_tag->vlan_id) अणु
		slave_dbg(bond_dev, slave_dev, "outer tag: proto %X vid %X\n",
			  ntohs(outer_tag->vlan_proto), outer_tag->vlan_id);
		__vlan_hwaccel_put_tag(skb, outer_tag->vlan_proto,
				       outer_tag->vlan_id);
	पूर्ण

xmit:
	arp_xmit(skb);
पूर्ण

/* Validate the device path between the @start_dev and the @end_dev.
 * The path is valid अगर the @end_dev is reachable through device
 * stacking.
 * When the path is validated, collect any vlan inक्रमmation in the
 * path.
 */
काष्ठा bond_vlan_tag *bond_verअगरy_device_path(काष्ठा net_device *start_dev,
					      काष्ठा net_device *end_dev,
					      पूर्णांक level)
अणु
	काष्ठा bond_vlan_tag *tags;
	काष्ठा net_device *upper;
	काष्ठा list_head  *iter;

	अगर (start_dev == end_dev) अणु
		tags = kसुस्मृति(level + 1, माप(*tags), GFP_ATOMIC);
		अगर (!tags)
			वापस ERR_PTR(-ENOMEM);
		tags[level].vlan_proto = VLAN_N_VID;
		वापस tags;
	पूर्ण

	netdev_क्रम_each_upper_dev_rcu(start_dev, upper, iter) अणु
		tags = bond_verअगरy_device_path(upper, end_dev, level + 1);
		अगर (IS_ERR_OR_शून्य(tags)) अणु
			अगर (IS_ERR(tags))
				वापस tags;
			जारी;
		पूर्ण
		अगर (is_vlan_dev(upper)) अणु
			tags[level].vlan_proto = vlan_dev_vlan_proto(upper);
			tags[level].vlan_id = vlan_dev_vlan_id(upper);
		पूर्ण

		वापस tags;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम bond_arp_send_all(काष्ठा bonding *bond, काष्ठा slave *slave)
अणु
	काष्ठा rtable *rt;
	काष्ठा bond_vlan_tag *tags;
	__be32 *tarमाला_लो = bond->params.arp_tarमाला_लो, addr;
	पूर्णांक i;

	क्रम (i = 0; i < BOND_MAX_ARP_TARGETS && tarमाला_लो[i]; i++) अणु
		slave_dbg(bond->dev, slave->dev, "%s: target %pI4\n",
			  __func__, &tarमाला_लो[i]);
		tags = शून्य;

		/* Find out through which dev should the packet go */
		rt = ip_route_output(dev_net(bond->dev), tarमाला_लो[i], 0,
				     RTO_ONLINK, 0);
		अगर (IS_ERR(rt)) अणु
			/* there's no route to target - try to send arp
			 * probe to generate any traffic (arp_validate=0)
			 */
			अगर (bond->params.arp_validate)
				net_warn_ratelimited("%s: no route to arp_ip_target %pI4 and arp_validate is set\n",
						     bond->dev->name,
						     &tarमाला_लो[i]);
			bond_arp_send(slave, ARPOP_REQUEST, tarमाला_लो[i],
				      0, tags);
			जारी;
		पूर्ण

		/* bond device itself */
		अगर (rt->dst.dev == bond->dev)
			जाओ found;

		rcu_पढ़ो_lock();
		tags = bond_verअगरy_device_path(bond->dev, rt->dst.dev, 0);
		rcu_पढ़ो_unlock();

		अगर (!IS_ERR_OR_शून्य(tags))
			जाओ found;

		/* Not our device - skip */
		slave_dbg(bond->dev, slave->dev, "no path to arp_ip_target %pI4 via rt.dev %s\n",
			   &tarमाला_लो[i], rt->dst.dev ? rt->dst.dev->name : "NULL");

		ip_rt_put(rt);
		जारी;

found:
		addr = bond_confirm_addr(rt->dst.dev, tarमाला_लो[i], 0);
		ip_rt_put(rt);
		bond_arp_send(slave, ARPOP_REQUEST, tarमाला_लो[i], addr, tags);
		kमुक्त(tags);
	पूर्ण
पूर्ण

अटल व्योम bond_validate_arp(काष्ठा bonding *bond, काष्ठा slave *slave, __be32 sip, __be32 tip)
अणु
	पूर्णांक i;

	अगर (!sip || !bond_has_this_ip(bond, tip)) अणु
		slave_dbg(bond->dev, slave->dev, "%s: sip %pI4 tip %pI4 not found\n",
			   __func__, &sip, &tip);
		वापस;
	पूर्ण

	i = bond_get_tarमाला_लो_ip(bond->params.arp_tarमाला_लो, sip);
	अगर (i == -1) अणु
		slave_dbg(bond->dev, slave->dev, "%s: sip %pI4 not found in targets\n",
			   __func__, &sip);
		वापस;
	पूर्ण
	slave->last_rx = jअगरfies;
	slave->target_last_arp_rx[i] = jअगरfies;
पूर्ण

पूर्णांक bond_arp_rcv(स्थिर काष्ठा sk_buff *skb, काष्ठा bonding *bond,
		 काष्ठा slave *slave)
अणु
	काष्ठा arphdr *arp = (काष्ठा arphdr *)skb->data;
	काष्ठा slave *curr_active_slave, *curr_arp_slave;
	अचिन्हित अक्षर *arp_ptr;
	__be32 sip, tip;
	पूर्णांक is_arp = skb->protocol == __cpu_to_be16(ETH_P_ARP);
	अचिन्हित पूर्णांक alen;

	अगर (!slave_करो_arp_validate(bond, slave)) अणु
		अगर ((slave_करो_arp_validate_only(bond) && is_arp) ||
		    !slave_करो_arp_validate_only(bond))
			slave->last_rx = jअगरfies;
		वापस RX_HANDLER_ANOTHER;
	पूर्ण अन्यथा अगर (!is_arp) अणु
		वापस RX_HANDLER_ANOTHER;
	पूर्ण

	alen = arp_hdr_len(bond->dev);

	slave_dbg(bond->dev, slave->dev, "%s: skb->dev %s\n",
		   __func__, skb->dev->name);

	अगर (alen > skb_headlen(skb)) अणु
		arp = kदो_स्मृति(alen, GFP_ATOMIC);
		अगर (!arp)
			जाओ out_unlock;
		अगर (skb_copy_bits(skb, 0, arp, alen) < 0)
			जाओ out_unlock;
	पूर्ण

	अगर (arp->ar_hln != bond->dev->addr_len ||
	    skb->pkt_type == PACKET_OTHERHOST ||
	    skb->pkt_type == PACKET_LOOPBACK ||
	    arp->ar_hrd != htons(ARPHRD_ETHER) ||
	    arp->ar_pro != htons(ETH_P_IP) ||
	    arp->ar_pln != 4)
		जाओ out_unlock;

	arp_ptr = (अचिन्हित अक्षर *)(arp + 1);
	arp_ptr += bond->dev->addr_len;
	स_नकल(&sip, arp_ptr, 4);
	arp_ptr += 4 + bond->dev->addr_len;
	स_नकल(&tip, arp_ptr, 4);

	slave_dbg(bond->dev, slave->dev, "%s: %s/%d av %d sv %d sip %pI4 tip %pI4\n",
		  __func__, slave->dev->name, bond_slave_state(slave),
		  bond->params.arp_validate, slave_करो_arp_validate(bond, slave),
		  &sip, &tip);

	curr_active_slave = rcu_dereference(bond->curr_active_slave);
	curr_arp_slave = rcu_dereference(bond->current_arp_slave);

	/* We 'trust' the received ARP enough to validate it अगर:
	 *
	 * (a) the slave receiving the ARP is active (which includes the
	 * current ARP slave, अगर any), or
	 *
	 * (b) the receiving slave isn't active, but there is a currently
	 * active slave and it received valid arp reply(s) after it became
	 * the currently active slave, or
	 *
	 * (c) there is an ARP slave that sent an ARP during the prior ARP
	 * पूर्णांकerval, and we receive an ARP reply on any slave.  We accept
	 * these because चयन FDB update delays may deliver the ARP
	 * reply to a slave other than the sender of the ARP request.
	 *
	 * Note: क्रम (b), backup slaves are receiving the broadcast ARP
	 * request, not a reply.  This request passes from the sending
	 * slave through the L2 चयन(es) to the receiving slave.  Since
	 * this is checking the request, sip/tip are swapped क्रम
	 * validation.
	 *
	 * This is करोne to aव्योम endless looping when we can't reach the
	 * arp_ip_target and fool ourselves with our own arp requests.
	 */
	अगर (bond_is_active_slave(slave))
		bond_validate_arp(bond, slave, sip, tip);
	अन्यथा अगर (curr_active_slave &&
		 समय_after(slave_last_rx(bond, curr_active_slave),
			    curr_active_slave->last_link_up))
		bond_validate_arp(bond, slave, tip, sip);
	अन्यथा अगर (curr_arp_slave && (arp->ar_op == htons(ARPOP_REPLY)) &&
		 bond_समय_in_पूर्णांकerval(bond,
				       dev_trans_start(curr_arp_slave->dev), 1))
		bond_validate_arp(bond, slave, sip, tip);

out_unlock:
	अगर (arp != (काष्ठा arphdr *)skb->data)
		kमुक्त(arp);
	वापस RX_HANDLER_ANOTHER;
पूर्ण

/* function to verअगरy अगर we're in the arp_पूर्णांकerval बारlice, वापसs true अगर
 * (last_act - arp_पूर्णांकerval) <= jअगरfies <= (last_act + mod * arp_पूर्णांकerval +
 * arp_पूर्णांकerval/2) . the arp_पूर्णांकerval/2 is needed क्रम really fast networks.
 */
अटल bool bond_समय_in_पूर्णांकerval(काष्ठा bonding *bond, अचिन्हित दीर्घ last_act,
				  पूर्णांक mod)
अणु
	पूर्णांक delta_in_ticks = msecs_to_jअगरfies(bond->params.arp_पूर्णांकerval);

	वापस समय_in_range(jअगरfies,
			     last_act - delta_in_ticks,
			     last_act + mod * delta_in_ticks + delta_in_ticks/2);
पूर्ण

/* This function is called regularly to monitor each slave's link
 * ensuring that traffic is being sent and received when arp monitoring
 * is used in load-balancing mode. अगर the adapter has been करोrmant, then an
 * arp is transmitted to generate traffic. see activebackup_arp_monitor क्रम
 * arp monitoring in active backup mode.
 */
अटल व्योम bond_loadbalance_arp_mon(काष्ठा bonding *bond)
अणु
	काष्ठा slave *slave, *oldcurrent;
	काष्ठा list_head *iter;
	पूर्णांक करो_failover = 0, slave_state_changed = 0;

	अगर (!bond_has_slaves(bond))
		जाओ re_arm;

	rcu_पढ़ो_lock();

	oldcurrent = rcu_dereference(bond->curr_active_slave);
	/* see अगर any of the previous devices are up now (i.e. they have
	 * xmt and rcv traffic). the curr_active_slave करोes not come पूर्णांकo
	 * the picture unless it is null. also, slave->last_link_up is not
	 * needed here because we send an arp on each slave and give a slave
	 * as दीर्घ as it needs to get the tx/rx within the delta.
	 * TODO: what about up/करोwn delay in arp mode? it wasn't here beक्रमe
	 *       so it can रुको
	 */
	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अचिन्हित दीर्घ trans_start = dev_trans_start(slave->dev);

		bond_propose_link_state(slave, BOND_LINK_NOCHANGE);

		अगर (slave->link != BOND_LINK_UP) अणु
			अगर (bond_समय_in_पूर्णांकerval(bond, trans_start, 1) &&
			    bond_समय_in_पूर्णांकerval(bond, slave->last_rx, 1)) अणु

				bond_propose_link_state(slave, BOND_LINK_UP);
				slave_state_changed = 1;

				/* primary_slave has no meaning in round-robin
				 * mode. the winकरोw of a slave being up and
				 * curr_active_slave being null after enslaving
				 * is बंदd.
				 */
				अगर (!oldcurrent) अणु
					slave_info(bond->dev, slave->dev, "link status definitely up\n");
					करो_failover = 1;
				पूर्ण अन्यथा अणु
					slave_info(bond->dev, slave->dev, "interface is now up\n");
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* slave->link == BOND_LINK_UP */

			/* not all चयनes will respond to an arp request
			 * when the source ip is 0, so करोn't take the link करोwn
			 * अगर we करोn't know our ip yet
			 */
			अगर (!bond_समय_in_पूर्णांकerval(bond, trans_start, 2) ||
			    !bond_समय_in_पूर्णांकerval(bond, slave->last_rx, 2)) अणु

				bond_propose_link_state(slave, BOND_LINK_DOWN);
				slave_state_changed = 1;

				अगर (slave->link_failure_count < अच_पूर्णांक_उच्च)
					slave->link_failure_count++;

				slave_info(bond->dev, slave->dev, "interface is now down\n");

				अगर (slave == oldcurrent)
					करो_failover = 1;
			पूर्ण
		पूर्ण

		/* note: अगर चयन is in round-robin mode, all links
		 * must tx arp to ensure all links rx an arp - otherwise
		 * links may oscillate or not come up at all; अगर चयन is
		 * in something like xor mode, there is nothing we can
		 * करो - all replies will be rx'ed on same link causing slaves
		 * to be unstable during low/no traffic periods
		 */
		अगर (bond_slave_is_up(slave))
			bond_arp_send_all(bond, slave);
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (करो_failover || slave_state_changed) अणु
		अगर (!rtnl_trylock())
			जाओ re_arm;

		bond_क्रम_each_slave(bond, slave, iter) अणु
			अगर (slave->link_new_state != BOND_LINK_NOCHANGE)
				slave->link = slave->link_new_state;
		पूर्ण

		अगर (slave_state_changed) अणु
			bond_slave_state_change(bond);
			अगर (BOND_MODE(bond) == BOND_MODE_XOR)
				bond_update_slave_arr(bond, शून्य);
		पूर्ण
		अगर (करो_failover) अणु
			block_netpoll_tx();
			bond_select_active_slave(bond);
			unblock_netpoll_tx();
		पूर्ण
		rtnl_unlock();
	पूर्ण

re_arm:
	अगर (bond->params.arp_पूर्णांकerval)
		queue_delayed_work(bond->wq, &bond->arp_work,
				   msecs_to_jअगरfies(bond->params.arp_पूर्णांकerval));
पूर्ण

/* Called to inspect slaves क्रम active-backup mode ARP monitor link state
 * changes.  Sets proposed link state in slaves to specअगरy what action
 * should take place क्रम the slave.  Returns 0 अगर no changes are found, >0
 * अगर changes to link states must be committed.
 *
 * Called with rcu_पढ़ो_lock held.
 */
अटल पूर्णांक bond_ab_arp_inspect(काष्ठा bonding *bond)
अणु
	अचिन्हित दीर्घ trans_start, last_rx;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	पूर्णांक commit = 0;

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		bond_propose_link_state(slave, BOND_LINK_NOCHANGE);
		last_rx = slave_last_rx(bond, slave);

		अगर (slave->link != BOND_LINK_UP) अणु
			अगर (bond_समय_in_पूर्णांकerval(bond, last_rx, 1)) अणु
				bond_propose_link_state(slave, BOND_LINK_UP);
				commit++;
			पूर्ण अन्यथा अगर (slave->link == BOND_LINK_BACK) अणु
				bond_propose_link_state(slave, BOND_LINK_FAIL);
				commit++;
			पूर्ण
			जारी;
		पूर्ण

		/* Give slaves 2*delta after being enslaved or made
		 * active.  This aव्योमs bouncing, as the last receive
		 * बार need a full ARP monitor cycle to be updated.
		 */
		अगर (bond_समय_in_पूर्णांकerval(bond, slave->last_link_up, 2))
			जारी;

		/* Backup slave is करोwn अगर:
		 * - No current_arp_slave AND
		 * - more than 3*delta since last receive AND
		 * - the bond has an IP address
		 *
		 * Note: a non-null current_arp_slave indicates
		 * the curr_active_slave went करोwn and we are
		 * searching क्रम a new one; under this condition
		 * we only take the curr_active_slave करोwn - this
		 * gives each slave a chance to tx/rx traffic
		 * beक्रमe being taken out
		 */
		अगर (!bond_is_active_slave(slave) &&
		    !rcu_access_poपूर्णांकer(bond->current_arp_slave) &&
		    !bond_समय_in_पूर्णांकerval(bond, last_rx, 3)) अणु
			bond_propose_link_state(slave, BOND_LINK_DOWN);
			commit++;
		पूर्ण

		/* Active slave is करोwn अगर:
		 * - more than 2*delta since transmitting OR
		 * - (more than 2*delta since receive AND
		 *    the bond has an IP address)
		 */
		trans_start = dev_trans_start(slave->dev);
		अगर (bond_is_active_slave(slave) &&
		    (!bond_समय_in_पूर्णांकerval(bond, trans_start, 2) ||
		     !bond_समय_in_पूर्णांकerval(bond, last_rx, 2))) अणु
			bond_propose_link_state(slave, BOND_LINK_DOWN);
			commit++;
		पूर्ण
	पूर्ण

	वापस commit;
पूर्ण

/* Called to commit link state changes noted by inspection step of
 * active-backup mode ARP monitor.
 *
 * Called with RTNL hold.
 */
अटल व्योम bond_ab_arp_commit(काष्ठा bonding *bond)
अणु
	अचिन्हित दीर्घ trans_start;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		चयन (slave->link_new_state) अणु
		हाल BOND_LINK_NOCHANGE:
			जारी;

		हाल BOND_LINK_UP:
			trans_start = dev_trans_start(slave->dev);
			अगर (rtnl_dereference(bond->curr_active_slave) != slave ||
			    (!rtnl_dereference(bond->curr_active_slave) &&
			     bond_समय_in_पूर्णांकerval(bond, trans_start, 1))) अणु
				काष्ठा slave *current_arp_slave;

				current_arp_slave = rtnl_dereference(bond->current_arp_slave);
				bond_set_slave_link_state(slave, BOND_LINK_UP,
							  BOND_SLAVE_NOTIFY_NOW);
				अगर (current_arp_slave) अणु
					bond_set_slave_inactive_flags(
						current_arp_slave,
						BOND_SLAVE_NOTIFY_NOW);
					RCU_INIT_POINTER(bond->current_arp_slave, शून्य);
				पूर्ण

				slave_info(bond->dev, slave->dev, "link status definitely up\n");

				अगर (!rtnl_dereference(bond->curr_active_slave) ||
				    slave == rtnl_dereference(bond->primary_slave))
					जाओ करो_failover;

			पूर्ण

			जारी;

		हाल BOND_LINK_DOWN:
			अगर (slave->link_failure_count < अच_पूर्णांक_उच्च)
				slave->link_failure_count++;

			bond_set_slave_link_state(slave, BOND_LINK_DOWN,
						  BOND_SLAVE_NOTIFY_NOW);
			bond_set_slave_inactive_flags(slave,
						      BOND_SLAVE_NOTIFY_NOW);

			slave_info(bond->dev, slave->dev, "link status definitely down, disabling slave\n");

			अगर (slave == rtnl_dereference(bond->curr_active_slave)) अणु
				RCU_INIT_POINTER(bond->current_arp_slave, शून्य);
				जाओ करो_failover;
			पूर्ण

			जारी;

		हाल BOND_LINK_FAIL:
			bond_set_slave_link_state(slave, BOND_LINK_FAIL,
						  BOND_SLAVE_NOTIFY_NOW);
			bond_set_slave_inactive_flags(slave,
						      BOND_SLAVE_NOTIFY_NOW);

			/* A slave has just been enslaved and has become
			 * the current active slave.
			 */
			अगर (rtnl_dereference(bond->curr_active_slave))
				RCU_INIT_POINTER(bond->current_arp_slave, शून्य);
			जारी;

		शेष:
			slave_err(bond->dev, slave->dev,
				  "impossible: link_new_state %d on slave\n",
				  slave->link_new_state);
			जारी;
		पूर्ण

करो_failover:
		block_netpoll_tx();
		bond_select_active_slave(bond);
		unblock_netpoll_tx();
	पूर्ण

	bond_set_carrier(bond);
पूर्ण

/* Send ARP probes क्रम active-backup mode ARP monitor.
 *
 * Called with rcu_पढ़ो_lock held.
 */
अटल bool bond_ab_arp_probe(काष्ठा bonding *bond)
अणु
	काष्ठा slave *slave, *beक्रमe = शून्य, *new_slave = शून्य,
		     *curr_arp_slave = rcu_dereference(bond->current_arp_slave),
		     *curr_active_slave = rcu_dereference(bond->curr_active_slave);
	काष्ठा list_head *iter;
	bool found = false;
	bool should_notअगरy_rtnl = BOND_SLAVE_NOTIFY_LATER;

	अगर (curr_arp_slave && curr_active_slave)
		netdev_info(bond->dev, "PROBE: c_arp %s && cas %s BAD\n",
			    curr_arp_slave->dev->name,
			    curr_active_slave->dev->name);

	अगर (curr_active_slave) अणु
		bond_arp_send_all(bond, curr_active_slave);
		वापस should_notअगरy_rtnl;
	पूर्ण

	/* अगर we करोn't have a curr_active_slave, search क्रम the next available
	 * backup slave from the current_arp_slave and make it the candidate
	 * क्रम becoming the curr_active_slave
	 */

	अगर (!curr_arp_slave) अणु
		curr_arp_slave = bond_first_slave_rcu(bond);
		अगर (!curr_arp_slave)
			वापस should_notअगरy_rtnl;
	पूर्ण

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (!found && !beक्रमe && bond_slave_is_up(slave))
			beक्रमe = slave;

		अगर (found && !new_slave && bond_slave_is_up(slave))
			new_slave = slave;
		/* अगर the link state is up at this poपूर्णांक, we
		 * mark it करोwn - this can happen अगर we have
		 * simultaneous link failures and
		 * reselect_active_पूर्णांकerface करोesn't make this
		 * one the current slave so it is still marked
		 * up when it is actually करोwn
		 */
		अगर (!bond_slave_is_up(slave) && slave->link == BOND_LINK_UP) अणु
			bond_set_slave_link_state(slave, BOND_LINK_DOWN,
						  BOND_SLAVE_NOTIFY_LATER);
			अगर (slave->link_failure_count < अच_पूर्णांक_उच्च)
				slave->link_failure_count++;

			bond_set_slave_inactive_flags(slave,
						      BOND_SLAVE_NOTIFY_LATER);

			slave_info(bond->dev, slave->dev, "backup interface is now down\n");
		पूर्ण
		अगर (slave == curr_arp_slave)
			found = true;
	पूर्ण

	अगर (!new_slave && beक्रमe)
		new_slave = beक्रमe;

	अगर (!new_slave)
		जाओ check_state;

	bond_set_slave_link_state(new_slave, BOND_LINK_BACK,
				  BOND_SLAVE_NOTIFY_LATER);
	bond_set_slave_active_flags(new_slave, BOND_SLAVE_NOTIFY_LATER);
	bond_arp_send_all(bond, new_slave);
	new_slave->last_link_up = jअगरfies;
	rcu_assign_poपूर्णांकer(bond->current_arp_slave, new_slave);

check_state:
	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (slave->should_notअगरy || slave->should_notअगरy_link) अणु
			should_notअगरy_rtnl = BOND_SLAVE_NOTIFY_NOW;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस should_notअगरy_rtnl;
पूर्ण

अटल व्योम bond_activebackup_arp_mon(काष्ठा bonding *bond)
अणु
	bool should_notअगरy_peers = false;
	bool should_notअगरy_rtnl = false;
	पूर्णांक delta_in_ticks;

	delta_in_ticks = msecs_to_jअगरfies(bond->params.arp_पूर्णांकerval);

	अगर (!bond_has_slaves(bond))
		जाओ re_arm;

	rcu_पढ़ो_lock();

	should_notअगरy_peers = bond_should_notअगरy_peers(bond);

	अगर (bond_ab_arp_inspect(bond)) अणु
		rcu_पढ़ो_unlock();

		/* Race aव्योमance with bond_बंद flush of workqueue */
		अगर (!rtnl_trylock()) अणु
			delta_in_ticks = 1;
			should_notअगरy_peers = false;
			जाओ re_arm;
		पूर्ण

		bond_ab_arp_commit(bond);

		rtnl_unlock();
		rcu_पढ़ो_lock();
	पूर्ण

	should_notअगरy_rtnl = bond_ab_arp_probe(bond);
	rcu_पढ़ो_unlock();

re_arm:
	अगर (bond->params.arp_पूर्णांकerval)
		queue_delayed_work(bond->wq, &bond->arp_work, delta_in_ticks);

	अगर (should_notअगरy_peers || should_notअगरy_rtnl) अणु
		अगर (!rtnl_trylock())
			वापस;

		अगर (should_notअगरy_peers)
			call_netdevice_notअगरiers(NETDEV_NOTIFY_PEERS,
						 bond->dev);
		अगर (should_notअगरy_rtnl) अणु
			bond_slave_state_notअगरy(bond);
			bond_slave_link_notअगरy(bond);
		पूर्ण

		rtnl_unlock();
	पूर्ण
पूर्ण

अटल व्योम bond_arp_monitor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bonding *bond = container_of(work, काष्ठा bonding,
					    arp_work.work);

	अगर (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP)
		bond_activebackup_arp_mon(bond);
	अन्यथा
		bond_loadbalance_arp_mon(bond);
पूर्ण

/*-------------------------- netdev event handling --------------------------*/

/* Change device name */
अटल पूर्णांक bond_event_changename(काष्ठा bonding *bond)
अणु
	bond_हटाओ_proc_entry(bond);
	bond_create_proc_entry(bond);

	bond_debug_reरेजिस्टर(bond);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक bond_master_netdev_event(अचिन्हित दीर्घ event,
				    काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *event_bond = netdev_priv(bond_dev);

	netdev_dbg(bond_dev, "%s called\n", __func__);

	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		वापस bond_event_changename(event_bond);
	हाल NETDEV_UNREGISTER:
		bond_हटाओ_proc_entry(event_bond);
		अवरोध;
	हाल NETDEV_REGISTER:
		bond_create_proc_entry(event_bond);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक bond_slave_netdev_event(अचिन्हित दीर्घ event,
				   काष्ठा net_device *slave_dev)
अणु
	काष्ठा slave *slave = bond_slave_get_rtnl(slave_dev), *primary;
	काष्ठा bonding *bond;
	काष्ठा net_device *bond_dev;

	/* A netdev event can be generated जबतक enslaving a device
	 * beक्रमe netdev_rx_handler_रेजिस्टर is called in which हाल
	 * slave will be शून्य
	 */
	अगर (!slave) अणु
		netdev_dbg(slave_dev, "%s called on NULL slave\n", __func__);
		वापस NOTIFY_DONE;
	पूर्ण

	bond_dev = slave->bond->dev;
	bond = slave->bond;
	primary = rtnl_dereference(bond->primary_slave);

	slave_dbg(bond_dev, slave_dev, "%s called\n", __func__);

	चयन (event) अणु
	हाल NETDEV_UNREGISTER:
		अगर (bond_dev->type != ARPHRD_ETHER)
			bond_release_and_destroy(bond_dev, slave_dev);
		अन्यथा
			__bond_release_one(bond_dev, slave_dev, false, true);
		अवरोध;
	हाल NETDEV_UP:
	हाल NETDEV_CHANGE:
		/* For 802.3ad mode only:
		 * Getting invalid Speed/Duplex values here will put slave
		 * in weird state. Mark it as link-fail अगर the link was
		 * previously up or link-करोwn अगर it hasn't yet come up, and
		 * let link-monitoring (miimon) set it right when correct
		 * speeds/duplex are available.
		 */
		अगर (bond_update_speed_duplex(slave) &&
		    BOND_MODE(bond) == BOND_MODE_8023AD) अणु
			अगर (slave->last_link_up)
				slave->link = BOND_LINK_FAIL;
			अन्यथा
				slave->link = BOND_LINK_DOWN;
		पूर्ण

		अगर (BOND_MODE(bond) == BOND_MODE_8023AD)
			bond_3ad_adapter_speed_duplex_changed(slave);
		fallthrough;
	हाल NETDEV_DOWN:
		/* Refresh slave-array अगर applicable!
		 * If the setup करोes not use miimon or arpmon (mode-specअगरic!),
		 * then these events will not cause the slave-array to be
		 * refreshed. This will cause xmit to use a slave that is not
		 * usable. Aव्योम such situation by refeshing the array at these
		 * events. If these (miimon/arpmon) parameters are configured
		 * then array माला_लो refreshed twice and that should be fine!
		 */
		अगर (bond_mode_can_use_xmit_hash(bond))
			bond_update_slave_arr(bond, शून्य);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		/* TODO: Should slaves be allowed to
		 * independently alter their MTU?  For
		 * an active-backup bond, slaves need
		 * not be the same type of device, so
		 * MTUs may vary.  For other modes,
		 * slaves arguably should have the
		 * same MTUs. To करो this, we'd need to
		 * take over the slave's change_mtu
		 * function क्रम the duration of their
		 * servitude.
		 */
		अवरोध;
	हाल NETDEV_CHANGENAME:
		/* we करोn't care if we don't have primary set */
		अगर (!bond_uses_primary(bond) ||
		    !bond->params.primary[0])
			अवरोध;

		अगर (slave == primary) अणु
			/* slave's name changed - he's no दीर्घer primary */
			RCU_INIT_POINTER(bond->primary_slave, शून्य);
		पूर्ण अन्यथा अगर (!म_भेद(slave_dev->name, bond->params.primary)) अणु
			/* we have a new primary slave */
			rcu_assign_poपूर्णांकer(bond->primary_slave, slave);
		पूर्ण अन्यथा अणु /* we didn't change primary - निकास */
			अवरोध;
		पूर्ण

		netdev_info(bond->dev, "Primary slave changed to %s, reselecting active slave\n",
			    primary ? slave_dev->name : "none");

		block_netpoll_tx();
		bond_select_active_slave(bond);
		unblock_netpoll_tx();
		अवरोध;
	हाल NETDEV_FEAT_CHANGE:
		bond_compute_features(bond);
		अवरोध;
	हाल NETDEV_RESEND_IGMP:
		/* Propagate to master device */
		call_netdevice_notअगरiers(event, slave->bond->dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/* bond_netdev_event: handle netdev notअगरier chain events.
 *
 * This function receives events क्रम the netdev chain.  The caller (an
 * ioctl handler calling blocking_notअगरier_call_chain) holds the necessary
 * locks क्रम us to safely manipulate the slave devices (RTNL lock,
 * dev_probe_lock).
 */
अटल पूर्णांक bond_netdev_event(काष्ठा notअगरier_block *this,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *event_dev = netdev_notअगरier_info_to_dev(ptr);

	netdev_dbg(event_dev, "%s received %s\n",
		   __func__, netdev_cmd_to_name(event));

	अगर (!(event_dev->priv_flags & IFF_BONDING))
		वापस NOTIFY_DONE;

	अगर (event_dev->flags & IFF_MASTER) अणु
		पूर्णांक ret;

		ret = bond_master_netdev_event(event, event_dev);
		अगर (ret != NOTIFY_DONE)
			वापस ret;
	पूर्ण

	अगर (event_dev->flags & IFF_SLAVE)
		वापस bond_slave_netdev_event(event, event_dev);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block bond_netdev_notअगरier = अणु
	.notअगरier_call = bond_netdev_event,
पूर्ण;

/*---------------------------- Hashing Policies -----------------------------*/

/* L2 hash helper */
अटल अंतरभूत u32 bond_eth_hash(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *ep, hdr_पंचांगp;

	ep = skb_header_poपूर्णांकer(skb, 0, माप(hdr_पंचांगp), &hdr_पंचांगp);
	अगर (ep)
		वापस ep->h_dest[5] ^ ep->h_source[5] ^ ep->h_proto;
	वापस 0;
पूर्ण

अटल bool bond_flow_ip(काष्ठा sk_buff *skb, काष्ठा flow_keys *fk,
			 पूर्णांक *noff, पूर्णांक *proto, bool l34)
अणु
	स्थिर काष्ठा ipv6hdr *iph6;
	स्थिर काष्ठा iphdr *iph;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		अगर (unlikely(!pskb_may_pull(skb, *noff + माप(*iph))))
			वापस false;
		iph = (स्थिर काष्ठा iphdr *)(skb->data + *noff);
		iph_to_flow_copy_v4addrs(fk, iph);
		*noff += iph->ihl << 2;
		अगर (!ip_is_fragment(iph))
			*proto = iph->protocol;
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		अगर (unlikely(!pskb_may_pull(skb, *noff + माप(*iph6))))
			वापस false;
		iph6 = (स्थिर काष्ठा ipv6hdr *)(skb->data + *noff);
		iph_to_flow_copy_v6addrs(fk, iph6);
		*noff += माप(*iph6);
		*proto = iph6->nexthdr;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	अगर (l34 && *proto >= 0)
		fk->ports.ports = skb_flow_get_ports(skb, *noff, *proto);

	वापस true;
पूर्ण

अटल u32 bond_vlan_srcmac_hash(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *mac_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	u32 srcmac_venकरोr = 0, srcmac_dev = 0;
	u16 vlan;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++)
		srcmac_venकरोr = (srcmac_venकरोr << 8) | mac_hdr->h_source[i];

	क्रम (i = 3; i < ETH_ALEN; i++)
		srcmac_dev = (srcmac_dev << 8) | mac_hdr->h_source[i];

	अगर (!skb_vlan_tag_present(skb))
		वापस srcmac_venकरोr ^ srcmac_dev;

	vlan = skb_vlan_tag_get(skb);

	वापस vlan ^ srcmac_venकरोr ^ srcmac_dev;
पूर्ण

/* Extract the appropriate headers based on bond's xmit policy */
अटल bool bond_flow_dissect(काष्ठा bonding *bond, काष्ठा sk_buff *skb,
			      काष्ठा flow_keys *fk)
अणु
	bool l34 = bond->params.xmit_policy == BOND_XMIT_POLICY_LAYER34;
	पूर्णांक noff, proto = -1;

	चयन (bond->params.xmit_policy) अणु
	हाल BOND_XMIT_POLICY_ENCAP23:
	हाल BOND_XMIT_POLICY_ENCAP34:
		स_रखो(fk, 0, माप(*fk));
		वापस __skb_flow_dissect(शून्य, skb, &flow_keys_bonding,
					  fk, शून्य, 0, 0, 0, 0);
	शेष:
		अवरोध;
	पूर्ण

	fk->ports.ports = 0;
	स_रखो(&fk->icmp, 0, माप(fk->icmp));
	noff = skb_network_offset(skb);
	अगर (!bond_flow_ip(skb, fk, &noff, &proto, l34))
		वापस false;

	/* ICMP error packets contains at least 8 bytes of the header
	 * of the packet which generated the error. Use this inक्रमmation
	 * to correlate ICMP error packets within the same flow which
	 * generated the error.
	 */
	अगर (proto == IPPROTO_ICMP || proto == IPPROTO_ICMPV6) अणु
		skb_flow_get_icmp_tci(skb, &fk->icmp, skb->data,
				      skb_transport_offset(skb),
				      skb_headlen(skb));
		अगर (proto == IPPROTO_ICMP) अणु
			अगर (!icmp_is_err(fk->icmp.type))
				वापस true;

			noff += माप(काष्ठा icmphdr);
		पूर्ण अन्यथा अगर (proto == IPPROTO_ICMPV6) अणु
			अगर (!icmpv6_is_err(fk->icmp.type))
				वापस true;

			noff += माप(काष्ठा icmp6hdr);
		पूर्ण
		वापस bond_flow_ip(skb, fk, &noff, &proto, l34);
	पूर्ण

	वापस true;
पूर्ण

अटल u32 bond_ip_hash(u32 hash, काष्ठा flow_keys *flow)
अणु
	hash ^= (__क्रमce u32)flow_get_u32_dst(flow) ^
		(__क्रमce u32)flow_get_u32_src(flow);
	hash ^= (hash >> 16);
	hash ^= (hash >> 8);
	/* discard lowest hash bit to deal with the common even ports pattern */
	वापस hash >> 1;
पूर्ण

/**
 * bond_xmit_hash - generate a hash value based on the xmit policy
 * @bond: bonding device
 * @skb: buffer to use क्रम headers
 *
 * This function will extract the necessary headers from the skb buffer and use
 * them to generate a hash based on the xmit_policy set in the bonding device
 */
u32 bond_xmit_hash(काष्ठा bonding *bond, काष्ठा sk_buff *skb)
अणु
	काष्ठा flow_keys flow;
	u32 hash;

	अगर (bond->params.xmit_policy == BOND_XMIT_POLICY_ENCAP34 &&
	    skb->l4_hash)
		वापस skb->hash;

	अगर (bond->params.xmit_policy == BOND_XMIT_POLICY_VLAN_SRCMAC)
		वापस bond_vlan_srcmac_hash(skb);

	अगर (bond->params.xmit_policy == BOND_XMIT_POLICY_LAYER2 ||
	    !bond_flow_dissect(bond, skb, &flow))
		वापस bond_eth_hash(skb);

	अगर (bond->params.xmit_policy == BOND_XMIT_POLICY_LAYER23 ||
	    bond->params.xmit_policy == BOND_XMIT_POLICY_ENCAP23) अणु
		hash = bond_eth_hash(skb);
	पूर्ण अन्यथा अणु
		अगर (flow.icmp.id)
			स_नकल(&hash, &flow.icmp, माप(hash));
		अन्यथा
			स_नकल(&hash, &flow.ports.ports, माप(hash));
	पूर्ण

	वापस bond_ip_hash(hash, &flow);
पूर्ण

/*-------------------------- Device entry poपूर्णांकs ----------------------------*/

व्योम bond_work_init_all(काष्ठा bonding *bond)
अणु
	INIT_DELAYED_WORK(&bond->mcast_work,
			  bond_resend_igmp_join_requests_delayed);
	INIT_DELAYED_WORK(&bond->alb_work, bond_alb_monitor);
	INIT_DELAYED_WORK(&bond->mii_work, bond_mii_monitor);
	INIT_DELAYED_WORK(&bond->arp_work, bond_arp_monitor);
	INIT_DELAYED_WORK(&bond->ad_work, bond_3ad_state_machine_handler);
	INIT_DELAYED_WORK(&bond->slave_arr_work, bond_slave_arr_handler);
पूर्ण

अटल व्योम bond_work_cancel_all(काष्ठा bonding *bond)
अणु
	cancel_delayed_work_sync(&bond->mii_work);
	cancel_delayed_work_sync(&bond->arp_work);
	cancel_delayed_work_sync(&bond->alb_work);
	cancel_delayed_work_sync(&bond->ad_work);
	cancel_delayed_work_sync(&bond->mcast_work);
	cancel_delayed_work_sync(&bond->slave_arr_work);
पूर्ण

अटल पूर्णांक bond_खोलो(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	/* reset slave->backup and slave->inactive */
	अगर (bond_has_slaves(bond)) अणु
		bond_क्रम_each_slave(bond, slave, iter) अणु
			अगर (bond_uses_primary(bond) &&
			    slave != rcu_access_poपूर्णांकer(bond->curr_active_slave)) अणु
				bond_set_slave_inactive_flags(slave,
							      BOND_SLAVE_NOTIFY_NOW);
			पूर्ण अन्यथा अगर (BOND_MODE(bond) != BOND_MODE_8023AD) अणु
				bond_set_slave_active_flags(slave,
							    BOND_SLAVE_NOTIFY_NOW);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (bond_is_lb(bond)) अणु
		/* bond_alb_initialize must be called beक्रमe the समयr
		 * is started.
		 */
		अगर (bond_alb_initialize(bond, (BOND_MODE(bond) == BOND_MODE_ALB)))
			वापस -ENOMEM;
		अगर (bond->params.tlb_dynamic_lb || BOND_MODE(bond) == BOND_MODE_ALB)
			queue_delayed_work(bond->wq, &bond->alb_work, 0);
	पूर्ण

	अगर (bond->params.miimon)  /* link check पूर्णांकerval, in milliseconds. */
		queue_delayed_work(bond->wq, &bond->mii_work, 0);

	अगर (bond->params.arp_पूर्णांकerval) अणु  /* arp पूर्णांकerval, in milliseconds. */
		queue_delayed_work(bond->wq, &bond->arp_work, 0);
		bond->recv_probe = bond_arp_rcv;
	पूर्ण

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		queue_delayed_work(bond->wq, &bond->ad_work, 0);
		/* रेजिस्टर to receive LACPDUs */
		bond->recv_probe = bond_3ad_lacpdu_recv;
		bond_3ad_initiate_agg_selection(bond, 1);
	पूर्ण

	अगर (bond_mode_can_use_xmit_hash(bond))
		bond_update_slave_arr(bond, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक bond_बंद(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);

	bond_work_cancel_all(bond);
	bond->send_peer_notअगर = 0;
	अगर (bond_is_lb(bond))
		bond_alb_deinitialize(bond);
	bond->recv_probe = शून्य;

	वापस 0;
पूर्ण

/* fold stats, assuming all rtnl_link_stats64 fields are u64, but
 * that some drivers can provide 32bit values only.
 */
अटल व्योम bond_fold_stats(काष्ठा rtnl_link_stats64 *_res,
			    स्थिर काष्ठा rtnl_link_stats64 *_new,
			    स्थिर काष्ठा rtnl_link_stats64 *_old)
अणु
	स्थिर u64 *new = (स्थिर u64 *)_new;
	स्थिर u64 *old = (स्थिर u64 *)_old;
	u64 *res = (u64 *)_res;
	पूर्णांक i;

	क्रम (i = 0; i < माप(*_res) / माप(u64); i++) अणु
		u64 nv = new[i];
		u64 ov = old[i];
		s64 delta = nv - ov;

		/* detects अगर this particular field is 32bit only */
		अगर (((nv | ov) >> 32) == 0)
			delta = (s64)(s32)((u32)nv - (u32)ov);

		/* filter anomalies, some drivers reset their stats
		 * at करोwn/up events.
		 */
		अगर (delta > 0)
			res[i] += delta;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
अटल पूर्णांक bond_get_lowest_level_rcu(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *ldev, *next, *now, *dev_stack[MAX_NEST_DEV + 1];
	काष्ठा list_head *niter, *iter, *iter_stack[MAX_NEST_DEV + 1];
	पूर्णांक cur = 0, max = 0;

	now = dev;
	iter = &dev->adj_list.lower;

	जबतक (1) अणु
		next = शून्य;
		जबतक (1) अणु
			ldev = netdev_next_lower_dev_rcu(now, &iter);
			अगर (!ldev)
				अवरोध;

			next = ldev;
			niter = &ldev->adj_list.lower;
			dev_stack[cur] = now;
			iter_stack[cur++] = iter;
			अगर (max <= cur)
				max = cur;
			अवरोध;
		पूर्ण

		अगर (!next) अणु
			अगर (!cur)
				वापस max;
			next = dev_stack[--cur];
			niter = iter_stack[cur];
		पूर्ण

		now = next;
		iter = niter;
	पूर्ण

	वापस max;
पूर्ण
#पूर्ण_अगर

अटल व्योम bond_get_stats(काष्ठा net_device *bond_dev,
			   काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा rtnl_link_stats64 temp;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	पूर्णांक nest_level = 0;


	rcu_पढ़ो_lock();
#अगर_घोषित CONFIG_LOCKDEP
	nest_level = bond_get_lowest_level_rcu(bond_dev);
#पूर्ण_अगर

	spin_lock_nested(&bond->stats_lock, nest_level);
	स_नकल(stats, &bond->bond_stats, माप(*stats));

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		स्थिर काष्ठा rtnl_link_stats64 *new =
			dev_get_stats(slave->dev, &temp);

		bond_fold_stats(stats, new, &slave->slave_stats);

		/* save off the slave stats क्रम the next run */
		स_नकल(&slave->slave_stats, new, माप(*new));
	पूर्ण

	स_नकल(&bond->bond_stats, stats, माप(*stats));
	spin_unlock(&bond->stats_lock);
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक bond_करो_ioctl(काष्ठा net_device *bond_dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा net_device *slave_dev = शून्य;
	काष्ठा अगरbond k_binfo;
	काष्ठा अगरbond __user *u_binfo = शून्य;
	काष्ठा अगरslave k_sinfo;
	काष्ठा अगरslave __user *u_sinfo = शून्य;
	काष्ठा mii_ioctl_data *mii = शून्य;
	काष्ठा bond_opt_value newval;
	काष्ठा net *net;
	पूर्णांक res = 0;

	netdev_dbg(bond_dev, "bond_ioctl: cmd=%d\n", cmd);

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		mii = अगर_mii(अगरr);
		अगर (!mii)
			वापस -EINVAL;

		mii->phy_id = 0;
		fallthrough;
	हाल SIOCGMIIREG:
		/* We करो this again just in हाल we were called by SIOCGMIIREG
		 * instead of SIOCGMIIPHY.
		 */
		mii = अगर_mii(अगरr);
		अगर (!mii)
			वापस -EINVAL;

		अगर (mii->reg_num == 1) अणु
			mii->val_out = 0;
			अगर (netअगर_carrier_ok(bond->dev))
				mii->val_out = BMSR_LSTATUS;
		पूर्ण

		वापस 0;
	हाल BOND_INFO_QUERY_OLD:
	हाल SIOCBONDINFOQUERY:
		u_binfo = (काष्ठा अगरbond __user *)अगरr->अगरr_data;

		अगर (copy_from_user(&k_binfo, u_binfo, माप(अगरbond)))
			वापस -EFAULT;

		bond_info_query(bond_dev, &k_binfo);
		अगर (copy_to_user(u_binfo, &k_binfo, माप(अगरbond)))
			वापस -EFAULT;

		वापस 0;
	हाल BOND_SLAVE_INFO_QUERY_OLD:
	हाल SIOCBONDSLAVEINFOQUERY:
		u_sinfo = (काष्ठा अगरslave __user *)अगरr->अगरr_data;

		अगर (copy_from_user(&k_sinfo, u_sinfo, माप(अगरslave)))
			वापस -EFAULT;

		res = bond_slave_info_query(bond_dev, &k_sinfo);
		अगर (res == 0 &&
		    copy_to_user(u_sinfo, &k_sinfo, माप(अगरslave)))
			वापस -EFAULT;

		वापस res;
	शेष:
		अवरोध;
	पूर्ण

	net = dev_net(bond_dev);

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	slave_dev = __dev_get_by_name(net, अगरr->अगरr_slave);

	slave_dbg(bond_dev, slave_dev, "slave_dev=%p:\n", slave_dev);

	अगर (!slave_dev)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल BOND_ENSLAVE_OLD:
	हाल SIOCBONDENSLAVE:
		res = bond_enslave(bond_dev, slave_dev, शून्य);
		अवरोध;
	हाल BOND_RELEASE_OLD:
	हाल SIOCBONDRELEASE:
		res = bond_release(bond_dev, slave_dev);
		अवरोध;
	हाल BOND_SETHWADDR_OLD:
	हाल SIOCBONDSETHWADDR:
		res = bond_set_dev_addr(bond_dev, slave_dev);
		अवरोध;
	हाल BOND_CHANGE_ACTIVE_OLD:
	हाल SIOCBONDCHANGEACTIVE:
		bond_opt_initstr(&newval, slave_dev->name);
		res = __bond_opt_set_notअगरy(bond, BOND_OPT_ACTIVE_SLAVE,
					    &newval);
		अवरोध;
	शेष:
		res = -EOPNOTSUPP;
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम bond_change_rx_flags(काष्ठा net_device *bond_dev, पूर्णांक change)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);

	अगर (change & IFF_PROMISC)
		bond_set_promiscuity(bond,
				     bond_dev->flags & IFF_PROMISC ? 1 : -1);

	अगर (change & IFF_ALLMULTI)
		bond_set_allmulti(bond,
				  bond_dev->flags & IFF_ALLMULTI ? 1 : -1);
पूर्ण

अटल व्योम bond_set_rx_mode(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	rcu_पढ़ो_lock();
	अगर (bond_uses_primary(bond)) अणु
		slave = rcu_dereference(bond->curr_active_slave);
		अगर (slave) अणु
			dev_uc_sync(slave->dev, bond_dev);
			dev_mc_sync(slave->dev, bond_dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
			dev_uc_sync_multiple(slave->dev, bond_dev);
			dev_mc_sync_multiple(slave->dev, bond_dev);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक bond_neigh_init(काष्ठा neighbour *n)
अणु
	काष्ठा bonding *bond = netdev_priv(n->dev);
	स्थिर काष्ठा net_device_ops *slave_ops;
	काष्ठा neigh_parms parms;
	काष्ठा slave *slave;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	slave = bond_first_slave_rcu(bond);
	अगर (!slave)
		जाओ out;
	slave_ops = slave->dev->netdev_ops;
	अगर (!slave_ops->nकरो_neigh_setup)
		जाओ out;

	/* TODO: find another way [1] to implement this.
	 * Passing a zeroed काष्ठाure is fragile,
	 * but at least we करो not pass garbage.
	 *
	 * [1] One way would be that nकरो_neigh_setup() never touch
	 *     काष्ठा neigh_parms, but propagate the new neigh_setup()
	 *     back to ___neigh_create() / neigh_parms_alloc()
	 */
	स_रखो(&parms, 0, माप(parms));
	ret = slave_ops->nकरो_neigh_setup(slave->dev, &parms);

	अगर (ret)
		जाओ out;

	अगर (parms.neigh_setup)
		ret = parms.neigh_setup(n);
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/* The bonding nकरो_neigh_setup is called at init समय beofre any
 * slave exists. So we must declare proxy setup function which will
 * be used at run समय to resolve the actual slave neigh param setup.
 *
 * It's also called by master devices (such as vlans) to setup their
 * underlying devices. In that हाल - करो nothing, we're alपढ़ोy set up from
 * our init.
 */
अटल पूर्णांक bond_neigh_setup(काष्ठा net_device *dev,
			    काष्ठा neigh_parms *parms)
अणु
	/* modअगरy only our neigh_parms */
	अगर (parms->dev == dev)
		parms->neigh_setup = bond_neigh_init;

	वापस 0;
पूर्ण

/* Change the MTU of all of a master's slaves to match the master */
अटल पूर्णांक bond_change_mtu(काष्ठा net_device *bond_dev, पूर्णांक new_mtu)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *slave, *rollback_slave;
	काष्ठा list_head *iter;
	पूर्णांक res = 0;

	netdev_dbg(bond_dev, "bond=%p, new_mtu=%d\n", bond, new_mtu);

	bond_क्रम_each_slave(bond, slave, iter) अणु
		slave_dbg(bond_dev, slave->dev, "s %p c_m %p\n",
			   slave, slave->dev->netdev_ops->nकरो_change_mtu);

		res = dev_set_mtu(slave->dev, new_mtu);

		अगर (res) अणु
			/* If we failed to set the slave's mtu to the new value
			 * we must पात the operation even in ACTIVE_BACKUP
			 * mode, because अगर we allow the backup slaves to have
			 * dअगरferent mtu values than the active slave we'll
			 * need to change their mtu when करोing a failover. That
			 * means changing their mtu from समयr context, which
			 * is probably not a good idea.
			 */
			slave_dbg(bond_dev, slave->dev, "err %d setting mtu to %d\n",
				  res, new_mtu);
			जाओ unwind;
		पूर्ण
	पूर्ण

	bond_dev->mtu = new_mtu;

	वापस 0;

unwind:
	/* unwind from head to the slave that failed */
	bond_क्रम_each_slave(bond, rollback_slave, iter) अणु
		पूर्णांक पंचांगp_res;

		अगर (rollback_slave == slave)
			अवरोध;

		पंचांगp_res = dev_set_mtu(rollback_slave->dev, bond_dev->mtu);
		अगर (पंचांगp_res)
			slave_dbg(bond_dev, rollback_slave->dev, "unwind err %d\n",
				  पंचांगp_res);
	पूर्ण

	वापस res;
पूर्ण

/* Change HW address
 *
 * Note that many devices must be करोwn to change the HW address, and
 * करोwning the master releases all slaves.  We can make bonds full of
 * bonding devices to test this, however.
 */
अटल पूर्णांक bond_set_mac_address(काष्ठा net_device *bond_dev, व्योम *addr)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *slave, *rollback_slave;
	काष्ठा sockaddr_storage *ss = addr, पंचांगp_ss;
	काष्ठा list_head *iter;
	पूर्णांक res = 0;

	अगर (BOND_MODE(bond) == BOND_MODE_ALB)
		वापस bond_alb_set_mac_address(bond_dev, addr);


	netdev_dbg(bond_dev, "%s: bond=%p\n", __func__, bond);

	/* If fail_over_mac is enabled, करो nothing and वापस success.
	 * Returning an error causes अगरenslave to fail.
	 */
	अगर (bond->params.fail_over_mac &&
	    BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP)
		वापस 0;

	अगर (!is_valid_ether_addr(ss->__data))
		वापस -EADDRNOTAVAIL;

	bond_क्रम_each_slave(bond, slave, iter) अणु
		slave_dbg(bond_dev, slave->dev, "%s: slave=%p\n",
			  __func__, slave);
		res = dev_set_mac_address(slave->dev, addr, शून्य);
		अगर (res) अणु
			/* TODO: consider करोwning the slave
			 * and retry ?
			 * User should expect communications
			 * अवरोधage anyway until ARP finish
			 * updating, so...
			 */
			slave_dbg(bond_dev, slave->dev, "%s: err %d\n",
				  __func__, res);
			जाओ unwind;
		पूर्ण
	पूर्ण

	/* success */
	स_नकल(bond_dev->dev_addr, ss->__data, bond_dev->addr_len);
	वापस 0;

unwind:
	स_नकल(पंचांगp_ss.__data, bond_dev->dev_addr, bond_dev->addr_len);
	पंचांगp_ss.ss_family = bond_dev->type;

	/* unwind from head to the slave that failed */
	bond_क्रम_each_slave(bond, rollback_slave, iter) अणु
		पूर्णांक पंचांगp_res;

		अगर (rollback_slave == slave)
			अवरोध;

		पंचांगp_res = dev_set_mac_address(rollback_slave->dev,
					      (काष्ठा sockaddr *)&पंचांगp_ss, शून्य);
		अगर (पंचांगp_res) अणु
			slave_dbg(bond_dev, rollback_slave->dev, "%s: unwind err %d\n",
				   __func__, पंचांगp_res);
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

/**
 * bond_get_slave_by_id - get xmit slave with slave_id
 * @bond: bonding device that is transmitting
 * @slave_id: slave id up to slave_cnt-1 through which to transmit
 *
 * This function tries to get slave with slave_id but in हाल
 * it fails, it tries to find the first available slave क्रम transmission.
 */
अटल काष्ठा slave *bond_get_slave_by_id(काष्ठा bonding *bond,
					  पूर्णांक slave_id)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	पूर्णांक i = slave_id;

	/* Here we start from the slave with slave_id */
	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (--i < 0) अणु
			अगर (bond_slave_can_tx(slave))
				वापस slave;
		पूर्ण
	पूर्ण

	/* Here we start from the first slave up to slave_id */
	i = slave_id;
	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (--i < 0)
			अवरोध;
		अगर (bond_slave_can_tx(slave))
			वापस slave;
	पूर्ण
	/* no slave that can tx has been found */
	वापस शून्य;
पूर्ण

/**
 * bond_rr_gen_slave_id - generate slave id based on packets_per_slave
 * @bond: bonding device to use
 *
 * Based on the value of the bonding device's packets_per_slave parameter
 * this function generates a slave id, which is usually used as the next
 * slave to transmit through.
 */
अटल u32 bond_rr_gen_slave_id(काष्ठा bonding *bond)
अणु
	u32 slave_id;
	काष्ठा reciprocal_value reciprocal_packets_per_slave;
	पूर्णांक packets_per_slave = bond->params.packets_per_slave;

	चयन (packets_per_slave) अणु
	हाल 0:
		slave_id = pअक्रमom_u32();
		अवरोध;
	हाल 1:
		slave_id = bond->rr_tx_counter;
		अवरोध;
	शेष:
		reciprocal_packets_per_slave =
			bond->params.reciprocal_packets_per_slave;
		slave_id = reciprocal_भागide(bond->rr_tx_counter,
					     reciprocal_packets_per_slave);
		अवरोध;
	पूर्ण
	bond->rr_tx_counter++;

	वापस slave_id;
पूर्ण

अटल काष्ठा slave *bond_xmit_roundrobin_slave_get(काष्ठा bonding *bond,
						    काष्ठा sk_buff *skb)
अणु
	काष्ठा slave *slave;
	पूर्णांक slave_cnt;
	u32 slave_id;

	/* Start with the curr_active_slave that joined the bond as the
	 * शेष क्रम sending IGMP traffic.  For failover purposes one
	 * needs to मुख्यtain some consistency क्रम the पूर्णांकerface that will
	 * send the join/membership reports.  The curr_active_slave found
	 * will send all of this type of traffic.
	 */
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		पूर्णांक noff = skb_network_offset(skb);
		काष्ठा iphdr *iph;

		अगर (unlikely(!pskb_may_pull(skb, noff + माप(*iph))))
			जाओ non_igmp;

		iph = ip_hdr(skb);
		अगर (iph->protocol == IPPROTO_IGMP) अणु
			slave = rcu_dereference(bond->curr_active_slave);
			अगर (slave)
				वापस slave;
			वापस bond_get_slave_by_id(bond, 0);
		पूर्ण
	पूर्ण

non_igmp:
	slave_cnt = READ_ONCE(bond->slave_cnt);
	अगर (likely(slave_cnt)) अणु
		slave_id = bond_rr_gen_slave_id(bond) % slave_cnt;
		वापस bond_get_slave_by_id(bond, slave_id);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल netdev_tx_t bond_xmit_roundrobin(काष्ठा sk_buff *skb,
					काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *slave;

	slave = bond_xmit_roundrobin_slave_get(bond, skb);
	अगर (likely(slave))
		वापस bond_dev_queue_xmit(bond, skb, slave->dev);

	वापस bond_tx_drop(bond_dev, skb);
पूर्ण

अटल काष्ठा slave *bond_xmit_activebackup_slave_get(काष्ठा bonding *bond,
						      काष्ठा sk_buff *skb)
अणु
	वापस rcu_dereference(bond->curr_active_slave);
पूर्ण

/* In active-backup mode, we know that bond->curr_active_slave is always valid अगर
 * the bond has a usable पूर्णांकerface.
 */
अटल netdev_tx_t bond_xmit_activebackup(काष्ठा sk_buff *skb,
					  काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *slave;

	slave = bond_xmit_activebackup_slave_get(bond, skb);
	अगर (slave)
		वापस bond_dev_queue_xmit(bond, skb, slave->dev);

	वापस bond_tx_drop(bond_dev, skb);
पूर्ण

/* Use this to update slave_array when (a) it's not appropriate to update
 * slave_array right away (note that update_slave_array() may sleep)
 * and / or (b) RTNL is not held.
 */
व्योम bond_slave_arr_work_rearm(काष्ठा bonding *bond, अचिन्हित दीर्घ delay)
अणु
	queue_delayed_work(bond->wq, &bond->slave_arr_work, delay);
पूर्ण

/* Slave array work handler. Holds only RTNL */
अटल व्योम bond_slave_arr_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bonding *bond = container_of(work, काष्ठा bonding,
					    slave_arr_work.work);
	पूर्णांक ret;

	अगर (!rtnl_trylock())
		जाओ err;

	ret = bond_update_slave_arr(bond, शून्य);
	rtnl_unlock();
	अगर (ret) अणु
		pr_warn_ratelimited("Failed to update slave array from WT\n");
		जाओ err;
	पूर्ण
	वापस;

err:
	bond_slave_arr_work_rearm(bond, 1);
पूर्ण

अटल व्योम bond_skip_slave(काष्ठा bond_up_slave *slaves,
			    काष्ठा slave *skipslave)
अणु
	पूर्णांक idx;

	/* Rare situation where caller has asked to skip a specअगरic
	 * slave but allocation failed (most likely!). BTW this is
	 * only possible when the call is initiated from
	 * __bond_release_one(). In this situation; overग_लिखो the
	 * skipslave entry in the array with the last entry from the
	 * array to aव्योम a situation where the xmit path may choose
	 * this to-be-skipped slave to send a packet out.
	 */
	क्रम (idx = 0; slaves && idx < slaves->count; idx++) अणु
		अगर (skipslave == slaves->arr[idx]) अणु
			slaves->arr[idx] =
				slaves->arr[slaves->count - 1];
			slaves->count--;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bond_set_slave_arr(काष्ठा bonding *bond,
			       काष्ठा bond_up_slave *usable_slaves,
			       काष्ठा bond_up_slave *all_slaves)
अणु
	काष्ठा bond_up_slave *usable, *all;

	usable = rtnl_dereference(bond->usable_slaves);
	rcu_assign_poपूर्णांकer(bond->usable_slaves, usable_slaves);
	kमुक्त_rcu(usable, rcu);

	all = rtnl_dereference(bond->all_slaves);
	rcu_assign_poपूर्णांकer(bond->all_slaves, all_slaves);
	kमुक्त_rcu(all, rcu);
पूर्ण

अटल व्योम bond_reset_slave_arr(काष्ठा bonding *bond)
अणु
	काष्ठा bond_up_slave *usable, *all;

	usable = rtnl_dereference(bond->usable_slaves);
	अगर (usable) अणु
		RCU_INIT_POINTER(bond->usable_slaves, शून्य);
		kमुक्त_rcu(usable, rcu);
	पूर्ण

	all = rtnl_dereference(bond->all_slaves);
	अगर (all) अणु
		RCU_INIT_POINTER(bond->all_slaves, शून्य);
		kमुक्त_rcu(all, rcu);
	पूर्ण
पूर्ण

/* Build the usable slaves array in control path क्रम modes that use xmit-hash
 * to determine the slave पूर्णांकerface -
 * (a) BOND_MODE_8023AD
 * (b) BOND_MODE_XOR
 * (c) (BOND_MODE_TLB || BOND_MODE_ALB) && tlb_dynamic_lb == 0
 *
 * The caller is expected to hold RTNL only and NO other lock!
 */
पूर्णांक bond_update_slave_arr(काष्ठा bonding *bond, काष्ठा slave *skipslave)
अणु
	काष्ठा bond_up_slave *usable_slaves = शून्य, *all_slaves = शून्य;
	काष्ठा slave *slave;
	काष्ठा list_head *iter;
	पूर्णांक agg_id = 0;
	पूर्णांक ret = 0;

	might_sleep();

	usable_slaves = kzalloc(काष्ठा_size(usable_slaves, arr,
					    bond->slave_cnt), GFP_KERNEL);
	all_slaves = kzalloc(काष्ठा_size(all_slaves, arr,
					 bond->slave_cnt), GFP_KERNEL);
	अगर (!usable_slaves || !all_slaves) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		काष्ठा ad_info ad_info;

		spin_lock_bh(&bond->mode_lock);
		अगर (bond_3ad_get_active_agg_info(bond, &ad_info)) अणु
			spin_unlock_bh(&bond->mode_lock);
			pr_debug("bond_3ad_get_active_agg_info failed\n");
			/* No active aggragator means it's not safe to use
			 * the previous array.
			 */
			bond_reset_slave_arr(bond);
			जाओ out;
		पूर्ण
		spin_unlock_bh(&bond->mode_lock);
		agg_id = ad_info.aggregator_id;
	पूर्ण
	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (skipslave == slave)
			जारी;

		all_slaves->arr[all_slaves->count++] = slave;
		अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
			काष्ठा aggregator *agg;

			agg = SLAVE_AD_INFO(slave)->port.aggregator;
			अगर (!agg || agg->aggregator_identअगरier != agg_id)
				जारी;
		पूर्ण
		अगर (!bond_slave_can_tx(slave))
			जारी;

		slave_dbg(bond->dev, slave->dev, "Adding slave to tx hash array[%d]\n",
			  usable_slaves->count);

		usable_slaves->arr[usable_slaves->count++] = slave;
	पूर्ण

	bond_set_slave_arr(bond, usable_slaves, all_slaves);
	वापस ret;
out:
	अगर (ret != 0 && skipslave) अणु
		bond_skip_slave(rtnl_dereference(bond->all_slaves),
				skipslave);
		bond_skip_slave(rtnl_dereference(bond->usable_slaves),
				skipslave);
	पूर्ण
	kमुक्त_rcu(all_slaves, rcu);
	kमुक्त_rcu(usable_slaves, rcu);

	वापस ret;
पूर्ण

अटल काष्ठा slave *bond_xmit_3ad_xor_slave_get(काष्ठा bonding *bond,
						 काष्ठा sk_buff *skb,
						 काष्ठा bond_up_slave *slaves)
अणु
	काष्ठा slave *slave;
	अचिन्हित पूर्णांक count;
	u32 hash;

	hash = bond_xmit_hash(bond, skb);
	count = slaves ? READ_ONCE(slaves->count) : 0;
	अगर (unlikely(!count))
		वापस शून्य;

	slave = slaves->arr[hash % count];
	वापस slave;
पूर्ण

/* Use this Xmit function क्रम 3AD as well as XOR modes. The current
 * usable slave array is क्रमmed in the control path. The xmit function
 * just calculates hash and sends the packet out.
 */
अटल netdev_tx_t bond_3ad_xor_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा bonding *bond = netdev_priv(dev);
	काष्ठा bond_up_slave *slaves;
	काष्ठा slave *slave;

	slaves = rcu_dereference(bond->usable_slaves);
	slave = bond_xmit_3ad_xor_slave_get(bond, skb, slaves);
	अगर (likely(slave))
		वापस bond_dev_queue_xmit(bond, skb, slave->dev);

	वापस bond_tx_drop(dev, skb);
पूर्ण

/* in broadcast mode, we send everything to all usable पूर्णांकerfaces. */
अटल netdev_tx_t bond_xmit_broadcast(काष्ठा sk_buff *skb,
				       काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा slave *slave = शून्य;
	काष्ठा list_head *iter;

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (bond_is_last_slave(bond, slave))
			अवरोध;
		अगर (bond_slave_is_up(slave) && slave->link == BOND_LINK_UP) अणु
			काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

			अगर (!skb2) अणु
				net_err_ratelimited("%s: Error: %s: skb_clone() failed\n",
						    bond_dev->name, __func__);
				जारी;
			पूर्ण
			bond_dev_queue_xmit(bond, skb2, slave->dev);
		पूर्ण
	पूर्ण
	अगर (slave && bond_slave_is_up(slave) && slave->link == BOND_LINK_UP)
		वापस bond_dev_queue_xmit(bond, skb, slave->dev);

	वापस bond_tx_drop(bond_dev, skb);
पूर्ण

/*------------------------- Device initialization ---------------------------*/

/* Lookup the slave that corresponds to a qid */
अटल अंतरभूत पूर्णांक bond_slave_override(काष्ठा bonding *bond,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा slave *slave = शून्य;
	काष्ठा list_head *iter;

	अगर (!skb_rx_queue_recorded(skb))
		वापस 1;

	/* Find out अगर any slaves have the same mapping as this skb. */
	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (slave->queue_id == skb_get_queue_mapping(skb)) अणु
			अगर (bond_slave_is_up(slave) &&
			    slave->link == BOND_LINK_UP) अणु
				bond_dev_queue_xmit(bond, skb, slave->dev);
				वापस 0;
			पूर्ण
			/* If the slave isn't UP, use शेष transmit policy. */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण


अटल u16 bond_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			     काष्ठा net_device *sb_dev)
अणु
	/* This helper function exists to help dev_pick_tx get the correct
	 * destination queue.  Using a helper function skips a call to
	 * skb_tx_hash and will put the skbs in the queue we expect on their
	 * way करोwn to the bonding driver.
	 */
	u16 txq = skb_rx_queue_recorded(skb) ? skb_get_rx_queue(skb) : 0;

	/* Save the original txq to restore beक्रमe passing to the driver */
	qdisc_skb_cb(skb)->slave_dev_queue_mapping = skb_get_queue_mapping(skb);

	अगर (unlikely(txq >= dev->real_num_tx_queues)) अणु
		करो अणु
			txq -= dev->real_num_tx_queues;
		पूर्ण जबतक (txq >= dev->real_num_tx_queues);
	पूर्ण
	वापस txq;
पूर्ण

अटल काष्ठा net_device *bond_xmit_get_slave(काष्ठा net_device *master_dev,
					      काष्ठा sk_buff *skb,
					      bool all_slaves)
अणु
	काष्ठा bonding *bond = netdev_priv(master_dev);
	काष्ठा bond_up_slave *slaves;
	काष्ठा slave *slave = शून्य;

	चयन (BOND_MODE(bond)) अणु
	हाल BOND_MODE_ROUNDROBIN:
		slave = bond_xmit_roundrobin_slave_get(bond, skb);
		अवरोध;
	हाल BOND_MODE_ACTIVEBACKUP:
		slave = bond_xmit_activebackup_slave_get(bond, skb);
		अवरोध;
	हाल BOND_MODE_8023AD:
	हाल BOND_MODE_XOR:
		अगर (all_slaves)
			slaves = rcu_dereference(bond->all_slaves);
		अन्यथा
			slaves = rcu_dereference(bond->usable_slaves);
		slave = bond_xmit_3ad_xor_slave_get(bond, skb, slaves);
		अवरोध;
	हाल BOND_MODE_BROADCAST:
		अवरोध;
	हाल BOND_MODE_ALB:
		slave = bond_xmit_alb_slave_get(bond, skb);
		अवरोध;
	हाल BOND_MODE_TLB:
		slave = bond_xmit_tlb_slave_get(bond, skb);
		अवरोध;
	शेष:
		/* Should never happen, mode alपढ़ोy checked */
		WARN_ONCE(true, "Unknown bonding mode");
		अवरोध;
	पूर्ण

	अगर (slave)
		वापस slave->dev;
	वापस शून्य;
पूर्ण

अटल व्योम bond_sk_to_flow(काष्ठा sock *sk, काष्ठा flow_keys *flow)
अणु
	चयन (sk->sk_family) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		अगर (sk->sk_ipv6only ||
		    ipv6_addr_type(&sk->sk_v6_daddr) != IPV6_ADDR_MAPPED) अणु
			flow->control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
			flow->addrs.v6addrs.src = inet6_sk(sk)->saddr;
			flow->addrs.v6addrs.dst = sk->sk_v6_daddr;
			अवरोध;
		पूर्ण
		fallthrough;
#पूर्ण_अगर
	शेष: /* AF_INET */
		flow->control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		flow->addrs.v4addrs.src = inet_sk(sk)->inet_rcv_saddr;
		flow->addrs.v4addrs.dst = inet_sk(sk)->inet_daddr;
		अवरोध;
	पूर्ण

	flow->ports.src = inet_sk(sk)->inet_sport;
	flow->ports.dst = inet_sk(sk)->inet_dport;
पूर्ण

/**
 * bond_sk_hash_l34 - generate a hash value based on the socket's L3 and L4 fields
 * @sk: socket to use क्रम headers
 *
 * This function will extract the necessary field from the socket and use
 * them to generate a hash based on the LAYER34 xmit_policy.
 * Assumes that sk is a TCP or UDP socket.
 */
अटल u32 bond_sk_hash_l34(काष्ठा sock *sk)
अणु
	काष्ठा flow_keys flow;
	u32 hash;

	bond_sk_to_flow(sk, &flow);

	/* L4 */
	स_नकल(&hash, &flow.ports.ports, माप(hash));
	/* L3 */
	वापस bond_ip_hash(hash, &flow);
पूर्ण

अटल काष्ठा net_device *__bond_sk_get_lower_dev(काष्ठा bonding *bond,
						  काष्ठा sock *sk)
अणु
	काष्ठा bond_up_slave *slaves;
	काष्ठा slave *slave;
	अचिन्हित पूर्णांक count;
	u32 hash;

	slaves = rcu_dereference(bond->usable_slaves);
	count = slaves ? READ_ONCE(slaves->count) : 0;
	अगर (unlikely(!count))
		वापस शून्य;

	hash = bond_sk_hash_l34(sk);
	slave = slaves->arr[hash % count];

	वापस slave->dev;
पूर्ण

अटल काष्ठा net_device *bond_sk_get_lower_dev(काष्ठा net_device *dev,
						काष्ठा sock *sk)
अणु
	काष्ठा bonding *bond = netdev_priv(dev);
	काष्ठा net_device *lower = शून्य;

	rcu_पढ़ो_lock();
	अगर (bond_sk_check(bond))
		lower = __bond_sk_get_lower_dev(bond, sk);
	rcu_पढ़ो_unlock();

	वापस lower;
पूर्ण

#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
अटल netdev_tx_t bond_tls_device_xmit(काष्ठा bonding *bond, काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	अगर (likely(bond_get_slave_by_dev(bond, tls_get_ctx(skb->sk)->netdev)))
		वापस bond_dev_queue_xmit(bond, skb, tls_get_ctx(skb->sk)->netdev);
	वापस bond_tx_drop(dev, skb);
पूर्ण
#पूर्ण_अगर

अटल netdev_tx_t __bond_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bonding *bond = netdev_priv(dev);

	अगर (bond_should_override_tx_queue(bond) &&
	    !bond_slave_override(bond, skb))
		वापस NETDEV_TX_OK;

#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
	अगर (skb->sk && tls_is_sk_tx_device_offloaded(skb->sk))
		वापस bond_tls_device_xmit(bond, skb, dev);
#पूर्ण_अगर

	चयन (BOND_MODE(bond)) अणु
	हाल BOND_MODE_ROUNDROBIN:
		वापस bond_xmit_roundrobin(skb, dev);
	हाल BOND_MODE_ACTIVEBACKUP:
		वापस bond_xmit_activebackup(skb, dev);
	हाल BOND_MODE_8023AD:
	हाल BOND_MODE_XOR:
		वापस bond_3ad_xor_xmit(skb, dev);
	हाल BOND_MODE_BROADCAST:
		वापस bond_xmit_broadcast(skb, dev);
	हाल BOND_MODE_ALB:
		वापस bond_alb_xmit(skb, dev);
	हाल BOND_MODE_TLB:
		वापस bond_tlb_xmit(skb, dev);
	शेष:
		/* Should never happen, mode alपढ़ोy checked */
		netdev_err(dev, "Unknown bonding mode %d\n", BOND_MODE(bond));
		WARN_ON_ONCE(1);
		वापस bond_tx_drop(dev, skb);
	पूर्ण
पूर्ण

अटल netdev_tx_t bond_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bonding *bond = netdev_priv(dev);
	netdev_tx_t ret = NETDEV_TX_OK;

	/* If we risk deadlock from transmitting this in the
	 * netpoll path, tell netpoll to queue the frame क्रम later tx
	 */
	अगर (unlikely(is_netpoll_tx_blocked(dev)))
		वापस NETDEV_TX_BUSY;

	rcu_पढ़ो_lock();
	अगर (bond_has_slaves(bond))
		ret = __bond_start_xmit(skb, dev);
	अन्यथा
		ret = bond_tx_drop(dev, skb);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल u32 bond_mode_bcast_speed(काष्ठा slave *slave, u32 speed)
अणु
	अगर (speed == 0 || speed == SPEED_UNKNOWN)
		speed = slave->speed;
	अन्यथा
		speed = min(speed, slave->speed);

	वापस speed;
पूर्ण

अटल पूर्णांक bond_ethtool_get_link_ksettings(काष्ठा net_device *bond_dev,
					   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	u32 speed = 0;

	cmd->base.duplex = DUPLEX_UNKNOWN;
	cmd->base.port = PORT_OTHER;

	/* Since bond_slave_can_tx वापसs false क्रम all inactive or करोwn slaves, we
	 * करो not need to check mode.  Though link speed might not represent
	 * the true receive or transmit bandwidth (not all modes are symmetric)
	 * this is an accurate maximum.
	 */
	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (bond_slave_can_tx(slave)) अणु
			अगर (slave->speed != SPEED_UNKNOWN) अणु
				अगर (BOND_MODE(bond) == BOND_MODE_BROADCAST)
					speed = bond_mode_bcast_speed(slave,
								      speed);
				अन्यथा
					speed += slave->speed;
			पूर्ण
			अगर (cmd->base.duplex == DUPLEX_UNKNOWN &&
			    slave->duplex != DUPLEX_UNKNOWN)
				cmd->base.duplex = slave->duplex;
		पूर्ण
	पूर्ण
	cmd->base.speed = speed ? : SPEED_UNKNOWN;

	वापस 0;
पूर्ण

अटल व्योम bond_ethtool_get_drvinfo(काष्ठा net_device *bond_dev,
				     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version), "%d",
		 BOND_ABI_VERSION);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bond_ethtool_ops = अणु
	.get_drvinfo		= bond_ethtool_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= bond_ethtool_get_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops bond_netdev_ops = अणु
	.nकरो_init		= bond_init,
	.nकरो_uninit		= bond_uninit,
	.nकरो_खोलो		= bond_खोलो,
	.nकरो_stop		= bond_बंद,
	.nकरो_start_xmit		= bond_start_xmit,
	.nकरो_select_queue	= bond_select_queue,
	.nकरो_get_stats64	= bond_get_stats,
	.nकरो_करो_ioctl		= bond_करो_ioctl,
	.nकरो_change_rx_flags	= bond_change_rx_flags,
	.nकरो_set_rx_mode	= bond_set_rx_mode,
	.nकरो_change_mtu		= bond_change_mtu,
	.nकरो_set_mac_address	= bond_set_mac_address,
	.nकरो_neigh_setup	= bond_neigh_setup,
	.nकरो_vlan_rx_add_vid	= bond_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= bond_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_netpoll_setup	= bond_netpoll_setup,
	.nकरो_netpoll_cleanup	= bond_netpoll_cleanup,
	.nकरो_poll_controller	= bond_poll_controller,
#पूर्ण_अगर
	.nकरो_add_slave		= bond_enslave,
	.nकरो_del_slave		= bond_release,
	.nकरो_fix_features	= bond_fix_features,
	.nकरो_features_check	= passthru_features_check,
	.nकरो_get_xmit_slave	= bond_xmit_get_slave,
	.nकरो_sk_get_lower_dev	= bond_sk_get_lower_dev,
पूर्ण;

अटल स्थिर काष्ठा device_type bond_type = अणु
	.name = "bond",
पूर्ण;

अटल व्योम bond_deकाष्ठाor(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	अगर (bond->wq)
		destroy_workqueue(bond->wq);
पूर्ण

व्योम bond_setup(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);

	spin_lock_init(&bond->mode_lock);
	bond->params = bonding_शेषs;

	/* Initialize poपूर्णांकers */
	bond->dev = bond_dev;

	/* Initialize the device entry poपूर्णांकs */
	ether_setup(bond_dev);
	bond_dev->max_mtu = ETH_MAX_MTU;
	bond_dev->netdev_ops = &bond_netdev_ops;
	bond_dev->ethtool_ops = &bond_ethtool_ops;

	bond_dev->needs_मुक्त_netdev = true;
	bond_dev->priv_deकाष्ठाor = bond_deकाष्ठाor;

	SET_NETDEV_DEVTYPE(bond_dev, &bond_type);

	/* Initialize the device options */
	bond_dev->flags |= IFF_MASTER;
	bond_dev->priv_flags |= IFF_BONDING | IFF_UNICAST_FLT | IFF_NO_QUEUE;
	bond_dev->priv_flags &= ~(IFF_XMIT_DST_RELEASE | IFF_TX_SKB_SHARING);

#अगर_घोषित CONFIG_XFRM_OFFLOAD
	/* set up xfrm device ops (only supported in active-backup right now) */
	bond_dev->xfrmdev_ops = &bond_xfrmdev_ops;
	bond->xs = शून्य;
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */

	/* करोn't acquire bond device's netअगर_tx_lock when transmitting */
	bond_dev->features |= NETIF_F_LLTX;

	/* By शेष, we declare the bond to be fully
	 * VLAN hardware accelerated capable. Special
	 * care is taken in the various xmit functions
	 * when there are slaves that are not hw accel
	 * capable
	 */

	/* Don't allow bond devices to change network namespaces. */
	bond_dev->features |= NETIF_F_NETNS_LOCAL;

	bond_dev->hw_features = BOND_VLAN_FEATURES |
				NETIF_F_HW_VLAN_CTAG_RX |
				NETIF_F_HW_VLAN_CTAG_FILTER;

	bond_dev->hw_features |= NETIF_F_GSO_ENCAP_ALL;
	bond_dev->features |= bond_dev->hw_features;
	bond_dev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_STAG_TX;
#अगर_घोषित CONFIG_XFRM_OFFLOAD
	bond_dev->hw_features |= BOND_XFRM_FEATURES;
	/* Only enable XFRM features अगर this is an active-backup config */
	अगर (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP)
		bond_dev->features |= BOND_XFRM_FEATURES;
#पूर्ण_अगर /* CONFIG_XFRM_OFFLOAD */
#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
	अगर (bond_sk_check(bond))
		bond_dev->features |= BOND_TLS_FEATURES;
#पूर्ण_अगर
पूर्ण

/* Destroy a bonding device.
 * Must be under rtnl_lock when this function is called.
 */
अटल व्योम bond_uninit(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा bond_up_slave *usable, *all;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	bond_netpoll_cleanup(bond_dev);

	/* Release the bonded slaves */
	bond_क्रम_each_slave(bond, slave, iter)
		__bond_release_one(bond_dev, slave->dev, true, true);
	netdev_info(bond_dev, "Released all slaves\n");

	usable = rtnl_dereference(bond->usable_slaves);
	अगर (usable) अणु
		RCU_INIT_POINTER(bond->usable_slaves, शून्य);
		kमुक्त_rcu(usable, rcu);
	पूर्ण

	all = rtnl_dereference(bond->all_slaves);
	अगर (all) अणु
		RCU_INIT_POINTER(bond->all_slaves, शून्य);
		kमुक्त_rcu(all, rcu);
	पूर्ण

	list_del(&bond->bond_list);

	bond_debug_unरेजिस्टर(bond);
पूर्ण

/*------------------------- Module initialization ---------------------------*/

अटल पूर्णांक bond_check_params(काष्ठा bond_params *params)
अणु
	पूर्णांक arp_validate_value, fail_over_mac_value, primary_reselect_value, i;
	काष्ठा bond_opt_value newval;
	स्थिर काष्ठा bond_opt_value *valptr;
	पूर्णांक arp_all_tarमाला_लो_value = 0;
	u16 ad_actor_sys_prio = 0;
	u16 ad_user_port_key = 0;
	__be32 arp_target[BOND_MAX_ARP_TARGETS] = अणु 0 पूर्ण;
	पूर्णांक arp_ip_count;
	पूर्णांक bond_mode	= BOND_MODE_ROUNDROBIN;
	पूर्णांक xmit_hashtype = BOND_XMIT_POLICY_LAYER2;
	पूर्णांक lacp_fast = 0;
	पूर्णांक tlb_dynamic_lb;

	/* Convert string parameters. */
	अगर (mode) अणु
		bond_opt_initstr(&newval, mode);
		valptr = bond_opt_parse(bond_opt_get(BOND_OPT_MODE), &newval);
		अगर (!valptr) अणु
			pr_err("Error: Invalid bonding mode \"%s\"\n", mode);
			वापस -EINVAL;
		पूर्ण
		bond_mode = valptr->value;
	पूर्ण

	अगर (xmit_hash_policy) अणु
		अगर (bond_mode == BOND_MODE_ROUNDROBIN ||
		    bond_mode == BOND_MODE_ACTIVEBACKUP ||
		    bond_mode == BOND_MODE_BROADCAST) अणु
			pr_info("xmit_hash_policy param is irrelevant in mode %s\n",
				bond_mode_name(bond_mode));
		पूर्ण अन्यथा अणु
			bond_opt_initstr(&newval, xmit_hash_policy);
			valptr = bond_opt_parse(bond_opt_get(BOND_OPT_XMIT_HASH),
						&newval);
			अगर (!valptr) अणु
				pr_err("Error: Invalid xmit_hash_policy \"%s\"\n",
				       xmit_hash_policy);
				वापस -EINVAL;
			पूर्ण
			xmit_hashtype = valptr->value;
		पूर्ण
	पूर्ण

	अगर (lacp_rate) अणु
		अगर (bond_mode != BOND_MODE_8023AD) अणु
			pr_info("lacp_rate param is irrelevant in mode %s\n",
				bond_mode_name(bond_mode));
		पूर्ण अन्यथा अणु
			bond_opt_initstr(&newval, lacp_rate);
			valptr = bond_opt_parse(bond_opt_get(BOND_OPT_LACP_RATE),
						&newval);
			अगर (!valptr) अणु
				pr_err("Error: Invalid lacp rate \"%s\"\n",
				       lacp_rate);
				वापस -EINVAL;
			पूर्ण
			lacp_fast = valptr->value;
		पूर्ण
	पूर्ण

	अगर (ad_select) अणु
		bond_opt_initstr(&newval, ad_select);
		valptr = bond_opt_parse(bond_opt_get(BOND_OPT_AD_SELECT),
					&newval);
		अगर (!valptr) अणु
			pr_err("Error: Invalid ad_select \"%s\"\n", ad_select);
			वापस -EINVAL;
		पूर्ण
		params->ad_select = valptr->value;
		अगर (bond_mode != BOND_MODE_8023AD)
			pr_warn("ad_select param only affects 802.3ad mode\n");
	पूर्ण अन्यथा अणु
		params->ad_select = BOND_AD_STABLE;
	पूर्ण

	अगर (max_bonds < 0) अणु
		pr_warn("Warning: max_bonds (%d) not in range %d-%d, so it was reset to BOND_DEFAULT_MAX_BONDS (%d)\n",
			max_bonds, 0, पूर्णांक_उच्च, BOND_DEFAULT_MAX_BONDS);
		max_bonds = BOND_DEFAULT_MAX_BONDS;
	पूर्ण

	अगर (miimon < 0) अणु
		pr_warn("Warning: miimon module parameter (%d), not in range 0-%d, so it was reset to 0\n",
			miimon, पूर्णांक_उच्च);
		miimon = 0;
	पूर्ण

	अगर (updelay < 0) अणु
		pr_warn("Warning: updelay module parameter (%d), not in range 0-%d, so it was reset to 0\n",
			updelay, पूर्णांक_उच्च);
		updelay = 0;
	पूर्ण

	अगर (करोwndelay < 0) अणु
		pr_warn("Warning: downdelay module parameter (%d), not in range 0-%d, so it was reset to 0\n",
			करोwndelay, पूर्णांक_उच्च);
		करोwndelay = 0;
	पूर्ण

	अगर ((use_carrier != 0) && (use_carrier != 1)) अणु
		pr_warn("Warning: use_carrier module parameter (%d), not of valid value (0/1), so it was set to 1\n",
			use_carrier);
		use_carrier = 1;
	पूर्ण

	अगर (num_peer_notअगर < 0 || num_peer_notअगर > 255) अणु
		pr_warn("Warning: num_grat_arp/num_unsol_na (%d) not in range 0-255 so it was reset to 1\n",
			num_peer_notअगर);
		num_peer_notअगर = 1;
	पूर्ण

	/* reset values क्रम 802.3ad/TLB/ALB */
	अगर (!bond_mode_uses_arp(bond_mode)) अणु
		अगर (!miimon) अणु
			pr_warn("Warning: miimon must be specified, otherwise bonding will not detect link failure, speed and duplex which are essential for 802.3ad operation\n");
			pr_warn("Forcing miimon to 100msec\n");
			miimon = BOND_DEFAULT_MIIMON;
		पूर्ण
	पूर्ण

	अगर (tx_queues < 1 || tx_queues > 255) अणु
		pr_warn("Warning: tx_queues (%d) should be between 1 and 255, resetting to %d\n",
			tx_queues, BOND_DEFAULT_TX_QUEUES);
		tx_queues = BOND_DEFAULT_TX_QUEUES;
	पूर्ण

	अगर ((all_slaves_active != 0) && (all_slaves_active != 1)) अणु
		pr_warn("Warning: all_slaves_active module parameter (%d), not of valid value (0/1), so it was set to 0\n",
			all_slaves_active);
		all_slaves_active = 0;
	पूर्ण

	अगर (resend_igmp < 0 || resend_igmp > 255) अणु
		pr_warn("Warning: resend_igmp (%d) should be between 0 and 255, resetting to %d\n",
			resend_igmp, BOND_DEFAULT_RESEND_IGMP);
		resend_igmp = BOND_DEFAULT_RESEND_IGMP;
	पूर्ण

	bond_opt_initval(&newval, packets_per_slave);
	अगर (!bond_opt_parse(bond_opt_get(BOND_OPT_PACKETS_PER_SLAVE), &newval)) अणु
		pr_warn("Warning: packets_per_slave (%d) should be between 0 and %u resetting to 1\n",
			packets_per_slave, अच_लघु_उच्च);
		packets_per_slave = 1;
	पूर्ण

	अगर (bond_mode == BOND_MODE_ALB) अणु
		pr_notice("In ALB mode you might experience client disconnections upon reconnection of a link if the bonding module updelay parameter (%d msec) is incompatible with the forwarding delay time of the switch\n",
			  updelay);
	पूर्ण

	अगर (!miimon) अणु
		अगर (updelay || करोwndelay) अणु
			/* just warn the user the up/करोwn delay will have
			 * no effect since miimon is zero...
			 */
			pr_warn("Warning: miimon module parameter not set and updelay (%d) or downdelay (%d) module parameter is set; updelay and downdelay have no effect unless miimon is set\n",
				updelay, करोwndelay);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* करोn't allow arp monitoring */
		अगर (arp_पूर्णांकerval) अणु
			pr_warn("Warning: miimon (%d) and arp_interval (%d) can't be used simultaneously, disabling ARP monitoring\n",
				miimon, arp_पूर्णांकerval);
			arp_पूर्णांकerval = 0;
		पूर्ण

		अगर ((updelay % miimon) != 0) अणु
			pr_warn("Warning: updelay (%d) is not a multiple of miimon (%d), updelay rounded to %d ms\n",
				updelay, miimon, (updelay / miimon) * miimon);
		पूर्ण

		updelay /= miimon;

		अगर ((करोwndelay % miimon) != 0) अणु
			pr_warn("Warning: downdelay (%d) is not a multiple of miimon (%d), downdelay rounded to %d ms\n",
				करोwndelay, miimon,
				(करोwndelay / miimon) * miimon);
		पूर्ण

		करोwndelay /= miimon;
	पूर्ण

	अगर (arp_पूर्णांकerval < 0) अणु
		pr_warn("Warning: arp_interval module parameter (%d), not in range 0-%d, so it was reset to 0\n",
			arp_पूर्णांकerval, पूर्णांक_उच्च);
		arp_पूर्णांकerval = 0;
	पूर्ण

	क्रम (arp_ip_count = 0, i = 0;
	     (arp_ip_count < BOND_MAX_ARP_TARGETS) && arp_ip_target[i]; i++) अणु
		__be32 ip;

		/* not a complete check, but good enough to catch mistakes */
		अगर (!in4_pton(arp_ip_target[i], -1, (u8 *)&ip, -1, शून्य) ||
		    !bond_is_ip_target_ok(ip)) अणु
			pr_warn("Warning: bad arp_ip_target module parameter (%s), ARP monitoring will not be performed\n",
				arp_ip_target[i]);
			arp_पूर्णांकerval = 0;
		पूर्ण अन्यथा अणु
			अगर (bond_get_tarमाला_लो_ip(arp_target, ip) == -1)
				arp_target[arp_ip_count++] = ip;
			अन्यथा
				pr_warn("Warning: duplicate address %pI4 in arp_ip_target, skipping\n",
					&ip);
		पूर्ण
	पूर्ण

	अगर (arp_पूर्णांकerval && !arp_ip_count) अणु
		/* करोn't allow arping अगर no arp_ip_target given... */
		pr_warn("Warning: arp_interval module parameter (%d) specified without providing an arp_ip_target parameter, arp_interval was reset to 0\n",
			arp_पूर्णांकerval);
		arp_पूर्णांकerval = 0;
	पूर्ण

	अगर (arp_validate) अणु
		अगर (!arp_पूर्णांकerval) अणु
			pr_err("arp_validate requires arp_interval\n");
			वापस -EINVAL;
		पूर्ण

		bond_opt_initstr(&newval, arp_validate);
		valptr = bond_opt_parse(bond_opt_get(BOND_OPT_ARP_VALIDATE),
					&newval);
		अगर (!valptr) अणु
			pr_err("Error: invalid arp_validate \"%s\"\n",
			       arp_validate);
			वापस -EINVAL;
		पूर्ण
		arp_validate_value = valptr->value;
	पूर्ण अन्यथा अणु
		arp_validate_value = 0;
	पूर्ण

	अगर (arp_all_tarमाला_लो) अणु
		bond_opt_initstr(&newval, arp_all_tarमाला_लो);
		valptr = bond_opt_parse(bond_opt_get(BOND_OPT_ARP_ALL_TARGETS),
					&newval);
		अगर (!valptr) अणु
			pr_err("Error: invalid arp_all_targets_value \"%s\"\n",
			       arp_all_tarमाला_लो);
			arp_all_tarमाला_लो_value = 0;
		पूर्ण अन्यथा अणु
			arp_all_tarमाला_लो_value = valptr->value;
		पूर्ण
	पूर्ण

	अगर (miimon) अणु
		pr_info("MII link monitoring set to %d ms\n", miimon);
	पूर्ण अन्यथा अगर (arp_पूर्णांकerval) अणु
		valptr = bond_opt_get_val(BOND_OPT_ARP_VALIDATE,
					  arp_validate_value);
		pr_info("ARP monitoring set to %d ms, validate %s, with %d target(s):",
			arp_पूर्णांकerval, valptr->string, arp_ip_count);

		क्रम (i = 0; i < arp_ip_count; i++)
			pr_cont(" %s", arp_ip_target[i]);

		pr_cont("\n");

	पूर्ण अन्यथा अगर (max_bonds) अणु
		/* miimon and arp_पूर्णांकerval not set, we need one so things
		 * work as expected, see bonding.txt क्रम details
		 */
		pr_debug("Warning: either miimon or arp_interval and arp_ip_target module parameters must be specified, otherwise bonding will not detect link failures! see bonding.txt for details\n");
	पूर्ण

	अगर (primary && !bond_mode_uses_primary(bond_mode)) अणु
		/* currently, using a primary only makes sense
		 * in active backup, TLB or ALB modes
		 */
		pr_warn("Warning: %s primary device specified but has no effect in %s mode\n",
			primary, bond_mode_name(bond_mode));
		primary = शून्य;
	पूर्ण

	अगर (primary && primary_reselect) अणु
		bond_opt_initstr(&newval, primary_reselect);
		valptr = bond_opt_parse(bond_opt_get(BOND_OPT_PRIMARY_RESELECT),
					&newval);
		अगर (!valptr) अणु
			pr_err("Error: Invalid primary_reselect \"%s\"\n",
			       primary_reselect);
			वापस -EINVAL;
		पूर्ण
		primary_reselect_value = valptr->value;
	पूर्ण अन्यथा अणु
		primary_reselect_value = BOND_PRI_RESELECT_ALWAYS;
	पूर्ण

	अगर (fail_over_mac) अणु
		bond_opt_initstr(&newval, fail_over_mac);
		valptr = bond_opt_parse(bond_opt_get(BOND_OPT_FAIL_OVER_MAC),
					&newval);
		अगर (!valptr) अणु
			pr_err("Error: invalid fail_over_mac \"%s\"\n",
			       fail_over_mac);
			वापस -EINVAL;
		पूर्ण
		fail_over_mac_value = valptr->value;
		अगर (bond_mode != BOND_MODE_ACTIVEBACKUP)
			pr_warn("Warning: fail_over_mac only affects active-backup mode\n");
	पूर्ण अन्यथा अणु
		fail_over_mac_value = BOND_FOM_NONE;
	पूर्ण

	bond_opt_initstr(&newval, "default");
	valptr = bond_opt_parse(
			bond_opt_get(BOND_OPT_AD_ACTOR_SYS_PRIO),
				     &newval);
	अगर (!valptr) अणु
		pr_err("Error: No ad_actor_sys_prio default value");
		वापस -EINVAL;
	पूर्ण
	ad_actor_sys_prio = valptr->value;

	valptr = bond_opt_parse(bond_opt_get(BOND_OPT_AD_USER_PORT_KEY),
				&newval);
	अगर (!valptr) अणु
		pr_err("Error: No ad_user_port_key default value");
		वापस -EINVAL;
	पूर्ण
	ad_user_port_key = valptr->value;

	bond_opt_initstr(&newval, "default");
	valptr = bond_opt_parse(bond_opt_get(BOND_OPT_TLB_DYNAMIC_LB), &newval);
	अगर (!valptr) अणु
		pr_err("Error: No tlb_dynamic_lb default value");
		वापस -EINVAL;
	पूर्ण
	tlb_dynamic_lb = valptr->value;

	अगर (lp_पूर्णांकerval == 0) अणु
		pr_warn("Warning: ip_interval must be between 1 and %d, so it was reset to %d\n",
			पूर्णांक_उच्च, BOND_ALB_DEFAULT_LP_INTERVAL);
		lp_पूर्णांकerval = BOND_ALB_DEFAULT_LP_INTERVAL;
	पूर्ण

	/* fill params काष्ठा with the proper values */
	params->mode = bond_mode;
	params->xmit_policy = xmit_hashtype;
	params->miimon = miimon;
	params->num_peer_notअगर = num_peer_notअगर;
	params->arp_पूर्णांकerval = arp_पूर्णांकerval;
	params->arp_validate = arp_validate_value;
	params->arp_all_tarमाला_लो = arp_all_tarमाला_लो_value;
	params->updelay = updelay;
	params->करोwndelay = करोwndelay;
	params->peer_notअगर_delay = 0;
	params->use_carrier = use_carrier;
	params->lacp_fast = lacp_fast;
	params->primary[0] = 0;
	params->primary_reselect = primary_reselect_value;
	params->fail_over_mac = fail_over_mac_value;
	params->tx_queues = tx_queues;
	params->all_slaves_active = all_slaves_active;
	params->resend_igmp = resend_igmp;
	params->min_links = min_links;
	params->lp_पूर्णांकerval = lp_पूर्णांकerval;
	params->packets_per_slave = packets_per_slave;
	params->tlb_dynamic_lb = tlb_dynamic_lb;
	params->ad_actor_sys_prio = ad_actor_sys_prio;
	eth_zero_addr(params->ad_actor_प्रणाली);
	params->ad_user_port_key = ad_user_port_key;
	अगर (packets_per_slave > 0) अणु
		params->reciprocal_packets_per_slave =
			reciprocal_value(packets_per_slave);
	पूर्ण अन्यथा अणु
		/* reciprocal_packets_per_slave is unused अगर
		 * packets_per_slave is 0 or 1, just initialize it
		 */
		params->reciprocal_packets_per_slave =
			(काष्ठा reciprocal_value) अणु 0 पूर्ण;
	पूर्ण

	अगर (primary) अणु
		म_नकलन(params->primary, primary, IFNAMSIZ);
		params->primary[IFNAMSIZ - 1] = 0;
	पूर्ण

	स_नकल(params->arp_tarमाला_लो, arp_target, माप(arp_target));

	वापस 0;
पूर्ण

/* Called from registration process */
अटल पूर्णांक bond_init(काष्ठा net_device *bond_dev)
अणु
	काष्ठा bonding *bond = netdev_priv(bond_dev);
	काष्ठा bond_net *bn = net_generic(dev_net(bond_dev), bond_net_id);

	netdev_dbg(bond_dev, "Begin bond_init\n");

	bond->wq = alloc_ordered_workqueue(bond_dev->name, WQ_MEM_RECLAIM);
	अगर (!bond->wq)
		वापस -ENOMEM;

	spin_lock_init(&bond->stats_lock);
	netdev_lockdep_set_classes(bond_dev);

	list_add_tail(&bond->bond_list, &bn->dev_list);

	bond_prepare_sysfs_group(bond);

	bond_debug_रेजिस्टर(bond);

	/* Ensure valid dev_addr */
	अगर (is_zero_ether_addr(bond_dev->dev_addr) &&
	    bond_dev->addr_assign_type == NET_ADDR_PERM)
		eth_hw_addr_अक्रमom(bond_dev);

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक bond_get_num_tx_queues(व्योम)
अणु
	वापस tx_queues;
पूर्ण

/* Create a new bond based on the specअगरied name and bonding parameters.
 * If name is शून्य, obtain a suitable "bond%d" name क्रम us.
 * Caller must NOT hold rtnl_lock; we need to release it here beक्रमe we
 * set up our sysfs entries.
 */
पूर्णांक bond_create(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा net_device *bond_dev;
	काष्ठा bonding *bond;
	काष्ठा alb_bond_info *bond_info;
	पूर्णांक res;

	rtnl_lock();

	bond_dev = alloc_netdev_mq(माप(काष्ठा bonding),
				   name ? name : "bond%d", NET_NAME_UNKNOWN,
				   bond_setup, tx_queues);
	अगर (!bond_dev) अणु
		pr_err("%s: eek! can't alloc netdev!\n", name);
		rtnl_unlock();
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Initialize rx_hashtbl_used_head to RLB_शून्य_INDEX.
	 * It is set to 0 by शेष which is wrong.
	 */
	bond = netdev_priv(bond_dev);
	bond_info = &(BOND_ALB_INFO(bond));
	bond_info->rx_hashtbl_used_head = RLB_शून्य_INDEX;

	dev_net_set(bond_dev, net);
	bond_dev->rtnl_link_ops = &bond_link_ops;

	res = रेजिस्टर_netdevice(bond_dev);
	अगर (res < 0) अणु
		मुक्त_netdev(bond_dev);
		rtnl_unlock();

		वापस res;
	पूर्ण

	netअगर_carrier_off(bond_dev);

	bond_work_init_all(bond);

	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक __net_init bond_net_init(काष्ठा net *net)
अणु
	काष्ठा bond_net *bn = net_generic(net, bond_net_id);

	bn->net = net;
	INIT_LIST_HEAD(&bn->dev_list);

	bond_create_proc_dir(bn);
	bond_create_sysfs(bn);

	वापस 0;
पूर्ण

अटल व्योम __net_निकास bond_net_निकास(काष्ठा net *net)
अणु
	काष्ठा bond_net *bn = net_generic(net, bond_net_id);
	काष्ठा bonding *bond, *पंचांगp_bond;
	LIST_HEAD(list);

	bond_destroy_sysfs(bn);

	/* Kill off any bonds created after unरेजिस्टरing bond rtnl ops */
	rtnl_lock();
	list_क्रम_each_entry_safe(bond, पंचांगp_bond, &bn->dev_list, bond_list)
		unरेजिस्टर_netdevice_queue(bond->dev, &list);
	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();

	bond_destroy_proc_dir(bn);
पूर्ण

अटल काष्ठा pernet_operations bond_net_ops = अणु
	.init = bond_net_init,
	.निकास = bond_net_निकास,
	.id   = &bond_net_id,
	.size = माप(काष्ठा bond_net),
पूर्ण;

अटल पूर्णांक __init bonding_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक res;

	res = bond_check_params(&bonding_शेषs);
	अगर (res)
		जाओ out;

	res = रेजिस्टर_pernet_subsys(&bond_net_ops);
	अगर (res)
		जाओ out;

	res = bond_netlink_init();
	अगर (res)
		जाओ err_link;

	bond_create_debugfs();

	क्रम (i = 0; i < max_bonds; i++) अणु
		res = bond_create(&init_net, शून्य);
		अगर (res)
			जाओ err;
	पूर्ण

	skb_flow_dissector_init(&flow_keys_bonding,
				flow_keys_bonding_keys,
				ARRAY_SIZE(flow_keys_bonding_keys));

	रेजिस्टर_netdevice_notअगरier(&bond_netdev_notअगरier);
out:
	वापस res;
err:
	bond_destroy_debugfs();
	bond_netlink_fini();
err_link:
	unरेजिस्टर_pernet_subsys(&bond_net_ops);
	जाओ out;

पूर्ण

अटल व्योम __निकास bonding_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&bond_netdev_notअगरier);

	bond_destroy_debugfs();

	bond_netlink_fini();
	unरेजिस्टर_pernet_subsys(&bond_net_ops);

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	/* Make sure we करोn't have an imbalance on our netpoll blocking */
	WARN_ON(atomic_पढ़ो(&netpoll_block_tx));
#पूर्ण_अगर
पूर्ण

module_init(bonding_init);
module_निकास(bonding_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR("Thomas Davis, tadavis@lbl.gov and many others");

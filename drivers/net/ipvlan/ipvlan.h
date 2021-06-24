<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014 Mahesh Bandewar <maheshb@google.com>
 */
#अगर_अघोषित __IPVLAN_H
#घोषणा __IPVLAN_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/rculist.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_route.h>
#समावेश <net/netns/generic.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/route.h>
#समावेश <net/addrconf.h>
#समावेश <net/l3mdev.h>

#घोषणा IPVLAN_DRV	"ipvlan"
#घोषणा IPV_DRV_VER	"0.1"

#घोषणा IPVLAN_HASH_SIZE	(1 << BITS_PER_BYTE)
#घोषणा IPVLAN_HASH_MASK	(IPVLAN_HASH_SIZE - 1)

#घोषणा IPVLAN_MAC_FILTER_BITS	8
#घोषणा IPVLAN_MAC_FILTER_SIZE	(1 << IPVLAN_MAC_FILTER_BITS)
#घोषणा IPVLAN_MAC_FILTER_MASK	(IPVLAN_MAC_FILTER_SIZE - 1)

#घोषणा IPVLAN_QBACKLOG_LIMIT	1000

प्रकार क्रमागत अणु
	IPVL_IPV6 = 0,
	IPVL_ICMPV6,
	IPVL_IPV4,
	IPVL_ARP,
पूर्ण ipvl_hdr_type;

काष्ठा ipvl_pcpu_stats अणु
	u64			rx_pkts;
	u64			rx_bytes;
	u64			rx_mcast;
	u64			tx_pkts;
	u64			tx_bytes;
	काष्ठा u64_stats_sync	syncp;
	u32			rx_errs;
	u32			tx_drps;
पूर्ण;

काष्ठा ipvl_port;

काष्ठा ipvl_dev अणु
	काष्ठा net_device	*dev;
	काष्ठा list_head	pnode;
	काष्ठा ipvl_port	*port;
	काष्ठा net_device	*phy_dev;
	काष्ठा list_head	addrs;
	काष्ठा ipvl_pcpu_stats	__percpu *pcpu_stats;
	DECLARE_BITMAP(mac_filters, IPVLAN_MAC_FILTER_SIZE);
	netdev_features_t	sfeatures;
	u32			msg_enable;
	spinlock_t		addrs_lock;
पूर्ण;

काष्ठा ipvl_addr अणु
	काष्ठा ipvl_dev		*master; /* Back poपूर्णांकer to master */
	जोड़ अणु
		काष्ठा in6_addr	ip6;	 /* IPv6 address on logical पूर्णांकerface */
		काष्ठा in_addr	ip4;	 /* IPv4 address on logical पूर्णांकerface */
	पूर्ण ipu;
#घोषणा ip6addr	ipu.ip6
#घोषणा ip4addr ipu.ip4
	काष्ठा hlist_node	hlnode;  /* Hash-table linkage */
	काष्ठा list_head	anode;   /* logical-पूर्णांकerface linkage */
	ipvl_hdr_type		atype;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा ipvl_port अणु
	काष्ठा net_device	*dev;
	possible_net_t		pnet;
	काष्ठा hlist_head	hlhead[IPVLAN_HASH_SIZE];
	काष्ठा list_head	ipvlans;
	u16			mode;
	u16			flags;
	u16			dev_id_start;
	काष्ठा work_काष्ठा	wq;
	काष्ठा sk_buff_head	backlog;
	पूर्णांक			count;
	काष्ठा ida		ida;
पूर्ण;

काष्ठा ipvl_skb_cb अणु
	bool tx_pkt;
पूर्ण;
#घोषणा IPVL_SKB_CB(_skb) ((काष्ठा ipvl_skb_cb *)&((_skb)->cb[0]))

अटल अंतरभूत काष्ठा ipvl_port *ipvlan_port_get_rcu(स्थिर काष्ठा net_device *d)
अणु
	वापस rcu_dereference(d->rx_handler_data);
पूर्ण

अटल अंतरभूत काष्ठा ipvl_port *ipvlan_port_get_rcu_bh(स्थिर काष्ठा net_device *d)
अणु
	वापस rcu_dereference_bh(d->rx_handler_data);
पूर्ण

अटल अंतरभूत काष्ठा ipvl_port *ipvlan_port_get_rtnl(स्थिर काष्ठा net_device *d)
अणु
	वापस rtnl_dereference(d->rx_handler_data);
पूर्ण

अटल अंतरभूत bool ipvlan_is_निजी(स्थिर काष्ठा ipvl_port *port)
अणु
	वापस !!(port->flags & IPVLAN_F_PRIVATE);
पूर्ण

अटल अंतरभूत व्योम ipvlan_mark_निजी(काष्ठा ipvl_port *port)
अणु
	port->flags |= IPVLAN_F_PRIVATE;
पूर्ण

अटल अंतरभूत व्योम ipvlan_clear_निजी(काष्ठा ipvl_port *port)
अणु
	port->flags &= ~IPVLAN_F_PRIVATE;
पूर्ण

अटल अंतरभूत bool ipvlan_is_vepa(स्थिर काष्ठा ipvl_port *port)
अणु
	वापस !!(port->flags & IPVLAN_F_VEPA);
पूर्ण

अटल अंतरभूत व्योम ipvlan_mark_vepa(काष्ठा ipvl_port *port)
अणु
	port->flags |= IPVLAN_F_VEPA;
पूर्ण

अटल अंतरभूत व्योम ipvlan_clear_vepa(काष्ठा ipvl_port *port)
अणु
	port->flags &= ~IPVLAN_F_VEPA;
पूर्ण

व्योम ipvlan_init_secret(व्योम);
अचिन्हित पूर्णांक ipvlan_mac_hash(स्थिर अचिन्हित अक्षर *addr);
rx_handler_result_t ipvlan_handle_frame(काष्ठा sk_buff **pskb);
व्योम ipvlan_process_multicast(काष्ठा work_काष्ठा *work);
पूर्णांक ipvlan_queue_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम ipvlan_ht_addr_add(काष्ठा ipvl_dev *ipvlan, काष्ठा ipvl_addr *addr);
काष्ठा ipvl_addr *ipvlan_find_addr(स्थिर काष्ठा ipvl_dev *ipvlan,
				   स्थिर व्योम *iaddr, bool is_v6);
bool ipvlan_addr_busy(काष्ठा ipvl_port *port, व्योम *iaddr, bool is_v6);
व्योम ipvlan_ht_addr_del(काष्ठा ipvl_addr *addr);
काष्ठा ipvl_addr *ipvlan_addr_lookup(काष्ठा ipvl_port *port, व्योम *lyr3h,
				     पूर्णांक addr_type, bool use_dest);
व्योम *ipvlan_get_L3_hdr(काष्ठा ipvl_port *port, काष्ठा sk_buff *skb, पूर्णांक *type);
व्योम ipvlan_count_rx(स्थिर काष्ठा ipvl_dev *ipvlan,
		     अचिन्हित पूर्णांक len, bool success, bool mcast);
पूर्णांक ipvlan_link_new(काष्ठा net *src_net, काष्ठा net_device *dev,
		    काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		    काष्ठा netlink_ext_ack *extack);
व्योम ipvlan_link_delete(काष्ठा net_device *dev, काष्ठा list_head *head);
व्योम ipvlan_link_setup(काष्ठा net_device *dev);
पूर्णांक ipvlan_link_रेजिस्टर(काष्ठा rtnl_link_ops *ops);
#अगर_घोषित CONFIG_IPVLAN_L3S
पूर्णांक ipvlan_l3s_रेजिस्टर(काष्ठा ipvl_port *port);
व्योम ipvlan_l3s_unरेजिस्टर(काष्ठा ipvl_port *port);
व्योम ipvlan_migrate_l3s_hook(काष्ठा net *oldnet, काष्ठा net *newnet);
पूर्णांक ipvlan_l3s_init(व्योम);
व्योम ipvlan_l3s_cleanup(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ipvlan_l3s_रेजिस्टर(काष्ठा ipvl_port *port)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ipvlan_l3s_unरेजिस्टर(काष्ठा ipvl_port *port)
अणु
पूर्ण

अटल अंतरभूत व्योम ipvlan_migrate_l3s_hook(काष्ठा net *oldnet,
					   काष्ठा net *newnet)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ipvlan_l3s_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ipvlan_l3s_cleanup(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_IPVLAN_L3S */

अटल अंतरभूत bool netअगर_is_ipvlan_port(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_access_poपूर्णांकer(dev->rx_handler) == ipvlan_handle_frame;
पूर्ण

#पूर्ण_अगर /* __IPVLAN_H */

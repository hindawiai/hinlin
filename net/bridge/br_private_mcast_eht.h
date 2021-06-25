<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later
 * Copyright (c) 2020, Nikolay Aleksandrov <nikolay@nvidia.com>
 */
#अगर_अघोषित _BR_PRIVATE_MCAST_EHT_H_
#घोषणा _BR_PRIVATE_MCAST_EHT_H_

#घोषणा BR_MCAST_DEFAULT_EHT_HOSTS_LIMIT 512

जोड़ net_bridge_eht_addr अणु
	__be32				ip4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा in6_addr			ip6;
#पूर्ण_अगर
पूर्ण;

/* single host's list of set entries and filter_mode */
काष्ठा net_bridge_group_eht_host अणु
	काष्ठा rb_node			rb_node;

	जोड़ net_bridge_eht_addr	h_addr;
	काष्ठा hlist_head		set_entries;
	अचिन्हित पूर्णांक			num_entries;
	अचिन्हित अक्षर			filter_mode;
	काष्ठा net_bridge_port_group	*pg;
पूर्ण;

/* (host, src entry) added to a per-src set and host's list */
काष्ठा net_bridge_group_eht_set_entry अणु
	काष्ठा rb_node			rb_node;
	काष्ठा hlist_node		host_list;

	जोड़ net_bridge_eht_addr	h_addr;
	काष्ठा समयr_list		समयr;
	काष्ठा net_bridge		*br;
	काष्ठा net_bridge_group_eht_set	*eht_set;
	काष्ठा net_bridge_group_eht_host *h_parent;
	काष्ठा net_bridge_mcast_gc	mcast_gc;
पूर्ण;

/* per-src set */
काष्ठा net_bridge_group_eht_set अणु
	काष्ठा rb_node			rb_node;

	जोड़ net_bridge_eht_addr	src_addr;
	काष्ठा rb_root			entry_tree;
	काष्ठा समयr_list		समयr;
	काष्ठा net_bridge_port_group	*pg;
	काष्ठा net_bridge		*br;
	काष्ठा net_bridge_mcast_gc	mcast_gc;
पूर्ण;

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
व्योम br_multicast_eht_clean_sets(काष्ठा net_bridge_port_group *pg);
bool br_multicast_eht_handle(काष्ठा net_bridge_port_group *pg,
			     व्योम *h_addr,
			     व्योम *srcs,
			     u32 nsrcs,
			     माप_प्रकार addr_size,
			     पूर्णांक grec_type);
पूर्णांक br_multicast_eht_set_hosts_limit(काष्ठा net_bridge_port *p,
				     u32 eht_hosts_limit);

अटल अंतरभूत bool
br_multicast_eht_should_del_pg(स्थिर काष्ठा net_bridge_port_group *pg)
अणु
	वापस !!((pg->key.port->flags & BR_MULTICAST_FAST_LEAVE) &&
		  RB_EMPTY_ROOT(&pg->eht_host_tree));
पूर्ण

अटल अंतरभूत bool
br_multicast_eht_hosts_over_limit(स्थिर काष्ठा net_bridge_port_group *pg)
अणु
	स्थिर काष्ठा net_bridge_port *p = pg->key.port;

	वापस !!(p->multicast_eht_hosts_cnt >= p->multicast_eht_hosts_limit);
पूर्ण

अटल अंतरभूत व्योम br_multicast_eht_hosts_inc(काष्ठा net_bridge_port_group *pg)
अणु
	काष्ठा net_bridge_port *p = pg->key.port;

	p->multicast_eht_hosts_cnt++;
पूर्ण

अटल अंतरभूत व्योम br_multicast_eht_hosts_dec(काष्ठा net_bridge_port_group *pg)
अणु
	काष्ठा net_bridge_port *p = pg->key.port;

	p->multicast_eht_hosts_cnt--;
पूर्ण
#पूर्ण_अगर /* CONFIG_BRIDGE_IGMP_SNOOPING */

#पूर्ण_अगर /* _BR_PRIVATE_MCAST_EHT_H_ */

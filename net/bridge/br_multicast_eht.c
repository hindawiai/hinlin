<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// Copyright (c) 2020, Nikolay Aleksandrov <nikolay@nvidia.com>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/igmp.h>
#समावेश <linux/in.h>
#समावेश <linux/jhash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/mroute.h>
#समावेश <net/ip.h>
#समावेश <net/चयनdev.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/icmpv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/mld.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/addrconf.h>
#पूर्ण_अगर

#समावेश "br_private.h"
#समावेश "br_private_mcast_eht.h"

अटल bool br_multicast_del_eht_set_entry(काष्ठा net_bridge_port_group *pg,
					   जोड़ net_bridge_eht_addr *src_addr,
					   जोड़ net_bridge_eht_addr *h_addr);
अटल व्योम br_multicast_create_eht_set_entry(काष्ठा net_bridge_port_group *pg,
					      जोड़ net_bridge_eht_addr *src_addr,
					      जोड़ net_bridge_eht_addr *h_addr,
					      पूर्णांक filter_mode,
					      bool allow_zero_src);

अटल काष्ठा net_bridge_group_eht_host *
br_multicast_eht_host_lookup(काष्ठा net_bridge_port_group *pg,
			     जोड़ net_bridge_eht_addr *h_addr)
अणु
	काष्ठा rb_node *node = pg->eht_host_tree.rb_node;

	जबतक (node) अणु
		काष्ठा net_bridge_group_eht_host *this;
		पूर्णांक result;

		this = rb_entry(node, काष्ठा net_bridge_group_eht_host,
				rb_node);
		result = स_भेद(h_addr, &this->h_addr, माप(*h_addr));
		अगर (result < 0)
			node = node->rb_left;
		अन्यथा अगर (result > 0)
			node = node->rb_right;
		अन्यथा
			वापस this;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक br_multicast_eht_host_filter_mode(काष्ठा net_bridge_port_group *pg,
					     जोड़ net_bridge_eht_addr *h_addr)
अणु
	काष्ठा net_bridge_group_eht_host *eht_host;

	eht_host = br_multicast_eht_host_lookup(pg, h_addr);
	अगर (!eht_host)
		वापस MCAST_INCLUDE;

	वापस eht_host->filter_mode;
पूर्ण

अटल काष्ठा net_bridge_group_eht_set_entry *
br_multicast_eht_set_entry_lookup(काष्ठा net_bridge_group_eht_set *eht_set,
				  जोड़ net_bridge_eht_addr *h_addr)
अणु
	काष्ठा rb_node *node = eht_set->entry_tree.rb_node;

	जबतक (node) अणु
		काष्ठा net_bridge_group_eht_set_entry *this;
		पूर्णांक result;

		this = rb_entry(node, काष्ठा net_bridge_group_eht_set_entry,
				rb_node);
		result = स_भेद(h_addr, &this->h_addr, माप(*h_addr));
		अगर (result < 0)
			node = node->rb_left;
		अन्यथा अगर (result > 0)
			node = node->rb_right;
		अन्यथा
			वापस this;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा net_bridge_group_eht_set *
br_multicast_eht_set_lookup(काष्ठा net_bridge_port_group *pg,
			    जोड़ net_bridge_eht_addr *src_addr)
अणु
	काष्ठा rb_node *node = pg->eht_set_tree.rb_node;

	जबतक (node) अणु
		काष्ठा net_bridge_group_eht_set *this;
		पूर्णांक result;

		this = rb_entry(node, काष्ठा net_bridge_group_eht_set,
				rb_node);
		result = स_भेद(src_addr, &this->src_addr, माप(*src_addr));
		अगर (result < 0)
			node = node->rb_left;
		अन्यथा अगर (result > 0)
			node = node->rb_right;
		अन्यथा
			वापस this;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __eht_destroy_host(काष्ठा net_bridge_group_eht_host *eht_host)
अणु
	WARN_ON(!hlist_empty(&eht_host->set_entries));

	br_multicast_eht_hosts_dec(eht_host->pg);

	rb_erase(&eht_host->rb_node, &eht_host->pg->eht_host_tree);
	RB_CLEAR_NODE(&eht_host->rb_node);
	kमुक्त(eht_host);
पूर्ण

अटल व्योम br_multicast_destroy_eht_set_entry(काष्ठा net_bridge_mcast_gc *gc)
अणु
	काष्ठा net_bridge_group_eht_set_entry *set_h;

	set_h = container_of(gc, काष्ठा net_bridge_group_eht_set_entry, mcast_gc);
	WARN_ON(!RB_EMPTY_NODE(&set_h->rb_node));

	del_समयr_sync(&set_h->समयr);
	kमुक्त(set_h);
पूर्ण

अटल व्योम br_multicast_destroy_eht_set(काष्ठा net_bridge_mcast_gc *gc)
अणु
	काष्ठा net_bridge_group_eht_set *eht_set;

	eht_set = container_of(gc, काष्ठा net_bridge_group_eht_set, mcast_gc);
	WARN_ON(!RB_EMPTY_NODE(&eht_set->rb_node));
	WARN_ON(!RB_EMPTY_ROOT(&eht_set->entry_tree));

	del_समयr_sync(&eht_set->समयr);
	kमुक्त(eht_set);
पूर्ण

अटल व्योम __eht_del_set_entry(काष्ठा net_bridge_group_eht_set_entry *set_h)
अणु
	काष्ठा net_bridge_group_eht_host *eht_host = set_h->h_parent;
	जोड़ net_bridge_eht_addr zero_addr;

	rb_erase(&set_h->rb_node, &set_h->eht_set->entry_tree);
	RB_CLEAR_NODE(&set_h->rb_node);
	hlist_del_init(&set_h->host_list);
	स_रखो(&zero_addr, 0, माप(zero_addr));
	अगर (स_भेद(&set_h->h_addr, &zero_addr, माप(zero_addr)))
		eht_host->num_entries--;
	hlist_add_head(&set_h->mcast_gc.gc_node, &set_h->br->mcast_gc_list);
	queue_work(प्रणाली_दीर्घ_wq, &set_h->br->mcast_gc_work);

	अगर (hlist_empty(&eht_host->set_entries))
		__eht_destroy_host(eht_host);
पूर्ण

अटल व्योम br_multicast_del_eht_set(काष्ठा net_bridge_group_eht_set *eht_set)
अणु
	काष्ठा net_bridge_group_eht_set_entry *set_h;
	काष्ठा rb_node *node;

	जबतक ((node = rb_first(&eht_set->entry_tree))) अणु
		set_h = rb_entry(node, काष्ठा net_bridge_group_eht_set_entry,
				 rb_node);
		__eht_del_set_entry(set_h);
	पूर्ण

	rb_erase(&eht_set->rb_node, &eht_set->pg->eht_set_tree);
	RB_CLEAR_NODE(&eht_set->rb_node);
	hlist_add_head(&eht_set->mcast_gc.gc_node, &eht_set->br->mcast_gc_list);
	queue_work(प्रणाली_दीर्घ_wq, &eht_set->br->mcast_gc_work);
पूर्ण

व्योम br_multicast_eht_clean_sets(काष्ठा net_bridge_port_group *pg)
अणु
	काष्ठा net_bridge_group_eht_set *eht_set;
	काष्ठा rb_node *node;

	जबतक ((node = rb_first(&pg->eht_set_tree))) अणु
		eht_set = rb_entry(node, काष्ठा net_bridge_group_eht_set,
				   rb_node);
		br_multicast_del_eht_set(eht_set);
	पूर्ण
पूर्ण

अटल व्योम br_multicast_eht_set_entry_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_group_eht_set_entry *set_h = from_समयr(set_h, t, समयr);
	काष्ठा net_bridge *br = set_h->br;

	spin_lock(&br->multicast_lock);
	अगर (RB_EMPTY_NODE(&set_h->rb_node) || समयr_pending(&set_h->समयr))
		जाओ out;

	br_multicast_del_eht_set_entry(set_h->eht_set->pg,
				       &set_h->eht_set->src_addr,
				       &set_h->h_addr);
out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_multicast_eht_set_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_group_eht_set *eht_set = from_समयr(eht_set, t,
							      समयr);
	काष्ठा net_bridge *br = eht_set->br;

	spin_lock(&br->multicast_lock);
	अगर (RB_EMPTY_NODE(&eht_set->rb_node) || समयr_pending(&eht_set->समयr))
		जाओ out;

	br_multicast_del_eht_set(eht_set);
out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल काष्ठा net_bridge_group_eht_host *
__eht_lookup_create_host(काष्ठा net_bridge_port_group *pg,
			 जोड़ net_bridge_eht_addr *h_addr,
			 अचिन्हित अक्षर filter_mode)
अणु
	काष्ठा rb_node **link = &pg->eht_host_tree.rb_node, *parent = शून्य;
	काष्ठा net_bridge_group_eht_host *eht_host;

	जबतक (*link) अणु
		काष्ठा net_bridge_group_eht_host *this;
		पूर्णांक result;

		this = rb_entry(*link, काष्ठा net_bridge_group_eht_host,
				rb_node);
		result = स_भेद(h_addr, &this->h_addr, माप(*h_addr));
		parent = *link;
		अगर (result < 0)
			link = &((*link)->rb_left);
		अन्यथा अगर (result > 0)
			link = &((*link)->rb_right);
		अन्यथा
			वापस this;
	पूर्ण

	अगर (br_multicast_eht_hosts_over_limit(pg))
		वापस शून्य;

	eht_host = kzalloc(माप(*eht_host), GFP_ATOMIC);
	अगर (!eht_host)
		वापस शून्य;

	स_नकल(&eht_host->h_addr, h_addr, माप(*h_addr));
	INIT_HLIST_HEAD(&eht_host->set_entries);
	eht_host->pg = pg;
	eht_host->filter_mode = filter_mode;

	rb_link_node(&eht_host->rb_node, parent, link);
	rb_insert_color(&eht_host->rb_node, &pg->eht_host_tree);

	br_multicast_eht_hosts_inc(pg);

	वापस eht_host;
पूर्ण

अटल काष्ठा net_bridge_group_eht_set_entry *
__eht_lookup_create_set_entry(काष्ठा net_bridge *br,
			      काष्ठा net_bridge_group_eht_set *eht_set,
			      काष्ठा net_bridge_group_eht_host *eht_host,
			      bool allow_zero_src)
अणु
	काष्ठा rb_node **link = &eht_set->entry_tree.rb_node, *parent = शून्य;
	काष्ठा net_bridge_group_eht_set_entry *set_h;

	जबतक (*link) अणु
		काष्ठा net_bridge_group_eht_set_entry *this;
		पूर्णांक result;

		this = rb_entry(*link, काष्ठा net_bridge_group_eht_set_entry,
				rb_node);
		result = स_भेद(&eht_host->h_addr, &this->h_addr,
				माप(जोड़ net_bridge_eht_addr));
		parent = *link;
		अगर (result < 0)
			link = &((*link)->rb_left);
		अन्यथा अगर (result > 0)
			link = &((*link)->rb_right);
		अन्यथा
			वापस this;
	पूर्ण

	/* always allow स्वतः-created zero entry */
	अगर (!allow_zero_src && eht_host->num_entries >= PG_SRC_ENT_LIMIT)
		वापस शून्य;

	set_h = kzalloc(माप(*set_h), GFP_ATOMIC);
	अगर (!set_h)
		वापस शून्य;

	स_नकल(&set_h->h_addr, &eht_host->h_addr,
	       माप(जोड़ net_bridge_eht_addr));
	set_h->mcast_gc.destroy = br_multicast_destroy_eht_set_entry;
	set_h->eht_set = eht_set;
	set_h->h_parent = eht_host;
	set_h->br = br;
	समयr_setup(&set_h->समयr, br_multicast_eht_set_entry_expired, 0);

	hlist_add_head(&set_h->host_list, &eht_host->set_entries);
	rb_link_node(&set_h->rb_node, parent, link);
	rb_insert_color(&set_h->rb_node, &eht_set->entry_tree);
	/* we must not count the स्वतः-created zero entry otherwise we won't be
	 * able to track the full list of PG_SRC_ENT_LIMIT entries
	 */
	अगर (!allow_zero_src)
		eht_host->num_entries++;

	वापस set_h;
पूर्ण

अटल काष्ठा net_bridge_group_eht_set *
__eht_lookup_create_set(काष्ठा net_bridge_port_group *pg,
			जोड़ net_bridge_eht_addr *src_addr)
अणु
	काष्ठा rb_node **link = &pg->eht_set_tree.rb_node, *parent = शून्य;
	काष्ठा net_bridge_group_eht_set *eht_set;

	जबतक (*link) अणु
		काष्ठा net_bridge_group_eht_set *this;
		पूर्णांक result;

		this = rb_entry(*link, काष्ठा net_bridge_group_eht_set,
				rb_node);
		result = स_भेद(src_addr, &this->src_addr, माप(*src_addr));
		parent = *link;
		अगर (result < 0)
			link = &((*link)->rb_left);
		अन्यथा अगर (result > 0)
			link = &((*link)->rb_right);
		अन्यथा
			वापस this;
	पूर्ण

	eht_set = kzalloc(माप(*eht_set), GFP_ATOMIC);
	अगर (!eht_set)
		वापस शून्य;

	स_नकल(&eht_set->src_addr, src_addr, माप(*src_addr));
	eht_set->mcast_gc.destroy = br_multicast_destroy_eht_set;
	eht_set->pg = pg;
	eht_set->br = pg->key.port->br;
	eht_set->entry_tree = RB_ROOT;
	समयr_setup(&eht_set->समयr, br_multicast_eht_set_expired, 0);

	rb_link_node(&eht_set->rb_node, parent, link);
	rb_insert_color(&eht_set->rb_node, &pg->eht_set_tree);

	वापस eht_set;
पूर्ण

अटल व्योम br_multicast_ip_src_to_eht_addr(स्थिर काष्ठा br_ip *src,
					    जोड़ net_bridge_eht_addr *dest)
अणु
	चयन (src->proto) अणु
	हाल htons(ETH_P_IP):
		dest->ip4 = src->src.ip4;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		स_नकल(&dest->ip6, &src->src.ip6, माप(काष्ठा in6_addr));
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम br_eht_convert_host_filter_mode(काष्ठा net_bridge_port_group *pg,
					    जोड़ net_bridge_eht_addr *h_addr,
					    पूर्णांक filter_mode)
अणु
	काष्ठा net_bridge_group_eht_host *eht_host;
	जोड़ net_bridge_eht_addr zero_addr;

	eht_host = br_multicast_eht_host_lookup(pg, h_addr);
	अगर (eht_host)
		eht_host->filter_mode = filter_mode;

	स_रखो(&zero_addr, 0, माप(zero_addr));
	चयन (filter_mode) अणु
	हाल MCAST_INCLUDE:
		br_multicast_del_eht_set_entry(pg, &zero_addr, h_addr);
		अवरोध;
	हाल MCAST_EXCLUDE:
		br_multicast_create_eht_set_entry(pg, &zero_addr, h_addr,
						  MCAST_EXCLUDE,
						  true);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम br_multicast_create_eht_set_entry(काष्ठा net_bridge_port_group *pg,
					      जोड़ net_bridge_eht_addr *src_addr,
					      जोड़ net_bridge_eht_addr *h_addr,
					      पूर्णांक filter_mode,
					      bool allow_zero_src)
अणु
	काष्ठा net_bridge_group_eht_set_entry *set_h;
	काष्ठा net_bridge_group_eht_host *eht_host;
	काष्ठा net_bridge *br = pg->key.port->br;
	काष्ठा net_bridge_group_eht_set *eht_set;
	जोड़ net_bridge_eht_addr zero_addr;

	स_रखो(&zero_addr, 0, माप(zero_addr));
	अगर (!allow_zero_src && !स_भेद(src_addr, &zero_addr, माप(zero_addr)))
		वापस;

	eht_set = __eht_lookup_create_set(pg, src_addr);
	अगर (!eht_set)
		वापस;

	eht_host = __eht_lookup_create_host(pg, h_addr, filter_mode);
	अगर (!eht_host)
		जाओ fail_host;

	set_h = __eht_lookup_create_set_entry(br, eht_set, eht_host,
					      allow_zero_src);
	अगर (!set_h)
		जाओ fail_set_entry;

	mod_समयr(&set_h->समयr, jअगरfies + br_multicast_gmi(br));
	mod_समयr(&eht_set->समयr, jअगरfies + br_multicast_gmi(br));

	वापस;

fail_set_entry:
	अगर (hlist_empty(&eht_host->set_entries))
		__eht_destroy_host(eht_host);
fail_host:
	अगर (RB_EMPTY_ROOT(&eht_set->entry_tree))
		br_multicast_del_eht_set(eht_set);
पूर्ण

अटल bool br_multicast_del_eht_set_entry(काष्ठा net_bridge_port_group *pg,
					   जोड़ net_bridge_eht_addr *src_addr,
					   जोड़ net_bridge_eht_addr *h_addr)
अणु
	काष्ठा net_bridge_group_eht_set_entry *set_h;
	काष्ठा net_bridge_group_eht_set *eht_set;
	bool set_deleted = false;

	eht_set = br_multicast_eht_set_lookup(pg, src_addr);
	अगर (!eht_set)
		जाओ out;

	set_h = br_multicast_eht_set_entry_lookup(eht_set, h_addr);
	अगर (!set_h)
		जाओ out;

	__eht_del_set_entry(set_h);

	अगर (RB_EMPTY_ROOT(&eht_set->entry_tree)) अणु
		br_multicast_del_eht_set(eht_set);
		set_deleted = true;
	पूर्ण

out:
	वापस set_deleted;
पूर्ण

अटल व्योम br_multicast_del_eht_host(काष्ठा net_bridge_port_group *pg,
				      जोड़ net_bridge_eht_addr *h_addr)
अणु
	काष्ठा net_bridge_group_eht_set_entry *set_h;
	काष्ठा net_bridge_group_eht_host *eht_host;
	काष्ठा hlist_node *पंचांगp;

	eht_host = br_multicast_eht_host_lookup(pg, h_addr);
	अगर (!eht_host)
		वापस;

	hlist_क्रम_each_entry_safe(set_h, पंचांगp, &eht_host->set_entries, host_list)
		br_multicast_del_eht_set_entry(set_h->eht_set->pg,
					       &set_h->eht_set->src_addr,
					       &set_h->h_addr);
पूर्ण

/* create new set entries from reports */
अटल व्योम __eht_create_set_entries(काष्ठा net_bridge_port_group *pg,
				     जोड़ net_bridge_eht_addr *h_addr,
				     व्योम *srcs,
				     u32 nsrcs,
				     माप_प्रकार addr_size,
				     पूर्णांक filter_mode)
अणु
	जोड़ net_bridge_eht_addr eht_src_addr;
	u32 src_idx;

	स_रखो(&eht_src_addr, 0, माप(eht_src_addr));
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&eht_src_addr, srcs + (src_idx * addr_size), addr_size);
		br_multicast_create_eht_set_entry(pg, &eht_src_addr, h_addr,
						  filter_mode,
						  false);
	पूर्ण
पूर्ण

/* delete existing set entries and their (S,G) entries अगर they were the last */
अटल bool __eht_del_set_entries(काष्ठा net_bridge_port_group *pg,
				  जोड़ net_bridge_eht_addr *h_addr,
				  व्योम *srcs,
				  u32 nsrcs,
				  माप_प्रकार addr_size)
अणु
	जोड़ net_bridge_eht_addr eht_src_addr;
	काष्ठा net_bridge_group_src *src_ent;
	bool changed = false;
	काष्ठा br_ip src_ip;
	u32 src_idx;

	स_रखो(&eht_src_addr, 0, माप(eht_src_addr));
	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&eht_src_addr, srcs + (src_idx * addr_size), addr_size);
		अगर (!br_multicast_del_eht_set_entry(pg, &eht_src_addr, h_addr))
			जारी;
		स_नकल(&src_ip, srcs + (src_idx * addr_size), addr_size);
		src_ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (!src_ent)
			जारी;
		br_multicast_del_group_src(src_ent, true);
		changed = true;
	पूर्ण

	वापस changed;
पूर्ण

अटल bool br_multicast_eht_allow(काष्ठा net_bridge_port_group *pg,
				   जोड़ net_bridge_eht_addr *h_addr,
				   व्योम *srcs,
				   u32 nsrcs,
				   माप_प्रकार addr_size)
अणु
	bool changed = false;

	चयन (br_multicast_eht_host_filter_mode(pg, h_addr)) अणु
	हाल MCAST_INCLUDE:
		__eht_create_set_entries(pg, h_addr, srcs, nsrcs, addr_size,
					 MCAST_INCLUDE);
		अवरोध;
	हाल MCAST_EXCLUDE:
		changed = __eht_del_set_entries(pg, h_addr, srcs, nsrcs,
						addr_size);
		अवरोध;
	पूर्ण

	वापस changed;
पूर्ण

अटल bool br_multicast_eht_block(काष्ठा net_bridge_port_group *pg,
				   जोड़ net_bridge_eht_addr *h_addr,
				   व्योम *srcs,
				   u32 nsrcs,
				   माप_प्रकार addr_size)
अणु
	bool changed = false;

	चयन (br_multicast_eht_host_filter_mode(pg, h_addr)) अणु
	हाल MCAST_INCLUDE:
		changed = __eht_del_set_entries(pg, h_addr, srcs, nsrcs,
						addr_size);
		अवरोध;
	हाल MCAST_EXCLUDE:
		__eht_create_set_entries(pg, h_addr, srcs, nsrcs, addr_size,
					 MCAST_EXCLUDE);
		अवरोध;
	पूर्ण

	वापस changed;
पूर्ण

/* flush_entries is true when changing mode */
अटल bool __eht_inc_exc(काष्ठा net_bridge_port_group *pg,
			  जोड़ net_bridge_eht_addr *h_addr,
			  व्योम *srcs,
			  u32 nsrcs,
			  माप_प्रकार addr_size,
			  अचिन्हित अक्षर filter_mode,
			  bool to_report)
अणु
	bool changed = false, flush_entries = to_report;
	जोड़ net_bridge_eht_addr eht_src_addr;

	अगर (br_multicast_eht_host_filter_mode(pg, h_addr) != filter_mode)
		flush_entries = true;

	स_रखो(&eht_src_addr, 0, माप(eht_src_addr));
	/* अगर we're changing mode del host and its entries */
	अगर (flush_entries)
		br_multicast_del_eht_host(pg, h_addr);
	__eht_create_set_entries(pg, h_addr, srcs, nsrcs, addr_size,
				 filter_mode);
	/* we can be missing sets only अगर we've deleted some entries */
	अगर (flush_entries) अणु
		काष्ठा net_bridge *br = pg->key.port->br;
		काष्ठा net_bridge_group_eht_set *eht_set;
		काष्ठा net_bridge_group_src *src_ent;
		काष्ठा hlist_node *पंचांगp;

		hlist_क्रम_each_entry_safe(src_ent, पंचांगp, &pg->src_list, node) अणु
			br_multicast_ip_src_to_eht_addr(&src_ent->addr,
							&eht_src_addr);
			अगर (!br_multicast_eht_set_lookup(pg, &eht_src_addr)) अणु
				br_multicast_del_group_src(src_ent, true);
				changed = true;
				जारी;
			पूर्ण
			/* this is an optimization क्रम TO_INCLUDE where we lower
			 * the set's समयout to LMQT to catch समयout hosts:
			 * - host A (timing out): set entries X, Y
			 * - host B: set entry Z (new from current TO_INCLUDE)
			 *           sends BLOCK Z after LMQT but host A's EHT
			 *           entries still exist (unless lowered to LMQT
			 *           so they can समयout with the S,Gs)
			 * => we रुको another LMQT, when we can just delete the
			 *    group immediately
			 */
			अगर (!(src_ent->flags & BR_SGRP_F_SEND) ||
			    filter_mode != MCAST_INCLUDE ||
			    !to_report)
				जारी;
			eht_set = br_multicast_eht_set_lookup(pg,
							      &eht_src_addr);
			अगर (!eht_set)
				जारी;
			mod_समयr(&eht_set->समयr, jअगरfies + br_multicast_lmqt(br));
		पूर्ण
	पूर्ण

	वापस changed;
पूर्ण

अटल bool br_multicast_eht_inc(काष्ठा net_bridge_port_group *pg,
				 जोड़ net_bridge_eht_addr *h_addr,
				 व्योम *srcs,
				 u32 nsrcs,
				 माप_प्रकार addr_size,
				 bool to_report)
अणु
	bool changed;

	changed = __eht_inc_exc(pg, h_addr, srcs, nsrcs, addr_size,
				MCAST_INCLUDE, to_report);
	br_eht_convert_host_filter_mode(pg, h_addr, MCAST_INCLUDE);

	वापस changed;
पूर्ण

अटल bool br_multicast_eht_exc(काष्ठा net_bridge_port_group *pg,
				 जोड़ net_bridge_eht_addr *h_addr,
				 व्योम *srcs,
				 u32 nsrcs,
				 माप_प्रकार addr_size,
				 bool to_report)
अणु
	bool changed;

	changed = __eht_inc_exc(pg, h_addr, srcs, nsrcs, addr_size,
				MCAST_EXCLUDE, to_report);
	br_eht_convert_host_filter_mode(pg, h_addr, MCAST_EXCLUDE);

	वापस changed;
पूर्ण

अटल bool __eht_ip4_handle(काष्ठा net_bridge_port_group *pg,
			     जोड़ net_bridge_eht_addr *h_addr,
			     व्योम *srcs,
			     u32 nsrcs,
			     पूर्णांक grec_type)
अणु
	bool changed = false, to_report = false;

	चयन (grec_type) अणु
	हाल IGMPV3_ALLOW_NEW_SOURCES:
		br_multicast_eht_allow(pg, h_addr, srcs, nsrcs, माप(__be32));
		अवरोध;
	हाल IGMPV3_BLOCK_OLD_SOURCES:
		changed = br_multicast_eht_block(pg, h_addr, srcs, nsrcs,
						 माप(__be32));
		अवरोध;
	हाल IGMPV3_CHANGE_TO_INCLUDE:
		to_report = true;
		fallthrough;
	हाल IGMPV3_MODE_IS_INCLUDE:
		changed = br_multicast_eht_inc(pg, h_addr, srcs, nsrcs,
					       माप(__be32), to_report);
		अवरोध;
	हाल IGMPV3_CHANGE_TO_EXCLUDE:
		to_report = true;
		fallthrough;
	हाल IGMPV3_MODE_IS_EXCLUDE:
		changed = br_multicast_eht_exc(pg, h_addr, srcs, nsrcs,
					       माप(__be32), to_report);
		अवरोध;
	पूर्ण

	वापस changed;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल bool __eht_ip6_handle(काष्ठा net_bridge_port_group *pg,
			     जोड़ net_bridge_eht_addr *h_addr,
			     व्योम *srcs,
			     u32 nsrcs,
			     पूर्णांक grec_type)
अणु
	bool changed = false, to_report = false;

	चयन (grec_type) अणु
	हाल MLD2_ALLOW_NEW_SOURCES:
		br_multicast_eht_allow(pg, h_addr, srcs, nsrcs,
				       माप(काष्ठा in6_addr));
		अवरोध;
	हाल MLD2_BLOCK_OLD_SOURCES:
		changed = br_multicast_eht_block(pg, h_addr, srcs, nsrcs,
						 माप(काष्ठा in6_addr));
		अवरोध;
	हाल MLD2_CHANGE_TO_INCLUDE:
		to_report = true;
		fallthrough;
	हाल MLD2_MODE_IS_INCLUDE:
		changed = br_multicast_eht_inc(pg, h_addr, srcs, nsrcs,
					       माप(काष्ठा in6_addr),
					       to_report);
		अवरोध;
	हाल MLD2_CHANGE_TO_EXCLUDE:
		to_report = true;
		fallthrough;
	हाल MLD2_MODE_IS_EXCLUDE:
		changed = br_multicast_eht_exc(pg, h_addr, srcs, nsrcs,
					       माप(काष्ठा in6_addr),
					       to_report);
		अवरोध;
	पूर्ण

	वापस changed;
पूर्ण
#पूर्ण_अगर

/* true means an entry was deleted */
bool br_multicast_eht_handle(काष्ठा net_bridge_port_group *pg,
			     व्योम *h_addr,
			     व्योम *srcs,
			     u32 nsrcs,
			     माप_प्रकार addr_size,
			     पूर्णांक grec_type)
अणु
	bool eht_enabled = !!(pg->key.port->flags & BR_MULTICAST_FAST_LEAVE);
	जोड़ net_bridge_eht_addr eht_host_addr;
	bool changed = false;

	अगर (!eht_enabled)
		जाओ out;

	स_रखो(&eht_host_addr, 0, माप(eht_host_addr));
	स_नकल(&eht_host_addr, h_addr, addr_size);
	अगर (addr_size == माप(__be32))
		changed = __eht_ip4_handle(pg, &eht_host_addr, srcs, nsrcs,
					   grec_type);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		changed = __eht_ip6_handle(pg, &eht_host_addr, srcs, nsrcs,
					   grec_type);
#पूर्ण_अगर

out:
	वापस changed;
पूर्ण

पूर्णांक br_multicast_eht_set_hosts_limit(काष्ठा net_bridge_port *p,
				     u32 eht_hosts_limit)
अणु
	काष्ठा net_bridge *br = p->br;

	अगर (!eht_hosts_limit)
		वापस -EINVAL;

	spin_lock_bh(&br->multicast_lock);
	p->multicast_eht_hosts_limit = eht_hosts_limit;
	spin_unlock_bh(&br->multicast_lock);

	वापस 0;
पूर्ण

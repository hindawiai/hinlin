<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Bridge multicast support.
 *
 * Copyright (c) 2010 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

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

अटल स्थिर काष्ठा rhashtable_params br_mdb_rht_params = अणु
	.head_offset = दुरत्व(काष्ठा net_bridge_mdb_entry, rhnode),
	.key_offset = दुरत्व(काष्ठा net_bridge_mdb_entry, addr),
	.key_len = माप(काष्ठा br_ip),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params br_sg_port_rht_params = अणु
	.head_offset = दुरत्व(काष्ठा net_bridge_port_group, rhnode),
	.key_offset = दुरत्व(काष्ठा net_bridge_port_group, key),
	.key_len = माप(काष्ठा net_bridge_port_group_sg_key),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल व्योम br_multicast_start_querier(काष्ठा net_bridge *br,
				       काष्ठा bridge_mcast_own_query *query);
अटल व्योम br_multicast_add_router(काष्ठा net_bridge *br,
				    काष्ठा net_bridge_port *port);
अटल व्योम br_ip4_multicast_leave_group(काष्ठा net_bridge *br,
					 काष्ठा net_bridge_port *port,
					 __be32 group,
					 __u16 vid,
					 स्थिर अचिन्हित अक्षर *src);
अटल व्योम br_multicast_port_group_rexmit(काष्ठा समयr_list *t);

अटल व्योम __del_port_router(काष्ठा net_bridge_port *p);
#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम br_ip6_multicast_leave_group(काष्ठा net_bridge *br,
					 काष्ठा net_bridge_port *port,
					 स्थिर काष्ठा in6_addr *group,
					 __u16 vid, स्थिर अचिन्हित अक्षर *src);
#पूर्ण_अगर
अटल काष्ठा net_bridge_port_group *
__br_multicast_add_group(काष्ठा net_bridge *br,
			 काष्ठा net_bridge_port *port,
			 काष्ठा br_ip *group,
			 स्थिर अचिन्हित अक्षर *src,
			 u8 filter_mode,
			 bool igmpv2_mldv1,
			 bool blocked);
अटल व्योम br_multicast_find_del_pg(काष्ठा net_bridge *br,
				     काष्ठा net_bridge_port_group *pg);

अटल काष्ठा net_bridge_port_group *
br_sg_port_find(काष्ठा net_bridge *br,
		काष्ठा net_bridge_port_group_sg_key *sg_p)
अणु
	lockdep_निश्चित_held_once(&br->multicast_lock);

	वापस rhashtable_lookup_fast(&br->sg_port_tbl, sg_p,
				      br_sg_port_rht_params);
पूर्ण

अटल काष्ठा net_bridge_mdb_entry *br_mdb_ip_get_rcu(काष्ठा net_bridge *br,
						      काष्ठा br_ip *dst)
अणु
	वापस rhashtable_lookup(&br->mdb_hash_tbl, dst, br_mdb_rht_params);
पूर्ण

काष्ठा net_bridge_mdb_entry *br_mdb_ip_get(काष्ठा net_bridge *br,
					   काष्ठा br_ip *dst)
अणु
	काष्ठा net_bridge_mdb_entry *ent;

	lockdep_निश्चित_held_once(&br->multicast_lock);

	rcu_पढ़ो_lock();
	ent = rhashtable_lookup(&br->mdb_hash_tbl, dst, br_mdb_rht_params);
	rcu_पढ़ो_unlock();

	वापस ent;
पूर्ण

अटल काष्ठा net_bridge_mdb_entry *br_mdb_ip4_get(काष्ठा net_bridge *br,
						   __be32 dst, __u16 vid)
अणु
	काष्ठा br_ip br_dst;

	स_रखो(&br_dst, 0, माप(br_dst));
	br_dst.dst.ip4 = dst;
	br_dst.proto = htons(ETH_P_IP);
	br_dst.vid = vid;

	वापस br_mdb_ip_get(br, &br_dst);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा net_bridge_mdb_entry *br_mdb_ip6_get(काष्ठा net_bridge *br,
						   स्थिर काष्ठा in6_addr *dst,
						   __u16 vid)
अणु
	काष्ठा br_ip br_dst;

	स_रखो(&br_dst, 0, माप(br_dst));
	br_dst.dst.ip6 = *dst;
	br_dst.proto = htons(ETH_P_IPV6);
	br_dst.vid = vid;

	वापस br_mdb_ip_get(br, &br_dst);
पूर्ण
#पूर्ण_अगर

काष्ठा net_bridge_mdb_entry *br_mdb_get(काष्ठा net_bridge *br,
					काष्ठा sk_buff *skb, u16 vid)
अणु
	काष्ठा br_ip ip;

	अगर (!br_opt_get(br, BROPT_MULTICAST_ENABLED))
		वापस शून्य;

	अगर (BR_INPUT_SKB_CB(skb)->igmp)
		वापस शून्य;

	स_रखो(&ip, 0, माप(ip));
	ip.proto = skb->protocol;
	ip.vid = vid;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		ip.dst.ip4 = ip_hdr(skb)->daddr;
		अगर (br->multicast_igmp_version == 3) अणु
			काष्ठा net_bridge_mdb_entry *mdb;

			ip.src.ip4 = ip_hdr(skb)->saddr;
			mdb = br_mdb_ip_get_rcu(br, &ip);
			अगर (mdb)
				वापस mdb;
			ip.src.ip4 = 0;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		ip.dst.ip6 = ipv6_hdr(skb)->daddr;
		अगर (br->multicast_mld_version == 2) अणु
			काष्ठा net_bridge_mdb_entry *mdb;

			ip.src.ip6 = ipv6_hdr(skb)->saddr;
			mdb = br_mdb_ip_get_rcu(br, &ip);
			अगर (mdb)
				वापस mdb;
			स_रखो(&ip.src.ip6, 0, माप(ip.src.ip6));
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		ip.proto = 0;
		ether_addr_copy(ip.dst.mac_addr, eth_hdr(skb)->h_dest);
	पूर्ण

	वापस br_mdb_ip_get_rcu(br, &ip);
पूर्ण

अटल bool br_port_group_equal(काष्ठा net_bridge_port_group *p,
				काष्ठा net_bridge_port *port,
				स्थिर अचिन्हित अक्षर *src)
अणु
	अगर (p->key.port != port)
		वापस false;

	अगर (!(port->flags & BR_MULTICAST_TO_UNICAST))
		वापस true;

	वापस ether_addr_equal(src, p->eth_addr);
पूर्ण

अटल व्योम __fwd_add_star_excl(काष्ठा net_bridge_port_group *pg,
				काष्ठा br_ip *sg_ip)
अणु
	काष्ठा net_bridge_port_group_sg_key sg_key;
	काष्ठा net_bridge *br = pg->key.port->br;
	काष्ठा net_bridge_port_group *src_pg;

	स_रखो(&sg_key, 0, माप(sg_key));
	sg_key.port = pg->key.port;
	sg_key.addr = *sg_ip;
	अगर (br_sg_port_find(br, &sg_key))
		वापस;

	src_pg = __br_multicast_add_group(br, pg->key.port, sg_ip, pg->eth_addr,
					  MCAST_INCLUDE, false, false);
	अगर (IS_ERR_OR_शून्य(src_pg) ||
	    src_pg->rt_protocol != RTPROT_KERNEL)
		वापस;

	src_pg->flags |= MDB_PG_FLAGS_STAR_EXCL;
पूर्ण

अटल व्योम __fwd_del_star_excl(काष्ठा net_bridge_port_group *pg,
				काष्ठा br_ip *sg_ip)
अणु
	काष्ठा net_bridge_port_group_sg_key sg_key;
	काष्ठा net_bridge *br = pg->key.port->br;
	काष्ठा net_bridge_port_group *src_pg;

	स_रखो(&sg_key, 0, माप(sg_key));
	sg_key.port = pg->key.port;
	sg_key.addr = *sg_ip;
	src_pg = br_sg_port_find(br, &sg_key);
	अगर (!src_pg || !(src_pg->flags & MDB_PG_FLAGS_STAR_EXCL) ||
	    src_pg->rt_protocol != RTPROT_KERNEL)
		वापस;

	br_multicast_find_del_pg(br, src_pg);
पूर्ण

/* When a port group transitions to (or is added as) EXCLUDE we need to add it
 * to all other ports' S,G entries which are not blocked by the current group
 * क्रम proper replication, the assumption is that any S,G blocked entries
 * are alपढ़ोy added so the S,G,port lookup should skip them.
 * When a port group transitions from EXCLUDE -> INCLUDE mode or is being
 * deleted we need to हटाओ it from all ports' S,G entries where it was
 * स्वतःmatically installed beक्रमe (i.e. where it's MDB_PG_FLAGS_STAR_EXCL).
 */
व्योम br_multicast_star_g_handle_mode(काष्ठा net_bridge_port_group *pg,
				     u8 filter_mode)
अणु
	काष्ठा net_bridge *br = pg->key.port->br;
	काष्ठा net_bridge_port_group *pg_lst;
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा br_ip sg_ip;

	अगर (WARN_ON(!br_multicast_is_star_g(&pg->key.addr)))
		वापस;

	mp = br_mdb_ip_get(br, &pg->key.addr);
	अगर (!mp)
		वापस;

	स_रखो(&sg_ip, 0, माप(sg_ip));
	sg_ip = pg->key.addr;
	क्रम (pg_lst = mlock_dereference(mp->ports, br);
	     pg_lst;
	     pg_lst = mlock_dereference(pg_lst->next, br)) अणु
		काष्ठा net_bridge_group_src *src_ent;

		अगर (pg_lst == pg)
			जारी;
		hlist_क्रम_each_entry(src_ent, &pg_lst->src_list, node) अणु
			अगर (!(src_ent->flags & BR_SGRP_F_INSTALLED))
				जारी;
			sg_ip.src = src_ent->addr.src;
			चयन (filter_mode) अणु
			हाल MCAST_INCLUDE:
				__fwd_del_star_excl(pg, &sg_ip);
				अवरोध;
			हाल MCAST_EXCLUDE:
				__fwd_add_star_excl(pg, &sg_ip);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* called when adding a new S,G with host_joined == false by शेष */
अटल व्योम br_multicast_sg_host_state(काष्ठा net_bridge_mdb_entry *star_mp,
				       काष्ठा net_bridge_port_group *sg)
अणु
	काष्ठा net_bridge_mdb_entry *sg_mp;

	अगर (WARN_ON(!br_multicast_is_star_g(&star_mp->addr)))
		वापस;
	अगर (!star_mp->host_joined)
		वापस;

	sg_mp = br_mdb_ip_get(star_mp->br, &sg->key.addr);
	अगर (!sg_mp)
		वापस;
	sg_mp->host_joined = true;
पूर्ण

/* set the host_joined state of all of *,G's S,G entries */
अटल व्योम br_multicast_star_g_host_state(काष्ठा net_bridge_mdb_entry *star_mp)
अणु
	काष्ठा net_bridge *br = star_mp->br;
	काष्ठा net_bridge_mdb_entry *sg_mp;
	काष्ठा net_bridge_port_group *pg;
	काष्ठा br_ip sg_ip;

	अगर (WARN_ON(!br_multicast_is_star_g(&star_mp->addr)))
		वापस;

	स_रखो(&sg_ip, 0, माप(sg_ip));
	sg_ip = star_mp->addr;
	क्रम (pg = mlock_dereference(star_mp->ports, br);
	     pg;
	     pg = mlock_dereference(pg->next, br)) अणु
		काष्ठा net_bridge_group_src *src_ent;

		hlist_क्रम_each_entry(src_ent, &pg->src_list, node) अणु
			अगर (!(src_ent->flags & BR_SGRP_F_INSTALLED))
				जारी;
			sg_ip.src = src_ent->addr.src;
			sg_mp = br_mdb_ip_get(br, &sg_ip);
			अगर (!sg_mp)
				जारी;
			sg_mp->host_joined = star_mp->host_joined;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम br_multicast_sg_del_exclude_ports(काष्ठा net_bridge_mdb_entry *sgmp)
अणु
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा net_bridge_port_group *p;

	/* *,G exclude ports are only added to S,G entries */
	अगर (WARN_ON(br_multicast_is_star_g(&sgmp->addr)))
		वापस;

	/* we need the STAR_EXCLUDE ports अगर there are non-STAR_EXCLUDE ports
	 * we should ignore perm entries since they're managed by user-space
	 */
	क्रम (pp = &sgmp->ports;
	     (p = mlock_dereference(*pp, sgmp->br)) != शून्य;
	     pp = &p->next)
		अगर (!(p->flags & (MDB_PG_FLAGS_STAR_EXCL |
				  MDB_PG_FLAGS_PERMANENT)))
			वापस;

	/* currently the host can only have joined the *,G which means
	 * we treat it as EXCLUDE अणुपूर्ण, so क्रम an S,G it's considered a
	 * STAR_EXCLUDE entry and we can safely leave it
	 */
	sgmp->host_joined = false;

	क्रम (pp = &sgmp->ports;
	     (p = mlock_dereference(*pp, sgmp->br)) != शून्य;) अणु
		अगर (!(p->flags & MDB_PG_FLAGS_PERMANENT))
			br_multicast_del_pg(sgmp, p, pp);
		अन्यथा
			pp = &p->next;
	पूर्ण
पूर्ण

व्योम br_multicast_sg_add_exclude_ports(काष्ठा net_bridge_mdb_entry *star_mp,
				       काष्ठा net_bridge_port_group *sg)
अणु
	काष्ठा net_bridge_port_group_sg_key sg_key;
	काष्ठा net_bridge *br = star_mp->br;
	काष्ठा net_bridge_port_group *pg;

	अगर (WARN_ON(br_multicast_is_star_g(&sg->key.addr)))
		वापस;
	अगर (WARN_ON(!br_multicast_is_star_g(&star_mp->addr)))
		वापस;

	br_multicast_sg_host_state(star_mp, sg);
	स_रखो(&sg_key, 0, माप(sg_key));
	sg_key.addr = sg->key.addr;
	/* we need to add all exclude ports to the S,G */
	क्रम (pg = mlock_dereference(star_mp->ports, br);
	     pg;
	     pg = mlock_dereference(pg->next, br)) अणु
		काष्ठा net_bridge_port_group *src_pg;

		अगर (pg == sg || pg->filter_mode == MCAST_INCLUDE)
			जारी;

		sg_key.port = pg->key.port;
		अगर (br_sg_port_find(br, &sg_key))
			जारी;

		src_pg = __br_multicast_add_group(br, pg->key.port,
						  &sg->key.addr,
						  sg->eth_addr,
						  MCAST_INCLUDE, false, false);
		अगर (IS_ERR_OR_शून्य(src_pg) ||
		    src_pg->rt_protocol != RTPROT_KERNEL)
			जारी;
		src_pg->flags |= MDB_PG_FLAGS_STAR_EXCL;
	पूर्ण
पूर्ण

अटल व्योम br_multicast_fwd_src_add(काष्ठा net_bridge_group_src *src)
अणु
	काष्ठा net_bridge_mdb_entry *star_mp;
	काष्ठा net_bridge_port_group *sg;
	काष्ठा br_ip sg_ip;

	अगर (src->flags & BR_SGRP_F_INSTALLED)
		वापस;

	स_रखो(&sg_ip, 0, माप(sg_ip));
	sg_ip = src->pg->key.addr;
	sg_ip.src = src->addr.src;
	sg = __br_multicast_add_group(src->br, src->pg->key.port, &sg_ip,
				      src->pg->eth_addr, MCAST_INCLUDE, false,
				      !समयr_pending(&src->समयr));
	अगर (IS_ERR_OR_शून्य(sg))
		वापस;
	src->flags |= BR_SGRP_F_INSTALLED;
	sg->flags &= ~MDB_PG_FLAGS_STAR_EXCL;

	/* अगर it was added by user-space as perm we can skip next steps */
	अगर (sg->rt_protocol != RTPROT_KERNEL &&
	    (sg->flags & MDB_PG_FLAGS_PERMANENT))
		वापस;

	/* the kernel is now responsible क्रम removing this S,G */
	del_समयr(&sg->समयr);
	star_mp = br_mdb_ip_get(src->br, &src->pg->key.addr);
	अगर (!star_mp)
		वापस;

	br_multicast_sg_add_exclude_ports(star_mp, sg);
पूर्ण

अटल व्योम br_multicast_fwd_src_हटाओ(काष्ठा net_bridge_group_src *src,
					bool fastleave)
अणु
	काष्ठा net_bridge_port_group *p, *pg = src->pg;
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा br_ip sg_ip;

	स_रखो(&sg_ip, 0, माप(sg_ip));
	sg_ip = pg->key.addr;
	sg_ip.src = src->addr.src;

	mp = br_mdb_ip_get(src->br, &sg_ip);
	अगर (!mp)
		वापस;

	क्रम (pp = &mp->ports;
	     (p = mlock_dereference(*pp, src->br)) != शून्य;
	     pp = &p->next) अणु
		अगर (!br_port_group_equal(p, pg->key.port, pg->eth_addr))
			जारी;

		अगर (p->rt_protocol != RTPROT_KERNEL &&
		    (p->flags & MDB_PG_FLAGS_PERMANENT))
			अवरोध;

		अगर (fastleave)
			p->flags |= MDB_PG_FLAGS_FAST_LEAVE;
		br_multicast_del_pg(mp, p, pp);
		अवरोध;
	पूर्ण
	src->flags &= ~BR_SGRP_F_INSTALLED;
पूर्ण

/* install S,G and based on src's समयr enable or disable क्रमwarding */
अटल व्योम br_multicast_fwd_src_handle(काष्ठा net_bridge_group_src *src)
अणु
	काष्ठा net_bridge_port_group_sg_key sg_key;
	काष्ठा net_bridge_port_group *sg;
	u8 old_flags;

	br_multicast_fwd_src_add(src);

	स_रखो(&sg_key, 0, माप(sg_key));
	sg_key.addr = src->pg->key.addr;
	sg_key.addr.src = src->addr.src;
	sg_key.port = src->pg->key.port;

	sg = br_sg_port_find(src->br, &sg_key);
	अगर (!sg || (sg->flags & MDB_PG_FLAGS_PERMANENT))
		वापस;

	old_flags = sg->flags;
	अगर (समयr_pending(&src->समयr))
		sg->flags &= ~MDB_PG_FLAGS_BLOCKED;
	अन्यथा
		sg->flags |= MDB_PG_FLAGS_BLOCKED;

	अगर (old_flags != sg->flags) अणु
		काष्ठा net_bridge_mdb_entry *sg_mp;

		sg_mp = br_mdb_ip_get(src->br, &sg_key.addr);
		अगर (!sg_mp)
			वापस;
		br_mdb_notअगरy(src->br->dev, sg_mp, sg, RTM_NEWMDB);
	पूर्ण
पूर्ण

अटल व्योम br_multicast_destroy_mdb_entry(काष्ठा net_bridge_mcast_gc *gc)
अणु
	काष्ठा net_bridge_mdb_entry *mp;

	mp = container_of(gc, काष्ठा net_bridge_mdb_entry, mcast_gc);
	WARN_ON(!hlist_unhashed(&mp->mdb_node));
	WARN_ON(mp->ports);

	del_समयr_sync(&mp->समयr);
	kमुक्त_rcu(mp, rcu);
पूर्ण

अटल व्योम br_multicast_del_mdb_entry(काष्ठा net_bridge_mdb_entry *mp)
अणु
	काष्ठा net_bridge *br = mp->br;

	rhashtable_हटाओ_fast(&br->mdb_hash_tbl, &mp->rhnode,
			       br_mdb_rht_params);
	hlist_del_init_rcu(&mp->mdb_node);
	hlist_add_head(&mp->mcast_gc.gc_node, &br->mcast_gc_list);
	queue_work(प्रणाली_दीर्घ_wq, &br->mcast_gc_work);
पूर्ण

अटल व्योम br_multicast_group_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_mdb_entry *mp = from_समयr(mp, t, समयr);
	काष्ठा net_bridge *br = mp->br;

	spin_lock(&br->multicast_lock);
	अगर (hlist_unhashed(&mp->mdb_node) || !netअगर_running(br->dev) ||
	    समयr_pending(&mp->समयr))
		जाओ out;

	br_multicast_host_leave(mp, true);

	अगर (mp->ports)
		जाओ out;
	br_multicast_del_mdb_entry(mp);
out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_multicast_destroy_group_src(काष्ठा net_bridge_mcast_gc *gc)
अणु
	काष्ठा net_bridge_group_src *src;

	src = container_of(gc, काष्ठा net_bridge_group_src, mcast_gc);
	WARN_ON(!hlist_unhashed(&src->node));

	del_समयr_sync(&src->समयr);
	kमुक्त_rcu(src, rcu);
पूर्ण

व्योम br_multicast_del_group_src(काष्ठा net_bridge_group_src *src,
				bool fastleave)
अणु
	काष्ठा net_bridge *br = src->pg->key.port->br;

	br_multicast_fwd_src_हटाओ(src, fastleave);
	hlist_del_init_rcu(&src->node);
	src->pg->src_ents--;
	hlist_add_head(&src->mcast_gc.gc_node, &br->mcast_gc_list);
	queue_work(प्रणाली_दीर्घ_wq, &br->mcast_gc_work);
पूर्ण

अटल व्योम br_multicast_destroy_port_group(काष्ठा net_bridge_mcast_gc *gc)
अणु
	काष्ठा net_bridge_port_group *pg;

	pg = container_of(gc, काष्ठा net_bridge_port_group, mcast_gc);
	WARN_ON(!hlist_unhashed(&pg->mglist));
	WARN_ON(!hlist_empty(&pg->src_list));

	del_समयr_sync(&pg->rexmit_समयr);
	del_समयr_sync(&pg->समयr);
	kमुक्त_rcu(pg, rcu);
पूर्ण

व्योम br_multicast_del_pg(काष्ठा net_bridge_mdb_entry *mp,
			 काष्ठा net_bridge_port_group *pg,
			 काष्ठा net_bridge_port_group __rcu **pp)
अणु
	काष्ठा net_bridge *br = pg->key.port->br;
	काष्ठा net_bridge_group_src *ent;
	काष्ठा hlist_node *पंचांगp;

	rcu_assign_poपूर्णांकer(*pp, pg->next);
	hlist_del_init(&pg->mglist);
	br_multicast_eht_clean_sets(pg);
	hlist_क्रम_each_entry_safe(ent, पंचांगp, &pg->src_list, node)
		br_multicast_del_group_src(ent, false);
	br_mdb_notअगरy(br->dev, mp, pg, RTM_DELMDB);
	अगर (!br_multicast_is_star_g(&mp->addr)) अणु
		rhashtable_हटाओ_fast(&br->sg_port_tbl, &pg->rhnode,
				       br_sg_port_rht_params);
		br_multicast_sg_del_exclude_ports(mp);
	पूर्ण अन्यथा अणु
		br_multicast_star_g_handle_mode(pg, MCAST_INCLUDE);
	पूर्ण
	hlist_add_head(&pg->mcast_gc.gc_node, &br->mcast_gc_list);
	queue_work(प्रणाली_दीर्घ_wq, &br->mcast_gc_work);

	अगर (!mp->ports && !mp->host_joined && netअगर_running(br->dev))
		mod_समयr(&mp->समयr, jअगरfies);
पूर्ण

अटल व्योम br_multicast_find_del_pg(काष्ठा net_bridge *br,
				     काष्ठा net_bridge_port_group *pg)
अणु
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा net_bridge_port_group *p;

	mp = br_mdb_ip_get(br, &pg->key.addr);
	अगर (WARN_ON(!mp))
		वापस;

	क्रम (pp = &mp->ports;
	     (p = mlock_dereference(*pp, br)) != शून्य;
	     pp = &p->next) अणु
		अगर (p != pg)
			जारी;

		br_multicast_del_pg(mp, pg, pp);
		वापस;
	पूर्ण

	WARN_ON(1);
पूर्ण

अटल व्योम br_multicast_port_group_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_port_group *pg = from_समयr(pg, t, समयr);
	काष्ठा net_bridge_group_src *src_ent;
	काष्ठा net_bridge *br = pg->key.port->br;
	काष्ठा hlist_node *पंचांगp;
	bool changed;

	spin_lock(&br->multicast_lock);
	अगर (!netअगर_running(br->dev) || समयr_pending(&pg->समयr) ||
	    hlist_unhashed(&pg->mglist) || pg->flags & MDB_PG_FLAGS_PERMANENT)
		जाओ out;

	changed = !!(pg->filter_mode == MCAST_EXCLUDE);
	pg->filter_mode = MCAST_INCLUDE;
	hlist_क्रम_each_entry_safe(src_ent, पंचांगp, &pg->src_list, node) अणु
		अगर (!समयr_pending(&src_ent->समयr)) अणु
			br_multicast_del_group_src(src_ent, false);
			changed = true;
		पूर्ण
	पूर्ण

	अगर (hlist_empty(&pg->src_list)) अणु
		br_multicast_find_del_pg(br, pg);
	पूर्ण अन्यथा अगर (changed) अणु
		काष्ठा net_bridge_mdb_entry *mp = br_mdb_ip_get(br, &pg->key.addr);

		अगर (changed && br_multicast_is_star_g(&pg->key.addr))
			br_multicast_star_g_handle_mode(pg, MCAST_INCLUDE);

		अगर (WARN_ON(!mp))
			जाओ out;
		br_mdb_notअगरy(br->dev, mp, pg, RTM_NEWMDB);
	पूर्ण
out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_multicast_gc(काष्ठा hlist_head *head)
अणु
	काष्ठा net_bridge_mcast_gc *gcent;
	काष्ठा hlist_node *पंचांगp;

	hlist_क्रम_each_entry_safe(gcent, पंचांगp, head, gc_node) अणु
		hlist_del_init(&gcent->gc_node);
		gcent->destroy(gcent);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *br_ip4_multicast_alloc_query(काष्ठा net_bridge *br,
						    काष्ठा net_bridge_port_group *pg,
						    __be32 ip_dst, __be32 group,
						    bool with_srcs, bool over_lmqt,
						    u8 sflag, u8 *igmp_type,
						    bool *need_rexmit)
अणु
	काष्ठा net_bridge_port *p = pg ? pg->key.port : शून्य;
	काष्ठा net_bridge_group_src *ent;
	माप_प्रकार pkt_size, igmp_hdr_size;
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा igmpv3_query *ihv3;
	व्योम *csum_start = शून्य;
	__sum16 *csum = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा igmphdr *ih;
	काष्ठा ethhdr *eth;
	अचिन्हित दीर्घ lmqt;
	काष्ठा iphdr *iph;
	u16 lmqt_srcs = 0;

	igmp_hdr_size = माप(*ih);
	अगर (br->multicast_igmp_version == 3) अणु
		igmp_hdr_size = माप(*ihv3);
		अगर (pg && with_srcs) अणु
			lmqt = now + (br->multicast_last_member_पूर्णांकerval *
				      br->multicast_last_member_count);
			hlist_क्रम_each_entry(ent, &pg->src_list, node) अणु
				अगर (over_lmqt == समय_after(ent->समयr.expires,
							    lmqt) &&
				    ent->src_query_rexmit_cnt > 0)
					lmqt_srcs++;
			पूर्ण

			अगर (!lmqt_srcs)
				वापस शून्य;
			igmp_hdr_size += lmqt_srcs * माप(__be32);
		पूर्ण
	पूर्ण

	pkt_size = माप(*eth) + माप(*iph) + 4 + igmp_hdr_size;
	अगर ((p && pkt_size > p->dev->mtu) ||
	    pkt_size > br->dev->mtu)
		वापस शून्य;

	skb = netdev_alloc_skb_ip_align(br->dev, pkt_size);
	अगर (!skb)
		जाओ out;

	skb->protocol = htons(ETH_P_IP);

	skb_reset_mac_header(skb);
	eth = eth_hdr(skb);

	ether_addr_copy(eth->h_source, br->dev->dev_addr);
	ip_eth_mc_map(ip_dst, eth->h_dest);
	eth->h_proto = htons(ETH_P_IP);
	skb_put(skb, माप(*eth));

	skb_set_network_header(skb, skb->len);
	iph = ip_hdr(skb);
	iph->tot_len = htons(pkt_size - माप(*eth));

	iph->version = 4;
	iph->ihl = 6;
	iph->tos = 0xc0;
	iph->id = 0;
	iph->frag_off = htons(IP_DF);
	iph->ttl = 1;
	iph->protocol = IPPROTO_IGMP;
	iph->saddr = br_opt_get(br, BROPT_MULTICAST_QUERY_USE_IFADDR) ?
		     inet_select_addr(br->dev, 0, RT_SCOPE_LINK) : 0;
	iph->daddr = ip_dst;
	((u8 *)&iph[1])[0] = IPOPT_RA;
	((u8 *)&iph[1])[1] = 4;
	((u8 *)&iph[1])[2] = 0;
	((u8 *)&iph[1])[3] = 0;
	ip_send_check(iph);
	skb_put(skb, 24);

	skb_set_transport_header(skb, skb->len);
	*igmp_type = IGMP_HOST_MEMBERSHIP_QUERY;

	चयन (br->multicast_igmp_version) अणु
	हाल 2:
		ih = igmp_hdr(skb);
		ih->type = IGMP_HOST_MEMBERSHIP_QUERY;
		ih->code = (group ? br->multicast_last_member_पूर्णांकerval :
				    br->multicast_query_response_पूर्णांकerval) /
			   (HZ / IGMP_TIMER_SCALE);
		ih->group = group;
		ih->csum = 0;
		csum = &ih->csum;
		csum_start = (व्योम *)ih;
		अवरोध;
	हाल 3:
		ihv3 = igmpv3_query_hdr(skb);
		ihv3->type = IGMP_HOST_MEMBERSHIP_QUERY;
		ihv3->code = (group ? br->multicast_last_member_पूर्णांकerval :
				      br->multicast_query_response_पूर्णांकerval) /
			     (HZ / IGMP_TIMER_SCALE);
		ihv3->group = group;
		ihv3->qqic = br->multicast_query_पूर्णांकerval / HZ;
		ihv3->nsrcs = htons(lmqt_srcs);
		ihv3->resv = 0;
		ihv3->suppress = sflag;
		ihv3->qrv = 2;
		ihv3->csum = 0;
		csum = &ihv3->csum;
		csum_start = (व्योम *)ihv3;
		अगर (!pg || !with_srcs)
			अवरोध;

		lmqt_srcs = 0;
		hlist_क्रम_each_entry(ent, &pg->src_list, node) अणु
			अगर (over_lmqt == समय_after(ent->समयr.expires,
						    lmqt) &&
			    ent->src_query_rexmit_cnt > 0) अणु
				ihv3->srcs[lmqt_srcs++] = ent->addr.src.ip4;
				ent->src_query_rexmit_cnt--;
				अगर (need_rexmit && ent->src_query_rexmit_cnt)
					*need_rexmit = true;
			पूर्ण
		पूर्ण
		अगर (WARN_ON(lmqt_srcs != ntohs(ihv3->nsrcs))) अणु
			kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (WARN_ON(!csum || !csum_start)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	*csum = ip_compute_csum(csum_start, igmp_hdr_size);
	skb_put(skb, igmp_hdr_size);
	__skb_pull(skb, माप(*eth));

out:
	वापस skb;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा sk_buff *br_ip6_multicast_alloc_query(काष्ठा net_bridge *br,
						    काष्ठा net_bridge_port_group *pg,
						    स्थिर काष्ठा in6_addr *ip6_dst,
						    स्थिर काष्ठा in6_addr *group,
						    bool with_srcs, bool over_llqt,
						    u8 sflag, u8 *igmp_type,
						    bool *need_rexmit)
अणु
	काष्ठा net_bridge_port *p = pg ? pg->key.port : शून्य;
	काष्ठा net_bridge_group_src *ent;
	माप_प्रकार pkt_size, mld_hdr_size;
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा mld2_query *mld2q;
	व्योम *csum_start = शून्य;
	अचिन्हित दीर्घ पूर्णांकerval;
	__sum16 *csum = शून्य;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा mld_msg *mldq;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ llqt;
	काष्ठा ethhdr *eth;
	u16 llqt_srcs = 0;
	u8 *hopopt;

	mld_hdr_size = माप(*mldq);
	अगर (br->multicast_mld_version == 2) अणु
		mld_hdr_size = माप(*mld2q);
		अगर (pg && with_srcs) अणु
			llqt = now + (br->multicast_last_member_पूर्णांकerval *
				      br->multicast_last_member_count);
			hlist_क्रम_each_entry(ent, &pg->src_list, node) अणु
				अगर (over_llqt == समय_after(ent->समयr.expires,
							    llqt) &&
				    ent->src_query_rexmit_cnt > 0)
					llqt_srcs++;
			पूर्ण

			अगर (!llqt_srcs)
				वापस शून्य;
			mld_hdr_size += llqt_srcs * माप(काष्ठा in6_addr);
		पूर्ण
	पूर्ण

	pkt_size = माप(*eth) + माप(*ip6h) + 8 + mld_hdr_size;
	अगर ((p && pkt_size > p->dev->mtu) ||
	    pkt_size > br->dev->mtu)
		वापस शून्य;

	skb = netdev_alloc_skb_ip_align(br->dev, pkt_size);
	अगर (!skb)
		जाओ out;

	skb->protocol = htons(ETH_P_IPV6);

	/* Ethernet header */
	skb_reset_mac_header(skb);
	eth = eth_hdr(skb);

	ether_addr_copy(eth->h_source, br->dev->dev_addr);
	eth->h_proto = htons(ETH_P_IPV6);
	skb_put(skb, माप(*eth));

	/* IPv6 header + HbH option */
	skb_set_network_header(skb, skb->len);
	ip6h = ipv6_hdr(skb);

	*(__क्रमce __be32 *)ip6h = htonl(0x60000000);
	ip6h->payload_len = htons(8 + mld_hdr_size);
	ip6h->nexthdr = IPPROTO_HOPOPTS;
	ip6h->hop_limit = 1;
	ip6h->daddr = *ip6_dst;
	अगर (ipv6_dev_get_saddr(dev_net(br->dev), br->dev, &ip6h->daddr, 0,
			       &ip6h->saddr)) अणु
		kमुक्त_skb(skb);
		br_opt_toggle(br, BROPT_HAS_IPV6_ADDR, false);
		वापस शून्य;
	पूर्ण

	br_opt_toggle(br, BROPT_HAS_IPV6_ADDR, true);
	ipv6_eth_mc_map(&ip6h->daddr, eth->h_dest);

	hopopt = (u8 *)(ip6h + 1);
	hopopt[0] = IPPROTO_ICMPV6;		/* next hdr */
	hopopt[1] = 0;				/* length of HbH */
	hopopt[2] = IPV6_TLV_ROUTERALERT;	/* Router Alert */
	hopopt[3] = 2;				/* Length of RA Option */
	hopopt[4] = 0;				/* Type = 0x0000 (MLD) */
	hopopt[5] = 0;
	hopopt[6] = IPV6_TLV_PAD1;		/* Pad1 */
	hopopt[7] = IPV6_TLV_PAD1;		/* Pad1 */

	skb_put(skb, माप(*ip6h) + 8);

	/* ICMPv6 */
	skb_set_transport_header(skb, skb->len);
	पूर्णांकerval = ipv6_addr_any(group) ?
			br->multicast_query_response_पूर्णांकerval :
			br->multicast_last_member_पूर्णांकerval;
	*igmp_type = ICMPV6_MGM_QUERY;
	चयन (br->multicast_mld_version) अणु
	हाल 1:
		mldq = (काष्ठा mld_msg *)icmp6_hdr(skb);
		mldq->mld_type = ICMPV6_MGM_QUERY;
		mldq->mld_code = 0;
		mldq->mld_cksum = 0;
		mldq->mld_maxdelay = htons((u16)jअगरfies_to_msecs(पूर्णांकerval));
		mldq->mld_reserved = 0;
		mldq->mld_mca = *group;
		csum = &mldq->mld_cksum;
		csum_start = (व्योम *)mldq;
		अवरोध;
	हाल 2:
		mld2q = (काष्ठा mld2_query *)icmp6_hdr(skb);
		mld2q->mld2q_mrc = htons((u16)jअगरfies_to_msecs(पूर्णांकerval));
		mld2q->mld2q_type = ICMPV6_MGM_QUERY;
		mld2q->mld2q_code = 0;
		mld2q->mld2q_cksum = 0;
		mld2q->mld2q_resv1 = 0;
		mld2q->mld2q_resv2 = 0;
		mld2q->mld2q_suppress = sflag;
		mld2q->mld2q_qrv = 2;
		mld2q->mld2q_nsrcs = htons(llqt_srcs);
		mld2q->mld2q_qqic = br->multicast_query_पूर्णांकerval / HZ;
		mld2q->mld2q_mca = *group;
		csum = &mld2q->mld2q_cksum;
		csum_start = (व्योम *)mld2q;
		अगर (!pg || !with_srcs)
			अवरोध;

		llqt_srcs = 0;
		hlist_क्रम_each_entry(ent, &pg->src_list, node) अणु
			अगर (over_llqt == समय_after(ent->समयr.expires,
						    llqt) &&
			    ent->src_query_rexmit_cnt > 0) अणु
				mld2q->mld2q_srcs[llqt_srcs++] = ent->addr.src.ip6;
				ent->src_query_rexmit_cnt--;
				अगर (need_rexmit && ent->src_query_rexmit_cnt)
					*need_rexmit = true;
			पूर्ण
		पूर्ण
		अगर (WARN_ON(llqt_srcs != ntohs(mld2q->mld2q_nsrcs))) अणु
			kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (WARN_ON(!csum || !csum_start)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	*csum = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr, mld_hdr_size,
				IPPROTO_ICMPV6,
				csum_partial(csum_start, mld_hdr_size, 0));
	skb_put(skb, mld_hdr_size);
	__skb_pull(skb, माप(*eth));

out:
	वापस skb;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा sk_buff *br_multicast_alloc_query(काष्ठा net_bridge *br,
						काष्ठा net_bridge_port_group *pg,
						काष्ठा br_ip *ip_dst,
						काष्ठा br_ip *group,
						bool with_srcs, bool over_lmqt,
						u8 sflag, u8 *igmp_type,
						bool *need_rexmit)
अणु
	__be32 ip4_dst;

	चयन (group->proto) अणु
	हाल htons(ETH_P_IP):
		ip4_dst = ip_dst ? ip_dst->dst.ip4 : htonl(INADDR_ALLHOSTS_GROUP);
		वापस br_ip4_multicast_alloc_query(br, pg,
						    ip4_dst, group->dst.ip4,
						    with_srcs, over_lmqt,
						    sflag, igmp_type,
						    need_rexmit);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6): अणु
		काष्ठा in6_addr ip6_dst;

		अगर (ip_dst)
			ip6_dst = ip_dst->dst.ip6;
		अन्यथा
			ipv6_addr_set(&ip6_dst, htonl(0xff020000), 0, 0,
				      htonl(1));

		वापस br_ip6_multicast_alloc_query(br, pg,
						    &ip6_dst, &group->dst.ip6,
						    with_srcs, over_lmqt,
						    sflag, igmp_type,
						    need_rexmit);
	पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा net_bridge_mdb_entry *br_multicast_new_group(काष्ठा net_bridge *br,
						    काष्ठा br_ip *group)
अणु
	काष्ठा net_bridge_mdb_entry *mp;
	पूर्णांक err;

	mp = br_mdb_ip_get(br, group);
	अगर (mp)
		वापस mp;

	अगर (atomic_पढ़ो(&br->mdb_hash_tbl.nelems) >= br->hash_max) अणु
		br_opt_toggle(br, BROPT_MULTICAST_ENABLED, false);
		वापस ERR_PTR(-E2BIG);
	पूर्ण

	mp = kzalloc(माप(*mp), GFP_ATOMIC);
	अगर (unlikely(!mp))
		वापस ERR_PTR(-ENOMEM);

	mp->br = br;
	mp->addr = *group;
	mp->mcast_gc.destroy = br_multicast_destroy_mdb_entry;
	समयr_setup(&mp->समयr, br_multicast_group_expired, 0);
	err = rhashtable_lookup_insert_fast(&br->mdb_hash_tbl, &mp->rhnode,
					    br_mdb_rht_params);
	अगर (err) अणु
		kमुक्त(mp);
		mp = ERR_PTR(err);
	पूर्ण अन्यथा अणु
		hlist_add_head_rcu(&mp->mdb_node, &br->mdb_list);
	पूर्ण

	वापस mp;
पूर्ण

अटल व्योम br_multicast_group_src_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_group_src *src = from_समयr(src, t, समयr);
	काष्ठा net_bridge_port_group *pg;
	काष्ठा net_bridge *br = src->br;

	spin_lock(&br->multicast_lock);
	अगर (hlist_unhashed(&src->node) || !netअगर_running(br->dev) ||
	    समयr_pending(&src->समयr))
		जाओ out;

	pg = src->pg;
	अगर (pg->filter_mode == MCAST_INCLUDE) अणु
		br_multicast_del_group_src(src, false);
		अगर (!hlist_empty(&pg->src_list))
			जाओ out;
		br_multicast_find_del_pg(br, pg);
	पूर्ण अन्यथा अणु
		br_multicast_fwd_src_handle(src);
	पूर्ण

out:
	spin_unlock(&br->multicast_lock);
पूर्ण

काष्ठा net_bridge_group_src *
br_multicast_find_group_src(काष्ठा net_bridge_port_group *pg, काष्ठा br_ip *ip)
अणु
	काष्ठा net_bridge_group_src *ent;

	चयन (ip->proto) अणु
	हाल htons(ETH_P_IP):
		hlist_क्रम_each_entry(ent, &pg->src_list, node)
			अगर (ip->src.ip4 == ent->addr.src.ip4)
				वापस ent;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		hlist_क्रम_each_entry(ent, &pg->src_list, node)
			अगर (!ipv6_addr_cmp(&ent->addr.src.ip6, &ip->src.ip6))
				वापस ent;
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा net_bridge_group_src *
br_multicast_new_group_src(काष्ठा net_bridge_port_group *pg, काष्ठा br_ip *src_ip)
अणु
	काष्ठा net_bridge_group_src *grp_src;

	अगर (unlikely(pg->src_ents >= PG_SRC_ENT_LIMIT))
		वापस शून्य;

	चयन (src_ip->proto) अणु
	हाल htons(ETH_P_IP):
		अगर (ipv4_is_zeronet(src_ip->src.ip4) ||
		    ipv4_is_multicast(src_ip->src.ip4))
			वापस शून्य;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		अगर (ipv6_addr_any(&src_ip->src.ip6) ||
		    ipv6_addr_is_multicast(&src_ip->src.ip6))
			वापस शून्य;
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	grp_src = kzalloc(माप(*grp_src), GFP_ATOMIC);
	अगर (unlikely(!grp_src))
		वापस शून्य;

	grp_src->pg = pg;
	grp_src->br = pg->key.port->br;
	grp_src->addr = *src_ip;
	grp_src->mcast_gc.destroy = br_multicast_destroy_group_src;
	समयr_setup(&grp_src->समयr, br_multicast_group_src_expired, 0);

	hlist_add_head_rcu(&grp_src->node, &pg->src_list);
	pg->src_ents++;

	वापस grp_src;
पूर्ण

काष्ठा net_bridge_port_group *br_multicast_new_port_group(
			काष्ठा net_bridge_port *port,
			काष्ठा br_ip *group,
			काष्ठा net_bridge_port_group __rcu *next,
			अचिन्हित अक्षर flags,
			स्थिर अचिन्हित अक्षर *src,
			u8 filter_mode,
			u8 rt_protocol)
अणु
	काष्ठा net_bridge_port_group *p;

	p = kzalloc(माप(*p), GFP_ATOMIC);
	अगर (unlikely(!p))
		वापस शून्य;

	p->key.addr = *group;
	p->key.port = port;
	p->flags = flags;
	p->filter_mode = filter_mode;
	p->rt_protocol = rt_protocol;
	p->eht_host_tree = RB_ROOT;
	p->eht_set_tree = RB_ROOT;
	p->mcast_gc.destroy = br_multicast_destroy_port_group;
	INIT_HLIST_HEAD(&p->src_list);

	अगर (!br_multicast_is_star_g(group) &&
	    rhashtable_lookup_insert_fast(&port->br->sg_port_tbl, &p->rhnode,
					  br_sg_port_rht_params)) अणु
		kमुक्त(p);
		वापस शून्य;
	पूर्ण

	rcu_assign_poपूर्णांकer(p->next, next);
	समयr_setup(&p->समयr, br_multicast_port_group_expired, 0);
	समयr_setup(&p->rexmit_समयr, br_multicast_port_group_rexmit, 0);
	hlist_add_head(&p->mglist, &port->mglist);

	अगर (src)
		स_नकल(p->eth_addr, src, ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(p->eth_addr);

	वापस p;
पूर्ण

व्योम br_multicast_host_join(काष्ठा net_bridge_mdb_entry *mp, bool notअगरy)
अणु
	अगर (!mp->host_joined) अणु
		mp->host_joined = true;
		अगर (br_multicast_is_star_g(&mp->addr))
			br_multicast_star_g_host_state(mp);
		अगर (notअगरy)
			br_mdb_notअगरy(mp->br->dev, mp, शून्य, RTM_NEWMDB);
	पूर्ण

	अगर (br_group_is_l2(&mp->addr))
		वापस;

	mod_समयr(&mp->समयr, jअगरfies + mp->br->multicast_membership_पूर्णांकerval);
पूर्ण

व्योम br_multicast_host_leave(काष्ठा net_bridge_mdb_entry *mp, bool notअगरy)
अणु
	अगर (!mp->host_joined)
		वापस;

	mp->host_joined = false;
	अगर (br_multicast_is_star_g(&mp->addr))
		br_multicast_star_g_host_state(mp);
	अगर (notअगरy)
		br_mdb_notअगरy(mp->br->dev, mp, शून्य, RTM_DELMDB);
पूर्ण

अटल काष्ठा net_bridge_port_group *
__br_multicast_add_group(काष्ठा net_bridge *br,
			 काष्ठा net_bridge_port *port,
			 काष्ठा br_ip *group,
			 स्थिर अचिन्हित अक्षर *src,
			 u8 filter_mode,
			 bool igmpv2_mldv1,
			 bool blocked)
अणु
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा net_bridge_port_group *p = शून्य;
	काष्ठा net_bridge_mdb_entry *mp;
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (!netअगर_running(br->dev) ||
	    (port && port->state == BR_STATE_DISABLED))
		जाओ out;

	mp = br_multicast_new_group(br, group);
	अगर (IS_ERR(mp))
		वापस ERR_CAST(mp);

	अगर (!port) अणु
		br_multicast_host_join(mp, true);
		जाओ out;
	पूर्ण

	क्रम (pp = &mp->ports;
	     (p = mlock_dereference(*pp, br)) != शून्य;
	     pp = &p->next) अणु
		अगर (br_port_group_equal(p, port, src))
			जाओ found;
		अगर ((अचिन्हित दीर्घ)p->key.port < (अचिन्हित दीर्घ)port)
			अवरोध;
	पूर्ण

	p = br_multicast_new_port_group(port, group, *pp, 0, src,
					filter_mode, RTPROT_KERNEL);
	अगर (unlikely(!p)) अणु
		p = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	rcu_assign_poपूर्णांकer(*pp, p);
	अगर (blocked)
		p->flags |= MDB_PG_FLAGS_BLOCKED;
	br_mdb_notअगरy(br->dev, mp, p, RTM_NEWMDB);

found:
	अगर (igmpv2_mldv1)
		mod_समयr(&p->समयr, now + br->multicast_membership_पूर्णांकerval);

out:
	वापस p;
पूर्ण

अटल पूर्णांक br_multicast_add_group(काष्ठा net_bridge *br,
				  काष्ठा net_bridge_port *port,
				  काष्ठा br_ip *group,
				  स्थिर अचिन्हित अक्षर *src,
				  u8 filter_mode,
				  bool igmpv2_mldv1)
अणु
	काष्ठा net_bridge_port_group *pg;
	पूर्णांक err;

	spin_lock(&br->multicast_lock);
	pg = __br_multicast_add_group(br, port, group, src, filter_mode,
				      igmpv2_mldv1, false);
	/* शून्य is considered valid क्रम host joined groups */
	err = PTR_ERR_OR_ZERO(pg);
	spin_unlock(&br->multicast_lock);

	वापस err;
पूर्ण

अटल पूर्णांक br_ip4_multicast_add_group(काष्ठा net_bridge *br,
				      काष्ठा net_bridge_port *port,
				      __be32 group,
				      __u16 vid,
				      स्थिर अचिन्हित अक्षर *src,
				      bool igmpv2)
अणु
	काष्ठा br_ip br_group;
	u8 filter_mode;

	अगर (ipv4_is_local_multicast(group))
		वापस 0;

	स_रखो(&br_group, 0, माप(br_group));
	br_group.dst.ip4 = group;
	br_group.proto = htons(ETH_P_IP);
	br_group.vid = vid;
	filter_mode = igmpv2 ? MCAST_EXCLUDE : MCAST_INCLUDE;

	वापस br_multicast_add_group(br, port, &br_group, src, filter_mode,
				      igmpv2);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक br_ip6_multicast_add_group(काष्ठा net_bridge *br,
				      काष्ठा net_bridge_port *port,
				      स्थिर काष्ठा in6_addr *group,
				      __u16 vid,
				      स्थिर अचिन्हित अक्षर *src,
				      bool mldv1)
अणु
	काष्ठा br_ip br_group;
	u8 filter_mode;

	अगर (ipv6_addr_is_ll_all_nodes(group))
		वापस 0;

	स_रखो(&br_group, 0, माप(br_group));
	br_group.dst.ip6 = *group;
	br_group.proto = htons(ETH_P_IPV6);
	br_group.vid = vid;
	filter_mode = mldv1 ? MCAST_EXCLUDE : MCAST_INCLUDE;

	वापस br_multicast_add_group(br, port, &br_group, src, filter_mode,
				      mldv1);
पूर्ण
#पूर्ण_अगर

अटल व्योम br_multicast_router_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_port *port =
			from_समयr(port, t, multicast_router_समयr);
	काष्ठा net_bridge *br = port->br;

	spin_lock(&br->multicast_lock);
	अगर (port->multicast_router == MDB_RTR_TYPE_DISABLED ||
	    port->multicast_router == MDB_RTR_TYPE_PERM ||
	    समयr_pending(&port->multicast_router_समयr))
		जाओ out;

	__del_port_router(port);
out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_mc_router_state_change(काष्ठा net_bridge *p,
				      bool is_mc_router)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_MROUTER,
		.flags = SWITCHDEV_F_DEFER,
		.u.mrouter = is_mc_router,
	पूर्ण;

	चयनdev_port_attr_set(p->dev, &attr, शून्य);
पूर्ण

अटल व्योम br_multicast_local_router_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge *br = from_समयr(br, t, multicast_router_समयr);

	spin_lock(&br->multicast_lock);
	अगर (br->multicast_router == MDB_RTR_TYPE_DISABLED ||
	    br->multicast_router == MDB_RTR_TYPE_PERM ||
	    समयr_pending(&br->multicast_router_समयr))
		जाओ out;

	br_mc_router_state_change(br, false);
out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_multicast_querier_expired(काष्ठा net_bridge *br,
					 काष्ठा bridge_mcast_own_query *query)
अणु
	spin_lock(&br->multicast_lock);
	अगर (!netअगर_running(br->dev) || !br_opt_get(br, BROPT_MULTICAST_ENABLED))
		जाओ out;

	br_multicast_start_querier(br, query);

out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_ip4_multicast_querier_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge *br = from_समयr(br, t, ip4_other_query.समयr);

	br_multicast_querier_expired(br, &br->ip4_own_query);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम br_ip6_multicast_querier_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge *br = from_समयr(br, t, ip6_other_query.समयr);

	br_multicast_querier_expired(br, &br->ip6_own_query);
पूर्ण
#पूर्ण_अगर

अटल व्योम br_multicast_select_own_querier(काष्ठा net_bridge *br,
					    काष्ठा br_ip *ip,
					    काष्ठा sk_buff *skb)
अणु
	अगर (ip->proto == htons(ETH_P_IP))
		br->ip4_querier.addr.src.ip4 = ip_hdr(skb)->saddr;
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		br->ip6_querier.addr.src.ip6 = ipv6_hdr(skb)->saddr;
#पूर्ण_अगर
पूर्ण

अटल व्योम __br_multicast_send_query(काष्ठा net_bridge *br,
				      काष्ठा net_bridge_port *port,
				      काष्ठा net_bridge_port_group *pg,
				      काष्ठा br_ip *ip_dst,
				      काष्ठा br_ip *group,
				      bool with_srcs,
				      u8 sflag,
				      bool *need_rexmit)
अणु
	bool over_lmqt = !!sflag;
	काष्ठा sk_buff *skb;
	u8 igmp_type;

again_under_lmqt:
	skb = br_multicast_alloc_query(br, pg, ip_dst, group, with_srcs,
				       over_lmqt, sflag, &igmp_type,
				       need_rexmit);
	अगर (!skb)
		वापस;

	अगर (port) अणु
		skb->dev = port->dev;
		br_multicast_count(br, port, skb, igmp_type,
				   BR_MCAST_सूची_TX);
		NF_HOOK(NFPROTO_BRIDGE, NF_BR_LOCAL_OUT,
			dev_net(port->dev), शून्य, skb, शून्य, skb->dev,
			br_dev_queue_push_xmit);

		अगर (over_lmqt && with_srcs && sflag) अणु
			over_lmqt = false;
			जाओ again_under_lmqt;
		पूर्ण
	पूर्ण अन्यथा अणु
		br_multicast_select_own_querier(br, group, skb);
		br_multicast_count(br, port, skb, igmp_type,
				   BR_MCAST_सूची_RX);
		netअगर_rx(skb);
	पूर्ण
पूर्ण

अटल व्योम br_multicast_send_query(काष्ठा net_bridge *br,
				    काष्ठा net_bridge_port *port,
				    काष्ठा bridge_mcast_own_query *own_query)
अणु
	काष्ठा bridge_mcast_other_query *other_query = शून्य;
	काष्ठा br_ip br_group;
	अचिन्हित दीर्घ समय;

	अगर (!netअगर_running(br->dev) ||
	    !br_opt_get(br, BROPT_MULTICAST_ENABLED) ||
	    !br_opt_get(br, BROPT_MULTICAST_QUERIER))
		वापस;

	स_रखो(&br_group.dst, 0, माप(br_group.dst));

	अगर (port ? (own_query == &port->ip4_own_query) :
		   (own_query == &br->ip4_own_query)) अणु
		other_query = &br->ip4_other_query;
		br_group.proto = htons(ETH_P_IP);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		other_query = &br->ip6_other_query;
		br_group.proto = htons(ETH_P_IPV6);
#पूर्ण_अगर
	पूर्ण

	अगर (!other_query || समयr_pending(&other_query->समयr))
		वापस;

	__br_multicast_send_query(br, port, शून्य, शून्य, &br_group, false, 0,
				  शून्य);

	समय = jअगरfies;
	समय += own_query->startup_sent < br->multicast_startup_query_count ?
		br->multicast_startup_query_पूर्णांकerval :
		br->multicast_query_पूर्णांकerval;
	mod_समयr(&own_query->समयr, समय);
पूर्ण

अटल व्योम
br_multicast_port_query_expired(काष्ठा net_bridge_port *port,
				काष्ठा bridge_mcast_own_query *query)
अणु
	काष्ठा net_bridge *br = port->br;

	spin_lock(&br->multicast_lock);
	अगर (port->state == BR_STATE_DISABLED ||
	    port->state == BR_STATE_BLOCKING)
		जाओ out;

	अगर (query->startup_sent < br->multicast_startup_query_count)
		query->startup_sent++;

	br_multicast_send_query(port->br, port, query);

out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_ip4_multicast_port_query_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_port *port = from_समयr(port, t, ip4_own_query.समयr);

	br_multicast_port_query_expired(port, &port->ip4_own_query);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम br_ip6_multicast_port_query_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_port *port = from_समयr(port, t, ip6_own_query.समयr);

	br_multicast_port_query_expired(port, &port->ip6_own_query);
पूर्ण
#पूर्ण_अगर

अटल व्योम br_multicast_port_group_rexmit(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge_port_group *pg = from_समयr(pg, t, rexmit_समयr);
	काष्ठा bridge_mcast_other_query *other_query = शून्य;
	काष्ठा net_bridge *br = pg->key.port->br;
	bool need_rexmit = false;

	spin_lock(&br->multicast_lock);
	अगर (!netअगर_running(br->dev) || hlist_unhashed(&pg->mglist) ||
	    !br_opt_get(br, BROPT_MULTICAST_ENABLED) ||
	    !br_opt_get(br, BROPT_MULTICAST_QUERIER))
		जाओ out;

	अगर (pg->key.addr.proto == htons(ETH_P_IP))
		other_query = &br->ip4_other_query;
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		other_query = &br->ip6_other_query;
#पूर्ण_अगर

	अगर (!other_query || समयr_pending(&other_query->समयr))
		जाओ out;

	अगर (pg->grp_query_rexmit_cnt) अणु
		pg->grp_query_rexmit_cnt--;
		__br_multicast_send_query(br, pg->key.port, pg, &pg->key.addr,
					  &pg->key.addr, false, 1, शून्य);
	पूर्ण
	__br_multicast_send_query(br, pg->key.port, pg, &pg->key.addr,
				  &pg->key.addr, true, 0, &need_rexmit);

	अगर (pg->grp_query_rexmit_cnt || need_rexmit)
		mod_समयr(&pg->rexmit_समयr, jअगरfies +
					     br->multicast_last_member_पूर्णांकerval);
out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल पूर्णांक br_mc_disabled_update(काष्ठा net_device *dev, bool value,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_MC_DISABLED,
		.flags = SWITCHDEV_F_DEFER,
		.u.mc_disabled = !value,
	पूर्ण;

	वापस चयनdev_port_attr_set(dev, &attr, extack);
पूर्ण

पूर्णांक br_multicast_add_port(काष्ठा net_bridge_port *port)
अणु
	पूर्णांक err;

	port->multicast_router = MDB_RTR_TYPE_TEMP_QUERY;
	port->multicast_eht_hosts_limit = BR_MCAST_DEFAULT_EHT_HOSTS_LIMIT;

	समयr_setup(&port->multicast_router_समयr,
		    br_multicast_router_expired, 0);
	समयr_setup(&port->ip4_own_query.समयr,
		    br_ip4_multicast_port_query_expired, 0);
#अगर IS_ENABLED(CONFIG_IPV6)
	समयr_setup(&port->ip6_own_query.समयr,
		    br_ip6_multicast_port_query_expired, 0);
#पूर्ण_अगर
	err = br_mc_disabled_update(port->dev,
				    br_opt_get(port->br,
					       BROPT_MULTICAST_ENABLED),
				    शून्य);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	port->mcast_stats = netdev_alloc_pcpu_stats(काष्ठा bridge_mcast_stats);
	अगर (!port->mcast_stats)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम br_multicast_del_port(काष्ठा net_bridge_port *port)
अणु
	काष्ठा net_bridge *br = port->br;
	काष्ठा net_bridge_port_group *pg;
	HLIST_HEAD(deleted_head);
	काष्ठा hlist_node *n;

	/* Take care of the reमुख्यing groups, only perm ones should be left */
	spin_lock_bh(&br->multicast_lock);
	hlist_क्रम_each_entry_safe(pg, n, &port->mglist, mglist)
		br_multicast_find_del_pg(br, pg);
	hlist_move_list(&br->mcast_gc_list, &deleted_head);
	spin_unlock_bh(&br->multicast_lock);
	br_multicast_gc(&deleted_head);
	del_समयr_sync(&port->multicast_router_समयr);
	मुक्त_percpu(port->mcast_stats);
पूर्ण

अटल व्योम br_multicast_enable(काष्ठा bridge_mcast_own_query *query)
अणु
	query->startup_sent = 0;

	अगर (try_to_del_समयr_sync(&query->समयr) >= 0 ||
	    del_समयr(&query->समयr))
		mod_समयr(&query->समयr, jअगरfies);
पूर्ण

अटल व्योम __br_multicast_enable_port(काष्ठा net_bridge_port *port)
अणु
	काष्ठा net_bridge *br = port->br;

	अगर (!br_opt_get(br, BROPT_MULTICAST_ENABLED) || !netअगर_running(br->dev))
		वापस;

	br_multicast_enable(&port->ip4_own_query);
#अगर IS_ENABLED(CONFIG_IPV6)
	br_multicast_enable(&port->ip6_own_query);
#पूर्ण_अगर
	अगर (port->multicast_router == MDB_RTR_TYPE_PERM &&
	    hlist_unhashed(&port->rlist))
		br_multicast_add_router(br, port);
पूर्ण

व्योम br_multicast_enable_port(काष्ठा net_bridge_port *port)
अणु
	काष्ठा net_bridge *br = port->br;

	spin_lock(&br->multicast_lock);
	__br_multicast_enable_port(port);
	spin_unlock(&br->multicast_lock);
पूर्ण

व्योम br_multicast_disable_port(काष्ठा net_bridge_port *port)
अणु
	काष्ठा net_bridge *br = port->br;
	काष्ठा net_bridge_port_group *pg;
	काष्ठा hlist_node *n;

	spin_lock(&br->multicast_lock);
	hlist_क्रम_each_entry_safe(pg, n, &port->mglist, mglist)
		अगर (!(pg->flags & MDB_PG_FLAGS_PERMANENT))
			br_multicast_find_del_pg(br, pg);

	__del_port_router(port);

	del_समयr(&port->multicast_router_समयr);
	del_समयr(&port->ip4_own_query.समयr);
#अगर IS_ENABLED(CONFIG_IPV6)
	del_समयr(&port->ip6_own_query.समयr);
#पूर्ण_अगर
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल पूर्णांक __grp_src_delete_marked(काष्ठा net_bridge_port_group *pg)
अणु
	काष्ठा net_bridge_group_src *ent;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक deleted = 0;

	hlist_क्रम_each_entry_safe(ent, पंचांगp, &pg->src_list, node)
		अगर (ent->flags & BR_SGRP_F_DELETE) अणु
			br_multicast_del_group_src(ent, false);
			deleted++;
		पूर्ण

	वापस deleted;
पूर्ण

अटल व्योम __grp_src_mod_समयr(काष्ठा net_bridge_group_src *src,
				अचिन्हित दीर्घ expires)
अणु
	mod_समयr(&src->समयr, expires);
	br_multicast_fwd_src_handle(src);
पूर्ण

अटल व्योम __grp_src_query_marked_and_rexmit(काष्ठा net_bridge_port_group *pg)
अणु
	काष्ठा bridge_mcast_other_query *other_query = शून्य;
	काष्ठा net_bridge *br = pg->key.port->br;
	u32 lmqc = br->multicast_last_member_count;
	अचिन्हित दीर्घ lmqt, lmi, now = jअगरfies;
	काष्ठा net_bridge_group_src *ent;

	अगर (!netअगर_running(br->dev) ||
	    !br_opt_get(br, BROPT_MULTICAST_ENABLED))
		वापस;

	अगर (pg->key.addr.proto == htons(ETH_P_IP))
		other_query = &br->ip4_other_query;
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		other_query = &br->ip6_other_query;
#पूर्ण_अगर

	lmqt = now + br_multicast_lmqt(br);
	hlist_क्रम_each_entry(ent, &pg->src_list, node) अणु
		अगर (ent->flags & BR_SGRP_F_SEND) अणु
			ent->flags &= ~BR_SGRP_F_SEND;
			अगर (ent->समयr.expires > lmqt) अणु
				अगर (br_opt_get(br, BROPT_MULTICAST_QUERIER) &&
				    other_query &&
				    !समयr_pending(&other_query->समयr))
					ent->src_query_rexmit_cnt = lmqc;
				__grp_src_mod_समयr(ent, lmqt);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!br_opt_get(br, BROPT_MULTICAST_QUERIER) ||
	    !other_query || समयr_pending(&other_query->समयr))
		वापस;

	__br_multicast_send_query(br, pg->key.port, pg, &pg->key.addr,
				  &pg->key.addr, true, 1, शून्य);

	lmi = now + br->multicast_last_member_पूर्णांकerval;
	अगर (!समयr_pending(&pg->rexmit_समयr) ||
	    समय_after(pg->rexmit_समयr.expires, lmi))
		mod_समयr(&pg->rexmit_समयr, lmi);
पूर्ण

अटल व्योम __grp_send_query_and_rexmit(काष्ठा net_bridge_port_group *pg)
अणु
	काष्ठा bridge_mcast_other_query *other_query = शून्य;
	काष्ठा net_bridge *br = pg->key.port->br;
	अचिन्हित दीर्घ now = jअगरfies, lmi;

	अगर (!netअगर_running(br->dev) ||
	    !br_opt_get(br, BROPT_MULTICAST_ENABLED))
		वापस;

	अगर (pg->key.addr.proto == htons(ETH_P_IP))
		other_query = &br->ip4_other_query;
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		other_query = &br->ip6_other_query;
#पूर्ण_अगर

	अगर (br_opt_get(br, BROPT_MULTICAST_QUERIER) &&
	    other_query && !समयr_pending(&other_query->समयr)) अणु
		lmi = now + br->multicast_last_member_पूर्णांकerval;
		pg->grp_query_rexmit_cnt = br->multicast_last_member_count - 1;
		__br_multicast_send_query(br, pg->key.port, pg, &pg->key.addr,
					  &pg->key.addr, false, 0, शून्य);
		अगर (!समयr_pending(&pg->rexmit_समयr) ||
		    समय_after(pg->rexmit_समयr.expires, lmi))
			mod_समयr(&pg->rexmit_समयr, lmi);
	पूर्ण

	अगर (pg->filter_mode == MCAST_EXCLUDE &&
	    (!समयr_pending(&pg->समयr) ||
	     समय_after(pg->समयr.expires, now + br_multicast_lmqt(br))))
		mod_समयr(&pg->समयr, now + br_multicast_lmqt(br));
पूर्ण

/* State          Msg type      New state                Actions
 * INCLUDE (A)    IS_IN (B)     INCLUDE (A+B)            (B)=GMI
 * INCLUDE (A)    ALLOW (B)     INCLUDE (A+B)            (B)=GMI
 * EXCLUDE (X,Y)  ALLOW (A)     EXCLUDE (X+A,Y-A)        (A)=GMI
 */
अटल bool br_multicast_isinc_allow(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				     व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
				     पूर्णांक grec_type)
अणु
	काष्ठा net_bridge *br = pg->key.port->br;
	काष्ठा net_bridge_group_src *ent;
	अचिन्हित दीर्घ now = jअगरfies;
	bool changed = false;
	काष्ठा br_ip src_ip;
	u32 src_idx;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (!ent) अणु
			ent = br_multicast_new_group_src(pg, &src_ip);
			अगर (ent)
				changed = true;
		पूर्ण

		अगर (ent)
			__grp_src_mod_समयr(ent, now + br_multicast_gmi(br));
	पूर्ण

	अगर (br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type))
		changed = true;

	वापस changed;
पूर्ण

/* State          Msg type      New state                Actions
 * INCLUDE (A)    IS_EX (B)     EXCLUDE (A*B,B-A)        (B-A)=0
 *                                                       Delete (A-B)
 *                                                       Group Timer=GMI
 */
अटल व्योम __grp_src_isexc_incl(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				 व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
				 पूर्णांक grec_type)
अणु
	काष्ठा net_bridge_group_src *ent;
	काष्ठा br_ip src_ip;
	u32 src_idx;

	hlist_क्रम_each_entry(ent, &pg->src_list, node)
		ent->flags |= BR_SGRP_F_DELETE;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (ent)
			ent->flags &= ~BR_SGRP_F_DELETE;
		अन्यथा
			ent = br_multicast_new_group_src(pg, &src_ip);
		अगर (ent)
			br_multicast_fwd_src_handle(ent);
	पूर्ण

	br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type);

	__grp_src_delete_marked(pg);
पूर्ण

/* State          Msg type      New state                Actions
 * EXCLUDE (X,Y)  IS_EX (A)     EXCLUDE (A-Y,Y*A)        (A-X-Y)=GMI
 *                                                       Delete (X-A)
 *                                                       Delete (Y-A)
 *                                                       Group Timer=GMI
 */
अटल bool __grp_src_isexc_excl(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				 व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
				 पूर्णांक grec_type)
अणु
	काष्ठा net_bridge *br = pg->key.port->br;
	काष्ठा net_bridge_group_src *ent;
	अचिन्हित दीर्घ now = jअगरfies;
	bool changed = false;
	काष्ठा br_ip src_ip;
	u32 src_idx;

	hlist_क्रम_each_entry(ent, &pg->src_list, node)
		ent->flags |= BR_SGRP_F_DELETE;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (ent) अणु
			ent->flags &= ~BR_SGRP_F_DELETE;
		पूर्ण अन्यथा अणु
			ent = br_multicast_new_group_src(pg, &src_ip);
			अगर (ent) अणु
				__grp_src_mod_समयr(ent,
						    now + br_multicast_gmi(br));
				changed = true;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type))
		changed = true;

	अगर (__grp_src_delete_marked(pg))
		changed = true;

	वापस changed;
पूर्ण

अटल bool br_multicast_isexc(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
			       व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
			       पूर्णांक grec_type)
अणु
	काष्ठा net_bridge *br = pg->key.port->br;
	bool changed = false;

	चयन (pg->filter_mode) अणु
	हाल MCAST_INCLUDE:
		__grp_src_isexc_incl(pg, h_addr, srcs, nsrcs, addr_size,
				     grec_type);
		br_multicast_star_g_handle_mode(pg, MCAST_EXCLUDE);
		changed = true;
		अवरोध;
	हाल MCAST_EXCLUDE:
		changed = __grp_src_isexc_excl(pg, h_addr, srcs, nsrcs, addr_size,
					       grec_type);
		अवरोध;
	पूर्ण

	pg->filter_mode = MCAST_EXCLUDE;
	mod_समयr(&pg->समयr, jअगरfies + br_multicast_gmi(br));

	वापस changed;
पूर्ण

/* State          Msg type      New state                Actions
 * INCLUDE (A)    TO_IN (B)     INCLUDE (A+B)            (B)=GMI
 *                                                       Send Q(G,A-B)
 */
अटल bool __grp_src_toin_incl(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
				पूर्णांक grec_type)
अणु
	काष्ठा net_bridge *br = pg->key.port->br;
	u32 src_idx, to_send = pg->src_ents;
	काष्ठा net_bridge_group_src *ent;
	अचिन्हित दीर्घ now = jअगरfies;
	bool changed = false;
	काष्ठा br_ip src_ip;

	hlist_क्रम_each_entry(ent, &pg->src_list, node)
		ent->flags |= BR_SGRP_F_SEND;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (ent) अणु
			ent->flags &= ~BR_SGRP_F_SEND;
			to_send--;
		पूर्ण अन्यथा अणु
			ent = br_multicast_new_group_src(pg, &src_ip);
			अगर (ent)
				changed = true;
		पूर्ण
		अगर (ent)
			__grp_src_mod_समयr(ent, now + br_multicast_gmi(br));
	पूर्ण

	अगर (br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type))
		changed = true;

	अगर (to_send)
		__grp_src_query_marked_and_rexmit(pg);

	वापस changed;
पूर्ण

/* State          Msg type      New state                Actions
 * EXCLUDE (X,Y)  TO_IN (A)     EXCLUDE (X+A,Y-A)        (A)=GMI
 *                                                       Send Q(G,X-A)
 *                                                       Send Q(G)
 */
अटल bool __grp_src_toin_excl(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
				पूर्णांक grec_type)
अणु
	काष्ठा net_bridge *br = pg->key.port->br;
	u32 src_idx, to_send = pg->src_ents;
	काष्ठा net_bridge_group_src *ent;
	अचिन्हित दीर्घ now = jअगरfies;
	bool changed = false;
	काष्ठा br_ip src_ip;

	hlist_क्रम_each_entry(ent, &pg->src_list, node)
		अगर (समयr_pending(&ent->समयr))
			ent->flags |= BR_SGRP_F_SEND;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (ent) अणु
			अगर (समयr_pending(&ent->समयr)) अणु
				ent->flags &= ~BR_SGRP_F_SEND;
				to_send--;
			पूर्ण
		पूर्ण अन्यथा अणु
			ent = br_multicast_new_group_src(pg, &src_ip);
			अगर (ent)
				changed = true;
		पूर्ण
		अगर (ent)
			__grp_src_mod_समयr(ent, now + br_multicast_gmi(br));
	पूर्ण

	अगर (br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type))
		changed = true;

	अगर (to_send)
		__grp_src_query_marked_and_rexmit(pg);

	__grp_send_query_and_rexmit(pg);

	वापस changed;
पूर्ण

अटल bool br_multicast_toin(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
			      व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
			      पूर्णांक grec_type)
अणु
	bool changed = false;

	चयन (pg->filter_mode) अणु
	हाल MCAST_INCLUDE:
		changed = __grp_src_toin_incl(pg, h_addr, srcs, nsrcs, addr_size,
					      grec_type);
		अवरोध;
	हाल MCAST_EXCLUDE:
		changed = __grp_src_toin_excl(pg, h_addr, srcs, nsrcs, addr_size,
					      grec_type);
		अवरोध;
	पूर्ण

	अगर (br_multicast_eht_should_del_pg(pg)) अणु
		pg->flags |= MDB_PG_FLAGS_FAST_LEAVE;
		br_multicast_find_del_pg(pg->key.port->br, pg);
		/* a notअगरication has alपढ़ोy been sent and we shouldn't
		 * access pg after the delete so we have to वापस false
		 */
		changed = false;
	पूर्ण

	वापस changed;
पूर्ण

/* State          Msg type      New state                Actions
 * INCLUDE (A)    TO_EX (B)     EXCLUDE (A*B,B-A)        (B-A)=0
 *                                                       Delete (A-B)
 *                                                       Send Q(G,A*B)
 *                                                       Group Timer=GMI
 */
अटल व्योम __grp_src_toex_incl(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
				पूर्णांक grec_type)
अणु
	काष्ठा net_bridge_group_src *ent;
	u32 src_idx, to_send = 0;
	काष्ठा br_ip src_ip;

	hlist_क्रम_each_entry(ent, &pg->src_list, node)
		ent->flags = (ent->flags & ~BR_SGRP_F_SEND) | BR_SGRP_F_DELETE;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (ent) अणु
			ent->flags = (ent->flags & ~BR_SGRP_F_DELETE) |
				     BR_SGRP_F_SEND;
			to_send++;
		पूर्ण अन्यथा अणु
			ent = br_multicast_new_group_src(pg, &src_ip);
		पूर्ण
		अगर (ent)
			br_multicast_fwd_src_handle(ent);
	पूर्ण

	br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type);

	__grp_src_delete_marked(pg);
	अगर (to_send)
		__grp_src_query_marked_and_rexmit(pg);
पूर्ण

/* State          Msg type      New state                Actions
 * EXCLUDE (X,Y)  TO_EX (A)     EXCLUDE (A-Y,Y*A)        (A-X-Y)=Group Timer
 *                                                       Delete (X-A)
 *                                                       Delete (Y-A)
 *                                                       Send Q(G,A-Y)
 *                                                       Group Timer=GMI
 */
अटल bool __grp_src_toex_excl(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
				पूर्णांक grec_type)
अणु
	काष्ठा net_bridge_group_src *ent;
	u32 src_idx, to_send = 0;
	bool changed = false;
	काष्ठा br_ip src_ip;

	hlist_क्रम_each_entry(ent, &pg->src_list, node)
		ent->flags = (ent->flags & ~BR_SGRP_F_SEND) | BR_SGRP_F_DELETE;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (ent) अणु
			ent->flags &= ~BR_SGRP_F_DELETE;
		पूर्ण अन्यथा अणु
			ent = br_multicast_new_group_src(pg, &src_ip);
			अगर (ent) अणु
				__grp_src_mod_समयr(ent, pg->समयr.expires);
				changed = true;
			पूर्ण
		पूर्ण
		अगर (ent && समयr_pending(&ent->समयr)) अणु
			ent->flags |= BR_SGRP_F_SEND;
			to_send++;
		पूर्ण
	पूर्ण

	अगर (br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type))
		changed = true;

	अगर (__grp_src_delete_marked(pg))
		changed = true;
	अगर (to_send)
		__grp_src_query_marked_and_rexmit(pg);

	वापस changed;
पूर्ण

अटल bool br_multicast_toex(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
			      व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size,
			      पूर्णांक grec_type)
अणु
	काष्ठा net_bridge *br = pg->key.port->br;
	bool changed = false;

	चयन (pg->filter_mode) अणु
	हाल MCAST_INCLUDE:
		__grp_src_toex_incl(pg, h_addr, srcs, nsrcs, addr_size,
				    grec_type);
		br_multicast_star_g_handle_mode(pg, MCAST_EXCLUDE);
		changed = true;
		अवरोध;
	हाल MCAST_EXCLUDE:
		changed = __grp_src_toex_excl(pg, h_addr, srcs, nsrcs, addr_size,
					      grec_type);
		अवरोध;
	पूर्ण

	pg->filter_mode = MCAST_EXCLUDE;
	mod_समयr(&pg->समयr, jअगरfies + br_multicast_gmi(br));

	वापस changed;
पूर्ण

/* State          Msg type      New state                Actions
 * INCLUDE (A)    BLOCK (B)     INCLUDE (A)              Send Q(G,A*B)
 */
अटल bool __grp_src_block_incl(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				 व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size, पूर्णांक grec_type)
अणु
	काष्ठा net_bridge_group_src *ent;
	u32 src_idx, to_send = 0;
	bool changed = false;
	काष्ठा br_ip src_ip;

	hlist_क्रम_each_entry(ent, &pg->src_list, node)
		ent->flags &= ~BR_SGRP_F_SEND;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (ent) अणु
			ent->flags |= BR_SGRP_F_SEND;
			to_send++;
		पूर्ण
	पूर्ण

	अगर (br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type))
		changed = true;

	अगर (to_send)
		__grp_src_query_marked_and_rexmit(pg);

	वापस changed;
पूर्ण

/* State          Msg type      New state                Actions
 * EXCLUDE (X,Y)  BLOCK (A)     EXCLUDE (X+(A-Y),Y)      (A-X-Y)=Group Timer
 *                                                       Send Q(G,A-Y)
 */
अटल bool __grp_src_block_excl(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
				 व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size, पूर्णांक grec_type)
अणु
	काष्ठा net_bridge_group_src *ent;
	u32 src_idx, to_send = 0;
	bool changed = false;
	काष्ठा br_ip src_ip;

	hlist_क्रम_each_entry(ent, &pg->src_list, node)
		ent->flags &= ~BR_SGRP_F_SEND;

	स_रखो(&src_ip, 0, माप(src_ip));
	src_ip.proto = pg->key.addr.proto;
	क्रम (src_idx = 0; src_idx < nsrcs; src_idx++) अणु
		स_नकल(&src_ip.src, srcs + (src_idx * addr_size), addr_size);
		ent = br_multicast_find_group_src(pg, &src_ip);
		अगर (!ent) अणु
			ent = br_multicast_new_group_src(pg, &src_ip);
			अगर (ent) अणु
				__grp_src_mod_समयr(ent, pg->समयr.expires);
				changed = true;
			पूर्ण
		पूर्ण
		अगर (ent && समयr_pending(&ent->समयr)) अणु
			ent->flags |= BR_SGRP_F_SEND;
			to_send++;
		पूर्ण
	पूर्ण

	अगर (br_multicast_eht_handle(pg, h_addr, srcs, nsrcs, addr_size, grec_type))
		changed = true;

	अगर (to_send)
		__grp_src_query_marked_and_rexmit(pg);

	वापस changed;
पूर्ण

अटल bool br_multicast_block(काष्ठा net_bridge_port_group *pg, व्योम *h_addr,
			       व्योम *srcs, u32 nsrcs, माप_प्रकार addr_size, पूर्णांक grec_type)
अणु
	bool changed = false;

	चयन (pg->filter_mode) अणु
	हाल MCAST_INCLUDE:
		changed = __grp_src_block_incl(pg, h_addr, srcs, nsrcs, addr_size,
					       grec_type);
		अवरोध;
	हाल MCAST_EXCLUDE:
		changed = __grp_src_block_excl(pg, h_addr, srcs, nsrcs, addr_size,
					       grec_type);
		अवरोध;
	पूर्ण

	अगर ((pg->filter_mode == MCAST_INCLUDE && hlist_empty(&pg->src_list)) ||
	    br_multicast_eht_should_del_pg(pg)) अणु
		अगर (br_multicast_eht_should_del_pg(pg))
			pg->flags |= MDB_PG_FLAGS_FAST_LEAVE;
		br_multicast_find_del_pg(pg->key.port->br, pg);
		/* a notअगरication has alपढ़ोy been sent and we shouldn't
		 * access pg after the delete so we have to वापस false
		 */
		changed = false;
	पूर्ण

	वापस changed;
पूर्ण

अटल काष्ठा net_bridge_port_group *
br_multicast_find_port(काष्ठा net_bridge_mdb_entry *mp,
		       काष्ठा net_bridge_port *p,
		       स्थिर अचिन्हित अक्षर *src)
अणु
	काष्ठा net_bridge *br __maybe_unused = mp->br;
	काष्ठा net_bridge_port_group *pg;

	क्रम (pg = mlock_dereference(mp->ports, br);
	     pg;
	     pg = mlock_dereference(pg->next, br))
		अगर (br_port_group_equal(pg, p, src))
			वापस pg;

	वापस शून्य;
पूर्ण

अटल पूर्णांक br_ip4_multicast_igmp3_report(काष्ठा net_bridge *br,
					 काष्ठा net_bridge_port *port,
					 काष्ठा sk_buff *skb,
					 u16 vid)
अणु
	bool igmpv2 = br->multicast_igmp_version == 2;
	काष्ठा net_bridge_mdb_entry *mdst;
	काष्ठा net_bridge_port_group *pg;
	स्थिर अचिन्हित अक्षर *src;
	काष्ठा igmpv3_report *ih;
	काष्ठा igmpv3_grec *grec;
	पूर्णांक i, len, num, type;
	__be32 group, *h_addr;
	bool changed = false;
	पूर्णांक err = 0;
	u16 nsrcs;

	ih = igmpv3_report_hdr(skb);
	num = ntohs(ih->ngrec);
	len = skb_transport_offset(skb) + माप(*ih);

	क्रम (i = 0; i < num; i++) अणु
		len += माप(*grec);
		अगर (!ip_mc_may_pull(skb, len))
			वापस -EINVAL;

		grec = (व्योम *)(skb->data + len - माप(*grec));
		group = grec->grec_mca;
		type = grec->grec_type;
		nsrcs = ntohs(grec->grec_nsrcs);

		len += nsrcs * 4;
		अगर (!ip_mc_may_pull(skb, len))
			वापस -EINVAL;

		चयन (type) अणु
		हाल IGMPV3_MODE_IS_INCLUDE:
		हाल IGMPV3_MODE_IS_EXCLUDE:
		हाल IGMPV3_CHANGE_TO_INCLUDE:
		हाल IGMPV3_CHANGE_TO_EXCLUDE:
		हाल IGMPV3_ALLOW_NEW_SOURCES:
		हाल IGMPV3_BLOCK_OLD_SOURCES:
			अवरोध;

		शेष:
			जारी;
		पूर्ण

		src = eth_hdr(skb)->h_source;
		अगर (nsrcs == 0 &&
		    (type == IGMPV3_CHANGE_TO_INCLUDE ||
		     type == IGMPV3_MODE_IS_INCLUDE)) अणु
			अगर (!port || igmpv2) अणु
				br_ip4_multicast_leave_group(br, port, group, vid, src);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = br_ip4_multicast_add_group(br, port, group, vid,
							 src, igmpv2);
			अगर (err)
				अवरोध;
		पूर्ण

		अगर (!port || igmpv2)
			जारी;

		spin_lock_bh(&br->multicast_lock);
		mdst = br_mdb_ip4_get(br, group, vid);
		अगर (!mdst)
			जाओ unlock_जारी;
		pg = br_multicast_find_port(mdst, port, src);
		अगर (!pg || (pg->flags & MDB_PG_FLAGS_PERMANENT))
			जाओ unlock_जारी;
		/* reload grec and host addr */
		grec = (व्योम *)(skb->data + len - माप(*grec) - (nsrcs * 4));
		h_addr = &ip_hdr(skb)->saddr;
		चयन (type) अणु
		हाल IGMPV3_ALLOW_NEW_SOURCES:
			changed = br_multicast_isinc_allow(pg, h_addr, grec->grec_src,
							   nsrcs, माप(__be32), type);
			अवरोध;
		हाल IGMPV3_MODE_IS_INCLUDE:
			changed = br_multicast_isinc_allow(pg, h_addr, grec->grec_src,
							   nsrcs, माप(__be32), type);
			अवरोध;
		हाल IGMPV3_MODE_IS_EXCLUDE:
			changed = br_multicast_isexc(pg, h_addr, grec->grec_src,
						     nsrcs, माप(__be32), type);
			अवरोध;
		हाल IGMPV3_CHANGE_TO_INCLUDE:
			changed = br_multicast_toin(pg, h_addr, grec->grec_src,
						    nsrcs, माप(__be32), type);
			अवरोध;
		हाल IGMPV3_CHANGE_TO_EXCLUDE:
			changed = br_multicast_toex(pg, h_addr, grec->grec_src,
						    nsrcs, माप(__be32), type);
			अवरोध;
		हाल IGMPV3_BLOCK_OLD_SOURCES:
			changed = br_multicast_block(pg, h_addr, grec->grec_src,
						     nsrcs, माप(__be32), type);
			अवरोध;
		पूर्ण
		अगर (changed)
			br_mdb_notअगरy(br->dev, mdst, pg, RTM_NEWMDB);
unlock_जारी:
		spin_unlock_bh(&br->multicast_lock);
	पूर्ण

	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक br_ip6_multicast_mld2_report(काष्ठा net_bridge *br,
					काष्ठा net_bridge_port *port,
					काष्ठा sk_buff *skb,
					u16 vid)
अणु
	bool mldv1 = br->multicast_mld_version == 1;
	काष्ठा net_bridge_mdb_entry *mdst;
	काष्ठा net_bridge_port_group *pg;
	अचिन्हित पूर्णांक nsrcs_offset;
	स्थिर अचिन्हित अक्षर *src;
	काष्ठा icmp6hdr *icmp6h;
	काष्ठा in6_addr *h_addr;
	काष्ठा mld2_grec *grec;
	अचिन्हित पूर्णांक grec_len;
	bool changed = false;
	पूर्णांक i, len, num;
	पूर्णांक err = 0;

	अगर (!ipv6_mc_may_pull(skb, माप(*icmp6h)))
		वापस -EINVAL;

	icmp6h = icmp6_hdr(skb);
	num = ntohs(icmp6h->icmp6_dataun.un_data16[1]);
	len = skb_transport_offset(skb) + माप(*icmp6h);

	क्रम (i = 0; i < num; i++) अणु
		__be16 *_nsrcs, __nsrcs;
		u16 nsrcs;

		nsrcs_offset = len + दुरत्व(काष्ठा mld2_grec, grec_nsrcs);

		अगर (skb_transport_offset(skb) + ipv6_transport_len(skb) <
		    nsrcs_offset + माप(__nsrcs))
			वापस -EINVAL;

		_nsrcs = skb_header_poपूर्णांकer(skb, nsrcs_offset,
					    माप(__nsrcs), &__nsrcs);
		अगर (!_nsrcs)
			वापस -EINVAL;

		nsrcs = ntohs(*_nsrcs);
		grec_len = काष्ठा_size(grec, grec_src, nsrcs);

		अगर (!ipv6_mc_may_pull(skb, len + grec_len))
			वापस -EINVAL;

		grec = (काष्ठा mld2_grec *)(skb->data + len);
		len += grec_len;

		चयन (grec->grec_type) अणु
		हाल MLD2_MODE_IS_INCLUDE:
		हाल MLD2_MODE_IS_EXCLUDE:
		हाल MLD2_CHANGE_TO_INCLUDE:
		हाल MLD2_CHANGE_TO_EXCLUDE:
		हाल MLD2_ALLOW_NEW_SOURCES:
		हाल MLD2_BLOCK_OLD_SOURCES:
			अवरोध;

		शेष:
			जारी;
		पूर्ण

		src = eth_hdr(skb)->h_source;
		अगर ((grec->grec_type == MLD2_CHANGE_TO_INCLUDE ||
		     grec->grec_type == MLD2_MODE_IS_INCLUDE) &&
		    nsrcs == 0) अणु
			अगर (!port || mldv1) अणु
				br_ip6_multicast_leave_group(br, port,
							     &grec->grec_mca,
							     vid, src);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = br_ip6_multicast_add_group(br, port,
							 &grec->grec_mca, vid,
							 src, mldv1);
			अगर (err)
				अवरोध;
		पूर्ण

		अगर (!port || mldv1)
			जारी;

		spin_lock_bh(&br->multicast_lock);
		mdst = br_mdb_ip6_get(br, &grec->grec_mca, vid);
		अगर (!mdst)
			जाओ unlock_जारी;
		pg = br_multicast_find_port(mdst, port, src);
		अगर (!pg || (pg->flags & MDB_PG_FLAGS_PERMANENT))
			जाओ unlock_जारी;
		h_addr = &ipv6_hdr(skb)->saddr;
		चयन (grec->grec_type) अणु
		हाल MLD2_ALLOW_NEW_SOURCES:
			changed = br_multicast_isinc_allow(pg, h_addr,
							   grec->grec_src, nsrcs,
							   माप(काष्ठा in6_addr),
							   grec->grec_type);
			अवरोध;
		हाल MLD2_MODE_IS_INCLUDE:
			changed = br_multicast_isinc_allow(pg, h_addr,
							   grec->grec_src, nsrcs,
							   माप(काष्ठा in6_addr),
							   grec->grec_type);
			अवरोध;
		हाल MLD2_MODE_IS_EXCLUDE:
			changed = br_multicast_isexc(pg, h_addr,
						     grec->grec_src, nsrcs,
						     माप(काष्ठा in6_addr),
						     grec->grec_type);
			अवरोध;
		हाल MLD2_CHANGE_TO_INCLUDE:
			changed = br_multicast_toin(pg, h_addr,
						    grec->grec_src, nsrcs,
						    माप(काष्ठा in6_addr),
						    grec->grec_type);
			अवरोध;
		हाल MLD2_CHANGE_TO_EXCLUDE:
			changed = br_multicast_toex(pg, h_addr,
						    grec->grec_src, nsrcs,
						    माप(काष्ठा in6_addr),
						    grec->grec_type);
			अवरोध;
		हाल MLD2_BLOCK_OLD_SOURCES:
			changed = br_multicast_block(pg, h_addr,
						     grec->grec_src, nsrcs,
						     माप(काष्ठा in6_addr),
						     grec->grec_type);
			अवरोध;
		पूर्ण
		अगर (changed)
			br_mdb_notअगरy(br->dev, mdst, pg, RTM_NEWMDB);
unlock_जारी:
		spin_unlock_bh(&br->multicast_lock);
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल bool br_ip4_multicast_select_querier(काष्ठा net_bridge *br,
					    काष्ठा net_bridge_port *port,
					    __be32 saddr)
अणु
	अगर (!समयr_pending(&br->ip4_own_query.समयr) &&
	    !समयr_pending(&br->ip4_other_query.समयr))
		जाओ update;

	अगर (!br->ip4_querier.addr.src.ip4)
		जाओ update;

	अगर (ntohl(saddr) <= ntohl(br->ip4_querier.addr.src.ip4))
		जाओ update;

	वापस false;

update:
	br->ip4_querier.addr.src.ip4 = saddr;

	/* update रक्षित by general multicast_lock by caller */
	rcu_assign_poपूर्णांकer(br->ip4_querier.port, port);

	वापस true;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल bool br_ip6_multicast_select_querier(काष्ठा net_bridge *br,
					    काष्ठा net_bridge_port *port,
					    काष्ठा in6_addr *saddr)
अणु
	अगर (!समयr_pending(&br->ip6_own_query.समयr) &&
	    !समयr_pending(&br->ip6_other_query.समयr))
		जाओ update;

	अगर (ipv6_addr_cmp(saddr, &br->ip6_querier.addr.src.ip6) <= 0)
		जाओ update;

	वापस false;

update:
	br->ip6_querier.addr.src.ip6 = *saddr;

	/* update रक्षित by general multicast_lock by caller */
	rcu_assign_poपूर्णांकer(br->ip6_querier.port, port);

	वापस true;
पूर्ण
#पूर्ण_अगर

अटल bool br_multicast_select_querier(काष्ठा net_bridge *br,
					काष्ठा net_bridge_port *port,
					काष्ठा br_ip *saddr)
अणु
	चयन (saddr->proto) अणु
	हाल htons(ETH_P_IP):
		वापस br_ip4_multicast_select_querier(br, port, saddr->src.ip4);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		वापस br_ip6_multicast_select_querier(br, port, &saddr->src.ip6);
#पूर्ण_अगर
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
br_multicast_update_query_समयr(काष्ठा net_bridge *br,
				काष्ठा bridge_mcast_other_query *query,
				अचिन्हित दीर्घ max_delay)
अणु
	अगर (!समयr_pending(&query->समयr))
		query->delay_समय = jअगरfies + max_delay;

	mod_समयr(&query->समयr, jअगरfies + br->multicast_querier_पूर्णांकerval);
पूर्ण

अटल व्योम br_port_mc_router_state_change(काष्ठा net_bridge_port *p,
					   bool is_mc_router)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_PORT_MROUTER,
		.flags = SWITCHDEV_F_DEFER,
		.u.mrouter = is_mc_router,
	पूर्ण;

	चयनdev_port_attr_set(p->dev, &attr, शून्य);
पूर्ण

/*
 * Add port to router_list
 *  list is मुख्यtained ordered by poपूर्णांकer value
 *  and locked by br->multicast_lock and RCU
 */
अटल व्योम br_multicast_add_router(काष्ठा net_bridge *br,
				    काष्ठा net_bridge_port *port)
अणु
	काष्ठा net_bridge_port *p;
	काष्ठा hlist_node *slot = शून्य;

	अगर (!hlist_unhashed(&port->rlist))
		वापस;

	hlist_क्रम_each_entry(p, &br->router_list, rlist) अणु
		अगर ((अचिन्हित दीर्घ) port >= (अचिन्हित दीर्घ) p)
			अवरोध;
		slot = &p->rlist;
	पूर्ण

	अगर (slot)
		hlist_add_behind_rcu(&port->rlist, slot);
	अन्यथा
		hlist_add_head_rcu(&port->rlist, &br->router_list);
	br_rtr_notअगरy(br->dev, port, RTM_NEWMDB);
	br_port_mc_router_state_change(port, true);
पूर्ण

अटल व्योम br_multicast_mark_router(काष्ठा net_bridge *br,
				     काष्ठा net_bridge_port *port)
अणु
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (!port) अणु
		अगर (br->multicast_router == MDB_RTR_TYPE_TEMP_QUERY) अणु
			अगर (!समयr_pending(&br->multicast_router_समयr))
				br_mc_router_state_change(br, true);
			mod_समयr(&br->multicast_router_समयr,
				  now + br->multicast_querier_पूर्णांकerval);
		पूर्ण
		वापस;
	पूर्ण

	अगर (port->multicast_router == MDB_RTR_TYPE_DISABLED ||
	    port->multicast_router == MDB_RTR_TYPE_PERM)
		वापस;

	br_multicast_add_router(br, port);

	mod_समयr(&port->multicast_router_समयr,
		  now + br->multicast_querier_पूर्णांकerval);
पूर्ण

अटल व्योम br_multicast_query_received(काष्ठा net_bridge *br,
					काष्ठा net_bridge_port *port,
					काष्ठा bridge_mcast_other_query *query,
					काष्ठा br_ip *saddr,
					अचिन्हित दीर्घ max_delay)
अणु
	अगर (!br_multicast_select_querier(br, port, saddr))
		वापस;

	br_multicast_update_query_समयr(br, query, max_delay);
	br_multicast_mark_router(br, port);
पूर्ण

अटल व्योम br_ip4_multicast_query(काष्ठा net_bridge *br,
				   काष्ठा net_bridge_port *port,
				   काष्ठा sk_buff *skb,
				   u16 vid)
अणु
	अचिन्हित पूर्णांक transport_len = ip_transport_len(skb);
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा igmphdr *ih = igmp_hdr(skb);
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा igmpv3_query *ih3;
	काष्ठा net_bridge_port_group *p;
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा br_ip saddr;
	अचिन्हित दीर्घ max_delay;
	अचिन्हित दीर्घ now = jअगरfies;
	__be32 group;

	spin_lock(&br->multicast_lock);
	अगर (!netअगर_running(br->dev) ||
	    (port && port->state == BR_STATE_DISABLED))
		जाओ out;

	group = ih->group;

	अगर (transport_len == माप(*ih)) अणु
		max_delay = ih->code * (HZ / IGMP_TIMER_SCALE);

		अगर (!max_delay) अणु
			max_delay = 10 * HZ;
			group = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (transport_len >= माप(*ih3)) अणु
		ih3 = igmpv3_query_hdr(skb);
		अगर (ih3->nsrcs ||
		    (br->multicast_igmp_version == 3 && group && ih3->suppress))
			जाओ out;

		max_delay = ih3->code ?
			    IGMPV3_MRC(ih3->code) * (HZ / IGMP_TIMER_SCALE) : 1;
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

	अगर (!group) अणु
		saddr.proto = htons(ETH_P_IP);
		saddr.src.ip4 = iph->saddr;

		br_multicast_query_received(br, port, &br->ip4_other_query,
					    &saddr, max_delay);
		जाओ out;
	पूर्ण

	mp = br_mdb_ip4_get(br, group, vid);
	अगर (!mp)
		जाओ out;

	max_delay *= br->multicast_last_member_count;

	अगर (mp->host_joined &&
	    (समयr_pending(&mp->समयr) ?
	     समय_after(mp->समयr.expires, now + max_delay) :
	     try_to_del_समयr_sync(&mp->समयr) >= 0))
		mod_समयr(&mp->समयr, now + max_delay);

	क्रम (pp = &mp->ports;
	     (p = mlock_dereference(*pp, br)) != शून्य;
	     pp = &p->next) अणु
		अगर (समयr_pending(&p->समयr) ?
		    समय_after(p->समयr.expires, now + max_delay) :
		    try_to_del_समयr_sync(&p->समयr) >= 0 &&
		    (br->multicast_igmp_version == 2 ||
		     p->filter_mode == MCAST_EXCLUDE))
			mod_समयr(&p->समयr, now + max_delay);
	पूर्ण

out:
	spin_unlock(&br->multicast_lock);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक br_ip6_multicast_query(काष्ठा net_bridge *br,
				  काष्ठा net_bridge_port *port,
				  काष्ठा sk_buff *skb,
				  u16 vid)
अणु
	अचिन्हित पूर्णांक transport_len = ipv6_transport_len(skb);
	काष्ठा mld_msg *mld;
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा mld2_query *mld2q;
	काष्ठा net_bridge_port_group *p;
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा br_ip saddr;
	अचिन्हित दीर्घ max_delay;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित पूर्णांक offset = skb_transport_offset(skb);
	स्थिर काष्ठा in6_addr *group = शून्य;
	bool is_general_query;
	पूर्णांक err = 0;

	spin_lock(&br->multicast_lock);
	अगर (!netअगर_running(br->dev) ||
	    (port && port->state == BR_STATE_DISABLED))
		जाओ out;

	अगर (transport_len == माप(*mld)) अणु
		अगर (!pskb_may_pull(skb, offset + माप(*mld))) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		mld = (काष्ठा mld_msg *) icmp6_hdr(skb);
		max_delay = msecs_to_jअगरfies(ntohs(mld->mld_maxdelay));
		अगर (max_delay)
			group = &mld->mld_mca;
	पूर्ण अन्यथा अणु
		अगर (!pskb_may_pull(skb, offset + माप(*mld2q))) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		mld2q = (काष्ठा mld2_query *)icmp6_hdr(skb);
		अगर (!mld2q->mld2q_nsrcs)
			group = &mld2q->mld2q_mca;
		अगर (br->multicast_mld_version == 2 &&
		    !ipv6_addr_any(&mld2q->mld2q_mca) &&
		    mld2q->mld2q_suppress)
			जाओ out;

		max_delay = max(msecs_to_jअगरfies(mldv2_mrc(mld2q)), 1UL);
	पूर्ण

	is_general_query = group && ipv6_addr_any(group);

	अगर (is_general_query) अणु
		saddr.proto = htons(ETH_P_IPV6);
		saddr.src.ip6 = ipv6_hdr(skb)->saddr;

		br_multicast_query_received(br, port, &br->ip6_other_query,
					    &saddr, max_delay);
		जाओ out;
	पूर्ण अन्यथा अगर (!group) अणु
		जाओ out;
	पूर्ण

	mp = br_mdb_ip6_get(br, group, vid);
	अगर (!mp)
		जाओ out;

	max_delay *= br->multicast_last_member_count;
	अगर (mp->host_joined &&
	    (समयr_pending(&mp->समयr) ?
	     समय_after(mp->समयr.expires, now + max_delay) :
	     try_to_del_समयr_sync(&mp->समयr) >= 0))
		mod_समयr(&mp->समयr, now + max_delay);

	क्रम (pp = &mp->ports;
	     (p = mlock_dereference(*pp, br)) != शून्य;
	     pp = &p->next) अणु
		अगर (समयr_pending(&p->समयr) ?
		    समय_after(p->समयr.expires, now + max_delay) :
		    try_to_del_समयr_sync(&p->समयr) >= 0 &&
		    (br->multicast_mld_version == 1 ||
		     p->filter_mode == MCAST_EXCLUDE))
			mod_समयr(&p->समयr, now + max_delay);
	पूर्ण

out:
	spin_unlock(&br->multicast_lock);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल व्योम
br_multicast_leave_group(काष्ठा net_bridge *br,
			 काष्ठा net_bridge_port *port,
			 काष्ठा br_ip *group,
			 काष्ठा bridge_mcast_other_query *other_query,
			 काष्ठा bridge_mcast_own_query *own_query,
			 स्थिर अचिन्हित अक्षर *src)
अणु
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा net_bridge_port_group *p;
	अचिन्हित दीर्घ now;
	अचिन्हित दीर्घ समय;

	spin_lock(&br->multicast_lock);
	अगर (!netअगर_running(br->dev) ||
	    (port && port->state == BR_STATE_DISABLED))
		जाओ out;

	mp = br_mdb_ip_get(br, group);
	अगर (!mp)
		जाओ out;

	अगर (port && (port->flags & BR_MULTICAST_FAST_LEAVE)) अणु
		काष्ठा net_bridge_port_group __rcu **pp;

		क्रम (pp = &mp->ports;
		     (p = mlock_dereference(*pp, br)) != शून्य;
		     pp = &p->next) अणु
			अगर (!br_port_group_equal(p, port, src))
				जारी;

			अगर (p->flags & MDB_PG_FLAGS_PERMANENT)
				अवरोध;

			p->flags |= MDB_PG_FLAGS_FAST_LEAVE;
			br_multicast_del_pg(mp, p, pp);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (समयr_pending(&other_query->समयr))
		जाओ out;

	अगर (br_opt_get(br, BROPT_MULTICAST_QUERIER)) अणु
		__br_multicast_send_query(br, port, शून्य, शून्य, &mp->addr,
					  false, 0, शून्य);

		समय = jअगरfies + br->multicast_last_member_count *
				 br->multicast_last_member_पूर्णांकerval;

		mod_समयr(&own_query->समयr, समय);

		क्रम (p = mlock_dereference(mp->ports, br);
		     p != शून्य;
		     p = mlock_dereference(p->next, br)) अणु
			अगर (!br_port_group_equal(p, port, src))
				जारी;

			अगर (!hlist_unhashed(&p->mglist) &&
			    (समयr_pending(&p->समयr) ?
			     समय_after(p->समयr.expires, समय) :
			     try_to_del_समयr_sync(&p->समयr) >= 0)) अणु
				mod_समयr(&p->समयr, समय);
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

	now = jअगरfies;
	समय = now + br->multicast_last_member_count *
		     br->multicast_last_member_पूर्णांकerval;

	अगर (!port) अणु
		अगर (mp->host_joined &&
		    (समयr_pending(&mp->समयr) ?
		     समय_after(mp->समयr.expires, समय) :
		     try_to_del_समयr_sync(&mp->समयr) >= 0)) अणु
			mod_समयr(&mp->समयr, समय);
		पूर्ण

		जाओ out;
	पूर्ण

	क्रम (p = mlock_dereference(mp->ports, br);
	     p != शून्य;
	     p = mlock_dereference(p->next, br)) अणु
		अगर (p->key.port != port)
			जारी;

		अगर (!hlist_unhashed(&p->mglist) &&
		    (समयr_pending(&p->समयr) ?
		     समय_after(p->समयr.expires, समय) :
		     try_to_del_समयr_sync(&p->समयr) >= 0)) अणु
			mod_समयr(&p->समयr, समय);
		पूर्ण

		अवरोध;
	पूर्ण
out:
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_ip4_multicast_leave_group(काष्ठा net_bridge *br,
					 काष्ठा net_bridge_port *port,
					 __be32 group,
					 __u16 vid,
					 स्थिर अचिन्हित अक्षर *src)
अणु
	काष्ठा br_ip br_group;
	काष्ठा bridge_mcast_own_query *own_query;

	अगर (ipv4_is_local_multicast(group))
		वापस;

	own_query = port ? &port->ip4_own_query : &br->ip4_own_query;

	स_रखो(&br_group, 0, माप(br_group));
	br_group.dst.ip4 = group;
	br_group.proto = htons(ETH_P_IP);
	br_group.vid = vid;

	br_multicast_leave_group(br, port, &br_group, &br->ip4_other_query,
				 own_query, src);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम br_ip6_multicast_leave_group(काष्ठा net_bridge *br,
					 काष्ठा net_bridge_port *port,
					 स्थिर काष्ठा in6_addr *group,
					 __u16 vid,
					 स्थिर अचिन्हित अक्षर *src)
अणु
	काष्ठा br_ip br_group;
	काष्ठा bridge_mcast_own_query *own_query;

	अगर (ipv6_addr_is_ll_all_nodes(group))
		वापस;

	own_query = port ? &port->ip6_own_query : &br->ip6_own_query;

	स_रखो(&br_group, 0, माप(br_group));
	br_group.dst.ip6 = *group;
	br_group.proto = htons(ETH_P_IPV6);
	br_group.vid = vid;

	br_multicast_leave_group(br, port, &br_group, &br->ip6_other_query,
				 own_query, src);
पूर्ण
#पूर्ण_अगर

अटल व्योम br_multicast_err_count(स्थिर काष्ठा net_bridge *br,
				   स्थिर काष्ठा net_bridge_port *p,
				   __be16 proto)
अणु
	काष्ठा bridge_mcast_stats __percpu *stats;
	काष्ठा bridge_mcast_stats *pstats;

	अगर (!br_opt_get(br, BROPT_MULTICAST_STATS_ENABLED))
		वापस;

	अगर (p)
		stats = p->mcast_stats;
	अन्यथा
		stats = br->mcast_stats;
	अगर (WARN_ON(!stats))
		वापस;

	pstats = this_cpu_ptr(stats);

	u64_stats_update_begin(&pstats->syncp);
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		pstats->mstats.igmp_parse_errors++;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		pstats->mstats.mld_parse_errors++;
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	u64_stats_update_end(&pstats->syncp);
पूर्ण

अटल व्योम br_multicast_pim(काष्ठा net_bridge *br,
			     काष्ठा net_bridge_port *port,
			     स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक offset = skb_transport_offset(skb);
	काष्ठा pimhdr *pimhdr, _pimhdr;

	pimhdr = skb_header_poपूर्णांकer(skb, offset, माप(_pimhdr), &_pimhdr);
	अगर (!pimhdr || pim_hdr_version(pimhdr) != PIM_VERSION ||
	    pim_hdr_type(pimhdr) != PIM_TYPE_HELLO)
		वापस;

	br_multicast_mark_router(br, port);
पूर्ण

अटल पूर्णांक br_ip4_multicast_mrd_rcv(काष्ठा net_bridge *br,
				    काष्ठा net_bridge_port *port,
				    काष्ठा sk_buff *skb)
अणु
	अगर (ip_hdr(skb)->protocol != IPPROTO_IGMP ||
	    igmp_hdr(skb)->type != IGMP_MRDISC_ADV)
		वापस -ENOMSG;

	br_multicast_mark_router(br, port);

	वापस 0;
पूर्ण

अटल पूर्णांक br_multicast_ipv4_rcv(काष्ठा net_bridge *br,
				 काष्ठा net_bridge_port *port,
				 काष्ठा sk_buff *skb,
				 u16 vid)
अणु
	स्थिर अचिन्हित अक्षर *src;
	काष्ठा igmphdr *ih;
	पूर्णांक err;

	err = ip_mc_check_igmp(skb);

	अगर (err == -ENOMSG) अणु
		अगर (!ipv4_is_local_multicast(ip_hdr(skb)->daddr)) अणु
			BR_INPUT_SKB_CB(skb)->mrouters_only = 1;
		पूर्ण अन्यथा अगर (pim_ipv4_all_pim_routers(ip_hdr(skb)->daddr)) अणु
			अगर (ip_hdr(skb)->protocol == IPPROTO_PIM)
				br_multicast_pim(br, port, skb);
		पूर्ण अन्यथा अगर (ipv4_is_all_snoopers(ip_hdr(skb)->daddr)) अणु
			br_ip4_multicast_mrd_rcv(br, port, skb);
		पूर्ण

		वापस 0;
	पूर्ण अन्यथा अगर (err < 0) अणु
		br_multicast_err_count(br, port, skb->protocol);
		वापस err;
	पूर्ण

	ih = igmp_hdr(skb);
	src = eth_hdr(skb)->h_source;
	BR_INPUT_SKB_CB(skb)->igmp = ih->type;

	चयन (ih->type) अणु
	हाल IGMP_HOST_MEMBERSHIP_REPORT:
	हाल IGMPV2_HOST_MEMBERSHIP_REPORT:
		BR_INPUT_SKB_CB(skb)->mrouters_only = 1;
		err = br_ip4_multicast_add_group(br, port, ih->group, vid, src,
						 true);
		अवरोध;
	हाल IGMPV3_HOST_MEMBERSHIP_REPORT:
		err = br_ip4_multicast_igmp3_report(br, port, skb, vid);
		अवरोध;
	हाल IGMP_HOST_MEMBERSHIP_QUERY:
		br_ip4_multicast_query(br, port, skb, vid);
		अवरोध;
	हाल IGMP_HOST_LEAVE_MESSAGE:
		br_ip4_multicast_leave_group(br, port, ih->group, vid, src);
		अवरोध;
	पूर्ण

	br_multicast_count(br, port, skb, BR_INPUT_SKB_CB(skb)->igmp,
			   BR_MCAST_सूची_RX);

	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम br_ip6_multicast_mrd_rcv(काष्ठा net_bridge *br,
				     काष्ठा net_bridge_port *port,
				     काष्ठा sk_buff *skb)
अणु
	अगर (icmp6_hdr(skb)->icmp6_type != ICMPV6_MRDISC_ADV)
		वापस;

	br_multicast_mark_router(br, port);
पूर्ण

अटल पूर्णांक br_multicast_ipv6_rcv(काष्ठा net_bridge *br,
				 काष्ठा net_bridge_port *port,
				 काष्ठा sk_buff *skb,
				 u16 vid)
अणु
	स्थिर अचिन्हित अक्षर *src;
	काष्ठा mld_msg *mld;
	पूर्णांक err;

	err = ipv6_mc_check_mld(skb);

	अगर (err == -ENOMSG || err == -ENODATA) अणु
		अगर (!ipv6_addr_is_ll_all_nodes(&ipv6_hdr(skb)->daddr))
			BR_INPUT_SKB_CB(skb)->mrouters_only = 1;
		अगर (err == -ENODATA &&
		    ipv6_addr_is_all_snoopers(&ipv6_hdr(skb)->daddr))
			br_ip6_multicast_mrd_rcv(br, port, skb);

		वापस 0;
	पूर्ण अन्यथा अगर (err < 0) अणु
		br_multicast_err_count(br, port, skb->protocol);
		वापस err;
	पूर्ण

	mld = (काष्ठा mld_msg *)skb_transport_header(skb);
	BR_INPUT_SKB_CB(skb)->igmp = mld->mld_type;

	चयन (mld->mld_type) अणु
	हाल ICMPV6_MGM_REPORT:
		src = eth_hdr(skb)->h_source;
		BR_INPUT_SKB_CB(skb)->mrouters_only = 1;
		err = br_ip6_multicast_add_group(br, port, &mld->mld_mca, vid,
						 src, true);
		अवरोध;
	हाल ICMPV6_MLD2_REPORT:
		err = br_ip6_multicast_mld2_report(br, port, skb, vid);
		अवरोध;
	हाल ICMPV6_MGM_QUERY:
		err = br_ip6_multicast_query(br, port, skb, vid);
		अवरोध;
	हाल ICMPV6_MGM_REDUCTION:
		src = eth_hdr(skb)->h_source;
		br_ip6_multicast_leave_group(br, port, &mld->mld_mca, vid, src);
		अवरोध;
	पूर्ण

	br_multicast_count(br, port, skb, BR_INPUT_SKB_CB(skb)->igmp,
			   BR_MCAST_सूची_RX);

	वापस err;
पूर्ण
#पूर्ण_अगर

पूर्णांक br_multicast_rcv(काष्ठा net_bridge *br, काष्ठा net_bridge_port *port,
		     काष्ठा sk_buff *skb, u16 vid)
अणु
	पूर्णांक ret = 0;

	BR_INPUT_SKB_CB(skb)->igmp = 0;
	BR_INPUT_SKB_CB(skb)->mrouters_only = 0;

	अगर (!br_opt_get(br, BROPT_MULTICAST_ENABLED))
		वापस 0;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		ret = br_multicast_ipv4_rcv(br, port, skb, vid);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		ret = br_multicast_ipv6_rcv(br, port, skb, vid);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम br_multicast_query_expired(काष्ठा net_bridge *br,
				       काष्ठा bridge_mcast_own_query *query,
				       काष्ठा bridge_mcast_querier *querier)
अणु
	spin_lock(&br->multicast_lock);
	अगर (query->startup_sent < br->multicast_startup_query_count)
		query->startup_sent++;

	RCU_INIT_POINTER(querier->port, शून्य);
	br_multicast_send_query(br, शून्य, query);
	spin_unlock(&br->multicast_lock);
पूर्ण

अटल व्योम br_ip4_multicast_query_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge *br = from_समयr(br, t, ip4_own_query.समयr);

	br_multicast_query_expired(br, &br->ip4_own_query, &br->ip4_querier);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम br_ip6_multicast_query_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा net_bridge *br = from_समयr(br, t, ip6_own_query.समयr);

	br_multicast_query_expired(br, &br->ip6_own_query, &br->ip6_querier);
पूर्ण
#पूर्ण_अगर

अटल व्योम br_multicast_gc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net_bridge *br = container_of(work, काष्ठा net_bridge,
					     mcast_gc_work);
	HLIST_HEAD(deleted_head);

	spin_lock_bh(&br->multicast_lock);
	hlist_move_list(&br->mcast_gc_list, &deleted_head);
	spin_unlock_bh(&br->multicast_lock);

	br_multicast_gc(&deleted_head);
पूर्ण

व्योम br_multicast_init(काष्ठा net_bridge *br)
अणु
	br->hash_max = BR_MULTICAST_DEFAULT_HASH_MAX;

	br->multicast_router = MDB_RTR_TYPE_TEMP_QUERY;
	br->multicast_last_member_count = 2;
	br->multicast_startup_query_count = 2;

	br->multicast_last_member_पूर्णांकerval = HZ;
	br->multicast_query_response_पूर्णांकerval = 10 * HZ;
	br->multicast_startup_query_पूर्णांकerval = 125 * HZ / 4;
	br->multicast_query_पूर्णांकerval = 125 * HZ;
	br->multicast_querier_पूर्णांकerval = 255 * HZ;
	br->multicast_membership_पूर्णांकerval = 260 * HZ;

	br->ip4_other_query.delay_समय = 0;
	br->ip4_querier.port = शून्य;
	br->multicast_igmp_version = 2;
#अगर IS_ENABLED(CONFIG_IPV6)
	br->multicast_mld_version = 1;
	br->ip6_other_query.delay_समय = 0;
	br->ip6_querier.port = शून्य;
#पूर्ण_अगर
	br_opt_toggle(br, BROPT_MULTICAST_ENABLED, true);
	br_opt_toggle(br, BROPT_HAS_IPV6_ADDR, true);

	spin_lock_init(&br->multicast_lock);
	समयr_setup(&br->multicast_router_समयr,
		    br_multicast_local_router_expired, 0);
	समयr_setup(&br->ip4_other_query.समयr,
		    br_ip4_multicast_querier_expired, 0);
	समयr_setup(&br->ip4_own_query.समयr,
		    br_ip4_multicast_query_expired, 0);
#अगर IS_ENABLED(CONFIG_IPV6)
	समयr_setup(&br->ip6_other_query.समयr,
		    br_ip6_multicast_querier_expired, 0);
	समयr_setup(&br->ip6_own_query.समयr,
		    br_ip6_multicast_query_expired, 0);
#पूर्ण_अगर
	INIT_HLIST_HEAD(&br->mdb_list);
	INIT_HLIST_HEAD(&br->mcast_gc_list);
	INIT_WORK(&br->mcast_gc_work, br_multicast_gc_work);
पूर्ण

अटल व्योम br_ip4_multicast_join_snoopers(काष्ठा net_bridge *br)
अणु
	काष्ठा in_device *in_dev = in_dev_get(br->dev);

	अगर (!in_dev)
		वापस;

	__ip_mc_inc_group(in_dev, htonl(INADDR_ALLSNOOPERS_GROUP), GFP_ATOMIC);
	in_dev_put(in_dev);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम br_ip6_multicast_join_snoopers(काष्ठा net_bridge *br)
अणु
	काष्ठा in6_addr addr;

	ipv6_addr_set(&addr, htonl(0xff020000), 0, 0, htonl(0x6a));
	ipv6_dev_mc_inc(br->dev, &addr);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम br_ip6_multicast_join_snoopers(काष्ठा net_bridge *br)
अणु
पूर्ण
#पूर्ण_अगर

व्योम br_multicast_join_snoopers(काष्ठा net_bridge *br)
अणु
	br_ip4_multicast_join_snoopers(br);
	br_ip6_multicast_join_snoopers(br);
पूर्ण

अटल व्योम br_ip4_multicast_leave_snoopers(काष्ठा net_bridge *br)
अणु
	काष्ठा in_device *in_dev = in_dev_get(br->dev);

	अगर (WARN_ON(!in_dev))
		वापस;

	__ip_mc_dec_group(in_dev, htonl(INADDR_ALLSNOOPERS_GROUP), GFP_ATOMIC);
	in_dev_put(in_dev);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम br_ip6_multicast_leave_snoopers(काष्ठा net_bridge *br)
अणु
	काष्ठा in6_addr addr;

	ipv6_addr_set(&addr, htonl(0xff020000), 0, 0, htonl(0x6a));
	ipv6_dev_mc_dec(br->dev, &addr);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम br_ip6_multicast_leave_snoopers(काष्ठा net_bridge *br)
अणु
पूर्ण
#पूर्ण_अगर

व्योम br_multicast_leave_snoopers(काष्ठा net_bridge *br)
अणु
	br_ip4_multicast_leave_snoopers(br);
	br_ip6_multicast_leave_snoopers(br);
पूर्ण

अटल व्योम __br_multicast_खोलो(काष्ठा net_bridge *br,
				काष्ठा bridge_mcast_own_query *query)
अणु
	query->startup_sent = 0;

	अगर (!br_opt_get(br, BROPT_MULTICAST_ENABLED))
		वापस;

	mod_समयr(&query->समयr, jअगरfies);
पूर्ण

व्योम br_multicast_खोलो(काष्ठा net_bridge *br)
अणु
	__br_multicast_खोलो(br, &br->ip4_own_query);
#अगर IS_ENABLED(CONFIG_IPV6)
	__br_multicast_खोलो(br, &br->ip6_own_query);
#पूर्ण_अगर
पूर्ण

व्योम br_multicast_stop(काष्ठा net_bridge *br)
अणु
	del_समयr_sync(&br->multicast_router_समयr);
	del_समयr_sync(&br->ip4_other_query.समयr);
	del_समयr_sync(&br->ip4_own_query.समयr);
#अगर IS_ENABLED(CONFIG_IPV6)
	del_समयr_sync(&br->ip6_other_query.समयr);
	del_समयr_sync(&br->ip6_own_query.समयr);
#पूर्ण_अगर
पूर्ण

व्योम br_multicast_dev_del(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_mdb_entry *mp;
	HLIST_HEAD(deleted_head);
	काष्ठा hlist_node *पंचांगp;

	spin_lock_bh(&br->multicast_lock);
	hlist_क्रम_each_entry_safe(mp, पंचांगp, &br->mdb_list, mdb_node)
		br_multicast_del_mdb_entry(mp);
	hlist_move_list(&br->mcast_gc_list, &deleted_head);
	spin_unlock_bh(&br->multicast_lock);

	br_multicast_gc(&deleted_head);
	cancel_work_sync(&br->mcast_gc_work);

	rcu_barrier();
पूर्ण

पूर्णांक br_multicast_set_router(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	पूर्णांक err = -EINVAL;

	spin_lock_bh(&br->multicast_lock);

	चयन (val) अणु
	हाल MDB_RTR_TYPE_DISABLED:
	हाल MDB_RTR_TYPE_PERM:
		br_mc_router_state_change(br, val == MDB_RTR_TYPE_PERM);
		del_समयr(&br->multicast_router_समयr);
		br->multicast_router = val;
		err = 0;
		अवरोध;
	हाल MDB_RTR_TYPE_TEMP_QUERY:
		अगर (br->multicast_router != MDB_RTR_TYPE_TEMP_QUERY)
			br_mc_router_state_change(br, false);
		br->multicast_router = val;
		err = 0;
		अवरोध;
	पूर्ण

	spin_unlock_bh(&br->multicast_lock);

	वापस err;
पूर्ण

अटल व्योम __del_port_router(काष्ठा net_bridge_port *p)
अणु
	अगर (hlist_unhashed(&p->rlist))
		वापस;
	hlist_del_init_rcu(&p->rlist);
	br_rtr_notअगरy(p->br->dev, p, RTM_DELMDB);
	br_port_mc_router_state_change(p, false);

	/* करोn't allow समयr refresh */
	अगर (p->multicast_router == MDB_RTR_TYPE_TEMP)
		p->multicast_router = MDB_RTR_TYPE_TEMP_QUERY;
पूर्ण

पूर्णांक br_multicast_set_port_router(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ val)
अणु
	काष्ठा net_bridge *br = p->br;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक err = -EINVAL;

	spin_lock(&br->multicast_lock);
	अगर (p->multicast_router == val) अणु
		/* Refresh the temp router port समयr */
		अगर (p->multicast_router == MDB_RTR_TYPE_TEMP)
			mod_समयr(&p->multicast_router_समयr,
				  now + br->multicast_querier_पूर्णांकerval);
		err = 0;
		जाओ unlock;
	पूर्ण
	चयन (val) अणु
	हाल MDB_RTR_TYPE_DISABLED:
		p->multicast_router = MDB_RTR_TYPE_DISABLED;
		__del_port_router(p);
		del_समयr(&p->multicast_router_समयr);
		अवरोध;
	हाल MDB_RTR_TYPE_TEMP_QUERY:
		p->multicast_router = MDB_RTR_TYPE_TEMP_QUERY;
		__del_port_router(p);
		अवरोध;
	हाल MDB_RTR_TYPE_PERM:
		p->multicast_router = MDB_RTR_TYPE_PERM;
		del_समयr(&p->multicast_router_समयr);
		br_multicast_add_router(br, p);
		अवरोध;
	हाल MDB_RTR_TYPE_TEMP:
		p->multicast_router = MDB_RTR_TYPE_TEMP;
		br_multicast_mark_router(br, p);
		अवरोध;
	शेष:
		जाओ unlock;
	पूर्ण
	err = 0;
unlock:
	spin_unlock(&br->multicast_lock);

	वापस err;
पूर्ण

अटल व्योम br_multicast_start_querier(काष्ठा net_bridge *br,
				       काष्ठा bridge_mcast_own_query *query)
अणु
	काष्ठा net_bridge_port *port;

	__br_multicast_खोलो(br, query);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(port, &br->port_list, list) अणु
		अगर (port->state == BR_STATE_DISABLED ||
		    port->state == BR_STATE_BLOCKING)
			जारी;

		अगर (query == &br->ip4_own_query)
			br_multicast_enable(&port->ip4_own_query);
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा
			br_multicast_enable(&port->ip6_own_query);
#पूर्ण_अगर
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक br_multicast_toggle(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_port *port;
	bool change_snoopers = false;
	पूर्णांक err = 0;

	spin_lock_bh(&br->multicast_lock);
	अगर (!!br_opt_get(br, BROPT_MULTICAST_ENABLED) == !!val)
		जाओ unlock;

	err = br_mc_disabled_update(br->dev, val, extack);
	अगर (err == -EOPNOTSUPP)
		err = 0;
	अगर (err)
		जाओ unlock;

	br_opt_toggle(br, BROPT_MULTICAST_ENABLED, !!val);
	अगर (!br_opt_get(br, BROPT_MULTICAST_ENABLED)) अणु
		change_snoopers = true;
		जाओ unlock;
	पूर्ण

	अगर (!netअगर_running(br->dev))
		जाओ unlock;

	br_multicast_खोलो(br);
	list_क्रम_each_entry(port, &br->port_list, list)
		__br_multicast_enable_port(port);

	change_snoopers = true;

unlock:
	spin_unlock_bh(&br->multicast_lock);

	/* br_multicast_join_snoopers has the potential to cause
	 * an MLD Report/Leave to be delivered to br_multicast_rcv,
	 * which would in turn call br_multicast_add_group, which would
	 * attempt to acquire multicast_lock. This function should be
	 * called after the lock has been released to aव्योम deadlocks on
	 * multicast_lock.
	 *
	 * br_multicast_leave_snoopers करोes not have the problem since
	 * br_multicast_rcv first checks BROPT_MULTICAST_ENABLED, and
	 * वापसs without calling br_multicast_ipv4/6_rcv अगर it's not
	 * enabled. Moved both functions out just क्रम symmetry.
	 */
	अगर (change_snoopers) अणु
		अगर (br_opt_get(br, BROPT_MULTICAST_ENABLED))
			br_multicast_join_snoopers(br);
		अन्यथा
			br_multicast_leave_snoopers(br);
	पूर्ण

	वापस err;
पूर्ण

bool br_multicast_enabled(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	वापस !!br_opt_get(br, BROPT_MULTICAST_ENABLED);
पूर्ण
EXPORT_SYMBOL_GPL(br_multicast_enabled);

bool br_multicast_router(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	bool is_router;

	spin_lock_bh(&br->multicast_lock);
	is_router = br_multicast_is_router(br);
	spin_unlock_bh(&br->multicast_lock);
	वापस is_router;
पूर्ण
EXPORT_SYMBOL_GPL(br_multicast_router);

पूर्णांक br_multicast_set_querier(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ max_delay;

	val = !!val;

	spin_lock_bh(&br->multicast_lock);
	अगर (br_opt_get(br, BROPT_MULTICAST_QUERIER) == val)
		जाओ unlock;

	br_opt_toggle(br, BROPT_MULTICAST_QUERIER, !!val);
	अगर (!val)
		जाओ unlock;

	max_delay = br->multicast_query_response_पूर्णांकerval;

	अगर (!समयr_pending(&br->ip4_other_query.समयr))
		br->ip4_other_query.delay_समय = jअगरfies + max_delay;

	br_multicast_start_querier(br, &br->ip4_own_query);

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (!समयr_pending(&br->ip6_other_query.समयr))
		br->ip6_other_query.delay_समय = jअगरfies + max_delay;

	br_multicast_start_querier(br, &br->ip6_own_query);
#पूर्ण_अगर

unlock:
	spin_unlock_bh(&br->multicast_lock);

	वापस 0;
पूर्ण

पूर्णांक br_multicast_set_igmp_version(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	/* Currently we support only version 2 and 3 */
	चयन (val) अणु
	हाल 2:
	हाल 3:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&br->multicast_lock);
	br->multicast_igmp_version = val;
	spin_unlock_bh(&br->multicast_lock);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक br_multicast_set_mld_version(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	/* Currently we support version 1 and 2 */
	चयन (val) अणु
	हाल 1:
	हाल 2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&br->multicast_lock);
	br->multicast_mld_version = val;
	spin_unlock_bh(&br->multicast_lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * br_multicast_list_adjacent - Returns snooped multicast addresses
 * @dev:	The bridge port adjacent to which to retrieve addresses
 * @br_ip_list:	The list to store found, snooped multicast IP addresses in
 *
 * Creates a list of IP addresses (काष्ठा br_ip_list) sensed by the multicast
 * snooping feature on all bridge ports of dev's bridge device, excluding
 * the addresses from dev itself.
 *
 * Returns the number of items added to br_ip_list.
 *
 * Notes:
 * - br_ip_list needs to be initialized by caller
 * - br_ip_list might contain duplicates in the end
 *   (needs to be taken care of by caller)
 * - br_ip_list needs to be मुक्तd by caller
 */
पूर्णांक br_multicast_list_adjacent(काष्ठा net_device *dev,
			       काष्ठा list_head *br_ip_list)
अणु
	काष्ठा net_bridge *br;
	काष्ठा net_bridge_port *port;
	काष्ठा net_bridge_port_group *group;
	काष्ठा br_ip_list *entry;
	पूर्णांक count = 0;

	rcu_पढ़ो_lock();
	अगर (!br_ip_list || !netअगर_is_bridge_port(dev))
		जाओ unlock;

	port = br_port_get_rcu(dev);
	अगर (!port || !port->br)
		जाओ unlock;

	br = port->br;

	list_क्रम_each_entry_rcu(port, &br->port_list, list) अणु
		अगर (!port->dev || port->dev == dev)
			जारी;

		hlist_क्रम_each_entry_rcu(group, &port->mglist, mglist) अणु
			entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
			अगर (!entry)
				जाओ unlock;

			entry->addr = group->key.addr;
			list_add(&entry->list, br_ip_list);
			count++;
		पूर्ण
	पूर्ण

unlock:
	rcu_पढ़ो_unlock();
	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(br_multicast_list_adjacent);

/**
 * br_multicast_has_querier_anywhere - Checks क्रम a querier on a bridge
 * @dev: The bridge port providing the bridge on which to check क्रम a querier
 * @proto: The protocol family to check क्रम: IGMP -> ETH_P_IP, MLD -> ETH_P_IPV6
 *
 * Checks whether the given पूर्णांकerface has a bridge on top and अगर so वापसs
 * true अगर a valid querier exists anywhere on the bridged link layer.
 * Otherwise वापसs false.
 */
bool br_multicast_has_querier_anywhere(काष्ठा net_device *dev, पूर्णांक proto)
अणु
	काष्ठा net_bridge *br;
	काष्ठा net_bridge_port *port;
	काष्ठा ethhdr eth;
	bool ret = false;

	rcu_पढ़ो_lock();
	अगर (!netअगर_is_bridge_port(dev))
		जाओ unlock;

	port = br_port_get_rcu(dev);
	अगर (!port || !port->br)
		जाओ unlock;

	br = port->br;

	स_रखो(&eth, 0, माप(eth));
	eth.h_proto = htons(proto);

	ret = br_multicast_querier_exists(br, &eth, शून्य);

unlock:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(br_multicast_has_querier_anywhere);

/**
 * br_multicast_has_querier_adjacent - Checks क्रम a querier behind a bridge port
 * @dev: The bridge port adjacent to which to check क्रम a querier
 * @proto: The protocol family to check क्रम: IGMP -> ETH_P_IP, MLD -> ETH_P_IPV6
 *
 * Checks whether the given पूर्णांकerface has a bridge on top and अगर so वापसs
 * true अगर a selected querier is behind one of the other ports of this
 * bridge. Otherwise वापसs false.
 */
bool br_multicast_has_querier_adjacent(काष्ठा net_device *dev, पूर्णांक proto)
अणु
	काष्ठा net_bridge *br;
	काष्ठा net_bridge_port *port;
	bool ret = false;

	rcu_पढ़ो_lock();
	अगर (!netअगर_is_bridge_port(dev))
		जाओ unlock;

	port = br_port_get_rcu(dev);
	अगर (!port || !port->br)
		जाओ unlock;

	br = port->br;

	चयन (proto) अणु
	हाल ETH_P_IP:
		अगर (!समयr_pending(&br->ip4_other_query.समयr) ||
		    rcu_dereference(br->ip4_querier.port) == port)
			जाओ unlock;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल ETH_P_IPV6:
		अगर (!समयr_pending(&br->ip6_other_query.समयr) ||
		    rcu_dereference(br->ip6_querier.port) == port)
			जाओ unlock;
		अवरोध;
#पूर्ण_अगर
	शेष:
		जाओ unlock;
	पूर्ण

	ret = true;
unlock:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(br_multicast_has_querier_adjacent);

अटल व्योम br_mcast_stats_add(काष्ठा bridge_mcast_stats __percpu *stats,
			       स्थिर काष्ठा sk_buff *skb, u8 type, u8 dir)
अणु
	काष्ठा bridge_mcast_stats *pstats = this_cpu_ptr(stats);
	__be16 proto = skb->protocol;
	अचिन्हित पूर्णांक t_len;

	u64_stats_update_begin(&pstats->syncp);
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		t_len = ntohs(ip_hdr(skb)->tot_len) - ip_hdrlen(skb);
		चयन (type) अणु
		हाल IGMP_HOST_MEMBERSHIP_REPORT:
			pstats->mstats.igmp_v1reports[dir]++;
			अवरोध;
		हाल IGMPV2_HOST_MEMBERSHIP_REPORT:
			pstats->mstats.igmp_v2reports[dir]++;
			अवरोध;
		हाल IGMPV3_HOST_MEMBERSHIP_REPORT:
			pstats->mstats.igmp_v3reports[dir]++;
			अवरोध;
		हाल IGMP_HOST_MEMBERSHIP_QUERY:
			अगर (t_len != माप(काष्ठा igmphdr)) अणु
				pstats->mstats.igmp_v3queries[dir]++;
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक offset = skb_transport_offset(skb);
				काष्ठा igmphdr *ih, _ihdr;

				ih = skb_header_poपूर्णांकer(skb, offset,
							माप(_ihdr), &_ihdr);
				अगर (!ih)
					अवरोध;
				अगर (!ih->code)
					pstats->mstats.igmp_v1queries[dir]++;
				अन्यथा
					pstats->mstats.igmp_v2queries[dir]++;
			पूर्ण
			अवरोध;
		हाल IGMP_HOST_LEAVE_MESSAGE:
			pstats->mstats.igmp_leaves[dir]++;
			अवरोध;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		t_len = ntohs(ipv6_hdr(skb)->payload_len) +
			माप(काष्ठा ipv6hdr);
		t_len -= skb_network_header_len(skb);
		चयन (type) अणु
		हाल ICMPV6_MGM_REPORT:
			pstats->mstats.mld_v1reports[dir]++;
			अवरोध;
		हाल ICMPV6_MLD2_REPORT:
			pstats->mstats.mld_v2reports[dir]++;
			अवरोध;
		हाल ICMPV6_MGM_QUERY:
			अगर (t_len != माप(काष्ठा mld_msg))
				pstats->mstats.mld_v2queries[dir]++;
			अन्यथा
				pstats->mstats.mld_v1queries[dir]++;
			अवरोध;
		हाल ICMPV6_MGM_REDUCTION:
			pstats->mstats.mld_leaves[dir]++;
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* CONFIG_IPV6 */
	पूर्ण
	u64_stats_update_end(&pstats->syncp);
पूर्ण

व्योम br_multicast_count(काष्ठा net_bridge *br, स्थिर काष्ठा net_bridge_port *p,
			स्थिर काष्ठा sk_buff *skb, u8 type, u8 dir)
अणु
	काष्ठा bridge_mcast_stats __percpu *stats;

	/* अगर multicast_disabled is true then igmp type can't be set */
	अगर (!type || !br_opt_get(br, BROPT_MULTICAST_STATS_ENABLED))
		वापस;

	अगर (p)
		stats = p->mcast_stats;
	अन्यथा
		stats = br->mcast_stats;
	अगर (WARN_ON(!stats))
		वापस;

	br_mcast_stats_add(stats, skb, type, dir);
पूर्ण

पूर्णांक br_multicast_init_stats(काष्ठा net_bridge *br)
अणु
	br->mcast_stats = netdev_alloc_pcpu_stats(काष्ठा bridge_mcast_stats);
	अगर (!br->mcast_stats)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम br_multicast_uninit_stats(काष्ठा net_bridge *br)
अणु
	मुक्त_percpu(br->mcast_stats);
पूर्ण

/* noअंतरभूत क्रम https://bugs.llvm.org/show_bug.cgi?id=45802#c9 */
अटल noअंतरभूत_क्रम_stack व्योम mcast_stats_add_dir(u64 *dst, u64 *src)
अणु
	dst[BR_MCAST_सूची_RX] += src[BR_MCAST_सूची_RX];
	dst[BR_MCAST_सूची_TX] += src[BR_MCAST_सूची_TX];
पूर्ण

व्योम br_multicast_get_stats(स्थिर काष्ठा net_bridge *br,
			    स्थिर काष्ठा net_bridge_port *p,
			    काष्ठा br_mcast_stats *dest)
अणु
	काष्ठा bridge_mcast_stats __percpu *stats;
	काष्ठा br_mcast_stats tdst;
	पूर्णांक i;

	स_रखो(dest, 0, माप(*dest));
	अगर (p)
		stats = p->mcast_stats;
	अन्यथा
		stats = br->mcast_stats;
	अगर (WARN_ON(!stats))
		वापस;

	स_रखो(&tdst, 0, माप(tdst));
	क्रम_each_possible_cpu(i) अणु
		काष्ठा bridge_mcast_stats *cpu_stats = per_cpu_ptr(stats, i);
		काष्ठा br_mcast_stats temp;
		अचिन्हित पूर्णांक start;

		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			स_नकल(&temp, &cpu_stats->mstats, माप(temp));
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		mcast_stats_add_dir(tdst.igmp_v1queries, temp.igmp_v1queries);
		mcast_stats_add_dir(tdst.igmp_v2queries, temp.igmp_v2queries);
		mcast_stats_add_dir(tdst.igmp_v3queries, temp.igmp_v3queries);
		mcast_stats_add_dir(tdst.igmp_leaves, temp.igmp_leaves);
		mcast_stats_add_dir(tdst.igmp_v1reports, temp.igmp_v1reports);
		mcast_stats_add_dir(tdst.igmp_v2reports, temp.igmp_v2reports);
		mcast_stats_add_dir(tdst.igmp_v3reports, temp.igmp_v3reports);
		tdst.igmp_parse_errors += temp.igmp_parse_errors;

		mcast_stats_add_dir(tdst.mld_v1queries, temp.mld_v1queries);
		mcast_stats_add_dir(tdst.mld_v2queries, temp.mld_v2queries);
		mcast_stats_add_dir(tdst.mld_leaves, temp.mld_leaves);
		mcast_stats_add_dir(tdst.mld_v1reports, temp.mld_v1reports);
		mcast_stats_add_dir(tdst.mld_v2reports, temp.mld_v2reports);
		tdst.mld_parse_errors += temp.mld_parse_errors;
	पूर्ण
	स_नकल(dest, &tdst, माप(*dest));
पूर्ण

पूर्णांक br_mdb_hash_init(काष्ठा net_bridge *br)
अणु
	पूर्णांक err;

	err = rhashtable_init(&br->sg_port_tbl, &br_sg_port_rht_params);
	अगर (err)
		वापस err;

	err = rhashtable_init(&br->mdb_hash_tbl, &br_mdb_rht_params);
	अगर (err) अणु
		rhashtable_destroy(&br->sg_port_tbl);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम br_mdb_hash_fini(काष्ठा net_bridge *br)
अणु
	rhashtable_destroy(&br->sg_port_tbl);
	rhashtable_destroy(&br->mdb_hash_tbl);
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <linux/igmp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/ip.h>
#समावेश <net/netlink.h>
#समावेश <net/चयनdev.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#पूर्ण_अगर

#समावेश "br_private.h"

अटल पूर्णांक br_rports_fill_info(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			       काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_port *p;
	काष्ठा nlattr *nest, *port_nest;

	अगर (!br->multicast_router || hlist_empty(&br->router_list))
		वापस 0;

	nest = nla_nest_start_noflag(skb, MDBA_ROUTER);
	अगर (nest == शून्य)
		वापस -EMSGSIZE;

	hlist_क्रम_each_entry_rcu(p, &br->router_list, rlist) अणु
		अगर (!p)
			जारी;
		port_nest = nla_nest_start_noflag(skb, MDBA_ROUTER_PORT);
		अगर (!port_nest)
			जाओ fail;
		अगर (nla_put_nohdr(skb, माप(u32), &p->dev->अगरindex) ||
		    nla_put_u32(skb, MDBA_ROUTER_PATTR_TIMER,
				br_समयr_value(&p->multicast_router_समयr)) ||
		    nla_put_u8(skb, MDBA_ROUTER_PATTR_TYPE,
			       p->multicast_router)) अणु
			nla_nest_cancel(skb, port_nest);
			जाओ fail;
		पूर्ण
		nla_nest_end(skb, port_nest);
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;
fail:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम __mdb_entry_fill_flags(काष्ठा br_mdb_entry *e, अचिन्हित अक्षर flags)
अणु
	e->state = flags & MDB_PG_FLAGS_PERMANENT;
	e->flags = 0;
	अगर (flags & MDB_PG_FLAGS_OFFLOAD)
		e->flags |= MDB_FLAGS_OFFLOAD;
	अगर (flags & MDB_PG_FLAGS_FAST_LEAVE)
		e->flags |= MDB_FLAGS_FAST_LEAVE;
	अगर (flags & MDB_PG_FLAGS_STAR_EXCL)
		e->flags |= MDB_FLAGS_STAR_EXCL;
	अगर (flags & MDB_PG_FLAGS_BLOCKED)
		e->flags |= MDB_FLAGS_BLOCKED;
पूर्ण

अटल व्योम __mdb_entry_to_br_ip(काष्ठा br_mdb_entry *entry, काष्ठा br_ip *ip,
				 काष्ठा nlattr **mdb_attrs)
अणु
	स_रखो(ip, 0, माप(काष्ठा br_ip));
	ip->vid = entry->vid;
	ip->proto = entry->addr.proto;
	चयन (ip->proto) अणु
	हाल htons(ETH_P_IP):
		ip->dst.ip4 = entry->addr.u.ip4;
		अगर (mdb_attrs && mdb_attrs[MDBE_ATTR_SOURCE])
			ip->src.ip4 = nla_get_in_addr(mdb_attrs[MDBE_ATTR_SOURCE]);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		ip->dst.ip6 = entry->addr.u.ip6;
		अगर (mdb_attrs && mdb_attrs[MDBE_ATTR_SOURCE])
			ip->src.ip6 = nla_get_in6_addr(mdb_attrs[MDBE_ATTR_SOURCE]);
		अवरोध;
#पूर्ण_अगर
	शेष:
		ether_addr_copy(ip->dst.mac_addr, entry->addr.u.mac_addr);
	पूर्ण

पूर्ण

अटल पूर्णांक __mdb_fill_srcs(काष्ठा sk_buff *skb,
			   काष्ठा net_bridge_port_group *p)
अणु
	काष्ठा net_bridge_group_src *ent;
	काष्ठा nlattr *nest, *nest_ent;

	अगर (hlist_empty(&p->src_list))
		वापस 0;

	nest = nla_nest_start(skb, MDBA_MDB_EATTR_SRC_LIST);
	अगर (!nest)
		वापस -EMSGSIZE;

	hlist_क्रम_each_entry_rcu(ent, &p->src_list, node,
				 lockdep_is_held(&p->key.port->br->multicast_lock)) अणु
		nest_ent = nla_nest_start(skb, MDBA_MDB_SRCLIST_ENTRY);
		अगर (!nest_ent)
			जाओ out_cancel_err;
		चयन (ent->addr.proto) अणु
		हाल htons(ETH_P_IP):
			अगर (nla_put_in_addr(skb, MDBA_MDB_SRCATTR_ADDRESS,
					    ent->addr.src.ip4)) अणु
				nla_nest_cancel(skb, nest_ent);
				जाओ out_cancel_err;
			पूर्ण
			अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
		हाल htons(ETH_P_IPV6):
			अगर (nla_put_in6_addr(skb, MDBA_MDB_SRCATTR_ADDRESS,
					     &ent->addr.src.ip6)) अणु
				nla_nest_cancel(skb, nest_ent);
				जाओ out_cancel_err;
			पूर्ण
			अवरोध;
#पूर्ण_अगर
		शेष:
			nla_nest_cancel(skb, nest_ent);
			जारी;
		पूर्ण
		अगर (nla_put_u32(skb, MDBA_MDB_SRCATTR_TIMER,
				br_समयr_value(&ent->समयr))) अणु
			nla_nest_cancel(skb, nest_ent);
			जाओ out_cancel_err;
		पूर्ण
		nla_nest_end(skb, nest_ent);
	पूर्ण

	nla_nest_end(skb, nest);

	वापस 0;

out_cancel_err:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक __mdb_fill_info(काष्ठा sk_buff *skb,
			   काष्ठा net_bridge_mdb_entry *mp,
			   काष्ठा net_bridge_port_group *p)
अणु
	bool dump_srcs_mode = false;
	काष्ठा समयr_list *mसमयr;
	काष्ठा nlattr *nest_ent;
	काष्ठा br_mdb_entry e;
	u8 flags = 0;
	पूर्णांक अगरindex;

	स_रखो(&e, 0, माप(e));
	अगर (p) अणु
		अगरindex = p->key.port->dev->अगरindex;
		mसमयr = &p->समयr;
		flags = p->flags;
	पूर्ण अन्यथा अणु
		अगरindex = mp->br->dev->अगरindex;
		mसमयr = &mp->समयr;
	पूर्ण

	__mdb_entry_fill_flags(&e, flags);
	e.अगरindex = अगरindex;
	e.vid = mp->addr.vid;
	अगर (mp->addr.proto == htons(ETH_P_IP))
		e.addr.u.ip4 = mp->addr.dst.ip4;
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (mp->addr.proto == htons(ETH_P_IPV6))
		e.addr.u.ip6 = mp->addr.dst.ip6;
#पूर्ण_अगर
	अन्यथा
		ether_addr_copy(e.addr.u.mac_addr, mp->addr.dst.mac_addr);
	e.addr.proto = mp->addr.proto;
	nest_ent = nla_nest_start_noflag(skb,
					 MDBA_MDB_ENTRY_INFO);
	अगर (!nest_ent)
		वापस -EMSGSIZE;

	अगर (nla_put_nohdr(skb, माप(e), &e) ||
	    nla_put_u32(skb,
			MDBA_MDB_EATTR_TIMER,
			br_समयr_value(mसमयr)))
		जाओ nest_err;

	चयन (mp->addr.proto) अणु
	हाल htons(ETH_P_IP):
		dump_srcs_mode = !!(mp->br->multicast_igmp_version == 3);
		अगर (mp->addr.src.ip4) अणु
			अगर (nla_put_in_addr(skb, MDBA_MDB_EATTR_SOURCE,
					    mp->addr.src.ip4))
				जाओ nest_err;
			अवरोध;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		dump_srcs_mode = !!(mp->br->multicast_mld_version == 2);
		अगर (!ipv6_addr_any(&mp->addr.src.ip6)) अणु
			अगर (nla_put_in6_addr(skb, MDBA_MDB_EATTR_SOURCE,
					     &mp->addr.src.ip6))
				जाओ nest_err;
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		ether_addr_copy(e.addr.u.mac_addr, mp->addr.dst.mac_addr);
	पूर्ण
	अगर (p) अणु
		अगर (nla_put_u8(skb, MDBA_MDB_EATTR_RTPROT, p->rt_protocol))
			जाओ nest_err;
		अगर (dump_srcs_mode &&
		    (__mdb_fill_srcs(skb, p) ||
		     nla_put_u8(skb, MDBA_MDB_EATTR_GROUP_MODE,
				p->filter_mode)))
			जाओ nest_err;
	पूर्ण
	nla_nest_end(skb, nest_ent);

	वापस 0;

nest_err:
	nla_nest_cancel(skb, nest_ent);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक br_mdb_fill_info(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			    काष्ठा net_device *dev)
अणु
	पूर्णांक idx = 0, s_idx = cb->args[1], err = 0, pidx = 0, s_pidx = cb->args[2];
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा nlattr *nest, *nest2;

	अगर (!br_opt_get(br, BROPT_MULTICAST_ENABLED))
		वापस 0;

	nest = nla_nest_start_noflag(skb, MDBA_MDB);
	अगर (nest == शून्य)
		वापस -EMSGSIZE;

	hlist_क्रम_each_entry_rcu(mp, &br->mdb_list, mdb_node) अणु
		काष्ठा net_bridge_port_group *p;
		काष्ठा net_bridge_port_group __rcu **pp;

		अगर (idx < s_idx)
			जाओ skip;

		nest2 = nla_nest_start_noflag(skb, MDBA_MDB_ENTRY);
		अगर (!nest2) अणु
			err = -EMSGSIZE;
			अवरोध;
		पूर्ण

		अगर (!s_pidx && mp->host_joined) अणु
			err = __mdb_fill_info(skb, mp, शून्य);
			अगर (err) अणु
				nla_nest_cancel(skb, nest2);
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (pp = &mp->ports; (p = rcu_dereference(*pp)) != शून्य;
		      pp = &p->next) अणु
			अगर (!p->key.port)
				जारी;
			अगर (pidx < s_pidx)
				जाओ skip_pg;

			err = __mdb_fill_info(skb, mp, p);
			अगर (err) अणु
				nla_nest_end(skb, nest2);
				जाओ out;
			पूर्ण
skip_pg:
			pidx++;
		पूर्ण
		pidx = 0;
		s_pidx = 0;
		nla_nest_end(skb, nest2);
skip:
		idx++;
	पूर्ण

out:
	cb->args[1] = idx;
	cb->args[2] = pidx;
	nla_nest_end(skb, nest);
	वापस err;
पूर्ण

अटल पूर्णांक br_mdb_valid_dump_req(स्थिर काष्ठा nlmsghdr *nlh,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा br_port_msg *bpm;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*bpm))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid header for mdb dump request");
		वापस -EINVAL;
	पूर्ण

	bpm = nlmsg_data(nlh);
	अगर (bpm->अगरindex) अणु
		NL_SET_ERR_MSG_MOD(extack, "Filtering by device index is not supported for mdb dump request");
		वापस -EINVAL;
	पूर्ण
	अगर (nlmsg_attrlen(nlh, माप(*bpm))) अणु
		NL_SET_ERR_MSG(extack, "Invalid data after header in mdb dump request");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक br_mdb_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net_device *dev;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlmsghdr *nlh = शून्य;
	पूर्णांक idx = 0, s_idx;

	अगर (cb->strict_check) अणु
		पूर्णांक err = br_mdb_valid_dump_req(cb->nlh, cb->extack);

		अगर (err < 0)
			वापस err;
	पूर्ण

	s_idx = cb->args[0];

	rcu_पढ़ो_lock();

	cb->seq = net->dev_base_seq;

	क्रम_each_netdev_rcu(net, dev) अणु
		अगर (dev->priv_flags & IFF_EBRIDGE) अणु
			काष्ठा br_port_msg *bpm;

			अगर (idx < s_idx)
				जाओ skip;

			nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq, RTM_GETMDB,
					माप(*bpm), NLM_F_MULTI);
			अगर (nlh == शून्य)
				अवरोध;

			bpm = nlmsg_data(nlh);
			स_रखो(bpm, 0, माप(*bpm));
			bpm->अगरindex = dev->अगरindex;
			अगर (br_mdb_fill_info(skb, cb, dev) < 0)
				जाओ out;
			अगर (br_rports_fill_info(skb, cb, dev) < 0)
				जाओ out;

			cb->args[1] = 0;
			nlmsg_end(skb, nlh);
		skip:
			idx++;
		पूर्ण
	पूर्ण

out:
	अगर (nlh)
		nlmsg_end(skb, nlh);
	rcu_पढ़ो_unlock();
	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल पूर्णांक nlmsg_populate_mdb_fill(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev,
				   काष्ठा net_bridge_mdb_entry *mp,
				   काष्ठा net_bridge_port_group *pg,
				   पूर्णांक type)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा br_port_msg *bpm;
	काष्ठा nlattr *nest, *nest2;

	nlh = nlmsg_put(skb, 0, 0, type, माप(*bpm), 0);
	अगर (!nlh)
		वापस -EMSGSIZE;

	bpm = nlmsg_data(nlh);
	स_रखो(bpm, 0, माप(*bpm));
	bpm->family  = AF_BRIDGE;
	bpm->अगरindex = dev->अगरindex;
	nest = nla_nest_start_noflag(skb, MDBA_MDB);
	अगर (nest == शून्य)
		जाओ cancel;
	nest2 = nla_nest_start_noflag(skb, MDBA_MDB_ENTRY);
	अगर (nest2 == शून्य)
		जाओ end;

	अगर (__mdb_fill_info(skb, mp, pg))
		जाओ end;

	nla_nest_end(skb, nest2);
	nla_nest_end(skb, nest);
	nlmsg_end(skb, nlh);
	वापस 0;

end:
	nla_nest_end(skb, nest);
cancel:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल माप_प्रकार rtnl_mdb_nlmsg_size(काष्ठा net_bridge_port_group *pg)
अणु
	माप_प्रकार nlmsg_size = NLMSG_ALIGN(माप(काष्ठा br_port_msg)) +
			    nla_total_size(माप(काष्ठा br_mdb_entry)) +
			    nla_total_size(माप(u32));
	काष्ठा net_bridge_group_src *ent;
	माप_प्रकार addr_size = 0;

	अगर (!pg)
		जाओ out;

	/* MDBA_MDB_EATTR_RTPROT */
	nlmsg_size += nla_total_size(माप(u8));

	चयन (pg->key.addr.proto) अणु
	हाल htons(ETH_P_IP):
		/* MDBA_MDB_EATTR_SOURCE */
		अगर (pg->key.addr.src.ip4)
			nlmsg_size += nla_total_size(माप(__be32));
		अगर (pg->key.port->br->multicast_igmp_version == 2)
			जाओ out;
		addr_size = माप(__be32);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		/* MDBA_MDB_EATTR_SOURCE */
		अगर (!ipv6_addr_any(&pg->key.addr.src.ip6))
			nlmsg_size += nla_total_size(माप(काष्ठा in6_addr));
		अगर (pg->key.port->br->multicast_mld_version == 1)
			जाओ out;
		addr_size = माप(काष्ठा in6_addr);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	/* MDBA_MDB_EATTR_GROUP_MODE */
	nlmsg_size += nla_total_size(माप(u8));

	/* MDBA_MDB_EATTR_SRC_LIST nested attr */
	अगर (!hlist_empty(&pg->src_list))
		nlmsg_size += nla_total_size(0);

	hlist_क्रम_each_entry(ent, &pg->src_list, node) अणु
		/* MDBA_MDB_SRCLIST_ENTRY nested attr +
		 * MDBA_MDB_SRCATTR_ADDRESS + MDBA_MDB_SRCATTR_TIMER
		 */
		nlmsg_size += nla_total_size(0) +
			      nla_total_size(addr_size) +
			      nla_total_size(माप(u32));
	पूर्ण
out:
	वापस nlmsg_size;
पूर्ण

काष्ठा br_mdb_complete_info अणु
	काष्ठा net_bridge_port *port;
	काष्ठा br_ip ip;
पूर्ण;

अटल व्योम br_mdb_complete(काष्ठा net_device *dev, पूर्णांक err, व्योम *priv)
अणु
	काष्ठा br_mdb_complete_info *data = priv;
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा net_bridge_port_group *p;
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा net_bridge_port *port = data->port;
	काष्ठा net_bridge *br = port->br;

	अगर (err)
		जाओ err;

	spin_lock_bh(&br->multicast_lock);
	mp = br_mdb_ip_get(br, &data->ip);
	अगर (!mp)
		जाओ out;
	क्रम (pp = &mp->ports; (p = mlock_dereference(*pp, br)) != शून्य;
	     pp = &p->next) अणु
		अगर (p->key.port != port)
			जारी;
		p->flags |= MDB_PG_FLAGS_OFFLOAD;
	पूर्ण
out:
	spin_unlock_bh(&br->multicast_lock);
err:
	kमुक्त(priv);
पूर्ण

अटल व्योम br_चयनdev_mdb_populate(काष्ठा चयनdev_obj_port_mdb *mdb,
				      स्थिर काष्ठा net_bridge_mdb_entry *mp)
अणु
	अगर (mp->addr.proto == htons(ETH_P_IP))
		ip_eth_mc_map(mp->addr.dst.ip4, mdb->addr);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (mp->addr.proto == htons(ETH_P_IPV6))
		ipv6_eth_mc_map(&mp->addr.dst.ip6, mdb->addr);
#पूर्ण_अगर
	अन्यथा
		ether_addr_copy(mdb->addr, mp->addr.dst.mac_addr);

	mdb->vid = mp->addr.vid;
पूर्ण

अटल पूर्णांक br_mdb_replay_one(काष्ठा notअगरier_block *nb, काष्ठा net_device *dev,
			     काष्ठा चयनdev_obj_port_mdb *mdb,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_notअगरier_port_obj_info obj_info = अणु
		.info = अणु
			.dev = dev,
			.extack = extack,
		पूर्ण,
		.obj = &mdb->obj,
	पूर्ण;
	पूर्णांक err;

	err = nb->notअगरier_call(nb, SWITCHDEV_PORT_OBJ_ADD, &obj_info);
	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक br_mdb_queue_one(काष्ठा list_head *mdb_list,
			    क्रमागत चयनdev_obj_id id,
			    स्थिर काष्ठा net_bridge_mdb_entry *mp,
			    काष्ठा net_device *orig_dev)
अणु
	काष्ठा चयनdev_obj_port_mdb *mdb;

	mdb = kzalloc(माप(*mdb), GFP_ATOMIC);
	अगर (!mdb)
		वापस -ENOMEM;

	mdb->obj.id = id;
	mdb->obj.orig_dev = orig_dev;
	br_चयनdev_mdb_populate(mdb, mp);
	list_add_tail(&mdb->obj.list, mdb_list);

	वापस 0;
पूर्ण

पूर्णांक br_mdb_replay(काष्ठा net_device *br_dev, काष्ठा net_device *dev,
		  काष्ठा notअगरier_block *nb, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा चयनdev_obj *obj, *पंचांगp;
	काष्ठा net_bridge *br;
	LIST_HEAD(mdb_list);
	पूर्णांक err = 0;

	ASSERT_RTNL();

	अगर (!netअगर_is_bridge_master(br_dev) || !netअगर_is_bridge_port(dev))
		वापस -EINVAL;

	br = netdev_priv(br_dev);

	अगर (!br_opt_get(br, BROPT_MULTICAST_ENABLED))
		वापस 0;

	/* We cannot walk over br->mdb_list रक्षित just by the rtnl_mutex,
	 * because the ग_लिखो-side protection is br->multicast_lock. But we
	 * need to emulate the [ blocking ] calling context of a regular
	 * चयनdev event, so since both br->multicast_lock and RCU पढ़ो side
	 * critical sections are atomic, we have no choice but to pick the RCU
	 * पढ़ो side lock, queue up all our events, leave the critical section
	 * and notअगरy चयनdev from blocking context.
	 */
	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(mp, &br->mdb_list, mdb_node) अणु
		काष्ठा net_bridge_port_group __rcu **pp;
		काष्ठा net_bridge_port_group *p;

		अगर (mp->host_joined) अणु
			err = br_mdb_queue_one(&mdb_list,
					       SWITCHDEV_OBJ_ID_HOST_MDB,
					       mp, br_dev);
			अगर (err) अणु
				rcu_पढ़ो_unlock();
				जाओ out_मुक्त_mdb;
			पूर्ण
		पूर्ण

		क्रम (pp = &mp->ports; (p = rcu_dereference(*pp)) != शून्य;
		     pp = &p->next) अणु
			अगर (p->key.port->dev != dev)
				जारी;

			err = br_mdb_queue_one(&mdb_list,
					       SWITCHDEV_OBJ_ID_PORT_MDB,
					       mp, dev);
			अगर (err) अणु
				rcu_पढ़ो_unlock();
				जाओ out_मुक्त_mdb;
			पूर्ण
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	list_क्रम_each_entry(obj, &mdb_list, list) अणु
		err = br_mdb_replay_one(nb, dev, SWITCHDEV_OBJ_PORT_MDB(obj),
					extack);
		अगर (err)
			जाओ out_मुक्त_mdb;
	पूर्ण

out_मुक्त_mdb:
	list_क्रम_each_entry_safe(obj, पंचांगp, &mdb_list, list) अणु
		list_del(&obj->list);
		kमुक्त(SWITCHDEV_OBJ_PORT_MDB(obj));
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(br_mdb_replay);

अटल व्योम br_mdb_चयनdev_host_port(काष्ठा net_device *dev,
				       काष्ठा net_device *lower_dev,
				       काष्ठा net_bridge_mdb_entry *mp,
				       पूर्णांक type)
अणु
	काष्ठा चयनdev_obj_port_mdb mdb = अणु
		.obj = अणु
			.id = SWITCHDEV_OBJ_ID_HOST_MDB,
			.flags = SWITCHDEV_F_DEFER,
			.orig_dev = dev,
		पूर्ण,
	पूर्ण;

	br_चयनdev_mdb_populate(&mdb, mp);

	चयन (type) अणु
	हाल RTM_NEWMDB:
		चयनdev_port_obj_add(lower_dev, &mdb.obj, शून्य);
		अवरोध;
	हाल RTM_DELMDB:
		चयनdev_port_obj_del(lower_dev, &mdb.obj);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम br_mdb_चयनdev_host(काष्ठा net_device *dev,
				  काष्ठा net_bridge_mdb_entry *mp, पूर्णांक type)
अणु
	काष्ठा net_device *lower_dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_lower_dev(dev, lower_dev, iter)
		br_mdb_चयनdev_host_port(dev, lower_dev, mp, type);
पूर्ण

व्योम br_mdb_notअगरy(काष्ठा net_device *dev,
		   काष्ठा net_bridge_mdb_entry *mp,
		   काष्ठा net_bridge_port_group *pg,
		   पूर्णांक type)
अणु
	काष्ठा br_mdb_complete_info *complete_info;
	काष्ठा चयनdev_obj_port_mdb mdb = अणु
		.obj = अणु
			.id = SWITCHDEV_OBJ_ID_PORT_MDB,
			.flags = SWITCHDEV_F_DEFER,
		पूर्ण,
	पूर्ण;
	काष्ठा net *net = dev_net(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	अगर (pg) अणु
		br_चयनdev_mdb_populate(&mdb, mp);

		mdb.obj.orig_dev = pg->key.port->dev;
		चयन (type) अणु
		हाल RTM_NEWMDB:
			complete_info = kदो_स्मृति(माप(*complete_info), GFP_ATOMIC);
			अगर (!complete_info)
				अवरोध;
			complete_info->port = pg->key.port;
			complete_info->ip = mp->addr;
			mdb.obj.complete_priv = complete_info;
			mdb.obj.complete = br_mdb_complete;
			अगर (चयनdev_port_obj_add(pg->key.port->dev, &mdb.obj, शून्य))
				kमुक्त(complete_info);
			अवरोध;
		हाल RTM_DELMDB:
			चयनdev_port_obj_del(pg->key.port->dev, &mdb.obj);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		br_mdb_चयनdev_host(dev, mp, type);
	पूर्ण

	skb = nlmsg_new(rtnl_mdb_nlmsg_size(pg), GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	err = nlmsg_populate_mdb_fill(skb, dev, mp, pg, type);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, net, 0, RTNLGRP_MDB, शून्य, GFP_ATOMIC);
	वापस;
errout:
	rtnl_set_sk_err(net, RTNLGRP_MDB, err);
पूर्ण

अटल पूर्णांक nlmsg_populate_rtr_fill(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev,
				   पूर्णांक अगरindex, u32 pid,
				   u32 seq, पूर्णांक type, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा br_port_msg *bpm;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *nest;

	nlh = nlmsg_put(skb, pid, seq, type, माप(*bpm), 0);
	अगर (!nlh)
		वापस -EMSGSIZE;

	bpm = nlmsg_data(nlh);
	स_रखो(bpm, 0, माप(*bpm));
	bpm->family = AF_BRIDGE;
	bpm->अगरindex = dev->अगरindex;
	nest = nla_nest_start_noflag(skb, MDBA_ROUTER);
	अगर (!nest)
		जाओ cancel;

	अगर (nla_put_u32(skb, MDBA_ROUTER_PORT, अगरindex))
		जाओ end;

	nla_nest_end(skb, nest);
	nlmsg_end(skb, nlh);
	वापस 0;

end:
	nla_nest_end(skb, nest);
cancel:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल अंतरभूत माप_प्रकार rtnl_rtr_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा br_port_msg))
		+ nla_total_size(माप(__u32));
पूर्ण

व्योम br_rtr_notअगरy(काष्ठा net_device *dev, काष्ठा net_bridge_port *port,
		   पूर्णांक type)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;
	पूर्णांक अगरindex;

	अगरindex = port ? port->dev->अगरindex : 0;
	skb = nlmsg_new(rtnl_rtr_nlmsg_size(), GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	err = nlmsg_populate_rtr_fill(skb, dev, अगरindex, 0, 0, type, NTF_SELF);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, net, 0, RTNLGRP_MDB, शून्य, GFP_ATOMIC);
	वापस;

errout:
	rtnl_set_sk_err(net, RTNLGRP_MDB, err);
पूर्ण

अटल bool is_valid_mdb_entry(काष्ठा br_mdb_entry *entry,
			       काष्ठा netlink_ext_ack *extack)
अणु
	अगर (entry->अगरindex == 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Zero entry ifindex is not allowed");
		वापस false;
	पूर्ण

	अगर (entry->addr.proto == htons(ETH_P_IP)) अणु
		अगर (!ipv4_is_multicast(entry->addr.u.ip4)) अणु
			NL_SET_ERR_MSG_MOD(extack, "IPv4 entry group address is not multicast");
			वापस false;
		पूर्ण
		अगर (ipv4_is_local_multicast(entry->addr.u.ip4)) अणु
			NL_SET_ERR_MSG_MOD(extack, "IPv4 entry group address is local multicast");
			वापस false;
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (entry->addr.proto == htons(ETH_P_IPV6)) अणु
		अगर (ipv6_addr_is_ll_all_nodes(&entry->addr.u.ip6)) अणु
			NL_SET_ERR_MSG_MOD(extack, "IPv6 entry group address is link-local all nodes");
			वापस false;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (entry->addr.proto == 0) अणु
		/* L2 mdb */
		अगर (!is_multicast_ether_addr(entry->addr.u.mac_addr)) अणु
			NL_SET_ERR_MSG_MOD(extack, "L2 entry group is not multicast");
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "Unknown entry protocol");
		वापस false;
	पूर्ण

	अगर (entry->state != MDB_PERMANENT && entry->state != MDB_TEMPORARY) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unknown entry state");
		वापस false;
	पूर्ण
	अगर (entry->vid >= VLAN_VID_MASK) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid entry VLAN id");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool is_valid_mdb_source(काष्ठा nlattr *attr, __be16 proto,
				काष्ठा netlink_ext_ack *extack)
अणु
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		अगर (nla_len(attr) != माप(काष्ठा in_addr)) अणु
			NL_SET_ERR_MSG_MOD(extack, "IPv4 invalid source address length");
			वापस false;
		पूर्ण
		अगर (ipv4_is_multicast(nla_get_in_addr(attr))) अणु
			NL_SET_ERR_MSG_MOD(extack, "IPv4 multicast source address is not allowed");
			वापस false;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6): अणु
		काष्ठा in6_addr src;

		अगर (nla_len(attr) != माप(काष्ठा in6_addr)) अणु
			NL_SET_ERR_MSG_MOD(extack, "IPv6 invalid source address length");
			वापस false;
		पूर्ण
		src = nla_get_in6_addr(attr);
		अगर (ipv6_addr_is_multicast(&src)) अणु
			NL_SET_ERR_MSG_MOD(extack, "IPv6 multicast source address is not allowed");
			वापस false;
		पूर्ण
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "Invalid protocol used with source address");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा nla_policy br_mdbe_attrs_pol[MDBE_ATTR_MAX + 1] = अणु
	[MDBE_ATTR_SOURCE] = NLA_POLICY_RANGE(NLA_BINARY,
					      माप(काष्ठा in_addr),
					      माप(काष्ठा in6_addr)),
पूर्ण;

अटल पूर्णांक br_mdb_parse(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा net_device **pdev, काष्ठा br_mdb_entry **pentry,
			काष्ठा nlattr **mdb_attrs, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा br_mdb_entry *entry;
	काष्ठा br_port_msg *bpm;
	काष्ठा nlattr *tb[MDBA_SET_ENTRY_MAX+1];
	काष्ठा net_device *dev;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, माप(*bpm), tb,
				     MDBA_SET_ENTRY_MAX, शून्य, शून्य);
	अगर (err < 0)
		वापस err;

	bpm = nlmsg_data(nlh);
	अगर (bpm->अगरindex == 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid bridge ifindex");
		वापस -EINVAL;
	पूर्ण

	dev = __dev_get_by_index(net, bpm->अगरindex);
	अगर (dev == शून्य) अणु
		NL_SET_ERR_MSG_MOD(extack, "Bridge device doesn't exist");
		वापस -ENODEV;
	पूर्ण

	अगर (!(dev->priv_flags & IFF_EBRIDGE)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device is not a bridge");
		वापस -EOPNOTSUPP;
	पूर्ण

	*pdev = dev;

	अगर (!tb[MDBA_SET_ENTRY]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing MDBA_SET_ENTRY attribute");
		वापस -EINVAL;
	पूर्ण
	अगर (nla_len(tb[MDBA_SET_ENTRY]) != माप(काष्ठा br_mdb_entry)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid MDBA_SET_ENTRY attribute length");
		वापस -EINVAL;
	पूर्ण

	entry = nla_data(tb[MDBA_SET_ENTRY]);
	अगर (!is_valid_mdb_entry(entry, extack))
		वापस -EINVAL;
	*pentry = entry;

	अगर (tb[MDBA_SET_ENTRY_ATTRS]) अणु
		err = nla_parse_nested(mdb_attrs, MDBE_ATTR_MAX,
				       tb[MDBA_SET_ENTRY_ATTRS],
				       br_mdbe_attrs_pol, extack);
		अगर (err)
			वापस err;
		अगर (mdb_attrs[MDBE_ATTR_SOURCE] &&
		    !is_valid_mdb_source(mdb_attrs[MDBE_ATTR_SOURCE],
					 entry->addr.proto, extack))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		स_रखो(mdb_attrs, 0,
		       माप(काष्ठा nlattr *) * (MDBE_ATTR_MAX + 1));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक br_mdb_add_group(काष्ठा net_bridge *br, काष्ठा net_bridge_port *port,
			    काष्ठा br_mdb_entry *entry,
			    काष्ठा nlattr **mdb_attrs,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_mdb_entry *mp, *star_mp;
	काष्ठा net_bridge_port_group *p;
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा br_ip group, star_group;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित अक्षर flags = 0;
	u8 filter_mode;
	पूर्णांक err;

	__mdb_entry_to_br_ip(entry, &group, mdb_attrs);

	/* host join errors which can happen beक्रमe creating the group */
	अगर (!port) अणु
		/* करोn't allow any flags क्रम host-joined groups */
		अगर (entry->state) अणु
			NL_SET_ERR_MSG_MOD(extack, "Flags are not allowed for host groups");
			वापस -EINVAL;
		पूर्ण
		अगर (!br_multicast_is_star_g(&group)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Groups with sources cannot be manually host joined");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (br_group_is_l2(&group) && entry->state != MDB_PERMANENT) अणु
		NL_SET_ERR_MSG_MOD(extack, "Only permanent L2 entries allowed");
		वापस -EINVAL;
	पूर्ण

	mp = br_mdb_ip_get(br, &group);
	अगर (!mp) अणु
		mp = br_multicast_new_group(br, &group);
		err = PTR_ERR_OR_ZERO(mp);
		अगर (err)
			वापस err;
	पूर्ण

	/* host join */
	अगर (!port) अणु
		अगर (mp->host_joined) अणु
			NL_SET_ERR_MSG_MOD(extack, "Group is already joined by host");
			वापस -EEXIST;
		पूर्ण

		br_multicast_host_join(mp, false);
		br_mdb_notअगरy(br->dev, mp, शून्य, RTM_NEWMDB);

		वापस 0;
	पूर्ण

	क्रम (pp = &mp->ports;
	     (p = mlock_dereference(*pp, br)) != शून्य;
	     pp = &p->next) अणु
		अगर (p->key.port == port) अणु
			NL_SET_ERR_MSG_MOD(extack, "Group is already joined by port");
			वापस -EEXIST;
		पूर्ण
		अगर ((अचिन्हित दीर्घ)p->key.port < (अचिन्हित दीर्घ)port)
			अवरोध;
	पूर्ण

	filter_mode = br_multicast_is_star_g(&group) ? MCAST_EXCLUDE :
						       MCAST_INCLUDE;

	अगर (entry->state == MDB_PERMANENT)
		flags |= MDB_PG_FLAGS_PERMANENT;

	p = br_multicast_new_port_group(port, &group, *pp, flags, शून्य,
					filter_mode, RTPROT_STATIC);
	अगर (unlikely(!p)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Couldn't allocate new port group");
		वापस -ENOMEM;
	पूर्ण
	rcu_assign_poपूर्णांकer(*pp, p);
	अगर (entry->state == MDB_TEMPORARY)
		mod_समयr(&p->समयr, now + br->multicast_membership_पूर्णांकerval);
	br_mdb_notअगरy(br->dev, mp, p, RTM_NEWMDB);
	/* अगर we are adding a new EXCLUDE port group (*,G) it needs to be also
	 * added to all S,G entries क्रम proper replication, अगर we are adding
	 * a new INCLUDE port (S,G) then all of *,G EXCLUDE ports need to be
	 * added to it क्रम proper replication
	 */
	अगर (br_multicast_should_handle_mode(br, group.proto)) अणु
		चयन (filter_mode) अणु
		हाल MCAST_EXCLUDE:
			br_multicast_star_g_handle_mode(p, MCAST_EXCLUDE);
			अवरोध;
		हाल MCAST_INCLUDE:
			star_group = p->key.addr;
			स_रखो(&star_group.src, 0, माप(star_group.src));
			star_mp = br_mdb_ip_get(br, &star_group);
			अगर (star_mp)
				br_multicast_sg_add_exclude_ports(star_mp, p);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __br_mdb_add(काष्ठा net *net, काष्ठा net_bridge *br,
			काष्ठा net_bridge_port *p,
			काष्ठा br_mdb_entry *entry,
			काष्ठा nlattr **mdb_attrs,
			काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret;

	spin_lock_bh(&br->multicast_lock);
	ret = br_mdb_add_group(br, p, entry, mdb_attrs, extack);
	spin_unlock_bh(&br->multicast_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक br_mdb_add(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *mdb_attrs[MDBE_ATTR_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p = शून्य;
	काष्ठा net_device *dev, *pdev;
	काष्ठा br_mdb_entry *entry;
	काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge *br;
	पूर्णांक err;

	err = br_mdb_parse(skb, nlh, &dev, &entry, mdb_attrs, extack);
	अगर (err < 0)
		वापस err;

	br = netdev_priv(dev);

	अगर (!netअगर_running(br->dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Bridge device is not running");
		वापस -EINVAL;
	पूर्ण

	अगर (!br_opt_get(br, BROPT_MULTICAST_ENABLED)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Bridge's multicast processing is disabled");
		वापस -EINVAL;
	पूर्ण

	अगर (entry->अगरindex != br->dev->अगरindex) अणु
		pdev = __dev_get_by_index(net, entry->अगरindex);
		अगर (!pdev) अणु
			NL_SET_ERR_MSG_MOD(extack, "Port net device doesn't exist");
			वापस -ENODEV;
		पूर्ण

		p = br_port_get_rtnl(pdev);
		अगर (!p) अणु
			NL_SET_ERR_MSG_MOD(extack, "Net device is not a bridge port");
			वापस -EINVAL;
		पूर्ण

		अगर (p->br != br) अणु
			NL_SET_ERR_MSG_MOD(extack, "Port belongs to a different bridge device");
			वापस -EINVAL;
		पूर्ण
		अगर (p->state == BR_STATE_DISABLED) अणु
			NL_SET_ERR_MSG_MOD(extack, "Port is in disabled state");
			वापस -EINVAL;
		पूर्ण
		vg = nbp_vlan_group(p);
	पूर्ण अन्यथा अणु
		vg = br_vlan_group(br);
	पूर्ण

	/* If vlan filtering is enabled and VLAN is not specअगरied
	 * install mdb entry on all vlans configured on the port.
	 */
	अगर (br_vlan_enabled(br->dev) && vg && entry->vid == 0) अणु
		list_क्रम_each_entry(v, &vg->vlan_list, vlist) अणु
			entry->vid = v->vid;
			err = __br_mdb_add(net, br, p, entry, mdb_attrs, extack);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = __br_mdb_add(net, br, p, entry, mdb_attrs, extack);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __br_mdb_del(काष्ठा net_bridge *br, काष्ठा br_mdb_entry *entry,
			काष्ठा nlattr **mdb_attrs)
अणु
	काष्ठा net_bridge_mdb_entry *mp;
	काष्ठा net_bridge_port_group *p;
	काष्ठा net_bridge_port_group __rcu **pp;
	काष्ठा br_ip ip;
	पूर्णांक err = -EINVAL;

	अगर (!netअगर_running(br->dev) || !br_opt_get(br, BROPT_MULTICAST_ENABLED))
		वापस -EINVAL;

	__mdb_entry_to_br_ip(entry, &ip, mdb_attrs);

	spin_lock_bh(&br->multicast_lock);
	mp = br_mdb_ip_get(br, &ip);
	अगर (!mp)
		जाओ unlock;

	/* host leave */
	अगर (entry->अगरindex == mp->br->dev->अगरindex && mp->host_joined) अणु
		br_multicast_host_leave(mp, false);
		err = 0;
		br_mdb_notअगरy(br->dev, mp, शून्य, RTM_DELMDB);
		अगर (!mp->ports && netअगर_running(br->dev))
			mod_समयr(&mp->समयr, jअगरfies);
		जाओ unlock;
	पूर्ण

	क्रम (pp = &mp->ports;
	     (p = mlock_dereference(*pp, br)) != शून्य;
	     pp = &p->next) अणु
		अगर (!p->key.port || p->key.port->dev->अगरindex != entry->अगरindex)
			जारी;

		अगर (p->key.port->state == BR_STATE_DISABLED)
			जाओ unlock;

		br_multicast_del_pg(mp, p, pp);
		err = 0;
		अवरोध;
	पूर्ण

unlock:
	spin_unlock_bh(&br->multicast_lock);
	वापस err;
पूर्ण

अटल पूर्णांक br_mdb_del(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *mdb_attrs[MDBE_ATTR_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p = शून्य;
	काष्ठा net_device *dev, *pdev;
	काष्ठा br_mdb_entry *entry;
	काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge *br;
	पूर्णांक err;

	err = br_mdb_parse(skb, nlh, &dev, &entry, mdb_attrs, extack);
	अगर (err < 0)
		वापस err;

	br = netdev_priv(dev);

	अगर (entry->अगरindex != br->dev->अगरindex) अणु
		pdev = __dev_get_by_index(net, entry->अगरindex);
		अगर (!pdev)
			वापस -ENODEV;

		p = br_port_get_rtnl(pdev);
		अगर (!p || p->br != br || p->state == BR_STATE_DISABLED)
			वापस -EINVAL;
		vg = nbp_vlan_group(p);
	पूर्ण अन्यथा अणु
		vg = br_vlan_group(br);
	पूर्ण

	/* If vlan filtering is enabled and VLAN is not specअगरied
	 * delete mdb entry on all vlans configured on the port.
	 */
	अगर (br_vlan_enabled(br->dev) && vg && entry->vid == 0) अणु
		list_क्रम_each_entry(v, &vg->vlan_list, vlist) अणु
			entry->vid = v->vid;
			err = __br_mdb_del(br, entry, mdb_attrs);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = __br_mdb_del(br, entry, mdb_attrs);
	पूर्ण

	वापस err;
पूर्ण

व्योम br_mdb_init(व्योम)
अणु
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_BRIDGE, RTM_GETMDB, शून्य, br_mdb_dump, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_BRIDGE, RTM_NEWMDB, br_mdb_add, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_BRIDGE, RTM_DELMDB, br_mdb_del, शून्य, 0);
पूर्ण

व्योम br_mdb_uninit(व्योम)
अणु
	rtnl_unरेजिस्टर(PF_BRIDGE, RTM_GETMDB);
	rtnl_unरेजिस्टर(PF_BRIDGE, RTM_NEWMDB);
	rtnl_unरेजिस्टर(PF_BRIDGE, RTM_DELMDB);
पूर्ण

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2018 Mellanox Technologies. */

#समावेश <net/vxlan.h>
#समावेश <net/gre.h>
#समावेश <net/geneve.h>
#समावेश <net/bareudp.h>
#समावेश "en/tc_tun.h"
#समावेश "en/tc_priv.h"
#समावेश "en_tc.h"
#समावेश "rep/tc.h"
#समावेश "rep/neigh.h"

काष्ठा mlx5e_tc_tun_route_attr अणु
	काष्ठा net_device *out_dev;
	काष्ठा net_device *route_dev;
	जोड़ अणु
		काष्ठा flowi4 fl4;
		काष्ठा flowi6 fl6;
	पूर्ण fl;
	काष्ठा neighbour *n;
	u8 ttl;
पूर्ण;

#घोषणा TC_TUN_ROUTE_ATTR_INIT(name) काष्ठा mlx5e_tc_tun_route_attr name = अणुपूर्ण

अटल व्योम mlx5e_tc_tun_route_attr_cleanup(काष्ठा mlx5e_tc_tun_route_attr *attr)
अणु
	अगर (attr->n)
		neigh_release(attr->n);
	अगर (attr->route_dev)
		dev_put(attr->route_dev);
पूर्ण

काष्ठा mlx5e_tc_tunnel *mlx5e_get_tc_tun(काष्ठा net_device *tunnel_dev)
अणु
	अगर (netअगर_is_vxlan(tunnel_dev))
		वापस &vxlan_tunnel;
	अन्यथा अगर (netअगर_is_geneve(tunnel_dev))
		वापस &geneve_tunnel;
	अन्यथा अगर (netअगर_is_gretap(tunnel_dev) ||
		 netअगर_is_ip6gretap(tunnel_dev))
		वापस &gre_tunnel;
	अन्यथा अगर (netअगर_is_bareudp(tunnel_dev))
		वापस &mplsoudp_tunnel;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक get_route_and_out_devs(काष्ठा mlx5e_priv *priv,
				  काष्ठा net_device *dev,
				  काष्ठा net_device **route_dev,
				  काष्ठा net_device **out_dev)
अणु
	काष्ठा net_device *uplink_dev, *uplink_upper, *real_dev;
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	bool dst_is_lag_dev;

	real_dev = is_vlan_dev(dev) ? vlan_dev_real_dev(dev) : dev;
	uplink_dev = mlx5_eचयन_uplink_get_proto_dev(esw, REP_ETH);

	rcu_पढ़ो_lock();
	uplink_upper = netdev_master_upper_dev_get_rcu(uplink_dev);
	/* mlx5_lag_is_sriov() is a blocking function which can't be called
	 * जबतक holding rcu पढ़ो lock. Take the net_device क्रम correctness
	 * sake.
	 */
	अगर (uplink_upper)
		dev_hold(uplink_upper);
	rcu_पढ़ो_unlock();

	dst_is_lag_dev = (uplink_upper &&
			  netअगर_is_lag_master(uplink_upper) &&
			  real_dev == uplink_upper &&
			  mlx5_lag_is_sriov(priv->mdev));
	अगर (uplink_upper)
		dev_put(uplink_upper);

	/* अगर the egress device isn't on the same HW e-चयन or
	 * it's a LAG device, use the uplink
	 */
	*route_dev = dev;
	अगर (!netdev_port_same_parent_id(priv->netdev, real_dev) ||
	    dst_is_lag_dev || is_vlan_dev(*route_dev))
		*out_dev = uplink_dev;
	अन्यथा अगर (mlx5e_eचयन_rep(dev) &&
		 mlx5e_is_valid_eचयन_fwd_dev(priv, dev))
		*out_dev = *route_dev;
	अन्यथा
		वापस -EOPNOTSUPP;

	अगर (!(mlx5e_eचयन_rep(*out_dev) &&
	      mlx5e_is_uplink_rep(netdev_priv(*out_dev))))
		वापस -EOPNOTSUPP;

	अगर (mlx5e_eचयन_uplink_rep(priv->netdev) && *out_dev != priv->netdev)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_route_lookup_ipv4_get(काष्ठा mlx5e_priv *priv,
				       काष्ठा net_device *mirred_dev,
				       काष्ठा mlx5e_tc_tun_route_attr *attr)
अणु
	काष्ठा net_device *route_dev;
	काष्ठा net_device *out_dev;
	काष्ठा neighbour *n;
	काष्ठा rtable *rt;

#अगर IS_ENABLED(CONFIG_INET)
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा net_device *uplink_dev;
	पूर्णांक ret;

	अगर (mlx5_lag_is_multipath(mdev)) अणु
		काष्ठा mlx5_eचयन *esw = mdev->priv.eचयन;

		uplink_dev = mlx5_eचयन_uplink_get_proto_dev(esw, REP_ETH);
		attr->fl.fl4.flowi4_oअगर = uplink_dev->अगरindex;
	पूर्ण

	rt = ip_route_output_key(dev_net(mirred_dev), &attr->fl.fl4);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);

	अगर (mlx5_lag_is_multipath(mdev) && rt->rt_gw_family != AF_INET) अणु
		ret = -ENETUNREACH;
		जाओ err_rt_release;
	पूर्ण
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर

	ret = get_route_and_out_devs(priv, rt->dst.dev, &route_dev, &out_dev);
	अगर (ret < 0)
		जाओ err_rt_release;
	dev_hold(route_dev);

	अगर (!attr->ttl)
		attr->ttl = ip4_dst_hoplimit(&rt->dst);
	n = dst_neigh_lookup(&rt->dst, &attr->fl.fl4.daddr);
	अगर (!n) अणु
		ret = -ENOMEM;
		जाओ err_dev_release;
	पूर्ण

	ip_rt_put(rt);
	attr->route_dev = route_dev;
	attr->out_dev = out_dev;
	attr->n = n;
	वापस 0;

err_dev_release:
	dev_put(route_dev);
err_rt_release:
	ip_rt_put(rt);
	वापस ret;
पूर्ण

अटल व्योम mlx5e_route_lookup_ipv4_put(काष्ठा mlx5e_tc_tun_route_attr *attr)
अणु
	mlx5e_tc_tun_route_attr_cleanup(attr);
पूर्ण

अटल स्थिर अक्षर *mlx5e_netdev_kind(काष्ठा net_device *dev)
अणु
	अगर (dev->rtnl_link_ops)
		वापस dev->rtnl_link_ops->kind;
	अन्यथा
		वापस "unknown";
पूर्ण

अटल पूर्णांक mlx5e_gen_ip_tunnel_header(अक्षर buf[], __u8 *ip_proto,
				      काष्ठा mlx5e_encap_entry *e)
अणु
	अगर (!e->tunnel) अणु
		pr_warn("mlx5: Cannot generate tunnel header for this tunnel\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस e->tunnel->generate_ip_tun_hdr(buf, ip_proto, e);
पूर्ण

अटल अक्षर *gen_eth_tnl_hdr(अक्षर *buf, काष्ठा net_device *dev,
			     काष्ठा mlx5e_encap_entry *e,
			     u16 proto)
अणु
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)buf;
	अक्षर *ip;

	ether_addr_copy(eth->h_dest, e->h_dest);
	ether_addr_copy(eth->h_source, dev->dev_addr);
	अगर (is_vlan_dev(dev)) अणु
		काष्ठा vlan_hdr *vlan = (काष्ठा vlan_hdr *)
					((अक्षर *)eth + ETH_HLEN);
		ip = (अक्षर *)vlan + VLAN_HLEN;
		eth->h_proto = vlan_dev_vlan_proto(dev);
		vlan->h_vlan_TCI = htons(vlan_dev_vlan_id(dev));
		vlan->h_vlan_encapsulated_proto = htons(proto);
	पूर्ण अन्यथा अणु
		eth->h_proto = htons(proto);
		ip = (अक्षर *)eth + ETH_HLEN;
	पूर्ण

	वापस ip;
पूर्ण

पूर्णांक mlx5e_tc_tun_create_header_ipv4(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *mirred_dev,
				    काष्ठा mlx5e_encap_entry *e)
अणु
	पूर्णांक max_encap_size = MLX5_CAP_ESW(priv->mdev, max_encap_header_size);
	स्थिर काष्ठा ip_tunnel_key *tun_key = &e->tun_info->key;
	काष्ठा mlx5e_neigh m_neigh = अणुपूर्ण;
	TC_TUN_ROUTE_ATTR_INIT(attr);
	पूर्णांक ipv4_encap_size;
	अक्षर *encap_header;
	काष्ठा iphdr *ip;
	u8 nud_state;
	पूर्णांक err;

	/* add the IP fields */
	attr.fl.fl4.flowi4_tos = tun_key->tos;
	attr.fl.fl4.daddr = tun_key->u.ipv4.dst;
	attr.fl.fl4.saddr = tun_key->u.ipv4.src;
	attr.ttl = tun_key->ttl;

	err = mlx5e_route_lookup_ipv4_get(priv, mirred_dev, &attr);
	अगर (err)
		वापस err;

	ipv4_encap_size =
		(is_vlan_dev(attr.route_dev) ? VLAN_ETH_HLEN : ETH_HLEN) +
		माप(काष्ठा iphdr) +
		e->tunnel->calc_hlen(e);

	अगर (max_encap_size < ipv4_encap_size) अणु
		mlx5_core_warn(priv->mdev, "encap size %d too big, max supported is %d\n",
			       ipv4_encap_size, max_encap_size);
		err = -EOPNOTSUPP;
		जाओ release_neigh;
	पूर्ण

	encap_header = kzalloc(ipv4_encap_size, GFP_KERNEL);
	अगर (!encap_header) अणु
		err = -ENOMEM;
		जाओ release_neigh;
	पूर्ण

	m_neigh.family = attr.n->ops->family;
	स_नकल(&m_neigh.dst_ip, attr.n->primary_key, attr.n->tbl->key_len);
	e->out_dev = attr.out_dev;
	e->route_dev_अगरindex = attr.route_dev->अगरindex;

	/* It's important to add the neigh to the hash table beक्रमe checking
	 * the neigh validity state. So अगर we'll get a notअगरication, in हाल the
	 * neigh changes it's validity state, we would find the relevant neigh
	 * in the hash.
	 */
	err = mlx5e_rep_encap_entry_attach(netdev_priv(attr.out_dev), e, &m_neigh, attr.n->dev);
	अगर (err)
		जाओ मुक्त_encap;

	पढ़ो_lock_bh(&attr.n->lock);
	nud_state = attr.n->nud_state;
	ether_addr_copy(e->h_dest, attr.n->ha);
	पढ़ो_unlock_bh(&attr.n->lock);

	/* add ethernet header */
	ip = (काष्ठा iphdr *)gen_eth_tnl_hdr(encap_header, attr.route_dev, e,
					     ETH_P_IP);

	/* add ip header */
	ip->tos = tun_key->tos;
	ip->version = 0x4;
	ip->ihl = 0x5;
	ip->ttl = attr.ttl;
	ip->daddr = attr.fl.fl4.daddr;
	ip->saddr = attr.fl.fl4.saddr;

	/* add tunneling protocol header */
	err = mlx5e_gen_ip_tunnel_header((अक्षर *)ip + माप(काष्ठा iphdr),
					 &ip->protocol, e);
	अगर (err)
		जाओ destroy_neigh_entry;

	e->encap_size = ipv4_encap_size;
	e->encap_header = encap_header;

	अगर (!(nud_state & NUD_VALID)) अणु
		neigh_event_send(attr.n, शून्य);
		/* the encap entry will be made valid on neigh update event
		 * and not used beक्रमe that.
		 */
		जाओ release_neigh;
	पूर्ण
	e->pkt_reक्रमmat = mlx5_packet_reक्रमmat_alloc(priv->mdev,
						     e->reक्रमmat_type,
						     ipv4_encap_size, encap_header,
						     MLX5_FLOW_NAMESPACE_FDB);
	अगर (IS_ERR(e->pkt_reक्रमmat)) अणु
		err = PTR_ERR(e->pkt_reक्रमmat);
		जाओ destroy_neigh_entry;
	पूर्ण

	e->flags |= MLX5_ENCAP_ENTRY_VALID;
	mlx5e_rep_queue_neigh_stats_work(netdev_priv(attr.out_dev));
	mlx5e_route_lookup_ipv4_put(&attr);
	वापस err;

destroy_neigh_entry:
	mlx5e_rep_encap_entry_detach(netdev_priv(e->out_dev), e);
मुक्त_encap:
	kमुक्त(encap_header);
release_neigh:
	mlx5e_route_lookup_ipv4_put(&attr);
	वापस err;
पूर्ण

पूर्णांक mlx5e_tc_tun_update_header_ipv4(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *mirred_dev,
				    काष्ठा mlx5e_encap_entry *e)
अणु
	पूर्णांक max_encap_size = MLX5_CAP_ESW(priv->mdev, max_encap_header_size);
	स्थिर काष्ठा ip_tunnel_key *tun_key = &e->tun_info->key;
	TC_TUN_ROUTE_ATTR_INIT(attr);
	पूर्णांक ipv4_encap_size;
	अक्षर *encap_header;
	काष्ठा iphdr *ip;
	u8 nud_state;
	पूर्णांक err;

	/* add the IP fields */
	attr.fl.fl4.flowi4_tos = tun_key->tos;
	attr.fl.fl4.daddr = tun_key->u.ipv4.dst;
	attr.fl.fl4.saddr = tun_key->u.ipv4.src;
	attr.ttl = tun_key->ttl;

	err = mlx5e_route_lookup_ipv4_get(priv, mirred_dev, &attr);
	अगर (err)
		वापस err;

	ipv4_encap_size =
		(is_vlan_dev(attr.route_dev) ? VLAN_ETH_HLEN : ETH_HLEN) +
		माप(काष्ठा iphdr) +
		e->tunnel->calc_hlen(e);

	अगर (max_encap_size < ipv4_encap_size) अणु
		mlx5_core_warn(priv->mdev, "encap size %d too big, max supported is %d\n",
			       ipv4_encap_size, max_encap_size);
		err = -EOPNOTSUPP;
		जाओ release_neigh;
	पूर्ण

	encap_header = kzalloc(ipv4_encap_size, GFP_KERNEL);
	अगर (!encap_header) अणु
		err = -ENOMEM;
		जाओ release_neigh;
	पूर्ण

	e->route_dev_अगरindex = attr.route_dev->अगरindex;

	पढ़ो_lock_bh(&attr.n->lock);
	nud_state = attr.n->nud_state;
	ether_addr_copy(e->h_dest, attr.n->ha);
	WRITE_ONCE(e->nhe->neigh_dev, attr.n->dev);
	पढ़ो_unlock_bh(&attr.n->lock);

	/* add ethernet header */
	ip = (काष्ठा iphdr *)gen_eth_tnl_hdr(encap_header, attr.route_dev, e,
					     ETH_P_IP);

	/* add ip header */
	ip->tos = tun_key->tos;
	ip->version = 0x4;
	ip->ihl = 0x5;
	ip->ttl = attr.ttl;
	ip->daddr = attr.fl.fl4.daddr;
	ip->saddr = attr.fl.fl4.saddr;

	/* add tunneling protocol header */
	err = mlx5e_gen_ip_tunnel_header((अक्षर *)ip + माप(काष्ठा iphdr),
					 &ip->protocol, e);
	अगर (err)
		जाओ मुक्त_encap;

	e->encap_size = ipv4_encap_size;
	kमुक्त(e->encap_header);
	e->encap_header = encap_header;

	अगर (!(nud_state & NUD_VALID)) अणु
		neigh_event_send(attr.n, शून्य);
		/* the encap entry will be made valid on neigh update event
		 * and not used beक्रमe that.
		 */
		जाओ release_neigh;
	पूर्ण
	e->pkt_reक्रमmat = mlx5_packet_reक्रमmat_alloc(priv->mdev,
						     e->reक्रमmat_type,
						     ipv4_encap_size, encap_header,
						     MLX5_FLOW_NAMESPACE_FDB);
	अगर (IS_ERR(e->pkt_reक्रमmat)) अणु
		err = PTR_ERR(e->pkt_reक्रमmat);
		जाओ मुक्त_encap;
	पूर्ण

	e->flags |= MLX5_ENCAP_ENTRY_VALID;
	mlx5e_rep_queue_neigh_stats_work(netdev_priv(attr.out_dev));
	mlx5e_route_lookup_ipv4_put(&attr);
	वापस err;

मुक्त_encap:
	kमुक्त(encap_header);
release_neigh:
	mlx5e_route_lookup_ipv4_put(&attr);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_INET) && IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक mlx5e_route_lookup_ipv6_get(काष्ठा mlx5e_priv *priv,
				       काष्ठा net_device *mirred_dev,
				       काष्ठा mlx5e_tc_tun_route_attr *attr)
अणु
	काष्ठा net_device *route_dev;
	काष्ठा net_device *out_dev;
	काष्ठा dst_entry *dst;
	काष्ठा neighbour *n;
	पूर्णांक ret;

	dst = ipv6_stub->ipv6_dst_lookup_flow(dev_net(mirred_dev), शून्य, &attr->fl.fl6,
					      शून्य);
	अगर (IS_ERR(dst))
		वापस PTR_ERR(dst);

	अगर (!attr->ttl)
		attr->ttl = ip6_dst_hoplimit(dst);

	ret = get_route_and_out_devs(priv, dst->dev, &route_dev, &out_dev);
	अगर (ret < 0)
		जाओ err_dst_release;

	dev_hold(route_dev);
	n = dst_neigh_lookup(dst, &attr->fl.fl6.daddr);
	अगर (!n) अणु
		ret = -ENOMEM;
		जाओ err_dev_release;
	पूर्ण

	dst_release(dst);
	attr->out_dev = out_dev;
	attr->route_dev = route_dev;
	attr->n = n;
	वापस 0;

err_dev_release:
	dev_put(route_dev);
err_dst_release:
	dst_release(dst);
	वापस ret;
पूर्ण

अटल व्योम mlx5e_route_lookup_ipv6_put(काष्ठा mlx5e_tc_tun_route_attr *attr)
अणु
	mlx5e_tc_tun_route_attr_cleanup(attr);
पूर्ण

पूर्णांक mlx5e_tc_tun_create_header_ipv6(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *mirred_dev,
				    काष्ठा mlx5e_encap_entry *e)
अणु
	पूर्णांक max_encap_size = MLX5_CAP_ESW(priv->mdev, max_encap_header_size);
	स्थिर काष्ठा ip_tunnel_key *tun_key = &e->tun_info->key;
	काष्ठा mlx5e_neigh m_neigh = अणुपूर्ण;
	TC_TUN_ROUTE_ATTR_INIT(attr);
	काष्ठा ipv6hdr *ip6h;
	पूर्णांक ipv6_encap_size;
	अक्षर *encap_header;
	u8 nud_state;
	पूर्णांक err;

	attr.ttl = tun_key->ttl;
	attr.fl.fl6.flowlabel = ip6_make_flowinfo(RT_TOS(tun_key->tos), tun_key->label);
	attr.fl.fl6.daddr = tun_key->u.ipv6.dst;
	attr.fl.fl6.saddr = tun_key->u.ipv6.src;

	err = mlx5e_route_lookup_ipv6_get(priv, mirred_dev, &attr);
	अगर (err)
		वापस err;

	ipv6_encap_size =
		(is_vlan_dev(attr.route_dev) ? VLAN_ETH_HLEN : ETH_HLEN) +
		माप(काष्ठा ipv6hdr) +
		e->tunnel->calc_hlen(e);

	अगर (max_encap_size < ipv6_encap_size) अणु
		mlx5_core_warn(priv->mdev, "encap size %d too big, max supported is %d\n",
			       ipv6_encap_size, max_encap_size);
		err = -EOPNOTSUPP;
		जाओ release_neigh;
	पूर्ण

	encap_header = kzalloc(ipv6_encap_size, GFP_KERNEL);
	अगर (!encap_header) अणु
		err = -ENOMEM;
		जाओ release_neigh;
	पूर्ण

	m_neigh.family = attr.n->ops->family;
	स_नकल(&m_neigh.dst_ip, attr.n->primary_key, attr.n->tbl->key_len);
	e->out_dev = attr.out_dev;
	e->route_dev_अगरindex = attr.route_dev->अगरindex;

	/* It's importent to add the neigh to the hash table beक्रमe checking
	 * the neigh validity state. So अगर we'll get a notअगरication, in हाल the
	 * neigh changes it's validity state, we would find the relevant neigh
	 * in the hash.
	 */
	err = mlx5e_rep_encap_entry_attach(netdev_priv(attr.out_dev), e, &m_neigh, attr.n->dev);
	अगर (err)
		जाओ मुक्त_encap;

	पढ़ो_lock_bh(&attr.n->lock);
	nud_state = attr.n->nud_state;
	ether_addr_copy(e->h_dest, attr.n->ha);
	पढ़ो_unlock_bh(&attr.n->lock);

	/* add ethernet header */
	ip6h = (काष्ठा ipv6hdr *)gen_eth_tnl_hdr(encap_header, attr.route_dev, e,
						 ETH_P_IPV6);

	/* add ip header */
	ip6_flow_hdr(ip6h, tun_key->tos, 0);
	/* the HW fills up ipv6 payload len */
	ip6h->hop_limit   = attr.ttl;
	ip6h->daddr	  = attr.fl.fl6.daddr;
	ip6h->saddr	  = attr.fl.fl6.saddr;

	/* add tunneling protocol header */
	err = mlx5e_gen_ip_tunnel_header((अक्षर *)ip6h + माप(काष्ठा ipv6hdr),
					 &ip6h->nexthdr, e);
	अगर (err)
		जाओ destroy_neigh_entry;

	e->encap_size = ipv6_encap_size;
	e->encap_header = encap_header;

	अगर (!(nud_state & NUD_VALID)) अणु
		neigh_event_send(attr.n, शून्य);
		/* the encap entry will be made valid on neigh update event
		 * and not used beक्रमe that.
		 */
		जाओ release_neigh;
	पूर्ण

	e->pkt_reक्रमmat = mlx5_packet_reक्रमmat_alloc(priv->mdev,
						     e->reक्रमmat_type,
						     ipv6_encap_size, encap_header,
						     MLX5_FLOW_NAMESPACE_FDB);
	अगर (IS_ERR(e->pkt_reक्रमmat)) अणु
		err = PTR_ERR(e->pkt_reक्रमmat);
		जाओ destroy_neigh_entry;
	पूर्ण

	e->flags |= MLX5_ENCAP_ENTRY_VALID;
	mlx5e_rep_queue_neigh_stats_work(netdev_priv(attr.out_dev));
	mlx5e_route_lookup_ipv6_put(&attr);
	वापस err;

destroy_neigh_entry:
	mlx5e_rep_encap_entry_detach(netdev_priv(e->out_dev), e);
मुक्त_encap:
	kमुक्त(encap_header);
release_neigh:
	mlx5e_route_lookup_ipv6_put(&attr);
	वापस err;
पूर्ण

पूर्णांक mlx5e_tc_tun_update_header_ipv6(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *mirred_dev,
				    काष्ठा mlx5e_encap_entry *e)
अणु
	पूर्णांक max_encap_size = MLX5_CAP_ESW(priv->mdev, max_encap_header_size);
	स्थिर काष्ठा ip_tunnel_key *tun_key = &e->tun_info->key;
	TC_TUN_ROUTE_ATTR_INIT(attr);
	काष्ठा ipv6hdr *ip6h;
	पूर्णांक ipv6_encap_size;
	अक्षर *encap_header;
	u8 nud_state;
	पूर्णांक err;

	attr.ttl = tun_key->ttl;

	attr.fl.fl6.flowlabel = ip6_make_flowinfo(RT_TOS(tun_key->tos), tun_key->label);
	attr.fl.fl6.daddr = tun_key->u.ipv6.dst;
	attr.fl.fl6.saddr = tun_key->u.ipv6.src;

	err = mlx5e_route_lookup_ipv6_get(priv, mirred_dev, &attr);
	अगर (err)
		वापस err;

	ipv6_encap_size =
		(is_vlan_dev(attr.route_dev) ? VLAN_ETH_HLEN : ETH_HLEN) +
		माप(काष्ठा ipv6hdr) +
		e->tunnel->calc_hlen(e);

	अगर (max_encap_size < ipv6_encap_size) अणु
		mlx5_core_warn(priv->mdev, "encap size %d too big, max supported is %d\n",
			       ipv6_encap_size, max_encap_size);
		err = -EOPNOTSUPP;
		जाओ release_neigh;
	पूर्ण

	encap_header = kzalloc(ipv6_encap_size, GFP_KERNEL);
	अगर (!encap_header) अणु
		err = -ENOMEM;
		जाओ release_neigh;
	पूर्ण

	e->route_dev_अगरindex = attr.route_dev->अगरindex;

	पढ़ो_lock_bh(&attr.n->lock);
	nud_state = attr.n->nud_state;
	ether_addr_copy(e->h_dest, attr.n->ha);
	WRITE_ONCE(e->nhe->neigh_dev, attr.n->dev);
	पढ़ो_unlock_bh(&attr.n->lock);

	/* add ethernet header */
	ip6h = (काष्ठा ipv6hdr *)gen_eth_tnl_hdr(encap_header, attr.route_dev, e,
						 ETH_P_IPV6);

	/* add ip header */
	ip6_flow_hdr(ip6h, tun_key->tos, 0);
	/* the HW fills up ipv6 payload len */
	ip6h->hop_limit   = attr.ttl;
	ip6h->daddr	  = attr.fl.fl6.daddr;
	ip6h->saddr	  = attr.fl.fl6.saddr;

	/* add tunneling protocol header */
	err = mlx5e_gen_ip_tunnel_header((अक्षर *)ip6h + माप(काष्ठा ipv6hdr),
					 &ip6h->nexthdr, e);
	अगर (err)
		जाओ मुक्त_encap;

	e->encap_size = ipv6_encap_size;
	kमुक्त(e->encap_header);
	e->encap_header = encap_header;

	अगर (!(nud_state & NUD_VALID)) अणु
		neigh_event_send(attr.n, शून्य);
		/* the encap entry will be made valid on neigh update event
		 * and not used beक्रमe that.
		 */
		जाओ release_neigh;
	पूर्ण

	e->pkt_reक्रमmat = mlx5_packet_reक्रमmat_alloc(priv->mdev,
						     e->reक्रमmat_type,
						     ipv6_encap_size, encap_header,
						     MLX5_FLOW_NAMESPACE_FDB);
	अगर (IS_ERR(e->pkt_reक्रमmat)) अणु
		err = PTR_ERR(e->pkt_reक्रमmat);
		जाओ मुक्त_encap;
	पूर्ण

	e->flags |= MLX5_ENCAP_ENTRY_VALID;
	mlx5e_rep_queue_neigh_stats_work(netdev_priv(attr.out_dev));
	mlx5e_route_lookup_ipv6_put(&attr);
	वापस err;

मुक्त_encap:
	kमुक्त(encap_header);
release_neigh:
	mlx5e_route_lookup_ipv6_put(&attr);
	वापस err;
पूर्ण
#पूर्ण_अगर

पूर्णांक mlx5e_tc_tun_route_lookup(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5_flow_spec *spec,
			      काष्ठा mlx5_flow_attr *flow_attr)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = flow_attr->esw_attr;
	TC_TUN_ROUTE_ATTR_INIT(attr);
	u16 vport_num;
	पूर्णांक err = 0;

	अगर (flow_attr->tun_ip_version == 4) अणु
		/* Addresses are swapped क्रम decap */
		attr.fl.fl4.saddr = esw_attr->rx_tun_attr->dst_ip.v4;
		attr.fl.fl4.daddr = esw_attr->rx_tun_attr->src_ip.v4;
		err = mlx5e_route_lookup_ipv4_get(priv, priv->netdev, &attr);
	पूर्ण
#अगर IS_ENABLED(CONFIG_INET) && IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (flow_attr->tun_ip_version == 6) अणु
		/* Addresses are swapped क्रम decap */
		attr.fl.fl6.saddr = esw_attr->rx_tun_attr->dst_ip.v6;
		attr.fl.fl6.daddr = esw_attr->rx_tun_attr->src_ip.v6;
		err = mlx5e_route_lookup_ipv6_get(priv, priv->netdev, &attr);
	पूर्ण
#पूर्ण_अगर
	अन्यथा
		वापस 0;

	अगर (err)
		वापस err;

	अगर (attr.route_dev->netdev_ops != &mlx5e_netdev_ops ||
	    !mlx5e_tc_is_vf_tunnel(attr.out_dev, attr.route_dev))
		जाओ out;

	err = mlx5e_tc_query_route_vport(attr.out_dev, attr.route_dev, &vport_num);
	अगर (err)
		जाओ out;

	esw_attr->rx_tun_attr->vni = MLX5_GET(fte_match_param, spec->match_value,
					      misc_parameters.vxlan_vni);
	esw_attr->rx_tun_attr->decap_vport = vport_num;

out:
	अगर (flow_attr->tun_ip_version == 4)
		mlx5e_route_lookup_ipv4_put(&attr);
#अगर IS_ENABLED(CONFIG_INET) && IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (flow_attr->tun_ip_version == 6)
		mlx5e_route_lookup_ipv6_put(&attr);
#पूर्ण_अगर
	वापस err;
पूर्ण

bool mlx5e_tc_tun_device_to_offload(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_tc_tunnel *tunnel = mlx5e_get_tc_tun(netdev);

	अगर (tunnel && tunnel->can_offload(priv))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

पूर्णांक mlx5e_tc_tun_init_encap_attr(काष्ठा net_device *tunnel_dev,
				 काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_encap_entry *e,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_tc_tunnel *tunnel = mlx5e_get_tc_tun(tunnel_dev);

	अगर (!tunnel) अणु
		e->reक्रमmat_type = -1;
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस tunnel->init_encap_attr(tunnel_dev, priv, e, extack);
पूर्ण

पूर्णांक mlx5e_tc_tun_parse(काष्ठा net_device *filter_dev,
		       काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5_flow_spec *spec,
		       काष्ठा flow_cls_offload *f,
		       u8 *match_level)
अणु
	काष्ठा mlx5e_tc_tunnel *tunnel = mlx5e_get_tc_tun(filter_dev);
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	व्योम *headers_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				       outer_headers);
	व्योम *headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				       outer_headers);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	पूर्णांक err = 0;

	अगर (!tunnel) अणु
		netdev_warn(priv->netdev,
			    "decapsulation offload is not supported for %s net device\n",
			    mlx5e_netdev_kind(filter_dev));
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	*match_level = tunnel->match_level;

	अगर (tunnel->parse_udp_ports) अणु
		err = tunnel->parse_udp_ports(priv, spec, f,
					      headers_c, headers_v);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (tunnel->parse_tunnel) अणु
		err = tunnel->parse_tunnel(priv, spec, f,
					   headers_c, headers_v);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_CONTROL)) अणु
		काष्ठा flow_dissector_key_basic key_basic = अणुपूर्ण;
		काष्ठा flow_dissector_key_basic mask_basic = अणु
			.n_proto = htons(0xFFFF),
		पूर्ण;
		काष्ठा flow_match_basic match_basic = अणु
			.key = &key_basic, .mask = &mask_basic,
		पूर्ण;
		काष्ठा flow_match_control match;
		u16 addr_type;

		flow_rule_match_enc_control(rule, &match);
		addr_type = match.key->addr_type;

		/* For tunnel addr_type used same key id`s as क्रम non-tunnel */
		अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
			काष्ठा flow_match_ipv4_addrs match;

			flow_rule_match_enc_ipv4_addrs(rule, &match);
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 src_ipv4_src_ipv6.ipv4_layout.ipv4,
				 ntohl(match.mask->src));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 src_ipv4_src_ipv6.ipv4_layout.ipv4,
				 ntohl(match.key->src));

			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 dst_ipv4_dst_ipv6.ipv4_layout.ipv4,
				 ntohl(match.mask->dst));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 dst_ipv4_dst_ipv6.ipv4_layout.ipv4,
				 ntohl(match.key->dst));

			key_basic.n_proto = htons(ETH_P_IP);
			mlx5e_tc_set_ethertype(priv->mdev, &match_basic, true,
					       headers_c, headers_v);
		पूर्ण अन्यथा अगर (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
			काष्ठा flow_match_ipv6_addrs match;

			flow_rule_match_enc_ipv6_addrs(rule, &match);
			स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
					    src_ipv4_src_ipv6.ipv6_layout.ipv6),
			       &match.mask->src, MLX5_FLD_SZ_BYTES(ipv6_layout,
								   ipv6));
			स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
					    src_ipv4_src_ipv6.ipv6_layout.ipv6),
			       &match.key->src, MLX5_FLD_SZ_BYTES(ipv6_layout,
								  ipv6));

			स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
					    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
			       &match.mask->dst, MLX5_FLD_SZ_BYTES(ipv6_layout,
								   ipv6));
			स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
					    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
			       &match.key->dst, MLX5_FLD_SZ_BYTES(ipv6_layout,
								  ipv6));

			key_basic.n_proto = htons(ETH_P_IPV6);
			mlx5e_tc_set_ethertype(priv->mdev, &match_basic, true,
					       headers_c, headers_v);
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_IP)) अणु
		काष्ठा flow_match_ip match;

		flow_rule_match_enc_ip(rule, &match);
		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_ecn,
			 match.mask->tos & 0x3);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_ecn,
			 match.key->tos & 0x3);

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_dscp,
			 match.mask->tos >> 2);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_dscp,
			 match.key->tos  >> 2);

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ttl_hoplimit,
			 match.mask->ttl);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ttl_hoplimit,
			 match.key->ttl);

		अगर (match.mask->ttl &&
		    !MLX5_CAP_ESW_FLOWTABLE_FDB
			(priv->mdev,
			 ft_field_support.outer_ipv4_ttl)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Matching on TTL is not supported");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण

	/* let software handle IP fragments */
	MLX5_SET(fte_match_set_lyr_2_4, headers_c, frag, 1);
	MLX5_SET(fte_match_set_lyr_2_4, headers_v, frag, 0);

	वापस 0;

out:
	वापस err;
पूर्ण

पूर्णांक mlx5e_tc_tun_parse_udp_ports(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5_flow_spec *spec,
				 काष्ठा flow_cls_offload *f,
				 व्योम *headers_c,
				 व्योम *headers_v)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा flow_match_ports enc_ports;

	/* Full udp dst port must be given */

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_PORTS)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "UDP tunnel decap filter must include enc_dst_port condition");
		netdev_warn(priv->netdev,
			    "UDP tunnel decap filter must include enc_dst_port condition\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	flow_rule_match_enc_ports(rule, &enc_ports);

	अगर (स_प्रथम_inv(&enc_ports.mask->dst, 0xff,
		       माप(enc_ports.mask->dst))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "UDP tunnel decap filter must match enc_dst_port fully");
		netdev_warn(priv->netdev,
			    "UDP tunnel decap filter must match enc_dst_port fully\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* match on UDP protocol and dst port number */

	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, headers_c, ip_protocol);
	MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_protocol, IPPROTO_UDP);

	MLX5_SET(fte_match_set_lyr_2_4, headers_c, udp_dport,
		 ntohs(enc_ports.mask->dst));
	MLX5_SET(fte_match_set_lyr_2_4, headers_v, udp_dport,
		 ntohs(enc_ports.key->dst));

	/* UDP src port on outer header is generated by HW,
	 * so it is probably a bad idea to request matching it.
	 * Nonetheless, it is allowed.
	 */

	MLX5_SET(fte_match_set_lyr_2_4, headers_c, udp_sport,
		 ntohs(enc_ports.mask->src));
	MLX5_SET(fte_match_set_lyr_2_4, headers_v, udp_sport,
		 ntohs(enc_ports.key->src));

	वापस 0;
पूर्ण

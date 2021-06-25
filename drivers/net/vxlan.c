<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VXLAN: Virtual eXtensible Local Area Network
 *
 * Copyright (c) 2012-2013 Vyatta Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/udp.h>
#समावेश <linux/igmp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ethtool.h>
#समावेश <net/arp.h>
#समावेश <net/ndisc.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/tun_proto.h>
#समावेश <net/vxlan.h>
#समावेश <net/nexthop.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ip6_tunnel.h>
#समावेश <net/ip6_checksum.h>
#पूर्ण_अगर

#घोषणा VXLAN_VERSION	"0.1"

#घोषणा PORT_HASH_BITS	8
#घोषणा PORT_HASH_SIZE  (1<<PORT_HASH_BITS)
#घोषणा FDB_AGE_DEFAULT 300 /* 5 min */
#घोषणा FDB_AGE_INTERVAL (10 * HZ)	/* rescan पूर्णांकerval */

/* UDP port क्रम VXLAN traffic.
 * The IANA asचिन्हित port is 4789, but the Linux शेष is 8472
 * क्रम compatibility with early aकरोpters.
 */
अटल अचिन्हित लघु vxlan_port __पढ़ो_mostly = 8472;
module_param_named(udp_port, vxlan_port, uलघु, 0444);
MODULE_PARM_DESC(udp_port, "Destination UDP port");

अटल bool log_ecn_error = true;
module_param(log_ecn_error, bool, 0644);
MODULE_PARM_DESC(log_ecn_error, "Log packets received with corrupted ECN");

अटल अचिन्हित पूर्णांक vxlan_net_id;
अटल काष्ठा rtnl_link_ops vxlan_link_ops;

अटल स्थिर u8 all_zeros_mac[ETH_ALEN + 2];

अटल पूर्णांक vxlan_sock_add(काष्ठा vxlan_dev *vxlan);

अटल व्योम vxlan_vs_del_dev(काष्ठा vxlan_dev *vxlan);

/* per-network namespace निजी data क्रम this module */
काष्ठा vxlan_net अणु
	काष्ठा list_head  vxlan_list;
	काष्ठा hlist_head sock_list[PORT_HASH_SIZE];
	spinlock_t	  sock_lock;
	काष्ठा notअगरier_block nexthop_notअगरier_block;
पूर्ण;

/* Forwarding table entry */
काष्ठा vxlan_fdb अणु
	काष्ठा hlist_node hlist;	/* linked list of entries */
	काष्ठा rcu_head	  rcu;
	अचिन्हित दीर्घ	  updated;	/* jअगरfies */
	अचिन्हित दीर्घ	  used;
	काष्ठा list_head  remotes;
	u8		  eth_addr[ETH_ALEN];
	u16		  state;	/* see ndm_state */
	__be32		  vni;
	u16		  flags;	/* see ndm_flags and below */
	काष्ठा list_head  nh_list;
	काष्ठा nexthop __rcu *nh;
	काष्ठा vxlan_dev  __rcu *vdev;
पूर्ण;

#घोषणा NTF_VXLAN_ADDED_BY_USER 0x100

/* salt क्रम hash table */
अटल u32 vxlan_salt __पढ़ो_mostly;

अटल अंतरभूत bool vxlan_collect_metadata(काष्ठा vxlan_sock *vs)
अणु
	वापस vs->flags & VXLAN_F_COLLECT_METADATA ||
	       ip_tunnel_collect_metadata();
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत
bool vxlan_addr_equal(स्थिर जोड़ vxlan_addr *a, स्थिर जोड़ vxlan_addr *b)
अणु
	अगर (a->sa.sa_family != b->sa.sa_family)
		वापस false;
	अगर (a->sa.sa_family == AF_INET6)
		वापस ipv6_addr_equal(&a->sin6.sin6_addr, &b->sin6.sin6_addr);
	अन्यथा
		वापस a->sin.sin_addr.s_addr == b->sin.sin_addr.s_addr;
पूर्ण

अटल पूर्णांक vxlan_nla_get_addr(जोड़ vxlan_addr *ip, काष्ठा nlattr *nla)
अणु
	अगर (nla_len(nla) >= माप(काष्ठा in6_addr)) अणु
		ip->sin6.sin6_addr = nla_get_in6_addr(nla);
		ip->sa.sa_family = AF_INET6;
		वापस 0;
	पूर्ण अन्यथा अगर (nla_len(nla) >= माप(__be32)) अणु
		ip->sin.sin_addr.s_addr = nla_get_in_addr(nla);
		ip->sa.sa_family = AF_INET;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EAFNOSUPPORT;
	पूर्ण
पूर्ण

अटल पूर्णांक vxlan_nla_put_addr(काष्ठा sk_buff *skb, पूर्णांक attr,
			      स्थिर जोड़ vxlan_addr *ip)
अणु
	अगर (ip->sa.sa_family == AF_INET6)
		वापस nla_put_in6_addr(skb, attr, &ip->sin6.sin6_addr);
	अन्यथा
		वापस nla_put_in_addr(skb, attr, ip->sin.sin_addr.s_addr);
पूर्ण

#अन्यथा /* !CONFIG_IPV6 */

अटल अंतरभूत
bool vxlan_addr_equal(स्थिर जोड़ vxlan_addr *a, स्थिर जोड़ vxlan_addr *b)
अणु
	वापस a->sin.sin_addr.s_addr == b->sin.sin_addr.s_addr;
पूर्ण

अटल पूर्णांक vxlan_nla_get_addr(जोड़ vxlan_addr *ip, काष्ठा nlattr *nla)
अणु
	अगर (nla_len(nla) >= माप(काष्ठा in6_addr)) अणु
		वापस -EAFNOSUPPORT;
	पूर्ण अन्यथा अगर (nla_len(nla) >= माप(__be32)) अणु
		ip->sin.sin_addr.s_addr = nla_get_in_addr(nla);
		ip->sa.sa_family = AF_INET;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EAFNOSUPPORT;
	पूर्ण
पूर्ण

अटल पूर्णांक vxlan_nla_put_addr(काष्ठा sk_buff *skb, पूर्णांक attr,
			      स्थिर जोड़ vxlan_addr *ip)
अणु
	वापस nla_put_in_addr(skb, attr, ip->sin.sin_addr.s_addr);
पूर्ण
#पूर्ण_अगर

/* Virtual Network hash table head */
अटल अंतरभूत काष्ठा hlist_head *vni_head(काष्ठा vxlan_sock *vs, __be32 vni)
अणु
	वापस &vs->vni_list[hash_32((__क्रमce u32)vni, VNI_HASH_BITS)];
पूर्ण

/* Socket hash table head */
अटल अंतरभूत काष्ठा hlist_head *vs_head(काष्ठा net *net, __be16 port)
अणु
	काष्ठा vxlan_net *vn = net_generic(net, vxlan_net_id);

	वापस &vn->sock_list[hash_32(ntohs(port), PORT_HASH_BITS)];
पूर्ण

/* First remote destination क्रम a क्रमwarding entry.
 * Guaranteed to be non-शून्य because remotes are never deleted.
 */
अटल अंतरभूत काष्ठा vxlan_rdst *first_remote_rcu(काष्ठा vxlan_fdb *fdb)
अणु
	अगर (rcu_access_poपूर्णांकer(fdb->nh))
		वापस शून्य;
	वापस list_entry_rcu(fdb->remotes.next, काष्ठा vxlan_rdst, list);
पूर्ण

अटल अंतरभूत काष्ठा vxlan_rdst *first_remote_rtnl(काष्ठा vxlan_fdb *fdb)
अणु
	अगर (rcu_access_poपूर्णांकer(fdb->nh))
		वापस शून्य;
	वापस list_first_entry(&fdb->remotes, काष्ठा vxlan_rdst, list);
पूर्ण

/* Find VXLAN socket based on network namespace, address family, UDP port,
 * enabled unshareable flags and socket device binding (see l3mdev with
 * non-शेष VRF).
 */
अटल काष्ठा vxlan_sock *vxlan_find_sock(काष्ठा net *net, sa_family_t family,
					  __be16 port, u32 flags, पूर्णांक अगरindex)
अणु
	काष्ठा vxlan_sock *vs;

	flags &= VXLAN_F_RCV_FLAGS;

	hlist_क्रम_each_entry_rcu(vs, vs_head(net, port), hlist) अणु
		अगर (inet_sk(vs->sock->sk)->inet_sport == port &&
		    vxlan_get_sk_family(vs) == family &&
		    vs->flags == flags &&
		    vs->sock->sk->sk_bound_dev_अगर == अगरindex)
			वापस vs;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा vxlan_dev *vxlan_vs_find_vni(काष्ठा vxlan_sock *vs, पूर्णांक अगरindex,
					   __be32 vni)
अणु
	काष्ठा vxlan_dev_node *node;

	/* For flow based devices, map all packets to VNI 0 */
	अगर (vs->flags & VXLAN_F_COLLECT_METADATA)
		vni = 0;

	hlist_क्रम_each_entry_rcu(node, vni_head(vs, vni), hlist) अणु
		अगर (node->vxlan->शेष_dst.remote_vni != vni)
			जारी;

		अगर (IS_ENABLED(CONFIG_IPV6)) अणु
			स्थिर काष्ठा vxlan_config *cfg = &node->vxlan->cfg;

			अगर ((cfg->flags & VXLAN_F_IPV6_LINKLOCAL) &&
			    cfg->remote_अगरindex != अगरindex)
				जारी;
		पूर्ण

		वापस node->vxlan;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Look up VNI in a per net namespace table */
अटल काष्ठा vxlan_dev *vxlan_find_vni(काष्ठा net *net, पूर्णांक अगरindex,
					__be32 vni, sa_family_t family,
					__be16 port, u32 flags)
अणु
	काष्ठा vxlan_sock *vs;

	vs = vxlan_find_sock(net, family, port, flags, अगरindex);
	अगर (!vs)
		वापस शून्य;

	वापस vxlan_vs_find_vni(vs, अगरindex, vni);
पूर्ण

/* Fill in neighbour message in skbuff. */
अटल पूर्णांक vxlan_fdb_info(काष्ठा sk_buff *skb, काष्ठा vxlan_dev *vxlan,
			  स्थिर काष्ठा vxlan_fdb *fdb,
			  u32 portid, u32 seq, पूर्णांक type, अचिन्हित पूर्णांक flags,
			  स्थिर काष्ठा vxlan_rdst *rdst)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा nda_cacheinfo ci;
	bool send_ip, send_eth;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nexthop *nh;
	काष्ठा ndmsg *ndm;
	पूर्णांक nh_family;
	u32 nh_id;

	nlh = nlmsg_put(skb, portid, seq, type, माप(*ndm), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	स_रखो(ndm, 0, माप(*ndm));

	send_eth = send_ip = true;

	rcu_पढ़ो_lock();
	nh = rcu_dereference(fdb->nh);
	अगर (nh) अणु
		nh_family = nexthop_get_family(nh);
		nh_id = nh->id;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (type == RTM_GETNEIGH) अणु
		अगर (rdst) अणु
			send_ip = !vxlan_addr_any(&rdst->remote_ip);
			ndm->ndm_family = send_ip ? rdst->remote_ip.sa.sa_family : AF_INET;
		पूर्ण अन्यथा अगर (nh) अणु
			ndm->ndm_family = nh_family;
		पूर्ण
		send_eth = !is_zero_ether_addr(fdb->eth_addr);
	पूर्ण अन्यथा
		ndm->ndm_family	= AF_BRIDGE;
	ndm->ndm_state = fdb->state;
	ndm->ndm_अगरindex = vxlan->dev->अगरindex;
	ndm->ndm_flags = fdb->flags;
	अगर (rdst && rdst->offloaded)
		ndm->ndm_flags |= NTF_OFFLOADED;
	ndm->ndm_type = RTN_UNICAST;

	अगर (!net_eq(dev_net(vxlan->dev), vxlan->net) &&
	    nla_put_s32(skb, NDA_LINK_NETNSID,
			peernet2id(dev_net(vxlan->dev), vxlan->net)))
		जाओ nla_put_failure;

	अगर (send_eth && nla_put(skb, NDA_LLADDR, ETH_ALEN, &fdb->eth_addr))
		जाओ nla_put_failure;
	अगर (nh) अणु
		अगर (nla_put_u32(skb, NDA_NH_ID, nh_id))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अगर (rdst) अणु
		अगर (send_ip && vxlan_nla_put_addr(skb, NDA_DST,
						  &rdst->remote_ip))
			जाओ nla_put_failure;

		अगर (rdst->remote_port &&
		    rdst->remote_port != vxlan->cfg.dst_port &&
		    nla_put_be16(skb, NDA_PORT, rdst->remote_port))
			जाओ nla_put_failure;
		अगर (rdst->remote_vni != vxlan->शेष_dst.remote_vni &&
		    nla_put_u32(skb, NDA_VNI, be32_to_cpu(rdst->remote_vni)))
			जाओ nla_put_failure;
		अगर (rdst->remote_अगरindex &&
		    nla_put_u32(skb, NDA_IFINDEX, rdst->remote_अगरindex))
			जाओ nla_put_failure;
	पूर्ण

	अगर ((vxlan->cfg.flags & VXLAN_F_COLLECT_METADATA) && fdb->vni &&
	    nla_put_u32(skb, NDA_SRC_VNI,
			be32_to_cpu(fdb->vni)))
		जाओ nla_put_failure;

	ci.ndm_used	 = jअगरfies_to_घड़ी_प्रकार(now - fdb->used);
	ci.ndm_confirmed = 0;
	ci.ndm_updated	 = jअगरfies_to_घड़ी_प्रकार(now - fdb->updated);
	ci.ndm_refcnt	 = 0;

	अगर (nla_put(skb, NDA_CACHEINFO, माप(ci), &ci))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल अंतरभूत माप_प्रकार vxlan_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा ndmsg))
		+ nla_total_size(ETH_ALEN) /* NDA_LLADDR */
		+ nla_total_size(माप(काष्ठा in6_addr)) /* NDA_DST */
		+ nla_total_size(माप(__be16)) /* NDA_PORT */
		+ nla_total_size(माप(__be32)) /* NDA_VNI */
		+ nla_total_size(माप(__u32)) /* NDA_IFINDEX */
		+ nla_total_size(माप(__s32)) /* NDA_LINK_NETNSID */
		+ nla_total_size(माप(काष्ठा nda_cacheinfo));
पूर्ण

अटल व्योम __vxlan_fdb_notअगरy(काष्ठा vxlan_dev *vxlan, काष्ठा vxlan_fdb *fdb,
			       काष्ठा vxlan_rdst *rd, पूर्णांक type)
अणु
	काष्ठा net *net = dev_net(vxlan->dev);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(vxlan_nlmsg_size(), GFP_ATOMIC);
	अगर (skb == शून्य)
		जाओ errout;

	err = vxlan_fdb_info(skb, vxlan, fdb, 0, 0, type, 0, rd);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in vxlan_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, net, 0, RTNLGRP_NEIGH, शून्य, GFP_ATOMIC);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_NEIGH, err);
पूर्ण

अटल व्योम vxlan_fdb_चयनdev_notअगरier_info(स्थिर काष्ठा vxlan_dev *vxlan,
			    स्थिर काष्ठा vxlan_fdb *fdb,
			    स्थिर काष्ठा vxlan_rdst *rd,
			    काष्ठा netlink_ext_ack *extack,
			    काष्ठा चयनdev_notअगरier_vxlan_fdb_info *fdb_info)
अणु
	fdb_info->info.dev = vxlan->dev;
	fdb_info->info.extack = extack;
	fdb_info->remote_ip = rd->remote_ip;
	fdb_info->remote_port = rd->remote_port;
	fdb_info->remote_vni = rd->remote_vni;
	fdb_info->remote_अगरindex = rd->remote_अगरindex;
	स_नकल(fdb_info->eth_addr, fdb->eth_addr, ETH_ALEN);
	fdb_info->vni = fdb->vni;
	fdb_info->offloaded = rd->offloaded;
	fdb_info->added_by_user = fdb->flags & NTF_VXLAN_ADDED_BY_USER;
पूर्ण

अटल पूर्णांक vxlan_fdb_चयनdev_call_notअगरiers(काष्ठा vxlan_dev *vxlan,
					      काष्ठा vxlan_fdb *fdb,
					      काष्ठा vxlan_rdst *rd,
					      bool adding,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_notअगरier_vxlan_fdb_info info;
	क्रमागत चयनdev_notअगरier_type notअगरier_type;
	पूर्णांक ret;

	अगर (WARN_ON(!rd))
		वापस 0;

	notअगरier_type = adding ? SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE
			       : SWITCHDEV_VXLAN_FDB_DEL_TO_DEVICE;
	vxlan_fdb_चयनdev_notअगरier_info(vxlan, fdb, rd, शून्य, &info);
	ret = call_चयनdev_notअगरiers(notअगरier_type, vxlan->dev,
				       &info.info, extack);
	वापस notअगरier_to_त्रुटि_सं(ret);
पूर्ण

अटल पूर्णांक vxlan_fdb_notअगरy(काष्ठा vxlan_dev *vxlan, काष्ठा vxlan_fdb *fdb,
			    काष्ठा vxlan_rdst *rd, पूर्णांक type, bool swdev_notअगरy,
			    काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	अगर (swdev_notअगरy && rd) अणु
		चयन (type) अणु
		हाल RTM_NEWNEIGH:
			err = vxlan_fdb_चयनdev_call_notअगरiers(vxlan, fdb, rd,
								 true, extack);
			अगर (err)
				वापस err;
			अवरोध;
		हाल RTM_DELNEIGH:
			vxlan_fdb_चयनdev_call_notअगरiers(vxlan, fdb, rd,
							   false, extack);
			अवरोध;
		पूर्ण
	पूर्ण

	__vxlan_fdb_notअगरy(vxlan, fdb, rd, type);
	वापस 0;
पूर्ण

अटल व्योम vxlan_ip_miss(काष्ठा net_device *dev, जोड़ vxlan_addr *ipa)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_fdb f = अणु
		.state = NUD_STALE,
	पूर्ण;
	काष्ठा vxlan_rdst remote = अणु
		.remote_ip = *ipa, /* goes to NDA_DST */
		.remote_vni = cpu_to_be32(VXLAN_N_VID),
	पूर्ण;

	vxlan_fdb_notअगरy(vxlan, &f, &remote, RTM_GETNEIGH, true, शून्य);
पूर्ण

अटल व्योम vxlan_fdb_miss(काष्ठा vxlan_dev *vxlan, स्थिर u8 eth_addr[ETH_ALEN])
अणु
	काष्ठा vxlan_fdb f = अणु
		.state = NUD_STALE,
	पूर्ण;
	काष्ठा vxlan_rdst remote = अणु पूर्ण;

	स_नकल(f.eth_addr, eth_addr, ETH_ALEN);

	vxlan_fdb_notअगरy(vxlan, &f, &remote, RTM_GETNEIGH, true, शून्य);
पूर्ण

/* Hash Ethernet address */
अटल u32 eth_hash(स्थिर अचिन्हित अक्षर *addr)
अणु
	u64 value = get_unaligned((u64 *)addr);

	/* only want 6 bytes */
#अगर_घोषित __BIG_ENDIAN
	value >>= 16;
#अन्यथा
	value <<= 16;
#पूर्ण_अगर
	वापस hash_64(value, FDB_HASH_BITS);
पूर्ण

अटल u32 eth_vni_hash(स्थिर अचिन्हित अक्षर *addr, __be32 vni)
अणु
	/* use 1 byte of OUI and 3 bytes of NIC */
	u32 key = get_unaligned((u32 *)(addr + 2));

	वापस jhash_2words(key, vni, vxlan_salt) & (FDB_HASH_SIZE - 1);
पूर्ण

अटल u32 fdb_head_index(काष्ठा vxlan_dev *vxlan, स्थिर u8 *mac, __be32 vni)
अणु
	अगर (vxlan->cfg.flags & VXLAN_F_COLLECT_METADATA)
		वापस eth_vni_hash(mac, vni);
	अन्यथा
		वापस eth_hash(mac);
पूर्ण

/* Hash chain to use given mac address */
अटल अंतरभूत काष्ठा hlist_head *vxlan_fdb_head(काष्ठा vxlan_dev *vxlan,
						स्थिर u8 *mac, __be32 vni)
अणु
	वापस &vxlan->fdb_head[fdb_head_index(vxlan, mac, vni)];
पूर्ण

/* Look up Ethernet address in क्रमwarding table */
अटल काष्ठा vxlan_fdb *__vxlan_find_mac(काष्ठा vxlan_dev *vxlan,
					  स्थिर u8 *mac, __be32 vni)
अणु
	काष्ठा hlist_head *head = vxlan_fdb_head(vxlan, mac, vni);
	काष्ठा vxlan_fdb *f;

	hlist_क्रम_each_entry_rcu(f, head, hlist) अणु
		अगर (ether_addr_equal(mac, f->eth_addr)) अणु
			अगर (vxlan->cfg.flags & VXLAN_F_COLLECT_METADATA) अणु
				अगर (vni == f->vni)
					वापस f;
			पूर्ण अन्यथा अणु
				वापस f;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा vxlan_fdb *vxlan_find_mac(काष्ठा vxlan_dev *vxlan,
					स्थिर u8 *mac, __be32 vni)
अणु
	काष्ठा vxlan_fdb *f;

	f = __vxlan_find_mac(vxlan, mac, vni);
	अगर (f && f->used != jअगरfies)
		f->used = jअगरfies;

	वापस f;
पूर्ण

/* caller should hold vxlan->hash_lock */
अटल काष्ठा vxlan_rdst *vxlan_fdb_find_rdst(काष्ठा vxlan_fdb *f,
					      जोड़ vxlan_addr *ip, __be16 port,
					      __be32 vni, __u32 अगरindex)
अणु
	काष्ठा vxlan_rdst *rd;

	list_क्रम_each_entry(rd, &f->remotes, list) अणु
		अगर (vxlan_addr_equal(&rd->remote_ip, ip) &&
		    rd->remote_port == port &&
		    rd->remote_vni == vni &&
		    rd->remote_अगरindex == अगरindex)
			वापस rd;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक vxlan_fdb_find_uc(काष्ठा net_device *dev, स्थिर u8 *mac, __be32 vni,
		      काष्ठा चयनdev_notअगरier_vxlan_fdb_info *fdb_info)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	u8 eth_addr[ETH_ALEN + 2] = अणु 0 पूर्ण;
	काष्ठा vxlan_rdst *rdst;
	काष्ठा vxlan_fdb *f;
	पूर्णांक rc = 0;

	अगर (is_multicast_ether_addr(mac) ||
	    is_zero_ether_addr(mac))
		वापस -EINVAL;

	ether_addr_copy(eth_addr, mac);

	rcu_पढ़ो_lock();

	f = __vxlan_find_mac(vxlan, eth_addr, vni);
	अगर (!f) अणु
		rc = -ENOENT;
		जाओ out;
	पूर्ण

	rdst = first_remote_rcu(f);
	vxlan_fdb_चयनdev_notअगरier_info(vxlan, f, rdst, शून्य, fdb_info);

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(vxlan_fdb_find_uc);

अटल पूर्णांक vxlan_fdb_notअगरy_one(काष्ठा notअगरier_block *nb,
				स्थिर काष्ठा vxlan_dev *vxlan,
				स्थिर काष्ठा vxlan_fdb *f,
				स्थिर काष्ठा vxlan_rdst *rdst,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_notअगरier_vxlan_fdb_info fdb_info;
	पूर्णांक rc;

	vxlan_fdb_चयनdev_notअगरier_info(vxlan, f, rdst, extack, &fdb_info);
	rc = nb->notअगरier_call(nb, SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE,
			       &fdb_info);
	वापस notअगरier_to_त्रुटि_सं(rc);
पूर्ण

पूर्णांक vxlan_fdb_replay(स्थिर काष्ठा net_device *dev, __be32 vni,
		     काष्ठा notअगरier_block *nb,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_dev *vxlan;
	काष्ठा vxlan_rdst *rdst;
	काष्ठा vxlan_fdb *f;
	अचिन्हित पूर्णांक h;
	पूर्णांक rc = 0;

	अगर (!netअगर_is_vxlan(dev))
		वापस -EINVAL;
	vxlan = netdev_priv(dev);

	क्रम (h = 0; h < FDB_HASH_SIZE; ++h) अणु
		spin_lock_bh(&vxlan->hash_lock[h]);
		hlist_क्रम_each_entry(f, &vxlan->fdb_head[h], hlist) अणु
			अगर (f->vni == vni) अणु
				list_क्रम_each_entry(rdst, &f->remotes, list) अणु
					rc = vxlan_fdb_notअगरy_one(nb, vxlan,
								  f, rdst,
								  extack);
					अगर (rc)
						जाओ unlock;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock_bh(&vxlan->hash_lock[h]);
	पूर्ण
	वापस 0;

unlock:
	spin_unlock_bh(&vxlan->hash_lock[h]);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(vxlan_fdb_replay);

व्योम vxlan_fdb_clear_offload(स्थिर काष्ठा net_device *dev, __be32 vni)
अणु
	काष्ठा vxlan_dev *vxlan;
	काष्ठा vxlan_rdst *rdst;
	काष्ठा vxlan_fdb *f;
	अचिन्हित पूर्णांक h;

	अगर (!netअगर_is_vxlan(dev))
		वापस;
	vxlan = netdev_priv(dev);

	क्रम (h = 0; h < FDB_HASH_SIZE; ++h) अणु
		spin_lock_bh(&vxlan->hash_lock[h]);
		hlist_क्रम_each_entry(f, &vxlan->fdb_head[h], hlist)
			अगर (f->vni == vni)
				list_क्रम_each_entry(rdst, &f->remotes, list)
					rdst->offloaded = false;
		spin_unlock_bh(&vxlan->hash_lock[h]);
	पूर्ण

पूर्ण
EXPORT_SYMBOL_GPL(vxlan_fdb_clear_offload);

/* Replace destination of unicast mac */
अटल पूर्णांक vxlan_fdb_replace(काष्ठा vxlan_fdb *f,
			     जोड़ vxlan_addr *ip, __be16 port, __be32 vni,
			     __u32 अगरindex, काष्ठा vxlan_rdst *oldrd)
अणु
	काष्ठा vxlan_rdst *rd;

	rd = vxlan_fdb_find_rdst(f, ip, port, vni, अगरindex);
	अगर (rd)
		वापस 0;

	rd = list_first_entry_or_null(&f->remotes, काष्ठा vxlan_rdst, list);
	अगर (!rd)
		वापस 0;

	*oldrd = *rd;
	dst_cache_reset(&rd->dst_cache);
	rd->remote_ip = *ip;
	rd->remote_port = port;
	rd->remote_vni = vni;
	rd->remote_अगरindex = अगरindex;
	rd->offloaded = false;
	वापस 1;
पूर्ण

/* Add/update destinations क्रम multicast */
अटल पूर्णांक vxlan_fdb_append(काष्ठा vxlan_fdb *f,
			    जोड़ vxlan_addr *ip, __be16 port, __be32 vni,
			    __u32 अगरindex, काष्ठा vxlan_rdst **rdp)
अणु
	काष्ठा vxlan_rdst *rd;

	rd = vxlan_fdb_find_rdst(f, ip, port, vni, अगरindex);
	अगर (rd)
		वापस 0;

	rd = kदो_स्मृति(माप(*rd), GFP_ATOMIC);
	अगर (rd == शून्य)
		वापस -ENOBUFS;

	अगर (dst_cache_init(&rd->dst_cache, GFP_ATOMIC)) अणु
		kमुक्त(rd);
		वापस -ENOBUFS;
	पूर्ण

	rd->remote_ip = *ip;
	rd->remote_port = port;
	rd->offloaded = false;
	rd->remote_vni = vni;
	rd->remote_अगरindex = अगरindex;

	list_add_tail_rcu(&rd->list, &f->remotes);

	*rdp = rd;
	वापस 1;
पूर्ण

अटल काष्ठा vxlanhdr *vxlan_gro_remcsum(काष्ठा sk_buff *skb,
					  अचिन्हित पूर्णांक off,
					  काष्ठा vxlanhdr *vh, माप_प्रकार hdrlen,
					  __be32 vni_field,
					  काष्ठा gro_remcsum *grc,
					  bool nopartial)
अणु
	माप_प्रकार start, offset;

	अगर (skb->remcsum_offload)
		वापस vh;

	अगर (!NAPI_GRO_CB(skb)->csum_valid)
		वापस शून्य;

	start = vxlan_rco_start(vni_field);
	offset = start + vxlan_rco_offset(vni_field);

	vh = skb_gro_remcsum_process(skb, (व्योम *)vh, off, hdrlen,
				     start, offset, grc, nopartial);

	skb->remcsum_offload = 1;

	वापस vh;
पूर्ण

अटल काष्ठा sk_buff *vxlan_gro_receive(काष्ठा sock *sk,
					 काष्ठा list_head *head,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा sk_buff *p;
	काष्ठा vxlanhdr *vh, *vh2;
	अचिन्हित पूर्णांक hlen, off_vx;
	पूर्णांक flush = 1;
	काष्ठा vxlan_sock *vs = rcu_dereference_sk_user_data(sk);
	__be32 flags;
	काष्ठा gro_remcsum grc;

	skb_gro_remcsum_init(&grc);

	off_vx = skb_gro_offset(skb);
	hlen = off_vx + माप(*vh);
	vh   = skb_gro_header_fast(skb, off_vx);
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		vh = skb_gro_header_slow(skb, hlen, off_vx);
		अगर (unlikely(!vh))
			जाओ out;
	पूर्ण

	skb_gro_postpull_rcsum(skb, vh, माप(काष्ठा vxlanhdr));

	flags = vh->vx_flags;

	अगर ((flags & VXLAN_HF_RCO) && (vs->flags & VXLAN_F_REMCSUM_RX)) अणु
		vh = vxlan_gro_remcsum(skb, off_vx, vh, माप(काष्ठा vxlanhdr),
				       vh->vx_vni, &grc,
				       !!(vs->flags &
					  VXLAN_F_REMCSUM_NOPARTIAL));

		अगर (!vh)
			जाओ out;
	पूर्ण

	skb_gro_pull(skb, माप(काष्ठा vxlanhdr)); /* pull vxlan header */

	list_क्रम_each_entry(p, head, list) अणु
		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		vh2 = (काष्ठा vxlanhdr *)(p->data + off_vx);
		अगर (vh->vx_flags != vh2->vx_flags ||
		    vh->vx_vni != vh2->vx_vni) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण
	पूर्ण

	pp = call_gro_receive(eth_gro_receive, head, skb);
	flush = 0;

out:
	skb_gro_flush_final_remcsum(skb, pp, flush, &grc);

	वापस pp;
पूर्ण

अटल पूर्णांक vxlan_gro_complete(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	/* Sets 'skb->inner_mac_header' since we are always called with
	 * 'skb->encapsulation' set.
	 */
	वापस eth_gro_complete(skb, nhoff + माप(काष्ठा vxlanhdr));
पूर्ण

अटल काष्ठा vxlan_fdb *vxlan_fdb_alloc(काष्ठा vxlan_dev *vxlan, स्थिर u8 *mac,
					 __u16 state, __be32 src_vni,
					 __u16 ndm_flags)
अणु
	काष्ठा vxlan_fdb *f;

	f = kदो_स्मृति(माप(*f), GFP_ATOMIC);
	अगर (!f)
		वापस शून्य;
	f->state = state;
	f->flags = ndm_flags;
	f->updated = f->used = jअगरfies;
	f->vni = src_vni;
	f->nh = शून्य;
	RCU_INIT_POINTER(f->vdev, vxlan);
	INIT_LIST_HEAD(&f->nh_list);
	INIT_LIST_HEAD(&f->remotes);
	स_नकल(f->eth_addr, mac, ETH_ALEN);

	वापस f;
पूर्ण

अटल व्योम vxlan_fdb_insert(काष्ठा vxlan_dev *vxlan, स्थिर u8 *mac,
			     __be32 src_vni, काष्ठा vxlan_fdb *f)
अणु
	++vxlan->addrcnt;
	hlist_add_head_rcu(&f->hlist,
			   vxlan_fdb_head(vxlan, mac, src_vni));
पूर्ण

अटल पूर्णांक vxlan_fdb_nh_update(काष्ठा vxlan_dev *vxlan, काष्ठा vxlan_fdb *fdb,
			       u32 nhid, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nexthop *old_nh = rtnl_dereference(fdb->nh);
	काष्ठा nexthop *nh;
	पूर्णांक err = -EINVAL;

	अगर (old_nh && old_nh->id == nhid)
		वापस 0;

	nh = nexthop_find_by_id(vxlan->net, nhid);
	अगर (!nh) अणु
		NL_SET_ERR_MSG(extack, "Nexthop id does not exist");
		जाओ err_inval;
	पूर्ण

	अगर (nh) अणु
		अगर (!nexthop_get(nh)) अणु
			NL_SET_ERR_MSG(extack, "Nexthop has been deleted");
			nh = शून्य;
			जाओ err_inval;
		पूर्ण
		अगर (!nexthop_is_fdb(nh)) अणु
			NL_SET_ERR_MSG(extack, "Nexthop is not a fdb nexthop");
			जाओ err_inval;
		पूर्ण

		अगर (!nexthop_is_multipath(nh)) अणु
			NL_SET_ERR_MSG(extack, "Nexthop is not a multipath group");
			जाओ err_inval;
		पूर्ण

		/* check nexthop group family */
		चयन (vxlan->शेष_dst.remote_ip.sa.sa_family) अणु
		हाल AF_INET:
			अगर (!nexthop_has_v4(nh)) अणु
				err = -EAFNOSUPPORT;
				NL_SET_ERR_MSG(extack, "Nexthop group family not supported");
				जाओ err_inval;
			पूर्ण
			अवरोध;
		हाल AF_INET6:
			अगर (nexthop_has_v4(nh)) अणु
				err = -EAFNOSUPPORT;
				NL_SET_ERR_MSG(extack, "Nexthop group family not supported");
				जाओ err_inval;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (old_nh) अणु
		list_del_rcu(&fdb->nh_list);
		nexthop_put(old_nh);
	पूर्ण
	rcu_assign_poपूर्णांकer(fdb->nh, nh);
	list_add_tail_rcu(&fdb->nh_list, &nh->fdb_list);
	वापस 1;

err_inval:
	अगर (nh)
		nexthop_put(nh);
	वापस err;
पूर्ण

अटल पूर्णांक vxlan_fdb_create(काष्ठा vxlan_dev *vxlan,
			    स्थिर u8 *mac, जोड़ vxlan_addr *ip,
			    __u16 state, __be16 port, __be32 src_vni,
			    __be32 vni, __u32 अगरindex, __u16 ndm_flags,
			    u32 nhid, काष्ठा vxlan_fdb **fdb,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_rdst *rd = शून्य;
	काष्ठा vxlan_fdb *f;
	पूर्णांक rc;

	अगर (vxlan->cfg.addrmax &&
	    vxlan->addrcnt >= vxlan->cfg.addrmax)
		वापस -ENOSPC;

	netdev_dbg(vxlan->dev, "add %pM -> %pIS\n", mac, ip);
	f = vxlan_fdb_alloc(vxlan, mac, state, src_vni, ndm_flags);
	अगर (!f)
		वापस -ENOMEM;

	अगर (nhid)
		rc = vxlan_fdb_nh_update(vxlan, f, nhid, extack);
	अन्यथा
		rc = vxlan_fdb_append(f, ip, port, vni, अगरindex, &rd);
	अगर (rc < 0)
		जाओ errout;

	*fdb = f;

	वापस 0;

errout:
	kमुक्त(f);
	वापस rc;
पूर्ण

अटल व्योम __vxlan_fdb_मुक्त(काष्ठा vxlan_fdb *f)
अणु
	काष्ठा vxlan_rdst *rd, *nd;
	काष्ठा nexthop *nh;

	nh = rcu_dereference_raw(f->nh);
	अगर (nh) अणु
		rcu_assign_poपूर्णांकer(f->nh, शून्य);
		rcu_assign_poपूर्णांकer(f->vdev, शून्य);
		nexthop_put(nh);
	पूर्ण

	list_क्रम_each_entry_safe(rd, nd, &f->remotes, list) अणु
		dst_cache_destroy(&rd->dst_cache);
		kमुक्त(rd);
	पूर्ण
	kमुक्त(f);
पूर्ण

अटल व्योम vxlan_fdb_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा vxlan_fdb *f = container_of(head, काष्ठा vxlan_fdb, rcu);

	__vxlan_fdb_मुक्त(f);
पूर्ण

अटल व्योम vxlan_fdb_destroy(काष्ठा vxlan_dev *vxlan, काष्ठा vxlan_fdb *f,
			      bool करो_notअगरy, bool swdev_notअगरy)
अणु
	काष्ठा vxlan_rdst *rd;

	netdev_dbg(vxlan->dev, "delete %pM\n", f->eth_addr);

	--vxlan->addrcnt;
	अगर (करो_notअगरy) अणु
		अगर (rcu_access_poपूर्णांकer(f->nh))
			vxlan_fdb_notअगरy(vxlan, f, शून्य, RTM_DELNEIGH,
					 swdev_notअगरy, शून्य);
		अन्यथा
			list_क्रम_each_entry(rd, &f->remotes, list)
				vxlan_fdb_notअगरy(vxlan, f, rd, RTM_DELNEIGH,
						 swdev_notअगरy, शून्य);
	पूर्ण

	hlist_del_rcu(&f->hlist);
	list_del_rcu(&f->nh_list);
	call_rcu(&f->rcu, vxlan_fdb_मुक्त);
पूर्ण

अटल व्योम vxlan_dst_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा vxlan_rdst *rd = container_of(head, काष्ठा vxlan_rdst, rcu);

	dst_cache_destroy(&rd->dst_cache);
	kमुक्त(rd);
पूर्ण

अटल पूर्णांक vxlan_fdb_update_existing(काष्ठा vxlan_dev *vxlan,
				     जोड़ vxlan_addr *ip,
				     __u16 state, __u16 flags,
				     __be16 port, __be32 vni,
				     __u32 अगरindex, __u16 ndm_flags,
				     काष्ठा vxlan_fdb *f, u32 nhid,
				     bool swdev_notअगरy,
				     काष्ठा netlink_ext_ack *extack)
अणु
	__u16 fdb_flags = (ndm_flags & ~NTF_USE);
	काष्ठा vxlan_rdst *rd = शून्य;
	काष्ठा vxlan_rdst oldrd;
	पूर्णांक notअगरy = 0;
	पूर्णांक rc = 0;
	पूर्णांक err;

	अगर (nhid && !rcu_access_poपूर्णांकer(f->nh)) अणु
		NL_SET_ERR_MSG(extack,
			       "Cannot replace an existing non nexthop fdb with a nexthop");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (nhid && (flags & NLM_F_APPEND)) अणु
		NL_SET_ERR_MSG(extack,
			       "Cannot append to a nexthop fdb");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Do not allow an बाह्यally learned entry to take over an entry added
	 * by the user.
	 */
	अगर (!(fdb_flags & NTF_EXT_LEARNED) ||
	    !(f->flags & NTF_VXLAN_ADDED_BY_USER)) अणु
		अगर (f->state != state) अणु
			f->state = state;
			f->updated = jअगरfies;
			notअगरy = 1;
		पूर्ण
		अगर (f->flags != fdb_flags) अणु
			f->flags = fdb_flags;
			f->updated = jअगरfies;
			notअगरy = 1;
		पूर्ण
	पूर्ण

	अगर ((flags & NLM_F_REPLACE)) अणु
		/* Only change unicasts */
		अगर (!(is_multicast_ether_addr(f->eth_addr) ||
		      is_zero_ether_addr(f->eth_addr))) अणु
			अगर (nhid) अणु
				rc = vxlan_fdb_nh_update(vxlan, f, nhid, extack);
				अगर (rc < 0)
					वापस rc;
			पूर्ण अन्यथा अणु
				rc = vxlan_fdb_replace(f, ip, port, vni,
						       अगरindex, &oldrd);
			पूर्ण
			notअगरy |= rc;
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG(extack, "Cannot replace non-unicast fdb entries");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	अगर ((flags & NLM_F_APPEND) &&
	    (is_multicast_ether_addr(f->eth_addr) ||
	     is_zero_ether_addr(f->eth_addr))) अणु
		rc = vxlan_fdb_append(f, ip, port, vni, अगरindex, &rd);

		अगर (rc < 0)
			वापस rc;
		notअगरy |= rc;
	पूर्ण

	अगर (ndm_flags & NTF_USE)
		f->used = jअगरfies;

	अगर (notअगरy) अणु
		अगर (rd == शून्य)
			rd = first_remote_rtnl(f);

		err = vxlan_fdb_notअगरy(vxlan, f, rd, RTM_NEWNEIGH,
				       swdev_notअगरy, extack);
		अगर (err)
			जाओ err_notअगरy;
	पूर्ण

	वापस 0;

err_notअगरy:
	अगर (nhid)
		वापस err;
	अगर ((flags & NLM_F_REPLACE) && rc)
		*rd = oldrd;
	अन्यथा अगर ((flags & NLM_F_APPEND) && rc) अणु
		list_del_rcu(&rd->list);
		call_rcu(&rd->rcu, vxlan_dst_मुक्त);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक vxlan_fdb_update_create(काष्ठा vxlan_dev *vxlan,
				   स्थिर u8 *mac, जोड़ vxlan_addr *ip,
				   __u16 state, __u16 flags,
				   __be16 port, __be32 src_vni, __be32 vni,
				   __u32 अगरindex, __u16 ndm_flags, u32 nhid,
				   bool swdev_notअगरy,
				   काष्ठा netlink_ext_ack *extack)
अणु
	__u16 fdb_flags = (ndm_flags & ~NTF_USE);
	काष्ठा vxlan_fdb *f;
	पूर्णांक rc;

	/* Disallow replace to add a multicast entry */
	अगर ((flags & NLM_F_REPLACE) &&
	    (is_multicast_ether_addr(mac) || is_zero_ether_addr(mac)))
		वापस -EOPNOTSUPP;

	netdev_dbg(vxlan->dev, "add %pM -> %pIS\n", mac, ip);
	rc = vxlan_fdb_create(vxlan, mac, ip, state, port, src_vni,
			      vni, अगरindex, fdb_flags, nhid, &f, extack);
	अगर (rc < 0)
		वापस rc;

	vxlan_fdb_insert(vxlan, mac, src_vni, f);
	rc = vxlan_fdb_notअगरy(vxlan, f, first_remote_rtnl(f), RTM_NEWNEIGH,
			      swdev_notअगरy, extack);
	अगर (rc)
		जाओ err_notअगरy;

	वापस 0;

err_notअगरy:
	vxlan_fdb_destroy(vxlan, f, false, false);
	वापस rc;
पूर्ण

/* Add new entry to क्रमwarding table -- assumes lock held */
अटल पूर्णांक vxlan_fdb_update(काष्ठा vxlan_dev *vxlan,
			    स्थिर u8 *mac, जोड़ vxlan_addr *ip,
			    __u16 state, __u16 flags,
			    __be16 port, __be32 src_vni, __be32 vni,
			    __u32 अगरindex, __u16 ndm_flags, u32 nhid,
			    bool swdev_notअगरy,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_fdb *f;

	f = __vxlan_find_mac(vxlan, mac, src_vni);
	अगर (f) अणु
		अगर (flags & NLM_F_EXCL) अणु
			netdev_dbg(vxlan->dev,
				   "lost race to create %pM\n", mac);
			वापस -EEXIST;
		पूर्ण

		वापस vxlan_fdb_update_existing(vxlan, ip, state, flags, port,
						 vni, अगरindex, ndm_flags, f,
						 nhid, swdev_notअगरy, extack);
	पूर्ण अन्यथा अणु
		अगर (!(flags & NLM_F_CREATE))
			वापस -ENOENT;

		वापस vxlan_fdb_update_create(vxlan, mac, ip, state, flags,
					       port, src_vni, vni, अगरindex,
					       ndm_flags, nhid, swdev_notअगरy,
					       extack);
	पूर्ण
पूर्ण

अटल व्योम vxlan_fdb_dst_destroy(काष्ठा vxlan_dev *vxlan, काष्ठा vxlan_fdb *f,
				  काष्ठा vxlan_rdst *rd, bool swdev_notअगरy)
अणु
	list_del_rcu(&rd->list);
	vxlan_fdb_notअगरy(vxlan, f, rd, RTM_DELNEIGH, swdev_notअगरy, शून्य);
	call_rcu(&rd->rcu, vxlan_dst_मुक्त);
पूर्ण

अटल पूर्णांक vxlan_fdb_parse(काष्ठा nlattr *tb[], काष्ठा vxlan_dev *vxlan,
			   जोड़ vxlan_addr *ip, __be16 *port, __be32 *src_vni,
			   __be32 *vni, u32 *अगरindex, u32 *nhid)
अणु
	काष्ठा net *net = dev_net(vxlan->dev);
	पूर्णांक err;

	अगर (tb[NDA_NH_ID] && (tb[NDA_DST] || tb[NDA_VNI] || tb[NDA_IFINDEX] ||
	    tb[NDA_PORT]))
		वापस -EINVAL;

	अगर (tb[NDA_DST]) अणु
		err = vxlan_nla_get_addr(ip, tb[NDA_DST]);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		जोड़ vxlan_addr *remote = &vxlan->शेष_dst.remote_ip;

		अगर (remote->sa.sa_family == AF_INET) अणु
			ip->sin.sin_addr.s_addr = htonl(INADDR_ANY);
			ip->sa.sa_family = AF_INET;
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्ण अन्यथा अणु
			ip->sin6.sin6_addr = in6addr_any;
			ip->sa.sa_family = AF_INET6;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	अगर (tb[NDA_PORT]) अणु
		अगर (nla_len(tb[NDA_PORT]) != माप(__be16))
			वापस -EINVAL;
		*port = nla_get_be16(tb[NDA_PORT]);
	पूर्ण अन्यथा अणु
		*port = vxlan->cfg.dst_port;
	पूर्ण

	अगर (tb[NDA_VNI]) अणु
		अगर (nla_len(tb[NDA_VNI]) != माप(u32))
			वापस -EINVAL;
		*vni = cpu_to_be32(nla_get_u32(tb[NDA_VNI]));
	पूर्ण अन्यथा अणु
		*vni = vxlan->शेष_dst.remote_vni;
	पूर्ण

	अगर (tb[NDA_SRC_VNI]) अणु
		अगर (nla_len(tb[NDA_SRC_VNI]) != माप(u32))
			वापस -EINVAL;
		*src_vni = cpu_to_be32(nla_get_u32(tb[NDA_SRC_VNI]));
	पूर्ण अन्यथा अणु
		*src_vni = vxlan->शेष_dst.remote_vni;
	पूर्ण

	अगर (tb[NDA_IFINDEX]) अणु
		काष्ठा net_device *tdev;

		अगर (nla_len(tb[NDA_IFINDEX]) != माप(u32))
			वापस -EINVAL;
		*अगरindex = nla_get_u32(tb[NDA_IFINDEX]);
		tdev = __dev_get_by_index(net, *अगरindex);
		अगर (!tdev)
			वापस -EADDRNOTAVAIL;
	पूर्ण अन्यथा अणु
		*अगरindex = 0;
	पूर्ण

	अगर (tb[NDA_NH_ID])
		*nhid = nla_get_u32(tb[NDA_NH_ID]);
	अन्यथा
		*nhid = 0;

	वापस 0;
पूर्ण

/* Add अटल entry (via netlink) */
अटल पूर्णांक vxlan_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			 काष्ठा net_device *dev,
			 स्थिर अचिन्हित अक्षर *addr, u16 vid, u16 flags,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	/* काष्ठा net *net = dev_net(vxlan->dev); */
	जोड़ vxlan_addr ip;
	__be16 port;
	__be32 src_vni, vni;
	u32 अगरindex, nhid;
	u32 hash_index;
	पूर्णांक err;

	अगर (!(ndm->ndm_state & (NUD_PERMANENT|NUD_REACHABLE))) अणु
		pr_info("RTM_NEWNEIGH with invalid state %#x\n",
			ndm->ndm_state);
		वापस -EINVAL;
	पूर्ण

	अगर (!tb || (!tb[NDA_DST] && !tb[NDA_NH_ID]))
		वापस -EINVAL;

	err = vxlan_fdb_parse(tb, vxlan, &ip, &port, &src_vni, &vni, &अगरindex,
			      &nhid);
	अगर (err)
		वापस err;

	अगर (vxlan->शेष_dst.remote_ip.sa.sa_family != ip.sa.sa_family)
		वापस -EAFNOSUPPORT;

	hash_index = fdb_head_index(vxlan, addr, src_vni);
	spin_lock_bh(&vxlan->hash_lock[hash_index]);
	err = vxlan_fdb_update(vxlan, addr, &ip, ndm->ndm_state, flags,
			       port, src_vni, vni, अगरindex,
			       ndm->ndm_flags | NTF_VXLAN_ADDED_BY_USER,
			       nhid, true, extack);
	spin_unlock_bh(&vxlan->hash_lock[hash_index]);

	वापस err;
पूर्ण

अटल पूर्णांक __vxlan_fdb_delete(काष्ठा vxlan_dev *vxlan,
			      स्थिर अचिन्हित अक्षर *addr, जोड़ vxlan_addr ip,
			      __be16 port, __be32 src_vni, __be32 vni,
			      u32 अगरindex, bool swdev_notअगरy)
अणु
	काष्ठा vxlan_rdst *rd = शून्य;
	काष्ठा vxlan_fdb *f;
	पूर्णांक err = -ENOENT;

	f = vxlan_find_mac(vxlan, addr, src_vni);
	अगर (!f)
		वापस err;

	अगर (!vxlan_addr_any(&ip)) अणु
		rd = vxlan_fdb_find_rdst(f, &ip, port, vni, अगरindex);
		अगर (!rd)
			जाओ out;
	पूर्ण

	/* हटाओ a destination अगर it's not the only one on the list,
	 * otherwise destroy the fdb entry
	 */
	अगर (rd && !list_is_singular(&f->remotes)) अणु
		vxlan_fdb_dst_destroy(vxlan, f, rd, swdev_notअगरy);
		जाओ out;
	पूर्ण

	vxlan_fdb_destroy(vxlan, f, true, swdev_notअगरy);

out:
	वापस 0;
पूर्ण

/* Delete entry (via netlink) */
अटल पूर्णांक vxlan_fdb_delete(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			    काष्ठा net_device *dev,
			    स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	जोड़ vxlan_addr ip;
	__be32 src_vni, vni;
	u32 अगरindex, nhid;
	u32 hash_index;
	__be16 port;
	पूर्णांक err;

	err = vxlan_fdb_parse(tb, vxlan, &ip, &port, &src_vni, &vni, &अगरindex,
			      &nhid);
	अगर (err)
		वापस err;

	hash_index = fdb_head_index(vxlan, addr, src_vni);
	spin_lock_bh(&vxlan->hash_lock[hash_index]);
	err = __vxlan_fdb_delete(vxlan, addr, ip, port, src_vni, vni, अगरindex,
				 true);
	spin_unlock_bh(&vxlan->hash_lock[hash_index]);

	वापस err;
पूर्ण

/* Dump क्रमwarding table */
अटल पूर्णांक vxlan_fdb_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			  काष्ठा net_device *dev,
			  काष्ठा net_device *filter_dev, पूर्णांक *idx)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	अचिन्हित पूर्णांक h;
	पूर्णांक err = 0;

	क्रम (h = 0; h < FDB_HASH_SIZE; ++h) अणु
		काष्ठा vxlan_fdb *f;

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(f, &vxlan->fdb_head[h], hlist) अणु
			काष्ठा vxlan_rdst *rd;

			अगर (rcu_access_poपूर्णांकer(f->nh)) अणु
				अगर (*idx < cb->args[2])
					जाओ skip_nh;
				err = vxlan_fdb_info(skb, vxlan, f,
						     NETLINK_CB(cb->skb).portid,
						     cb->nlh->nlmsg_seq,
						     RTM_NEWNEIGH,
						     NLM_F_MULTI, शून्य);
				अगर (err < 0) अणु
					rcu_पढ़ो_unlock();
					जाओ out;
				पूर्ण
skip_nh:
				*idx += 1;
				जारी;
			पूर्ण

			list_क्रम_each_entry_rcu(rd, &f->remotes, list) अणु
				अगर (*idx < cb->args[2])
					जाओ skip;

				err = vxlan_fdb_info(skb, vxlan, f,
						     NETLINK_CB(cb->skb).portid,
						     cb->nlh->nlmsg_seq,
						     RTM_NEWNEIGH,
						     NLM_F_MULTI, rd);
				अगर (err < 0) अणु
					rcu_पढ़ो_unlock();
					जाओ out;
				पूर्ण
skip:
				*idx += 1;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक vxlan_fdb_get(काष्ठा sk_buff *skb,
			 काष्ठा nlattr *tb[],
			 काष्ठा net_device *dev,
			 स्थिर अचिन्हित अक्षर *addr,
			 u16 vid, u32 portid, u32 seq,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_fdb *f;
	__be32 vni;
	पूर्णांक err;

	अगर (tb[NDA_VNI])
		vni = cpu_to_be32(nla_get_u32(tb[NDA_VNI]));
	अन्यथा
		vni = vxlan->शेष_dst.remote_vni;

	rcu_पढ़ो_lock();

	f = __vxlan_find_mac(vxlan, addr, vni);
	अगर (!f) अणु
		NL_SET_ERR_MSG(extack, "Fdb entry not found");
		err = -ENOENT;
		जाओ errout;
	पूर्ण

	err = vxlan_fdb_info(skb, vxlan, f, portid, seq,
			     RTM_NEWNEIGH, 0, first_remote_rcu(f));
errout:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

/* Watch incoming packets to learn mapping between Ethernet address
 * and Tunnel endpoपूर्णांक.
 * Return true अगर packet is bogus and should be dropped.
 */
अटल bool vxlan_snoop(काष्ठा net_device *dev,
			जोड़ vxlan_addr *src_ip, स्थिर u8 *src_mac,
			u32 src_अगरindex, __be32 vni)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_fdb *f;
	u32 अगरindex = 0;

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (src_ip->sa.sa_family == AF_INET6 &&
	    (ipv6_addr_type(&src_ip->sin6.sin6_addr) & IPV6_ADDR_LINKLOCAL))
		अगरindex = src_अगरindex;
#पूर्ण_अगर

	f = vxlan_find_mac(vxlan, src_mac, vni);
	अगर (likely(f)) अणु
		काष्ठा vxlan_rdst *rdst = first_remote_rcu(f);

		अगर (likely(vxlan_addr_equal(&rdst->remote_ip, src_ip) &&
			   rdst->remote_अगरindex == अगरindex))
			वापस false;

		/* Don't migrate अटल entries, drop packets */
		अगर (f->state & (NUD_PERMANENT | NUD_NOARP))
			वापस true;

		/* Don't override an fdb with nexthop with a learnt entry */
		अगर (rcu_access_poपूर्णांकer(f->nh))
			वापस true;

		अगर (net_ratelimit())
			netdev_info(dev,
				    "%pM migrated from %pIS to %pIS\n",
				    src_mac, &rdst->remote_ip.sa, &src_ip->sa);

		rdst->remote_ip = *src_ip;
		f->updated = jअगरfies;
		vxlan_fdb_notअगरy(vxlan, f, rdst, RTM_NEWNEIGH, true, शून्य);
	पूर्ण अन्यथा अणु
		u32 hash_index = fdb_head_index(vxlan, src_mac, vni);

		/* learned new entry */
		spin_lock(&vxlan->hash_lock[hash_index]);

		/* बंद off race between vxlan_flush and incoming packets */
		अगर (netअगर_running(dev))
			vxlan_fdb_update(vxlan, src_mac, src_ip,
					 NUD_REACHABLE,
					 NLM_F_EXCL|NLM_F_CREATE,
					 vxlan->cfg.dst_port,
					 vni,
					 vxlan->शेष_dst.remote_vni,
					 अगरindex, NTF_SELF, 0, true, शून्य);
		spin_unlock(&vxlan->hash_lock[hash_index]);
	पूर्ण

	वापस false;
पूर्ण

/* See अगर multicast group is alपढ़ोy in use by other ID */
अटल bool vxlan_group_used(काष्ठा vxlan_net *vn, काष्ठा vxlan_dev *dev)
अणु
	काष्ठा vxlan_dev *vxlan;
	काष्ठा vxlan_sock *sock4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा vxlan_sock *sock6;
#पूर्ण_अगर
	अचिन्हित लघु family = dev->शेष_dst.remote_ip.sa.sa_family;

	sock4 = rtnl_dereference(dev->vn4_sock);

	/* The vxlan_sock is only used by dev, leaving group has
	 * no effect on other vxlan devices.
	 */
	अगर (family == AF_INET && sock4 && refcount_पढ़ो(&sock4->refcnt) == 1)
		वापस false;
#अगर IS_ENABLED(CONFIG_IPV6)
	sock6 = rtnl_dereference(dev->vn6_sock);
	अगर (family == AF_INET6 && sock6 && refcount_पढ़ो(&sock6->refcnt) == 1)
		वापस false;
#पूर्ण_अगर

	list_क्रम_each_entry(vxlan, &vn->vxlan_list, next) अणु
		अगर (!netअगर_running(vxlan->dev) || vxlan == dev)
			जारी;

		अगर (family == AF_INET &&
		    rtnl_dereference(vxlan->vn4_sock) != sock4)
			जारी;
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (family == AF_INET6 &&
		    rtnl_dereference(vxlan->vn6_sock) != sock6)
			जारी;
#पूर्ण_अगर

		अगर (!vxlan_addr_equal(&vxlan->शेष_dst.remote_ip,
				      &dev->शेष_dst.remote_ip))
			जारी;

		अगर (vxlan->शेष_dst.remote_अगरindex !=
		    dev->शेष_dst.remote_अगरindex)
			जारी;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool __vxlan_sock_release_prep(काष्ठा vxlan_sock *vs)
अणु
	काष्ठा vxlan_net *vn;

	अगर (!vs)
		वापस false;
	अगर (!refcount_dec_and_test(&vs->refcnt))
		वापस false;

	vn = net_generic(sock_net(vs->sock->sk), vxlan_net_id);
	spin_lock(&vn->sock_lock);
	hlist_del_rcu(&vs->hlist);
	udp_tunnel_notअगरy_del_rx_port(vs->sock,
				      (vs->flags & VXLAN_F_GPE) ?
				      UDP_TUNNEL_TYPE_VXLAN_GPE :
				      UDP_TUNNEL_TYPE_VXLAN);
	spin_unlock(&vn->sock_lock);

	वापस true;
पूर्ण

अटल व्योम vxlan_sock_release(काष्ठा vxlan_dev *vxlan)
अणु
	काष्ठा vxlan_sock *sock4 = rtnl_dereference(vxlan->vn4_sock);
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा vxlan_sock *sock6 = rtnl_dereference(vxlan->vn6_sock);

	RCU_INIT_POINTER(vxlan->vn6_sock, शून्य);
#पूर्ण_अगर

	RCU_INIT_POINTER(vxlan->vn4_sock, शून्य);
	synchronize_net();

	vxlan_vs_del_dev(vxlan);

	अगर (__vxlan_sock_release_prep(sock4)) अणु
		udp_tunnel_sock_release(sock4->sock);
		kमुक्त(sock4);
	पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (__vxlan_sock_release_prep(sock6)) अणु
		udp_tunnel_sock_release(sock6->sock);
		kमुक्त(sock6);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Update multicast group membership when first VNI on
 * multicast address is brought up
 */
अटल पूर्णांक vxlan_igmp_join(काष्ठा vxlan_dev *vxlan)
अणु
	काष्ठा sock *sk;
	जोड़ vxlan_addr *ip = &vxlan->शेष_dst.remote_ip;
	पूर्णांक अगरindex = vxlan->शेष_dst.remote_अगरindex;
	पूर्णांक ret = -EINVAL;

	अगर (ip->sa.sa_family == AF_INET) अणु
		काष्ठा vxlan_sock *sock4 = rtnl_dereference(vxlan->vn4_sock);
		काष्ठा ip_mreqn mreq = अणु
			.imr_multiaddr.s_addr	= ip->sin.sin_addr.s_addr,
			.imr_अगरindex		= अगरindex,
		पूर्ण;

		sk = sock4->sock->sk;
		lock_sock(sk);
		ret = ip_mc_join_group(sk, &mreq);
		release_sock(sk);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		काष्ठा vxlan_sock *sock6 = rtnl_dereference(vxlan->vn6_sock);

		sk = sock6->sock->sk;
		lock_sock(sk);
		ret = ipv6_stub->ipv6_sock_mc_join(sk, अगरindex,
						   &ip->sin6.sin6_addr);
		release_sock(sk);
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण

/* Inverse of vxlan_igmp_join when last VNI is brought करोwn */
अटल पूर्णांक vxlan_igmp_leave(काष्ठा vxlan_dev *vxlan)
अणु
	काष्ठा sock *sk;
	जोड़ vxlan_addr *ip = &vxlan->शेष_dst.remote_ip;
	पूर्णांक अगरindex = vxlan->शेष_dst.remote_अगरindex;
	पूर्णांक ret = -EINVAL;

	अगर (ip->sa.sa_family == AF_INET) अणु
		काष्ठा vxlan_sock *sock4 = rtnl_dereference(vxlan->vn4_sock);
		काष्ठा ip_mreqn mreq = अणु
			.imr_multiaddr.s_addr	= ip->sin.sin_addr.s_addr,
			.imr_अगरindex		= अगरindex,
		पूर्ण;

		sk = sock4->sock->sk;
		lock_sock(sk);
		ret = ip_mc_leave_group(sk, &mreq);
		release_sock(sk);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		काष्ठा vxlan_sock *sock6 = rtnl_dereference(vxlan->vn6_sock);

		sk = sock6->sock->sk;
		lock_sock(sk);
		ret = ipv6_stub->ipv6_sock_mc_drop(sk, अगरindex,
						   &ip->sin6.sin6_addr);
		release_sock(sk);
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण

अटल bool vxlan_remcsum(काष्ठा vxlanhdr *unparsed,
			  काष्ठा sk_buff *skb, u32 vxflags)
अणु
	माप_प्रकार start, offset;

	अगर (!(unparsed->vx_flags & VXLAN_HF_RCO) || skb->remcsum_offload)
		जाओ out;

	start = vxlan_rco_start(unparsed->vx_vni);
	offset = start + vxlan_rco_offset(unparsed->vx_vni);

	अगर (!pskb_may_pull(skb, offset + माप(u16)))
		वापस false;

	skb_remcsum_process(skb, (व्योम *)(vxlan_hdr(skb) + 1), start, offset,
			    !!(vxflags & VXLAN_F_REMCSUM_NOPARTIAL));
out:
	unparsed->vx_flags &= ~VXLAN_HF_RCO;
	unparsed->vx_vni &= VXLAN_VNI_MASK;
	वापस true;
पूर्ण

अटल व्योम vxlan_parse_gbp_hdr(काष्ठा vxlanhdr *unparsed,
				काष्ठा sk_buff *skb, u32 vxflags,
				काष्ठा vxlan_metadata *md)
अणु
	काष्ठा vxlanhdr_gbp *gbp = (काष्ठा vxlanhdr_gbp *)unparsed;
	काष्ठा metadata_dst *tun_dst;

	अगर (!(unparsed->vx_flags & VXLAN_HF_GBP))
		जाओ out;

	md->gbp = ntohs(gbp->policy_id);

	tun_dst = (काष्ठा metadata_dst *)skb_dst(skb);
	अगर (tun_dst) अणु
		tun_dst->u.tun_info.key.tun_flags |= TUNNEL_VXLAN_OPT;
		tun_dst->u.tun_info.options_len = माप(*md);
	पूर्ण
	अगर (gbp->करोnt_learn)
		md->gbp |= VXLAN_GBP_DONT_LEARN;

	अगर (gbp->policy_applied)
		md->gbp |= VXLAN_GBP_POLICY_APPLIED;

	/* In flow-based mode, GBP is carried in dst_metadata */
	अगर (!(vxflags & VXLAN_F_COLLECT_METADATA))
		skb->mark = md->gbp;
out:
	unparsed->vx_flags &= ~VXLAN_GBP_USED_BITS;
पूर्ण

अटल bool vxlan_parse_gpe_hdr(काष्ठा vxlanhdr *unparsed,
				__be16 *protocol,
				काष्ठा sk_buff *skb, u32 vxflags)
अणु
	काष्ठा vxlanhdr_gpe *gpe = (काष्ठा vxlanhdr_gpe *)unparsed;

	/* Need to have Next Protocol set क्रम पूर्णांकerfaces in GPE mode. */
	अगर (!gpe->np_applied)
		वापस false;
	/* "The initial version is 0. If a receiver करोes not support the
	 * version indicated it MUST drop the packet.
	 */
	अगर (gpe->version != 0)
		वापस false;
	/* "When the O bit is set to 1, the packet is an OAM packet and OAM
	 * processing MUST occur." However, we करोn't implement OAM
	 * processing, thus drop the packet.
	 */
	अगर (gpe->oam_flag)
		वापस false;

	*protocol = tun_p_to_eth_p(gpe->next_protocol);
	अगर (!*protocol)
		वापस false;

	unparsed->vx_flags &= ~VXLAN_GPE_USED_BITS;
	वापस true;
पूर्ण

अटल bool vxlan_set_mac(काष्ठा vxlan_dev *vxlan,
			  काष्ठा vxlan_sock *vs,
			  काष्ठा sk_buff *skb, __be32 vni)
अणु
	जोड़ vxlan_addr saddr;
	u32 अगरindex = skb->dev->अगरindex;

	skb_reset_mac_header(skb);
	skb->protocol = eth_type_trans(skb, vxlan->dev);
	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);

	/* Ignore packet loops (and multicast echo) */
	अगर (ether_addr_equal(eth_hdr(skb)->h_source, vxlan->dev->dev_addr))
		वापस false;

	/* Get address from the outer IP header */
	अगर (vxlan_get_sk_family(vs) == AF_INET) अणु
		saddr.sin.sin_addr.s_addr = ip_hdr(skb)->saddr;
		saddr.sa.sa_family = AF_INET;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		saddr.sin6.sin6_addr = ipv6_hdr(skb)->saddr;
		saddr.sa.sa_family = AF_INET6;
#पूर्ण_अगर
	पूर्ण

	अगर ((vxlan->cfg.flags & VXLAN_F_LEARN) &&
	    vxlan_snoop(skb->dev, &saddr, eth_hdr(skb)->h_source, अगरindex, vni))
		वापस false;

	वापस true;
पूर्ण

अटल bool vxlan_ecn_decapsulate(काष्ठा vxlan_sock *vs, व्योम *oiph,
				  काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 0;

	अगर (vxlan_get_sk_family(vs) == AF_INET)
		err = IP_ECN_decapsulate(oiph, skb);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		err = IP6_ECN_decapsulate(oiph, skb);
#पूर्ण_अगर

	अगर (unlikely(err) && log_ecn_error) अणु
		अगर (vxlan_get_sk_family(vs) == AF_INET)
			net_info_ratelimited("non-ECT from %pI4 with TOS=%#x\n",
					     &((काष्ठा iphdr *)oiph)->saddr,
					     ((काष्ठा iphdr *)oiph)->tos);
		अन्यथा
			net_info_ratelimited("non-ECT from %pI6\n",
					     &((काष्ठा ipv6hdr *)oiph)->saddr);
	पूर्ण
	वापस err <= 1;
पूर्ण

/* Callback from net/ipv4/udp.c to receive packets */
अटल पूर्णांक vxlan_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा vxlan_dev *vxlan;
	काष्ठा vxlan_sock *vs;
	काष्ठा vxlanhdr unparsed;
	काष्ठा vxlan_metadata _md;
	काष्ठा vxlan_metadata *md = &_md;
	__be16 protocol = htons(ETH_P_TEB);
	bool raw_proto = false;
	व्योम *oiph;
	__be32 vni = 0;

	/* Need UDP and VXLAN header to be present */
	अगर (!pskb_may_pull(skb, VXLAN_HLEN))
		जाओ drop;

	unparsed = *vxlan_hdr(skb);
	/* VNI flag always required to be set */
	अगर (!(unparsed.vx_flags & VXLAN_HF_VNI)) अणु
		netdev_dbg(skb->dev, "invalid vxlan flags=%#x vni=%#x\n",
			   ntohl(vxlan_hdr(skb)->vx_flags),
			   ntohl(vxlan_hdr(skb)->vx_vni));
		/* Return non vxlan pkt */
		जाओ drop;
	पूर्ण
	unparsed.vx_flags &= ~VXLAN_HF_VNI;
	unparsed.vx_vni &= ~VXLAN_VNI_MASK;

	vs = rcu_dereference_sk_user_data(sk);
	अगर (!vs)
		जाओ drop;

	vni = vxlan_vni(vxlan_hdr(skb)->vx_vni);

	vxlan = vxlan_vs_find_vni(vs, skb->dev->अगरindex, vni);
	अगर (!vxlan)
		जाओ drop;

	/* For backwards compatibility, only allow reserved fields to be
	 * used by VXLAN extensions अगर explicitly requested.
	 */
	अगर (vs->flags & VXLAN_F_GPE) अणु
		अगर (!vxlan_parse_gpe_hdr(&unparsed, &protocol, skb, vs->flags))
			जाओ drop;
		raw_proto = true;
	पूर्ण

	अगर (__iptunnel_pull_header(skb, VXLAN_HLEN, protocol, raw_proto,
				   !net_eq(vxlan->net, dev_net(vxlan->dev))))
		जाओ drop;

	अगर (vs->flags & VXLAN_F_REMCSUM_RX)
		अगर (unlikely(!vxlan_remcsum(&unparsed, skb, vs->flags)))
			जाओ drop;

	अगर (vxlan_collect_metadata(vs)) अणु
		काष्ठा metadata_dst *tun_dst;

		tun_dst = udp_tun_rx_dst(skb, vxlan_get_sk_family(vs), TUNNEL_KEY,
					 key32_to_tunnel_id(vni), माप(*md));

		अगर (!tun_dst)
			जाओ drop;

		md = ip_tunnel_info_opts(&tun_dst->u.tun_info);

		skb_dst_set(skb, (काष्ठा dst_entry *)tun_dst);
	पूर्ण अन्यथा अणु
		स_रखो(md, 0, माप(*md));
	पूर्ण

	अगर (vs->flags & VXLAN_F_GBP)
		vxlan_parse_gbp_hdr(&unparsed, skb, vs->flags, md);
	/* Note that GBP and GPE can never be active together. This is
	 * ensured in vxlan_dev_configure.
	 */

	अगर (unparsed.vx_flags || unparsed.vx_vni) अणु
		/* If there are any unprocessed flags reमुख्यing treat
		 * this as a malक्रमmed packet. This behavior भागerges from
		 * VXLAN RFC (RFC7348) which stipulates that bits in reserved
		 * in reserved fields are to be ignored. The approach here
		 * मुख्यtains compatibility with previous stack code, and also
		 * is more robust and provides a little more security in
		 * adding extensions to VXLAN.
		 */
		जाओ drop;
	पूर्ण

	अगर (!raw_proto) अणु
		अगर (!vxlan_set_mac(vxlan, vs, skb, vni))
			जाओ drop;
	पूर्ण अन्यथा अणु
		skb_reset_mac_header(skb);
		skb->dev = vxlan->dev;
		skb->pkt_type = PACKET_HOST;
	पूर्ण

	oiph = skb_network_header(skb);
	skb_reset_network_header(skb);

	अगर (!vxlan_ecn_decapsulate(vs, oiph, skb)) अणु
		++vxlan->dev->stats.rx_frame_errors;
		++vxlan->dev->stats.rx_errors;
		जाओ drop;
	पूर्ण

	rcu_पढ़ो_lock();

	अगर (unlikely(!(vxlan->dev->flags & IFF_UP))) अणु
		rcu_पढ़ो_unlock();
		atomic_दीर्घ_inc(&vxlan->dev->rx_dropped);
		जाओ drop;
	पूर्ण

	dev_sw_netstats_rx_add(vxlan->dev, skb->len);
	gro_cells_receive(&vxlan->gro_cells, skb);

	rcu_पढ़ो_unlock();

	वापस 0;

drop:
	/* Consume bad packet */
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/* Callback from net/ipvअणु4,6पूर्ण/udp.c to check that we have a VNI क्रम errors */
अटल पूर्णांक vxlan_err_lookup(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा vxlan_dev *vxlan;
	काष्ठा vxlan_sock *vs;
	काष्ठा vxlanhdr *hdr;
	__be32 vni;

	अगर (!pskb_may_pull(skb, skb_transport_offset(skb) + VXLAN_HLEN))
		वापस -EINVAL;

	hdr = vxlan_hdr(skb);

	अगर (!(hdr->vx_flags & VXLAN_HF_VNI))
		वापस -EINVAL;

	vs = rcu_dereference_sk_user_data(sk);
	अगर (!vs)
		वापस -ENOENT;

	vni = vxlan_vni(hdr->vx_vni);
	vxlan = vxlan_vs_find_vni(vs, skb->dev->अगरindex, vni);
	अगर (!vxlan)
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल पूर्णांक arp_reduce(काष्ठा net_device *dev, काष्ठा sk_buff *skb, __be32 vni)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा arphdr *parp;
	u8 *arpptr, *sha;
	__be32 sip, tip;
	काष्ठा neighbour *n;

	अगर (dev->flags & IFF_NOARP)
		जाओ out;

	अगर (!pskb_may_pull(skb, arp_hdr_len(dev))) अणु
		dev->stats.tx_dropped++;
		जाओ out;
	पूर्ण
	parp = arp_hdr(skb);

	अगर ((parp->ar_hrd != htons(ARPHRD_ETHER) &&
	     parp->ar_hrd != htons(ARPHRD_IEEE802)) ||
	    parp->ar_pro != htons(ETH_P_IP) ||
	    parp->ar_op != htons(ARPOP_REQUEST) ||
	    parp->ar_hln != dev->addr_len ||
	    parp->ar_pln != 4)
		जाओ out;
	arpptr = (u8 *)parp + माप(काष्ठा arphdr);
	sha = arpptr;
	arpptr += dev->addr_len;	/* sha */
	स_नकल(&sip, arpptr, माप(sip));
	arpptr += माप(sip);
	arpptr += dev->addr_len;	/* tha */
	स_नकल(&tip, arpptr, माप(tip));

	अगर (ipv4_is_loopback(tip) ||
	    ipv4_is_multicast(tip))
		जाओ out;

	n = neigh_lookup(&arp_tbl, &tip, dev);

	अगर (n) अणु
		काष्ठा vxlan_fdb *f;
		काष्ठा sk_buff	*reply;

		अगर (!(n->nud_state & NUD_CONNECTED)) अणु
			neigh_release(n);
			जाओ out;
		पूर्ण

		f = vxlan_find_mac(vxlan, n->ha, vni);
		अगर (f && vxlan_addr_any(&(first_remote_rcu(f)->remote_ip))) अणु
			/* bridge-local neighbor */
			neigh_release(n);
			जाओ out;
		पूर्ण

		reply = arp_create(ARPOP_REPLY, ETH_P_ARP, sip, dev, tip, sha,
				n->ha, sha);

		neigh_release(n);

		अगर (reply == शून्य)
			जाओ out;

		skb_reset_mac_header(reply);
		__skb_pull(reply, skb_network_offset(reply));
		reply->ip_summed = CHECKSUM_UNNECESSARY;
		reply->pkt_type = PACKET_HOST;

		अगर (netअगर_rx_ni(reply) == NET_RX_DROP)
			dev->stats.rx_dropped++;
	पूर्ण अन्यथा अगर (vxlan->cfg.flags & VXLAN_F_L3MISS) अणु
		जोड़ vxlan_addr ipa = अणु
			.sin.sin_addr.s_addr = tip,
			.sin.sin_family = AF_INET,
		पूर्ण;

		vxlan_ip_miss(dev, &ipa);
	पूर्ण
out:
	consume_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा sk_buff *vxlan_na_create(काष्ठा sk_buff *request,
	काष्ठा neighbour *n, bool isrouter)
अणु
	काष्ठा net_device *dev = request->dev;
	काष्ठा sk_buff *reply;
	काष्ठा nd_msg *ns, *na;
	काष्ठा ipv6hdr *pip6;
	u8 *daddr;
	पूर्णांक na_olen = 8; /* opt hdr + ETH_ALEN क्रम target */
	पूर्णांक ns_olen;
	पूर्णांक i, len;

	अगर (dev == शून्य || !pskb_may_pull(request, request->len))
		वापस शून्य;

	len = LL_RESERVED_SPACE(dev) + माप(काष्ठा ipv6hdr) +
		माप(*na) + na_olen + dev->needed_tailroom;
	reply = alloc_skb(len, GFP_ATOMIC);
	अगर (reply == शून्य)
		वापस शून्य;

	reply->protocol = htons(ETH_P_IPV6);
	reply->dev = dev;
	skb_reserve(reply, LL_RESERVED_SPACE(request->dev));
	skb_push(reply, माप(काष्ठा ethhdr));
	skb_reset_mac_header(reply);

	ns = (काष्ठा nd_msg *)(ipv6_hdr(request) + 1);

	daddr = eth_hdr(request)->h_source;
	ns_olen = request->len - skb_network_offset(request) -
		माप(काष्ठा ipv6hdr) - माप(*ns);
	क्रम (i = 0; i < ns_olen-1; i += (ns->opt[i+1]<<3)) अणु
		अगर (!ns->opt[i + 1]) अणु
			kमुक्त_skb(reply);
			वापस शून्य;
		पूर्ण
		अगर (ns->opt[i] == ND_OPT_SOURCE_LL_ADDR) अणु
			daddr = ns->opt + i + माप(काष्ठा nd_opt_hdr);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Ethernet header */
	ether_addr_copy(eth_hdr(reply)->h_dest, daddr);
	ether_addr_copy(eth_hdr(reply)->h_source, n->ha);
	eth_hdr(reply)->h_proto = htons(ETH_P_IPV6);
	reply->protocol = htons(ETH_P_IPV6);

	skb_pull(reply, माप(काष्ठा ethhdr));
	skb_reset_network_header(reply);
	skb_put(reply, माप(काष्ठा ipv6hdr));

	/* IPv6 header */

	pip6 = ipv6_hdr(reply);
	स_रखो(pip6, 0, माप(काष्ठा ipv6hdr));
	pip6->version = 6;
	pip6->priority = ipv6_hdr(request)->priority;
	pip6->nexthdr = IPPROTO_ICMPV6;
	pip6->hop_limit = 255;
	pip6->daddr = ipv6_hdr(request)->saddr;
	pip6->saddr = *(काष्ठा in6_addr *)n->primary_key;

	skb_pull(reply, माप(काष्ठा ipv6hdr));
	skb_reset_transport_header(reply);

	/* Neighbor Advertisement */
	na = skb_put_zero(reply, माप(*na) + na_olen);
	na->icmph.icmp6_type = NDISC_NEIGHBOUR_ADVERTISEMENT;
	na->icmph.icmp6_router = isrouter;
	na->icmph.icmp6_override = 1;
	na->icmph.icmp6_solicited = 1;
	na->target = ns->target;
	ether_addr_copy(&na->opt[2], n->ha);
	na->opt[0] = ND_OPT_TARGET_LL_ADDR;
	na->opt[1] = na_olen >> 3;

	na->icmph.icmp6_cksum = csum_ipv6_magic(&pip6->saddr,
		&pip6->daddr, माप(*na)+na_olen, IPPROTO_ICMPV6,
		csum_partial(na, माप(*na)+na_olen, 0));

	pip6->payload_len = htons(माप(*na)+na_olen);

	skb_push(reply, माप(काष्ठा ipv6hdr));

	reply->ip_summed = CHECKSUM_UNNECESSARY;

	वापस reply;
पूर्ण

अटल पूर्णांक neigh_reduce(काष्ठा net_device *dev, काष्ठा sk_buff *skb, __be32 vni)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	स्थिर काष्ठा in6_addr *daddr;
	स्थिर काष्ठा ipv6hdr *iphdr;
	काष्ठा inet6_dev *in6_dev;
	काष्ठा neighbour *n;
	काष्ठा nd_msg *msg;

	in6_dev = __in6_dev_get(dev);
	अगर (!in6_dev)
		जाओ out;

	iphdr = ipv6_hdr(skb);
	daddr = &iphdr->daddr;
	msg = (काष्ठा nd_msg *)(iphdr + 1);

	अगर (ipv6_addr_loopback(daddr) ||
	    ipv6_addr_is_multicast(&msg->target))
		जाओ out;

	n = neigh_lookup(ipv6_stub->nd_tbl, &msg->target, dev);

	अगर (n) अणु
		काष्ठा vxlan_fdb *f;
		काष्ठा sk_buff *reply;

		अगर (!(n->nud_state & NUD_CONNECTED)) अणु
			neigh_release(n);
			जाओ out;
		पूर्ण

		f = vxlan_find_mac(vxlan, n->ha, vni);
		अगर (f && vxlan_addr_any(&(first_remote_rcu(f)->remote_ip))) अणु
			/* bridge-local neighbor */
			neigh_release(n);
			जाओ out;
		पूर्ण

		reply = vxlan_na_create(skb, n,
					!!(f ? f->flags & NTF_ROUTER : 0));

		neigh_release(n);

		अगर (reply == शून्य)
			जाओ out;

		अगर (netअगर_rx_ni(reply) == NET_RX_DROP)
			dev->stats.rx_dropped++;

	पूर्ण अन्यथा अगर (vxlan->cfg.flags & VXLAN_F_L3MISS) अणु
		जोड़ vxlan_addr ipa = अणु
			.sin6.sin6_addr = msg->target,
			.sin6.sin6_family = AF_INET6,
		पूर्ण;

		vxlan_ip_miss(dev, &ipa);
	पूर्ण

out:
	consume_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण
#पूर्ण_अगर

अटल bool route_लघुcircuit(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा neighbour *n;

	अगर (is_multicast_ether_addr(eth_hdr(skb)->h_dest))
		वापस false;

	n = शून्य;
	चयन (ntohs(eth_hdr(skb)->h_proto)) अणु
	हाल ETH_P_IP:
	अणु
		काष्ठा iphdr *pip;

		अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
			वापस false;
		pip = ip_hdr(skb);
		n = neigh_lookup(&arp_tbl, &pip->daddr, dev);
		अगर (!n && (vxlan->cfg.flags & VXLAN_F_L3MISS)) अणु
			जोड़ vxlan_addr ipa = अणु
				.sin.sin_addr.s_addr = pip->daddr,
				.sin.sin_family = AF_INET,
			पूर्ण;

			vxlan_ip_miss(dev, &ipa);
			वापस false;
		पूर्ण

		अवरोध;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल ETH_P_IPV6:
	अणु
		काष्ठा ipv6hdr *pip6;

		अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
			वापस false;
		pip6 = ipv6_hdr(skb);
		n = neigh_lookup(ipv6_stub->nd_tbl, &pip6->daddr, dev);
		अगर (!n && (vxlan->cfg.flags & VXLAN_F_L3MISS)) अणु
			जोड़ vxlan_addr ipa = अणु
				.sin6.sin6_addr = pip6->daddr,
				.sin6.sin6_family = AF_INET6,
			पूर्ण;

			vxlan_ip_miss(dev, &ipa);
			वापस false;
		पूर्ण

		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		वापस false;
	पूर्ण

	अगर (n) अणु
		bool dअगरf;

		dअगरf = !ether_addr_equal(eth_hdr(skb)->h_dest, n->ha);
		अगर (dअगरf) अणु
			स_नकल(eth_hdr(skb)->h_source, eth_hdr(skb)->h_dest,
				dev->addr_len);
			स_नकल(eth_hdr(skb)->h_dest, n->ha, dev->addr_len);
		पूर्ण
		neigh_release(n);
		वापस dअगरf;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम vxlan_build_gbp_hdr(काष्ठा vxlanhdr *vxh, u32 vxflags,
				काष्ठा vxlan_metadata *md)
अणु
	काष्ठा vxlanhdr_gbp *gbp;

	अगर (!md->gbp)
		वापस;

	gbp = (काष्ठा vxlanhdr_gbp *)vxh;
	vxh->vx_flags |= VXLAN_HF_GBP;

	अगर (md->gbp & VXLAN_GBP_DONT_LEARN)
		gbp->करोnt_learn = 1;

	अगर (md->gbp & VXLAN_GBP_POLICY_APPLIED)
		gbp->policy_applied = 1;

	gbp->policy_id = htons(md->gbp & VXLAN_GBP_ID_MASK);
पूर्ण

अटल पूर्णांक vxlan_build_gpe_hdr(काष्ठा vxlanhdr *vxh, u32 vxflags,
			       __be16 protocol)
अणु
	काष्ठा vxlanhdr_gpe *gpe = (काष्ठा vxlanhdr_gpe *)vxh;

	gpe->np_applied = 1;
	gpe->next_protocol = tun_p_from_eth_p(protocol);
	अगर (!gpe->next_protocol)
		वापस -EPFNOSUPPORT;
	वापस 0;
पूर्ण

अटल पूर्णांक vxlan_build_skb(काष्ठा sk_buff *skb, काष्ठा dst_entry *dst,
			   पूर्णांक iphdr_len, __be32 vni,
			   काष्ठा vxlan_metadata *md, u32 vxflags,
			   bool udp_sum)
अणु
	काष्ठा vxlanhdr *vxh;
	पूर्णांक min_headroom;
	पूर्णांक err;
	पूर्णांक type = udp_sum ? SKB_GSO_UDP_TUNNEL_CSUM : SKB_GSO_UDP_TUNNEL;
	__be16 inner_protocol = htons(ETH_P_TEB);

	अगर ((vxflags & VXLAN_F_REMCSUM_TX) &&
	    skb->ip_summed == CHECKSUM_PARTIAL) अणु
		पूर्णांक csum_start = skb_checksum_start_offset(skb);

		अगर (csum_start <= VXLAN_MAX_REMCSUM_START &&
		    !(csum_start & VXLAN_RCO_SHIFT_MASK) &&
		    (skb->csum_offset == दुरत्व(काष्ठा udphdr, check) ||
		     skb->csum_offset == दुरत्व(काष्ठा tcphdr, check)))
			type |= SKB_GSO_TUNNEL_REMCSUM;
	पूर्ण

	min_headroom = LL_RESERVED_SPACE(dst->dev) + dst->header_len
			+ VXLAN_HLEN + iphdr_len;

	/* Need space क्रम new headers (invalidates iph ptr) */
	err = skb_cow_head(skb, min_headroom);
	अगर (unlikely(err))
		वापस err;

	err = iptunnel_handle_offloads(skb, type);
	अगर (err)
		वापस err;

	vxh = __skb_push(skb, माप(*vxh));
	vxh->vx_flags = VXLAN_HF_VNI;
	vxh->vx_vni = vxlan_vni_field(vni);

	अगर (type & SKB_GSO_TUNNEL_REMCSUM) अणु
		अचिन्हित पूर्णांक start;

		start = skb_checksum_start_offset(skb) - माप(काष्ठा vxlanhdr);
		vxh->vx_vni |= vxlan_compute_rco(start, skb->csum_offset);
		vxh->vx_flags |= VXLAN_HF_RCO;

		अगर (!skb_is_gso(skb)) अणु
			skb->ip_summed = CHECKSUM_NONE;
			skb->encapsulation = 0;
		पूर्ण
	पूर्ण

	अगर (vxflags & VXLAN_F_GBP)
		vxlan_build_gbp_hdr(vxh, vxflags, md);
	अगर (vxflags & VXLAN_F_GPE) अणु
		err = vxlan_build_gpe_hdr(vxh, vxflags, skb->protocol);
		अगर (err < 0)
			वापस err;
		inner_protocol = skb->protocol;
	पूर्ण

	skb_set_inner_protocol(skb, inner_protocol);
	वापस 0;
पूर्ण

अटल काष्ठा rtable *vxlan_get_route(काष्ठा vxlan_dev *vxlan, काष्ठा net_device *dev,
				      काष्ठा vxlan_sock *sock4,
				      काष्ठा sk_buff *skb, पूर्णांक oअगर, u8 tos,
				      __be32 daddr, __be32 *saddr, __be16 dport, __be16 sport,
				      काष्ठा dst_cache *dst_cache,
				      स्थिर काष्ठा ip_tunnel_info *info)
अणु
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	काष्ठा rtable *rt = शून्य;
	काष्ठा flowi4 fl4;

	अगर (!sock4)
		वापस ERR_PTR(-EIO);

	अगर (tos && !info)
		use_cache = false;
	अगर (use_cache) अणु
		rt = dst_cache_get_ip4(dst_cache, saddr);
		अगर (rt)
			वापस rt;
	पूर्ण

	स_रखो(&fl4, 0, माप(fl4));
	fl4.flowi4_oअगर = oअगर;
	fl4.flowi4_tos = RT_TOS(tos);
	fl4.flowi4_mark = skb->mark;
	fl4.flowi4_proto = IPPROTO_UDP;
	fl4.daddr = daddr;
	fl4.saddr = *saddr;
	fl4.fl4_dport = dport;
	fl4.fl4_sport = sport;

	rt = ip_route_output_key(vxlan->net, &fl4);
	अगर (!IS_ERR(rt)) अणु
		अगर (rt->dst.dev == dev) अणु
			netdev_dbg(dev, "circular route to %pI4\n", &daddr);
			ip_rt_put(rt);
			वापस ERR_PTR(-ELOOP);
		पूर्ण

		*saddr = fl4.saddr;
		अगर (use_cache)
			dst_cache_set_ip4(dst_cache, &rt->dst, fl4.saddr);
	पूर्ण अन्यथा अणु
		netdev_dbg(dev, "no route to %pI4\n", &daddr);
		वापस ERR_PTR(-ENETUNREACH);
	पूर्ण
	वापस rt;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा dst_entry *vxlan6_get_route(काष्ठा vxlan_dev *vxlan,
					  काष्ठा net_device *dev,
					  काष्ठा vxlan_sock *sock6,
					  काष्ठा sk_buff *skb, पूर्णांक oअगर, u8 tos,
					  __be32 label,
					  स्थिर काष्ठा in6_addr *daddr,
					  काष्ठा in6_addr *saddr,
					  __be16 dport, __be16 sport,
					  काष्ठा dst_cache *dst_cache,
					  स्थिर काष्ठा ip_tunnel_info *info)
अणु
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	काष्ठा dst_entry *ndst;
	काष्ठा flowi6 fl6;

	अगर (!sock6)
		वापस ERR_PTR(-EIO);

	अगर (tos && !info)
		use_cache = false;
	अगर (use_cache) अणु
		ndst = dst_cache_get_ip6(dst_cache, saddr);
		अगर (ndst)
			वापस ndst;
	पूर्ण

	स_रखो(&fl6, 0, माप(fl6));
	fl6.flowi6_oअगर = oअगर;
	fl6.daddr = *daddr;
	fl6.saddr = *saddr;
	fl6.flowlabel = ip6_make_flowinfo(RT_TOS(tos), label);
	fl6.flowi6_mark = skb->mark;
	fl6.flowi6_proto = IPPROTO_UDP;
	fl6.fl6_dport = dport;
	fl6.fl6_sport = sport;

	ndst = ipv6_stub->ipv6_dst_lookup_flow(vxlan->net, sock6->sock->sk,
					       &fl6, शून्य);
	अगर (IS_ERR(ndst)) अणु
		netdev_dbg(dev, "no route to %pI6\n", daddr);
		वापस ERR_PTR(-ENETUNREACH);
	पूर्ण

	अगर (unlikely(ndst->dev == dev)) अणु
		netdev_dbg(dev, "circular route to %pI6\n", daddr);
		dst_release(ndst);
		वापस ERR_PTR(-ELOOP);
	पूर्ण

	*saddr = fl6.saddr;
	अगर (use_cache)
		dst_cache_set_ip6(dst_cache, ndst, saddr);
	वापस ndst;
पूर्ण
#पूर्ण_अगर

/* Bypass encapsulation अगर the destination is local */
अटल व्योम vxlan_encap_bypass(काष्ठा sk_buff *skb, काष्ठा vxlan_dev *src_vxlan,
			       काष्ठा vxlan_dev *dst_vxlan, __be32 vni,
			       bool snoop)
अणु
	काष्ठा pcpu_sw_netstats *tx_stats, *rx_stats;
	जोड़ vxlan_addr loopback;
	जोड़ vxlan_addr *remote_ip = &dst_vxlan->शेष_dst.remote_ip;
	काष्ठा net_device *dev;
	पूर्णांक len = skb->len;

	tx_stats = this_cpu_ptr(src_vxlan->dev->tstats);
	rx_stats = this_cpu_ptr(dst_vxlan->dev->tstats);
	skb->pkt_type = PACKET_HOST;
	skb->encapsulation = 0;
	skb->dev = dst_vxlan->dev;
	__skb_pull(skb, skb_network_offset(skb));

	अगर (remote_ip->sa.sa_family == AF_INET) अणु
		loopback.sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		loopback.sa.sa_family =  AF_INET;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		loopback.sin6.sin6_addr = in6addr_loopback;
		loopback.sa.sa_family =  AF_INET6;
#पूर्ण_अगर
	पूर्ण

	rcu_पढ़ो_lock();
	dev = skb->dev;
	अगर (unlikely(!(dev->flags & IFF_UP))) अणु
		kमुक्त_skb(skb);
		जाओ drop;
	पूर्ण

	अगर ((dst_vxlan->cfg.flags & VXLAN_F_LEARN) && snoop)
		vxlan_snoop(dev, &loopback, eth_hdr(skb)->h_source, 0, vni);

	u64_stats_update_begin(&tx_stats->syncp);
	tx_stats->tx_packets++;
	tx_stats->tx_bytes += len;
	u64_stats_update_end(&tx_stats->syncp);

	अगर (netअगर_rx(skb) == NET_RX_SUCCESS) अणु
		u64_stats_update_begin(&rx_stats->syncp);
		rx_stats->rx_packets++;
		rx_stats->rx_bytes += len;
		u64_stats_update_end(&rx_stats->syncp);
	पूर्ण अन्यथा अणु
drop:
		dev->stats.rx_dropped++;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक encap_bypass_अगर_local(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				 काष्ठा vxlan_dev *vxlan,
				 जोड़ vxlan_addr *daddr,
				 __be16 dst_port, पूर्णांक dst_अगरindex, __be32 vni,
				 काष्ठा dst_entry *dst,
				 u32 rt_flags)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	/* IPv6 rt-flags are checked against RTF_LOCAL, but the value of
	 * RTF_LOCAL is equal to RTCF_LOCAL. So to keep code simple
	 * we can use RTCF_LOCAL which works क्रम ipv4 and ipv6 route entry.
	 */
	BUILD_BUG_ON(RTCF_LOCAL != RTF_LOCAL);
#पूर्ण_अगर
	/* Bypass encapsulation अगर the destination is local */
	अगर (rt_flags & RTCF_LOCAL &&
	    !(rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))) अणु
		काष्ठा vxlan_dev *dst_vxlan;

		dst_release(dst);
		dst_vxlan = vxlan_find_vni(vxlan->net, dst_अगरindex, vni,
					   daddr->sa.sa_family, dst_port,
					   vxlan->cfg.flags);
		अगर (!dst_vxlan) अणु
			dev->stats.tx_errors++;
			kमुक्त_skb(skb);

			वापस -ENOENT;
		पूर्ण
		vxlan_encap_bypass(skb, vxlan, dst_vxlan, vni, true);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vxlan_xmit_one(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   __be32 शेष_vni, काष्ठा vxlan_rdst *rdst,
			   bool did_rsc)
अणु
	काष्ठा dst_cache *dst_cache;
	काष्ठा ip_tunnel_info *info;
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	स्थिर काष्ठा iphdr *old_iph = ip_hdr(skb);
	जोड़ vxlan_addr *dst;
	जोड़ vxlan_addr remote_ip, local_ip;
	काष्ठा vxlan_metadata _md;
	काष्ठा vxlan_metadata *md = &_md;
	__be16 src_port = 0, dst_port;
	काष्ठा dst_entry *ndst = शून्य;
	__be32 vni, label;
	__u8 tos, ttl;
	पूर्णांक अगरindex;
	पूर्णांक err;
	u32 flags = vxlan->cfg.flags;
	bool udp_sum = false;
	bool xnet = !net_eq(vxlan->net, dev_net(vxlan->dev));

	info = skb_tunnel_info(skb);

	अगर (rdst) अणु
		dst = &rdst->remote_ip;
		अगर (vxlan_addr_any(dst)) अणु
			अगर (did_rsc) अणु
				/* लघु-circuited back to local bridge */
				vxlan_encap_bypass(skb, vxlan, vxlan,
						   शेष_vni, true);
				वापस;
			पूर्ण
			जाओ drop;
		पूर्ण

		dst_port = rdst->remote_port ? rdst->remote_port : vxlan->cfg.dst_port;
		vni = (rdst->remote_vni) ? : शेष_vni;
		अगरindex = rdst->remote_अगरindex;
		local_ip = vxlan->cfg.saddr;
		dst_cache = &rdst->dst_cache;
		md->gbp = skb->mark;
		अगर (flags & VXLAN_F_TTL_INHERIT) अणु
			ttl = ip_tunnel_get_ttl(old_iph, skb);
		पूर्ण अन्यथा अणु
			ttl = vxlan->cfg.ttl;
			अगर (!ttl && vxlan_addr_multicast(dst))
				ttl = 1;
		पूर्ण

		tos = vxlan->cfg.tos;
		अगर (tos == 1)
			tos = ip_tunnel_get_dsfield(old_iph, skb);

		अगर (dst->sa.sa_family == AF_INET)
			udp_sum = !(flags & VXLAN_F_UDP_ZERO_CSUM_TX);
		अन्यथा
			udp_sum = !(flags & VXLAN_F_UDP_ZERO_CSUM6_TX);
		label = vxlan->cfg.label;
	पूर्ण अन्यथा अणु
		अगर (!info) अणु
			WARN_ONCE(1, "%s: Missing encapsulation instructions\n",
				  dev->name);
			जाओ drop;
		पूर्ण
		remote_ip.sa.sa_family = ip_tunnel_info_af(info);
		अगर (remote_ip.sa.sa_family == AF_INET) अणु
			remote_ip.sin.sin_addr.s_addr = info->key.u.ipv4.dst;
			local_ip.sin.sin_addr.s_addr = info->key.u.ipv4.src;
		पूर्ण अन्यथा अणु
			remote_ip.sin6.sin6_addr = info->key.u.ipv6.dst;
			local_ip.sin6.sin6_addr = info->key.u.ipv6.src;
		पूर्ण
		dst = &remote_ip;
		dst_port = info->key.tp_dst ? : vxlan->cfg.dst_port;
		vni = tunnel_id_to_key32(info->key.tun_id);
		अगरindex = 0;
		dst_cache = &info->dst_cache;
		अगर (info->key.tun_flags & TUNNEL_VXLAN_OPT) अणु
			अगर (info->options_len < माप(*md))
				जाओ drop;
			md = ip_tunnel_info_opts(info);
		पूर्ण
		ttl = info->key.ttl;
		tos = info->key.tos;
		label = info->key.label;
		udp_sum = !!(info->key.tun_flags & TUNNEL_CSUM);
	पूर्ण
	src_port = udp_flow_src_port(dev_net(dev), skb, vxlan->cfg.port_min,
				     vxlan->cfg.port_max, true);

	rcu_पढ़ो_lock();
	अगर (dst->sa.sa_family == AF_INET) अणु
		काष्ठा vxlan_sock *sock4 = rcu_dereference(vxlan->vn4_sock);
		काष्ठा rtable *rt;
		__be16 df = 0;

		अगर (!अगरindex)
			अगरindex = sock4->sock->sk->sk_bound_dev_अगर;

		rt = vxlan_get_route(vxlan, dev, sock4, skb, अगरindex, tos,
				     dst->sin.sin_addr.s_addr,
				     &local_ip.sin.sin_addr.s_addr,
				     dst_port, src_port,
				     dst_cache, info);
		अगर (IS_ERR(rt)) अणु
			err = PTR_ERR(rt);
			जाओ tx_error;
		पूर्ण

		अगर (!info) अणु
			/* Bypass encapsulation अगर the destination is local */
			err = encap_bypass_अगर_local(skb, dev, vxlan, dst,
						    dst_port, अगरindex, vni,
						    &rt->dst, rt->rt_flags);
			अगर (err)
				जाओ out_unlock;

			अगर (vxlan->cfg.df == VXLAN_DF_SET) अणु
				df = htons(IP_DF);
			पूर्ण अन्यथा अगर (vxlan->cfg.df == VXLAN_DF_INHERIT) अणु
				काष्ठा ethhdr *eth = eth_hdr(skb);

				अगर (ntohs(eth->h_proto) == ETH_P_IPV6 ||
				    (ntohs(eth->h_proto) == ETH_P_IP &&
				     old_iph->frag_off & htons(IP_DF)))
					df = htons(IP_DF);
			पूर्ण
		पूर्ण अन्यथा अगर (info->key.tun_flags & TUNNEL_DONT_FRAGMENT) अणु
			df = htons(IP_DF);
		पूर्ण

		ndst = &rt->dst;
		err = skb_tunnel_check_pmtu(skb, ndst, VXLAN_HEADROOM,
					    netअगर_is_any_bridge_port(dev));
		अगर (err < 0) अणु
			जाओ tx_error;
		पूर्ण अन्यथा अगर (err) अणु
			अगर (info) अणु
				काष्ठा ip_tunnel_info *unclone;
				काष्ठा in_addr src, dst;

				unclone = skb_tunnel_info_unclone(skb);
				अगर (unlikely(!unclone))
					जाओ tx_error;

				src = remote_ip.sin.sin_addr;
				dst = local_ip.sin.sin_addr;
				unclone->key.u.ipv4.src = src.s_addr;
				unclone->key.u.ipv4.dst = dst.s_addr;
			पूर्ण
			vxlan_encap_bypass(skb, vxlan, vxlan, vni, false);
			dst_release(ndst);
			जाओ out_unlock;
		पूर्ण

		tos = ip_tunnel_ecn_encap(tos, old_iph, skb);
		ttl = ttl ? : ip4_dst_hoplimit(&rt->dst);
		err = vxlan_build_skb(skb, ndst, माप(काष्ठा iphdr),
				      vni, md, flags, udp_sum);
		अगर (err < 0)
			जाओ tx_error;

		udp_tunnel_xmit_skb(rt, sock4->sock->sk, skb, local_ip.sin.sin_addr.s_addr,
				    dst->sin.sin_addr.s_addr, tos, ttl, df,
				    src_port, dst_port, xnet, !udp_sum);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		काष्ठा vxlan_sock *sock6 = rcu_dereference(vxlan->vn6_sock);

		अगर (!अगरindex)
			अगरindex = sock6->sock->sk->sk_bound_dev_अगर;

		ndst = vxlan6_get_route(vxlan, dev, sock6, skb, अगरindex, tos,
					label, &dst->sin6.sin6_addr,
					&local_ip.sin6.sin6_addr,
					dst_port, src_port,
					dst_cache, info);
		अगर (IS_ERR(ndst)) अणु
			err = PTR_ERR(ndst);
			ndst = शून्य;
			जाओ tx_error;
		पूर्ण

		अगर (!info) अणु
			u32 rt6i_flags = ((काष्ठा rt6_info *)ndst)->rt6i_flags;

			err = encap_bypass_अगर_local(skb, dev, vxlan, dst,
						    dst_port, अगरindex, vni,
						    ndst, rt6i_flags);
			अगर (err)
				जाओ out_unlock;
		पूर्ण

		err = skb_tunnel_check_pmtu(skb, ndst, VXLAN6_HEADROOM,
					    netअगर_is_any_bridge_port(dev));
		अगर (err < 0) अणु
			जाओ tx_error;
		पूर्ण अन्यथा अगर (err) अणु
			अगर (info) अणु
				काष्ठा ip_tunnel_info *unclone;
				काष्ठा in6_addr src, dst;

				unclone = skb_tunnel_info_unclone(skb);
				अगर (unlikely(!unclone))
					जाओ tx_error;

				src = remote_ip.sin6.sin6_addr;
				dst = local_ip.sin6.sin6_addr;
				unclone->key.u.ipv6.src = src;
				unclone->key.u.ipv6.dst = dst;
			पूर्ण

			vxlan_encap_bypass(skb, vxlan, vxlan, vni, false);
			dst_release(ndst);
			जाओ out_unlock;
		पूर्ण

		tos = ip_tunnel_ecn_encap(tos, old_iph, skb);
		ttl = ttl ? : ip6_dst_hoplimit(ndst);
		skb_scrub_packet(skb, xnet);
		err = vxlan_build_skb(skb, ndst, माप(काष्ठा ipv6hdr),
				      vni, md, flags, udp_sum);
		अगर (err < 0)
			जाओ tx_error;

		udp_tunnel6_xmit_skb(ndst, sock6->sock->sk, skb, dev,
				     &local_ip.sin6.sin6_addr,
				     &dst->sin6.sin6_addr, tos, ttl,
				     label, src_port, dst_port, !udp_sum);
#पूर्ण_अगर
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
	वापस;

drop:
	dev->stats.tx_dropped++;
	dev_kमुक्त_skb(skb);
	वापस;

tx_error:
	rcu_पढ़ो_unlock();
	अगर (err == -ELOOP)
		dev->stats.collisions++;
	अन्यथा अगर (err == -ENETUNREACH)
		dev->stats.tx_carrier_errors++;
	dst_release(ndst);
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम vxlan_xmit_nh(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  काष्ठा vxlan_fdb *f, __be32 vni, bool did_rsc)
अणु
	काष्ठा vxlan_rdst nh_rdst;
	काष्ठा nexthop *nh;
	bool करो_xmit;
	u32 hash;

	स_रखो(&nh_rdst, 0, माप(काष्ठा vxlan_rdst));
	hash = skb_get_hash(skb);

	rcu_पढ़ो_lock();
	nh = rcu_dereference(f->nh);
	अगर (!nh) अणु
		rcu_पढ़ो_unlock();
		जाओ drop;
	पूर्ण
	करो_xmit = vxlan_fdb_nh_path_select(nh, hash, &nh_rdst);
	rcu_पढ़ो_unlock();

	अगर (likely(करो_xmit))
		vxlan_xmit_one(skb, dev, vni, &nh_rdst, did_rsc);
	अन्यथा
		जाओ drop;

	वापस;

drop:
	dev->stats.tx_dropped++;
	dev_kमुक्त_skb(skb);
पूर्ण

/* Transmit local packets over Vxlan
 *
 * Outer IP header inherits ECN and DF from inner header.
 * Outer UDP destination is the VXLAN asचिन्हित port.
 *           source port is based on hash of flow
 */
अटल netdev_tx_t vxlan_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_rdst *rdst, *fdst = शून्य;
	स्थिर काष्ठा ip_tunnel_info *info;
	bool did_rsc = false;
	काष्ठा vxlan_fdb *f;
	काष्ठा ethhdr *eth;
	__be32 vni = 0;

	info = skb_tunnel_info(skb);

	skb_reset_mac_header(skb);

	अगर (vxlan->cfg.flags & VXLAN_F_COLLECT_METADATA) अणु
		अगर (info && info->mode & IP_TUNNEL_INFO_BRIDGE &&
		    info->mode & IP_TUNNEL_INFO_TX) अणु
			vni = tunnel_id_to_key32(info->key.tun_id);
		पूर्ण अन्यथा अणु
			अगर (info && info->mode & IP_TUNNEL_INFO_TX)
				vxlan_xmit_one(skb, dev, vni, शून्य, false);
			अन्यथा
				kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	अगर (vxlan->cfg.flags & VXLAN_F_PROXY) अणु
		eth = eth_hdr(skb);
		अगर (ntohs(eth->h_proto) == ETH_P_ARP)
			वापस arp_reduce(dev, skb, vni);
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (ntohs(eth->h_proto) == ETH_P_IPV6 &&
			 pskb_may_pull(skb, माप(काष्ठा ipv6hdr) +
					    माप(काष्ठा nd_msg)) &&
			 ipv6_hdr(skb)->nexthdr == IPPROTO_ICMPV6) अणु
			काष्ठा nd_msg *m = (काष्ठा nd_msg *)(ipv6_hdr(skb) + 1);

			अगर (m->icmph.icmp6_code == 0 &&
			    m->icmph.icmp6_type == NDISC_NEIGHBOUR_SOLICITATION)
				वापस neigh_reduce(dev, skb, vni);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	eth = eth_hdr(skb);
	f = vxlan_find_mac(vxlan, eth->h_dest, vni);
	did_rsc = false;

	अगर (f && (f->flags & NTF_ROUTER) && (vxlan->cfg.flags & VXLAN_F_RSC) &&
	    (ntohs(eth->h_proto) == ETH_P_IP ||
	     ntohs(eth->h_proto) == ETH_P_IPV6)) अणु
		did_rsc = route_लघुcircuit(dev, skb);
		अगर (did_rsc)
			f = vxlan_find_mac(vxlan, eth->h_dest, vni);
	पूर्ण

	अगर (f == शून्य) अणु
		f = vxlan_find_mac(vxlan, all_zeros_mac, vni);
		अगर (f == शून्य) अणु
			अगर ((vxlan->cfg.flags & VXLAN_F_L2MISS) &&
			    !is_multicast_ether_addr(eth->h_dest))
				vxlan_fdb_miss(vxlan, eth->h_dest);

			dev->stats.tx_dropped++;
			kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	अगर (rcu_access_poपूर्णांकer(f->nh)) अणु
		vxlan_xmit_nh(skb, dev, f,
			      (vni ? : vxlan->शेष_dst.remote_vni), did_rsc);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(rdst, &f->remotes, list) अणु
			काष्ठा sk_buff *skb1;

			अगर (!fdst) अणु
				fdst = rdst;
				जारी;
			पूर्ण
			skb1 = skb_clone(skb, GFP_ATOMIC);
			अगर (skb1)
				vxlan_xmit_one(skb1, dev, vni, rdst, did_rsc);
		पूर्ण
		अगर (fdst)
			vxlan_xmit_one(skb, dev, vni, fdst, did_rsc);
		अन्यथा
			kमुक्त_skb(skb);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/* Walk the क्रमwarding table and purge stale entries */
अटल व्योम vxlan_cleanup(काष्ठा समयr_list *t)
अणु
	काष्ठा vxlan_dev *vxlan = from_समयr(vxlan, t, age_समयr);
	अचिन्हित दीर्घ next_समयr = jअगरfies + FDB_AGE_INTERVAL;
	अचिन्हित पूर्णांक h;

	अगर (!netअगर_running(vxlan->dev))
		वापस;

	क्रम (h = 0; h < FDB_HASH_SIZE; ++h) अणु
		काष्ठा hlist_node *p, *n;

		spin_lock(&vxlan->hash_lock[h]);
		hlist_क्रम_each_safe(p, n, &vxlan->fdb_head[h]) अणु
			काष्ठा vxlan_fdb *f
				= container_of(p, काष्ठा vxlan_fdb, hlist);
			अचिन्हित दीर्घ समयout;

			अगर (f->state & (NUD_PERMANENT | NUD_NOARP))
				जारी;

			अगर (f->flags & NTF_EXT_LEARNED)
				जारी;

			समयout = f->used + vxlan->cfg.age_पूर्णांकerval * HZ;
			अगर (समय_beक्रमe_eq(समयout, jअगरfies)) अणु
				netdev_dbg(vxlan->dev,
					   "garbage collect %pM\n",
					   f->eth_addr);
				f->state = NUD_STALE;
				vxlan_fdb_destroy(vxlan, f, true, true);
			पूर्ण अन्यथा अगर (समय_beक्रमe(समयout, next_समयr))
				next_समयr = समयout;
		पूर्ण
		spin_unlock(&vxlan->hash_lock[h]);
	पूर्ण

	mod_समयr(&vxlan->age_समयr, next_समयr);
पूर्ण

अटल व्योम vxlan_vs_del_dev(काष्ठा vxlan_dev *vxlan)
अणु
	काष्ठा vxlan_net *vn = net_generic(vxlan->net, vxlan_net_id);

	spin_lock(&vn->sock_lock);
	hlist_del_init_rcu(&vxlan->hlist4.hlist);
#अगर IS_ENABLED(CONFIG_IPV6)
	hlist_del_init_rcu(&vxlan->hlist6.hlist);
#पूर्ण_अगर
	spin_unlock(&vn->sock_lock);
पूर्ण

अटल व्योम vxlan_vs_add_dev(काष्ठा vxlan_sock *vs, काष्ठा vxlan_dev *vxlan,
			     काष्ठा vxlan_dev_node *node)
अणु
	काष्ठा vxlan_net *vn = net_generic(vxlan->net, vxlan_net_id);
	__be32 vni = vxlan->शेष_dst.remote_vni;

	node->vxlan = vxlan;
	spin_lock(&vn->sock_lock);
	hlist_add_head_rcu(&node->hlist, vni_head(vs, vni));
	spin_unlock(&vn->sock_lock);
पूर्ण

/* Setup stats when device is created */
अटल पूर्णांक vxlan_init(काष्ठा net_device *dev)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	पूर्णांक err;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	err = gro_cells_init(&vxlan->gro_cells, dev);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vxlan_fdb_delete_शेष(काष्ठा vxlan_dev *vxlan, __be32 vni)
अणु
	काष्ठा vxlan_fdb *f;
	u32 hash_index = fdb_head_index(vxlan, all_zeros_mac, vni);

	spin_lock_bh(&vxlan->hash_lock[hash_index]);
	f = __vxlan_find_mac(vxlan, all_zeros_mac, vni);
	अगर (f)
		vxlan_fdb_destroy(vxlan, f, true, true);
	spin_unlock_bh(&vxlan->hash_lock[hash_index]);
पूर्ण

अटल व्योम vxlan_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);

	gro_cells_destroy(&vxlan->gro_cells);

	vxlan_fdb_delete_शेष(vxlan, vxlan->cfg.vni);

	मुक्त_percpu(dev->tstats);
पूर्ण

/* Start ageing समयr and join group when device is brought up */
अटल पूर्णांक vxlan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	पूर्णांक ret;

	ret = vxlan_sock_add(vxlan);
	अगर (ret < 0)
		वापस ret;

	अगर (vxlan_addr_multicast(&vxlan->शेष_dst.remote_ip)) अणु
		ret = vxlan_igmp_join(vxlan);
		अगर (ret == -EADDRINUSE)
			ret = 0;
		अगर (ret) अणु
			vxlan_sock_release(vxlan);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (vxlan->cfg.age_पूर्णांकerval)
		mod_समयr(&vxlan->age_समयr, jअगरfies + FDB_AGE_INTERVAL);

	वापस ret;
पूर्ण

/* Purge the क्रमwarding table */
अटल व्योम vxlan_flush(काष्ठा vxlan_dev *vxlan, bool करो_all)
अणु
	अचिन्हित पूर्णांक h;

	क्रम (h = 0; h < FDB_HASH_SIZE; ++h) अणु
		काष्ठा hlist_node *p, *n;

		spin_lock_bh(&vxlan->hash_lock[h]);
		hlist_क्रम_each_safe(p, n, &vxlan->fdb_head[h]) अणु
			काष्ठा vxlan_fdb *f
				= container_of(p, काष्ठा vxlan_fdb, hlist);
			अगर (!करो_all && (f->state & (NUD_PERMANENT | NUD_NOARP)))
				जारी;
			/* the all_zeros_mac entry is deleted at vxlan_uninit */
			अगर (is_zero_ether_addr(f->eth_addr) &&
			    f->vni == vxlan->cfg.vni)
				जारी;
			vxlan_fdb_destroy(vxlan, f, true, true);
		पूर्ण
		spin_unlock_bh(&vxlan->hash_lock[h]);
	पूर्ण
पूर्ण

/* Cleanup समयr and क्रमwarding table on shutकरोwn */
अटल पूर्णांक vxlan_stop(काष्ठा net_device *dev)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_net *vn = net_generic(vxlan->net, vxlan_net_id);
	पूर्णांक ret = 0;

	अगर (vxlan_addr_multicast(&vxlan->शेष_dst.remote_ip) &&
	    !vxlan_group_used(vn, vxlan))
		ret = vxlan_igmp_leave(vxlan);

	del_समयr_sync(&vxlan->age_समयr);

	vxlan_flush(vxlan, false);
	vxlan_sock_release(vxlan);

	वापस ret;
पूर्ण

/* Stub, nothing needs to be करोne. */
अटल व्योम vxlan_set_multicast_list(काष्ठा net_device *dev)
अणु
पूर्ण

अटल पूर्णांक vxlan_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_rdst *dst = &vxlan->शेष_dst;
	काष्ठा net_device *lowerdev = __dev_get_by_index(vxlan->net,
							 dst->remote_अगरindex);
	bool use_ipv6 = !!(vxlan->cfg.flags & VXLAN_F_IPV6);

	/* This check is dअगरferent than dev->max_mtu, because it looks at
	 * the lowerdev->mtu, rather than the अटल dev->max_mtu
	 */
	अगर (lowerdev) अणु
		पूर्णांक max_mtu = lowerdev->mtu -
			      (use_ipv6 ? VXLAN6_HEADROOM : VXLAN_HEADROOM);
		अगर (new_mtu > max_mtu)
			वापस -EINVAL;
	पूर्ण

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल पूर्णांक vxlan_fill_metadata_dst(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा ip_tunnel_info *info = skb_tunnel_info(skb);
	__be16 sport, dport;

	sport = udp_flow_src_port(dev_net(dev), skb, vxlan->cfg.port_min,
				  vxlan->cfg.port_max, true);
	dport = info->key.tp_dst ? : vxlan->cfg.dst_port;

	अगर (ip_tunnel_info_af(info) == AF_INET) अणु
		काष्ठा vxlan_sock *sock4 = rcu_dereference(vxlan->vn4_sock);
		काष्ठा rtable *rt;

		rt = vxlan_get_route(vxlan, dev, sock4, skb, 0, info->key.tos,
				     info->key.u.ipv4.dst,
				     &info->key.u.ipv4.src, dport, sport,
				     &info->dst_cache, info);
		अगर (IS_ERR(rt))
			वापस PTR_ERR(rt);
		ip_rt_put(rt);
	पूर्ण अन्यथा अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा vxlan_sock *sock6 = rcu_dereference(vxlan->vn6_sock);
		काष्ठा dst_entry *ndst;

		ndst = vxlan6_get_route(vxlan, dev, sock6, skb, 0, info->key.tos,
					info->key.label, &info->key.u.ipv6.dst,
					&info->key.u.ipv6.src, dport, sport,
					&info->dst_cache, info);
		अगर (IS_ERR(ndst))
			वापस PTR_ERR(ndst);
		dst_release(ndst);
#अन्यथा /* !CONFIG_IPV6 */
		वापस -EPFNOSUPPORT;
#पूर्ण_अगर
	पूर्ण
	info->key.tp_src = sport;
	info->key.tp_dst = dport;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops vxlan_netdev_ether_ops = अणु
	.nकरो_init		= vxlan_init,
	.nकरो_uninit		= vxlan_uninit,
	.nकरो_खोलो		= vxlan_खोलो,
	.nकरो_stop		= vxlan_stop,
	.nकरो_start_xmit		= vxlan_xmit,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_rx_mode	= vxlan_set_multicast_list,
	.nकरो_change_mtu		= vxlan_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_fdb_add		= vxlan_fdb_add,
	.nकरो_fdb_del		= vxlan_fdb_delete,
	.nकरो_fdb_dump		= vxlan_fdb_dump,
	.nकरो_fdb_get		= vxlan_fdb_get,
	.nकरो_fill_metadata_dst	= vxlan_fill_metadata_dst,
	.nकरो_change_proto_करोwn  = dev_change_proto_करोwn_generic,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops vxlan_netdev_raw_ops = अणु
	.nकरो_init		= vxlan_init,
	.nकरो_uninit		= vxlan_uninit,
	.nकरो_खोलो		= vxlan_खोलो,
	.nकरो_stop		= vxlan_stop,
	.nकरो_start_xmit		= vxlan_xmit,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_change_mtu		= vxlan_change_mtu,
	.nकरो_fill_metadata_dst	= vxlan_fill_metadata_dst,
पूर्ण;

/* Info क्रम udev, that this is a भव tunnel endpoपूर्णांक */
अटल काष्ठा device_type vxlan_type = अणु
	.name = "vxlan",
पूर्ण;

/* Calls the nकरो_udp_tunnel_add of the caller in order to
 * supply the listening VXLAN udp ports. Callers are expected
 * to implement the nकरो_udp_tunnel_add.
 */
अटल व्योम vxlan_offload_rx_ports(काष्ठा net_device *dev, bool push)
अणु
	काष्ठा vxlan_sock *vs;
	काष्ठा net *net = dev_net(dev);
	काष्ठा vxlan_net *vn = net_generic(net, vxlan_net_id);
	अचिन्हित पूर्णांक i;

	spin_lock(&vn->sock_lock);
	क्रम (i = 0; i < PORT_HASH_SIZE; ++i) अणु
		hlist_क्रम_each_entry_rcu(vs, &vn->sock_list[i], hlist) अणु
			अचिन्हित लघु type;

			अगर (vs->flags & VXLAN_F_GPE)
				type = UDP_TUNNEL_TYPE_VXLAN_GPE;
			अन्यथा
				type = UDP_TUNNEL_TYPE_VXLAN;

			अगर (push)
				udp_tunnel_push_rx_port(dev, vs->sock, type);
			अन्यथा
				udp_tunnel_drop_rx_port(dev, vs->sock, type);
		पूर्ण
	पूर्ण
	spin_unlock(&vn->sock_lock);
पूर्ण

/* Initialize the device काष्ठाure. */
अटल व्योम vxlan_setup(काष्ठा net_device *dev)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	अचिन्हित पूर्णांक h;

	eth_hw_addr_अक्रमom(dev);
	ether_setup(dev);

	dev->needs_मुक्त_netdev = true;
	SET_NETDEV_DEVTYPE(dev, &vxlan_type);

	dev->features	|= NETIF_F_LLTX;
	dev->features	|= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FRAGLIST;
	dev->features   |= NETIF_F_RXCSUM;
	dev->features   |= NETIF_F_GSO_SOFTWARE;

	dev->vlan_features = dev->features;
	dev->hw_features |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_FRAGLIST;
	dev->hw_features |= NETIF_F_RXCSUM;
	dev->hw_features |= NETIF_F_GSO_SOFTWARE;
	netअगर_keep_dst(dev);
	dev->priv_flags |= IFF_NO_QUEUE;

	/* MTU range: 68 - 65535 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = ETH_MAX_MTU;

	INIT_LIST_HEAD(&vxlan->next);

	समयr_setup(&vxlan->age_समयr, vxlan_cleanup, TIMER_DEFERRABLE);

	vxlan->dev = dev;

	क्रम (h = 0; h < FDB_HASH_SIZE; ++h) अणु
		spin_lock_init(&vxlan->hash_lock[h]);
		INIT_HLIST_HEAD(&vxlan->fdb_head[h]);
	पूर्ण
पूर्ण

अटल व्योम vxlan_ether_setup(काष्ठा net_device *dev)
अणु
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	dev->netdev_ops = &vxlan_netdev_ether_ops;
पूर्ण

अटल व्योम vxlan_raw_setup(काष्ठा net_device *dev)
अणु
	dev->header_ops = शून्य;
	dev->type = ARPHRD_NONE;
	dev->hard_header_len = 0;
	dev->addr_len = 0;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	dev->netdev_ops = &vxlan_netdev_raw_ops;
पूर्ण

अटल स्थिर काष्ठा nla_policy vxlan_policy[IFLA_VXLAN_MAX + 1] = अणु
	[IFLA_VXLAN_ID]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VXLAN_GROUP]	= अणु .len = माप_field(काष्ठा iphdr, daddr) पूर्ण,
	[IFLA_VXLAN_GROUP6]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFLA_VXLAN_LINK]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VXLAN_LOCAL]	= अणु .len = माप_field(काष्ठा iphdr, saddr) पूर्ण,
	[IFLA_VXLAN_LOCAL6]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFLA_VXLAN_TOS]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_TTL]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_LABEL]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VXLAN_LEARNING]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_AGEING]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VXLAN_LIMIT]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VXLAN_PORT_RANGE] = अणु .len  = माप(काष्ठा अगरla_vxlan_port_range) पूर्ण,
	[IFLA_VXLAN_PROXY]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_RSC]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_L2MISS]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_L3MISS]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_COLLECT_METADATA]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_PORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_VXLAN_UDP_CSUM]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_UDP_ZERO_CSUM6_TX]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_UDP_ZERO_CSUM6_RX]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_REMCSUM_TX]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_REMCSUM_RX]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_VXLAN_GBP]	= अणु .type = NLA_FLAG, पूर्ण,
	[IFLA_VXLAN_GPE]	= अणु .type = NLA_FLAG, पूर्ण,
	[IFLA_VXLAN_REMCSUM_NOPARTIAL]	= अणु .type = NLA_FLAG पूर्ण,
	[IFLA_VXLAN_TTL_INHERIT]	= अणु .type = NLA_FLAG पूर्ण,
	[IFLA_VXLAN_DF]		= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक vxlan_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_ADDRESS],
					    "Provided link layer address is not Ethernet");
			वापस -EINVAL;
		पूर्ण

		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS]))) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_ADDRESS],
					    "Provided Ethernet address is not unicast");
			वापस -EADDRNOTAVAIL;
		पूर्ण
	पूर्ण

	अगर (tb[IFLA_MTU]) अणु
		u32 mtu = nla_get_u32(tb[IFLA_MTU]);

		अगर (mtu < ETH_MIN_MTU || mtu > ETH_MAX_MTU) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_MTU],
					    "MTU must be between 68 and 65535");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!data) अणु
		NL_SET_ERR_MSG(extack,
			       "Required attributes not provided to perform the operation");
		वापस -EINVAL;
	पूर्ण

	अगर (data[IFLA_VXLAN_ID]) अणु
		u32 id = nla_get_u32(data[IFLA_VXLAN_ID]);

		अगर (id >= VXLAN_N_VID) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_VXLAN_ID],
					    "VXLAN ID must be lower than 16777216");
			वापस -दुस्फल;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_VXLAN_PORT_RANGE]) अणु
		स्थिर काष्ठा अगरla_vxlan_port_range *p
			= nla_data(data[IFLA_VXLAN_PORT_RANGE]);

		अगर (ntohs(p->high) < ntohs(p->low)) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_VXLAN_PORT_RANGE],
					    "Invalid source port range");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_VXLAN_DF]) अणु
		क्रमागत अगरla_vxlan_df df = nla_get_u8(data[IFLA_VXLAN_DF]);

		अगर (df < 0 || df > VXLAN_DF_MAX) अणु
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_VXLAN_DF],
					    "Invalid DF attribute");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vxlan_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->version, VXLAN_VERSION, माप(drvinfo->version));
	strlcpy(drvinfo->driver, "vxlan", माप(drvinfo->driver));
पूर्ण

अटल पूर्णांक vxlan_get_link_ksettings(काष्ठा net_device *dev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_rdst *dst = &vxlan->शेष_dst;
	काष्ठा net_device *lowerdev = __dev_get_by_index(vxlan->net,
							 dst->remote_अगरindex);

	अगर (!lowerdev) अणु
		cmd->base.duplex = DUPLEX_UNKNOWN;
		cmd->base.port = PORT_OTHER;
		cmd->base.speed = SPEED_UNKNOWN;

		वापस 0;
	पूर्ण

	वापस __ethtool_get_link_ksettings(lowerdev, cmd);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vxlan_ethtool_ops = अणु
	.get_drvinfo		= vxlan_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= vxlan_get_link_ksettings,
पूर्ण;

अटल काष्ठा socket *vxlan_create_sock(काष्ठा net *net, bool ipv6,
					__be16 port, u32 flags, पूर्णांक अगरindex)
अणु
	काष्ठा socket *sock;
	काष्ठा udp_port_cfg udp_conf;
	पूर्णांक err;

	स_रखो(&udp_conf, 0, माप(udp_conf));

	अगर (ipv6) अणु
		udp_conf.family = AF_INET6;
		udp_conf.use_udp6_rx_checksums =
		    !(flags & VXLAN_F_UDP_ZERO_CSUM6_RX);
		udp_conf.ipv6_v6only = 1;
	पूर्ण अन्यथा अणु
		udp_conf.family = AF_INET;
	पूर्ण

	udp_conf.local_udp_port = port;
	udp_conf.bind_अगरindex = अगरindex;

	/* Open UDP socket */
	err = udp_sock_create(net, &udp_conf, &sock);
	अगर (err < 0)
		वापस ERR_PTR(err);

	udp_allow_gso(sock->sk);
	वापस sock;
पूर्ण

/* Create new listen socket अगर needed */
अटल काष्ठा vxlan_sock *vxlan_socket_create(काष्ठा net *net, bool ipv6,
					      __be16 port, u32 flags,
					      पूर्णांक अगरindex)
अणु
	काष्ठा vxlan_net *vn = net_generic(net, vxlan_net_id);
	काष्ठा vxlan_sock *vs;
	काष्ठा socket *sock;
	अचिन्हित पूर्णांक h;
	काष्ठा udp_tunnel_sock_cfg tunnel_cfg;

	vs = kzalloc(माप(*vs), GFP_KERNEL);
	अगर (!vs)
		वापस ERR_PTR(-ENOMEM);

	क्रम (h = 0; h < VNI_HASH_SIZE; ++h)
		INIT_HLIST_HEAD(&vs->vni_list[h]);

	sock = vxlan_create_sock(net, ipv6, port, flags, अगरindex);
	अगर (IS_ERR(sock)) अणु
		kमुक्त(vs);
		वापस ERR_CAST(sock);
	पूर्ण

	vs->sock = sock;
	refcount_set(&vs->refcnt, 1);
	vs->flags = (flags & VXLAN_F_RCV_FLAGS);

	spin_lock(&vn->sock_lock);
	hlist_add_head_rcu(&vs->hlist, vs_head(net, port));
	udp_tunnel_notअगरy_add_rx_port(sock,
				      (vs->flags & VXLAN_F_GPE) ?
				      UDP_TUNNEL_TYPE_VXLAN_GPE :
				      UDP_TUNNEL_TYPE_VXLAN);
	spin_unlock(&vn->sock_lock);

	/* Mark socket as an encapsulation socket. */
	स_रखो(&tunnel_cfg, 0, माप(tunnel_cfg));
	tunnel_cfg.sk_user_data = vs;
	tunnel_cfg.encap_type = 1;
	tunnel_cfg.encap_rcv = vxlan_rcv;
	tunnel_cfg.encap_err_lookup = vxlan_err_lookup;
	tunnel_cfg.encap_destroy = शून्य;
	tunnel_cfg.gro_receive = vxlan_gro_receive;
	tunnel_cfg.gro_complete = vxlan_gro_complete;

	setup_udp_tunnel_sock(net, sock, &tunnel_cfg);

	वापस vs;
पूर्ण

अटल पूर्णांक __vxlan_sock_add(काष्ठा vxlan_dev *vxlan, bool ipv6)
अणु
	काष्ठा vxlan_net *vn = net_generic(vxlan->net, vxlan_net_id);
	काष्ठा vxlan_sock *vs = शून्य;
	काष्ठा vxlan_dev_node *node;
	पूर्णांक l3mdev_index = 0;

	अगर (vxlan->cfg.remote_अगरindex)
		l3mdev_index = l3mdev_master_upper_अगरindex_by_index(
			vxlan->net, vxlan->cfg.remote_अगरindex);

	अगर (!vxlan->cfg.no_share) अणु
		spin_lock(&vn->sock_lock);
		vs = vxlan_find_sock(vxlan->net, ipv6 ? AF_INET6 : AF_INET,
				     vxlan->cfg.dst_port, vxlan->cfg.flags,
				     l3mdev_index);
		अगर (vs && !refcount_inc_not_zero(&vs->refcnt)) अणु
			spin_unlock(&vn->sock_lock);
			वापस -EBUSY;
		पूर्ण
		spin_unlock(&vn->sock_lock);
	पूर्ण
	अगर (!vs)
		vs = vxlan_socket_create(vxlan->net, ipv6,
					 vxlan->cfg.dst_port, vxlan->cfg.flags,
					 l3mdev_index);
	अगर (IS_ERR(vs))
		वापस PTR_ERR(vs);
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (ipv6) अणु
		rcu_assign_poपूर्णांकer(vxlan->vn6_sock, vs);
		node = &vxlan->hlist6;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		rcu_assign_poपूर्णांकer(vxlan->vn4_sock, vs);
		node = &vxlan->hlist4;
	पूर्ण
	vxlan_vs_add_dev(vs, vxlan, node);
	वापस 0;
पूर्ण

अटल पूर्णांक vxlan_sock_add(काष्ठा vxlan_dev *vxlan)
अणु
	bool metadata = vxlan->cfg.flags & VXLAN_F_COLLECT_METADATA;
	bool ipv6 = vxlan->cfg.flags & VXLAN_F_IPV6 || metadata;
	bool ipv4 = !ipv6 || metadata;
	पूर्णांक ret = 0;

	RCU_INIT_POINTER(vxlan->vn4_sock, शून्य);
#अगर IS_ENABLED(CONFIG_IPV6)
	RCU_INIT_POINTER(vxlan->vn6_sock, शून्य);
	अगर (ipv6) अणु
		ret = __vxlan_sock_add(vxlan, true);
		अगर (ret < 0 && ret != -EAFNOSUPPORT)
			ipv4 = false;
	पूर्ण
#पूर्ण_अगर
	अगर (ipv4)
		ret = __vxlan_sock_add(vxlan, false);
	अगर (ret < 0)
		vxlan_sock_release(vxlan);
	वापस ret;
पूर्ण

अटल पूर्णांक vxlan_config_validate(काष्ठा net *src_net, काष्ठा vxlan_config *conf,
				 काष्ठा net_device **lower,
				 काष्ठा vxlan_dev *old,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_net *vn = net_generic(src_net, vxlan_net_id);
	काष्ठा vxlan_dev *पंचांगp;
	bool use_ipv6 = false;

	अगर (conf->flags & VXLAN_F_GPE) अणु
		/* For now, allow GPE only together with
		 * COLLECT_METADATA. This can be relaxed later; in such
		 * हाल, the other side of the PtP link will have to be
		 * provided.
		 */
		अगर ((conf->flags & ~VXLAN_F_ALLOWED_GPE) ||
		    !(conf->flags & VXLAN_F_COLLECT_METADATA)) अणु
			NL_SET_ERR_MSG(extack,
				       "VXLAN GPE does not support this combination of attributes");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!conf->remote_ip.sa.sa_family && !conf->saddr.sa.sa_family) अणु
		/* Unless IPv6 is explicitly requested, assume IPv4 */
		conf->remote_ip.sa.sa_family = AF_INET;
		conf->saddr.sa.sa_family = AF_INET;
	पूर्ण अन्यथा अगर (!conf->remote_ip.sa.sa_family) अणु
		conf->remote_ip.sa.sa_family = conf->saddr.sa.sa_family;
	पूर्ण अन्यथा अगर (!conf->saddr.sa.sa_family) अणु
		conf->saddr.sa.sa_family = conf->remote_ip.sa.sa_family;
	पूर्ण

	अगर (conf->saddr.sa.sa_family != conf->remote_ip.sa.sa_family) अणु
		NL_SET_ERR_MSG(extack,
			       "Local and remote address must be from the same family");
		वापस -EINVAL;
	पूर्ण

	अगर (vxlan_addr_multicast(&conf->saddr)) अणु
		NL_SET_ERR_MSG(extack, "Local address cannot be multicast");
		वापस -EINVAL;
	पूर्ण

	अगर (conf->saddr.sa.sa_family == AF_INET6) अणु
		अगर (!IS_ENABLED(CONFIG_IPV6)) अणु
			NL_SET_ERR_MSG(extack,
				       "IPv6 support not enabled in the kernel");
			वापस -EPFNOSUPPORT;
		पूर्ण
		use_ipv6 = true;
		conf->flags |= VXLAN_F_IPV6;

		अगर (!(conf->flags & VXLAN_F_COLLECT_METADATA)) अणु
			पूर्णांक local_type =
				ipv6_addr_type(&conf->saddr.sin6.sin6_addr);
			पूर्णांक remote_type =
				ipv6_addr_type(&conf->remote_ip.sin6.sin6_addr);

			अगर (local_type & IPV6_ADDR_LINKLOCAL) अणु
				अगर (!(remote_type & IPV6_ADDR_LINKLOCAL) &&
				    (remote_type != IPV6_ADDR_ANY)) अणु
					NL_SET_ERR_MSG(extack,
						       "Invalid combination of local and remote address scopes");
					वापस -EINVAL;
				पूर्ण

				conf->flags |= VXLAN_F_IPV6_LINKLOCAL;
			पूर्ण अन्यथा अणु
				अगर (remote_type ==
				    (IPV6_ADDR_UNICAST | IPV6_ADDR_LINKLOCAL)) अणु
					NL_SET_ERR_MSG(extack,
						       "Invalid combination of local and remote address scopes");
					वापस -EINVAL;
				पूर्ण

				conf->flags &= ~VXLAN_F_IPV6_LINKLOCAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (conf->label && !use_ipv6) अणु
		NL_SET_ERR_MSG(extack,
			       "Label attribute only applies to IPv6 VXLAN devices");
		वापस -EINVAL;
	पूर्ण

	अगर (conf->remote_अगरindex) अणु
		काष्ठा net_device *lowerdev;

		lowerdev = __dev_get_by_index(src_net, conf->remote_अगरindex);
		अगर (!lowerdev) अणु
			NL_SET_ERR_MSG(extack,
				       "Invalid local interface, device not found");
			वापस -ENODEV;
		पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (use_ipv6) अणु
			काष्ठा inet6_dev *idev = __in6_dev_get(lowerdev);

			अगर (idev && idev->cnf.disable_ipv6) अणु
				NL_SET_ERR_MSG(extack,
					       "IPv6 support disabled by administrator");
				वापस -EPERM;
			पूर्ण
		पूर्ण
#पूर्ण_अगर

		*lower = lowerdev;
	पूर्ण अन्यथा अणु
		अगर (vxlan_addr_multicast(&conf->remote_ip)) अणु
			NL_SET_ERR_MSG(extack,
				       "Local interface required for multicast remote destination");

			वापस -EINVAL;
		पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (conf->flags & VXLAN_F_IPV6_LINKLOCAL) अणु
			NL_SET_ERR_MSG(extack,
				       "Local interface required for link-local local/remote addresses");
			वापस -EINVAL;
		पूर्ण
#पूर्ण_अगर

		*lower = शून्य;
	पूर्ण

	अगर (!conf->dst_port) अणु
		अगर (conf->flags & VXLAN_F_GPE)
			conf->dst_port = htons(4790); /* IANA VXLAN-GPE port */
		अन्यथा
			conf->dst_port = htons(vxlan_port);
	पूर्ण

	अगर (!conf->age_पूर्णांकerval)
		conf->age_पूर्णांकerval = FDB_AGE_DEFAULT;

	list_क्रम_each_entry(पंचांगp, &vn->vxlan_list, next) अणु
		अगर (पंचांगp == old)
			जारी;

		अगर (पंचांगp->cfg.vni != conf->vni)
			जारी;
		अगर (पंचांगp->cfg.dst_port != conf->dst_port)
			जारी;
		अगर ((पंचांगp->cfg.flags & (VXLAN_F_RCV_FLAGS | VXLAN_F_IPV6)) !=
		    (conf->flags & (VXLAN_F_RCV_FLAGS | VXLAN_F_IPV6)))
			जारी;

		अगर ((conf->flags & VXLAN_F_IPV6_LINKLOCAL) &&
		    पंचांगp->cfg.remote_अगरindex != conf->remote_अगरindex)
			जारी;

		NL_SET_ERR_MSG(extack,
			       "A VXLAN device with the specified VNI already exists");
		वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vxlan_config_apply(काष्ठा net_device *dev,
			       काष्ठा vxlan_config *conf,
			       काष्ठा net_device *lowerdev,
			       काष्ठा net *src_net,
			       bool changelink)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_rdst *dst = &vxlan->शेष_dst;
	अचिन्हित लघु needed_headroom = ETH_HLEN;
	bool use_ipv6 = !!(conf->flags & VXLAN_F_IPV6);
	पूर्णांक max_mtu = ETH_MAX_MTU;

	अगर (!changelink) अणु
		अगर (conf->flags & VXLAN_F_GPE)
			vxlan_raw_setup(dev);
		अन्यथा
			vxlan_ether_setup(dev);

		अगर (conf->mtu)
			dev->mtu = conf->mtu;

		vxlan->net = src_net;
	पूर्ण

	dst->remote_vni = conf->vni;

	स_नकल(&dst->remote_ip, &conf->remote_ip, माप(conf->remote_ip));

	अगर (lowerdev) अणु
		dst->remote_अगरindex = conf->remote_अगरindex;

		dev->gso_max_size = lowerdev->gso_max_size;
		dev->gso_max_segs = lowerdev->gso_max_segs;

		needed_headroom = lowerdev->hard_header_len;
		needed_headroom += lowerdev->needed_headroom;

		dev->needed_tailroom = lowerdev->needed_tailroom;

		max_mtu = lowerdev->mtu - (use_ipv6 ? VXLAN6_HEADROOM :
					   VXLAN_HEADROOM);
		अगर (max_mtu < ETH_MIN_MTU)
			max_mtu = ETH_MIN_MTU;

		अगर (!changelink && !conf->mtu)
			dev->mtu = max_mtu;
	पूर्ण

	अगर (dev->mtu > max_mtu)
		dev->mtu = max_mtu;

	अगर (use_ipv6 || conf->flags & VXLAN_F_COLLECT_METADATA)
		needed_headroom += VXLAN6_HEADROOM;
	अन्यथा
		needed_headroom += VXLAN_HEADROOM;
	dev->needed_headroom = needed_headroom;

	स_नकल(&vxlan->cfg, conf, माप(*conf));
पूर्ण

अटल पूर्णांक vxlan_dev_configure(काष्ठा net *src_net, काष्ठा net_device *dev,
			       काष्ठा vxlan_config *conf, bool changelink,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev;
	पूर्णांक ret;

	ret = vxlan_config_validate(src_net, conf, &lowerdev, vxlan, extack);
	अगर (ret)
		वापस ret;

	vxlan_config_apply(dev, conf, lowerdev, src_net, changelink);

	वापस 0;
पूर्ण

अटल पूर्णांक __vxlan_dev_create(काष्ठा net *net, काष्ठा net_device *dev,
			      काष्ठा vxlan_config *conf,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_net *vn = net_generic(net, vxlan_net_id);
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा net_device *remote_dev = शून्य;
	काष्ठा vxlan_fdb *f = शून्य;
	bool unरेजिस्टर = false;
	काष्ठा vxlan_rdst *dst;
	पूर्णांक err;

	dst = &vxlan->शेष_dst;
	err = vxlan_dev_configure(net, dev, conf, false, extack);
	अगर (err)
		वापस err;

	dev->ethtool_ops = &vxlan_ethtool_ops;

	/* create an fdb entry क्रम a valid शेष destination */
	अगर (!vxlan_addr_any(&dst->remote_ip)) अणु
		err = vxlan_fdb_create(vxlan, all_zeros_mac,
				       &dst->remote_ip,
				       NUD_REACHABLE | NUD_PERMANENT,
				       vxlan->cfg.dst_port,
				       dst->remote_vni,
				       dst->remote_vni,
				       dst->remote_अगरindex,
				       NTF_SELF, 0, &f, extack);
		अगर (err)
			वापस err;
	पूर्ण

	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		जाओ errout;
	unरेजिस्टर = true;

	अगर (dst->remote_अगरindex) अणु
		remote_dev = __dev_get_by_index(net, dst->remote_अगरindex);
		अगर (!remote_dev) अणु
			err = -ENODEV;
			जाओ errout;
		पूर्ण

		err = netdev_upper_dev_link(remote_dev, dev, extack);
		अगर (err)
			जाओ errout;
	पूर्ण

	err = rtnl_configure_link(dev, शून्य);
	अगर (err < 0)
		जाओ unlink;

	अगर (f) अणु
		vxlan_fdb_insert(vxlan, all_zeros_mac, dst->remote_vni, f);

		/* notअगरy शेष fdb entry */
		err = vxlan_fdb_notअगरy(vxlan, f, first_remote_rtnl(f),
				       RTM_NEWNEIGH, true, extack);
		अगर (err) अणु
			vxlan_fdb_destroy(vxlan, f, false, false);
			अगर (remote_dev)
				netdev_upper_dev_unlink(remote_dev, dev);
			जाओ unरेजिस्टर;
		पूर्ण
	पूर्ण

	list_add(&vxlan->next, &vn->vxlan_list);
	अगर (remote_dev)
		dst->remote_dev = remote_dev;
	वापस 0;
unlink:
	अगर (remote_dev)
		netdev_upper_dev_unlink(remote_dev, dev);
errout:
	/* unरेजिस्टर_netdevice() destroys the शेष FDB entry with deletion
	 * notअगरication. But the addition notअगरication was not sent yet, so
	 * destroy the entry by hand here.
	 */
	अगर (f)
		__vxlan_fdb_मुक्त(f);
unरेजिस्टर:
	अगर (unरेजिस्टर)
		unरेजिस्टर_netdevice(dev);
	वापस err;
पूर्ण

/* Set/clear flags based on attribute */
अटल पूर्णांक vxlan_nl2flag(काष्ठा vxlan_config *conf, काष्ठा nlattr *tb[],
			  पूर्णांक attrtype, अचिन्हित दीर्घ mask, bool changelink,
			  bool changelink_supported,
			  काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!tb[attrtype])
		वापस 0;

	अगर (changelink && !changelink_supported) अणु
		vxlan_flag_attr_error(attrtype, extack);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vxlan_policy[attrtype].type == NLA_FLAG)
		flags = conf->flags | mask;
	अन्यथा अगर (nla_get_u8(tb[attrtype]))
		flags = conf->flags | mask;
	अन्यथा
		flags = conf->flags & ~mask;

	conf->flags = flags;

	वापस 0;
पूर्ण

अटल पूर्णांक vxlan_nl2conf(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा net_device *dev, काष्ठा vxlan_config *conf,
			 bool changelink, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	पूर्णांक err = 0;

	स_रखो(conf, 0, माप(*conf));

	/* अगर changelink operation, start with old existing cfg */
	अगर (changelink)
		स_नकल(conf, &vxlan->cfg, माप(*conf));

	अगर (data[IFLA_VXLAN_ID]) अणु
		__be32 vni = cpu_to_be32(nla_get_u32(data[IFLA_VXLAN_ID]));

		अगर (changelink && (vni != conf->vni)) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_ID], "Cannot change VNI");
			वापस -EOPNOTSUPP;
		पूर्ण
		conf->vni = cpu_to_be32(nla_get_u32(data[IFLA_VXLAN_ID]));
	पूर्ण

	अगर (data[IFLA_VXLAN_GROUP]) अणु
		अगर (changelink && (conf->remote_ip.sa.sa_family != AF_INET)) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_GROUP], "New group address family does not match old group");
			वापस -EOPNOTSUPP;
		पूर्ण

		conf->remote_ip.sin.sin_addr.s_addr = nla_get_in_addr(data[IFLA_VXLAN_GROUP]);
		conf->remote_ip.sa.sa_family = AF_INET;
	पूर्ण अन्यथा अगर (data[IFLA_VXLAN_GROUP6]) अणु
		अगर (!IS_ENABLED(CONFIG_IPV6)) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_GROUP6], "IPv6 support not enabled in the kernel");
			वापस -EPFNOSUPPORT;
		पूर्ण

		अगर (changelink && (conf->remote_ip.sa.sa_family != AF_INET6)) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_GROUP6], "New group address family does not match old group");
			वापस -EOPNOTSUPP;
		पूर्ण

		conf->remote_ip.sin6.sin6_addr = nla_get_in6_addr(data[IFLA_VXLAN_GROUP6]);
		conf->remote_ip.sa.sa_family = AF_INET6;
	पूर्ण

	अगर (data[IFLA_VXLAN_LOCAL]) अणु
		अगर (changelink && (conf->saddr.sa.sa_family != AF_INET)) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_LOCAL], "New local address family does not match old");
			वापस -EOPNOTSUPP;
		पूर्ण

		conf->saddr.sin.sin_addr.s_addr = nla_get_in_addr(data[IFLA_VXLAN_LOCAL]);
		conf->saddr.sa.sa_family = AF_INET;
	पूर्ण अन्यथा अगर (data[IFLA_VXLAN_LOCAL6]) अणु
		अगर (!IS_ENABLED(CONFIG_IPV6)) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_LOCAL6], "IPv6 support not enabled in the kernel");
			वापस -EPFNOSUPPORT;
		पूर्ण

		अगर (changelink && (conf->saddr.sa.sa_family != AF_INET6)) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_LOCAL6], "New local address family does not match old");
			वापस -EOPNOTSUPP;
		पूर्ण

		/* TODO: respect scope id */
		conf->saddr.sin6.sin6_addr = nla_get_in6_addr(data[IFLA_VXLAN_LOCAL6]);
		conf->saddr.sa.sa_family = AF_INET6;
	पूर्ण

	अगर (data[IFLA_VXLAN_LINK])
		conf->remote_अगरindex = nla_get_u32(data[IFLA_VXLAN_LINK]);

	अगर (data[IFLA_VXLAN_TOS])
		conf->tos  = nla_get_u8(data[IFLA_VXLAN_TOS]);

	अगर (data[IFLA_VXLAN_TTL])
		conf->ttl = nla_get_u8(data[IFLA_VXLAN_TTL]);

	अगर (data[IFLA_VXLAN_TTL_INHERIT]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_TTL_INHERIT,
				    VXLAN_F_TTL_INHERIT, changelink, false,
				    extack);
		अगर (err)
			वापस err;

	पूर्ण

	अगर (data[IFLA_VXLAN_LABEL])
		conf->label = nla_get_be32(data[IFLA_VXLAN_LABEL]) &
			     IPV6_FLOWLABEL_MASK;

	अगर (data[IFLA_VXLAN_LEARNING]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_LEARNING,
				    VXLAN_F_LEARN, changelink, true,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (!changelink) अणु
		/* शेष to learn on a new device */
		conf->flags |= VXLAN_F_LEARN;
	पूर्ण

	अगर (data[IFLA_VXLAN_AGEING])
		conf->age_पूर्णांकerval = nla_get_u32(data[IFLA_VXLAN_AGEING]);

	अगर (data[IFLA_VXLAN_PROXY]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_PROXY,
				    VXLAN_F_PROXY, changelink, false,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_RSC]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_RSC,
				    VXLAN_F_RSC, changelink, false,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_L2MISS]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_L2MISS,
				    VXLAN_F_L2MISS, changelink, false,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_L3MISS]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_L3MISS,
				    VXLAN_F_L3MISS, changelink, false,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_LIMIT]) अणु
		अगर (changelink) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_LIMIT],
					    "Cannot change limit");
			वापस -EOPNOTSUPP;
		पूर्ण
		conf->addrmax = nla_get_u32(data[IFLA_VXLAN_LIMIT]);
	पूर्ण

	अगर (data[IFLA_VXLAN_COLLECT_METADATA]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_COLLECT_METADATA,
				    VXLAN_F_COLLECT_METADATA, changelink, false,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_PORT_RANGE]) अणु
		अगर (!changelink) अणु
			स्थिर काष्ठा अगरla_vxlan_port_range *p
				= nla_data(data[IFLA_VXLAN_PORT_RANGE]);
			conf->port_min = ntohs(p->low);
			conf->port_max = ntohs(p->high);
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_PORT_RANGE],
					    "Cannot change port range");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (data[IFLA_VXLAN_PORT]) अणु
		अगर (changelink) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_PORT],
					    "Cannot change port");
			वापस -EOPNOTSUPP;
		पूर्ण
		conf->dst_port = nla_get_be16(data[IFLA_VXLAN_PORT]);
	पूर्ण

	अगर (data[IFLA_VXLAN_UDP_CSUM]) अणु
		अगर (changelink) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_UDP_CSUM],
					    "Cannot change UDP_CSUM flag");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (!nla_get_u8(data[IFLA_VXLAN_UDP_CSUM]))
			conf->flags |= VXLAN_F_UDP_ZERO_CSUM_TX;
	पूर्ण

	अगर (data[IFLA_VXLAN_UDP_ZERO_CSUM6_TX]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_UDP_ZERO_CSUM6_TX,
				    VXLAN_F_UDP_ZERO_CSUM6_TX, changelink,
				    false, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_UDP_ZERO_CSUM6_RX]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_UDP_ZERO_CSUM6_RX,
				    VXLAN_F_UDP_ZERO_CSUM6_RX, changelink,
				    false, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_REMCSUM_TX]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_REMCSUM_TX,
				    VXLAN_F_REMCSUM_TX, changelink, false,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_REMCSUM_RX]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_REMCSUM_RX,
				    VXLAN_F_REMCSUM_RX, changelink, false,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_GBP]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_GBP,
				    VXLAN_F_GBP, changelink, false, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_GPE]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_GPE,
				    VXLAN_F_GPE, changelink, false,
				    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_VXLAN_REMCSUM_NOPARTIAL]) अणु
		err = vxlan_nl2flag(conf, data, IFLA_VXLAN_REMCSUM_NOPARTIAL,
				    VXLAN_F_REMCSUM_NOPARTIAL, changelink,
				    false, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_MTU]) अणु
		अगर (changelink) अणु
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_MTU],
					    "Cannot change mtu");
			वापस -EOPNOTSUPP;
		पूर्ण
		conf->mtu = nla_get_u32(tb[IFLA_MTU]);
	पूर्ण

	अगर (data[IFLA_VXLAN_DF])
		conf->df = nla_get_u8(data[IFLA_VXLAN_DF]);

	वापस 0;
पूर्ण

अटल पूर्णांक vxlan_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			 काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_config conf;
	पूर्णांक err;

	err = vxlan_nl2conf(tb, data, dev, &conf, false, extack);
	अगर (err)
		वापस err;

	वापस __vxlan_dev_create(src_net, dev, &conf, extack);
पूर्ण

अटल पूर्णांक vxlan_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			    काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा net_device *lowerdev;
	काष्ठा vxlan_config conf;
	काष्ठा vxlan_rdst *dst;
	पूर्णांक err;

	dst = &vxlan->शेष_dst;
	err = vxlan_nl2conf(tb, data, dev, &conf, true, extack);
	अगर (err)
		वापस err;

	err = vxlan_config_validate(vxlan->net, &conf, &lowerdev,
				    vxlan, extack);
	अगर (err)
		वापस err;

	अगर (dst->remote_dev == lowerdev)
		lowerdev = शून्य;

	err = netdev_adjacent_change_prepare(dst->remote_dev, lowerdev, dev,
					     extack);
	अगर (err)
		वापस err;

	/* handle शेष dst entry */
	अगर (!vxlan_addr_equal(&conf.remote_ip, &dst->remote_ip)) अणु
		u32 hash_index = fdb_head_index(vxlan, all_zeros_mac, conf.vni);

		spin_lock_bh(&vxlan->hash_lock[hash_index]);
		अगर (!vxlan_addr_any(&conf.remote_ip)) अणु
			err = vxlan_fdb_update(vxlan, all_zeros_mac,
					       &conf.remote_ip,
					       NUD_REACHABLE | NUD_PERMANENT,
					       NLM_F_APPEND | NLM_F_CREATE,
					       vxlan->cfg.dst_port,
					       conf.vni, conf.vni,
					       conf.remote_अगरindex,
					       NTF_SELF, 0, true, extack);
			अगर (err) अणु
				spin_unlock_bh(&vxlan->hash_lock[hash_index]);
				netdev_adjacent_change_पात(dst->remote_dev,
							     lowerdev, dev);
				वापस err;
			पूर्ण
		पूर्ण
		अगर (!vxlan_addr_any(&dst->remote_ip))
			__vxlan_fdb_delete(vxlan, all_zeros_mac,
					   dst->remote_ip,
					   vxlan->cfg.dst_port,
					   dst->remote_vni,
					   dst->remote_vni,
					   dst->remote_अगरindex,
					   true);
		spin_unlock_bh(&vxlan->hash_lock[hash_index]);
	पूर्ण

	अगर (conf.age_पूर्णांकerval != vxlan->cfg.age_पूर्णांकerval)
		mod_समयr(&vxlan->age_समयr, jअगरfies);

	netdev_adjacent_change_commit(dst->remote_dev, lowerdev, dev);
	अगर (lowerdev && lowerdev != dst->remote_dev)
		dst->remote_dev = lowerdev;
	vxlan_config_apply(dev, &conf, lowerdev, vxlan->net, true);
	वापस 0;
पूर्ण

अटल व्योम vxlan_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);

	vxlan_flush(vxlan, true);

	list_del(&vxlan->next);
	unरेजिस्टर_netdevice_queue(dev, head);
	अगर (vxlan->शेष_dst.remote_dev)
		netdev_upper_dev_unlink(vxlan->शेष_dst.remote_dev, dev);
पूर्ण

अटल माप_प्रकार vxlan_get_size(स्थिर काष्ठा net_device *dev)
अणु

	वापस nla_total_size(माप(__u32)) +	/* IFLA_VXLAN_ID */
		nla_total_size(माप(काष्ठा in6_addr)) + /* IFLA_VXLAN_GROUPअणु6पूर्ण */
		nla_total_size(माप(__u32)) +	/* IFLA_VXLAN_LINK */
		nla_total_size(माप(काष्ठा in6_addr)) + /* IFLA_VXLAN_LOCALअणु6पूर्ण */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_TTL */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_TTL_INHERIT */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_TOS */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_DF */
		nla_total_size(माप(__be32)) + /* IFLA_VXLAN_LABEL */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_LEARNING */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_PROXY */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_RSC */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_L2MISS */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_L3MISS */
		nla_total_size(माप(__u8)) +	/* IFLA_VXLAN_COLLECT_METADATA */
		nla_total_size(माप(__u32)) +	/* IFLA_VXLAN_AGEING */
		nla_total_size(माप(__u32)) +	/* IFLA_VXLAN_LIMIT */
		nla_total_size(माप(काष्ठा अगरla_vxlan_port_range)) +
		nla_total_size(माप(__be16)) + /* IFLA_VXLAN_PORT */
		nla_total_size(माप(__u8)) + /* IFLA_VXLAN_UDP_CSUM */
		nla_total_size(माप(__u8)) + /* IFLA_VXLAN_UDP_ZERO_CSUM6_TX */
		nla_total_size(माप(__u8)) + /* IFLA_VXLAN_UDP_ZERO_CSUM6_RX */
		nla_total_size(माप(__u8)) + /* IFLA_VXLAN_REMCSUM_TX */
		nla_total_size(माप(__u8)) + /* IFLA_VXLAN_REMCSUM_RX */
		0;
पूर्ण

अटल पूर्णांक vxlan_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	स्थिर काष्ठा vxlan_rdst *dst = &vxlan->शेष_dst;
	काष्ठा अगरla_vxlan_port_range ports = अणु
		.low =  htons(vxlan->cfg.port_min),
		.high = htons(vxlan->cfg.port_max),
	पूर्ण;

	अगर (nla_put_u32(skb, IFLA_VXLAN_ID, be32_to_cpu(dst->remote_vni)))
		जाओ nla_put_failure;

	अगर (!vxlan_addr_any(&dst->remote_ip)) अणु
		अगर (dst->remote_ip.sa.sa_family == AF_INET) अणु
			अगर (nla_put_in_addr(skb, IFLA_VXLAN_GROUP,
					    dst->remote_ip.sin.sin_addr.s_addr))
				जाओ nla_put_failure;
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्ण अन्यथा अणु
			अगर (nla_put_in6_addr(skb, IFLA_VXLAN_GROUP6,
					     &dst->remote_ip.sin6.sin6_addr))
				जाओ nla_put_failure;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	अगर (dst->remote_अगरindex && nla_put_u32(skb, IFLA_VXLAN_LINK, dst->remote_अगरindex))
		जाओ nla_put_failure;

	अगर (!vxlan_addr_any(&vxlan->cfg.saddr)) अणु
		अगर (vxlan->cfg.saddr.sa.sa_family == AF_INET) अणु
			अगर (nla_put_in_addr(skb, IFLA_VXLAN_LOCAL,
					    vxlan->cfg.saddr.sin.sin_addr.s_addr))
				जाओ nla_put_failure;
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्ण अन्यथा अणु
			अगर (nla_put_in6_addr(skb, IFLA_VXLAN_LOCAL6,
					     &vxlan->cfg.saddr.sin6.sin6_addr))
				जाओ nla_put_failure;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	अगर (nla_put_u8(skb, IFLA_VXLAN_TTL, vxlan->cfg.ttl) ||
	    nla_put_u8(skb, IFLA_VXLAN_TTL_INHERIT,
		       !!(vxlan->cfg.flags & VXLAN_F_TTL_INHERIT)) ||
	    nla_put_u8(skb, IFLA_VXLAN_TOS, vxlan->cfg.tos) ||
	    nla_put_u8(skb, IFLA_VXLAN_DF, vxlan->cfg.df) ||
	    nla_put_be32(skb, IFLA_VXLAN_LABEL, vxlan->cfg.label) ||
	    nla_put_u8(skb, IFLA_VXLAN_LEARNING,
		       !!(vxlan->cfg.flags & VXLAN_F_LEARN)) ||
	    nla_put_u8(skb, IFLA_VXLAN_PROXY,
		       !!(vxlan->cfg.flags & VXLAN_F_PROXY)) ||
	    nla_put_u8(skb, IFLA_VXLAN_RSC,
		       !!(vxlan->cfg.flags & VXLAN_F_RSC)) ||
	    nla_put_u8(skb, IFLA_VXLAN_L2MISS,
		       !!(vxlan->cfg.flags & VXLAN_F_L2MISS)) ||
	    nla_put_u8(skb, IFLA_VXLAN_L3MISS,
		       !!(vxlan->cfg.flags & VXLAN_F_L3MISS)) ||
	    nla_put_u8(skb, IFLA_VXLAN_COLLECT_METADATA,
		       !!(vxlan->cfg.flags & VXLAN_F_COLLECT_METADATA)) ||
	    nla_put_u32(skb, IFLA_VXLAN_AGEING, vxlan->cfg.age_पूर्णांकerval) ||
	    nla_put_u32(skb, IFLA_VXLAN_LIMIT, vxlan->cfg.addrmax) ||
	    nla_put_be16(skb, IFLA_VXLAN_PORT, vxlan->cfg.dst_port) ||
	    nla_put_u8(skb, IFLA_VXLAN_UDP_CSUM,
		       !(vxlan->cfg.flags & VXLAN_F_UDP_ZERO_CSUM_TX)) ||
	    nla_put_u8(skb, IFLA_VXLAN_UDP_ZERO_CSUM6_TX,
		       !!(vxlan->cfg.flags & VXLAN_F_UDP_ZERO_CSUM6_TX)) ||
	    nla_put_u8(skb, IFLA_VXLAN_UDP_ZERO_CSUM6_RX,
		       !!(vxlan->cfg.flags & VXLAN_F_UDP_ZERO_CSUM6_RX)) ||
	    nla_put_u8(skb, IFLA_VXLAN_REMCSUM_TX,
		       !!(vxlan->cfg.flags & VXLAN_F_REMCSUM_TX)) ||
	    nla_put_u8(skb, IFLA_VXLAN_REMCSUM_RX,
		       !!(vxlan->cfg.flags & VXLAN_F_REMCSUM_RX)))
		जाओ nla_put_failure;

	अगर (nla_put(skb, IFLA_VXLAN_PORT_RANGE, माप(ports), &ports))
		जाओ nla_put_failure;

	अगर (vxlan->cfg.flags & VXLAN_F_GBP &&
	    nla_put_flag(skb, IFLA_VXLAN_GBP))
		जाओ nla_put_failure;

	अगर (vxlan->cfg.flags & VXLAN_F_GPE &&
	    nla_put_flag(skb, IFLA_VXLAN_GPE))
		जाओ nla_put_failure;

	अगर (vxlan->cfg.flags & VXLAN_F_REMCSUM_NOPARTIAL &&
	    nla_put_flag(skb, IFLA_VXLAN_REMCSUM_NOPARTIAL))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा net *vxlan_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);

	वापस vxlan->net;
पूर्ण

अटल काष्ठा rtnl_link_ops vxlan_link_ops __पढ़ो_mostly = अणु
	.kind		= "vxlan",
	.maxtype	= IFLA_VXLAN_MAX,
	.policy		= vxlan_policy,
	.priv_size	= माप(काष्ठा vxlan_dev),
	.setup		= vxlan_setup,
	.validate	= vxlan_validate,
	.newlink	= vxlan_newlink,
	.changelink	= vxlan_changelink,
	.dellink	= vxlan_dellink,
	.get_size	= vxlan_get_size,
	.fill_info	= vxlan_fill_info,
	.get_link_net	= vxlan_get_link_net,
पूर्ण;

काष्ठा net_device *vxlan_dev_create(काष्ठा net *net, स्थिर अक्षर *name,
				    u8 name_assign_type,
				    काष्ठा vxlan_config *conf)
अणु
	काष्ठा nlattr *tb[IFLA_MAX + 1];
	काष्ठा net_device *dev;
	पूर्णांक err;

	स_रखो(&tb, 0, माप(tb));

	dev = rtnl_create_link(net, name, name_assign_type,
			       &vxlan_link_ops, tb, शून्य);
	अगर (IS_ERR(dev))
		वापस dev;

	err = __vxlan_dev_create(net, dev, conf, शून्य);
	अगर (err < 0) अणु
		मुक्त_netdev(dev);
		वापस ERR_PTR(err);
	पूर्ण

	err = rtnl_configure_link(dev, शून्य);
	अगर (err < 0) अणु
		LIST_HEAD(list_समाप्त);

		vxlan_dellink(dev, &list_समाप्त);
		unरेजिस्टर_netdevice_many(&list_समाप्त);
		वापस ERR_PTR(err);
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(vxlan_dev_create);

अटल व्योम vxlan_handle_lowerdev_unरेजिस्टर(काष्ठा vxlan_net *vn,
					     काष्ठा net_device *dev)
अणु
	काष्ठा vxlan_dev *vxlan, *next;
	LIST_HEAD(list_समाप्त);

	list_क्रम_each_entry_safe(vxlan, next, &vn->vxlan_list, next) अणु
		काष्ठा vxlan_rdst *dst = &vxlan->शेष_dst;

		/* In हाल we created vxlan device with carrier
		 * and we loose the carrier due to module unload
		 * we also need to हटाओ vxlan device. In other
		 * हालs, it's not necessary and remote_अगरindex
		 * is 0 here, so no matches.
		 */
		अगर (dst->remote_अगरindex == dev->अगरindex)
			vxlan_dellink(vxlan->dev, &list_समाप्त);
	पूर्ण

	unरेजिस्टर_netdevice_many(&list_समाप्त);
पूर्ण

अटल पूर्णांक vxlan_netdevice_event(काष्ठा notअगरier_block *unused,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा vxlan_net *vn = net_generic(dev_net(dev), vxlan_net_id);

	अगर (event == NETDEV_UNREGISTER)
		vxlan_handle_lowerdev_unरेजिस्टर(vn, dev);
	अन्यथा अगर (event == NETDEV_UDP_TUNNEL_PUSH_INFO)
		vxlan_offload_rx_ports(dev, true);
	अन्यथा अगर (event == NETDEV_UDP_TUNNEL_DROP_INFO)
		vxlan_offload_rx_ports(dev, false);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block vxlan_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = vxlan_netdevice_event,
पूर्ण;

अटल व्योम
vxlan_fdb_offloaded_set(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_vxlan_fdb_info *fdb_info)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_rdst *rdst;
	काष्ठा vxlan_fdb *f;
	u32 hash_index;

	hash_index = fdb_head_index(vxlan, fdb_info->eth_addr, fdb_info->vni);

	spin_lock_bh(&vxlan->hash_lock[hash_index]);

	f = vxlan_find_mac(vxlan, fdb_info->eth_addr, fdb_info->vni);
	अगर (!f)
		जाओ out;

	rdst = vxlan_fdb_find_rdst(f, &fdb_info->remote_ip,
				   fdb_info->remote_port,
				   fdb_info->remote_vni,
				   fdb_info->remote_अगरindex);
	अगर (!rdst)
		जाओ out;

	rdst->offloaded = fdb_info->offloaded;

out:
	spin_unlock_bh(&vxlan->hash_lock[hash_index]);
पूर्ण

अटल पूर्णांक
vxlan_fdb_बाह्यal_learn_add(काष्ठा net_device *dev,
			     काष्ठा चयनdev_notअगरier_vxlan_fdb_info *fdb_info)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा netlink_ext_ack *extack;
	u32 hash_index;
	पूर्णांक err;

	hash_index = fdb_head_index(vxlan, fdb_info->eth_addr, fdb_info->vni);
	extack = चयनdev_notअगरier_info_to_extack(&fdb_info->info);

	spin_lock_bh(&vxlan->hash_lock[hash_index]);
	err = vxlan_fdb_update(vxlan, fdb_info->eth_addr, &fdb_info->remote_ip,
			       NUD_REACHABLE,
			       NLM_F_CREATE | NLM_F_REPLACE,
			       fdb_info->remote_port,
			       fdb_info->vni,
			       fdb_info->remote_vni,
			       fdb_info->remote_अगरindex,
			       NTF_USE | NTF_SELF | NTF_EXT_LEARNED,
			       0, false, extack);
	spin_unlock_bh(&vxlan->hash_lock[hash_index]);

	वापस err;
पूर्ण

अटल पूर्णांक
vxlan_fdb_बाह्यal_learn_del(काष्ठा net_device *dev,
			     काष्ठा चयनdev_notअगरier_vxlan_fdb_info *fdb_info)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	काष्ठा vxlan_fdb *f;
	u32 hash_index;
	पूर्णांक err = 0;

	hash_index = fdb_head_index(vxlan, fdb_info->eth_addr, fdb_info->vni);
	spin_lock_bh(&vxlan->hash_lock[hash_index]);

	f = vxlan_find_mac(vxlan, fdb_info->eth_addr, fdb_info->vni);
	अगर (!f)
		err = -ENOENT;
	अन्यथा अगर (f->flags & NTF_EXT_LEARNED)
		err = __vxlan_fdb_delete(vxlan, fdb_info->eth_addr,
					 fdb_info->remote_ip,
					 fdb_info->remote_port,
					 fdb_info->vni,
					 fdb_info->remote_vni,
					 fdb_info->remote_अगरindex,
					 false);

	spin_unlock_bh(&vxlan->hash_lock[hash_index]);

	वापस err;
पूर्ण

अटल पूर्णांक vxlan_चयनdev_event(काष्ठा notअगरier_block *unused,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	काष्ठा चयनdev_notअगरier_vxlan_fdb_info *fdb_info;
	पूर्णांक err = 0;

	चयन (event) अणु
	हाल SWITCHDEV_VXLAN_FDB_OFFLOADED:
		vxlan_fdb_offloaded_set(dev, ptr);
		अवरोध;
	हाल SWITCHDEV_VXLAN_FDB_ADD_TO_BRIDGE:
		fdb_info = ptr;
		err = vxlan_fdb_बाह्यal_learn_add(dev, fdb_info);
		अगर (err) अणु
			err = notअगरier_from_त्रुटि_सं(err);
			अवरोध;
		पूर्ण
		fdb_info->offloaded = true;
		vxlan_fdb_offloaded_set(dev, fdb_info);
		अवरोध;
	हाल SWITCHDEV_VXLAN_FDB_DEL_TO_BRIDGE:
		fdb_info = ptr;
		err = vxlan_fdb_बाह्यal_learn_del(dev, fdb_info);
		अगर (err) अणु
			err = notअगरier_from_त्रुटि_सं(err);
			अवरोध;
		पूर्ण
		fdb_info->offloaded = false;
		vxlan_fdb_offloaded_set(dev, fdb_info);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा notअगरier_block vxlan_चयनdev_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = vxlan_चयनdev_event,
पूर्ण;

अटल व्योम vxlan_fdb_nh_flush(काष्ठा nexthop *nh)
अणु
	काष्ठा vxlan_fdb *fdb;
	काष्ठा vxlan_dev *vxlan;
	u32 hash_index;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(fdb, &nh->fdb_list, nh_list) अणु
		vxlan = rcu_dereference(fdb->vdev);
		WARN_ON(!vxlan);
		hash_index = fdb_head_index(vxlan, fdb->eth_addr,
					    vxlan->शेष_dst.remote_vni);
		spin_lock_bh(&vxlan->hash_lock[hash_index]);
		अगर (!hlist_unhashed(&fdb->hlist))
			vxlan_fdb_destroy(vxlan, fdb, false, false);
		spin_unlock_bh(&vxlan->hash_lock[hash_index]);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक vxlan_nexthop_event(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा nh_notअगरier_info *info = ptr;
	काष्ठा nexthop *nh;

	अगर (event != NEXTHOP_EVENT_DEL)
		वापस NOTIFY_DONE;

	nh = nexthop_find_by_id(info->net, info->id);
	अगर (!nh)
		वापस NOTIFY_DONE;

	vxlan_fdb_nh_flush(nh);

	वापस NOTIFY_DONE;
पूर्ण

अटल __net_init पूर्णांक vxlan_init_net(काष्ठा net *net)
अणु
	काष्ठा vxlan_net *vn = net_generic(net, vxlan_net_id);
	अचिन्हित पूर्णांक h;

	INIT_LIST_HEAD(&vn->vxlan_list);
	spin_lock_init(&vn->sock_lock);
	vn->nexthop_notअगरier_block.notअगरier_call = vxlan_nexthop_event;

	क्रम (h = 0; h < PORT_HASH_SIZE; ++h)
		INIT_HLIST_HEAD(&vn->sock_list[h]);

	वापस रेजिस्टर_nexthop_notअगरier(net, &vn->nexthop_notअगरier_block,
					 शून्य);
पूर्ण

अटल व्योम vxlan_destroy_tunnels(काष्ठा net *net, काष्ठा list_head *head)
अणु
	काष्ठा vxlan_net *vn = net_generic(net, vxlan_net_id);
	काष्ठा vxlan_dev *vxlan, *next;
	काष्ठा net_device *dev, *aux;

	क्रम_each_netdev_safe(net, dev, aux)
		अगर (dev->rtnl_link_ops == &vxlan_link_ops)
			unरेजिस्टर_netdevice_queue(dev, head);

	list_क्रम_each_entry_safe(vxlan, next, &vn->vxlan_list, next) अणु
		/* If vxlan->dev is in the same netns, it has alपढ़ोy been added
		 * to the list by the previous loop.
		 */
		अगर (!net_eq(dev_net(vxlan->dev), net))
			unरेजिस्टर_netdevice_queue(vxlan->dev, head);
	पूर्ण

पूर्ण

अटल व्योम __net_निकास vxlan_निकास_batch_net(काष्ठा list_head *net_list)
अणु
	काष्ठा net *net;
	LIST_HEAD(list);
	अचिन्हित पूर्णांक h;

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		काष्ठा vxlan_net *vn = net_generic(net, vxlan_net_id);

		unरेजिस्टर_nexthop_notअगरier(net, &vn->nexthop_notअगरier_block);
	पूर्ण
	list_क्रम_each_entry(net, net_list, निकास_list)
		vxlan_destroy_tunnels(net, &list);

	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();

	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		काष्ठा vxlan_net *vn = net_generic(net, vxlan_net_id);

		क्रम (h = 0; h < PORT_HASH_SIZE; ++h)
			WARN_ON_ONCE(!hlist_empty(&vn->sock_list[h]));
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations vxlan_net_ops = अणु
	.init = vxlan_init_net,
	.निकास_batch = vxlan_निकास_batch_net,
	.id   = &vxlan_net_id,
	.size = माप(काष्ठा vxlan_net),
पूर्ण;

अटल पूर्णांक __init vxlan_init_module(व्योम)
अणु
	पूर्णांक rc;

	get_अक्रमom_bytes(&vxlan_salt, माप(vxlan_salt));

	rc = रेजिस्टर_pernet_subsys(&vxlan_net_ops);
	अगर (rc)
		जाओ out1;

	rc = रेजिस्टर_netdevice_notअगरier(&vxlan_notअगरier_block);
	अगर (rc)
		जाओ out2;

	rc = रेजिस्टर_चयनdev_notअगरier(&vxlan_चयनdev_notअगरier_block);
	अगर (rc)
		जाओ out3;

	rc = rtnl_link_रेजिस्टर(&vxlan_link_ops);
	अगर (rc)
		जाओ out4;

	वापस 0;
out4:
	unरेजिस्टर_चयनdev_notअगरier(&vxlan_चयनdev_notअगरier_block);
out3:
	unरेजिस्टर_netdevice_notअगरier(&vxlan_notअगरier_block);
out2:
	unरेजिस्टर_pernet_subsys(&vxlan_net_ops);
out1:
	वापस rc;
पूर्ण
late_initcall(vxlan_init_module);

अटल व्योम __निकास vxlan_cleanup_module(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&vxlan_link_ops);
	unरेजिस्टर_चयनdev_notअगरier(&vxlan_चयनdev_notअगरier_block);
	unरेजिस्टर_netdevice_notअगरier(&vxlan_notअगरier_block);
	unरेजिस्टर_pernet_subsys(&vxlan_net_ops);
	/* rcu_barrier() is called by netns */
पूर्ण
module_निकास(vxlan_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_VERSION(VXLAN_VERSION);
MODULE_AUTHOR("Stephen Hemminger <stephen@networkplumber.org>");
MODULE_DESCRIPTION("Driver for VXLAN encapsulated traffic");
MODULE_ALIAS_RTNL_LINK("vxlan");

<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/etherdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/netevent.h>
#समावेश <linux/idr.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/arp.h>

#समावेश "cmsg.h"
#समावेश "main.h"
#समावेश "../nfp_net_repr.h"
#समावेश "../nfp_net.h"

#घोषणा NFP_FL_MAX_ROUTES               32

#घोषणा NFP_TUN_PRE_TUN_RULE_LIMIT	32
#घोषणा NFP_TUN_PRE_TUN_RULE_DEL	BIT(0)
#घोषणा NFP_TUN_PRE_TUN_IDX_BIT		BIT(3)
#घोषणा NFP_TUN_PRE_TUN_IPV6_BIT	BIT(7)

/**
 * काष्ठा nfp_tun_pre_run_rule - rule matched beक्रमe decap
 * @flags:		options क्रम the rule offset
 * @port_idx:		index of destination MAC address क्रम the rule
 * @vlan_tci:		VLAN info associated with MAC
 * @host_ctx_id:	stats context of rule to update
 */
काष्ठा nfp_tun_pre_tun_rule अणु
	__be32 flags;
	__be16 port_idx;
	__be16 vlan_tci;
	__be32 host_ctx_id;
पूर्ण;

/**
 * काष्ठा nfp_tun_active_tuns - periodic message of active tunnels
 * @seq:		sequence number of the message
 * @count:		number of tunnels report in message
 * @flags:		options part of the request
 * @tun_info.ipv4:		dest IPv4 address of active route
 * @tun_info.egress_port:	port the encapsulated packet egressed
 * @tun_info.extra:		reserved क्रम future use
 * @tun_info:		tunnels that have sent traffic in reported period
 */
काष्ठा nfp_tun_active_tuns अणु
	__be32 seq;
	__be32 count;
	__be32 flags;
	काष्ठा route_ip_info अणु
		__be32 ipv4;
		__be32 egress_port;
		__be32 extra[2];
	पूर्ण tun_info[];
पूर्ण;

/**
 * काष्ठा nfp_tun_active_tuns_v6 - periodic message of active IPv6 tunnels
 * @seq:		sequence number of the message
 * @count:		number of tunnels report in message
 * @flags:		options part of the request
 * @tun_info.ipv6:		dest IPv6 address of active route
 * @tun_info.egress_port:	port the encapsulated packet egressed
 * @tun_info.extra:		reserved क्रम future use
 * @tun_info:		tunnels that have sent traffic in reported period
 */
काष्ठा nfp_tun_active_tuns_v6 अणु
	__be32 seq;
	__be32 count;
	__be32 flags;
	काष्ठा route_ip_info_v6 अणु
		काष्ठा in6_addr ipv6;
		__be32 egress_port;
		__be32 extra[2];
	पूर्ण tun_info[];
पूर्ण;

/**
 * काष्ठा nfp_tun_neigh - neighbour/route entry on the NFP
 * @dst_ipv4:	destination IPv4 address
 * @src_ipv4:	source IPv4 address
 * @dst_addr:	destination MAC address
 * @src_addr:	source MAC address
 * @port_id:	NFP port to output packet on - associated with source IPv4
 */
काष्ठा nfp_tun_neigh अणु
	__be32 dst_ipv4;
	__be32 src_ipv4;
	u8 dst_addr[ETH_ALEN];
	u8 src_addr[ETH_ALEN];
	__be32 port_id;
पूर्ण;

/**
 * काष्ठा nfp_tun_neigh_v6 - neighbour/route entry on the NFP
 * @dst_ipv6:	destination IPv6 address
 * @src_ipv6:	source IPv6 address
 * @dst_addr:	destination MAC address
 * @src_addr:	source MAC address
 * @port_id:	NFP port to output packet on - associated with source IPv6
 */
काष्ठा nfp_tun_neigh_v6 अणु
	काष्ठा in6_addr dst_ipv6;
	काष्ठा in6_addr src_ipv6;
	u8 dst_addr[ETH_ALEN];
	u8 src_addr[ETH_ALEN];
	__be32 port_id;
पूर्ण;

/**
 * काष्ठा nfp_tun_req_route_ipv4 - NFP requests a route/neighbour lookup
 * @ingress_port:	ingress port of packet that संकेतled request
 * @ipv4_addr:		destination ipv4 address क्रम route
 * @reserved:		reserved क्रम future use
 */
काष्ठा nfp_tun_req_route_ipv4 अणु
	__be32 ingress_port;
	__be32 ipv4_addr;
	__be32 reserved[2];
पूर्ण;

/**
 * काष्ठा nfp_tun_req_route_ipv6 - NFP requests an IPv6 route/neighbour lookup
 * @ingress_port:	ingress port of packet that संकेतled request
 * @ipv6_addr:		destination ipv6 address क्रम route
 */
काष्ठा nfp_tun_req_route_ipv6 अणु
	__be32 ingress_port;
	काष्ठा in6_addr ipv6_addr;
पूर्ण;

/**
 * काष्ठा nfp_offloaded_route - routes that are offloaded to the NFP
 * @list:	list poपूर्णांकer
 * @ip_add:	destination of route - can be IPv4 or IPv6
 */
काष्ठा nfp_offloaded_route अणु
	काष्ठा list_head list;
	u8 ip_add[];
पूर्ण;

#घोषणा NFP_FL_IPV4_ADDRS_MAX        32

/**
 * काष्ठा nfp_tun_ipv4_addr - set the IP address list on the NFP
 * @count:	number of IPs populated in the array
 * @ipv4_addr:	array of IPV4_ADDRS_MAX 32 bit IPv4 addresses
 */
काष्ठा nfp_tun_ipv4_addr अणु
	__be32 count;
	__be32 ipv4_addr[NFP_FL_IPV4_ADDRS_MAX];
पूर्ण;

/**
 * काष्ठा nfp_ipv4_addr_entry - cached IPv4 addresses
 * @ipv4_addr:	IP address
 * @ref_count:	number of rules currently using this IP
 * @list:	list poपूर्णांकer
 */
काष्ठा nfp_ipv4_addr_entry अणु
	__be32 ipv4_addr;
	पूर्णांक ref_count;
	काष्ठा list_head list;
पूर्ण;

#घोषणा NFP_FL_IPV6_ADDRS_MAX        4

/**
 * काष्ठा nfp_tun_ipv6_addr - set the IP address list on the NFP
 * @count:	number of IPs populated in the array
 * @ipv6_addr:	array of IPV6_ADDRS_MAX 128 bit IPv6 addresses
 */
काष्ठा nfp_tun_ipv6_addr अणु
	__be32 count;
	काष्ठा in6_addr ipv6_addr[NFP_FL_IPV6_ADDRS_MAX];
पूर्ण;

#घोषणा NFP_TUN_MAC_OFFLOAD_DEL_FLAG	0x2

/**
 * काष्ठा nfp_tun_mac_addr_offload - configure MAC address of tunnel EP on NFP
 * @flags:	MAC address offload options
 * @count:	number of MAC addresses in the message (should be 1)
 * @index:	index of MAC address in the lookup table
 * @addr:	पूर्णांकerface MAC address
 */
काष्ठा nfp_tun_mac_addr_offload अणु
	__be16 flags;
	__be16 count;
	__be16 index;
	u8 addr[ETH_ALEN];
पूर्ण;

क्रमागत nfp_flower_mac_offload_cmd अणु
	NFP_TUNNEL_MAC_OFFLOAD_ADD =		0,
	NFP_TUNNEL_MAC_OFFLOAD_DEL =		1,
	NFP_TUNNEL_MAC_OFFLOAD_MOD =		2,
पूर्ण;

#घोषणा NFP_MAX_MAC_INDEX       0xff

/**
 * काष्ठा nfp_tun_offloaded_mac - hashtable entry क्रम an offloaded MAC
 * @ht_node:		Hashtable entry
 * @addr:		Offloaded MAC address
 * @index:		Offloaded index क्रम given MAC address
 * @ref_count:		Number of devs using this MAC address
 * @repr_list:		List of reprs sharing this MAC address
 * @bridge_count:	Number of bridge/पूर्णांकernal devs with MAC
 */
काष्ठा nfp_tun_offloaded_mac अणु
	काष्ठा rhash_head ht_node;
	u8 addr[ETH_ALEN];
	u16 index;
	पूर्णांक ref_count;
	काष्ठा list_head repr_list;
	पूर्णांक bridge_count;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params offloaded_macs_params = अणु
	.key_offset	= दुरत्व(काष्ठा nfp_tun_offloaded_mac, addr),
	.head_offset	= दुरत्व(काष्ठा nfp_tun_offloaded_mac, ht_node),
	.key_len	= ETH_ALEN,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

व्योम nfp_tunnel_keep_alive(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_tun_active_tuns *payload;
	काष्ठा net_device *netdev;
	पूर्णांक count, i, pay_len;
	काष्ठा neighbour *n;
	__be32 ipv4_addr;
	u32 port;

	payload = nfp_flower_cmsg_get_data(skb);
	count = be32_to_cpu(payload->count);
	अगर (count > NFP_FL_MAX_ROUTES) अणु
		nfp_flower_cmsg_warn(app, "Tunnel keep-alive request exceeds max routes.\n");
		वापस;
	पूर्ण

	pay_len = nfp_flower_cmsg_get_data_len(skb);
	अगर (pay_len != काष्ठा_size(payload, tun_info, count)) अणु
		nfp_flower_cmsg_warn(app, "Corruption in tunnel keep-alive message.\n");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < count; i++) अणु
		ipv4_addr = payload->tun_info[i].ipv4;
		port = be32_to_cpu(payload->tun_info[i].egress_port);
		netdev = nfp_app_dev_get(app, port, शून्य);
		अगर (!netdev)
			जारी;

		n = neigh_lookup(&arp_tbl, &ipv4_addr, netdev);
		अगर (!n)
			जारी;

		/* Update the used बारtamp of neighbour */
		neigh_event_send(n, शून्य);
		neigh_release(n);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम nfp_tunnel_keep_alive_v6(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा nfp_tun_active_tuns_v6 *payload;
	काष्ठा net_device *netdev;
	पूर्णांक count, i, pay_len;
	काष्ठा neighbour *n;
	व्योम *ipv6_add;
	u32 port;

	payload = nfp_flower_cmsg_get_data(skb);
	count = be32_to_cpu(payload->count);
	अगर (count > NFP_FL_IPV6_ADDRS_MAX) अणु
		nfp_flower_cmsg_warn(app, "IPv6 tunnel keep-alive request exceeds max routes.\n");
		वापस;
	पूर्ण

	pay_len = nfp_flower_cmsg_get_data_len(skb);
	अगर (pay_len != काष्ठा_size(payload, tun_info, count)) अणु
		nfp_flower_cmsg_warn(app, "Corruption in tunnel keep-alive message.\n");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < count; i++) अणु
		ipv6_add = &payload->tun_info[i].ipv6;
		port = be32_to_cpu(payload->tun_info[i].egress_port);
		netdev = nfp_app_dev_get(app, port, शून्य);
		अगर (!netdev)
			जारी;

		n = neigh_lookup(&nd_tbl, ipv6_add, netdev);
		अगर (!n)
			जारी;

		/* Update the used बारtamp of neighbour */
		neigh_event_send(n, शून्य);
		neigh_release(n);
	पूर्ण
	rcu_पढ़ो_unlock();
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
nfp_flower_xmit_tun_conf(काष्ठा nfp_app *app, u8 mtype, u16 plen, व्योम *pdata,
			 gfp_t flag)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *msg;

	skb = nfp_flower_cmsg_alloc(app, plen, mtype, flag);
	अगर (!skb)
		वापस -ENOMEM;

	msg = nfp_flower_cmsg_get_data(skb);
	स_नकल(msg, pdata, nfp_flower_cmsg_get_data_len(skb));

	nfp_ctrl_tx(app->ctrl, skb);
	वापस 0;
पूर्ण

अटल bool
__nfp_tun_has_route(काष्ठा list_head *route_list, spinlock_t *list_lock,
		    व्योम *add, पूर्णांक add_len)
अणु
	काष्ठा nfp_offloaded_route *entry;

	spin_lock_bh(list_lock);
	list_क्रम_each_entry(entry, route_list, list)
		अगर (!स_भेद(entry->ip_add, add, add_len)) अणु
			spin_unlock_bh(list_lock);
			वापस true;
		पूर्ण
	spin_unlock_bh(list_lock);
	वापस false;
पूर्ण

अटल पूर्णांक
__nfp_tun_add_route_to_cache(काष्ठा list_head *route_list,
			     spinlock_t *list_lock, व्योम *add, पूर्णांक add_len)
अणु
	काष्ठा nfp_offloaded_route *entry;

	spin_lock_bh(list_lock);
	list_क्रम_each_entry(entry, route_list, list)
		अगर (!स_भेद(entry->ip_add, add, add_len)) अणु
			spin_unlock_bh(list_lock);
			वापस 0;
		पूर्ण

	entry = kदो_स्मृति(माप(*entry) + add_len, GFP_ATOMIC);
	अगर (!entry) अणु
		spin_unlock_bh(list_lock);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(entry->ip_add, add, add_len);
	list_add_tail(&entry->list, route_list);
	spin_unlock_bh(list_lock);

	वापस 0;
पूर्ण

अटल व्योम
__nfp_tun_del_route_from_cache(काष्ठा list_head *route_list,
			       spinlock_t *list_lock, व्योम *add, पूर्णांक add_len)
अणु
	काष्ठा nfp_offloaded_route *entry;

	spin_lock_bh(list_lock);
	list_क्रम_each_entry(entry, route_list, list)
		अगर (!स_भेद(entry->ip_add, add, add_len)) अणु
			list_del(&entry->list);
			kमुक्त(entry);
			अवरोध;
		पूर्ण
	spin_unlock_bh(list_lock);
पूर्ण

अटल bool nfp_tun_has_route_v4(काष्ठा nfp_app *app, __be32 *ipv4_addr)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	वापस __nfp_tun_has_route(&priv->tun.neigh_off_list_v4,
				   &priv->tun.neigh_off_lock_v4, ipv4_addr,
				   माप(*ipv4_addr));
पूर्ण

अटल bool
nfp_tun_has_route_v6(काष्ठा nfp_app *app, काष्ठा in6_addr *ipv6_addr)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	वापस __nfp_tun_has_route(&priv->tun.neigh_off_list_v6,
				   &priv->tun.neigh_off_lock_v6, ipv6_addr,
				   माप(*ipv6_addr));
पूर्ण

अटल व्योम
nfp_tun_add_route_to_cache_v4(काष्ठा nfp_app *app, __be32 *ipv4_addr)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	__nfp_tun_add_route_to_cache(&priv->tun.neigh_off_list_v4,
				     &priv->tun.neigh_off_lock_v4, ipv4_addr,
				     माप(*ipv4_addr));
पूर्ण

अटल व्योम
nfp_tun_add_route_to_cache_v6(काष्ठा nfp_app *app, काष्ठा in6_addr *ipv6_addr)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	__nfp_tun_add_route_to_cache(&priv->tun.neigh_off_list_v6,
				     &priv->tun.neigh_off_lock_v6, ipv6_addr,
				     माप(*ipv6_addr));
पूर्ण

अटल व्योम
nfp_tun_del_route_from_cache_v4(काष्ठा nfp_app *app, __be32 *ipv4_addr)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	__nfp_tun_del_route_from_cache(&priv->tun.neigh_off_list_v4,
				       &priv->tun.neigh_off_lock_v4, ipv4_addr,
				       माप(*ipv4_addr));
पूर्ण

अटल व्योम
nfp_tun_del_route_from_cache_v6(काष्ठा nfp_app *app, काष्ठा in6_addr *ipv6_addr)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	__nfp_tun_del_route_from_cache(&priv->tun.neigh_off_list_v6,
				       &priv->tun.neigh_off_lock_v6, ipv6_addr,
				       माप(*ipv6_addr));
पूर्ण

अटल व्योम
nfp_tun_ग_लिखो_neigh_v4(काष्ठा net_device *netdev, काष्ठा nfp_app *app,
		       काष्ठा flowi4 *flow, काष्ठा neighbour *neigh, gfp_t flag)
अणु
	काष्ठा nfp_tun_neigh payload;
	u32 port_id;

	port_id = nfp_flower_get_port_id_from_netdev(app, netdev);
	अगर (!port_id)
		वापस;

	स_रखो(&payload, 0, माप(काष्ठा nfp_tun_neigh));
	payload.dst_ipv4 = flow->daddr;

	/* If entry has expired send dst IP with all other fields 0. */
	अगर (!(neigh->nud_state & NUD_VALID) || neigh->dead) अणु
		nfp_tun_del_route_from_cache_v4(app, &payload.dst_ipv4);
		/* Trigger ARP to verअगरy invalid neighbour state. */
		neigh_event_send(neigh, शून्य);
		जाओ send_msg;
	पूर्ण

	/* Have a valid neighbour so populate rest of entry. */
	payload.src_ipv4 = flow->saddr;
	ether_addr_copy(payload.src_addr, netdev->dev_addr);
	neigh_ha_snapshot(payload.dst_addr, neigh, netdev);
	payload.port_id = cpu_to_be32(port_id);
	/* Add destination of new route to NFP cache. */
	nfp_tun_add_route_to_cache_v4(app, &payload.dst_ipv4);

send_msg:
	nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_NEIGH,
				 माप(काष्ठा nfp_tun_neigh),
				 (अचिन्हित अक्षर *)&payload, flag);
पूर्ण

अटल व्योम
nfp_tun_ग_लिखो_neigh_v6(काष्ठा net_device *netdev, काष्ठा nfp_app *app,
		       काष्ठा flowi6 *flow, काष्ठा neighbour *neigh, gfp_t flag)
अणु
	काष्ठा nfp_tun_neigh_v6 payload;
	u32 port_id;

	port_id = nfp_flower_get_port_id_from_netdev(app, netdev);
	अगर (!port_id)
		वापस;

	स_रखो(&payload, 0, माप(काष्ठा nfp_tun_neigh_v6));
	payload.dst_ipv6 = flow->daddr;

	/* If entry has expired send dst IP with all other fields 0. */
	अगर (!(neigh->nud_state & NUD_VALID) || neigh->dead) अणु
		nfp_tun_del_route_from_cache_v6(app, &payload.dst_ipv6);
		/* Trigger probe to verअगरy invalid neighbour state. */
		neigh_event_send(neigh, शून्य);
		जाओ send_msg;
	पूर्ण

	/* Have a valid neighbour so populate rest of entry. */
	payload.src_ipv6 = flow->saddr;
	ether_addr_copy(payload.src_addr, netdev->dev_addr);
	neigh_ha_snapshot(payload.dst_addr, neigh, netdev);
	payload.port_id = cpu_to_be32(port_id);
	/* Add destination of new route to NFP cache. */
	nfp_tun_add_route_to_cache_v6(app, &payload.dst_ipv6);

send_msg:
	nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_NEIGH_V6,
				 माप(काष्ठा nfp_tun_neigh_v6),
				 (अचिन्हित अक्षर *)&payload, flag);
पूर्ण

अटल पूर्णांक
nfp_tun_neigh_event_handler(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा nfp_flower_priv *app_priv;
	काष्ठा netevent_redirect *redir;
	काष्ठा flowi4 flow4 = अणुपूर्ण;
	काष्ठा flowi6 flow6 = अणुपूर्ण;
	काष्ठा neighbour *n;
	काष्ठा nfp_app *app;
	काष्ठा rtable *rt;
	bool ipv6 = false;
	पूर्णांक err;

	चयन (event) अणु
	हाल NETEVENT_REसूचीECT:
		redir = (काष्ठा netevent_redirect *)ptr;
		n = redir->neigh;
		अवरोध;
	हाल NETEVENT_NEIGH_UPDATE:
		n = (काष्ठा neighbour *)ptr;
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (n->tbl->family == AF_INET6)
		ipv6 = true;

	अगर (ipv6)
		flow6.daddr = *(काष्ठा in6_addr *)n->primary_key;
	अन्यथा
		flow4.daddr = *(__be32 *)n->primary_key;

	app_priv = container_of(nb, काष्ठा nfp_flower_priv, tun.neigh_nb);
	app = app_priv->app;

	अगर (!nfp_netdev_is_nfp_repr(n->dev) &&
	    !nfp_flower_पूर्णांकernal_port_can_offload(app, n->dev))
		वापस NOTIFY_DONE;

	/* Only concerned with changes to routes alपढ़ोy added to NFP. */
	अगर ((ipv6 && !nfp_tun_has_route_v6(app, &flow6.daddr)) ||
	    (!ipv6 && !nfp_tun_has_route_v4(app, &flow4.daddr)))
		वापस NOTIFY_DONE;

#अगर IS_ENABLED(CONFIG_INET)
	अगर (ipv6) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा dst_entry *dst;

		dst = ipv6_stub->ipv6_dst_lookup_flow(dev_net(n->dev), शून्य,
						      &flow6, शून्य);
		अगर (IS_ERR(dst))
			वापस NOTIFY_DONE;

		dst_release(dst);
		flow6.flowi6_proto = IPPROTO_UDP;
		nfp_tun_ग_लिखो_neigh_v6(n->dev, app, &flow6, n, GFP_ATOMIC);
#अन्यथा
		वापस NOTIFY_DONE;
#पूर्ण_अगर /* CONFIG_IPV6 */
	पूर्ण अन्यथा अणु
		/* Do a route lookup to populate flow data. */
		rt = ip_route_output_key(dev_net(n->dev), &flow4);
		err = PTR_ERR_OR_ZERO(rt);
		अगर (err)
			वापस NOTIFY_DONE;

		ip_rt_put(rt);

		flow4.flowi4_proto = IPPROTO_UDP;
		nfp_tun_ग_लिखो_neigh_v4(n->dev, app, &flow4, n, GFP_ATOMIC);
	पूर्ण
#अन्यथा
	वापस NOTIFY_DONE;
#पूर्ण_अगर /* CONFIG_INET */

	वापस NOTIFY_OK;
पूर्ण

व्योम nfp_tunnel_request_route_v4(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_tun_req_route_ipv4 *payload;
	काष्ठा net_device *netdev;
	काष्ठा flowi4 flow = अणुपूर्ण;
	काष्ठा neighbour *n;
	काष्ठा rtable *rt;
	पूर्णांक err;

	payload = nfp_flower_cmsg_get_data(skb);

	rcu_पढ़ो_lock();
	netdev = nfp_app_dev_get(app, be32_to_cpu(payload->ingress_port), शून्य);
	अगर (!netdev)
		जाओ fail_rcu_unlock;

	flow.daddr = payload->ipv4_addr;
	flow.flowi4_proto = IPPROTO_UDP;

#अगर IS_ENABLED(CONFIG_INET)
	/* Do a route lookup on same namespace as ingress port. */
	rt = ip_route_output_key(dev_net(netdev), &flow);
	err = PTR_ERR_OR_ZERO(rt);
	अगर (err)
		जाओ fail_rcu_unlock;
#अन्यथा
	जाओ fail_rcu_unlock;
#पूर्ण_अगर

	/* Get the neighbour entry क्रम the lookup */
	n = dst_neigh_lookup(&rt->dst, &flow.daddr);
	ip_rt_put(rt);
	अगर (!n)
		जाओ fail_rcu_unlock;
	nfp_tun_ग_लिखो_neigh_v4(n->dev, app, &flow, n, GFP_ATOMIC);
	neigh_release(n);
	rcu_पढ़ो_unlock();
	वापस;

fail_rcu_unlock:
	rcu_पढ़ो_unlock();
	nfp_flower_cmsg_warn(app, "Requested route not found.\n");
पूर्ण

व्योम nfp_tunnel_request_route_v6(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_tun_req_route_ipv6 *payload;
	काष्ठा net_device *netdev;
	काष्ठा flowi6 flow = अणुपूर्ण;
	काष्ठा dst_entry *dst;
	काष्ठा neighbour *n;

	payload = nfp_flower_cmsg_get_data(skb);

	rcu_पढ़ो_lock();
	netdev = nfp_app_dev_get(app, be32_to_cpu(payload->ingress_port), शून्य);
	अगर (!netdev)
		जाओ fail_rcu_unlock;

	flow.daddr = payload->ipv6_addr;
	flow.flowi6_proto = IPPROTO_UDP;

#अगर IS_ENABLED(CONFIG_INET) && IS_ENABLED(CONFIG_IPV6)
	dst = ipv6_stub->ipv6_dst_lookup_flow(dev_net(netdev), शून्य, &flow,
					      शून्य);
	अगर (IS_ERR(dst))
		जाओ fail_rcu_unlock;
#अन्यथा
	जाओ fail_rcu_unlock;
#पूर्ण_अगर

	n = dst_neigh_lookup(dst, &flow.daddr);
	dst_release(dst);
	अगर (!n)
		जाओ fail_rcu_unlock;

	nfp_tun_ग_लिखो_neigh_v6(n->dev, app, &flow, n, GFP_ATOMIC);
	neigh_release(n);
	rcu_पढ़ो_unlock();
	वापस;

fail_rcu_unlock:
	rcu_पढ़ो_unlock();
	nfp_flower_cmsg_warn(app, "Requested IPv6 route not found.\n");
पूर्ण

अटल व्योम nfp_tun_ग_लिखो_ipv4_list(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_ipv4_addr_entry *entry;
	काष्ठा nfp_tun_ipv4_addr payload;
	काष्ठा list_head *ptr, *storage;
	पूर्णांक count;

	स_रखो(&payload, 0, माप(काष्ठा nfp_tun_ipv4_addr));
	mutex_lock(&priv->tun.ipv4_off_lock);
	count = 0;
	list_क्रम_each_safe(ptr, storage, &priv->tun.ipv4_off_list) अणु
		अगर (count >= NFP_FL_IPV4_ADDRS_MAX) अणु
			mutex_unlock(&priv->tun.ipv4_off_lock);
			nfp_flower_cmsg_warn(app, "IPv4 offload exceeds limit.\n");
			वापस;
		पूर्ण
		entry = list_entry(ptr, काष्ठा nfp_ipv4_addr_entry, list);
		payload.ipv4_addr[count++] = entry->ipv4_addr;
	पूर्ण
	payload.count = cpu_to_be32(count);
	mutex_unlock(&priv->tun.ipv4_off_lock);

	nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_IPS,
				 माप(काष्ठा nfp_tun_ipv4_addr),
				 &payload, GFP_KERNEL);
पूर्ण

व्योम nfp_tunnel_add_ipv4_off(काष्ठा nfp_app *app, __be32 ipv4)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_ipv4_addr_entry *entry;
	काष्ठा list_head *ptr, *storage;

	mutex_lock(&priv->tun.ipv4_off_lock);
	list_क्रम_each_safe(ptr, storage, &priv->tun.ipv4_off_list) अणु
		entry = list_entry(ptr, काष्ठा nfp_ipv4_addr_entry, list);
		अगर (entry->ipv4_addr == ipv4) अणु
			entry->ref_count++;
			mutex_unlock(&priv->tun.ipv4_off_lock);
			वापस;
		पूर्ण
	पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		mutex_unlock(&priv->tun.ipv4_off_lock);
		nfp_flower_cmsg_warn(app, "Mem error when offloading IP address.\n");
		वापस;
	पूर्ण
	entry->ipv4_addr = ipv4;
	entry->ref_count = 1;
	list_add_tail(&entry->list, &priv->tun.ipv4_off_list);
	mutex_unlock(&priv->tun.ipv4_off_lock);

	nfp_tun_ग_लिखो_ipv4_list(app);
पूर्ण

व्योम nfp_tunnel_del_ipv4_off(काष्ठा nfp_app *app, __be32 ipv4)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_ipv4_addr_entry *entry;
	काष्ठा list_head *ptr, *storage;

	mutex_lock(&priv->tun.ipv4_off_lock);
	list_क्रम_each_safe(ptr, storage, &priv->tun.ipv4_off_list) अणु
		entry = list_entry(ptr, काष्ठा nfp_ipv4_addr_entry, list);
		अगर (entry->ipv4_addr == ipv4) अणु
			entry->ref_count--;
			अगर (!entry->ref_count) अणु
				list_del(&entry->list);
				kमुक्त(entry);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->tun.ipv4_off_lock);

	nfp_tun_ग_लिखो_ipv4_list(app);
पूर्ण

अटल व्योम nfp_tun_ग_लिखो_ipv6_list(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_ipv6_addr_entry *entry;
	काष्ठा nfp_tun_ipv6_addr payload;
	पूर्णांक count = 0;

	स_रखो(&payload, 0, माप(काष्ठा nfp_tun_ipv6_addr));
	mutex_lock(&priv->tun.ipv6_off_lock);
	list_क्रम_each_entry(entry, &priv->tun.ipv6_off_list, list) अणु
		अगर (count >= NFP_FL_IPV6_ADDRS_MAX) अणु
			nfp_flower_cmsg_warn(app, "Too many IPv6 tunnel endpoint addresses, some cannot be offloaded.\n");
			अवरोध;
		पूर्ण
		payload.ipv6_addr[count++] = entry->ipv6_addr;
	पूर्ण
	mutex_unlock(&priv->tun.ipv6_off_lock);
	payload.count = cpu_to_be32(count);

	nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_IPS_V6,
				 माप(काष्ठा nfp_tun_ipv6_addr),
				 &payload, GFP_KERNEL);
पूर्ण

काष्ठा nfp_ipv6_addr_entry *
nfp_tunnel_add_ipv6_off(काष्ठा nfp_app *app, काष्ठा in6_addr *ipv6)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_ipv6_addr_entry *entry;

	mutex_lock(&priv->tun.ipv6_off_lock);
	list_क्रम_each_entry(entry, &priv->tun.ipv6_off_list, list)
		अगर (!स_भेद(&entry->ipv6_addr, ipv6, माप(*ipv6))) अणु
			entry->ref_count++;
			mutex_unlock(&priv->tun.ipv6_off_lock);
			वापस entry;
		पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		mutex_unlock(&priv->tun.ipv6_off_lock);
		nfp_flower_cmsg_warn(app, "Mem error when offloading IP address.\n");
		वापस शून्य;
	पूर्ण
	entry->ipv6_addr = *ipv6;
	entry->ref_count = 1;
	list_add_tail(&entry->list, &priv->tun.ipv6_off_list);
	mutex_unlock(&priv->tun.ipv6_off_lock);

	nfp_tun_ग_लिखो_ipv6_list(app);

	वापस entry;
पूर्ण

व्योम
nfp_tunnel_put_ipv6_off(काष्ठा nfp_app *app, काष्ठा nfp_ipv6_addr_entry *entry)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	bool मुक्तd = false;

	mutex_lock(&priv->tun.ipv6_off_lock);
	अगर (!--entry->ref_count) अणु
		list_del(&entry->list);
		kमुक्त(entry);
		मुक्तd = true;
	पूर्ण
	mutex_unlock(&priv->tun.ipv6_off_lock);

	अगर (मुक्तd)
		nfp_tun_ग_लिखो_ipv6_list(app);
पूर्ण

अटल पूर्णांक
__nfp_tunnel_offload_mac(काष्ठा nfp_app *app, u8 *mac, u16 idx, bool del)
अणु
	काष्ठा nfp_tun_mac_addr_offload payload;

	स_रखो(&payload, 0, माप(payload));

	अगर (del)
		payload.flags = cpu_to_be16(NFP_TUN_MAC_OFFLOAD_DEL_FLAG);

	/* FW supports multiple MACs per cmsg but restrict to single. */
	payload.count = cpu_to_be16(1);
	payload.index = cpu_to_be16(idx);
	ether_addr_copy(payload.addr, mac);

	वापस nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_MAC,
					माप(काष्ठा nfp_tun_mac_addr_offload),
					&payload, GFP_KERNEL);
पूर्ण

अटल bool nfp_tunnel_port_is_phy_repr(पूर्णांक port)
अणु
	अगर (FIELD_GET(NFP_FLOWER_CMSG_PORT_TYPE, port) ==
	    NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT)
		वापस true;

	वापस false;
पूर्ण

अटल u16 nfp_tunnel_get_mac_idx_from_phy_port_id(पूर्णांक port)
अणु
	वापस port << 8 | NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT;
पूर्ण

अटल u16 nfp_tunnel_get_global_mac_idx_from_ida(पूर्णांक id)
अणु
	वापस id << 8 | NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT;
पूर्ण

अटल पूर्णांक nfp_tunnel_get_ida_from_global_mac_idx(u16 nfp_mac_idx)
अणु
	वापस nfp_mac_idx >> 8;
पूर्ण

अटल bool nfp_tunnel_is_mac_idx_global(u16 nfp_mac_idx)
अणु
	वापस (nfp_mac_idx & 0xff) == NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT;
पूर्ण

अटल काष्ठा nfp_tun_offloaded_mac *
nfp_tunnel_lookup_offloaded_macs(काष्ठा nfp_app *app, u8 *mac)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	वापस rhashtable_lookup_fast(&priv->tun.offloaded_macs, mac,
				      offloaded_macs_params);
पूर्ण

अटल व्योम
nfp_tunnel_offloaded_macs_inc_ref_and_link(काष्ठा nfp_tun_offloaded_mac *entry,
					   काष्ठा net_device *netdev, bool mod)
अणु
	अगर (nfp_netdev_is_nfp_repr(netdev)) अणु
		काष्ठा nfp_flower_repr_priv *repr_priv;
		काष्ठा nfp_repr *repr;

		repr = netdev_priv(netdev);
		repr_priv = repr->app_priv;

		/* If modअगरing MAC, हटाओ repr from old list first. */
		अगर (mod)
			list_del(&repr_priv->mac_list);

		list_add_tail(&repr_priv->mac_list, &entry->repr_list);
	पूर्ण अन्यथा अगर (nfp_flower_is_supported_bridge(netdev)) अणु
		entry->bridge_count++;
	पूर्ण

	entry->ref_count++;
पूर्ण

अटल पूर्णांक
nfp_tunnel_add_shared_mac(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			  पूर्णांक port, bool mod)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	पूर्णांक ida_idx = NFP_MAX_MAC_INDEX, err;
	काष्ठा nfp_tun_offloaded_mac *entry;
	u16 nfp_mac_idx = 0;

	entry = nfp_tunnel_lookup_offloaded_macs(app, netdev->dev_addr);
	अगर (entry && nfp_tunnel_is_mac_idx_global(entry->index)) अणु
		अगर (entry->bridge_count ||
		    !nfp_flower_is_supported_bridge(netdev)) अणु
			nfp_tunnel_offloaded_macs_inc_ref_and_link(entry,
								   netdev, mod);
			वापस 0;
		पूर्ण

		/* MAC is global but matches need to go to pre_tun table. */
		nfp_mac_idx = entry->index | NFP_TUN_PRE_TUN_IDX_BIT;
	पूर्ण

	अगर (!nfp_mac_idx) अणु
		/* Assign a global index अगर non-repr or MAC is now shared. */
		अगर (entry || !port) अणु
			ida_idx = ida_simple_get(&priv->tun.mac_off_ids, 0,
						 NFP_MAX_MAC_INDEX, GFP_KERNEL);
			अगर (ida_idx < 0)
				वापस ida_idx;

			nfp_mac_idx =
				nfp_tunnel_get_global_mac_idx_from_ida(ida_idx);

			अगर (nfp_flower_is_supported_bridge(netdev))
				nfp_mac_idx |= NFP_TUN_PRE_TUN_IDX_BIT;

		पूर्ण अन्यथा अणु
			nfp_mac_idx =
				nfp_tunnel_get_mac_idx_from_phy_port_id(port);
		पूर्ण
	पूर्ण

	अगर (!entry) अणु
		entry = kzalloc(माप(*entry), GFP_KERNEL);
		अगर (!entry) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_ida;
		पूर्ण

		ether_addr_copy(entry->addr, netdev->dev_addr);
		INIT_LIST_HEAD(&entry->repr_list);

		अगर (rhashtable_insert_fast(&priv->tun.offloaded_macs,
					   &entry->ht_node,
					   offloaded_macs_params)) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_entry;
		पूर्ण
	पूर्ण

	err = __nfp_tunnel_offload_mac(app, netdev->dev_addr,
				       nfp_mac_idx, false);
	अगर (err) अणु
		/* If not shared then मुक्त. */
		अगर (!entry->ref_count)
			जाओ err_हटाओ_hash;
		जाओ err_मुक्त_ida;
	पूर्ण

	entry->index = nfp_mac_idx;
	nfp_tunnel_offloaded_macs_inc_ref_and_link(entry, netdev, mod);

	वापस 0;

err_हटाओ_hash:
	rhashtable_हटाओ_fast(&priv->tun.offloaded_macs, &entry->ht_node,
			       offloaded_macs_params);
err_मुक्त_entry:
	kमुक्त(entry);
err_मुक्त_ida:
	अगर (ida_idx != NFP_MAX_MAC_INDEX)
		ida_simple_हटाओ(&priv->tun.mac_off_ids, ida_idx);

	वापस err;
पूर्ण

अटल पूर्णांक
nfp_tunnel_del_shared_mac(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			  u8 *mac, bool mod)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_flower_repr_priv *repr_priv;
	काष्ठा nfp_tun_offloaded_mac *entry;
	काष्ठा nfp_repr *repr;
	पूर्णांक ida_idx;

	entry = nfp_tunnel_lookup_offloaded_macs(app, mac);
	अगर (!entry)
		वापस 0;

	entry->ref_count--;
	/* If del is part of a mod then mac_list is still in use अन्यथाwheree. */
	अगर (nfp_netdev_is_nfp_repr(netdev) && !mod) अणु
		repr = netdev_priv(netdev);
		repr_priv = repr->app_priv;
		list_del(&repr_priv->mac_list);
	पूर्ण

	अगर (nfp_flower_is_supported_bridge(netdev)) अणु
		entry->bridge_count--;

		अगर (!entry->bridge_count && entry->ref_count) अणु
			u16 nfp_mac_idx;

			nfp_mac_idx = entry->index & ~NFP_TUN_PRE_TUN_IDX_BIT;
			अगर (__nfp_tunnel_offload_mac(app, mac, nfp_mac_idx,
						     false)) अणु
				nfp_flower_cmsg_warn(app, "MAC offload index revert failed on %s.\n",
						     netdev_name(netdev));
				वापस 0;
			पूर्ण

			entry->index = nfp_mac_idx;
			वापस 0;
		पूर्ण
	पूर्ण

	/* If MAC is now used by 1 repr set the offloaded MAC index to port. */
	अगर (entry->ref_count == 1 && list_is_singular(&entry->repr_list)) अणु
		u16 nfp_mac_idx;
		पूर्णांक port, err;

		repr_priv = list_first_entry(&entry->repr_list,
					     काष्ठा nfp_flower_repr_priv,
					     mac_list);
		repr = repr_priv->nfp_repr;
		port = nfp_repr_get_port_id(repr->netdev);
		nfp_mac_idx = nfp_tunnel_get_mac_idx_from_phy_port_id(port);
		err = __nfp_tunnel_offload_mac(app, mac, nfp_mac_idx, false);
		अगर (err) अणु
			nfp_flower_cmsg_warn(app, "MAC offload index revert failed on %s.\n",
					     netdev_name(netdev));
			वापस 0;
		पूर्ण

		ida_idx = nfp_tunnel_get_ida_from_global_mac_idx(entry->index);
		ida_simple_हटाओ(&priv->tun.mac_off_ids, ida_idx);
		entry->index = nfp_mac_idx;
		वापस 0;
	पूर्ण

	अगर (entry->ref_count)
		वापस 0;

	WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->tun.offloaded_macs,
					    &entry->ht_node,
					    offloaded_macs_params));
	/* If MAC has global ID then extract and मुक्त the ida entry. */
	अगर (nfp_tunnel_is_mac_idx_global(entry->index)) अणु
		ida_idx = nfp_tunnel_get_ida_from_global_mac_idx(entry->index);
		ida_simple_हटाओ(&priv->tun.mac_off_ids, ida_idx);
	पूर्ण

	kमुक्त(entry);

	वापस __nfp_tunnel_offload_mac(app, mac, 0, true);
पूर्ण

अटल पूर्णांक
nfp_tunnel_offload_mac(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
		       क्रमागत nfp_flower_mac_offload_cmd cmd)
अणु
	काष्ठा nfp_flower_non_repr_priv *nr_priv = शून्य;
	bool non_repr = false, *mac_offloaded;
	u8 *off_mac = शून्य;
	पूर्णांक err, port = 0;

	अगर (nfp_netdev_is_nfp_repr(netdev)) अणु
		काष्ठा nfp_flower_repr_priv *repr_priv;
		काष्ठा nfp_repr *repr;

		repr = netdev_priv(netdev);
		अगर (repr->app != app)
			वापस 0;

		repr_priv = repr->app_priv;
		अगर (repr_priv->on_bridge)
			वापस 0;

		mac_offloaded = &repr_priv->mac_offloaded;
		off_mac = &repr_priv->offloaded_mac_addr[0];
		port = nfp_repr_get_port_id(netdev);
		अगर (!nfp_tunnel_port_is_phy_repr(port))
			वापस 0;
	पूर्ण अन्यथा अगर (nfp_fl_is_netdev_to_offload(netdev)) अणु
		nr_priv = nfp_flower_non_repr_priv_get(app, netdev);
		अगर (!nr_priv)
			वापस -ENOMEM;

		mac_offloaded = &nr_priv->mac_offloaded;
		off_mac = &nr_priv->offloaded_mac_addr[0];
		non_repr = true;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		err = -EINVAL;
		जाओ err_put_non_repr_priv;
	पूर्ण

	अगर (cmd == NFP_TUNNEL_MAC_OFFLOAD_MOD && !*mac_offloaded)
		cmd = NFP_TUNNEL_MAC_OFFLOAD_ADD;

	चयन (cmd) अणु
	हाल NFP_TUNNEL_MAC_OFFLOAD_ADD:
		err = nfp_tunnel_add_shared_mac(app, netdev, port, false);
		अगर (err)
			जाओ err_put_non_repr_priv;

		अगर (non_repr)
			__nfp_flower_non_repr_priv_get(nr_priv);

		*mac_offloaded = true;
		ether_addr_copy(off_mac, netdev->dev_addr);
		अवरोध;
	हाल NFP_TUNNEL_MAC_OFFLOAD_DEL:
		/* Only attempt delete अगर add was successful. */
		अगर (!*mac_offloaded)
			अवरोध;

		अगर (non_repr)
			__nfp_flower_non_repr_priv_put(nr_priv);

		*mac_offloaded = false;

		err = nfp_tunnel_del_shared_mac(app, netdev, netdev->dev_addr,
						false);
		अगर (err)
			जाओ err_put_non_repr_priv;

		अवरोध;
	हाल NFP_TUNNEL_MAC_OFFLOAD_MOD:
		/* Ignore अगर changing to the same address. */
		अगर (ether_addr_equal(netdev->dev_addr, off_mac))
			अवरोध;

		err = nfp_tunnel_add_shared_mac(app, netdev, port, true);
		अगर (err)
			जाओ err_put_non_repr_priv;

		/* Delete the previous MAC address. */
		err = nfp_tunnel_del_shared_mac(app, netdev, off_mac, true);
		अगर (err)
			nfp_flower_cmsg_warn(app, "Failed to remove offload of replaced MAC addr on %s.\n",
					     netdev_name(netdev));

		ether_addr_copy(off_mac, netdev->dev_addr);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ err_put_non_repr_priv;
	पूर्ण

	अगर (non_repr)
		__nfp_flower_non_repr_priv_put(nr_priv);

	वापस 0;

err_put_non_repr_priv:
	अगर (non_repr)
		__nfp_flower_non_repr_priv_put(nr_priv);

	वापस err;
पूर्ण

पूर्णांक nfp_tunnel_mac_event_handler(काष्ठा nfp_app *app,
				 काष्ठा net_device *netdev,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	पूर्णांक err;

	अगर (event == NETDEV_DOWN) अणु
		err = nfp_tunnel_offload_mac(app, netdev,
					     NFP_TUNNEL_MAC_OFFLOAD_DEL);
		अगर (err)
			nfp_flower_cmsg_warn(app, "Failed to delete offload MAC on %s.\n",
					     netdev_name(netdev));
	पूर्ण अन्यथा अगर (event == NETDEV_UP) अणु
		err = nfp_tunnel_offload_mac(app, netdev,
					     NFP_TUNNEL_MAC_OFFLOAD_ADD);
		अगर (err)
			nfp_flower_cmsg_warn(app, "Failed to offload MAC on %s.\n",
					     netdev_name(netdev));
	पूर्ण अन्यथा अगर (event == NETDEV_CHANGEADDR) अणु
		/* Only offload addr change अगर netdev is alपढ़ोy up. */
		अगर (!(netdev->flags & IFF_UP))
			वापस NOTIFY_OK;

		err = nfp_tunnel_offload_mac(app, netdev,
					     NFP_TUNNEL_MAC_OFFLOAD_MOD);
		अगर (err)
			nfp_flower_cmsg_warn(app, "Failed to offload MAC change on %s.\n",
					     netdev_name(netdev));
	पूर्ण अन्यथा अगर (event == NETDEV_CHANGEUPPER) अणु
		/* If a repr is attached to a bridge then tunnel packets
		 * entering the physical port are directed through the bridge
		 * datapath and cannot be directly detunneled. Thereक्रमe,
		 * associated offloaded MACs and indexes should not be used
		 * by fw क्रम detunneling.
		 */
		काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
		काष्ठा net_device *upper = info->upper_dev;
		काष्ठा nfp_flower_repr_priv *repr_priv;
		काष्ठा nfp_repr *repr;

		अगर (!nfp_netdev_is_nfp_repr(netdev) ||
		    !nfp_flower_is_supported_bridge(upper))
			वापस NOTIFY_OK;

		repr = netdev_priv(netdev);
		अगर (repr->app != app)
			वापस NOTIFY_OK;

		repr_priv = repr->app_priv;

		अगर (info->linking) अणु
			अगर (nfp_tunnel_offload_mac(app, netdev,
						   NFP_TUNNEL_MAC_OFFLOAD_DEL))
				nfp_flower_cmsg_warn(app, "Failed to delete offloaded MAC on %s.\n",
						     netdev_name(netdev));
			repr_priv->on_bridge = true;
		पूर्ण अन्यथा अणु
			repr_priv->on_bridge = false;

			अगर (!(netdev->flags & IFF_UP))
				वापस NOTIFY_OK;

			अगर (nfp_tunnel_offload_mac(app, netdev,
						   NFP_TUNNEL_MAC_OFFLOAD_ADD))
				nfp_flower_cmsg_warn(app, "Failed to offload MAC on %s.\n",
						     netdev_name(netdev));
		पूर्ण
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

पूर्णांक nfp_flower_xmit_pre_tun_flow(काष्ठा nfp_app *app,
				 काष्ठा nfp_fl_payload *flow)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;
	काष्ठा nfp_tun_offloaded_mac *mac_entry;
	काष्ठा nfp_flower_meta_tci *key_meta;
	काष्ठा nfp_tun_pre_tun_rule payload;
	काष्ठा net_device *पूर्णांकernal_dev;
	पूर्णांक err;

	अगर (app_priv->pre_tun_rule_cnt == NFP_TUN_PRE_TUN_RULE_LIMIT)
		वापस -ENOSPC;

	स_रखो(&payload, 0, माप(काष्ठा nfp_tun_pre_tun_rule));

	पूर्णांकernal_dev = flow->pre_tun_rule.dev;
	payload.vlan_tci = flow->pre_tun_rule.vlan_tci;
	payload.host_ctx_id = flow->meta.host_ctx_id;

	/* Lookup MAC index क्रम the pre-tunnel rule egress device.
	 * Note that because the device is always an पूर्णांकernal port, it will
	 * have a स्थिरant global index so करोes not need to be tracked.
	 */
	mac_entry = nfp_tunnel_lookup_offloaded_macs(app,
						     पूर्णांकernal_dev->dev_addr);
	अगर (!mac_entry)
		वापस -ENOENT;

	/* Set/clear IPV6 bit. cpu_to_be16() swap will lead to MSB being
	 * set/clear क्रम port_idx.
	 */
	key_meta = (काष्ठा nfp_flower_meta_tci *)flow->unmasked_data;
	अगर (key_meta->nfp_flow_key_layer & NFP_FLOWER_LAYER_IPV6)
		mac_entry->index |= NFP_TUN_PRE_TUN_IPV6_BIT;
	अन्यथा
		mac_entry->index &= ~NFP_TUN_PRE_TUN_IPV6_BIT;

	payload.port_idx = cpu_to_be16(mac_entry->index);

	/* Copy mac id and vlan to flow - dev may not exist at delete समय. */
	flow->pre_tun_rule.vlan_tci = payload.vlan_tci;
	flow->pre_tun_rule.port_idx = payload.port_idx;

	err = nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_PRE_TUN_RULE,
				       माप(काष्ठा nfp_tun_pre_tun_rule),
				       (अचिन्हित अक्षर *)&payload, GFP_KERNEL);
	अगर (err)
		वापस err;

	app_priv->pre_tun_rule_cnt++;

	वापस 0;
पूर्ण

पूर्णांक nfp_flower_xmit_pre_tun_del_flow(काष्ठा nfp_app *app,
				     काष्ठा nfp_fl_payload *flow)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;
	काष्ठा nfp_tun_pre_tun_rule payload;
	u32 पंचांगp_flags = 0;
	पूर्णांक err;

	स_रखो(&payload, 0, माप(काष्ठा nfp_tun_pre_tun_rule));

	पंचांगp_flags |= NFP_TUN_PRE_TUN_RULE_DEL;
	payload.flags = cpu_to_be32(पंचांगp_flags);
	payload.vlan_tci = flow->pre_tun_rule.vlan_tci;
	payload.port_idx = flow->pre_tun_rule.port_idx;

	err = nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_PRE_TUN_RULE,
				       माप(काष्ठा nfp_tun_pre_tun_rule),
				       (अचिन्हित अक्षर *)&payload, GFP_KERNEL);
	अगर (err)
		वापस err;

	app_priv->pre_tun_rule_cnt--;

	वापस 0;
पूर्ण

पूर्णांक nfp_tunnel_config_start(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	पूर्णांक err;

	/* Initialise rhash क्रम MAC offload tracking. */
	err = rhashtable_init(&priv->tun.offloaded_macs,
			      &offloaded_macs_params);
	अगर (err)
		वापस err;

	ida_init(&priv->tun.mac_off_ids);

	/* Initialise priv data क्रम IPv4/v6 offloading. */
	mutex_init(&priv->tun.ipv4_off_lock);
	INIT_LIST_HEAD(&priv->tun.ipv4_off_list);
	mutex_init(&priv->tun.ipv6_off_lock);
	INIT_LIST_HEAD(&priv->tun.ipv6_off_list);

	/* Initialise priv data क्रम neighbour offloading. */
	spin_lock_init(&priv->tun.neigh_off_lock_v4);
	INIT_LIST_HEAD(&priv->tun.neigh_off_list_v4);
	spin_lock_init(&priv->tun.neigh_off_lock_v6);
	INIT_LIST_HEAD(&priv->tun.neigh_off_list_v6);
	priv->tun.neigh_nb.notअगरier_call = nfp_tun_neigh_event_handler;

	err = रेजिस्टर_netevent_notअगरier(&priv->tun.neigh_nb);
	अगर (err) अणु
		rhashtable_मुक्त_and_destroy(&priv->tun.offloaded_macs,
					    nfp_check_rhashtable_empty, शून्य);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nfp_tunnel_config_stop(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_offloaded_route *route_entry, *temp;
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_ipv4_addr_entry *ip_entry;
	काष्ठा nfp_tun_neigh_v6 ipv6_route;
	काष्ठा nfp_tun_neigh ipv4_route;
	काष्ठा list_head *ptr, *storage;

	unरेजिस्टर_netevent_notअगरier(&priv->tun.neigh_nb);

	ida_destroy(&priv->tun.mac_off_ids);

	/* Free any memory that may be occupied by ipv4 list. */
	list_क्रम_each_safe(ptr, storage, &priv->tun.ipv4_off_list) अणु
		ip_entry = list_entry(ptr, काष्ठा nfp_ipv4_addr_entry, list);
		list_del(&ip_entry->list);
		kमुक्त(ip_entry);
	पूर्ण

	mutex_destroy(&priv->tun.ipv6_off_lock);

	/* Free memory in the route list and हटाओ entries from fw cache. */
	list_क्रम_each_entry_safe(route_entry, temp,
				 &priv->tun.neigh_off_list_v4, list) अणु
		स_रखो(&ipv4_route, 0, माप(ipv4_route));
		स_नकल(&ipv4_route.dst_ipv4, &route_entry->ip_add,
		       माप(ipv4_route.dst_ipv4));
		list_del(&route_entry->list);
		kमुक्त(route_entry);

		nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_NEIGH,
					 माप(काष्ठा nfp_tun_neigh),
					 (अचिन्हित अक्षर *)&ipv4_route,
					 GFP_KERNEL);
	पूर्ण

	list_क्रम_each_entry_safe(route_entry, temp,
				 &priv->tun.neigh_off_list_v6, list) अणु
		स_रखो(&ipv6_route, 0, माप(ipv6_route));
		स_नकल(&ipv6_route.dst_ipv6, &route_entry->ip_add,
		       माप(ipv6_route.dst_ipv6));
		list_del(&route_entry->list);
		kमुक्त(route_entry);

		nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_NEIGH_V6,
					 माप(काष्ठा nfp_tun_neigh),
					 (अचिन्हित अक्षर *)&ipv6_route,
					 GFP_KERNEL);
	पूर्ण

	/* Destroy rhash. Entries should be cleaned on netdev notअगरier unreg. */
	rhashtable_मुक्त_and_destroy(&priv->tun.offloaded_macs,
				    nfp_check_rhashtable_empty, शून्य);
पूर्ण

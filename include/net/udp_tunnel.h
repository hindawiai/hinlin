<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_UDP_TUNNEL_H
#घोषणा __NET_UDP_TUNNEL_H

#समावेश <net/ip_tunnels.h>
#समावेश <net/udp.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ipv6.h>
#समावेश <net/ipv6_stubs.h>
#पूर्ण_अगर

काष्ठा udp_port_cfg अणु
	u8			family;

	/* Used only क्रम kernel-created sockets */
	जोड़ अणु
		काष्ठा in_addr		local_ip;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा in6_addr		local_ip6;
#पूर्ण_अगर
	पूर्ण;

	जोड़ अणु
		काष्ठा in_addr		peer_ip;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा in6_addr		peer_ip6;
#पूर्ण_अगर
	पूर्ण;

	__be16			local_udp_port;
	__be16			peer_udp_port;
	पूर्णांक			bind_अगरindex;
	अचिन्हित पूर्णांक		use_udp_checksums:1,
				use_udp6_tx_checksums:1,
				use_udp6_rx_checksums:1,
				ipv6_v6only:1;
पूर्ण;

पूर्णांक udp_sock_create4(काष्ठा net *net, काष्ठा udp_port_cfg *cfg,
		     काष्ठा socket **sockp);

#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक udp_sock_create6(काष्ठा net *net, काष्ठा udp_port_cfg *cfg,
		     काष्ठा socket **sockp);
#अन्यथा
अटल अंतरभूत पूर्णांक udp_sock_create6(काष्ठा net *net, काष्ठा udp_port_cfg *cfg,
				   काष्ठा socket **sockp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक udp_sock_create(काष्ठा net *net,
				  काष्ठा udp_port_cfg *cfg,
				  काष्ठा socket **sockp)
अणु
	अगर (cfg->family == AF_INET)
		वापस udp_sock_create4(net, cfg, sockp);

	अगर (cfg->family == AF_INET6)
		वापस udp_sock_create6(net, cfg, sockp);

	वापस -EPFNOSUPPORT;
पूर्ण

प्रकार पूर्णांक (*udp_tunnel_encap_rcv_t)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
प्रकार पूर्णांक (*udp_tunnel_encap_err_lookup_t)(काष्ठा sock *sk,
					     काष्ठा sk_buff *skb);
प्रकार व्योम (*udp_tunnel_encap_destroy_t)(काष्ठा sock *sk);
प्रकार काष्ठा sk_buff *(*udp_tunnel_gro_receive_t)(काष्ठा sock *sk,
						    काष्ठा list_head *head,
						    काष्ठा sk_buff *skb);
प्रकार पूर्णांक (*udp_tunnel_gro_complete_t)(काष्ठा sock *sk, काष्ठा sk_buff *skb,
					 पूर्णांक nhoff);

काष्ठा udp_tunnel_sock_cfg अणु
	व्योम *sk_user_data;     /* user data used by encap_rcv call back */
	/* Used क्रम setting up udp_sock fields, see udp.h क्रम details */
	__u8  encap_type;
	udp_tunnel_encap_rcv_t encap_rcv;
	udp_tunnel_encap_err_lookup_t encap_err_lookup;
	udp_tunnel_encap_destroy_t encap_destroy;
	udp_tunnel_gro_receive_t gro_receive;
	udp_tunnel_gro_complete_t gro_complete;
पूर्ण;

/* Setup the given (UDP) sock to receive UDP encapsulated packets */
व्योम setup_udp_tunnel_sock(काष्ठा net *net, काष्ठा socket *sock,
			   काष्ठा udp_tunnel_sock_cfg *sock_cfg);

/* -- List of parsable UDP tunnel types --
 *
 * Adding to this list will result in serious debate.  The मुख्य issue is
 * that this list is essentially a list of workarounds क्रम either poorly
 * deचिन्हित tunnels, or poorly deचिन्हित device offloads.
 *
 * The parsing supported via these types should really be used क्रम Rx
 * traffic only as the network stack will have alपढ़ोy inserted offsets क्रम
 * the location of the headers in the skb.  In addition any ports that are
 * pushed should be kept within the namespace without leaking to other
 * devices such as VFs or other ports on the same device.
 *
 * It is strongly encouraged to use CHECKSUM_COMPLETE क्रम Rx to aव्योम the
 * need to use this क्रम Rx checksum offload.  It should not be necessary to
 * call this function to perक्रमm Tx offloads on outgoing traffic.
 */
क्रमागत udp_parsable_tunnel_type अणु
	UDP_TUNNEL_TYPE_VXLAN	  = BIT(0), /* RFC 7348 */
	UDP_TUNNEL_TYPE_GENEVE	  = BIT(1), /* draft-ietf-nvo3-geneve */
	UDP_TUNNEL_TYPE_VXLAN_GPE = BIT(2), /* draft-ietf-nvo3-vxlan-gpe */
पूर्ण;

काष्ठा udp_tunnel_info अणु
	अचिन्हित लघु type;
	sa_family_t sa_family;
	__be16 port;
	u8 hw_priv;
पूर्ण;

/* Notअगरy network devices of offloadable types */
व्योम udp_tunnel_push_rx_port(काष्ठा net_device *dev, काष्ठा socket *sock,
			     अचिन्हित लघु type);
व्योम udp_tunnel_drop_rx_port(काष्ठा net_device *dev, काष्ठा socket *sock,
			     अचिन्हित लघु type);
व्योम udp_tunnel_notअगरy_add_rx_port(काष्ठा socket *sock, अचिन्हित लघु type);
व्योम udp_tunnel_notअगरy_del_rx_port(काष्ठा socket *sock, अचिन्हित लघु type);

अटल अंतरभूत व्योम udp_tunnel_get_rx_info(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	अगर (!(dev->features & NETIF_F_RX_UDP_TUNNEL_PORT))
		वापस;
	call_netdevice_notअगरiers(NETDEV_UDP_TUNNEL_PUSH_INFO, dev);
पूर्ण

अटल अंतरभूत व्योम udp_tunnel_drop_rx_info(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	अगर (!(dev->features & NETIF_F_RX_UDP_TUNNEL_PORT))
		वापस;
	call_netdevice_notअगरiers(NETDEV_UDP_TUNNEL_DROP_INFO, dev);
पूर्ण

/* Transmit the skb using UDP encapsulation. */
व्योम udp_tunnel_xmit_skb(काष्ठा rtable *rt, काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 __be32 src, __be32 dst, __u8 tos, __u8 ttl,
			 __be16 df, __be16 src_port, __be16 dst_port,
			 bool xnet, bool nocheck);

पूर्णांक udp_tunnel6_xmit_skb(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			 काष्ठा sk_buff *skb,
			 काष्ठा net_device *dev, काष्ठा in6_addr *saddr,
			 काष्ठा in6_addr *daddr,
			 __u8 prio, __u8 ttl, __be32 label,
			 __be16 src_port, __be16 dst_port, bool nocheck);

व्योम udp_tunnel_sock_release(काष्ठा socket *sock);

काष्ठा metadata_dst *udp_tun_rx_dst(काष्ठा sk_buff *skb, अचिन्हित लघु family,
				    __be16 flags, __be64 tunnel_id,
				    पूर्णांक md_size);

#अगर_घोषित CONFIG_INET
अटल अंतरभूत पूर्णांक udp_tunnel_handle_offloads(काष्ठा sk_buff *skb, bool udp_csum)
अणु
	पूर्णांक type = udp_csum ? SKB_GSO_UDP_TUNNEL_CSUM : SKB_GSO_UDP_TUNNEL;

	वापस iptunnel_handle_offloads(skb, type);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम udp_tunnel_encap_enable(काष्ठा socket *sock)
अणु
	काष्ठा udp_sock *up = udp_sk(sock->sk);

	अगर (up->encap_enabled)
		वापस;

	up->encap_enabled = 1;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sock->sk->sk_family == PF_INET6)
		ipv6_stub->udpv6_encap_enable();
#पूर्ण_अगर
	udp_encap_enable();
पूर्ण

#घोषणा UDP_TUNNEL_NIC_MAX_TABLES	4

क्रमागत udp_tunnel_nic_info_flags अणु
	/* Device callbacks may sleep */
	UDP_TUNNEL_NIC_INFO_MAY_SLEEP	= BIT(0),
	/* Device only supports offloads when it's खोलो, all ports
	 * will be हटाओd beक्रमe बंद and re-added after खोलो.
	 */
	UDP_TUNNEL_NIC_INFO_OPEN_ONLY	= BIT(1),
	/* Device supports only IPv4 tunnels */
	UDP_TUNNEL_NIC_INFO_IPV4_ONLY	= BIT(2),
	/* Device has hard-coded the IANA VXLAN port (4789) as VXLAN.
	 * This port must not be counted towards n_entries of any table.
	 * Driver will not receive any callback associated with port 4789.
	 */
	UDP_TUNNEL_NIC_INFO_STATIC_IANA_VXLAN	= BIT(3),
पूर्ण;

काष्ठा udp_tunnel_nic;

#घोषणा UDP_TUNNEL_NIC_MAX_SHARING_DEVICES	(U16_MAX / 2)

काष्ठा udp_tunnel_nic_shared अणु
	काष्ठा udp_tunnel_nic *udp_tunnel_nic_info;

	काष्ठा list_head devices;
पूर्ण;

काष्ठा udp_tunnel_nic_shared_node अणु
	काष्ठा net_device *dev;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा udp_tunnel_nic_info - driver UDP tunnel offload inक्रमmation
 * @set_port:	callback क्रम adding a new port
 * @unset_port:	callback क्रम removing a port
 * @sync_table:	callback क्रम syncing the entire port table at once
 * @shared:	reference to device global state (optional)
 * @flags:	device flags from क्रमागत udp_tunnel_nic_info_flags
 * @tables:	UDP port tables this device has
 * @tables.n_entries:		number of entries in this table
 * @tables.tunnel_types:	types of tunnels this table accepts
 *
 * Drivers are expected to provide either @set_port and @unset_port callbacks
 * or the @sync_table callback. Callbacks are invoked with rtnl lock held.
 *
 * Devices which (misguidedly) share the UDP tunnel port table across multiple
 * netdevs should allocate an instance of काष्ठा udp_tunnel_nic_shared and
 * poपूर्णांक @shared at it.
 * There must never be more than %UDP_TUNNEL_NIC_MAX_SHARING_DEVICES devices
 * sharing a table.
 *
 * Known limitations:
 *  - UDP tunnel port notअगरications are fundamentally best-efक्रमt -
 *    it is likely the driver will both see skbs which use a UDP tunnel port,
 *    जबतक not being a tunneled skb, and tunnel skbs from other ports -
 *    drivers should only use these ports क्रम non-critical RX-side offloads,
 *    e.g. the checksum offload;
 *  - none of the devices care about the socket family at present, so we करोn't
 *    track it. Please extend this code अगर you care.
 */
काष्ठा udp_tunnel_nic_info अणु
	/* one-by-one */
	पूर्णांक (*set_port)(काष्ठा net_device *dev,
			अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
			काष्ठा udp_tunnel_info *ti);
	पूर्णांक (*unset_port)(काष्ठा net_device *dev,
			  अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
			  काष्ठा udp_tunnel_info *ti);

	/* all at once */
	पूर्णांक (*sync_table)(काष्ठा net_device *dev, अचिन्हित पूर्णांक table);

	काष्ठा udp_tunnel_nic_shared *shared;

	अचिन्हित पूर्णांक flags;

	काष्ठा udp_tunnel_nic_table_info अणु
		अचिन्हित पूर्णांक n_entries;
		अचिन्हित पूर्णांक tunnel_types;
	पूर्ण tables[UDP_TUNNEL_NIC_MAX_TABLES];
पूर्ण;

/* UDP tunnel module dependencies
 *
 * Tunnel drivers are expected to have a hard dependency on the udp_tunnel
 * module. NIC drivers are not, they just attach their
 * काष्ठा udp_tunnel_nic_info to the netdev and रुको क्रम callbacks to come.
 * Loading a tunnel driver will cause the udp_tunnel module to be loaded
 * and only then will all the required state काष्ठाures be allocated.
 * Since we want a weak dependency from the drivers and the core to udp_tunnel
 * we call things through the following stubs.
 */
काष्ठा udp_tunnel_nic_ops अणु
	व्योम (*get_port)(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			 अचिन्हित पूर्णांक idx, काष्ठा udp_tunnel_info *ti);
	व्योम (*set_port_priv)(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			      अचिन्हित पूर्णांक idx, u8 priv);
	व्योम (*add_port)(काष्ठा net_device *dev, काष्ठा udp_tunnel_info *ti);
	व्योम (*del_port)(काष्ठा net_device *dev, काष्ठा udp_tunnel_info *ti);
	व्योम (*reset_ntf)(काष्ठा net_device *dev);

	माप_प्रकार (*dump_size)(काष्ठा net_device *dev, अचिन्हित पूर्णांक table);
	पूर्णांक (*dump_ग_लिखो)(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			  काष्ठा sk_buff *skb);
पूर्ण;

#अगर_घोषित CONFIG_INET
बाह्य स्थिर काष्ठा udp_tunnel_nic_ops *udp_tunnel_nic_ops;
#अन्यथा
#घोषणा udp_tunnel_nic_ops	((काष्ठा udp_tunnel_nic_ops *)शून्य)
#पूर्ण_अगर

अटल अंतरभूत व्योम
udp_tunnel_nic_get_port(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			अचिन्हित पूर्णांक idx, काष्ठा udp_tunnel_info *ti)
अणु
	/* This helper is used from .sync_table, we indicate empty entries
	 * by zero'ed @ti. Drivers which need to know the details of a port
	 * when it माला_लो deleted should use the .set_port / .unset_port
	 * callbacks.
	 * Zero out here, otherwise !CONFIG_INET causes uninitilized warnings.
	 */
	स_रखो(ti, 0, माप(*ti));

	अगर (udp_tunnel_nic_ops)
		udp_tunnel_nic_ops->get_port(dev, table, idx, ti);
पूर्ण

अटल अंतरभूत व्योम
udp_tunnel_nic_set_port_priv(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			     अचिन्हित पूर्णांक idx, u8 priv)
अणु
	अगर (udp_tunnel_nic_ops)
		udp_tunnel_nic_ops->set_port_priv(dev, table, idx, priv);
पूर्ण

अटल अंतरभूत व्योम
udp_tunnel_nic_add_port(काष्ठा net_device *dev, काष्ठा udp_tunnel_info *ti)
अणु
	अगर (!(dev->features & NETIF_F_RX_UDP_TUNNEL_PORT))
		वापस;
	अगर (udp_tunnel_nic_ops)
		udp_tunnel_nic_ops->add_port(dev, ti);
पूर्ण

अटल अंतरभूत व्योम
udp_tunnel_nic_del_port(काष्ठा net_device *dev, काष्ठा udp_tunnel_info *ti)
अणु
	अगर (!(dev->features & NETIF_F_RX_UDP_TUNNEL_PORT))
		वापस;
	अगर (udp_tunnel_nic_ops)
		udp_tunnel_nic_ops->del_port(dev, ti);
पूर्ण

/**
 * udp_tunnel_nic_reset_ntf() - device-originating reset notअगरication
 * @dev: network पूर्णांकerface device काष्ठाure
 *
 * Called by the driver to inक्रमm the core that the entire UDP tunnel port
 * state has been lost, usually due to device reset. Core will assume device
 * क्रमgot all the ports and issue .set_port and .sync_table callbacks as
 * necessary.
 *
 * This function must be called with rtnl lock held, and will issue all
 * the callbacks beक्रमe वापसing.
 */
अटल अंतरभूत व्योम udp_tunnel_nic_reset_ntf(काष्ठा net_device *dev)
अणु
	अगर (udp_tunnel_nic_ops)
		udp_tunnel_nic_ops->reset_ntf(dev);
पूर्ण

अटल अंतरभूत माप_प्रकार
udp_tunnel_nic_dump_size(काष्ठा net_device *dev, अचिन्हित पूर्णांक table)
अणु
	अगर (!udp_tunnel_nic_ops)
		वापस 0;
	वापस udp_tunnel_nic_ops->dump_size(dev, table);
पूर्ण

अटल अंतरभूत पूर्णांक
udp_tunnel_nic_dump_ग_लिखो(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			  काष्ठा sk_buff *skb)
अणु
	अगर (!udp_tunnel_nic_ops)
		वापस 0;
	वापस udp_tunnel_nic_ops->dump_ग_लिखो(dev, table, skb);
पूर्ण
#पूर्ण_अगर

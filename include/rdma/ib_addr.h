<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2005 Voltaire Inc.  All rights reserved.
 * Copyright (c) 2005 Intel Corporation.  All rights reserved.
 */

#अगर_अघोषित IB_ADDR_H
#घोषणा IB_ADDR_H

#समावेश <linux/ethtool.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/socket.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ipv6.h>
#समावेश <net/अगर_inet6.h>
#समावेश <net/ip.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_pack.h>
#समावेश <net/net_namespace.h>

/**
 * काष्ठा rdma_dev_addr - Contains resolved RDMA hardware addresses
 * @src_dev_addr:	Source MAC address.
 * @dst_dev_addr:	Destination MAC address.
 * @broadcast:		Broadcast address of the device.
 * @dev_type:		The पूर्णांकerface hardware type of the device.
 * @bound_dev_अगर:	An optional device पूर्णांकerface index.
 * @transport:		The transport type used.
 * @net:		Network namespace containing the bound_dev_अगर net_dev.
 * @sgid_attr:		GID attribute to use क्रम identअगरied SGID
 */
काष्ठा rdma_dev_addr अणु
	अचिन्हित अक्षर src_dev_addr[MAX_ADDR_LEN];
	अचिन्हित अक्षर dst_dev_addr[MAX_ADDR_LEN];
	अचिन्हित अक्षर broadcast[MAX_ADDR_LEN];
	अचिन्हित लघु dev_type;
	पूर्णांक bound_dev_अगर;
	क्रमागत rdma_transport_type transport;
	काष्ठा net *net;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	क्रमागत rdma_network_type network;
	पूर्णांक hoplimit;
पूर्ण;

/**
 * rdma_translate_ip - Translate a local IP address to an RDMA hardware
 *   address.
 *
 * The dev_addr->net field must be initialized.
 */
पूर्णांक rdma_translate_ip(स्थिर काष्ठा sockaddr *addr,
		      काष्ठा rdma_dev_addr *dev_addr);

/**
 * rdma_resolve_ip - Resolve source and destination IP addresses to
 *   RDMA hardware addresses.
 * @src_addr: An optional source address to use in the resolution.  If a
 *   source address is not provided, a usable address will be वापसed via
 *   the callback.
 * @dst_addr: The destination address to resolve.
 * @addr: A reference to a data location that will receive the resolved
 *   addresses.  The data location must reमुख्य valid until the callback has
 *   been invoked. The net field of the addr काष्ठा must be valid.
 * @समयout_ms: Amount of समय to रुको क्रम the address resolution to complete.
 * @callback: Call invoked once address resolution has completed, समयd out,
 *   or been canceled.  A status of 0 indicates success.
 * @resolve_by_gid_attr:	Resolve the ip based on the GID attribute from
 *				rdma_dev_addr.
 * @context: User-specअगरied context associated with the call.
 */
पूर्णांक rdma_resolve_ip(काष्ठा sockaddr *src_addr, स्थिर काष्ठा sockaddr *dst_addr,
		    काष्ठा rdma_dev_addr *addr, अचिन्हित दीर्घ समयout_ms,
		    व्योम (*callback)(पूर्णांक status, काष्ठा sockaddr *src_addr,
				     काष्ठा rdma_dev_addr *addr, व्योम *context),
		    bool resolve_by_gid_attr, व्योम *context);

व्योम rdma_addr_cancel(काष्ठा rdma_dev_addr *addr);

पूर्णांक rdma_addr_size(स्थिर काष्ठा sockaddr *addr);
पूर्णांक rdma_addr_size_in6(काष्ठा sockaddr_in6 *addr);
पूर्णांक rdma_addr_size_kss(काष्ठा __kernel_sockaddr_storage *addr);

अटल अंतरभूत u16 ib_addr_get_pkey(काष्ठा rdma_dev_addr *dev_addr)
अणु
	वापस ((u16)dev_addr->broadcast[8] << 8) | (u16)dev_addr->broadcast[9];
पूर्ण

अटल अंतरभूत व्योम ib_addr_set_pkey(काष्ठा rdma_dev_addr *dev_addr, u16 pkey)
अणु
	dev_addr->broadcast[8] = pkey >> 8;
	dev_addr->broadcast[9] = (अचिन्हित अक्षर) pkey;
पूर्ण

अटल अंतरभूत व्योम ib_addr_get_mgid(काष्ठा rdma_dev_addr *dev_addr,
				    जोड़ ib_gid *gid)
अणु
	स_नकल(gid, dev_addr->broadcast + 4, माप *gid);
पूर्ण

अटल अंतरभूत पूर्णांक rdma_addr_gid_offset(काष्ठा rdma_dev_addr *dev_addr)
अणु
	वापस dev_addr->dev_type == ARPHRD_INFINIBAND ? 4 : 0;
पूर्ण

अटल अंतरभूत u16 rdma_vlan_dev_vlan_id(स्थिर काष्ठा net_device *dev)
अणु
	वापस is_vlan_dev(dev) ? vlan_dev_vlan_id(dev) : 0xffff;
पूर्ण

अटल अंतरभूत पूर्णांक rdma_ip2gid(काष्ठा sockaddr *addr, जोड़ ib_gid *gid)
अणु
	चयन (addr->sa_family) अणु
	हाल AF_INET:
		ipv6_addr_set_v4mapped(((काष्ठा sockaddr_in *)
					addr)->sin_addr.s_addr,
				       (काष्ठा in6_addr *)gid);
		अवरोध;
	हाल AF_INET6:
		*(काष्ठा in6_addr *)&gid->raw =
			((काष्ठा sockaddr_in6 *)addr)->sin6_addr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Important - sockaddr should be a जोड़ of sockaddr_in and sockaddr_in6 */
अटल अंतरभूत व्योम rdma_gid2ip(काष्ठा sockaddr *out, स्थिर जोड़ ib_gid *gid)
अणु
	अगर (ipv6_addr_v4mapped((काष्ठा in6_addr *)gid)) अणु
		काष्ठा sockaddr_in *out_in = (काष्ठा sockaddr_in *)out;
		स_रखो(out_in, 0, माप(*out_in));
		out_in->sin_family = AF_INET;
		स_नकल(&out_in->sin_addr.s_addr, gid->raw + 12, 4);
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *out_in = (काष्ठा sockaddr_in6 *)out;
		स_रखो(out_in, 0, माप(*out_in));
		out_in->sin6_family = AF_INET6;
		स_नकल(&out_in->sin6_addr.s6_addr, gid->raw, 16);
	पूर्ण
पूर्ण

/*
 * rdma_get/set_sgid/dgid() APIs are applicable to IB, and iWarp.
 * They are not applicable to RoCE.
 * RoCE GIDs are derived from the IP addresses.
 */
अटल अंतरभूत व्योम rdma_addr_get_sgid(काष्ठा rdma_dev_addr *dev_addr, जोड़ ib_gid *gid)
अणु
	स_नकल(gid, dev_addr->src_dev_addr + rdma_addr_gid_offset(dev_addr),
	       माप(*gid));
पूर्ण

अटल अंतरभूत व्योम rdma_addr_set_sgid(काष्ठा rdma_dev_addr *dev_addr, जोड़ ib_gid *gid)
अणु
	स_नकल(dev_addr->src_dev_addr + rdma_addr_gid_offset(dev_addr), gid, माप *gid);
पूर्ण

अटल अंतरभूत व्योम rdma_addr_get_dgid(काष्ठा rdma_dev_addr *dev_addr, जोड़ ib_gid *gid)
अणु
	स_नकल(gid, dev_addr->dst_dev_addr + rdma_addr_gid_offset(dev_addr), माप *gid);
पूर्ण

अटल अंतरभूत व्योम rdma_addr_set_dgid(काष्ठा rdma_dev_addr *dev_addr, जोड़ ib_gid *gid)
अणु
	स_नकल(dev_addr->dst_dev_addr + rdma_addr_gid_offset(dev_addr), gid, माप *gid);
पूर्ण

अटल अंतरभूत क्रमागत ib_mtu iboe_get_mtu(पूर्णांक mtu)
अणु
	/*
	 * Reduce IB headers from effective IBoE MTU.
	 */
	mtu = mtu - (IB_GRH_BYTES + IB_UDP_BYTES + IB_BTH_BYTES +
		     IB_EXT_XRC_BYTES + IB_EXT_ATOMICETH_BYTES +
		     IB_ICRC_BYTES);

	अगर (mtu >= ib_mtu_क्रमागत_to_पूर्णांक(IB_MTU_4096))
		वापस IB_MTU_4096;
	अन्यथा अगर (mtu >= ib_mtu_क्रमागत_to_पूर्णांक(IB_MTU_2048))
		वापस IB_MTU_2048;
	अन्यथा अगर (mtu >= ib_mtu_क्रमागत_to_पूर्णांक(IB_MTU_1024))
		वापस IB_MTU_1024;
	अन्यथा अगर (mtu >= ib_mtu_क्रमागत_to_पूर्णांक(IB_MTU_512))
		वापस IB_MTU_512;
	अन्यथा अगर (mtu >= ib_mtu_क्रमागत_to_पूर्णांक(IB_MTU_256))
		वापस IB_MTU_256;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक iboe_get_rate(काष्ठा net_device *dev)
अणु
	काष्ठा ethtool_link_ksettings cmd;
	पूर्णांक err;

	rtnl_lock();
	err = __ethtool_get_link_ksettings(dev, &cmd);
	rtnl_unlock();
	अगर (err)
		वापस IB_RATE_PORT_CURRENT;

	अगर (cmd.base.speed >= 40000)
		वापस IB_RATE_40_GBPS;
	अन्यथा अगर (cmd.base.speed >= 30000)
		वापस IB_RATE_30_GBPS;
	अन्यथा अगर (cmd.base.speed >= 20000)
		वापस IB_RATE_20_GBPS;
	अन्यथा अगर (cmd.base.speed >= 10000)
		वापस IB_RATE_10_GBPS;
	अन्यथा
		वापस IB_RATE_PORT_CURRENT;
पूर्ण

अटल अंतरभूत पूर्णांक rdma_link_local_addr(काष्ठा in6_addr *addr)
अणु
	अगर (addr->s6_addr32[0] == htonl(0xfe800000) &&
	    addr->s6_addr32[1] == 0)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rdma_get_ll_mac(काष्ठा in6_addr *addr, u8 *mac)
अणु
	स_नकल(mac, &addr->s6_addr[8], 3);
	स_नकल(mac + 3, &addr->s6_addr[13], 3);
	mac[0] ^= 2;
पूर्ण

अटल अंतरभूत पूर्णांक rdma_is_multicast_addr(काष्ठा in6_addr *addr)
अणु
	__be32 ipv4_addr;

	अगर (addr->s6_addr[0] == 0xff)
		वापस 1;

	ipv4_addr = addr->s6_addr32[3];
	वापस (ipv6_addr_v4mapped(addr) && ipv4_is_multicast(ipv4_addr));
पूर्ण

अटल अंतरभूत व्योम rdma_get_mcast_mac(काष्ठा in6_addr *addr, u8 *mac)
अणु
	पूर्णांक i;

	mac[0] = 0x33;
	mac[1] = 0x33;
	क्रम (i = 2; i < 6; ++i)
		mac[i] = addr->s6_addr[i + 10];
पूर्ण

अटल अंतरभूत u16 rdma_get_vlan_id(जोड़ ib_gid *dgid)
अणु
	u16 vid;

	vid = dgid->raw[11] << 8 | dgid->raw[12];
	वापस vid < 0x1000 ? vid : 0xffff;
पूर्ण

अटल अंतरभूत काष्ठा net_device *rdma_vlan_dev_real_dev(स्थिर काष्ठा net_device *dev)
अणु
	वापस is_vlan_dev(dev) ? vlan_dev_real_dev(dev) : शून्य;
पूर्ण

#पूर्ण_अगर /* IB_ADDR_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_VXLAN_H
#घोषणा __NET_VXLAN_H 1

#समावेश <linux/अगर_vlan.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/चयनdev.h>
#समावेश <net/nexthop.h>

#घोषणा IANA_VXLAN_UDP_PORT     4789

/* VXLAN protocol (RFC 7348) header:
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |R|R|R|R|I|R|R|R|               Reserved                        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                VXLAN Network Identअगरier (VNI) |   Reserved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * I = VXLAN Network Identअगरier (VNI) present.
 */
काष्ठा vxlanhdr अणु
	__be32 vx_flags;
	__be32 vx_vni;
पूर्ण;

/* VXLAN header flags. */
#घोषणा VXLAN_HF_VNI	cpu_to_be32(BIT(27))

#घोषणा VXLAN_N_VID     (1u << 24)
#घोषणा VXLAN_VID_MASK  (VXLAN_N_VID - 1)
#घोषणा VXLAN_VNI_MASK	cpu_to_be32(VXLAN_VID_MASK << 8)
#घोषणा VXLAN_HLEN (माप(काष्ठा udphdr) + माप(काष्ठा vxlanhdr))

#घोषणा VNI_HASH_BITS	10
#घोषणा VNI_HASH_SIZE	(1<<VNI_HASH_BITS)
#घोषणा FDB_HASH_BITS	8
#घोषणा FDB_HASH_SIZE	(1<<FDB_HASH_BITS)

/* Remote checksum offload क्रम VXLAN (VXLAN_F_REMCSUM_[RT]X):
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |R|R|R|R|I|R|R|R|R|R|C|              Reserved                   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           VXLAN Network Identअगरier (VNI)      |O| Csum start  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * C = Remote checksum offload bit. When set indicates that the
 *     remote checksum offload data is present.
 *
 * O = Offset bit. Indicates the checksum offset relative to
 *     checksum start.
 *
 * Csum start = Checksum start भागided by two.
 *
 * http://tools.ietf.org/hपंचांगl/draft-herbert-vxlan-rco
 */

/* VXLAN-RCO header flags. */
#घोषणा VXLAN_HF_RCO	cpu_to_be32(BIT(21))

/* Remote checksum offload header option */
#घोषणा VXLAN_RCO_MASK	cpu_to_be32(0x7f)  /* Last byte of vni field */
#घोषणा VXLAN_RCO_UDP	cpu_to_be32(0x80)  /* Indicate UDP RCO (TCP when not set *) */
#घोषणा VXLAN_RCO_SHIFT	1		   /* Left shअगरt of start */
#घोषणा VXLAN_RCO_SHIFT_MASK ((1 << VXLAN_RCO_SHIFT) - 1)
#घोषणा VXLAN_MAX_REMCSUM_START (0x7f << VXLAN_RCO_SHIFT)

/*
 * VXLAN Group Based Policy Extension (VXLAN_F_GBP):
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |G|R|R|R|I|R|R|R|R|D|R|R|A|R|R|R|        Group Policy ID        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                VXLAN Network Identअगरier (VNI) |   Reserved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * G = Group Policy ID present.
 *
 * D = Don't Learn bit. When set, this bit indicates that the egress
 *     VTEP MUST NOT learn the source address of the encapsulated frame.
 *
 * A = Indicates that the group policy has alपढ़ोy been applied to
 *     this packet. Policies MUST NOT be applied by devices when the
 *     A bit is set.
 *
 * https://tools.ietf.org/hपंचांगl/draft-smith-vxlan-group-policy
 */
काष्ठा vxlanhdr_gbp अणु
	u8	vx_flags;
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
	u8	reserved_flags1:3,
		policy_applied:1,
		reserved_flags2:2,
		करोnt_learn:1,
		reserved_flags3:1;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	u8	reserved_flags1:1,
		करोnt_learn:1,
		reserved_flags2:2,
		policy_applied:1,
		reserved_flags3:3;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__be16	policy_id;
	__be32	vx_vni;
पूर्ण;

/* VXLAN-GBP header flags. */
#घोषणा VXLAN_HF_GBP	cpu_to_be32(BIT(31))

#घोषणा VXLAN_GBP_USED_BITS (VXLAN_HF_GBP | cpu_to_be32(0xFFFFFF))

/* skb->mark mapping
 *
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |R|R|R|R|R|R|R|R|R|D|R|R|A|R|R|R|        Group Policy ID        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#घोषणा VXLAN_GBP_DONT_LEARN		(BIT(6) << 16)
#घोषणा VXLAN_GBP_POLICY_APPLIED	(BIT(3) << 16)
#घोषणा VXLAN_GBP_ID_MASK		(0xFFFF)

#घोषणा VXLAN_GBP_MASK (VXLAN_GBP_DONT_LEARN | VXLAN_GBP_POLICY_APPLIED | \
			VXLAN_GBP_ID_MASK)

/*
 * VXLAN Generic Protocol Extension (VXLAN_F_GPE):
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |R|R|Ver|I|P|R|O|       Reserved                |Next Protocol  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                VXLAN Network Identअगरier (VNI) |   Reserved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Ver = Version. Indicates VXLAN GPE protocol version.
 *
 * P = Next Protocol Bit. The P bit is set to indicate that the
 *     Next Protocol field is present.
 *
 * O = OAM Flag Bit. The O bit is set to indicate that the packet
 *     is an OAM packet.
 *
 * Next Protocol = This 8 bit field indicates the protocol header
 * immediately following the VXLAN GPE header.
 *
 * https://tools.ietf.org/hपंचांगl/draft-ietf-nvo3-vxlan-gpe-01
 */

काष्ठा vxlanhdr_gpe अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8	oam_flag:1,
		reserved_flags1:1,
		np_applied:1,
		instance_applied:1,
		version:2,
		reserved_flags2:2;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	u8	reserved_flags2:2,
		version:2,
		instance_applied:1,
		np_applied:1,
		reserved_flags1:1,
		oam_flag:1;
#पूर्ण_अगर
	u8	reserved_flags3;
	u8	reserved_flags4;
	u8	next_protocol;
	__be32	vx_vni;
पूर्ण;

/* VXLAN-GPE header flags. */
#घोषणा VXLAN_HF_VER	cpu_to_be32(BIT(29) | BIT(28))
#घोषणा VXLAN_HF_NP	cpu_to_be32(BIT(26))
#घोषणा VXLAN_HF_OAM	cpu_to_be32(BIT(24))

#घोषणा VXLAN_GPE_USED_BITS (VXLAN_HF_VER | VXLAN_HF_NP | VXLAN_HF_OAM | \
			     cpu_to_be32(0xff))

काष्ठा vxlan_metadata अणु
	u32		gbp;
पूर्ण;

/* per UDP socket inक्रमmation */
काष्ठा vxlan_sock अणु
	काष्ठा hlist_node hlist;
	काष्ठा socket	 *sock;
	काष्ठा hlist_head vni_list[VNI_HASH_SIZE];
	refcount_t	  refcnt;
	u32		  flags;
पूर्ण;

जोड़ vxlan_addr अणु
	काष्ठा sockaddr_in sin;
	काष्ठा sockaddr_in6 sin6;
	काष्ठा sockaddr sa;
पूर्ण;

काष्ठा vxlan_rdst अणु
	जोड़ vxlan_addr	 remote_ip;
	__be16			 remote_port;
	u8			 offloaded:1;
	__be32			 remote_vni;
	u32			 remote_अगरindex;
	काष्ठा net_device	 *remote_dev;
	काष्ठा list_head	 list;
	काष्ठा rcu_head		 rcu;
	काष्ठा dst_cache	 dst_cache;
पूर्ण;

काष्ठा vxlan_config अणु
	जोड़ vxlan_addr	remote_ip;
	जोड़ vxlan_addr	saddr;
	__be32			vni;
	पूर्णांक			remote_अगरindex;
	पूर्णांक			mtu;
	__be16			dst_port;
	u16			port_min;
	u16			port_max;
	u8			tos;
	u8			ttl;
	__be32			label;
	u32			flags;
	अचिन्हित दीर्घ		age_पूर्णांकerval;
	अचिन्हित पूर्णांक		addrmax;
	bool			no_share;
	क्रमागत अगरla_vxlan_df	df;
पूर्ण;

काष्ठा vxlan_dev_node अणु
	काष्ठा hlist_node hlist;
	काष्ठा vxlan_dev *vxlan;
पूर्ण;

/* Pseuकरो network device */
काष्ठा vxlan_dev अणु
	काष्ठा vxlan_dev_node hlist4;	/* vni hash table क्रम IPv4 socket */
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा vxlan_dev_node hlist6;	/* vni hash table क्रम IPv6 socket */
#पूर्ण_अगर
	काष्ठा list_head  next;		/* vxlan's per namespace list */
	काष्ठा vxlan_sock __rcu *vn4_sock;	/* listening socket क्रम IPv4 */
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा vxlan_sock __rcu *vn6_sock;	/* listening socket क्रम IPv6 */
#पूर्ण_अगर
	काष्ठा net_device *dev;
	काष्ठा net	  *net;		/* netns क्रम packet i/o */
	काष्ठा vxlan_rdst शेष_dst;	/* शेष destination */

	काष्ठा समयr_list age_समयr;
	spinlock_t	  hash_lock[FDB_HASH_SIZE];
	अचिन्हित पूर्णांक	  addrcnt;
	काष्ठा gro_cells  gro_cells;

	काष्ठा vxlan_config	cfg;

	काष्ठा hlist_head fdb_head[FDB_HASH_SIZE];
पूर्ण;

#घोषणा VXLAN_F_LEARN			0x01
#घोषणा VXLAN_F_PROXY			0x02
#घोषणा VXLAN_F_RSC			0x04
#घोषणा VXLAN_F_L2MISS			0x08
#घोषणा VXLAN_F_L3MISS			0x10
#घोषणा VXLAN_F_IPV6			0x20
#घोषणा VXLAN_F_UDP_ZERO_CSUM_TX	0x40
#घोषणा VXLAN_F_UDP_ZERO_CSUM6_TX	0x80
#घोषणा VXLAN_F_UDP_ZERO_CSUM6_RX	0x100
#घोषणा VXLAN_F_REMCSUM_TX		0x200
#घोषणा VXLAN_F_REMCSUM_RX		0x400
#घोषणा VXLAN_F_GBP			0x800
#घोषणा VXLAN_F_REMCSUM_NOPARTIAL	0x1000
#घोषणा VXLAN_F_COLLECT_METADATA	0x2000
#घोषणा VXLAN_F_GPE			0x4000
#घोषणा VXLAN_F_IPV6_LINKLOCAL		0x8000
#घोषणा VXLAN_F_TTL_INHERIT		0x10000

/* Flags that are used in the receive path. These flags must match in
 * order क्रम a socket to be shareable
 */
#घोषणा VXLAN_F_RCV_FLAGS		(VXLAN_F_GBP |			\
					 VXLAN_F_GPE |			\
					 VXLAN_F_UDP_ZERO_CSUM6_RX |	\
					 VXLAN_F_REMCSUM_RX |		\
					 VXLAN_F_REMCSUM_NOPARTIAL |	\
					 VXLAN_F_COLLECT_METADATA)

/* Flags that can be set together with VXLAN_F_GPE. */
#घोषणा VXLAN_F_ALLOWED_GPE		(VXLAN_F_GPE |			\
					 VXLAN_F_IPV6 |			\
					 VXLAN_F_IPV6_LINKLOCAL |	\
					 VXLAN_F_UDP_ZERO_CSUM_TX |	\
					 VXLAN_F_UDP_ZERO_CSUM6_TX |	\
					 VXLAN_F_UDP_ZERO_CSUM6_RX |	\
					 VXLAN_F_COLLECT_METADATA)

काष्ठा net_device *vxlan_dev_create(काष्ठा net *net, स्थिर अक्षर *name,
				    u8 name_assign_type, काष्ठा vxlan_config *conf);

अटल अंतरभूत netdev_features_t vxlan_features_check(काष्ठा sk_buff *skb,
						     netdev_features_t features)
अणु
	u8 l4_hdr = 0;

	अगर (!skb->encapsulation)
		वापस features;

	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IP):
		l4_hdr = ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		l4_hdr = ipv6_hdr(skb)->nexthdr;
		अवरोध;
	शेष:
		वापस features;
	पूर्ण

	अगर ((l4_hdr == IPPROTO_UDP) &&
	    (skb->inner_protocol_type != ENCAP_TYPE_ETHER ||
	     skb->inner_protocol != htons(ETH_P_TEB) ||
	     (skb_inner_mac_header(skb) - skb_transport_header(skb) !=
	      माप(काष्ठा udphdr) + माप(काष्ठा vxlanhdr)) ||
	     (skb->ip_summed != CHECKSUM_NONE &&
	      !can_checksum_protocol(features, inner_eth_hdr(skb)->h_proto))))
		वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);

	वापस features;
पूर्ण

/* IP header + UDP + VXLAN + Ethernet header */
#घोषणा VXLAN_HEADROOM (20 + 8 + 8 + 14)
/* IPv6 header + UDP + VXLAN + Ethernet header */
#घोषणा VXLAN6_HEADROOM (40 + 8 + 8 + 14)

अटल अंतरभूत काष्ठा vxlanhdr *vxlan_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा vxlanhdr *)(udp_hdr(skb) + 1);
पूर्ण

अटल अंतरभूत __be32 vxlan_vni(__be32 vni_field)
अणु
#अगर defined(__BIG_ENDIAN)
	वापस (__क्रमce __be32)((__क्रमce u32)vni_field >> 8);
#अन्यथा
	वापस (__क्रमce __be32)((__क्रमce u32)(vni_field & VXLAN_VNI_MASK) << 8);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __be32 vxlan_vni_field(__be32 vni)
अणु
#अगर defined(__BIG_ENDIAN)
	वापस (__क्रमce __be32)((__क्रमce u32)vni << 8);
#अन्यथा
	वापस (__क्रमce __be32)((__क्रमce u32)vni >> 8);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत माप_प्रकार vxlan_rco_start(__be32 vni_field)
अणु
	वापस be32_to_cpu(vni_field & VXLAN_RCO_MASK) << VXLAN_RCO_SHIFT;
पूर्ण

अटल अंतरभूत माप_प्रकार vxlan_rco_offset(__be32 vni_field)
अणु
	वापस (vni_field & VXLAN_RCO_UDP) ?
		दुरत्व(काष्ठा udphdr, check) :
		दुरत्व(काष्ठा tcphdr, check);
पूर्ण

अटल अंतरभूत __be32 vxlan_compute_rco(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक offset)
अणु
	__be32 vni_field = cpu_to_be32(start >> VXLAN_RCO_SHIFT);

	अगर (offset == दुरत्व(काष्ठा udphdr, check))
		vni_field |= VXLAN_RCO_UDP;
	वापस vni_field;
पूर्ण

अटल अंतरभूत अचिन्हित लघु vxlan_get_sk_family(काष्ठा vxlan_sock *vs)
अणु
	वापस vs->sock->sk->sk_family;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)

अटल अंतरभूत bool vxlan_addr_any(स्थिर जोड़ vxlan_addr *ipa)
अणु
	अगर (ipa->sa.sa_family == AF_INET6)
		वापस ipv6_addr_any(&ipa->sin6.sin6_addr);
	अन्यथा
		वापस ipa->sin.sin_addr.s_addr == htonl(INADDR_ANY);
पूर्ण

अटल अंतरभूत bool vxlan_addr_multicast(स्थिर जोड़ vxlan_addr *ipa)
अणु
	अगर (ipa->sa.sa_family == AF_INET6)
		वापस ipv6_addr_is_multicast(&ipa->sin6.sin6_addr);
	अन्यथा
		वापस ipv4_is_multicast(ipa->sin.sin_addr.s_addr);
पूर्ण

#अन्यथा /* !IS_ENABLED(CONFIG_IPV6) */

अटल अंतरभूत bool vxlan_addr_any(स्थिर जोड़ vxlan_addr *ipa)
अणु
	वापस ipa->sin.sin_addr.s_addr == htonl(INADDR_ANY);
पूर्ण

अटल अंतरभूत bool vxlan_addr_multicast(स्थिर जोड़ vxlan_addr *ipa)
अणु
	वापस ipv4_is_multicast(ipa->sin.sin_addr.s_addr);
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */

अटल अंतरभूत bool netअगर_is_vxlan(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->rtnl_link_ops &&
	       !म_भेद(dev->rtnl_link_ops->kind, "vxlan");
पूर्ण

काष्ठा चयनdev_notअगरier_vxlan_fdb_info अणु
	काष्ठा चयनdev_notअगरier_info info; /* must be first */
	जोड़ vxlan_addr remote_ip;
	__be16 remote_port;
	__be32 remote_vni;
	u32 remote_अगरindex;
	u8 eth_addr[ETH_ALEN];
	__be32 vni;
	bool offloaded;
	bool added_by_user;
पूर्ण;

#अगर IS_ENABLED(CONFIG_VXLAN)
पूर्णांक vxlan_fdb_find_uc(काष्ठा net_device *dev, स्थिर u8 *mac, __be32 vni,
		      काष्ठा चयनdev_notअगरier_vxlan_fdb_info *fdb_info);
पूर्णांक vxlan_fdb_replay(स्थिर काष्ठा net_device *dev, __be32 vni,
		     काष्ठा notअगरier_block *nb,
		     काष्ठा netlink_ext_ack *extack);
व्योम vxlan_fdb_clear_offload(स्थिर काष्ठा net_device *dev, __be32 vni);

#अन्यथा
अटल अंतरभूत पूर्णांक
vxlan_fdb_find_uc(काष्ठा net_device *dev, स्थिर u8 *mac, __be32 vni,
		  काष्ठा चयनdev_notअगरier_vxlan_fdb_info *fdb_info)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत पूर्णांक vxlan_fdb_replay(स्थिर काष्ठा net_device *dev, __be32 vni,
				   काष्ठा notअगरier_block *nb,
				   काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम
vxlan_fdb_clear_offload(स्थिर काष्ठा net_device *dev, __be32 vni)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम vxlan_flag_attr_error(पूर्णांक attrtype,
					 काष्ठा netlink_ext_ack *extack)
अणु
#घोषणा VXLAN_FLAG(flg) \
	हाल IFLA_VXLAN_##flg: \
		NL_SET_ERR_MSG_MOD(extack, \
				   "cannot change " #flg " flag"); \
		अवरोध
	चयन (attrtype) अणु
	VXLAN_FLAG(TTL_INHERIT);
	VXLAN_FLAG(LEARNING);
	VXLAN_FLAG(PROXY);
	VXLAN_FLAG(RSC);
	VXLAN_FLAG(L2MISS);
	VXLAN_FLAG(L3MISS);
	VXLAN_FLAG(COLLECT_METADATA);
	VXLAN_FLAG(UDP_ZERO_CSUM6_TX);
	VXLAN_FLAG(UDP_ZERO_CSUM6_RX);
	VXLAN_FLAG(REMCSUM_TX);
	VXLAN_FLAG(REMCSUM_RX);
	VXLAN_FLAG(GBP);
	VXLAN_FLAG(GPE);
	VXLAN_FLAG(REMCSUM_NOPARTIAL);
	शेष:
		NL_SET_ERR_MSG_MOD(extack, \
				   "cannot change flag");
		अवरोध;
	पूर्ण
#अघोषित VXLAN_FLAG
पूर्ण

अटल अंतरभूत bool vxlan_fdb_nh_path_select(काष्ठा nexthop *nh,
					    पूर्णांक hash,
					    काष्ठा vxlan_rdst *rdst)
अणु
	काष्ठा fib_nh_common *nhc;

	nhc = nexthop_path_fdb_result(nh, hash);
	अगर (unlikely(!nhc))
		वापस false;

	चयन (nhc->nhc_gw_family) अणु
	हाल AF_INET:
		rdst->remote_ip.sin.sin_addr.s_addr = nhc->nhc_gw.ipv4;
		rdst->remote_ip.sa.sa_family = AF_INET;
		अवरोध;
	हाल AF_INET6:
		rdst->remote_ip.sin6.sin6_addr = nhc->nhc_gw.ipv6;
		rdst->remote_ip.sa.sa_family = AF_INET6;
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

#पूर्ण_अगर

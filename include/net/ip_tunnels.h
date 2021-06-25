<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_IP_TUNNELS_H
#घोषणा __NET_IP_TUNNELS_H 1

#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/types.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/bitops.h>

#समावेश <net/dsfield.h>
#समावेश <net/gro_cells.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/netns/generic.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/dst_cache.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ipv6.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>
#पूर्ण_अगर

/* Keep error state on tunnel क्रम 30 sec */
#घोषणा IPTUNNEL_ERR_TIMEO	(30*HZ)

/* Used to स_रखो ip_tunnel padding. */
#घोषणा IP_TUNNEL_KEY_SIZE	दुरत्वend(काष्ठा ip_tunnel_key, tp_dst)

/* Used to स_रखो ipv4 address padding. */
#घोषणा IP_TUNNEL_KEY_IPV4_PAD	दुरत्वend(काष्ठा ip_tunnel_key, u.ipv4.dst)
#घोषणा IP_TUNNEL_KEY_IPV4_PAD_LEN				\
	(माप_field(काष्ठा ip_tunnel_key, u) -		\
	 माप_field(काष्ठा ip_tunnel_key, u.ipv4))

काष्ठा ip_tunnel_key अणु
	__be64			tun_id;
	जोड़ अणु
		काष्ठा अणु
			__be32	src;
			__be32	dst;
		पूर्ण ipv4;
		काष्ठा अणु
			काष्ठा in6_addr src;
			काष्ठा in6_addr dst;
		पूर्ण ipv6;
	पूर्ण u;
	__be16			tun_flags;
	u8			tos;		/* TOS क्रम IPv4, TC क्रम IPv6 */
	u8			ttl;		/* TTL क्रम IPv4, HL क्रम IPv6 */
	__be32			label;		/* Flow Label क्रम IPv6 */
	__be16			tp_src;
	__be16			tp_dst;
पूर्ण;

/* Flags क्रम ip_tunnel_info mode. */
#घोषणा IP_TUNNEL_INFO_TX	0x01	/* represents tx tunnel parameters */
#घोषणा IP_TUNNEL_INFO_IPV6	0x02	/* key contains IPv6 addresses */
#घोषणा IP_TUNNEL_INFO_BRIDGE	0x04	/* represents a bridged tunnel id */

/* Maximum tunnel options length. */
#घोषणा IP_TUNNEL_OPTS_MAX					\
	GENMASK((माप_field(काष्ठा ip_tunnel_info,		\
			      options_len) * BITS_PER_BYTE) - 1, 0)

काष्ठा ip_tunnel_info अणु
	काष्ठा ip_tunnel_key	key;
#अगर_घोषित CONFIG_DST_CACHE
	काष्ठा dst_cache	dst_cache;
#पूर्ण_अगर
	u8			options_len;
	u8			mode;
पूर्ण;

/* 6rd prefix/relay inक्रमmation */
#अगर_घोषित CONFIG_IPV6_SIT_6RD
काष्ठा ip_tunnel_6rd_parm अणु
	काष्ठा in6_addr		prefix;
	__be32			relay_prefix;
	u16			prefixlen;
	u16			relay_prefixlen;
पूर्ण;
#पूर्ण_अगर

काष्ठा ip_tunnel_encap अणु
	u16			type;
	u16			flags;
	__be16			sport;
	__be16			dport;
पूर्ण;

काष्ठा ip_tunnel_prl_entry अणु
	काष्ठा ip_tunnel_prl_entry __rcu *next;
	__be32				addr;
	u16				flags;
	काष्ठा rcu_head			rcu_head;
पूर्ण;

काष्ठा metadata_dst;

काष्ठा ip_tunnel अणु
	काष्ठा ip_tunnel __rcu	*next;
	काष्ठा hlist_node hash_node;
	काष्ठा net_device	*dev;
	काष्ठा net		*net;	/* netns क्रम packet i/o */

	अचिन्हित दीर्घ	err_समय;	/* Time when the last ICMP error
					 * arrived */
	पूर्णांक		err_count;	/* Number of arrived ICMP errors */

	/* These four fields used only by GRE */
	u32		i_seqno;	/* The last seen seqno	*/
	u32		o_seqno;	/* The last output seqno */
	पूर्णांक		tun_hlen;	/* Precalculated header length */

	/* These four fields used only by ERSPAN */
	u32		index;		/* ERSPAN type II index */
	u8		erspan_ver;	/* ERSPAN version */
	u8		dir;		/* ERSPAN direction */
	u16		hwid;		/* ERSPAN hardware ID */

	काष्ठा dst_cache dst_cache;

	काष्ठा ip_tunnel_parm parms;

	पूर्णांक		mlink;
	पूर्णांक		encap_hlen;	/* Encap header length (FOU,GUE) */
	पूर्णांक		hlen;		/* tun_hlen + encap_hlen */
	काष्ठा ip_tunnel_encap encap;

	/* क्रम SIT */
#अगर_घोषित CONFIG_IPV6_SIT_6RD
	काष्ठा ip_tunnel_6rd_parm ip6rd;
#पूर्ण_अगर
	काष्ठा ip_tunnel_prl_entry __rcu *prl;	/* potential router list */
	अचिन्हित पूर्णांक		prl_count;	/* # of entries in PRL */
	अचिन्हित पूर्णांक		ip_tnl_net_id;
	काष्ठा gro_cells	gro_cells;
	__u32			fwmark;
	bool			collect_md;
	bool			ignore_df;
पूर्ण;

काष्ठा tnl_ptk_info अणु
	__be16 flags;
	__be16 proto;
	__be32 key;
	__be32 seq;
	पूर्णांक hdr_len;
पूर्ण;

#घोषणा PACKET_RCVD	0
#घोषणा PACKET_REJECT	1
#घोषणा PACKET_NEXT	2

#घोषणा IP_TNL_HASH_BITS   7
#घोषणा IP_TNL_HASH_SIZE   (1 << IP_TNL_HASH_BITS)

काष्ठा ip_tunnel_net अणु
	काष्ठा net_device *fb_tunnel_dev;
	काष्ठा rtnl_link_ops *rtnl_link_ops;
	काष्ठा hlist_head tunnels[IP_TNL_HASH_SIZE];
	काष्ठा ip_tunnel __rcu *collect_md_tun;
	पूर्णांक type;
पूर्ण;

अटल अंतरभूत व्योम ip_tunnel_key_init(काष्ठा ip_tunnel_key *key,
				      __be32 saddr, __be32 daddr,
				      u8 tos, u8 ttl, __be32 label,
				      __be16 tp_src, __be16 tp_dst,
				      __be64 tun_id, __be16 tun_flags)
अणु
	key->tun_id = tun_id;
	key->u.ipv4.src = saddr;
	key->u.ipv4.dst = daddr;
	स_रखो((अचिन्हित अक्षर *)key + IP_TUNNEL_KEY_IPV4_PAD,
	       0, IP_TUNNEL_KEY_IPV4_PAD_LEN);
	key->tos = tos;
	key->ttl = ttl;
	key->label = label;
	key->tun_flags = tun_flags;

	/* For the tunnel types on the top of IPsec, the tp_src and tp_dst of
	 * the upper tunnel are used.
	 * E.g: GRE over IPSEC, the tp_src and tp_port are zero.
	 */
	key->tp_src = tp_src;
	key->tp_dst = tp_dst;

	/* Clear काष्ठा padding. */
	अगर (माप(*key) != IP_TUNNEL_KEY_SIZE)
		स_रखो((अचिन्हित अक्षर *)key + IP_TUNNEL_KEY_SIZE,
		       0, माप(*key) - IP_TUNNEL_KEY_SIZE);
पूर्ण

अटल अंतरभूत bool
ip_tunnel_dst_cache_usable(स्थिर काष्ठा sk_buff *skb,
			   स्थिर काष्ठा ip_tunnel_info *info)
अणु
	अगर (skb->mark)
		वापस false;
	अगर (!info)
		वापस true;
	अगर (info->key.tun_flags & TUNNEL_NOCACHE)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित लघु ip_tunnel_info_af(स्थिर काष्ठा ip_tunnel_info
					       *tun_info)
अणु
	वापस tun_info->mode & IP_TUNNEL_INFO_IPV6 ? AF_INET6 : AF_INET;
पूर्ण

अटल अंतरभूत __be64 key32_to_tunnel_id(__be32 key)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस (__क्रमce __be64)key;
#अन्यथा
	वापस (__क्रमce __be64)((__क्रमce u64)key << 32);
#पूर्ण_अगर
पूर्ण

/* Returns the least-signअगरicant 32 bits of a __be64. */
अटल अंतरभूत __be32 tunnel_id_to_key32(__be64 tun_id)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस (__क्रमce __be32)tun_id;
#अन्यथा
	वापस (__क्रमce __be32)((__क्रमce u64)tun_id >> 32);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_INET

अटल अंतरभूत व्योम ip_tunnel_init_flow(काष्ठा flowi4 *fl4,
				       पूर्णांक proto,
				       __be32 daddr, __be32 saddr,
				       __be32 key, __u8 tos, पूर्णांक oअगर,
				       __u32 mark, __u32 tun_inner_hash)
अणु
	स_रखो(fl4, 0, माप(*fl4));
	fl4->flowi4_oअगर = oअगर;
	fl4->daddr = daddr;
	fl4->saddr = saddr;
	fl4->flowi4_tos = tos;
	fl4->flowi4_proto = proto;
	fl4->fl4_gre_key = key;
	fl4->flowi4_mark = mark;
	fl4->flowi4_multipath_hash = tun_inner_hash;
पूर्ण

पूर्णांक ip_tunnel_init(काष्ठा net_device *dev);
व्योम ip_tunnel_uninit(काष्ठा net_device *dev);
व्योम  ip_tunnel_dellink(काष्ठा net_device *dev, काष्ठा list_head *head);
काष्ठा net *ip_tunnel_get_link_net(स्थिर काष्ठा net_device *dev);
पूर्णांक ip_tunnel_get_अगरlink(स्थिर काष्ठा net_device *dev);
पूर्णांक ip_tunnel_init_net(काष्ठा net *net, अचिन्हित पूर्णांक ip_tnl_net_id,
		       काष्ठा rtnl_link_ops *ops, अक्षर *devname);

व्योम ip_tunnel_delete_nets(काष्ठा list_head *list_net, अचिन्हित पूर्णांक id,
			   काष्ठा rtnl_link_ops *ops);

व्योम ip_tunnel_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		    स्थिर काष्ठा iphdr *tnl_params, स्थिर u8 protocol);
व्योम ip_md_tunnel_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       स्थिर u8 proto, पूर्णांक tunnel_hlen);
पूर्णांक ip_tunnel_ctl(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p, पूर्णांक cmd);
पूर्णांक ip_tunnel_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
पूर्णांक __ip_tunnel_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu, bool strict);
पूर्णांक ip_tunnel_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);

काष्ठा ip_tunnel *ip_tunnel_lookup(काष्ठा ip_tunnel_net *itn,
				   पूर्णांक link, __be16 flags,
				   __be32 remote, __be32 local,
				   __be32 key);

पूर्णांक ip_tunnel_rcv(काष्ठा ip_tunnel *tunnel, काष्ठा sk_buff *skb,
		  स्थिर काष्ठा tnl_ptk_info *tpi, काष्ठा metadata_dst *tun_dst,
		  bool log_ecn_error);
पूर्णांक ip_tunnel_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			 काष्ठा ip_tunnel_parm *p, __u32 fwmark);
पूर्णांक ip_tunnel_newlink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
		      काष्ठा ip_tunnel_parm *p, __u32 fwmark);
व्योम ip_tunnel_setup(काष्ठा net_device *dev, अचिन्हित पूर्णांक net_id);

बाह्य स्थिर काष्ठा header_ops ip_tunnel_header_ops;
__be16 ip_tunnel_parse_protocol(स्थिर काष्ठा sk_buff *skb);

काष्ठा ip_tunnel_encap_ops अणु
	माप_प्रकार (*encap_hlen)(काष्ठा ip_tunnel_encap *e);
	पूर्णांक (*build_header)(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
			    u8 *protocol, काष्ठा flowi4 *fl4);
	पूर्णांक (*err_handler)(काष्ठा sk_buff *skb, u32 info);
पूर्ण;

#घोषणा MAX_IPTUN_ENCAP_OPS 8

बाह्य स्थिर काष्ठा ip_tunnel_encap_ops __rcu *
		iptun_encaps[MAX_IPTUN_ENCAP_OPS];

पूर्णांक ip_tunnel_encap_add_ops(स्थिर काष्ठा ip_tunnel_encap_ops *op,
			    अचिन्हित पूर्णांक num);
पूर्णांक ip_tunnel_encap_del_ops(स्थिर काष्ठा ip_tunnel_encap_ops *op,
			    अचिन्हित पूर्णांक num);

पूर्णांक ip_tunnel_encap_setup(काष्ठा ip_tunnel *t,
			  काष्ठा ip_tunnel_encap *ipencap);

अटल अंतरभूत bool pskb_inet_may_pull(काष्ठा sk_buff *skb)
अणु
	पूर्णांक nhlen;

	चयन (skb->protocol) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		nhlen = माप(काष्ठा ipv6hdr);
		अवरोध;
#पूर्ण_अगर
	हाल htons(ETH_P_IP):
		nhlen = माप(काष्ठा iphdr);
		अवरोध;
	शेष:
		nhlen = 0;
	पूर्ण

	वापस pskb_network_may_pull(skb, nhlen);
पूर्ण

अटल अंतरभूत पूर्णांक ip_encap_hlen(काष्ठा ip_tunnel_encap *e)
अणु
	स्थिर काष्ठा ip_tunnel_encap_ops *ops;
	पूर्णांक hlen = -EINVAL;

	अगर (e->type == TUNNEL_ENCAP_NONE)
		वापस 0;

	अगर (e->type >= MAX_IPTUN_ENCAP_OPS)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(iptun_encaps[e->type]);
	अगर (likely(ops && ops->encap_hlen))
		hlen = ops->encap_hlen(e);
	rcu_पढ़ो_unlock();

	वापस hlen;
पूर्ण

अटल अंतरभूत पूर्णांक ip_tunnel_encap(काष्ठा sk_buff *skb, काष्ठा ip_tunnel *t,
				  u8 *protocol, काष्ठा flowi4 *fl4)
अणु
	स्थिर काष्ठा ip_tunnel_encap_ops *ops;
	पूर्णांक ret = -EINVAL;

	अगर (t->encap.type == TUNNEL_ENCAP_NONE)
		वापस 0;

	अगर (t->encap.type >= MAX_IPTUN_ENCAP_OPS)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(iptun_encaps[t->encap.type]);
	अगर (likely(ops && ops->build_header))
		ret = ops->build_header(skb, &t->encap, protocol, fl4);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* Extract dsfield from inner protocol */
अटल अंतरभूत u8 ip_tunnel_get_dsfield(स्थिर काष्ठा iphdr *iph,
				       स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP))
		वापस iph->tos;
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		वापस ipv6_get_dsfield((स्थिर काष्ठा ipv6hdr *)iph);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत u8 ip_tunnel_get_ttl(स्थिर काष्ठा iphdr *iph,
				       स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP))
		वापस iph->ttl;
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		वापस ((स्थिर काष्ठा ipv6hdr *)iph)->hop_limit;
	अन्यथा
		वापस 0;
पूर्ण

/* Propogate ECN bits out */
अटल अंतरभूत u8 ip_tunnel_ecn_encap(u8 tos, स्थिर काष्ठा iphdr *iph,
				     स्थिर काष्ठा sk_buff *skb)
अणु
	u8 inner = ip_tunnel_get_dsfield(iph, skb);

	वापस INET_ECN_encapsulate(tos, inner);
पूर्ण

पूर्णांक __iptunnel_pull_header(काष्ठा sk_buff *skb, पूर्णांक hdr_len,
			   __be16 inner_proto, bool raw_proto, bool xnet);

अटल अंतरभूत पूर्णांक iptunnel_pull_header(काष्ठा sk_buff *skb, पूर्णांक hdr_len,
				       __be16 inner_proto, bool xnet)
अणु
	वापस __iptunnel_pull_header(skb, hdr_len, inner_proto, false, xnet);
पूर्ण

व्योम iptunnel_xmit(काष्ठा sock *sk, काष्ठा rtable *rt, काष्ठा sk_buff *skb,
		   __be32 src, __be32 dst, u8 proto,
		   u8 tos, u8 ttl, __be16 df, bool xnet);
काष्ठा metadata_dst *iptunnel_metadata_reply(काष्ठा metadata_dst *md,
					     gfp_t flags);
पूर्णांक skb_tunnel_check_pmtu(काष्ठा sk_buff *skb, काष्ठा dst_entry *encap_dst,
			  पूर्णांक headroom, bool reply);

पूर्णांक iptunnel_handle_offloads(काष्ठा sk_buff *skb, पूर्णांक gso_type_mask);

अटल अंतरभूत पूर्णांक iptunnel_pull_offloads(काष्ठा sk_buff *skb)
अणु
	अगर (skb_is_gso(skb)) अणु
		पूर्णांक err;

		err = skb_unclone(skb, GFP_ATOMIC);
		अगर (unlikely(err))
			वापस err;
		skb_shinfo(skb)->gso_type &= ~(NETIF_F_GSO_ENCAP_ALL >>
					       NETIF_F_GSO_SHIFT);
	पूर्ण

	skb->encapsulation = 0;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iptunnel_xmit_stats(काष्ठा net_device *dev, पूर्णांक pkt_len)
अणु
	अगर (pkt_len > 0) अणु
		काष्ठा pcpu_sw_netstats *tstats = get_cpu_ptr(dev->tstats);

		u64_stats_update_begin(&tstats->syncp);
		tstats->tx_bytes += pkt_len;
		tstats->tx_packets++;
		u64_stats_update_end(&tstats->syncp);
		put_cpu_ptr(tstats);
	पूर्ण अन्यथा अणु
		काष्ठा net_device_stats *err_stats = &dev->stats;

		अगर (pkt_len < 0) अणु
			err_stats->tx_errors++;
			err_stats->tx_पातed_errors++;
		पूर्ण अन्यथा अणु
			err_stats->tx_dropped++;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *ip_tunnel_info_opts(काष्ठा ip_tunnel_info *info)
अणु
	वापस info + 1;
पूर्ण

अटल अंतरभूत व्योम ip_tunnel_info_opts_get(व्योम *to,
					   स्थिर काष्ठा ip_tunnel_info *info)
अणु
	स_नकल(to, info + 1, info->options_len);
पूर्ण

अटल अंतरभूत व्योम ip_tunnel_info_opts_set(काष्ठा ip_tunnel_info *info,
					   स्थिर व्योम *from, पूर्णांक len,
					   __be16 flags)
अणु
	info->options_len = len;
	अगर (len > 0) अणु
		स_नकल(ip_tunnel_info_opts(info), from, len);
		info->key.tun_flags |= flags;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा ip_tunnel_info *lwt_tun_info(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस (काष्ठा ip_tunnel_info *)lwtstate->data;
पूर्ण

DECLARE_STATIC_KEY_FALSE(ip_tunnel_metadata_cnt);

/* Returns > 0 अगर metadata should be collected */
अटल अंतरभूत पूर्णांक ip_tunnel_collect_metadata(व्योम)
अणु
	वापस अटल_branch_unlikely(&ip_tunnel_metadata_cnt);
पूर्ण

व्योम __init ip_tunnel_core_init(व्योम);

व्योम ip_tunnel_need_metadata(व्योम);
व्योम ip_tunnel_unneed_metadata(व्योम);

#अन्यथा /* CONFIG_INET */

अटल अंतरभूत काष्ठा ip_tunnel_info *lwt_tun_info(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम ip_tunnel_need_metadata(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम ip_tunnel_unneed_metadata(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम ip_tunnel_info_opts_get(व्योम *to,
					   स्थिर काष्ठा ip_tunnel_info *info)
अणु
पूर्ण

अटल अंतरभूत व्योम ip_tunnel_info_opts_set(काष्ठा ip_tunnel_info *info,
					   स्थिर व्योम *from, पूर्णांक len,
					   __be16 flags)
अणु
	info->options_len = 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_INET */

#पूर्ण_अगर /* __NET_IP_TUNNELS_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_IP6_TUNNEL_H
#घोषणा _NET_IP6_TUNNEL_H

#समावेश <linux/ipv6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/ip6_tunnel.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/dst_cache.h>

#घोषणा IP6TUNNEL_ERR_TIMEO (30*HZ)

/* capable of sending packets */
#घोषणा IP6_TNL_F_CAP_XMIT 0x10000
/* capable of receiving packets */
#घोषणा IP6_TNL_F_CAP_RCV 0x20000
/* determine capability on a per-packet basis */
#घोषणा IP6_TNL_F_CAP_PER_PACKET 0x40000

काष्ठा __ip6_tnl_parm अणु
	अक्षर name[IFNAMSIZ];	/* name of tunnel device */
	पूर्णांक link;		/* अगरindex of underlying L2 पूर्णांकerface */
	__u8 proto;		/* tunnel protocol */
	__u8 encap_limit;	/* encapsulation limit क्रम tunnel */
	__u8 hop_limit;		/* hop limit क्रम tunnel */
	bool collect_md;
	__be32 flowinfo;	/* traffic class and flowlabel क्रम tunnel */
	__u32 flags;		/* tunnel flags */
	काष्ठा in6_addr laddr;	/* local tunnel end-poपूर्णांक address */
	काष्ठा in6_addr raddr;	/* remote tunnel end-poपूर्णांक address */

	__be16			i_flags;
	__be16			o_flags;
	__be32			i_key;
	__be32			o_key;

	__u32			fwmark;
	__u32			index;	/* ERSPAN type II index */
	__u8			erspan_ver;	/* ERSPAN version */
	__u8			dir;	/* direction */
	__u16			hwid;	/* hwid */
पूर्ण;

/* IPv6 tunnel */
काष्ठा ip6_tnl अणु
	काष्ठा ip6_tnl __rcu *next;	/* next tunnel in list */
	काष्ठा net_device *dev;	/* भव device associated with tunnel */
	काष्ठा net *net;	/* netns क्रम packet i/o */
	काष्ठा __ip6_tnl_parm parms;	/* tunnel configuration parameters */
	काष्ठा flowi fl;	/* flowi ढाँचा क्रम xmit */
	काष्ठा dst_cache dst_cache;	/* cached dst */
	काष्ठा gro_cells gro_cells;

	पूर्णांक err_count;
	अचिन्हित दीर्घ err_समय;

	/* These fields used only by GRE */
	__u32 i_seqno;	/* The last seen seqno	*/
	__u32 o_seqno;	/* The last output seqno */
	पूर्णांक hlen;       /* tun_hlen + encap_hlen */
	पूर्णांक tun_hlen;	/* Precalculated header length */
	पूर्णांक encap_hlen; /* Encap header length (FOU,GUE) */
	काष्ठा ip_tunnel_encap encap;
	पूर्णांक mlink;
पूर्ण;

काष्ठा ip6_tnl_encap_ops अणु
	माप_प्रकार (*encap_hlen)(काष्ठा ip_tunnel_encap *e);
	पूर्णांक (*build_header)(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
			    u8 *protocol, काष्ठा flowi6 *fl6);
	पूर्णांक (*err_handler)(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			   u8 type, u8 code, पूर्णांक offset, __be32 info);
पूर्ण;

#अगर_घोषित CONFIG_INET

बाह्य स्थिर काष्ठा ip6_tnl_encap_ops __rcu *
		ip6tun_encaps[MAX_IPTUN_ENCAP_OPS];

पूर्णांक ip6_tnl_encap_add_ops(स्थिर काष्ठा ip6_tnl_encap_ops *ops,
			  अचिन्हित पूर्णांक num);
पूर्णांक ip6_tnl_encap_del_ops(स्थिर काष्ठा ip6_tnl_encap_ops *ops,
			  अचिन्हित पूर्णांक num);
पूर्णांक ip6_tnl_encap_setup(काष्ठा ip6_tnl *t,
			काष्ठा ip_tunnel_encap *ipencap);

अटल अंतरभूत पूर्णांक ip6_encap_hlen(काष्ठा ip_tunnel_encap *e)
अणु
	स्थिर काष्ठा ip6_tnl_encap_ops *ops;
	पूर्णांक hlen = -EINVAL;

	अगर (e->type == TUNNEL_ENCAP_NONE)
		वापस 0;

	अगर (e->type >= MAX_IPTUN_ENCAP_OPS)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(ip6tun_encaps[e->type]);
	अगर (likely(ops && ops->encap_hlen))
		hlen = ops->encap_hlen(e);
	rcu_पढ़ो_unlock();

	वापस hlen;
पूर्ण

अटल अंतरभूत पूर्णांक ip6_tnl_encap(काष्ठा sk_buff *skb, काष्ठा ip6_tnl *t,
				u8 *protocol, काष्ठा flowi6 *fl6)
अणु
	स्थिर काष्ठा ip6_tnl_encap_ops *ops;
	पूर्णांक ret = -EINVAL;

	अगर (t->encap.type == TUNNEL_ENCAP_NONE)
		वापस 0;

	अगर (t->encap.type >= MAX_IPTUN_ENCAP_OPS)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(ip6tun_encaps[t->encap.type]);
	अगर (likely(ops && ops->build_header))
		ret = ops->build_header(skb, &t->encap, protocol, fl6);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* Tunnel encapsulation limit destination sub-option */

काष्ठा ipv6_tlv_tnl_enc_lim अणु
	__u8 type;		/* type-code क्रम option         */
	__u8 length;		/* option length                */
	__u8 encap_limit;	/* tunnel encapsulation limit   */
पूर्ण __packed;

पूर्णांक ip6_tnl_rcv_ctl(काष्ठा ip6_tnl *t, स्थिर काष्ठा in6_addr *laddr,
		स्थिर काष्ठा in6_addr *raddr);
पूर्णांक ip6_tnl_rcv(काष्ठा ip6_tnl *tunnel, काष्ठा sk_buff *skb,
		स्थिर काष्ठा tnl_ptk_info *tpi, काष्ठा metadata_dst *tun_dst,
		bool log_ecn_error);
पूर्णांक ip6_tnl_xmit_ctl(काष्ठा ip6_tnl *t, स्थिर काष्ठा in6_addr *laddr,
		     स्थिर काष्ठा in6_addr *raddr);
पूर्णांक ip6_tnl_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev, __u8 dsfield,
		 काष्ठा flowi6 *fl6, पूर्णांक encap_limit, __u32 *pmtu, __u8 proto);
__u16 ip6_tnl_parse_tlv_enc_lim(काष्ठा sk_buff *skb, __u8 *raw);
__u32 ip6_tnl_get_cap(काष्ठा ip6_tnl *t, स्थिर काष्ठा in6_addr *laddr,
			     स्थिर काष्ठा in6_addr *raddr);
काष्ठा net *ip6_tnl_get_link_net(स्थिर काष्ठा net_device *dev);
पूर्णांक ip6_tnl_get_अगरlink(स्थिर काष्ठा net_device *dev);
पूर्णांक ip6_tnl_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);

अटल अंतरभूत व्योम ip6tunnel_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev)
अणु
	पूर्णांक pkt_len, err;

	स_रखो(skb->cb, 0, माप(काष्ठा inet6_skb_parm));
	pkt_len = skb->len - skb_inner_network_offset(skb);
	err = ip6_local_out(dev_net(skb_dst(skb)->dev), sk, skb);

	अगर (dev) अणु
		अगर (unlikely(net_xmit_eval(err)))
			pkt_len = -1;
		iptunnel_xmit_stats(dev, pkt_len);
	पूर्ण
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

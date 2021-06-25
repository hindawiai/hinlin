<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_DST_METADATA_H
#घोषणा __NET_DST_METADATA_H 1

#समावेश <linux/skbuff.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/dst.h>

क्रमागत metadata_type अणु
	METADATA_IP_TUNNEL,
	METADATA_HW_PORT_MUX,
पूर्ण;

काष्ठा hw_port_info अणु
	काष्ठा net_device *lower_dev;
	u32 port_id;
पूर्ण;

काष्ठा metadata_dst अणु
	काष्ठा dst_entry		dst;
	क्रमागत metadata_type		type;
	जोड़ अणु
		काष्ठा ip_tunnel_info	tun_info;
		काष्ठा hw_port_info	port_info;
	पूर्ण u;
पूर्ण;

अटल अंतरभूत काष्ठा metadata_dst *skb_metadata_dst(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा metadata_dst *md_dst = (काष्ठा metadata_dst *) skb_dst(skb);

	अगर (md_dst && md_dst->dst.flags & DST_METADATA)
		वापस md_dst;

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा ip_tunnel_info *
skb_tunnel_info(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा metadata_dst *md_dst = skb_metadata_dst(skb);
	काष्ठा dst_entry *dst;

	अगर (md_dst && md_dst->type == METADATA_IP_TUNNEL)
		वापस &md_dst->u.tun_info;

	dst = skb_dst(skb);
	अगर (dst && dst->lwtstate)
		वापस lwt_tun_info(dst->lwtstate);

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool skb_valid_dst(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);

	वापस dst && !(dst->flags & DST_METADATA);
पूर्ण

अटल अंतरभूत पूर्णांक skb_metadata_dst_cmp(स्थिर काष्ठा sk_buff *skb_a,
				       स्थिर काष्ठा sk_buff *skb_b)
अणु
	स्थिर काष्ठा metadata_dst *a, *b;

	अगर (!(skb_a->_skb_refdst | skb_b->_skb_refdst))
		वापस 0;

	a = (स्थिर काष्ठा metadata_dst *) skb_dst(skb_a);
	b = (स्थिर काष्ठा metadata_dst *) skb_dst(skb_b);

	अगर (!a != !b || a->type != b->type)
		वापस 1;

	चयन (a->type) अणु
	हाल METADATA_HW_PORT_MUX:
		वापस स_भेद(&a->u.port_info, &b->u.port_info,
			      माप(a->u.port_info));
	हाल METADATA_IP_TUNNEL:
		वापस स_भेद(&a->u.tun_info, &b->u.tun_info,
			      माप(a->u.tun_info) +
					 a->u.tun_info.options_len);
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

व्योम metadata_dst_मुक्त(काष्ठा metadata_dst *);
काष्ठा metadata_dst *metadata_dst_alloc(u8 optslen, क्रमागत metadata_type type,
					gfp_t flags);
व्योम metadata_dst_मुक्त_percpu(काष्ठा metadata_dst __percpu *md_dst);
काष्ठा metadata_dst __percpu *
metadata_dst_alloc_percpu(u8 optslen, क्रमागत metadata_type type, gfp_t flags);

अटल अंतरभूत काष्ठा metadata_dst *tun_rx_dst(पूर्णांक md_size)
अणु
	काष्ठा metadata_dst *tun_dst;

	tun_dst = metadata_dst_alloc(md_size, METADATA_IP_TUNNEL, GFP_ATOMIC);
	अगर (!tun_dst)
		वापस शून्य;

	tun_dst->u.tun_info.options_len = 0;
	tun_dst->u.tun_info.mode = 0;
	वापस tun_dst;
पूर्ण

अटल अंतरभूत काष्ठा metadata_dst *tun_dst_unclone(काष्ठा sk_buff *skb)
अणु
	काष्ठा metadata_dst *md_dst = skb_metadata_dst(skb);
	पूर्णांक md_size;
	काष्ठा metadata_dst *new_md;

	अगर (!md_dst || md_dst->type != METADATA_IP_TUNNEL)
		वापस ERR_PTR(-EINVAL);

	md_size = md_dst->u.tun_info.options_len;
	new_md = metadata_dst_alloc(md_size, METADATA_IP_TUNNEL, GFP_ATOMIC);
	अगर (!new_md)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(&new_md->u.tun_info, &md_dst->u.tun_info,
	       माप(काष्ठा ip_tunnel_info) + md_size);
	skb_dst_drop(skb);
	dst_hold(&new_md->dst);
	skb_dst_set(skb, &new_md->dst);
	वापस new_md;
पूर्ण

अटल अंतरभूत काष्ठा ip_tunnel_info *skb_tunnel_info_unclone(काष्ठा sk_buff *skb)
अणु
	काष्ठा metadata_dst *dst;

	dst = tun_dst_unclone(skb);
	अगर (IS_ERR(dst))
		वापस शून्य;

	वापस &dst->u.tun_info;
पूर्ण

अटल अंतरभूत काष्ठा metadata_dst *__ip_tun_set_dst(__be32 saddr,
						    __be32 daddr,
						    __u8 tos, __u8 ttl,
						    __be16 tp_dst,
						    __be16 flags,
						    __be64 tunnel_id,
						    पूर्णांक md_size)
अणु
	काष्ठा metadata_dst *tun_dst;

	tun_dst = tun_rx_dst(md_size);
	अगर (!tun_dst)
		वापस शून्य;

	ip_tunnel_key_init(&tun_dst->u.tun_info.key,
			   saddr, daddr, tos, ttl,
			   0, 0, tp_dst, tunnel_id, flags);
	वापस tun_dst;
पूर्ण

अटल अंतरभूत काष्ठा metadata_dst *ip_tun_rx_dst(काष्ठा sk_buff *skb,
						 __be16 flags,
						 __be64 tunnel_id,
						 पूर्णांक md_size)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

	वापस __ip_tun_set_dst(iph->saddr, iph->daddr, iph->tos, iph->ttl,
				0, flags, tunnel_id, md_size);
पूर्ण

अटल अंतरभूत काष्ठा metadata_dst *__ipv6_tun_set_dst(स्थिर काष्ठा in6_addr *saddr,
						      स्थिर काष्ठा in6_addr *daddr,
						      __u8 tos, __u8 ttl,
						      __be16 tp_dst,
						      __be32 label,
						      __be16 flags,
						      __be64 tunnel_id,
						      पूर्णांक md_size)
अणु
	काष्ठा metadata_dst *tun_dst;
	काष्ठा ip_tunnel_info *info;

	tun_dst = tun_rx_dst(md_size);
	अगर (!tun_dst)
		वापस शून्य;

	info = &tun_dst->u.tun_info;
	info->mode = IP_TUNNEL_INFO_IPV6;
	info->key.tun_flags = flags;
	info->key.tun_id = tunnel_id;
	info->key.tp_src = 0;
	info->key.tp_dst = tp_dst;

	info->key.u.ipv6.src = *saddr;
	info->key.u.ipv6.dst = *daddr;

	info->key.tos = tos;
	info->key.ttl = ttl;
	info->key.label = label;

	वापस tun_dst;
पूर्ण

अटल अंतरभूत काष्ठा metadata_dst *ipv6_tun_rx_dst(काष्ठा sk_buff *skb,
						   __be16 flags,
						   __be64 tunnel_id,
						   पूर्णांक md_size)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);

	वापस __ipv6_tun_set_dst(&ip6h->saddr, &ip6h->daddr,
				  ipv6_get_dsfield(ip6h), ip6h->hop_limit,
				  0, ip6_flowlabel(ip6h), flags, tunnel_id,
				  md_size);
पूर्ण
#पूर्ण_अगर /* __NET_DST_METADATA_H */

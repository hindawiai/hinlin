<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_GRE_H
#घोषणा __LINUX_GRE_H

#समावेश <linux/skbuff.h>
#समावेश <net/ip_tunnels.h>

काष्ठा gre_base_hdr अणु
	__be16 flags;
	__be16 protocol;
पूर्ण __packed;

काष्ठा gre_full_hdr अणु
	काष्ठा gre_base_hdr fixed_header;
	__be16 csum;
	__be16 reserved1;
	__be32 key;
	__be32 seq;
पूर्ण __packed;
#घोषणा GRE_HEADER_SECTION 4

#घोषणा GREPROTO_CISCO		0
#घोषणा GREPROTO_PPTP		1
#घोषणा GREPROTO_MAX		2
#घोषणा GRE_IP_PROTO_MAX	2

काष्ठा gre_protocol अणु
	पूर्णांक  (*handler)(काष्ठा sk_buff *skb);
	व्योम (*err_handler)(काष्ठा sk_buff *skb, u32 info);
पूर्ण;

पूर्णांक gre_add_protocol(स्थिर काष्ठा gre_protocol *proto, u8 version);
पूर्णांक gre_del_protocol(स्थिर काष्ठा gre_protocol *proto, u8 version);

काष्ठा net_device *gretap_fb_dev_create(काष्ठा net *net, स्थिर अक्षर *name,
				       u8 name_assign_type);
पूर्णांक gre_parse_header(काष्ठा sk_buff *skb, काष्ठा tnl_ptk_info *tpi,
		     bool *csum_err, __be16 proto, पूर्णांक nhs);

अटल अंतरभूत bool netअगर_is_gretap(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->rtnl_link_ops &&
	       !म_भेद(dev->rtnl_link_ops->kind, "gretap");
पूर्ण

अटल अंतरभूत bool netअगर_is_ip6gretap(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->rtnl_link_ops &&
	       !म_भेद(dev->rtnl_link_ops->kind, "ip6gretap");
पूर्ण

अटल अंतरभूत पूर्णांक gre_calc_hlen(__be16 o_flags)
अणु
	पूर्णांक addend = 4;

	अगर (o_flags & TUNNEL_CSUM)
		addend += 4;
	अगर (o_flags & TUNNEL_KEY)
		addend += 4;
	अगर (o_flags & TUNNEL_SEQ)
		addend += 4;
	वापस addend;
पूर्ण

अटल अंतरभूत __be16 gre_flags_to_tnl_flags(__be16 flags)
अणु
	__be16 tflags = 0;

	अगर (flags & GRE_CSUM)
		tflags |= TUNNEL_CSUM;
	अगर (flags & GRE_ROUTING)
		tflags |= TUNNEL_ROUTING;
	अगर (flags & GRE_KEY)
		tflags |= TUNNEL_KEY;
	अगर (flags & GRE_SEQ)
		tflags |= TUNNEL_SEQ;
	अगर (flags & GRE_STRICT)
		tflags |= TUNNEL_STRICT;
	अगर (flags & GRE_REC)
		tflags |= TUNNEL_REC;
	अगर (flags & GRE_VERSION)
		tflags |= TUNNEL_VERSION;

	वापस tflags;
पूर्ण

अटल अंतरभूत __be16 gre_tnl_flags_to_gre_flags(__be16 tflags)
अणु
	__be16 flags = 0;

	अगर (tflags & TUNNEL_CSUM)
		flags |= GRE_CSUM;
	अगर (tflags & TUNNEL_ROUTING)
		flags |= GRE_ROUTING;
	अगर (tflags & TUNNEL_KEY)
		flags |= GRE_KEY;
	अगर (tflags & TUNNEL_SEQ)
		flags |= GRE_SEQ;
	अगर (tflags & TUNNEL_STRICT)
		flags |= GRE_STRICT;
	अगर (tflags & TUNNEL_REC)
		flags |= GRE_REC;
	अगर (tflags & TUNNEL_VERSION)
		flags |= GRE_VERSION;

	वापस flags;
पूर्ण

अटल अंतरभूत व्योम gre_build_header(काष्ठा sk_buff *skb, पूर्णांक hdr_len,
				    __be16 flags, __be16 proto,
				    __be32 key, __be32 seq)
अणु
	काष्ठा gre_base_hdr *greh;

	skb_push(skb, hdr_len);

	skb_set_inner_protocol(skb, proto);
	skb_reset_transport_header(skb);
	greh = (काष्ठा gre_base_hdr *)skb->data;
	greh->flags = gre_tnl_flags_to_gre_flags(flags);
	greh->protocol = proto;

	अगर (flags & (TUNNEL_KEY | TUNNEL_CSUM | TUNNEL_SEQ)) अणु
		__be32 *ptr = (__be32 *)(((u8 *)greh) + hdr_len - 4);

		अगर (flags & TUNNEL_SEQ) अणु
			*ptr = seq;
			ptr--;
		पूर्ण
		अगर (flags & TUNNEL_KEY) अणु
			*ptr = key;
			ptr--;
		पूर्ण
		अगर (flags & TUNNEL_CSUM &&
		    !(skb_shinfo(skb)->gso_type &
		      (SKB_GSO_GRE | SKB_GSO_GRE_CSUM))) अणु
			*ptr = 0;
			अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
				*(__sum16 *)ptr = csum_fold(lco_csum(skb));
			पूर्ण अन्यथा अणु
				skb->ip_summed = CHECKSUM_PARTIAL;
				skb->csum_start = skb_transport_header(skb) - skb->head;
				skb->csum_offset = माप(*greh);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर

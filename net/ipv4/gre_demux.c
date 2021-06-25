<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	GRE over IPv4 demultiplexer driver
 *
 *	Authors: Dmitry Kozlov (xeb@mail.ru)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/अगर.h>
#समावेश <linux/icmp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/spinlock.h>
#समावेश <net/protocol.h>
#समावेश <net/gre.h>
#समावेश <net/erspan.h>

#समावेश <net/icmp.h>
#समावेश <net/route.h>
#समावेश <net/xfrm.h>

अटल स्थिर काष्ठा gre_protocol __rcu *gre_proto[GREPROTO_MAX] __पढ़ो_mostly;

पूर्णांक gre_add_protocol(स्थिर काष्ठा gre_protocol *proto, u8 version)
अणु
	अगर (version >= GREPROTO_MAX)
		वापस -EINVAL;

	वापस (cmpxchg((स्थिर काष्ठा gre_protocol **)&gre_proto[version], शून्य, proto) == शून्य) ?
		0 : -EBUSY;
पूर्ण
EXPORT_SYMBOL_GPL(gre_add_protocol);

पूर्णांक gre_del_protocol(स्थिर काष्ठा gre_protocol *proto, u8 version)
अणु
	पूर्णांक ret;

	अगर (version >= GREPROTO_MAX)
		वापस -EINVAL;

	ret = (cmpxchg((स्थिर काष्ठा gre_protocol **)&gre_proto[version], proto, शून्य) == proto) ?
		0 : -EBUSY;

	अगर (ret)
		वापस ret;

	synchronize_rcu();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gre_del_protocol);

/* Fills in tpi and वापसs header length to be pulled.
 * Note that caller must use pskb_may_pull() beक्रमe pulling GRE header.
 */
पूर्णांक gre_parse_header(काष्ठा sk_buff *skb, काष्ठा tnl_ptk_info *tpi,
		     bool *csum_err, __be16 proto, पूर्णांक nhs)
अणु
	स्थिर काष्ठा gre_base_hdr *greh;
	__be32 *options;
	पूर्णांक hdr_len;

	अगर (unlikely(!pskb_may_pull(skb, nhs + माप(काष्ठा gre_base_hdr))))
		वापस -EINVAL;

	greh = (काष्ठा gre_base_hdr *)(skb->data + nhs);
	अगर (unlikely(greh->flags & (GRE_VERSION | GRE_ROUTING)))
		वापस -EINVAL;

	tpi->flags = gre_flags_to_tnl_flags(greh->flags);
	hdr_len = gre_calc_hlen(tpi->flags);

	अगर (!pskb_may_pull(skb, nhs + hdr_len))
		वापस -EINVAL;

	greh = (काष्ठा gre_base_hdr *)(skb->data + nhs);
	tpi->proto = greh->protocol;

	options = (__be32 *)(greh + 1);
	अगर (greh->flags & GRE_CSUM) अणु
		अगर (!skb_checksum_simple_validate(skb)) अणु
			skb_checksum_try_convert(skb, IPPROTO_GRE,
						 null_compute_pseuकरो);
		पूर्ण अन्यथा अगर (csum_err) अणु
			*csum_err = true;
			वापस -EINVAL;
		पूर्ण

		options++;
	पूर्ण

	अगर (greh->flags & GRE_KEY) अणु
		tpi->key = *options;
		options++;
	पूर्ण अन्यथा अणु
		tpi->key = 0;
	पूर्ण
	अगर (unlikely(greh->flags & GRE_SEQ)) अणु
		tpi->seq = *options;
		options++;
	पूर्ण अन्यथा अणु
		tpi->seq = 0;
	पूर्ण
	/* WCCP version 1 and 2 protocol decoding.
	 * - Change protocol to IPv4/IPv6
	 * - When dealing with WCCPv2, Skip extra 4 bytes in GRE header
	 */
	अगर (greh->flags == 0 && tpi->proto == htons(ETH_P_WCCP)) अणु
		u8 _val, *val;

		val = skb_header_poपूर्णांकer(skb, nhs + hdr_len,
					 माप(_val), &_val);
		अगर (!val)
			वापस -EINVAL;
		tpi->proto = proto;
		अगर ((*val & 0xF0) != 0x40)
			hdr_len += 4;
	पूर्ण
	tpi->hdr_len = hdr_len;

	/* ERSPAN ver 1 and 2 protocol sets GRE key field
	 * to 0 and sets the configured key in the
	 * inner erspan header field
	 */
	अगर ((greh->protocol == htons(ETH_P_ERSPAN) && hdr_len != 4) ||
	    greh->protocol == htons(ETH_P_ERSPAN2)) अणु
		काष्ठा erspan_base_hdr *ershdr;

		अगर (!pskb_may_pull(skb, nhs + hdr_len + माप(*ershdr)))
			वापस -EINVAL;

		ershdr = (काष्ठा erspan_base_hdr *)(skb->data + nhs + hdr_len);
		tpi->key = cpu_to_be32(get_session_id(ershdr));
	पूर्ण

	वापस hdr_len;
पूर्ण
EXPORT_SYMBOL(gre_parse_header);

अटल पूर्णांक gre_rcv(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा gre_protocol *proto;
	u8 ver;
	पूर्णांक ret;

	अगर (!pskb_may_pull(skb, 12))
		जाओ drop;

	ver = skb->data[1]&0x7f;
	अगर (ver >= GREPROTO_MAX)
		जाओ drop;

	rcu_पढ़ो_lock();
	proto = rcu_dereference(gre_proto[ver]);
	अगर (!proto || !proto->handler)
		जाओ drop_unlock;
	ret = proto->handler(skb);
	rcu_पढ़ो_unlock();
	वापस ret;

drop_unlock:
	rcu_पढ़ो_unlock();
drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल पूर्णांक gre_err(काष्ठा sk_buff *skb, u32 info)
अणु
	स्थिर काष्ठा gre_protocol *proto;
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	u8 ver = skb->data[(iph->ihl<<2) + 1]&0x7f;
	पूर्णांक err = 0;

	अगर (ver >= GREPROTO_MAX)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	proto = rcu_dereference(gre_proto[ver]);
	अगर (proto && proto->err_handler)
		proto->err_handler(skb, info);
	अन्यथा
		err = -EPROTONOSUPPORT;
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_protocol net_gre_protocol = अणु
	.handler     = gre_rcv,
	.err_handler = gre_err,
	.netns_ok    = 1,
पूर्ण;

अटल पूर्णांक __init gre_init(व्योम)
अणु
	pr_info("GRE over IPv4 demultiplexor driver\n");

	अगर (inet_add_protocol(&net_gre_protocol, IPPROTO_GRE) < 0) अणु
		pr_err("can't add protocol\n");
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास gre_निकास(व्योम)
अणु
	inet_del_protocol(&net_gre_protocol, IPPROTO_GRE);
पूर्ण

module_init(gre_init);
module_निकास(gre_निकास);

MODULE_DESCRIPTION("GRE over IPv4 demultiplexer driver");
MODULE_AUTHOR("D. Kozlov (xeb@mail.ru)");
MODULE_LICENSE("GPL");

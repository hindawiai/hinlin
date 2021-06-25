<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/socket.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/icmp.h>
#समावेश <linux/udp.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <net/genetlink.h>
#समावेश <net/gue.h>
#समावेश <net/fou.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/udp.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/xfrm.h>
#समावेश <uapi/linux/fou.h>
#समावेश <uapi/linux/genetlink.h>

काष्ठा fou अणु
	काष्ठा socket *sock;
	u8 protocol;
	u8 flags;
	__be16 port;
	u8 family;
	u16 type;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

#घोषणा FOU_F_REMCSUM_NOPARTIAL BIT(0)

काष्ठा fou_cfg अणु
	u16 type;
	u8 protocol;
	u8 flags;
	काष्ठा udp_port_cfg udp_config;
पूर्ण;

अटल अचिन्हित पूर्णांक fou_net_id;

काष्ठा fou_net अणु
	काष्ठा list_head fou_list;
	काष्ठा mutex fou_lock;
पूर्ण;

अटल अंतरभूत काष्ठा fou *fou_from_sock(काष्ठा sock *sk)
अणु
	वापस sk->sk_user_data;
पूर्ण

अटल पूर्णांक fou_recv_pull(काष्ठा sk_buff *skb, काष्ठा fou *fou, माप_प्रकार len)
अणु
	/* Remove 'len' bytes from the packet (UDP header and
	 * FOU header अगर present).
	 */
	अगर (fou->family == AF_INET)
		ip_hdr(skb)->tot_len = htons(ntohs(ip_hdr(skb)->tot_len) - len);
	अन्यथा
		ipv6_hdr(skb)->payload_len =
		    htons(ntohs(ipv6_hdr(skb)->payload_len) - len);

	__skb_pull(skb, len);
	skb_postpull_rcsum(skb, udp_hdr(skb), len);
	skb_reset_transport_header(skb);
	वापस iptunnel_pull_offloads(skb);
पूर्ण

अटल पूर्णांक fou_udp_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा fou *fou = fou_from_sock(sk);

	अगर (!fou)
		वापस 1;

	अगर (fou_recv_pull(skb, fou, माप(काष्ठा udphdr)))
		जाओ drop;

	वापस -fou->protocol;

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल काष्ठा guehdr *gue_remcsum(काष्ठा sk_buff *skb, काष्ठा guehdr *guehdr,
				  व्योम *data, माप_प्रकार hdrlen, u8 ipproto,
				  bool nopartial)
अणु
	__be16 *pd = data;
	माप_प्रकार start = ntohs(pd[0]);
	माप_प्रकार offset = ntohs(pd[1]);
	माप_प्रकार plen = माप(काष्ठा udphdr) + hdrlen +
	    max_t(माप_प्रकार, offset + माप(u16), start);

	अगर (skb->remcsum_offload)
		वापस guehdr;

	अगर (!pskb_may_pull(skb, plen))
		वापस शून्य;
	guehdr = (काष्ठा guehdr *)&udp_hdr(skb)[1];

	skb_remcsum_process(skb, (व्योम *)guehdr + hdrlen,
			    start, offset, nopartial);

	वापस guehdr;
पूर्ण

अटल पूर्णांक gue_control_message(काष्ठा sk_buff *skb, काष्ठा guehdr *guehdr)
अणु
	/* No support yet */
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक gue_udp_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा fou *fou = fou_from_sock(sk);
	माप_प्रकार len, optlen, hdrlen;
	काष्ठा guehdr *guehdr;
	व्योम *data;
	u16 करोffset = 0;
	u8 proto_ctype;

	अगर (!fou)
		वापस 1;

	len = माप(काष्ठा udphdr) + माप(काष्ठा guehdr);
	अगर (!pskb_may_pull(skb, len))
		जाओ drop;

	guehdr = (काष्ठा guehdr *)&udp_hdr(skb)[1];

	चयन (guehdr->version) अणु
	हाल 0: /* Full GUE header present */
		अवरोध;

	हाल 1: अणु
		/* Direct encapsulation of IPv4 or IPv6 */

		पूर्णांक prot;

		चयन (((काष्ठा iphdr *)guehdr)->version) अणु
		हाल 4:
			prot = IPPROTO_IPIP;
			अवरोध;
		हाल 6:
			prot = IPPROTO_IPV6;
			अवरोध;
		शेष:
			जाओ drop;
		पूर्ण

		अगर (fou_recv_pull(skb, fou, माप(काष्ठा udphdr)))
			जाओ drop;

		वापस -prot;
	पूर्ण

	शेष: /* Undefined version */
		जाओ drop;
	पूर्ण

	optlen = guehdr->hlen << 2;
	len += optlen;

	अगर (!pskb_may_pull(skb, len))
		जाओ drop;

	/* guehdr may change after pull */
	guehdr = (काष्ठा guehdr *)&udp_hdr(skb)[1];

	अगर (validate_gue_flags(guehdr, optlen))
		जाओ drop;

	hdrlen = माप(काष्ठा guehdr) + optlen;

	अगर (fou->family == AF_INET)
		ip_hdr(skb)->tot_len = htons(ntohs(ip_hdr(skb)->tot_len) - len);
	अन्यथा
		ipv6_hdr(skb)->payload_len =
		    htons(ntohs(ipv6_hdr(skb)->payload_len) - len);

	/* Pull csum through the guehdr now . This can be used अगर
	 * there is a remote checksum offload.
	 */
	skb_postpull_rcsum(skb, udp_hdr(skb), len);

	data = &guehdr[1];

	अगर (guehdr->flags & GUE_FLAG_PRIV) अणु
		__be32 flags = *(__be32 *)(data + करोffset);

		करोffset += GUE_LEN_PRIV;

		अगर (flags & GUE_PFLAG_REMCSUM) अणु
			guehdr = gue_remcsum(skb, guehdr, data + करोffset,
					     hdrlen, guehdr->proto_ctype,
					     !!(fou->flags &
						FOU_F_REMCSUM_NOPARTIAL));
			अगर (!guehdr)
				जाओ drop;

			data = &guehdr[1];

			करोffset += GUE_PLEN_REMCSUM;
		पूर्ण
	पूर्ण

	अगर (unlikely(guehdr->control))
		वापस gue_control_message(skb, guehdr);

	proto_ctype = guehdr->proto_ctype;
	__skb_pull(skb, माप(काष्ठा udphdr) + hdrlen);
	skb_reset_transport_header(skb);

	अगर (iptunnel_pull_offloads(skb))
		जाओ drop;

	वापस -proto_ctype;

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *fou_gro_receive(काष्ठा sock *sk,
				       काष्ठा list_head *head,
				       काष्ठा sk_buff *skb)
अणु
	u8 proto = fou_from_sock(sk)->protocol;
	स्थिर काष्ठा net_offload **offloads;
	स्थिर काष्ठा net_offload *ops;
	काष्ठा sk_buff *pp = शून्य;

	/* We can clear the encap_mark क्रम FOU as we are essentially करोing
	 * one of two possible things.  We are either adding an L4 tunnel
	 * header to the outer L3 tunnel header, or we are simply
	 * treating the GRE tunnel header as though it is a UDP protocol
	 * specअगरic header such as VXLAN or GENEVE.
	 */
	NAPI_GRO_CB(skb)->encap_mark = 0;

	/* Flag this frame as alपढ़ोy having an outer encap header */
	NAPI_GRO_CB(skb)->is_fou = 1;

	rcu_पढ़ो_lock();
	offloads = NAPI_GRO_CB(skb)->is_ipv6 ? inet6_offloads : inet_offloads;
	ops = rcu_dereference(offloads[proto]);
	अगर (!ops || !ops->callbacks.gro_receive)
		जाओ out_unlock;

	pp = call_gro_receive(ops->callbacks.gro_receive, head, skb);

out_unlock:
	rcu_पढ़ो_unlock();

	वापस pp;
पूर्ण

अटल पूर्णांक fou_gro_complete(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    पूर्णांक nhoff)
अणु
	स्थिर काष्ठा net_offload *ops;
	u8 proto = fou_from_sock(sk)->protocol;
	पूर्णांक err = -ENOSYS;
	स्थिर काष्ठा net_offload **offloads;

	rcu_पढ़ो_lock();
	offloads = NAPI_GRO_CB(skb)->is_ipv6 ? inet6_offloads : inet_offloads;
	ops = rcu_dereference(offloads[proto]);
	अगर (WARN_ON(!ops || !ops->callbacks.gro_complete))
		जाओ out_unlock;

	err = ops->callbacks.gro_complete(skb, nhoff);

	skb_set_inner_mac_header(skb, nhoff);

out_unlock:
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल काष्ठा guehdr *gue_gro_remcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक off,
				      काष्ठा guehdr *guehdr, व्योम *data,
				      माप_प्रकार hdrlen, काष्ठा gro_remcsum *grc,
				      bool nopartial)
अणु
	__be16 *pd = data;
	माप_प्रकार start = ntohs(pd[0]);
	माप_प्रकार offset = ntohs(pd[1]);

	अगर (skb->remcsum_offload)
		वापस guehdr;

	अगर (!NAPI_GRO_CB(skb)->csum_valid)
		वापस शून्य;

	guehdr = skb_gro_remcsum_process(skb, (व्योम *)guehdr, off, hdrlen,
					 start, offset, grc, nopartial);

	skb->remcsum_offload = 1;

	वापस guehdr;
पूर्ण

अटल काष्ठा sk_buff *gue_gro_receive(काष्ठा sock *sk,
				       काष्ठा list_head *head,
				       काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा net_offload **offloads;
	स्थिर काष्ठा net_offload *ops;
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा sk_buff *p;
	काष्ठा guehdr *guehdr;
	माप_प्रकार len, optlen, hdrlen, off;
	व्योम *data;
	u16 करोffset = 0;
	पूर्णांक flush = 1;
	काष्ठा fou *fou = fou_from_sock(sk);
	काष्ठा gro_remcsum grc;
	u8 proto;

	skb_gro_remcsum_init(&grc);

	off = skb_gro_offset(skb);
	len = off + माप(*guehdr);

	guehdr = skb_gro_header_fast(skb, off);
	अगर (skb_gro_header_hard(skb, len)) अणु
		guehdr = skb_gro_header_slow(skb, len, off);
		अगर (unlikely(!guehdr))
			जाओ out;
	पूर्ण

	चयन (guehdr->version) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		चयन (((काष्ठा iphdr *)guehdr)->version) अणु
		हाल 4:
			proto = IPPROTO_IPIP;
			अवरोध;
		हाल 6:
			proto = IPPROTO_IPV6;
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
		जाओ next_proto;
	शेष:
		जाओ out;
	पूर्ण

	optlen = guehdr->hlen << 2;
	len += optlen;

	अगर (skb_gro_header_hard(skb, len)) अणु
		guehdr = skb_gro_header_slow(skb, len, off);
		अगर (unlikely(!guehdr))
			जाओ out;
	पूर्ण

	अगर (unlikely(guehdr->control) || guehdr->version != 0 ||
	    validate_gue_flags(guehdr, optlen))
		जाओ out;

	hdrlen = माप(*guehdr) + optlen;

	/* Adjust NAPI_GRO_CB(skb)->csum to account क्रम guehdr,
	 * this is needed अगर there is a remote checkcsum offload.
	 */
	skb_gro_postpull_rcsum(skb, guehdr, hdrlen);

	data = &guehdr[1];

	अगर (guehdr->flags & GUE_FLAG_PRIV) अणु
		__be32 flags = *(__be32 *)(data + करोffset);

		करोffset += GUE_LEN_PRIV;

		अगर (flags & GUE_PFLAG_REMCSUM) अणु
			guehdr = gue_gro_remcsum(skb, off, guehdr,
						 data + करोffset, hdrlen, &grc,
						 !!(fou->flags &
						    FOU_F_REMCSUM_NOPARTIAL));

			अगर (!guehdr)
				जाओ out;

			data = &guehdr[1];

			करोffset += GUE_PLEN_REMCSUM;
		पूर्ण
	पूर्ण

	skb_gro_pull(skb, hdrlen);

	list_क्रम_each_entry(p, head, list) अणु
		स्थिर काष्ठा guehdr *guehdr2;

		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		guehdr2 = (काष्ठा guehdr *)(p->data + off);

		/* Compare base GUE header to be equal (covers
		 * hlen, version, proto_ctype, and flags.
		 */
		अगर (guehdr->word != guehdr2->word) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण

		/* Compare optional fields are the same. */
		अगर (guehdr->hlen && स_भेद(&guehdr[1], &guehdr2[1],
					   guehdr->hlen << 2)) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण
	पूर्ण

	proto = guehdr->proto_ctype;

next_proto:

	/* We can clear the encap_mark क्रम GUE as we are essentially करोing
	 * one of two possible things.  We are either adding an L4 tunnel
	 * header to the outer L3 tunnel header, or we are simply
	 * treating the GRE tunnel header as though it is a UDP protocol
	 * specअगरic header such as VXLAN or GENEVE.
	 */
	NAPI_GRO_CB(skb)->encap_mark = 0;

	/* Flag this frame as alपढ़ोy having an outer encap header */
	NAPI_GRO_CB(skb)->is_fou = 1;

	rcu_पढ़ो_lock();
	offloads = NAPI_GRO_CB(skb)->is_ipv6 ? inet6_offloads : inet_offloads;
	ops = rcu_dereference(offloads[proto]);
	अगर (WARN_ON_ONCE(!ops || !ops->callbacks.gro_receive))
		जाओ out_unlock;

	pp = call_gro_receive(ops->callbacks.gro_receive, head, skb);
	flush = 0;

out_unlock:
	rcu_पढ़ो_unlock();
out:
	skb_gro_flush_final_remcsum(skb, pp, flush, &grc);

	वापस pp;
पूर्ण

अटल पूर्णांक gue_gro_complete(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	स्थिर काष्ठा net_offload **offloads;
	काष्ठा guehdr *guehdr = (काष्ठा guehdr *)(skb->data + nhoff);
	स्थिर काष्ठा net_offload *ops;
	अचिन्हित पूर्णांक guehlen = 0;
	u8 proto;
	पूर्णांक err = -ENOENT;

	चयन (guehdr->version) अणु
	हाल 0:
		proto = guehdr->proto_ctype;
		guehlen = माप(*guehdr) + (guehdr->hlen << 2);
		अवरोध;
	हाल 1:
		चयन (((काष्ठा iphdr *)guehdr)->version) अणु
		हाल 4:
			proto = IPPROTO_IPIP;
			अवरोध;
		हाल 6:
			proto = IPPROTO_IPV6;
			अवरोध;
		शेष:
			वापस err;
		पूर्ण
		अवरोध;
	शेष:
		वापस err;
	पूर्ण

	rcu_पढ़ो_lock();
	offloads = NAPI_GRO_CB(skb)->is_ipv6 ? inet6_offloads : inet_offloads;
	ops = rcu_dereference(offloads[proto]);
	अगर (WARN_ON(!ops || !ops->callbacks.gro_complete))
		जाओ out_unlock;

	err = ops->callbacks.gro_complete(skb, nhoff + guehlen);

	skb_set_inner_mac_header(skb, nhoff + guehlen);

out_unlock:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल bool fou_cfg_cmp(काष्ठा fou *fou, काष्ठा fou_cfg *cfg)
अणु
	काष्ठा sock *sk = fou->sock->sk;
	काष्ठा udp_port_cfg *udp_cfg = &cfg->udp_config;

	अगर (fou->family != udp_cfg->family ||
	    fou->port != udp_cfg->local_udp_port ||
	    sk->sk_dport != udp_cfg->peer_udp_port ||
	    sk->sk_bound_dev_अगर != udp_cfg->bind_अगरindex)
		वापस false;

	अगर (fou->family == AF_INET) अणु
		अगर (sk->sk_rcv_saddr != udp_cfg->local_ip.s_addr ||
		    sk->sk_daddr != udp_cfg->peer_ip.s_addr)
			वापस false;
		अन्यथा
			वापस true;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		अगर (ipv6_addr_cmp(&sk->sk_v6_rcv_saddr, &udp_cfg->local_ip6) ||
		    ipv6_addr_cmp(&sk->sk_v6_daddr, &udp_cfg->peer_ip6))
			वापस false;
		अन्यथा
			वापस true;
#पूर्ण_अगर
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक fou_add_to_port_list(काष्ठा net *net, काष्ठा fou *fou,
				काष्ठा fou_cfg *cfg)
अणु
	काष्ठा fou_net *fn = net_generic(net, fou_net_id);
	काष्ठा fou *fout;

	mutex_lock(&fn->fou_lock);
	list_क्रम_each_entry(fout, &fn->fou_list, list) अणु
		अगर (fou_cfg_cmp(fout, cfg)) अणु
			mutex_unlock(&fn->fou_lock);
			वापस -EALREADY;
		पूर्ण
	पूर्ण

	list_add(&fou->list, &fn->fou_list);
	mutex_unlock(&fn->fou_lock);

	वापस 0;
पूर्ण

अटल व्योम fou_release(काष्ठा fou *fou)
अणु
	काष्ठा socket *sock = fou->sock;

	list_del(&fou->list);
	udp_tunnel_sock_release(sock);

	kमुक्त_rcu(fou, rcu);
पूर्ण

अटल पूर्णांक fou_create(काष्ठा net *net, काष्ठा fou_cfg *cfg,
		      काष्ठा socket **sockp)
अणु
	काष्ठा socket *sock = शून्य;
	काष्ठा fou *fou = शून्य;
	काष्ठा sock *sk;
	काष्ठा udp_tunnel_sock_cfg tunnel_cfg;
	पूर्णांक err;

	/* Open UDP socket */
	err = udp_sock_create(net, &cfg->udp_config, &sock);
	अगर (err < 0)
		जाओ error;

	/* Allocate FOU port काष्ठाure */
	fou = kzalloc(माप(*fou), GFP_KERNEL);
	अगर (!fou) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	sk = sock->sk;

	fou->port = cfg->udp_config.local_udp_port;
	fou->family = cfg->udp_config.family;
	fou->flags = cfg->flags;
	fou->type = cfg->type;
	fou->sock = sock;

	स_रखो(&tunnel_cfg, 0, माप(tunnel_cfg));
	tunnel_cfg.encap_type = 1;
	tunnel_cfg.sk_user_data = fou;
	tunnel_cfg.encap_destroy = शून्य;

	/* Initial क्रम fou type */
	चयन (cfg->type) अणु
	हाल FOU_ENCAP_सूचीECT:
		tunnel_cfg.encap_rcv = fou_udp_recv;
		tunnel_cfg.gro_receive = fou_gro_receive;
		tunnel_cfg.gro_complete = fou_gro_complete;
		fou->protocol = cfg->protocol;
		अवरोध;
	हाल FOU_ENCAP_GUE:
		tunnel_cfg.encap_rcv = gue_udp_recv;
		tunnel_cfg.gro_receive = gue_gro_receive;
		tunnel_cfg.gro_complete = gue_gro_complete;
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ error;
	पूर्ण

	setup_udp_tunnel_sock(net, sock, &tunnel_cfg);

	sk->sk_allocation = GFP_ATOMIC;

	err = fou_add_to_port_list(net, fou, cfg);
	अगर (err)
		जाओ error;

	अगर (sockp)
		*sockp = sock;

	वापस 0;

error:
	kमुक्त(fou);
	अगर (sock)
		udp_tunnel_sock_release(sock);

	वापस err;
पूर्ण

अटल पूर्णांक fou_destroy(काष्ठा net *net, काष्ठा fou_cfg *cfg)
अणु
	काष्ठा fou_net *fn = net_generic(net, fou_net_id);
	पूर्णांक err = -EINVAL;
	काष्ठा fou *fou;

	mutex_lock(&fn->fou_lock);
	list_क्रम_each_entry(fou, &fn->fou_list, list) अणु
		अगर (fou_cfg_cmp(fou, cfg)) अणु
			fou_release(fou);
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&fn->fou_lock);

	वापस err;
पूर्ण

अटल काष्ठा genl_family fou_nl_family;

अटल स्थिर काष्ठा nla_policy fou_nl_policy[FOU_ATTR_MAX + 1] = अणु
	[FOU_ATTR_PORT]			= अणु .type = NLA_U16, पूर्ण,
	[FOU_ATTR_AF]			= अणु .type = NLA_U8, पूर्ण,
	[FOU_ATTR_IPPROTO]		= अणु .type = NLA_U8, पूर्ण,
	[FOU_ATTR_TYPE]			= अणु .type = NLA_U8, पूर्ण,
	[FOU_ATTR_REMCSUM_NOPARTIAL]	= अणु .type = NLA_FLAG, पूर्ण,
	[FOU_ATTR_LOCAL_V4]		= अणु .type = NLA_U32, पूर्ण,
	[FOU_ATTR_PEER_V4]		= अणु .type = NLA_U32, पूर्ण,
	[FOU_ATTR_LOCAL_V6]		= अणु .len = माप(काष्ठा in6_addr), पूर्ण,
	[FOU_ATTR_PEER_V6]		= अणु .len = माप(काष्ठा in6_addr), पूर्ण,
	[FOU_ATTR_PEER_PORT]		= अणु .type = NLA_U16, पूर्ण,
	[FOU_ATTR_IFINDEX]		= अणु .type = NLA_S32, पूर्ण,
पूर्ण;

अटल पूर्णांक parse_nl_config(काष्ठा genl_info *info,
			   काष्ठा fou_cfg *cfg)
अणु
	bool has_local = false, has_peer = false;
	काष्ठा nlattr *attr;
	पूर्णांक अगरindex;
	__be16 port;

	स_रखो(cfg, 0, माप(*cfg));

	cfg->udp_config.family = AF_INET;

	अगर (info->attrs[FOU_ATTR_AF]) अणु
		u8 family = nla_get_u8(info->attrs[FOU_ATTR_AF]);

		चयन (family) अणु
		हाल AF_INET:
			अवरोध;
		हाल AF_INET6:
			cfg->udp_config.ipv6_v6only = 1;
			अवरोध;
		शेष:
			वापस -EAFNOSUPPORT;
		पूर्ण

		cfg->udp_config.family = family;
	पूर्ण

	अगर (info->attrs[FOU_ATTR_PORT]) अणु
		port = nla_get_be16(info->attrs[FOU_ATTR_PORT]);
		cfg->udp_config.local_udp_port = port;
	पूर्ण

	अगर (info->attrs[FOU_ATTR_IPPROTO])
		cfg->protocol = nla_get_u8(info->attrs[FOU_ATTR_IPPROTO]);

	अगर (info->attrs[FOU_ATTR_TYPE])
		cfg->type = nla_get_u8(info->attrs[FOU_ATTR_TYPE]);

	अगर (info->attrs[FOU_ATTR_REMCSUM_NOPARTIAL])
		cfg->flags |= FOU_F_REMCSUM_NOPARTIAL;

	अगर (cfg->udp_config.family == AF_INET) अणु
		अगर (info->attrs[FOU_ATTR_LOCAL_V4]) अणु
			attr = info->attrs[FOU_ATTR_LOCAL_V4];
			cfg->udp_config.local_ip.s_addr = nla_get_in_addr(attr);
			has_local = true;
		पूर्ण

		अगर (info->attrs[FOU_ATTR_PEER_V4]) अणु
			attr = info->attrs[FOU_ATTR_PEER_V4];
			cfg->udp_config.peer_ip.s_addr = nla_get_in_addr(attr);
			has_peer = true;
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		अगर (info->attrs[FOU_ATTR_LOCAL_V6]) अणु
			attr = info->attrs[FOU_ATTR_LOCAL_V6];
			cfg->udp_config.local_ip6 = nla_get_in6_addr(attr);
			has_local = true;
		पूर्ण

		अगर (info->attrs[FOU_ATTR_PEER_V6]) अणु
			attr = info->attrs[FOU_ATTR_PEER_V6];
			cfg->udp_config.peer_ip6 = nla_get_in6_addr(attr);
			has_peer = true;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (has_peer) अणु
		अगर (info->attrs[FOU_ATTR_PEER_PORT]) अणु
			port = nla_get_be16(info->attrs[FOU_ATTR_PEER_PORT]);
			cfg->udp_config.peer_udp_port = port;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (info->attrs[FOU_ATTR_IFINDEX]) अणु
		अगर (!has_local)
			वापस -EINVAL;

		अगरindex = nla_get_s32(info->attrs[FOU_ATTR_IFINDEX]);

		cfg->udp_config.bind_अगरindex = अगरindex;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fou_nl_cmd_add_port(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा fou_cfg cfg;
	पूर्णांक err;

	err = parse_nl_config(info, &cfg);
	अगर (err)
		वापस err;

	वापस fou_create(net, &cfg, शून्य);
पूर्ण

अटल पूर्णांक fou_nl_cmd_rm_port(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा fou_cfg cfg;
	पूर्णांक err;

	err = parse_nl_config(info, &cfg);
	अगर (err)
		वापस err;

	वापस fou_destroy(net, &cfg);
पूर्ण

अटल पूर्णांक fou_fill_info(काष्ठा fou *fou, काष्ठा sk_buff *msg)
अणु
	काष्ठा sock *sk = fou->sock->sk;

	अगर (nla_put_u8(msg, FOU_ATTR_AF, fou->sock->sk->sk_family) ||
	    nla_put_be16(msg, FOU_ATTR_PORT, fou->port) ||
	    nla_put_be16(msg, FOU_ATTR_PEER_PORT, sk->sk_dport) ||
	    nla_put_u8(msg, FOU_ATTR_IPPROTO, fou->protocol) ||
	    nla_put_u8(msg, FOU_ATTR_TYPE, fou->type) ||
	    nla_put_s32(msg, FOU_ATTR_IFINDEX, sk->sk_bound_dev_अगर))
		वापस -1;

	अगर (fou->flags & FOU_F_REMCSUM_NOPARTIAL)
		अगर (nla_put_flag(msg, FOU_ATTR_REMCSUM_NOPARTIAL))
			वापस -1;

	अगर (fou->sock->sk->sk_family == AF_INET) अणु
		अगर (nla_put_in_addr(msg, FOU_ATTR_LOCAL_V4, sk->sk_rcv_saddr))
			वापस -1;

		अगर (nla_put_in_addr(msg, FOU_ATTR_PEER_V4, sk->sk_daddr))
			वापस -1;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		अगर (nla_put_in6_addr(msg, FOU_ATTR_LOCAL_V6,
				     &sk->sk_v6_rcv_saddr))
			वापस -1;

		अगर (nla_put_in6_addr(msg, FOU_ATTR_PEER_V6, &sk->sk_v6_daddr))
			वापस -1;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fou_dump_info(काष्ठा fou *fou, u32 portid, u32 seq,
			 u32 flags, काष्ठा sk_buff *skb, u8 cmd)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(skb, portid, seq, &fou_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -ENOMEM;

	अगर (fou_fill_info(fou, skb) < 0)
		जाओ nla_put_failure;

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fou_nl_cmd_get_port(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा fou_net *fn = net_generic(net, fou_net_id);
	काष्ठा sk_buff *msg;
	काष्ठा fou_cfg cfg;
	काष्ठा fou *fout;
	__be16 port;
	u8 family;
	पूर्णांक ret;

	ret = parse_nl_config(info, &cfg);
	अगर (ret)
		वापस ret;
	port = cfg.udp_config.local_udp_port;
	अगर (port == 0)
		वापस -EINVAL;

	family = cfg.udp_config.family;
	अगर (family != AF_INET && family != AF_INET6)
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = -ESRCH;
	mutex_lock(&fn->fou_lock);
	list_क्रम_each_entry(fout, &fn->fou_list, list) अणु
		अगर (fou_cfg_cmp(fout, &cfg)) अणु
			ret = fou_dump_info(fout, info->snd_portid,
					    info->snd_seq, 0, msg,
					    info->genlhdr->cmd);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&fn->fou_lock);
	अगर (ret < 0)
		जाओ out_मुक्त;

	वापस genlmsg_reply(msg, info);

out_मुक्त:
	nlmsg_मुक्त(msg);
	वापस ret;
पूर्ण

अटल पूर्णांक fou_nl_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fou_net *fn = net_generic(net, fou_net_id);
	काष्ठा fou *fout;
	पूर्णांक idx = 0, ret;

	mutex_lock(&fn->fou_lock);
	list_क्रम_each_entry(fout, &fn->fou_list, list) अणु
		अगर (idx++ < cb->args[0])
			जारी;
		ret = fou_dump_info(fout, NETLINK_CB(cb->skb).portid,
				    cb->nlh->nlmsg_seq, NLM_F_MULTI,
				    skb, FOU_CMD_GET);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&fn->fou_lock);

	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops fou_nl_ops[] = अणु
	अणु
		.cmd = FOU_CMD_ADD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = fou_nl_cmd_add_port,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = FOU_CMD_DEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = fou_nl_cmd_rm_port,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = FOU_CMD_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = fou_nl_cmd_get_port,
		.dumpit = fou_nl_dump,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family fou_nl_family __ro_after_init = अणु
	.hdrsize	= 0,
	.name		= FOU_GENL_NAME,
	.version	= FOU_GENL_VERSION,
	.maxattr	= FOU_ATTR_MAX,
	.policy = fou_nl_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= fou_nl_ops,
	.n_small_ops	= ARRAY_SIZE(fou_nl_ops),
पूर्ण;

माप_प्रकार fou_encap_hlen(काष्ठा ip_tunnel_encap *e)
अणु
	वापस माप(काष्ठा udphdr);
पूर्ण
EXPORT_SYMBOL(fou_encap_hlen);

माप_प्रकार gue_encap_hlen(काष्ठा ip_tunnel_encap *e)
अणु
	माप_प्रकार len;
	bool need_priv = false;

	len = माप(काष्ठा udphdr) + माप(काष्ठा guehdr);

	अगर (e->flags & TUNNEL_ENCAP_FLAG_REMCSUM) अणु
		len += GUE_PLEN_REMCSUM;
		need_priv = true;
	पूर्ण

	len += need_priv ? GUE_LEN_PRIV : 0;

	वापस len;
पूर्ण
EXPORT_SYMBOL(gue_encap_hlen);

पूर्णांक __fou_build_header(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
		       u8 *protocol, __be16 *sport, पूर्णांक type)
अणु
	पूर्णांक err;

	err = iptunnel_handle_offloads(skb, type);
	अगर (err)
		वापस err;

	*sport = e->sport ? : udp_flow_src_port(dev_net(skb->dev),
						skb, 0, 0, false);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__fou_build_header);

पूर्णांक __gue_build_header(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
		       u8 *protocol, __be16 *sport, पूर्णांक type)
अणु
	काष्ठा guehdr *guehdr;
	माप_प्रकार hdrlen, optlen = 0;
	व्योम *data;
	bool need_priv = false;
	पूर्णांक err;

	अगर ((e->flags & TUNNEL_ENCAP_FLAG_REMCSUM) &&
	    skb->ip_summed == CHECKSUM_PARTIAL) अणु
		optlen += GUE_PLEN_REMCSUM;
		type |= SKB_GSO_TUNNEL_REMCSUM;
		need_priv = true;
	पूर्ण

	optlen += need_priv ? GUE_LEN_PRIV : 0;

	err = iptunnel_handle_offloads(skb, type);
	अगर (err)
		वापस err;

	/* Get source port (based on flow hash) beक्रमe skb_push */
	*sport = e->sport ? : udp_flow_src_port(dev_net(skb->dev),
						skb, 0, 0, false);

	hdrlen = माप(काष्ठा guehdr) + optlen;

	skb_push(skb, hdrlen);

	guehdr = (काष्ठा guehdr *)skb->data;

	guehdr->control = 0;
	guehdr->version = 0;
	guehdr->hlen = optlen >> 2;
	guehdr->flags = 0;
	guehdr->proto_ctype = *protocol;

	data = &guehdr[1];

	अगर (need_priv) अणु
		__be32 *flags = data;

		guehdr->flags |= GUE_FLAG_PRIV;
		*flags = 0;
		data += GUE_LEN_PRIV;

		अगर (type & SKB_GSO_TUNNEL_REMCSUM) अणु
			u16 csum_start = skb_checksum_start_offset(skb);
			__be16 *pd = data;

			अगर (csum_start < hdrlen)
				वापस -EINVAL;

			csum_start -= hdrlen;
			pd[0] = htons(csum_start);
			pd[1] = htons(csum_start + skb->csum_offset);

			अगर (!skb_is_gso(skb)) अणु
				skb->ip_summed = CHECKSUM_NONE;
				skb->encapsulation = 0;
			पूर्ण

			*flags |= GUE_PFLAG_REMCSUM;
			data += GUE_PLEN_REMCSUM;
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__gue_build_header);

#अगर_घोषित CONFIG_NET_FOU_IP_TUNNELS

अटल व्योम fou_build_udp(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
			  काष्ठा flowi4 *fl4, u8 *protocol, __be16 sport)
अणु
	काष्ठा udphdr *uh;

	skb_push(skb, माप(काष्ठा udphdr));
	skb_reset_transport_header(skb);

	uh = udp_hdr(skb);

	uh->dest = e->dport;
	uh->source = sport;
	uh->len = htons(skb->len);
	udp_set_csum(!(e->flags & TUNNEL_ENCAP_FLAG_CSUM), skb,
		     fl4->saddr, fl4->daddr, skb->len);

	*protocol = IPPROTO_UDP;
पूर्ण

अटल पूर्णांक fou_build_header(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
			    u8 *protocol, काष्ठा flowi4 *fl4)
अणु
	पूर्णांक type = e->flags & TUNNEL_ENCAP_FLAG_CSUM ? SKB_GSO_UDP_TUNNEL_CSUM :
						       SKB_GSO_UDP_TUNNEL;
	__be16 sport;
	पूर्णांक err;

	err = __fou_build_header(skb, e, protocol, &sport, type);
	अगर (err)
		वापस err;

	fou_build_udp(skb, e, fl4, protocol, sport);

	वापस 0;
पूर्ण

अटल पूर्णांक gue_build_header(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_encap *e,
			    u8 *protocol, काष्ठा flowi4 *fl4)
अणु
	पूर्णांक type = e->flags & TUNNEL_ENCAP_FLAG_CSUM ? SKB_GSO_UDP_TUNNEL_CSUM :
						       SKB_GSO_UDP_TUNNEL;
	__be16 sport;
	पूर्णांक err;

	err = __gue_build_header(skb, e, protocol, &sport, type);
	अगर (err)
		वापस err;

	fou_build_udp(skb, e, fl4, protocol, sport);

	वापस 0;
पूर्ण

अटल पूर्णांक gue_err_proto_handler(पूर्णांक proto, काष्ठा sk_buff *skb, u32 info)
अणु
	स्थिर काष्ठा net_protocol *ipprot = rcu_dereference(inet_protos[proto]);

	अगर (ipprot && ipprot->err_handler) अणु
		अगर (!ipprot->err_handler(skb, info))
			वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक gue_err(काष्ठा sk_buff *skb, u32 info)
अणु
	पूर्णांक transport_offset = skb_transport_offset(skb);
	काष्ठा guehdr *guehdr;
	माप_प्रकार len, optlen;
	पूर्णांक ret;

	len = माप(काष्ठा udphdr) + माप(काष्ठा guehdr);
	अगर (!pskb_may_pull(skb, transport_offset + len))
		वापस -EINVAL;

	guehdr = (काष्ठा guehdr *)&udp_hdr(skb)[1];

	चयन (guehdr->version) अणु
	हाल 0: /* Full GUE header present */
		अवरोध;
	हाल 1: अणु
		/* Direct encapsulation of IPv4 or IPv6 */
		skb_set_transport_header(skb, -(पूर्णांक)माप(काष्ठा icmphdr));

		चयन (((काष्ठा iphdr *)guehdr)->version) अणु
		हाल 4:
			ret = gue_err_proto_handler(IPPROTO_IPIP, skb, info);
			जाओ out;
#अगर IS_ENABLED(CONFIG_IPV6)
		हाल 6:
			ret = gue_err_proto_handler(IPPROTO_IPV6, skb, info);
			जाओ out;
#पूर्ण_अगर
		शेष:
			ret = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण
	शेष: /* Undefined version */
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (guehdr->control)
		वापस -ENOENT;

	optlen = guehdr->hlen << 2;

	अगर (!pskb_may_pull(skb, transport_offset + len + optlen))
		वापस -EINVAL;

	guehdr = (काष्ठा guehdr *)&udp_hdr(skb)[1];
	अगर (validate_gue_flags(guehdr, optlen))
		वापस -EINVAL;

	/* Handling exceptions क्रम direct UDP encapsulation in GUE would lead to
	 * recursion. Besides, this kind of encapsulation can't even be
	 * configured currently. Discard this.
	 */
	अगर (guehdr->proto_ctype == IPPROTO_UDP ||
	    guehdr->proto_ctype == IPPROTO_UDPLITE)
		वापस -EOPNOTSUPP;

	skb_set_transport_header(skb, -(पूर्णांक)माप(काष्ठा icmphdr));
	ret = gue_err_proto_handler(guehdr->proto_ctype, skb, info);

out:
	skb_set_transport_header(skb, transport_offset);
	वापस ret;
पूर्ण


अटल स्थिर काष्ठा ip_tunnel_encap_ops fou_iptun_ops = अणु
	.encap_hlen = fou_encap_hlen,
	.build_header = fou_build_header,
	.err_handler = gue_err,
पूर्ण;

अटल स्थिर काष्ठा ip_tunnel_encap_ops gue_iptun_ops = अणु
	.encap_hlen = gue_encap_hlen,
	.build_header = gue_build_header,
	.err_handler = gue_err,
पूर्ण;

अटल पूर्णांक ip_tunnel_encap_add_fou_ops(व्योम)
अणु
	पूर्णांक ret;

	ret = ip_tunnel_encap_add_ops(&fou_iptun_ops, TUNNEL_ENCAP_FOU);
	अगर (ret < 0) अणु
		pr_err("can't add fou ops\n");
		वापस ret;
	पूर्ण

	ret = ip_tunnel_encap_add_ops(&gue_iptun_ops, TUNNEL_ENCAP_GUE);
	अगर (ret < 0) अणु
		pr_err("can't add gue ops\n");
		ip_tunnel_encap_del_ops(&fou_iptun_ops, TUNNEL_ENCAP_FOU);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ip_tunnel_encap_del_fou_ops(व्योम)
अणु
	ip_tunnel_encap_del_ops(&fou_iptun_ops, TUNNEL_ENCAP_FOU);
	ip_tunnel_encap_del_ops(&gue_iptun_ops, TUNNEL_ENCAP_GUE);
पूर्ण

#अन्यथा

अटल पूर्णांक ip_tunnel_encap_add_fou_ops(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम ip_tunnel_encap_del_fou_ops(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल __net_init पूर्णांक fou_init_net(काष्ठा net *net)
अणु
	काष्ठा fou_net *fn = net_generic(net, fou_net_id);

	INIT_LIST_HEAD(&fn->fou_list);
	mutex_init(&fn->fou_lock);
	वापस 0;
पूर्ण

अटल __net_निकास व्योम fou_निकास_net(काष्ठा net *net)
अणु
	काष्ठा fou_net *fn = net_generic(net, fou_net_id);
	काष्ठा fou *fou, *next;

	/* Close all the FOU sockets */
	mutex_lock(&fn->fou_lock);
	list_क्रम_each_entry_safe(fou, next, &fn->fou_list, list)
		fou_release(fou);
	mutex_unlock(&fn->fou_lock);
पूर्ण

अटल काष्ठा pernet_operations fou_net_ops = अणु
	.init = fou_init_net,
	.निकास = fou_निकास_net,
	.id   = &fou_net_id,
	.size = माप(काष्ठा fou_net),
पूर्ण;

अटल पूर्णांक __init fou_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_device(&fou_net_ops);
	अगर (ret)
		जाओ निकास;

	ret = genl_रेजिस्टर_family(&fou_nl_family);
	अगर (ret < 0)
		जाओ unरेजिस्टर;

	ret = ip_tunnel_encap_add_fou_ops();
	अगर (ret == 0)
		वापस 0;

	genl_unरेजिस्टर_family(&fou_nl_family);
unरेजिस्टर:
	unरेजिस्टर_pernet_device(&fou_net_ops);
निकास:
	वापस ret;
पूर्ण

अटल व्योम __निकास fou_fini(व्योम)
अणु
	ip_tunnel_encap_del_fou_ops();
	genl_unरेजिस्टर_family(&fou_nl_family);
	unरेजिस्टर_pernet_device(&fou_net_ops);
पूर्ण

module_init(fou_init);
module_निकास(fou_fini);
MODULE_AUTHOR("Tom Herbert <therbert@google.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Foo over UDP");

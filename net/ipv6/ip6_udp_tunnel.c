<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/socket.h>
#समावेश <linux/udp.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/in6.h>
#समावेश <net/udp.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/ip6_tunnel.h>
#समावेश <net/ip6_checksum.h>

पूर्णांक udp_sock_create6(काष्ठा net *net, काष्ठा udp_port_cfg *cfg,
		     काष्ठा socket **sockp)
अणु
	काष्ठा sockaddr_in6 udp6_addr = अणुपूर्ण;
	पूर्णांक err;
	काष्ठा socket *sock = शून्य;

	err = sock_create_kern(net, AF_INET6, SOCK_DGRAM, 0, &sock);
	अगर (err < 0)
		जाओ error;

	अगर (cfg->ipv6_v6only) अणु
		err = ip6_sock_set_v6only(sock->sk);
		अगर (err < 0)
			जाओ error;
	पूर्ण
	अगर (cfg->bind_अगरindex) अणु
		err = sock_bindtoindex(sock->sk, cfg->bind_अगरindex, true);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	udp6_addr.sin6_family = AF_INET6;
	स_नकल(&udp6_addr.sin6_addr, &cfg->local_ip6,
	       माप(udp6_addr.sin6_addr));
	udp6_addr.sin6_port = cfg->local_udp_port;
	err = kernel_bind(sock, (काष्ठा sockaddr *)&udp6_addr,
			  माप(udp6_addr));
	अगर (err < 0)
		जाओ error;

	अगर (cfg->peer_udp_port) अणु
		स_रखो(&udp6_addr, 0, माप(udp6_addr));
		udp6_addr.sin6_family = AF_INET6;
		स_नकल(&udp6_addr.sin6_addr, &cfg->peer_ip6,
		       माप(udp6_addr.sin6_addr));
		udp6_addr.sin6_port = cfg->peer_udp_port;
		err = kernel_connect(sock,
				     (काष्ठा sockaddr *)&udp6_addr,
				     माप(udp6_addr), 0);
	पूर्ण
	अगर (err < 0)
		जाओ error;

	udp_set_no_check6_tx(sock->sk, !cfg->use_udp6_tx_checksums);
	udp_set_no_check6_rx(sock->sk, !cfg->use_udp6_rx_checksums);

	*sockp = sock;
	वापस 0;

error:
	अगर (sock) अणु
		kernel_sock_shutकरोwn(sock, SHUT_RDWR);
		sock_release(sock);
	पूर्ण
	*sockp = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(udp_sock_create6);

पूर्णांक udp_tunnel6_xmit_skb(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			 काष्ठा sk_buff *skb,
			 काष्ठा net_device *dev, काष्ठा in6_addr *saddr,
			 काष्ठा in6_addr *daddr,
			 __u8 prio, __u8 ttl, __be32 label,
			 __be16 src_port, __be16 dst_port, bool nocheck)
अणु
	काष्ठा udphdr *uh;
	काष्ठा ipv6hdr *ip6h;

	__skb_push(skb, माप(*uh));
	skb_reset_transport_header(skb);
	uh = udp_hdr(skb);

	uh->dest = dst_port;
	uh->source = src_port;

	uh->len = htons(skb->len);

	skb_dst_set(skb, dst);

	udp6_set_csum(nocheck, skb, saddr, daddr, skb->len);

	__skb_push(skb, माप(*ip6h));
	skb_reset_network_header(skb);
	ip6h		  = ipv6_hdr(skb);
	ip6_flow_hdr(ip6h, prio, label);
	ip6h->payload_len = htons(skb->len);
	ip6h->nexthdr     = IPPROTO_UDP;
	ip6h->hop_limit   = ttl;
	ip6h->daddr	  = *daddr;
	ip6h->saddr	  = *saddr;

	ip6tunnel_xmit(sk, skb, dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(udp_tunnel6_xmit_skb);

MODULE_LICENSE("GPL");

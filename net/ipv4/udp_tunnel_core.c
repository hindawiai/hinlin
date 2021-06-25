<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/socket.h>
#समावेश <linux/udp.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/net_namespace.h>
#समावेश <net/udp.h>
#समावेश <net/udp_tunnel.h>

पूर्णांक udp_sock_create4(काष्ठा net *net, काष्ठा udp_port_cfg *cfg,
		     काष्ठा socket **sockp)
अणु
	पूर्णांक err;
	काष्ठा socket *sock = शून्य;
	काष्ठा sockaddr_in udp_addr;

	err = sock_create_kern(net, AF_INET, SOCK_DGRAM, 0, &sock);
	अगर (err < 0)
		जाओ error;

	अगर (cfg->bind_अगरindex) अणु
		err = sock_bindtoindex(sock->sk, cfg->bind_अगरindex, true);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	udp_addr.sin_family = AF_INET;
	udp_addr.sin_addr = cfg->local_ip;
	udp_addr.sin_port = cfg->local_udp_port;
	err = kernel_bind(sock, (काष्ठा sockaddr *)&udp_addr,
			  माप(udp_addr));
	अगर (err < 0)
		जाओ error;

	अगर (cfg->peer_udp_port) अणु
		udp_addr.sin_family = AF_INET;
		udp_addr.sin_addr = cfg->peer_ip;
		udp_addr.sin_port = cfg->peer_udp_port;
		err = kernel_connect(sock, (काष्ठा sockaddr *)&udp_addr,
				     माप(udp_addr), 0);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	sock->sk->sk_no_check_tx = !cfg->use_udp_checksums;

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
EXPORT_SYMBOL(udp_sock_create4);

व्योम setup_udp_tunnel_sock(काष्ठा net *net, काष्ठा socket *sock,
			   काष्ठा udp_tunnel_sock_cfg *cfg)
अणु
	काष्ठा sock *sk = sock->sk;

	/* Disable multicast loopback */
	inet_sk(sk)->mc_loop = 0;

	/* Enable CHECKSUM_UNNECESSARY to CHECKSUM_COMPLETE conversion */
	inet_inc_convert_csum(sk);

	rcu_assign_sk_user_data(sk, cfg->sk_user_data);

	udp_sk(sk)->encap_type = cfg->encap_type;
	udp_sk(sk)->encap_rcv = cfg->encap_rcv;
	udp_sk(sk)->encap_err_lookup = cfg->encap_err_lookup;
	udp_sk(sk)->encap_destroy = cfg->encap_destroy;
	udp_sk(sk)->gro_receive = cfg->gro_receive;
	udp_sk(sk)->gro_complete = cfg->gro_complete;

	udp_tunnel_encap_enable(sock);
पूर्ण
EXPORT_SYMBOL_GPL(setup_udp_tunnel_sock);

व्योम udp_tunnel_push_rx_port(काष्ठा net_device *dev, काष्ठा socket *sock,
			     अचिन्हित लघु type)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा udp_tunnel_info ti;

	ti.type = type;
	ti.sa_family = sk->sk_family;
	ti.port = inet_sk(sk)->inet_sport;

	udp_tunnel_nic_add_port(dev, &ti);
पूर्ण
EXPORT_SYMBOL_GPL(udp_tunnel_push_rx_port);

व्योम udp_tunnel_drop_rx_port(काष्ठा net_device *dev, काष्ठा socket *sock,
			     अचिन्हित लघु type)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा udp_tunnel_info ti;

	ti.type = type;
	ti.sa_family = sk->sk_family;
	ti.port = inet_sk(sk)->inet_sport;

	udp_tunnel_nic_del_port(dev, &ti);
पूर्ण
EXPORT_SYMBOL_GPL(udp_tunnel_drop_rx_port);

/* Notअगरy netdevs that UDP port started listening */
व्योम udp_tunnel_notअगरy_add_rx_port(काष्ठा socket *sock, अचिन्हित लघु type)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा udp_tunnel_info ti;
	काष्ठा net_device *dev;

	ti.type = type;
	ti.sa_family = sk->sk_family;
	ti.port = inet_sk(sk)->inet_sport;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		udp_tunnel_nic_add_port(dev, &ti);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(udp_tunnel_notअगरy_add_rx_port);

/* Notअगरy netdevs that UDP port is no more listening */
व्योम udp_tunnel_notअगरy_del_rx_port(काष्ठा socket *sock, अचिन्हित लघु type)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा udp_tunnel_info ti;
	काष्ठा net_device *dev;

	ti.type = type;
	ti.sa_family = sk->sk_family;
	ti.port = inet_sk(sk)->inet_sport;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		udp_tunnel_nic_del_port(dev, &ti);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(udp_tunnel_notअगरy_del_rx_port);

व्योम udp_tunnel_xmit_skb(काष्ठा rtable *rt, काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 __be32 src, __be32 dst, __u8 tos, __u8 ttl,
			 __be16 df, __be16 src_port, __be16 dst_port,
			 bool xnet, bool nocheck)
अणु
	काष्ठा udphdr *uh;

	__skb_push(skb, माप(*uh));
	skb_reset_transport_header(skb);
	uh = udp_hdr(skb);

	uh->dest = dst_port;
	uh->source = src_port;
	uh->len = htons(skb->len);

	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));

	udp_set_csum(nocheck, skb, src, dst, skb->len);

	iptunnel_xmit(sk, rt, skb, src, dst, IPPROTO_UDP, tos, ttl, df, xnet);
पूर्ण
EXPORT_SYMBOL_GPL(udp_tunnel_xmit_skb);

व्योम udp_tunnel_sock_release(काष्ठा socket *sock)
अणु
	rcu_assign_sk_user_data(sock->sk, शून्य);
	kernel_sock_shutकरोwn(sock, SHUT_RDWR);
	sock_release(sock);
पूर्ण
EXPORT_SYMBOL_GPL(udp_tunnel_sock_release);

काष्ठा metadata_dst *udp_tun_rx_dst(काष्ठा sk_buff *skb,  अचिन्हित लघु family,
				    __be16 flags, __be64 tunnel_id, पूर्णांक md_size)
अणु
	काष्ठा metadata_dst *tun_dst;
	काष्ठा ip_tunnel_info *info;

	अगर (family == AF_INET)
		tun_dst = ip_tun_rx_dst(skb, flags, tunnel_id, md_size);
	अन्यथा
		tun_dst = ipv6_tun_rx_dst(skb, flags, tunnel_id, md_size);
	अगर (!tun_dst)
		वापस शून्य;

	info = &tun_dst->u.tun_info;
	info->key.tp_src = udp_hdr(skb)->source;
	info->key.tp_dst = udp_hdr(skb)->dest;
	अगर (udp_hdr(skb)->check)
		info->key.tun_flags |= TUNNEL_CSUM;
	वापस tun_dst;
पूर्ण
EXPORT_SYMBOL_GPL(udp_tun_rx_dst);

MODULE_LICENSE("GPL");

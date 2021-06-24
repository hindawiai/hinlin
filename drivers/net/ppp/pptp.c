<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Poपूर्णांक-to-Poपूर्णांक Tunneling Protocol क्रम Linux
 *
 *	Authors: Dmitry Kozlov <xeb@mail.ru>
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/अगर_pppox.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/file.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/spinlock.h>

#समावेश <net/sock.h>
#समावेश <net/protocol.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/route.h>
#समावेश <net/gre.h>
#समावेश <net/pptp.h>

#समावेश <linux/uaccess.h>

#घोषणा PPTP_DRIVER_VERSION "0.8.5"

#घोषणा MAX_CALLID 65535

अटल DECLARE_BITMAP(callid_biपंचांगap, MAX_CALLID + 1);
अटल काष्ठा pppox_sock __rcu **callid_sock;

अटल DEFINE_SPINLOCK(chan_lock);

अटल काष्ठा proto pptp_sk_proto __पढ़ो_mostly;
अटल स्थिर काष्ठा ppp_channel_ops pptp_chan_ops;
अटल स्थिर काष्ठा proto_ops pptp_ops;

अटल काष्ठा pppox_sock *lookup_chan(u16 call_id, __be32 s_addr)
अणु
	काष्ठा pppox_sock *sock;
	काष्ठा pptp_opt *opt;

	rcu_पढ़ो_lock();
	sock = rcu_dereference(callid_sock[call_id]);
	अगर (sock) अणु
		opt = &sock->proto.pptp;
		अगर (opt->dst_addr.sin_addr.s_addr != s_addr)
			sock = शून्य;
		अन्यथा
			sock_hold(sk_pppox(sock));
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस sock;
पूर्ण

अटल पूर्णांक lookup_chan_dst(u16 call_id, __be32 d_addr)
अणु
	काष्ठा pppox_sock *sock;
	काष्ठा pptp_opt *opt;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	i = 1;
	क्रम_each_set_bit_from(i, callid_biपंचांगap, MAX_CALLID) अणु
		sock = rcu_dereference(callid_sock[i]);
		अगर (!sock)
			जारी;
		opt = &sock->proto.pptp;
		अगर (opt->dst_addr.call_id == call_id &&
			  opt->dst_addr.sin_addr.s_addr == d_addr)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस i < MAX_CALLID;
पूर्ण

अटल पूर्णांक add_chan(काष्ठा pppox_sock *sock,
		    काष्ठा pptp_addr *sa)
अणु
	अटल पूर्णांक call_id;

	spin_lock(&chan_lock);
	अगर (!sa->call_id)	अणु
		call_id = find_next_zero_bit(callid_biपंचांगap, MAX_CALLID, call_id + 1);
		अगर (call_id == MAX_CALLID) अणु
			call_id = find_next_zero_bit(callid_biपंचांगap, MAX_CALLID, 1);
			अगर (call_id == MAX_CALLID)
				जाओ out_err;
		पूर्ण
		sa->call_id = call_id;
	पूर्ण अन्यथा अगर (test_bit(sa->call_id, callid_biपंचांगap)) अणु
		जाओ out_err;
	पूर्ण

	sock->proto.pptp.src_addr = *sa;
	set_bit(sa->call_id, callid_biपंचांगap);
	rcu_assign_poपूर्णांकer(callid_sock[sa->call_id], sock);
	spin_unlock(&chan_lock);

	वापस 0;

out_err:
	spin_unlock(&chan_lock);
	वापस -1;
पूर्ण

अटल व्योम del_chan(काष्ठा pppox_sock *sock)
अणु
	spin_lock(&chan_lock);
	clear_bit(sock->proto.pptp.src_addr.call_id, callid_biपंचांगap);
	RCU_INIT_POINTER(callid_sock[sock->proto.pptp.src_addr.call_id], शून्य);
	spin_unlock(&chan_lock);
पूर्ण

अटल पूर्णांक pptp_xmit(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = (काष्ठा sock *) chan->निजी;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा pptp_opt *opt = &po->proto.pptp;
	काष्ठा pptp_gre_header *hdr;
	अचिन्हित पूर्णांक header_len = माप(*hdr);
	काष्ठा flowi4 fl4;
	पूर्णांक islcp;
	पूर्णांक len;
	अचिन्हित अक्षर *data;
	__u32 seq_recv;


	काष्ठा rtable *rt;
	काष्ठा net_device *tdev;
	काष्ठा iphdr  *iph;
	पूर्णांक    max_headroom;

	अगर (sk_pppox(po)->sk_state & PPPOX_DEAD)
		जाओ tx_error;

	rt = ip_route_output_ports(net, &fl4, शून्य,
				   opt->dst_addr.sin_addr.s_addr,
				   opt->src_addr.sin_addr.s_addr,
				   0, 0, IPPROTO_GRE,
				   RT_TOS(0), sk->sk_bound_dev_अगर);
	अगर (IS_ERR(rt))
		जाओ tx_error;

	tdev = rt->dst.dev;

	max_headroom = LL_RESERVED_SPACE(tdev) + माप(*iph) + माप(*hdr) + 2;

	अगर (skb_headroom(skb) < max_headroom || skb_cloned(skb) || skb_shared(skb)) अणु
		काष्ठा sk_buff *new_skb = skb_पुनः_स्मृति_headroom(skb, max_headroom);
		अगर (!new_skb) अणु
			ip_rt_put(rt);
			जाओ tx_error;
		पूर्ण
		अगर (skb->sk)
			skb_set_owner_w(new_skb, skb->sk);
		consume_skb(skb);
		skb = new_skb;
	पूर्ण

	data = skb->data;
	islcp = ((data[0] << 8) + data[1]) == PPP_LCP && 1 <= data[2] && data[2] <= 7;

	/* compress protocol field */
	अगर ((opt->ppp_flags & SC_COMP_PROT) && data[0] == 0 && !islcp)
		skb_pull(skb, 1);

	/* Put in the address/control bytes अगर necessary */
	अगर ((opt->ppp_flags & SC_COMP_AC) == 0 || islcp) अणु
		data = skb_push(skb, 2);
		data[0] = PPP_ALLSTATIONS;
		data[1] = PPP_UI;
	पूर्ण

	len = skb->len;

	seq_recv = opt->seq_recv;

	अगर (opt->ack_sent == seq_recv)
		header_len -= माप(hdr->ack);

	/* Push करोwn and install GRE header */
	skb_push(skb, header_len);
	hdr = (काष्ठा pptp_gre_header *)(skb->data);

	hdr->gre_hd.flags = GRE_KEY | GRE_VERSION_1 | GRE_SEQ;
	hdr->gre_hd.protocol = GRE_PROTO_PPP;
	hdr->call_id = htons(opt->dst_addr.call_id);

	hdr->seq = htonl(++opt->seq_sent);
	अगर (opt->ack_sent != seq_recv)	अणु
		/* send ack with this message */
		hdr->gre_hd.flags |= GRE_ACK;
		hdr->ack  = htonl(seq_recv);
		opt->ack_sent = seq_recv;
	पूर्ण
	hdr->payload_len = htons(len);

	/*	Push करोwn and install the IP header. */

	skb_reset_transport_header(skb);
	skb_push(skb, माप(*iph));
	skb_reset_network_header(skb);
	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));
	IPCB(skb)->flags &= ~(IPSKB_XFRM_TUNNEL_SIZE | IPSKB_XFRM_TRANSFORMED | IPSKB_REROUTED);

	iph =	ip_hdr(skb);
	iph->version =	4;
	iph->ihl =	माप(काष्ठा iphdr) >> 2;
	अगर (ip_करोnt_fragment(sk, &rt->dst))
		iph->frag_off	=	htons(IP_DF);
	अन्यथा
		iph->frag_off	=	0;
	iph->protocol = IPPROTO_GRE;
	iph->tos      = 0;
	iph->daddr    = fl4.daddr;
	iph->saddr    = fl4.saddr;
	iph->ttl      = ip4_dst_hoplimit(&rt->dst);
	iph->tot_len  = htons(skb->len);

	skb_dst_drop(skb);
	skb_dst_set(skb, &rt->dst);

	nf_reset_ct(skb);

	skb->ip_summed = CHECKSUM_NONE;
	ip_select_ident(net, skb, शून्य);
	ip_send_check(iph);

	ip_local_out(net, skb->sk, skb);
	वापस 1;

tx_error:
	kमुक्त_skb(skb);
	वापस 1;
पूर्ण

अटल पूर्णांक pptp_rcv_core(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा pptp_opt *opt = &po->proto.pptp;
	पूर्णांक headersize, payload_len, seq;
	__u8 *payload;
	काष्ठा pptp_gre_header *header;

	अगर (!(sk->sk_state & PPPOX_CONNECTED)) अणु
		अगर (sock_queue_rcv_skb(sk, skb))
			जाओ drop;
		वापस NET_RX_SUCCESS;
	पूर्ण

	header = (काष्ठा pptp_gre_header *)(skb->data);
	headersize  = माप(*header);

	/* test अगर acknowledgement present */
	अगर (GRE_IS_ACK(header->gre_hd.flags)) अणु
		__u32 ack;

		अगर (!pskb_may_pull(skb, headersize))
			जाओ drop;
		header = (काष्ठा pptp_gre_header *)(skb->data);

		/* ack in dअगरferent place अगर S = 0 */
		ack = GRE_IS_SEQ(header->gre_hd.flags) ? ntohl(header->ack) :
							 ntohl(header->seq);
		अगर (ack > opt->ack_recv)
			opt->ack_recv = ack;
		/* also handle sequence number wrap-around  */
		अगर (WRAPPED(ack, opt->ack_recv))
			opt->ack_recv = ack;
	पूर्ण अन्यथा अणु
		headersize -= माप(header->ack);
	पूर्ण
	/* test अगर payload present */
	अगर (!GRE_IS_SEQ(header->gre_hd.flags))
		जाओ drop;

	payload_len = ntohs(header->payload_len);
	seq         = ntohl(header->seq);

	/* check क्रम incomplete packet (length smaller than expected) */
	अगर (!pskb_may_pull(skb, headersize + payload_len))
		जाओ drop;

	payload = skb->data + headersize;
	/* check क्रम expected sequence number */
	अगर (seq < opt->seq_recv + 1 || WRAPPED(opt->seq_recv, seq)) अणु
		अगर ((payload[0] == PPP_ALLSTATIONS) && (payload[1] == PPP_UI) &&
				(PPP_PROTOCOL(payload) == PPP_LCP) &&
				((payload[4] == PPP_LCP_ECHOREQ) || (payload[4] == PPP_LCP_ECHOREP)))
			जाओ allow_packet;
	पूर्ण अन्यथा अणु
		opt->seq_recv = seq;
allow_packet:
		skb_pull(skb, headersize);

		अगर (payload[0] == PPP_ALLSTATIONS && payload[1] == PPP_UI) अणु
			/* chop off address/control */
			अगर (skb->len < 3)
				जाओ drop;
			skb_pull(skb, 2);
		पूर्ण

		skb->ip_summed = CHECKSUM_NONE;
		skb_set_network_header(skb, skb->head-skb->data);
		ppp_input(&po->chan, skb);

		वापस NET_RX_SUCCESS;
	पूर्ण
drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल पूर्णांक pptp_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा pppox_sock *po;
	काष्ठा pptp_gre_header *header;
	काष्ठा iphdr *iph;

	अगर (skb->pkt_type != PACKET_HOST)
		जाओ drop;

	अगर (!pskb_may_pull(skb, 12))
		जाओ drop;

	iph = ip_hdr(skb);

	header = (काष्ठा pptp_gre_header *)skb->data;

	अगर (header->gre_hd.protocol != GRE_PROTO_PPP || /* PPTP-GRE protocol क्रम PPTP */
		GRE_IS_CSUM(header->gre_hd.flags) ||    /* flag CSUM should be clear */
		GRE_IS_ROUTING(header->gre_hd.flags) || /* flag ROUTING should be clear */
		!GRE_IS_KEY(header->gre_hd.flags) ||    /* flag KEY should be set */
		(header->gre_hd.flags & GRE_FLAGS))     /* flag Recursion Ctrl should be clear */
		/* अगर invalid, discard this packet */
		जाओ drop;

	po = lookup_chan(ntohs(header->call_id), iph->saddr);
	अगर (po) अणु
		skb_dst_drop(skb);
		nf_reset_ct(skb);
		वापस sk_receive_skb(sk_pppox(po), skb, 0);
	पूर्ण
drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल पूर्णांक pptp_bind(काष्ठा socket *sock, काष्ठा sockaddr *uservaddr,
	पूर्णांक sockaddr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_pppox *sp = (काष्ठा sockaddr_pppox *) uservaddr;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	पूर्णांक error = 0;

	अगर (sockaddr_len < माप(काष्ठा sockaddr_pppox))
		वापस -EINVAL;

	lock_sock(sk);

	अगर (sk->sk_state & PPPOX_DEAD) अणु
		error = -EALREADY;
		जाओ out;
	पूर्ण

	अगर (sk->sk_state & PPPOX_BOUND) अणु
		error = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (add_chan(po, &sp->sa_addr.pptp))
		error = -EBUSY;
	अन्यथा
		sk->sk_state |= PPPOX_BOUND;

out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक pptp_connect(काष्ठा socket *sock, काष्ठा sockaddr *uservaddr,
	पूर्णांक sockaddr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_pppox *sp = (काष्ठा sockaddr_pppox *) uservaddr;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा pptp_opt *opt = &po->proto.pptp;
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;
	पूर्णांक error = 0;

	अगर (sockaddr_len < माप(काष्ठा sockaddr_pppox))
		वापस -EINVAL;

	अगर (sp->sa_protocol != PX_PROTO_PPTP)
		वापस -EINVAL;

	अगर (lookup_chan_dst(sp->sa_addr.pptp.call_id, sp->sa_addr.pptp.sin_addr.s_addr))
		वापस -EALREADY;

	lock_sock(sk);
	/* Check क्रम alपढ़ोy bound sockets */
	अगर (sk->sk_state & PPPOX_CONNECTED) अणु
		error = -EBUSY;
		जाओ end;
	पूर्ण

	/* Check क्रम alपढ़ोy disconnected sockets, on attempts to disconnect */
	अगर (sk->sk_state & PPPOX_DEAD) अणु
		error = -EALREADY;
		जाओ end;
	पूर्ण

	अगर (!opt->src_addr.sin_addr.s_addr || !sp->sa_addr.pptp.sin_addr.s_addr) अणु
		error = -EINVAL;
		जाओ end;
	पूर्ण

	po->chan.निजी = sk;
	po->chan.ops = &pptp_chan_ops;

	rt = ip_route_output_ports(sock_net(sk), &fl4, sk,
				   opt->dst_addr.sin_addr.s_addr,
				   opt->src_addr.sin_addr.s_addr,
				   0, 0,
				   IPPROTO_GRE, RT_CONN_FLAGS(sk),
				   sk->sk_bound_dev_अगर);
	अगर (IS_ERR(rt)) अणु
		error = -EHOSTUNREACH;
		जाओ end;
	पूर्ण
	sk_setup_caps(sk, &rt->dst);

	po->chan.mtu = dst_mtu(&rt->dst);
	अगर (!po->chan.mtu)
		po->chan.mtu = PPP_MRU;
	po->chan.mtu -= PPTP_HEADER_OVERHEAD;

	po->chan.hdrlen = 2 + माप(काष्ठा pptp_gre_header);
	error = ppp_रेजिस्टर_channel(&po->chan);
	अगर (error) अणु
		pr_err("PPTP: failed to register PPP channel (%d)\n", error);
		जाओ end;
	पूर्ण

	opt->dst_addr = sp->sa_addr.pptp;
	sk->sk_state |= PPPOX_CONNECTED;

 end:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक pptp_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
	पूर्णांक peer)
अणु
	पूर्णांक len = माप(काष्ठा sockaddr_pppox);
	काष्ठा sockaddr_pppox sp;

	स_रखो(&sp.sa_addr, 0, माप(sp.sa_addr));

	sp.sa_family    = AF_PPPOX;
	sp.sa_protocol  = PX_PROTO_PPTP;
	sp.sa_addr.pptp = pppox_sk(sock->sk)->proto.pptp.src_addr;

	स_नकल(uaddr, &sp, len);

	वापस len;
पूर्ण

अटल पूर्णांक pptp_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pppox_sock *po;
	पूर्णांक error = 0;

	अगर (!sk)
		वापस 0;

	lock_sock(sk);

	अगर (sock_flag(sk, SOCK_DEAD)) अणु
		release_sock(sk);
		वापस -EBADF;
	पूर्ण

	po = pppox_sk(sk);
	del_chan(po);
	synchronize_rcu();

	pppox_unbind_sock(sk);
	sk->sk_state = PPPOX_DEAD;

	sock_orphan(sk);
	sock->sk = शून्य;

	release_sock(sk);
	sock_put(sk);

	वापस error;
पूर्ण

अटल व्योम pptp_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	अगर (!(sk->sk_state & PPPOX_DEAD)) अणु
		del_chan(pppox_sk(sk));
		pppox_unbind_sock(sk);
	पूर्ण
	skb_queue_purge(&sk->sk_receive_queue);
	dst_release(rcu_dereference_रक्षित(sk->sk_dst_cache, 1));
पूर्ण

अटल पूर्णांक pptp_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक kern)
अणु
	पूर्णांक error = -ENOMEM;
	काष्ठा sock *sk;
	काष्ठा pppox_sock *po;
	काष्ठा pptp_opt *opt;

	sk = sk_alloc(net, PF_PPPOX, GFP_KERNEL, &pptp_sk_proto, kern);
	अगर (!sk)
		जाओ out;

	sock_init_data(sock, sk);

	sock->state = SS_UNCONNECTED;
	sock->ops   = &pptp_ops;

	sk->sk_backlog_rcv = pptp_rcv_core;
	sk->sk_state       = PPPOX_NONE;
	sk->sk_type        = SOCK_STREAM;
	sk->sk_family      = PF_PPPOX;
	sk->sk_protocol    = PX_PROTO_PPTP;
	sk->sk_deकाष्ठा    = pptp_sock_deकाष्ठा;

	po = pppox_sk(sk);
	opt = &po->proto.pptp;

	opt->seq_sent = 0; opt->seq_recv = 0xffffffff;
	opt->ack_recv = 0; opt->ack_sent = 0xffffffff;

	error = 0;
out:
	वापस error;
पूर्ण

अटल पूर्णांक pptp_ppp_ioctl(काष्ठा ppp_channel *chan, अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = (काष्ठा sock *) chan->निजी;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा pptp_opt *opt = &po->proto.pptp;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक err, val;

	err = -EFAULT;
	चयन (cmd) अणु
	हाल PPPIOCGFLAGS:
		val = opt->ppp_flags;
		अगर (put_user(val, p))
			अवरोध;
		err = 0;
		अवरोध;
	हाल PPPIOCSFLAGS:
		अगर (get_user(val, p))
			अवरोध;
		opt->ppp_flags = val & ~SC_RCV_BITS;
		err = 0;
		अवरोध;
	शेष:
		err = -ENOTTY;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ppp_channel_ops pptp_chan_ops = अणु
	.start_xmit = pptp_xmit,
	.ioctl      = pptp_ppp_ioctl,
पूर्ण;

अटल काष्ठा proto pptp_sk_proto __पढ़ो_mostly = अणु
	.name     = "PPTP",
	.owner    = THIS_MODULE,
	.obj_size = माप(काष्ठा pppox_sock),
पूर्ण;

अटल स्थिर काष्ठा proto_ops pptp_ops = अणु
	.family     = AF_PPPOX,
	.owner      = THIS_MODULE,
	.release    = pptp_release,
	.bind       = pptp_bind,
	.connect    = pptp_connect,
	.socketpair = sock_no_socketpair,
	.accept     = sock_no_accept,
	.getname    = pptp_getname,
	.listen     = sock_no_listen,
	.shutकरोwn   = sock_no_shutकरोwn,
	.sendmsg    = sock_no_sendmsg,
	.recvmsg    = sock_no_recvmsg,
	.mmap       = sock_no_mmap,
	.ioctl      = pppox_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = pppox_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pppox_proto pppox_pptp_proto = अणु
	.create = pptp_create,
	.owner  = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा gre_protocol gre_pptp_protocol = अणु
	.handler = pptp_rcv,
पूर्ण;

अटल पूर्णांक __init pptp_init_module(व्योम)
अणु
	पूर्णांक err = 0;
	pr_info("PPTP driver version " PPTP_DRIVER_VERSION "\n");

	callid_sock = vzalloc(array_size(माप(व्योम *), (MAX_CALLID + 1)));
	अगर (!callid_sock)
		वापस -ENOMEM;

	err = gre_add_protocol(&gre_pptp_protocol, GREPROTO_PPTP);
	अगर (err) अणु
		pr_err("PPTP: can't add gre protocol\n");
		जाओ out_mem_मुक्त;
	पूर्ण

	err = proto_रेजिस्टर(&pptp_sk_proto, 0);
	अगर (err) अणु
		pr_err("PPTP: can't register sk_proto\n");
		जाओ out_gre_del_protocol;
	पूर्ण

	err = रेजिस्टर_pppox_proto(PX_PROTO_PPTP, &pppox_pptp_proto);
	अगर (err) अणु
		pr_err("PPTP: can't register pppox_proto\n");
		जाओ out_unरेजिस्टर_sk_proto;
	पूर्ण

	वापस 0;

out_unरेजिस्टर_sk_proto:
	proto_unरेजिस्टर(&pptp_sk_proto);
out_gre_del_protocol:
	gre_del_protocol(&gre_pptp_protocol, GREPROTO_PPTP);
out_mem_मुक्त:
	vमुक्त(callid_sock);

	वापस err;
पूर्ण

अटल व्योम __निकास pptp_निकास_module(व्योम)
अणु
	unरेजिस्टर_pppox_proto(PX_PROTO_PPTP);
	proto_unरेजिस्टर(&pptp_sk_proto);
	gre_del_protocol(&gre_pptp_protocol, GREPROTO_PPTP);
	vमुक्त(callid_sock);
पूर्ण

module_init(pptp_init_module);
module_निकास(pptp_निकास_module);

MODULE_DESCRIPTION("Point-to-Point Tunneling Protocol");
MODULE_AUTHOR("D. Kozlov (xeb@mail.ru)");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO(PF_PPPOX, PX_PROTO_PPTP);

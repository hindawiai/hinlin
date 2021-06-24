<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File: af_phonet.c
 *
 * Phonet protocols family
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Authors: Sakari Ailus <sakari.ailus@nokia.com>
 *          Rथऊmi Denis-Courmont
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/sock.h>

#समावेश <linux/अगर_phonet.h>
#समावेश <linux/phonet.h>
#समावेश <net/phonet/phonet.h>
#समावेश <net/phonet/pn_dev.h>

/* Transport protocol registration */
अटल स्थिर काष्ठा phonet_protocol *proto_tab[PHONET_NPROTO] __पढ़ो_mostly;

अटल स्थिर काष्ठा phonet_protocol *phonet_proto_get(अचिन्हित पूर्णांक protocol)
अणु
	स्थिर काष्ठा phonet_protocol *pp;

	अगर (protocol >= PHONET_NPROTO)
		वापस शून्य;

	rcu_पढ़ो_lock();
	pp = rcu_dereference(proto_tab[protocol]);
	अगर (pp && !try_module_get(pp->prot->owner))
		pp = शून्य;
	rcu_पढ़ो_unlock();

	वापस pp;
पूर्ण

अटल अंतरभूत व्योम phonet_proto_put(स्थिर काष्ठा phonet_protocol *pp)
अणु
	module_put(pp->prot->owner);
पूर्ण

/* protocol family functions */

अटल पूर्णांक pn_socket_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			    पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा pn_sock *pn;
	स्थिर काष्ठा phonet_protocol *pnp;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (protocol == 0) अणु
		/* Default protocol selection */
		चयन (sock->type) अणु
		हाल SOCK_DGRAM:
			protocol = PN_PROTO_PHONET;
			अवरोध;
		हाल SOCK_SEQPACKET:
			protocol = PN_PROTO_PIPE;
			अवरोध;
		शेष:
			वापस -EPROTONOSUPPORT;
		पूर्ण
	पूर्ण

	pnp = phonet_proto_get(protocol);
	अगर (pnp == शून्य &&
	    request_module("net-pf-%d-proto-%d", PF_PHONET, protocol) == 0)
		pnp = phonet_proto_get(protocol);

	अगर (pnp == शून्य)
		वापस -EPROTONOSUPPORT;
	अगर (sock->type != pnp->sock_type) अणु
		err = -EPROTONOSUPPORT;
		जाओ out;
	पूर्ण

	sk = sk_alloc(net, PF_PHONET, GFP_KERNEL, pnp->prot, kern);
	अगर (sk == शून्य) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	sock_init_data(sock, sk);
	sock->state = SS_UNCONNECTED;
	sock->ops = pnp->ops;
	sk->sk_backlog_rcv = sk->sk_prot->backlog_rcv;
	sk->sk_protocol = protocol;
	pn = pn_sk(sk);
	pn->sobject = 0;
	pn->करोbject = 0;
	pn->resource = 0;
	sk->sk_prot->init(sk);
	err = 0;

out:
	phonet_proto_put(pnp);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_proto_family phonet_proto_family = अणु
	.family = PF_PHONET,
	.create = pn_socket_create,
	.owner = THIS_MODULE,
पूर्ण;

/* Phonet device header operations */
अटल पूर्णांक pn_header_create(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				अचिन्हित लघु type, स्थिर व्योम *daddr,
				स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	u8 *media = skb_push(skb, 1);

	अगर (type != ETH_P_PHONET)
		वापस -1;

	अगर (!saddr)
		saddr = dev->dev_addr;
	*media = *(स्थिर u8 *)saddr;
	वापस 1;
पूर्ण

अटल पूर्णांक pn_header_parse(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr)
अणु
	स्थिर u8 *media = skb_mac_header(skb);
	*haddr = *media;
	वापस 1;
पूर्ण

स्थिर काष्ठा header_ops phonet_header_ops = अणु
	.create = pn_header_create,
	.parse = pn_header_parse,
पूर्ण;
EXPORT_SYMBOL(phonet_header_ops);

/*
 * Prepends an ISI header and sends a datagram.
 */
अटल पूर्णांक pn_send(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			u16 dst, u16 src, u8 res, u8 irq)
अणु
	काष्ठा phonethdr *ph;
	पूर्णांक err;

	अगर (skb->len + 2 > 0xffff /* Phonet length field limit */ ||
	    skb->len + माप(काष्ठा phonethdr) > dev->mtu) अणु
		err = -EMSGSIZE;
		जाओ drop;
	पूर्ण

	/* Broadcast sending is not implemented */
	अगर (pn_addr(dst) == PNADDR_BROADCAST) अणु
		err = -EOPNOTSUPP;
		जाओ drop;
	पूर्ण

	skb_reset_transport_header(skb);
	WARN_ON(skb_headroom(skb) & 1); /* HW assumes word alignment */
	skb_push(skb, माप(काष्ठा phonethdr));
	skb_reset_network_header(skb);
	ph = pn_hdr(skb);
	ph->pn_rdev = pn_dev(dst);
	ph->pn_sdev = pn_dev(src);
	ph->pn_res = res;
	ph->pn_length = __cpu_to_be16(skb->len + 2 - माप(*ph));
	ph->pn_robj = pn_obj(dst);
	ph->pn_sobj = pn_obj(src);

	skb->protocol = htons(ETH_P_PHONET);
	skb->priority = 0;
	skb->dev = dev;

	अगर (skb->pkt_type == PACKET_LOOPBACK) अणु
		skb_reset_mac_header(skb);
		skb_orphan(skb);
		err = (irq ? netअगर_rx(skb) : netअगर_rx_ni(skb)) ? -ENOBUFS : 0;
	पूर्ण अन्यथा अणु
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
					शून्य, शून्य, skb->len);
		अगर (err < 0) अणु
			err = -EHOSTUNREACH;
			जाओ drop;
		पूर्ण
		err = dev_queue_xmit(skb);
		अगर (unlikely(err > 0))
			err = net_xmit_त्रुटि_सं(err);
	पूर्ण

	वापस err;
drop:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक pn_raw_send(स्थिर व्योम *data, पूर्णांक len, काष्ठा net_device *dev,
			u16 dst, u16 src, u8 res)
अणु
	काष्ठा sk_buff *skb = alloc_skb(MAX_PHONET_HEADER + len, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	अगर (phonet_address_lookup(dev_net(dev), pn_addr(dst)) == 0)
		skb->pkt_type = PACKET_LOOPBACK;

	skb_reserve(skb, MAX_PHONET_HEADER);
	__skb_put(skb, len);
	skb_copy_to_linear_data(skb, data, len);
	वापस pn_send(skb, dev, dst, src, res, 1);
पूर्ण

/*
 * Create a Phonet header क्रम the skb and send it out. Returns
 * non-zero error code अगर failed. The skb is मुक्तd then.
 */
पूर्णांक pn_skb_send(काष्ठा sock *sk, काष्ठा sk_buff *skb,
		स्थिर काष्ठा sockaddr_pn *target)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा net_device *dev;
	काष्ठा pn_sock *pn = pn_sk(sk);
	पूर्णांक err;
	u16 src, dst;
	u8 daddr, saddr, res;

	src = pn->sobject;
	अगर (target != शून्य) अणु
		dst = pn_sockaddr_get_object(target);
		res = pn_sockaddr_get_resource(target);
	पूर्ण अन्यथा अणु
		dst = pn->करोbject;
		res = pn->resource;
	पूर्ण
	daddr = pn_addr(dst);

	err = -EHOSTUNREACH;
	अगर (sk->sk_bound_dev_अगर)
		dev = dev_get_by_index(net, sk->sk_bound_dev_अगर);
	अन्यथा अगर (phonet_address_lookup(net, daddr) == 0) अणु
		dev = phonet_device_get(net);
		skb->pkt_type = PACKET_LOOPBACK;
	पूर्ण अन्यथा अगर (dst == 0) अणु
		/* Resource routing (small race until phonet_rcv()) */
		काष्ठा sock *sk = pn_find_sock_by_res(net, res);
		अगर (sk)	अणु
			sock_put(sk);
			dev = phonet_device_get(net);
			skb->pkt_type = PACKET_LOOPBACK;
		पूर्ण अन्यथा
			dev = phonet_route_output(net, daddr);
	पूर्ण अन्यथा
		dev = phonet_route_output(net, daddr);

	अगर (!dev || !(dev->flags & IFF_UP))
		जाओ drop;

	saddr = phonet_address_get(dev, daddr);
	अगर (saddr == PN_NO_ADDR)
		जाओ drop;

	अगर (!pn_addr(src))
		src = pn_object(saddr, pn_obj(src));

	err = pn_send(skb, dev, dst, src, res, 0);
	dev_put(dev);
	वापस err;

drop:
	kमुक्त_skb(skb);
	अगर (dev)
		dev_put(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(pn_skb_send);

/* Do not send an error message in response to an error message */
अटल अंतरभूत पूर्णांक can_respond(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा phonethdr *ph;
	स्थिर काष्ठा phoneपंचांगsg *pm;
	u8 submsg_id;

	अगर (!pskb_may_pull(skb, 3))
		वापस 0;

	ph = pn_hdr(skb);
	अगर (ph->pn_res == PN_PREFIX && !pskb_may_pull(skb, 5))
		वापस 0;
	अगर (ph->pn_res == PN_COMMGR) /* indications */
		वापस 0;

	ph = pn_hdr(skb); /* re-acquires the poपूर्णांकer */
	pm = pn_msg(skb);
	अगर (pm->pn_msg_id != PN_COMMON_MESSAGE)
		वापस 1;
	submsg_id = (ph->pn_res == PN_PREFIX)
		? pm->pn_e_submsg_id : pm->pn_submsg_id;
	अगर (submsg_id != PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP &&
		pm->pn_e_submsg_id != PN_COMM_SERVICE_NOT_IDENTIFIED_RESP)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक send_obj_unreachable(काष्ठा sk_buff *rskb)
अणु
	स्थिर काष्ठा phonethdr *oph = pn_hdr(rskb);
	स्थिर काष्ठा phoneपंचांगsg *opm = pn_msg(rskb);
	काष्ठा phoneपंचांगsg resp;

	स_रखो(&resp, 0, माप(resp));
	resp.pn_trans_id = opm->pn_trans_id;
	resp.pn_msg_id = PN_COMMON_MESSAGE;
	अगर (oph->pn_res == PN_PREFIX) अणु
		resp.pn_e_res_id = opm->pn_e_res_id;
		resp.pn_e_submsg_id = PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP;
		resp.pn_e_orig_msg_id = opm->pn_msg_id;
		resp.pn_e_status = 0;
	पूर्ण अन्यथा अणु
		resp.pn_submsg_id = PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP;
		resp.pn_orig_msg_id = opm->pn_msg_id;
		resp.pn_status = 0;
	पूर्ण
	वापस pn_raw_send(&resp, माप(resp), rskb->dev,
				pn_object(oph->pn_sdev, oph->pn_sobj),
				pn_object(oph->pn_rdev, oph->pn_robj),
				oph->pn_res);
पूर्ण

अटल पूर्णांक send_reset_indications(काष्ठा sk_buff *rskb)
अणु
	काष्ठा phonethdr *oph = pn_hdr(rskb);
	अटल स्थिर u8 data[4] = अणु
		0x00 /* trans ID */, 0x10 /* subscribe msg */,
		0x00 /* subscription count */, 0x00 /* dummy */
	पूर्ण;

	वापस pn_raw_send(data, माप(data), rskb->dev,
				pn_object(oph->pn_sdev, 0x00),
				pn_object(oph->pn_rdev, oph->pn_robj),
				PN_COMMGR);
पूर्ण


/* packet type functions */

/*
 * Stuff received packets to associated sockets.
 * On error, वापसs non-zero and releases the skb.
 */
अटल पूर्णांक phonet_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			काष्ठा packet_type *pkttype,
			काष्ठा net_device *orig_dev)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा phonethdr *ph;
	काष्ठा sockaddr_pn sa;
	u16 len;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस NET_RX_DROP;

	/* check we have at least a full Phonet header */
	अगर (!pskb_pull(skb, माप(काष्ठा phonethdr)))
		जाओ out;

	/* check that the advertised length is correct */
	ph = pn_hdr(skb);
	len = get_unaligned_be16(&ph->pn_length);
	अगर (len < 2)
		जाओ out;
	len -= 2;
	अगर ((len > skb->len) || pskb_trim(skb, len))
		जाओ out;
	skb_reset_transport_header(skb);

	pn_skb_get_dst_sockaddr(skb, &sa);

	/* check अगर this is broadcasted */
	अगर (pn_sockaddr_get_addr(&sa) == PNADDR_BROADCAST) अणु
		pn_deliver_sock_broadcast(net, skb);
		जाओ out;
	पूर्ण

	/* resource routing */
	अगर (pn_sockaddr_get_object(&sa) == 0) अणु
		काष्ठा sock *sk = pn_find_sock_by_res(net, sa.spn_resource);
		अगर (sk)
			वापस sk_receive_skb(sk, skb, 0);
	पूर्ण

	/* check अगर we are the destination */
	अगर (phonet_address_lookup(net, pn_sockaddr_get_addr(&sa)) == 0) अणु
		/* Phonet packet input */
		काष्ठा sock *sk = pn_find_sock_by_sa(net, &sa);

		अगर (sk)
			वापस sk_receive_skb(sk, skb, 0);

		अगर (can_respond(skb)) अणु
			send_obj_unreachable(skb);
			send_reset_indications(skb);
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(skb->pkt_type == PACKET_LOOPBACK))
		जाओ out; /* Race between address deletion and loopback */
	अन्यथा अणु
		/* Phonet packet routing */
		काष्ठा net_device *out_dev;

		out_dev = phonet_route_output(net, pn_sockaddr_get_addr(&sa));
		अगर (!out_dev) अणु
			net_dbg_ratelimited("No Phonet route to %02X\n",
					    pn_sockaddr_get_addr(&sa));
			जाओ out;
		पूर्ण

		__skb_push(skb, माप(काष्ठा phonethdr));
		skb->dev = out_dev;
		अगर (out_dev == dev) अणु
			net_dbg_ratelimited("Phonet loop to %02X on %s\n",
					    pn_sockaddr_get_addr(&sa),
					    dev->name);
			जाओ out_dev;
		पूर्ण
		/* Some drivers (e.g. TUN) करो not allocate HW header space */
		अगर (skb_cow_head(skb, out_dev->hard_header_len))
			जाओ out_dev;

		अगर (dev_hard_header(skb, out_dev, ETH_P_PHONET, शून्य, शून्य,
					skb->len) < 0)
			जाओ out_dev;
		dev_queue_xmit(skb);
		dev_put(out_dev);
		वापस NET_RX_SUCCESS;
out_dev:
		dev_put(out_dev);
	पूर्ण

out:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल काष्ठा packet_type phonet_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_PHONET),
	.func = phonet_rcv,
पूर्ण;

अटल DEFINE_MUTEX(proto_tab_lock);

पूर्णांक __init_or_module phonet_proto_रेजिस्टर(अचिन्हित पूर्णांक protocol,
				स्थिर काष्ठा phonet_protocol *pp)
अणु
	पूर्णांक err = 0;

	अगर (protocol >= PHONET_NPROTO)
		वापस -EINVAL;

	err = proto_रेजिस्टर(pp->prot, 1);
	अगर (err)
		वापस err;

	mutex_lock(&proto_tab_lock);
	अगर (proto_tab[protocol])
		err = -EBUSY;
	अन्यथा
		rcu_assign_poपूर्णांकer(proto_tab[protocol], pp);
	mutex_unlock(&proto_tab_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(phonet_proto_रेजिस्टर);

व्योम phonet_proto_unरेजिस्टर(अचिन्हित पूर्णांक protocol,
			स्थिर काष्ठा phonet_protocol *pp)
अणु
	mutex_lock(&proto_tab_lock);
	BUG_ON(proto_tab[protocol] != pp);
	RCU_INIT_POINTER(proto_tab[protocol], शून्य);
	mutex_unlock(&proto_tab_lock);
	synchronize_rcu();
	proto_unरेजिस्टर(pp->prot);
पूर्ण
EXPORT_SYMBOL(phonet_proto_unरेजिस्टर);

/* Module registration */
अटल पूर्णांक __init phonet_init(व्योम)
अणु
	पूर्णांक err;

	err = phonet_device_init();
	अगर (err)
		वापस err;

	pn_sock_init();
	err = sock_रेजिस्टर(&phonet_proto_family);
	अगर (err) अणु
		prपूर्णांकk(KERN_ALERT
			"phonet protocol family initialization failed\n");
		जाओ err_sock;
	पूर्ण

	dev_add_pack(&phonet_packet_type);
	phonet_sysctl_init();

	err = isi_रेजिस्टर();
	अगर (err)
		जाओ err;
	वापस 0;

err:
	phonet_sysctl_निकास();
	sock_unरेजिस्टर(PF_PHONET);
	dev_हटाओ_pack(&phonet_packet_type);
err_sock:
	phonet_device_निकास();
	वापस err;
पूर्ण

अटल व्योम __निकास phonet_निकास(व्योम)
अणु
	isi_unरेजिस्टर();
	phonet_sysctl_निकास();
	sock_unरेजिस्टर(PF_PHONET);
	dev_हटाओ_pack(&phonet_packet_type);
	phonet_device_निकास();
पूर्ण

module_init(phonet_init);
module_निकास(phonet_निकास);
MODULE_DESCRIPTION("Phonet protocol stack for Linux");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_PHONET);

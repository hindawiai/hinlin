<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2003 Intel Corp.
 * Copyright (c) 2001-2002 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions पूर्णांकerface with the sockets layer to implement the
 * SCTP Extensions क्रम the Sockets API.
 *
 * Note that the descriptions from the specअगरication are USER level
 * functions--this file is the functions which populate the काष्ठा proto
 * क्रम SCTP which is the BOTTOM of the sockets पूर्णांकerface.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Narasimha Budihal     <narsi@refcode.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Xingang Guo           <xingang.guo@पूर्णांकel.com>
 *    Daisy Chang           <daisyc@us.ibm.com>
 *    Sridhar Samudrala     <samudrala@us.ibm.com>
 *    Inaky Perez-Gonzalez  <inaky.gonzalez@पूर्णांकel.com>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 *    Ryan Layer	    <rmlayer@us.ibm.com>
 *    Anup Pemmaiah         <pemmaiah@cc.usu.edu>
 *    Kevin Gao             <kevin.gao@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <crypto/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/ip.h>
#समावेश <linux/capability.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/compat.h>
#समावेश <linux/rhashtable.h>

#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/route.h>
#समावेश <net/ipv6.h>
#समावेश <net/inet_common.h>
#समावेश <net/busy_poll.h>

#समावेश <linux/socket.h> /* क्रम sa_family_t */
#समावेश <linux/export.h>
#समावेश <net/sock.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/stream_sched.h>

/* Forward declarations क्रम पूर्णांकernal helper functions. */
अटल bool sctp_ग_लिखोable(काष्ठा sock *sk);
अटल व्योम sctp_wमुक्त(काष्ठा sk_buff *skb);
अटल पूर्णांक sctp_रुको_क्रम_sndbuf(काष्ठा sctp_association *asoc, दीर्घ *समयo_p,
				माप_प्रकार msg_len);
अटल पूर्णांक sctp_रुको_क्रम_packet(काष्ठा sock *sk, पूर्णांक *err, दीर्घ *समयo_p);
अटल पूर्णांक sctp_रुको_क्रम_connect(काष्ठा sctp_association *, दीर्घ *समयo_p);
अटल पूर्णांक sctp_रुको_क्रम_accept(काष्ठा sock *sk, दीर्घ समयo);
अटल व्योम sctp_रुको_क्रम_बंद(काष्ठा sock *sk, दीर्घ समयo);
अटल व्योम sctp_deकाष्ठा_sock(काष्ठा sock *sk);
अटल काष्ठा sctp_af *sctp_sockaddr_af(काष्ठा sctp_sock *opt,
					जोड़ sctp_addr *addr, पूर्णांक len);
अटल पूर्णांक sctp_bindx_add(काष्ठा sock *, काष्ठा sockaddr *, पूर्णांक);
अटल पूर्णांक sctp_bindx_rem(काष्ठा sock *, काष्ठा sockaddr *, पूर्णांक);
अटल पूर्णांक sctp_send_asconf_add_ip(काष्ठा sock *, काष्ठा sockaddr *, पूर्णांक);
अटल पूर्णांक sctp_send_asconf_del_ip(काष्ठा sock *, काष्ठा sockaddr *, पूर्णांक);
अटल पूर्णांक sctp_send_asconf(काष्ठा sctp_association *asoc,
			    काष्ठा sctp_chunk *chunk);
अटल पूर्णांक sctp_करो_bind(काष्ठा sock *, जोड़ sctp_addr *, पूर्णांक);
अटल पूर्णांक sctp_स्वतःbind(काष्ठा sock *sk);
अटल पूर्णांक sctp_sock_migrate(काष्ठा sock *oldsk, काष्ठा sock *newsk,
			     काष्ठा sctp_association *assoc,
			     क्रमागत sctp_socket_type type);

अटल अचिन्हित दीर्घ sctp_memory_pressure;
अटल atomic_दीर्घ_t sctp_memory_allocated;
काष्ठा percpu_counter sctp_sockets_allocated;

अटल व्योम sctp_enter_memory_pressure(काष्ठा sock *sk)
अणु
	sctp_memory_pressure = 1;
पूर्ण


/* Get the sndbuf space available at the समय on the association.  */
अटल अंतरभूत पूर्णांक sctp_wspace(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sock *sk = asoc->base.sk;

	वापस asoc->ep->sndbuf_policy ? sk->sk_sndbuf - asoc->sndbuf_used
				       : sk_stream_wspace(sk);
पूर्ण

/* Increment the used sndbuf space count of the corresponding association by
 * the size of the outgoing data chunk.
 * Also, set the skb deकाष्ठाor क्रम sndbuf accounting later.
 *
 * Since it is always 1-1 between chunk and skb, and also a new skb is always
 * allocated क्रम chunk bundling in sctp_packet_transmit(), we can use the
 * deकाष्ठाor in the data chunk skb क्रम the purpose of the sndbuf space
 * tracking.
 */
अटल अंतरभूत व्योम sctp_set_owner_w(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_association *asoc = chunk->asoc;
	काष्ठा sock *sk = asoc->base.sk;

	/* The sndbuf space is tracked per association.  */
	sctp_association_hold(asoc);

	अगर (chunk->shkey)
		sctp_auth_shkey_hold(chunk->shkey);

	skb_set_owner_w(chunk->skb, sk);

	chunk->skb->deकाष्ठाor = sctp_wमुक्त;
	/* Save the chunk poपूर्णांकer in skb क्रम sctp_wमुक्त to use later.  */
	skb_shinfo(chunk->skb)->deकाष्ठाor_arg = chunk;

	refcount_add(माप(काष्ठा sctp_chunk), &sk->sk_wmem_alloc);
	asoc->sndbuf_used += chunk->skb->truesize + माप(काष्ठा sctp_chunk);
	sk->sk_wmem_queued += chunk->skb->truesize + माप(काष्ठा sctp_chunk);
	sk_mem_अक्षरge(sk, chunk->skb->truesize);
पूर्ण

अटल व्योम sctp_clear_owner_w(काष्ठा sctp_chunk *chunk)
अणु
	skb_orphan(chunk->skb);
पूर्ण

#घोषणा traverse_and_process()	\
करो अणु				\
	msg = chunk->msg;	\
	अगर (msg == prev_msg)	\
		जारी;	\
	list_क्रम_each_entry(c, &msg->chunks, frag_list) अणु	\
		अगर ((clear && asoc->base.sk == c->skb->sk) ||	\
		    (!clear && asoc->base.sk != c->skb->sk))	\
			cb(c);	\
	पूर्ण			\
	prev_msg = msg;		\
पूर्ण जबतक (0)

अटल व्योम sctp_क्रम_each_tx_datachunk(काष्ठा sctp_association *asoc,
				       bool clear,
				       व्योम (*cb)(काष्ठा sctp_chunk *))

अणु
	काष्ठा sctp_datamsg *msg, *prev_msg = शून्य;
	काष्ठा sctp_outq *q = &asoc->outqueue;
	काष्ठा sctp_chunk *chunk, *c;
	काष्ठा sctp_transport *t;

	list_क्रम_each_entry(t, &asoc->peer.transport_addr_list, transports)
		list_क्रम_each_entry(chunk, &t->transmitted, transmitted_list)
			traverse_and_process();

	list_क्रम_each_entry(chunk, &q->retransmit, transmitted_list)
		traverse_and_process();

	list_क्रम_each_entry(chunk, &q->sacked, transmitted_list)
		traverse_and_process();

	list_क्रम_each_entry(chunk, &q->abanकरोned, transmitted_list)
		traverse_and_process();

	list_क्रम_each_entry(chunk, &q->out_chunk_list, list)
		traverse_and_process();
पूर्ण

अटल व्योम sctp_क्रम_each_rx_skb(काष्ठा sctp_association *asoc, काष्ठा sock *sk,
				 व्योम (*cb)(काष्ठा sk_buff *, काष्ठा sock *))

अणु
	काष्ठा sk_buff *skb, *पंचांगp;

	sctp_skb_क्रम_each(skb, &asoc->ulpq.lobby, पंचांगp)
		cb(skb, sk);

	sctp_skb_क्रम_each(skb, &asoc->ulpq.reयंत्र, पंचांगp)
		cb(skb, sk);

	sctp_skb_क्रम_each(skb, &asoc->ulpq.reयंत्र_uo, पंचांगp)
		cb(skb, sk);
पूर्ण

/* Verअगरy that this is a valid address. */
अटल अंतरभूत पूर्णांक sctp_verअगरy_addr(काष्ठा sock *sk, जोड़ sctp_addr *addr,
				   पूर्णांक len)
अणु
	काष्ठा sctp_af *af;

	/* Verअगरy basic sockaddr. */
	af = sctp_sockaddr_af(sctp_sk(sk), addr, len);
	अगर (!af)
		वापस -EINVAL;

	/* Is this a valid SCTP address?  */
	अगर (!af->addr_valid(addr, sctp_sk(sk), शून्य))
		वापस -EINVAL;

	अगर (!sctp_sk(sk)->pf->send_verअगरy(sctp_sk(sk), (addr)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Look up the association by its id.  If this is not a UDP-style
 * socket, the ID field is always ignored.
 */
काष्ठा sctp_association *sctp_id2assoc(काष्ठा sock *sk, sctp_assoc_t id)
अणु
	काष्ठा sctp_association *asoc = शून्य;

	/* If this is not a UDP-style socket, assoc id should be ignored. */
	अगर (!sctp_style(sk, UDP)) अणु
		/* Return शून्य अगर the socket state is not ESTABLISHED. It
		 * could be a TCP-style listening socket or a socket which
		 * hasn't yet called connect() to establish an association.
		 */
		अगर (!sctp_sstate(sk, ESTABLISHED) && !sctp_sstate(sk, CLOSING))
			वापस शून्य;

		/* Get the first and the only association from the list. */
		अगर (!list_empty(&sctp_sk(sk)->ep->asocs))
			asoc = list_entry(sctp_sk(sk)->ep->asocs.next,
					  काष्ठा sctp_association, asocs);
		वापस asoc;
	पूर्ण

	/* Otherwise this is a UDP-style socket. */
	अगर (id <= SCTP_ALL_ASSOC)
		वापस शून्य;

	spin_lock_bh(&sctp_assocs_id_lock);
	asoc = (काष्ठा sctp_association *)idr_find(&sctp_assocs_id, (पूर्णांक)id);
	अगर (asoc && (asoc->base.sk != sk || asoc->base.dead))
		asoc = शून्य;
	spin_unlock_bh(&sctp_assocs_id_lock);

	वापस asoc;
पूर्ण

/* Look up the transport from an address and an assoc id. If both address and
 * id are specअगरied, the associations matching the address and the id should be
 * the same.
 */
अटल काष्ठा sctp_transport *sctp_addr_id2transport(काष्ठा sock *sk,
					      काष्ठा sockaddr_storage *addr,
					      sctp_assoc_t id)
अणु
	काष्ठा sctp_association *addr_asoc = शून्य, *id_asoc = शून्य;
	काष्ठा sctp_af *af = sctp_get_af_specअगरic(addr->ss_family);
	जोड़ sctp_addr *laddr = (जोड़ sctp_addr *)addr;
	काष्ठा sctp_transport *transport;

	अगर (!af || sctp_verअगरy_addr(sk, laddr, af->sockaddr_len))
		वापस शून्य;

	addr_asoc = sctp_endpoपूर्णांक_lookup_assoc(sctp_sk(sk)->ep,
					       laddr,
					       &transport);

	अगर (!addr_asoc)
		वापस शून्य;

	id_asoc = sctp_id2assoc(sk, id);
	अगर (id_asoc && (id_asoc != addr_asoc))
		वापस शून्य;

	sctp_get_pf_specअगरic(sk->sk_family)->addr_to_user(sctp_sk(sk),
						(जोड़ sctp_addr *)addr);

	वापस transport;
पूर्ण

/* API 3.1.2 bind() - UDP Style Syntax
 * The syntax of bind() is,
 *
 *   ret = bind(पूर्णांक sd, काष्ठा sockaddr *addr, पूर्णांक addrlen);
 *
 *   sd      - the socket descriptor वापसed by socket().
 *   addr    - the address काष्ठाure (काष्ठा sockaddr_in or काष्ठा
 *             sockaddr_in6 [RFC 2553]),
 *   addr_len - the size of the address काष्ठाure.
 */
अटल पूर्णांक sctp_bind(काष्ठा sock *sk, काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	पूर्णांक retval = 0;

	lock_sock(sk);

	pr_debug("%s: sk:%p, addr:%p, addr_len:%d\n", __func__, sk,
		 addr, addr_len);

	/* Disallow binding twice. */
	अगर (!sctp_sk(sk)->ep->base.bind_addr.port)
		retval = sctp_करो_bind(sk, (जोड़ sctp_addr *)addr,
				      addr_len);
	अन्यथा
		retval = -EINVAL;

	release_sock(sk);

	वापस retval;
पूर्ण

अटल पूर्णांक sctp_get_port_local(काष्ठा sock *, जोड़ sctp_addr *);

/* Verअगरy this is a valid sockaddr. */
अटल काष्ठा sctp_af *sctp_sockaddr_af(काष्ठा sctp_sock *opt,
					जोड़ sctp_addr *addr, पूर्णांक len)
अणु
	काष्ठा sctp_af *af;

	/* Check minimum size.  */
	अगर (len < माप (काष्ठा sockaddr))
		वापस शून्य;

	अगर (!opt->pf->af_supported(addr->sa.sa_family, opt))
		वापस शून्य;

	अगर (addr->sa.sa_family == AF_INET6) अणु
		अगर (len < SIN6_LEN_RFC2133)
			वापस शून्य;
		/* V4 mapped address are really of AF_INET family */
		अगर (ipv6_addr_v4mapped(&addr->v6.sin6_addr) &&
		    !opt->pf->af_supported(AF_INET, opt))
			वापस शून्य;
	पूर्ण

	/* If we get this far, af is valid. */
	af = sctp_get_af_specअगरic(addr->sa.sa_family);

	अगर (len < af->sockaddr_len)
		वापस शून्य;

	वापस af;
पूर्ण

अटल व्योम sctp_स्वतः_asconf_init(काष्ठा sctp_sock *sp)
अणु
	काष्ठा net *net = sock_net(&sp->inet.sk);

	अगर (net->sctp.शेष_स्वतः_asconf) अणु
		spin_lock(&net->sctp.addr_wq_lock);
		list_add_tail(&sp->स्वतः_asconf_list, &net->sctp.स्वतः_asconf_splist);
		spin_unlock(&net->sctp.addr_wq_lock);
		sp->करो_स्वतः_asconf = 1;
	पूर्ण
पूर्ण

/* Bind a local address either to an endpoपूर्णांक or to an association.  */
अटल पूर्णांक sctp_करो_bind(काष्ठा sock *sk, जोड़ sctp_addr *addr, पूर्णांक len)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_endpoपूर्णांक *ep = sp->ep;
	काष्ठा sctp_bind_addr *bp = &ep->base.bind_addr;
	काष्ठा sctp_af *af;
	अचिन्हित लघु snum;
	पूर्णांक ret = 0;

	/* Common sockaddr verअगरication. */
	af = sctp_sockaddr_af(sp, addr, len);
	अगर (!af) अणु
		pr_debug("%s: sk:%p, newaddr:%p, len:%d EINVAL\n",
			 __func__, sk, addr, len);
		वापस -EINVAL;
	पूर्ण

	snum = ntohs(addr->v4.sin_port);

	pr_debug("%s: sk:%p, new addr:%pISc, port:%d, new port:%d, len:%d\n",
		 __func__, sk, &addr->sa, bp->port, snum, len);

	/* PF specअगरic bind() address verअगरication. */
	अगर (!sp->pf->bind_verअगरy(sp, addr))
		वापस -EADDRNOTAVAIL;

	/* We must either be unbound, or bind to the same port.
	 * It's OK to allow 0 ports अगर we are alपढ़ोy bound.
	 * We'll just inhert an alपढ़ोy bound port in this हाल
	 */
	अगर (bp->port) अणु
		अगर (!snum)
			snum = bp->port;
		अन्यथा अगर (snum != bp->port) अणु
			pr_debug("%s: new port %d doesn't match existing port "
				 "%d\n", __func__, snum, bp->port);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (snum && inet_port_requires_bind_service(net, snum) &&
	    !ns_capable(net->user_ns, CAP_NET_BIND_SERVICE))
		वापस -EACCES;

	/* See अगर the address matches any of the addresses we may have
	 * alपढ़ोy bound beक्रमe checking against other endpoपूर्णांकs.
	 */
	अगर (sctp_bind_addr_match(bp, addr, sp))
		वापस -EINVAL;

	/* Make sure we are allowed to bind here.
	 * The function sctp_get_port_local() करोes duplicate address
	 * detection.
	 */
	addr->v4.sin_port = htons(snum);
	अगर (sctp_get_port_local(sk, addr))
		वापस -EADDRINUSE;

	/* Refresh ephemeral port.  */
	अगर (!bp->port) अणु
		bp->port = inet_sk(sk)->inet_num;
		sctp_स्वतः_asconf_init(sp);
	पूर्ण

	/* Add the address to the bind address list.
	 * Use GFP_ATOMIC since BHs will be disabled.
	 */
	ret = sctp_add_bind_addr(bp, addr, af->sockaddr_len,
				 SCTP_ADDR_SRC, GFP_ATOMIC);

	अगर (ret) अणु
		sctp_put_port(sk);
		वापस ret;
	पूर्ण
	/* Copy back पूर्णांकo socket क्रम माला_लोockname() use. */
	inet_sk(sk)->inet_sport = htons(inet_sk(sk)->inet_num);
	sp->pf->to_sk_saddr(addr, sk);

	वापस ret;
पूर्ण

 /* ADDIP Section 4.1.1 Congestion Control of ASCONF Chunks
 *
 * R1) One and only one ASCONF Chunk MAY be in transit and unacknowledged
 * at any one समय.  If a sender, after sending an ASCONF chunk, decides
 * it needs to transfer another ASCONF Chunk, it MUST रुको until the
 * ASCONF-ACK Chunk वापसs from the previous ASCONF Chunk beक्रमe sending a
 * subsequent ASCONF. Note this restriction binds each side, so at any
 * समय two ASCONF may be in-transit on any given association (one sent
 * from each endpoपूर्णांक).
 */
अटल पूर्णांक sctp_send_asconf(काष्ठा sctp_association *asoc,
			    काष्ठा sctp_chunk *chunk)
अणु
	पूर्णांक retval = 0;

	/* If there is an outstanding ASCONF chunk, queue it क्रम later
	 * transmission.
	 */
	अगर (asoc->addip_last_asconf) अणु
		list_add_tail(&chunk->list, &asoc->addip_chunk_list);
		जाओ out;
	पूर्ण

	/* Hold the chunk until an ASCONF_ACK is received. */
	sctp_chunk_hold(chunk);
	retval = sctp_primitive_ASCONF(asoc->base.net, asoc, chunk);
	अगर (retval)
		sctp_chunk_मुक्त(chunk);
	अन्यथा
		asoc->addip_last_asconf = chunk;

out:
	वापस retval;
पूर्ण

/* Add a list of addresses as bind addresses to local endpoपूर्णांक or
 * association.
 *
 * Basically run through each address specअगरied in the addrs/addrcnt
 * array/length pair, determine अगर it is IPv6 or IPv4 and call
 * sctp_करो_bind() on it.
 *
 * If any of them fails, then the operation will be reversed and the
 * ones that were added will be हटाओd.
 *
 * Only sctp_setsockopt_bindx() is supposed to call this function.
 */
अटल पूर्णांक sctp_bindx_add(काष्ठा sock *sk, काष्ठा sockaddr *addrs, पूर्णांक addrcnt)
अणु
	पूर्णांक cnt;
	पूर्णांक retval = 0;
	व्योम *addr_buf;
	काष्ठा sockaddr *sa_addr;
	काष्ठा sctp_af *af;

	pr_debug("%s: sk:%p, addrs:%p, addrcnt:%d\n", __func__, sk,
		 addrs, addrcnt);

	addr_buf = addrs;
	क्रम (cnt = 0; cnt < addrcnt; cnt++) अणु
		/* The list may contain either IPv4 or IPv6 address;
		 * determine the address length क्रम walking thru the list.
		 */
		sa_addr = addr_buf;
		af = sctp_get_af_specअगरic(sa_addr->sa_family);
		अगर (!af) अणु
			retval = -EINVAL;
			जाओ err_bindx_add;
		पूर्ण

		retval = sctp_करो_bind(sk, (जोड़ sctp_addr *)sa_addr,
				      af->sockaddr_len);

		addr_buf += af->sockaddr_len;

err_bindx_add:
		अगर (retval < 0) अणु
			/* Failed. Cleanup the ones that have been added */
			अगर (cnt > 0)
				sctp_bindx_rem(sk, addrs, cnt);
			वापस retval;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

/* Send an ASCONF chunk with Add IP address parameters to all the peers of the
 * associations that are part of the endpoपूर्णांक indicating that a list of local
 * addresses are added to the endpoपूर्णांक.
 *
 * If any of the addresses is alपढ़ोy in the bind address list of the
 * association, we करो not send the chunk क्रम that association.  But it will not
 * affect other associations.
 *
 * Only sctp_setsockopt_bindx() is supposed to call this function.
 */
अटल पूर्णांक sctp_send_asconf_add_ip(काष्ठा sock		*sk,
				   काष्ठा sockaddr	*addrs,
				   पूर्णांक 			addrcnt)
अणु
	काष्ठा sctp_sock		*sp;
	काष्ठा sctp_endpoपूर्णांक		*ep;
	काष्ठा sctp_association		*asoc;
	काष्ठा sctp_bind_addr		*bp;
	काष्ठा sctp_chunk		*chunk;
	काष्ठा sctp_sockaddr_entry	*laddr;
	जोड़ sctp_addr			*addr;
	जोड़ sctp_addr			saveaddr;
	व्योम				*addr_buf;
	काष्ठा sctp_af			*af;
	काष्ठा list_head		*p;
	पूर्णांक 				i;
	पूर्णांक 				retval = 0;

	sp = sctp_sk(sk);
	ep = sp->ep;

	अगर (!ep->asconf_enable)
		वापस retval;

	pr_debug("%s: sk:%p, addrs:%p, addrcnt:%d\n",
		 __func__, sk, addrs, addrcnt);

	list_क्रम_each_entry(asoc, &ep->asocs, asocs) अणु
		अगर (!asoc->peer.asconf_capable)
			जारी;

		अगर (asoc->peer.addip_disabled_mask & SCTP_PARAM_ADD_IP)
			जारी;

		अगर (!sctp_state(asoc, ESTABLISHED))
			जारी;

		/* Check अगर any address in the packed array of addresses is
		 * in the bind address list of the association. If so,
		 * करो not send the asconf chunk to its peer, but जारी with
		 * other associations.
		 */
		addr_buf = addrs;
		क्रम (i = 0; i < addrcnt; i++) अणु
			addr = addr_buf;
			af = sctp_get_af_specअगरic(addr->v4.sin_family);
			अगर (!af) अणु
				retval = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (sctp_assoc_lookup_laddr(asoc, addr))
				अवरोध;

			addr_buf += af->sockaddr_len;
		पूर्ण
		अगर (i < addrcnt)
			जारी;

		/* Use the first valid address in bind addr list of
		 * association as Address Parameter of ASCONF CHUNK.
		 */
		bp = &asoc->base.bind_addr;
		p = bp->address_list.next;
		laddr = list_entry(p, काष्ठा sctp_sockaddr_entry, list);
		chunk = sctp_make_asconf_update_ip(asoc, &laddr->a, addrs,
						   addrcnt, SCTP_PARAM_ADD_IP);
		अगर (!chunk) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण

		/* Add the new addresses to the bind address list with
		 * use_as_src set to 0.
		 */
		addr_buf = addrs;
		क्रम (i = 0; i < addrcnt; i++) अणु
			addr = addr_buf;
			af = sctp_get_af_specअगरic(addr->v4.sin_family);
			स_नकल(&saveaddr, addr, af->sockaddr_len);
			retval = sctp_add_bind_addr(bp, &saveaddr,
						    माप(saveaddr),
						    SCTP_ADDR_NEW, GFP_ATOMIC);
			addr_buf += af->sockaddr_len;
		पूर्ण
		अगर (asoc->src_out_of_asoc_ok) अणु
			काष्ठा sctp_transport *trans;

			list_क्रम_each_entry(trans,
			    &asoc->peer.transport_addr_list, transports) अणु
				trans->cwnd = min(4*asoc->pathmtu, max_t(__u32,
				    2*asoc->pathmtu, 4380));
				trans->ssthresh = asoc->peer.i.a_rwnd;
				trans->rto = asoc->rto_initial;
				sctp_max_rto(asoc, trans);
				trans->rtt = trans->srtt = trans->rttvar = 0;
				/* Clear the source and route cache */
				sctp_transport_route(trans, शून्य,
						     sctp_sk(asoc->base.sk));
			पूर्ण
		पूर्ण
		retval = sctp_send_asconf(asoc, chunk);
	पूर्ण

out:
	वापस retval;
पूर्ण

/* Remove a list of addresses from bind addresses list.  Do not हटाओ the
 * last address.
 *
 * Basically run through each address specअगरied in the addrs/addrcnt
 * array/length pair, determine अगर it is IPv6 or IPv4 and call
 * sctp_del_bind() on it.
 *
 * If any of them fails, then the operation will be reversed and the
 * ones that were हटाओd will be added back.
 *
 * At least one address has to be left; अगर only one address is
 * available, the operation will वापस -EBUSY.
 *
 * Only sctp_setsockopt_bindx() is supposed to call this function.
 */
अटल पूर्णांक sctp_bindx_rem(काष्ठा sock *sk, काष्ठा sockaddr *addrs, पूर्णांक addrcnt)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_endpoपूर्णांक *ep = sp->ep;
	पूर्णांक cnt;
	काष्ठा sctp_bind_addr *bp = &ep->base.bind_addr;
	पूर्णांक retval = 0;
	व्योम *addr_buf;
	जोड़ sctp_addr *sa_addr;
	काष्ठा sctp_af *af;

	pr_debug("%s: sk:%p, addrs:%p, addrcnt:%d\n",
		 __func__, sk, addrs, addrcnt);

	addr_buf = addrs;
	क्रम (cnt = 0; cnt < addrcnt; cnt++) अणु
		/* If the bind address list is empty or अगर there is only one
		 * bind address, there is nothing more to be हटाओd (we need
		 * at least one address here).
		 */
		अगर (list_empty(&bp->address_list) ||
		    (sctp_list_single_entry(&bp->address_list))) अणु
			retval = -EBUSY;
			जाओ err_bindx_rem;
		पूर्ण

		sa_addr = addr_buf;
		af = sctp_get_af_specअगरic(sa_addr->sa.sa_family);
		अगर (!af) अणु
			retval = -EINVAL;
			जाओ err_bindx_rem;
		पूर्ण

		अगर (!af->addr_valid(sa_addr, sp, शून्य)) अणु
			retval = -EADDRNOTAVAIL;
			जाओ err_bindx_rem;
		पूर्ण

		अगर (sa_addr->v4.sin_port &&
		    sa_addr->v4.sin_port != htons(bp->port)) अणु
			retval = -EINVAL;
			जाओ err_bindx_rem;
		पूर्ण

		अगर (!sa_addr->v4.sin_port)
			sa_addr->v4.sin_port = htons(bp->port);

		/* FIXME - There is probably a need to check अगर sk->sk_saddr and
		 * sk->sk_rcv_addr are currently set to one of the addresses to
		 * be हटाओd. This is something which needs to be looked पूर्णांकo
		 * when we are fixing the outstanding issues with multi-homing
		 * socket routing and failover schemes. Refer to comments in
		 * sctp_करो_bind(). -daisy
		 */
		retval = sctp_del_bind_addr(bp, sa_addr);

		addr_buf += af->sockaddr_len;
err_bindx_rem:
		अगर (retval < 0) अणु
			/* Failed. Add the ones that has been हटाओd back */
			अगर (cnt > 0)
				sctp_bindx_add(sk, addrs, cnt);
			वापस retval;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

/* Send an ASCONF chunk with Delete IP address parameters to all the peers of
 * the associations that are part of the endpoपूर्णांक indicating that a list of
 * local addresses are हटाओd from the endpoपूर्णांक.
 *
 * If any of the addresses is alपढ़ोy in the bind address list of the
 * association, we करो not send the chunk क्रम that association.  But it will not
 * affect other associations.
 *
 * Only sctp_setsockopt_bindx() is supposed to call this function.
 */
अटल पूर्णांक sctp_send_asconf_del_ip(काष्ठा sock		*sk,
				   काष्ठा sockaddr	*addrs,
				   पूर्णांक			addrcnt)
अणु
	काष्ठा sctp_sock	*sp;
	काष्ठा sctp_endpoपूर्णांक	*ep;
	काष्ठा sctp_association	*asoc;
	काष्ठा sctp_transport	*transport;
	काष्ठा sctp_bind_addr	*bp;
	काष्ठा sctp_chunk	*chunk;
	जोड़ sctp_addr		*laddr;
	व्योम			*addr_buf;
	काष्ठा sctp_af		*af;
	काष्ठा sctp_sockaddr_entry *saddr;
	पूर्णांक 			i;
	पूर्णांक 			retval = 0;
	पूर्णांक			stored = 0;

	chunk = शून्य;
	sp = sctp_sk(sk);
	ep = sp->ep;

	अगर (!ep->asconf_enable)
		वापस retval;

	pr_debug("%s: sk:%p, addrs:%p, addrcnt:%d\n",
		 __func__, sk, addrs, addrcnt);

	list_क्रम_each_entry(asoc, &ep->asocs, asocs) अणु

		अगर (!asoc->peer.asconf_capable)
			जारी;

		अगर (asoc->peer.addip_disabled_mask & SCTP_PARAM_DEL_IP)
			जारी;

		अगर (!sctp_state(asoc, ESTABLISHED))
			जारी;

		/* Check अगर any address in the packed array of addresses is
		 * not present in the bind address list of the association.
		 * If so, करो not send the asconf chunk to its peer, but
		 * जारी with other associations.
		 */
		addr_buf = addrs;
		क्रम (i = 0; i < addrcnt; i++) अणु
			laddr = addr_buf;
			af = sctp_get_af_specअगरic(laddr->v4.sin_family);
			अगर (!af) अणु
				retval = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (!sctp_assoc_lookup_laddr(asoc, laddr))
				अवरोध;

			addr_buf += af->sockaddr_len;
		पूर्ण
		अगर (i < addrcnt)
			जारी;

		/* Find one address in the association's bind address list
		 * that is not in the packed array of addresses. This is to
		 * make sure that we करो not delete all the addresses in the
		 * association.
		 */
		bp = &asoc->base.bind_addr;
		laddr = sctp_find_unmatch_addr(bp, (जोड़ sctp_addr *)addrs,
					       addrcnt, sp);
		अगर ((laddr == शून्य) && (addrcnt == 1)) अणु
			अगर (asoc->asconf_addr_del_pending)
				जारी;
			asoc->asconf_addr_del_pending =
			    kzalloc(माप(जोड़ sctp_addr), GFP_ATOMIC);
			अगर (asoc->asconf_addr_del_pending == शून्य) अणु
				retval = -ENOMEM;
				जाओ out;
			पूर्ण
			asoc->asconf_addr_del_pending->sa.sa_family =
				    addrs->sa_family;
			asoc->asconf_addr_del_pending->v4.sin_port =
				    htons(bp->port);
			अगर (addrs->sa_family == AF_INET) अणु
				काष्ठा sockaddr_in *sin;

				sin = (काष्ठा sockaddr_in *)addrs;
				asoc->asconf_addr_del_pending->v4.sin_addr.s_addr = sin->sin_addr.s_addr;
			पूर्ण अन्यथा अगर (addrs->sa_family == AF_INET6) अणु
				काष्ठा sockaddr_in6 *sin6;

				sin6 = (काष्ठा sockaddr_in6 *)addrs;
				asoc->asconf_addr_del_pending->v6.sin6_addr = sin6->sin6_addr;
			पूर्ण

			pr_debug("%s: keep the last address asoc:%p %pISc at %p\n",
				 __func__, asoc, &asoc->asconf_addr_del_pending->sa,
				 asoc->asconf_addr_del_pending);

			asoc->src_out_of_asoc_ok = 1;
			stored = 1;
			जाओ skip_mkasconf;
		पूर्ण

		अगर (laddr == शून्य)
			वापस -EINVAL;

		/* We करो not need RCU protection throughout this loop
		 * because this is करोne under a socket lock from the
		 * setsockopt call.
		 */
		chunk = sctp_make_asconf_update_ip(asoc, laddr, addrs, addrcnt,
						   SCTP_PARAM_DEL_IP);
		अगर (!chunk) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण

skip_mkasconf:
		/* Reset use_as_src flag क्रम the addresses in the bind address
		 * list that are to be deleted.
		 */
		addr_buf = addrs;
		क्रम (i = 0; i < addrcnt; i++) अणु
			laddr = addr_buf;
			af = sctp_get_af_specअगरic(laddr->v4.sin_family);
			list_क्रम_each_entry(saddr, &bp->address_list, list) अणु
				अगर (sctp_cmp_addr_exact(&saddr->a, laddr))
					saddr->state = SCTP_ADDR_DEL;
			पूर्ण
			addr_buf += af->sockaddr_len;
		पूर्ण

		/* Update the route and saddr entries क्रम all the transports
		 * as some of the addresses in the bind address list are
		 * about to be deleted and cannot be used as source addresses.
		 */
		list_क्रम_each_entry(transport, &asoc->peer.transport_addr_list,
					transports) अणु
			sctp_transport_route(transport, शून्य,
					     sctp_sk(asoc->base.sk));
		पूर्ण

		अगर (stored)
			/* We करोn't need to transmit ASCONF */
			जारी;
		retval = sctp_send_asconf(asoc, chunk);
	पूर्ण
out:
	वापस retval;
पूर्ण

/* set addr events to assocs in the endpoपूर्णांक.  ep and addr_wq must be locked */
पूर्णांक sctp_asconf_mgmt(काष्ठा sctp_sock *sp, काष्ठा sctp_sockaddr_entry *addrw)
अणु
	काष्ठा sock *sk = sctp_opt2sk(sp);
	जोड़ sctp_addr *addr;
	काष्ठा sctp_af *af;

	/* It is safe to ग_लिखो port space in caller. */
	addr = &addrw->a;
	addr->v4.sin_port = htons(sp->ep->base.bind_addr.port);
	af = sctp_get_af_specअगरic(addr->sa.sa_family);
	अगर (!af)
		वापस -EINVAL;
	अगर (sctp_verअगरy_addr(sk, addr, af->sockaddr_len))
		वापस -EINVAL;

	अगर (addrw->state == SCTP_ADDR_NEW)
		वापस sctp_send_asconf_add_ip(sk, (काष्ठा sockaddr *)addr, 1);
	अन्यथा
		वापस sctp_send_asconf_del_ip(sk, (काष्ठा sockaddr *)addr, 1);
पूर्ण

/* Helper क्रम tunneling sctp_bindx() requests through sctp_setsockopt()
 *
 * API 8.1
 * पूर्णांक sctp_bindx(पूर्णांक sd, काष्ठा sockaddr *addrs, पूर्णांक addrcnt,
 *                पूर्णांक flags);
 *
 * If sd is an IPv4 socket, the addresses passed must be IPv4 addresses.
 * If the sd is an IPv6 socket, the addresses passed can either be IPv4
 * or IPv6 addresses.
 *
 * A single address may be specअगरied as INADDR_ANY or IN6ADDR_ANY, see
 * Section 3.1.2 क्रम this usage.
 *
 * addrs is a poपूर्णांकer to an array of one or more socket addresses. Each
 * address is contained in its appropriate काष्ठाure (i.e. काष्ठा
 * sockaddr_in or काष्ठा sockaddr_in6) the family of the address type
 * must be used to distinguish the address length (note that this
 * representation is termed a "packed array" of addresses). The caller
 * specअगरies the number of addresses in the array with addrcnt.
 *
 * On success, sctp_bindx() वापसs 0. On failure, sctp_bindx() वापसs
 * -1, and sets त्रुटि_सं to the appropriate error code.
 *
 * For SCTP, the port given in each socket address must be the same, or
 * sctp_bindx() will fail, setting त्रुटि_सं to EINVAL.
 *
 * The flags parameter is क्रमmed from the bitwise OR of zero or more of
 * the following currently defined flags:
 *
 * SCTP_BINDX_ADD_ADDR
 *
 * SCTP_BINDX_REM_ADDR
 *
 * SCTP_BINDX_ADD_ADDR directs SCTP to add the given addresses to the
 * association, and SCTP_BINDX_REM_ADDR directs SCTP to हटाओ the given
 * addresses from the association. The two flags are mutually exclusive;
 * अगर both are given, sctp_bindx() will fail with EINVAL. A caller may
 * not हटाओ all addresses from an association; sctp_bindx() will
 * reject such an attempt with EINVAL.
 *
 * An application can use sctp_bindx(SCTP_BINDX_ADD_ADDR) to associate
 * additional addresses with an endpoपूर्णांक after calling bind().  Or use
 * sctp_bindx(SCTP_BINDX_REM_ADDR) to हटाओ some addresses a listening
 * socket is associated with so that no new association accepted will be
 * associated with those addresses. If the endpoपूर्णांक supports dynamic
 * address a SCTP_BINDX_REM_ADDR or SCTP_BINDX_ADD_ADDR may cause a
 * endpoपूर्णांक to send the appropriate message to the peer to change the
 * peers address lists.
 *
 * Adding and removing addresses from a connected association is
 * optional functionality. Implementations that करो not support this
 * functionality should वापस EOPNOTSUPP.
 *
 * Basically करो nothing but copying the addresses from user to kernel
 * land and invoking either sctp_bindx_add() or sctp_bindx_rem() on the sk.
 * This is used क्रम tunneling the sctp_bindx() request through sctp_setsockopt()
 * from userspace.
 *
 * On निकास there is no need to करो sockfd_put(), sys_setsockopt() करोes
 * it.
 *
 * sk        The sk of the socket
 * addrs     The poपूर्णांकer to the addresses
 * addrssize Size of the addrs buffer
 * op        Operation to perक्रमm (add or हटाओ, see the flags of
 *           sctp_bindx)
 *
 * Returns 0 अगर ok, <0 त्रुटि_सं code on error.
 */
अटल पूर्णांक sctp_setsockopt_bindx(काष्ठा sock *sk, काष्ठा sockaddr *addrs,
				 पूर्णांक addrs_size, पूर्णांक op)
अणु
	पूर्णांक err;
	पूर्णांक addrcnt = 0;
	पूर्णांक walk_size = 0;
	काष्ठा sockaddr *sa_addr;
	व्योम *addr_buf = addrs;
	काष्ठा sctp_af *af;

	pr_debug("%s: sk:%p addrs:%p addrs_size:%d opt:%d\n",
		 __func__, sk, addr_buf, addrs_size, op);

	अगर (unlikely(addrs_size <= 0))
		वापस -EINVAL;

	/* Walk through the addrs buffer and count the number of addresses. */
	जबतक (walk_size < addrs_size) अणु
		अगर (walk_size + माप(sa_family_t) > addrs_size)
			वापस -EINVAL;

		sa_addr = addr_buf;
		af = sctp_get_af_specअगरic(sa_addr->sa_family);

		/* If the address family is not supported or अगर this address
		 * causes the address buffer to overflow वापस EINVAL.
		 */
		अगर (!af || (walk_size + af->sockaddr_len) > addrs_size)
			वापस -EINVAL;
		addrcnt++;
		addr_buf += af->sockaddr_len;
		walk_size += af->sockaddr_len;
	पूर्ण

	/* Do the work. */
	चयन (op) अणु
	हाल SCTP_BINDX_ADD_ADDR:
		/* Allow security module to validate bindx addresses. */
		err = security_sctp_bind_connect(sk, SCTP_SOCKOPT_BINDX_ADD,
						 addrs, addrs_size);
		अगर (err)
			वापस err;
		err = sctp_bindx_add(sk, addrs, addrcnt);
		अगर (err)
			वापस err;
		वापस sctp_send_asconf_add_ip(sk, addrs, addrcnt);
	हाल SCTP_BINDX_REM_ADDR:
		err = sctp_bindx_rem(sk, addrs, addrcnt);
		अगर (err)
			वापस err;
		वापस sctp_send_asconf_del_ip(sk, addrs, addrcnt);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sctp_bind_add(काष्ठा sock *sk, काष्ठा sockaddr *addrs,
		पूर्णांक addrlen)
अणु
	पूर्णांक err;

	lock_sock(sk);
	err = sctp_setsockopt_bindx(sk, addrs, addrlen, SCTP_BINDX_ADD_ADDR);
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक sctp_connect_new_asoc(काष्ठा sctp_endpoपूर्णांक *ep,
				 स्थिर जोड़ sctp_addr *daddr,
				 स्थिर काष्ठा sctp_iniपंचांगsg *init,
				 काष्ठा sctp_transport **tp)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sock *sk = ep->base.sk;
	काष्ठा net *net = sock_net(sk);
	क्रमागत sctp_scope scope;
	पूर्णांक err;

	अगर (sctp_endpoपूर्णांक_is_peeled_off(ep, daddr))
		वापस -EADDRNOTAVAIL;

	अगर (!ep->base.bind_addr.port) अणु
		अगर (sctp_स्वतःbind(sk))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		अगर (inet_port_requires_bind_service(net, ep->base.bind_addr.port) &&
		    !ns_capable(net->user_ns, CAP_NET_BIND_SERVICE))
			वापस -EACCES;
	पूर्ण

	scope = sctp_scope(daddr);
	asoc = sctp_association_new(ep, sk, scope, GFP_KERNEL);
	अगर (!asoc)
		वापस -ENOMEM;

	err = sctp_assoc_set_bind_addr_from_ep(asoc, scope, GFP_KERNEL);
	अगर (err < 0)
		जाओ मुक्त;

	*tp = sctp_assoc_add_peer(asoc, daddr, GFP_KERNEL, SCTP_UNKNOWN);
	अगर (!*tp) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	अगर (!init)
		वापस 0;

	अगर (init->sinit_num_ostreams) अणु
		__u16 outcnt = init->sinit_num_ostreams;

		asoc->c.sinit_num_ostreams = outcnt;
		/* outcnt has been changed, need to re-init stream */
		err = sctp_stream_init(&asoc->stream, outcnt, 0, GFP_KERNEL);
		अगर (err)
			जाओ मुक्त;
	पूर्ण

	अगर (init->sinit_max_instreams)
		asoc->c.sinit_max_instreams = init->sinit_max_instreams;

	अगर (init->sinit_max_attempts)
		asoc->max_init_attempts = init->sinit_max_attempts;

	अगर (init->sinit_max_init_समयo)
		asoc->max_init_समयo =
			msecs_to_jअगरfies(init->sinit_max_init_समयo);

	वापस 0;
मुक्त:
	sctp_association_मुक्त(asoc);
	वापस err;
पूर्ण

अटल पूर्णांक sctp_connect_add_peer(काष्ठा sctp_association *asoc,
				 जोड़ sctp_addr *daddr, पूर्णांक addr_len)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = asoc->ep;
	काष्ठा sctp_association *old;
	काष्ठा sctp_transport *t;
	पूर्णांक err;

	err = sctp_verअगरy_addr(ep->base.sk, daddr, addr_len);
	अगर (err)
		वापस err;

	old = sctp_endpoपूर्णांक_lookup_assoc(ep, daddr, &t);
	अगर (old && old != asoc)
		वापस old->state >= SCTP_STATE_ESTABLISHED ? -EISCONN
							    : -EALREADY;

	अगर (sctp_endpoपूर्णांक_is_peeled_off(ep, daddr))
		वापस -EADDRNOTAVAIL;

	t = sctp_assoc_add_peer(asoc, daddr, GFP_KERNEL, SCTP_UNKNOWN);
	अगर (!t)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* __sctp_connect(काष्ठा sock* sk, काष्ठा sockaddr *kaddrs, पूर्णांक addrs_size)
 *
 * Common routine क्रम handling connect() and sctp_connectx().
 * Connect will come in with just a single address.
 */
अटल पूर्णांक __sctp_connect(काष्ठा sock *sk, काष्ठा sockaddr *kaddrs,
			  पूर्णांक addrs_size, पूर्णांक flags, sctp_assoc_t *assoc_id)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_endpoपूर्णांक *ep = sp->ep;
	काष्ठा sctp_transport *transport;
	काष्ठा sctp_association *asoc;
	व्योम *addr_buf = kaddrs;
	जोड़ sctp_addr *daddr;
	काष्ठा sctp_af *af;
	पूर्णांक walk_size, err;
	दीर्घ समयo;

	अगर (sctp_sstate(sk, ESTABLISHED) || sctp_sstate(sk, CLOSING) ||
	    (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING)))
		वापस -EISCONN;

	daddr = addr_buf;
	af = sctp_get_af_specअगरic(daddr->sa.sa_family);
	अगर (!af || af->sockaddr_len > addrs_size)
		वापस -EINVAL;

	err = sctp_verअगरy_addr(sk, daddr, af->sockaddr_len);
	अगर (err)
		वापस err;

	asoc = sctp_endpoपूर्णांक_lookup_assoc(ep, daddr, &transport);
	अगर (asoc)
		वापस asoc->state >= SCTP_STATE_ESTABLISHED ? -EISCONN
							     : -EALREADY;

	err = sctp_connect_new_asoc(ep, daddr, शून्य, &transport);
	अगर (err)
		वापस err;
	asoc = transport->asoc;

	addr_buf += af->sockaddr_len;
	walk_size = af->sockaddr_len;
	जबतक (walk_size < addrs_size) अणु
		err = -EINVAL;
		अगर (walk_size + माप(sa_family_t) > addrs_size)
			जाओ out_मुक्त;

		daddr = addr_buf;
		af = sctp_get_af_specअगरic(daddr->sa.sa_family);
		अगर (!af || af->sockaddr_len + walk_size > addrs_size)
			जाओ out_मुक्त;

		अगर (asoc->peer.port != ntohs(daddr->v4.sin_port))
			जाओ out_मुक्त;

		err = sctp_connect_add_peer(asoc, daddr, af->sockaddr_len);
		अगर (err)
			जाओ out_मुक्त;

		addr_buf  += af->sockaddr_len;
		walk_size += af->sockaddr_len;
	पूर्ण

	/* In हाल the user of sctp_connectx() wants an association
	 * id back, assign one now.
	 */
	अगर (assoc_id) अणु
		err = sctp_assoc_set_id(asoc, GFP_KERNEL);
		अगर (err < 0)
			जाओ out_मुक्त;
	पूर्ण

	err = sctp_primitive_ASSOCIATE(sock_net(sk), asoc, शून्य);
	अगर (err < 0)
		जाओ out_मुक्त;

	/* Initialize sk's dport and daddr क्रम getpeername() */
	inet_sk(sk)->inet_dport = htons(asoc->peer.port);
	sp->pf->to_sk_daddr(daddr, sk);
	sk->sk_err = 0;

	अगर (assoc_id)
		*assoc_id = asoc->assoc_id;

	समयo = sock_sndसमयo(sk, flags & O_NONBLOCK);
	वापस sctp_रुको_क्रम_connect(asoc, &समयo);

out_मुक्त:
	pr_debug("%s: took out_free path with asoc:%p kaddrs:%p err:%d\n",
		 __func__, asoc, kaddrs, err);
	sctp_association_मुक्त(asoc);
	वापस err;
पूर्ण

/* Helper क्रम tunneling sctp_connectx() requests through sctp_setsockopt()
 *
 * API 8.9
 * पूर्णांक sctp_connectx(पूर्णांक sd, काष्ठा sockaddr *addrs, पूर्णांक addrcnt,
 * 			sctp_assoc_t *asoc);
 *
 * If sd is an IPv4 socket, the addresses passed must be IPv4 addresses.
 * If the sd is an IPv6 socket, the addresses passed can either be IPv4
 * or IPv6 addresses.
 *
 * A single address may be specअगरied as INADDR_ANY or IN6ADDR_ANY, see
 * Section 3.1.2 क्रम this usage.
 *
 * addrs is a poपूर्णांकer to an array of one or more socket addresses. Each
 * address is contained in its appropriate काष्ठाure (i.e. काष्ठा
 * sockaddr_in or काष्ठा sockaddr_in6) the family of the address type
 * must be used to distengish the address length (note that this
 * representation is termed a "packed array" of addresses). The caller
 * specअगरies the number of addresses in the array with addrcnt.
 *
 * On success, sctp_connectx() वापसs 0. It also sets the assoc_id to
 * the association id of the new association.  On failure, sctp_connectx()
 * वापसs -1, and sets त्रुटि_सं to the appropriate error code.  The assoc_id
 * is not touched by the kernel.
 *
 * For SCTP, the port given in each socket address must be the same, or
 * sctp_connectx() will fail, setting त्रुटि_सं to EINVAL.
 *
 * An application can use sctp_connectx to initiate an association with
 * an endpoपूर्णांक that is multi-homed.  Much like sctp_bindx() this call
 * allows a caller to specअगरy multiple addresses at which a peer can be
 * reached.  The way the SCTP stack uses the list of addresses to set up
 * the association is implementation dependent.  This function only
 * specअगरies that the stack will try to make use of all the addresses in
 * the list when needed.
 *
 * Note that the list of addresses passed in is only used क्रम setting up
 * the association.  It करोes not necessarily equal the set of addresses
 * the peer uses क्रम the resulting association.  If the caller wants to
 * find out the set of peer addresses, it must use sctp_getpaddrs() to
 * retrieve them after the association has been set up.
 *
 * Basically करो nothing but copying the addresses from user to kernel
 * land and invoking either sctp_connectx(). This is used क्रम tunneling
 * the sctp_connectx() request through sctp_setsockopt() from userspace.
 *
 * On निकास there is no need to करो sockfd_put(), sys_setsockopt() करोes
 * it.
 *
 * sk        The sk of the socket
 * addrs     The poपूर्णांकer to the addresses
 * addrssize Size of the addrs buffer
 *
 * Returns >=0 अगर ok, <0 त्रुटि_सं code on error.
 */
अटल पूर्णांक __sctp_setsockopt_connectx(काष्ठा sock *sk, काष्ठा sockaddr *kaddrs,
				      पूर्णांक addrs_size, sctp_assoc_t *assoc_id)
अणु
	पूर्णांक err = 0, flags = 0;

	pr_debug("%s: sk:%p addrs:%p addrs_size:%d\n",
		 __func__, sk, kaddrs, addrs_size);

	/* make sure the 1st addr's sa_family is accessible later */
	अगर (unlikely(addrs_size < माप(sa_family_t)))
		वापस -EINVAL;

	/* Allow security module to validate connectx addresses. */
	err = security_sctp_bind_connect(sk, SCTP_SOCKOPT_CONNECTX,
					 (काष्ठा sockaddr *)kaddrs,
					  addrs_size);
	अगर (err)
		वापस err;

	/* in-kernel sockets करोn't generally have a file allocated to them
	 * अगर all they करो is call sock_create_kern().
	 */
	अगर (sk->sk_socket->file)
		flags = sk->sk_socket->file->f_flags;

	वापस __sctp_connect(sk, kaddrs, addrs_size, flags, assoc_id);
पूर्ण

/*
 * This is an older पूर्णांकerface.  It's kept क्रम backward compatibility
 * to the option that करोesn't provide association id.
 */
अटल पूर्णांक sctp_setsockopt_connectx_old(काष्ठा sock *sk,
					काष्ठा sockaddr *kaddrs,
					पूर्णांक addrs_size)
अणु
	वापस __sctp_setsockopt_connectx(sk, kaddrs, addrs_size, शून्य);
पूर्ण

/*
 * New पूर्णांकerface क्रम the API.  The since the API is करोne with a socket
 * option, to make it simple we feed back the association id is as a वापस
 * indication to the call.  Error is always negative and association id is
 * always positive.
 */
अटल पूर्णांक sctp_setsockopt_connectx(काष्ठा sock *sk,
				    काष्ठा sockaddr *kaddrs,
				    पूर्णांक addrs_size)
अणु
	sctp_assoc_t assoc_id = 0;
	पूर्णांक err = 0;

	err = __sctp_setsockopt_connectx(sk, kaddrs, addrs_size, &assoc_id);

	अगर (err)
		वापस err;
	अन्यथा
		वापस assoc_id;
पूर्ण

/*
 * New (hopefully final) पूर्णांकerface क्रम the API.
 * We use the sctp_getaddrs_old काष्ठाure so that use-space library
 * can aव्योम any unnecessary allocations. The only dअगरferent part
 * is that we store the actual length of the address buffer पूर्णांकo the
 * addrs_num काष्ठाure member. That way we can re-use the existing
 * code.
 */
#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_sctp_getaddrs_old अणु
	sctp_assoc_t	assoc_id;
	s32		addr_num;
	compat_uptr_t	addrs;		/* काष्ठा sockaddr * */
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक sctp_माला_लोockopt_connectx3(काष्ठा sock *sk, पूर्णांक len,
				     अक्षर __user *optval,
				     पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_getaddrs_old param;
	sctp_assoc_t assoc_id = 0;
	काष्ठा sockaddr *kaddrs;
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_COMPAT
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_sctp_getaddrs_old param32;

		अगर (len < माप(param32))
			वापस -EINVAL;
		अगर (copy_from_user(&param32, optval, माप(param32)))
			वापस -EFAULT;

		param.assoc_id = param32.assoc_id;
		param.addr_num = param32.addr_num;
		param.addrs = compat_ptr(param32.addrs);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अगर (len < माप(param))
			वापस -EINVAL;
		अगर (copy_from_user(&param, optval, माप(param)))
			वापस -EFAULT;
	पूर्ण

	kaddrs = memdup_user(param.addrs, param.addr_num);
	अगर (IS_ERR(kaddrs))
		वापस PTR_ERR(kaddrs);

	err = __sctp_setsockopt_connectx(sk, kaddrs, param.addr_num, &assoc_id);
	kमुक्त(kaddrs);
	अगर (err == 0 || err == -EINPROGRESS) अणु
		अगर (copy_to_user(optval, &assoc_id, माप(assoc_id)))
			वापस -EFAULT;
		अगर (put_user(माप(assoc_id), optlen))
			वापस -EFAULT;
	पूर्ण

	वापस err;
पूर्ण

/* API 3.1.4 बंद() - UDP Style Syntax
 * Applications use बंद() to perक्रमm graceful shutकरोwn (as described in
 * Section 10.1 of [SCTP]) on ALL the associations currently represented
 * by a UDP-style socket.
 *
 * The syntax is
 *
 *   ret = बंद(पूर्णांक sd);
 *
 *   sd      - the socket descriptor of the associations to be बंदd.
 *
 * To gracefully shutकरोwn a specअगरic association represented by the
 * UDP-style socket, an application should use the sendmsg() call,
 * passing no user data, but including the appropriate flag in the
 * ancillary data (see Section xxxx).
 *
 * If sd in the बंद() call is a branched-off socket representing only
 * one association, the shutकरोwn is perक्रमmed on that association only.
 *
 * 4.1.6 बंद() - TCP Style Syntax
 *
 * Applications use बंद() to gracefully बंद करोwn an association.
 *
 * The syntax is:
 *
 *    पूर्णांक बंद(पूर्णांक sd);
 *
 *      sd      - the socket descriptor of the association to be बंदd.
 *
 * After an application calls बंद() on a socket descriptor, no further
 * socket operations will succeed on that descriptor.
 *
 * API 7.1.4 SO_LINGER
 *
 * An application using the TCP-style socket can use this option to
 * perक्रमm the SCTP ABORT primitive.  The linger option काष्ठाure is:
 *
 *  काष्ठा  linger अणु
 *     पूर्णांक     l_onoff;                // option on/off
 *     पूर्णांक     l_linger;               // linger समय
 * पूर्ण;
 *
 * To enable the option, set l_onoff to 1.  If the l_linger value is set
 * to 0, calling बंद() is the same as the ABORT primitive.  If the
 * value is set to a negative value, the setsockopt() call will वापस
 * an error.  If the value is set to a positive value linger_समय, the
 * बंद() can be blocked क्रम at most linger_समय ms.  If the graceful
 * shutकरोwn phase करोes not finish during this period, बंद() will
 * वापस but the graceful shutकरोwn phase जारीs in the प्रणाली.
 */
अटल व्योम sctp_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा sctp_endpoपूर्णांक *ep;
	काष्ठा sctp_association *asoc;
	काष्ठा list_head *pos, *temp;
	अचिन्हित पूर्णांक data_was_unपढ़ो;

	pr_debug("%s: sk:%p, timeout:%ld\n", __func__, sk, समयout);

	lock_sock_nested(sk, SINGLE_DEPTH_NESTING);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	inet_sk_set_state(sk, SCTP_SS_CLOSING);

	ep = sctp_sk(sk)->ep;

	/* Clean up any skbs sitting on the receive queue.  */
	data_was_unपढ़ो = sctp_queue_purge_ulpevents(&sk->sk_receive_queue);
	data_was_unपढ़ो += sctp_queue_purge_ulpevents(&sctp_sk(sk)->pd_lobby);

	/* Walk all associations on an endpoपूर्णांक.  */
	list_क्रम_each_safe(pos, temp, &ep->asocs) अणु
		asoc = list_entry(pos, काष्ठा sctp_association, asocs);

		अगर (sctp_style(sk, TCP)) अणु
			/* A बंदd association can still be in the list अगर
			 * it beदीर्घs to a TCP-style listening socket that is
			 * not yet accepted. If so, मुक्त it. If not, send an
			 * ABORT or SHUTDOWN based on the linger options.
			 */
			अगर (sctp_state(asoc, CLOSED)) अणु
				sctp_association_मुक्त(asoc);
				जारी;
			पूर्ण
		पूर्ण

		अगर (data_was_unपढ़ो || !skb_queue_empty(&asoc->ulpq.lobby) ||
		    !skb_queue_empty(&asoc->ulpq.reयंत्र) ||
		    !skb_queue_empty(&asoc->ulpq.reयंत्र_uo) ||
		    (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingerसमय)) अणु
			काष्ठा sctp_chunk *chunk;

			chunk = sctp_make_पात_user(asoc, शून्य, 0);
			sctp_primitive_ABORT(net, asoc, chunk);
		पूर्ण अन्यथा
			sctp_primitive_SHUTDOWN(net, asoc, शून्य);
	पूर्ण

	/* On a TCP-style socket, block क्रम at most linger_समय अगर set. */
	अगर (sctp_style(sk, TCP) && समयout)
		sctp_रुको_क्रम_बंद(sk, समयout);

	/* This will run the backlog queue.  */
	release_sock(sk);

	/* Supposedly, no process has access to the socket, but
	 * the net layers still may.
	 * Also, sctp_destroy_sock() needs to be called with addr_wq_lock
	 * held and that should be grabbed beक्रमe socket lock.
	 */
	spin_lock_bh(&net->sctp.addr_wq_lock);
	bh_lock_sock_nested(sk);

	/* Hold the sock, since sk_common_release() will put sock_put()
	 * and we have just a little more cleanup.
	 */
	sock_hold(sk);
	sk_common_release(sk);

	bh_unlock_sock(sk);
	spin_unlock_bh(&net->sctp.addr_wq_lock);

	sock_put(sk);

	SCTP_DBG_OBJCNT_DEC(sock);
पूर्ण

/* Handle EPIPE error. */
अटल पूर्णांक sctp_error(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक err)
अणु
	अगर (err == -EPIPE)
		err = sock_error(sk) ? : -EPIPE;
	अगर (err == -EPIPE && !(flags & MSG_NOSIGNAL))
		send_sig(SIGPIPE, current, 0);
	वापस err;
पूर्ण

/* API 3.1.3 sendmsg() - UDP Style Syntax
 *
 * An application uses sendmsg() and recvmsg() calls to transmit data to
 * and receive data from its peer.
 *
 *  sमाप_प्रकार sendmsg(पूर्णांक socket, स्थिर काष्ठा msghdr *message,
 *                  पूर्णांक flags);
 *
 *  socket  - the socket descriptor of the endpoपूर्णांक.
 *  message - poपूर्णांकer to the msghdr काष्ठाure which contains a single
 *            user message and possibly some ancillary data.
 *
 *            See Section 5 क्रम complete description of the data
 *            काष्ठाures.
 *
 *  flags   - flags sent or received with the user message, see Section
 *            5 क्रम complete description of the flags.
 *
 * Note:  This function could use a reग_लिखो especially when explicit
 * connect support comes in.
 */
/* BUG:  We करो not implement the equivalent of sk_stream_रुको_memory(). */

अटल पूर्णांक sctp_msghdr_parse(स्थिर काष्ठा msghdr *msg,
			     काष्ठा sctp_cmsgs *cmsgs);

अटल पूर्णांक sctp_sendmsg_parse(काष्ठा sock *sk, काष्ठा sctp_cmsgs *cmsgs,
			      काष्ठा sctp_sndrcvinfo *srinfo,
			      स्थिर काष्ठा msghdr *msg, माप_प्रकार msg_len)
अणु
	__u16 sflags;
	पूर्णांक err;

	अगर (sctp_sstate(sk, LISTENING) && sctp_style(sk, TCP))
		वापस -EPIPE;

	अगर (msg_len > sk->sk_sndbuf)
		वापस -EMSGSIZE;

	स_रखो(cmsgs, 0, माप(*cmsgs));
	err = sctp_msghdr_parse(msg, cmsgs);
	अगर (err) अणु
		pr_debug("%s: msghdr parse err:%x\n", __func__, err);
		वापस err;
	पूर्ण

	स_रखो(srinfo, 0, माप(*srinfo));
	अगर (cmsgs->srinfo) अणु
		srinfo->sinfo_stream = cmsgs->srinfo->sinfo_stream;
		srinfo->sinfo_flags = cmsgs->srinfo->sinfo_flags;
		srinfo->sinfo_ppid = cmsgs->srinfo->sinfo_ppid;
		srinfo->sinfo_context = cmsgs->srinfo->sinfo_context;
		srinfo->sinfo_assoc_id = cmsgs->srinfo->sinfo_assoc_id;
		srinfo->sinfo_समयtolive = cmsgs->srinfo->sinfo_समयtolive;
	पूर्ण

	अगर (cmsgs->sinfo) अणु
		srinfo->sinfo_stream = cmsgs->sinfo->snd_sid;
		srinfo->sinfo_flags = cmsgs->sinfo->snd_flags;
		srinfo->sinfo_ppid = cmsgs->sinfo->snd_ppid;
		srinfo->sinfo_context = cmsgs->sinfo->snd_context;
		srinfo->sinfo_assoc_id = cmsgs->sinfo->snd_assoc_id;
	पूर्ण

	अगर (cmsgs->prinfo) अणु
		srinfo->sinfo_समयtolive = cmsgs->prinfo->pr_value;
		SCTP_PR_SET_POLICY(srinfo->sinfo_flags,
				   cmsgs->prinfo->pr_policy);
	पूर्ण

	sflags = srinfo->sinfo_flags;
	अगर (!sflags && msg_len)
		वापस 0;

	अगर (sctp_style(sk, TCP) && (sflags & (SCTP_खातापूर्ण | SCTP_ABORT)))
		वापस -EINVAL;

	अगर (((sflags & SCTP_खातापूर्ण) && msg_len > 0) ||
	    (!(sflags & (SCTP_खातापूर्ण | SCTP_ABORT)) && msg_len == 0))
		वापस -EINVAL;

	अगर ((sflags & SCTP_ADDR_OVER) && !msg->msg_name)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sendmsg_new_asoc(काष्ठा sock *sk, __u16 sflags,
				 काष्ठा sctp_cmsgs *cmsgs,
				 जोड़ sctp_addr *daddr,
				 काष्ठा sctp_transport **tp)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_association *asoc;
	काष्ठा cmsghdr *cmsg;
	__be32 flowinfo = 0;
	काष्ठा sctp_af *af;
	पूर्णांक err;

	*tp = शून्य;

	अगर (sflags & (SCTP_खातापूर्ण | SCTP_ABORT))
		वापस -EINVAL;

	अगर (sctp_style(sk, TCP) && (sctp_sstate(sk, ESTABLISHED) ||
				    sctp_sstate(sk, CLOSING)))
		वापस -EADDRNOTAVAIL;

	/* Label connection socket क्रम first association 1-to-many
	 * style क्रम client sequence socket()->sendmsg(). This
	 * needs to be करोne beक्रमe sctp_assoc_add_peer() as that will
	 * set up the initial packet that needs to account क्रम any
	 * security ip options (CIPSO/CALIPSO) added to the packet.
	 */
	af = sctp_get_af_specअगरic(daddr->sa.sa_family);
	अगर (!af)
		वापस -EINVAL;
	err = security_sctp_bind_connect(sk, SCTP_SENDMSG_CONNECT,
					 (काष्ठा sockaddr *)daddr,
					 af->sockaddr_len);
	अगर (err < 0)
		वापस err;

	err = sctp_connect_new_asoc(ep, daddr, cmsgs->init, tp);
	अगर (err)
		वापस err;
	asoc = (*tp)->asoc;

	अगर (!cmsgs->addrs_msg)
		वापस 0;

	अगर (daddr->sa.sa_family == AF_INET6)
		flowinfo = daddr->v6.sin6_flowinfo;

	/* sendv addr list parse */
	क्रम_each_cmsghdr(cmsg, cmsgs->addrs_msg) अणु
		जोड़ sctp_addr _daddr;
		पूर्णांक dlen;

		अगर (cmsg->cmsg_level != IPPROTO_SCTP ||
		    (cmsg->cmsg_type != SCTP_DSTADDRV4 &&
		     cmsg->cmsg_type != SCTP_DSTADDRV6))
			जारी;

		daddr = &_daddr;
		स_रखो(daddr, 0, माप(*daddr));
		dlen = cmsg->cmsg_len - माप(काष्ठा cmsghdr);
		अगर (cmsg->cmsg_type == SCTP_DSTADDRV4) अणु
			अगर (dlen < माप(काष्ठा in_addr)) अणु
				err = -EINVAL;
				जाओ मुक्त;
			पूर्ण

			dlen = माप(काष्ठा in_addr);
			daddr->v4.sin_family = AF_INET;
			daddr->v4.sin_port = htons(asoc->peer.port);
			स_नकल(&daddr->v4.sin_addr, CMSG_DATA(cmsg), dlen);
		पूर्ण अन्यथा अणु
			अगर (dlen < माप(काष्ठा in6_addr)) अणु
				err = -EINVAL;
				जाओ मुक्त;
			पूर्ण

			dlen = माप(काष्ठा in6_addr);
			daddr->v6.sin6_flowinfo = flowinfo;
			daddr->v6.sin6_family = AF_INET6;
			daddr->v6.sin6_port = htons(asoc->peer.port);
			स_नकल(&daddr->v6.sin6_addr, CMSG_DATA(cmsg), dlen);
		पूर्ण

		err = sctp_connect_add_peer(asoc, daddr, माप(*daddr));
		अगर (err)
			जाओ मुक्त;
	पूर्ण

	वापस 0;

मुक्त:
	sctp_association_मुक्त(asoc);
	वापस err;
पूर्ण

अटल पूर्णांक sctp_sendmsg_check_sflags(काष्ठा sctp_association *asoc,
				     __u16 sflags, काष्ठा msghdr *msg,
				     माप_प्रकार msg_len)
अणु
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा net *net = sock_net(sk);

	अगर (sctp_state(asoc, CLOSED) && sctp_style(sk, TCP))
		वापस -EPIPE;

	अगर ((sflags & SCTP_SENDALL) && sctp_style(sk, UDP) &&
	    !sctp_state(asoc, ESTABLISHED))
		वापस 0;

	अगर (sflags & SCTP_खातापूर्ण) अणु
		pr_debug("%s: shutting down association:%p\n", __func__, asoc);
		sctp_primitive_SHUTDOWN(net, asoc, शून्य);

		वापस 0;
	पूर्ण

	अगर (sflags & SCTP_ABORT) अणु
		काष्ठा sctp_chunk *chunk;

		chunk = sctp_make_पात_user(asoc, msg, msg_len);
		अगर (!chunk)
			वापस -ENOMEM;

		pr_debug("%s: aborting association:%p\n", __func__, asoc);
		sctp_primitive_ABORT(net, asoc, chunk);
		iov_iter_revert(&msg->msg_iter, msg_len);

		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक sctp_sendmsg_to_asoc(काष्ठा sctp_association *asoc,
				काष्ठा msghdr *msg, माप_प्रकार msg_len,
				काष्ठा sctp_transport *transport,
				काष्ठा sctp_sndrcvinfo *sinfo)
अणु
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा sctp_datamsg *datamsg;
	bool रुको_connect = false;
	काष्ठा sctp_chunk *chunk;
	दीर्घ समयo;
	पूर्णांक err;

	अगर (sinfo->sinfo_stream >= asoc->stream.outcnt) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (unlikely(!SCTP_SO(&asoc->stream, sinfo->sinfo_stream)->ext)) अणु
		err = sctp_stream_init_ext(&asoc->stream, sinfo->sinfo_stream);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (sp->disable_fragments && msg_len > asoc->frag_poपूर्णांक) अणु
		err = -EMSGSIZE;
		जाओ err;
	पूर्ण

	अगर (asoc->pmtu_pending) अणु
		अगर (sp->param_flags & SPP_PMTUD_ENABLE)
			sctp_assoc_sync_pmtu(asoc);
		asoc->pmtu_pending = 0;
	पूर्ण

	अगर (sctp_wspace(asoc) < (पूर्णांक)msg_len)
		sctp_prsctp_prune(asoc, sinfo, msg_len - sctp_wspace(asoc));

	अगर (sk_under_memory_pressure(sk))
		sk_mem_reclaim(sk);

	अगर (sctp_wspace(asoc) <= 0 || !sk_wmem_schedule(sk, msg_len)) अणु
		समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);
		err = sctp_रुको_क्रम_sndbuf(asoc, &समयo, msg_len);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (sctp_state(asoc, CLOSED)) अणु
		err = sctp_primitive_ASSOCIATE(net, asoc, शून्य);
		अगर (err)
			जाओ err;

		अगर (asoc->ep->पूर्णांकl_enable) अणु
			समयo = sock_sndसमयo(sk, 0);
			err = sctp_रुको_क्रम_connect(asoc, &समयo);
			अगर (err) अणु
				err = -ESRCH;
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			रुको_connect = true;
		पूर्ण

		pr_debug("%s: we associated primitively\n", __func__);
	पूर्ण

	datamsg = sctp_datamsg_from_user(asoc, sinfo, &msg->msg_iter);
	अगर (IS_ERR(datamsg)) अणु
		err = PTR_ERR(datamsg);
		जाओ err;
	पूर्ण

	asoc->क्रमce_delay = !!(msg->msg_flags & MSG_MORE);

	list_क्रम_each_entry(chunk, &datamsg->chunks, frag_list) अणु
		sctp_chunk_hold(chunk);
		sctp_set_owner_w(chunk);
		chunk->transport = transport;
	पूर्ण

	err = sctp_primitive_SEND(net, asoc, datamsg);
	अगर (err) अणु
		sctp_datamsg_मुक्त(datamsg);
		जाओ err;
	पूर्ण

	pr_debug("%s: we sent primitively\n", __func__);

	sctp_datamsg_put(datamsg);

	अगर (unlikely(रुको_connect)) अणु
		समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);
		sctp_रुको_क्रम_connect(asoc, &समयo);
	पूर्ण

	err = msg_len;

err:
	वापस err;
पूर्ण

अटल जोड़ sctp_addr *sctp_sendmsg_get_daddr(काष्ठा sock *sk,
					       स्थिर काष्ठा msghdr *msg,
					       काष्ठा sctp_cmsgs *cmsgs)
अणु
	जोड़ sctp_addr *daddr = शून्य;
	पूर्णांक err;

	अगर (!sctp_style(sk, UDP_HIGH_BANDWIDTH) && msg->msg_name) अणु
		पूर्णांक len = msg->msg_namelen;

		अगर (len > माप(*daddr))
			len = माप(*daddr);

		daddr = (जोड़ sctp_addr *)msg->msg_name;

		err = sctp_verअगरy_addr(sk, daddr, len);
		अगर (err)
			वापस ERR_PTR(err);
	पूर्ण

	वापस daddr;
पूर्ण

अटल व्योम sctp_sendmsg_update_sinfo(काष्ठा sctp_association *asoc,
				      काष्ठा sctp_sndrcvinfo *sinfo,
				      काष्ठा sctp_cmsgs *cmsgs)
अणु
	अगर (!cmsgs->srinfo && !cmsgs->sinfo) अणु
		sinfo->sinfo_stream = asoc->शेष_stream;
		sinfo->sinfo_ppid = asoc->शेष_ppid;
		sinfo->sinfo_context = asoc->शेष_context;
		sinfo->sinfo_assoc_id = sctp_assoc2id(asoc);

		अगर (!cmsgs->prinfo)
			sinfo->sinfo_flags = asoc->शेष_flags;
	पूर्ण

	अगर (!cmsgs->srinfo && !cmsgs->prinfo)
		sinfo->sinfo_समयtolive = asoc->शेष_समयtolive;

	अगर (cmsgs->authinfo) अणु
		/* Reuse sinfo_tsn to indicate that authinfo was set and
		 * sinfo_ssn to save the keyid on tx path.
		 */
		sinfo->sinfo_tsn = 1;
		sinfo->sinfo_ssn = cmsgs->authinfo->auth_keynumber;
	पूर्ण
पूर्ण

अटल पूर्णांक sctp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार msg_len)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_transport *transport = शून्य;
	काष्ठा sctp_sndrcvinfo _sinfo, *sinfo;
	काष्ठा sctp_association *asoc, *पंचांगp;
	काष्ठा sctp_cmsgs cmsgs;
	जोड़ sctp_addr *daddr;
	bool new = false;
	__u16 sflags;
	पूर्णांक err;

	/* Parse and get snd_info */
	err = sctp_sendmsg_parse(sk, &cmsgs, &_sinfo, msg, msg_len);
	अगर (err)
		जाओ out;

	sinfo  = &_sinfo;
	sflags = sinfo->sinfo_flags;

	/* Get daddr from msg */
	daddr = sctp_sendmsg_get_daddr(sk, msg, &cmsgs);
	अगर (IS_ERR(daddr)) अणु
		err = PTR_ERR(daddr);
		जाओ out;
	पूर्ण

	lock_sock(sk);

	/* SCTP_SENDALL process */
	अगर ((sflags & SCTP_SENDALL) && sctp_style(sk, UDP)) अणु
		list_क्रम_each_entry_safe(asoc, पंचांगp, &ep->asocs, asocs) अणु
			err = sctp_sendmsg_check_sflags(asoc, sflags, msg,
							msg_len);
			अगर (err == 0)
				जारी;
			अगर (err < 0)
				जाओ out_unlock;

			sctp_sendmsg_update_sinfo(asoc, sinfo, &cmsgs);

			err = sctp_sendmsg_to_asoc(asoc, msg, msg_len,
						   शून्य, sinfo);
			अगर (err < 0)
				जाओ out_unlock;

			iov_iter_revert(&msg->msg_iter, err);
		पूर्ण

		जाओ out_unlock;
	पूर्ण

	/* Get and check or create asoc */
	अगर (daddr) अणु
		asoc = sctp_endpoपूर्णांक_lookup_assoc(ep, daddr, &transport);
		अगर (asoc) अणु
			err = sctp_sendmsg_check_sflags(asoc, sflags, msg,
							msg_len);
			अगर (err <= 0)
				जाओ out_unlock;
		पूर्ण अन्यथा अणु
			err = sctp_sendmsg_new_asoc(sk, sflags, &cmsgs, daddr,
						    &transport);
			अगर (err)
				जाओ out_unlock;

			asoc = transport->asoc;
			new = true;
		पूर्ण

		अगर (!sctp_style(sk, TCP) && !(sflags & SCTP_ADDR_OVER))
			transport = शून्य;
	पूर्ण अन्यथा अणु
		asoc = sctp_id2assoc(sk, sinfo->sinfo_assoc_id);
		अगर (!asoc) अणु
			err = -EPIPE;
			जाओ out_unlock;
		पूर्ण

		err = sctp_sendmsg_check_sflags(asoc, sflags, msg, msg_len);
		अगर (err <= 0)
			जाओ out_unlock;
	पूर्ण

	/* Update snd_info with the asoc */
	sctp_sendmsg_update_sinfo(asoc, sinfo, &cmsgs);

	/* Send msg to the asoc */
	err = sctp_sendmsg_to_asoc(asoc, msg, msg_len, transport, sinfo);
	अगर (err < 0 && err != -ESRCH && new)
		sctp_association_मुक्त(asoc);

out_unlock:
	release_sock(sk);
out:
	वापस sctp_error(sk, msg->msg_flags, err);
पूर्ण

/* This is an extended version of skb_pull() that हटाओs the data from the
 * start of a skb even when data is spपढ़ो across the list of skb's in the
 * frag_list. len specअगरies the total amount of data that needs to be हटाओd.
 * when 'len' bytes could be हटाओd from the skb, it वापसs 0.
 * If 'len' exceeds the total skb length,  it वापसs the no. of bytes that
 * could not be हटाओd.
 */
अटल पूर्णांक sctp_skb_pull(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	काष्ठा sk_buff *list;
	पूर्णांक skb_len = skb_headlen(skb);
	पूर्णांक rlen;

	अगर (len <= skb_len) अणु
		__skb_pull(skb, len);
		वापस 0;
	पूर्ण
	len -= skb_len;
	__skb_pull(skb, skb_len);

	skb_walk_frags(skb, list) अणु
		rlen = sctp_skb_pull(list, len);
		skb->len -= (len-rlen);
		skb->data_len -= (len-rlen);

		अगर (!rlen)
			वापस 0;

		len = rlen;
	पूर्ण

	वापस len;
पूर्ण

/* API 3.1.3  recvmsg() - UDP Style Syntax
 *
 *  sमाप_प्रकार recvmsg(पूर्णांक socket, काष्ठा msghdr *message,
 *                    पूर्णांक flags);
 *
 *  socket  - the socket descriptor of the endpoपूर्णांक.
 *  message - poपूर्णांकer to the msghdr काष्ठाure which contains a single
 *            user message and possibly some ancillary data.
 *
 *            See Section 5 क्रम complete description of the data
 *            काष्ठाures.
 *
 *  flags   - flags sent or received with the user message, see Section
 *            5 क्रम complete description of the flags.
 */
अटल पूर्णांक sctp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा sctp_ulpevent *event = शून्य;
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sk_buff *skb, *head_skb;
	पूर्णांक copied;
	पूर्णांक err = 0;
	पूर्णांक skb_len;

	pr_debug("%s: sk:%p, msghdr:%p, len:%zd, noblock:%d, flags:0x%x, "
		 "addr_len:%p)\n", __func__, sk, msg, len, noblock, flags,
		 addr_len);

	lock_sock(sk);

	अगर (sctp_style(sk, TCP) && !sctp_sstate(sk, ESTABLISHED) &&
	    !sctp_sstate(sk, CLOSING) && !sctp_sstate(sk, CLOSED)) अणु
		err = -ENOTCONN;
		जाओ out;
	पूर्ण

	skb = sctp_skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		जाओ out;

	/* Get the total length of the skb including any skb's in the
	 * frag_list.
	 */
	skb_len = skb->len;

	copied = skb_len;
	अगर (copied > len)
		copied = len;

	err = skb_copy_datagram_msg(skb, 0, msg, copied);

	event = sctp_skb2event(skb);

	अगर (err)
		जाओ out_मुक्त;

	अगर (event->chunk && event->chunk->head_skb)
		head_skb = event->chunk->head_skb;
	अन्यथा
		head_skb = skb;
	sock_recv_ts_and_drops(msg, sk, head_skb);
	अगर (sctp_ulpevent_is_notअगरication(event)) अणु
		msg->msg_flags |= MSG_NOTIFICATION;
		sp->pf->event_msgname(event, msg->msg_name, addr_len);
	पूर्ण अन्यथा अणु
		sp->pf->skb_msgname(head_skb, msg->msg_name, addr_len);
	पूर्ण

	/* Check अगर we allow SCTP_NXTINFO. */
	अगर (sp->recvnxtinfo)
		sctp_ulpevent_पढ़ो_nxtinfo(event, msg, sk);
	/* Check अगर we allow SCTP_RCVINFO. */
	अगर (sp->recvrcvinfo)
		sctp_ulpevent_पढ़ो_rcvinfo(event, msg);
	/* Check अगर we allow SCTP_SNDRCVINFO. */
	अगर (sctp_ulpevent_type_enabled(sp->subscribe, SCTP_DATA_IO_EVENT))
		sctp_ulpevent_पढ़ो_sndrcvinfo(event, msg);

	err = copied;

	/* If skb's length exceeds the user's buffer, update the skb and
	 * push it back to the receive_queue so that the next call to
	 * recvmsg() will वापस the reमुख्यing data. Don't set MSG_EOR.
	 */
	अगर (skb_len > copied) अणु
		msg->msg_flags &= ~MSG_EOR;
		अगर (flags & MSG_PEEK)
			जाओ out_मुक्त;
		sctp_skb_pull(skb, copied);
		skb_queue_head(&sk->sk_receive_queue, skb);

		/* When only partial message is copied to the user, increase
		 * rwnd by that amount. If all the data in the skb is पढ़ो,
		 * rwnd is updated when the event is मुक्तd.
		 */
		अगर (!sctp_ulpevent_is_notअगरication(event))
			sctp_assoc_rwnd_increase(event->asoc, copied);
		जाओ out;
	पूर्ण अन्यथा अगर ((event->msg_flags & MSG_NOTIFICATION) ||
		   (event->msg_flags & MSG_EOR))
		msg->msg_flags |= MSG_EOR;
	अन्यथा
		msg->msg_flags &= ~MSG_EOR;

out_मुक्त:
	अगर (flags & MSG_PEEK) अणु
		/* Release the skb reference acquired after peeking the skb in
		 * sctp_skb_recv_datagram().
		 */
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		/* Free the event which includes releasing the reference to
		 * the owner of the skb, मुक्तing the skb and updating the
		 * rwnd.
		 */
		sctp_ulpevent_मुक्त(event);
	पूर्ण
out:
	release_sock(sk);
	वापस err;
पूर्ण

/* 7.1.12 Enable/Disable message fragmentation (SCTP_DISABLE_FRAGMENTS)
 *
 * This option is a on/off flag.  If enabled no SCTP message
 * fragmentation will be perक्रमmed.  Instead अगर a message being sent
 * exceeds the current PMTU size, the message will NOT be sent and
 * instead a error will be indicated to the user.
 */
अटल पूर्णांक sctp_setsockopt_disable_fragments(काष्ठा sock *sk, पूर्णांक *val,
					     अचिन्हित पूर्णांक optlen)
अणु
	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;
	sctp_sk(sk)->disable_fragments = (*val == 0) ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_events(काष्ठा sock *sk, __u8 *sn_type,
				  अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	पूर्णांक i;

	अगर (optlen > माप(काष्ठा sctp_event_subscribe))
		वापस -EINVAL;

	क्रम (i = 0; i < optlen; i++)
		sctp_ulpevent_type_set(&sp->subscribe, SCTP_SN_TYPE_BASE + i,
				       sn_type[i]);

	list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs)
		asoc->subscribe = sctp_sk(sk)->subscribe;

	/* At the समय when a user app subscribes to SCTP_SENDER_DRY_EVENT,
	 * अगर there is no data to be sent or retransmit, the stack will
	 * immediately send up this notअगरication.
	 */
	अगर (sctp_ulpevent_type_enabled(sp->subscribe, SCTP_SENDER_DRY_EVENT)) अणु
		काष्ठा sctp_ulpevent *event;

		asoc = sctp_id2assoc(sk, 0);
		अगर (asoc && sctp_outq_is_empty(&asoc->outqueue)) अणु
			event = sctp_ulpevent_make_sender_dry_event(asoc,
					GFP_USER | __GFP_NOWARN);
			अगर (!event)
				वापस -ENOMEM;

			asoc->stream.si->enqueue_event(&asoc->ulpq, event);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* 7.1.8 Automatic Close of associations (SCTP_AUTOCLOSE)
 *
 * This socket option is applicable to the UDP-style socket only.  When
 * set it will cause associations that are idle क्रम more than the
 * specअगरied number of seconds to स्वतःmatically बंद.  An association
 * being idle is defined an association that has NOT sent or received
 * user data.  The special value of '0' indicates that no स्वतःmatic
 * बंद of any associations should be perक्रमmed.  The option expects an
 * पूर्णांकeger defining the number of seconds of idle समय beक्रमe an
 * association is बंदd.
 */
अटल पूर्णांक sctp_setsockopt_स्वतःबंद(काष्ठा sock *sk, u32 *optval,
				     अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा net *net = sock_net(sk);

	/* Applicable to UDP-style socket only */
	अगर (sctp_style(sk, TCP))
		वापस -EOPNOTSUPP;
	अगर (optlen != माप(पूर्णांक))
		वापस -EINVAL;

	sp->स्वतःबंद = *optval;
	अगर (sp->स्वतःबंद > net->sctp.max_स्वतःबंद)
		sp->स्वतःबंद = net->sctp.max_स्वतःबंद;

	वापस 0;
पूर्ण

/* 7.1.13 Peer Address Parameters (SCTP_PEER_ADDR_PARAMS)
 *
 * Applications can enable or disable heartbeats क्रम any peer address of
 * an association, modअगरy an address's heartbeat पूर्णांकerval, क्रमce a
 * heartbeat to be sent immediately, and adjust the address's maximum
 * number of retransmissions sent beक्रमe an address is considered
 * unreachable.  The following काष्ठाure is used to access and modअगरy an
 * address's parameters:
 *
 *  काष्ठा sctp_paddrparams अणु
 *     sctp_assoc_t            spp_assoc_id;
 *     काष्ठा sockaddr_storage spp_address;
 *     uपूर्णांक32_t                spp_hbपूर्णांकerval;
 *     uपूर्णांक16_t                spp_pathmaxrxt;
 *     uपूर्णांक32_t                spp_pathmtu;
 *     uपूर्णांक32_t                spp_sackdelay;
 *     uपूर्णांक32_t                spp_flags;
 *     uपूर्णांक32_t                spp_ipv6_flowlabel;
 *     uपूर्णांक8_t                 spp_dscp;
 * पूर्ण;
 *
 *   spp_assoc_id    - (one-to-many style socket) This is filled in the
 *                     application, and identअगरies the association क्रम
 *                     this query.
 *   spp_address     - This specअगरies which address is of पूर्णांकerest.
 *   spp_hbपूर्णांकerval  - This contains the value of the heartbeat पूर्णांकerval,
 *                     in milliseconds.  If a  value of zero
 *                     is present in this field then no changes are to
 *                     be made to this parameter.
 *   spp_pathmaxrxt  - This contains the maximum number of
 *                     retransmissions beक्रमe this address shall be
 *                     considered unreachable. If a  value of zero
 *                     is present in this field then no changes are to
 *                     be made to this parameter.
 *   spp_pathmtu     - When Path MTU discovery is disabled the value
 *                     specअगरied here will be the "fixed" path mtu.
 *                     Note that अगर the spp_address field is empty
 *                     then all associations on this address will
 *                     have this fixed path mtu set upon them.
 *
 *   spp_sackdelay   - When delayed sack is enabled, this value specअगरies
 *                     the number of milliseconds that sacks will be delayed
 *                     क्रम. This value will apply to all addresses of an
 *                     association अगर the spp_address field is empty. Note
 *                     also, that अगर delayed sack is enabled and this
 *                     value is set to 0, no change is made to the last
 *                     recorded delayed sack समयr value.
 *
 *   spp_flags       - These flags are used to control various features
 *                     on an association. The flag field may contain
 *                     zero or more of the following options.
 *
 *                     SPP_HB_ENABLE  - Enable heartbeats on the
 *                     specअगरied address. Note that अगर the address
 *                     field is empty all addresses क्रम the association
 *                     have heartbeats enabled upon them.
 *
 *                     SPP_HB_DISABLE - Disable heartbeats on the
 *                     speicअगरed address. Note that अगर the address
 *                     field is empty all addresses क्रम the association
 *                     will have their heartbeats disabled. Note also
 *                     that SPP_HB_ENABLE and SPP_HB_DISABLE are
 *                     mutually exclusive, only one of these two should
 *                     be specअगरied. Enabling both fields will have
 *                     undetermined results.
 *
 *                     SPP_HB_DEMAND - Request a user initiated heartbeat
 *                     to be made immediately.
 *
 *                     SPP_HB_TIME_IS_ZERO - Specअगरy's that the समय क्रम
 *                     heartbeat delayis to be set to the value of 0
 *                     milliseconds.
 *
 *                     SPP_PMTUD_ENABLE - This field will enable PMTU
 *                     discovery upon the specअगरied address. Note that
 *                     अगर the address feild is empty then all addresses
 *                     on the association are effected.
 *
 *                     SPP_PMTUD_DISABLE - This field will disable PMTU
 *                     discovery upon the specअगरied address. Note that
 *                     अगर the address feild is empty then all addresses
 *                     on the association are effected. Not also that
 *                     SPP_PMTUD_ENABLE and SPP_PMTUD_DISABLE are mutually
 *                     exclusive. Enabling both will have undetermined
 *                     results.
 *
 *                     SPP_SACKDELAY_ENABLE - Setting this flag turns
 *                     on delayed sack. The समय specअगरied in spp_sackdelay
 *                     is used to specअगरy the sack delay क्रम this address. Note
 *                     that अगर spp_address is empty then all addresses will
 *                     enable delayed sack and take on the sack delay
 *                     value specअगरied in spp_sackdelay.
 *                     SPP_SACKDELAY_DISABLE - Setting this flag turns
 *                     off delayed sack. If the spp_address field is blank then
 *                     delayed sack is disabled क्रम the entire association. Note
 *                     also that this field is mutually exclusive to
 *                     SPP_SACKDELAY_ENABLE, setting both will have undefined
 *                     results.
 *
 *                     SPP_IPV6_FLOWLABEL:  Setting this flag enables the
 *                     setting of the IPV6 flow label value.  The value is
 *                     contained in the spp_ipv6_flowlabel field.
 *                     Upon retrieval, this flag will be set to indicate that
 *                     the spp_ipv6_flowlabel field has a valid value वापसed.
 *                     If a specअगरic destination address is set (in the
 *                     spp_address field), then the value वापसed is that of
 *                     the address.  If just an association is specअगरied (and
 *                     no address), then the association's शेष flow label
 *                     is वापसed.  If neither an association nor a destination
 *                     is specअगरied, then the socket's शेष flow label is
 *                     वापसed.  For non-IPv6 sockets, this flag will be left
 *                     cleared.
 *
 *                     SPP_DSCP:  Setting this flag enables the setting of the
 *                     Dअगरferentiated Services Code Poपूर्णांक (DSCP) value
 *                     associated with either the association or a specअगरic
 *                     address.  The value is obtained in the spp_dscp field.
 *                     Upon retrieval, this flag will be set to indicate that
 *                     the spp_dscp field has a valid value वापसed.  If a
 *                     specअगरic destination address is set when called (in the
 *                     spp_address field), then that specअगरic destination
 *                     address's DSCP value is वापसed.  If just an association
 *                     is specअगरied, then the association's शेष DSCP is
 *                     वापसed.  If neither an association nor a destination is
 *                     specअगरied, then the socket's शेष DSCP is वापसed.
 *
 *   spp_ipv6_flowlabel
 *                   - This field is used in conjunction with the
 *                     SPP_IPV6_FLOWLABEL flag and contains the IPv6 flow label.
 *                     The 20 least signअगरicant bits are used क्रम the flow
 *                     label.  This setting has precedence over any IPv6-layer
 *                     setting.
 *
 *   spp_dscp        - This field is used in conjunction with the SPP_DSCP flag
 *                     and contains the DSCP.  The 6 most signअगरicant bits are
 *                     used क्रम the DSCP.  This setting has precedence over any
 *                     IPv4- or IPv6- layer setting.
 */
अटल पूर्णांक sctp_apply_peer_addr_params(काष्ठा sctp_paddrparams *params,
				       काष्ठा sctp_transport   *trans,
				       काष्ठा sctp_association *asoc,
				       काष्ठा sctp_sock        *sp,
				       पूर्णांक                      hb_change,
				       पूर्णांक                      pmtud_change,
				       पूर्णांक                      sackdelay_change)
अणु
	पूर्णांक error;

	अगर (params->spp_flags & SPP_HB_DEMAND && trans) अणु
		error = sctp_primitive_REQUESTHEARTBEAT(trans->asoc->base.net,
							trans->asoc, trans);
		अगर (error)
			वापस error;
	पूर्ण

	/* Note that unless the spp_flag is set to SPP_HB_ENABLE the value of
	 * this field is ignored.  Note also that a value of zero indicates
	 * the current setting should be left unchanged.
	 */
	अगर (params->spp_flags & SPP_HB_ENABLE) अणु

		/* Re-zero the पूर्णांकerval अगर the SPP_HB_TIME_IS_ZERO is
		 * set.  This lets us use 0 value when this flag
		 * is set.
		 */
		अगर (params->spp_flags & SPP_HB_TIME_IS_ZERO)
			params->spp_hbपूर्णांकerval = 0;

		अगर (params->spp_hbपूर्णांकerval ||
		    (params->spp_flags & SPP_HB_TIME_IS_ZERO)) अणु
			अगर (trans) अणु
				trans->hbपूर्णांकerval =
				    msecs_to_jअगरfies(params->spp_hbपूर्णांकerval);
			पूर्ण अन्यथा अगर (asoc) अणु
				asoc->hbपूर्णांकerval =
				    msecs_to_jअगरfies(params->spp_hbपूर्णांकerval);
			पूर्ण अन्यथा अणु
				sp->hbपूर्णांकerval = params->spp_hbपूर्णांकerval;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hb_change) अणु
		अगर (trans) अणु
			trans->param_flags =
				(trans->param_flags & ~SPP_HB) | hb_change;
		पूर्ण अन्यथा अगर (asoc) अणु
			asoc->param_flags =
				(asoc->param_flags & ~SPP_HB) | hb_change;
		पूर्ण अन्यथा अणु
			sp->param_flags =
				(sp->param_flags & ~SPP_HB) | hb_change;
		पूर्ण
	पूर्ण

	/* When Path MTU discovery is disabled the value specअगरied here will
	 * be the "fixed" path mtu (i.e. the value of the spp_flags field must
	 * include the flag SPP_PMTUD_DISABLE क्रम this field to have any
	 * effect).
	 */
	अगर ((params->spp_flags & SPP_PMTUD_DISABLE) && params->spp_pathmtu) अणु
		अगर (trans) अणु
			trans->pathmtu = params->spp_pathmtu;
			sctp_assoc_sync_pmtu(asoc);
		पूर्ण अन्यथा अगर (asoc) अणु
			sctp_assoc_set_pmtu(asoc, params->spp_pathmtu);
		पूर्ण अन्यथा अणु
			sp->pathmtu = params->spp_pathmtu;
		पूर्ण
	पूर्ण

	अगर (pmtud_change) अणु
		अगर (trans) अणु
			पूर्णांक update = (trans->param_flags & SPP_PMTUD_DISABLE) &&
				(params->spp_flags & SPP_PMTUD_ENABLE);
			trans->param_flags =
				(trans->param_flags & ~SPP_PMTUD) | pmtud_change;
			अगर (update) अणु
				sctp_transport_pmtu(trans, sctp_opt2sk(sp));
				sctp_assoc_sync_pmtu(asoc);
			पूर्ण
		पूर्ण अन्यथा अगर (asoc) अणु
			asoc->param_flags =
				(asoc->param_flags & ~SPP_PMTUD) | pmtud_change;
		पूर्ण अन्यथा अणु
			sp->param_flags =
				(sp->param_flags & ~SPP_PMTUD) | pmtud_change;
		पूर्ण
	पूर्ण

	/* Note that unless the spp_flag is set to SPP_SACKDELAY_ENABLE the
	 * value of this field is ignored.  Note also that a value of zero
	 * indicates the current setting should be left unchanged.
	 */
	अगर ((params->spp_flags & SPP_SACKDELAY_ENABLE) && params->spp_sackdelay) अणु
		अगर (trans) अणु
			trans->sackdelay =
				msecs_to_jअगरfies(params->spp_sackdelay);
		पूर्ण अन्यथा अगर (asoc) अणु
			asoc->sackdelay =
				msecs_to_jअगरfies(params->spp_sackdelay);
		पूर्ण अन्यथा अणु
			sp->sackdelay = params->spp_sackdelay;
		पूर्ण
	पूर्ण

	अगर (sackdelay_change) अणु
		अगर (trans) अणु
			trans->param_flags =
				(trans->param_flags & ~SPP_SACKDELAY) |
				sackdelay_change;
		पूर्ण अन्यथा अगर (asoc) अणु
			asoc->param_flags =
				(asoc->param_flags & ~SPP_SACKDELAY) |
				sackdelay_change;
		पूर्ण अन्यथा अणु
			sp->param_flags =
				(sp->param_flags & ~SPP_SACKDELAY) |
				sackdelay_change;
		पूर्ण
	पूर्ण

	/* Note that a value of zero indicates the current setting should be
	   left unchanged.
	 */
	अगर (params->spp_pathmaxrxt) अणु
		अगर (trans) अणु
			trans->pathmaxrxt = params->spp_pathmaxrxt;
		पूर्ण अन्यथा अगर (asoc) अणु
			asoc->pathmaxrxt = params->spp_pathmaxrxt;
		पूर्ण अन्यथा अणु
			sp->pathmaxrxt = params->spp_pathmaxrxt;
		पूर्ण
	पूर्ण

	अगर (params->spp_flags & SPP_IPV6_FLOWLABEL) अणु
		अगर (trans) अणु
			अगर (trans->ipaddr.sa.sa_family == AF_INET6) अणु
				trans->flowlabel = params->spp_ipv6_flowlabel &
						   SCTP_FLOWLABEL_VAL_MASK;
				trans->flowlabel |= SCTP_FLOWLABEL_SET_MASK;
			पूर्ण
		पूर्ण अन्यथा अगर (asoc) अणु
			काष्ठा sctp_transport *t;

			list_क्रम_each_entry(t, &asoc->peer.transport_addr_list,
					    transports) अणु
				अगर (t->ipaddr.sa.sa_family != AF_INET6)
					जारी;
				t->flowlabel = params->spp_ipv6_flowlabel &
					       SCTP_FLOWLABEL_VAL_MASK;
				t->flowlabel |= SCTP_FLOWLABEL_SET_MASK;
			पूर्ण
			asoc->flowlabel = params->spp_ipv6_flowlabel &
					  SCTP_FLOWLABEL_VAL_MASK;
			asoc->flowlabel |= SCTP_FLOWLABEL_SET_MASK;
		पूर्ण अन्यथा अगर (sctp_opt2sk(sp)->sk_family == AF_INET6) अणु
			sp->flowlabel = params->spp_ipv6_flowlabel &
					SCTP_FLOWLABEL_VAL_MASK;
			sp->flowlabel |= SCTP_FLOWLABEL_SET_MASK;
		पूर्ण
	पूर्ण

	अगर (params->spp_flags & SPP_DSCP) अणु
		अगर (trans) अणु
			trans->dscp = params->spp_dscp & SCTP_DSCP_VAL_MASK;
			trans->dscp |= SCTP_DSCP_SET_MASK;
		पूर्ण अन्यथा अगर (asoc) अणु
			काष्ठा sctp_transport *t;

			list_क्रम_each_entry(t, &asoc->peer.transport_addr_list,
					    transports) अणु
				t->dscp = params->spp_dscp &
					  SCTP_DSCP_VAL_MASK;
				t->dscp |= SCTP_DSCP_SET_MASK;
			पूर्ण
			asoc->dscp = params->spp_dscp & SCTP_DSCP_VAL_MASK;
			asoc->dscp |= SCTP_DSCP_SET_MASK;
		पूर्ण अन्यथा अणु
			sp->dscp = params->spp_dscp & SCTP_DSCP_VAL_MASK;
			sp->dscp |= SCTP_DSCP_SET_MASK;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_peer_addr_params(काष्ठा sock *sk,
					    काष्ठा sctp_paddrparams *params,
					    अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_transport   *trans = शून्य;
	काष्ठा sctp_association *asoc = शून्य;
	काष्ठा sctp_sock        *sp = sctp_sk(sk);
	पूर्णांक error;
	पूर्णांक hb_change, pmtud_change, sackdelay_change;

	अगर (optlen == ALIGN(दुरत्व(काष्ठा sctp_paddrparams,
					    spp_ipv6_flowlabel), 4)) अणु
		अगर (params->spp_flags & (SPP_DSCP | SPP_IPV6_FLOWLABEL))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (optlen != माप(*params)) अणु
		वापस -EINVAL;
	पूर्ण

	/* Validate flags and value parameters. */
	hb_change        = params->spp_flags & SPP_HB;
	pmtud_change     = params->spp_flags & SPP_PMTUD;
	sackdelay_change = params->spp_flags & SPP_SACKDELAY;

	अगर (hb_change        == SPP_HB ||
	    pmtud_change     == SPP_PMTUD ||
	    sackdelay_change == SPP_SACKDELAY ||
	    params->spp_sackdelay > 500 ||
	    (params->spp_pathmtu &&
	     params->spp_pathmtu < SCTP_DEFAULT_MINSEGMENT))
		वापस -EINVAL;

	/* If an address other than INADDR_ANY is specअगरied, and
	 * no transport is found, then the request is invalid.
	 */
	अगर (!sctp_is_any(sk, (जोड़ sctp_addr *)&params->spp_address)) अणु
		trans = sctp_addr_id2transport(sk, &params->spp_address,
					       params->spp_assoc_id);
		अगर (!trans)
			वापस -EINVAL;
	पूर्ण

	/* Get association, अगर assoc_id != SCTP_FUTURE_ASSOC and the
	 * socket is a one to many style socket, and an association
	 * was not found, then the id was invalid.
	 */
	asoc = sctp_id2assoc(sk, params->spp_assoc_id);
	अगर (!asoc && params->spp_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	/* Heartbeat demand can only be sent on a transport or
	 * association, but not a socket.
	 */
	अगर (params->spp_flags & SPP_HB_DEMAND && !trans && !asoc)
		वापस -EINVAL;

	/* Process parameters. */
	error = sctp_apply_peer_addr_params(params, trans, asoc, sp,
					    hb_change, pmtud_change,
					    sackdelay_change);

	अगर (error)
		वापस error;

	/* If changes are क्रम association, also apply parameters to each
	 * transport.
	 */
	अगर (!trans && asoc) अणु
		list_क्रम_each_entry(trans, &asoc->peer.transport_addr_list,
				transports) अणु
			sctp_apply_peer_addr_params(params, trans, asoc, sp,
						    hb_change, pmtud_change,
						    sackdelay_change);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत __u32 sctp_spp_sackdelay_enable(__u32 param_flags)
अणु
	वापस (param_flags & ~SPP_SACKDELAY) | SPP_SACKDELAY_ENABLE;
पूर्ण

अटल अंतरभूत __u32 sctp_spp_sackdelay_disable(__u32 param_flags)
अणु
	वापस (param_flags & ~SPP_SACKDELAY) | SPP_SACKDELAY_DISABLE;
पूर्ण

अटल व्योम sctp_apply_asoc_delayed_ack(काष्ठा sctp_sack_info *params,
					काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_transport *trans;

	अगर (params->sack_delay) अणु
		asoc->sackdelay = msecs_to_jअगरfies(params->sack_delay);
		asoc->param_flags =
			sctp_spp_sackdelay_enable(asoc->param_flags);
	पूर्ण
	अगर (params->sack_freq == 1) अणु
		asoc->param_flags =
			sctp_spp_sackdelay_disable(asoc->param_flags);
	पूर्ण अन्यथा अगर (params->sack_freq > 1) अणु
		asoc->sackfreq = params->sack_freq;
		asoc->param_flags =
			sctp_spp_sackdelay_enable(asoc->param_flags);
	पूर्ण

	list_क्रम_each_entry(trans, &asoc->peer.transport_addr_list,
			    transports) अणु
		अगर (params->sack_delay) अणु
			trans->sackdelay = msecs_to_jअगरfies(params->sack_delay);
			trans->param_flags =
				sctp_spp_sackdelay_enable(trans->param_flags);
		पूर्ण
		अगर (params->sack_freq == 1) अणु
			trans->param_flags =
				sctp_spp_sackdelay_disable(trans->param_flags);
		पूर्ण अन्यथा अगर (params->sack_freq > 1) अणु
			trans->sackfreq = params->sack_freq;
			trans->param_flags =
				sctp_spp_sackdelay_enable(trans->param_flags);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * 7.1.23.  Get or set delayed ack समयr (SCTP_DELAYED_SACK)
 *
 * This option will effect the way delayed acks are perक्रमmed.  This
 * option allows you to get or set the delayed ack समय, in
 * milliseconds.  It also allows changing the delayed ack frequency.
 * Changing the frequency to 1 disables the delayed sack algorithm.  If
 * the assoc_id is 0, then this sets or माला_लो the endpoपूर्णांकs शेष
 * values.  If the assoc_id field is non-zero, then the set or get
 * effects the specअगरied association क्रम the one to many model (the
 * assoc_id field is ignored by the one to one model).  Note that अगर
 * sack_delay or sack_freq are 0 when setting this option, then the
 * current values will reमुख्य unchanged.
 *
 * काष्ठा sctp_sack_info अणु
 *     sctp_assoc_t            sack_assoc_id;
 *     uपूर्णांक32_t                sack_delay;
 *     uपूर्णांक32_t                sack_freq;
 * पूर्ण;
 *
 * sack_assoc_id -  This parameter, indicates which association the user
 *    is perक्रमming an action upon.  Note that अगर this field's value is
 *    zero then the endpoपूर्णांकs शेष value is changed (effecting future
 *    associations only).
 *
 * sack_delay -  This parameter contains the number of milliseconds that
 *    the user is requesting the delayed ACK समयr be set to.  Note that
 *    this value is defined in the standard to be between 200 and 500
 *    milliseconds.
 *
 * sack_freq -  This parameter contains the number of packets that must
 *    be received beक्रमe a sack is sent without रुकोing क्रम the delay
 *    समयr to expire.  The शेष value क्रम this is 2, setting this
 *    value to 1 will disable the delayed sack algorithm.
 */
अटल पूर्णांक __sctp_setsockopt_delayed_ack(काष्ठा sock *sk,
					 काष्ठा sctp_sack_info *params)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;

	/* Validate value parameter. */
	अगर (params->sack_delay > 500)
		वापस -EINVAL;

	/* Get association, अगर sack_assoc_id != SCTP_FUTURE_ASSOC and the
	 * socket is a one to many style socket, and an association
	 * was not found, then the id was invalid.
	 */
	asoc = sctp_id2assoc(sk, params->sack_assoc_id);
	अगर (!asoc && params->sack_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		sctp_apply_asoc_delayed_ack(params, asoc);

		वापस 0;
	पूर्ण

	अगर (sctp_style(sk, TCP))
		params->sack_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (params->sack_assoc_id == SCTP_FUTURE_ASSOC ||
	    params->sack_assoc_id == SCTP_ALL_ASSOC) अणु
		अगर (params->sack_delay) अणु
			sp->sackdelay = params->sack_delay;
			sp->param_flags =
				sctp_spp_sackdelay_enable(sp->param_flags);
		पूर्ण
		अगर (params->sack_freq == 1) अणु
			sp->param_flags =
				sctp_spp_sackdelay_disable(sp->param_flags);
		पूर्ण अन्यथा अगर (params->sack_freq > 1) अणु
			sp->sackfreq = params->sack_freq;
			sp->param_flags =
				sctp_spp_sackdelay_enable(sp->param_flags);
		पूर्ण
	पूर्ण

	अगर (params->sack_assoc_id == SCTP_CURRENT_ASSOC ||
	    params->sack_assoc_id == SCTP_ALL_ASSOC)
		list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs)
			sctp_apply_asoc_delayed_ack(params, asoc);

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_delayed_ack(काष्ठा sock *sk,
				       काष्ठा sctp_sack_info *params,
				       अचिन्हित पूर्णांक optlen)
अणु
	अगर (optlen == माप(काष्ठा sctp_assoc_value)) अणु
		काष्ठा sctp_assoc_value *v = (काष्ठा sctp_assoc_value *)params;
		काष्ठा sctp_sack_info p;

		pr_warn_ratelimited(DEPRECATED
				    "%s (pid %d) "
				    "Use of struct sctp_assoc_value in delayed_ack socket option.\n"
				    "Use struct sctp_sack_info instead\n",
				    current->comm, task_pid_nr(current));

		p.sack_assoc_id = v->assoc_id;
		p.sack_delay = v->assoc_value;
		p.sack_freq = v->assoc_value ? 0 : 1;
		वापस __sctp_setsockopt_delayed_ack(sk, &p);
	पूर्ण

	अगर (optlen != माप(काष्ठा sctp_sack_info))
		वापस -EINVAL;
	अगर (params->sack_delay == 0 && params->sack_freq == 0)
		वापस 0;
	वापस __sctp_setsockopt_delayed_ack(sk, params);
पूर्ण

/* 7.1.3 Initialization Parameters (SCTP_INITMSG)
 *
 * Applications can specअगरy protocol parameters क्रम the शेष association
 * initialization.  The option name argument to setsockopt() and माला_लोockopt()
 * is SCTP_INITMSG.
 *
 * Setting initialization parameters is effective only on an unconnected
 * socket (क्रम UDP-style sockets only future associations are effected
 * by the change).  With TCP-style sockets, this option is inherited by
 * sockets derived from a listener socket.
 */
अटल पूर्णांक sctp_setsockopt_iniपंचांगsg(काष्ठा sock *sk, काष्ठा sctp_iniपंचांगsg *sinit,
				   अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);

	अगर (optlen != माप(काष्ठा sctp_iniपंचांगsg))
		वापस -EINVAL;

	अगर (sinit->sinit_num_ostreams)
		sp->iniपंचांगsg.sinit_num_ostreams = sinit->sinit_num_ostreams;
	अगर (sinit->sinit_max_instreams)
		sp->iniपंचांगsg.sinit_max_instreams = sinit->sinit_max_instreams;
	अगर (sinit->sinit_max_attempts)
		sp->iniपंचांगsg.sinit_max_attempts = sinit->sinit_max_attempts;
	अगर (sinit->sinit_max_init_समयo)
		sp->iniपंचांगsg.sinit_max_init_समयo = sinit->sinit_max_init_समयo;

	वापस 0;
पूर्ण

/*
 * 7.1.14 Set शेष send parameters (SCTP_DEFAULT_SEND_PARAM)
 *
 *   Applications that wish to use the sendto() प्रणाली call may wish to
 *   specअगरy a शेष set of parameters that would normally be supplied
 *   through the inclusion of ancillary data.  This socket option allows
 *   such an application to set the शेष sctp_sndrcvinfo काष्ठाure.
 *   The application that wishes to use this socket option simply passes
 *   in to this call the sctp_sndrcvinfo काष्ठाure defined in Section
 *   5.2.2) The input parameters accepted by this call include
 *   sinfo_stream, sinfo_flags, sinfo_ppid, sinfo_context,
 *   sinfo_समयtolive.  The user must provide the sinfo_assoc_id field in
 *   to this call अगर the caller is using the UDP model.
 */
अटल पूर्णांक sctp_setsockopt_शेष_send_param(काष्ठा sock *sk,
					      काष्ठा sctp_sndrcvinfo *info,
					      अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;

	अगर (optlen != माप(*info))
		वापस -EINVAL;
	अगर (info->sinfo_flags &
	    ~(SCTP_UNORDERED | SCTP_ADDR_OVER |
	      SCTP_ABORT | SCTP_खातापूर्ण))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, info->sinfo_assoc_id);
	अगर (!asoc && info->sinfo_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		asoc->शेष_stream = info->sinfo_stream;
		asoc->शेष_flags = info->sinfo_flags;
		asoc->शेष_ppid = info->sinfo_ppid;
		asoc->शेष_context = info->sinfo_context;
		asoc->शेष_समयtolive = info->sinfo_समयtolive;

		वापस 0;
	पूर्ण

	अगर (sctp_style(sk, TCP))
		info->sinfo_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (info->sinfo_assoc_id == SCTP_FUTURE_ASSOC ||
	    info->sinfo_assoc_id == SCTP_ALL_ASSOC) अणु
		sp->शेष_stream = info->sinfo_stream;
		sp->शेष_flags = info->sinfo_flags;
		sp->शेष_ppid = info->sinfo_ppid;
		sp->शेष_context = info->sinfo_context;
		sp->शेष_समयtolive = info->sinfo_समयtolive;
	पूर्ण

	अगर (info->sinfo_assoc_id == SCTP_CURRENT_ASSOC ||
	    info->sinfo_assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs) अणु
			asoc->शेष_stream = info->sinfo_stream;
			asoc->शेष_flags = info->sinfo_flags;
			asoc->शेष_ppid = info->sinfo_ppid;
			asoc->शेष_context = info->sinfo_context;
			asoc->शेष_समयtolive = info->sinfo_समयtolive;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* RFC6458, Section 8.1.31. Set/get Default Send Parameters
 * (SCTP_DEFAULT_SNDINFO)
 */
अटल पूर्णांक sctp_setsockopt_शेष_sndinfo(काष्ठा sock *sk,
					   काष्ठा sctp_sndinfo *info,
					   अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;

	अगर (optlen != माप(*info))
		वापस -EINVAL;
	अगर (info->snd_flags &
	    ~(SCTP_UNORDERED | SCTP_ADDR_OVER |
	      SCTP_ABORT | SCTP_खातापूर्ण))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, info->snd_assoc_id);
	अगर (!asoc && info->snd_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		asoc->शेष_stream = info->snd_sid;
		asoc->शेष_flags = info->snd_flags;
		asoc->शेष_ppid = info->snd_ppid;
		asoc->शेष_context = info->snd_context;

		वापस 0;
	पूर्ण

	अगर (sctp_style(sk, TCP))
		info->snd_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (info->snd_assoc_id == SCTP_FUTURE_ASSOC ||
	    info->snd_assoc_id == SCTP_ALL_ASSOC) अणु
		sp->शेष_stream = info->snd_sid;
		sp->शेष_flags = info->snd_flags;
		sp->शेष_ppid = info->snd_ppid;
		sp->शेष_context = info->snd_context;
	पूर्ण

	अगर (info->snd_assoc_id == SCTP_CURRENT_ASSOC ||
	    info->snd_assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs) अणु
			asoc->शेष_stream = info->snd_sid;
			asoc->शेष_flags = info->snd_flags;
			asoc->शेष_ppid = info->snd_ppid;
			asoc->शेष_context = info->snd_context;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* 7.1.10 Set Primary Address (SCTP_PRIMARY_ADDR)
 *
 * Requests that the local SCTP stack use the enबंदd peer address as
 * the association primary.  The enबंदd address must be one of the
 * association peer's addresses.
 */
अटल पूर्णांक sctp_setsockopt_primary_addr(काष्ठा sock *sk, काष्ठा sctp_prim *prim,
					अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_transport *trans;
	काष्ठा sctp_af *af;
	पूर्णांक err;

	अगर (optlen != माप(काष्ठा sctp_prim))
		वापस -EINVAL;

	/* Allow security module to validate address but need address len. */
	af = sctp_get_af_specअगरic(prim->ssp_addr.ss_family);
	अगर (!af)
		वापस -EINVAL;

	err = security_sctp_bind_connect(sk, SCTP_PRIMARY_ADDR,
					 (काष्ठा sockaddr *)&prim->ssp_addr,
					 af->sockaddr_len);
	अगर (err)
		वापस err;

	trans = sctp_addr_id2transport(sk, &prim->ssp_addr, prim->ssp_assoc_id);
	अगर (!trans)
		वापस -EINVAL;

	sctp_assoc_set_primary(trans->asoc, trans);

	वापस 0;
पूर्ण

/*
 * 7.1.5 SCTP_NODELAY
 *
 * Turn on/off any Nagle-like algorithm.  This means that packets are
 * generally sent as soon as possible and no unnecessary delays are
 * पूर्णांकroduced, at the cost of more packets in the network.  Expects an
 *  पूर्णांकeger boolean flag.
 */
अटल पूर्णांक sctp_setsockopt_nodelay(काष्ठा sock *sk, पूर्णांक *val,
				   अचिन्हित पूर्णांक optlen)
अणु
	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;
	sctp_sk(sk)->nodelay = (*val == 0) ? 0 : 1;
	वापस 0;
पूर्ण

/*
 *
 * 7.1.1 SCTP_RTOINFO
 *
 * The protocol parameters used to initialize and bound retransmission
 * समयout (RTO) are tunable. sctp_rtoinfo काष्ठाure is used to access
 * and modअगरy these parameters.
 * All parameters are समय values, in milliseconds.  A value of 0, when
 * modअगरying the parameters, indicates that the current value should not
 * be changed.
 *
 */
अटल पूर्णांक sctp_setsockopt_rtoinfo(काष्ठा sock *sk,
				   काष्ठा sctp_rtoinfo *rtoinfo,
				   अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;
	अचिन्हित दीर्घ rto_min, rto_max;
	काष्ठा sctp_sock *sp = sctp_sk(sk);

	अगर (optlen != माप (काष्ठा sctp_rtoinfo))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, rtoinfo->srto_assoc_id);

	/* Set the values to the specअगरic association */
	अगर (!asoc && rtoinfo->srto_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	rto_max = rtoinfo->srto_max;
	rto_min = rtoinfo->srto_min;

	अगर (rto_max)
		rto_max = asoc ? msecs_to_jअगरfies(rto_max) : rto_max;
	अन्यथा
		rto_max = asoc ? asoc->rto_max : sp->rtoinfo.srto_max;

	अगर (rto_min)
		rto_min = asoc ? msecs_to_jअगरfies(rto_min) : rto_min;
	अन्यथा
		rto_min = asoc ? asoc->rto_min : sp->rtoinfo.srto_min;

	अगर (rto_min > rto_max)
		वापस -EINVAL;

	अगर (asoc) अणु
		अगर (rtoinfo->srto_initial != 0)
			asoc->rto_initial =
				msecs_to_jअगरfies(rtoinfo->srto_initial);
		asoc->rto_max = rto_max;
		asoc->rto_min = rto_min;
	पूर्ण अन्यथा अणु
		/* If there is no association or the association-id = 0
		 * set the values to the endpoपूर्णांक.
		 */
		अगर (rtoinfo->srto_initial != 0)
			sp->rtoinfo.srto_initial = rtoinfo->srto_initial;
		sp->rtoinfo.srto_max = rto_max;
		sp->rtoinfo.srto_min = rto_min;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *
 * 7.1.2 SCTP_ASSOCINFO
 *
 * This option is used to tune the maximum retransmission attempts
 * of the association.
 * Returns an error अगर the new association retransmission value is
 * greater than the sum of the retransmission value  of the peer.
 * See [SCTP] क्रम more inक्रमmation.
 *
 */
अटल पूर्णांक sctp_setsockopt_associnfo(काष्ठा sock *sk,
				     काष्ठा sctp_assocparams *assocparams,
				     अचिन्हित पूर्णांक optlen)
अणु

	काष्ठा sctp_association *asoc;

	अगर (optlen != माप(काष्ठा sctp_assocparams))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, assocparams->sasoc_assoc_id);

	अगर (!asoc && assocparams->sasoc_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	/* Set the values to the specअगरic association */
	अगर (asoc) अणु
		अगर (assocparams->sasoc_asocmaxrxt != 0) अणु
			__u32 path_sum = 0;
			पूर्णांक   paths = 0;
			काष्ठा sctp_transport *peer_addr;

			list_क्रम_each_entry(peer_addr, &asoc->peer.transport_addr_list,
					transports) अणु
				path_sum += peer_addr->pathmaxrxt;
				paths++;
			पूर्ण

			/* Only validate asocmaxrxt अगर we have more than
			 * one path/transport.  We करो this because path
			 * retransmissions are only counted when we have more
			 * then one path.
			 */
			अगर (paths > 1 &&
			    assocparams->sasoc_asocmaxrxt > path_sum)
				वापस -EINVAL;

			asoc->max_retrans = assocparams->sasoc_asocmaxrxt;
		पूर्ण

		अगर (assocparams->sasoc_cookie_lअगरe != 0)
			asoc->cookie_lअगरe =
				ms_to_kसमय(assocparams->sasoc_cookie_lअगरe);
	पूर्ण अन्यथा अणु
		/* Set the values to the endpoपूर्णांक */
		काष्ठा sctp_sock *sp = sctp_sk(sk);

		अगर (assocparams->sasoc_asocmaxrxt != 0)
			sp->assocparams.sasoc_asocmaxrxt =
						assocparams->sasoc_asocmaxrxt;
		अगर (assocparams->sasoc_cookie_lअगरe != 0)
			sp->assocparams.sasoc_cookie_lअगरe =
						assocparams->sasoc_cookie_lअगरe;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * 7.1.16 Set/clear IPv4 mapped addresses (SCTP_I_WANT_MAPPED_V4_ADDR)
 *
 * This socket option is a boolean flag which turns on or off mapped V4
 * addresses.  If this option is turned on and the socket is type
 * PF_INET6, then IPv4 addresses will be mapped to V6 representation.
 * If this option is turned off, then no mapping will be करोne of V4
 * addresses and a user will receive both PF_INET6 and PF_INET type
 * addresses on the socket.
 */
अटल पूर्णांक sctp_setsockopt_mappedv4(काष्ठा sock *sk, पूर्णांक *val,
				    अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;
	अगर (*val)
		sp->v4mapped = 1;
	अन्यथा
		sp->v4mapped = 0;

	वापस 0;
पूर्ण

/*
 * 8.1.16.  Get or Set the Maximum Fragmentation Size (SCTP_MAXSEG)
 * This option will get or set the maximum size to put in any outgoing
 * SCTP DATA chunk.  If a message is larger than this size it will be
 * fragmented by SCTP पूर्णांकo the specअगरied size.  Note that the underlying
 * SCTP implementation may fragment पूर्णांकo smaller sized chunks when the
 * PMTU of the underlying association is smaller than the value set by
 * the user.  The शेष value क्रम this option is '0' which indicates
 * the user is NOT limiting fragmentation and only the PMTU will effect
 * SCTP's choice of DATA chunk size.  Note also that values set larger
 * than the maximum size of an IP datagram will effectively let SCTP
 * control fragmentation (i.e. the same as setting this option to 0).
 *
 * The following काष्ठाure is used to access and modअगरy this parameter:
 *
 * काष्ठा sctp_assoc_value अणु
 *   sctp_assoc_t assoc_id;
 *   uपूर्णांक32_t assoc_value;
 * पूर्ण;
 *
 * assoc_id:  This parameter is ignored क्रम one-to-one style sockets.
 *    For one-to-many style sockets this parameter indicates which
 *    association the user is perक्रमming an action upon.  Note that अगर
 *    this field's value is zero then the endpoपूर्णांकs शेष value is
 *    changed (effecting future associations only).
 * assoc_value:  This parameter specअगरies the maximum size in bytes.
 */
अटल पूर्णांक sctp_setsockopt_maxseg(काष्ठा sock *sk,
				  काष्ठा sctp_assoc_value *params,
				  अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	sctp_assoc_t assoc_id;
	पूर्णांक val;

	अगर (optlen == माप(पूर्णांक)) अणु
		pr_warn_ratelimited(DEPRECATED
				    "%s (pid %d) "
				    "Use of int in maxseg socket option.\n"
				    "Use struct sctp_assoc_value instead\n",
				    current->comm, task_pid_nr(current));
		assoc_id = SCTP_FUTURE_ASSOC;
		val = *(पूर्णांक *)params;
	पूर्ण अन्यथा अगर (optlen == माप(काष्ठा sctp_assoc_value)) अणु
		assoc_id = params->assoc_id;
		val = params->assoc_value;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	asoc = sctp_id2assoc(sk, assoc_id);
	अगर (!asoc && assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (val) अणु
		पूर्णांक min_len, max_len;
		__u16 datasize = asoc ? sctp_datachk_len(&asoc->stream) :
				 माप(काष्ठा sctp_data_chunk);

		min_len = sctp_min_frag_poपूर्णांक(sp, datasize);
		max_len = SCTP_MAX_CHUNK_LEN - datasize;

		अगर (val < min_len || val > max_len)
			वापस -EINVAL;
	पूर्ण

	अगर (asoc) अणु
		asoc->user_frag = val;
		sctp_assoc_update_frag_poपूर्णांक(asoc);
	पूर्ण अन्यथा अणु
		sp->user_frag = val;
	पूर्ण

	वापस 0;
पूर्ण


/*
 *  7.1.9 Set Peer Primary Address (SCTP_SET_PEER_PRIMARY_ADDR)
 *
 *   Requests that the peer mark the enबंदd address as the association
 *   primary. The enबंदd address must be one of the association's
 *   locally bound addresses. The following काष्ठाure is used to make a
 *   set primary request:
 */
अटल पूर्णांक sctp_setsockopt_peer_primary_addr(काष्ठा sock *sk,
					     काष्ठा sctp_setpeerprim *prim,
					     अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock	*sp;
	काष्ठा sctp_association	*asoc = शून्य;
	काष्ठा sctp_chunk	*chunk;
	काष्ठा sctp_af		*af;
	पूर्णांक 			err;

	sp = sctp_sk(sk);

	अगर (!sp->ep->asconf_enable)
		वापस -EPERM;

	अगर (optlen != माप(काष्ठा sctp_setpeerprim))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, prim->sspp_assoc_id);
	अगर (!asoc)
		वापस -EINVAL;

	अगर (!asoc->peer.asconf_capable)
		वापस -EPERM;

	अगर (asoc->peer.addip_disabled_mask & SCTP_PARAM_SET_PRIMARY)
		वापस -EPERM;

	अगर (!sctp_state(asoc, ESTABLISHED))
		वापस -ENOTCONN;

	af = sctp_get_af_specअगरic(prim->sspp_addr.ss_family);
	अगर (!af)
		वापस -EINVAL;

	अगर (!af->addr_valid((जोड़ sctp_addr *)&prim->sspp_addr, sp, शून्य))
		वापस -EADDRNOTAVAIL;

	अगर (!sctp_assoc_lookup_laddr(asoc, (जोड़ sctp_addr *)&prim->sspp_addr))
		वापस -EADDRNOTAVAIL;

	/* Allow security module to validate address. */
	err = security_sctp_bind_connect(sk, SCTP_SET_PEER_PRIMARY_ADDR,
					 (काष्ठा sockaddr *)&prim->sspp_addr,
					 af->sockaddr_len);
	अगर (err)
		वापस err;

	/* Create an ASCONF chunk with SET_PRIMARY parameter	*/
	chunk = sctp_make_asconf_set_prim(asoc,
					  (जोड़ sctp_addr *)&prim->sspp_addr);
	अगर (!chunk)
		वापस -ENOMEM;

	err = sctp_send_asconf(asoc, chunk);

	pr_debug("%s: we set peer primary addr primitively\n", __func__);

	वापस err;
पूर्ण

अटल पूर्णांक sctp_setsockopt_adaptation_layer(काष्ठा sock *sk,
					    काष्ठा sctp_setadaptation *adapt,
					    अचिन्हित पूर्णांक optlen)
अणु
	अगर (optlen != माप(काष्ठा sctp_setadaptation))
		वापस -EINVAL;

	sctp_sk(sk)->adaptation_ind = adapt->ssb_adaptation_ind;

	वापस 0;
पूर्ण

/*
 * 7.1.29.  Set or Get the शेष context (SCTP_CONTEXT)
 *
 * The context field in the sctp_sndrcvinfo काष्ठाure is normally only
 * used when a failed message is retrieved holding the value that was
 * sent करोwn on the actual send call.  This option allows the setting of
 * a शेष context on an association basis that will be received on
 * पढ़ोing messages from the peer.  This is especially helpful in the
 * one-2-many model क्रम an application to keep some reference to an
 * पूर्णांकernal state machine that is processing messages on the
 * association.  Note that the setting of this value only effects
 * received messages from the peer and करोes not effect the value that is
 * saved with outbound messages.
 */
अटल पूर्णांक sctp_setsockopt_context(काष्ठा sock *sk,
				   काष्ठा sctp_assoc_value *params,
				   अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;

	अगर (optlen != माप(काष्ठा sctp_assoc_value))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		asoc->शेष_rcv_context = params->assoc_value;

		वापस 0;
	पूर्ण

	अगर (sctp_style(sk, TCP))
		params->assoc_id = SCTP_FUTURE_ASSOC;

	अगर (params->assoc_id == SCTP_FUTURE_ASSOC ||
	    params->assoc_id == SCTP_ALL_ASSOC)
		sp->शेष_rcv_context = params->assoc_value;

	अगर (params->assoc_id == SCTP_CURRENT_ASSOC ||
	    params->assoc_id == SCTP_ALL_ASSOC)
		list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs)
			asoc->शेष_rcv_context = params->assoc_value;

	वापस 0;
पूर्ण

/*
 * 7.1.24.  Get or set fragmented पूर्णांकerleave (SCTP_FRAGMENT_INTERLEAVE)
 *
 * This options will at a minimum specअगरy अगर the implementation is करोing
 * fragmented पूर्णांकerleave.  Fragmented पूर्णांकerleave, क्रम a one to many
 * socket, is when subsequent calls to receive a message may वापस
 * parts of messages from dअगरferent associations.  Some implementations
 * may allow you to turn this value on or off.  If so, when turned off,
 * no fragment पूर्णांकerleave will occur (which will cause a head of line
 * blocking amongst multiple associations sharing the same one to many
 * socket).  When this option is turned on, then each receive call may
 * come from a dअगरferent association (thus the user must receive data
 * with the extended calls (e.g. sctp_recvmsg) to keep track of which
 * association each receive beदीर्घs to.
 *
 * This option takes a boolean value.  A non-zero value indicates that
 * fragmented पूर्णांकerleave is on.  A value of zero indicates that
 * fragmented पूर्णांकerleave is off.
 *
 * Note that it is important that an implementation that allows this
 * option to be turned on, have it off by शेष.  Otherwise an unaware
 * application using the one to many model may become confused and act
 * incorrectly.
 */
अटल पूर्णांक sctp_setsockopt_fragment_पूर्णांकerleave(काष्ठा sock *sk, पूर्णांक *val,
					       अचिन्हित पूर्णांक optlen)
अणु
	अगर (optlen != माप(पूर्णांक))
		वापस -EINVAL;

	sctp_sk(sk)->frag_पूर्णांकerleave = !!*val;

	अगर (!sctp_sk(sk)->frag_पूर्णांकerleave)
		sctp_sk(sk)->ep->पूर्णांकl_enable = 0;

	वापस 0;
पूर्ण

/*
 * 8.1.21.  Set or Get the SCTP Partial Delivery Poपूर्णांक
 *       (SCTP_PARTIAL_DELIVERY_POINT)
 *
 * This option will set or get the SCTP partial delivery poपूर्णांक.  This
 * poपूर्णांक is the size of a message where the partial delivery API will be
 * invoked to help मुक्त up rwnd space क्रम the peer.  Setting this to a
 * lower value will cause partial deliveries to happen more often.  The
 * calls argument is an पूर्णांकeger that sets or माला_लो the partial delivery
 * poपूर्णांक.  Note also that the call will fail अगर the user attempts to set
 * this value larger than the socket receive buffer size.
 *
 * Note that any single message having a length smaller than or equal to
 * the SCTP partial delivery poपूर्णांक will be delivered in one single पढ़ो
 * call as दीर्घ as the user provided buffer is large enough to hold the
 * message.
 */
अटल पूर्णांक sctp_setsockopt_partial_delivery_poपूर्णांक(काष्ठा sock *sk, u32 *val,
						  अचिन्हित पूर्णांक optlen)
अणु
	अगर (optlen != माप(u32))
		वापस -EINVAL;

	/* Note: We द्विगुन the receive buffer from what the user sets
	 * it to be, also initial rwnd is based on rcvbuf/2.
	 */
	अगर (*val > (sk->sk_rcvbuf >> 1))
		वापस -EINVAL;

	sctp_sk(sk)->pd_poपूर्णांक = *val;

	वापस 0; /* is this the right error code? */
पूर्ण

/*
 * 7.1.28.  Set or Get the maximum burst (SCTP_MAX_BURST)
 *
 * This option will allow a user to change the maximum burst of packets
 * that can be emitted by this association.  Note that the शेष value
 * is 4, and some implementations may restrict this setting so that it
 * can only be lowered.
 *
 * NOTE: This text करोesn't seem right.  Do this on a socket basis with
 * future associations inheriting the socket value.
 */
अटल पूर्णांक sctp_setsockopt_maxburst(काष्ठा sock *sk,
				    काष्ठा sctp_assoc_value *params,
				    अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	sctp_assoc_t assoc_id;
	u32 assoc_value;

	अगर (optlen == माप(पूर्णांक)) अणु
		pr_warn_ratelimited(DEPRECATED
				    "%s (pid %d) "
				    "Use of int in max_burst socket option deprecated.\n"
				    "Use struct sctp_assoc_value instead\n",
				    current->comm, task_pid_nr(current));
		assoc_id = SCTP_FUTURE_ASSOC;
		assoc_value = *((पूर्णांक *)params);
	पूर्ण अन्यथा अगर (optlen == माप(काष्ठा sctp_assoc_value)) अणु
		assoc_id = params->assoc_id;
		assoc_value = params->assoc_value;
	पूर्ण अन्यथा
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, assoc_id);
	अगर (!asoc && assoc_id > SCTP_ALL_ASSOC && sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		asoc->max_burst = assoc_value;

		वापस 0;
	पूर्ण

	अगर (sctp_style(sk, TCP))
		assoc_id = SCTP_FUTURE_ASSOC;

	अगर (assoc_id == SCTP_FUTURE_ASSOC || assoc_id == SCTP_ALL_ASSOC)
		sp->max_burst = assoc_value;

	अगर (assoc_id == SCTP_CURRENT_ASSOC || assoc_id == SCTP_ALL_ASSOC)
		list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs)
			asoc->max_burst = assoc_value;

	वापस 0;
पूर्ण

/*
 * 7.1.18.  Add a chunk that must be authenticated (SCTP_AUTH_CHUNK)
 *
 * This set option adds a chunk type that the user is requesting to be
 * received only in an authenticated way.  Changes to the list of chunks
 * will only effect future associations on the socket.
 */
अटल पूर्णांक sctp_setsockopt_auth_chunk(काष्ठा sock *sk,
				      काष्ठा sctp_authchunk *val,
				      अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;

	अगर (!ep->auth_enable)
		वापस -EACCES;

	अगर (optlen != माप(काष्ठा sctp_authchunk))
		वापस -EINVAL;

	चयन (val->sauth_chunk) अणु
	हाल SCTP_CID_INIT:
	हाल SCTP_CID_INIT_ACK:
	हाल SCTP_CID_SHUTDOWN_COMPLETE:
	हाल SCTP_CID_AUTH:
		वापस -EINVAL;
	पूर्ण

	/* add this chunk id to the endpoपूर्णांक */
	वापस sctp_auth_ep_add_chunkid(ep, val->sauth_chunk);
पूर्ण

/*
 * 7.1.19.  Get or set the list of supported HMAC Identअगरiers (SCTP_HMAC_IDENT)
 *
 * This option माला_लो or sets the list of HMAC algorithms that the local
 * endpoपूर्णांक requires the peer to use.
 */
अटल पूर्णांक sctp_setsockopt_hmac_ident(काष्ठा sock *sk,
				      काष्ठा sctp_hmacalgo *hmacs,
				      अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	u32 idents;

	अगर (!ep->auth_enable)
		वापस -EACCES;

	अगर (optlen < माप(काष्ठा sctp_hmacalgo))
		वापस -EINVAL;
	optlen = min_t(अचिन्हित पूर्णांक, optlen, माप(काष्ठा sctp_hmacalgo) +
					     SCTP_AUTH_NUM_HMACS * माप(u16));

	idents = hmacs->shmac_num_idents;
	अगर (idents == 0 || idents > SCTP_AUTH_NUM_HMACS ||
	    (idents * माप(u16)) > (optlen - माप(काष्ठा sctp_hmacalgo)))
		वापस -EINVAL;

	वापस sctp_auth_ep_set_hmacs(ep, hmacs);
पूर्ण

/*
 * 7.1.20.  Set a shared key (SCTP_AUTH_KEY)
 *
 * This option will set a shared secret key which is used to build an
 * association shared key.
 */
अटल पूर्णांक sctp_setsockopt_auth_key(काष्ठा sock *sk,
				    काष्ठा sctp_authkey *authkey,
				    अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_association *asoc;
	पूर्णांक ret = -EINVAL;

	अगर (optlen <= माप(काष्ठा sctp_authkey))
		वापस -EINVAL;
	/* authkey->sca_keylength is u16, so optlen can't be bigger than
	 * this.
	 */
	optlen = min_t(अचिन्हित पूर्णांक, optlen, अच_लघु_उच्च + माप(*authkey));

	अगर (authkey->sca_keylength > optlen - माप(*authkey))
		जाओ out;

	asoc = sctp_id2assoc(sk, authkey->sca_assoc_id);
	अगर (!asoc && authkey->sca_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	अगर (asoc) अणु
		ret = sctp_auth_set_key(ep, asoc, authkey);
		जाओ out;
	पूर्ण

	अगर (sctp_style(sk, TCP))
		authkey->sca_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (authkey->sca_assoc_id == SCTP_FUTURE_ASSOC ||
	    authkey->sca_assoc_id == SCTP_ALL_ASSOC) अणु
		ret = sctp_auth_set_key(ep, asoc, authkey);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = 0;

	अगर (authkey->sca_assoc_id == SCTP_CURRENT_ASSOC ||
	    authkey->sca_assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &ep->asocs, asocs) अणु
			पूर्णांक res = sctp_auth_set_key(ep, asoc, authkey);

			अगर (res && !ret)
				ret = res;
		पूर्ण
	पूर्ण

out:
	memzero_explicit(authkey, optlen);
	वापस ret;
पूर्ण

/*
 * 7.1.21.  Get or set the active shared key (SCTP_AUTH_ACTIVE_KEY)
 *
 * This option will get or set the active shared key to be used to build
 * the association shared key.
 */
अटल पूर्णांक sctp_setsockopt_active_key(काष्ठा sock *sk,
				      काष्ठा sctp_authkeyid *val,
				      अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_association *asoc;
	पूर्णांक ret = 0;

	अगर (optlen != माप(काष्ठा sctp_authkeyid))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, val->scact_assoc_id);
	अगर (!asoc && val->scact_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc)
		वापस sctp_auth_set_active_key(ep, asoc, val->scact_keynumber);

	अगर (sctp_style(sk, TCP))
		val->scact_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (val->scact_assoc_id == SCTP_FUTURE_ASSOC ||
	    val->scact_assoc_id == SCTP_ALL_ASSOC) अणु
		ret = sctp_auth_set_active_key(ep, asoc, val->scact_keynumber);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (val->scact_assoc_id == SCTP_CURRENT_ASSOC ||
	    val->scact_assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &ep->asocs, asocs) अणु
			पूर्णांक res = sctp_auth_set_active_key(ep, asoc,
							   val->scact_keynumber);

			अगर (res && !ret)
				ret = res;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * 7.1.22.  Delete a shared key (SCTP_AUTH_DELETE_KEY)
 *
 * This set option will delete a shared secret key from use.
 */
अटल पूर्णांक sctp_setsockopt_del_key(काष्ठा sock *sk,
				   काष्ठा sctp_authkeyid *val,
				   अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_association *asoc;
	पूर्णांक ret = 0;

	अगर (optlen != माप(काष्ठा sctp_authkeyid))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, val->scact_assoc_id);
	अगर (!asoc && val->scact_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc)
		वापस sctp_auth_del_key_id(ep, asoc, val->scact_keynumber);

	अगर (sctp_style(sk, TCP))
		val->scact_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (val->scact_assoc_id == SCTP_FUTURE_ASSOC ||
	    val->scact_assoc_id == SCTP_ALL_ASSOC) अणु
		ret = sctp_auth_del_key_id(ep, asoc, val->scact_keynumber);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (val->scact_assoc_id == SCTP_CURRENT_ASSOC ||
	    val->scact_assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &ep->asocs, asocs) अणु
			पूर्णांक res = sctp_auth_del_key_id(ep, asoc,
						       val->scact_keynumber);

			अगर (res && !ret)
				ret = res;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * 8.3.4  Deactivate a Shared Key (SCTP_AUTH_DEACTIVATE_KEY)
 *
 * This set option will deactivate a shared secret key.
 */
अटल पूर्णांक sctp_setsockopt_deactivate_key(काष्ठा sock *sk,
					  काष्ठा sctp_authkeyid *val,
					  अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_association *asoc;
	पूर्णांक ret = 0;

	अगर (optlen != माप(काष्ठा sctp_authkeyid))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, val->scact_assoc_id);
	अगर (!asoc && val->scact_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc)
		वापस sctp_auth_deact_key_id(ep, asoc, val->scact_keynumber);

	अगर (sctp_style(sk, TCP))
		val->scact_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (val->scact_assoc_id == SCTP_FUTURE_ASSOC ||
	    val->scact_assoc_id == SCTP_ALL_ASSOC) अणु
		ret = sctp_auth_deact_key_id(ep, asoc, val->scact_keynumber);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (val->scact_assoc_id == SCTP_CURRENT_ASSOC ||
	    val->scact_assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &ep->asocs, asocs) अणु
			पूर्णांक res = sctp_auth_deact_key_id(ep, asoc,
							 val->scact_keynumber);

			अगर (res && !ret)
				ret = res;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * 8.1.23 SCTP_AUTO_ASCONF
 *
 * This option will enable or disable the use of the स्वतःmatic generation of
 * ASCONF chunks to add and delete addresses to an existing association.  Note
 * that this option has two caveats namely: a) it only affects sockets that
 * are bound to all addresses available to the SCTP stack, and b) the प्रणाली
 * administrator may have an overriding control that turns the ASCONF feature
 * off no matter what setting the socket option may have.
 * This option expects an पूर्णांकeger boolean flag, where a non-zero value turns on
 * the option, and a zero value turns off the option.
 * Note. In this implementation, socket operation overrides शेष parameter
 * being set by sysctl as well as FreeBSD implementation
 */
अटल पूर्णांक sctp_setsockopt_स्वतः_asconf(काष्ठा sock *sk, पूर्णांक *val,
					अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;
	अगर (!sctp_is_ep_boundall(sk) && *val)
		वापस -EINVAL;
	अगर ((*val && sp->करो_स्वतः_asconf) || (!*val && !sp->करो_स्वतः_asconf))
		वापस 0;

	spin_lock_bh(&sock_net(sk)->sctp.addr_wq_lock);
	अगर (*val == 0 && sp->करो_स्वतः_asconf) अणु
		list_del(&sp->स्वतः_asconf_list);
		sp->करो_स्वतः_asconf = 0;
	पूर्ण अन्यथा अगर (*val && !sp->करो_स्वतः_asconf) अणु
		list_add_tail(&sp->स्वतः_asconf_list,
		    &sock_net(sk)->sctp.स्वतः_asconf_splist);
		sp->करो_स्वतः_asconf = 1;
	पूर्ण
	spin_unlock_bh(&sock_net(sk)->sctp.addr_wq_lock);
	वापस 0;
पूर्ण

/*
 * SCTP_PEER_ADDR_THLDS
 *
 * This option allows us to alter the partially failed threshold क्रम one or all
 * transports in an association.  See Section 6.1 of:
 * http://www.ietf.org/id/draft-nishida-tsvwg-sctp-failover-05.txt
 */
अटल पूर्णांक sctp_setsockopt_paddr_thresholds(काष्ठा sock *sk,
					    काष्ठा sctp_paddrthlds_v2 *val,
					    अचिन्हित पूर्णांक optlen, bool v2)
अणु
	काष्ठा sctp_transport *trans;
	काष्ठा sctp_association *asoc;
	पूर्णांक len;

	len = v2 ? माप(*val) : माप(काष्ठा sctp_paddrthlds);
	अगर (optlen < len)
		वापस -EINVAL;

	अगर (v2 && val->spt_pathpfthld > val->spt_pathcpthld)
		वापस -EINVAL;

	अगर (!sctp_is_any(sk, (स्थिर जोड़ sctp_addr *)&val->spt_address)) अणु
		trans = sctp_addr_id2transport(sk, &val->spt_address,
					       val->spt_assoc_id);
		अगर (!trans)
			वापस -ENOENT;

		अगर (val->spt_pathmaxrxt)
			trans->pathmaxrxt = val->spt_pathmaxrxt;
		अगर (v2)
			trans->ps_retrans = val->spt_pathcpthld;
		trans->pf_retrans = val->spt_pathpfthld;

		वापस 0;
	पूर्ण

	asoc = sctp_id2assoc(sk, val->spt_assoc_id);
	अगर (!asoc && val->spt_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		list_क्रम_each_entry(trans, &asoc->peer.transport_addr_list,
				    transports) अणु
			अगर (val->spt_pathmaxrxt)
				trans->pathmaxrxt = val->spt_pathmaxrxt;
			अगर (v2)
				trans->ps_retrans = val->spt_pathcpthld;
			trans->pf_retrans = val->spt_pathpfthld;
		पूर्ण

		अगर (val->spt_pathmaxrxt)
			asoc->pathmaxrxt = val->spt_pathmaxrxt;
		अगर (v2)
			asoc->ps_retrans = val->spt_pathcpthld;
		asoc->pf_retrans = val->spt_pathpfthld;
	पूर्ण अन्यथा अणु
		काष्ठा sctp_sock *sp = sctp_sk(sk);

		अगर (val->spt_pathmaxrxt)
			sp->pathmaxrxt = val->spt_pathmaxrxt;
		अगर (v2)
			sp->ps_retrans = val->spt_pathcpthld;
		sp->pf_retrans = val->spt_pathpfthld;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_recvrcvinfo(काष्ठा sock *sk, पूर्णांक *val,
				       अचिन्हित पूर्णांक optlen)
अणु
	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	sctp_sk(sk)->recvrcvinfo = (*val == 0) ? 0 : 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_recvnxtinfo(काष्ठा sock *sk, पूर्णांक *val,
				       अचिन्हित पूर्णांक optlen)
अणु
	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	sctp_sk(sk)->recvnxtinfo = (*val == 0) ? 0 : 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_pr_supported(काष्ठा sock *sk,
					काष्ठा sctp_assoc_value *params,
					अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;

	अगर (optlen != माप(*params))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	sctp_sk(sk)->ep->prsctp_enable = !!params->assoc_value;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_शेष_prinfo(काष्ठा sock *sk,
					  काष्ठा sctp_शेष_prinfo *info,
					  अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EINVAL;

	अगर (optlen != माप(*info))
		जाओ out;

	अगर (info->pr_policy & ~SCTP_PR_SCTP_MASK)
		जाओ out;

	अगर (info->pr_policy == SCTP_PR_SCTP_NONE)
		info->pr_value = 0;

	asoc = sctp_id2assoc(sk, info->pr_assoc_id);
	अगर (!asoc && info->pr_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	retval = 0;

	अगर (asoc) अणु
		SCTP_PR_SET_POLICY(asoc->शेष_flags, info->pr_policy);
		asoc->शेष_समयtolive = info->pr_value;
		जाओ out;
	पूर्ण

	अगर (sctp_style(sk, TCP))
		info->pr_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (info->pr_assoc_id == SCTP_FUTURE_ASSOC ||
	    info->pr_assoc_id == SCTP_ALL_ASSOC) अणु
		SCTP_PR_SET_POLICY(sp->शेष_flags, info->pr_policy);
		sp->शेष_समयtolive = info->pr_value;
	पूर्ण

	अगर (info->pr_assoc_id == SCTP_CURRENT_ASSOC ||
	    info->pr_assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs) अणु
			SCTP_PR_SET_POLICY(asoc->शेष_flags,
					   info->pr_policy);
			asoc->शेष_समयtolive = info->pr_value;
		पूर्ण
	पूर्ण

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_reconfig_supported(काष्ठा sock *sk,
					      काष्ठा sctp_assoc_value *params,
					      अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EINVAL;

	अगर (optlen != माप(*params))
		जाओ out;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	sctp_sk(sk)->ep->reconf_enable = !!params->assoc_value;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_enable_strreset(काष्ठा sock *sk,
					   काष्ठा sctp_assoc_value *params,
					   अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EINVAL;

	अगर (optlen != माप(*params))
		जाओ out;

	अगर (params->assoc_value & (~SCTP_ENABLE_STRRESET_MASK))
		जाओ out;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	retval = 0;

	अगर (asoc) अणु
		asoc->strreset_enable = params->assoc_value;
		जाओ out;
	पूर्ण

	अगर (sctp_style(sk, TCP))
		params->assoc_id = SCTP_FUTURE_ASSOC;

	अगर (params->assoc_id == SCTP_FUTURE_ASSOC ||
	    params->assoc_id == SCTP_ALL_ASSOC)
		ep->strreset_enable = params->assoc_value;

	अगर (params->assoc_id == SCTP_CURRENT_ASSOC ||
	    params->assoc_id == SCTP_ALL_ASSOC)
		list_क्रम_each_entry(asoc, &ep->asocs, asocs)
			asoc->strreset_enable = params->assoc_value;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_reset_streams(काष्ठा sock *sk,
					 काष्ठा sctp_reset_streams *params,
					 अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;

	अगर (optlen < माप(*params))
		वापस -EINVAL;
	/* srs_number_streams is u16, so optlen can't be bigger than this. */
	optlen = min_t(अचिन्हित पूर्णांक, optlen, अच_लघु_उच्च +
					     माप(__u16) * माप(*params));

	अगर (params->srs_number_streams * माप(__u16) >
	    optlen - माप(*params))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, params->srs_assoc_id);
	अगर (!asoc)
		वापस -EINVAL;

	वापस sctp_send_reset_streams(asoc, params);
पूर्ण

अटल पूर्णांक sctp_setsockopt_reset_assoc(काष्ठा sock *sk, sctp_assoc_t *associd,
				       अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;

	अगर (optlen != माप(*associd))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, *associd);
	अगर (!asoc)
		वापस -EINVAL;

	वापस sctp_send_reset_assoc(asoc);
पूर्ण

अटल पूर्णांक sctp_setsockopt_add_streams(काष्ठा sock *sk,
				       काष्ठा sctp_add_streams *params,
				       अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;

	अगर (optlen != माप(*params))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, params->sas_assoc_id);
	अगर (!asoc)
		वापस -EINVAL;

	वापस sctp_send_add_streams(asoc, params);
पूर्ण

अटल पूर्णांक sctp_setsockopt_scheduler(काष्ठा sock *sk,
				     काष्ठा sctp_assoc_value *params,
				     अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = 0;

	अगर (optlen < माप(*params))
		वापस -EINVAL;

	अगर (params->assoc_value > SCTP_SS_MAX)
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc)
		वापस sctp_sched_set_sched(asoc, params->assoc_value);

	अगर (sctp_style(sk, TCP))
		params->assoc_id = SCTP_FUTURE_ASSOC;

	अगर (params->assoc_id == SCTP_FUTURE_ASSOC ||
	    params->assoc_id == SCTP_ALL_ASSOC)
		sp->शेष_ss = params->assoc_value;

	अगर (params->assoc_id == SCTP_CURRENT_ASSOC ||
	    params->assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs) अणु
			पूर्णांक ret = sctp_sched_set_sched(asoc,
						       params->assoc_value);

			अगर (ret && !retval)
				retval = ret;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_scheduler_value(काष्ठा sock *sk,
					   काष्ठा sctp_stream_value *params,
					   अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EINVAL;

	अगर (optlen < माप(*params))
		जाओ out;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id != SCTP_CURRENT_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	अगर (asoc) अणु
		retval = sctp_sched_set_value(asoc, params->stream_id,
					      params->stream_value, GFP_KERNEL);
		जाओ out;
	पूर्ण

	retval = 0;

	list_क्रम_each_entry(asoc, &sctp_sk(sk)->ep->asocs, asocs) अणु
		पूर्णांक ret = sctp_sched_set_value(asoc, params->stream_id,
					       params->stream_value,
					       GFP_KERNEL);
		अगर (ret && !retval) /* try to वापस the 1st error. */
			retval = ret;
	पूर्ण

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_पूर्णांकerleaving_supported(काष्ठा sock *sk,
						  काष्ठा sctp_assoc_value *p,
						  अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;

	अगर (optlen < माप(*p))
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, p->assoc_id);
	अगर (!asoc && p->assoc_id != SCTP_FUTURE_ASSOC && sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (!sock_net(sk)->sctp.पूर्णांकl_enable || !sp->frag_पूर्णांकerleave) अणु
		वापस -EPERM;
	पूर्ण

	sp->ep->पूर्णांकl_enable = !!p->assoc_value;
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_reuse_port(काष्ठा sock *sk, पूर्णांक *val,
				      अचिन्हित पूर्णांक optlen)
अणु
	अगर (!sctp_style(sk, TCP))
		वापस -EOPNOTSUPP;

	अगर (sctp_sk(sk)->ep->base.bind_addr.port)
		वापस -EFAULT;

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	sctp_sk(sk)->reuse = !!*val;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_assoc_ulpevent_type_set(काष्ठा sctp_event *param,
					काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_ulpevent *event;

	sctp_ulpevent_type_set(&asoc->subscribe, param->se_type, param->se_on);

	अगर (param->se_type == SCTP_SENDER_DRY_EVENT && param->se_on) अणु
		अगर (sctp_outq_is_empty(&asoc->outqueue)) अणु
			event = sctp_ulpevent_make_sender_dry_event(asoc,
					GFP_USER | __GFP_NOWARN);
			अगर (!event)
				वापस -ENOMEM;

			asoc->stream.si->enqueue_event(&asoc->ulpq, event);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_setsockopt_event(काष्ठा sock *sk, काष्ठा sctp_event *param,
				 अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = 0;

	अगर (optlen < माप(*param))
		वापस -EINVAL;

	अगर (param->se_type < SCTP_SN_TYPE_BASE ||
	    param->se_type > SCTP_SN_TYPE_MAX)
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, param->se_assoc_id);
	अगर (!asoc && param->se_assoc_id > SCTP_ALL_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc)
		वापस sctp_assoc_ulpevent_type_set(param, asoc);

	अगर (sctp_style(sk, TCP))
		param->se_assoc_id = SCTP_FUTURE_ASSOC;

	अगर (param->se_assoc_id == SCTP_FUTURE_ASSOC ||
	    param->se_assoc_id == SCTP_ALL_ASSOC)
		sctp_ulpevent_type_set(&sp->subscribe,
				       param->se_type, param->se_on);

	अगर (param->se_assoc_id == SCTP_CURRENT_ASSOC ||
	    param->se_assoc_id == SCTP_ALL_ASSOC) अणु
		list_क्रम_each_entry(asoc, &sp->ep->asocs, asocs) अणु
			पूर्णांक ret = sctp_assoc_ulpevent_type_set(param, asoc);

			अगर (ret && !retval)
				retval = ret;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_asconf_supported(काष्ठा sock *sk,
					    काष्ठा sctp_assoc_value *params,
					    अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_endpoपूर्णांक *ep;
	पूर्णांक retval = -EINVAL;

	अगर (optlen != माप(*params))
		जाओ out;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	ep = sctp_sk(sk)->ep;
	ep->asconf_enable = !!params->assoc_value;

	अगर (ep->asconf_enable && ep->auth_enable) अणु
		sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF);
		sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF_ACK);
	पूर्ण

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_auth_supported(काष्ठा sock *sk,
					  काष्ठा sctp_assoc_value *params,
					  अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_endpoपूर्णांक *ep;
	पूर्णांक retval = -EINVAL;

	अगर (optlen != माप(*params))
		जाओ out;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	ep = sctp_sk(sk)->ep;
	अगर (params->assoc_value) अणु
		retval = sctp_auth_init(ep, GFP_KERNEL);
		अगर (retval)
			जाओ out;
		अगर (ep->asconf_enable) अणु
			sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF);
			sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF_ACK);
		पूर्ण
	पूर्ण

	ep->auth_enable = !!params->assoc_value;
	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_ecn_supported(काष्ठा sock *sk,
					 काष्ठा sctp_assoc_value *params,
					 अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EINVAL;

	अगर (optlen != माप(*params))
		जाओ out;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	sctp_sk(sk)->ep->ecn_enable = !!params->assoc_value;
	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_pf_expose(काष्ठा sock *sk,
				     काष्ठा sctp_assoc_value *params,
				     अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EINVAL;

	अगर (optlen != माप(*params))
		जाओ out;

	अगर (params->assoc_value > SCTP_PF_EXPOSE_MAX)
		जाओ out;

	asoc = sctp_id2assoc(sk, params->assoc_id);
	अगर (!asoc && params->assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		जाओ out;

	अगर (asoc)
		asoc->pf_expose = params->assoc_value;
	अन्यथा
		sctp_sk(sk)->pf_expose = params->assoc_value;
	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_setsockopt_encap_port(काष्ठा sock *sk,
				      काष्ठा sctp_udpencaps *encap,
				      अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_transport *t;
	__be16 encap_port;

	अगर (optlen != माप(*encap))
		वापस -EINVAL;

	/* If an address other than INADDR_ANY is specअगरied, and
	 * no transport is found, then the request is invalid.
	 */
	encap_port = (__क्रमce __be16)encap->sue_port;
	अगर (!sctp_is_any(sk, (जोड़ sctp_addr *)&encap->sue_address)) अणु
		t = sctp_addr_id2transport(sk, &encap->sue_address,
					   encap->sue_assoc_id);
		अगर (!t)
			वापस -EINVAL;

		t->encap_port = encap_port;
		वापस 0;
	पूर्ण

	/* Get association, अगर assoc_id != SCTP_FUTURE_ASSOC and the
	 * socket is a one to many style socket, and an association
	 * was not found, then the id was invalid.
	 */
	asoc = sctp_id2assoc(sk, encap->sue_assoc_id);
	अगर (!asoc && encap->sue_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	/* If changes are क्रम association, also apply encap_port to
	 * each transport.
	 */
	अगर (asoc) अणु
		list_क्रम_each_entry(t, &asoc->peer.transport_addr_list,
				    transports)
			t->encap_port = encap_port;

		asoc->encap_port = encap_port;
		वापस 0;
	पूर्ण

	sctp_sk(sk)->encap_port = encap_port;
	वापस 0;
पूर्ण

/* API 6.2 setsockopt(), माला_लोockopt()
 *
 * Applications use setsockopt() and माला_लोockopt() to set or retrieve
 * socket options.  Socket options are used to change the शेष
 * behavior of sockets calls.  They are described in Section 7.
 *
 * The syntax is:
 *
 *   ret = माला_लोockopt(पूर्णांक sd, पूर्णांक level, पूर्णांक optname, व्योम __user *optval,
 *                    पूर्णांक __user *optlen);
 *   ret = setsockopt(पूर्णांक sd, पूर्णांक level, पूर्णांक optname, स्थिर व्योम __user *optval,
 *                    पूर्णांक optlen);
 *
 *   sd      - the socket descript.
 *   level   - set to IPPROTO_SCTP क्रम all SCTP options.
 *   optname - the option name.
 *   optval  - the buffer to store the value of the option.
 *   optlen  - the size of the buffer.
 */
अटल पूर्णांक sctp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			   sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	व्योम *kopt = शून्य;
	पूर्णांक retval = 0;

	pr_debug("%s: sk:%p, optname:%d\n", __func__, sk, optname);

	/* I can hardly begin to describe how wrong this is.  This is
	 * so broken as to be worse than useless.  The API draft
	 * REALLY is NOT helpful here...  I am not convinced that the
	 * semantics of setsockopt() with a level OTHER THAN SOL_SCTP
	 * are at all well-founded.
	 */
	अगर (level != SOL_SCTP) अणु
		काष्ठा sctp_af *af = sctp_sk(sk)->pf->af;

		वापस af->setsockopt(sk, level, optname, optval, optlen);
	पूर्ण

	अगर (optlen > 0) अणु
		kopt = memdup_sockptr(optval, optlen);
		अगर (IS_ERR(kopt))
			वापस PTR_ERR(kopt);
	पूर्ण

	lock_sock(sk);

	चयन (optname) अणु
	हाल SCTP_SOCKOPT_BINDX_ADD:
		/* 'optlen' is the size of the addresses buffer. */
		retval = sctp_setsockopt_bindx(sk, kopt, optlen,
					       SCTP_BINDX_ADD_ADDR);
		अवरोध;

	हाल SCTP_SOCKOPT_BINDX_REM:
		/* 'optlen' is the size of the addresses buffer. */
		retval = sctp_setsockopt_bindx(sk, kopt, optlen,
					       SCTP_BINDX_REM_ADDR);
		अवरोध;

	हाल SCTP_SOCKOPT_CONNECTX_OLD:
		/* 'optlen' is the size of the addresses buffer. */
		retval = sctp_setsockopt_connectx_old(sk, kopt, optlen);
		अवरोध;

	हाल SCTP_SOCKOPT_CONNECTX:
		/* 'optlen' is the size of the addresses buffer. */
		retval = sctp_setsockopt_connectx(sk, kopt, optlen);
		अवरोध;

	हाल SCTP_DISABLE_FRAGMENTS:
		retval = sctp_setsockopt_disable_fragments(sk, kopt, optlen);
		अवरोध;

	हाल SCTP_EVENTS:
		retval = sctp_setsockopt_events(sk, kopt, optlen);
		अवरोध;

	हाल SCTP_AUTOCLOSE:
		retval = sctp_setsockopt_स्वतःबंद(sk, kopt, optlen);
		अवरोध;

	हाल SCTP_PEER_ADDR_PARAMS:
		retval = sctp_setsockopt_peer_addr_params(sk, kopt, optlen);
		अवरोध;

	हाल SCTP_DELAYED_SACK:
		retval = sctp_setsockopt_delayed_ack(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_PARTIAL_DELIVERY_POINT:
		retval = sctp_setsockopt_partial_delivery_poपूर्णांक(sk, kopt, optlen);
		अवरोध;

	हाल SCTP_INITMSG:
		retval = sctp_setsockopt_iniपंचांगsg(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_DEFAULT_SEND_PARAM:
		retval = sctp_setsockopt_शेष_send_param(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_DEFAULT_SNDINFO:
		retval = sctp_setsockopt_शेष_sndinfo(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_PRIMARY_ADDR:
		retval = sctp_setsockopt_primary_addr(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_SET_PEER_PRIMARY_ADDR:
		retval = sctp_setsockopt_peer_primary_addr(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_NODELAY:
		retval = sctp_setsockopt_nodelay(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_RTOINFO:
		retval = sctp_setsockopt_rtoinfo(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_ASSOCINFO:
		retval = sctp_setsockopt_associnfo(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_I_WANT_MAPPED_V4_ADDR:
		retval = sctp_setsockopt_mappedv4(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_MAXSEG:
		retval = sctp_setsockopt_maxseg(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_ADAPTATION_LAYER:
		retval = sctp_setsockopt_adaptation_layer(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_CONTEXT:
		retval = sctp_setsockopt_context(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_FRAGMENT_INTERLEAVE:
		retval = sctp_setsockopt_fragment_पूर्णांकerleave(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_MAX_BURST:
		retval = sctp_setsockopt_maxburst(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_AUTH_CHUNK:
		retval = sctp_setsockopt_auth_chunk(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_HMAC_IDENT:
		retval = sctp_setsockopt_hmac_ident(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_AUTH_KEY:
		retval = sctp_setsockopt_auth_key(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_AUTH_ACTIVE_KEY:
		retval = sctp_setsockopt_active_key(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_AUTH_DELETE_KEY:
		retval = sctp_setsockopt_del_key(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_AUTH_DEACTIVATE_KEY:
		retval = sctp_setsockopt_deactivate_key(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_AUTO_ASCONF:
		retval = sctp_setsockopt_स्वतः_asconf(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_PEER_ADDR_THLDS:
		retval = sctp_setsockopt_paddr_thresholds(sk, kopt, optlen,
							  false);
		अवरोध;
	हाल SCTP_PEER_ADDR_THLDS_V2:
		retval = sctp_setsockopt_paddr_thresholds(sk, kopt, optlen,
							  true);
		अवरोध;
	हाल SCTP_RECVRCVINFO:
		retval = sctp_setsockopt_recvrcvinfo(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_RECVNXTINFO:
		retval = sctp_setsockopt_recvnxtinfo(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_PR_SUPPORTED:
		retval = sctp_setsockopt_pr_supported(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_DEFAULT_PRINFO:
		retval = sctp_setsockopt_शेष_prinfo(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_RECONFIG_SUPPORTED:
		retval = sctp_setsockopt_reconfig_supported(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_ENABLE_STREAM_RESET:
		retval = sctp_setsockopt_enable_strreset(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_RESET_STREAMS:
		retval = sctp_setsockopt_reset_streams(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_RESET_ASSOC:
		retval = sctp_setsockopt_reset_assoc(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_ADD_STREAMS:
		retval = sctp_setsockopt_add_streams(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_STREAM_SCHEDULER:
		retval = sctp_setsockopt_scheduler(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_STREAM_SCHEDULER_VALUE:
		retval = sctp_setsockopt_scheduler_value(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_INTERLEAVING_SUPPORTED:
		retval = sctp_setsockopt_पूर्णांकerleaving_supported(sk, kopt,
								optlen);
		अवरोध;
	हाल SCTP_REUSE_PORT:
		retval = sctp_setsockopt_reuse_port(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_EVENT:
		retval = sctp_setsockopt_event(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_ASCONF_SUPPORTED:
		retval = sctp_setsockopt_asconf_supported(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_AUTH_SUPPORTED:
		retval = sctp_setsockopt_auth_supported(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_ECN_SUPPORTED:
		retval = sctp_setsockopt_ecn_supported(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_EXPOSE_POTENTIALLY_FAILED_STATE:
		retval = sctp_setsockopt_pf_expose(sk, kopt, optlen);
		अवरोध;
	हाल SCTP_REMOTE_UDP_ENCAPS_PORT:
		retval = sctp_setsockopt_encap_port(sk, kopt, optlen);
		अवरोध;
	शेष:
		retval = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	kमुक्त(kopt);
	वापस retval;
पूर्ण

/* API 3.1.6 connect() - UDP Style Syntax
 *
 * An application may use the connect() call in the UDP model to initiate an
 * association without sending data.
 *
 * The syntax is:
 *
 * ret = connect(पूर्णांक sd, स्थिर काष्ठा sockaddr *nam, socklen_t len);
 *
 * sd: the socket descriptor to have a new association added to.
 *
 * nam: the address काष्ठाure (either काष्ठा sockaddr_in or काष्ठा
 *    sockaddr_in6 defined in RFC2553 [7]).
 *
 * len: the size of the address.
 */
अटल पूर्णांक sctp_connect(काष्ठा sock *sk, काष्ठा sockaddr *addr,
			पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sctp_af *af;
	पूर्णांक err = -EINVAL;

	lock_sock(sk);
	pr_debug("%s: sk:%p, sockaddr:%p, addr_len:%d\n", __func__, sk,
		 addr, addr_len);

	/* Validate addr_len beक्रमe calling common connect/connectx routine. */
	af = sctp_get_af_specअगरic(addr->sa_family);
	अगर (af && addr_len >= af->sockaddr_len)
		err = __sctp_connect(sk, addr, af->sockaddr_len, flags, शून्य);

	release_sock(sk);
	वापस err;
पूर्ण

पूर्णांक sctp_inet_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		      पूर्णांक addr_len, पूर्णांक flags)
अणु
	अगर (addr_len < माप(uaddr->sa_family))
		वापस -EINVAL;

	अगर (uaddr->sa_family == AF_UNSPEC)
		वापस -EOPNOTSUPP;

	वापस sctp_connect(sock->sk, uaddr, addr_len, flags);
पूर्ण

/* FIXME: Write comments. */
अटल पूर्णांक sctp_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP; /* STUB */
पूर्ण

/* 4.1.4 accept() - TCP Style Syntax
 *
 * Applications use accept() call to हटाओ an established SCTP
 * association from the accept queue of the endpoपूर्णांक.  A new socket
 * descriptor will be वापसed from accept() to represent the newly
 * क्रमmed association.
 */
अटल काष्ठा sock *sctp_accept(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक *err, bool kern)
अणु
	काष्ठा sctp_sock *sp;
	काष्ठा sctp_endpoपूर्णांक *ep;
	काष्ठा sock *newsk = शून्य;
	काष्ठा sctp_association *asoc;
	दीर्घ समयo;
	पूर्णांक error = 0;

	lock_sock(sk);

	sp = sctp_sk(sk);
	ep = sp->ep;

	अगर (!sctp_style(sk, TCP)) अणु
		error = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (!sctp_sstate(sk, LISTENING)) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण

	समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);

	error = sctp_रुको_क्रम_accept(sk, समयo);
	अगर (error)
		जाओ out;

	/* We treat the list of associations on the endpoपूर्णांक as the accept
	 * queue and pick the first association on the list.
	 */
	asoc = list_entry(ep->asocs.next, काष्ठा sctp_association, asocs);

	newsk = sp->pf->create_accept_sk(sk, asoc, kern);
	अगर (!newsk) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Populate the fields of the newsk from the oldsk and migrate the
	 * asoc to the newsk.
	 */
	error = sctp_sock_migrate(sk, newsk, asoc, SCTP_SOCKET_TCP);
	अगर (error) अणु
		sk_common_release(newsk);
		newsk = शून्य;
	पूर्ण

out:
	release_sock(sk);
	*err = error;
	वापस newsk;
पूर्ण

/* The SCTP ioctl handler. */
अटल पूर्णांक sctp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc = -ENOTCONN;

	lock_sock(sk);

	/*
	 * SEQPACKET-style sockets in LISTENING state are valid, क्रम
	 * SCTP, so only discard TCP-style sockets in LISTENING state.
	 */
	अगर (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING))
		जाओ out;

	चयन (cmd) अणु
	हाल SIOCINQ: अणु
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक amount = 0;

		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb != शून्य) अणु
			/*
			 * We will only वापस the amount of this packet since
			 * that is all that will be पढ़ो.
			 */
			amount = skb->len;
		पूर्ण
		rc = put_user(amount, (पूर्णांक __user *)arg);
		अवरोध;
	पूर्ण
	शेष:
		rc = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
out:
	release_sock(sk);
	वापस rc;
पूर्ण

/* This is the function which माला_लो called during socket creation to
 * initialized the SCTP-specअगरic portion of the sock.
 * The sock काष्ठाure should alपढ़ोy be zero-filled memory.
 */
अटल पूर्णांक sctp_init_sock(काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा sctp_sock *sp;

	pr_debug("%s: sk:%p\n", __func__, sk);

	sp = sctp_sk(sk);

	/* Initialize the SCTP per socket area.  */
	चयन (sk->sk_type) अणु
	हाल SOCK_SEQPACKET:
		sp->type = SCTP_SOCKET_UDP;
		अवरोध;
	हाल SOCK_STREAM:
		sp->type = SCTP_SOCKET_TCP;
		अवरोध;
	शेष:
		वापस -ESOCKTNOSUPPORT;
	पूर्ण

	sk->sk_gso_type = SKB_GSO_SCTP;

	/* Initialize शेष send parameters. These parameters can be
	 * modअगरied with the SCTP_DEFAULT_SEND_PARAM socket option.
	 */
	sp->शेष_stream = 0;
	sp->शेष_ppid = 0;
	sp->शेष_flags = 0;
	sp->शेष_context = 0;
	sp->शेष_समयtolive = 0;

	sp->शेष_rcv_context = 0;
	sp->max_burst = net->sctp.max_burst;

	sp->sctp_hmac_alg = net->sctp.sctp_hmac_alg;

	/* Initialize शेष setup parameters. These parameters
	 * can be modअगरied with the SCTP_INITMSG socket option or
	 * overridden by the SCTP_INIT CMSG.
	 */
	sp->iniपंचांगsg.sinit_num_ostreams   = sctp_max_outstreams;
	sp->iniपंचांगsg.sinit_max_instreams  = sctp_max_instreams;
	sp->iniपंचांगsg.sinit_max_attempts   = net->sctp.max_retrans_init;
	sp->iniपंचांगsg.sinit_max_init_समयo = net->sctp.rto_max;

	/* Initialize शेष RTO related parameters.  These parameters can
	 * be modअगरied क्रम with the SCTP_RTOINFO socket option.
	 */
	sp->rtoinfo.srto_initial = net->sctp.rto_initial;
	sp->rtoinfo.srto_max     = net->sctp.rto_max;
	sp->rtoinfo.srto_min     = net->sctp.rto_min;

	/* Initialize शेष association related parameters. These parameters
	 * can be modअगरied with the SCTP_ASSOCINFO socket option.
	 */
	sp->assocparams.sasoc_asocmaxrxt = net->sctp.max_retrans_association;
	sp->assocparams.sasoc_number_peer_destinations = 0;
	sp->assocparams.sasoc_peer_rwnd = 0;
	sp->assocparams.sasoc_local_rwnd = 0;
	sp->assocparams.sasoc_cookie_lअगरe = net->sctp.valid_cookie_lअगरe;

	/* Initialize शेष event subscriptions. By शेष, all the
	 * options are off.
	 */
	sp->subscribe = 0;

	/* Default Peer Address Parameters.  These शेषs can
	 * be modअगरied via SCTP_PEER_ADDR_PARAMS
	 */
	sp->hbपूर्णांकerval  = net->sctp.hb_पूर्णांकerval;
	sp->udp_port    = htons(net->sctp.udp_port);
	sp->encap_port  = htons(net->sctp.encap_port);
	sp->pathmaxrxt  = net->sctp.max_retrans_path;
	sp->pf_retrans  = net->sctp.pf_retrans;
	sp->ps_retrans  = net->sctp.ps_retrans;
	sp->pf_expose   = net->sctp.pf_expose;
	sp->pathmtu     = 0; /* allow शेष discovery */
	sp->sackdelay   = net->sctp.sack_समयout;
	sp->sackfreq	= 2;
	sp->param_flags = SPP_HB_ENABLE |
			  SPP_PMTUD_ENABLE |
			  SPP_SACKDELAY_ENABLE;
	sp->शेष_ss = SCTP_SS_DEFAULT;

	/* If enabled no SCTP message fragmentation will be perक्रमmed.
	 * Configure through SCTP_DISABLE_FRAGMENTS socket option.
	 */
	sp->disable_fragments = 0;

	/* Enable Nagle algorithm by शेष.  */
	sp->nodelay           = 0;

	sp->recvrcvinfo = 0;
	sp->recvnxtinfo = 0;

	/* Enable by शेष. */
	sp->v4mapped          = 1;

	/* Auto-बंद idle associations after the configured
	 * number of seconds.  A value of 0 disables this
	 * feature.  Configure through the SCTP_AUTOCLOSE socket option,
	 * क्रम UDP-style sockets only.
	 */
	sp->स्वतःबंद         = 0;

	/* User specअगरied fragmentation limit. */
	sp->user_frag         = 0;

	sp->adaptation_ind = 0;

	sp->pf = sctp_get_pf_specअगरic(sk->sk_family);

	/* Control variables क्रम partial data delivery. */
	atomic_set(&sp->pd_mode, 0);
	skb_queue_head_init(&sp->pd_lobby);
	sp->frag_पूर्णांकerleave = 0;

	/* Create a per socket endpoपूर्णांक काष्ठाure.  Even अगर we
	 * change the data काष्ठाure relationships, this may still
	 * be useful क्रम storing pre-connect address inक्रमmation.
	 */
	sp->ep = sctp_endpoपूर्णांक_new(sk, GFP_KERNEL);
	अगर (!sp->ep)
		वापस -ENOMEM;

	sp->hmac = शून्य;

	sk->sk_deकाष्ठा = sctp_deकाष्ठा_sock;

	SCTP_DBG_OBJCNT_INC(sock);

	local_bh_disable();
	sk_sockets_allocated_inc(sk);
	sock_prot_inuse_add(net, sk->sk_prot, 1);

	local_bh_enable();

	वापस 0;
पूर्ण

/* Cleanup any SCTP per socket resources. Must be called with
 * sock_net(sk)->sctp.addr_wq_lock held अगर sp->करो_स्वतः_asconf is true
 */
अटल व्योम sctp_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा sctp_sock *sp;

	pr_debug("%s: sk:%p\n", __func__, sk);

	/* Release our hold on the endpoपूर्णांक. */
	sp = sctp_sk(sk);
	/* This could happen during socket init, thus we bail out
	 * early, since the rest of the below is not setup either.
	 */
	अगर (sp->ep == शून्य)
		वापस;

	अगर (sp->करो_स्वतः_asconf) अणु
		sp->करो_स्वतः_asconf = 0;
		list_del(&sp->स्वतः_asconf_list);
	पूर्ण
	sctp_endpoपूर्णांक_मुक्त(sp->ep);
	local_bh_disable();
	sk_sockets_allocated_dec(sk);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	local_bh_enable();
पूर्ण

/* Triggered when there are no references on the socket anymore */
अटल व्योम sctp_deकाष्ठा_sock(काष्ठा sock *sk)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);

	/* Free up the HMAC transक्रमm. */
	crypto_मुक्त_shash(sp->hmac);

	inet_sock_deकाष्ठा(sk);
पूर्ण

/* API 4.1.7 shutकरोwn() - TCP Style Syntax
 *     पूर्णांक shutकरोwn(पूर्णांक socket, पूर्णांक how);
 *
 *     sd      - the socket descriptor of the association to be बंदd.
 *     how     - Specअगरies the type of shutकरोwn.  The  values  are
 *               as follows:
 *               SHUT_RD
 *                     Disables further receive operations. No SCTP
 *                     protocol action is taken.
 *               SHUT_WR
 *                     Disables further send operations, and initiates
 *                     the SCTP shutकरोwn sequence.
 *               SHUT_RDWR
 *                     Disables further send  and  receive  operations
 *                     and initiates the SCTP shutकरोwn sequence.
 */
अटल व्योम sctp_shutकरोwn(काष्ठा sock *sk, पूर्णांक how)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा sctp_endpoपूर्णांक *ep;

	अगर (!sctp_style(sk, TCP))
		वापस;

	ep = sctp_sk(sk)->ep;
	अगर (how & SEND_SHUTDOWN && !list_empty(&ep->asocs)) अणु
		काष्ठा sctp_association *asoc;

		inet_sk_set_state(sk, SCTP_SS_CLOSING);
		asoc = list_entry(ep->asocs.next,
				  काष्ठा sctp_association, asocs);
		sctp_primitive_SHUTDOWN(net, asoc, शून्य);
	पूर्ण
पूर्ण

पूर्णांक sctp_get_sctp_info(काष्ठा sock *sk, काष्ठा sctp_association *asoc,
		       काष्ठा sctp_info *info)
अणु
	काष्ठा sctp_transport *prim;
	काष्ठा list_head *pos;
	पूर्णांक mask;

	स_रखो(info, 0, माप(*info));
	अगर (!asoc) अणु
		काष्ठा sctp_sock *sp = sctp_sk(sk);

		info->sctpi_s_स्वतःबंद = sp->स्वतःबंद;
		info->sctpi_s_adaptation_ind = sp->adaptation_ind;
		info->sctpi_s_pd_poपूर्णांक = sp->pd_poपूर्णांक;
		info->sctpi_s_nodelay = sp->nodelay;
		info->sctpi_s_disable_fragments = sp->disable_fragments;
		info->sctpi_s_v4mapped = sp->v4mapped;
		info->sctpi_s_frag_पूर्णांकerleave = sp->frag_पूर्णांकerleave;
		info->sctpi_s_type = sp->type;

		वापस 0;
	पूर्ण

	info->sctpi_tag = asoc->c.my_vtag;
	info->sctpi_state = asoc->state;
	info->sctpi_rwnd = asoc->a_rwnd;
	info->sctpi_unackdata = asoc->unack_data;
	info->sctpi_penddata = sctp_tsnmap_pending(&asoc->peer.tsn_map);
	info->sctpi_instrms = asoc->stream.incnt;
	info->sctpi_outstrms = asoc->stream.outcnt;
	list_क्रम_each(pos, &asoc->base.inqueue.in_chunk_list)
		info->sctpi_inqueue++;
	list_क्रम_each(pos, &asoc->outqueue.out_chunk_list)
		info->sctpi_outqueue++;
	info->sctpi_overall_error = asoc->overall_error_count;
	info->sctpi_max_burst = asoc->max_burst;
	info->sctpi_maxseg = asoc->frag_poपूर्णांक;
	info->sctpi_peer_rwnd = asoc->peer.rwnd;
	info->sctpi_peer_tag = asoc->c.peer_vtag;

	mask = asoc->peer.ecn_capable << 1;
	mask = (mask | asoc->peer.ipv4_address) << 1;
	mask = (mask | asoc->peer.ipv6_address) << 1;
	mask = (mask | asoc->peer.hostname_address) << 1;
	mask = (mask | asoc->peer.asconf_capable) << 1;
	mask = (mask | asoc->peer.prsctp_capable) << 1;
	mask = (mask | asoc->peer.auth_capable);
	info->sctpi_peer_capable = mask;
	mask = asoc->peer.sack_needed << 1;
	mask = (mask | asoc->peer.sack_generation) << 1;
	mask = (mask | asoc->peer.zero_winकरोw_announced);
	info->sctpi_peer_sack = mask;

	info->sctpi_isacks = asoc->stats.isacks;
	info->sctpi_osacks = asoc->stats.osacks;
	info->sctpi_opackets = asoc->stats.opackets;
	info->sctpi_ipackets = asoc->stats.ipackets;
	info->sctpi_rtxchunks = asoc->stats.rtxchunks;
	info->sctpi_outofseqtsns = asoc->stats.outofseqtsns;
	info->sctpi_idupchunks = asoc->stats.idupchunks;
	info->sctpi_gapcnt = asoc->stats.gapcnt;
	info->sctpi_ouodchunks = asoc->stats.ouodchunks;
	info->sctpi_iuodchunks = asoc->stats.iuodchunks;
	info->sctpi_oodchunks = asoc->stats.oodchunks;
	info->sctpi_iodchunks = asoc->stats.iodchunks;
	info->sctpi_octrlchunks = asoc->stats.octrlchunks;
	info->sctpi_ictrlchunks = asoc->stats.ictrlchunks;

	prim = asoc->peer.primary_path;
	स_नकल(&info->sctpi_p_address, &prim->ipaddr, माप(prim->ipaddr));
	info->sctpi_p_state = prim->state;
	info->sctpi_p_cwnd = prim->cwnd;
	info->sctpi_p_srtt = prim->srtt;
	info->sctpi_p_rto = jअगरfies_to_msecs(prim->rto);
	info->sctpi_p_hbपूर्णांकerval = prim->hbपूर्णांकerval;
	info->sctpi_p_pathmaxrxt = prim->pathmaxrxt;
	info->sctpi_p_sackdelay = jअगरfies_to_msecs(prim->sackdelay);
	info->sctpi_p_ssthresh = prim->ssthresh;
	info->sctpi_p_partial_bytes_acked = prim->partial_bytes_acked;
	info->sctpi_p_flight_size = prim->flight_size;
	info->sctpi_p_error = prim->error_count;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sctp_get_sctp_info);

/* use callback to aव्योम exporting the core काष्ठाure */
व्योम sctp_transport_walk_start(काष्ठा rhashtable_iter *iter) __acquires(RCU)
अणु
	rhltable_walk_enter(&sctp_transport_hashtable, iter);

	rhashtable_walk_start(iter);
पूर्ण

व्योम sctp_transport_walk_stop(काष्ठा rhashtable_iter *iter) __releases(RCU)
अणु
	rhashtable_walk_stop(iter);
	rhashtable_walk_निकास(iter);
पूर्ण

काष्ठा sctp_transport *sctp_transport_get_next(काष्ठा net *net,
					       काष्ठा rhashtable_iter *iter)
अणु
	काष्ठा sctp_transport *t;

	t = rhashtable_walk_next(iter);
	क्रम (; t; t = rhashtable_walk_next(iter)) अणु
		अगर (IS_ERR(t)) अणु
			अगर (PTR_ERR(t) == -EAGAIN)
				जारी;
			अवरोध;
		पूर्ण

		अगर (!sctp_transport_hold(t))
			जारी;

		अगर (net_eq(t->asoc->base.net, net) &&
		    t->asoc->peer.primary_path == t)
			अवरोध;

		sctp_transport_put(t);
	पूर्ण

	वापस t;
पूर्ण

काष्ठा sctp_transport *sctp_transport_get_idx(काष्ठा net *net,
					      काष्ठा rhashtable_iter *iter,
					      पूर्णांक pos)
अणु
	काष्ठा sctp_transport *t;

	अगर (!pos)
		वापस SEQ_START_TOKEN;

	जबतक ((t = sctp_transport_get_next(net, iter)) && !IS_ERR(t)) अणु
		अगर (!--pos)
			अवरोध;
		sctp_transport_put(t);
	पूर्ण

	वापस t;
पूर्ण

पूर्णांक sctp_क्रम_each_endpoपूर्णांक(पूर्णांक (*cb)(काष्ठा sctp_endpoपूर्णांक *, व्योम *),
			   व्योम *p) अणु
	पूर्णांक err = 0;
	पूर्णांक hash = 0;
	काष्ठा sctp_ep_common *epb;
	काष्ठा sctp_hashbucket *head;

	क्रम (head = sctp_ep_hashtable; hash < sctp_ep_hashsize;
	     hash++, head++) अणु
		पढ़ो_lock_bh(&head->lock);
		sctp_क्रम_each_hentry(epb, &head->chain) अणु
			err = cb(sctp_ep(epb), p);
			अगर (err)
				अवरोध;
		पूर्ण
		पढ़ो_unlock_bh(&head->lock);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sctp_क्रम_each_endpoपूर्णांक);

पूर्णांक sctp_transport_lookup_process(पूर्णांक (*cb)(काष्ठा sctp_transport *, व्योम *),
				  काष्ठा net *net,
				  स्थिर जोड़ sctp_addr *laddr,
				  स्थिर जोड़ sctp_addr *paddr, व्योम *p)
अणु
	काष्ठा sctp_transport *transport;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	transport = sctp_addrs_lookup_transport(net, laddr, paddr);
	rcu_पढ़ो_unlock();
	अगर (!transport)
		वापस -ENOENT;

	err = cb(transport, p);
	sctp_transport_put(transport);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sctp_transport_lookup_process);

पूर्णांक sctp_क्रम_each_transport(पूर्णांक (*cb)(काष्ठा sctp_transport *, व्योम *),
			    पूर्णांक (*cb_करोne)(काष्ठा sctp_transport *, व्योम *),
			    काष्ठा net *net, पूर्णांक *pos, व्योम *p) अणु
	काष्ठा rhashtable_iter hti;
	काष्ठा sctp_transport *tsp;
	पूर्णांक ret;

again:
	ret = 0;
	sctp_transport_walk_start(&hti);

	tsp = sctp_transport_get_idx(net, &hti, *pos + 1);
	क्रम (; !IS_ERR_OR_शून्य(tsp); tsp = sctp_transport_get_next(net, &hti)) अणु
		ret = cb(tsp, p);
		अगर (ret)
			अवरोध;
		(*pos)++;
		sctp_transport_put(tsp);
	पूर्ण
	sctp_transport_walk_stop(&hti);

	अगर (ret) अणु
		अगर (cb_करोne && !cb_करोne(tsp, p)) अणु
			(*pos)++;
			sctp_transport_put(tsp);
			जाओ again;
		पूर्ण
		sctp_transport_put(tsp);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sctp_क्रम_each_transport);

/* 7.2.1 Association Status (SCTP_STATUS)

 * Applications can retrieve current status inक्रमmation about an
 * association, including association state, peer receiver winकरोw size,
 * number of unacked data chunks, and number of data chunks pending
 * receipt.  This inक्रमmation is पढ़ो-only.
 */
अटल पूर्णांक sctp_माला_लोockopt_sctp_status(काष्ठा sock *sk, पूर्णांक len,
				       अक्षर __user *optval,
				       पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_status status;
	काष्ठा sctp_association *asoc = शून्य;
	काष्ठा sctp_transport *transport;
	sctp_assoc_t associd;
	पूर्णांक retval = 0;

	अगर (len < माप(status)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(status);
	अगर (copy_from_user(&status, optval, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	associd = status.sstat_assoc_id;
	asoc = sctp_id2assoc(sk, associd);
	अगर (!asoc) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	transport = asoc->peer.primary_path;

	status.sstat_assoc_id = sctp_assoc2id(asoc);
	status.sstat_state = sctp_assoc_to_state(asoc);
	status.sstat_rwnd =  asoc->peer.rwnd;
	status.sstat_unackdata = asoc->unack_data;

	status.sstat_penddata = sctp_tsnmap_pending(&asoc->peer.tsn_map);
	status.sstat_instrms = asoc->stream.incnt;
	status.sstat_outstrms = asoc->stream.outcnt;
	status.sstat_fragmentation_poपूर्णांक = asoc->frag_poपूर्णांक;
	status.sstat_primary.spinfo_assoc_id = sctp_assoc2id(transport->asoc);
	स_नकल(&status.sstat_primary.spinfo_address, &transport->ipaddr,
			transport->af_specअगरic->sockaddr_len);
	/* Map ipv4 address पूर्णांकo v4-mapped-on-v6 address.  */
	sctp_get_pf_specअगरic(sk->sk_family)->addr_to_user(sctp_sk(sk),
		(जोड़ sctp_addr *)&status.sstat_primary.spinfo_address);
	status.sstat_primary.spinfo_state = transport->state;
	status.sstat_primary.spinfo_cwnd = transport->cwnd;
	status.sstat_primary.spinfo_srtt = transport->srtt;
	status.sstat_primary.spinfo_rto = jअगरfies_to_msecs(transport->rto);
	status.sstat_primary.spinfo_mtu = transport->pathmtu;

	अगर (status.sstat_primary.spinfo_state == SCTP_UNKNOWN)
		status.sstat_primary.spinfo_state = SCTP_ACTIVE;

	अगर (put_user(len, optlen)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	pr_debug("%s: len:%d, state:%d, rwnd:%d, assoc_id:%d\n",
		 __func__, len, status.sstat_state, status.sstat_rwnd,
		 status.sstat_assoc_id);

	अगर (copy_to_user(optval, &status, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

out:
	वापस retval;
पूर्ण


/* 7.2.2 Peer Address Inक्रमmation (SCTP_GET_PEER_ADDR_INFO)
 *
 * Applications can retrieve inक्रमmation about a specअगरic peer address
 * of an association, including its reachability state, congestion
 * winकरोw, and retransmission समयr values.  This inक्रमmation is
 * पढ़ो-only.
 */
अटल पूर्णांक sctp_माला_लोockopt_peer_addr_info(काष्ठा sock *sk, पूर्णांक len,
					  अक्षर __user *optval,
					  पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_paddrinfo pinfo;
	काष्ठा sctp_transport *transport;
	पूर्णांक retval = 0;

	अगर (len < माप(pinfo)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(pinfo);
	अगर (copy_from_user(&pinfo, optval, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	transport = sctp_addr_id2transport(sk, &pinfo.spinfo_address,
					   pinfo.spinfo_assoc_id);
	अगर (!transport) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (transport->state == SCTP_PF &&
	    transport->asoc->pf_expose == SCTP_PF_EXPOSE_DISABLE) अणु
		retval = -EACCES;
		जाओ out;
	पूर्ण

	pinfo.spinfo_assoc_id = sctp_assoc2id(transport->asoc);
	pinfo.spinfo_state = transport->state;
	pinfo.spinfo_cwnd = transport->cwnd;
	pinfo.spinfo_srtt = transport->srtt;
	pinfo.spinfo_rto = jअगरfies_to_msecs(transport->rto);
	pinfo.spinfo_mtu = transport->pathmtu;

	अगर (pinfo.spinfo_state == SCTP_UNKNOWN)
		pinfo.spinfo_state = SCTP_ACTIVE;

	अगर (put_user(len, optlen)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (copy_to_user(optval, &pinfo, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

out:
	वापस retval;
पूर्ण

/* 7.1.12 Enable/Disable message fragmentation (SCTP_DISABLE_FRAGMENTS)
 *
 * This option is a on/off flag.  If enabled no SCTP message
 * fragmentation will be perक्रमmed.  Instead अगर a message being sent
 * exceeds the current PMTU size, the message will NOT be sent and
 * instead a error will be indicated to the user.
 */
अटल पूर्णांक sctp_माला_लोockopt_disable_fragments(काष्ठा sock *sk, पूर्णांक len,
					अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक val;

	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;

	len = माप(पूर्णांक);
	val = (sctp_sk(sk)->disable_fragments == 1);
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* 7.1.15 Set notअगरication and ancillary events (SCTP_EVENTS)
 *
 * This socket option is used to specअगरy various notअगरications and
 * ancillary data the user wishes to receive.
 */
अटल पूर्णांक sctp_माला_लोockopt_events(काष्ठा sock *sk, पूर्णांक len, अक्षर __user *optval,
				  पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_event_subscribe subscribe;
	__u8 *sn_type = (__u8 *)&subscribe;
	पूर्णांक i;

	अगर (len == 0)
		वापस -EINVAL;
	अगर (len > माप(काष्ठा sctp_event_subscribe))
		len = माप(काष्ठा sctp_event_subscribe);
	अगर (put_user(len, optlen))
		वापस -EFAULT;

	क्रम (i = 0; i < len; i++)
		sn_type[i] = sctp_ulpevent_type_enabled(sctp_sk(sk)->subscribe,
							SCTP_SN_TYPE_BASE + i);

	अगर (copy_to_user(optval, &subscribe, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* 7.1.8 Automatic Close of associations (SCTP_AUTOCLOSE)
 *
 * This socket option is applicable to the UDP-style socket only.  When
 * set it will cause associations that are idle क्रम more than the
 * specअगरied number of seconds to स्वतःmatically बंद.  An association
 * being idle is defined an association that has NOT sent or received
 * user data.  The special value of '0' indicates that no स्वतःmatic
 * बंद of any associations should be perक्रमmed.  The option expects an
 * पूर्णांकeger defining the number of seconds of idle समय beक्रमe an
 * association is बंदd.
 */
अटल पूर्णांक sctp_माला_लोockopt_स्वतःबंद(काष्ठा sock *sk, पूर्णांक len, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	/* Applicable to UDP-style socket only */
	अगर (sctp_style(sk, TCP))
		वापस -EOPNOTSUPP;
	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;
	len = माप(पूर्णांक);
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (put_user(sctp_sk(sk)->स्वतःबंद, (पूर्णांक __user *)optval))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* Helper routine to branch off an association to a new socket.  */
पूर्णांक sctp_करो_peeloff(काष्ठा sock *sk, sctp_assoc_t id, काष्ठा socket **sockp)
अणु
	काष्ठा sctp_association *asoc = sctp_id2assoc(sk, id);
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा socket *sock;
	पूर्णांक err = 0;

	/* Do not peel off from one netns to another one. */
	अगर (!net_eq(current->nsproxy->net_ns, sock_net(sk)))
		वापस -EINVAL;

	अगर (!asoc)
		वापस -EINVAL;

	/* An association cannot be branched off from an alपढ़ोy peeled-off
	 * socket, nor is this supported क्रम tcp style sockets.
	 */
	अगर (!sctp_style(sk, UDP))
		वापस -EINVAL;

	/* Create a new socket.  */
	err = sock_create(sk->sk_family, SOCK_SEQPACKET, IPPROTO_SCTP, &sock);
	अगर (err < 0)
		वापस err;

	sctp_copy_sock(sock->sk, sk, asoc);

	/* Make peeled-off sockets more like 1-1 accepted sockets.
	 * Set the daddr and initialize id to something more अक्रमom and also
	 * copy over any ip options.
	 */
	sp->pf->to_sk_daddr(&asoc->peer.primary_addr, sk);
	sp->pf->copy_ip_options(sk, sock->sk);

	/* Populate the fields of the newsk from the oldsk and migrate the
	 * asoc to the newsk.
	 */
	err = sctp_sock_migrate(sk, sock->sk, asoc,
				SCTP_SOCKET_UDP_HIGH_BANDWIDTH);
	अगर (err) अणु
		sock_release(sock);
		sock = शून्य;
	पूर्ण

	*sockp = sock;

	वापस err;
पूर्ण
EXPORT_SYMBOL(sctp_करो_peeloff);

अटल पूर्णांक sctp_माला_लोockopt_peeloff_common(काष्ठा sock *sk, sctp_peeloff_arg_t *peeloff,
					  काष्ठा file **newfile, अचिन्हित flags)
अणु
	काष्ठा socket *newsock;
	पूर्णांक retval;

	retval = sctp_करो_peeloff(sk, peeloff->associd, &newsock);
	अगर (retval < 0)
		जाओ out;

	/* Map the socket to an unused fd that can be वापसed to the user.  */
	retval = get_unused_fd_flags(flags & SOCK_CLOEXEC);
	अगर (retval < 0) अणु
		sock_release(newsock);
		जाओ out;
	पूर्ण

	*newfile = sock_alloc_file(newsock, 0, शून्य);
	अगर (IS_ERR(*newfile)) अणु
		put_unused_fd(retval);
		retval = PTR_ERR(*newfile);
		*newfile = शून्य;
		वापस retval;
	पूर्ण

	pr_debug("%s: sk:%p, newsk:%p, sd:%d\n", __func__, sk, newsock->sk,
		 retval);

	peeloff->sd = retval;

	अगर (flags & SOCK_NONBLOCK)
		(*newfile)->f_flags |= O_NONBLOCK;
out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_peeloff(काष्ठा sock *sk, पूर्णांक len, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	sctp_peeloff_arg_t peeloff;
	काष्ठा file *newfile = शून्य;
	पूर्णांक retval = 0;

	अगर (len < माप(sctp_peeloff_arg_t))
		वापस -EINVAL;
	len = माप(sctp_peeloff_arg_t);
	अगर (copy_from_user(&peeloff, optval, len))
		वापस -EFAULT;

	retval = sctp_माला_लोockopt_peeloff_common(sk, &peeloff, &newfile, 0);
	अगर (retval < 0)
		जाओ out;

	/* Return the fd mapped to the new socket.  */
	अगर (put_user(len, optlen)) अणु
		fput(newfile);
		put_unused_fd(retval);
		वापस -EFAULT;
	पूर्ण

	अगर (copy_to_user(optval, &peeloff, len)) अणु
		fput(newfile);
		put_unused_fd(retval);
		वापस -EFAULT;
	पूर्ण
	fd_install(retval, newfile);
out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_peeloff_flags(काष्ठा sock *sk, पूर्णांक len,
					 अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	sctp_peeloff_flags_arg_t peeloff;
	काष्ठा file *newfile = शून्य;
	पूर्णांक retval = 0;

	अगर (len < माप(sctp_peeloff_flags_arg_t))
		वापस -EINVAL;
	len = माप(sctp_peeloff_flags_arg_t);
	अगर (copy_from_user(&peeloff, optval, len))
		वापस -EFAULT;

	retval = sctp_माला_लोockopt_peeloff_common(sk, &peeloff.p_arg,
						&newfile, peeloff.flags);
	अगर (retval < 0)
		जाओ out;

	/* Return the fd mapped to the new socket.  */
	अगर (put_user(len, optlen)) अणु
		fput(newfile);
		put_unused_fd(retval);
		वापस -EFAULT;
	पूर्ण

	अगर (copy_to_user(optval, &peeloff, len)) अणु
		fput(newfile);
		put_unused_fd(retval);
		वापस -EFAULT;
	पूर्ण
	fd_install(retval, newfile);
out:
	वापस retval;
पूर्ण

/* 7.1.13 Peer Address Parameters (SCTP_PEER_ADDR_PARAMS)
 *
 * Applications can enable or disable heartbeats क्रम any peer address of
 * an association, modअगरy an address's heartbeat पूर्णांकerval, क्रमce a
 * heartbeat to be sent immediately, and adjust the address's maximum
 * number of retransmissions sent beक्रमe an address is considered
 * unreachable.  The following काष्ठाure is used to access and modअगरy an
 * address's parameters:
 *
 *  काष्ठा sctp_paddrparams अणु
 *     sctp_assoc_t            spp_assoc_id;
 *     काष्ठा sockaddr_storage spp_address;
 *     uपूर्णांक32_t                spp_hbपूर्णांकerval;
 *     uपूर्णांक16_t                spp_pathmaxrxt;
 *     uपूर्णांक32_t                spp_pathmtu;
 *     uपूर्णांक32_t                spp_sackdelay;
 *     uपूर्णांक32_t                spp_flags;
 * पूर्ण;
 *
 *   spp_assoc_id    - (one-to-many style socket) This is filled in the
 *                     application, and identअगरies the association क्रम
 *                     this query.
 *   spp_address     - This specअगरies which address is of पूर्णांकerest.
 *   spp_hbपूर्णांकerval  - This contains the value of the heartbeat पूर्णांकerval,
 *                     in milliseconds.  If a  value of zero
 *                     is present in this field then no changes are to
 *                     be made to this parameter.
 *   spp_pathmaxrxt  - This contains the maximum number of
 *                     retransmissions beक्रमe this address shall be
 *                     considered unreachable. If a  value of zero
 *                     is present in this field then no changes are to
 *                     be made to this parameter.
 *   spp_pathmtu     - When Path MTU discovery is disabled the value
 *                     specअगरied here will be the "fixed" path mtu.
 *                     Note that अगर the spp_address field is empty
 *                     then all associations on this address will
 *                     have this fixed path mtu set upon them.
 *
 *   spp_sackdelay   - When delayed sack is enabled, this value specअगरies
 *                     the number of milliseconds that sacks will be delayed
 *                     क्रम. This value will apply to all addresses of an
 *                     association अगर the spp_address field is empty. Note
 *                     also, that अगर delayed sack is enabled and this
 *                     value is set to 0, no change is made to the last
 *                     recorded delayed sack समयr value.
 *
 *   spp_flags       - These flags are used to control various features
 *                     on an association. The flag field may contain
 *                     zero or more of the following options.
 *
 *                     SPP_HB_ENABLE  - Enable heartbeats on the
 *                     specअगरied address. Note that अगर the address
 *                     field is empty all addresses क्रम the association
 *                     have heartbeats enabled upon them.
 *
 *                     SPP_HB_DISABLE - Disable heartbeats on the
 *                     speicअगरed address. Note that अगर the address
 *                     field is empty all addresses क्रम the association
 *                     will have their heartbeats disabled. Note also
 *                     that SPP_HB_ENABLE and SPP_HB_DISABLE are
 *                     mutually exclusive, only one of these two should
 *                     be specअगरied. Enabling both fields will have
 *                     undetermined results.
 *
 *                     SPP_HB_DEMAND - Request a user initiated heartbeat
 *                     to be made immediately.
 *
 *                     SPP_PMTUD_ENABLE - This field will enable PMTU
 *                     discovery upon the specअगरied address. Note that
 *                     अगर the address feild is empty then all addresses
 *                     on the association are effected.
 *
 *                     SPP_PMTUD_DISABLE - This field will disable PMTU
 *                     discovery upon the specअगरied address. Note that
 *                     अगर the address feild is empty then all addresses
 *                     on the association are effected. Not also that
 *                     SPP_PMTUD_ENABLE and SPP_PMTUD_DISABLE are mutually
 *                     exclusive. Enabling both will have undetermined
 *                     results.
 *
 *                     SPP_SACKDELAY_ENABLE - Setting this flag turns
 *                     on delayed sack. The समय specअगरied in spp_sackdelay
 *                     is used to specअगरy the sack delay क्रम this address. Note
 *                     that अगर spp_address is empty then all addresses will
 *                     enable delayed sack and take on the sack delay
 *                     value specअगरied in spp_sackdelay.
 *                     SPP_SACKDELAY_DISABLE - Setting this flag turns
 *                     off delayed sack. If the spp_address field is blank then
 *                     delayed sack is disabled क्रम the entire association. Note
 *                     also that this field is mutually exclusive to
 *                     SPP_SACKDELAY_ENABLE, setting both will have undefined
 *                     results.
 *
 *                     SPP_IPV6_FLOWLABEL:  Setting this flag enables the
 *                     setting of the IPV6 flow label value.  The value is
 *                     contained in the spp_ipv6_flowlabel field.
 *                     Upon retrieval, this flag will be set to indicate that
 *                     the spp_ipv6_flowlabel field has a valid value वापसed.
 *                     If a specअगरic destination address is set (in the
 *                     spp_address field), then the value वापसed is that of
 *                     the address.  If just an association is specअगरied (and
 *                     no address), then the association's शेष flow label
 *                     is वापसed.  If neither an association nor a destination
 *                     is specअगरied, then the socket's शेष flow label is
 *                     वापसed.  For non-IPv6 sockets, this flag will be left
 *                     cleared.
 *
 *                     SPP_DSCP:  Setting this flag enables the setting of the
 *                     Dअगरferentiated Services Code Poपूर्णांक (DSCP) value
 *                     associated with either the association or a specअगरic
 *                     address.  The value is obtained in the spp_dscp field.
 *                     Upon retrieval, this flag will be set to indicate that
 *                     the spp_dscp field has a valid value वापसed.  If a
 *                     specअगरic destination address is set when called (in the
 *                     spp_address field), then that specअगरic destination
 *                     address's DSCP value is वापसed.  If just an association
 *                     is specअगरied, then the association's शेष DSCP is
 *                     वापसed.  If neither an association nor a destination is
 *                     specअगरied, then the socket's शेष DSCP is वापसed.
 *
 *   spp_ipv6_flowlabel
 *                   - This field is used in conjunction with the
 *                     SPP_IPV6_FLOWLABEL flag and contains the IPv6 flow label.
 *                     The 20 least signअगरicant bits are used क्रम the flow
 *                     label.  This setting has precedence over any IPv6-layer
 *                     setting.
 *
 *   spp_dscp        - This field is used in conjunction with the SPP_DSCP flag
 *                     and contains the DSCP.  The 6 most signअगरicant bits are
 *                     used क्रम the DSCP.  This setting has precedence over any
 *                     IPv4- or IPv6- layer setting.
 */
अटल पूर्णांक sctp_माला_लोockopt_peer_addr_params(काष्ठा sock *sk, पूर्णांक len,
					    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_paddrparams  params;
	काष्ठा sctp_transport   *trans = शून्य;
	काष्ठा sctp_association *asoc = शून्य;
	काष्ठा sctp_sock        *sp = sctp_sk(sk);

	अगर (len >= माप(params))
		len = माप(params);
	अन्यथा अगर (len >= ALIGN(दुरत्व(काष्ठा sctp_paddrparams,
				       spp_ipv6_flowlabel), 4))
		len = ALIGN(दुरत्व(काष्ठा sctp_paddrparams,
				     spp_ipv6_flowlabel), 4);
	अन्यथा
		वापस -EINVAL;

	अगर (copy_from_user(&params, optval, len))
		वापस -EFAULT;

	/* If an address other than INADDR_ANY is specअगरied, and
	 * no transport is found, then the request is invalid.
	 */
	अगर (!sctp_is_any(sk, (जोड़ sctp_addr *)&params.spp_address)) अणु
		trans = sctp_addr_id2transport(sk, &params.spp_address,
					       params.spp_assoc_id);
		अगर (!trans) अणु
			pr_debug("%s: failed no transport\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Get association, अगर assoc_id != SCTP_FUTURE_ASSOC and the
	 * socket is a one to many style socket, and an association
	 * was not found, then the id was invalid.
	 */
	asoc = sctp_id2assoc(sk, params.spp_assoc_id);
	अगर (!asoc && params.spp_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		pr_debug("%s: failed no association\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (trans) अणु
		/* Fetch transport values. */
		params.spp_hbपूर्णांकerval = jअगरfies_to_msecs(trans->hbपूर्णांकerval);
		params.spp_pathmtu    = trans->pathmtu;
		params.spp_pathmaxrxt = trans->pathmaxrxt;
		params.spp_sackdelay  = jअगरfies_to_msecs(trans->sackdelay);

		/*draft-11 करोesn't say what to वापस in spp_flags*/
		params.spp_flags      = trans->param_flags;
		अगर (trans->flowlabel & SCTP_FLOWLABEL_SET_MASK) अणु
			params.spp_ipv6_flowlabel = trans->flowlabel &
						    SCTP_FLOWLABEL_VAL_MASK;
			params.spp_flags |= SPP_IPV6_FLOWLABEL;
		पूर्ण
		अगर (trans->dscp & SCTP_DSCP_SET_MASK) अणु
			params.spp_dscp	= trans->dscp & SCTP_DSCP_VAL_MASK;
			params.spp_flags |= SPP_DSCP;
		पूर्ण
	पूर्ण अन्यथा अगर (asoc) अणु
		/* Fetch association values. */
		params.spp_hbपूर्णांकerval = jअगरfies_to_msecs(asoc->hbपूर्णांकerval);
		params.spp_pathmtu    = asoc->pathmtu;
		params.spp_pathmaxrxt = asoc->pathmaxrxt;
		params.spp_sackdelay  = jअगरfies_to_msecs(asoc->sackdelay);

		/*draft-11 करोesn't say what to वापस in spp_flags*/
		params.spp_flags      = asoc->param_flags;
		अगर (asoc->flowlabel & SCTP_FLOWLABEL_SET_MASK) अणु
			params.spp_ipv6_flowlabel = asoc->flowlabel &
						    SCTP_FLOWLABEL_VAL_MASK;
			params.spp_flags |= SPP_IPV6_FLOWLABEL;
		पूर्ण
		अगर (asoc->dscp & SCTP_DSCP_SET_MASK) अणु
			params.spp_dscp	= asoc->dscp & SCTP_DSCP_VAL_MASK;
			params.spp_flags |= SPP_DSCP;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Fetch socket values. */
		params.spp_hbपूर्णांकerval = sp->hbपूर्णांकerval;
		params.spp_pathmtu    = sp->pathmtu;
		params.spp_sackdelay  = sp->sackdelay;
		params.spp_pathmaxrxt = sp->pathmaxrxt;

		/*draft-11 करोesn't say what to वापस in spp_flags*/
		params.spp_flags      = sp->param_flags;
		अगर (sp->flowlabel & SCTP_FLOWLABEL_SET_MASK) अणु
			params.spp_ipv6_flowlabel = sp->flowlabel &
						    SCTP_FLOWLABEL_VAL_MASK;
			params.spp_flags |= SPP_IPV6_FLOWLABEL;
		पूर्ण
		अगर (sp->dscp & SCTP_DSCP_SET_MASK) अणु
			params.spp_dscp	= sp->dscp & SCTP_DSCP_VAL_MASK;
			params.spp_flags |= SPP_DSCP;
		पूर्ण
	पूर्ण

	अगर (copy_to_user(optval, &params, len))
		वापस -EFAULT;

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 7.1.23.  Get or set delayed ack समयr (SCTP_DELAYED_SACK)
 *
 * This option will effect the way delayed acks are perक्रमmed.  This
 * option allows you to get or set the delayed ack समय, in
 * milliseconds.  It also allows changing the delayed ack frequency.
 * Changing the frequency to 1 disables the delayed sack algorithm.  If
 * the assoc_id is 0, then this sets or माला_लो the endpoपूर्णांकs शेष
 * values.  If the assoc_id field is non-zero, then the set or get
 * effects the specअगरied association क्रम the one to many model (the
 * assoc_id field is ignored by the one to one model).  Note that अगर
 * sack_delay or sack_freq are 0 when setting this option, then the
 * current values will reमुख्य unchanged.
 *
 * काष्ठा sctp_sack_info अणु
 *     sctp_assoc_t            sack_assoc_id;
 *     uपूर्णांक32_t                sack_delay;
 *     uपूर्णांक32_t                sack_freq;
 * पूर्ण;
 *
 * sack_assoc_id -  This parameter, indicates which association the user
 *    is perक्रमming an action upon.  Note that अगर this field's value is
 *    zero then the endpoपूर्णांकs शेष value is changed (effecting future
 *    associations only).
 *
 * sack_delay -  This parameter contains the number of milliseconds that
 *    the user is requesting the delayed ACK समयr be set to.  Note that
 *    this value is defined in the standard to be between 200 and 500
 *    milliseconds.
 *
 * sack_freq -  This parameter contains the number of packets that must
 *    be received beक्रमe a sack is sent without रुकोing क्रम the delay
 *    समयr to expire.  The शेष value क्रम this is 2, setting this
 *    value to 1 will disable the delayed sack algorithm.
 */
अटल पूर्णांक sctp_माला_लोockopt_delayed_ack(काष्ठा sock *sk, पूर्णांक len,
					    अक्षर __user *optval,
					    पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_sack_info    params;
	काष्ठा sctp_association *asoc = शून्य;
	काष्ठा sctp_sock        *sp = sctp_sk(sk);

	अगर (len >= माप(काष्ठा sctp_sack_info)) अणु
		len = माप(काष्ठा sctp_sack_info);

		अगर (copy_from_user(&params, optval, len))
			वापस -EFAULT;
	पूर्ण अन्यथा अगर (len == माप(काष्ठा sctp_assoc_value)) अणु
		pr_warn_ratelimited(DEPRECATED
				    "%s (pid %d) "
				    "Use of struct sctp_assoc_value in delayed_ack socket option.\n"
				    "Use struct sctp_sack_info instead\n",
				    current->comm, task_pid_nr(current));
		अगर (copy_from_user(&params, optval, len))
			वापस -EFAULT;
	पूर्ण अन्यथा
		वापस -EINVAL;

	/* Get association, अगर sack_assoc_id != SCTP_FUTURE_ASSOC and the
	 * socket is a one to many style socket, and an association
	 * was not found, then the id was invalid.
	 */
	asoc = sctp_id2assoc(sk, params.sack_assoc_id);
	अगर (!asoc && params.sack_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		/* Fetch association values. */
		अगर (asoc->param_flags & SPP_SACKDELAY_ENABLE) अणु
			params.sack_delay = jअगरfies_to_msecs(asoc->sackdelay);
			params.sack_freq = asoc->sackfreq;

		पूर्ण अन्यथा अणु
			params.sack_delay = 0;
			params.sack_freq = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Fetch socket values. */
		अगर (sp->param_flags & SPP_SACKDELAY_ENABLE) अणु
			params.sack_delay  = sp->sackdelay;
			params.sack_freq = sp->sackfreq;
		पूर्ण अन्यथा अणु
			params.sack_delay  = 0;
			params.sack_freq = 1;
		पूर्ण
	पूर्ण

	अगर (copy_to_user(optval, &params, len))
		वापस -EFAULT;

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* 7.1.3 Initialization Parameters (SCTP_INITMSG)
 *
 * Applications can specअगरy protocol parameters क्रम the शेष association
 * initialization.  The option name argument to setsockopt() and माला_लोockopt()
 * is SCTP_INITMSG.
 *
 * Setting initialization parameters is effective only on an unconnected
 * socket (क्रम UDP-style sockets only future associations are effected
 * by the change).  With TCP-style sockets, this option is inherited by
 * sockets derived from a listener socket.
 */
अटल पूर्णांक sctp_माला_लोockopt_iniपंचांगsg(काष्ठा sock *sk, पूर्णांक len, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	अगर (len < माप(काष्ठा sctp_iniपंचांगsg))
		वापस -EINVAL;
	len = माप(काष्ठा sctp_iniपंचांगsg);
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &sctp_sk(sk)->iniपंचांगsg, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण


अटल पूर्णांक sctp_माला_लोockopt_peer_addrs(काष्ठा sock *sk, पूर्णांक len,
				      अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_association *asoc;
	पूर्णांक cnt = 0;
	काष्ठा sctp_getaddrs getaddrs;
	काष्ठा sctp_transport *from;
	व्योम __user *to;
	जोड़ sctp_addr temp;
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	पूर्णांक addrlen;
	माप_प्रकार space_left;
	पूर्णांक bytes_copied;

	अगर (len < माप(काष्ठा sctp_getaddrs))
		वापस -EINVAL;

	अगर (copy_from_user(&getaddrs, optval, माप(काष्ठा sctp_getaddrs)))
		वापस -EFAULT;

	/* For UDP-style sockets, id specअगरies the association to query.  */
	asoc = sctp_id2assoc(sk, getaddrs.assoc_id);
	अगर (!asoc)
		वापस -EINVAL;

	to = optval + दुरत्व(काष्ठा sctp_getaddrs, addrs);
	space_left = len - दुरत्व(काष्ठा sctp_getaddrs, addrs);

	list_क्रम_each_entry(from, &asoc->peer.transport_addr_list,
				transports) अणु
		स_नकल(&temp, &from->ipaddr, माप(temp));
		addrlen = sctp_get_pf_specअगरic(sk->sk_family)
			      ->addr_to_user(sp, &temp);
		अगर (space_left < addrlen)
			वापस -ENOMEM;
		अगर (copy_to_user(to, &temp, addrlen))
			वापस -EFAULT;
		to += addrlen;
		cnt++;
		space_left -= addrlen;
	पूर्ण

	अगर (put_user(cnt, &((काष्ठा sctp_getaddrs __user *)optval)->addr_num))
		वापस -EFAULT;
	bytes_copied = ((अक्षर __user *)to) - optval;
	अगर (put_user(bytes_copied, optlen))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_copy_laddrs(काष्ठा sock *sk, __u16 port, व्योम *to,
			    माप_प्रकार space_left, पूर्णांक *bytes_copied)
अणु
	काष्ठा sctp_sockaddr_entry *addr;
	जोड़ sctp_addr temp;
	पूर्णांक cnt = 0;
	पूर्णांक addrlen;
	काष्ठा net *net = sock_net(sk);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(addr, &net->sctp.local_addr_list, list) अणु
		अगर (!addr->valid)
			जारी;

		अगर ((PF_INET == sk->sk_family) &&
		    (AF_INET6 == addr->a.sa.sa_family))
			जारी;
		अगर ((PF_INET6 == sk->sk_family) &&
		    inet_v6_ipv6only(sk) &&
		    (AF_INET == addr->a.sa.sa_family))
			जारी;
		स_नकल(&temp, &addr->a, माप(temp));
		अगर (!temp.v4.sin_port)
			temp.v4.sin_port = htons(port);

		addrlen = sctp_get_pf_specअगरic(sk->sk_family)
			      ->addr_to_user(sctp_sk(sk), &temp);

		अगर (space_left < addrlen) अणु
			cnt =  -ENOMEM;
			अवरोध;
		पूर्ण
		स_नकल(to, &temp, addrlen);

		to += addrlen;
		cnt++;
		space_left -= addrlen;
		*bytes_copied += addrlen;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस cnt;
पूर्ण


अटल पूर्णांक sctp_माला_लोockopt_local_addrs(काष्ठा sock *sk, पूर्णांक len,
				       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_bind_addr *bp;
	काष्ठा sctp_association *asoc;
	पूर्णांक cnt = 0;
	काष्ठा sctp_getaddrs getaddrs;
	काष्ठा sctp_sockaddr_entry *addr;
	व्योम __user *to;
	जोड़ sctp_addr temp;
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	पूर्णांक addrlen;
	पूर्णांक err = 0;
	माप_प्रकार space_left;
	पूर्णांक bytes_copied = 0;
	व्योम *addrs;
	व्योम *buf;

	अगर (len < माप(काष्ठा sctp_getaddrs))
		वापस -EINVAL;

	अगर (copy_from_user(&getaddrs, optval, माप(काष्ठा sctp_getaddrs)))
		वापस -EFAULT;

	/*
	 *  For UDP-style sockets, id specअगरies the association to query.
	 *  If the id field is set to the value '0' then the locally bound
	 *  addresses are वापसed without regard to any particular
	 *  association.
	 */
	अगर (0 == getaddrs.assoc_id) अणु
		bp = &sctp_sk(sk)->ep->base.bind_addr;
	पूर्ण अन्यथा अणु
		asoc = sctp_id2assoc(sk, getaddrs.assoc_id);
		अगर (!asoc)
			वापस -EINVAL;
		bp = &asoc->base.bind_addr;
	पूर्ण

	to = optval + दुरत्व(काष्ठा sctp_getaddrs, addrs);
	space_left = len - दुरत्व(काष्ठा sctp_getaddrs, addrs);

	addrs = kदो_स्मृति(space_left, GFP_USER | __GFP_NOWARN);
	अगर (!addrs)
		वापस -ENOMEM;

	/* If the endpoपूर्णांक is bound to 0.0.0.0 or ::0, get the valid
	 * addresses from the global local address list.
	 */
	अगर (sctp_list_single_entry(&bp->address_list)) अणु
		addr = list_entry(bp->address_list.next,
				  काष्ठा sctp_sockaddr_entry, list);
		अगर (sctp_is_any(sk, &addr->a)) अणु
			cnt = sctp_copy_laddrs(sk, bp->port, addrs,
						space_left, &bytes_copied);
			अगर (cnt < 0) अणु
				err = cnt;
				जाओ out;
			पूर्ण
			जाओ copy_getaddrs;
		पूर्ण
	पूर्ण

	buf = addrs;
	/* Protection on the bound address list is not needed since
	 * in the socket option context we hold a socket lock and
	 * thus the bound address list can't change.
	 */
	list_क्रम_each_entry(addr, &bp->address_list, list) अणु
		स_नकल(&temp, &addr->a, माप(temp));
		addrlen = sctp_get_pf_specअगरic(sk->sk_family)
			      ->addr_to_user(sp, &temp);
		अगर (space_left < addrlen) अणु
			err =  -ENOMEM; /*fixme: right error?*/
			जाओ out;
		पूर्ण
		स_नकल(buf, &temp, addrlen);
		buf += addrlen;
		bytes_copied += addrlen;
		cnt++;
		space_left -= addrlen;
	पूर्ण

copy_getaddrs:
	अगर (copy_to_user(to, addrs, bytes_copied)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (put_user(cnt, &((काष्ठा sctp_getaddrs __user *)optval)->addr_num)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण
	/* XXX: We should have accounted क्रम माप(काष्ठा sctp_getaddrs) too,
	 * but we can't change it anymore.
	 */
	अगर (put_user(bytes_copied, optlen))
		err = -EFAULT;
out:
	kमुक्त(addrs);
	वापस err;
पूर्ण

/* 7.1.10 Set Primary Address (SCTP_PRIMARY_ADDR)
 *
 * Requests that the local SCTP stack use the enबंदd peer address as
 * the association primary.  The enबंदd address must be one of the
 * association peer's addresses.
 */
अटल पूर्णांक sctp_माला_लोockopt_primary_addr(काष्ठा sock *sk, पूर्णांक len,
					अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_prim prim;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_sock *sp = sctp_sk(sk);

	अगर (len < माप(काष्ठा sctp_prim))
		वापस -EINVAL;

	len = माप(काष्ठा sctp_prim);

	अगर (copy_from_user(&prim, optval, len))
		वापस -EFAULT;

	asoc = sctp_id2assoc(sk, prim.ssp_assoc_id);
	अगर (!asoc)
		वापस -EINVAL;

	अगर (!asoc->peer.primary_path)
		वापस -ENOTCONN;

	स_नकल(&prim.ssp_addr, &asoc->peer.primary_path->ipaddr,
		asoc->peer.primary_path->af_specअगरic->sockaddr_len);

	sctp_get_pf_specअगरic(sk->sk_family)->addr_to_user(sp,
			(जोड़ sctp_addr *)&prim.ssp_addr);

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &prim, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 7.1.11  Set Adaptation Layer Indicator (SCTP_ADAPTATION_LAYER)
 *
 * Requests that the local endpoपूर्णांक set the specअगरied Adaptation Layer
 * Indication parameter क्रम all future INIT and INIT-ACK exchanges.
 */
अटल पूर्णांक sctp_माला_लोockopt_adaptation_layer(काष्ठा sock *sk, पूर्णांक len,
				  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_setadaptation adaptation;

	अगर (len < माप(काष्ठा sctp_setadaptation))
		वापस -EINVAL;

	len = माप(काष्ठा sctp_setadaptation);

	adaptation.ssb_adaptation_ind = sctp_sk(sk)->adaptation_ind;

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &adaptation, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 *
 * 7.1.14 Set शेष send parameters (SCTP_DEFAULT_SEND_PARAM)
 *
 *   Applications that wish to use the sendto() प्रणाली call may wish to
 *   specअगरy a शेष set of parameters that would normally be supplied
 *   through the inclusion of ancillary data.  This socket option allows
 *   such an application to set the शेष sctp_sndrcvinfo काष्ठाure.


 *   The application that wishes to use this socket option simply passes
 *   in to this call the sctp_sndrcvinfo काष्ठाure defined in Section
 *   5.2.2) The input parameters accepted by this call include
 *   sinfo_stream, sinfo_flags, sinfo_ppid, sinfo_context,
 *   sinfo_समयtolive.  The user must provide the sinfo_assoc_id field in
 *   to this call अगर the caller is using the UDP model.
 *
 *   For माला_लोockopt, it get the शेष sctp_sndrcvinfo काष्ठाure.
 */
अटल पूर्णांक sctp_माला_लोockopt_शेष_send_param(काष्ठा sock *sk,
					पूर्णांक len, अक्षर __user *optval,
					पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_sndrcvinfo info;

	अगर (len < माप(info))
		वापस -EINVAL;

	len = माप(info);

	अगर (copy_from_user(&info, optval, len))
		वापस -EFAULT;

	asoc = sctp_id2assoc(sk, info.sinfo_assoc_id);
	अगर (!asoc && info.sinfo_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		info.sinfo_stream = asoc->शेष_stream;
		info.sinfo_flags = asoc->शेष_flags;
		info.sinfo_ppid = asoc->शेष_ppid;
		info.sinfo_context = asoc->शेष_context;
		info.sinfo_समयtolive = asoc->शेष_समयtolive;
	पूर्ण अन्यथा अणु
		info.sinfo_stream = sp->शेष_stream;
		info.sinfo_flags = sp->शेष_flags;
		info.sinfo_ppid = sp->शेष_ppid;
		info.sinfo_context = sp->शेष_context;
		info.sinfo_समयtolive = sp->शेष_समयtolive;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &info, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* RFC6458, Section 8.1.31. Set/get Default Send Parameters
 * (SCTP_DEFAULT_SNDINFO)
 */
अटल पूर्णांक sctp_माला_लोockopt_शेष_sndinfo(काष्ठा sock *sk, पूर्णांक len,
					   अक्षर __user *optval,
					   पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_sndinfo info;

	अगर (len < माप(info))
		वापस -EINVAL;

	len = माप(info);

	अगर (copy_from_user(&info, optval, len))
		वापस -EFAULT;

	asoc = sctp_id2assoc(sk, info.snd_assoc_id);
	अगर (!asoc && info.snd_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		info.snd_sid = asoc->शेष_stream;
		info.snd_flags = asoc->शेष_flags;
		info.snd_ppid = asoc->शेष_ppid;
		info.snd_context = asoc->शेष_context;
	पूर्ण अन्यथा अणु
		info.snd_sid = sp->शेष_stream;
		info.snd_flags = sp->शेष_flags;
		info.snd_ppid = sp->शेष_ppid;
		info.snd_context = sp->शेष_context;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &info, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 *
 * 7.1.5 SCTP_NODELAY
 *
 * Turn on/off any Nagle-like algorithm.  This means that packets are
 * generally sent as soon as possible and no unnecessary delays are
 * पूर्णांकroduced, at the cost of more packets in the network.  Expects an
 * पूर्णांकeger boolean flag.
 */

अटल पूर्णांक sctp_माला_लोockopt_nodelay(काष्ठा sock *sk, पूर्णांक len,
				   अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक val;

	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;

	len = माप(पूर्णांक);
	val = (sctp_sk(sk)->nodelay == 1);
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 *
 * 7.1.1 SCTP_RTOINFO
 *
 * The protocol parameters used to initialize and bound retransmission
 * समयout (RTO) are tunable. sctp_rtoinfo काष्ठाure is used to access
 * and modअगरy these parameters.
 * All parameters are समय values, in milliseconds.  A value of 0, when
 * modअगरying the parameters, indicates that the current value should not
 * be changed.
 *
 */
अटल पूर्णांक sctp_माला_लोockopt_rtoinfo(काष्ठा sock *sk, पूर्णांक len,
				अक्षर __user *optval,
				पूर्णांक __user *optlen) अणु
	काष्ठा sctp_rtoinfo rtoinfo;
	काष्ठा sctp_association *asoc;

	अगर (len < माप (काष्ठा sctp_rtoinfo))
		वापस -EINVAL;

	len = माप(काष्ठा sctp_rtoinfo);

	अगर (copy_from_user(&rtoinfo, optval, len))
		वापस -EFAULT;

	asoc = sctp_id2assoc(sk, rtoinfo.srto_assoc_id);

	अगर (!asoc && rtoinfo.srto_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	/* Values corresponding to the specअगरic association. */
	अगर (asoc) अणु
		rtoinfo.srto_initial = jअगरfies_to_msecs(asoc->rto_initial);
		rtoinfo.srto_max = jअगरfies_to_msecs(asoc->rto_max);
		rtoinfo.srto_min = jअगरfies_to_msecs(asoc->rto_min);
	पूर्ण अन्यथा अणु
		/* Values corresponding to the endpoपूर्णांक. */
		काष्ठा sctp_sock *sp = sctp_sk(sk);

		rtoinfo.srto_initial = sp->rtoinfo.srto_initial;
		rtoinfo.srto_max = sp->rtoinfo.srto_max;
		rtoinfo.srto_min = sp->rtoinfo.srto_min;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	अगर (copy_to_user(optval, &rtoinfo, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 *
 * 7.1.2 SCTP_ASSOCINFO
 *
 * This option is used to tune the maximum retransmission attempts
 * of the association.
 * Returns an error अगर the new association retransmission value is
 * greater than the sum of the retransmission value  of the peer.
 * See [SCTP] क्रम more inक्रमmation.
 *
 */
अटल पूर्णांक sctp_माला_लोockopt_associnfo(काष्ठा sock *sk, पूर्णांक len,
				     अक्षर __user *optval,
				     पूर्णांक __user *optlen)
अणु

	काष्ठा sctp_assocparams assocparams;
	काष्ठा sctp_association *asoc;
	काष्ठा list_head *pos;
	पूर्णांक cnt = 0;

	अगर (len < माप (काष्ठा sctp_assocparams))
		वापस -EINVAL;

	len = माप(काष्ठा sctp_assocparams);

	अगर (copy_from_user(&assocparams, optval, len))
		वापस -EFAULT;

	asoc = sctp_id2assoc(sk, assocparams.sasoc_assoc_id);

	अगर (!asoc && assocparams.sasoc_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	/* Values correspoinding to the specअगरic association */
	अगर (asoc) अणु
		assocparams.sasoc_asocmaxrxt = asoc->max_retrans;
		assocparams.sasoc_peer_rwnd = asoc->peer.rwnd;
		assocparams.sasoc_local_rwnd = asoc->a_rwnd;
		assocparams.sasoc_cookie_lअगरe = kसमय_प्रकारo_ms(asoc->cookie_lअगरe);

		list_क्रम_each(pos, &asoc->peer.transport_addr_list) अणु
			cnt++;
		पूर्ण

		assocparams.sasoc_number_peer_destinations = cnt;
	पूर्ण अन्यथा अणु
		/* Values corresponding to the endpoपूर्णांक */
		काष्ठा sctp_sock *sp = sctp_sk(sk);

		assocparams.sasoc_asocmaxrxt = sp->assocparams.sasoc_asocmaxrxt;
		assocparams.sasoc_peer_rwnd = sp->assocparams.sasoc_peer_rwnd;
		assocparams.sasoc_local_rwnd = sp->assocparams.sasoc_local_rwnd;
		assocparams.sasoc_cookie_lअगरe =
					sp->assocparams.sasoc_cookie_lअगरe;
		assocparams.sasoc_number_peer_destinations =
					sp->assocparams.
					sasoc_number_peer_destinations;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	अगर (copy_to_user(optval, &assocparams, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 7.1.16 Set/clear IPv4 mapped addresses (SCTP_I_WANT_MAPPED_V4_ADDR)
 *
 * This socket option is a boolean flag which turns on or off mapped V4
 * addresses.  If this option is turned on and the socket is type
 * PF_INET6, then IPv4 addresses will be mapped to V6 representation.
 * If this option is turned off, then no mapping will be करोne of V4
 * addresses and a user will receive both PF_INET6 and PF_INET type
 * addresses on the socket.
 */
अटल पूर्णांक sctp_माला_लोockopt_mappedv4(काष्ठा sock *sk, पूर्णांक len,
				    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक val;
	काष्ठा sctp_sock *sp = sctp_sk(sk);

	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;

	len = माप(पूर्णांक);
	val = sp->v4mapped;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 7.1.29.  Set or Get the शेष context (SCTP_CONTEXT)
 * (chapter and verse is quoted at sctp_setsockopt_context())
 */
अटल पूर्णांक sctp_माला_लोockopt_context(काष्ठा sock *sk, पूर्णांक len,
				   अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;

	अगर (len < माप(काष्ठा sctp_assoc_value))
		वापस -EINVAL;

	len = माप(काष्ठा sctp_assoc_value);

	अगर (copy_from_user(&params, optval, len))
		वापस -EFAULT;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	params.assoc_value = asoc ? asoc->शेष_rcv_context
				  : sctp_sk(sk)->शेष_rcv_context;

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &params, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 8.1.16.  Get or Set the Maximum Fragmentation Size (SCTP_MAXSEG)
 * This option will get or set the maximum size to put in any outgoing
 * SCTP DATA chunk.  If a message is larger than this size it will be
 * fragmented by SCTP पूर्णांकo the specअगरied size.  Note that the underlying
 * SCTP implementation may fragment पूर्णांकo smaller sized chunks when the
 * PMTU of the underlying association is smaller than the value set by
 * the user.  The शेष value क्रम this option is '0' which indicates
 * the user is NOT limiting fragmentation and only the PMTU will effect
 * SCTP's choice of DATA chunk size.  Note also that values set larger
 * than the maximum size of an IP datagram will effectively let SCTP
 * control fragmentation (i.e. the same as setting this option to 0).
 *
 * The following काष्ठाure is used to access and modअगरy this parameter:
 *
 * काष्ठा sctp_assoc_value अणु
 *   sctp_assoc_t assoc_id;
 *   uपूर्णांक32_t assoc_value;
 * पूर्ण;
 *
 * assoc_id:  This parameter is ignored क्रम one-to-one style sockets.
 *    For one-to-many style sockets this parameter indicates which
 *    association the user is perक्रमming an action upon.  Note that अगर
 *    this field's value is zero then the endpoपूर्णांकs शेष value is
 *    changed (effecting future associations only).
 * assoc_value:  This parameter specअगरies the maximum size in bytes.
 */
अटल पूर्णांक sctp_माला_लोockopt_maxseg(काष्ठा sock *sk, पूर्णांक len,
				  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;

	अगर (len == माप(पूर्णांक)) अणु
		pr_warn_ratelimited(DEPRECATED
				    "%s (pid %d) "
				    "Use of int in maxseg socket option.\n"
				    "Use struct sctp_assoc_value instead\n",
				    current->comm, task_pid_nr(current));
		params.assoc_id = SCTP_FUTURE_ASSOC;
	पूर्ण अन्यथा अगर (len >= माप(काष्ठा sctp_assoc_value)) अणु
		len = माप(काष्ठा sctp_assoc_value);
		अगर (copy_from_user(&params, optval, len))
			वापस -EFAULT;
	पूर्ण अन्यथा
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc)
		params.assoc_value = asoc->frag_poपूर्णांक;
	अन्यथा
		params.assoc_value = sctp_sk(sk)->user_frag;

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (len == माप(पूर्णांक)) अणु
		अगर (copy_to_user(optval, &params.assoc_value, len))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(optval, &params, len))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * 7.1.24.  Get or set fragmented पूर्णांकerleave (SCTP_FRAGMENT_INTERLEAVE)
 * (chapter and verse is quoted at sctp_setsockopt_fragment_पूर्णांकerleave())
 */
अटल पूर्णांक sctp_माला_लोockopt_fragment_पूर्णांकerleave(काष्ठा sock *sk, पूर्णांक len,
					       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक val;

	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;

	len = माप(पूर्णांक);

	val = sctp_sk(sk)->frag_पूर्णांकerleave;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 7.1.25.  Set or Get the sctp partial delivery poपूर्णांक
 * (chapter and verse is quoted at sctp_setsockopt_partial_delivery_poपूर्णांक())
 */
अटल पूर्णांक sctp_माला_लोockopt_partial_delivery_poपूर्णांक(काष्ठा sock *sk, पूर्णांक len,
						  अक्षर __user *optval,
						  पूर्णांक __user *optlen)
अणु
	u32 val;

	अगर (len < माप(u32))
		वापस -EINVAL;

	len = माप(u32);

	val = sctp_sk(sk)->pd_poपूर्णांक;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 7.1.28.  Set or Get the maximum burst (SCTP_MAX_BURST)
 * (chapter and verse is quoted at sctp_setsockopt_maxburst())
 */
अटल पूर्णांक sctp_माला_लोockopt_maxburst(काष्ठा sock *sk, पूर्णांक len,
				    अक्षर __user *optval,
				    पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;

	अगर (len == माप(पूर्णांक)) अणु
		pr_warn_ratelimited(DEPRECATED
				    "%s (pid %d) "
				    "Use of int in max_burst socket option.\n"
				    "Use struct sctp_assoc_value instead\n",
				    current->comm, task_pid_nr(current));
		params.assoc_id = SCTP_FUTURE_ASSOC;
	पूर्ण अन्यथा अगर (len >= माप(काष्ठा sctp_assoc_value)) अणु
		len = माप(काष्ठा sctp_assoc_value);
		अगर (copy_from_user(&params, optval, len))
			वापस -EFAULT;
	पूर्ण अन्यथा
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	params.assoc_value = asoc ? asoc->max_burst : sctp_sk(sk)->max_burst;

	अगर (len == माप(पूर्णांक)) अणु
		अगर (copy_to_user(optval, &params.assoc_value, len))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(optval, &params, len))
			वापस -EFAULT;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_hmac_ident(काष्ठा sock *sk, पूर्णांक len,
				    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_hmacalgo  __user *p = (व्योम __user *)optval;
	काष्ठा sctp_hmac_algo_param *hmacs;
	__u16 data_len = 0;
	u32 num_idents;
	पूर्णांक i;

	अगर (!ep->auth_enable)
		वापस -EACCES;

	hmacs = ep->auth_hmacs_list;
	data_len = ntohs(hmacs->param_hdr.length) -
		   माप(काष्ठा sctp_paramhdr);

	अगर (len < माप(काष्ठा sctp_hmacalgo) + data_len)
		वापस -EINVAL;

	len = माप(काष्ठा sctp_hmacalgo) + data_len;
	num_idents = data_len / माप(u16);

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (put_user(num_idents, &p->shmac_num_idents))
		वापस -EFAULT;
	क्रम (i = 0; i < num_idents; i++) अणु
		__u16 hmacid = ntohs(hmacs->hmac_ids[i]);

		अगर (copy_to_user(&p->shmac_idents[i], &hmacid, माप(__u16)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_active_key(काष्ठा sock *sk, पूर्णांक len,
				    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_authkeyid val;
	काष्ठा sctp_association *asoc;

	अगर (len < माप(काष्ठा sctp_authkeyid))
		वापस -EINVAL;

	len = माप(काष्ठा sctp_authkeyid);
	अगर (copy_from_user(&val, optval, len))
		वापस -EFAULT;

	asoc = sctp_id2assoc(sk, val.scact_assoc_id);
	अगर (!asoc && val.scact_assoc_id && sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		अगर (!asoc->peer.auth_capable)
			वापस -EACCES;
		val.scact_keynumber = asoc->active_key_id;
	पूर्ण अन्यथा अणु
		अगर (!ep->auth_enable)
			वापस -EACCES;
		val.scact_keynumber = ep->active_key_id;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_peer_auth_chunks(काष्ठा sock *sk, पूर्णांक len,
				    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_authchunks __user *p = (व्योम __user *)optval;
	काष्ठा sctp_authchunks val;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_chunks_param *ch;
	u32    num_chunks = 0;
	अक्षर __user *to;

	अगर (len < माप(काष्ठा sctp_authchunks))
		वापस -EINVAL;

	अगर (copy_from_user(&val, optval, माप(val)))
		वापस -EFAULT;

	to = p->gauth_chunks;
	asoc = sctp_id2assoc(sk, val.gauth_assoc_id);
	अगर (!asoc)
		वापस -EINVAL;

	अगर (!asoc->peer.auth_capable)
		वापस -EACCES;

	ch = asoc->peer.peer_chunks;
	अगर (!ch)
		जाओ num;

	/* See अगर the user provided enough room क्रम all the data */
	num_chunks = ntohs(ch->param_hdr.length) - माप(काष्ठा sctp_paramhdr);
	अगर (len < num_chunks)
		वापस -EINVAL;

	अगर (copy_to_user(to, ch->chunks, num_chunks))
		वापस -EFAULT;
num:
	len = माप(काष्ठा sctp_authchunks) + num_chunks;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (put_user(num_chunks, &p->gauth_number_of_chunks))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_local_auth_chunks(काष्ठा sock *sk, पूर्णांक len,
				    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	काष्ठा sctp_authchunks __user *p = (व्योम __user *)optval;
	काष्ठा sctp_authchunks val;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_chunks_param *ch;
	u32    num_chunks = 0;
	अक्षर __user *to;

	अगर (len < माप(काष्ठा sctp_authchunks))
		वापस -EINVAL;

	अगर (copy_from_user(&val, optval, माप(val)))
		वापस -EFAULT;

	to = p->gauth_chunks;
	asoc = sctp_id2assoc(sk, val.gauth_assoc_id);
	अगर (!asoc && val.gauth_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		अगर (!asoc->peer.auth_capable)
			वापस -EACCES;
		ch = (काष्ठा sctp_chunks_param *)asoc->c.auth_chunks;
	पूर्ण अन्यथा अणु
		अगर (!ep->auth_enable)
			वापस -EACCES;
		ch = ep->auth_chunk_list;
	पूर्ण
	अगर (!ch)
		जाओ num;

	num_chunks = ntohs(ch->param_hdr.length) - माप(काष्ठा sctp_paramhdr);
	अगर (len < माप(काष्ठा sctp_authchunks) + num_chunks)
		वापस -EINVAL;

	अगर (copy_to_user(to, ch->chunks, num_chunks))
		वापस -EFAULT;
num:
	len = माप(काष्ठा sctp_authchunks) + num_chunks;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (put_user(num_chunks, &p->gauth_number_of_chunks))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 8.2.5.  Get the Current Number of Associations (SCTP_GET_ASSOC_NUMBER)
 * This option माला_लो the current number of associations that are attached
 * to a one-to-many style socket.  The option value is an uपूर्णांक32_t.
 */
अटल पूर्णांक sctp_माला_लोockopt_assoc_number(काष्ठा sock *sk, पूर्णांक len,
				    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	u32 val = 0;

	अगर (sctp_style(sk, TCP))
		वापस -EOPNOTSUPP;

	अगर (len < माप(u32))
		वापस -EINVAL;

	len = माप(u32);

	list_क्रम_each_entry(asoc, &(sp->ep->asocs), asocs) अणु
		val++;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * 8.1.23 SCTP_AUTO_ASCONF
 * See the corresponding setsockopt entry as description
 */
अटल पूर्णांक sctp_माला_लोockopt_स्वतः_asconf(काष्ठा sock *sk, पूर्णांक len,
				   अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक val = 0;

	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;

	len = माप(पूर्णांक);
	अगर (sctp_sk(sk)->करो_स्वतः_asconf && sctp_is_ep_boundall(sk))
		val = 1;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * 8.2.6. Get the Current Identअगरiers of Associations
 *        (SCTP_GET_ASSOC_ID_LIST)
 *
 * This option माला_लो the current list of SCTP association identअगरiers of
 * the SCTP associations handled by a one-to-many style socket.
 */
अटल पूर्णांक sctp_माला_लोockopt_assoc_ids(काष्ठा sock *sk, पूर्णांक len,
				    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_assoc_ids *ids;
	u32 num = 0;

	अगर (sctp_style(sk, TCP))
		वापस -EOPNOTSUPP;

	अगर (len < माप(काष्ठा sctp_assoc_ids))
		वापस -EINVAL;

	list_क्रम_each_entry(asoc, &(sp->ep->asocs), asocs) अणु
		num++;
	पूर्ण

	अगर (len < माप(काष्ठा sctp_assoc_ids) + माप(sctp_assoc_t) * num)
		वापस -EINVAL;

	len = माप(काष्ठा sctp_assoc_ids) + माप(sctp_assoc_t) * num;

	ids = kदो_स्मृति(len, GFP_USER | __GFP_NOWARN);
	अगर (unlikely(!ids))
		वापस -ENOMEM;

	ids->gaids_number_of_ids = num;
	num = 0;
	list_क्रम_each_entry(asoc, &(sp->ep->asocs), asocs) अणु
		ids->gaids_assoc_id[num++] = asoc->assoc_id;
	पूर्ण

	अगर (put_user(len, optlen) || copy_to_user(optval, ids, len)) अणु
		kमुक्त(ids);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(ids);
	वापस 0;
पूर्ण

/*
 * SCTP_PEER_ADDR_THLDS
 *
 * This option allows us to fetch the partially failed threshold क्रम one or all
 * transports in an association.  See Section 6.1 of:
 * http://www.ietf.org/id/draft-nishida-tsvwg-sctp-failover-05.txt
 */
अटल पूर्णांक sctp_माला_लोockopt_paddr_thresholds(काष्ठा sock *sk,
					    अक्षर __user *optval, पूर्णांक len,
					    पूर्णांक __user *optlen, bool v2)
अणु
	काष्ठा sctp_paddrthlds_v2 val;
	काष्ठा sctp_transport *trans;
	काष्ठा sctp_association *asoc;
	पूर्णांक min;

	min = v2 ? माप(val) : माप(काष्ठा sctp_paddrthlds);
	अगर (len < min)
		वापस -EINVAL;
	len = min;
	अगर (copy_from_user(&val, optval, len))
		वापस -EFAULT;

	अगर (!sctp_is_any(sk, (स्थिर जोड़ sctp_addr *)&val.spt_address)) अणु
		trans = sctp_addr_id2transport(sk, &val.spt_address,
					       val.spt_assoc_id);
		अगर (!trans)
			वापस -ENOENT;

		val.spt_pathmaxrxt = trans->pathmaxrxt;
		val.spt_pathpfthld = trans->pf_retrans;
		val.spt_pathcpthld = trans->ps_retrans;

		जाओ out;
	पूर्ण

	asoc = sctp_id2assoc(sk, val.spt_assoc_id);
	अगर (!asoc && val.spt_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	अगर (asoc) अणु
		val.spt_pathpfthld = asoc->pf_retrans;
		val.spt_pathmaxrxt = asoc->pathmaxrxt;
		val.spt_pathcpthld = asoc->ps_retrans;
	पूर्ण अन्यथा अणु
		काष्ठा sctp_sock *sp = sctp_sk(sk);

		val.spt_pathpfthld = sp->pf_retrans;
		val.spt_pathmaxrxt = sp->pathmaxrxt;
		val.spt_pathcpthld = sp->ps_retrans;
	पूर्ण

out:
	अगर (put_user(len, optlen) || copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * SCTP_GET_ASSOC_STATS
 *
 * This option retrieves local per endpoपूर्णांक statistics. It is modeled
 * after OpenSolaris' implementation
 */
अटल पूर्णांक sctp_माला_लोockopt_assoc_stats(काष्ठा sock *sk, पूर्णांक len,
				       अक्षर __user *optval,
				       पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_stats sas;
	काष्ठा sctp_association *asoc = शून्य;

	/* User must provide at least the assoc id */
	अगर (len < माप(sctp_assoc_t))
		वापस -EINVAL;

	/* Allow the काष्ठा to grow and fill in as much as possible */
	len = min_t(माप_प्रकार, len, माप(sas));

	अगर (copy_from_user(&sas, optval, len))
		वापस -EFAULT;

	asoc = sctp_id2assoc(sk, sas.sas_assoc_id);
	अगर (!asoc)
		वापस -EINVAL;

	sas.sas_rtxchunks = asoc->stats.rtxchunks;
	sas.sas_gapcnt = asoc->stats.gapcnt;
	sas.sas_outofseqtsns = asoc->stats.outofseqtsns;
	sas.sas_osacks = asoc->stats.osacks;
	sas.sas_isacks = asoc->stats.isacks;
	sas.sas_octrlchunks = asoc->stats.octrlchunks;
	sas.sas_ictrlchunks = asoc->stats.ictrlchunks;
	sas.sas_oodchunks = asoc->stats.oodchunks;
	sas.sas_iodchunks = asoc->stats.iodchunks;
	sas.sas_ouodchunks = asoc->stats.ouodchunks;
	sas.sas_iuodchunks = asoc->stats.iuodchunks;
	sas.sas_idupchunks = asoc->stats.idupchunks;
	sas.sas_opackets = asoc->stats.opackets;
	sas.sas_ipackets = asoc->stats.ipackets;

	/* New high max rto observed, will वापस 0 अगर not a single
	 * RTO update took place. obs_rto_ipaddr will be bogus
	 * in such a हाल
	 */
	sas.sas_maxrto = asoc->stats.max_obs_rto;
	स_नकल(&sas.sas_obs_rto_ipaddr, &asoc->stats.obs_rto_ipaddr,
		माप(काष्ठा sockaddr_storage));

	/* Mark beginning of a new observation period */
	asoc->stats.max_obs_rto = asoc->rto_min;

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	pr_debug("%s: len:%d, assoc_id:%d\n", __func__, len, sas.sas_assoc_id);

	अगर (copy_to_user(optval, &sas, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_recvrcvinfo(काष्ठा sock *sk,	पूर्णांक len,
				       अक्षर __user *optval,
				       पूर्णांक __user *optlen)
अणु
	पूर्णांक val = 0;

	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;

	len = माप(पूर्णांक);
	अगर (sctp_sk(sk)->recvrcvinfo)
		val = 1;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_recvnxtinfo(काष्ठा sock *sk,	पूर्णांक len,
				       अक्षर __user *optval,
				       पूर्णांक __user *optlen)
अणु
	पूर्णांक val = 0;

	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;

	len = माप(पूर्णांक);
	अगर (sctp_sk(sk)->recvnxtinfo)
		val = 1;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_pr_supported(काष्ठा sock *sk, पूर्णांक len,
					अक्षर __user *optval,
					पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? asoc->peer.prsctp_capable
				  : sctp_sk(sk)->ep->prsctp_enable;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_शेष_prinfo(काष्ठा sock *sk, पूर्णांक len,
					  अक्षर __user *optval,
					  पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_शेष_prinfo info;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(info)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(info);
	अगर (copy_from_user(&info, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, info.pr_assoc_id);
	अगर (!asoc && info.pr_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (asoc) अणु
		info.pr_policy = SCTP_PR_POLICY(asoc->शेष_flags);
		info.pr_value = asoc->शेष_समयtolive;
	पूर्ण अन्यथा अणु
		काष्ठा sctp_sock *sp = sctp_sk(sk);

		info.pr_policy = SCTP_PR_POLICY(sp->शेष_flags);
		info.pr_value = sp->शेष_समयtolive;
	पूर्ण

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &info, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_pr_assocstatus(काष्ठा sock *sk, पूर्णांक len,
					  अक्षर __user *optval,
					  पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_prstatus params;
	काष्ठा sctp_association *asoc;
	पूर्णांक policy;
	पूर्णांक retval = -EINVAL;

	अगर (len < माप(params))
		जाओ out;

	len = माप(params);
	अगर (copy_from_user(&params, optval, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	policy = params.sprstat_policy;
	अगर (!policy || (policy & ~(SCTP_PR_SCTP_MASK | SCTP_PR_SCTP_ALL)) ||
	    ((policy & SCTP_PR_SCTP_ALL) && (policy & SCTP_PR_SCTP_MASK)))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.sprstat_assoc_id);
	अगर (!asoc)
		जाओ out;

	अगर (policy == SCTP_PR_SCTP_ALL) अणु
		params.sprstat_abanकरोned_unsent = 0;
		params.sprstat_abanकरोned_sent = 0;
		क्रम (policy = 0; policy <= SCTP_PR_INDEX(MAX); policy++) अणु
			params.sprstat_abanकरोned_unsent +=
				asoc->abanकरोned_unsent[policy];
			params.sprstat_abanकरोned_sent +=
				asoc->abanकरोned_sent[policy];
		पूर्ण
	पूर्ण अन्यथा अणु
		params.sprstat_abanकरोned_unsent =
			asoc->abanकरोned_unsent[__SCTP_PR_INDEX(policy)];
		params.sprstat_abanकरोned_sent =
			asoc->abanकरोned_sent[__SCTP_PR_INDEX(policy)];
	पूर्ण

	अगर (put_user(len, optlen)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (copy_to_user(optval, &params, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_pr_streamstatus(काष्ठा sock *sk, पूर्णांक len,
					   अक्षर __user *optval,
					   पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_stream_out_ext *streamoute;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_prstatus params;
	पूर्णांक retval = -EINVAL;
	पूर्णांक policy;

	अगर (len < माप(params))
		जाओ out;

	len = माप(params);
	अगर (copy_from_user(&params, optval, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	policy = params.sprstat_policy;
	अगर (!policy || (policy & ~(SCTP_PR_SCTP_MASK | SCTP_PR_SCTP_ALL)) ||
	    ((policy & SCTP_PR_SCTP_ALL) && (policy & SCTP_PR_SCTP_MASK)))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.sprstat_assoc_id);
	अगर (!asoc || params.sprstat_sid >= asoc->stream.outcnt)
		जाओ out;

	streamoute = SCTP_SO(&asoc->stream, params.sprstat_sid)->ext;
	अगर (!streamoute) अणु
		/* Not allocated yet, means all stats are 0 */
		params.sprstat_abanकरोned_unsent = 0;
		params.sprstat_abanकरोned_sent = 0;
		retval = 0;
		जाओ out;
	पूर्ण

	अगर (policy == SCTP_PR_SCTP_ALL) अणु
		params.sprstat_abanकरोned_unsent = 0;
		params.sprstat_abanकरोned_sent = 0;
		क्रम (policy = 0; policy <= SCTP_PR_INDEX(MAX); policy++) अणु
			params.sprstat_abanकरोned_unsent +=
				streamoute->abanकरोned_unsent[policy];
			params.sprstat_abanकरोned_sent +=
				streamoute->abanकरोned_sent[policy];
		पूर्ण
	पूर्ण अन्यथा अणु
		params.sprstat_abanकरोned_unsent =
			streamoute->abanकरोned_unsent[__SCTP_PR_INDEX(policy)];
		params.sprstat_abanकरोned_sent =
			streamoute->abanकरोned_sent[__SCTP_PR_INDEX(policy)];
	पूर्ण

	अगर (put_user(len, optlen) || copy_to_user(optval, &params, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_reconfig_supported(काष्ठा sock *sk, पूर्णांक len,
					      अक्षर __user *optval,
					      पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? asoc->peer.reconf_capable
				  : sctp_sk(sk)->ep->reconf_enable;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_enable_strreset(काष्ठा sock *sk, पूर्णांक len,
					   अक्षर __user *optval,
					   पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? asoc->strreset_enable
				  : sctp_sk(sk)->ep->strreset_enable;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_scheduler(काष्ठा sock *sk, पूर्णांक len,
				     अक्षर __user *optval,
				     पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? sctp_sched_get_sched(asoc)
				  : sctp_sk(sk)->शेष_ss;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_scheduler_value(काष्ठा sock *sk, पूर्णांक len,
					   अक्षर __user *optval,
					   पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_stream_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	retval = sctp_sched_get_value(asoc, params.stream_id,
				      &params.stream_value);
	अगर (retval)
		जाओ out;

	अगर (put_user(len, optlen)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (copy_to_user(optval, &params, len)) अणु
		retval = -EFAULT;
		जाओ out;
	पूर्ण

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_पूर्णांकerleaving_supported(काष्ठा sock *sk, पूर्णांक len,
						  अक्षर __user *optval,
						  पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? asoc->peer.पूर्णांकl_capable
				  : sctp_sk(sk)->ep->पूर्णांकl_enable;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_reuse_port(काष्ठा sock *sk, पूर्णांक len,
				      अक्षर __user *optval,
				      पूर्णांक __user *optlen)
अणु
	पूर्णांक val;

	अगर (len < माप(पूर्णांक))
		वापस -EINVAL;

	len = माप(पूर्णांक);
	val = sctp_sk(sk)->reuse;
	अगर (put_user(len, optlen))
		वापस -EFAULT;

	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_event(काष्ठा sock *sk, पूर्णांक len, अक्षर __user *optval,
				 पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_event param;
	__u16 subscribe;

	अगर (len < माप(param))
		वापस -EINVAL;

	len = माप(param);
	अगर (copy_from_user(&param, optval, len))
		वापस -EFAULT;

	अगर (param.se_type < SCTP_SN_TYPE_BASE ||
	    param.se_type > SCTP_SN_TYPE_MAX)
		वापस -EINVAL;

	asoc = sctp_id2assoc(sk, param.se_assoc_id);
	अगर (!asoc && param.se_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		वापस -EINVAL;

	subscribe = asoc ? asoc->subscribe : sctp_sk(sk)->subscribe;
	param.se_on = sctp_ulpevent_type_enabled(subscribe, param.se_type);

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	अगर (copy_to_user(optval, &param, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_asconf_supported(काष्ठा sock *sk, पूर्णांक len,
					    अक्षर __user *optval,
					    पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? asoc->peer.asconf_capable
				  : sctp_sk(sk)->ep->asconf_enable;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_auth_supported(काष्ठा sock *sk, पूर्णांक len,
					  अक्षर __user *optval,
					  पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? asoc->peer.auth_capable
				  : sctp_sk(sk)->ep->auth_enable;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_ecn_supported(काष्ठा sock *sk, पूर्णांक len,
					 अक्षर __user *optval,
					 पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? asoc->peer.ecn_capable
				  : sctp_sk(sk)->ep->ecn_enable;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_pf_expose(काष्ठा sock *sk, पूर्णांक len,
				     अक्षर __user *optval,
				     पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_assoc_value params;
	काष्ठा sctp_association *asoc;
	पूर्णांक retval = -EFAULT;

	अगर (len < माप(params)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	len = माप(params);
	अगर (copy_from_user(&params, optval, len))
		जाओ out;

	asoc = sctp_id2assoc(sk, params.assoc_id);
	अगर (!asoc && params.assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	params.assoc_value = asoc ? asoc->pf_expose
				  : sctp_sk(sk)->pf_expose;

	अगर (put_user(len, optlen))
		जाओ out;

	अगर (copy_to_user(optval, &params, len))
		जाओ out;

	retval = 0;

out:
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt_encap_port(काष्ठा sock *sk, पूर्णांक len,
				      अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_udpencaps encap;
	काष्ठा sctp_transport *t;
	__be16 encap_port;

	अगर (len < माप(encap))
		वापस -EINVAL;

	len = माप(encap);
	अगर (copy_from_user(&encap, optval, len))
		वापस -EFAULT;

	/* If an address other than INADDR_ANY is specअगरied, and
	 * no transport is found, then the request is invalid.
	 */
	अगर (!sctp_is_any(sk, (जोड़ sctp_addr *)&encap.sue_address)) अणु
		t = sctp_addr_id2transport(sk, &encap.sue_address,
					   encap.sue_assoc_id);
		अगर (!t) अणु
			pr_debug("%s: failed no transport\n", __func__);
			वापस -EINVAL;
		पूर्ण

		encap_port = t->encap_port;
		जाओ out;
	पूर्ण

	/* Get association, अगर assoc_id != SCTP_FUTURE_ASSOC and the
	 * socket is a one to many style socket, and an association
	 * was not found, then the id was invalid.
	 */
	asoc = sctp_id2assoc(sk, encap.sue_assoc_id);
	अगर (!asoc && encap.sue_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP)) अणु
		pr_debug("%s: failed no association\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (asoc) अणु
		encap_port = asoc->encap_port;
		जाओ out;
	पूर्ण

	encap_port = sctp_sk(sk)->encap_port;

out:
	encap.sue_port = (__क्रमce uपूर्णांक16_t)encap_port;
	अगर (copy_to_user(optval, &encap, len))
		वापस -EFAULT;

	अगर (put_user(len, optlen))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			   अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक retval = 0;
	पूर्णांक len;

	pr_debug("%s: sk:%p, optname:%d\n", __func__, sk, optname);

	/* I can hardly begin to describe how wrong this is.  This is
	 * so broken as to be worse than useless.  The API draft
	 * REALLY is NOT helpful here...  I am not convinced that the
	 * semantics of माला_लोockopt() with a level OTHER THAN SOL_SCTP
	 * are at all well-founded.
	 */
	अगर (level != SOL_SCTP) अणु
		काष्ठा sctp_af *af = sctp_sk(sk)->pf->af;

		retval = af->माला_लोockopt(sk, level, optname, optval, optlen);
		वापस retval;
	पूर्ण

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	अगर (len < 0)
		वापस -EINVAL;

	lock_sock(sk);

	चयन (optname) अणु
	हाल SCTP_STATUS:
		retval = sctp_माला_लोockopt_sctp_status(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_DISABLE_FRAGMENTS:
		retval = sctp_माला_लोockopt_disable_fragments(sk, len, optval,
							   optlen);
		अवरोध;
	हाल SCTP_EVENTS:
		retval = sctp_माला_लोockopt_events(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_AUTOCLOSE:
		retval = sctp_माला_लोockopt_स्वतःबंद(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_SOCKOPT_PEELOFF:
		retval = sctp_माला_लोockopt_peeloff(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_SOCKOPT_PEELOFF_FLAGS:
		retval = sctp_माला_लोockopt_peeloff_flags(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_PEER_ADDR_PARAMS:
		retval = sctp_माला_लोockopt_peer_addr_params(sk, len, optval,
							  optlen);
		अवरोध;
	हाल SCTP_DELAYED_SACK:
		retval = sctp_माला_लोockopt_delayed_ack(sk, len, optval,
							  optlen);
		अवरोध;
	हाल SCTP_INITMSG:
		retval = sctp_माला_लोockopt_iniपंचांगsg(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_GET_PEER_ADDRS:
		retval = sctp_माला_लोockopt_peer_addrs(sk, len, optval,
						    optlen);
		अवरोध;
	हाल SCTP_GET_LOCAL_ADDRS:
		retval = sctp_माला_लोockopt_local_addrs(sk, len, optval,
						     optlen);
		अवरोध;
	हाल SCTP_SOCKOPT_CONNECTX3:
		retval = sctp_माला_लोockopt_connectx3(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_DEFAULT_SEND_PARAM:
		retval = sctp_माला_लोockopt_शेष_send_param(sk, len,
							    optval, optlen);
		अवरोध;
	हाल SCTP_DEFAULT_SNDINFO:
		retval = sctp_माला_लोockopt_शेष_sndinfo(sk, len,
							 optval, optlen);
		अवरोध;
	हाल SCTP_PRIMARY_ADDR:
		retval = sctp_माला_लोockopt_primary_addr(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_NODELAY:
		retval = sctp_माला_लोockopt_nodelay(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_RTOINFO:
		retval = sctp_माला_लोockopt_rtoinfo(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_ASSOCINFO:
		retval = sctp_माला_लोockopt_associnfo(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_I_WANT_MAPPED_V4_ADDR:
		retval = sctp_माला_लोockopt_mappedv4(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_MAXSEG:
		retval = sctp_माला_लोockopt_maxseg(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_GET_PEER_ADDR_INFO:
		retval = sctp_माला_लोockopt_peer_addr_info(sk, len, optval,
							optlen);
		अवरोध;
	हाल SCTP_ADAPTATION_LAYER:
		retval = sctp_माला_लोockopt_adaptation_layer(sk, len, optval,
							optlen);
		अवरोध;
	हाल SCTP_CONTEXT:
		retval = sctp_माला_लोockopt_context(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_FRAGMENT_INTERLEAVE:
		retval = sctp_माला_लोockopt_fragment_पूर्णांकerleave(sk, len, optval,
							     optlen);
		अवरोध;
	हाल SCTP_PARTIAL_DELIVERY_POINT:
		retval = sctp_माला_लोockopt_partial_delivery_poपूर्णांक(sk, len, optval,
								optlen);
		अवरोध;
	हाल SCTP_MAX_BURST:
		retval = sctp_माला_लोockopt_maxburst(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_AUTH_KEY:
	हाल SCTP_AUTH_CHUNK:
	हाल SCTP_AUTH_DELETE_KEY:
	हाल SCTP_AUTH_DEACTIVATE_KEY:
		retval = -EOPNOTSUPP;
		अवरोध;
	हाल SCTP_HMAC_IDENT:
		retval = sctp_माला_लोockopt_hmac_ident(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_AUTH_ACTIVE_KEY:
		retval = sctp_माला_लोockopt_active_key(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_PEER_AUTH_CHUNKS:
		retval = sctp_माला_लोockopt_peer_auth_chunks(sk, len, optval,
							optlen);
		अवरोध;
	हाल SCTP_LOCAL_AUTH_CHUNKS:
		retval = sctp_माला_लोockopt_local_auth_chunks(sk, len, optval,
							optlen);
		अवरोध;
	हाल SCTP_GET_ASSOC_NUMBER:
		retval = sctp_माला_लोockopt_assoc_number(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_GET_ASSOC_ID_LIST:
		retval = sctp_माला_लोockopt_assoc_ids(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_AUTO_ASCONF:
		retval = sctp_माला_लोockopt_स्वतः_asconf(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_PEER_ADDR_THLDS:
		retval = sctp_माला_लोockopt_paddr_thresholds(sk, optval, len,
							  optlen, false);
		अवरोध;
	हाल SCTP_PEER_ADDR_THLDS_V2:
		retval = sctp_माला_लोockopt_paddr_thresholds(sk, optval, len,
							  optlen, true);
		अवरोध;
	हाल SCTP_GET_ASSOC_STATS:
		retval = sctp_माला_लोockopt_assoc_stats(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_RECVRCVINFO:
		retval = sctp_माला_लोockopt_recvrcvinfo(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_RECVNXTINFO:
		retval = sctp_माला_लोockopt_recvnxtinfo(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_PR_SUPPORTED:
		retval = sctp_माला_लोockopt_pr_supported(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_DEFAULT_PRINFO:
		retval = sctp_माला_लोockopt_शेष_prinfo(sk, len, optval,
							optlen);
		अवरोध;
	हाल SCTP_PR_ASSOC_STATUS:
		retval = sctp_माला_लोockopt_pr_assocstatus(sk, len, optval,
							optlen);
		अवरोध;
	हाल SCTP_PR_STREAM_STATUS:
		retval = sctp_माला_लोockopt_pr_streamstatus(sk, len, optval,
							 optlen);
		अवरोध;
	हाल SCTP_RECONFIG_SUPPORTED:
		retval = sctp_माला_लोockopt_reconfig_supported(sk, len, optval,
							    optlen);
		अवरोध;
	हाल SCTP_ENABLE_STREAM_RESET:
		retval = sctp_माला_लोockopt_enable_strreset(sk, len, optval,
							 optlen);
		अवरोध;
	हाल SCTP_STREAM_SCHEDULER:
		retval = sctp_माला_लोockopt_scheduler(sk, len, optval,
						   optlen);
		अवरोध;
	हाल SCTP_STREAM_SCHEDULER_VALUE:
		retval = sctp_माला_लोockopt_scheduler_value(sk, len, optval,
							 optlen);
		अवरोध;
	हाल SCTP_INTERLEAVING_SUPPORTED:
		retval = sctp_माला_लोockopt_पूर्णांकerleaving_supported(sk, len, optval,
								optlen);
		अवरोध;
	हाल SCTP_REUSE_PORT:
		retval = sctp_माला_लोockopt_reuse_port(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_EVENT:
		retval = sctp_माला_लोockopt_event(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_ASCONF_SUPPORTED:
		retval = sctp_माला_लोockopt_asconf_supported(sk, len, optval,
							  optlen);
		अवरोध;
	हाल SCTP_AUTH_SUPPORTED:
		retval = sctp_माला_लोockopt_auth_supported(sk, len, optval,
							optlen);
		अवरोध;
	हाल SCTP_ECN_SUPPORTED:
		retval = sctp_माला_लोockopt_ecn_supported(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_EXPOSE_POTENTIALLY_FAILED_STATE:
		retval = sctp_माला_लोockopt_pf_expose(sk, len, optval, optlen);
		अवरोध;
	हाल SCTP_REMOTE_UDP_ENCAPS_PORT:
		retval = sctp_माला_लोockopt_encap_port(sk, len, optval, optlen);
		अवरोध;
	शेष:
		retval = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस retval;
पूर्ण

अटल पूर्णांक sctp_hash(काष्ठा sock *sk)
अणु
	/* STUB */
	वापस 0;
पूर्ण

अटल व्योम sctp_unhash(काष्ठा sock *sk)
अणु
	/* STUB */
पूर्ण

/* Check अगर port is acceptable.  Possibly find first available port.
 *
 * The port hash table (contained in the 'global' SCTP protocol storage
 * वापसed by काष्ठा sctp_protocol *sctp_get_protocol()). The hash
 * table is an array of 4096 lists (sctp_bind_hashbucket). Each
 * list (the list number is the port number hashed out, so as you
 * would expect from a hash function, all the ports in a given list have
 * such a number that hashes out to the same list number; you were
 * expecting that, right?); so each list has a set of ports, with a
 * link to the socket (काष्ठा sock) that uses it, the port number and
 * a fastreuse flag (FIXME: NPI ipg).
 */
अटल काष्ठा sctp_bind_bucket *sctp_bucket_create(
	काष्ठा sctp_bind_hashbucket *head, काष्ठा net *, अचिन्हित लघु snum);

अटल पूर्णांक sctp_get_port_local(काष्ठा sock *sk, जोड़ sctp_addr *addr)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	bool reuse = (sk->sk_reuse || sp->reuse);
	काष्ठा sctp_bind_hashbucket *head; /* hash list */
	काष्ठा net *net = sock_net(sk);
	kuid_t uid = sock_i_uid(sk);
	काष्ठा sctp_bind_bucket *pp;
	अचिन्हित लघु snum;
	पूर्णांक ret;

	snum = ntohs(addr->v4.sin_port);

	pr_debug("%s: begins, snum:%d\n", __func__, snum);

	अगर (snum == 0) अणु
		/* Search क्रम an available port. */
		पूर्णांक low, high, reमुख्यing, index;
		अचिन्हित पूर्णांक rover;

		inet_get_local_port_range(net, &low, &high);
		reमुख्यing = (high - low) + 1;
		rover = pअक्रमom_u32() % reमुख्यing + low;

		करो अणु
			rover++;
			अगर ((rover < low) || (rover > high))
				rover = low;
			अगर (inet_is_local_reserved_port(net, rover))
				जारी;
			index = sctp_phashfn(net, rover);
			head = &sctp_port_hashtable[index];
			spin_lock_bh(&head->lock);
			sctp_क्रम_each_hentry(pp, &head->chain)
				अगर ((pp->port == rover) &&
				    net_eq(net, pp->net))
					जाओ next;
			अवरोध;
		next:
			spin_unlock_bh(&head->lock);
			cond_resched();
		पूर्ण जबतक (--reमुख्यing > 0);

		/* Exhausted local port range during search? */
		ret = 1;
		अगर (reमुख्यing <= 0)
			वापस ret;

		/* OK, here is the one we will use.  HEAD (the port
		 * hash table list entry) is non-शून्य and we hold it's
		 * mutex.
		 */
		snum = rover;
	पूर्ण अन्यथा अणु
		/* We are given an specअगरic port number; we verअगरy
		 * that it is not being used. If it is used, we will
		 * exahust the search in the hash list corresponding
		 * to the port number (snum) - we detect that with the
		 * port iterator, pp being शून्य.
		 */
		head = &sctp_port_hashtable[sctp_phashfn(net, snum)];
		spin_lock_bh(&head->lock);
		sctp_क्रम_each_hentry(pp, &head->chain) अणु
			अगर ((pp->port == snum) && net_eq(pp->net, net))
				जाओ pp_found;
		पूर्ण
	पूर्ण
	pp = शून्य;
	जाओ pp_not_found;
pp_found:
	अगर (!hlist_empty(&pp->owner)) अणु
		/* We had a port hash table hit - there is an
		 * available port (pp != शून्य) and it is being
		 * used by other socket (pp->owner not empty); that other
		 * socket is going to be sk2.
		 */
		काष्ठा sock *sk2;

		pr_debug("%s: found a possible match\n", __func__);

		अगर ((pp->fastreuse && reuse &&
		     sk->sk_state != SCTP_SS_LISTENING) ||
		    (pp->fastreuseport && sk->sk_reuseport &&
		     uid_eq(pp->fastuid, uid)))
			जाओ success;

		/* Run through the list of sockets bound to the port
		 * (pp->port) [via the poपूर्णांकers bind_next and
		 * bind_pprev in the काष्ठा sock *sk2 (pp->sk)]. On each one,
		 * we get the endpoपूर्णांक they describe and run through
		 * the endpoपूर्णांक's list of IP (v4 or v6) addresses,
		 * comparing each of the addresses with the address of
		 * the socket sk. If we find a match, then that means
		 * that this port/socket (sk) combination are alपढ़ोy
		 * in an endpoपूर्णांक.
		 */
		sk_क्रम_each_bound(sk2, &pp->owner) अणु
			काष्ठा sctp_sock *sp2 = sctp_sk(sk2);
			काष्ठा sctp_endpoपूर्णांक *ep2 = sp2->ep;

			अगर (sk == sk2 ||
			    (reuse && (sk2->sk_reuse || sp2->reuse) &&
			     sk2->sk_state != SCTP_SS_LISTENING) ||
			    (sk->sk_reuseport && sk2->sk_reuseport &&
			     uid_eq(uid, sock_i_uid(sk2))))
				जारी;

			अगर (sctp_bind_addr_conflict(&ep2->base.bind_addr,
						    addr, sp2, sp)) अणु
				ret = 1;
				जाओ fail_unlock;
			पूर्ण
		पूर्ण

		pr_debug("%s: found a match\n", __func__);
	पूर्ण
pp_not_found:
	/* If there was a hash table miss, create a new port.  */
	ret = 1;
	अगर (!pp && !(pp = sctp_bucket_create(head, net, snum)))
		जाओ fail_unlock;

	/* In either हाल (hit or miss), make sure fastreuse is 1 only
	 * अगर sk->sk_reuse is too (that is, अगर the caller requested
	 * SO_REUSEADDR on this socket -sk-).
	 */
	अगर (hlist_empty(&pp->owner)) अणु
		अगर (reuse && sk->sk_state != SCTP_SS_LISTENING)
			pp->fastreuse = 1;
		अन्यथा
			pp->fastreuse = 0;

		अगर (sk->sk_reuseport) अणु
			pp->fastreuseport = 1;
			pp->fastuid = uid;
		पूर्ण अन्यथा अणु
			pp->fastreuseport = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pp->fastreuse &&
		    (!reuse || sk->sk_state == SCTP_SS_LISTENING))
			pp->fastreuse = 0;

		अगर (pp->fastreuseport &&
		    (!sk->sk_reuseport || !uid_eq(pp->fastuid, uid)))
			pp->fastreuseport = 0;
	पूर्ण

	/* We are set, so fill up all the data in the hash table
	 * entry, tie the socket list inक्रमmation with the rest of the
	 * sockets FIXME: Blurry, NPI (ipg).
	 */
success:
	अगर (!sp->bind_hash) अणु
		inet_sk(sk)->inet_num = snum;
		sk_add_bind_node(sk, &pp->owner);
		sp->bind_hash = pp;
	पूर्ण
	ret = 0;

fail_unlock:
	spin_unlock_bh(&head->lock);
	वापस ret;
पूर्ण

/* Assign a 'snum' port to the socket.  If snum == 0, an ephemeral
 * port is requested.
 */
अटल पूर्णांक sctp_get_port(काष्ठा sock *sk, अचिन्हित लघु snum)
अणु
	जोड़ sctp_addr addr;
	काष्ठा sctp_af *af = sctp_sk(sk)->pf->af;

	/* Set up a dummy address काष्ठा from the sk. */
	af->from_sk(&addr, sk);
	addr.v4.sin_port = htons(snum);

	/* Note: sk->sk_num माला_लो filled in अगर ephemeral port request. */
	वापस sctp_get_port_local(sk, &addr);
पूर्ण

/*
 *  Move a socket to LISTENING state.
 */
अटल पूर्णांक sctp_listen_start(काष्ठा sock *sk, पूर्णांक backlog)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_endpoपूर्णांक *ep = sp->ep;
	काष्ठा crypto_shash *tfm = शून्य;
	अक्षर alg[32];

	/* Allocate HMAC क्रम generating cookie. */
	अगर (!sp->hmac && sp->sctp_hmac_alg) अणु
		प्र_लिखो(alg, "hmac(%s)", sp->sctp_hmac_alg);
		tfm = crypto_alloc_shash(alg, 0, 0);
		अगर (IS_ERR(tfm)) अणु
			net_info_ratelimited("failed to load transform for %s: %ld\n",
					     sp->sctp_hmac_alg, PTR_ERR(tfm));
			वापस -ENOSYS;
		पूर्ण
		sctp_sk(sk)->hmac = tfm;
	पूर्ण

	/*
	 * If a bind() or sctp_bindx() is not called prior to a listen()
	 * call that allows new associations to be accepted, the प्रणाली
	 * picks an ephemeral port and will choose an address set equivalent
	 * to binding with a wildcard address.
	 *
	 * This is not currently spelled out in the SCTP sockets
	 * extensions draft, but follows the practice as seen in TCP
	 * sockets.
	 *
	 */
	inet_sk_set_state(sk, SCTP_SS_LISTENING);
	अगर (!ep->base.bind_addr.port) अणु
		अगर (sctp_स्वतःbind(sk))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		अगर (sctp_get_port(sk, inet_sk(sk)->inet_num)) अणु
			inet_sk_set_state(sk, SCTP_SS_CLOSED);
			वापस -EADDRINUSE;
		पूर्ण
	पूर्ण

	WRITE_ONCE(sk->sk_max_ack_backlog, backlog);
	वापस sctp_hash_endpoपूर्णांक(ep);
पूर्ण

/*
 * 4.1.3 / 5.1.3 listen()
 *
 *   By शेष, new associations are not accepted क्रम UDP style sockets.
 *   An application uses listen() to mark a socket as being able to
 *   accept new associations.
 *
 *   On TCP style sockets, applications use listen() to पढ़ोy the SCTP
 *   endpoपूर्णांक क्रम accepting inbound associations.
 *
 *   On both types of endpoपूर्णांकs a backlog of '0' disables listening.
 *
 *  Move a socket to LISTENING state.
 */
पूर्णांक sctp_inet_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sctp_endpoपूर्णांक *ep = sctp_sk(sk)->ep;
	पूर्णांक err = -EINVAL;

	अगर (unlikely(backlog < 0))
		वापस err;

	lock_sock(sk);

	/* Peeled-off sockets are not allowed to listen().  */
	अगर (sctp_style(sk, UDP_HIGH_BANDWIDTH))
		जाओ out;

	अगर (sock->state != SS_UNCONNECTED)
		जाओ out;

	अगर (!sctp_sstate(sk, LISTENING) && !sctp_sstate(sk, CLOSED))
		जाओ out;

	/* If backlog is zero, disable listening. */
	अगर (!backlog) अणु
		अगर (sctp_sstate(sk, CLOSED))
			जाओ out;

		err = 0;
		sctp_unhash_endpoपूर्णांक(ep);
		sk->sk_state = SCTP_SS_CLOSED;
		अगर (sk->sk_reuse || sctp_sk(sk)->reuse)
			sctp_sk(sk)->bind_hash->fastreuse = 1;
		जाओ out;
	पूर्ण

	/* If we are alपढ़ोy listening, just update the backlog */
	अगर (sctp_sstate(sk, LISTENING))
		WRITE_ONCE(sk->sk_max_ack_backlog, backlog);
	अन्यथा अणु
		err = sctp_listen_start(sk, backlog);
		अगर (err)
			जाओ out;
	पूर्ण

	err = 0;
out:
	release_sock(sk);
	वापस err;
पूर्ण

/*
 * This function is करोne by modeling the current datagram_poll() and the
 * tcp_poll().  Note that, based on these implementations, we करोn't
 * lock the socket in this function, even though it seems that,
 * ideally, locking or some other mechanisms can be used to ensure
 * the पूर्णांकegrity of the counters (sndbuf and wmem_alloc) used
 * in this place.  We assume that we करोn't need locks either until proven
 * otherwise.
 *
 * Another thing to note is that we include the Async I/O support
 * here, again, by modeling the current TCP/UDP code.  We करोn't have
 * a good way to test with it yet.
 */
__poll_t sctp_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	__poll_t mask;

	poll_रुको(file, sk_sleep(sk), रुको);

	sock_rps_record_flow(sk);

	/* A TCP-style listening socket becomes पढ़ोable when the accept queue
	 * is not empty.
	 */
	अगर (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING))
		वापस (!list_empty(&sp->ep->asocs)) ?
			(EPOLLIN | EPOLLRDNORM) : 0;

	mask = 0;

	/* Is there any exceptional events?  */
	अगर (sk->sk_err || !skb_queue_empty_lockless(&sk->sk_error_queue))
		mask |= EPOLLERR |
			(sock_flag(sk, SOCK_SELECT_ERR_QUEUE) ? EPOLLPRI : 0);
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		mask |= EPOLLHUP;

	/* Is it पढ़ोable?  Reconsider this code with TCP-style support.  */
	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* The association is either gone or not पढ़ोy.  */
	अगर (!sctp_style(sk, UDP) && sctp_sstate(sk, CLOSED))
		वापस mask;

	/* Is it writable?  */
	अगर (sctp_ग_लिखोable(sk)) अणु
		mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण अन्यथा अणु
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		/*
		 * Since the socket is not locked, the buffer
		 * might be made available after the ग_लिखोable check and
		 * beक्रमe the bit is set.  This could cause a lost I/O
		 * संकेत.  tcp_poll() has a race अवरोधer क्रम this race
		 * condition.  Based on their implementation, we put
		 * in the following code to cover it as well.
		 */
		अगर (sctp_ग_लिखोable(sk))
			mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण
	वापस mask;
पूर्ण

/********************************************************************
 * 2nd Level Abstractions
 ********************************************************************/

अटल काष्ठा sctp_bind_bucket *sctp_bucket_create(
	काष्ठा sctp_bind_hashbucket *head, काष्ठा net *net, अचिन्हित लघु snum)
अणु
	काष्ठा sctp_bind_bucket *pp;

	pp = kmem_cache_alloc(sctp_bucket_cachep, GFP_ATOMIC);
	अगर (pp) अणु
		SCTP_DBG_OBJCNT_INC(bind_bucket);
		pp->port = snum;
		pp->fastreuse = 0;
		INIT_HLIST_HEAD(&pp->owner);
		pp->net = net;
		hlist_add_head(&pp->node, &head->chain);
	पूर्ण
	वापस pp;
पूर्ण

/* Caller must hold hashbucket lock क्रम this tb with local BH disabled */
अटल व्योम sctp_bucket_destroy(काष्ठा sctp_bind_bucket *pp)
अणु
	अगर (pp && hlist_empty(&pp->owner)) अणु
		__hlist_del(&pp->node);
		kmem_cache_मुक्त(sctp_bucket_cachep, pp);
		SCTP_DBG_OBJCNT_DEC(bind_bucket);
	पूर्ण
पूर्ण

/* Release this socket's reference to a local port.  */
अटल अंतरभूत व्योम __sctp_put_port(काष्ठा sock *sk)
अणु
	काष्ठा sctp_bind_hashbucket *head =
		&sctp_port_hashtable[sctp_phashfn(sock_net(sk),
						  inet_sk(sk)->inet_num)];
	काष्ठा sctp_bind_bucket *pp;

	spin_lock(&head->lock);
	pp = sctp_sk(sk)->bind_hash;
	__sk_del_bind_node(sk);
	sctp_sk(sk)->bind_hash = शून्य;
	inet_sk(sk)->inet_num = 0;
	sctp_bucket_destroy(pp);
	spin_unlock(&head->lock);
पूर्ण

व्योम sctp_put_port(काष्ठा sock *sk)
अणु
	local_bh_disable();
	__sctp_put_port(sk);
	local_bh_enable();
पूर्ण

/*
 * The प्रणाली picks an ephemeral port and choose an address set equivalent
 * to binding with a wildcard address.
 * One of those addresses will be the primary address क्रम the association.
 * This स्वतःmatically enables the multihoming capability of SCTP.
 */
अटल पूर्णांक sctp_स्वतःbind(काष्ठा sock *sk)
अणु
	जोड़ sctp_addr स्वतःaddr;
	काष्ठा sctp_af *af;
	__be16 port;

	/* Initialize a local sockaddr काष्ठाure to INADDR_ANY. */
	af = sctp_sk(sk)->pf->af;

	port = htons(inet_sk(sk)->inet_num);
	af->inaddr_any(&स्वतःaddr, port);

	वापस sctp_करो_bind(sk, &स्वतःaddr, af->sockaddr_len);
पूर्ण

/* Parse out IPPROTO_SCTP CMSG headers.  Perक्रमm only minimal validation.
 *
 * From RFC 2292
 * 4.2 The cmsghdr Structure *
 *
 * When ancillary data is sent or received, any number of ancillary data
 * objects can be specअगरied by the msg_control and msg_controllen members of
 * the msghdr काष्ठाure, because each object is preceded by
 * a cmsghdr काष्ठाure defining the object's length (the cmsg_len member).
 * Historically Berkeley-derived implementations have passed only one object
 * at a समय, but this API allows multiple objects to be
 * passed in a single call to sendmsg() or recvmsg(). The following example
 * shows two ancillary data objects in a control buffer.
 *
 *   |<--------------------------- msg_controllen -------------------------->|
 *   |                                                                       |
 *
 *   |<----- ancillary data object ----->|<----- ancillary data object ----->|
 *
 *   |<---------- CMSG_SPACE() --------->|<---------- CMSG_SPACE() --------->|
 *   |                                   |                                   |
 *
 *   |<---------- cmsg_len ---------->|  |<--------- cmsg_len ----------->|  |
 *
 *   |<--------- CMSG_LEN() --------->|  |<-------- CMSG_LEN() ---------->|  |
 *   |                                |  |                                |  |
 *
 *   +-----+-----+-----+--+-----------+--+-----+-----+-----+--+-----------+--+
 *   |cmsg_|cmsg_|cmsg_|XX|           |XX|cmsg_|cmsg_|cmsg_|XX|           |XX|
 *
 *   |len  |level|type |XX|cmsg_data[]|XX|len  |level|type |XX|cmsg_data[]|XX|
 *
 *   +-----+-----+-----+--+-----------+--+-----+-----+-----+--+-----------+--+
 *    ^
 *    |
 *
 * msg_control
 * poपूर्णांकs here
 */
अटल पूर्णांक sctp_msghdr_parse(स्थिर काष्ठा msghdr *msg, काष्ठा sctp_cmsgs *cmsgs)
अणु
	काष्ठा msghdr *my_msg = (काष्ठा msghdr *)msg;
	काष्ठा cmsghdr *cmsg;

	क्रम_each_cmsghdr(cmsg, my_msg) अणु
		अगर (!CMSG_OK(my_msg, cmsg))
			वापस -EINVAL;

		/* Should we parse this header or ignore?  */
		अगर (cmsg->cmsg_level != IPPROTO_SCTP)
			जारी;

		/* Strictly check lengths following example in SCM code.  */
		चयन (cmsg->cmsg_type) अणु
		हाल SCTP_INIT:
			/* SCTP Socket API Extension
			 * 5.3.1 SCTP Initiation Structure (SCTP_INIT)
			 *
			 * This cmsghdr काष्ठाure provides inक्रमmation क्रम
			 * initializing new SCTP associations with sendmsg().
			 * The SCTP_INITMSG socket option uses this same data
			 * काष्ठाure.  This काष्ठाure is not used क्रम
			 * recvmsg().
			 *
			 * cmsg_level    cmsg_type      cmsg_data[]
			 * ------------  ------------   ----------------------
			 * IPPROTO_SCTP  SCTP_INIT      काष्ठा sctp_iniपंचांगsg
			 */
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(काष्ठा sctp_iniपंचांगsg)))
				वापस -EINVAL;

			cmsgs->init = CMSG_DATA(cmsg);
			अवरोध;

		हाल SCTP_SNDRCV:
			/* SCTP Socket API Extension
			 * 5.3.2 SCTP Header Inक्रमmation Structure(SCTP_SNDRCV)
			 *
			 * This cmsghdr काष्ठाure specअगरies SCTP options क्रम
			 * sendmsg() and describes SCTP header inक्रमmation
			 * about a received message through recvmsg().
			 *
			 * cmsg_level    cmsg_type      cmsg_data[]
			 * ------------  ------------   ----------------------
			 * IPPROTO_SCTP  SCTP_SNDRCV    काष्ठा sctp_sndrcvinfo
			 */
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(काष्ठा sctp_sndrcvinfo)))
				वापस -EINVAL;

			cmsgs->srinfo = CMSG_DATA(cmsg);

			अगर (cmsgs->srinfo->sinfo_flags &
			    ~(SCTP_UNORDERED | SCTP_ADDR_OVER |
			      SCTP_SACK_IMMEDIATELY | SCTP_SENDALL |
			      SCTP_PR_SCTP_MASK | SCTP_ABORT | SCTP_खातापूर्ण))
				वापस -EINVAL;
			अवरोध;

		हाल SCTP_SNDINFO:
			/* SCTP Socket API Extension
			 * 5.3.4 SCTP Send Inक्रमmation Structure (SCTP_SNDINFO)
			 *
			 * This cmsghdr काष्ठाure specअगरies SCTP options क्रम
			 * sendmsg(). This काष्ठाure and SCTP_RCVINFO replaces
			 * SCTP_SNDRCV which has been deprecated.
			 *
			 * cmsg_level    cmsg_type      cmsg_data[]
			 * ------------  ------------   ---------------------
			 * IPPROTO_SCTP  SCTP_SNDINFO    काष्ठा sctp_sndinfo
			 */
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(काष्ठा sctp_sndinfo)))
				वापस -EINVAL;

			cmsgs->sinfo = CMSG_DATA(cmsg);

			अगर (cmsgs->sinfo->snd_flags &
			    ~(SCTP_UNORDERED | SCTP_ADDR_OVER |
			      SCTP_SACK_IMMEDIATELY | SCTP_SENDALL |
			      SCTP_PR_SCTP_MASK | SCTP_ABORT | SCTP_खातापूर्ण))
				वापस -EINVAL;
			अवरोध;
		हाल SCTP_PRINFO:
			/* SCTP Socket API Extension
			 * 5.3.7 SCTP PR-SCTP Inक्रमmation Structure (SCTP_PRINFO)
			 *
			 * This cmsghdr काष्ठाure specअगरies SCTP options क्रम sendmsg().
			 *
			 * cmsg_level    cmsg_type      cmsg_data[]
			 * ------------  ------------   ---------------------
			 * IPPROTO_SCTP  SCTP_PRINFO    काष्ठा sctp_prinfo
			 */
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(काष्ठा sctp_prinfo)))
				वापस -EINVAL;

			cmsgs->prinfo = CMSG_DATA(cmsg);
			अगर (cmsgs->prinfo->pr_policy & ~SCTP_PR_SCTP_MASK)
				वापस -EINVAL;

			अगर (cmsgs->prinfo->pr_policy == SCTP_PR_SCTP_NONE)
				cmsgs->prinfo->pr_value = 0;
			अवरोध;
		हाल SCTP_AUTHINFO:
			/* SCTP Socket API Extension
			 * 5.3.8 SCTP AUTH Inक्रमmation Structure (SCTP_AUTHINFO)
			 *
			 * This cmsghdr काष्ठाure specअगरies SCTP options क्रम sendmsg().
			 *
			 * cmsg_level    cmsg_type      cmsg_data[]
			 * ------------  ------------   ---------------------
			 * IPPROTO_SCTP  SCTP_AUTHINFO  काष्ठा sctp_authinfo
			 */
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(काष्ठा sctp_authinfo)))
				वापस -EINVAL;

			cmsgs->authinfo = CMSG_DATA(cmsg);
			अवरोध;
		हाल SCTP_DSTADDRV4:
		हाल SCTP_DSTADDRV6:
			/* SCTP Socket API Extension
			 * 5.3.9/10 SCTP Destination IPv4/6 Address Structure (SCTP_DSTADDRV4/6)
			 *
			 * This cmsghdr काष्ठाure specअगरies SCTP options क्रम sendmsg().
			 *
			 * cmsg_level    cmsg_type         cmsg_data[]
			 * ------------  ------------   ---------------------
			 * IPPROTO_SCTP  SCTP_DSTADDRV4 काष्ठा in_addr
			 * ------------  ------------   ---------------------
			 * IPPROTO_SCTP  SCTP_DSTADDRV6 काष्ठा in6_addr
			 */
			cmsgs->addrs_msg = my_msg;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wait क्रम a packet..
 * Note: This function is the same function as in core/datagram.c
 * with a few modअगरications to make lksctp work.
 */
अटल पूर्णांक sctp_रुको_क्रम_packet(काष्ठा sock *sk, पूर्णांक *err, दीर्घ *समयo_p)
अणु
	पूर्णांक error;
	DEFINE_WAIT(रुको);

	prepare_to_रुको_exclusive(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);

	/* Socket errors? */
	error = sock_error(sk);
	अगर (error)
		जाओ out;

	अगर (!skb_queue_empty(&sk->sk_receive_queue))
		जाओ पढ़ोy;

	/* Socket shut करोwn?  */
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		जाओ out;

	/* Sequenced packets can come disconnected.  If so we report the
	 * problem.
	 */
	error = -ENOTCONN;

	/* Is there a good reason to think that we may receive some data?  */
	अगर (list_empty(&sctp_sk(sk)->ep->asocs) && !sctp_sstate(sk, LISTENING))
		जाओ out;

	/* Handle संकेतs.  */
	अगर (संकेत_pending(current))
		जाओ पूर्णांकerrupted;

	/* Let another process have a go.  Since we are going to sleep
	 * anyway.  Note: This may cause odd behaviors अगर the message
	 * करोes not fit in the user's buffer, but this seems to be the
	 * only way to honor MSG_DONTWAIT realistically.
	 */
	release_sock(sk);
	*समयo_p = schedule_समयout(*समयo_p);
	lock_sock(sk);

पढ़ोy:
	finish_रुको(sk_sleep(sk), &रुको);
	वापस 0;

पूर्णांकerrupted:
	error = sock_पूर्णांकr_त्रुटि_सं(*समयo_p);

out:
	finish_रुको(sk_sleep(sk), &रुको);
	*err = error;
	वापस error;
पूर्ण

/* Receive a datagram.
 * Note: This is pretty much the same routine as in core/datagram.c
 * with a few changes to make lksctp work.
 */
काष्ठा sk_buff *sctp_skb_recv_datagram(काष्ठा sock *sk, पूर्णांक flags,
				       पूर्णांक noblock, पूर्णांक *err)
अणु
	पूर्णांक error;
	काष्ठा sk_buff *skb;
	दीर्घ समयo;

	समयo = sock_rcvसमयo(sk, noblock);

	pr_debug("%s: timeo:%ld, max:%ld\n", __func__, समयo,
		 MAX_SCHEDULE_TIMEOUT);

	करो अणु
		/* Again only user level code calls this function,
		 * so nothing पूर्णांकerrupt level
		 * will suddenly eat the receive_queue.
		 *
		 *  Look at current nfs client by the way...
		 *  However, this function was correct in any हाल. 8)
		 */
		अगर (flags & MSG_PEEK) अणु
			skb = skb_peek(&sk->sk_receive_queue);
			अगर (skb)
				refcount_inc(&skb->users);
		पूर्ण अन्यथा अणु
			skb = __skb_dequeue(&sk->sk_receive_queue);
		पूर्ण

		अगर (skb)
			वापस skb;

		/* Caller is allowed not to check sk->sk_err beक्रमe calling. */
		error = sock_error(sk);
		अगर (error)
			जाओ no_packet;

		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			अवरोध;

		अगर (sk_can_busy_loop(sk)) अणु
			sk_busy_loop(sk, noblock);

			अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
				जारी;
		पूर्ण

		/* User करोesn't want to रुको.  */
		error = -EAGAIN;
		अगर (!समयo)
			जाओ no_packet;
	पूर्ण जबतक (sctp_रुको_क्रम_packet(sk, err, &समयo) == 0);

	वापस शून्य;

no_packet:
	*err = error;
	वापस शून्य;
पूर्ण

/* If sndbuf has changed, wake up per association sndbuf रुकोers.  */
अटल व्योम __sctp_ग_लिखो_space(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sock *sk = asoc->base.sk;

	अगर (sctp_wspace(asoc) <= 0)
		वापस;

	अगर (रुकोqueue_active(&asoc->रुको))
		wake_up_पूर्णांकerruptible(&asoc->रुको);

	अगर (sctp_ग_लिखोable(sk)) अणु
		काष्ठा socket_wq *wq;

		rcu_पढ़ो_lock();
		wq = rcu_dereference(sk->sk_wq);
		अगर (wq) अणु
			अगर (रुकोqueue_active(&wq->रुको))
				wake_up_पूर्णांकerruptible(&wq->रुको);

			/* Note that we try to include the Async I/O support
			 * here by modeling from the current TCP/UDP code.
			 * We have not tested with it yet.
			 */
			अगर (!(sk->sk_shutकरोwn & SEND_SHUTDOWN))
				sock_wake_async(wq, SOCK_WAKE_SPACE, POLL_OUT);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम sctp_wake_up_रुकोers(काष्ठा sock *sk,
				 काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_association *पंचांगp = asoc;

	/* We करो accounting क्रम the sndbuf space per association,
	 * so we only need to wake our own association.
	 */
	अगर (asoc->ep->sndbuf_policy)
		वापस __sctp_ग_लिखो_space(asoc);

	/* If association goes करोwn and is just flushing its
	 * outq, then just normally notअगरy others.
	 */
	अगर (asoc->base.dead)
		वापस sctp_ग_लिखो_space(sk);

	/* Accounting क्रम the sndbuf space is per socket, so we
	 * need to wake up others, try to be fair and in हाल of
	 * other associations, let them have a go first instead
	 * of just करोing a sctp_ग_लिखो_space() call.
	 *
	 * Note that we reach sctp_wake_up_रुकोers() only when
	 * associations मुक्त up queued chunks, thus we are under
	 * lock and the list of associations on a socket is
	 * guaranteed not to change.
	 */
	क्रम (पंचांगp = list_next_entry(पंचांगp, asocs); 1;
	     पंचांगp = list_next_entry(पंचांगp, asocs)) अणु
		/* Manually skip the head element. */
		अगर (&पंचांगp->asocs == &((sctp_sk(sk))->ep->asocs))
			जारी;
		/* Wake up association. */
		__sctp_ग_लिखो_space(पंचांगp);
		/* We've reached the end. */
		अगर (पंचांगp == asoc)
			अवरोध;
	पूर्ण
पूर्ण

/* Do accounting क्रम the sndbuf space.
 * Decrement the used sndbuf space of the corresponding association by the
 * data size which was just transmitted(मुक्तd).
 */
अटल व्योम sctp_wमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sctp_chunk *chunk = skb_shinfo(skb)->deकाष्ठाor_arg;
	काष्ठा sctp_association *asoc = chunk->asoc;
	काष्ठा sock *sk = asoc->base.sk;

	sk_mem_unअक्षरge(sk, skb->truesize);
	sk->sk_wmem_queued -= skb->truesize + माप(काष्ठा sctp_chunk);
	asoc->sndbuf_used -= skb->truesize + माप(काष्ठा sctp_chunk);
	WARN_ON(refcount_sub_and_test(माप(काष्ठा sctp_chunk),
				      &sk->sk_wmem_alloc));

	अगर (chunk->shkey) अणु
		काष्ठा sctp_shared_key *shkey = chunk->shkey;

		/* refcnt == 2 and !list_empty mean after this release, it's
		 * not being used anywhere, and it's समय to notअगरy userland
		 * that this shkey can be मुक्तd अगर it's been deactivated.
		 */
		अगर (shkey->deactivated && !list_empty(&shkey->key_list) &&
		    refcount_पढ़ो(&shkey->refcnt) == 2) अणु
			काष्ठा sctp_ulpevent *ev;

			ev = sctp_ulpevent_make_authkey(asoc, shkey->key_id,
							SCTP_AUTH_FREE_KEY,
							GFP_KERNEL);
			अगर (ev)
				asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
		पूर्ण
		sctp_auth_shkey_release(chunk->shkey);
	पूर्ण

	sock_wमुक्त(skb);
	sctp_wake_up_रुकोers(sk, asoc);

	sctp_association_put(asoc);
पूर्ण

/* Do accounting क्रम the receive space on the socket.
 * Accounting क्रम the association is करोne in ulpevent.c
 * We set this as a deकाष्ठाor क्रम the cloned data skbs so that
 * accounting is करोne at the correct समय.
 */
व्योम sctp_sock_rमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा sctp_ulpevent *event = sctp_skb2event(skb);

	atomic_sub(event->rmem_len, &sk->sk_rmem_alloc);

	/*
	 * Mimic the behavior of sock_rमुक्त
	 */
	sk_mem_unअक्षरge(sk, event->rmem_len);
पूर्ण


/* Helper function to रुको क्रम space in the sndbuf.  */
अटल पूर्णांक sctp_रुको_क्रम_sndbuf(काष्ठा sctp_association *asoc, दीर्घ *समयo_p,
				माप_प्रकार msg_len)
अणु
	काष्ठा sock *sk = asoc->base.sk;
	दीर्घ current_समयo = *समयo_p;
	DEFINE_WAIT(रुको);
	पूर्णांक err = 0;

	pr_debug("%s: asoc:%p, timeo:%ld, msg_len:%zu\n", __func__, asoc,
		 *समयo_p, msg_len);

	/* Increment the association's refcnt.  */
	sctp_association_hold(asoc);

	/* Wait on the association specअगरic sndbuf space. */
	क्रम (;;) अणु
		prepare_to_रुको_exclusive(&asoc->रुको, &रुको,
					  TASK_INTERRUPTIBLE);
		अगर (asoc->base.dead)
			जाओ करो_dead;
		अगर (!*समयo_p)
			जाओ करो_nonblock;
		अगर (sk->sk_err || asoc->state >= SCTP_STATE_SHUTDOWN_PENDING)
			जाओ करो_error;
		अगर (संकेत_pending(current))
			जाओ करो_पूर्णांकerrupted;
		अगर (sk_under_memory_pressure(sk))
			sk_mem_reclaim(sk);
		अगर ((पूर्णांक)msg_len <= sctp_wspace(asoc) &&
		    sk_wmem_schedule(sk, msg_len))
			अवरोध;

		/* Let another process have a go.  Since we are going
		 * to sleep anyway.
		 */
		release_sock(sk);
		current_समयo = schedule_समयout(current_समयo);
		lock_sock(sk);
		अगर (sk != asoc->base.sk)
			जाओ करो_error;

		*समयo_p = current_समयo;
	पूर्ण

out:
	finish_रुको(&asoc->रुको, &रुको);

	/* Release the association's refcnt.  */
	sctp_association_put(asoc);

	वापस err;

करो_dead:
	err = -ESRCH;
	जाओ out;

करो_error:
	err = -EPIPE;
	जाओ out;

करो_पूर्णांकerrupted:
	err = sock_पूर्णांकr_त्रुटि_सं(*समयo_p);
	जाओ out;

करो_nonblock:
	err = -EAGAIN;
	जाओ out;
पूर्ण

व्योम sctp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको, EPOLLIN |
						EPOLLRDNORM | EPOLLRDBAND);
	sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
	rcu_पढ़ो_unlock();
पूर्ण

/* If socket sndbuf has changed, wake up all per association रुकोers.  */
व्योम sctp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा sctp_association *asoc;

	/* Wake up the tasks in each रुको queue.  */
	list_क्रम_each_entry(asoc, &((sctp_sk(sk))->ep->asocs), asocs) अणु
		__sctp_ग_लिखो_space(asoc);
	पूर्ण
पूर्ण

/* Is there any sndbuf space available on the socket?
 *
 * Note that sk_wmem_alloc is the sum of the send buffers on all of the
 * associations on the same socket.  For a UDP-style socket with
 * multiple associations, it is possible क्रम it to be "unwriteable"
 * prematurely.  I assume that this is acceptable because
 * a premature "unwriteable" is better than an accidental "writeable" which
 * would cause an unwanted block under certain circumstances.  For the 1-1
 * UDP-style sockets or TCP-style sockets, this code should work.
 *  - Daisy
 */
अटल bool sctp_ग_लिखोable(काष्ठा sock *sk)
अणु
	वापस sk->sk_sndbuf > sk->sk_wmem_queued;
पूर्ण

/* Wait क्रम an association to go पूर्णांकo ESTABLISHED state. If समयout is 0,
 * वापसs immediately with EINPROGRESS.
 */
अटल पूर्णांक sctp_रुको_क्रम_connect(काष्ठा sctp_association *asoc, दीर्घ *समयo_p)
अणु
	काष्ठा sock *sk = asoc->base.sk;
	पूर्णांक err = 0;
	दीर्घ current_समयo = *समयo_p;
	DEFINE_WAIT(रुको);

	pr_debug("%s: asoc:%p, timeo:%ld\n", __func__, asoc, *समयo_p);

	/* Increment the association's refcnt.  */
	sctp_association_hold(asoc);

	क्रम (;;) अणु
		prepare_to_रुको_exclusive(&asoc->रुको, &रुको,
					  TASK_INTERRUPTIBLE);
		अगर (!*समयo_p)
			जाओ करो_nonblock;
		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			अवरोध;
		अगर (sk->sk_err || asoc->state >= SCTP_STATE_SHUTDOWN_PENDING ||
		    asoc->base.dead)
			जाओ करो_error;
		अगर (संकेत_pending(current))
			जाओ करो_पूर्णांकerrupted;

		अगर (sctp_state(asoc, ESTABLISHED))
			अवरोध;

		/* Let another process have a go.  Since we are going
		 * to sleep anyway.
		 */
		release_sock(sk);
		current_समयo = schedule_समयout(current_समयo);
		lock_sock(sk);

		*समयo_p = current_समयo;
	पूर्ण

out:
	finish_रुको(&asoc->रुको, &रुको);

	/* Release the association's refcnt.  */
	sctp_association_put(asoc);

	वापस err;

करो_error:
	अगर (asoc->init_err_counter + 1 > asoc->max_init_attempts)
		err = -ETIMEDOUT;
	अन्यथा
		err = -ECONNREFUSED;
	जाओ out;

करो_पूर्णांकerrupted:
	err = sock_पूर्णांकr_त्रुटि_सं(*समयo_p);
	जाओ out;

करो_nonblock:
	err = -EINPROGRESS;
	जाओ out;
पूर्ण

अटल पूर्णांक sctp_रुको_क्रम_accept(काष्ठा sock *sk, दीर्घ समयo)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep;
	पूर्णांक err = 0;
	DEFINE_WAIT(रुको);

	ep = sctp_sk(sk)->ep;


	क्रम (;;) अणु
		prepare_to_रुको_exclusive(sk_sleep(sk), &रुको,
					  TASK_INTERRUPTIBLE);

		अगर (list_empty(&ep->asocs)) अणु
			release_sock(sk);
			समयo = schedule_समयout(समयo);
			lock_sock(sk);
		पूर्ण

		err = -EINVAL;
		अगर (!sctp_sstate(sk, LISTENING))
			अवरोध;

		err = 0;
		अगर (!list_empty(&ep->asocs))
			अवरोध;

		err = sock_पूर्णांकr_त्रुटि_सं(समयo);
		अगर (संकेत_pending(current))
			अवरोध;

		err = -EAGAIN;
		अगर (!समयo)
			अवरोध;
	पूर्ण

	finish_रुको(sk_sleep(sk), &रुको);

	वापस err;
पूर्ण

अटल व्योम sctp_रुको_क्रम_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	DEFINE_WAIT(रुको);

	करो अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		अगर (list_empty(&sctp_sk(sk)->ep->asocs))
			अवरोध;
		release_sock(sk);
		समयout = schedule_समयout(समयout);
		lock_sock(sk);
	पूर्ण जबतक (!संकेत_pending(current) && समयout);

	finish_रुको(sk_sleep(sk), &रुको);
पूर्ण

अटल व्योम sctp_skb_set_owner_r_frag(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *frag;

	अगर (!skb->data_len)
		जाओ करोne;

	/* Don't क्रमget the fragments. */
	skb_walk_frags(skb, frag)
		sctp_skb_set_owner_r_frag(frag, sk);

करोne:
	sctp_skb_set_owner_r(skb, sk);
पूर्ण

व्योम sctp_copy_sock(काष्ठा sock *newsk, काष्ठा sock *sk,
		    काष्ठा sctp_association *asoc)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा inet_sock *newinet;
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_endpoपूर्णांक *ep = sp->ep;

	newsk->sk_type = sk->sk_type;
	newsk->sk_bound_dev_अगर = sk->sk_bound_dev_अगर;
	newsk->sk_flags = sk->sk_flags;
	newsk->sk_tsflags = sk->sk_tsflags;
	newsk->sk_no_check_tx = sk->sk_no_check_tx;
	newsk->sk_no_check_rx = sk->sk_no_check_rx;
	newsk->sk_reuse = sk->sk_reuse;
	sctp_sk(newsk)->reuse = sp->reuse;

	newsk->sk_shutकरोwn = sk->sk_shutकरोwn;
	newsk->sk_deकाष्ठा = sctp_deकाष्ठा_sock;
	newsk->sk_family = sk->sk_family;
	newsk->sk_protocol = IPPROTO_SCTP;
	newsk->sk_backlog_rcv = sk->sk_prot->backlog_rcv;
	newsk->sk_sndbuf = sk->sk_sndbuf;
	newsk->sk_rcvbuf = sk->sk_rcvbuf;
	newsk->sk_lingerसमय = sk->sk_lingerसमय;
	newsk->sk_rcvसमयo = sk->sk_rcvसमयo;
	newsk->sk_sndसमयo = sk->sk_sndसमयo;
	newsk->sk_rxhash = sk->sk_rxhash;

	newinet = inet_sk(newsk);

	/* Initialize sk's sport, dport, rcv_saddr and daddr क्रम
	 * माला_लोockname() and getpeername()
	 */
	newinet->inet_sport = inet->inet_sport;
	newinet->inet_saddr = inet->inet_saddr;
	newinet->inet_rcv_saddr = inet->inet_rcv_saddr;
	newinet->inet_dport = htons(asoc->peer.port);
	newinet->pmtudisc = inet->pmtudisc;
	newinet->inet_id = pअक्रमom_u32();

	newinet->uc_ttl = inet->uc_ttl;
	newinet->mc_loop = 1;
	newinet->mc_ttl = 1;
	newinet->mc_index = 0;
	newinet->mc_list = शून्य;

	अगर (newsk->sk_flags & SK_FLAGS_TIMESTAMP)
		net_enable_बारtamp();

	/* Set newsk security attributes from original sk and connection
	 * security attribute from ep.
	 */
	security_sctp_sk_clone(ep, sk, newsk);
पूर्ण

अटल अंतरभूत व्योम sctp_copy_descendant(काष्ठा sock *sk_to,
					स्थिर काष्ठा sock *sk_from)
अणु
	माप_प्रकार ancestor_size = माप(काष्ठा inet_sock);

	ancestor_size += sk_from->sk_prot->obj_size;
	ancestor_size -= दुरत्व(काष्ठा sctp_sock, pd_lobby);
	__inet_sk_copy_descendant(sk_to, sk_from, ancestor_size);
पूर्ण

/* Populate the fields of the newsk from the oldsk and migrate the assoc
 * and its messages to the newsk.
 */
अटल पूर्णांक sctp_sock_migrate(काष्ठा sock *oldsk, काष्ठा sock *newsk,
			     काष्ठा sctp_association *assoc,
			     क्रमागत sctp_socket_type type)
अणु
	काष्ठा sctp_sock *oldsp = sctp_sk(oldsk);
	काष्ठा sctp_sock *newsp = sctp_sk(newsk);
	काष्ठा sctp_bind_bucket *pp; /* hash list port iterator */
	काष्ठा sctp_endpoपूर्णांक *newep = newsp->ep;
	काष्ठा sk_buff *skb, *पंचांगp;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_bind_hashbucket *head;
	पूर्णांक err;

	/* Migrate socket buffer sizes and all the socket level options to the
	 * new socket.
	 */
	newsk->sk_sndbuf = oldsk->sk_sndbuf;
	newsk->sk_rcvbuf = oldsk->sk_rcvbuf;
	/* Brute क्रमce copy old sctp opt. */
	sctp_copy_descendant(newsk, oldsk);

	/* Restore the ep value that was overwritten with the above काष्ठाure
	 * copy.
	 */
	newsp->ep = newep;
	newsp->hmac = शून्य;

	/* Hook this new socket in to the bind_hash list. */
	head = &sctp_port_hashtable[sctp_phashfn(sock_net(oldsk),
						 inet_sk(oldsk)->inet_num)];
	spin_lock_bh(&head->lock);
	pp = sctp_sk(oldsk)->bind_hash;
	sk_add_bind_node(newsk, &pp->owner);
	sctp_sk(newsk)->bind_hash = pp;
	inet_sk(newsk)->inet_num = inet_sk(oldsk)->inet_num;
	spin_unlock_bh(&head->lock);

	/* Copy the bind_addr list from the original endpoपूर्णांक to the new
	 * endpoपूर्णांक so that we can handle restarts properly
	 */
	err = sctp_bind_addr_dup(&newsp->ep->base.bind_addr,
				 &oldsp->ep->base.bind_addr, GFP_KERNEL);
	अगर (err)
		वापस err;

	/* New ep's auth_hmacs should be set if old ep's is set, in हाल
	 * that net->sctp.auth_enable has been changed to 0 by users and
	 * new ep's auth_hmacs couldn't be set in sctp_endpoपूर्णांक_init().
	 */
	अगर (oldsp->ep->auth_hmacs) अणु
		err = sctp_auth_init_hmacs(newsp->ep, GFP_KERNEL);
		अगर (err)
			वापस err;
	पूर्ण

	sctp_स्वतः_asconf_init(newsp);

	/* Move any messages in the old socket's receive queue that are क्रम the
	 * peeled off association to the new socket's receive queue.
	 */
	sctp_skb_क्रम_each(skb, &oldsk->sk_receive_queue, पंचांगp) अणु
		event = sctp_skb2event(skb);
		अगर (event->asoc == assoc) अणु
			__skb_unlink(skb, &oldsk->sk_receive_queue);
			__skb_queue_tail(&newsk->sk_receive_queue, skb);
			sctp_skb_set_owner_r_frag(skb, newsk);
		पूर्ण
	पूर्ण

	/* Clean up any messages pending delivery due to partial
	 * delivery.   Three हालs:
	 * 1) No partial deliver;  no work.
	 * 2) Peeling off partial delivery; keep pd_lobby in new pd_lobby.
	 * 3) Peeling off non-partial delivery; move pd_lobby to receive_queue.
	 */
	atomic_set(&sctp_sk(newsk)->pd_mode, assoc->ulpq.pd_mode);

	अगर (atomic_पढ़ो(&sctp_sk(oldsk)->pd_mode)) अणु
		काष्ठा sk_buff_head *queue;

		/* Decide which queue to move pd_lobby skbs to. */
		अगर (assoc->ulpq.pd_mode) अणु
			queue = &newsp->pd_lobby;
		पूर्ण अन्यथा
			queue = &newsk->sk_receive_queue;

		/* Walk through the pd_lobby, looking क्रम skbs that
		 * need moved to the new socket.
		 */
		sctp_skb_क्रम_each(skb, &oldsp->pd_lobby, पंचांगp) अणु
			event = sctp_skb2event(skb);
			अगर (event->asoc == assoc) अणु
				__skb_unlink(skb, &oldsp->pd_lobby);
				__skb_queue_tail(queue, skb);
				sctp_skb_set_owner_r_frag(skb, newsk);
			पूर्ण
		पूर्ण

		/* Clear up any skbs रुकोing क्रम the partial
		 * delivery to finish.
		 */
		अगर (assoc->ulpq.pd_mode)
			sctp_clear_pd(oldsk, शून्य);

	पूर्ण

	sctp_क्रम_each_rx_skb(assoc, newsk, sctp_skb_set_owner_r_frag);

	/* Set the type of socket to indicate that it is peeled off from the
	 * original UDP-style socket or created with the accept() call on a
	 * TCP-style socket..
	 */
	newsp->type = type;

	/* Mark the new socket "in-use" by the user so that any packets
	 * that may arrive on the association after we've moved it are
	 * queued to the backlog.  This prevents a potential race between
	 * backlog processing on the old socket and new-packet processing
	 * on the new socket.
	 *
	 * The caller has just allocated newsk so we can guarantee that other
	 * paths won't try to lock it and then oldsk.
	 */
	lock_sock_nested(newsk, SINGLE_DEPTH_NESTING);
	sctp_क्रम_each_tx_datachunk(assoc, true, sctp_clear_owner_w);
	sctp_assoc_migrate(assoc, newsk);
	sctp_क्रम_each_tx_datachunk(assoc, false, sctp_set_owner_w);

	/* If the association on the newsk is alपढ़ोy बंदd beक्रमe accept()
	 * is called, set RCV_SHUTDOWN flag.
	 */
	अगर (sctp_state(assoc, CLOSED) && sctp_style(newsk, TCP)) अणु
		inet_sk_set_state(newsk, SCTP_SS_CLOSED);
		newsk->sk_shutकरोwn |= RCV_SHUTDOWN;
	पूर्ण अन्यथा अणु
		inet_sk_set_state(newsk, SCTP_SS_ESTABLISHED);
	पूर्ण

	release_sock(newsk);

	वापस 0;
पूर्ण


/* This proto काष्ठा describes the ULP पूर्णांकerface क्रम SCTP.  */
काष्ठा proto sctp_prot = अणु
	.name        =	"SCTP",
	.owner       =	THIS_MODULE,
	.बंद       =	sctp_बंद,
	.disconnect  =	sctp_disconnect,
	.accept      =	sctp_accept,
	.ioctl       =	sctp_ioctl,
	.init        =	sctp_init_sock,
	.destroy     =	sctp_destroy_sock,
	.shutकरोwn    =	sctp_shutकरोwn,
	.setsockopt  =	sctp_setsockopt,
	.माला_लोockopt  =	sctp_माला_लोockopt,
	.sendmsg     =	sctp_sendmsg,
	.recvmsg     =	sctp_recvmsg,
	.bind        =	sctp_bind,
	.bind_add    =  sctp_bind_add,
	.backlog_rcv =	sctp_backlog_rcv,
	.hash        =	sctp_hash,
	.unhash      =	sctp_unhash,
	.no_स्वतःbind =	true,
	.obj_size    =  माप(काष्ठा sctp_sock),
	.useroffset  =  दुरत्व(काष्ठा sctp_sock, subscribe),
	.usersize    =  दुरत्व(काष्ठा sctp_sock, iniपंचांगsg) -
				दुरत्व(काष्ठा sctp_sock, subscribe) +
				माप_field(काष्ठा sctp_sock, iniपंचांगsg),
	.sysctl_mem  =  sysctl_sctp_mem,
	.sysctl_rmem =  sysctl_sctp_rmem,
	.sysctl_wmem =  sysctl_sctp_wmem,
	.memory_pressure = &sctp_memory_pressure,
	.enter_memory_pressure = sctp_enter_memory_pressure,
	.memory_allocated = &sctp_memory_allocated,
	.sockets_allocated = &sctp_sockets_allocated,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)

#समावेश <net/transp_v6.h>
अटल व्योम sctp_v6_destroy_sock(काष्ठा sock *sk)
अणु
	sctp_destroy_sock(sk);
	inet6_destroy_sock(sk);
पूर्ण

काष्ठा proto sctpv6_prot = अणु
	.name		= "SCTPv6",
	.owner		= THIS_MODULE,
	.बंद		= sctp_बंद,
	.disconnect	= sctp_disconnect,
	.accept		= sctp_accept,
	.ioctl		= sctp_ioctl,
	.init		= sctp_init_sock,
	.destroy	= sctp_v6_destroy_sock,
	.shutकरोwn	= sctp_shutकरोwn,
	.setsockopt	= sctp_setsockopt,
	.माला_लोockopt	= sctp_माला_लोockopt,
	.sendmsg	= sctp_sendmsg,
	.recvmsg	= sctp_recvmsg,
	.bind		= sctp_bind,
	.bind_add	= sctp_bind_add,
	.backlog_rcv	= sctp_backlog_rcv,
	.hash		= sctp_hash,
	.unhash		= sctp_unhash,
	.no_स्वतःbind	= true,
	.obj_size	= माप(काष्ठा sctp6_sock),
	.useroffset	= दुरत्व(काष्ठा sctp6_sock, sctp.subscribe),
	.usersize	= दुरत्व(काष्ठा sctp6_sock, sctp.iniपंचांगsg) -
				दुरत्व(काष्ठा sctp6_sock, sctp.subscribe) +
				माप_field(काष्ठा sctp6_sock, sctp.iniपंचांगsg),
	.sysctl_mem	= sysctl_sctp_mem,
	.sysctl_rmem	= sysctl_sctp_rmem,
	.sysctl_wmem	= sysctl_sctp_wmem,
	.memory_pressure = &sctp_memory_pressure,
	.enter_memory_pressure = sctp_enter_memory_pressure,
	.memory_allocated = &sctp_memory_allocated,
	.sockets_allocated = &sctp_sockets_allocated,
पूर्ण;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */

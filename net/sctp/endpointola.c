<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2002 International Business Machines, Corp.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * This file is part of the SCTP kernel implementation
 *
 * This असलtraction represents an SCTP endpoपूर्णांक.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson <karl@athena.chicago.il.us>
 *    Jon Grimm <jgrimm@austin.ibm.com>
 *    Daisy Chang <daisyc@us.ibm.com>
 *    Dajiang Zhang <dajiang.zhang@nokia.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <linux/अक्रमom.h>	/* get_अक्रमom_bytes() */
#समावेश <net/sock.h>
#समावेश <net/ipv6.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

/* Forward declarations क्रम पूर्णांकernal helpers. */
अटल व्योम sctp_endpoपूर्णांक_bh_rcv(काष्ठा work_काष्ठा *work);

/*
 * Initialize the base fields of the endpoपूर्णांक काष्ठाure.
 */
अटल काष्ठा sctp_endpoपूर्णांक *sctp_endpoपूर्णांक_init(काष्ठा sctp_endpoपूर्णांक *ep,
						काष्ठा sock *sk,
						gfp_t gfp)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा sctp_shared_key *null_key;

	ep->digest = kzalloc(SCTP_SIGNATURE_SIZE, gfp);
	अगर (!ep->digest)
		वापस शून्य;

	ep->asconf_enable = net->sctp.addip_enable;
	ep->auth_enable = net->sctp.auth_enable;
	अगर (ep->auth_enable) अणु
		अगर (sctp_auth_init(ep, gfp))
			जाओ nomem;
		अगर (ep->asconf_enable) अणु
			sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF);
			sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF_ACK);
		पूर्ण
	पूर्ण

	/* Initialize the base काष्ठाure. */
	/* What type of endpoपूर्णांक are we?  */
	ep->base.type = SCTP_EP_TYPE_SOCKET;

	/* Initialize the basic object fields. */
	refcount_set(&ep->base.refcnt, 1);
	ep->base.dead = false;

	/* Create an input queue.  */
	sctp_inq_init(&ep->base.inqueue);

	/* Set its top-half handler */
	sctp_inq_set_th_handler(&ep->base.inqueue, sctp_endpoपूर्णांक_bh_rcv);

	/* Initialize the bind addr area */
	sctp_bind_addr_init(&ep->base.bind_addr, 0);

	/* Create the lists of associations.  */
	INIT_LIST_HEAD(&ep->asocs);

	/* Use SCTP specअगरic send buffer space queues.  */
	ep->sndbuf_policy = net->sctp.sndbuf_policy;

	sk->sk_data_पढ़ोy = sctp_data_पढ़ोy;
	sk->sk_ग_लिखो_space = sctp_ग_लिखो_space;
	sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);

	/* Get the receive buffer policy क्रम this endpoपूर्णांक */
	ep->rcvbuf_policy = net->sctp.rcvbuf_policy;

	/* Initialize the secret key used with cookie. */
	get_अक्रमom_bytes(ep->secret_key, माप(ep->secret_key));

	/* SCTP-AUTH extensions*/
	INIT_LIST_HEAD(&ep->endpoपूर्णांक_shared_keys);
	null_key = sctp_auth_shkey_create(0, gfp);
	अगर (!null_key)
		जाओ nomem_shkey;

	list_add(&null_key->key_list, &ep->endpoपूर्णांक_shared_keys);

	/* Add the null key to the endpoपूर्णांक shared keys list and
	 * set the hmcas and chunks poपूर्णांकers.
	 */
	ep->prsctp_enable = net->sctp.prsctp_enable;
	ep->reconf_enable = net->sctp.reconf_enable;
	ep->ecn_enable = net->sctp.ecn_enable;

	/* Remember who we are attached to.  */
	ep->base.sk = sk;
	ep->base.net = sock_net(sk);
	sock_hold(ep->base.sk);

	वापस ep;

nomem_shkey:
	sctp_auth_मुक्त(ep);
nomem:
	kमुक्त(ep->digest);
	वापस शून्य;

पूर्ण

/* Create a sctp_endpoपूर्णांक with all that boring stuff initialized.
 * Returns शून्य अगर there isn't enough memory.
 */
काष्ठा sctp_endpoपूर्णांक *sctp_endpoपूर्णांक_new(काष्ठा sock *sk, gfp_t gfp)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep;

	/* Build a local endpoपूर्णांक. */
	ep = kzalloc(माप(*ep), gfp);
	अगर (!ep)
		जाओ fail;

	अगर (!sctp_endpoपूर्णांक_init(ep, sk, gfp))
		जाओ fail_init;

	SCTP_DBG_OBJCNT_INC(ep);
	वापस ep;

fail_init:
	kमुक्त(ep);
fail:
	वापस शून्य;
पूर्ण

/* Add an association to an endpoपूर्णांक.  */
व्योम sctp_endpoपूर्णांक_add_asoc(काष्ठा sctp_endpoपूर्णांक *ep,
			    काष्ठा sctp_association *asoc)
अणु
	काष्ठा sock *sk = ep->base.sk;

	/* If this is a temporary association, करोn't bother
	 * since we'll be removing it shortly and don't
	 * want anyone to find it anyway.
	 */
	अगर (asoc->temp)
		वापस;

	/* Now just add it to our list of asocs */
	list_add_tail(&asoc->asocs, &ep->asocs);

	/* Increment the backlog value क्रम a TCP-style listening socket. */
	अगर (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING))
		sk_acceptq_added(sk);
पूर्ण

/* Free the endpoपूर्णांक काष्ठाure.  Delay cleanup until
 * all users have released their reference count on this काष्ठाure.
 */
व्योम sctp_endpoपूर्णांक_मुक्त(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	ep->base.dead = true;

	inet_sk_set_state(ep->base.sk, SCTP_SS_CLOSED);

	/* Unlink this endpoपूर्णांक, so we can't find it again! */
	sctp_unhash_endpoपूर्णांक(ep);

	sctp_endpoपूर्णांक_put(ep);
पूर्ण

/* Final deकाष्ठाor क्रम endpoपूर्णांक.  */
अटल व्योम sctp_endpoपूर्णांक_destroy(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	काष्ठा sock *sk;

	अगर (unlikely(!ep->base.dead)) अणु
		WARN(1, "Attempt to destroy undead endpoint %p!\n", ep);
		वापस;
	पूर्ण

	/* Free the digest buffer */
	kमुक्त(ep->digest);

	/* SCTP-AUTH: Free up AUTH releated data such as shared keys
	 * chunks and hmacs arrays that were allocated
	 */
	sctp_auth_destroy_keys(&ep->endpoपूर्णांक_shared_keys);
	sctp_auth_मुक्त(ep);

	/* Cleanup. */
	sctp_inq_मुक्त(&ep->base.inqueue);
	sctp_bind_addr_मुक्त(&ep->base.bind_addr);

	स_रखो(ep->secret_key, 0, माप(ep->secret_key));

	sk = ep->base.sk;
	/* Remove and मुक्त the port */
	अगर (sctp_sk(sk)->bind_hash)
		sctp_put_port(sk);

	sctp_sk(sk)->ep = शून्य;
	/* Give up our hold on the sock */
	sock_put(sk);

	kमुक्त(ep);
	SCTP_DBG_OBJCNT_DEC(ep);
पूर्ण

/* Hold a reference to an endpoपूर्णांक. */
व्योम sctp_endpoपूर्णांक_hold(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	refcount_inc(&ep->base.refcnt);
पूर्ण

/* Release a reference to an endpoपूर्णांक and clean up अगर there are
 * no more references.
 */
व्योम sctp_endpoपूर्णांक_put(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	अगर (refcount_dec_and_test(&ep->base.refcnt))
		sctp_endpoपूर्णांक_destroy(ep);
पूर्ण

/* Is this the endpoपूर्णांक we are looking क्रम?  */
काष्ठा sctp_endpoपूर्णांक *sctp_endpoपूर्णांक_is_match(काष्ठा sctp_endpoपूर्णांक *ep,
					       काष्ठा net *net,
					       स्थिर जोड़ sctp_addr *laddr)
अणु
	काष्ठा sctp_endpoपूर्णांक *retval = शून्य;

	अगर ((htons(ep->base.bind_addr.port) == laddr->v4.sin_port) &&
	    net_eq(ep->base.net, net)) अणु
		अगर (sctp_bind_addr_match(&ep->base.bind_addr, laddr,
					 sctp_sk(ep->base.sk)))
			retval = ep;
	पूर्ण

	वापस retval;
पूर्ण

/* Find the association that goes with this chunk.
 * We lookup the transport from hashtable at first, then get association
 * through t->assoc.
 */
काष्ठा sctp_association *sctp_endpoपूर्णांक_lookup_assoc(
	स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
	स्थिर जोड़ sctp_addr *paddr,
	काष्ठा sctp_transport **transport)
अणु
	काष्ठा sctp_association *asoc = शून्य;
	काष्ठा sctp_transport *t;

	*transport = शून्य;

	/* If the local port is not set, there can't be any associations
	 * on this endpoपूर्णांक.
	 */
	अगर (!ep->base.bind_addr.port)
		वापस शून्य;

	rcu_पढ़ो_lock();
	t = sctp_epaddr_lookup_transport(ep, paddr);
	अगर (!t)
		जाओ out;

	*transport = t;
	asoc = t->asoc;
out:
	rcu_पढ़ो_unlock();
	वापस asoc;
पूर्ण

/* Look क्रम any peeled off association from the endpoपूर्णांक that matches the
 * given peer address.
 */
bool sctp_endpoपूर्णांक_is_peeled_off(काष्ठा sctp_endpoपूर्णांक *ep,
				 स्थिर जोड़ sctp_addr *paddr)
अणु
	काष्ठा sctp_sockaddr_entry *addr;
	काष्ठा net *net = ep->base.net;
	काष्ठा sctp_bind_addr *bp;

	bp = &ep->base.bind_addr;
	/* This function is called with the socket lock held,
	 * so the address_list can not change.
	 */
	list_क्रम_each_entry(addr, &bp->address_list, list) अणु
		अगर (sctp_has_association(net, &addr->a, paddr))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Do delayed input processing.  This is scheduled by sctp_rcv().
 * This may be called on BH or task समय.
 */
अटल व्योम sctp_endpoपूर्णांक_bh_rcv(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep =
		container_of(work, काष्ठा sctp_endpoपूर्णांक,
			     base.inqueue.immediate);
	काष्ठा sctp_association *asoc;
	काष्ठा sock *sk;
	काष्ठा net *net;
	काष्ठा sctp_transport *transport;
	काष्ठा sctp_chunk *chunk;
	काष्ठा sctp_inq *inqueue;
	जोड़ sctp_subtype subtype;
	क्रमागत sctp_state state;
	पूर्णांक error = 0;
	पूर्णांक first_समय = 1;	/* is this the first समय through the loop */

	अगर (ep->base.dead)
		वापस;

	asoc = शून्य;
	inqueue = &ep->base.inqueue;
	sk = ep->base.sk;
	net = sock_net(sk);

	जबतक (शून्य != (chunk = sctp_inq_pop(inqueue))) अणु
		subtype = SCTP_ST_CHUNK(chunk->chunk_hdr->type);

		/* If the first chunk in the packet is AUTH, करो special
		 * processing specअगरied in Section 6.3 of SCTP-AUTH spec
		 */
		अगर (first_समय && (subtype.chunk == SCTP_CID_AUTH)) अणु
			काष्ठा sctp_chunkhdr *next_hdr;

			next_hdr = sctp_inq_peek(inqueue);
			अगर (!next_hdr)
				जाओ normal;

			/* If the next chunk is COOKIE-ECHO, skip the AUTH
			 * chunk जबतक saving a poपूर्णांकer to it so we can करो
			 * Authentication later (during cookie-echo
			 * processing).
			 */
			अगर (next_hdr->type == SCTP_CID_COOKIE_ECHO) अणु
				chunk->auth_chunk = skb_clone(chunk->skb,
								GFP_ATOMIC);
				chunk->auth = 1;
				जारी;
			पूर्ण
		पूर्ण
normal:
		/* We might have grown an association since last we
		 * looked, so try again.
		 *
		 * This happens when we've just processed our
		 * COOKIE-ECHO chunk.
		 */
		अगर (शून्य == chunk->asoc) अणु
			asoc = sctp_endpoपूर्णांक_lookup_assoc(ep,
							  sctp_source(chunk),
							  &transport);
			chunk->asoc = asoc;
			chunk->transport = transport;
		पूर्ण

		state = asoc ? asoc->state : SCTP_STATE_CLOSED;
		अगर (sctp_auth_recv_cid(subtype.chunk, asoc) && !chunk->auth)
			जारी;

		/* Remember where the last DATA chunk came from so we
		 * know where to send the SACK.
		 */
		अगर (asoc && sctp_chunk_is_data(chunk))
			asoc->peer.last_data_from = chunk->transport;
		अन्यथा अणु
			SCTP_INC_STATS(ep->base.net, SCTP_MIB_INCTRLCHUNKS);
			अगर (asoc)
				asoc->stats.ictrlchunks++;
		पूर्ण

		अगर (chunk->transport)
			chunk->transport->last_समय_heard = kसमय_get();

		error = sctp_करो_sm(net, SCTP_EVENT_T_CHUNK, subtype, state,
				   ep, asoc, chunk, GFP_ATOMIC);

		अगर (error && chunk)
			chunk->pdiscard = 1;

		/* Check to see अगर the endpoपूर्णांक is मुक्तd in response to
		 * the incoming chunk. If so, get out of the जबतक loop.
		 */
		अगर (!sctp_sk(sk)->ep)
			अवरोध;

		अगर (first_समय)
			first_समय = 0;
	पूर्ण
पूर्ण

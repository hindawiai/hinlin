<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/** -*- linux-c -*- ***********************************************************
 * Linux PPP over Ethernet (PPPoX/PPPoE) Sockets
 *
 * PPPoX --- Generic PPP encapsulation socket family
 * PPPoE --- PPP over Ethernet (RFC 2516)
 *
 * Version:	0.7.0
 *
 * 070228 :	Fix to allow multiple sessions with same remote MAC and same
 *		session id by including the local device अगरindex in the
 *		tuple identअगरying a session. This also ensures packets can't
 *		be injected पूर्णांकo a session from पूर्णांकerfaces other than the one
 *		specअगरied by userspace. Florian Zumbiehl <florz@florz.de>
 *		(Oh, BTW, this one is YYMMDD, in हाल you were wondering ...)
 * 220102 :	Fix module use count on failure in pppoe_create, pppox_sk -acme
 * 030700 :	Fixed connect logic to allow क्रम disconnect.
 * 270700 :	Fixed potential SMP problems; we must protect against
 *		simultaneous invocation of ppp_input
 *		and ppp_unरेजिस्टर_channel.
 * 040800 :	Respect reference count mechanisms on net-devices.
 * 200800 :	fix kमुक्त(skb) in pppoe_rcv (acme)
 *		Module reference count is decremented in the right spot now,
 *		guards against sock_put not actually मुक्तing the sk
 *		in pppoe_release.
 * 051000 :	Initialization cleanup.
 * 111100 :	Fix recvmsg.
 * 050101 :	Fix PADT processing.
 * 140501 :	Use pppoe_rcv_core to handle all backlog. (Alexey)
 * 170701 :	Do not lock_sock with rwlock held. (DaveM)
 *		Ignore discovery frames अगर user has socket
 *		locked. (DaveM)
 *		Ignore वापस value of dev_queue_xmit in __pppoe_xmit
 *		or अन्यथा we may kमुक्त an SKB twice. (DaveM)
 * 190701 :	When करोing copies of skb's in __pppoe_xmit, always delete
 *		the original skb that was passed in on success, never on
 *		failure.  Delete the copy of the skb on failure to aव्योम
 *		a memory leak.
 * 081001 :	Misc. cleanup (licence string, non-blocking, prevent
 *		reference of device on बंद).
 * 121301 :	New ppp channels पूर्णांकerface; cannot unरेजिस्टर a channel
 *		from पूर्णांकerrupts.  Thus, we mark the socket as a ZOMBIE
 *		and करो the unregistration later.
 * 081002 :	seq_file support क्रम proc stuff -acme
 * 111602 :	Merge all 2.4 fixes पूर्णांकo 2.5/2.6 tree.  Label 2.5/2.6
 *		as version 0.7.  Spacing cleanup.
 * Author:	Michal Ostrowski <mostrows@speakeasy.net>
 * Contributors:
 * 		Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *		David S. Miller (davem@redhat.com)
 *
 * License:
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/net.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_pppox.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/nsproxy.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>

#समावेश <linux/uaccess.h>

#घोषणा PPPOE_HASH_BITS 4
#घोषणा PPPOE_HASH_SIZE (1 << PPPOE_HASH_BITS)
#घोषणा PPPOE_HASH_MASK	(PPPOE_HASH_SIZE - 1)

अटल पूर्णांक __pppoe_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल स्थिर काष्ठा proto_ops pppoe_ops;
अटल स्थिर काष्ठा ppp_channel_ops pppoe_chan_ops;

/* per-net निजी data क्रम this module */
अटल अचिन्हित पूर्णांक pppoe_net_id __पढ़ो_mostly;
काष्ठा pppoe_net अणु
	/*
	 * we could use _single_ hash table क्रम all
	 * nets by injecting net id पूर्णांकo the hash but
	 * it would increase hash chains and add
	 * a few additional math comparisons messy
	 * as well, moreover in हाल of SMP less locking
	 * controversy here
	 */
	काष्ठा pppox_sock *hash_table[PPPOE_HASH_SIZE];
	rwlock_t hash_lock;
पूर्ण;

/*
 * PPPoE could be in the following stages:
 * 1) Discovery stage (to obtain remote MAC and Session ID)
 * 2) Session stage (MAC and SID are known)
 *
 * Ethernet frames have a special tag क्रम this but
 * we use simpler approach based on session id
 */
अटल अंतरभूत bool stage_session(__be16 sid)
अणु
	वापस sid != 0;
पूर्ण

अटल अंतरभूत काष्ठा pppoe_net *pppoe_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, pppoe_net_id);
पूर्ण

अटल अंतरभूत पूर्णांक cmp_2_addr(काष्ठा pppoe_addr *a, काष्ठा pppoe_addr *b)
अणु
	वापस a->sid == b->sid && ether_addr_equal(a->remote, b->remote);
पूर्ण

अटल अंतरभूत पूर्णांक cmp_addr(काष्ठा pppoe_addr *a, __be16 sid, अक्षर *addr)
अणु
	वापस a->sid == sid && ether_addr_equal(a->remote, addr);
पूर्ण

#अगर 8 % PPPOE_HASH_BITS
#त्रुटि 8 must be a multiple of PPPOE_HASH_BITS
#पूर्ण_अगर

अटल पूर्णांक hash_item(__be16 sid, अचिन्हित अक्षर *addr)
अणु
	अचिन्हित अक्षर hash = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		hash ^= addr[i];
	क्रम (i = 0; i < माप(sid_t) * 8; i += 8)
		hash ^= (__क्रमce __u32)sid >> i;
	क्रम (i = 8; (i >>= 1) >= PPPOE_HASH_BITS;)
		hash ^= hash >> i;

	वापस hash & PPPOE_HASH_MASK;
पूर्ण

/**********************************************************************
 *
 *  Set/get/delete/rehash items  (पूर्णांकernal versions)
 *
 **********************************************************************/
अटल काष्ठा pppox_sock *__get_item(काष्ठा pppoe_net *pn, __be16 sid,
				अचिन्हित अक्षर *addr, पूर्णांक अगरindex)
अणु
	पूर्णांक hash = hash_item(sid, addr);
	काष्ठा pppox_sock *ret;

	ret = pn->hash_table[hash];
	जबतक (ret) अणु
		अगर (cmp_addr(&ret->pppoe_pa, sid, addr) &&
		    ret->pppoe_अगरindex == अगरindex)
			वापस ret;

		ret = ret->next;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __set_item(काष्ठा pppoe_net *pn, काष्ठा pppox_sock *po)
अणु
	पूर्णांक hash = hash_item(po->pppoe_pa.sid, po->pppoe_pa.remote);
	काष्ठा pppox_sock *ret;

	ret = pn->hash_table[hash];
	जबतक (ret) अणु
		अगर (cmp_2_addr(&ret->pppoe_pa, &po->pppoe_pa) &&
		    ret->pppoe_अगरindex == po->pppoe_अगरindex)
			वापस -EALREADY;

		ret = ret->next;
	पूर्ण

	po->next = pn->hash_table[hash];
	pn->hash_table[hash] = po;

	वापस 0;
पूर्ण

अटल व्योम __delete_item(काष्ठा pppoe_net *pn, __be16 sid,
					अक्षर *addr, पूर्णांक अगरindex)
अणु
	पूर्णांक hash = hash_item(sid, addr);
	काष्ठा pppox_sock *ret, **src;

	ret = pn->hash_table[hash];
	src = &pn->hash_table[hash];

	जबतक (ret) अणु
		अगर (cmp_addr(&ret->pppoe_pa, sid, addr) &&
		    ret->pppoe_अगरindex == अगरindex) अणु
			*src = ret->next;
			अवरोध;
		पूर्ण

		src = &ret->next;
		ret = ret->next;
	पूर्ण
पूर्ण

/**********************************************************************
 *
 *  Set/get/delete/rehash items
 *
 **********************************************************************/
अटल अंतरभूत काष्ठा pppox_sock *get_item(काष्ठा pppoe_net *pn, __be16 sid,
					अचिन्हित अक्षर *addr, पूर्णांक अगरindex)
अणु
	काष्ठा pppox_sock *po;

	पढ़ो_lock_bh(&pn->hash_lock);
	po = __get_item(pn, sid, addr, अगरindex);
	अगर (po)
		sock_hold(sk_pppox(po));
	पढ़ो_unlock_bh(&pn->hash_lock);

	वापस po;
पूर्ण

अटल अंतरभूत काष्ठा pppox_sock *get_item_by_addr(काष्ठा net *net,
						काष्ठा sockaddr_pppox *sp)
अणु
	काष्ठा net_device *dev;
	काष्ठा pppoe_net *pn;
	काष्ठा pppox_sock *pppox_sock = शून्य;

	पूर्णांक अगरindex;

	rcu_पढ़ो_lock();
	dev = dev_get_by_name_rcu(net, sp->sa_addr.pppoe.dev);
	अगर (dev) अणु
		अगरindex = dev->अगरindex;
		pn = pppoe_pernet(net);
		pppox_sock = get_item(pn, sp->sa_addr.pppoe.sid,
				sp->sa_addr.pppoe.remote, अगरindex);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस pppox_sock;
पूर्ण

अटल अंतरभूत व्योम delete_item(काष्ठा pppoe_net *pn, __be16 sid,
					अक्षर *addr, पूर्णांक अगरindex)
अणु
	ग_लिखो_lock_bh(&pn->hash_lock);
	__delete_item(pn, sid, addr, अगरindex);
	ग_लिखो_unlock_bh(&pn->hash_lock);
पूर्ण

/***************************************************************************
 *
 *  Handler क्रम device events.
 *  Certain device events require that sockets be unconnected.
 *
 **************************************************************************/

अटल व्योम pppoe_flush_dev(काष्ठा net_device *dev)
अणु
	काष्ठा pppoe_net *pn;
	पूर्णांक i;

	pn = pppoe_pernet(dev_net(dev));
	ग_लिखो_lock_bh(&pn->hash_lock);
	क्रम (i = 0; i < PPPOE_HASH_SIZE; i++) अणु
		काष्ठा pppox_sock *po = pn->hash_table[i];
		काष्ठा sock *sk;

		जबतक (po) अणु
			जबतक (po && po->pppoe_dev != dev) अणु
				po = po->next;
			पूर्ण

			अगर (!po)
				अवरोध;

			sk = sk_pppox(po);

			/* We always grab the socket lock, followed by the
			 * hash_lock, in that order.  Since we should hold the
			 * sock lock जबतक करोing any unbinding, we need to
			 * release the lock we're holding.  Hold a reference to
			 * the sock so it करोesn't disappear as we're jumping
			 * between locks.
			 */

			sock_hold(sk);
			ग_लिखो_unlock_bh(&pn->hash_lock);
			lock_sock(sk);

			अगर (po->pppoe_dev == dev &&
			    sk->sk_state & (PPPOX_CONNECTED | PPPOX_BOUND)) अणु
				pppox_unbind_sock(sk);
				sk->sk_state_change(sk);
				po->pppoe_dev = शून्य;
				dev_put(dev);
			पूर्ण

			release_sock(sk);
			sock_put(sk);

			/* Restart the process from the start of the current
			 * hash chain. We dropped locks so the world may have
			 * change from underneath us.
			 */

			BUG_ON(pppoe_pernet(dev_net(dev)) == शून्य);
			ग_लिखो_lock_bh(&pn->hash_lock);
			po = pn->hash_table[i];
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&pn->hash_lock);
पूर्ण

अटल पूर्णांक pppoe_device_event(काष्ठा notअगरier_block *this,
			      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	/* Only look at sockets that are using this specअगरic device. */
	चयन (event) अणु
	हाल NETDEV_CHANGEADDR:
	हाल NETDEV_CHANGEMTU:
		/* A change in mtu or address is a bad thing, requiring
		 * LCP re-negotiation.
		 */

	हाल NETDEV_GOING_DOWN:
	हाल NETDEV_DOWN:
		/* Find every socket on this device and समाप्त it. */
		pppoe_flush_dev(dev);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block pppoe_notअगरier = अणु
	.notअगरier_call = pppoe_device_event,
पूर्ण;

/************************************************************************
 *
 * Do the real work of receiving a PPPoE Session frame.
 *
 ***********************************************************************/
अटल पूर्णांक pppoe_rcv_core(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा pppox_sock *relay_po;

	/* Backlog receive. Semantics of backlog rcv preclude any code from
	 * executing in lock_sock()/release_sock() bounds; meaning sk->sk_state
	 * can't change.
	 */

	अगर (skb->pkt_type == PACKET_OTHERHOST)
		जाओ पात_kमुक्त;

	अगर (sk->sk_state & PPPOX_BOUND) अणु
		ppp_input(&po->chan, skb);
	पूर्ण अन्यथा अगर (sk->sk_state & PPPOX_RELAY) अणु
		relay_po = get_item_by_addr(sock_net(sk),
					    &po->pppoe_relay);
		अगर (relay_po == शून्य)
			जाओ पात_kमुक्त;

		अगर ((sk_pppox(relay_po)->sk_state & PPPOX_CONNECTED) == 0)
			जाओ पात_put;

		अगर (!__pppoe_xmit(sk_pppox(relay_po), skb))
			जाओ पात_put;

		sock_put(sk_pppox(relay_po));
	पूर्ण अन्यथा अणु
		अगर (sock_queue_rcv_skb(sk, skb))
			जाओ पात_kमुक्त;
	पूर्ण

	वापस NET_RX_SUCCESS;

पात_put:
	sock_put(sk_pppox(relay_po));

पात_kमुक्त:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

/************************************************************************
 *
 * Receive wrapper called in BH context.
 *
 ***********************************************************************/
अटल पूर्णांक pppoe_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा pppoe_hdr *ph;
	काष्ठा pppox_sock *po;
	काष्ठा pppoe_net *pn;
	पूर्णांक len;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;

	अगर (skb_mac_header_len(skb) < ETH_HLEN)
		जाओ drop;

	अगर (!pskb_may_pull(skb, माप(काष्ठा pppoe_hdr)))
		जाओ drop;

	ph = pppoe_hdr(skb);
	len = ntohs(ph->length);

	skb_pull_rcsum(skb, माप(*ph));
	अगर (skb->len < len)
		जाओ drop;

	अगर (pskb_trim_rcsum(skb, len))
		जाओ drop;

	ph = pppoe_hdr(skb);
	pn = pppoe_pernet(dev_net(dev));

	/* Note that get_item करोes a sock_hold(), so sk_pppox(po)
	 * is known to be safe.
	 */
	po = get_item(pn, ph->sid, eth_hdr(skb)->h_source, dev->अगरindex);
	अगर (!po)
		जाओ drop;

	वापस sk_receive_skb(sk_pppox(po), skb, 0);

drop:
	kमुक्त_skb(skb);
out:
	वापस NET_RX_DROP;
पूर्ण

अटल व्योम pppoe_unbind_sock_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pppox_sock *po = container_of(work, काष्ठा pppox_sock,
					     proto.pppoe.padt_work);
	काष्ठा sock *sk = sk_pppox(po);

	lock_sock(sk);
	अगर (po->pppoe_dev) अणु
		dev_put(po->pppoe_dev);
		po->pppoe_dev = शून्य;
	पूर्ण
	pppox_unbind_sock(sk);
	release_sock(sk);
	sock_put(sk);
पूर्ण

/************************************************************************
 *
 * Receive a PPPoE Discovery frame.
 * This is solely क्रम detection of PADT frames
 *
 ***********************************************************************/
अटल पूर्णांक pppoe_disc_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)

अणु
	काष्ठा pppoe_hdr *ph;
	काष्ठा pppox_sock *po;
	काष्ठा pppoe_net *pn;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;

	अगर (skb->pkt_type != PACKET_HOST)
		जाओ पात;

	अगर (!pskb_may_pull(skb, माप(काष्ठा pppoe_hdr)))
		जाओ पात;

	ph = pppoe_hdr(skb);
	अगर (ph->code != PADT_CODE)
		जाओ पात;

	pn = pppoe_pernet(dev_net(dev));
	po = get_item(pn, ph->sid, eth_hdr(skb)->h_source, dev->अगरindex);
	अगर (po)
		अगर (!schedule_work(&po->proto.pppoe.padt_work))
			sock_put(sk_pppox(po));

पात:
	kमुक्त_skb(skb);
out:
	वापस NET_RX_SUCCESS; /* Lies... :-) */
पूर्ण

अटल काष्ठा packet_type pppoes_ptype __पढ़ो_mostly = अणु
	.type	= cpu_to_be16(ETH_P_PPP_SES),
	.func	= pppoe_rcv,
पूर्ण;

अटल काष्ठा packet_type pppoed_ptype __पढ़ो_mostly = अणु
	.type	= cpu_to_be16(ETH_P_PPP_DISC),
	.func	= pppoe_disc_rcv,
पूर्ण;

अटल काष्ठा proto pppoe_sk_proto __पढ़ो_mostly = अणु
	.name	  = "PPPOE",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा pppox_sock),
पूर्ण;

/***********************************************************************
 *
 * Initialize a new काष्ठा sock.
 *
 **********************************************************************/
अटल पूर्णांक pppoe_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	sk = sk_alloc(net, PF_PPPOX, GFP_KERNEL, &pppoe_sk_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);

	sock->state	= SS_UNCONNECTED;
	sock->ops	= &pppoe_ops;

	sk->sk_backlog_rcv	= pppoe_rcv_core;
	sk->sk_state		= PPPOX_NONE;
	sk->sk_type		= SOCK_STREAM;
	sk->sk_family		= PF_PPPOX;
	sk->sk_protocol		= PX_PROTO_OE;

	INIT_WORK(&pppox_sk(sk)->proto.pppoe.padt_work,
		  pppoe_unbind_sock_work);

	वापस 0;
पूर्ण

अटल पूर्णांक pppoe_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pppox_sock *po;
	काष्ठा pppoe_net *pn;
	काष्ठा net *net = शून्य;

	अगर (!sk)
		वापस 0;

	lock_sock(sk);
	अगर (sock_flag(sk, SOCK_DEAD)) अणु
		release_sock(sk);
		वापस -EBADF;
	पूर्ण

	po = pppox_sk(sk);

	अगर (po->pppoe_dev) अणु
		dev_put(po->pppoe_dev);
		po->pppoe_dev = शून्य;
	पूर्ण

	pppox_unbind_sock(sk);

	/* Signal the death of the socket. */
	sk->sk_state = PPPOX_DEAD;

	net = sock_net(sk);
	pn = pppoe_pernet(net);

	/*
	 * protect "po" from concurrent updates
	 * on pppoe_flush_dev
	 */
	delete_item(pn, po->pppoe_pa.sid, po->pppoe_pa.remote,
		    po->pppoe_अगरindex);

	sock_orphan(sk);
	sock->sk = शून्य;

	skb_queue_purge(&sk->sk_receive_queue);
	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक pppoe_connect(काष्ठा socket *sock, काष्ठा sockaddr *uservaddr,
		  पूर्णांक sockaddr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_pppox *sp = (काष्ठा sockaddr_pppox *)uservaddr;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा net_device *dev = शून्य;
	काष्ठा pppoe_net *pn;
	काष्ठा net *net = शून्य;
	पूर्णांक error;

	lock_sock(sk);

	error = -EINVAL;

	अगर (sockaddr_len != माप(काष्ठा sockaddr_pppox))
		जाओ end;

	अगर (sp->sa_protocol != PX_PROTO_OE)
		जाओ end;

	/* Check क्रम alपढ़ोy bound sockets */
	error = -EBUSY;
	अगर ((sk->sk_state & PPPOX_CONNECTED) &&
	     stage_session(sp->sa_addr.pppoe.sid))
		जाओ end;

	/* Check क्रम alपढ़ोy disconnected sockets, on attempts to disconnect */
	error = -EALREADY;
	अगर ((sk->sk_state & PPPOX_DEAD) &&
	     !stage_session(sp->sa_addr.pppoe.sid))
		जाओ end;

	error = 0;

	/* Delete the old binding */
	अगर (stage_session(po->pppoe_pa.sid)) अणु
		pppox_unbind_sock(sk);
		pn = pppoe_pernet(sock_net(sk));
		delete_item(pn, po->pppoe_pa.sid,
			    po->pppoe_pa.remote, po->pppoe_अगरindex);
		अगर (po->pppoe_dev) अणु
			dev_put(po->pppoe_dev);
			po->pppoe_dev = शून्य;
		पूर्ण

		po->pppoe_अगरindex = 0;
		स_रखो(&po->pppoe_pa, 0, माप(po->pppoe_pa));
		स_रखो(&po->pppoe_relay, 0, माप(po->pppoe_relay));
		स_रखो(&po->chan, 0, माप(po->chan));
		po->next = शून्य;
		po->num = 0;

		sk->sk_state = PPPOX_NONE;
	पूर्ण

	/* Re-bind in session stage only */
	अगर (stage_session(sp->sa_addr.pppoe.sid)) अणु
		error = -ENODEV;
		net = sock_net(sk);
		dev = dev_get_by_name(net, sp->sa_addr.pppoe.dev);
		अगर (!dev)
			जाओ err_put;

		po->pppoe_dev = dev;
		po->pppoe_अगरindex = dev->अगरindex;
		pn = pppoe_pernet(net);
		अगर (!(dev->flags & IFF_UP)) अणु
			जाओ err_put;
		पूर्ण

		स_नकल(&po->pppoe_pa,
		       &sp->sa_addr.pppoe,
		       माप(काष्ठा pppoe_addr));

		ग_लिखो_lock_bh(&pn->hash_lock);
		error = __set_item(pn, po);
		ग_लिखो_unlock_bh(&pn->hash_lock);
		अगर (error < 0)
			जाओ err_put;

		po->chan.hdrlen = (माप(काष्ठा pppoe_hdr) +
				   dev->hard_header_len);

		po->chan.mtu = dev->mtu - माप(काष्ठा pppoe_hdr) - 2;
		po->chan.निजी = sk;
		po->chan.ops = &pppoe_chan_ops;

		error = ppp_रेजिस्टर_net_channel(dev_net(dev), &po->chan);
		अगर (error) अणु
			delete_item(pn, po->pppoe_pa.sid,
				    po->pppoe_pa.remote, po->pppoe_अगरindex);
			जाओ err_put;
		पूर्ण

		sk->sk_state = PPPOX_CONNECTED;
	पूर्ण

	po->num = sp->sa_addr.pppoe.sid;

end:
	release_sock(sk);
	वापस error;
err_put:
	अगर (po->pppoe_dev) अणु
		dev_put(po->pppoe_dev);
		po->pppoe_dev = शून्य;
	पूर्ण
	जाओ end;
पूर्ण

अटल पूर्णांक pppoe_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		  पूर्णांक peer)
अणु
	पूर्णांक len = माप(काष्ठा sockaddr_pppox);
	काष्ठा sockaddr_pppox sp;

	sp.sa_family	= AF_PPPOX;
	sp.sa_protocol	= PX_PROTO_OE;
	स_नकल(&sp.sa_addr.pppoe, &pppox_sk(sock->sk)->pppoe_pa,
	       माप(काष्ठा pppoe_addr));

	स_नकल(uaddr, &sp, len);

	वापस len;
पूर्ण

अटल पूर्णांक pppoe_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	पूर्णांक val;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल PPPIOCGMRU:
		err = -ENXIO;
		अगर (!(sk->sk_state & PPPOX_CONNECTED))
			अवरोध;

		err = -EFAULT;
		अगर (put_user(po->pppoe_dev->mtu -
			     माप(काष्ठा pppoe_hdr) -
			     PPP_HDRLEN,
			     (पूर्णांक __user *)arg))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPIOCSMRU:
		err = -ENXIO;
		अगर (!(sk->sk_state & PPPOX_CONNECTED))
			अवरोध;

		err = -EFAULT;
		अगर (get_user(val, (पूर्णांक __user *)arg))
			अवरोध;

		अगर (val < (po->pppoe_dev->mtu
			   - माप(काष्ठा pppoe_hdr)
			   - PPP_HDRLEN))
			err = 0;
		अन्यथा
			err = -EINVAL;
		अवरोध;

	हाल PPPIOCSFLAGS:
		err = -EFAULT;
		अगर (get_user(val, (पूर्णांक __user *)arg))
			अवरोध;
		err = 0;
		अवरोध;

	हाल PPPOEIOCSFWD:
	अणु
		काष्ठा pppox_sock *relay_po;

		err = -EBUSY;
		अगर (sk->sk_state & (PPPOX_BOUND | PPPOX_DEAD))
			अवरोध;

		err = -ENOTCONN;
		अगर (!(sk->sk_state & PPPOX_CONNECTED))
			अवरोध;

		/* PPPoE address from the user specअगरies an outbound
		   PPPoE address which frames are क्रमwarded to */
		err = -EFAULT;
		अगर (copy_from_user(&po->pppoe_relay,
				   (व्योम __user *)arg,
				   माप(काष्ठा sockaddr_pppox)))
			अवरोध;

		err = -EINVAL;
		अगर (po->pppoe_relay.sa_family != AF_PPPOX ||
		    po->pppoe_relay.sa_protocol != PX_PROTO_OE)
			अवरोध;

		/* Check that the socket referenced by the address
		   actually exists. */
		relay_po = get_item_by_addr(sock_net(sk), &po->pppoe_relay);
		अगर (!relay_po)
			अवरोध;

		sock_put(sk_pppox(relay_po));
		sk->sk_state |= PPPOX_RELAY;
		err = 0;
		अवरोध;
	पूर्ण

	हाल PPPOEIOCDFWD:
		err = -EALREADY;
		अगर (!(sk->sk_state & PPPOX_RELAY))
			अवरोध;

		sk->sk_state &= ~PPPOX_RELAY;
		err = 0;
		अवरोध;

	शेष:
		err = -ENOTTY;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pppoe_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m,
			 माप_प्रकार total_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk = sock->sk;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	पूर्णांक error;
	काष्ठा pppoe_hdr hdr;
	काष्ठा pppoe_hdr *ph;
	काष्ठा net_device *dev;
	अक्षर *start;
	पूर्णांक hlen;

	lock_sock(sk);
	अगर (sock_flag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED)) अणु
		error = -ENOTCONN;
		जाओ end;
	पूर्ण

	hdr.ver = 1;
	hdr.type = 1;
	hdr.code = 0;
	hdr.sid = po->num;

	dev = po->pppoe_dev;

	error = -EMSGSIZE;
	अगर (total_len > (dev->mtu + dev->hard_header_len))
		जाओ end;

	hlen = LL_RESERVED_SPACE(dev);
	skb = sock_wदो_स्मृति(sk, hlen + माप(*ph) + total_len +
			   dev->needed_tailroom, 0, GFP_KERNEL);
	अगर (!skb) अणु
		error = -ENOMEM;
		जाओ end;
	पूर्ण

	/* Reserve space क्रम headers. */
	skb_reserve(skb, hlen);
	skb_reset_network_header(skb);

	skb->dev = dev;

	skb->priority = sk->sk_priority;
	skb->protocol = cpu_to_be16(ETH_P_PPP_SES);

	ph = skb_put(skb, total_len + माप(काष्ठा pppoe_hdr));
	start = (अक्षर *)&ph->tag[0];

	error = स_नकल_from_msg(start, m, total_len);
	अगर (error < 0) अणु
		kमुक्त_skb(skb);
		जाओ end;
	पूर्ण

	error = total_len;
	dev_hard_header(skb, dev, ETH_P_PPP_SES,
			po->pppoe_pa.remote, शून्य, total_len);

	स_नकल(ph, &hdr, माप(काष्ठा pppoe_hdr));

	ph->length = htons(total_len);

	dev_queue_xmit(skb);

end:
	release_sock(sk);
	वापस error;
पूर्ण

/************************************************************************
 *
 * xmit function क्रम पूर्णांकernal use.
 *
 ***********************************************************************/
अटल पूर्णांक __pppoe_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा net_device *dev = po->pppoe_dev;
	काष्ठा pppoe_hdr *ph;
	पूर्णांक data_len = skb->len;

	/* The higher-level PPP code (ppp_unरेजिस्टर_channel()) ensures the PPP
	 * xmit operations conclude prior to an unregistration call.  Thus
	 * sk->sk_state cannot change, so we करोn't need to करो lock_sock().
	 * But, we also can't करो a lock_sock since that पूर्णांकroduces a potential
	 * deadlock as we'd reverse the lock ordering used when calling
	 * ppp_unरेजिस्टर_channel().
	 */

	अगर (sock_flag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED))
		जाओ पात;

	अगर (!dev)
		जाओ पात;

	/* Copy the data अगर there is no space क्रम the header or अगर it's
	 * पढ़ो-only.
	 */
	अगर (skb_cow_head(skb, LL_RESERVED_SPACE(dev) + माप(*ph)))
		जाओ पात;

	__skb_push(skb, माप(*ph));
	skb_reset_network_header(skb);

	ph = pppoe_hdr(skb);
	ph->ver	= 1;
	ph->type = 1;
	ph->code = 0;
	ph->sid	= po->num;
	ph->length = htons(data_len);

	skb->protocol = cpu_to_be16(ETH_P_PPP_SES);
	skb->dev = dev;

	dev_hard_header(skb, dev, ETH_P_PPP_SES,
			po->pppoe_pa.remote, शून्य, data_len);

	dev_queue_xmit(skb);
	वापस 1;

पात:
	kमुक्त_skb(skb);
	वापस 1;
पूर्ण

/************************************************************************
 *
 * xmit function called by generic PPP driver
 * sends PPP frame over PPPoE socket
 *
 ***********************************************************************/
अटल पूर्णांक pppoe_xmit(काष्ठा ppp_channel *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)chan->निजी;
	वापस __pppoe_xmit(sk, skb);
पूर्ण

अटल पूर्णांक pppoe_fill_क्रमward_path(काष्ठा net_device_path_ctx *ctx,
				   काष्ठा net_device_path *path,
				   स्थिर काष्ठा ppp_channel *chan)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)chan->निजी;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	काष्ठा net_device *dev = po->pppoe_dev;

	अगर (sock_flag(sk, SOCK_DEAD) ||
	    !(sk->sk_state & PPPOX_CONNECTED) || !dev)
		वापस -1;

	path->type = DEV_PATH_PPPOE;
	path->encap.proto = htons(ETH_P_PPP_SES);
	path->encap.id = be16_to_cpu(po->num);
	स_नकल(path->encap.h_dest, po->pppoe_pa.remote, ETH_ALEN);
	path->dev = ctx->dev;
	ctx->dev = dev;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ppp_channel_ops pppoe_chan_ops = अणु
	.start_xmit = pppoe_xmit,
	.fill_क्रमward_path = pppoe_fill_क्रमward_path,
पूर्ण;

अटल पूर्णांक pppoe_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *m,
			 माप_प्रकार total_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक error = 0;

	अगर (sk->sk_state & PPPOX_BOUND) अणु
		error = -EIO;
		जाओ end;
	पूर्ण

	skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
				flags & MSG_DONTWAIT, &error);
	अगर (error < 0)
		जाओ end;

	अगर (skb) अणु
		total_len = min_t(माप_प्रकार, total_len, skb->len);
		error = skb_copy_datagram_msg(skb, 0, m, total_len);
		अगर (error == 0) अणु
			consume_skb(skb);
			वापस total_len;
		पूर्ण
	पूर्ण

	kमुक्त_skb(skb);
end:
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक pppoe_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा pppox_sock *po;
	अक्षर *dev_name;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Id       Address              Device\n");
		जाओ out;
	पूर्ण

	po = v;
	dev_name = po->pppoe_pa.dev;

	seq_म_लिखो(seq, "%08X %pM %8s\n",
		po->pppoe_pa.sid, po->pppoe_pa.remote, dev_name);
out:
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा pppox_sock *pppoe_get_idx(काष्ठा pppoe_net *pn, loff_t pos)
अणु
	काष्ठा pppox_sock *po;
	पूर्णांक i;

	क्रम (i = 0; i < PPPOE_HASH_SIZE; i++) अणु
		po = pn->hash_table[i];
		जबतक (po) अणु
			अगर (!pos--)
				जाओ out;
			po = po->next;
		पूर्ण
	पूर्ण

out:
	वापस po;
पूर्ण

अटल व्योम *pppoe_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(pn->hash_lock)
अणु
	काष्ठा pppoe_net *pn = pppoe_pernet(seq_file_net(seq));
	loff_t l = *pos;

	पढ़ो_lock_bh(&pn->hash_lock);
	वापस l ? pppoe_get_idx(pn, --l) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *pppoe_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा pppoe_net *pn = pppoe_pernet(seq_file_net(seq));
	काष्ठा pppox_sock *po;

	++*pos;
	अगर (v == SEQ_START_TOKEN) अणु
		po = pppoe_get_idx(pn, 0);
		जाओ out;
	पूर्ण
	po = v;
	अगर (po->next)
		po = po->next;
	अन्यथा अणु
		पूर्णांक hash = hash_item(po->pppoe_pa.sid, po->pppoe_pa.remote);

		po = शून्य;
		जबतक (++hash < PPPOE_HASH_SIZE) अणु
			po = pn->hash_table[hash];
			अगर (po)
				अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस po;
पूर्ण

अटल व्योम pppoe_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(pn->hash_lock)
अणु
	काष्ठा pppoe_net *pn = pppoe_pernet(seq_file_net(seq));
	पढ़ो_unlock_bh(&pn->hash_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations pppoe_seq_ops = अणु
	.start		= pppoe_seq_start,
	.next		= pppoe_seq_next,
	.stop		= pppoe_seq_stop,
	.show		= pppoe_seq_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल स्थिर काष्ठा proto_ops pppoe_ops = अणु
	.family		= AF_PPPOX,
	.owner		= THIS_MODULE,
	.release	= pppoe_release,
	.bind		= sock_no_bind,
	.connect	= pppoe_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.getname	= pppoe_getname,
	.poll		= datagram_poll,
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.sendmsg	= pppoe_sendmsg,
	.recvmsg	= pppoe_recvmsg,
	.mmap		= sock_no_mmap,
	.ioctl		= pppox_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= pppox_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pppox_proto pppoe_proto = अणु
	.create	= pppoe_create,
	.ioctl	= pppoe_ioctl,
	.owner	= THIS_MODULE,
पूर्ण;

अटल __net_init पूर्णांक pppoe_init_net(काष्ठा net *net)
अणु
	काष्ठा pppoe_net *pn = pppoe_pernet(net);
	काष्ठा proc_dir_entry *pde;

	rwlock_init(&pn->hash_lock);

	pde = proc_create_net("pppoe", 0444, net->proc_net,
			&pppoe_seq_ops, माप(काष्ठा seq_net_निजी));
#अगर_घोषित CONFIG_PROC_FS
	अगर (!pde)
		वापस -ENOMEM;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल __net_निकास व्योम pppoe_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("pppoe", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations pppoe_net_ops = अणु
	.init = pppoe_init_net,
	.निकास = pppoe_निकास_net,
	.id   = &pppoe_net_id,
	.size = माप(काष्ठा pppoe_net),
पूर्ण;

अटल पूर्णांक __init pppoe_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_device(&pppoe_net_ops);
	अगर (err)
		जाओ out;

	err = proto_रेजिस्टर(&pppoe_sk_proto, 0);
	अगर (err)
		जाओ out_unरेजिस्टर_net_ops;

	err = रेजिस्टर_pppox_proto(PX_PROTO_OE, &pppoe_proto);
	अगर (err)
		जाओ out_unरेजिस्टर_pppoe_proto;

	dev_add_pack(&pppoes_ptype);
	dev_add_pack(&pppoed_ptype);
	रेजिस्टर_netdevice_notअगरier(&pppoe_notअगरier);

	वापस 0;

out_unरेजिस्टर_pppoe_proto:
	proto_unरेजिस्टर(&pppoe_sk_proto);
out_unरेजिस्टर_net_ops:
	unरेजिस्टर_pernet_device(&pppoe_net_ops);
out:
	वापस err;
पूर्ण

अटल व्योम __निकास pppoe_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&pppoe_notअगरier);
	dev_हटाओ_pack(&pppoed_ptype);
	dev_हटाओ_pack(&pppoes_ptype);
	unरेजिस्टर_pppox_proto(PX_PROTO_OE);
	proto_unरेजिस्टर(&pppoe_sk_proto);
	unरेजिस्टर_pernet_device(&pppoe_net_ops);
पूर्ण

module_init(pppoe_init);
module_निकास(pppoe_निकास);

MODULE_AUTHOR("Michal Ostrowski <mostrows@speakeasy.net>");
MODULE_DESCRIPTION("PPP over Ethernet driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO(PF_PPPOX, PX_PROTO_OE);

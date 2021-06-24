<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Socket Layer Interface
 *
 * Authors:     Eduarकरो Marcelo Serrat <emserrat@geocities.com>
 *              Patrick Caulfield <patrick@pandh.demon.co.uk>
 *
 * Changes:
 *        Steve Whitehouse: Copied from Eduarकरो Serrat and Patrick Caulfield's
 *                          version of the code. Original copyright preserved
 *                          below.
 *        Steve Whitehouse: Some bug fixes, cleaning up some code to make it
 *                          compatible with my routing layer.
 *        Steve Whitehouse: Merging changes from Eduarकरो Serrat and Patrick
 *                          Caulfield.
 *        Steve Whitehouse: Further bug fixes, checking module code still works
 *                          with new routing layer.
 *        Steve Whitehouse: Additional set/get_sockopt() calls.
 *        Steve Whitehouse: Fixed TIOCINQ ioctl to be same as Eduarकरो's new
 *                          code.
 *        Steve Whitehouse: recvmsg() changed to try and behave in a POSIX like
 *                          way. Didn't manage it entirely, but its better.
 *        Steve Whitehouse: ditto क्रम sendmsg().
 *        Steve Whitehouse: A selection of bug fixes to various things.
 *        Steve Whitehouse: Added TIOCOUTQ ioctl.
 *        Steve Whitehouse: Fixes to username2sockaddr & sockaddr2username.
 *        Steve Whitehouse: Fixes to connect() error वापसs.
 *       Patrick Caulfield: Fixes to delayed acceptance logic.
 *         David S. Miller: New socket locking
 *        Steve Whitehouse: Socket list hashing/locking
 *         Arnalकरो C. Melo: use capable, not suser
 *        Steve Whitehouse: Removed unused code. Fix to use sk->allocation
 *                          when required.
 *       Patrick Caulfield: /proc/net/decnet now has object name/number
 *        Steve Whitehouse: Fixed local port allocation, hashed sk list
 *          Matthew Wilcox: Fixes क्रम dn_ioctl()
 *        Steve Whitehouse: New connect/accept logic to allow समयouts and
 *                          prepare क्रम sendpage etc.
 */


/******************************************************************************
    (c) 1995-1998 E.M. Serrat		emserrat@geocities.com


HISTORY:

Version           Kernel     Date       Author/Comments
-------           ------     ----       ---------------
Version 0.0.1     2.0.30    01-dic-97	Eduarकरो Marcelo Serrat
					(emserrat@geocities.com)

					First Development of DECnet Socket La-
					yer क्रम Linux. Only supports outgoing
					connections.

Version 0.0.2	  2.1.105   20-jun-98   Patrick J. Caulfield
					(patrick@pandh.demon.co.uk)

					Port to new kernel development version.

Version 0.0.3     2.1.106   25-jun-98   Eduarकरो Marcelo Serrat
					(emserrat@geocities.com)
					_
					Added support क्रम incoming connections
					so we can start developing server apps
					on Linux.
					-
					Module Support
Version 0.0.4     2.1.109   21-jul-98   Eduarकरो Marcelo Serrat
				       (emserrat@geocities.com)
				       _
					Added support क्रम X11R6.4. Now we can
					use DECnet transport क्रम X on Linux!!!
				       -
Version 0.0.5    2.1.110   01-aug-98   Eduarकरो Marcelo Serrat
				       (emserrat@geocities.com)
				       Removed bugs on flow control
				       Removed bugs on incoming accessdata
				       order
				       -
Version 0.0.6    2.1.110   07-aug-98   Eduarकरो Marcelo Serrat
				       dn_recvmsg fixes

					Patrick J. Caulfield
				       dn_bind fixes
*******************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/route.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/seq_file.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/flow.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <linux/capability.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/jअगरfies.h>
#समावेश <net/net_namespace.h>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/fib_rules.h>
#समावेश <net/tcp.h>
#समावेश <net/dn.h>
#समावेश <net/dn_nsp.h>
#समावेश <net/dn_dev.h>
#समावेश <net/dn_route.h>
#समावेश <net/dn_fib.h>
#समावेश <net/dn_neigh.h>

काष्ठा dn_sock अणु
	काष्ठा sock sk;
	काष्ठा dn_scp scp;
पूर्ण;

अटल व्योम dn_keepalive(काष्ठा sock *sk);

#घोषणा DN_SK_HASH_SHIFT 8
#घोषणा DN_SK_HASH_SIZE (1 << DN_SK_HASH_SHIFT)
#घोषणा DN_SK_HASH_MASK (DN_SK_HASH_SIZE - 1)


अटल स्थिर काष्ठा proto_ops dn_proto_ops;
अटल DEFINE_RWLOCK(dn_hash_lock);
अटल काष्ठा hlist_head dn_sk_hash[DN_SK_HASH_SIZE];
अटल काष्ठा hlist_head dn_wild_sk;
अटल atomic_दीर्घ_t decnet_memory_allocated;

अटल पूर्णांक __dn_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen, पूर्णांक flags);
अटल पूर्णांक __dn_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen, पूर्णांक flags);

अटल काष्ठा hlist_head *dn_find_list(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	अगर (scp->addr.sdn_flags & SDF_WILD)
		वापस hlist_empty(&dn_wild_sk) ? &dn_wild_sk : शून्य;

	वापस &dn_sk_hash[le16_to_cpu(scp->addrloc) & DN_SK_HASH_MASK];
पूर्ण

/*
 * Valid ports are those greater than zero and not alपढ़ोy in use.
 */
अटल पूर्णांक check_port(__le16 port)
अणु
	काष्ठा sock *sk;

	अगर (port == 0)
		वापस -1;

	sk_क्रम_each(sk, &dn_sk_hash[le16_to_cpu(port) & DN_SK_HASH_MASK]) अणु
		काष्ठा dn_scp *scp = DN_SK(sk);
		अगर (scp->addrloc == port)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित लघु port_alloc(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	अटल अचिन्हित लघु port = 0x2000;
	अचिन्हित लघु i_port = port;

	जबतक(check_port(cpu_to_le16(++port)) != 0) अणु
		अगर (port == i_port)
			वापस 0;
	पूर्ण

	scp->addrloc = cpu_to_le16(port);

	वापस 1;
पूर्ण

/*
 * Since this is only ever called from user
 * level, we करोn't need a ग_लिखो_lock() version
 * of this.
 */
अटल पूर्णांक dn_hash_sock(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा hlist_head *list;
	पूर्णांक rv = -EUSERS;

	BUG_ON(sk_hashed(sk));

	ग_लिखो_lock_bh(&dn_hash_lock);

	अगर (!scp->addrloc && !port_alloc(sk))
		जाओ out;

	rv = -EADDRINUSE;
	अगर ((list = dn_find_list(sk)) == शून्य)
		जाओ out;

	sk_add_node(sk, list);
	rv = 0;
out:
	ग_लिखो_unlock_bh(&dn_hash_lock);
	वापस rv;
पूर्ण

अटल व्योम dn_unhash_sock(काष्ठा sock *sk)
अणु
	ग_लिखो_lock(&dn_hash_lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock(&dn_hash_lock);
पूर्ण

अटल व्योम dn_unhash_sock_bh(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&dn_hash_lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&dn_hash_lock);
पूर्ण

अटल काष्ठा hlist_head *listen_hash(काष्ठा sockaddr_dn *addr)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक hash = addr->sdn_objnum;

	अगर (hash == 0) अणु
		hash = addr->sdn_objnamel;
		क्रम(i = 0; i < le16_to_cpu(addr->sdn_objnamel); i++) अणु
			hash ^= addr->sdn_objname[i];
			hash ^= (hash << 3);
		पूर्ण
	पूर्ण

	वापस &dn_sk_hash[hash & DN_SK_HASH_MASK];
पूर्ण

/*
 * Called to transक्रमm a socket from bound (i.e. with a local address)
 * पूर्णांकo a listening socket (करोesn't need a local port number) and rehashes
 * based upon the object name/number.
 */
अटल व्योम dn_rehash_sock(काष्ठा sock *sk)
अणु
	काष्ठा hlist_head *list;
	काष्ठा dn_scp *scp = DN_SK(sk);

	अगर (scp->addr.sdn_flags & SDF_WILD)
		वापस;

	ग_लिखो_lock_bh(&dn_hash_lock);
	sk_del_node_init(sk);
	DN_SK(sk)->addrloc = 0;
	list = listen_hash(&DN_SK(sk)->addr);
	sk_add_node(sk, list);
	ग_लिखो_unlock_bh(&dn_hash_lock);
पूर्ण

पूर्णांक dn_sockaddr2username(काष्ठा sockaddr_dn *sdn, अचिन्हित अक्षर *buf, अचिन्हित अक्षर type)
अणु
	पूर्णांक len = 2;

	*buf++ = type;

	चयन (type) अणु
	हाल 0:
		*buf++ = sdn->sdn_objnum;
		अवरोध;
	हाल 1:
		*buf++ = 0;
		*buf++ = le16_to_cpu(sdn->sdn_objnamel);
		स_नकल(buf, sdn->sdn_objname, le16_to_cpu(sdn->sdn_objnamel));
		len = 3 + le16_to_cpu(sdn->sdn_objnamel);
		अवरोध;
	हाल 2:
		स_रखो(buf, 0, 5);
		buf += 5;
		*buf++ = le16_to_cpu(sdn->sdn_objnamel);
		स_नकल(buf, sdn->sdn_objname, le16_to_cpu(sdn->sdn_objnamel));
		len = 7 + le16_to_cpu(sdn->sdn_objnamel);
		अवरोध;
	पूर्ण

	वापस len;
पूर्ण

/*
 * On reception of usernames, we handle types 1 and 0 क्रम destination
 * addresses only. Types 2 and 4 are used क्रम source addresses, but the
 * UIC, GIC are ignored and they are both treated the same way. Type 3
 * is never used as I've no idea what its purpose might be or what its
 * क्रमmat is.
 */
पूर्णांक dn_username2sockaddr(अचिन्हित अक्षर *data, पूर्णांक len, काष्ठा sockaddr_dn *sdn, अचिन्हित अक्षर *fmt)
अणु
	अचिन्हित अक्षर type;
	पूर्णांक size = len;
	पूर्णांक namel = 12;

	sdn->sdn_objnum = 0;
	sdn->sdn_objnamel = cpu_to_le16(0);
	स_रखो(sdn->sdn_objname, 0, DN_MAXOBJL);

	अगर (len < 2)
		वापस -1;

	len -= 2;
	*fmt = *data++;
	type = *data++;

	चयन (*fmt) अणु
	हाल 0:
		sdn->sdn_objnum = type;
		वापस 2;
	हाल 1:
		namel = 16;
		अवरोध;
	हाल 2:
		len  -= 4;
		data += 4;
		अवरोध;
	हाल 4:
		len  -= 8;
		data += 8;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	len -= 1;

	अगर (len < 0)
		वापस -1;

	sdn->sdn_objnamel = cpu_to_le16(*data++);
	len -= le16_to_cpu(sdn->sdn_objnamel);

	अगर ((len < 0) || (le16_to_cpu(sdn->sdn_objnamel) > namel))
		वापस -1;

	स_नकल(sdn->sdn_objname, data, le16_to_cpu(sdn->sdn_objnamel));

	वापस size - len;
पूर्ण

काष्ठा sock *dn_sklist_find_listener(काष्ठा sockaddr_dn *addr)
अणु
	काष्ठा hlist_head *list = listen_hash(addr);
	काष्ठा sock *sk;

	पढ़ो_lock(&dn_hash_lock);
	sk_क्रम_each(sk, list) अणु
		काष्ठा dn_scp *scp = DN_SK(sk);
		अगर (sk->sk_state != TCP_LISTEN)
			जारी;
		अगर (scp->addr.sdn_objnum) अणु
			अगर (scp->addr.sdn_objnum != addr->sdn_objnum)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (addr->sdn_objnum)
				जारी;
			अगर (scp->addr.sdn_objnamel != addr->sdn_objnamel)
				जारी;
			अगर (स_भेद(scp->addr.sdn_objname, addr->sdn_objname, le16_to_cpu(addr->sdn_objnamel)) != 0)
				जारी;
		पूर्ण
		sock_hold(sk);
		पढ़ो_unlock(&dn_hash_lock);
		वापस sk;
	पूर्ण

	sk = sk_head(&dn_wild_sk);
	अगर (sk) अणु
		अगर (sk->sk_state == TCP_LISTEN)
			sock_hold(sk);
		अन्यथा
			sk = शून्य;
	पूर्ण

	पढ़ो_unlock(&dn_hash_lock);
	वापस sk;
पूर्ण

काष्ठा sock *dn_find_by_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
	काष्ठा sock *sk;
	काष्ठा dn_scp *scp;

	पढ़ो_lock(&dn_hash_lock);
	sk_क्रम_each(sk, &dn_sk_hash[le16_to_cpu(cb->dst_port) & DN_SK_HASH_MASK]) अणु
		scp = DN_SK(sk);
		अगर (cb->src != dn_saddr2dn(&scp->peer))
			जारी;
		अगर (cb->dst_port != scp->addrloc)
			जारी;
		अगर (scp->addrrem && (cb->src_port != scp->addrrem))
			जारी;
		sock_hold(sk);
		जाओ found;
	पूर्ण
	sk = शून्य;
found:
	पढ़ो_unlock(&dn_hash_lock);
	वापस sk;
पूर्ण



अटल व्योम dn_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	skb_queue_purge(&scp->data_xmit_queue);
	skb_queue_purge(&scp->other_xmit_queue);
	skb_queue_purge(&scp->other_receive_queue);

	dst_release(rcu_dereference_रक्षित(sk->sk_dst_cache, 1));
पूर्ण

अटल अचिन्हित दीर्घ dn_memory_pressure;

अटल व्योम dn_enter_memory_pressure(काष्ठा sock *sk)
अणु
	अगर (!dn_memory_pressure) अणु
		dn_memory_pressure = 1;
	पूर्ण
पूर्ण

अटल काष्ठा proto dn_proto = अणु
	.name			= "NSP",
	.owner			= THIS_MODULE,
	.enter_memory_pressure	= dn_enter_memory_pressure,
	.memory_pressure	= &dn_memory_pressure,
	.memory_allocated	= &decnet_memory_allocated,
	.sysctl_mem		= sysctl_decnet_mem,
	.sysctl_wmem		= sysctl_decnet_wmem,
	.sysctl_rmem		= sysctl_decnet_rmem,
	.max_header		= DN_MAX_NSP_DATA_HEADER + 64,
	.obj_size		= माप(काष्ठा dn_sock),
पूर्ण;

अटल काष्ठा sock *dn_alloc_sock(काष्ठा net *net, काष्ठा socket *sock, gfp_t gfp, पूर्णांक kern)
अणु
	काष्ठा dn_scp *scp;
	काष्ठा sock *sk = sk_alloc(net, PF_DECnet, gfp, &dn_proto, kern);

	अगर  (!sk)
		जाओ out;

	अगर (sock)
		sock->ops = &dn_proto_ops;
	sock_init_data(sock, sk);

	sk->sk_backlog_rcv = dn_nsp_backlog_rcv;
	sk->sk_deकाष्ठा    = dn_deकाष्ठा;
	sk->sk_no_check_tx = 1;
	sk->sk_family      = PF_DECnet;
	sk->sk_protocol    = 0;
	sk->sk_allocation  = gfp;
	sk->sk_sndbuf	   = sysctl_decnet_wmem[1];
	sk->sk_rcvbuf	   = sysctl_decnet_rmem[1];

	/* Initialization of DECnet Session Control Port		*/
	scp = DN_SK(sk);
	scp->state	= DN_O;		/* Open			*/
	scp->numdat	= 1;		/* Next data seg to tx	*/
	scp->numoth	= 1;		/* Next oth data to tx  */
	scp->ackxmt_dat = 0;		/* Last data seg ack'ed */
	scp->ackxmt_oth = 0;		/* Last oth data ack'ed */
	scp->ackrcv_dat = 0;		/* Highest data ack recv*/
	scp->ackrcv_oth = 0;		/* Last oth data ack rec*/
	scp->flowrem_sw = DN_SEND;
	scp->flowloc_sw = DN_SEND;
	scp->flowrem_dat = 0;
	scp->flowrem_oth = 1;
	scp->flowloc_dat = 0;
	scp->flowloc_oth = 1;
	scp->services_rem = 0;
	scp->services_loc = 1 | NSP_FC_NONE;
	scp->info_rem = 0;
	scp->info_loc = 0x03; /* NSP version 4.1 */
	scp->segsize_rem = 230 - DN_MAX_NSP_DATA_HEADER; /* Default: Updated by remote segsize */
	scp->nonagle = 0;
	scp->multi_ireq = 1;
	scp->accept_mode = ACC_IMMED;
	scp->addr.sdn_family    = AF_DECnet;
	scp->peer.sdn_family    = AF_DECnet;
	scp->accessdata.acc_accl = 5;
	स_नकल(scp->accessdata.acc_acc, "LINUX", 5);

	scp->max_winकरोw   = NSP_MAX_WINDOW;
	scp->snd_winकरोw   = NSP_MIN_WINDOW;
	scp->nsp_srtt     = NSP_INITIAL_SRTT;
	scp->nsp_rttvar   = NSP_INITIAL_RTTVAR;
	scp->nsp_rxtshअगरt = 0;

	skb_queue_head_init(&scp->data_xmit_queue);
	skb_queue_head_init(&scp->other_xmit_queue);
	skb_queue_head_init(&scp->other_receive_queue);

	scp->persist = 0;
	scp->persist_fxn = शून्य;
	scp->keepalive = 10 * HZ;
	scp->keepalive_fxn = dn_keepalive;

	dn_start_slow_समयr(sk);
out:
	वापस sk;
पूर्ण

/*
 * Keepalive समयr.
 * FIXME: Should respond to SO_KEEPALIVE etc.
 */
अटल व्योम dn_keepalive(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	/*
	 * By checking the other_data transmit queue is empty
	 * we are द्विगुन checking that we are not sending too
	 * many of these keepalive frames.
	 */
	अगर (skb_queue_empty(&scp->other_xmit_queue))
		dn_nsp_send_link(sk, DN_NOCHANGE, 0);
पूर्ण


/*
 * Timer क्रम shutकरोwn/destroyed sockets.
 * When socket is dead & no packets have been sent क्रम a
 * certain amount of समय, they are हटाओd by this
 * routine. Also takes care of sending out DI & DC
 * frames at correct बार.
 */
पूर्णांक dn_destroy_समयr(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	scp->persist = dn_nsp_persist(sk);

	चयन (scp->state) अणु
	हाल DN_DI:
		dn_nsp_send_disc(sk, NSP_DISCINIT, 0, GFP_ATOMIC);
		अगर (scp->nsp_rxtshअगरt >= decnet_di_count)
			scp->state = DN_CN;
		वापस 0;

	हाल DN_DR:
		dn_nsp_send_disc(sk, NSP_DISCINIT, 0, GFP_ATOMIC);
		अगर (scp->nsp_rxtshअगरt >= decnet_dr_count)
			scp->state = DN_DRC;
		वापस 0;

	हाल DN_DN:
		अगर (scp->nsp_rxtshअगरt < decnet_dn_count) अणु
			/* prपूर्णांकk(KERN_DEBUG "dn_destroy_timer: DN\n"); */
			dn_nsp_send_disc(sk, NSP_DISCCONF, NSP_REASON_DC,
					 GFP_ATOMIC);
			वापस 0;
		पूर्ण
	पूर्ण

	scp->persist = (HZ * decnet_समय_रुको);

	अगर (sk->sk_socket)
		वापस 0;

	अगर (समय_after_eq(jअगरfies, scp->stamp + HZ * decnet_समय_रुको)) अणु
		dn_unhash_sock(sk);
		sock_put(sk);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dn_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	scp->nsp_rxtshअगरt = 0; /* reset back off */

	अगर (sk->sk_socket) अणु
		अगर (sk->sk_socket->state != SS_UNCONNECTED)
			sk->sk_socket->state = SS_DISCONNECTING;
	पूर्ण

	sk->sk_state = TCP_CLOSE;

	चयन (scp->state) अणु
	हाल DN_DN:
		dn_nsp_send_disc(sk, NSP_DISCCONF, NSP_REASON_DC,
				 sk->sk_allocation);
		scp->persist_fxn = dn_destroy_समयr;
		scp->persist = dn_nsp_persist(sk);
		अवरोध;
	हाल DN_CR:
		scp->state = DN_DR;
		जाओ disc_reject;
	हाल DN_RUN:
		scp->state = DN_DI;
		fallthrough;
	हाल DN_DI:
	हाल DN_DR:
disc_reject:
		dn_nsp_send_disc(sk, NSP_DISCINIT, 0, sk->sk_allocation);
		fallthrough;
	हाल DN_NC:
	हाल DN_NR:
	हाल DN_RJ:
	हाल DN_DIC:
	हाल DN_CN:
	हाल DN_DRC:
	हाल DN_CI:
	हाल DN_CD:
		scp->persist_fxn = dn_destroy_समयr;
		scp->persist = dn_nsp_persist(sk);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "DECnet: dn_destroy_sock passed socket in invalid state\n");
		fallthrough;
	हाल DN_O:
		dn_stop_slow_समयr(sk);

		dn_unhash_sock_bh(sk);
		sock_put(sk);

		अवरोध;
	पूर्ण
पूर्ण

अक्षर *dn_addr2asc(__u16 addr, अक्षर *buf)
अणु
	अचिन्हित लघु node, area;

	node = addr & 0x03ff;
	area = addr >> 10;
	प्र_लिखो(buf, "%hd.%hd", area, node);

	वापस buf;
पूर्ण



अटल पूर्णांक dn_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		     पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	अगर (protocol < 0 || protocol > U8_MAX)
		वापस -EINVAL;

	अगर (!net_eq(net, &init_net))
		वापस -EAFNOSUPPORT;

	चयन (sock->type) अणु
	हाल SOCK_SEQPACKET:
		अगर (protocol != DNPROTO_NSP)
			वापस -EPROTONOSUPPORT;
		अवरोध;
	हाल SOCK_STREAM:
		अवरोध;
	शेष:
		वापस -ESOCKTNOSUPPORT;
	पूर्ण


	अगर ((sk = dn_alloc_sock(net, sock, GFP_KERNEL, kern)) == शून्य)
		वापस -ENOBUFS;

	sk->sk_protocol = protocol;

	वापस 0;
पूर्ण


अटल पूर्णांक
dn_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk) अणु
		sock_orphan(sk);
		sock_hold(sk);
		lock_sock(sk);
		dn_destroy_sock(sk);
		release_sock(sk);
		sock_put(sk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dn_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा sockaddr_dn *saddr = (काष्ठा sockaddr_dn *)uaddr;
	काष्ठा net_device *dev, *ldev;
	पूर्णांक rv;

	अगर (addr_len != माप(काष्ठा sockaddr_dn))
		वापस -EINVAL;

	अगर (saddr->sdn_family != AF_DECnet)
		वापस -EINVAL;

	अगर (le16_to_cpu(saddr->sdn_nodeaddrl) && (le16_to_cpu(saddr->sdn_nodeaddrl) != 2))
		वापस -EINVAL;

	अगर (le16_to_cpu(saddr->sdn_objnamel) > DN_MAXOBJL)
		वापस -EINVAL;

	अगर (saddr->sdn_flags & ~SDF_WILD)
		वापस -EINVAL;

	अगर (!capable(CAP_NET_BIND_SERVICE) && (saddr->sdn_objnum ||
	    (saddr->sdn_flags & SDF_WILD)))
		वापस -EACCES;

	अगर (!(saddr->sdn_flags & SDF_WILD)) अणु
		अगर (le16_to_cpu(saddr->sdn_nodeaddrl)) अणु
			rcu_पढ़ो_lock();
			ldev = शून्य;
			क्रम_each_netdev_rcu(&init_net, dev) अणु
				अगर (!dev->dn_ptr)
					जारी;
				अगर (dn_dev_islocal(dev, dn_saddr2dn(saddr))) अणु
					ldev = dev;
					अवरोध;
				पूर्ण
			पूर्ण
			rcu_पढ़ो_unlock();
			अगर (ldev == शून्य)
				वापस -EADDRNOTAVAIL;
		पूर्ण
	पूर्ण

	rv = -EINVAL;
	lock_sock(sk);
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		स_नकल(&scp->addr, saddr, addr_len);
		sock_reset_flag(sk, SOCK_ZAPPED);

		rv = dn_hash_sock(sk);
		अगर (rv)
			sock_set_flag(sk, SOCK_ZAPPED);
	पूर्ण
	release_sock(sk);

	वापस rv;
पूर्ण


अटल पूर्णांक dn_स्वतः_bind(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	पूर्णांक rv;

	sock_reset_flag(sk, SOCK_ZAPPED);

	scp->addr.sdn_flags  = 0;
	scp->addr.sdn_objnum = 0;

	/*
	 * This stuff is to keep compatibility with Eduarकरो's
	 * patch. I hope I can dispense with it लघुly...
	 */
	अगर ((scp->accessdata.acc_accl != 0) &&
		(scp->accessdata.acc_accl <= 12)) अणु

		scp->addr.sdn_objnamel = cpu_to_le16(scp->accessdata.acc_accl);
		स_नकल(scp->addr.sdn_objname, scp->accessdata.acc_acc, le16_to_cpu(scp->addr.sdn_objnamel));

		scp->accessdata.acc_accl = 0;
		स_रखो(scp->accessdata.acc_acc, 0, 40);
	पूर्ण
	/* End of compatibility stuff */

	scp->addr.sdn_add.a_len = cpu_to_le16(2);
	rv = dn_dev_bind_शेष((__le16 *)scp->addr.sdn_add.a_addr);
	अगर (rv == 0) अणु
		rv = dn_hash_sock(sk);
		अगर (rv)
			sock_set_flag(sk, SOCK_ZAPPED);
	पूर्ण

	वापस rv;
पूर्ण

अटल पूर्णांक dn_confirm_accept(काष्ठा sock *sk, दीर्घ *समयo, gfp_t allocation)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	DEFINE_WAIT(रुको);
	पूर्णांक err;

	अगर (scp->state != DN_CR)
		वापस -EINVAL;

	scp->state = DN_CC;
	scp->segsize_loc = dst_metric_advmss(__sk_dst_get(sk));
	dn_send_conn_conf(sk, allocation);

	prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	क्रम(;;) अणु
		release_sock(sk);
		अगर (scp->state == DN_CC)
			*समयo = schedule_समयout(*समयo);
		lock_sock(sk);
		err = 0;
		अगर (scp->state == DN_RUN)
			अवरोध;
		err = sock_error(sk);
		अगर (err)
			अवरोध;
		err = sock_पूर्णांकr_त्रुटि_सं(*समयo);
		अगर (संकेत_pending(current))
			अवरोध;
		err = -EAGAIN;
		अगर (!*समयo)
			अवरोध;
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	अगर (err == 0) अणु
		sk->sk_socket->state = SS_CONNECTED;
	पूर्ण अन्यथा अगर (scp->state != DN_CC) अणु
		sk->sk_socket->state = SS_UNCONNECTED;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक dn_रुको_run(काष्ठा sock *sk, दीर्घ *समयo)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	DEFINE_WAIT(रुको);
	पूर्णांक err = 0;

	अगर (scp->state == DN_RUN)
		जाओ out;

	अगर (!*समयo)
		वापस -EALREADY;

	prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	क्रम(;;) अणु
		release_sock(sk);
		अगर (scp->state == DN_CI || scp->state == DN_CC)
			*समयo = schedule_समयout(*समयo);
		lock_sock(sk);
		err = 0;
		अगर (scp->state == DN_RUN)
			अवरोध;
		err = sock_error(sk);
		अगर (err)
			अवरोध;
		err = sock_पूर्णांकr_त्रुटि_सं(*समयo);
		अगर (संकेत_pending(current))
			अवरोध;
		err = -ETIMEDOUT;
		अगर (!*समयo)
			अवरोध;
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
out:
	अगर (err == 0) अणु
		sk->sk_socket->state = SS_CONNECTED;
	पूर्ण अन्यथा अगर (scp->state != DN_CI && scp->state != DN_CC) अणु
		sk->sk_socket->state = SS_UNCONNECTED;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __dn_connect(काष्ठा sock *sk, काष्ठा sockaddr_dn *addr, पूर्णांक addrlen, दीर्घ *समयo, पूर्णांक flags)
अणु
	काष्ठा socket *sock = sk->sk_socket;
	काष्ठा dn_scp *scp = DN_SK(sk);
	पूर्णांक err = -EISCONN;
	काष्ठा flowidn fld;
	काष्ठा dst_entry *dst;

	अगर (sock->state == SS_CONNECTED)
		जाओ out;

	अगर (sock->state == SS_CONNECTING) अणु
		err = 0;
		अगर (scp->state == DN_RUN) अणु
			sock->state = SS_CONNECTED;
			जाओ out;
		पूर्ण
		err = -ECONNREFUSED;
		अगर (scp->state != DN_CI && scp->state != DN_CC) अणु
			sock->state = SS_UNCONNECTED;
			जाओ out;
		पूर्ण
		वापस dn_रुको_run(sk, समयo);
	पूर्ण

	err = -EINVAL;
	अगर (scp->state != DN_O)
		जाओ out;

	अगर (addr == शून्य || addrlen != माप(काष्ठा sockaddr_dn))
		जाओ out;
	अगर (addr->sdn_family != AF_DECnet)
		जाओ out;
	अगर (addr->sdn_flags & SDF_WILD)
		जाओ out;

	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		err = dn_स्वतः_bind(sk->sk_socket);
		अगर (err)
			जाओ out;
	पूर्ण

	स_नकल(&scp->peer, addr, माप(काष्ठा sockaddr_dn));

	err = -EHOSTUNREACH;
	स_रखो(&fld, 0, माप(fld));
	fld.flowidn_oअगर = sk->sk_bound_dev_अगर;
	fld.daddr = dn_saddr2dn(&scp->peer);
	fld.saddr = dn_saddr2dn(&scp->addr);
	dn_sk_ports_copy(&fld, scp);
	fld.flowidn_proto = DNPROTO_NSP;
	अगर (dn_route_output_sock(&sk->sk_dst_cache, &fld, sk, flags) < 0)
		जाओ out;
	dst = __sk_dst_get(sk);
	sk->sk_route_caps = dst->dev->features;
	sock->state = SS_CONNECTING;
	scp->state = DN_CI;
	scp->segsize_loc = dst_metric_advmss(dst);

	dn_nsp_send_conninit(sk, NSP_CI);
	err = -EINPROGRESS;
	अगर (*समयo) अणु
		err = dn_रुको_run(sk, समयo);
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक dn_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addrlen, पूर्णांक flags)
अणु
	काष्ठा sockaddr_dn *addr = (काष्ठा sockaddr_dn *)uaddr;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;
	दीर्घ समयo = sock_sndसमयo(sk, flags & O_NONBLOCK);

	lock_sock(sk);
	err = __dn_connect(sk, addr, addrlen, &समयo, 0);
	release_sock(sk);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक dn_check_state(काष्ठा sock *sk, काष्ठा sockaddr_dn *addr, पूर्णांक addrlen, दीर्घ *समयo, पूर्णांक flags)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);

	चयन (scp->state) अणु
	हाल DN_RUN:
		वापस 0;
	हाल DN_CR:
		वापस dn_confirm_accept(sk, समयo, sk->sk_allocation);
	हाल DN_CI:
	हाल DN_CC:
		वापस dn_रुको_run(sk, समयo);
	हाल DN_O:
		वापस __dn_connect(sk, addr, addrlen, समयo, flags);
	पूर्ण

	वापस -EINVAL;
पूर्ण


अटल व्योम dn_access_copy(काष्ठा sk_buff *skb, काष्ठा accessdata_dn *acc)
अणु
	अचिन्हित अक्षर *ptr = skb->data;

	acc->acc_userl = *ptr++;
	स_नकल(&acc->acc_user, ptr, acc->acc_userl);
	ptr += acc->acc_userl;

	acc->acc_passl = *ptr++;
	स_नकल(&acc->acc_pass, ptr, acc->acc_passl);
	ptr += acc->acc_passl;

	acc->acc_accl = *ptr++;
	स_नकल(&acc->acc_acc, ptr, acc->acc_accl);

	skb_pull(skb, acc->acc_accl + acc->acc_passl + acc->acc_userl + 3);

पूर्ण

अटल व्योम dn_user_copy(काष्ठा sk_buff *skb, काष्ठा optdata_dn *opt)
अणु
	अचिन्हित अक्षर *ptr = skb->data;
	u16 len = *ptr++; /* yes, it's 8bit on the wire */

	BUG_ON(len > 16); /* we've checked the contents earlier */
	opt->opt_optl   = cpu_to_le16(len);
	opt->opt_status = 0;
	स_नकल(opt->opt_data, ptr, len);
	skb_pull(skb, len + 1);
पूर्ण

अटल काष्ठा sk_buff *dn_रुको_क्रम_connect(काष्ठा sock *sk, दीर्घ *समयo)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक err = 0;

	prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	क्रम(;;) अणु
		release_sock(sk);
		skb = skb_dequeue(&sk->sk_receive_queue);
		अगर (skb == शून्य) अणु
			*समयo = schedule_समयout(*समयo);
			skb = skb_dequeue(&sk->sk_receive_queue);
		पूर्ण
		lock_sock(sk);
		अगर (skb != शून्य)
			अवरोध;
		err = -EINVAL;
		अगर (sk->sk_state != TCP_LISTEN)
			अवरोध;
		err = sock_पूर्णांकr_त्रुटि_सं(*समयo);
		अगर (संकेत_pending(current))
			अवरोध;
		err = -EAGAIN;
		अगर (!*समयo)
			अवरोध;
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);

	वापस skb == शून्य ? ERR_PTR(err) : skb;
पूर्ण

अटल पूर्णांक dn_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		     bool kern)
अणु
	काष्ठा sock *sk = sock->sk, *newsk;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा dn_skb_cb *cb;
	अचिन्हित अक्षर menuver;
	पूर्णांक err = 0;
	अचिन्हित अक्षर type;
	दीर्घ समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);
	काष्ठा dst_entry *dst;

	lock_sock(sk);

	अगर (sk->sk_state != TCP_LISTEN || DN_SK(sk)->state != DN_O) अणु
		release_sock(sk);
		वापस -EINVAL;
	पूर्ण

	skb = skb_dequeue(&sk->sk_receive_queue);
	अगर (skb == शून्य) अणु
		skb = dn_रुको_क्रम_connect(sk, &समयo);
		अगर (IS_ERR(skb)) अणु
			release_sock(sk);
			वापस PTR_ERR(skb);
		पूर्ण
	पूर्ण

	cb = DN_SKB_CB(skb);
	sk_acceptq_हटाओd(sk);
	newsk = dn_alloc_sock(sock_net(sk), newsock, sk->sk_allocation, kern);
	अगर (newsk == शून्य) अणु
		release_sock(sk);
		kमुक्त_skb(skb);
		वापस -ENOBUFS;
	पूर्ण
	release_sock(sk);

	dst = skb_dst(skb);
	sk_dst_set(newsk, dst);
	skb_dst_set(skb, शून्य);

	DN_SK(newsk)->state        = DN_CR;
	DN_SK(newsk)->addrrem      = cb->src_port;
	DN_SK(newsk)->services_rem = cb->services;
	DN_SK(newsk)->info_rem     = cb->info;
	DN_SK(newsk)->segsize_rem  = cb->segsize;
	DN_SK(newsk)->accept_mode  = DN_SK(sk)->accept_mode;

	अगर (DN_SK(newsk)->segsize_rem < 230)
		DN_SK(newsk)->segsize_rem = 230;

	अगर ((DN_SK(newsk)->services_rem & NSP_FC_MASK) == NSP_FC_NONE)
		DN_SK(newsk)->max_winकरोw = decnet_no_fc_max_cwnd;

	newsk->sk_state  = TCP_LISTEN;
	स_नकल(&(DN_SK(newsk)->addr), &(DN_SK(sk)->addr), माप(काष्ठा sockaddr_dn));

	/*
	 * If we are listening on a wild socket, we करोn't want
	 * the newly created socket on the wrong hash queue.
	 */
	DN_SK(newsk)->addr.sdn_flags &= ~SDF_WILD;

	skb_pull(skb, dn_username2sockaddr(skb->data, skb->len, &(DN_SK(newsk)->addr), &type));
	skb_pull(skb, dn_username2sockaddr(skb->data, skb->len, &(DN_SK(newsk)->peer), &type));
	*(__le16 *)(DN_SK(newsk)->peer.sdn_add.a_addr) = cb->src;
	*(__le16 *)(DN_SK(newsk)->addr.sdn_add.a_addr) = cb->dst;

	menuver = *skb->data;
	skb_pull(skb, 1);

	अगर (menuver & DN_MENUVER_ACC)
		dn_access_copy(skb, &(DN_SK(newsk)->accessdata));

	अगर (menuver & DN_MENUVER_USR)
		dn_user_copy(skb, &(DN_SK(newsk)->conndata_in));

	अगर (menuver & DN_MENUVER_PRX)
		DN_SK(newsk)->peer.sdn_flags |= SDF_PROXY;

	अगर (menuver & DN_MENUVER_UIC)
		DN_SK(newsk)->peer.sdn_flags |= SDF_UICPROXY;

	kमुक्त_skb(skb);

	स_नकल(&(DN_SK(newsk)->conndata_out), &(DN_SK(sk)->conndata_out),
		माप(काष्ठा optdata_dn));
	स_नकल(&(DN_SK(newsk)->discdata_out), &(DN_SK(sk)->discdata_out),
		माप(काष्ठा optdata_dn));

	lock_sock(newsk);
	err = dn_hash_sock(newsk);
	अगर (err == 0) अणु
		sock_reset_flag(newsk, SOCK_ZAPPED);
		dn_send_conn_ack(newsk);

		/*
		 * Here we use sk->sk_allocation since although the conn conf is
		 * क्रम the newsk, the context is the old socket.
		 */
		अगर (DN_SK(newsk)->accept_mode == ACC_IMMED)
			err = dn_confirm_accept(newsk, &समयo,
						sk->sk_allocation);
	पूर्ण
	release_sock(newsk);
	वापस err;
पूर्ण


अटल पूर्णांक dn_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,पूर्णांक peer)
अणु
	काष्ठा sockaddr_dn *sa = (काष्ठा sockaddr_dn *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);

	lock_sock(sk);

	अगर (peer) अणु
		अगर ((sock->state != SS_CONNECTED &&
		     sock->state != SS_CONNECTING) &&
		    scp->accept_mode == ACC_IMMED) अणु
			release_sock(sk);
			वापस -ENOTCONN;
		पूर्ण

		स_नकल(sa, &scp->peer, माप(काष्ठा sockaddr_dn));
	पूर्ण अन्यथा अणु
		स_नकल(sa, &scp->addr, माप(काष्ठा sockaddr_dn));
	पूर्ण

	release_sock(sk);

	वापस माप(काष्ठा sockaddr_dn);
पूर्ण


अटल __poll_t dn_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table  *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	__poll_t mask = datagram_poll(file, sock, रुको);

	अगर (!skb_queue_empty_lockless(&scp->other_receive_queue))
		mask |= EPOLLRDBAND;

	वापस mask;
पूर्ण

अटल पूर्णांक dn_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	पूर्णांक err = -EOPNOTSUPP;
	दीर्घ amount = 0;
	काष्ठा sk_buff *skb;
	पूर्णांक val;

	चयन(cmd)
	अणु
	हाल SIOCGIFADDR:
	हाल SIOCSIFADDR:
		वापस dn_dev_ioctl(cmd, (व्योम __user *)arg);

	हाल SIOCATMARK:
		lock_sock(sk);
		val = !skb_queue_empty(&scp->other_receive_queue);
		अगर (scp->state != DN_RUN)
			val = -ENOTCONN;
		release_sock(sk);
		वापस val;

	हाल TIOCOUTQ:
		amount = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
		अगर (amount < 0)
			amount = 0;
		err = put_user(amount, (पूर्णांक __user *)arg);
		अवरोध;

	हाल TIOCINQ:
		lock_sock(sk);
		skb = skb_peek(&scp->other_receive_queue);
		अगर (skb) अणु
			amount = skb->len;
		पूर्ण अन्यथा अणु
			skb_queue_walk(&sk->sk_receive_queue, skb)
				amount += skb->len;
		पूर्ण
		release_sock(sk);
		err = put_user(amount, (पूर्णांक __user *)arg);
		अवरोध;

	शेष:
		err = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dn_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = -EINVAL;

	lock_sock(sk);

	अगर (sock_flag(sk, SOCK_ZAPPED))
		जाओ out;

	अगर ((DN_SK(sk)->state != DN_O) || (sk->sk_state == TCP_LISTEN))
		जाओ out;

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog     = 0;
	sk->sk_state           = TCP_LISTEN;
	err                 = 0;
	dn_rehash_sock(sk);

out:
	release_sock(sk);

	वापस err;
पूर्ण


अटल पूर्णांक dn_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	पूर्णांक err = -ENOTCONN;

	lock_sock(sk);

	अगर (sock->state == SS_UNCONNECTED)
		जाओ out;

	err = 0;
	अगर (sock->state == SS_DISCONNECTING)
		जाओ out;

	err = -EINVAL;
	अगर (scp->state == DN_O)
		जाओ out;

	अगर (how != SHUT_RDWR)
		जाओ out;

	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	dn_destroy_sock(sk);
	err = 0;

out:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक dn_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	lock_sock(sk);
	err = __dn_setsockopt(sock, level, optname, optval, optlen, 0);
	release_sock(sk);
#अगर_घोषित CONFIG_NETFILTER
	/* we need to exclude all possible ENOPROTOOPTs except शेष हाल */
	अगर (err == -ENOPROTOOPT && optname != DSO_LINKINFO &&
	    optname != DSO_STREAM && optname != DSO_SEQPACKET)
		err = nf_setsockopt(sk, PF_DECnet, optname, optval, optlen);
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल पूर्णांक __dn_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen, पूर्णांक flags)
अणु
	काष्ठा	sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	दीर्घ समयo;
	जोड़ अणु
		काष्ठा optdata_dn opt;
		काष्ठा accessdata_dn acc;
		पूर्णांक mode;
		अचिन्हित दीर्घ win;
		पूर्णांक val;
		अचिन्हित अक्षर services;
		अचिन्हित अक्षर info;
	पूर्ण u;
	पूर्णांक err;

	अगर (optlen && sockptr_is_null(optval))
		वापस -EINVAL;

	अगर (optlen > माप(u))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&u, optval, optlen))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल DSO_CONDATA:
		अगर (sock->state == SS_CONNECTED)
			वापस -EISCONN;
		अगर ((scp->state != DN_O) && (scp->state != DN_CR))
			वापस -EINVAL;

		अगर (optlen != माप(काष्ठा optdata_dn))
			वापस -EINVAL;

		अगर (le16_to_cpu(u.opt.opt_optl) > 16)
			वापस -EINVAL;

		स_नकल(&scp->conndata_out, &u.opt, optlen);
		अवरोध;

	हाल DSO_DISDATA:
		अगर (sock->state != SS_CONNECTED &&
		    scp->accept_mode == ACC_IMMED)
			वापस -ENOTCONN;

		अगर (optlen != माप(काष्ठा optdata_dn))
			वापस -EINVAL;

		अगर (le16_to_cpu(u.opt.opt_optl) > 16)
			वापस -EINVAL;

		स_नकल(&scp->discdata_out, &u.opt, optlen);
		अवरोध;

	हाल DSO_CONACCESS:
		अगर (sock->state == SS_CONNECTED)
			वापस -EISCONN;
		अगर (scp->state != DN_O)
			वापस -EINVAL;

		अगर (optlen != माप(काष्ठा accessdata_dn))
			वापस -EINVAL;

		अगर ((u.acc.acc_accl > DN_MAXACCL) ||
		    (u.acc.acc_passl > DN_MAXACCL) ||
		    (u.acc.acc_userl > DN_MAXACCL))
			वापस -EINVAL;

		स_नकल(&scp->accessdata, &u.acc, optlen);
		अवरोध;

	हाल DSO_ACCEPTMODE:
		अगर (sock->state == SS_CONNECTED)
			वापस -EISCONN;
		अगर (scp->state != DN_O)
			वापस -EINVAL;

		अगर (optlen != माप(पूर्णांक))
			वापस -EINVAL;

		अगर ((u.mode != ACC_IMMED) && (u.mode != ACC_DEFER))
			वापस -EINVAL;

		scp->accept_mode = (अचिन्हित अक्षर)u.mode;
		अवरोध;

	हाल DSO_CONACCEPT:
		अगर (scp->state != DN_CR)
			वापस -EINVAL;
		समयo = sock_rcvसमयo(sk, 0);
		err = dn_confirm_accept(sk, &समयo, sk->sk_allocation);
		वापस err;

	हाल DSO_CONREJECT:
		अगर (scp->state != DN_CR)
			वापस -EINVAL;

		scp->state = DN_DR;
		sk->sk_shutकरोwn = SHUTDOWN_MASK;
		dn_nsp_send_disc(sk, 0x38, 0, sk->sk_allocation);
		अवरोध;

	हाल DSO_MAXWINDOW:
		अगर (optlen != माप(अचिन्हित दीर्घ))
			वापस -EINVAL;
		अगर (u.win > NSP_MAX_WINDOW)
			u.win = NSP_MAX_WINDOW;
		अगर (u.win == 0)
			वापस -EINVAL;
		scp->max_winकरोw = u.win;
		अगर (scp->snd_winकरोw > u.win)
			scp->snd_winकरोw = u.win;
		अवरोध;

	हाल DSO_NODELAY:
		अगर (optlen != माप(पूर्णांक))
			वापस -EINVAL;
		अगर (scp->nonagle == TCP_NAGLE_CORK)
			वापस -EINVAL;
		scp->nonagle = (u.val == 0) ? 0 : TCP_NAGLE_OFF;
		/* अगर (scp->nonagle == 1) अणु Push pending frames पूर्ण */
		अवरोध;

	हाल DSO_CORK:
		अगर (optlen != माप(पूर्णांक))
			वापस -EINVAL;
		अगर (scp->nonagle == TCP_NAGLE_OFF)
			वापस -EINVAL;
		scp->nonagle = (u.val == 0) ? 0 : TCP_NAGLE_CORK;
		/* अगर (scp->nonagle == 0) अणु Push pending frames पूर्ण */
		अवरोध;

	हाल DSO_SERVICES:
		अगर (optlen != माप(अचिन्हित अक्षर))
			वापस -EINVAL;
		अगर ((u.services & ~NSP_FC_MASK) != 0x01)
			वापस -EINVAL;
		अगर ((u.services & NSP_FC_MASK) == NSP_FC_MASK)
			वापस -EINVAL;
		scp->services_loc = u.services;
		अवरोध;

	हाल DSO_INFO:
		अगर (optlen != माप(अचिन्हित अक्षर))
			वापस -EINVAL;
		अगर (u.info & 0xfc)
			वापस -EINVAL;
		scp->info_loc = u.info;
		अवरोध;

	हाल DSO_LINKINFO:
	हाल DSO_STREAM:
	हाल DSO_SEQPACKET:
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dn_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	lock_sock(sk);
	err = __dn_माला_लोockopt(sock, level, optname, optval, optlen, 0);
	release_sock(sk);
#अगर_घोषित CONFIG_NETFILTER
	अगर (err == -ENOPROTOOPT && optname != DSO_STREAM &&
	    optname != DSO_SEQPACKET && optname != DSO_CONACCEPT &&
	    optname != DSO_CONREJECT) अणु
		पूर्णांक len;

		अगर (get_user(len, optlen))
			वापस -EFAULT;

		err = nf_माला_लोockopt(sk, PF_DECnet, optname, optval, &len);
		अगर (err >= 0)
			err = put_user(len, optlen);
	पूर्ण
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल पूर्णांक __dn_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level,पूर्णांक optname, अक्षर __user *optval,पूर्णांक __user *optlen, पूर्णांक flags)
अणु
	काष्ठा	sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा linkinfo_dn link;
	अचिन्हित पूर्णांक r_len;
	व्योम *r_data = शून्य;
	अचिन्हित पूर्णांक val;

	अगर(get_user(r_len , optlen))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल DSO_CONDATA:
		अगर (r_len > माप(काष्ठा optdata_dn))
			r_len = माप(काष्ठा optdata_dn);
		r_data = &scp->conndata_in;
		अवरोध;

	हाल DSO_DISDATA:
		अगर (r_len > माप(काष्ठा optdata_dn))
			r_len = माप(काष्ठा optdata_dn);
		r_data = &scp->discdata_in;
		अवरोध;

	हाल DSO_CONACCESS:
		अगर (r_len > माप(काष्ठा accessdata_dn))
			r_len = माप(काष्ठा accessdata_dn);
		r_data = &scp->accessdata;
		अवरोध;

	हाल DSO_ACCEPTMODE:
		अगर (r_len > माप(अचिन्हित अक्षर))
			r_len = माप(अचिन्हित अक्षर);
		r_data = &scp->accept_mode;
		अवरोध;

	हाल DSO_LINKINFO:
		अगर (r_len > माप(काष्ठा linkinfo_dn))
			r_len = माप(काष्ठा linkinfo_dn);

		स_रखो(&link, 0, माप(link));

		चयन (sock->state) अणु
		हाल SS_CONNECTING:
			link.idn_linkstate = LL_CONNECTING;
			अवरोध;
		हाल SS_DISCONNECTING:
			link.idn_linkstate = LL_DISCONNECTING;
			अवरोध;
		हाल SS_CONNECTED:
			link.idn_linkstate = LL_RUNNING;
			अवरोध;
		शेष:
			link.idn_linkstate = LL_INACTIVE;
		पूर्ण

		link.idn_segsize = scp->segsize_rem;
		r_data = &link;
		अवरोध;

	हाल DSO_MAXWINDOW:
		अगर (r_len > माप(अचिन्हित दीर्घ))
			r_len = माप(अचिन्हित दीर्घ);
		r_data = &scp->max_winकरोw;
		अवरोध;

	हाल DSO_NODELAY:
		अगर (r_len > माप(पूर्णांक))
			r_len = माप(पूर्णांक);
		val = (scp->nonagle == TCP_NAGLE_OFF);
		r_data = &val;
		अवरोध;

	हाल DSO_CORK:
		अगर (r_len > माप(पूर्णांक))
			r_len = माप(पूर्णांक);
		val = (scp->nonagle == TCP_NAGLE_CORK);
		r_data = &val;
		अवरोध;

	हाल DSO_SERVICES:
		अगर (r_len > माप(अचिन्हित अक्षर))
			r_len = माप(अचिन्हित अक्षर);
		r_data = &scp->services_rem;
		अवरोध;

	हाल DSO_INFO:
		अगर (r_len > माप(अचिन्हित अक्षर))
			r_len = माप(अचिन्हित अक्षर);
		r_data = &scp->info_rem;
		अवरोध;

	हाल DSO_STREAM:
	हाल DSO_SEQPACKET:
	हाल DSO_CONACCEPT:
	हाल DSO_CONREJECT:
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (r_data) अणु
		अगर (copy_to_user(optval, r_data, r_len))
			वापस -EFAULT;
		अगर (put_user(r_len, optlen))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक dn_data_पढ़ोy(काष्ठा sock *sk, काष्ठा sk_buff_head *q, पूर्णांक flags, पूर्णांक target)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक len = 0;

	अगर (flags & MSG_OOB)
		वापस !skb_queue_empty(q) ? 1 : 0;

	skb_queue_walk(q, skb) अणु
		काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);
		len += skb->len;

		अगर (cb->nsp_flags & 0x40) अणु
			/* SOCK_SEQPACKET पढ़ोs to EOM */
			अगर (sk->sk_type == SOCK_SEQPACKET)
				वापस 1;
			/* so करोes SOCK_STREAM unless WAITALL is specअगरied */
			अगर (!(flags & MSG_WAITALL))
				वापस 1;
		पूर्ण

		/* minimum data length क्रम पढ़ो exceeded */
		अगर (len >= target)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक dn_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		      पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	काष्ठा sk_buff_head *queue = &sk->sk_receive_queue;
	माप_प्रकार target = size > 1 ? 1 : 0;
	माप_प्रकार copied = 0;
	पूर्णांक rv = 0;
	काष्ठा sk_buff *skb, *n;
	काष्ठा dn_skb_cb *cb = शून्य;
	अचिन्हित अक्षर eor = 0;
	दीर्घ समयo = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	lock_sock(sk);

	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		rv = -EADDRNOTAVAIL;
		जाओ out;
	पूर्ण

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
		rv = 0;
		जाओ out;
	पूर्ण

	rv = dn_check_state(sk, शून्य, 0, &समयo, flags);
	अगर (rv)
		जाओ out;

	अगर (flags & ~(MSG_CMSG_COMPAT|MSG_PEEK|MSG_OOB|MSG_WAITALL|MSG_DONTWAIT|MSG_NOSIGNAL)) अणु
		rv = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (flags & MSG_OOB)
		queue = &scp->other_receive_queue;

	अगर (flags & MSG_WAITALL)
		target = size;


	/*
	 * See अगर there is data पढ़ोy to पढ़ो, sleep अगर there isn't
	 */
	क्रम(;;) अणु
		DEFINE_WAIT_FUNC(रुको, woken_wake_function);

		अगर (sk->sk_err)
			जाओ out;

		अगर (!skb_queue_empty(&scp->other_receive_queue)) अणु
			अगर (!(flags & MSG_OOB)) अणु
				msg->msg_flags |= MSG_OOB;
				अगर (!scp->other_report) अणु
					scp->other_report = 1;
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (scp->state != DN_RUN)
			जाओ out;

		अगर (संकेत_pending(current)) अणु
			rv = sock_पूर्णांकr_त्रुटि_सं(समयo);
			जाओ out;
		पूर्ण

		अगर (dn_data_पढ़ोy(sk, queue, flags, target))
			अवरोध;

		अगर (flags & MSG_DONTWAIT) अणु
			rv = -EWOULDBLOCK;
			जाओ out;
		पूर्ण

		add_रुको_queue(sk_sleep(sk), &रुको);
		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		sk_रुको_event(sk, &समयo, dn_data_पढ़ोy(sk, queue, flags, target), &रुको);
		sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	पूर्ण

	skb_queue_walk_safe(queue, skb, n) अणु
		अचिन्हित पूर्णांक chunk = skb->len;
		cb = DN_SKB_CB(skb);

		अगर ((chunk + copied) > size)
			chunk = size - copied;

		अगर (स_नकल_to_msg(msg, skb->data, chunk)) अणु
			rv = -EFAULT;
			अवरोध;
		पूर्ण
		copied += chunk;

		अगर (!(flags & MSG_PEEK))
			skb_pull(skb, chunk);

		eor = cb->nsp_flags & 0x40;

		अगर (skb->len == 0) अणु
			skb_unlink(skb, queue);
			kमुक्त_skb(skb);
			/*
			 * N.B. Don't refer to skb or cb after this poपूर्णांक
			 * in loop.
			 */
			अगर ((scp->flowloc_sw == DN_DONTSEND) && !dn_congested(sk)) अणु
				scp->flowloc_sw = DN_SEND;
				dn_nsp_send_link(sk, DN_SEND, 0);
			पूर्ण
		पूर्ण

		अगर (eor) अणु
			अगर (sk->sk_type == SOCK_SEQPACKET)
				अवरोध;
			अगर (!(flags & MSG_WAITALL))
				अवरोध;
		पूर्ण

		अगर (flags & MSG_OOB)
			अवरोध;

		अगर (copied >= target)
			अवरोध;
	पूर्ण

	rv = copied;


	अगर (eor && (sk->sk_type == SOCK_SEQPACKET))
		msg->msg_flags |= MSG_EOR;

out:
	अगर (rv == 0)
		rv = (flags & MSG_PEEK) ? -sk->sk_err : sock_error(sk);

	अगर ((rv >= 0) && msg->msg_name) अणु
		__sockaddr_check_size(माप(काष्ठा sockaddr_dn));
		स_नकल(msg->msg_name, &scp->peer, माप(काष्ठा sockaddr_dn));
		msg->msg_namelen = माप(काष्ठा sockaddr_dn);
	पूर्ण

	release_sock(sk);

	वापस rv;
पूर्ण


अटल अंतरभूत पूर्णांक dn_queue_too_दीर्घ(काष्ठा dn_scp *scp, काष्ठा sk_buff_head *queue, पूर्णांक flags)
अणु
	अचिन्हित अक्षर fctype = scp->services_rem & NSP_FC_MASK;
	अगर (skb_queue_len(queue) >= scp->snd_winकरोw)
		वापस 1;
	अगर (fctype != NSP_FC_NONE) अणु
		अगर (flags & MSG_OOB) अणु
			अगर (scp->flowrem_oth == 0)
				वापस 1;
		पूर्ण अन्यथा अणु
			अगर (scp->flowrem_dat == 0)
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The DECnet spec requires that the "routing layer" accepts packets which
 * are at least 230 bytes in size. This excludes any headers which the NSP
 * layer might add, so we always assume that we'll be using the maximal
 * length header on data packets. The variation in length is due to the
 * inclusion (or not) of the two 16 bit acknowledgement fields so it करोesn't
 * make much practical dअगरference.
 */
अचिन्हित पूर्णांक dn_mss_from_pmtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	अचिन्हित पूर्णांक mss = 230 - DN_MAX_NSP_DATA_HEADER;
	अगर (dev) अणु
		काष्ठा dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);
		mtu -= LL_RESERVED_SPACE(dev);
		अगर (dn_db->use_दीर्घ)
			mtu -= 21;
		अन्यथा
			mtu -= 6;
		mtu -= DN_MAX_NSP_DATA_HEADER;
	पूर्ण अन्यथा अणु
		/*
		 * 21 = दीर्घ header, 16 = guess at MAC header length
		 */
		mtu -= (21 + DN_MAX_NSP_DATA_HEADER + 16);
	पूर्ण
	अगर (mtu > mss)
		mss = mtu;
	वापस mss;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dn_current_mss(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा dst_entry *dst = __sk_dst_get(sk);
	काष्ठा dn_scp *scp = DN_SK(sk);
	पूर्णांक mss_now = min_t(पूर्णांक, scp->segsize_loc, scp->segsize_rem);

	/* Other data messages are limited to 16 bytes per packet */
	अगर (flags & MSG_OOB)
		वापस 16;

	/* This works out the maximum size of segment we can send out */
	अगर (dst) अणु
		u32 mtu = dst_mtu(dst);
		mss_now = min_t(पूर्णांक, dn_mss_from_pmtu(dst->dev, mtu), mss_now);
	पूर्ण

	वापस mss_now;
पूर्ण

/*
 * N.B. We get the समयout wrong here, but then we always did get it
 * wrong beक्रमe and this is another step aदीर्घ the road to correcting
 * it. It ought to get updated each समय we pass through the routine,
 * but in practise it probably करोesn't matter too much क्रम now.
 */
अटल अंतरभूत काष्ठा sk_buff *dn_alloc_send_pskb(काष्ठा sock *sk,
			      अचिन्हित दीर्घ datalen, पूर्णांक noblock,
			      पूर्णांक *errcode)
अणु
	काष्ठा sk_buff *skb = sock_alloc_send_skb(sk, datalen,
						   noblock, errcode);
	अगर (skb) अणु
		skb->protocol = htons(ETH_P_DNA_RT);
		skb->pkt_type = PACKET_OUTGOING;
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक dn_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा dn_scp *scp = DN_SK(sk);
	माप_प्रकार mss;
	काष्ठा sk_buff_head *queue = &scp->data_xmit_queue;
	पूर्णांक flags = msg->msg_flags;
	पूर्णांक err = 0;
	माप_प्रकार sent = 0;
	पूर्णांक addr_len = msg->msg_namelen;
	DECLARE_SOCKADDR(काष्ठा sockaddr_dn *, addr, msg->msg_name);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा dn_skb_cb *cb;
	माप_प्रकार len;
	अचिन्हित अक्षर fctype;
	दीर्घ समयo;

	अगर (flags & ~(MSG_TRYHARD|MSG_OOB|MSG_DONTWAIT|MSG_EOR|MSG_NOSIGNAL|MSG_MORE|MSG_CMSG_COMPAT))
		वापस -EOPNOTSUPP;

	अगर (addr_len && (addr_len != माप(काष्ठा sockaddr_dn)))
		वापस -EINVAL;

	lock_sock(sk);
	समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);
	/*
	 * The only dअगरference between stream sockets and sequenced packet
	 * sockets is that the stream sockets always behave as अगर MSG_EOR
	 * has been set.
	 */
	अगर (sock->type == SOCK_STREAM) अणु
		अगर (flags & MSG_EOR) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		flags |= MSG_EOR;
	पूर्ण


	err = dn_check_state(sk, addr, addr_len, &समयo, flags);
	अगर (err)
		जाओ out_err;

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		err = -EPIPE;
		अगर (!(flags & MSG_NOSIGNAL))
			send_sig(SIGPIPE, current, 0);
		जाओ out_err;
	पूर्ण

	अगर ((flags & MSG_TRYHARD) && sk->sk_dst_cache)
		dst_negative_advice(sk);

	mss = scp->segsize_rem;
	fctype = scp->services_rem & NSP_FC_MASK;

	mss = dn_current_mss(sk, flags);

	अगर (flags & MSG_OOB) अणु
		queue = &scp->other_xmit_queue;
		अगर (size > mss) अणु
			err = -EMSGSIZE;
			जाओ out;
		पूर्ण
	पूर्ण

	scp->persist_fxn = dn_nsp_xmit_समयout;

	जबतक(sent < size) अणु
		err = sock_error(sk);
		अगर (err)
			जाओ out;

		अगर (संकेत_pending(current)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			जाओ out;
		पूर्ण

		/*
		 * Calculate size that we wish to send.
		 */
		len = size - sent;

		अगर (len > mss)
			len = mss;

		/*
		 * Wait क्रम queue size to go करोwn below the winकरोw
		 * size.
		 */
		अगर (dn_queue_too_दीर्घ(scp, queue, flags)) अणु
			DEFINE_WAIT_FUNC(रुको, woken_wake_function);

			अगर (flags & MSG_DONTWAIT) अणु
				err = -EWOULDBLOCK;
				जाओ out;
			पूर्ण

			add_रुको_queue(sk_sleep(sk), &रुको);
			sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
			sk_रुको_event(sk, &समयo,
				      !dn_queue_too_दीर्घ(scp, queue, flags), &रुको);
			sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
			हटाओ_रुको_queue(sk_sleep(sk), &रुको);
			जारी;
		पूर्ण

		/*
		 * Get a suitably sized skb.
		 * 64 is a bit of a hack really, but its larger than any
		 * link-layer headers and has served us well as a good
		 * guess as to their real length.
		 */
		skb = dn_alloc_send_pskb(sk, len + 64 + DN_MAX_NSP_DATA_HEADER,
					 flags & MSG_DONTWAIT, &err);

		अगर (err)
			अवरोध;

		अगर (!skb)
			जारी;

		cb = DN_SKB_CB(skb);

		skb_reserve(skb, 64 + DN_MAX_NSP_DATA_HEADER);

		अगर (स_नकल_from_msg(skb_put(skb, len), msg, len)) अणु
			err = -EFAULT;
			जाओ out;
		पूर्ण

		अगर (flags & MSG_OOB) अणु
			cb->nsp_flags = 0x30;
			अगर (fctype != NSP_FC_NONE)
				scp->flowrem_oth--;
		पूर्ण अन्यथा अणु
			cb->nsp_flags = 0x00;
			अगर (scp->seg_total == 0)
				cb->nsp_flags |= 0x20;

			scp->seg_total += len;

			अगर (((sent + len) == size) && (flags & MSG_EOR)) अणु
				cb->nsp_flags |= 0x40;
				scp->seg_total = 0;
				अगर (fctype == NSP_FC_SCMC)
					scp->flowrem_dat--;
			पूर्ण
			अगर (fctype == NSP_FC_SRC)
				scp->flowrem_dat--;
		पूर्ण

		sent += len;
		dn_nsp_queue_xmit(sk, skb, sk->sk_allocation, flags & MSG_OOB);
		skb = शून्य;

		scp->persist = dn_nsp_persist(sk);

	पूर्ण
out:

	kमुक्त_skb(skb);

	release_sock(sk);

	वापस sent ? sent : err;

out_err:
	err = sk_stream_error(sk, flags, err);
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक dn_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		dn_dev_up(dev);
		अवरोध;
	हाल NETDEV_DOWN:
		dn_dev_करोwn(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block dn_dev_notअगरier = अणु
	.notअगरier_call = dn_device_event,
पूर्ण;

अटल काष्ठा packet_type dn_dix_packet_type __पढ़ो_mostly = अणु
	.type =		cpu_to_be16(ETH_P_DNA_RT),
	.func =		dn_route_rcv,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
काष्ठा dn_iter_state अणु
	पूर्णांक bucket;
पूर्ण;

अटल काष्ठा sock *dn_socket_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा dn_iter_state *state = seq->निजी;
	काष्ठा sock *n = शून्य;

	क्रम(state->bucket = 0;
	    state->bucket < DN_SK_HASH_SIZE;
	    ++state->bucket) अणु
		n = sk_head(&dn_sk_hash[state->bucket]);
		अगर (n)
			अवरोध;
	पूर्ण

	वापस n;
पूर्ण

अटल काष्ठा sock *dn_socket_get_next(काष्ठा seq_file *seq,
				       काष्ठा sock *n)
अणु
	काष्ठा dn_iter_state *state = seq->निजी;

	n = sk_next(n);
	जबतक (!n) अणु
		अगर (++state->bucket >= DN_SK_HASH_SIZE)
			अवरोध;
		n = sk_head(&dn_sk_hash[state->bucket]);
	पूर्ण
	वापस n;
पूर्ण

अटल काष्ठा sock *socket_get_idx(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा sock *sk = dn_socket_get_first(seq);

	अगर (sk) अणु
		जबतक(*pos && (sk = dn_socket_get_next(seq, sk)))
			--*pos;
	पूर्ण
	वापस *pos ? शून्य : sk;
पूर्ण

अटल व्योम *dn_socket_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	व्योम *rc;
	पढ़ो_lock_bh(&dn_hash_lock);
	rc = socket_get_idx(seq, &pos);
	अगर (!rc) अणु
		पढ़ो_unlock_bh(&dn_hash_lock);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम *dn_socket_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos ? dn_socket_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *dn_socket_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	व्योम *rc;

	अगर (v == SEQ_START_TOKEN) अणु
		rc = dn_socket_get_idx(seq, 0);
		जाओ out;
	पूर्ण

	rc = dn_socket_get_next(seq, v);
	अगर (rc)
		जाओ out;
	पढ़ो_unlock_bh(&dn_hash_lock);
out:
	++*pos;
	वापस rc;
पूर्ण

अटल व्योम dn_socket_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v && v != SEQ_START_TOKEN)
		पढ़ो_unlock_bh(&dn_hash_lock);
पूर्ण

#घोषणा IS_NOT_PRINTABLE(x) ((x) < 32 || (x) > 126)

अटल व्योम dn_prपूर्णांकable_object(काष्ठा sockaddr_dn *dn, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक i;

	चयन (le16_to_cpu(dn->sdn_objnamel)) अणु
	हाल 0:
		प्र_लिखो(buf, "%d", dn->sdn_objnum);
		अवरोध;
	शेष:
		क्रम (i = 0; i < le16_to_cpu(dn->sdn_objnamel); i++) अणु
			buf[i] = dn->sdn_objname[i];
			अगर (IS_NOT_PRINTABLE(buf[i]))
				buf[i] = '.';
		पूर्ण
		buf[i] = 0;
	पूर्ण
पूर्ण

अटल अक्षर *dn_state2asc(अचिन्हित अक्षर state)
अणु
	चयन (state) अणु
	हाल DN_O:
		वापस "OPEN";
	हाल DN_CR:
		वापस "  CR";
	हाल DN_DR:
		वापस "  DR";
	हाल DN_DRC:
		वापस " DRC";
	हाल DN_CC:
		वापस "  CC";
	हाल DN_CI:
		वापस "  CI";
	हाल DN_NR:
		वापस "  NR";
	हाल DN_NC:
		वापस "  NC";
	हाल DN_CD:
		वापस "  CD";
	हाल DN_RJ:
		वापस "  RJ";
	हाल DN_RUN:
		वापस " RUN";
	हाल DN_DI:
		वापस "  DI";
	हाल DN_DIC:
		वापस " DIC";
	हाल DN_DN:
		वापस "  DN";
	हाल DN_CL:
		वापस "  CL";
	हाल DN_CN:
		वापस "  CN";
	पूर्ण

	वापस "????";
पूर्ण

अटल अंतरभूत व्योम dn_socket_क्रमmat_entry(काष्ठा seq_file *seq, काष्ठा sock *sk)
अणु
	काष्ठा dn_scp *scp = DN_SK(sk);
	अक्षर buf1[DN_ASCBUF_LEN];
	अक्षर buf2[DN_ASCBUF_LEN];
	अक्षर local_object[DN_MAXOBJL+3];
	अक्षर remote_object[DN_MAXOBJL+3];

	dn_prपूर्णांकable_object(&scp->addr, local_object);
	dn_prपूर्णांकable_object(&scp->peer, remote_object);

	seq_म_लिखो(seq,
		   "%6s/%04X %04d:%04d %04d:%04d %01d %-16s "
		   "%6s/%04X %04d:%04d %04d:%04d %01d %-16s %4s %s\n",
		   dn_addr2asc(le16_to_cpu(dn_saddr2dn(&scp->addr)), buf1),
		   scp->addrloc,
		   scp->numdat,
		   scp->numoth,
		   scp->ackxmt_dat,
		   scp->ackxmt_oth,
		   scp->flowloc_sw,
		   local_object,
		   dn_addr2asc(le16_to_cpu(dn_saddr2dn(&scp->peer)), buf2),
		   scp->addrrem,
		   scp->numdat_rcv,
		   scp->numoth_rcv,
		   scp->ackrcv_dat,
		   scp->ackrcv_oth,
		   scp->flowrem_sw,
		   remote_object,
		   dn_state2asc(scp->state),
		   ((scp->accept_mode == ACC_IMMED) ? "IMMED" : "DEFER"));
पूर्ण

अटल पूर्णांक dn_socket_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Local                                              Remote\n");
	पूर्ण अन्यथा अणु
		dn_socket_क्रमmat_entry(seq, v);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations dn_socket_seq_ops = अणु
	.start	= dn_socket_seq_start,
	.next	= dn_socket_seq_next,
	.stop	= dn_socket_seq_stop,
	.show	= dn_socket_seq_show,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा net_proto_family	dn_family_ops = अणु
	.family =	AF_DECnet,
	.create =	dn_create,
	.owner	=	THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा proto_ops dn_proto_ops = अणु
	.family =	AF_DECnet,
	.owner =	THIS_MODULE,
	.release =	dn_release,
	.bind =		dn_bind,
	.connect =	dn_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	dn_accept,
	.getname =	dn_getname,
	.poll =		dn_poll,
	.ioctl =	dn_ioctl,
	.listen =	dn_listen,
	.shutकरोwn =	dn_shutकरोwn,
	.setsockopt =	dn_setsockopt,
	.माला_लोockopt =	dn_माला_लोockopt,
	.sendmsg =	dn_sendmsg,
	.recvmsg =	dn_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
पूर्ण;

MODULE_DESCRIPTION("The Linux DECnet Network Protocol");
MODULE_AUTHOR("Linux DECnet Project Team");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_DECnet);

अटल स्थिर अक्षर banner[] __initस्थिर = KERN_INFO
"NET4: DECnet for Linux: V.2.5.68s (C) 1995-2003 Linux DECnet Project Team\n";

अटल पूर्णांक __init decnet_init(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(banner);

	rc = proto_रेजिस्टर(&dn_proto, 1);
	अगर (rc != 0)
		जाओ out;

	dn_neigh_init();
	dn_dev_init();
	dn_route_init();
	dn_fib_init();

	sock_रेजिस्टर(&dn_family_ops);
	dev_add_pack(&dn_dix_packet_type);
	रेजिस्टर_netdevice_notअगरier(&dn_dev_notअगरier);

	proc_create_seq_निजी("decnet", 0444, init_net.proc_net,
			&dn_socket_seq_ops, माप(काष्ठा dn_iter_state),
			शून्य);
	dn_रेजिस्टर_sysctl();
out:
	वापस rc;

पूर्ण
module_init(decnet_init);

/*
 * Prevent DECnet module unloading until its fixed properly.
 * Requires an audit of the code to check क्रम memory leaks and
 * initialisation problems etc.
 */
#अगर 0
अटल व्योम __निकास decnet_निकास(व्योम)
अणु
	sock_unरेजिस्टर(AF_DECnet);
	rtnl_unरेजिस्टर_all(PF_DECnet);
	dev_हटाओ_pack(&dn_dix_packet_type);

	dn_unरेजिस्टर_sysctl();

	unरेजिस्टर_netdevice_notअगरier(&dn_dev_notअगरier);

	dn_route_cleanup();
	dn_dev_cleanup();
	dn_neigh_cleanup();
	dn_fib_cleanup();

	हटाओ_proc_entry("decnet", init_net.proc_net);

	proto_unरेजिस्टर(&dn_proto);

	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */
पूर्ण
module_निकास(decnet_निकास);
#पूर्ण_अगर

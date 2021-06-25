<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	DDP:	An implementation of the AppleTalk DDP protocol क्रम
 *		Ethernet 'ELAP'.
 *
 *		Alan Cox  <alan@lxorguk.ukuu.org.uk>
 *
 *		With more than a little assistance from
 *
 *		Wesley Craig <netatalk@umich.edu>
 *
 *	Fixes:
 *		Neil Horman		:	Added missing device ioctls
 *		Michael Callahan	:	Made routing work
 *		Wesley Craig		:	Fix probing to listen to a
 *						passed node id.
 *		Alan Cox		:	Added send/recvmsg support
 *		Alan Cox		:	Moved at. to protinfo in
 *						socket.
 *		Alan Cox		:	Added firewall hooks.
 *		Alan Cox		:	Supports new ARPHRD_LOOPBACK
 *		Christer Weinigel	: 	Routing and /proc fixes.
 *		Bradक्रमd Johnson	:	LocalTalk.
 *		Tom Dyas		:	Module support.
 *		Alan Cox		:	Hooks क्रम PPP (based on the
 *						LocalTalk hook).
 *		Alan Cox		:	Posix bits
 *		Alan Cox/Mike Freeman	:	Possible fix to NBP problems
 *		Bradक्रमd Johnson	:	IP-over-DDP (experimental)
 *		Jay Schulist		:	Moved IP-over-DDP to its own
 *						driver file. (ipddp.c & ipddp.h)
 *		Jay Schulist		:	Made work as module with
 *						AppleTalk drivers, cleaned it.
 *		Rob Newberry		:	Added proxy AARP and AARP
 *						procfs, moved probing to AARP
 *						module.
 *              Adrian Sun/
 *              Michael Zuelsकरोrff      :       fix क्रम net.0 packets. करोn't
 *                                              allow illegal ether/tokentalk
 *                                              port assignment. we lose a
 *                                              valid localtalk port as a
 *                                              result.
 *		Arnalकरो C. de Melo	:	Cleanup, in preparation क्रम
 *						shared skb support 8)
 *		Arnalकरो C. de Melo	:	Move proc stuff to atalk_proc.c,
 *						use seq_file
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/termios.h>	/* For TIOCOUTQ/INQ */
#समावेश <linux/compat.h>
#समावेश <linux/slab.h>
#समावेश <net/datalink.h>
#समावेश <net/psnap.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/route.h>
#समावेश <net/compat.h>
#समावेश <linux/atalk.h>
#समावेश <linux/highस्मृति.स>

काष्ठा datalink_proto *ddp_dl, *aarp_dl;
अटल स्थिर काष्ठा proto_ops atalk_dgram_ops;

/**************************************************************************\
*                                                                          *
* Handlers क्रम the socket list.                                            *
*                                                                          *
\**************************************************************************/

HLIST_HEAD(atalk_sockets);
DEFINE_RWLOCK(atalk_sockets_lock);

अटल अंतरभूत व्योम __atalk_insert_socket(काष्ठा sock *sk)
अणु
	sk_add_node(sk, &atalk_sockets);
पूर्ण

अटल अंतरभूत व्योम atalk_हटाओ_socket(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&atalk_sockets_lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&atalk_sockets_lock);
पूर्ण

अटल काष्ठा sock *atalk_search_socket(काष्ठा sockaddr_at *to,
					काष्ठा atalk_अगरace *atअगर)
अणु
	काष्ठा sock *s;

	पढ़ो_lock_bh(&atalk_sockets_lock);
	sk_क्रम_each(s, &atalk_sockets) अणु
		काष्ठा atalk_sock *at = at_sk(s);

		अगर (to->sat_port != at->src_port)
			जारी;

		अगर (to->sat_addr.s_net == ATADDR_ANYNET &&
		    to->sat_addr.s_node == ATADDR_BCAST)
			जाओ found;

		अगर (to->sat_addr.s_net == at->src_net &&
		    (to->sat_addr.s_node == at->src_node ||
		     to->sat_addr.s_node == ATADDR_BCAST ||
		     to->sat_addr.s_node == ATADDR_ANYNODE))
			जाओ found;

		/* XXXX.0 -- we got a request क्रम this router. make sure
		 * that the node is appropriately set. */
		अगर (to->sat_addr.s_node == ATADDR_ANYNODE &&
		    to->sat_addr.s_net != ATADDR_ANYNET &&
		    atअगर->address.s_node == at->src_node) अणु
			to->sat_addr.s_node = atअगर->address.s_node;
			जाओ found;
		पूर्ण
	पूर्ण
	s = शून्य;
found:
	पढ़ो_unlock_bh(&atalk_sockets_lock);
	वापस s;
पूर्ण

/**
 * atalk_find_or_insert_socket - Try to find a socket matching ADDR
 * @sk: socket to insert in the list अगर it is not there alपढ़ोy
 * @sat: address to search क्रम
 *
 * Try to find a socket matching ADDR in the socket list, अगर found then वापस
 * it. If not, insert SK पूर्णांकo the socket list.
 *
 * This entire operation must execute atomically.
 */
अटल काष्ठा sock *atalk_find_or_insert_socket(काष्ठा sock *sk,
						काष्ठा sockaddr_at *sat)
अणु
	काष्ठा sock *s;
	काष्ठा atalk_sock *at;

	ग_लिखो_lock_bh(&atalk_sockets_lock);
	sk_क्रम_each(s, &atalk_sockets) अणु
		at = at_sk(s);

		अगर (at->src_net == sat->sat_addr.s_net &&
		    at->src_node == sat->sat_addr.s_node &&
		    at->src_port == sat->sat_port)
			जाओ found;
	पूर्ण
	s = शून्य;
	__atalk_insert_socket(sk); /* Wheee, it's मुक्त, assign and insert. */
found:
	ग_लिखो_unlock_bh(&atalk_sockets_lock);
	वापस s;
पूर्ण

अटल व्योम atalk_destroy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);

	अगर (sk_has_allocations(sk)) अणु
		sk->sk_समयr.expires = jअगरfies + SOCK_DESTROY_TIME;
		add_समयr(&sk->sk_समयr);
	पूर्ण अन्यथा
		sock_put(sk);
पूर्ण

अटल अंतरभूत व्योम atalk_destroy_socket(काष्ठा sock *sk)
अणु
	atalk_हटाओ_socket(sk);
	skb_queue_purge(&sk->sk_receive_queue);

	अगर (sk_has_allocations(sk)) अणु
		समयr_setup(&sk->sk_समयr, atalk_destroy_समयr, 0);
		sk->sk_समयr.expires	= jअगरfies + SOCK_DESTROY_TIME;
		add_समयr(&sk->sk_समयr);
	पूर्ण अन्यथा
		sock_put(sk);
पूर्ण

/**************************************************************************\
*                                                                          *
* Routing tables क्रम the AppleTalk socket layer.                           *
*                                                                          *
\**************************************************************************/

/* Anti-deadlock ordering is atalk_routes_lock --> अगरace_lock -DaveM */
काष्ठा atalk_route *atalk_routes;
DEFINE_RWLOCK(atalk_routes_lock);

काष्ठा atalk_अगरace *atalk_पूर्णांकerfaces;
DEFINE_RWLOCK(atalk_पूर्णांकerfaces_lock);

/* For probing devices or in a routerless network */
काष्ठा atalk_route atrtr_शेष;

/* AppleTalk पूर्णांकerface control */
/*
 * Drop a device. Doesn't drop any of its routes - that is the caller's
 * problem. Called when we करोwn the पूर्णांकerface or delete the address.
 */
अटल व्योम atअगर_drop_device(काष्ठा net_device *dev)
अणु
	काष्ठा atalk_अगरace **अगरace = &atalk_पूर्णांकerfaces;
	काष्ठा atalk_अगरace *पंचांगp;

	ग_लिखो_lock_bh(&atalk_पूर्णांकerfaces_lock);
	जबतक ((पंचांगp = *अगरace) != शून्य) अणु
		अगर (पंचांगp->dev == dev) अणु
			*अगरace = पंचांगp->next;
			dev_put(dev);
			kमुक्त(पंचांगp);
			dev->atalk_ptr = शून्य;
		पूर्ण अन्यथा
			अगरace = &पंचांगp->next;
	पूर्ण
	ग_लिखो_unlock_bh(&atalk_पूर्णांकerfaces_lock);
पूर्ण

अटल काष्ठा atalk_अगरace *atअगर_add_device(काष्ठा net_device *dev,
					   काष्ठा atalk_addr *sa)
अणु
	काष्ठा atalk_अगरace *अगरace = kzalloc(माप(*अगरace), GFP_KERNEL);

	अगर (!अगरace)
		जाओ out;

	dev_hold(dev);
	अगरace->dev = dev;
	dev->atalk_ptr = अगरace;
	अगरace->address = *sa;
	अगरace->status = 0;

	ग_लिखो_lock_bh(&atalk_पूर्णांकerfaces_lock);
	अगरace->next = atalk_पूर्णांकerfaces;
	atalk_पूर्णांकerfaces = अगरace;
	ग_लिखो_unlock_bh(&atalk_पूर्णांकerfaces_lock);
out:
	वापस अगरace;
पूर्ण

/* Perक्रमm phase 2 AARP probing on our tentative address */
अटल पूर्णांक atअगर_probe_device(काष्ठा atalk_अगरace *atअगर)
अणु
	पूर्णांक netrange = ntohs(atअगर->nets.nr_lastnet) -
			ntohs(atअगर->nets.nr_firstnet) + 1;
	पूर्णांक probe_net = ntohs(atअगर->address.s_net);
	पूर्णांक probe_node = atअगर->address.s_node;
	पूर्णांक netct, nodect;

	/* Offset the network we start probing with */
	अगर (probe_net == ATADDR_ANYNET) अणु
		probe_net = ntohs(atअगर->nets.nr_firstnet);
		अगर (netrange)
			probe_net += jअगरfies % netrange;
	पूर्ण
	अगर (probe_node == ATADDR_ANYNODE)
		probe_node = jअगरfies & 0xFF;

	/* Scan the networks */
	atअगर->status |= ATIF_PROBE;
	क्रम (netct = 0; netct <= netrange; netct++) अणु
		/* Sweep the available nodes from a given start */
		atअगर->address.s_net = htons(probe_net);
		क्रम (nodect = 0; nodect < 256; nodect++) अणु
			atअगर->address.s_node = (nodect + probe_node) & 0xFF;
			अगर (atअगर->address.s_node > 0 &&
			    atअगर->address.s_node < 254) अणु
				/* Probe a proposed address */
				aarp_probe_network(atअगर);

				अगर (!(atअगर->status & ATIF_PROBE_FAIL)) अणु
					atअगर->status &= ~ATIF_PROBE;
					वापस 0;
				पूर्ण
			पूर्ण
			atअगर->status &= ~ATIF_PROBE_FAIL;
		पूर्ण
		probe_net++;
		अगर (probe_net > ntohs(atअगर->nets.nr_lastnet))
			probe_net = ntohs(atअगर->nets.nr_firstnet);
	पूर्ण
	atअगर->status &= ~ATIF_PROBE;

	वापस -EADDRINUSE;	/* Network is full... */
पूर्ण


/* Perक्रमm AARP probing क्रम a proxy address */
अटल पूर्णांक atअगर_proxy_probe_device(काष्ठा atalk_अगरace *atअगर,
				   काष्ठा atalk_addr *proxy_addr)
अणु
	पूर्णांक netrange = ntohs(atअगर->nets.nr_lastnet) -
			ntohs(atअगर->nets.nr_firstnet) + 1;
	/* we probe the पूर्णांकerface's network */
	पूर्णांक probe_net = ntohs(atअगर->address.s_net);
	पूर्णांक probe_node = ATADDR_ANYNODE;	    /* we'll take anything */
	पूर्णांक netct, nodect;

	/* Offset the network we start probing with */
	अगर (probe_net == ATADDR_ANYNET) अणु
		probe_net = ntohs(atअगर->nets.nr_firstnet);
		अगर (netrange)
			probe_net += jअगरfies % netrange;
	पूर्ण

	अगर (probe_node == ATADDR_ANYNODE)
		probe_node = jअगरfies & 0xFF;

	/* Scan the networks */
	क्रम (netct = 0; netct <= netrange; netct++) अणु
		/* Sweep the available nodes from a given start */
		proxy_addr->s_net = htons(probe_net);
		क्रम (nodect = 0; nodect < 256; nodect++) अणु
			proxy_addr->s_node = (nodect + probe_node) & 0xFF;
			अगर (proxy_addr->s_node > 0 &&
			    proxy_addr->s_node < 254) अणु
				/* Tell AARP to probe a proposed address */
				पूर्णांक ret = aarp_proxy_probe_network(atअगर,
								    proxy_addr);

				अगर (ret != -EADDRINUSE)
					वापस ret;
			पूर्ण
		पूर्ण
		probe_net++;
		अगर (probe_net > ntohs(atअगर->nets.nr_lastnet))
			probe_net = ntohs(atअगर->nets.nr_firstnet);
	पूर्ण

	वापस -EADDRINUSE;	/* Network is full... */
पूर्ण


काष्ठा atalk_addr *atalk_find_dev_addr(काष्ठा net_device *dev)
अणु
	काष्ठा atalk_अगरace *अगरace = dev->atalk_ptr;
	वापस अगरace ? &अगरace->address : शून्य;
पूर्ण

अटल काष्ठा atalk_addr *atalk_find_primary(व्योम)
अणु
	काष्ठा atalk_अगरace *fअगरace = शून्य;
	काष्ठा atalk_addr *retval;
	काष्ठा atalk_अगरace *अगरace;

	/*
	 * Return a poपूर्णांक-to-poपूर्णांक पूर्णांकerface only अगर
	 * there is no non-ptp पूर्णांकerface available.
	 */
	पढ़ो_lock_bh(&atalk_पूर्णांकerfaces_lock);
	क्रम (अगरace = atalk_पूर्णांकerfaces; अगरace; अगरace = अगरace->next) अणु
		अगर (!fअगरace && !(अगरace->dev->flags & IFF_LOOPBACK))
			fअगरace = अगरace;
		अगर (!(अगरace->dev->flags & (IFF_LOOPBACK | IFF_POINTOPOINT))) अणु
			retval = &अगरace->address;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (fअगरace)
		retval = &fअगरace->address;
	अन्यथा अगर (atalk_पूर्णांकerfaces)
		retval = &atalk_पूर्णांकerfaces->address;
	अन्यथा
		retval = शून्य;
out:
	पढ़ो_unlock_bh(&atalk_पूर्णांकerfaces_lock);
	वापस retval;
पूर्ण

/*
 * Find a match क्रम 'any network' - ie any of our पूर्णांकerfaces with that
 * node number will करो just nicely.
 */
अटल काष्ठा atalk_अगरace *atalk_find_anynet(पूर्णांक node, काष्ठा net_device *dev)
अणु
	काष्ठा atalk_अगरace *अगरace = dev->atalk_ptr;

	अगर (!अगरace || अगरace->status & ATIF_PROBE)
		जाओ out_err;

	अगर (node != ATADDR_BCAST &&
	    अगरace->address.s_node != node &&
	    node != ATADDR_ANYNODE)
		जाओ out_err;
out:
	वापस अगरace;
out_err:
	अगरace = शून्य;
	जाओ out;
पूर्ण

/* Find a match क्रम a specअगरic network:node pair */
अटल काष्ठा atalk_अगरace *atalk_find_पूर्णांकerface(__be16 net, पूर्णांक node)
अणु
	काष्ठा atalk_अगरace *अगरace;

	पढ़ो_lock_bh(&atalk_पूर्णांकerfaces_lock);
	क्रम (अगरace = atalk_पूर्णांकerfaces; अगरace; अगरace = अगरace->next) अणु
		अगर ((node == ATADDR_BCAST ||
		     node == ATADDR_ANYNODE ||
		     अगरace->address.s_node == node) &&
		    अगरace->address.s_net == net &&
		    !(अगरace->status & ATIF_PROBE))
			अवरोध;

		/* XXXX.0 -- net.0 वापसs the अगरace associated with net */
		अगर (node == ATADDR_ANYNODE && net != ATADDR_ANYNET &&
		    ntohs(अगरace->nets.nr_firstnet) <= ntohs(net) &&
		    ntohs(net) <= ntohs(अगरace->nets.nr_lastnet))
			अवरोध;
	पूर्ण
	पढ़ो_unlock_bh(&atalk_पूर्णांकerfaces_lock);
	वापस अगरace;
पूर्ण


/*
 * Find a route क्रम an AppleTalk packet. This ought to get cached in
 * the socket (later on...). We know about host routes and the fact
 * that a route must be direct to broadcast.
 */
अटल काष्ठा atalk_route *atrtr_find(काष्ठा atalk_addr *target)
अणु
	/*
	 * we must search through all routes unless we find a
	 * host route, because some host routes might overlap
	 * network routes
	 */
	काष्ठा atalk_route *net_route = शून्य;
	काष्ठा atalk_route *r;

	पढ़ो_lock_bh(&atalk_routes_lock);
	क्रम (r = atalk_routes; r; r = r->next) अणु
		अगर (!(r->flags & RTF_UP))
			जारी;

		अगर (r->target.s_net == target->s_net) अणु
			अगर (r->flags & RTF_HOST) अणु
				/*
				 * अगर this host route is क्रम the target,
				 * the we're करोne
				 */
				अगर (r->target.s_node == target->s_node)
					जाओ out;
			पूर्ण अन्यथा
				/*
				 * this route will work अगर there isn't a
				 * direct host route, so cache it
				 */
				net_route = r;
		पूर्ण
	पूर्ण

	/*
	 * अगर we found a network route but not a direct host
	 * route, then वापस it
	 */
	अगर (net_route)
		r = net_route;
	अन्यथा अगर (atrtr_शेष.dev)
		r = &atrtr_शेष;
	अन्यथा /* No route can be found */
		r = शून्य;
out:
	पढ़ो_unlock_bh(&atalk_routes_lock);
	वापस r;
पूर्ण


/*
 * Given an AppleTalk network, find the device to use. This can be
 * a simple lookup.
 */
काष्ठा net_device *atrtr_get_dev(काष्ठा atalk_addr *sa)
अणु
	काष्ठा atalk_route *atr = atrtr_find(sa);
	वापस atr ? atr->dev : शून्य;
पूर्ण

/* Set up a शेष router */
अटल व्योम atrtr_set_शेष(काष्ठा net_device *dev)
अणु
	atrtr_शेष.dev	     = dev;
	atrtr_शेष.flags	     = RTF_UP;
	atrtr_शेष.gateway.s_net  = htons(0);
	atrtr_शेष.gateway.s_node = 0;
पूर्ण

/*
 * Add a router. Basically make sure it looks valid and stuff the
 * entry in the list. While it uses netranges we always set them to one
 * entry to work like netatalk.
 */
अटल पूर्णांक atrtr_create(काष्ठा rtentry *r, काष्ठा net_device *devhपूर्णांक)
अणु
	काष्ठा sockaddr_at *ta = (काष्ठा sockaddr_at *)&r->rt_dst;
	काष्ठा sockaddr_at *ga = (काष्ठा sockaddr_at *)&r->rt_gateway;
	काष्ठा atalk_route *rt;
	काष्ठा atalk_अगरace *अगरace, *rअगरace;
	पूर्णांक retval = -EINVAL;

	/*
	 * Fixme: Raise/Lower a routing change semaphore क्रम these
	 * operations.
	 */

	/* Validate the request */
	अगर (ta->sat_family != AF_APPLETALK ||
	    (!devhपूर्णांक && ga->sat_family != AF_APPLETALK))
		जाओ out;

	/* Now walk the routing table and make our decisions */
	ग_लिखो_lock_bh(&atalk_routes_lock);
	क्रम (rt = atalk_routes; rt; rt = rt->next) अणु
		अगर (r->rt_flags != rt->flags)
			जारी;

		अगर (ta->sat_addr.s_net == rt->target.s_net) अणु
			अगर (!(rt->flags & RTF_HOST))
				अवरोध;
			अगर (ta->sat_addr.s_node == rt->target.s_node)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!devhपूर्णांक) अणु
		rअगरace = शून्य;

		पढ़ो_lock_bh(&atalk_पूर्णांकerfaces_lock);
		क्रम (अगरace = atalk_पूर्णांकerfaces; अगरace; अगरace = अगरace->next) अणु
			अगर (!rअगरace &&
			    ntohs(ga->sat_addr.s_net) >=
					ntohs(अगरace->nets.nr_firstnet) &&
			    ntohs(ga->sat_addr.s_net) <=
					ntohs(अगरace->nets.nr_lastnet))
				rअगरace = अगरace;

			अगर (ga->sat_addr.s_net == अगरace->address.s_net &&
			    ga->sat_addr.s_node == अगरace->address.s_node)
				rअगरace = अगरace;
		पूर्ण
		पढ़ो_unlock_bh(&atalk_पूर्णांकerfaces_lock);

		retval = -ENETUNREACH;
		अगर (!rअगरace)
			जाओ out_unlock;

		devhपूर्णांक = rअगरace->dev;
	पूर्ण

	अगर (!rt) अणु
		rt = kzalloc(माप(*rt), GFP_ATOMIC);

		retval = -ENOBUFS;
		अगर (!rt)
			जाओ out_unlock;

		rt->next = atalk_routes;
		atalk_routes = rt;
	पूर्ण

	/* Fill in the routing entry */
	rt->target  = ta->sat_addr;
	dev_hold(devhपूर्णांक);
	rt->dev     = devhपूर्णांक;
	rt->flags   = r->rt_flags;
	rt->gateway = ga->sat_addr;

	retval = 0;
out_unlock:
	ग_लिखो_unlock_bh(&atalk_routes_lock);
out:
	वापस retval;
पूर्ण

/* Delete a route. Find it and discard it */
अटल पूर्णांक atrtr_delete(काष्ठा atalk_addr *addr)
अणु
	काष्ठा atalk_route **r = &atalk_routes;
	पूर्णांक retval = 0;
	काष्ठा atalk_route *पंचांगp;

	ग_लिखो_lock_bh(&atalk_routes_lock);
	जबतक ((पंचांगp = *r) != शून्य) अणु
		अगर (पंचांगp->target.s_net == addr->s_net &&
		    (!(पंचांगp->flags&RTF_GATEWAY) ||
		     पंचांगp->target.s_node == addr->s_node)) अणु
			*r = पंचांगp->next;
			dev_put(पंचांगp->dev);
			kमुक्त(पंचांगp);
			जाओ out;
		पूर्ण
		r = &पंचांगp->next;
	पूर्ण
	retval = -ENOENT;
out:
	ग_लिखो_unlock_bh(&atalk_routes_lock);
	वापस retval;
पूर्ण

/*
 * Called when a device is करोwned. Just throw away any routes
 * via it.
 */
अटल व्योम atrtr_device_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा atalk_route **r = &atalk_routes;
	काष्ठा atalk_route *पंचांगp;

	ग_लिखो_lock_bh(&atalk_routes_lock);
	जबतक ((पंचांगp = *r) != शून्य) अणु
		अगर (पंचांगp->dev == dev) अणु
			*r = पंचांगp->next;
			dev_put(dev);
			kमुक्त(पंचांगp);
		पूर्ण अन्यथा
			r = &पंचांगp->next;
	पूर्ण
	ग_लिखो_unlock_bh(&atalk_routes_lock);

	अगर (atrtr_शेष.dev == dev)
		atrtr_set_शेष(शून्य);
पूर्ण

/* Actually करोwn the पूर्णांकerface */
अटल अंतरभूत व्योम atalk_dev_करोwn(काष्ठा net_device *dev)
अणु
	atrtr_device_करोwn(dev);	/* Remove all routes क्रम the device */
	aarp_device_करोwn(dev);	/* Remove AARP entries क्रम the device */
	atअगर_drop_device(dev);	/* Remove the device */
पूर्ण

/*
 * A device event has occurred. Watch क्रम devices going करोwn and
 * delete our use of them (अगरace and route).
 */
अटल पूर्णांक ddp_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_DOWN)
		/* Discard any use of this */
		atalk_dev_करोwn(dev);

	वापस NOTIFY_DONE;
पूर्ण

/* ioctl calls. Shouldn't even need touching */
/* Device configuration ioctl calls */
अटल पूर्णांक atअगर_ioctl(पूर्णांक cmd, व्योम __user *arg)
अणु
	अटल अक्षर aarp_mcast[6] = अणु 0x09, 0x00, 0x00, 0xFF, 0xFF, 0xFF पूर्ण;
	काष्ठा अगरreq atreq;
	काष्ठा atalk_netrange *nr;
	काष्ठा sockaddr_at *sa;
	काष्ठा net_device *dev;
	काष्ठा atalk_अगरace *atअगर;
	पूर्णांक ct;
	पूर्णांक limit;
	काष्ठा rtentry rtdef;
	पूर्णांक add_route;

	अगर (copy_from_user(&atreq, arg, माप(atreq)))
		वापस -EFAULT;

	dev = __dev_get_by_name(&init_net, atreq.अगरr_name);
	अगर (!dev)
		वापस -ENODEV;

	sa = (काष्ठा sockaddr_at *)&atreq.अगरr_addr;
	atअगर = atalk_find_dev(dev);

	चयन (cmd) अणु
	हाल SIOCSIFADDR:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (sa->sat_family != AF_APPLETALK)
			वापस -EINVAL;
		अगर (dev->type != ARPHRD_ETHER &&
		    dev->type != ARPHRD_LOOPBACK &&
		    dev->type != ARPHRD_LOCALTLK &&
		    dev->type != ARPHRD_PPP)
			वापस -EPROTONOSUPPORT;

		nr = (काष्ठा atalk_netrange *)&sa->sat_zero[0];
		add_route = 1;

		/*
		 * अगर this is a poपूर्णांक-to-poपूर्णांक अगरace, and we alपढ़ोy
		 * have an अगरace क्रम this AppleTalk address, then we
		 * should not add a route
		 */
		अगर ((dev->flags & IFF_POINTOPOINT) &&
		    atalk_find_पूर्णांकerface(sa->sat_addr.s_net,
					 sa->sat_addr.s_node)) अणु
			prपूर्णांकk(KERN_DEBUG "AppleTalk: point-to-point "
			       "interface added with "
			       "existing address\n");
			add_route = 0;
		पूर्ण

		/*
		 * Phase 1 is fine on LocalTalk but we करोn't करो
		 * EtherTalk phase 1. Anyone wanting to add it go ahead.
		 */
		अगर (dev->type == ARPHRD_ETHER && nr->nr_phase != 2)
			वापस -EPROTONOSUPPORT;
		अगर (sa->sat_addr.s_node == ATADDR_BCAST ||
		    sa->sat_addr.s_node == 254)
			वापस -EINVAL;
		अगर (atअगर) अणु
			/* Alपढ़ोy setting address */
			अगर (atअगर->status & ATIF_PROBE)
				वापस -EBUSY;

			atअगर->address.s_net  = sa->sat_addr.s_net;
			atअगर->address.s_node = sa->sat_addr.s_node;
			atrtr_device_करोwn(dev);	/* Flush old routes */
		पूर्ण अन्यथा अणु
			atअगर = atअगर_add_device(dev, &sa->sat_addr);
			अगर (!atअगर)
				वापस -ENOMEM;
		पूर्ण
		atअगर->nets = *nr;

		/*
		 * Check अगर the chosen address is used. If so we
		 * error and atalkd will try another.
		 */

		अगर (!(dev->flags & IFF_LOOPBACK) &&
		    !(dev->flags & IFF_POINTOPOINT) &&
		    atअगर_probe_device(atअगर) < 0) अणु
			atअगर_drop_device(dev);
			वापस -EADDRINUSE;
		पूर्ण

		/* Hey it worked - add the direct routes */
		sa = (काष्ठा sockaddr_at *)&rtdef.rt_gateway;
		sa->sat_family = AF_APPLETALK;
		sa->sat_addr.s_net  = atअगर->address.s_net;
		sa->sat_addr.s_node = atअगर->address.s_node;
		sa = (काष्ठा sockaddr_at *)&rtdef.rt_dst;
		rtdef.rt_flags = RTF_UP;
		sa->sat_family = AF_APPLETALK;
		sa->sat_addr.s_node = ATADDR_ANYNODE;
		अगर (dev->flags & IFF_LOOPBACK ||
		    dev->flags & IFF_POINTOPOINT)
			rtdef.rt_flags |= RTF_HOST;

		/* Routerless initial state */
		अगर (nr->nr_firstnet == htons(0) &&
		    nr->nr_lastnet == htons(0xFFFE)) अणु
			sa->sat_addr.s_net = atअगर->address.s_net;
			atrtr_create(&rtdef, dev);
			atrtr_set_शेष(dev);
		पूर्ण अन्यथा अणु
			limit = ntohs(nr->nr_lastnet);
			अगर (limit - ntohs(nr->nr_firstnet) > 4096) अणु
				prपूर्णांकk(KERN_WARNING "Too many routes/"
				       "iface.\n");
				वापस -EINVAL;
			पूर्ण
			अगर (add_route)
				क्रम (ct = ntohs(nr->nr_firstnet);
				     ct <= limit; ct++) अणु
					sa->sat_addr.s_net = htons(ct);
					atrtr_create(&rtdef, dev);
				पूर्ण
		पूर्ण
		dev_mc_add_global(dev, aarp_mcast);
		वापस 0;

	हाल SIOCGIFADDR:
		अगर (!atअगर)
			वापस -EADDRNOTAVAIL;

		sa->sat_family = AF_APPLETALK;
		sa->sat_addr = atअगर->address;
		अवरोध;

	हाल SIOCGIFBRDADDR:
		अगर (!atअगर)
			वापस -EADDRNOTAVAIL;

		sa->sat_family = AF_APPLETALK;
		sa->sat_addr.s_net = atअगर->address.s_net;
		sa->sat_addr.s_node = ATADDR_BCAST;
		अवरोध;

	हाल SIOCATALKDIFADDR:
	हाल SIOCDIFADDR:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (sa->sat_family != AF_APPLETALK)
			वापस -EINVAL;
		atalk_dev_करोwn(dev);
		अवरोध;

	हाल SIOCSARP:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (sa->sat_family != AF_APPLETALK)
			वापस -EINVAL;
		/*
		 * क्रम now, we only support proxy AARP on ELAP;
		 * we should be able to करो it क्रम LocalTalk, too.
		 */
		अगर (dev->type != ARPHRD_ETHER)
			वापस -EPROTONOSUPPORT;

		/*
		 * atअगर poपूर्णांकs to the current पूर्णांकerface on this network;
		 * we aren't concerned about its current status (at
		 * least क्रम now), but it has all the settings about
		 * the network we're going to probe. Consequently, it
		 * must exist.
		 */
		अगर (!atअगर)
			वापस -EADDRNOTAVAIL;

		nr = (काष्ठा atalk_netrange *)&(atअगर->nets);
		/*
		 * Phase 1 is fine on Localtalk but we करोn't करो
		 * Ethertalk phase 1. Anyone wanting to add it go ahead.
		 */
		अगर (dev->type == ARPHRD_ETHER && nr->nr_phase != 2)
			वापस -EPROTONOSUPPORT;

		अगर (sa->sat_addr.s_node == ATADDR_BCAST ||
		    sa->sat_addr.s_node == 254)
			वापस -EINVAL;

		/*
		 * Check अगर the chosen address is used. If so we
		 * error and ATCP will try another.
		 */
		अगर (atअगर_proxy_probe_device(atअगर, &(sa->sat_addr)) < 0)
			वापस -EADDRINUSE;

		/*
		 * We now have an address on the local network, and
		 * the AARP code will defend it क्रम us until we take it
		 * करोwn. We करोn't set up any routes right now, because
		 * ATCP will install them manually via SIOCADDRT.
		 */
		अवरोध;

	हाल SIOCDARP:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (sa->sat_family != AF_APPLETALK)
			वापस -EINVAL;
		अगर (!atअगर)
			वापस -EADDRNOTAVAIL;

		/* give to aarp module to हटाओ proxy entry */
		aarp_proxy_हटाओ(atअगर->dev, &(sa->sat_addr));
		वापस 0;
	पूर्ण

	वापस copy_to_user(arg, &atreq, माप(atreq)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक atrtr_ioctl_addrt(काष्ठा rtentry *rt)
अणु
	काष्ठा net_device *dev = शून्य;

	अगर (rt->rt_dev) अणु
		अक्षर name[IFNAMSIZ];

		अगर (copy_from_user(name, rt->rt_dev, IFNAMSIZ-1))
			वापस -EFAULT;
		name[IFNAMSIZ-1] = '\0';

		dev = __dev_get_by_name(&init_net, name);
		अगर (!dev)
			वापस -ENODEV;
	पूर्ण
	वापस atrtr_create(rt, dev);
पूर्ण

/* Routing ioctl() calls */
अटल पूर्णांक atrtr_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा rtentry rt;

	अगर (copy_from_user(&rt, arg, माप(rt)))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल SIOCDELRT:
		अगर (rt.rt_dst.sa_family != AF_APPLETALK)
			वापस -EINVAL;
		वापस atrtr_delete(&((काष्ठा sockaddr_at *)
				      &rt.rt_dst)->sat_addr);

	हाल SIOCADDRT:
		वापस atrtr_ioctl_addrt(&rt);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**************************************************************************\
*                                                                          *
* Handling क्रम प्रणाली calls applied via the various पूर्णांकerfaces to an       *
* AppleTalk socket object.                                                 *
*                                                                          *
\**************************************************************************/

/*
 * Checksum: This is 'optional'. It's quite likely also a good
 * candidate क्रम assembler hackery 8)
 */
अटल अचिन्हित दीर्घ atalk_sum_partial(स्थिर अचिन्हित अक्षर *data,
				       पूर्णांक len, अचिन्हित दीर्घ sum)
अणु
	/* This ought to be unwrapped neatly. I'll trust gcc क्रम now */
	जबतक (len--) अणु
		sum += *data++;
		sum = rol16(sum, 1);
	पूर्ण
	वापस sum;
पूर्ण

/*  Checksum skb data --  similar to skb_checksum  */
अटल अचिन्हित दीर्घ atalk_sum_skb(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
				   पूर्णांक len, अचिन्हित दीर्घ sum)
अणु
	पूर्णांक start = skb_headlen(skb);
	काष्ठा sk_buff *frag_iter;
	पूर्णांक i, copy;

	/* checksum stuff in header space */
	अगर ((copy = start - offset) > 0) अणु
		अगर (copy > len)
			copy = len;
		sum = atalk_sum_partial(skb->data + offset, copy, sum);
		अगर ((len -= copy) == 0)
			वापस sum;

		offset += copy;
	पूर्ण

	/* checksum stuff in frags */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक end;
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		WARN_ON(start > offset + len);

		end = start + skb_frag_size(frag);
		अगर ((copy = end - offset) > 0) अणु
			u8 *vaddr;

			अगर (copy > len)
				copy = len;
			vaddr = kmap_atomic(skb_frag_page(frag));
			sum = atalk_sum_partial(vaddr + skb_frag_off(frag) +
						offset - start, copy, sum);
			kunmap_atomic(vaddr);

			अगर (!(len -= copy))
				वापस sum;
			offset += copy;
		पूर्ण
		start = end;
	पूर्ण

	skb_walk_frags(skb, frag_iter) अणु
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + frag_iter->len;
		अगर ((copy = end - offset) > 0) अणु
			अगर (copy > len)
				copy = len;
			sum = atalk_sum_skb(frag_iter, offset - start,
					    copy, sum);
			अगर ((len -= copy) == 0)
				वापस sum;
			offset += copy;
		पूर्ण
		start = end;
	पूर्ण

	BUG_ON(len > 0);

	वापस sum;
पूर्ण

अटल __be16 atalk_checksum(स्थिर काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	अचिन्हित दीर्घ sum;

	/* skip header 4 bytes */
	sum = atalk_sum_skb(skb, 4, len-4, 0);

	/* Use 0xFFFF क्रम 0. 0 itself means none */
	वापस sum ? htons((अचिन्हित लघु)sum) : htons(0xFFFF);
पूर्ण

अटल काष्ठा proto ddp_proto = अणु
	.name	  = "DDP",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा atalk_sock),
पूर्ण;

/*
 * Create a socket. Initialise the socket, blank the addresses
 * set the state.
 */
अटल पूर्णांक atalk_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	पूर्णांक rc = -ESOCKTNOSUPPORT;

	अगर (!net_eq(net, &init_net))
		वापस -EAFNOSUPPORT;

	/*
	 * We permit SOCK_DGRAM and RAW is an extension. It is trivial to करो
	 * and gives you the full ELAP frame. Should be handy क्रम CAP 8)
	 */
	अगर (sock->type != SOCK_RAW && sock->type != SOCK_DGRAM)
		जाओ out;

	rc = -EPERM;
	अगर (sock->type == SOCK_RAW && !kern && !capable(CAP_NET_RAW))
		जाओ out;

	rc = -ENOMEM;
	sk = sk_alloc(net, PF_APPLETALK, GFP_KERNEL, &ddp_proto, kern);
	अगर (!sk)
		जाओ out;
	rc = 0;
	sock->ops = &atalk_dgram_ops;
	sock_init_data(sock, sk);

	/* Checksums on by शेष */
	sock_set_flag(sk, SOCK_ZAPPED);
out:
	वापस rc;
पूर्ण

/* Free a socket. No work needed */
अटल पूर्णांक atalk_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk) अणु
		sock_hold(sk);
		lock_sock(sk);

		sock_orphan(sk);
		sock->sk = शून्य;
		atalk_destroy_socket(sk);

		release_sock(sk);
		sock_put(sk);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * atalk_pick_and_bind_port - Pick a source port when one is not given
 * @sk: socket to insert पूर्णांकo the tables
 * @sat: address to search क्रम
 *
 * Pick a source port when one is not given. If we can find a suitable मुक्त
 * one, we insert the socket पूर्णांकo the tables using it.
 *
 * This whole operation must be atomic.
 */
अटल पूर्णांक atalk_pick_and_bind_port(काष्ठा sock *sk, काष्ठा sockaddr_at *sat)
अणु
	पूर्णांक retval;

	ग_लिखो_lock_bh(&atalk_sockets_lock);

	क्रम (sat->sat_port = ATPORT_RESERVED;
	     sat->sat_port < ATPORT_LAST;
	     sat->sat_port++) अणु
		काष्ठा sock *s;

		sk_क्रम_each(s, &atalk_sockets) अणु
			काष्ठा atalk_sock *at = at_sk(s);

			अगर (at->src_net == sat->sat_addr.s_net &&
			    at->src_node == sat->sat_addr.s_node &&
			    at->src_port == sat->sat_port)
				जाओ try_next_port;
		पूर्ण

		/* Wheee, it's मुक्त, assign and insert. */
		__atalk_insert_socket(sk);
		at_sk(sk)->src_port = sat->sat_port;
		retval = 0;
		जाओ out;

try_next_port:;
	पूर्ण

	retval = -EBUSY;
out:
	ग_लिखो_unlock_bh(&atalk_sockets_lock);
	वापस retval;
पूर्ण

अटल पूर्णांक atalk_स्वतःbind(काष्ठा sock *sk)
अणु
	काष्ठा atalk_sock *at = at_sk(sk);
	काष्ठा sockaddr_at sat;
	काष्ठा atalk_addr *ap = atalk_find_primary();
	पूर्णांक n = -EADDRNOTAVAIL;

	अगर (!ap || ap->s_net == htons(ATADDR_ANYNET))
		जाओ out;

	at->src_net  = sat.sat_addr.s_net  = ap->s_net;
	at->src_node = sat.sat_addr.s_node = ap->s_node;

	n = atalk_pick_and_bind_port(sk, &sat);
	अगर (!n)
		sock_reset_flag(sk, SOCK_ZAPPED);
out:
	वापस n;
पूर्ण

/* Set the address 'our end' of the connection */
अटल पूर्णांक atalk_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_at *addr = (काष्ठा sockaddr_at *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा atalk_sock *at = at_sk(sk);
	पूर्णांक err;

	अगर (!sock_flag(sk, SOCK_ZAPPED) ||
	    addr_len != माप(काष्ठा sockaddr_at))
		वापस -EINVAL;

	अगर (addr->sat_family != AF_APPLETALK)
		वापस -EAFNOSUPPORT;

	lock_sock(sk);
	अगर (addr->sat_addr.s_net == htons(ATADDR_ANYNET)) अणु
		काष्ठा atalk_addr *ap = atalk_find_primary();

		err = -EADDRNOTAVAIL;
		अगर (!ap)
			जाओ out;

		at->src_net  = addr->sat_addr.s_net = ap->s_net;
		at->src_node = addr->sat_addr.s_node = ap->s_node;
	पूर्ण अन्यथा अणु
		err = -EADDRNOTAVAIL;
		अगर (!atalk_find_पूर्णांकerface(addr->sat_addr.s_net,
					  addr->sat_addr.s_node))
			जाओ out;

		at->src_net  = addr->sat_addr.s_net;
		at->src_node = addr->sat_addr.s_node;
	पूर्ण

	अगर (addr->sat_port == ATADDR_ANYPORT) अणु
		err = atalk_pick_and_bind_port(sk, addr);

		अगर (err < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		at->src_port = addr->sat_port;

		err = -EADDRINUSE;
		अगर (atalk_find_or_insert_socket(sk, addr))
			जाओ out;
	पूर्ण

	sock_reset_flag(sk, SOCK_ZAPPED);
	err = 0;
out:
	release_sock(sk);
	वापस err;
पूर्ण

/* Set the address we talk to */
अटल पूर्णांक atalk_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			 पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा atalk_sock *at = at_sk(sk);
	काष्ठा sockaddr_at *addr;
	पूर्णांक err;

	sk->sk_state   = TCP_CLOSE;
	sock->state = SS_UNCONNECTED;

	अगर (addr_len != माप(*addr))
		वापस -EINVAL;

	addr = (काष्ठा sockaddr_at *)uaddr;

	अगर (addr->sat_family != AF_APPLETALK)
		वापस -EAFNOSUPPORT;

	अगर (addr->sat_addr.s_node == ATADDR_BCAST &&
	    !sock_flag(sk, SOCK_BROADCAST)) अणु
#अगर 1
		pr_warn("atalk_connect: %s is broken and did not set SO_BROADCAST.\n",
			current->comm);
#अन्यथा
		वापस -EACCES;
#पूर्ण_अगर
	पूर्ण

	lock_sock(sk);
	err = -EBUSY;
	अगर (sock_flag(sk, SOCK_ZAPPED))
		अगर (atalk_स्वतःbind(sk) < 0)
			जाओ out;

	err = -ENETUNREACH;
	अगर (!atrtr_get_dev(&addr->sat_addr))
		जाओ out;

	at->dest_port = addr->sat_port;
	at->dest_net  = addr->sat_addr.s_net;
	at->dest_node = addr->sat_addr.s_node;

	sock->state  = SS_CONNECTED;
	sk->sk_state = TCP_ESTABLISHED;
	err = 0;
out:
	release_sock(sk);
	वापस err;
पूर्ण

/*
 * Find the name of an AppleTalk socket. Just copy the right
 * fields पूर्णांकo the sockaddr.
 */
अटल पूर्णांक atalk_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			 पूर्णांक peer)
अणु
	काष्ठा sockaddr_at sat;
	काष्ठा sock *sk = sock->sk;
	काष्ठा atalk_sock *at = at_sk(sk);
	पूर्णांक err;

	lock_sock(sk);
	err = -ENOBUFS;
	अगर (sock_flag(sk, SOCK_ZAPPED))
		अगर (atalk_स्वतःbind(sk) < 0)
			जाओ out;

	स_रखो(&sat, 0, माप(sat));

	अगर (peer) अणु
		err = -ENOTCONN;
		अगर (sk->sk_state != TCP_ESTABLISHED)
			जाओ out;

		sat.sat_addr.s_net  = at->dest_net;
		sat.sat_addr.s_node = at->dest_node;
		sat.sat_port	    = at->dest_port;
	पूर्ण अन्यथा अणु
		sat.sat_addr.s_net  = at->src_net;
		sat.sat_addr.s_node = at->src_node;
		sat.sat_port	    = at->src_port;
	पूर्ण

	sat.sat_family = AF_APPLETALK;
	स_नकल(uaddr, &sat, माप(sat));
	err = माप(काष्ठा sockaddr_at);

out:
	release_sock(sk);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPDDP)
अटल __अंतरभूत__ पूर्णांक is_ip_over_ddp(काष्ठा sk_buff *skb)
अणु
	वापस skb->data[12] == 22;
पूर्ण

अटल पूर्णांक handle_ip_over_ddp(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = __dev_get_by_name(&init_net, "ipddp0");
	काष्ठा net_device_stats *stats;

	/* This needs to be able to handle ipddp"N" devices */
	अगर (!dev) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	skb->protocol = htons(ETH_P_IP);
	skb_pull(skb, 13);
	skb->dev   = dev;
	skb_reset_transport_header(skb);

	stats = netdev_priv(dev);
	stats->rx_packets++;
	stats->rx_bytes += skb->len + 13;
	वापस netअगर_rx(skb);  /* Send the SKB up to a higher place. */
पूर्ण
#अन्यथा
/* make it easy क्रम gcc to optimize this test out, i.e. समाप्त the code */
#घोषणा is_ip_over_ddp(skb) 0
#घोषणा handle_ip_over_ddp(skb) 0
#पूर्ण_अगर

अटल पूर्णांक atalk_route_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			      काष्ठा ddpehdr *ddp, __u16 len_hops, पूर्णांक origlen)
अणु
	काष्ठा atalk_route *rt;
	काष्ठा atalk_addr ta;

	/*
	 * Don't route multicast, etc., packets, or packets sent to "this
	 * network"
	 */
	अगर (skb->pkt_type != PACKET_HOST || !ddp->deh_dnet) अणु
		/*
		 * FIXME:
		 *
		 * Can it ever happen that a packet is from a PPP अगरace and
		 * needs to be broadcast onto the शेष network?
		 */
		अगर (dev->type == ARPHRD_PPP)
			prपूर्णांकk(KERN_DEBUG "AppleTalk: didn't forward broadcast "
					  "packet received from PPP iface\n");
		जाओ मुक्त_it;
	पूर्ण

	ta.s_net  = ddp->deh_dnet;
	ta.s_node = ddp->deh_dnode;

	/* Route the packet */
	rt = atrtr_find(&ta);
	/* increment hops count */
	len_hops += 1 << 10;
	अगर (!rt || !(len_hops & (15 << 10)))
		जाओ मुक्त_it;

	/* FIXME: use skb->cb to be able to use shared skbs */

	/*
	 * Route goes through another gateway, so set the target to the
	 * gateway instead.
	 */

	अगर (rt->flags & RTF_GATEWAY) अणु
		ta.s_net  = rt->gateway.s_net;
		ta.s_node = rt->gateway.s_node;
	पूर्ण

	/* Fix up skb->len field */
	skb_trim(skb, min_t(अचिन्हित पूर्णांक, origlen,
			    (rt->dev->hard_header_len +
			     ddp_dl->header_length + (len_hops & 1023))));

	/* FIXME: use skb->cb to be able to use shared skbs */
	ddp->deh_len_hops = htons(len_hops);

	/*
	 * Send the buffer onwards
	 *
	 * Now we must always be careful. If it's come from LocalTalk to
	 * EtherTalk it might not fit
	 *
	 * Order matters here: If a packet has to be copied to make a new
	 * headroom (rare hopefully) then it won't need unsharing.
	 *
	 * Note. ddp-> becomes invalid at the पुनः_स्मृति.
	 */
	अगर (skb_headroom(skb) < 22) अणु
		/* 22 bytes - 12 ether, 2 len, 3 802.2 5 snap */
		काष्ठा sk_buff *nskb = skb_पुनः_स्मृति_headroom(skb, 32);
		kमुक्त_skb(skb);
		skb = nskb;
	पूर्ण अन्यथा
		skb = skb_unshare(skb, GFP_ATOMIC);

	/*
	 * If the buffer didn't vanish पूर्णांकo the lack of space bitbucket we can
	 * send it.
	 */
	अगर (skb == शून्य)
		जाओ drop;

	अगर (aarp_send_ddp(rt->dev, skb, &ta, शून्य) == NET_XMIT_DROP)
		वापस NET_RX_DROP;
	वापस NET_RX_SUCCESS;
मुक्त_it:
	kमुक्त_skb(skb);
drop:
	वापस NET_RX_DROP;
पूर्ण

/**
 *	atalk_rcv - Receive a packet (in skb) from device dev
 *	@skb: packet received
 *	@dev: network device where the packet comes from
 *	@pt: packet type
 *	@orig_dev: the original receive net device
 *
 *	Receive a packet (in skb) from device dev. This has come from the SNAP
 *	decoder, and on entry skb->transport_header is the DDP header, skb->len
 *	is the DDP header, skb->len is the DDP length. The physical headers
 *	have been extracted. PPP should probably pass frames marked as क्रम this
 *	layer.  [ie ARPHRD_ETHERTALK]
 */
अटल पूर्णांक atalk_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा ddpehdr *ddp;
	काष्ठा sock *sock;
	काष्ठा atalk_अगरace *atअगर;
	काष्ठा sockaddr_at tosat;
	पूर्णांक origlen;
	__u16 len_hops;

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ drop;

	/* Don't mangle buffer अगर shared */
	अगर (!(skb = skb_share_check(skb, GFP_ATOMIC)))
		जाओ out;

	/* Size check and make sure header is contiguous */
	अगर (!pskb_may_pull(skb, माप(*ddp)))
		जाओ drop;

	ddp = ddp_hdr(skb);

	len_hops = ntohs(ddp->deh_len_hops);

	/* Trim buffer in हाल of stray trailing data */
	origlen = skb->len;
	skb_trim(skb, min_t(अचिन्हित पूर्णांक, skb->len, len_hops & 1023));

	/*
	 * Size check to see अगर ddp->deh_len was crap
	 * (Otherwise we'll detonate most spectacularly
	 * in the middle of atalk_checksum() or recvmsg()).
	 */
	अगर (skb->len < माप(*ddp) || skb->len < (len_hops & 1023)) अणु
		pr_debug("AppleTalk: dropping corrupted frame (deh_len=%u, "
			 "skb->len=%u)\n", len_hops & 1023, skb->len);
		जाओ drop;
	पूर्ण

	/*
	 * Any checksums. Note we करोn't करो htons() on this == is assumed to be
	 * valid क्रम net byte orders all over the networking code...
	 */
	अगर (ddp->deh_sum &&
	    atalk_checksum(skb, len_hops & 1023) != ddp->deh_sum)
		/* Not a valid AppleTalk frame - dustbin समय */
		जाओ drop;

	/* Check the packet is aimed at us */
	अगर (!ddp->deh_dnet)	/* Net 0 is 'this network' */
		atअगर = atalk_find_anynet(ddp->deh_dnode, dev);
	अन्यथा
		atअगर = atalk_find_पूर्णांकerface(ddp->deh_dnet, ddp->deh_dnode);

	अगर (!atअगर) अणु
		/* Not ours, so we route the packet via the correct
		 * AppleTalk अगरace
		 */
		वापस atalk_route_packet(skb, dev, ddp, len_hops, origlen);
	पूर्ण

	/* अगर IP over DDP is not selected this code will be optimized out */
	अगर (is_ip_over_ddp(skb))
		वापस handle_ip_over_ddp(skb);
	/*
	 * Which socket - atalk_search_socket() looks क्रम a *full match*
	 * of the <net, node, port> tuple.
	 */
	tosat.sat_addr.s_net  = ddp->deh_dnet;
	tosat.sat_addr.s_node = ddp->deh_dnode;
	tosat.sat_port	      = ddp->deh_dport;

	sock = atalk_search_socket(&tosat, atअगर);
	अगर (!sock) /* But not one of our sockets */
		जाओ drop;

	/* Queue packet (standard) */
	अगर (sock_queue_rcv_skb(sock, skb) < 0)
		जाओ drop;

	वापस NET_RX_SUCCESS;

drop:
	kमुक्त_skb(skb);
out:
	वापस NET_RX_DROP;

पूर्ण

/*
 * Receive a LocalTalk frame. We make some demands on the caller here.
 * Caller must provide enough headroom on the packet to pull the लघु
 * header and append a दीर्घ one.
 */
अटल पूर्णांक ltalk_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ मुक्तit;

	/* Expand any लघु क्रमm frames */
	अगर (skb_mac_header(skb)[2] == 1) अणु
		काष्ठा ddpehdr *ddp;
		/* Find our address */
		काष्ठा atalk_addr *ap = atalk_find_dev_addr(dev);

		अगर (!ap || skb->len < माप(__be16) || skb->len > 1023)
			जाओ मुक्तit;

		/* Don't mangle buffer अगर shared */
		अगर (!(skb = skb_share_check(skb, GFP_ATOMIC)))
			वापस 0;

		/*
		 * The push leaves us with a ddephdr not an shdr, and
		 * handily the port bytes in the right place preset.
		 */
		ddp = skb_push(skb, माप(*ddp) - 4);

		/* Now fill in the दीर्घ header */

		/*
		 * These two first. The mac overlays the new source/dest
		 * network inक्रमmation so we MUST copy these beक्रमe
		 * we ग_लिखो the network numbers !
		 */

		ddp->deh_dnode = skb_mac_header(skb)[0];     /* From physical header */
		ddp->deh_snode = skb_mac_header(skb)[1];     /* From physical header */

		ddp->deh_dnet  = ap->s_net;	/* Network number */
		ddp->deh_snet  = ap->s_net;
		ddp->deh_sum   = 0;		/* No checksum */
		/*
		 * Not sure about this bit...
		 */
		/* Non routable, so क्रमce a drop अगर we slip up later */
		ddp->deh_len_hops = htons(skb->len + (DDP_MAXHOPS << 10));
	पूर्ण
	skb_reset_transport_header(skb);

	वापस atalk_rcv(skb, dev, pt, orig_dev);
मुक्तit:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक atalk_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा atalk_sock *at = at_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_at *, usat, msg->msg_name);
	पूर्णांक flags = msg->msg_flags;
	पूर्णांक loopback = 0;
	काष्ठा sockaddr_at local_satalk, gsat;
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	काष्ठा ddpehdr *ddp;
	पूर्णांक size, hard_header_len;
	काष्ठा atalk_route *rt, *rt_lo = शून्य;
	पूर्णांक err;

	अगर (flags & ~(MSG_DONTWAIT|MSG_CMSG_COMPAT))
		वापस -EINVAL;

	अगर (len > DDP_MAXSZ)
		वापस -EMSGSIZE;

	lock_sock(sk);
	अगर (usat) अणु
		err = -EBUSY;
		अगर (sock_flag(sk, SOCK_ZAPPED))
			अगर (atalk_स्वतःbind(sk) < 0)
				जाओ out;

		err = -EINVAL;
		अगर (msg->msg_namelen < माप(*usat) ||
		    usat->sat_family != AF_APPLETALK)
			जाओ out;

		err = -EPERM;
		/* netatalk didn't implement this check */
		अगर (usat->sat_addr.s_node == ATADDR_BCAST &&
		    !sock_flag(sk, SOCK_BROADCAST)) अणु
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -ENOTCONN;
		अगर (sk->sk_state != TCP_ESTABLISHED)
			जाओ out;
		usat = &local_satalk;
		usat->sat_family      = AF_APPLETALK;
		usat->sat_port	      = at->dest_port;
		usat->sat_addr.s_node = at->dest_node;
		usat->sat_addr.s_net  = at->dest_net;
	पूर्ण

	/* Build a packet */
	SOCK_DEBUG(sk, "SK %p: Got address.\n", sk);

	/* For headers */
	size = माप(काष्ठा ddpehdr) + len + ddp_dl->header_length;

	अगर (usat->sat_addr.s_net || usat->sat_addr.s_node == ATADDR_ANYNODE) अणु
		rt = atrtr_find(&usat->sat_addr);
	पूर्ण अन्यथा अणु
		काष्ठा atalk_addr at_hपूर्णांक;

		at_hपूर्णांक.s_node = 0;
		at_hपूर्णांक.s_net  = at->src_net;

		rt = atrtr_find(&at_hपूर्णांक);
	पूर्ण
	err = -ENETUNREACH;
	अगर (!rt)
		जाओ out;

	dev = rt->dev;

	SOCK_DEBUG(sk, "SK %p: Size needed %d, device %s\n",
			sk, size, dev->name);

	hard_header_len = dev->hard_header_len;
	/* Leave room क्रम loopback hardware header अगर necessary */
	अगर (usat->sat_addr.s_node == ATADDR_BCAST &&
	    (dev->flags & IFF_LOOPBACK || !(rt->flags & RTF_GATEWAY))) अणु
		काष्ठा atalk_addr at_lo;

		at_lo.s_node = 0;
		at_lo.s_net  = 0;

		rt_lo = atrtr_find(&at_lo);

		अगर (rt_lo && rt_lo->dev->hard_header_len > hard_header_len)
			hard_header_len = rt_lo->dev->hard_header_len;
	पूर्ण

	size += hard_header_len;
	release_sock(sk);
	skb = sock_alloc_send_skb(sk, size, (flags & MSG_DONTWAIT), &err);
	lock_sock(sk);
	अगर (!skb)
		जाओ out;

	skb_reserve(skb, ddp_dl->header_length);
	skb_reserve(skb, hard_header_len);
	skb->dev = dev;

	SOCK_DEBUG(sk, "SK %p: Begin build.\n", sk);

	ddp = skb_put(skb, माप(काष्ठा ddpehdr));
	ddp->deh_len_hops  = htons(len + माप(*ddp));
	ddp->deh_dnet  = usat->sat_addr.s_net;
	ddp->deh_snet  = at->src_net;
	ddp->deh_dnode = usat->sat_addr.s_node;
	ddp->deh_snode = at->src_node;
	ddp->deh_dport = usat->sat_port;
	ddp->deh_sport = at->src_port;

	SOCK_DEBUG(sk, "SK %p: Copy user data (%zd bytes).\n", sk, len);

	err = स_नकल_from_msg(skb_put(skb, len), msg, len);
	अगर (err) अणु
		kमुक्त_skb(skb);
		err = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (sk->sk_no_check_tx)
		ddp->deh_sum = 0;
	अन्यथा
		ddp->deh_sum = atalk_checksum(skb, len + माप(*ddp));

	/*
	 * Loopback broadcast packets to non gateway tarमाला_लो (ie routes
	 * to group we are in)
	 */
	अगर (ddp->deh_dnode == ATADDR_BCAST &&
	    !(rt->flags & RTF_GATEWAY) && !(dev->flags & IFF_LOOPBACK)) अणु
		काष्ठा sk_buff *skb2 = skb_copy(skb, GFP_KERNEL);

		अगर (skb2) अणु
			loopback = 1;
			SOCK_DEBUG(sk, "SK %p: send out(copy).\n", sk);
			/*
			 * If it fails it is queued/sent above in the aarp queue
			 */
			aarp_send_ddp(dev, skb2, &usat->sat_addr, शून्य);
		पूर्ण
	पूर्ण

	अगर (dev->flags & IFF_LOOPBACK || loopback) अणु
		SOCK_DEBUG(sk, "SK %p: Loop back.\n", sk);
		/* loop back */
		skb_orphan(skb);
		अगर (ddp->deh_dnode == ATADDR_BCAST) अणु
			अगर (!rt_lo) अणु
				kमुक्त_skb(skb);
				err = -ENETUNREACH;
				जाओ out;
			पूर्ण
			dev = rt_lo->dev;
			skb->dev = dev;
		पूर्ण
		ddp_dl->request(ddp_dl, skb, dev->dev_addr);
	पूर्ण अन्यथा अणु
		SOCK_DEBUG(sk, "SK %p: send out.\n", sk);
		अगर (rt->flags & RTF_GATEWAY) अणु
		    gsat.sat_addr = rt->gateway;
		    usat = &gsat;
		पूर्ण

		/*
		 * If it fails it is queued/sent above in the aarp queue
		 */
		aarp_send_ddp(dev, skb, &usat->sat_addr, शून्य);
	पूर्ण
	SOCK_DEBUG(sk, "SK %p: Done write (%zd).\n", sk, len);

out:
	release_sock(sk);
	वापस err ? : len;
पूर्ण

अटल पूर्णांक atalk_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
			 पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा ddpehdr *ddp;
	पूर्णांक copied = 0;
	पूर्णांक offset = 0;
	पूर्णांक err = 0;
	काष्ठा sk_buff *skb;

	skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
						flags & MSG_DONTWAIT, &err);
	lock_sock(sk);

	अगर (!skb)
		जाओ out;

	/* FIXME: use skb->cb to be able to use shared skbs */
	ddp = ddp_hdr(skb);
	copied = ntohs(ddp->deh_len_hops) & 1023;

	अगर (sk->sk_type != SOCK_RAW) अणु
		offset = माप(*ddp);
		copied -= offset;
	पूर्ण

	अगर (copied > size) अणु
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण
	err = skb_copy_datagram_msg(skb, offset, msg, copied);

	अगर (!err && msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_at *, sat, msg->msg_name);
		sat->sat_family      = AF_APPLETALK;
		sat->sat_port        = ddp->deh_sport;
		sat->sat_addr.s_node = ddp->deh_snode;
		sat->sat_addr.s_net  = ddp->deh_snet;
		msg->msg_namelen     = माप(*sat);
	पूर्ण

	skb_मुक्त_datagram(sk, skb);	/* Free the datagram. */

out:
	release_sock(sk);
	वापस err ? : copied;
पूर्ण


/*
 * AppleTalk ioctl calls.
 */
अटल पूर्णांक atalk_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc = -ENOIOCTLCMD;
	काष्ठा sock *sk = sock->sk;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	/* Protocol layer */
	हाल TIOCOUTQ: अणु
		दीर्घ amount = sk->sk_sndbuf - sk_wmem_alloc_get(sk);

		अगर (amount < 0)
			amount = 0;
		rc = put_user(amount, (पूर्णांक __user *)argp);
		अवरोध;
	पूर्ण
	हाल TIOCINQ: अणु
		/*
		 * These two are safe on a single CPU प्रणाली as only
		 * user tasks fiddle here
		 */
		काष्ठा sk_buff *skb = skb_peek(&sk->sk_receive_queue);
		दीर्घ amount = 0;

		अगर (skb)
			amount = skb->len - माप(काष्ठा ddpehdr);
		rc = put_user(amount, (पूर्णांक __user *)argp);
		अवरोध;
	पूर्ण
	/* Routing */
	हाल SIOCADDRT:
	हाल SIOCDELRT:
		rc = -EPERM;
		अगर (capable(CAP_NET_ADMIN))
			rc = atrtr_ioctl(cmd, argp);
		अवरोध;
	/* Interface */
	हाल SIOCGIFADDR:
	हाल SIOCSIFADDR:
	हाल SIOCGIFBRDADDR:
	हाल SIOCATALKDIFADDR:
	हाल SIOCDIFADDR:
	हाल SIOCSARP:		/* proxy AARP */
	हाल SIOCDARP:		/* proxy AARP */
		rtnl_lock();
		rc = atअगर_ioctl(cmd, argp);
		rtnl_unlock();
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण


#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक atalk_compat_routing_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd,
		काष्ठा compat_rtentry __user *ur)
अणु
	compat_uptr_t rtdev;
	काष्ठा rtentry rt;

	अगर (copy_from_user(&rt.rt_dst, &ur->rt_dst,
			3 * माप(काष्ठा sockaddr)) ||
	    get_user(rt.rt_flags, &ur->rt_flags) ||
	    get_user(rt.rt_metric, &ur->rt_metric) ||
	    get_user(rt.rt_mtu, &ur->rt_mtu) ||
	    get_user(rt.rt_winकरोw, &ur->rt_winकरोw) ||
	    get_user(rt.rt_irtt, &ur->rt_irtt) ||
	    get_user(rtdev, &ur->rt_dev))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल SIOCDELRT:
		अगर (rt.rt_dst.sa_family != AF_APPLETALK)
			वापस -EINVAL;
		वापस atrtr_delete(&((काष्ठा sockaddr_at *)
				      &rt.rt_dst)->sat_addr);

	हाल SIOCADDRT:
		rt.rt_dev = compat_ptr(rtdev);
		वापस atrtr_ioctl_addrt(&rt);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
अटल पूर्णांक atalk_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);
	काष्ठा sock *sk = sock->sk;

	चयन (cmd) अणु
	हाल SIOCADDRT:
	हाल SIOCDELRT:
		वापस atalk_compat_routing_ioctl(sk, cmd, argp);
	/*
	 * SIOCATALKDIFADDR is a SIOCPROTOPRIVATE ioctl number, so we
	 * cannot handle it in common code. The data we access अगर अगरreq
	 * here is compatible, so we can simply call the native
	 * handler.
	 */
	हाल SIOCATALKDIFADDR:
		वापस atalk_ioctl(sock, cmd, (अचिन्हित दीर्घ)argp);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */


अटल स्थिर काष्ठा net_proto_family atalk_family_ops = अणु
	.family		= PF_APPLETALK,
	.create		= atalk_create,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा proto_ops atalk_dgram_ops = अणु
	.family		= PF_APPLETALK,
	.owner		= THIS_MODULE,
	.release	= atalk_release,
	.bind		= atalk_bind,
	.connect	= atalk_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.getname	= atalk_getname,
	.poll		= datagram_poll,
	.ioctl		= atalk_ioctl,
	.gettstamp	= sock_gettstamp,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= atalk_compat_ioctl,
#पूर्ण_अगर
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.sendmsg	= atalk_sendmsg,
	.recvmsg	= atalk_recvmsg,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage,
पूर्ण;

अटल काष्ठा notअगरier_block ddp_notअगरier = अणु
	.notअगरier_call	= ddp_device_event,
पूर्ण;

अटल काष्ठा packet_type ltalk_packet_type __पढ़ो_mostly = अणु
	.type		= cpu_to_be16(ETH_P_LOCALTALK),
	.func		= ltalk_rcv,
पूर्ण;

अटल काष्ठा packet_type ppptalk_packet_type __पढ़ो_mostly = अणु
	.type		= cpu_to_be16(ETH_P_PPPTALK),
	.func		= atalk_rcv,
पूर्ण;

अटल अचिन्हित अक्षर ddp_snap_id[] = अणु 0x08, 0x00, 0x07, 0x80, 0x9B पूर्ण;

/* Export symbols क्रम use by drivers when AppleTalk is a module */
EXPORT_SYMBOL(atrtr_get_dev);
EXPORT_SYMBOL(atalk_find_dev_addr);

/* Called by proto.c on kernel start up */
अटल पूर्णांक __init atalk_init(व्योम)
अणु
	पूर्णांक rc;

	rc = proto_रेजिस्टर(&ddp_proto, 0);
	अगर (rc)
		जाओ out;

	rc = sock_रेजिस्टर(&atalk_family_ops);
	अगर (rc)
		जाओ out_proto;

	ddp_dl = रेजिस्टर_snap_client(ddp_snap_id, atalk_rcv);
	अगर (!ddp_dl) अणु
		pr_crit("Unable to register DDP with SNAP.\n");
		rc = -ENOMEM;
		जाओ out_sock;
	पूर्ण

	dev_add_pack(&ltalk_packet_type);
	dev_add_pack(&ppptalk_packet_type);

	rc = रेजिस्टर_netdevice_notअगरier(&ddp_notअगरier);
	अगर (rc)
		जाओ out_snap;

	rc = aarp_proto_init();
	अगर (rc)
		जाओ out_dev;

	rc = atalk_proc_init();
	अगर (rc)
		जाओ out_aarp;

	rc = atalk_रेजिस्टर_sysctl();
	अगर (rc)
		जाओ out_proc;
out:
	वापस rc;
out_proc:
	atalk_proc_निकास();
out_aarp:
	aarp_cleanup_module();
out_dev:
	unरेजिस्टर_netdevice_notअगरier(&ddp_notअगरier);
out_snap:
	dev_हटाओ_pack(&ppptalk_packet_type);
	dev_हटाओ_pack(&ltalk_packet_type);
	unरेजिस्टर_snap_client(ddp_dl);
out_sock:
	sock_unरेजिस्टर(PF_APPLETALK);
out_proto:
	proto_unरेजिस्टर(&ddp_proto);
	जाओ out;
पूर्ण
module_init(atalk_init);

/*
 * No explicit module reference count manipulation is needed in the
 * protocol. Socket layer sets module reference count क्रम us
 * and पूर्णांकerfaces reference counting is करोne
 * by the network device layer.
 *
 * Ergo, beक्रमe the AppleTalk module can be हटाओd, all AppleTalk
 * sockets be बंदd from user space.
 */
अटल व्योम __निकास atalk_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_SYSCTL
	atalk_unरेजिस्टर_sysctl();
#पूर्ण_अगर /* CONFIG_SYSCTL */
	atalk_proc_निकास();
	aarp_cleanup_module();	/* General aarp clean-up. */
	unरेजिस्टर_netdevice_notअगरier(&ddp_notअगरier);
	dev_हटाओ_pack(&ltalk_packet_type);
	dev_हटाओ_pack(&ppptalk_packet_type);
	unरेजिस्टर_snap_client(ddp_dl);
	sock_unरेजिस्टर(PF_APPLETALK);
	proto_unरेजिस्टर(&ddp_proto);
पूर्ण
module_निकास(atalk_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan Cox <alan@lxorguk.ukuu.org.uk>");
MODULE_DESCRIPTION("AppleTalk 0.20\n");
MODULE_ALIAS_NETPROTO(PF_APPLETALK);

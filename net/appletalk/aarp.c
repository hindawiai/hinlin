<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	AARP:		An implementation of the AppleTalk AARP protocol क्रम
 *			Ethernet 'ELAP'.
 *
 *		Alan Cox  <Alan.Cox@linux.org>
 *
 *	This करोesn't fit cleanly with the IP arp. Potentially we can use
 *	the generic neighbour discovery code to clean this up.
 *
 *	FIXME:
 *		We ought to handle the retransmits with a single list and a
 *	separate fast समयr क्रम when it is needed.
 *		Use neighbour discovery code.
 *		Token Ring Support.
 *
 *	References:
 *		Inside AppleTalk (2nd Ed).
 *	Fixes:
 *		Jaume Grau	-	flush caches on AARP_PROBE
 *		Rob Newberry	-	Added proxy AARP and AARP proc fs,
 *					moved probing from DDP module.
 *		Arnalकरो C. Melo -	करोn't mangle rx packets
 */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/datalink.h>
#समावेश <net/psnap.h>
#समावेश <linux/atalk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>
#समावेश <linux/etherdevice.h>

पूर्णांक sysctl_aarp_expiry_समय = AARP_EXPIRY_TIME;
पूर्णांक sysctl_aarp_tick_समय = AARP_TICK_TIME;
पूर्णांक sysctl_aarp_retransmit_limit = AARP_RETRANSMIT_LIMIT;
पूर्णांक sysctl_aarp_resolve_समय = AARP_RESOLVE_TIME;

/* Lists of aarp entries */
/**
 *	काष्ठा aarp_entry - AARP entry
 *	@last_sent: Last समय we xmitted the aarp request
 *	@packet_queue: Queue of frames रुको क्रम resolution
 *	@status: Used क्रम proxy AARP
 *	@expires_at: Entry expiry समय
 *	@target_addr: DDP Address
 *	@dev:  Device to use
 *	@hwaddr:  Physical i/f address of target/router
 *	@xmit_count:  When this hits 10 we give up
 *	@next: Next entry in chain
 */
काष्ठा aarp_entry अणु
	/* These first two are only used क्रम unresolved entries */
	अचिन्हित दीर्घ		last_sent;
	काष्ठा sk_buff_head	packet_queue;
	पूर्णांक			status;
	अचिन्हित दीर्घ		expires_at;
	काष्ठा atalk_addr	target_addr;
	काष्ठा net_device	*dev;
	अक्षर			hwaddr[ETH_ALEN];
	अचिन्हित लघु		xmit_count;
	काष्ठा aarp_entry	*next;
पूर्ण;

/* Hashed list of resolved, unresolved and proxy entries */
अटल काष्ठा aarp_entry *resolved[AARP_HASH_SIZE];
अटल काष्ठा aarp_entry *unresolved[AARP_HASH_SIZE];
अटल काष्ठा aarp_entry *proxies[AARP_HASH_SIZE];
अटल पूर्णांक unresolved_count;

/* One lock protects it all. */
अटल DEFINE_RWLOCK(aarp_lock);

/* Used to walk the list and purge/kick entries.  */
अटल काष्ठा समयr_list aarp_समयr;

/*
 *	Delete an aarp queue
 *
 *	Must run under aarp_lock.
 */
अटल व्योम __aarp_expire(काष्ठा aarp_entry *a)
अणु
	skb_queue_purge(&a->packet_queue);
	kमुक्त(a);
पूर्ण

/*
 *	Send an aarp queue entry request
 *
 *	Must run under aarp_lock.
 */
अटल व्योम __aarp_send_query(काष्ठा aarp_entry *a)
अणु
	अटल अचिन्हित अक्षर aarp_eth_multicast[ETH_ALEN] =
					अणु 0x09, 0x00, 0x07, 0xFF, 0xFF, 0xFF पूर्ण;
	काष्ठा net_device *dev = a->dev;
	काष्ठा elapaarp *eah;
	पूर्णांक len = dev->hard_header_len + माप(*eah) + aarp_dl->header_length;
	काष्ठा sk_buff *skb = alloc_skb(len, GFP_ATOMIC);
	काष्ठा atalk_addr *sat = atalk_find_dev_addr(dev);

	अगर (!skb)
		वापस;

	अगर (!sat) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* Set up the buffer */
	skb_reserve(skb, dev->hard_header_len + aarp_dl->header_length);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb_put(skb, माप(*eah));
	skb->protocol    = htons(ETH_P_ATALK);
	skb->dev	 = dev;
	eah		 = aarp_hdr(skb);

	/* Set up the ARP */
	eah->hw_type	 = htons(AARP_HW_TYPE_ETHERNET);
	eah->pa_type	 = htons(ETH_P_ATALK);
	eah->hw_len	 = ETH_ALEN;
	eah->pa_len	 = AARP_PA_ALEN;
	eah->function	 = htons(AARP_REQUEST);

	ether_addr_copy(eah->hw_src, dev->dev_addr);

	eah->pa_src_zero = 0;
	eah->pa_src_net	 = sat->s_net;
	eah->pa_src_node = sat->s_node;

	eth_zero_addr(eah->hw_dst);

	eah->pa_dst_zero = 0;
	eah->pa_dst_net	 = a->target_addr.s_net;
	eah->pa_dst_node = a->target_addr.s_node;

	/* Send it */
	aarp_dl->request(aarp_dl, skb, aarp_eth_multicast);
	/* Update the sending count */
	a->xmit_count++;
	a->last_sent = jअगरfies;
पूर्ण

/* This runs under aarp_lock and in softपूर्णांक context, so only atomic memory
 * allocations can be used. */
अटल व्योम aarp_send_reply(काष्ठा net_device *dev, काष्ठा atalk_addr *us,
			    काष्ठा atalk_addr *them, अचिन्हित अक्षर *sha)
अणु
	काष्ठा elapaarp *eah;
	पूर्णांक len = dev->hard_header_len + माप(*eah) + aarp_dl->header_length;
	काष्ठा sk_buff *skb = alloc_skb(len, GFP_ATOMIC);

	अगर (!skb)
		वापस;

	/* Set up the buffer */
	skb_reserve(skb, dev->hard_header_len + aarp_dl->header_length);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb_put(skb, माप(*eah));
	skb->protocol    = htons(ETH_P_ATALK);
	skb->dev	 = dev;
	eah		 = aarp_hdr(skb);

	/* Set up the ARP */
	eah->hw_type	 = htons(AARP_HW_TYPE_ETHERNET);
	eah->pa_type	 = htons(ETH_P_ATALK);
	eah->hw_len	 = ETH_ALEN;
	eah->pa_len	 = AARP_PA_ALEN;
	eah->function	 = htons(AARP_REPLY);

	ether_addr_copy(eah->hw_src, dev->dev_addr);

	eah->pa_src_zero = 0;
	eah->pa_src_net	 = us->s_net;
	eah->pa_src_node = us->s_node;

	अगर (!sha)
		eth_zero_addr(eah->hw_dst);
	अन्यथा
		ether_addr_copy(eah->hw_dst, sha);

	eah->pa_dst_zero = 0;
	eah->pa_dst_net	 = them->s_net;
	eah->pa_dst_node = them->s_node;

	/* Send it */
	aarp_dl->request(aarp_dl, skb, sha);
पूर्ण

/*
 *	Send probe frames. Called from aarp_probe_network and
 *	aarp_proxy_probe_network.
 */

अटल व्योम aarp_send_probe(काष्ठा net_device *dev, काष्ठा atalk_addr *us)
अणु
	काष्ठा elapaarp *eah;
	पूर्णांक len = dev->hard_header_len + माप(*eah) + aarp_dl->header_length;
	काष्ठा sk_buff *skb = alloc_skb(len, GFP_ATOMIC);
	अटल अचिन्हित अक्षर aarp_eth_multicast[ETH_ALEN] =
					अणु 0x09, 0x00, 0x07, 0xFF, 0xFF, 0xFF पूर्ण;

	अगर (!skb)
		वापस;

	/* Set up the buffer */
	skb_reserve(skb, dev->hard_header_len + aarp_dl->header_length);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb_put(skb, माप(*eah));
	skb->protocol    = htons(ETH_P_ATALK);
	skb->dev	 = dev;
	eah		 = aarp_hdr(skb);

	/* Set up the ARP */
	eah->hw_type	 = htons(AARP_HW_TYPE_ETHERNET);
	eah->pa_type	 = htons(ETH_P_ATALK);
	eah->hw_len	 = ETH_ALEN;
	eah->pa_len	 = AARP_PA_ALEN;
	eah->function	 = htons(AARP_PROBE);

	ether_addr_copy(eah->hw_src, dev->dev_addr);

	eah->pa_src_zero = 0;
	eah->pa_src_net	 = us->s_net;
	eah->pa_src_node = us->s_node;

	eth_zero_addr(eah->hw_dst);

	eah->pa_dst_zero = 0;
	eah->pa_dst_net	 = us->s_net;
	eah->pa_dst_node = us->s_node;

	/* Send it */
	aarp_dl->request(aarp_dl, skb, aarp_eth_multicast);
पूर्ण

/*
 *	Handle an aarp समयr expire
 *
 *	Must run under the aarp_lock.
 */

अटल व्योम __aarp_expire_समयr(काष्ठा aarp_entry **n)
अणु
	काष्ठा aarp_entry *t;

	जबतक (*n)
		/* Expired ? */
		अगर (समय_after(jअगरfies, (*n)->expires_at)) अणु
			t = *n;
			*n = (*n)->next;
			__aarp_expire(t);
		पूर्ण अन्यथा
			n = &((*n)->next);
पूर्ण

/*
 *	Kick all pending requests 5 बार a second.
 *
 *	Must run under the aarp_lock.
 */
अटल व्योम __aarp_kick(काष्ठा aarp_entry **n)
अणु
	काष्ठा aarp_entry *t;

	जबतक (*n)
		/* Expired: अगर this will be the 11th tx, we delete instead. */
		अगर ((*n)->xmit_count >= sysctl_aarp_retransmit_limit) अणु
			t = *n;
			*n = (*n)->next;
			__aarp_expire(t);
		पूर्ण अन्यथा अणु
			__aarp_send_query(*n);
			n = &((*n)->next);
		पूर्ण
पूर्ण

/*
 *	A device has gone करोwn. Take all entries referring to the device
 *	and हटाओ them.
 *
 *	Must run under the aarp_lock.
 */
अटल व्योम __aarp_expire_device(काष्ठा aarp_entry **n, काष्ठा net_device *dev)
अणु
	काष्ठा aarp_entry *t;

	जबतक (*n)
		अगर ((*n)->dev == dev) अणु
			t = *n;
			*n = (*n)->next;
			__aarp_expire(t);
		पूर्ण अन्यथा
			n = &((*n)->next);
पूर्ण

/* Handle the समयr event */
अटल व्योम aarp_expire_समयout(काष्ठा समयr_list *unused)
अणु
	पूर्णांक ct;

	ग_लिखो_lock_bh(&aarp_lock);

	क्रम (ct = 0; ct < AARP_HASH_SIZE; ct++) अणु
		__aarp_expire_समयr(&resolved[ct]);
		__aarp_kick(&unresolved[ct]);
		__aarp_expire_समयr(&unresolved[ct]);
		__aarp_expire_समयr(&proxies[ct]);
	पूर्ण

	ग_लिखो_unlock_bh(&aarp_lock);
	mod_समयr(&aarp_समयr, jअगरfies +
			       (unresolved_count ? sysctl_aarp_tick_समय :
				sysctl_aarp_expiry_समय));
पूर्ण

/* Network device notअगरier chain handler. */
अटल पूर्णांक aarp_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	पूर्णांक ct;

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_DOWN) अणु
		ग_लिखो_lock_bh(&aarp_lock);

		क्रम (ct = 0; ct < AARP_HASH_SIZE; ct++) अणु
			__aarp_expire_device(&resolved[ct], dev);
			__aarp_expire_device(&unresolved[ct], dev);
			__aarp_expire_device(&proxies[ct], dev);
		पूर्ण

		ग_लिखो_unlock_bh(&aarp_lock);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/* Expire all entries in a hash chain */
अटल व्योम __aarp_expire_all(काष्ठा aarp_entry **n)
अणु
	काष्ठा aarp_entry *t;

	जबतक (*n) अणु
		t = *n;
		*n = (*n)->next;
		__aarp_expire(t);
	पूर्ण
पूर्ण

/* Cleanup all hash chains -- module unloading */
अटल व्योम aarp_purge(व्योम)
अणु
	पूर्णांक ct;

	ग_लिखो_lock_bh(&aarp_lock);
	क्रम (ct = 0; ct < AARP_HASH_SIZE; ct++) अणु
		__aarp_expire_all(&resolved[ct]);
		__aarp_expire_all(&unresolved[ct]);
		__aarp_expire_all(&proxies[ct]);
	पूर्ण
	ग_लिखो_unlock_bh(&aarp_lock);
पूर्ण

/*
 *	Create a new aarp entry.  This must use GFP_ATOMIC because it
 *	runs जबतक holding spinlocks.
 */
अटल काष्ठा aarp_entry *aarp_alloc(व्योम)
अणु
	काष्ठा aarp_entry *a = kदो_स्मृति(माप(*a), GFP_ATOMIC);

	अगर (a)
		skb_queue_head_init(&a->packet_queue);
	वापस a;
पूर्ण

/*
 * Find an entry. We might वापस an expired but not yet purged entry. We
 * करोn't care as it will करो no harm.
 *
 * This must run under the aarp_lock.
 */
अटल काष्ठा aarp_entry *__aarp_find_entry(काष्ठा aarp_entry *list,
					    काष्ठा net_device *dev,
					    काष्ठा atalk_addr *sat)
अणु
	जबतक (list) अणु
		अगर (list->target_addr.s_net == sat->s_net &&
		    list->target_addr.s_node == sat->s_node &&
		    list->dev == dev)
			अवरोध;
		list = list->next;
	पूर्ण

	वापस list;
पूर्ण

/* Called from the DDP code, and thus must be exported. */
व्योम aarp_proxy_हटाओ(काष्ठा net_device *dev, काष्ठा atalk_addr *sa)
अणु
	पूर्णांक hash = sa->s_node % (AARP_HASH_SIZE - 1);
	काष्ठा aarp_entry *a;

	ग_लिखो_lock_bh(&aarp_lock);

	a = __aarp_find_entry(proxies[hash], dev, sa);
	अगर (a)
		a->expires_at = jअगरfies - 1;

	ग_लिखो_unlock_bh(&aarp_lock);
पूर्ण

/* This must run under aarp_lock. */
अटल काष्ठा atalk_addr *__aarp_proxy_find(काष्ठा net_device *dev,
					    काष्ठा atalk_addr *sa)
अणु
	पूर्णांक hash = sa->s_node % (AARP_HASH_SIZE - 1);
	काष्ठा aarp_entry *a = __aarp_find_entry(proxies[hash], dev, sa);

	वापस a ? sa : शून्य;
पूर्ण

/*
 * Probe a Phase 1 device or a device that requires its Net:Node to
 * be set via an ioctl.
 */
अटल व्योम aarp_send_probe_phase1(काष्ठा atalk_अगरace *अगरace)
अणु
	काष्ठा अगरreq atreq;
	काष्ठा sockaddr_at *sa = (काष्ठा sockaddr_at *)&atreq.अगरr_addr;
	स्थिर काष्ठा net_device_ops *ops = अगरace->dev->netdev_ops;

	sa->sat_addr.s_node = अगरace->address.s_node;
	sa->sat_addr.s_net = ntohs(अगरace->address.s_net);

	/* We pass the Net:Node to the drivers/cards by a Device ioctl. */
	अगर (!(ops->nकरो_करो_ioctl(अगरace->dev, &atreq, SIOCSIFADDR))) अणु
		ops->nकरो_करो_ioctl(अगरace->dev, &atreq, SIOCGIFADDR);
		अगर (अगरace->address.s_net != htons(sa->sat_addr.s_net) ||
		    अगरace->address.s_node != sa->sat_addr.s_node)
			अगरace->status |= ATIF_PROBE_FAIL;

		अगरace->address.s_net  = htons(sa->sat_addr.s_net);
		अगरace->address.s_node = sa->sat_addr.s_node;
	पूर्ण
पूर्ण


व्योम aarp_probe_network(काष्ठा atalk_अगरace *atअगर)
अणु
	अगर (atअगर->dev->type == ARPHRD_LOCALTLK ||
	    atअगर->dev->type == ARPHRD_PPP)
		aarp_send_probe_phase1(atअगर);
	अन्यथा अणु
		अचिन्हित पूर्णांक count;

		क्रम (count = 0; count < AARP_RETRANSMIT_LIMIT; count++) अणु
			aarp_send_probe(atअगर->dev, &atअगर->address);

			/* Defer 1/10th */
			msleep(100);

			अगर (atअगर->status & ATIF_PROBE_FAIL)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक aarp_proxy_probe_network(काष्ठा atalk_अगरace *atअगर, काष्ठा atalk_addr *sa)
अणु
	पूर्णांक hash, retval = -EPROTONOSUPPORT;
	काष्ठा aarp_entry *entry;
	अचिन्हित पूर्णांक count;

	/*
	 * we करोn't currently support LocalTalk or PPP क्रम proxy AARP;
	 * अगर someone wants to try and add it, have fun
	 */
	अगर (atअगर->dev->type == ARPHRD_LOCALTLK ||
	    atअगर->dev->type == ARPHRD_PPP)
		जाओ out;

	/*
	 * create a new AARP entry with the flags set to be published --
	 * we need this one to hang around even अगर it's in use
	 */
	entry = aarp_alloc();
	retval = -ENOMEM;
	अगर (!entry)
		जाओ out;

	entry->expires_at = -1;
	entry->status = ATIF_PROBE;
	entry->target_addr.s_node = sa->s_node;
	entry->target_addr.s_net = sa->s_net;
	entry->dev = atअगर->dev;

	ग_लिखो_lock_bh(&aarp_lock);

	hash = sa->s_node % (AARP_HASH_SIZE - 1);
	entry->next = proxies[hash];
	proxies[hash] = entry;

	क्रम (count = 0; count < AARP_RETRANSMIT_LIMIT; count++) अणु
		aarp_send_probe(atअगर->dev, sa);

		/* Defer 1/10th */
		ग_लिखो_unlock_bh(&aarp_lock);
		msleep(100);
		ग_लिखो_lock_bh(&aarp_lock);

		अगर (entry->status & ATIF_PROBE_FAIL)
			अवरोध;
	पूर्ण

	अगर (entry->status & ATIF_PROBE_FAIL) अणु
		entry->expires_at = jअगरfies - 1; /* मुक्त the entry */
		retval = -EADDRINUSE; /* वापस network full */
	पूर्ण अन्यथा अणु /* clear the probing flag */
		entry->status &= ~ATIF_PROBE;
		retval = 1;
	पूर्ण

	ग_लिखो_unlock_bh(&aarp_lock);
out:
	वापस retval;
पूर्ण

/* Send a DDP frame */
पूर्णांक aarp_send_ddp(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		  काष्ठा atalk_addr *sa, व्योम *hwaddr)
अणु
	अटल अक्षर ddp_eth_multicast[ETH_ALEN] =
		अणु 0x09, 0x00, 0x07, 0xFF, 0xFF, 0xFF पूर्ण;
	पूर्णांक hash;
	काष्ठा aarp_entry *a;

	skb_reset_network_header(skb);

	/* Check क्रम LocalTalk first */
	अगर (dev->type == ARPHRD_LOCALTLK) अणु
		काष्ठा atalk_addr *at = atalk_find_dev_addr(dev);
		काष्ठा ddpehdr *ddp = (काष्ठा ddpehdr *)skb->data;
		पूर्णांक ft = 2;

		/*
		 * Compressible ?
		 *
		 * IFF: src_net == dest_net == device_net
		 * (zero matches anything)
		 */

		अगर ((!ddp->deh_snet || at->s_net == ddp->deh_snet) &&
		    (!ddp->deh_dnet || at->s_net == ddp->deh_dnet)) अणु
			skb_pull(skb, माप(*ddp) - 4);

			/*
			 *	The upper two reमुख्यing bytes are the port
			 *	numbers	we just happen to need. Now put the
			 *	length in the lower two.
			 */
			*((__be16 *)skb->data) = htons(skb->len);
			ft = 1;
		पूर्ण
		/*
		 * Nice and easy. No AARP type protocols occur here so we can
		 * just shovel it out with a 3 byte LLAP header
		 */

		skb_push(skb, 3);
		skb->data[0] = sa->s_node;
		skb->data[1] = at->s_node;
		skb->data[2] = ft;
		skb->dev     = dev;
		जाओ sendit;
	पूर्ण

	/* On a PPP link we neither compress nor aarp.  */
	अगर (dev->type == ARPHRD_PPP) अणु
		skb->protocol = htons(ETH_P_PPPTALK);
		skb->dev = dev;
		जाओ sendit;
	पूर्ण

	/* Non ELAP we cannot करो. */
	अगर (dev->type != ARPHRD_ETHER)
		जाओ मुक्त_it;

	skb->dev = dev;
	skb->protocol = htons(ETH_P_ATALK);
	hash = sa->s_node % (AARP_HASH_SIZE - 1);

	/* Do we have a resolved entry? */
	अगर (sa->s_node == ATADDR_BCAST) अणु
		/* Send it */
		ddp_dl->request(ddp_dl, skb, ddp_eth_multicast);
		जाओ sent;
	पूर्ण

	ग_लिखो_lock_bh(&aarp_lock);
	a = __aarp_find_entry(resolved[hash], dev, sa);

	अगर (a) अणु /* Return 1 and fill in the address */
		a->expires_at = jअगरfies + (sysctl_aarp_expiry_समय * 10);
		ddp_dl->request(ddp_dl, skb, a->hwaddr);
		ग_लिखो_unlock_bh(&aarp_lock);
		जाओ sent;
	पूर्ण

	/* Do we have an unresolved entry: This is the less common path */
	a = __aarp_find_entry(unresolved[hash], dev, sa);
	अगर (a) अणु /* Queue onto the unresolved queue */
		skb_queue_tail(&a->packet_queue, skb);
		जाओ out_unlock;
	पूर्ण

	/* Allocate a new entry */
	a = aarp_alloc();
	अगर (!a) अणु
		/* Whoops slipped... good job it's an unreliable protocol 8) */
		ग_लिखो_unlock_bh(&aarp_lock);
		जाओ मुक्त_it;
	पूर्ण

	/* Set up the queue */
	skb_queue_tail(&a->packet_queue, skb);
	a->expires_at	 = jअगरfies + sysctl_aarp_resolve_समय;
	a->dev		 = dev;
	a->next		 = unresolved[hash];
	a->target_addr	 = *sa;
	a->xmit_count	 = 0;
	unresolved[hash] = a;
	unresolved_count++;

	/* Send an initial request क्रम the address */
	__aarp_send_query(a);

	/*
	 * Switch to fast समयr अगर needed (That is अगर this is the first
	 * unresolved entry to get added)
	 */

	अगर (unresolved_count == 1)
		mod_समयr(&aarp_समयr, jअगरfies + sysctl_aarp_tick_समय);

	/* Now finally, it is safe to drop the lock. */
out_unlock:
	ग_लिखो_unlock_bh(&aarp_lock);

	/* Tell the ddp layer we have taken over क्रम this frame. */
	जाओ sent;

sendit:
	अगर (skb->sk)
		skb->priority = skb->sk->sk_priority;
	अगर (dev_queue_xmit(skb))
		जाओ drop;
sent:
	वापस NET_XMIT_SUCCESS;
मुक्त_it:
	kमुक्त_skb(skb);
drop:
	वापस NET_XMIT_DROP;
पूर्ण
EXPORT_SYMBOL(aarp_send_ddp);

/*
 *	An entry in the aarp unresolved queue has become resolved. Send
 *	all the frames queued under it.
 *
 *	Must run under aarp_lock.
 */
अटल व्योम __aarp_resolved(काष्ठा aarp_entry **list, काष्ठा aarp_entry *a,
			    पूर्णांक hash)
अणु
	काष्ठा sk_buff *skb;

	जबतक (*list)
		अगर (*list == a) अणु
			unresolved_count--;
			*list = a->next;

			/* Move पूर्णांकo the resolved list */
			a->next = resolved[hash];
			resolved[hash] = a;

			/* Kick frames off */
			जबतक ((skb = skb_dequeue(&a->packet_queue)) != शून्य) अणु
				a->expires_at = jअगरfies +
						sysctl_aarp_expiry_समय * 10;
				ddp_dl->request(ddp_dl, skb, a->hwaddr);
			पूर्ण
		पूर्ण अन्यथा
			list = &((*list)->next);
पूर्ण

/*
 *	This is called by the SNAP driver whenever we see an AARP SNAP
 *	frame. We currently only support Ethernet.
 */
अटल पूर्णांक aarp_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		    काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा elapaarp *ea = aarp_hdr(skb);
	पूर्णांक hash, ret = 0;
	__u16 function;
	काष्ठा aarp_entry *a;
	काष्ठा atalk_addr sa, *ma, da;
	काष्ठा atalk_अगरace *अगरa;

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ out0;

	/* We only करो Ethernet SNAP AARP. */
	अगर (dev->type != ARPHRD_ETHER)
		जाओ out0;

	/* Frame size ok? */
	अगर (!skb_pull(skb, माप(*ea)))
		जाओ out0;

	function = ntohs(ea->function);

	/* Sanity check fields. */
	अगर (function < AARP_REQUEST || function > AARP_PROBE ||
	    ea->hw_len != ETH_ALEN || ea->pa_len != AARP_PA_ALEN ||
	    ea->pa_src_zero || ea->pa_dst_zero)
		जाओ out0;

	/* Looks good. */
	hash = ea->pa_src_node % (AARP_HASH_SIZE - 1);

	/* Build an address. */
	sa.s_node = ea->pa_src_node;
	sa.s_net = ea->pa_src_net;

	/* Process the packet. Check क्रम replies of me. */
	अगरa = atalk_find_dev(dev);
	अगर (!अगरa)
		जाओ out1;

	अगर (अगरa->status & ATIF_PROBE &&
	    अगरa->address.s_node == ea->pa_dst_node &&
	    अगरa->address.s_net == ea->pa_dst_net) अणु
		अगरa->status |= ATIF_PROBE_FAIL; /* Fail the probe (in use) */
		जाओ out1;
	पूर्ण

	/* Check क्रम replies of proxy AARP entries */
	da.s_node = ea->pa_dst_node;
	da.s_net  = ea->pa_dst_net;

	ग_लिखो_lock_bh(&aarp_lock);
	a = __aarp_find_entry(proxies[hash], dev, &da);

	अगर (a && a->status & ATIF_PROBE) अणु
		a->status |= ATIF_PROBE_FAIL;
		/*
		 * we करो not respond to probe or request packets of
		 * this address जबतक we are probing this address
		 */
		जाओ unlock;
	पूर्ण

	चयन (function) अणु
	हाल AARP_REPLY:
		अगर (!unresolved_count)	/* Speed up */
			अवरोध;

		/* Find the entry.  */
		a = __aarp_find_entry(unresolved[hash], dev, &sa);
		अगर (!a || dev != a->dev)
			अवरोध;

		/* We can fill one in - this is good. */
		ether_addr_copy(a->hwaddr, ea->hw_src);
		__aarp_resolved(&unresolved[hash], a, hash);
		अगर (!unresolved_count)
			mod_समयr(&aarp_समयr,
				  jअगरfies + sysctl_aarp_expiry_समय);
		अवरोध;

	हाल AARP_REQUEST:
	हाल AARP_PROBE:

		/*
		 * If it is my address set ma to my address and reply.
		 * We can treat probe and request the same.  Probe
		 * simply means we shouldn't cache the querying host,
		 * as in a probe they are proposing an address not
		 * using one.
		 *
		 * Support क्रम proxy-AARP added. We check अगर the
		 * address is one of our proxies beक्रमe we toss the
		 * packet out.
		 */

		sa.s_node = ea->pa_dst_node;
		sa.s_net  = ea->pa_dst_net;

		/* See अगर we have a matching proxy. */
		ma = __aarp_proxy_find(dev, &sa);
		अगर (!ma)
			ma = &अगरa->address;
		अन्यथा अणु /* We need to make a copy of the entry. */
			da.s_node = sa.s_node;
			da.s_net = sa.s_net;
			ma = &da;
		पूर्ण

		अगर (function == AARP_PROBE) अणु
			/*
			 * A probe implies someone trying to get an
			 * address. So as a precaution flush any
			 * entries we have क्रम this address.
			 */
			a = __aarp_find_entry(resolved[sa.s_node %
						       (AARP_HASH_SIZE - 1)],
					      skb->dev, &sa);

			/*
			 * Make it expire next tick - that aव्योमs us
			 * getting पूर्णांकo a probe/flush/learn/probe/
			 * flush/learn cycle during probing of a slow
			 * to respond host addr.
			 */
			अगर (a) अणु
				a->expires_at = jअगरfies - 1;
				mod_समयr(&aarp_समयr, jअगरfies +
					  sysctl_aarp_tick_समय);
			पूर्ण
		पूर्ण

		अगर (sa.s_node != ma->s_node)
			अवरोध;

		अगर (sa.s_net && ma->s_net && sa.s_net != ma->s_net)
			अवरोध;

		sa.s_node = ea->pa_src_node;
		sa.s_net = ea->pa_src_net;

		/* aarp_my_address has found the address to use क्रम us.
		 */
		aarp_send_reply(dev, ma, &sa, ea->hw_src);
		अवरोध;
	पूर्ण

unlock:
	ग_लिखो_unlock_bh(&aarp_lock);
out1:
	ret = 1;
out0:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block aarp_notअगरier = अणु
	.notअगरier_call = aarp_device_event,
पूर्ण;

अटल अचिन्हित अक्षर aarp_snap_id[] = अणु 0x00, 0x00, 0x00, 0x80, 0xF3 पूर्ण;

पूर्णांक __init aarp_proto_init(व्योम)
अणु
	पूर्णांक rc;

	aarp_dl = रेजिस्टर_snap_client(aarp_snap_id, aarp_rcv);
	अगर (!aarp_dl) अणु
		prपूर्णांकk(KERN_CRIT "Unable to register AARP with SNAP.\n");
		वापस -ENOMEM;
	पूर्ण
	समयr_setup(&aarp_समयr, aarp_expire_समयout, 0);
	aarp_समयr.expires  = jअगरfies + sysctl_aarp_expiry_समय;
	add_समयr(&aarp_समयr);
	rc = रेजिस्टर_netdevice_notअगरier(&aarp_notअगरier);
	अगर (rc) अणु
		del_समयr_sync(&aarp_समयr);
		unरेजिस्टर_snap_client(aarp_dl);
	पूर्ण
	वापस rc;
पूर्ण

/* Remove the AARP entries associated with a device. */
व्योम aarp_device_करोwn(काष्ठा net_device *dev)
अणु
	पूर्णांक ct;

	ग_लिखो_lock_bh(&aarp_lock);

	क्रम (ct = 0; ct < AARP_HASH_SIZE; ct++) अणु
		__aarp_expire_device(&resolved[ct], dev);
		__aarp_expire_device(&unresolved[ct], dev);
		__aarp_expire_device(&proxies[ct], dev);
	पूर्ण

	ग_लिखो_unlock_bh(&aarp_lock);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/*
 * Get the aarp entry that is in the chain described
 * by the iterator.
 * If pos is set then skip till that index.
 * pos = 1 is the first entry
 */
अटल काष्ठा aarp_entry *iter_next(काष्ठा aarp_iter_state *iter, loff_t *pos)
अणु
	पूर्णांक ct = iter->bucket;
	काष्ठा aarp_entry **table = iter->table;
	loff_t off = 0;
	काष्ठा aarp_entry *entry;

 rescan:
	जबतक (ct < AARP_HASH_SIZE) अणु
		क्रम (entry = table[ct]; entry; entry = entry->next) अणु
			अगर (!pos || ++off == *pos) अणु
				iter->table = table;
				iter->bucket = ct;
				वापस entry;
			पूर्ण
		पूर्ण
		++ct;
	पूर्ण

	अगर (table == resolved) अणु
		ct = 0;
		table = unresolved;
		जाओ rescan;
	पूर्ण
	अगर (table == unresolved) अणु
		ct = 0;
		table = proxies;
		जाओ rescan;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *aarp_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(aarp_lock)
अणु
	काष्ठा aarp_iter_state *iter = seq->निजी;

	पढ़ो_lock_bh(&aarp_lock);
	iter->table     = resolved;
	iter->bucket    = 0;

	वापस *pos ? iter_next(iter, pos) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *aarp_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा aarp_entry *entry = v;
	काष्ठा aarp_iter_state *iter = seq->निजी;

	++*pos;

	/* first line after header */
	अगर (v == SEQ_START_TOKEN)
		entry = iter_next(iter, शून्य);

	/* next entry in current bucket */
	अन्यथा अगर (entry->next)
		entry = entry->next;

	/* next bucket or table */
	अन्यथा अणु
		++iter->bucket;
		entry = iter_next(iter, शून्य);
	पूर्ण
	वापस entry;
पूर्ण

अटल व्योम aarp_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(aarp_lock)
अणु
	पढ़ो_unlock_bh(&aarp_lock);
पूर्ण

अटल स्थिर अक्षर *dt2str(अचिन्हित दीर्घ ticks)
अणु
	अटल अक्षर buf[32];

	प्र_लिखो(buf, "%ld.%02ld", ticks / HZ, ((ticks % HZ) * 100) / HZ);

	वापस buf;
पूर्ण

अटल पूर्णांक aarp_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aarp_iter_state *iter = seq->निजी;
	काष्ठा aarp_entry *entry = v;
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
			 "Address  Interface   Hardware Address"
			 "   Expires LastSend  Retry Status\n");
	अन्यथा अणु
		seq_म_लिखो(seq, "%04X:%02X  %-12s",
			   ntohs(entry->target_addr.s_net),
			   (अचिन्हित पूर्णांक) entry->target_addr.s_node,
			   entry->dev ? entry->dev->name : "????");
		seq_म_लिखो(seq, "%pM", entry->hwaddr);
		seq_म_लिखो(seq, " %8s",
			   dt2str((दीर्घ)entry->expires_at - (दीर्घ)now));
		अगर (iter->table == unresolved)
			seq_म_लिखो(seq, " %8s %6hu",
				   dt2str(now - entry->last_sent),
				   entry->xmit_count);
		अन्यथा
			seq_माला_दो(seq, "                ");
		seq_म_लिखो(seq, " %s\n",
			   (iter->table == resolved) ? "resolved"
			   : (iter->table == unresolved) ? "unresolved"
			   : (iter->table == proxies) ? "proxies"
			   : "unknown");
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations aarp_seq_ops = अणु
	.start  = aarp_seq_start,
	.next   = aarp_seq_next,
	.stop   = aarp_seq_stop,
	.show   = aarp_seq_show,
पूर्ण;
#पूर्ण_अगर

/* General module cleanup. Called from cleanup_module() in ddp.c. */
व्योम aarp_cleanup_module(व्योम)
अणु
	del_समयr_sync(&aarp_समयr);
	unरेजिस्टर_netdevice_notअगरier(&aarp_notअगरier);
	unरेजिस्टर_snap_client(aarp_dl);
	aarp_purge();
पूर्ण

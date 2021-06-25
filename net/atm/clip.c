<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* net/aपंचांग/clip.c - RFC1577 Classical IP over ATM */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h> /* क्रम अच_पूर्णांक_उच्च */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समयr.h>
#समावेश <linux/अगर_arp.h> /* क्रम some manअगरest स्थिरants */
#समावेश <linux/notअगरier.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगclip.h>
#समावेश <linux/aपंचांगarp.h>
#समावेश <linux/capability.h>
#समावेश <linux/ip.h> /* क्रम net/route.h */
#समावेश <linux/in.h> /* क्रम काष्ठा sockaddr_in */
#समावेश <linux/अगर.h> /* क्रम IFF_UP */
#समावेश <linux/inetdevice.h>
#समावेश <linux/bitops.h>
#समावेश <linux/poison.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/jhash.h>
#समावेश <linux/slab.h>
#समावेश <net/route.h> /* क्रम काष्ठा rtable and routing */
#समावेश <net/icmp.h> /* icmp_send */
#समावेश <net/arp.h>
#समावेश <linux/param.h> /* क्रम HZ */
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h> /* क्रम htons etc. */
#समावेश <linux/atomic.h>

#समावेश "common.h"
#समावेश "resources.h"
#समावेश <net/aपंचांगclip.h>

अटल काष्ठा net_device *clip_devs;
अटल काष्ठा aपंचांग_vcc *aपंचांगarpd;
अटल काष्ठा समयr_list idle_समयr;
अटल स्थिर काष्ठा neigh_ops clip_neigh_ops;

अटल पूर्णांक to_aपंचांगarpd(क्रमागत aपंचांगarp_ctrl_type type, पूर्णांक itf, __be32 ip)
अणु
	काष्ठा sock *sk;
	काष्ठा aपंचांगarp_ctrl *ctrl;
	काष्ठा sk_buff *skb;

	pr_debug("(%d)\n", type);
	अगर (!aपंचांगarpd)
		वापस -EUNATCH;
	skb = alloc_skb(माप(काष्ठा aपंचांगarp_ctrl), GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;
	ctrl = skb_put(skb, माप(काष्ठा aपंचांगarp_ctrl));
	ctrl->type = type;
	ctrl->itf_num = itf;
	ctrl->ip = ip;
	aपंचांग_क्रमce_अक्षरge(aपंचांगarpd, skb->truesize);

	sk = sk_aपंचांग(aपंचांगarpd);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_पढ़ोy(sk);
	वापस 0;
पूर्ण

अटल व्योम link_vcc(काष्ठा clip_vcc *clip_vcc, काष्ठा aपंचांगarp_entry *entry)
अणु
	pr_debug("%p to entry %p (neigh %p)\n", clip_vcc, entry, entry->neigh);
	clip_vcc->entry = entry;
	clip_vcc->xoff = 0;	/* @@@ may overrun buffer by one packet */
	clip_vcc->next = entry->vccs;
	entry->vccs = clip_vcc;
	entry->neigh->used = jअगरfies;
पूर्ण

अटल व्योम unlink_clip_vcc(काष्ठा clip_vcc *clip_vcc)
अणु
	काष्ठा aपंचांगarp_entry *entry = clip_vcc->entry;
	काष्ठा clip_vcc **walk;

	अगर (!entry) अणु
		pr_err("!clip_vcc->entry (clip_vcc %p)\n", clip_vcc);
		वापस;
	पूर्ण
	netअगर_tx_lock_bh(entry->neigh->dev);	/* block clip_start_xmit() */
	entry->neigh->used = jअगरfies;
	क्रम (walk = &entry->vccs; *walk; walk = &(*walk)->next)
		अगर (*walk == clip_vcc) अणु
			पूर्णांक error;

			*walk = clip_vcc->next;	/* atomic */
			clip_vcc->entry = शून्य;
			अगर (clip_vcc->xoff)
				netअगर_wake_queue(entry->neigh->dev);
			अगर (entry->vccs)
				जाओ out;
			entry->expires = jअगरfies - 1;
			/* क्रमce resolution or expiration */
			error = neigh_update(entry->neigh, शून्य, NUD_NONE,
					     NEIGH_UPDATE_F_ADMIN, 0);
			अगर (error)
				pr_err("neigh_update failed with %d\n", error);
			जाओ out;
		पूर्ण
	pr_err("ATMARP: failed (entry %p, vcc 0x%p)\n", entry, clip_vcc);
out:
	netअगर_tx_unlock_bh(entry->neigh->dev);
पूर्ण

/* The neighbour entry n->lock is held. */
अटल पूर्णांक neigh_check_cb(काष्ठा neighbour *n)
अणु
	काष्ठा aपंचांगarp_entry *entry = neighbour_priv(n);
	काष्ठा clip_vcc *cv;

	अगर (n->ops != &clip_neigh_ops)
		वापस 0;
	क्रम (cv = entry->vccs; cv; cv = cv->next) अणु
		अचिन्हित दीर्घ exp = cv->last_use + cv->idle_समयout;

		अगर (cv->idle_समयout && समय_after(jअगरfies, exp)) अणु
			pr_debug("releasing vcc %p->%p of entry %p\n",
				 cv, cv->vcc, entry);
			vcc_release_async(cv->vcc, -ETIMEDOUT);
		पूर्ण
	पूर्ण

	अगर (entry->vccs || समय_beक्रमe(jअगरfies, entry->expires))
		वापस 0;

	अगर (refcount_पढ़ो(&n->refcnt) > 1) अणु
		काष्ठा sk_buff *skb;

		pr_debug("destruction postponed with ref %d\n",
			 refcount_पढ़ो(&n->refcnt));

		जबतक ((skb = skb_dequeue(&n->arp_queue)) != शून्य)
			dev_kमुक्त_skb(skb);

		वापस 0;
	पूर्ण

	pr_debug("expired neigh %p\n", n);
	वापस 1;
पूर्ण

अटल व्योम idle_समयr_check(काष्ठा समयr_list *unused)
अणु
	ग_लिखो_lock(&arp_tbl.lock);
	__neigh_क्रम_each_release(&arp_tbl, neigh_check_cb);
	mod_समयr(&idle_समयr, jअगरfies + CLIP_CHECK_INTERVAL * HZ);
	ग_लिखो_unlock(&arp_tbl.lock);
पूर्ण

अटल पूर्णांक clip_arp_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा aपंचांग_vcc *vcc;

	pr_debug("\n");
	vcc = ATM_SKB(skb)->vcc;
	अगर (!vcc || !aपंचांग_अक्षरge(vcc, skb->truesize)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण
	pr_debug("pushing to %p\n", vcc);
	pr_debug("using %p\n", CLIP_VCC(vcc)->old_push);
	CLIP_VCC(vcc)->old_push(vcc, skb);
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित अक्षर llc_oui[] = अणु
	0xaa,	/* DSAP: non-ISO */
	0xaa,	/* SSAP: non-ISO */
	0x03,	/* Ctrl: Unnumbered Inक्रमmation Command PDU */
	0x00,	/* OUI: EtherType */
	0x00,
	0x00
पूर्ण;

अटल व्योम clip_push(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा clip_vcc *clip_vcc = CLIP_VCC(vcc);

	pr_debug("\n");

	अगर (!clip_devs) अणु
		aपंचांग_वापस(vcc, skb->truesize);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (!skb) अणु
		pr_debug("removing VCC %p\n", clip_vcc);
		अगर (clip_vcc->entry)
			unlink_clip_vcc(clip_vcc);
		clip_vcc->old_push(vcc, शून्य);	/* pass on the bad news */
		kमुक्त(clip_vcc);
		वापस;
	पूर्ण
	aपंचांग_वापस(vcc, skb->truesize);
	skb->dev = clip_vcc->entry ? clip_vcc->entry->neigh->dev : clip_devs;
	/* clip_vcc->entry == शून्य अगर we करोn't have an IP address yet */
	अगर (!skb->dev) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण
	ATM_SKB(skb)->vcc = vcc;
	skb_reset_mac_header(skb);
	अगर (!clip_vcc->encap ||
	    skb->len < RFC1483LLC_LEN ||
	    स_भेद(skb->data, llc_oui, माप(llc_oui)))
		skb->protocol = htons(ETH_P_IP);
	अन्यथा अणु
		skb->protocol = ((__be16 *)skb->data)[3];
		skb_pull(skb, RFC1483LLC_LEN);
		अगर (skb->protocol == htons(ETH_P_ARP)) अणु
			skb->dev->stats.rx_packets++;
			skb->dev->stats.rx_bytes += skb->len;
			clip_arp_rcv(skb);
			वापस;
		पूर्ण
	पूर्ण
	clip_vcc->last_use = jअगरfies;
	skb->dev->stats.rx_packets++;
	skb->dev->stats.rx_bytes += skb->len;
	स_रखो(ATM_SKB(skb), 0, माप(काष्ठा aपंचांग_skb_data));
	netअगर_rx(skb);
पूर्ण

/*
 * Note: these spinlocks _must_not_ block on non-SMP. The only goal is that
 * clip_pop is atomic with respect to the critical section in clip_start_xmit.
 */

अटल व्योम clip_pop(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा clip_vcc *clip_vcc = CLIP_VCC(vcc);
	काष्ठा net_device *dev = skb->dev;
	पूर्णांक old;
	अचिन्हित दीर्घ flags;

	pr_debug("(vcc %p)\n", vcc);
	clip_vcc->old_pop(vcc, skb);
	/* skb->dev == शून्य in outbound ARP packets */
	अगर (!dev)
		वापस;
	spin_lock_irqsave(&PRIV(dev)->xoff_lock, flags);
	अगर (aपंचांग_may_send(vcc, 0)) अणु
		old = xchg(&clip_vcc->xoff, 0);
		अगर (old)
			netअगर_wake_queue(dev);
	पूर्ण
	spin_unlock_irqrestore(&PRIV(dev)->xoff_lock, flags);
पूर्ण

अटल व्योम clip_neigh_solicit(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	__be32 *ip = (__be32 *) neigh->primary_key;

	pr_debug("(neigh %p, skb %p)\n", neigh, skb);
	to_aपंचांगarpd(act_need, PRIV(neigh->dev)->number, *ip);
पूर्ण

अटल व्योम clip_neigh_error(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
#अगर_अघोषित CONFIG_ATM_CLIP_NO_ICMP
	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, 0);
#पूर्ण_अगर
	kमुक्त_skb(skb);
पूर्ण

अटल स्थिर काष्ठा neigh_ops clip_neigh_ops = अणु
	.family =		AF_INET,
	.solicit =		clip_neigh_solicit,
	.error_report =		clip_neigh_error,
	.output =		neigh_direct_output,
	.connected_output =	neigh_direct_output,
पूर्ण;

अटल पूर्णांक clip_स्थिरructor(काष्ठा net_device *dev, काष्ठा neighbour *neigh)
अणु
	काष्ठा aपंचांगarp_entry *entry = neighbour_priv(neigh);

	अगर (neigh->tbl->family != AF_INET)
		वापस -EINVAL;

	अगर (neigh->type != RTN_UNICAST)
		वापस -EINVAL;

	neigh->nud_state = NUD_NONE;
	neigh->ops = &clip_neigh_ops;
	neigh->output = neigh->ops->output;
	entry->neigh = neigh;
	entry->vccs = शून्य;
	entry->expires = jअगरfies - 1;

	वापस 0;
पूर्ण

/* @@@ copy bh locking from arp.c -- need to bh-enable aपंचांग code beक्रमe */

/*
 * We play with the resolve flag: 0 and 1 have the usual meaning, but -1 means
 * to allocate the neighbour entry but not to ask aपंचांगarpd क्रम resolution. Also,
 * करोn't increment the usage count. This is used to create entries in
 * clip_setentry.
 */

अटल पूर्णांक clip_encap(काष्ठा aपंचांग_vcc *vcc, पूर्णांक mode)
अणु
	अगर (!CLIP_VCC(vcc))
		वापस -EBADFD;

	CLIP_VCC(vcc)->encap = mode;
	वापस 0;
पूर्ण

अटल netdev_tx_t clip_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	काष्ठा clip_priv *clip_priv = PRIV(dev);
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा aपंचांगarp_entry *entry;
	काष्ठा neighbour *n;
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा rtable *rt;
	__be32 *daddr;
	पूर्णांक old;
	अचिन्हित दीर्घ flags;

	pr_debug("(skb %p)\n", skb);
	अगर (!dst) अणु
		pr_err("skb_dst(skb) == NULL\n");
		dev_kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	rt = (काष्ठा rtable *) dst;
	अगर (rt->rt_gw_family == AF_INET)
		daddr = &rt->rt_gw4;
	अन्यथा
		daddr = &ip_hdr(skb)->daddr;
	n = dst_neigh_lookup(dst, daddr);
	अगर (!n) अणु
		pr_err("NO NEIGHBOUR !\n");
		dev_kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	entry = neighbour_priv(n);
	अगर (!entry->vccs) अणु
		अगर (समय_after(jअगरfies, entry->expires)) अणु
			/* should be resolved */
			entry->expires = jअगरfies + ATMARP_RETRY_DELAY * HZ;
			to_aपंचांगarpd(act_need, PRIV(dev)->number, *((__be32 *)n->primary_key));
		पूर्ण
		अगर (entry->neigh->arp_queue.qlen < ATMARP_MAX_UNRES_PACKETS)
			skb_queue_tail(&entry->neigh->arp_queue, skb);
		अन्यथा अणु
			dev_kमुक्त_skb(skb);
			dev->stats.tx_dropped++;
		पूर्ण
		जाओ out_release_neigh;
	पूर्ण
	pr_debug("neigh %p, vccs %p\n", entry, entry->vccs);
	ATM_SKB(skb)->vcc = vcc = entry->vccs->vcc;
	pr_debug("using neighbour %p, vcc %p\n", n, vcc);
	अगर (entry->vccs->encap) अणु
		व्योम *here;

		here = skb_push(skb, RFC1483LLC_LEN);
		स_नकल(here, llc_oui, माप(llc_oui));
		((__be16 *) here)[3] = skb->protocol;
	पूर्ण
	aपंचांग_account_tx(vcc, skb);
	entry->vccs->last_use = jअगरfies;
	pr_debug("atm_skb(%p)->vcc(%p)->dev(%p)\n", skb, vcc, vcc->dev);
	old = xchg(&entry->vccs->xoff, 1);	/* assume XOFF ... */
	अगर (old) अणु
		pr_warn("XOFF->XOFF transition\n");
		जाओ out_release_neigh;
	पूर्ण
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	vcc->send(vcc, skb);
	अगर (aपंचांग_may_send(vcc, 0)) अणु
		entry->vccs->xoff = 0;
		जाओ out_release_neigh;
	पूर्ण
	spin_lock_irqsave(&clip_priv->xoff_lock, flags);
	netअगर_stop_queue(dev);	/* XOFF -> throttle immediately */
	barrier();
	अगर (!entry->vccs->xoff)
		netअगर_start_queue(dev);
	/* Oh, we just raced with clip_pop. netअगर_start_queue should be
	   good enough, because nothing should really be asleep because
	   of the brief netअगर_stop_queue. If this isn't true or अगर it
	   changes, use netअगर_wake_queue instead. */
	spin_unlock_irqrestore(&clip_priv->xoff_lock, flags);
out_release_neigh:
	neigh_release(n);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक clip_mkip(काष्ठा aपंचांग_vcc *vcc, पूर्णांक समयout)
अणु
	काष्ठा clip_vcc *clip_vcc;

	अगर (!vcc->push)
		वापस -EBADFD;
	clip_vcc = kदो_स्मृति(माप(काष्ठा clip_vcc), GFP_KERNEL);
	अगर (!clip_vcc)
		वापस -ENOMEM;
	pr_debug("%p vcc %p\n", clip_vcc, vcc);
	clip_vcc->vcc = vcc;
	vcc->user_back = clip_vcc;
	set_bit(ATM_VF_IS_CLIP, &vcc->flags);
	clip_vcc->entry = शून्य;
	clip_vcc->xoff = 0;
	clip_vcc->encap = 1;
	clip_vcc->last_use = jअगरfies;
	clip_vcc->idle_समयout = समयout * HZ;
	clip_vcc->old_push = vcc->push;
	clip_vcc->old_pop = vcc->pop;
	vcc->push = clip_push;
	vcc->pop = clip_pop;

	/* re-process everything received between connection setup and MKIP */
	vcc_process_recv_queue(vcc);

	वापस 0;
पूर्ण

अटल पूर्णांक clip_setentry(काष्ठा aपंचांग_vcc *vcc, __be32 ip)
अणु
	काष्ठा neighbour *neigh;
	काष्ठा aपंचांगarp_entry *entry;
	पूर्णांक error;
	काष्ठा clip_vcc *clip_vcc;
	काष्ठा rtable *rt;

	अगर (vcc->push != clip_push) अणु
		pr_warn("non-CLIP VCC\n");
		वापस -EBADF;
	पूर्ण
	clip_vcc = CLIP_VCC(vcc);
	अगर (!ip) अणु
		अगर (!clip_vcc->entry) अणु
			pr_err("hiding hidden ATMARP entry\n");
			वापस 0;
		पूर्ण
		pr_debug("remove\n");
		unlink_clip_vcc(clip_vcc);
		वापस 0;
	पूर्ण
	rt = ip_route_output(&init_net, ip, 0, 1, 0);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);
	neigh = __neigh_lookup(&arp_tbl, &ip, rt->dst.dev, 1);
	ip_rt_put(rt);
	अगर (!neigh)
		वापस -ENOMEM;
	entry = neighbour_priv(neigh);
	अगर (entry != clip_vcc->entry) अणु
		अगर (!clip_vcc->entry)
			pr_debug("add\n");
		अन्यथा अणु
			pr_debug("update\n");
			unlink_clip_vcc(clip_vcc);
		पूर्ण
		link_vcc(clip_vcc, entry);
	पूर्ण
	error = neigh_update(neigh, llc_oui, NUD_PERMANENT,
			     NEIGH_UPDATE_F_OVERRIDE | NEIGH_UPDATE_F_ADMIN, 0);
	neigh_release(neigh);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा net_device_ops clip_netdev_ops = अणु
	.nकरो_start_xmit		= clip_start_xmit,
	.nकरो_neigh_स्थिरruct	= clip_स्थिरructor,
पूर्ण;

अटल व्योम clip_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &clip_netdev_ops;
	dev->type = ARPHRD_ATM;
	dev->neigh_priv_len = माप(काष्ठा aपंचांगarp_entry);
	dev->hard_header_len = RFC1483LLC_LEN;
	dev->mtu = RFC1626_MTU;
	dev->tx_queue_len = 100;	/* "normal" queue (packets) */
	/* When using a "real" qdisc, the qdisc determines the queue */
	/* length. tx_queue_len is only used क्रम the शेष हाल, */
	/* without any more elaborate queuing. 100 is a reasonable */
	/* compromise between decent burst-tolerance and protection */
	/* against memory hogs. */
	netअगर_keep_dst(dev);
पूर्ण

अटल पूर्णांक clip_create(पूर्णांक number)
अणु
	काष्ठा net_device *dev;
	काष्ठा clip_priv *clip_priv;
	पूर्णांक error;

	अगर (number != -1) अणु
		क्रम (dev = clip_devs; dev; dev = PRIV(dev)->next)
			अगर (PRIV(dev)->number == number)
				वापस -EEXIST;
	पूर्ण अन्यथा अणु
		number = 0;
		क्रम (dev = clip_devs; dev; dev = PRIV(dev)->next)
			अगर (PRIV(dev)->number >= number)
				number = PRIV(dev)->number + 1;
	पूर्ण
	dev = alloc_netdev(माप(काष्ठा clip_priv), "", NET_NAME_UNKNOWN,
			   clip_setup);
	अगर (!dev)
		वापस -ENOMEM;
	clip_priv = PRIV(dev);
	प्र_लिखो(dev->name, "atm%d", number);
	spin_lock_init(&clip_priv->xoff_lock);
	clip_priv->number = number;
	error = रेजिस्टर_netdev(dev);
	अगर (error) अणु
		मुक्त_netdev(dev);
		वापस error;
	पूर्ण
	clip_priv->next = clip_devs;
	clip_devs = dev;
	pr_debug("registered (net:%s)\n", dev->name);
	वापस number;
पूर्ण

अटल पूर्णांक clip_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_UNREGISTER)
		वापस NOTIFY_DONE;

	/* ignore non-CLIP devices */
	अगर (dev->type != ARPHRD_ATM || dev->netdev_ops != &clip_netdev_ops)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		pr_debug("NETDEV_UP\n");
		to_aपंचांगarpd(act_up, PRIV(dev)->number, 0);
		अवरोध;
	हाल NETDEV_GOING_DOWN:
		pr_debug("NETDEV_DOWN\n");
		to_aपंचांगarpd(act_करोwn, PRIV(dev)->number, 0);
		अवरोध;
	हाल NETDEV_CHANGE:
	हाल NETDEV_CHANGEMTU:
		pr_debug("NETDEV_CHANGE*\n");
		to_aपंचांगarpd(act_change, PRIV(dev)->number, 0);
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक clip_inet_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *अगरa)
अणु
	काष्ठा in_device *in_dev;
	काष्ठा netdev_notअगरier_info info;

	in_dev = ((काष्ठा in_अगरaddr *)अगरa)->अगरa_dev;
	/*
	 * Transitions are of the करोwn-change-up type, so it's sufficient to
	 * handle the change on up.
	 */
	अगर (event != NETDEV_UP)
		वापस NOTIFY_DONE;
	netdev_notअगरier_info_init(&info, in_dev->dev);
	वापस clip_device_event(this, NETDEV_CHANGE, &info);
पूर्ण

अटल काष्ठा notअगरier_block clip_dev_notअगरier = अणु
	.notअगरier_call = clip_device_event,
पूर्ण;



अटल काष्ठा notअगरier_block clip_inet_notअगरier = अणु
	.notअगरier_call = clip_inet_event,
पूर्ण;



अटल व्योम aपंचांगarpd_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	pr_debug("\n");

	rtnl_lock();
	aपंचांगarpd = शून्य;
	skb_queue_purge(&sk_aपंचांग(vcc)->sk_receive_queue);
	rtnl_unlock();

	pr_debug("(done)\n");
	module_put(THIS_MODULE);
पूर्ण

अटल स्थिर काष्ठा aपंचांगdev_ops aपंचांगarpd_dev_ops = अणु
	.बंद = aपंचांगarpd_बंद
पूर्ण;


अटल काष्ठा aपंचांग_dev aपंचांगarpd_dev = अणु
	.ops =			&aपंचांगarpd_dev_ops,
	.type =			"arpd",
	.number = 		999,
	.lock =			__SPIN_LOCK_UNLOCKED(aपंचांगarpd_dev.lock)
पूर्ण;


अटल पूर्णांक aपंचांग_init_aपंचांगarp(काष्ठा aपंचांग_vcc *vcc)
अणु
	rtnl_lock();
	अगर (aपंचांगarpd) अणु
		rtnl_unlock();
		वापस -EADDRINUSE;
	पूर्ण

	mod_समयr(&idle_समयr, jअगरfies + CLIP_CHECK_INTERVAL * HZ);

	aपंचांगarpd = vcc;
	set_bit(ATM_VF_META, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);
	    /* allow replies and aव्योम getting बंदd अगर संकेतing dies */
	vcc->dev = &aपंचांगarpd_dev;
	vcc_insert_socket(sk_aपंचांग(vcc));
	vcc->push = शून्य;
	vcc->pop = शून्य; /* crash */
	vcc->push_oam = शून्य; /* crash */
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक clip_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल SIOCMKCLIP:
	हाल ATMARPD_CTRL:
	हाल ATMARP_MKIP:
	हाल ATMARP_SETENTRY:
	हाल ATMARP_ENCAP:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	चयन (cmd) अणु
	हाल SIOCMKCLIP:
		err = clip_create(arg);
		अवरोध;
	हाल ATMARPD_CTRL:
		err = aपंचांग_init_aपंचांगarp(vcc);
		अगर (!err) अणु
			sock->state = SS_CONNECTED;
			__module_get(THIS_MODULE);
		पूर्ण
		अवरोध;
	हाल ATMARP_MKIP:
		err = clip_mkip(vcc, arg);
		अवरोध;
	हाल ATMARP_SETENTRY:
		err = clip_setentry(vcc, (__क्रमce __be32)arg);
		अवरोध;
	हाल ATMARP_ENCAP:
		err = clip_encap(vcc, arg);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा aपंचांग_ioctl clip_ioctl_ops = अणु
	.owner = THIS_MODULE,
	.ioctl = clip_ioctl,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम svc_addr(काष्ठा seq_file *seq, काष्ठा sockaddr_aपंचांगsvc *addr)
अणु
	अटल पूर्णांक code[] = अणु 1, 2, 10, 6, 1, 0 पूर्ण;
	अटल पूर्णांक e164[] = अणु 1, 8, 4, 6, 1, 0 पूर्ण;

	अगर (*addr->sas_addr.pub) अणु
		seq_म_लिखो(seq, "%s", addr->sas_addr.pub);
		अगर (*addr->sas_addr.prv)
			seq_अ_दो(seq, '+');
	पूर्ण अन्यथा अगर (!*addr->sas_addr.prv) अणु
		seq_म_लिखो(seq, "%s", "(none)");
		वापस;
	पूर्ण
	अगर (*addr->sas_addr.prv) अणु
		अचिन्हित अक्षर *prv = addr->sas_addr.prv;
		पूर्णांक *fields;
		पूर्णांक i, j;

		fields = *prv == ATM_AFI_E164 ? e164 : code;
		क्रम (i = 0; fields[i]; i++) अणु
			क्रम (j = fields[i]; j; j--)
				seq_म_लिखो(seq, "%02X", *prv++);
			अगर (fields[i + 1])
				seq_अ_दो(seq, '.');
		पूर्ण
	पूर्ण
पूर्ण

/* This means the neighbour entry has no attached VCC objects. */
#घोषणा SEQ_NO_VCC_TOKEN	((व्योम *) 2)

अटल व्योम aपंचांगarp_info(काष्ठा seq_file *seq, काष्ठा neighbour *n,
			काष्ठा aपंचांगarp_entry *entry, काष्ठा clip_vcc *clip_vcc)
अणु
	काष्ठा net_device *dev = n->dev;
	अचिन्हित दीर्घ exp;
	अक्षर buf[17];
	पूर्णांक svc, llc, off;

	svc = ((clip_vcc == SEQ_NO_VCC_TOKEN) ||
	       (sk_aपंचांग(clip_vcc->vcc)->sk_family == AF_ATMSVC));

	llc = ((clip_vcc == SEQ_NO_VCC_TOKEN) || clip_vcc->encap);

	अगर (clip_vcc == SEQ_NO_VCC_TOKEN)
		exp = entry->neigh->used;
	अन्यथा
		exp = clip_vcc->last_use;

	exp = (jअगरfies - exp) / HZ;

	seq_म_लिखो(seq, "%-6s%-4s%-4s%5ld ",
		   dev->name, svc ? "SVC" : "PVC", llc ? "LLC" : "NULL", exp);

	off = scnम_लिखो(buf, माप(buf) - 1, "%pI4", n->primary_key);
	जबतक (off < 16)
		buf[off++] = ' ';
	buf[off] = '\0';
	seq_म_लिखो(seq, "%s", buf);

	अगर (clip_vcc == SEQ_NO_VCC_TOKEN) अणु
		अगर (समय_beक्रमe(jअगरfies, entry->expires))
			seq_म_लिखो(seq, "(resolving)\n");
		अन्यथा
			seq_म_लिखो(seq, "(expired, ref %d)\n",
				   refcount_पढ़ो(&entry->neigh->refcnt));
	पूर्ण अन्यथा अगर (!svc) अणु
		seq_म_लिखो(seq, "%d.%d.%d\n",
			   clip_vcc->vcc->dev->number,
			   clip_vcc->vcc->vpi, clip_vcc->vcc->vci);
	पूर्ण अन्यथा अणु
		svc_addr(seq, &clip_vcc->vcc->remote);
		seq_अ_दो(seq, '\n');
	पूर्ण
पूर्ण

काष्ठा clip_seq_state अणु
	/* This member must be first. */
	काष्ठा neigh_seq_state ns;

	/* Local to clip specअगरic iteration. */
	काष्ठा clip_vcc *vcc;
पूर्ण;

अटल काष्ठा clip_vcc *clip_seq_next_vcc(काष्ठा aपंचांगarp_entry *e,
					  काष्ठा clip_vcc *curr)
अणु
	अगर (!curr) अणु
		curr = e->vccs;
		अगर (!curr)
			वापस SEQ_NO_VCC_TOKEN;
		वापस curr;
	पूर्ण
	अगर (curr == SEQ_NO_VCC_TOKEN)
		वापस शून्य;

	curr = curr->next;

	वापस curr;
पूर्ण

अटल व्योम *clip_seq_vcc_walk(काष्ठा clip_seq_state *state,
			       काष्ठा aपंचांगarp_entry *e, loff_t * pos)
अणु
	काष्ठा clip_vcc *vcc = state->vcc;

	vcc = clip_seq_next_vcc(e, vcc);
	अगर (vcc && pos != शून्य) अणु
		जबतक (*pos) अणु
			vcc = clip_seq_next_vcc(e, vcc);
			अगर (!vcc)
				अवरोध;
			--(*pos);
		पूर्ण
	पूर्ण
	state->vcc = vcc;

	वापस vcc;
पूर्ण

अटल व्योम *clip_seq_sub_iter(काष्ठा neigh_seq_state *_state,
			       काष्ठा neighbour *n, loff_t * pos)
अणु
	काष्ठा clip_seq_state *state = (काष्ठा clip_seq_state *)_state;

	अगर (n->dev->type != ARPHRD_ATM)
		वापस शून्य;

	वापस clip_seq_vcc_walk(state, neighbour_priv(n), pos);
पूर्ण

अटल व्योम *clip_seq_start(काष्ठा seq_file *seq, loff_t * pos)
अणु
	काष्ठा clip_seq_state *state = seq->निजी;
	state->ns.neigh_sub_iter = clip_seq_sub_iter;
	वापस neigh_seq_start(seq, pos, &arp_tbl, NEIGH_SEQ_NEIGH_ONLY);
पूर्ण

अटल पूर्णांक clip_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल अक्षर aपंचांग_arp_banner[] =
	    "IPitf TypeEncp Idle IP address      ATM address\n";

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, aपंचांग_arp_banner);
	पूर्ण अन्यथा अणु
		काष्ठा clip_seq_state *state = seq->निजी;
		काष्ठा clip_vcc *vcc = state->vcc;
		काष्ठा neighbour *n = v;

		aपंचांगarp_info(seq, n, neighbour_priv(n), vcc);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations arp_seq_ops = अणु
	.start	= clip_seq_start,
	.next	= neigh_seq_next,
	.stop	= neigh_seq_stop,
	.show	= clip_seq_show,
पूर्ण;
#पूर्ण_अगर

अटल व्योम aपंचांग_clip_निकास_noproc(व्योम);

अटल पूर्णांक __init aपंचांग_clip_init(व्योम)
अणु
	रेजिस्टर_aपंचांग_ioctl(&clip_ioctl_ops);
	रेजिस्टर_netdevice_notअगरier(&clip_dev_notअगरier);
	रेजिस्टर_inetaddr_notअगरier(&clip_inet_notअगरier);

	समयr_setup(&idle_समयr, idle_समयr_check, 0);

#अगर_घोषित CONFIG_PROC_FS
	अणु
		काष्ठा proc_dir_entry *p;

		p = proc_create_net("arp", 0444, aपंचांग_proc_root, &arp_seq_ops,
				माप(काष्ठा clip_seq_state));
		अगर (!p) अणु
			pr_err("Unable to initialize /proc/net/atm/arp\n");
			aपंचांग_clip_निकास_noproc();
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम aपंचांग_clip_निकास_noproc(व्योम)
अणु
	काष्ठा net_device *dev, *next;

	unरेजिस्टर_inetaddr_notअगरier(&clip_inet_notअगरier);
	unरेजिस्टर_netdevice_notअगरier(&clip_dev_notअगरier);

	deरेजिस्टर_aपंचांग_ioctl(&clip_ioctl_ops);

	/* First, stop the idle समयr, so it stops banging
	 * on the table.
	 */
	del_समयr_sync(&idle_समयr);

	dev = clip_devs;
	जबतक (dev) अणु
		next = PRIV(dev)->next;
		unरेजिस्टर_netdev(dev);
		मुक्त_netdev(dev);
		dev = next;
	पूर्ण
पूर्ण

अटल व्योम __निकास aपंचांग_clip_निकास(व्योम)
अणु
	हटाओ_proc_entry("arp", aपंचांग_proc_root);

	aपंचांग_clip_निकास_noproc();
पूर्ण

module_init(aपंचांग_clip_init);
module_निकास(aपंचांग_clip_निकास);
MODULE_AUTHOR("Werner Almesberger");
MODULE_DESCRIPTION("Classical/IP over ATM interface");
MODULE_LICENSE("GPL");

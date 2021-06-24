<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAIF Interface registration.
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 *
 * Borrowed heavily from file: pn_dev.c. Thanks to Remi Denis-Courmont
 *  and Sakari Ailus <sakari.ailus@nokia.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <net/netns/generic.h>
#समावेश <net/net_namespace.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/caअगर/caअगर_device.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/caअगर_dev.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/cfcnfg.h>
#समावेश <net/caअगर/cfserl.h>

MODULE_LICENSE("GPL");

/* Used क्रम local tracking of the CAIF net devices */
काष्ठा caअगर_device_entry अणु
	काष्ठा cflayer layer;
	काष्ठा list_head list;
	काष्ठा net_device *netdev;
	पूर्णांक __percpu *pcpu_refcnt;
	spinlock_t flow_lock;
	काष्ठा sk_buff *xoff_skb;
	व्योम (*xoff_skb_dtor)(काष्ठा sk_buff *skb);
	bool xoff;
पूर्ण;

काष्ठा caअगर_device_entry_list अणु
	काष्ठा list_head list;
	/* Protects simulanous deletes in list */
	काष्ठा mutex lock;
पूर्ण;

काष्ठा caअगर_net अणु
	काष्ठा cfcnfg *cfg;
	काष्ठा caअगर_device_entry_list caअगरdevs;
पूर्ण;

अटल अचिन्हित पूर्णांक caअगर_net_id;
अटल पूर्णांक q_high = 50; /* Percent */

काष्ठा cfcnfg *get_cfcnfg(काष्ठा net *net)
अणु
	काष्ठा caअगर_net *caअगरn;
	caअगरn = net_generic(net, caअगर_net_id);
	वापस caअगरn->cfg;
पूर्ण
EXPORT_SYMBOL(get_cfcnfg);

अटल काष्ठा caअगर_device_entry_list *caअगर_device_list(काष्ठा net *net)
अणु
	काष्ठा caअगर_net *caअगरn;
	caअगरn = net_generic(net, caअगर_net_id);
	वापस &caअगरn->caअगरdevs;
पूर्ण

अटल व्योम caअगरd_put(काष्ठा caअगर_device_entry *e)
अणु
	this_cpu_dec(*e->pcpu_refcnt);
पूर्ण

अटल व्योम caअगरd_hold(काष्ठा caअगर_device_entry *e)
अणु
	this_cpu_inc(*e->pcpu_refcnt);
पूर्ण

अटल पूर्णांक caअगरd_refcnt_पढ़ो(काष्ठा caअगर_device_entry *e)
अणु
	पूर्णांक i, refcnt = 0;
	क्रम_each_possible_cpu(i)
		refcnt += *per_cpu_ptr(e->pcpu_refcnt, i);
	वापस refcnt;
पूर्ण

/* Allocate new CAIF device. */
अटल काष्ठा caअगर_device_entry *caअगर_device_alloc(काष्ठा net_device *dev)
अणु
	काष्ठा caअगर_device_entry *caअगरd;

	caअगरd = kzalloc(माप(*caअगरd), GFP_KERNEL);
	अगर (!caअगरd)
		वापस शून्य;
	caअगरd->pcpu_refcnt = alloc_percpu(पूर्णांक);
	अगर (!caअगरd->pcpu_refcnt) अणु
		kमुक्त(caअगरd);
		वापस शून्य;
	पूर्ण
	caअगरd->netdev = dev;
	dev_hold(dev);
	वापस caअगरd;
पूर्ण

अटल काष्ठा caअगर_device_entry *caअगर_get(काष्ठा net_device *dev)
अणु
	काष्ठा caअगर_device_entry_list *caअगरdevs =
	    caअगर_device_list(dev_net(dev));
	काष्ठा caअगर_device_entry *caअगरd;

	list_क्रम_each_entry_rcu(caअगरd, &caअगरdevs->list, list,
				lockdep_rtnl_is_held()) अणु
		अगर (caअगरd->netdev == dev)
			वापस caअगरd;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम caअगर_flow_cb(काष्ठा sk_buff *skb)
अणु
	काष्ठा caअगर_device_entry *caअगरd;
	व्योम (*dtor)(काष्ठा sk_buff *skb) = शून्य;
	bool send_xoff;

	WARN_ON(skb->dev == शून्य);

	rcu_पढ़ो_lock();
	caअगरd = caअगर_get(skb->dev);

	WARN_ON(caअगरd == शून्य);
	अगर (!caअगरd) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	caअगरd_hold(caअगरd);
	rcu_पढ़ो_unlock();

	spin_lock_bh(&caअगरd->flow_lock);
	send_xoff = caअगरd->xoff;
	caअगरd->xoff = false;
	dtor = caअगरd->xoff_skb_dtor;

	अगर (WARN_ON(caअगरd->xoff_skb != skb))
		skb = शून्य;

	caअगरd->xoff_skb = शून्य;
	caअगरd->xoff_skb_dtor = शून्य;

	spin_unlock_bh(&caअगरd->flow_lock);

	अगर (dtor && skb)
		dtor(skb);

	अगर (send_xoff)
		caअगरd->layer.up->
			ctrlcmd(caअगरd->layer.up,
				_CAIF_CTRLCMD_PHYIF_FLOW_ON_IND,
				caअगरd->layer.id);
	caअगरd_put(caअगरd);
पूर्ण

अटल पूर्णांक transmit(काष्ठा cflayer *layer, काष्ठा cfpkt *pkt)
अणु
	पूर्णांक err, high = 0, qlen = 0;
	काष्ठा caअगर_device_entry *caअगरd =
	    container_of(layer, काष्ठा caअगर_device_entry, layer);
	काष्ठा sk_buff *skb;
	काष्ठा netdev_queue *txq;

	rcu_पढ़ो_lock_bh();

	skb = cfpkt_tonative(pkt);
	skb->dev = caअगरd->netdev;
	skb_reset_network_header(skb);
	skb->protocol = htons(ETH_P_CAIF);

	/* Check अगर we need to handle xoff */
	अगर (likely(caअगरd->netdev->priv_flags & IFF_NO_QUEUE))
		जाओ noxoff;

	अगर (unlikely(caअगरd->xoff))
		जाओ noxoff;

	अगर (likely(!netअगर_queue_stopped(caअगरd->netdev))) अणु
		काष्ठा Qdisc *sch;

		/* If we run with a TX queue, check अगर the queue is too दीर्घ*/
		txq = netdev_get_tx_queue(skb->dev, 0);
		sch = rcu_dereference_bh(txq->qdisc);
		अगर (likely(qdisc_is_empty(sch)))
			जाओ noxoff;

		/* can check क्रम explicit qdisc len value only !NOLOCK,
		 * always set flow off otherwise
		 */
		high = (caअगरd->netdev->tx_queue_len * q_high) / 100;
		अगर (!(sch->flags & TCQ_F_NOLOCK) && likely(sch->q.qlen < high))
			जाओ noxoff;
	पूर्ण

	/* Hold lock जबतक accessing xoff */
	spin_lock_bh(&caअगरd->flow_lock);
	अगर (caअगरd->xoff) अणु
		spin_unlock_bh(&caअगरd->flow_lock);
		जाओ noxoff;
	पूर्ण

	/*
	 * Handle flow off, we करो this by temporary hi-jacking this
	 * skb's deकाष्ठाor function, and replace it with our own
	 * flow-on callback. The callback will set flow-on and call
	 * the original deकाष्ठाor.
	 */

	pr_debug("queue has stopped(%d) or is full (%d > %d)\n",
			netअगर_queue_stopped(caअगरd->netdev),
			qlen, high);
	caअगरd->xoff = true;
	caअगरd->xoff_skb = skb;
	caअगरd->xoff_skb_dtor = skb->deकाष्ठाor;
	skb->deकाष्ठाor = caअगर_flow_cb;
	spin_unlock_bh(&caअगरd->flow_lock);

	caअगरd->layer.up->ctrlcmd(caअगरd->layer.up,
					_CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND,
					caअगरd->layer.id);
noxoff:
	rcu_पढ़ो_unlock_bh();

	err = dev_queue_xmit(skb);
	अगर (err > 0)
		err = -EIO;

	वापस err;
पूर्ण

/*
 * Stuff received packets पूर्णांकo the CAIF stack.
 * On error, वापसs non-zero and releases the skb.
 */
अटल पूर्णांक receive(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		   काष्ठा packet_type *pkttype, काष्ठा net_device *orig_dev)
अणु
	काष्ठा cfpkt *pkt;
	काष्ठा caअगर_device_entry *caअगरd;
	पूर्णांक err;

	pkt = cfpkt_fromnative(CAIF_सूची_IN, skb);

	rcu_पढ़ो_lock();
	caअगरd = caअगर_get(dev);

	अगर (!caअगरd || !caअगरd->layer.up || !caअगरd->layer.up->receive ||
			!netअगर_oper_up(caअगरd->netdev)) अणु
		rcu_पढ़ो_unlock();
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	/* Hold reference to netdevice जबतक using CAIF stack */
	caअगरd_hold(caअगरd);
	rcu_पढ़ो_unlock();

	err = caअगरd->layer.up->receive(caअगरd->layer.up, pkt);

	/* For -EILSEQ the packet is not मुक्तd so so it now */
	अगर (err == -EILSEQ)
		cfpkt_destroy(pkt);

	/* Release reference to stack upwards */
	caअगरd_put(caअगरd);

	अगर (err != 0)
		err = NET_RX_DROP;
	वापस err;
पूर्ण

अटल काष्ठा packet_type caअगर_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_CAIF),
	.func = receive,
पूर्ण;

अटल व्योम dev_flowctrl(काष्ठा net_device *dev, पूर्णांक on)
अणु
	काष्ठा caअगर_device_entry *caअगरd;

	rcu_पढ़ो_lock();

	caअगरd = caअगर_get(dev);
	अगर (!caअगरd || !caअगरd->layer.up || !caअगरd->layer.up->ctrlcmd) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	caअगरd_hold(caअगरd);
	rcu_पढ़ो_unlock();

	caअगरd->layer.up->ctrlcmd(caअगरd->layer.up,
				 on ?
				 _CAIF_CTRLCMD_PHYIF_FLOW_ON_IND :
				 _CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND,
				 caअगरd->layer.id);
	caअगरd_put(caअगरd);
पूर्ण

पूर्णांक caअगर_enroll_dev(काष्ठा net_device *dev, काष्ठा caअगर_dev_common *caअगरdev,
		     काष्ठा cflayer *link_support, पूर्णांक head_room,
		     काष्ठा cflayer **layer,
		     पूर्णांक (**rcv_func)(काष्ठा sk_buff *, काष्ठा net_device *,
				      काष्ठा packet_type *,
				      काष्ठा net_device *))
अणु
	काष्ठा caअगर_device_entry *caअगरd;
	क्रमागत cfcnfg_phy_preference pref;
	काष्ठा cfcnfg *cfg = get_cfcnfg(dev_net(dev));
	काष्ठा caअगर_device_entry_list *caअगरdevs;
	पूर्णांक res;

	caअगरdevs = caअगर_device_list(dev_net(dev));
	caअगरd = caअगर_device_alloc(dev);
	अगर (!caअगरd)
		वापस -ENOMEM;
	*layer = &caअगरd->layer;
	spin_lock_init(&caअगरd->flow_lock);

	चयन (caअगरdev->link_select) अणु
	हाल CAIF_LINK_HIGH_BANDW:
		pref = CFPHYPREF_HIGH_BW;
		अवरोध;
	हाल CAIF_LINK_LOW_LATENCY:
		pref = CFPHYPREF_LOW_LAT;
		अवरोध;
	शेष:
		pref = CFPHYPREF_HIGH_BW;
		अवरोध;
	पूर्ण
	mutex_lock(&caअगरdevs->lock);
	list_add_rcu(&caअगरd->list, &caअगरdevs->list);

	strlcpy(caअगरd->layer.name, dev->name,
		माप(caअगरd->layer.name));
	caअगरd->layer.transmit = transmit;
	res = cfcnfg_add_phy_layer(cfg,
				dev,
				&caअगरd->layer,
				pref,
				link_support,
				caअगरdev->use_fcs,
				head_room);
	mutex_unlock(&caअगरdevs->lock);
	अगर (rcv_func)
		*rcv_func = receive;
	वापस res;
पूर्ण
EXPORT_SYMBOL(caअगर_enroll_dev);

/* notअगरy Caअगर of device events */
अटल पूर्णांक caअगर_device_notअगरy(काष्ठा notअगरier_block *me, अचिन्हित दीर्घ what,
			      व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा caअगर_device_entry *caअगरd = शून्य;
	काष्ठा caअगर_dev_common *caअगरdev;
	काष्ठा cfcnfg *cfg;
	काष्ठा cflayer *layer, *link_support;
	पूर्णांक head_room = 0;
	काष्ठा caअगर_device_entry_list *caअगरdevs;
	पूर्णांक res;

	cfg = get_cfcnfg(dev_net(dev));
	caअगरdevs = caअगर_device_list(dev_net(dev));

	caअगरd = caअगर_get(dev);
	अगर (caअगरd == शून्य && dev->type != ARPHRD_CAIF)
		वापस 0;

	चयन (what) अणु
	हाल NETDEV_REGISTER:
		अगर (caअगरd != शून्य)
			अवरोध;

		caअगरdev = netdev_priv(dev);

		link_support = शून्य;
		अगर (caअगरdev->use_frag) अणु
			head_room = 1;
			link_support = cfserl_create(dev->अगरindex,
							caअगरdev->use_stx);
			अगर (!link_support) अणु
				pr_warn("Out of memory\n");
				अवरोध;
			पूर्ण
		पूर्ण
		res = caअगर_enroll_dev(dev, caअगरdev, link_support, head_room,
				&layer, शून्य);
		अगर (res)
			cfserl_release(link_support);
		caअगरdev->flowctrl = dev_flowctrl;
		अवरोध;

	हाल NETDEV_UP:
		rcu_पढ़ो_lock();

		caअगरd = caअगर_get(dev);
		अगर (caअगरd == शून्य) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण

		caअगरd->xoff = false;
		cfcnfg_set_phy_state(cfg, &caअगरd->layer, true);
		rcu_पढ़ो_unlock();

		अवरोध;

	हाल NETDEV_DOWN:
		rcu_पढ़ो_lock();

		caअगरd = caअगर_get(dev);
		अगर (!caअगरd || !caअगरd->layer.up || !caअगरd->layer.up->ctrlcmd) अणु
			rcu_पढ़ो_unlock();
			वापस -EINVAL;
		पूर्ण

		cfcnfg_set_phy_state(cfg, &caअगरd->layer, false);
		caअगरd_hold(caअगरd);
		rcu_पढ़ो_unlock();

		caअगरd->layer.up->ctrlcmd(caअगरd->layer.up,
					 _CAIF_CTRLCMD_PHYIF_DOWN_IND,
					 caअगरd->layer.id);

		spin_lock_bh(&caअगरd->flow_lock);

		/*
		 * Replace our xoff-deकाष्ठाor with original deकाष्ठाor.
		 * We trust that skb->deकाष्ठाor *always* is called beक्रमe
		 * the skb reference is invalid. The hijacked SKB deकाष्ठाor
		 * takes the flow_lock so manipulating the skb->deकाष्ठाor here
		 * should be safe.
		*/
		अगर (caअगरd->xoff_skb_dtor != शून्य && caअगरd->xoff_skb != शून्य)
			caअगरd->xoff_skb->deकाष्ठाor = caअगरd->xoff_skb_dtor;

		caअगरd->xoff = false;
		caअगरd->xoff_skb_dtor = शून्य;
		caअगरd->xoff_skb = शून्य;

		spin_unlock_bh(&caअगरd->flow_lock);
		caअगरd_put(caअगरd);
		अवरोध;

	हाल NETDEV_UNREGISTER:
		mutex_lock(&caअगरdevs->lock);

		caअगरd = caअगर_get(dev);
		अगर (caअगरd == शून्य) अणु
			mutex_unlock(&caअगरdevs->lock);
			अवरोध;
		पूर्ण
		list_del_rcu(&caअगरd->list);

		/*
		 * NETDEV_UNREGISTER is called repeatedly until all reference
		 * counts क्रम the net-device are released. If references to
		 * caअगरd is taken, simply ignore NETDEV_UNREGISTER and रुको क्रम
		 * the next call to NETDEV_UNREGISTER.
		 *
		 * If any packets are in flight करोwn the CAIF Stack,
		 * cfcnfg_del_phy_layer will वापस nonzero.
		 * If no packets are in flight, the CAIF Stack associated
		 * with the net-device un-रेजिस्टरing is मुक्तd.
		 */

		अगर (caअगरd_refcnt_पढ़ो(caअगरd) != 0 ||
			cfcnfg_del_phy_layer(cfg, &caअगरd->layer) != 0) अणु

			pr_info("Wait for device inuse\n");
			/* Enrole device अगर CAIF Stack is still in use */
			list_add_rcu(&caअगरd->list, &caअगरdevs->list);
			mutex_unlock(&caअगरdevs->lock);
			अवरोध;
		पूर्ण

		synchronize_rcu();
		dev_put(caअगरd->netdev);
		मुक्त_percpu(caअगरd->pcpu_refcnt);
		kमुक्त(caअगरd);

		mutex_unlock(&caअगरdevs->lock);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block caअगर_device_notअगरier = अणु
	.notअगरier_call = caअगर_device_notअगरy,
	.priority = 0,
पूर्ण;

/* Per-namespace Caअगर devices handling */
अटल पूर्णांक caअगर_init_net(काष्ठा net *net)
अणु
	काष्ठा caअगर_net *caअगरn = net_generic(net, caअगर_net_id);
	INIT_LIST_HEAD(&caअगरn->caअगरdevs.list);
	mutex_init(&caअगरn->caअगरdevs.lock);

	caअगरn->cfg = cfcnfg_create();
	अगर (!caअगरn->cfg)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम caअगर_निकास_net(काष्ठा net *net)
अणु
	काष्ठा caअगर_device_entry *caअगरd, *पंचांगp;
	काष्ठा caअगर_device_entry_list *caअगरdevs =
	    caअगर_device_list(net);
	काष्ठा cfcnfg *cfg =  get_cfcnfg(net);

	rtnl_lock();
	mutex_lock(&caअगरdevs->lock);

	list_क्रम_each_entry_safe(caअगरd, पंचांगp, &caअगरdevs->list, list) अणु
		पूर्णांक i = 0;
		list_del_rcu(&caअगरd->list);
		cfcnfg_set_phy_state(cfg, &caअगरd->layer, false);

		जबतक (i < 10 &&
			(caअगरd_refcnt_पढ़ो(caअगरd) != 0 ||
			cfcnfg_del_phy_layer(cfg, &caअगरd->layer) != 0)) अणु

			pr_info("Wait for device inuse\n");
			msleep(250);
			i++;
		पूर्ण
		synchronize_rcu();
		dev_put(caअगरd->netdev);
		मुक्त_percpu(caअगरd->pcpu_refcnt);
		kमुक्त(caअगरd);
	पूर्ण
	cfcnfg_हटाओ(cfg);

	mutex_unlock(&caअगरdevs->lock);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations caअगर_net_ops = अणु
	.init = caअगर_init_net,
	.निकास = caअगर_निकास_net,
	.id   = &caअगर_net_id,
	.size = माप(काष्ठा caअगर_net),
पूर्ण;

/* Initialize Caअगर devices list */
अटल पूर्णांक __init caअगर_device_init(व्योम)
अणु
	पूर्णांक result;

	result = रेजिस्टर_pernet_subsys(&caअगर_net_ops);

	अगर (result)
		वापस result;

	रेजिस्टर_netdevice_notअगरier(&caअगर_device_notअगरier);
	dev_add_pack(&caअगर_packet_type);

	वापस result;
पूर्ण

अटल व्योम __निकास caअगर_device_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&caअगर_device_notअगरier);
	dev_हटाओ_pack(&caअगर_packet_type);
	unरेजिस्टर_pernet_subsys(&caअगर_net_ops);
पूर्ण

module_init(caअगर_device_init);
module_निकास(caअगर_device_निकास);

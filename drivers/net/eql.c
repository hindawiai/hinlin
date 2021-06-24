<शैली गुरु>
/*
 * Equalizer Load-balancer क्रम serial network पूर्णांकerfaces.
 *
 * (c) Copyright 1995 Simon "Guru Aleph-Null" Janes
 * NCM: Network and Communications Management, Inc.
 *
 * (c) Copyright 2002 David S. Miller (davem@redhat.com)
 *
 *	This software may be used and distributed according to the terms
 *	of the GNU General Public License, incorporated herein by reference.
 *
 * The author may be reached as simon@ncm.com, or C/O
 *    NCM
 *    Attn: Simon Janes
 *    6803 Whittier Ave
 *    McLean VA 22101
 *    Phone: 1-703-847-0040 ext 103
 */

/*
 * Sources:
 *   skeleton.c by Donald Becker.
 * Inspirations:
 *   The Harried and Overworked Alan Cox
 * Conspiracies:
 *   The Alan Cox and Mike McLagan plot to get someone अन्यथा to करो the code,
 *   which turned out to be me.
 */

/*
 * $Log: eql.c,v $
 * Revision 1.2  1996/04/11 17:51:52  guru
 * Added one-line eql_हटाओ_slave patch.
 *
 * Revision 1.1  1996/04/11 17:44:17  guru
 * Initial revision
 *
 * Revision 3.13  1996/01/21  15:17:18  alan
 * tx_queue_len changes.
 * reक्रमmatted.
 *
 * Revision 3.12  1995/03/22  21:07:51  anarchy
 * Added capable() checks on configuration.
 * Moved header file.
 *
 * Revision 3.11  1995/01/19  23:14:31  guru
 * 		      slave_load = (अच_दीर्घ_उच्च - (अच_दीर्घ_उच्च / 2)) -
 * 			(priority_Bps) + bytes_queued * 8;
 *
 * Revision 3.10  1995/01/19  23:07:53  guru
 * back to
 * 		      slave_load = (अच_दीर्घ_उच्च - (अच_दीर्घ_उच्च / 2)) -
 * 			(priority_Bps) + bytes_queued;
 *
 * Revision 3.9  1995/01/19  22:38:20  guru
 * 		      slave_load = (अच_दीर्घ_उच्च - (अच_दीर्घ_उच्च / 2)) -
 * 			(priority_Bps) + bytes_queued * 4;
 *
 * Revision 3.8  1995/01/19  22:30:55  guru
 *       slave_load = (अच_दीर्घ_उच्च - (अच_दीर्घ_उच्च / 2)) -
 * 			(priority_Bps) + bytes_queued * 2;
 *
 * Revision 3.7  1995/01/19  21:52:35  guru
 * prपूर्णांकk's trimmed out.
 *
 * Revision 3.6  1995/01/19  21:49:56  guru
 * This is working pretty well. I gained 1 K/s in speed.. now it's just
 * robustness and prपूर्णांकk's to be diked out.
 *
 * Revision 3.5  1995/01/18  22:29:59  guru
 * still crashes the kernel when the lock_रुको thing is woken up.
 *
 * Revision 3.4  1995/01/18  21:59:47  guru
 * Broken set-bit locking snapshot
 *
 * Revision 3.3  1995/01/17  22:09:18  guru
 * infinite sleep in a lock somewhere..
 *
 * Revision 3.2  1995/01/15  16:46:06  guru
 * Log trimmed of non-pertinent 1.x branch messages
 *
 * Revision 3.1  1995/01/15  14:41:45  guru
 * New Scheduler and समयr stuff...
 *
 * Revision 1.15  1995/01/15  14:29:02  guru
 * Will make 1.14 (now 1.15) the 3.0 branch, and the 1.12 the 2.0 branch, the one
 * with the dumber scheduler
 *
 * Revision 1.14  1995/01/15  02:37:08  guru
 * shock.. the kept-new-versions could have zonked working
 * stuff.. shudder
 *
 * Revision 1.13  1995/01/15  02:36:31  guru
 * big changes
 *
 * 	scheduler was torn out and replaced with something smarter
 *
 * 	global names not prefixed with eql_ were नामd to protect
 * 	against namespace collisions
 *
 * 	a few more असलtract पूर्णांकerfaces were added to facilitate any
 * 	potential change of dataकाष्ठाure.  the driver is still using
 * 	a linked list of slaves.  going to a heap would be a bit of
 * 	an overसमाप्त.
 *
 * 	this compiles fine with no warnings.
 *
 * 	the locking mechanism and समयr stuff must be written however,
 * 	this version will not work otherwise
 *
 * Sorry, I had to reग_लिखो most of this क्रम 2.5.x -DaveM
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/netdevice.h>
#समावेश <net/net_namespace.h>

#समावेश <linux/अगर.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_eql.h>
#समावेश <linux/pkt_sched.h>

#समावेश <linux/uaccess.h>

अटल पूर्णांक eql_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक eql_बंद(काष्ठा net_device *dev);
अटल पूर्णांक eql_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
अटल netdev_tx_t eql_slave_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

#घोषणा eql_is_slave(dev)	((dev->flags & IFF_SLAVE) == IFF_SLAVE)
#घोषणा eql_is_master(dev)	((dev->flags & IFF_MASTER) == IFF_MASTER)

अटल व्योम eql_समाप्त_one_slave(slave_queue_t *queue, slave_t *slave);

अटल व्योम eql_समयr(काष्ठा समयr_list *t)
अणु
	equalizer_t *eql = from_समयr(eql, t, समयr);
	काष्ठा list_head *this, *पंचांगp, *head;

	spin_lock(&eql->queue.lock);
	head = &eql->queue.all_slaves;
	list_क्रम_each_safe(this, पंचांगp, head) अणु
		slave_t *slave = list_entry(this, slave_t, list);

		अगर ((slave->dev->flags & IFF_UP) == IFF_UP) अणु
			slave->bytes_queued -= slave->priority_Bps;
			अगर (slave->bytes_queued < 0)
				slave->bytes_queued = 0;
		पूर्ण अन्यथा अणु
			eql_समाप्त_one_slave(&eql->queue, slave);
		पूर्ण

	पूर्ण
	spin_unlock(&eql->queue.lock);

	eql->समयr.expires = jअगरfies + EQL_DEFAULT_RESCHED_IVAL;
	add_समयr(&eql->समयr);
पूर्ण

अटल स्थिर अक्षर version[] __initस्थिर =
	"Equalizer2002: Simon Janes (simon@ncm.com) and David S. Miller (davem@redhat.com)";

अटल स्थिर काष्ठा net_device_ops eql_netdev_ops = अणु
	.nकरो_खोलो	= eql_खोलो,
	.nकरो_stop	= eql_बंद,
	.nकरो_करो_ioctl	= eql_ioctl,
	.nकरो_start_xmit	= eql_slave_xmit,
पूर्ण;

अटल व्योम __init eql_setup(काष्ठा net_device *dev)
अणु
	equalizer_t *eql = netdev_priv(dev);

	समयr_setup(&eql->समयr, eql_समयr, 0);
	eql->समयr.expires  	= jअगरfies + EQL_DEFAULT_RESCHED_IVAL;

	spin_lock_init(&eql->queue.lock);
	INIT_LIST_HEAD(&eql->queue.all_slaves);
	eql->queue.master_dev	= dev;

	dev->netdev_ops		= &eql_netdev_ops;

	/*
	 *	Now we unकरो some of the things that eth_setup करोes
	 * 	that we करोn't like
	 */

	dev->mtu        	= EQL_DEFAULT_MTU;	/* set to 576 in अगर_eql.h */
	dev->flags      	= IFF_MASTER;

	dev->type       	= ARPHRD_SLIP;
	dev->tx_queue_len 	= 5;		/* Hands them off fast */
	netअगर_keep_dst(dev);
पूर्ण

अटल पूर्णांक eql_खोलो(काष्ठा net_device *dev)
अणु
	equalizer_t *eql = netdev_priv(dev);

	/* XXX We should क्रमce this off स्वतःmatically क्रम the user. */
	netdev_info(dev,
		    "remember to turn off Van-Jacobson compression on your slave devices\n");

	BUG_ON(!list_empty(&eql->queue.all_slaves));

	eql->min_slaves = 1;
	eql->max_slaves = EQL_DEFAULT_MAX_SLAVES; /* 4 usually... */

	add_समयr(&eql->समयr);

	वापस 0;
पूर्ण

अटल व्योम eql_समाप्त_one_slave(slave_queue_t *queue, slave_t *slave)
अणु
	list_del(&slave->list);
	queue->num_slaves--;
	slave->dev->flags &= ~IFF_SLAVE;
	dev_put(slave->dev);
	kमुक्त(slave);
पूर्ण

अटल व्योम eql_समाप्त_slave_queue(slave_queue_t *queue)
अणु
	काष्ठा list_head *head, *पंचांगp, *this;

	spin_lock_bh(&queue->lock);

	head = &queue->all_slaves;
	list_क्रम_each_safe(this, पंचांगp, head) अणु
		slave_t *s = list_entry(this, slave_t, list);

		eql_समाप्त_one_slave(queue, s);
	पूर्ण

	spin_unlock_bh(&queue->lock);
पूर्ण

अटल पूर्णांक eql_बंद(काष्ठा net_device *dev)
अणु
	equalizer_t *eql = netdev_priv(dev);

	/*
	 *	The समयr has to be stopped first beक्रमe we start hacking away
	 *	at the data काष्ठाure it scans every so often...
	 */

	del_समयr_sync(&eql->समयr);

	eql_समाप्त_slave_queue(&eql->queue);

	वापस 0;
पूर्ण

अटल पूर्णांक eql_enslave(काष्ठा net_device *dev,  slaving_request_t __user *srq);
अटल पूर्णांक eql_emancipate(काष्ठा net_device *dev, slaving_request_t __user *srq);

अटल पूर्णांक eql_g_slave_cfg(काष्ठा net_device *dev, slave_config_t __user *sc);
अटल पूर्णांक eql_s_slave_cfg(काष्ठा net_device *dev, slave_config_t __user *sc);

अटल पूर्णांक eql_g_master_cfg(काष्ठा net_device *dev, master_config_t __user *mc);
अटल पूर्णांक eql_s_master_cfg(काष्ठा net_device *dev, master_config_t __user *mc);

अटल पूर्णांक eql_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	अगर (cmd != EQL_GETMASTRCFG && cmd != EQL_GETSLAVECFG &&
	    !capable(CAP_NET_ADMIN))
	  	वापस -EPERM;

	चयन (cmd) अणु
		हाल EQL_ENSLAVE:
			वापस eql_enslave(dev, अगरr->अगरr_data);
		हाल EQL_EMANCIPATE:
			वापस eql_emancipate(dev, अगरr->अगरr_data);
		हाल EQL_GETSLAVECFG:
			वापस eql_g_slave_cfg(dev, अगरr->अगरr_data);
		हाल EQL_SETSLAVECFG:
			वापस eql_s_slave_cfg(dev, अगरr->अगरr_data);
		हाल EQL_GETMASTRCFG:
			वापस eql_g_master_cfg(dev, अगरr->अगरr_data);
		हाल EQL_SETMASTRCFG:
			वापस eql_s_master_cfg(dev, अगरr->अगरr_data);
		शेष:
			वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/* queue->lock must be held */
अटल slave_t *__eql_schedule_slaves(slave_queue_t *queue)
अणु
	अचिन्हित दीर्घ best_load = ~0UL;
	काष्ठा list_head *this, *पंचांगp, *head;
	slave_t *best_slave;

	best_slave = शून्य;

	/* Make a pass to set the best slave. */
	head = &queue->all_slaves;
	list_क्रम_each_safe(this, पंचांगp, head) अणु
		slave_t *slave = list_entry(this, slave_t, list);
		अचिन्हित दीर्घ slave_load, bytes_queued, priority_Bps;

		/* Go through the slave list once, updating best_slave
		 * whenever a new best_load is found.
		 */
		bytes_queued = slave->bytes_queued;
		priority_Bps = slave->priority_Bps;
		अगर ((slave->dev->flags & IFF_UP) == IFF_UP) अणु
			slave_load = (~0UL - (~0UL / 2)) -
				(priority_Bps) + bytes_queued * 8;

			अगर (slave_load < best_load) अणु
				best_load = slave_load;
				best_slave = slave;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* We found a dead slave, समाप्त it. */
			eql_समाप्त_one_slave(queue, slave);
		पूर्ण
	पूर्ण
	वापस best_slave;
पूर्ण

अटल netdev_tx_t eql_slave_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	equalizer_t *eql = netdev_priv(dev);
	slave_t *slave;

	spin_lock(&eql->queue.lock);

	slave = __eql_schedule_slaves(&eql->queue);
	अगर (slave) अणु
		काष्ठा net_device *slave_dev = slave->dev;

		skb->dev = slave_dev;
		skb->priority = TC_PRIO_FILLER;
		slave->bytes_queued += skb->len;
		dev_queue_xmit(skb);
		dev->stats.tx_packets++;
	पूर्ण अन्यथा अणु
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb(skb);
	पूर्ण

	spin_unlock(&eql->queue.lock);

	वापस NETDEV_TX_OK;
पूर्ण

/*
 *	Private ioctl functions
 */

/* queue->lock must be held */
अटल slave_t *__eql_find_slave_dev(slave_queue_t *queue, काष्ठा net_device *dev)
अणु
	काष्ठा list_head *this, *head;

	head = &queue->all_slaves;
	list_क्रम_each(this, head) अणु
		slave_t *slave = list_entry(this, slave_t, list);

		अगर (slave->dev == dev)
			वापस slave;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक eql_is_full(slave_queue_t *queue)
अणु
	equalizer_t *eql = netdev_priv(queue->master_dev);

	अगर (queue->num_slaves >= eql->max_slaves)
		वापस 1;
	वापस 0;
पूर्ण

/* queue->lock must be held */
अटल पूर्णांक __eql_insert_slave(slave_queue_t *queue, slave_t *slave)
अणु
	अगर (!eql_is_full(queue)) अणु
		slave_t *duplicate_slave = शून्य;

		duplicate_slave = __eql_find_slave_dev(queue, slave->dev);
		अगर (duplicate_slave)
			eql_समाप्त_one_slave(queue, duplicate_slave);

		dev_hold(slave->dev);
		list_add(&slave->list, &queue->all_slaves);
		queue->num_slaves++;
		slave->dev->flags |= IFF_SLAVE;

		वापस 0;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक eql_enslave(काष्ठा net_device *master_dev, slaving_request_t __user *srqp)
अणु
	काष्ठा net_device *slave_dev;
	slaving_request_t srq;

	अगर (copy_from_user(&srq, srqp, माप (slaving_request_t)))
		वापस -EFAULT;

	slave_dev = __dev_get_by_name(&init_net, srq.slave_name);
	अगर (!slave_dev)
		वापस -ENODEV;

	अगर ((master_dev->flags & IFF_UP) == IFF_UP) अणु
		/* slave is not a master & not alपढ़ोy a slave: */
		अगर (!eql_is_master(slave_dev) && !eql_is_slave(slave_dev)) अणु
			slave_t *s = kदो_स्मृति(माप(*s), GFP_KERNEL);
			equalizer_t *eql = netdev_priv(master_dev);
			पूर्णांक ret;

			अगर (!s)
				वापस -ENOMEM;

			स_रखो(s, 0, माप(*s));
			s->dev = slave_dev;
			s->priority = srq.priority;
			s->priority_bps = srq.priority;
			s->priority_Bps = srq.priority / 8;

			spin_lock_bh(&eql->queue.lock);
			ret = __eql_insert_slave(&eql->queue, s);
			अगर (ret)
				kमुक्त(s);

			spin_unlock_bh(&eql->queue.lock);

			वापस ret;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक eql_emancipate(काष्ठा net_device *master_dev, slaving_request_t __user *srqp)
अणु
	equalizer_t *eql = netdev_priv(master_dev);
	काष्ठा net_device *slave_dev;
	slaving_request_t srq;
	पूर्णांक ret;

	अगर (copy_from_user(&srq, srqp, माप (slaving_request_t)))
		वापस -EFAULT;

	slave_dev = __dev_get_by_name(&init_net, srq.slave_name);
	अगर (!slave_dev)
		वापस -ENODEV;

	ret = -EINVAL;
	spin_lock_bh(&eql->queue.lock);
	अगर (eql_is_slave(slave_dev)) अणु
		slave_t *slave = __eql_find_slave_dev(&eql->queue, slave_dev);
		अगर (slave) अणु
			eql_समाप्त_one_slave(&eql->queue, slave);
			ret = 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&eql->queue.lock);

	वापस ret;
पूर्ण

अटल पूर्णांक eql_g_slave_cfg(काष्ठा net_device *dev, slave_config_t __user *scp)
अणु
	equalizer_t *eql = netdev_priv(dev);
	slave_t *slave;
	काष्ठा net_device *slave_dev;
	slave_config_t sc;
	पूर्णांक ret;

	अगर (copy_from_user(&sc, scp, माप (slave_config_t)))
		वापस -EFAULT;

	slave_dev = __dev_get_by_name(&init_net, sc.slave_name);
	अगर (!slave_dev)
		वापस -ENODEV;

	ret = -EINVAL;

	spin_lock_bh(&eql->queue.lock);
	अगर (eql_is_slave(slave_dev)) अणु
		slave = __eql_find_slave_dev(&eql->queue, slave_dev);
		अगर (slave) अणु
			sc.priority = slave->priority;
			ret = 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&eql->queue.lock);

	अगर (!ret && copy_to_user(scp, &sc, माप (slave_config_t)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक eql_s_slave_cfg(काष्ठा net_device *dev, slave_config_t __user *scp)
अणु
	slave_t *slave;
	equalizer_t *eql;
	काष्ठा net_device *slave_dev;
	slave_config_t sc;
	पूर्णांक ret;

	अगर (copy_from_user(&sc, scp, माप (slave_config_t)))
		वापस -EFAULT;

	slave_dev = __dev_get_by_name(&init_net, sc.slave_name);
	अगर (!slave_dev)
		वापस -ENODEV;

	ret = -EINVAL;

	eql = netdev_priv(dev);
	spin_lock_bh(&eql->queue.lock);
	अगर (eql_is_slave(slave_dev)) अणु
		slave = __eql_find_slave_dev(&eql->queue, slave_dev);
		अगर (slave) अणु
			slave->priority = sc.priority;
			slave->priority_bps = sc.priority;
			slave->priority_Bps = sc.priority / 8;
			ret = 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&eql->queue.lock);

	वापस ret;
पूर्ण

अटल पूर्णांक eql_g_master_cfg(काष्ठा net_device *dev, master_config_t __user *mcp)
अणु
	equalizer_t *eql;
	master_config_t mc;

	स_रखो(&mc, 0, माप(master_config_t));

	अगर (eql_is_master(dev)) अणु
		eql = netdev_priv(dev);
		mc.max_slaves = eql->max_slaves;
		mc.min_slaves = eql->min_slaves;
		अगर (copy_to_user(mcp, &mc, माप (master_config_t)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक eql_s_master_cfg(काष्ठा net_device *dev, master_config_t __user *mcp)
अणु
	equalizer_t *eql;
	master_config_t mc;

	अगर (copy_from_user(&mc, mcp, माप (master_config_t)))
		वापस -EFAULT;

	अगर (eql_is_master(dev)) अणु
		eql = netdev_priv(dev);
		eql->max_slaves = mc.max_slaves;
		eql->min_slaves = mc.min_slaves;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल काष्ठा net_device *dev_eql;

अटल पूर्णांक __init eql_init_module(व्योम)
अणु
	पूर्णांक err;

	pr_info("%s\n", version);

	dev_eql = alloc_netdev(माप(equalizer_t), "eql", NET_NAME_UNKNOWN,
			       eql_setup);
	अगर (!dev_eql)
		वापस -ENOMEM;

	err = रेजिस्टर_netdev(dev_eql);
	अगर (err)
		मुक्त_netdev(dev_eql);
	वापस err;
पूर्ण

अटल व्योम __निकास eql_cleanup_module(व्योम)
अणु
	unरेजिस्टर_netdev(dev_eql);
	मुक्त_netdev(dev_eql);
पूर्ण

module_init(eql_init_module);
module_निकास(eql_cleanup_module);
MODULE_LICENSE("GPL");

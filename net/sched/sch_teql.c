<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* net/sched/sch_teql.c	"True" (or "trivial") link equalizer.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/moduleparam.h>
#समावेश <net/dst.h>
#समावेश <net/neighbour.h>
#समावेश <net/pkt_sched.h>

/*
   How to setup it.
   ----------------

   After loading this module you will find a new device teqlN
   and new qdisc with the same name. To join a slave to the equalizer
   you should just set this qdisc on a device f.e.

   # tc qdisc add dev eth0 root teql0
   # tc qdisc add dev eth1 root teql0

   That's all. Full PnP 8)

   Applicability.
   --------------

   1. Slave devices MUST be active devices, i.e., they must उठाओ the tbusy
      संकेत and generate EOI events. If you want to equalize भव devices
      like tunnels, use a normal eql device.
   2. This device माला_दो no limitations on physical slave अक्षरacteristics
      f.e. it will equalize 9600baud line and 100Mb ethernet perfectly :-)
      Certainly, large dअगरference in link speeds will make the resulting
      eqalized link unusable, because of huge packet reordering.
      I estimate an upper useful dअगरference as ~10 बार.
   3. If the slave requires address resolution, only protocols using
      neighbour cache (IPv4/IPv6) will work over the equalized link.
      Other protocols are still allowed to use the slave device directly,
      which will not अवरोध load balancing, though native slave
      traffic will have the highest priority.  */

काष्ठा teql_master अणु
	काष्ठा Qdisc_ops qops;
	काष्ठा net_device *dev;
	काष्ठा Qdisc *slaves;
	काष्ठा list_head master_list;
	अचिन्हित दीर्घ	tx_bytes;
	अचिन्हित दीर्घ	tx_packets;
	अचिन्हित दीर्घ	tx_errors;
	अचिन्हित दीर्घ	tx_dropped;
पूर्ण;

काष्ठा teql_sched_data अणु
	काष्ठा Qdisc *next;
	काष्ठा teql_master *m;
	काष्ठा sk_buff_head q;
पूर्ण;

#घोषणा NEXT_SLAVE(q) (((काष्ठा teql_sched_data *)qdisc_priv(q))->next)

#घोषणा FMASK (IFF_BROADCAST | IFF_POINTOPOINT)

/* "teql*" qdisc routines */

अटल पूर्णांक
teql_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch, काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा teql_sched_data *q = qdisc_priv(sch);

	अगर (q->q.qlen < dev->tx_queue_len) अणु
		__skb_queue_tail(&q->q, skb);
		वापस NET_XMIT_SUCCESS;
	पूर्ण

	वापस qdisc_drop(skb, sch, to_मुक्त);
पूर्ण

अटल काष्ठा sk_buff *
teql_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा teql_sched_data *dat = qdisc_priv(sch);
	काष्ठा netdev_queue *dat_queue;
	काष्ठा sk_buff *skb;
	काष्ठा Qdisc *q;

	skb = __skb_dequeue(&dat->q);
	dat_queue = netdev_get_tx_queue(dat->m->dev, 0);
	q = rcu_dereference_bh(dat_queue->qdisc);

	अगर (skb == शून्य) अणु
		काष्ठा net_device *m = qdisc_dev(q);
		अगर (m) अणु
			dat->m->slaves = sch;
			netअगर_wake_queue(m);
		पूर्ण
	पूर्ण अन्यथा अणु
		qdisc_bstats_update(sch, skb);
	पूर्ण
	sch->q.qlen = dat->q.qlen + q->q.qlen;
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
teql_peek(काष्ठा Qdisc *sch)
अणु
	/* teql is meant to be used as root qdisc */
	वापस शून्य;
पूर्ण

अटल व्योम
teql_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा teql_sched_data *dat = qdisc_priv(sch);

	skb_queue_purge(&dat->q);
	sch->q.qlen = 0;
पूर्ण

अटल व्योम
teql_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा Qdisc *q, *prev;
	काष्ठा teql_sched_data *dat = qdisc_priv(sch);
	काष्ठा teql_master *master = dat->m;

	अगर (!master)
		वापस;

	prev = master->slaves;
	अगर (prev) अणु
		करो अणु
			q = NEXT_SLAVE(prev);
			अगर (q == sch) अणु
				NEXT_SLAVE(prev) = NEXT_SLAVE(q);
				अगर (q == master->slaves) अणु
					master->slaves = NEXT_SLAVE(q);
					अगर (q == master->slaves) अणु
						काष्ठा netdev_queue *txq;
						spinlock_t *root_lock;

						txq = netdev_get_tx_queue(master->dev, 0);
						master->slaves = शून्य;

						root_lock = qdisc_root_sleeping_lock(rtnl_dereference(txq->qdisc));
						spin_lock_bh(root_lock);
						qdisc_reset(rtnl_dereference(txq->qdisc));
						spin_unlock_bh(root_lock);
					पूर्ण
				पूर्ण
				skb_queue_purge(&dat->q);
				अवरोध;
			पूर्ण

		पूर्ण जबतक ((prev = q) != master->slaves);
	पूर्ण
पूर्ण

अटल पूर्णांक teql_qdisc_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा teql_master *m = (काष्ठा teql_master *)sch->ops;
	काष्ठा teql_sched_data *q = qdisc_priv(sch);

	अगर (dev->hard_header_len > m->dev->hard_header_len)
		वापस -EINVAL;

	अगर (m->dev == dev)
		वापस -ELOOP;

	q->m = m;

	skb_queue_head_init(&q->q);

	अगर (m->slaves) अणु
		अगर (m->dev->flags & IFF_UP) अणु
			अगर ((m->dev->flags & IFF_POINTOPOINT &&
			     !(dev->flags & IFF_POINTOPOINT)) ||
			    (m->dev->flags & IFF_BROADCAST &&
			     !(dev->flags & IFF_BROADCAST)) ||
			    (m->dev->flags & IFF_MULTICAST &&
			     !(dev->flags & IFF_MULTICAST)) ||
			    dev->mtu < m->dev->mtu)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (!(dev->flags&IFF_POINTOPOINT))
				m->dev->flags &= ~IFF_POINTOPOINT;
			अगर (!(dev->flags&IFF_BROADCAST))
				m->dev->flags &= ~IFF_BROADCAST;
			अगर (!(dev->flags&IFF_MULTICAST))
				m->dev->flags &= ~IFF_MULTICAST;
			अगर (dev->mtu < m->dev->mtu)
				m->dev->mtu = dev->mtu;
		पूर्ण
		q->next = NEXT_SLAVE(m->slaves);
		NEXT_SLAVE(m->slaves) = sch;
	पूर्ण अन्यथा अणु
		q->next = sch;
		m->slaves = sch;
		m->dev->mtu = dev->mtu;
		m->dev->flags = (m->dev->flags&~FMASK)|(dev->flags&FMASK);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक
__teql_resolve(काष्ठा sk_buff *skb, काष्ठा sk_buff *skb_res,
	       काष्ठा net_device *dev, काष्ठा netdev_queue *txq,
	       काष्ठा dst_entry *dst)
अणु
	काष्ठा neighbour *n;
	पूर्णांक err = 0;

	n = dst_neigh_lookup_skb(dst, skb);
	अगर (!n)
		वापस -ENOENT;

	अगर (dst->dev != dev) अणु
		काष्ठा neighbour *mn;

		mn = __neigh_lookup_त्रुटि_सं(n->tbl, n->primary_key, dev);
		neigh_release(n);
		अगर (IS_ERR(mn))
			वापस PTR_ERR(mn);
		n = mn;
	पूर्ण

	अगर (neigh_event_send(n, skb_res) == 0) अणु
		पूर्णांक err;
		अक्षर haddr[MAX_ADDR_LEN];

		neigh_ha_snapshot(haddr, n, dev);
		err = dev_hard_header(skb, dev, ntohs(skb_protocol(skb, false)),
				      haddr, शून्य, skb->len);

		अगर (err < 0)
			err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = (skb_res == शून्य) ? -EAGAIN : 1;
	पूर्ण
	neigh_release(n);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक teql_resolve(काष्ठा sk_buff *skb,
			       काष्ठा sk_buff *skb_res,
			       काष्ठा net_device *dev,
			       काष्ठा netdev_queue *txq)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	पूर्णांक res;

	अगर (rcu_access_poपूर्णांकer(txq->qdisc) == &noop_qdisc)
		वापस -ENODEV;

	अगर (!dev->header_ops || !dst)
		वापस 0;

	rcu_पढ़ो_lock();
	res = __teql_resolve(skb, skb_res, dev, txq, dst);
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण

अटल netdev_tx_t teql_master_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा teql_master *master = netdev_priv(dev);
	काष्ठा Qdisc *start, *q;
	पूर्णांक busy;
	पूर्णांक nores;
	पूर्णांक subq = skb_get_queue_mapping(skb);
	काष्ठा sk_buff *skb_res = शून्य;

	start = master->slaves;

restart:
	nores = 0;
	busy = 0;

	q = start;
	अगर (!q)
		जाओ drop;

	करो अणु
		काष्ठा net_device *slave = qdisc_dev(q);
		काष्ठा netdev_queue *slave_txq = netdev_get_tx_queue(slave, 0);

		अगर (slave_txq->qdisc_sleeping != q)
			जारी;
		अगर (netअगर_xmit_stopped(netdev_get_tx_queue(slave, subq)) ||
		    !netअगर_running(slave)) अणु
			busy = 1;
			जारी;
		पूर्ण

		चयन (teql_resolve(skb, skb_res, slave, slave_txq)) अणु
		हाल 0:
			अगर (__netअगर_tx_trylock(slave_txq)) अणु
				अचिन्हित पूर्णांक length = qdisc_pkt_len(skb);

				अगर (!netअगर_xmit_frozen_or_stopped(slave_txq) &&
				    netdev_start_xmit(skb, slave, slave_txq, false) ==
				    NETDEV_TX_OK) अणु
					__netअगर_tx_unlock(slave_txq);
					master->slaves = NEXT_SLAVE(q);
					netअगर_wake_queue(dev);
					master->tx_packets++;
					master->tx_bytes += length;
					वापस NETDEV_TX_OK;
				पूर्ण
				__netअगर_tx_unlock(slave_txq);
			पूर्ण
			अगर (netअगर_xmit_stopped(netdev_get_tx_queue(dev, 0)))
				busy = 1;
			अवरोध;
		हाल 1:
			master->slaves = NEXT_SLAVE(q);
			वापस NETDEV_TX_OK;
		शेष:
			nores = 1;
			अवरोध;
		पूर्ण
		__skb_pull(skb, skb_network_offset(skb));
	पूर्ण जबतक ((q = NEXT_SLAVE(q)) != start);

	अगर (nores && skb_res == शून्य) अणु
		skb_res = skb;
		जाओ restart;
	पूर्ण

	अगर (busy) अणु
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण
	master->tx_errors++;

drop:
	master->tx_dropped++;
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक teql_master_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा Qdisc *q;
	काष्ठा teql_master *m = netdev_priv(dev);
	पूर्णांक mtu = 0xFFFE;
	अचिन्हित पूर्णांक flags = IFF_NOARP | IFF_MULTICAST;

	अगर (m->slaves == शून्य)
		वापस -EUNATCH;

	flags = FMASK;

	q = m->slaves;
	करो अणु
		काष्ठा net_device *slave = qdisc_dev(q);

		अगर (slave == शून्य)
			वापस -EUNATCH;

		अगर (slave->mtu < mtu)
			mtu = slave->mtu;
		अगर (slave->hard_header_len > LL_MAX_HEADER)
			वापस -EINVAL;

		/* If all the slaves are BROADCAST, master is BROADCAST
		   If all the slaves are PtP, master is PtP
		   Otherwise, master is NBMA.
		 */
		अगर (!(slave->flags&IFF_POINTOPOINT))
			flags &= ~IFF_POINTOPOINT;
		अगर (!(slave->flags&IFF_BROADCAST))
			flags &= ~IFF_BROADCAST;
		अगर (!(slave->flags&IFF_MULTICAST))
			flags &= ~IFF_MULTICAST;
	पूर्ण जबतक ((q = NEXT_SLAVE(q)) != m->slaves);

	m->dev->mtu = mtu;
	m->dev->flags = (m->dev->flags&~FMASK) | flags;
	netअगर_start_queue(m->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक teql_master_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

अटल व्योम teql_master_stats64(काष्ठा net_device *dev,
				काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा teql_master *m = netdev_priv(dev);

	stats->tx_packets	= m->tx_packets;
	stats->tx_bytes		= m->tx_bytes;
	stats->tx_errors	= m->tx_errors;
	stats->tx_dropped	= m->tx_dropped;
पूर्ण

अटल पूर्णांक teql_master_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा teql_master *m = netdev_priv(dev);
	काष्ठा Qdisc *q;

	q = m->slaves;
	अगर (q) अणु
		करो अणु
			अगर (new_mtu > qdisc_dev(q)->mtu)
				वापस -EINVAL;
		पूर्ण जबतक ((q = NEXT_SLAVE(q)) != m->slaves);
	पूर्ण

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops teql_netdev_ops = अणु
	.nकरो_खोलो	= teql_master_खोलो,
	.nकरो_stop	= teql_master_बंद,
	.nकरो_start_xmit	= teql_master_xmit,
	.nकरो_get_stats64 = teql_master_stats64,
	.nकरो_change_mtu	= teql_master_mtu,
पूर्ण;

अटल __init व्योम teql_master_setup(काष्ठा net_device *dev)
अणु
	काष्ठा teql_master *master = netdev_priv(dev);
	काष्ठा Qdisc_ops *ops = &master->qops;

	master->dev	= dev;
	ops->priv_size  = माप(काष्ठा teql_sched_data);

	ops->enqueue	=	teql_enqueue;
	ops->dequeue	=	teql_dequeue;
	ops->peek	=	teql_peek;
	ops->init	=	teql_qdisc_init;
	ops->reset	=	teql_reset;
	ops->destroy	=	teql_destroy;
	ops->owner	=	THIS_MODULE;

	dev->netdev_ops =       &teql_netdev_ops;
	dev->type		= ARPHRD_VOID;
	dev->mtu		= 1500;
	dev->min_mtu		= 68;
	dev->max_mtu		= 65535;
	dev->tx_queue_len	= 100;
	dev->flags		= IFF_NOARP;
	dev->hard_header_len	= LL_MAX_HEADER;
	netअगर_keep_dst(dev);
पूर्ण

अटल LIST_HEAD(master_dev_list);
अटल पूर्णांक max_equalizers = 1;
module_param(max_equalizers, पूर्णांक, 0);
MODULE_PARM_DESC(max_equalizers, "Max number of link equalizers");

अटल पूर्णांक __init teql_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक err = -ENODEV;

	क्रम (i = 0; i < max_equalizers; i++) अणु
		काष्ठा net_device *dev;
		काष्ठा teql_master *master;

		dev = alloc_netdev(माप(काष्ठा teql_master), "teql%d",
				   NET_NAME_UNKNOWN, teql_master_setup);
		अगर (!dev) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		अगर ((err = रेजिस्टर_netdev(dev))) अणु
			मुक्त_netdev(dev);
			अवरोध;
		पूर्ण

		master = netdev_priv(dev);

		strlcpy(master->qops.id, dev->name, IFNAMSIZ);
		err = रेजिस्टर_qdisc(&master->qops);

		अगर (err) अणु
			unरेजिस्टर_netdev(dev);
			मुक्त_netdev(dev);
			अवरोध;
		पूर्ण

		list_add_tail(&master->master_list, &master_dev_list);
	पूर्ण
	वापस i ? 0 : err;
पूर्ण

अटल व्योम __निकास teql_निकास(व्योम)
अणु
	काष्ठा teql_master *master, *nxt;

	list_क्रम_each_entry_safe(master, nxt, &master_dev_list, master_list) अणु

		list_del(&master->master_list);

		unरेजिस्टर_qdisc(&master->qops);
		unरेजिस्टर_netdev(master->dev);
		मुक्त_netdev(master->dev);
	पूर्ण
पूर्ण

module_init(teql_init);
module_निकास(teql_निकास);

MODULE_LICENSE("GPL");

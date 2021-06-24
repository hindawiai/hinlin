<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	G8BPQ compatible "AX.25 via ethernet" driver release 004
 *
 *	This code REQUIRES 2.0.0 or higher/ NET3.029
 *
 *	This is a "pseudo" network driver to allow AX.25 over Ethernet
 *	using G8BPQ encapsulation. It has been extracted from the protocol
 *	implementation because
 *
 *		- things got unपढ़ोable within the protocol stack
 *		- to cure the protocol stack from "feature-ism"
 *		- a protocol implementation shouldn't need to know on
 *		  which hardware it is running
 *		- user-level programs like the AX.25 utilities shouldn't
 *		  need to know about the hardware.
 *		- IP over ethernet encapsulated AX.25 was impossible
 *		- rxecho.c did not work
 *		- to have room क्रम extensions
 *		- it just deserves to "live" as an own driver
 *
 *	This driver can use any ethernet destination address, and can be
 *	limited to accept frames from one dedicated ethernet card only.
 *
 *	Note that the driver sets up the BPQ devices स्वतःmagically on
 *	startup or (अगर started beक्रमe the "insmod" of an ethernet device)
 *	on "ifconfig up". It hopefully will हटाओ the BPQ on "rmmod"ing
 *	the ethernet device (in fact: as soon as another ethernet or bpq
 *	device माला_लो "ifconfig"ured).
 *
 *	I have heard that several people are thinking of experiments
 *	with highspeed packet radio using existing ethernet cards.
 *	Well, this driver is prepared क्रम this purpose, just add
 *	your tx key control and a txdelay / tailसमय algorithm,
 *	probably some buffering, and /voila/...
 *
 *	History
 *	BPQ   001	Joerg(DL1BKE)		Extracted BPQ code from AX.25
 *						protocol stack and added my own
 *						yet existing patches
 *	BPQ   002	Joerg(DL1BKE)		Scan network device list on
 *						startup.
 *	BPQ   003	Joerg(DL1BKE)		Ethernet destination address
 *						and accepted source address
 *						can be configured by an ioctl()
 *						call.
 *						Fixed to match Linux networking
 *						changes - 2.1.15.
 *	BPQ   004	Joerg(DL1BKE)		Fixed to not lock up on अगरconfig.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/rtnetlink.h>

#समावेश <net/ip.h>
#समावेश <net/arp.h>
#समावेश <net/net_namespace.h>

#समावेश <linux/bpqether.h>

अटल स्थिर अक्षर banner[] __initस्थिर = KERN_INFO \
	"AX.25: bpqether driver version 004\n";

अटल पूर्णांक bpq_rcv(काष्ठा sk_buff *, काष्ठा net_device *, काष्ठा packet_type *, काष्ठा net_device *);
अटल पूर्णांक bpq_device_event(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);

अटल काष्ठा packet_type bpq_packet_type __पढ़ो_mostly = अणु
	.type	= cpu_to_be16(ETH_P_BPQ),
	.func	= bpq_rcv,
पूर्ण;

अटल काष्ठा notअगरier_block bpq_dev_notअगरier = अणु
	.notअगरier_call = bpq_device_event,
पूर्ण;


काष्ठा bpqdev अणु
	काष्ठा list_head bpq_list;	/* list of bpq devices chain */
	काष्ठा net_device *ethdev;	/* link to ethernet device */
	काष्ठा net_device *axdev;	/* bpq device (bpq#) */
	अक्षर   dest_addr[6];		/* ether destination address */
	अक्षर   acpt_addr[6];		/* accept ether frames from this address only */
पूर्ण;

अटल LIST_HEAD(bpq_devices);

/*
 * bpqether network devices are paired with ethernet devices below them, so
 * क्रमm a special "super class" of normal ethernet devices; split their locks
 * off पूर्णांकo a separate class since they always nest.
 */
अटल काष्ठा lock_class_key bpq_netdev_xmit_lock_key;
अटल काष्ठा lock_class_key bpq_netdev_addr_lock_key;

अटल व्योम bpq_set_lockdep_class_one(काष्ठा net_device *dev,
				      काष्ठा netdev_queue *txq,
				      व्योम *_unused)
अणु
	lockdep_set_class(&txq->_xmit_lock, &bpq_netdev_xmit_lock_key);
पूर्ण

अटल व्योम bpq_set_lockdep_class(काष्ठा net_device *dev)
अणु
	lockdep_set_class(&dev->addr_list_lock, &bpq_netdev_addr_lock_key);
	netdev_क्रम_each_tx_queue(dev, bpq_set_lockdep_class_one, शून्य);
पूर्ण

/* ------------------------------------------------------------------------ */


/*
 *	Get the ethernet device क्रम a BPQ device
 */
अटल अंतरभूत काष्ठा net_device *bpq_get_ether_dev(काष्ठा net_device *dev)
अणु
	काष्ठा bpqdev *bpq = netdev_priv(dev);

	वापस bpq ? bpq->ethdev : शून्य;
पूर्ण

/*
 *	Get the BPQ device क्रम the ethernet device
 */
अटल अंतरभूत काष्ठा net_device *bpq_get_ax25_dev(काष्ठा net_device *dev)
अणु
	काष्ठा bpqdev *bpq;

	list_क्रम_each_entry_rcu(bpq, &bpq_devices, bpq_list,
				lockdep_rtnl_is_held()) अणु
		अगर (bpq->ethdev == dev)
			वापस bpq->axdev;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक dev_is_ethdev(काष्ठा net_device *dev)
अणु
	वापस dev->type == ARPHRD_ETHER && म_भेदन(dev->name, "dummy", 5);
पूर्ण

/* ------------------------------------------------------------------------ */


/*
 *	Receive an AX.25 frame via an ethernet पूर्णांकerface.
 */
अटल पूर्णांक bpq_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *ptype, काष्ठा net_device *orig_dev)
अणु
	पूर्णांक len;
	अक्षर * ptr;
	काष्ठा ethhdr *eth;
	काष्ठा bpqdev *bpq;

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ drop;

	अगर ((skb = skb_share_check(skb, GFP_ATOMIC)) == शून्य)
		वापस NET_RX_DROP;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ethhdr)))
		जाओ drop;

	rcu_पढ़ो_lock();
	dev = bpq_get_ax25_dev(dev);

	अगर (dev == शून्य || !netअगर_running(dev)) 
		जाओ drop_unlock;

	/*
	 * अगर we want to accept frames from just one ethernet device
	 * we check the source address of the sender.
	 */

	bpq = netdev_priv(dev);

	eth = eth_hdr(skb);

	अगर (!(bpq->acpt_addr[0] & 0x01) &&
	    !ether_addr_equal(eth->h_source, bpq->acpt_addr))
		जाओ drop_unlock;

	अगर (skb_cow(skb, माप(काष्ठा ethhdr)))
		जाओ drop_unlock;

	len = skb->data[0] + skb->data[1] * 256 - 5;

	skb_pull(skb, 2);	/* Remove the length bytes */
	skb_trim(skb, len);	/* Set the length of the data */

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	ptr = skb_push(skb, 1);
	*ptr = 0;

	skb->protocol = ax25_type_trans(skb, dev);
	netअगर_rx(skb);
unlock:

	rcu_पढ़ो_unlock();

	वापस 0;
drop_unlock:
	kमुक्त_skb(skb);
	जाओ unlock;

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * 	Send an AX.25 frame via an ethernet पूर्णांकerface
 */
अटल netdev_tx_t bpq_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित अक्षर *ptr;
	काष्ठा bpqdev *bpq;
	काष्ठा net_device *orig_dev;
	पूर्णांक size;

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ax25_ip_xmit(skb);

	/*
	 * Just to be *really* sure not to send anything अगर the पूर्णांकerface
	 * is करोwn, the ethernet device may have gone.
	 */
	अगर (!netअगर_running(dev)) अणु
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	skb_pull(skb, 1);			/* Drop KISS byte */
	size = skb->len;

	/*
	 * We're about to mess with the skb which may still shared with the
	 * generic networking code so unshare and ensure it's got enough
	 * space क्रम the BPQ headers.
	 */
	अगर (skb_cow(skb, AX25_BPQ_HEADER_LEN)) अणु
		अगर (net_ratelimit())
			pr_err("bpqether: out of memory\n");
		kमुक्त_skb(skb);

		वापस NETDEV_TX_OK;
	पूर्ण

	ptr = skb_push(skb, 2);			/* Make space क्रम length */

	*ptr++ = (size + 5) % 256;
	*ptr++ = (size + 5) / 256;

	bpq = netdev_priv(dev);

	orig_dev = dev;
	अगर ((dev = bpq_get_ether_dev(dev)) == शून्य) अणु
		orig_dev->stats.tx_dropped++;
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	skb->protocol = ax25_type_trans(skb, dev);
	skb_reset_network_header(skb);
	dev_hard_header(skb, dev, ETH_P_BPQ, bpq->dest_addr, शून्य, 0);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes+=skb->len;
  
	dev_queue_xmit(skb);
	netअगर_wake_queue(dev);
	वापस NETDEV_TX_OK;
पूर्ण

/*
 *	Set AX.25 callsign
 */
अटल पूर्णांक bpq_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
    काष्ठा sockaddr *sa = (काष्ठा sockaddr *)addr;

    स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len);

    वापस 0;
पूर्ण

/*	Ioctl commands
 *
 *		SIOCSBPQETHOPT		reserved क्रम enhancements
 *		SIOCSBPQETHADDR		set the destination and accepted
 *					source ethernet address (broadcast
 *					or multicast: accept all)
 */
अटल पूर्णांक bpq_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा bpq_ethaddr __user *ethaddr = अगरr->अगरr_data;
	काष्ठा bpqdev *bpq = netdev_priv(dev);
	काष्ठा bpq_req req;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
		हाल SIOCSBPQETHOPT:
			अगर (copy_from_user(&req, अगरr->अगरr_data, माप(काष्ठा bpq_req)))
				वापस -EFAULT;
			चयन (req.cmd) अणु
				हाल SIOCGBPQETHPARAM:
				हाल SIOCSBPQETHPARAM:
				शेष:
					वापस -EINVAL;
			पूर्ण

			अवरोध;

		हाल SIOCSBPQETHADDR:
			अगर (copy_from_user(bpq->dest_addr, ethaddr->destination, ETH_ALEN))
				वापस -EFAULT;
			अगर (copy_from_user(bpq->acpt_addr, ethaddr->accept, ETH_ALEN))
				वापस -EFAULT;
			अवरोध;

		शेष:
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * खोलो/बंद a device
 */
अटल पूर्णांक bpq_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक bpq_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण


/* ------------------------------------------------------------------------ */


/*
 *	Proc fileप्रणाली
 */
अटल व्योम *bpq_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	पूर्णांक i = 1;
	काष्ठा bpqdev *bpqdev;

	rcu_पढ़ो_lock();

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;
	
	list_क्रम_each_entry_rcu(bpqdev, &bpq_devices, bpq_list) अणु
		अगर (i == *pos)
			वापस bpqdev;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *bpq_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा list_head *p;
	काष्ठा bpqdev *bpqdev = v;

	++*pos;

	अगर (v == SEQ_START_TOKEN)
		p = rcu_dereference(list_next_rcu(&bpq_devices));
	अन्यथा
		p = rcu_dereference(list_next_rcu(&bpqdev->bpq_list));

	वापस (p == &bpq_devices) ? शून्य 
		: list_entry(p, काष्ठा bpqdev, bpq_list);
पूर्ण

अटल व्योम bpq_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण


अटल पूर्णांक bpq_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, 
			 "dev   ether      destination        accept from\n");
	अन्यथा अणु
		स्थिर काष्ठा bpqdev *bpqdev = v;

		seq_म_लिखो(seq, "%-5s %-10s %pM  ",
			bpqdev->axdev->name, bpqdev->ethdev->name,
			bpqdev->dest_addr);

		अगर (is_multicast_ether_addr(bpqdev->acpt_addr))
			seq_म_लिखो(seq, "*\n");
		अन्यथा
			seq_म_लिखो(seq, "%pM\n", bpqdev->acpt_addr);

	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations bpq_seqops = अणु
	.start = bpq_seq_start,
	.next = bpq_seq_next,
	.stop = bpq_seq_stop,
	.show = bpq_seq_show,
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल स्थिर काष्ठा net_device_ops bpq_netdev_ops = अणु
	.nकरो_खोलो	     = bpq_खोलो,
	.nकरो_stop	     = bpq_बंद,
	.nकरो_start_xmit	     = bpq_xmit,
	.nकरो_set_mac_address = bpq_set_mac_address,
	.nकरो_करो_ioctl	     = bpq_ioctl,
पूर्ण;

अटल व्योम bpq_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops	     = &bpq_netdev_ops;
	dev->needs_मुक्त_netdev = true;

	स_नकल(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	स_नकल(dev->dev_addr,  &ax25_defaddr, AX25_ADDR_LEN);

	dev->flags      = 0;
	dev->features	= NETIF_F_LLTX;	/* Allow recursion */

#अगर IS_ENABLED(CONFIG_AX25)
	dev->header_ops      = &ax25_header_ops;
#पूर्ण_अगर

	dev->type            = ARPHRD_AX25;
	dev->hard_header_len = AX25_MAX_HEADER_LEN + AX25_BPQ_HEADER_LEN;
	dev->mtu             = AX25_DEF_PACLEN;
	dev->addr_len        = AX25_ADDR_LEN;

पूर्ण

/*
 *	Setup a new device.
 */
अटल पूर्णांक bpq_new_device(काष्ठा net_device *edev)
अणु
	पूर्णांक err;
	काष्ठा net_device *ndev;
	काष्ठा bpqdev *bpq;

	ndev = alloc_netdev(माप(काष्ठा bpqdev), "bpq%d", NET_NAME_UNKNOWN,
			    bpq_setup);
	अगर (!ndev)
		वापस -ENOMEM;

		
	bpq = netdev_priv(ndev);
	dev_hold(edev);
	bpq->ethdev = edev;
	bpq->axdev = ndev;

	eth_broadcast_addr(bpq->dest_addr);
	eth_broadcast_addr(bpq->acpt_addr);

	err = रेजिस्टर_netdevice(ndev);
	अगर (err)
		जाओ error;
	bpq_set_lockdep_class(ndev);

	/* List रक्षित by RTNL */
	list_add_rcu(&bpq->bpq_list, &bpq_devices);
	वापस 0;

 error:
	dev_put(edev);
	मुक्त_netdev(ndev);
	वापस err;
	
पूर्ण

अटल व्योम bpq_मुक्त_device(काष्ठा net_device *ndev)
अणु
	काष्ठा bpqdev *bpq = netdev_priv(ndev);

	dev_put(bpq->ethdev);
	list_del_rcu(&bpq->bpq_list);

	unरेजिस्टर_netdevice(ndev);
पूर्ण

/*
 *	Handle device status changes.
 */
अटल पूर्णांक bpq_device_event(काष्ठा notअगरier_block *this,
			    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (!dev_is_ethdev(dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:		/* new ethernet device -> new BPQ पूर्णांकerface */
		अगर (bpq_get_ax25_dev(dev) == शून्य)
			bpq_new_device(dev);
		अवरोध;

	हाल NETDEV_DOWN:	/* ethernet device बंदd -> बंद BPQ पूर्णांकerface */
		अगर ((dev = bpq_get_ax25_dev(dev)) != शून्य)
			dev_बंद(dev);
		अवरोध;

	हाल NETDEV_UNREGISTER:	/* ethernet device हटाओd -> मुक्त BPQ पूर्णांकerface */
		अगर ((dev = bpq_get_ax25_dev(dev)) != शून्य)
			bpq_मुक्त_device(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण


/* ------------------------------------------------------------------------ */

/*
 * Initialize driver. To be called from af_ax25 अगर not compiled as a
 * module
 */
अटल पूर्णांक __init bpq_init_driver(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_seq("bpqether", 0444, init_net.proc_net, &bpq_seqops)) अणु
		prपूर्णांकk(KERN_ERR
			"bpq: cannot create /proc/net/bpqether entry.\n");
		वापस -ENOENT;
	पूर्ण
#पूर्ण_अगर  /* CONFIG_PROC_FS */

	dev_add_pack(&bpq_packet_type);

	रेजिस्टर_netdevice_notअगरier(&bpq_dev_notअगरier);

	prपूर्णांकk(banner);

	वापस 0;
पूर्ण

अटल व्योम __निकास bpq_cleanup_driver(व्योम)
अणु
	काष्ठा bpqdev *bpq;

	dev_हटाओ_pack(&bpq_packet_type);

	unरेजिस्टर_netdevice_notअगरier(&bpq_dev_notअगरier);

	हटाओ_proc_entry("bpqether", init_net.proc_net);

	rtnl_lock();
	जबतक (!list_empty(&bpq_devices)) अणु
		bpq = list_entry(bpq_devices.next, काष्ठा bpqdev, bpq_list);
		bpq_मुक्त_device(bpq->axdev);
	पूर्ण
	rtnl_unlock();
पूर्ण

MODULE_AUTHOR("Joerg Reuter DL1BKE <jreuter@yaina.de>");
MODULE_DESCRIPTION("Transmit and receive AX.25 packets over Ethernet");
MODULE_LICENSE("GPL");
module_init(bpq_init_driver);
module_निकास(bpq_cleanup_driver);

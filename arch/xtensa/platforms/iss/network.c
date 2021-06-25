<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * arch/xtensa/platक्रमms/iss/network.c
 *
 * Platक्रमm specअगरic initialization.
 *
 * Authors: Chris Zankel <chris@zankel.net>
 * Based on work क्रमm the UML team.
 *
 * Copyright 2005 Tensilica Inc.
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/list.h>
#समावेश <linux/irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/अगर_tun.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/memblock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <platक्रमm/simcall.h>

#घोषणा DRIVER_NAME "iss-netdev"
#घोषणा ETH_MAX_PACKET 1500
#घोषणा ETH_HEADER_OTHER 14
#घोषणा ISS_NET_TIMER_VALUE (HZ / 10)


अटल DEFINE_SPINLOCK(खोलोed_lock);
अटल LIST_HEAD(खोलोed);

अटल DEFINE_SPINLOCK(devices_lock);
अटल LIST_HEAD(devices);

/* ------------------------------------------------------------------------- */

/* We currently only support the TUNTAP transport protocol. */

#घोषणा TRANSPORT_TUNTAP_NAME "tuntap"
#घोषणा TRANSPORT_TUNTAP_MTU ETH_MAX_PACKET

काष्ठा tuntap_info अणु
	अक्षर dev_name[IFNAMSIZ];
	पूर्णांक fd;
पूर्ण;

/* ------------------------------------------------------------------------- */


/* This काष्ठाure contains out निजी inक्रमmation क्रम the driver. */

काष्ठा iss_net_निजी अणु
	काष्ठा list_head device_list;
	काष्ठा list_head खोलोed_list;

	spinlock_t lock;
	काष्ठा net_device *dev;
	काष्ठा platक्रमm_device pdev;
	काष्ठा समयr_list tl;
	काष्ठा net_device_stats stats;

	काष्ठा समयr_list समयr;
	अचिन्हित पूर्णांक समयr_val;

	पूर्णांक index;
	पूर्णांक mtu;

	काष्ठा अणु
		जोड़ अणु
			काष्ठा tuntap_info tuntap;
		पूर्ण info;

		पूर्णांक (*खोलो)(काष्ठा iss_net_निजी *lp);
		व्योम (*बंद)(काष्ठा iss_net_निजी *lp);
		पूर्णांक (*पढ़ो)(काष्ठा iss_net_निजी *lp, काष्ठा sk_buff **skb);
		पूर्णांक (*ग_लिखो)(काष्ठा iss_net_निजी *lp, काष्ठा sk_buff **skb);
		अचिन्हित लघु (*protocol)(काष्ठा sk_buff *skb);
		पूर्णांक (*poll)(काष्ठा iss_net_निजी *lp);
	पूर्ण tp;

पूर्ण;

/* ================================ HELPERS ================================ */


अटल अक्षर *split_अगर_spec(अक्षर *str, ...)
अणु
	अक्षर **arg, *end;
	बहु_सूची ap;

	बहु_शुरू(ap, str);
	जबतक ((arg = बहु_तर्क(ap, अक्षर**)) != शून्य) अणु
		अगर (*str == '\0') अणु
			बहु_पूर्ण(ap);
			वापस शून्य;
		पूर्ण
		end = म_अक्षर(str, ',');
		अगर (end != str)
			*arg = str;
		अगर (end == शून्य) अणु
			बहु_पूर्ण(ap);
			वापस शून्य;
		पूर्ण
		*end++ = '\0';
		str = end;
	पूर्ण
	बहु_पूर्ण(ap);
	वापस str;
पूर्ण

/* Set Ethernet address of the specअगरied device. */

अटल व्योम setup_etheraddr(काष्ठा net_device *dev, अक्षर *str)
अणु
	अचिन्हित अक्षर *addr = dev->dev_addr;

	अगर (str == शून्य)
		जाओ अक्रमom;

	अगर (!mac_pton(str, addr)) अणु
		pr_err("%s: failed to parse '%s' as an ethernet address\n",
		       dev->name, str);
		जाओ अक्रमom;
	पूर्ण
	अगर (is_multicast_ether_addr(addr)) अणु
		pr_err("%s: attempt to assign a multicast ethernet address\n",
		       dev->name);
		जाओ अक्रमom;
	पूर्ण
	अगर (!is_valid_ether_addr(addr)) अणु
		pr_err("%s: attempt to assign an invalid ethernet address\n",
		       dev->name);
		जाओ अक्रमom;
	पूर्ण
	अगर (!is_local_ether_addr(addr))
		pr_warn("%s: assigning a globally valid ethernet address\n",
			dev->name);
	वापस;

अक्रमom:
	pr_info("%s: choosing a random ethernet address\n",
		dev->name);
	eth_hw_addr_अक्रमom(dev);
पूर्ण

/* ======================= TUNTAP TRANSPORT INTERFACE ====================== */

अटल पूर्णांक tuntap_खोलो(काष्ठा iss_net_निजी *lp)
अणु
	काष्ठा अगरreq अगरr;
	अक्षर *dev_name = lp->tp.info.tuntap.dev_name;
	पूर्णांक err = -EINVAL;
	पूर्णांक fd;

	fd = simc_खोलो("/dev/net/tun", 02, 0); /* O_RDWR */
	अगर (fd < 0) अणु
		pr_err("%s: failed to open /dev/net/tun, returned %d (errno = %d)\n",
		       lp->dev->name, fd, त्रुटि_सं);
		वापस fd;
	पूर्ण

	स_रखो(&अगरr, 0, माप(अगरr));
	अगरr.अगरr_flags = IFF_TAP | IFF_NO_PI;
	strlcpy(अगरr.अगरr_name, dev_name, माप(अगरr.अगरr_name));

	err = simc_ioctl(fd, TUNSETIFF, &अगरr);
	अगर (err < 0) अणु
		pr_err("%s: failed to set interface %s, returned %d (errno = %d)\n",
		       lp->dev->name, dev_name, err, त्रुटि_सं);
		simc_बंद(fd);
		वापस err;
	पूर्ण

	lp->tp.info.tuntap.fd = fd;
	वापस err;
पूर्ण

अटल व्योम tuntap_बंद(काष्ठा iss_net_निजी *lp)
अणु
	simc_बंद(lp->tp.info.tuntap.fd);
	lp->tp.info.tuntap.fd = -1;
पूर्ण

अटल पूर्णांक tuntap_पढ़ो(काष्ठा iss_net_निजी *lp, काष्ठा sk_buff **skb)
अणु
	वापस simc_पढ़ो(lp->tp.info.tuntap.fd,
			(*skb)->data, (*skb)->dev->mtu + ETH_HEADER_OTHER);
पूर्ण

अटल पूर्णांक tuntap_ग_लिखो(काष्ठा iss_net_निजी *lp, काष्ठा sk_buff **skb)
अणु
	वापस simc_ग_लिखो(lp->tp.info.tuntap.fd, (*skb)->data, (*skb)->len);
पूर्ण

अचिन्हित लघु tuntap_protocol(काष्ठा sk_buff *skb)
अणु
	वापस eth_type_trans(skb, skb->dev);
पूर्ण

अटल पूर्णांक tuntap_poll(काष्ठा iss_net_निजी *lp)
अणु
	वापस simc_poll(lp->tp.info.tuntap.fd);
पूर्ण

/*
 * ethX=tuntap,[mac address],device name
 */

अटल पूर्णांक tuntap_probe(काष्ठा iss_net_निजी *lp, पूर्णांक index, अक्षर *init)
अणु
	काष्ठा net_device *dev = lp->dev;
	अक्षर *dev_name = शून्य, *mac_str = शून्य, *rem = शून्य;

	/* Transport should be 'tuntap': ethX=tuntap,mac,dev_name */

	अगर (म_भेदन(init, TRANSPORT_TUNTAP_NAME,
		    माप(TRANSPORT_TUNTAP_NAME) - 1))
		वापस 0;

	init += माप(TRANSPORT_TUNTAP_NAME) - 1;
	अगर (*init == ',') अणु
		rem = split_अगर_spec(init + 1, &mac_str, &dev_name);
		अगर (rem != शून्य) अणु
			pr_err("%s: extra garbage on specification : '%s'\n",
			       dev->name, rem);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (*init != '\0') अणु
		pr_err("%s: invalid argument: %s. Skipping device!\n",
		       dev->name, init);
		वापस 0;
	पूर्ण

	अगर (!dev_name) अणु
		pr_err("%s: missing tuntap device name\n", dev->name);
		वापस 0;
	पूर्ण

	strlcpy(lp->tp.info.tuntap.dev_name, dev_name,
		माप(lp->tp.info.tuntap.dev_name));

	setup_etheraddr(dev, mac_str);

	lp->mtu = TRANSPORT_TUNTAP_MTU;

	lp->tp.info.tuntap.fd = -1;

	lp->tp.खोलो = tuntap_खोलो;
	lp->tp.बंद = tuntap_बंद;
	lp->tp.पढ़ो = tuntap_पढ़ो;
	lp->tp.ग_लिखो = tuntap_ग_लिखो;
	lp->tp.protocol = tuntap_protocol;
	lp->tp.poll = tuntap_poll;

	वापस 1;
पूर्ण

/* ================================ ISS NET ================================ */

अटल पूर्णांक iss_net_rx(काष्ठा net_device *dev)
अणु
	काष्ठा iss_net_निजी *lp = netdev_priv(dev);
	पूर्णांक pkt_len;
	काष्ठा sk_buff *skb;

	/* Check अगर there is any new data. */

	अगर (lp->tp.poll(lp) == 0)
		वापस 0;

	/* Try to allocate memory, अगर it fails, try again next round. */

	skb = dev_alloc_skb(dev->mtu + 2 + ETH_HEADER_OTHER);
	अगर (skb == शून्य) अणु
		lp->stats.rx_dropped++;
		वापस 0;
	पूर्ण

	skb_reserve(skb, 2);

	/* Setup skb */

	skb->dev = dev;
	skb_reset_mac_header(skb);
	pkt_len = lp->tp.पढ़ो(lp, &skb);
	skb_put(skb, pkt_len);

	अगर (pkt_len > 0) अणु
		skb_trim(skb, pkt_len);
		skb->protocol = lp->tp.protocol(skb);

		lp->stats.rx_bytes += skb->len;
		lp->stats.rx_packets++;
		netअगर_rx_ni(skb);
		वापस pkt_len;
	पूर्ण
	kमुक्त_skb(skb);
	वापस pkt_len;
पूर्ण

अटल पूर्णांक iss_net_poll(व्योम)
अणु
	काष्ठा list_head *ele;
	पूर्णांक err, ret = 0;

	spin_lock(&खोलोed_lock);

	list_क्रम_each(ele, &खोलोed) अणु
		काष्ठा iss_net_निजी *lp;

		lp = list_entry(ele, काष्ठा iss_net_निजी, खोलोed_list);

		अगर (!netअगर_running(lp->dev))
			अवरोध;

		spin_lock(&lp->lock);

		जबतक ((err = iss_net_rx(lp->dev)) > 0)
			ret++;

		spin_unlock(&lp->lock);

		अगर (err < 0) अणु
			pr_err("Device '%s' read returned %d, shutting it down\n",
			       lp->dev->name, err);
			dev_बंद(lp->dev);
		पूर्ण अन्यथा अणु
			/* FIXME reactivate_fd(lp->fd, ISS_ETH_IRQ); */
		पूर्ण
	पूर्ण

	spin_unlock(&खोलोed_lock);
	वापस ret;
पूर्ण


अटल व्योम iss_net_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा iss_net_निजी *lp = from_समयr(lp, t, समयr);

	iss_net_poll();
	spin_lock(&lp->lock);
	mod_समयr(&lp->समयr, jअगरfies + lp->समयr_val);
	spin_unlock(&lp->lock);
पूर्ण


अटल पूर्णांक iss_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा iss_net_निजी *lp = netdev_priv(dev);
	पूर्णांक err;

	spin_lock_bh(&lp->lock);

	err = lp->tp.खोलो(lp);
	अगर (err < 0)
		जाओ out;

	netअगर_start_queue(dev);

	/* clear buffer - it can happen that the host side of the पूर्णांकerface
	 * is full when we get here. In this हाल, new data is never queued,
	 * SIGIOs never arrive, and the net never works.
	 */
	जबतक ((err = iss_net_rx(dev)) > 0)
		;

	spin_unlock_bh(&lp->lock);
	spin_lock_bh(&खोलोed_lock);
	list_add(&lp->खोलोed_list, &खोलोed);
	spin_unlock_bh(&खोलोed_lock);
	spin_lock_bh(&lp->lock);

	समयr_setup(&lp->समयr, iss_net_समयr, 0);
	lp->समयr_val = ISS_NET_TIMER_VALUE;
	mod_समयr(&lp->समयr, jअगरfies + lp->समयr_val);

out:
	spin_unlock_bh(&lp->lock);
	वापस err;
पूर्ण

अटल पूर्णांक iss_net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा iss_net_निजी *lp = netdev_priv(dev);
	netअगर_stop_queue(dev);
	spin_lock_bh(&lp->lock);

	spin_lock(&खोलोed_lock);
	list_del(&खोलोed);
	spin_unlock(&खोलोed_lock);

	del_समयr_sync(&lp->समयr);

	lp->tp.बंद(lp);

	spin_unlock_bh(&lp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक iss_net_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा iss_net_निजी *lp = netdev_priv(dev);
	पूर्णांक len;

	netअगर_stop_queue(dev);
	spin_lock_bh(&lp->lock);

	len = lp->tp.ग_लिखो(lp, &skb);

	अगर (len == skb->len) अणु
		lp->stats.tx_packets++;
		lp->stats.tx_bytes += skb->len;
		netअगर_trans_update(dev);
		netअगर_start_queue(dev);

		/* this is normally करोne in the पूर्णांकerrupt when tx finishes */
		netअगर_wake_queue(dev);

	पूर्ण अन्यथा अगर (len == 0) अणु
		netअगर_start_queue(dev);
		lp->stats.tx_dropped++;

	पूर्ण अन्यथा अणु
		netअगर_start_queue(dev);
		pr_err("%s: %s failed(%d)\n", dev->name, __func__, len);
	पूर्ण

	spin_unlock_bh(&lp->lock);

	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण


अटल काष्ठा net_device_stats *iss_net_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा iss_net_निजी *lp = netdev_priv(dev);
	वापस &lp->stats;
पूर्ण

अटल व्योम iss_net_set_multicast_list(काष्ठा net_device *dev)
अणु
पूर्ण

अटल व्योम iss_net_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
पूर्ण

अटल पूर्णांक iss_net_set_mac(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा iss_net_निजी *lp = netdev_priv(dev);
	काष्ठा sockaddr *hwaddr = addr;

	अगर (!is_valid_ether_addr(hwaddr->sa_data))
		वापस -EADDRNOTAVAIL;
	spin_lock_bh(&lp->lock);
	स_नकल(dev->dev_addr, hwaddr->sa_data, ETH_ALEN);
	spin_unlock_bh(&lp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक iss_net_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	वापस -EINVAL;
पूर्ण

व्योम iss_net_user_समयr_expire(काष्ठा समयr_list *unused)
अणु
पूर्ण


अटल काष्ठा platक्रमm_driver iss_net_driver = अणु
	.driver = अणु
		.name  = DRIVER_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक driver_रेजिस्टरed;

अटल स्थिर काष्ठा net_device_ops iss_netdev_ops = अणु
	.nकरो_खोलो		= iss_net_खोलो,
	.nकरो_stop		= iss_net_बंद,
	.nकरो_get_stats		= iss_net_get_stats,
	.nकरो_start_xmit		= iss_net_start_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= iss_net_change_mtu,
	.nकरो_set_mac_address	= iss_net_set_mac,
	.nकरो_tx_समयout		= iss_net_tx_समयout,
	.nकरो_set_rx_mode	= iss_net_set_multicast_list,
पूर्ण;

अटल पूर्णांक iss_net_configure(पूर्णांक index, अक्षर *init)
अणु
	काष्ठा net_device *dev;
	काष्ठा iss_net_निजी *lp;
	पूर्णांक err;

	dev = alloc_etherdev(माप(*lp));
	अगर (dev == शून्य) अणु
		pr_err("eth_configure: failed to allocate device\n");
		वापस 1;
	पूर्ण

	/* Initialize निजी element. */

	lp = netdev_priv(dev);
	*lp = (काष्ठा iss_net_निजी) अणु
		.device_list		= LIST_HEAD_INIT(lp->device_list),
		.खोलोed_list		= LIST_HEAD_INIT(lp->खोलोed_list),
		.dev			= dev,
		.index			= index,
	पूर्ण;

	spin_lock_init(&lp->lock);
	/*
	 * If this name ends up conflicting with an existing रेजिस्टरed
	 * netdevice, that is OK, रेजिस्टर_netdevअणु,iceपूर्ण() will notice this
	 * and fail.
	 */
	snम_लिखो(dev->name, माप(dev->name), "eth%d", index);

	/*
	 * Try all transport protocols.
	 * Note: more protocols can be added by adding '&& !X_init(lp, eth)'.
	 */

	अगर (!tuntap_probe(lp, index, init)) अणु
		pr_err("%s: invalid arguments. Skipping device!\n",
		       dev->name);
		जाओ errout;
	पूर्ण

	pr_info("Netdevice %d (%pM)\n", index, dev->dev_addr);

	/* sysfs रेजिस्टर */

	अगर (!driver_रेजिस्टरed) अणु
		platक्रमm_driver_रेजिस्टर(&iss_net_driver);
		driver_रेजिस्टरed = 1;
	पूर्ण

	spin_lock(&devices_lock);
	list_add(&lp->device_list, &devices);
	spin_unlock(&devices_lock);

	lp->pdev.id = index;
	lp->pdev.name = DRIVER_NAME;
	platक्रमm_device_रेजिस्टर(&lp->pdev);
	SET_NETDEV_DEV(dev, &lp->pdev.dev);

	dev->netdev_ops = &iss_netdev_ops;
	dev->mtu = lp->mtu;
	dev->watchकरोg_समयo = (HZ >> 1);
	dev->irq = -1;

	rtnl_lock();
	err = रेजिस्टर_netdevice(dev);
	rtnl_unlock();

	अगर (err) अणु
		pr_err("%s: error registering net device!\n", dev->name);
		/* XXX: should we call ->हटाओ() here? */
		मुक्त_netdev(dev);
		वापस 1;
	पूर्ण

	समयr_setup(&lp->tl, iss_net_user_समयr_expire, 0);

	वापस 0;

errout:
	/* FIXME: unरेजिस्टर; मुक्त, etc.. */
	वापस -EIO;
पूर्ण

/* ------------------------------------------------------------------------- */

/* Filled in during early boot */

काष्ठा list_head eth_cmd_line = LIST_HEAD_INIT(eth_cmd_line);

काष्ठा iss_net_init अणु
	काष्ठा list_head list;
	अक्षर *init;		/* init string */
	पूर्णांक index;
पूर्ण;

/*
 * Parse the command line and look क्रम 'ethX=...' fields, and रेजिस्टर all
 * those fields. They will be later initialized in iss_net_init.
 */

अटल पूर्णांक __init iss_net_setup(अक्षर *str)
अणु
	काष्ठा iss_net_निजी *device = शून्य;
	काष्ठा iss_net_init *new;
	काष्ठा list_head *ele;
	अक्षर *end;
	पूर्णांक rc;
	अचिन्हित n;

	end = म_अक्षर(str, '=');
	अगर (!end) अणु
		pr_err("Expected '=' after device number\n");
		वापस 1;
	पूर्ण
	*end = 0;
	rc = kstrtouपूर्णांक(str, 0, &n);
	*end = '=';
	अगर (rc < 0) अणु
		pr_err("Failed to parse '%s'\n", str);
		वापस 1;
	पूर्ण
	str = end;

	spin_lock(&devices_lock);

	list_क्रम_each(ele, &devices) अणु
		device = list_entry(ele, काष्ठा iss_net_निजी, device_list);
		अगर (device->index == n)
			अवरोध;
	पूर्ण

	spin_unlock(&devices_lock);

	अगर (device && device->index == n) अणु
		pr_err("Device %u already configured\n", n);
		वापस 1;
	पूर्ण

	new = memblock_alloc(माप(*new), SMP_CACHE_BYTES);
	अगर (new == शून्य) अणु
		pr_err("Alloc_bootmem failed\n");
		वापस 1;
	पूर्ण

	INIT_LIST_HEAD(&new->list);
	new->index = n;
	new->init = str + 1;

	list_add_tail(&new->list, &eth_cmd_line);
	वापस 1;
पूर्ण

__setup("eth", iss_net_setup);

/*
 * Initialize all ISS Ethernet devices previously रेजिस्टरed in iss_net_setup.
 */

अटल पूर्णांक iss_net_init(व्योम)
अणु
	काष्ठा list_head *ele, *next;

	/* Walk through all Ethernet devices specअगरied in the command line. */

	list_क्रम_each_safe(ele, next, &eth_cmd_line) अणु
		काष्ठा iss_net_init *eth;
		eth = list_entry(ele, काष्ठा iss_net_init, list);
		iss_net_configure(eth->index, eth->init);
	पूर्ण

	वापस 1;
पूर्ण
device_initcall(iss_net_init);

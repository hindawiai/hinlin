<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Device Layer
 *
 * Authors:     Steve Whitehouse <SteveW@ACM.org>
 *              Eduarकरो Marcelo Serrat <emserrat@geocities.com>
 *
 * Changes:
 *          Steve Whitehouse : Devices now see incoming frames so they
 *                             can mark on who it came from.
 *          Steve Whitehouse : Fixed bug in creating neighbours. Each neighbour
 *                             can now have a device specअगरic setup func.
 *          Steve Whitehouse : Added /proc/sys/net/decnet/conf/<dev>/
 *          Steve Whitehouse : Fixed bug which someबार समाप्तed समयr
 *          Steve Whitehouse : Multiple अगरaddr support
 *          Steve Whitehouse : SIOCGIFCONF is now a compile समय option
 *          Steve Whitehouse : /proc/sys/net/decnet/conf/<sys>/क्रमwarding
 *          Steve Whitehouse : Removed समयr1 - it's a user space issue now
 *         Patrick Caulfield : Fixed router hello message क्रमmat
 *          Steve Whitehouse : Got rid of स्थिरant sizes क्रम blksize क्रम
 *                             devices. All mtu based now.
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/अगर_addr.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/uaccess.h>
#समावेश <net/net_namespace.h>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/fib_rules.h>
#समावेश <net/netlink.h>
#समावेश <net/dn.h>
#समावेश <net/dn_dev.h>
#समावेश <net/dn_route.h>
#समावेश <net/dn_neigh.h>
#समावेश <net/dn_fib.h>

#घोषणा DN_IFREQ_SIZE (दुरत्व(काष्ठा अगरreq, अगरr_अगरru) + माप(काष्ठा sockaddr_dn))

अटल अक्षर dn_rt_all_end_mcast[ETH_ALEN] = अणु0xAB,0x00,0x00,0x04,0x00,0x00पूर्ण;
अटल अक्षर dn_rt_all_rt_mcast[ETH_ALEN]  = अणु0xAB,0x00,0x00,0x03,0x00,0x00पूर्ण;
अटल अक्षर dn_hiord[ETH_ALEN]            = अणु0xAA,0x00,0x04,0x00,0x00,0x00पूर्ण;
अटल अचिन्हित अक्षर dn_eco_version[3]    = अणु0x02,0x00,0x00पूर्ण;

बाह्य काष्ठा neigh_table dn_neigh_table;

/*
 * decnet_address is kept in network order.
 */
__le16 decnet_address = 0;

अटल DEFINE_SPINLOCK(dndev_lock);
अटल काष्ठा net_device *decnet_शेष_device;
अटल BLOCKING_NOTIFIER_HEAD(dnaddr_chain);

अटल काष्ठा dn_dev *dn_dev_create(काष्ठा net_device *dev, पूर्णांक *err);
अटल व्योम dn_dev_delete(काष्ठा net_device *dev);
अटल व्योम dn_अगरaddr_notअगरy(पूर्णांक event, काष्ठा dn_अगरaddr *अगरa);

अटल पूर्णांक dn_eth_up(काष्ठा net_device *);
अटल व्योम dn_eth_करोwn(काष्ठा net_device *);
अटल व्योम dn_send_brd_hello(काष्ठा net_device *dev, काष्ठा dn_अगरaddr *अगरa);
अटल व्योम dn_send_ptp_hello(काष्ठा net_device *dev, काष्ठा dn_अगरaddr *अगरa);

अटल काष्ठा dn_dev_parms dn_dev_list[] =  अणु
अणु
	.type =		ARPHRD_ETHER, /* Ethernet */
	.mode =		DN_DEV_BCAST,
	.state =	DN_DEV_S_RU,
	.t2 =		1,
	.t3 =		10,
	.name =		"ethernet",
	.up =		dn_eth_up,
	.करोwn = 	dn_eth_करोwn,
	.समयr3 =	dn_send_brd_hello,
पूर्ण,
अणु
	.type =		ARPHRD_IPGRE, /* DECnet tunneled over GRE in IP */
	.mode =		DN_DEV_BCAST,
	.state =	DN_DEV_S_RU,
	.t2 =		1,
	.t3 =		10,
	.name =		"ipgre",
	.समयr3 =	dn_send_brd_hello,
पूर्ण,
#अगर 0
अणु
	.type =		ARPHRD_X25, /* Bog standard X.25 */
	.mode =		DN_DEV_UCAST,
	.state =	DN_DEV_S_DS,
	.t2 =		1,
	.t3 =		120,
	.name =		"x25",
	.समयr3 =	dn_send_ptp_hello,
पूर्ण,
#पूर्ण_अगर
#अगर 0
अणु
	.type =		ARPHRD_PPP, /* DECnet over PPP */
	.mode =		DN_DEV_BCAST,
	.state =	DN_DEV_S_RU,
	.t2 =		1,
	.t3 =		10,
	.name =		"ppp",
	.समयr3 =	dn_send_brd_hello,
पूर्ण,
#पूर्ण_अगर
अणु
	.type =		ARPHRD_DDCMP, /* DECnet over DDCMP */
	.mode =		DN_DEV_UCAST,
	.state =	DN_DEV_S_DS,
	.t2 =		1,
	.t3 =		120,
	.name =		"ddcmp",
	.समयr3 =	dn_send_ptp_hello,
पूर्ण,
अणु
	.type =		ARPHRD_LOOPBACK, /* Loopback पूर्णांकerface - always last */
	.mode =		DN_DEV_BCAST,
	.state =	DN_DEV_S_RU,
	.t2 =		1,
	.t3 =		10,
	.name =		"loopback",
	.समयr3 =	dn_send_brd_hello,
पूर्ण
पूर्ण;

#घोषणा DN_DEV_LIST_SIZE ARRAY_SIZE(dn_dev_list)

#घोषणा DN_DEV_PARMS_OFFSET(x) दुरत्व(काष्ठा dn_dev_parms, x)

#अगर_घोषित CONFIG_SYSCTL

अटल पूर्णांक min_t2[] = अणु 1 पूर्ण;
अटल पूर्णांक max_t2[] = अणु 60 पूर्ण; /* No max specअगरied, but this seems sensible */
अटल पूर्णांक min_t3[] = अणु 1 पूर्ण;
अटल पूर्णांक max_t3[] = अणु 8191 पूर्ण; /* Must fit in 16 bits when multiplied by BCT3MULT or T3MULT */

अटल पूर्णांक min_priority[1];
अटल पूर्णांक max_priority[] = अणु 127 पूर्ण; /* From DECnet spec */

अटल पूर्णांक dn_क्रमwarding_proc(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *,
		loff_t *);
अटल काष्ठा dn_dev_sysctl_table अणु
	काष्ठा ctl_table_header *sysctl_header;
	काष्ठा ctl_table dn_dev_vars[5];
पूर्ण dn_dev_sysctl = अणु
	शून्य,
	अणु
	अणु
		.procname = "forwarding",
		.data = (व्योम *)DN_DEV_PARMS_OFFSET(क्रमwarding),
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = dn_क्रमwarding_proc,
	पूर्ण,
	अणु
		.procname = "priority",
		.data = (व्योम *)DN_DEV_PARMS_OFFSET(priority),
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_priority,
		.extra2 = &max_priority
	पूर्ण,
	अणु
		.procname = "t2",
		.data = (व्योम *)DN_DEV_PARMS_OFFSET(t2),
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_t2,
		.extra2 = &max_t2
	पूर्ण,
	अणु
		.procname = "t3",
		.data = (व्योम *)DN_DEV_PARMS_OFFSET(t3),
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = &min_t3,
		.extra2 = &max_t3
	पूर्ण,
	अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल व्योम dn_dev_sysctl_रेजिस्टर(काष्ठा net_device *dev, काष्ठा dn_dev_parms *parms)
अणु
	काष्ठा dn_dev_sysctl_table *t;
	पूर्णांक i;

	अक्षर path[माप("net/decnet/conf/") + IFNAMSIZ];

	t = kmemdup(&dn_dev_sysctl, माप(*t), GFP_KERNEL);
	अगर (t == शून्य)
		वापस;

	क्रम(i = 0; i < ARRAY_SIZE(t->dn_dev_vars) - 1; i++) अणु
		दीर्घ offset = (दीर्घ)t->dn_dev_vars[i].data;
		t->dn_dev_vars[i].data = ((अक्षर *)parms) + offset;
	पूर्ण

	snम_लिखो(path, माप(path), "net/decnet/conf/%s",
		dev? dev->name : parms->name);

	t->dn_dev_vars[0].extra1 = (व्योम *)dev;

	t->sysctl_header = रेजिस्टर_net_sysctl(&init_net, path, t->dn_dev_vars);
	अगर (t->sysctl_header == शून्य)
		kमुक्त(t);
	अन्यथा
		parms->sysctl = t;
पूर्ण

अटल व्योम dn_dev_sysctl_unरेजिस्टर(काष्ठा dn_dev_parms *parms)
अणु
	अगर (parms->sysctl) अणु
		काष्ठा dn_dev_sysctl_table *t = parms->sysctl;
		parms->sysctl = शून्य;
		unरेजिस्टर_net_sysctl_table(t->sysctl_header);
		kमुक्त(t);
	पूर्ण
पूर्ण

अटल पूर्णांक dn_क्रमwarding_proc(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
#अगर_घोषित CONFIG_DECNET_ROUTER
	काष्ठा net_device *dev = table->extra1;
	काष्ठा dn_dev *dn_db;
	पूर्णांक err;
	पूर्णांक पंचांगp, old;

	अगर (table->extra1 == शून्य)
		वापस -EINVAL;

	dn_db = rcu_dereference_raw(dev->dn_ptr);
	old = dn_db->parms.क्रमwarding;

	err = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);

	अगर ((err >= 0) && ग_लिखो) अणु
		अगर (dn_db->parms.क्रमwarding < 0)
			dn_db->parms.क्रमwarding = 0;
		अगर (dn_db->parms.क्रमwarding > 2)
			dn_db->parms.क्रमwarding = 2;
		/*
		 * What an ugly hack this is... its works, just. It
		 * would be nice अगर sysctl/proc were just that little
		 * bit more flexible so I करोn't have to ग_लिखो a special
		 * routine, or suffer hacks like this - SJW
		 */
		पंचांगp = dn_db->parms.क्रमwarding;
		dn_db->parms.क्रमwarding = old;
		अगर (dn_db->parms.करोwn)
			dn_db->parms.करोwn(dev);
		dn_db->parms.क्रमwarding = पंचांगp;
		अगर (dn_db->parms.up)
			dn_db->parms.up(dev);
	पूर्ण

	वापस err;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

#अन्यथा /* CONFIG_SYSCTL */
अटल व्योम dn_dev_sysctl_unरेजिस्टर(काष्ठा dn_dev_parms *parms)
अणु
पूर्ण
अटल व्योम dn_dev_sysctl_रेजिस्टर(काष्ठा net_device *dev, काष्ठा dn_dev_parms *parms)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_SYSCTL */

अटल अंतरभूत __u16 mtu2blksize(काष्ठा net_device *dev)
अणु
	u32 blksize = dev->mtu;
	अगर (blksize > 0xffff)
		blksize = 0xffff;

	अगर (dev->type == ARPHRD_ETHER ||
	    dev->type == ARPHRD_PPP ||
	    dev->type == ARPHRD_IPGRE ||
	    dev->type == ARPHRD_LOOPBACK)
		blksize -= 2;

	वापस (__u16)blksize;
पूर्ण

अटल काष्ठा dn_अगरaddr *dn_dev_alloc_अगरa(व्योम)
अणु
	काष्ठा dn_अगरaddr *अगरa;

	अगरa = kzalloc(माप(*अगरa), GFP_KERNEL);

	वापस अगरa;
पूर्ण

अटल व्योम dn_dev_मुक्त_अगरa(काष्ठा dn_अगरaddr *अगरa)
अणु
	kमुक्त_rcu(अगरa, rcu);
पूर्ण

अटल व्योम dn_dev_del_अगरa(काष्ठा dn_dev *dn_db, काष्ठा dn_अगरaddr __rcu **अगरap, पूर्णांक destroy)
अणु
	काष्ठा dn_अगरaddr *अगरa1 = rtnl_dereference(*अगरap);
	अचिन्हित अक्षर mac_addr[6];
	काष्ठा net_device *dev = dn_db->dev;

	ASSERT_RTNL();

	*अगरap = अगरa1->अगरa_next;

	अगर (dn_db->dev->type == ARPHRD_ETHER) अणु
		अगर (अगरa1->अगरa_local != dn_eth2dn(dev->dev_addr)) अणु
			dn_dn2eth(mac_addr, अगरa1->अगरa_local);
			dev_mc_del(dev, mac_addr);
		पूर्ण
	पूर्ण

	dn_अगरaddr_notअगरy(RTM_DELADDR, अगरa1);
	blocking_notअगरier_call_chain(&dnaddr_chain, NETDEV_DOWN, अगरa1);
	अगर (destroy) अणु
		dn_dev_मुक्त_अगरa(अगरa1);

		अगर (dn_db->अगरa_list == शून्य)
			dn_dev_delete(dn_db->dev);
	पूर्ण
पूर्ण

अटल पूर्णांक dn_dev_insert_अगरa(काष्ठा dn_dev *dn_db, काष्ठा dn_अगरaddr *अगरa)
अणु
	काष्ठा net_device *dev = dn_db->dev;
	काष्ठा dn_अगरaddr *अगरa1;
	अचिन्हित अक्षर mac_addr[6];

	ASSERT_RTNL();

	/* Check क्रम duplicates */
	क्रम (अगरa1 = rtnl_dereference(dn_db->अगरa_list);
	     अगरa1 != शून्य;
	     अगरa1 = rtnl_dereference(अगरa1->अगरa_next)) अणु
		अगर (अगरa1->अगरa_local == अगरa->अगरa_local)
			वापस -EEXIST;
	पूर्ण

	अगर (dev->type == ARPHRD_ETHER) अणु
		अगर (अगरa->अगरa_local != dn_eth2dn(dev->dev_addr)) अणु
			dn_dn2eth(mac_addr, अगरa->अगरa_local);
			dev_mc_add(dev, mac_addr);
		पूर्ण
	पूर्ण

	अगरa->अगरa_next = dn_db->अगरa_list;
	rcu_assign_poपूर्णांकer(dn_db->अगरa_list, अगरa);

	dn_अगरaddr_notअगरy(RTM_NEWADDR, अगरa);
	blocking_notअगरier_call_chain(&dnaddr_chain, NETDEV_UP, अगरa);

	वापस 0;
पूर्ण

अटल पूर्णांक dn_dev_set_अगरa(काष्ठा net_device *dev, काष्ठा dn_अगरaddr *अगरa)
अणु
	काष्ठा dn_dev *dn_db = rtnl_dereference(dev->dn_ptr);
	पूर्णांक rv;

	अगर (dn_db == शून्य) अणु
		पूर्णांक err;
		dn_db = dn_dev_create(dev, &err);
		अगर (dn_db == शून्य)
			वापस err;
	पूर्ण

	अगरa->अगरa_dev = dn_db;

	अगर (dev->flags & IFF_LOOPBACK)
		अगरa->अगरa_scope = RT_SCOPE_HOST;

	rv = dn_dev_insert_अगरa(dn_db, अगरa);
	अगर (rv)
		dn_dev_मुक्त_अगरa(अगरa);
	वापस rv;
पूर्ण


पूर्णांक dn_dev_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	अक्षर buffer[DN_IFREQ_SIZE];
	काष्ठा अगरreq *अगरr = (काष्ठा अगरreq *)buffer;
	काष्ठा sockaddr_dn *sdn = (काष्ठा sockaddr_dn *)&अगरr->अगरr_addr;
	काष्ठा dn_dev *dn_db;
	काष्ठा net_device *dev;
	काष्ठा dn_अगरaddr *अगरa = शून्य;
	काष्ठा dn_अगरaddr __rcu **अगरap = शून्य;
	पूर्णांक ret = 0;

	अगर (copy_from_user(अगरr, arg, DN_IFREQ_SIZE))
		वापस -EFAULT;
	अगरr->अगरr_name[IFNAMSIZ-1] = 0;

	dev_load(&init_net, अगरr->अगरr_name);

	चयन (cmd) अणु
	हाल SIOCGIFADDR:
		अवरोध;
	हाल SIOCSIFADDR:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EACCES;
		अगर (sdn->sdn_family != AF_DECnet)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rtnl_lock();

	अगर ((dev = __dev_get_by_name(&init_net, अगरr->अगरr_name)) == शून्य) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर ((dn_db = rtnl_dereference(dev->dn_ptr)) != शून्य) अणु
		क्रम (अगरap = &dn_db->अगरa_list;
		     (अगरa = rtnl_dereference(*अगरap)) != शून्य;
		     अगरap = &अगरa->अगरa_next)
			अगर (म_भेद(अगरr->अगरr_name, अगरa->अगरa_label) == 0)
				अवरोध;
	पूर्ण

	अगर (अगरa == शून्य && cmd != SIOCSIFADDR) अणु
		ret = -EADDRNOTAVAIL;
		जाओ करोne;
	पूर्ण

	चयन (cmd) अणु
	हाल SIOCGIFADDR:
		*((__le16 *)sdn->sdn_nodeaddr) = अगरa->अगरa_local;
		अगर (copy_to_user(arg, अगरr, DN_IFREQ_SIZE))
			ret = -EFAULT;
		अवरोध;

	हाल SIOCSIFADDR:
		अगर (!अगरa) अणु
			अगर ((अगरa = dn_dev_alloc_अगरa()) == शून्य) अणु
				ret = -ENOBUFS;
				अवरोध;
			पूर्ण
			स_नकल(अगरa->अगरa_label, dev->name, IFNAMSIZ);
		पूर्ण अन्यथा अणु
			अगर (अगरa->अगरa_local == dn_saddr2dn(sdn))
				अवरोध;
			dn_dev_del_अगरa(dn_db, अगरap, 0);
		पूर्ण

		अगरa->अगरa_local = अगरa->अगरa_address = dn_saddr2dn(sdn);

		ret = dn_dev_set_अगरa(dev, अगरa);
	पूर्ण
करोne:
	rtnl_unlock();

	वापस ret;
पूर्ण

काष्ठा net_device *dn_dev_get_शेष(व्योम)
अणु
	काष्ठा net_device *dev;

	spin_lock(&dndev_lock);
	dev = decnet_शेष_device;
	अगर (dev) अणु
		अगर (dev->dn_ptr)
			dev_hold(dev);
		अन्यथा
			dev = शून्य;
	पूर्ण
	spin_unlock(&dndev_lock);

	वापस dev;
पूर्ण

पूर्णांक dn_dev_set_शेष(काष्ठा net_device *dev, पूर्णांक क्रमce)
अणु
	काष्ठा net_device *old = शून्य;
	पूर्णांक rv = -EBUSY;
	अगर (!dev->dn_ptr)
		वापस -ENODEV;

	spin_lock(&dndev_lock);
	अगर (क्रमce || decnet_शेष_device == शून्य) अणु
		old = decnet_शेष_device;
		decnet_शेष_device = dev;
		rv = 0;
	पूर्ण
	spin_unlock(&dndev_lock);

	अगर (old)
		dev_put(old);
	वापस rv;
पूर्ण

अटल व्योम dn_dev_check_शेष(काष्ठा net_device *dev)
अणु
	spin_lock(&dndev_lock);
	अगर (dev == decnet_शेष_device) अणु
		decnet_शेष_device = शून्य;
	पूर्ण अन्यथा अणु
		dev = शून्य;
	पूर्ण
	spin_unlock(&dndev_lock);

	अगर (dev)
		dev_put(dev);
पूर्ण

/*
 * Called with RTNL
 */
अटल काष्ठा dn_dev *dn_dev_by_index(पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;
	काष्ठा dn_dev *dn_dev = शून्य;

	dev = __dev_get_by_index(&init_net, अगरindex);
	अगर (dev)
		dn_dev = rtnl_dereference(dev->dn_ptr);

	वापस dn_dev;
पूर्ण

अटल स्थिर काष्ठा nla_policy dn_अगरa_policy[IFA_MAX+1] = अणु
	[IFA_ADDRESS]		= अणु .type = NLA_U16 पूर्ण,
	[IFA_LOCAL]		= अणु .type = NLA_U16 पूर्ण,
	[IFA_LABEL]		= अणु .type = NLA_STRING,
				    .len = IFNAMSIZ - 1 पूर्ण,
	[IFA_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक dn_nl_deladdr(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा dn_dev *dn_db;
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा dn_अगरaddr *अगरa;
	काष्ठा dn_अगरaddr __rcu **अगरap;
	पूर्णांक err = -EINVAL;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!net_eq(net, &init_net))
		जाओ errout;

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFA_MAX,
				     dn_अगरa_policy, extack);
	अगर (err < 0)
		जाओ errout;

	err = -ENODEV;
	अगरm = nlmsg_data(nlh);
	अगर ((dn_db = dn_dev_by_index(अगरm->अगरa_index)) == शून्य)
		जाओ errout;

	err = -EADDRNOTAVAIL;
	क्रम (अगरap = &dn_db->अगरa_list;
	     (अगरa = rtnl_dereference(*अगरap)) != शून्य;
	     अगरap = &अगरa->अगरa_next) अणु
		अगर (tb[IFA_LOCAL] &&
		    nla_स_भेद(tb[IFA_LOCAL], &अगरa->अगरa_local, 2))
			जारी;

		अगर (tb[IFA_LABEL] && nla_म_भेद(tb[IFA_LABEL], अगरa->अगरa_label))
			जारी;

		dn_dev_del_अगरa(dn_db, अगरap, 1);
		वापस 0;
	पूर्ण

errout:
	वापस err;
पूर्ण

अटल पूर्णांक dn_nl_newaddr(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा net_device *dev;
	काष्ठा dn_dev *dn_db;
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा dn_अगरaddr *अगरa;
	पूर्णांक err;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!net_eq(net, &init_net))
		वापस -EINVAL;

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFA_MAX,
				     dn_अगरa_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFA_LOCAL] == शून्य)
		वापस -EINVAL;

	अगरm = nlmsg_data(nlh);
	अगर ((dev = __dev_get_by_index(&init_net, अगरm->अगरa_index)) == शून्य)
		वापस -ENODEV;

	अगर ((dn_db = rtnl_dereference(dev->dn_ptr)) == शून्य) अणु
		dn_db = dn_dev_create(dev, &err);
		अगर (!dn_db)
			वापस err;
	पूर्ण

	अगर ((अगरa = dn_dev_alloc_अगरa()) == शून्य)
		वापस -ENOBUFS;

	अगर (tb[IFA_ADDRESS] == शून्य)
		tb[IFA_ADDRESS] = tb[IFA_LOCAL];

	अगरa->अगरa_local = nla_get_le16(tb[IFA_LOCAL]);
	अगरa->अगरa_address = nla_get_le16(tb[IFA_ADDRESS]);
	अगरa->अगरa_flags = tb[IFA_FLAGS] ? nla_get_u32(tb[IFA_FLAGS]) :
					 अगरm->अगरa_flags;
	अगरa->अगरa_scope = अगरm->अगरa_scope;
	अगरa->अगरa_dev = dn_db;

	अगर (tb[IFA_LABEL])
		nla_strscpy(अगरa->अगरa_label, tb[IFA_LABEL], IFNAMSIZ);
	अन्यथा
		स_नकल(अगरa->अगरa_label, dev->name, IFNAMSIZ);

	err = dn_dev_insert_अगरa(dn_db, अगरa);
	अगर (err)
		dn_dev_मुक्त_अगरa(अगरa);

	वापस err;
पूर्ण

अटल अंतरभूत माप_प्रकार dn_अगरaddr_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा अगरaddrmsg))
	       + nla_total_size(IFNAMSIZ) /* IFA_LABEL */
	       + nla_total_size(2) /* IFA_ADDRESS */
	       + nla_total_size(2) /* IFA_LOCAL */
	       + nla_total_size(4); /* IFA_FLAGS */
पूर्ण

अटल पूर्णांक dn_nl_fill_अगरaddr(काष्ठा sk_buff *skb, काष्ठा dn_अगरaddr *अगरa,
			     u32 portid, u32 seq, पूर्णांक event, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा nlmsghdr *nlh;
	u32 अगरa_flags = अगरa->अगरa_flags | IFA_F_PERMANENT;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*अगरm), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	अगरm = nlmsg_data(nlh);
	अगरm->अगरa_family = AF_DECnet;
	अगरm->अगरa_prefixlen = 16;
	अगरm->अगरa_flags = अगरa_flags;
	अगरm->अगरa_scope = अगरa->अगरa_scope;
	अगरm->अगरa_index = अगरa->अगरa_dev->dev->अगरindex;

	अगर ((अगरa->अगरa_address &&
	     nla_put_le16(skb, IFA_ADDRESS, अगरa->अगरa_address)) ||
	    (अगरa->अगरa_local &&
	     nla_put_le16(skb, IFA_LOCAL, अगरa->अगरa_local)) ||
	    (अगरa->अगरa_label[0] &&
	     nla_put_string(skb, IFA_LABEL, अगरa->अगरa_label)) ||
	     nla_put_u32(skb, IFA_FLAGS, अगरa_flags))
		जाओ nla_put_failure;
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम dn_अगरaddr_notअगरy(पूर्णांक event, काष्ठा dn_अगरaddr *अगरa)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = alloc_skb(dn_अगरaddr_nlmsg_size(), GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ errout;

	err = dn_nl_fill_अगरaddr(skb, अगरa, 0, 0, event, 0);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in dn_अगरaddr_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, &init_net, 0, RTNLGRP_DECnet_IFADDR, शून्य, GFP_KERNEL);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(&init_net, RTNLGRP_DECnet_IFADDR, err);
पूर्ण

अटल पूर्णांक dn_nl_dump_अगरaddr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक idx, dn_idx = 0, skip_ndevs, skip_naddr;
	काष्ठा net_device *dev;
	काष्ठा dn_dev *dn_db;
	काष्ठा dn_अगरaddr *अगरa;

	अगर (!net_eq(net, &init_net))
		वापस 0;

	skip_ndevs = cb->args[0];
	skip_naddr = cb->args[1];

	idx = 0;
	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर (idx < skip_ndevs)
			जाओ cont;
		अन्यथा अगर (idx > skip_ndevs) अणु
			/* Only skip over addresses क्रम first dev dumped
			 * in this iteration (idx == skip_ndevs) */
			skip_naddr = 0;
		पूर्ण

		अगर ((dn_db = rcu_dereference(dev->dn_ptr)) == शून्य)
			जाओ cont;

		क्रम (अगरa = rcu_dereference(dn_db->अगरa_list), dn_idx = 0; अगरa;
		     अगरa = rcu_dereference(अगरa->अगरa_next), dn_idx++) अणु
			अगर (dn_idx < skip_naddr)
				जारी;

			अगर (dn_nl_fill_अगरaddr(skb, अगरa, NETLINK_CB(cb->skb).portid,
					      cb->nlh->nlmsg_seq, RTM_NEWADDR,
					      NLM_F_MULTI) < 0)
				जाओ करोne;
		पूर्ण
cont:
		idx++;
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();
	cb->args[0] = idx;
	cb->args[1] = dn_idx;

	वापस skb->len;
पूर्ण

अटल पूर्णांक dn_dev_get_first(काष्ठा net_device *dev, __le16 *addr)
अणु
	काष्ठा dn_dev *dn_db;
	काष्ठा dn_अगरaddr *अगरa;
	पूर्णांक rv = -ENODEV;

	rcu_पढ़ो_lock();
	dn_db = rcu_dereference(dev->dn_ptr);
	अगर (dn_db == शून्य)
		जाओ out;

	अगरa = rcu_dereference(dn_db->अगरa_list);
	अगर (अगरa != शून्य) अणु
		*addr = अगरa->अगरa_local;
		rv = 0;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस rv;
पूर्ण

/*
 * Find a शेष address to bind to.
 *
 * This is one of those areas where the initial VMS concepts करोn't really
 * map onto the Linux concepts, and since we पूर्णांकroduced multiple addresses
 * per पूर्णांकerface we have to cope with slightly odd ways of finding out what
 * "our address" really is. Mostly it's not a problem; क्रम this we just guess
 * a sensible शेष. Eventually the routing code will take care of all the
 * nasties क्रम us I hope.
 */
पूर्णांक dn_dev_bind_शेष(__le16 *addr)
अणु
	काष्ठा net_device *dev;
	पूर्णांक rv;
	dev = dn_dev_get_शेष();
last_chance:
	अगर (dev) अणु
		rv = dn_dev_get_first(dev, addr);
		dev_put(dev);
		अगर (rv == 0 || dev == init_net.loopback_dev)
			वापस rv;
	पूर्ण
	dev = init_net.loopback_dev;
	dev_hold(dev);
	जाओ last_chance;
पूर्ण

अटल व्योम dn_send_endnode_hello(काष्ठा net_device *dev, काष्ठा dn_अगरaddr *अगरa)
अणु
	काष्ठा endnode_hello_message *msg;
	काष्ठा sk_buff *skb = शून्य;
	__le16 *pktlen;
	काष्ठा dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);

	अगर ((skb = dn_alloc_skb(शून्य, माप(*msg), GFP_ATOMIC)) == शून्य)
		वापस;

	skb->dev = dev;

	msg = skb_put(skb, माप(*msg));

	msg->msgflg  = 0x0D;
	स_नकल(msg->tiver, dn_eco_version, 3);
	dn_dn2eth(msg->id, अगरa->अगरa_local);
	msg->iinfo   = DN_RT_INFO_ENDN;
	msg->blksize = cpu_to_le16(mtu2blksize(dev));
	msg->area    = 0x00;
	स_रखो(msg->seed, 0, 8);
	स_नकल(msg->neighbor, dn_hiord, ETH_ALEN);

	अगर (dn_db->router) अणु
		काष्ठा dn_neigh *dn = (काष्ठा dn_neigh *)dn_db->router;
		dn_dn2eth(msg->neighbor, dn->addr);
	पूर्ण

	msg->समयr   = cpu_to_le16((अचिन्हित लघु)dn_db->parms.t3);
	msg->mpd     = 0x00;
	msg->datalen = 0x02;
	स_रखो(msg->data, 0xAA, 2);

	pktlen = skb_push(skb, 2);
	*pktlen = cpu_to_le16(skb->len - 2);

	skb_reset_network_header(skb);

	dn_rt_finish_output(skb, dn_rt_all_rt_mcast, msg->id);
पूर्ण


#घोषणा DRDELAY (5 * HZ)

अटल पूर्णांक dn_am_i_a_router(काष्ठा dn_neigh *dn, काष्ठा dn_dev *dn_db, काष्ठा dn_अगरaddr *अगरa)
अणु
	/* First check समय since device went up */
	अगर (समय_beक्रमe(jअगरfies, dn_db->upसमय + DRDELAY))
		वापस 0;

	/* If there is no router, then yes... */
	अगर (!dn_db->router)
		वापस 1;

	/* otherwise only अगर we have a higher priority or.. */
	अगर (dn->priority < dn_db->parms.priority)
		वापस 1;

	/* अगर we have equal priority and a higher node number */
	अगर (dn->priority != dn_db->parms.priority)
		वापस 0;

	अगर (le16_to_cpu(dn->addr) < le16_to_cpu(अगरa->अगरa_local))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम dn_send_router_hello(काष्ठा net_device *dev, काष्ठा dn_अगरaddr *अगरa)
अणु
	पूर्णांक n;
	काष्ठा dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);
	काष्ठा dn_neigh *dn = (काष्ठा dn_neigh *)dn_db->router;
	काष्ठा sk_buff *skb;
	माप_प्रकार size;
	अचिन्हित अक्षर *ptr;
	अचिन्हित अक्षर *i1, *i2;
	__le16 *pktlen;
	अक्षर *src;

	अगर (mtu2blksize(dev) < (26 + 7))
		वापस;

	n = mtu2blksize(dev) - 26;
	n /= 7;

	अगर (n > 32)
		n = 32;

	size = 2 + 26 + 7 * n;

	अगर ((skb = dn_alloc_skb(शून्य, size, GFP_ATOMIC)) == शून्य)
		वापस;

	skb->dev = dev;
	ptr = skb_put(skb, size);

	*ptr++ = DN_RT_PKT_CNTL | DN_RT_PKT_ERTH;
	*ptr++ = 2; /* ECO */
	*ptr++ = 0;
	*ptr++ = 0;
	dn_dn2eth(ptr, अगरa->अगरa_local);
	src = ptr;
	ptr += ETH_ALEN;
	*ptr++ = dn_db->parms.क्रमwarding == 1 ?
			DN_RT_INFO_L1RT : DN_RT_INFO_L2RT;
	*((__le16 *)ptr) = cpu_to_le16(mtu2blksize(dev));
	ptr += 2;
	*ptr++ = dn_db->parms.priority; /* Priority */
	*ptr++ = 0; /* Area: Reserved */
	*((__le16 *)ptr) = cpu_to_le16((अचिन्हित लघु)dn_db->parms.t3);
	ptr += 2;
	*ptr++ = 0; /* MPD: Reserved */
	i1 = ptr++;
	स_रखो(ptr, 0, 7); /* Name: Reserved */
	ptr += 7;
	i2 = ptr++;

	n = dn_neigh_elist(dev, ptr, n);

	*i2 = 7 * n;
	*i1 = 8 + *i2;

	skb_trim(skb, (27 + *i2));

	pktlen = skb_push(skb, 2);
	*pktlen = cpu_to_le16(skb->len - 2);

	skb_reset_network_header(skb);

	अगर (dn_am_i_a_router(dn, dn_db, अगरa)) अणु
		काष्ठा sk_buff *skb2 = skb_copy(skb, GFP_ATOMIC);
		अगर (skb2) अणु
			dn_rt_finish_output(skb2, dn_rt_all_end_mcast, src);
		पूर्ण
	पूर्ण

	dn_rt_finish_output(skb, dn_rt_all_rt_mcast, src);
पूर्ण

अटल व्योम dn_send_brd_hello(काष्ठा net_device *dev, काष्ठा dn_अगरaddr *अगरa)
अणु
	काष्ठा dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);

	अगर (dn_db->parms.क्रमwarding == 0)
		dn_send_endnode_hello(dev, अगरa);
	अन्यथा
		dn_send_router_hello(dev, अगरa);
पूर्ण

अटल व्योम dn_send_ptp_hello(काष्ठा net_device *dev, काष्ठा dn_अगरaddr *अगरa)
अणु
	पूर्णांक tdlen = 16;
	पूर्णांक size = dev->hard_header_len + 2 + 4 + tdlen;
	काष्ठा sk_buff *skb = dn_alloc_skb(शून्य, size, GFP_ATOMIC);
	पूर्णांक i;
	अचिन्हित अक्षर *ptr;
	अक्षर src[ETH_ALEN];

	अगर (skb == शून्य)
		वापस ;

	skb->dev = dev;
	skb_push(skb, dev->hard_header_len);
	ptr = skb_put(skb, 2 + 4 + tdlen);

	*ptr++ = DN_RT_PKT_HELO;
	*((__le16 *)ptr) = अगरa->अगरa_local;
	ptr += 2;
	*ptr++ = tdlen;

	क्रम(i = 0; i < tdlen; i++)
		*ptr++ = 0252;

	dn_dn2eth(src, अगरa->अगरa_local);
	dn_rt_finish_output(skb, dn_rt_all_rt_mcast, src);
पूर्ण

अटल पूर्णांक dn_eth_up(काष्ठा net_device *dev)
अणु
	काष्ठा dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);

	अगर (dn_db->parms.क्रमwarding == 0)
		dev_mc_add(dev, dn_rt_all_end_mcast);
	अन्यथा
		dev_mc_add(dev, dn_rt_all_rt_mcast);

	dn_db->use_दीर्घ = 1;

	वापस 0;
पूर्ण

अटल व्योम dn_eth_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);

	अगर (dn_db->parms.क्रमwarding == 0)
		dev_mc_del(dev, dn_rt_all_end_mcast);
	अन्यथा
		dev_mc_del(dev, dn_rt_all_rt_mcast);
पूर्ण

अटल व्योम dn_dev_set_समयr(काष्ठा net_device *dev);

अटल व्योम dn_dev_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा dn_dev *dn_db = from_समयr(dn_db, t, समयr);
	काष्ठा net_device *dev;
	काष्ठा dn_अगरaddr *अगरa;

	rcu_पढ़ो_lock();
	dev = dn_db->dev;
	अगर (dn_db->t3 <= dn_db->parms.t2) अणु
		अगर (dn_db->parms.समयr3) अणु
			क्रम (अगरa = rcu_dereference(dn_db->अगरa_list);
			     अगरa;
			     अगरa = rcu_dereference(अगरa->अगरa_next)) अणु
				अगर (!(अगरa->अगरa_flags & IFA_F_SECONDARY))
					dn_db->parms.समयr3(dev, अगरa);
			पूर्ण
		पूर्ण
		dn_db->t3 = dn_db->parms.t3;
	पूर्ण अन्यथा अणु
		dn_db->t3 -= dn_db->parms.t2;
	पूर्ण
	rcu_पढ़ो_unlock();
	dn_dev_set_समयr(dev);
पूर्ण

अटल व्योम dn_dev_set_समयr(काष्ठा net_device *dev)
अणु
	काष्ठा dn_dev *dn_db = rcu_dereference_raw(dev->dn_ptr);

	अगर (dn_db->parms.t2 > dn_db->parms.t3)
		dn_db->parms.t2 = dn_db->parms.t3;

	dn_db->समयr.expires = jअगरfies + (dn_db->parms.t2 * HZ);

	add_समयr(&dn_db->समयr);
पूर्ण

अटल काष्ठा dn_dev *dn_dev_create(काष्ठा net_device *dev, पूर्णांक *err)
अणु
	पूर्णांक i;
	काष्ठा dn_dev_parms *p = dn_dev_list;
	काष्ठा dn_dev *dn_db;

	क्रम(i = 0; i < DN_DEV_LIST_SIZE; i++, p++) अणु
		अगर (p->type == dev->type)
			अवरोध;
	पूर्ण

	*err = -ENODEV;
	अगर (i == DN_DEV_LIST_SIZE)
		वापस शून्य;

	*err = -ENOBUFS;
	अगर ((dn_db = kzalloc(माप(काष्ठा dn_dev), GFP_ATOMIC)) == शून्य)
		वापस शून्य;

	स_नकल(&dn_db->parms, p, माप(काष्ठा dn_dev_parms));

	rcu_assign_poपूर्णांकer(dev->dn_ptr, dn_db);
	dn_db->dev = dev;
	समयr_setup(&dn_db->समयr, dn_dev_समयr_func, 0);

	dn_db->upसमय = jअगरfies;

	dn_db->neigh_parms = neigh_parms_alloc(dev, &dn_neigh_table);
	अगर (!dn_db->neigh_parms) अणु
		RCU_INIT_POINTER(dev->dn_ptr, शून्य);
		kमुक्त(dn_db);
		वापस शून्य;
	पूर्ण

	अगर (dn_db->parms.up) अणु
		अगर (dn_db->parms.up(dev) < 0) अणु
			neigh_parms_release(&dn_neigh_table, dn_db->neigh_parms);
			dev->dn_ptr = शून्य;
			kमुक्त(dn_db);
			वापस शून्य;
		पूर्ण
	पूर्ण

	dn_dev_sysctl_रेजिस्टर(dev, &dn_db->parms);

	dn_dev_set_समयr(dev);

	*err = 0;
	वापस dn_db;
पूर्ण


/*
 * This processes a device up event. We only start up
 * the loopback device & ethernet devices with correct
 * MAC addresses स्वतःmatically. Others must be started
 * specअगरically.
 *
 * FIXME: How should we configure the loopback address ? If we could dispense
 * with using decnet_address here and क्रम स्वतःbind, it will be one less thing
 * क्रम users to worry about setting up.
 */

व्योम dn_dev_up(काष्ठा net_device *dev)
अणु
	काष्ठा dn_अगरaddr *अगरa;
	__le16 addr = decnet_address;
	पूर्णांक maybe_शेष = 0;
	काष्ठा dn_dev *dn_db = rtnl_dereference(dev->dn_ptr);

	अगर ((dev->type != ARPHRD_ETHER) && (dev->type != ARPHRD_LOOPBACK))
		वापस;

	/*
	 * Need to ensure that loopback device has a dn_db attached to it
	 * to allow creation of neighbours against it, even though it might
	 * not have a local address of its own. Might as well करो the same क्रम
	 * all स्वतःconfigured पूर्णांकerfaces.
	 */
	अगर (dn_db == शून्य) अणु
		पूर्णांक err;
		dn_db = dn_dev_create(dev, &err);
		अगर (dn_db == शून्य)
			वापस;
	पूर्ण

	अगर (dev->type == ARPHRD_ETHER) अणु
		अगर (स_भेद(dev->dev_addr, dn_hiord, 4) != 0)
			वापस;
		addr = dn_eth2dn(dev->dev_addr);
		maybe_शेष = 1;
	पूर्ण

	अगर (addr == 0)
		वापस;

	अगर ((अगरa = dn_dev_alloc_अगरa()) == शून्य)
		वापस;

	अगरa->अगरa_local = अगरa->अगरa_address = addr;
	अगरa->अगरa_flags = 0;
	अगरa->अगरa_scope = RT_SCOPE_UNIVERSE;
	म_नकल(अगरa->अगरa_label, dev->name);

	dn_dev_set_अगरa(dev, अगरa);

	/*
	 * Automagically set the शेष device to the first स्वतःmatically
	 * configured ethernet card in the प्रणाली.
	 */
	अगर (maybe_शेष) अणु
		dev_hold(dev);
		अगर (dn_dev_set_शेष(dev, 0))
			dev_put(dev);
	पूर्ण
पूर्ण

अटल व्योम dn_dev_delete(काष्ठा net_device *dev)
अणु
	काष्ठा dn_dev *dn_db = rtnl_dereference(dev->dn_ptr);

	अगर (dn_db == शून्य)
		वापस;

	del_समयr_sync(&dn_db->समयr);
	dn_dev_sysctl_unरेजिस्टर(&dn_db->parms);
	dn_dev_check_शेष(dev);
	neigh_अगरकरोwn(&dn_neigh_table, dev);

	अगर (dn_db->parms.करोwn)
		dn_db->parms.करोwn(dev);

	dev->dn_ptr = शून्य;

	neigh_parms_release(&dn_neigh_table, dn_db->neigh_parms);
	neigh_अगरकरोwn(&dn_neigh_table, dev);

	अगर (dn_db->router)
		neigh_release(dn_db->router);
	अगर (dn_db->peer)
		neigh_release(dn_db->peer);

	kमुक्त(dn_db);
पूर्ण

व्योम dn_dev_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा dn_dev *dn_db = rtnl_dereference(dev->dn_ptr);
	काष्ठा dn_अगरaddr *अगरa;

	अगर (dn_db == शून्य)
		वापस;

	जबतक ((अगरa = rtnl_dereference(dn_db->अगरa_list)) != शून्य) अणु
		dn_dev_del_अगरa(dn_db, &dn_db->अगरa_list, 0);
		dn_dev_मुक्त_अगरa(अगरa);
	पूर्ण

	dn_dev_delete(dev);
पूर्ण

व्योम dn_dev_init_pkt(काष्ठा sk_buff *skb)
अणु
पूर्ण

व्योम dn_dev_veri_pkt(काष्ठा sk_buff *skb)
अणु
पूर्ण

व्योम dn_dev_hello(काष्ठा sk_buff *skb)
अणु
पूर्ण

व्योम dn_dev_devices_off(व्योम)
अणु
	काष्ठा net_device *dev;

	rtnl_lock();
	क्रम_each_netdev(&init_net, dev)
		dn_dev_करोwn(dev);
	rtnl_unlock();

पूर्ण

व्योम dn_dev_devices_on(व्योम)
अणु
	काष्ठा net_device *dev;

	rtnl_lock();
	क्रम_each_netdev(&init_net, dev) अणु
		अगर (dev->flags & IFF_UP)
			dn_dev_up(dev);
	पूर्ण
	rtnl_unlock();
पूर्ण

पूर्णांक रेजिस्टर_dnaddr_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&dnaddr_chain, nb);
पूर्ण

पूर्णांक unरेजिस्टर_dnaddr_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&dnaddr_chain, nb);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल अंतरभूत पूर्णांक is_dn_dev(काष्ठा net_device *dev)
अणु
	वापस dev->dn_ptr != शून्य;
पूर्ण

अटल व्योम *dn_dev_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	पूर्णांक i;
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	i = 1;
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर (!is_dn_dev(dev))
			जारी;

		अगर (i++ == *pos)
			वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *dn_dev_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा net_device *dev;

	++*pos;

	dev = v;
	अगर (v == SEQ_START_TOKEN)
		dev = net_device_entry(&init_net.dev_base_head);

	क्रम_each_netdev_जारी_rcu(&init_net, dev) अणु
		अगर (!is_dn_dev(dev))
			जारी;

		वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम dn_dev_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल अक्षर *dn_type2asc(अक्षर type)
अणु
	चयन (type) अणु
	हाल DN_DEV_BCAST:
		वापस "B";
	हाल DN_DEV_UCAST:
		वापस "U";
	हाल DN_DEV_MPOINT:
		वापस "M";
	पूर्ण

	वापस "?";
पूर्ण

अटल पूर्णांक dn_dev_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "Name     Flags T1   Timer1 T3   Timer3 BlkSize Pri State DevType    Router Peer\n");
	अन्यथा अणु
		काष्ठा net_device *dev = v;
		अक्षर peer_buf[DN_ASCBUF_LEN];
		अक्षर router_buf[DN_ASCBUF_LEN];
		काष्ठा dn_dev *dn_db = rcu_dereference(dev->dn_ptr);

		seq_म_लिखो(seq, "%-8s %1s     %04u %04u   %04lu %04lu"
				"   %04hu    %03d %02x    %-10s %-7s %-7s\n",
				dev->name,
				dn_type2asc(dn_db->parms.mode),
				0, 0,
				dn_db->t3, dn_db->parms.t3,
				mtu2blksize(dev),
				dn_db->parms.priority,
				dn_db->parms.state, dn_db->parms.name,
				dn_db->router ? dn_addr2asc(le16_to_cpu(*(__le16 *)dn_db->router->primary_key), router_buf) : "",
				dn_db->peer ? dn_addr2asc(le16_to_cpu(*(__le16 *)dn_db->peer->primary_key), peer_buf) : "");
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations dn_dev_seq_ops = अणु
	.start	= dn_dev_seq_start,
	.next	= dn_dev_seq_next,
	.stop	= dn_dev_seq_stop,
	.show	= dn_dev_seq_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल पूर्णांक addr[2];
module_param_array(addr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(addr, "The DECnet address of this machine: area,node");

व्योम __init dn_dev_init(व्योम)
अणु
	अगर (addr[0] > 63 || addr[0] < 0) अणु
		prपूर्णांकk(KERN_ERR "DECnet: Area must be between 0 and 63");
		वापस;
	पूर्ण

	अगर (addr[1] > 1023 || addr[1] < 0) अणु
		prपूर्णांकk(KERN_ERR "DECnet: Node must be between 0 and 1023");
		वापस;
	पूर्ण

	decnet_address = cpu_to_le16((addr[0] << 10) | addr[1]);

	dn_dev_devices_on();

	rtnl_रेजिस्टर_module(THIS_MODULE, PF_DECnet, RTM_NEWADDR,
			     dn_nl_newaddr, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_DECnet, RTM_DELADDR,
			     dn_nl_deladdr, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_DECnet, RTM_GETADDR,
			     शून्य, dn_nl_dump_अगरaddr, 0);

	proc_create_seq("decnet_dev", 0444, init_net.proc_net, &dn_dev_seq_ops);

#अगर_घोषित CONFIG_SYSCTL
	अणु
		पूर्णांक i;
		क्रम(i = 0; i < DN_DEV_LIST_SIZE; i++)
			dn_dev_sysctl_रेजिस्टर(शून्य, &dn_dev_list[i]);
	पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */
पूर्ण

व्योम __निकास dn_dev_cleanup(व्योम)
अणु
#अगर_घोषित CONFIG_SYSCTL
	अणु
		पूर्णांक i;
		क्रम(i = 0; i < DN_DEV_LIST_SIZE; i++)
			dn_dev_sysctl_unरेजिस्टर(&dn_dev_list[i]);
	पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

	हटाओ_proc_entry("decnet_dev", init_net.proc_net);

	dn_dev_devices_off();
पूर्ण

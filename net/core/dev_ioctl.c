<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kmod.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/wireless.h>
#समावेश <net/dsa.h>
#समावेश <net/wext.h>

/*
 *	Map an पूर्णांकerface index to its name (SIOCGIFNAME)
 */

/*
 *	We need this ioctl क्रम efficient implementation of the
 *	अगर_indextoname() function required by the IPv6 API.  Without
 *	it, we would have to search all the पूर्णांकerfaces to find a
 *	match.  --pb
 */

अटल पूर्णांक dev_अगरname(काष्ठा net *net, काष्ठा अगरreq *अगरr)
अणु
	अगरr->अगरr_name[IFNAMSIZ-1] = 0;
	वापस netdev_get_name(net, अगरr->अगरr_name, अगरr->अगरr_अगरindex);
पूर्ण

अटल gअगरconf_func_t *gअगरconf_list[NPROTO];

/**
 *	रेजिस्टर_gअगरconf	-	रेजिस्टर a SIOCGIF handler
 *	@family: Address family
 *	@gअगरconf: Function handler
 *
 *	Register protocol dependent address dumping routines. The handler
 *	that is passed must not be मुक्तd or reused until it has been replaced
 *	by another handler.
 */
पूर्णांक रेजिस्टर_gअगरconf(अचिन्हित पूर्णांक family, gअगरconf_func_t *gअगरconf)
अणु
	अगर (family >= NPROTO)
		वापस -EINVAL;
	gअगरconf_list[family] = gअगरconf;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_gअगरconf);

/*
 *	Perक्रमm a SIOCGIFCONF call. This काष्ठाure will change
 *	size eventually, and there is nothing I can करो about it.
 *	Thus we will need a 'compatibility mode'.
 */

पूर्णांक dev_अगरconf(काष्ठा net *net, काष्ठा अगरconf *अगरc, पूर्णांक size)
अणु
	काष्ठा net_device *dev;
	अक्षर __user *pos;
	पूर्णांक len;
	पूर्णांक total;
	पूर्णांक i;

	/*
	 *	Fetch the caller's info block.
	 */

	pos = अगरc->अगरc_buf;
	len = अगरc->अगरc_len;

	/*
	 *	Loop over the पूर्णांकerfaces, and ग_लिखो an info block क्रम each.
	 */

	total = 0;
	क्रम_each_netdev(net, dev) अणु
		क्रम (i = 0; i < NPROTO; i++) अणु
			अगर (gअगरconf_list[i]) अणु
				पूर्णांक करोne;
				अगर (!pos)
					करोne = gअगरconf_list[i](dev, शून्य, 0, size);
				अन्यथा
					करोne = gअगरconf_list[i](dev, pos + total,
							       len - total, size);
				अगर (करोne < 0)
					वापस -EFAULT;
				total += करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 *	All करोne.  Write the updated control block back to the caller.
	 */
	अगरc->अगरc_len = total;

	/*
	 * 	Both BSD and Solaris वापस 0 here, so we करो too.
	 */
	वापस 0;
पूर्ण

/*
 *	Perक्रमm the SIOCxIFxxx calls, inside rcu_पढ़ो_lock()
 */
अटल पूर्णांक dev_अगरsioc_locked(काष्ठा net *net, काष्ठा अगरreq *अगरr, अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक err;
	काष्ठा net_device *dev = dev_get_by_name_rcu(net, अगरr->अगरr_name);

	अगर (!dev)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल SIOCGIFFLAGS:	/* Get पूर्णांकerface flags */
		अगरr->अगरr_flags = (लघु) dev_get_flags(dev);
		वापस 0;

	हाल SIOCGIFMETRIC:	/* Get the metric on the पूर्णांकerface
				   (currently unused) */
		अगरr->अगरr_metric = 0;
		वापस 0;

	हाल SIOCGIFMTU:	/* Get the MTU of a device */
		अगरr->अगरr_mtu = dev->mtu;
		वापस 0;

	हाल SIOCGIFSLAVE:
		err = -EINVAL;
		अवरोध;

	हाल SIOCGIFMAP:
		अगरr->अगरr_map.mem_start = dev->mem_start;
		अगरr->अगरr_map.mem_end   = dev->mem_end;
		अगरr->अगरr_map.base_addr = dev->base_addr;
		अगरr->अगरr_map.irq       = dev->irq;
		अगरr->अगरr_map.dma       = dev->dma;
		अगरr->अगरr_map.port      = dev->अगर_port;
		वापस 0;

	हाल SIOCGIFINDEX:
		अगरr->अगरr_अगरindex = dev->अगरindex;
		वापस 0;

	हाल SIOCGIFTXQLEN:
		अगरr->अगरr_qlen = dev->tx_queue_len;
		वापस 0;

	शेष:
		/* dev_ioctl() should ensure this हाल
		 * is never reached
		 */
		WARN_ON(1);
		err = -ENOTTY;
		अवरोध;

	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक net_hwtstamp_validate(काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config cfg;
	क्रमागत hwtstamp_tx_types tx_type;
	क्रमागत hwtstamp_rx_filters rx_filter;
	पूर्णांक tx_type_valid = 0;
	पूर्णांक rx_filter_valid = 0;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	अगर (cfg.flags) /* reserved क्रम future extensions */
		वापस -EINVAL;

	tx_type = cfg.tx_type;
	rx_filter = cfg.rx_filter;

	चयन (tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
	हाल HWTSTAMP_TX_ON:
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
	हाल HWTSTAMP_TX_ONESTEP_P2P:
		tx_type_valid = 1;
		अवरोध;
	हाल __HWTSTAMP_TX_CNT:
		/* not a real value */
		अवरोध;
	पूर्ण

	चयन (rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		rx_filter_valid = 1;
		अवरोध;
	हाल __HWTSTAMP_FILTER_CNT:
		/* not a real value */
		अवरोध;
	पूर्ण

	अगर (!tx_type_valid || !rx_filter_valid)
		वापस -दुस्फल;

	वापस 0;
पूर्ण

अटल पूर्णांक dev_करो_ioctl(काष्ठा net_device *dev,
			काष्ठा अगरreq *अगरr, अचिन्हित पूर्णांक cmd)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	पूर्णांक err;

	err = dsa_nकरो_करो_ioctl(dev, अगरr, cmd);
	अगर (err == 0 || err != -EOPNOTSUPP)
		वापस err;

	अगर (ops->nकरो_करो_ioctl) अणु
		अगर (netअगर_device_present(dev))
			err = ops->nकरो_करो_ioctl(dev, अगरr, cmd);
		अन्यथा
			err = -ENODEV;
	पूर्ण

	वापस err;
पूर्ण

/*
 *	Perक्रमm the SIOCxIFxxx calls, inside rtnl_lock()
 */
अटल पूर्णांक dev_अगरsioc(काष्ठा net *net, काष्ठा अगरreq *अगरr, अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक err;
	काष्ठा net_device *dev = __dev_get_by_name(net, अगरr->अगरr_name);
	स्थिर काष्ठा net_device_ops *ops;

	अगर (!dev)
		वापस -ENODEV;

	ops = dev->netdev_ops;

	चयन (cmd) अणु
	हाल SIOCSIFFLAGS:	/* Set पूर्णांकerface flags */
		वापस dev_change_flags(dev, अगरr->अगरr_flags, शून्य);

	हाल SIOCSIFMETRIC:	/* Set the metric on the पूर्णांकerface
				   (currently unused) */
		वापस -EOPNOTSUPP;

	हाल SIOCSIFMTU:	/* Set the MTU of a device */
		वापस dev_set_mtu(dev, अगरr->अगरr_mtu);

	हाल SIOCSIFHWADDR:
		अगर (dev->addr_len > माप(काष्ठा sockaddr))
			वापस -EINVAL;
		वापस dev_set_mac_address_user(dev, &अगरr->अगरr_hwaddr, शून्य);

	हाल SIOCSIFHWBROADCAST:
		अगर (अगरr->अगरr_hwaddr.sa_family != dev->type)
			वापस -EINVAL;
		स_नकल(dev->broadcast, अगरr->अगरr_hwaddr.sa_data,
		       min(माप(अगरr->अगरr_hwaddr.sa_data),
			   (माप_प्रकार)dev->addr_len));
		call_netdevice_notअगरiers(NETDEV_CHANGEADDR, dev);
		वापस 0;

	हाल SIOCSIFMAP:
		अगर (ops->nकरो_set_config) अणु
			अगर (!netअगर_device_present(dev))
				वापस -ENODEV;
			वापस ops->nकरो_set_config(dev, &अगरr->अगरr_map);
		पूर्ण
		वापस -EOPNOTSUPP;

	हाल SIOCADDMULTI:
		अगर (!ops->nकरो_set_rx_mode ||
		    अगरr->अगरr_hwaddr.sa_family != AF_UNSPEC)
			वापस -EINVAL;
		अगर (!netअगर_device_present(dev))
			वापस -ENODEV;
		वापस dev_mc_add_global(dev, अगरr->अगरr_hwaddr.sa_data);

	हाल SIOCDELMULTI:
		अगर (!ops->nकरो_set_rx_mode ||
		    अगरr->अगरr_hwaddr.sa_family != AF_UNSPEC)
			वापस -EINVAL;
		अगर (!netअगर_device_present(dev))
			वापस -ENODEV;
		वापस dev_mc_del_global(dev, अगरr->अगरr_hwaddr.sa_data);

	हाल SIOCSIFTXQLEN:
		अगर (अगरr->अगरr_qlen < 0)
			वापस -EINVAL;
		वापस dev_change_tx_queue_len(dev, अगरr->अगरr_qlen);

	हाल SIOCSIFNAME:
		अगरr->अगरr_newname[IFNAMSIZ-1] = '\0';
		वापस dev_change_name(dev, अगरr->अगरr_newname);

	हाल SIOCSHWTSTAMP:
		err = net_hwtstamp_validate(अगरr);
		अगर (err)
			वापस err;
		fallthrough;

	/*
	 *	Unknown or निजी ioctl
	 */
	शेष:
		अगर ((cmd >= SIOCDEVPRIVATE &&
		    cmd <= SIOCDEVPRIVATE + 15) ||
		    cmd == SIOCBONDENSLAVE ||
		    cmd == SIOCBONDRELEASE ||
		    cmd == SIOCBONDSETHWADDR ||
		    cmd == SIOCBONDSLAVEINFOQUERY ||
		    cmd == SIOCBONDINFOQUERY ||
		    cmd == SIOCBONDCHANGEACTIVE ||
		    cmd == SIOCGMIIPHY ||
		    cmd == SIOCGMIIREG ||
		    cmd == SIOCSMIIREG ||
		    cmd == SIOCBRADDIF ||
		    cmd == SIOCBRDELIF ||
		    cmd == SIOCSHWTSTAMP ||
		    cmd == SIOCGHWTSTAMP ||
		    cmd == SIOCWANDEV) अणु
			err = dev_करो_ioctl(dev, अगरr, cmd);
		पूर्ण अन्यथा
			err = -EINVAL;

	पूर्ण
	वापस err;
पूर्ण

/**
 *	dev_load 	- load a network module
 *	@net: the applicable net namespace
 *	@name: name of पूर्णांकerface
 *
 *	If a network पूर्णांकerface is not present and the process has suitable
 *	privileges this function loads the module. If module loading is not
 *	available in this kernel then it becomes a nop.
 */

व्योम dev_load(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा net_device *dev;
	पूर्णांक no_module;

	rcu_पढ़ो_lock();
	dev = dev_get_by_name_rcu(net, name);
	rcu_पढ़ो_unlock();

	no_module = !dev;
	अगर (no_module && capable(CAP_NET_ADMIN))
		no_module = request_module("netdev-%s", name);
	अगर (no_module && capable(CAP_SYS_MODULE))
		request_module("%s", name);
पूर्ण
EXPORT_SYMBOL(dev_load);

/*
 *	This function handles all "interface"-type I/O control requests. The actual
 *	'doing' part of this is dev_अगरsioc above.
 */

/**
 *	dev_ioctl	-	network device ioctl
 *	@net: the applicable net namespace
 *	@cmd: command to issue
 *	@अगरr: poपूर्णांकer to a काष्ठा अगरreq in user space
 *	@need_copyout: whether or not copy_to_user() should be called
 *
 *	Issue ioctl functions to devices. This is normally called by the
 *	user space syscall पूर्णांकerfaces but can someबार be useful क्रम
 *	other purposes. The वापस value is the वापस from the syscall अगर
 *	positive or a negative त्रुटि_सं code on error.
 */

पूर्णांक dev_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, काष्ठा अगरreq *अगरr, bool *need_copyout)
अणु
	पूर्णांक ret;
	अक्षर *colon;

	अगर (need_copyout)
		*need_copyout = true;
	अगर (cmd == SIOCGIFNAME)
		वापस dev_अगरname(net, अगरr);

	अगरr->अगरr_name[IFNAMSIZ-1] = 0;

	colon = म_अक्षर(अगरr->अगरr_name, ':');
	अगर (colon)
		*colon = 0;

	/*
	 *	See which पूर्णांकerface the caller is talking about.
	 */

	चयन (cmd) अणु
	हाल SIOCGIFHWADDR:
		dev_load(net, अगरr->अगरr_name);
		ret = dev_get_mac_address(&अगरr->अगरr_hwaddr, net, अगरr->अगरr_name);
		अगर (colon)
			*colon = ':';
		वापस ret;
	/*
	 *	These ioctl calls:
	 *	- can be करोne by all.
	 *	- atomic and करो not require locking.
	 *	- वापस a value
	 */
	हाल SIOCGIFFLAGS:
	हाल SIOCGIFMETRIC:
	हाल SIOCGIFMTU:
	हाल SIOCGIFSLAVE:
	हाल SIOCGIFMAP:
	हाल SIOCGIFINDEX:
	हाल SIOCGIFTXQLEN:
		dev_load(net, अगरr->अगरr_name);
		rcu_पढ़ो_lock();
		ret = dev_अगरsioc_locked(net, अगरr, cmd);
		rcu_पढ़ो_unlock();
		अगर (colon)
			*colon = ':';
		वापस ret;

	हाल SIOCETHTOOL:
		dev_load(net, अगरr->अगरr_name);
		rtnl_lock();
		ret = dev_ethtool(net, अगरr);
		rtnl_unlock();
		अगर (colon)
			*colon = ':';
		वापस ret;

	/*
	 *	These ioctl calls:
	 *	- require superuser घातer.
	 *	- require strict serialization.
	 *	- वापस a value
	 */
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSIFNAME:
		dev_load(net, अगरr->अगरr_name);
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
		rtnl_lock();
		ret = dev_अगरsioc(net, अगरr, cmd);
		rtnl_unlock();
		अगर (colon)
			*colon = ':';
		वापस ret;

	/*
	 *	These ioctl calls:
	 *	- require superuser घातer.
	 *	- require strict serialization.
	 *	- करो not वापस a value
	 */
	हाल SIOCSIFMAP:
	हाल SIOCSIFTXQLEN:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		fallthrough;
	/*
	 *	These ioctl calls:
	 *	- require local superuser घातer.
	 *	- require strict serialization.
	 *	- करो not वापस a value
	 */
	हाल SIOCSIFFLAGS:
	हाल SIOCSIFMETRIC:
	हाल SIOCSIFMTU:
	हाल SIOCSIFHWADDR:
	हाल SIOCSIFSLAVE:
	हाल SIOCADDMULTI:
	हाल SIOCDELMULTI:
	हाल SIOCSIFHWBROADCAST:
	हाल SIOCSMIIREG:
	हाल SIOCBONDENSLAVE:
	हाल SIOCBONDRELEASE:
	हाल SIOCBONDSETHWADDR:
	हाल SIOCBONDCHANGEACTIVE:
	हाल SIOCBRADDIF:
	हाल SIOCBRDELIF:
	हाल SIOCSHWTSTAMP:
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
		fallthrough;
	हाल SIOCBONDSLAVEINFOQUERY:
	हाल SIOCBONDINFOQUERY:
		dev_load(net, अगरr->अगरr_name);
		rtnl_lock();
		ret = dev_अगरsioc(net, अगरr, cmd);
		rtnl_unlock();
		अगर (need_copyout)
			*need_copyout = false;
		वापस ret;

	हाल SIOCGIFMEM:
		/* Get the per device memory space. We can add this but
		 * currently करो not support it */
	हाल SIOCSIFMEM:
		/* Set the per device memory buffer space.
		 * Not applicable in our हाल */
	हाल SIOCSIFLINK:
		वापस -ENOTTY;

	/*
	 *	Unknown or निजी ioctl.
	 */
	शेष:
		अगर (cmd == SIOCWANDEV ||
		    cmd == SIOCGHWTSTAMP ||
		    (cmd >= SIOCDEVPRIVATE &&
		     cmd <= SIOCDEVPRIVATE + 15)) अणु
			dev_load(net, अगरr->अगरr_name);
			rtnl_lock();
			ret = dev_अगरsioc(net, अगरr, cmd);
			rtnl_unlock();
			वापस ret;
		पूर्ण
		वापस -ENOTTY;
	पूर्ण
पूर्ण

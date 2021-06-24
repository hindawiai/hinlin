<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      NET3    Protocol independent device support routines.
 *
 *	Derived from the non IP parts of dev.c 1.0.19
 *              Authors:	Ross Biro
 *				Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *				Mark Evans, <evansmp@uhura.aston.ac.uk>
 *
 *	Additional Authors:
 *		Florian la Roche <rzsfl@rz.uni-sb.de>
 *		Alan Cox <gw4pts@gw4pts.ampr.org>
 *		David Hinds <dahinds@users.sourceक्रमge.net>
 *		Alexey Kuznetsov <kuznet@ms2.inr.ac.ru>
 *		Adam Sulmicki <adam@cfar.umd.edu>
 *              Pekka Riikonen <priikone@poesiकरोn.pspt.fi>
 *
 *	Changes:
 *              D.J. Barrow     :       Fixed bug where dev->refcnt माला_लो set
 *                                      to 2 अगर रेजिस्टर_netdev माला_लो called
 *                                      beक्रमe net_dev_init & also हटाओd a
 *                                      few lines of code in the process.
 *		Alan Cox	:	device निजी ioctl copies fields back.
 *		Alan Cox	:	Transmit queue code करोes relevant
 *					stunts to keep the queue safe.
 *		Alan Cox	:	Fixed द्विगुन lock.
 *		Alan Cox	:	Fixed promisc शून्य poपूर्णांकer trap
 *		????????	:	Support the full निजी ioctl range
 *		Alan Cox	:	Moved ioctl permission check पूर्णांकo
 *					drivers
 *		Tim Kordas	:	SIOCADDMULTI/SIOCDELMULTI
 *		Alan Cox	:	100 backlog just करोesn't cut it when
 *					you start करोing multicast video 8)
 *		Alan Cox	:	Rewrote net_bh and list manager.
 *              Alan Cox        :       Fix ETH_P_ALL echoback lengths.
 *		Alan Cox	:	Took out transmit every packet pass
 *					Saved a few bytes in the ioctl handler
 *		Alan Cox	:	Network driver sets packet type beक्रमe
 *					calling netअगर_rx. Saves a function
 *					call a packet.
 *		Alan Cox	:	Hashed net_bh()
 *		Riअक्षरd Kooijman:	Timestamp fixes.
 *		Alan Cox	:	Wrong field in SIOCGIFDSTADDR
 *		Alan Cox	:	Device lock protection.
 *              Alan Cox        :       Fixed nasty side effect of device बंद
 *					changes.
 *		Rudi Cilibrasi	:	Pass the right thing to
 *					set_mac_address()
 *		Dave Miller	:	32bit quantity क्रम the device lock to
 *					make it work out on a Sparc.
 *		Bjorn Ekwall	:	Added KERNELD hack.
 *		Alan Cox	:	Cleaned up the backlog initialise.
 *		Craig Metz	:	SIOCGIFCONF fix अगर space क्रम under
 *					1 device.
 *	    Thomas Bogenकरोerfer :	Return ENODEV क्रम dev_खोलो, अगर there
 *					is no device खोलो function.
 *		Andi Kleen	:	Fix error reporting क्रम SIOCGIFCONF
 *	    Michael Chastain	:	Fix चिन्हित/अचिन्हित क्रम SIOCGIFCONF
 *		Cyrus Durgin	:	Cleaned क्रम KMOD
 *		Adam Sulmicki   :	Bug Fix : Network Device Unload
 *					A network device unload needs to purge
 *					the backlog queue.
 *	Paul Rusty Russell	:	SIOCSIFNAME
 *              Pekka Riikonen  :	Netdev boot-समय settings code
 *              Andrew Morton   :       Make unरेजिस्टर_netdevice रुको
 *                                      indefinitely on dev->refcnt
 *              J Hadi Salim    :       - Backlog queue sampling
 *				        - netअगर_rx() feedback
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/capability.h>
#समावेश <linux/cpu.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hash.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/busy_poll.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/स्थिति.स>
#समावेश <net/dsa.h>
#समावेश <net/dst.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/gro.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/checksum.h>
#समावेश <net/xfrm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/delay.h>
#समावेश <net/iw_handler.h>
#समावेश <यंत्र/current.h>
#समावेश <linux/audit.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>
#समावेश <net/mpls.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अक्रमom.h>
#समावेश <trace/events/napi.h>
#समावेश <trace/events/net.h>
#समावेश <trace/events/skb.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/cpu_rmap.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अगर_macvlan.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/netfilter_ingress.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/sctp.h>
#समावेश <net/udp_tunnel.h>
#समावेश <linux/net_namespace.h>
#समावेश <linux/indirect_call_wrapper.h>
#समावेश <net/devlink.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pअक्रमom.h>

#समावेश "net-sysfs.h"

#घोषणा MAX_GRO_SKBS 8

/* This should be increased अगर a protocol with a bigger head is added. */
#घोषणा GRO_MAX_HEAD (MAX_HEADER + 128)

अटल DEFINE_SPINLOCK(ptype_lock);
अटल DEFINE_SPINLOCK(offload_lock);
काष्ठा list_head ptype_base[PTYPE_HASH_SIZE] __पढ़ो_mostly;
काष्ठा list_head ptype_all __पढ़ो_mostly;	/* Taps */
अटल काष्ठा list_head offload_base __पढ़ो_mostly;

अटल पूर्णांक netअगर_rx_पूर्णांकernal(काष्ठा sk_buff *skb);
अटल पूर्णांक call_netdevice_notअगरiers_info(अचिन्हित दीर्घ val,
					 काष्ठा netdev_notअगरier_info *info);
अटल पूर्णांक call_netdevice_notअगरiers_extack(अचिन्हित दीर्घ val,
					   काष्ठा net_device *dev,
					   काष्ठा netlink_ext_ack *extack);
अटल काष्ठा napi_काष्ठा *napi_by_id(अचिन्हित पूर्णांक napi_id);

/*
 * The @dev_base_head list is रक्षित by @dev_base_lock and the rtnl
 * semaphore.
 *
 * Pure पढ़ोers hold dev_base_lock क्रम पढ़ोing, or rcu_पढ़ो_lock()
 *
 * Writers must hold the rtnl semaphore जबतक they loop through the
 * dev_base_head list, and hold dev_base_lock क्रम writing when they करो the
 * actual updates.  This allows pure पढ़ोers to access the list even
 * जबतक a ग_लिखोr is preparing to update it.
 *
 * To put it another way, dev_base_lock is held क्रम writing only to
 * protect against pure पढ़ोers; the rtnl semaphore provides the
 * protection against other ग_लिखोrs.
 *
 * See, क्रम example usages, रेजिस्टर_netdevice() and
 * unरेजिस्टर_netdevice(), which must be called with the rtnl
 * semaphore held.
 */
DEFINE_RWLOCK(dev_base_lock);
EXPORT_SYMBOL(dev_base_lock);

अटल DEFINE_MUTEX(अगरalias_mutex);

/* protects napi_hash addition/deletion and napi_gen_id */
अटल DEFINE_SPINLOCK(napi_hash_lock);

अटल अचिन्हित पूर्णांक napi_gen_id = NR_CPUS;
अटल DEFINE_READ_MOSTLY_HASHTABLE(napi_hash, 8);

अटल DECLARE_RWSEM(devnet_नाम_sem);

अटल अंतरभूत व्योम dev_base_seq_inc(काष्ठा net *net)
अणु
	जबतक (++net->dev_base_seq == 0)
		;
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *dev_name_hash(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक hash = full_name_hash(net, name, strnlen(name, IFNAMSIZ));

	वापस &net->dev_name_head[hash_32(hash, NETDEV_HASHBITS)];
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *dev_index_hash(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	वापस &net->dev_index_head[अगरindex & (NETDEV_HASHENTRIES - 1)];
पूर्ण

अटल अंतरभूत व्योम rps_lock(काष्ठा softnet_data *sd)
अणु
#अगर_घोषित CONFIG_RPS
	spin_lock(&sd->input_pkt_queue.lock);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम rps_unlock(काष्ठा softnet_data *sd)
अणु
#अगर_घोषित CONFIG_RPS
	spin_unlock(&sd->input_pkt_queue.lock);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा netdev_name_node *netdev_name_node_alloc(काष्ठा net_device *dev,
						       स्थिर अक्षर *name)
अणु
	काष्ठा netdev_name_node *name_node;

	name_node = kदो_स्मृति(माप(*name_node), GFP_KERNEL);
	अगर (!name_node)
		वापस शून्य;
	INIT_HLIST_NODE(&name_node->hlist);
	name_node->dev = dev;
	name_node->name = name;
	वापस name_node;
पूर्ण

अटल काष्ठा netdev_name_node *
netdev_name_node_head_alloc(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_name_node *name_node;

	name_node = netdev_name_node_alloc(dev, dev->name);
	अगर (!name_node)
		वापस शून्य;
	INIT_LIST_HEAD(&name_node->list);
	वापस name_node;
पूर्ण

अटल व्योम netdev_name_node_मुक्त(काष्ठा netdev_name_node *name_node)
अणु
	kमुक्त(name_node);
पूर्ण

अटल व्योम netdev_name_node_add(काष्ठा net *net,
				 काष्ठा netdev_name_node *name_node)
अणु
	hlist_add_head_rcu(&name_node->hlist,
			   dev_name_hash(net, name_node->name));
पूर्ण

अटल व्योम netdev_name_node_del(काष्ठा netdev_name_node *name_node)
अणु
	hlist_del_rcu(&name_node->hlist);
पूर्ण

अटल काष्ठा netdev_name_node *netdev_name_node_lookup(काष्ठा net *net,
							स्थिर अक्षर *name)
अणु
	काष्ठा hlist_head *head = dev_name_hash(net, name);
	काष्ठा netdev_name_node *name_node;

	hlist_क्रम_each_entry(name_node, head, hlist)
		अगर (!म_भेद(name_node->name, name))
			वापस name_node;
	वापस शून्य;
पूर्ण

अटल काष्ठा netdev_name_node *netdev_name_node_lookup_rcu(काष्ठा net *net,
							    स्थिर अक्षर *name)
अणु
	काष्ठा hlist_head *head = dev_name_hash(net, name);
	काष्ठा netdev_name_node *name_node;

	hlist_क्रम_each_entry_rcu(name_node, head, hlist)
		अगर (!म_भेद(name_node->name, name))
			वापस name_node;
	वापस शून्य;
पूर्ण

पूर्णांक netdev_name_node_alt_create(काष्ठा net_device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा netdev_name_node *name_node;
	काष्ठा net *net = dev_net(dev);

	name_node = netdev_name_node_lookup(net, name);
	अगर (name_node)
		वापस -EEXIST;
	name_node = netdev_name_node_alloc(dev, name);
	अगर (!name_node)
		वापस -ENOMEM;
	netdev_name_node_add(net, name_node);
	/* The node that holds dev->name acts as a head of per-device list. */
	list_add_tail(&name_node->list, &dev->name_node->list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_name_node_alt_create);

अटल व्योम __netdev_name_node_alt_destroy(काष्ठा netdev_name_node *name_node)
अणु
	list_del(&name_node->list);
	netdev_name_node_del(name_node);
	kमुक्त(name_node->name);
	netdev_name_node_मुक्त(name_node);
पूर्ण

पूर्णांक netdev_name_node_alt_destroy(काष्ठा net_device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा netdev_name_node *name_node;
	काष्ठा net *net = dev_net(dev);

	name_node = netdev_name_node_lookup(net, name);
	अगर (!name_node)
		वापस -ENOENT;
	/* lookup might have found our primary name or a name beदीर्घing
	 * to another device.
	 */
	अगर (name_node == dev->name_node || name_node->dev != dev)
		वापस -EINVAL;

	__netdev_name_node_alt_destroy(name_node);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_name_node_alt_destroy);

अटल व्योम netdev_name_node_alt_flush(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_name_node *name_node, *पंचांगp;

	list_क्रम_each_entry_safe(name_node, पंचांगp, &dev->name_node->list, list)
		__netdev_name_node_alt_destroy(name_node);
पूर्ण

/* Device list insertion */
अटल व्योम list_netdevice(काष्ठा net_device *dev)
अणु
	काष्ठा net *net = dev_net(dev);

	ASSERT_RTNL();

	ग_लिखो_lock_bh(&dev_base_lock);
	list_add_tail_rcu(&dev->dev_list, &net->dev_base_head);
	netdev_name_node_add(net, dev->name_node);
	hlist_add_head_rcu(&dev->index_hlist,
			   dev_index_hash(net, dev->अगरindex));
	ग_लिखो_unlock_bh(&dev_base_lock);

	dev_base_seq_inc(net);
पूर्ण

/* Device list removal
 * caller must respect a RCU grace period beक्रमe मुक्तing/reusing dev
 */
अटल व्योम unlist_netdevice(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();

	/* Unlink dev from the device chain */
	ग_लिखो_lock_bh(&dev_base_lock);
	list_del_rcu(&dev->dev_list);
	netdev_name_node_del(dev->name_node);
	hlist_del_rcu(&dev->index_hlist);
	ग_लिखो_unlock_bh(&dev_base_lock);

	dev_base_seq_inc(dev_net(dev));
पूर्ण

/*
 *	Our notअगरier list
 */

अटल RAW_NOTIFIER_HEAD(netdev_chain);

/*
 *	Device drivers call our routines to queue packets here. We empty the
 *	queue in the local softnet handler.
 */

DEFINE_PER_CPU_ALIGNED(काष्ठा softnet_data, softnet_data);
EXPORT_PER_CPU_SYMBOL(softnet_data);

#अगर_घोषित CONFIG_LOCKDEP
/*
 * रेजिस्टर_netdevice() inits txq->_xmit_lock and sets lockdep class
 * according to dev->type
 */
अटल स्थिर अचिन्हित लघु netdev_lock_type[] = अणु
	 ARPHRD_NETROM, ARPHRD_ETHER, ARPHRD_EETHER, ARPHRD_AX25,
	 ARPHRD_PRONET, ARPHRD_CHAOS, ARPHRD_IEEE802, ARPHRD_ARCNET,
	 ARPHRD_APPLETLK, ARPHRD_DLCI, ARPHRD_ATM, ARPHRD_METRICOM,
	 ARPHRD_IEEE1394, ARPHRD_EUI64, ARPHRD_INFINIBAND, ARPHRD_SLIP,
	 ARPHRD_CSLIP, ARPHRD_SLIP6, ARPHRD_CSLIP6, ARPHRD_RSRVD,
	 ARPHRD_ADAPT, ARPHRD_ROSE, ARPHRD_X25, ARPHRD_HWX25,
	 ARPHRD_PPP, ARPHRD_CISCO, ARPHRD_LAPB, ARPHRD_DDCMP,
	 ARPHRD_RAWHDLC, ARPHRD_TUNNEL, ARPHRD_TUNNEL6, ARPHRD_FRAD,
	 ARPHRD_SKIP, ARPHRD_LOOPBACK, ARPHRD_LOCALTLK, ARPHRD_FDDI,
	 ARPHRD_BIF, ARPHRD_SIT, ARPHRD_IPDDP, ARPHRD_IPGRE,
	 ARPHRD_PIMREG, ARPHRD_HIPPI, ARPHRD_ASH, ARPHRD_ECONET,
	 ARPHRD_IRDA, ARPHRD_FCPP, ARPHRD_FCAL, ARPHRD_FCPL,
	 ARPHRD_FCFABRIC, ARPHRD_IEEE80211, ARPHRD_IEEE80211_PRISM,
	 ARPHRD_IEEE80211_RADIOTAP, ARPHRD_PHONET, ARPHRD_PHONET_PIPE,
	 ARPHRD_IEEE802154, ARPHRD_VOID, ARPHRD_NONEपूर्ण;

अटल स्थिर अक्षर *स्थिर netdev_lock_name[] = अणु
	"_xmit_NETROM", "_xmit_ETHER", "_xmit_EETHER", "_xmit_AX25",
	"_xmit_PRONET", "_xmit_CHAOS", "_xmit_IEEE802", "_xmit_ARCNET",
	"_xmit_APPLETLK", "_xmit_DLCI", "_xmit_ATM", "_xmit_METRICOM",
	"_xmit_IEEE1394", "_xmit_EUI64", "_xmit_INFINIBAND", "_xmit_SLIP",
	"_xmit_CSLIP", "_xmit_SLIP6", "_xmit_CSLIP6", "_xmit_RSRVD",
	"_xmit_ADAPT", "_xmit_ROSE", "_xmit_X25", "_xmit_HWX25",
	"_xmit_PPP", "_xmit_CISCO", "_xmit_LAPB", "_xmit_DDCMP",
	"_xmit_RAWHDLC", "_xmit_TUNNEL", "_xmit_TUNNEL6", "_xmit_FRAD",
	"_xmit_SKIP", "_xmit_LOOPBACK", "_xmit_LOCALTLK", "_xmit_FDDI",
	"_xmit_BIF", "_xmit_SIT", "_xmit_IPDDP", "_xmit_IPGRE",
	"_xmit_PIMREG", "_xmit_HIPPI", "_xmit_ASH", "_xmit_ECONET",
	"_xmit_IRDA", "_xmit_FCPP", "_xmit_FCAL", "_xmit_FCPL",
	"_xmit_FCFABRIC", "_xmit_IEEE80211", "_xmit_IEEE80211_PRISM",
	"_xmit_IEEE80211_RADIOTAP", "_xmit_PHONET", "_xmit_PHONET_PIPE",
	"_xmit_IEEE802154", "_xmit_VOID", "_xmit_NONE"पूर्ण;

अटल काष्ठा lock_class_key netdev_xmit_lock_key[ARRAY_SIZE(netdev_lock_type)];
अटल काष्ठा lock_class_key netdev_addr_lock_key[ARRAY_SIZE(netdev_lock_type)];

अटल अंतरभूत अचिन्हित लघु netdev_lock_pos(अचिन्हित लघु dev_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(netdev_lock_type); i++)
		अगर (netdev_lock_type[i] == dev_type)
			वापस i;
	/* the last key is used by शेष */
	वापस ARRAY_SIZE(netdev_lock_type) - 1;
पूर्ण

अटल अंतरभूत व्योम netdev_set_xmit_lockdep_class(spinlock_t *lock,
						 अचिन्हित लघु dev_type)
अणु
	पूर्णांक i;

	i = netdev_lock_pos(dev_type);
	lockdep_set_class_and_name(lock, &netdev_xmit_lock_key[i],
				   netdev_lock_name[i]);
पूर्ण

अटल अंतरभूत व्योम netdev_set_addr_lockdep_class(काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	i = netdev_lock_pos(dev->type);
	lockdep_set_class_and_name(&dev->addr_list_lock,
				   &netdev_addr_lock_key[i],
				   netdev_lock_name[i]);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम netdev_set_xmit_lockdep_class(spinlock_t *lock,
						 अचिन्हित लघु dev_type)
अणु
पूर्ण

अटल अंतरभूत व्योम netdev_set_addr_lockdep_class(काष्ठा net_device *dev)
अणु
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 *		Protocol management and registration routines
 *
 *******************************************************************************/


/*
 *	Add a protocol ID to the list. Now that the input handler is
 *	smarter we can dispense with all the messy stuff that used to be
 *	here.
 *
 *	BEWARE!!! Protocol handlers, mangling input packets,
 *	MUST BE last in hash buckets and checking protocol handlers
 *	MUST start from promiscuous ptype_all chain in net_bh.
 *	It is true now, करो not change it.
 *	Explanation follows: अगर protocol handler, mangling packet, will
 *	be the first on list, it is not able to sense, that packet
 *	is cloned and should be copied-on-ग_लिखो, so that it will
 *	change it and subsequent पढ़ोers will get broken packet.
 *							--ANK (980803)
 */

अटल अंतरभूत काष्ठा list_head *ptype_head(स्थिर काष्ठा packet_type *pt)
अणु
	अगर (pt->type == htons(ETH_P_ALL))
		वापस pt->dev ? &pt->dev->ptype_all : &ptype_all;
	अन्यथा
		वापस pt->dev ? &pt->dev->ptype_specअगरic :
				 &ptype_base[ntohs(pt->type) & PTYPE_HASH_MASK];
पूर्ण

/**
 *	dev_add_pack - add packet handler
 *	@pt: packet type declaration
 *
 *	Add a protocol handler to the networking stack. The passed &packet_type
 *	is linked पूर्णांकo kernel lists and may not be मुक्तd until it has been
 *	हटाओd from the kernel lists.
 *
 *	This call करोes not sleep thereक्रमe it can not
 *	guarantee all CPU's that are in middle of receiving packets
 *	will see the new packet type (until the next received packet).
 */

व्योम dev_add_pack(काष्ठा packet_type *pt)
अणु
	काष्ठा list_head *head = ptype_head(pt);

	spin_lock(&ptype_lock);
	list_add_rcu(&pt->list, head);
	spin_unlock(&ptype_lock);
पूर्ण
EXPORT_SYMBOL(dev_add_pack);

/**
 *	__dev_हटाओ_pack	 - हटाओ packet handler
 *	@pt: packet type declaration
 *
 *	Remove a protocol handler that was previously added to the kernel
 *	protocol handlers by dev_add_pack(). The passed &packet_type is हटाओd
 *	from the kernel lists and can be मुक्तd or reused once this function
 *	वापसs.
 *
 *      The packet type might still be in use by receivers
 *	and must not be मुक्तd until after all the CPU's have gone
 *	through a quiescent state.
 */
व्योम __dev_हटाओ_pack(काष्ठा packet_type *pt)
अणु
	काष्ठा list_head *head = ptype_head(pt);
	काष्ठा packet_type *pt1;

	spin_lock(&ptype_lock);

	list_क्रम_each_entry(pt1, head, list) अणु
		अगर (pt == pt1) अणु
			list_del_rcu(&pt->list);
			जाओ out;
		पूर्ण
	पूर्ण

	pr_warn("dev_remove_pack: %p not found\n", pt);
out:
	spin_unlock(&ptype_lock);
पूर्ण
EXPORT_SYMBOL(__dev_हटाओ_pack);

/**
 *	dev_हटाओ_pack	 - हटाओ packet handler
 *	@pt: packet type declaration
 *
 *	Remove a protocol handler that was previously added to the kernel
 *	protocol handlers by dev_add_pack(). The passed &packet_type is हटाओd
 *	from the kernel lists and can be मुक्तd or reused once this function
 *	वापसs.
 *
 *	This call sleeps to guarantee that no CPU is looking at the packet
 *	type after वापस.
 */
व्योम dev_हटाओ_pack(काष्ठा packet_type *pt)
अणु
	__dev_हटाओ_pack(pt);

	synchronize_net();
पूर्ण
EXPORT_SYMBOL(dev_हटाओ_pack);


/**
 *	dev_add_offload - रेजिस्टर offload handlers
 *	@po: protocol offload declaration
 *
 *	Add protocol offload handlers to the networking stack. The passed
 *	&proto_offload is linked पूर्णांकo kernel lists and may not be मुक्तd until
 *	it has been हटाओd from the kernel lists.
 *
 *	This call करोes not sleep thereक्रमe it can not
 *	guarantee all CPU's that are in middle of receiving packets
 *	will see the new offload handlers (until the next received packet).
 */
व्योम dev_add_offload(काष्ठा packet_offload *po)
अणु
	काष्ठा packet_offload *elem;

	spin_lock(&offload_lock);
	list_क्रम_each_entry(elem, &offload_base, list) अणु
		अगर (po->priority < elem->priority)
			अवरोध;
	पूर्ण
	list_add_rcu(&po->list, elem->list.prev);
	spin_unlock(&offload_lock);
पूर्ण
EXPORT_SYMBOL(dev_add_offload);

/**
 *	__dev_हटाओ_offload	 - हटाओ offload handler
 *	@po: packet offload declaration
 *
 *	Remove a protocol offload handler that was previously added to the
 *	kernel offload handlers by dev_add_offload(). The passed &offload_type
 *	is हटाओd from the kernel lists and can be मुक्तd or reused once this
 *	function वापसs.
 *
 *      The packet type might still be in use by receivers
 *	and must not be मुक्तd until after all the CPU's have gone
 *	through a quiescent state.
 */
अटल व्योम __dev_हटाओ_offload(काष्ठा packet_offload *po)
अणु
	काष्ठा list_head *head = &offload_base;
	काष्ठा packet_offload *po1;

	spin_lock(&offload_lock);

	list_क्रम_each_entry(po1, head, list) अणु
		अगर (po == po1) अणु
			list_del_rcu(&po->list);
			जाओ out;
		पूर्ण
	पूर्ण

	pr_warn("dev_remove_offload: %p not found\n", po);
out:
	spin_unlock(&offload_lock);
पूर्ण

/**
 *	dev_हटाओ_offload	 - हटाओ packet offload handler
 *	@po: packet offload declaration
 *
 *	Remove a packet offload handler that was previously added to the kernel
 *	offload handlers by dev_add_offload(). The passed &offload_type is
 *	हटाओd from the kernel lists and can be मुक्तd or reused once this
 *	function वापसs.
 *
 *	This call sleeps to guarantee that no CPU is looking at the packet
 *	type after वापस.
 */
व्योम dev_हटाओ_offload(काष्ठा packet_offload *po)
अणु
	__dev_हटाओ_offload(po);

	synchronize_net();
पूर्ण
EXPORT_SYMBOL(dev_हटाओ_offload);

/******************************************************************************
 *
 *		      Device Boot-समय Settings Routines
 *
 ******************************************************************************/

/* Boot समय configuration table */
अटल काष्ठा netdev_boot_setup dev_boot_setup[NETDEV_BOOT_SETUP_MAX];

/**
 *	netdev_boot_setup_add	- add new setup entry
 *	@name: name of the device
 *	@map: configured settings क्रम the device
 *
 *	Adds new setup entry to the dev_boot_setup list.  The function
 *	वापसs 0 on error and 1 on success.  This is a generic routine to
 *	all netdevices.
 */
अटल पूर्णांक netdev_boot_setup_add(अक्षर *name, काष्ठा अगरmap *map)
अणु
	काष्ठा netdev_boot_setup *s;
	पूर्णांक i;

	s = dev_boot_setup;
	क्रम (i = 0; i < NETDEV_BOOT_SETUP_MAX; i++) अणु
		अगर (s[i].name[0] == '\0' || s[i].name[0] == ' ') अणु
			स_रखो(s[i].name, 0, माप(s[i].name));
			strlcpy(s[i].name, name, IFNAMSIZ);
			स_नकल(&s[i].map, map, माप(s[i].map));
			अवरोध;
		पूर्ण
	पूर्ण

	वापस i >= NETDEV_BOOT_SETUP_MAX ? 0 : 1;
पूर्ण

/**
 * netdev_boot_setup_check	- check boot समय settings
 * @dev: the netdevice
 *
 * Check boot समय settings क्रम the device.
 * The found settings are set क्रम the device to be used
 * later in the device probing.
 * Returns 0 अगर no settings found, 1 अगर they are.
 */
पूर्णांक netdev_boot_setup_check(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_boot_setup *s = dev_boot_setup;
	पूर्णांक i;

	क्रम (i = 0; i < NETDEV_BOOT_SETUP_MAX; i++) अणु
		अगर (s[i].name[0] != '\0' && s[i].name[0] != ' ' &&
		    !म_भेद(dev->name, s[i].name)) अणु
			dev->irq = s[i].map.irq;
			dev->base_addr = s[i].map.base_addr;
			dev->mem_start = s[i].map.mem_start;
			dev->mem_end = s[i].map.mem_end;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_boot_setup_check);


/**
 * netdev_boot_base	- get address from boot समय settings
 * @prefix: prefix क्रम network device
 * @unit: id क्रम network device
 *
 * Check boot समय settings क्रम the base address of device.
 * The found settings are set क्रम the device to be used
 * later in the device probing.
 * Returns 0 अगर no settings found.
 */
अचिन्हित दीर्घ netdev_boot_base(स्थिर अक्षर *prefix, पूर्णांक unit)
अणु
	स्थिर काष्ठा netdev_boot_setup *s = dev_boot_setup;
	अक्षर name[IFNAMSIZ];
	पूर्णांक i;

	प्र_लिखो(name, "%s%d", prefix, unit);

	/*
	 * If device alपढ़ोy रेजिस्टरed then वापस base of 1
	 * to indicate not to probe क्रम this पूर्णांकerface
	 */
	अगर (__dev_get_by_name(&init_net, name))
		वापस 1;

	क्रम (i = 0; i < NETDEV_BOOT_SETUP_MAX; i++)
		अगर (!म_भेद(name, s[i].name))
			वापस s[i].map.base_addr;
	वापस 0;
पूर्ण

/*
 * Saves at boot समय configured settings क्रम any netdevice.
 */
पूर्णांक __init netdev_boot_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[5];
	काष्ठा अगरmap map;

	str = get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);
	अगर (!str || !*str)
		वापस 0;

	/* Save settings */
	स_रखो(&map, 0, माप(map));
	अगर (पूर्णांकs[0] > 0)
		map.irq = पूर्णांकs[1];
	अगर (पूर्णांकs[0] > 1)
		map.base_addr = पूर्णांकs[2];
	अगर (पूर्णांकs[0] > 2)
		map.mem_start = पूर्णांकs[3];
	अगर (पूर्णांकs[0] > 3)
		map.mem_end = पूर्णांकs[4];

	/* Add new entry to the list */
	वापस netdev_boot_setup_add(str, &map);
पूर्ण

__setup("netdev=", netdev_boot_setup);

/*******************************************************************************
 *
 *			    Device Interface Subroutines
 *
 *******************************************************************************/

/**
 *	dev_get_अगरlink	- get 'iflink' value of a पूर्णांकerface
 *	@dev: targeted पूर्णांकerface
 *
 *	Indicates the अगरindex the पूर्णांकerface is linked to.
 *	Physical पूर्णांकerfaces have the same 'ifindex' and 'iflink' values.
 */

पूर्णांक dev_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	अगर (dev->netdev_ops && dev->netdev_ops->nकरो_get_अगरlink)
		वापस dev->netdev_ops->nकरो_get_अगरlink(dev);

	वापस dev->अगरindex;
पूर्ण
EXPORT_SYMBOL(dev_get_अगरlink);

/**
 *	dev_fill_metadata_dst - Retrieve tunnel egress inक्रमmation.
 *	@dev: targeted पूर्णांकerface
 *	@skb: The packet.
 *
 *	For better visibility of tunnel traffic OVS needs to retrieve
 *	egress tunnel inक्रमmation क्रम a packet. Following API allows
 *	user to get this info.
 */
पूर्णांक dev_fill_metadata_dst(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_tunnel_info *info;

	अगर (!dev->netdev_ops  || !dev->netdev_ops->nकरो_fill_metadata_dst)
		वापस -EINVAL;

	info = skb_tunnel_info_unclone(skb);
	अगर (!info)
		वापस -ENOMEM;
	अगर (unlikely(!(info->mode & IP_TUNNEL_INFO_TX)))
		वापस -EINVAL;

	वापस dev->netdev_ops->nकरो_fill_metadata_dst(dev, skb);
पूर्ण
EXPORT_SYMBOL_GPL(dev_fill_metadata_dst);

अटल काष्ठा net_device_path *dev_fwd_path(काष्ठा net_device_path_stack *stack)
अणु
	पूर्णांक k = stack->num_paths++;

	अगर (WARN_ON_ONCE(k >= NET_DEVICE_PATH_STACK_MAX))
		वापस शून्य;

	वापस &stack->path[k];
पूर्ण

पूर्णांक dev_fill_क्रमward_path(स्थिर काष्ठा net_device *dev, स्थिर u8 *daddr,
			  काष्ठा net_device_path_stack *stack)
अणु
	स्थिर काष्ठा net_device *last_dev;
	काष्ठा net_device_path_ctx ctx = अणु
		.dev	= dev,
		.daddr	= daddr,
	पूर्ण;
	काष्ठा net_device_path *path;
	पूर्णांक ret = 0;

	stack->num_paths = 0;
	जबतक (ctx.dev && ctx.dev->netdev_ops->nकरो_fill_क्रमward_path) अणु
		last_dev = ctx.dev;
		path = dev_fwd_path(stack);
		अगर (!path)
			वापस -1;

		स_रखो(path, 0, माप(काष्ठा net_device_path));
		ret = ctx.dev->netdev_ops->nकरो_fill_क्रमward_path(&ctx, path);
		अगर (ret < 0)
			वापस -1;

		अगर (WARN_ON_ONCE(last_dev == ctx.dev))
			वापस -1;
	पूर्ण
	path = dev_fwd_path(stack);
	अगर (!path)
		वापस -1;
	path->type = DEV_PATH_ETHERNET;
	path->dev = ctx.dev;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_fill_क्रमward_path);

/**
 *	__dev_get_by_name	- find a device by its name
 *	@net: the applicable net namespace
 *	@name: name to find
 *
 *	Find an पूर्णांकerface by name. Must be called under RTNL semaphore
 *	or @dev_base_lock. If the name is found a poपूर्णांकer to the device
 *	is वापसed. If the name is not found then %शून्य is वापसed. The
 *	reference counters are not incremented so the caller must be
 *	careful with locks.
 */

काष्ठा net_device *__dev_get_by_name(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा netdev_name_node *node_name;

	node_name = netdev_name_node_lookup(net, name);
	वापस node_name ? node_name->dev : शून्य;
पूर्ण
EXPORT_SYMBOL(__dev_get_by_name);

/**
 * dev_get_by_name_rcu	- find a device by its name
 * @net: the applicable net namespace
 * @name: name to find
 *
 * Find an पूर्णांकerface by name.
 * If the name is found a poपूर्णांकer to the device is वापसed.
 * If the name is not found then %शून्य is वापसed.
 * The reference counters are not incremented so the caller must be
 * careful with locks. The caller must hold RCU lock.
 */

काष्ठा net_device *dev_get_by_name_rcu(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा netdev_name_node *node_name;

	node_name = netdev_name_node_lookup_rcu(net, name);
	वापस node_name ? node_name->dev : शून्य;
पूर्ण
EXPORT_SYMBOL(dev_get_by_name_rcu);

/**
 *	dev_get_by_name		- find a device by its name
 *	@net: the applicable net namespace
 *	@name: name to find
 *
 *	Find an पूर्णांकerface by name. This can be called from any
 *	context and करोes its own locking. The वापसed handle has
 *	the usage count incremented and the caller must use dev_put() to
 *	release it when it is no दीर्घer needed. %शून्य is वापसed अगर no
 *	matching device is found.
 */

काष्ठा net_device *dev_get_by_name(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	dev = dev_get_by_name_rcu(net, name);
	अगर (dev)
		dev_hold(dev);
	rcu_पढ़ो_unlock();
	वापस dev;
पूर्ण
EXPORT_SYMBOL(dev_get_by_name);

/**
 *	__dev_get_by_index - find a device by its अगरindex
 *	@net: the applicable net namespace
 *	@अगरindex: index of device
 *
 *	Search क्रम an पूर्णांकerface by index. Returns %शून्य अगर the device
 *	is not found or a poपूर्णांकer to the device. The device has not
 *	had its reference counter increased so the caller must be careful
 *	about locking. The caller must hold either the RTNL semaphore
 *	or @dev_base_lock.
 */

काष्ठा net_device *__dev_get_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;
	काष्ठा hlist_head *head = dev_index_hash(net, अगरindex);

	hlist_क्रम_each_entry(dev, head, index_hlist)
		अगर (dev->अगरindex == अगरindex)
			वापस dev;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__dev_get_by_index);

/**
 *	dev_get_by_index_rcu - find a device by its अगरindex
 *	@net: the applicable net namespace
 *	@अगरindex: index of device
 *
 *	Search क्रम an पूर्णांकerface by index. Returns %शून्य अगर the device
 *	is not found or a poपूर्णांकer to the device. The device has not
 *	had its reference counter increased so the caller must be careful
 *	about locking. The caller must hold RCU lock.
 */

काष्ठा net_device *dev_get_by_index_rcu(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;
	काष्ठा hlist_head *head = dev_index_hash(net, अगरindex);

	hlist_क्रम_each_entry_rcu(dev, head, index_hlist)
		अगर (dev->अगरindex == अगरindex)
			वापस dev;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dev_get_by_index_rcu);


/**
 *	dev_get_by_index - find a device by its अगरindex
 *	@net: the applicable net namespace
 *	@अगरindex: index of device
 *
 *	Search क्रम an पूर्णांकerface by index. Returns शून्य अगर the device
 *	is not found or a poपूर्णांकer to the device. The device वापसed has
 *	had a reference added and the poपूर्णांकer is safe until the user calls
 *	dev_put to indicate they have finished with it.
 */

काष्ठा net_device *dev_get_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	dev = dev_get_by_index_rcu(net, अगरindex);
	अगर (dev)
		dev_hold(dev);
	rcu_पढ़ो_unlock();
	वापस dev;
पूर्ण
EXPORT_SYMBOL(dev_get_by_index);

/**
 *	dev_get_by_napi_id - find a device by napi_id
 *	@napi_id: ID of the NAPI काष्ठा
 *
 *	Search क्रम an पूर्णांकerface by NAPI ID. Returns %शून्य अगर the device
 *	is not found or a poपूर्णांकer to the device. The device has not had
 *	its reference counter increased so the caller must be careful
 *	about locking. The caller must hold RCU lock.
 */

काष्ठा net_device *dev_get_by_napi_id(अचिन्हित पूर्णांक napi_id)
अणु
	काष्ठा napi_काष्ठा *napi;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	अगर (napi_id < MIN_NAPI_ID)
		वापस शून्य;

	napi = napi_by_id(napi_id);

	वापस napi ? napi->dev : शून्य;
पूर्ण
EXPORT_SYMBOL(dev_get_by_napi_id);

/**
 *	netdev_get_name - get a netdevice name, knowing its अगरindex.
 *	@net: network namespace
 *	@name: a poपूर्णांकer to the buffer where the name will be stored.
 *	@अगरindex: the अगरindex of the पूर्णांकerface to get the name from.
 */
पूर्णांक netdev_get_name(काष्ठा net *net, अक्षर *name, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;
	पूर्णांक ret;

	करोwn_पढ़ो(&devnet_नाम_sem);
	rcu_पढ़ो_lock();

	dev = dev_get_by_index_rcu(net, अगरindex);
	अगर (!dev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	म_नकल(name, dev->name);

	ret = 0;
out:
	rcu_पढ़ो_unlock();
	up_पढ़ो(&devnet_नाम_sem);
	वापस ret;
पूर्ण

/**
 *	dev_getbyhwaddr_rcu - find a device by its hardware address
 *	@net: the applicable net namespace
 *	@type: media type of device
 *	@ha: hardware address
 *
 *	Search क्रम an पूर्णांकerface by MAC address. Returns शून्य अगर the device
 *	is not found or a poपूर्णांकer to the device.
 *	The caller must hold RCU or RTNL.
 *	The वापसed device has not had its ref count increased
 *	and the caller must thereक्रमe be careful about locking
 *
 */

काष्ठा net_device *dev_getbyhwaddr_rcu(काष्ठा net *net, अचिन्हित लघु type,
				       स्थिर अक्षर *ha)
अणु
	काष्ठा net_device *dev;

	क्रम_each_netdev_rcu(net, dev)
		अगर (dev->type == type &&
		    !स_भेद(dev->dev_addr, ha, dev->addr_len))
			वापस dev;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dev_getbyhwaddr_rcu);

काष्ठा net_device *dev_getfirstbyhwtype(काष्ठा net *net, अचिन्हित लघु type)
अणु
	काष्ठा net_device *dev, *ret = शून्य;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev)
		अगर (dev->type == type) अणु
			dev_hold(dev);
			ret = dev;
			अवरोध;
		पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dev_getfirstbyhwtype);

/**
 *	__dev_get_by_flags - find any device with given flags
 *	@net: the applicable net namespace
 *	@अगर_flags: IFF_* values
 *	@mask: biपंचांगask of bits in अगर_flags to check
 *
 *	Search क्रम any पूर्णांकerface with the given flags. Returns शून्य अगर a device
 *	is not found or a poपूर्णांकer to the device. Must be called inside
 *	rtnl_lock(), and result refcount is unchanged.
 */

काष्ठा net_device *__dev_get_by_flags(काष्ठा net *net, अचिन्हित लघु अगर_flags,
				      अचिन्हित लघु mask)
अणु
	काष्ठा net_device *dev, *ret;

	ASSERT_RTNL();

	ret = शून्य;
	क्रम_each_netdev(net, dev) अणु
		अगर (((dev->flags ^ अगर_flags) & mask) == 0) अणु
			ret = dev;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__dev_get_by_flags);

/**
 *	dev_valid_name - check अगर name is okay क्रम network device
 *	@name: name string
 *
 *	Network device names need to be valid file names to
 *	allow sysfs to work.  We also disallow any kind of
 *	whitespace.
 */
bool dev_valid_name(स्थिर अक्षर *name)
अणु
	अगर (*name == '\0')
		वापस false;
	अगर (strnlen(name, IFNAMSIZ) == IFNAMSIZ)
		वापस false;
	अगर (!म_भेद(name, ".") || !म_भेद(name, ".."))
		वापस false;

	जबतक (*name) अणु
		अगर (*name == '/' || *name == ':' || है_खाली(*name))
			वापस false;
		name++;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL(dev_valid_name);

/**
 *	__dev_alloc_name - allocate a name क्रम a device
 *	@net: network namespace to allocate the device name in
 *	@name: name क्रमmat string
 *	@buf:  scratch buffer and result name string
 *
 *	Passed a क्रमmat string - eg "lt%d" it will try and find a suitable
 *	id. It scans list of devices to build up a मुक्त map, then chooses
 *	the first empty slot. The caller must hold the dev_base or rtnl lock
 *	जबतक allocating the name and adding the device in order to aव्योम
 *	duplicates.
 *	Limited to bits_per_byte * page size devices (ie 32K on most platक्रमms).
 *	Returns the number of the unit asचिन्हित or a negative त्रुटि_सं code.
 */

अटल पूर्णांक __dev_alloc_name(काष्ठा net *net, स्थिर अक्षर *name, अक्षर *buf)
अणु
	पूर्णांक i = 0;
	स्थिर अक्षर *p;
	स्थिर पूर्णांक max_netdevices = 8*PAGE_SIZE;
	अचिन्हित दीर्घ *inuse;
	काष्ठा net_device *d;

	अगर (!dev_valid_name(name))
		वापस -EINVAL;

	p = म_अक्षर(name, '%');
	अगर (p) अणु
		/*
		 * Verअगरy the string as this thing may have come from
		 * the user.  There must be either one "%d" and no other "%"
		 * अक्षरacters.
		 */
		अगर (p[1] != 'd' || strchr(p + 2, '%'))
			वापस -EINVAL;

		/* Use one page as a bit array of possible slots */
		inuse = (अचिन्हित दीर्घ *) get_zeroed_page(GFP_ATOMIC);
		अगर (!inuse)
			वापस -ENOMEM;

		क्रम_each_netdev(net, d) अणु
			काष्ठा netdev_name_node *name_node;
			list_क्रम_each_entry(name_node, &d->name_node->list, list) अणु
				अगर (!माला_पूछो(name_node->name, name, &i))
					जारी;
				अगर (i < 0 || i >= max_netdevices)
					जारी;

				/*  aव्योम हालs where माला_पूछो is not exact inverse of म_लिखो */
				snम_लिखो(buf, IFNAMSIZ, name, i);
				अगर (!म_भेदन(buf, name_node->name, IFNAMSIZ))
					set_bit(i, inuse);
			पूर्ण
			अगर (!माला_पूछो(d->name, name, &i))
				जारी;
			अगर (i < 0 || i >= max_netdevices)
				जारी;

			/*  aव्योम हालs where माला_पूछो is not exact inverse of म_लिखो */
			snम_लिखो(buf, IFNAMSIZ, name, i);
			अगर (!म_भेदन(buf, d->name, IFNAMSIZ))
				set_bit(i, inuse);
		पूर्ण

		i = find_first_zero_bit(inuse, max_netdevices);
		मुक्त_page((अचिन्हित दीर्घ) inuse);
	पूर्ण

	snम_लिखो(buf, IFNAMSIZ, name, i);
	अगर (!__dev_get_by_name(net, buf))
		वापस i;

	/* It is possible to run out of possible slots
	 * when the name is दीर्घ and there isn't enough space left
	 * क्रम the digits, or अगर all bits are used.
	 */
	वापस -ENखाता;
पूर्ण

अटल पूर्णांक dev_alloc_name_ns(काष्ठा net *net,
			     काष्ठा net_device *dev,
			     स्थिर अक्षर *name)
अणु
	अक्षर buf[IFNAMSIZ];
	पूर्णांक ret;

	BUG_ON(!net);
	ret = __dev_alloc_name(net, name, buf);
	अगर (ret >= 0)
		strlcpy(dev->name, buf, IFNAMSIZ);
	वापस ret;
पूर्ण

/**
 *	dev_alloc_name - allocate a name क्रम a device
 *	@dev: device
 *	@name: name क्रमmat string
 *
 *	Passed a क्रमmat string - eg "lt%d" it will try and find a suitable
 *	id. It scans list of devices to build up a मुक्त map, then chooses
 *	the first empty slot. The caller must hold the dev_base or rtnl lock
 *	जबतक allocating the name and adding the device in order to aव्योम
 *	duplicates.
 *	Limited to bits_per_byte * page size devices (ie 32K on most platक्रमms).
 *	Returns the number of the unit asचिन्हित or a negative त्रुटि_सं code.
 */

पूर्णांक dev_alloc_name(काष्ठा net_device *dev, स्थिर अक्षर *name)
अणु
	वापस dev_alloc_name_ns(dev_net(dev), dev, name);
पूर्ण
EXPORT_SYMBOL(dev_alloc_name);

अटल पूर्णांक dev_get_valid_name(काष्ठा net *net, काष्ठा net_device *dev,
			      स्थिर अक्षर *name)
अणु
	BUG_ON(!net);

	अगर (!dev_valid_name(name))
		वापस -EINVAL;

	अगर (म_अक्षर(name, '%'))
		वापस dev_alloc_name_ns(net, dev, name);
	अन्यथा अगर (__dev_get_by_name(net, name))
		वापस -EEXIST;
	अन्यथा अगर (dev->name != name)
		strlcpy(dev->name, name, IFNAMSIZ);

	वापस 0;
पूर्ण

/**
 *	dev_change_name - change name of a device
 *	@dev: device
 *	@newname: name (or क्रमmat string) must be at least IFNAMSIZ
 *
 *	Change name of a device, can pass क्रमmat strings "eth%d".
 *	क्रम wildcarding.
 */
पूर्णांक dev_change_name(काष्ठा net_device *dev, स्थिर अक्षर *newname)
अणु
	अचिन्हित अक्षर old_assign_type;
	अक्षर oldname[IFNAMSIZ];
	पूर्णांक err = 0;
	पूर्णांक ret;
	काष्ठा net *net;

	ASSERT_RTNL();
	BUG_ON(!dev_net(dev));

	net = dev_net(dev);

	/* Some स्वतः-enslaved devices e.g. failover slaves are
	 * special, as userspace might नाम the device after
	 * the पूर्णांकerface had been brought up and running since
	 * the poपूर्णांक kernel initiated स्वतः-enslavement. Allow
	 * live name change even when these slave devices are
	 * up and running.
	 *
	 * Typically, users of these स्वतः-enslaving devices
	 * करोn't actually care about slave name change, as
	 * they are supposed to operate on master पूर्णांकerface
	 * directly.
	 */
	अगर (dev->flags & IFF_UP &&
	    likely(!(dev->priv_flags & IFF_LIVE_RENAME_OK)))
		वापस -EBUSY;

	करोwn_ग_लिखो(&devnet_नाम_sem);

	अगर (म_भेदन(newname, dev->name, IFNAMSIZ) == 0) अणु
		up_ग_लिखो(&devnet_नाम_sem);
		वापस 0;
	पूर्ण

	स_नकल(oldname, dev->name, IFNAMSIZ);

	err = dev_get_valid_name(net, dev, newname);
	अगर (err < 0) अणु
		up_ग_लिखो(&devnet_नाम_sem);
		वापस err;
	पूर्ण

	अगर (oldname[0] && !म_अक्षर(oldname, '%'))
		netdev_info(dev, "renamed from %s\n", oldname);

	old_assign_type = dev->name_assign_type;
	dev->name_assign_type = NET_NAME_RENAMED;

rollback:
	ret = device_नाम(&dev->dev, dev->name);
	अगर (ret) अणु
		स_नकल(dev->name, oldname, IFNAMSIZ);
		dev->name_assign_type = old_assign_type;
		up_ग_लिखो(&devnet_नाम_sem);
		वापस ret;
	पूर्ण

	up_ग_लिखो(&devnet_नाम_sem);

	netdev_adjacent_नाम_links(dev, oldname);

	ग_लिखो_lock_bh(&dev_base_lock);
	netdev_name_node_del(dev->name_node);
	ग_लिखो_unlock_bh(&dev_base_lock);

	synchronize_rcu();

	ग_लिखो_lock_bh(&dev_base_lock);
	netdev_name_node_add(net, dev->name_node);
	ग_लिखो_unlock_bh(&dev_base_lock);

	ret = call_netdevice_notअगरiers(NETDEV_CHANGENAME, dev);
	ret = notअगरier_to_त्रुटि_सं(ret);

	अगर (ret) अणु
		/* err >= 0 after dev_alloc_name() or stores the first त्रुटि_सं */
		अगर (err >= 0) अणु
			err = ret;
			करोwn_ग_लिखो(&devnet_नाम_sem);
			स_नकल(dev->name, oldname, IFNAMSIZ);
			स_नकल(oldname, newname, IFNAMSIZ);
			dev->name_assign_type = old_assign_type;
			old_assign_type = NET_NAME_RENAMED;
			जाओ rollback;
		पूर्ण अन्यथा अणु
			pr_err("%s: name change rollback failed: %d\n",
			       dev->name, ret);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 *	dev_set_alias - change अगरalias of a device
 *	@dev: device
 *	@alias: name up to IFALIASZ
 *	@len: limit of bytes to copy from info
 *
 *	Set अगरalias क्रम a device,
 */
पूर्णांक dev_set_alias(काष्ठा net_device *dev, स्थिर अक्षर *alias, माप_प्रकार len)
अणु
	काष्ठा dev_अगरalias *new_alias = शून्य;

	अगर (len >= IFALIASZ)
		वापस -EINVAL;

	अगर (len) अणु
		new_alias = kदो_स्मृति(माप(*new_alias) + len + 1, GFP_KERNEL);
		अगर (!new_alias)
			वापस -ENOMEM;

		स_नकल(new_alias->अगरalias, alias, len);
		new_alias->अगरalias[len] = 0;
	पूर्ण

	mutex_lock(&अगरalias_mutex);
	new_alias = rcu_replace_poपूर्णांकer(dev->अगरalias, new_alias,
					mutex_is_locked(&अगरalias_mutex));
	mutex_unlock(&अगरalias_mutex);

	अगर (new_alias)
		kमुक्त_rcu(new_alias, rcuhead);

	वापस len;
पूर्ण
EXPORT_SYMBOL(dev_set_alias);

/**
 *	dev_get_alias - get अगरalias of a device
 *	@dev: device
 *	@name: buffer to store name of अगरalias
 *	@len: size of buffer
 *
 *	get अगरalias क्रम a device.  Caller must make sure dev cannot go
 *	away,  e.g. rcu पढ़ो lock or own a reference count to device.
 */
पूर्णांक dev_get_alias(स्थिर काष्ठा net_device *dev, अक्षर *name, माप_प्रकार len)
अणु
	स्थिर काष्ठा dev_अगरalias *alias;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	alias = rcu_dereference(dev->अगरalias);
	अगर (alias)
		ret = snम_लिखो(name, len, "%s", alias->अगरalias);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/**
 *	netdev_features_change - device changes features
 *	@dev: device to cause notअगरication
 *
 *	Called to indicate a device has changed features.
 */
व्योम netdev_features_change(काष्ठा net_device *dev)
अणु
	call_netdevice_notअगरiers(NETDEV_FEAT_CHANGE, dev);
पूर्ण
EXPORT_SYMBOL(netdev_features_change);

/**
 *	netdev_state_change - device changes state
 *	@dev: device to cause notअगरication
 *
 *	Called to indicate a device has changed state. This function calls
 *	the notअगरier chains क्रम netdev_chain and sends a NEWLINK message
 *	to the routing socket.
 */
व्योम netdev_state_change(काष्ठा net_device *dev)
अणु
	अगर (dev->flags & IFF_UP) अणु
		काष्ठा netdev_notअगरier_change_info change_info = अणु
			.info.dev = dev,
		पूर्ण;

		call_netdevice_notअगरiers_info(NETDEV_CHANGE,
					      &change_info.info);
		rपंचांगsg_अगरinfo(RTM_NEWLINK, dev, 0, GFP_KERNEL);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netdev_state_change);

/**
 * __netdev_notअगरy_peers - notअगरy network peers about existence of @dev,
 * to be called when rtnl lock is alपढ़ोy held.
 * @dev: network device
 *
 * Generate traffic such that पूर्णांकerested network peers are aware of
 * @dev, such as by generating a gratuitous ARP. This may be used when
 * a device wants to inक्रमm the rest of the network about some sort of
 * reconfiguration such as a failover event or भव machine
 * migration.
 */
व्योम __netdev_notअगरy_peers(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	call_netdevice_notअगरiers(NETDEV_NOTIFY_PEERS, dev);
	call_netdevice_notअगरiers(NETDEV_RESEND_IGMP, dev);
पूर्ण
EXPORT_SYMBOL(__netdev_notअगरy_peers);

/**
 * netdev_notअगरy_peers - notअगरy network peers about existence of @dev
 * @dev: network device
 *
 * Generate traffic such that पूर्णांकerested network peers are aware of
 * @dev, such as by generating a gratuitous ARP. This may be used when
 * a device wants to inक्रमm the rest of the network about some sort of
 * reconfiguration such as a failover event or भव machine
 * migration.
 */
व्योम netdev_notअगरy_peers(काष्ठा net_device *dev)
अणु
	rtnl_lock();
	__netdev_notअगरy_peers(dev);
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL(netdev_notअगरy_peers);

अटल पूर्णांक napi_thपढ़ोed_poll(व्योम *data);

अटल पूर्णांक napi_kthपढ़ो_create(काष्ठा napi_काष्ठा *n)
अणु
	पूर्णांक err = 0;

	/* Create and wake up the kthपढ़ो once to put it in
	 * TASK_INTERRUPTIBLE mode to aव्योम the blocked task
	 * warning and work with loadavg.
	 */
	n->thपढ़ो = kthपढ़ो_run(napi_thपढ़ोed_poll, n, "napi/%s-%d",
				n->dev->name, n->napi_id);
	अगर (IS_ERR(n->thपढ़ो)) अणु
		err = PTR_ERR(n->thपढ़ो);
		pr_err("kthread_run failed with err %d\n", err);
		n->thपढ़ो = शून्य;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __dev_खोलो(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (!netअगर_device_present(dev)) अणु
		/* may be detached because parent is runसमय-suspended */
		अगर (dev->dev.parent)
			pm_runसमय_resume(dev->dev.parent);
		अगर (!netअगर_device_present(dev))
			वापस -ENODEV;
	पूर्ण

	/* Block netpoll from trying to करो any rx path servicing.
	 * If we करोn't करो this there is a chance nकरो_poll_controller
	 * or nकरो_poll may be running जबतक we खोलो the device
	 */
	netpoll_poll_disable(dev);

	ret = call_netdevice_notअगरiers_extack(NETDEV_PRE_UP, dev, extack);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret)
		वापस ret;

	set_bit(__LINK_STATE_START, &dev->state);

	अगर (ops->nकरो_validate_addr)
		ret = ops->nकरो_validate_addr(dev);

	अगर (!ret && ops->nकरो_खोलो)
		ret = ops->nकरो_खोलो(dev);

	netpoll_poll_enable(dev);

	अगर (ret)
		clear_bit(__LINK_STATE_START, &dev->state);
	अन्यथा अणु
		dev->flags |= IFF_UP;
		dev_set_rx_mode(dev);
		dev_activate(dev);
		add_device_अक्रमomness(dev->dev_addr, dev->addr_len);
	पूर्ण

	वापस ret;
पूर्ण

/**
 *	dev_खोलो	- prepare an पूर्णांकerface क्रम use.
 *	@dev: device to खोलो
 *	@extack: netlink extended ack
 *
 *	Takes a device from करोwn to up state. The device's निजी खोलो
 *	function is invoked and then the multicast lists are loaded. Finally
 *	the device is moved पूर्णांकo the up state and a %NETDEV_UP message is
 *	sent to the netdev notअगरier chain.
 *
 *	Calling this function on an active पूर्णांकerface is a nop. On a failure
 *	a negative त्रुटि_सं code is वापसed.
 */
पूर्णांक dev_खोलो(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret;

	अगर (dev->flags & IFF_UP)
		वापस 0;

	ret = __dev_खोलो(dev, extack);
	अगर (ret < 0)
		वापस ret;

	rपंचांगsg_अगरinfo(RTM_NEWLINK, dev, IFF_UP|IFF_RUNNING, GFP_KERNEL);
	call_netdevice_notअगरiers(NETDEV_UP, dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dev_खोलो);

अटल व्योम __dev_बंद_many(काष्ठा list_head *head)
अणु
	काष्ठा net_device *dev;

	ASSERT_RTNL();
	might_sleep();

	list_क्रम_each_entry(dev, head, बंद_list) अणु
		/* Temporarily disable netpoll until the पूर्णांकerface is करोwn */
		netpoll_poll_disable(dev);

		call_netdevice_notअगरiers(NETDEV_GOING_DOWN, dev);

		clear_bit(__LINK_STATE_START, &dev->state);

		/* Synchronize to scheduled poll. We cannot touch poll list, it
		 * can be even on dअगरferent cpu. So just clear netअगर_running().
		 *
		 * dev->stop() will invoke napi_disable() on all of it's
		 * napi_काष्ठा instances on this device.
		 */
		smp_mb__after_atomic(); /* Commit netअगर_running(). */
	पूर्ण

	dev_deactivate_many(head);

	list_क्रम_each_entry(dev, head, बंद_list) अणु
		स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

		/*
		 *	Call the device specअगरic बंद. This cannot fail.
		 *	Only अगर device is UP
		 *
		 *	We allow it to be called even after a DETACH hot-plug
		 *	event.
		 */
		अगर (ops->nकरो_stop)
			ops->nकरो_stop(dev);

		dev->flags &= ~IFF_UP;
		netpoll_poll_enable(dev);
	पूर्ण
पूर्ण

अटल व्योम __dev_बंद(काष्ठा net_device *dev)
अणु
	LIST_HEAD(single);

	list_add(&dev->बंद_list, &single);
	__dev_बंद_many(&single);
	list_del(&single);
पूर्ण

व्योम dev_बंद_many(काष्ठा list_head *head, bool unlink)
अणु
	काष्ठा net_device *dev, *पंचांगp;

	/* Remove the devices that करोn't need to be बंदd */
	list_क्रम_each_entry_safe(dev, पंचांगp, head, बंद_list)
		अगर (!(dev->flags & IFF_UP))
			list_del_init(&dev->बंद_list);

	__dev_बंद_many(head);

	list_क्रम_each_entry_safe(dev, पंचांगp, head, बंद_list) अणु
		rपंचांगsg_अगरinfo(RTM_NEWLINK, dev, IFF_UP|IFF_RUNNING, GFP_KERNEL);
		call_netdevice_notअगरiers(NETDEV_DOWN, dev);
		अगर (unlink)
			list_del_init(&dev->बंद_list);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dev_बंद_many);

/**
 *	dev_बंद - shutकरोwn an पूर्णांकerface.
 *	@dev: device to shutकरोwn
 *
 *	This function moves an active device पूर्णांकo करोwn state. A
 *	%NETDEV_GOING_DOWN is sent to the netdev notअगरier chain. The device
 *	is then deactivated and finally a %NETDEV_DOWN is sent to the notअगरier
 *	chain.
 */
व्योम dev_बंद(काष्ठा net_device *dev)
अणु
	अगर (dev->flags & IFF_UP) अणु
		LIST_HEAD(single);

		list_add(&dev->बंद_list, &single);
		dev_बंद_many(&single, true);
		list_del(&single);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dev_बंद);


/**
 *	dev_disable_lro - disable Large Receive Offload on a device
 *	@dev: device
 *
 *	Disable Large Receive Offload (LRO) on a net device.  Must be
 *	called under RTNL.  This is needed अगर received packets may be
 *	क्रमwarded to another पूर्णांकerface.
 */
व्योम dev_disable_lro(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *lower_dev;
	काष्ठा list_head *iter;

	dev->wanted_features &= ~NETIF_F_LRO;
	netdev_update_features(dev);

	अगर (unlikely(dev->features & NETIF_F_LRO))
		netdev_WARN(dev, "failed to disable LRO!\n");

	netdev_क्रम_each_lower_dev(dev, lower_dev, iter)
		dev_disable_lro(lower_dev);
पूर्ण
EXPORT_SYMBOL(dev_disable_lro);

/**
 *	dev_disable_gro_hw - disable HW Generic Receive Offload on a device
 *	@dev: device
 *
 *	Disable HW Generic Receive Offload (GRO_HW) on a net device.  Must be
 *	called under RTNL.  This is needed अगर Generic XDP is installed on
 *	the device.
 */
अटल व्योम dev_disable_gro_hw(काष्ठा net_device *dev)
अणु
	dev->wanted_features &= ~NETIF_F_GRO_HW;
	netdev_update_features(dev);

	अगर (unlikely(dev->features & NETIF_F_GRO_HW))
		netdev_WARN(dev, "failed to disable GRO_HW!\n");
पूर्ण

स्थिर अक्षर *netdev_cmd_to_name(क्रमागत netdev_cmd cmd)
अणु
#घोषणा N(val) 						\
	हाल NETDEV_##val:				\
		वापस "NETDEV_" __stringअगरy(val);
	चयन (cmd) अणु
	N(UP) N(DOWN) N(REBOOT) N(CHANGE) N(REGISTER) N(UNREGISTER)
	N(CHANGEMTU) N(CHANGEADDR) N(GOING_DOWN) N(CHANGENAME) N(FEAT_CHANGE)
	N(BONDING_FAILOVER) N(PRE_UP) N(PRE_TYPE_CHANGE) N(POST_TYPE_CHANGE)
	N(POST_INIT) N(RELEASE) N(NOTIFY_PEERS) N(JOIN) N(CHANGEUPPER)
	N(RESEND_IGMP) N(PRECHANGEMTU) N(CHANGEINFODATA) N(BONDING_INFO)
	N(PRECHANGEUPPER) N(CHANGELOWERSTATE) N(UDP_TUNNEL_PUSH_INFO)
	N(UDP_TUNNEL_DROP_INFO) N(CHANGE_TX_QUEUE_LEN)
	N(CVLAN_FILTER_PUSH_INFO) N(CVLAN_FILTER_DROP_INFO)
	N(SVLAN_FILTER_PUSH_INFO) N(SVLAN_FILTER_DROP_INFO)
	N(PRE_CHANGEADDR)
	पूर्ण
#अघोषित N
	वापस "UNKNOWN_NETDEV_EVENT";
पूर्ण
EXPORT_SYMBOL_GPL(netdev_cmd_to_name);

अटल पूर्णांक call_netdevice_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				   काष्ठा net_device *dev)
अणु
	काष्ठा netdev_notअगरier_info info = अणु
		.dev = dev,
	पूर्ण;

	वापस nb->notअगरier_call(nb, val, &info);
पूर्ण

अटल पूर्णांक call_netdevice_रेजिस्टर_notअगरiers(काष्ठा notअगरier_block *nb,
					     काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	err = call_netdevice_notअगरier(nb, NETDEV_REGISTER, dev);
	err = notअगरier_to_त्रुटि_सं(err);
	अगर (err)
		वापस err;

	अगर (!(dev->flags & IFF_UP))
		वापस 0;

	call_netdevice_notअगरier(nb, NETDEV_UP, dev);
	वापस 0;
पूर्ण

अटल व्योम call_netdevice_unरेजिस्टर_notअगरiers(काष्ठा notअगरier_block *nb,
						काष्ठा net_device *dev)
अणु
	अगर (dev->flags & IFF_UP) अणु
		call_netdevice_notअगरier(nb, NETDEV_GOING_DOWN,
					dev);
		call_netdevice_notअगरier(nb, NETDEV_DOWN, dev);
	पूर्ण
	call_netdevice_notअगरier(nb, NETDEV_UNREGISTER, dev);
पूर्ण

अटल पूर्णांक call_netdevice_रेजिस्टर_net_notअगरiers(काष्ठा notअगरier_block *nb,
						 काष्ठा net *net)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err;

	क्रम_each_netdev(net, dev) अणु
		err = call_netdevice_रेजिस्टर_notअगरiers(nb, dev);
		अगर (err)
			जाओ rollback;
	पूर्ण
	वापस 0;

rollback:
	क्रम_each_netdev_जारी_reverse(net, dev)
		call_netdevice_unरेजिस्टर_notअगरiers(nb, dev);
	वापस err;
पूर्ण

अटल व्योम call_netdevice_unरेजिस्टर_net_notअगरiers(काष्ठा notअगरier_block *nb,
						    काष्ठा net *net)
अणु
	काष्ठा net_device *dev;

	क्रम_each_netdev(net, dev)
		call_netdevice_unरेजिस्टर_notअगरiers(nb, dev);
पूर्ण

अटल पूर्णांक dev_boot_phase = 1;

/**
 * रेजिस्टर_netdevice_notअगरier - रेजिस्टर a network notअगरier block
 * @nb: notअगरier
 *
 * Register a notअगरier to be called when network device events occur.
 * The notअगरier passed is linked पूर्णांकo the kernel काष्ठाures and must
 * not be reused until it has been unरेजिस्टरed. A negative त्रुटि_सं code
 * is वापसed on a failure.
 *
 * When रेजिस्टरed all registration and up events are replayed
 * to the new notअगरier to allow device to have a race मुक्त
 * view of the network device list.
 */

पूर्णांक रेजिस्टर_netdevice_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा net *net;
	पूर्णांक err;

	/* Close race with setup_net() and cleanup_net() */
	करोwn_ग_लिखो(&pernet_ops_rwsem);
	rtnl_lock();
	err = raw_notअगरier_chain_रेजिस्टर(&netdev_chain, nb);
	अगर (err)
		जाओ unlock;
	अगर (dev_boot_phase)
		जाओ unlock;
	क्रम_each_net(net) अणु
		err = call_netdevice_रेजिस्टर_net_notअगरiers(nb, net);
		अगर (err)
			जाओ rollback;
	पूर्ण

unlock:
	rtnl_unlock();
	up_ग_लिखो(&pernet_ops_rwsem);
	वापस err;

rollback:
	क्रम_each_net_जारी_reverse(net)
		call_netdevice_unरेजिस्टर_net_notअगरiers(nb, net);

	raw_notअगरier_chain_unरेजिस्टर(&netdev_chain, nb);
	जाओ unlock;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_netdevice_notअगरier);

/**
 * unरेजिस्टर_netdevice_notअगरier - unरेजिस्टर a network notअगरier block
 * @nb: notअगरier
 *
 * Unरेजिस्टर a notअगरier previously रेजिस्टरed by
 * रेजिस्टर_netdevice_notअगरier(). The notअगरier is unlinked पूर्णांकo the
 * kernel काष्ठाures and may then be reused. A negative त्रुटि_सं code
 * is वापसed on a failure.
 *
 * After unरेजिस्टरing unरेजिस्टर and करोwn device events are synthesized
 * क्रम all devices on the device list to the हटाओd notअगरier to हटाओ
 * the need क्रम special हाल cleanup code.
 */

पूर्णांक unरेजिस्टर_netdevice_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा net *net;
	पूर्णांक err;

	/* Close race with setup_net() and cleanup_net() */
	करोwn_ग_लिखो(&pernet_ops_rwsem);
	rtnl_lock();
	err = raw_notअगरier_chain_unरेजिस्टर(&netdev_chain, nb);
	अगर (err)
		जाओ unlock;

	क्रम_each_net(net)
		call_netdevice_unरेजिस्टर_net_notअगरiers(nb, net);

unlock:
	rtnl_unlock();
	up_ग_लिखो(&pernet_ops_rwsem);
	वापस err;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_netdevice_notअगरier);

अटल पूर्णांक __रेजिस्टर_netdevice_notअगरier_net(काष्ठा net *net,
					     काष्ठा notअगरier_block *nb,
					     bool ignore_call_fail)
अणु
	पूर्णांक err;

	err = raw_notअगरier_chain_रेजिस्टर(&net->netdev_chain, nb);
	अगर (err)
		वापस err;
	अगर (dev_boot_phase)
		वापस 0;

	err = call_netdevice_रेजिस्टर_net_notअगरiers(nb, net);
	अगर (err && !ignore_call_fail)
		जाओ chain_unरेजिस्टर;

	वापस 0;

chain_unरेजिस्टर:
	raw_notअगरier_chain_unरेजिस्टर(&net->netdev_chain, nb);
	वापस err;
पूर्ण

अटल पूर्णांक __unरेजिस्टर_netdevice_notअगरier_net(काष्ठा net *net,
					       काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक err;

	err = raw_notअगरier_chain_unरेजिस्टर(&net->netdev_chain, nb);
	अगर (err)
		वापस err;

	call_netdevice_unरेजिस्टर_net_notअगरiers(nb, net);
	वापस 0;
पूर्ण

/**
 * रेजिस्टर_netdevice_notअगरier_net - रेजिस्टर a per-netns network notअगरier block
 * @net: network namespace
 * @nb: notअगरier
 *
 * Register a notअगरier to be called when network device events occur.
 * The notअगरier passed is linked पूर्णांकo the kernel काष्ठाures and must
 * not be reused until it has been unरेजिस्टरed. A negative त्रुटि_सं code
 * is वापसed on a failure.
 *
 * When रेजिस्टरed all registration and up events are replayed
 * to the new notअगरier to allow device to have a race मुक्त
 * view of the network device list.
 */

पूर्णांक रेजिस्टर_netdevice_notअगरier_net(काष्ठा net *net, काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __रेजिस्टर_netdevice_notअगरier_net(net, nb, false);
	rtnl_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_netdevice_notअगरier_net);

/**
 * unरेजिस्टर_netdevice_notअगरier_net - unरेजिस्टर a per-netns
 *                                     network notअगरier block
 * @net: network namespace
 * @nb: notअगरier
 *
 * Unरेजिस्टर a notअगरier previously रेजिस्टरed by
 * रेजिस्टर_netdevice_notअगरier(). The notअगरier is unlinked पूर्णांकo the
 * kernel काष्ठाures and may then be reused. A negative त्रुटि_सं code
 * is वापसed on a failure.
 *
 * After unरेजिस्टरing unरेजिस्टर and करोwn device events are synthesized
 * क्रम all devices on the device list to the हटाओd notअगरier to हटाओ
 * the need क्रम special हाल cleanup code.
 */

पूर्णांक unरेजिस्टर_netdevice_notअगरier_net(काष्ठा net *net,
				      काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __unरेजिस्टर_netdevice_notअगरier_net(net, nb);
	rtnl_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_netdevice_notअगरier_net);

पूर्णांक रेजिस्टर_netdevice_notअगरier_dev_net(काष्ठा net_device *dev,
					काष्ठा notअगरier_block *nb,
					काष्ठा netdev_net_notअगरier *nn)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __रेजिस्टर_netdevice_notअगरier_net(dev_net(dev), nb, false);
	अगर (!err) अणु
		nn->nb = nb;
		list_add(&nn->list, &dev->net_notअगरier_list);
	पूर्ण
	rtnl_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_netdevice_notअगरier_dev_net);

पूर्णांक unरेजिस्टर_netdevice_notअगरier_dev_net(काष्ठा net_device *dev,
					  काष्ठा notअगरier_block *nb,
					  काष्ठा netdev_net_notअगरier *nn)
अणु
	पूर्णांक err;

	rtnl_lock();
	list_del(&nn->list);
	err = __unरेजिस्टर_netdevice_notअगरier_net(dev_net(dev), nb);
	rtnl_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_netdevice_notअगरier_dev_net);

अटल व्योम move_netdevice_notअगरiers_dev_net(काष्ठा net_device *dev,
					     काष्ठा net *net)
अणु
	काष्ठा netdev_net_notअगरier *nn;

	list_क्रम_each_entry(nn, &dev->net_notअगरier_list, list) अणु
		__unरेजिस्टर_netdevice_notअगरier_net(dev_net(dev), nn->nb);
		__रेजिस्टर_netdevice_notअगरier_net(net, nn->nb, true);
	पूर्ण
पूर्ण

/**
 *	call_netdevice_notअगरiers_info - call all network notअगरier blocks
 *	@val: value passed unmodअगरied to notअगरier function
 *	@info: notअगरier inक्रमmation data
 *
 *	Call all network notअगरier blocks.  Parameters and वापस value
 *	are as क्रम raw_notअगरier_call_chain().
 */

अटल पूर्णांक call_netdevice_notअगरiers_info(अचिन्हित दीर्घ val,
					 काष्ठा netdev_notअगरier_info *info)
अणु
	काष्ठा net *net = dev_net(info->dev);
	पूर्णांक ret;

	ASSERT_RTNL();

	/* Run per-netns notअगरier block chain first, then run the global one.
	 * Hopefully, one day, the global one is going to be हटाओd after
	 * all notअगरier block registrators get converted to be per-netns.
	 */
	ret = raw_notअगरier_call_chain(&net->netdev_chain, val, info);
	अगर (ret & NOTIFY_STOP_MASK)
		वापस ret;
	वापस raw_notअगरier_call_chain(&netdev_chain, val, info);
पूर्ण

अटल पूर्णांक call_netdevice_notअगरiers_extack(अचिन्हित दीर्घ val,
					   काष्ठा net_device *dev,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_notअगरier_info info = अणु
		.dev = dev,
		.extack = extack,
	पूर्ण;

	वापस call_netdevice_notअगरiers_info(val, &info);
पूर्ण

/**
 *	call_netdevice_notअगरiers - call all network notअगरier blocks
 *      @val: value passed unmodअगरied to notअगरier function
 *      @dev: net_device poपूर्णांकer passed unmodअगरied to notअगरier function
 *
 *	Call all network notअगरier blocks.  Parameters and वापस value
 *	are as क्रम raw_notअगरier_call_chain().
 */

पूर्णांक call_netdevice_notअगरiers(अचिन्हित दीर्घ val, काष्ठा net_device *dev)
अणु
	वापस call_netdevice_notअगरiers_extack(val, dev, शून्य);
पूर्ण
EXPORT_SYMBOL(call_netdevice_notअगरiers);

/**
 *	call_netdevice_notअगरiers_mtu - call all network notअगरier blocks
 *	@val: value passed unmodअगरied to notअगरier function
 *	@dev: net_device poपूर्णांकer passed unmodअगरied to notअगरier function
 *	@arg: additional u32 argument passed to the notअगरier function
 *
 *	Call all network notअगरier blocks.  Parameters and वापस value
 *	are as क्रम raw_notअगरier_call_chain().
 */
अटल पूर्णांक call_netdevice_notअगरiers_mtu(अचिन्हित दीर्घ val,
					काष्ठा net_device *dev, u32 arg)
अणु
	काष्ठा netdev_notअगरier_info_ext info = अणु
		.info.dev = dev,
		.ext.mtu = arg,
	पूर्ण;

	BUILD_BUG_ON(दुरत्व(काष्ठा netdev_notअगरier_info_ext, info) != 0);

	वापस call_netdevice_notअगरiers_info(val, &info.info);
पूर्ण

#अगर_घोषित CONFIG_NET_INGRESS
अटल DEFINE_STATIC_KEY_FALSE(ingress_needed_key);

व्योम net_inc_ingress_queue(व्योम)
अणु
	अटल_branch_inc(&ingress_needed_key);
पूर्ण
EXPORT_SYMBOL_GPL(net_inc_ingress_queue);

व्योम net_dec_ingress_queue(व्योम)
अणु
	अटल_branch_dec(&ingress_needed_key);
पूर्ण
EXPORT_SYMBOL_GPL(net_dec_ingress_queue);
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_EGRESS
अटल DEFINE_STATIC_KEY_FALSE(egress_needed_key);

व्योम net_inc_egress_queue(व्योम)
अणु
	अटल_branch_inc(&egress_needed_key);
पूर्ण
EXPORT_SYMBOL_GPL(net_inc_egress_queue);

व्योम net_dec_egress_queue(व्योम)
अणु
	अटल_branch_dec(&egress_needed_key);
पूर्ण
EXPORT_SYMBOL_GPL(net_dec_egress_queue);
#पूर्ण_अगर

अटल DEFINE_STATIC_KEY_FALSE(netstamp_needed_key);
#अगर_घोषित CONFIG_JUMP_LABEL
अटल atomic_t netstamp_needed_deferred;
अटल atomic_t netstamp_wanted;
अटल व्योम netstamp_clear(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक deferred = atomic_xchg(&netstamp_needed_deferred, 0);
	पूर्णांक wanted;

	wanted = atomic_add_वापस(deferred, &netstamp_wanted);
	अगर (wanted > 0)
		अटल_branch_enable(&netstamp_needed_key);
	अन्यथा
		अटल_branch_disable(&netstamp_needed_key);
पूर्ण
अटल DECLARE_WORK(netstamp_work, netstamp_clear);
#पूर्ण_अगर

व्योम net_enable_बारtamp(व्योम)
अणु
#अगर_घोषित CONFIG_JUMP_LABEL
	पूर्णांक wanted;

	जबतक (1) अणु
		wanted = atomic_पढ़ो(&netstamp_wanted);
		अगर (wanted <= 0)
			अवरोध;
		अगर (atomic_cmpxchg(&netstamp_wanted, wanted, wanted + 1) == wanted)
			वापस;
	पूर्ण
	atomic_inc(&netstamp_needed_deferred);
	schedule_work(&netstamp_work);
#अन्यथा
	अटल_branch_inc(&netstamp_needed_key);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(net_enable_बारtamp);

व्योम net_disable_बारtamp(व्योम)
अणु
#अगर_घोषित CONFIG_JUMP_LABEL
	पूर्णांक wanted;

	जबतक (1) अणु
		wanted = atomic_पढ़ो(&netstamp_wanted);
		अगर (wanted <= 1)
			अवरोध;
		अगर (atomic_cmpxchg(&netstamp_wanted, wanted, wanted - 1) == wanted)
			वापस;
	पूर्ण
	atomic_dec(&netstamp_needed_deferred);
	schedule_work(&netstamp_work);
#अन्यथा
	अटल_branch_dec(&netstamp_needed_key);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(net_disable_बारtamp);

अटल अंतरभूत व्योम net_बारtamp_set(काष्ठा sk_buff *skb)
अणु
	skb->tstamp = 0;
	अगर (अटल_branch_unlikely(&netstamp_needed_key))
		__net_बारtamp(skb);
पूर्ण

#घोषणा net_बारtamp_check(COND, SKB)				\
	अगर (अटल_branch_unlikely(&netstamp_needed_key)) अणु	\
		अगर ((COND) && !(SKB)->tstamp)			\
			__net_बारtamp(SKB);			\
	पूर्ण							\

bool is_skb_क्रमwardable(स्थिर काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb)
अणु
	वापस __is_skb_क्रमwardable(dev, skb, true);
पूर्ण
EXPORT_SYMBOL_GPL(is_skb_क्रमwardable);

अटल पूर्णांक __dev_क्रमward_skb2(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			      bool check_mtu)
अणु
	पूर्णांक ret = ____dev_क्रमward_skb(dev, skb, check_mtu);

	अगर (likely(!ret)) अणु
		skb->protocol = eth_type_trans(skb, dev);
		skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक __dev_क्रमward_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	वापस __dev_क्रमward_skb2(dev, skb, true);
पूर्ण
EXPORT_SYMBOL_GPL(__dev_क्रमward_skb);

/**
 * dev_क्रमward_skb - loopback an skb to another netअगर
 *
 * @dev: destination network device
 * @skb: buffer to क्रमward
 *
 * वापस values:
 *	NET_RX_SUCCESS	(no congestion)
 *	NET_RX_DROP     (packet was dropped, but मुक्तd)
 *
 * dev_क्रमward_skb can be used क्रम injecting an skb from the
 * start_xmit function of one device पूर्णांकo the receive queue
 * of another device.
 *
 * The receiving device may be in another namespace, so
 * we have to clear all inक्रमmation in the skb that could
 * impact namespace isolation.
 */
पूर्णांक dev_क्रमward_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	वापस __dev_क्रमward_skb(dev, skb) ?: netअगर_rx_पूर्णांकernal(skb);
पूर्ण
EXPORT_SYMBOL_GPL(dev_क्रमward_skb);

पूर्णांक dev_क्रमward_skb_nomtu(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	वापस __dev_क्रमward_skb2(dev, skb, false) ?: netअगर_rx_पूर्णांकernal(skb);
पूर्ण

अटल अंतरभूत पूर्णांक deliver_skb(काष्ठा sk_buff *skb,
			      काष्ठा packet_type *pt_prev,
			      काष्ठा net_device *orig_dev)
अणु
	अगर (unlikely(skb_orphan_frags_rx(skb, GFP_ATOMIC)))
		वापस -ENOMEM;
	refcount_inc(&skb->users);
	वापस pt_prev->func(skb, skb->dev, pt_prev, orig_dev);
पूर्ण

अटल अंतरभूत व्योम deliver_ptype_list_skb(काष्ठा sk_buff *skb,
					  काष्ठा packet_type **pt,
					  काष्ठा net_device *orig_dev,
					  __be16 type,
					  काष्ठा list_head *ptype_list)
अणु
	काष्ठा packet_type *ptype, *pt_prev = *pt;

	list_क्रम_each_entry_rcu(ptype, ptype_list, list) अणु
		अगर (ptype->type != type)
			जारी;
		अगर (pt_prev)
			deliver_skb(skb, pt_prev, orig_dev);
		pt_prev = ptype;
	पूर्ण
	*pt = pt_prev;
पूर्ण

अटल अंतरभूत bool skb_loop_sk(काष्ठा packet_type *ptype, काष्ठा sk_buff *skb)
अणु
	अगर (!ptype->af_packet_priv || !skb->sk)
		वापस false;

	अगर (ptype->id_match)
		वापस ptype->id_match(ptype, skb->sk);
	अन्यथा अगर ((काष्ठा sock *)ptype->af_packet_priv == skb->sk)
		वापस true;

	वापस false;
पूर्ण

/**
 * dev_nit_active - वापस true अगर any network पूर्णांकerface taps are in use
 *
 * @dev: network device to check क्रम the presence of taps
 */
bool dev_nit_active(काष्ठा net_device *dev)
अणु
	वापस !list_empty(&ptype_all) || !list_empty(&dev->ptype_all);
पूर्ण
EXPORT_SYMBOL_GPL(dev_nit_active);

/*
 *	Support routine. Sends outgoing frames to any network
 *	taps currently in use.
 */

व्योम dev_queue_xmit_nit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा packet_type *ptype;
	काष्ठा sk_buff *skb2 = शून्य;
	काष्ठा packet_type *pt_prev = शून्य;
	काष्ठा list_head *ptype_list = &ptype_all;

	rcu_पढ़ो_lock();
again:
	list_क्रम_each_entry_rcu(ptype, ptype_list, list) अणु
		अगर (ptype->ignore_outgoing)
			जारी;

		/* Never send packets back to the socket
		 * they originated from - MvS (miquels@drinkel.ow.org)
		 */
		अगर (skb_loop_sk(ptype, skb))
			जारी;

		अगर (pt_prev) अणु
			deliver_skb(skb2, pt_prev, skb->dev);
			pt_prev = ptype;
			जारी;
		पूर्ण

		/* need to clone skb, करोne only once */
		skb2 = skb_clone(skb, GFP_ATOMIC);
		अगर (!skb2)
			जाओ out_unlock;

		net_बारtamp_set(skb2);

		/* skb->nh should be correctly
		 * set by sender, so that the second statement is
		 * just protection against buggy protocols.
		 */
		skb_reset_mac_header(skb2);

		अगर (skb_network_header(skb2) < skb2->data ||
		    skb_network_header(skb2) > skb_tail_poपूर्णांकer(skb2)) अणु
			net_crit_ratelimited("protocol %04x is buggy, dev %s\n",
					     ntohs(skb2->protocol),
					     dev->name);
			skb_reset_network_header(skb2);
		पूर्ण

		skb2->transport_header = skb2->network_header;
		skb2->pkt_type = PACKET_OUTGOING;
		pt_prev = ptype;
	पूर्ण

	अगर (ptype_list == &ptype_all) अणु
		ptype_list = &dev->ptype_all;
		जाओ again;
	पूर्ण
out_unlock:
	अगर (pt_prev) अणु
		अगर (!skb_orphan_frags_rx(skb2, GFP_ATOMIC))
			pt_prev->func(skb2, skb->dev, pt_prev, skb->dev);
		अन्यथा
			kमुक्त_skb(skb2);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(dev_queue_xmit_nit);

/**
 * netअगर_setup_tc - Handle tc mappings on real_num_tx_queues change
 * @dev: Network device
 * @txq: number of queues available
 *
 * If real_num_tx_queues is changed the tc mappings may no दीर्घer be
 * valid. To resolve this verअगरy the tc mapping reमुख्यs valid and अगर
 * not शून्य the mapping. With no priorities mapping to this
 * offset/count pair it will no दीर्घer be used. In the worst हाल TC0
 * is invalid nothing can be करोne so disable priority mappings. If is
 * expected that drivers will fix this mapping अगर they can beक्रमe
 * calling netअगर_set_real_num_tx_queues.
 */
अटल व्योम netअगर_setup_tc(काष्ठा net_device *dev, अचिन्हित पूर्णांक txq)
अणु
	पूर्णांक i;
	काष्ठा netdev_tc_txq *tc = &dev->tc_to_txq[0];

	/* If TC0 is invalidated disable TC mapping */
	अगर (tc->offset + tc->count > txq) अणु
		pr_warn("Number of in use tx queues changed invalidating tc mappings. Priority traffic classification disabled!\n");
		dev->num_tc = 0;
		वापस;
	पूर्ण

	/* Invalidated prio to tc mappings set to TC0 */
	क्रम (i = 1; i < TC_BITMASK + 1; i++) अणु
		पूर्णांक q = netdev_get_prio_tc_map(dev, i);

		tc = &dev->tc_to_txq[q];
		अगर (tc->offset + tc->count > txq) अणु
			pr_warn("Number of in use tx queues changed. Priority %i to tc mapping %i is no longer valid. Setting map to 0\n",
				i, q);
			netdev_set_prio_tc_map(dev, i, 0);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक netdev_txq_to_tc(काष्ठा net_device *dev, अचिन्हित पूर्णांक txq)
अणु
	अगर (dev->num_tc) अणु
		काष्ठा netdev_tc_txq *tc = &dev->tc_to_txq[0];
		पूर्णांक i;

		/* walk through the TCs and see अगर it falls पूर्णांकo any of them */
		क्रम (i = 0; i < TC_MAX_QUEUE; i++, tc++) अणु
			अगर ((txq - tc->offset) < tc->count)
				वापस i;
		पूर्ण

		/* didn't find it, just वापस -1 to indicate no match */
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_txq_to_tc);

#अगर_घोषित CONFIG_XPS
अटल काष्ठा अटल_key xps_needed __पढ़ो_mostly;
अटल काष्ठा अटल_key xps_rxqs_needed __पढ़ो_mostly;
अटल DEFINE_MUTEX(xps_map_mutex);
#घोषणा xmap_dereference(P)		\
	rcu_dereference_रक्षित((P), lockdep_is_held(&xps_map_mutex))

अटल bool हटाओ_xps_queue(काष्ठा xps_dev_maps *dev_maps,
			     काष्ठा xps_dev_maps *old_maps, पूर्णांक tci, u16 index)
अणु
	काष्ठा xps_map *map = शून्य;
	पूर्णांक pos;

	अगर (dev_maps)
		map = xmap_dereference(dev_maps->attr_map[tci]);
	अगर (!map)
		वापस false;

	क्रम (pos = map->len; pos--;) अणु
		अगर (map->queues[pos] != index)
			जारी;

		अगर (map->len > 1) अणु
			map->queues[pos] = map->queues[--map->len];
			अवरोध;
		पूर्ण

		अगर (old_maps)
			RCU_INIT_POINTER(old_maps->attr_map[tci], शून्य);
		RCU_INIT_POINTER(dev_maps->attr_map[tci], शून्य);
		kमुक्त_rcu(map, rcu);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool हटाओ_xps_queue_cpu(काष्ठा net_device *dev,
				 काष्ठा xps_dev_maps *dev_maps,
				 पूर्णांक cpu, u16 offset, u16 count)
अणु
	पूर्णांक num_tc = dev_maps->num_tc;
	bool active = false;
	पूर्णांक tci;

	क्रम (tci = cpu * num_tc; num_tc--; tci++) अणु
		पूर्णांक i, j;

		क्रम (i = count, j = offset; i--; j++) अणु
			अगर (!हटाओ_xps_queue(dev_maps, शून्य, tci, j))
				अवरोध;
		पूर्ण

		active |= i < 0;
	पूर्ण

	वापस active;
पूर्ण

अटल व्योम reset_xps_maps(काष्ठा net_device *dev,
			   काष्ठा xps_dev_maps *dev_maps,
			   क्रमागत xps_map_type type)
अणु
	अटल_key_slow_dec_cpuslocked(&xps_needed);
	अगर (type == XPS_RXQS)
		अटल_key_slow_dec_cpuslocked(&xps_rxqs_needed);

	RCU_INIT_POINTER(dev->xps_maps[type], शून्य);

	kमुक्त_rcu(dev_maps, rcu);
पूर्ण

अटल व्योम clean_xps_maps(काष्ठा net_device *dev, क्रमागत xps_map_type type,
			   u16 offset, u16 count)
अणु
	काष्ठा xps_dev_maps *dev_maps;
	bool active = false;
	पूर्णांक i, j;

	dev_maps = xmap_dereference(dev->xps_maps[type]);
	अगर (!dev_maps)
		वापस;

	क्रम (j = 0; j < dev_maps->nr_ids; j++)
		active |= हटाओ_xps_queue_cpu(dev, dev_maps, j, offset, count);
	अगर (!active)
		reset_xps_maps(dev, dev_maps, type);

	अगर (type == XPS_CPUS) अणु
		क्रम (i = offset + (count - 1); count--; i--)
			netdev_queue_numa_node_ग_लिखो(
				netdev_get_tx_queue(dev, i), NUMA_NO_NODE);
	पूर्ण
पूर्ण

अटल व्योम netअगर_reset_xps_queues(काष्ठा net_device *dev, u16 offset,
				   u16 count)
अणु
	अगर (!अटल_key_false(&xps_needed))
		वापस;

	cpus_पढ़ो_lock();
	mutex_lock(&xps_map_mutex);

	अगर (अटल_key_false(&xps_rxqs_needed))
		clean_xps_maps(dev, XPS_RXQS, offset, count);

	clean_xps_maps(dev, XPS_CPUS, offset, count);

	mutex_unlock(&xps_map_mutex);
	cpus_पढ़ो_unlock();
पूर्ण

अटल व्योम netअगर_reset_xps_queues_gt(काष्ठा net_device *dev, u16 index)
अणु
	netअगर_reset_xps_queues(dev, index, dev->num_tx_queues - index);
पूर्ण

अटल काष्ठा xps_map *expand_xps_map(काष्ठा xps_map *map, पूर्णांक attr_index,
				      u16 index, bool is_rxqs_map)
अणु
	काष्ठा xps_map *new_map;
	पूर्णांक alloc_len = XPS_MIN_MAP_ALLOC;
	पूर्णांक i, pos;

	क्रम (pos = 0; map && pos < map->len; pos++) अणु
		अगर (map->queues[pos] != index)
			जारी;
		वापस map;
	पूर्ण

	/* Need to add tx-queue to this CPU's/rx-queue's existing map */
	अगर (map) अणु
		अगर (pos < map->alloc_len)
			वापस map;

		alloc_len = map->alloc_len * 2;
	पूर्ण

	/* Need to allocate new map to store tx-queue on this CPU's/rx-queue's
	 *  map
	 */
	अगर (is_rxqs_map)
		new_map = kzalloc(XPS_MAP_SIZE(alloc_len), GFP_KERNEL);
	अन्यथा
		new_map = kzalloc_node(XPS_MAP_SIZE(alloc_len), GFP_KERNEL,
				       cpu_to_node(attr_index));
	अगर (!new_map)
		वापस शून्य;

	क्रम (i = 0; i < pos; i++)
		new_map->queues[i] = map->queues[i];
	new_map->alloc_len = alloc_len;
	new_map->len = pos;

	वापस new_map;
पूर्ण

/* Copy xps maps at a given index */
अटल व्योम xps_copy_dev_maps(काष्ठा xps_dev_maps *dev_maps,
			      काष्ठा xps_dev_maps *new_dev_maps, पूर्णांक index,
			      पूर्णांक tc, bool skip_tc)
अणु
	पूर्णांक i, tci = index * dev_maps->num_tc;
	काष्ठा xps_map *map;

	/* copy maps beदीर्घing to क्रमeign traffic classes */
	क्रम (i = 0; i < dev_maps->num_tc; i++, tci++) अणु
		अगर (i == tc && skip_tc)
			जारी;

		/* fill in the new device map from the old device map */
		map = xmap_dereference(dev_maps->attr_map[tci]);
		RCU_INIT_POINTER(new_dev_maps->attr_map[tci], map);
	पूर्ण
पूर्ण

/* Must be called under cpus_पढ़ो_lock */
पूर्णांक __netअगर_set_xps_queue(काष्ठा net_device *dev, स्थिर अचिन्हित दीर्घ *mask,
			  u16 index, क्रमागत xps_map_type type)
अणु
	काष्ठा xps_dev_maps *dev_maps, *new_dev_maps = शून्य, *old_dev_maps = शून्य;
	स्थिर अचिन्हित दीर्घ *online_mask = शून्य;
	bool active = false, copy = false;
	पूर्णांक i, j, tci, numa_node_id = -2;
	पूर्णांक maps_sz, num_tc = 1, tc = 0;
	काष्ठा xps_map *map, *new_map;
	अचिन्हित पूर्णांक nr_ids;

	अगर (dev->num_tc) अणु
		/* Do not allow XPS on subordinate device directly */
		num_tc = dev->num_tc;
		अगर (num_tc < 0)
			वापस -EINVAL;

		/* If queue beदीर्घs to subordinate dev use its map */
		dev = netdev_get_tx_queue(dev, index)->sb_dev ? : dev;

		tc = netdev_txq_to_tc(dev, index);
		अगर (tc < 0)
			वापस -EINVAL;
	पूर्ण

	mutex_lock(&xps_map_mutex);

	dev_maps = xmap_dereference(dev->xps_maps[type]);
	अगर (type == XPS_RXQS) अणु
		maps_sz = XPS_RXQ_DEV_MAPS_SIZE(num_tc, dev->num_rx_queues);
		nr_ids = dev->num_rx_queues;
	पूर्ण अन्यथा अणु
		maps_sz = XPS_CPU_DEV_MAPS_SIZE(num_tc);
		अगर (num_possible_cpus() > 1)
			online_mask = cpumask_bits(cpu_online_mask);
		nr_ids = nr_cpu_ids;
	पूर्ण

	अगर (maps_sz < L1_CACHE_BYTES)
		maps_sz = L1_CACHE_BYTES;

	/* The old dev_maps could be larger or smaller than the one we're
	 * setting up now, as dev->num_tc or nr_ids could have been updated in
	 * between. We could try to be smart, but let's be safe instead and only
	 * copy क्रमeign traffic classes अगर the two map sizes match.
	 */
	अगर (dev_maps &&
	    dev_maps->num_tc == num_tc && dev_maps->nr_ids == nr_ids)
		copy = true;

	/* allocate memory क्रम queue storage */
	क्रम (j = -1; j = netअगर_attrmask_next_and(j, online_mask, mask, nr_ids),
	     j < nr_ids;) अणु
		अगर (!new_dev_maps) अणु
			new_dev_maps = kzalloc(maps_sz, GFP_KERNEL);
			अगर (!new_dev_maps) अणु
				mutex_unlock(&xps_map_mutex);
				वापस -ENOMEM;
			पूर्ण

			new_dev_maps->nr_ids = nr_ids;
			new_dev_maps->num_tc = num_tc;
		पूर्ण

		tci = j * num_tc + tc;
		map = copy ? xmap_dereference(dev_maps->attr_map[tci]) : शून्य;

		map = expand_xps_map(map, j, index, type == XPS_RXQS);
		अगर (!map)
			जाओ error;

		RCU_INIT_POINTER(new_dev_maps->attr_map[tci], map);
	पूर्ण

	अगर (!new_dev_maps)
		जाओ out_no_new_maps;

	अगर (!dev_maps) अणु
		/* Increment अटल keys at most once per type */
		अटल_key_slow_inc_cpuslocked(&xps_needed);
		अगर (type == XPS_RXQS)
			अटल_key_slow_inc_cpuslocked(&xps_rxqs_needed);
	पूर्ण

	क्रम (j = 0; j < nr_ids; j++) अणु
		bool skip_tc = false;

		tci = j * num_tc + tc;
		अगर (netअगर_attr_test_mask(j, mask, nr_ids) &&
		    netअगर_attr_test_online(j, online_mask, nr_ids)) अणु
			/* add tx-queue to CPU/rx-queue maps */
			पूर्णांक pos = 0;

			skip_tc = true;

			map = xmap_dereference(new_dev_maps->attr_map[tci]);
			जबतक ((pos < map->len) && (map->queues[pos] != index))
				pos++;

			अगर (pos == map->len)
				map->queues[map->len++] = index;
#अगर_घोषित CONFIG_NUMA
			अगर (type == XPS_CPUS) अणु
				अगर (numa_node_id == -2)
					numa_node_id = cpu_to_node(j);
				अन्यथा अगर (numa_node_id != cpu_to_node(j))
					numa_node_id = -1;
			पूर्ण
#पूर्ण_अगर
		पूर्ण

		अगर (copy)
			xps_copy_dev_maps(dev_maps, new_dev_maps, j, tc,
					  skip_tc);
	पूर्ण

	rcu_assign_poपूर्णांकer(dev->xps_maps[type], new_dev_maps);

	/* Cleanup old maps */
	अगर (!dev_maps)
		जाओ out_no_old_maps;

	क्रम (j = 0; j < dev_maps->nr_ids; j++) अणु
		क्रम (i = num_tc, tci = j * dev_maps->num_tc; i--; tci++) अणु
			map = xmap_dereference(dev_maps->attr_map[tci]);
			अगर (!map)
				जारी;

			अगर (copy) अणु
				new_map = xmap_dereference(new_dev_maps->attr_map[tci]);
				अगर (map == new_map)
					जारी;
			पूर्ण

			RCU_INIT_POINTER(dev_maps->attr_map[tci], शून्य);
			kमुक्त_rcu(map, rcu);
		पूर्ण
	पूर्ण

	old_dev_maps = dev_maps;

out_no_old_maps:
	dev_maps = new_dev_maps;
	active = true;

out_no_new_maps:
	अगर (type == XPS_CPUS)
		/* update Tx queue numa node */
		netdev_queue_numa_node_ग_लिखो(netdev_get_tx_queue(dev, index),
					     (numa_node_id >= 0) ?
					     numa_node_id : NUMA_NO_NODE);

	अगर (!dev_maps)
		जाओ out_no_maps;

	/* हटाओs tx-queue from unused CPUs/rx-queues */
	क्रम (j = 0; j < dev_maps->nr_ids; j++) अणु
		tci = j * dev_maps->num_tc;

		क्रम (i = 0; i < dev_maps->num_tc; i++, tci++) अणु
			अगर (i == tc &&
			    netअगर_attr_test_mask(j, mask, dev_maps->nr_ids) &&
			    netअगर_attr_test_online(j, online_mask, dev_maps->nr_ids))
				जारी;

			active |= हटाओ_xps_queue(dev_maps,
						   copy ? old_dev_maps : शून्य,
						   tci, index);
		पूर्ण
	पूर्ण

	अगर (old_dev_maps)
		kमुक्त_rcu(old_dev_maps, rcu);

	/* मुक्त map अगर not active */
	अगर (!active)
		reset_xps_maps(dev, dev_maps, type);

out_no_maps:
	mutex_unlock(&xps_map_mutex);

	वापस 0;
error:
	/* हटाओ any maps that we added */
	क्रम (j = 0; j < nr_ids; j++) अणु
		क्रम (i = num_tc, tci = j * num_tc; i--; tci++) अणु
			new_map = xmap_dereference(new_dev_maps->attr_map[tci]);
			map = copy ?
			      xmap_dereference(dev_maps->attr_map[tci]) :
			      शून्य;
			अगर (new_map && new_map != map)
				kमुक्त(new_map);
		पूर्ण
	पूर्ण

	mutex_unlock(&xps_map_mutex);

	kमुक्त(new_dev_maps);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(__netअगर_set_xps_queue);

पूर्णांक netअगर_set_xps_queue(काष्ठा net_device *dev, स्थिर काष्ठा cpumask *mask,
			u16 index)
अणु
	पूर्णांक ret;

	cpus_पढ़ो_lock();
	ret =  __netअगर_set_xps_queue(dev, cpumask_bits(mask), index, XPS_CPUS);
	cpus_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(netअगर_set_xps_queue);

#पूर्ण_अगर
अटल व्योम netdev_unbind_all_sb_channels(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_queue *txq = &dev->_tx[dev->num_tx_queues];

	/* Unbind any subordinate channels */
	जबतक (txq-- != &dev->_tx[0]) अणु
		अगर (txq->sb_dev)
			netdev_unbind_sb_channel(dev, txq->sb_dev);
	पूर्ण
पूर्ण

व्योम netdev_reset_tc(काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_XPS
	netअगर_reset_xps_queues_gt(dev, 0);
#पूर्ण_अगर
	netdev_unbind_all_sb_channels(dev);

	/* Reset TC configuration of device */
	dev->num_tc = 0;
	स_रखो(dev->tc_to_txq, 0, माप(dev->tc_to_txq));
	स_रखो(dev->prio_tc_map, 0, माप(dev->prio_tc_map));
पूर्ण
EXPORT_SYMBOL(netdev_reset_tc);

पूर्णांक netdev_set_tc_queue(काष्ठा net_device *dev, u8 tc, u16 count, u16 offset)
अणु
	अगर (tc >= dev->num_tc)
		वापस -EINVAL;

#अगर_घोषित CONFIG_XPS
	netअगर_reset_xps_queues(dev, offset, count);
#पूर्ण_अगर
	dev->tc_to_txq[tc].count = count;
	dev->tc_to_txq[tc].offset = offset;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_set_tc_queue);

पूर्णांक netdev_set_num_tc(काष्ठा net_device *dev, u8 num_tc)
अणु
	अगर (num_tc > TC_MAX_QUEUE)
		वापस -EINVAL;

#अगर_घोषित CONFIG_XPS
	netअगर_reset_xps_queues_gt(dev, 0);
#पूर्ण_अगर
	netdev_unbind_all_sb_channels(dev);

	dev->num_tc = num_tc;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_set_num_tc);

व्योम netdev_unbind_sb_channel(काष्ठा net_device *dev,
			      काष्ठा net_device *sb_dev)
अणु
	काष्ठा netdev_queue *txq = &dev->_tx[dev->num_tx_queues];

#अगर_घोषित CONFIG_XPS
	netअगर_reset_xps_queues_gt(sb_dev, 0);
#पूर्ण_अगर
	स_रखो(sb_dev->tc_to_txq, 0, माप(sb_dev->tc_to_txq));
	स_रखो(sb_dev->prio_tc_map, 0, माप(sb_dev->prio_tc_map));

	जबतक (txq-- != &dev->_tx[0]) अणु
		अगर (txq->sb_dev == sb_dev)
			txq->sb_dev = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netdev_unbind_sb_channel);

पूर्णांक netdev_bind_sb_channel_queue(काष्ठा net_device *dev,
				 काष्ठा net_device *sb_dev,
				 u8 tc, u16 count, u16 offset)
अणु
	/* Make certain the sb_dev and dev are alपढ़ोy configured */
	अगर (sb_dev->num_tc >= 0 || tc >= dev->num_tc)
		वापस -EINVAL;

	/* We cannot hand out queues we करोn't have */
	अगर ((offset + count) > dev->real_num_tx_queues)
		वापस -EINVAL;

	/* Record the mapping */
	sb_dev->tc_to_txq[tc].count = count;
	sb_dev->tc_to_txq[tc].offset = offset;

	/* Provide a way क्रम Tx queue to find the tc_to_txq map or
	 * XPS map क्रम itself.
	 */
	जबतक (count--)
		netdev_get_tx_queue(dev, count + offset)->sb_dev = sb_dev;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_bind_sb_channel_queue);

पूर्णांक netdev_set_sb_channel(काष्ठा net_device *dev, u16 channel)
अणु
	/* Do not use a multiqueue device to represent a subordinate channel */
	अगर (netअगर_is_multiqueue(dev))
		वापस -ENODEV;

	/* We allow channels 1 - 32767 to be used क्रम subordinate channels.
	 * Channel 0 is meant to be "native" mode and used only to represent
	 * the मुख्य root device. We allow writing 0 to reset the device back
	 * to normal mode after being used as a subordinate channel.
	 */
	अगर (channel > S16_MAX)
		वापस -EINVAL;

	dev->num_tc = -channel;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_set_sb_channel);

/*
 * Routine to help set real_num_tx_queues. To aव्योम skbs mapped to queues
 * greater than real_num_tx_queues stale skbs on the qdisc must be flushed.
 */
पूर्णांक netअगर_set_real_num_tx_queues(काष्ठा net_device *dev, अचिन्हित पूर्णांक txq)
अणु
	bool disabling;
	पूर्णांक rc;

	disabling = txq < dev->real_num_tx_queues;

	अगर (txq < 1 || txq > dev->num_tx_queues)
		वापस -EINVAL;

	अगर (dev->reg_state == NETREG_REGISTERED ||
	    dev->reg_state == NETREG_UNREGISTERING) अणु
		ASSERT_RTNL();

		rc = netdev_queue_update_kobjects(dev, dev->real_num_tx_queues,
						  txq);
		अगर (rc)
			वापस rc;

		अगर (dev->num_tc)
			netअगर_setup_tc(dev, txq);

		dev->real_num_tx_queues = txq;

		अगर (disabling) अणु
			synchronize_net();
			qdisc_reset_all_tx_gt(dev, txq);
#अगर_घोषित CONFIG_XPS
			netअगर_reset_xps_queues_gt(dev, txq);
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->real_num_tx_queues = txq;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netअगर_set_real_num_tx_queues);

#अगर_घोषित CONFIG_SYSFS
/**
 *	netअगर_set_real_num_rx_queues - set actual number of RX queues used
 *	@dev: Network device
 *	@rxq: Actual number of RX queues
 *
 *	This must be called either with the rtnl_lock held or beक्रमe
 *	registration of the net device.  Returns 0 on success, or a
 *	negative error code.  If called beक्रमe registration, it always
 *	succeeds.
 */
पूर्णांक netअगर_set_real_num_rx_queues(काष्ठा net_device *dev, अचिन्हित पूर्णांक rxq)
अणु
	पूर्णांक rc;

	अगर (rxq < 1 || rxq > dev->num_rx_queues)
		वापस -EINVAL;

	अगर (dev->reg_state == NETREG_REGISTERED) अणु
		ASSERT_RTNL();

		rc = net_rx_queue_update_kobjects(dev, dev->real_num_rx_queues,
						  rxq);
		अगर (rc)
			वापस rc;
	पूर्ण

	dev->real_num_rx_queues = rxq;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(netअगर_set_real_num_rx_queues);
#पूर्ण_अगर

/**
 * netअगर_get_num_शेष_rss_queues - शेष number of RSS queues
 *
 * This routine should set an upper limit on the number of RSS queues
 * used by शेष by multiqueue devices.
 */
पूर्णांक netअगर_get_num_शेष_rss_queues(व्योम)
अणु
	वापस is_kdump_kernel() ?
		1 : min_t(पूर्णांक, DEFAULT_MAX_NUM_RSS_QUEUES, num_online_cpus());
पूर्ण
EXPORT_SYMBOL(netअगर_get_num_शेष_rss_queues);

अटल व्योम __netअगर_reschedule(काष्ठा Qdisc *q)
अणु
	काष्ठा softnet_data *sd;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	sd = this_cpu_ptr(&softnet_data);
	q->next_sched = शून्य;
	*sd->output_queue_tailp = q;
	sd->output_queue_tailp = &q->next_sched;
	उठाओ_softirq_irqoff(NET_TX_SOFTIRQ);
	local_irq_restore(flags);
पूर्ण

व्योम __netअगर_schedule(काष्ठा Qdisc *q)
अणु
	अगर (!test_and_set_bit(__QDISC_STATE_SCHED, &q->state))
		__netअगर_reschedule(q);
पूर्ण
EXPORT_SYMBOL(__netअगर_schedule);

काष्ठा dev_kमुक्त_skb_cb अणु
	क्रमागत skb_मुक्त_reason reason;
पूर्ण;

अटल काष्ठा dev_kमुक्त_skb_cb *get_kमुक्त_skb_cb(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा dev_kमुक्त_skb_cb *)skb->cb;
पूर्ण

व्योम netअगर_schedule_queue(काष्ठा netdev_queue *txq)
अणु
	rcu_पढ़ो_lock();
	अगर (!netअगर_xmit_stopped(txq)) अणु
		काष्ठा Qdisc *q = rcu_dereference(txq->qdisc);

		__netअगर_schedule(q);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(netअगर_schedule_queue);

व्योम netअगर_tx_wake_queue(काष्ठा netdev_queue *dev_queue)
अणु
	अगर (test_and_clear_bit(__QUEUE_STATE_DRV_XOFF, &dev_queue->state)) अणु
		काष्ठा Qdisc *q;

		rcu_पढ़ो_lock();
		q = rcu_dereference(dev_queue->qdisc);
		__netअगर_schedule(q);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netअगर_tx_wake_queue);

व्योम __dev_kमुक्त_skb_irq(काष्ठा sk_buff *skb, क्रमागत skb_मुक्त_reason reason)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!skb))
		वापस;

	अगर (likely(refcount_पढ़ो(&skb->users) == 1)) अणु
		smp_rmb();
		refcount_set(&skb->users, 0);
	पूर्ण अन्यथा अगर (likely(!refcount_dec_and_test(&skb->users))) अणु
		वापस;
	पूर्ण
	get_kमुक्त_skb_cb(skb)->reason = reason;
	local_irq_save(flags);
	skb->next = __this_cpu_पढ़ो(softnet_data.completion_queue);
	__this_cpu_ग_लिखो(softnet_data.completion_queue, skb);
	उठाओ_softirq_irqoff(NET_TX_SOFTIRQ);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(__dev_kमुक्त_skb_irq);

व्योम __dev_kमुक्त_skb_any(काष्ठा sk_buff *skb, क्रमागत skb_मुक्त_reason reason)
अणु
	अगर (in_irq() || irqs_disabled())
		__dev_kमुक्त_skb_irq(skb, reason);
	अन्यथा
		dev_kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(__dev_kमुक्त_skb_any);


/**
 * netअगर_device_detach - mark device as हटाओd
 * @dev: network device
 *
 * Mark device as हटाओd from प्रणाली and thereक्रमe no दीर्घer available.
 */
व्योम netअगर_device_detach(काष्ठा net_device *dev)
अणु
	अगर (test_and_clear_bit(__LINK_STATE_PRESENT, &dev->state) &&
	    netअगर_running(dev)) अणु
		netअगर_tx_stop_all_queues(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netअगर_device_detach);

/**
 * netअगर_device_attach - mark device as attached
 * @dev: network device
 *
 * Mark device as attached from प्रणाली and restart अगर needed.
 */
व्योम netअगर_device_attach(काष्ठा net_device *dev)
अणु
	अगर (!test_and_set_bit(__LINK_STATE_PRESENT, &dev->state) &&
	    netअगर_running(dev)) अणु
		netअगर_tx_wake_all_queues(dev);
		__netdev_watchकरोg_up(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netअगर_device_attach);

/*
 * Returns a Tx hash based on the given packet descriptor a Tx queues' number
 * to be used as a distribution range.
 */
अटल u16 skb_tx_hash(स्थिर काष्ठा net_device *dev,
		       स्थिर काष्ठा net_device *sb_dev,
		       काष्ठा sk_buff *skb)
अणु
	u32 hash;
	u16 qoffset = 0;
	u16 qcount = dev->real_num_tx_queues;

	अगर (dev->num_tc) अणु
		u8 tc = netdev_get_prio_tc_map(dev, skb->priority);

		qoffset = sb_dev->tc_to_txq[tc].offset;
		qcount = sb_dev->tc_to_txq[tc].count;
	पूर्ण

	अगर (skb_rx_queue_recorded(skb)) अणु
		hash = skb_get_rx_queue(skb);
		अगर (hash >= qoffset)
			hash -= qoffset;
		जबतक (unlikely(hash >= qcount))
			hash -= qcount;
		वापस hash + qoffset;
	पूर्ण

	वापस (u16) reciprocal_scale(skb_get_hash(skb), qcount) + qoffset;
पूर्ण

अटल व्योम skb_warn_bad_offload(स्थिर काष्ठा sk_buff *skb)
अणु
	अटल स्थिर netdev_features_t null_features;
	काष्ठा net_device *dev = skb->dev;
	स्थिर अक्षर *name = "";

	अगर (!net_ratelimit())
		वापस;

	अगर (dev) अणु
		अगर (dev->dev.parent)
			name = dev_driver_string(dev->dev.parent);
		अन्यथा
			name = netdev_name(dev);
	पूर्ण
	skb_dump(KERN_WARNING, skb, false);
	WARN(1, "%s: caps=(%pNF, %pNF)\n",
	     name, dev ? &dev->features : &null_features,
	     skb->sk ? &skb->sk->sk_route_caps : &null_features);
पूर्ण

/*
 * Invalidate hardware checksum when packet is to be mangled, and
 * complete checksum manually on outgoing path.
 */
पूर्णांक skb_checksum_help(काष्ठा sk_buff *skb)
अणु
	__wsum csum;
	पूर्णांक ret = 0, offset;

	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		जाओ out_set_summed;

	अगर (unlikely(skb_is_gso(skb))) अणु
		skb_warn_bad_offload(skb);
		वापस -EINVAL;
	पूर्ण

	/* Beक्रमe computing a checksum, we should make sure no frag could
	 * be modअगरied by an बाह्यal entity : checksum could be wrong.
	 */
	अगर (skb_has_shared_frag(skb)) अणु
		ret = __skb_linearize(skb);
		अगर (ret)
			जाओ out;
	पूर्ण

	offset = skb_checksum_start_offset(skb);
	BUG_ON(offset >= skb_headlen(skb));
	csum = skb_checksum(skb, offset, skb->len - offset, 0);

	offset += skb->csum_offset;
	BUG_ON(offset + माप(__sum16) > skb_headlen(skb));

	ret = skb_ensure_writable(skb, offset + माप(__sum16));
	अगर (ret)
		जाओ out;

	*(__sum16 *)(skb->data + offset) = csum_fold(csum) ?: CSUM_MANGLED_0;
out_set_summed:
	skb->ip_summed = CHECKSUM_NONE;
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(skb_checksum_help);

पूर्णांक skb_crc32c_csum_help(काष्ठा sk_buff *skb)
अणु
	__le32 crc32c_csum;
	पूर्णांक ret = 0, offset, start;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		जाओ out;

	अगर (unlikely(skb_is_gso(skb)))
		जाओ out;

	/* Beक्रमe computing a checksum, we should make sure no frag could
	 * be modअगरied by an बाह्यal entity : checksum could be wrong.
	 */
	अगर (unlikely(skb_has_shared_frag(skb))) अणु
		ret = __skb_linearize(skb);
		अगर (ret)
			जाओ out;
	पूर्ण
	start = skb_checksum_start_offset(skb);
	offset = start + दुरत्व(काष्ठा sctphdr, checksum);
	अगर (WARN_ON_ONCE(offset >= skb_headlen(skb))) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = skb_ensure_writable(skb, offset + माप(__le32));
	अगर (ret)
		जाओ out;

	crc32c_csum = cpu_to_le32(~__skb_checksum(skb, start,
						  skb->len - start, ~(__u32)0,
						  crc32c_csum_stub));
	*(__le32 *)(skb->data + offset) = crc32c_csum;
	skb->ip_summed = CHECKSUM_NONE;
	skb->csum_not_inet = 0;
out:
	वापस ret;
पूर्ण

__be16 skb_network_protocol(काष्ठा sk_buff *skb, पूर्णांक *depth)
अणु
	__be16 type = skb->protocol;

	/* Tunnel gso handlers can set protocol to ethernet. */
	अगर (type == htons(ETH_P_TEB)) अणु
		काष्ठा ethhdr *eth;

		अगर (unlikely(!pskb_may_pull(skb, माप(काष्ठा ethhdr))))
			वापस 0;

		eth = (काष्ठा ethhdr *)skb->data;
		type = eth->h_proto;
	पूर्ण

	वापस __vlan_get_protocol(skb, type, depth);
पूर्ण

/**
 *	skb_mac_gso_segment - mac layer segmentation handler.
 *	@skb: buffer to segment
 *	@features: features क्रम the output path (see dev->features)
 */
काष्ठा sk_buff *skb_mac_gso_segment(काष्ठा sk_buff *skb,
				    netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = ERR_PTR(-EPROTONOSUPPORT);
	काष्ठा packet_offload *ptype;
	पूर्णांक vlan_depth = skb->mac_len;
	__be16 type = skb_network_protocol(skb, &vlan_depth);

	अगर (unlikely(!type))
		वापस ERR_PTR(-EINVAL);

	__skb_pull(skb, vlan_depth);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ptype, &offload_base, list) अणु
		अगर (ptype->type == type && ptype->callbacks.gso_segment) अणु
			segs = ptype->callbacks.gso_segment(skb, features);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	__skb_push(skb, skb->data - skb_mac_header(skb));

	वापस segs;
पूर्ण
EXPORT_SYMBOL(skb_mac_gso_segment);


/* खोलोvचयन calls this on rx path, so we need a dअगरferent check.
 */
अटल अंतरभूत bool skb_needs_check(काष्ठा sk_buff *skb, bool tx_path)
अणु
	अगर (tx_path)
		वापस skb->ip_summed != CHECKSUM_PARTIAL &&
		       skb->ip_summed != CHECKSUM_UNNECESSARY;

	वापस skb->ip_summed == CHECKSUM_NONE;
पूर्ण

/**
 *	__skb_gso_segment - Perक्रमm segmentation on skb.
 *	@skb: buffer to segment
 *	@features: features क्रम the output path (see dev->features)
 *	@tx_path: whether it is called in TX path
 *
 *	This function segments the given skb and वापसs a list of segments.
 *
 *	It may वापस शून्य अगर the skb requires no segmentation.  This is
 *	only possible when GSO is used क्रम verअगरying header पूर्णांकegrity.
 *
 *	Segmentation preserves SKB_GSO_CB_OFFSET bytes of previous skb cb.
 */
काष्ठा sk_buff *__skb_gso_segment(काष्ठा sk_buff *skb,
				  netdev_features_t features, bool tx_path)
अणु
	काष्ठा sk_buff *segs;

	अगर (unlikely(skb_needs_check(skb, tx_path))) अणु
		पूर्णांक err;

		/* We're going to init ->check field in TCP or UDP header */
		err = skb_cow_head(skb, 0);
		अगर (err < 0)
			वापस ERR_PTR(err);
	पूर्ण

	/* Only report GSO partial support अगर it will enable us to
	 * support segmentation on this frame without needing additional
	 * work.
	 */
	अगर (features & NETIF_F_GSO_PARTIAL) अणु
		netdev_features_t partial_features = NETIF_F_GSO_ROBUST;
		काष्ठा net_device *dev = skb->dev;

		partial_features |= dev->features & dev->gso_partial_features;
		अगर (!skb_gso_ok(skb, features | partial_features))
			features &= ~NETIF_F_GSO_PARTIAL;
	पूर्ण

	BUILD_BUG_ON(SKB_GSO_CB_OFFSET +
		     माप(*SKB_GSO_CB(skb)) > माप(skb->cb));

	SKB_GSO_CB(skb)->mac_offset = skb_headroom(skb);
	SKB_GSO_CB(skb)->encap_level = 0;

	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);

	segs = skb_mac_gso_segment(skb, features);

	अगर (segs != skb && unlikely(skb_needs_check(skb, tx_path) && !IS_ERR(segs)))
		skb_warn_bad_offload(skb);

	वापस segs;
पूर्ण
EXPORT_SYMBOL(__skb_gso_segment);

/* Take action when hardware reception checksum errors are detected. */
#अगर_घोषित CONFIG_BUG
व्योम netdev_rx_csum_fault(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	अगर (net_ratelimit()) अणु
		pr_err("%s: hw csum failure\n", dev ? dev->name : "<unknown>");
		skb_dump(KERN_ERR, skb, true);
		dump_stack();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netdev_rx_csum_fault);
#पूर्ण_अगर

/* XXX: check that highmem exists at all on the given machine. */
अटल पूर्णांक illegal_highdma(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	पूर्णांक i;

	अगर (!(dev->features & NETIF_F_HIGHDMA)) अणु
		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			अगर (PageHighMem(skb_frag_page(frag)))
				वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* If MPLS offload request, verअगरy we are testing hardware MPLS features
 * instead of standard features क्रम the netdev.
 */
#अगर IS_ENABLED(CONFIG_NET_MPLS_GSO)
अटल netdev_features_t net_mpls_features(काष्ठा sk_buff *skb,
					   netdev_features_t features,
					   __be16 type)
अणु
	अगर (eth_p_mpls(type))
		features &= skb->dev->mpls_features;

	वापस features;
पूर्ण
#अन्यथा
अटल netdev_features_t net_mpls_features(काष्ठा sk_buff *skb,
					   netdev_features_t features,
					   __be16 type)
अणु
	वापस features;
पूर्ण
#पूर्ण_अगर

अटल netdev_features_t harmonize_features(काष्ठा sk_buff *skb,
	netdev_features_t features)
अणु
	__be16 type;

	type = skb_network_protocol(skb, शून्य);
	features = net_mpls_features(skb, features, type);

	अगर (skb->ip_summed != CHECKSUM_NONE &&
	    !can_checksum_protocol(features, type)) अणु
		features &= ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	पूर्ण
	अगर (illegal_highdma(skb->dev, skb))
		features &= ~NETIF_F_SG;

	वापस features;
पूर्ण

netdev_features_t passthru_features_check(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev,
					  netdev_features_t features)
अणु
	वापस features;
पूर्ण
EXPORT_SYMBOL(passthru_features_check);

अटल netdev_features_t dflt_features_check(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	वापस vlan_features_check(skb, features);
पूर्ण

अटल netdev_features_t gso_features_check(स्थिर काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev,
					    netdev_features_t features)
अणु
	u16 gso_segs = skb_shinfo(skb)->gso_segs;

	अगर (gso_segs > dev->gso_max_segs)
		वापस features & ~NETIF_F_GSO_MASK;

	अगर (!skb_shinfo(skb)->gso_type) अणु
		skb_warn_bad_offload(skb);
		वापस features & ~NETIF_F_GSO_MASK;
	पूर्ण

	/* Support क्रम GSO partial features requires software
	 * पूर्णांकervention beक्रमe we can actually process the packets
	 * so we need to strip support क्रम any partial features now
	 * and we can pull them back in after we have partially
	 * segmented the frame.
	 */
	अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL))
		features &= ~dev->gso_partial_features;

	/* Make sure to clear the IPv4 ID mangling feature अगर the
	 * IPv4 header has the potential to be fragmented.
	 */
	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4) अणु
		काष्ठा iphdr *iph = skb->encapsulation ?
				    inner_ip_hdr(skb) : ip_hdr(skb);

		अगर (!(iph->frag_off & htons(IP_DF)))
			features &= ~NETIF_F_TSO_MANGLEID;
	पूर्ण

	वापस features;
पूर्ण

netdev_features_t netअगर_skb_features(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	netdev_features_t features = dev->features;

	अगर (skb_is_gso(skb))
		features = gso_features_check(skb, dev, features);

	/* If encapsulation offload request, verअगरy we are testing
	 * hardware encapsulation features instead of standard
	 * features क्रम the netdev
	 */
	अगर (skb->encapsulation)
		features &= dev->hw_enc_features;

	अगर (skb_vlan_tagged(skb))
		features = netdev_पूर्णांकersect_features(features,
						     dev->vlan_features |
						     NETIF_F_HW_VLAN_CTAG_TX |
						     NETIF_F_HW_VLAN_STAG_TX);

	अगर (dev->netdev_ops->nकरो_features_check)
		features &= dev->netdev_ops->nकरो_features_check(skb, dev,
								features);
	अन्यथा
		features &= dflt_features_check(skb, dev, features);

	वापस harmonize_features(skb, features);
पूर्ण
EXPORT_SYMBOL(netअगर_skb_features);

अटल पूर्णांक xmit_one(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		    काष्ठा netdev_queue *txq, bool more)
अणु
	अचिन्हित पूर्णांक len;
	पूर्णांक rc;

	अगर (dev_nit_active(dev))
		dev_queue_xmit_nit(skb, dev);

	len = skb->len;
	PRANDOM_ADD_NOISE(skb, dev, txq, len + jअगरfies);
	trace_net_dev_start_xmit(skb, dev);
	rc = netdev_start_xmit(skb, dev, txq, more);
	trace_net_dev_xmit(skb, rc, dev, len);

	वापस rc;
पूर्ण

काष्ठा sk_buff *dev_hard_start_xmit(काष्ठा sk_buff *first, काष्ठा net_device *dev,
				    काष्ठा netdev_queue *txq, पूर्णांक *ret)
अणु
	काष्ठा sk_buff *skb = first;
	पूर्णांक rc = NETDEV_TX_OK;

	जबतक (skb) अणु
		काष्ठा sk_buff *next = skb->next;

		skb_mark_not_on_list(skb);
		rc = xmit_one(skb, dev, txq, next != शून्य);
		अगर (unlikely(!dev_xmit_complete(rc))) अणु
			skb->next = next;
			जाओ out;
		पूर्ण

		skb = next;
		अगर (netअगर_tx_queue_stopped(txq) && skb) अणु
			rc = NETDEV_TX_BUSY;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	*ret = rc;
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *validate_xmit_vlan(काष्ठा sk_buff *skb,
					  netdev_features_t features)
अणु
	अगर (skb_vlan_tag_present(skb) &&
	    !vlan_hw_offload_capable(features, skb->vlan_proto))
		skb = __vlan_hwaccel_push_inside(skb);
	वापस skb;
पूर्ण

पूर्णांक skb_csum_hwoffload_help(काष्ठा sk_buff *skb,
			    स्थिर netdev_features_t features)
अणु
	अगर (unlikely(skb_csum_is_sctp(skb)))
		वापस !!(features & NETIF_F_SCTP_CRC) ? 0 :
			skb_crc32c_csum_help(skb);

	अगर (features & NETIF_F_HW_CSUM)
		वापस 0;

	अगर (features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) अणु
		चयन (skb->csum_offset) अणु
		हाल दुरत्व(काष्ठा tcphdr, check):
		हाल दुरत्व(काष्ठा udphdr, check):
			वापस 0;
		पूर्ण
	पूर्ण

	वापस skb_checksum_help(skb);
पूर्ण
EXPORT_SYMBOL(skb_csum_hwoffload_help);

अटल काष्ठा sk_buff *validate_xmit_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev, bool *again)
अणु
	netdev_features_t features;

	features = netअगर_skb_features(skb);
	skb = validate_xmit_vlan(skb, features);
	अगर (unlikely(!skb))
		जाओ out_null;

	skb = sk_validate_xmit_skb(skb, dev);
	अगर (unlikely(!skb))
		जाओ out_null;

	अगर (netअगर_needs_gso(skb, features)) अणु
		काष्ठा sk_buff *segs;

		segs = skb_gso_segment(skb, features);
		अगर (IS_ERR(segs)) अणु
			जाओ out_kमुक्त_skb;
		पूर्ण अन्यथा अगर (segs) अणु
			consume_skb(skb);
			skb = segs;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (skb_needs_linearize(skb, features) &&
		    __skb_linearize(skb))
			जाओ out_kमुक्त_skb;

		/* If packet is not checksummed and device करोes not
		 * support checksumming क्रम this protocol, complete
		 * checksumming here.
		 */
		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			अगर (skb->encapsulation)
				skb_set_inner_transport_header(skb,
							       skb_checksum_start_offset(skb));
			अन्यथा
				skb_set_transport_header(skb,
							 skb_checksum_start_offset(skb));
			अगर (skb_csum_hwoffload_help(skb, features))
				जाओ out_kमुक्त_skb;
		पूर्ण
	पूर्ण

	skb = validate_xmit_xfrm(skb, features, again);

	वापस skb;

out_kमुक्त_skb:
	kमुक्त_skb(skb);
out_null:
	atomic_दीर्घ_inc(&dev->tx_dropped);
	वापस शून्य;
पूर्ण

काष्ठा sk_buff *validate_xmit_skb_list(काष्ठा sk_buff *skb, काष्ठा net_device *dev, bool *again)
अणु
	काष्ठा sk_buff *next, *head = शून्य, *tail;

	क्रम (; skb != शून्य; skb = next) अणु
		next = skb->next;
		skb_mark_not_on_list(skb);

		/* in हाल skb wont be segmented, poपूर्णांक to itself */
		skb->prev = skb;

		skb = validate_xmit_skb(skb, dev, again);
		अगर (!skb)
			जारी;

		अगर (!head)
			head = skb;
		अन्यथा
			tail->next = skb;
		/* If skb was segmented, skb->prev poपूर्णांकs to
		 * the last segment. If not, it still contains skb.
		 */
		tail = skb->prev;
	पूर्ण
	वापस head;
पूर्ण
EXPORT_SYMBOL_GPL(validate_xmit_skb_list);

अटल व्योम qdisc_pkt_len_init(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

	qdisc_skb_cb(skb)->pkt_len = skb->len;

	/* To get more precise estimation of bytes sent on wire,
	 * we add to pkt_len the headers size of all segments
	 */
	अगर (shinfo->gso_size && skb_transport_header_was_set(skb)) अणु
		अचिन्हित पूर्णांक hdr_len;
		u16 gso_segs = shinfo->gso_segs;

		/* mac layer + network layer */
		hdr_len = skb_transport_header(skb) - skb_mac_header(skb);

		/* + transport layer */
		अगर (likely(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6))) अणु
			स्थिर काष्ठा tcphdr *th;
			काष्ठा tcphdr _tcphdr;

			th = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
						माप(_tcphdr), &_tcphdr);
			अगर (likely(th))
				hdr_len += __tcp_hdrlen(th);
		पूर्ण अन्यथा अणु
			काष्ठा udphdr _udphdr;

			अगर (skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
					       माप(_udphdr), &_udphdr))
				hdr_len += माप(काष्ठा udphdr);
		पूर्ण

		अगर (shinfo->gso_type & SKB_GSO_DODGY)
			gso_segs = DIV_ROUND_UP(skb->len - hdr_len,
						shinfo->gso_size);

		qdisc_skb_cb(skb)->pkt_len += (gso_segs - 1) * hdr_len;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक __dev_xmit_skb(काष्ठा sk_buff *skb, काष्ठा Qdisc *q,
				 काष्ठा net_device *dev,
				 काष्ठा netdev_queue *txq)
अणु
	spinlock_t *root_lock = qdisc_lock(q);
	काष्ठा sk_buff *to_मुक्त = शून्य;
	bool contended;
	पूर्णांक rc;

	qdisc_calculate_pkt_len(skb, q);

	अगर (q->flags & TCQ_F_NOLOCK) अणु
		rc = q->enqueue(skb, q, &to_मुक्त) & NET_XMIT_MASK;
		अगर (likely(!netअगर_xmit_frozen_or_stopped(txq)))
			qdisc_run(q);

		अगर (unlikely(to_मुक्त))
			kमुक्त_skb_list(to_मुक्त);
		वापस rc;
	पूर्ण

	/*
	 * Heuristic to क्रमce contended enqueues to serialize on a
	 * separate lock beक्रमe trying to get qdisc मुख्य lock.
	 * This permits qdisc->running owner to get the lock more
	 * often and dequeue packets faster.
	 */
	contended = qdisc_is_running(q);
	अगर (unlikely(contended))
		spin_lock(&q->busylock);

	spin_lock(root_lock);
	अगर (unlikely(test_bit(__QDISC_STATE_DEACTIVATED, &q->state))) अणु
		__qdisc_drop(skb, &to_मुक्त);
		rc = NET_XMIT_DROP;
	पूर्ण अन्यथा अगर ((q->flags & TCQ_F_CAN_BYPASS) && !qdisc_qlen(q) &&
		   qdisc_run_begin(q)) अणु
		/*
		 * This is a work-conserving queue; there are no old skbs
		 * रुकोing to be sent out; and the qdisc is not running -
		 * xmit the skb directly.
		 */

		qdisc_bstats_update(q, skb);

		अगर (sch_direct_xmit(skb, q, dev, txq, root_lock, true)) अणु
			अगर (unlikely(contended)) अणु
				spin_unlock(&q->busylock);
				contended = false;
			पूर्ण
			__qdisc_run(q);
		पूर्ण

		qdisc_run_end(q);
		rc = NET_XMIT_SUCCESS;
	पूर्ण अन्यथा अणु
		rc = q->enqueue(skb, q, &to_मुक्त) & NET_XMIT_MASK;
		अगर (qdisc_run_begin(q)) अणु
			अगर (unlikely(contended)) अणु
				spin_unlock(&q->busylock);
				contended = false;
			पूर्ण
			__qdisc_run(q);
			qdisc_run_end(q);
		पूर्ण
	पूर्ण
	spin_unlock(root_lock);
	अगर (unlikely(to_मुक्त))
		kमुक्त_skb_list(to_मुक्त);
	अगर (unlikely(contended))
		spin_unlock(&q->busylock);
	वापस rc;
पूर्ण

#अगर IS_ENABLED(CONFIG_CGROUP_NET_PRIO)
अटल व्योम skb_update_prio(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा netprio_map *map;
	स्थिर काष्ठा sock *sk;
	अचिन्हित पूर्णांक prioidx;

	अगर (skb->priority)
		वापस;
	map = rcu_dereference_bh(skb->dev->priomap);
	अगर (!map)
		वापस;
	sk = skb_to_full_sk(skb);
	अगर (!sk)
		वापस;

	prioidx = sock_cgroup_prioidx(&sk->sk_cgrp_data);

	अगर (prioidx < map->priomap_len)
		skb->priority = map->priomap[prioidx];
पूर्ण
#अन्यथा
#घोषणा skb_update_prio(skb)
#पूर्ण_अगर

/**
 *	dev_loopback_xmit - loop back @skb
 *	@net: network namespace this loopback is happening in
 *	@sk:  sk needed to be a netfilter okfn
 *	@skb: buffer to transmit
 */
पूर्णांक dev_loopback_xmit(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb_reset_mac_header(skb);
	__skb_pull(skb, skb_network_offset(skb));
	skb->pkt_type = PACKET_LOOPBACK;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	WARN_ON(!skb_dst(skb));
	skb_dst_क्रमce(skb);
	netअगर_rx_ni(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dev_loopback_xmit);

#अगर_घोषित CONFIG_NET_EGRESS
अटल काष्ठा sk_buff *
sch_handle_egress(काष्ठा sk_buff *skb, पूर्णांक *ret, काष्ठा net_device *dev)
अणु
	काष्ठा mini_Qdisc *miniq = rcu_dereference_bh(dev->miniq_egress);
	काष्ठा tcf_result cl_res;

	अगर (!miniq)
		वापस skb;

	/* qdisc_skb_cb(skb)->pkt_len was alपढ़ोy set by the caller. */
	qdisc_skb_cb(skb)->mru = 0;
	qdisc_skb_cb(skb)->post_ct = false;
	mini_qdisc_bstats_cpu_update(miniq, skb);

	चयन (tcf_classअगरy(skb, miniq->filter_list, &cl_res, false)) अणु
	हाल TC_ACT_OK:
	हाल TC_ACT_RECLASSIFY:
		skb->tc_index = TC_H_MIN(cl_res.classid);
		अवरोध;
	हाल TC_ACT_SHOT:
		mini_qdisc_qstats_cpu_drop(miniq);
		*ret = NET_XMIT_DROP;
		kमुक्त_skb(skb);
		वापस शून्य;
	हाल TC_ACT_STOLEN:
	हाल TC_ACT_QUEUED:
	हाल TC_ACT_TRAP:
		*ret = NET_XMIT_SUCCESS;
		consume_skb(skb);
		वापस शून्य;
	हाल TC_ACT_REसूचीECT:
		/* No need to push/pop skb's mac_header here on egress! */
		skb_करो_redirect(skb);
		*ret = NET_XMIT_SUCCESS;
		वापस शून्य;
	शेष:
		अवरोध;
	पूर्ण

	वापस skb;
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_EGRESS */

#अगर_घोषित CONFIG_XPS
अटल पूर्णांक __get_xps_queue_idx(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			       काष्ठा xps_dev_maps *dev_maps, अचिन्हित पूर्णांक tci)
अणु
	पूर्णांक tc = netdev_get_prio_tc_map(dev, skb->priority);
	काष्ठा xps_map *map;
	पूर्णांक queue_index = -1;

	अगर (tc >= dev_maps->num_tc || tci >= dev_maps->nr_ids)
		वापस queue_index;

	tci *= dev_maps->num_tc;
	tci += tc;

	map = rcu_dereference(dev_maps->attr_map[tci]);
	अगर (map) अणु
		अगर (map->len == 1)
			queue_index = map->queues[0];
		अन्यथा
			queue_index = map->queues[reciprocal_scale(
						skb_get_hash(skb), map->len)];
		अगर (unlikely(queue_index >= dev->real_num_tx_queues))
			queue_index = -1;
	पूर्ण
	वापस queue_index;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक get_xps_queue(काष्ठा net_device *dev, काष्ठा net_device *sb_dev,
			 काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_XPS
	काष्ठा xps_dev_maps *dev_maps;
	काष्ठा sock *sk = skb->sk;
	पूर्णांक queue_index = -1;

	अगर (!अटल_key_false(&xps_needed))
		वापस -1;

	rcu_पढ़ो_lock();
	अगर (!अटल_key_false(&xps_rxqs_needed))
		जाओ get_cpus_map;

	dev_maps = rcu_dereference(sb_dev->xps_maps[XPS_RXQS]);
	अगर (dev_maps) अणु
		पूर्णांक tci = sk_rx_queue_get(sk);

		अगर (tci >= 0)
			queue_index = __get_xps_queue_idx(dev, skb, dev_maps,
							  tci);
	पूर्ण

get_cpus_map:
	अगर (queue_index < 0) अणु
		dev_maps = rcu_dereference(sb_dev->xps_maps[XPS_CPUS]);
		अगर (dev_maps) अणु
			अचिन्हित पूर्णांक tci = skb->sender_cpu - 1;

			queue_index = __get_xps_queue_idx(dev, skb, dev_maps,
							  tci);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस queue_index;
#अन्यथा
	वापस -1;
#पूर्ण_अगर
पूर्ण

u16 dev_pick_tx_zero(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		     काष्ठा net_device *sb_dev)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dev_pick_tx_zero);

u16 dev_pick_tx_cpu_id(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		       काष्ठा net_device *sb_dev)
अणु
	वापस (u16)raw_smp_processor_id() % dev->real_num_tx_queues;
पूर्ण
EXPORT_SYMBOL(dev_pick_tx_cpu_id);

u16 netdev_pick_tx(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		     काष्ठा net_device *sb_dev)
अणु
	काष्ठा sock *sk = skb->sk;
	पूर्णांक queue_index = sk_tx_queue_get(sk);

	sb_dev = sb_dev ? : dev;

	अगर (queue_index < 0 || skb->ooo_okay ||
	    queue_index >= dev->real_num_tx_queues) अणु
		पूर्णांक new_index = get_xps_queue(dev, sb_dev, skb);

		अगर (new_index < 0)
			new_index = skb_tx_hash(dev, sb_dev, skb);

		अगर (queue_index != new_index && sk &&
		    sk_fullsock(sk) &&
		    rcu_access_poपूर्णांकer(sk->sk_dst_cache))
			sk_tx_queue_set(sk, new_index);

		queue_index = new_index;
	पूर्ण

	वापस queue_index;
पूर्ण
EXPORT_SYMBOL(netdev_pick_tx);

काष्ठा netdev_queue *netdev_core_pick_tx(काष्ठा net_device *dev,
					 काष्ठा sk_buff *skb,
					 काष्ठा net_device *sb_dev)
अणु
	पूर्णांक queue_index = 0;

#अगर_घोषित CONFIG_XPS
	u32 sender_cpu = skb->sender_cpu - 1;

	अगर (sender_cpu >= (u32)NR_CPUS)
		skb->sender_cpu = raw_smp_processor_id() + 1;
#पूर्ण_अगर

	अगर (dev->real_num_tx_queues != 1) अणु
		स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

		अगर (ops->nकरो_select_queue)
			queue_index = ops->nकरो_select_queue(dev, skb, sb_dev);
		अन्यथा
			queue_index = netdev_pick_tx(dev, skb, sb_dev);

		queue_index = netdev_cap_txqueue(dev, queue_index);
	पूर्ण

	skb_set_queue_mapping(skb, queue_index);
	वापस netdev_get_tx_queue(dev, queue_index);
पूर्ण

/**
 *	__dev_queue_xmit - transmit a buffer
 *	@skb: buffer to transmit
 *	@sb_dev: suboordinate device used क्रम L2 क्रमwarding offload
 *
 *	Queue a buffer क्रम transmission to a network device. The caller must
 *	have set the device and priority and built the buffer beक्रमe calling
 *	this function. The function can be called from an पूर्णांकerrupt.
 *
 *	A negative त्रुटि_सं code is वापसed on a failure. A success करोes not
 *	guarantee the frame will be transmitted as it may be dropped due
 *	to congestion or traffic shaping.
 *
 * -----------------------------------------------------------------------------------
 *      I notice this method can also वापस errors from the queue disciplines,
 *      including NET_XMIT_DROP, which is a positive value.  So, errors can also
 *      be positive.
 *
 *      Regardless of the वापस value, the skb is consumed, so it is currently
 *      dअगरficult to retry a send to this method.  (You can bump the ref count
 *      beक्रमe sending to hold a reference क्रम retry अगर you are careful.)
 *
 *      When calling this method, पूर्णांकerrupts MUST be enabled.  This is because
 *      the BH enable code must have IRQs enabled so that it will not deadlock.
 *          --BLG
 */
अटल पूर्णांक __dev_queue_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *sb_dev)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा netdev_queue *txq;
	काष्ठा Qdisc *q;
	पूर्णांक rc = -ENOMEM;
	bool again = false;

	skb_reset_mac_header(skb);

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_SCHED_TSTAMP))
		__skb_tstamp_tx(skb, शून्य, शून्य, skb->sk, SCM_TSTAMP_SCHED);

	/* Disable soft irqs क्रम various locks below. Also
	 * stops preemption क्रम RCU.
	 */
	rcu_पढ़ो_lock_bh();

	skb_update_prio(skb);

	qdisc_pkt_len_init(skb);
#अगर_घोषित CONFIG_NET_CLS_ACT
	skb->tc_at_ingress = 0;
# अगरdef CONFIG_NET_EGRESS
	अगर (अटल_branch_unlikely(&egress_needed_key)) अणु
		skb = sch_handle_egress(skb, &rc, dev);
		अगर (!skb)
			जाओ out;
	पूर्ण
# endअगर
#पूर्ण_अगर
	/* If device/qdisc करोn't need skb->dst, release it right now जबतक
	 * its hot in this cpu cache.
	 */
	अगर (dev->priv_flags & IFF_XMIT_DST_RELEASE)
		skb_dst_drop(skb);
	अन्यथा
		skb_dst_क्रमce(skb);

	txq = netdev_core_pick_tx(dev, skb, sb_dev);
	q = rcu_dereference_bh(txq->qdisc);

	trace_net_dev_queue(skb);
	अगर (q->enqueue) अणु
		rc = __dev_xmit_skb(skb, q, dev, txq);
		जाओ out;
	पूर्ण

	/* The device has no queue. Common हाल क्रम software devices:
	 * loopback, all the sorts of tunnels...

	 * Really, it is unlikely that netअगर_tx_lock protection is necessary
	 * here.  (f.e. loopback and IP tunnels are clean ignoring statistics
	 * counters.)
	 * However, it is possible, that they rely on protection
	 * made by us here.

	 * Check this and shot the lock. It is not prone from deadlocks.
	 *Either shot noqueue qdisc, it is even simpler 8)
	 */
	अगर (dev->flags & IFF_UP) अणु
		पूर्णांक cpu = smp_processor_id(); /* ok because BHs are off */

		अगर (txq->xmit_lock_owner != cpu) अणु
			अगर (dev_xmit_recursion())
				जाओ recursion_alert;

			skb = validate_xmit_skb(skb, dev, &again);
			अगर (!skb)
				जाओ out;

			PRANDOM_ADD_NOISE(skb, dev, txq, jअगरfies);
			HARD_TX_LOCK(dev, txq, cpu);

			अगर (!netअगर_xmit_stopped(txq)) अणु
				dev_xmit_recursion_inc();
				skb = dev_hard_start_xmit(skb, dev, txq, &rc);
				dev_xmit_recursion_dec();
				अगर (dev_xmit_complete(rc)) अणु
					HARD_TX_UNLOCK(dev, txq);
					जाओ out;
				पूर्ण
			पूर्ण
			HARD_TX_UNLOCK(dev, txq);
			net_crit_ratelimited("Virtual device %s asks to queue packet!\n",
					     dev->name);
		पूर्ण अन्यथा अणु
			/* Recursion is detected! It is possible,
			 * unक्रमtunately
			 */
recursion_alert:
			net_crit_ratelimited("Dead loop on virtual device %s, fix it urgently!\n",
					     dev->name);
		पूर्ण
	पूर्ण

	rc = -ENETDOWN;
	rcu_पढ़ो_unlock_bh();

	atomic_दीर्घ_inc(&dev->tx_dropped);
	kमुक्त_skb_list(skb);
	वापस rc;
out:
	rcu_पढ़ो_unlock_bh();
	वापस rc;
पूर्ण

पूर्णांक dev_queue_xmit(काष्ठा sk_buff *skb)
अणु
	वापस __dev_queue_xmit(skb, शून्य);
पूर्ण
EXPORT_SYMBOL(dev_queue_xmit);

पूर्णांक dev_queue_xmit_accel(काष्ठा sk_buff *skb, काष्ठा net_device *sb_dev)
अणु
	वापस __dev_queue_xmit(skb, sb_dev);
पूर्ण
EXPORT_SYMBOL(dev_queue_xmit_accel);

पूर्णांक __dev_direct_xmit(काष्ठा sk_buff *skb, u16 queue_id)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा sk_buff *orig_skb = skb;
	काष्ठा netdev_queue *txq;
	पूर्णांक ret = NETDEV_TX_BUSY;
	bool again = false;

	अगर (unlikely(!netअगर_running(dev) ||
		     !netअगर_carrier_ok(dev)))
		जाओ drop;

	skb = validate_xmit_skb_list(skb, dev, &again);
	अगर (skb != orig_skb)
		जाओ drop;

	skb_set_queue_mapping(skb, queue_id);
	txq = skb_get_tx_queue(dev, skb);
	PRANDOM_ADD_NOISE(skb, dev, txq, jअगरfies);

	local_bh_disable();

	dev_xmit_recursion_inc();
	HARD_TX_LOCK(dev, txq, smp_processor_id());
	अगर (!netअगर_xmit_frozen_or_drv_stopped(txq))
		ret = netdev_start_xmit(skb, dev, txq, false);
	HARD_TX_UNLOCK(dev, txq);
	dev_xmit_recursion_dec();

	local_bh_enable();
	वापस ret;
drop:
	atomic_दीर्घ_inc(&dev->tx_dropped);
	kमुक्त_skb_list(skb);
	वापस NET_XMIT_DROP;
पूर्ण
EXPORT_SYMBOL(__dev_direct_xmit);

/*************************************************************************
 *			Receiver routines
 *************************************************************************/

पूर्णांक netdev_max_backlog __पढ़ो_mostly = 1000;
EXPORT_SYMBOL(netdev_max_backlog);

पूर्णांक netdev_tstamp_prequeue __पढ़ो_mostly = 1;
पूर्णांक netdev_budget __पढ़ो_mostly = 300;
/* Must be at least 2 jअगरfes to guarantee 1 jअगरfy समयout */
अचिन्हित पूर्णांक __पढ़ो_mostly netdev_budget_usecs = 2 * USEC_PER_SEC / HZ;
पूर्णांक weight_p __पढ़ो_mostly = 64;           /* old backlog weight */
पूर्णांक dev_weight_rx_bias __पढ़ो_mostly = 1;  /* bias क्रम backlog weight */
पूर्णांक dev_weight_tx_bias __पढ़ो_mostly = 1;  /* bias क्रम output_queue quota */
पूर्णांक dev_rx_weight __पढ़ो_mostly = 64;
पूर्णांक dev_tx_weight __पढ़ो_mostly = 64;
/* Maximum number of GRO_NORMAL skbs to batch up क्रम list-RX */
पूर्णांक gro_normal_batch __पढ़ो_mostly = 8;

/* Called with irq disabled */
अटल अंतरभूत व्योम ____napi_schedule(काष्ठा softnet_data *sd,
				     काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;

	अगर (test_bit(NAPI_STATE_THREADED, &napi->state)) अणु
		/* Paired with smp_mb__beक्रमe_atomic() in
		 * napi_enable()/dev_set_thपढ़ोed().
		 * Use READ_ONCE() to guarantee a complete
		 * पढ़ो on napi->thपढ़ो. Only call
		 * wake_up_process() when it's not शून्य.
		 */
		thपढ़ो = READ_ONCE(napi->thपढ़ो);
		अगर (thपढ़ो) अणु
			/* Aव्योम करोing set_bit() अगर the thपढ़ो is in
			 * INTERRUPTIBLE state, cause napi_thपढ़ो_रुको()
			 * makes sure to proceed with napi polling
			 * अगर the thपढ़ो is explicitly woken from here.
			 */
			अगर (READ_ONCE(thपढ़ो->state) != TASK_INTERRUPTIBLE)
				set_bit(NAPI_STATE_SCHED_THREADED, &napi->state);
			wake_up_process(thपढ़ो);
			वापस;
		पूर्ण
	पूर्ण

	list_add_tail(&napi->poll_list, &sd->poll_list);
	__उठाओ_softirq_irqoff(NET_RX_SOFTIRQ);
पूर्ण

#अगर_घोषित CONFIG_RPS

/* One global table that all flow-based protocols share. */
काष्ठा rps_sock_flow_table __rcu *rps_sock_flow_table __पढ़ो_mostly;
EXPORT_SYMBOL(rps_sock_flow_table);
u32 rps_cpu_mask __पढ़ो_mostly;
EXPORT_SYMBOL(rps_cpu_mask);

काष्ठा अटल_key_false rps_needed __पढ़ो_mostly;
EXPORT_SYMBOL(rps_needed);
काष्ठा अटल_key_false rfs_needed __पढ़ो_mostly;
EXPORT_SYMBOL(rfs_needed);

अटल काष्ठा rps_dev_flow *
set_rps_cpu(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
	    काष्ठा rps_dev_flow *rflow, u16 next_cpu)
अणु
	अगर (next_cpu < nr_cpu_ids) अणु
#अगर_घोषित CONFIG_RFS_ACCEL
		काष्ठा netdev_rx_queue *rxqueue;
		काष्ठा rps_dev_flow_table *flow_table;
		काष्ठा rps_dev_flow *old_rflow;
		u32 flow_id;
		u16 rxq_index;
		पूर्णांक rc;

		/* Should we steer this flow to a dअगरferent hardware queue? */
		अगर (!skb_rx_queue_recorded(skb) || !dev->rx_cpu_rmap ||
		    !(dev->features & NETIF_F_NTUPLE))
			जाओ out;
		rxq_index = cpu_rmap_lookup_index(dev->rx_cpu_rmap, next_cpu);
		अगर (rxq_index == skb_get_rx_queue(skb))
			जाओ out;

		rxqueue = dev->_rx + rxq_index;
		flow_table = rcu_dereference(rxqueue->rps_flow_table);
		अगर (!flow_table)
			जाओ out;
		flow_id = skb_get_hash(skb) & flow_table->mask;
		rc = dev->netdev_ops->nकरो_rx_flow_steer(dev, skb,
							rxq_index, flow_id);
		अगर (rc < 0)
			जाओ out;
		old_rflow = rflow;
		rflow = &flow_table->flows[flow_id];
		rflow->filter = rc;
		अगर (old_rflow->filter == rflow->filter)
			old_rflow->filter = RPS_NO_FILTER;
	out:
#पूर्ण_अगर
		rflow->last_qtail =
			per_cpu(softnet_data, next_cpu).input_queue_head;
	पूर्ण

	rflow->cpu = next_cpu;
	वापस rflow;
पूर्ण

/*
 * get_rps_cpu is called from netअगर_receive_skb and वापसs the target
 * CPU from the RPS map of the receiving queue क्रम a given skb.
 * rcu_पढ़ो_lock must be held on entry.
 */
अटल पूर्णांक get_rps_cpu(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		       काष्ठा rps_dev_flow **rflowp)
अणु
	स्थिर काष्ठा rps_sock_flow_table *sock_flow_table;
	काष्ठा netdev_rx_queue *rxqueue = dev->_rx;
	काष्ठा rps_dev_flow_table *flow_table;
	काष्ठा rps_map *map;
	पूर्णांक cpu = -1;
	u32 tcpu;
	u32 hash;

	अगर (skb_rx_queue_recorded(skb)) अणु
		u16 index = skb_get_rx_queue(skb);

		अगर (unlikely(index >= dev->real_num_rx_queues)) अणु
			WARN_ONCE(dev->real_num_rx_queues > 1,
				  "%s received packet on queue %u, but number "
				  "of RX queues is %u\n",
				  dev->name, index, dev->real_num_rx_queues);
			जाओ करोne;
		पूर्ण
		rxqueue += index;
	पूर्ण

	/* Aव्योम computing hash अगर RFS/RPS is not active क्रम this rxqueue */

	flow_table = rcu_dereference(rxqueue->rps_flow_table);
	map = rcu_dereference(rxqueue->rps_map);
	अगर (!flow_table && !map)
		जाओ करोne;

	skb_reset_network_header(skb);
	hash = skb_get_hash(skb);
	अगर (!hash)
		जाओ करोne;

	sock_flow_table = rcu_dereference(rps_sock_flow_table);
	अगर (flow_table && sock_flow_table) अणु
		काष्ठा rps_dev_flow *rflow;
		u32 next_cpu;
		u32 ident;

		/* First check पूर्णांकo global flow table अगर there is a match */
		ident = sock_flow_table->ents[hash & sock_flow_table->mask];
		अगर ((ident ^ hash) & ~rps_cpu_mask)
			जाओ try_rps;

		next_cpu = ident & rps_cpu_mask;

		/* OK, now we know there is a match,
		 * we can look at the local (per receive queue) flow table
		 */
		rflow = &flow_table->flows[hash & flow_table->mask];
		tcpu = rflow->cpu;

		/*
		 * If the desired CPU (where last recvmsg was करोne) is
		 * dअगरferent from current CPU (one in the rx-queue flow
		 * table entry), चयन अगर one of the following holds:
		 *   - Current CPU is unset (>= nr_cpu_ids).
		 *   - Current CPU is offline.
		 *   - The current CPU's queue tail has advanced beyond the
		 *     last packet that was enqueued using this table entry.
		 *     This guarantees that all previous packets क्रम the flow
		 *     have been dequeued, thus preserving in order delivery.
		 */
		अगर (unlikely(tcpu != next_cpu) &&
		    (tcpu >= nr_cpu_ids || !cpu_online(tcpu) ||
		     ((पूर्णांक)(per_cpu(softnet_data, tcpu).input_queue_head -
		      rflow->last_qtail)) >= 0)) अणु
			tcpu = next_cpu;
			rflow = set_rps_cpu(dev, skb, rflow, next_cpu);
		पूर्ण

		अगर (tcpu < nr_cpu_ids && cpu_online(tcpu)) अणु
			*rflowp = rflow;
			cpu = tcpu;
			जाओ करोne;
		पूर्ण
	पूर्ण

try_rps:

	अगर (map) अणु
		tcpu = map->cpus[reciprocal_scale(hash, map->len)];
		अगर (cpu_online(tcpu)) अणु
			cpu = tcpu;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	वापस cpu;
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL

/**
 * rps_may_expire_flow - check whether an RFS hardware filter may be हटाओd
 * @dev: Device on which the filter was set
 * @rxq_index: RX queue index
 * @flow_id: Flow ID passed to nकरो_rx_flow_steer()
 * @filter_id: Filter ID वापसed by nकरो_rx_flow_steer()
 *
 * Drivers that implement nकरो_rx_flow_steer() should periodically call
 * this function क्रम each installed filter and हटाओ the filters क्रम
 * which it वापसs %true.
 */
bool rps_may_expire_flow(काष्ठा net_device *dev, u16 rxq_index,
			 u32 flow_id, u16 filter_id)
अणु
	काष्ठा netdev_rx_queue *rxqueue = dev->_rx + rxq_index;
	काष्ठा rps_dev_flow_table *flow_table;
	काष्ठा rps_dev_flow *rflow;
	bool expire = true;
	अचिन्हित पूर्णांक cpu;

	rcu_पढ़ो_lock();
	flow_table = rcu_dereference(rxqueue->rps_flow_table);
	अगर (flow_table && flow_id <= flow_table->mask) अणु
		rflow = &flow_table->flows[flow_id];
		cpu = READ_ONCE(rflow->cpu);
		अगर (rflow->filter == filter_id && cpu < nr_cpu_ids &&
		    ((पूर्णांक)(per_cpu(softnet_data, cpu).input_queue_head -
			   rflow->last_qtail) <
		     (पूर्णांक)(10 * flow_table->mask)))
			expire = false;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस expire;
पूर्ण
EXPORT_SYMBOL(rps_may_expire_flow);

#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

/* Called from hardirq (IPI) context */
अटल व्योम rps_trigger_softirq(व्योम *data)
अणु
	काष्ठा softnet_data *sd = data;

	____napi_schedule(sd, &sd->backlog);
	sd->received_rps++;
पूर्ण

#पूर्ण_अगर /* CONFIG_RPS */

/*
 * Check अगर this softnet_data काष्ठाure is another cpu one
 * If yes, queue it to our IPI list and वापस 1
 * If no, वापस 0
 */
अटल पूर्णांक rps_ipi_queued(काष्ठा softnet_data *sd)
अणु
#अगर_घोषित CONFIG_RPS
	काष्ठा softnet_data *mysd = this_cpu_ptr(&softnet_data);

	अगर (sd != mysd) अणु
		sd->rps_ipi_next = mysd->rps_ipi_list;
		mysd->rps_ipi_list = sd;

		__उठाओ_softirq_irqoff(NET_RX_SOFTIRQ);
		वापस 1;
	पूर्ण
#पूर्ण_अगर /* CONFIG_RPS */
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_FLOW_LIMIT
पूर्णांक netdev_flow_limit_table_len __पढ़ो_mostly = (1 << 12);
#पूर्ण_अगर

अटल bool skb_flow_limit(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक qlen)
अणु
#अगर_घोषित CONFIG_NET_FLOW_LIMIT
	काष्ठा sd_flow_limit *fl;
	काष्ठा softnet_data *sd;
	अचिन्हित पूर्णांक old_flow, new_flow;

	अगर (qlen < (netdev_max_backlog >> 1))
		वापस false;

	sd = this_cpu_ptr(&softnet_data);

	rcu_पढ़ो_lock();
	fl = rcu_dereference(sd->flow_limit);
	अगर (fl) अणु
		new_flow = skb_get_hash(skb) & (fl->num_buckets - 1);
		old_flow = fl->history[fl->history_head];
		fl->history[fl->history_head] = new_flow;

		fl->history_head++;
		fl->history_head &= FLOW_LIMIT_HISTORY - 1;

		अगर (likely(fl->buckets[old_flow]))
			fl->buckets[old_flow]--;

		अगर (++fl->buckets[new_flow] > (FLOW_LIMIT_HISTORY >> 1)) अणु
			fl->count++;
			rcu_पढ़ो_unlock();
			वापस true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
#पूर्ण_अगर
	वापस false;
पूर्ण

/*
 * enqueue_to_backlog is called to queue an skb to a per CPU backlog
 * queue (may be a remote CPU queue).
 */
अटल पूर्णांक enqueue_to_backlog(काष्ठा sk_buff *skb, पूर्णांक cpu,
			      अचिन्हित पूर्णांक *qtail)
अणु
	काष्ठा softnet_data *sd;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक qlen;

	sd = &per_cpu(softnet_data, cpu);

	local_irq_save(flags);

	rps_lock(sd);
	अगर (!netअगर_running(skb->dev))
		जाओ drop;
	qlen = skb_queue_len(&sd->input_pkt_queue);
	अगर (qlen <= netdev_max_backlog && !skb_flow_limit(skb, qlen)) अणु
		अगर (qlen) अणु
enqueue:
			__skb_queue_tail(&sd->input_pkt_queue, skb);
			input_queue_tail_incr_save(sd, qtail);
			rps_unlock(sd);
			local_irq_restore(flags);
			वापस NET_RX_SUCCESS;
		पूर्ण

		/* Schedule NAPI क्रम backlog device
		 * We can use non atomic operation since we own the queue lock
		 */
		अगर (!__test_and_set_bit(NAPI_STATE_SCHED, &sd->backlog.state)) अणु
			अगर (!rps_ipi_queued(sd))
				____napi_schedule(sd, &sd->backlog);
		पूर्ण
		जाओ enqueue;
	पूर्ण

drop:
	sd->dropped++;
	rps_unlock(sd);

	local_irq_restore(flags);

	atomic_दीर्घ_inc(&skb->dev->rx_dropped);
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल काष्ठा netdev_rx_queue *netअगर_get_rxqueue(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा netdev_rx_queue *rxqueue;

	rxqueue = dev->_rx;

	अगर (skb_rx_queue_recorded(skb)) अणु
		u16 index = skb_get_rx_queue(skb);

		अगर (unlikely(index >= dev->real_num_rx_queues)) अणु
			WARN_ONCE(dev->real_num_rx_queues > 1,
				  "%s received packet on queue %u, but number "
				  "of RX queues is %u\n",
				  dev->name, index, dev->real_num_rx_queues);

			वापस rxqueue; /* Return first rxqueue */
		पूर्ण
		rxqueue += index;
	पूर्ण
	वापस rxqueue;
पूर्ण

अटल u32 netअगर_receive_generic_xdp(काष्ठा sk_buff *skb,
				     काष्ठा xdp_buff *xdp,
				     काष्ठा bpf_prog *xdp_prog)
अणु
	व्योम *orig_data, *orig_data_end, *hard_start;
	काष्ठा netdev_rx_queue *rxqueue;
	u32 metalen, act = XDP_DROP;
	bool orig_bcast, orig_host;
	u32 mac_len, frame_sz;
	__be16 orig_eth_type;
	काष्ठा ethhdr *eth;
	पूर्णांक off;

	/* Reinjected packets coming from act_mirred or similar should
	 * not get XDP generic processing.
	 */
	अगर (skb_is_redirected(skb))
		वापस XDP_PASS;

	/* XDP packets must be linear and must have sufficient headroom
	 * of XDP_PACKET_HEADROOM bytes. This is the guarantee that also
	 * native XDP provides, thus we need to करो it here as well.
	 */
	अगर (skb_cloned(skb) || skb_is_nonlinear(skb) ||
	    skb_headroom(skb) < XDP_PACKET_HEADROOM) अणु
		पूर्णांक hroom = XDP_PACKET_HEADROOM - skb_headroom(skb);
		पूर्णांक troom = skb->tail + skb->data_len - skb->end;

		/* In हाल we have to go करोwn the path and also linearize,
		 * then lets करो the pskb_expand_head() work just once here.
		 */
		अगर (pskb_expand_head(skb,
				     hroom > 0 ? ALIGN(hroom, NET_SKB_PAD) : 0,
				     troom > 0 ? troom + 128 : 0, GFP_ATOMIC))
			जाओ करो_drop;
		अगर (skb_linearize(skb))
			जाओ करो_drop;
	पूर्ण

	/* The XDP program wants to see the packet starting at the MAC
	 * header.
	 */
	mac_len = skb->data - skb_mac_header(skb);
	hard_start = skb->data - skb_headroom(skb);

	/* SKB "head" area always have tailroom क्रम skb_shared_info */
	frame_sz = (व्योम *)skb_end_poपूर्णांकer(skb) - hard_start;
	frame_sz += SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	rxqueue = netअगर_get_rxqueue(skb);
	xdp_init_buff(xdp, frame_sz, &rxqueue->xdp_rxq);
	xdp_prepare_buff(xdp, hard_start, skb_headroom(skb) - mac_len,
			 skb_headlen(skb) + mac_len, true);

	orig_data_end = xdp->data_end;
	orig_data = xdp->data;
	eth = (काष्ठा ethhdr *)xdp->data;
	orig_host = ether_addr_equal_64bits(eth->h_dest, skb->dev->dev_addr);
	orig_bcast = is_multicast_ether_addr_64bits(eth->h_dest);
	orig_eth_type = eth->h_proto;

	act = bpf_prog_run_xdp(xdp_prog, xdp);

	/* check अगर bpf_xdp_adjust_head was used */
	off = xdp->data - orig_data;
	अगर (off) अणु
		अगर (off > 0)
			__skb_pull(skb, off);
		अन्यथा अगर (off < 0)
			__skb_push(skb, -off);

		skb->mac_header += off;
		skb_reset_network_header(skb);
	पूर्ण

	/* check अगर bpf_xdp_adjust_tail was used */
	off = xdp->data_end - orig_data_end;
	अगर (off != 0) अणु
		skb_set_tail_poपूर्णांकer(skb, xdp->data_end - xdp->data);
		skb->len += off; /* positive on grow, negative on shrink */
	पूर्ण

	/* check अगर XDP changed eth hdr such SKB needs update */
	eth = (काष्ठा ethhdr *)xdp->data;
	अगर ((orig_eth_type != eth->h_proto) ||
	    (orig_host != ether_addr_equal_64bits(eth->h_dest,
						  skb->dev->dev_addr)) ||
	    (orig_bcast != is_multicast_ether_addr_64bits(eth->h_dest))) अणु
		__skb_push(skb, ETH_HLEN);
		skb->pkt_type = PACKET_HOST;
		skb->protocol = eth_type_trans(skb, skb->dev);
	पूर्ण

	चयन (act) अणु
	हाल XDP_REसूचीECT:
	हाल XDP_TX:
		__skb_push(skb, mac_len);
		अवरोध;
	हाल XDP_PASS:
		metalen = xdp->data - xdp->data_meta;
		अगर (metalen)
			skb_metadata_set(skb, metalen);
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(skb->dev, xdp_prog, act);
		fallthrough;
	हाल XDP_DROP:
	करो_drop:
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	वापस act;
पूर्ण

/* When करोing generic XDP we have to bypass the qdisc layer and the
 * network taps in order to match in-driver-XDP behavior.
 */
व्योम generic_xdp_tx(काष्ठा sk_buff *skb, काष्ठा bpf_prog *xdp_prog)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा netdev_queue *txq;
	bool मुक्त_skb = true;
	पूर्णांक cpu, rc;

	txq = netdev_core_pick_tx(dev, skb, शून्य);
	cpu = smp_processor_id();
	HARD_TX_LOCK(dev, txq, cpu);
	अगर (!netअगर_xmit_stopped(txq)) अणु
		rc = netdev_start_xmit(skb, dev, txq, 0);
		अगर (dev_xmit_complete(rc))
			मुक्त_skb = false;
	पूर्ण
	HARD_TX_UNLOCK(dev, txq);
	अगर (मुक्त_skb) अणु
		trace_xdp_exception(dev, xdp_prog, XDP_TX);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल DEFINE_STATIC_KEY_FALSE(generic_xdp_needed_key);

पूर्णांक करो_xdp_generic(काष्ठा bpf_prog *xdp_prog, काष्ठा sk_buff *skb)
अणु
	अगर (xdp_prog) अणु
		काष्ठा xdp_buff xdp;
		u32 act;
		पूर्णांक err;

		act = netअगर_receive_generic_xdp(skb, &xdp, xdp_prog);
		अगर (act != XDP_PASS) अणु
			चयन (act) अणु
			हाल XDP_REसूचीECT:
				err = xdp_करो_generic_redirect(skb->dev, skb,
							      &xdp, xdp_prog);
				अगर (err)
					जाओ out_redir;
				अवरोध;
			हाल XDP_TX:
				generic_xdp_tx(skb, xdp_prog);
				अवरोध;
			पूर्ण
			वापस XDP_DROP;
		पूर्ण
	पूर्ण
	वापस XDP_PASS;
out_redir:
	kमुक्त_skb(skb);
	वापस XDP_DROP;
पूर्ण
EXPORT_SYMBOL_GPL(करो_xdp_generic);

अटल पूर्णांक netअगर_rx_पूर्णांकernal(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	net_बारtamp_check(netdev_tstamp_prequeue, skb);

	trace_netअगर_rx(skb);

#अगर_घोषित CONFIG_RPS
	अगर (अटल_branch_unlikely(&rps_needed)) अणु
		काष्ठा rps_dev_flow व्योमflow, *rflow = &व्योमflow;
		पूर्णांक cpu;

		preempt_disable();
		rcu_पढ़ो_lock();

		cpu = get_rps_cpu(skb->dev, skb, &rflow);
		अगर (cpu < 0)
			cpu = smp_processor_id();

		ret = enqueue_to_backlog(skb, cpu, &rflow->last_qtail);

		rcu_पढ़ो_unlock();
		preempt_enable();
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अचिन्हित पूर्णांक qtail;

		ret = enqueue_to_backlog(skb, get_cpu(), &qtail);
		put_cpu();
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	netअगर_rx	-	post buffer to the network code
 *	@skb: buffer to post
 *
 *	This function receives a packet from a device driver and queues it क्रम
 *	the upper (protocol) levels to process.  It always succeeds. The buffer
 *	may be dropped during processing क्रम congestion control or by the
 *	protocol layers.
 *
 *	वापस values:
 *	NET_RX_SUCCESS	(no congestion)
 *	NET_RX_DROP     (packet was dropped)
 *
 */

पूर्णांक netअगर_rx(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	trace_netअगर_rx_entry(skb);

	ret = netअगर_rx_पूर्णांकernal(skb);
	trace_netअगर_rx_निकास(ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(netअगर_rx);

पूर्णांक netअगर_rx_ni(काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	trace_netअगर_rx_ni_entry(skb);

	preempt_disable();
	err = netअगर_rx_पूर्णांकernal(skb);
	अगर (local_softirq_pending())
		करो_softirq();
	preempt_enable();
	trace_netअगर_rx_ni_निकास(err);

	वापस err;
पूर्ण
EXPORT_SYMBOL(netअगर_rx_ni);

पूर्णांक netअगर_rx_any_context(काष्ठा sk_buff *skb)
अणु
	/*
	 * If invoked from contexts which करो not invoke bottom half
	 * processing either at वापस from पूर्णांकerrupt or when softrqs are
	 * reenabled, use netअगर_rx_ni() which invokes bottomhalf processing
	 * directly.
	 */
	अगर (in_पूर्णांकerrupt())
		वापस netअगर_rx(skb);
	अन्यथा
		वापस netअगर_rx_ni(skb);
पूर्ण
EXPORT_SYMBOL(netअगर_rx_any_context);

अटल __latent_entropy व्योम net_tx_action(काष्ठा softirq_action *h)
अणु
	काष्ठा softnet_data *sd = this_cpu_ptr(&softnet_data);

	अगर (sd->completion_queue) अणु
		काष्ठा sk_buff *clist;

		local_irq_disable();
		clist = sd->completion_queue;
		sd->completion_queue = शून्य;
		local_irq_enable();

		जबतक (clist) अणु
			काष्ठा sk_buff *skb = clist;

			clist = clist->next;

			WARN_ON(refcount_पढ़ो(&skb->users));
			अगर (likely(get_kमुक्त_skb_cb(skb)->reason == SKB_REASON_CONSUMED))
				trace_consume_skb(skb);
			अन्यथा
				trace_kमुक्त_skb(skb, net_tx_action);

			अगर (skb->fclone != SKB_FCLONE_UNAVAILABLE)
				__kमुक्त_skb(skb);
			अन्यथा
				__kमुक्त_skb_defer(skb);
		पूर्ण
	पूर्ण

	अगर (sd->output_queue) अणु
		काष्ठा Qdisc *head;

		local_irq_disable();
		head = sd->output_queue;
		sd->output_queue = शून्य;
		sd->output_queue_tailp = &sd->output_queue;
		local_irq_enable();

		rcu_पढ़ो_lock();

		जबतक (head) अणु
			काष्ठा Qdisc *q = head;
			spinlock_t *root_lock = शून्य;

			head = head->next_sched;

			/* We need to make sure head->next_sched is पढ़ो
			 * beक्रमe clearing __QDISC_STATE_SCHED
			 */
			smp_mb__beक्रमe_atomic();

			अगर (!(q->flags & TCQ_F_NOLOCK)) अणु
				root_lock = qdisc_lock(q);
				spin_lock(root_lock);
			पूर्ण अन्यथा अगर (unlikely(test_bit(__QDISC_STATE_DEACTIVATED,
						     &q->state))) अणु
				/* There is a synchronize_net() between
				 * STATE_DEACTIVATED flag being set and
				 * qdisc_reset()/some_qdisc_is_busy() in
				 * dev_deactivate(), so we can safely bail out
				 * early here to aव्योम data race between
				 * qdisc_deactivate() and some_qdisc_is_busy()
				 * क्रम lockless qdisc.
				 */
				clear_bit(__QDISC_STATE_SCHED, &q->state);
				जारी;
			पूर्ण

			clear_bit(__QDISC_STATE_SCHED, &q->state);
			qdisc_run(q);
			अगर (root_lock)
				spin_unlock(root_lock);
		पूर्ण

		rcu_पढ़ो_unlock();
	पूर्ण

	xfrm_dev_backlog(sd);
पूर्ण

#अगर IS_ENABLED(CONFIG_BRIDGE) && IS_ENABLED(CONFIG_ATM_LANE)
/* This hook is defined here क्रम ATM LANE */
पूर्णांक (*br_fdb_test_addr_hook)(काष्ठा net_device *dev,
			     अचिन्हित अक्षर *addr) __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(br_fdb_test_addr_hook);
#पूर्ण_अगर

अटल अंतरभूत काष्ठा sk_buff *
sch_handle_ingress(काष्ठा sk_buff *skb, काष्ठा packet_type **pt_prev, पूर्णांक *ret,
		   काष्ठा net_device *orig_dev, bool *another)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा mini_Qdisc *miniq = rcu_dereference_bh(skb->dev->miniq_ingress);
	काष्ठा tcf_result cl_res;

	/* If there's at least one ingress present somewhere (so
	 * we get here via enabled अटल key), reमुख्यing devices
	 * that are not configured with an ingress qdisc will bail
	 * out here.
	 */
	अगर (!miniq)
		वापस skb;

	अगर (*pt_prev) अणु
		*ret = deliver_skb(skb, *pt_prev, orig_dev);
		*pt_prev = शून्य;
	पूर्ण

	qdisc_skb_cb(skb)->pkt_len = skb->len;
	qdisc_skb_cb(skb)->mru = 0;
	qdisc_skb_cb(skb)->post_ct = false;
	skb->tc_at_ingress = 1;
	mini_qdisc_bstats_cpu_update(miniq, skb);

	चयन (tcf_classअगरy_ingress(skb, miniq->block, miniq->filter_list,
				     &cl_res, false)) अणु
	हाल TC_ACT_OK:
	हाल TC_ACT_RECLASSIFY:
		skb->tc_index = TC_H_MIN(cl_res.classid);
		अवरोध;
	हाल TC_ACT_SHOT:
		mini_qdisc_qstats_cpu_drop(miniq);
		kमुक्त_skb(skb);
		वापस शून्य;
	हाल TC_ACT_STOLEN:
	हाल TC_ACT_QUEUED:
	हाल TC_ACT_TRAP:
		consume_skb(skb);
		वापस शून्य;
	हाल TC_ACT_REसूचीECT:
		/* skb_mac_header check was करोne by cls/act_bpf, so
		 * we can safely push the L2 header back beक्रमe
		 * redirecting to another netdev
		 */
		__skb_push(skb, skb->mac_len);
		अगर (skb_करो_redirect(skb) == -EAGAIN) अणु
			__skb_pull(skb, skb->mac_len);
			*another = true;
			अवरोध;
		पूर्ण
		वापस शून्य;
	हाल TC_ACT_CONSUMED:
		वापस शून्य;
	शेष:
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* CONFIG_NET_CLS_ACT */
	वापस skb;
पूर्ण

/**
 *	netdev_is_rx_handler_busy - check अगर receive handler is रेजिस्टरed
 *	@dev: device to check
 *
 *	Check अगर a receive handler is alपढ़ोy रेजिस्टरed क्रम a given device.
 *	Return true अगर there one.
 *
 *	The caller must hold the rtnl_mutex.
 */
bool netdev_is_rx_handler_busy(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	वापस dev && rtnl_dereference(dev->rx_handler);
पूर्ण
EXPORT_SYMBOL_GPL(netdev_is_rx_handler_busy);

/**
 *	netdev_rx_handler_रेजिस्टर - रेजिस्टर receive handler
 *	@dev: device to रेजिस्टर a handler क्रम
 *	@rx_handler: receive handler to रेजिस्टर
 *	@rx_handler_data: data poपूर्णांकer that is used by rx handler
 *
 *	Register a receive handler क्रम a device. This handler will then be
 *	called from __netअगर_receive_skb. A negative त्रुटि_सं code is वापसed
 *	on a failure.
 *
 *	The caller must hold the rtnl_mutex.
 *
 *	For a general description of rx_handler, see क्रमागत rx_handler_result.
 */
पूर्णांक netdev_rx_handler_रेजिस्टर(काष्ठा net_device *dev,
			       rx_handler_func_t *rx_handler,
			       व्योम *rx_handler_data)
अणु
	अगर (netdev_is_rx_handler_busy(dev))
		वापस -EBUSY;

	अगर (dev->priv_flags & IFF_NO_RX_HANDLER)
		वापस -EINVAL;

	/* Note: rx_handler_data must be set beक्रमe rx_handler */
	rcu_assign_poपूर्णांकer(dev->rx_handler_data, rx_handler_data);
	rcu_assign_poपूर्णांकer(dev->rx_handler, rx_handler);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netdev_rx_handler_रेजिस्टर);

/**
 *	netdev_rx_handler_unरेजिस्टर - unरेजिस्टर receive handler
 *	@dev: device to unरेजिस्टर a handler from
 *
 *	Unरेजिस्टर a receive handler from a device.
 *
 *	The caller must hold the rtnl_mutex.
 */
व्योम netdev_rx_handler_unरेजिस्टर(काष्ठा net_device *dev)
अणु

	ASSERT_RTNL();
	RCU_INIT_POINTER(dev->rx_handler, शून्य);
	/* a पढ़ोer seeing a non शून्य rx_handler in a rcu_पढ़ो_lock()
	 * section has a guarantee to see a non शून्य rx_handler_data
	 * as well.
	 */
	synchronize_net();
	RCU_INIT_POINTER(dev->rx_handler_data, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(netdev_rx_handler_unरेजिस्टर);

/*
 * Limit the use of PFMEMALLOC reserves to those protocols that implement
 * the special handling of PFMEMALLOC skbs.
 */
अटल bool skb_pfmeदो_स्मृति_protocol(काष्ठा sk_buff *skb)
अणु
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_ARP):
	हाल htons(ETH_P_IP):
	हाल htons(ETH_P_IPV6):
	हाल htons(ETH_P_8021Q):
	हाल htons(ETH_P_8021AD):
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक nf_ingress(काष्ठा sk_buff *skb, काष्ठा packet_type **pt_prev,
			     पूर्णांक *ret, काष्ठा net_device *orig_dev)
अणु
	अगर (nf_hook_ingress_active(skb)) अणु
		पूर्णांक ingress_retval;

		अगर (*pt_prev) अणु
			*ret = deliver_skb(skb, *pt_prev, orig_dev);
			*pt_prev = शून्य;
		पूर्ण

		rcu_पढ़ो_lock();
		ingress_retval = nf_hook_ingress(skb);
		rcu_पढ़ो_unlock();
		वापस ingress_retval;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __netअगर_receive_skb_core(काष्ठा sk_buff **pskb, bool pfmeदो_स्मृति,
				    काष्ठा packet_type **ppt_prev)
अणु
	काष्ठा packet_type *ptype, *pt_prev;
	rx_handler_func_t *rx_handler;
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा net_device *orig_dev;
	bool deliver_exact = false;
	पूर्णांक ret = NET_RX_DROP;
	__be16 type;

	net_बारtamp_check(!netdev_tstamp_prequeue, skb);

	trace_netअगर_receive_skb(skb);

	orig_dev = skb->dev;

	skb_reset_network_header(skb);
	अगर (!skb_transport_header_was_set(skb))
		skb_reset_transport_header(skb);
	skb_reset_mac_len(skb);

	pt_prev = शून्य;

another_round:
	skb->skb_iअगर = skb->dev->अगरindex;

	__this_cpu_inc(softnet_data.processed);

	अगर (अटल_branch_unlikely(&generic_xdp_needed_key)) अणु
		पूर्णांक ret2;

		preempt_disable();
		ret2 = करो_xdp_generic(rcu_dereference(skb->dev->xdp_prog), skb);
		preempt_enable();

		अगर (ret2 != XDP_PASS) अणु
			ret = NET_RX_DROP;
			जाओ out;
		पूर्ण
		skb_reset_mac_len(skb);
	पूर्ण

	अगर (eth_type_vlan(skb->protocol)) अणु
		skb = skb_vlan_untag(skb);
		अगर (unlikely(!skb))
			जाओ out;
	पूर्ण

	अगर (skb_skip_tc_classअगरy(skb))
		जाओ skip_classअगरy;

	अगर (pfmeदो_स्मृति)
		जाओ skip_taps;

	list_क्रम_each_entry_rcu(ptype, &ptype_all, list) अणु
		अगर (pt_prev)
			ret = deliver_skb(skb, pt_prev, orig_dev);
		pt_prev = ptype;
	पूर्ण

	list_क्रम_each_entry_rcu(ptype, &skb->dev->ptype_all, list) अणु
		अगर (pt_prev)
			ret = deliver_skb(skb, pt_prev, orig_dev);
		pt_prev = ptype;
	पूर्ण

skip_taps:
#अगर_घोषित CONFIG_NET_INGRESS
	अगर (अटल_branch_unlikely(&ingress_needed_key)) अणु
		bool another = false;

		skb = sch_handle_ingress(skb, &pt_prev, &ret, orig_dev,
					 &another);
		अगर (another)
			जाओ another_round;
		अगर (!skb)
			जाओ out;

		अगर (nf_ingress(skb, &pt_prev, &ret, orig_dev) < 0)
			जाओ out;
	पूर्ण
#पूर्ण_अगर
	skb_reset_redirect(skb);
skip_classअगरy:
	अगर (pfmeदो_स्मृति && !skb_pfmeदो_स्मृति_protocol(skb))
		जाओ drop;

	अगर (skb_vlan_tag_present(skb)) अणु
		अगर (pt_prev) अणु
			ret = deliver_skb(skb, pt_prev, orig_dev);
			pt_prev = शून्य;
		पूर्ण
		अगर (vlan_करो_receive(&skb))
			जाओ another_round;
		अन्यथा अगर (unlikely(!skb))
			जाओ out;
	पूर्ण

	rx_handler = rcu_dereference(skb->dev->rx_handler);
	अगर (rx_handler) अणु
		अगर (pt_prev) अणु
			ret = deliver_skb(skb, pt_prev, orig_dev);
			pt_prev = शून्य;
		पूर्ण
		चयन (rx_handler(&skb)) अणु
		हाल RX_HANDLER_CONSUMED:
			ret = NET_RX_SUCCESS;
			जाओ out;
		हाल RX_HANDLER_ANOTHER:
			जाओ another_round;
		हाल RX_HANDLER_EXACT:
			deliver_exact = true;
			अवरोध;
		हाल RX_HANDLER_PASS:
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	अगर (unlikely(skb_vlan_tag_present(skb)) && !netdev_uses_dsa(skb->dev)) अणु
check_vlan_id:
		अगर (skb_vlan_tag_get_id(skb)) अणु
			/* Vlan id is non 0 and vlan_करो_receive() above couldn't
			 * find vlan device.
			 */
			skb->pkt_type = PACKET_OTHERHOST;
		पूर्ण अन्यथा अगर (eth_type_vlan(skb->protocol)) अणु
			/* Outer header is 802.1P with vlan 0, inner header is
			 * 802.1Q or 802.1AD and vlan_करो_receive() above could
			 * not find vlan dev क्रम vlan id 0.
			 */
			__vlan_hwaccel_clear_tag(skb);
			skb = skb_vlan_untag(skb);
			अगर (unlikely(!skb))
				जाओ out;
			अगर (vlan_करो_receive(&skb))
				/* After stripping off 802.1P header with vlan 0
				 * vlan dev is found क्रम inner header.
				 */
				जाओ another_round;
			अन्यथा अगर (unlikely(!skb))
				जाओ out;
			अन्यथा
				/* We have stripped outer 802.1P vlan 0 header.
				 * But could not find vlan dev.
				 * check again क्रम vlan id to set OTHERHOST.
				 */
				जाओ check_vlan_id;
		पूर्ण
		/* Note: we might in the future use prio bits
		 * and set skb->priority like in vlan_करो_receive()
		 * For the समय being, just ignore Priority Code Poपूर्णांक
		 */
		__vlan_hwaccel_clear_tag(skb);
	पूर्ण

	type = skb->protocol;

	/* deliver only exact match when indicated */
	अगर (likely(!deliver_exact)) अणु
		deliver_ptype_list_skb(skb, &pt_prev, orig_dev, type,
				       &ptype_base[ntohs(type) &
						   PTYPE_HASH_MASK]);
	पूर्ण

	deliver_ptype_list_skb(skb, &pt_prev, orig_dev, type,
			       &orig_dev->ptype_specअगरic);

	अगर (unlikely(skb->dev != orig_dev)) अणु
		deliver_ptype_list_skb(skb, &pt_prev, orig_dev, type,
				       &skb->dev->ptype_specअगरic);
	पूर्ण

	अगर (pt_prev) अणु
		अगर (unlikely(skb_orphan_frags_rx(skb, GFP_ATOMIC)))
			जाओ drop;
		*ppt_prev = pt_prev;
	पूर्ण अन्यथा अणु
drop:
		अगर (!deliver_exact)
			atomic_दीर्घ_inc(&skb->dev->rx_dropped);
		अन्यथा
			atomic_दीर्घ_inc(&skb->dev->rx_nohandler);
		kमुक्त_skb(skb);
		/* Jamal, now you will not able to escape explaining
		 * me how you were going to use this. :-)
		 */
		ret = NET_RX_DROP;
	पूर्ण

out:
	/* The invariant here is that अगर *ppt_prev is not शून्य
	 * then skb should also be non-शून्य.
	 *
	 * Apparently *ppt_prev assignment above holds this invariant due to
	 * skb dereferencing near it.
	 */
	*pskb = skb;
	वापस ret;
पूर्ण

अटल पूर्णांक __netअगर_receive_skb_one_core(काष्ठा sk_buff *skb, bool pfmeदो_स्मृति)
अणु
	काष्ठा net_device *orig_dev = skb->dev;
	काष्ठा packet_type *pt_prev = शून्य;
	पूर्णांक ret;

	ret = __netअगर_receive_skb_core(&skb, pfmeदो_स्मृति, &pt_prev);
	अगर (pt_prev)
		ret = INसूचीECT_CALL_INET(pt_prev->func, ipv6_rcv, ip_rcv, skb,
					 skb->dev, pt_prev, orig_dev);
	वापस ret;
पूर्ण

/**
 *	netअगर_receive_skb_core - special purpose version of netअगर_receive_skb
 *	@skb: buffer to process
 *
 *	More direct receive version of netअगर_receive_skb().  It should
 *	only be used by callers that have a need to skip RPS and Generic XDP.
 *	Caller must also take care of handling अगर ``(page_is_)pfmeदो_स्मृति``.
 *
 *	This function may only be called from softirq context and पूर्णांकerrupts
 *	should be enabled.
 *
 *	Return values (usually ignored):
 *	NET_RX_SUCCESS: no congestion
 *	NET_RX_DROP: packet was dropped
 */
पूर्णांक netअगर_receive_skb_core(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = __netअगर_receive_skb_one_core(skb, false);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(netअगर_receive_skb_core);

अटल अंतरभूत व्योम __netअगर_receive_skb_list_ptype(काष्ठा list_head *head,
						  काष्ठा packet_type *pt_prev,
						  काष्ठा net_device *orig_dev)
अणु
	काष्ठा sk_buff *skb, *next;

	अगर (!pt_prev)
		वापस;
	अगर (list_empty(head))
		वापस;
	अगर (pt_prev->list_func != शून्य)
		INसूचीECT_CALL_INET(pt_prev->list_func, ipv6_list_rcv,
				   ip_list_rcv, head, pt_prev, orig_dev);
	अन्यथा
		list_क्रम_each_entry_safe(skb, next, head, list) अणु
			skb_list_del_init(skb);
			pt_prev->func(skb, skb->dev, pt_prev, orig_dev);
		पूर्ण
पूर्ण

अटल व्योम __netअगर_receive_skb_list_core(काष्ठा list_head *head, bool pfmeदो_स्मृति)
अणु
	/* Fast-path assumptions:
	 * - There is no RX handler.
	 * - Only one packet_type matches.
	 * If either of these fails, we will end up करोing some per-packet
	 * processing in-line, then handling the 'last ptype' क्रम the whole
	 * sublist.  This can't cause out-of-order delivery to any single ptype,
	 * because the 'last ptype' must be स्थिरant across the sublist, and all
	 * other ptypes are handled per-packet.
	 */
	/* Current (common) ptype of sublist */
	काष्ठा packet_type *pt_curr = शून्य;
	/* Current (common) orig_dev of sublist */
	काष्ठा net_device *od_curr = शून्य;
	काष्ठा list_head sublist;
	काष्ठा sk_buff *skb, *next;

	INIT_LIST_HEAD(&sublist);
	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		काष्ठा net_device *orig_dev = skb->dev;
		काष्ठा packet_type *pt_prev = शून्य;

		skb_list_del_init(skb);
		__netअगर_receive_skb_core(&skb, pfmeदो_स्मृति, &pt_prev);
		अगर (!pt_prev)
			जारी;
		अगर (pt_curr != pt_prev || od_curr != orig_dev) अणु
			/* dispatch old sublist */
			__netअगर_receive_skb_list_ptype(&sublist, pt_curr, od_curr);
			/* start new sublist */
			INIT_LIST_HEAD(&sublist);
			pt_curr = pt_prev;
			od_curr = orig_dev;
		पूर्ण
		list_add_tail(&skb->list, &sublist);
	पूर्ण

	/* dispatch final sublist */
	__netअगर_receive_skb_list_ptype(&sublist, pt_curr, od_curr);
पूर्ण

अटल पूर्णांक __netअगर_receive_skb(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	अगर (sk_meदो_स्मृति_socks() && skb_pfmeदो_स्मृति(skb)) अणु
		अचिन्हित पूर्णांक noreclaim_flag;

		/*
		 * PFMEMALLOC skbs are special, they should
		 * - be delivered to SOCK_MEMALLOC sockets only
		 * - stay away from userspace
		 * - have bounded memory usage
		 *
		 * Use PF_MEMALLOC as this saves us from propagating the allocation
		 * context करोwn to all allocation sites.
		 */
		noreclaim_flag = meदो_स्मृति_noreclaim_save();
		ret = __netअगर_receive_skb_one_core(skb, true);
		meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	पूर्ण अन्यथा
		ret = __netअगर_receive_skb_one_core(skb, false);

	वापस ret;
पूर्ण

अटल व्योम __netअगर_receive_skb_list(काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ noreclaim_flag = 0;
	काष्ठा sk_buff *skb, *next;
	bool pfmeदो_स्मृति = false; /* Is current sublist PF_MEMALLOC? */

	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		अगर ((sk_meदो_स्मृति_socks() && skb_pfmeदो_स्मृति(skb)) != pfmeदो_स्मृति) अणु
			काष्ठा list_head sublist;

			/* Handle the previous sublist */
			list_cut_beक्रमe(&sublist, head, &skb->list);
			अगर (!list_empty(&sublist))
				__netअगर_receive_skb_list_core(&sublist, pfmeदो_स्मृति);
			pfmeदो_स्मृति = !pfmeदो_स्मृति;
			/* See comments in __netअगर_receive_skb */
			अगर (pfmeदो_स्मृति)
				noreclaim_flag = meदो_स्मृति_noreclaim_save();
			अन्यथा
				meदो_स्मृति_noreclaim_restore(noreclaim_flag);
		पूर्ण
	पूर्ण
	/* Handle the reमुख्यing sublist */
	अगर (!list_empty(head))
		__netअगर_receive_skb_list_core(head, pfmeदो_स्मृति);
	/* Restore pflags */
	अगर (pfmeदो_स्मृति)
		meदो_स्मृति_noreclaim_restore(noreclaim_flag);
पूर्ण

अटल पूर्णांक generic_xdp_install(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा bpf_prog *old = rtnl_dereference(dev->xdp_prog);
	काष्ठा bpf_prog *new = xdp->prog;
	पूर्णांक ret = 0;

	अगर (new) अणु
		u32 i;

		mutex_lock(&new->aux->used_maps_mutex);

		/* generic XDP करोes not work with DEVMAPs that can
		 * have a bpf_prog installed on an entry
		 */
		क्रम (i = 0; i < new->aux->used_map_cnt; i++) अणु
			अगर (dev_map_can_have_prog(new->aux->used_maps[i]) ||
			    cpu_map_prog_allowed(new->aux->used_maps[i])) अणु
				mutex_unlock(&new->aux->used_maps_mutex);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		mutex_unlock(&new->aux->used_maps_mutex);
	पूर्ण

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		rcu_assign_poपूर्णांकer(dev->xdp_prog, new);
		अगर (old)
			bpf_prog_put(old);

		अगर (old && !new) अणु
			अटल_branch_dec(&generic_xdp_needed_key);
		पूर्ण अन्यथा अगर (new && !old) अणु
			अटल_branch_inc(&generic_xdp_needed_key);
			dev_disable_lro(dev);
			dev_disable_gro_hw(dev);
		पूर्ण
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक netअगर_receive_skb_पूर्णांकernal(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	net_बारtamp_check(netdev_tstamp_prequeue, skb);

	अगर (skb_defer_rx_बारtamp(skb))
		वापस NET_RX_SUCCESS;

	rcu_पढ़ो_lock();
#अगर_घोषित CONFIG_RPS
	अगर (अटल_branch_unlikely(&rps_needed)) अणु
		काष्ठा rps_dev_flow व्योमflow, *rflow = &व्योमflow;
		पूर्णांक cpu = get_rps_cpu(skb->dev, skb, &rflow);

		अगर (cpu >= 0) अणु
			ret = enqueue_to_backlog(skb, cpu, &rflow->last_qtail);
			rcu_पढ़ो_unlock();
			वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	ret = __netअगर_receive_skb(skb);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल व्योम netअगर_receive_skb_list_पूर्णांकernal(काष्ठा list_head *head)
अणु
	काष्ठा sk_buff *skb, *next;
	काष्ठा list_head sublist;

	INIT_LIST_HEAD(&sublist);
	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		net_बारtamp_check(netdev_tstamp_prequeue, skb);
		skb_list_del_init(skb);
		अगर (!skb_defer_rx_बारtamp(skb))
			list_add_tail(&skb->list, &sublist);
	पूर्ण
	list_splice_init(&sublist, head);

	rcu_पढ़ो_lock();
#अगर_घोषित CONFIG_RPS
	अगर (अटल_branch_unlikely(&rps_needed)) अणु
		list_क्रम_each_entry_safe(skb, next, head, list) अणु
			काष्ठा rps_dev_flow व्योमflow, *rflow = &व्योमflow;
			पूर्णांक cpu = get_rps_cpu(skb->dev, skb, &rflow);

			अगर (cpu >= 0) अणु
				/* Will be handled, हटाओ from list */
				skb_list_del_init(skb);
				enqueue_to_backlog(skb, cpu, &rflow->last_qtail);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	__netअगर_receive_skb_list(head);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 *	netअगर_receive_skb - process receive buffer from network
 *	@skb: buffer to process
 *
 *	netअगर_receive_skb() is the मुख्य receive data processing function.
 *	It always succeeds. The buffer may be dropped during processing
 *	क्रम congestion control or by the protocol layers.
 *
 *	This function may only be called from softirq context and पूर्णांकerrupts
 *	should be enabled.
 *
 *	Return values (usually ignored):
 *	NET_RX_SUCCESS: no congestion
 *	NET_RX_DROP: packet was dropped
 */
पूर्णांक netअगर_receive_skb(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	trace_netअगर_receive_skb_entry(skb);

	ret = netअगर_receive_skb_पूर्णांकernal(skb);
	trace_netअगर_receive_skb_निकास(ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(netअगर_receive_skb);

/**
 *	netअगर_receive_skb_list - process many receive buffers from network
 *	@head: list of skbs to process.
 *
 *	Since वापस value of netअगर_receive_skb() is normally ignored, and
 *	wouldn't be meaningful क्रम a list, this function वापसs व्योम.
 *
 *	This function may only be called from softirq context and पूर्णांकerrupts
 *	should be enabled.
 */
व्योम netअगर_receive_skb_list(काष्ठा list_head *head)
अणु
	काष्ठा sk_buff *skb;

	अगर (list_empty(head))
		वापस;
	अगर (trace_netअगर_receive_skb_list_entry_enabled()) अणु
		list_क्रम_each_entry(skb, head, list)
			trace_netअगर_receive_skb_list_entry(skb);
	पूर्ण
	netअगर_receive_skb_list_पूर्णांकernal(head);
	trace_netअगर_receive_skb_list_निकास(0);
पूर्ण
EXPORT_SYMBOL(netअगर_receive_skb_list);

अटल DEFINE_PER_CPU(काष्ठा work_काष्ठा, flush_works);

/* Network device is going away, flush any packets still pending */
अटल व्योम flush_backlog(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;
	काष्ठा softnet_data *sd;

	local_bh_disable();
	sd = this_cpu_ptr(&softnet_data);

	local_irq_disable();
	rps_lock(sd);
	skb_queue_walk_safe(&sd->input_pkt_queue, skb, पंचांगp) अणु
		अगर (skb->dev->reg_state == NETREG_UNREGISTERING) अणु
			__skb_unlink(skb, &sd->input_pkt_queue);
			dev_kमुक्त_skb_irq(skb);
			input_queue_head_incr(sd);
		पूर्ण
	पूर्ण
	rps_unlock(sd);
	local_irq_enable();

	skb_queue_walk_safe(&sd->process_queue, skb, पंचांगp) अणु
		अगर (skb->dev->reg_state == NETREG_UNREGISTERING) अणु
			__skb_unlink(skb, &sd->process_queue);
			kमुक्त_skb(skb);
			input_queue_head_incr(sd);
		पूर्ण
	पूर्ण
	local_bh_enable();
पूर्ण

अटल bool flush_required(पूर्णांक cpu)
अणु
#अगर IS_ENABLED(CONFIG_RPS)
	काष्ठा softnet_data *sd = &per_cpu(softnet_data, cpu);
	bool करो_flush;

	local_irq_disable();
	rps_lock(sd);

	/* as insertion पूर्णांकo process_queue happens with the rps lock held,
	 * process_queue access may race only with dequeue
	 */
	करो_flush = !skb_queue_empty(&sd->input_pkt_queue) ||
		   !skb_queue_empty_lockless(&sd->process_queue);
	rps_unlock(sd);
	local_irq_enable();

	वापस करो_flush;
#पूर्ण_अगर
	/* without RPS we can't safely check input_pkt_queue: during a
	 * concurrent remote skb_queue_splice() we can detect as empty both
	 * input_pkt_queue and process_queue even अगर the latter could end-up
	 * containing a lot of packets.
	 */
	वापस true;
पूर्ण

अटल व्योम flush_all_backlogs(व्योम)
अणु
	अटल cpumask_t flush_cpus;
	अचिन्हित पूर्णांक cpu;

	/* since we are under rtnl lock protection we can use अटल data
	 * क्रम the cpumask and aव्योम allocating on stack the possibly
	 * large mask
	 */
	ASSERT_RTNL();

	get_online_cpus();

	cpumask_clear(&flush_cpus);
	क्रम_each_online_cpu(cpu) अणु
		अगर (flush_required(cpu)) अणु
			queue_work_on(cpu, प्रणाली_highpri_wq,
				      per_cpu_ptr(&flush_works, cpu));
			cpumask_set_cpu(cpu, &flush_cpus);
		पूर्ण
	पूर्ण

	/* we can have in flight packet[s] on the cpus we are not flushing,
	 * synchronize_net() in unरेजिस्टर_netdevice_many() will take care of
	 * them
	 */
	क्रम_each_cpu(cpu, &flush_cpus)
		flush_work(per_cpu_ptr(&flush_works, cpu));

	put_online_cpus();
पूर्ण

/* Pass the currently batched GRO_NORMAL SKBs up to the stack. */
अटल व्योम gro_normal_list(काष्ठा napi_काष्ठा *napi)
अणु
	अगर (!napi->rx_count)
		वापस;
	netअगर_receive_skb_list_पूर्णांकernal(&napi->rx_list);
	INIT_LIST_HEAD(&napi->rx_list);
	napi->rx_count = 0;
पूर्ण

/* Queue one GRO_NORMAL SKB up क्रम list processing. If batch size exceeded,
 * pass the whole batch up to the stack.
 */
अटल व्योम gro_normal_one(काष्ठा napi_काष्ठा *napi, काष्ठा sk_buff *skb, पूर्णांक segs)
अणु
	list_add_tail(&skb->list, &napi->rx_list);
	napi->rx_count += segs;
	अगर (napi->rx_count >= gro_normal_batch)
		gro_normal_list(napi);
पूर्ण

अटल पूर्णांक napi_gro_complete(काष्ठा napi_काष्ठा *napi, काष्ठा sk_buff *skb)
अणु
	काष्ठा packet_offload *ptype;
	__be16 type = skb->protocol;
	काष्ठा list_head *head = &offload_base;
	पूर्णांक err = -ENOENT;

	BUILD_BUG_ON(माप(काष्ठा napi_gro_cb) > माप(skb->cb));

	अगर (NAPI_GRO_CB(skb)->count == 1) अणु
		skb_shinfo(skb)->gso_size = 0;
		जाओ out;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ptype, head, list) अणु
		अगर (ptype->type != type || !ptype->callbacks.gro_complete)
			जारी;

		err = INसूचीECT_CALL_INET(ptype->callbacks.gro_complete,
					 ipv6_gro_complete, inet_gro_complete,
					 skb, 0);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (err) अणु
		WARN_ON(&ptype->list == head);
		kमुक्त_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

out:
	gro_normal_one(napi, skb, NAPI_GRO_CB(skb)->count);
	वापस NET_RX_SUCCESS;
पूर्ण

अटल व्योम __napi_gro_flush_chain(काष्ठा napi_काष्ठा *napi, u32 index,
				   bool flush_old)
अणु
	काष्ठा list_head *head = &napi->gro_hash[index].list;
	काष्ठा sk_buff *skb, *p;

	list_क्रम_each_entry_safe_reverse(skb, p, head, list) अणु
		अगर (flush_old && NAPI_GRO_CB(skb)->age == jअगरfies)
			वापस;
		skb_list_del_init(skb);
		napi_gro_complete(napi, skb);
		napi->gro_hash[index].count--;
	पूर्ण

	अगर (!napi->gro_hash[index].count)
		__clear_bit(index, &napi->gro_biपंचांगask);
पूर्ण

/* napi->gro_hash[].list contains packets ordered by age.
 * youngest packets at the head of it.
 * Complete skbs in reverse order to reduce latencies.
 */
व्योम napi_gro_flush(काष्ठा napi_काष्ठा *napi, bool flush_old)
अणु
	अचिन्हित दीर्घ biपंचांगask = napi->gro_biपंचांगask;
	अचिन्हित पूर्णांक i, base = ~0U;

	जबतक ((i = ffs(biपंचांगask)) != 0) अणु
		biपंचांगask >>= i;
		base += i;
		__napi_gro_flush_chain(napi, base, flush_old);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(napi_gro_flush);

अटल व्योम gro_list_prepare(स्थिर काष्ठा list_head *head,
			     स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक maclen = skb->dev->hard_header_len;
	u32 hash = skb_get_hash_raw(skb);
	काष्ठा sk_buff *p;

	list_क्रम_each_entry(p, head, list) अणु
		अचिन्हित दीर्घ dअगरfs;

		NAPI_GRO_CB(p)->flush = 0;

		अगर (hash != skb_get_hash_raw(p)) अणु
			NAPI_GRO_CB(p)->same_flow = 0;
			जारी;
		पूर्ण

		dअगरfs = (अचिन्हित दीर्घ)p->dev ^ (अचिन्हित दीर्घ)skb->dev;
		dअगरfs |= skb_vlan_tag_present(p) ^ skb_vlan_tag_present(skb);
		अगर (skb_vlan_tag_present(p))
			dअगरfs |= skb_vlan_tag_get(p) ^ skb_vlan_tag_get(skb);
		dअगरfs |= skb_metadata_dst_cmp(p, skb);
		dअगरfs |= skb_metadata_dअगरfers(p, skb);
		अगर (maclen == ETH_HLEN)
			dअगरfs |= compare_ether_header(skb_mac_header(p),
						      skb_mac_header(skb));
		अन्यथा अगर (!dअगरfs)
			dअगरfs = स_भेद(skb_mac_header(p),
				       skb_mac_header(skb),
				       maclen);
		NAPI_GRO_CB(p)->same_flow = !dअगरfs;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम skb_gro_reset_offset(काष्ठा sk_buff *skb, u32 nhoff)
अणु
	स्थिर काष्ठा skb_shared_info *pinfo = skb_shinfo(skb);
	स्थिर skb_frag_t *frag0 = &pinfo->frags[0];

	NAPI_GRO_CB(skb)->data_offset = 0;
	NAPI_GRO_CB(skb)->frag0 = शून्य;
	NAPI_GRO_CB(skb)->frag0_len = 0;

	अगर (!skb_headlen(skb) && pinfo->nr_frags &&
	    !PageHighMem(skb_frag_page(frag0)) &&
	    (!NET_IP_ALIGN || !((skb_frag_off(frag0) + nhoff) & 3))) अणु
		NAPI_GRO_CB(skb)->frag0 = skb_frag_address(frag0);
		NAPI_GRO_CB(skb)->frag0_len = min_t(अचिन्हित पूर्णांक,
						    skb_frag_size(frag0),
						    skb->end - skb->tail);
	पूर्ण
पूर्ण

अटल व्योम gro_pull_from_frag0(काष्ठा sk_buff *skb, पूर्णांक grow)
अणु
	काष्ठा skb_shared_info *pinfo = skb_shinfo(skb);

	BUG_ON(skb->end - skb->tail < grow);

	स_नकल(skb_tail_poपूर्णांकer(skb), NAPI_GRO_CB(skb)->frag0, grow);

	skb->data_len -= grow;
	skb->tail += grow;

	skb_frag_off_add(&pinfo->frags[0], grow);
	skb_frag_size_sub(&pinfo->frags[0], grow);

	अगर (unlikely(!skb_frag_size(&pinfo->frags[0]))) अणु
		skb_frag_unref(skb, 0);
		स_हटाओ(pinfo->frags, pinfo->frags + 1,
			--pinfo->nr_frags * माप(pinfo->frags[0]));
	पूर्ण
पूर्ण

अटल व्योम gro_flush_oldest(काष्ठा napi_काष्ठा *napi, काष्ठा list_head *head)
अणु
	काष्ठा sk_buff *oldest;

	oldest = list_last_entry(head, काष्ठा sk_buff, list);

	/* We are called with head length >= MAX_GRO_SKBS, so this is
	 * impossible.
	 */
	अगर (WARN_ON_ONCE(!oldest))
		वापस;

	/* Do not adjust napi->gro_hash[].count, caller is adding a new
	 * SKB to the chain.
	 */
	skb_list_del_init(oldest);
	napi_gro_complete(napi, oldest);
पूर्ण

अटल क्रमागत gro_result dev_gro_receive(काष्ठा napi_काष्ठा *napi, काष्ठा sk_buff *skb)
अणु
	u32 bucket = skb_get_hash_raw(skb) & (GRO_HASH_BUCKETS - 1);
	काष्ठा gro_list *gro_list = &napi->gro_hash[bucket];
	काष्ठा list_head *head = &offload_base;
	काष्ठा packet_offload *ptype;
	__be16 type = skb->protocol;
	काष्ठा sk_buff *pp = शून्य;
	क्रमागत gro_result ret;
	पूर्णांक same_flow;
	पूर्णांक grow;

	अगर (netअगर_elide_gro(skb->dev))
		जाओ normal;

	gro_list_prepare(&gro_list->list, skb);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ptype, head, list) अणु
		अगर (ptype->type != type || !ptype->callbacks.gro_receive)
			जारी;

		skb_set_network_header(skb, skb_gro_offset(skb));
		skb_reset_mac_len(skb);
		NAPI_GRO_CB(skb)->same_flow = 0;
		NAPI_GRO_CB(skb)->flush = skb_is_gso(skb) || skb_has_frag_list(skb);
		NAPI_GRO_CB(skb)->मुक्त = 0;
		NAPI_GRO_CB(skb)->encap_mark = 0;
		NAPI_GRO_CB(skb)->recursion_counter = 0;
		NAPI_GRO_CB(skb)->is_fou = 0;
		NAPI_GRO_CB(skb)->is_atomic = 1;
		NAPI_GRO_CB(skb)->gro_remcsum_start = 0;

		/* Setup क्रम GRO checksum validation */
		चयन (skb->ip_summed) अणु
		हाल CHECKSUM_COMPLETE:
			NAPI_GRO_CB(skb)->csum = skb->csum;
			NAPI_GRO_CB(skb)->csum_valid = 1;
			NAPI_GRO_CB(skb)->csum_cnt = 0;
			अवरोध;
		हाल CHECKSUM_UNNECESSARY:
			NAPI_GRO_CB(skb)->csum_cnt = skb->csum_level + 1;
			NAPI_GRO_CB(skb)->csum_valid = 0;
			अवरोध;
		शेष:
			NAPI_GRO_CB(skb)->csum_cnt = 0;
			NAPI_GRO_CB(skb)->csum_valid = 0;
		पूर्ण

		pp = INसूचीECT_CALL_INET(ptype->callbacks.gro_receive,
					ipv6_gro_receive, inet_gro_receive,
					&gro_list->list, skb);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (&ptype->list == head)
		जाओ normal;

	अगर (PTR_ERR(pp) == -EINPROGRESS) अणु
		ret = GRO_CONSUMED;
		जाओ ok;
	पूर्ण

	same_flow = NAPI_GRO_CB(skb)->same_flow;
	ret = NAPI_GRO_CB(skb)->मुक्त ? GRO_MERGED_FREE : GRO_MERGED;

	अगर (pp) अणु
		skb_list_del_init(pp);
		napi_gro_complete(napi, pp);
		gro_list->count--;
	पूर्ण

	अगर (same_flow)
		जाओ ok;

	अगर (NAPI_GRO_CB(skb)->flush)
		जाओ normal;

	अगर (unlikely(gro_list->count >= MAX_GRO_SKBS))
		gro_flush_oldest(napi, &gro_list->list);
	अन्यथा
		gro_list->count++;

	NAPI_GRO_CB(skb)->count = 1;
	NAPI_GRO_CB(skb)->age = jअगरfies;
	NAPI_GRO_CB(skb)->last = skb;
	skb_shinfo(skb)->gso_size = skb_gro_len(skb);
	list_add(&skb->list, &gro_list->list);
	ret = GRO_HELD;

pull:
	grow = skb_gro_offset(skb) - skb_headlen(skb);
	अगर (grow > 0)
		gro_pull_from_frag0(skb, grow);
ok:
	अगर (gro_list->count) अणु
		अगर (!test_bit(bucket, &napi->gro_biपंचांगask))
			__set_bit(bucket, &napi->gro_biपंचांगask);
	पूर्ण अन्यथा अगर (test_bit(bucket, &napi->gro_biपंचांगask)) अणु
		__clear_bit(bucket, &napi->gro_biपंचांगask);
	पूर्ण

	वापस ret;

normal:
	ret = GRO_NORMAL;
	जाओ pull;
पूर्ण

काष्ठा packet_offload *gro_find_receive_by_type(__be16 type)
अणु
	काष्ठा list_head *offload_head = &offload_base;
	काष्ठा packet_offload *ptype;

	list_क्रम_each_entry_rcu(ptype, offload_head, list) अणु
		अगर (ptype->type != type || !ptype->callbacks.gro_receive)
			जारी;
		वापस ptype;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(gro_find_receive_by_type);

काष्ठा packet_offload *gro_find_complete_by_type(__be16 type)
अणु
	काष्ठा list_head *offload_head = &offload_base;
	काष्ठा packet_offload *ptype;

	list_क्रम_each_entry_rcu(ptype, offload_head, list) अणु
		अगर (ptype->type != type || !ptype->callbacks.gro_complete)
			जारी;
		वापस ptype;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(gro_find_complete_by_type);

अटल gro_result_t napi_skb_finish(काष्ठा napi_काष्ठा *napi,
				    काष्ठा sk_buff *skb,
				    gro_result_t ret)
अणु
	चयन (ret) अणु
	हाल GRO_NORMAL:
		gro_normal_one(napi, skb, 1);
		अवरोध;

	हाल GRO_MERGED_FREE:
		अगर (NAPI_GRO_CB(skb)->मुक्त == NAPI_GRO_FREE_STOLEN_HEAD)
			napi_skb_मुक्त_stolen_head(skb);
		अन्यथा
			__kमुक्त_skb_defer(skb);
		अवरोध;

	हाल GRO_HELD:
	हाल GRO_MERGED:
	हाल GRO_CONSUMED:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

gro_result_t napi_gro_receive(काष्ठा napi_काष्ठा *napi, काष्ठा sk_buff *skb)
अणु
	gro_result_t ret;

	skb_mark_napi_id(skb, napi);
	trace_napi_gro_receive_entry(skb);

	skb_gro_reset_offset(skb, 0);

	ret = napi_skb_finish(napi, skb, dev_gro_receive(napi, skb));
	trace_napi_gro_receive_निकास(ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(napi_gro_receive);

अटल व्योम napi_reuse_skb(काष्ठा napi_काष्ठा *napi, काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(skb->pfmeदो_स्मृति)) अणु
		consume_skb(skb);
		वापस;
	पूर्ण
	__skb_pull(skb, skb_headlen(skb));
	/* restore the reserve we had after netdev_alloc_skb_ip_align() */
	skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN - skb_headroom(skb));
	__vlan_hwaccel_clear_tag(skb);
	skb->dev = napi->dev;
	skb->skb_iअगर = 0;

	/* eth_type_trans() assumes pkt_type is PACKET_HOST */
	skb->pkt_type = PACKET_HOST;

	skb->encapsulation = 0;
	skb_shinfo(skb)->gso_type = 0;
	skb->truesize = SKB_TRUESIZE(skb_end_offset(skb));
	skb_ext_reset(skb);

	napi->skb = skb;
पूर्ण

काष्ठा sk_buff *napi_get_frags(काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा sk_buff *skb = napi->skb;

	अगर (!skb) अणु
		skb = napi_alloc_skb(napi, GRO_MAX_HEAD);
		अगर (skb) अणु
			napi->skb = skb;
			skb_mark_napi_id(skb, napi);
		पूर्ण
	पूर्ण
	वापस skb;
पूर्ण
EXPORT_SYMBOL(napi_get_frags);

अटल gro_result_t napi_frags_finish(काष्ठा napi_काष्ठा *napi,
				      काष्ठा sk_buff *skb,
				      gro_result_t ret)
अणु
	चयन (ret) अणु
	हाल GRO_NORMAL:
	हाल GRO_HELD:
		__skb_push(skb, ETH_HLEN);
		skb->protocol = eth_type_trans(skb, skb->dev);
		अगर (ret == GRO_NORMAL)
			gro_normal_one(napi, skb, 1);
		अवरोध;

	हाल GRO_MERGED_FREE:
		अगर (NAPI_GRO_CB(skb)->मुक्त == NAPI_GRO_FREE_STOLEN_HEAD)
			napi_skb_मुक्त_stolen_head(skb);
		अन्यथा
			napi_reuse_skb(napi, skb);
		अवरोध;

	हाल GRO_MERGED:
	हाल GRO_CONSUMED:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Upper GRO stack assumes network header starts at gro_offset=0
 * Drivers could call both napi_gro_frags() and napi_gro_receive()
 * We copy ethernet header पूर्णांकo skb->data to have a common layout.
 */
अटल काष्ठा sk_buff *napi_frags_skb(काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा sk_buff *skb = napi->skb;
	स्थिर काष्ठा ethhdr *eth;
	अचिन्हित पूर्णांक hlen = माप(*eth);

	napi->skb = शून्य;

	skb_reset_mac_header(skb);
	skb_gro_reset_offset(skb, hlen);

	अगर (unlikely(skb_gro_header_hard(skb, hlen))) अणु
		eth = skb_gro_header_slow(skb, hlen, 0);
		अगर (unlikely(!eth)) अणु
			net_warn_ratelimited("%s: dropping impossible skb from %s\n",
					     __func__, napi->dev->name);
			napi_reuse_skb(napi, skb);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		eth = (स्थिर काष्ठा ethhdr *)skb->data;
		gro_pull_from_frag0(skb, hlen);
		NAPI_GRO_CB(skb)->frag0 += hlen;
		NAPI_GRO_CB(skb)->frag0_len -= hlen;
	पूर्ण
	__skb_pull(skb, hlen);

	/*
	 * This works because the only protocols we care about करोn't require
	 * special handling.
	 * We'll fix it up properly in napi_frags_finish()
	 */
	skb->protocol = eth->h_proto;

	वापस skb;
पूर्ण

gro_result_t napi_gro_frags(काष्ठा napi_काष्ठा *napi)
अणु
	gro_result_t ret;
	काष्ठा sk_buff *skb = napi_frags_skb(napi);

	trace_napi_gro_frags_entry(skb);

	ret = napi_frags_finish(napi, skb, dev_gro_receive(napi, skb));
	trace_napi_gro_frags_निकास(ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(napi_gro_frags);

/* Compute the checksum from gro_offset and वापस the folded value
 * after adding in any pseuकरो checksum.
 */
__sum16 __skb_gro_checksum_complete(काष्ठा sk_buff *skb)
अणु
	__wsum wsum;
	__sum16 sum;

	wsum = skb_checksum(skb, skb_gro_offset(skb), skb_gro_len(skb), 0);

	/* NAPI_GRO_CB(skb)->csum holds pseuकरो checksum */
	sum = csum_fold(csum_add(NAPI_GRO_CB(skb)->csum, wsum));
	/* See comments in __skb_checksum_complete(). */
	अगर (likely(!sum)) अणु
		अगर (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(skb->dev, skb);
	पूर्ण

	NAPI_GRO_CB(skb)->csum = wsum;
	NAPI_GRO_CB(skb)->csum_valid = 1;

	वापस sum;
पूर्ण
EXPORT_SYMBOL(__skb_gro_checksum_complete);

अटल व्योम net_rps_send_ipi(काष्ठा softnet_data *remsd)
अणु
#अगर_घोषित CONFIG_RPS
	जबतक (remsd) अणु
		काष्ठा softnet_data *next = remsd->rps_ipi_next;

		अगर (cpu_online(remsd->cpu))
			smp_call_function_single_async(remsd->cpu, &remsd->csd);
		remsd = next;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * net_rps_action_and_irq_enable sends any pending IPI's क्रम rps.
 * Note: called with local irq disabled, but निकासs with local irq enabled.
 */
अटल व्योम net_rps_action_and_irq_enable(काष्ठा softnet_data *sd)
अणु
#अगर_घोषित CONFIG_RPS
	काष्ठा softnet_data *remsd = sd->rps_ipi_list;

	अगर (remsd) अणु
		sd->rps_ipi_list = शून्य;

		local_irq_enable();

		/* Send pending IPI's to kick RPS processing on remote cpus. */
		net_rps_send_ipi(remsd);
	पूर्ण अन्यथा
#पूर्ण_अगर
		local_irq_enable();
पूर्ण

अटल bool sd_has_rps_ipi_रुकोing(काष्ठा softnet_data *sd)
अणु
#अगर_घोषित CONFIG_RPS
	वापस sd->rps_ipi_list != शून्य;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक process_backlog(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा softnet_data *sd = container_of(napi, काष्ठा softnet_data, backlog);
	bool again = true;
	पूर्णांक work = 0;

	/* Check अगर we have pending ipi, its better to send them now,
	 * not रुकोing net_rx_action() end.
	 */
	अगर (sd_has_rps_ipi_रुकोing(sd)) अणु
		local_irq_disable();
		net_rps_action_and_irq_enable(sd);
	पूर्ण

	napi->weight = dev_rx_weight;
	जबतक (again) अणु
		काष्ठा sk_buff *skb;

		जबतक ((skb = __skb_dequeue(&sd->process_queue))) अणु
			rcu_पढ़ो_lock();
			__netअगर_receive_skb(skb);
			rcu_पढ़ो_unlock();
			input_queue_head_incr(sd);
			अगर (++work >= quota)
				वापस work;

		पूर्ण

		local_irq_disable();
		rps_lock(sd);
		अगर (skb_queue_empty(&sd->input_pkt_queue)) अणु
			/*
			 * Inline a custom version of __napi_complete().
			 * only current cpu owns and manipulates this napi,
			 * and NAPI_STATE_SCHED is the only possible flag set
			 * on backlog.
			 * We can use a plain ग_लिखो instead of clear_bit(),
			 * and we करोnt need an smp_mb() memory barrier.
			 */
			napi->state = 0;
			again = false;
		पूर्ण अन्यथा अणु
			skb_queue_splice_tail_init(&sd->input_pkt_queue,
						   &sd->process_queue);
		पूर्ण
		rps_unlock(sd);
		local_irq_enable();
	पूर्ण

	वापस work;
पूर्ण

/**
 * __napi_schedule - schedule क्रम receive
 * @n: entry to schedule
 *
 * The entry's receive function will be scheduled to run.
 * Consider using __napi_schedule_irqoff() अगर hard irqs are masked.
 */
व्योम __napi_schedule(काष्ठा napi_काष्ठा *n)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	____napi_schedule(this_cpu_ptr(&softnet_data), n);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(__napi_schedule);

/**
 *	napi_schedule_prep - check अगर napi can be scheduled
 *	@n: napi context
 *
 * Test अगर NAPI routine is alपढ़ोy running, and अगर not mark
 * it as running.  This is used as a condition variable to
 * insure only one NAPI poll instance runs.  We also make
 * sure there is no pending NAPI disable.
 */
bool napi_schedule_prep(काष्ठा napi_काष्ठा *n)
अणु
	अचिन्हित दीर्घ val, new;

	करो अणु
		val = READ_ONCE(n->state);
		अगर (unlikely(val & NAPIF_STATE_DISABLE))
			वापस false;
		new = val | NAPIF_STATE_SCHED;

		/* Sets STATE_MISSED bit अगर STATE_SCHED was alपढ़ोy set
		 * This was suggested by Alexander Duyck, as compiler
		 * emits better code than :
		 * अगर (val & NAPIF_STATE_SCHED)
		 *     new |= NAPIF_STATE_MISSED;
		 */
		new |= (val & NAPIF_STATE_SCHED) / NAPIF_STATE_SCHED *
						   NAPIF_STATE_MISSED;
	पूर्ण जबतक (cmpxchg(&n->state, val, new) != val);

	वापस !(val & NAPIF_STATE_SCHED);
पूर्ण
EXPORT_SYMBOL(napi_schedule_prep);

/**
 * __napi_schedule_irqoff - schedule क्रम receive
 * @n: entry to schedule
 *
 * Variant of __napi_schedule() assuming hard irqs are masked
 */
व्योम __napi_schedule_irqoff(काष्ठा napi_काष्ठा *n)
अणु
	____napi_schedule(this_cpu_ptr(&softnet_data), n);
पूर्ण
EXPORT_SYMBOL(__napi_schedule_irqoff);

bool napi_complete_करोne(काष्ठा napi_काष्ठा *n, पूर्णांक work_करोne)
अणु
	अचिन्हित दीर्घ flags, val, new, समयout = 0;
	bool ret = true;

	/*
	 * 1) Don't let napi dequeue from the cpu poll list
	 *    just in हाल its running on a dअगरferent cpu.
	 * 2) If we are busy polling, करो nothing here, we have
	 *    the guarantee we will be called later.
	 */
	अगर (unlikely(n->state & (NAPIF_STATE_NPSVC |
				 NAPIF_STATE_IN_BUSY_POLL)))
		वापस false;

	अगर (work_करोne) अणु
		अगर (n->gro_biपंचांगask)
			समयout = READ_ONCE(n->dev->gro_flush_समयout);
		n->defer_hard_irqs_count = READ_ONCE(n->dev->napi_defer_hard_irqs);
	पूर्ण
	अगर (n->defer_hard_irqs_count > 0) अणु
		n->defer_hard_irqs_count--;
		समयout = READ_ONCE(n->dev->gro_flush_समयout);
		अगर (समयout)
			ret = false;
	पूर्ण
	अगर (n->gro_biपंचांगask) अणु
		/* When the NAPI instance uses a समयout and keeps postponing
		 * it, we need to bound somehow the समय packets are kept in
		 * the GRO layer
		 */
		napi_gro_flush(n, !!समयout);
	पूर्ण

	gro_normal_list(n);

	अगर (unlikely(!list_empty(&n->poll_list))) अणु
		/* If n->poll_list is not empty, we need to mask irqs */
		local_irq_save(flags);
		list_del_init(&n->poll_list);
		local_irq_restore(flags);
	पूर्ण

	करो अणु
		val = READ_ONCE(n->state);

		WARN_ON_ONCE(!(val & NAPIF_STATE_SCHED));

		new = val & ~(NAPIF_STATE_MISSED | NAPIF_STATE_SCHED |
			      NAPIF_STATE_SCHED_THREADED |
			      NAPIF_STATE_PREFER_BUSY_POLL);

		/* If STATE_MISSED was set, leave STATE_SCHED set,
		 * because we will call napi->poll() one more समय.
		 * This C code was suggested by Alexander Duyck to help gcc.
		 */
		new |= (val & NAPIF_STATE_MISSED) / NAPIF_STATE_MISSED *
						    NAPIF_STATE_SCHED;
	पूर्ण जबतक (cmpxchg(&n->state, val, new) != val);

	अगर (unlikely(val & NAPIF_STATE_MISSED)) अणु
		__napi_schedule(n);
		वापस false;
	पूर्ण

	अगर (समयout)
		hrसमयr_start(&n->समयr, ns_to_kसमय(समयout),
			      HRTIMER_MODE_REL_PINNED);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(napi_complete_करोne);

/* must be called under rcu_पढ़ो_lock(), as we करोnt take a reference */
अटल काष्ठा napi_काष्ठा *napi_by_id(अचिन्हित पूर्णांक napi_id)
अणु
	अचिन्हित पूर्णांक hash = napi_id % HASH_SIZE(napi_hash);
	काष्ठा napi_काष्ठा *napi;

	hlist_क्रम_each_entry_rcu(napi, &napi_hash[hash], napi_hash_node)
		अगर (napi->napi_id == napi_id)
			वापस napi;

	वापस शून्य;
पूर्ण

#अगर defined(CONFIG_NET_RX_BUSY_POLL)

अटल व्योम __busy_poll_stop(काष्ठा napi_काष्ठा *napi, bool skip_schedule)
अणु
	अगर (!skip_schedule) अणु
		gro_normal_list(napi);
		__napi_schedule(napi);
		वापस;
	पूर्ण

	अगर (napi->gro_biपंचांगask) अणु
		/* flush too old packets
		 * If HZ < 1000, flush all packets.
		 */
		napi_gro_flush(napi, HZ >= 1000);
	पूर्ण

	gro_normal_list(napi);
	clear_bit(NAPI_STATE_SCHED, &napi->state);
पूर्ण

अटल व्योम busy_poll_stop(काष्ठा napi_काष्ठा *napi, व्योम *have_poll_lock, bool prefer_busy_poll,
			   u16 budget)
अणु
	bool skip_schedule = false;
	अचिन्हित दीर्घ समयout;
	पूर्णांक rc;

	/* Busy polling means there is a high chance device driver hard irq
	 * could not grab NAPI_STATE_SCHED, and that NAPI_STATE_MISSED was
	 * set in napi_schedule_prep().
	 * Since we are about to call napi->poll() once more, we can safely
	 * clear NAPI_STATE_MISSED.
	 *
	 * Note: x86 could use a single "lock and ..." inकाष्ठाion
	 * to perक्रमm these two clear_bit()
	 */
	clear_bit(NAPI_STATE_MISSED, &napi->state);
	clear_bit(NAPI_STATE_IN_BUSY_POLL, &napi->state);

	local_bh_disable();

	अगर (prefer_busy_poll) अणु
		napi->defer_hard_irqs_count = READ_ONCE(napi->dev->napi_defer_hard_irqs);
		समयout = READ_ONCE(napi->dev->gro_flush_समयout);
		अगर (napi->defer_hard_irqs_count && समयout) अणु
			hrसमयr_start(&napi->समयr, ns_to_kसमय(समयout), HRTIMER_MODE_REL_PINNED);
			skip_schedule = true;
		पूर्ण
	पूर्ण

	/* All we really want here is to re-enable device पूर्णांकerrupts.
	 * Ideally, a new nकरो_busy_poll_stop() could aव्योम another round.
	 */
	rc = napi->poll(napi, budget);
	/* We can't gro_normal_list() here, because napi->poll() might have
	 * rearmed the napi (napi_complete_करोne()) in which हाल it could
	 * alपढ़ोy be running on another CPU.
	 */
	trace_napi_poll(napi, rc, budget);
	netpoll_poll_unlock(have_poll_lock);
	अगर (rc == budget)
		__busy_poll_stop(napi, skip_schedule);
	local_bh_enable();
पूर्ण

व्योम napi_busy_loop(अचिन्हित पूर्णांक napi_id,
		    bool (*loop_end)(व्योम *, अचिन्हित दीर्घ),
		    व्योम *loop_end_arg, bool prefer_busy_poll, u16 budget)
अणु
	अचिन्हित दीर्घ start_समय = loop_end ? busy_loop_current_समय() : 0;
	पूर्णांक (*napi_poll)(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
	व्योम *have_poll_lock = शून्य;
	काष्ठा napi_काष्ठा *napi;

restart:
	napi_poll = शून्य;

	rcu_पढ़ो_lock();

	napi = napi_by_id(napi_id);
	अगर (!napi)
		जाओ out;

	preempt_disable();
	क्रम (;;) अणु
		पूर्णांक work = 0;

		local_bh_disable();
		अगर (!napi_poll) अणु
			अचिन्हित दीर्घ val = READ_ONCE(napi->state);

			/* If multiple thपढ़ोs are competing क्रम this napi,
			 * we aव्योम dirtying napi->state as much as we can.
			 */
			अगर (val & (NAPIF_STATE_DISABLE | NAPIF_STATE_SCHED |
				   NAPIF_STATE_IN_BUSY_POLL)) अणु
				अगर (prefer_busy_poll)
					set_bit(NAPI_STATE_PREFER_BUSY_POLL, &napi->state);
				जाओ count;
			पूर्ण
			अगर (cmpxchg(&napi->state, val,
				    val | NAPIF_STATE_IN_BUSY_POLL |
					  NAPIF_STATE_SCHED) != val) अणु
				अगर (prefer_busy_poll)
					set_bit(NAPI_STATE_PREFER_BUSY_POLL, &napi->state);
				जाओ count;
			पूर्ण
			have_poll_lock = netpoll_poll_lock(napi);
			napi_poll = napi->poll;
		पूर्ण
		work = napi_poll(napi, budget);
		trace_napi_poll(napi, work, budget);
		gro_normal_list(napi);
count:
		अगर (work > 0)
			__NET_ADD_STATS(dev_net(napi->dev),
					LINUX_MIB_BUSYPOLLRXPACKETS, work);
		local_bh_enable();

		अगर (!loop_end || loop_end(loop_end_arg, start_समय))
			अवरोध;

		अगर (unlikely(need_resched())) अणु
			अगर (napi_poll)
				busy_poll_stop(napi, have_poll_lock, prefer_busy_poll, budget);
			preempt_enable();
			rcu_पढ़ो_unlock();
			cond_resched();
			अगर (loop_end(loop_end_arg, start_समय))
				वापस;
			जाओ restart;
		पूर्ण
		cpu_relax();
	पूर्ण
	अगर (napi_poll)
		busy_poll_stop(napi, have_poll_lock, prefer_busy_poll, budget);
	preempt_enable();
out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(napi_busy_loop);

#पूर्ण_अगर /* CONFIG_NET_RX_BUSY_POLL */

अटल व्योम napi_hash_add(काष्ठा napi_काष्ठा *napi)
अणु
	अगर (test_bit(NAPI_STATE_NO_BUSY_POLL, &napi->state))
		वापस;

	spin_lock(&napi_hash_lock);

	/* 0..NR_CPUS range is reserved क्रम sender_cpu use */
	करो अणु
		अगर (unlikely(++napi_gen_id < MIN_NAPI_ID))
			napi_gen_id = MIN_NAPI_ID;
	पूर्ण जबतक (napi_by_id(napi_gen_id));
	napi->napi_id = napi_gen_id;

	hlist_add_head_rcu(&napi->napi_hash_node,
			   &napi_hash[napi->napi_id % HASH_SIZE(napi_hash)]);

	spin_unlock(&napi_hash_lock);
पूर्ण

/* Warning : caller is responsible to make sure rcu grace period
 * is respected beक्रमe मुक्तing memory containing @napi
 */
अटल व्योम napi_hash_del(काष्ठा napi_काष्ठा *napi)
अणु
	spin_lock(&napi_hash_lock);

	hlist_del_init_rcu(&napi->napi_hash_node);

	spin_unlock(&napi_hash_lock);
पूर्ण

अटल क्रमागत hrसमयr_restart napi_watchकरोg(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा napi_काष्ठा *napi;

	napi = container_of(समयr, काष्ठा napi_काष्ठा, समयr);

	/* Note : we use a relaxed variant of napi_schedule_prep() not setting
	 * NAPI_STATE_MISSED, since we करो not react to a device IRQ.
	 */
	अगर (!napi_disable_pending(napi) &&
	    !test_and_set_bit(NAPI_STATE_SCHED, &napi->state)) अणु
		clear_bit(NAPI_STATE_PREFER_BUSY_POLL, &napi->state);
		__napi_schedule_irqoff(napi);
	पूर्ण

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम init_gro_hash(काष्ठा napi_काष्ठा *napi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < GRO_HASH_BUCKETS; i++) अणु
		INIT_LIST_HEAD(&napi->gro_hash[i].list);
		napi->gro_hash[i].count = 0;
	पूर्ण
	napi->gro_biपंचांगask = 0;
पूर्ण

पूर्णांक dev_set_thपढ़ोed(काष्ठा net_device *dev, bool thपढ़ोed)
अणु
	काष्ठा napi_काष्ठा *napi;
	पूर्णांक err = 0;

	अगर (dev->thपढ़ोed == thपढ़ोed)
		वापस 0;

	अगर (thपढ़ोed) अणु
		list_क्रम_each_entry(napi, &dev->napi_list, dev_list) अणु
			अगर (!napi->thपढ़ो) अणु
				err = napi_kthपढ़ो_create(napi);
				अगर (err) अणु
					thपढ़ोed = false;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	dev->thपढ़ोed = thपढ़ोed;

	/* Make sure kthपढ़ो is created beक्रमe THREADED bit
	 * is set.
	 */
	smp_mb__beक्रमe_atomic();

	/* Setting/unsetting thपढ़ोed mode on a napi might not immediately
	 * take effect, अगर the current napi instance is actively being
	 * polled. In this हाल, the चयन between thपढ़ोed mode and
	 * softirq mode will happen in the next round of napi_schedule().
	 * This should not cause hiccups/stalls to the live traffic.
	 */
	list_क्रम_each_entry(napi, &dev->napi_list, dev_list) अणु
		अगर (thपढ़ोed)
			set_bit(NAPI_STATE_THREADED, &napi->state);
		अन्यथा
			clear_bit(NAPI_STATE_THREADED, &napi->state);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_set_thपढ़ोed);

व्योम netअगर_napi_add(काष्ठा net_device *dev, काष्ठा napi_काष्ठा *napi,
		    पूर्णांक (*poll)(काष्ठा napi_काष्ठा *, पूर्णांक), पूर्णांक weight)
अणु
	अगर (WARN_ON(test_and_set_bit(NAPI_STATE_LISTED, &napi->state)))
		वापस;

	INIT_LIST_HEAD(&napi->poll_list);
	INIT_HLIST_NODE(&napi->napi_hash_node);
	hrसमयr_init(&napi->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_PINNED);
	napi->समयr.function = napi_watchकरोg;
	init_gro_hash(napi);
	napi->skb = शून्य;
	INIT_LIST_HEAD(&napi->rx_list);
	napi->rx_count = 0;
	napi->poll = poll;
	अगर (weight > NAPI_POLL_WEIGHT)
		netdev_err_once(dev, "%s() called with weight %d\n", __func__,
				weight);
	napi->weight = weight;
	napi->dev = dev;
#अगर_घोषित CONFIG_NETPOLL
	napi->poll_owner = -1;
#पूर्ण_अगर
	set_bit(NAPI_STATE_SCHED, &napi->state);
	set_bit(NAPI_STATE_NPSVC, &napi->state);
	list_add_rcu(&napi->dev_list, &dev->napi_list);
	napi_hash_add(napi);
	/* Create kthपढ़ो क्रम this napi अगर dev->thपढ़ोed is set.
	 * Clear dev->thपढ़ोed अगर kthपढ़ो creation failed so that
	 * thपढ़ोed mode will not be enabled in napi_enable().
	 */
	अगर (dev->thपढ़ोed && napi_kthपढ़ो_create(napi))
		dev->thपढ़ोed = 0;
पूर्ण
EXPORT_SYMBOL(netअगर_napi_add);

व्योम napi_disable(काष्ठा napi_काष्ठा *n)
अणु
	might_sleep();
	set_bit(NAPI_STATE_DISABLE, &n->state);

	जबतक (test_and_set_bit(NAPI_STATE_SCHED, &n->state))
		msleep(1);
	जबतक (test_and_set_bit(NAPI_STATE_NPSVC, &n->state))
		msleep(1);

	hrसमयr_cancel(&n->समयr);

	clear_bit(NAPI_STATE_PREFER_BUSY_POLL, &n->state);
	clear_bit(NAPI_STATE_DISABLE, &n->state);
	clear_bit(NAPI_STATE_THREADED, &n->state);
पूर्ण
EXPORT_SYMBOL(napi_disable);

/**
 *	napi_enable - enable NAPI scheduling
 *	@n: NAPI context
 *
 * Resume NAPI from being scheduled on this context.
 * Must be paired with napi_disable.
 */
व्योम napi_enable(काष्ठा napi_काष्ठा *n)
अणु
	BUG_ON(!test_bit(NAPI_STATE_SCHED, &n->state));
	smp_mb__beक्रमe_atomic();
	clear_bit(NAPI_STATE_SCHED, &n->state);
	clear_bit(NAPI_STATE_NPSVC, &n->state);
	अगर (n->dev->thपढ़ोed && n->thपढ़ो)
		set_bit(NAPI_STATE_THREADED, &n->state);
पूर्ण
EXPORT_SYMBOL(napi_enable);

अटल व्योम flush_gro_hash(काष्ठा napi_काष्ठा *napi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < GRO_HASH_BUCKETS; i++) अणु
		काष्ठा sk_buff *skb, *n;

		list_क्रम_each_entry_safe(skb, n, &napi->gro_hash[i].list, list)
			kमुक्त_skb(skb);
		napi->gro_hash[i].count = 0;
	पूर्ण
पूर्ण

/* Must be called in process context */
व्योम __netअगर_napi_del(काष्ठा napi_काष्ठा *napi)
अणु
	अगर (!test_and_clear_bit(NAPI_STATE_LISTED, &napi->state))
		वापस;

	napi_hash_del(napi);
	list_del_rcu(&napi->dev_list);
	napi_मुक्त_frags(napi);

	flush_gro_hash(napi);
	napi->gro_biपंचांगask = 0;

	अगर (napi->thपढ़ो) अणु
		kthपढ़ो_stop(napi->thपढ़ो);
		napi->thपढ़ो = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__netअगर_napi_del);

अटल पूर्णांक __napi_poll(काष्ठा napi_काष्ठा *n, bool *repoll)
अणु
	पूर्णांक work, weight;

	weight = n->weight;

	/* This NAPI_STATE_SCHED test is क्रम aव्योमing a race
	 * with netpoll's poll_napi().  Only the entity which
	 * obtains the lock and sees NAPI_STATE_SCHED set will
	 * actually make the ->poll() call.  Thereक्रमe we aव्योम
	 * accidentally calling ->poll() when NAPI is not scheduled.
	 */
	work = 0;
	अगर (test_bit(NAPI_STATE_SCHED, &n->state)) अणु
		work = n->poll(n, weight);
		trace_napi_poll(n, work, weight);
	पूर्ण

	अगर (unlikely(work > weight))
		pr_err_once("NAPI poll function %pS returned %d, exceeding its budget of %d.\n",
			    n->poll, work, weight);

	अगर (likely(work < weight))
		वापस work;

	/* Drivers must not modअगरy the NAPI state अगर they
	 * consume the entire weight.  In such हालs this code
	 * still "owns" the NAPI instance and thereक्रमe can
	 * move the instance around on the list at-will.
	 */
	अगर (unlikely(napi_disable_pending(n))) अणु
		napi_complete(n);
		वापस work;
	पूर्ण

	/* The NAPI context has more processing work, but busy-polling
	 * is preferred. Exit early.
	 */
	अगर (napi_prefer_busy_poll(n)) अणु
		अगर (napi_complete_करोne(n, work)) अणु
			/* If समयout is not set, we need to make sure
			 * that the NAPI is re-scheduled.
			 */
			napi_schedule(n);
		पूर्ण
		वापस work;
	पूर्ण

	अगर (n->gro_biपंचांगask) अणु
		/* flush too old packets
		 * If HZ < 1000, flush all packets.
		 */
		napi_gro_flush(n, HZ >= 1000);
	पूर्ण

	gro_normal_list(n);

	/* Some drivers may have called napi_schedule
	 * prior to exhausting their budget.
	 */
	अगर (unlikely(!list_empty(&n->poll_list))) अणु
		pr_warn_once("%s: Budget exhausted after napi rescheduled\n",
			     n->dev ? n->dev->name : "backlog");
		वापस work;
	पूर्ण

	*repoll = true;

	वापस work;
पूर्ण

अटल पूर्णांक napi_poll(काष्ठा napi_काष्ठा *n, काष्ठा list_head *repoll)
अणु
	bool करो_repoll = false;
	व्योम *have;
	पूर्णांक work;

	list_del_init(&n->poll_list);

	have = netpoll_poll_lock(n);

	work = __napi_poll(n, &करो_repoll);

	अगर (करो_repoll)
		list_add_tail(&n->poll_list, repoll);

	netpoll_poll_unlock(have);

	वापस work;
पूर्ण

अटल पूर्णांक napi_thपढ़ो_रुको(काष्ठा napi_काष्ठा *napi)
अणु
	bool woken = false;

	set_current_state(TASK_INTERRUPTIBLE);

	जबतक (!kthपढ़ो_should_stop()) अणु
		/* Testing SCHED_THREADED bit here to make sure the current
		 * kthपढ़ो owns this napi and could poll on this napi.
		 * Testing SCHED bit is not enough because SCHED bit might be
		 * set by some other busy poll thपढ़ो or by napi_disable().
		 */
		अगर (test_bit(NAPI_STATE_SCHED_THREADED, &napi->state) || woken) अणु
			WARN_ON(!list_empty(&napi->poll_list));
			__set_current_state(TASK_RUNNING);
			वापस 0;
		पूर्ण

		schedule();
		/* woken being true indicates this thपढ़ो owns this napi. */
		woken = true;
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण
	__set_current_state(TASK_RUNNING);

	वापस -1;
पूर्ण

अटल पूर्णांक napi_thपढ़ोed_poll(व्योम *data)
अणु
	काष्ठा napi_काष्ठा *napi = data;
	व्योम *have;

	जबतक (!napi_thपढ़ो_रुको(napi)) अणु
		क्रम (;;) अणु
			bool repoll = false;

			local_bh_disable();

			have = netpoll_poll_lock(napi);
			__napi_poll(napi, &repoll);
			netpoll_poll_unlock(have);

			local_bh_enable();

			अगर (!repoll)
				अवरोध;

			cond_resched();
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल __latent_entropy व्योम net_rx_action(काष्ठा softirq_action *h)
अणु
	काष्ठा softnet_data *sd = this_cpu_ptr(&softnet_data);
	अचिन्हित दीर्घ समय_limit = jअगरfies +
		usecs_to_jअगरfies(netdev_budget_usecs);
	पूर्णांक budget = netdev_budget;
	LIST_HEAD(list);
	LIST_HEAD(repoll);

	local_irq_disable();
	list_splice_init(&sd->poll_list, &list);
	local_irq_enable();

	क्रम (;;) अणु
		काष्ठा napi_काष्ठा *n;

		अगर (list_empty(&list)) अणु
			अगर (!sd_has_rps_ipi_रुकोing(sd) && list_empty(&repoll))
				वापस;
			अवरोध;
		पूर्ण

		n = list_first_entry(&list, काष्ठा napi_काष्ठा, poll_list);
		budget -= napi_poll(n, &repoll);

		/* If softirq winकरोw is exhausted then punt.
		 * Allow this to run क्रम 2 jअगरfies since which will allow
		 * an average latency of 1.5/HZ.
		 */
		अगर (unlikely(budget <= 0 ||
			     समय_after_eq(jअगरfies, समय_limit))) अणु
			sd->समय_squeeze++;
			अवरोध;
		पूर्ण
	पूर्ण

	local_irq_disable();

	list_splice_tail_init(&sd->poll_list, &list);
	list_splice_tail(&repoll, &list);
	list_splice(&list, &sd->poll_list);
	अगर (!list_empty(&sd->poll_list))
		__उठाओ_softirq_irqoff(NET_RX_SOFTIRQ);

	net_rps_action_and_irq_enable(sd);
पूर्ण

काष्ठा netdev_adjacent अणु
	काष्ठा net_device *dev;

	/* upper master flag, there can only be one master device per list */
	bool master;

	/* lookup ignore flag */
	bool ignore;

	/* counter क्रम the number of बार this device was added to us */
	u16 ref_nr;

	/* निजी field क्रम the users */
	व्योम *निजी;

	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल काष्ठा netdev_adjacent *__netdev_find_adj(काष्ठा net_device *adj_dev,
						 काष्ठा list_head *adj_list)
अणु
	काष्ठा netdev_adjacent *adj;

	list_क्रम_each_entry(adj, adj_list, list) अणु
		अगर (adj->dev == adj_dev)
			वापस adj;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक ____netdev_has_upper_dev(काष्ठा net_device *upper_dev,
				    काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)priv->data;

	वापस upper_dev == dev;
पूर्ण

/**
 * netdev_has_upper_dev - Check अगर device is linked to an upper device
 * @dev: device
 * @upper_dev: upper device to check
 *
 * Find out अगर a device is linked to specअगरied upper device and वापस true
 * in हाल it is. Note that this checks only immediate upper device,
 * not through a complete stack of devices. The caller must hold the RTNL lock.
 */
bool netdev_has_upper_dev(काष्ठा net_device *dev,
			  काष्ठा net_device *upper_dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)upper_dev,
	पूर्ण;

	ASSERT_RTNL();

	वापस netdev_walk_all_upper_dev_rcu(dev, ____netdev_has_upper_dev,
					     &priv);
पूर्ण
EXPORT_SYMBOL(netdev_has_upper_dev);

/**
 * netdev_has_upper_dev_all_rcu - Check अगर device is linked to an upper device
 * @dev: device
 * @upper_dev: upper device to check
 *
 * Find out अगर a device is linked to specअगरied upper device and वापस true
 * in हाल it is. Note that this checks the entire upper device chain.
 * The caller must hold rcu lock.
 */

bool netdev_has_upper_dev_all_rcu(काष्ठा net_device *dev,
				  काष्ठा net_device *upper_dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)upper_dev,
	पूर्ण;

	वापस !!netdev_walk_all_upper_dev_rcu(dev, ____netdev_has_upper_dev,
					       &priv);
पूर्ण
EXPORT_SYMBOL(netdev_has_upper_dev_all_rcu);

/**
 * netdev_has_any_upper_dev - Check अगर device is linked to some device
 * @dev: device
 *
 * Find out अगर a device is linked to an upper device and वापस true in हाल
 * it is. The caller must hold the RTNL lock.
 */
bool netdev_has_any_upper_dev(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();

	वापस !list_empty(&dev->adj_list.upper);
पूर्ण
EXPORT_SYMBOL(netdev_has_any_upper_dev);

/**
 * netdev_master_upper_dev_get - Get master upper device
 * @dev: device
 *
 * Find a master upper device and वापस poपूर्णांकer to it or शून्य in हाल
 * it's not there. The caller must hold the RTNL lock.
 */
काष्ठा net_device *netdev_master_upper_dev_get(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_adjacent *upper;

	ASSERT_RTNL();

	अगर (list_empty(&dev->adj_list.upper))
		वापस शून्य;

	upper = list_first_entry(&dev->adj_list.upper,
				 काष्ठा netdev_adjacent, list);
	अगर (likely(upper->master))
		वापस upper->dev;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(netdev_master_upper_dev_get);

अटल काष्ठा net_device *__netdev_master_upper_dev_get(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_adjacent *upper;

	ASSERT_RTNL();

	अगर (list_empty(&dev->adj_list.upper))
		वापस शून्य;

	upper = list_first_entry(&dev->adj_list.upper,
				 काष्ठा netdev_adjacent, list);
	अगर (likely(upper->master) && !upper->ignore)
		वापस upper->dev;
	वापस शून्य;
पूर्ण

/**
 * netdev_has_any_lower_dev - Check अगर device is linked to some device
 * @dev: device
 *
 * Find out अगर a device is linked to a lower device and वापस true in हाल
 * it is. The caller must hold the RTNL lock.
 */
अटल bool netdev_has_any_lower_dev(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();

	वापस !list_empty(&dev->adj_list.lower);
पूर्ण

व्योम *netdev_adjacent_get_निजी(काष्ठा list_head *adj_list)
अणु
	काष्ठा netdev_adjacent *adj;

	adj = list_entry(adj_list, काष्ठा netdev_adjacent, list);

	वापस adj->निजी;
पूर्ण
EXPORT_SYMBOL(netdev_adjacent_get_निजी);

/**
 * netdev_upper_get_next_dev_rcu - Get the next dev from upper list
 * @dev: device
 * @iter: list_head ** of the current position
 *
 * Gets the next device from the dev's upper list, starting from iter
 * position. The caller must hold RCU पढ़ो lock.
 */
काष्ठा net_device *netdev_upper_get_next_dev_rcu(काष्ठा net_device *dev,
						 काष्ठा list_head **iter)
अणु
	काष्ठा netdev_adjacent *upper;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !lockdep_rtnl_is_held());

	upper = list_entry_rcu((*iter)->next, काष्ठा netdev_adjacent, list);

	अगर (&upper->list == &dev->adj_list.upper)
		वापस शून्य;

	*iter = &upper->list;

	वापस upper->dev;
पूर्ण
EXPORT_SYMBOL(netdev_upper_get_next_dev_rcu);

अटल काष्ठा net_device *__netdev_next_upper_dev(काष्ठा net_device *dev,
						  काष्ठा list_head **iter,
						  bool *ignore)
अणु
	काष्ठा netdev_adjacent *upper;

	upper = list_entry((*iter)->next, काष्ठा netdev_adjacent, list);

	अगर (&upper->list == &dev->adj_list.upper)
		वापस शून्य;

	*iter = &upper->list;
	*ignore = upper->ignore;

	वापस upper->dev;
पूर्ण

अटल काष्ठा net_device *netdev_next_upper_dev_rcu(काष्ठा net_device *dev,
						    काष्ठा list_head **iter)
अणु
	काष्ठा netdev_adjacent *upper;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !lockdep_rtnl_is_held());

	upper = list_entry_rcu((*iter)->next, काष्ठा netdev_adjacent, list);

	अगर (&upper->list == &dev->adj_list.upper)
		वापस शून्य;

	*iter = &upper->list;

	वापस upper->dev;
पूर्ण

अटल पूर्णांक __netdev_walk_all_upper_dev(काष्ठा net_device *dev,
				       पूर्णांक (*fn)(काष्ठा net_device *dev,
					 काष्ठा netdev_nested_priv *priv),
				       काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा net_device *udev, *next, *now, *dev_stack[MAX_NEST_DEV + 1];
	काष्ठा list_head *niter, *iter, *iter_stack[MAX_NEST_DEV + 1];
	पूर्णांक ret, cur = 0;
	bool ignore;

	now = dev;
	iter = &dev->adj_list.upper;

	जबतक (1) अणु
		अगर (now != dev) अणु
			ret = fn(now, priv);
			अगर (ret)
				वापस ret;
		पूर्ण

		next = शून्य;
		जबतक (1) अणु
			udev = __netdev_next_upper_dev(now, &iter, &ignore);
			अगर (!udev)
				अवरोध;
			अगर (ignore)
				जारी;

			next = udev;
			niter = &udev->adj_list.upper;
			dev_stack[cur] = now;
			iter_stack[cur++] = iter;
			अवरोध;
		पूर्ण

		अगर (!next) अणु
			अगर (!cur)
				वापस 0;
			next = dev_stack[--cur];
			niter = iter_stack[cur];
		पूर्ण

		now = next;
		iter = niter;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक netdev_walk_all_upper_dev_rcu(काष्ठा net_device *dev,
				  पूर्णांक (*fn)(काष्ठा net_device *dev,
					    काष्ठा netdev_nested_priv *priv),
				  काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा net_device *udev, *next, *now, *dev_stack[MAX_NEST_DEV + 1];
	काष्ठा list_head *niter, *iter, *iter_stack[MAX_NEST_DEV + 1];
	पूर्णांक ret, cur = 0;

	now = dev;
	iter = &dev->adj_list.upper;

	जबतक (1) अणु
		अगर (now != dev) अणु
			ret = fn(now, priv);
			अगर (ret)
				वापस ret;
		पूर्ण

		next = शून्य;
		जबतक (1) अणु
			udev = netdev_next_upper_dev_rcu(now, &iter);
			अगर (!udev)
				अवरोध;

			next = udev;
			niter = &udev->adj_list.upper;
			dev_stack[cur] = now;
			iter_stack[cur++] = iter;
			अवरोध;
		पूर्ण

		अगर (!next) अणु
			अगर (!cur)
				वापस 0;
			next = dev_stack[--cur];
			niter = iter_stack[cur];
		पूर्ण

		now = next;
		iter = niter;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netdev_walk_all_upper_dev_rcu);

अटल bool __netdev_has_upper_dev(काष्ठा net_device *dev,
				   काष्ठा net_device *upper_dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.flags = 0,
		.data = (व्योम *)upper_dev,
	पूर्ण;

	ASSERT_RTNL();

	वापस __netdev_walk_all_upper_dev(dev, ____netdev_has_upper_dev,
					   &priv);
पूर्ण

/**
 * netdev_lower_get_next_निजी - Get the next ->निजी from the
 *				   lower neighbour list
 * @dev: device
 * @iter: list_head ** of the current position
 *
 * Gets the next netdev_adjacent->निजी from the dev's lower neighbour
 * list, starting from iter position. The caller must hold either hold the
 * RTNL lock or its own locking that guarantees that the neighbour lower
 * list will reमुख्य unchanged.
 */
व्योम *netdev_lower_get_next_निजी(काष्ठा net_device *dev,
				    काष्ठा list_head **iter)
अणु
	काष्ठा netdev_adjacent *lower;

	lower = list_entry(*iter, काष्ठा netdev_adjacent, list);

	अगर (&lower->list == &dev->adj_list.lower)
		वापस शून्य;

	*iter = lower->list.next;

	वापस lower->निजी;
पूर्ण
EXPORT_SYMBOL(netdev_lower_get_next_निजी);

/**
 * netdev_lower_get_next_निजी_rcu - Get the next ->निजी from the
 *				       lower neighbour list, RCU
 *				       variant
 * @dev: device
 * @iter: list_head ** of the current position
 *
 * Gets the next netdev_adjacent->निजी from the dev's lower neighbour
 * list, starting from iter position. The caller must hold RCU पढ़ो lock.
 */
व्योम *netdev_lower_get_next_निजी_rcu(काष्ठा net_device *dev,
					काष्ठा list_head **iter)
अणु
	काष्ठा netdev_adjacent *lower;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	lower = list_entry_rcu((*iter)->next, काष्ठा netdev_adjacent, list);

	अगर (&lower->list == &dev->adj_list.lower)
		वापस शून्य;

	*iter = &lower->list;

	वापस lower->निजी;
पूर्ण
EXPORT_SYMBOL(netdev_lower_get_next_निजी_rcu);

/**
 * netdev_lower_get_next - Get the next device from the lower neighbour
 *                         list
 * @dev: device
 * @iter: list_head ** of the current position
 *
 * Gets the next netdev_adjacent from the dev's lower neighbour
 * list, starting from iter position. The caller must hold RTNL lock or
 * its own locking that guarantees that the neighbour lower
 * list will reमुख्य unchanged.
 */
व्योम *netdev_lower_get_next(काष्ठा net_device *dev, काष्ठा list_head **iter)
अणु
	काष्ठा netdev_adjacent *lower;

	lower = list_entry(*iter, काष्ठा netdev_adjacent, list);

	अगर (&lower->list == &dev->adj_list.lower)
		वापस शून्य;

	*iter = lower->list.next;

	वापस lower->dev;
पूर्ण
EXPORT_SYMBOL(netdev_lower_get_next);

अटल काष्ठा net_device *netdev_next_lower_dev(काष्ठा net_device *dev,
						काष्ठा list_head **iter)
अणु
	काष्ठा netdev_adjacent *lower;

	lower = list_entry((*iter)->next, काष्ठा netdev_adjacent, list);

	अगर (&lower->list == &dev->adj_list.lower)
		वापस शून्य;

	*iter = &lower->list;

	वापस lower->dev;
पूर्ण

अटल काष्ठा net_device *__netdev_next_lower_dev(काष्ठा net_device *dev,
						  काष्ठा list_head **iter,
						  bool *ignore)
अणु
	काष्ठा netdev_adjacent *lower;

	lower = list_entry((*iter)->next, काष्ठा netdev_adjacent, list);

	अगर (&lower->list == &dev->adj_list.lower)
		वापस शून्य;

	*iter = &lower->list;
	*ignore = lower->ignore;

	वापस lower->dev;
पूर्ण

पूर्णांक netdev_walk_all_lower_dev(काष्ठा net_device *dev,
			      पूर्णांक (*fn)(काष्ठा net_device *dev,
					काष्ठा netdev_nested_priv *priv),
			      काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा net_device *ldev, *next, *now, *dev_stack[MAX_NEST_DEV + 1];
	काष्ठा list_head *niter, *iter, *iter_stack[MAX_NEST_DEV + 1];
	पूर्णांक ret, cur = 0;

	now = dev;
	iter = &dev->adj_list.lower;

	जबतक (1) अणु
		अगर (now != dev) अणु
			ret = fn(now, priv);
			अगर (ret)
				वापस ret;
		पूर्ण

		next = शून्य;
		जबतक (1) अणु
			ldev = netdev_next_lower_dev(now, &iter);
			अगर (!ldev)
				अवरोध;

			next = ldev;
			niter = &ldev->adj_list.lower;
			dev_stack[cur] = now;
			iter_stack[cur++] = iter;
			अवरोध;
		पूर्ण

		अगर (!next) अणु
			अगर (!cur)
				वापस 0;
			next = dev_stack[--cur];
			niter = iter_stack[cur];
		पूर्ण

		now = next;
		iter = niter;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netdev_walk_all_lower_dev);

अटल पूर्णांक __netdev_walk_all_lower_dev(काष्ठा net_device *dev,
				       पूर्णांक (*fn)(काष्ठा net_device *dev,
					 काष्ठा netdev_nested_priv *priv),
				       काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा net_device *ldev, *next, *now, *dev_stack[MAX_NEST_DEV + 1];
	काष्ठा list_head *niter, *iter, *iter_stack[MAX_NEST_DEV + 1];
	पूर्णांक ret, cur = 0;
	bool ignore;

	now = dev;
	iter = &dev->adj_list.lower;

	जबतक (1) अणु
		अगर (now != dev) अणु
			ret = fn(now, priv);
			अगर (ret)
				वापस ret;
		पूर्ण

		next = शून्य;
		जबतक (1) अणु
			ldev = __netdev_next_lower_dev(now, &iter, &ignore);
			अगर (!ldev)
				अवरोध;
			अगर (ignore)
				जारी;

			next = ldev;
			niter = &ldev->adj_list.lower;
			dev_stack[cur] = now;
			iter_stack[cur++] = iter;
			अवरोध;
		पूर्ण

		अगर (!next) अणु
			अगर (!cur)
				वापस 0;
			next = dev_stack[--cur];
			niter = iter_stack[cur];
		पूर्ण

		now = next;
		iter = niter;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा net_device *netdev_next_lower_dev_rcu(काष्ठा net_device *dev,
					     काष्ठा list_head **iter)
अणु
	काष्ठा netdev_adjacent *lower;

	lower = list_entry_rcu((*iter)->next, काष्ठा netdev_adjacent, list);
	अगर (&lower->list == &dev->adj_list.lower)
		वापस शून्य;

	*iter = &lower->list;

	वापस lower->dev;
पूर्ण
EXPORT_SYMBOL(netdev_next_lower_dev_rcu);

अटल u8 __netdev_upper_depth(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *udev;
	काष्ठा list_head *iter;
	u8 max_depth = 0;
	bool ignore;

	क्रम (iter = &dev->adj_list.upper,
	     udev = __netdev_next_upper_dev(dev, &iter, &ignore);
	     udev;
	     udev = __netdev_next_upper_dev(dev, &iter, &ignore)) अणु
		अगर (ignore)
			जारी;
		अगर (max_depth < udev->upper_level)
			max_depth = udev->upper_level;
	पूर्ण

	वापस max_depth;
पूर्ण

अटल u8 __netdev_lower_depth(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *ldev;
	काष्ठा list_head *iter;
	u8 max_depth = 0;
	bool ignore;

	क्रम (iter = &dev->adj_list.lower,
	     ldev = __netdev_next_lower_dev(dev, &iter, &ignore);
	     ldev;
	     ldev = __netdev_next_lower_dev(dev, &iter, &ignore)) अणु
		अगर (ignore)
			जारी;
		अगर (max_depth < ldev->lower_level)
			max_depth = ldev->lower_level;
	पूर्ण

	वापस max_depth;
पूर्ण

अटल पूर्णांक __netdev_update_upper_level(काष्ठा net_device *dev,
				       काष्ठा netdev_nested_priv *__unused)
अणु
	dev->upper_level = __netdev_upper_depth(dev) + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __netdev_update_lower_level(काष्ठा net_device *dev,
				       काष्ठा netdev_nested_priv *priv)
अणु
	dev->lower_level = __netdev_lower_depth(dev) + 1;

#अगर_घोषित CONFIG_LOCKDEP
	अगर (!priv)
		वापस 0;

	अगर (priv->flags & NESTED_SYNC_IMM)
		dev->nested_level = dev->lower_level - 1;
	अगर (priv->flags & NESTED_SYNC_TODO)
		net_unlink_toकरो(dev);
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक netdev_walk_all_lower_dev_rcu(काष्ठा net_device *dev,
				  पूर्णांक (*fn)(काष्ठा net_device *dev,
					    काष्ठा netdev_nested_priv *priv),
				  काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा net_device *ldev, *next, *now, *dev_stack[MAX_NEST_DEV + 1];
	काष्ठा list_head *niter, *iter, *iter_stack[MAX_NEST_DEV + 1];
	पूर्णांक ret, cur = 0;

	now = dev;
	iter = &dev->adj_list.lower;

	जबतक (1) अणु
		अगर (now != dev) अणु
			ret = fn(now, priv);
			अगर (ret)
				वापस ret;
		पूर्ण

		next = शून्य;
		जबतक (1) अणु
			ldev = netdev_next_lower_dev_rcu(now, &iter);
			अगर (!ldev)
				अवरोध;

			next = ldev;
			niter = &ldev->adj_list.lower;
			dev_stack[cur] = now;
			iter_stack[cur++] = iter;
			अवरोध;
		पूर्ण

		अगर (!next) अणु
			अगर (!cur)
				वापस 0;
			next = dev_stack[--cur];
			niter = iter_stack[cur];
		पूर्ण

		now = next;
		iter = niter;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netdev_walk_all_lower_dev_rcu);

/**
 * netdev_lower_get_first_निजी_rcu - Get the first ->निजी from the
 *				       lower neighbour list, RCU
 *				       variant
 * @dev: device
 *
 * Gets the first netdev_adjacent->निजी from the dev's lower neighbour
 * list. The caller must hold RCU पढ़ो lock.
 */
व्योम *netdev_lower_get_first_निजी_rcu(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_adjacent *lower;

	lower = list_first_or_null_rcu(&dev->adj_list.lower,
			काष्ठा netdev_adjacent, list);
	अगर (lower)
		वापस lower->निजी;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(netdev_lower_get_first_निजी_rcu);

/**
 * netdev_master_upper_dev_get_rcu - Get master upper device
 * @dev: device
 *
 * Find a master upper device and वापस poपूर्णांकer to it or शून्य in हाल
 * it's not there. The caller must hold the RCU पढ़ो lock.
 */
काष्ठा net_device *netdev_master_upper_dev_get_rcu(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_adjacent *upper;

	upper = list_first_or_null_rcu(&dev->adj_list.upper,
				       काष्ठा netdev_adjacent, list);
	अगर (upper && likely(upper->master))
		वापस upper->dev;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(netdev_master_upper_dev_get_rcu);

अटल पूर्णांक netdev_adjacent_sysfs_add(काष्ठा net_device *dev,
			      काष्ठा net_device *adj_dev,
			      काष्ठा list_head *dev_list)
अणु
	अक्षर linkname[IFNAMSIZ+7];

	प्र_लिखो(linkname, dev_list == &dev->adj_list.upper ?
		"upper_%s" : "lower_%s", adj_dev->name);
	वापस sysfs_create_link(&(dev->dev.kobj), &(adj_dev->dev.kobj),
				 linkname);
पूर्ण
अटल व्योम netdev_adjacent_sysfs_del(काष्ठा net_device *dev,
			       अक्षर *name,
			       काष्ठा list_head *dev_list)
अणु
	अक्षर linkname[IFNAMSIZ+7];

	प्र_लिखो(linkname, dev_list == &dev->adj_list.upper ?
		"upper_%s" : "lower_%s", name);
	sysfs_हटाओ_link(&(dev->dev.kobj), linkname);
पूर्ण

अटल अंतरभूत bool netdev_adjacent_is_neigh_list(काष्ठा net_device *dev,
						 काष्ठा net_device *adj_dev,
						 काष्ठा list_head *dev_list)
अणु
	वापस (dev_list == &dev->adj_list.upper ||
		dev_list == &dev->adj_list.lower) &&
		net_eq(dev_net(dev), dev_net(adj_dev));
पूर्ण

अटल पूर्णांक __netdev_adjacent_dev_insert(काष्ठा net_device *dev,
					काष्ठा net_device *adj_dev,
					काष्ठा list_head *dev_list,
					व्योम *निजी, bool master)
अणु
	काष्ठा netdev_adjacent *adj;
	पूर्णांक ret;

	adj = __netdev_find_adj(adj_dev, dev_list);

	अगर (adj) अणु
		adj->ref_nr += 1;
		pr_debug("Insert adjacency: dev %s adj_dev %s adj->ref_nr %d\n",
			 dev->name, adj_dev->name, adj->ref_nr);

		वापस 0;
	पूर्ण

	adj = kदो_स्मृति(माप(*adj), GFP_KERNEL);
	अगर (!adj)
		वापस -ENOMEM;

	adj->dev = adj_dev;
	adj->master = master;
	adj->ref_nr = 1;
	adj->निजी = निजी;
	adj->ignore = false;
	dev_hold(adj_dev);

	pr_debug("Insert adjacency: dev %s adj_dev %s adj->ref_nr %d; dev_hold on %s\n",
		 dev->name, adj_dev->name, adj->ref_nr, adj_dev->name);

	अगर (netdev_adjacent_is_neigh_list(dev, adj_dev, dev_list)) अणु
		ret = netdev_adjacent_sysfs_add(dev, adj_dev, dev_list);
		अगर (ret)
			जाओ मुक्त_adj;
	पूर्ण

	/* Ensure that master link is always the first item in list. */
	अगर (master) अणु
		ret = sysfs_create_link(&(dev->dev.kobj),
					&(adj_dev->dev.kobj), "master");
		अगर (ret)
			जाओ हटाओ_symlinks;

		list_add_rcu(&adj->list, dev_list);
	पूर्ण अन्यथा अणु
		list_add_tail_rcu(&adj->list, dev_list);
	पूर्ण

	वापस 0;

हटाओ_symlinks:
	अगर (netdev_adjacent_is_neigh_list(dev, adj_dev, dev_list))
		netdev_adjacent_sysfs_del(dev, adj_dev->name, dev_list);
मुक्त_adj:
	kमुक्त(adj);
	dev_put(adj_dev);

	वापस ret;
पूर्ण

अटल व्योम __netdev_adjacent_dev_हटाओ(काष्ठा net_device *dev,
					 काष्ठा net_device *adj_dev,
					 u16 ref_nr,
					 काष्ठा list_head *dev_list)
अणु
	काष्ठा netdev_adjacent *adj;

	pr_debug("Remove adjacency: dev %s adj_dev %s ref_nr %d\n",
		 dev->name, adj_dev->name, ref_nr);

	adj = __netdev_find_adj(adj_dev, dev_list);

	अगर (!adj) अणु
		pr_err("Adjacency does not exist for device %s from %s\n",
		       dev->name, adj_dev->name);
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (adj->ref_nr > ref_nr) अणु
		pr_debug("adjacency: %s to %s ref_nr - %d = %d\n",
			 dev->name, adj_dev->name, ref_nr,
			 adj->ref_nr - ref_nr);
		adj->ref_nr -= ref_nr;
		वापस;
	पूर्ण

	अगर (adj->master)
		sysfs_हटाओ_link(&(dev->dev.kobj), "master");

	अगर (netdev_adjacent_is_neigh_list(dev, adj_dev, dev_list))
		netdev_adjacent_sysfs_del(dev, adj_dev->name, dev_list);

	list_del_rcu(&adj->list);
	pr_debug("adjacency: dev_put for %s, because link removed from %s to %s\n",
		 adj_dev->name, dev->name, adj_dev->name);
	dev_put(adj_dev);
	kमुक्त_rcu(adj, rcu);
पूर्ण

अटल पूर्णांक __netdev_adjacent_dev_link_lists(काष्ठा net_device *dev,
					    काष्ठा net_device *upper_dev,
					    काष्ठा list_head *up_list,
					    काष्ठा list_head *करोwn_list,
					    व्योम *निजी, bool master)
अणु
	पूर्णांक ret;

	ret = __netdev_adjacent_dev_insert(dev, upper_dev, up_list,
					   निजी, master);
	अगर (ret)
		वापस ret;

	ret = __netdev_adjacent_dev_insert(upper_dev, dev, करोwn_list,
					   निजी, false);
	अगर (ret) अणु
		__netdev_adjacent_dev_हटाओ(dev, upper_dev, 1, up_list);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __netdev_adjacent_dev_unlink_lists(काष्ठा net_device *dev,
					       काष्ठा net_device *upper_dev,
					       u16 ref_nr,
					       काष्ठा list_head *up_list,
					       काष्ठा list_head *करोwn_list)
अणु
	__netdev_adjacent_dev_हटाओ(dev, upper_dev, ref_nr, up_list);
	__netdev_adjacent_dev_हटाओ(upper_dev, dev, ref_nr, करोwn_list);
पूर्ण

अटल पूर्णांक __netdev_adjacent_dev_link_neighbour(काष्ठा net_device *dev,
						काष्ठा net_device *upper_dev,
						व्योम *निजी, bool master)
अणु
	वापस __netdev_adjacent_dev_link_lists(dev, upper_dev,
						&dev->adj_list.upper,
						&upper_dev->adj_list.lower,
						निजी, master);
पूर्ण

अटल व्योम __netdev_adjacent_dev_unlink_neighbour(काष्ठा net_device *dev,
						   काष्ठा net_device *upper_dev)
अणु
	__netdev_adjacent_dev_unlink_lists(dev, upper_dev, 1,
					   &dev->adj_list.upper,
					   &upper_dev->adj_list.lower);
पूर्ण

अटल पूर्णांक __netdev_upper_dev_link(काष्ठा net_device *dev,
				   काष्ठा net_device *upper_dev, bool master,
				   व्योम *upper_priv, व्योम *upper_info,
				   काष्ठा netdev_nested_priv *priv,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_notअगरier_changeupper_info changeupper_info = अणु
		.info = अणु
			.dev = dev,
			.extack = extack,
		पूर्ण,
		.upper_dev = upper_dev,
		.master = master,
		.linking = true,
		.upper_info = upper_info,
	पूर्ण;
	काष्ठा net_device *master_dev;
	पूर्णांक ret = 0;

	ASSERT_RTNL();

	अगर (dev == upper_dev)
		वापस -EBUSY;

	/* To prevent loops, check अगर dev is not upper device to upper_dev. */
	अगर (__netdev_has_upper_dev(upper_dev, dev))
		वापस -EBUSY;

	अगर ((dev->lower_level + upper_dev->upper_level) > MAX_NEST_DEV)
		वापस -EMLINK;

	अगर (!master) अणु
		अगर (__netdev_has_upper_dev(dev, upper_dev))
			वापस -EEXIST;
	पूर्ण अन्यथा अणु
		master_dev = __netdev_master_upper_dev_get(dev);
		अगर (master_dev)
			वापस master_dev == upper_dev ? -EEXIST : -EBUSY;
	पूर्ण

	ret = call_netdevice_notअगरiers_info(NETDEV_PRECHANGEUPPER,
					    &changeupper_info.info);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret)
		वापस ret;

	ret = __netdev_adjacent_dev_link_neighbour(dev, upper_dev, upper_priv,
						   master);
	अगर (ret)
		वापस ret;

	ret = call_netdevice_notअगरiers_info(NETDEV_CHANGEUPPER,
					    &changeupper_info.info);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret)
		जाओ rollback;

	__netdev_update_upper_level(dev, शून्य);
	__netdev_walk_all_lower_dev(dev, __netdev_update_upper_level, शून्य);

	__netdev_update_lower_level(upper_dev, priv);
	__netdev_walk_all_upper_dev(upper_dev, __netdev_update_lower_level,
				    priv);

	वापस 0;

rollback:
	__netdev_adjacent_dev_unlink_neighbour(dev, upper_dev);

	वापस ret;
पूर्ण

/**
 * netdev_upper_dev_link - Add a link to the upper device
 * @dev: device
 * @upper_dev: new upper device
 * @extack: netlink extended ack
 *
 * Adds a link to device which is upper to this one. The caller must hold
 * the RTNL lock. On a failure a negative त्रुटि_सं code is वापसed.
 * On success the reference counts are adjusted and the function
 * वापसs zero.
 */
पूर्णांक netdev_upper_dev_link(काष्ठा net_device *dev,
			  काष्ठा net_device *upper_dev,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.flags = NESTED_SYNC_IMM | NESTED_SYNC_TODO,
		.data = शून्य,
	पूर्ण;

	वापस __netdev_upper_dev_link(dev, upper_dev, false,
				       शून्य, शून्य, &priv, extack);
पूर्ण
EXPORT_SYMBOL(netdev_upper_dev_link);

/**
 * netdev_master_upper_dev_link - Add a master link to the upper device
 * @dev: device
 * @upper_dev: new upper device
 * @upper_priv: upper device निजी
 * @upper_info: upper info to be passed करोwn via notअगरier
 * @extack: netlink extended ack
 *
 * Adds a link to device which is upper to this one. In this हाल, only
 * one master upper device can be linked, although other non-master devices
 * might be linked as well. The caller must hold the RTNL lock.
 * On a failure a negative त्रुटि_सं code is वापसed. On success the reference
 * counts are adjusted and the function वापसs zero.
 */
पूर्णांक netdev_master_upper_dev_link(काष्ठा net_device *dev,
				 काष्ठा net_device *upper_dev,
				 व्योम *upper_priv, व्योम *upper_info,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.flags = NESTED_SYNC_IMM | NESTED_SYNC_TODO,
		.data = शून्य,
	पूर्ण;

	वापस __netdev_upper_dev_link(dev, upper_dev, true,
				       upper_priv, upper_info, &priv, extack);
पूर्ण
EXPORT_SYMBOL(netdev_master_upper_dev_link);

अटल व्योम __netdev_upper_dev_unlink(काष्ठा net_device *dev,
				      काष्ठा net_device *upper_dev,
				      काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा netdev_notअगरier_changeupper_info changeupper_info = अणु
		.info = अणु
			.dev = dev,
		पूर्ण,
		.upper_dev = upper_dev,
		.linking = false,
	पूर्ण;

	ASSERT_RTNL();

	changeupper_info.master = netdev_master_upper_dev_get(dev) == upper_dev;

	call_netdevice_notअगरiers_info(NETDEV_PRECHANGEUPPER,
				      &changeupper_info.info);

	__netdev_adjacent_dev_unlink_neighbour(dev, upper_dev);

	call_netdevice_notअगरiers_info(NETDEV_CHANGEUPPER,
				      &changeupper_info.info);

	__netdev_update_upper_level(dev, शून्य);
	__netdev_walk_all_lower_dev(dev, __netdev_update_upper_level, शून्य);

	__netdev_update_lower_level(upper_dev, priv);
	__netdev_walk_all_upper_dev(upper_dev, __netdev_update_lower_level,
				    priv);
पूर्ण

/**
 * netdev_upper_dev_unlink - Removes a link to upper device
 * @dev: device
 * @upper_dev: new upper device
 *
 * Removes a link to device which is upper to this one. The caller must hold
 * the RTNL lock.
 */
व्योम netdev_upper_dev_unlink(काष्ठा net_device *dev,
			     काष्ठा net_device *upper_dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.flags = NESTED_SYNC_TODO,
		.data = शून्य,
	पूर्ण;

	__netdev_upper_dev_unlink(dev, upper_dev, &priv);
पूर्ण
EXPORT_SYMBOL(netdev_upper_dev_unlink);

अटल व्योम __netdev_adjacent_dev_set(काष्ठा net_device *upper_dev,
				      काष्ठा net_device *lower_dev,
				      bool val)
अणु
	काष्ठा netdev_adjacent *adj;

	adj = __netdev_find_adj(lower_dev, &upper_dev->adj_list.lower);
	अगर (adj)
		adj->ignore = val;

	adj = __netdev_find_adj(upper_dev, &lower_dev->adj_list.upper);
	अगर (adj)
		adj->ignore = val;
पूर्ण

अटल व्योम netdev_adjacent_dev_disable(काष्ठा net_device *upper_dev,
					काष्ठा net_device *lower_dev)
अणु
	__netdev_adjacent_dev_set(upper_dev, lower_dev, true);
पूर्ण

अटल व्योम netdev_adjacent_dev_enable(काष्ठा net_device *upper_dev,
				       काष्ठा net_device *lower_dev)
अणु
	__netdev_adjacent_dev_set(upper_dev, lower_dev, false);
पूर्ण

पूर्णांक netdev_adjacent_change_prepare(काष्ठा net_device *old_dev,
				   काष्ठा net_device *new_dev,
				   काष्ठा net_device *dev,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.flags = 0,
		.data = शून्य,
	पूर्ण;
	पूर्णांक err;

	अगर (!new_dev)
		वापस 0;

	अगर (old_dev && new_dev != old_dev)
		netdev_adjacent_dev_disable(dev, old_dev);
	err = __netdev_upper_dev_link(new_dev, dev, false, शून्य, शून्य, &priv,
				      extack);
	अगर (err) अणु
		अगर (old_dev && new_dev != old_dev)
			netdev_adjacent_dev_enable(dev, old_dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netdev_adjacent_change_prepare);

व्योम netdev_adjacent_change_commit(काष्ठा net_device *old_dev,
				   काष्ठा net_device *new_dev,
				   काष्ठा net_device *dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.flags = NESTED_SYNC_IMM | NESTED_SYNC_TODO,
		.data = शून्य,
	पूर्ण;

	अगर (!new_dev || !old_dev)
		वापस;

	अगर (new_dev == old_dev)
		वापस;

	netdev_adjacent_dev_enable(dev, old_dev);
	__netdev_upper_dev_unlink(old_dev, dev, &priv);
पूर्ण
EXPORT_SYMBOL(netdev_adjacent_change_commit);

व्योम netdev_adjacent_change_पात(काष्ठा net_device *old_dev,
				  काष्ठा net_device *new_dev,
				  काष्ठा net_device *dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.flags = 0,
		.data = शून्य,
	पूर्ण;

	अगर (!new_dev)
		वापस;

	अगर (old_dev && new_dev != old_dev)
		netdev_adjacent_dev_enable(dev, old_dev);

	__netdev_upper_dev_unlink(new_dev, dev, &priv);
पूर्ण
EXPORT_SYMBOL(netdev_adjacent_change_पात);

/**
 * netdev_bonding_info_change - Dispatch event about slave change
 * @dev: device
 * @bonding_info: info to dispatch
 *
 * Send NETDEV_BONDING_INFO to netdev notअगरiers with info.
 * The caller must hold the RTNL lock.
 */
व्योम netdev_bonding_info_change(काष्ठा net_device *dev,
				काष्ठा netdev_bonding_info *bonding_info)
अणु
	काष्ठा netdev_notअगरier_bonding_info info = अणु
		.info.dev = dev,
	पूर्ण;

	स_नकल(&info.bonding_info, bonding_info,
	       माप(काष्ठा netdev_bonding_info));
	call_netdevice_notअगरiers_info(NETDEV_BONDING_INFO,
				      &info.info);
पूर्ण
EXPORT_SYMBOL(netdev_bonding_info_change);

/**
 * netdev_get_xmit_slave - Get the xmit slave of master device
 * @dev: device
 * @skb: The packet
 * @all_slaves: assume all the slaves are active
 *
 * The reference counters are not incremented so the caller must be
 * careful with locks. The caller must hold RCU lock.
 * %शून्य is वापसed अगर no slave is found.
 */

काष्ठा net_device *netdev_get_xmit_slave(काष्ठा net_device *dev,
					 काष्ठा sk_buff *skb,
					 bool all_slaves)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	अगर (!ops->nकरो_get_xmit_slave)
		वापस शून्य;
	वापस ops->nकरो_get_xmit_slave(dev, skb, all_slaves);
पूर्ण
EXPORT_SYMBOL(netdev_get_xmit_slave);

अटल काष्ठा net_device *netdev_sk_get_lower_dev(काष्ठा net_device *dev,
						  काष्ठा sock *sk)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	अगर (!ops->nकरो_sk_get_lower_dev)
		वापस शून्य;
	वापस ops->nकरो_sk_get_lower_dev(dev, sk);
पूर्ण

/**
 * netdev_sk_get_lowest_dev - Get the lowest device in chain given device and socket
 * @dev: device
 * @sk: the socket
 *
 * %शून्य is वापसed अगर no lower device is found.
 */

काष्ठा net_device *netdev_sk_get_lowest_dev(काष्ठा net_device *dev,
					    काष्ठा sock *sk)
अणु
	काष्ठा net_device *lower;

	lower = netdev_sk_get_lower_dev(dev, sk);
	जबतक (lower) अणु
		dev = lower;
		lower = netdev_sk_get_lower_dev(dev, sk);
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL(netdev_sk_get_lowest_dev);

अटल व्योम netdev_adjacent_add_links(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_adjacent *iter;

	काष्ठा net *net = dev_net(dev);

	list_क्रम_each_entry(iter, &dev->adj_list.upper, list) अणु
		अगर (!net_eq(net, dev_net(iter->dev)))
			जारी;
		netdev_adjacent_sysfs_add(iter->dev, dev,
					  &iter->dev->adj_list.lower);
		netdev_adjacent_sysfs_add(dev, iter->dev,
					  &dev->adj_list.upper);
	पूर्ण

	list_क्रम_each_entry(iter, &dev->adj_list.lower, list) अणु
		अगर (!net_eq(net, dev_net(iter->dev)))
			जारी;
		netdev_adjacent_sysfs_add(iter->dev, dev,
					  &iter->dev->adj_list.upper);
		netdev_adjacent_sysfs_add(dev, iter->dev,
					  &dev->adj_list.lower);
	पूर्ण
पूर्ण

अटल व्योम netdev_adjacent_del_links(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_adjacent *iter;

	काष्ठा net *net = dev_net(dev);

	list_क्रम_each_entry(iter, &dev->adj_list.upper, list) अणु
		अगर (!net_eq(net, dev_net(iter->dev)))
			जारी;
		netdev_adjacent_sysfs_del(iter->dev, dev->name,
					  &iter->dev->adj_list.lower);
		netdev_adjacent_sysfs_del(dev, iter->dev->name,
					  &dev->adj_list.upper);
	पूर्ण

	list_क्रम_each_entry(iter, &dev->adj_list.lower, list) अणु
		अगर (!net_eq(net, dev_net(iter->dev)))
			जारी;
		netdev_adjacent_sysfs_del(iter->dev, dev->name,
					  &iter->dev->adj_list.upper);
		netdev_adjacent_sysfs_del(dev, iter->dev->name,
					  &dev->adj_list.lower);
	पूर्ण
पूर्ण

व्योम netdev_adjacent_नाम_links(काष्ठा net_device *dev, अक्षर *oldname)
अणु
	काष्ठा netdev_adjacent *iter;

	काष्ठा net *net = dev_net(dev);

	list_क्रम_each_entry(iter, &dev->adj_list.upper, list) अणु
		अगर (!net_eq(net, dev_net(iter->dev)))
			जारी;
		netdev_adjacent_sysfs_del(iter->dev, oldname,
					  &iter->dev->adj_list.lower);
		netdev_adjacent_sysfs_add(iter->dev, dev,
					  &iter->dev->adj_list.lower);
	पूर्ण

	list_क्रम_each_entry(iter, &dev->adj_list.lower, list) अणु
		अगर (!net_eq(net, dev_net(iter->dev)))
			जारी;
		netdev_adjacent_sysfs_del(iter->dev, oldname,
					  &iter->dev->adj_list.upper);
		netdev_adjacent_sysfs_add(iter->dev, dev,
					  &iter->dev->adj_list.upper);
	पूर्ण
पूर्ण

व्योम *netdev_lower_dev_get_निजी(काष्ठा net_device *dev,
				   काष्ठा net_device *lower_dev)
अणु
	काष्ठा netdev_adjacent *lower;

	अगर (!lower_dev)
		वापस शून्य;
	lower = __netdev_find_adj(lower_dev, &dev->adj_list.lower);
	अगर (!lower)
		वापस शून्य;

	वापस lower->निजी;
पूर्ण
EXPORT_SYMBOL(netdev_lower_dev_get_निजी);


/**
 * netdev_lower_state_changed - Dispatch event about lower device state change
 * @lower_dev: device
 * @lower_state_info: state to dispatch
 *
 * Send NETDEV_CHANGELOWERSTATE to netdev notअगरiers with info.
 * The caller must hold the RTNL lock.
 */
व्योम netdev_lower_state_changed(काष्ठा net_device *lower_dev,
				व्योम *lower_state_info)
अणु
	काष्ठा netdev_notअगरier_changelowerstate_info changelowerstate_info = अणु
		.info.dev = lower_dev,
	पूर्ण;

	ASSERT_RTNL();
	changelowerstate_info.lower_state_info = lower_state_info;
	call_netdevice_notअगरiers_info(NETDEV_CHANGELOWERSTATE,
				      &changelowerstate_info.info);
पूर्ण
EXPORT_SYMBOL(netdev_lower_state_changed);

अटल व्योम dev_change_rx_flags(काष्ठा net_device *dev, पूर्णांक flags)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	अगर (ops->nकरो_change_rx_flags)
		ops->nकरो_change_rx_flags(dev, flags);
पूर्ण

अटल पूर्णांक __dev_set_promiscuity(काष्ठा net_device *dev, पूर्णांक inc, bool notअगरy)
अणु
	अचिन्हित पूर्णांक old_flags = dev->flags;
	kuid_t uid;
	kgid_t gid;

	ASSERT_RTNL();

	dev->flags |= IFF_PROMISC;
	dev->promiscuity += inc;
	अगर (dev->promiscuity == 0) अणु
		/*
		 * Aव्योम overflow.
		 * If inc causes overflow, untouch promisc and वापस error.
		 */
		अगर (inc < 0)
			dev->flags &= ~IFF_PROMISC;
		अन्यथा अणु
			dev->promiscuity -= inc;
			pr_warn("%s: promiscuity touches roof, set promiscuity failed. promiscuity feature of device might be broken.\n",
				dev->name);
			वापस -EOVERFLOW;
		पूर्ण
	पूर्ण
	अगर (dev->flags != old_flags) अणु
		pr_info("device %s %s promiscuous mode\n",
			dev->name,
			dev->flags & IFF_PROMISC ? "entered" : "left");
		अगर (audit_enabled) अणु
			current_uid_gid(&uid, &gid);
			audit_log(audit_context(), GFP_ATOMIC,
				  AUDIT_ANOM_PROMISCUOUS,
				  "dev=%s prom=%d old_prom=%d auid=%u uid=%u gid=%u ses=%u",
				  dev->name, (dev->flags & IFF_PROMISC),
				  (old_flags & IFF_PROMISC),
				  from_kuid(&init_user_ns, audit_get_loginuid(current)),
				  from_kuid(&init_user_ns, uid),
				  from_kgid(&init_user_ns, gid),
				  audit_get_sessionid(current));
		पूर्ण

		dev_change_rx_flags(dev, IFF_PROMISC);
	पूर्ण
	अगर (notअगरy)
		__dev_notअगरy_flags(dev, old_flags, IFF_PROMISC);
	वापस 0;
पूर्ण

/**
 *	dev_set_promiscuity	- update promiscuity count on a device
 *	@dev: device
 *	@inc: modअगरier
 *
 *	Add or हटाओ promiscuity from a device. While the count in the device
 *	reमुख्यs above zero the पूर्णांकerface reमुख्यs promiscuous. Once it hits zero
 *	the device reverts back to normal filtering operation. A negative inc
 *	value is used to drop promiscuity on the device.
 *	Return 0 अगर successful or a negative त्रुटि_सं code on error.
 */
पूर्णांक dev_set_promiscuity(काष्ठा net_device *dev, पूर्णांक inc)
अणु
	अचिन्हित पूर्णांक old_flags = dev->flags;
	पूर्णांक err;

	err = __dev_set_promiscuity(dev, inc, true);
	अगर (err < 0)
		वापस err;
	अगर (dev->flags != old_flags)
		dev_set_rx_mode(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_set_promiscuity);

अटल पूर्णांक __dev_set_allmulti(काष्ठा net_device *dev, पूर्णांक inc, bool notअगरy)
अणु
	अचिन्हित पूर्णांक old_flags = dev->flags, old_gflags = dev->gflags;

	ASSERT_RTNL();

	dev->flags |= IFF_ALLMULTI;
	dev->allmulti += inc;
	अगर (dev->allmulti == 0) अणु
		/*
		 * Aव्योम overflow.
		 * If inc causes overflow, untouch allmulti and वापस error.
		 */
		अगर (inc < 0)
			dev->flags &= ~IFF_ALLMULTI;
		अन्यथा अणु
			dev->allmulti -= inc;
			pr_warn("%s: allmulti touches roof, set allmulti failed. allmulti feature of device might be broken.\n",
				dev->name);
			वापस -EOVERFLOW;
		पूर्ण
	पूर्ण
	अगर (dev->flags ^ old_flags) अणु
		dev_change_rx_flags(dev, IFF_ALLMULTI);
		dev_set_rx_mode(dev);
		अगर (notअगरy)
			__dev_notअगरy_flags(dev, old_flags,
					   dev->gflags ^ old_gflags);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	dev_set_allmulti	- update allmulti count on a device
 *	@dev: device
 *	@inc: modअगरier
 *
 *	Add or हटाओ reception of all multicast frames to a device. While the
 *	count in the device reमुख्यs above zero the पूर्णांकerface reमुख्यs listening
 *	to all पूर्णांकerfaces. Once it hits zero the device reverts back to normal
 *	filtering operation. A negative @inc value is used to drop the counter
 *	when releasing a resource needing all multicasts.
 *	Return 0 अगर successful or a negative त्रुटि_सं code on error.
 */

पूर्णांक dev_set_allmulti(काष्ठा net_device *dev, पूर्णांक inc)
अणु
	वापस __dev_set_allmulti(dev, inc, true);
पूर्ण
EXPORT_SYMBOL(dev_set_allmulti);

/*
 *	Upload unicast and multicast address lists to device and
 *	configure RX filtering. When the device करोesn't support unicast
 *	filtering it is put in promiscuous mode जबतक unicast addresses
 *	are present.
 */
व्योम __dev_set_rx_mode(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	/* dev_खोलो will call this function so the list will stay sane. */
	अगर (!(dev->flags&IFF_UP))
		वापस;

	अगर (!netअगर_device_present(dev))
		वापस;

	अगर (!(dev->priv_flags & IFF_UNICAST_FLT)) अणु
		/* Unicast addresses changes may only happen under the rtnl,
		 * thereक्रमe calling __dev_set_promiscuity here is safe.
		 */
		अगर (!netdev_uc_empty(dev) && !dev->uc_promisc) अणु
			__dev_set_promiscuity(dev, 1, false);
			dev->uc_promisc = true;
		पूर्ण अन्यथा अगर (netdev_uc_empty(dev) && dev->uc_promisc) अणु
			__dev_set_promiscuity(dev, -1, false);
			dev->uc_promisc = false;
		पूर्ण
	पूर्ण

	अगर (ops->nकरो_set_rx_mode)
		ops->nकरो_set_rx_mode(dev);
पूर्ण

व्योम dev_set_rx_mode(काष्ठा net_device *dev)
अणु
	netअगर_addr_lock_bh(dev);
	__dev_set_rx_mode(dev);
	netअगर_addr_unlock_bh(dev);
पूर्ण

/**
 *	dev_get_flags - get flags reported to userspace
 *	@dev: device
 *
 *	Get the combination of flag bits exported through APIs to userspace.
 */
अचिन्हित पूर्णांक dev_get_flags(स्थिर काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक flags;

	flags = (dev->flags & ~(IFF_PROMISC |
				IFF_ALLMULTI |
				IFF_RUNNING |
				IFF_LOWER_UP |
				IFF_DORMANT)) |
		(dev->gflags & (IFF_PROMISC |
				IFF_ALLMULTI));

	अगर (netअगर_running(dev)) अणु
		अगर (netअगर_oper_up(dev))
			flags |= IFF_RUNNING;
		अगर (netअगर_carrier_ok(dev))
			flags |= IFF_LOWER_UP;
		अगर (netअगर_करोrmant(dev))
			flags |= IFF_DORMANT;
	पूर्ण

	वापस flags;
पूर्ण
EXPORT_SYMBOL(dev_get_flags);

पूर्णांक __dev_change_flags(काष्ठा net_device *dev, अचिन्हित पूर्णांक flags,
		       काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित पूर्णांक old_flags = dev->flags;
	पूर्णांक ret;

	ASSERT_RTNL();

	/*
	 *	Set the flags on our device.
	 */

	dev->flags = (flags & (IFF_DEBUG | IFF_NOTRAILERS | IFF_NOARP |
			       IFF_DYNAMIC | IFF_MULTICAST | IFF_PORTSEL |
			       IFF_AUTOMEDIA)) |
		     (dev->flags & (IFF_UP | IFF_VOLATILE | IFF_PROMISC |
				    IFF_ALLMULTI));

	/*
	 *	Load in the correct multicast list now the flags have changed.
	 */

	अगर ((old_flags ^ flags) & IFF_MULTICAST)
		dev_change_rx_flags(dev, IFF_MULTICAST);

	dev_set_rx_mode(dev);

	/*
	 *	Have we करोwned the पूर्णांकerface. We handle IFF_UP ourselves
	 *	according to user attempts to set it, rather than blindly
	 *	setting it.
	 */

	ret = 0;
	अगर ((old_flags ^ flags) & IFF_UP) अणु
		अगर (old_flags & IFF_UP)
			__dev_बंद(dev);
		अन्यथा
			ret = __dev_खोलो(dev, extack);
	पूर्ण

	अगर ((flags ^ dev->gflags) & IFF_PROMISC) अणु
		पूर्णांक inc = (flags & IFF_PROMISC) ? 1 : -1;
		अचिन्हित पूर्णांक old_flags = dev->flags;

		dev->gflags ^= IFF_PROMISC;

		अगर (__dev_set_promiscuity(dev, inc, false) >= 0)
			अगर (dev->flags != old_flags)
				dev_set_rx_mode(dev);
	पूर्ण

	/* NOTE: order of synchronization of IFF_PROMISC and IFF_ALLMULTI
	 * is important. Some (broken) drivers set IFF_PROMISC, when
	 * IFF_ALLMULTI is requested not asking us and not reporting.
	 */
	अगर ((flags ^ dev->gflags) & IFF_ALLMULTI) अणु
		पूर्णांक inc = (flags & IFF_ALLMULTI) ? 1 : -1;

		dev->gflags ^= IFF_ALLMULTI;
		__dev_set_allmulti(dev, inc, false);
	पूर्ण

	वापस ret;
पूर्ण

व्योम __dev_notअगरy_flags(काष्ठा net_device *dev, अचिन्हित पूर्णांक old_flags,
			अचिन्हित पूर्णांक gchanges)
अणु
	अचिन्हित पूर्णांक changes = dev->flags ^ old_flags;

	अगर (gchanges)
		rपंचांगsg_अगरinfo(RTM_NEWLINK, dev, gchanges, GFP_ATOMIC);

	अगर (changes & IFF_UP) अणु
		अगर (dev->flags & IFF_UP)
			call_netdevice_notअगरiers(NETDEV_UP, dev);
		अन्यथा
			call_netdevice_notअगरiers(NETDEV_DOWN, dev);
	पूर्ण

	अगर (dev->flags & IFF_UP &&
	    (changes & ~(IFF_UP | IFF_PROMISC | IFF_ALLMULTI | IFF_VOLATILE))) अणु
		काष्ठा netdev_notअगरier_change_info change_info = अणु
			.info = अणु
				.dev = dev,
			पूर्ण,
			.flags_changed = changes,
		पूर्ण;

		call_netdevice_notअगरiers_info(NETDEV_CHANGE, &change_info.info);
	पूर्ण
पूर्ण

/**
 *	dev_change_flags - change device settings
 *	@dev: device
 *	@flags: device state flags
 *	@extack: netlink extended ack
 *
 *	Change settings on device based state flags. The flags are
 *	in the userspace exported क्रमmat.
 */
पूर्णांक dev_change_flags(काष्ठा net_device *dev, अचिन्हित पूर्णांक flags,
		     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक changes, old_flags = dev->flags, old_gflags = dev->gflags;

	ret = __dev_change_flags(dev, flags, extack);
	अगर (ret < 0)
		वापस ret;

	changes = (old_flags ^ dev->flags) | (old_gflags ^ dev->gflags);
	__dev_notअगरy_flags(dev, old_flags, changes);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dev_change_flags);

पूर्णांक __dev_set_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	अगर (ops->nकरो_change_mtu)
		वापस ops->nकरो_change_mtu(dev, new_mtu);

	/* Pairs with all the lockless पढ़ोs of dev->mtu in the stack */
	WRITE_ONCE(dev->mtu, new_mtu);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__dev_set_mtu);

पूर्णांक dev_validate_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu,
		     काष्ठा netlink_ext_ack *extack)
अणु
	/* MTU must be positive, and in range */
	अगर (new_mtu < 0 || new_mtu < dev->min_mtu) अणु
		NL_SET_ERR_MSG(extack, "mtu less than device minimum");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->max_mtu > 0 && new_mtu > dev->max_mtu) अणु
		NL_SET_ERR_MSG(extack, "mtu greater than device maximum");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	dev_set_mtu_ext - Change maximum transfer unit
 *	@dev: device
 *	@new_mtu: new transfer unit
 *	@extack: netlink extended ack
 *
 *	Change the maximum transfer size of the network device.
 */
पूर्णांक dev_set_mtu_ext(काष्ठा net_device *dev, पूर्णांक new_mtu,
		    काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err, orig_mtu;

	अगर (new_mtu == dev->mtu)
		वापस 0;

	err = dev_validate_mtu(dev, new_mtu, extack);
	अगर (err)
		वापस err;

	अगर (!netअगर_device_present(dev))
		वापस -ENODEV;

	err = call_netdevice_notअगरiers(NETDEV_PRECHANGEMTU, dev);
	err = notअगरier_to_त्रुटि_सं(err);
	अगर (err)
		वापस err;

	orig_mtu = dev->mtu;
	err = __dev_set_mtu(dev, new_mtu);

	अगर (!err) अणु
		err = call_netdevice_notअगरiers_mtu(NETDEV_CHANGEMTU, dev,
						   orig_mtu);
		err = notअगरier_to_त्रुटि_सं(err);
		अगर (err) अणु
			/* setting mtu back and notअगरying everyone again,
			 * so that they have a chance to revert changes.
			 */
			__dev_set_mtu(dev, orig_mtu);
			call_netdevice_notअगरiers_mtu(NETDEV_CHANGEMTU, dev,
						     new_mtu);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक dev_set_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा netlink_ext_ack extack;
	पूर्णांक err;

	स_रखो(&extack, 0, माप(extack));
	err = dev_set_mtu_ext(dev, new_mtu, &extack);
	अगर (err && extack._msg)
		net_err_ratelimited("%s: %s\n", dev->name, extack._msg);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_set_mtu);

/**
 *	dev_change_tx_queue_len - Change TX queue length of a netdevice
 *	@dev: device
 *	@new_len: new tx queue length
 */
पूर्णांक dev_change_tx_queue_len(काष्ठा net_device *dev, अचिन्हित दीर्घ new_len)
अणु
	अचिन्हित पूर्णांक orig_len = dev->tx_queue_len;
	पूर्णांक res;

	अगर (new_len != (अचिन्हित पूर्णांक)new_len)
		वापस -दुस्फल;

	अगर (new_len != orig_len) अणु
		dev->tx_queue_len = new_len;
		res = call_netdevice_notअगरiers(NETDEV_CHANGE_TX_QUEUE_LEN, dev);
		res = notअगरier_to_त्रुटि_सं(res);
		अगर (res)
			जाओ err_rollback;
		res = dev_qdisc_change_tx_queue_len(dev);
		अगर (res)
			जाओ err_rollback;
	पूर्ण

	वापस 0;

err_rollback:
	netdev_err(dev, "refused to change device tx_queue_len\n");
	dev->tx_queue_len = orig_len;
	वापस res;
पूर्ण

/**
 *	dev_set_group - Change group this device beदीर्घs to
 *	@dev: device
 *	@new_group: group this device should beदीर्घ to
 */
व्योम dev_set_group(काष्ठा net_device *dev, पूर्णांक new_group)
अणु
	dev->group = new_group;
पूर्ण
EXPORT_SYMBOL(dev_set_group);

/**
 *	dev_pre_changeaddr_notअगरy - Call NETDEV_PRE_CHANGEADDR.
 *	@dev: device
 *	@addr: new address
 *	@extack: netlink extended ack
 */
पूर्णांक dev_pre_changeaddr_notअगरy(काष्ठा net_device *dev, स्थिर अक्षर *addr,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_notअगरier_pre_changeaddr_info info = अणु
		.info.dev = dev,
		.info.extack = extack,
		.dev_addr = addr,
	पूर्ण;
	पूर्णांक rc;

	rc = call_netdevice_notअगरiers_info(NETDEV_PRE_CHANGEADDR, &info.info);
	वापस notअगरier_to_त्रुटि_सं(rc);
पूर्ण
EXPORT_SYMBOL(dev_pre_changeaddr_notअगरy);

/**
 *	dev_set_mac_address - Change Media Access Control Address
 *	@dev: device
 *	@sa: new address
 *	@extack: netlink extended ack
 *
 *	Change the hardware (MAC) address of the device
 */
पूर्णांक dev_set_mac_address(काष्ठा net_device *dev, काष्ठा sockaddr *sa,
			काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	पूर्णांक err;

	अगर (!ops->nकरो_set_mac_address)
		वापस -EOPNOTSUPP;
	अगर (sa->sa_family != dev->type)
		वापस -EINVAL;
	अगर (!netअगर_device_present(dev))
		वापस -ENODEV;
	err = dev_pre_changeaddr_notअगरy(dev, sa->sa_data, extack);
	अगर (err)
		वापस err;
	err = ops->nकरो_set_mac_address(dev, sa);
	अगर (err)
		वापस err;
	dev->addr_assign_type = NET_ADDR_SET;
	call_netdevice_notअगरiers(NETDEV_CHANGEADDR, dev);
	add_device_अक्रमomness(dev->dev_addr, dev->addr_len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dev_set_mac_address);

अटल DECLARE_RWSEM(dev_addr_sem);

पूर्णांक dev_set_mac_address_user(काष्ठा net_device *dev, काष्ठा sockaddr *sa,
			     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&dev_addr_sem);
	ret = dev_set_mac_address(dev, sa, extack);
	up_ग_लिखो(&dev_addr_sem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dev_set_mac_address_user);

पूर्णांक dev_get_mac_address(काष्ठा sockaddr *sa, काष्ठा net *net, अक्षर *dev_name)
अणु
	माप_प्रकार size = माप(sa->sa_data);
	काष्ठा net_device *dev;
	पूर्णांक ret = 0;

	करोwn_पढ़ो(&dev_addr_sem);
	rcu_पढ़ो_lock();

	dev = dev_get_by_name_rcu(net, dev_name);
	अगर (!dev) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण
	अगर (!dev->addr_len)
		स_रखो(sa->sa_data, 0, size);
	अन्यथा
		स_नकल(sa->sa_data, dev->dev_addr,
		       min_t(माप_प्रकार, size, dev->addr_len));
	sa->sa_family = dev->type;

unlock:
	rcu_पढ़ो_unlock();
	up_पढ़ो(&dev_addr_sem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dev_get_mac_address);

/**
 *	dev_change_carrier - Change device carrier
 *	@dev: device
 *	@new_carrier: new value
 *
 *	Change device carrier
 */
पूर्णांक dev_change_carrier(काष्ठा net_device *dev, bool new_carrier)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	अगर (!ops->nकरो_change_carrier)
		वापस -EOPNOTSUPP;
	अगर (!netअगर_device_present(dev))
		वापस -ENODEV;
	वापस ops->nकरो_change_carrier(dev, new_carrier);
पूर्ण
EXPORT_SYMBOL(dev_change_carrier);

/**
 *	dev_get_phys_port_id - Get device physical port ID
 *	@dev: device
 *	@ppid: port ID
 *
 *	Get device physical port ID
 */
पूर्णांक dev_get_phys_port_id(काष्ठा net_device *dev,
			 काष्ठा netdev_phys_item_id *ppid)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	अगर (!ops->nकरो_get_phys_port_id)
		वापस -EOPNOTSUPP;
	वापस ops->nकरो_get_phys_port_id(dev, ppid);
पूर्ण
EXPORT_SYMBOL(dev_get_phys_port_id);

/**
 *	dev_get_phys_port_name - Get device physical port name
 *	@dev: device
 *	@name: port name
 *	@len: limit of bytes to copy to name
 *
 *	Get device physical port name
 */
पूर्णांक dev_get_phys_port_name(काष्ठा net_device *dev,
			   अक्षर *name, माप_प्रकार len)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	पूर्णांक err;

	अगर (ops->nकरो_get_phys_port_name) अणु
		err = ops->nकरो_get_phys_port_name(dev, name, len);
		अगर (err != -EOPNOTSUPP)
			वापस err;
	पूर्ण
	वापस devlink_compat_phys_port_name_get(dev, name, len);
पूर्ण
EXPORT_SYMBOL(dev_get_phys_port_name);

/**
 *	dev_get_port_parent_id - Get the device's port parent identअगरier
 *	@dev: network device
 *	@ppid: poपूर्णांकer to a storage क्रम the port's parent identअगरier
 *	@recurse: allow/disallow recursion to lower devices
 *
 *	Get the devices's port parent identअगरier
 */
पूर्णांक dev_get_port_parent_id(काष्ठा net_device *dev,
			   काष्ठा netdev_phys_item_id *ppid,
			   bool recurse)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	काष्ठा netdev_phys_item_id first = अणु पूर्ण;
	काष्ठा net_device *lower_dev;
	काष्ठा list_head *iter;
	पूर्णांक err;

	अगर (ops->nकरो_get_port_parent_id) अणु
		err = ops->nकरो_get_port_parent_id(dev, ppid);
		अगर (err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	err = devlink_compat_चयन_id_get(dev, ppid);
	अगर (!err || err != -EOPNOTSUPP)
		वापस err;

	अगर (!recurse)
		वापस -EOPNOTSUPP;

	netdev_क्रम_each_lower_dev(dev, lower_dev, iter) अणु
		err = dev_get_port_parent_id(lower_dev, ppid, recurse);
		अगर (err)
			अवरोध;
		अगर (!first.id_len)
			first = *ppid;
		अन्यथा अगर (स_भेद(&first, ppid, माप(*ppid)))
			वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(dev_get_port_parent_id);

/**
 *	netdev_port_same_parent_id - Indicate अगर two network devices have
 *	the same port parent identअगरier
 *	@a: first network device
 *	@b: second network device
 */
bool netdev_port_same_parent_id(काष्ठा net_device *a, काष्ठा net_device *b)
अणु
	काष्ठा netdev_phys_item_id a_id = अणु पूर्ण;
	काष्ठा netdev_phys_item_id b_id = अणु पूर्ण;

	अगर (dev_get_port_parent_id(a, &a_id, true) ||
	    dev_get_port_parent_id(b, &b_id, true))
		वापस false;

	वापस netdev_phys_item_id_same(&a_id, &b_id);
पूर्ण
EXPORT_SYMBOL(netdev_port_same_parent_id);

/**
 *	dev_change_proto_करोwn - update protocol port state inक्रमmation
 *	@dev: device
 *	@proto_करोwn: new value
 *
 *	This info can be used by चयन drivers to set the phys state of the
 *	port.
 */
पूर्णांक dev_change_proto_करोwn(काष्ठा net_device *dev, bool proto_करोwn)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	अगर (!ops->nकरो_change_proto_करोwn)
		वापस -EOPNOTSUPP;
	अगर (!netअगर_device_present(dev))
		वापस -ENODEV;
	वापस ops->nकरो_change_proto_करोwn(dev, proto_करोwn);
पूर्ण
EXPORT_SYMBOL(dev_change_proto_करोwn);

/**
 *	dev_change_proto_करोwn_generic - generic implementation क्रम
 * 	nकरो_change_proto_करोwn that sets carrier according to
 * 	proto_करोwn.
 *
 *	@dev: device
 *	@proto_करोwn: new value
 */
पूर्णांक dev_change_proto_करोwn_generic(काष्ठा net_device *dev, bool proto_करोwn)
अणु
	अगर (proto_करोwn)
		netअगर_carrier_off(dev);
	अन्यथा
		netअगर_carrier_on(dev);
	dev->proto_करोwn = proto_करोwn;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dev_change_proto_करोwn_generic);

/**
 *	dev_change_proto_करोwn_reason - proto करोwn reason
 *
 *	@dev: device
 *	@mask: proto करोwn mask
 *	@value: proto करोwn value
 */
व्योम dev_change_proto_करोwn_reason(काष्ठा net_device *dev, अचिन्हित दीर्घ mask,
				  u32 value)
अणु
	पूर्णांक b;

	अगर (!mask) अणु
		dev->proto_करोwn_reason = value;
	पूर्ण अन्यथा अणु
		क्रम_each_set_bit(b, &mask, 32) अणु
			अगर (value & (1 << b))
				dev->proto_करोwn_reason |= BIT(b);
			अन्यथा
				dev->proto_करोwn_reason &= ~BIT(b);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dev_change_proto_करोwn_reason);

काष्ठा bpf_xdp_link अणु
	काष्ठा bpf_link link;
	काष्ठा net_device *dev; /* रक्षित by rtnl_lock, no refcnt held */
	पूर्णांक flags;
पूर्ण;

अटल क्रमागत bpf_xdp_mode dev_xdp_mode(काष्ठा net_device *dev, u32 flags)
अणु
	अगर (flags & XDP_FLAGS_HW_MODE)
		वापस XDP_MODE_HW;
	अगर (flags & XDP_FLAGS_DRV_MODE)
		वापस XDP_MODE_DRV;
	अगर (flags & XDP_FLAGS_SKB_MODE)
		वापस XDP_MODE_SKB;
	वापस dev->netdev_ops->nकरो_bpf ? XDP_MODE_DRV : XDP_MODE_SKB;
पूर्ण

अटल bpf_op_t dev_xdp_bpf_op(काष्ठा net_device *dev, क्रमागत bpf_xdp_mode mode)
अणु
	चयन (mode) अणु
	हाल XDP_MODE_SKB:
		वापस generic_xdp_install;
	हाल XDP_MODE_DRV:
	हाल XDP_MODE_HW:
		वापस dev->netdev_ops->nकरो_bpf;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा bpf_xdp_link *dev_xdp_link(काष्ठा net_device *dev,
					 क्रमागत bpf_xdp_mode mode)
अणु
	वापस dev->xdp_state[mode].link;
पूर्ण

अटल काष्ठा bpf_prog *dev_xdp_prog(काष्ठा net_device *dev,
				     क्रमागत bpf_xdp_mode mode)
अणु
	काष्ठा bpf_xdp_link *link = dev_xdp_link(dev, mode);

	अगर (link)
		वापस link->link.prog;
	वापस dev->xdp_state[mode].prog;
पूर्ण

अटल u8 dev_xdp_prog_count(काष्ठा net_device *dev)
अणु
	u8 count = 0;
	पूर्णांक i;

	क्रम (i = 0; i < __MAX_XDP_MODE; i++)
		अगर (dev->xdp_state[i].prog || dev->xdp_state[i].link)
			count++;
	वापस count;
पूर्ण

u32 dev_xdp_prog_id(काष्ठा net_device *dev, क्रमागत bpf_xdp_mode mode)
अणु
	काष्ठा bpf_prog *prog = dev_xdp_prog(dev, mode);

	वापस prog ? prog->aux->id : 0;
पूर्ण

अटल व्योम dev_xdp_set_link(काष्ठा net_device *dev, क्रमागत bpf_xdp_mode mode,
			     काष्ठा bpf_xdp_link *link)
अणु
	dev->xdp_state[mode].link = link;
	dev->xdp_state[mode].prog = शून्य;
पूर्ण

अटल व्योम dev_xdp_set_prog(काष्ठा net_device *dev, क्रमागत bpf_xdp_mode mode,
			     काष्ठा bpf_prog *prog)
अणु
	dev->xdp_state[mode].link = शून्य;
	dev->xdp_state[mode].prog = prog;
पूर्ण

अटल पूर्णांक dev_xdp_install(काष्ठा net_device *dev, क्रमागत bpf_xdp_mode mode,
			   bpf_op_t bpf_op, काष्ठा netlink_ext_ack *extack,
			   u32 flags, काष्ठा bpf_prog *prog)
अणु
	काष्ठा netdev_bpf xdp;
	पूर्णांक err;

	स_रखो(&xdp, 0, माप(xdp));
	xdp.command = mode == XDP_MODE_HW ? XDP_SETUP_PROG_HW : XDP_SETUP_PROG;
	xdp.extack = extack;
	xdp.flags = flags;
	xdp.prog = prog;

	/* Drivers assume refcnt is alपढ़ोy incremented (i.e, prog poपूर्णांकer is
	 * "moved" पूर्णांकo driver), so they करोn't increment it on their own, but
	 * they करो decrement refcnt when program is detached or replaced.
	 * Given net_device also owns link/prog, we need to bump refcnt here
	 * to prevent drivers from underflowing it.
	 */
	अगर (prog)
		bpf_prog_inc(prog);
	err = bpf_op(dev, &xdp);
	अगर (err) अणु
		अगर (prog)
			bpf_prog_put(prog);
		वापस err;
	पूर्ण

	अगर (mode != XDP_MODE_HW)
		bpf_prog_change_xdp(dev_xdp_prog(dev, mode), prog);

	वापस 0;
पूर्ण

अटल व्योम dev_xdp_uninstall(काष्ठा net_device *dev)
अणु
	काष्ठा bpf_xdp_link *link;
	काष्ठा bpf_prog *prog;
	क्रमागत bpf_xdp_mode mode;
	bpf_op_t bpf_op;

	ASSERT_RTNL();

	क्रम (mode = XDP_MODE_SKB; mode < __MAX_XDP_MODE; mode++) अणु
		prog = dev_xdp_prog(dev, mode);
		अगर (!prog)
			जारी;

		bpf_op = dev_xdp_bpf_op(dev, mode);
		अगर (!bpf_op)
			जारी;

		WARN_ON(dev_xdp_install(dev, mode, bpf_op, शून्य, 0, शून्य));

		/* स्वतः-detach link from net device */
		link = dev_xdp_link(dev, mode);
		अगर (link)
			link->dev = शून्य;
		अन्यथा
			bpf_prog_put(prog);

		dev_xdp_set_link(dev, mode, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक dev_xdp_attach(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack,
			  काष्ठा bpf_xdp_link *link, काष्ठा bpf_prog *new_prog,
			  काष्ठा bpf_prog *old_prog, u32 flags)
अणु
	अचिन्हित पूर्णांक num_modes = hweight32(flags & XDP_FLAGS_MODES);
	काष्ठा bpf_prog *cur_prog;
	क्रमागत bpf_xdp_mode mode;
	bpf_op_t bpf_op;
	पूर्णांक err;

	ASSERT_RTNL();

	/* either link or prog attachment, never both */
	अगर (link && (new_prog || old_prog))
		वापस -EINVAL;
	/* link supports only XDP mode flags */
	अगर (link && (flags & ~XDP_FLAGS_MODES)) अणु
		NL_SET_ERR_MSG(extack, "Invalid XDP flags for BPF link attachment");
		वापस -EINVAL;
	पूर्ण
	/* just one XDP mode bit should be set, zero शेषs to drv/skb mode */
	अगर (num_modes > 1) अणु
		NL_SET_ERR_MSG(extack, "Only one XDP mode flag can be set");
		वापस -EINVAL;
	पूर्ण
	/* aव्योम ambiguity अगर offload + drv/skb mode progs are both loaded */
	अगर (!num_modes && dev_xdp_prog_count(dev) > 1) अणु
		NL_SET_ERR_MSG(extack,
			       "More than one program loaded, unset mode is ambiguous");
		वापस -EINVAL;
	पूर्ण
	/* old_prog != शून्य implies XDP_FLAGS_REPLACE is set */
	अगर (old_prog && !(flags & XDP_FLAGS_REPLACE)) अणु
		NL_SET_ERR_MSG(extack, "XDP_FLAGS_REPLACE is not specified");
		वापस -EINVAL;
	पूर्ण

	mode = dev_xdp_mode(dev, flags);
	/* can't replace attached link */
	अगर (dev_xdp_link(dev, mode)) अणु
		NL_SET_ERR_MSG(extack, "Can't replace active BPF XDP link");
		वापस -EBUSY;
	पूर्ण

	cur_prog = dev_xdp_prog(dev, mode);
	/* can't replace attached prog with link */
	अगर (link && cur_prog) अणु
		NL_SET_ERR_MSG(extack, "Can't replace active XDP program with BPF link");
		वापस -EBUSY;
	पूर्ण
	अगर ((flags & XDP_FLAGS_REPLACE) && cur_prog != old_prog) अणु
		NL_SET_ERR_MSG(extack, "Active program does not match expected");
		वापस -EEXIST;
	पूर्ण

	/* put effective new program पूर्णांकo new_prog */
	अगर (link)
		new_prog = link->link.prog;

	अगर (new_prog) अणु
		bool offload = mode == XDP_MODE_HW;
		क्रमागत bpf_xdp_mode other_mode = mode == XDP_MODE_SKB
					       ? XDP_MODE_DRV : XDP_MODE_SKB;

		अगर ((flags & XDP_FLAGS_UPDATE_IF_NOEXIST) && cur_prog) अणु
			NL_SET_ERR_MSG(extack, "XDP program already attached");
			वापस -EBUSY;
		पूर्ण
		अगर (!offload && dev_xdp_prog(dev, other_mode)) अणु
			NL_SET_ERR_MSG(extack, "Native and generic XDP can't be active at the same time");
			वापस -EEXIST;
		पूर्ण
		अगर (!offload && bpf_prog_is_dev_bound(new_prog->aux)) अणु
			NL_SET_ERR_MSG(extack, "Using device-bound program without HW_MODE flag is not supported");
			वापस -EINVAL;
		पूर्ण
		अगर (new_prog->expected_attach_type == BPF_XDP_DEVMAP) अणु
			NL_SET_ERR_MSG(extack, "BPF_XDP_DEVMAP programs can not be attached to a device");
			वापस -EINVAL;
		पूर्ण
		अगर (new_prog->expected_attach_type == BPF_XDP_CPUMAP) अणु
			NL_SET_ERR_MSG(extack, "BPF_XDP_CPUMAP programs can not be attached to a device");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* करोn't call drivers if the effective program didn't change */
	अगर (new_prog != cur_prog) अणु
		bpf_op = dev_xdp_bpf_op(dev, mode);
		अगर (!bpf_op) अणु
			NL_SET_ERR_MSG(extack, "Underlying driver does not support XDP in native mode");
			वापस -EOPNOTSUPP;
		पूर्ण

		err = dev_xdp_install(dev, mode, bpf_op, extack, flags, new_prog);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (link)
		dev_xdp_set_link(dev, mode, link);
	अन्यथा
		dev_xdp_set_prog(dev, mode, new_prog);
	अगर (cur_prog)
		bpf_prog_put(cur_prog);

	वापस 0;
पूर्ण

अटल पूर्णांक dev_xdp_attach_link(काष्ठा net_device *dev,
			       काष्ठा netlink_ext_ack *extack,
			       काष्ठा bpf_xdp_link *link)
अणु
	वापस dev_xdp_attach(dev, extack, link, शून्य, शून्य, link->flags);
पूर्ण

अटल पूर्णांक dev_xdp_detach_link(काष्ठा net_device *dev,
			       काष्ठा netlink_ext_ack *extack,
			       काष्ठा bpf_xdp_link *link)
अणु
	क्रमागत bpf_xdp_mode mode;
	bpf_op_t bpf_op;

	ASSERT_RTNL();

	mode = dev_xdp_mode(dev, link->flags);
	अगर (dev_xdp_link(dev, mode) != link)
		वापस -EINVAL;

	bpf_op = dev_xdp_bpf_op(dev, mode);
	WARN_ON(dev_xdp_install(dev, mode, bpf_op, शून्य, 0, शून्य));
	dev_xdp_set_link(dev, mode, शून्य);
	वापस 0;
पूर्ण

अटल व्योम bpf_xdp_link_release(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_xdp_link *xdp_link = container_of(link, काष्ठा bpf_xdp_link, link);

	rtnl_lock();

	/* अगर racing with net_device's tear करोwn, xdp_link->dev might be
	 * alपढ़ोy शून्य, in which हाल link was alपढ़ोy स्वतः-detached
	 */
	अगर (xdp_link->dev) अणु
		WARN_ON(dev_xdp_detach_link(xdp_link->dev, शून्य, xdp_link));
		xdp_link->dev = शून्य;
	पूर्ण

	rtnl_unlock();
पूर्ण

अटल पूर्णांक bpf_xdp_link_detach(काष्ठा bpf_link *link)
अणु
	bpf_xdp_link_release(link);
	वापस 0;
पूर्ण

अटल व्योम bpf_xdp_link_dealloc(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_xdp_link *xdp_link = container_of(link, काष्ठा bpf_xdp_link, link);

	kमुक्त(xdp_link);
पूर्ण

अटल व्योम bpf_xdp_link_show_fdinfo(स्थिर काष्ठा bpf_link *link,
				     काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_xdp_link *xdp_link = container_of(link, काष्ठा bpf_xdp_link, link);
	u32 अगरindex = 0;

	rtnl_lock();
	अगर (xdp_link->dev)
		अगरindex = xdp_link->dev->अगरindex;
	rtnl_unlock();

	seq_म_लिखो(seq, "ifindex:\t%u\n", अगरindex);
पूर्ण

अटल पूर्णांक bpf_xdp_link_fill_link_info(स्थिर काष्ठा bpf_link *link,
				       काष्ठा bpf_link_info *info)
अणु
	काष्ठा bpf_xdp_link *xdp_link = container_of(link, काष्ठा bpf_xdp_link, link);
	u32 अगरindex = 0;

	rtnl_lock();
	अगर (xdp_link->dev)
		अगरindex = xdp_link->dev->अगरindex;
	rtnl_unlock();

	info->xdp.अगरindex = अगरindex;
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_xdp_link_update(काष्ठा bpf_link *link, काष्ठा bpf_prog *new_prog,
			       काष्ठा bpf_prog *old_prog)
अणु
	काष्ठा bpf_xdp_link *xdp_link = container_of(link, काष्ठा bpf_xdp_link, link);
	क्रमागत bpf_xdp_mode mode;
	bpf_op_t bpf_op;
	पूर्णांक err = 0;

	rtnl_lock();

	/* link might have been स्वतः-released alपढ़ोy, so fail */
	अगर (!xdp_link->dev) अणु
		err = -ENOLINK;
		जाओ out_unlock;
	पूर्ण

	अगर (old_prog && link->prog != old_prog) अणु
		err = -EPERM;
		जाओ out_unlock;
	पूर्ण
	old_prog = link->prog;
	अगर (old_prog == new_prog) अणु
		/* no-op, करोn't disturb drivers */
		bpf_prog_put(new_prog);
		जाओ out_unlock;
	पूर्ण

	mode = dev_xdp_mode(xdp_link->dev, xdp_link->flags);
	bpf_op = dev_xdp_bpf_op(xdp_link->dev, mode);
	err = dev_xdp_install(xdp_link->dev, mode, bpf_op, शून्य,
			      xdp_link->flags, new_prog);
	अगर (err)
		जाओ out_unlock;

	old_prog = xchg(&link->prog, new_prog);
	bpf_prog_put(old_prog);

out_unlock:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल स्थिर काष्ठा bpf_link_ops bpf_xdp_link_lops = अणु
	.release = bpf_xdp_link_release,
	.dealloc = bpf_xdp_link_dealloc,
	.detach = bpf_xdp_link_detach,
	.show_fdinfo = bpf_xdp_link_show_fdinfo,
	.fill_link_info = bpf_xdp_link_fill_link_info,
	.update_prog = bpf_xdp_link_update,
पूर्ण;

पूर्णांक bpf_xdp_link_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	काष्ठा bpf_link_primer link_primer;
	काष्ठा bpf_xdp_link *link;
	काष्ठा net_device *dev;
	पूर्णांक err, fd;

	dev = dev_get_by_index(net, attr->link_create.target_अगरindex);
	अगर (!dev)
		वापस -EINVAL;

	link = kzalloc(माप(*link), GFP_USER);
	अगर (!link) अणु
		err = -ENOMEM;
		जाओ out_put_dev;
	पूर्ण

	bpf_link_init(&link->link, BPF_LINK_TYPE_XDP, &bpf_xdp_link_lops, prog);
	link->dev = dev;
	link->flags = attr->link_create.flags;

	err = bpf_link_prime(&link->link, &link_primer);
	अगर (err) अणु
		kमुक्त(link);
		जाओ out_put_dev;
	पूर्ण

	rtnl_lock();
	err = dev_xdp_attach_link(dev, शून्य, link);
	rtnl_unlock();

	अगर (err) अणु
		bpf_link_cleanup(&link_primer);
		जाओ out_put_dev;
	पूर्ण

	fd = bpf_link_settle(&link_primer);
	/* link itself करोesn't hold dev's refcnt to not complicate shutकरोwn */
	dev_put(dev);
	वापस fd;

out_put_dev:
	dev_put(dev);
	वापस err;
पूर्ण

/**
 *	dev_change_xdp_fd - set or clear a bpf program क्रम a device rx path
 *	@dev: device
 *	@extack: netlink extended ack
 *	@fd: new program fd or negative value to clear
 *	@expected_fd: old program fd that userspace expects to replace or clear
 *	@flags: xdp-related flags
 *
 *	Set or clear a bpf program क्रम a device
 */
पूर्णांक dev_change_xdp_fd(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack,
		      पूर्णांक fd, पूर्णांक expected_fd, u32 flags)
अणु
	क्रमागत bpf_xdp_mode mode = dev_xdp_mode(dev, flags);
	काष्ठा bpf_prog *new_prog = शून्य, *old_prog = शून्य;
	पूर्णांक err;

	ASSERT_RTNL();

	अगर (fd >= 0) अणु
		new_prog = bpf_prog_get_type_dev(fd, BPF_PROG_TYPE_XDP,
						 mode != XDP_MODE_SKB);
		अगर (IS_ERR(new_prog))
			वापस PTR_ERR(new_prog);
	पूर्ण

	अगर (expected_fd >= 0) अणु
		old_prog = bpf_prog_get_type_dev(expected_fd, BPF_PROG_TYPE_XDP,
						 mode != XDP_MODE_SKB);
		अगर (IS_ERR(old_prog)) अणु
			err = PTR_ERR(old_prog);
			old_prog = शून्य;
			जाओ err_out;
		पूर्ण
	पूर्ण

	err = dev_xdp_attach(dev, extack, शून्य, new_prog, old_prog, flags);

err_out:
	अगर (err && new_prog)
		bpf_prog_put(new_prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);
	वापस err;
पूर्ण

/**
 *	dev_new_index	-	allocate an अगरindex
 *	@net: the applicable net namespace
 *
 *	Returns a suitable unique value क्रम a new device पूर्णांकerface
 *	number.  The caller must hold the rtnl semaphore or the
 *	dev_base_lock to be sure it reमुख्यs unique.
 */
अटल पूर्णांक dev_new_index(काष्ठा net *net)
अणु
	पूर्णांक अगरindex = net->अगरindex;

	क्रम (;;) अणु
		अगर (++अगरindex <= 0)
			अगरindex = 1;
		अगर (!__dev_get_by_index(net, अगरindex))
			वापस net->अगरindex = अगरindex;
	पूर्ण
पूर्ण

/* Delayed registration/unरेजिस्टरation */
अटल LIST_HEAD(net_toकरो_list);
DECLARE_WAIT_QUEUE_HEAD(netdev_unरेजिस्टरing_wq);

अटल व्योम net_set_toकरो(काष्ठा net_device *dev)
अणु
	list_add_tail(&dev->toकरो_list, &net_toकरो_list);
	dev_net(dev)->dev_unreg_count++;
पूर्ण

अटल netdev_features_t netdev_sync_upper_features(काष्ठा net_device *lower,
	काष्ठा net_device *upper, netdev_features_t features)
अणु
	netdev_features_t upper_disables = NETIF_F_UPPER_DISABLES;
	netdev_features_t feature;
	पूर्णांक feature_bit;

	क्रम_each_netdev_feature(upper_disables, feature_bit) अणु
		feature = __NETIF_F_BIT(feature_bit);
		अगर (!(upper->wanted_features & feature)
		    && (features & feature)) अणु
			netdev_dbg(lower, "Dropping feature %pNF, upper dev %s has it off.\n",
				   &feature, upper->name);
			features &= ~feature;
		पूर्ण
	पूर्ण

	वापस features;
पूर्ण

अटल व्योम netdev_sync_lower_features(काष्ठा net_device *upper,
	काष्ठा net_device *lower, netdev_features_t features)
अणु
	netdev_features_t upper_disables = NETIF_F_UPPER_DISABLES;
	netdev_features_t feature;
	पूर्णांक feature_bit;

	क्रम_each_netdev_feature(upper_disables, feature_bit) अणु
		feature = __NETIF_F_BIT(feature_bit);
		अगर (!(features & feature) && (lower->features & feature)) अणु
			netdev_dbg(upper, "Disabling feature %pNF on lower dev %s.\n",
				   &feature, lower->name);
			lower->wanted_features &= ~feature;
			__netdev_update_features(lower);

			अगर (unlikely(lower->features & feature))
				netdev_WARN(upper, "failed to disable %pNF on %s!\n",
					    &feature, lower->name);
			अन्यथा
				netdev_features_change(lower);
		पूर्ण
	पूर्ण
पूर्ण

अटल netdev_features_t netdev_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	/* Fix illegal checksum combinations */
	अगर ((features & NETIF_F_HW_CSUM) &&
	    (features & (NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM))) अणु
		netdev_warn(dev, "mixed HW and IP checksum settings.\n");
		features &= ~(NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM);
	पूर्ण

	/* TSO requires that SG is present as well. */
	अगर ((features & NETIF_F_ALL_TSO) && !(features & NETIF_F_SG)) अणु
		netdev_dbg(dev, "Dropping TSO features since no SG feature.\n");
		features &= ~NETIF_F_ALL_TSO;
	पूर्ण

	अगर ((features & NETIF_F_TSO) && !(features & NETIF_F_HW_CSUM) &&
					!(features & NETIF_F_IP_CSUM)) अणु
		netdev_dbg(dev, "Dropping TSO features since no CSUM feature.\n");
		features &= ~NETIF_F_TSO;
		features &= ~NETIF_F_TSO_ECN;
	पूर्ण

	अगर ((features & NETIF_F_TSO6) && !(features & NETIF_F_HW_CSUM) &&
					 !(features & NETIF_F_IPV6_CSUM)) अणु
		netdev_dbg(dev, "Dropping TSO6 features since no CSUM feature.\n");
		features &= ~NETIF_F_TSO6;
	पूर्ण

	/* TSO with IPv4 ID mangling requires IPv4 TSO be enabled */
	अगर ((features & NETIF_F_TSO_MANGLEID) && !(features & NETIF_F_TSO))
		features &= ~NETIF_F_TSO_MANGLEID;

	/* TSO ECN requires that TSO is present as well. */
	अगर ((features & NETIF_F_ALL_TSO) == NETIF_F_TSO_ECN)
		features &= ~NETIF_F_TSO_ECN;

	/* Software GSO depends on SG. */
	अगर ((features & NETIF_F_GSO) && !(features & NETIF_F_SG)) अणु
		netdev_dbg(dev, "Dropping NETIF_F_GSO since no SG feature.\n");
		features &= ~NETIF_F_GSO;
	पूर्ण

	/* GSO partial features require GSO partial be set */
	अगर ((features & dev->gso_partial_features) &&
	    !(features & NETIF_F_GSO_PARTIAL)) अणु
		netdev_dbg(dev,
			   "Dropping partially supported GSO features since no GSO partial.\n");
		features &= ~dev->gso_partial_features;
	पूर्ण

	अगर (!(features & NETIF_F_RXCSUM)) अणु
		/* NETIF_F_GRO_HW implies करोing RXCSUM since every packet
		 * successfully merged by hardware must also have the
		 * checksum verअगरied by hardware.  If the user करोes not
		 * want to enable RXCSUM, logically, we should disable GRO_HW.
		 */
		अगर (features & NETIF_F_GRO_HW) अणु
			netdev_dbg(dev, "Dropping NETIF_F_GRO_HW since no RXCSUM feature.\n");
			features &= ~NETIF_F_GRO_HW;
		पूर्ण
	पूर्ण

	/* LRO/HW-GRO features cannot be combined with RX-FCS */
	अगर (features & NETIF_F_RXFCS) अणु
		अगर (features & NETIF_F_LRO) अणु
			netdev_dbg(dev, "Dropping LRO feature since RX-FCS is requested.\n");
			features &= ~NETIF_F_LRO;
		पूर्ण

		अगर (features & NETIF_F_GRO_HW) अणु
			netdev_dbg(dev, "Dropping HW-GRO feature since RX-FCS is requested.\n");
			features &= ~NETIF_F_GRO_HW;
		पूर्ण
	पूर्ण

	अगर (features & NETIF_F_HW_TLS_TX) अणु
		bool ip_csum = (features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) ==
			(NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM);
		bool hw_csum = features & NETIF_F_HW_CSUM;

		अगर (!ip_csum && !hw_csum) अणु
			netdev_dbg(dev, "Dropping TLS TX HW offload feature since no CSUM feature.\n");
			features &= ~NETIF_F_HW_TLS_TX;
		पूर्ण
	पूर्ण

	अगर ((features & NETIF_F_HW_TLS_RX) && !(features & NETIF_F_RXCSUM)) अणु
		netdev_dbg(dev, "Dropping TLS RX HW offload feature since no RXCSUM feature.\n");
		features &= ~NETIF_F_HW_TLS_RX;
	पूर्ण

	वापस features;
पूर्ण

पूर्णांक __netdev_update_features(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *upper, *lower;
	netdev_features_t features;
	काष्ठा list_head *iter;
	पूर्णांक err = -1;

	ASSERT_RTNL();

	features = netdev_get_wanted_features(dev);

	अगर (dev->netdev_ops->nकरो_fix_features)
		features = dev->netdev_ops->nकरो_fix_features(dev, features);

	/* driver might be less strict about feature dependencies */
	features = netdev_fix_features(dev, features);

	/* some features can't be enabled if they're off on an upper device */
	netdev_क्रम_each_upper_dev_rcu(dev, upper, iter)
		features = netdev_sync_upper_features(dev, upper, features);

	अगर (dev->features == features)
		जाओ sync_lower;

	netdev_dbg(dev, "Features changed: %pNF -> %pNF\n",
		&dev->features, &features);

	अगर (dev->netdev_ops->nकरो_set_features)
		err = dev->netdev_ops->nकरो_set_features(dev, features);
	अन्यथा
		err = 0;

	अगर (unlikely(err < 0)) अणु
		netdev_err(dev,
			"set_features() failed (%d); wanted %pNF, left %pNF\n",
			err, &features, &dev->features);
		/* वापस non-0 since some features might have changed and
		 * it's better to fire a spurious notअगरication than miss it
		 */
		वापस -1;
	पूर्ण

sync_lower:
	/* some features must be disabled on lower devices when disabled
	 * on an upper device (think: bonding master or bridge)
	 */
	netdev_क्रम_each_lower_dev(dev, lower, iter)
		netdev_sync_lower_features(dev, lower, features);

	अगर (!err) अणु
		netdev_features_t dअगरf = features ^ dev->features;

		अगर (dअगरf & NETIF_F_RX_UDP_TUNNEL_PORT) अणु
			/* udp_tunnel_अणुget,dropपूर्ण_rx_info both need
			 * NETIF_F_RX_UDP_TUNNEL_PORT enabled on the
			 * device, or they won't करो anything.
			 * Thus we need to update dev->features
			 * *beक्रमe* calling udp_tunnel_get_rx_info,
			 * but *after* calling udp_tunnel_drop_rx_info.
			 */
			अगर (features & NETIF_F_RX_UDP_TUNNEL_PORT) अणु
				dev->features = features;
				udp_tunnel_get_rx_info(dev);
			पूर्ण अन्यथा अणु
				udp_tunnel_drop_rx_info(dev);
			पूर्ण
		पूर्ण

		अगर (dअगरf & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
			अगर (features & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
				dev->features = features;
				err |= vlan_get_rx_ctag_filter_info(dev);
			पूर्ण अन्यथा अणु
				vlan_drop_rx_ctag_filter_info(dev);
			पूर्ण
		पूर्ण

		अगर (dअगरf & NETIF_F_HW_VLAN_STAG_FILTER) अणु
			अगर (features & NETIF_F_HW_VLAN_STAG_FILTER) अणु
				dev->features = features;
				err |= vlan_get_rx_stag_filter_info(dev);
			पूर्ण अन्यथा अणु
				vlan_drop_rx_stag_filter_info(dev);
			पूर्ण
		पूर्ण

		dev->features = features;
	पूर्ण

	वापस err < 0 ? 0 : 1;
पूर्ण

/**
 *	netdev_update_features - recalculate device features
 *	@dev: the device to check
 *
 *	Recalculate dev->features set and send notअगरications अगर it
 *	has changed. Should be called after driver or hardware dependent
 *	conditions might have changed that influence the features.
 */
व्योम netdev_update_features(काष्ठा net_device *dev)
अणु
	अगर (__netdev_update_features(dev))
		netdev_features_change(dev);
पूर्ण
EXPORT_SYMBOL(netdev_update_features);

/**
 *	netdev_change_features - recalculate device features
 *	@dev: the device to check
 *
 *	Recalculate dev->features set and send notअगरications even
 *	अगर they have not changed. Should be called instead of
 *	netdev_update_features() अगर also dev->vlan_features might
 *	have changed to allow the changes to be propagated to stacked
 *	VLAN devices.
 */
व्योम netdev_change_features(काष्ठा net_device *dev)
अणु
	__netdev_update_features(dev);
	netdev_features_change(dev);
पूर्ण
EXPORT_SYMBOL(netdev_change_features);

/**
 *	netअगर_stacked_transfer_operstate -	transfer operstate
 *	@rootdev: the root or lower level device to transfer state from
 *	@dev: the device to transfer operstate to
 *
 *	Transfer operational state from root to device. This is normally
 *	called when a stacking relationship exists between the root
 *	device and the device(a leaf device).
 */
व्योम netअगर_stacked_transfer_operstate(स्थिर काष्ठा net_device *rootdev,
					काष्ठा net_device *dev)
अणु
	अगर (rootdev->operstate == IF_OPER_DORMANT)
		netअगर_करोrmant_on(dev);
	अन्यथा
		netअगर_करोrmant_off(dev);

	अगर (rootdev->operstate == IF_OPER_TESTING)
		netअगर_testing_on(dev);
	अन्यथा
		netअगर_testing_off(dev);

	अगर (netअगर_carrier_ok(rootdev))
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);
पूर्ण
EXPORT_SYMBOL(netअगर_stacked_transfer_operstate);

अटल पूर्णांक netअगर_alloc_rx_queues(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i, count = dev->num_rx_queues;
	काष्ठा netdev_rx_queue *rx;
	माप_प्रकार sz = count * माप(*rx);
	पूर्णांक err = 0;

	BUG_ON(count < 1);

	rx = kvzalloc(sz, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	अगर (!rx)
		वापस -ENOMEM;

	dev->_rx = rx;

	क्रम (i = 0; i < count; i++) अणु
		rx[i].dev = dev;

		/* XDP RX-queue setup */
		err = xdp_rxq_info_reg(&rx[i].xdp_rxq, dev, i, 0);
		अगर (err < 0)
			जाओ err_rxq_info;
	पूर्ण
	वापस 0;

err_rxq_info:
	/* Rollback successful reg's and मुक्त other resources */
	जबतक (i--)
		xdp_rxq_info_unreg(&rx[i].xdp_rxq);
	kvमुक्त(dev->_rx);
	dev->_rx = शून्य;
	वापस err;
पूर्ण

अटल व्योम netअगर_मुक्त_rx_queues(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i, count = dev->num_rx_queues;

	/* netअगर_alloc_rx_queues alloc failed, resources have been unreg'ed */
	अगर (!dev->_rx)
		वापस;

	क्रम (i = 0; i < count; i++)
		xdp_rxq_info_unreg(&dev->_rx[i].xdp_rxq);

	kvमुक्त(dev->_rx);
पूर्ण

अटल व्योम netdev_init_one_queue(काष्ठा net_device *dev,
				  काष्ठा netdev_queue *queue, व्योम *_unused)
अणु
	/* Initialize queue lock */
	spin_lock_init(&queue->_xmit_lock);
	netdev_set_xmit_lockdep_class(&queue->_xmit_lock, dev->type);
	queue->xmit_lock_owner = -1;
	netdev_queue_numa_node_ग_लिखो(queue, NUMA_NO_NODE);
	queue->dev = dev;
#अगर_घोषित CONFIG_BQL
	dql_init(&queue->dql, HZ);
#पूर्ण_अगर
पूर्ण

अटल व्योम netअगर_मुक्त_tx_queues(काष्ठा net_device *dev)
अणु
	kvमुक्त(dev->_tx);
पूर्ण

अटल पूर्णांक netअगर_alloc_netdev_queues(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक count = dev->num_tx_queues;
	काष्ठा netdev_queue *tx;
	माप_प्रकार sz = count * माप(*tx);

	अगर (count < 1 || count > 0xffff)
		वापस -EINVAL;

	tx = kvzalloc(sz, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	अगर (!tx)
		वापस -ENOMEM;

	dev->_tx = tx;

	netdev_क्रम_each_tx_queue(dev, netdev_init_one_queue, शून्य);
	spin_lock_init(&dev->tx_global_lock);

	वापस 0;
पूर्ण

व्योम netअगर_tx_stop_all_queues(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);

		netअगर_tx_stop_queue(txq);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netअगर_tx_stop_all_queues);

/**
 *	रेजिस्टर_netdevice	- रेजिस्टर a network device
 *	@dev: device to रेजिस्टर
 *
 *	Take a completed network device काष्ठाure and add it to the kernel
 *	पूर्णांकerfaces. A %NETDEV_REGISTER message is sent to the netdev notअगरier
 *	chain. 0 is वापसed on success. A negative त्रुटि_सं code is वापसed
 *	on a failure to set up the device, or अगर the name is a duplicate.
 *
 *	Callers must hold the rtnl semaphore. You may want
 *	रेजिस्टर_netdev() instead of this.
 *
 *	BUGS:
 *	The locking appears insufficient to guarantee two parallel रेजिस्टरs
 *	will not get the same name.
 */

पूर्णांक रेजिस्टर_netdevice(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा net *net = dev_net(dev);

	BUILD_BUG_ON(माप(netdev_features_t) * BITS_PER_BYTE <
		     NETDEV_FEATURE_COUNT);
	BUG_ON(dev_boot_phase);
	ASSERT_RTNL();

	might_sleep();

	/* When net_device's are persistent, this will be fatal. */
	BUG_ON(dev->reg_state != NETREG_UNINITIALIZED);
	BUG_ON(!net);

	ret = ethtool_check_ops(dev->ethtool_ops);
	अगर (ret)
		वापस ret;

	spin_lock_init(&dev->addr_list_lock);
	netdev_set_addr_lockdep_class(dev);

	ret = dev_get_valid_name(net, dev, dev->name);
	अगर (ret < 0)
		जाओ out;

	ret = -ENOMEM;
	dev->name_node = netdev_name_node_head_alloc(dev);
	अगर (!dev->name_node)
		जाओ out;

	/* Init, अगर this function is available */
	अगर (dev->netdev_ops->nकरो_init) अणु
		ret = dev->netdev_ops->nकरो_init(dev);
		अगर (ret) अणु
			अगर (ret > 0)
				ret = -EIO;
			जाओ err_मुक्त_name;
		पूर्ण
	पूर्ण

	अगर (((dev->hw_features | dev->features) &
	     NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    (!dev->netdev_ops->nकरो_vlan_rx_add_vid ||
	     !dev->netdev_ops->nकरो_vlan_rx_समाप्त_vid)) अणु
		netdev_WARN(dev, "Buggy VLAN acceleration in driver!\n");
		ret = -EINVAL;
		जाओ err_uninit;
	पूर्ण

	ret = -EBUSY;
	अगर (!dev->अगरindex)
		dev->अगरindex = dev_new_index(net);
	अन्यथा अगर (__dev_get_by_index(net, dev->अगरindex))
		जाओ err_uninit;

	/* Transfer changeable features to wanted_features and enable
	 * software offloads (GSO and GRO).
	 */
	dev->hw_features |= (NETIF_F_SOFT_FEATURES | NETIF_F_SOFT_FEATURES_OFF);
	dev->features |= NETIF_F_SOFT_FEATURES;

	अगर (dev->udp_tunnel_nic_info) अणु
		dev->features |= NETIF_F_RX_UDP_TUNNEL_PORT;
		dev->hw_features |= NETIF_F_RX_UDP_TUNNEL_PORT;
	पूर्ण

	dev->wanted_features = dev->features & dev->hw_features;

	अगर (!(dev->flags & IFF_LOOPBACK))
		dev->hw_features |= NETIF_F_NOCACHE_COPY;

	/* If IPv4 TCP segmentation offload is supported we should also
	 * allow the device to enable segmenting the frame with the option
	 * of ignoring a अटल IP ID value.  This करोesn't enable the
	 * feature itself but allows the user to enable it later.
	 */
	अगर (dev->hw_features & NETIF_F_TSO)
		dev->hw_features |= NETIF_F_TSO_MANGLEID;
	अगर (dev->vlan_features & NETIF_F_TSO)
		dev->vlan_features |= NETIF_F_TSO_MANGLEID;
	अगर (dev->mpls_features & NETIF_F_TSO)
		dev->mpls_features |= NETIF_F_TSO_MANGLEID;
	अगर (dev->hw_enc_features & NETIF_F_TSO)
		dev->hw_enc_features |= NETIF_F_TSO_MANGLEID;

	/* Make NETIF_F_HIGHDMA inheritable to VLAN devices.
	 */
	dev->vlan_features |= NETIF_F_HIGHDMA;

	/* Make NETIF_F_SG inheritable to tunnel devices.
	 */
	dev->hw_enc_features |= NETIF_F_SG | NETIF_F_GSO_PARTIAL;

	/* Make NETIF_F_SG inheritable to MPLS.
	 */
	dev->mpls_features |= NETIF_F_SG;

	ret = call_netdevice_notअगरiers(NETDEV_POST_INIT, dev);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret)
		जाओ err_uninit;

	ret = netdev_रेजिस्टर_kobject(dev);
	अगर (ret) अणु
		dev->reg_state = NETREG_UNREGISTERED;
		जाओ err_uninit;
	पूर्ण
	dev->reg_state = NETREG_REGISTERED;

	__netdev_update_features(dev);

	/*
	 *	Default initial state at registry is that the
	 *	device is present.
	 */

	set_bit(__LINK_STATE_PRESENT, &dev->state);

	linkwatch_init_dev(dev);

	dev_init_scheduler(dev);
	dev_hold(dev);
	list_netdevice(dev);
	add_device_अक्रमomness(dev->dev_addr, dev->addr_len);

	/* If the device has permanent device address, driver should
	 * set dev_addr and also addr_assign_type should be set to
	 * NET_ADDR_PERM (शेष value).
	 */
	अगर (dev->addr_assign_type == NET_ADDR_PERM)
		स_नकल(dev->perm_addr, dev->dev_addr, dev->addr_len);

	/* Notअगरy protocols, that a new device appeared. */
	ret = call_netdevice_notअगरiers(NETDEV_REGISTER, dev);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret) अणु
		/* Expect explicit मुक्त_netdev() on failure */
		dev->needs_मुक्त_netdev = false;
		unरेजिस्टर_netdevice_queue(dev, शून्य);
		जाओ out;
	पूर्ण
	/*
	 *	Prevent userspace races by रुकोing until the network
	 *	device is fully setup beक्रमe sending notअगरications.
	 */
	अगर (!dev->rtnl_link_ops ||
	    dev->rtnl_link_state == RTNL_LINK_INITIALIZED)
		rपंचांगsg_अगरinfo(RTM_NEWLINK, dev, ~0U, GFP_KERNEL);

out:
	वापस ret;

err_uninit:
	अगर (dev->netdev_ops->nकरो_uninit)
		dev->netdev_ops->nकरो_uninit(dev);
	अगर (dev->priv_deकाष्ठाor)
		dev->priv_deकाष्ठाor(dev);
err_मुक्त_name:
	netdev_name_node_मुक्त(dev->name_node);
	जाओ out;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_netdevice);

/**
 *	init_dummy_netdev	- init a dummy network device क्रम NAPI
 *	@dev: device to init
 *
 *	This takes a network device काष्ठाure and initialize the minimum
 *	amount of fields so it can be used to schedule NAPI polls without
 *	रेजिस्टरing a full blown पूर्णांकerface. This is to be used by drivers
 *	that need to tie several hardware पूर्णांकerfaces to a single NAPI
 *	poll scheduler due to HW limitations.
 */
पूर्णांक init_dummy_netdev(काष्ठा net_device *dev)
अणु
	/* Clear everything. Note we करोn't initialize spinlocks
	 * are they aren't supposed to be taken by any of the
	 * NAPI code and this dummy netdev is supposed to be
	 * only ever used क्रम NAPI polls
	 */
	स_रखो(dev, 0, माप(काष्ठा net_device));

	/* make sure we BUG अगर trying to hit standard
	 * रेजिस्टर/unरेजिस्टर code path
	 */
	dev->reg_state = NETREG_DUMMY;

	/* NAPI wants this */
	INIT_LIST_HEAD(&dev->napi_list);

	/* a dummy पूर्णांकerface is started by शेष */
	set_bit(__LINK_STATE_PRESENT, &dev->state);
	set_bit(__LINK_STATE_START, &dev->state);

	/* napi_busy_loop stats accounting wants this */
	dev_net_set(dev, &init_net);

	/* Note : We करोnt allocate pcpu_refcnt क्रम dummy devices,
	 * because users of this 'device' करोnt need to change
	 * its refcount.
	 */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(init_dummy_netdev);


/**
 *	रेजिस्टर_netdev	- रेजिस्टर a network device
 *	@dev: device to रेजिस्टर
 *
 *	Take a completed network device काष्ठाure and add it to the kernel
 *	पूर्णांकerfaces. A %NETDEV_REGISTER message is sent to the netdev notअगरier
 *	chain. 0 is वापसed on success. A negative त्रुटि_सं code is वापसed
 *	on a failure to set up the device, or अगर the name is a duplicate.
 *
 *	This is a wrapper around रेजिस्टर_netdevice that takes the rtnl semaphore
 *	and expands the device name अगर you passed a क्रमmat string to
 *	alloc_netdev.
 */
पूर्णांक रेजिस्टर_netdev(काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	अगर (rtnl_lock_समाप्तable())
		वापस -EINTR;
	err = रेजिस्टर_netdevice(dev);
	rtnl_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_netdev);

पूर्णांक netdev_refcnt_पढ़ो(स्थिर काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_PCPU_DEV_REFCNT
	पूर्णांक i, refcnt = 0;

	क्रम_each_possible_cpu(i)
		refcnt += *per_cpu_ptr(dev->pcpu_refcnt, i);
	वापस refcnt;
#अन्यथा
	वापस refcount_पढ़ो(&dev->dev_refcnt);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(netdev_refcnt_पढ़ो);

पूर्णांक netdev_unरेजिस्टर_समयout_secs __पढ़ो_mostly = 10;

#घोषणा WAIT_REFS_MIN_MSECS 1
#घोषणा WAIT_REFS_MAX_MSECS 250
/**
 * netdev_रुको_allrefs - रुको until all references are gone.
 * @dev: target net_device
 *
 * This is called when unरेजिस्टरing network devices.
 *
 * Any protocol or device that holds a reference should रेजिस्टर
 * क्रम netdevice notअगरication, and cleanup and put back the
 * reference अगर they receive an UNREGISTER event.
 * We can get stuck here अगर buggy protocols करोn't correctly
 * call dev_put.
 */
अटल व्योम netdev_रुको_allrefs(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ rebroadcast_समय, warning_समय;
	पूर्णांक रुको = 0, refcnt;

	linkwatch_क्रमget_dev(dev);

	rebroadcast_समय = warning_समय = jअगरfies;
	refcnt = netdev_refcnt_पढ़ो(dev);

	जबतक (refcnt != 1) अणु
		अगर (समय_after(jअगरfies, rebroadcast_समय + 1 * HZ)) अणु
			rtnl_lock();

			/* Rebroadcast unरेजिस्टर notअगरication */
			call_netdevice_notअगरiers(NETDEV_UNREGISTER, dev);

			__rtnl_unlock();
			rcu_barrier();
			rtnl_lock();

			अगर (test_bit(__LINK_STATE_LINKWATCH_PENDING,
				     &dev->state)) अणु
				/* We must not have linkwatch events
				 * pending on unरेजिस्टर. If this
				 * happens, we simply run the queue
				 * unscheduled, resulting in a noop
				 * क्रम this device.
				 */
				linkwatch_run_queue();
			पूर्ण

			__rtnl_unlock();

			rebroadcast_समय = jअगरfies;
		पूर्ण

		अगर (!रुको) अणु
			rcu_barrier();
			रुको = WAIT_REFS_MIN_MSECS;
		पूर्ण अन्यथा अणु
			msleep(रुको);
			रुको = min(रुको << 1, WAIT_REFS_MAX_MSECS);
		पूर्ण

		refcnt = netdev_refcnt_पढ़ो(dev);

		अगर (refcnt != 1 &&
		    समय_after(jअगरfies, warning_समय +
			       netdev_unरेजिस्टर_समयout_secs * HZ)) अणु
			pr_emerg("unregister_netdevice: waiting for %s to become free. Usage count = %d\n",
				 dev->name, refcnt);
			warning_समय = jअगरfies;
		पूर्ण
	पूर्ण
पूर्ण

/* The sequence is:
 *
 *	rtnl_lock();
 *	...
 *	रेजिस्टर_netdevice(x1);
 *	रेजिस्टर_netdevice(x2);
 *	...
 *	unरेजिस्टर_netdevice(y1);
 *	unरेजिस्टर_netdevice(y2);
 *      ...
 *	rtnl_unlock();
 *	मुक्त_netdev(y1);
 *	मुक्त_netdev(y2);
 *
 * We are invoked by rtnl_unlock().
 * This allows us to deal with problems:
 * 1) We can delete sysfs objects which invoke hotplug
 *    without deadlocking with linkwatch via keventd.
 * 2) Since we run with the RTNL semaphore not held, we can sleep
 *    safely in order to रुको क्रम the netdev refcnt to drop to zero.
 *
 * We must not वापस until all unरेजिस्टर events added during
 * the पूर्णांकerval the lock was held have been completed.
 */
व्योम netdev_run_toकरो(व्योम)
अणु
	काष्ठा list_head list;
#अगर_घोषित CONFIG_LOCKDEP
	काष्ठा list_head unlink_list;

	list_replace_init(&net_unlink_list, &unlink_list);

	जबतक (!list_empty(&unlink_list)) अणु
		काष्ठा net_device *dev = list_first_entry(&unlink_list,
							  काष्ठा net_device,
							  unlink_list);
		list_del_init(&dev->unlink_list);
		dev->nested_level = dev->lower_level - 1;
	पूर्ण
#पूर्ण_अगर

	/* Snapshot list, allow later requests */
	list_replace_init(&net_toकरो_list, &list);

	__rtnl_unlock();


	/* Wait क्रम rcu callbacks to finish beक्रमe next phase */
	अगर (!list_empty(&list))
		rcu_barrier();

	जबतक (!list_empty(&list)) अणु
		काष्ठा net_device *dev
			= list_first_entry(&list, काष्ठा net_device, toकरो_list);
		list_del(&dev->toकरो_list);

		अगर (unlikely(dev->reg_state != NETREG_UNREGISTERING)) अणु
			pr_err("network todo '%s' but state %d\n",
			       dev->name, dev->reg_state);
			dump_stack();
			जारी;
		पूर्ण

		dev->reg_state = NETREG_UNREGISTERED;

		netdev_रुको_allrefs(dev);

		/* paranoia */
		BUG_ON(netdev_refcnt_पढ़ो(dev) != 1);
		BUG_ON(!list_empty(&dev->ptype_all));
		BUG_ON(!list_empty(&dev->ptype_specअगरic));
		WARN_ON(rcu_access_poपूर्णांकer(dev->ip_ptr));
		WARN_ON(rcu_access_poपूर्णांकer(dev->ip6_ptr));
#अगर IS_ENABLED(CONFIG_DECNET)
		WARN_ON(dev->dn_ptr);
#पूर्ण_अगर
		अगर (dev->priv_deकाष्ठाor)
			dev->priv_deकाष्ठाor(dev);
		अगर (dev->needs_मुक्त_netdev)
			मुक्त_netdev(dev);

		/* Report a network device has been unरेजिस्टरed */
		rtnl_lock();
		dev_net(dev)->dev_unreg_count--;
		__rtnl_unlock();
		wake_up(&netdev_unरेजिस्टरing_wq);

		/* Free network device */
		kobject_put(&dev->dev.kobj);
	पूर्ण
पूर्ण

/* Convert net_device_stats to rtnl_link_stats64. rtnl_link_stats64 has
 * all the same fields in the same order as net_device_stats, with only
 * the type dअगरfering, but rtnl_link_stats64 may have additional fields
 * at the end क्रम newer counters.
 */
व्योम netdev_stats_to_stats64(काष्ठा rtnl_link_stats64 *stats64,
			     स्थिर काष्ठा net_device_stats *netdev_stats)
अणु
#अगर BITS_PER_LONG == 64
	BUILD_BUG_ON(माप(*stats64) < माप(*netdev_stats));
	स_नकल(stats64, netdev_stats, माप(*netdev_stats));
	/* zero out counters that only exist in rtnl_link_stats64 */
	स_रखो((अक्षर *)stats64 + माप(*netdev_stats), 0,
	       माप(*stats64) - माप(*netdev_stats));
#अन्यथा
	माप_प्रकार i, n = माप(*netdev_stats) / माप(अचिन्हित दीर्घ);
	स्थिर अचिन्हित दीर्घ *src = (स्थिर अचिन्हित दीर्घ *)netdev_stats;
	u64 *dst = (u64 *)stats64;

	BUILD_BUG_ON(n > माप(*stats64) / माप(u64));
	क्रम (i = 0; i < n; i++)
		dst[i] = src[i];
	/* zero out counters that only exist in rtnl_link_stats64 */
	स_रखो((अक्षर *)stats64 + n * माप(u64), 0,
	       माप(*stats64) - n * माप(u64));
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(netdev_stats_to_stats64);

/**
 *	dev_get_stats	- get network device statistics
 *	@dev: device to get statistics from
 *	@storage: place to store stats
 *
 *	Get network statistics from device. Return @storage.
 *	The device driver may provide its own method by setting
 *	dev->netdev_ops->get_stats64 or dev->netdev_ops->get_stats;
 *	otherwise the पूर्णांकernal statistics काष्ठाure is used.
 */
काष्ठा rtnl_link_stats64 *dev_get_stats(काष्ठा net_device *dev,
					काष्ठा rtnl_link_stats64 *storage)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	अगर (ops->nकरो_get_stats64) अणु
		स_रखो(storage, 0, माप(*storage));
		ops->nकरो_get_stats64(dev, storage);
	पूर्ण अन्यथा अगर (ops->nकरो_get_stats) अणु
		netdev_stats_to_stats64(storage, ops->nकरो_get_stats(dev));
	पूर्ण अन्यथा अणु
		netdev_stats_to_stats64(storage, &dev->stats);
	पूर्ण
	storage->rx_dropped += (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&dev->rx_dropped);
	storage->tx_dropped += (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&dev->tx_dropped);
	storage->rx_nohandler += (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&dev->rx_nohandler);
	वापस storage;
पूर्ण
EXPORT_SYMBOL(dev_get_stats);

/**
 *	dev_fetch_sw_netstats - get per-cpu network device statistics
 *	@s: place to store stats
 *	@netstats: per-cpu network stats to पढ़ो from
 *
 *	Read per-cpu network statistics and populate the related fields in @s.
 */
व्योम dev_fetch_sw_netstats(काष्ठा rtnl_link_stats64 *s,
			   स्थिर काष्ठा pcpu_sw_netstats __percpu *netstats)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		स्थिर काष्ठा pcpu_sw_netstats *stats;
		काष्ठा pcpu_sw_netstats पंचांगp;
		अचिन्हित पूर्णांक start;

		stats = per_cpu_ptr(netstats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			पंचांगp.rx_packets = stats->rx_packets;
			पंचांगp.rx_bytes   = stats->rx_bytes;
			पंचांगp.tx_packets = stats->tx_packets;
			पंचांगp.tx_bytes   = stats->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		s->rx_packets += पंचांगp.rx_packets;
		s->rx_bytes   += पंचांगp.rx_bytes;
		s->tx_packets += पंचांगp.tx_packets;
		s->tx_bytes   += पंचांगp.tx_bytes;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dev_fetch_sw_netstats);

/**
 *	dev_get_tstats64 - nकरो_get_stats64 implementation
 *	@dev: device to get statistics from
 *	@s: place to store stats
 *
 *	Populate @s from dev->stats and dev->tstats. Can be used as
 *	nकरो_get_stats64() callback.
 */
व्योम dev_get_tstats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *s)
अणु
	netdev_stats_to_stats64(s, &dev->stats);
	dev_fetch_sw_netstats(s, dev->tstats);
पूर्ण
EXPORT_SYMBOL_GPL(dev_get_tstats64);

काष्ठा netdev_queue *dev_ingress_queue_create(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_queue *queue = dev_ingress_queue(dev);

#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (queue)
		वापस queue;
	queue = kzalloc(माप(*queue), GFP_KERNEL);
	अगर (!queue)
		वापस शून्य;
	netdev_init_one_queue(dev, queue, शून्य);
	RCU_INIT_POINTER(queue->qdisc, &noop_qdisc);
	queue->qdisc_sleeping = &noop_qdisc;
	rcu_assign_poपूर्णांकer(dev->ingress_queue, queue);
#पूर्ण_अगर
	वापस queue;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops शेष_ethtool_ops;

व्योम netdev_set_शेष_ethtool_ops(काष्ठा net_device *dev,
				    स्थिर काष्ठा ethtool_ops *ops)
अणु
	अगर (dev->ethtool_ops == &शेष_ethtool_ops)
		dev->ethtool_ops = ops;
पूर्ण
EXPORT_SYMBOL_GPL(netdev_set_शेष_ethtool_ops);

व्योम netdev_मुक्तmem(काष्ठा net_device *dev)
अणु
	अक्षर *addr = (अक्षर *)dev - dev->padded;

	kvमुक्त(addr);
पूर्ण

/**
 * alloc_netdev_mqs - allocate network device
 * @माप_priv: size of निजी data to allocate space क्रम
 * @name: device name क्रमmat string
 * @name_assign_type: origin of device name
 * @setup: callback to initialize device
 * @txqs: the number of TX subqueues to allocate
 * @rxqs: the number of RX subqueues to allocate
 *
 * Allocates a काष्ठा net_device with निजी data area क्रम driver use
 * and perक्रमms basic initialization.  Also allocates subqueue काष्ठाs
 * क्रम each queue on the device.
 */
काष्ठा net_device *alloc_netdev_mqs(पूर्णांक माप_priv, स्थिर अक्षर *name,
		अचिन्हित अक्षर name_assign_type,
		व्योम (*setup)(काष्ठा net_device *),
		अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs)
अणु
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक alloc_size;
	काष्ठा net_device *p;

	BUG_ON(म_माप(name) >= माप(dev->name));

	अगर (txqs < 1) अणु
		pr_err("alloc_netdev: Unable to allocate device with zero queues\n");
		वापस शून्य;
	पूर्ण

	अगर (rxqs < 1) अणु
		pr_err("alloc_netdev: Unable to allocate device with zero RX queues\n");
		वापस शून्य;
	पूर्ण

	alloc_size = माप(काष्ठा net_device);
	अगर (माप_priv) अणु
		/* ensure 32-byte alignment of निजी area */
		alloc_size = ALIGN(alloc_size, NETDEV_ALIGN);
		alloc_size += माप_priv;
	पूर्ण
	/* ensure 32-byte alignment of whole स्थिरruct */
	alloc_size += NETDEV_ALIGN - 1;

	p = kvzalloc(alloc_size, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	अगर (!p)
		वापस शून्य;

	dev = PTR_ALIGN(p, NETDEV_ALIGN);
	dev->padded = (अक्षर *)dev - (अक्षर *)p;

#अगर_घोषित CONFIG_PCPU_DEV_REFCNT
	dev->pcpu_refcnt = alloc_percpu(पूर्णांक);
	अगर (!dev->pcpu_refcnt)
		जाओ मुक्त_dev;
	dev_hold(dev);
#अन्यथा
	refcount_set(&dev->dev_refcnt, 1);
#पूर्ण_अगर

	अगर (dev_addr_init(dev))
		जाओ मुक्त_pcpu;

	dev_mc_init(dev);
	dev_uc_init(dev);

	dev_net_set(dev, &init_net);

	dev->gso_max_size = GSO_MAX_SIZE;
	dev->gso_max_segs = GSO_MAX_SEGS;
	dev->upper_level = 1;
	dev->lower_level = 1;
#अगर_घोषित CONFIG_LOCKDEP
	dev->nested_level = 0;
	INIT_LIST_HEAD(&dev->unlink_list);
#पूर्ण_अगर

	INIT_LIST_HEAD(&dev->napi_list);
	INIT_LIST_HEAD(&dev->unreg_list);
	INIT_LIST_HEAD(&dev->बंद_list);
	INIT_LIST_HEAD(&dev->link_watch_list);
	INIT_LIST_HEAD(&dev->adj_list.upper);
	INIT_LIST_HEAD(&dev->adj_list.lower);
	INIT_LIST_HEAD(&dev->ptype_all);
	INIT_LIST_HEAD(&dev->ptype_specअगरic);
	INIT_LIST_HEAD(&dev->net_notअगरier_list);
#अगर_घोषित CONFIG_NET_SCHED
	hash_init(dev->qdisc_hash);
#पूर्ण_अगर
	dev->priv_flags = IFF_XMIT_DST_RELEASE | IFF_XMIT_DST_RELEASE_PERM;
	setup(dev);

	अगर (!dev->tx_queue_len) अणु
		dev->priv_flags |= IFF_NO_QUEUE;
		dev->tx_queue_len = DEFAULT_TX_QUEUE_LEN;
	पूर्ण

	dev->num_tx_queues = txqs;
	dev->real_num_tx_queues = txqs;
	अगर (netअगर_alloc_netdev_queues(dev))
		जाओ मुक्त_all;

	dev->num_rx_queues = rxqs;
	dev->real_num_rx_queues = rxqs;
	अगर (netअगर_alloc_rx_queues(dev))
		जाओ मुक्त_all;

	म_नकल(dev->name, name);
	dev->name_assign_type = name_assign_type;
	dev->group = INIT_NETDEV_GROUP;
	अगर (!dev->ethtool_ops)
		dev->ethtool_ops = &शेष_ethtool_ops;

	nf_hook_ingress_init(dev);

	वापस dev;

मुक्त_all:
	मुक्त_netdev(dev);
	वापस शून्य;

मुक्त_pcpu:
#अगर_घोषित CONFIG_PCPU_DEV_REFCNT
	मुक्त_percpu(dev->pcpu_refcnt);
मुक्त_dev:
#पूर्ण_अगर
	netdev_मुक्तmem(dev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(alloc_netdev_mqs);

/**
 * मुक्त_netdev - मुक्त network device
 * @dev: device
 *
 * This function करोes the last stage of destroying an allocated device
 * पूर्णांकerface. The reference to the device object is released. If this
 * is the last reference then it will be मुक्तd.Must be called in process
 * context.
 */
व्योम मुक्त_netdev(काष्ठा net_device *dev)
अणु
	काष्ठा napi_काष्ठा *p, *n;

	might_sleep();

	/* When called immediately after रेजिस्टर_netdevice() failed the unwind
	 * handling may still be dismantling the device. Handle that हाल by
	 * deferring the मुक्त.
	 */
	अगर (dev->reg_state == NETREG_UNREGISTERING) अणु
		ASSERT_RTNL();
		dev->needs_मुक्त_netdev = true;
		वापस;
	पूर्ण

	netअगर_मुक्त_tx_queues(dev);
	netअगर_मुक्त_rx_queues(dev);

	kमुक्त(rcu_dereference_रक्षित(dev->ingress_queue, 1));

	/* Flush device addresses */
	dev_addr_flush(dev);

	list_क्रम_each_entry_safe(p, n, &dev->napi_list, dev_list)
		netअगर_napi_del(p);

#अगर_घोषित CONFIG_PCPU_DEV_REFCNT
	मुक्त_percpu(dev->pcpu_refcnt);
	dev->pcpu_refcnt = शून्य;
#पूर्ण_अगर
	मुक्त_percpu(dev->xdp_bulkq);
	dev->xdp_bulkq = शून्य;

	/*  Compatibility with error handling in drivers */
	अगर (dev->reg_state == NETREG_UNINITIALIZED) अणु
		netdev_मुक्तmem(dev);
		वापस;
	पूर्ण

	BUG_ON(dev->reg_state != NETREG_UNREGISTERED);
	dev->reg_state = NETREG_RELEASED;

	/* will मुक्त via device release */
	put_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL(मुक्त_netdev);

/**
 *	synchronize_net -  Synchronize with packet receive processing
 *
 *	Wait क्रम packets currently being received to be करोne.
 *	Does not block later packets from starting.
 */
व्योम synchronize_net(व्योम)
अणु
	might_sleep();
	अगर (rtnl_is_locked())
		synchronize_rcu_expedited();
	अन्यथा
		synchronize_rcu();
पूर्ण
EXPORT_SYMBOL(synchronize_net);

/**
 *	unरेजिस्टर_netdevice_queue - हटाओ device from the kernel
 *	@dev: device
 *	@head: list
 *
 *	This function shuts करोwn a device पूर्णांकerface and हटाओs it
 *	from the kernel tables.
 *	If head not शून्य, device is queued to be unरेजिस्टरed later.
 *
 *	Callers must hold the rtnl semaphore.  You may want
 *	unरेजिस्टर_netdev() instead of this.
 */

व्योम unरेजिस्टर_netdevice_queue(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	ASSERT_RTNL();

	अगर (head) अणु
		list_move_tail(&dev->unreg_list, head);
	पूर्ण अन्यथा अणु
		LIST_HEAD(single);

		list_add(&dev->unreg_list, &single);
		unरेजिस्टर_netdevice_many(&single);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_netdevice_queue);

/**
 *	unरेजिस्टर_netdevice_many - unरेजिस्टर many devices
 *	@head: list of devices
 *
 *  Note: As most callers use a stack allocated list_head,
 *  we क्रमce a list_del() to make sure stack wont be corrupted later.
 */
व्योम unरेजिस्टर_netdevice_many(काष्ठा list_head *head)
अणु
	काष्ठा net_device *dev, *पंचांगp;
	LIST_HEAD(बंद_head);

	BUG_ON(dev_boot_phase);
	ASSERT_RTNL();

	अगर (list_empty(head))
		वापस;

	list_क्रम_each_entry_safe(dev, पंचांगp, head, unreg_list) अणु
		/* Some devices call without रेजिस्टरing
		 * क्रम initialization unwind. Remove those
		 * devices and proceed with the reमुख्यing.
		 */
		अगर (dev->reg_state == NETREG_UNINITIALIZED) अणु
			pr_debug("unregister_netdevice: device %s/%p never was registered\n",
				 dev->name, dev);

			WARN_ON(1);
			list_del(&dev->unreg_list);
			जारी;
		पूर्ण
		dev->dismantle = true;
		BUG_ON(dev->reg_state != NETREG_REGISTERED);
	पूर्ण

	/* If device is running, बंद it first. */
	list_क्रम_each_entry(dev, head, unreg_list)
		list_add_tail(&dev->बंद_list, &बंद_head);
	dev_बंद_many(&बंद_head, true);

	list_क्रम_each_entry(dev, head, unreg_list) अणु
		/* And unlink it from device chain. */
		unlist_netdevice(dev);

		dev->reg_state = NETREG_UNREGISTERING;
	पूर्ण
	flush_all_backlogs();

	synchronize_net();

	list_क्रम_each_entry(dev, head, unreg_list) अणु
		काष्ठा sk_buff *skb = शून्य;

		/* Shutकरोwn queueing discipline. */
		dev_shutकरोwn(dev);

		dev_xdp_uninstall(dev);

		/* Notअगरy protocols, that we are about to destroy
		 * this device. They should clean all the things.
		 */
		call_netdevice_notअगरiers(NETDEV_UNREGISTER, dev);

		अगर (!dev->rtnl_link_ops ||
		    dev->rtnl_link_state == RTNL_LINK_INITIALIZED)
			skb = rपंचांगsg_अगरinfo_build_skb(RTM_DELLINK, dev, ~0U, 0,
						     GFP_KERNEL, शून्य, 0);

		/*
		 *	Flush the unicast and multicast chains
		 */
		dev_uc_flush(dev);
		dev_mc_flush(dev);

		netdev_name_node_alt_flush(dev);
		netdev_name_node_मुक्त(dev->name_node);

		अगर (dev->netdev_ops->nकरो_uninit)
			dev->netdev_ops->nकरो_uninit(dev);

		अगर (skb)
			rपंचांगsg_अगरinfo_send(skb, dev, GFP_KERNEL);

		/* Notअगरier chain MUST detach us all upper devices. */
		WARN_ON(netdev_has_any_upper_dev(dev));
		WARN_ON(netdev_has_any_lower_dev(dev));

		/* Remove entries from kobject tree */
		netdev_unरेजिस्टर_kobject(dev);
#अगर_घोषित CONFIG_XPS
		/* Remove XPS queueing entries */
		netअगर_reset_xps_queues_gt(dev, 0);
#पूर्ण_अगर
	पूर्ण

	synchronize_net();

	list_क्रम_each_entry(dev, head, unreg_list) अणु
		dev_put(dev);
		net_set_toकरो(dev);
	पूर्ण

	list_del(head);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_netdevice_many);

/**
 *	unरेजिस्टर_netdev - हटाओ device from the kernel
 *	@dev: device
 *
 *	This function shuts करोwn a device पूर्णांकerface and हटाओs it
 *	from the kernel tables.
 *
 *	This is just a wrapper क्रम unरेजिस्टर_netdevice that takes
 *	the rtnl semaphore.  In general you want to use this and not
 *	unरेजिस्टर_netdevice.
 */
व्योम unरेजिस्टर_netdev(काष्ठा net_device *dev)
अणु
	rtnl_lock();
	unरेजिस्टर_netdevice(dev);
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_netdev);

/**
 *	__dev_change_net_namespace - move device to dअगरferent nethost namespace
 *	@dev: device
 *	@net: network namespace
 *	@pat: If not शून्य name pattern to try अगर the current device name
 *	      is alपढ़ोy taken in the destination network namespace.
 *	@new_अगरindex: If not zero, specअगरies device index in the target
 *	              namespace.
 *
 *	This function shuts करोwn a device पूर्णांकerface and moves it
 *	to a new network namespace. On success 0 is वापसed, on
 *	a failure a netagive त्रुटि_सं code is वापसed.
 *
 *	Callers must hold the rtnl semaphore.
 */

पूर्णांक __dev_change_net_namespace(काष्ठा net_device *dev, काष्ठा net *net,
			       स्थिर अक्षर *pat, पूर्णांक new_अगरindex)
अणु
	काष्ठा net *net_old = dev_net(dev);
	पूर्णांक err, new_nsid;

	ASSERT_RTNL();

	/* Don't allow namespace local devices to be moved. */
	err = -EINVAL;
	अगर (dev->features & NETIF_F_NETNS_LOCAL)
		जाओ out;

	/* Ensure the device has been registrered */
	अगर (dev->reg_state != NETREG_REGISTERED)
		जाओ out;

	/* Get out अगर there is nothing toकरो */
	err = 0;
	अगर (net_eq(net_old, net))
		जाओ out;

	/* Pick the destination device name, and ensure
	 * we can use it in the destination network namespace.
	 */
	err = -EEXIST;
	अगर (__dev_get_by_name(net, dev->name)) अणु
		/* We get here अगर we can't use the current device name */
		अगर (!pat)
			जाओ out;
		err = dev_get_valid_name(net, dev, pat);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	/* Check that new_अगरindex isn't used yet. */
	err = -EBUSY;
	अगर (new_अगरindex && __dev_get_by_index(net, new_अगरindex))
		जाओ out;

	/*
	 * And now a mini version of रेजिस्टर_netdevice unरेजिस्टर_netdevice.
	 */

	/* If device is running बंद it first. */
	dev_बंद(dev);

	/* And unlink it from device chain */
	unlist_netdevice(dev);

	synchronize_net();

	/* Shutकरोwn queueing discipline. */
	dev_shutकरोwn(dev);

	/* Notअगरy protocols, that we are about to destroy
	 * this device. They should clean all the things.
	 *
	 * Note that dev->reg_state stays at NETREG_REGISTERED.
	 * This is wanted because this way 8021q and macvlan know
	 * the device is just moving and can keep their slaves up.
	 */
	call_netdevice_notअगरiers(NETDEV_UNREGISTER, dev);
	rcu_barrier();

	new_nsid = peernet2id_alloc(dev_net(dev), net, GFP_KERNEL);
	/* If there is an अगरindex conflict assign a new one */
	अगर (!new_अगरindex) अणु
		अगर (__dev_get_by_index(net, dev->अगरindex))
			new_अगरindex = dev_new_index(net);
		अन्यथा
			new_अगरindex = dev->अगरindex;
	पूर्ण

	rपंचांगsg_अगरinfo_newnet(RTM_DELLINK, dev, ~0U, GFP_KERNEL, &new_nsid,
			    new_अगरindex);

	/*
	 *	Flush the unicast and multicast chains
	 */
	dev_uc_flush(dev);
	dev_mc_flush(dev);

	/* Send a netdev-हटाओd uevent to the old namespace */
	kobject_uevent(&dev->dev.kobj, KOBJ_REMOVE);
	netdev_adjacent_del_links(dev);

	/* Move per-net netdevice notअगरiers that are following the netdevice */
	move_netdevice_notअगरiers_dev_net(dev, net);

	/* Actually चयन the network namespace */
	dev_net_set(dev, net);
	dev->अगरindex = new_अगरindex;

	/* Send a netdev-add uevent to the new namespace */
	kobject_uevent(&dev->dev.kobj, KOBJ_ADD);
	netdev_adjacent_add_links(dev);

	/* Fixup kobjects */
	err = device_नाम(&dev->dev, dev->name);
	WARN_ON(err);

	/* Adapt owner in हाल owning user namespace of target network
	 * namespace is dअगरferent from the original one.
	 */
	err = netdev_change_owner(dev, net_old, net);
	WARN_ON(err);

	/* Add the device back in the hashes */
	list_netdevice(dev);

	/* Notअगरy protocols, that a new device appeared. */
	call_netdevice_notअगरiers(NETDEV_REGISTER, dev);

	/*
	 *	Prevent userspace races by रुकोing until the network
	 *	device is fully setup beक्रमe sending notअगरications.
	 */
	rपंचांगsg_अगरinfo(RTM_NEWLINK, dev, ~0U, GFP_KERNEL);

	synchronize_net();
	err = 0;
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__dev_change_net_namespace);

अटल पूर्णांक dev_cpu_dead(अचिन्हित पूर्णांक oldcpu)
अणु
	काष्ठा sk_buff **list_skb;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक cpu;
	काष्ठा softnet_data *sd, *oldsd, *remsd = शून्य;

	local_irq_disable();
	cpu = smp_processor_id();
	sd = &per_cpu(softnet_data, cpu);
	oldsd = &per_cpu(softnet_data, oldcpu);

	/* Find end of our completion_queue. */
	list_skb = &sd->completion_queue;
	जबतक (*list_skb)
		list_skb = &(*list_skb)->next;
	/* Append completion queue from offline CPU. */
	*list_skb = oldsd->completion_queue;
	oldsd->completion_queue = शून्य;

	/* Append output queue from offline CPU. */
	अगर (oldsd->output_queue) अणु
		*sd->output_queue_tailp = oldsd->output_queue;
		sd->output_queue_tailp = oldsd->output_queue_tailp;
		oldsd->output_queue = शून्य;
		oldsd->output_queue_tailp = &oldsd->output_queue;
	पूर्ण
	/* Append NAPI poll list from offline CPU, with one exception :
	 * process_backlog() must be called by cpu owning percpu backlog.
	 * We properly handle process_queue & input_pkt_queue later.
	 */
	जबतक (!list_empty(&oldsd->poll_list)) अणु
		काष्ठा napi_काष्ठा *napi = list_first_entry(&oldsd->poll_list,
							    काष्ठा napi_काष्ठा,
							    poll_list);

		list_del_init(&napi->poll_list);
		अगर (napi->poll == process_backlog)
			napi->state = 0;
		अन्यथा
			____napi_schedule(sd, napi);
	पूर्ण

	उठाओ_softirq_irqoff(NET_TX_SOFTIRQ);
	local_irq_enable();

#अगर_घोषित CONFIG_RPS
	remsd = oldsd->rps_ipi_list;
	oldsd->rps_ipi_list = शून्य;
#पूर्ण_अगर
	/* send out pending IPI's on offline CPU */
	net_rps_send_ipi(remsd);

	/* Process offline CPU's input_pkt_queue */
	जबतक ((skb = __skb_dequeue(&oldsd->process_queue))) अणु
		netअगर_rx_ni(skb);
		input_queue_head_incr(oldsd);
	पूर्ण
	जबतक ((skb = skb_dequeue(&oldsd->input_pkt_queue))) अणु
		netअगर_rx_ni(skb);
		input_queue_head_incr(oldsd);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	netdev_increment_features - increment feature set by one
 *	@all: current feature set
 *	@one: new feature set
 *	@mask: mask feature set
 *
 *	Computes a new feature set after adding a device with feature set
 *	@one to the master device with current feature set @all.  Will not
 *	enable anything that is off in @mask. Returns the new feature set.
 */
netdev_features_t netdev_increment_features(netdev_features_t all,
	netdev_features_t one, netdev_features_t mask)
अणु
	अगर (mask & NETIF_F_HW_CSUM)
		mask |= NETIF_F_CSUM_MASK;
	mask |= NETIF_F_VLAN_CHALLENGED;

	all |= one & (NETIF_F_ONE_FOR_ALL | NETIF_F_CSUM_MASK) & mask;
	all &= one | ~NETIF_F_ALL_FOR_ALL;

	/* If one device supports hw checksumming, set क्रम all. */
	अगर (all & NETIF_F_HW_CSUM)
		all &= ~(NETIF_F_CSUM_MASK & ~NETIF_F_HW_CSUM);

	वापस all;
पूर्ण
EXPORT_SYMBOL(netdev_increment_features);

अटल काष्ठा hlist_head * __net_init netdev_create_hash(व्योम)
अणु
	पूर्णांक i;
	काष्ठा hlist_head *hash;

	hash = kदो_स्मृति_array(NETDEV_HASHENTRIES, माप(*hash), GFP_KERNEL);
	अगर (hash != शून्य)
		क्रम (i = 0; i < NETDEV_HASHENTRIES; i++)
			INIT_HLIST_HEAD(&hash[i]);

	वापस hash;
पूर्ण

/* Initialize per network namespace state */
अटल पूर्णांक __net_init netdev_init(काष्ठा net *net)
अणु
	BUILD_BUG_ON(GRO_HASH_BUCKETS >
		     8 * माप_field(काष्ठा napi_काष्ठा, gro_biपंचांगask));

	अगर (net != &init_net)
		INIT_LIST_HEAD(&net->dev_base_head);

	net->dev_name_head = netdev_create_hash();
	अगर (net->dev_name_head == शून्य)
		जाओ err_name;

	net->dev_index_head = netdev_create_hash();
	अगर (net->dev_index_head == शून्य)
		जाओ err_idx;

	RAW_INIT_NOTIFIER_HEAD(&net->netdev_chain);

	वापस 0;

err_idx:
	kमुक्त(net->dev_name_head);
err_name:
	वापस -ENOMEM;
पूर्ण

/**
 *	netdev_drivername - network driver क्रम the device
 *	@dev: network device
 *
 *	Determine network driver क्रम device.
 */
स्थिर अक्षर *netdev_drivername(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा device_driver *driver;
	स्थिर काष्ठा device *parent;
	स्थिर अक्षर *empty = "";

	parent = dev->dev.parent;
	अगर (!parent)
		वापस empty;

	driver = parent->driver;
	अगर (driver && driver->name)
		वापस driver->name;
	वापस empty;
पूर्ण

अटल व्योम __netdev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा net_device *dev,
			    काष्ठा va_क्रमmat *vaf)
अणु
	अगर (dev && dev->dev.parent) अणु
		dev_prपूर्णांकk_emit(level[1] - '0',
				dev->dev.parent,
				"%s %s %s%s: %pV",
				dev_driver_string(dev->dev.parent),
				dev_name(dev->dev.parent),
				netdev_name(dev), netdev_reg_state(dev),
				vaf);
	पूर्ण अन्यथा अगर (dev) अणु
		prपूर्णांकk("%s%s%s: %pV",
		       level, netdev_name(dev), netdev_reg_state(dev), vaf);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("%s(NULL net_device): %pV", level, vaf);
	पूर्ण
पूर्ण

व्योम netdev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा net_device *dev,
		   स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;

	__netdev_prपूर्णांकk(level, dev, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(netdev_prपूर्णांकk);

#घोषणा define_netdev_prपूर्णांकk_level(func, level)			\
व्योम func(स्थिर काष्ठा net_device *dev, स्थिर अक्षर *fmt, ...)	\
अणु								\
	काष्ठा va_क्रमmat vaf;					\
	बहु_सूची args;						\
								\
	बहु_शुरू(args, fmt);					\
								\
	vaf.fmt = fmt;						\
	vaf.va = &args;						\
								\
	__netdev_prपूर्णांकk(level, dev, &vaf);			\
								\
	बहु_पूर्ण(args);						\
पूर्ण								\
EXPORT_SYMBOL(func);

define_netdev_prपूर्णांकk_level(netdev_emerg, KERN_EMERG);
define_netdev_prपूर्णांकk_level(netdev_alert, KERN_ALERT);
define_netdev_prपूर्णांकk_level(netdev_crit, KERN_CRIT);
define_netdev_prपूर्णांकk_level(netdev_err, KERN_ERR);
define_netdev_prपूर्णांकk_level(netdev_warn, KERN_WARNING);
define_netdev_prपूर्णांकk_level(netdev_notice, KERN_NOTICE);
define_netdev_prपूर्णांकk_level(netdev_info, KERN_INFO);

अटल व्योम __net_निकास netdev_निकास(काष्ठा net *net)
अणु
	kमुक्त(net->dev_name_head);
	kमुक्त(net->dev_index_head);
	अगर (net != &init_net)
		WARN_ON_ONCE(!list_empty(&net->dev_base_head));
पूर्ण

अटल काष्ठा pernet_operations __net_initdata netdev_net_ops = अणु
	.init = netdev_init,
	.निकास = netdev_निकास,
पूर्ण;

अटल व्योम __net_निकास शेष_device_निकास(काष्ठा net *net)
अणु
	काष्ठा net_device *dev, *aux;
	/*
	 * Push all migratable network devices back to the
	 * initial network namespace
	 */
	rtnl_lock();
	क्रम_each_netdev_safe(net, dev, aux) अणु
		पूर्णांक err;
		अक्षर fb_name[IFNAMSIZ];

		/* Ignore unmoveable devices (i.e. loopback) */
		अगर (dev->features & NETIF_F_NETNS_LOCAL)
			जारी;

		/* Leave भव devices क्रम the generic cleanup */
		अगर (dev->rtnl_link_ops && !dev->rtnl_link_ops->netns_refund)
			जारी;

		/* Push reमुख्यing network devices to init_net */
		snम_लिखो(fb_name, IFNAMSIZ, "dev%d", dev->अगरindex);
		अगर (__dev_get_by_name(&init_net, fb_name))
			snम_लिखो(fb_name, IFNAMSIZ, "dev%%d");
		err = dev_change_net_namespace(dev, &init_net, fb_name);
		अगर (err) अणु
			pr_emerg("%s: failed to move %s to init_net: %d\n",
				 __func__, dev->name, err);
			BUG();
		पूर्ण
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल व्योम __net_निकास rtnl_lock_unरेजिस्टरing(काष्ठा list_head *net_list)
अणु
	/* Return with the rtnl_lock held when there are no network
	 * devices unरेजिस्टरing in any network namespace in net_list.
	 */
	काष्ठा net *net;
	bool unरेजिस्टरing;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	add_रुको_queue(&netdev_unरेजिस्टरing_wq, &रुको);
	क्रम (;;) अणु
		unरेजिस्टरing = false;
		rtnl_lock();
		list_क्रम_each_entry(net, net_list, निकास_list) अणु
			अगर (net->dev_unreg_count > 0) अणु
				unरेजिस्टरing = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!unरेजिस्टरing)
			अवरोध;
		__rtnl_unlock();

		रुको_woken(&रुको, TASK_UNINTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	पूर्ण
	हटाओ_रुको_queue(&netdev_unरेजिस्टरing_wq, &रुको);
पूर्ण

अटल व्योम __net_निकास शेष_device_निकास_batch(काष्ठा list_head *net_list)
अणु
	/* At निकास all network devices most be हटाओd from a network
	 * namespace.  Do this in the reverse order of registration.
	 * Do this across as many network namespaces as possible to
	 * improve batching efficiency.
	 */
	काष्ठा net_device *dev;
	काष्ठा net *net;
	LIST_HEAD(dev_समाप्त_list);

	/* To prevent network device cleanup code from dereferencing
	 * loopback devices or network devices that have been मुक्तd
	 * रुको here क्रम all pending unregistrations to complete,
	 * beक्रमe unregistring the loopback device and allowing the
	 * network namespace be मुक्तd.
	 *
	 * The netdev toकरो list containing all network devices
	 * unregistrations that happen in शेष_device_निकास_batch
	 * will run in the rtnl_unlock() at the end of
	 * शेष_device_निकास_batch.
	 */
	rtnl_lock_unरेजिस्टरing(net_list);
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		क्रम_each_netdev_reverse(net, dev) अणु
			अगर (dev->rtnl_link_ops && dev->rtnl_link_ops->dellink)
				dev->rtnl_link_ops->dellink(dev, &dev_समाप्त_list);
			अन्यथा
				unरेजिस्टर_netdevice_queue(dev, &dev_समाप्त_list);
		पूर्ण
	पूर्ण
	unरेजिस्टर_netdevice_many(&dev_समाप्त_list);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations __net_initdata शेष_device_ops = अणु
	.निकास = शेष_device_निकास,
	.निकास_batch = शेष_device_निकास_batch,
पूर्ण;

/*
 *	Initialize the DEV module. At boot समय this walks the device list and
 *	unhooks any devices that fail to initialise (normally hardware not
 *	present) and leaves us with a valid list of present and active devices.
 *
 */

/*
 *       This is called single thपढ़ोed during boot, so no need
 *       to take the rtnl semaphore.
 */
अटल पूर्णांक __init net_dev_init(व्योम)
अणु
	पूर्णांक i, rc = -ENOMEM;

	BUG_ON(!dev_boot_phase);

	अगर (dev_proc_init())
		जाओ out;

	अगर (netdev_kobject_init())
		जाओ out;

	INIT_LIST_HEAD(&ptype_all);
	क्रम (i = 0; i < PTYPE_HASH_SIZE; i++)
		INIT_LIST_HEAD(&ptype_base[i]);

	INIT_LIST_HEAD(&offload_base);

	अगर (रेजिस्टर_pernet_subsys(&netdev_net_ops))
		जाओ out;

	/*
	 *	Initialise the packet receive queues.
	 */

	क्रम_each_possible_cpu(i) अणु
		काष्ठा work_काष्ठा *flush = per_cpu_ptr(&flush_works, i);
		काष्ठा softnet_data *sd = &per_cpu(softnet_data, i);

		INIT_WORK(flush, flush_backlog);

		skb_queue_head_init(&sd->input_pkt_queue);
		skb_queue_head_init(&sd->process_queue);
#अगर_घोषित CONFIG_XFRM_OFFLOAD
		skb_queue_head_init(&sd->xfrm_backlog);
#पूर्ण_अगर
		INIT_LIST_HEAD(&sd->poll_list);
		sd->output_queue_tailp = &sd->output_queue;
#अगर_घोषित CONFIG_RPS
		INIT_CSD(&sd->csd, rps_trigger_softirq, sd);
		sd->cpu = i;
#पूर्ण_अगर

		init_gro_hash(&sd->backlog);
		sd->backlog.poll = process_backlog;
		sd->backlog.weight = weight_p;
	पूर्ण

	dev_boot_phase = 0;

	/* The loopback device is special अगर any other network devices
	 * is present in a network namespace the loopback device must
	 * be present. Since we now dynamically allocate and मुक्त the
	 * loopback device ensure this invariant is मुख्यtained by
	 * keeping the loopback device as the first device on the
	 * list of network devices.  Ensuring the loopback devices
	 * is the first device that appears and the last network device
	 * that disappears.
	 */
	अगर (रेजिस्टर_pernet_device(&loopback_net_ops))
		जाओ out;

	अगर (रेजिस्टर_pernet_device(&शेष_device_ops))
		जाओ out;

	खोलो_softirq(NET_TX_SOFTIRQ, net_tx_action);
	खोलो_softirq(NET_RX_SOFTIRQ, net_rx_action);

	rc = cpuhp_setup_state_nocalls(CPUHP_NET_DEV_DEAD, "net/dev:dead",
				       शून्य, dev_cpu_dead);
	WARN_ON(rc < 0);
	rc = 0;
out:
	वापस rc;
पूर्ण

subsys_initcall(net_dev_init);

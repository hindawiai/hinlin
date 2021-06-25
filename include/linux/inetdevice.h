<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_INETDEVICE_H
#घोषणा _LINUX_INETDEVICE_H

#अगर_घोषित __KERNEL__

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/अगर.h>
#समावेश <linux/ip.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/refcount.h>

काष्ठा ipv4_devconf अणु
	व्योम	*sysctl;
	पूर्णांक	data[IPV4_DEVCONF_MAX];
	DECLARE_BITMAP(state, IPV4_DEVCONF_MAX);
पूर्ण;

#घोषणा MC_HASH_SZ_LOG 9

काष्ठा in_device अणु
	काष्ठा net_device	*dev;
	refcount_t		refcnt;
	पूर्णांक			dead;
	काष्ठा in_अगरaddr	__rcu *अगरa_list;/* IP अगरaddr chain		*/

	काष्ठा ip_mc_list __rcu	*mc_list;	/* IP multicast filter chain    */
	काष्ठा ip_mc_list __rcu	* __rcu *mc_hash;

	पूर्णांक			mc_count;	/* Number of installed mcasts	*/
	spinlock_t		mc_tomb_lock;
	काष्ठा ip_mc_list	*mc_tomb;
	अचिन्हित दीर्घ		mr_v1_seen;
	अचिन्हित दीर्घ		mr_v2_seen;
	अचिन्हित दीर्घ		mr_maxdelay;
	अचिन्हित दीर्घ		mr_qi;		/* Query Interval */
	अचिन्हित दीर्घ		mr_qri;		/* Query Response Interval */
	अचिन्हित अक्षर		mr_qrv;		/* Query Robustness Variable */
	अचिन्हित अक्षर		mr_gq_running;
	अचिन्हित अक्षर		mr_अगरc_count;
	काष्ठा समयr_list	mr_gq_समयr;	/* general query समयr */
	काष्ठा समयr_list	mr_अगरc_समयr;	/* पूर्णांकerface change समयr */

	काष्ठा neigh_parms	*arp_parms;
	काष्ठा ipv4_devconf	cnf;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

#घोषणा IPV4_DEVCONF(cnf, attr) ((cnf).data[IPV4_DEVCONF_ ## attr - 1])
#घोषणा IPV4_DEVCONF_ALL(net, attr) \
	IPV4_DEVCONF((*(net)->ipv4.devconf_all), attr)

अटल अंतरभूत पूर्णांक ipv4_devconf_get(काष्ठा in_device *in_dev, पूर्णांक index)
अणु
	index--;
	वापस in_dev->cnf.data[index];
पूर्ण

अटल अंतरभूत व्योम ipv4_devconf_set(काष्ठा in_device *in_dev, पूर्णांक index,
				    पूर्णांक val)
अणु
	index--;
	set_bit(index, in_dev->cnf.state);
	in_dev->cnf.data[index] = val;
पूर्ण

अटल अंतरभूत व्योम ipv4_devconf_setall(काष्ठा in_device *in_dev)
अणु
	biपंचांगap_fill(in_dev->cnf.state, IPV4_DEVCONF_MAX);
पूर्ण

#घोषणा IN_DEV_CONF_GET(in_dev, attr) \
	ipv4_devconf_get((in_dev), IPV4_DEVCONF_ ## attr)
#घोषणा IN_DEV_CONF_SET(in_dev, attr, val) \
	ipv4_devconf_set((in_dev), IPV4_DEVCONF_ ## attr, (val))

#घोषणा IN_DEV_ANDCONF(in_dev, attr) \
	(IPV4_DEVCONF_ALL(dev_net(in_dev->dev), attr) && \
	 IN_DEV_CONF_GET((in_dev), attr))

#घोषणा IN_DEV_NET_ORCONF(in_dev, net, attr) \
	(IPV4_DEVCONF_ALL(net, attr) || \
	 IN_DEV_CONF_GET((in_dev), attr))

#घोषणा IN_DEV_ORCONF(in_dev, attr) \
	IN_DEV_NET_ORCONF(in_dev, dev_net(in_dev->dev), attr)

#घोषणा IN_DEV_MAXCONF(in_dev, attr) \
	(max(IPV4_DEVCONF_ALL(dev_net(in_dev->dev), attr), \
	     IN_DEV_CONF_GET((in_dev), attr)))

#घोषणा IN_DEV_FORWARD(in_dev)		IN_DEV_CONF_GET((in_dev), FORWARDING)
#घोषणा IN_DEV_MFORWARD(in_dev)		IN_DEV_ANDCONF((in_dev), MC_FORWARDING)
#घोषणा IN_DEV_BFORWARD(in_dev)		IN_DEV_ANDCONF((in_dev), BC_FORWARDING)
#घोषणा IN_DEV_RPFILTER(in_dev)		IN_DEV_MAXCONF((in_dev), RP_FILTER)
#घोषणा IN_DEV_SRC_VMARK(in_dev)    	IN_DEV_ORCONF((in_dev), SRC_VMARK)
#घोषणा IN_DEV_SOURCE_ROUTE(in_dev)	IN_DEV_ANDCONF((in_dev), \
						       ACCEPT_SOURCE_ROUTE)
#घोषणा IN_DEV_ACCEPT_LOCAL(in_dev)	IN_DEV_ORCONF((in_dev), ACCEPT_LOCAL)
#घोषणा IN_DEV_BOOTP_RELAY(in_dev)	IN_DEV_ANDCONF((in_dev), BOOTP_RELAY)

#घोषणा IN_DEV_LOG_MARTIANS(in_dev)	IN_DEV_ORCONF((in_dev), LOG_MARTIANS)
#घोषणा IN_DEV_PROXY_ARP(in_dev)	IN_DEV_ORCONF((in_dev), PROXY_ARP)
#घोषणा IN_DEV_PROXY_ARP_PVLAN(in_dev)	IN_DEV_ORCONF((in_dev), PROXY_ARP_PVLAN)
#घोषणा IN_DEV_SHARED_MEDIA(in_dev)	IN_DEV_ORCONF((in_dev), SHARED_MEDIA)
#घोषणा IN_DEV_TX_REसूचीECTS(in_dev)	IN_DEV_ORCONF((in_dev), SEND_REसूचीECTS)
#घोषणा IN_DEV_SEC_REसूचीECTS(in_dev)	IN_DEV_ORCONF((in_dev), \
						      SECURE_REसूचीECTS)
#घोषणा IN_DEV_IDTAG(in_dev)		IN_DEV_CONF_GET(in_dev, TAG)
#घोषणा IN_DEV_MEDIUM_ID(in_dev)	IN_DEV_CONF_GET(in_dev, MEDIUM_ID)
#घोषणा IN_DEV_PROMOTE_SECONDARIES(in_dev) \
					IN_DEV_ORCONF((in_dev), \
						      PROMOTE_SECONDARIES)
#घोषणा IN_DEV_ROUTE_LOCALNET(in_dev)	IN_DEV_ORCONF(in_dev, ROUTE_LOCALNET)
#घोषणा IN_DEV_NET_ROUTE_LOCALNET(in_dev, net)	\
	IN_DEV_NET_ORCONF(in_dev, net, ROUTE_LOCALNET)

#घोषणा IN_DEV_RX_REसूचीECTS(in_dev) \
	((IN_DEV_FORWARD(in_dev) && \
	  IN_DEV_ANDCONF((in_dev), ACCEPT_REसूचीECTS)) \
	 || (!IN_DEV_FORWARD(in_dev) && \
	  IN_DEV_ORCONF((in_dev), ACCEPT_REसूचीECTS)))

#घोषणा IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN(in_dev) \
	IN_DEV_ORCONF((in_dev), IGNORE_ROUTES_WITH_LINKDOWN)

#घोषणा IN_DEV_ARPFILTER(in_dev)	IN_DEV_ORCONF((in_dev), ARPFILTER)
#घोषणा IN_DEV_ARP_ACCEPT(in_dev)	IN_DEV_ORCONF((in_dev), ARP_ACCEPT)
#घोषणा IN_DEV_ARP_ANNOUNCE(in_dev)	IN_DEV_MAXCONF((in_dev), ARP_ANNOUNCE)
#घोषणा IN_DEV_ARP_IGNORE(in_dev)	IN_DEV_MAXCONF((in_dev), ARP_IGNORE)
#घोषणा IN_DEV_ARP_NOTIFY(in_dev)	IN_DEV_MAXCONF((in_dev), ARP_NOTIFY)

काष्ठा in_अगरaddr अणु
	काष्ठा hlist_node	hash;
	काष्ठा in_अगरaddr	__rcu *अगरa_next;
	काष्ठा in_device	*अगरa_dev;
	काष्ठा rcu_head		rcu_head;
	__be32			अगरa_local;
	__be32			अगरa_address;
	__be32			अगरa_mask;
	__u32			अगरa_rt_priority;
	__be32			अगरa_broadcast;
	अचिन्हित अक्षर		अगरa_scope;
	अचिन्हित अक्षर		अगरa_prefixlen;
	__u32			अगरa_flags;
	अक्षर			अगरa_label[IFNAMSIZ];

	/* In seconds, relative to tstamp. Expiry is at tstamp + HZ * lft. */
	__u32			अगरa_valid_lft;
	__u32			अगरa_preferred_lft;
	अचिन्हित दीर्घ		अगरa_cstamp; /* created बारtamp */
	अचिन्हित दीर्घ		अगरa_tstamp; /* updated बारtamp */
पूर्ण;

काष्ठा in_validator_info अणु
	__be32			ivi_addr;
	काष्ठा in_device	*ivi_dev;
	काष्ठा netlink_ext_ack	*extack;
पूर्ण;

पूर्णांक रेजिस्टर_inetaddr_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_inetaddr_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक रेजिस्टर_inetaddr_validator_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_inetaddr_validator_notअगरier(काष्ठा notअगरier_block *nb);

व्योम inet_netconf_notअगरy_devconf(काष्ठा net *net, पूर्णांक event, पूर्णांक type,
				 पूर्णांक अगरindex, काष्ठा ipv4_devconf *devconf);

काष्ठा net_device *__ip_dev_find(काष्ठा net *net, __be32 addr, bool devref);
अटल अंतरभूत काष्ठा net_device *ip_dev_find(काष्ठा net *net, __be32 addr)
अणु
	वापस __ip_dev_find(net, addr, true);
पूर्ण

पूर्णांक inet_addr_onlink(काष्ठा in_device *in_dev, __be32 a, __be32 b);
पूर्णांक devinet_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, काष्ठा अगरreq *);
व्योम devinet_init(व्योम);
काष्ठा in_device *inetdev_by_index(काष्ठा net *, पूर्णांक);
__be32 inet_select_addr(स्थिर काष्ठा net_device *dev, __be32 dst, पूर्णांक scope);
__be32 inet_confirm_addr(काष्ठा net *net, काष्ठा in_device *in_dev, __be32 dst,
			 __be32 local, पूर्णांक scope);
काष्ठा in_अगरaddr *inet_अगरa_byprefix(काष्ठा in_device *in_dev, __be32 prefix,
				    __be32 mask);
काष्ठा in_अगरaddr *inet_lookup_अगरaddr_rcu(काष्ठा net *net, __be32 addr);
अटल अंतरभूत bool inet_अगरa_match(__be32 addr, स्थिर काष्ठा in_अगरaddr *अगरa)
अणु
	वापस !((addr^अगरa->अगरa_address)&अगरa->अगरa_mask);
पूर्ण

/*
 *	Check अगर a mask is acceptable.
 */
 
अटल __अंतरभूत__ bool bad_mask(__be32 mask, __be32 addr)
अणु
	__u32 hmask;
	अगर (addr & (mask = ~mask))
		वापस true;
	hmask = ntohl(mask);
	अगर (hmask & (hmask+1))
		वापस true;
	वापस false;
पूर्ण

#घोषणा in_dev_क्रम_each_अगरa_rtnl(अगरa, in_dev)			\
	क्रम (अगरa = rtnl_dereference((in_dev)->अगरa_list); अगरa;	\
	     अगरa = rtnl_dereference(अगरa->अगरa_next))

#घोषणा in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev)			\
	क्रम (अगरa = rcu_dereference((in_dev)->अगरa_list); अगरa;	\
	     अगरa = rcu_dereference(अगरa->अगरa_next))

अटल अंतरभूत काष्ठा in_device *__in_dev_get_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference(dev->ip_ptr);
पूर्ण

अटल अंतरभूत काष्ठा in_device *in_dev_get(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा in_device *in_dev;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(dev);
	अगर (in_dev)
		refcount_inc(&in_dev->refcnt);
	rcu_पढ़ो_unlock();
	वापस in_dev;
पूर्ण

अटल अंतरभूत काष्ठा in_device *__in_dev_get_rtnl(स्थिर काष्ठा net_device *dev)
अणु
	वापस rtnl_dereference(dev->ip_ptr);
पूर्ण

/* called with rcu_पढ़ो_lock or rtnl held */
अटल अंतरभूत bool ip_ignore_linkकरोwn(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा in_device *in_dev;
	bool rc = false;

	in_dev = rcu_dereference_rtnl(dev->ip_ptr);
	अगर (in_dev &&
	    IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN(in_dev))
		rc = true;

	वापस rc;
पूर्ण

अटल अंतरभूत काष्ठा neigh_parms *__in_dev_arp_parms_get_rcu(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);

	वापस in_dev ? in_dev->arp_parms : शून्य;
पूर्ण

व्योम in_dev_finish_destroy(काष्ठा in_device *idev);

अटल अंतरभूत व्योम in_dev_put(काष्ठा in_device *idev)
अणु
	अगर (refcount_dec_and_test(&idev->refcnt))
		in_dev_finish_destroy(idev);
पूर्ण

#घोषणा __in_dev_put(idev)  refcount_dec(&(idev)->refcnt)
#घोषणा in_dev_hold(idev)   refcount_inc(&(idev)->refcnt)

#पूर्ण_अगर /* __KERNEL__ */

अटल __अंतरभूत__ __be32 inet_make_mask(पूर्णांक logmask)
अणु
	अगर (logmask)
		वापस htonl(~((1U<<(32-logmask))-1));
	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक inet_mask_len(__be32 mask)
अणु
	__u32 hmask = ntohl(mask);
	अगर (!hmask)
		वापस 0;
	वापस 32 - ffz(~hmask);
पूर्ण


#पूर्ण_अगर /* _LINUX_INETDEVICE_H */

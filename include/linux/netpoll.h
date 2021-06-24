<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common code क्रम low-level network console, dump, and debugger code
 *
 * Derived from netconsole, kgdb-over-ethernet, and netdump patches
 */

#अगर_अघोषित _LINUX_NETPOLL_H
#घोषणा _LINUX_NETPOLL_H

#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/refcount.h>

जोड़ inet_addr अणु
	__u32		all[4];
	__be32		ip;
	__be32		ip6[4];
	काष्ठा in_addr	in;
	काष्ठा in6_addr	in6;
पूर्ण;

काष्ठा netpoll अणु
	काष्ठा net_device *dev;
	अक्षर dev_name[IFNAMSIZ];
	स्थिर अक्षर *name;

	जोड़ inet_addr local_ip, remote_ip;
	bool ipv6;
	u16 local_port, remote_port;
	u8 remote_mac[ETH_ALEN];
पूर्ण;

काष्ठा netpoll_info अणु
	refcount_t refcnt;

	काष्ठा semaphore dev_lock;

	काष्ठा sk_buff_head txq;

	काष्ठा delayed_work tx_work;

	काष्ठा netpoll *netpoll;
	काष्ठा rcu_head rcu;
पूर्ण;

#अगर_घोषित CONFIG_NETPOLL
व्योम netpoll_poll_dev(काष्ठा net_device *dev);
व्योम netpoll_poll_disable(काष्ठा net_device *dev);
व्योम netpoll_poll_enable(काष्ठा net_device *dev);
#अन्यथा
अटल अंतरभूत व्योम netpoll_poll_disable(काष्ठा net_device *dev) अणु वापस; पूर्ण
अटल अंतरभूत व्योम netpoll_poll_enable(काष्ठा net_device *dev) अणु वापस; पूर्ण
#पूर्ण_अगर

व्योम netpoll_send_udp(काष्ठा netpoll *np, स्थिर अक्षर *msg, पूर्णांक len);
व्योम netpoll_prपूर्णांक_options(काष्ठा netpoll *np);
पूर्णांक netpoll_parse_options(काष्ठा netpoll *np, अक्षर *opt);
पूर्णांक __netpoll_setup(काष्ठा netpoll *np, काष्ठा net_device *ndev);
पूर्णांक netpoll_setup(काष्ठा netpoll *np);
व्योम __netpoll_cleanup(काष्ठा netpoll *np);
व्योम __netpoll_मुक्त(काष्ठा netpoll *np);
व्योम netpoll_cleanup(काष्ठा netpoll *np);
netdev_tx_t netpoll_send_skb(काष्ठा netpoll *np, काष्ठा sk_buff *skb);

#अगर_घोषित CONFIG_NETPOLL
अटल अंतरभूत व्योम *netpoll_poll_lock(काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा net_device *dev = napi->dev;

	अगर (dev && dev->npinfo) अणु
		पूर्णांक owner = smp_processor_id();

		जबतक (cmpxchg(&napi->poll_owner, -1, owner) != -1)
			cpu_relax();

		वापस napi;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम netpoll_poll_unlock(व्योम *have)
अणु
	काष्ठा napi_काष्ठा *napi = have;

	अगर (napi)
		smp_store_release(&napi->poll_owner, -1);
पूर्ण

अटल अंतरभूत bool netpoll_tx_running(काष्ठा net_device *dev)
अणु
	वापस irqs_disabled();
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम *netpoll_poll_lock(काष्ठा napi_काष्ठा *napi)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम netpoll_poll_unlock(व्योम *have)
अणु
पूर्ण
अटल अंतरभूत bool netpoll_tx_running(काष्ठा net_device *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

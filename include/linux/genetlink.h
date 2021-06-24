<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_GENERIC_NETLINK_H
#घोषणा __LINUX_GENERIC_NETLINK_H

#समावेश <uapi/linux/genetlink.h>


/* All generic netlink requests are serialized by a global lock.  */
बाह्य व्योम genl_lock(व्योम);
बाह्य व्योम genl_unlock(व्योम);
#अगर_घोषित CONFIG_LOCKDEP
बाह्य bool lockdep_genl_is_held(व्योम);
#पूर्ण_अगर

/* क्रम synchronisation between af_netlink and genetlink */
बाह्य atomic_t genl_sk_deकाष्ठाing_cnt;
बाह्य रुको_queue_head_t genl_sk_deकाष्ठाing_रुकोq;

/**
 * rcu_dereference_genl - rcu_dereference with debug checking
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * Do an rcu_dereference(p), but check caller either holds rcu_पढ़ो_lock()
 * or genl mutex. Note : Please prefer genl_dereference() or rcu_dereference()
 */
#घोषणा rcu_dereference_genl(p)					\
	rcu_dereference_check(p, lockdep_genl_is_held())

/**
 * genl_dereference - fetch RCU poपूर्णांकer when updates are prevented by genl mutex
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * Return the value of the specअगरied RCU-रक्षित poपूर्णांकer, but omit
 * the READ_ONCE(), because caller holds genl mutex.
 */
#घोषणा genl_dereference(p)					\
	rcu_dereference_रक्षित(p, lockdep_genl_is_held())

#घोषणा MODULE_ALIAS_GENL_FAMILY(family)\
 MODULE_ALIAS_NET_PF_PROTO_NAME(PF_NETLINK, NETLINK_GENERIC, "-family-" family)

#पूर्ण_अगर	/* __LINUX_GENERIC_NETLINK_H */

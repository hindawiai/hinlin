<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_RTNETLINK_H
#घोषणा __LINUX_RTNETLINK_H


#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/रुको.h>
#समावेश <linux/refcount.h>
#समावेश <uapi/linux/rtnetlink.h>

बाह्य पूर्णांक rtnetlink_send(काष्ठा sk_buff *skb, काष्ठा net *net, u32 pid, u32 group, पूर्णांक echo);
बाह्य पूर्णांक rtnl_unicast(काष्ठा sk_buff *skb, काष्ठा net *net, u32 pid);
बाह्य व्योम rtnl_notअगरy(काष्ठा sk_buff *skb, काष्ठा net *net, u32 pid,
			u32 group, काष्ठा nlmsghdr *nlh, gfp_t flags);
बाह्य व्योम rtnl_set_sk_err(काष्ठा net *net, u32 group, पूर्णांक error);
बाह्य पूर्णांक rtnetlink_put_metrics(काष्ठा sk_buff *skb, u32 *metrics);
बाह्य पूर्णांक rtnl_put_cacheinfo(काष्ठा sk_buff *skb, काष्ठा dst_entry *dst,
			      u32 id, दीर्घ expires, u32 error);

व्योम rपंचांगsg_अगरinfo(पूर्णांक type, काष्ठा net_device *dev, अचिन्हित change, gfp_t flags);
व्योम rपंचांगsg_अगरinfo_newnet(पूर्णांक type, काष्ठा net_device *dev, अचिन्हित पूर्णांक change,
			 gfp_t flags, पूर्णांक *new_nsid, पूर्णांक new_अगरindex);
काष्ठा sk_buff *rपंचांगsg_अगरinfo_build_skb(पूर्णांक type, काष्ठा net_device *dev,
				       अचिन्हित change, u32 event,
				       gfp_t flags, पूर्णांक *new_nsid,
				       पूर्णांक new_अगरindex);
व्योम rपंचांगsg_अगरinfo_send(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       gfp_t flags);


/* RTNL is used as a global lock क्रम all changes to network configuration  */
बाह्य व्योम rtnl_lock(व्योम);
बाह्य व्योम rtnl_unlock(व्योम);
बाह्य पूर्णांक rtnl_trylock(व्योम);
बाह्य पूर्णांक rtnl_is_locked(व्योम);
बाह्य पूर्णांक rtnl_lock_समाप्तable(व्योम);
बाह्य bool refcount_dec_and_rtnl_lock(refcount_t *r);

बाह्य रुको_queue_head_t netdev_unरेजिस्टरing_wq;
बाह्य काष्ठा rw_semaphore pernet_ops_rwsem;
बाह्य काष्ठा rw_semaphore net_rwsem;

#अगर_घोषित CONFIG_PROVE_LOCKING
बाह्य bool lockdep_rtnl_is_held(व्योम);
#अन्यथा
अटल अंतरभूत bool lockdep_rtnl_is_held(व्योम)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* #अगर_घोषित CONFIG_PROVE_LOCKING */

/**
 * rcu_dereference_rtnl - rcu_dereference with debug checking
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * Do an rcu_dereference(p), but check caller either holds rcu_पढ़ो_lock()
 * or RTNL. Note : Please prefer rtnl_dereference() or rcu_dereference()
 */
#घोषणा rcu_dereference_rtnl(p)					\
	rcu_dereference_check(p, lockdep_rtnl_is_held())

/**
 * rcu_dereference_bh_rtnl - rcu_dereference_bh with debug checking
 * @p: The poपूर्णांकer to पढ़ो, prior to dereference
 *
 * Do an rcu_dereference_bh(p), but check caller either holds rcu_पढ़ो_lock_bh()
 * or RTNL. Note : Please prefer rtnl_dereference() or rcu_dereference_bh()
 */
#घोषणा rcu_dereference_bh_rtnl(p)				\
	rcu_dereference_bh_check(p, lockdep_rtnl_is_held())

/**
 * rtnl_dereference - fetch RCU poपूर्णांकer when updates are prevented by RTNL
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * Return the value of the specअगरied RCU-रक्षित poपूर्णांकer, but omit
 * the READ_ONCE(), because caller holds RTNL.
 */
#घोषणा rtnl_dereference(p)					\
	rcu_dereference_रक्षित(p, lockdep_rtnl_is_held())

अटल अंतरभूत काष्ठा netdev_queue *dev_ingress_queue(काष्ठा net_device *dev)
अणु
	वापस rtnl_dereference(dev->ingress_queue);
पूर्ण

अटल अंतरभूत काष्ठा netdev_queue *dev_ingress_queue_rcu(काष्ठा net_device *dev)
अणु
	वापस rcu_dereference(dev->ingress_queue);
पूर्ण

काष्ठा netdev_queue *dev_ingress_queue_create(काष्ठा net_device *dev);

#अगर_घोषित CONFIG_NET_INGRESS
व्योम net_inc_ingress_queue(व्योम);
व्योम net_dec_ingress_queue(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_EGRESS
व्योम net_inc_egress_queue(व्योम);
व्योम net_dec_egress_queue(व्योम);
#पूर्ण_अगर

व्योम rtnetlink_init(व्योम);
व्योम __rtnl_unlock(व्योम);
व्योम rtnl_kमुक्त_skbs(काष्ठा sk_buff *head, काष्ठा sk_buff *tail);

#घोषणा ASSERT_RTNL() \
	WARN_ONCE(!rtnl_is_locked(), \
		  "RTNL: assertion failed at %s (%d)\n", __खाता__,  __LINE__)

बाह्य पूर्णांक nकरो_dflt_fdb_dump(काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb,
			     काष्ठा net_device *dev,
			     काष्ठा net_device *filter_dev,
			     पूर्णांक *idx);
बाह्य पूर्णांक nकरो_dflt_fdb_add(काष्ठा ndmsg *ndm,
			    काष्ठा nlattr *tb[],
			    काष्ठा net_device *dev,
			    स्थिर अचिन्हित अक्षर *addr,
			    u16 vid,
			    u16 flags);
बाह्य पूर्णांक nकरो_dflt_fdb_del(काष्ठा ndmsg *ndm,
			    काष्ठा nlattr *tb[],
			    काष्ठा net_device *dev,
			    स्थिर अचिन्हित अक्षर *addr,
			    u16 vid);

बाह्य पूर्णांक nकरो_dflt_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
				   काष्ठा net_device *dev, u16 mode,
				   u32 flags, u32 mask, पूर्णांक nlflags,
				   u32 filter_mask,
				   पूर्णांक (*vlan_fill)(काष्ठा sk_buff *skb,
						    काष्ठा net_device *dev,
						    u32 filter_mask));
#पूर्ण_अगर	/* __LINUX_RTNETLINK_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/net/l3mdev.h - L3 master device API
 * Copyright (c) 2015 Cumulus Networks
 * Copyright (c) 2015 David Ahern <dsa@cumulusnetworks.com>
 */
#अगर_अघोषित _NET_L3MDEV_H_
#घोषणा _NET_L3MDEV_H_

#समावेश <net/dst.h>
#समावेश <net/fib_rules.h>

क्रमागत l3mdev_type अणु
	L3MDEV_TYPE_UNSPEC,
	L3MDEV_TYPE_VRF,
	__L3MDEV_TYPE_MAX
पूर्ण;

#घोषणा L3MDEV_TYPE_MAX (__L3MDEV_TYPE_MAX - 1)

प्रकार पूर्णांक (*lookup_by_table_id_t)(काष्ठा net *net, u32 table_d);

/**
 * काष्ठा l3mdev_ops - l3mdev operations
 *
 * @l3mdev_fib_table: Get FIB table id to use क्रम lookups
 *
 * @l3mdev_l3_rcv:    Hook in L3 receive path
 *
 * @l3mdev_l3_out:    Hook in L3 output path
 *
 * @l3mdev_link_scope_lookup: IPv6 lookup क्रम linklocal and mcast destinations
 */

काष्ठा l3mdev_ops अणु
	u32		(*l3mdev_fib_table)(स्थिर काष्ठा net_device *dev);
	काष्ठा sk_buff * (*l3mdev_l3_rcv)(काष्ठा net_device *dev,
					  काष्ठा sk_buff *skb, u16 proto);
	काष्ठा sk_buff * (*l3mdev_l3_out)(काष्ठा net_device *dev,
					  काष्ठा sock *sk, काष्ठा sk_buff *skb,
					  u16 proto);

	/* IPv6 ops */
	काष्ठा dst_entry * (*l3mdev_link_scope_lookup)(स्थिर काष्ठा net_device *dev,
						 काष्ठा flowi6 *fl6);
पूर्ण;

#अगर_घोषित CONFIG_NET_L3_MASTER_DEV

पूर्णांक l3mdev_table_lookup_रेजिस्टर(क्रमागत l3mdev_type l3type,
				 lookup_by_table_id_t fn);

व्योम l3mdev_table_lookup_unरेजिस्टर(क्रमागत l3mdev_type l3type,
				    lookup_by_table_id_t fn);

पूर्णांक l3mdev_अगरindex_lookup_by_table_id(क्रमागत l3mdev_type l3type, काष्ठा net *net,
				      u32 table_id);

पूर्णांक l3mdev_fib_rule_match(काष्ठा net *net, काष्ठा flowi *fl,
			  काष्ठा fib_lookup_arg *arg);

व्योम l3mdev_update_flow(काष्ठा net *net, काष्ठा flowi *fl);

पूर्णांक l3mdev_master_अगरindex_rcu(स्थिर काष्ठा net_device *dev);
अटल अंतरभूत पूर्णांक l3mdev_master_अगरindex(काष्ठा net_device *dev)
अणु
	पूर्णांक अगरindex;

	rcu_पढ़ो_lock();
	अगरindex = l3mdev_master_अगरindex_rcu(dev);
	rcu_पढ़ो_unlock();

	वापस अगरindex;
पूर्ण

अटल अंतरभूत पूर्णांक l3mdev_master_अगरindex_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;
	पूर्णांक rc = 0;

	अगर (likely(अगरindex)) अणु
		rcu_पढ़ो_lock();

		dev = dev_get_by_index_rcu(net, अगरindex);
		अगर (dev)
			rc = l3mdev_master_अगरindex_rcu(dev);

		rcu_पढ़ो_unlock();
	पूर्ण

	वापस rc;
पूर्ण

अटल अंतरभूत
काष्ठा net_device *l3mdev_master_dev_rcu(स्थिर काष्ठा net_device *_dev)
अणु
	/* netdev_master_upper_dev_get_rcu calls
	 * list_first_or_null_rcu to walk the upper dev list.
	 * list_first_or_null_rcu करोes not handle a स्थिर arg. We aren't
	 * making changes, just want the master device from that list so
	 * typecast to हटाओ the स्थिर
	 */
	काष्ठा net_device *dev = (काष्ठा net_device *)_dev;
	काष्ठा net_device *master;

	अगर (!dev)
		वापस शून्य;

	अगर (netअगर_is_l3_master(dev))
		master = dev;
	अन्यथा अगर (netअगर_is_l3_slave(dev))
		master = netdev_master_upper_dev_get_rcu(dev);
	अन्यथा
		master = शून्य;

	वापस master;
पूर्ण

पूर्णांक l3mdev_master_upper_अगरindex_by_index_rcu(काष्ठा net *net, पूर्णांक अगरindex);
अटल अंतरभूत
पूर्णांक l3mdev_master_upper_अगरindex_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	rcu_पढ़ो_lock();
	अगरindex = l3mdev_master_upper_अगरindex_by_index_rcu(net, अगरindex);
	rcu_पढ़ो_unlock();

	वापस अगरindex;
पूर्ण

u32 l3mdev_fib_table_rcu(स्थिर काष्ठा net_device *dev);
u32 l3mdev_fib_table_by_index(काष्ठा net *net, पूर्णांक अगरindex);
अटल अंतरभूत u32 l3mdev_fib_table(स्थिर काष्ठा net_device *dev)
अणु
	u32 tb_id;

	rcu_पढ़ो_lock();
	tb_id = l3mdev_fib_table_rcu(dev);
	rcu_पढ़ो_unlock();

	वापस tb_id;
पूर्ण

अटल अंतरभूत bool netअगर_index_is_l3_master(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;
	bool rc = false;

	अगर (अगरindex == 0)
		वापस false;

	rcu_पढ़ो_lock();

	dev = dev_get_by_index_rcu(net, अगरindex);
	अगर (dev)
		rc = netअगर_is_l3_master(dev);

	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

काष्ठा dst_entry *l3mdev_link_scope_lookup(काष्ठा net *net, काष्ठा flowi6 *fl6);

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_l3_rcv(काष्ठा sk_buff *skb, u16 proto)
अणु
	काष्ठा net_device *master = शून्य;

	अगर (netअगर_is_l3_slave(skb->dev))
		master = netdev_master_upper_dev_get_rcu(skb->dev);
	अन्यथा अगर (netअगर_is_l3_master(skb->dev) ||
		 netअगर_has_l3_rx_handler(skb->dev))
		master = skb->dev;

	अगर (master && master->l3mdev_ops->l3mdev_l3_rcv)
		skb = master->l3mdev_ops->l3mdev_l3_rcv(master, skb, proto);

	वापस skb;
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_ip_rcv(काष्ठा sk_buff *skb)
अणु
	वापस l3mdev_l3_rcv(skb, AF_INET);
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_ip6_rcv(काष्ठा sk_buff *skb)
अणु
	वापस l3mdev_l3_rcv(skb, AF_INET6);
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_l3_out(काष्ठा sock *sk, काष्ठा sk_buff *skb, u16 proto)
अणु
	काष्ठा net_device *dev = skb_dst(skb)->dev;

	अगर (netअगर_is_l3_slave(dev)) अणु
		काष्ठा net_device *master;

		master = netdev_master_upper_dev_get_rcu(dev);
		अगर (master && master->l3mdev_ops->l3mdev_l3_out)
			skb = master->l3mdev_ops->l3mdev_l3_out(master, sk,
								skb, proto);
	पूर्ण

	वापस skb;
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_ip_out(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस l3mdev_l3_out(sk, skb, AF_INET);
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_ip6_out(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस l3mdev_l3_out(sk, skb, AF_INET6);
पूर्ण
#अन्यथा

अटल अंतरभूत पूर्णांक l3mdev_master_अगरindex_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक l3mdev_master_अगरindex(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक l3mdev_master_अगरindex_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक l3mdev_master_upper_अगरindex_by_index_rcu(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
पूर्णांक l3mdev_master_upper_अगरindex_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
काष्ठा net_device *l3mdev_master_dev_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत u32 l3mdev_fib_table_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत u32 l3mdev_fib_table(स्थिर काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत u32 l3mdev_fib_table_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool netअगर_index_is_l3_master(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत
काष्ठा dst_entry *l3mdev_link_scope_lookup(काष्ठा net *net, काष्ठा flowi6 *fl6)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_ip_rcv(काष्ठा sk_buff *skb)
अणु
	वापस skb;
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_ip6_rcv(काष्ठा sk_buff *skb)
अणु
	वापस skb;
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_ip_out(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस skb;
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *l3mdev_ip6_out(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस skb;
पूर्ण

अटल अंतरभूत
पूर्णांक l3mdev_table_lookup_रेजिस्टर(क्रमागत l3mdev_type l3type,
				 lookup_by_table_id_t fn)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत
व्योम l3mdev_table_lookup_unरेजिस्टर(क्रमागत l3mdev_type l3type,
				    lookup_by_table_id_t fn)
अणु
पूर्ण

अटल अंतरभूत
पूर्णांक l3mdev_अगरindex_lookup_by_table_id(क्रमागत l3mdev_type l3type, काष्ठा net *net,
				      u32 table_id)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत
पूर्णांक l3mdev_fib_rule_match(काष्ठा net *net, काष्ठा flowi *fl,
			  काष्ठा fib_lookup_arg *arg)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत
व्योम l3mdev_update_flow(काष्ठा net *net, काष्ठा flowi *fl)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _NET_L3MDEV_H_ */

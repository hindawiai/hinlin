<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/l3mdev/l3mdev.c - L3 master device implementation
 * Copyright (c) 2015 Cumulus Networks
 * Copyright (c) 2015 David Ahern <dsa@cumulusnetworks.com>
 */

#समावेश <linux/netdevice.h>
#समावेश <net/fib_rules.h>
#समावेश <net/l3mdev.h>

अटल DEFINE_SPINLOCK(l3mdev_lock);

काष्ठा l3mdev_handler अणु
	lookup_by_table_id_t dev_lookup;
पूर्ण;

अटल काष्ठा l3mdev_handler l3mdev_handlers[L3MDEV_TYPE_MAX + 1];

अटल पूर्णांक l3mdev_check_type(क्रमागत l3mdev_type l3type)
अणु
	अगर (l3type <= L3MDEV_TYPE_UNSPEC || l3type > L3MDEV_TYPE_MAX)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक l3mdev_table_lookup_रेजिस्टर(क्रमागत l3mdev_type l3type,
				 lookup_by_table_id_t fn)
अणु
	काष्ठा l3mdev_handler *hdlr;
	पूर्णांक res;

	res = l3mdev_check_type(l3type);
	अगर (res)
		वापस res;

	hdlr = &l3mdev_handlers[l3type];

	spin_lock(&l3mdev_lock);

	अगर (hdlr->dev_lookup) अणु
		res = -EBUSY;
		जाओ unlock;
	पूर्ण

	hdlr->dev_lookup = fn;
	res = 0;

unlock:
	spin_unlock(&l3mdev_lock);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_table_lookup_रेजिस्टर);

व्योम l3mdev_table_lookup_unरेजिस्टर(क्रमागत l3mdev_type l3type,
				    lookup_by_table_id_t fn)
अणु
	काष्ठा l3mdev_handler *hdlr;

	अगर (l3mdev_check_type(l3type))
		वापस;

	hdlr = &l3mdev_handlers[l3type];

	spin_lock(&l3mdev_lock);

	अगर (hdlr->dev_lookup == fn)
		hdlr->dev_lookup = शून्य;

	spin_unlock(&l3mdev_lock);
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_table_lookup_unरेजिस्टर);

पूर्णांक l3mdev_अगरindex_lookup_by_table_id(क्रमागत l3mdev_type l3type,
				      काष्ठा net *net, u32 table_id)
अणु
	lookup_by_table_id_t lookup;
	काष्ठा l3mdev_handler *hdlr;
	पूर्णांक अगरindex = -EINVAL;
	पूर्णांक res;

	res = l3mdev_check_type(l3type);
	अगर (res)
		वापस res;

	hdlr = &l3mdev_handlers[l3type];

	spin_lock(&l3mdev_lock);

	lookup = hdlr->dev_lookup;
	अगर (!lookup)
		जाओ unlock;

	अगरindex = lookup(net, table_id);

unlock:
	spin_unlock(&l3mdev_lock);

	वापस अगरindex;
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_अगरindex_lookup_by_table_id);

/**
 *	l3mdev_master_अगरindex_rcu - get index of L3 master device
 *	@dev: targeted पूर्णांकerface
 */

पूर्णांक l3mdev_master_अगरindex_rcu(स्थिर काष्ठा net_device *dev)
अणु
	पूर्णांक अगरindex = 0;

	अगर (!dev)
		वापस 0;

	अगर (netअगर_is_l3_master(dev)) अणु
		अगरindex = dev->अगरindex;
	पूर्ण अन्यथा अगर (netअगर_is_l3_slave(dev)) अणु
		काष्ठा net_device *master;
		काष्ठा net_device *_dev = (काष्ठा net_device *)dev;

		/* netdev_master_upper_dev_get_rcu calls
		 * list_first_or_null_rcu to walk the upper dev list.
		 * list_first_or_null_rcu करोes not handle a स्थिर arg. We aren't
		 * making changes, just want the master device from that list so
		 * typecast to हटाओ the स्थिर
		 */
		master = netdev_master_upper_dev_get_rcu(_dev);
		अगर (master)
			अगरindex = master->अगरindex;
	पूर्ण

	वापस अगरindex;
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_master_अगरindex_rcu);

/**
 *	l3mdev_master_upper_अगरindex_by_index_rcu - get index of upper l3 master
 *					       device
 *	@net: network namespace क्रम device index lookup
 *	@अगरindex: targeted पूर्णांकerface
 */
पूर्णांक l3mdev_master_upper_अगरindex_by_index_rcu(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;

	dev = dev_get_by_index_rcu(net, अगरindex);
	जबतक (dev && !netअगर_is_l3_master(dev))
		dev = netdev_master_upper_dev_get(dev);

	वापस dev ? dev->अगरindex : 0;
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_master_upper_अगरindex_by_index_rcu);

/**
 *	l3mdev_fib_table_rcu - get FIB table id associated with an L3
 *                             master पूर्णांकerface
 *	@dev: targeted पूर्णांकerface
 */

u32 l3mdev_fib_table_rcu(स्थिर काष्ठा net_device *dev)
अणु
	u32 tb_id = 0;

	अगर (!dev)
		वापस 0;

	अगर (netअगर_is_l3_master(dev)) अणु
		अगर (dev->l3mdev_ops->l3mdev_fib_table)
			tb_id = dev->l3mdev_ops->l3mdev_fib_table(dev);
	पूर्ण अन्यथा अगर (netअगर_is_l3_slave(dev)) अणु
		/* Users of netdev_master_upper_dev_get_rcu need non-स्थिर,
		 * but current inet_*type functions take a स्थिर
		 */
		काष्ठा net_device *_dev = (काष्ठा net_device *) dev;
		स्थिर काष्ठा net_device *master;

		master = netdev_master_upper_dev_get_rcu(_dev);
		अगर (master &&
		    master->l3mdev_ops->l3mdev_fib_table)
			tb_id = master->l3mdev_ops->l3mdev_fib_table(master);
	पूर्ण

	वापस tb_id;
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_fib_table_rcu);

u32 l3mdev_fib_table_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;
	u32 tb_id = 0;

	अगर (!अगरindex)
		वापस 0;

	rcu_पढ़ो_lock();

	dev = dev_get_by_index_rcu(net, अगरindex);
	अगर (dev)
		tb_id = l3mdev_fib_table_rcu(dev);

	rcu_पढ़ो_unlock();

	वापस tb_id;
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_fib_table_by_index);

/**
 *	l3mdev_link_scope_lookup - IPv6 route lookup based on flow क्रम link
 *			     local and multicast addresses
 *	@net: network namespace क्रम device index lookup
 *	@fl6: IPv6 flow काष्ठा क्रम lookup
 *	This function करोes not hold refcnt on the वापसed dst.
 *	Caller must hold rcu_पढ़ो_lock().
 */

काष्ठा dst_entry *l3mdev_link_scope_lookup(काष्ठा net *net,
					   काष्ठा flowi6 *fl6)
अणु
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा net_device *dev;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	अगर (fl6->flowi6_oअगर) अणु
		dev = dev_get_by_index_rcu(net, fl6->flowi6_oअगर);
		अगर (dev && netअगर_is_l3_slave(dev))
			dev = netdev_master_upper_dev_get_rcu(dev);

		अगर (dev && netअगर_is_l3_master(dev) &&
		    dev->l3mdev_ops->l3mdev_link_scope_lookup)
			dst = dev->l3mdev_ops->l3mdev_link_scope_lookup(dev, fl6);
	पूर्ण

	वापस dst;
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_link_scope_lookup);

/**
 *	l3mdev_fib_rule_match - Determine अगर flowi references an
 *				L3 master device
 *	@net: network namespace क्रम device index lookup
 *	@fl:  flow काष्ठा
 *	@arg: store the table the rule matched with here
 */

पूर्णांक l3mdev_fib_rule_match(काष्ठा net *net, काष्ठा flowi *fl,
			  काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा net_device *dev;
	पूर्णांक rc = 0;

	rcu_पढ़ो_lock();

	dev = dev_get_by_index_rcu(net, fl->flowi_oअगर);
	अगर (dev && netअगर_is_l3_master(dev) &&
	    dev->l3mdev_ops->l3mdev_fib_table) अणु
		arg->table = dev->l3mdev_ops->l3mdev_fib_table(dev);
		rc = 1;
		जाओ out;
	पूर्ण

	dev = dev_get_by_index_rcu(net, fl->flowi_iअगर);
	अगर (dev && netअगर_is_l3_master(dev) &&
	    dev->l3mdev_ops->l3mdev_fib_table) अणु
		arg->table = dev->l3mdev_ops->l3mdev_fib_table(dev);
		rc = 1;
		जाओ out;
	पूर्ण

out:
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

व्योम l3mdev_update_flow(काष्ठा net *net, काष्ठा flowi *fl)
अणु
	काष्ठा net_device *dev;
	पूर्णांक अगरindex;

	rcu_पढ़ो_lock();

	अगर (fl->flowi_oअगर) अणु
		dev = dev_get_by_index_rcu(net, fl->flowi_oअगर);
		अगर (dev) अणु
			अगरindex = l3mdev_master_अगरindex_rcu(dev);
			अगर (अगरindex) अणु
				fl->flowi_oअगर = अगरindex;
				fl->flowi_flags |= FLOWI_FLAG_SKIP_NH_OIF;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (fl->flowi_iअगर) अणु
		dev = dev_get_by_index_rcu(net, fl->flowi_iअगर);
		अगर (dev) अणु
			अगरindex = l3mdev_master_अगरindex_rcu(dev);
			अगर (अगरindex) अणु
				fl->flowi_iअगर = अगरindex;
				fl->flowi_flags |= FLOWI_FLAG_SKIP_NH_OIF;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(l3mdev_update_flow);

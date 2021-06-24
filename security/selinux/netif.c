<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Network पूर्णांकerface table.
 *
 * Network पूर्णांकerfaces (devices) करो not have a security field, so we
 * मुख्यtain a table associating each पूर्णांकerface with a SID.
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2003 Red Hat, Inc., James Morris <jmorris@redhat.com>
 * Copyright (C) 2007 Hewlett-Packard Development Company, L.P.
 *		      Paul Moore <paul@paul-moore.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rcupdate.h>
#समावेश <net/net_namespace.h>

#समावेश "security.h"
#समावेश "objsec.h"
#समावेश "netif.h"

#घोषणा SEL_NETIF_HASH_SIZE	64
#घोषणा SEL_NETIF_HASH_MAX	1024

काष्ठा sel_netअगर अणु
	काष्ठा list_head list;
	काष्ठा netअगर_security_काष्ठा nsec;
	काष्ठा rcu_head rcu_head;
पूर्ण;

अटल u32 sel_netअगर_total;
अटल DEFINE_SPINLOCK(sel_netअगर_lock);
अटल काष्ठा list_head sel_netअगर_hash[SEL_NETIF_HASH_SIZE];

/**
 * sel_netअगर_hashfn - Hashing function क्रम the पूर्णांकerface table
 * @ns: the network namespace
 * @अगरindex: the network पूर्णांकerface
 *
 * Description:
 * This is the hashing function क्रम the network पूर्णांकerface table, it वापसs the
 * bucket number क्रम the given पूर्णांकerface.
 *
 */
अटल अंतरभूत u32 sel_netअगर_hashfn(स्थिर काष्ठा net *ns, पूर्णांक अगरindex)
अणु
	वापस (((uपूर्णांकptr_t)ns + अगरindex) & (SEL_NETIF_HASH_SIZE - 1));
पूर्ण

/**
 * sel_netअगर_find - Search क्रम an पूर्णांकerface record
 * @ns: the network namespace
 * @अगरindex: the network पूर्णांकerface
 *
 * Description:
 * Search the network पूर्णांकerface table and वापस the record matching @अगरindex.
 * If an entry can not be found in the table वापस शून्य.
 *
 */
अटल अंतरभूत काष्ठा sel_netअगर *sel_netअगर_find(स्थिर काष्ठा net *ns,
					       पूर्णांक अगरindex)
अणु
	पूर्णांक idx = sel_netअगर_hashfn(ns, अगरindex);
	काष्ठा sel_netअगर *netअगर;

	list_क्रम_each_entry_rcu(netअगर, &sel_netअगर_hash[idx], list)
		अगर (net_eq(netअगर->nsec.ns, ns) &&
		    netअगर->nsec.अगरindex == अगरindex)
			वापस netअगर;

	वापस शून्य;
पूर्ण

/**
 * sel_netअगर_insert - Insert a new पूर्णांकerface पूर्णांकo the table
 * @netअगर: the new पूर्णांकerface record
 *
 * Description:
 * Add a new पूर्णांकerface record to the network पूर्णांकerface hash table.  Returns
 * zero on success, negative values on failure.
 *
 */
अटल पूर्णांक sel_netअगर_insert(काष्ठा sel_netअगर *netअगर)
अणु
	पूर्णांक idx;

	अगर (sel_netअगर_total >= SEL_NETIF_HASH_MAX)
		वापस -ENOSPC;

	idx = sel_netअगर_hashfn(netअगर->nsec.ns, netअगर->nsec.अगरindex);
	list_add_rcu(&netअगर->list, &sel_netअगर_hash[idx]);
	sel_netअगर_total++;

	वापस 0;
पूर्ण

/**
 * sel_netअगर_destroy - Remove an पूर्णांकerface record from the table
 * @netअगर: the existing पूर्णांकerface record
 *
 * Description:
 * Remove an existing पूर्णांकerface record from the network पूर्णांकerface table.
 *
 */
अटल व्योम sel_netअगर_destroy(काष्ठा sel_netअगर *netअगर)
अणु
	list_del_rcu(&netअगर->list);
	sel_netअगर_total--;
	kमुक्त_rcu(netअगर, rcu_head);
पूर्ण

/**
 * sel_netअगर_sid_slow - Lookup the SID of a network पूर्णांकerface using the policy
 * @ns: the network namespace
 * @अगरindex: the network पूर्णांकerface
 * @sid: पूर्णांकerface SID
 *
 * Description:
 * This function determines the SID of a network पूर्णांकerface by querying the
 * security policy.  The result is added to the network पूर्णांकerface table to
 * speedup future queries.  Returns zero on success, negative values on
 * failure.
 *
 */
अटल पूर्णांक sel_netअगर_sid_slow(काष्ठा net *ns, पूर्णांक अगरindex, u32 *sid)
अणु
	पूर्णांक ret = 0;
	काष्ठा sel_netअगर *netअगर;
	काष्ठा sel_netअगर *new;
	काष्ठा net_device *dev;

	/* NOTE: we always use init's network namespace since we don't
	 * currently support containers */

	dev = dev_get_by_index(ns, अगरindex);
	अगर (unlikely(dev == शून्य)) अणु
		pr_warn("SELinux: failure in %s(), invalid network interface (%d)\n",
			__func__, अगरindex);
		वापस -ENOENT;
	पूर्ण

	spin_lock_bh(&sel_netअगर_lock);
	netअगर = sel_netअगर_find(ns, अगरindex);
	अगर (netअगर != शून्य) अणु
		*sid = netअगर->nsec.sid;
		जाओ out;
	पूर्ण

	ret = security_netअगर_sid(&selinux_state, dev->name, sid);
	अगर (ret != 0)
		जाओ out;
	new = kzalloc(माप(*new), GFP_ATOMIC);
	अगर (new) अणु
		new->nsec.ns = ns;
		new->nsec.अगरindex = अगरindex;
		new->nsec.sid = *sid;
		अगर (sel_netअगर_insert(new))
			kमुक्त(new);
	पूर्ण

out:
	spin_unlock_bh(&sel_netअगर_lock);
	dev_put(dev);
	अगर (unlikely(ret))
		pr_warn("SELinux: failure in %s(), unable to determine network interface label (%d)\n",
			__func__, अगरindex);
	वापस ret;
पूर्ण

/**
 * sel_netअगर_sid - Lookup the SID of a network पूर्णांकerface
 * @ns: the network namespace
 * @अगरindex: the network पूर्णांकerface
 * @sid: पूर्णांकerface SID
 *
 * Description:
 * This function determines the SID of a network पूर्णांकerface using the fastest
 * method possible.  First the पूर्णांकerface table is queried, but अगर an entry
 * can't be found then the policy is queried and the result is added to the
 * table to speedup future queries.  Returns zero on success, negative values
 * on failure.
 *
 */
पूर्णांक sel_netअगर_sid(काष्ठा net *ns, पूर्णांक अगरindex, u32 *sid)
अणु
	काष्ठा sel_netअगर *netअगर;

	rcu_पढ़ो_lock();
	netअगर = sel_netअगर_find(ns, अगरindex);
	अगर (likely(netअगर != शून्य)) अणु
		*sid = netअगर->nsec.sid;
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस sel_netअगर_sid_slow(ns, अगरindex, sid);
पूर्ण

/**
 * sel_netअगर_समाप्त - Remove an entry from the network पूर्णांकerface table
 * @ns: the network namespace
 * @अगरindex: the network पूर्णांकerface
 *
 * Description:
 * This function हटाओs the entry matching @अगरindex from the network पूर्णांकerface
 * table अगर it exists.
 *
 */
अटल व्योम sel_netअगर_समाप्त(स्थिर काष्ठा net *ns, पूर्णांक अगरindex)
अणु
	काष्ठा sel_netअगर *netअगर;

	rcu_पढ़ो_lock();
	spin_lock_bh(&sel_netअगर_lock);
	netअगर = sel_netअगर_find(ns, अगरindex);
	अगर (netअगर)
		sel_netअगर_destroy(netअगर);
	spin_unlock_bh(&sel_netअगर_lock);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * sel_netअगर_flush - Flush the entire network पूर्णांकerface table
 *
 * Description:
 * Remove all entries from the network पूर्णांकerface table.
 *
 */
व्योम sel_netअगर_flush(व्योम)
अणु
	पूर्णांक idx;
	काष्ठा sel_netअगर *netअगर;

	spin_lock_bh(&sel_netअगर_lock);
	क्रम (idx = 0; idx < SEL_NETIF_HASH_SIZE; idx++)
		list_क्रम_each_entry(netअगर, &sel_netअगर_hash[idx], list)
			sel_netअगर_destroy(netअगर);
	spin_unlock_bh(&sel_netअगर_lock);
पूर्ण

अटल पूर्णांक sel_netअगर_netdev_notअगरier_handler(काष्ठा notअगरier_block *this,
					     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (event == NETDEV_DOWN)
		sel_netअगर_समाप्त(dev_net(dev), dev->अगरindex);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block sel_netअगर_netdev_notअगरier = अणु
	.notअगरier_call = sel_netअगर_netdev_notअगरier_handler,
पूर्ण;

अटल __init पूर्णांक sel_netअगर_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!selinux_enabled_boot)
		वापस 0;

	क्रम (i = 0; i < SEL_NETIF_HASH_SIZE; i++)
		INIT_LIST_HEAD(&sel_netअगर_hash[i]);

	रेजिस्टर_netdevice_notअगरier(&sel_netअगर_netdev_notअगरier);

	वापस 0;
पूर्ण

__initcall(sel_netअगर_init);


<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Network port table
 *
 * SELinux must keep a mapping of network ports to labels/SIDs.  This
 * mapping is मुख्यtained as part of the normal policy but a fast cache is
 * needed to reduce the lookup overhead.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 *
 * This code is heavily based on the "netif" concept originally developed by
 * James Morris <jmorris@redhat.com>
 *   (see security/selinux/netअगर.c क्रम more inक्रमmation)
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2008
 */

#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>

#समावेश "netport.h"
#समावेश "objsec.h"

#घोषणा SEL_NETPORT_HASH_SIZE       256
#घोषणा SEL_NETPORT_HASH_BKT_LIMIT   16

काष्ठा sel_netport_bkt अणु
	पूर्णांक size;
	काष्ठा list_head list;
पूर्ण;

काष्ठा sel_netport अणु
	काष्ठा netport_security_काष्ठा psec;

	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

/* NOTE: we are using a combined hash table क्रम both IPv4 and IPv6, the reason
 * क्रम this is that I suspect most users will not make heavy use of both
 * address families at the same समय so one table will usually end up wasted,
 * अगर this becomes a problem we can always add a hash table क्रम each address
 * family later */

अटल DEFINE_SPINLOCK(sel_netport_lock);
अटल काष्ठा sel_netport_bkt sel_netport_hash[SEL_NETPORT_HASH_SIZE];

/**
 * sel_netport_hashfn - Hashing function क्रम the port table
 * @pnum: port number
 *
 * Description:
 * This is the hashing function क्रम the port table, it वापसs the bucket
 * number क्रम the given port.
 *
 */
अटल अचिन्हित पूर्णांक sel_netport_hashfn(u16 pnum)
अणु
	वापस (pnum & (SEL_NETPORT_HASH_SIZE - 1));
पूर्ण

/**
 * sel_netport_find - Search क्रम a port record
 * @protocol: protocol
 * @port: pnum
 *
 * Description:
 * Search the network port table and वापस the matching record.  If an entry
 * can not be found in the table वापस शून्य.
 *
 */
अटल काष्ठा sel_netport *sel_netport_find(u8 protocol, u16 pnum)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा sel_netport *port;

	idx = sel_netport_hashfn(pnum);
	list_क्रम_each_entry_rcu(port, &sel_netport_hash[idx].list, list)
		अगर (port->psec.port == pnum && port->psec.protocol == protocol)
			वापस port;

	वापस शून्य;
पूर्ण

/**
 * sel_netport_insert - Insert a new port पूर्णांकo the table
 * @port: the new port record
 *
 * Description:
 * Add a new port record to the network address hash table.
 *
 */
अटल व्योम sel_netport_insert(काष्ठा sel_netport *port)
अणु
	अचिन्हित पूर्णांक idx;

	/* we need to impose a limit on the growth of the hash table so check
	 * this bucket to make sure it is within the specअगरied bounds */
	idx = sel_netport_hashfn(port->psec.port);
	list_add_rcu(&port->list, &sel_netport_hash[idx].list);
	अगर (sel_netport_hash[idx].size == SEL_NETPORT_HASH_BKT_LIMIT) अणु
		काष्ठा sel_netport *tail;
		tail = list_entry(
			rcu_dereference_रक्षित(
				sel_netport_hash[idx].list.prev,
				lockdep_is_held(&sel_netport_lock)),
			काष्ठा sel_netport, list);
		list_del_rcu(&tail->list);
		kमुक्त_rcu(tail, rcu);
	पूर्ण अन्यथा
		sel_netport_hash[idx].size++;
पूर्ण

/**
 * sel_netport_sid_slow - Lookup the SID of a network address using the policy
 * @protocol: protocol
 * @pnum: port
 * @sid: port SID
 *
 * Description:
 * This function determines the SID of a network port by querying the security
 * policy.  The result is added to the network port table to speedup future
 * queries.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक sel_netport_sid_slow(u8 protocol, u16 pnum, u32 *sid)
अणु
	पूर्णांक ret;
	काष्ठा sel_netport *port;
	काष्ठा sel_netport *new;

	spin_lock_bh(&sel_netport_lock);
	port = sel_netport_find(protocol, pnum);
	अगर (port != शून्य) अणु
		*sid = port->psec.sid;
		spin_unlock_bh(&sel_netport_lock);
		वापस 0;
	पूर्ण

	ret = security_port_sid(&selinux_state, protocol, pnum, sid);
	अगर (ret != 0)
		जाओ out;
	new = kzalloc(माप(*new), GFP_ATOMIC);
	अगर (new) अणु
		new->psec.port = pnum;
		new->psec.protocol = protocol;
		new->psec.sid = *sid;
		sel_netport_insert(new);
	पूर्ण

out:
	spin_unlock_bh(&sel_netport_lock);
	अगर (unlikely(ret))
		pr_warn("SELinux: failure in %s(), unable to determine network port label\n",
			__func__);
	वापस ret;
पूर्ण

/**
 * sel_netport_sid - Lookup the SID of a network port
 * @protocol: protocol
 * @pnum: port
 * @sid: port SID
 *
 * Description:
 * This function determines the SID of a network port using the fastest method
 * possible.  First the port table is queried, but अगर an entry can't be found
 * then the policy is queried and the result is added to the table to speedup
 * future queries.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक sel_netport_sid(u8 protocol, u16 pnum, u32 *sid)
अणु
	काष्ठा sel_netport *port;

	rcu_पढ़ो_lock();
	port = sel_netport_find(protocol, pnum);
	अगर (port != शून्य) अणु
		*sid = port->psec.sid;
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस sel_netport_sid_slow(protocol, pnum, sid);
पूर्ण

/**
 * sel_netport_flush - Flush the entire network port table
 *
 * Description:
 * Remove all entries from the network address table.
 *
 */
व्योम sel_netport_flush(व्योम)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा sel_netport *port, *port_पंचांगp;

	spin_lock_bh(&sel_netport_lock);
	क्रम (idx = 0; idx < SEL_NETPORT_HASH_SIZE; idx++) अणु
		list_क्रम_each_entry_safe(port, port_पंचांगp,
					 &sel_netport_hash[idx].list, list) अणु
			list_del_rcu(&port->list);
			kमुक्त_rcu(port, rcu);
		पूर्ण
		sel_netport_hash[idx].size = 0;
	पूर्ण
	spin_unlock_bh(&sel_netport_lock);
पूर्ण

अटल __init पूर्णांक sel_netport_init(व्योम)
अणु
	पूर्णांक iter;

	अगर (!selinux_enabled_boot)
		वापस 0;

	क्रम (iter = 0; iter < SEL_NETPORT_HASH_SIZE; iter++) अणु
		INIT_LIST_HEAD(&sel_netport_hash[iter].list);
		sel_netport_hash[iter].size = 0;
	पूर्ण

	वापस 0;
पूर्ण

__initcall(sel_netport_init);

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Network node table
 *
 * SELinux must keep a mapping of network nodes to labels/SIDs.  This
 * mapping is मुख्यtained as part of the normal policy but a fast cache is
 * needed to reduce the lookup overhead since most of these queries happen on
 * a per-packet basis.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 *
 * This code is heavily based on the "netif" concept originally developed by
 * James Morris <jmorris@redhat.com>
 *   (see security/selinux/netअगर.c क्रम more inक्रमmation)
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2007
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

#समावेश "netnode.h"
#समावेश "objsec.h"

#घोषणा SEL_NETNODE_HASH_SIZE       256
#घोषणा SEL_NETNODE_HASH_BKT_LIMIT   16

काष्ठा sel_netnode_bkt अणु
	अचिन्हित पूर्णांक size;
	काष्ठा list_head list;
पूर्ण;

काष्ठा sel_netnode अणु
	काष्ठा netnode_security_काष्ठा nsec;

	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

/* NOTE: we are using a combined hash table क्रम both IPv4 and IPv6, the reason
 * क्रम this is that I suspect most users will not make heavy use of both
 * address families at the same समय so one table will usually end up wasted,
 * अगर this becomes a problem we can always add a hash table क्रम each address
 * family later */

अटल DEFINE_SPINLOCK(sel_netnode_lock);
अटल काष्ठा sel_netnode_bkt sel_netnode_hash[SEL_NETNODE_HASH_SIZE];

/**
 * sel_netnode_hashfn_ipv4 - IPv4 hashing function क्रम the node table
 * @addr: IPv4 address
 *
 * Description:
 * This is the IPv4 hashing function क्रम the node पूर्णांकerface table, it वापसs
 * the bucket number क्रम the given IP address.
 *
 */
अटल अचिन्हित पूर्णांक sel_netnode_hashfn_ipv4(__be32 addr)
अणु
	/* at some poपूर्णांक we should determine अगर the mismatch in byte order
	 * affects the hash function dramatically */
	वापस (addr & (SEL_NETNODE_HASH_SIZE - 1));
पूर्ण

/**
 * sel_netnode_hashfn_ipv6 - IPv6 hashing function क्रम the node table
 * @addr: IPv6 address
 *
 * Description:
 * This is the IPv6 hashing function क्रम the node पूर्णांकerface table, it वापसs
 * the bucket number क्रम the given IP address.
 *
 */
अटल अचिन्हित पूर्णांक sel_netnode_hashfn_ipv6(स्थिर काष्ठा in6_addr *addr)
अणु
	/* just hash the least signअगरicant 32 bits to keep things fast (they
	 * are the most likely to be dअगरferent anyway), we can revisit this
	 * later अगर needed */
	वापस (addr->s6_addr32[3] & (SEL_NETNODE_HASH_SIZE - 1));
पूर्ण

/**
 * sel_netnode_find - Search क्रम a node record
 * @addr: IP address
 * @family: address family
 *
 * Description:
 * Search the network node table and वापस the record matching @addr.  If an
 * entry can not be found in the table वापस शून्य.
 *
 */
अटल काष्ठा sel_netnode *sel_netnode_find(स्थिर व्योम *addr, u16 family)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा sel_netnode *node;

	चयन (family) अणु
	हाल PF_INET:
		idx = sel_netnode_hashfn_ipv4(*(__be32 *)addr);
		अवरोध;
	हाल PF_INET6:
		idx = sel_netnode_hashfn_ipv6(addr);
		अवरोध;
	शेष:
		BUG();
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry_rcu(node, &sel_netnode_hash[idx].list, list)
		अगर (node->nsec.family == family)
			चयन (family) अणु
			हाल PF_INET:
				अगर (node->nsec.addr.ipv4 == *(__be32 *)addr)
					वापस node;
				अवरोध;
			हाल PF_INET6:
				अगर (ipv6_addr_equal(&node->nsec.addr.ipv6,
						    addr))
					वापस node;
				अवरोध;
			पूर्ण

	वापस शून्य;
पूर्ण

/**
 * sel_netnode_insert - Insert a new node पूर्णांकo the table
 * @node: the new node record
 *
 * Description:
 * Add a new node record to the network address hash table.
 *
 */
अटल व्योम sel_netnode_insert(काष्ठा sel_netnode *node)
अणु
	अचिन्हित पूर्णांक idx;

	चयन (node->nsec.family) अणु
	हाल PF_INET:
		idx = sel_netnode_hashfn_ipv4(node->nsec.addr.ipv4);
		अवरोध;
	हाल PF_INET6:
		idx = sel_netnode_hashfn_ipv6(&node->nsec.addr.ipv6);
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण

	/* we need to impose a limit on the growth of the hash table so check
	 * this bucket to make sure it is within the specअगरied bounds */
	list_add_rcu(&node->list, &sel_netnode_hash[idx].list);
	अगर (sel_netnode_hash[idx].size == SEL_NETNODE_HASH_BKT_LIMIT) अणु
		काष्ठा sel_netnode *tail;
		tail = list_entry(
			rcu_dereference_रक्षित(sel_netnode_hash[idx].list.prev,
						  lockdep_is_held(&sel_netnode_lock)),
			काष्ठा sel_netnode, list);
		list_del_rcu(&tail->list);
		kमुक्त_rcu(tail, rcu);
	पूर्ण अन्यथा
		sel_netnode_hash[idx].size++;
पूर्ण

/**
 * sel_netnode_sid_slow - Lookup the SID of a network address using the policy
 * @addr: the IP address
 * @family: the address family
 * @sid: node SID
 *
 * Description:
 * This function determines the SID of a network address by querying the
 * security policy.  The result is added to the network address table to
 * speedup future queries.  Returns zero on success, negative values on
 * failure.
 *
 */
अटल पूर्णांक sel_netnode_sid_slow(व्योम *addr, u16 family, u32 *sid)
अणु
	पूर्णांक ret;
	काष्ठा sel_netnode *node;
	काष्ठा sel_netnode *new;

	spin_lock_bh(&sel_netnode_lock);
	node = sel_netnode_find(addr, family);
	अगर (node != शून्य) अणु
		*sid = node->nsec.sid;
		spin_unlock_bh(&sel_netnode_lock);
		वापस 0;
	पूर्ण

	new = kzalloc(माप(*new), GFP_ATOMIC);
	चयन (family) अणु
	हाल PF_INET:
		ret = security_node_sid(&selinux_state, PF_INET,
					addr, माप(काष्ठा in_addr), sid);
		अगर (new)
			new->nsec.addr.ipv4 = *(__be32 *)addr;
		अवरोध;
	हाल PF_INET6:
		ret = security_node_sid(&selinux_state, PF_INET6,
					addr, माप(काष्ठा in6_addr), sid);
		अगर (new)
			new->nsec.addr.ipv6 = *(काष्ठा in6_addr *)addr;
		अवरोध;
	शेष:
		BUG();
		ret = -EINVAL;
	पूर्ण
	अगर (ret == 0 && new) अणु
		new->nsec.family = family;
		new->nsec.sid = *sid;
		sel_netnode_insert(new);
	पूर्ण अन्यथा
		kमुक्त(new);

	spin_unlock_bh(&sel_netnode_lock);
	अगर (unlikely(ret))
		pr_warn("SELinux: failure in %s(), unable to determine network node label\n",
			__func__);
	वापस ret;
पूर्ण

/**
 * sel_netnode_sid - Lookup the SID of a network address
 * @addr: the IP address
 * @family: the address family
 * @sid: node SID
 *
 * Description:
 * This function determines the SID of a network address using the fastest
 * method possible.  First the address table is queried, but अगर an entry
 * can't be found then the policy is queried and the result is added to the
 * table to speedup future queries.  Returns zero on success, negative values
 * on failure.
 *
 */
पूर्णांक sel_netnode_sid(व्योम *addr, u16 family, u32 *sid)
अणु
	काष्ठा sel_netnode *node;

	rcu_पढ़ो_lock();
	node = sel_netnode_find(addr, family);
	अगर (node != शून्य) अणु
		*sid = node->nsec.sid;
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस sel_netnode_sid_slow(addr, family, sid);
पूर्ण

/**
 * sel_netnode_flush - Flush the entire network address table
 *
 * Description:
 * Remove all entries from the network address table.
 *
 */
व्योम sel_netnode_flush(व्योम)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा sel_netnode *node, *node_पंचांगp;

	spin_lock_bh(&sel_netnode_lock);
	क्रम (idx = 0; idx < SEL_NETNODE_HASH_SIZE; idx++) अणु
		list_क्रम_each_entry_safe(node, node_पंचांगp,
					 &sel_netnode_hash[idx].list, list) अणु
				list_del_rcu(&node->list);
				kमुक्त_rcu(node, rcu);
		पूर्ण
		sel_netnode_hash[idx].size = 0;
	पूर्ण
	spin_unlock_bh(&sel_netnode_lock);
पूर्ण

अटल __init पूर्णांक sel_netnode_init(व्योम)
अणु
	पूर्णांक iter;

	अगर (!selinux_enabled_boot)
		वापस 0;

	क्रम (iter = 0; iter < SEL_NETNODE_HASH_SIZE; iter++) अणु
		INIT_LIST_HEAD(&sel_netnode_hash[iter].list);
		sel_netnode_hash[iter].size = 0;
	पूर्ण

	वापस 0;
पूर्ण

__initcall(sel_netnode_init);

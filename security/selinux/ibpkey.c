<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pkey table
 *
 * SELinux must keep a mapping of Infinband PKEYs to labels/SIDs.  This
 * mapping is मुख्यtained as part of the normal policy but a fast cache is
 * needed to reduce the lookup overhead.
 *
 * This code is heavily based on the "netif" and "netport" concept originally
 * developed by
 * James Morris <jmorris@redhat.com> and
 * Paul Moore <paul@paul-moore.com>
 *   (see security/selinux/netअगर.c and security/selinux/netport.c क्रम more
 *   inक्रमmation)
 */

/*
 * (c) Mellanox Technologies, 2016
 */

#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

#समावेश "ibpkey.h"
#समावेश "objsec.h"

#घोषणा SEL_PKEY_HASH_SIZE       256
#घोषणा SEL_PKEY_HASH_BKT_LIMIT   16

काष्ठा sel_ib_pkey_bkt अणु
	पूर्णांक size;
	काष्ठा list_head list;
पूर्ण;

काष्ठा sel_ib_pkey अणु
	काष्ठा pkey_security_काष्ठा psec;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल DEFINE_SPINLOCK(sel_ib_pkey_lock);
अटल काष्ठा sel_ib_pkey_bkt sel_ib_pkey_hash[SEL_PKEY_HASH_SIZE];

/**
 * sel_ib_pkey_hashfn - Hashing function क्रम the pkey table
 * @pkey: pkey number
 *
 * Description:
 * This is the hashing function क्रम the pkey table, it वापसs the bucket
 * number क्रम the given pkey.
 *
 */
अटल अचिन्हित पूर्णांक sel_ib_pkey_hashfn(u16 pkey)
अणु
	वापस (pkey & (SEL_PKEY_HASH_SIZE - 1));
पूर्ण

/**
 * sel_ib_pkey_find - Search क्रम a pkey record
 * @subnet_prefix: subnet_prefix
 * @pkey_num: pkey_num
 *
 * Description:
 * Search the pkey table and वापस the matching record.  If an entry
 * can not be found in the table वापस शून्य.
 *
 */
अटल काष्ठा sel_ib_pkey *sel_ib_pkey_find(u64 subnet_prefix, u16 pkey_num)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा sel_ib_pkey *pkey;

	idx = sel_ib_pkey_hashfn(pkey_num);
	list_क्रम_each_entry_rcu(pkey, &sel_ib_pkey_hash[idx].list, list) अणु
		अगर (pkey->psec.pkey == pkey_num &&
		    pkey->psec.subnet_prefix == subnet_prefix)
			वापस pkey;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * sel_ib_pkey_insert - Insert a new pkey पूर्णांकo the table
 * @pkey: the new pkey record
 *
 * Description:
 * Add a new pkey record to the hash table.
 *
 */
अटल व्योम sel_ib_pkey_insert(काष्ठा sel_ib_pkey *pkey)
अणु
	अचिन्हित पूर्णांक idx;

	/* we need to impose a limit on the growth of the hash table so check
	 * this bucket to make sure it is within the specअगरied bounds
	 */
	idx = sel_ib_pkey_hashfn(pkey->psec.pkey);
	list_add_rcu(&pkey->list, &sel_ib_pkey_hash[idx].list);
	अगर (sel_ib_pkey_hash[idx].size == SEL_PKEY_HASH_BKT_LIMIT) अणु
		काष्ठा sel_ib_pkey *tail;

		tail = list_entry(
			rcu_dereference_रक्षित(
				sel_ib_pkey_hash[idx].list.prev,
				lockdep_is_held(&sel_ib_pkey_lock)),
			काष्ठा sel_ib_pkey, list);
		list_del_rcu(&tail->list);
		kमुक्त_rcu(tail, rcu);
	पूर्ण अन्यथा अणु
		sel_ib_pkey_hash[idx].size++;
	पूर्ण
पूर्ण

/**
 * sel_ib_pkey_sid_slow - Lookup the SID of a pkey using the policy
 * @subnet_prefix: subnet prefix
 * @pkey_num: pkey number
 * @sid: pkey SID
 *
 * Description:
 * This function determines the SID of a pkey by querying the security
 * policy.  The result is added to the pkey table to speedup future
 * queries.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक sel_ib_pkey_sid_slow(u64 subnet_prefix, u16 pkey_num, u32 *sid)
अणु
	पूर्णांक ret;
	काष्ठा sel_ib_pkey *pkey;
	काष्ठा sel_ib_pkey *new = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sel_ib_pkey_lock, flags);
	pkey = sel_ib_pkey_find(subnet_prefix, pkey_num);
	अगर (pkey) अणु
		*sid = pkey->psec.sid;
		spin_unlock_irqrestore(&sel_ib_pkey_lock, flags);
		वापस 0;
	पूर्ण

	ret = security_ib_pkey_sid(&selinux_state, subnet_prefix, pkey_num,
				   sid);
	अगर (ret)
		जाओ out;

	/* If this memory allocation fails still वापस 0. The SID
	 * is valid, it just won't be added to the cache.
	 */
	new = kzalloc(माप(*new), GFP_ATOMIC);
	अगर (!new) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	new->psec.subnet_prefix = subnet_prefix;
	new->psec.pkey = pkey_num;
	new->psec.sid = *sid;
	sel_ib_pkey_insert(new);

out:
	spin_unlock_irqrestore(&sel_ib_pkey_lock, flags);
	वापस ret;
पूर्ण

/**
 * sel_ib_pkey_sid - Lookup the SID of a PKEY
 * @subnet_prefix: subnet_prefix
 * @pkey_num: pkey number
 * @sid: pkey SID
 *
 * Description:
 * This function determines the SID of a PKEY using the fastest method
 * possible.  First the pkey table is queried, but अगर an entry can't be found
 * then the policy is queried and the result is added to the table to speedup
 * future queries.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक sel_ib_pkey_sid(u64 subnet_prefix, u16 pkey_num, u32 *sid)
अणु
	काष्ठा sel_ib_pkey *pkey;

	rcu_पढ़ो_lock();
	pkey = sel_ib_pkey_find(subnet_prefix, pkey_num);
	अगर (pkey) अणु
		*sid = pkey->psec.sid;
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस sel_ib_pkey_sid_slow(subnet_prefix, pkey_num, sid);
पूर्ण

/**
 * sel_ib_pkey_flush - Flush the entire pkey table
 *
 * Description:
 * Remove all entries from the pkey table
 *
 */
व्योम sel_ib_pkey_flush(व्योम)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा sel_ib_pkey *pkey, *pkey_पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sel_ib_pkey_lock, flags);
	क्रम (idx = 0; idx < SEL_PKEY_HASH_SIZE; idx++) अणु
		list_क्रम_each_entry_safe(pkey, pkey_पंचांगp,
					 &sel_ib_pkey_hash[idx].list, list) अणु
			list_del_rcu(&pkey->list);
			kमुक्त_rcu(pkey, rcu);
		पूर्ण
		sel_ib_pkey_hash[idx].size = 0;
	पूर्ण
	spin_unlock_irqrestore(&sel_ib_pkey_lock, flags);
पूर्ण

अटल __init पूर्णांक sel_ib_pkey_init(व्योम)
अणु
	पूर्णांक iter;

	अगर (!selinux_enabled_boot)
		वापस 0;

	क्रम (iter = 0; iter < SEL_PKEY_HASH_SIZE; iter++) अणु
		INIT_LIST_HEAD(&sel_ib_pkey_hash[iter].list);
		sel_ib_pkey_hash[iter].size = 0;
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(sel_ib_pkey_init);

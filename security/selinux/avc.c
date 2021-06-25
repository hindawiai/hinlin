<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of the kernel access vector cache (AVC).
 *
 * Authors:  Stephen Smalley, <sds@tycho.nsa.gov>
 *	     James Morris <jmorris@redhat.com>
 *
 * Update:   KaiGai, Kohei <kaigai@ak.jp.nec.com>
 *	Replaced the avc_lock spinlock by RCU.
 *
 * Copyright (C) 2003 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/dcache.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/percpu.h>
#समावेश <linux/list.h>
#समावेश <net/sock.h>
#समावेश <linux/un.h>
#समावेश <net/af_unix.h>
#समावेश <linux/ip.h>
#समावेश <linux/audit.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश "avc.h"
#समावेश "avc_ss.h"
#समावेश "classmap.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/avc.h>

#घोषणा AVC_CACHE_SLOTS			512
#घोषणा AVC_DEF_CACHE_THRESHOLD		512
#घोषणा AVC_CACHE_RECLAIM		16

#अगर_घोषित CONFIG_SECURITY_SELINUX_AVC_STATS
#घोषणा avc_cache_stats_incr(field)	this_cpu_inc(avc_cache_stats.field)
#अन्यथा
#घोषणा avc_cache_stats_incr(field)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा avc_entry अणु
	u32			ssid;
	u32			tsid;
	u16			tclass;
	काष्ठा av_decision	avd;
	काष्ठा avc_xperms_node	*xp_node;
पूर्ण;

काष्ठा avc_node अणु
	काष्ठा avc_entry	ae;
	काष्ठा hlist_node	list; /* anchored in avc_cache->slots[i] */
	काष्ठा rcu_head		rhead;
पूर्ण;

काष्ठा avc_xperms_decision_node अणु
	काष्ठा extended_perms_decision xpd;
	काष्ठा list_head xpd_list; /* list of extended_perms_decision */
पूर्ण;

काष्ठा avc_xperms_node अणु
	काष्ठा extended_perms xp;
	काष्ठा list_head xpd_head; /* list head of extended_perms_decision */
पूर्ण;

काष्ठा avc_cache अणु
	काष्ठा hlist_head	slots[AVC_CACHE_SLOTS]; /* head क्रम avc_node->list */
	spinlock_t		slots_lock[AVC_CACHE_SLOTS]; /* lock क्रम ग_लिखोs */
	atomic_t		lru_hपूर्णांक;	/* LRU hपूर्णांक क्रम reclaim scan */
	atomic_t		active_nodes;
	u32			latest_notअगर;	/* latest revocation notअगरication */
पूर्ण;

काष्ठा avc_callback_node अणु
	पूर्णांक (*callback) (u32 event);
	u32 events;
	काष्ठा avc_callback_node *next;
पूर्ण;

#अगर_घोषित CONFIG_SECURITY_SELINUX_AVC_STATS
DEFINE_PER_CPU(काष्ठा avc_cache_stats, avc_cache_stats) = अणु 0 पूर्ण;
#पूर्ण_अगर

काष्ठा selinux_avc अणु
	अचिन्हित पूर्णांक avc_cache_threshold;
	काष्ठा avc_cache avc_cache;
पूर्ण;

अटल काष्ठा selinux_avc selinux_avc;

व्योम selinux_avc_init(काष्ठा selinux_avc **avc)
अणु
	पूर्णांक i;

	selinux_avc.avc_cache_threshold = AVC_DEF_CACHE_THRESHOLD;
	क्रम (i = 0; i < AVC_CACHE_SLOTS; i++) अणु
		INIT_HLIST_HEAD(&selinux_avc.avc_cache.slots[i]);
		spin_lock_init(&selinux_avc.avc_cache.slots_lock[i]);
	पूर्ण
	atomic_set(&selinux_avc.avc_cache.active_nodes, 0);
	atomic_set(&selinux_avc.avc_cache.lru_hपूर्णांक, 0);
	*avc = &selinux_avc;
पूर्ण

अचिन्हित पूर्णांक avc_get_cache_threshold(काष्ठा selinux_avc *avc)
अणु
	वापस avc->avc_cache_threshold;
पूर्ण

व्योम avc_set_cache_threshold(काष्ठा selinux_avc *avc,
			     अचिन्हित पूर्णांक cache_threshold)
अणु
	avc->avc_cache_threshold = cache_threshold;
पूर्ण

अटल काष्ठा avc_callback_node *avc_callbacks __ro_after_init;
अटल काष्ठा kmem_cache *avc_node_cachep __ro_after_init;
अटल काष्ठा kmem_cache *avc_xperms_data_cachep __ro_after_init;
अटल काष्ठा kmem_cache *avc_xperms_decision_cachep __ro_after_init;
अटल काष्ठा kmem_cache *avc_xperms_cachep __ro_after_init;

अटल अंतरभूत पूर्णांक avc_hash(u32 ssid, u32 tsid, u16 tclass)
अणु
	वापस (ssid ^ (tsid<<2) ^ (tclass<<4)) & (AVC_CACHE_SLOTS - 1);
पूर्ण

/**
 * avc_init - Initialize the AVC.
 *
 * Initialize the access vector cache.
 */
व्योम __init avc_init(व्योम)
अणु
	avc_node_cachep = kmem_cache_create("avc_node", माप(काष्ठा avc_node),
					0, SLAB_PANIC, शून्य);
	avc_xperms_cachep = kmem_cache_create("avc_xperms_node",
					माप(काष्ठा avc_xperms_node),
					0, SLAB_PANIC, शून्य);
	avc_xperms_decision_cachep = kmem_cache_create(
					"avc_xperms_decision_node",
					माप(काष्ठा avc_xperms_decision_node),
					0, SLAB_PANIC, शून्य);
	avc_xperms_data_cachep = kmem_cache_create("avc_xperms_data",
					माप(काष्ठा extended_perms_data),
					0, SLAB_PANIC, शून्य);
पूर्ण

पूर्णांक avc_get_hash_stats(काष्ठा selinux_avc *avc, अक्षर *page)
अणु
	पूर्णांक i, chain_len, max_chain_len, slots_used;
	काष्ठा avc_node *node;
	काष्ठा hlist_head *head;

	rcu_पढ़ो_lock();

	slots_used = 0;
	max_chain_len = 0;
	क्रम (i = 0; i < AVC_CACHE_SLOTS; i++) अणु
		head = &avc->avc_cache.slots[i];
		अगर (!hlist_empty(head)) अणु
			slots_used++;
			chain_len = 0;
			hlist_क्रम_each_entry_rcu(node, head, list)
				chain_len++;
			अगर (chain_len > max_chain_len)
				max_chain_len = chain_len;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस scnम_लिखो(page, PAGE_SIZE, "entries: %d\nbuckets used: %d/%d\n"
			 "longest chain: %d\n",
			 atomic_पढ़ो(&avc->avc_cache.active_nodes),
			 slots_used, AVC_CACHE_SLOTS, max_chain_len);
पूर्ण

/*
 * using a linked list क्रम extended_perms_decision lookup because the list is
 * always small. i.e. less than 5, typically 1
 */
अटल काष्ठा extended_perms_decision *avc_xperms_decision_lookup(u8 driver,
					काष्ठा avc_xperms_node *xp_node)
अणु
	काष्ठा avc_xperms_decision_node *xpd_node;

	list_क्रम_each_entry(xpd_node, &xp_node->xpd_head, xpd_list) अणु
		अगर (xpd_node->xpd.driver == driver)
			वापस &xpd_node->xpd;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
avc_xperms_has_perm(काष्ठा extended_perms_decision *xpd,
					u8 perm, u8 which)
अणु
	अचिन्हित पूर्णांक rc = 0;

	अगर ((which == XPERMS_ALLOWED) &&
			(xpd->used & XPERMS_ALLOWED))
		rc = security_xperm_test(xpd->allowed->p, perm);
	अन्यथा अगर ((which == XPERMS_AUDITALLOW) &&
			(xpd->used & XPERMS_AUDITALLOW))
		rc = security_xperm_test(xpd->auditallow->p, perm);
	अन्यथा अगर ((which == XPERMS_DONTAUDIT) &&
			(xpd->used & XPERMS_DONTAUDIT))
		rc = security_xperm_test(xpd->करोntaudit->p, perm);
	वापस rc;
पूर्ण

अटल व्योम avc_xperms_allow_perm(काष्ठा avc_xperms_node *xp_node,
				u8 driver, u8 perm)
अणु
	काष्ठा extended_perms_decision *xpd;
	security_xperm_set(xp_node->xp.drivers.p, driver);
	xpd = avc_xperms_decision_lookup(driver, xp_node);
	अगर (xpd && xpd->allowed)
		security_xperm_set(xpd->allowed->p, perm);
पूर्ण

अटल व्योम avc_xperms_decision_मुक्त(काष्ठा avc_xperms_decision_node *xpd_node)
अणु
	काष्ठा extended_perms_decision *xpd;

	xpd = &xpd_node->xpd;
	अगर (xpd->allowed)
		kmem_cache_मुक्त(avc_xperms_data_cachep, xpd->allowed);
	अगर (xpd->auditallow)
		kmem_cache_मुक्त(avc_xperms_data_cachep, xpd->auditallow);
	अगर (xpd->करोntaudit)
		kmem_cache_मुक्त(avc_xperms_data_cachep, xpd->करोntaudit);
	kmem_cache_मुक्त(avc_xperms_decision_cachep, xpd_node);
पूर्ण

अटल व्योम avc_xperms_मुक्त(काष्ठा avc_xperms_node *xp_node)
अणु
	काष्ठा avc_xperms_decision_node *xpd_node, *पंचांगp;

	अगर (!xp_node)
		वापस;

	list_क्रम_each_entry_safe(xpd_node, पंचांगp, &xp_node->xpd_head, xpd_list) अणु
		list_del(&xpd_node->xpd_list);
		avc_xperms_decision_मुक्त(xpd_node);
	पूर्ण
	kmem_cache_मुक्त(avc_xperms_cachep, xp_node);
पूर्ण

अटल व्योम avc_copy_xperms_decision(काष्ठा extended_perms_decision *dest,
					काष्ठा extended_perms_decision *src)
अणु
	dest->driver = src->driver;
	dest->used = src->used;
	अगर (dest->used & XPERMS_ALLOWED)
		स_नकल(dest->allowed->p, src->allowed->p,
				माप(src->allowed->p));
	अगर (dest->used & XPERMS_AUDITALLOW)
		स_नकल(dest->auditallow->p, src->auditallow->p,
				माप(src->auditallow->p));
	अगर (dest->used & XPERMS_DONTAUDIT)
		स_नकल(dest->करोntaudit->p, src->करोntaudit->p,
				माप(src->करोntaudit->p));
पूर्ण

/*
 * similar to avc_copy_xperms_decision, but only copy decision
 * inक्रमmation relevant to this perm
 */
अटल अंतरभूत व्योम avc_quick_copy_xperms_decision(u8 perm,
			काष्ठा extended_perms_decision *dest,
			काष्ठा extended_perms_decision *src)
अणु
	/*
	 * compute index of the u32 of the 256 bits (8 u32s) that contain this
	 * command permission
	 */
	u8 i = perm >> 5;

	dest->used = src->used;
	अगर (dest->used & XPERMS_ALLOWED)
		dest->allowed->p[i] = src->allowed->p[i];
	अगर (dest->used & XPERMS_AUDITALLOW)
		dest->auditallow->p[i] = src->auditallow->p[i];
	अगर (dest->used & XPERMS_DONTAUDIT)
		dest->करोntaudit->p[i] = src->करोntaudit->p[i];
पूर्ण

अटल काष्ठा avc_xperms_decision_node
		*avc_xperms_decision_alloc(u8 which)
अणु
	काष्ठा avc_xperms_decision_node *xpd_node;
	काष्ठा extended_perms_decision *xpd;

	xpd_node = kmem_cache_zalloc(avc_xperms_decision_cachep, GFP_NOWAIT);
	अगर (!xpd_node)
		वापस शून्य;

	xpd = &xpd_node->xpd;
	अगर (which & XPERMS_ALLOWED) अणु
		xpd->allowed = kmem_cache_zalloc(avc_xperms_data_cachep,
						GFP_NOWAIT);
		अगर (!xpd->allowed)
			जाओ error;
	पूर्ण
	अगर (which & XPERMS_AUDITALLOW) अणु
		xpd->auditallow = kmem_cache_zalloc(avc_xperms_data_cachep,
						GFP_NOWAIT);
		अगर (!xpd->auditallow)
			जाओ error;
	पूर्ण
	अगर (which & XPERMS_DONTAUDIT) अणु
		xpd->करोntaudit = kmem_cache_zalloc(avc_xperms_data_cachep,
						GFP_NOWAIT);
		अगर (!xpd->करोntaudit)
			जाओ error;
	पूर्ण
	वापस xpd_node;
error:
	avc_xperms_decision_मुक्त(xpd_node);
	वापस शून्य;
पूर्ण

अटल पूर्णांक avc_add_xperms_decision(काष्ठा avc_node *node,
			काष्ठा extended_perms_decision *src)
अणु
	काष्ठा avc_xperms_decision_node *dest_xpd;

	node->ae.xp_node->xp.len++;
	dest_xpd = avc_xperms_decision_alloc(src->used);
	अगर (!dest_xpd)
		वापस -ENOMEM;
	avc_copy_xperms_decision(&dest_xpd->xpd, src);
	list_add(&dest_xpd->xpd_list, &node->ae.xp_node->xpd_head);
	वापस 0;
पूर्ण

अटल काष्ठा avc_xperms_node *avc_xperms_alloc(व्योम)
अणु
	काष्ठा avc_xperms_node *xp_node;

	xp_node = kmem_cache_zalloc(avc_xperms_cachep, GFP_NOWAIT);
	अगर (!xp_node)
		वापस xp_node;
	INIT_LIST_HEAD(&xp_node->xpd_head);
	वापस xp_node;
पूर्ण

अटल पूर्णांक avc_xperms_populate(काष्ठा avc_node *node,
				काष्ठा avc_xperms_node *src)
अणु
	काष्ठा avc_xperms_node *dest;
	काष्ठा avc_xperms_decision_node *dest_xpd;
	काष्ठा avc_xperms_decision_node *src_xpd;

	अगर (src->xp.len == 0)
		वापस 0;
	dest = avc_xperms_alloc();
	अगर (!dest)
		वापस -ENOMEM;

	स_नकल(dest->xp.drivers.p, src->xp.drivers.p, माप(dest->xp.drivers.p));
	dest->xp.len = src->xp.len;

	/* क्रम each source xpd allocate a destination xpd and copy */
	list_क्रम_each_entry(src_xpd, &src->xpd_head, xpd_list) अणु
		dest_xpd = avc_xperms_decision_alloc(src_xpd->xpd.used);
		अगर (!dest_xpd)
			जाओ error;
		avc_copy_xperms_decision(&dest_xpd->xpd, &src_xpd->xpd);
		list_add(&dest_xpd->xpd_list, &dest->xpd_head);
	पूर्ण
	node->ae.xp_node = dest;
	वापस 0;
error:
	avc_xperms_मुक्त(dest);
	वापस -ENOMEM;

पूर्ण

अटल अंतरभूत u32 avc_xperms_audit_required(u32 requested,
					काष्ठा av_decision *avd,
					काष्ठा extended_perms_decision *xpd,
					u8 perm,
					पूर्णांक result,
					u32 *deniedp)
अणु
	u32 denied, audited;

	denied = requested & ~avd->allowed;
	अगर (unlikely(denied)) अणु
		audited = denied & avd->auditdeny;
		अगर (audited && xpd) अणु
			अगर (avc_xperms_has_perm(xpd, perm, XPERMS_DONTAUDIT))
				audited &= ~requested;
		पूर्ण
	पूर्ण अन्यथा अगर (result) अणु
		audited = denied = requested;
	पूर्ण अन्यथा अणु
		audited = requested & avd->auditallow;
		अगर (audited && xpd) अणु
			अगर (!avc_xperms_has_perm(xpd, perm, XPERMS_AUDITALLOW))
				audited &= ~requested;
		पूर्ण
	पूर्ण

	*deniedp = denied;
	वापस audited;
पूर्ण

अटल अंतरभूत पूर्णांक avc_xperms_audit(काष्ठा selinux_state *state,
				   u32 ssid, u32 tsid, u16 tclass,
				   u32 requested, काष्ठा av_decision *avd,
				   काष्ठा extended_perms_decision *xpd,
				   u8 perm, पूर्णांक result,
				   काष्ठा common_audit_data *ad)
अणु
	u32 audited, denied;

	audited = avc_xperms_audit_required(
			requested, avd, xpd, perm, result, &denied);
	अगर (likely(!audited))
		वापस 0;
	वापस slow_avc_audit(state, ssid, tsid, tclass, requested,
			audited, denied, result, ad);
पूर्ण

अटल व्योम avc_node_मुक्त(काष्ठा rcu_head *rhead)
अणु
	काष्ठा avc_node *node = container_of(rhead, काष्ठा avc_node, rhead);
	avc_xperms_मुक्त(node->ae.xp_node);
	kmem_cache_मुक्त(avc_node_cachep, node);
	avc_cache_stats_incr(मुक्तs);
पूर्ण

अटल व्योम avc_node_delete(काष्ठा selinux_avc *avc, काष्ठा avc_node *node)
अणु
	hlist_del_rcu(&node->list);
	call_rcu(&node->rhead, avc_node_मुक्त);
	atomic_dec(&avc->avc_cache.active_nodes);
पूर्ण

अटल व्योम avc_node_समाप्त(काष्ठा selinux_avc *avc, काष्ठा avc_node *node)
अणु
	avc_xperms_मुक्त(node->ae.xp_node);
	kmem_cache_मुक्त(avc_node_cachep, node);
	avc_cache_stats_incr(मुक्तs);
	atomic_dec(&avc->avc_cache.active_nodes);
पूर्ण

अटल व्योम avc_node_replace(काष्ठा selinux_avc *avc,
			     काष्ठा avc_node *new, काष्ठा avc_node *old)
अणु
	hlist_replace_rcu(&old->list, &new->list);
	call_rcu(&old->rhead, avc_node_मुक्त);
	atomic_dec(&avc->avc_cache.active_nodes);
पूर्ण

अटल अंतरभूत पूर्णांक avc_reclaim_node(काष्ठा selinux_avc *avc)
अणु
	काष्ठा avc_node *node;
	पूर्णांक hvalue, try, ecx;
	अचिन्हित दीर्घ flags;
	काष्ठा hlist_head *head;
	spinlock_t *lock;

	क्रम (try = 0, ecx = 0; try < AVC_CACHE_SLOTS; try++) अणु
		hvalue = atomic_inc_वापस(&avc->avc_cache.lru_hपूर्णांक) &
			(AVC_CACHE_SLOTS - 1);
		head = &avc->avc_cache.slots[hvalue];
		lock = &avc->avc_cache.slots_lock[hvalue];

		अगर (!spin_trylock_irqsave(lock, flags))
			जारी;

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry(node, head, list) अणु
			avc_node_delete(avc, node);
			avc_cache_stats_incr(reclaims);
			ecx++;
			अगर (ecx >= AVC_CACHE_RECLAIM) अणु
				rcu_पढ़ो_unlock();
				spin_unlock_irqrestore(lock, flags);
				जाओ out;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		spin_unlock_irqrestore(lock, flags);
	पूर्ण
out:
	वापस ecx;
पूर्ण

अटल काष्ठा avc_node *avc_alloc_node(काष्ठा selinux_avc *avc)
अणु
	काष्ठा avc_node *node;

	node = kmem_cache_zalloc(avc_node_cachep, GFP_NOWAIT);
	अगर (!node)
		जाओ out;

	INIT_HLIST_NODE(&node->list);
	avc_cache_stats_incr(allocations);

	अगर (atomic_inc_वापस(&avc->avc_cache.active_nodes) >
	    avc->avc_cache_threshold)
		avc_reclaim_node(avc);

out:
	वापस node;
पूर्ण

अटल व्योम avc_node_populate(काष्ठा avc_node *node, u32 ssid, u32 tsid, u16 tclass, काष्ठा av_decision *avd)
अणु
	node->ae.ssid = ssid;
	node->ae.tsid = tsid;
	node->ae.tclass = tclass;
	स_नकल(&node->ae.avd, avd, माप(node->ae.avd));
पूर्ण

अटल अंतरभूत काष्ठा avc_node *avc_search_node(काष्ठा selinux_avc *avc,
					       u32 ssid, u32 tsid, u16 tclass)
अणु
	काष्ठा avc_node *node, *ret = शून्य;
	पूर्णांक hvalue;
	काष्ठा hlist_head *head;

	hvalue = avc_hash(ssid, tsid, tclass);
	head = &avc->avc_cache.slots[hvalue];
	hlist_क्रम_each_entry_rcu(node, head, list) अणु
		अगर (ssid == node->ae.ssid &&
		    tclass == node->ae.tclass &&
		    tsid == node->ae.tsid) अणु
			ret = node;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * avc_lookup - Look up an AVC entry.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 *
 * Look up an AVC entry that is valid क्रम the
 * (@ssid, @tsid), पूर्णांकerpreting the permissions
 * based on @tclass.  If a valid AVC entry exists,
 * then this function वापसs the avc_node.
 * Otherwise, this function वापसs शून्य.
 */
अटल काष्ठा avc_node *avc_lookup(काष्ठा selinux_avc *avc,
				   u32 ssid, u32 tsid, u16 tclass)
अणु
	काष्ठा avc_node *node;

	avc_cache_stats_incr(lookups);
	node = avc_search_node(avc, ssid, tsid, tclass);

	अगर (node)
		वापस node;

	avc_cache_stats_incr(misses);
	वापस शून्य;
पूर्ण

अटल पूर्णांक avc_latest_notअगर_update(काष्ठा selinux_avc *avc,
				   पूर्णांक seqno, पूर्णांक is_insert)
अणु
	पूर्णांक ret = 0;
	अटल DEFINE_SPINLOCK(notअगर_lock);
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&notअगर_lock, flag);
	अगर (is_insert) अणु
		अगर (seqno < avc->avc_cache.latest_notअगर) अणु
			pr_warn("SELinux: avc:  seqno %d < latest_notif %d\n",
			       seqno, avc->avc_cache.latest_notअगर);
			ret = -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (seqno > avc->avc_cache.latest_notअगर)
			avc->avc_cache.latest_notअगर = seqno;
	पूर्ण
	spin_unlock_irqrestore(&notअगर_lock, flag);

	वापस ret;
पूर्ण

/**
 * avc_insert - Insert an AVC entry.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 * @avd: resulting av decision
 * @xp_node: resulting extended permissions
 *
 * Insert an AVC entry क्रम the SID pair
 * (@ssid, @tsid) and class @tclass.
 * The access vectors and the sequence number are
 * normally provided by the security server in
 * response to a security_compute_av() call.  If the
 * sequence number @avd->seqno is not less than the latest
 * revocation notअगरication, then the function copies
 * the access vectors पूर्णांकo a cache entry, वापसs
 * avc_node inserted. Otherwise, this function वापसs शून्य.
 */
अटल काष्ठा avc_node *avc_insert(काष्ठा selinux_avc *avc,
				   u32 ssid, u32 tsid, u16 tclass,
				   काष्ठा av_decision *avd,
				   काष्ठा avc_xperms_node *xp_node)
अणु
	काष्ठा avc_node *pos, *node = शून्य;
	पूर्णांक hvalue;
	अचिन्हित दीर्घ flag;
	spinlock_t *lock;
	काष्ठा hlist_head *head;

	अगर (avc_latest_notअगर_update(avc, avd->seqno, 1))
		वापस शून्य;

	node = avc_alloc_node(avc);
	अगर (!node)
		वापस शून्य;

	avc_node_populate(node, ssid, tsid, tclass, avd);
	अगर (avc_xperms_populate(node, xp_node)) अणु
		avc_node_समाप्त(avc, node);
		वापस शून्य;
	पूर्ण

	hvalue = avc_hash(ssid, tsid, tclass);
	head = &avc->avc_cache.slots[hvalue];
	lock = &avc->avc_cache.slots_lock[hvalue];
	spin_lock_irqsave(lock, flag);
	hlist_क्रम_each_entry(pos, head, list) अणु
		अगर (pos->ae.ssid == ssid &&
			pos->ae.tsid == tsid &&
			pos->ae.tclass == tclass) अणु
			avc_node_replace(avc, node, pos);
			जाओ found;
		पूर्ण
	पूर्ण
	hlist_add_head_rcu(&node->list, head);
found:
	spin_unlock_irqrestore(lock, flag);
	वापस node;
पूर्ण

/**
 * avc_audit_pre_callback - SELinux specअगरic inक्रमmation
 * will be called by generic audit code
 * @ab: the audit buffer
 * @a: audit_data
 */
अटल व्योम avc_audit_pre_callback(काष्ठा audit_buffer *ab, व्योम *a)
अणु
	काष्ठा common_audit_data *ad = a;
	काष्ठा selinux_audit_data *sad = ad->selinux_audit_data;
	u32 av = sad->audited;
	स्थिर अक्षर **perms;
	पूर्णांक i, perm;

	audit_log_क्रमmat(ab, "avc:  %s ", sad->denied ? "denied" : "granted");

	अगर (av == 0) अणु
		audit_log_क्रमmat(ab, " null");
		वापस;
	पूर्ण

	perms = secclass_map[sad->tclass-1].perms;

	audit_log_क्रमmat(ab, " {");
	i = 0;
	perm = 1;
	जबतक (i < (माप(av) * 8)) अणु
		अगर ((perm & av) && perms[i]) अणु
			audit_log_क्रमmat(ab, " %s", perms[i]);
			av &= ~perm;
		पूर्ण
		i++;
		perm <<= 1;
	पूर्ण

	अगर (av)
		audit_log_क्रमmat(ab, " 0x%x", av);

	audit_log_क्रमmat(ab, " } for ");
पूर्ण

/**
 * avc_audit_post_callback - SELinux specअगरic inक्रमmation
 * will be called by generic audit code
 * @ab: the audit buffer
 * @a: audit_data
 */
अटल व्योम avc_audit_post_callback(काष्ठा audit_buffer *ab, व्योम *a)
अणु
	काष्ठा common_audit_data *ad = a;
	काष्ठा selinux_audit_data *sad = ad->selinux_audit_data;
	अक्षर *scontext = शून्य;
	अक्षर *tcontext = शून्य;
	स्थिर अक्षर *tclass = शून्य;
	u32 scontext_len;
	u32 tcontext_len;
	पूर्णांक rc;

	rc = security_sid_to_context(sad->state, sad->ssid, &scontext,
				     &scontext_len);
	अगर (rc)
		audit_log_क्रमmat(ab, " ssid=%d", sad->ssid);
	अन्यथा
		audit_log_क्रमmat(ab, " scontext=%s", scontext);

	rc = security_sid_to_context(sad->state, sad->tsid, &tcontext,
				     &tcontext_len);
	अगर (rc)
		audit_log_क्रमmat(ab, " tsid=%d", sad->tsid);
	अन्यथा
		audit_log_क्रमmat(ab, " tcontext=%s", tcontext);

	tclass = secclass_map[sad->tclass-1].name;
	audit_log_क्रमmat(ab, " tclass=%s", tclass);

	अगर (sad->denied)
		audit_log_क्रमmat(ab, " permissive=%u", sad->result ? 0 : 1);

	trace_selinux_audited(sad, scontext, tcontext, tclass);
	kमुक्त(tcontext);
	kमुक्त(scontext);

	/* in हाल of invalid context report also the actual context string */
	rc = security_sid_to_context_inval(sad->state, sad->ssid, &scontext,
					   &scontext_len);
	अगर (!rc && scontext) अणु
		अगर (scontext_len && scontext[scontext_len - 1] == '\0')
			scontext_len--;
		audit_log_क्रमmat(ab, " srawcon=");
		audit_log_n_untrustedstring(ab, scontext, scontext_len);
		kमुक्त(scontext);
	पूर्ण

	rc = security_sid_to_context_inval(sad->state, sad->tsid, &scontext,
					   &scontext_len);
	अगर (!rc && scontext) अणु
		अगर (scontext_len && scontext[scontext_len - 1] == '\0')
			scontext_len--;
		audit_log_क्रमmat(ab, " trawcon=");
		audit_log_n_untrustedstring(ab, scontext, scontext_len);
		kमुक्त(scontext);
	पूर्ण
पूर्ण

/* This is the slow part of avc audit with big stack footprपूर्णांक */
noअंतरभूत पूर्णांक slow_avc_audit(काष्ठा selinux_state *state,
			    u32 ssid, u32 tsid, u16 tclass,
			    u32 requested, u32 audited, u32 denied, पूर्णांक result,
			    काष्ठा common_audit_data *a)
अणु
	काष्ठा common_audit_data stack_data;
	काष्ठा selinux_audit_data sad;

	अगर (WARN_ON(!tclass || tclass >= ARRAY_SIZE(secclass_map)))
		वापस -EINVAL;

	अगर (!a) अणु
		a = &stack_data;
		a->type = LSM_AUDIT_DATA_NONE;
	पूर्ण

	sad.tclass = tclass;
	sad.requested = requested;
	sad.ssid = ssid;
	sad.tsid = tsid;
	sad.audited = audited;
	sad.denied = denied;
	sad.result = result;
	sad.state = state;

	a->selinux_audit_data = &sad;

	common_lsm_audit(a, avc_audit_pre_callback, avc_audit_post_callback);
	वापस 0;
पूर्ण

/**
 * avc_add_callback - Register a callback क्रम security events.
 * @callback: callback function
 * @events: security events
 *
 * Register a callback function क्रम events in the set @events.
 * Returns %0 on success or -%ENOMEM अगर insufficient memory
 * exists to add the callback.
 */
पूर्णांक __init avc_add_callback(पूर्णांक (*callback)(u32 event), u32 events)
अणु
	काष्ठा avc_callback_node *c;
	पूर्णांक rc = 0;

	c = kदो_स्मृति(माप(*c), GFP_KERNEL);
	अगर (!c) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	c->callback = callback;
	c->events = events;
	c->next = avc_callbacks;
	avc_callbacks = c;
out:
	वापस rc;
पूर्ण

/**
 * avc_update_node Update an AVC entry
 * @event : Updating event
 * @perms : Permission mask bits
 * @ssid,@tsid,@tclass : identअगरier of an AVC entry
 * @seqno : sequence number when decision was made
 * @xpd: extended_perms_decision to be added to the node
 * @flags: the AVC_* flags, e.g. AVC_NONBLOCKING, AVC_EXTENDED_PERMS, or 0.
 *
 * अगर a valid AVC entry करोesn't exist,this function वापसs -ENOENT.
 * अगर kदो_स्मृति() called पूर्णांकernal वापसs शून्य, this function वापसs -ENOMEM.
 * otherwise, this function updates the AVC entry. The original AVC-entry object
 * will release later by RCU.
 */
अटल पूर्णांक avc_update_node(काष्ठा selinux_avc *avc,
			   u32 event, u32 perms, u8 driver, u8 xperm, u32 ssid,
			   u32 tsid, u16 tclass, u32 seqno,
			   काष्ठा extended_perms_decision *xpd,
			   u32 flags)
अणु
	पूर्णांक hvalue, rc = 0;
	अचिन्हित दीर्घ flag;
	काष्ठा avc_node *pos, *node, *orig = शून्य;
	काष्ठा hlist_head *head;
	spinlock_t *lock;

	/*
	 * If we are in a non-blocking code path, e.g. VFS RCU walk,
	 * then we must not add permissions to a cache entry
	 * because we will not audit the denial.  Otherwise,
	 * during the subsequent blocking retry (e.g. VFS ref walk), we
	 * will find the permissions alपढ़ोy granted in the cache entry
	 * and won't audit anything at all, leading to silent denials in
	 * permissive mode that only appear when in enक्रमcing mode.
	 *
	 * See the corresponding handling of MAY_NOT_BLOCK in avc_audit()
	 * and selinux_inode_permission().
	 */
	अगर (flags & AVC_NONBLOCKING)
		वापस 0;

	node = avc_alloc_node(avc);
	अगर (!node) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Lock the target slot */
	hvalue = avc_hash(ssid, tsid, tclass);

	head = &avc->avc_cache.slots[hvalue];
	lock = &avc->avc_cache.slots_lock[hvalue];

	spin_lock_irqsave(lock, flag);

	hlist_क्रम_each_entry(pos, head, list) अणु
		अगर (ssid == pos->ae.ssid &&
		    tsid == pos->ae.tsid &&
		    tclass == pos->ae.tclass &&
		    seqno == pos->ae.avd.seqno)अणु
			orig = pos;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!orig) अणु
		rc = -ENOENT;
		avc_node_समाप्त(avc, node);
		जाओ out_unlock;
	पूर्ण

	/*
	 * Copy and replace original node.
	 */

	avc_node_populate(node, ssid, tsid, tclass, &orig->ae.avd);

	अगर (orig->ae.xp_node) अणु
		rc = avc_xperms_populate(node, orig->ae.xp_node);
		अगर (rc) अणु
			avc_node_समाप्त(avc, node);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	चयन (event) अणु
	हाल AVC_CALLBACK_GRANT:
		node->ae.avd.allowed |= perms;
		अगर (node->ae.xp_node && (flags & AVC_EXTENDED_PERMS))
			avc_xperms_allow_perm(node->ae.xp_node, driver, xperm);
		अवरोध;
	हाल AVC_CALLBACK_TRY_REVOKE:
	हाल AVC_CALLBACK_REVOKE:
		node->ae.avd.allowed &= ~perms;
		अवरोध;
	हाल AVC_CALLBACK_AUDITALLOW_ENABLE:
		node->ae.avd.auditallow |= perms;
		अवरोध;
	हाल AVC_CALLBACK_AUDITALLOW_DISABLE:
		node->ae.avd.auditallow &= ~perms;
		अवरोध;
	हाल AVC_CALLBACK_AUDITDENY_ENABLE:
		node->ae.avd.auditdeny |= perms;
		अवरोध;
	हाल AVC_CALLBACK_AUDITDENY_DISABLE:
		node->ae.avd.auditdeny &= ~perms;
		अवरोध;
	हाल AVC_CALLBACK_ADD_XPERMS:
		avc_add_xperms_decision(node, xpd);
		अवरोध;
	पूर्ण
	avc_node_replace(avc, node, orig);
out_unlock:
	spin_unlock_irqrestore(lock, flag);
out:
	वापस rc;
पूर्ण

/**
 * avc_flush - Flush the cache
 */
अटल व्योम avc_flush(काष्ठा selinux_avc *avc)
अणु
	काष्ठा hlist_head *head;
	काष्ठा avc_node *node;
	spinlock_t *lock;
	अचिन्हित दीर्घ flag;
	पूर्णांक i;

	क्रम (i = 0; i < AVC_CACHE_SLOTS; i++) अणु
		head = &avc->avc_cache.slots[i];
		lock = &avc->avc_cache.slots_lock[i];

		spin_lock_irqsave(lock, flag);
		/*
		 * With preemptable RCU, the outer spinlock करोes not
		 * prevent RCU grace periods from ending.
		 */
		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry(node, head, list)
			avc_node_delete(avc, node);
		rcu_पढ़ो_unlock();
		spin_unlock_irqrestore(lock, flag);
	पूर्ण
पूर्ण

/**
 * avc_ss_reset - Flush the cache and revalidate migrated permissions.
 * @seqno: policy sequence number
 */
पूर्णांक avc_ss_reset(काष्ठा selinux_avc *avc, u32 seqno)
अणु
	काष्ठा avc_callback_node *c;
	पूर्णांक rc = 0, पंचांगprc;

	avc_flush(avc);

	क्रम (c = avc_callbacks; c; c = c->next) अणु
		अगर (c->events & AVC_CALLBACK_RESET) अणु
			पंचांगprc = c->callback(AVC_CALLBACK_RESET);
			/* save the first error encountered क्रम the वापस
			   value and जारी processing the callbacks */
			अगर (!rc)
				rc = पंचांगprc;
		पूर्ण
	पूर्ण

	avc_latest_notअगर_update(avc, seqno, 0);
	वापस rc;
पूर्ण

/*
 * Slow-path helper function क्रम avc_has_perm_noaudit,
 * when the avc_node lookup fails. We get called with
 * the RCU पढ़ो lock held, and need to वापस with it
 * still held, but drop अगर क्रम the security compute.
 *
 * Don't inline this, since it's the slow-path and just
 * results in a bigger stack frame.
 */
अटल noअंतरभूत
काष्ठा avc_node *avc_compute_av(काष्ठा selinux_state *state,
				u32 ssid, u32 tsid,
				u16 tclass, काष्ठा av_decision *avd,
				काष्ठा avc_xperms_node *xp_node)
अणु
	rcu_पढ़ो_unlock();
	INIT_LIST_HEAD(&xp_node->xpd_head);
	security_compute_av(state, ssid, tsid, tclass, avd, &xp_node->xp);
	rcu_पढ़ो_lock();
	वापस avc_insert(state->avc, ssid, tsid, tclass, avd, xp_node);
पूर्ण

अटल noअंतरभूत पूर्णांक avc_denied(काष्ठा selinux_state *state,
			       u32 ssid, u32 tsid,
			       u16 tclass, u32 requested,
			       u8 driver, u8 xperm, अचिन्हित पूर्णांक flags,
			       काष्ठा av_decision *avd)
अणु
	अगर (flags & AVC_STRICT)
		वापस -EACCES;

	अगर (enक्रमcing_enabled(state) &&
	    !(avd->flags & AVD_FLAGS_PERMISSIVE))
		वापस -EACCES;

	avc_update_node(state->avc, AVC_CALLBACK_GRANT, requested, driver,
			xperm, ssid, tsid, tclass, avd->seqno, शून्य, flags);
	वापस 0;
पूर्ण

/*
 * The avc extended permissions logic adds an additional 256 bits of
 * permissions to an avc node when extended permissions क्रम that node are
 * specअगरied in the avtab. If the additional 256 permissions is not adequate,
 * as-is the हाल with ioctls, then multiple may be chained together and the
 * driver field is used to specअगरy which set contains the permission.
 */
पूर्णांक avc_has_extended_perms(काष्ठा selinux_state *state,
			   u32 ssid, u32 tsid, u16 tclass, u32 requested,
			   u8 driver, u8 xperm, काष्ठा common_audit_data *ad)
अणु
	काष्ठा avc_node *node;
	काष्ठा av_decision avd;
	u32 denied;
	काष्ठा extended_perms_decision local_xpd;
	काष्ठा extended_perms_decision *xpd = शून्य;
	काष्ठा extended_perms_data allowed;
	काष्ठा extended_perms_data auditallow;
	काष्ठा extended_perms_data करोntaudit;
	काष्ठा avc_xperms_node local_xp_node;
	काष्ठा avc_xperms_node *xp_node;
	पूर्णांक rc = 0, rc2;

	xp_node = &local_xp_node;
	अगर (WARN_ON(!requested))
		वापस -EACCES;

	rcu_पढ़ो_lock();

	node = avc_lookup(state->avc, ssid, tsid, tclass);
	अगर (unlikely(!node)) अणु
		node = avc_compute_av(state, ssid, tsid, tclass, &avd, xp_node);
	पूर्ण अन्यथा अणु
		स_नकल(&avd, &node->ae.avd, माप(avd));
		xp_node = node->ae.xp_node;
	पूर्ण
	/* अगर extended permissions are not defined, only consider av_decision */
	अगर (!xp_node || !xp_node->xp.len)
		जाओ decision;

	local_xpd.allowed = &allowed;
	local_xpd.auditallow = &auditallow;
	local_xpd.करोntaudit = &करोntaudit;

	xpd = avc_xperms_decision_lookup(driver, xp_node);
	अगर (unlikely(!xpd)) अणु
		/*
		 * Compute the extended_perms_decision only अगर the driver
		 * is flagged
		 */
		अगर (!security_xperm_test(xp_node->xp.drivers.p, driver)) अणु
			avd.allowed &= ~requested;
			जाओ decision;
		पूर्ण
		rcu_पढ़ो_unlock();
		security_compute_xperms_decision(state, ssid, tsid, tclass,
						 driver, &local_xpd);
		rcu_पढ़ो_lock();
		avc_update_node(state->avc, AVC_CALLBACK_ADD_XPERMS, requested,
				driver, xperm, ssid, tsid, tclass, avd.seqno,
				&local_xpd, 0);
	पूर्ण अन्यथा अणु
		avc_quick_copy_xperms_decision(xperm, &local_xpd, xpd);
	पूर्ण
	xpd = &local_xpd;

	अगर (!avc_xperms_has_perm(xpd, xperm, XPERMS_ALLOWED))
		avd.allowed &= ~requested;

decision:
	denied = requested & ~(avd.allowed);
	अगर (unlikely(denied))
		rc = avc_denied(state, ssid, tsid, tclass, requested,
				driver, xperm, AVC_EXTENDED_PERMS, &avd);

	rcu_पढ़ो_unlock();

	rc2 = avc_xperms_audit(state, ssid, tsid, tclass, requested,
			&avd, xpd, xperm, rc, ad);
	अगर (rc2)
		वापस rc2;
	वापस rc;
पूर्ण

/**
 * avc_has_perm_noaudit - Check permissions but perक्रमm no auditing.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 * @requested: requested permissions, पूर्णांकerpreted based on @tclass
 * @flags:  AVC_STRICT, AVC_NONBLOCKING, or 0
 * @avd: access vector decisions
 *
 * Check the AVC to determine whether the @requested permissions are granted
 * क्रम the SID pair (@ssid, @tsid), पूर्णांकerpreting the permissions
 * based on @tclass, and call the security server on a cache miss to obtain
 * a new decision and add it to the cache.  Return a copy of the decisions
 * in @avd.  Return %0 अगर all @requested permissions are granted,
 * -%EACCES अगर any permissions are denied, or another -त्रुटि_सं upon
 * other errors.  This function is typically called by avc_has_perm(),
 * but may also be called directly to separate permission checking from
 * auditing, e.g. in हालs where a lock must be held क्रम the check but
 * should be released क्रम the auditing.
 */
अंतरभूत पूर्णांक avc_has_perm_noaudit(काष्ठा selinux_state *state,
				u32 ssid, u32 tsid,
				u16 tclass, u32 requested,
				अचिन्हित पूर्णांक flags,
				काष्ठा av_decision *avd)
अणु
	काष्ठा avc_node *node;
	काष्ठा avc_xperms_node xp_node;
	पूर्णांक rc = 0;
	u32 denied;

	अगर (WARN_ON(!requested))
		वापस -EACCES;

	rcu_पढ़ो_lock();

	node = avc_lookup(state->avc, ssid, tsid, tclass);
	अगर (unlikely(!node))
		node = avc_compute_av(state, ssid, tsid, tclass, avd, &xp_node);
	अन्यथा
		स_नकल(avd, &node->ae.avd, माप(*avd));

	denied = requested & ~(avd->allowed);
	अगर (unlikely(denied))
		rc = avc_denied(state, ssid, tsid, tclass, requested, 0, 0,
				flags, avd);

	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

/**
 * avc_has_perm - Check permissions and perक्रमm any appropriate auditing.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 * @requested: requested permissions, पूर्णांकerpreted based on @tclass
 * @auditdata: auxiliary audit data
 *
 * Check the AVC to determine whether the @requested permissions are granted
 * क्रम the SID pair (@ssid, @tsid), पूर्णांकerpreting the permissions
 * based on @tclass, and call the security server on a cache miss to obtain
 * a new decision and add it to the cache.  Audit the granting or denial of
 * permissions in accordance with the policy.  Return %0 अगर all @requested
 * permissions are granted, -%EACCES अगर any permissions are denied, or
 * another -त्रुटि_सं upon other errors.
 */
पूर्णांक avc_has_perm(काष्ठा selinux_state *state, u32 ssid, u32 tsid, u16 tclass,
		 u32 requested, काष्ठा common_audit_data *auditdata)
अणु
	काष्ठा av_decision avd;
	पूर्णांक rc, rc2;

	rc = avc_has_perm_noaudit(state, ssid, tsid, tclass, requested, 0,
				  &avd);

	rc2 = avc_audit(state, ssid, tsid, tclass, requested, &avd, rc,
			auditdata, 0);
	अगर (rc2)
		वापस rc2;
	वापस rc;
पूर्ण

पूर्णांक avc_has_perm_flags(काष्ठा selinux_state *state,
		       u32 ssid, u32 tsid, u16 tclass, u32 requested,
		       काष्ठा common_audit_data *auditdata,
		       पूर्णांक flags)
अणु
	काष्ठा av_decision avd;
	पूर्णांक rc, rc2;

	rc = avc_has_perm_noaudit(state, ssid, tsid, tclass, requested,
				  (flags & MAY_NOT_BLOCK) ? AVC_NONBLOCKING : 0,
				  &avd);

	rc2 = avc_audit(state, ssid, tsid, tclass, requested, &avd, rc,
			auditdata, flags);
	अगर (rc2)
		वापस rc2;
	वापस rc;
पूर्ण

u32 avc_policy_seqno(काष्ठा selinux_state *state)
अणु
	वापस state->avc->avc_cache.latest_notअगर;
पूर्ण

व्योम avc_disable(व्योम)
अणु
	/*
	 * If you are looking at this because you have realized that we are
	 * not destroying the avc_node_cachep it might be easy to fix, but
	 * I करोn't know the memory barrier semantics well enough to know.  It's
	 * possible that some other task dereferenced security_ops when
	 * it still poपूर्णांकed to selinux operations.  If that is the हाल it's
	 * possible that it is about to use the avc and is about to need the
	 * avc_node_cachep.  I know I could wrap the security.c security_ops call
	 * in an rcu_lock, but seriously, it's not worth it.  Instead I just flush
	 * the cache and get that memory back.
	 */
	अगर (avc_node_cachep) अणु
		avc_flush(selinux_state.avc);
		/* kmem_cache_destroy(avc_node_cachep); */
	पूर्ण
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Multipath support क्रम RPC
 *
 * Copyright (c) 2015, 2016, Primary Data, Inc. All rights reserved.
 *
 * Trond Myklebust <trond.myklebust@primarydata.com>
 *
 */
#समावेश <linux/types.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sunrpc/xprt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/xprपंचांगultipath.h>

प्रकार काष्ठा rpc_xprt *(*xprt_चयन_find_xprt_t)(काष्ठा rpc_xprt_चयन *xps,
		स्थिर काष्ठा rpc_xprt *cur);

अटल स्थिर काष्ठा rpc_xprt_iter_ops rpc_xprt_iter_singular;
अटल स्थिर काष्ठा rpc_xprt_iter_ops rpc_xprt_iter_roundrobin;
अटल स्थिर काष्ठा rpc_xprt_iter_ops rpc_xprt_iter_listall;

अटल व्योम xprt_चयन_add_xprt_locked(काष्ठा rpc_xprt_चयन *xps,
		काष्ठा rpc_xprt *xprt)
अणु
	अगर (unlikely(xprt_get(xprt) == शून्य))
		वापस;
	list_add_tail_rcu(&xprt->xprt_चयन, &xps->xps_xprt_list);
	smp_wmb();
	अगर (xps->xps_nxprts == 0)
		xps->xps_net = xprt->xprt_net;
	xps->xps_nxprts++;
	xps->xps_nactive++;
पूर्ण

/**
 * rpc_xprt_चयन_add_xprt - Add a new rpc_xprt to an rpc_xprt_चयन
 * @xps: poपूर्णांकer to काष्ठा rpc_xprt_चयन
 * @xprt: poपूर्णांकer to काष्ठा rpc_xprt
 *
 * Adds xprt to the end of the list of काष्ठा rpc_xprt in xps.
 */
व्योम rpc_xprt_चयन_add_xprt(काष्ठा rpc_xprt_चयन *xps,
		काष्ठा rpc_xprt *xprt)
अणु
	अगर (xprt == शून्य)
		वापस;
	spin_lock(&xps->xps_lock);
	अगर (xps->xps_net == xprt->xprt_net || xps->xps_net == शून्य)
		xprt_चयन_add_xprt_locked(xps, xprt);
	spin_unlock(&xps->xps_lock);
पूर्ण

अटल व्योम xprt_चयन_हटाओ_xprt_locked(काष्ठा rpc_xprt_चयन *xps,
		काष्ठा rpc_xprt *xprt)
अणु
	अगर (unlikely(xprt == शून्य))
		वापस;
	xps->xps_nactive--;
	xps->xps_nxprts--;
	अगर (xps->xps_nxprts == 0)
		xps->xps_net = शून्य;
	smp_wmb();
	list_del_rcu(&xprt->xprt_चयन);
पूर्ण

/**
 * rpc_xprt_चयन_हटाओ_xprt - Removes an rpc_xprt from a rpc_xprt_चयन
 * @xps: poपूर्णांकer to काष्ठा rpc_xprt_चयन
 * @xprt: poपूर्णांकer to काष्ठा rpc_xprt
 *
 * Removes xprt from the list of काष्ठा rpc_xprt in xps.
 */
व्योम rpc_xprt_चयन_हटाओ_xprt(काष्ठा rpc_xprt_चयन *xps,
		काष्ठा rpc_xprt *xprt)
अणु
	spin_lock(&xps->xps_lock);
	xprt_चयन_हटाओ_xprt_locked(xps, xprt);
	spin_unlock(&xps->xps_lock);
	xprt_put(xprt);
पूर्ण

/**
 * xprt_चयन_alloc - Allocate a new काष्ठा rpc_xprt_चयन
 * @xprt: poपूर्णांकer to काष्ठा rpc_xprt
 * @gfp_flags: allocation flags
 *
 * On success, वापसs an initialised काष्ठा rpc_xprt_चयन, containing
 * the entry xprt. Returns शून्य on failure.
 */
काष्ठा rpc_xprt_चयन *xprt_चयन_alloc(काष्ठा rpc_xprt *xprt,
		gfp_t gfp_flags)
अणु
	काष्ठा rpc_xprt_चयन *xps;

	xps = kदो_स्मृति(माप(*xps), gfp_flags);
	अगर (xps != शून्य) अणु
		spin_lock_init(&xps->xps_lock);
		kref_init(&xps->xps_kref);
		xps->xps_nxprts = xps->xps_nactive = 0;
		atomic_दीर्घ_set(&xps->xps_queuelen, 0);
		xps->xps_net = शून्य;
		INIT_LIST_HEAD(&xps->xps_xprt_list);
		xps->xps_iter_ops = &rpc_xprt_iter_singular;
		xprt_चयन_add_xprt_locked(xps, xprt);
	पूर्ण

	वापस xps;
पूर्ण

अटल व्योम xprt_चयन_मुक्त_entries(काष्ठा rpc_xprt_चयन *xps)
अणु
	spin_lock(&xps->xps_lock);
	जबतक (!list_empty(&xps->xps_xprt_list)) अणु
		काष्ठा rpc_xprt *xprt;

		xprt = list_first_entry(&xps->xps_xprt_list,
				काष्ठा rpc_xprt, xprt_चयन);
		xprt_चयन_हटाओ_xprt_locked(xps, xprt);
		spin_unlock(&xps->xps_lock);
		xprt_put(xprt);
		spin_lock(&xps->xps_lock);
	पूर्ण
	spin_unlock(&xps->xps_lock);
पूर्ण

अटल व्योम xprt_चयन_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा rpc_xprt_चयन *xps = container_of(kref,
			काष्ठा rpc_xprt_चयन, xps_kref);

	xprt_चयन_मुक्त_entries(xps);
	kमुक्त_rcu(xps, xps_rcu);
पूर्ण

/**
 * xprt_चयन_get - Return a reference to a rpc_xprt_चयन
 * @xps: poपूर्णांकer to काष्ठा rpc_xprt_चयन
 *
 * Returns a reference to xps unless the refcount is alपढ़ोy zero.
 */
काष्ठा rpc_xprt_चयन *xprt_चयन_get(काष्ठा rpc_xprt_चयन *xps)
अणु
	अगर (xps != शून्य && kref_get_unless_zero(&xps->xps_kref))
		वापस xps;
	वापस शून्य;
पूर्ण

/**
 * xprt_चयन_put - Release a reference to a rpc_xprt_चयन
 * @xps: poपूर्णांकer to काष्ठा rpc_xprt_चयन
 *
 * Release the reference to xps, and मुक्त it once the refcount is zero.
 */
व्योम xprt_चयन_put(काष्ठा rpc_xprt_चयन *xps)
अणु
	अगर (xps != शून्य)
		kref_put(&xps->xps_kref, xprt_चयन_मुक्त);
पूर्ण

/**
 * rpc_xprt_चयन_set_roundrobin - Set a round-robin policy on rpc_xprt_चयन
 * @xps: poपूर्णांकer to काष्ठा rpc_xprt_चयन
 *
 * Sets a round-robin शेष policy क्रम iterators acting on xps.
 */
व्योम rpc_xprt_चयन_set_roundrobin(काष्ठा rpc_xprt_चयन *xps)
अणु
	अगर (READ_ONCE(xps->xps_iter_ops) != &rpc_xprt_iter_roundrobin)
		WRITE_ONCE(xps->xps_iter_ops, &rpc_xprt_iter_roundrobin);
पूर्ण

अटल
स्थिर काष्ठा rpc_xprt_iter_ops *xprt_iter_ops(स्थिर काष्ठा rpc_xprt_iter *xpi)
अणु
	अगर (xpi->xpi_ops != शून्य)
		वापस xpi->xpi_ops;
	वापस rcu_dereference(xpi->xpi_xpचयन)->xps_iter_ops;
पूर्ण

अटल
व्योम xprt_iter_no_शुरुआत(काष्ठा rpc_xprt_iter *xpi)
अणु
पूर्ण

अटल
व्योम xprt_iter_शेष_शुरुआत(काष्ठा rpc_xprt_iter *xpi)
अणु
	WRITE_ONCE(xpi->xpi_cursor, शून्य);
पूर्ण

अटल
bool xprt_is_active(स्थिर काष्ठा rpc_xprt *xprt)
अणु
	वापस kref_पढ़ो(&xprt->kref) != 0;
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_चयन_find_first_entry(काष्ठा list_head *head)
अणु
	काष्ठा rpc_xprt *pos;

	list_क्रम_each_entry_rcu(pos, head, xprt_चयन) अणु
		अगर (xprt_is_active(pos))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_iter_first_entry(काष्ठा rpc_xprt_iter *xpi)
अणु
	काष्ठा rpc_xprt_चयन *xps = rcu_dereference(xpi->xpi_xpचयन);

	अगर (xps == शून्य)
		वापस शून्य;
	वापस xprt_चयन_find_first_entry(&xps->xps_xprt_list);
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_चयन_find_current_entry(काष्ठा list_head *head,
		स्थिर काष्ठा rpc_xprt *cur)
अणु
	काष्ठा rpc_xprt *pos;
	bool found = false;

	list_क्रम_each_entry_rcu(pos, head, xprt_चयन) अणु
		अगर (cur == pos)
			found = true;
		अगर (found && xprt_is_active(pos))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_iter_current_entry(काष्ठा rpc_xprt_iter *xpi)
अणु
	काष्ठा rpc_xprt_चयन *xps = rcu_dereference(xpi->xpi_xpचयन);
	काष्ठा list_head *head;

	अगर (xps == शून्य)
		वापस शून्य;
	head = &xps->xps_xprt_list;
	अगर (xpi->xpi_cursor == शून्य || xps->xps_nxprts < 2)
		वापस xprt_चयन_find_first_entry(head);
	वापस xprt_चयन_find_current_entry(head, xpi->xpi_cursor);
पूर्ण

bool rpc_xprt_चयन_has_addr(काष्ठा rpc_xprt_चयन *xps,
			      स्थिर काष्ठा sockaddr *sap)
अणु
	काष्ठा list_head *head;
	काष्ठा rpc_xprt *pos;

	अगर (xps == शून्य || sap == शून्य)
		वापस false;

	head = &xps->xps_xprt_list;
	list_क्रम_each_entry_rcu(pos, head, xprt_चयन) अणु
		अगर (rpc_cmp_addr_port(sap, (काष्ठा sockaddr *)&pos->addr)) अणु
			pr_info("RPC:   addr %s already in xprt switch\n",
				pos->address_strings[RPC_DISPLAY_ADDR]);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_चयन_find_next_entry(काष्ठा list_head *head,
		स्थिर काष्ठा rpc_xprt *cur)
अणु
	काष्ठा rpc_xprt *pos, *prev = शून्य;
	bool found = false;

	list_क्रम_each_entry_rcu(pos, head, xprt_चयन) अणु
		अगर (cur == prev)
			found = true;
		अगर (found && xprt_is_active(pos))
			वापस pos;
		prev = pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_चयन_set_next_cursor(काष्ठा rpc_xprt_चयन *xps,
		काष्ठा rpc_xprt **cursor,
		xprt_चयन_find_xprt_t find_next)
अणु
	काष्ठा rpc_xprt *pos, *old;

	old = smp_load_acquire(cursor);
	pos = find_next(xps, old);
	smp_store_release(cursor, pos);
	वापस pos;
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_iter_next_entry_multiple(काष्ठा rpc_xprt_iter *xpi,
		xprt_चयन_find_xprt_t find_next)
अणु
	काष्ठा rpc_xprt_चयन *xps = rcu_dereference(xpi->xpi_xpचयन);

	अगर (xps == शून्य)
		वापस शून्य;
	वापस xprt_चयन_set_next_cursor(xps, &xpi->xpi_cursor, find_next);
पूर्ण

अटल
काष्ठा rpc_xprt *__xprt_चयन_find_next_entry_roundrobin(काष्ठा list_head *head,
		स्थिर काष्ठा rpc_xprt *cur)
अणु
	काष्ठा rpc_xprt *ret;

	ret = xprt_चयन_find_next_entry(head, cur);
	अगर (ret != शून्य)
		वापस ret;
	वापस xprt_चयन_find_first_entry(head);
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_चयन_find_next_entry_roundrobin(काष्ठा rpc_xprt_चयन *xps,
		स्थिर काष्ठा rpc_xprt *cur)
अणु
	काष्ठा list_head *head = &xps->xps_xprt_list;
	काष्ठा rpc_xprt *xprt;
	अचिन्हित पूर्णांक nactive;

	क्रम (;;) अणु
		अचिन्हित दीर्घ xprt_queuelen, xps_queuelen;

		xprt = __xprt_चयन_find_next_entry_roundrobin(head, cur);
		अगर (!xprt)
			अवरोध;
		xprt_queuelen = atomic_दीर्घ_पढ़ो(&xprt->queuelen);
		xps_queuelen = atomic_दीर्घ_पढ़ो(&xps->xps_queuelen);
		nactive = READ_ONCE(xps->xps_nactive);
		/* Exit loop अगर xprt_queuelen <= average queue length */
		अगर (xprt_queuelen * nactive <= xps_queuelen)
			अवरोध;
		cur = xprt;
	पूर्ण
	वापस xprt;
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_iter_next_entry_roundrobin(काष्ठा rpc_xprt_iter *xpi)
अणु
	वापस xprt_iter_next_entry_multiple(xpi,
			xprt_चयन_find_next_entry_roundrobin);
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_चयन_find_next_entry_all(काष्ठा rpc_xprt_चयन *xps,
		स्थिर काष्ठा rpc_xprt *cur)
अणु
	वापस xprt_चयन_find_next_entry(&xps->xps_xprt_list, cur);
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_iter_next_entry_all(काष्ठा rpc_xprt_iter *xpi)
अणु
	वापस xprt_iter_next_entry_multiple(xpi,
			xprt_चयन_find_next_entry_all);
पूर्ण

/*
 * xprt_iter_शुरुआत - Resets the xprt iterator
 * @xpi: poपूर्णांकer to rpc_xprt_iter
 *
 * Resets xpi to ensure that it poपूर्णांकs to the first entry in the list
 * of transports.
 */
अटल
व्योम xprt_iter_शुरुआत(काष्ठा rpc_xprt_iter *xpi)
अणु
	rcu_पढ़ो_lock();
	xprt_iter_ops(xpi)->xpi_शुरुआत(xpi);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम __xprt_iter_init(काष्ठा rpc_xprt_iter *xpi,
		काष्ठा rpc_xprt_चयन *xps,
		स्थिर काष्ठा rpc_xprt_iter_ops *ops)
अणु
	rcu_assign_poपूर्णांकer(xpi->xpi_xpचयन, xprt_चयन_get(xps));
	xpi->xpi_cursor = शून्य;
	xpi->xpi_ops = ops;
पूर्ण

/**
 * xprt_iter_init - Initialise an xprt iterator
 * @xpi: poपूर्णांकer to rpc_xprt_iter
 * @xps: poपूर्णांकer to rpc_xprt_चयन
 *
 * Initialises the iterator to use the शेष iterator ops
 * as set in xps. This function is मुख्यly पूर्णांकended क्रम पूर्णांकernal
 * use in the rpc_client.
 */
व्योम xprt_iter_init(काष्ठा rpc_xprt_iter *xpi,
		काष्ठा rpc_xprt_चयन *xps)
अणु
	__xprt_iter_init(xpi, xps, शून्य);
पूर्ण

/**
 * xprt_iter_init_listall - Initialise an xprt iterator
 * @xpi: poपूर्णांकer to rpc_xprt_iter
 * @xps: poपूर्णांकer to rpc_xprt_चयन
 *
 * Initialises the iterator to iterate once through the entire list
 * of entries in xps.
 */
व्योम xprt_iter_init_listall(काष्ठा rpc_xprt_iter *xpi,
		काष्ठा rpc_xprt_चयन *xps)
अणु
	__xprt_iter_init(xpi, xps, &rpc_xprt_iter_listall);
पूर्ण

/**
 * xprt_iter_xchg_चयन - Atomically swap out the rpc_xprt_चयन
 * @xpi: poपूर्णांकer to rpc_xprt_iter
 * @newचयन: poपूर्णांकer to a new rpc_xprt_चयन or शून्य
 *
 * Swaps out the existing xpi->xpi_xpचयन with a new value.
 */
काष्ठा rpc_xprt_चयन *xprt_iter_xchg_चयन(काष्ठा rpc_xprt_iter *xpi,
		काष्ठा rpc_xprt_चयन *newचयन)
अणु
	काष्ठा rpc_xprt_चयन __rcu *oldचयन;

	/* Atomically swap out the old xpचयन */
	oldचयन = xchg(&xpi->xpi_xpचयन, RCU_INITIALIZER(newचयन));
	अगर (newचयन != शून्य)
		xprt_iter_शुरुआत(xpi);
	वापस rcu_dereference_रक्षित(oldचयन, true);
पूर्ण

/**
 * xprt_iter_destroy - Destroys the xprt iterator
 * @xpi: poपूर्णांकer to rpc_xprt_iter
 */
व्योम xprt_iter_destroy(काष्ठा rpc_xprt_iter *xpi)
अणु
	xprt_चयन_put(xprt_iter_xchg_चयन(xpi, शून्य));
पूर्ण

/**
 * xprt_iter_xprt - Returns the rpc_xprt poपूर्णांकed to by the cursor
 * @xpi: poपूर्णांकer to rpc_xprt_iter
 *
 * Returns a poपूर्णांकer to the काष्ठा rpc_xprt that is currently
 * poपूर्णांकed to by the cursor.
 * Caller must be holding rcu_पढ़ो_lock().
 */
काष्ठा rpc_xprt *xprt_iter_xprt(काष्ठा rpc_xprt_iter *xpi)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस xprt_iter_ops(xpi)->xpi_xprt(xpi);
पूर्ण

अटल
काष्ठा rpc_xprt *xprt_iter_get_helper(काष्ठा rpc_xprt_iter *xpi,
		काष्ठा rpc_xprt *(*fn)(काष्ठा rpc_xprt_iter *))
अणु
	काष्ठा rpc_xprt *ret;

	करो अणु
		ret = fn(xpi);
		अगर (ret == शून्य)
			अवरोध;
		ret = xprt_get(ret);
	पूर्ण जबतक (ret == शून्य);
	वापस ret;
पूर्ण

/**
 * xprt_iter_get_xprt - Returns the rpc_xprt poपूर्णांकed to by the cursor
 * @xpi: poपूर्णांकer to rpc_xprt_iter
 *
 * Returns a reference to the काष्ठा rpc_xprt that is currently
 * poपूर्णांकed to by the cursor.
 */
काष्ठा rpc_xprt *xprt_iter_get_xprt(काष्ठा rpc_xprt_iter *xpi)
अणु
	काष्ठा rpc_xprt *xprt;

	rcu_पढ़ो_lock();
	xprt = xprt_iter_get_helper(xpi, xprt_iter_ops(xpi)->xpi_xprt);
	rcu_पढ़ो_unlock();
	वापस xprt;
पूर्ण

/**
 * xprt_iter_get_next - Returns the next rpc_xprt following the cursor
 * @xpi: poपूर्णांकer to rpc_xprt_iter
 *
 * Returns a reference to the काष्ठा rpc_xprt that immediately follows the
 * entry poपूर्णांकed to by the cursor.
 */
काष्ठा rpc_xprt *xprt_iter_get_next(काष्ठा rpc_xprt_iter *xpi)
अणु
	काष्ठा rpc_xprt *xprt;

	rcu_पढ़ो_lock();
	xprt = xprt_iter_get_helper(xpi, xprt_iter_ops(xpi)->xpi_next);
	rcu_पढ़ो_unlock();
	वापस xprt;
पूर्ण

/* Policy क्रम always वापसing the first entry in the rpc_xprt_चयन */
अटल
स्थिर काष्ठा rpc_xprt_iter_ops rpc_xprt_iter_singular = अणु
	.xpi_शुरुआत = xprt_iter_no_शुरुआत,
	.xpi_xprt = xprt_iter_first_entry,
	.xpi_next = xprt_iter_first_entry,
पूर्ण;

/* Policy क्रम round-robin iteration of entries in the rpc_xprt_चयन */
अटल
स्थिर काष्ठा rpc_xprt_iter_ops rpc_xprt_iter_roundrobin = अणु
	.xpi_शुरुआत = xprt_iter_शेष_शुरुआत,
	.xpi_xprt = xprt_iter_current_entry,
	.xpi_next = xprt_iter_next_entry_roundrobin,
पूर्ण;

/* Policy क्रम once-through iteration of entries in the rpc_xprt_चयन */
अटल
स्थिर काष्ठा rpc_xprt_iter_ops rpc_xprt_iter_listall = अणु
	.xpi_शुरुआत = xprt_iter_शेष_शुरुआत,
	.xpi_xprt = xprt_iter_current_entry,
	.xpi_next = xprt_iter_next_entry_all,
पूर्ण;

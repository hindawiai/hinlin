<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bug.h>
#समावेश <linux/export.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/xarray.h>

/**
 * idr_alloc_u32() - Allocate an ID.
 * @idr: IDR handle.
 * @ptr: Poपूर्णांकer to be associated with the new ID.
 * @nextid: Poपूर्णांकer to an ID.
 * @max: The maximum ID to allocate (inclusive).
 * @gfp: Memory allocation flags.
 *
 * Allocates an unused ID in the range specअगरied by @nextid and @max.
 * Note that @max is inclusive whereas the @end parameter to idr_alloc()
 * is exclusive.  The new ID is asचिन्हित to @nextid beक्रमe the poपूर्णांकer
 * is inserted पूर्णांकo the IDR, so अगर @nextid poपूर्णांकs पूर्णांकo the object poपूर्णांकed
 * to by @ptr, a concurrent lookup will not find an uninitialised ID.
 *
 * The caller should provide their own locking to ensure that two
 * concurrent modअगरications to the IDR are not possible.  Read-only
 * accesses to the IDR may be करोne under the RCU पढ़ो lock or may
 * exclude simultaneous ग_लिखोrs.
 *
 * Return: 0 अगर an ID was allocated, -ENOMEM अगर memory allocation failed,
 * or -ENOSPC अगर no मुक्त IDs could be found.  If an error occurred,
 * @nextid is unchanged.
 */
पूर्णांक idr_alloc_u32(काष्ठा idr *idr, व्योम *ptr, u32 *nextid,
			अचिन्हित दीर्घ max, gfp_t gfp)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;
	अचिन्हित पूर्णांक base = idr->idr_base;
	अचिन्हित पूर्णांक id = *nextid;

	अगर (WARN_ON_ONCE(!(idr->idr_rt.xa_flags & ROOT_IS_IDR)))
		idr->idr_rt.xa_flags |= IDR_RT_MARKER;

	id = (id < base) ? 0 : id - base;
	radix_tree_iter_init(&iter, id);
	slot = idr_get_मुक्त(&idr->idr_rt, &iter, gfp, max - base);
	अगर (IS_ERR(slot))
		वापस PTR_ERR(slot);

	*nextid = iter.index + base;
	/* there is a memory barrier inside radix_tree_iter_replace() */
	radix_tree_iter_replace(&idr->idr_rt, &iter, slot, ptr);
	radix_tree_iter_tag_clear(&idr->idr_rt, &iter, IDR_FREE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(idr_alloc_u32);

/**
 * idr_alloc() - Allocate an ID.
 * @idr: IDR handle.
 * @ptr: Poपूर्णांकer to be associated with the new ID.
 * @start: The minimum ID (inclusive).
 * @end: The maximum ID (exclusive).
 * @gfp: Memory allocation flags.
 *
 * Allocates an unused ID in the range specअगरied by @start and @end.  If
 * @end is <= 0, it is treated as one larger than %पूर्णांक_उच्च.  This allows
 * callers to use @start + N as @end as दीर्घ as N is within पूर्णांकeger range.
 *
 * The caller should provide their own locking to ensure that two
 * concurrent modअगरications to the IDR are not possible.  Read-only
 * accesses to the IDR may be करोne under the RCU पढ़ो lock or may
 * exclude simultaneous ग_लिखोrs.
 *
 * Return: The newly allocated ID, -ENOMEM अगर memory allocation failed,
 * or -ENOSPC अगर no मुक्त IDs could be found.
 */
पूर्णांक idr_alloc(काष्ठा idr *idr, व्योम *ptr, पूर्णांक start, पूर्णांक end, gfp_t gfp)
अणु
	u32 id = start;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(start < 0))
		वापस -EINVAL;

	ret = idr_alloc_u32(idr, ptr, &id, end > 0 ? end - 1 : पूर्णांक_उच्च, gfp);
	अगर (ret)
		वापस ret;

	वापस id;
पूर्ण
EXPORT_SYMBOL_GPL(idr_alloc);

/**
 * idr_alloc_cyclic() - Allocate an ID cyclically.
 * @idr: IDR handle.
 * @ptr: Poपूर्णांकer to be associated with the new ID.
 * @start: The minimum ID (inclusive).
 * @end: The maximum ID (exclusive).
 * @gfp: Memory allocation flags.
 *
 * Allocates an unused ID in the range specअगरied by @nextid and @end.  If
 * @end is <= 0, it is treated as one larger than %पूर्णांक_उच्च.  This allows
 * callers to use @start + N as @end as दीर्घ as N is within पूर्णांकeger range.
 * The search क्रम an unused ID will start at the last ID allocated and will
 * wrap around to @start अगर no मुक्त IDs are found beक्रमe reaching @end.
 *
 * The caller should provide their own locking to ensure that two
 * concurrent modअगरications to the IDR are not possible.  Read-only
 * accesses to the IDR may be करोne under the RCU पढ़ो lock or may
 * exclude simultaneous ग_लिखोrs.
 *
 * Return: The newly allocated ID, -ENOMEM अगर memory allocation failed,
 * or -ENOSPC अगर no मुक्त IDs could be found.
 */
पूर्णांक idr_alloc_cyclic(काष्ठा idr *idr, व्योम *ptr, पूर्णांक start, पूर्णांक end, gfp_t gfp)
अणु
	u32 id = idr->idr_next;
	पूर्णांक err, max = end > 0 ? end - 1 : पूर्णांक_उच्च;

	अगर ((पूर्णांक)id < start)
		id = start;

	err = idr_alloc_u32(idr, ptr, &id, max, gfp);
	अगर ((err == -ENOSPC) && (id > start)) अणु
		id = start;
		err = idr_alloc_u32(idr, ptr, &id, max, gfp);
	पूर्ण
	अगर (err)
		वापस err;

	idr->idr_next = id + 1;
	वापस id;
पूर्ण
EXPORT_SYMBOL(idr_alloc_cyclic);

/**
 * idr_हटाओ() - Remove an ID from the IDR.
 * @idr: IDR handle.
 * @id: Poपूर्णांकer ID.
 *
 * Removes this ID from the IDR.  If the ID was not previously in the IDR,
 * this function वापसs %शून्य.
 *
 * Since this function modअगरies the IDR, the caller should provide their
 * own locking to ensure that concurrent modअगरication of the same IDR is
 * not possible.
 *
 * Return: The poपूर्णांकer क्रमmerly associated with this ID.
 */
व्योम *idr_हटाओ(काष्ठा idr *idr, अचिन्हित दीर्घ id)
अणु
	वापस radix_tree_delete_item(&idr->idr_rt, id - idr->idr_base, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(idr_हटाओ);

/**
 * idr_find() - Return poपूर्णांकer क्रम given ID.
 * @idr: IDR handle.
 * @id: Poपूर्णांकer ID.
 *
 * Looks up the poपूर्णांकer associated with this ID.  A %शून्य poपूर्णांकer may
 * indicate that @id is not allocated or that the %शून्य poपूर्णांकer was
 * associated with this ID.
 *
 * This function can be called under rcu_पढ़ो_lock(), given that the leaf
 * poपूर्णांकers lअगरeबार are correctly managed.
 *
 * Return: The poपूर्णांकer associated with this ID.
 */
व्योम *idr_find(स्थिर काष्ठा idr *idr, अचिन्हित दीर्घ id)
अणु
	वापस radix_tree_lookup(&idr->idr_rt, id - idr->idr_base);
पूर्ण
EXPORT_SYMBOL_GPL(idr_find);

/**
 * idr_क्रम_each() - Iterate through all stored poपूर्णांकers.
 * @idr: IDR handle.
 * @fn: Function to be called क्रम each poपूर्णांकer.
 * @data: Data passed to callback function.
 *
 * The callback function will be called क्रम each entry in @idr, passing
 * the ID, the entry and @data.
 *
 * If @fn वापसs anything other than %0, the iteration stops and that
 * value is वापसed from this function.
 *
 * idr_क्रम_each() can be called concurrently with idr_alloc() and
 * idr_हटाओ() अगर रक्षित by RCU.  Newly added entries may not be
 * seen and deleted entries may be seen, but adding and removing entries
 * will not cause other entries to be skipped, nor spurious ones to be seen.
 */
पूर्णांक idr_क्रम_each(स्थिर काष्ठा idr *idr,
		पूर्णांक (*fn)(पूर्णांक id, व्योम *p, व्योम *data), व्योम *data)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;
	पूर्णांक base = idr->idr_base;

	radix_tree_क्रम_each_slot(slot, &idr->idr_rt, &iter, 0) अणु
		पूर्णांक ret;
		अचिन्हित दीर्घ id = iter.index + base;

		अगर (WARN_ON_ONCE(id > पूर्णांक_उच्च))
			अवरोध;
		ret = fn(id, rcu_dereference_raw(*slot), data);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(idr_क्रम_each);

/**
 * idr_get_next_ul() - Find next populated entry.
 * @idr: IDR handle.
 * @nextid: Poपूर्णांकer to an ID.
 *
 * Returns the next populated entry in the tree with an ID greater than
 * or equal to the value poपूर्णांकed to by @nextid.  On निकास, @nextid is updated
 * to the ID of the found value.  To use in a loop, the value poपूर्णांकed to by
 * nextid must be incremented by the user.
 */
व्योम *idr_get_next_ul(काष्ठा idr *idr, अचिन्हित दीर्घ *nextid)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;
	व्योम *entry = शून्य;
	अचिन्हित दीर्घ base = idr->idr_base;
	अचिन्हित दीर्घ id = *nextid;

	id = (id < base) ? 0 : id - base;
	radix_tree_क्रम_each_slot(slot, &idr->idr_rt, &iter, id) अणु
		entry = rcu_dereference_raw(*slot);
		अगर (!entry)
			जारी;
		अगर (!xa_is_पूर्णांकernal(entry))
			अवरोध;
		अगर (slot != &idr->idr_rt.xa_head && !xa_is_retry(entry))
			अवरोध;
		slot = radix_tree_iter_retry(&iter);
	पूर्ण
	अगर (!slot)
		वापस शून्य;

	*nextid = iter.index + base;
	वापस entry;
पूर्ण
EXPORT_SYMBOL(idr_get_next_ul);

/**
 * idr_get_next() - Find next populated entry.
 * @idr: IDR handle.
 * @nextid: Poपूर्णांकer to an ID.
 *
 * Returns the next populated entry in the tree with an ID greater than
 * or equal to the value poपूर्णांकed to by @nextid.  On निकास, @nextid is updated
 * to the ID of the found value.  To use in a loop, the value poपूर्णांकed to by
 * nextid must be incremented by the user.
 */
व्योम *idr_get_next(काष्ठा idr *idr, पूर्णांक *nextid)
अणु
	अचिन्हित दीर्घ id = *nextid;
	व्योम *entry = idr_get_next_ul(idr, &id);

	अगर (WARN_ON_ONCE(id > पूर्णांक_उच्च))
		वापस शून्य;
	*nextid = id;
	वापस entry;
पूर्ण
EXPORT_SYMBOL(idr_get_next);

/**
 * idr_replace() - replace poपूर्णांकer क्रम given ID.
 * @idr: IDR handle.
 * @ptr: New poपूर्णांकer to associate with the ID.
 * @id: ID to change.
 *
 * Replace the poपूर्णांकer रेजिस्टरed with an ID and वापस the old value.
 * This function can be called under the RCU पढ़ो lock concurrently with
 * idr_alloc() and idr_हटाओ() (as दीर्घ as the ID being हटाओd is not
 * the one being replaced!).
 *
 * Returns: the old value on success.  %-ENOENT indicates that @id was not
 * found.  %-EINVAL indicates that @ptr was not valid.
 */
व्योम *idr_replace(काष्ठा idr *idr, व्योम *ptr, अचिन्हित दीर्घ id)
अणु
	काष्ठा radix_tree_node *node;
	व्योम __rcu **slot = शून्य;
	व्योम *entry;

	id -= idr->idr_base;

	entry = __radix_tree_lookup(&idr->idr_rt, id, &node, &slot);
	अगर (!slot || radix_tree_tag_get(&idr->idr_rt, id, IDR_FREE))
		वापस ERR_PTR(-ENOENT);

	__radix_tree_replace(&idr->idr_rt, node, slot, ptr);

	वापस entry;
पूर्ण
EXPORT_SYMBOL(idr_replace);

/**
 * DOC: IDA description
 *
 * The IDA is an ID allocator which करोes not provide the ability to
 * associate an ID with a poपूर्णांकer.  As such, it only needs to store one
 * bit per ID, and so is more space efficient than an IDR.  To use an IDA,
 * define it using DEFINE_IDA() (or embed a &काष्ठा ida in a data काष्ठाure,
 * then initialise it using ida_init()).  To allocate a new ID, call
 * ida_alloc(), ida_alloc_min(), ida_alloc_max() or ida_alloc_range().
 * To मुक्त an ID, call ida_मुक्त().
 *
 * ida_destroy() can be used to dispose of an IDA without needing to
 * मुक्त the inभागidual IDs in it.  You can use ida_is_empty() to find
 * out whether the IDA has any IDs currently allocated.
 *
 * The IDA handles its own locking.  It is safe to call any of the IDA
 * functions without synchronisation in your code.
 *
 * IDs are currently limited to the range [0-पूर्णांक_उच्च].  If this is an awkward
 * limitation, it should be quite straightक्रमward to उठाओ the maximum.
 */

/*
 * Developer's notes:
 *
 * The IDA uses the functionality provided by the XArray to store biपंचांगaps in
 * each entry.  The XA_FREE_MARK is only cleared when all bits in the biपंचांगap
 * have been set.
 *
 * I considered telling the XArray that each slot is an order-10 node
 * and indexing by bit number, but the XArray can't allow a single multi-index
 * entry in the head, which would signअगरicantly increase memory consumption
 * क्रम the IDA.  So instead we भागide the index by the number of bits in the
 * leaf biपंचांगap beक्रमe करोing a radix tree lookup.
 *
 * As an optimisation, अगर there are only a few low bits set in any given
 * leaf, instead of allocating a 128-byte biपंचांगap, we store the bits
 * as a value entry.  Value entries never have the XA_FREE_MARK cleared
 * because we can always convert them पूर्णांकo a biपंचांगap entry.
 *
 * It would be possible to optimise further; once we've run out of a
 * single 128-byte biपंचांगap, we currently चयन to a 576-byte node, put
 * the 128-byte biपंचांगap in the first entry and then start allocating extra
 * 128-byte entries.  We could instead use the 512 bytes of the node's
 * data as a biपंचांगap beक्रमe moving to that scheme.  I करो not believe this
 * is a worthजबतक optimisation; Rयंत्रus Villemoes surveyed the current
 * users of the IDA and almost none of them use more than 1024 entries.
 * Those that करो use more than the 8192 IDs that the 512 bytes would
 * provide.
 *
 * The IDA always uses a lock to alloc/मुक्त.  If we add a 'test_bit'
 * equivalent, it will still need locking.  Going to RCU lookup would require
 * using RCU to मुक्त biपंचांगaps, and that's not trivial without embedding an
 * RCU head in the biपंचांगap, which adds a 2-poपूर्णांकer overhead to each 128-byte
 * biपंचांगap, which is excessive.
 */

/**
 * ida_alloc_range() - Allocate an unused ID.
 * @ida: IDA handle.
 * @min: Lowest ID to allocate.
 * @max: Highest ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Allocate an ID between @min and @max, inclusive.  The allocated ID will
 * not exceed %पूर्णांक_उच्च, even अगर @max is larger.
 *
 * Context: Any context. It is safe to call this function without
 * locking in your code.
 * Return: The allocated ID, or %-ENOMEM अगर memory could not be allocated,
 * or %-ENOSPC अगर there are no मुक्त IDs.
 */
पूर्णांक ida_alloc_range(काष्ठा ida *ida, अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max,
			gfp_t gfp)
अणु
	XA_STATE(xas, &ida->xa, min / IDA_BITMAP_BITS);
	अचिन्हित bit = min % IDA_BITMAP_BITS;
	अचिन्हित दीर्घ flags;
	काष्ठा ida_biपंचांगap *biपंचांगap, *alloc = शून्य;

	अगर ((पूर्णांक)min < 0)
		वापस -ENOSPC;

	अगर ((पूर्णांक)max < 0)
		max = पूर्णांक_उच्च;

retry:
	xas_lock_irqsave(&xas, flags);
next:
	biपंचांगap = xas_find_marked(&xas, max / IDA_BITMAP_BITS, XA_FREE_MARK);
	अगर (xas.xa_index > min / IDA_BITMAP_BITS)
		bit = 0;
	अगर (xas.xa_index * IDA_BITMAP_BITS + bit > max)
		जाओ nospc;

	अगर (xa_is_value(biपंचांगap)) अणु
		अचिन्हित दीर्घ पंचांगp = xa_to_value(biपंचांगap);

		अगर (bit < BITS_PER_XA_VALUE) अणु
			bit = find_next_zero_bit(&पंचांगp, BITS_PER_XA_VALUE, bit);
			अगर (xas.xa_index * IDA_BITMAP_BITS + bit > max)
				जाओ nospc;
			अगर (bit < BITS_PER_XA_VALUE) अणु
				पंचांगp |= 1UL << bit;
				xas_store(&xas, xa_mk_value(पंचांगp));
				जाओ out;
			पूर्ण
		पूर्ण
		biपंचांगap = alloc;
		अगर (!biपंचांगap)
			biपंचांगap = kzalloc(माप(*biपंचांगap), GFP_NOWAIT);
		अगर (!biपंचांगap)
			जाओ alloc;
		biपंचांगap->biपंचांगap[0] = पंचांगp;
		xas_store(&xas, biपंचांगap);
		अगर (xas_error(&xas)) अणु
			biपंचांगap->biपंचांगap[0] = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (biपंचांगap) अणु
		bit = find_next_zero_bit(biपंचांगap->biपंचांगap, IDA_BITMAP_BITS, bit);
		अगर (xas.xa_index * IDA_BITMAP_BITS + bit > max)
			जाओ nospc;
		अगर (bit == IDA_BITMAP_BITS)
			जाओ next;

		__set_bit(bit, biपंचांगap->biपंचांगap);
		अगर (biपंचांगap_full(biपंचांगap->biपंचांगap, IDA_BITMAP_BITS))
			xas_clear_mark(&xas, XA_FREE_MARK);
	पूर्ण अन्यथा अणु
		अगर (bit < BITS_PER_XA_VALUE) अणु
			biपंचांगap = xa_mk_value(1UL << bit);
		पूर्ण अन्यथा अणु
			biपंचांगap = alloc;
			अगर (!biपंचांगap)
				biपंचांगap = kzalloc(माप(*biपंचांगap), GFP_NOWAIT);
			अगर (!biपंचांगap)
				जाओ alloc;
			__set_bit(bit, biपंचांगap->biपंचांगap);
		पूर्ण
		xas_store(&xas, biपंचांगap);
	पूर्ण
out:
	xas_unlock_irqrestore(&xas, flags);
	अगर (xas_nomem(&xas, gfp)) अणु
		xas.xa_index = min / IDA_BITMAP_BITS;
		bit = min % IDA_BITMAP_BITS;
		जाओ retry;
	पूर्ण
	अगर (biपंचांगap != alloc)
		kमुक्त(alloc);
	अगर (xas_error(&xas))
		वापस xas_error(&xas);
	वापस xas.xa_index * IDA_BITMAP_BITS + bit;
alloc:
	xas_unlock_irqrestore(&xas, flags);
	alloc = kzalloc(माप(*biपंचांगap), gfp);
	अगर (!alloc)
		वापस -ENOMEM;
	xas_set(&xas, min / IDA_BITMAP_BITS);
	bit = min % IDA_BITMAP_BITS;
	जाओ retry;
nospc:
	xas_unlock_irqrestore(&xas, flags);
	kमुक्त(alloc);
	वापस -ENOSPC;
पूर्ण
EXPORT_SYMBOL(ida_alloc_range);

/**
 * ida_मुक्त() - Release an allocated ID.
 * @ida: IDA handle.
 * @id: Previously allocated ID.
 *
 * Context: Any context. It is safe to call this function without
 * locking in your code.
 */
व्योम ida_मुक्त(काष्ठा ida *ida, अचिन्हित पूर्णांक id)
अणु
	XA_STATE(xas, &ida->xa, id / IDA_BITMAP_BITS);
	अचिन्हित bit = id % IDA_BITMAP_BITS;
	काष्ठा ida_biपंचांगap *biपंचांगap;
	अचिन्हित दीर्घ flags;

	BUG_ON((पूर्णांक)id < 0);

	xas_lock_irqsave(&xas, flags);
	biपंचांगap = xas_load(&xas);

	अगर (xa_is_value(biपंचांगap)) अणु
		अचिन्हित दीर्घ v = xa_to_value(biपंचांगap);
		अगर (bit >= BITS_PER_XA_VALUE)
			जाओ err;
		अगर (!(v & (1UL << bit)))
			जाओ err;
		v &= ~(1UL << bit);
		अगर (!v)
			जाओ delete;
		xas_store(&xas, xa_mk_value(v));
	पूर्ण अन्यथा अणु
		अगर (!test_bit(bit, biपंचांगap->biपंचांगap))
			जाओ err;
		__clear_bit(bit, biपंचांगap->biपंचांगap);
		xas_set_mark(&xas, XA_FREE_MARK);
		अगर (biपंचांगap_empty(biपंचांगap->biपंचांगap, IDA_BITMAP_BITS)) अणु
			kमुक्त(biपंचांगap);
delete:
			xas_store(&xas, शून्य);
		पूर्ण
	पूर्ण
	xas_unlock_irqrestore(&xas, flags);
	वापस;
 err:
	xas_unlock_irqrestore(&xas, flags);
	WARN(1, "ida_free called for id=%d which is not allocated.\n", id);
पूर्ण
EXPORT_SYMBOL(ida_मुक्त);

/**
 * ida_destroy() - Free all IDs.
 * @ida: IDA handle.
 *
 * Calling this function मुक्तs all IDs and releases all resources used
 * by an IDA.  When this call वापसs, the IDA is empty and can be reused
 * or मुक्तd.  If the IDA is alपढ़ोy empty, there is no need to call this
 * function.
 *
 * Context: Any context. It is safe to call this function without
 * locking in your code.
 */
व्योम ida_destroy(काष्ठा ida *ida)
अणु
	XA_STATE(xas, &ida->xa, 0);
	काष्ठा ida_biपंचांगap *biपंचांगap;
	अचिन्हित दीर्घ flags;

	xas_lock_irqsave(&xas, flags);
	xas_क्रम_each(&xas, biपंचांगap, अच_दीर्घ_उच्च) अणु
		अगर (!xa_is_value(biपंचांगap))
			kमुक्त(biपंचांगap);
		xas_store(&xas, शून्य);
	पूर्ण
	xas_unlock_irqrestore(&xas, flags);
पूर्ण
EXPORT_SYMBOL(ida_destroy);

#अगर_अघोषित __KERNEL__
बाह्य व्योम xa_dump_index(अचिन्हित दीर्घ index, अचिन्हित पूर्णांक shअगरt);
#घोषणा IDA_CHUNK_SHIFT		ilog2(IDA_BITMAP_BITS)

अटल व्योम ida_dump_entry(व्योम *entry, अचिन्हित दीर्घ index)
अणु
	अचिन्हित दीर्घ i;

	अगर (!entry)
		वापस;

	अगर (xa_is_node(entry)) अणु
		काष्ठा xa_node *node = xa_to_node(entry);
		अचिन्हित पूर्णांक shअगरt = node->shअगरt + IDA_CHUNK_SHIFT +
			XA_CHUNK_SHIFT;

		xa_dump_index(index * IDA_BITMAP_BITS, shअगरt);
		xa_dump_node(node);
		क्रम (i = 0; i < XA_CHUNK_SIZE; i++)
			ida_dump_entry(node->slots[i],
					index | (i << node->shअगरt));
	पूर्ण अन्यथा अगर (xa_is_value(entry)) अणु
		xa_dump_index(index * IDA_BITMAP_BITS, ilog2(BITS_PER_LONG));
		pr_cont("value: data %lx [%px]\n", xa_to_value(entry), entry);
	पूर्ण अन्यथा अणु
		काष्ठा ida_biपंचांगap *biपंचांगap = entry;

		xa_dump_index(index * IDA_BITMAP_BITS, IDA_CHUNK_SHIFT);
		pr_cont("bitmap: %p data", biपंचांगap);
		क्रम (i = 0; i < IDA_BITMAP_LONGS; i++)
			pr_cont(" %lx", biपंचांगap->biपंचांगap[i]);
		pr_cont("\n");
	पूर्ण
पूर्ण

अटल व्योम ida_dump(काष्ठा ida *ida)
अणु
	काष्ठा xarray *xa = &ida->xa;
	pr_debug("ida: %p node %p free %d\n", ida, xa->xa_head,
				xa->xa_flags >> ROOT_TAG_SHIFT);
	ida_dump_entry(xa->xa_head, 0);
पूर्ण
#पूर्ण_अगर

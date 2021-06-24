<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/idr.h
 * 
 * 2002-10-18  written by Jim Houston jim.houston@ccur.com
 *	Copyright (C) 2002 by Concurrent Computer Corporation
 *
 * Small id to poपूर्णांकer translation service aव्योमing fixed sized
 * tables.
 */

#अगर_अघोषित __IDR_H__
#घोषणा __IDR_H__

#समावेश <linux/radix-tree.h>
#समावेश <linux/gfp.h>
#समावेश <linux/percpu.h>

काष्ठा idr अणु
	काष्ठा radix_tree_root	idr_rt;
	अचिन्हित पूर्णांक		idr_base;
	अचिन्हित पूर्णांक		idr_next;
पूर्ण;

/*
 * The IDR API करोes not expose the tagging functionality of the radix tree
 * to users.  Use tag 0 to track whether a node has मुक्त space below it.
 */
#घोषणा IDR_FREE	0

/* Set the IDR flag and the IDR_FREE tag */
#घोषणा IDR_RT_MARKER	(ROOT_IS_IDR | (__क्रमce gfp_t)			\
					(1 << (ROOT_TAG_SHIFT + IDR_FREE)))

#घोषणा IDR_INIT_BASE(name, base) अणु					\
	.idr_rt = RADIX_TREE_INIT(name, IDR_RT_MARKER),			\
	.idr_base = (base),						\
	.idr_next = 0,							\
पूर्ण

/**
 * IDR_INIT() - Initialise an IDR.
 * @name: Name of IDR.
 *
 * A freshly-initialised IDR contains no IDs.
 */
#घोषणा IDR_INIT(name)	IDR_INIT_BASE(name, 0)

/**
 * DEFINE_IDR() - Define a अटलally-allocated IDR.
 * @name: Name of IDR.
 *
 * An IDR defined using this macro is पढ़ोy क्रम use with no additional
 * initialisation required.  It contains no IDs.
 */
#घोषणा DEFINE_IDR(name)	काष्ठा idr name = IDR_INIT(name)

/**
 * idr_get_cursor - Return the current position of the cyclic allocator
 * @idr: idr handle
 *
 * The value वापसed is the value that will be next वापसed from
 * idr_alloc_cyclic() अगर it is मुक्त (otherwise the search will start from
 * this position).
 */
अटल अंतरभूत अचिन्हित पूर्णांक idr_get_cursor(स्थिर काष्ठा idr *idr)
अणु
	वापस READ_ONCE(idr->idr_next);
पूर्ण

/**
 * idr_set_cursor - Set the current position of the cyclic allocator
 * @idr: idr handle
 * @val: new position
 *
 * The next call to idr_alloc_cyclic() will वापस @val अगर it is मुक्त
 * (otherwise the search will start from this position).
 */
अटल अंतरभूत व्योम idr_set_cursor(काष्ठा idr *idr, अचिन्हित पूर्णांक val)
अणु
	WRITE_ONCE(idr->idr_next, val);
पूर्ण

/**
 * DOC: idr sync
 * idr synchronization (stolen from radix-tree.h)
 *
 * idr_find() is able to be called locklessly, using RCU. The caller must
 * ensure calls to this function are made within rcu_पढ़ो_lock() regions.
 * Other पढ़ोers (lock-मुक्त or otherwise) and modअगरications may be running
 * concurrently.
 *
 * It is still required that the caller manage the synchronization and
 * lअगरeबार of the items. So अगर RCU lock-मुक्त lookups are used, typically
 * this would mean that the items have their own locks, or are amenable to
 * lock-मुक्त access; and that the items are मुक्तd by RCU (or only मुक्तd after
 * having been deleted from the idr tree *and* a synchronize_rcu() grace
 * period).
 */

#घोषणा idr_lock(idr)		xa_lock(&(idr)->idr_rt)
#घोषणा idr_unlock(idr)		xa_unlock(&(idr)->idr_rt)
#घोषणा idr_lock_bh(idr)	xa_lock_bh(&(idr)->idr_rt)
#घोषणा idr_unlock_bh(idr)	xa_unlock_bh(&(idr)->idr_rt)
#घोषणा idr_lock_irq(idr)	xa_lock_irq(&(idr)->idr_rt)
#घोषणा idr_unlock_irq(idr)	xa_unlock_irq(&(idr)->idr_rt)
#घोषणा idr_lock_irqsave(idr, flags) \
				xa_lock_irqsave(&(idr)->idr_rt, flags)
#घोषणा idr_unlock_irqrestore(idr, flags) \
				xa_unlock_irqrestore(&(idr)->idr_rt, flags)

व्योम idr_preload(gfp_t gfp_mask);

पूर्णांक idr_alloc(काष्ठा idr *, व्योम *ptr, पूर्णांक start, पूर्णांक end, gfp_t);
पूर्णांक __must_check idr_alloc_u32(काष्ठा idr *, व्योम *ptr, u32 *id,
				अचिन्हित दीर्घ max, gfp_t);
पूर्णांक idr_alloc_cyclic(काष्ठा idr *, व्योम *ptr, पूर्णांक start, पूर्णांक end, gfp_t);
व्योम *idr_हटाओ(काष्ठा idr *, अचिन्हित दीर्घ id);
व्योम *idr_find(स्थिर काष्ठा idr *, अचिन्हित दीर्घ id);
पूर्णांक idr_क्रम_each(स्थिर काष्ठा idr *,
		 पूर्णांक (*fn)(पूर्णांक id, व्योम *p, व्योम *data), व्योम *data);
व्योम *idr_get_next(काष्ठा idr *, पूर्णांक *nextid);
व्योम *idr_get_next_ul(काष्ठा idr *, अचिन्हित दीर्घ *nextid);
व्योम *idr_replace(काष्ठा idr *, व्योम *, अचिन्हित दीर्घ id);
व्योम idr_destroy(काष्ठा idr *);

/**
 * idr_init_base() - Initialise an IDR.
 * @idr: IDR handle.
 * @base: The base value क्रम the IDR.
 *
 * This variation of idr_init() creates an IDR which will allocate IDs
 * starting at %base.
 */
अटल अंतरभूत व्योम idr_init_base(काष्ठा idr *idr, पूर्णांक base)
अणु
	INIT_RADIX_TREE(&idr->idr_rt, IDR_RT_MARKER);
	idr->idr_base = base;
	idr->idr_next = 0;
पूर्ण

/**
 * idr_init() - Initialise an IDR.
 * @idr: IDR handle.
 *
 * Initialise a dynamically allocated IDR.  To initialise a
 * अटलally allocated IDR, use DEFINE_IDR().
 */
अटल अंतरभूत व्योम idr_init(काष्ठा idr *idr)
अणु
	idr_init_base(idr, 0);
पूर्ण

/**
 * idr_is_empty() - Are there any IDs allocated?
 * @idr: IDR handle.
 *
 * Return: %true अगर any IDs have been allocated from this IDR.
 */
अटल अंतरभूत bool idr_is_empty(स्थिर काष्ठा idr *idr)
अणु
	वापस radix_tree_empty(&idr->idr_rt) &&
		radix_tree_tagged(&idr->idr_rt, IDR_FREE);
पूर्ण

/**
 * idr_preload_end - end preload section started with idr_preload()
 *
 * Each idr_preload() should be matched with an invocation of this
 * function.  See idr_preload() क्रम details.
 */
अटल अंतरभूत व्योम idr_preload_end(व्योम)
अणु
	local_unlock(&radix_tree_preloads.lock);
पूर्ण

/**
 * idr_क्रम_each_entry() - Iterate over an IDR's elements of a given type.
 * @idr: IDR handle.
 * @entry: The type * to use as cursor
 * @id: Entry ID.
 *
 * @entry and @id करो not need to be initialized beक्रमe the loop, and
 * after normal termination @entry is left with the value शून्य.  This
 * is convenient क्रम a "not found" value.
 */
#घोषणा idr_क्रम_each_entry(idr, entry, id)			\
	क्रम (id = 0; ((entry) = idr_get_next(idr, &(id))) != शून्य; id += 1U)

/**
 * idr_क्रम_each_entry_ul() - Iterate over an IDR's elements of a given type.
 * @idr: IDR handle.
 * @entry: The type * to use as cursor.
 * @पंचांगp: A temporary placeholder क्रम ID.
 * @id: Entry ID.
 *
 * @entry and @id करो not need to be initialized beक्रमe the loop, and
 * after normal termination @entry is left with the value शून्य.  This
 * is convenient क्रम a "not found" value.
 */
#घोषणा idr_क्रम_each_entry_ul(idr, entry, पंचांगp, id)			\
	क्रम (पंचांगp = 0, id = 0;						\
	     पंचांगp <= id && ((entry) = idr_get_next_ul(idr, &(id))) != शून्य; \
	     पंचांगp = id, ++id)

/**
 * idr_क्रम_each_entry_जारी() - Continue iteration over an IDR's elements of a given type
 * @idr: IDR handle.
 * @entry: The type * to use as a cursor.
 * @id: Entry ID.
 *
 * Continue to iterate over entries, continuing after the current position.
 */
#घोषणा idr_क्रम_each_entry_जारी(idr, entry, id)			\
	क्रम ((entry) = idr_get_next((idr), &(id));			\
	     entry;							\
	     ++id, (entry) = idr_get_next((idr), &(id)))

/**
 * idr_क्रम_each_entry_जारी_ul() - Continue iteration over an IDR's elements of a given type
 * @idr: IDR handle.
 * @entry: The type * to use as a cursor.
 * @पंचांगp: A temporary placeholder क्रम ID.
 * @id: Entry ID.
 *
 * Continue to iterate over entries, continuing after the current position.
 */
#घोषणा idr_क्रम_each_entry_जारी_ul(idr, entry, पंचांगp, id)		\
	क्रम (पंचांगp = id;							\
	     पंचांगp <= id && ((entry) = idr_get_next_ul(idr, &(id))) != शून्य; \
	     पंचांगp = id, ++id)

/*
 * IDA - ID Allocator, use when translation from id to poपूर्णांकer isn't necessary.
 */
#घोषणा IDA_CHUNK_SIZE		128	/* 128 bytes per chunk */
#घोषणा IDA_BITMAP_LONGS	(IDA_CHUNK_SIZE / माप(दीर्घ))
#घोषणा IDA_BITMAP_BITS 	(IDA_BITMAP_LONGS * माप(दीर्घ) * 8)

काष्ठा ida_biपंचांगap अणु
	अचिन्हित दीर्घ		biपंचांगap[IDA_BITMAP_LONGS];
पूर्ण;

काष्ठा ida अणु
	काष्ठा xarray xa;
पूर्ण;

#घोषणा IDA_INIT_FLAGS	(XA_FLAGS_LOCK_IRQ | XA_FLAGS_ALLOC)

#घोषणा IDA_INIT(name)	अणु						\
	.xa = XARRAY_INIT(name, IDA_INIT_FLAGS)				\
पूर्ण
#घोषणा DEFINE_IDA(name)	काष्ठा ida name = IDA_INIT(name)

पूर्णांक ida_alloc_range(काष्ठा ida *, अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max, gfp_t);
व्योम ida_मुक्त(काष्ठा ida *, अचिन्हित पूर्णांक id);
व्योम ida_destroy(काष्ठा ida *ida);

/**
 * ida_alloc() - Allocate an unused ID.
 * @ida: IDA handle.
 * @gfp: Memory allocation flags.
 *
 * Allocate an ID between 0 and %पूर्णांक_उच्च, inclusive.
 *
 * Context: Any context. It is safe to call this function without
 * locking in your code.
 * Return: The allocated ID, or %-ENOMEM अगर memory could not be allocated,
 * or %-ENOSPC अगर there are no मुक्त IDs.
 */
अटल अंतरभूत पूर्णांक ida_alloc(काष्ठा ida *ida, gfp_t gfp)
अणु
	वापस ida_alloc_range(ida, 0, ~0, gfp);
पूर्ण

/**
 * ida_alloc_min() - Allocate an unused ID.
 * @ida: IDA handle.
 * @min: Lowest ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Allocate an ID between @min and %पूर्णांक_उच्च, inclusive.
 *
 * Context: Any context. It is safe to call this function without
 * locking in your code.
 * Return: The allocated ID, or %-ENOMEM अगर memory could not be allocated,
 * or %-ENOSPC अगर there are no मुक्त IDs.
 */
अटल अंतरभूत पूर्णांक ida_alloc_min(काष्ठा ida *ida, अचिन्हित पूर्णांक min, gfp_t gfp)
अणु
	वापस ida_alloc_range(ida, min, ~0, gfp);
पूर्ण

/**
 * ida_alloc_max() - Allocate an unused ID.
 * @ida: IDA handle.
 * @max: Highest ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Allocate an ID between 0 and @max, inclusive.
 *
 * Context: Any context. It is safe to call this function without
 * locking in your code.
 * Return: The allocated ID, or %-ENOMEM अगर memory could not be allocated,
 * or %-ENOSPC अगर there are no मुक्त IDs.
 */
अटल अंतरभूत पूर्णांक ida_alloc_max(काष्ठा ida *ida, अचिन्हित पूर्णांक max, gfp_t gfp)
अणु
	वापस ida_alloc_range(ida, 0, max, gfp);
पूर्ण

अटल अंतरभूत व्योम ida_init(काष्ठा ida *ida)
अणु
	xa_init_flags(&ida->xa, IDA_INIT_FLAGS);
पूर्ण

/*
 * ida_simple_get() and ida_simple_हटाओ() are deprecated. Use
 * ida_alloc() and ida_मुक्त() instead respectively.
 */
#घोषणा ida_simple_get(ida, start, end, gfp)	\
			ida_alloc_range(ida, start, (end) - 1, gfp)
#घोषणा ida_simple_हटाओ(ida, id)	ida_मुक्त(ida, id)

अटल अंतरभूत bool ida_is_empty(स्थिर काष्ठा ida *ida)
अणु
	वापस xa_empty(&ida->xa);
पूर्ण
#पूर्ण_अगर /* __IDR_H__ */

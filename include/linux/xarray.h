<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित _LINUX_XARRAY_H
#घोषणा _LINUX_XARRAY_H
/*
 * eXtensible Arrays
 * Copyright (c) 2017 Microsoft Corporation
 * Author: Matthew Wilcox <willy@infradead.org>
 *
 * See Documentation/core-api/xarray.rst क्रम how to use the XArray.
 */

#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

/*
 * The bottom two bits of the entry determine how the XArray पूर्णांकerprets
 * the contents:
 *
 * 00: Poपूर्णांकer entry
 * 10: Internal entry
 * x1: Value entry or tagged poपूर्णांकer
 *
 * Attempting to store पूर्णांकernal entries in the XArray is a bug.
 *
 * Most पूर्णांकernal entries are poपूर्णांकers to the next node in the tree.
 * The following पूर्णांकernal entries have a special meaning:
 *
 * 0-62: Sibling entries
 * 256: Retry entry
 * 257: Zero entry
 *
 * Errors are also represented as पूर्णांकernal entries, but use the negative
 * space (-4094 to -2).  They're never stored in the slots array; only
 * वापसed by the normal API.
 */

#घोषणा BITS_PER_XA_VALUE	(BITS_PER_LONG - 1)

/**
 * xa_mk_value() - Create an XArray entry from an पूर्णांकeger.
 * @v: Value to store in XArray.
 *
 * Context: Any context.
 * Return: An entry suitable क्रम storing in the XArray.
 */
अटल अंतरभूत व्योम *xa_mk_value(अचिन्हित दीर्घ v)
अणु
	WARN_ON((दीर्घ)v < 0);
	वापस (व्योम *)((v << 1) | 1);
पूर्ण

/**
 * xa_to_value() - Get value stored in an XArray entry.
 * @entry: XArray entry.
 *
 * Context: Any context.
 * Return: The value stored in the XArray entry.
 */
अटल अंतरभूत अचिन्हित दीर्घ xa_to_value(स्थिर व्योम *entry)
अणु
	वापस (अचिन्हित दीर्घ)entry >> 1;
पूर्ण

/**
 * xa_is_value() - Determine अगर an entry is a value.
 * @entry: XArray entry.
 *
 * Context: Any context.
 * Return: True अगर the entry is a value, false अगर it is a poपूर्णांकer.
 */
अटल अंतरभूत bool xa_is_value(स्थिर व्योम *entry)
अणु
	वापस (अचिन्हित दीर्घ)entry & 1;
पूर्ण

/**
 * xa_tag_poपूर्णांकer() - Create an XArray entry क्रम a tagged poपूर्णांकer.
 * @p: Plain poपूर्णांकer.
 * @tag: Tag value (0, 1 or 3).
 *
 * If the user of the XArray prefers, they can tag their poपूर्णांकers instead
 * of storing value entries.  Three tags are available (0, 1 and 3).
 * These are distinct from the xa_mark_t as they are not replicated up
 * through the array and cannot be searched क्रम.
 *
 * Context: Any context.
 * Return: An XArray entry.
 */
अटल अंतरभूत व्योम *xa_tag_poपूर्णांकer(व्योम *p, अचिन्हित दीर्घ tag)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)p | tag);
पूर्ण

/**
 * xa_untag_poपूर्णांकer() - Turn an XArray entry पूर्णांकo a plain poपूर्णांकer.
 * @entry: XArray entry.
 *
 * If you have stored a tagged poपूर्णांकer in the XArray, call this function
 * to get the untagged version of the poपूर्णांकer.
 *
 * Context: Any context.
 * Return: A poपूर्णांकer.
 */
अटल अंतरभूत व्योम *xa_untag_poपूर्णांकer(व्योम *entry)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)entry & ~3UL);
पूर्ण

/**
 * xa_poपूर्णांकer_tag() - Get the tag stored in an XArray entry.
 * @entry: XArray entry.
 *
 * If you have stored a tagged poपूर्णांकer in the XArray, call this function
 * to get the tag of that poपूर्णांकer.
 *
 * Context: Any context.
 * Return: A tag.
 */
अटल अंतरभूत अचिन्हित पूर्णांक xa_poपूर्णांकer_tag(व्योम *entry)
अणु
	वापस (अचिन्हित दीर्घ)entry & 3UL;
पूर्ण

/*
 * xa_mk_पूर्णांकernal() - Create an पूर्णांकernal entry.
 * @v: Value to turn पूर्णांकo an पूर्णांकernal entry.
 *
 * Internal entries are used क्रम a number of purposes.  Entries 0-255 are
 * used क्रम sibling entries (only 0-62 are used by the current code).  256
 * is used क्रम the retry entry.  257 is used क्रम the reserved / zero entry.
 * Negative पूर्णांकernal entries are used to represent त्रुटि_संs.  Node poपूर्णांकers
 * are also tagged as पूर्णांकernal entries in some situations.
 *
 * Context: Any context.
 * Return: An XArray पूर्णांकernal entry corresponding to this value.
 */
अटल अंतरभूत व्योम *xa_mk_पूर्णांकernal(अचिन्हित दीर्घ v)
अणु
	वापस (व्योम *)((v << 2) | 2);
पूर्ण

/*
 * xa_to_पूर्णांकernal() - Extract the value from an पूर्णांकernal entry.
 * @entry: XArray entry.
 *
 * Context: Any context.
 * Return: The value which was stored in the पूर्णांकernal entry.
 */
अटल अंतरभूत अचिन्हित दीर्घ xa_to_पूर्णांकernal(स्थिर व्योम *entry)
अणु
	वापस (अचिन्हित दीर्घ)entry >> 2;
पूर्ण

/*
 * xa_is_पूर्णांकernal() - Is the entry an पूर्णांकernal entry?
 * @entry: XArray entry.
 *
 * Context: Any context.
 * Return: %true अगर the entry is an पूर्णांकernal entry.
 */
अटल अंतरभूत bool xa_is_पूर्णांकernal(स्थिर व्योम *entry)
अणु
	वापस ((अचिन्हित दीर्घ)entry & 3) == 2;
पूर्ण

#घोषणा XA_ZERO_ENTRY		xa_mk_पूर्णांकernal(257)

/**
 * xa_is_zero() - Is the entry a zero entry?
 * @entry: Entry retrieved from the XArray
 *
 * The normal API will वापस शून्य as the contents of a slot containing
 * a zero entry.  You can only see zero entries by using the advanced API.
 *
 * Return: %true अगर the entry is a zero entry.
 */
अटल अंतरभूत bool xa_is_zero(स्थिर व्योम *entry)
अणु
	वापस unlikely(entry == XA_ZERO_ENTRY);
पूर्ण

/**
 * xa_is_err() - Report whether an XArray operation वापसed an error
 * @entry: Result from calling an XArray function
 *
 * If an XArray operation cannot complete an operation, it will वापस
 * a special value indicating an error.  This function tells you
 * whether an error occurred; xa_err() tells you which error occurred.
 *
 * Context: Any context.
 * Return: %true अगर the entry indicates an error.
 */
अटल अंतरभूत bool xa_is_err(स्थिर व्योम *entry)
अणु
	वापस unlikely(xa_is_पूर्णांकernal(entry) &&
			entry >= xa_mk_पूर्णांकernal(-MAX_ERRNO));
पूर्ण

/**
 * xa_err() - Turn an XArray result पूर्णांकo an त्रुटि_सं.
 * @entry: Result from calling an XArray function.
 *
 * If an XArray operation cannot complete an operation, it will वापस
 * a special poपूर्णांकer value which encodes an त्रुटि_सं.  This function extracts
 * the त्रुटि_सं from the poपूर्णांकer value, or वापसs 0 अगर the poपूर्णांकer करोes not
 * represent an त्रुटि_सं.
 *
 * Context: Any context.
 * Return: A negative त्रुटि_सं or 0.
 */
अटल अंतरभूत पूर्णांक xa_err(व्योम *entry)
अणु
	/* xa_to_पूर्णांकernal() would not करो sign extension. */
	अगर (xa_is_err(entry))
		वापस (दीर्घ)entry >> 2;
	वापस 0;
पूर्ण

/**
 * काष्ठा xa_limit - Represents a range of IDs.
 * @min: The lowest ID to allocate (inclusive).
 * @max: The maximum ID to allocate (inclusive).
 *
 * This काष्ठाure is used either directly or via the XA_LIMIT() macro
 * to communicate the range of IDs that are valid क्रम allocation.
 * Three common ranges are predefined क्रम you:
 * * xa_limit_32b	- [0 - अच_पूर्णांक_उच्च]
 * * xa_limit_31b	- [0 - पूर्णांक_उच्च]
 * * xa_limit_16b	- [0 - अच_लघु_उच्च]
 */
काष्ठा xa_limit अणु
	u32 max;
	u32 min;
पूर्ण;

#घोषणा XA_LIMIT(_min, _max) (काष्ठा xa_limit) अणु .min = _min, .max = _max पूर्ण

#घोषणा xa_limit_32b	XA_LIMIT(0, अच_पूर्णांक_उच्च)
#घोषणा xa_limit_31b	XA_LIMIT(0, पूर्णांक_उच्च)
#घोषणा xa_limit_16b	XA_LIMIT(0, अच_लघु_उच्च)

प्रकार अचिन्हित __bitwise xa_mark_t;
#घोषणा XA_MARK_0		((__क्रमce xa_mark_t)0U)
#घोषणा XA_MARK_1		((__क्रमce xa_mark_t)1U)
#घोषणा XA_MARK_2		((__क्रमce xa_mark_t)2U)
#घोषणा XA_PRESENT		((__क्रमce xa_mark_t)8U)
#घोषणा XA_MARK_MAX		XA_MARK_2
#घोषणा XA_FREE_MARK		XA_MARK_0

क्रमागत xa_lock_type अणु
	XA_LOCK_IRQ = 1,
	XA_LOCK_BH = 2,
पूर्ण;

/*
 * Values क्रम xa_flags.  The radix tree stores its GFP flags in the xa_flags,
 * and we reमुख्य compatible with that.
 */
#घोषणा XA_FLAGS_LOCK_IRQ	((__क्रमce gfp_t)XA_LOCK_IRQ)
#घोषणा XA_FLAGS_LOCK_BH	((__क्रमce gfp_t)XA_LOCK_BH)
#घोषणा XA_FLAGS_TRACK_FREE	((__क्रमce gfp_t)4U)
#घोषणा XA_FLAGS_ZERO_BUSY	((__क्रमce gfp_t)8U)
#घोषणा XA_FLAGS_ALLOC_WRAPPED	((__क्रमce gfp_t)16U)
#घोषणा XA_FLAGS_ACCOUNT	((__क्रमce gfp_t)32U)
#घोषणा XA_FLAGS_MARK(mark)	((__क्रमce gfp_t)((1U << __GFP_BITS_SHIFT) << \
						(__क्रमce अचिन्हित)(mark)))

/* ALLOC is क्रम a normal 0-based alloc.  ALLOC1 is क्रम an 1-based alloc */
#घोषणा XA_FLAGS_ALLOC	(XA_FLAGS_TRACK_FREE | XA_FLAGS_MARK(XA_FREE_MARK))
#घोषणा XA_FLAGS_ALLOC1	(XA_FLAGS_TRACK_FREE | XA_FLAGS_ZERO_BUSY)

/**
 * काष्ठा xarray - The anchor of the XArray.
 * @xa_lock: Lock that protects the contents of the XArray.
 *
 * To use the xarray, define it अटलally or embed it in your data काष्ठाure.
 * It is a very small data काष्ठाure, so it करोes not usually make sense to
 * allocate it separately and keep a poपूर्णांकer to it in your data काष्ठाure.
 *
 * You may use the xa_lock to protect your own data काष्ठाures as well.
 */
/*
 * If all of the entries in the array are शून्य, @xa_head is a शून्य poपूर्णांकer.
 * If the only non-शून्य entry in the array is at index 0, @xa_head is that
 * entry.  If any other entry in the array is non-शून्य, @xa_head poपूर्णांकs
 * to an @xa_node.
 */
काष्ठा xarray अणु
	spinlock_t	xa_lock;
/* निजी: The rest of the data काष्ठाure is not to be used directly. */
	gfp_t		xa_flags;
	व्योम __rcu *	xa_head;
पूर्ण;

#घोषणा XARRAY_INIT(name, flags) अणु				\
	.xa_lock = __SPIN_LOCK_UNLOCKED(name.xa_lock),		\
	.xa_flags = flags,					\
	.xa_head = शून्य,					\
पूर्ण

/**
 * DEFINE_XARRAY_FLAGS() - Define an XArray with custom flags.
 * @name: A string that names your XArray.
 * @flags: XA_FLAG values.
 *
 * This is पूर्णांकended क्रम file scope definitions of XArrays.  It declares
 * and initialises an empty XArray with the chosen name and flags.  It is
 * equivalent to calling xa_init_flags() on the array, but it करोes the
 * initialisation at compileसमय instead of runसमय.
 */
#घोषणा DEFINE_XARRAY_FLAGS(name, flags)				\
	काष्ठा xarray name = XARRAY_INIT(name, flags)

/**
 * DEFINE_XARRAY() - Define an XArray.
 * @name: A string that names your XArray.
 *
 * This is पूर्णांकended क्रम file scope definitions of XArrays.  It declares
 * and initialises an empty XArray with the chosen name.  It is equivalent
 * to calling xa_init() on the array, but it करोes the initialisation at
 * compileसमय instead of runसमय.
 */
#घोषणा DEFINE_XARRAY(name) DEFINE_XARRAY_FLAGS(name, 0)

/**
 * DEFINE_XARRAY_ALLOC() - Define an XArray which allocates IDs starting at 0.
 * @name: A string that names your XArray.
 *
 * This is पूर्णांकended क्रम file scope definitions of allocating XArrays.
 * See also DEFINE_XARRAY().
 */
#घोषणा DEFINE_XARRAY_ALLOC(name) DEFINE_XARRAY_FLAGS(name, XA_FLAGS_ALLOC)

/**
 * DEFINE_XARRAY_ALLOC1() - Define an XArray which allocates IDs starting at 1.
 * @name: A string that names your XArray.
 *
 * This is पूर्णांकended क्रम file scope definitions of allocating XArrays.
 * See also DEFINE_XARRAY().
 */
#घोषणा DEFINE_XARRAY_ALLOC1(name) DEFINE_XARRAY_FLAGS(name, XA_FLAGS_ALLOC1)

व्योम *xa_load(काष्ठा xarray *, अचिन्हित दीर्घ index);
व्योम *xa_store(काष्ठा xarray *, अचिन्हित दीर्घ index, व्योम *entry, gfp_t);
व्योम *xa_erase(काष्ठा xarray *, अचिन्हित दीर्घ index);
व्योम *xa_store_range(काष्ठा xarray *, अचिन्हित दीर्घ first, अचिन्हित दीर्घ last,
			व्योम *entry, gfp_t);
bool xa_get_mark(काष्ठा xarray *, अचिन्हित दीर्घ index, xa_mark_t);
व्योम xa_set_mark(काष्ठा xarray *, अचिन्हित दीर्घ index, xa_mark_t);
व्योम xa_clear_mark(काष्ठा xarray *, अचिन्हित दीर्घ index, xa_mark_t);
व्योम *xa_find(काष्ठा xarray *xa, अचिन्हित दीर्घ *index,
		अचिन्हित दीर्घ max, xa_mark_t) __attribute__((nonnull(2)));
व्योम *xa_find_after(काष्ठा xarray *xa, अचिन्हित दीर्घ *index,
		अचिन्हित दीर्घ max, xa_mark_t) __attribute__((nonnull(2)));
अचिन्हित पूर्णांक xa_extract(काष्ठा xarray *, व्योम **dst, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ max, अचिन्हित पूर्णांक n, xa_mark_t);
व्योम xa_destroy(काष्ठा xarray *);

/**
 * xa_init_flags() - Initialise an empty XArray with flags.
 * @xa: XArray.
 * @flags: XA_FLAG values.
 *
 * If you need to initialise an XArray with special flags (eg you need
 * to take the lock from पूर्णांकerrupt context), use this function instead
 * of xa_init().
 *
 * Context: Any context.
 */
अटल अंतरभूत व्योम xa_init_flags(काष्ठा xarray *xa, gfp_t flags)
अणु
	spin_lock_init(&xa->xa_lock);
	xa->xa_flags = flags;
	xa->xa_head = शून्य;
पूर्ण

/**
 * xa_init() - Initialise an empty XArray.
 * @xa: XArray.
 *
 * An empty XArray is full of शून्य entries.
 *
 * Context: Any context.
 */
अटल अंतरभूत व्योम xa_init(काष्ठा xarray *xa)
अणु
	xa_init_flags(xa, 0);
पूर्ण

/**
 * xa_empty() - Determine अगर an array has any present entries.
 * @xa: XArray.
 *
 * Context: Any context.
 * Return: %true अगर the array contains only शून्य poपूर्णांकers.
 */
अटल अंतरभूत bool xa_empty(स्थिर काष्ठा xarray *xa)
अणु
	वापस xa->xa_head == शून्य;
पूर्ण

/**
 * xa_marked() - Inquire whether any entry in this array has a mark set
 * @xa: Array
 * @mark: Mark value
 *
 * Context: Any context.
 * Return: %true अगर any entry has this mark set.
 */
अटल अंतरभूत bool xa_marked(स्थिर काष्ठा xarray *xa, xa_mark_t mark)
अणु
	वापस xa->xa_flags & XA_FLAGS_MARK(mark);
पूर्ण

/**
 * xa_क्रम_each_range() - Iterate over a portion of an XArray.
 * @xa: XArray.
 * @index: Index of @entry.
 * @entry: Entry retrieved from array.
 * @start: First index to retrieve from array.
 * @last: Last index to retrieve from array.
 *
 * During the iteration, @entry will have the value of the entry stored
 * in @xa at @index.  You may modअगरy @index during the iteration अगर you
 * want to skip or reprocess indices.  It is safe to modअगरy the array
 * during the iteration.  At the end of the iteration, @entry will be set
 * to शून्य and @index will have a value less than or equal to max.
 *
 * xa_क्रम_each_range() is O(n.log(n)) जबतक xas_क्रम_each() is O(n).  You have
 * to handle your own locking with xas_क्रम_each(), and अगर you have to unlock
 * after each iteration, it will also end up being O(n.log(n)).
 * xa_क्रम_each_range() will spin अगर it hits a retry entry; अगर you पूर्णांकend to
 * see retry entries, you should use the xas_क्रम_each() iterator instead.
 * The xas_क्रम_each() iterator will expand पूर्णांकo more अंतरभूत code than
 * xa_क्रम_each_range().
 *
 * Context: Any context.  Takes and releases the RCU lock.
 */
#घोषणा xa_क्रम_each_range(xa, index, entry, start, last)		\
	क्रम (index = start,						\
	     entry = xa_find(xa, &index, last, XA_PRESENT);		\
	     entry;							\
	     entry = xa_find_after(xa, &index, last, XA_PRESENT))

/**
 * xa_क्रम_each_start() - Iterate over a portion of an XArray.
 * @xa: XArray.
 * @index: Index of @entry.
 * @entry: Entry retrieved from array.
 * @start: First index to retrieve from array.
 *
 * During the iteration, @entry will have the value of the entry stored
 * in @xa at @index.  You may modअगरy @index during the iteration अगर you
 * want to skip or reprocess indices.  It is safe to modअगरy the array
 * during the iteration.  At the end of the iteration, @entry will be set
 * to शून्य and @index will have a value less than or equal to max.
 *
 * xa_क्रम_each_start() is O(n.log(n)) जबतक xas_क्रम_each() is O(n).  You have
 * to handle your own locking with xas_क्रम_each(), and अगर you have to unlock
 * after each iteration, it will also end up being O(n.log(n)).
 * xa_क्रम_each_start() will spin अगर it hits a retry entry; अगर you पूर्णांकend to
 * see retry entries, you should use the xas_क्रम_each() iterator instead.
 * The xas_क्रम_each() iterator will expand पूर्णांकo more अंतरभूत code than
 * xa_क्रम_each_start().
 *
 * Context: Any context.  Takes and releases the RCU lock.
 */
#घोषणा xa_क्रम_each_start(xa, index, entry, start) \
	xa_क्रम_each_range(xa, index, entry, start, अच_दीर्घ_उच्च)

/**
 * xa_क्रम_each() - Iterate over present entries in an XArray.
 * @xa: XArray.
 * @index: Index of @entry.
 * @entry: Entry retrieved from array.
 *
 * During the iteration, @entry will have the value of the entry stored
 * in @xa at @index.  You may modअगरy @index during the iteration अगर you want
 * to skip or reprocess indices.  It is safe to modअगरy the array during the
 * iteration.  At the end of the iteration, @entry will be set to शून्य and
 * @index will have a value less than or equal to max.
 *
 * xa_क्रम_each() is O(n.log(n)) जबतक xas_क्रम_each() is O(n).  You have
 * to handle your own locking with xas_क्रम_each(), and अगर you have to unlock
 * after each iteration, it will also end up being O(n.log(n)).  xa_क्रम_each()
 * will spin अगर it hits a retry entry; अगर you पूर्णांकend to see retry entries,
 * you should use the xas_क्रम_each() iterator instead.  The xas_क्रम_each()
 * iterator will expand पूर्णांकo more अंतरभूत code than xa_क्रम_each().
 *
 * Context: Any context.  Takes and releases the RCU lock.
 */
#घोषणा xa_क्रम_each(xa, index, entry) \
	xa_क्रम_each_start(xa, index, entry, 0)

/**
 * xa_क्रम_each_marked() - Iterate over marked entries in an XArray.
 * @xa: XArray.
 * @index: Index of @entry.
 * @entry: Entry retrieved from array.
 * @filter: Selection criterion.
 *
 * During the iteration, @entry will have the value of the entry stored
 * in @xa at @index.  The iteration will skip all entries in the array
 * which करो not match @filter.  You may modअगरy @index during the iteration
 * अगर you want to skip or reprocess indices.  It is safe to modअगरy the array
 * during the iteration.  At the end of the iteration, @entry will be set to
 * शून्य and @index will have a value less than or equal to max.
 *
 * xa_क्रम_each_marked() is O(n.log(n)) जबतक xas_क्रम_each_marked() is O(n).
 * You have to handle your own locking with xas_क्रम_each(), and अगर you have
 * to unlock after each iteration, it will also end up being O(n.log(n)).
 * xa_क्रम_each_marked() will spin अगर it hits a retry entry; अगर you पूर्णांकend to
 * see retry entries, you should use the xas_क्रम_each_marked() iterator
 * instead.  The xas_क्रम_each_marked() iterator will expand पूर्णांकo more अंतरभूत
 * code than xa_क्रम_each_marked().
 *
 * Context: Any context.  Takes and releases the RCU lock.
 */
#घोषणा xa_क्रम_each_marked(xa, index, entry, filter) \
	क्रम (index = 0, entry = xa_find(xa, &index, अच_दीर्घ_उच्च, filter); \
	     entry; entry = xa_find_after(xa, &index, अच_दीर्घ_उच्च, filter))

#घोषणा xa_trylock(xa)		spin_trylock(&(xa)->xa_lock)
#घोषणा xa_lock(xa)		spin_lock(&(xa)->xa_lock)
#घोषणा xa_unlock(xa)		spin_unlock(&(xa)->xa_lock)
#घोषणा xa_lock_bh(xa)		spin_lock_bh(&(xa)->xa_lock)
#घोषणा xa_unlock_bh(xa)	spin_unlock_bh(&(xa)->xa_lock)
#घोषणा xa_lock_irq(xa)		spin_lock_irq(&(xa)->xa_lock)
#घोषणा xa_unlock_irq(xa)	spin_unlock_irq(&(xa)->xa_lock)
#घोषणा xa_lock_irqsave(xa, flags) \
				spin_lock_irqsave(&(xa)->xa_lock, flags)
#घोषणा xa_unlock_irqrestore(xa, flags) \
				spin_unlock_irqrestore(&(xa)->xa_lock, flags)
#घोषणा xa_lock_nested(xa, subclass) \
				spin_lock_nested(&(xa)->xa_lock, subclass)
#घोषणा xa_lock_bh_nested(xa, subclass) \
				spin_lock_bh_nested(&(xa)->xa_lock, subclass)
#घोषणा xa_lock_irq_nested(xa, subclass) \
				spin_lock_irq_nested(&(xa)->xa_lock, subclass)
#घोषणा xa_lock_irqsave_nested(xa, flags, subclass) \
		spin_lock_irqsave_nested(&(xa)->xa_lock, flags, subclass)

/*
 * Versions of the normal API which require the caller to hold the
 * xa_lock.  If the GFP flags allow it, they will drop the lock to
 * allocate memory, then reacquire it afterwards.  These functions
 * may also re-enable पूर्णांकerrupts अगर the XArray flags indicate the
 * locking should be पूर्णांकerrupt safe.
 */
व्योम *__xa_erase(काष्ठा xarray *, अचिन्हित दीर्घ index);
व्योम *__xa_store(काष्ठा xarray *, अचिन्हित दीर्घ index, व्योम *entry, gfp_t);
व्योम *__xa_cmpxchg(काष्ठा xarray *, अचिन्हित दीर्घ index, व्योम *old,
		व्योम *entry, gfp_t);
पूर्णांक __must_check __xa_insert(काष्ठा xarray *, अचिन्हित दीर्घ index,
		व्योम *entry, gfp_t);
पूर्णांक __must_check __xa_alloc(काष्ठा xarray *, u32 *id, व्योम *entry,
		काष्ठा xa_limit, gfp_t);
पूर्णांक __must_check __xa_alloc_cyclic(काष्ठा xarray *, u32 *id, व्योम *entry,
		काष्ठा xa_limit, u32 *next, gfp_t);
व्योम __xa_set_mark(काष्ठा xarray *, अचिन्हित दीर्घ index, xa_mark_t);
व्योम __xa_clear_mark(काष्ठा xarray *, अचिन्हित दीर्घ index, xa_mark_t);

/**
 * xa_store_bh() - Store this entry in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * This function is like calling xa_store() except it disables softirqs
 * जबतक holding the array lock.
 *
 * Context: Any context.  Takes and releases the xa_lock जबतक
 * disabling softirqs.
 * Return: The old entry at this index or xa_err() अगर an error happened.
 */
अटल अंतरभूत व्योम *xa_store_bh(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
		व्योम *entry, gfp_t gfp)
अणु
	व्योम *curr;

	xa_lock_bh(xa);
	curr = __xa_store(xa, index, entry, gfp);
	xa_unlock_bh(xa);

	वापस curr;
पूर्ण

/**
 * xa_store_irq() - Store this entry in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * This function is like calling xa_store() except it disables पूर्णांकerrupts
 * जबतक holding the array lock.
 *
 * Context: Process context.  Takes and releases the xa_lock जबतक
 * disabling पूर्णांकerrupts.
 * Return: The old entry at this index or xa_err() अगर an error happened.
 */
अटल अंतरभूत व्योम *xa_store_irq(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
		व्योम *entry, gfp_t gfp)
अणु
	व्योम *curr;

	xa_lock_irq(xa);
	curr = __xa_store(xa, index, entry, gfp);
	xa_unlock_irq(xa);

	वापस curr;
पूर्ण

/**
 * xa_erase_bh() - Erase this entry from the XArray.
 * @xa: XArray.
 * @index: Index of entry.
 *
 * After this function वापसs, loading from @index will वापस %शून्य.
 * If the index is part of a multi-index entry, all indices will be erased
 * and none of the entries will be part of a multi-index entry.
 *
 * Context: Any context.  Takes and releases the xa_lock जबतक
 * disabling softirqs.
 * Return: The entry which used to be at this index.
 */
अटल अंतरभूत व्योम *xa_erase_bh(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	व्योम *entry;

	xa_lock_bh(xa);
	entry = __xa_erase(xa, index);
	xa_unlock_bh(xa);

	वापस entry;
पूर्ण

/**
 * xa_erase_irq() - Erase this entry from the XArray.
 * @xa: XArray.
 * @index: Index of entry.
 *
 * After this function वापसs, loading from @index will वापस %शून्य.
 * If the index is part of a multi-index entry, all indices will be erased
 * and none of the entries will be part of a multi-index entry.
 *
 * Context: Process context.  Takes and releases the xa_lock जबतक
 * disabling पूर्णांकerrupts.
 * Return: The entry which used to be at this index.
 */
अटल अंतरभूत व्योम *xa_erase_irq(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	व्योम *entry;

	xa_lock_irq(xa);
	entry = __xa_erase(xa, index);
	xa_unlock_irq(xa);

	वापस entry;
पूर्ण

/**
 * xa_cmpxchg() - Conditionally replace an entry in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @old: Old value to test against.
 * @entry: New value to place in array.
 * @gfp: Memory allocation flags.
 *
 * If the entry at @index is the same as @old, replace it with @entry.
 * If the वापस value is equal to @old, then the exchange was successful.
 *
 * Context: Any context.  Takes and releases the xa_lock.  May sleep
 * अगर the @gfp flags permit.
 * Return: The old value at this index or xa_err() अगर an error happened.
 */
अटल अंतरभूत व्योम *xa_cmpxchg(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
			व्योम *old, व्योम *entry, gfp_t gfp)
अणु
	व्योम *curr;

	xa_lock(xa);
	curr = __xa_cmpxchg(xa, index, old, entry, gfp);
	xa_unlock(xa);

	वापस curr;
पूर्ण

/**
 * xa_cmpxchg_bh() - Conditionally replace an entry in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @old: Old value to test against.
 * @entry: New value to place in array.
 * @gfp: Memory allocation flags.
 *
 * This function is like calling xa_cmpxchg() except it disables softirqs
 * जबतक holding the array lock.
 *
 * Context: Any context.  Takes and releases the xa_lock जबतक
 * disabling softirqs.  May sleep अगर the @gfp flags permit.
 * Return: The old value at this index or xa_err() अगर an error happened.
 */
अटल अंतरभूत व्योम *xa_cmpxchg_bh(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
			व्योम *old, व्योम *entry, gfp_t gfp)
अणु
	व्योम *curr;

	xa_lock_bh(xa);
	curr = __xa_cmpxchg(xa, index, old, entry, gfp);
	xa_unlock_bh(xa);

	वापस curr;
पूर्ण

/**
 * xa_cmpxchg_irq() - Conditionally replace an entry in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @old: Old value to test against.
 * @entry: New value to place in array.
 * @gfp: Memory allocation flags.
 *
 * This function is like calling xa_cmpxchg() except it disables पूर्णांकerrupts
 * जबतक holding the array lock.
 *
 * Context: Process context.  Takes and releases the xa_lock जबतक
 * disabling पूर्णांकerrupts.  May sleep अगर the @gfp flags permit.
 * Return: The old value at this index or xa_err() अगर an error happened.
 */
अटल अंतरभूत व्योम *xa_cmpxchg_irq(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
			व्योम *old, व्योम *entry, gfp_t gfp)
अणु
	व्योम *curr;

	xa_lock_irq(xa);
	curr = __xa_cmpxchg(xa, index, old, entry, gfp);
	xa_unlock_irq(xa);

	वापस curr;
पूर्ण

/**
 * xa_insert() - Store this entry in the XArray unless another entry is
 *			alपढ़ोy present.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * Inserting a शून्य entry will store a reserved entry (like xa_reserve())
 * अगर no entry is present.  Inserting will fail अगर a reserved entry is
 * present, even though loading from this index will वापस शून्य.
 *
 * Context: Any context.  Takes and releases the xa_lock.  May sleep अगर
 * the @gfp flags permit.
 * Return: 0 अगर the store succeeded.  -EBUSY अगर another entry was present.
 * -ENOMEM अगर memory could not be allocated.
 */
अटल अंतरभूत पूर्णांक __must_check xa_insert(काष्ठा xarray *xa,
		अचिन्हित दीर्घ index, व्योम *entry, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock(xa);
	err = __xa_insert(xa, index, entry, gfp);
	xa_unlock(xa);

	वापस err;
पूर्ण

/**
 * xa_insert_bh() - Store this entry in the XArray unless another entry is
 *			alपढ़ोy present.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * Inserting a शून्य entry will store a reserved entry (like xa_reserve())
 * अगर no entry is present.  Inserting will fail अगर a reserved entry is
 * present, even though loading from this index will वापस शून्य.
 *
 * Context: Any context.  Takes and releases the xa_lock जबतक
 * disabling softirqs.  May sleep अगर the @gfp flags permit.
 * Return: 0 अगर the store succeeded.  -EBUSY अगर another entry was present.
 * -ENOMEM अगर memory could not be allocated.
 */
अटल अंतरभूत पूर्णांक __must_check xa_insert_bh(काष्ठा xarray *xa,
		अचिन्हित दीर्घ index, व्योम *entry, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock_bh(xa);
	err = __xa_insert(xa, index, entry, gfp);
	xa_unlock_bh(xa);

	वापस err;
पूर्ण

/**
 * xa_insert_irq() - Store this entry in the XArray unless another entry is
 *			alपढ़ोy present.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * Inserting a शून्य entry will store a reserved entry (like xa_reserve())
 * अगर no entry is present.  Inserting will fail अगर a reserved entry is
 * present, even though loading from this index will वापस शून्य.
 *
 * Context: Process context.  Takes and releases the xa_lock जबतक
 * disabling पूर्णांकerrupts.  May sleep अगर the @gfp flags permit.
 * Return: 0 अगर the store succeeded.  -EBUSY अगर another entry was present.
 * -ENOMEM अगर memory could not be allocated.
 */
अटल अंतरभूत पूर्णांक __must_check xa_insert_irq(काष्ठा xarray *xa,
		अचिन्हित दीर्घ index, व्योम *entry, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock_irq(xa);
	err = __xa_insert(xa, index, entry, gfp);
	xa_unlock_irq(xa);

	वापस err;
पूर्ण

/**
 * xa_alloc() - Find somewhere to store this entry in the XArray.
 * @xa: XArray.
 * @id: Poपूर्णांकer to ID.
 * @entry: New entry.
 * @limit: Range of ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Finds an empty entry in @xa between @limit.min and @limit.max,
 * stores the index पूर्णांकo the @id poपूर्णांकer, then stores the entry at
 * that index.  A concurrent lookup will not see an uninitialised @id.
 *
 * Context: Any context.  Takes and releases the xa_lock.  May sleep अगर
 * the @gfp flags permit.
 * Return: 0 on success, -ENOMEM अगर memory could not be allocated or
 * -EBUSY अगर there are no मुक्त entries in @limit.
 */
अटल अंतरभूत __must_check पूर्णांक xa_alloc(काष्ठा xarray *xa, u32 *id,
		व्योम *entry, काष्ठा xa_limit limit, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock(xa);
	err = __xa_alloc(xa, id, entry, limit, gfp);
	xa_unlock(xa);

	वापस err;
पूर्ण

/**
 * xa_alloc_bh() - Find somewhere to store this entry in the XArray.
 * @xa: XArray.
 * @id: Poपूर्णांकer to ID.
 * @entry: New entry.
 * @limit: Range of ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Finds an empty entry in @xa between @limit.min and @limit.max,
 * stores the index पूर्णांकo the @id poपूर्णांकer, then stores the entry at
 * that index.  A concurrent lookup will not see an uninitialised @id.
 *
 * Context: Any context.  Takes and releases the xa_lock जबतक
 * disabling softirqs.  May sleep अगर the @gfp flags permit.
 * Return: 0 on success, -ENOMEM अगर memory could not be allocated or
 * -EBUSY अगर there are no मुक्त entries in @limit.
 */
अटल अंतरभूत पूर्णांक __must_check xa_alloc_bh(काष्ठा xarray *xa, u32 *id,
		व्योम *entry, काष्ठा xa_limit limit, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock_bh(xa);
	err = __xa_alloc(xa, id, entry, limit, gfp);
	xa_unlock_bh(xa);

	वापस err;
पूर्ण

/**
 * xa_alloc_irq() - Find somewhere to store this entry in the XArray.
 * @xa: XArray.
 * @id: Poपूर्णांकer to ID.
 * @entry: New entry.
 * @limit: Range of ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Finds an empty entry in @xa between @limit.min and @limit.max,
 * stores the index पूर्णांकo the @id poपूर्णांकer, then stores the entry at
 * that index.  A concurrent lookup will not see an uninitialised @id.
 *
 * Context: Process context.  Takes and releases the xa_lock जबतक
 * disabling पूर्णांकerrupts.  May sleep अगर the @gfp flags permit.
 * Return: 0 on success, -ENOMEM अगर memory could not be allocated or
 * -EBUSY अगर there are no मुक्त entries in @limit.
 */
अटल अंतरभूत पूर्णांक __must_check xa_alloc_irq(काष्ठा xarray *xa, u32 *id,
		व्योम *entry, काष्ठा xa_limit limit, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock_irq(xa);
	err = __xa_alloc(xa, id, entry, limit, gfp);
	xa_unlock_irq(xa);

	वापस err;
पूर्ण

/**
 * xa_alloc_cyclic() - Find somewhere to store this entry in the XArray.
 * @xa: XArray.
 * @id: Poपूर्णांकer to ID.
 * @entry: New entry.
 * @limit: Range of allocated ID.
 * @next: Poपूर्णांकer to next ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Finds an empty entry in @xa between @limit.min and @limit.max,
 * stores the index पूर्णांकo the @id poपूर्णांकer, then stores the entry at
 * that index.  A concurrent lookup will not see an uninitialised @id.
 * The search क्रम an empty entry will start at @next and will wrap
 * around अगर necessary.
 *
 * Context: Any context.  Takes and releases the xa_lock.  May sleep अगर
 * the @gfp flags permit.
 * Return: 0 अगर the allocation succeeded without wrapping.  1 अगर the
 * allocation succeeded after wrapping, -ENOMEM अगर memory could not be
 * allocated or -EBUSY अगर there are no मुक्त entries in @limit.
 */
अटल अंतरभूत पूर्णांक xa_alloc_cyclic(काष्ठा xarray *xa, u32 *id, व्योम *entry,
		काष्ठा xa_limit limit, u32 *next, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock(xa);
	err = __xa_alloc_cyclic(xa, id, entry, limit, next, gfp);
	xa_unlock(xa);

	वापस err;
पूर्ण

/**
 * xa_alloc_cyclic_bh() - Find somewhere to store this entry in the XArray.
 * @xa: XArray.
 * @id: Poपूर्णांकer to ID.
 * @entry: New entry.
 * @limit: Range of allocated ID.
 * @next: Poपूर्णांकer to next ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Finds an empty entry in @xa between @limit.min and @limit.max,
 * stores the index पूर्णांकo the @id poपूर्णांकer, then stores the entry at
 * that index.  A concurrent lookup will not see an uninitialised @id.
 * The search क्रम an empty entry will start at @next and will wrap
 * around अगर necessary.
 *
 * Context: Any context.  Takes and releases the xa_lock जबतक
 * disabling softirqs.  May sleep अगर the @gfp flags permit.
 * Return: 0 अगर the allocation succeeded without wrapping.  1 अगर the
 * allocation succeeded after wrapping, -ENOMEM अगर memory could not be
 * allocated or -EBUSY अगर there are no मुक्त entries in @limit.
 */
अटल अंतरभूत पूर्णांक xa_alloc_cyclic_bh(काष्ठा xarray *xa, u32 *id, व्योम *entry,
		काष्ठा xa_limit limit, u32 *next, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock_bh(xa);
	err = __xa_alloc_cyclic(xa, id, entry, limit, next, gfp);
	xa_unlock_bh(xa);

	वापस err;
पूर्ण

/**
 * xa_alloc_cyclic_irq() - Find somewhere to store this entry in the XArray.
 * @xa: XArray.
 * @id: Poपूर्णांकer to ID.
 * @entry: New entry.
 * @limit: Range of allocated ID.
 * @next: Poपूर्णांकer to next ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Finds an empty entry in @xa between @limit.min and @limit.max,
 * stores the index पूर्णांकo the @id poपूर्णांकer, then stores the entry at
 * that index.  A concurrent lookup will not see an uninitialised @id.
 * The search क्रम an empty entry will start at @next and will wrap
 * around अगर necessary.
 *
 * Context: Process context.  Takes and releases the xa_lock जबतक
 * disabling पूर्णांकerrupts.  May sleep अगर the @gfp flags permit.
 * Return: 0 अगर the allocation succeeded without wrapping.  1 अगर the
 * allocation succeeded after wrapping, -ENOMEM अगर memory could not be
 * allocated or -EBUSY अगर there are no मुक्त entries in @limit.
 */
अटल अंतरभूत पूर्णांक xa_alloc_cyclic_irq(काष्ठा xarray *xa, u32 *id, व्योम *entry,
		काष्ठा xa_limit limit, u32 *next, gfp_t gfp)
अणु
	पूर्णांक err;

	xa_lock_irq(xa);
	err = __xa_alloc_cyclic(xa, id, entry, limit, next, gfp);
	xa_unlock_irq(xa);

	वापस err;
पूर्ण

/**
 * xa_reserve() - Reserve this index in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @gfp: Memory allocation flags.
 *
 * Ensures there is somewhere to store an entry at @index in the array.
 * If there is alपढ़ोy something stored at @index, this function करोes
 * nothing.  If there was nothing there, the entry is marked as reserved.
 * Loading from a reserved entry वापसs a %शून्य poपूर्णांकer.
 *
 * If you करो not use the entry that you have reserved, call xa_release()
 * or xa_erase() to मुक्त any unnecessary memory.
 *
 * Context: Any context.  Takes and releases the xa_lock.
 * May sleep अगर the @gfp flags permit.
 * Return: 0 अगर the reservation succeeded or -ENOMEM अगर it failed.
 */
अटल अंतरभूत __must_check
पूर्णांक xa_reserve(काष्ठा xarray *xa, अचिन्हित दीर्घ index, gfp_t gfp)
अणु
	वापस xa_err(xa_cmpxchg(xa, index, शून्य, XA_ZERO_ENTRY, gfp));
पूर्ण

/**
 * xa_reserve_bh() - Reserve this index in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @gfp: Memory allocation flags.
 *
 * A softirq-disabling version of xa_reserve().
 *
 * Context: Any context.  Takes and releases the xa_lock जबतक
 * disabling softirqs.
 * Return: 0 अगर the reservation succeeded or -ENOMEM अगर it failed.
 */
अटल अंतरभूत __must_check
पूर्णांक xa_reserve_bh(काष्ठा xarray *xa, अचिन्हित दीर्घ index, gfp_t gfp)
अणु
	वापस xa_err(xa_cmpxchg_bh(xa, index, शून्य, XA_ZERO_ENTRY, gfp));
पूर्ण

/**
 * xa_reserve_irq() - Reserve this index in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @gfp: Memory allocation flags.
 *
 * An पूर्णांकerrupt-disabling version of xa_reserve().
 *
 * Context: Process context.  Takes and releases the xa_lock जबतक
 * disabling पूर्णांकerrupts.
 * Return: 0 अगर the reservation succeeded or -ENOMEM अगर it failed.
 */
अटल अंतरभूत __must_check
पूर्णांक xa_reserve_irq(काष्ठा xarray *xa, अचिन्हित दीर्घ index, gfp_t gfp)
अणु
	वापस xa_err(xa_cmpxchg_irq(xa, index, शून्य, XA_ZERO_ENTRY, gfp));
पूर्ण

/**
 * xa_release() - Release a reserved entry.
 * @xa: XArray.
 * @index: Index of entry.
 *
 * After calling xa_reserve(), you can call this function to release the
 * reservation.  If the entry at @index has been stored to, this function
 * will करो nothing.
 */
अटल अंतरभूत व्योम xa_release(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	xa_cmpxchg(xa, index, XA_ZERO_ENTRY, शून्य, 0);
पूर्ण

/* Everything below here is the Advanced API.  Proceed with caution. */

/*
 * The xarray is स्थिरructed out of a set of 'chunks' of poपूर्णांकers.  Choosing
 * the best chunk size requires some tradeoffs.  A घातer of two recommends
 * itself so that we can walk the tree based purely on shअगरts and masks.
 * Generally, the larger the better; as the number of slots per level of the
 * tree increases, the less tall the tree needs to be.  But that needs to be
 * balanced against the memory consumption of each node.  On a 64-bit प्रणाली,
 * xa_node is currently 576 bytes, and we get 7 of them per 4kB page.  If we
 * द्विगुनd the number of slots per node, we'd get only 3 nodes per 4kB page.
 */
#अगर_अघोषित XA_CHUNK_SHIFT
#घोषणा XA_CHUNK_SHIFT		(CONFIG_BASE_SMALL ? 4 : 6)
#पूर्ण_अगर
#घोषणा XA_CHUNK_SIZE		(1UL << XA_CHUNK_SHIFT)
#घोषणा XA_CHUNK_MASK		(XA_CHUNK_SIZE - 1)
#घोषणा XA_MAX_MARKS		3
#घोषणा XA_MARK_LONGS		DIV_ROUND_UP(XA_CHUNK_SIZE, BITS_PER_LONG)

/*
 * @count is the count of every non-शून्य element in the ->slots array
 * whether that is a value entry, a retry entry, a user poपूर्णांकer,
 * a sibling entry or a poपूर्णांकer to the next level of the tree.
 * @nr_values is the count of every element in ->slots which is
 * either a value entry or a sibling of a value entry.
 */
काष्ठा xa_node अणु
	अचिन्हित अक्षर	shअगरt;		/* Bits reमुख्यing in each slot */
	अचिन्हित अक्षर	offset;		/* Slot offset in parent */
	अचिन्हित अक्षर	count;		/* Total entry count */
	अचिन्हित अक्षर	nr_values;	/* Value entry count */
	काष्ठा xa_node __rcu *parent;	/* शून्य at top of tree */
	काष्ठा xarray	*array;		/* The array we beदीर्घ to */
	जोड़ अणु
		काष्ठा list_head निजी_list;	/* For tree user */
		काष्ठा rcu_head	rcu_head;	/* Used when मुक्तing node */
	पूर्ण;
	व्योम __rcu	*slots[XA_CHUNK_SIZE];
	जोड़ अणु
		अचिन्हित दीर्घ	tags[XA_MAX_MARKS][XA_MARK_LONGS];
		अचिन्हित दीर्घ	marks[XA_MAX_MARKS][XA_MARK_LONGS];
	पूर्ण;
पूर्ण;

व्योम xa_dump(स्थिर काष्ठा xarray *);
व्योम xa_dump_node(स्थिर काष्ठा xa_node *);

#अगर_घोषित XA_DEBUG
#घोषणा XA_BUG_ON(xa, x) करो अणु					\
		अगर (x) अणु					\
			xa_dump(xa);				\
			BUG();					\
		पूर्ण						\
	पूर्ण जबतक (0)
#घोषणा XA_NODE_BUG_ON(node, x) करो अणु				\
		अगर (x) अणु					\
			अगर (node) xa_dump_node(node);		\
			BUG();					\
		पूर्ण						\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा XA_BUG_ON(xa, x)	करो अणु पूर्ण जबतक (0)
#घोषणा XA_NODE_BUG_ON(node, x)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* Private */
अटल अंतरभूत व्योम *xa_head(स्थिर काष्ठा xarray *xa)
अणु
	वापस rcu_dereference_check(xa->xa_head,
						lockdep_is_held(&xa->xa_lock));
पूर्ण

/* Private */
अटल अंतरभूत व्योम *xa_head_locked(स्थिर काष्ठा xarray *xa)
अणु
	वापस rcu_dereference_रक्षित(xa->xa_head,
						lockdep_is_held(&xa->xa_lock));
पूर्ण

/* Private */
अटल अंतरभूत व्योम *xa_entry(स्थिर काष्ठा xarray *xa,
				स्थिर काष्ठा xa_node *node, अचिन्हित पूर्णांक offset)
अणु
	XA_NODE_BUG_ON(node, offset >= XA_CHUNK_SIZE);
	वापस rcu_dereference_check(node->slots[offset],
						lockdep_is_held(&xa->xa_lock));
पूर्ण

/* Private */
अटल अंतरभूत व्योम *xa_entry_locked(स्थिर काष्ठा xarray *xa,
				स्थिर काष्ठा xa_node *node, अचिन्हित पूर्णांक offset)
अणु
	XA_NODE_BUG_ON(node, offset >= XA_CHUNK_SIZE);
	वापस rcu_dereference_रक्षित(node->slots[offset],
						lockdep_is_held(&xa->xa_lock));
पूर्ण

/* Private */
अटल अंतरभूत काष्ठा xa_node *xa_parent(स्थिर काष्ठा xarray *xa,
					स्थिर काष्ठा xa_node *node)
अणु
	वापस rcu_dereference_check(node->parent,
						lockdep_is_held(&xa->xa_lock));
पूर्ण

/* Private */
अटल अंतरभूत काष्ठा xa_node *xa_parent_locked(स्थिर काष्ठा xarray *xa,
					स्थिर काष्ठा xa_node *node)
अणु
	वापस rcu_dereference_रक्षित(node->parent,
						lockdep_is_held(&xa->xa_lock));
पूर्ण

/* Private */
अटल अंतरभूत व्योम *xa_mk_node(स्थिर काष्ठा xa_node *node)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)node | 2);
पूर्ण

/* Private */
अटल अंतरभूत काष्ठा xa_node *xa_to_node(स्थिर व्योम *entry)
अणु
	वापस (काष्ठा xa_node *)((अचिन्हित दीर्घ)entry - 2);
पूर्ण

/* Private */
अटल अंतरभूत bool xa_is_node(स्थिर व्योम *entry)
अणु
	वापस xa_is_पूर्णांकernal(entry) && (अचिन्हित दीर्घ)entry > 4096;
पूर्ण

/* Private */
अटल अंतरभूत व्योम *xa_mk_sibling(अचिन्हित पूर्णांक offset)
अणु
	वापस xa_mk_पूर्णांकernal(offset);
पूर्ण

/* Private */
अटल अंतरभूत अचिन्हित दीर्घ xa_to_sibling(स्थिर व्योम *entry)
अणु
	वापस xa_to_पूर्णांकernal(entry);
पूर्ण

/**
 * xa_is_sibling() - Is the entry a sibling entry?
 * @entry: Entry retrieved from the XArray
 *
 * Return: %true अगर the entry is a sibling entry.
 */
अटल अंतरभूत bool xa_is_sibling(स्थिर व्योम *entry)
अणु
	वापस IS_ENABLED(CONFIG_XARRAY_MULTI) && xa_is_पूर्णांकernal(entry) &&
		(entry < xa_mk_sibling(XA_CHUNK_SIZE - 1));
पूर्ण

#घोषणा XA_RETRY_ENTRY		xa_mk_पूर्णांकernal(256)

/**
 * xa_is_retry() - Is the entry a retry entry?
 * @entry: Entry retrieved from the XArray
 *
 * Return: %true अगर the entry is a retry entry.
 */
अटल अंतरभूत bool xa_is_retry(स्थिर व्योम *entry)
अणु
	वापस unlikely(entry == XA_RETRY_ENTRY);
पूर्ण

/**
 * xa_is_advanced() - Is the entry only permitted क्रम the advanced API?
 * @entry: Entry to be stored in the XArray.
 *
 * Return: %true अगर the entry cannot be stored by the normal API.
 */
अटल अंतरभूत bool xa_is_advanced(स्थिर व्योम *entry)
अणु
	वापस xa_is_पूर्णांकernal(entry) && (entry <= XA_RETRY_ENTRY);
पूर्ण

/**
 * प्रकार xa_update_node_t - A callback function from the XArray.
 * @node: The node which is being processed
 *
 * This function is called every समय the XArray updates the count of
 * present and value entries in a node.  It allows advanced users to
 * मुख्यtain the निजी_list in the node.
 *
 * Context: The xa_lock is held and पूर्णांकerrupts may be disabled.
 *	    Implementations should not drop the xa_lock, nor re-enable
 *	    पूर्णांकerrupts.
 */
प्रकार व्योम (*xa_update_node_t)(काष्ठा xa_node *node);

व्योम xa_delete_node(काष्ठा xa_node *, xa_update_node_t);

/*
 * The xa_state is opaque to its users.  It contains various dअगरferent pieces
 * of state involved in the current operation on the XArray.  It should be
 * declared on the stack and passed between the various पूर्णांकernal routines.
 * The various elements in it should not be accessed directly, but only
 * through the provided accessor functions.  The below करोcumentation is क्रम
 * the benefit of those working on the code, not क्रम users of the XArray.
 *
 * @xa_node usually poपूर्णांकs to the xa_node containing the slot we're operating
 * on (and @xa_offset is the offset in the slots array).  If there is a
 * single entry in the array at index 0, there are no allocated xa_nodes to
 * poपूर्णांक to, and so we store %शून्य in @xa_node.  @xa_node is set to
 * the value %XAS_RESTART अगर the xa_state is not walked to the correct
 * position in the tree of nodes क्रम this operation.  If an error occurs
 * during an operation, it is set to an %XAS_ERROR value.  If we run off the
 * end of the allocated nodes, it is set to %XAS_BOUNDS.
 */
काष्ठा xa_state अणु
	काष्ठा xarray *xa;
	अचिन्हित दीर्घ xa_index;
	अचिन्हित अक्षर xa_shअगरt;
	अचिन्हित अक्षर xa_sibs;
	अचिन्हित अक्षर xa_offset;
	अचिन्हित अक्षर xa_pad;		/* Helps gcc generate better code */
	काष्ठा xa_node *xa_node;
	काष्ठा xa_node *xa_alloc;
	xa_update_node_t xa_update;
पूर्ण;

/*
 * We encode त्रुटि_संs in the xas->xa_node.  If an error has happened, we need to
 * drop the lock to fix it, and once we've करोne so the xa_state is invalid.
 */
#घोषणा XA_ERROR(त्रुटि_सं) ((काष्ठा xa_node *)(((अचिन्हित दीर्घ)त्रुटि_सं << 2) | 2UL))
#घोषणा XAS_BOUNDS	((काष्ठा xa_node *)1UL)
#घोषणा XAS_RESTART	((काष्ठा xa_node *)3UL)

#घोषणा __XA_STATE(array, index, shअगरt, sibs)  अणु	\
	.xa = array,					\
	.xa_index = index,				\
	.xa_shअगरt = shअगरt,				\
	.xa_sibs = sibs,				\
	.xa_offset = 0,					\
	.xa_pad = 0,					\
	.xa_node = XAS_RESTART,				\
	.xa_alloc = शून्य,				\
	.xa_update = शून्य				\
पूर्ण

/**
 * XA_STATE() - Declare an XArray operation state.
 * @name: Name of this operation state (usually xas).
 * @array: Array to operate on.
 * @index: Initial index of पूर्णांकerest.
 *
 * Declare and initialise an xa_state on the stack.
 */
#घोषणा XA_STATE(name, array, index)				\
	काष्ठा xa_state name = __XA_STATE(array, index, 0, 0)

/**
 * XA_STATE_ORDER() - Declare an XArray operation state.
 * @name: Name of this operation state (usually xas).
 * @array: Array to operate on.
 * @index: Initial index of पूर्णांकerest.
 * @order: Order of entry.
 *
 * Declare and initialise an xa_state on the stack.  This variant of
 * XA_STATE() allows you to specअगरy the 'order' of the element you
 * want to operate on.`
 */
#घोषणा XA_STATE_ORDER(name, array, index, order)		\
	काष्ठा xa_state name = __XA_STATE(array,		\
			(index >> order) << order,		\
			order - (order % XA_CHUNK_SHIFT),	\
			(1U << (order % XA_CHUNK_SHIFT)) - 1)

#घोषणा xas_marked(xas, mark)	xa_marked((xas)->xa, (mark))
#घोषणा xas_trylock(xas)	xa_trylock((xas)->xa)
#घोषणा xas_lock(xas)		xa_lock((xas)->xa)
#घोषणा xas_unlock(xas)		xa_unlock((xas)->xa)
#घोषणा xas_lock_bh(xas)	xa_lock_bh((xas)->xa)
#घोषणा xas_unlock_bh(xas)	xa_unlock_bh((xas)->xa)
#घोषणा xas_lock_irq(xas)	xa_lock_irq((xas)->xa)
#घोषणा xas_unlock_irq(xas)	xa_unlock_irq((xas)->xa)
#घोषणा xas_lock_irqsave(xas, flags) \
				xa_lock_irqsave((xas)->xa, flags)
#घोषणा xas_unlock_irqrestore(xas, flags) \
				xa_unlock_irqrestore((xas)->xa, flags)

/**
 * xas_error() - Return an त्रुटि_सं stored in the xa_state.
 * @xas: XArray operation state.
 *
 * Return: 0 अगर no error has been noted.  A negative त्रुटि_सं अगर one has.
 */
अटल अंतरभूत पूर्णांक xas_error(स्थिर काष्ठा xa_state *xas)
अणु
	वापस xa_err(xas->xa_node);
पूर्ण

/**
 * xas_set_err() - Note an error in the xa_state.
 * @xas: XArray operation state.
 * @err: Negative error number.
 *
 * Only call this function with a negative @err; zero or positive errors
 * will probably not behave the way you think they should.  If you want
 * to clear the error from an xa_state, use xas_reset().
 */
अटल अंतरभूत व्योम xas_set_err(काष्ठा xa_state *xas, दीर्घ err)
अणु
	xas->xa_node = XA_ERROR(err);
पूर्ण

/**
 * xas_invalid() - Is the xas in a retry or error state?
 * @xas: XArray operation state.
 *
 * Return: %true अगर the xas cannot be used क्रम operations.
 */
अटल अंतरभूत bool xas_invalid(स्थिर काष्ठा xa_state *xas)
अणु
	वापस (अचिन्हित दीर्घ)xas->xa_node & 3;
पूर्ण

/**
 * xas_valid() - Is the xas a valid cursor पूर्णांकo the array?
 * @xas: XArray operation state.
 *
 * Return: %true अगर the xas can be used क्रम operations.
 */
अटल अंतरभूत bool xas_valid(स्थिर काष्ठा xa_state *xas)
अणु
	वापस !xas_invalid(xas);
पूर्ण

/**
 * xas_is_node() - Does the xas poपूर्णांक to a node?
 * @xas: XArray operation state.
 *
 * Return: %true अगर the xas currently references a node.
 */
अटल अंतरभूत bool xas_is_node(स्थिर काष्ठा xa_state *xas)
अणु
	वापस xas_valid(xas) && xas->xa_node;
पूर्ण

/* True अगर the poपूर्णांकer is something other than a node */
अटल अंतरभूत bool xas_not_node(काष्ठा xa_node *node)
अणु
	वापस ((अचिन्हित दीर्घ)node & 3) || !node;
पूर्ण

/* True अगर the node represents RESTART or an error */
अटल अंतरभूत bool xas_frozen(काष्ठा xa_node *node)
अणु
	वापस (अचिन्हित दीर्घ)node & 2;
पूर्ण

/* True अगर the node represents head-of-tree, RESTART or BOUNDS */
अटल अंतरभूत bool xas_top(काष्ठा xa_node *node)
अणु
	वापस node <= XAS_RESTART;
पूर्ण

/**
 * xas_reset() - Reset an XArray operation state.
 * @xas: XArray operation state.
 *
 * Resets the error or walk state of the @xas so future walks of the
 * array will start from the root.  Use this अगर you have dropped the
 * xarray lock and want to reuse the xa_state.
 *
 * Context: Any context.
 */
अटल अंतरभूत व्योम xas_reset(काष्ठा xa_state *xas)
अणु
	xas->xa_node = XAS_RESTART;
पूर्ण

/**
 * xas_retry() - Retry the operation अगर appropriate.
 * @xas: XArray operation state.
 * @entry: Entry from xarray.
 *
 * The advanced functions may someबार वापस an पूर्णांकernal entry, such as
 * a retry entry or a zero entry.  This function sets up the @xas to restart
 * the walk from the head of the array अगर needed.
 *
 * Context: Any context.
 * Return: true अगर the operation needs to be retried.
 */
अटल अंतरभूत bool xas_retry(काष्ठा xa_state *xas, स्थिर व्योम *entry)
अणु
	अगर (xa_is_zero(entry))
		वापस true;
	अगर (!xa_is_retry(entry))
		वापस false;
	xas_reset(xas);
	वापस true;
पूर्ण

व्योम *xas_load(काष्ठा xa_state *);
व्योम *xas_store(काष्ठा xa_state *, व्योम *entry);
व्योम *xas_find(काष्ठा xa_state *, अचिन्हित दीर्घ max);
व्योम *xas_find_conflict(काष्ठा xa_state *);

bool xas_get_mark(स्थिर काष्ठा xa_state *, xa_mark_t);
व्योम xas_set_mark(स्थिर काष्ठा xa_state *, xa_mark_t);
व्योम xas_clear_mark(स्थिर काष्ठा xa_state *, xa_mark_t);
व्योम *xas_find_marked(काष्ठा xa_state *, अचिन्हित दीर्घ max, xa_mark_t);
व्योम xas_init_marks(स्थिर काष्ठा xa_state *);

bool xas_nomem(काष्ठा xa_state *, gfp_t);
व्योम xas_छोड़ो(काष्ठा xa_state *);

व्योम xas_create_range(काष्ठा xa_state *);

#अगर_घोषित CONFIG_XARRAY_MULTI
पूर्णांक xa_get_order(काष्ठा xarray *, अचिन्हित दीर्घ index);
व्योम xas_split(काष्ठा xa_state *, व्योम *entry, अचिन्हित पूर्णांक order);
व्योम xas_split_alloc(काष्ठा xa_state *, व्योम *entry, अचिन्हित पूर्णांक order, gfp_t);
#अन्यथा
अटल अंतरभूत पूर्णांक xa_get_order(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xas_split(काष्ठा xa_state *xas, व्योम *entry,
		अचिन्हित पूर्णांक order)
अणु
	xas_store(xas, entry);
पूर्ण

अटल अंतरभूत व्योम xas_split_alloc(काष्ठा xa_state *xas, व्योम *entry,
		अचिन्हित पूर्णांक order, gfp_t gfp)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * xas_reload() - Refetch an entry from the xarray.
 * @xas: XArray operation state.
 *
 * Use this function to check that a previously loaded entry still has
 * the same value.  This is useful क्रम the lockless pagecache lookup where
 * we walk the array with only the RCU lock to protect us, lock the page,
 * then check that the page hasn't moved since we looked it up.
 *
 * The caller guarantees that @xas is still valid.  If it may be in an
 * error or restart state, call xas_load() instead.
 *
 * Return: The entry at this location in the xarray.
 */
अटल अंतरभूत व्योम *xas_reload(काष्ठा xa_state *xas)
अणु
	काष्ठा xa_node *node = xas->xa_node;
	व्योम *entry;
	अक्षर offset;

	अगर (!node)
		वापस xa_head(xas->xa);
	अगर (IS_ENABLED(CONFIG_XARRAY_MULTI)) अणु
		offset = (xas->xa_index >> node->shअगरt) & XA_CHUNK_MASK;
		entry = xa_entry(xas->xa, node, offset);
		अगर (!xa_is_sibling(entry))
			वापस entry;
		offset = xa_to_sibling(entry);
	पूर्ण अन्यथा अणु
		offset = xas->xa_offset;
	पूर्ण
	वापस xa_entry(xas->xa, node, offset);
पूर्ण

/**
 * xas_set() - Set up XArray operation state क्रम a dअगरferent index.
 * @xas: XArray operation state.
 * @index: New index पूर्णांकo the XArray.
 *
 * Move the operation state to refer to a dअगरferent index.  This will
 * have the effect of starting a walk from the top; see xas_next()
 * to move to an adjacent index.
 */
अटल अंतरभूत व्योम xas_set(काष्ठा xa_state *xas, अचिन्हित दीर्घ index)
अणु
	xas->xa_index = index;
	xas->xa_node = XAS_RESTART;
पूर्ण

/**
 * xas_set_order() - Set up XArray operation state क्रम a multislot entry.
 * @xas: XArray operation state.
 * @index: Target of the operation.
 * @order: Entry occupies 2^@order indices.
 */
अटल अंतरभूत व्योम xas_set_order(काष्ठा xa_state *xas, अचिन्हित दीर्घ index,
					अचिन्हित पूर्णांक order)
अणु
#अगर_घोषित CONFIG_XARRAY_MULTI
	xas->xa_index = order < BITS_PER_LONG ? (index >> order) << order : 0;
	xas->xa_shअगरt = order - (order % XA_CHUNK_SHIFT);
	xas->xa_sibs = (1 << (order % XA_CHUNK_SHIFT)) - 1;
	xas->xa_node = XAS_RESTART;
#अन्यथा
	BUG_ON(order > 0);
	xas_set(xas, index);
#पूर्ण_अगर
पूर्ण

/**
 * xas_set_update() - Set up XArray operation state क्रम a callback.
 * @xas: XArray operation state.
 * @update: Function to call when updating a node.
 *
 * The XArray can notअगरy a caller after it has updated an xa_node.
 * This is advanced functionality and is only needed by the page cache.
 */
अटल अंतरभूत व्योम xas_set_update(काष्ठा xa_state *xas, xa_update_node_t update)
अणु
	xas->xa_update = update;
पूर्ण

/**
 * xas_next_entry() - Advance iterator to next present entry.
 * @xas: XArray operation state.
 * @max: Highest index to वापस.
 *
 * xas_next_entry() is an अंतरभूत function to optimise xarray traversal क्रम
 * speed.  It is equivalent to calling xas_find(), and will call xas_find()
 * क्रम all the hard हालs.
 *
 * Return: The next present entry after the one currently referred to by @xas.
 */
अटल अंतरभूत व्योम *xas_next_entry(काष्ठा xa_state *xas, अचिन्हित दीर्घ max)
अणु
	काष्ठा xa_node *node = xas->xa_node;
	व्योम *entry;

	अगर (unlikely(xas_not_node(node) || node->shअगरt ||
			xas->xa_offset != (xas->xa_index & XA_CHUNK_MASK)))
		वापस xas_find(xas, max);

	करो अणु
		अगर (unlikely(xas->xa_index >= max))
			वापस xas_find(xas, max);
		अगर (unlikely(xas->xa_offset == XA_CHUNK_MASK))
			वापस xas_find(xas, max);
		entry = xa_entry(xas->xa, node, xas->xa_offset + 1);
		अगर (unlikely(xa_is_पूर्णांकernal(entry)))
			वापस xas_find(xas, max);
		xas->xa_offset++;
		xas->xa_index++;
	पूर्ण जबतक (!entry);

	वापस entry;
पूर्ण

/* Private */
अटल अंतरभूत अचिन्हित पूर्णांक xas_find_chunk(काष्ठा xa_state *xas, bool advance,
		xa_mark_t mark)
अणु
	अचिन्हित दीर्घ *addr = xas->xa_node->marks[(__क्रमce अचिन्हित)mark];
	अचिन्हित पूर्णांक offset = xas->xa_offset;

	अगर (advance)
		offset++;
	अगर (XA_CHUNK_SIZE == BITS_PER_LONG) अणु
		अगर (offset < XA_CHUNK_SIZE) अणु
			अचिन्हित दीर्घ data = *addr & (~0UL << offset);
			अगर (data)
				वापस __ffs(data);
		पूर्ण
		वापस XA_CHUNK_SIZE;
	पूर्ण

	वापस find_next_bit(addr, XA_CHUNK_SIZE, offset);
पूर्ण

/**
 * xas_next_marked() - Advance iterator to next marked entry.
 * @xas: XArray operation state.
 * @max: Highest index to वापस.
 * @mark: Mark to search क्रम.
 *
 * xas_next_marked() is an अंतरभूत function to optimise xarray traversal क्रम
 * speed.  It is equivalent to calling xas_find_marked(), and will call
 * xas_find_marked() क्रम all the hard हालs.
 *
 * Return: The next marked entry after the one currently referred to by @xas.
 */
अटल अंतरभूत व्योम *xas_next_marked(काष्ठा xa_state *xas, अचिन्हित दीर्घ max,
								xa_mark_t mark)
अणु
	काष्ठा xa_node *node = xas->xa_node;
	व्योम *entry;
	अचिन्हित पूर्णांक offset;

	अगर (unlikely(xas_not_node(node) || node->shअगरt))
		वापस xas_find_marked(xas, max, mark);
	offset = xas_find_chunk(xas, true, mark);
	xas->xa_offset = offset;
	xas->xa_index = (xas->xa_index & ~XA_CHUNK_MASK) + offset;
	अगर (xas->xa_index > max)
		वापस शून्य;
	अगर (offset == XA_CHUNK_SIZE)
		वापस xas_find_marked(xas, max, mark);
	entry = xa_entry(xas->xa, node, offset);
	अगर (!entry)
		वापस xas_find_marked(xas, max, mark);
	वापस entry;
पूर्ण

/*
 * If iterating जबतक holding a lock, drop the lock and reschedule
 * every %XA_CHECK_SCHED loops.
 */
क्रमागत अणु
	XA_CHECK_SCHED = 4096,
पूर्ण;

/**
 * xas_क्रम_each() - Iterate over a range of an XArray.
 * @xas: XArray operation state.
 * @entry: Entry retrieved from the array.
 * @max: Maximum index to retrieve from array.
 *
 * The loop body will be executed क्रम each entry present in the xarray
 * between the current xas position and @max.  @entry will be set to
 * the entry retrieved from the xarray.  It is safe to delete entries
 * from the array in the loop body.  You should hold either the RCU lock
 * or the xa_lock जबतक iterating.  If you need to drop the lock, call
 * xas_छोड़ो() first.
 */
#घोषणा xas_क्रम_each(xas, entry, max) \
	क्रम (entry = xas_find(xas, max); entry; \
	     entry = xas_next_entry(xas, max))

/**
 * xas_क्रम_each_marked() - Iterate over a range of an XArray.
 * @xas: XArray operation state.
 * @entry: Entry retrieved from the array.
 * @max: Maximum index to retrieve from array.
 * @mark: Mark to search क्रम.
 *
 * The loop body will be executed क्रम each marked entry in the xarray
 * between the current xas position and @max.  @entry will be set to
 * the entry retrieved from the xarray.  It is safe to delete entries
 * from the array in the loop body.  You should hold either the RCU lock
 * or the xa_lock जबतक iterating.  If you need to drop the lock, call
 * xas_छोड़ो() first.
 */
#घोषणा xas_क्रम_each_marked(xas, entry, max, mark) \
	क्रम (entry = xas_find_marked(xas, max, mark); entry; \
	     entry = xas_next_marked(xas, max, mark))

/**
 * xas_क्रम_each_conflict() - Iterate over a range of an XArray.
 * @xas: XArray operation state.
 * @entry: Entry retrieved from the array.
 *
 * The loop body will be executed क्रम each entry in the XArray that
 * lies within the range specअगरied by @xas.  If the loop terminates
 * normally, @entry will be %शून्य.  The user may अवरोध out of the loop,
 * which will leave @entry set to the conflicting entry.  The caller
 * may also call xa_set_err() to निकास the loop जबतक setting an error
 * to record the reason.
 */
#घोषणा xas_क्रम_each_conflict(xas, entry) \
	जबतक ((entry = xas_find_conflict(xas)))

व्योम *__xas_next(काष्ठा xa_state *);
व्योम *__xas_prev(काष्ठा xa_state *);

/**
 * xas_prev() - Move iterator to previous index.
 * @xas: XArray operation state.
 *
 * If the @xas was in an error state, it will reमुख्य in an error state
 * and this function will वापस %शून्य.  If the @xas has never been walked,
 * it will have the effect of calling xas_load().  Otherwise one will be
 * subtracted from the index and the state will be walked to the correct
 * location in the array क्रम the next operation.
 *
 * If the iterator was referencing index 0, this function wraps
 * around to %अच_दीर्घ_उच्च.
 *
 * Return: The entry at the new index.  This may be %शून्य or an पूर्णांकernal
 * entry.
 */
अटल अंतरभूत व्योम *xas_prev(काष्ठा xa_state *xas)
अणु
	काष्ठा xa_node *node = xas->xa_node;

	अगर (unlikely(xas_not_node(node) || node->shअगरt ||
				xas->xa_offset == 0))
		वापस __xas_prev(xas);

	xas->xa_index--;
	xas->xa_offset--;
	वापस xa_entry(xas->xa, node, xas->xa_offset);
पूर्ण

/**
 * xas_next() - Move state to next index.
 * @xas: XArray operation state.
 *
 * If the @xas was in an error state, it will reमुख्य in an error state
 * and this function will वापस %शून्य.  If the @xas has never been walked,
 * it will have the effect of calling xas_load().  Otherwise one will be
 * added to the index and the state will be walked to the correct
 * location in the array क्रम the next operation.
 *
 * If the iterator was referencing index %अच_दीर्घ_उच्च, this function wraps
 * around to 0.
 *
 * Return: The entry at the new index.  This may be %शून्य or an पूर्णांकernal
 * entry.
 */
अटल अंतरभूत व्योम *xas_next(काष्ठा xa_state *xas)
अणु
	काष्ठा xa_node *node = xas->xa_node;

	अगर (unlikely(xas_not_node(node) || node->shअगरt ||
				xas->xa_offset == XA_CHUNK_MASK))
		वापस __xas_next(xas);

	xas->xa_index++;
	xas->xa_offset++;
	वापस xa_entry(xas->xa, node, xas->xa_offset);
पूर्ण

#पूर्ण_अगर /* _LINUX_XARRAY_H */

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/list_sort.h>
#समावेश <linux/list.h>

/*
 * Returns a list organized in an पूर्णांकermediate क्रमmat suited
 * to chaining of merge() calls: null-terminated, no reserved or
 * sentinel head node, "prev" links not मुख्यtained.
 */
__attribute__((nonnull(2,3,4)))
अटल काष्ठा list_head *merge(व्योम *priv, list_cmp_func_t cmp,
				काष्ठा list_head *a, काष्ठा list_head *b)
अणु
	काष्ठा list_head *head, **tail = &head;

	क्रम (;;) अणु
		/* अगर equal, take 'a' -- important क्रम sort stability */
		अगर (cmp(priv, a, b) <= 0) अणु
			*tail = a;
			tail = &a->next;
			a = a->next;
			अगर (!a) अणु
				*tail = b;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			*tail = b;
			tail = &b->next;
			b = b->next;
			अगर (!b) अणु
				*tail = a;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस head;
पूर्ण

/*
 * Combine final list merge with restoration of standard करोubly-linked
 * list काष्ठाure.  This approach duplicates code from merge(), but
 * runs faster than the tidier alternatives of either a separate final
 * prev-link restoration pass, or मुख्यtaining the prev links
 * throughout.
 */
__attribute__((nonnull(2,3,4,5)))
अटल व्योम merge_final(व्योम *priv, list_cmp_func_t cmp, काष्ठा list_head *head,
			काष्ठा list_head *a, काष्ठा list_head *b)
अणु
	काष्ठा list_head *tail = head;
	u8 count = 0;

	क्रम (;;) अणु
		/* अगर equal, take 'a' -- important क्रम sort stability */
		अगर (cmp(priv, a, b) <= 0) अणु
			tail->next = a;
			a->prev = tail;
			tail = a;
			a = a->next;
			अगर (!a)
				अवरोध;
		पूर्ण अन्यथा अणु
			tail->next = b;
			b->prev = tail;
			tail = b;
			b = b->next;
			अगर (!b) अणु
				b = a;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Finish linking reमुख्यder of list b on to tail */
	tail->next = b;
	करो अणु
		/*
		 * If the merge is highly unbalanced (e.g. the input is
		 * alपढ़ोy sorted), this loop may run many iterations.
		 * Continue callbacks to the client even though no
		 * element comparison is needed, so the client's cmp()
		 * routine can invoke cond_resched() periodically.
		 */
		अगर (unlikely(!++count))
			cmp(priv, b, b);
		b->prev = tail;
		tail = b;
		b = b->next;
	पूर्ण जबतक (b);

	/* And the final links to make a circular करोubly-linked list */
	tail->next = head;
	head->prev = tail;
पूर्ण

/**
 * list_sort - sort a list
 * @priv: निजी data, opaque to list_sort(), passed to @cmp
 * @head: the list to sort
 * @cmp: the elements comparison function
 *
 * The comparison funtion @cmp must वापस > 0 अगर @a should sort after
 * @b ("@a > @b" अगर you want an ascending sort), and <= 0 अगर @a should
 * sort beक्रमe @b *or* their original order should be preserved.  It is
 * always called with the element that came first in the input in @a,
 * and list_sort is a stable sort, so it is not necessary to distinguish
 * the @a < @b and @a == @b हालs.
 *
 * This is compatible with two styles of @cmp function:
 * - The traditional style which वापसs <0 / =0 / >0, or
 * - Returning a boolean 0/1.
 * The latter offers a chance to save a few cycles in the comparison
 * (which is used by e.g. plug_ctx_cmp() in block/blk-mq.c).
 *
 * A good way to ग_लिखो a multi-word comparison is::
 *
 *	अगर (a->high != b->high)
 *		वापस a->high > b->high;
 *	अगर (a->middle != b->middle)
 *		वापस a->middle > b->middle;
 *	वापस a->low > b->low;
 *
 *
 * This mergesort is as eager as possible जबतक always perक्रमming at least
 * 2:1 balanced merges.  Given two pending sublists of size 2^k, they are
 * merged to a size-2^(k+1) list as soon as we have 2^k following elements.
 *
 * Thus, it will aव्योम cache thrashing as दीर्घ as 3*2^k elements can
 * fit पूर्णांकo the cache.  Not quite as good as a fully-eager bottom-up
 * mergesort, but it करोes use 0.2*n fewer comparisons, so is faster in
 * the common हाल that everything fits पूर्णांकo L1.
 *
 *
 * The merging is controlled by "count", the number of elements in the
 * pending lists.  This is beautअगरully simple code, but rather subtle.
 *
 * Each समय we increment "count", we set one bit (bit k) and clear
 * bits k-1 .. 0.  Each समय this happens (except the very first समय
 * क्रम each bit, when count increments to 2^k), we merge two lists of
 * size 2^k पूर्णांकo one list of size 2^(k+1).
 *
 * This merge happens exactly when the count reaches an odd multiple of
 * 2^k, which is when we have 2^k elements pending in smaller lists,
 * so it's safe to merge away two lists of size 2^k.
 *
 * After this happens twice, we have created two lists of size 2^(k+1),
 * which will be merged पूर्णांकo a list of size 2^(k+2) beक्रमe we create
 * a third list of size 2^(k+1), so there are never more than two pending.
 *
 * The number of pending lists of size 2^k is determined by the
 * state of bit k of "count" plus two extra pieces of inक्रमmation:
 *
 * - The state of bit k-1 (when k == 0, consider bit -1 always set), and
 * - Whether the higher-order bits are zero or non-zero (i.e.
 *   is count >= 2^(k+1)).
 *
 * There are six states we distinguish.  "x" represents some arbitrary
 * bits, and "y" represents some arbitrary non-zero bits:
 * 0:  00x: 0 pending of size 2^k;           x pending of sizes < 2^k
 * 1:  01x: 0 pending of size 2^k; 2^(k-1) + x pending of sizes < 2^k
 * 2: x10x: 0 pending of size 2^k; 2^k     + x pending of sizes < 2^k
 * 3: x11x: 1 pending of size 2^k; 2^(k-1) + x pending of sizes < 2^k
 * 4: y00x: 1 pending of size 2^k; 2^k     + x pending of sizes < 2^k
 * 5: y01x: 2 pending of size 2^k; 2^(k-1) + x pending of sizes < 2^k
 * (merge and loop back to state 2)
 *
 * We gain lists of size 2^k in the 2->3 and 4->5 transitions (because
 * bit k-1 is set जबतक the more signअगरicant bits are non-zero) and
 * merge them away in the 5->2 transition.  Note in particular that just
 * beक्रमe the 5->2 transition, all lower-order bits are 11 (state 3),
 * so there is one list of each smaller size.
 *
 * When we reach the end of the input, we merge all the pending
 * lists, from smallest to largest.  If you work through हालs 2 to
 * 5 above, you can see that the number of elements we merge with a list
 * of size 2^k varies from 2^(k-1) (हालs 3 and 5 when x == 0) to
 * 2^(k+1) - 1 (second merge of हाल 5 when x == 2^(k-1) - 1).
 */
__attribute__((nonnull(2,3)))
व्योम list_sort(व्योम *priv, काष्ठा list_head *head, list_cmp_func_t cmp)
अणु
	काष्ठा list_head *list = head->next, *pending = शून्य;
	माप_प्रकार count = 0;	/* Count of pending */

	अगर (list == head->prev)	/* Zero or one elements */
		वापस;

	/* Convert to a null-terminated singly-linked list. */
	head->prev->next = शून्य;

	/*
	 * Data काष्ठाure invariants:
	 * - All lists are singly linked and null-terminated; prev
	 *   poपूर्णांकers are not मुख्यtained.
	 * - pending is a prev-linked "list of lists" of sorted
	 *   sublists aरुकोing further merging.
	 * - Each of the sorted sublists is घातer-of-two in size.
	 * - Sublists are sorted by size and age, smallest & newest at front.
	 * - There are zero to two sublists of each size.
	 * - A pair of pending sublists are merged as soon as the number
	 *   of following pending elements equals their size (i.e.
	 *   each समय count reaches an odd multiple of that size).
	 *   That ensures each later final merge will be at worst 2:1.
	 * - Each round consists of:
	 *   - Merging the two sublists selected by the highest bit
	 *     which flips when count is incremented, and
	 *   - Adding an element from the input as a size-1 sublist.
	 */
	करो अणु
		माप_प्रकार bits;
		काष्ठा list_head **tail = &pending;

		/* Find the least-signअगरicant clear bit in count */
		क्रम (bits = count; bits & 1; bits >>= 1)
			tail = &(*tail)->prev;
		/* Do the indicated merge */
		अगर (likely(bits)) अणु
			काष्ठा list_head *a = *tail, *b = a->prev;

			a = merge(priv, cmp, b, a);
			/* Install the merged result in place of the inमाला_दो */
			a->prev = b->prev;
			*tail = a;
		पूर्ण

		/* Move one element from input list to pending */
		list->prev = pending;
		pending = list;
		list = list->next;
		pending->next = शून्य;
		count++;
	पूर्ण जबतक (list);

	/* End of input; merge together all the pending lists. */
	list = pending;
	pending = pending->prev;
	क्रम (;;) अणु
		काष्ठा list_head *next = pending->prev;

		अगर (!next)
			अवरोध;
		list = merge(priv, cmp, pending, list);
		pending = next;
	पूर्ण
	/* The final merge, rebuilding prev links */
	merge_final(priv, cmp, head, pending, list);
पूर्ण
EXPORT_SYMBOL(list_sort);

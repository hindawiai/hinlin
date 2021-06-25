<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Regression2
 * Description:
 * Toshiyuki Okajima describes the following radix-tree bug:
 *
 * In the following हाल, we can get a hangup on
 *   radix_radix_tree_gang_lookup_tag_slot.
 *
 * 0.  The radix tree contains RADIX_TREE_MAP_SIZE items. And the tag of
 *     a certain item has PAGECACHE_TAG_सूचीTY.
 * 1.  radix_tree_range_tag_अगर_tagged(, start, end, , PAGECACHE_TAG_सूचीTY,
 *     PAGECACHE_TAG_TOWRITE) is called to add PAGECACHE_TAG_TOWRITE tag
 *     क्रम the tag which has PAGECACHE_TAG_सूचीTY. However, there is no tag with
 *     PAGECACHE_TAG_सूचीTY within the range from start to end. As the result,
 *     There is no tag with PAGECACHE_TAG_TOWRITE but the root tag has
 *     PAGECACHE_TAG_TOWRITE.
 * 2.  An item is added पूर्णांकo the radix tree and then the level of it is
 *     extended पूर्णांकo 2 from 1. At that समय, the new radix tree node succeeds
 *     the tag status of the root tag. Thereक्रमe the tag of the new radix tree
 *     node has PAGECACHE_TAG_TOWRITE but there is not slot with
 *     PAGECACHE_TAG_TOWRITE tag in the child node of the new radix tree node.
 * 3.  The tag of a certain item is cleared with PAGECACHE_TAG_सूचीTY.
 * 4.  All items within the index range from 0 to RADIX_TREE_MAP_SIZE - 1 are
 *     released. (Only the item which index is RADIX_TREE_MAP_SIZE exist in the
 *     radix tree.) As the result, the slot of the radix tree node is शून्य but
 *     the tag which corresponds to the slot has PAGECACHE_TAG_TOWRITE.
 * 5.  radix_tree_gang_lookup_tag_slot(PAGECACHE_TAG_TOWRITE) calls
 *     __lookup_tag. __lookup_tag वापसs with 0. And __lookup_tag करोesn't
 *     change the index that is the input and output parameter. Because the 1st
 *     slot of the radix tree node is शून्य, but the tag which corresponds to
 *     the slot has PAGECACHE_TAG_TOWRITE.
 *     Thereक्रमe radix_tree_gang_lookup_tag_slot tries to get some items by
 *     calling __lookup_tag, but it cannot get any items क्रमever.
 *
 * The fix is to change that radix_tree_tag_अगर_tagged करोesn't tag the root tag
 * अगर it करोesn't set any tags within the specअगरied range.
 *
 * Running:
 * This test should run to completion immediately. The above bug would cause it
 * to hang indefinitely.
 *
 * Upstream commit:
 * Not yet
 */
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/radix-tree.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>

#समावेश "regression.h"
#समावेश "test.h"

#घोषणा PAGECACHE_TAG_सूचीTY     XA_MARK_0
#घोषणा PAGECACHE_TAG_WRITEBACK XA_MARK_1
#घोषणा PAGECACHE_TAG_TOWRITE   XA_MARK_2

अटल RADIX_TREE(mt_tree, GFP_KERNEL);
अचिन्हित दीर्घ page_count = 0;

काष्ठा page अणु
	अचिन्हित दीर्घ index;
पूर्ण;

अटल काष्ठा page *page_alloc(व्योम)
अणु
	काष्ठा page *p;
	p = दो_स्मृति(माप(काष्ठा page));
	p->index = page_count++;

	वापस p;
पूर्ण

व्योम regression2_test(व्योम)
अणु
	पूर्णांक i;
	काष्ठा page *p;
	पूर्णांक max_slots = RADIX_TREE_MAP_SIZE;
	अचिन्हित दीर्घ पूर्णांक start, end;
	काष्ठा page *pages[1];

	prपूर्णांकv(1, "running regression test 2 (should take milliseconds)\n");
	/* 0. */
	क्रम (i = 0; i <= max_slots - 1; i++) अणु
		p = page_alloc();
		radix_tree_insert(&mt_tree, i, p);
	पूर्ण
	radix_tree_tag_set(&mt_tree, max_slots - 1, PAGECACHE_TAG_सूचीTY);

	/* 1. */
	start = 0;
	end = max_slots - 2;
	tag_tagged_items(&mt_tree, start, end, 1,
				PAGECACHE_TAG_सूचीTY, PAGECACHE_TAG_TOWRITE);

	/* 2. */
	p = page_alloc();
	radix_tree_insert(&mt_tree, max_slots, p);

	/* 3. */
	radix_tree_tag_clear(&mt_tree, max_slots - 1, PAGECACHE_TAG_सूचीTY);

	/* 4. */
	क्रम (i = max_slots - 1; i >= 0; i--)
		मुक्त(radix_tree_delete(&mt_tree, i));

	/* 5. */
	// NOTE: start should not be 0 because radix_tree_gang_lookup_tag_slot
	//       can वापस.
	start = 1;
	end = max_slots - 2;
	radix_tree_gang_lookup_tag_slot(&mt_tree, (व्योम ***)pages, start, end,
		PAGECACHE_TAG_TOWRITE);

	/* We हटाओ all the reमुख्यed nodes */
	मुक्त(radix_tree_delete(&mt_tree, max_slots));

	BUG_ON(!radix_tree_empty(&mt_tree));

	prपूर्णांकv(1, "regression test 2, done\n");
पूर्ण

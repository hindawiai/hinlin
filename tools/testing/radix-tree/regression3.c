<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Regression3
 * Description:
 * Helper radix_tree_iter_retry resets next_index to the current index.
 * In following radix_tree_next_slot current chunk size becomes zero.
 * This isn't checked and it tries to dereference null poपूर्णांकer in slot.
 *
 * Helper radix_tree_iter_resume reset slot to शून्य and next_index to index + 1,
 * क्रम tagger iteraction it also must reset cached tags in iterator to पात
 * next radix_tree_next_slot and go to slow-path पूर्णांकo radix_tree_next_chunk.
 *
 * Running:
 * This test should run to completion immediately. The above bug would
 * cause it to segfault.
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

व्योम regression3_test(व्योम)
अणु
	RADIX_TREE(root, GFP_KERNEL);
	व्योम *ptr0 = (व्योम *)4ul;
	व्योम *ptr = (व्योम *)8ul;
	काष्ठा radix_tree_iter iter;
	व्योम **slot;
	bool first;

	prपूर्णांकv(1, "running regression test 3 (should take milliseconds)\n");

	radix_tree_insert(&root, 0, ptr0);
	radix_tree_tag_set(&root, 0, 0);

	first = true;
	radix_tree_क्रम_each_tagged(slot, &root, &iter, 0, 0) अणु
		prपूर्णांकv(2, "tagged %ld %p\n", iter.index, *slot);
		अगर (first) अणु
			radix_tree_insert(&root, 1, ptr);
			radix_tree_tag_set(&root, 1, 0);
			first = false;
		पूर्ण
		अगर (radix_tree_deref_retry(*slot)) अणु
			prपूर्णांकv(2, "retry at %ld\n", iter.index);
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
	पूर्ण
	radix_tree_delete(&root, 1);

	first = true;
	radix_tree_क्रम_each_slot(slot, &root, &iter, 0) अणु
		prपूर्णांकv(2, "slot %ld %p\n", iter.index, *slot);
		अगर (first) अणु
			radix_tree_insert(&root, 1, ptr);
			first = false;
		पूर्ण
		अगर (radix_tree_deref_retry(*slot)) अणु
			prपूर्णांकv(2, "retry at %ld\n", iter.index);
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
	पूर्ण

	radix_tree_क्रम_each_slot(slot, &root, &iter, 0) अणु
		prपूर्णांकv(2, "slot %ld %p\n", iter.index, *slot);
		अगर (!iter.index) अणु
			prपूर्णांकv(2, "next at %ld\n", iter.index);
			slot = radix_tree_iter_resume(slot, &iter);
		पूर्ण
	पूर्ण

	radix_tree_tag_set(&root, 0, 0);
	radix_tree_tag_set(&root, 1, 0);
	radix_tree_क्रम_each_tagged(slot, &root, &iter, 0, 0) अणु
		prपूर्णांकv(2, "tagged %ld %p\n", iter.index, *slot);
		अगर (!iter.index) अणु
			prपूर्णांकv(2, "next at %ld\n", iter.index);
			slot = radix_tree_iter_resume(slot, &iter);
		पूर्ण
	पूर्ण

	radix_tree_delete(&root, 0);
	radix_tree_delete(&root, 1);

	prपूर्णांकv(1, "regression test 3 passed\n");
पूर्ण

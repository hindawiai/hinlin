<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_BLOCK_RANGE_H
#घोषणा __PERF_BLOCK_RANGE_H

#समावेश <stdbool.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/types.h>

काष्ठा symbol;

/*
 * काष्ठा block_range - non-overlapping parts of basic blocks
 * @node:	treenode
 * @start:	inclusive start of range
 * @end:	inclusive end of range
 * @is_target:	@start is a jump target
 * @is_branch:	@end is a branch inकाष्ठाion
 * @coverage:	number of blocks that cover this range
 * @taken:	number of बार the branch is taken (requires @is_branch)
 * @pred:	number of बार the taken branch was predicted
 */
काष्ठा block_range अणु
	काष्ठा rb_node node;

	काष्ठा symbol *sym;

	u64 start;
	u64 end;

	पूर्णांक is_target, is_branch;

	u64 coverage;
	u64 entry;
	u64 taken;
	u64 pred;
पूर्ण;

अटल अंतरभूत काष्ठा block_range *block_range__next(काष्ठा block_range *br)
अणु
	काष्ठा rb_node *n = rb_next(&br->node);
	अगर (!n)
		वापस शून्य;
	वापस rb_entry(n, काष्ठा block_range, node);
पूर्ण

काष्ठा block_range_iter अणु
	काष्ठा block_range *start;
	काष्ठा block_range *end;
पूर्ण;

अटल अंतरभूत काष्ठा block_range *block_range_iter(काष्ठा block_range_iter *iter)
अणु
	वापस iter->start;
पूर्ण

अटल अंतरभूत bool block_range_iter__next(काष्ठा block_range_iter *iter)
अणु
	अगर (iter->start == iter->end)
		वापस false;

	iter->start = block_range__next(iter->start);
	वापस true;
पूर्ण

अटल अंतरभूत bool block_range_iter__valid(काष्ठा block_range_iter *iter)
अणु
	अगर (!iter->start || !iter->end)
		वापस false;
	वापस true;
पूर्ण

बाह्य काष्ठा block_range *block_range__find(u64 addr);
बाह्य काष्ठा block_range_iter block_range__create(u64 start, u64 end);
बाह्य द्विगुन block_range__coverage(काष्ठा block_range *br);

#पूर्ण_अगर /* __PERF_BLOCK_RANGE_H */

<शैली गुरु>
/*
 * Copyright (c) 2014, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/list_sort.h>

#समावेश <linux/पूर्णांकerval_tree_generic.h>
#समावेश "usnic_uiom_interval_tree.h"

#घोषणा START(node) ((node)->start)
#घोषणा LAST(node) ((node)->last)

#घोषणा MAKE_NODE(node, start, end, ref_cnt, flags, err, err_out)	\
		करो अणु							\
			node = usnic_uiom_पूर्णांकerval_node_alloc(start,	\
					end, ref_cnt, flags);		\
				अगर (!node) अणु				\
					err = -ENOMEM;			\
					जाओ err_out;			\
				पूर्ण					\
		पूर्ण जबतक (0)

#घोषणा MARK_FOR_ADD(node, list) (list_add_tail(&node->link, list))

#घोषणा MAKE_NODE_AND_APPEND(node, start, end, ref_cnt, flags, err,	\
				err_out, list)				\
				करो अणु					\
					MAKE_NODE(node, start, end,	\
						ref_cnt, flags, err,	\
						err_out);		\
					MARK_FOR_ADD(node, list);	\
				पूर्ण जबतक (0)

#घोषणा FLAGS_EQUAL(flags1, flags2, mask)				\
			(((flags1) & (mask)) == ((flags2) & (mask)))

अटल काष्ठा usnic_uiom_पूर्णांकerval_node*
usnic_uiom_पूर्णांकerval_node_alloc(दीर्घ पूर्णांक start, दीर्घ पूर्णांक last, पूर्णांक ref_cnt,
				पूर्णांक flags)
अणु
	काष्ठा usnic_uiom_पूर्णांकerval_node *पूर्णांकerval = kzalloc(माप(*पूर्णांकerval),
								GFP_ATOMIC);
	अगर (!पूर्णांकerval)
		वापस शून्य;

	पूर्णांकerval->start = start;
	पूर्णांकerval->last = last;
	पूर्णांकerval->flags = flags;
	पूर्णांकerval->ref_cnt = ref_cnt;

	वापस पूर्णांकerval;
पूर्ण

अटल पूर्णांक पूर्णांकerval_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
			स्थिर काष्ठा list_head *b)
अणु
	काष्ठा usnic_uiom_पूर्णांकerval_node *node_a, *node_b;

	node_a = list_entry(a, काष्ठा usnic_uiom_पूर्णांकerval_node, link);
	node_b = list_entry(b, काष्ठा usnic_uiom_पूर्णांकerval_node, link);

	/* दीर्घ to पूर्णांक */
	अगर (node_a->start < node_b->start)
		वापस -1;
	अन्यथा अगर (node_a->start > node_b->start)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम
find_पूर्णांकervals_पूर्णांकersection_sorted(काष्ठा rb_root_cached *root,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ last,
				   काष्ठा list_head *list)
अणु
	काष्ठा usnic_uiom_पूर्णांकerval_node *node;

	INIT_LIST_HEAD(list);

	क्रम (node = usnic_uiom_पूर्णांकerval_tree_iter_first(root, start, last);
		node;
		node = usnic_uiom_पूर्णांकerval_tree_iter_next(node, start, last))
		list_add_tail(&node->link, list);

	list_sort(शून्य, list, पूर्णांकerval_cmp);
पूर्ण

पूर्णांक usnic_uiom_get_पूर्णांकervals_dअगरf(अचिन्हित दीर्घ start, अचिन्हित दीर्घ last,
					पूर्णांक flags, पूर्णांक flag_mask,
					काष्ठा rb_root_cached *root,
					काष्ठा list_head *dअगरf_set)
अणु
	काष्ठा usnic_uiom_पूर्णांकerval_node *पूर्णांकerval, *पंचांगp;
	पूर्णांक err = 0;
	दीर्घ पूर्णांक pivot = start;
	LIST_HEAD(पूर्णांकersection_set);

	INIT_LIST_HEAD(dअगरf_set);

	find_पूर्णांकervals_पूर्णांकersection_sorted(root, start, last,
						&पूर्णांकersection_set);

	list_क्रम_each_entry(पूर्णांकerval, &पूर्णांकersection_set, link) अणु
		अगर (pivot < पूर्णांकerval->start) अणु
			MAKE_NODE_AND_APPEND(पंचांगp, pivot, पूर्णांकerval->start - 1,
						1, flags, err, err_out,
						dअगरf_set);
			pivot = पूर्णांकerval->start;
		पूर्ण

		/*
		 * Invariant: Set [start, pivot] is either in dअगरf_set or root,
		 * but not in both.
		 */

		अगर (pivot > पूर्णांकerval->last) अणु
			जारी;
		पूर्ण अन्यथा अगर (pivot <= पूर्णांकerval->last &&
				FLAGS_EQUAL(पूर्णांकerval->flags, flags,
				flag_mask)) अणु
			pivot = पूर्णांकerval->last + 1;
		पूर्ण
	पूर्ण

	अगर (pivot <= last)
		MAKE_NODE_AND_APPEND(पंचांगp, pivot, last, 1, flags, err, err_out,
					dअगरf_set);

	वापस 0;

err_out:
	list_क्रम_each_entry_safe(पूर्णांकerval, पंचांगp, dअगरf_set, link) अणु
		list_del(&पूर्णांकerval->link);
		kमुक्त(पूर्णांकerval);
	पूर्ण

	वापस err;
पूर्ण

व्योम usnic_uiom_put_पूर्णांकerval_set(काष्ठा list_head *पूर्णांकervals)
अणु
	काष्ठा usnic_uiom_पूर्णांकerval_node *पूर्णांकerval, *पंचांगp;
	list_क्रम_each_entry_safe(पूर्णांकerval, पंचांगp, पूर्णांकervals, link)
		kमुक्त(पूर्णांकerval);
पूर्ण

पूर्णांक usnic_uiom_insert_पूर्णांकerval(काष्ठा rb_root_cached *root, अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ last, पूर्णांक flags)
अणु
	काष्ठा usnic_uiom_पूर्णांकerval_node *पूर्णांकerval, *पंचांगp;
	अचिन्हित दीर्घ istart, ilast;
	पूर्णांक iref_cnt, अगरlags;
	अचिन्हित दीर्घ lpivot = start;
	पूर्णांक err = 0;
	LIST_HEAD(to_add);
	LIST_HEAD(पूर्णांकersection_set);

	find_पूर्णांकervals_पूर्णांकersection_sorted(root, start, last,
						&पूर्णांकersection_set);

	list_क्रम_each_entry(पूर्णांकerval, &पूर्णांकersection_set, link) अणु
		/*
		 * Invariant - lpivot is the left edge of next पूर्णांकerval to be
		 * inserted
		 */
		istart = पूर्णांकerval->start;
		ilast = पूर्णांकerval->last;
		iref_cnt = पूर्णांकerval->ref_cnt;
		अगरlags = पूर्णांकerval->flags;

		अगर (istart < lpivot) अणु
			MAKE_NODE_AND_APPEND(पंचांगp, istart, lpivot - 1, iref_cnt,
						अगरlags, err, err_out, &to_add);
		पूर्ण अन्यथा अगर (istart > lpivot) अणु
			MAKE_NODE_AND_APPEND(पंचांगp, lpivot, istart - 1, 1, flags,
						err, err_out, &to_add);
			lpivot = istart;
		पूर्ण अन्यथा अणु
			lpivot = istart;
		पूर्ण

		अगर (ilast > last) अणु
			MAKE_NODE_AND_APPEND(पंचांगp, lpivot, last, iref_cnt + 1,
						अगरlags | flags, err, err_out,
						&to_add);
			MAKE_NODE_AND_APPEND(पंचांगp, last + 1, ilast, iref_cnt,
						अगरlags, err, err_out, &to_add);
		पूर्ण अन्यथा अणु
			MAKE_NODE_AND_APPEND(पंचांगp, lpivot, ilast, iref_cnt + 1,
						अगरlags | flags, err, err_out,
						&to_add);
		पूर्ण

		lpivot = ilast + 1;
	पूर्ण

	अगर (lpivot <= last)
		MAKE_NODE_AND_APPEND(पंचांगp, lpivot, last, 1, flags, err, err_out,
					&to_add);

	list_क्रम_each_entry_safe(पूर्णांकerval, पंचांगp, &पूर्णांकersection_set, link) अणु
		usnic_uiom_पूर्णांकerval_tree_हटाओ(पूर्णांकerval, root);
		kमुक्त(पूर्णांकerval);
	पूर्ण

	list_क्रम_each_entry(पूर्णांकerval, &to_add, link)
		usnic_uiom_पूर्णांकerval_tree_insert(पूर्णांकerval, root);

	वापस 0;

err_out:
	list_क्रम_each_entry_safe(पूर्णांकerval, पंचांगp, &to_add, link)
		kमुक्त(पूर्णांकerval);

	वापस err;
पूर्ण

व्योम usnic_uiom_हटाओ_पूर्णांकerval(काष्ठा rb_root_cached *root,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ last,
				काष्ठा list_head *हटाओd)
अणु
	काष्ठा usnic_uiom_पूर्णांकerval_node *पूर्णांकerval;

	क्रम (पूर्णांकerval = usnic_uiom_पूर्णांकerval_tree_iter_first(root, start, last);
			पूर्णांकerval;
			पूर्णांकerval = usnic_uiom_पूर्णांकerval_tree_iter_next(पूर्णांकerval,
									start,
									last)) अणु
		अगर (--पूर्णांकerval->ref_cnt == 0)
			list_add_tail(&पूर्णांकerval->link, हटाओd);
	पूर्ण

	list_क्रम_each_entry(पूर्णांकerval, हटाओd, link)
		usnic_uiom_पूर्णांकerval_tree_हटाओ(पूर्णांकerval, root);
पूर्ण

INTERVAL_TREE_DEFINE(काष्ठा usnic_uiom_पूर्णांकerval_node, rb,
			अचिन्हित दीर्घ, __subtree_last,
			START, LAST, , usnic_uiom_पूर्णांकerval_tree)

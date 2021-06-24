<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
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

#अगर_अघोषित USNIC_UIOM_INTERVAL_TREE_H_
#घोषणा USNIC_UIOM_INTERVAL_TREE_H_

#समावेश <linux/rbtree.h>

काष्ठा usnic_uiom_पूर्णांकerval_node अणु
	काष्ठा rb_node			rb;
	काष्ठा list_head		link;
	अचिन्हित दीर्घ			start;
	अचिन्हित दीर्घ			last;
	अचिन्हित दीर्घ			__subtree_last;
	अचिन्हित पूर्णांक			ref_cnt;
	पूर्णांक				flags;
पूर्ण;

बाह्य व्योम
usnic_uiom_पूर्णांकerval_tree_insert(काष्ठा usnic_uiom_पूर्णांकerval_node *node,
					काष्ठा rb_root_cached *root);
बाह्य व्योम
usnic_uiom_पूर्णांकerval_tree_हटाओ(काष्ठा usnic_uiom_पूर्णांकerval_node *node,
					काष्ठा rb_root_cached *root);
बाह्य काष्ठा usnic_uiom_पूर्णांकerval_node *
usnic_uiom_पूर्णांकerval_tree_iter_first(काष्ठा rb_root_cached *root,
					अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ last);
बाह्य काष्ठा usnic_uiom_पूर्णांकerval_node *
usnic_uiom_पूर्णांकerval_tree_iter_next(काष्ठा usnic_uiom_पूर्णांकerval_node *node,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ last);
/*
 * Inserts अणुstart...lastपूर्ण पूर्णांकo अणुrootपूर्ण.  If there are overlaps,
 * nodes will be broken up and merged
 */
पूर्णांक usnic_uiom_insert_पूर्णांकerval(काष्ठा rb_root_cached *root,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ last,
				पूर्णांक flags);
/*
 * Removed अणुstart...lastपूर्ण from अणुrootपूर्ण.  The nodes हटाओd are वापसed in
 * 'removed.' The caller is responsibile क्रम मुक्तing memory of nodes in
 * 'removed.'
 */
व्योम usnic_uiom_हटाओ_पूर्णांकerval(काष्ठा rb_root_cached *root,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ last,
				काष्ठा list_head *हटाओd);
/*
 * Returns अणुstart...lastपूर्ण - अणुrootपूर्ण (relative complement of अणुstart...lastपूर्ण in
 * अणुrootपूर्ण) in dअगरf_set sorted ascendingly
 */
पूर्णांक usnic_uiom_get_पूर्णांकervals_dअगरf(अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ last, पूर्णांक flags,
					पूर्णांक flag_mask,
					काष्ठा rb_root_cached *root,
					काष्ठा list_head *dअगरf_set);
/* Call this to मुक्त dअगरf_set वापसed by usnic_uiom_get_पूर्णांकervals_dअगरf */
व्योम usnic_uiom_put_पूर्णांकerval_set(काष्ठा list_head *पूर्णांकervals);
#पूर्ण_अगर /* USNIC_UIOM_INTERVAL_TREE_H_ */

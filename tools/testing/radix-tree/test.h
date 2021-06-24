<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/gfp.h>
#समावेश <linux/types.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/rcupdate.h>

काष्ठा item अणु
	काष्ठा rcu_head	rcu_head;
	अचिन्हित दीर्घ index;
	अचिन्हित पूर्णांक order;
पूर्ण;

काष्ठा item *item_create(अचिन्हित दीर्घ index, अचिन्हित पूर्णांक order);
पूर्णांक item_insert(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index);
व्योम item_sanity(काष्ठा item *item, अचिन्हित दीर्घ index);
व्योम item_मुक्त(काष्ठा item *item, अचिन्हित दीर्घ index);
पूर्णांक item_delete(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index);
पूर्णांक item_delete_rcu(काष्ठा xarray *xa, अचिन्हित दीर्घ index);
काष्ठा item *item_lookup(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index);

व्योम item_check_present(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index);
व्योम item_check_असलent(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index);
व्योम item_gang_check_present(काष्ठा radix_tree_root *root,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr,
			पूर्णांक chunk, पूर्णांक hop);
व्योम item_full_scan(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ nr, पूर्णांक chunk);
व्योम item_समाप्त_tree(काष्ठा radix_tree_root *root);

पूर्णांक tag_tagged_items(काष्ठा xarray *, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		अचिन्हित batch, xa_mark_t अगरtag, xa_mark_t thentag);

व्योम xarray_tests(व्योम);
व्योम tag_check(व्योम);
व्योम multiorder_checks(व्योम);
व्योम iteration_test(अचिन्हित order, अचिन्हित duration);
व्योम iteration_test2(अचिन्हित duration);
व्योम benchmark(व्योम);
व्योम idr_checks(व्योम);
व्योम ida_tests(व्योम);

काष्ठा item *
item_tag_set(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index, पूर्णांक tag);
काष्ठा item *
item_tag_clear(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index, पूर्णांक tag);
पूर्णांक item_tag_get(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index, पूर्णांक tag);
व्योम tree_verअगरy_min_height(काष्ठा radix_tree_root *root, पूर्णांक maxindex);
व्योम verअगरy_tag_consistency(काष्ठा radix_tree_root *root, अचिन्हित पूर्णांक tag);

बाह्य पूर्णांक nr_allocated;

/* Normally निजी parts of lib/radix-tree.c */
काष्ठा radix_tree_node *entry_to_node(व्योम *ptr);
व्योम radix_tree_dump(काष्ठा radix_tree_root *root);
पूर्णांक root_tag_get(काष्ठा radix_tree_root *root, अचिन्हित पूर्णांक tag);
अचिन्हित दीर्घ node_maxindex(काष्ठा radix_tree_node *);
अचिन्हित दीर्घ shअगरt_maxindex(अचिन्हित पूर्णांक shअगरt);
पूर्णांक radix_tree_cpu_dead(अचिन्हित पूर्णांक cpu);
बाह्य काष्ठा radix_tree_preload radix_tree_preloads;

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/पूर्णांकerval_tree.c - पूर्णांकerval tree क्रम mapping->i_mmap
 *
 * Copyright (C) 2012, Michel Lespinasse <walken@google.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/rmap.h>
#समावेश <linux/पूर्णांकerval_tree_generic.h>

अटल अंतरभूत अचिन्हित दीर्घ vma_start_pgoff(काष्ठा vm_area_काष्ठा *v)
अणु
	वापस v->vm_pgoff;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vma_last_pgoff(काष्ठा vm_area_काष्ठा *v)
अणु
	वापस v->vm_pgoff + vma_pages(v) - 1;
पूर्ण

INTERVAL_TREE_DEFINE(काष्ठा vm_area_काष्ठा, shared.rb,
		     अचिन्हित दीर्घ, shared.rb_subtree_last,
		     vma_start_pgoff, vma_last_pgoff, /* empty */, vma_पूर्णांकerval_tree)

/* Insert node immediately after prev in the पूर्णांकerval tree */
व्योम vma_पूर्णांकerval_tree_insert_after(काष्ठा vm_area_काष्ठा *node,
				    काष्ठा vm_area_काष्ठा *prev,
				    काष्ठा rb_root_cached *root)
अणु
	काष्ठा rb_node **link;
	काष्ठा vm_area_काष्ठा *parent;
	अचिन्हित दीर्घ last = vma_last_pgoff(node);

	VM_BUG_ON_VMA(vma_start_pgoff(node) != vma_start_pgoff(prev), node);

	अगर (!prev->shared.rb.rb_right) अणु
		parent = prev;
		link = &prev->shared.rb.rb_right;
	पूर्ण अन्यथा अणु
		parent = rb_entry(prev->shared.rb.rb_right,
				  काष्ठा vm_area_काष्ठा, shared.rb);
		अगर (parent->shared.rb_subtree_last < last)
			parent->shared.rb_subtree_last = last;
		जबतक (parent->shared.rb.rb_left) अणु
			parent = rb_entry(parent->shared.rb.rb_left,
				काष्ठा vm_area_काष्ठा, shared.rb);
			अगर (parent->shared.rb_subtree_last < last)
				parent->shared.rb_subtree_last = last;
		पूर्ण
		link = &parent->shared.rb.rb_left;
	पूर्ण

	node->shared.rb_subtree_last = last;
	rb_link_node(&node->shared.rb, &parent->shared.rb, link);
	rb_insert_augmented(&node->shared.rb, &root->rb_root,
			    &vma_पूर्णांकerval_tree_augment);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ avc_start_pgoff(काष्ठा anon_vma_chain *avc)
अणु
	वापस vma_start_pgoff(avc->vma);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ avc_last_pgoff(काष्ठा anon_vma_chain *avc)
अणु
	वापस vma_last_pgoff(avc->vma);
पूर्ण

INTERVAL_TREE_DEFINE(काष्ठा anon_vma_chain, rb, अचिन्हित दीर्घ, rb_subtree_last,
		     avc_start_pgoff, avc_last_pgoff,
		     अटल अंतरभूत, __anon_vma_पूर्णांकerval_tree)

व्योम anon_vma_पूर्णांकerval_tree_insert(काष्ठा anon_vma_chain *node,
				   काष्ठा rb_root_cached *root)
अणु
#अगर_घोषित CONFIG_DEBUG_VM_RB
	node->cached_vma_start = avc_start_pgoff(node);
	node->cached_vma_last = avc_last_pgoff(node);
#पूर्ण_अगर
	__anon_vma_पूर्णांकerval_tree_insert(node, root);
पूर्ण

व्योम anon_vma_पूर्णांकerval_tree_हटाओ(काष्ठा anon_vma_chain *node,
				   काष्ठा rb_root_cached *root)
अणु
	__anon_vma_पूर्णांकerval_tree_हटाओ(node, root);
पूर्ण

काष्ठा anon_vma_chain *
anon_vma_पूर्णांकerval_tree_iter_first(काष्ठा rb_root_cached *root,
				  अचिन्हित दीर्घ first, अचिन्हित दीर्घ last)
अणु
	वापस __anon_vma_पूर्णांकerval_tree_iter_first(root, first, last);
पूर्ण

काष्ठा anon_vma_chain *
anon_vma_पूर्णांकerval_tree_iter_next(काष्ठा anon_vma_chain *node,
				 अचिन्हित दीर्घ first, अचिन्हित दीर्घ last)
अणु
	वापस __anon_vma_पूर्णांकerval_tree_iter_next(node, first, last);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VM_RB
व्योम anon_vma_पूर्णांकerval_tree_verअगरy(काष्ठा anon_vma_chain *node)
अणु
	WARN_ON_ONCE(node->cached_vma_start != avc_start_pgoff(node));
	WARN_ON_ONCE(node->cached_vma_last != avc_last_pgoff(node));
पूर्ण
#पूर्ण_अगर

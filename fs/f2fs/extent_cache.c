<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * f2fs extent cache support
 *
 * Copyright (c) 2015 Motorola Mobility
 * Copyright (c) 2015 Samsung Electronics
 * Authors: Jaegeuk Kim <jaegeuk@kernel.org>
 *          Chao Yu <chao2.yu@samsung.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश <trace/events/f2fs.h>

अटल काष्ठा rb_entry *__lookup_rb_tree_fast(काष्ठा rb_entry *cached_re,
							अचिन्हित पूर्णांक ofs)
अणु
	अगर (cached_re) अणु
		अगर (cached_re->ofs <= ofs &&
				cached_re->ofs + cached_re->len > ofs) अणु
			वापस cached_re;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा rb_entry *__lookup_rb_tree_slow(काष्ठा rb_root_cached *root,
							अचिन्हित पूर्णांक ofs)
अणु
	काष्ठा rb_node *node = root->rb_root.rb_node;
	काष्ठा rb_entry *re;

	जबतक (node) अणु
		re = rb_entry(node, काष्ठा rb_entry, rb_node);

		अगर (ofs < re->ofs)
			node = node->rb_left;
		अन्यथा अगर (ofs >= re->ofs + re->len)
			node = node->rb_right;
		अन्यथा
			वापस re;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा rb_entry *f2fs_lookup_rb_tree(काष्ठा rb_root_cached *root,
				काष्ठा rb_entry *cached_re, अचिन्हित पूर्णांक ofs)
अणु
	काष्ठा rb_entry *re;

	re = __lookup_rb_tree_fast(cached_re, ofs);
	अगर (!re)
		वापस __lookup_rb_tree_slow(root, ofs);

	वापस re;
पूर्ण

काष्ठा rb_node **f2fs_lookup_rb_tree_ext(काष्ठा f2fs_sb_info *sbi,
					काष्ठा rb_root_cached *root,
					काष्ठा rb_node **parent,
					अचिन्हित दीर्घ दीर्घ key, bool *lefपंचांगost)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_entry *re;

	जबतक (*p) अणु
		*parent = *p;
		re = rb_entry(*parent, काष्ठा rb_entry, rb_node);

		अगर (key < re->key) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अणु
			p = &(*p)->rb_right;
			*lefपंचांगost = false;
		पूर्ण
	पूर्ण

	वापस p;
पूर्ण

काष्ठा rb_node **f2fs_lookup_rb_tree_क्रम_insert(काष्ठा f2fs_sb_info *sbi,
				काष्ठा rb_root_cached *root,
				काष्ठा rb_node **parent,
				अचिन्हित पूर्णांक ofs, bool *lefपंचांगost)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_entry *re;

	जबतक (*p) अणु
		*parent = *p;
		re = rb_entry(*parent, काष्ठा rb_entry, rb_node);

		अगर (ofs < re->ofs) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (ofs >= re->ofs + re->len) अणु
			p = &(*p)->rb_right;
			*lefपंचांगost = false;
		पूर्ण अन्यथा अणु
			f2fs_bug_on(sbi, 1);
		पूर्ण
	पूर्ण

	वापस p;
पूर्ण

/*
 * lookup rb entry in position of @ofs in rb-tree,
 * अगर hit, वापस the entry, otherwise, वापस शून्य
 * @prev_ex: extent beक्रमe ofs
 * @next_ex: extent after ofs
 * @insert_p: insert poपूर्णांक क्रम new extent at ofs
 * in order to simpfy the insertion after.
 * tree must stay unchanged between lookup and insertion.
 */
काष्ठा rb_entry *f2fs_lookup_rb_tree_ret(काष्ठा rb_root_cached *root,
				काष्ठा rb_entry *cached_re,
				अचिन्हित पूर्णांक ofs,
				काष्ठा rb_entry **prev_entry,
				काष्ठा rb_entry **next_entry,
				काष्ठा rb_node ***insert_p,
				काष्ठा rb_node **insert_parent,
				bool क्रमce, bool *lefपंचांगost)
अणु
	काष्ठा rb_node **pnode = &root->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य, *पंचांगp_node;
	काष्ठा rb_entry *re = cached_re;

	*insert_p = शून्य;
	*insert_parent = शून्य;
	*prev_entry = शून्य;
	*next_entry = शून्य;

	अगर (RB_EMPTY_ROOT(&root->rb_root))
		वापस शून्य;

	अगर (re) अणु
		अगर (re->ofs <= ofs && re->ofs + re->len > ofs)
			जाओ lookup_neighbors;
	पूर्ण

	अगर (lefपंचांगost)
		*lefपंचांगost = true;

	जबतक (*pnode) अणु
		parent = *pnode;
		re = rb_entry(*pnode, काष्ठा rb_entry, rb_node);

		अगर (ofs < re->ofs) अणु
			pnode = &(*pnode)->rb_left;
		पूर्ण अन्यथा अगर (ofs >= re->ofs + re->len) अणु
			pnode = &(*pnode)->rb_right;
			अगर (lefपंचांगost)
				*lefपंचांगost = false;
		पूर्ण अन्यथा अणु
			जाओ lookup_neighbors;
		पूर्ण
	पूर्ण

	*insert_p = pnode;
	*insert_parent = parent;

	re = rb_entry(parent, काष्ठा rb_entry, rb_node);
	पंचांगp_node = parent;
	अगर (parent && ofs > re->ofs)
		पंचांगp_node = rb_next(parent);
	*next_entry = rb_entry_safe(पंचांगp_node, काष्ठा rb_entry, rb_node);

	पंचांगp_node = parent;
	अगर (parent && ofs < re->ofs)
		पंचांगp_node = rb_prev(parent);
	*prev_entry = rb_entry_safe(पंचांगp_node, काष्ठा rb_entry, rb_node);
	वापस शून्य;

lookup_neighbors:
	अगर (ofs == re->ofs || क्रमce) अणु
		/* lookup prev node क्रम merging backward later */
		पंचांगp_node = rb_prev(&re->rb_node);
		*prev_entry = rb_entry_safe(पंचांगp_node, काष्ठा rb_entry, rb_node);
	पूर्ण
	अगर (ofs == re->ofs + re->len - 1 || क्रमce) अणु
		/* lookup next node क्रम merging frontward later */
		पंचांगp_node = rb_next(&re->rb_node);
		*next_entry = rb_entry_safe(पंचांगp_node, काष्ठा rb_entry, rb_node);
	पूर्ण
	वापस re;
पूर्ण

bool f2fs_check_rb_tree_consistence(काष्ठा f2fs_sb_info *sbi,
				काष्ठा rb_root_cached *root, bool check_key)
अणु
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	काष्ठा rb_node *cur = rb_first_cached(root), *next;
	काष्ठा rb_entry *cur_re, *next_re;

	अगर (!cur)
		वापस true;

	जबतक (cur) अणु
		next = rb_next(cur);
		अगर (!next)
			वापस true;

		cur_re = rb_entry(cur, काष्ठा rb_entry, rb_node);
		next_re = rb_entry(next, काष्ठा rb_entry, rb_node);

		अगर (check_key) अणु
			अगर (cur_re->key > next_re->key) अणु
				f2fs_info(sbi, "inconsistent rbtree, "
					"cur(%llu) next(%llu)",
					cur_re->key, next_re->key);
				वापस false;
			पूर्ण
			जाओ next;
		पूर्ण

		अगर (cur_re->ofs + cur_re->len > next_re->ofs) अणु
			f2fs_info(sbi, "inconsistent rbtree, cur(%u, %u) next(%u, %u)",
				  cur_re->ofs, cur_re->len,
				  next_re->ofs, next_re->len);
			वापस false;
		पूर्ण
next:
		cur = next;
	पूर्ण
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल काष्ठा kmem_cache *extent_tree_slab;
अटल काष्ठा kmem_cache *extent_node_slab;

अटल काष्ठा extent_node *__attach_extent_node(काष्ठा f2fs_sb_info *sbi,
				काष्ठा extent_tree *et, काष्ठा extent_info *ei,
				काष्ठा rb_node *parent, काष्ठा rb_node **p,
				bool lefपंचांगost)
अणु
	काष्ठा extent_node *en;

	en = kmem_cache_alloc(extent_node_slab, GFP_ATOMIC);
	अगर (!en)
		वापस शून्य;

	en->ei = *ei;
	INIT_LIST_HEAD(&en->list);
	en->et = et;

	rb_link_node(&en->rb_node, parent, p);
	rb_insert_color_cached(&en->rb_node, &et->root, lefपंचांगost);
	atomic_inc(&et->node_cnt);
	atomic_inc(&sbi->total_ext_node);
	वापस en;
पूर्ण

अटल व्योम __detach_extent_node(काष्ठा f2fs_sb_info *sbi,
				काष्ठा extent_tree *et, काष्ठा extent_node *en)
अणु
	rb_erase_cached(&en->rb_node, &et->root);
	atomic_dec(&et->node_cnt);
	atomic_dec(&sbi->total_ext_node);

	अगर (et->cached_en == en)
		et->cached_en = शून्य;
	kmem_cache_मुक्त(extent_node_slab, en);
पूर्ण

/*
 * Flow to release an extent_node:
 * 1. list_del_init
 * 2. __detach_extent_node
 * 3. kmem_cache_मुक्त.
 */
अटल व्योम __release_extent_node(काष्ठा f2fs_sb_info *sbi,
			काष्ठा extent_tree *et, काष्ठा extent_node *en)
अणु
	spin_lock(&sbi->extent_lock);
	f2fs_bug_on(sbi, list_empty(&en->list));
	list_del_init(&en->list);
	spin_unlock(&sbi->extent_lock);

	__detach_extent_node(sbi, et, en);
पूर्ण

अटल काष्ठा extent_tree *__grab_extent_tree(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा extent_tree *et;
	nid_t ino = inode->i_ino;

	mutex_lock(&sbi->extent_tree_lock);
	et = radix_tree_lookup(&sbi->extent_tree_root, ino);
	अगर (!et) अणु
		et = f2fs_kmem_cache_alloc(extent_tree_slab, GFP_NOFS);
		f2fs_radix_tree_insert(&sbi->extent_tree_root, ino, et);
		स_रखो(et, 0, माप(काष्ठा extent_tree));
		et->ino = ino;
		et->root = RB_ROOT_CACHED;
		et->cached_en = शून्य;
		rwlock_init(&et->lock);
		INIT_LIST_HEAD(&et->list);
		atomic_set(&et->node_cnt, 0);
		atomic_inc(&sbi->total_ext_tree);
	पूर्ण अन्यथा अणु
		atomic_dec(&sbi->total_zombie_tree);
		list_del_init(&et->list);
	पूर्ण
	mutex_unlock(&sbi->extent_tree_lock);

	/* never died until evict_inode */
	F2FS_I(inode)->extent_tree = et;

	वापस et;
पूर्ण

अटल काष्ठा extent_node *__init_extent_tree(काष्ठा f2fs_sb_info *sbi,
				काष्ठा extent_tree *et, काष्ठा extent_info *ei)
अणु
	काष्ठा rb_node **p = &et->root.rb_root.rb_node;
	काष्ठा extent_node *en;

	en = __attach_extent_node(sbi, et, ei, शून्य, p, true);
	अगर (!en)
		वापस शून्य;

	et->largest = en->ei;
	et->cached_en = en;
	वापस en;
पूर्ण

अटल अचिन्हित पूर्णांक __मुक्त_extent_tree(काष्ठा f2fs_sb_info *sbi,
					काष्ठा extent_tree *et)
अणु
	काष्ठा rb_node *node, *next;
	काष्ठा extent_node *en;
	अचिन्हित पूर्णांक count = atomic_पढ़ो(&et->node_cnt);

	node = rb_first_cached(&et->root);
	जबतक (node) अणु
		next = rb_next(node);
		en = rb_entry(node, काष्ठा extent_node, rb_node);
		__release_extent_node(sbi, et, en);
		node = next;
	पूर्ण

	वापस count - atomic_पढ़ो(&et->node_cnt);
पूर्ण

अटल व्योम __drop_largest_extent(काष्ठा extent_tree *et,
					pgoff_t fofs, अचिन्हित पूर्णांक len)
अणु
	अगर (fofs < et->largest.fofs + et->largest.len &&
			fofs + len > et->largest.fofs) अणु
		et->largest.len = 0;
		et->largest_updated = true;
	पूर्ण
पूर्ण

/* वापस true, अगर inode page is changed */
अटल व्योम __f2fs_init_extent_tree(काष्ठा inode *inode, काष्ठा page *ipage)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_extent *i_ext = ipage ? &F2FS_INODE(ipage)->i_ext : शून्य;
	काष्ठा extent_tree *et;
	काष्ठा extent_node *en;
	काष्ठा extent_info ei;

	अगर (!f2fs_may_extent_tree(inode)) अणु
		/* drop largest extent */
		अगर (i_ext && i_ext->len) अणु
			f2fs_रुको_on_page_ग_लिखोback(ipage, NODE, true, true);
			i_ext->len = 0;
			set_page_dirty(ipage);
			वापस;
		पूर्ण
		वापस;
	पूर्ण

	et = __grab_extent_tree(inode);

	अगर (!i_ext || !i_ext->len)
		वापस;

	get_extent_info(&ei, i_ext);

	ग_लिखो_lock(&et->lock);
	अगर (atomic_पढ़ो(&et->node_cnt))
		जाओ out;

	en = __init_extent_tree(sbi, et, &ei);
	अगर (en) अणु
		spin_lock(&sbi->extent_lock);
		list_add_tail(&en->list, &sbi->extent_list);
		spin_unlock(&sbi->extent_lock);
	पूर्ण
out:
	ग_लिखो_unlock(&et->lock);
पूर्ण

व्योम f2fs_init_extent_tree(काष्ठा inode *inode, काष्ठा page *ipage)
अणु
	__f2fs_init_extent_tree(inode, ipage);

	अगर (!F2FS_I(inode)->extent_tree)
		set_inode_flag(inode, FI_NO_EXTENT);
पूर्ण

अटल bool f2fs_lookup_extent_tree(काष्ठा inode *inode, pgoff_t pgofs,
							काष्ठा extent_info *ei)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा extent_tree *et = F2FS_I(inode)->extent_tree;
	काष्ठा extent_node *en;
	bool ret = false;

	f2fs_bug_on(sbi, !et);

	trace_f2fs_lookup_extent_tree_start(inode, pgofs);

	पढ़ो_lock(&et->lock);

	अगर (et->largest.fofs <= pgofs &&
			et->largest.fofs + et->largest.len > pgofs) अणु
		*ei = et->largest;
		ret = true;
		stat_inc_largest_node_hit(sbi);
		जाओ out;
	पूर्ण

	en = (काष्ठा extent_node *)f2fs_lookup_rb_tree(&et->root,
				(काष्ठा rb_entry *)et->cached_en, pgofs);
	अगर (!en)
		जाओ out;

	अगर (en == et->cached_en)
		stat_inc_cached_node_hit(sbi);
	अन्यथा
		stat_inc_rbtree_node_hit(sbi);

	*ei = en->ei;
	spin_lock(&sbi->extent_lock);
	अगर (!list_empty(&en->list)) अणु
		list_move_tail(&en->list, &sbi->extent_list);
		et->cached_en = en;
	पूर्ण
	spin_unlock(&sbi->extent_lock);
	ret = true;
out:
	stat_inc_total_hit(sbi);
	पढ़ो_unlock(&et->lock);

	trace_f2fs_lookup_extent_tree_end(inode, pgofs, ei);
	वापस ret;
पूर्ण

अटल काष्ठा extent_node *__try_merge_extent_node(काष्ठा f2fs_sb_info *sbi,
				काष्ठा extent_tree *et, काष्ठा extent_info *ei,
				काष्ठा extent_node *prev_ex,
				काष्ठा extent_node *next_ex)
अणु
	काष्ठा extent_node *en = शून्य;

	अगर (prev_ex && __is_back_mergeable(ei, &prev_ex->ei)) अणु
		prev_ex->ei.len += ei->len;
		ei = &prev_ex->ei;
		en = prev_ex;
	पूर्ण

	अगर (next_ex && __is_front_mergeable(ei, &next_ex->ei)) अणु
		next_ex->ei.fofs = ei->fofs;
		next_ex->ei.blk = ei->blk;
		next_ex->ei.len += ei->len;
		अगर (en)
			__release_extent_node(sbi, et, prev_ex);

		en = next_ex;
	पूर्ण

	अगर (!en)
		वापस शून्य;

	__try_update_largest_extent(et, en);

	spin_lock(&sbi->extent_lock);
	अगर (!list_empty(&en->list)) अणु
		list_move_tail(&en->list, &sbi->extent_list);
		et->cached_en = en;
	पूर्ण
	spin_unlock(&sbi->extent_lock);
	वापस en;
पूर्ण

अटल काष्ठा extent_node *__insert_extent_tree(काष्ठा f2fs_sb_info *sbi,
				काष्ठा extent_tree *et, काष्ठा extent_info *ei,
				काष्ठा rb_node **insert_p,
				काष्ठा rb_node *insert_parent,
				bool lefपंचांगost)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा extent_node *en = शून्य;

	अगर (insert_p && insert_parent) अणु
		parent = insert_parent;
		p = insert_p;
		जाओ करो_insert;
	पूर्ण

	lefपंचांगost = true;

	p = f2fs_lookup_rb_tree_क्रम_insert(sbi, &et->root, &parent,
						ei->fofs, &lefपंचांगost);
करो_insert:
	en = __attach_extent_node(sbi, et, ei, parent, p, lefपंचांगost);
	अगर (!en)
		वापस शून्य;

	__try_update_largest_extent(et, en);

	/* update in global extent list */
	spin_lock(&sbi->extent_lock);
	list_add_tail(&en->list, &sbi->extent_list);
	et->cached_en = en;
	spin_unlock(&sbi->extent_lock);
	वापस en;
पूर्ण

अटल व्योम f2fs_update_extent_tree_range(काष्ठा inode *inode,
				pgoff_t fofs, block_t blkaddr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा extent_tree *et = F2FS_I(inode)->extent_tree;
	काष्ठा extent_node *en = शून्य, *en1 = शून्य;
	काष्ठा extent_node *prev_en = शून्य, *next_en = शून्य;
	काष्ठा extent_info ei, dei, prev;
	काष्ठा rb_node **insert_p = शून्य, *insert_parent = शून्य;
	अचिन्हित पूर्णांक end = fofs + len;
	अचिन्हित पूर्णांक pos = (अचिन्हित पूर्णांक)fofs;
	bool updated = false;
	bool lefपंचांगost = false;

	अगर (!et)
		वापस;

	trace_f2fs_update_extent_tree_range(inode, fofs, blkaddr, len);

	ग_लिखो_lock(&et->lock);

	अगर (is_inode_flag_set(inode, FI_NO_EXTENT)) अणु
		ग_लिखो_unlock(&et->lock);
		वापस;
	पूर्ण

	prev = et->largest;
	dei.len = 0;

	/*
	 * drop largest extent beक्रमe lookup, in हाल it's alपढ़ोy
	 * been shrunk from extent tree
	 */
	__drop_largest_extent(et, fofs, len);

	/* 1. lookup first extent node in range [fofs, fofs + len - 1] */
	en = (काष्ठा extent_node *)f2fs_lookup_rb_tree_ret(&et->root,
					(काष्ठा rb_entry *)et->cached_en, fofs,
					(काष्ठा rb_entry **)&prev_en,
					(काष्ठा rb_entry **)&next_en,
					&insert_p, &insert_parent, false,
					&lefपंचांगost);
	अगर (!en)
		en = next_en;

	/* 2. invlidate all extent nodes in range [fofs, fofs + len - 1] */
	जबतक (en && en->ei.fofs < end) अणु
		अचिन्हित पूर्णांक org_end;
		पूर्णांक parts = 0;	/* # of parts current extent split पूर्णांकo */

		next_en = en1 = शून्य;

		dei = en->ei;
		org_end = dei.fofs + dei.len;
		f2fs_bug_on(sbi, pos >= org_end);

		अगर (pos > dei.fofs &&	pos - dei.fofs >= F2FS_MIN_EXTENT_LEN) अणु
			en->ei.len = pos - en->ei.fofs;
			prev_en = en;
			parts = 1;
		पूर्ण

		अगर (end < org_end && org_end - end >= F2FS_MIN_EXTENT_LEN) अणु
			अगर (parts) अणु
				set_extent_info(&ei, end,
						end - dei.fofs + dei.blk,
						org_end - end);
				en1 = __insert_extent_tree(sbi, et, &ei,
							शून्य, शून्य, true);
				next_en = en1;
			पूर्ण अन्यथा अणु
				en->ei.fofs = end;
				en->ei.blk += end - dei.fofs;
				en->ei.len -= end - dei.fofs;
				next_en = en;
			पूर्ण
			parts++;
		पूर्ण

		अगर (!next_en) अणु
			काष्ठा rb_node *node = rb_next(&en->rb_node);

			next_en = rb_entry_safe(node, काष्ठा extent_node,
						rb_node);
		पूर्ण

		अगर (parts)
			__try_update_largest_extent(et, en);
		अन्यथा
			__release_extent_node(sbi, et, en);

		/*
		 * अगर original extent is split पूर्णांकo zero or two parts, extent
		 * tree has been altered by deletion or insertion, thereक्रमe
		 * invalidate poपूर्णांकers regard to tree.
		 */
		अगर (parts != 1) अणु
			insert_p = शून्य;
			insert_parent = शून्य;
		पूर्ण
		en = next_en;
	पूर्ण

	/* 3. update extent in extent cache */
	अगर (blkaddr) अणु

		set_extent_info(&ei, fofs, blkaddr, len);
		अगर (!__try_merge_extent_node(sbi, et, &ei, prev_en, next_en))
			__insert_extent_tree(sbi, et, &ei,
					insert_p, insert_parent, lefपंचांगost);

		/* give up extent_cache, अगर split and small updates happen */
		अगर (dei.len >= 1 &&
				prev.len < F2FS_MIN_EXTENT_LEN &&
				et->largest.len < F2FS_MIN_EXTENT_LEN) अणु
			et->largest.len = 0;
			et->largest_updated = true;
			set_inode_flag(inode, FI_NO_EXTENT);
		पूर्ण
	पूर्ण

	अगर (is_inode_flag_set(inode, FI_NO_EXTENT))
		__मुक्त_extent_tree(sbi, et);

	अगर (et->largest_updated) अणु
		et->largest_updated = false;
		updated = true;
	पूर्ण

	ग_लिखो_unlock(&et->lock);

	अगर (updated)
		f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

अचिन्हित पूर्णांक f2fs_shrink_extent_tree(काष्ठा f2fs_sb_info *sbi, पूर्णांक nr_shrink)
अणु
	काष्ठा extent_tree *et, *next;
	काष्ठा extent_node *en;
	अचिन्हित पूर्णांक node_cnt = 0, tree_cnt = 0;
	पूर्णांक reमुख्यed;

	अगर (!test_opt(sbi, EXTENT_CACHE))
		वापस 0;

	अगर (!atomic_पढ़ो(&sbi->total_zombie_tree))
		जाओ मुक्त_node;

	अगर (!mutex_trylock(&sbi->extent_tree_lock))
		जाओ out;

	/* 1. हटाओ unreferenced extent tree */
	list_क्रम_each_entry_safe(et, next, &sbi->zombie_list, list) अणु
		अगर (atomic_पढ़ो(&et->node_cnt)) अणु
			ग_लिखो_lock(&et->lock);
			node_cnt += __मुक्त_extent_tree(sbi, et);
			ग_लिखो_unlock(&et->lock);
		पूर्ण
		f2fs_bug_on(sbi, atomic_पढ़ो(&et->node_cnt));
		list_del_init(&et->list);
		radix_tree_delete(&sbi->extent_tree_root, et->ino);
		kmem_cache_मुक्त(extent_tree_slab, et);
		atomic_dec(&sbi->total_ext_tree);
		atomic_dec(&sbi->total_zombie_tree);
		tree_cnt++;

		अगर (node_cnt + tree_cnt >= nr_shrink)
			जाओ unlock_out;
		cond_resched();
	पूर्ण
	mutex_unlock(&sbi->extent_tree_lock);

मुक्त_node:
	/* 2. हटाओ LRU extent entries */
	अगर (!mutex_trylock(&sbi->extent_tree_lock))
		जाओ out;

	reमुख्यed = nr_shrink - (node_cnt + tree_cnt);

	spin_lock(&sbi->extent_lock);
	क्रम (; reमुख्यed > 0; reमुख्यed--) अणु
		अगर (list_empty(&sbi->extent_list))
			अवरोध;
		en = list_first_entry(&sbi->extent_list,
					काष्ठा extent_node, list);
		et = en->et;
		अगर (!ग_लिखो_trylock(&et->lock)) अणु
			/* refresh this extent node's position in extent list */
			list_move_tail(&en->list, &sbi->extent_list);
			जारी;
		पूर्ण

		list_del_init(&en->list);
		spin_unlock(&sbi->extent_lock);

		__detach_extent_node(sbi, et, en);

		ग_लिखो_unlock(&et->lock);
		node_cnt++;
		spin_lock(&sbi->extent_lock);
	पूर्ण
	spin_unlock(&sbi->extent_lock);

unlock_out:
	mutex_unlock(&sbi->extent_tree_lock);
out:
	trace_f2fs_shrink_extent_tree(sbi, node_cnt, tree_cnt);

	वापस node_cnt + tree_cnt;
पूर्ण

अचिन्हित पूर्णांक f2fs_destroy_extent_node(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा extent_tree *et = F2FS_I(inode)->extent_tree;
	अचिन्हित पूर्णांक node_cnt = 0;

	अगर (!et || !atomic_पढ़ो(&et->node_cnt))
		वापस 0;

	ग_लिखो_lock(&et->lock);
	node_cnt = __मुक्त_extent_tree(sbi, et);
	ग_लिखो_unlock(&et->lock);

	वापस node_cnt;
पूर्ण

व्योम f2fs_drop_extent_tree(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा extent_tree *et = F2FS_I(inode)->extent_tree;
	bool updated = false;

	अगर (!f2fs_may_extent_tree(inode))
		वापस;

	set_inode_flag(inode, FI_NO_EXTENT);

	ग_लिखो_lock(&et->lock);
	__मुक्त_extent_tree(sbi, et);
	अगर (et->largest.len) अणु
		et->largest.len = 0;
		updated = true;
	पूर्ण
	ग_लिखो_unlock(&et->lock);
	अगर (updated)
		f2fs_mark_inode_dirty_sync(inode, true);
पूर्ण

व्योम f2fs_destroy_extent_tree(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा extent_tree *et = F2FS_I(inode)->extent_tree;
	अचिन्हित पूर्णांक node_cnt = 0;

	अगर (!et)
		वापस;

	अगर (inode->i_nlink && !is_bad_inode(inode) &&
					atomic_पढ़ो(&et->node_cnt)) अणु
		mutex_lock(&sbi->extent_tree_lock);
		list_add_tail(&et->list, &sbi->zombie_list);
		atomic_inc(&sbi->total_zombie_tree);
		mutex_unlock(&sbi->extent_tree_lock);
		वापस;
	पूर्ण

	/* मुक्त all extent info beदीर्घ to this extent tree */
	node_cnt = f2fs_destroy_extent_node(inode);

	/* delete extent tree entry in radix tree */
	mutex_lock(&sbi->extent_tree_lock);
	f2fs_bug_on(sbi, atomic_पढ़ो(&et->node_cnt));
	radix_tree_delete(&sbi->extent_tree_root, inode->i_ino);
	kmem_cache_मुक्त(extent_tree_slab, et);
	atomic_dec(&sbi->total_ext_tree);
	mutex_unlock(&sbi->extent_tree_lock);

	F2FS_I(inode)->extent_tree = शून्य;

	trace_f2fs_destroy_extent_tree(inode, node_cnt);
पूर्ण

bool f2fs_lookup_extent_cache(काष्ठा inode *inode, pgoff_t pgofs,
					काष्ठा extent_info *ei)
अणु
	अगर (!f2fs_may_extent_tree(inode))
		वापस false;

	वापस f2fs_lookup_extent_tree(inode, pgofs, ei);
पूर्ण

व्योम f2fs_update_extent_cache(काष्ठा dnode_of_data *dn)
अणु
	pgoff_t fofs;
	block_t blkaddr;

	अगर (!f2fs_may_extent_tree(dn->inode))
		वापस;

	अगर (dn->data_blkaddr == NEW_ADDR)
		blkaddr = शून्य_ADDR;
	अन्यथा
		blkaddr = dn->data_blkaddr;

	fofs = f2fs_start_bidx_of_node(ofs_of_node(dn->node_page), dn->inode) +
								dn->ofs_in_node;
	f2fs_update_extent_tree_range(dn->inode, fofs, blkaddr, 1);
पूर्ण

व्योम f2fs_update_extent_cache_range(काष्ठा dnode_of_data *dn,
				pgoff_t fofs, block_t blkaddr, अचिन्हित पूर्णांक len)

अणु
	अगर (!f2fs_may_extent_tree(dn->inode))
		वापस;

	f2fs_update_extent_tree_range(dn->inode, fofs, blkaddr, len);
पूर्ण

व्योम f2fs_init_extent_cache_info(काष्ठा f2fs_sb_info *sbi)
अणु
	INIT_RADIX_TREE(&sbi->extent_tree_root, GFP_NOIO);
	mutex_init(&sbi->extent_tree_lock);
	INIT_LIST_HEAD(&sbi->extent_list);
	spin_lock_init(&sbi->extent_lock);
	atomic_set(&sbi->total_ext_tree, 0);
	INIT_LIST_HEAD(&sbi->zombie_list);
	atomic_set(&sbi->total_zombie_tree, 0);
	atomic_set(&sbi->total_ext_node, 0);
पूर्ण

पूर्णांक __init f2fs_create_extent_cache(व्योम)
अणु
	extent_tree_slab = f2fs_kmem_cache_create("f2fs_extent_tree",
			माप(काष्ठा extent_tree));
	अगर (!extent_tree_slab)
		वापस -ENOMEM;
	extent_node_slab = f2fs_kmem_cache_create("f2fs_extent_node",
			माप(काष्ठा extent_node));
	अगर (!extent_node_slab) अणु
		kmem_cache_destroy(extent_tree_slab);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम f2fs_destroy_extent_cache(व्योम)
अणु
	kmem_cache_destroy(extent_node_slab);
	kmem_cache_destroy(extent_tree_slab);
पूर्ण

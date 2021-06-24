<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "tree-mod-log.h"
#समावेश "disk-io.h"

काष्ठा tree_mod_root अणु
	u64 logical;
	u8 level;
पूर्ण;

काष्ठा tree_mod_elem अणु
	काष्ठा rb_node node;
	u64 logical;
	u64 seq;
	क्रमागत btrfs_mod_log_op op;

	/*
	 * This is used क्रम BTRFS_MOD_LOG_KEY_* and BTRFS_MOD_LOG_MOVE_KEYS
	 * operations.
	 */
	पूर्णांक slot;

	/* This is used क्रम BTRFS_MOD_LOG_KEY* and BTRFS_MOD_LOG_ROOT_REPLACE. */
	u64 generation;

	/* Those are used क्रम op == BTRFS_MOD_LOG_KEY_अणुREPLACE,REMOVEपूर्ण. */
	काष्ठा btrfs_disk_key key;
	u64 blockptr;

	/* This is used क्रम op == BTRFS_MOD_LOG_MOVE_KEYS. */
	काष्ठा अणु
		पूर्णांक dst_slot;
		पूर्णांक nr_items;
	पूर्ण move;

	/* This is used क्रम op == BTRFS_MOD_LOG_ROOT_REPLACE. */
	काष्ठा tree_mod_root old_root;
पूर्ण;

/*
 * Pull a new tree mod seq number क्रम our operation.
 */
अटल अंतरभूत u64 btrfs_inc_tree_mod_seq(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस atomic64_inc_वापस(&fs_info->tree_mod_seq);
पूर्ण

/*
 * This adds a new blocker to the tree mod log's blocker list अगर the @elem
 * passed करोes not alपढ़ोy have a sequence number set. So when a caller expects
 * to record tree modअगरications, it should ensure to set elem->seq to zero
 * beक्रमe calling btrfs_get_tree_mod_seq.
 * Returns a fresh, unused tree log modअगरication sequence number, even अगर no new
 * blocker was added.
 */
u64 btrfs_get_tree_mod_seq(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_seq_list *elem)
अणु
	ग_लिखो_lock(&fs_info->tree_mod_log_lock);
	अगर (!elem->seq) अणु
		elem->seq = btrfs_inc_tree_mod_seq(fs_info);
		list_add_tail(&elem->list, &fs_info->tree_mod_seq_list);
		set_bit(BTRFS_FS_TREE_MOD_LOG_USERS, &fs_info->flags);
	पूर्ण
	ग_लिखो_unlock(&fs_info->tree_mod_log_lock);

	वापस elem->seq;
पूर्ण

व्योम btrfs_put_tree_mod_seq(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_seq_list *elem)
अणु
	काष्ठा rb_root *पंचांग_root;
	काष्ठा rb_node *node;
	काष्ठा rb_node *next;
	काष्ठा tree_mod_elem *पंचांग;
	u64 min_seq = BTRFS_SEQ_LAST;
	u64 seq_putting = elem->seq;

	अगर (!seq_putting)
		वापस;

	ग_लिखो_lock(&fs_info->tree_mod_log_lock);
	list_del(&elem->list);
	elem->seq = 0;

	अगर (list_empty(&fs_info->tree_mod_seq_list)) अणु
		clear_bit(BTRFS_FS_TREE_MOD_LOG_USERS, &fs_info->flags);
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_seq_list *first;

		first = list_first_entry(&fs_info->tree_mod_seq_list,
					 काष्ठा btrfs_seq_list, list);
		अगर (seq_putting > first->seq) अणु
			/*
			 * Blocker with lower sequence number exists, we cannot
			 * हटाओ anything from the log.
			 */
			ग_लिखो_unlock(&fs_info->tree_mod_log_lock);
			वापस;
		पूर्ण
		min_seq = first->seq;
	पूर्ण

	/*
	 * Anything that's lower than the lowest existing (पढ़ो: blocked)
	 * sequence number can be हटाओd from the tree.
	 */
	पंचांग_root = &fs_info->tree_mod_log;
	क्रम (node = rb_first(पंचांग_root); node; node = next) अणु
		next = rb_next(node);
		पंचांग = rb_entry(node, काष्ठा tree_mod_elem, node);
		अगर (पंचांग->seq >= min_seq)
			जारी;
		rb_erase(node, पंचांग_root);
		kमुक्त(पंचांग);
	पूर्ण
	ग_लिखो_unlock(&fs_info->tree_mod_log_lock);
पूर्ण

/*
 * Key order of the log:
 *       node/leaf start address -> sequence
 *
 * The 'start address' is the logical address of the *new* root node क्रम root
 * replace operations, or the logical address of the affected block क्रम all
 * other operations.
 */
अटल noअंतरभूत पूर्णांक tree_mod_log_insert(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा tree_mod_elem *पंचांग)
अणु
	काष्ठा rb_root *पंचांग_root;
	काष्ठा rb_node **new;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा tree_mod_elem *cur;

	lockdep_निश्चित_held_ग_लिखो(&fs_info->tree_mod_log_lock);

	पंचांग->seq = btrfs_inc_tree_mod_seq(fs_info);

	पंचांग_root = &fs_info->tree_mod_log;
	new = &पंचांग_root->rb_node;
	जबतक (*new) अणु
		cur = rb_entry(*new, काष्ठा tree_mod_elem, node);
		parent = *new;
		अगर (cur->logical < पंचांग->logical)
			new = &((*new)->rb_left);
		अन्यथा अगर (cur->logical > पंचांग->logical)
			new = &((*new)->rb_right);
		अन्यथा अगर (cur->seq < पंचांग->seq)
			new = &((*new)->rb_left);
		अन्यथा अगर (cur->seq > पंचांग->seq)
			new = &((*new)->rb_right);
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	rb_link_node(&पंचांग->node, parent, new);
	rb_insert_color(&पंचांग->node, पंचांग_root);
	वापस 0;
पूर्ण

/*
 * Determines अगर logging can be omitted. Returns true अगर it can. Otherwise, it
 * वापसs false with the tree_mod_log_lock acquired. The caller must hold
 * this until all tree mod log insertions are recorded in the rb tree and then
 * ग_लिखो unlock fs_info::tree_mod_log_lock.
 */
अटल अंतरभूत bool tree_mod_करोnt_log(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा extent_buffer *eb)
अणु
	अगर (!test_bit(BTRFS_FS_TREE_MOD_LOG_USERS, &fs_info->flags))
		वापस true;
	अगर (eb && btrfs_header_level(eb) == 0)
		वापस true;

	ग_लिखो_lock(&fs_info->tree_mod_log_lock);
	अगर (list_empty(&(fs_info)->tree_mod_seq_list)) अणु
		ग_लिखो_unlock(&fs_info->tree_mod_log_lock);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Similar to tree_mod_करोnt_log, but करोesn't acquire any locks. */
अटल अंतरभूत bool tree_mod_need_log(स्थिर काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा extent_buffer *eb)
अणु
	अगर (!test_bit(BTRFS_FS_TREE_MOD_LOG_USERS, &fs_info->flags))
		वापस false;
	अगर (eb && btrfs_header_level(eb) == 0)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा tree_mod_elem *alloc_tree_mod_elem(काष्ठा extent_buffer *eb,
						 पूर्णांक slot,
						 क्रमागत btrfs_mod_log_op op,
						 gfp_t flags)
अणु
	काष्ठा tree_mod_elem *पंचांग;

	पंचांग = kzalloc(माप(*पंचांग), flags);
	अगर (!पंचांग)
		वापस शून्य;

	पंचांग->logical = eb->start;
	अगर (op != BTRFS_MOD_LOG_KEY_ADD) अणु
		btrfs_node_key(eb, &पंचांग->key, slot);
		पंचांग->blockptr = btrfs_node_blockptr(eb, slot);
	पूर्ण
	पंचांग->op = op;
	पंचांग->slot = slot;
	पंचांग->generation = btrfs_node_ptr_generation(eb, slot);
	RB_CLEAR_NODE(&पंचांग->node);

	वापस पंचांग;
पूर्ण

पूर्णांक btrfs_tree_mod_log_insert_key(काष्ठा extent_buffer *eb, पूर्णांक slot,
				  क्रमागत btrfs_mod_log_op op, gfp_t flags)
अणु
	काष्ठा tree_mod_elem *पंचांग;
	पूर्णांक ret;

	अगर (!tree_mod_need_log(eb->fs_info, eb))
		वापस 0;

	पंचांग = alloc_tree_mod_elem(eb, slot, op, flags);
	अगर (!पंचांग)
		वापस -ENOMEM;

	अगर (tree_mod_करोnt_log(eb->fs_info, eb)) अणु
		kमुक्त(पंचांग);
		वापस 0;
	पूर्ण

	ret = tree_mod_log_insert(eb->fs_info, पंचांग);
	ग_लिखो_unlock(&eb->fs_info->tree_mod_log_lock);
	अगर (ret)
		kमुक्त(पंचांग);

	वापस ret;
पूर्ण

पूर्णांक btrfs_tree_mod_log_insert_move(काष्ठा extent_buffer *eb,
				   पूर्णांक dst_slot, पूर्णांक src_slot,
				   पूर्णांक nr_items)
अणु
	काष्ठा tree_mod_elem *पंचांग = शून्य;
	काष्ठा tree_mod_elem **पंचांग_list = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक i;
	bool locked = false;

	अगर (!tree_mod_need_log(eb->fs_info, eb))
		वापस 0;

	पंचांग_list = kसुस्मृति(nr_items, माप(काष्ठा tree_mod_elem *), GFP_NOFS);
	अगर (!पंचांग_list)
		वापस -ENOMEM;

	पंचांग = kzalloc(माप(*पंचांग), GFP_NOFS);
	अगर (!पंचांग) अणु
		ret = -ENOMEM;
		जाओ मुक्त_पंचांगs;
	पूर्ण

	पंचांग->logical = eb->start;
	पंचांग->slot = src_slot;
	पंचांग->move.dst_slot = dst_slot;
	पंचांग->move.nr_items = nr_items;
	पंचांग->op = BTRFS_MOD_LOG_MOVE_KEYS;

	क्रम (i = 0; i + dst_slot < src_slot && i < nr_items; i++) अणु
		पंचांग_list[i] = alloc_tree_mod_elem(eb, i + dst_slot,
				BTRFS_MOD_LOG_KEY_REMOVE_WHILE_MOVING, GFP_NOFS);
		अगर (!पंचांग_list[i]) अणु
			ret = -ENOMEM;
			जाओ मुक्त_पंचांगs;
		पूर्ण
	पूर्ण

	अगर (tree_mod_करोnt_log(eb->fs_info, eb))
		जाओ मुक्त_पंचांगs;
	locked = true;

	/*
	 * When we override something during the move, we log these removals.
	 * This can only happen when we move towards the beginning of the
	 * buffer, i.e. dst_slot < src_slot.
	 */
	क्रम (i = 0; i + dst_slot < src_slot && i < nr_items; i++) अणु
		ret = tree_mod_log_insert(eb->fs_info, पंचांग_list[i]);
		अगर (ret)
			जाओ मुक्त_पंचांगs;
	पूर्ण

	ret = tree_mod_log_insert(eb->fs_info, पंचांग);
	अगर (ret)
		जाओ मुक्त_पंचांगs;
	ग_लिखो_unlock(&eb->fs_info->tree_mod_log_lock);
	kमुक्त(पंचांग_list);

	वापस 0;

मुक्त_पंचांगs:
	क्रम (i = 0; i < nr_items; i++) अणु
		अगर (पंचांग_list[i] && !RB_EMPTY_NODE(&पंचांग_list[i]->node))
			rb_erase(&पंचांग_list[i]->node, &eb->fs_info->tree_mod_log);
		kमुक्त(पंचांग_list[i]);
	पूर्ण
	अगर (locked)
		ग_लिखो_unlock(&eb->fs_info->tree_mod_log_lock);
	kमुक्त(पंचांग_list);
	kमुक्त(पंचांग);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक tree_mod_log_मुक्त_eb(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा tree_mod_elem **पंचांग_list,
				       पूर्णांक nritems)
अणु
	पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = nritems - 1; i >= 0; i--) अणु
		ret = tree_mod_log_insert(fs_info, पंचांग_list[i]);
		अगर (ret) अणु
			क्रम (j = nritems - 1; j > i; j--)
				rb_erase(&पंचांग_list[j]->node,
					 &fs_info->tree_mod_log);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btrfs_tree_mod_log_insert_root(काष्ठा extent_buffer *old_root,
				   काष्ठा extent_buffer *new_root,
				   bool log_removal)
अणु
	काष्ठा btrfs_fs_info *fs_info = old_root->fs_info;
	काष्ठा tree_mod_elem *पंचांग = शून्य;
	काष्ठा tree_mod_elem **पंचांग_list = शून्य;
	पूर्णांक nritems = 0;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!tree_mod_need_log(fs_info, शून्य))
		वापस 0;

	अगर (log_removal && btrfs_header_level(old_root) > 0) अणु
		nritems = btrfs_header_nritems(old_root);
		पंचांग_list = kसुस्मृति(nritems, माप(काष्ठा tree_mod_elem *),
				  GFP_NOFS);
		अगर (!पंचांग_list) अणु
			ret = -ENOMEM;
			जाओ मुक्त_पंचांगs;
		पूर्ण
		क्रम (i = 0; i < nritems; i++) अणु
			पंचांग_list[i] = alloc_tree_mod_elem(old_root, i,
			    BTRFS_MOD_LOG_KEY_REMOVE_WHILE_FREEING, GFP_NOFS);
			अगर (!पंचांग_list[i]) अणु
				ret = -ENOMEM;
				जाओ मुक्त_पंचांगs;
			पूर्ण
		पूर्ण
	पूर्ण

	पंचांग = kzalloc(माप(*पंचांग), GFP_NOFS);
	अगर (!पंचांग) अणु
		ret = -ENOMEM;
		जाओ मुक्त_पंचांगs;
	पूर्ण

	पंचांग->logical = new_root->start;
	पंचांग->old_root.logical = old_root->start;
	पंचांग->old_root.level = btrfs_header_level(old_root);
	पंचांग->generation = btrfs_header_generation(old_root);
	पंचांग->op = BTRFS_MOD_LOG_ROOT_REPLACE;

	अगर (tree_mod_करोnt_log(fs_info, शून्य))
		जाओ मुक्त_पंचांगs;

	अगर (पंचांग_list)
		ret = tree_mod_log_मुक्त_eb(fs_info, पंचांग_list, nritems);
	अगर (!ret)
		ret = tree_mod_log_insert(fs_info, पंचांग);

	ग_लिखो_unlock(&fs_info->tree_mod_log_lock);
	अगर (ret)
		जाओ मुक्त_पंचांगs;
	kमुक्त(पंचांग_list);

	वापस ret;

मुक्त_पंचांगs:
	अगर (पंचांग_list) अणु
		क्रम (i = 0; i < nritems; i++)
			kमुक्त(पंचांग_list[i]);
		kमुक्त(पंचांग_list);
	पूर्ण
	kमुक्त(पंचांग);

	वापस ret;
पूर्ण

अटल काष्ठा tree_mod_elem *__tree_mod_log_search(काष्ठा btrfs_fs_info *fs_info,
						   u64 start, u64 min_seq,
						   bool smallest)
अणु
	काष्ठा rb_root *पंचांग_root;
	काष्ठा rb_node *node;
	काष्ठा tree_mod_elem *cur = शून्य;
	काष्ठा tree_mod_elem *found = शून्य;

	पढ़ो_lock(&fs_info->tree_mod_log_lock);
	पंचांग_root = &fs_info->tree_mod_log;
	node = पंचांग_root->rb_node;
	जबतक (node) अणु
		cur = rb_entry(node, काष्ठा tree_mod_elem, node);
		अगर (cur->logical < start) अणु
			node = node->rb_left;
		पूर्ण अन्यथा अगर (cur->logical > start) अणु
			node = node->rb_right;
		पूर्ण अन्यथा अगर (cur->seq < min_seq) अणु
			node = node->rb_left;
		पूर्ण अन्यथा अगर (!smallest) अणु
			/* We want the node with the highest seq */
			अगर (found)
				BUG_ON(found->seq > cur->seq);
			found = cur;
			node = node->rb_left;
		पूर्ण अन्यथा अगर (cur->seq > min_seq) अणु
			/* We want the node with the smallest seq */
			अगर (found)
				BUG_ON(found->seq < cur->seq);
			found = cur;
			node = node->rb_right;
		पूर्ण अन्यथा अणु
			found = cur;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&fs_info->tree_mod_log_lock);

	वापस found;
पूर्ण

/*
 * This वापसs the element from the log with the smallest समय sequence
 * value that's in the log (the oldest log item). Any element with a समय
 * sequence lower than min_seq will be ignored.
 */
अटल काष्ठा tree_mod_elem *tree_mod_log_search_oldest(काष्ठा btrfs_fs_info *fs_info,
							u64 start, u64 min_seq)
अणु
	वापस __tree_mod_log_search(fs_info, start, min_seq, true);
पूर्ण

/*
 * This वापसs the element from the log with the largest समय sequence
 * value that's in the log (the most recent log item). Any element with
 * a समय sequence lower than min_seq will be ignored.
 */
अटल काष्ठा tree_mod_elem *tree_mod_log_search(काष्ठा btrfs_fs_info *fs_info,
						 u64 start, u64 min_seq)
अणु
	वापस __tree_mod_log_search(fs_info, start, min_seq, false);
पूर्ण

पूर्णांक btrfs_tree_mod_log_eb_copy(काष्ठा extent_buffer *dst,
			       काष्ठा extent_buffer *src,
			       अचिन्हित दीर्घ dst_offset,
			       अचिन्हित दीर्घ src_offset,
			       पूर्णांक nr_items)
अणु
	काष्ठा btrfs_fs_info *fs_info = dst->fs_info;
	पूर्णांक ret = 0;
	काष्ठा tree_mod_elem **पंचांग_list = शून्य;
	काष्ठा tree_mod_elem **पंचांग_list_add, **पंचांग_list_rem;
	पूर्णांक i;
	bool locked = false;

	अगर (!tree_mod_need_log(fs_info, शून्य))
		वापस 0;

	अगर (btrfs_header_level(dst) == 0 && btrfs_header_level(src) == 0)
		वापस 0;

	पंचांग_list = kसुस्मृति(nr_items * 2, माप(काष्ठा tree_mod_elem *),
			  GFP_NOFS);
	अगर (!पंचांग_list)
		वापस -ENOMEM;

	पंचांग_list_add = पंचांग_list;
	पंचांग_list_rem = पंचांग_list + nr_items;
	क्रम (i = 0; i < nr_items; i++) अणु
		पंचांग_list_rem[i] = alloc_tree_mod_elem(src, i + src_offset,
		    BTRFS_MOD_LOG_KEY_REMOVE, GFP_NOFS);
		अगर (!पंचांग_list_rem[i]) अणु
			ret = -ENOMEM;
			जाओ मुक्त_पंचांगs;
		पूर्ण

		पंचांग_list_add[i] = alloc_tree_mod_elem(dst, i + dst_offset,
						BTRFS_MOD_LOG_KEY_ADD, GFP_NOFS);
		अगर (!पंचांग_list_add[i]) अणु
			ret = -ENOMEM;
			जाओ मुक्त_पंचांगs;
		पूर्ण
	पूर्ण

	अगर (tree_mod_करोnt_log(fs_info, शून्य))
		जाओ मुक्त_पंचांगs;
	locked = true;

	क्रम (i = 0; i < nr_items; i++) अणु
		ret = tree_mod_log_insert(fs_info, पंचांग_list_rem[i]);
		अगर (ret)
			जाओ मुक्त_पंचांगs;
		ret = tree_mod_log_insert(fs_info, पंचांग_list_add[i]);
		अगर (ret)
			जाओ मुक्त_पंचांगs;
	पूर्ण

	ग_लिखो_unlock(&fs_info->tree_mod_log_lock);
	kमुक्त(पंचांग_list);

	वापस 0;

मुक्त_पंचांगs:
	क्रम (i = 0; i < nr_items * 2; i++) अणु
		अगर (पंचांग_list[i] && !RB_EMPTY_NODE(&पंचांग_list[i]->node))
			rb_erase(&पंचांग_list[i]->node, &fs_info->tree_mod_log);
		kमुक्त(पंचांग_list[i]);
	पूर्ण
	अगर (locked)
		ग_लिखो_unlock(&fs_info->tree_mod_log_lock);
	kमुक्त(पंचांग_list);

	वापस ret;
पूर्ण

पूर्णांक btrfs_tree_mod_log_मुक्त_eb(काष्ठा extent_buffer *eb)
अणु
	काष्ठा tree_mod_elem **पंचांग_list = शून्य;
	पूर्णांक nritems = 0;
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!tree_mod_need_log(eb->fs_info, eb))
		वापस 0;

	nritems = btrfs_header_nritems(eb);
	पंचांग_list = kसुस्मृति(nritems, माप(काष्ठा tree_mod_elem *), GFP_NOFS);
	अगर (!पंचांग_list)
		वापस -ENOMEM;

	क्रम (i = 0; i < nritems; i++) अणु
		पंचांग_list[i] = alloc_tree_mod_elem(eb, i,
		    BTRFS_MOD_LOG_KEY_REMOVE_WHILE_FREEING, GFP_NOFS);
		अगर (!पंचांग_list[i]) अणु
			ret = -ENOMEM;
			जाओ मुक्त_पंचांगs;
		पूर्ण
	पूर्ण

	अगर (tree_mod_करोnt_log(eb->fs_info, eb))
		जाओ मुक्त_पंचांगs;

	ret = tree_mod_log_मुक्त_eb(eb->fs_info, पंचांग_list, nritems);
	ग_लिखो_unlock(&eb->fs_info->tree_mod_log_lock);
	अगर (ret)
		जाओ मुक्त_पंचांगs;
	kमुक्त(पंचांग_list);

	वापस 0;

मुक्त_पंचांगs:
	क्रम (i = 0; i < nritems; i++)
		kमुक्त(पंचांग_list[i]);
	kमुक्त(पंचांग_list);

	वापस ret;
पूर्ण

/*
 * Returns the logical address of the oldest predecessor of the given root.
 * Entries older than समय_seq are ignored.
 */
अटल काष्ठा tree_mod_elem *tree_mod_log_oldest_root(काष्ठा extent_buffer *eb_root,
						      u64 समय_seq)
अणु
	काष्ठा tree_mod_elem *पंचांग;
	काष्ठा tree_mod_elem *found = शून्य;
	u64 root_logical = eb_root->start;
	bool looped = false;

	अगर (!समय_seq)
		वापस शून्य;

	/*
	 * The very last operation that's logged क्रम a root is the replacement
	 * operation (अगर it is replaced at all). This has the logical address
	 * of the *new* root, making it the very first operation that's logged
	 * क्रम this root.
	 */
	जबतक (1) अणु
		पंचांग = tree_mod_log_search_oldest(eb_root->fs_info, root_logical,
						समय_seq);
		अगर (!looped && !पंचांग)
			वापस शून्य;
		/*
		 * If there are no tree operation क्रम the oldest root, we simply
		 * वापस it. This should only happen अगर that (old) root is at
		 * level 0.
		 */
		अगर (!पंचांग)
			अवरोध;

		/*
		 * If there's an operation that's not a root replacement, we
		 * found the oldest version of our root. Normally, we'll find a
		 * BTRFS_MOD_LOG_KEY_REMOVE_WHILE_FREEING operation here.
		 */
		अगर (पंचांग->op != BTRFS_MOD_LOG_ROOT_REPLACE)
			अवरोध;

		found = पंचांग;
		root_logical = पंचांग->old_root.logical;
		looped = true;
	पूर्ण

	/* If there's no old root to वापस, वापस what we found instead */
	अगर (!found)
		found = पंचांग;

	वापस found;
पूर्ण


/*
 * पंचांग is a poपूर्णांकer to the first operation to शुरुआत within eb. Then, all
 * previous operations will be rewound (until we reach something older than
 * समय_seq).
 */
अटल व्योम tree_mod_log_शुरुआत(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा extent_buffer *eb,
				u64 समय_seq,
				काष्ठा tree_mod_elem *first_पंचांग)
अणु
	u32 n;
	काष्ठा rb_node *next;
	काष्ठा tree_mod_elem *पंचांग = first_पंचांग;
	अचिन्हित दीर्घ o_dst;
	अचिन्हित दीर्घ o_src;
	अचिन्हित दीर्घ p_size = माप(काष्ठा btrfs_key_ptr);

	n = btrfs_header_nritems(eb);
	पढ़ो_lock(&fs_info->tree_mod_log_lock);
	जबतक (पंचांग && पंचांग->seq >= समय_seq) अणु
		/*
		 * All the operations are recorded with the चालक used क्रम
		 * the modअगरication. As we're going backwards, we करो the
		 * opposite of each operation here.
		 */
		चयन (पंचांग->op) अणु
		हाल BTRFS_MOD_LOG_KEY_REMOVE_WHILE_FREEING:
			BUG_ON(पंचांग->slot < n);
			fallthrough;
		हाल BTRFS_MOD_LOG_KEY_REMOVE_WHILE_MOVING:
		हाल BTRFS_MOD_LOG_KEY_REMOVE:
			btrfs_set_node_key(eb, &पंचांग->key, पंचांग->slot);
			btrfs_set_node_blockptr(eb, पंचांग->slot, पंचांग->blockptr);
			btrfs_set_node_ptr_generation(eb, पंचांग->slot,
						      पंचांग->generation);
			n++;
			अवरोध;
		हाल BTRFS_MOD_LOG_KEY_REPLACE:
			BUG_ON(पंचांग->slot >= n);
			btrfs_set_node_key(eb, &पंचांग->key, पंचांग->slot);
			btrfs_set_node_blockptr(eb, पंचांग->slot, पंचांग->blockptr);
			btrfs_set_node_ptr_generation(eb, पंचांग->slot,
						      पंचांग->generation);
			अवरोध;
		हाल BTRFS_MOD_LOG_KEY_ADD:
			/* अगर a move operation is needed it's in the log */
			n--;
			अवरोध;
		हाल BTRFS_MOD_LOG_MOVE_KEYS:
			o_dst = btrfs_node_key_ptr_offset(पंचांग->slot);
			o_src = btrfs_node_key_ptr_offset(पंचांग->move.dst_slot);
			स_हटाओ_extent_buffer(eb, o_dst, o_src,
					      पंचांग->move.nr_items * p_size);
			अवरोध;
		हाल BTRFS_MOD_LOG_ROOT_REPLACE:
			/*
			 * This operation is special. For roots, this must be
			 * handled explicitly beक्रमe शुरुआतing.
			 * For non-roots, this operation may exist अगर the node
			 * was a root: root A -> child B; then A माला_लो empty and
			 * B is promoted to the new root. In the mod log, we'll
			 * have a root-replace operation क्रम B, a tree block
			 * that is no root. We simply ignore that operation.
			 */
			अवरोध;
		पूर्ण
		next = rb_next(&पंचांग->node);
		अगर (!next)
			अवरोध;
		पंचांग = rb_entry(next, काष्ठा tree_mod_elem, node);
		अगर (पंचांग->logical != first_पंचांग->logical)
			अवरोध;
	पूर्ण
	पढ़ो_unlock(&fs_info->tree_mod_log_lock);
	btrfs_set_header_nritems(eb, n);
पूर्ण

/*
 * Called with eb पढ़ो locked. If the buffer cannot be rewound, the same buffer
 * is वापसed. If शुरुआत operations happen, a fresh buffer is वापसed. The
 * वापसed buffer is always पढ़ो-locked. If the वापसed buffer is not the
 * input buffer, the lock on the input buffer is released and the input buffer
 * is मुक्तd (its refcount is decremented).
 */
काष्ठा extent_buffer *btrfs_tree_mod_log_शुरुआत(काष्ठा btrfs_fs_info *fs_info,
						काष्ठा btrfs_path *path,
						काष्ठा extent_buffer *eb,
						u64 समय_seq)
अणु
	काष्ठा extent_buffer *eb_rewin;
	काष्ठा tree_mod_elem *पंचांग;

	अगर (!समय_seq)
		वापस eb;

	अगर (btrfs_header_level(eb) == 0)
		वापस eb;

	पंचांग = tree_mod_log_search(fs_info, eb->start, समय_seq);
	अगर (!पंचांग)
		वापस eb;

	अगर (पंचांग->op == BTRFS_MOD_LOG_KEY_REMOVE_WHILE_FREEING) अणु
		BUG_ON(पंचांग->slot != 0);
		eb_rewin = alloc_dummy_extent_buffer(fs_info, eb->start);
		अगर (!eb_rewin) अणु
			btrfs_tree_पढ़ो_unlock(eb);
			मुक्त_extent_buffer(eb);
			वापस शून्य;
		पूर्ण
		btrfs_set_header_bytenr(eb_rewin, eb->start);
		btrfs_set_header_backref_rev(eb_rewin,
					     btrfs_header_backref_rev(eb));
		btrfs_set_header_owner(eb_rewin, btrfs_header_owner(eb));
		btrfs_set_header_level(eb_rewin, btrfs_header_level(eb));
	पूर्ण अन्यथा अणु
		eb_rewin = btrfs_clone_extent_buffer(eb);
		अगर (!eb_rewin) अणु
			btrfs_tree_पढ़ो_unlock(eb);
			मुक्त_extent_buffer(eb);
			वापस शून्य;
		पूर्ण
	पूर्ण

	btrfs_tree_पढ़ो_unlock(eb);
	मुक्त_extent_buffer(eb);

	btrfs_set_buffer_lockdep_class(btrfs_header_owner(eb_rewin),
				       eb_rewin, btrfs_header_level(eb_rewin));
	btrfs_tree_पढ़ो_lock(eb_rewin);
	tree_mod_log_शुरुआत(fs_info, eb_rewin, समय_seq, पंचांग);
	WARN_ON(btrfs_header_nritems(eb_rewin) >
		BTRFS_NODEPTRS_PER_BLOCK(fs_info));

	वापस eb_rewin;
पूर्ण

/*
 * Rewind the state of @root's root node to the given @समय_seq value.
 * If there are no changes, the current root->root_node is वापसed. If anything
 * changed in between, there's a fresh buffer allocated on which the शुरुआत
 * operations are करोne. In any हाल, the वापसed buffer is पढ़ो locked.
 * Returns शून्य on error (with no locks held).
 */
काष्ठा extent_buffer *btrfs_get_old_root(काष्ठा btrfs_root *root, u64 समय_seq)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा tree_mod_elem *पंचांग;
	काष्ठा extent_buffer *eb = शून्य;
	काष्ठा extent_buffer *eb_root;
	u64 eb_root_owner = 0;
	काष्ठा extent_buffer *old;
	काष्ठा tree_mod_root *old_root = शून्य;
	u64 old_generation = 0;
	u64 logical;
	पूर्णांक level;

	eb_root = btrfs_पढ़ो_lock_root_node(root);
	पंचांग = tree_mod_log_oldest_root(eb_root, समय_seq);
	अगर (!पंचांग)
		वापस eb_root;

	अगर (पंचांग->op == BTRFS_MOD_LOG_ROOT_REPLACE) अणु
		old_root = &पंचांग->old_root;
		old_generation = पंचांग->generation;
		logical = old_root->logical;
		level = old_root->level;
	पूर्ण अन्यथा अणु
		logical = eb_root->start;
		level = btrfs_header_level(eb_root);
	पूर्ण

	पंचांग = tree_mod_log_search(fs_info, logical, समय_seq);
	अगर (old_root && पंचांग && पंचांग->op != BTRFS_MOD_LOG_KEY_REMOVE_WHILE_FREEING) अणु
		btrfs_tree_पढ़ो_unlock(eb_root);
		मुक्त_extent_buffer(eb_root);
		old = पढ़ो_tree_block(fs_info, logical, root->root_key.objectid,
				      0, level, शून्य);
		अगर (WARN_ON(IS_ERR(old) || !extent_buffer_uptodate(old))) अणु
			अगर (!IS_ERR(old))
				मुक्त_extent_buffer(old);
			btrfs_warn(fs_info,
				   "failed to read tree block %llu from get_old_root",
				   logical);
		पूर्ण अन्यथा अणु
			काष्ठा tree_mod_elem *पंचांग2;

			btrfs_tree_पढ़ो_lock(old);
			eb = btrfs_clone_extent_buffer(old);
			/*
			 * After the lookup क्रम the most recent tree mod operation
			 * above and beक्रमe we locked and cloned the extent buffer
			 * 'old', a new tree mod log operation may have been added.
			 * So lookup क्रम a more recent one to make sure the number
			 * of mod log operations we replay is consistent with the
			 * number of items we have in the cloned extent buffer,
			 * otherwise we can hit a BUG_ON when शुरुआतing the extent
			 * buffer.
			 */
			पंचांग2 = tree_mod_log_search(fs_info, logical, समय_seq);
			btrfs_tree_पढ़ो_unlock(old);
			मुक्त_extent_buffer(old);
			ASSERT(पंचांग2);
			ASSERT(पंचांग2 == पंचांग || पंचांग2->seq > पंचांग->seq);
			अगर (!पंचांग2 || पंचांग2->seq < पंचांग->seq) अणु
				मुक्त_extent_buffer(eb);
				वापस शून्य;
			पूर्ण
			पंचांग = पंचांग2;
		पूर्ण
	पूर्ण अन्यथा अगर (old_root) अणु
		eb_root_owner = btrfs_header_owner(eb_root);
		btrfs_tree_पढ़ो_unlock(eb_root);
		मुक्त_extent_buffer(eb_root);
		eb = alloc_dummy_extent_buffer(fs_info, logical);
	पूर्ण अन्यथा अणु
		eb = btrfs_clone_extent_buffer(eb_root);
		btrfs_tree_पढ़ो_unlock(eb_root);
		मुक्त_extent_buffer(eb_root);
	पूर्ण

	अगर (!eb)
		वापस शून्य;
	अगर (old_root) अणु
		btrfs_set_header_bytenr(eb, eb->start);
		btrfs_set_header_backref_rev(eb, BTRFS_MIXED_BACKREF_REV);
		btrfs_set_header_owner(eb, eb_root_owner);
		btrfs_set_header_level(eb, old_root->level);
		btrfs_set_header_generation(eb, old_generation);
	पूर्ण
	btrfs_set_buffer_lockdep_class(btrfs_header_owner(eb), eb,
				       btrfs_header_level(eb));
	btrfs_tree_पढ़ो_lock(eb);
	अगर (पंचांग)
		tree_mod_log_शुरुआत(fs_info, eb, समय_seq, पंचांग);
	अन्यथा
		WARN_ON(btrfs_header_level(eb) != 0);
	WARN_ON(btrfs_header_nritems(eb) > BTRFS_NODEPTRS_PER_BLOCK(fs_info));

	वापस eb;
पूर्ण

पूर्णांक btrfs_old_root_level(काष्ठा btrfs_root *root, u64 समय_seq)
अणु
	काष्ठा tree_mod_elem *पंचांग;
	पूर्णांक level;
	काष्ठा extent_buffer *eb_root = btrfs_root_node(root);

	पंचांग = tree_mod_log_oldest_root(eb_root, समय_seq);
	अगर (पंचांग && पंचांग->op == BTRFS_MOD_LOG_ROOT_REPLACE)
		level = पंचांग->old_root.level;
	अन्यथा
		level = btrfs_header_level(eb_root);

	मुक्त_extent_buffer(eb_root);

	वापस level;
पूर्ण

/*
 * Return the lowest sequence number in the tree modअगरication log.
 *
 * Return the sequence number of the oldest tree modअगरication log user, which
 * corresponds to the lowest sequence number of all existing users. If there are
 * no users it वापसs 0.
 */
u64 btrfs_tree_mod_log_lowest_seq(काष्ठा btrfs_fs_info *fs_info)
अणु
	u64 ret = 0;

	पढ़ो_lock(&fs_info->tree_mod_log_lock);
	अगर (!list_empty(&fs_info->tree_mod_seq_list)) अणु
		काष्ठा btrfs_seq_list *elem;

		elem = list_first_entry(&fs_info->tree_mod_seq_list,
					काष्ठा btrfs_seq_list, list);
		ret = elem->seq;
	पूर्ण
	पढ़ो_unlock(&fs_info->tree_mod_log_lock);

	वापस ret;
पूर्ण

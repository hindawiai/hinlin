<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/block_validity.c
 *
 * Copyright (C) 2009
 * Theoकरोre Ts'o (tytso@mit.edu)
 *
 * Track which blocks in the fileप्रणाली are metadata blocks that
 * should never be used as data blocks by files or directories.
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/swap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश "ext4.h"

काष्ठा ext4_प्रणाली_zone अणु
	काष्ठा rb_node	node;
	ext4_fsblk_t	start_blk;
	अचिन्हित पूर्णांक	count;
	u32		ino;
पूर्ण;

अटल काष्ठा kmem_cache *ext4_प्रणाली_zone_cachep;

पूर्णांक __init ext4_init_प्रणाली_zone(व्योम)
अणु
	ext4_प्रणाली_zone_cachep = KMEM_CACHE(ext4_प्रणाली_zone, 0);
	अगर (ext4_प्रणाली_zone_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम ext4_निकास_प्रणाली_zone(व्योम)
अणु
	rcu_barrier();
	kmem_cache_destroy(ext4_प्रणाली_zone_cachep);
पूर्ण

अटल अंतरभूत पूर्णांक can_merge(काष्ठा ext4_प्रणाली_zone *entry1,
		     काष्ठा ext4_प्रणाली_zone *entry2)
अणु
	अगर ((entry1->start_blk + entry1->count) == entry2->start_blk &&
	    entry1->ino == entry2->ino)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम release_प्रणाली_zone(काष्ठा ext4_प्रणाली_blocks *प्रणाली_blks)
अणु
	काष्ठा ext4_प्रणाली_zone	*entry, *n;

	rbtree_postorder_क्रम_each_entry_safe(entry, n,
				&प्रणाली_blks->root, node)
		kmem_cache_मुक्त(ext4_प्रणाली_zone_cachep, entry);
पूर्ण

/*
 * Mark a range of blocks as beदीर्घing to the "system zone" --- that
 * is, fileप्रणाली metadata blocks which should never be used by
 * inodes.
 */
अटल पूर्णांक add_प्रणाली_zone(काष्ठा ext4_प्रणाली_blocks *प्रणाली_blks,
			   ext4_fsblk_t start_blk,
			   अचिन्हित पूर्णांक count, u32 ino)
अणु
	काष्ठा ext4_प्रणाली_zone *new_entry, *entry;
	काष्ठा rb_node **n = &प्रणाली_blks->root.rb_node, *node;
	काष्ठा rb_node *parent = शून्य, *new_node = शून्य;

	जबतक (*n) अणु
		parent = *n;
		entry = rb_entry(parent, काष्ठा ext4_प्रणाली_zone, node);
		अगर (start_blk < entry->start_blk)
			n = &(*n)->rb_left;
		अन्यथा अगर (start_blk >= (entry->start_blk + entry->count))
			n = &(*n)->rb_right;
		अन्यथा	/* Unexpected overlap of प्रणाली zones. */
			वापस -EFSCORRUPTED;
	पूर्ण

	new_entry = kmem_cache_alloc(ext4_प्रणाली_zone_cachep,
				     GFP_KERNEL);
	अगर (!new_entry)
		वापस -ENOMEM;
	new_entry->start_blk = start_blk;
	new_entry->count = count;
	new_entry->ino = ino;
	new_node = &new_entry->node;

	rb_link_node(new_node, parent, n);
	rb_insert_color(new_node, &प्रणाली_blks->root);

	/* Can we merge to the left? */
	node = rb_prev(new_node);
	अगर (node) अणु
		entry = rb_entry(node, काष्ठा ext4_प्रणाली_zone, node);
		अगर (can_merge(entry, new_entry)) अणु
			new_entry->start_blk = entry->start_blk;
			new_entry->count += entry->count;
			rb_erase(node, &प्रणाली_blks->root);
			kmem_cache_मुक्त(ext4_प्रणाली_zone_cachep, entry);
		पूर्ण
	पूर्ण

	/* Can we merge to the right? */
	node = rb_next(new_node);
	अगर (node) अणु
		entry = rb_entry(node, काष्ठा ext4_प्रणाली_zone, node);
		अगर (can_merge(new_entry, entry)) अणु
			new_entry->count += entry->count;
			rb_erase(node, &प्रणाली_blks->root);
			kmem_cache_मुक्त(ext4_प्रणाली_zone_cachep, entry);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम debug_prपूर्णांक_tree(काष्ठा ext4_sb_info *sbi)
अणु
	काष्ठा rb_node *node;
	काष्ठा ext4_प्रणाली_zone *entry;
	काष्ठा ext4_प्रणाली_blocks *प्रणाली_blks;
	पूर्णांक first = 1;

	prपूर्णांकk(KERN_INFO "System zones: ");
	rcu_पढ़ो_lock();
	प्रणाली_blks = rcu_dereference(sbi->s_प्रणाली_blks);
	node = rb_first(&प्रणाली_blks->root);
	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा ext4_प्रणाली_zone, node);
		prपूर्णांकk(KERN_CONT "%s%llu-%llu", first ? "" : ", ",
		       entry->start_blk, entry->start_blk + entry->count - 1);
		first = 0;
		node = rb_next(node);
	पूर्ण
	rcu_पढ़ो_unlock();
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल पूर्णांक ext4_protect_reserved_inode(काष्ठा super_block *sb,
				       काष्ठा ext4_प्रणाली_blocks *प्रणाली_blks,
				       u32 ino)
अणु
	काष्ठा inode *inode;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_map_blocks map;
	u32 i = 0, num;
	पूर्णांक err = 0, n;

	अगर ((ino < EXT4_ROOT_INO) ||
	    (ino > le32_to_cpu(sbi->s_es->s_inodes_count)))
		वापस -EINVAL;
	inode = ext4_iget(sb, ino, EXT4_IGET_SPECIAL);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);
	num = (inode->i_size + sb->s_blocksize - 1) >> sb->s_blocksize_bits;
	जबतक (i < num) अणु
		cond_resched();
		map.m_lblk = i;
		map.m_len = num - i;
		n = ext4_map_blocks(शून्य, inode, &map, 0);
		अगर (n < 0) अणु
			err = n;
			अवरोध;
		पूर्ण
		अगर (n == 0) अणु
			i++;
		पूर्ण अन्यथा अणु
			err = add_प्रणाली_zone(प्रणाली_blks, map.m_pblk, n, ino);
			अगर (err < 0) अणु
				अगर (err == -EFSCORRUPTED) अणु
					EXT4_ERROR_INODE_ERR(inode, -err,
						"blocks %llu-%llu from inode overlap system zone",
						map.m_pblk,
						map.m_pblk + map.m_len - 1);
				पूर्ण
				अवरोध;
			पूर्ण
			i += n;
		पूर्ण
	पूर्ण
	iput(inode);
	वापस err;
पूर्ण

अटल व्योम ext4_destroy_प्रणाली_zone(काष्ठा rcu_head *rcu)
अणु
	काष्ठा ext4_प्रणाली_blocks *प्रणाली_blks;

	प्रणाली_blks = container_of(rcu, काष्ठा ext4_प्रणाली_blocks, rcu);
	release_प्रणाली_zone(प्रणाली_blks);
	kमुक्त(प्रणाली_blks);
पूर्ण

/*
 * Build प्रणाली zone rbtree which is used क्रम block validity checking.
 *
 * The update of प्रणाली_blks poपूर्णांकer in this function is रक्षित by
 * sb->s_umount semaphore. However we have to be careful as we can be
 * racing with ext4_inode_block_valid() calls पढ़ोing प्रणाली_blks rbtree
 * रक्षित only by RCU. That's why we first build the rbtree and then
 * swap it in place.
 */
पूर्णांक ext4_setup_प्रणाली_zone(काष्ठा super_block *sb)
अणु
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_प्रणाली_blocks *प्रणाली_blks;
	काष्ठा ext4_group_desc *gdp;
	ext4_group_t i;
	पूर्णांक flex_size = ext4_flex_bg_size(sbi);
	पूर्णांक ret;

	प्रणाली_blks = kzalloc(माप(*प्रणाली_blks), GFP_KERNEL);
	अगर (!प्रणाली_blks)
		वापस -ENOMEM;

	क्रम (i=0; i < ngroups; i++) अणु
		cond_resched();
		अगर (ext4_bg_has_super(sb, i) &&
		    ((i < 5) || ((i % flex_size) == 0))) अणु
			ret = add_प्रणाली_zone(प्रणाली_blks,
					ext4_group_first_block_no(sb, i),
					ext4_bg_num_gdb(sb, i) + 1, 0);
			अगर (ret)
				जाओ err;
		पूर्ण
		gdp = ext4_get_group_desc(sb, i, शून्य);
		ret = add_प्रणाली_zone(प्रणाली_blks,
				ext4_block_biपंचांगap(sb, gdp), 1, 0);
		अगर (ret)
			जाओ err;
		ret = add_प्रणाली_zone(प्रणाली_blks,
				ext4_inode_biपंचांगap(sb, gdp), 1, 0);
		अगर (ret)
			जाओ err;
		ret = add_प्रणाली_zone(प्रणाली_blks,
				ext4_inode_table(sb, gdp),
				sbi->s_itb_per_group, 0);
		अगर (ret)
			जाओ err;
	पूर्ण
	अगर (ext4_has_feature_journal(sb) && sbi->s_es->s_journal_inum) अणु
		ret = ext4_protect_reserved_inode(sb, प्रणाली_blks,
				le32_to_cpu(sbi->s_es->s_journal_inum));
		अगर (ret)
			जाओ err;
	पूर्ण

	/*
	 * System blks rbtree complete, announce it once to prevent racing
	 * with ext4_inode_block_valid() accessing the rbtree at the same
	 * समय.
	 */
	rcu_assign_poपूर्णांकer(sbi->s_प्रणाली_blks, प्रणाली_blks);

	अगर (test_opt(sb, DEBUG))
		debug_prपूर्णांक_tree(sbi);
	वापस 0;
err:
	release_प्रणाली_zone(प्रणाली_blks);
	kमुक्त(प्रणाली_blks);
	वापस ret;
पूर्ण

/*
 * Called when the fileप्रणाली is unmounted or when remounting it with
 * noblock_validity specअगरied.
 *
 * The update of प्रणाली_blks poपूर्णांकer in this function is रक्षित by
 * sb->s_umount semaphore. However we have to be careful as we can be
 * racing with ext4_inode_block_valid() calls पढ़ोing प्रणाली_blks rbtree
 * रक्षित only by RCU. So we first clear the प्रणाली_blks poपूर्णांकer and
 * then मुक्त the rbtree only after RCU grace period expires.
 */
व्योम ext4_release_प्रणाली_zone(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_प्रणाली_blocks *प्रणाली_blks;

	प्रणाली_blks = rcu_dereference_रक्षित(EXT4_SB(sb)->s_प्रणाली_blks,
					lockdep_is_held(&sb->s_umount));
	rcu_assign_poपूर्णांकer(EXT4_SB(sb)->s_प्रणाली_blks, शून्य);

	अगर (प्रणाली_blks)
		call_rcu(&प्रणाली_blks->rcu, ext4_destroy_प्रणाली_zone);
पूर्ण

/*
 * Returns 1 अगर the passed-in block region (start_blk,
 * start_blk+count) is valid; 0 अगर some part of the block region
 * overlaps with some other fileप्रणाली metadata blocks.
 */
पूर्णांक ext4_inode_block_valid(काष्ठा inode *inode, ext4_fsblk_t start_blk,
			  अचिन्हित पूर्णांक count)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_प्रणाली_blocks *प्रणाली_blks;
	काष्ठा ext4_प्रणाली_zone *entry;
	काष्ठा rb_node *n;
	पूर्णांक ret = 1;

	अगर ((start_blk <= le32_to_cpu(sbi->s_es->s_first_data_block)) ||
	    (start_blk + count < start_blk) ||
	    (start_blk + count > ext4_blocks_count(sbi->s_es)))
		वापस 0;

	/*
	 * Lock the प्रणाली zone to prevent it being released concurrently
	 * when करोing a remount which inverse current "[no]block_validity"
	 * mount option.
	 */
	rcu_पढ़ो_lock();
	प्रणाली_blks = rcu_dereference(sbi->s_प्रणाली_blks);
	अगर (प्रणाली_blks == शून्य)
		जाओ out_rcu;

	n = प्रणाली_blks->root.rb_node;
	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा ext4_प्रणाली_zone, node);
		अगर (start_blk + count - 1 < entry->start_blk)
			n = n->rb_left;
		अन्यथा अगर (start_blk >= (entry->start_blk + entry->count))
			n = n->rb_right;
		अन्यथा अणु
			ret = (entry->ino == inode->i_ino);
			अवरोध;
		पूर्ण
	पूर्ण
out_rcu:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

पूर्णांक ext4_check_blockref(स्थिर अक्षर *function, अचिन्हित पूर्णांक line,
			काष्ठा inode *inode, __le32 *p, अचिन्हित पूर्णांक max)
अणु
	__le32 *bref = p;
	अचिन्हित पूर्णांक blk;

	अगर (ext4_has_feature_journal(inode->i_sb) &&
	    (inode->i_ino ==
	     le32_to_cpu(EXT4_SB(inode->i_sb)->s_es->s_journal_inum)))
		वापस 0;

	जबतक (bref < p+max) अणु
		blk = le32_to_cpu(*bref++);
		अगर (blk &&
		    unlikely(!ext4_inode_block_valid(inode, blk, 1))) अणु
			ext4_error_inode(inode, function, line, blk,
					 "invalid block");
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


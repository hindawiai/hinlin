<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * btree.c - NILFS B-tree.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pagevec.h>
#समावेश "nilfs.h"
#समावेश "page.h"
#समावेश "btnode.h"
#समावेश "btree.h"
#समावेश "alloc.h"
#समावेश "dat.h"

अटल व्योम __nilfs_btree_init(काष्ठा nilfs_bmap *bmap);

अटल काष्ठा nilfs_btree_path *nilfs_btree_alloc_path(व्योम)
अणु
	काष्ठा nilfs_btree_path *path;
	पूर्णांक level = NILFS_BTREE_LEVEL_DATA;

	path = kmem_cache_alloc(nilfs_btree_path_cache, GFP_NOFS);
	अगर (path == शून्य)
		जाओ out;

	क्रम (; level < NILFS_BTREE_LEVEL_MAX; level++) अणु
		path[level].bp_bh = शून्य;
		path[level].bp_sib_bh = शून्य;
		path[level].bp_index = 0;
		path[level].bp_oldreq.bpr_ptr = NILFS_BMAP_INVALID_PTR;
		path[level].bp_newreq.bpr_ptr = NILFS_BMAP_INVALID_PTR;
		path[level].bp_op = शून्य;
	पूर्ण

out:
	वापस path;
पूर्ण

अटल व्योम nilfs_btree_मुक्त_path(काष्ठा nilfs_btree_path *path)
अणु
	पूर्णांक level = NILFS_BTREE_LEVEL_DATA;

	क्रम (; level < NILFS_BTREE_LEVEL_MAX; level++)
		brअन्यथा(path[level].bp_bh);

	kmem_cache_मुक्त(nilfs_btree_path_cache, path);
पूर्ण

/*
 * B-tree node operations
 */
अटल पूर्णांक nilfs_btree_get_new_block(स्थिर काष्ठा nilfs_bmap *btree,
				     __u64 ptr, काष्ठा buffer_head **bhp)
अणु
	काष्ठा address_space *btnc = &NILFS_BMAP_I(btree)->i_btnode_cache;
	काष्ठा buffer_head *bh;

	bh = nilfs_btnode_create_block(btnc, ptr);
	अगर (!bh)
		वापस -ENOMEM;

	set_buffer_nilfs_अस्थिर(bh);
	*bhp = bh;
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_btree_node_get_flags(स्थिर काष्ठा nilfs_btree_node *node)
अणु
	वापस node->bn_flags;
पूर्ण

अटल व्योम
nilfs_btree_node_set_flags(काष्ठा nilfs_btree_node *node, पूर्णांक flags)
अणु
	node->bn_flags = flags;
पूर्ण

अटल पूर्णांक nilfs_btree_node_root(स्थिर काष्ठा nilfs_btree_node *node)
अणु
	वापस nilfs_btree_node_get_flags(node) & NILFS_BTREE_NODE_ROOT;
पूर्ण

अटल पूर्णांक nilfs_btree_node_get_level(स्थिर काष्ठा nilfs_btree_node *node)
अणु
	वापस node->bn_level;
पूर्ण

अटल व्योम
nilfs_btree_node_set_level(काष्ठा nilfs_btree_node *node, पूर्णांक level)
अणु
	node->bn_level = level;
पूर्ण

अटल पूर्णांक nilfs_btree_node_get_nchildren(स्थिर काष्ठा nilfs_btree_node *node)
अणु
	वापस le16_to_cpu(node->bn_nchildren);
पूर्ण

अटल व्योम
nilfs_btree_node_set_nchildren(काष्ठा nilfs_btree_node *node, पूर्णांक nchildren)
अणु
	node->bn_nchildren = cpu_to_le16(nchildren);
पूर्ण

अटल पूर्णांक nilfs_btree_node_size(स्थिर काष्ठा nilfs_bmap *btree)
अणु
	वापस i_blocksize(btree->b_inode);
पूर्ण

अटल पूर्णांक nilfs_btree_nchildren_per_block(स्थिर काष्ठा nilfs_bmap *btree)
अणु
	वापस btree->b_nchildren_per_block;
पूर्ण

अटल __le64 *
nilfs_btree_node_dkeys(स्थिर काष्ठा nilfs_btree_node *node)
अणु
	वापस (__le64 *)((अक्षर *)(node + 1) +
			  (nilfs_btree_node_root(node) ?
			   0 : NILFS_BTREE_NODE_EXTRA_PAD_SIZE));
पूर्ण

अटल __le64 *
nilfs_btree_node_dptrs(स्थिर काष्ठा nilfs_btree_node *node, पूर्णांक ncmax)
अणु
	वापस (__le64 *)(nilfs_btree_node_dkeys(node) + ncmax);
पूर्ण

अटल __u64
nilfs_btree_node_get_key(स्थिर काष्ठा nilfs_btree_node *node, पूर्णांक index)
अणु
	वापस le64_to_cpu(*(nilfs_btree_node_dkeys(node) + index));
पूर्ण

अटल व्योम
nilfs_btree_node_set_key(काष्ठा nilfs_btree_node *node, पूर्णांक index, __u64 key)
अणु
	*(nilfs_btree_node_dkeys(node) + index) = cpu_to_le64(key);
पूर्ण

अटल __u64
nilfs_btree_node_get_ptr(स्थिर काष्ठा nilfs_btree_node *node, पूर्णांक index,
			 पूर्णांक ncmax)
अणु
	वापस le64_to_cpu(*(nilfs_btree_node_dptrs(node, ncmax) + index));
पूर्ण

अटल व्योम
nilfs_btree_node_set_ptr(काष्ठा nilfs_btree_node *node, पूर्णांक index, __u64 ptr,
			 पूर्णांक ncmax)
अणु
	*(nilfs_btree_node_dptrs(node, ncmax) + index) = cpu_to_le64(ptr);
पूर्ण

अटल व्योम nilfs_btree_node_init(काष्ठा nilfs_btree_node *node, पूर्णांक flags,
				  पूर्णांक level, पूर्णांक nchildren, पूर्णांक ncmax,
				  स्थिर __u64 *keys, स्थिर __u64 *ptrs)
अणु
	__le64 *dkeys;
	__le64 *dptrs;
	पूर्णांक i;

	nilfs_btree_node_set_flags(node, flags);
	nilfs_btree_node_set_level(node, level);
	nilfs_btree_node_set_nchildren(node, nchildren);

	dkeys = nilfs_btree_node_dkeys(node);
	dptrs = nilfs_btree_node_dptrs(node, ncmax);
	क्रम (i = 0; i < nchildren; i++) अणु
		dkeys[i] = cpu_to_le64(keys[i]);
		dptrs[i] = cpu_to_le64(ptrs[i]);
	पूर्ण
पूर्ण

/* Assume the buffer heads corresponding to left and right are locked. */
अटल व्योम nilfs_btree_node_move_left(काष्ठा nilfs_btree_node *left,
				       काष्ठा nilfs_btree_node *right,
				       पूर्णांक n, पूर्णांक lncmax, पूर्णांक rncmax)
अणु
	__le64 *ldkeys, *rdkeys;
	__le64 *ldptrs, *rdptrs;
	पूर्णांक lnchildren, rnchildren;

	ldkeys = nilfs_btree_node_dkeys(left);
	ldptrs = nilfs_btree_node_dptrs(left, lncmax);
	lnchildren = nilfs_btree_node_get_nchildren(left);

	rdkeys = nilfs_btree_node_dkeys(right);
	rdptrs = nilfs_btree_node_dptrs(right, rncmax);
	rnchildren = nilfs_btree_node_get_nchildren(right);

	स_नकल(ldkeys + lnchildren, rdkeys, n * माप(*rdkeys));
	स_नकल(ldptrs + lnchildren, rdptrs, n * माप(*rdptrs));
	स_हटाओ(rdkeys, rdkeys + n, (rnchildren - n) * माप(*rdkeys));
	स_हटाओ(rdptrs, rdptrs + n, (rnchildren - n) * माप(*rdptrs));

	lnchildren += n;
	rnchildren -= n;
	nilfs_btree_node_set_nchildren(left, lnchildren);
	nilfs_btree_node_set_nchildren(right, rnchildren);
पूर्ण

/* Assume that the buffer heads corresponding to left and right are locked. */
अटल व्योम nilfs_btree_node_move_right(काष्ठा nilfs_btree_node *left,
					काष्ठा nilfs_btree_node *right,
					पूर्णांक n, पूर्णांक lncmax, पूर्णांक rncmax)
अणु
	__le64 *ldkeys, *rdkeys;
	__le64 *ldptrs, *rdptrs;
	पूर्णांक lnchildren, rnchildren;

	ldkeys = nilfs_btree_node_dkeys(left);
	ldptrs = nilfs_btree_node_dptrs(left, lncmax);
	lnchildren = nilfs_btree_node_get_nchildren(left);

	rdkeys = nilfs_btree_node_dkeys(right);
	rdptrs = nilfs_btree_node_dptrs(right, rncmax);
	rnchildren = nilfs_btree_node_get_nchildren(right);

	स_हटाओ(rdkeys + n, rdkeys, rnchildren * माप(*rdkeys));
	स_हटाओ(rdptrs + n, rdptrs, rnchildren * माप(*rdptrs));
	स_नकल(rdkeys, ldkeys + lnchildren - n, n * माप(*rdkeys));
	स_नकल(rdptrs, ldptrs + lnchildren - n, n * माप(*rdptrs));

	lnchildren -= n;
	rnchildren += n;
	nilfs_btree_node_set_nchildren(left, lnchildren);
	nilfs_btree_node_set_nchildren(right, rnchildren);
पूर्ण

/* Assume that the buffer head corresponding to node is locked. */
अटल व्योम nilfs_btree_node_insert(काष्ठा nilfs_btree_node *node, पूर्णांक index,
				    __u64 key, __u64 ptr, पूर्णांक ncmax)
अणु
	__le64 *dkeys;
	__le64 *dptrs;
	पूर्णांक nchildren;

	dkeys = nilfs_btree_node_dkeys(node);
	dptrs = nilfs_btree_node_dptrs(node, ncmax);
	nchildren = nilfs_btree_node_get_nchildren(node);
	अगर (index < nchildren) अणु
		स_हटाओ(dkeys + index + 1, dkeys + index,
			(nchildren - index) * माप(*dkeys));
		स_हटाओ(dptrs + index + 1, dptrs + index,
			(nchildren - index) * माप(*dptrs));
	पूर्ण
	dkeys[index] = cpu_to_le64(key);
	dptrs[index] = cpu_to_le64(ptr);
	nchildren++;
	nilfs_btree_node_set_nchildren(node, nchildren);
पूर्ण

/* Assume that the buffer head corresponding to node is locked. */
अटल व्योम nilfs_btree_node_delete(काष्ठा nilfs_btree_node *node, पूर्णांक index,
				    __u64 *keyp, __u64 *ptrp, पूर्णांक ncmax)
अणु
	__u64 key;
	__u64 ptr;
	__le64 *dkeys;
	__le64 *dptrs;
	पूर्णांक nchildren;

	dkeys = nilfs_btree_node_dkeys(node);
	dptrs = nilfs_btree_node_dptrs(node, ncmax);
	key = le64_to_cpu(dkeys[index]);
	ptr = le64_to_cpu(dptrs[index]);
	nchildren = nilfs_btree_node_get_nchildren(node);
	अगर (keyp != शून्य)
		*keyp = key;
	अगर (ptrp != शून्य)
		*ptrp = ptr;

	अगर (index < nchildren - 1) अणु
		स_हटाओ(dkeys + index, dkeys + index + 1,
			(nchildren - index - 1) * माप(*dkeys));
		स_हटाओ(dptrs + index, dptrs + index + 1,
			(nchildren - index - 1) * माप(*dptrs));
	पूर्ण
	nchildren--;
	nilfs_btree_node_set_nchildren(node, nchildren);
पूर्ण

अटल पूर्णांक nilfs_btree_node_lookup(स्थिर काष्ठा nilfs_btree_node *node,
				   __u64 key, पूर्णांक *indexp)
अणु
	__u64 nkey;
	पूर्णांक index, low, high, s;

	/* binary search */
	low = 0;
	high = nilfs_btree_node_get_nchildren(node) - 1;
	index = 0;
	s = 0;
	जबतक (low <= high) अणु
		index = (low + high) / 2;
		nkey = nilfs_btree_node_get_key(node, index);
		अगर (nkey == key) अणु
			s = 0;
			जाओ out;
		पूर्ण अन्यथा अगर (nkey < key) अणु
			low = index + 1;
			s = -1;
		पूर्ण अन्यथा अणु
			high = index - 1;
			s = 1;
		पूर्ण
	पूर्ण

	/* adjust index */
	अगर (nilfs_btree_node_get_level(node) > NILFS_BTREE_LEVEL_NODE_MIN) अणु
		अगर (s > 0 && index > 0)
			index--;
	पूर्ण अन्यथा अगर (s < 0)
		index++;

 out:
	*indexp = index;

	वापस s == 0;
पूर्ण

/**
 * nilfs_btree_node_broken - verअगरy consistency of btree node
 * @node: btree node block to be examined
 * @size: node size (in bytes)
 * @inode: host inode of btree
 * @blocknr: block number
 *
 * Return Value: If node is broken, 1 is वापसed. Otherwise, 0 is वापसed.
 */
अटल पूर्णांक nilfs_btree_node_broken(स्थिर काष्ठा nilfs_btree_node *node,
				   माप_प्रकार size, काष्ठा inode *inode,
				   sector_t blocknr)
अणु
	पूर्णांक level, flags, nchildren;
	पूर्णांक ret = 0;

	level = nilfs_btree_node_get_level(node);
	flags = nilfs_btree_node_get_flags(node);
	nchildren = nilfs_btree_node_get_nchildren(node);

	अगर (unlikely(level < NILFS_BTREE_LEVEL_NODE_MIN ||
		     level >= NILFS_BTREE_LEVEL_MAX ||
		     (flags & NILFS_BTREE_NODE_ROOT) ||
		     nchildren < 0 ||
		     nchildren > NILFS_BTREE_NODE_NCHILDREN_MAX(size))) अणु
		nilfs_crit(inode->i_sb,
			   "bad btree node (ino=%lu, blocknr=%llu): level = %d, flags = 0x%x, nchildren = %d",
			   inode->i_ino, (अचिन्हित दीर्घ दीर्घ)blocknr, level,
			   flags, nchildren);
		ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nilfs_btree_root_broken - verअगरy consistency of btree root node
 * @node: btree root node to be examined
 * @inode: host inode of btree
 *
 * Return Value: If node is broken, 1 is वापसed. Otherwise, 0 is वापसed.
 */
अटल पूर्णांक nilfs_btree_root_broken(स्थिर काष्ठा nilfs_btree_node *node,
				   काष्ठा inode *inode)
अणु
	पूर्णांक level, flags, nchildren;
	पूर्णांक ret = 0;

	level = nilfs_btree_node_get_level(node);
	flags = nilfs_btree_node_get_flags(node);
	nchildren = nilfs_btree_node_get_nchildren(node);

	अगर (unlikely(level < NILFS_BTREE_LEVEL_NODE_MIN ||
		     level >= NILFS_BTREE_LEVEL_MAX ||
		     nchildren < 0 ||
		     nchildren > NILFS_BTREE_ROOT_NCHILDREN_MAX)) अणु
		nilfs_crit(inode->i_sb,
			   "bad btree root (ino=%lu): level = %d, flags = 0x%x, nchildren = %d",
			   inode->i_ino, level, flags, nchildren);
		ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक nilfs_btree_broken_node_block(काष्ठा buffer_head *bh)
अणु
	काष्ठा inode *inode;
	पूर्णांक ret;

	अगर (buffer_nilfs_checked(bh))
		वापस 0;

	inode = bh->b_page->mapping->host;
	ret = nilfs_btree_node_broken((काष्ठा nilfs_btree_node *)bh->b_data,
				      bh->b_size, inode, bh->b_blocknr);
	अगर (likely(!ret))
		set_buffer_nilfs_checked(bh);
	वापस ret;
पूर्ण

अटल काष्ठा nilfs_btree_node *
nilfs_btree_get_root(स्थिर काष्ठा nilfs_bmap *btree)
अणु
	वापस (काष्ठा nilfs_btree_node *)btree->b_u.u_data;
पूर्ण

अटल काष्ठा nilfs_btree_node *
nilfs_btree_get_nonroot_node(स्थिर काष्ठा nilfs_btree_path *path, पूर्णांक level)
अणु
	वापस (काष्ठा nilfs_btree_node *)path[level].bp_bh->b_data;
पूर्ण

अटल काष्ठा nilfs_btree_node *
nilfs_btree_get_sib_node(स्थिर काष्ठा nilfs_btree_path *path, पूर्णांक level)
अणु
	वापस (काष्ठा nilfs_btree_node *)path[level].bp_sib_bh->b_data;
पूर्ण

अटल पूर्णांक nilfs_btree_height(स्थिर काष्ठा nilfs_bmap *btree)
अणु
	वापस nilfs_btree_node_get_level(nilfs_btree_get_root(btree)) + 1;
पूर्ण

अटल काष्ठा nilfs_btree_node *
nilfs_btree_get_node(स्थिर काष्ठा nilfs_bmap *btree,
		     स्थिर काष्ठा nilfs_btree_path *path,
		     पूर्णांक level, पूर्णांक *ncmaxp)
अणु
	काष्ठा nilfs_btree_node *node;

	अगर (level == nilfs_btree_height(btree) - 1) अणु
		node = nilfs_btree_get_root(btree);
		*ncmaxp = NILFS_BTREE_ROOT_NCHILDREN_MAX;
	पूर्ण अन्यथा अणु
		node = nilfs_btree_get_nonroot_node(path, level);
		*ncmaxp = nilfs_btree_nchildren_per_block(btree);
	पूर्ण
	वापस node;
पूर्ण

अटल पूर्णांक nilfs_btree_bad_node(स्थिर काष्ठा nilfs_bmap *btree,
				काष्ठा nilfs_btree_node *node, पूर्णांक level)
अणु
	अगर (unlikely(nilfs_btree_node_get_level(node) != level)) अणु
		dump_stack();
		nilfs_crit(btree->b_inode->i_sb,
			   "btree level mismatch (ino=%lu): %d != %d",
			   btree->b_inode->i_ino,
			   nilfs_btree_node_get_level(node), level);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा nilfs_btree_पढ़ोahead_info अणु
	काष्ठा nilfs_btree_node *node;	/* parent node */
	पूर्णांक max_ra_blocks;		/* max nof blocks to पढ़ो ahead */
	पूर्णांक index;			/* current index on the parent node */
	पूर्णांक ncmax;			/* nof children in the parent node */
पूर्ण;

अटल पूर्णांक __nilfs_btree_get_block(स्थिर काष्ठा nilfs_bmap *btree, __u64 ptr,
				   काष्ठा buffer_head **bhp,
				   स्थिर काष्ठा nilfs_btree_पढ़ोahead_info *ra)
अणु
	काष्ठा address_space *btnc = &NILFS_BMAP_I(btree)->i_btnode_cache;
	काष्ठा buffer_head *bh, *ra_bh;
	sector_t submit_ptr = 0;
	पूर्णांक ret;

	ret = nilfs_btnode_submit_block(btnc, ptr, 0, REQ_OP_READ, 0, &bh,
					&submit_ptr);
	अगर (ret) अणु
		अगर (ret != -EEXIST)
			वापस ret;
		जाओ out_check;
	पूर्ण

	अगर (ra) अणु
		पूर्णांक i, n;
		__u64 ptr2;

		/* पढ़ो ahead sibling nodes */
		क्रम (n = ra->max_ra_blocks, i = ra->index + 1;
		     n > 0 && i < ra->ncmax; n--, i++) अणु
			ptr2 = nilfs_btree_node_get_ptr(ra->node, i, ra->ncmax);

			ret = nilfs_btnode_submit_block(btnc, ptr2, 0,
							REQ_OP_READ, REQ_RAHEAD,
							&ra_bh, &submit_ptr);
			अगर (likely(!ret || ret == -EEXIST))
				brअन्यथा(ra_bh);
			अन्यथा अगर (ret != -EBUSY)
				अवरोध;
			अगर (!buffer_locked(bh))
				जाओ out_no_रुको;
		पूर्ण
	पूर्ण

	रुको_on_buffer(bh);

 out_no_रुको:
	अगर (!buffer_uptodate(bh)) अणु
		nilfs_err(btree->b_inode->i_sb,
			  "I/O error reading b-tree node block (ino=%lu, blocknr=%llu)",
			  btree->b_inode->i_ino, (अचिन्हित दीर्घ दीर्घ)ptr);
		brअन्यथा(bh);
		वापस -EIO;
	पूर्ण

 out_check:
	अगर (nilfs_btree_broken_node_block(bh)) अणु
		clear_buffer_uptodate(bh);
		brअन्यथा(bh);
		वापस -EINVAL;
	पूर्ण

	*bhp = bh;
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_btree_get_block(स्थिर काष्ठा nilfs_bmap *btree, __u64 ptr,
				   काष्ठा buffer_head **bhp)
अणु
	वापस __nilfs_btree_get_block(btree, ptr, bhp, शून्य);
पूर्ण

अटल पूर्णांक nilfs_btree_करो_lookup(स्थिर काष्ठा nilfs_bmap *btree,
				 काष्ठा nilfs_btree_path *path,
				 __u64 key, __u64 *ptrp, पूर्णांक minlevel,
				 पूर्णांक पढ़ोahead)
अणु
	काष्ठा nilfs_btree_node *node;
	काष्ठा nilfs_btree_पढ़ोahead_info p, *ra;
	__u64 ptr;
	पूर्णांक level, index, found, ncmax, ret;

	node = nilfs_btree_get_root(btree);
	level = nilfs_btree_node_get_level(node);
	अगर (level < minlevel || nilfs_btree_node_get_nchildren(node) <= 0)
		वापस -ENOENT;

	found = nilfs_btree_node_lookup(node, key, &index);
	ptr = nilfs_btree_node_get_ptr(node, index,
				       NILFS_BTREE_ROOT_NCHILDREN_MAX);
	path[level].bp_bh = शून्य;
	path[level].bp_index = index;

	ncmax = nilfs_btree_nchildren_per_block(btree);

	जबतक (--level >= minlevel) अणु
		ra = शून्य;
		अगर (level == NILFS_BTREE_LEVEL_NODE_MIN && पढ़ोahead) अणु
			p.node = nilfs_btree_get_node(btree, path, level + 1,
						      &p.ncmax);
			p.index = index;
			p.max_ra_blocks = 7;
			ra = &p;
		पूर्ण
		ret = __nilfs_btree_get_block(btree, ptr, &path[level].bp_bh,
					      ra);
		अगर (ret < 0)
			वापस ret;

		node = nilfs_btree_get_nonroot_node(path, level);
		अगर (nilfs_btree_bad_node(btree, node, level))
			वापस -EINVAL;
		अगर (!found)
			found = nilfs_btree_node_lookup(node, key, &index);
		अन्यथा
			index = 0;
		अगर (index < ncmax) अणु
			ptr = nilfs_btree_node_get_ptr(node, index, ncmax);
		पूर्ण अन्यथा अणु
			WARN_ON(found || level != NILFS_BTREE_LEVEL_NODE_MIN);
			/* insert */
			ptr = NILFS_BMAP_INVALID_PTR;
		पूर्ण
		path[level].bp_index = index;
	पूर्ण
	अगर (!found)
		वापस -ENOENT;

	अगर (ptrp != शून्य)
		*ptrp = ptr;

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_btree_करो_lookup_last(स्थिर काष्ठा nilfs_bmap *btree,
				      काष्ठा nilfs_btree_path *path,
				      __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node;
	__u64 ptr;
	पूर्णांक index, level, ncmax, ret;

	node = nilfs_btree_get_root(btree);
	index = nilfs_btree_node_get_nchildren(node) - 1;
	अगर (index < 0)
		वापस -ENOENT;
	level = nilfs_btree_node_get_level(node);
	ptr = nilfs_btree_node_get_ptr(node, index,
				       NILFS_BTREE_ROOT_NCHILDREN_MAX);
	path[level].bp_bh = शून्य;
	path[level].bp_index = index;
	ncmax = nilfs_btree_nchildren_per_block(btree);

	क्रम (level--; level > 0; level--) अणु
		ret = nilfs_btree_get_block(btree, ptr, &path[level].bp_bh);
		अगर (ret < 0)
			वापस ret;
		node = nilfs_btree_get_nonroot_node(path, level);
		अगर (nilfs_btree_bad_node(btree, node, level))
			वापस -EINVAL;
		index = nilfs_btree_node_get_nchildren(node) - 1;
		ptr = nilfs_btree_node_get_ptr(node, index, ncmax);
		path[level].bp_index = index;
	पूर्ण

	अगर (keyp != शून्य)
		*keyp = nilfs_btree_node_get_key(node, index);
	अगर (ptrp != शून्य)
		*ptrp = ptr;

	वापस 0;
पूर्ण

/**
 * nilfs_btree_get_next_key - get next valid key from btree path array
 * @btree: bmap काष्ठा of btree
 * @path: array of nilfs_btree_path काष्ठा
 * @minlevel: start level
 * @nextkey: place to store the next valid key
 *
 * Return Value: If a next key was found, 0 is वापसed. Otherwise,
 * -ENOENT is वापसed.
 */
अटल पूर्णांक nilfs_btree_get_next_key(स्थिर काष्ठा nilfs_bmap *btree,
				    स्थिर काष्ठा nilfs_btree_path *path,
				    पूर्णांक minlevel, __u64 *nextkey)
अणु
	काष्ठा nilfs_btree_node *node;
	पूर्णांक maxlevel = nilfs_btree_height(btree) - 1;
	पूर्णांक index, next_adj, level;

	/* Next index is alपढ़ोy set to bp_index क्रम leaf nodes. */
	next_adj = 0;
	क्रम (level = minlevel; level <= maxlevel; level++) अणु
		अगर (level == maxlevel)
			node = nilfs_btree_get_root(btree);
		अन्यथा
			node = nilfs_btree_get_nonroot_node(path, level);

		index = path[level].bp_index + next_adj;
		अगर (index < nilfs_btree_node_get_nchildren(node)) अणु
			/* Next key is in this node */
			*nextkey = nilfs_btree_node_get_key(node, index);
			वापस 0;
		पूर्ण
		/* For non-leaf nodes, next index is stored at bp_index + 1. */
		next_adj = 1;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक nilfs_btree_lookup(स्थिर काष्ठा nilfs_bmap *btree,
			      __u64 key, पूर्णांक level, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_path *path;
	पूर्णांक ret;

	path = nilfs_btree_alloc_path();
	अगर (path == शून्य)
		वापस -ENOMEM;

	ret = nilfs_btree_करो_lookup(btree, path, key, ptrp, level, 0);

	nilfs_btree_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_btree_lookup_contig(स्थिर काष्ठा nilfs_bmap *btree,
				     __u64 key, __u64 *ptrp,
				     अचिन्हित पूर्णांक maxblocks)
अणु
	काष्ठा nilfs_btree_path *path;
	काष्ठा nilfs_btree_node *node;
	काष्ठा inode *dat = शून्य;
	__u64 ptr, ptr2;
	sector_t blocknr;
	पूर्णांक level = NILFS_BTREE_LEVEL_NODE_MIN;
	पूर्णांक ret, cnt, index, maxlevel, ncmax;
	काष्ठा nilfs_btree_पढ़ोahead_info p;

	path = nilfs_btree_alloc_path();
	अगर (path == शून्य)
		वापस -ENOMEM;

	ret = nilfs_btree_करो_lookup(btree, path, key, &ptr, level, 1);
	अगर (ret < 0)
		जाओ out;

	अगर (NILFS_BMAP_USE_VBN(btree)) अणु
		dat = nilfs_bmap_get_dat(btree);
		ret = nilfs_dat_translate(dat, ptr, &blocknr);
		अगर (ret < 0)
			जाओ out;
		ptr = blocknr;
	पूर्ण
	cnt = 1;
	अगर (cnt == maxblocks)
		जाओ end;

	maxlevel = nilfs_btree_height(btree) - 1;
	node = nilfs_btree_get_node(btree, path, level, &ncmax);
	index = path[level].bp_index + 1;
	क्रम (;;) अणु
		जबतक (index < nilfs_btree_node_get_nchildren(node)) अणु
			अगर (nilfs_btree_node_get_key(node, index) !=
			    key + cnt)
				जाओ end;
			ptr2 = nilfs_btree_node_get_ptr(node, index, ncmax);
			अगर (dat) अणु
				ret = nilfs_dat_translate(dat, ptr2, &blocknr);
				अगर (ret < 0)
					जाओ out;
				ptr2 = blocknr;
			पूर्ण
			अगर (ptr2 != ptr + cnt || ++cnt == maxblocks)
				जाओ end;
			index++;
			जारी;
		पूर्ण
		अगर (level == maxlevel)
			अवरोध;

		/* look-up right sibling node */
		p.node = nilfs_btree_get_node(btree, path, level + 1, &p.ncmax);
		p.index = path[level + 1].bp_index + 1;
		p.max_ra_blocks = 7;
		अगर (p.index >= nilfs_btree_node_get_nchildren(p.node) ||
		    nilfs_btree_node_get_key(p.node, p.index) != key + cnt)
			अवरोध;
		ptr2 = nilfs_btree_node_get_ptr(p.node, p.index, p.ncmax);
		path[level + 1].bp_index = p.index;

		brअन्यथा(path[level].bp_bh);
		path[level].bp_bh = शून्य;

		ret = __nilfs_btree_get_block(btree, ptr2, &path[level].bp_bh,
					      &p);
		अगर (ret < 0)
			जाओ out;
		node = nilfs_btree_get_nonroot_node(path, level);
		ncmax = nilfs_btree_nchildren_per_block(btree);
		index = 0;
		path[level].bp_index = index;
	पूर्ण
 end:
	*ptrp = ptr;
	ret = cnt;
 out:
	nilfs_btree_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल व्योम nilfs_btree_promote_key(काष्ठा nilfs_bmap *btree,
				    काष्ठा nilfs_btree_path *path,
				    पूर्णांक level, __u64 key)
अणु
	अगर (level < nilfs_btree_height(btree) - 1) अणु
		करो अणु
			nilfs_btree_node_set_key(
				nilfs_btree_get_nonroot_node(path, level),
				path[level].bp_index, key);
			अगर (!buffer_dirty(path[level].bp_bh))
				mark_buffer_dirty(path[level].bp_bh);
		पूर्ण जबतक ((path[level].bp_index == 0) &&
			 (++level < nilfs_btree_height(btree) - 1));
	पूर्ण

	/* root */
	अगर (level == nilfs_btree_height(btree) - 1) अणु
		nilfs_btree_node_set_key(nilfs_btree_get_root(btree),
					 path[level].bp_index, key);
	पूर्ण
पूर्ण

अटल व्योम nilfs_btree_करो_insert(काष्ठा nilfs_bmap *btree,
				  काष्ठा nilfs_btree_path *path,
				  पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node;
	पूर्णांक ncblk;

	अगर (level < nilfs_btree_height(btree) - 1) अणु
		node = nilfs_btree_get_nonroot_node(path, level);
		ncblk = nilfs_btree_nchildren_per_block(btree);
		nilfs_btree_node_insert(node, path[level].bp_index,
					*keyp, *ptrp, ncblk);
		अगर (!buffer_dirty(path[level].bp_bh))
			mark_buffer_dirty(path[level].bp_bh);

		अगर (path[level].bp_index == 0)
			nilfs_btree_promote_key(btree, path, level + 1,
						nilfs_btree_node_get_key(node,
									 0));
	पूर्ण अन्यथा अणु
		node = nilfs_btree_get_root(btree);
		nilfs_btree_node_insert(node, path[level].bp_index,
					*keyp, *ptrp,
					NILFS_BTREE_ROOT_NCHILDREN_MAX);
	पूर्ण
पूर्ण

अटल व्योम nilfs_btree_carry_left(काष्ठा nilfs_bmap *btree,
				   काष्ठा nilfs_btree_path *path,
				   पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node, *left;
	पूर्णांक nchildren, lnchildren, n, move, ncblk;

	node = nilfs_btree_get_nonroot_node(path, level);
	left = nilfs_btree_get_sib_node(path, level);
	nchildren = nilfs_btree_node_get_nchildren(node);
	lnchildren = nilfs_btree_node_get_nchildren(left);
	ncblk = nilfs_btree_nchildren_per_block(btree);
	move = 0;

	n = (nchildren + lnchildren + 1) / 2 - lnchildren;
	अगर (n > path[level].bp_index) अणु
		/* move insert poपूर्णांक */
		n--;
		move = 1;
	पूर्ण

	nilfs_btree_node_move_left(left, node, n, ncblk, ncblk);

	अगर (!buffer_dirty(path[level].bp_bh))
		mark_buffer_dirty(path[level].bp_bh);
	अगर (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	nilfs_btree_promote_key(btree, path, level + 1,
				nilfs_btree_node_get_key(node, 0));

	अगर (move) अणु
		brअन्यथा(path[level].bp_bh);
		path[level].bp_bh = path[level].bp_sib_bh;
		path[level].bp_sib_bh = शून्य;
		path[level].bp_index += lnchildren;
		path[level + 1].bp_index--;
	पूर्ण अन्यथा अणु
		brअन्यथा(path[level].bp_sib_bh);
		path[level].bp_sib_bh = शून्य;
		path[level].bp_index -= n;
	पूर्ण

	nilfs_btree_करो_insert(btree, path, level, keyp, ptrp);
पूर्ण

अटल व्योम nilfs_btree_carry_right(काष्ठा nilfs_bmap *btree,
				    काष्ठा nilfs_btree_path *path,
				    पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node, *right;
	पूर्णांक nchildren, rnchildren, n, move, ncblk;

	node = nilfs_btree_get_nonroot_node(path, level);
	right = nilfs_btree_get_sib_node(path, level);
	nchildren = nilfs_btree_node_get_nchildren(node);
	rnchildren = nilfs_btree_node_get_nchildren(right);
	ncblk = nilfs_btree_nchildren_per_block(btree);
	move = 0;

	n = (nchildren + rnchildren + 1) / 2 - rnchildren;
	अगर (n > nchildren - path[level].bp_index) अणु
		/* move insert poपूर्णांक */
		n--;
		move = 1;
	पूर्ण

	nilfs_btree_node_move_right(node, right, n, ncblk, ncblk);

	अगर (!buffer_dirty(path[level].bp_bh))
		mark_buffer_dirty(path[level].bp_bh);
	अगर (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	path[level + 1].bp_index++;
	nilfs_btree_promote_key(btree, path, level + 1,
				nilfs_btree_node_get_key(right, 0));
	path[level + 1].bp_index--;

	अगर (move) अणु
		brअन्यथा(path[level].bp_bh);
		path[level].bp_bh = path[level].bp_sib_bh;
		path[level].bp_sib_bh = शून्य;
		path[level].bp_index -= nilfs_btree_node_get_nchildren(node);
		path[level + 1].bp_index++;
	पूर्ण अन्यथा अणु
		brअन्यथा(path[level].bp_sib_bh);
		path[level].bp_sib_bh = शून्य;
	पूर्ण

	nilfs_btree_करो_insert(btree, path, level, keyp, ptrp);
पूर्ण

अटल व्योम nilfs_btree_split(काष्ठा nilfs_bmap *btree,
			      काष्ठा nilfs_btree_path *path,
			      पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node, *right;
	पूर्णांक nchildren, n, move, ncblk;

	node = nilfs_btree_get_nonroot_node(path, level);
	right = nilfs_btree_get_sib_node(path, level);
	nchildren = nilfs_btree_node_get_nchildren(node);
	ncblk = nilfs_btree_nchildren_per_block(btree);
	move = 0;

	n = (nchildren + 1) / 2;
	अगर (n > nchildren - path[level].bp_index) अणु
		n--;
		move = 1;
	पूर्ण

	nilfs_btree_node_move_right(node, right, n, ncblk, ncblk);

	अगर (!buffer_dirty(path[level].bp_bh))
		mark_buffer_dirty(path[level].bp_bh);
	अगर (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	अगर (move) अणु
		path[level].bp_index -= nilfs_btree_node_get_nchildren(node);
		nilfs_btree_node_insert(right, path[level].bp_index,
					*keyp, *ptrp, ncblk);

		*keyp = nilfs_btree_node_get_key(right, 0);
		*ptrp = path[level].bp_newreq.bpr_ptr;

		brअन्यथा(path[level].bp_bh);
		path[level].bp_bh = path[level].bp_sib_bh;
		path[level].bp_sib_bh = शून्य;
	पूर्ण अन्यथा अणु
		nilfs_btree_करो_insert(btree, path, level, keyp, ptrp);

		*keyp = nilfs_btree_node_get_key(right, 0);
		*ptrp = path[level].bp_newreq.bpr_ptr;

		brअन्यथा(path[level].bp_sib_bh);
		path[level].bp_sib_bh = शून्य;
	पूर्ण

	path[level + 1].bp_index++;
पूर्ण

अटल व्योम nilfs_btree_grow(काष्ठा nilfs_bmap *btree,
			     काष्ठा nilfs_btree_path *path,
			     पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *root, *child;
	पूर्णांक n, ncblk;

	root = nilfs_btree_get_root(btree);
	child = nilfs_btree_get_sib_node(path, level);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	n = nilfs_btree_node_get_nchildren(root);

	nilfs_btree_node_move_right(root, child, n,
				    NILFS_BTREE_ROOT_NCHILDREN_MAX, ncblk);
	nilfs_btree_node_set_level(root, level + 1);

	अगर (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	path[level].bp_bh = path[level].bp_sib_bh;
	path[level].bp_sib_bh = शून्य;

	nilfs_btree_करो_insert(btree, path, level, keyp, ptrp);

	*keyp = nilfs_btree_node_get_key(child, 0);
	*ptrp = path[level].bp_newreq.bpr_ptr;
पूर्ण

अटल __u64 nilfs_btree_find_near(स्थिर काष्ठा nilfs_bmap *btree,
				   स्थिर काष्ठा nilfs_btree_path *path)
अणु
	काष्ठा nilfs_btree_node *node;
	पूर्णांक level, ncmax;

	अगर (path == शून्य)
		वापस NILFS_BMAP_INVALID_PTR;

	/* left sibling */
	level = NILFS_BTREE_LEVEL_NODE_MIN;
	अगर (path[level].bp_index > 0) अणु
		node = nilfs_btree_get_node(btree, path, level, &ncmax);
		वापस nilfs_btree_node_get_ptr(node,
						path[level].bp_index - 1,
						ncmax);
	पूर्ण

	/* parent */
	level = NILFS_BTREE_LEVEL_NODE_MIN + 1;
	अगर (level <= nilfs_btree_height(btree) - 1) अणु
		node = nilfs_btree_get_node(btree, path, level, &ncmax);
		वापस nilfs_btree_node_get_ptr(node, path[level].bp_index,
						ncmax);
	पूर्ण

	वापस NILFS_BMAP_INVALID_PTR;
पूर्ण

अटल __u64 nilfs_btree_find_target_v(स्थिर काष्ठा nilfs_bmap *btree,
				       स्थिर काष्ठा nilfs_btree_path *path,
				       __u64 key)
अणु
	__u64 ptr;

	ptr = nilfs_bmap_find_target_seq(btree, key);
	अगर (ptr != NILFS_BMAP_INVALID_PTR)
		/* sequential access */
		वापस ptr;

	ptr = nilfs_btree_find_near(btree, path);
	अगर (ptr != NILFS_BMAP_INVALID_PTR)
		/* near */
		वापस ptr;

	/* block group */
	वापस nilfs_bmap_find_target_in_group(btree);
पूर्ण

अटल पूर्णांक nilfs_btree_prepare_insert(काष्ठा nilfs_bmap *btree,
				      काष्ठा nilfs_btree_path *path,
				      पूर्णांक *levelp, __u64 key, __u64 ptr,
				      काष्ठा nilfs_bmap_stats *stats)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_btree_node *node, *parent, *sib;
	__u64 sibptr;
	पूर्णांक pindex, level, ncmax, ncblk, ret;
	काष्ठा inode *dat = शून्य;

	stats->bs_nblocks = 0;
	level = NILFS_BTREE_LEVEL_DATA;

	/* allocate a new ptr क्रम data block */
	अगर (NILFS_BMAP_USE_VBN(btree)) अणु
		path[level].bp_newreq.bpr_ptr =
			nilfs_btree_find_target_v(btree, path, key);
		dat = nilfs_bmap_get_dat(btree);
	पूर्ण

	ret = nilfs_bmap_prepare_alloc_ptr(btree, &path[level].bp_newreq, dat);
	अगर (ret < 0)
		जाओ err_out_data;

	ncblk = nilfs_btree_nchildren_per_block(btree);

	क्रम (level = NILFS_BTREE_LEVEL_NODE_MIN;
	     level < nilfs_btree_height(btree) - 1;
	     level++) अणु
		node = nilfs_btree_get_nonroot_node(path, level);
		अगर (nilfs_btree_node_get_nchildren(node) < ncblk) अणु
			path[level].bp_op = nilfs_btree_करो_insert;
			stats->bs_nblocks++;
			जाओ out;
		पूर्ण

		parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
		pindex = path[level + 1].bp_index;

		/* left sibling */
		अगर (pindex > 0) अणु
			sibptr = nilfs_btree_node_get_ptr(parent, pindex - 1,
							  ncmax);
			ret = nilfs_btree_get_block(btree, sibptr, &bh);
			अगर (ret < 0)
				जाओ err_out_child_node;
			sib = (काष्ठा nilfs_btree_node *)bh->b_data;
			अगर (nilfs_btree_node_get_nchildren(sib) < ncblk) अणु
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_carry_left;
				stats->bs_nblocks++;
				जाओ out;
			पूर्ण अन्यथा अणु
				brअन्यथा(bh);
			पूर्ण
		पूर्ण

		/* right sibling */
		अगर (pindex < nilfs_btree_node_get_nchildren(parent) - 1) अणु
			sibptr = nilfs_btree_node_get_ptr(parent, pindex + 1,
							  ncmax);
			ret = nilfs_btree_get_block(btree, sibptr, &bh);
			अगर (ret < 0)
				जाओ err_out_child_node;
			sib = (काष्ठा nilfs_btree_node *)bh->b_data;
			अगर (nilfs_btree_node_get_nchildren(sib) < ncblk) अणु
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_carry_right;
				stats->bs_nblocks++;
				जाओ out;
			पूर्ण अन्यथा अणु
				brअन्यथा(bh);
			पूर्ण
		पूर्ण

		/* split */
		path[level].bp_newreq.bpr_ptr =
			path[level - 1].bp_newreq.bpr_ptr + 1;
		ret = nilfs_bmap_prepare_alloc_ptr(btree,
						   &path[level].bp_newreq, dat);
		अगर (ret < 0)
			जाओ err_out_child_node;
		ret = nilfs_btree_get_new_block(btree,
						path[level].bp_newreq.bpr_ptr,
						&bh);
		अगर (ret < 0)
			जाओ err_out_curr_node;

		stats->bs_nblocks++;

		sib = (काष्ठा nilfs_btree_node *)bh->b_data;
		nilfs_btree_node_init(sib, 0, level, 0, ncblk, शून्य, शून्य);
		path[level].bp_sib_bh = bh;
		path[level].bp_op = nilfs_btree_split;
	पूर्ण

	/* root */
	node = nilfs_btree_get_root(btree);
	अगर (nilfs_btree_node_get_nchildren(node) <
	    NILFS_BTREE_ROOT_NCHILDREN_MAX) अणु
		path[level].bp_op = nilfs_btree_करो_insert;
		stats->bs_nblocks++;
		जाओ out;
	पूर्ण

	/* grow */
	path[level].bp_newreq.bpr_ptr = path[level - 1].bp_newreq.bpr_ptr + 1;
	ret = nilfs_bmap_prepare_alloc_ptr(btree, &path[level].bp_newreq, dat);
	अगर (ret < 0)
		जाओ err_out_child_node;
	ret = nilfs_btree_get_new_block(btree, path[level].bp_newreq.bpr_ptr,
					&bh);
	अगर (ret < 0)
		जाओ err_out_curr_node;

	nilfs_btree_node_init((काष्ठा nilfs_btree_node *)bh->b_data,
			      0, level, 0, ncblk, शून्य, शून्य);
	path[level].bp_sib_bh = bh;
	path[level].bp_op = nilfs_btree_grow;

	level++;
	path[level].bp_op = nilfs_btree_करो_insert;

	/* a newly-created node block and a data block are added */
	stats->bs_nblocks += 2;

	/* success */
 out:
	*levelp = level;
	वापस ret;

	/* error */
 err_out_curr_node:
	nilfs_bmap_पात_alloc_ptr(btree, &path[level].bp_newreq, dat);
 err_out_child_node:
	क्रम (level--; level > NILFS_BTREE_LEVEL_DATA; level--) अणु
		nilfs_btnode_delete(path[level].bp_sib_bh);
		nilfs_bmap_पात_alloc_ptr(btree, &path[level].bp_newreq, dat);

	पूर्ण

	nilfs_bmap_पात_alloc_ptr(btree, &path[level].bp_newreq, dat);
 err_out_data:
	*levelp = level;
	stats->bs_nblocks = 0;
	वापस ret;
पूर्ण

अटल व्योम nilfs_btree_commit_insert(काष्ठा nilfs_bmap *btree,
				      काष्ठा nilfs_btree_path *path,
				      पूर्णांक maxlevel, __u64 key, __u64 ptr)
अणु
	काष्ठा inode *dat = शून्य;
	पूर्णांक level;

	set_buffer_nilfs_अस्थिर((काष्ठा buffer_head *)((अचिन्हित दीर्घ)ptr));
	ptr = path[NILFS_BTREE_LEVEL_DATA].bp_newreq.bpr_ptr;
	अगर (NILFS_BMAP_USE_VBN(btree)) अणु
		nilfs_bmap_set_target_v(btree, key, ptr);
		dat = nilfs_bmap_get_dat(btree);
	पूर्ण

	क्रम (level = NILFS_BTREE_LEVEL_NODE_MIN; level <= maxlevel; level++) अणु
		nilfs_bmap_commit_alloc_ptr(btree,
					    &path[level - 1].bp_newreq, dat);
		path[level].bp_op(btree, path, level, &key, &ptr);
	पूर्ण

	अगर (!nilfs_bmap_dirty(btree))
		nilfs_bmap_set_dirty(btree);
पूर्ण

अटल पूर्णांक nilfs_btree_insert(काष्ठा nilfs_bmap *btree, __u64 key, __u64 ptr)
अणु
	काष्ठा nilfs_btree_path *path;
	काष्ठा nilfs_bmap_stats stats;
	पूर्णांक level, ret;

	path = nilfs_btree_alloc_path();
	अगर (path == शून्य)
		वापस -ENOMEM;

	ret = nilfs_btree_करो_lookup(btree, path, key, शून्य,
				    NILFS_BTREE_LEVEL_NODE_MIN, 0);
	अगर (ret != -ENOENT) अणु
		अगर (ret == 0)
			ret = -EEXIST;
		जाओ out;
	पूर्ण

	ret = nilfs_btree_prepare_insert(btree, path, &level, key, ptr, &stats);
	अगर (ret < 0)
		जाओ out;
	nilfs_btree_commit_insert(btree, path, level, key, ptr);
	nilfs_inode_add_blocks(btree->b_inode, stats.bs_nblocks);

 out:
	nilfs_btree_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल व्योम nilfs_btree_करो_delete(काष्ठा nilfs_bmap *btree,
				  काष्ठा nilfs_btree_path *path,
				  पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node;
	पूर्णांक ncblk;

	अगर (level < nilfs_btree_height(btree) - 1) अणु
		node = nilfs_btree_get_nonroot_node(path, level);
		ncblk = nilfs_btree_nchildren_per_block(btree);
		nilfs_btree_node_delete(node, path[level].bp_index,
					keyp, ptrp, ncblk);
		अगर (!buffer_dirty(path[level].bp_bh))
			mark_buffer_dirty(path[level].bp_bh);
		अगर (path[level].bp_index == 0)
			nilfs_btree_promote_key(btree, path, level + 1,
				nilfs_btree_node_get_key(node, 0));
	पूर्ण अन्यथा अणु
		node = nilfs_btree_get_root(btree);
		nilfs_btree_node_delete(node, path[level].bp_index,
					keyp, ptrp,
					NILFS_BTREE_ROOT_NCHILDREN_MAX);
	पूर्ण
पूर्ण

अटल व्योम nilfs_btree_borrow_left(काष्ठा nilfs_bmap *btree,
				    काष्ठा nilfs_btree_path *path,
				    पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node, *left;
	पूर्णांक nchildren, lnchildren, n, ncblk;

	nilfs_btree_करो_delete(btree, path, level, keyp, ptrp);

	node = nilfs_btree_get_nonroot_node(path, level);
	left = nilfs_btree_get_sib_node(path, level);
	nchildren = nilfs_btree_node_get_nchildren(node);
	lnchildren = nilfs_btree_node_get_nchildren(left);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	n = (nchildren + lnchildren) / 2 - nchildren;

	nilfs_btree_node_move_right(left, node, n, ncblk, ncblk);

	अगर (!buffer_dirty(path[level].bp_bh))
		mark_buffer_dirty(path[level].bp_bh);
	अगर (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	nilfs_btree_promote_key(btree, path, level + 1,
				nilfs_btree_node_get_key(node, 0));

	brअन्यथा(path[level].bp_sib_bh);
	path[level].bp_sib_bh = शून्य;
	path[level].bp_index += n;
पूर्ण

अटल व्योम nilfs_btree_borrow_right(काष्ठा nilfs_bmap *btree,
				     काष्ठा nilfs_btree_path *path,
				     पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node, *right;
	पूर्णांक nchildren, rnchildren, n, ncblk;

	nilfs_btree_करो_delete(btree, path, level, keyp, ptrp);

	node = nilfs_btree_get_nonroot_node(path, level);
	right = nilfs_btree_get_sib_node(path, level);
	nchildren = nilfs_btree_node_get_nchildren(node);
	rnchildren = nilfs_btree_node_get_nchildren(right);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	n = (nchildren + rnchildren) / 2 - nchildren;

	nilfs_btree_node_move_left(node, right, n, ncblk, ncblk);

	अगर (!buffer_dirty(path[level].bp_bh))
		mark_buffer_dirty(path[level].bp_bh);
	अगर (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	path[level + 1].bp_index++;
	nilfs_btree_promote_key(btree, path, level + 1,
				nilfs_btree_node_get_key(right, 0));
	path[level + 1].bp_index--;

	brअन्यथा(path[level].bp_sib_bh);
	path[level].bp_sib_bh = शून्य;
पूर्ण

अटल व्योम nilfs_btree_concat_left(काष्ठा nilfs_bmap *btree,
				    काष्ठा nilfs_btree_path *path,
				    पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node, *left;
	पूर्णांक n, ncblk;

	nilfs_btree_करो_delete(btree, path, level, keyp, ptrp);

	node = nilfs_btree_get_nonroot_node(path, level);
	left = nilfs_btree_get_sib_node(path, level);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	n = nilfs_btree_node_get_nchildren(node);

	nilfs_btree_node_move_left(left, node, n, ncblk, ncblk);

	अगर (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	nilfs_btnode_delete(path[level].bp_bh);
	path[level].bp_bh = path[level].bp_sib_bh;
	path[level].bp_sib_bh = शून्य;
	path[level].bp_index += nilfs_btree_node_get_nchildren(left);
पूर्ण

अटल व्योम nilfs_btree_concat_right(काष्ठा nilfs_bmap *btree,
				     काष्ठा nilfs_btree_path *path,
				     पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *node, *right;
	पूर्णांक n, ncblk;

	nilfs_btree_करो_delete(btree, path, level, keyp, ptrp);

	node = nilfs_btree_get_nonroot_node(path, level);
	right = nilfs_btree_get_sib_node(path, level);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	n = nilfs_btree_node_get_nchildren(right);

	nilfs_btree_node_move_left(node, right, n, ncblk, ncblk);

	अगर (!buffer_dirty(path[level].bp_bh))
		mark_buffer_dirty(path[level].bp_bh);

	nilfs_btnode_delete(path[level].bp_sib_bh);
	path[level].bp_sib_bh = शून्य;
	path[level + 1].bp_index++;
पूर्ण

अटल व्योम nilfs_btree_shrink(काष्ठा nilfs_bmap *btree,
			       काष्ठा nilfs_btree_path *path,
			       पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
	काष्ठा nilfs_btree_node *root, *child;
	पूर्णांक n, ncblk;

	nilfs_btree_करो_delete(btree, path, level, keyp, ptrp);

	root = nilfs_btree_get_root(btree);
	child = nilfs_btree_get_nonroot_node(path, level);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	nilfs_btree_node_delete(root, 0, शून्य, शून्य,
				NILFS_BTREE_ROOT_NCHILDREN_MAX);
	nilfs_btree_node_set_level(root, level);
	n = nilfs_btree_node_get_nchildren(child);
	nilfs_btree_node_move_left(root, child, n,
				   NILFS_BTREE_ROOT_NCHILDREN_MAX, ncblk);

	nilfs_btnode_delete(path[level].bp_bh);
	path[level].bp_bh = शून्य;
पूर्ण

अटल व्योम nilfs_btree_nop(काष्ठा nilfs_bmap *btree,
			    काष्ठा nilfs_btree_path *path,
			    पूर्णांक level, __u64 *keyp, __u64 *ptrp)
अणु
पूर्ण

अटल पूर्णांक nilfs_btree_prepare_delete(काष्ठा nilfs_bmap *btree,
				      काष्ठा nilfs_btree_path *path,
				      पूर्णांक *levelp,
				      काष्ठा nilfs_bmap_stats *stats,
				      काष्ठा inode *dat)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_btree_node *node, *parent, *sib;
	__u64 sibptr;
	पूर्णांक pindex, dindex, level, ncmin, ncmax, ncblk, ret;

	ret = 0;
	stats->bs_nblocks = 0;
	ncmin = NILFS_BTREE_NODE_NCHILDREN_MIN(nilfs_btree_node_size(btree));
	ncblk = nilfs_btree_nchildren_per_block(btree);

	क्रम (level = NILFS_BTREE_LEVEL_NODE_MIN, dindex = path[level].bp_index;
	     level < nilfs_btree_height(btree) - 1;
	     level++) अणु
		node = nilfs_btree_get_nonroot_node(path, level);
		path[level].bp_oldreq.bpr_ptr =
			nilfs_btree_node_get_ptr(node, dindex, ncblk);
		ret = nilfs_bmap_prepare_end_ptr(btree,
						 &path[level].bp_oldreq, dat);
		अगर (ret < 0)
			जाओ err_out_child_node;

		अगर (nilfs_btree_node_get_nchildren(node) > ncmin) अणु
			path[level].bp_op = nilfs_btree_करो_delete;
			stats->bs_nblocks++;
			जाओ out;
		पूर्ण

		parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
		pindex = path[level + 1].bp_index;
		dindex = pindex;

		अगर (pindex > 0) अणु
			/* left sibling */
			sibptr = nilfs_btree_node_get_ptr(parent, pindex - 1,
							  ncmax);
			ret = nilfs_btree_get_block(btree, sibptr, &bh);
			अगर (ret < 0)
				जाओ err_out_curr_node;
			sib = (काष्ठा nilfs_btree_node *)bh->b_data;
			अगर (nilfs_btree_node_get_nchildren(sib) > ncmin) अणु
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_borrow_left;
				stats->bs_nblocks++;
				जाओ out;
			पूर्ण अन्यथा अणु
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_concat_left;
				stats->bs_nblocks++;
				/* जारी; */
			पूर्ण
		पूर्ण अन्यथा अगर (pindex <
			   nilfs_btree_node_get_nchildren(parent) - 1) अणु
			/* right sibling */
			sibptr = nilfs_btree_node_get_ptr(parent, pindex + 1,
							  ncmax);
			ret = nilfs_btree_get_block(btree, sibptr, &bh);
			अगर (ret < 0)
				जाओ err_out_curr_node;
			sib = (काष्ठा nilfs_btree_node *)bh->b_data;
			अगर (nilfs_btree_node_get_nchildren(sib) > ncmin) अणु
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_borrow_right;
				stats->bs_nblocks++;
				जाओ out;
			पूर्ण अन्यथा अणु
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_concat_right;
				stats->bs_nblocks++;
				/*
				 * When merging right sibling node
				 * पूर्णांकo the current node, poपूर्णांकer to
				 * the right sibling node must be
				 * terminated instead.  The adjusपंचांगent
				 * below is required क्रम that.
				 */
				dindex = pindex + 1;
				/* जारी; */
			पूर्ण
		पूर्ण अन्यथा अणु
			/* no siblings */
			/* the only child of the root node */
			WARN_ON(level != nilfs_btree_height(btree) - 2);
			अगर (nilfs_btree_node_get_nchildren(node) - 1 <=
			    NILFS_BTREE_ROOT_NCHILDREN_MAX) अणु
				path[level].bp_op = nilfs_btree_shrink;
				stats->bs_nblocks += 2;
				level++;
				path[level].bp_op = nilfs_btree_nop;
				जाओ shrink_root_child;
			पूर्ण अन्यथा अणु
				path[level].bp_op = nilfs_btree_करो_delete;
				stats->bs_nblocks++;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	/* child of the root node is deleted */
	path[level].bp_op = nilfs_btree_करो_delete;
	stats->bs_nblocks++;

shrink_root_child:
	node = nilfs_btree_get_root(btree);
	path[level].bp_oldreq.bpr_ptr =
		nilfs_btree_node_get_ptr(node, dindex,
					 NILFS_BTREE_ROOT_NCHILDREN_MAX);

	ret = nilfs_bmap_prepare_end_ptr(btree, &path[level].bp_oldreq, dat);
	अगर (ret < 0)
		जाओ err_out_child_node;

	/* success */
 out:
	*levelp = level;
	वापस ret;

	/* error */
 err_out_curr_node:
	nilfs_bmap_पात_end_ptr(btree, &path[level].bp_oldreq, dat);
 err_out_child_node:
	क्रम (level--; level >= NILFS_BTREE_LEVEL_NODE_MIN; level--) अणु
		brअन्यथा(path[level].bp_sib_bh);
		nilfs_bmap_पात_end_ptr(btree, &path[level].bp_oldreq, dat);
	पूर्ण
	*levelp = level;
	stats->bs_nblocks = 0;
	वापस ret;
पूर्ण

अटल व्योम nilfs_btree_commit_delete(काष्ठा nilfs_bmap *btree,
				      काष्ठा nilfs_btree_path *path,
				      पूर्णांक maxlevel, काष्ठा inode *dat)
अणु
	पूर्णांक level;

	क्रम (level = NILFS_BTREE_LEVEL_NODE_MIN; level <= maxlevel; level++) अणु
		nilfs_bmap_commit_end_ptr(btree, &path[level].bp_oldreq, dat);
		path[level].bp_op(btree, path, level, शून्य, शून्य);
	पूर्ण

	अगर (!nilfs_bmap_dirty(btree))
		nilfs_bmap_set_dirty(btree);
पूर्ण

अटल पूर्णांक nilfs_btree_delete(काष्ठा nilfs_bmap *btree, __u64 key)

अणु
	काष्ठा nilfs_btree_path *path;
	काष्ठा nilfs_bmap_stats stats;
	काष्ठा inode *dat;
	पूर्णांक level, ret;

	path = nilfs_btree_alloc_path();
	अगर (path == शून्य)
		वापस -ENOMEM;

	ret = nilfs_btree_करो_lookup(btree, path, key, शून्य,
				    NILFS_BTREE_LEVEL_NODE_MIN, 0);
	अगर (ret < 0)
		जाओ out;


	dat = NILFS_BMAP_USE_VBN(btree) ? nilfs_bmap_get_dat(btree) : शून्य;

	ret = nilfs_btree_prepare_delete(btree, path, &level, &stats, dat);
	अगर (ret < 0)
		जाओ out;
	nilfs_btree_commit_delete(btree, path, level, dat);
	nilfs_inode_sub_blocks(btree->b_inode, stats.bs_nblocks);

out:
	nilfs_btree_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_btree_seek_key(स्थिर काष्ठा nilfs_bmap *btree, __u64 start,
				__u64 *keyp)
अणु
	काष्ठा nilfs_btree_path *path;
	स्थिर पूर्णांक minlevel = NILFS_BTREE_LEVEL_NODE_MIN;
	पूर्णांक ret;

	path = nilfs_btree_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = nilfs_btree_करो_lookup(btree, path, start, शून्य, minlevel, 0);
	अगर (!ret)
		*keyp = start;
	अन्यथा अगर (ret == -ENOENT)
		ret = nilfs_btree_get_next_key(btree, path, minlevel, keyp);

	nilfs_btree_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_btree_last_key(स्थिर काष्ठा nilfs_bmap *btree, __u64 *keyp)
अणु
	काष्ठा nilfs_btree_path *path;
	पूर्णांक ret;

	path = nilfs_btree_alloc_path();
	अगर (path == शून्य)
		वापस -ENOMEM;

	ret = nilfs_btree_करो_lookup_last(btree, path, keyp, शून्य);

	nilfs_btree_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_btree_check_delete(काष्ठा nilfs_bmap *btree, __u64 key)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_btree_node *root, *node;
	__u64 maxkey, nexपंचांगaxkey;
	__u64 ptr;
	पूर्णांक nchildren, ret;

	root = nilfs_btree_get_root(btree);
	चयन (nilfs_btree_height(btree)) अणु
	हाल 2:
		bh = शून्य;
		node = root;
		अवरोध;
	हाल 3:
		nchildren = nilfs_btree_node_get_nchildren(root);
		अगर (nchildren > 1)
			वापस 0;
		ptr = nilfs_btree_node_get_ptr(root, nchildren - 1,
					       NILFS_BTREE_ROOT_NCHILDREN_MAX);
		ret = nilfs_btree_get_block(btree, ptr, &bh);
		अगर (ret < 0)
			वापस ret;
		node = (काष्ठा nilfs_btree_node *)bh->b_data;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	nchildren = nilfs_btree_node_get_nchildren(node);
	maxkey = nilfs_btree_node_get_key(node, nchildren - 1);
	nexपंचांगaxkey = (nchildren > 1) ?
		nilfs_btree_node_get_key(node, nchildren - 2) : 0;
	अगर (bh != शून्य)
		brअन्यथा(bh);

	वापस (maxkey == key) && (nexपंचांगaxkey < NILFS_BMAP_LARGE_LOW);
पूर्ण

अटल पूर्णांक nilfs_btree_gather_data(काष्ठा nilfs_bmap *btree,
				   __u64 *keys, __u64 *ptrs, पूर्णांक nitems)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_btree_node *node, *root;
	__le64 *dkeys;
	__le64 *dptrs;
	__u64 ptr;
	पूर्णांक nchildren, ncmax, i, ret;

	root = nilfs_btree_get_root(btree);
	चयन (nilfs_btree_height(btree)) अणु
	हाल 2:
		bh = शून्य;
		node = root;
		ncmax = NILFS_BTREE_ROOT_NCHILDREN_MAX;
		अवरोध;
	हाल 3:
		nchildren = nilfs_btree_node_get_nchildren(root);
		WARN_ON(nchildren > 1);
		ptr = nilfs_btree_node_get_ptr(root, nchildren - 1,
					       NILFS_BTREE_ROOT_NCHILDREN_MAX);
		ret = nilfs_btree_get_block(btree, ptr, &bh);
		अगर (ret < 0)
			वापस ret;
		node = (काष्ठा nilfs_btree_node *)bh->b_data;
		ncmax = nilfs_btree_nchildren_per_block(btree);
		अवरोध;
	शेष:
		node = शून्य;
		वापस -EINVAL;
	पूर्ण

	nchildren = nilfs_btree_node_get_nchildren(node);
	अगर (nchildren < nitems)
		nitems = nchildren;
	dkeys = nilfs_btree_node_dkeys(node);
	dptrs = nilfs_btree_node_dptrs(node, ncmax);
	क्रम (i = 0; i < nitems; i++) अणु
		keys[i] = le64_to_cpu(dkeys[i]);
		ptrs[i] = le64_to_cpu(dptrs[i]);
	पूर्ण

	अगर (bh != शून्य)
		brअन्यथा(bh);

	वापस nitems;
पूर्ण

अटल पूर्णांक
nilfs_btree_prepare_convert_and_insert(काष्ठा nilfs_bmap *btree, __u64 key,
				       जोड़ nilfs_bmap_ptr_req *dreq,
				       जोड़ nilfs_bmap_ptr_req *nreq,
				       काष्ठा buffer_head **bhp,
				       काष्ठा nilfs_bmap_stats *stats)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा inode *dat = शून्य;
	पूर्णांक ret;

	stats->bs_nblocks = 0;

	/* क्रम data */
	/* cannot find near ptr */
	अगर (NILFS_BMAP_USE_VBN(btree)) अणु
		dreq->bpr_ptr = nilfs_btree_find_target_v(btree, शून्य, key);
		dat = nilfs_bmap_get_dat(btree);
	पूर्ण

	ret = nilfs_bmap_prepare_alloc_ptr(btree, dreq, dat);
	अगर (ret < 0)
		वापस ret;

	*bhp = शून्य;
	stats->bs_nblocks++;
	अगर (nreq != शून्य) अणु
		nreq->bpr_ptr = dreq->bpr_ptr + 1;
		ret = nilfs_bmap_prepare_alloc_ptr(btree, nreq, dat);
		अगर (ret < 0)
			जाओ err_out_dreq;

		ret = nilfs_btree_get_new_block(btree, nreq->bpr_ptr, &bh);
		अगर (ret < 0)
			जाओ err_out_nreq;

		*bhp = bh;
		stats->bs_nblocks++;
	पूर्ण

	/* success */
	वापस 0;

	/* error */
 err_out_nreq:
	nilfs_bmap_पात_alloc_ptr(btree, nreq, dat);
 err_out_dreq:
	nilfs_bmap_पात_alloc_ptr(btree, dreq, dat);
	stats->bs_nblocks = 0;
	वापस ret;

पूर्ण

अटल व्योम
nilfs_btree_commit_convert_and_insert(काष्ठा nilfs_bmap *btree,
				      __u64 key, __u64 ptr,
				      स्थिर __u64 *keys, स्थिर __u64 *ptrs,
				      पूर्णांक n,
				      जोड़ nilfs_bmap_ptr_req *dreq,
				      जोड़ nilfs_bmap_ptr_req *nreq,
				      काष्ठा buffer_head *bh)
अणु
	काष्ठा nilfs_btree_node *node;
	काष्ठा inode *dat;
	__u64 पंचांगpptr;
	पूर्णांक ncblk;

	/* मुक्त resources */
	अगर (btree->b_ops->bop_clear != शून्य)
		btree->b_ops->bop_clear(btree);

	/* ptr must be a poपूर्णांकer to a buffer head. */
	set_buffer_nilfs_अस्थिर((काष्ठा buffer_head *)((अचिन्हित दीर्घ)ptr));

	/* convert and insert */
	dat = NILFS_BMAP_USE_VBN(btree) ? nilfs_bmap_get_dat(btree) : शून्य;
	__nilfs_btree_init(btree);
	अगर (nreq != शून्य) अणु
		nilfs_bmap_commit_alloc_ptr(btree, dreq, dat);
		nilfs_bmap_commit_alloc_ptr(btree, nreq, dat);

		/* create child node at level 1 */
		node = (काष्ठा nilfs_btree_node *)bh->b_data;
		ncblk = nilfs_btree_nchildren_per_block(btree);
		nilfs_btree_node_init(node, 0, 1, n, ncblk, keys, ptrs);
		nilfs_btree_node_insert(node, n, key, dreq->bpr_ptr, ncblk);
		अगर (!buffer_dirty(bh))
			mark_buffer_dirty(bh);
		अगर (!nilfs_bmap_dirty(btree))
			nilfs_bmap_set_dirty(btree);

		brअन्यथा(bh);

		/* create root node at level 2 */
		node = nilfs_btree_get_root(btree);
		पंचांगpptr = nreq->bpr_ptr;
		nilfs_btree_node_init(node, NILFS_BTREE_NODE_ROOT, 2, 1,
				      NILFS_BTREE_ROOT_NCHILDREN_MAX,
				      &keys[0], &पंचांगpptr);
	पूर्ण अन्यथा अणु
		nilfs_bmap_commit_alloc_ptr(btree, dreq, dat);

		/* create root node at level 1 */
		node = nilfs_btree_get_root(btree);
		nilfs_btree_node_init(node, NILFS_BTREE_NODE_ROOT, 1, n,
				      NILFS_BTREE_ROOT_NCHILDREN_MAX,
				      keys, ptrs);
		nilfs_btree_node_insert(node, n, key, dreq->bpr_ptr,
					NILFS_BTREE_ROOT_NCHILDREN_MAX);
		अगर (!nilfs_bmap_dirty(btree))
			nilfs_bmap_set_dirty(btree);
	पूर्ण

	अगर (NILFS_BMAP_USE_VBN(btree))
		nilfs_bmap_set_target_v(btree, key, dreq->bpr_ptr);
पूर्ण

/**
 * nilfs_btree_convert_and_insert -
 * @bmap:
 * @key:
 * @ptr:
 * @keys:
 * @ptrs:
 * @n:
 */
पूर्णांक nilfs_btree_convert_and_insert(काष्ठा nilfs_bmap *btree,
				   __u64 key, __u64 ptr,
				   स्थिर __u64 *keys, स्थिर __u64 *ptrs, पूर्णांक n)
अणु
	काष्ठा buffer_head *bh = शून्य;
	जोड़ nilfs_bmap_ptr_req dreq, nreq, *di, *ni;
	काष्ठा nilfs_bmap_stats stats;
	पूर्णांक ret;

	अगर (n + 1 <= NILFS_BTREE_ROOT_NCHILDREN_MAX) अणु
		di = &dreq;
		ni = शून्य;
	पूर्ण अन्यथा अगर ((n + 1) <= NILFS_BTREE_NODE_NCHILDREN_MAX(
			   nilfs_btree_node_size(btree))) अणु
		di = &dreq;
		ni = &nreq;
	पूर्ण अन्यथा अणु
		di = शून्य;
		ni = शून्य;
		BUG();
	पूर्ण

	ret = nilfs_btree_prepare_convert_and_insert(btree, key, di, ni, &bh,
						     &stats);
	अगर (ret < 0)
		वापस ret;
	nilfs_btree_commit_convert_and_insert(btree, key, ptr, keys, ptrs, n,
					      di, ni, bh);
	nilfs_inode_add_blocks(btree->b_inode, stats.bs_nblocks);
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_btree_propagate_p(काष्ठा nilfs_bmap *btree,
				   काष्ठा nilfs_btree_path *path,
				   पूर्णांक level,
				   काष्ठा buffer_head *bh)
अणु
	जबतक ((++level < nilfs_btree_height(btree) - 1) &&
	       !buffer_dirty(path[level].bp_bh))
		mark_buffer_dirty(path[level].bp_bh);

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_btree_prepare_update_v(काष्ठा nilfs_bmap *btree,
					काष्ठा nilfs_btree_path *path,
					पूर्णांक level, काष्ठा inode *dat)
अणु
	काष्ठा nilfs_btree_node *parent;
	पूर्णांक ncmax, ret;

	parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
	path[level].bp_oldreq.bpr_ptr =
		nilfs_btree_node_get_ptr(parent, path[level + 1].bp_index,
					 ncmax);
	path[level].bp_newreq.bpr_ptr = path[level].bp_oldreq.bpr_ptr + 1;
	ret = nilfs_dat_prepare_update(dat, &path[level].bp_oldreq.bpr_req,
				       &path[level].bp_newreq.bpr_req);
	अगर (ret < 0)
		वापस ret;

	अगर (buffer_nilfs_node(path[level].bp_bh)) अणु
		path[level].bp_ctxt.oldkey = path[level].bp_oldreq.bpr_ptr;
		path[level].bp_ctxt.newkey = path[level].bp_newreq.bpr_ptr;
		path[level].bp_ctxt.bh = path[level].bp_bh;
		ret = nilfs_btnode_prepare_change_key(
			&NILFS_BMAP_I(btree)->i_btnode_cache,
			&path[level].bp_ctxt);
		अगर (ret < 0) अणु
			nilfs_dat_पात_update(dat,
					       &path[level].bp_oldreq.bpr_req,
					       &path[level].bp_newreq.bpr_req);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nilfs_btree_commit_update_v(काष्ठा nilfs_bmap *btree,
					काष्ठा nilfs_btree_path *path,
					पूर्णांक level, काष्ठा inode *dat)
अणु
	काष्ठा nilfs_btree_node *parent;
	पूर्णांक ncmax;

	nilfs_dat_commit_update(dat, &path[level].bp_oldreq.bpr_req,
				&path[level].bp_newreq.bpr_req,
				btree->b_ptr_type == NILFS_BMAP_PTR_VS);

	अगर (buffer_nilfs_node(path[level].bp_bh)) अणु
		nilfs_btnode_commit_change_key(
			&NILFS_BMAP_I(btree)->i_btnode_cache,
			&path[level].bp_ctxt);
		path[level].bp_bh = path[level].bp_ctxt.bh;
	पूर्ण
	set_buffer_nilfs_अस्थिर(path[level].bp_bh);

	parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
	nilfs_btree_node_set_ptr(parent, path[level + 1].bp_index,
				 path[level].bp_newreq.bpr_ptr, ncmax);
पूर्ण

अटल व्योम nilfs_btree_पात_update_v(काष्ठा nilfs_bmap *btree,
				       काष्ठा nilfs_btree_path *path,
				       पूर्णांक level, काष्ठा inode *dat)
अणु
	nilfs_dat_पात_update(dat, &path[level].bp_oldreq.bpr_req,
			       &path[level].bp_newreq.bpr_req);
	अगर (buffer_nilfs_node(path[level].bp_bh))
		nilfs_btnode_पात_change_key(
			&NILFS_BMAP_I(btree)->i_btnode_cache,
			&path[level].bp_ctxt);
पूर्ण

अटल पूर्णांक nilfs_btree_prepare_propagate_v(काष्ठा nilfs_bmap *btree,
					   काष्ठा nilfs_btree_path *path,
					   पूर्णांक minlevel, पूर्णांक *maxlevelp,
					   काष्ठा inode *dat)
अणु
	पूर्णांक level, ret;

	level = minlevel;
	अगर (!buffer_nilfs_अस्थिर(path[level].bp_bh)) अणु
		ret = nilfs_btree_prepare_update_v(btree, path, level, dat);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	जबतक ((++level < nilfs_btree_height(btree) - 1) &&
	       !buffer_dirty(path[level].bp_bh)) अणु

		WARN_ON(buffer_nilfs_अस्थिर(path[level].bp_bh));
		ret = nilfs_btree_prepare_update_v(btree, path, level, dat);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* success */
	*maxlevelp = level - 1;
	वापस 0;

	/* error */
 out:
	जबतक (--level > minlevel)
		nilfs_btree_पात_update_v(btree, path, level, dat);
	अगर (!buffer_nilfs_अस्थिर(path[level].bp_bh))
		nilfs_btree_पात_update_v(btree, path, level, dat);
	वापस ret;
पूर्ण

अटल व्योम nilfs_btree_commit_propagate_v(काष्ठा nilfs_bmap *btree,
					   काष्ठा nilfs_btree_path *path,
					   पूर्णांक minlevel, पूर्णांक maxlevel,
					   काष्ठा buffer_head *bh,
					   काष्ठा inode *dat)
अणु
	पूर्णांक level;

	अगर (!buffer_nilfs_अस्थिर(path[minlevel].bp_bh))
		nilfs_btree_commit_update_v(btree, path, minlevel, dat);

	क्रम (level = minlevel + 1; level <= maxlevel; level++)
		nilfs_btree_commit_update_v(btree, path, level, dat);
पूर्ण

अटल पूर्णांक nilfs_btree_propagate_v(काष्ठा nilfs_bmap *btree,
				   काष्ठा nilfs_btree_path *path,
				   पूर्णांक level, काष्ठा buffer_head *bh)
अणु
	पूर्णांक maxlevel = 0, ret;
	काष्ठा nilfs_btree_node *parent;
	काष्ठा inode *dat = nilfs_bmap_get_dat(btree);
	__u64 ptr;
	पूर्णांक ncmax;

	get_bh(bh);
	path[level].bp_bh = bh;
	ret = nilfs_btree_prepare_propagate_v(btree, path, level, &maxlevel,
					      dat);
	अगर (ret < 0)
		जाओ out;

	अगर (buffer_nilfs_अस्थिर(path[level].bp_bh)) अणु
		parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
		ptr = nilfs_btree_node_get_ptr(parent,
					       path[level + 1].bp_index,
					       ncmax);
		ret = nilfs_dat_mark_dirty(dat, ptr);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	nilfs_btree_commit_propagate_v(btree, path, level, maxlevel, bh, dat);

 out:
	brअन्यथा(path[level].bp_bh);
	path[level].bp_bh = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_btree_propagate(काष्ठा nilfs_bmap *btree,
				 काष्ठा buffer_head *bh)
अणु
	काष्ठा nilfs_btree_path *path;
	काष्ठा nilfs_btree_node *node;
	__u64 key;
	पूर्णांक level, ret;

	WARN_ON(!buffer_dirty(bh));

	path = nilfs_btree_alloc_path();
	अगर (path == शून्य)
		वापस -ENOMEM;

	अगर (buffer_nilfs_node(bh)) अणु
		node = (काष्ठा nilfs_btree_node *)bh->b_data;
		key = nilfs_btree_node_get_key(node, 0);
		level = nilfs_btree_node_get_level(node);
	पूर्ण अन्यथा अणु
		key = nilfs_bmap_data_get_key(btree, bh);
		level = NILFS_BTREE_LEVEL_DATA;
	पूर्ण

	ret = nilfs_btree_करो_lookup(btree, path, key, शून्य, level + 1, 0);
	अगर (ret < 0) अणु
		अगर (unlikely(ret == -ENOENT))
			nilfs_crit(btree->b_inode->i_sb,
				   "writing node/leaf block does not appear in b-tree (ino=%lu) at key=%llu, level=%d",
				   btree->b_inode->i_ino,
				   (अचिन्हित दीर्घ दीर्घ)key, level);
		जाओ out;
	पूर्ण

	ret = NILFS_BMAP_USE_VBN(btree) ?
		nilfs_btree_propagate_v(btree, path, level, bh) :
		nilfs_btree_propagate_p(btree, path, level, bh);

 out:
	nilfs_btree_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_btree_propagate_gc(काष्ठा nilfs_bmap *btree,
				    काष्ठा buffer_head *bh)
अणु
	वापस nilfs_dat_mark_dirty(nilfs_bmap_get_dat(btree), bh->b_blocknr);
पूर्ण

अटल व्योम nilfs_btree_add_dirty_buffer(काष्ठा nilfs_bmap *btree,
					 काष्ठा list_head *lists,
					 काष्ठा buffer_head *bh)
अणु
	काष्ठा list_head *head;
	काष्ठा buffer_head *cbh;
	काष्ठा nilfs_btree_node *node, *cnode;
	__u64 key, ckey;
	पूर्णांक level;

	get_bh(bh);
	node = (काष्ठा nilfs_btree_node *)bh->b_data;
	key = nilfs_btree_node_get_key(node, 0);
	level = nilfs_btree_node_get_level(node);
	अगर (level < NILFS_BTREE_LEVEL_NODE_MIN ||
	    level >= NILFS_BTREE_LEVEL_MAX) अणु
		dump_stack();
		nilfs_warn(btree->b_inode->i_sb,
			   "invalid btree level: %d (key=%llu, ino=%lu, blocknr=%llu)",
			   level, (अचिन्हित दीर्घ दीर्घ)key,
			   btree->b_inode->i_ino,
			   (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस;
	पूर्ण

	list_क्रम_each(head, &lists[level]) अणु
		cbh = list_entry(head, काष्ठा buffer_head, b_assoc_buffers);
		cnode = (काष्ठा nilfs_btree_node *)cbh->b_data;
		ckey = nilfs_btree_node_get_key(cnode, 0);
		अगर (key < ckey)
			अवरोध;
	पूर्ण
	list_add_tail(&bh->b_assoc_buffers, head);
पूर्ण

अटल व्योम nilfs_btree_lookup_dirty_buffers(काष्ठा nilfs_bmap *btree,
					     काष्ठा list_head *listp)
अणु
	काष्ठा address_space *btcache = &NILFS_BMAP_I(btree)->i_btnode_cache;
	काष्ठा list_head lists[NILFS_BTREE_LEVEL_MAX];
	काष्ठा pagevec pvec;
	काष्ठा buffer_head *bh, *head;
	pgoff_t index = 0;
	पूर्णांक level, i;

	क्रम (level = NILFS_BTREE_LEVEL_NODE_MIN;
	     level < NILFS_BTREE_LEVEL_MAX;
	     level++)
		INIT_LIST_HEAD(&lists[level]);

	pagevec_init(&pvec);

	जबतक (pagevec_lookup_tag(&pvec, btcache, &index,
					PAGECACHE_TAG_सूचीTY)) अणु
		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			bh = head = page_buffers(pvec.pages[i]);
			करो अणु
				अगर (buffer_dirty(bh))
					nilfs_btree_add_dirty_buffer(btree,
								     lists, bh);
			पूर्ण जबतक ((bh = bh->b_this_page) != head);
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण

	क्रम (level = NILFS_BTREE_LEVEL_NODE_MIN;
	     level < NILFS_BTREE_LEVEL_MAX;
	     level++)
		list_splice_tail(&lists[level], listp);
पूर्ण

अटल पूर्णांक nilfs_btree_assign_p(काष्ठा nilfs_bmap *btree,
				काष्ठा nilfs_btree_path *path,
				पूर्णांक level,
				काष्ठा buffer_head **bh,
				sector_t blocknr,
				जोड़ nilfs_binfo *binfo)
अणु
	काष्ठा nilfs_btree_node *parent;
	__u64 key;
	__u64 ptr;
	पूर्णांक ncmax, ret;

	parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
	ptr = nilfs_btree_node_get_ptr(parent, path[level + 1].bp_index,
				       ncmax);
	अगर (buffer_nilfs_node(*bh)) अणु
		path[level].bp_ctxt.oldkey = ptr;
		path[level].bp_ctxt.newkey = blocknr;
		path[level].bp_ctxt.bh = *bh;
		ret = nilfs_btnode_prepare_change_key(
			&NILFS_BMAP_I(btree)->i_btnode_cache,
			&path[level].bp_ctxt);
		अगर (ret < 0)
			वापस ret;
		nilfs_btnode_commit_change_key(
			&NILFS_BMAP_I(btree)->i_btnode_cache,
			&path[level].bp_ctxt);
		*bh = path[level].bp_ctxt.bh;
	पूर्ण

	nilfs_btree_node_set_ptr(parent, path[level + 1].bp_index, blocknr,
				 ncmax);

	key = nilfs_btree_node_get_key(parent, path[level + 1].bp_index);
	/* on-disk क्रमmat */
	binfo->bi_dat.bi_blkoff = cpu_to_le64(key);
	binfo->bi_dat.bi_level = level;

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_btree_assign_v(काष्ठा nilfs_bmap *btree,
				काष्ठा nilfs_btree_path *path,
				पूर्णांक level,
				काष्ठा buffer_head **bh,
				sector_t blocknr,
				जोड़ nilfs_binfo *binfo)
अणु
	काष्ठा nilfs_btree_node *parent;
	काष्ठा inode *dat = nilfs_bmap_get_dat(btree);
	__u64 key;
	__u64 ptr;
	जोड़ nilfs_bmap_ptr_req req;
	पूर्णांक ncmax, ret;

	parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
	ptr = nilfs_btree_node_get_ptr(parent, path[level + 1].bp_index,
				       ncmax);
	req.bpr_ptr = ptr;
	ret = nilfs_dat_prepare_start(dat, &req.bpr_req);
	अगर (ret < 0)
		वापस ret;
	nilfs_dat_commit_start(dat, &req.bpr_req, blocknr);

	key = nilfs_btree_node_get_key(parent, path[level + 1].bp_index);
	/* on-disk क्रमmat */
	binfo->bi_v.bi_vblocknr = cpu_to_le64(ptr);
	binfo->bi_v.bi_blkoff = cpu_to_le64(key);

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_btree_assign(काष्ठा nilfs_bmap *btree,
			      काष्ठा buffer_head **bh,
			      sector_t blocknr,
			      जोड़ nilfs_binfo *binfo)
अणु
	काष्ठा nilfs_btree_path *path;
	काष्ठा nilfs_btree_node *node;
	__u64 key;
	पूर्णांक level, ret;

	path = nilfs_btree_alloc_path();
	अगर (path == शून्य)
		वापस -ENOMEM;

	अगर (buffer_nilfs_node(*bh)) अणु
		node = (काष्ठा nilfs_btree_node *)(*bh)->b_data;
		key = nilfs_btree_node_get_key(node, 0);
		level = nilfs_btree_node_get_level(node);
	पूर्ण अन्यथा अणु
		key = nilfs_bmap_data_get_key(btree, *bh);
		level = NILFS_BTREE_LEVEL_DATA;
	पूर्ण

	ret = nilfs_btree_करो_lookup(btree, path, key, शून्य, level + 1, 0);
	अगर (ret < 0) अणु
		WARN_ON(ret == -ENOENT);
		जाओ out;
	पूर्ण

	ret = NILFS_BMAP_USE_VBN(btree) ?
		nilfs_btree_assign_v(btree, path, level, bh, blocknr, binfo) :
		nilfs_btree_assign_p(btree, path, level, bh, blocknr, binfo);

 out:
	nilfs_btree_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_btree_assign_gc(काष्ठा nilfs_bmap *btree,
				 काष्ठा buffer_head **bh,
				 sector_t blocknr,
				 जोड़ nilfs_binfo *binfo)
अणु
	काष्ठा nilfs_btree_node *node;
	__u64 key;
	पूर्णांक ret;

	ret = nilfs_dat_move(nilfs_bmap_get_dat(btree), (*bh)->b_blocknr,
			     blocknr);
	अगर (ret < 0)
		वापस ret;

	अगर (buffer_nilfs_node(*bh)) अणु
		node = (काष्ठा nilfs_btree_node *)(*bh)->b_data;
		key = nilfs_btree_node_get_key(node, 0);
	पूर्ण अन्यथा
		key = nilfs_bmap_data_get_key(btree, *bh);

	/* on-disk क्रमmat */
	binfo->bi_v.bi_vblocknr = cpu_to_le64((*bh)->b_blocknr);
	binfo->bi_v.bi_blkoff = cpu_to_le64(key);

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_btree_mark(काष्ठा nilfs_bmap *btree, __u64 key, पूर्णांक level)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_btree_path *path;
	__u64 ptr;
	पूर्णांक ret;

	path = nilfs_btree_alloc_path();
	अगर (path == शून्य)
		वापस -ENOMEM;

	ret = nilfs_btree_करो_lookup(btree, path, key, &ptr, level + 1, 0);
	अगर (ret < 0) अणु
		WARN_ON(ret == -ENOENT);
		जाओ out;
	पूर्ण
	ret = nilfs_btree_get_block(btree, ptr, &bh);
	अगर (ret < 0) अणु
		WARN_ON(ret == -ENOENT);
		जाओ out;
	पूर्ण

	अगर (!buffer_dirty(bh))
		mark_buffer_dirty(bh);
	brअन्यथा(bh);
	अगर (!nilfs_bmap_dirty(btree))
		nilfs_bmap_set_dirty(btree);

 out:
	nilfs_btree_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nilfs_bmap_operations nilfs_btree_ops = अणु
	.bop_lookup		=	nilfs_btree_lookup,
	.bop_lookup_contig	=	nilfs_btree_lookup_contig,
	.bop_insert		=	nilfs_btree_insert,
	.bop_delete		=	nilfs_btree_delete,
	.bop_clear		=	शून्य,

	.bop_propagate		=	nilfs_btree_propagate,

	.bop_lookup_dirty_buffers =	nilfs_btree_lookup_dirty_buffers,

	.bop_assign		=	nilfs_btree_assign,
	.bop_mark		=	nilfs_btree_mark,

	.bop_seek_key		=	nilfs_btree_seek_key,
	.bop_last_key		=	nilfs_btree_last_key,

	.bop_check_insert	=	शून्य,
	.bop_check_delete	=	nilfs_btree_check_delete,
	.bop_gather_data	=	nilfs_btree_gather_data,
पूर्ण;

अटल स्थिर काष्ठा nilfs_bmap_operations nilfs_btree_ops_gc = अणु
	.bop_lookup		=	शून्य,
	.bop_lookup_contig	=	शून्य,
	.bop_insert		=	शून्य,
	.bop_delete		=	शून्य,
	.bop_clear		=	शून्य,

	.bop_propagate		=	nilfs_btree_propagate_gc,

	.bop_lookup_dirty_buffers =	nilfs_btree_lookup_dirty_buffers,

	.bop_assign		=	nilfs_btree_assign_gc,
	.bop_mark		=	शून्य,

	.bop_seek_key		=	शून्य,
	.bop_last_key		=	शून्य,

	.bop_check_insert	=	शून्य,
	.bop_check_delete	=	शून्य,
	.bop_gather_data	=	शून्य,
पूर्ण;

अटल व्योम __nilfs_btree_init(काष्ठा nilfs_bmap *bmap)
अणु
	bmap->b_ops = &nilfs_btree_ops;
	bmap->b_nchildren_per_block =
		NILFS_BTREE_NODE_NCHILDREN_MAX(nilfs_btree_node_size(bmap));
पूर्ण

पूर्णांक nilfs_btree_init(काष्ठा nilfs_bmap *bmap)
अणु
	पूर्णांक ret = 0;

	__nilfs_btree_init(bmap);

	अगर (nilfs_btree_root_broken(nilfs_btree_get_root(bmap), bmap->b_inode))
		ret = -EIO;
	वापस ret;
पूर्ण

व्योम nilfs_btree_init_gc(काष्ठा nilfs_bmap *bmap)
अणु
	bmap->b_ops = &nilfs_btree_ops_gc;
	bmap->b_nchildren_per_block =
		NILFS_BTREE_NODE_NCHILDREN_MAX(nilfs_btree_node_size(bmap));
पूर्ण

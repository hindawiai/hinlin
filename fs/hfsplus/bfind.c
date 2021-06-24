<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/bfind.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Search routines क्रम btrees
 */

#समावेश <linux/slab.h>
#समावेश "hfsplus_fs.h"

पूर्णांक hfs_find_init(काष्ठा hfs_btree *tree, काष्ठा hfs_find_data *fd)
अणु
	व्योम *ptr;

	fd->tree = tree;
	fd->bnode = शून्य;
	ptr = kदो_स्मृति(tree->max_key_len * 2 + 4, GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;
	fd->search_key = ptr;
	fd->key = ptr + tree->max_key_len + 2;
	hfs_dbg(BNODE_REFS, "find_init: %d (%p)\n",
		tree->cnid, __builtin_वापस_address(0));
	चयन (tree->cnid) अणु
	हाल HFSPLUS_CAT_CNID:
		mutex_lock_nested(&tree->tree_lock, CATALOG_BTREE_MUTEX);
		अवरोध;
	हाल HFSPLUS_EXT_CNID:
		mutex_lock_nested(&tree->tree_lock, EXTENTS_BTREE_MUTEX);
		अवरोध;
	हाल HFSPLUS_ATTR_CNID:
		mutex_lock_nested(&tree->tree_lock, ATTR_BTREE_MUTEX);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

व्योम hfs_find_निकास(काष्ठा hfs_find_data *fd)
अणु
	hfs_bnode_put(fd->bnode);
	kमुक्त(fd->search_key);
	hfs_dbg(BNODE_REFS, "find_exit: %d (%p)\n",
		fd->tree->cnid, __builtin_वापस_address(0));
	mutex_unlock(&fd->tree->tree_lock);
	fd->tree = शून्य;
पूर्ण

पूर्णांक hfs_find_1st_rec_by_cnid(काष्ठा hfs_bnode *bnode,
				काष्ठा hfs_find_data *fd,
				पूर्णांक *begin,
				पूर्णांक *end,
				पूर्णांक *cur_rec)
अणु
	__be32 cur_cnid;
	__be32 search_cnid;

	अगर (bnode->tree->cnid == HFSPLUS_EXT_CNID) अणु
		cur_cnid = fd->key->ext.cnid;
		search_cnid = fd->search_key->ext.cnid;
	पूर्ण अन्यथा अगर (bnode->tree->cnid == HFSPLUS_CAT_CNID) अणु
		cur_cnid = fd->key->cat.parent;
		search_cnid = fd->search_key->cat.parent;
	पूर्ण अन्यथा अगर (bnode->tree->cnid == HFSPLUS_ATTR_CNID) अणु
		cur_cnid = fd->key->attr.cnid;
		search_cnid = fd->search_key->attr.cnid;
	पूर्ण अन्यथा अणु
		cur_cnid = 0;	/* used-uninitialized warning */
		search_cnid = 0;
		BUG();
	पूर्ण

	अगर (cur_cnid == search_cnid) अणु
		(*end) = (*cur_rec);
		अगर ((*begin) == (*end))
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (be32_to_cpu(cur_cnid) < be32_to_cpu(search_cnid))
			(*begin) = (*cur_rec) + 1;
		अन्यथा
			(*end) = (*cur_rec) - 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hfs_find_rec_by_key(काष्ठा hfs_bnode *bnode,
				काष्ठा hfs_find_data *fd,
				पूर्णांक *begin,
				पूर्णांक *end,
				पूर्णांक *cur_rec)
अणु
	पूर्णांक cmpval;

	cmpval = bnode->tree->keycmp(fd->key, fd->search_key);
	अगर (!cmpval) अणु
		(*end) = (*cur_rec);
		वापस 1;
	पूर्ण
	अगर (cmpval < 0)
		(*begin) = (*cur_rec) + 1;
	अन्यथा
		*(end) = (*cur_rec) - 1;

	वापस 0;
पूर्ण

/* Find the record in bnode that best matches key (not greater than...)*/
पूर्णांक __hfs_brec_find(काष्ठा hfs_bnode *bnode, काष्ठा hfs_find_data *fd,
					search_strategy_t rec_found)
अणु
	u16 off, len, keylen;
	पूर्णांक rec;
	पूर्णांक b, e;
	पूर्णांक res;

	BUG_ON(!rec_found);
	b = 0;
	e = bnode->num_recs - 1;
	res = -ENOENT;
	करो अणु
		rec = (e + b) / 2;
		len = hfs_brec_lenoff(bnode, rec, &off);
		keylen = hfs_brec_keylen(bnode, rec);
		अगर (keylen == 0) अणु
			res = -EINVAL;
			जाओ fail;
		पूर्ण
		hfs_bnode_पढ़ो(bnode, fd->key, off, keylen);
		अगर (rec_found(bnode, fd, &b, &e, &rec)) अणु
			res = 0;
			जाओ करोne;
		पूर्ण
	पूर्ण जबतक (b <= e);

	अगर (rec != e && e >= 0) अणु
		len = hfs_brec_lenoff(bnode, e, &off);
		keylen = hfs_brec_keylen(bnode, e);
		अगर (keylen == 0) अणु
			res = -EINVAL;
			जाओ fail;
		पूर्ण
		hfs_bnode_पढ़ो(bnode, fd->key, off, keylen);
	पूर्ण

करोne:
	fd->record = e;
	fd->keyoffset = off;
	fd->keylength = keylen;
	fd->entryoffset = off + keylen;
	fd->entrylength = len - keylen;

fail:
	वापस res;
पूर्ण

/* Traverse a B*Tree from the root to a leaf finding best fit to key */
/* Return allocated copy of node found, set recnum to best record */
पूर्णांक hfs_brec_find(काष्ठा hfs_find_data *fd, search_strategy_t करो_key_compare)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *bnode;
	u32 nidx, parent;
	__be32 data;
	पूर्णांक height, res;

	tree = fd->tree;
	अगर (fd->bnode)
		hfs_bnode_put(fd->bnode);
	fd->bnode = शून्य;
	nidx = tree->root;
	अगर (!nidx)
		वापस -ENOENT;
	height = tree->depth;
	res = 0;
	parent = 0;
	क्रम (;;) अणु
		bnode = hfs_bnode_find(tree, nidx);
		अगर (IS_ERR(bnode)) अणु
			res = PTR_ERR(bnode);
			bnode = शून्य;
			अवरोध;
		पूर्ण
		अगर (bnode->height != height)
			जाओ invalid;
		अगर (bnode->type != (--height ? HFS_NODE_INDEX : HFS_NODE_LEAF))
			जाओ invalid;
		bnode->parent = parent;

		res = __hfs_brec_find(bnode, fd, करो_key_compare);
		अगर (!height)
			अवरोध;
		अगर (fd->record < 0)
			जाओ release;

		parent = nidx;
		hfs_bnode_पढ़ो(bnode, &data, fd->entryoffset, 4);
		nidx = be32_to_cpu(data);
		hfs_bnode_put(bnode);
	पूर्ण
	fd->bnode = bnode;
	वापस res;

invalid:
	pr_err("inconsistency in B*Tree (%d,%d,%d,%u,%u)\n",
		height, bnode->height, bnode->type, nidx, parent);
	res = -EIO;
release:
	hfs_bnode_put(bnode);
	वापस res;
पूर्ण

पूर्णांक hfs_brec_पढ़ो(काष्ठा hfs_find_data *fd, व्योम *rec, पूर्णांक rec_len)
अणु
	पूर्णांक res;

	res = hfs_brec_find(fd, hfs_find_rec_by_key);
	अगर (res)
		वापस res;
	अगर (fd->entrylength > rec_len)
		वापस -EINVAL;
	hfs_bnode_पढ़ो(fd->bnode, rec, fd->entryoffset, fd->entrylength);
	वापस 0;
पूर्ण

पूर्णांक hfs_brec_जाओ(काष्ठा hfs_find_data *fd, पूर्णांक cnt)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *bnode;
	पूर्णांक idx, res = 0;
	u16 off, len, keylen;

	bnode = fd->bnode;
	tree = bnode->tree;

	अगर (cnt < 0) अणु
		cnt = -cnt;
		जबतक (cnt > fd->record) अणु
			cnt -= fd->record + 1;
			fd->record = bnode->num_recs - 1;
			idx = bnode->prev;
			अगर (!idx) अणु
				res = -ENOENT;
				जाओ out;
			पूर्ण
			hfs_bnode_put(bnode);
			bnode = hfs_bnode_find(tree, idx);
			अगर (IS_ERR(bnode)) अणु
				res = PTR_ERR(bnode);
				bnode = शून्य;
				जाओ out;
			पूर्ण
		पूर्ण
		fd->record -= cnt;
	पूर्ण अन्यथा अणु
		जबतक (cnt >= bnode->num_recs - fd->record) अणु
			cnt -= bnode->num_recs - fd->record;
			fd->record = 0;
			idx = bnode->next;
			अगर (!idx) अणु
				res = -ENOENT;
				जाओ out;
			पूर्ण
			hfs_bnode_put(bnode);
			bnode = hfs_bnode_find(tree, idx);
			अगर (IS_ERR(bnode)) अणु
				res = PTR_ERR(bnode);
				bnode = शून्य;
				जाओ out;
			पूर्ण
		पूर्ण
		fd->record += cnt;
	पूर्ण

	len = hfs_brec_lenoff(bnode, fd->record, &off);
	keylen = hfs_brec_keylen(bnode, fd->record);
	अगर (keylen == 0) अणु
		res = -EINVAL;
		जाओ out;
	पूर्ण
	fd->keyoffset = off;
	fd->keylength = keylen;
	fd->entryoffset = off + keylen;
	fd->entrylength = len - keylen;
	hfs_bnode_पढ़ो(bnode, fd->key, off, keylen);
out:
	fd->bnode = bnode;
	वापस res;
पूर्ण

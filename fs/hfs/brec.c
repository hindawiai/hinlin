<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfs/brec.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handle inभागidual btree records
 */

#समावेश "btree.h"

अटल काष्ठा hfs_bnode *hfs_bnode_split(काष्ठा hfs_find_data *fd);
अटल पूर्णांक hfs_brec_update_parent(काष्ठा hfs_find_data *fd);
अटल पूर्णांक hfs_btree_inc_height(काष्ठा hfs_btree *tree);

/* Get the length and offset of the given record in the given node */
u16 hfs_brec_lenoff(काष्ठा hfs_bnode *node, u16 rec, u16 *off)
अणु
	__be16 retval[2];
	u16 dataoff;

	dataoff = node->tree->node_size - (rec + 2) * 2;
	hfs_bnode_पढ़ो(node, retval, dataoff, 4);
	*off = be16_to_cpu(retval[1]);
	वापस be16_to_cpu(retval[0]) - *off;
पूर्ण

/* Get the length of the key from a keyed record */
u16 hfs_brec_keylen(काष्ठा hfs_bnode *node, u16 rec)
अणु
	u16 retval, recoff;

	अगर (node->type != HFS_NODE_INDEX && node->type != HFS_NODE_LEAF)
		वापस 0;

	अगर ((node->type == HFS_NODE_INDEX) &&
	   !(node->tree->attributes & HFS_TREE_VARIDXKEYS)) अणु
		अगर (node->tree->attributes & HFS_TREE_BIGKEYS)
			retval = node->tree->max_key_len + 2;
		अन्यथा
			retval = node->tree->max_key_len + 1;
	पूर्ण अन्यथा अणु
		recoff = hfs_bnode_पढ़ो_u16(node, node->tree->node_size - (rec + 1) * 2);
		अगर (!recoff)
			वापस 0;
		अगर (node->tree->attributes & HFS_TREE_BIGKEYS) अणु
			retval = hfs_bnode_पढ़ो_u16(node, recoff) + 2;
			अगर (retval > node->tree->max_key_len + 2) अणु
				pr_err("keylen %d too large\n", retval);
				retval = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			retval = (hfs_bnode_पढ़ो_u8(node, recoff) | 1) + 1;
			अगर (retval > node->tree->max_key_len + 1) अणु
				pr_err("keylen %d too large\n", retval);
				retval = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

पूर्णांक hfs_brec_insert(काष्ठा hfs_find_data *fd, व्योम *entry, पूर्णांक entry_len)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *node, *new_node;
	पूर्णांक size, key_len, rec;
	पूर्णांक data_off, end_off;
	पूर्णांक idx_rec_off, data_rec_off, end_rec_off;
	__be32 cnid;

	tree = fd->tree;
	अगर (!fd->bnode) अणु
		अगर (!tree->root)
			hfs_btree_inc_height(tree);
		node = hfs_bnode_find(tree, tree->leaf_head);
		अगर (IS_ERR(node))
			वापस PTR_ERR(node);
		fd->bnode = node;
		fd->record = -1;
	पूर्ण
	new_node = शून्य;
	key_len = (fd->search_key->key_len | 1) + 1;
again:
	/* new record idx and complete record size */
	rec = fd->record + 1;
	size = key_len + entry_len;

	node = fd->bnode;
	hfs_bnode_dump(node);
	/* get last offset */
	end_rec_off = tree->node_size - (node->num_recs + 1) * 2;
	end_off = hfs_bnode_पढ़ो_u16(node, end_rec_off);
	end_rec_off -= 2;
	hfs_dbg(BNODE_MOD, "insert_rec: %d, %d, %d, %d\n",
		rec, size, end_off, end_rec_off);
	अगर (size > end_rec_off - end_off) अणु
		अगर (new_node)
			panic("not enough room!\n");
		new_node = hfs_bnode_split(fd);
		अगर (IS_ERR(new_node))
			वापस PTR_ERR(new_node);
		जाओ again;
	पूर्ण
	अगर (node->type == HFS_NODE_LEAF) अणु
		tree->leaf_count++;
		mark_inode_dirty(tree->inode);
	पूर्ण
	node->num_recs++;
	/* ग_लिखो new last offset */
	hfs_bnode_ग_लिखो_u16(node, दुरत्व(काष्ठा hfs_bnode_desc, num_recs), node->num_recs);
	hfs_bnode_ग_लिखो_u16(node, end_rec_off, end_off + size);
	data_off = end_off;
	data_rec_off = end_rec_off + 2;
	idx_rec_off = tree->node_size - (rec + 1) * 2;
	अगर (idx_rec_off == data_rec_off)
		जाओ skip;
	/* move all following entries */
	करो अणु
		data_off = hfs_bnode_पढ़ो_u16(node, data_rec_off + 2);
		hfs_bnode_ग_लिखो_u16(node, data_rec_off, data_off + size);
		data_rec_off += 2;
	पूर्ण जबतक (data_rec_off < idx_rec_off);

	/* move data away */
	hfs_bnode_move(node, data_off + size, data_off,
		       end_off - data_off);

skip:
	hfs_bnode_ग_लिखो(node, fd->search_key, data_off, key_len);
	hfs_bnode_ग_लिखो(node, entry, data_off + key_len, entry_len);
	hfs_bnode_dump(node);

	/*
	 * update parent key अगर we inserted a key
	 * at the start of the node and it is not the new node
	 */
	अगर (!rec && new_node != node) अणु
		hfs_bnode_पढ़ो_key(node, fd->search_key, data_off + size);
		hfs_brec_update_parent(fd);
	पूर्ण

	अगर (new_node) अणु
		hfs_bnode_put(fd->bnode);
		अगर (!new_node->parent) अणु
			hfs_btree_inc_height(tree);
			new_node->parent = tree->root;
		पूर्ण
		fd->bnode = hfs_bnode_find(tree, new_node->parent);

		/* create index data entry */
		cnid = cpu_to_be32(new_node->this);
		entry = &cnid;
		entry_len = माप(cnid);

		/* get index key */
		hfs_bnode_पढ़ो_key(new_node, fd->search_key, 14);
		__hfs_brec_find(fd->bnode, fd);

		hfs_bnode_put(new_node);
		new_node = शून्य;

		अगर (tree->attributes & HFS_TREE_VARIDXKEYS)
			key_len = fd->search_key->key_len + 1;
		अन्यथा अणु
			fd->search_key->key_len = tree->max_key_len;
			key_len = tree->max_key_len + 1;
		पूर्ण
		जाओ again;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hfs_brec_हटाओ(काष्ठा hfs_find_data *fd)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *node, *parent;
	पूर्णांक end_off, rec_off, data_off, size;

	tree = fd->tree;
	node = fd->bnode;
again:
	rec_off = tree->node_size - (fd->record + 2) * 2;
	end_off = tree->node_size - (node->num_recs + 1) * 2;

	अगर (node->type == HFS_NODE_LEAF) अणु
		tree->leaf_count--;
		mark_inode_dirty(tree->inode);
	पूर्ण
	hfs_bnode_dump(node);
	hfs_dbg(BNODE_MOD, "remove_rec: %d, %d\n",
		fd->record, fd->keylength + fd->entrylength);
	अगर (!--node->num_recs) अणु
		hfs_bnode_unlink(node);
		अगर (!node->parent)
			वापस 0;
		parent = hfs_bnode_find(tree, node->parent);
		अगर (IS_ERR(parent))
			वापस PTR_ERR(parent);
		hfs_bnode_put(node);
		node = fd->bnode = parent;

		__hfs_brec_find(node, fd);
		जाओ again;
	पूर्ण
	hfs_bnode_ग_लिखो_u16(node, दुरत्व(काष्ठा hfs_bnode_desc, num_recs), node->num_recs);

	अगर (rec_off == end_off)
		जाओ skip;
	size = fd->keylength + fd->entrylength;

	करो अणु
		data_off = hfs_bnode_पढ़ो_u16(node, rec_off);
		hfs_bnode_ग_लिखो_u16(node, rec_off + 2, data_off - size);
		rec_off -= 2;
	पूर्ण जबतक (rec_off >= end_off);

	/* fill hole */
	hfs_bnode_move(node, fd->keyoffset, fd->keyoffset + size,
		       data_off - fd->keyoffset - size);
skip:
	hfs_bnode_dump(node);
	अगर (!fd->record)
		hfs_brec_update_parent(fd);
	वापस 0;
पूर्ण

अटल काष्ठा hfs_bnode *hfs_bnode_split(काष्ठा hfs_find_data *fd)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *node, *new_node, *next_node;
	काष्ठा hfs_bnode_desc node_desc;
	पूर्णांक num_recs, new_rec_off, new_off, old_rec_off;
	पूर्णांक data_start, data_end, size;

	tree = fd->tree;
	node = fd->bnode;
	new_node = hfs_bmap_alloc(tree);
	अगर (IS_ERR(new_node))
		वापस new_node;
	hfs_bnode_get(node);
	hfs_dbg(BNODE_MOD, "split_nodes: %d - %d - %d\n",
		node->this, new_node->this, node->next);
	new_node->next = node->next;
	new_node->prev = node->this;
	new_node->parent = node->parent;
	new_node->type = node->type;
	new_node->height = node->height;

	अगर (node->next)
		next_node = hfs_bnode_find(tree, node->next);
	अन्यथा
		next_node = शून्य;

	अगर (IS_ERR(next_node)) अणु
		hfs_bnode_put(node);
		hfs_bnode_put(new_node);
		वापस next_node;
	पूर्ण

	size = tree->node_size / 2 - node->num_recs * 2 - 14;
	old_rec_off = tree->node_size - 4;
	num_recs = 1;
	क्रम (;;) अणु
		data_start = hfs_bnode_पढ़ो_u16(node, old_rec_off);
		अगर (data_start > size)
			अवरोध;
		old_rec_off -= 2;
		अगर (++num_recs < node->num_recs)
			जारी;
		/* panic? */
		hfs_bnode_put(node);
		hfs_bnode_put(new_node);
		अगर (next_node)
			hfs_bnode_put(next_node);
		वापस ERR_PTR(-ENOSPC);
	पूर्ण

	अगर (fd->record + 1 < num_recs) अणु
		/* new record is in the lower half,
		 * so leave some more space there
		 */
		old_rec_off += 2;
		num_recs--;
		data_start = hfs_bnode_पढ़ो_u16(node, old_rec_off);
	पूर्ण अन्यथा अणु
		hfs_bnode_put(node);
		hfs_bnode_get(new_node);
		fd->bnode = new_node;
		fd->record -= num_recs;
		fd->keyoffset -= data_start - 14;
		fd->entryoffset -= data_start - 14;
	पूर्ण
	new_node->num_recs = node->num_recs - num_recs;
	node->num_recs = num_recs;

	new_rec_off = tree->node_size - 2;
	new_off = 14;
	size = data_start - new_off;
	num_recs = new_node->num_recs;
	data_end = data_start;
	जबतक (num_recs) अणु
		hfs_bnode_ग_लिखो_u16(new_node, new_rec_off, new_off);
		old_rec_off -= 2;
		new_rec_off -= 2;
		data_end = hfs_bnode_पढ़ो_u16(node, old_rec_off);
		new_off = data_end - size;
		num_recs--;
	पूर्ण
	hfs_bnode_ग_लिखो_u16(new_node, new_rec_off, new_off);
	hfs_bnode_copy(new_node, 14, node, data_start, data_end - data_start);

	/* update new bnode header */
	node_desc.next = cpu_to_be32(new_node->next);
	node_desc.prev = cpu_to_be32(new_node->prev);
	node_desc.type = new_node->type;
	node_desc.height = new_node->height;
	node_desc.num_recs = cpu_to_be16(new_node->num_recs);
	node_desc.reserved = 0;
	hfs_bnode_ग_लिखो(new_node, &node_desc, 0, माप(node_desc));

	/* update previous bnode header */
	node->next = new_node->this;
	hfs_bnode_पढ़ो(node, &node_desc, 0, माप(node_desc));
	node_desc.next = cpu_to_be32(node->next);
	node_desc.num_recs = cpu_to_be16(node->num_recs);
	hfs_bnode_ग_लिखो(node, &node_desc, 0, माप(node_desc));

	/* update next bnode header */
	अगर (next_node) अणु
		next_node->prev = new_node->this;
		hfs_bnode_पढ़ो(next_node, &node_desc, 0, माप(node_desc));
		node_desc.prev = cpu_to_be32(next_node->prev);
		hfs_bnode_ग_लिखो(next_node, &node_desc, 0, माप(node_desc));
		hfs_bnode_put(next_node);
	पूर्ण अन्यथा अगर (node->this == tree->leaf_tail) अणु
		/* अगर there is no next node, this might be the new tail */
		tree->leaf_tail = new_node->this;
		mark_inode_dirty(tree->inode);
	पूर्ण

	hfs_bnode_dump(node);
	hfs_bnode_dump(new_node);
	hfs_bnode_put(node);

	वापस new_node;
पूर्ण

अटल पूर्णांक hfs_brec_update_parent(काष्ठा hfs_find_data *fd)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *node, *new_node, *parent;
	पूर्णांक newkeylen, dअगरf;
	पूर्णांक rec, rec_off, end_rec_off;
	पूर्णांक start_off, end_off;

	tree = fd->tree;
	node = fd->bnode;
	new_node = शून्य;
	अगर (!node->parent)
		वापस 0;

again:
	parent = hfs_bnode_find(tree, node->parent);
	अगर (IS_ERR(parent))
		वापस PTR_ERR(parent);
	__hfs_brec_find(parent, fd);
	अगर (fd->record < 0)
		वापस -ENOENT;
	hfs_bnode_dump(parent);
	rec = fd->record;

	/* size dअगरference between old and new key */
	अगर (tree->attributes & HFS_TREE_VARIDXKEYS)
		newkeylen = (hfs_bnode_पढ़ो_u8(node, 14) | 1) + 1;
	अन्यथा
		fd->keylength = newkeylen = tree->max_key_len + 1;
	hfs_dbg(BNODE_MOD, "update_rec: %d, %d, %d\n",
		rec, fd->keylength, newkeylen);

	rec_off = tree->node_size - (rec + 2) * 2;
	end_rec_off = tree->node_size - (parent->num_recs + 1) * 2;
	dअगरf = newkeylen - fd->keylength;
	अगर (!dअगरf)
		जाओ skip;
	अगर (dअगरf > 0) अणु
		end_off = hfs_bnode_पढ़ो_u16(parent, end_rec_off);
		अगर (end_rec_off - end_off < dअगरf) अणु

			prपूर्णांकk(KERN_DEBUG "splitting index node...\n");
			fd->bnode = parent;
			new_node = hfs_bnode_split(fd);
			अगर (IS_ERR(new_node))
				वापस PTR_ERR(new_node);
			parent = fd->bnode;
			rec = fd->record;
			rec_off = tree->node_size - (rec + 2) * 2;
			end_rec_off = tree->node_size - (parent->num_recs + 1) * 2;
		पूर्ण
	पूर्ण

	end_off = start_off = hfs_bnode_पढ़ो_u16(parent, rec_off);
	hfs_bnode_ग_लिखो_u16(parent, rec_off, start_off + dअगरf);
	start_off -= 4;	/* move previous cnid too */

	जबतक (rec_off > end_rec_off) अणु
		rec_off -= 2;
		end_off = hfs_bnode_पढ़ो_u16(parent, rec_off);
		hfs_bnode_ग_लिखो_u16(parent, rec_off, end_off + dअगरf);
	पूर्ण
	hfs_bnode_move(parent, start_off + dअगरf, start_off,
		       end_off - start_off);
skip:
	hfs_bnode_copy(parent, fd->keyoffset, node, 14, newkeylen);
	अगर (!(tree->attributes & HFS_TREE_VARIDXKEYS))
		hfs_bnode_ग_लिखो_u8(parent, fd->keyoffset, newkeylen - 1);
	hfs_bnode_dump(parent);

	hfs_bnode_put(node);
	node = parent;

	अगर (new_node) अणु
		__be32 cnid;

		अगर (!new_node->parent) अणु
			hfs_btree_inc_height(tree);
			new_node->parent = tree->root;
		पूर्ण
		fd->bnode = hfs_bnode_find(tree, new_node->parent);
		/* create index key and entry */
		hfs_bnode_पढ़ो_key(new_node, fd->search_key, 14);
		cnid = cpu_to_be32(new_node->this);

		__hfs_brec_find(fd->bnode, fd);
		hfs_brec_insert(fd, &cnid, माप(cnid));
		hfs_bnode_put(fd->bnode);
		hfs_bnode_put(new_node);

		अगर (!rec) अणु
			अगर (new_node == node)
				जाओ out;
			/* restore search_key */
			hfs_bnode_पढ़ो_key(node, fd->search_key, 14);
		पूर्ण
		new_node = शून्य;
	पूर्ण

	अगर (!rec && node->parent)
		जाओ again;
out:
	fd->bnode = node;
	वापस 0;
पूर्ण

अटल पूर्णांक hfs_btree_inc_height(काष्ठा hfs_btree *tree)
अणु
	काष्ठा hfs_bnode *node, *new_node;
	काष्ठा hfs_bnode_desc node_desc;
	पूर्णांक key_size, rec;
	__be32 cnid;

	node = शून्य;
	अगर (tree->root) अणु
		node = hfs_bnode_find(tree, tree->root);
		अगर (IS_ERR(node))
			वापस PTR_ERR(node);
	पूर्ण
	new_node = hfs_bmap_alloc(tree);
	अगर (IS_ERR(new_node)) अणु
		hfs_bnode_put(node);
		वापस PTR_ERR(new_node);
	पूर्ण

	tree->root = new_node->this;
	अगर (!tree->depth) अणु
		tree->leaf_head = tree->leaf_tail = new_node->this;
		new_node->type = HFS_NODE_LEAF;
		new_node->num_recs = 0;
	पूर्ण अन्यथा अणु
		new_node->type = HFS_NODE_INDEX;
		new_node->num_recs = 1;
	पूर्ण
	new_node->parent = 0;
	new_node->next = 0;
	new_node->prev = 0;
	new_node->height = ++tree->depth;

	node_desc.next = cpu_to_be32(new_node->next);
	node_desc.prev = cpu_to_be32(new_node->prev);
	node_desc.type = new_node->type;
	node_desc.height = new_node->height;
	node_desc.num_recs = cpu_to_be16(new_node->num_recs);
	node_desc.reserved = 0;
	hfs_bnode_ग_लिखो(new_node, &node_desc, 0, माप(node_desc));

	rec = tree->node_size - 2;
	hfs_bnode_ग_लिखो_u16(new_node, rec, 14);

	अगर (node) अणु
		/* insert old root idx पूर्णांकo new root */
		node->parent = tree->root;
		अगर (node->type == HFS_NODE_LEAF ||
		    tree->attributes & HFS_TREE_VARIDXKEYS)
			key_size = hfs_bnode_पढ़ो_u8(node, 14) + 1;
		अन्यथा
			key_size = tree->max_key_len + 1;
		hfs_bnode_copy(new_node, 14, node, 14, key_size);

		अगर (!(tree->attributes & HFS_TREE_VARIDXKEYS)) अणु
			key_size = tree->max_key_len + 1;
			hfs_bnode_ग_लिखो_u8(new_node, 14, tree->max_key_len);
		पूर्ण
		key_size = (key_size + 1) & -2;
		cnid = cpu_to_be32(node->this);
		hfs_bnode_ग_लिखो(new_node, &cnid, 14 + key_size, 4);

		rec -= 2;
		hfs_bnode_ग_लिखो_u16(new_node, rec, 14 + key_size + 4);

		hfs_bnode_put(node);
	पूर्ण
	hfs_bnode_put(new_node);
	mark_inode_dirty(tree->inode);

	वापस 0;
पूर्ण

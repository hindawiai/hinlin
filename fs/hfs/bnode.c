<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfs/bnode.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handle basic btree node operations
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>

#समावेश "btree.h"

व्योम hfs_bnode_पढ़ो(काष्ठा hfs_bnode *node, व्योम *buf,
		पूर्णांक off, पूर्णांक len)
अणु
	काष्ठा page *page;

	off += node->page_offset;
	page = node->page[0];

	स_नकल(buf, kmap(page) + off, len);
	kunmap(page);
पूर्ण

u16 hfs_bnode_पढ़ो_u16(काष्ठा hfs_bnode *node, पूर्णांक off)
अणु
	__be16 data;
	// optimize later...
	hfs_bnode_पढ़ो(node, &data, off, 2);
	वापस be16_to_cpu(data);
पूर्ण

u8 hfs_bnode_पढ़ो_u8(काष्ठा hfs_bnode *node, पूर्णांक off)
अणु
	u8 data;
	// optimize later...
	hfs_bnode_पढ़ो(node, &data, off, 1);
	वापस data;
पूर्ण

व्योम hfs_bnode_पढ़ो_key(काष्ठा hfs_bnode *node, व्योम *key, पूर्णांक off)
अणु
	काष्ठा hfs_btree *tree;
	पूर्णांक key_len;

	tree = node->tree;
	अगर (node->type == HFS_NODE_LEAF ||
	    tree->attributes & HFS_TREE_VARIDXKEYS)
		key_len = hfs_bnode_पढ़ो_u8(node, off) + 1;
	अन्यथा
		key_len = tree->max_key_len + 1;

	hfs_bnode_पढ़ो(node, key, off, key_len);
पूर्ण

व्योम hfs_bnode_ग_लिखो(काष्ठा hfs_bnode *node, व्योम *buf, पूर्णांक off, पूर्णांक len)
अणु
	काष्ठा page *page;

	off += node->page_offset;
	page = node->page[0];

	स_नकल(kmap(page) + off, buf, len);
	kunmap(page);
	set_page_dirty(page);
पूर्ण

व्योम hfs_bnode_ग_लिखो_u16(काष्ठा hfs_bnode *node, पूर्णांक off, u16 data)
अणु
	__be16 v = cpu_to_be16(data);
	// optimize later...
	hfs_bnode_ग_लिखो(node, &v, off, 2);
पूर्ण

व्योम hfs_bnode_ग_लिखो_u8(काष्ठा hfs_bnode *node, पूर्णांक off, u8 data)
अणु
	// optimize later...
	hfs_bnode_ग_लिखो(node, &data, off, 1);
पूर्ण

व्योम hfs_bnode_clear(काष्ठा hfs_bnode *node, पूर्णांक off, पूर्णांक len)
अणु
	काष्ठा page *page;

	off += node->page_offset;
	page = node->page[0];

	स_रखो(kmap(page) + off, 0, len);
	kunmap(page);
	set_page_dirty(page);
पूर्ण

व्योम hfs_bnode_copy(काष्ठा hfs_bnode *dst_node, पूर्णांक dst,
		काष्ठा hfs_bnode *src_node, पूर्णांक src, पूर्णांक len)
अणु
	काष्ठा page *src_page, *dst_page;

	hfs_dbg(BNODE_MOD, "copybytes: %u,%u,%u\n", dst, src, len);
	अगर (!len)
		वापस;
	src += src_node->page_offset;
	dst += dst_node->page_offset;
	src_page = src_node->page[0];
	dst_page = dst_node->page[0];

	स_नकल(kmap(dst_page) + dst, kmap(src_page) + src, len);
	kunmap(src_page);
	kunmap(dst_page);
	set_page_dirty(dst_page);
पूर्ण

व्योम hfs_bnode_move(काष्ठा hfs_bnode *node, पूर्णांक dst, पूर्णांक src, पूर्णांक len)
अणु
	काष्ठा page *page;
	व्योम *ptr;

	hfs_dbg(BNODE_MOD, "movebytes: %u,%u,%u\n", dst, src, len);
	अगर (!len)
		वापस;
	src += node->page_offset;
	dst += node->page_offset;
	page = node->page[0];
	ptr = kmap(page);
	स_हटाओ(ptr + dst, ptr + src, len);
	kunmap(page);
	set_page_dirty(page);
पूर्ण

व्योम hfs_bnode_dump(काष्ठा hfs_bnode *node)
अणु
	काष्ठा hfs_bnode_desc desc;
	__be32 cnid;
	पूर्णांक i, off, key_off;

	hfs_dbg(BNODE_MOD, "bnode: %d\n", node->this);
	hfs_bnode_पढ़ो(node, &desc, 0, माप(desc));
	hfs_dbg(BNODE_MOD, "%d, %d, %d, %d, %d\n",
		be32_to_cpu(desc.next), be32_to_cpu(desc.prev),
		desc.type, desc.height, be16_to_cpu(desc.num_recs));

	off = node->tree->node_size - 2;
	क्रम (i = be16_to_cpu(desc.num_recs); i >= 0; off -= 2, i--) अणु
		key_off = hfs_bnode_पढ़ो_u16(node, off);
		hfs_dbg_cont(BNODE_MOD, " %d", key_off);
		अगर (i && node->type == HFS_NODE_INDEX) अणु
			पूर्णांक पंचांगp;

			अगर (node->tree->attributes & HFS_TREE_VARIDXKEYS)
				पंचांगp = (hfs_bnode_पढ़ो_u8(node, key_off) | 1) + 1;
			अन्यथा
				पंचांगp = node->tree->max_key_len + 1;
			hfs_dbg_cont(BNODE_MOD, " (%d,%d",
				     पंचांगp, hfs_bnode_पढ़ो_u8(node, key_off));
			hfs_bnode_पढ़ो(node, &cnid, key_off + पंचांगp, 4);
			hfs_dbg_cont(BNODE_MOD, ",%d)", be32_to_cpu(cnid));
		पूर्ण अन्यथा अगर (i && node->type == HFS_NODE_LEAF) अणु
			पूर्णांक पंचांगp;

			पंचांगp = hfs_bnode_पढ़ो_u8(node, key_off);
			hfs_dbg_cont(BNODE_MOD, " (%d)", पंचांगp);
		पूर्ण
	पूर्ण
	hfs_dbg_cont(BNODE_MOD, "\n");
पूर्ण

व्योम hfs_bnode_unlink(काष्ठा hfs_bnode *node)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *पंचांगp;
	__be32 cnid;

	tree = node->tree;
	अगर (node->prev) अणु
		पंचांगp = hfs_bnode_find(tree, node->prev);
		अगर (IS_ERR(पंचांगp))
			वापस;
		पंचांगp->next = node->next;
		cnid = cpu_to_be32(पंचांगp->next);
		hfs_bnode_ग_लिखो(पंचांगp, &cnid, दुरत्व(काष्ठा hfs_bnode_desc, next), 4);
		hfs_bnode_put(पंचांगp);
	पूर्ण अन्यथा अगर (node->type == HFS_NODE_LEAF)
		tree->leaf_head = node->next;

	अगर (node->next) अणु
		पंचांगp = hfs_bnode_find(tree, node->next);
		अगर (IS_ERR(पंचांगp))
			वापस;
		पंचांगp->prev = node->prev;
		cnid = cpu_to_be32(पंचांगp->prev);
		hfs_bnode_ग_लिखो(पंचांगp, &cnid, दुरत्व(काष्ठा hfs_bnode_desc, prev), 4);
		hfs_bnode_put(पंचांगp);
	पूर्ण अन्यथा अगर (node->type == HFS_NODE_LEAF)
		tree->leaf_tail = node->prev;

	// move करोwn?
	अगर (!node->prev && !node->next) अणु
		prपूर्णांकk(KERN_DEBUG "hfs_btree_del_level\n");
	पूर्ण
	अगर (!node->parent) अणु
		tree->root = 0;
		tree->depth = 0;
	पूर्ण
	set_bit(HFS_BNODE_DELETED, &node->flags);
पूर्ण

अटल अंतरभूत पूर्णांक hfs_bnode_hash(u32 num)
अणु
	num = (num >> 16) + num;
	num += num >> 8;
	वापस num & (NODE_HASH_SIZE - 1);
पूर्ण

काष्ठा hfs_bnode *hfs_bnode_findhash(काष्ठा hfs_btree *tree, u32 cnid)
अणु
	काष्ठा hfs_bnode *node;

	अगर (cnid >= tree->node_count) अणु
		pr_err("request for non-existent node %d in B*Tree\n", cnid);
		वापस शून्य;
	पूर्ण

	क्रम (node = tree->node_hash[hfs_bnode_hash(cnid)];
	     node; node = node->next_hash) अणु
		अगर (node->this == cnid) अणु
			वापस node;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा hfs_bnode *__hfs_bnode_create(काष्ठा hfs_btree *tree, u32 cnid)
अणु
	काष्ठा hfs_bnode *node, *node2;
	काष्ठा address_space *mapping;
	काष्ठा page *page;
	पूर्णांक size, block, i, hash;
	loff_t off;

	अगर (cnid >= tree->node_count) अणु
		pr_err("request for non-existent node %d in B*Tree\n", cnid);
		वापस शून्य;
	पूर्ण

	size = माप(काष्ठा hfs_bnode) + tree->pages_per_bnode *
		माप(काष्ठा page *);
	node = kzalloc(size, GFP_KERNEL);
	अगर (!node)
		वापस शून्य;
	node->tree = tree;
	node->this = cnid;
	set_bit(HFS_BNODE_NEW, &node->flags);
	atomic_set(&node->refcnt, 1);
	hfs_dbg(BNODE_REFS, "new_node(%d:%d): 1\n",
		node->tree->cnid, node->this);
	init_रुकोqueue_head(&node->lock_wq);
	spin_lock(&tree->hash_lock);
	node2 = hfs_bnode_findhash(tree, cnid);
	अगर (!node2) अणु
		hash = hfs_bnode_hash(cnid);
		node->next_hash = tree->node_hash[hash];
		tree->node_hash[hash] = node;
		tree->node_hash_cnt++;
	पूर्ण अन्यथा अणु
		spin_unlock(&tree->hash_lock);
		kमुक्त(node);
		रुको_event(node2->lock_wq, !test_bit(HFS_BNODE_NEW, &node2->flags));
		वापस node2;
	पूर्ण
	spin_unlock(&tree->hash_lock);

	mapping = tree->inode->i_mapping;
	off = (loff_t)cnid * tree->node_size;
	block = off >> PAGE_SHIFT;
	node->page_offset = off & ~PAGE_MASK;
	क्रम (i = 0; i < tree->pages_per_bnode; i++) अणु
		page = पढ़ो_mapping_page(mapping, block++, शून्य);
		अगर (IS_ERR(page))
			जाओ fail;
		अगर (PageError(page)) अणु
			put_page(page);
			जाओ fail;
		पूर्ण
		node->page[i] = page;
	पूर्ण

	वापस node;
fail:
	set_bit(HFS_BNODE_ERROR, &node->flags);
	वापस node;
पूर्ण

व्योम hfs_bnode_unhash(काष्ठा hfs_bnode *node)
अणु
	काष्ठा hfs_bnode **p;

	hfs_dbg(BNODE_REFS, "remove_node(%d:%d): %d\n",
		node->tree->cnid, node->this, atomic_पढ़ो(&node->refcnt));
	क्रम (p = &node->tree->node_hash[hfs_bnode_hash(node->this)];
	     *p && *p != node; p = &(*p)->next_hash)
		;
	BUG_ON(!*p);
	*p = node->next_hash;
	node->tree->node_hash_cnt--;
पूर्ण

/* Load a particular node out of a tree */
काष्ठा hfs_bnode *hfs_bnode_find(काष्ठा hfs_btree *tree, u32 num)
अणु
	काष्ठा hfs_bnode *node;
	काष्ठा hfs_bnode_desc *desc;
	पूर्णांक i, rec_off, off, next_off;
	पूर्णांक entry_size, key_size;

	spin_lock(&tree->hash_lock);
	node = hfs_bnode_findhash(tree, num);
	अगर (node) अणु
		hfs_bnode_get(node);
		spin_unlock(&tree->hash_lock);
		रुको_event(node->lock_wq, !test_bit(HFS_BNODE_NEW, &node->flags));
		अगर (test_bit(HFS_BNODE_ERROR, &node->flags))
			जाओ node_error;
		वापस node;
	पूर्ण
	spin_unlock(&tree->hash_lock);
	node = __hfs_bnode_create(tree, num);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);
	अगर (test_bit(HFS_BNODE_ERROR, &node->flags))
		जाओ node_error;
	अगर (!test_bit(HFS_BNODE_NEW, &node->flags))
		वापस node;

	desc = (काष्ठा hfs_bnode_desc *)(kmap(node->page[0]) + node->page_offset);
	node->prev = be32_to_cpu(desc->prev);
	node->next = be32_to_cpu(desc->next);
	node->num_recs = be16_to_cpu(desc->num_recs);
	node->type = desc->type;
	node->height = desc->height;
	kunmap(node->page[0]);

	चयन (node->type) अणु
	हाल HFS_NODE_HEADER:
	हाल HFS_NODE_MAP:
		अगर (node->height != 0)
			जाओ node_error;
		अवरोध;
	हाल HFS_NODE_LEAF:
		अगर (node->height != 1)
			जाओ node_error;
		अवरोध;
	हाल HFS_NODE_INDEX:
		अगर (node->height <= 1 || node->height > tree->depth)
			जाओ node_error;
		अवरोध;
	शेष:
		जाओ node_error;
	पूर्ण

	rec_off = tree->node_size - 2;
	off = hfs_bnode_पढ़ो_u16(node, rec_off);
	अगर (off != माप(काष्ठा hfs_bnode_desc))
		जाओ node_error;
	क्रम (i = 1; i <= node->num_recs; off = next_off, i++) अणु
		rec_off -= 2;
		next_off = hfs_bnode_पढ़ो_u16(node, rec_off);
		अगर (next_off <= off ||
		    next_off > tree->node_size ||
		    next_off & 1)
			जाओ node_error;
		entry_size = next_off - off;
		अगर (node->type != HFS_NODE_INDEX &&
		    node->type != HFS_NODE_LEAF)
			जारी;
		key_size = hfs_bnode_पढ़ो_u8(node, off) + 1;
		अगर (key_size >= entry_size /*|| key_size & 1*/)
			जाओ node_error;
	पूर्ण
	clear_bit(HFS_BNODE_NEW, &node->flags);
	wake_up(&node->lock_wq);
	वापस node;

node_error:
	set_bit(HFS_BNODE_ERROR, &node->flags);
	clear_bit(HFS_BNODE_NEW, &node->flags);
	wake_up(&node->lock_wq);
	hfs_bnode_put(node);
	वापस ERR_PTR(-EIO);
पूर्ण

व्योम hfs_bnode_मुक्त(काष्ठा hfs_bnode *node)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < node->tree->pages_per_bnode; i++)
		अगर (node->page[i])
			put_page(node->page[i]);
	kमुक्त(node);
पूर्ण

काष्ठा hfs_bnode *hfs_bnode_create(काष्ठा hfs_btree *tree, u32 num)
अणु
	काष्ठा hfs_bnode *node;
	काष्ठा page **pagep;
	पूर्णांक i;

	spin_lock(&tree->hash_lock);
	node = hfs_bnode_findhash(tree, num);
	spin_unlock(&tree->hash_lock);
	अगर (node) अणु
		pr_crit("new node %u already hashed?\n", num);
		WARN_ON(1);
		वापस node;
	पूर्ण
	node = __hfs_bnode_create(tree, num);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);
	अगर (test_bit(HFS_BNODE_ERROR, &node->flags)) अणु
		hfs_bnode_put(node);
		वापस ERR_PTR(-EIO);
	पूर्ण

	pagep = node->page;
	स_रखो(kmap(*pagep) + node->page_offset, 0,
	       min((पूर्णांक)PAGE_SIZE, (पूर्णांक)tree->node_size));
	set_page_dirty(*pagep);
	kunmap(*pagep);
	क्रम (i = 1; i < tree->pages_per_bnode; i++) अणु
		स_रखो(kmap(*++pagep), 0, PAGE_SIZE);
		set_page_dirty(*pagep);
		kunmap(*pagep);
	पूर्ण
	clear_bit(HFS_BNODE_NEW, &node->flags);
	wake_up(&node->lock_wq);

	वापस node;
पूर्ण

व्योम hfs_bnode_get(काष्ठा hfs_bnode *node)
अणु
	अगर (node) अणु
		atomic_inc(&node->refcnt);
		hfs_dbg(BNODE_REFS, "get_node(%d:%d): %d\n",
			node->tree->cnid, node->this,
			atomic_पढ़ो(&node->refcnt));
	पूर्ण
पूर्ण

/* Dispose of resources used by a node */
व्योम hfs_bnode_put(काष्ठा hfs_bnode *node)
अणु
	अगर (node) अणु
		काष्ठा hfs_btree *tree = node->tree;
		पूर्णांक i;

		hfs_dbg(BNODE_REFS, "put_node(%d:%d): %d\n",
			node->tree->cnid, node->this,
			atomic_पढ़ो(&node->refcnt));
		BUG_ON(!atomic_पढ़ो(&node->refcnt));
		अगर (!atomic_dec_and_lock(&node->refcnt, &tree->hash_lock))
			वापस;
		क्रम (i = 0; i < tree->pages_per_bnode; i++) अणु
			अगर (!node->page[i])
				जारी;
			mark_page_accessed(node->page[i]);
		पूर्ण

		अगर (test_bit(HFS_BNODE_DELETED, &node->flags)) अणु
			hfs_bnode_unhash(node);
			spin_unlock(&tree->hash_lock);
			hfs_bmap_मुक्त(node);
			hfs_bnode_मुक्त(node);
			वापस;
		पूर्ण
		spin_unlock(&tree->hash_lock);
	पूर्ण
पूर्ण

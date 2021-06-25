<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfs/btree.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handle खोलोing/closing btree
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>

#समावेश "btree.h"

/* Get a reference to a B*Tree and करो some initial checks */
काष्ठा hfs_btree *hfs_btree_खोलो(काष्ठा super_block *sb, u32 id, btree_keycmp keycmp)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_btree_header_rec *head;
	काष्ठा address_space *mapping;
	काष्ठा page *page;
	अचिन्हित पूर्णांक size;

	tree = kzalloc(माप(*tree), GFP_KERNEL);
	अगर (!tree)
		वापस शून्य;

	mutex_init(&tree->tree_lock);
	spin_lock_init(&tree->hash_lock);
	/* Set the correct compare function */
	tree->sb = sb;
	tree->cnid = id;
	tree->keycmp = keycmp;

	tree->inode = iget_locked(sb, id);
	अगर (!tree->inode)
		जाओ मुक्त_tree;
	BUG_ON(!(tree->inode->i_state & I_NEW));
	अणु
	काष्ठा hfs_mdb *mdb = HFS_SB(sb)->mdb;
	HFS_I(tree->inode)->flags = 0;
	mutex_init(&HFS_I(tree->inode)->extents_lock);
	चयन (id) अणु
	हाल HFS_EXT_CNID:
		hfs_inode_पढ़ो_विभाजन(tree->inode, mdb->drXTExtRec, mdb->drXTFlSize,
				    mdb->drXTFlSize, be32_to_cpu(mdb->drXTClpSiz));
		अगर (HFS_I(tree->inode)->alloc_blocks >
					HFS_I(tree->inode)->first_blocks) अणु
			pr_err("invalid btree extent records\n");
			unlock_new_inode(tree->inode);
			जाओ मुक्त_inode;
		पूर्ण

		tree->inode->i_mapping->a_ops = &hfs_btree_aops;
		अवरोध;
	हाल HFS_CAT_CNID:
		hfs_inode_पढ़ो_विभाजन(tree->inode, mdb->drCTExtRec, mdb->drCTFlSize,
				    mdb->drCTFlSize, be32_to_cpu(mdb->drCTClpSiz));

		अगर (!HFS_I(tree->inode)->first_blocks) अणु
			pr_err("invalid btree extent records (0 size)\n");
			unlock_new_inode(tree->inode);
			जाओ मुक्त_inode;
		पूर्ण

		tree->inode->i_mapping->a_ops = &hfs_btree_aops;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	पूर्ण
	unlock_new_inode(tree->inode);

	mapping = tree->inode->i_mapping;
	page = पढ़ो_mapping_page(mapping, 0, शून्य);
	अगर (IS_ERR(page))
		जाओ मुक्त_inode;

	/* Load the header */
	head = (काष्ठा hfs_btree_header_rec *)(kmap(page) + माप(काष्ठा hfs_bnode_desc));
	tree->root = be32_to_cpu(head->root);
	tree->leaf_count = be32_to_cpu(head->leaf_count);
	tree->leaf_head = be32_to_cpu(head->leaf_head);
	tree->leaf_tail = be32_to_cpu(head->leaf_tail);
	tree->node_count = be32_to_cpu(head->node_count);
	tree->मुक्त_nodes = be32_to_cpu(head->मुक्त_nodes);
	tree->attributes = be32_to_cpu(head->attributes);
	tree->node_size = be16_to_cpu(head->node_size);
	tree->max_key_len = be16_to_cpu(head->max_key_len);
	tree->depth = be16_to_cpu(head->depth);

	size = tree->node_size;
	अगर (!is_घातer_of_2(size))
		जाओ fail_page;
	अगर (!tree->node_count)
		जाओ fail_page;
	चयन (id) अणु
	हाल HFS_EXT_CNID:
		अगर (tree->max_key_len != HFS_MAX_EXT_KEYLEN) अणु
			pr_err("invalid extent max_key_len %d\n",
			       tree->max_key_len);
			जाओ fail_page;
		पूर्ण
		अवरोध;
	हाल HFS_CAT_CNID:
		अगर (tree->max_key_len != HFS_MAX_CAT_KEYLEN) अणु
			pr_err("invalid catalog max_key_len %d\n",
			       tree->max_key_len);
			जाओ fail_page;
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	tree->node_size_shअगरt = ffs(size) - 1;
	tree->pages_per_bnode = (tree->node_size + PAGE_SIZE - 1) >> PAGE_SHIFT;

	kunmap(page);
	put_page(page);
	वापस tree;

fail_page:
	put_page(page);
मुक्त_inode:
	tree->inode->i_mapping->a_ops = &hfs_aops;
	iput(tree->inode);
मुक्त_tree:
	kमुक्त(tree);
	वापस शून्य;
पूर्ण

/* Release resources used by a btree */
व्योम hfs_btree_बंद(काष्ठा hfs_btree *tree)
अणु
	काष्ठा hfs_bnode *node;
	पूर्णांक i;

	अगर (!tree)
		वापस;

	क्रम (i = 0; i < NODE_HASH_SIZE; i++) अणु
		जबतक ((node = tree->node_hash[i])) अणु
			tree->node_hash[i] = node->next_hash;
			अगर (atomic_पढ़ो(&node->refcnt))
				pr_err("node %d:%d still has %d user(s)!\n",
				       node->tree->cnid, node->this,
				       atomic_पढ़ो(&node->refcnt));
			hfs_bnode_मुक्त(node);
			tree->node_hash_cnt--;
		पूर्ण
	पूर्ण
	iput(tree->inode);
	kमुक्त(tree);
पूर्ण

व्योम hfs_btree_ग_लिखो(काष्ठा hfs_btree *tree)
अणु
	काष्ठा hfs_btree_header_rec *head;
	काष्ठा hfs_bnode *node;
	काष्ठा page *page;

	node = hfs_bnode_find(tree, 0);
	अगर (IS_ERR(node))
		/* panic? */
		वापस;
	/* Load the header */
	page = node->page[0];
	head = (काष्ठा hfs_btree_header_rec *)(kmap(page) + माप(काष्ठा hfs_bnode_desc));

	head->root = cpu_to_be32(tree->root);
	head->leaf_count = cpu_to_be32(tree->leaf_count);
	head->leaf_head = cpu_to_be32(tree->leaf_head);
	head->leaf_tail = cpu_to_be32(tree->leaf_tail);
	head->node_count = cpu_to_be32(tree->node_count);
	head->मुक्त_nodes = cpu_to_be32(tree->मुक्त_nodes);
	head->attributes = cpu_to_be32(tree->attributes);
	head->depth = cpu_to_be16(tree->depth);

	kunmap(page);
	set_page_dirty(page);
	hfs_bnode_put(node);
पूर्ण

अटल काष्ठा hfs_bnode *hfs_bmap_new_bmap(काष्ठा hfs_bnode *prev, u32 idx)
अणु
	काष्ठा hfs_btree *tree = prev->tree;
	काष्ठा hfs_bnode *node;
	काष्ठा hfs_bnode_desc desc;
	__be32 cnid;

	node = hfs_bnode_create(tree, idx);
	अगर (IS_ERR(node))
		वापस node;

	अगर (!tree->मुक्त_nodes)
		panic("FIXME!!!");
	tree->मुक्त_nodes--;
	prev->next = idx;
	cnid = cpu_to_be32(idx);
	hfs_bnode_ग_लिखो(prev, &cnid, दुरत्व(काष्ठा hfs_bnode_desc, next), 4);

	node->type = HFS_NODE_MAP;
	node->num_recs = 1;
	hfs_bnode_clear(node, 0, tree->node_size);
	desc.next = 0;
	desc.prev = 0;
	desc.type = HFS_NODE_MAP;
	desc.height = 0;
	desc.num_recs = cpu_to_be16(1);
	desc.reserved = 0;
	hfs_bnode_ग_लिखो(node, &desc, 0, माप(desc));
	hfs_bnode_ग_लिखो_u16(node, 14, 0x8000);
	hfs_bnode_ग_लिखो_u16(node, tree->node_size - 2, 14);
	hfs_bnode_ग_लिखो_u16(node, tree->node_size - 4, tree->node_size - 6);

	वापस node;
पूर्ण

/* Make sure @tree has enough space क्रम the @rsvd_nodes */
पूर्णांक hfs_bmap_reserve(काष्ठा hfs_btree *tree, पूर्णांक rsvd_nodes)
अणु
	काष्ठा inode *inode = tree->inode;
	u32 count;
	पूर्णांक res;

	जबतक (tree->मुक्त_nodes < rsvd_nodes) अणु
		res = hfs_extend_file(inode);
		अगर (res)
			वापस res;
		HFS_I(inode)->phys_size = inode->i_size =
				(loff_t)HFS_I(inode)->alloc_blocks *
				HFS_SB(tree->sb)->alloc_blksz;
		HFS_I(inode)->fs_blocks = inode->i_size >>
					  tree->sb->s_blocksize_bits;
		inode_set_bytes(inode, inode->i_size);
		count = inode->i_size >> tree->node_size_shअगरt;
		tree->मुक्त_nodes += count - tree->node_count;
		tree->node_count = count;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा hfs_bnode *hfs_bmap_alloc(काष्ठा hfs_btree *tree)
अणु
	काष्ठा hfs_bnode *node, *next_node;
	काष्ठा page **pagep;
	u32 nidx, idx;
	अचिन्हित off;
	u16 off16;
	u16 len;
	u8 *data, byte, m;
	पूर्णांक i, res;

	res = hfs_bmap_reserve(tree, 1);
	अगर (res)
		वापस ERR_PTR(res);

	nidx = 0;
	node = hfs_bnode_find(tree, nidx);
	अगर (IS_ERR(node))
		वापस node;
	len = hfs_brec_lenoff(node, 2, &off16);
	off = off16;

	off += node->page_offset;
	pagep = node->page + (off >> PAGE_SHIFT);
	data = kmap(*pagep);
	off &= ~PAGE_MASK;
	idx = 0;

	क्रम (;;) अणु
		जबतक (len) अणु
			byte = data[off];
			अगर (byte != 0xff) अणु
				क्रम (m = 0x80, i = 0; i < 8; m >>= 1, i++) अणु
					अगर (!(byte & m)) अणु
						idx += i;
						data[off] |= m;
						set_page_dirty(*pagep);
						kunmap(*pagep);
						tree->मुक्त_nodes--;
						mark_inode_dirty(tree->inode);
						hfs_bnode_put(node);
						वापस hfs_bnode_create(tree, idx);
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (++off >= PAGE_SIZE) अणु
				kunmap(*pagep);
				data = kmap(*++pagep);
				off = 0;
			पूर्ण
			idx += 8;
			len--;
		पूर्ण
		kunmap(*pagep);
		nidx = node->next;
		अगर (!nidx) अणु
			prपूर्णांकk(KERN_DEBUG "create new bmap node...\n");
			next_node = hfs_bmap_new_bmap(node, idx);
		पूर्ण अन्यथा
			next_node = hfs_bnode_find(tree, nidx);
		hfs_bnode_put(node);
		अगर (IS_ERR(next_node))
			वापस next_node;
		node = next_node;

		len = hfs_brec_lenoff(node, 0, &off16);
		off = off16;
		off += node->page_offset;
		pagep = node->page + (off >> PAGE_SHIFT);
		data = kmap(*pagep);
		off &= ~PAGE_MASK;
	पूर्ण
पूर्ण

व्योम hfs_bmap_मुक्त(काष्ठा hfs_bnode *node)
अणु
	काष्ठा hfs_btree *tree;
	काष्ठा page *page;
	u16 off, len;
	u32 nidx;
	u8 *data, byte, m;

	hfs_dbg(BNODE_MOD, "btree_free_node: %u\n", node->this);
	tree = node->tree;
	nidx = node->this;
	node = hfs_bnode_find(tree, 0);
	अगर (IS_ERR(node))
		वापस;
	len = hfs_brec_lenoff(node, 2, &off);
	जबतक (nidx >= len * 8) अणु
		u32 i;

		nidx -= len * 8;
		i = node->next;
		अगर (!i) अणु
			/* panic */;
			pr_crit("unable to free bnode %u. bmap not found!\n",
				node->this);
			hfs_bnode_put(node);
			वापस;
		पूर्ण
		hfs_bnode_put(node);
		node = hfs_bnode_find(tree, i);
		अगर (IS_ERR(node))
			वापस;
		अगर (node->type != HFS_NODE_MAP) अणु
			/* panic */;
			pr_crit("invalid bmap found! (%u,%d)\n",
				node->this, node->type);
			hfs_bnode_put(node);
			वापस;
		पूर्ण
		len = hfs_brec_lenoff(node, 0, &off);
	पूर्ण
	off += node->page_offset + nidx / 8;
	page = node->page[off >> PAGE_SHIFT];
	data = kmap(page);
	off &= ~PAGE_MASK;
	m = 1 << (~nidx & 7);
	byte = data[off];
	अगर (!(byte & m)) अणु
		pr_crit("trying to free free bnode %u(%d)\n",
			node->this, node->type);
		kunmap(page);
		hfs_bnode_put(node);
		वापस;
	पूर्ण
	data[off] = byte & ~m;
	set_page_dirty(page);
	kunmap(page);
	hfs_bnode_put(node);
	tree->मुक्त_nodes++;
	mark_inode_dirty(tree->inode);
पूर्ण

<शैली गुरु>
/*
 * linux/fs/befs/btree.c
 *
 * Copyright (C) 2001-2002 Will Dyson <will_dyson@pobox.com>
 *
 * Licensed under the GNU GPL. See the file COPYING क्रम details.
 *
 * 2002-02-05: Sergey S. Kostyliov added binary search within
 * 		btree nodes.
 *
 * Many thanks to:
 *
 * Dominic Giampaolo, author of "Practical File System
 * Design with the Be File System", क्रम such a helpful book.
 *
 * Marcus J. Ranum, author of the b+tree package in
 * comp.sources.misc volume 10. This code is not copied from that
 * work, but it is partially based on it.
 *
 * Makoto Kato, author of the original BeFS क्रम linux fileप्रणाली
 * driver.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/buffer_head.h>

#समावेश "befs.h"
#समावेश "btree.h"
#समावेश "datastream.h"

/*
 * The btree functions in this file are built on top of the
 * datastream.c पूर्णांकerface, which is in turn built on top of the
 * io.c पूर्णांकerface.
 */

/* Befs B+tree काष्ठाure:
 *
 * The first thing in the tree is the tree superblock. It tells you
 * all kinds of useful things about the tree, like where the rootnode
 * is located, and the size of the nodes (always 1024 with current version
 * of BeOS).
 *
 * The rest of the tree consists of a series of nodes. Nodes contain a header
 * (काष्ठा befs_btree_nodehead), the packed key data, an array of लघुs
 * containing the ending offsets क्रम each of the keys, and an array of
 * befs_off_t values. In पूर्णांकerior nodes, the keys are the ending keys क्रम
 * the childnode they poपूर्णांक to, and the values are offsets पूर्णांकo the
 * datastream containing the tree.
 */

/* Note:
 *
 * The book states 2 confusing things about befs b+trees. First,
 * it states that the overflow field of node headers is used by पूर्णांकernal nodes
 * to poपूर्णांक to another node that "effectively continues this one". Here is what
 * I believe that means. Each key in पूर्णांकernal nodes poपूर्णांकs to another node that
 * contains key values less than itself. Inspection reveals that the last key
 * in the पूर्णांकernal node is not the last key in the index. Keys that are
 * greater than the last key in the पूर्णांकernal node go पूर्णांकo the overflow node.
 * I imagine there is a perक्रमmance reason क्रम this.
 *
 * Second, it states that the header of a btree node is sufficient to
 * distinguish पूर्णांकernal nodes from leaf nodes. Without saying exactly how.
 * After figuring out the first, it becomes obvious that पूर्णांकernal nodes have
 * overflow nodes and leafnodes करो not.
 */

/*
 * Currently, this code is only good क्रम directory B+trees.
 * In order to be used क्रम other BFS indexes, it needs to be extended to handle
 * duplicate keys and non-string keytypes (पूर्णांक32, पूर्णांक64, भग्न, द्विगुन).
 */

/*
 * In memory काष्ठाure of each btree node
 */
काष्ठा befs_btree_node अणु
	befs_host_btree_nodehead head;	/* head of node converted to cpu byteorder */
	काष्ठा buffer_head *bh;
	befs_btree_nodehead *od_node;	/* on disk node */
पूर्ण;

/* local स्थिरants */
अटल स्थिर befs_off_t BEFS_BT_INVAL = 0xffffffffffffffffULL;

/* local functions */
अटल पूर्णांक befs_btree_seekleaf(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
			       befs_btree_super * bt_super,
			       काष्ठा befs_btree_node *this_node,
			       befs_off_t * node_off);

अटल पूर्णांक befs_bt_पढ़ो_super(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
			      befs_btree_super * sup);

अटल पूर्णांक befs_bt_पढ़ो_node(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
			     काष्ठा befs_btree_node *node,
			     befs_off_t node_off);

अटल पूर्णांक befs_leafnode(काष्ठा befs_btree_node *node);

अटल fs16 *befs_bt_keylen_index(काष्ठा befs_btree_node *node);

अटल fs64 *befs_bt_valarray(काष्ठा befs_btree_node *node);

अटल अक्षर *befs_bt_keydata(काष्ठा befs_btree_node *node);

अटल पूर्णांक befs_find_key(काष्ठा super_block *sb,
			 काष्ठा befs_btree_node *node,
			 स्थिर अक्षर *findkey, befs_off_t * value);

अटल अक्षर *befs_bt_get_key(काष्ठा super_block *sb,
			     काष्ठा befs_btree_node *node,
			     पूर्णांक index, u16 * keylen);

अटल पूर्णांक befs_compare_strings(स्थिर व्योम *key1, पूर्णांक keylen1,
				स्थिर व्योम *key2, पूर्णांक keylen2);

/**
 * befs_bt_पढ़ो_super() - पढ़ो in btree superblock convert to cpu byteorder
 * @sb:        Fileप्रणाली superblock
 * @ds:        Datastream to पढ़ो from
 * @sup:       Buffer in which to place the btree superblock
 *
 * Calls befs_पढ़ो_datastream to पढ़ो in the btree superblock and
 * makes sure it is in cpu byteorder, byteswapping अगर necessary.
 * Return: BEFS_OK on success and अगर *@sup contains the btree superblock in cpu
 * byte order. Otherwise वापस BEFS_ERR on error.
 */
अटल पूर्णांक
befs_bt_पढ़ो_super(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		   befs_btree_super * sup)
अणु
	काष्ठा buffer_head *bh;
	befs_disk_btree_super *od_sup;

	befs_debug(sb, "---> %s", __func__);

	bh = befs_पढ़ो_datastream(sb, ds, 0, शून्य);

	अगर (!bh) अणु
		befs_error(sb, "Couldn't read index header.");
		जाओ error;
	पूर्ण
	od_sup = (befs_disk_btree_super *) bh->b_data;
	befs_dump_index_entry(sb, od_sup);

	sup->magic = fs32_to_cpu(sb, od_sup->magic);
	sup->node_size = fs32_to_cpu(sb, od_sup->node_size);
	sup->max_depth = fs32_to_cpu(sb, od_sup->max_depth);
	sup->data_type = fs32_to_cpu(sb, od_sup->data_type);
	sup->root_node_ptr = fs64_to_cpu(sb, od_sup->root_node_ptr);

	brअन्यथा(bh);
	अगर (sup->magic != BEFS_BTREE_MAGIC) अणु
		befs_error(sb, "Index header has bad magic.");
		जाओ error;
	पूर्ण

	befs_debug(sb, "<--- %s", __func__);
	वापस BEFS_OK;

      error:
	befs_debug(sb, "<--- %s ERROR", __func__);
	वापस BEFS_ERR;
पूर्ण

/**
 * befs_bt_पढ़ो_node - पढ़ो in btree node and convert to cpu byteorder
 * @sb: Fileप्रणाली superblock
 * @ds: Datastream to पढ़ो from
 * @node: Buffer in which to place the btree node
 * @node_off: Starting offset (in bytes) of the node in @ds
 *
 * Calls befs_पढ़ो_datastream to पढ़ो in the indicated btree node and
 * makes sure its header fields are in cpu byteorder, byteswapping अगर
 * necessary.
 * Note: node->bh must be शून्य when this function is called the first समय.
 * Don't क्रमget brअन्यथा(node->bh) after last call.
 *
 * On success, वापसs BEFS_OK and *@node contains the btree node that
 * starts at @node_off, with the node->head fields in cpu byte order.
 *
 * On failure, BEFS_ERR is वापसed.
 */

अटल पूर्णांक
befs_bt_पढ़ो_node(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		  काष्ठा befs_btree_node *node, befs_off_t node_off)
अणु
	uपूर्णांक off = 0;

	befs_debug(sb, "---> %s", __func__);

	अगर (node->bh)
		brअन्यथा(node->bh);

	node->bh = befs_पढ़ो_datastream(sb, ds, node_off, &off);
	अगर (!node->bh) अणु
		befs_error(sb, "%s failed to read "
			   "node at %llu", __func__, node_off);
		befs_debug(sb, "<--- %s ERROR", __func__);

		वापस BEFS_ERR;
	पूर्ण
	node->od_node =
	    (befs_btree_nodehead *) ((व्योम *) node->bh->b_data + off);

	befs_dump_index_node(sb, node->od_node);

	node->head.left = fs64_to_cpu(sb, node->od_node->left);
	node->head.right = fs64_to_cpu(sb, node->od_node->right);
	node->head.overflow = fs64_to_cpu(sb, node->od_node->overflow);
	node->head.all_key_count =
	    fs16_to_cpu(sb, node->od_node->all_key_count);
	node->head.all_key_length =
	    fs16_to_cpu(sb, node->od_node->all_key_length);

	befs_debug(sb, "<--- %s", __func__);
	वापस BEFS_OK;
पूर्ण

/**
 * befs_btree_find - Find a key in a befs B+tree
 * @sb: Fileप्रणाली superblock
 * @ds: Datastream containing btree
 * @key: Key string to lookup in btree
 * @value: Value stored with @key
 *
 * On success, वापसs BEFS_OK and sets *@value to the value stored
 * with @key (usually the disk block number of an inode).
 *
 * On failure, वापसs BEFS_ERR or BEFS_BT_NOT_FOUND.
 *
 * Algorithm:
 *   Read the superblock and rootnode of the b+tree.
 *   Drill करोwn through the पूर्णांकerior nodes using befs_find_key().
 *   Once at the correct leaf node, use befs_find_key() again to get the
 *   actual value stored with the key.
 */
पूर्णांक
befs_btree_find(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		स्थिर अक्षर *key, befs_off_t * value)
अणु
	काष्ठा befs_btree_node *this_node;
	befs_btree_super bt_super;
	befs_off_t node_off;
	पूर्णांक res;

	befs_debug(sb, "---> %s Key: %s", __func__, key);

	अगर (befs_bt_पढ़ो_super(sb, ds, &bt_super) != BEFS_OK) अणु
		befs_error(sb,
			   "befs_btree_find() failed to read index superblock");
		जाओ error;
	पूर्ण

	this_node = kदो_स्मृति(माप(काष्ठा befs_btree_node),
						GFP_NOFS);
	अगर (!this_node) अणु
		befs_error(sb, "befs_btree_find() failed to allocate %zu "
			   "bytes of memory", माप(काष्ठा befs_btree_node));
		जाओ error;
	पूर्ण

	this_node->bh = शून्य;

	/* पढ़ो in root node */
	node_off = bt_super.root_node_ptr;
	अगर (befs_bt_पढ़ो_node(sb, ds, this_node, node_off) != BEFS_OK) अणु
		befs_error(sb, "befs_btree_find() failed to read "
			   "node at %llu", node_off);
		जाओ error_alloc;
	पूर्ण

	जबतक (!befs_leafnode(this_node)) अणु
		res = befs_find_key(sb, this_node, key, &node_off);
		/* अगर no key set, try the overflow node */
		अगर (res == BEFS_BT_OVERFLOW)
			node_off = this_node->head.overflow;
		अगर (befs_bt_पढ़ो_node(sb, ds, this_node, node_off) != BEFS_OK) अणु
			befs_error(sb, "befs_btree_find() failed to read "
				   "node at %llu", node_off);
			जाओ error_alloc;
		पूर्ण
	पूर्ण

	/* at a leaf node now, check अगर it is correct */
	res = befs_find_key(sb, this_node, key, value);

	brअन्यथा(this_node->bh);
	kमुक्त(this_node);

	अगर (res != BEFS_BT_MATCH) अणु
		befs_error(sb, "<--- %s Key %s not found", __func__, key);
		befs_debug(sb, "<--- %s ERROR", __func__);
		*value = 0;
		वापस BEFS_BT_NOT_FOUND;
	पूर्ण
	befs_debug(sb, "<--- %s Found key %s, value %llu", __func__,
		   key, *value);
	वापस BEFS_OK;

      error_alloc:
	kमुक्त(this_node);
      error:
	*value = 0;
	befs_debug(sb, "<--- %s ERROR", __func__);
	वापस BEFS_ERR;
पूर्ण

/**
 * befs_find_key - Search क्रम a key within a node
 * @sb: Fileप्रणाली superblock
 * @node: Node to find the key within
 * @findkey: Keystring to search क्रम
 * @value: If key is found, the value stored with the key is put here
 *
 * Finds exact match अगर one exists, and वापसs BEFS_BT_MATCH.
 * If there is no match and node's value array is too small क्रम key, वापस
 * BEFS_BT_OVERFLOW.
 * If no match and node should countain this key, वापस BEFS_BT_NOT_FOUND.
 *
 * Uses binary search instead of a linear.
 */
अटल पूर्णांक
befs_find_key(काष्ठा super_block *sb, काष्ठा befs_btree_node *node,
	      स्थिर अक्षर *findkey, befs_off_t * value)
अणु
	पूर्णांक first, last, mid;
	पूर्णांक eq;
	u16 keylen;
	पूर्णांक findkey_len;
	अक्षर *thiskey;
	fs64 *valarray;

	befs_debug(sb, "---> %s %s", __func__, findkey);

	findkey_len = म_माप(findkey);

	/* अगर node can not contain key, just skip this node */
	last = node->head.all_key_count - 1;
	thiskey = befs_bt_get_key(sb, node, last, &keylen);

	eq = befs_compare_strings(thiskey, keylen, findkey, findkey_len);
	अगर (eq < 0) अणु
		befs_debug(sb, "<--- node can't contain %s", findkey);
		वापस BEFS_BT_OVERFLOW;
	पूर्ण

	valarray = befs_bt_valarray(node);

	/* simple binary search */
	first = 0;
	mid = 0;
	जबतक (last >= first) अणु
		mid = (last + first) / 2;
		befs_debug(sb, "first: %d, last: %d, mid: %d", first, last,
			   mid);
		thiskey = befs_bt_get_key(sb, node, mid, &keylen);
		eq = befs_compare_strings(thiskey, keylen, findkey,
					  findkey_len);

		अगर (eq == 0) अणु
			befs_debug(sb, "<--- %s found %s at %d",
				   __func__, thiskey, mid);

			*value = fs64_to_cpu(sb, valarray[mid]);
			वापस BEFS_BT_MATCH;
		पूर्ण
		अगर (eq > 0)
			last = mid - 1;
		अन्यथा
			first = mid + 1;
	पूर्ण

	/* वापस an existing value so caller can arrive to a leaf node */
	अगर (eq < 0)
		*value = fs64_to_cpu(sb, valarray[mid + 1]);
	अन्यथा
		*value = fs64_to_cpu(sb, valarray[mid]);
	befs_error(sb, "<--- %s %s not found", __func__, findkey);
	befs_debug(sb, "<--- %s ERROR", __func__);
	वापस BEFS_BT_NOT_FOUND;
पूर्ण

/**
 * befs_btree_पढ़ो - Traverse leafnodes of a btree
 * @sb: Fileप्रणाली superblock
 * @ds: Datastream containing btree
 * @key_no: Key number (alphabetical order) of key to पढ़ो
 * @bufsize: Size of the buffer to वापस key in
 * @keybuf: Poपूर्णांकer to a buffer to put the key in
 * @keysize: Length of the वापसed key
 * @value: Value stored with the वापसed key
 *
 * Here's how it works: Key_no is the index of the key/value pair to
 * वापस in keybuf/value.
 * Bufsize is the size of keybuf (BEFS_NAME_LEN+1 is a good size). Keysize is
 * the number of अक्षरacters in the key (just a convenience).
 *
 * Algorithm:
 *   Get the first leafnode of the tree. See अगर the requested key is in that
 *   node. If not, follow the node->right link to the next leafnode. Repeat
 *   until the (key_no)th key is found or the tree is out of keys.
 */
पूर्णांक
befs_btree_पढ़ो(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		loff_t key_no, माप_प्रकार bufsize, अक्षर *keybuf, माप_प्रकार * keysize,
		befs_off_t * value)
अणु
	काष्ठा befs_btree_node *this_node;
	befs_btree_super bt_super;
	befs_off_t node_off;
	पूर्णांक cur_key;
	fs64 *valarray;
	अक्षर *keystart;
	u16 keylen;
	पूर्णांक res;

	uपूर्णांक key_sum = 0;

	befs_debug(sb, "---> %s", __func__);

	अगर (befs_bt_पढ़ो_super(sb, ds, &bt_super) != BEFS_OK) अणु
		befs_error(sb,
			   "befs_btree_read() failed to read index superblock");
		जाओ error;
	पूर्ण

	this_node = kदो_स्मृति(माप(काष्ठा befs_btree_node), GFP_NOFS);
	अगर (this_node == शून्य) अणु
		befs_error(sb, "befs_btree_read() failed to allocate %zu "
			   "bytes of memory", माप(काष्ठा befs_btree_node));
		जाओ error;
	पूर्ण

	node_off = bt_super.root_node_ptr;
	this_node->bh = शून्य;

	/* seeks करोwn to first leafnode, पढ़ोs it पूर्णांकo this_node */
	res = befs_btree_seekleaf(sb, ds, &bt_super, this_node, &node_off);
	अगर (res == BEFS_BT_EMPTY) अणु
		brअन्यथा(this_node->bh);
		kमुक्त(this_node);
		*value = 0;
		*keysize = 0;
		befs_debug(sb, "<--- %s Tree is EMPTY", __func__);
		वापस BEFS_BT_EMPTY;
	पूर्ण अन्यथा अगर (res == BEFS_ERR) अणु
		जाओ error_alloc;
	पूर्ण

	/* find the leaf node containing the key_no key */

	जबतक (key_sum + this_node->head.all_key_count <= key_no) अणु

		/* no more nodes to look in: key_no is too large */
		अगर (this_node->head.right == BEFS_BT_INVAL) अणु
			*keysize = 0;
			*value = 0;
			befs_debug(sb,
				   "<--- %s END of keys at %llu", __func__,
				   (अचिन्हित दीर्घ दीर्घ)
				   key_sum + this_node->head.all_key_count);
			brअन्यथा(this_node->bh);
			kमुक्त(this_node);
			वापस BEFS_BT_END;
		पूर्ण

		key_sum += this_node->head.all_key_count;
		node_off = this_node->head.right;

		अगर (befs_bt_पढ़ो_node(sb, ds, this_node, node_off) != BEFS_OK) अणु
			befs_error(sb, "%s failed to read node at %llu",
				  __func__, (अचिन्हित दीर्घ दीर्घ)node_off);
			जाओ error_alloc;
		पूर्ण
	पूर्ण

	/* how many keys पूर्णांकo this_node is key_no */
	cur_key = key_no - key_sum;

	/* get poपूर्णांकers to dataकाष्ठाures within the node body */
	valarray = befs_bt_valarray(this_node);

	keystart = befs_bt_get_key(sb, this_node, cur_key, &keylen);

	befs_debug(sb, "Read [%llu,%d]: keysize %d",
		   (दीर्घ दीर्घ अचिन्हित पूर्णांक)node_off, (पूर्णांक)cur_key,
		   (पूर्णांक)keylen);

	अगर (bufsize < keylen + 1) अणु
		befs_error(sb, "%s keybuf too small (%zu) "
			   "for key of size %d", __func__, bufsize, keylen);
		brअन्यथा(this_node->bh);
		जाओ error_alloc;
	पूर्ण

	strlcpy(keybuf, keystart, keylen + 1);
	*value = fs64_to_cpu(sb, valarray[cur_key]);
	*keysize = keylen;

	befs_debug(sb, "Read [%llu,%d]: Key \"%.*s\", Value %llu", node_off,
		   cur_key, keylen, keybuf, *value);

	brअन्यथा(this_node->bh);
	kमुक्त(this_node);

	befs_debug(sb, "<--- %s", __func__);

	वापस BEFS_OK;

      error_alloc:
	kमुक्त(this_node);

      error:
	*keysize = 0;
	*value = 0;
	befs_debug(sb, "<--- %s ERROR", __func__);
	वापस BEFS_ERR;
पूर्ण

/**
 * befs_btree_seekleaf - Find the first leafnode in the btree
 * @sb: Fileप्रणाली superblock
 * @ds: Datastream containing btree
 * @bt_super: Poपूर्णांकer to the superblock of the btree
 * @this_node: Buffer to वापस the leafnode in
 * @node_off: Poपूर्णांकer to offset of current node within datastream. Modअगरied
 * 		by the function.
 *
 * Helper function क्रम btree traverse. Moves the current position to the
 * start of the first leaf node.
 *
 * Also checks क्रम an empty tree. If there are no keys, वापसs BEFS_BT_EMPTY.
 */
अटल पूर्णांक
befs_btree_seekleaf(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		    befs_btree_super *bt_super,
		    काष्ठा befs_btree_node *this_node,
		    befs_off_t * node_off)
अणु

	befs_debug(sb, "---> %s", __func__);

	अगर (befs_bt_पढ़ो_node(sb, ds, this_node, *node_off) != BEFS_OK) अणु
		befs_error(sb, "%s failed to read "
			   "node at %llu", __func__, *node_off);
		जाओ error;
	पूर्ण
	befs_debug(sb, "Seekleaf to root node %llu", *node_off);

	अगर (this_node->head.all_key_count == 0 && befs_leafnode(this_node)) अणु
		befs_debug(sb, "<--- %s Tree is EMPTY", __func__);
		वापस BEFS_BT_EMPTY;
	पूर्ण

	जबतक (!befs_leafnode(this_node)) अणु

		अगर (this_node->head.all_key_count == 0) अणु
			befs_debug(sb, "%s encountered "
				   "an empty interior node: %llu. Using Overflow "
				   "node: %llu", __func__, *node_off,
				   this_node->head.overflow);
			*node_off = this_node->head.overflow;
		पूर्ण अन्यथा अणु
			fs64 *valarray = befs_bt_valarray(this_node);
			*node_off = fs64_to_cpu(sb, valarray[0]);
		पूर्ण
		अगर (befs_bt_पढ़ो_node(sb, ds, this_node, *node_off) != BEFS_OK) अणु
			befs_error(sb, "%s failed to read "
				   "node at %llu", __func__, *node_off);
			जाओ error;
		पूर्ण

		befs_debug(sb, "Seekleaf to child node %llu", *node_off);
	पूर्ण
	befs_debug(sb, "Node %llu is a leaf node", *node_off);

	वापस BEFS_OK;

      error:
	befs_debug(sb, "<--- %s ERROR", __func__);
	वापस BEFS_ERR;
पूर्ण

/**
 * befs_leafnode - Determine अगर the btree node is a leaf node or an
 * पूर्णांकerior node
 * @node: Poपूर्णांकer to node काष्ठाure to test
 *
 * Return 1 अगर leaf, 0 अगर पूर्णांकerior
 */
अटल पूर्णांक
befs_leafnode(काष्ठा befs_btree_node *node)
अणु
	/* all पूर्णांकerior nodes (and only पूर्णांकerior nodes) have an overflow node */
	अगर (node->head.overflow == BEFS_BT_INVAL)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * befs_bt_keylen_index - Finds start of keylen index in a node
 * @node: Poपूर्णांकer to the node काष्ठाure to find the keylen index within
 *
 * Returns a poपूर्णांकer to the start of the key length index array
 * of the B+tree node *@node
 *
 * "The length of all the keys in the node is added to the size of the
 * header and then rounded up to a multiple of four to get the beginning
 * of the key length index" (p.88, practical fileप्रणाली design).
 *
 * Except that rounding up to 8 works, and rounding up to 4 करोesn't.
 */
अटल fs16 *
befs_bt_keylen_index(काष्ठा befs_btree_node *node)
अणु
	स्थिर पूर्णांक keylen_align = 8;
	अचिन्हित दीर्घ पूर्णांक off =
	    (माप (befs_btree_nodehead) + node->head.all_key_length);
	uदीर्घ पंचांगp = off % keylen_align;

	अगर (पंचांगp)
		off += keylen_align - पंचांगp;

	वापस (fs16 *) ((व्योम *) node->od_node + off);
पूर्ण

/**
 * befs_bt_valarray - Finds the start of value array in a node
 * @node: Poपूर्णांकer to the node काष्ठाure to find the value array within
 *
 * Returns a poपूर्णांकer to the start of the value array
 * of the node poपूर्णांकed to by the node header
 */
अटल fs64 *
befs_bt_valarray(काष्ठा befs_btree_node *node)
अणु
	व्योम *keylen_index_start = (व्योम *) befs_bt_keylen_index(node);
	माप_प्रकार keylen_index_size = node->head.all_key_count * माप (fs16);

	वापस (fs64 *) (keylen_index_start + keylen_index_size);
पूर्ण

/**
 * befs_bt_keydata - Finds start of keydata array in a node
 * @node: Poपूर्णांकer to the node काष्ठाure to find the keydata array within
 *
 * Returns a poपूर्णांकer to the start of the keydata array
 * of the node poपूर्णांकed to by the node header
 */
अटल अक्षर *
befs_bt_keydata(काष्ठा befs_btree_node *node)
अणु
	वापस (अक्षर *) ((व्योम *) node->od_node + माप (befs_btree_nodehead));
पूर्ण

/**
 * befs_bt_get_key - वापसs a poपूर्णांकer to the start of a key
 * @sb: fileप्रणाली superblock
 * @node: node in which to look क्रम the key
 * @index: the index of the key to get
 * @keylen: modअगरied to be the length of the key at @index
 *
 * Returns a valid poपूर्णांकer पूर्णांकo @node on success.
 * Returns शून्य on failure (bad input) and sets *@keylen = 0
 */
अटल अक्षर *
befs_bt_get_key(काष्ठा super_block *sb, काष्ठा befs_btree_node *node,
		पूर्णांक index, u16 * keylen)
अणु
	पूर्णांक prev_key_end;
	अक्षर *keystart;
	fs16 *keylen_index;

	अगर (index < 0 || index > node->head.all_key_count) अणु
		*keylen = 0;
		वापस शून्य;
	पूर्ण

	keystart = befs_bt_keydata(node);
	keylen_index = befs_bt_keylen_index(node);

	अगर (index == 0)
		prev_key_end = 0;
	अन्यथा
		prev_key_end = fs16_to_cpu(sb, keylen_index[index - 1]);

	*keylen = fs16_to_cpu(sb, keylen_index[index]) - prev_key_end;

	वापस keystart + prev_key_end;
पूर्ण

/**
 * befs_compare_strings - compare two strings
 * @key1: poपूर्णांकer to the first key to be compared
 * @keylen1: length in bytes of key1
 * @key2: poपूर्णांकer to the second key to be compared
 * @keylen2: length in bytes of key2
 *
 * Returns 0 अगर @key1 and @key2 are equal.
 * Returns >0 अगर @key1 is greater.
 * Returns <0 अगर @key2 is greater.
 */
अटल पूर्णांक
befs_compare_strings(स्थिर व्योम *key1, पूर्णांक keylen1,
		     स्थिर व्योम *key2, पूर्णांक keylen2)
अणु
	पूर्णांक len = min_t(पूर्णांक, keylen1, keylen2);
	पूर्णांक result = म_भेदन(key1, key2, len);
	अगर (result == 0)
		result = keylen1 - keylen2;
	वापस result;
पूर्ण

/* These will be used क्रम non-string keyed btrees */
#अगर 0
अटल पूर्णांक
btree_compare_पूर्णांक32(cont व्योम *key1, पूर्णांक keylen1, स्थिर व्योम *key2, पूर्णांक keylen2)
अणु
	वापस *(पूर्णांक32_t *) key1 - *(पूर्णांक32_t *) key2;
पूर्ण

अटल पूर्णांक
btree_compare_uपूर्णांक32(cont व्योम *key1, पूर्णांक keylen1,
		     स्थिर व्योम *key2, पूर्णांक keylen2)
अणु
	अगर (*(u_पूर्णांक32_t *) key1 == *(u_पूर्णांक32_t *) key2)
		वापस 0;
	अन्यथा अगर (*(u_पूर्णांक32_t *) key1 > *(u_पूर्णांक32_t *) key2)
		वापस 1;

	वापस -1;
पूर्ण
अटल पूर्णांक
btree_compare_पूर्णांक64(cont व्योम *key1, पूर्णांक keylen1, स्थिर व्योम *key2, पूर्णांक keylen2)
अणु
	अगर (*(पूर्णांक64_t *) key1 == *(पूर्णांक64_t *) key2)
		वापस 0;
	अन्यथा अगर (*(पूर्णांक64_t *) key1 > *(पूर्णांक64_t *) key2)
		वापस 1;

	वापस -1;
पूर्ण

अटल पूर्णांक
btree_compare_uपूर्णांक64(cont व्योम *key1, पूर्णांक keylen1,
		     स्थिर व्योम *key2, पूर्णांक keylen2)
अणु
	अगर (*(u_पूर्णांक64_t *) key1 == *(u_पूर्णांक64_t *) key2)
		वापस 0;
	अन्यथा अगर (*(u_पूर्णांक64_t *) key1 > *(u_पूर्णांक64_t *) key2)
		वापस 1;

	वापस -1;
पूर्ण

अटल पूर्णांक
btree_compare_भग्न(cont व्योम *key1, पूर्णांक keylen1, स्थिर व्योम *key2, पूर्णांक keylen2)
अणु
	भग्न result = *(भग्न *) key1 - *(भग्न *) key2;
	अगर (result == 0.0f)
		वापस 0;

	वापस (result < 0.0f) ? -1 : 1;
पूर्ण

अटल पूर्णांक
btree_compare_द्विगुन(cont व्योम *key1, पूर्णांक keylen1,
		     स्थिर व्योम *key2, पूर्णांक keylen2)
अणु
	द्विगुन result = *(द्विगुन *) key1 - *(द्विगुन *) key2;
	अगर (result == 0.0)
		वापस 0;

	वापस (result < 0.0) ? -1 : 1;
पूर्ण
#पूर्ण_अगर				//0

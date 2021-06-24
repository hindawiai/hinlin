<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * bmap.c - NILFS block mapping.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश "nilfs.h"
#समावेश "bmap.h"
#समावेश "btree.h"
#समावेश "direct.h"
#समावेश "btnode.h"
#समावेश "mdt.h"
#समावेश "dat.h"
#समावेश "alloc.h"

काष्ठा inode *nilfs_bmap_get_dat(स्थिर काष्ठा nilfs_bmap *bmap)
अणु
	काष्ठा the_nilfs *nilfs = bmap->b_inode->i_sb->s_fs_info;

	वापस nilfs->ns_dat;
पूर्ण

अटल पूर्णांक nilfs_bmap_convert_error(काष्ठा nilfs_bmap *bmap,
				     स्थिर अक्षर *fname, पूर्णांक err)
अणु
	काष्ठा inode *inode = bmap->b_inode;

	अगर (err == -EINVAL) अणु
		__nilfs_error(inode->i_sb, fname,
			      "broken bmap (inode number=%lu)", inode->i_ino);
		err = -EIO;
	पूर्ण
	वापस err;
पूर्ण

/**
 * nilfs_bmap_lookup_at_level - find a data block or node block
 * @bmap: bmap
 * @key: key
 * @level: level
 * @ptrp: place to store the value associated to @key
 *
 * Description: nilfs_bmap_lookup_at_level() finds a record whose key
 * matches @key in the block at @level of the bmap.
 *
 * Return Value: On success, 0 is वापसed and the record associated with @key
 * is stored in the place poपूर्णांकed by @ptrp. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - A record associated with @key करोes not exist.
 */
पूर्णांक nilfs_bmap_lookup_at_level(काष्ठा nilfs_bmap *bmap, __u64 key, पूर्णांक level,
			       __u64 *ptrp)
अणु
	sector_t blocknr;
	पूर्णांक ret;

	करोwn_पढ़ो(&bmap->b_sem);
	ret = bmap->b_ops->bop_lookup(bmap, key, level, ptrp);
	अगर (ret < 0) अणु
		ret = nilfs_bmap_convert_error(bmap, __func__, ret);
		जाओ out;
	पूर्ण
	अगर (NILFS_BMAP_USE_VBN(bmap)) अणु
		ret = nilfs_dat_translate(nilfs_bmap_get_dat(bmap), *ptrp,
					  &blocknr);
		अगर (!ret)
			*ptrp = blocknr;
	पूर्ण

 out:
	up_पढ़ो(&bmap->b_sem);
	वापस ret;
पूर्ण

पूर्णांक nilfs_bmap_lookup_contig(काष्ठा nilfs_bmap *bmap, __u64 key, __u64 *ptrp,
			     अचिन्हित पूर्णांक maxblocks)
अणु
	पूर्णांक ret;

	करोwn_पढ़ो(&bmap->b_sem);
	ret = bmap->b_ops->bop_lookup_contig(bmap, key, ptrp, maxblocks);
	up_पढ़ो(&bmap->b_sem);

	वापस nilfs_bmap_convert_error(bmap, __func__, ret);
पूर्ण

अटल पूर्णांक nilfs_bmap_करो_insert(काष्ठा nilfs_bmap *bmap, __u64 key, __u64 ptr)
अणु
	__u64 keys[NILFS_BMAP_SMALL_HIGH + 1];
	__u64 ptrs[NILFS_BMAP_SMALL_HIGH + 1];
	पूर्णांक ret, n;

	अगर (bmap->b_ops->bop_check_insert != शून्य) अणु
		ret = bmap->b_ops->bop_check_insert(bmap, key);
		अगर (ret > 0) अणु
			n = bmap->b_ops->bop_gather_data(
				bmap, keys, ptrs, NILFS_BMAP_SMALL_HIGH + 1);
			अगर (n < 0)
				वापस n;
			ret = nilfs_btree_convert_and_insert(
				bmap, key, ptr, keys, ptrs, n);
			अगर (ret == 0)
				bmap->b_u.u_flags |= NILFS_BMAP_LARGE;

			वापस ret;
		पूर्ण अन्यथा अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस bmap->b_ops->bop_insert(bmap, key, ptr);
पूर्ण

/**
 * nilfs_bmap_insert - insert a new key-record pair पूर्णांकo a bmap
 * @bmap: bmap
 * @key: key
 * @rec: record
 *
 * Description: nilfs_bmap_insert() inserts the new key-record pair specअगरied
 * by @key and @rec पूर्णांकo @bmap.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EEXIST - A record associated with @key alपढ़ोy exist.
 */
पूर्णांक nilfs_bmap_insert(काष्ठा nilfs_bmap *bmap, __u64 key, अचिन्हित दीर्घ rec)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&bmap->b_sem);
	ret = nilfs_bmap_करो_insert(bmap, key, rec);
	up_ग_लिखो(&bmap->b_sem);

	वापस nilfs_bmap_convert_error(bmap, __func__, ret);
पूर्ण

अटल पूर्णांक nilfs_bmap_करो_delete(काष्ठा nilfs_bmap *bmap, __u64 key)
अणु
	__u64 keys[NILFS_BMAP_LARGE_LOW + 1];
	__u64 ptrs[NILFS_BMAP_LARGE_LOW + 1];
	पूर्णांक ret, n;

	अगर (bmap->b_ops->bop_check_delete != शून्य) अणु
		ret = bmap->b_ops->bop_check_delete(bmap, key);
		अगर (ret > 0) अणु
			n = bmap->b_ops->bop_gather_data(
				bmap, keys, ptrs, NILFS_BMAP_LARGE_LOW + 1);
			अगर (n < 0)
				वापस n;
			ret = nilfs_direct_delete_and_convert(
				bmap, key, keys, ptrs, n);
			अगर (ret == 0)
				bmap->b_u.u_flags &= ~NILFS_BMAP_LARGE;

			वापस ret;
		पूर्ण अन्यथा अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस bmap->b_ops->bop_delete(bmap, key);
पूर्ण

/**
 * nilfs_bmap_seek_key - seek a valid entry and वापस its key
 * @bmap: bmap काष्ठा
 * @start: start key number
 * @keyp: place to store valid key
 *
 * Description: nilfs_bmap_seek_key() seeks a valid key on @bmap
 * starting from @start, and stores it to @keyp अगर found.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - No valid entry was found
 */
पूर्णांक nilfs_bmap_seek_key(काष्ठा nilfs_bmap *bmap, __u64 start, __u64 *keyp)
अणु
	पूर्णांक ret;

	करोwn_पढ़ो(&bmap->b_sem);
	ret = bmap->b_ops->bop_seek_key(bmap, start, keyp);
	up_पढ़ो(&bmap->b_sem);

	अगर (ret < 0)
		ret = nilfs_bmap_convert_error(bmap, __func__, ret);
	वापस ret;
पूर्ण

पूर्णांक nilfs_bmap_last_key(काष्ठा nilfs_bmap *bmap, __u64 *keyp)
अणु
	पूर्णांक ret;

	करोwn_पढ़ो(&bmap->b_sem);
	ret = bmap->b_ops->bop_last_key(bmap, keyp);
	up_पढ़ो(&bmap->b_sem);

	अगर (ret < 0)
		ret = nilfs_bmap_convert_error(bmap, __func__, ret);
	वापस ret;
पूर्ण

/**
 * nilfs_bmap_delete - delete a key-record pair from a bmap
 * @bmap: bmap
 * @key: key
 *
 * Description: nilfs_bmap_delete() deletes the key-record pair specअगरied by
 * @key from @bmap.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - A record associated with @key करोes not exist.
 */
पूर्णांक nilfs_bmap_delete(काष्ठा nilfs_bmap *bmap, __u64 key)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&bmap->b_sem);
	ret = nilfs_bmap_करो_delete(bmap, key);
	up_ग_लिखो(&bmap->b_sem);

	वापस nilfs_bmap_convert_error(bmap, __func__, ret);
पूर्ण

अटल पूर्णांक nilfs_bmap_करो_truncate(काष्ठा nilfs_bmap *bmap, __u64 key)
अणु
	__u64 lastkey;
	पूर्णांक ret;

	ret = bmap->b_ops->bop_last_key(bmap, &lastkey);
	अगर (ret < 0) अणु
		अगर (ret == -ENOENT)
			ret = 0;
		वापस ret;
	पूर्ण

	जबतक (key <= lastkey) अणु
		ret = nilfs_bmap_करो_delete(bmap, lastkey);
		अगर (ret < 0)
			वापस ret;
		ret = bmap->b_ops->bop_last_key(bmap, &lastkey);
		अगर (ret < 0) अणु
			अगर (ret == -ENOENT)
				ret = 0;
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * nilfs_bmap_truncate - truncate a bmap to a specअगरied key
 * @bmap: bmap
 * @key: key
 *
 * Description: nilfs_bmap_truncate() हटाओs key-record pairs whose keys are
 * greater than or equal to @key from @bmap.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_bmap_truncate(काष्ठा nilfs_bmap *bmap, __u64 key)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&bmap->b_sem);
	ret = nilfs_bmap_करो_truncate(bmap, key);
	up_ग_लिखो(&bmap->b_sem);

	वापस nilfs_bmap_convert_error(bmap, __func__, ret);
पूर्ण

/**
 * nilfs_bmap_clear - मुक्त resources a bmap holds
 * @bmap: bmap
 *
 * Description: nilfs_bmap_clear() मुक्तs resources associated with @bmap.
 */
व्योम nilfs_bmap_clear(काष्ठा nilfs_bmap *bmap)
अणु
	करोwn_ग_लिखो(&bmap->b_sem);
	अगर (bmap->b_ops->bop_clear != शून्य)
		bmap->b_ops->bop_clear(bmap);
	up_ग_लिखो(&bmap->b_sem);
पूर्ण

/**
 * nilfs_bmap_propagate - propagate dirty state
 * @bmap: bmap
 * @bh: buffer head
 *
 * Description: nilfs_bmap_propagate() marks the buffers that directly or
 * indirectly refer to the block specअगरied by @bh dirty.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_bmap_propagate(काष्ठा nilfs_bmap *bmap, काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&bmap->b_sem);
	ret = bmap->b_ops->bop_propagate(bmap, bh);
	up_ग_लिखो(&bmap->b_sem);

	वापस nilfs_bmap_convert_error(bmap, __func__, ret);
पूर्ण

/**
 * nilfs_bmap_lookup_dirty_buffers -
 * @bmap: bmap
 * @listp: poपूर्णांकer to buffer head list
 */
व्योम nilfs_bmap_lookup_dirty_buffers(काष्ठा nilfs_bmap *bmap,
				     काष्ठा list_head *listp)
अणु
	अगर (bmap->b_ops->bop_lookup_dirty_buffers != शून्य)
		bmap->b_ops->bop_lookup_dirty_buffers(bmap, listp);
पूर्ण

/**
 * nilfs_bmap_assign - assign a new block number to a block
 * @bmap: bmap
 * @bh: poपूर्णांकer to buffer head
 * @blocknr: block number
 * @binfo: block inक्रमmation
 *
 * Description: nilfs_bmap_assign() assigns the block number @blocknr to the
 * buffer specअगरied by @bh.
 *
 * Return Value: On success, 0 is वापसed and the buffer head of a newly
 * create buffer and the block inक्रमmation associated with the buffer are
 * stored in the place poपूर्णांकed by @bh and @binfo, respectively. On error, one
 * of the following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_bmap_assign(काष्ठा nilfs_bmap *bmap,
		      काष्ठा buffer_head **bh,
		      अचिन्हित दीर्घ blocknr,
		      जोड़ nilfs_binfo *binfo)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&bmap->b_sem);
	ret = bmap->b_ops->bop_assign(bmap, bh, blocknr, binfo);
	up_ग_लिखो(&bmap->b_sem);

	वापस nilfs_bmap_convert_error(bmap, __func__, ret);
पूर्ण

/**
 * nilfs_bmap_mark - mark block dirty
 * @bmap: bmap
 * @key: key
 * @level: level
 *
 * Description: nilfs_bmap_mark() marks the block specअगरied by @key and @level
 * as dirty.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_bmap_mark(काष्ठा nilfs_bmap *bmap, __u64 key, पूर्णांक level)
अणु
	पूर्णांक ret;

	अगर (bmap->b_ops->bop_mark == शून्य)
		वापस 0;

	करोwn_ग_लिखो(&bmap->b_sem);
	ret = bmap->b_ops->bop_mark(bmap, key, level);
	up_ग_लिखो(&bmap->b_sem);

	वापस nilfs_bmap_convert_error(bmap, __func__, ret);
पूर्ण

/**
 * nilfs_bmap_test_and_clear_dirty - test and clear a bmap dirty state
 * @bmap: bmap
 *
 * Description: nilfs_test_and_clear() is the atomic operation to test and
 * clear the dirty state of @bmap.
 *
 * Return Value: 1 is वापसed अगर @bmap is dirty, or 0 अगर clear.
 */
पूर्णांक nilfs_bmap_test_and_clear_dirty(काष्ठा nilfs_bmap *bmap)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&bmap->b_sem);
	ret = nilfs_bmap_dirty(bmap);
	nilfs_bmap_clear_dirty(bmap);
	up_ग_लिखो(&bmap->b_sem);
	वापस ret;
पूर्ण


/*
 * Internal use only
 */
__u64 nilfs_bmap_data_get_key(स्थिर काष्ठा nilfs_bmap *bmap,
			      स्थिर काष्ठा buffer_head *bh)
अणु
	काष्ठा buffer_head *pbh;
	__u64 key;

	key = page_index(bh->b_page) << (PAGE_SHIFT -
					 bmap->b_inode->i_blkbits);
	क्रम (pbh = page_buffers(bh->b_page); pbh != bh; pbh = pbh->b_this_page)
		key++;

	वापस key;
पूर्ण

__u64 nilfs_bmap_find_target_seq(स्थिर काष्ठा nilfs_bmap *bmap, __u64 key)
अणु
	__s64 dअगरf;

	dअगरf = key - bmap->b_last_allocated_key;
	अगर ((nilfs_bmap_keydअगरf_असल(dअगरf) < NILFS_INODE_BMAP_SIZE) &&
	    (bmap->b_last_allocated_ptr != NILFS_BMAP_INVALID_PTR) &&
	    (bmap->b_last_allocated_ptr + dअगरf > 0))
		वापस bmap->b_last_allocated_ptr + dअगरf;
	अन्यथा
		वापस NILFS_BMAP_INVALID_PTR;
पूर्ण

#घोषणा NILFS_BMAP_GROUP_DIV	8
__u64 nilfs_bmap_find_target_in_group(स्थिर काष्ठा nilfs_bmap *bmap)
अणु
	काष्ठा inode *dat = nilfs_bmap_get_dat(bmap);
	अचिन्हित दीर्घ entries_per_group = nilfs_palloc_entries_per_group(dat);
	अचिन्हित दीर्घ group = bmap->b_inode->i_ino / entries_per_group;

	वापस group * entries_per_group +
		(bmap->b_inode->i_ino % NILFS_BMAP_GROUP_DIV) *
		(entries_per_group / NILFS_BMAP_GROUP_DIV);
पूर्ण

अटल काष्ठा lock_class_key nilfs_bmap_dat_lock_key;
अटल काष्ठा lock_class_key nilfs_bmap_mdt_lock_key;

/**
 * nilfs_bmap_पढ़ो - पढ़ो a bmap from an inode
 * @bmap: bmap
 * @raw_inode: on-disk inode
 *
 * Description: nilfs_bmap_पढ़ो() initializes the bmap @bmap.
 *
 * Return Value: On success, 0 is वापसed. On error, the following negative
 * error code is वापसed.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_bmap_पढ़ो(काष्ठा nilfs_bmap *bmap, काष्ठा nilfs_inode *raw_inode)
अणु
	अगर (raw_inode == शून्य)
		स_रखो(bmap->b_u.u_data, 0, NILFS_BMAP_SIZE);
	अन्यथा
		स_नकल(bmap->b_u.u_data, raw_inode->i_bmap, NILFS_BMAP_SIZE);

	init_rwsem(&bmap->b_sem);
	bmap->b_state = 0;
	bmap->b_inode = &NILFS_BMAP_I(bmap)->vfs_inode;
	चयन (bmap->b_inode->i_ino) अणु
	हाल NILFS_DAT_INO:
		bmap->b_ptr_type = NILFS_BMAP_PTR_P;
		bmap->b_last_allocated_key = 0;
		bmap->b_last_allocated_ptr = NILFS_BMAP_NEW_PTR_INIT;
		lockdep_set_class(&bmap->b_sem, &nilfs_bmap_dat_lock_key);
		अवरोध;
	हाल NILFS_CPखाता_INO:
	हाल NILFS_SUखाता_INO:
		bmap->b_ptr_type = NILFS_BMAP_PTR_VS;
		bmap->b_last_allocated_key = 0;
		bmap->b_last_allocated_ptr = NILFS_BMAP_INVALID_PTR;
		lockdep_set_class(&bmap->b_sem, &nilfs_bmap_mdt_lock_key);
		अवरोध;
	हाल NILFS_Iखाता_INO:
		lockdep_set_class(&bmap->b_sem, &nilfs_bmap_mdt_lock_key);
		fallthrough;
	शेष:
		bmap->b_ptr_type = NILFS_BMAP_PTR_VM;
		bmap->b_last_allocated_key = 0;
		bmap->b_last_allocated_ptr = NILFS_BMAP_INVALID_PTR;
		अवरोध;
	पूर्ण

	वापस (bmap->b_u.u_flags & NILFS_BMAP_LARGE) ?
		nilfs_btree_init(bmap) : nilfs_direct_init(bmap);
पूर्ण

/**
 * nilfs_bmap_ग_लिखो - ग_लिखो back a bmap to an inode
 * @bmap: bmap
 * @raw_inode: on-disk inode
 *
 * Description: nilfs_bmap_ग_लिखो() stores @bmap in @raw_inode.
 */
व्योम nilfs_bmap_ग_लिखो(काष्ठा nilfs_bmap *bmap, काष्ठा nilfs_inode *raw_inode)
अणु
	करोwn_ग_लिखो(&bmap->b_sem);
	स_नकल(raw_inode->i_bmap, bmap->b_u.u_data,
	       NILFS_INODE_BMAP_SIZE * माप(__le64));
	अगर (bmap->b_inode->i_ino == NILFS_DAT_INO)
		bmap->b_last_allocated_ptr = NILFS_BMAP_NEW_PTR_INIT;

	up_ग_लिखो(&bmap->b_sem);
पूर्ण

व्योम nilfs_bmap_init_gc(काष्ठा nilfs_bmap *bmap)
अणु
	स_रखो(&bmap->b_u, 0, NILFS_BMAP_SIZE);
	init_rwsem(&bmap->b_sem);
	bmap->b_inode = &NILFS_BMAP_I(bmap)->vfs_inode;
	bmap->b_ptr_type = NILFS_BMAP_PTR_U;
	bmap->b_last_allocated_key = 0;
	bmap->b_last_allocated_ptr = NILFS_BMAP_INVALID_PTR;
	bmap->b_state = 0;
	nilfs_btree_init_gc(bmap);
पूर्ण

व्योम nilfs_bmap_save(स्थिर काष्ठा nilfs_bmap *bmap,
		     काष्ठा nilfs_bmap_store *store)
अणु
	स_नकल(store->data, bmap->b_u.u_data, माप(store->data));
	store->last_allocated_key = bmap->b_last_allocated_key;
	store->last_allocated_ptr = bmap->b_last_allocated_ptr;
	store->state = bmap->b_state;
पूर्ण

व्योम nilfs_bmap_restore(काष्ठा nilfs_bmap *bmap,
			स्थिर काष्ठा nilfs_bmap_store *store)
अणु
	स_नकल(bmap->b_u.u_data, store->data, माप(store->data));
	bmap->b_last_allocated_key = store->last_allocated_key;
	bmap->b_last_allocated_ptr = store->last_allocated_ptr;
	bmap->b_state = store->state;
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * अगरile.c - NILFS inode file
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Amagai Yoshiji.
 * Revised by Ryusuke Konishi.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश "nilfs.h"
#समावेश "mdt.h"
#समावेश "alloc.h"
#समावेश "ifile.h"

/**
 * काष्ठा nilfs_अगरile_info - on-memory निजी data of अगरile
 * @mi: on-memory निजी data of metadata file
 * @palloc_cache: persistent object allocator cache of अगरile
 */
काष्ठा nilfs_अगरile_info अणु
	काष्ठा nilfs_mdt_info mi;
	काष्ठा nilfs_palloc_cache palloc_cache;
पूर्ण;

अटल अंतरभूत काष्ठा nilfs_अगरile_info *NILFS_Iखाता_I(काष्ठा inode *अगरile)
अणु
	वापस (काष्ठा nilfs_अगरile_info *)NILFS_MDT(अगरile);
पूर्ण

/**
 * nilfs_अगरile_create_inode - create a new disk inode
 * @अगरile: अगरile inode
 * @out_ino: poपूर्णांकer to a variable to store inode number
 * @out_bh: buffer_head contains newly allocated disk inode
 *
 * Return Value: On success, 0 is वापसed and the newly allocated inode
 * number is stored in the place poपूर्णांकed by @ino, and buffer_head poपूर्णांकer
 * that contains newly allocated disk inode काष्ठाure is stored in the
 * place poपूर्णांकed by @out_bh
 * On error, one of the following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOSPC - No inode left.
 */
पूर्णांक nilfs_अगरile_create_inode(काष्ठा inode *अगरile, ino_t *out_ino,
			     काष्ठा buffer_head **out_bh)
अणु
	काष्ठा nilfs_palloc_req req;
	पूर्णांक ret;

	req.pr_entry_nr = 0;  /*
			       * 0 says find मुक्त inode from beginning
			       * of a group. dull code!!
			       */
	req.pr_entry_bh = शून्य;

	ret = nilfs_palloc_prepare_alloc_entry(अगरile, &req);
	अगर (!ret) अणु
		ret = nilfs_palloc_get_entry_block(अगरile, req.pr_entry_nr, 1,
						   &req.pr_entry_bh);
		अगर (ret < 0)
			nilfs_palloc_पात_alloc_entry(अगरile, &req);
	पूर्ण
	अगर (ret < 0) अणु
		brअन्यथा(req.pr_entry_bh);
		वापस ret;
	पूर्ण
	nilfs_palloc_commit_alloc_entry(अगरile, &req);
	mark_buffer_dirty(req.pr_entry_bh);
	nilfs_mdt_mark_dirty(अगरile);
	*out_ino = (ino_t)req.pr_entry_nr;
	*out_bh = req.pr_entry_bh;
	वापस 0;
पूर्ण

/**
 * nilfs_अगरile_delete_inode - delete a disk inode
 * @अगरile: अगरile inode
 * @ino: inode number
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - The inode number @ino have not been allocated.
 */
पूर्णांक nilfs_अगरile_delete_inode(काष्ठा inode *अगरile, ino_t ino)
अणु
	काष्ठा nilfs_palloc_req req = अणु
		.pr_entry_nr = ino, .pr_entry_bh = शून्य
	पूर्ण;
	काष्ठा nilfs_inode *raw_inode;
	व्योम *kaddr;
	पूर्णांक ret;

	ret = nilfs_palloc_prepare_मुक्त_entry(अगरile, &req);
	अगर (!ret) अणु
		ret = nilfs_palloc_get_entry_block(अगरile, req.pr_entry_nr, 0,
						   &req.pr_entry_bh);
		अगर (ret < 0)
			nilfs_palloc_पात_मुक्त_entry(अगरile, &req);
	पूर्ण
	अगर (ret < 0) अणु
		brअन्यथा(req.pr_entry_bh);
		वापस ret;
	पूर्ण

	kaddr = kmap_atomic(req.pr_entry_bh->b_page);
	raw_inode = nilfs_palloc_block_get_entry(अगरile, req.pr_entry_nr,
						 req.pr_entry_bh, kaddr);
	raw_inode->i_flags = 0;
	kunmap_atomic(kaddr);

	mark_buffer_dirty(req.pr_entry_bh);
	brअन्यथा(req.pr_entry_bh);

	nilfs_palloc_commit_मुक्त_entry(अगरile, &req);

	वापस 0;
पूर्ण

पूर्णांक nilfs_अगरile_get_inode_block(काष्ठा inode *अगरile, ino_t ino,
				काष्ठा buffer_head **out_bh)
अणु
	काष्ठा super_block *sb = अगरile->i_sb;
	पूर्णांक err;

	अगर (unlikely(!NILFS_VALID_INODE(sb, ino))) अणु
		nilfs_error(sb, "bad inode number: %lu", (अचिन्हित दीर्घ)ino);
		वापस -EINVAL;
	पूर्ण

	err = nilfs_palloc_get_entry_block(अगरile, ino, 0, out_bh);
	अगर (unlikely(err))
		nilfs_warn(sb, "error %d reading inode: ino=%lu",
			   err, (अचिन्हित दीर्घ)ino);
	वापस err;
पूर्ण

/**
 * nilfs_अगरile_count_मुक्त_inodes - calculate मुक्त inodes count
 * @अगरile: अगरile inode
 * @nmaxinodes: current maximum of available inodes count [out]
 * @nमुक्तinodes: मुक्त inodes count [out]
 */
पूर्णांक nilfs_अगरile_count_मुक्त_inodes(काष्ठा inode *अगरile,
				    u64 *nmaxinodes, u64 *nमुक्तinodes)
अणु
	u64 nused;
	पूर्णांक err;

	*nmaxinodes = 0;
	*nमुक्तinodes = 0;

	nused = atomic64_पढ़ो(&NILFS_I(अगरile)->i_root->inodes_count);
	err = nilfs_palloc_count_max_entries(अगरile, nused, nmaxinodes);
	अगर (likely(!err))
		*nमुक्तinodes = *nmaxinodes - nused;
	वापस err;
पूर्ण

/**
 * nilfs_अगरile_पढ़ो - पढ़ो or get अगरile inode
 * @sb: super block instance
 * @root: root object
 * @inode_size: size of an inode
 * @raw_inode: on-disk अगरile inode
 * @inodep: buffer to store the inode
 */
पूर्णांक nilfs_अगरile_पढ़ो(काष्ठा super_block *sb, काष्ठा nilfs_root *root,
		     माप_प्रकार inode_size, काष्ठा nilfs_inode *raw_inode,
		     काष्ठा inode **inodep)
अणु
	काष्ठा inode *अगरile;
	पूर्णांक err;

	अगरile = nilfs_iget_locked(sb, root, NILFS_Iखाता_INO);
	अगर (unlikely(!अगरile))
		वापस -ENOMEM;
	अगर (!(अगरile->i_state & I_NEW))
		जाओ out;

	err = nilfs_mdt_init(अगरile, NILFS_MDT_GFP,
			     माप(काष्ठा nilfs_अगरile_info));
	अगर (err)
		जाओ failed;

	err = nilfs_palloc_init_blockgroup(अगरile, inode_size);
	अगर (err)
		जाओ failed;

	nilfs_palloc_setup_cache(अगरile, &NILFS_Iखाता_I(अगरile)->palloc_cache);

	err = nilfs_पढ़ो_inode_common(अगरile, raw_inode);
	अगर (err)
		जाओ failed;

	unlock_new_inode(अगरile);
 out:
	*inodep = अगरile;
	वापस 0;
 failed:
	iget_failed(अगरile);
	वापस err;
पूर्ण

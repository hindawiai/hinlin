<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * dat.c - NILFS disk address translation.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#समावेश <linux/types.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश "nilfs.h"
#समावेश "mdt.h"
#समावेश "alloc.h"
#समावेश "dat.h"


#घोषणा NILFS_CNO_MIN	((__u64)1)
#घोषणा NILFS_CNO_MAX	(~(__u64)0)

/**
 * काष्ठा nilfs_dat_info - on-memory निजी data of DAT file
 * @mi: on-memory निजी data of metadata file
 * @palloc_cache: persistent object allocator cache of DAT file
 * @shaकरोw: shaकरोw map of DAT file
 */
काष्ठा nilfs_dat_info अणु
	काष्ठा nilfs_mdt_info mi;
	काष्ठा nilfs_palloc_cache palloc_cache;
	काष्ठा nilfs_shaकरोw_map shaकरोw;
पूर्ण;

अटल अंतरभूत काष्ठा nilfs_dat_info *NILFS_DAT_I(काष्ठा inode *dat)
अणु
	वापस (काष्ठा nilfs_dat_info *)NILFS_MDT(dat);
पूर्ण

अटल पूर्णांक nilfs_dat_prepare_entry(काष्ठा inode *dat,
				   काष्ठा nilfs_palloc_req *req, पूर्णांक create)
अणु
	वापस nilfs_palloc_get_entry_block(dat, req->pr_entry_nr,
					    create, &req->pr_entry_bh);
पूर्ण

अटल व्योम nilfs_dat_commit_entry(काष्ठा inode *dat,
				   काष्ठा nilfs_palloc_req *req)
अणु
	mark_buffer_dirty(req->pr_entry_bh);
	nilfs_mdt_mark_dirty(dat);
	brअन्यथा(req->pr_entry_bh);
पूर्ण

अटल व्योम nilfs_dat_पात_entry(काष्ठा inode *dat,
				  काष्ठा nilfs_palloc_req *req)
अणु
	brअन्यथा(req->pr_entry_bh);
पूर्ण

पूर्णांक nilfs_dat_prepare_alloc(काष्ठा inode *dat, काष्ठा nilfs_palloc_req *req)
अणु
	पूर्णांक ret;

	ret = nilfs_palloc_prepare_alloc_entry(dat, req);
	अगर (ret < 0)
		वापस ret;

	ret = nilfs_dat_prepare_entry(dat, req, 1);
	अगर (ret < 0)
		nilfs_palloc_पात_alloc_entry(dat, req);

	वापस ret;
पूर्ण

व्योम nilfs_dat_commit_alloc(काष्ठा inode *dat, काष्ठा nilfs_palloc_req *req)
अणु
	काष्ठा nilfs_dat_entry *entry;
	व्योम *kaddr;

	kaddr = kmap_atomic(req->pr_entry_bh->b_page);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	entry->de_start = cpu_to_le64(NILFS_CNO_MIN);
	entry->de_end = cpu_to_le64(NILFS_CNO_MAX);
	entry->de_blocknr = cpu_to_le64(0);
	kunmap_atomic(kaddr);

	nilfs_palloc_commit_alloc_entry(dat, req);
	nilfs_dat_commit_entry(dat, req);
पूर्ण

व्योम nilfs_dat_पात_alloc(काष्ठा inode *dat, काष्ठा nilfs_palloc_req *req)
अणु
	nilfs_dat_पात_entry(dat, req);
	nilfs_palloc_पात_alloc_entry(dat, req);
पूर्ण

अटल व्योम nilfs_dat_commit_मुक्त(काष्ठा inode *dat,
				  काष्ठा nilfs_palloc_req *req)
अणु
	काष्ठा nilfs_dat_entry *entry;
	व्योम *kaddr;

	kaddr = kmap_atomic(req->pr_entry_bh->b_page);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	entry->de_start = cpu_to_le64(NILFS_CNO_MIN);
	entry->de_end = cpu_to_le64(NILFS_CNO_MIN);
	entry->de_blocknr = cpu_to_le64(0);
	kunmap_atomic(kaddr);

	nilfs_dat_commit_entry(dat, req);
	nilfs_palloc_commit_मुक्त_entry(dat, req);
पूर्ण

पूर्णांक nilfs_dat_prepare_start(काष्ठा inode *dat, काष्ठा nilfs_palloc_req *req)
अणु
	पूर्णांक ret;

	ret = nilfs_dat_prepare_entry(dat, req, 0);
	WARN_ON(ret == -ENOENT);
	वापस ret;
पूर्ण

व्योम nilfs_dat_commit_start(काष्ठा inode *dat, काष्ठा nilfs_palloc_req *req,
			    sector_t blocknr)
अणु
	काष्ठा nilfs_dat_entry *entry;
	व्योम *kaddr;

	kaddr = kmap_atomic(req->pr_entry_bh->b_page);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	entry->de_start = cpu_to_le64(nilfs_mdt_cno(dat));
	entry->de_blocknr = cpu_to_le64(blocknr);
	kunmap_atomic(kaddr);

	nilfs_dat_commit_entry(dat, req);
पूर्ण

पूर्णांक nilfs_dat_prepare_end(काष्ठा inode *dat, काष्ठा nilfs_palloc_req *req)
अणु
	काष्ठा nilfs_dat_entry *entry;
	sector_t blocknr;
	व्योम *kaddr;
	पूर्णांक ret;

	ret = nilfs_dat_prepare_entry(dat, req, 0);
	अगर (ret < 0) अणु
		WARN_ON(ret == -ENOENT);
		वापस ret;
	पूर्ण

	kaddr = kmap_atomic(req->pr_entry_bh->b_page);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	blocknr = le64_to_cpu(entry->de_blocknr);
	kunmap_atomic(kaddr);

	अगर (blocknr == 0) अणु
		ret = nilfs_palloc_prepare_मुक्त_entry(dat, req);
		अगर (ret < 0) अणु
			nilfs_dat_पात_entry(dat, req);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम nilfs_dat_commit_end(काष्ठा inode *dat, काष्ठा nilfs_palloc_req *req,
			  पूर्णांक dead)
अणु
	काष्ठा nilfs_dat_entry *entry;
	__u64 start, end;
	sector_t blocknr;
	व्योम *kaddr;

	kaddr = kmap_atomic(req->pr_entry_bh->b_page);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	end = start = le64_to_cpu(entry->de_start);
	अगर (!dead) अणु
		end = nilfs_mdt_cno(dat);
		WARN_ON(start > end);
	पूर्ण
	entry->de_end = cpu_to_le64(end);
	blocknr = le64_to_cpu(entry->de_blocknr);
	kunmap_atomic(kaddr);

	अगर (blocknr == 0)
		nilfs_dat_commit_मुक्त(dat, req);
	अन्यथा
		nilfs_dat_commit_entry(dat, req);
पूर्ण

व्योम nilfs_dat_पात_end(काष्ठा inode *dat, काष्ठा nilfs_palloc_req *req)
अणु
	काष्ठा nilfs_dat_entry *entry;
	__u64 start;
	sector_t blocknr;
	व्योम *kaddr;

	kaddr = kmap_atomic(req->pr_entry_bh->b_page);
	entry = nilfs_palloc_block_get_entry(dat, req->pr_entry_nr,
					     req->pr_entry_bh, kaddr);
	start = le64_to_cpu(entry->de_start);
	blocknr = le64_to_cpu(entry->de_blocknr);
	kunmap_atomic(kaddr);

	अगर (start == nilfs_mdt_cno(dat) && blocknr == 0)
		nilfs_palloc_पात_मुक्त_entry(dat, req);
	nilfs_dat_पात_entry(dat, req);
पूर्ण

पूर्णांक nilfs_dat_prepare_update(काष्ठा inode *dat,
			     काष्ठा nilfs_palloc_req *oldreq,
			     काष्ठा nilfs_palloc_req *newreq)
अणु
	पूर्णांक ret;

	ret = nilfs_dat_prepare_end(dat, oldreq);
	अगर (!ret) अणु
		ret = nilfs_dat_prepare_alloc(dat, newreq);
		अगर (ret < 0)
			nilfs_dat_पात_end(dat, oldreq);
	पूर्ण
	वापस ret;
पूर्ण

व्योम nilfs_dat_commit_update(काष्ठा inode *dat,
			     काष्ठा nilfs_palloc_req *oldreq,
			     काष्ठा nilfs_palloc_req *newreq, पूर्णांक dead)
अणु
	nilfs_dat_commit_end(dat, oldreq, dead);
	nilfs_dat_commit_alloc(dat, newreq);
पूर्ण

व्योम nilfs_dat_पात_update(काष्ठा inode *dat,
			    काष्ठा nilfs_palloc_req *oldreq,
			    काष्ठा nilfs_palloc_req *newreq)
अणु
	nilfs_dat_पात_end(dat, oldreq);
	nilfs_dat_पात_alloc(dat, newreq);
पूर्ण

/**
 * nilfs_dat_mark_dirty -
 * @dat: DAT file inode
 * @vblocknr: भव block number
 *
 * Description:
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_dat_mark_dirty(काष्ठा inode *dat, __u64 vblocknr)
अणु
	काष्ठा nilfs_palloc_req req;
	पूर्णांक ret;

	req.pr_entry_nr = vblocknr;
	ret = nilfs_dat_prepare_entry(dat, &req, 0);
	अगर (ret == 0)
		nilfs_dat_commit_entry(dat, &req);
	वापस ret;
पूर्ण

/**
 * nilfs_dat_मुक्तv - मुक्त भव block numbers
 * @dat: DAT file inode
 * @vblocknrs: array of भव block numbers
 * @nitems: number of भव block numbers
 *
 * Description: nilfs_dat_मुक्तv() मुक्तs the भव block numbers specअगरied by
 * @vblocknrs and @nitems.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - The भव block number have not been allocated.
 */
पूर्णांक nilfs_dat_मुक्तv(काष्ठा inode *dat, __u64 *vblocknrs, माप_प्रकार nitems)
अणु
	वापस nilfs_palloc_मुक्तv(dat, vblocknrs, nitems);
पूर्ण

/**
 * nilfs_dat_move - change a block number
 * @dat: DAT file inode
 * @vblocknr: भव block number
 * @blocknr: block number
 *
 * Description: nilfs_dat_move() changes the block number associated with
 * @vblocknr to @blocknr.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_dat_move(काष्ठा inode *dat, __u64 vblocknr, sector_t blocknr)
अणु
	काष्ठा buffer_head *entry_bh;
	काष्ठा nilfs_dat_entry *entry;
	व्योम *kaddr;
	पूर्णांक ret;

	ret = nilfs_palloc_get_entry_block(dat, vblocknr, 0, &entry_bh);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The given disk block number (blocknr) is not yet written to
	 * the device at this poपूर्णांक.
	 *
	 * To prevent nilfs_dat_translate() from वापसing the
	 * uncommitted block number, this makes a copy of the entry
	 * buffer and redirects nilfs_dat_translate() to the copy.
	 */
	अगर (!buffer_nilfs_redirected(entry_bh)) अणु
		ret = nilfs_mdt_मुक्तze_buffer(dat, entry_bh);
		अगर (ret) अणु
			brअन्यथा(entry_bh);
			वापस ret;
		पूर्ण
	पूर्ण

	kaddr = kmap_atomic(entry_bh->b_page);
	entry = nilfs_palloc_block_get_entry(dat, vblocknr, entry_bh, kaddr);
	अगर (unlikely(entry->de_blocknr == cpu_to_le64(0))) अणु
		nilfs_crit(dat->i_sb,
			   "%s: invalid vblocknr = %llu, [%llu, %llu)",
			   __func__, (अचिन्हित दीर्घ दीर्घ)vblocknr,
			   (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(entry->de_start),
			   (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(entry->de_end));
		kunmap_atomic(kaddr);
		brअन्यथा(entry_bh);
		वापस -EINVAL;
	पूर्ण
	WARN_ON(blocknr == 0);
	entry->de_blocknr = cpu_to_le64(blocknr);
	kunmap_atomic(kaddr);

	mark_buffer_dirty(entry_bh);
	nilfs_mdt_mark_dirty(dat);

	brअन्यथा(entry_bh);

	वापस 0;
पूर्ण

/**
 * nilfs_dat_translate - translate a भव block number to a block number
 * @dat: DAT file inode
 * @vblocknr: भव block number
 * @blocknrp: poपूर्णांकer to a block number
 *
 * Description: nilfs_dat_translate() maps the भव block number @vblocknr
 * to the corresponding block number.
 *
 * Return Value: On success, 0 is वापसed and the block number associated
 * with @vblocknr is stored in the place poपूर्णांकed by @blocknrp. On error, one
 * of the following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - A block number associated with @vblocknr करोes not exist.
 */
पूर्णांक nilfs_dat_translate(काष्ठा inode *dat, __u64 vblocknr, sector_t *blocknrp)
अणु
	काष्ठा buffer_head *entry_bh, *bh;
	काष्ठा nilfs_dat_entry *entry;
	sector_t blocknr;
	व्योम *kaddr;
	पूर्णांक ret;

	ret = nilfs_palloc_get_entry_block(dat, vblocknr, 0, &entry_bh);
	अगर (ret < 0)
		वापस ret;

	अगर (!nilfs_करोing_gc() && buffer_nilfs_redirected(entry_bh)) अणु
		bh = nilfs_mdt_get_frozen_buffer(dat, entry_bh);
		अगर (bh) अणु
			WARN_ON(!buffer_uptodate(bh));
			brअन्यथा(entry_bh);
			entry_bh = bh;
		पूर्ण
	पूर्ण

	kaddr = kmap_atomic(entry_bh->b_page);
	entry = nilfs_palloc_block_get_entry(dat, vblocknr, entry_bh, kaddr);
	blocknr = le64_to_cpu(entry->de_blocknr);
	अगर (blocknr == 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	*blocknrp = blocknr;

 out:
	kunmap_atomic(kaddr);
	brअन्यथा(entry_bh);
	वापस ret;
पूर्ण

sमाप_प्रकार nilfs_dat_get_vinfo(काष्ठा inode *dat, व्योम *buf, अचिन्हित पूर्णांक visz,
			    माप_प्रकार nvi)
अणु
	काष्ठा buffer_head *entry_bh;
	काष्ठा nilfs_dat_entry *entry;
	काष्ठा nilfs_vinfo *vinfo = buf;
	__u64 first, last;
	व्योम *kaddr;
	अचिन्हित दीर्घ entries_per_block = NILFS_MDT(dat)->mi_entries_per_block;
	पूर्णांक i, j, n, ret;

	क्रम (i = 0; i < nvi; i += n) अणु
		ret = nilfs_palloc_get_entry_block(dat, vinfo->vi_vblocknr,
						   0, &entry_bh);
		अगर (ret < 0)
			वापस ret;
		kaddr = kmap_atomic(entry_bh->b_page);
		/* last भव block number in this block */
		first = vinfo->vi_vblocknr;
		करो_भाग(first, entries_per_block);
		first *= entries_per_block;
		last = first + entries_per_block - 1;
		क्रम (j = i, n = 0;
		     j < nvi && vinfo->vi_vblocknr >= first &&
			     vinfo->vi_vblocknr <= last;
		     j++, n++, vinfo = (व्योम *)vinfo + visz) अणु
			entry = nilfs_palloc_block_get_entry(
				dat, vinfo->vi_vblocknr, entry_bh, kaddr);
			vinfo->vi_start = le64_to_cpu(entry->de_start);
			vinfo->vi_end = le64_to_cpu(entry->de_end);
			vinfo->vi_blocknr = le64_to_cpu(entry->de_blocknr);
		पूर्ण
		kunmap_atomic(kaddr);
		brअन्यथा(entry_bh);
	पूर्ण

	वापस nvi;
पूर्ण

/**
 * nilfs_dat_पढ़ो - पढ़ो or get dat inode
 * @sb: super block instance
 * @entry_size: size of a dat entry
 * @raw_inode: on-disk dat inode
 * @inodep: buffer to store the inode
 */
पूर्णांक nilfs_dat_पढ़ो(काष्ठा super_block *sb, माप_प्रकार entry_size,
		   काष्ठा nilfs_inode *raw_inode, काष्ठा inode **inodep)
अणु
	अटल काष्ठा lock_class_key dat_lock_key;
	काष्ठा inode *dat;
	काष्ठा nilfs_dat_info *di;
	पूर्णांक err;

	अगर (entry_size > sb->s_blocksize) अणु
		nilfs_err(sb, "too large DAT entry size: %zu bytes",
			  entry_size);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (entry_size < NILFS_MIN_DAT_ENTRY_SIZE) अणु
		nilfs_err(sb, "too small DAT entry size: %zu bytes",
			  entry_size);
		वापस -EINVAL;
	पूर्ण

	dat = nilfs_iget_locked(sb, शून्य, NILFS_DAT_INO);
	अगर (unlikely(!dat))
		वापस -ENOMEM;
	अगर (!(dat->i_state & I_NEW))
		जाओ out;

	err = nilfs_mdt_init(dat, NILFS_MDT_GFP, माप(*di));
	अगर (err)
		जाओ failed;

	err = nilfs_palloc_init_blockgroup(dat, entry_size);
	अगर (err)
		जाओ failed;

	di = NILFS_DAT_I(dat);
	lockdep_set_class(&di->mi.mi_sem, &dat_lock_key);
	nilfs_palloc_setup_cache(dat, &di->palloc_cache);
	nilfs_mdt_setup_shaकरोw_map(dat, &di->shaकरोw);

	err = nilfs_पढ़ो_inode_common(dat, raw_inode);
	अगर (err)
		जाओ failed;

	unlock_new_inode(dat);
 out:
	*inodep = dat;
	वापस 0;
 failed:
	iget_failed(dat);
	वापस err;
पूर्ण

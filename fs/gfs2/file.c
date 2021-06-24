<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/compat.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/mm.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/swap.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/dlm.h>
#समावेश <linux/dlm_plock.h>
#समावेश <linux/delay.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fileattr.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "aops.h"
#समावेश "dir.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "inode.h"
#समावेश "log.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "rgrp.h"
#समावेश "trans.h"
#समावेश "util.h"

/**
 * gfs2_llseek - seek to a location in a file
 * @file: the file
 * @offset: the offset
 * @whence: Where to seek from (शुरू_से, प्रस्तुत_से, or अंत_से)
 *
 * अंत_से requires the glock क्रम the file because it references the
 * file's size.
 *
 * Returns: The new offset, or त्रुटि_सं
 */

अटल loff_t gfs2_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(file->f_mapping->host);
	काष्ठा gfs2_holder i_gh;
	loff_t error;

	चयन (whence) अणु
	हाल अंत_से:
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY,
					   &i_gh);
		अगर (!error) अणु
			error = generic_file_llseek(file, offset, whence);
			gfs2_glock_dq_uninit(&i_gh);
		पूर्ण
		अवरोध;

	हाल SEEK_DATA:
		error = gfs2_seek_data(file, offset);
		अवरोध;

	हाल SEEK_HOLE:
		error = gfs2_seek_hole(file, offset);
		अवरोध;

	हाल प्रस्तुत_से:
	हाल शुरू_से:
		/*
		 * These करोn't reference inode->i_size and don't depend on the
		 * block mapping, so we करोn't need the glock.
		 */
		error = generic_file_llseek(file, offset, whence);
		अवरोध;
	शेष:
		error = -EINVAL;
	पूर्ण

	वापस error;
पूर्ण

/**
 * gfs2_सूची_पढ़ो - Iterator क्रम a directory
 * @file: The directory to पढ़ो from
 * @ctx: What to feed directory entries to
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *dir = file->f_mapping->host;
	काष्ठा gfs2_inode *dip = GFS2_I(dir);
	काष्ठा gfs2_holder d_gh;
	पूर्णांक error;

	error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, &d_gh);
	अगर (error)
		वापस error;

	error = gfs2_dir_पढ़ो(dir, ctx, &file->f_ra);

	gfs2_glock_dq_uninit(&d_gh);

	वापस error;
पूर्ण

/*
 * काष्ठा fsflag_gfs2flag
 *
 * The FS_JOURNAL_DATA_FL flag maps to GFS2_DIF_INHERIT_JDATA क्रम directories,
 * and to GFS2_DIF_JDATA क्रम non-directories.
 */
अटल काष्ठा अणु
	u32 fsflag;
	u32 gfsflag;
पूर्ण fsflag_gfs2flag[] = अणु
	अणुFS_SYNC_FL, GFS2_DIF_SYNCपूर्ण,
	अणुFS_IMMUTABLE_FL, GFS2_DIF_IMMUTABLEपूर्ण,
	अणुFS_APPEND_FL, GFS2_DIF_APPENDONLYपूर्ण,
	अणुFS_NOATIME_FL, GFS2_DIF_NOATIMEपूर्ण,
	अणुFS_INDEX_FL, GFS2_DIF_EXHASHपूर्ण,
	अणुFS_TOPसूची_FL, GFS2_DIF_TOPसूचीपूर्ण,
	अणुFS_JOURNAL_DATA_FL, GFS2_DIF_JDATA | GFS2_DIF_INHERIT_JDATAपूर्ण,
पूर्ण;

अटल अंतरभूत u32 gfs2_gfsflags_to_fsflags(काष्ठा inode *inode, u32 gfsflags)
अणु
	पूर्णांक i;
	u32 fsflags = 0;

	अगर (S_ISसूची(inode->i_mode))
		gfsflags &= ~GFS2_DIF_JDATA;
	अन्यथा
		gfsflags &= ~GFS2_DIF_INHERIT_JDATA;

	क्रम (i = 0; i < ARRAY_SIZE(fsflag_gfs2flag); i++)
		अगर (gfsflags & fsflag_gfs2flag[i].gfsflag)
			fsflags |= fsflag_gfs2flag[i].fsflag;
	वापस fsflags;
पूर्ण

पूर्णांक gfs2_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	पूर्णांक error;
	u32 fsflags;

	अगर (d_is_special(dentry))
		वापस -ENOTTY;

	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	error = gfs2_glock_nq(&gh);
	अगर (error)
		जाओ out_uninit;

	fsflags = gfs2_gfsflags_to_fsflags(inode, ip->i_diskflags);

	fileattr_fill_flags(fa, fsflags);

	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	वापस error;
पूर्ण

व्योम gfs2_set_inode_flags(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	अचिन्हित पूर्णांक flags = inode->i_flags;

	flags &= ~(S_SYNC|S_APPEND|S_IMMUTABLE|S_NOATIME|S_सूचीSYNC|S_NOSEC);
	अगर ((ip->i_eattr == 0) && !is_sxid(inode->i_mode))
		flags |= S_NOSEC;
	अगर (ip->i_diskflags & GFS2_DIF_IMMUTABLE)
		flags |= S_IMMUTABLE;
	अगर (ip->i_diskflags & GFS2_DIF_APPENDONLY)
		flags |= S_APPEND;
	अगर (ip->i_diskflags & GFS2_DIF_NOATIME)
		flags |= S_NOATIME;
	अगर (ip->i_diskflags & GFS2_DIF_SYNC)
		flags |= S_SYNC;
	inode->i_flags = flags;
पूर्ण

/* Flags that can be set by user space */
#घोषणा GFS2_FLAGS_USER_SET (GFS2_DIF_JDATA|			\
			     GFS2_DIF_IMMUTABLE|		\
			     GFS2_DIF_APPENDONLY|		\
			     GFS2_DIF_NOATIME|			\
			     GFS2_DIF_SYNC|			\
			     GFS2_DIF_TOPसूची|			\
			     GFS2_DIF_INHERIT_JDATA)

/**
 * करो_gfs2_set_flags - set flags on an inode
 * @filp: file poपूर्णांकer
 * @reqflags: The flags to set
 * @mask: Indicates which flags are valid
 * @fsflags: The FS_* inode flags passed in
 *
 */
अटल पूर्णांक करो_gfs2_set_flags(काष्ठा inode *inode, u32 reqflags, u32 mask,
			     स्थिर u32 fsflags)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_holder gh;
	पूर्णांक error;
	u32 new_flags, flags;

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
	अगर (error)
		वापस error;

	error = 0;
	flags = ip->i_diskflags;
	new_flags = (flags & ~mask) | (reqflags & mask);
	अगर ((new_flags ^ flags) == 0)
		जाओ out;

	error = -EPERM;
	अगर (IS_IMMUTABLE(inode) && (new_flags & GFS2_DIF_IMMUTABLE))
		जाओ out;
	अगर (IS_APPEND(inode) && (new_flags & GFS2_DIF_APPENDONLY))
		जाओ out;
	अगर (!IS_IMMUTABLE(inode)) अणु
		error = gfs2_permission(&init_user_ns, inode, MAY_WRITE);
		अगर (error)
			जाओ out;
	पूर्ण
	अगर ((flags ^ new_flags) & GFS2_DIF_JDATA) अणु
		अगर (new_flags & GFS2_DIF_JDATA)
			gfs2_log_flush(sdp, ip->i_gl,
				       GFS2_LOG_HEAD_FLUSH_NORMAL |
				       GFS2_LFC_SET_FLAGS);
		error = filemap_fdataग_लिखो(inode->i_mapping);
		अगर (error)
			जाओ out;
		error = filemap_fdataरुको(inode->i_mapping);
		अगर (error)
			जाओ out;
		अगर (new_flags & GFS2_DIF_JDATA)
			gfs2_ordered_del_inode(ip);
	पूर्ण
	error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	अगर (error)
		जाओ out;
	error = gfs2_meta_inode_buffer(ip, &bh);
	अगर (error)
		जाओ out_trans_end;
	inode->i_स_समय = current_समय(inode);
	gfs2_trans_add_meta(ip->i_gl, bh);
	ip->i_diskflags = new_flags;
	gfs2_dinode_out(ip, bh->b_data);
	brअन्यथा(bh);
	gfs2_set_inode_flags(inode);
	gfs2_set_aops(inode);
out_trans_end:
	gfs2_trans_end(sdp);
out:
	gfs2_glock_dq_uninit(&gh);
	वापस error;
पूर्ण

पूर्णांक gfs2_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	u32 fsflags = fa->flags, gfsflags = 0;
	u32 mask;
	पूर्णांक i;

	अगर (d_is_special(dentry))
		वापस -ENOTTY;

	अगर (fileattr_has_fsx(fa))
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i < ARRAY_SIZE(fsflag_gfs2flag); i++) अणु
		अगर (fsflags & fsflag_gfs2flag[i].fsflag) अणु
			fsflags &= ~fsflag_gfs2flag[i].fsflag;
			gfsflags |= fsflag_gfs2flag[i].gfsflag;
		पूर्ण
	पूर्ण
	अगर (fsflags || gfsflags & ~GFS2_FLAGS_USER_SET)
		वापस -EINVAL;

	mask = GFS2_FLAGS_USER_SET;
	अगर (S_ISसूची(inode->i_mode)) अणु
		mask &= ~GFS2_DIF_JDATA;
	पूर्ण अन्यथा अणु
		/* The GFS2_DIF_TOPसूची flag is only valid क्रम directories. */
		अगर (gfsflags & GFS2_DIF_TOPसूची)
			वापस -EINVAL;
		mask &= ~(GFS2_DIF_TOPसूची | GFS2_DIF_INHERIT_JDATA);
	पूर्ण

	वापस करो_gfs2_set_flags(inode, gfsflags, mask, fsflags);
पूर्ण

अटल पूर्णांक gfs2_getlabel(काष्ठा file *filp, अक्षर __user *label)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);

	अगर (copy_to_user(label, sdp->sd_sb.sb_locktable, GFS2_LOCKNAME_LEN))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ gfs2_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन(cmd) अणु
	हाल FITRIM:
		वापस gfs2_fitrim(filp, (व्योम __user *)arg);
	हाल FS_IOC_GETFSLABEL:
		वापस gfs2_getlabel(filp, (अक्षर __user *)arg);
	पूर्ण

	वापस -ENOTTY;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ gfs2_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन(cmd) अणु
	/* Keep this list in sync with gfs2_ioctl */
	हाल FITRIM:
	हाल FS_IOC_GETFSLABEL:
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस gfs2_ioctl(filp, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा gfs2_compat_ioctl शून्य
#पूर्ण_अगर

/**
 * gfs2_size_hपूर्णांक - Give a hपूर्णांक to the size of a ग_लिखो request
 * @filep: The काष्ठा file
 * @offset: The file offset of the ग_लिखो
 * @size: The length of the ग_लिखो
 *
 * When we are about to करो a ग_लिखो, this function records the total
 * ग_लिखो size in order to provide a suitable hपूर्णांक to the lower layers
 * about how many blocks will be required.
 *
 */

अटल व्योम gfs2_size_hपूर्णांक(काष्ठा file *filep, loff_t offset, माप_प्रकार size)
अणु
	काष्ठा inode *inode = file_inode(filep);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	माप_प्रकार blks = (size + sdp->sd_sb.sb_bsize - 1) >> sdp->sd_sb.sb_bsize_shअगरt;
	पूर्णांक hपूर्णांक = min_t(माप_प्रकार, पूर्णांक_उच्च, blks);

	अगर (hपूर्णांक > atomic_पढ़ो(&ip->i_sizehपूर्णांक))
		atomic_set(&ip->i_sizehपूर्णांक, hपूर्णांक);
पूर्ण

/**
 * gfs2_allocate_page_backing - Allocate blocks क्रम a ग_लिखो fault
 * @page: The (locked) page to allocate backing क्रम
 * @length: Size of the allocation
 *
 * We try to allocate all the blocks required क्रम the page in one go.  This
 * might fail क्रम various reasons, so we keep trying until all the blocks to
 * back this page are allocated.  If some of the blocks are alपढ़ोy allocated,
 * that is ok too.
 */
अटल पूर्णांक gfs2_allocate_page_backing(काष्ठा page *page, अचिन्हित पूर्णांक length)
अणु
	u64 pos = page_offset(page);

	करो अणु
		काष्ठा iomap iomap = अणु पूर्ण;

		अगर (gfs2_iomap_alloc(page->mapping->host, pos, length, &iomap))
			वापस -EIO;

		अगर (length < iomap.length)
			iomap.length = length;
		length -= iomap.length;
		pos += iomap.length;
	पूर्ण जबतक (length > 0);

	वापस 0;
पूर्ण

/**
 * gfs2_page_mkग_लिखो - Make a shared, mmap()ed, page writable
 * @vmf: The भव memory fault containing the page to become writable
 *
 * When the page becomes writable, we need to ensure that we have
 * blocks allocated on disk to back that page.
 */

अटल vm_fault_t gfs2_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_alloc_parms ap = अणु .aflags = 0, पूर्ण;
	u64 offset = page_offset(page);
	अचिन्हित पूर्णांक data_blocks, ind_blocks, rblocks;
	काष्ठा gfs2_holder gh;
	अचिन्हित पूर्णांक length;
	loff_t size;
	पूर्णांक ret;

	sb_start_pagefault(inode->i_sb);

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
	ret = gfs2_glock_nq(&gh);
	अगर (ret)
		जाओ out_uninit;

	/* Check page index against inode size */
	size = i_size_पढ़ो(inode);
	अगर (offset >= size) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* Update file बार beक्रमe taking page lock */
	file_update_समय(vmf->vma->vm_file);

	/* page is wholly or partially inside खातापूर्ण */
	अगर (offset > size - PAGE_SIZE)
		length = offset_in_page(size);
	अन्यथा
		length = PAGE_SIZE;

	gfs2_size_hपूर्णांक(vmf->vma->vm_file, offset, length);

	set_bit(GLF_सूचीTY, &ip->i_gl->gl_flags);
	set_bit(GIF_SW_PAGED, &ip->i_flags);

	/*
	 * iomap_ग_लिखोpage / iomap_ग_लिखोpages currently करोn't support अंतरभूत
	 * files, so always unstuff here.
	 */

	अगर (!gfs2_is_stuffed(ip) &&
	    !gfs2_ग_लिखो_alloc_required(ip, offset, length)) अणु
		lock_page(page);
		अगर (!PageUptodate(page) || page->mapping != inode->i_mapping) अणु
			ret = -EAGAIN;
			unlock_page(page);
		पूर्ण
		जाओ out_unlock;
	पूर्ण

	ret = gfs2_rindex_update(sdp);
	अगर (ret)
		जाओ out_unlock;

	gfs2_ग_लिखो_calc_reserv(ip, length, &data_blocks, &ind_blocks);
	ap.target = data_blocks + ind_blocks;
	ret = gfs2_quota_lock_check(ip, &ap);
	अगर (ret)
		जाओ out_unlock;
	ret = gfs2_inplace_reserve(ip, &ap);
	अगर (ret)
		जाओ out_quota_unlock;

	rblocks = RES_DINODE + ind_blocks;
	अगर (gfs2_is_jdata(ip))
		rblocks += data_blocks ? data_blocks : 1;
	अगर (ind_blocks || data_blocks) अणु
		rblocks += RES_STATFS + RES_QUOTA;
		rblocks += gfs2_rg_blocks(ip, data_blocks + ind_blocks);
	पूर्ण
	ret = gfs2_trans_begin(sdp, rblocks, 0);
	अगर (ret)
		जाओ out_trans_fail;

	lock_page(page);
	ret = -EAGAIN;
	/* If truncated, we must retry the operation, we may have raced
	 * with the glock demotion code.
	 */
	अगर (!PageUptodate(page) || page->mapping != inode->i_mapping)
		जाओ out_trans_end;

	/* Unstuff, अगर required, and allocate backing blocks क्रम page */
	ret = 0;
	अगर (gfs2_is_stuffed(ip))
		ret = gfs2_unstuff_dinode(ip, page);
	अगर (ret == 0)
		ret = gfs2_allocate_page_backing(page, length);

out_trans_end:
	अगर (ret)
		unlock_page(page);
	gfs2_trans_end(sdp);
out_trans_fail:
	gfs2_inplace_release(ip);
out_quota_unlock:
	gfs2_quota_unlock(ip);
out_unlock:
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	अगर (ret == 0) अणु
		set_page_dirty(page);
		रुको_क्रम_stable_page(page);
	पूर्ण
	sb_end_pagefault(inode->i_sb);
	वापस block_page_mkग_लिखो_वापस(ret);
पूर्ण

अटल vm_fault_t gfs2_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	vm_fault_t ret;
	पूर्णांक err;

	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	err = gfs2_glock_nq(&gh);
	अगर (err) अणु
		ret = block_page_mkग_लिखो_वापस(err);
		जाओ out_uninit;
	पूर्ण
	ret = filemap_fault(vmf);
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा gfs2_vm_ops = अणु
	.fault = gfs2_fault,
	.map_pages = filemap_map_pages,
	.page_mkग_लिखो = gfs2_page_mkग_लिखो,
पूर्ण;

/**
 * gfs2_mmap
 * @file: The file to map
 * @vma: The VMA which described the mapping
 *
 * There is no need to get a lock here unless we should be updating
 * aसमय. We ignore any locking errors since the only consequence is
 * a missed aसमय update (which will just be deferred until later).
 *
 * Returns: 0
 */

अटल पूर्णांक gfs2_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(file->f_mapping->host);

	अगर (!(file->f_flags & O_NOATIME) &&
	    !IS_NOATIME(&ip->i_inode)) अणु
		काष्ठा gfs2_holder i_gh;
		पूर्णांक error;

		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY,
					   &i_gh);
		अगर (error)
			वापस error;
		/* grab lock to update inode */
		gfs2_glock_dq_uninit(&i_gh);
		file_accessed(file);
	पूर्ण
	vma->vm_ops = &gfs2_vm_ops;

	वापस 0;
पूर्ण

/**
 * gfs2_खोलो_common - This is common to खोलो and atomic_खोलो
 * @inode: The inode being खोलोed
 * @file: The file being खोलोed
 *
 * This maybe called under a glock or not depending upon how it has
 * been called. We must always be called under a glock क्रम regular
 * files, however. For other file types, it करोes not matter whether
 * we hold the glock or not.
 *
 * Returns: Error code or 0 क्रम success
 */

पूर्णांक gfs2_खोलो_common(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gfs2_file *fp;
	पूर्णांक ret;

	अगर (S_ISREG(inode->i_mode)) अणु
		ret = generic_file_खोलो(inode, file);
		अगर (ret)
			वापस ret;
	पूर्ण

	fp = kzalloc(माप(काष्ठा gfs2_file), GFP_NOFS);
	अगर (!fp)
		वापस -ENOMEM;

	mutex_init(&fp->f_fl_mutex);

	gfs2_निश्चित_warn(GFS2_SB(inode), !file->निजी_data);
	file->निजी_data = fp;
	अगर (file->f_mode & FMODE_WRITE) अणु
		ret = gfs2_qa_get(GFS2_I(inode));
		अगर (ret)
			जाओ fail;
	पूर्ण
	वापस 0;

fail:
	kमुक्त(file->निजी_data);
	file->निजी_data = शून्य;
	वापस ret;
पूर्ण

/**
 * gfs2_खोलो - खोलो a file
 * @inode: the inode to खोलो
 * @file: the काष्ठा file क्रम this खोलोing
 *
 * After atomic_खोलो, this function is only used क्रम खोलोing files
 * which are alपढ़ोy cached. We must still get the glock क्रम regular
 * files to ensure that we have the file size uptodate क्रम the large
 * file check which is in the common code. That is only an issue क्रम
 * regular files though.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder i_gh;
	पूर्णांक error;
	bool need_unlock = false;

	अगर (S_ISREG(ip->i_inode.i_mode)) अणु
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY,
					   &i_gh);
		अगर (error)
			वापस error;
		need_unlock = true;
	पूर्ण

	error = gfs2_खोलो_common(inode, file);

	अगर (need_unlock)
		gfs2_glock_dq_uninit(&i_gh);

	वापस error;
पूर्ण

/**
 * gfs2_release - called to बंद a काष्ठा file
 * @inode: the inode the काष्ठा file beदीर्घs to
 * @file: the काष्ठा file being बंदd
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);

	kमुक्त(file->निजी_data);
	file->निजी_data = शून्य;

	अगर (gfs2_rs_active(&ip->i_res))
		gfs2_rs_delete(ip, &inode->i_ग_लिखोcount);
	अगर (file->f_mode & FMODE_WRITE)
		gfs2_qa_put(ip);
	वापस 0;
पूर्ण

/**
 * gfs2_fsync - sync the dirty data क्रम a file (across the cluster)
 * @file: the file that poपूर्णांकs to the dentry
 * @start: the start position in the file to sync
 * @end: the end position in the file to sync
 * @datasync: set अगर we can ignore बारtamp changes
 *
 * We split the data flushing here so that we करोn't रुको क्रम the data
 * until after we've also sent the metadata to disk. Note that क्रम
 * data=ordered, we will ग_लिखो & रुको क्रम the data at the log flush
 * stage anyway, so this is unlikely to make much of a dअगरference
 * except in the data=ग_लिखोback हाल.
 *
 * If the fdataग_लिखो fails due to any reason except -EIO, we will
 * जारी the reमुख्यder of the fsync, although we'll still report
 * the error at the end. This is to match filemap_ग_लिखो_and_रुको_range()
 * behaviour.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_fsync(काष्ठा file *file, loff_t start, loff_t end,
		      पूर्णांक datasync)
अणु
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	पूर्णांक sync_state = inode->i_state & I_सूचीTY;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	पूर्णांक ret = 0, ret1 = 0;

	अगर (mapping->nrpages) अणु
		ret1 = filemap_fdataग_लिखो_range(mapping, start, end);
		अगर (ret1 == -EIO)
			वापस ret1;
	पूर्ण

	अगर (!gfs2_is_jdata(ip))
		sync_state &= ~I_सूचीTY_PAGES;
	अगर (datasync)
		sync_state &= ~I_सूचीTY_SYNC;

	अगर (sync_state) अणु
		ret = sync_inode_metadata(inode, 1);
		अगर (ret)
			वापस ret;
		अगर (gfs2_is_jdata(ip))
			ret = file_ग_लिखो_and_रुको(file);
		अगर (ret)
			वापस ret;
		gfs2_ail_flush(ip->i_gl, 1);
	पूर्ण

	अगर (mapping->nrpages)
		ret = file_fdataरुको_range(file, start, end);

	वापस ret ? ret : ret1;
पूर्ण

अटल sमाप_प्रकार gfs2_file_direct_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to,
				     काष्ठा gfs2_holder *gh)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा gfs2_inode *ip = GFS2_I(file->f_mapping->host);
	माप_प्रकार count = iov_iter_count(to);
	sमाप_प्रकार ret;

	अगर (!count)
		वापस 0; /* skip aसमय */

	gfs2_holder_init(ip->i_gl, LM_ST_DEFERRED, 0, gh);
	ret = gfs2_glock_nq(gh);
	अगर (ret)
		जाओ out_uninit;

	ret = iomap_dio_rw(iocb, to, &gfs2_iomap_ops, शून्य, 0);
	gfs2_glock_dq(gh);
out_uninit:
	gfs2_holder_uninit(gh);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार gfs2_file_direct_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from,
				      काष्ठा gfs2_holder *gh)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	माप_प्रकार len = iov_iter_count(from);
	loff_t offset = iocb->ki_pos;
	sमाप_प्रकार ret;

	/*
	 * Deferred lock, even अगर its a ग_लिखो, since we करो no allocation on
	 * this path. All we need to change is the aसमय, and this lock mode
	 * ensures that other nodes have flushed their buffered पढ़ो caches
	 * (i.e. their page cache entries क्रम this inode). We करो not,
	 * unक्रमtunately, have the option of only flushing a range like the
	 * VFS करोes.
	 */
	gfs2_holder_init(ip->i_gl, LM_ST_DEFERRED, 0, gh);
	ret = gfs2_glock_nq(gh);
	अगर (ret)
		जाओ out_uninit;

	/* Silently fall back to buffered I/O when writing beyond खातापूर्ण */
	अगर (offset + len > i_size_पढ़ो(&ip->i_inode))
		जाओ out;

	ret = iomap_dio_rw(iocb, from, &gfs2_iomap_ops, शून्य, 0);
	अगर (ret == -ENOTBLK)
		ret = 0;
out:
	gfs2_glock_dq(gh);
out_uninit:
	gfs2_holder_uninit(gh);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार gfs2_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा gfs2_inode *ip;
	काष्ठा gfs2_holder gh;
	माप_प्रकार written = 0;
	sमाप_प्रकार ret;

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		ret = gfs2_file_direct_पढ़ो(iocb, to, &gh);
		अगर (likely(ret != -ENOTBLK))
			वापस ret;
		iocb->ki_flags &= ~IOCB_सूचीECT;
	पूर्ण
	iocb->ki_flags |= IOCB_NOIO;
	ret = generic_file_पढ़ो_iter(iocb, to);
	iocb->ki_flags &= ~IOCB_NOIO;
	अगर (ret >= 0) अणु
		अगर (!iov_iter_count(to))
			वापस ret;
		written = ret;
	पूर्ण अन्यथा अणु
		अगर (ret != -EAGAIN)
			वापस ret;
		अगर (iocb->ki_flags & IOCB_NOWAIT)
			वापस ret;
	पूर्ण
	ip = GFS2_I(iocb->ki_filp->f_mapping->host);
	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	ret = gfs2_glock_nq(&gh);
	अगर (ret)
		जाओ out_uninit;
	ret = generic_file_पढ़ो_iter(iocb, to);
	अगर (ret > 0)
		written += ret;
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	वापस written ? written : ret;
पूर्ण

/**
 * gfs2_file_ग_लिखो_iter - Perक्रमm a ग_लिखो to a file
 * @iocb: The io context
 * @from: The data to ग_लिखो
 *
 * We have to करो a lock/unlock here to refresh the inode size क्रम
 * O_APPEND ग_लिखोs, otherwise we can land up writing at the wrong
 * offset. There is still a race, but provided the app is using its
 * own file locking, this will make O_APPEND work as expected.
 *
 */

अटल sमाप_प्रकार gfs2_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	sमाप_प्रकार ret;

	gfs2_size_hपूर्णांक(file, iocb->ki_pos, iov_iter_count(from));

	अगर (iocb->ki_flags & IOCB_APPEND) अणु
		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
		अगर (ret)
			वापस ret;
		gfs2_glock_dq_uninit(&gh);
	पूर्ण

	inode_lock(inode);
	ret = generic_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0)
		जाओ out_unlock;

	ret = file_हटाओ_privs(file);
	अगर (ret)
		जाओ out_unlock;

	ret = file_update_समय(file);
	अगर (ret)
		जाओ out_unlock;

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		काष्ठा address_space *mapping = file->f_mapping;
		sमाप_प्रकार buffered, ret2;

		ret = gfs2_file_direct_ग_लिखो(iocb, from, &gh);
		अगर (ret < 0 || !iov_iter_count(from))
			जाओ out_unlock;

		iocb->ki_flags |= IOCB_DSYNC;
		current->backing_dev_info = inode_to_bdi(inode);
		buffered = iomap_file_buffered_ग_लिखो(iocb, from, &gfs2_iomap_ops);
		current->backing_dev_info = शून्य;
		अगर (unlikely(buffered <= 0)) अणु
			अगर (!ret)
				ret = buffered;
			जाओ out_unlock;
		पूर्ण

		/*
		 * We need to ensure that the page cache pages are written to
		 * disk and invalidated to preserve the expected O_सूचीECT
		 * semantics.  If the ग_लिखोback or invalidate fails, only report
		 * the direct I/O range as we करोn't know अगर the buffered pages
		 * made it to disk.
		 */
		iocb->ki_pos += buffered;
		ret2 = generic_ग_लिखो_sync(iocb, buffered);
		invalidate_mapping_pages(mapping,
				(iocb->ki_pos - buffered) >> PAGE_SHIFT,
				(iocb->ki_pos - 1) >> PAGE_SHIFT);
		अगर (!ret || ret2 > 0)
			ret += ret2;
	पूर्ण अन्यथा अणु
		current->backing_dev_info = inode_to_bdi(inode);
		ret = iomap_file_buffered_ग_लिखो(iocb, from, &gfs2_iomap_ops);
		current->backing_dev_info = शून्य;
		अगर (likely(ret > 0)) अणु
			iocb->ki_pos += ret;
			ret = generic_ग_लिखो_sync(iocb, ret);
		पूर्ण
	पूर्ण

out_unlock:
	inode_unlock(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक fallocate_chunk(काष्ठा inode *inode, loff_t offset, loff_t len,
			   पूर्णांक mode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	loff_t end = offset + len;
	काष्ठा buffer_head *dibh;
	पूर्णांक error;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (unlikely(error))
		वापस error;

	gfs2_trans_add_meta(ip->i_gl, dibh);

	अगर (gfs2_is_stuffed(ip)) अणु
		error = gfs2_unstuff_dinode(ip, शून्य);
		अगर (unlikely(error))
			जाओ out;
	पूर्ण

	जबतक (offset < end) अणु
		काष्ठा iomap iomap = अणु पूर्ण;

		error = gfs2_iomap_alloc(inode, offset, end - offset, &iomap);
		अगर (error)
			जाओ out;
		offset = iomap.offset + iomap.length;
		अगर (!(iomap.flags & IOMAP_F_NEW))
			जारी;
		error = sb_issue_zeroout(sb, iomap.addr >> inode->i_blkbits,
					 iomap.length >> inode->i_blkbits,
					 GFP_NOFS);
		अगर (error) अणु
			fs_err(GFS2_SB(inode), "Failed to zero data buffers\n");
			जाओ out;
		पूर्ण
	पूर्ण
out:
	brअन्यथा(dibh);
	वापस error;
पूर्ण

/**
 * calc_max_reserv() - Reverse of ग_लिखो_calc_reserv. Given a number of
 *                     blocks, determine how many bytes can be written.
 * @ip:          The inode in question.
 * @len:         Max cap of bytes. What we वापस in *len must be <= this.
 * @data_blocks: Compute and वापस the number of data blocks needed
 * @ind_blocks:  Compute and वापस the number of indirect blocks needed
 * @max_blocks:  The total blocks available to work with.
 *
 * Returns: व्योम, but @len, @data_blocks and @ind_blocks are filled in.
 */
अटल व्योम calc_max_reserv(काष्ठा gfs2_inode *ip, loff_t *len,
			    अचिन्हित पूर्णांक *data_blocks, अचिन्हित पूर्णांक *ind_blocks,
			    अचिन्हित पूर्णांक max_blocks)
अणु
	loff_t max = *len;
	स्थिर काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	अचिन्हित पूर्णांक पंचांगp, max_data = max_blocks - 3 * (sdp->sd_max_height - 1);

	क्रम (पंचांगp = max_data; पंचांगp > sdp->sd_diptrs;) अणु
		पंचांगp = DIV_ROUND_UP(पंचांगp, sdp->sd_inptrs);
		max_data -= पंचांगp;
	पूर्ण

	*data_blocks = max_data;
	*ind_blocks = max_blocks - max_data;
	*len = ((loff_t)max_data - 3) << sdp->sd_sb.sb_bsize_shअगरt;
	अगर (*len > max) अणु
		*len = max;
		gfs2_ग_लिखो_calc_reserv(ip, max, data_blocks, ind_blocks);
	पूर्ण
पूर्ण

अटल दीर्घ __gfs2_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_alloc_parms ap = अणु .aflags = 0, पूर्ण;
	अचिन्हित पूर्णांक data_blocks = 0, ind_blocks = 0, rblocks;
	loff_t bytes, max_bytes, max_blks;
	पूर्णांक error;
	स्थिर loff_t pos = offset;
	स्थिर loff_t count = len;
	loff_t bsize_mask = ~((loff_t)sdp->sd_sb.sb_bsize - 1);
	loff_t next = (offset + len - 1) >> sdp->sd_sb.sb_bsize_shअगरt;
	loff_t max_chunk_size = अच_पूर्णांक_उच्च & bsize_mask;

	next = (next + 1) << sdp->sd_sb.sb_bsize_shअगरt;

	offset &= bsize_mask;

	len = next - offset;
	bytes = sdp->sd_max_rg_data * sdp->sd_sb.sb_bsize / 2;
	अगर (!bytes)
		bytes = अच_पूर्णांक_उच्च;
	bytes &= bsize_mask;
	अगर (bytes == 0)
		bytes = sdp->sd_sb.sb_bsize;

	gfs2_size_hपूर्णांक(file, offset, len);

	gfs2_ग_लिखो_calc_reserv(ip, PAGE_SIZE, &data_blocks, &ind_blocks);
	ap.min_target = data_blocks + ind_blocks;

	जबतक (len > 0) अणु
		अगर (len < bytes)
			bytes = len;
		अगर (!gfs2_ग_लिखो_alloc_required(ip, offset, bytes)) अणु
			len -= bytes;
			offset += bytes;
			जारी;
		पूर्ण

		/* We need to determine how many bytes we can actually
		 * fallocate without exceeding quota or going over the
		 * end of the fs. We start off optimistically by assuming
		 * we can ग_लिखो max_bytes */
		max_bytes = (len > max_chunk_size) ? max_chunk_size : len;

		/* Since max_bytes is most likely a theoretical max, we
		 * calculate a more realistic 'bytes' to serve as a good
		 * starting poपूर्णांक क्रम the number of bytes we may be able
		 * to ग_लिखो */
		gfs2_ग_लिखो_calc_reserv(ip, bytes, &data_blocks, &ind_blocks);
		ap.target = data_blocks + ind_blocks;

		error = gfs2_quota_lock_check(ip, &ap);
		अगर (error)
			वापस error;
		/* ap.allowed tells us how many blocks quota will allow
		 * us to ग_लिखो. Check अगर this reduces max_blks */
		max_blks = अच_पूर्णांक_उच्च;
		अगर (ap.allowed)
			max_blks = ap.allowed;

		error = gfs2_inplace_reserve(ip, &ap);
		अगर (error)
			जाओ out_qunlock;

		/* check अगर the selected rgrp limits our max_blks further */
		अगर (ip->i_res.rs_reserved < max_blks)
			max_blks = ip->i_res.rs_reserved;

		/* Almost करोne. Calculate bytes that can be written using
		 * max_blks. We also recompute max_bytes, data_blocks and
		 * ind_blocks */
		calc_max_reserv(ip, &max_bytes, &data_blocks,
				&ind_blocks, max_blks);

		rblocks = RES_DINODE + ind_blocks + RES_STATFS + RES_QUOTA +
			  RES_RG_HDR + gfs2_rg_blocks(ip, data_blocks + ind_blocks);
		अगर (gfs2_is_jdata(ip))
			rblocks += data_blocks ? data_blocks : 1;

		error = gfs2_trans_begin(sdp, rblocks,
					 PAGE_SIZE >> inode->i_blkbits);
		अगर (error)
			जाओ out_trans_fail;

		error = fallocate_chunk(inode, offset, max_bytes, mode);
		gfs2_trans_end(sdp);

		अगर (error)
			जाओ out_trans_fail;

		len -= max_bytes;
		offset += max_bytes;
		gfs2_inplace_release(ip);
		gfs2_quota_unlock(ip);
	पूर्ण

	अगर (!(mode & FALLOC_FL_KEEP_SIZE) && (pos + count) > inode->i_size)
		i_size_ग_लिखो(inode, pos + count);
	file_update_समय(file);
	mark_inode_dirty(inode);

	अगर ((file->f_flags & O_DSYNC) || IS_SYNC(file->f_mapping->host))
		वापस vfs_fsync_range(file, pos, pos + count - 1,
			       (file->f_flags & __O_SYNC) ? 0 : 1);
	वापस 0;

out_trans_fail:
	gfs2_inplace_release(ip);
out_qunlock:
	gfs2_quota_unlock(ip);
	वापस error;
पूर्ण

अटल दीर्घ gfs2_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	पूर्णांक ret;

	अगर (mode & ~(FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE))
		वापस -EOPNOTSUPP;
	/* fallocate is needed by gfs2_grow to reserve space in the rindex */
	अगर (gfs2_is_jdata(ip) && inode != sdp->sd_rindex)
		वापस -EOPNOTSUPP;

	inode_lock(inode);

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
	ret = gfs2_glock_nq(&gh);
	अगर (ret)
		जाओ out_uninit;

	अगर (!(mode & FALLOC_FL_KEEP_SIZE) &&
	    (offset + len) > inode->i_size) अणु
		ret = inode_newsize_ok(inode, offset + len);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	ret = get_ग_लिखो_access(inode);
	अगर (ret)
		जाओ out_unlock;

	अगर (mode & FALLOC_FL_PUNCH_HOLE) अणु
		ret = __gfs2_punch_hole(file, offset, len);
	पूर्ण अन्यथा अणु
		ret = __gfs2_fallocate(file, mode, offset, len);
		अगर (ret)
			gfs2_rs_deltree(&ip->i_res);
	पूर्ण

	put_ग_लिखो_access(inode);
out_unlock:
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	inode_unlock(inode);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार gfs2_file_splice_ग_लिखो(काष्ठा pipe_inode_info *pipe,
				      काष्ठा file *out, loff_t *ppos,
				      माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	sमाप_प्रकार ret;

	gfs2_size_hपूर्णांक(out, *ppos, len);

	ret = iter_file_splice_ग_लिखो(pipe, out, ppos, len, flags);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GFS2_FS_LOCKING_DLM

/**
 * gfs2_lock - acquire/release a posix lock on a file
 * @file: the file poपूर्णांकer
 * @cmd: either modअगरy or retrieve lock state, possibly रुको
 * @fl: type and range of lock
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_lock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(file->f_mapping->host);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(file->f_mapping->host);
	काष्ठा lm_lockकाष्ठा *ls = &sdp->sd_lockकाष्ठा;

	अगर (!(fl->fl_flags & FL_POSIX))
		वापस -ENOLCK;
	अगर (__mandatory_lock(&ip->i_inode) && fl->fl_type != F_UNLCK)
		वापस -ENOLCK;

	अगर (cmd == F_CANCELLK) अणु
		/* Hack: */
		cmd = F_SETLK;
		fl->fl_type = F_UNLCK;
	पूर्ण
	अगर (unlikely(gfs2_withdrawn(sdp))) अणु
		अगर (fl->fl_type == F_UNLCK)
			locks_lock_file_रुको(file, fl);
		वापस -EIO;
	पूर्ण
	अगर (IS_GETLK(cmd))
		वापस dlm_posix_get(ls->ls_dlm, ip->i_no_addr, file, fl);
	अन्यथा अगर (fl->fl_type == F_UNLCK)
		वापस dlm_posix_unlock(ls->ls_dlm, ip->i_no_addr, file, fl);
	अन्यथा
		वापस dlm_posix_lock(ls->ls_dlm, ip->i_no_addr, file, cmd, fl);
पूर्ण

अटल पूर्णांक करो_flock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा gfs2_file *fp = file->निजी_data;
	काष्ठा gfs2_holder *fl_gh = &fp->f_fl_gh;
	काष्ठा gfs2_inode *ip = GFS2_I(file_inode(file));
	काष्ठा gfs2_glock *gl;
	अचिन्हित पूर्णांक state;
	u16 flags;
	पूर्णांक error = 0;
	पूर्णांक sleepसमय;

	state = (fl->fl_type == F_WRLCK) ? LM_ST_EXCLUSIVE : LM_ST_SHARED;
	flags = (IS_SETLKW(cmd) ? 0 : LM_FLAG_TRY_1CB) | GL_EXACT;

	mutex_lock(&fp->f_fl_mutex);

	अगर (gfs2_holder_initialized(fl_gh)) अणु
		काष्ठा file_lock request;
		अगर (fl_gh->gh_state == state)
			जाओ out;
		locks_init_lock(&request);
		request.fl_type = F_UNLCK;
		request.fl_flags = FL_FLOCK;
		locks_lock_file_रुको(file, &request);
		gfs2_glock_dq(fl_gh);
		gfs2_holder_reinit(state, flags, fl_gh);
	पूर्ण अन्यथा अणु
		error = gfs2_glock_get(GFS2_SB(&ip->i_inode), ip->i_no_addr,
				       &gfs2_flock_glops, CREATE, &gl);
		अगर (error)
			जाओ out;
		gfs2_holder_init(gl, state, flags, fl_gh);
		gfs2_glock_put(gl);
	पूर्ण
	क्रम (sleepसमय = 1; sleepसमय <= 4; sleepसमय <<= 1) अणु
		error = gfs2_glock_nq(fl_gh);
		अगर (error != GLR_TRYFAILED)
			अवरोध;
		fl_gh->gh_flags = LM_FLAG_TRY | GL_EXACT;
		fl_gh->gh_error = 0;
		msleep(sleepसमय);
	पूर्ण
	अगर (error) अणु
		gfs2_holder_uninit(fl_gh);
		अगर (error == GLR_TRYFAILED)
			error = -EAGAIN;
	पूर्ण अन्यथा अणु
		error = locks_lock_file_रुको(file, fl);
		gfs2_निश्चित_warn(GFS2_SB(&ip->i_inode), !error);
	पूर्ण

out:
	mutex_unlock(&fp->f_fl_mutex);
	वापस error;
पूर्ण

अटल व्योम करो_unflock(काष्ठा file *file, काष्ठा file_lock *fl)
अणु
	काष्ठा gfs2_file *fp = file->निजी_data;
	काष्ठा gfs2_holder *fl_gh = &fp->f_fl_gh;

	mutex_lock(&fp->f_fl_mutex);
	locks_lock_file_रुको(file, fl);
	अगर (gfs2_holder_initialized(fl_gh)) अणु
		gfs2_glock_dq(fl_gh);
		gfs2_holder_uninit(fl_gh);
	पूर्ण
	mutex_unlock(&fp->f_fl_mutex);
पूर्ण

/**
 * gfs2_flock - acquire/release a flock lock on a file
 * @file: the file poपूर्णांकer
 * @cmd: either modअगरy or retrieve lock state, possibly रुको
 * @fl: type and range of lock
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_flock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	अगर (!(fl->fl_flags & FL_FLOCK))
		वापस -ENOLCK;
	अगर (fl->fl_type & LOCK_MAND)
		वापस -EOPNOTSUPP;

	अगर (fl->fl_type == F_UNLCK) अणु
		करो_unflock(file, fl);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस करो_flock(file, cmd, fl);
	पूर्ण
पूर्ण

स्थिर काष्ठा file_operations gfs2_file_fops = अणु
	.llseek		= gfs2_llseek,
	.पढ़ो_iter	= gfs2_file_पढ़ो_iter,
	.ग_लिखो_iter	= gfs2_file_ग_लिखो_iter,
	.iopoll		= iomap_dio_iopoll,
	.unlocked_ioctl	= gfs2_ioctl,
	.compat_ioctl	= gfs2_compat_ioctl,
	.mmap		= gfs2_mmap,
	.खोलो		= gfs2_खोलो,
	.release	= gfs2_release,
	.fsync		= gfs2_fsync,
	.lock		= gfs2_lock,
	.flock		= gfs2_flock,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= gfs2_file_splice_ग_लिखो,
	.setlease	= simple_nosetlease,
	.fallocate	= gfs2_fallocate,
पूर्ण;

स्थिर काष्ठा file_operations gfs2_dir_fops = अणु
	.iterate_shared	= gfs2_सूची_पढ़ो,
	.unlocked_ioctl	= gfs2_ioctl,
	.compat_ioctl	= gfs2_compat_ioctl,
	.खोलो		= gfs2_खोलो,
	.release	= gfs2_release,
	.fsync		= gfs2_fsync,
	.lock		= gfs2_lock,
	.flock		= gfs2_flock,
	.llseek		= शेष_llseek,
पूर्ण;

#पूर्ण_अगर /* CONFIG_GFS2_FS_LOCKING_DLM */

स्थिर काष्ठा file_operations gfs2_file_fops_nolock = अणु
	.llseek		= gfs2_llseek,
	.पढ़ो_iter	= gfs2_file_पढ़ो_iter,
	.ग_लिखो_iter	= gfs2_file_ग_लिखो_iter,
	.iopoll		= iomap_dio_iopoll,
	.unlocked_ioctl	= gfs2_ioctl,
	.compat_ioctl	= gfs2_compat_ioctl,
	.mmap		= gfs2_mmap,
	.खोलो		= gfs2_खोलो,
	.release	= gfs2_release,
	.fsync		= gfs2_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= gfs2_file_splice_ग_लिखो,
	.setlease	= generic_setlease,
	.fallocate	= gfs2_fallocate,
पूर्ण;

स्थिर काष्ठा file_operations gfs2_dir_fops_nolock = अणु
	.iterate_shared	= gfs2_सूची_पढ़ो,
	.unlocked_ioctl	= gfs2_ioctl,
	.compat_ioctl	= gfs2_compat_ioctl,
	.खोलो		= gfs2_खोलो,
	.release	= gfs2_release,
	.fsync		= gfs2_fsync,
	.llseek		= शेष_llseek,
पूर्ण;


<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ioctl.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/mm.h>
#समावेश <linux/capability.h>
#समावेश <linux/compat.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fiemap.h>
#समावेश <linux/mount.h>
#समावेश <linux/fscrypt.h>
#समावेश <linux/fileattr.h>

#समावेश "internal.h"

#समावेश <यंत्र/ioctls.h>

/* So that the fiemap access checks can't overflow on 32 bit machines. */
#घोषणा FIEMAP_MAX_EXTENTS	(अच_पूर्णांक_उच्च / माप(काष्ठा fiemap_extent))

/**
 * vfs_ioctl - call fileप्रणाली specअगरic ioctl methods
 * @filp:	खोलो file to invoke ioctl method on
 * @cmd:	ioctl command to execute
 * @arg:	command-specअगरic argument क्रम ioctl
 *
 * Invokes fileप्रणाली specअगरic ->unlocked_ioctl, अगर one exists; otherwise
 * वापसs -ENOTTY.
 *
 * Returns 0 on success, -त्रुटि_सं on error.
 */
दीर्घ vfs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक error = -ENOTTY;

	अगर (!filp->f_op->unlocked_ioctl)
		जाओ out;

	error = filp->f_op->unlocked_ioctl(filp, cmd, arg);
	अगर (error == -ENOIOCTLCMD)
		error = -ENOTTY;
 out:
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_ioctl);

अटल पूर्णांक ioctl_fibmap(काष्ठा file *filp, पूर्णांक __user *p)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक error, ur_block;
	sector_t block;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	error = get_user(ur_block, p);
	अगर (error)
		वापस error;

	अगर (ur_block < 0)
		वापस -EINVAL;

	block = ur_block;
	error = bmap(inode, &block);

	अगर (block > पूर्णांक_उच्च) अणु
		error = -दुस्फल;
		pr_warn_ratelimited("[%s/%d] FS: %s File: %pD4 would truncate fibmap result\n",
				    current->comm, task_pid_nr(current),
				    sb->s_id, filp);
	पूर्ण

	अगर (error)
		ur_block = 0;
	अन्यथा
		ur_block = block;

	अगर (put_user(ur_block, p))
		error = -EFAULT;

	वापस error;
पूर्ण

/**
 * fiemap_fill_next_extent - Fiemap helper function
 * @fieinfo:	Fiemap context passed पूर्णांकo ->fiemap
 * @logical:	Extent logical start offset, in bytes
 * @phys:	Extent physical start offset, in bytes
 * @len:	Extent length, in bytes
 * @flags:	FIEMAP_EXTENT flags that describe this extent
 *
 * Called from file प्रणाली ->fiemap callback. Will populate extent
 * info as passed in via arguments and copy to user memory. On
 * success, extent count on fieinfo is incremented.
 *
 * Returns 0 on success, -त्रुटि_सं on error, 1 अगर this was the last
 * extent that will fit in user array.
 */
#घोषणा SET_UNKNOWN_FLAGS	(FIEMAP_EXTENT_DELALLOC)
#घोषणा SET_NO_UNMOUNTED_IO_FLAGS	(FIEMAP_EXTENT_DATA_ENCRYPTED)
#घोषणा SET_NOT_ALIGNED_FLAGS	(FIEMAP_EXTENT_DATA_TAIL|FIEMAP_EXTENT_DATA_INLINE)
पूर्णांक fiemap_fill_next_extent(काष्ठा fiemap_extent_info *fieinfo, u64 logical,
			    u64 phys, u64 len, u32 flags)
अणु
	काष्ठा fiemap_extent extent;
	काष्ठा fiemap_extent __user *dest = fieinfo->fi_extents_start;

	/* only count the extents */
	अगर (fieinfo->fi_extents_max == 0) अणु
		fieinfo->fi_extents_mapped++;
		वापस (flags & FIEMAP_EXTENT_LAST) ? 1 : 0;
	पूर्ण

	अगर (fieinfo->fi_extents_mapped >= fieinfo->fi_extents_max)
		वापस 1;

	अगर (flags & SET_UNKNOWN_FLAGS)
		flags |= FIEMAP_EXTENT_UNKNOWN;
	अगर (flags & SET_NO_UNMOUNTED_IO_FLAGS)
		flags |= FIEMAP_EXTENT_ENCODED;
	अगर (flags & SET_NOT_ALIGNED_FLAGS)
		flags |= FIEMAP_EXTENT_NOT_ALIGNED;

	स_रखो(&extent, 0, माप(extent));
	extent.fe_logical = logical;
	extent.fe_physical = phys;
	extent.fe_length = len;
	extent.fe_flags = flags;

	dest += fieinfo->fi_extents_mapped;
	अगर (copy_to_user(dest, &extent, माप(extent)))
		वापस -EFAULT;

	fieinfo->fi_extents_mapped++;
	अगर (fieinfo->fi_extents_mapped == fieinfo->fi_extents_max)
		वापस 1;
	वापस (flags & FIEMAP_EXTENT_LAST) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL(fiemap_fill_next_extent);

/**
 * fiemap_prep - check validity of requested flags क्रम fiemap
 * @inode:	Inode to operate on
 * @fieinfo:	Fiemap context passed पूर्णांकo ->fiemap
 * @start:	Start of the mapped range
 * @len:	Length of the mapped range, can be truncated by this function.
 * @supported_flags:	Set of fiemap flags that the file प्रणाली understands
 *
 * This function must be called from each ->fiemap instance to validate the
 * fiemap request against the file प्रणाली parameters.
 *
 * Returns 0 on success, or a negative error on failure.
 */
पूर्णांक fiemap_prep(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		u64 start, u64 *len, u32 supported_flags)
अणु
	u64 maxbytes = inode->i_sb->s_maxbytes;
	u32 incompat_flags;
	पूर्णांक ret = 0;

	अगर (*len == 0)
		वापस -EINVAL;
	अगर (start > maxbytes)
		वापस -EFBIG;

	/*
	 * Shrink request scope to what the fs can actually handle.
	 */
	अगर (*len > maxbytes || (maxbytes - *len) < start)
		*len = maxbytes - start;

	supported_flags |= FIEMAP_FLAG_SYNC;
	supported_flags &= FIEMAP_FLAGS_COMPAT;
	incompat_flags = fieinfo->fi_flags & ~supported_flags;
	अगर (incompat_flags) अणु
		fieinfo->fi_flags = incompat_flags;
		वापस -EBADR;
	पूर्ण

	अगर (fieinfo->fi_flags & FIEMAP_FLAG_SYNC)
		ret = filemap_ग_लिखो_and_रुको(inode->i_mapping);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(fiemap_prep);

अटल पूर्णांक ioctl_fiemap(काष्ठा file *filp, काष्ठा fiemap __user *ufiemap)
अणु
	काष्ठा fiemap fiemap;
	काष्ठा fiemap_extent_info fieinfo = अणु 0, पूर्ण;
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक error;

	अगर (!inode->i_op->fiemap)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&fiemap, ufiemap, माप(fiemap)))
		वापस -EFAULT;

	अगर (fiemap.fm_extent_count > FIEMAP_MAX_EXTENTS)
		वापस -EINVAL;

	fieinfo.fi_flags = fiemap.fm_flags;
	fieinfo.fi_extents_max = fiemap.fm_extent_count;
	fieinfo.fi_extents_start = ufiemap->fm_extents;

	error = inode->i_op->fiemap(inode, &fieinfo, fiemap.fm_start,
			fiemap.fm_length);

	fiemap.fm_flags = fieinfo.fi_flags;
	fiemap.fm_mapped_extents = fieinfo.fi_extents_mapped;
	अगर (copy_to_user(ufiemap, &fiemap, माप(fiemap)))
		error = -EFAULT;

	वापस error;
पूर्ण

अटल दीर्घ ioctl_file_clone(काष्ठा file *dst_file, अचिन्हित दीर्घ srcfd,
			     u64 off, u64 olen, u64 destoff)
अणु
	काष्ठा fd src_file = fdget(srcfd);
	loff_t cloned;
	पूर्णांक ret;

	अगर (!src_file.file)
		वापस -EBADF;
	ret = -EXDEV;
	अगर (src_file.file->f_path.mnt != dst_file->f_path.mnt)
		जाओ fdput;
	cloned = vfs_clone_file_range(src_file.file, off, dst_file, destoff,
				      olen, 0);
	अगर (cloned < 0)
		ret = cloned;
	अन्यथा अगर (olen && cloned != olen)
		ret = -EINVAL;
	अन्यथा
		ret = 0;
fdput:
	fdput(src_file);
	वापस ret;
पूर्ण

अटल दीर्घ ioctl_file_clone_range(काष्ठा file *file,
				   काष्ठा file_clone_range __user *argp)
अणु
	काष्ठा file_clone_range args;

	अगर (copy_from_user(&args, argp, माप(args)))
		वापस -EFAULT;
	वापस ioctl_file_clone(file, args.src_fd, args.src_offset,
				args.src_length, args.dest_offset);
पूर्ण

#अगर_घोषित CONFIG_BLOCK

अटल अंतरभूत sector_t logical_to_blk(काष्ठा inode *inode, loff_t offset)
अणु
	वापस (offset >> inode->i_blkbits);
पूर्ण

अटल अंतरभूत loff_t blk_to_logical(काष्ठा inode *inode, sector_t blk)
अणु
	वापस (blk << inode->i_blkbits);
पूर्ण

/**
 * __generic_block_fiemap - FIEMAP क्रम block based inodes (no locking)
 * @inode: the inode to map
 * @fieinfo: the fiemap info काष्ठा that will be passed back to userspace
 * @start: where to start mapping in the inode
 * @len: how much space to map
 * @get_block: the fs's get_block function
 *
 * This करोes FIEMAP क्रम block based inodes.  Basically it will just loop
 * through get_block until we hit the number of extents we want to map, or we
 * go past the end of the file and hit a hole.
 *
 * If it is possible to have data blocks beyond a hole past @inode->i_size, then
 * please करो not use this function, it will stop at the first unmapped block
 * beyond i_size.
 *
 * If you use this function directly, you need to करो your own locking. Use
 * generic_block_fiemap अगर you want the locking करोne क्रम you.
 */
अटल पूर्णांक __generic_block_fiemap(काष्ठा inode *inode,
			   काष्ठा fiemap_extent_info *fieinfo, loff_t start,
			   loff_t len, get_block_t *get_block)
अणु
	काष्ठा buffer_head map_bh;
	sector_t start_blk, last_blk;
	loff_t isize = i_size_पढ़ो(inode);
	u64 logical = 0, phys = 0, size = 0;
	u32 flags = FIEMAP_EXTENT_MERGED;
	bool past_eof = false, whole_file = false;
	पूर्णांक ret = 0;

	ret = fiemap_prep(inode, fieinfo, start, &len, FIEMAP_FLAG_SYNC);
	अगर (ret)
		वापस ret;

	/*
	 * Either the i_mutex or other appropriate locking needs to be held
	 * since we expect isize to not change at all through the duration of
	 * this call.
	 */
	अगर (len >= isize) अणु
		whole_file = true;
		len = isize;
	पूर्ण

	/*
	 * Some fileप्रणालीs can't deal with being asked to map less than
	 * blocksize, so make sure our len is at least block length.
	 */
	अगर (logical_to_blk(inode, len) == 0)
		len = blk_to_logical(inode, 1);

	start_blk = logical_to_blk(inode, start);
	last_blk = logical_to_blk(inode, start + len - 1);

	करो अणु
		/*
		 * we set b_size to the total size we want so it will map as
		 * many contiguous blocks as possible at once
		 */
		स_रखो(&map_bh, 0, माप(काष्ठा buffer_head));
		map_bh.b_size = len;

		ret = get_block(inode, start_blk, &map_bh, 0);
		अगर (ret)
			अवरोध;

		/* HOLE */
		अगर (!buffer_mapped(&map_bh)) अणु
			start_blk++;

			/*
			 * We want to handle the हाल where there is an
			 * allocated block at the front of the file, and then
			 * nothing but holes up to the end of the file properly,
			 * to make sure that extent at the front माला_लो properly
			 * marked with FIEMAP_EXTENT_LAST
			 */
			अगर (!past_eof &&
			    blk_to_logical(inode, start_blk) >= isize)
				past_eof = 1;

			/*
			 * First hole after going past the खातापूर्ण, this is our
			 * last extent
			 */
			अगर (past_eof && size) अणु
				flags = FIEMAP_EXTENT_MERGED|FIEMAP_EXTENT_LAST;
				ret = fiemap_fill_next_extent(fieinfo, logical,
							      phys, size,
							      flags);
			पूर्ण अन्यथा अगर (size) अणु
				ret = fiemap_fill_next_extent(fieinfo, logical,
							      phys, size, flags);
				size = 0;
			पूर्ण

			/* अगर we have holes up to/past खातापूर्ण then we're करोne */
			अगर (start_blk > last_blk || past_eof || ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			/*
			 * We have gone over the length of what we wanted to
			 * map, and it wasn't the entire file, so add the extent
			 * we got last समय and निकास.
			 *
			 * This is क्रम the हाल where say we want to map all the
			 * way up to the second to the last block in a file, but
			 * the last block is a hole, making the second to last
			 * block FIEMAP_EXTENT_LAST.  In this हाल we want to
			 * see अगर there is a hole after the second to last block
			 * so we can mark it properly.  If we found data after
			 * we exceeded the length we were requesting, then we
			 * are good to go, just add the extent to the fieinfo
			 * and अवरोध
			 */
			अगर (start_blk > last_blk && !whole_file) अणु
				ret = fiemap_fill_next_extent(fieinfo, logical,
							      phys, size,
							      flags);
				अवरोध;
			पूर्ण

			/*
			 * अगर size != 0 then we know we alपढ़ोy have an extent
			 * to add, so add it.
			 */
			अगर (size) अणु
				ret = fiemap_fill_next_extent(fieinfo, logical,
							      phys, size,
							      flags);
				अगर (ret)
					अवरोध;
			पूर्ण

			logical = blk_to_logical(inode, start_blk);
			phys = blk_to_logical(inode, map_bh.b_blocknr);
			size = map_bh.b_size;
			flags = FIEMAP_EXTENT_MERGED;

			start_blk += logical_to_blk(inode, size);

			/*
			 * If we are past the खातापूर्ण, then we need to make sure as
			 * soon as we find a hole that the last extent we found
			 * is marked with FIEMAP_EXTENT_LAST
			 */
			अगर (!past_eof && logical + size >= isize)
				past_eof = true;
		पूर्ण
		cond_resched();
		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण

	पूर्ण जबतक (1);

	/* If ret is 1 then we just hit the end of the extent array */
	अगर (ret == 1)
		ret = 0;

	वापस ret;
पूर्ण

/**
 * generic_block_fiemap - FIEMAP क्रम block based inodes
 * @inode: The inode to map
 * @fieinfo: The mapping inक्रमmation
 * @start: The initial block to map
 * @len: The length of the extect to attempt to map
 * @get_block: The block mapping function क्रम the fs
 *
 * Calls __generic_block_fiemap to map the inode, after taking
 * the inode's mutex lock.
 */

पूर्णांक generic_block_fiemap(काष्ठा inode *inode,
			 काष्ठा fiemap_extent_info *fieinfo, u64 start,
			 u64 len, get_block_t *get_block)
अणु
	पूर्णांक ret;
	inode_lock(inode);
	ret = __generic_block_fiemap(inode, fieinfo, start, len, get_block);
	inode_unlock(inode);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(generic_block_fiemap);

#पूर्ण_अगर  /*  CONFIG_BLOCK  */

/*
 * This provides compatibility with legacy XFS pre-allocation ioctls
 * which predate the fallocate syscall.
 *
 * Only the l_start, l_len and l_whence fields of the 'struct space_resv'
 * are used here, rest are ignored.
 */
अटल पूर्णांक ioctl_pपुनः_स्मृतिate(काष्ठा file *filp, पूर्णांक mode, व्योम __user *argp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा space_resv sr;

	अगर (copy_from_user(&sr, argp, माप(sr)))
		वापस -EFAULT;

	चयन (sr.l_whence) अणु
	हाल शुरू_से:
		अवरोध;
	हाल प्रस्तुत_से:
		sr.l_start += filp->f_pos;
		अवरोध;
	हाल अंत_से:
		sr.l_start += i_size_पढ़ो(inode);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस vfs_fallocate(filp, mode | FALLOC_FL_KEEP_SIZE, sr.l_start,
			sr.l_len);
पूर्ण

/* on ia32 l_start is on a 32-bit boundary */
#अगर defined CONFIG_COMPAT && defined(CONFIG_X86_64)
/* just account क्रम dअगरferent alignment */
अटल पूर्णांक compat_ioctl_pपुनः_स्मृतिate(काष्ठा file *file, पूर्णांक mode,
				    काष्ठा space_resv_32 __user *argp)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा space_resv_32 sr;

	अगर (copy_from_user(&sr, argp, माप(sr)))
		वापस -EFAULT;

	चयन (sr.l_whence) अणु
	हाल शुरू_से:
		अवरोध;
	हाल प्रस्तुत_से:
		sr.l_start += file->f_pos;
		अवरोध;
	हाल अंत_से:
		sr.l_start += i_size_पढ़ो(inode);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस vfs_fallocate(file, mode | FALLOC_FL_KEEP_SIZE, sr.l_start, sr.l_len);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक file_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, पूर्णांक __user *p)
अणु
	चयन (cmd) अणु
	हाल FIBMAP:
		वापस ioctl_fibmap(filp, p);
	हाल FS_IOC_RESVSP:
	हाल FS_IOC_RESVSP64:
		वापस ioctl_pपुनः_स्मृतिate(filp, 0, p);
	हाल FS_IOC_UNRESVSP:
	हाल FS_IOC_UNRESVSP64:
		वापस ioctl_pपुनः_स्मृतिate(filp, FALLOC_FL_PUNCH_HOLE, p);
	हाल FS_IOC_ZERO_RANGE:
		वापस ioctl_pपुनः_स्मृतिate(filp, FALLOC_FL_ZERO_RANGE, p);
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

अटल पूर्णांक ioctl_fionbio(काष्ठा file *filp, पूर्णांक __user *argp)
अणु
	अचिन्हित पूर्णांक flag;
	पूर्णांक on, error;

	error = get_user(on, argp);
	अगर (error)
		वापस error;
	flag = O_NONBLOCK;
#अगर_घोषित __sparc__
	/* SunOS compatibility item. */
	अगर (O_NONBLOCK != O_NDELAY)
		flag |= O_NDELAY;
#पूर्ण_अगर
	spin_lock(&filp->f_lock);
	अगर (on)
		filp->f_flags |= flag;
	अन्यथा
		filp->f_flags &= ~flag;
	spin_unlock(&filp->f_lock);
	वापस error;
पूर्ण

अटल पूर्णांक ioctl_fioasync(अचिन्हित पूर्णांक fd, काष्ठा file *filp,
			  पूर्णांक __user *argp)
अणु
	अचिन्हित पूर्णांक flag;
	पूर्णांक on, error;

	error = get_user(on, argp);
	अगर (error)
		वापस error;
	flag = on ? FASYNC : 0;

	/* Did FASYNC state change ? */
	अगर ((flag ^ filp->f_flags) & FASYNC) अणु
		अगर (filp->f_op->fasync)
			/* fasync() adjusts filp->f_flags */
			error = filp->f_op->fasync(fd, filp, on);
		अन्यथा
			error = -ENOTTY;
	पूर्ण
	वापस error < 0 ? error : 0;
पूर्ण

अटल पूर्णांक ioctl_fsमुक्तze(काष्ठा file *filp)
अणु
	काष्ठा super_block *sb = file_inode(filp)->i_sb;

	अगर (!ns_capable(sb->s_user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	/* If fileप्रणाली करोesn't support मुक्तze feature, वापस. */
	अगर (sb->s_op->मुक्तze_fs == शून्य && sb->s_op->मुक्तze_super == शून्य)
		वापस -EOPNOTSUPP;

	/* Freeze */
	अगर (sb->s_op->मुक्तze_super)
		वापस sb->s_op->मुक्तze_super(sb);
	वापस मुक्तze_super(sb);
पूर्ण

अटल पूर्णांक ioctl_fsthaw(काष्ठा file *filp)
अणु
	काष्ठा super_block *sb = file_inode(filp)->i_sb;

	अगर (!ns_capable(sb->s_user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	/* Thaw */
	अगर (sb->s_op->thaw_super)
		वापस sb->s_op->thaw_super(sb);
	वापस thaw_super(sb);
पूर्ण

अटल पूर्णांक ioctl_file_dedupe_range(काष्ठा file *file,
				   काष्ठा file_dedupe_range __user *argp)
अणु
	काष्ठा file_dedupe_range *same = शून्य;
	पूर्णांक ret;
	अचिन्हित दीर्घ size;
	u16 count;

	अगर (get_user(count, &argp->dest_count)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	size = दुरत्व(काष्ठा file_dedupe_range __user, info[count]);
	अगर (size > PAGE_SIZE) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	same = memdup_user(argp, size);
	अगर (IS_ERR(same)) अणु
		ret = PTR_ERR(same);
		same = शून्य;
		जाओ out;
	पूर्ण

	same->dest_count = count;
	ret = vfs_dedupe_file_range(file, same);
	अगर (ret)
		जाओ out;

	ret = copy_to_user(argp, same, size);
	अगर (ret)
		ret = -EFAULT;

out:
	kमुक्त(same);
	वापस ret;
पूर्ण

/**
 * fileattr_fill_xflags - initialize fileattr with xflags
 * @fa:		fileattr poपूर्णांकer
 * @xflags:	FS_XFLAG_* flags
 *
 * Set ->fsx_xflags, ->fsx_valid and ->flags (translated xflags).  All
 * other fields are zeroed.
 */
व्योम fileattr_fill_xflags(काष्ठा fileattr *fa, u32 xflags)
अणु
	स_रखो(fa, 0, माप(*fa));
	fa->fsx_valid = true;
	fa->fsx_xflags = xflags;
	अगर (fa->fsx_xflags & FS_XFLAG_IMMUTABLE)
		fa->flags |= FS_IMMUTABLE_FL;
	अगर (fa->fsx_xflags & FS_XFLAG_APPEND)
		fa->flags |= FS_APPEND_FL;
	अगर (fa->fsx_xflags & FS_XFLAG_SYNC)
		fa->flags |= FS_SYNC_FL;
	अगर (fa->fsx_xflags & FS_XFLAG_NOATIME)
		fa->flags |= FS_NOATIME_FL;
	अगर (fa->fsx_xflags & FS_XFLAG_NODUMP)
		fa->flags |= FS_NODUMP_FL;
	अगर (fa->fsx_xflags & FS_XFLAG_DAX)
		fa->flags |= FS_DAX_FL;
	अगर (fa->fsx_xflags & FS_XFLAG_PROJINHERIT)
		fa->flags |= FS_PROJINHERIT_FL;
पूर्ण
EXPORT_SYMBOL(fileattr_fill_xflags);

/**
 * fileattr_fill_flags - initialize fileattr with flags
 * @fa:		fileattr poपूर्णांकer
 * @flags:	FS_*_FL flags
 *
 * Set ->flags, ->flags_valid and ->fsx_xflags (translated flags).
 * All other fields are zeroed.
 */
व्योम fileattr_fill_flags(काष्ठा fileattr *fa, u32 flags)
अणु
	स_रखो(fa, 0, माप(*fa));
	fa->flags_valid = true;
	fa->flags = flags;
	अगर (fa->flags & FS_SYNC_FL)
		fa->fsx_xflags |= FS_XFLAG_SYNC;
	अगर (fa->flags & FS_IMMUTABLE_FL)
		fa->fsx_xflags |= FS_XFLAG_IMMUTABLE;
	अगर (fa->flags & FS_APPEND_FL)
		fa->fsx_xflags |= FS_XFLAG_APPEND;
	अगर (fa->flags & FS_NODUMP_FL)
		fa->fsx_xflags |= FS_XFLAG_NODUMP;
	अगर (fa->flags & FS_NOATIME_FL)
		fa->fsx_xflags |= FS_XFLAG_NOATIME;
	अगर (fa->flags & FS_DAX_FL)
		fa->fsx_xflags |= FS_XFLAG_DAX;
	अगर (fa->flags & FS_PROJINHERIT_FL)
		fa->fsx_xflags |= FS_XFLAG_PROJINHERIT;
पूर्ण
EXPORT_SYMBOL(fileattr_fill_flags);

/**
 * vfs_fileattr_get - retrieve miscellaneous file attributes
 * @dentry:	the object to retrieve from
 * @fa:		fileattr poपूर्णांकer
 *
 * Call i_op->fileattr_get() callback, अगर exists.
 *
 * Return: 0 on success, or a negative error on failure.
 */
पूर्णांक vfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (!inode->i_op->fileattr_get)
		वापस -ENOIOCTLCMD;

	वापस inode->i_op->fileattr_get(dentry, fa);
पूर्ण
EXPORT_SYMBOL(vfs_fileattr_get);

/**
 * copy_fsxattr_to_user - copy fsxattr to userspace.
 * @fa:		fileattr poपूर्णांकer
 * @ufa:	fsxattr user poपूर्णांकer
 *
 * Return: 0 on success, or -EFAULT on failure.
 */
पूर्णांक copy_fsxattr_to_user(स्थिर काष्ठा fileattr *fa, काष्ठा fsxattr __user *ufa)
अणु
	काष्ठा fsxattr xfa;

	स_रखो(&xfa, 0, माप(xfa));
	xfa.fsx_xflags = fa->fsx_xflags;
	xfa.fsx_extsize = fa->fsx_extsize;
	xfa.fsx_nextents = fa->fsx_nextents;
	xfa.fsx_projid = fa->fsx_projid;
	xfa.fsx_cowextsize = fa->fsx_cowextsize;

	अगर (copy_to_user(ufa, &xfa, माप(xfa)))
		वापस -EFAULT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(copy_fsxattr_to_user);

अटल पूर्णांक copy_fsxattr_from_user(काष्ठा fileattr *fa,
				  काष्ठा fsxattr __user *ufa)
अणु
	काष्ठा fsxattr xfa;

	अगर (copy_from_user(&xfa, ufa, माप(xfa)))
		वापस -EFAULT;

	fileattr_fill_xflags(fa, xfa.fsx_xflags);
	fa->fsx_extsize = xfa.fsx_extsize;
	fa->fsx_nextents = xfa.fsx_nextents;
	fa->fsx_projid = xfa.fsx_projid;
	fa->fsx_cowextsize = xfa.fsx_cowextsize;

	वापस 0;
पूर्ण

/*
 * Generic function to check FS_IOC_FSSETXATTR/FS_IOC_SETFLAGS values and reject
 * any invalid configurations.
 *
 * Note: must be called with inode lock held.
 */
अटल पूर्णांक fileattr_set_prepare(काष्ठा inode *inode,
			      स्थिर काष्ठा fileattr *old_ma,
			      काष्ठा fileattr *fa)
अणु
	पूर्णांक err;

	/*
	 * The IMMUTABLE and APPEND_ONLY flags can only be changed by
	 * the relevant capability.
	 */
	अगर ((fa->flags ^ old_ma->flags) & (FS_APPEND_FL | FS_IMMUTABLE_FL) &&
	    !capable(CAP_LINUX_IMMUTABLE))
		वापस -EPERM;

	err = fscrypt_prepare_setflags(inode, old_ma->flags, fa->flags);
	अगर (err)
		वापस err;

	/*
	 * Project Quota ID state is only allowed to change from within the init
	 * namespace. Enक्रमce that restriction only अगर we are trying to change
	 * the quota ID state. Everything अन्यथा is allowed in user namespaces.
	 */
	अगर (current_user_ns() != &init_user_ns) अणु
		अगर (old_ma->fsx_projid != fa->fsx_projid)
			वापस -EINVAL;
		अगर ((old_ma->fsx_xflags ^ fa->fsx_xflags) &
				FS_XFLAG_PROJINHERIT)
			वापस -EINVAL;
	पूर्ण

	/* Check extent size hपूर्णांकs. */
	अगर ((fa->fsx_xflags & FS_XFLAG_EXTSIZE) && !S_ISREG(inode->i_mode))
		वापस -EINVAL;

	अगर ((fa->fsx_xflags & FS_XFLAG_EXTSZINHERIT) &&
			!S_ISसूची(inode->i_mode))
		वापस -EINVAL;

	अगर ((fa->fsx_xflags & FS_XFLAG_COWEXTSIZE) &&
	    !S_ISREG(inode->i_mode) && !S_ISसूची(inode->i_mode))
		वापस -EINVAL;

	/*
	 * It is only valid to set the DAX flag on regular files and
	 * directories on fileप्रणालीs.
	 */
	अगर ((fa->fsx_xflags & FS_XFLAG_DAX) &&
	    !(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode)))
		वापस -EINVAL;

	/* Extent size hपूर्णांकs of zero turn off the flags. */
	अगर (fa->fsx_extsize == 0)
		fa->fsx_xflags &= ~(FS_XFLAG_EXTSIZE | FS_XFLAG_EXTSZINHERIT);
	अगर (fa->fsx_cowextsize == 0)
		fa->fsx_xflags &= ~FS_XFLAG_COWEXTSIZE;

	वापस 0;
पूर्ण

/**
 * vfs_fileattr_set - change miscellaneous file attributes
 * @mnt_userns:	user namespace of the mount
 * @dentry:	the object to change
 * @fa:		fileattr poपूर्णांकer
 *
 * After verअगरying permissions, call i_op->fileattr_set() callback, अगर
 * exists.
 *
 * Verअगरying attributes involves retrieving current attributes with
 * i_op->fileattr_get(), this also allows initializing attributes that have
 * not been set by the caller to current values.  Inode lock is held
 * thoughout to prevent racing with another instance.
 *
 * Return: 0 on success, or a negative error on failure.
 */
पूर्णांक vfs_fileattr_set(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		     काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा fileattr old_ma = अणुपूर्ण;
	पूर्णांक err;

	अगर (!inode->i_op->fileattr_set)
		वापस -ENOIOCTLCMD;

	अगर (!inode_owner_or_capable(mnt_userns, inode))
		वापस -EPERM;

	inode_lock(inode);
	err = vfs_fileattr_get(dentry, &old_ma);
	अगर (!err) अणु
		/* initialize missing bits from old_ma */
		अगर (fa->flags_valid) अणु
			fa->fsx_xflags |= old_ma.fsx_xflags & ~FS_XFLAG_COMMON;
			fa->fsx_extsize = old_ma.fsx_extsize;
			fa->fsx_nextents = old_ma.fsx_nextents;
			fa->fsx_projid = old_ma.fsx_projid;
			fa->fsx_cowextsize = old_ma.fsx_cowextsize;
		पूर्ण अन्यथा अणु
			fa->flags |= old_ma.flags & ~FS_COMMON_FL;
		पूर्ण
		err = fileattr_set_prepare(inode, &old_ma, fa);
		अगर (!err)
			err = inode->i_op->fileattr_set(mnt_userns, dentry, fa);
	पूर्ण
	inode_unlock(inode);

	वापस err;
पूर्ण
EXPORT_SYMBOL(vfs_fileattr_set);

अटल पूर्णांक ioctl_getflags(काष्ठा file *file, अचिन्हित पूर्णांक __user *argp)
अणु
	काष्ठा fileattr fa = अणु .flags_valid = true पूर्ण; /* hपूर्णांक only */
	पूर्णांक err;

	err = vfs_fileattr_get(file->f_path.dentry, &fa);
	अगर (!err)
		err = put_user(fa.flags, argp);
	वापस err;
पूर्ण

अटल पूर्णांक ioctl_setflags(काष्ठा file *file, अचिन्हित पूर्णांक __user *argp)
अणु
	काष्ठा user_namespace *mnt_userns = file_mnt_user_ns(file);
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा fileattr fa;
	अचिन्हित पूर्णांक flags;
	पूर्णांक err;

	err = get_user(flags, argp);
	अगर (!err) अणु
		err = mnt_want_ग_लिखो_file(file);
		अगर (!err) अणु
			fileattr_fill_flags(&fa, flags);
			err = vfs_fileattr_set(mnt_userns, dentry, &fa);
			mnt_drop_ग_लिखो_file(file);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ioctl_fsgetxattr(काष्ठा file *file, व्योम __user *argp)
अणु
	काष्ठा fileattr fa = अणु .fsx_valid = true पूर्ण; /* hपूर्णांक only */
	पूर्णांक err;

	err = vfs_fileattr_get(file->f_path.dentry, &fa);
	अगर (!err)
		err = copy_fsxattr_to_user(&fa, argp);

	वापस err;
पूर्ण

अटल पूर्णांक ioctl_fssetxattr(काष्ठा file *file, व्योम __user *argp)
अणु
	काष्ठा user_namespace *mnt_userns = file_mnt_user_ns(file);
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा fileattr fa;
	पूर्णांक err;

	err = copy_fsxattr_from_user(&fa, argp);
	अगर (!err) अणु
		err = mnt_want_ग_लिखो_file(file);
		अगर (!err) अणु
			err = vfs_fileattr_set(mnt_userns, dentry, &fa);
			mnt_drop_ग_लिखो_file(file);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/*
 * करो_vfs_ioctl() is not क्रम drivers and not पूर्णांकended to be EXPORT_SYMBOL()'d.
 * It's just a simple helper क्रम sys_ioctl and compat_sys_ioctl.
 *
 * When you add any new common ioctls to the चयनes above and below,
 * please ensure they have compatible arguments in compat mode.
 */
अटल पूर्णांक करो_vfs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक fd,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा inode *inode = file_inode(filp);

	चयन (cmd) अणु
	हाल FIOCLEX:
		set_बंद_on_exec(fd, 1);
		वापस 0;

	हाल FIONCLEX:
		set_बंद_on_exec(fd, 0);
		वापस 0;

	हाल FIONBIO:
		वापस ioctl_fionbio(filp, argp);

	हाल FIOASYNC:
		वापस ioctl_fioasync(fd, filp, argp);

	हाल FIOQSIZE:
		अगर (S_ISसूची(inode->i_mode) || S_ISREG(inode->i_mode) ||
		    S_ISLNK(inode->i_mode)) अणु
			loff_t res = inode_get_bytes(inode);
			वापस copy_to_user(argp, &res, माप(res)) ?
					    -EFAULT : 0;
		पूर्ण

		वापस -ENOTTY;

	हाल FIFREEZE:
		वापस ioctl_fsमुक्तze(filp);

	हाल FITHAW:
		वापस ioctl_fsthaw(filp);

	हाल FS_IOC_FIEMAP:
		वापस ioctl_fiemap(filp, argp);

	हाल FIGETBSZ:
		/* anon_bdev fileप्रणालीs may not have a block size */
		अगर (!inode->i_sb->s_blocksize)
			वापस -EINVAL;

		वापस put_user(inode->i_sb->s_blocksize, (पूर्णांक __user *)argp);

	हाल FICLONE:
		वापस ioctl_file_clone(filp, arg, 0, 0, 0);

	हाल FICLONदुस्फल:
		वापस ioctl_file_clone_range(filp, argp);

	हाल FIDEDUPदुस्फल:
		वापस ioctl_file_dedupe_range(filp, argp);

	हाल FIONREAD:
		अगर (!S_ISREG(inode->i_mode))
			वापस vfs_ioctl(filp, cmd, arg);

		वापस put_user(i_size_पढ़ो(inode) - filp->f_pos,
				(पूर्णांक __user *)argp);

	हाल FS_IOC_GETFLAGS:
		वापस ioctl_getflags(filp, argp);

	हाल FS_IOC_SETFLAGS:
		वापस ioctl_setflags(filp, argp);

	हाल FS_IOC_FSGETXATTR:
		वापस ioctl_fsgetxattr(filp, argp);

	हाल FS_IOC_FSSETXATTR:
		वापस ioctl_fssetxattr(filp, argp);

	शेष:
		अगर (S_ISREG(inode->i_mode))
			वापस file_ioctl(filp, cmd, argp);
		अवरोध;
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

SYSCALL_DEFINE3(ioctl, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, cmd, अचिन्हित दीर्घ, arg)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक error;

	अगर (!f.file)
		वापस -EBADF;

	error = security_file_ioctl(f.file, cmd, arg);
	अगर (error)
		जाओ out;

	error = करो_vfs_ioctl(f.file, fd, cmd, arg);
	अगर (error == -ENOIOCTLCMD)
		error = vfs_ioctl(f.file, cmd, arg);

out:
	fdput(f);
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/**
 * compat_ptr_ioctl - generic implementation of .compat_ioctl file operation
 *
 * This is not normally called as a function, but instead set in काष्ठा
 * file_operations as
 *
 *     .compat_ioctl = compat_ptr_ioctl,
 *
 * On most architectures, the compat_ptr_ioctl() just passes all arguments
 * to the corresponding ->ioctl handler. The exception is arch/s390, where
 * compat_ptr() clears the top bit of a 32-bit poपूर्णांकer value, so user space
 * poपूर्णांकers to the second 2GB alias the first 2GB, as is the हाल क्रम
 * native 32-bit s390 user space.
 *
 * The compat_ptr_ioctl() function must thereक्रमe be used only with ioctl
 * functions that either ignore the argument or pass a poपूर्णांकer to a
 * compatible data type.
 *
 * If any ioctl command handled by fops->unlocked_ioctl passes a plain
 * पूर्णांकeger instead of a poपूर्णांकer, or any of the passed data types
 * is incompatible between 32-bit and 64-bit architectures, a proper
 * handler is required instead of compat_ptr_ioctl.
 */
दीर्घ compat_ptr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (!file->f_op->unlocked_ioctl)
		वापस -ENOIOCTLCMD;

	वापस file->f_op->unlocked_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
EXPORT_SYMBOL(compat_ptr_ioctl);

COMPAT_SYSCALL_DEFINE3(ioctl, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, cmd,
		       compat_uदीर्घ_t, arg)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक error;

	अगर (!f.file)
		वापस -EBADF;

	/* RED-PEN how should LSM module know it's handling 32bit? */
	error = security_file_ioctl(f.file, cmd, arg);
	अगर (error)
		जाओ out;

	चयन (cmd) अणु
	/* FICLONE takes an पूर्णांक argument, so करोn't use compat_ptr() */
	हाल FICLONE:
		error = ioctl_file_clone(f.file, arg, 0, 0, 0);
		अवरोध;

#अगर defined(CONFIG_X86_64)
	/* these get messy on amd64 due to alignment dअगरferences */
	हाल FS_IOC_RESVSP_32:
	हाल FS_IOC_RESVSP64_32:
		error = compat_ioctl_pपुनः_स्मृतिate(f.file, 0, compat_ptr(arg));
		अवरोध;
	हाल FS_IOC_UNRESVSP_32:
	हाल FS_IOC_UNRESVSP64_32:
		error = compat_ioctl_pपुनः_स्मृतिate(f.file, FALLOC_FL_PUNCH_HOLE,
				compat_ptr(arg));
		अवरोध;
	हाल FS_IOC_ZERO_RANGE_32:
		error = compat_ioctl_pपुनः_स्मृतिate(f.file, FALLOC_FL_ZERO_RANGE,
				compat_ptr(arg));
		अवरोध;
#पूर्ण_अगर

	/*
	 * These access 32-bit values anyway so no further handling is
	 * necessary.
	 */
	हाल FS_IOC32_GETFLAGS:
	हाल FS_IOC32_SETFLAGS:
		cmd = (cmd == FS_IOC32_GETFLAGS) ?
			FS_IOC_GETFLAGS : FS_IOC_SETFLAGS;
		fallthrough;
	/*
	 * everything अन्यथा in करो_vfs_ioctl() takes either a compatible
	 * poपूर्णांकer argument or no argument -- call it with a modअगरied
	 * argument.
	 */
	शेष:
		error = करो_vfs_ioctl(f.file, fd, cmd,
				     (अचिन्हित दीर्घ)compat_ptr(arg));
		अगर (error != -ENOIOCTLCMD)
			अवरोध;

		अगर (f.file->f_op->compat_ioctl)
			error = f.file->f_op->compat_ioctl(f.file, cmd, arg);
		अगर (error == -ENOIOCTLCMD)
			error = -ENOTTY;
		अवरोध;
	पूर्ण

 out:
	fdput(f);

	वापस error;
पूर्ण
#पूर्ण_अगर

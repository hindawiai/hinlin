<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ioctl.c - NILFS ioctl operations.
 *
 * Copyright (C) 2007, 2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#समावेश <linux/fs.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/capability.h>	/* capable() */
#समावेश <linux/uaccess.h>	/* copy_from_user(), copy_to_user() */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/compat.h>	/* compat_ptr() */
#समावेश <linux/mount.h>	/* mnt_want_ग_लिखो_file(), mnt_drop_ग_लिखो_file() */
#समावेश <linux/buffer_head.h>
#समावेश <linux/fileattr.h>
#समावेश "nilfs.h"
#समावेश "segment.h"
#समावेश "bmap.h"
#समावेश "cpfile.h"
#समावेश "sufile.h"
#समावेश "dat.h"

/**
 * nilfs_ioctl_wrap_copy - wrapping function of get/set metadata info
 * @nilfs: nilfs object
 * @argv: vector of arguments from userspace
 * @dir: set of direction flags
 * @करोfunc: concrete function of get/set metadata info
 *
 * Description: nilfs_ioctl_wrap_copy() माला_लो/sets metadata info by means of
 * calling करोfunc() function on the basis of @argv argument.
 *
 * Return Value: On success, 0 is वापसed and requested metadata info
 * is copied पूर्णांकo userspace. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EINVAL - Invalid arguments from userspace.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EFAULT - Failure during execution of requested operation.
 */
अटल पूर्णांक nilfs_ioctl_wrap_copy(काष्ठा the_nilfs *nilfs,
				 काष्ठा nilfs_argv *argv, पूर्णांक dir,
				 sमाप_प्रकार (*करोfunc)(काष्ठा the_nilfs *,
						   __u64 *, पूर्णांक,
						   व्योम *, माप_प्रकार, माप_प्रकार))
अणु
	व्योम *buf;
	व्योम __user *base = (व्योम __user *)(अचिन्हित दीर्घ)argv->v_base;
	माप_प्रकार maxmembs, total, n;
	sमाप_प्रकार nr;
	पूर्णांक ret, i;
	__u64 pos, ppos;

	अगर (argv->v_nmembs == 0)
		वापस 0;

	अगर (argv->v_size > PAGE_SIZE)
		वापस -EINVAL;

	/*
	 * Reject pairs of a start item position (argv->v_index) and a
	 * total count (argv->v_nmembs) which leads position 'pos' to
	 * overflow by the increment at the end of the loop.
	 */
	अगर (argv->v_index > ~(__u64)0 - argv->v_nmembs)
		वापस -EINVAL;

	buf = (व्योम *)__get_मुक्त_pages(GFP_NOFS, 0);
	अगर (unlikely(!buf))
		वापस -ENOMEM;
	maxmembs = PAGE_SIZE / argv->v_size;

	ret = 0;
	total = 0;
	pos = argv->v_index;
	क्रम (i = 0; i < argv->v_nmembs; i += n) अणु
		n = (argv->v_nmembs - i < maxmembs) ?
			argv->v_nmembs - i : maxmembs;
		अगर ((dir & _IOC_WRITE) &&
		    copy_from_user(buf, base + argv->v_size * i,
				   argv->v_size * n)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ppos = pos;
		nr = करोfunc(nilfs, &pos, argv->v_flags, buf, argv->v_size,
			       n);
		अगर (nr < 0) अणु
			ret = nr;
			अवरोध;
		पूर्ण
		अगर ((dir & _IOC_READ) &&
		    copy_to_user(base + argv->v_size * i, buf,
				 argv->v_size * nr)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		total += nr;
		अगर ((माप_प्रकार)nr < n)
			अवरोध;
		अगर (pos == ppos)
			pos += n;
	पूर्ण
	argv->v_nmembs = total;

	मुक्त_pages((अचिन्हित दीर्घ)buf, 0);
	वापस ret;
पूर्ण

/**
 * nilfs_fileattr_get - ioctl to support lsattr
 */
पूर्णांक nilfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	fileattr_fill_flags(fa, NILFS_I(inode)->i_flags & FS_FL_USER_VISIBLE);

	वापस 0;
पूर्ण

/**
 * nilfs_fileattr_set - ioctl to support chattr
 */
पूर्णांक nilfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
		       काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा nilfs_transaction_info ti;
	अचिन्हित पूर्णांक flags, oldflags;
	पूर्णांक ret;

	अगर (fileattr_has_fsx(fa))
		वापस -EOPNOTSUPP;

	flags = nilfs_mask_flags(inode->i_mode, fa->flags);

	ret = nilfs_transaction_begin(inode->i_sb, &ti, 0);
	अगर (ret)
		वापस ret;

	oldflags = NILFS_I(inode)->i_flags & ~FS_FL_USER_MODIFIABLE;
	NILFS_I(inode)->i_flags = oldflags | (flags & FS_FL_USER_MODIFIABLE);

	nilfs_set_inode_flags(inode);
	inode->i_स_समय = current_समय(inode);
	अगर (IS_SYNC(inode))
		nilfs_set_transaction_flag(NILFS_TI_SYNC);

	nilfs_mark_inode_dirty(inode);
	वापस nilfs_transaction_commit(inode->i_sb);
पूर्ण

/**
 * nilfs_ioctl_getversion - get info about a file's version (generation number)
 */
अटल पूर्णांक nilfs_ioctl_getversion(काष्ठा inode *inode, व्योम __user *argp)
अणु
	वापस put_user(inode->i_generation, (पूर्णांक __user *)argp);
पूर्ण

/**
 * nilfs_ioctl_change_cpmode - change checkpoपूर्णांक mode (checkpoपूर्णांक/snapshot)
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_change_cpmode() function changes mode of
 * given checkpoपूर्णांक between checkpoपूर्णांक and snapshot state. This ioctl
 * is used in chcp and mkcp utilities.
 *
 * Return Value: On success, 0 is वापसed and mode of a checkpoपूर्णांक is
 * changed. On error, one of the following negative error codes
 * is वापसed.
 *
 * %-EPERM - Operation not permitted.
 *
 * %-EFAULT - Failure during checkpoपूर्णांक mode changing.
 */
अटल पूर्णांक nilfs_ioctl_change_cpmode(काष्ठा inode *inode, काष्ठा file *filp,
				     अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा nilfs_transaction_info ti;
	काष्ठा nilfs_cpmode cpmode;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	ret = -EFAULT;
	अगर (copy_from_user(&cpmode, argp, माप(cpmode)))
		जाओ out;

	mutex_lock(&nilfs->ns_snapshot_mount_mutex);

	nilfs_transaction_begin(inode->i_sb, &ti, 0);
	ret = nilfs_cpfile_change_cpmode(
		nilfs->ns_cpfile, cpmode.cm_cno, cpmode.cm_mode);
	अगर (unlikely(ret < 0))
		nilfs_transaction_पात(inode->i_sb);
	अन्यथा
		nilfs_transaction_commit(inode->i_sb); /* never fails */

	mutex_unlock(&nilfs->ns_snapshot_mount_mutex);
out:
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_delete_checkpoपूर्णांक - हटाओ checkpoपूर्णांक
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_delete_checkpoपूर्णांक() function हटाओs
 * checkpoपूर्णांक from NILFS2 file प्रणाली. This ioctl is used in rmcp
 * utility.
 *
 * Return Value: On success, 0 is वापसed and a checkpoपूर्णांक is
 * हटाओd. On error, one of the following negative error codes
 * is वापसed.
 *
 * %-EPERM - Operation not permitted.
 *
 * %-EFAULT - Failure during checkpoपूर्णांक removing.
 */
अटल पूर्णांक
nilfs_ioctl_delete_checkpoपूर्णांक(काष्ठा inode *inode, काष्ठा file *filp,
			      अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा nilfs_transaction_info ti;
	__u64 cno;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	ret = -EFAULT;
	अगर (copy_from_user(&cno, argp, माप(cno)))
		जाओ out;

	nilfs_transaction_begin(inode->i_sb, &ti, 0);
	ret = nilfs_cpfile_delete_checkpoपूर्णांक(nilfs->ns_cpfile, cno);
	अगर (unlikely(ret < 0))
		nilfs_transaction_पात(inode->i_sb);
	अन्यथा
		nilfs_transaction_commit(inode->i_sb); /* never fails */
out:
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_करो_get_cpinfo - callback method getting info about checkpoपूर्णांकs
 * @nilfs: nilfs object
 * @posp: poपूर्णांकer on array of checkpoपूर्णांक's numbers
 * @flags: checkpoपूर्णांक mode (checkpoपूर्णांक or snapshot)
 * @buf: buffer क्रम storing checkponts' info
 * @size: size in bytes of one checkpoपूर्णांक info item in array
 * @nmembs: number of checkpoपूर्णांकs in array (numbers and infos)
 *
 * Description: nilfs_ioctl_करो_get_cpinfo() function वापसs info about
 * requested checkpoपूर्णांकs. The NILFS_IOCTL_GET_CPINFO ioctl is used in
 * lscp utility and by nilfs_cleanerd daemon.
 *
 * Return value: count of nilfs_cpinfo काष्ठाures in output buffer.
 */
अटल sमाप_प्रकार
nilfs_ioctl_करो_get_cpinfo(काष्ठा the_nilfs *nilfs, __u64 *posp, पूर्णांक flags,
			  व्योम *buf, माप_प्रकार size, माप_प्रकार nmembs)
अणु
	पूर्णांक ret;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	ret = nilfs_cpfile_get_cpinfo(nilfs->ns_cpfile, posp, flags, buf,
				      size, nmembs);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_get_cpstat - get checkpoपूर्णांकs statistics
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_get_cpstat() वापसs inक्रमmation about checkpoपूर्णांकs.
 * The NILFS_IOCTL_GET_CPSTAT ioctl is used by lscp, rmcp utilities
 * and by nilfs_cleanerd daemon.
 *
 * Return Value: On success, 0 is वापसed, and checkpoपूर्णांकs inक्रमmation is
 * copied पूर्णांकo userspace poपूर्णांकer @argp. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EFAULT - Failure during getting checkpoपूर्णांकs statistics.
 */
अटल पूर्णांक nilfs_ioctl_get_cpstat(काष्ठा inode *inode, काष्ठा file *filp,
				  अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा nilfs_cpstat cpstat;
	पूर्णांक ret;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	ret = nilfs_cpfile_get_stat(nilfs->ns_cpfile, &cpstat);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	अगर (ret < 0)
		वापस ret;

	अगर (copy_to_user(argp, &cpstat, माप(cpstat)))
		ret = -EFAULT;
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_करो_get_suinfo - callback method getting segment usage info
 * @nilfs: nilfs object
 * @posp: poपूर्णांकer on array of segment numbers
 * @flags: *not used*
 * @buf: buffer क्रम storing suinfo array
 * @size: size in bytes of one suinfo item in array
 * @nmembs: count of segment numbers and suinfos in array
 *
 * Description: nilfs_ioctl_करो_get_suinfo() function वापसs segment usage
 * info about requested segments. The NILFS_IOCTL_GET_SUINFO ioctl is used
 * in lssu, nilfs_resize utilities and by nilfs_cleanerd daemon.
 *
 * Return value: count of nilfs_suinfo काष्ठाures in output buffer.
 */
अटल sमाप_प्रकार
nilfs_ioctl_करो_get_suinfo(काष्ठा the_nilfs *nilfs, __u64 *posp, पूर्णांक flags,
			  व्योम *buf, माप_प्रकार size, माप_प्रकार nmembs)
अणु
	पूर्णांक ret;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	ret = nilfs_sufile_get_suinfo(nilfs->ns_sufile, *posp, buf, size,
				      nmembs);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_get_sustat - get segment usage statistics
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_get_sustat() वापसs segment usage statistics.
 * The NILFS_IOCTL_GET_SUSTAT ioctl is used in lssu, nilfs_resize utilities
 * and by nilfs_cleanerd daemon.
 *
 * Return Value: On success, 0 is वापसed, and segment usage inक्रमmation is
 * copied पूर्णांकo userspace poपूर्णांकer @argp. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EFAULT - Failure during getting segment usage statistics.
 */
अटल पूर्णांक nilfs_ioctl_get_sustat(काष्ठा inode *inode, काष्ठा file *filp,
				  अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा nilfs_sustat sustat;
	पूर्णांक ret;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	ret = nilfs_sufile_get_stat(nilfs->ns_sufile, &sustat);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	अगर (ret < 0)
		वापस ret;

	अगर (copy_to_user(argp, &sustat, माप(sustat)))
		ret = -EFAULT;
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_करो_get_vinfo - callback method getting भव blocks info
 * @nilfs: nilfs object
 * @posp: *not used*
 * @flags: *not used*
 * @buf: buffer क्रम storing array of nilfs_vinfo काष्ठाures
 * @size: size in bytes of one vinfo item in array
 * @nmembs: count of vinfos in array
 *
 * Description: nilfs_ioctl_करो_get_vinfo() function वापसs inक्रमmation
 * on भव block addresses. The NILFS_IOCTL_GET_VINFO ioctl is used
 * by nilfs_cleanerd daemon.
 *
 * Return value: count of nilfs_vinfo काष्ठाures in output buffer.
 */
अटल sमाप_प्रकार
nilfs_ioctl_करो_get_vinfo(काष्ठा the_nilfs *nilfs, __u64 *posp, पूर्णांक flags,
			 व्योम *buf, माप_प्रकार size, माप_प्रकार nmembs)
अणु
	पूर्णांक ret;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	ret = nilfs_dat_get_vinfo(nilfs->ns_dat, buf, size, nmembs);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_करो_get_bdescs - callback method getting disk block descriptors
 * @nilfs: nilfs object
 * @posp: *not used*
 * @flags: *not used*
 * @buf: buffer क्रम storing array of nilfs_bdesc काष्ठाures
 * @size: size in bytes of one bdesc item in array
 * @nmembs: count of bdescs in array
 *
 * Description: nilfs_ioctl_करो_get_bdescs() function वापसs inक्रमmation
 * about descriptors of disk block numbers. The NILFS_IOCTL_GET_BDESCS ioctl
 * is used by nilfs_cleanerd daemon.
 *
 * Return value: count of nilfs_bdescs काष्ठाures in output buffer.
 */
अटल sमाप_प्रकार
nilfs_ioctl_करो_get_bdescs(काष्ठा the_nilfs *nilfs, __u64 *posp, पूर्णांक flags,
			  व्योम *buf, माप_प्रकार size, माप_प्रकार nmembs)
अणु
	काष्ठा nilfs_bmap *bmap = NILFS_I(nilfs->ns_dat)->i_bmap;
	काष्ठा nilfs_bdesc *bdescs = buf;
	पूर्णांक ret, i;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	क्रम (i = 0; i < nmembs; i++) अणु
		ret = nilfs_bmap_lookup_at_level(bmap,
						 bdescs[i].bd_offset,
						 bdescs[i].bd_level + 1,
						 &bdescs[i].bd_blocknr);
		अगर (ret < 0) अणु
			अगर (ret != -ENOENT) अणु
				up_पढ़ो(&nilfs->ns_segctor_sem);
				वापस ret;
			पूर्ण
			bdescs[i].bd_blocknr = 0;
		पूर्ण
	पूर्ण
	up_पढ़ो(&nilfs->ns_segctor_sem);
	वापस nmembs;
पूर्ण

/**
 * nilfs_ioctl_get_bdescs - get disk block descriptors
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_करो_get_bdescs() function वापसs inक्रमmation
 * about descriptors of disk block numbers. The NILFS_IOCTL_GET_BDESCS ioctl
 * is used by nilfs_cleanerd daemon.
 *
 * Return Value: On success, 0 is वापसed, and disk block descriptors are
 * copied पूर्णांकo userspace poपूर्णांकer @argp. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EINVAL - Invalid arguments from userspace.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EFAULT - Failure during getting disk block descriptors.
 */
अटल पूर्णांक nilfs_ioctl_get_bdescs(काष्ठा inode *inode, काष्ठा file *filp,
				  अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा nilfs_argv argv;
	पूर्णांक ret;

	अगर (copy_from_user(&argv, argp, माप(argv)))
		वापस -EFAULT;

	अगर (argv.v_size != माप(काष्ठा nilfs_bdesc))
		वापस -EINVAL;

	ret = nilfs_ioctl_wrap_copy(nilfs, &argv, _IOC_सूची(cmd),
				    nilfs_ioctl_करो_get_bdescs);
	अगर (ret < 0)
		वापस ret;

	अगर (copy_to_user(argp, &argv, माप(argv)))
		ret = -EFAULT;
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_move_inode_block - prepare data/node block क्रम moving by GC
 * @inode: inode object
 * @vdesc: descriptor of भव block number
 * @buffers: list of moving buffers
 *
 * Description: nilfs_ioctl_move_inode_block() function रेजिस्टरs data/node
 * buffer in the GC pagecache and submit पढ़ो request.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - Requested block करोesn't exist.
 *
 * %-EEXIST - Blocks conflict is detected.
 */
अटल पूर्णांक nilfs_ioctl_move_inode_block(काष्ठा inode *inode,
					काष्ठा nilfs_vdesc *vdesc,
					काष्ठा list_head *buffers)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक ret;

	अगर (vdesc->vd_flags == 0)
		ret = nilfs_gccache_submit_पढ़ो_data(
			inode, vdesc->vd_offset, vdesc->vd_blocknr,
			vdesc->vd_vblocknr, &bh);
	अन्यथा
		ret = nilfs_gccache_submit_पढ़ो_node(
			inode, vdesc->vd_blocknr, vdesc->vd_vblocknr, &bh);

	अगर (unlikely(ret < 0)) अणु
		अगर (ret == -ENOENT)
			nilfs_crit(inode->i_sb,
				   "%s: invalid virtual block address (%s): ino=%llu, cno=%llu, offset=%llu, blocknr=%llu, vblocknr=%llu",
				   __func__, vdesc->vd_flags ? "node" : "data",
				   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_ino,
				   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_cno,
				   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_offset,
				   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_blocknr,
				   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_vblocknr);
		वापस ret;
	पूर्ण
	अगर (unlikely(!list_empty(&bh->b_assoc_buffers))) अणु
		nilfs_crit(inode->i_sb,
			   "%s: conflicting %s buffer: ino=%llu, cno=%llu, offset=%llu, blocknr=%llu, vblocknr=%llu",
			   __func__, vdesc->vd_flags ? "node" : "data",
			   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_ino,
			   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_cno,
			   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_offset,
			   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_blocknr,
			   (अचिन्हित दीर्घ दीर्घ)vdesc->vd_vblocknr);
		brअन्यथा(bh);
		वापस -EEXIST;
	पूर्ण
	list_add_tail(&bh->b_assoc_buffers, buffers);
	वापस 0;
पूर्ण

/**
 * nilfs_ioctl_move_blocks - move valid inode's blocks during garbage collection
 * @sb: superblock object
 * @argv: vector of arguments from userspace
 * @buf: array of nilfs_vdesc काष्ठाures
 *
 * Description: nilfs_ioctl_move_blocks() function पढ़ोs valid data/node
 * blocks that garbage collector specअगरied with the array of nilfs_vdesc
 * काष्ठाures and stores them पूर्णांकo page caches of GC inodes.
 *
 * Return Value: Number of processed nilfs_vdesc काष्ठाures or
 * error code, otherwise.
 */
अटल पूर्णांक nilfs_ioctl_move_blocks(काष्ठा super_block *sb,
				   काष्ठा nilfs_argv *argv, व्योम *buf)
अणु
	माप_प्रकार nmembs = argv->v_nmembs;
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा inode *inode;
	काष्ठा nilfs_vdesc *vdesc;
	काष्ठा buffer_head *bh, *n;
	LIST_HEAD(buffers);
	ino_t ino;
	__u64 cno;
	पूर्णांक i, ret;

	क्रम (i = 0, vdesc = buf; i < nmembs; ) अणु
		ino = vdesc->vd_ino;
		cno = vdesc->vd_cno;
		inode = nilfs_iget_क्रम_gc(sb, ino, cno);
		अगर (IS_ERR(inode)) अणु
			ret = PTR_ERR(inode);
			जाओ failed;
		पूर्ण
		अगर (list_empty(&NILFS_I(inode)->i_dirty)) अणु
			/*
			 * Add the inode to GC inode list. Garbage Collection
			 * is serialized and no two processes manipulate the
			 * list simultaneously.
			 */
			igrab(inode);
			list_add(&NILFS_I(inode)->i_dirty,
				 &nilfs->ns_gc_inodes);
		पूर्ण

		करो अणु
			ret = nilfs_ioctl_move_inode_block(inode, vdesc,
							   &buffers);
			अगर (unlikely(ret < 0)) अणु
				iput(inode);
				जाओ failed;
			पूर्ण
			vdesc++;
		पूर्ण जबतक (++i < nmembs &&
			 vdesc->vd_ino == ino && vdesc->vd_cno == cno);

		iput(inode); /* The inode still reमुख्यs in GC inode list */
	पूर्ण

	list_क्रम_each_entry_safe(bh, n, &buffers, b_assoc_buffers) अणु
		ret = nilfs_gccache_रुको_and_mark_dirty(bh);
		अगर (unlikely(ret < 0)) अणु
			WARN_ON(ret == -EEXIST);
			जाओ failed;
		पूर्ण
		list_del_init(&bh->b_assoc_buffers);
		brअन्यथा(bh);
	पूर्ण
	वापस nmembs;

 failed:
	list_क्रम_each_entry_safe(bh, n, &buffers, b_assoc_buffers) अणु
		list_del_init(&bh->b_assoc_buffers);
		brअन्यथा(bh);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_delete_checkpoपूर्णांकs - delete checkpoपूर्णांकs
 * @nilfs: nilfs object
 * @argv: vector of arguments from userspace
 * @buf: array of periods of checkpoपूर्णांकs numbers
 *
 * Description: nilfs_ioctl_delete_checkpoपूर्णांकs() function deletes checkpoपूर्णांकs
 * in the period from p_start to p_end, excluding p_end itself. The checkpoपूर्णांकs
 * which have been alपढ़ोy deleted are ignored.
 *
 * Return Value: Number of processed nilfs_period काष्ठाures or
 * error code, otherwise.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EINVAL - invalid checkpoपूर्णांकs.
 */
अटल पूर्णांक nilfs_ioctl_delete_checkpoपूर्णांकs(काष्ठा the_nilfs *nilfs,
					  काष्ठा nilfs_argv *argv, व्योम *buf)
अणु
	माप_प्रकार nmembs = argv->v_nmembs;
	काष्ठा inode *cpfile = nilfs->ns_cpfile;
	काष्ठा nilfs_period *periods = buf;
	पूर्णांक ret, i;

	क्रम (i = 0; i < nmembs; i++) अणु
		ret = nilfs_cpfile_delete_checkpoपूर्णांकs(
			cpfile, periods[i].p_start, periods[i].p_end);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस nmembs;
पूर्ण

/**
 * nilfs_ioctl_मुक्त_vblocknrs - मुक्त भव block numbers
 * @nilfs: nilfs object
 * @argv: vector of arguments from userspace
 * @buf: array of भव block numbers
 *
 * Description: nilfs_ioctl_मुक्त_vblocknrs() function मुक्तs
 * the भव block numbers specअगरied by @buf and @argv->v_nmembs.
 *
 * Return Value: Number of processed भव block numbers or
 * error code, otherwise.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - The भव block number have not been allocated.
 */
अटल पूर्णांक nilfs_ioctl_मुक्त_vblocknrs(काष्ठा the_nilfs *nilfs,
				      काष्ठा nilfs_argv *argv, व्योम *buf)
अणु
	माप_प्रकार nmembs = argv->v_nmembs;
	पूर्णांक ret;

	ret = nilfs_dat_मुक्तv(nilfs->ns_dat, buf, nmembs);

	वापस (ret < 0) ? ret : nmembs;
पूर्ण

/**
 * nilfs_ioctl_mark_blocks_dirty - mark blocks dirty
 * @nilfs: nilfs object
 * @argv: vector of arguments from userspace
 * @buf: array of block descriptors
 *
 * Description: nilfs_ioctl_mark_blocks_dirty() function marks
 * metadata file or data blocks as dirty.
 *
 * Return Value: Number of processed block descriptors or
 * error code, otherwise.
 *
 * %-ENOMEM - Insufficient memory available.
 *
 * %-EIO - I/O error
 *
 * %-ENOENT - the specअगरied block करोes not exist (hole block)
 */
अटल पूर्णांक nilfs_ioctl_mark_blocks_dirty(काष्ठा the_nilfs *nilfs,
					 काष्ठा nilfs_argv *argv, व्योम *buf)
अणु
	माप_प्रकार nmembs = argv->v_nmembs;
	काष्ठा nilfs_bmap *bmap = NILFS_I(nilfs->ns_dat)->i_bmap;
	काष्ठा nilfs_bdesc *bdescs = buf;
	काष्ठा buffer_head *bh;
	पूर्णांक ret, i;

	क्रम (i = 0; i < nmembs; i++) अणु
		/* XXX: use macro or अंतरभूत func to check liveness */
		ret = nilfs_bmap_lookup_at_level(bmap,
						 bdescs[i].bd_offset,
						 bdescs[i].bd_level + 1,
						 &bdescs[i].bd_blocknr);
		अगर (ret < 0) अणु
			अगर (ret != -ENOENT)
				वापस ret;
			bdescs[i].bd_blocknr = 0;
		पूर्ण
		अगर (bdescs[i].bd_blocknr != bdescs[i].bd_oblocknr)
			/* skip dead block */
			जारी;
		अगर (bdescs[i].bd_level == 0) अणु
			ret = nilfs_mdt_get_block(nilfs->ns_dat,
						  bdescs[i].bd_offset,
						  false, शून्य, &bh);
			अगर (unlikely(ret)) अणु
				WARN_ON(ret == -ENOENT);
				वापस ret;
			पूर्ण
			mark_buffer_dirty(bh);
			nilfs_mdt_mark_dirty(nilfs->ns_dat);
			put_bh(bh);
		पूर्ण अन्यथा अणु
			ret = nilfs_bmap_mark(bmap, bdescs[i].bd_offset,
					      bdescs[i].bd_level);
			अगर (ret < 0) अणु
				WARN_ON(ret == -ENOENT);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस nmembs;
पूर्ण

पूर्णांक nilfs_ioctl_prepare_clean_segments(काष्ठा the_nilfs *nilfs,
				       काष्ठा nilfs_argv *argv, व्योम **kbufs)
अणु
	स्थिर अक्षर *msg;
	पूर्णांक ret;

	ret = nilfs_ioctl_delete_checkpoपूर्णांकs(nilfs, &argv[1], kbufs[1]);
	अगर (ret < 0) अणु
		/*
		 * can safely पात because checkpoपूर्णांकs can be हटाओd
		 * independently.
		 */
		msg = "cannot delete checkpoints";
		जाओ failed;
	पूर्ण
	ret = nilfs_ioctl_मुक्त_vblocknrs(nilfs, &argv[2], kbufs[2]);
	अगर (ret < 0) अणु
		/*
		 * can safely पात because DAT file is updated atomically
		 * using a copy-on-ग_लिखो technique.
		 */
		msg = "cannot delete virtual blocks from DAT file";
		जाओ failed;
	पूर्ण
	ret = nilfs_ioctl_mark_blocks_dirty(nilfs, &argv[3], kbufs[3]);
	अगर (ret < 0) अणु
		/*
		 * can safely पात because the operation is nondeकाष्ठाive.
		 */
		msg = "cannot mark copying blocks dirty";
		जाओ failed;
	पूर्ण
	वापस 0;

 failed:
	nilfs_err(nilfs->ns_sb, "error %d preparing GC: %s", ret, msg);
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_clean_segments - clean segments
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_clean_segments() function makes garbage
 * collection operation in the environment of requested parameters
 * from userspace. The NILFS_IOCTL_CLEAN_SEGMENTS ioctl is used by
 * nilfs_cleanerd daemon.
 *
 * Return Value: On success, 0 is वापसed or error code, otherwise.
 */
अटल पूर्णांक nilfs_ioctl_clean_segments(काष्ठा inode *inode, काष्ठा file *filp,
				      अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा nilfs_argv argv[5];
	अटल स्थिर माप_प्रकार argsz[5] = अणु
		माप(काष्ठा nilfs_vdesc),
		माप(काष्ठा nilfs_period),
		माप(__u64),
		माप(काष्ठा nilfs_bdesc),
		माप(__u64),
	पूर्ण;
	व्योम __user *base;
	व्योम *kbufs[5];
	काष्ठा the_nilfs *nilfs;
	माप_प्रकार len, nsegs;
	पूर्णांक n, ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	ret = -EFAULT;
	अगर (copy_from_user(argv, argp, माप(argv)))
		जाओ out;

	ret = -EINVAL;
	nsegs = argv[4].v_nmembs;
	अगर (argv[4].v_size != argsz[4])
		जाओ out;
	अगर (nsegs > अच_पूर्णांक_उच्च / माप(__u64))
		जाओ out;

	/*
	 * argv[4] poपूर्णांकs to segment numbers this ioctl cleans.  We
	 * use kदो_स्मृति() क्रम its buffer because memory used क्रम the
	 * segment numbers is enough small.
	 */
	kbufs[4] = memdup_user((व्योम __user *)(अचिन्हित दीर्घ)argv[4].v_base,
			       nsegs * माप(__u64));
	अगर (IS_ERR(kbufs[4])) अणु
		ret = PTR_ERR(kbufs[4]);
		जाओ out;
	पूर्ण
	nilfs = inode->i_sb->s_fs_info;

	क्रम (n = 0; n < 4; n++) अणु
		ret = -EINVAL;
		अगर (argv[n].v_size != argsz[n])
			जाओ out_मुक्त;

		अगर (argv[n].v_nmembs > nsegs * nilfs->ns_blocks_per_segment)
			जाओ out_मुक्त;

		अगर (argv[n].v_nmembs >= अच_पूर्णांक_उच्च / argv[n].v_size)
			जाओ out_मुक्त;

		len = argv[n].v_size * argv[n].v_nmembs;
		base = (व्योम __user *)(अचिन्हित दीर्घ)argv[n].v_base;
		अगर (len == 0) अणु
			kbufs[n] = शून्य;
			जारी;
		पूर्ण

		kbufs[n] = vदो_स्मृति(len);
		अगर (!kbufs[n]) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त;
		पूर्ण
		अगर (copy_from_user(kbufs[n], base, len)) अणु
			ret = -EFAULT;
			vमुक्त(kbufs[n]);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	/*
	 * nilfs_ioctl_move_blocks() will call nilfs_iget_क्रम_gc(),
	 * which will operates an inode list without blocking.
	 * To protect the list from concurrent operations,
	 * nilfs_ioctl_move_blocks should be atomic operation.
	 */
	अगर (test_and_set_bit(THE_NILFS_GC_RUNNING, &nilfs->ns_flags)) अणु
		ret = -EBUSY;
		जाओ out_मुक्त;
	पूर्ण

	ret = nilfs_ioctl_move_blocks(inode->i_sb, &argv[0], kbufs[0]);
	अगर (ret < 0) अणु
		nilfs_err(inode->i_sb,
			  "error %d preparing GC: cannot read source blocks",
			  ret);
	पूर्ण अन्यथा अणु
		अगर (nilfs_sb_need_update(nilfs))
			set_nilfs_disजारीd(nilfs);
		ret = nilfs_clean_segments(inode->i_sb, argv, kbufs);
	पूर्ण

	nilfs_हटाओ_all_gcinodes(nilfs);
	clear_nilfs_gc_running(nilfs);

out_मुक्त:
	जबतक (--n >= 0)
		vमुक्त(kbufs[n]);
	kमुक्त(kbufs[4]);
out:
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_sync - make a checkpoपूर्णांक
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_sync() function स्थिरructs a logical segment
 * क्रम checkpoपूर्णांकing.  This function guarantees that all modअगरied data
 * and metadata are written out to the device when it successfully
 * वापसed.
 *
 * Return Value: On success, 0 is retured. On errors, one of the following
 * negative error code is वापसed.
 *
 * %-EROFS - Read only fileप्रणाली.
 *
 * %-EIO - I/O error
 *
 * %-ENOSPC - No space left on device (only in a panic state).
 *
 * %-ERESTARTSYS - Interrupted.
 *
 * %-ENOMEM - Insufficient memory available.
 *
 * %-EFAULT - Failure during execution of requested operation.
 */
अटल पूर्णांक nilfs_ioctl_sync(काष्ठा inode *inode, काष्ठा file *filp,
			    अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	__u64 cno;
	पूर्णांक ret;
	काष्ठा the_nilfs *nilfs;

	ret = nilfs_स्थिरruct_segment(inode->i_sb);
	अगर (ret < 0)
		वापस ret;

	nilfs = inode->i_sb->s_fs_info;
	ret = nilfs_flush_device(nilfs);
	अगर (ret < 0)
		वापस ret;

	अगर (argp != शून्य) अणु
		करोwn_पढ़ो(&nilfs->ns_segctor_sem);
		cno = nilfs->ns_cno - 1;
		up_पढ़ो(&nilfs->ns_segctor_sem);
		अगर (copy_to_user(argp, &cno, माप(cno)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * nilfs_ioctl_resize - resize NILFS2 volume
 * @inode: inode object
 * @filp: file object
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Return Value: On success, 0 is वापसed or error code, otherwise.
 */
अटल पूर्णांक nilfs_ioctl_resize(काष्ठा inode *inode, काष्ठा file *filp,
			      व्योम __user *argp)
अणु
	__u64 newsize;
	पूर्णांक ret = -EPERM;

	अगर (!capable(CAP_SYS_ADMIN))
		जाओ out;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		जाओ out;

	ret = -EFAULT;
	अगर (copy_from_user(&newsize, argp, माप(newsize)))
		जाओ out_drop_ग_लिखो;

	ret = nilfs_resize_fs(inode->i_sb, newsize);

out_drop_ग_लिखो:
	mnt_drop_ग_लिखो_file(filp);
out:
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_trim_fs() - trim ioctl handle function
 * @inode: inode object
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_trim_fs is the FITRIM ioctl handle function. It
 * checks the arguments from userspace and calls nilfs_sufile_trim_fs, which
 * perक्रमms the actual trim operation.
 *
 * Return Value: On success, 0 is वापसed or negative error code, otherwise.
 */
अटल पूर्णांक nilfs_ioctl_trim_fs(काष्ठा inode *inode, व्योम __user *argp)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा request_queue *q = bdev_get_queue(nilfs->ns_bdev);
	काष्ठा fstrim_range range;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!blk_queue_discard(q))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&range, argp, माप(range)))
		वापस -EFAULT;

	range.minlen = max_t(u64, range.minlen, q->limits.discard_granularity);

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	ret = nilfs_sufile_trim_fs(nilfs->ns_sufile, &range);
	up_पढ़ो(&nilfs->ns_segctor_sem);

	अगर (ret < 0)
		वापस ret;

	अगर (copy_to_user(argp, &range, माप(range)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/**
 * nilfs_ioctl_set_alloc_range - limit range of segments to be allocated
 * @inode: inode object
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: nilfs_ioctl_set_alloc_range() function defines lower limit
 * of segments in bytes and upper limit of segments in bytes.
 * The NILFS_IOCTL_SET_ALLOC_RANGE is used by nilfs_resize utility.
 *
 * Return Value: On success, 0 is वापसed or error code, otherwise.
 */
अटल पूर्णांक nilfs_ioctl_set_alloc_range(काष्ठा inode *inode, व्योम __user *argp)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	__u64 range[2];
	__u64 minseg, maxseg;
	अचिन्हित दीर्घ segbytes;
	पूर्णांक ret = -EPERM;

	अगर (!capable(CAP_SYS_ADMIN))
		जाओ out;

	ret = -EFAULT;
	अगर (copy_from_user(range, argp, माप(__u64[2])))
		जाओ out;

	ret = -दुस्फल;
	अगर (range[1] > i_size_पढ़ो(inode->i_sb->s_bdev->bd_inode))
		जाओ out;

	segbytes = nilfs->ns_blocks_per_segment * nilfs->ns_blocksize;

	minseg = range[0] + segbytes - 1;
	करो_भाग(minseg, segbytes);
	maxseg = NILFS_SB2_OFFSET_BYTES(range[1]);
	करो_भाग(maxseg, segbytes);
	maxseg--;

	ret = nilfs_sufile_set_alloc_range(nilfs->ns_sufile, minseg, maxseg);
out:
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_get_info - wrapping function of get metadata info
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 * @membsz: size of an item in bytes
 * @करोfunc: concrete function of getting metadata info
 *
 * Description: nilfs_ioctl_get_info() माला_लो metadata info by means of
 * calling करोfunc() function.
 *
 * Return Value: On success, 0 is वापसed and requested metadata info
 * is copied पूर्णांकo userspace. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EINVAL - Invalid arguments from userspace.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EFAULT - Failure during execution of requested operation.
 */
अटल पूर्णांक nilfs_ioctl_get_info(काष्ठा inode *inode, काष्ठा file *filp,
				अचिन्हित पूर्णांक cmd, व्योम __user *argp,
				माप_प्रकार membsz,
				sमाप_प्रकार (*करोfunc)(काष्ठा the_nilfs *,
						  __u64 *, पूर्णांक,
						  व्योम *, माप_प्रकार, माप_प्रकार))

अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा nilfs_argv argv;
	पूर्णांक ret;

	अगर (copy_from_user(&argv, argp, माप(argv)))
		वापस -EFAULT;

	अगर (argv.v_size < membsz)
		वापस -EINVAL;

	ret = nilfs_ioctl_wrap_copy(nilfs, &argv, _IOC_सूची(cmd), करोfunc);
	अगर (ret < 0)
		वापस ret;

	अगर (copy_to_user(argp, &argv, माप(argv)))
		ret = -EFAULT;
	वापस ret;
पूर्ण

/**
 * nilfs_ioctl_set_suinfo - set segment usage info
 * @inode: inode object
 * @filp: file object
 * @cmd: ioctl's request code
 * @argp: poपूर्णांकer on argument from userspace
 *
 * Description: Expects an array of nilfs_suinfo_update काष्ठाures
 * encapsulated in nilfs_argv and updates the segment usage info
 * according to the flags in nilfs_suinfo_update.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the
 * following negative error codes is वापसed.
 *
 * %-EPERM - Not enough permissions
 *
 * %-EFAULT - Error copying input data
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EINVAL - Invalid values in input (segment number, flags or nblocks)
 */
अटल पूर्णांक nilfs_ioctl_set_suinfo(काष्ठा inode *inode, काष्ठा file *filp,
				अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा nilfs_transaction_info ti;
	काष्ठा nilfs_argv argv;
	माप_प्रकार len;
	व्योम __user *base;
	व्योम *kbuf;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	ret = -EFAULT;
	अगर (copy_from_user(&argv, argp, माप(argv)))
		जाओ out;

	ret = -EINVAL;
	अगर (argv.v_size < माप(काष्ठा nilfs_suinfo_update))
		जाओ out;

	अगर (argv.v_nmembs > nilfs->ns_nsegments)
		जाओ out;

	अगर (argv.v_nmembs >= अच_पूर्णांक_उच्च / argv.v_size)
		जाओ out;

	len = argv.v_size * argv.v_nmembs;
	अगर (!len) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	base = (व्योम __user *)(अचिन्हित दीर्घ)argv.v_base;
	kbuf = vदो_स्मृति(len);
	अगर (!kbuf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(kbuf, base, len)) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	nilfs_transaction_begin(inode->i_sb, &ti, 0);
	ret = nilfs_sufile_set_suinfo(nilfs->ns_sufile, kbuf, argv.v_size,
			argv.v_nmembs);
	अगर (unlikely(ret < 0))
		nilfs_transaction_पात(inode->i_sb);
	अन्यथा
		nilfs_transaction_commit(inode->i_sb); /* never fails */

out_मुक्त:
	vमुक्त(kbuf);
out:
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

दीर्घ nilfs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल FS_IOC_GETVERSION:
		वापस nilfs_ioctl_getversion(inode, argp);
	हाल NILFS_IOCTL_CHANGE_CPMODE:
		वापस nilfs_ioctl_change_cpmode(inode, filp, cmd, argp);
	हाल NILFS_IOCTL_DELETE_CHECKPOINT:
		वापस nilfs_ioctl_delete_checkpoपूर्णांक(inode, filp, cmd, argp);
	हाल NILFS_IOCTL_GET_CPINFO:
		वापस nilfs_ioctl_get_info(inode, filp, cmd, argp,
					    माप(काष्ठा nilfs_cpinfo),
					    nilfs_ioctl_करो_get_cpinfo);
	हाल NILFS_IOCTL_GET_CPSTAT:
		वापस nilfs_ioctl_get_cpstat(inode, filp, cmd, argp);
	हाल NILFS_IOCTL_GET_SUINFO:
		वापस nilfs_ioctl_get_info(inode, filp, cmd, argp,
					    माप(काष्ठा nilfs_suinfo),
					    nilfs_ioctl_करो_get_suinfo);
	हाल NILFS_IOCTL_SET_SUINFO:
		वापस nilfs_ioctl_set_suinfo(inode, filp, cmd, argp);
	हाल NILFS_IOCTL_GET_SUSTAT:
		वापस nilfs_ioctl_get_sustat(inode, filp, cmd, argp);
	हाल NILFS_IOCTL_GET_VINFO:
		वापस nilfs_ioctl_get_info(inode, filp, cmd, argp,
					    माप(काष्ठा nilfs_vinfo),
					    nilfs_ioctl_करो_get_vinfo);
	हाल NILFS_IOCTL_GET_BDESCS:
		वापस nilfs_ioctl_get_bdescs(inode, filp, cmd, argp);
	हाल NILFS_IOCTL_CLEAN_SEGMENTS:
		वापस nilfs_ioctl_clean_segments(inode, filp, cmd, argp);
	हाल NILFS_IOCTL_SYNC:
		वापस nilfs_ioctl_sync(inode, filp, cmd, argp);
	हाल NILFS_IOCTL_RESIZE:
		वापस nilfs_ioctl_resize(inode, filp, argp);
	हाल NILFS_IOCTL_SET_ALLOC_RANGE:
		वापस nilfs_ioctl_set_alloc_range(inode, argp);
	हाल FITRIM:
		वापस nilfs_ioctl_trim_fs(inode, argp);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
दीर्घ nilfs_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल FS_IOC32_GETVERSION:
		cmd = FS_IOC_GETVERSION;
		अवरोध;
	हाल NILFS_IOCTL_CHANGE_CPMODE:
	हाल NILFS_IOCTL_DELETE_CHECKPOINT:
	हाल NILFS_IOCTL_GET_CPINFO:
	हाल NILFS_IOCTL_GET_CPSTAT:
	हाल NILFS_IOCTL_GET_SUINFO:
	हाल NILFS_IOCTL_SET_SUINFO:
	हाल NILFS_IOCTL_GET_SUSTAT:
	हाल NILFS_IOCTL_GET_VINFO:
	हाल NILFS_IOCTL_GET_BDESCS:
	हाल NILFS_IOCTL_CLEAN_SEGMENTS:
	हाल NILFS_IOCTL_SYNC:
	हाल NILFS_IOCTL_RESIZE:
	हाल NILFS_IOCTL_SET_ALLOC_RANGE:
	हाल FITRIM:
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस nilfs_ioctl(filp, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

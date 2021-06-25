<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 1997-2004 Erez Zaकरोk
 * Copyright (C) 2001-2004 Stony Brook University
 * Copyright (C) 2004-2007 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mhalcrow@us.ibm.com>
 *   		Michael C. Thompson <mcthomps@us.ibm.com>
 */

#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/security.h>
#समावेश <linux/compat.h>
#समावेश <linux/fs_stack.h>
#समावेश "ecryptfs_kernel.h"

/*
 * ecryptfs_पढ़ो_update_aसमय
 *
 * generic_file_पढ़ो updates the aसमय of upper layer inode.  But, it
 * करोesn't give us a chance to update the aसमय of the lower layer
 * inode.  This function is a wrapper to generic_file_पढ़ो.  It
 * updates the aसमय of the lower level inode अगर generic_file_पढ़ो
 * वापसs without any errors. This is to be used only क्रम file पढ़ोs.
 * The function to be used क्रम directory पढ़ोs is ecryptfs_पढ़ो.
 */
अटल sमाप_प्रकार ecryptfs_पढ़ो_update_aसमय(काष्ठा kiocb *iocb,
				काष्ठा iov_iter *to)
अणु
	sमाप_प्रकार rc;
	काष्ठा path *path;
	काष्ठा file *file = iocb->ki_filp;

	rc = generic_file_पढ़ो_iter(iocb, to);
	अगर (rc >= 0) अणु
		path = ecryptfs_dentry_to_lower_path(file->f_path.dentry);
		touch_aसमय(path);
	पूर्ण
	वापस rc;
पूर्ण

काष्ठा ecryptfs_getdents_callback अणु
	काष्ठा dir_context ctx;
	काष्ठा dir_context *caller;
	काष्ठा super_block *sb;
	पूर्णांक filldir_called;
	पूर्णांक entries_written;
पूर्ण;

/* Inspired by generic filldir in fs/सूची_पढ़ो.c */
अटल पूर्णांक
ecryptfs_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *lower_name,
		 पूर्णांक lower_namelen, loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा ecryptfs_getdents_callback *buf =
		container_of(ctx, काष्ठा ecryptfs_getdents_callback, ctx);
	माप_प्रकार name_size;
	अक्षर *name;
	पूर्णांक rc;

	buf->filldir_called++;
	rc = ecryptfs_decode_and_decrypt_filename(&name, &name_size,
						  buf->sb, lower_name,
						  lower_namelen);
	अगर (rc) अणु
		अगर (rc != -EINVAL) अणु
			ecryptfs_prपूर्णांकk(KERN_DEBUG,
					"%s: Error attempting to decode and decrypt filename [%s]; rc = [%d]\n",
					__func__, lower_name, rc);
			वापस rc;
		पूर्ण

		/* Mask -EINVAL errors as these are most likely due a plaपूर्णांकext
		 * filename present in the lower fileप्रणाली despite filename
		 * encryption being enabled. One unaव्योमable example would be
		 * the "lost+found" dentry in the root directory of an Ext4
		 * fileप्रणाली.
		 */
		वापस 0;
	पूर्ण

	buf->caller->pos = buf->ctx.pos;
	rc = !dir_emit(buf->caller, name, name_size, ino, d_type);
	kमुक्त(name);
	अगर (!rc)
		buf->entries_written++;

	वापस rc;
पूर्ण

/**
 * ecryptfs_सूची_पढ़ो
 * @file: The eCryptfs directory file
 * @ctx: The actor to feed the entries to
 */
अटल पूर्णांक ecryptfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	पूर्णांक rc;
	काष्ठा file *lower_file;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ecryptfs_getdents_callback buf = अणु
		.ctx.actor = ecryptfs_filldir,
		.caller = ctx,
		.sb = inode->i_sb,
	पूर्ण;
	lower_file = ecryptfs_file_to_lower(file);
	rc = iterate_dir(lower_file, &buf.ctx);
	ctx->pos = buf.ctx.pos;
	अगर (rc < 0)
		जाओ out;
	अगर (buf.filldir_called && !buf.entries_written)
		जाओ out;
	अगर (rc >= 0)
		fsstack_copy_attr_aसमय(inode,
					file_inode(lower_file));
out:
	वापस rc;
पूर्ण

काष्ठा kmem_cache *ecryptfs_file_info_cache;

अटल पूर्णांक पढ़ो_or_initialize_metadata(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat;
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
	पूर्णांक rc;

	crypt_stat = &ecryptfs_inode_to_निजी(inode)->crypt_stat;
	mount_crypt_stat = &ecryptfs_superblock_to_निजी(
						inode->i_sb)->mount_crypt_stat;
	mutex_lock(&crypt_stat->cs_mutex);

	अगर (crypt_stat->flags & ECRYPTFS_POLICY_APPLIED &&
	    crypt_stat->flags & ECRYPTFS_KEY_VALID) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	rc = ecryptfs_पढ़ो_metadata(dentry);
	अगर (!rc)
		जाओ out;

	अगर (mount_crypt_stat->flags & ECRYPTFS_PLAINTEXT_PASSTHROUGH_ENABLED) अणु
		crypt_stat->flags &= ~(ECRYPTFS_I_SIZE_INITIALIZED
				       | ECRYPTFS_ENCRYPTED);
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (!(mount_crypt_stat->flags & ECRYPTFS_XATTR_METADATA_ENABLED) &&
	    !i_size_पढ़ो(ecryptfs_inode_to_lower(inode))) अणु
		rc = ecryptfs_initialize_file(dentry, inode);
		अगर (!rc)
			जाओ out;
	पूर्ण

	rc = -EIO;
out:
	mutex_unlock(&crypt_stat->cs_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक ecryptfs_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *lower_file = ecryptfs_file_to_lower(file);
	/*
	 * Don't allow mmap on top of file systems that don't support it
	 * natively.  If खाताSYSTEM_MAX_STACK_DEPTH > 2 or ecryptfs
	 * allows recursive mounting, this will need to be extended.
	 */
	अगर (!lower_file->f_op->mmap)
		वापस -ENODEV;
	वापस generic_file_mmap(file, vma);
पूर्ण

/**
 * ecryptfs_खोलो
 * @inode: inode specअगरying file to खोलो
 * @file: Structure to वापस filled in
 *
 * Opens the file specअगरied by inode.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc = 0;
	काष्ठा ecryptfs_crypt_stat *crypt_stat = शून्य;
	काष्ठा dentry *ecryptfs_dentry = file->f_path.dentry;
	/* Private value of ecryptfs_dentry allocated in
	 * ecryptfs_lookup() */
	काष्ठा ecryptfs_file_info *file_info;

	/* Released in ecryptfs_release or end of function अगर failure */
	file_info = kmem_cache_zalloc(ecryptfs_file_info_cache, GFP_KERNEL);
	ecryptfs_set_file_निजी(file, file_info);
	अगर (!file_info) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR,
				"Error attempting to allocate memory\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	crypt_stat = &ecryptfs_inode_to_निजी(inode)->crypt_stat;
	mutex_lock(&crypt_stat->cs_mutex);
	अगर (!(crypt_stat->flags & ECRYPTFS_POLICY_APPLIED)) अणु
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "Setting flags for stat...\n");
		/* Policy code enabled in future release */
		crypt_stat->flags |= (ECRYPTFS_POLICY_APPLIED
				      | ECRYPTFS_ENCRYPTED);
	पूर्ण
	mutex_unlock(&crypt_stat->cs_mutex);
	rc = ecryptfs_get_lower_file(ecryptfs_dentry, inode);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to initialize "
			"the lower file for the dentry with name "
			"[%pd]; rc = [%d]\n", __func__,
			ecryptfs_dentry, rc);
		जाओ out_मुक्त;
	पूर्ण
	अगर ((ecryptfs_inode_to_निजी(inode)->lower_file->f_flags & O_ACCMODE)
	    == O_RDONLY && (file->f_flags & O_ACCMODE) != O_RDONLY) अणु
		rc = -EPERM;
		prपूर्णांकk(KERN_WARNING "%s: Lower file is RO; eCryptfs "
		       "file must hence be opened RO\n", __func__);
		जाओ out_put;
	पूर्ण
	ecryptfs_set_file_lower(
		file, ecryptfs_inode_to_निजी(inode)->lower_file);
	rc = पढ़ो_or_initialize_metadata(ecryptfs_dentry);
	अगर (rc)
		जाओ out_put;
	ecryptfs_prपूर्णांकk(KERN_DEBUG, "inode w/ addr = [0x%p], i_ino = "
			"[0x%.16lx] size: [0x%.16llx]\n", inode, inode->i_ino,
			(अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(inode));
	जाओ out;
out_put:
	ecryptfs_put_lower_file(inode);
out_मुक्त:
	kmem_cache_मुक्त(ecryptfs_file_info_cache,
			ecryptfs_file_to_निजी(file));
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_dir_खोलो
 * @inode: inode specअगरying file to खोलो
 * @file: Structure to वापस filled in
 *
 * Opens the file specअगरied by inode.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dentry *ecryptfs_dentry = file->f_path.dentry;
	/* Private value of ecryptfs_dentry allocated in
	 * ecryptfs_lookup() */
	काष्ठा ecryptfs_file_info *file_info;
	काष्ठा file *lower_file;

	/* Released in ecryptfs_release or end of function अगर failure */
	file_info = kmem_cache_zalloc(ecryptfs_file_info_cache, GFP_KERNEL);
	ecryptfs_set_file_निजी(file, file_info);
	अगर (unlikely(!file_info)) अणु
		ecryptfs_prपूर्णांकk(KERN_ERR,
				"Error attempting to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण
	lower_file = dentry_खोलो(ecryptfs_dentry_to_lower_path(ecryptfs_dentry),
				 file->f_flags, current_cred());
	अगर (IS_ERR(lower_file)) अणु
		prपूर्णांकk(KERN_ERR "%s: Error attempting to initialize "
			"the lower file for the dentry with name "
			"[%pd]; rc = [%ld]\n", __func__,
			ecryptfs_dentry, PTR_ERR(lower_file));
		kmem_cache_मुक्त(ecryptfs_file_info_cache, file_info);
		वापस PTR_ERR(lower_file);
	पूर्ण
	ecryptfs_set_file_lower(file, lower_file);
	वापस 0;
पूर्ण

अटल पूर्णांक ecryptfs_flush(काष्ठा file *file, fl_owner_t td)
अणु
	काष्ठा file *lower_file = ecryptfs_file_to_lower(file);

	अगर (lower_file->f_op->flush) अणु
		filemap_ग_लिखो_and_रुको(file->f_mapping);
		वापस lower_file->f_op->flush(lower_file, td);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ecryptfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	ecryptfs_put_lower_file(inode);
	kmem_cache_मुक्त(ecryptfs_file_info_cache,
			ecryptfs_file_to_निजी(file));
	वापस 0;
पूर्ण

अटल पूर्णांक ecryptfs_dir_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	fput(ecryptfs_file_to_lower(file));
	kmem_cache_मुक्त(ecryptfs_file_info_cache,
			ecryptfs_file_to_निजी(file));
	वापस 0;
पूर्ण

अटल loff_t ecryptfs_dir_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	वापस vfs_llseek(ecryptfs_file_to_lower(file), offset, whence);
पूर्ण

अटल पूर्णांक
ecryptfs_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	पूर्णांक rc;

	rc = file_ग_लिखो_and_रुको(file);
	अगर (rc)
		वापस rc;

	वापस vfs_fsync(ecryptfs_file_to_lower(file), datasync);
पूर्ण

अटल पूर्णांक ecryptfs_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक flag)
अणु
	पूर्णांक rc = 0;
	काष्ठा file *lower_file = शून्य;

	lower_file = ecryptfs_file_to_lower(file);
	अगर (lower_file->f_op->fasync)
		rc = lower_file->f_op->fasync(fd, lower_file, flag);
	वापस rc;
पूर्ण

अटल दीर्घ
ecryptfs_unlocked_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा file *lower_file = ecryptfs_file_to_lower(file);
	दीर्घ rc = -ENOTTY;

	अगर (!lower_file->f_op->unlocked_ioctl)
		वापस rc;

	चयन (cmd) अणु
	हाल FITRIM:
	हाल FS_IOC_GETFLAGS:
	हाल FS_IOC_SETFLAGS:
	हाल FS_IOC_GETVERSION:
	हाल FS_IOC_SETVERSION:
		rc = lower_file->f_op->unlocked_ioctl(lower_file, cmd, arg);
		fsstack_copy_attr_all(file_inode(file), file_inode(lower_file));

		वापस rc;
	शेष:
		वापस rc;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ
ecryptfs_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा file *lower_file = ecryptfs_file_to_lower(file);
	दीर्घ rc = -ENOIOCTLCMD;

	अगर (!lower_file->f_op->compat_ioctl)
		वापस rc;

	चयन (cmd) अणु
	हाल FITRIM:
	हाल FS_IOC32_GETFLAGS:
	हाल FS_IOC32_SETFLAGS:
	हाल FS_IOC32_GETVERSION:
	हाल FS_IOC32_SETVERSION:
		rc = lower_file->f_op->compat_ioctl(lower_file, cmd, arg);
		fsstack_copy_attr_all(file_inode(file), file_inode(lower_file));

		वापस rc;
	शेष:
		वापस rc;
	पूर्ण
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा file_operations ecryptfs_dir_fops = अणु
	.iterate_shared = ecryptfs_सूची_पढ़ो,
	.पढ़ो = generic_पढ़ो_dir,
	.unlocked_ioctl = ecryptfs_unlocked_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = ecryptfs_compat_ioctl,
#पूर्ण_अगर
	.खोलो = ecryptfs_dir_खोलो,
	.release = ecryptfs_dir_release,
	.fsync = ecryptfs_fsync,
	.llseek = ecryptfs_dir_llseek,
पूर्ण;

स्थिर काष्ठा file_operations ecryptfs_मुख्य_fops = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = ecryptfs_पढ़ो_update_aसमय,
	.ग_लिखो_iter = generic_file_ग_लिखो_iter,
	.unlocked_ioctl = ecryptfs_unlocked_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = ecryptfs_compat_ioctl,
#पूर्ण_अगर
	.mmap = ecryptfs_mmap,
	.खोलो = ecryptfs_खोलो,
	.flush = ecryptfs_flush,
	.release = ecryptfs_release,
	.fsync = ecryptfs_fsync,
	.fasync = ecryptfs_fasync,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
पूर्ण;

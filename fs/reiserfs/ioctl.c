<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश "reiserfs.h"
#समावेश <linux/समय.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/compat.h>
#समावेश <linux/fileattr.h>

पूर्णांक reiserfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (!reiserfs_attrs(inode->i_sb))
		वापस -ENOTTY;

	fileattr_fill_flags(fa, REISERFS_I(inode)->i_attrs);

	वापस 0;
पूर्ण

पूर्णांक reiserfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक flags = fa->flags;
	पूर्णांक err;

	reiserfs_ग_लिखो_lock(inode->i_sb);

	err = -ENOTTY;
	अगर (!reiserfs_attrs(inode->i_sb))
		जाओ unlock;

	err = -EOPNOTSUPP;
	अगर (fileattr_has_fsx(fa))
		जाओ unlock;

	/*
	 * Is it quota file? Do not allow user to mess with it
	 */
	err = -EPERM;
	अगर (IS_NOQUOTA(inode))
		जाओ unlock;

	अगर ((flags & REISERFS_NOTAIL_FL) && S_ISREG(inode->i_mode)) अणु
		err = reiserfs_unpack(inode);
		अगर (err)
			जाओ unlock;
	पूर्ण
	sd_attrs_to_i_attrs(flags, inode);
	REISERFS_I(inode)->i_attrs = flags;
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
	err = 0;
unlock:
	reiserfs_ग_लिखो_unlock(inode->i_sb);

	वापस err;
पूर्ण

/*
 * reiserfs_ioctl - handler क्रम ioctl क्रम inode
 * supported commands:
 *  1) REISERFS_IOC_UNPACK - try to unpack tail from direct item पूर्णांकo indirect
 *                           and prevent packing file (argument arg has t
 *			      be non-zero)
 *  2) REISERFS_IOC_[GS]ETFLAGS, REISERFS_IOC_[GS]ETVERSION
 *  3) That's all क्रम a जबतक ...
 */
दीर्घ reiserfs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक err = 0;

	reiserfs_ग_लिखो_lock(inode->i_sb);

	चयन (cmd) अणु
	हाल REISERFS_IOC_UNPACK:
		अगर (S_ISREG(inode->i_mode)) अणु
			अगर (arg)
				err = reiserfs_unpack(inode);
		पूर्ण अन्यथा
			err = -ENOTTY;
		अवरोध;
		/*
		 * following two हालs are taken from fs/ext2/ioctl.c by Remy
		 * Card (card@masi.ibp.fr)
		 */
	हाल REISERFS_IOC_GETVERSION:
		err = put_user(inode->i_generation, (पूर्णांक __user *)arg);
		अवरोध;
	हाल REISERFS_IOC_SETVERSION:
		अगर (!inode_owner_or_capable(&init_user_ns, inode)) अणु
			err = -EPERM;
			अवरोध;
		पूर्ण
		err = mnt_want_ग_लिखो_file(filp);
		अगर (err)
			अवरोध;
		अगर (get_user(inode->i_generation, (पूर्णांक __user *)arg)) अणु
			err = -EFAULT;
			जाओ setversion_out;
		पूर्ण
		inode->i_स_समय = current_समय(inode);
		mark_inode_dirty(inode);
setversion_out:
		mnt_drop_ग_लिखो_file(filp);
		अवरोध;
	शेष:
		err = -ENOTTY;
	पूर्ण

	reiserfs_ग_लिखो_unlock(inode->i_sb);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
दीर्घ reiserfs_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	/*
	 * These are just misnamed, they actually
	 * get/put from/to user an पूर्णांक
	 */
	चयन (cmd) अणु
	हाल REISERFS_IOC32_UNPACK:
		cmd = REISERFS_IOC_UNPACK;
		अवरोध;
	हाल REISERFS_IOC32_GETVERSION:
		cmd = REISERFS_IOC_GETVERSION;
		अवरोध;
	हाल REISERFS_IOC32_SETVERSION:
		cmd = REISERFS_IOC_SETVERSION;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस reiserfs_ioctl(file, cmd, (अचिन्हित दीर्घ) compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

पूर्णांक reiserfs_commit_ग_लिखो(काष्ठा file *f, काष्ठा page *page,
			  अचिन्हित from, अचिन्हित to);
/*
 * reiserfs_unpack
 * Function try to convert tail from direct item पूर्णांकo indirect.
 * It set up nopack attribute in the REISERFS_I(inode)->nopack
 */
पूर्णांक reiserfs_unpack(काष्ठा inode *inode)
अणु
	पूर्णांक retval = 0;
	पूर्णांक index;
	काष्ठा page *page;
	काष्ठा address_space *mapping;
	अचिन्हित दीर्घ ग_लिखो_from;
	अचिन्हित दीर्घ blocksize = inode->i_sb->s_blocksize;

	अगर (inode->i_size == 0) अणु
		REISERFS_I(inode)->i_flags |= i_nopack_mask;
		वापस 0;
	पूर्ण
	/* ioctl alपढ़ोy करोne */
	अगर (REISERFS_I(inode)->i_flags & i_nopack_mask) अणु
		वापस 0;
	पूर्ण

	/* we need to make sure nobody is changing the file size beneath us */
	अणु
		पूर्णांक depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);

		inode_lock(inode);
		reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);
	पूर्ण

	reiserfs_ग_लिखो_lock(inode->i_sb);

	ग_लिखो_from = inode->i_size & (blocksize - 1);
	/* अगर we are on a block boundary, we are alपढ़ोy unpacked.  */
	अगर (ग_लिखो_from == 0) अणु
		REISERFS_I(inode)->i_flags |= i_nopack_mask;
		जाओ out;
	पूर्ण

	/*
	 * we unpack by finding the page with the tail, and calling
	 * __reiserfs_ग_लिखो_begin on that page.  This will क्रमce a
	 * reiserfs_get_block to unpack the tail क्रम us.
	 */
	index = inode->i_size >> PAGE_SHIFT;
	mapping = inode->i_mapping;
	page = grab_cache_page(mapping, index);
	retval = -ENOMEM;
	अगर (!page) अणु
		जाओ out;
	पूर्ण
	retval = __reiserfs_ग_लिखो_begin(page, ग_लिखो_from, 0);
	अगर (retval)
		जाओ out_unlock;

	/* conversion can change page contents, must flush */
	flush_dcache_page(page);
	retval = reiserfs_commit_ग_लिखो(शून्य, page, ग_लिखो_from, ग_लिखो_from);
	REISERFS_I(inode)->i_flags |= i_nopack_mask;

out_unlock:
	unlock_page(page);
	put_page(page);

out:
	inode_unlock(inode);
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	वापस retval;
पूर्ण

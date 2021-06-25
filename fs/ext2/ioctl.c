<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext2/ioctl.c
 *
 * Copyright (C) 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 */

#समावेश "ext2.h"
#समावेश <linux/capability.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched.h>
#समावेश <linux/compat.h>
#समावेश <linux/mount.h>
#समावेश <यंत्र/current.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fileattr.h>

पूर्णांक ext2_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा ext2_inode_info *ei = EXT2_I(d_inode(dentry));

	fileattr_fill_flags(fa, ei->i_flags & EXT2_FL_USER_VISIBLE);

	वापस 0;
पूर्ण

पूर्णांक ext2_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);

	अगर (fileattr_has_fsx(fa))
		वापस -EOPNOTSUPP;

	/* Is it quota file? Do not allow user to mess with it */
	अगर (IS_NOQUOTA(inode))
		वापस -EPERM;

	ei->i_flags = (ei->i_flags & ~EXT2_FL_USER_MODIFIABLE) |
		(fa->flags & EXT2_FL_USER_MODIFIABLE);

	ext2_set_inode_flags(inode);
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);

	वापस 0;
पूर्ण


दीर्घ ext2_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	अचिन्हित लघु rsv_winकरोw_size;
	पूर्णांक ret;

	ext2_debug ("cmd = %u, arg = %lu\n", cmd, arg);

	चयन (cmd) अणु
	हाल EXT2_IOC_GETVERSION:
		वापस put_user(inode->i_generation, (पूर्णांक __user *) arg);
	हाल EXT2_IOC_SETVERSION: अणु
		__u32 generation;

		अगर (!inode_owner_or_capable(&init_user_ns, inode))
			वापस -EPERM;
		ret = mnt_want_ग_लिखो_file(filp);
		अगर (ret)
			वापस ret;
		अगर (get_user(generation, (पूर्णांक __user *) arg)) अणु
			ret = -EFAULT;
			जाओ setversion_out;
		पूर्ण

		inode_lock(inode);
		inode->i_स_समय = current_समय(inode);
		inode->i_generation = generation;
		inode_unlock(inode);

		mark_inode_dirty(inode);
setversion_out:
		mnt_drop_ग_लिखो_file(filp);
		वापस ret;
	पूर्ण
	हाल EXT2_IOC_GETRSVSZ:
		अगर (test_opt(inode->i_sb, RESERVATION)
			&& S_ISREG(inode->i_mode)
			&& ei->i_block_alloc_info) अणु
			rsv_winकरोw_size = ei->i_block_alloc_info->rsv_winकरोw_node.rsv_goal_size;
			वापस put_user(rsv_winकरोw_size, (पूर्णांक __user *)arg);
		पूर्ण
		वापस -ENOTTY;
	हाल EXT2_IOC_SETRSVSZ: अणु

		अगर (!test_opt(inode->i_sb, RESERVATION) ||!S_ISREG(inode->i_mode))
			वापस -ENOTTY;

		अगर (!inode_owner_or_capable(&init_user_ns, inode))
			वापस -EACCES;

		अगर (get_user(rsv_winकरोw_size, (पूर्णांक __user *)arg))
			वापस -EFAULT;

		ret = mnt_want_ग_लिखो_file(filp);
		अगर (ret)
			वापस ret;

		अगर (rsv_winकरोw_size > EXT2_MAX_RESERVE_BLOCKS)
			rsv_winकरोw_size = EXT2_MAX_RESERVE_BLOCKS;

		/*
		 * need to allocate reservation काष्ठाure क्रम this inode
		 * beक्रमe set the winकरोw size
		 */
		/*
		 * XXX What lock should protect the rsv_goal_size?
		 * Accessed in ext2_get_block only.  ext3 uses i_truncate.
		 */
		mutex_lock(&ei->truncate_mutex);
		अगर (!ei->i_block_alloc_info)
			ext2_init_block_alloc_info(inode);

		अगर (ei->i_block_alloc_info)अणु
			काष्ठा ext2_reserve_winकरोw_node *rsv = &ei->i_block_alloc_info->rsv_winकरोw_node;
			rsv->rsv_goal_size = rsv_winकरोw_size;
		पूर्ण अन्यथा अणु
			ret = -ENOMEM;
		पूर्ण

		mutex_unlock(&ei->truncate_mutex);
		mnt_drop_ग_लिखो_file(filp);
		वापस ret;
	पूर्ण
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
दीर्घ ext2_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	/* These are just misnamed, they actually get/put from/to user an पूर्णांक */
	चयन (cmd) अणु
	हाल EXT2_IOC32_GETVERSION:
		cmd = EXT2_IOC_GETVERSION;
		अवरोध;
	हाल EXT2_IOC32_SETVERSION:
		cmd = EXT2_IOC_SETVERSION;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस ext2_ioctl(file, cmd, (अचिन्हित दीर्घ) compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

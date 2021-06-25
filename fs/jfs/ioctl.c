<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/jfs/ioctl.c
 *
 * Copyright (C) 2006 Herbert Poetzl
 * adapted from Remy Card's ext2/ioctl.c
 */

#समावेश <linux/fs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/capability.h>
#समावेश <linux/mount.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched.h>
#समावेश <linux/blkdev.h>
#समावेश <यंत्र/current.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fileattr.h>

#समावेश "jfs_filsys.h"
#समावेश "jfs_debug.h"
#समावेश "jfs_incore.h"
#समावेश "jfs_dinode.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_discard.h"

अटल काष्ठा अणु
	दीर्घ jfs_flag;
	दीर्घ ext2_flag;
पूर्ण jfs_map[] = अणु
	अणुJFS_NOATIME_FL,	FS_NOATIME_FLपूर्ण,
	अणुJFS_सूचीSYNC_FL,	FS_सूचीSYNC_FLपूर्ण,
	अणुJFS_SYNC_FL,		FS_SYNC_FLपूर्ण,
	अणुJFS_SECRM_FL,		FS_SECRM_FLपूर्ण,
	अणुJFS_UNRM_FL,		FS_UNRM_FLपूर्ण,
	अणुJFS_APPEND_FL,		FS_APPEND_FLपूर्ण,
	अणुJFS_IMMUTABLE_FL,	FS_IMMUTABLE_FLपूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;

अटल दीर्घ jfs_map_ext2(अचिन्हित दीर्घ flags, पूर्णांक from)
अणु
	पूर्णांक index=0;
	दीर्घ mapped=0;

	जबतक (jfs_map[index].jfs_flag) अणु
		अगर (from) अणु
			अगर (jfs_map[index].ext2_flag & flags)
				mapped |= jfs_map[index].jfs_flag;
		पूर्ण अन्यथा अणु
			अगर (jfs_map[index].jfs_flag & flags)
				mapped |= jfs_map[index].ext2_flag;
		पूर्ण
		index++;
	पूर्ण
	वापस mapped;
पूर्ण

पूर्णांक jfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा jfs_inode_info *jfs_inode = JFS_IP(d_inode(dentry));
	अचिन्हित पूर्णांक flags = jfs_inode->mode2 & JFS_FL_USER_VISIBLE;

	अगर (d_is_special(dentry))
		वापस -ENOTTY;

	fileattr_fill_flags(fa, jfs_map_ext2(flags, 0));

	वापस 0;
पूर्ण

पूर्णांक jfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
		     काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा jfs_inode_info *jfs_inode = JFS_IP(inode);
	अचिन्हित पूर्णांक flags;

	अगर (d_is_special(dentry))
		वापस -ENOTTY;

	अगर (fileattr_has_fsx(fa))
		वापस -EOPNOTSUPP;

	flags = jfs_map_ext2(fa->flags, 1);
	अगर (!S_ISसूची(inode->i_mode))
		flags &= ~JFS_सूचीSYNC_FL;

	/* Is it quota file? Do not allow user to mess with it */
	अगर (IS_NOQUOTA(inode))
		वापस -EPERM;

	flags = flags & JFS_FL_USER_MODIFIABLE;
	flags |= jfs_inode->mode2 & ~JFS_FL_USER_MODIFIABLE;
	jfs_inode->mode2 = flags;

	jfs_set_inode_flags(inode);
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);

	वापस 0;
पूर्ण

दीर्घ jfs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);

	चयन (cmd) अणु
	हाल FITRIM:
	अणु
		काष्ठा super_block *sb = inode->i_sb;
		काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
		काष्ठा fstrim_range range;
		s64 ret = 0;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (!blk_queue_discard(q)) अणु
			jfs_warn("FITRIM not supported on device");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (copy_from_user(&range, (काष्ठा fstrim_range __user *)arg,
		    माप(range)))
			वापस -EFAULT;

		range.minlen = max_t(अचिन्हित पूर्णांक, range.minlen,
			q->limits.discard_granularity);

		ret = jfs_ioc_trim(inode, &range);
		अगर (ret < 0)
			वापस ret;

		अगर (copy_to_user((काष्ठा fstrim_range __user *)arg, &range,
		    माप(range)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

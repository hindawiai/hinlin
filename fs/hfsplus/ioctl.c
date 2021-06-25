<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/ioctl.c
 *
 * Copyright (C) 2003
 * Ethan Benson <erbenson@alaska.net>
 * partially derived from linux/fs/ext2/ioctl.c
 * Copyright (C) 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 * hfsplus ioctls
 */

#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश "hfsplus_fs.h"

/*
 * "Blessing" an HFS+ fileप्रणाली ग_लिखोs metadata to the superblock inक्रमming
 * the platक्रमm firmware which file to boot from
 */
अटल पूर्णांक hfsplus_ioctl_bless(काष्ठा file *file, पूर्णांक __user *user_flags)
अणु
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(inode->i_sb);
	काष्ठा hfsplus_vh *vh = sbi->s_vhdr;
	काष्ठा hfsplus_vh *bvh = sbi->s_backup_vhdr;
	u32 cnid = (अचिन्हित दीर्घ)dentry->d_fsdata;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	mutex_lock(&sbi->vh_mutex);

	/* Directory containing the bootable प्रणाली */
	vh->finder_info[0] = bvh->finder_info[0] =
		cpu_to_be32(parent_ino(dentry));

	/*
	 * Bootloader. Just using the inode here अवरोधs in the हाल of
	 * hard links - the firmware wants the ID of the hard link file,
	 * but the inode poपूर्णांकs at the indirect inode
	 */
	vh->finder_info[1] = bvh->finder_info[1] = cpu_to_be32(cnid);

	/* Per spec, the OS X प्रणाली folder - same as finder_info[0] here */
	vh->finder_info[5] = bvh->finder_info[5] =
		cpu_to_be32(parent_ino(dentry));

	mutex_unlock(&sbi->vh_mutex);
	वापस 0;
पूर्ण

दीर्घ hfsplus_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल HFSPLUS_IOC_BLESS:
		वापस hfsplus_ioctl_bless(file, argp);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

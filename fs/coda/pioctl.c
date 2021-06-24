<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Pioctl operations क्रम Coda.
 * Original version: (C) 1996 Peter Braam
 * Rewritten क्रम Linux 2.1: (C) 1997 Carnegie Mellon University
 *
 * Carnegie Mellon encourages users of this code to contribute improvements
 * to the Coda project. Contact Peter Braam <coda@cs.cmu.edu>.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/namei.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"

/* pioctl ops */
अटल पूर्णांक coda_ioctl_permission(काष्ठा user_namespace *mnt_userns,
				 काष्ठा inode *inode, पूर्णांक mask);
अटल दीर्घ coda_pioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ user_data);

/* exported from this file */
स्थिर काष्ठा inode_operations coda_ioctl_inode_operations = अणु
	.permission	= coda_ioctl_permission,
	.setattr	= coda_setattr,
पूर्ण;

स्थिर काष्ठा file_operations coda_ioctl_operations = अणु
	.unlocked_ioctl	= coda_pioctl,
	.llseek		= noop_llseek,
पूर्ण;

/* the coda pioctl inode ops */
अटल पूर्णांक coda_ioctl_permission(काष्ठा user_namespace *mnt_userns,
				 काष्ठा inode *inode, पूर्णांक mask)
अणु
	वापस (mask & MAY_EXEC) ? -EACCES : 0;
पूर्ण

अटल दीर्घ coda_pioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ user_data)
अणु
	काष्ठा path path;
	पूर्णांक error;
	काष्ठा PioctlData data;
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा inode *target_inode = शून्य;
	काष्ठा coda_inode_info *cnp;

	/* get the Pioctl data arguments from user space */
	अगर (copy_from_user(&data, (व्योम __user *)user_data, माप(data)))
		वापस -EINVAL;

	/*
	 * Look up the pathname. Note that the pathname is in
	 * user memory, and namei takes care of this
	 */
	error = user_path_at(AT_FDCWD, data.path,
			     data.follow ? LOOKUP_FOLLOW : 0, &path);
	अगर (error)
		वापस error;

	target_inode = d_inode(path.dentry);

	/* वापस अगर it is not a Coda inode */
	अगर (target_inode->i_sb != inode->i_sb) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण

	/* now proceed to make the upcall */
	cnp = ITOC(target_inode);

	error = venus_pioctl(inode->i_sb, &(cnp->c_fid), cmd, &data);
out:
	path_put(&path);
	वापस error;
पूर्ण

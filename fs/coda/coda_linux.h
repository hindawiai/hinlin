<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Coda File System, Linux Kernel module
 * 
 * Original version, adapted from cfs_mach.c, (C) Carnegie Mellon University
 * Linux modअगरications (C) 1996, Peter J. Braam
 * Rewritten क्रम Linux 2.1 (C) 1997 Carnegie Mellon University
 *
 * Carnegie Mellon University encourages users of this software to
 * contribute improvements to the Coda project.
 */

#अगर_अघोषित _LINUX_CODA_FS
#घोषणा _LINUX_CODA_FS

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>		
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश "coda_fs_i.h"

/* operations */
बाह्य स्थिर काष्ठा inode_operations coda_dir_inode_operations;
बाह्य स्थिर काष्ठा inode_operations coda_file_inode_operations;
बाह्य स्थिर काष्ठा inode_operations coda_ioctl_inode_operations;

बाह्य स्थिर काष्ठा dentry_operations coda_dentry_operations;

बाह्य स्थिर काष्ठा address_space_operations coda_file_aops;
बाह्य स्थिर काष्ठा address_space_operations coda_symlink_aops;

बाह्य स्थिर काष्ठा file_operations coda_dir_operations;
बाह्य स्थिर काष्ठा file_operations coda_file_operations;
बाह्य स्थिर काष्ठा file_operations coda_ioctl_operations;

/* operations shared over more than one file */
पूर्णांक coda_खोलो(काष्ठा inode *i, काष्ठा file *f);
पूर्णांक coda_release(काष्ठा inode *i, काष्ठा file *f);
पूर्णांक coda_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		    पूर्णांक mask);
पूर्णांक coda_revalidate_inode(काष्ठा inode *);
पूर्णांक coda_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *, काष्ठा kstat *,
		 u32, अचिन्हित पूर्णांक);
पूर्णांक coda_setattr(काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);

/* this file:  heloers */
अक्षर *coda_f2s(काष्ठा CodaFid *f);
पूर्णांक coda_iscontrol(स्थिर अक्षर *name, माप_प्रकार length);

व्योम coda_vattr_to_iattr(काष्ठा inode *, काष्ठा coda_vattr *);
व्योम coda_iattr_to_vattr(काष्ठा iattr *, काष्ठा coda_vattr *);
अचिन्हित लघु coda_flags_to_cflags(अचिन्हित लघु);

/* inode to cnode access functions */

अटल अंतरभूत काष्ठा coda_inode_info *ITOC(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा coda_inode_info, vfs_inode);
पूर्ण

अटल __अंतरभूत__ काष्ठा CodaFid *coda_i2f(काष्ठा inode *inode)
अणु
	वापस &(ITOC(inode)->c_fid);
पूर्ण

अटल __अंतरभूत__ अक्षर *coda_i2s(काष्ठा inode *inode)
अणु
	वापस coda_f2s(&(ITOC(inode)->c_fid));
पूर्ण

/* this will not zap the inode away */
अटल __अंतरभूत__ व्योम coda_flag_inode(काष्ठा inode *inode, पूर्णांक flag)
अणु
	काष्ठा coda_inode_info *cii = ITOC(inode);

	spin_lock(&cii->c_lock);
	cii->c_flags |= flag;
	spin_unlock(&cii->c_lock);
पूर्ण		

#पूर्ण_अगर

<शैली गुरु>
/*
 *   fs/cअगरs/cअगरsfs.h
 *
 *   Copyright (c) International Business Machines  Corp., 2002, 2007
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#अगर_अघोषित _CIFSFS_H
#घोषणा _CIFSFS_H

#समावेश <linux/hash.h>

#घोषणा ROOT_I 2

/*
 * ino_t is 32-bits on 32-bit arch. We have to squash the 64-bit value करोwn
 * so that it will fit. We use hash_64 to convert the value to 31 bits, and
 * then add 1, to ensure that we करोn't end up with a 0 as the value.
 */
अटल अंतरभूत ino_t
cअगरs_uniqueid_to_ino_t(u64 fileid)
अणु
	अगर ((माप(ino_t)) < (माप(u64)))
		वापस (ino_t)hash_64(fileid, (माप(ino_t) * 8) - 1) + 1;

	वापस (ino_t)fileid;

पूर्ण

अटल अंतरभूत व्योम cअगरs_set_समय(काष्ठा dentry *dentry, अचिन्हित दीर्घ समय)
अणु
	dentry->d_fsdata = (व्योम *) समय;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cअगरs_get_समय(काष्ठा dentry *dentry)
अणु
	वापस (अचिन्हित दीर्घ) dentry->d_fsdata;
पूर्ण

बाह्य काष्ठा file_प्रणाली_type cअगरs_fs_type;
बाह्य स्थिर काष्ठा address_space_operations cअगरs_addr_ops;
बाह्य स्थिर काष्ठा address_space_operations cअगरs_addr_ops_smallbuf;

/* Functions related to super block operations */
बाह्य व्योम cअगरs_sb_active(काष्ठा super_block *sb);
बाह्य व्योम cअगरs_sb_deactive(काष्ठा super_block *sb);

/* Functions related to inodes */
बाह्य स्थिर काष्ठा inode_operations cअगरs_dir_inode_ops;
बाह्य काष्ठा inode *cअगरs_root_iget(काष्ठा super_block *);
बाह्य पूर्णांक cअगरs_create(काष्ठा user_namespace *, काष्ठा inode *,
		       काष्ठा dentry *, umode_t, bool excl);
बाह्य पूर्णांक cअगरs_atomic_खोलो(काष्ठा inode *, काष्ठा dentry *,
			    काष्ठा file *, अचिन्हित, umode_t);
बाह्य काष्ठा dentry *cअगरs_lookup(काष्ठा inode *, काष्ठा dentry *,
				  अचिन्हित पूर्णांक);
बाह्य पूर्णांक cअगरs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry);
बाह्य पूर्णांक cअगरs_hardlink(काष्ठा dentry *, काष्ठा inode *, काष्ठा dentry *);
बाह्य पूर्णांक cअगरs_mknod(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
		      umode_t, dev_t);
बाह्य पूर्णांक cअगरs_सूची_गढ़ो(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
		      umode_t);
बाह्य पूर्णांक cअगरs_सूची_हटाओ(काष्ठा inode *, काष्ठा dentry *);
बाह्य पूर्णांक cअगरs_नाम2(काष्ठा user_namespace *, काष्ठा inode *,
			काष्ठा dentry *, काष्ठा inode *, काष्ठा dentry *,
			अचिन्हित पूर्णांक);
बाह्य पूर्णांक cअगरs_revalidate_file_attr(काष्ठा file *filp);
बाह्य पूर्णांक cअगरs_revalidate_dentry_attr(काष्ठा dentry *);
बाह्य पूर्णांक cअगरs_revalidate_file(काष्ठा file *filp);
बाह्य पूर्णांक cअगरs_revalidate_dentry(काष्ठा dentry *);
बाह्य पूर्णांक cअगरs_invalidate_mapping(काष्ठा inode *inode);
बाह्य पूर्णांक cअगरs_revalidate_mapping(काष्ठा inode *inode);
बाह्य पूर्णांक cअगरs_zap_mapping(काष्ठा inode *inode);
बाह्य पूर्णांक cअगरs_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *,
			काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य पूर्णांक cअगरs_setattr(काष्ठा user_namespace *, काष्ठा dentry *,
			काष्ठा iattr *);
बाह्य पूर्णांक cअगरs_fiemap(काष्ठा inode *, काष्ठा fiemap_extent_info *, u64 start,
		       u64 len);

बाह्य स्थिर काष्ठा inode_operations cअगरs_file_inode_ops;
बाह्य स्थिर काष्ठा inode_operations cअगरs_symlink_inode_ops;
बाह्य स्थिर काष्ठा inode_operations cअगरs_dfs_referral_inode_operations;


/* Functions related to files and directories */
बाह्य स्थिर काष्ठा file_operations cअगरs_file_ops;
बाह्य स्थिर काष्ठा file_operations cअगरs_file_direct_ops; /* अगर directio mnt */
बाह्य स्थिर काष्ठा file_operations cअगरs_file_strict_ops; /* अगर strictio mnt */
बाह्य स्थिर काष्ठा file_operations cअगरs_file_nobrl_ops; /* no brlocks */
बाह्य स्थिर काष्ठा file_operations cअगरs_file_direct_nobrl_ops;
बाह्य स्थिर काष्ठा file_operations cअगरs_file_strict_nobrl_ops;
बाह्य पूर्णांक cअगरs_खोलो(काष्ठा inode *inode, काष्ठा file *file);
बाह्य पूर्णांक cअगरs_बंद(काष्ठा inode *inode, काष्ठा file *file);
बाह्य पूर्णांक cअगरs_बंद_सूची(काष्ठा inode *inode, काष्ठा file *file);
बाह्य sमाप_प्रकार cअगरs_user_पढ़ोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *to);
बाह्य sमाप_प्रकार cअगरs_direct_पढ़ोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *to);
बाह्य sमाप_प्रकार cअगरs_strict_पढ़ोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *to);
बाह्य sमाप_प्रकार cअगरs_user_ग_लिखोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *from);
बाह्य sमाप_प्रकार cअगरs_direct_ग_लिखोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *from);
बाह्य sमाप_प्रकार cअगरs_strict_ग_लिखोv(काष्ठा kiocb *iocb, काष्ठा iov_iter *from);
बाह्य पूर्णांक cअगरs_flock(काष्ठा file *pfile, पूर्णांक cmd, काष्ठा file_lock *plock);
बाह्य पूर्णांक cअगरs_lock(काष्ठा file *, पूर्णांक, काष्ठा file_lock *);
बाह्य पूर्णांक cअगरs_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);
बाह्य पूर्णांक cअगरs_strict_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);
बाह्य पूर्णांक cअगरs_flush(काष्ठा file *, fl_owner_t id);
बाह्य पूर्णांक cअगरs_file_mmap(काष्ठा file * , काष्ठा vm_area_काष्ठा *);
बाह्य पूर्णांक cअगरs_file_strict_mmap(काष्ठा file * , काष्ठा vm_area_काष्ठा *);
बाह्य स्थिर काष्ठा file_operations cअगरs_dir_ops;
बाह्य पूर्णांक cअगरs_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file);
बाह्य पूर्णांक cअगरs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx);

/* Functions related to dir entries */
बाह्य स्थिर काष्ठा dentry_operations cअगरs_dentry_ops;
बाह्य स्थिर काष्ठा dentry_operations cअगरs_ci_dentry_ops;

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
बाह्य काष्ठा vfsmount *cअगरs_dfs_d_स्वतःmount(काष्ठा path *path);
#अन्यथा
#घोषणा cअगरs_dfs_d_स्वतःmount शून्य
#पूर्ण_अगर

/* Functions related to symlinks */
बाह्य स्थिर अक्षर *cअगरs_get_link(काष्ठा dentry *, काष्ठा inode *,
			काष्ठा delayed_call *);
बाह्य पूर्णांक cअगरs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
			काष्ठा dentry *direntry, स्थिर अक्षर *symname);

#अगर_घोषित CONFIG_CIFS_XATTR
बाह्य स्थिर काष्ठा xattr_handler *cअगरs_xattr_handlers[];
बाह्य sमाप_प्रकार	cअगरs_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);
#अन्यथा
# define cअगरs_xattr_handlers शून्य
# define cअगरs_listxattr शून्य
#पूर्ण_अगर

बाह्य sमाप_प्रकार cअगरs_file_copychunk_range(अचिन्हित पूर्णांक xid,
					काष्ठा file *src_file, loff_t off,
					काष्ठा file *dst_file, loff_t destoff,
					माप_प्रकार len, अचिन्हित पूर्णांक flags);

बाह्य दीर्घ cअगरs_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
बाह्य व्योम cअगरs_setsize(काष्ठा inode *inode, loff_t offset);
बाह्य पूर्णांक cअगरs_truncate_page(काष्ठा address_space *mapping, loff_t from);

काष्ठा smb3_fs_context;
बाह्य काष्ठा dentry *cअगरs_smb3_करो_mount(काष्ठा file_प्रणाली_type *fs_type,
					 पूर्णांक flags, काष्ठा smb3_fs_context *ctx);

#अगर_घोषित CONFIG_CIFS_NFSD_EXPORT
बाह्य स्थिर काष्ठा export_operations cअगरs_export_ops;
#पूर्ण_अगर /* CONFIG_CIFS_NFSD_EXPORT */

#घोषणा CIFS_VERSION   "2.32"
#पूर्ण_अगर				/* _CIFSFS_H */

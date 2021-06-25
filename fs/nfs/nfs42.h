<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014 Anna Schumaker <Anna.Schumaker@Netapp.com>
 */

#अगर_अघोषित __LINUX_FS_NFS_NFS4_2_H
#घोषणा __LINUX_FS_NFS_NFS4_2_H

#समावेश <linux/xattr.h>

/*
 * FIXME:  four LAYOUTSTATS calls per compound at most! Do we need to support
 * more? Need to consider not to pre-alloc too much क्रम a compound.
 */
#घोषणा PNFS_LAYOUTSTATS_MAXDEV (4)

/* nfs4.2proc.c */
#अगर_घोषित CONFIG_NFS_V4_2
पूर्णांक nfs42_proc_allocate(काष्ठा file *, loff_t, loff_t);
sमाप_प्रकार nfs42_proc_copy(काष्ठा file *, loff_t, काष्ठा file *, loff_t, माप_प्रकार,
			काष्ठा nl4_server *, nfs4_stateid *, bool);
पूर्णांक nfs42_proc_deallocate(काष्ठा file *, loff_t, loff_t);
loff_t nfs42_proc_llseek(काष्ठा file *, loff_t, पूर्णांक);
पूर्णांक nfs42_proc_layoutstats_generic(काष्ठा nfs_server *,
				   काष्ठा nfs42_layoutstat_data *);
पूर्णांक nfs42_proc_clone(काष्ठा file *, काष्ठा file *, loff_t, loff_t, loff_t);
पूर्णांक nfs42_proc_layouterror(काष्ठा pnfs_layout_segment *lseg,
			   स्थिर काष्ठा nfs42_layout_error *errors,
			   माप_प्रकार n);
पूर्णांक nfs42_proc_copy_notअगरy(काष्ठा file *, काष्ठा file *,
			   काष्ठा nfs42_copy_notअगरy_res *);
अटल अंतरभूत bool nfs42_files_from_same_server(काष्ठा file *in,
						काष्ठा file *out)
अणु
	काष्ठा nfs_client *c_in = (NFS_SERVER(file_inode(in)))->nfs_client;
	काष्ठा nfs_client *c_out = (NFS_SERVER(file_inode(out)))->nfs_client;

	वापस nfs4_check_serverowner_major_id(c_in->cl_serverowner,
					       c_out->cl_serverowner);
पूर्ण

sमाप_प्रकार nfs42_proc_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			    व्योम *buf, माप_प्रकार buflen);
पूर्णांक nfs42_proc_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			स्थिर व्योम *buf, माप_प्रकार buflen, पूर्णांक flags);
sमाप_प्रकार nfs42_proc_listxattrs(काष्ठा inode *inode, व्योम *buf,
			       माप_प्रकार buflen, u64 *cookiep, bool *eofp);
पूर्णांक nfs42_proc_हटाओxattr(काष्ठा inode *inode, स्थिर अक्षर *name);

/*
 * Maximum XDR buffer size needed क्रम a listxattr buffer of buflen size.
 *
 * The upper boundary is a buffer with all 1-byte sized attribute names.
 * They would be 7 bytes दीर्घ in the eventual buffer ("user.x\0"), and
 * 8 bytes दीर्घ XDR-encoded.
 *
 * Include the trailing eof word as well.
 */
अटल अंतरभूत u32 nfs42_listxattr_xdrsize(u32 buflen)
अणु
	वापस ((buflen / (XATTR_USER_PREFIX_LEN + 2)) * 8) + 4;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */
#पूर्ण_अगर /* __LINUX_FS_NFS_NFS4_2_H */

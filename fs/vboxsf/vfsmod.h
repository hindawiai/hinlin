<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * VirtualBox Guest Shared Folders support: module header.
 *
 * Copyright (C) 2006-2018 Oracle Corporation
 */

#अगर_अघोषित VFSMOD_H
#घोषणा VFSMOD_H

#समावेश <linux/backing-dev.h>
#समावेश <linux/idr.h>
#समावेश "shfl_hostintf.h"

#घोषणा सूची_BUFFER_SIZE SZ_16K

/* The cast is to prevent assignment of व्योम * to poपूर्णांकers of arbitrary type */
#घोषणा VBOXSF_SBI(sb)	((काष्ठा vboxsf_sbi *)(sb)->s_fs_info)
#घोषणा VBOXSF_I(i)	container_of(i, काष्ठा vboxsf_inode, vfs_inode)

काष्ठा vboxsf_options अणु
	अचिन्हित दीर्घ ttl;
	kuid_t uid;
	kgid_t gid;
	bool dmode_set;
	bool भ_शेषe_set;
	umode_t dmode;
	umode_t भ_शेषe;
	umode_t dmask;
	umode_t fmask;
पूर्ण;

काष्ठा vboxsf_fs_context अणु
	काष्ठा vboxsf_options o;
	अक्षर *nls_name;
पूर्ण;

/* per-shared folder inक्रमmation */
काष्ठा vboxsf_sbi अणु
	काष्ठा vboxsf_options o;
	काष्ठा shfl_fsobjinfo root_info;
	काष्ठा idr ino_idr;
	spinlock_t ino_idr_lock; /* This protects ino_idr */
	काष्ठा nls_table *nls;
	u32 next_generation;
	u32 root;
	पूर्णांक bdi_id;
पूर्ण;

/* per-inode inक्रमmation */
काष्ठा vboxsf_inode अणु
	/* some inक्रमmation was changed, update data on next revalidate */
	पूर्णांक क्रमce_restat;
	/* list of खोलो handles क्रम this inode + lock protecting it */
	काष्ठा list_head handle_list;
	/* This mutex protects handle_list accesses */
	काष्ठा mutex handle_list_mutex;
	/* The VFS inode काष्ठा */
	काष्ठा inode vfs_inode;
पूर्ण;

काष्ठा vboxsf_dir_info अणु
	काष्ठा list_head info_list;
पूर्ण;

काष्ठा vboxsf_dir_buf अणु
	माप_प्रकार entries;
	माप_प्रकार मुक्त;
	माप_प्रकार used;
	व्योम *buf;
	काष्ठा list_head head;
पूर्ण;

/* globals */
बाह्य स्थिर काष्ठा inode_operations vboxsf_dir_iops;
बाह्य स्थिर काष्ठा inode_operations vboxsf_lnk_iops;
बाह्य स्थिर काष्ठा inode_operations vboxsf_reg_iops;
बाह्य स्थिर काष्ठा file_operations vboxsf_dir_fops;
बाह्य स्थिर काष्ठा file_operations vboxsf_reg_fops;
बाह्य स्थिर काष्ठा address_space_operations vboxsf_reg_aops;
बाह्य स्थिर काष्ठा dentry_operations vboxsf_dentry_ops;

/* from utils.c */
काष्ठा inode *vboxsf_new_inode(काष्ठा super_block *sb);
पूर्णांक vboxsf_init_inode(काष्ठा vboxsf_sbi *sbi, काष्ठा inode *inode,
		       स्थिर काष्ठा shfl_fsobjinfo *info, bool reinit);
पूर्णांक vboxsf_create_at_dentry(काष्ठा dentry *dentry,
			    काष्ठा shfl_createparms *params);
पूर्णांक vboxsf_stat(काष्ठा vboxsf_sbi *sbi, काष्ठा shfl_string *path,
		काष्ठा shfl_fsobjinfo *info);
पूर्णांक vboxsf_stat_dentry(काष्ठा dentry *dentry, काष्ठा shfl_fsobjinfo *info);
पूर्णांक vboxsf_inode_revalidate(काष्ठा dentry *dentry);
पूर्णांक vboxsf_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		   काष्ठा kstat *kstat, u32 request_mask,
		   अचिन्हित पूर्णांक query_flags);
पूर्णांक vboxsf_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		   काष्ठा iattr *iattr);
काष्ठा shfl_string *vboxsf_path_from_dentry(काष्ठा vboxsf_sbi *sbi,
					    काष्ठा dentry *dentry);
पूर्णांक vboxsf_nlscpy(काष्ठा vboxsf_sbi *sbi, अक्षर *name, माप_प्रकार name_bound_len,
		  स्थिर अचिन्हित अक्षर *utf8_name, माप_प्रकार utf8_len);
काष्ठा vboxsf_dir_info *vboxsf_dir_info_alloc(व्योम);
व्योम vboxsf_dir_info_मुक्त(काष्ठा vboxsf_dir_info *p);
पूर्णांक vboxsf_dir_पढ़ो_all(काष्ठा vboxsf_sbi *sbi, काष्ठा vboxsf_dir_info *sf_d,
			u64 handle);

/* from vboxsf_wrappers.c */
पूर्णांक vboxsf_connect(व्योम);
व्योम vboxsf_disconnect(व्योम);

पूर्णांक vboxsf_create(u32 root, काष्ठा shfl_string *parsed_path,
		  काष्ठा shfl_createparms *create_parms);

पूर्णांक vboxsf_बंद(u32 root, u64 handle);
पूर्णांक vboxsf_हटाओ(u32 root, काष्ठा shfl_string *parsed_path, u32 flags);
पूर्णांक vboxsf_नाम(u32 root, काष्ठा shfl_string *src_path,
		  काष्ठा shfl_string *dest_path, u32 flags);

पूर्णांक vboxsf_पढ़ो(u32 root, u64 handle, u64 offset, u32 *buf_len, u8 *buf);
पूर्णांक vboxsf_ग_लिखो(u32 root, u64 handle, u64 offset, u32 *buf_len, u8 *buf);

पूर्णांक vboxsf_dirinfo(u32 root, u64 handle,
		   काष्ठा shfl_string *parsed_path, u32 flags, u32 index,
		   u32 *buf_len, काष्ठा shfl_dirinfo *buf, u32 *file_count);
पूर्णांक vboxsf_fsinfo(u32 root, u64 handle, u32 flags,
		  u32 *buf_len, व्योम *buf);

पूर्णांक vboxsf_map_folder(काष्ठा shfl_string *folder_name, u32 *root);
पूर्णांक vboxsf_unmap_folder(u32 root);

पूर्णांक vboxsf_पढ़ोlink(u32 root, काष्ठा shfl_string *parsed_path,
		    u32 buf_len, u8 *buf);
पूर्णांक vboxsf_symlink(u32 root, काष्ठा shfl_string *new_path,
		   काष्ठा shfl_string *old_path, काष्ठा shfl_fsobjinfo *buf);

पूर्णांक vboxsf_set_utf8(व्योम);
पूर्णांक vboxsf_set_symlinks(व्योम);

#पूर्ण_अगर

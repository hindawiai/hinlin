<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * fs/kernfs/kernfs-पूर्णांकernal.h - kernfs पूर्णांकernal header file
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007, 2013 Tejun Heo <teheo@suse.de>
 */

#अगर_अघोषित __KERNFS_INTERNAL_H
#घोषणा __KERNFS_INTERNAL_H

#समावेश <linux/lockdep.h>
#समावेश <linux/fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/xattr.h>

#समावेश <linux/kernfs.h>
#समावेश <linux/fs_context.h>

काष्ठा kernfs_iattrs अणु
	kuid_t			ia_uid;
	kgid_t			ia_gid;
	काष्ठा बारpec64	ia_aसमय;
	काष्ठा बारpec64	ia_mसमय;
	काष्ठा बारpec64	ia_स_समय;

	काष्ठा simple_xattrs	xattrs;
	atomic_t		nr_user_xattrs;
	atomic_t		user_xattr_size;
पूर्ण;

/* +1 to aव्योम triggering overflow warning when negating it */
#घोषणा KN_DEACTIVATED_BIAS		(पूर्णांक_न्यून + 1)

/* KERNFS_TYPE_MASK and types are defined in include/linux/kernfs.h */

/**
 * kernfs_root - find out the kernfs_root a kernfs_node beदीर्घs to
 * @kn: kernfs_node of पूर्णांकerest
 *
 * Return the kernfs_root @kn beदीर्घs to.
 */
अटल अंतरभूत काष्ठा kernfs_root *kernfs_root(काष्ठा kernfs_node *kn)
अणु
	/* अगर parent exists, it's always a dir; otherwise, @sd is a dir */
	अगर (kn->parent)
		kn = kn->parent;
	वापस kn->dir.root;
पूर्ण

/*
 * mount.c
 */
काष्ठा kernfs_super_info अणु
	काष्ठा super_block	*sb;

	/*
	 * The root associated with this super_block.  Each super_block is
	 * identअगरied by the root and ns it's associated with.
	 */
	काष्ठा kernfs_root	*root;

	/*
	 * Each sb is associated with one namespace tag, currently the
	 * network namespace of the task which mounted this kernfs
	 * instance.  If multiple tags become necessary, make the following
	 * an array and compare kernfs_node tag against every entry.
	 */
	स्थिर व्योम		*ns;

	/* anchored at kernfs_root->supers, रक्षित by kernfs_mutex */
	काष्ठा list_head	node;
पूर्ण;
#घोषणा kernfs_info(SB) ((काष्ठा kernfs_super_info *)(SB->s_fs_info))

अटल अंतरभूत काष्ठा kernfs_node *kernfs_dentry_node(काष्ठा dentry *dentry)
अणु
	अगर (d_really_is_negative(dentry))
		वापस शून्य;
	वापस d_inode(dentry)->i_निजी;
पूर्ण

बाह्य स्थिर काष्ठा super_operations kernfs_sops;
बाह्य काष्ठा kmem_cache *kernfs_node_cache, *kernfs_iattrs_cache;

/*
 * inode.c
 */
बाह्य स्थिर काष्ठा xattr_handler *kernfs_xattr_handlers[];
व्योम kernfs_evict_inode(काष्ठा inode *inode);
पूर्णांक kernfs_iop_permission(काष्ठा user_namespace *mnt_userns,
			  काष्ठा inode *inode, पूर्णांक mask);
पूर्णांक kernfs_iop_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		       काष्ठा iattr *iattr);
पूर्णांक kernfs_iop_getattr(काष्ठा user_namespace *mnt_userns,
		       स्थिर काष्ठा path *path, काष्ठा kstat *stat,
		       u32 request_mask, अचिन्हित पूर्णांक query_flags);
sमाप_प्रकार kernfs_iop_listxattr(काष्ठा dentry *dentry, अक्षर *buf, माप_प्रकार size);
पूर्णांक __kernfs_setattr(काष्ठा kernfs_node *kn, स्थिर काष्ठा iattr *iattr);

/*
 * dir.c
 */
बाह्य काष्ठा mutex kernfs_mutex;
बाह्य स्थिर काष्ठा dentry_operations kernfs_करोps;
बाह्य स्थिर काष्ठा file_operations kernfs_dir_fops;
बाह्य स्थिर काष्ठा inode_operations kernfs_dir_iops;

काष्ठा kernfs_node *kernfs_get_active(काष्ठा kernfs_node *kn);
व्योम kernfs_put_active(काष्ठा kernfs_node *kn);
पूर्णांक kernfs_add_one(काष्ठा kernfs_node *kn);
काष्ठा kernfs_node *kernfs_new_node(काष्ठा kernfs_node *parent,
				    स्थिर अक्षर *name, umode_t mode,
				    kuid_t uid, kgid_t gid,
				    अचिन्हित flags);

/*
 * file.c
 */
बाह्य स्थिर काष्ठा file_operations kernfs_file_fops;

व्योम kernfs_drain_खोलो_files(काष्ठा kernfs_node *kn);

/*
 * symlink.c
 */
बाह्य स्थिर काष्ठा inode_operations kernfs_symlink_iops;

#पूर्ण_अगर	/* __KERNFS_INTERNAL_H */

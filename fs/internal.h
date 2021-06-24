<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* fs/ पूर्णांकernal definitions
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

काष्ठा super_block;
काष्ठा file_प्रणाली_type;
काष्ठा iomap;
काष्ठा iomap_ops;
काष्ठा linux_binprm;
काष्ठा path;
काष्ठा mount;
काष्ठा shrink_control;
काष्ठा fs_context;
काष्ठा user_namespace;
काष्ठा pipe_inode_info;

/*
 * block_dev.c
 */
#अगर_घोषित CONFIG_BLOCK
बाह्य व्योम __init bdev_cache_init(व्योम);

बाह्य पूर्णांक __sync_blockdev(काष्ठा block_device *bdev, पूर्णांक रुको);
व्योम iterate_bdevs(व्योम (*)(काष्ठा block_device *, व्योम *), व्योम *);
व्योम emergency_thaw_bdev(काष्ठा super_block *sb);
#अन्यथा
अटल अंतरभूत व्योम bdev_cache_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक __sync_blockdev(काष्ठा block_device *bdev, पूर्णांक रुको)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम iterate_bdevs(व्योम (*f)(काष्ठा block_device *, व्योम *),
		व्योम *arg)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक emergency_thaw_bdev(काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLOCK */

/*
 * buffer.c
 */
बाह्य पूर्णांक __block_ग_लिखो_begin_पूर्णांक(काष्ठा page *page, loff_t pos, अचिन्हित len,
		get_block_t *get_block, काष्ठा iomap *iomap);

/*
 * अक्षर_dev.c
 */
बाह्य व्योम __init chrdev_init(व्योम);

/*
 * fs_context.c
 */
बाह्य स्थिर काष्ठा fs_context_operations legacy_fs_context_ops;
बाह्य पूर्णांक parse_monolithic_mount_data(काष्ठा fs_context *, व्योम *);
बाह्य व्योम fc_drop_locked(काष्ठा fs_context *);
बाह्य व्योम vfs_clean_context(काष्ठा fs_context *fc);
बाह्य पूर्णांक finish_clean_context(काष्ठा fs_context *fc);

/*
 * namei.c
 */
बाह्य पूर्णांक filename_lookup(पूर्णांक dfd, काष्ठा filename *name, अचिन्हित flags,
			   काष्ठा path *path, काष्ठा path *root);
बाह्य पूर्णांक vfs_path_lookup(काष्ठा dentry *, काष्ठा vfsmount *,
			   स्थिर अक्षर *, अचिन्हित पूर्णांक, काष्ठा path *);
दीर्घ करो_सूची_हटाओ(पूर्णांक dfd, काष्ठा filename *name);
दीर्घ करो_unlinkat(पूर्णांक dfd, काष्ठा filename *name);
पूर्णांक may_linkat(काष्ठा user_namespace *mnt_userns, काष्ठा path *link);
पूर्णांक करो_नामat2(पूर्णांक olddfd, काष्ठा filename *oldname, पूर्णांक newdfd,
		 काष्ठा filename *newname, अचिन्हित पूर्णांक flags);

/*
 * namespace.c
 */
बाह्य काष्ठा vfsmount *lookup_mnt(स्थिर काष्ठा path *);
बाह्य पूर्णांक finish_स्वतःmount(काष्ठा vfsmount *, काष्ठा path *);

बाह्य पूर्णांक sb_prepare_remount_पढ़ोonly(काष्ठा super_block *);

बाह्य व्योम __init mnt_init(व्योम);

बाह्य पूर्णांक __mnt_want_ग_लिखो_file(काष्ठा file *);
बाह्य व्योम __mnt_drop_ग_लिखो_file(काष्ठा file *);

बाह्य व्योम dissolve_on_fput(काष्ठा vfsmount *);

पूर्णांक path_mount(स्थिर अक्षर *dev_name, काष्ठा path *path,
		स्थिर अक्षर *type_page, अचिन्हित दीर्घ flags, व्योम *data_page);
पूर्णांक path_umount(काष्ठा path *path, पूर्णांक flags);

/*
 * fs_काष्ठा.c
 */
बाह्य व्योम chroot_fs_refs(स्थिर काष्ठा path *, स्थिर काष्ठा path *);

/*
 * file_table.c
 */
बाह्य काष्ठा file *alloc_empty_file(पूर्णांक, स्थिर काष्ठा cred *);
बाह्य काष्ठा file *alloc_empty_file_noaccount(पूर्णांक, स्थिर काष्ठा cred *);

/*
 * super.c
 */
बाह्य पूर्णांक reconfigure_super(काष्ठा fs_context *);
बाह्य bool trylock_super(काष्ठा super_block *sb);
काष्ठा super_block *user_get_super(dev_t, bool excl);
व्योम put_super(काष्ठा super_block *sb);
बाह्य bool mount_capable(काष्ठा fs_context *);

/*
 * खोलो.c
 */
काष्ठा खोलो_flags अणु
	पूर्णांक खोलो_flag;
	umode_t mode;
	पूर्णांक acc_mode;
	पूर्णांक पूर्णांकent;
	पूर्णांक lookup_flags;
पूर्ण;
बाह्य काष्ठा file *करो_filp_खोलो(पूर्णांक dfd, काष्ठा filename *pathname,
		स्थिर काष्ठा खोलो_flags *op);
बाह्य काष्ठा file *करो_file_खोलो_root(काष्ठा dentry *, काष्ठा vfsmount *,
		स्थिर अक्षर *, स्थिर काष्ठा खोलो_flags *);
बाह्य काष्ठा खोलो_how build_खोलो_how(पूर्णांक flags, umode_t mode);
बाह्य पूर्णांक build_खोलो_flags(स्थिर काष्ठा खोलो_how *how, काष्ठा खोलो_flags *op);
बाह्य पूर्णांक __बंद_fd_get_file(अचिन्हित पूर्णांक fd, काष्ठा file **res);

दीर्घ करो_sys_ftruncate(अचिन्हित पूर्णांक fd, loff_t length, पूर्णांक small);
पूर्णांक chmod_common(स्थिर काष्ठा path *path, umode_t mode);
पूर्णांक करो_fchownat(पूर्णांक dfd, स्थिर अक्षर __user *filename, uid_t user, gid_t group,
		पूर्णांक flag);
पूर्णांक chown_common(स्थिर काष्ठा path *path, uid_t user, gid_t group);
बाह्य पूर्णांक vfs_खोलो(स्थिर काष्ठा path *, काष्ठा file *);

/*
 * inode.c
 */
बाह्य दीर्घ prune_icache_sb(काष्ठा super_block *sb, काष्ठा shrink_control *sc);
बाह्य व्योम inode_add_lru(काष्ठा inode *inode);
बाह्य पूर्णांक dentry_needs_हटाओ_privs(काष्ठा dentry *dentry);

/*
 * fs-ग_लिखोback.c
 */
बाह्य दीर्घ get_nr_dirty_inodes(व्योम);
बाह्य पूर्णांक invalidate_inodes(काष्ठा super_block *, bool);

/*
 * dcache.c
 */
बाह्य पूर्णांक d_set_mounted(काष्ठा dentry *dentry);
बाह्य दीर्घ prune_dcache_sb(काष्ठा super_block *sb, काष्ठा shrink_control *sc);
बाह्य काष्ठा dentry *d_alloc_cursor(काष्ठा dentry *);
बाह्य काष्ठा dentry * d_alloc_pseuकरो(काष्ठा super_block *, स्थिर काष्ठा qstr *);
बाह्य अक्षर *simple_dname(काष्ठा dentry *, अक्षर *, पूर्णांक);
बाह्य व्योम dput_to_list(काष्ठा dentry *, काष्ठा list_head *);
बाह्य व्योम shrink_dentry_list(काष्ठा list_head *);

/*
 * पढ़ो_ग_लिखो.c
 */
बाह्य पूर्णांक rw_verअगरy_area(पूर्णांक, काष्ठा file *, स्थिर loff_t *, माप_प्रकार);

/*
 * pipe.c
 */
बाह्य स्थिर काष्ठा file_operations pipefअगरo_fops;

/*
 * fs_pin.c
 */
बाह्य व्योम group_pin_समाप्त(काष्ठा hlist_head *p);
बाह्य व्योम mnt_pin_समाप्त(काष्ठा mount *m);

/*
 * fs/nsfs.c
 */
बाह्य स्थिर काष्ठा dentry_operations ns_dentry_operations;

/* direct-io.c: */
पूर्णांक sb_init_dio_करोne_wq(काष्ठा super_block *sb);

/*
 * fs/stat.c:
 */
पूर्णांक करो_statx(पूर्णांक dfd, स्थिर अक्षर __user *filename, अचिन्हित flags,
	     अचिन्हित पूर्णांक mask, काष्ठा statx __user *buffer);

/*
 * fs/splice.c:
 */
दीर्घ splice_file_to_pipe(काष्ठा file *in,
			 काष्ठा pipe_inode_info *opipe,
			 loff_t *offset,
			 माप_प्रकार len, अचिन्हित पूर्णांक flags);

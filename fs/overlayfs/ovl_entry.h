<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2011 Novell Inc.
 * Copyright (C) 2016 Red Hat, Inc.
 */

काष्ठा ovl_config अणु
	अक्षर *lowerdir;
	अक्षर *upperdir;
	अक्षर *workdir;
	bool शेष_permissions;
	bool redirect_dir;
	bool redirect_follow;
	स्थिर अक्षर *redirect_mode;
	bool index;
	bool uuid;
	bool nfs_export;
	पूर्णांक xino;
	bool metacopy;
	bool userxattr;
	bool ovl_अस्थिर;
पूर्ण;

काष्ठा ovl_sb अणु
	काष्ठा super_block *sb;
	dev_t pseuकरो_dev;
	/* Unusable (conflicting) uuid */
	bool bad_uuid;
	/* Used as a lower layer (but maybe also as upper) */
	bool is_lower;
पूर्ण;

काष्ठा ovl_layer अणु
	काष्ठा vfsmount *mnt;
	/* Trap in ovl inode cache */
	काष्ठा inode *trap;
	काष्ठा ovl_sb *fs;
	/* Index of this layer in fs root (upper idx == 0) */
	पूर्णांक idx;
	/* One fsid per unique underlying sb (upper fsid == 0) */
	पूर्णांक fsid;
पूर्ण;

काष्ठा ovl_path अणु
	स्थिर काष्ठा ovl_layer *layer;
	काष्ठा dentry *dentry;
पूर्ण;

/* निजी inक्रमmation held क्रम overlayfs's superblock */
काष्ठा ovl_fs अणु
	अचिन्हित पूर्णांक numlayer;
	/* Number of unique fs among layers including upper fs */
	अचिन्हित पूर्णांक numfs;
	स्थिर काष्ठा ovl_layer *layers;
	काष्ठा ovl_sb *fs;
	/* workbasedir is the path at workdir= mount option */
	काष्ठा dentry *workbasedir;
	/* workdir is the 'work' directory under workbasedir */
	काष्ठा dentry *workdir;
	/* index directory listing overlay inodes by origin file handle */
	काष्ठा dentry *indexdir;
	दीर्घ namelen;
	/* pathnames of lower and upper dirs, क्रम show_options */
	काष्ठा ovl_config config;
	/* creds of process who क्रमced instantiation of super block */
	स्थिर काष्ठा cred *creator_cred;
	bool क्षणिक_ख;
	bool noxattr;
	/* Did we take the inuse lock? */
	bool upperdir_locked;
	bool workdir_locked;
	bool share_whiteout;
	/* Traps in ovl inode cache */
	काष्ठा inode *workbasedir_trap;
	काष्ठा inode *workdir_trap;
	काष्ठा inode *indexdir_trap;
	/* -1: disabled, 0: same fs, 1..32: number of unused ino bits */
	पूर्णांक xino_mode;
	/* For allocation of non-persistent inode numbers */
	atomic_दीर्घ_t last_ino;
	/* Whiteout dentry cache */
	काष्ठा dentry *whiteout;
	/* r/o snapshot of upperdir sb's only taken on अस्थिर mounts */
	errseq_t errseq;
पूर्ण;

अटल अंतरभूत काष्ठा vfsmount *ovl_upper_mnt(काष्ठा ovl_fs *ofs)
अणु
	वापस ofs->layers[0].mnt;
पूर्ण

अटल अंतरभूत काष्ठा ovl_fs *OVL_FS(काष्ठा super_block *sb)
अणु
	वापस (काष्ठा ovl_fs *)sb->s_fs_info;
पूर्ण

अटल अंतरभूत bool ovl_should_sync(काष्ठा ovl_fs *ofs)
अणु
	वापस !ofs->config.ovl_अस्थिर;
पूर्ण

/* निजी inक्रमmation held क्रम every overlayfs dentry */
काष्ठा ovl_entry अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ flags;
		पूर्ण;
		काष्ठा rcu_head rcu;
	पूर्ण;
	अचिन्हित numlower;
	काष्ठा ovl_path lowerstack[];
पूर्ण;

काष्ठा ovl_entry *ovl_alloc_entry(अचिन्हित पूर्णांक numlower);

अटल अंतरभूत काष्ठा ovl_entry *OVL_E(काष्ठा dentry *dentry)
अणु
	वापस (काष्ठा ovl_entry *) dentry->d_fsdata;
पूर्ण

काष्ठा ovl_inode अणु
	जोड़ अणु
		काष्ठा ovl_dir_cache *cache;	/* directory */
		काष्ठा inode *lowerdata;	/* regular file */
	पूर्ण;
	स्थिर अक्षर *redirect;
	u64 version;
	अचिन्हित दीर्घ flags;
	काष्ठा inode vfs_inode;
	काष्ठा dentry *__upperdentry;
	काष्ठा inode *lower;

	/* synchronize copy up and more */
	काष्ठा mutex lock;
पूर्ण;

अटल अंतरभूत काष्ठा ovl_inode *OVL_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा ovl_inode, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा dentry *ovl_upperdentry_dereference(काष्ठा ovl_inode *oi)
अणु
	वापस READ_ONCE(oi->__upperdentry);
पूर्ण

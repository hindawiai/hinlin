<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _UFS_UFS_H
#घोषणा _UFS_UFS_H 1

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा UFS_MAX_GROUP_LOADED 8
#घोषणा UFS_CGNO_EMPTY ((अचिन्हित)-1)

काष्ठा ufs_sb_निजी_info;
काष्ठा ufs_cg_निजी_info;
काष्ठा ufs_csum;

काष्ठा ufs_sb_info अणु
	काष्ठा ufs_sb_निजी_info * s_uspi;
	काष्ठा ufs_csum	* s_csp;
	अचिन्हित s_bytesex;
	अचिन्हित s_flags;
	काष्ठा buffer_head ** s_ucg;
	काष्ठा ufs_cg_निजी_info * s_ucpi[UFS_MAX_GROUP_LOADED];
	अचिन्हित s_cgno[UFS_MAX_GROUP_LOADED];
	अचिन्हित लघु s_cg_loaded;
	अचिन्हित s_mount_opt;
	काष्ठा super_block *sb;
	पूर्णांक work_queued; /* non-zero अगर the delayed work is queued */
	काष्ठा delayed_work sync_work; /* FS sync delayed work */
	spinlock_t work_lock; /* protects sync_work and work_queued */
	काष्ठा mutex s_lock;
पूर्ण;

काष्ठा ufs_inode_info अणु
	जोड़ अणु
		__fs32	i_data[15];
		__u8	i_symlink[2 * 4 * 15];
		__fs64	u2_i_data[15];
	पूर्ण i_u1;
	__u32	i_flags;
	__u32	i_shaकरोw;
	__u32	i_unused1;
	__u32	i_unused2;
	__u32	i_oeftflag;
	__u16	i_osync;
	__u64	i_lastfrag;
	seqlock_t meta_lock;
	काष्ठा mutex	truncate_mutex;
	__u32   i_dir_start_lookup;
	काष्ठा inode vfs_inode;
पूर्ण;

/* mount options */
#घोषणा UFS_MOUNT_ONERROR		0x0000000F
#घोषणा UFS_MOUNT_ONERROR_PANIC		0x00000001
#घोषणा UFS_MOUNT_ONERROR_LOCK		0x00000002
#घोषणा UFS_MOUNT_ONERROR_UMOUNT	0x00000004
#घोषणा UFS_MOUNT_ONERROR_REPAIR	0x00000008

#घोषणा UFS_MOUNT_UFSTYPE		0x0000FFF0
#घोषणा UFS_MOUNT_UFSTYPE_OLD		0x00000010
#घोषणा UFS_MOUNT_UFSTYPE_44BSD		0x00000020
#घोषणा UFS_MOUNT_UFSTYPE_SUN		0x00000040
#घोषणा UFS_MOUNT_UFSTYPE_NEXTSTEP	0x00000080
#घोषणा UFS_MOUNT_UFSTYPE_NEXTSTEP_CD	0x00000100
#घोषणा UFS_MOUNT_UFSTYPE_OPENSTEP	0x00000200
#घोषणा UFS_MOUNT_UFSTYPE_SUNx86	0x00000400
#घोषणा UFS_MOUNT_UFSTYPE_HP	        0x00000800
#घोषणा UFS_MOUNT_UFSTYPE_UFS2		0x00001000
#घोषणा UFS_MOUNT_UFSTYPE_SUNOS		0x00002000

#घोषणा ufs_clear_opt(o,opt)	o &= ~UFS_MOUNT_##opt
#घोषणा ufs_set_opt(o,opt)	o |= UFS_MOUNT_##opt
#घोषणा ufs_test_opt(o,opt)	((o) & UFS_MOUNT_##opt)

/*
 * Debug code
 */
#अगर_घोषित CONFIG_UFS_DEBUG
#	define UFSD(f, a...)	अणु					\
		pr_debug("UFSD (%s, %d): %s:",				\
			__खाता__, __LINE__, __func__);		\
		pr_debug(f, ## a);					\
	पूर्ण
#अन्यथा
#	define UFSD(f, a...)	/**/
#पूर्ण_अगर

/* balloc.c */
बाह्य व्योम ufs_मुक्त_fragments (काष्ठा inode *, u64, अचिन्हित);
बाह्य व्योम ufs_मुक्त_blocks (काष्ठा inode *, u64, अचिन्हित);
बाह्य u64 ufs_new_fragments(काष्ठा inode *, व्योम *, u64, u64,
			     अचिन्हित, पूर्णांक *, काष्ठा page *);

/* cylinder.c */
बाह्य काष्ठा ufs_cg_निजी_info * ufs_load_cylinder (काष्ठा super_block *, अचिन्हित);
बाह्य व्योम ufs_put_cylinder (काष्ठा super_block *, अचिन्हित);

/* dir.c */
बाह्य स्थिर काष्ठा inode_operations ufs_dir_inode_operations;
बाह्य पूर्णांक ufs_add_link (काष्ठा dentry *, काष्ठा inode *);
बाह्य ino_t ufs_inode_by_name(काष्ठा inode *, स्थिर काष्ठा qstr *);
बाह्य पूर्णांक ufs_make_empty(काष्ठा inode *, काष्ठा inode *);
बाह्य काष्ठा ufs_dir_entry *ufs_find_entry(काष्ठा inode *, स्थिर काष्ठा qstr *, काष्ठा page **);
बाह्य पूर्णांक ufs_delete_entry(काष्ठा inode *, काष्ठा ufs_dir_entry *, काष्ठा page *);
बाह्य पूर्णांक ufs_empty_dir (काष्ठा inode *);
बाह्य काष्ठा ufs_dir_entry *ufs_करोtकरोt(काष्ठा inode *, काष्ठा page **);
बाह्य व्योम ufs_set_link(काष्ठा inode *dir, काष्ठा ufs_dir_entry *de,
			 काष्ठा page *page, काष्ठा inode *inode, bool update_बार);

/* file.c */
बाह्य स्थिर काष्ठा inode_operations ufs_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations ufs_file_operations;
बाह्य स्थिर काष्ठा address_space_operations ufs_aops;

/* ialloc.c */
बाह्य व्योम ufs_मुक्त_inode (काष्ठा inode *inode);
बाह्य काष्ठा inode * ufs_new_inode (काष्ठा inode *, umode_t);

/* inode.c */
बाह्य काष्ठा inode *ufs_iget(काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य पूर्णांक ufs_ग_लिखो_inode (काष्ठा inode *, काष्ठा ग_लिखोback_control *);
बाह्य पूर्णांक ufs_sync_inode (काष्ठा inode *);
बाह्य व्योम ufs_evict_inode (काष्ठा inode *);
बाह्य पूर्णांक ufs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		       काष्ठा iattr *attr);

/* namei.c */
बाह्य स्थिर काष्ठा file_operations ufs_dir_operations;

/* super.c */
बाह्य __म_लिखो(3, 4)
व्योम ufs_warning(काष्ठा super_block *, स्थिर अक्षर *, स्थिर अक्षर *, ...);
बाह्य __म_लिखो(3, 4)
व्योम ufs_error(काष्ठा super_block *, स्थिर अक्षर *, स्थिर अक्षर *, ...);
बाह्य __म_लिखो(3, 4)
व्योम ufs_panic(काष्ठा super_block *, स्थिर अक्षर *, स्थिर अक्षर *, ...);
व्योम ufs_mark_sb_dirty(काष्ठा super_block *sb);

अटल अंतरभूत काष्ठा ufs_sb_info *UFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा ufs_inode_info *UFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा ufs_inode_info, vfs_inode);
पूर्ण

/*
 * Give cylinder group number क्रम a file प्रणाली block.
 * Give cylinder group block number क्रम a file प्रणाली block.
 */
/* #घोषणा	ufs_dtog(d)	((d) / uspi->s_fpg) */
अटल अंतरभूत u64 ufs_dtog(काष्ठा ufs_sb_निजी_info * uspi, u64 b)
अणु
	करो_भाग(b, uspi->s_fpg);
	वापस b;
पूर्ण
/* #घोषणा	ufs_dtogd(d)	((d) % uspi->s_fpg) */
अटल अंतरभूत u32 ufs_dtogd(काष्ठा ufs_sb_निजी_info * uspi, u64 b)
अणु
	वापस करो_भाग(b, uspi->s_fpg);
पूर्ण

#पूर्ण_अगर /* _UFS_UFS_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#अगर_अघोषित __EROFS_INTERNAL_H
#घोषणा __EROFS_INTERNAL_H

#समावेश <linux/fs.h>
#समावेश <linux/dcache.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/bपन.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "erofs_fs.h"

/* redefine pr_fmt "erofs: " */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "erofs: " fmt

__म_लिखो(3, 4) व्योम _erofs_err(काष्ठा super_block *sb,
			       स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...);
#घोषणा erofs_err(sb, fmt, ...)	\
	_erofs_err(sb, __func__, fmt "\n", ##__VA_ARGS__)
__म_लिखो(3, 4) व्योम _erofs_info(काष्ठा super_block *sb,
			       स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...);
#घोषणा erofs_info(sb, fmt, ...) \
	_erofs_info(sb, __func__, fmt "\n", ##__VA_ARGS__)
#अगर_घोषित CONFIG_EROFS_FS_DEBUG
#घोषणा erofs_dbg(x, ...)       pr_debug(x "\n", ##__VA_ARGS__)
#घोषणा DBG_BUGON               BUG_ON
#अन्यथा
#घोषणा erofs_dbg(x, ...)       ((व्योम)0)
#घोषणा DBG_BUGON(x)            ((व्योम)(x))
#पूर्ण_अगर	/* !CONFIG_EROFS_FS_DEBUG */

/* EROFS_SUPER_MAGIC_V1 to represent the whole file प्रणाली */
#घोषणा EROFS_SUPER_MAGIC   EROFS_SUPER_MAGIC_V1

प्रकार u64 erofs_nid_t;
प्रकार u64 erofs_off_t;
/* data type क्रम fileप्रणाली-wide blocks number */
प्रकार u32 erofs_blk_t;

काष्ठा erofs_fs_context अणु
#अगर_घोषित CONFIG_EROFS_FS_ZIP
	/* current strategy of how to use managed cache */
	अचिन्हित अक्षर cache_strategy;
	/* strategy of sync decompression (false - स्वतः, true - क्रमce on) */
	bool पढ़ोahead_sync_decompress;

	/* threshold क्रम decompression synchronously */
	अचिन्हित पूर्णांक max_sync_decompress_pages;
#पूर्ण_अगर
	अचिन्हित पूर्णांक mount_opt;
पूर्ण;

/* all fileप्रणाली-wide lz4 configurations */
काष्ठा erofs_sb_lz4_info अणु
	/* # of pages needed क्रम EROFS lz4 rolling decompression */
	u16 max_distance_pages;
	/* maximum possible blocks क्रम pclusters in the fileप्रणाली */
	u16 max_pclusterblks;
पूर्ण;

काष्ठा erofs_sb_info अणु
#अगर_घोषित CONFIG_EROFS_FS_ZIP
	/* list क्रम all रेजिस्टरed superblocks, मुख्यly क्रम shrinker */
	काष्ठा list_head list;
	काष्ठा mutex umount_mutex;

	/* managed XArray arranged in physical block number */
	काष्ठा xarray managed_pslots;

	अचिन्हित पूर्णांक shrinker_run_no;
	u16 available_compr_algs;

	/* pseuकरो inode to manage cached pages */
	काष्ठा inode *managed_cache;

	काष्ठा erofs_sb_lz4_info lz4;
#पूर्ण_अगर	/* CONFIG_EROFS_FS_ZIP */
	u32 blocks;
	u32 meta_blkaddr;
#अगर_घोषित CONFIG_EROFS_FS_XATTR
	u32 xattr_blkaddr;
#पूर्ण_अगर

	/* inode slot unit size in bit shअगरt */
	अचिन्हित अक्षर islotbits;

	u32 sb_size;			/* total superblock size */
	u32 build_समय_nsec;
	u64 build_समय;

	/* what we really care is nid, rather than ino.. */
	erofs_nid_t root_nid;
	/* used क्रम statfs, f_files - f_favail */
	u64 inos;

	u8 uuid[16];                    /* 128-bit uuid क्रम volume */
	u8 volume_name[16];             /* volume name */
	u32 feature_compat;
	u32 feature_incompat;

	काष्ठा erofs_fs_context ctx;	/* options */
पूर्ण;

#घोषणा EROFS_SB(sb) ((काष्ठा erofs_sb_info *)(sb)->s_fs_info)
#घोषणा EROFS_I_SB(inode) ((काष्ठा erofs_sb_info *)(inode)->i_sb->s_fs_info)

/* Mount flags set via mount options or शेषs */
#घोषणा EROFS_MOUNT_XATTR_USER		0x00000010
#घोषणा EROFS_MOUNT_POSIX_ACL		0x00000020

#घोषणा clear_opt(ctx, option)	((ctx)->mount_opt &= ~EROFS_MOUNT_##option)
#घोषणा set_opt(ctx, option)	((ctx)->mount_opt |= EROFS_MOUNT_##option)
#घोषणा test_opt(ctx, option)	((ctx)->mount_opt & EROFS_MOUNT_##option)

क्रमागत अणु
	EROFS_ZIP_CACHE_DISABLED,
	EROFS_ZIP_CACHE_READAHEAD,
	EROFS_ZIP_CACHE_READAROUND
पूर्ण;

#अगर_घोषित CONFIG_EROFS_FS_ZIP
#घोषणा EROFS_LOCKED_MAGIC     (पूर्णांक_न्यून | 0xE0F510CCL)

/* basic unit of the workstation of a super_block */
काष्ठा erofs_workgroup अणु
	/* the workgroup index in the workstation */
	pgoff_t index;

	/* overall workgroup reference count */
	atomic_t refcount;
पूर्ण;

#अगर defined(CONFIG_SMP)
अटल अंतरभूत bool erofs_workgroup_try_to_मुक्तze(काष्ठा erofs_workgroup *grp,
						 पूर्णांक val)
अणु
	preempt_disable();
	अगर (val != atomic_cmpxchg(&grp->refcount, val, EROFS_LOCKED_MAGIC)) अणु
		preempt_enable();
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत व्योम erofs_workgroup_unमुक्तze(काष्ठा erofs_workgroup *grp,
					    पूर्णांक orig_val)
अणु
	/*
	 * other observers should notice all modअगरications
	 * in the मुक्तzing period.
	 */
	smp_mb();
	atomic_set(&grp->refcount, orig_val);
	preempt_enable();
पूर्ण

अटल अंतरभूत पूर्णांक erofs_रुको_on_workgroup_मुक्तzed(काष्ठा erofs_workgroup *grp)
अणु
	वापस atomic_cond_पढ़ो_relaxed(&grp->refcount,
					VAL != EROFS_LOCKED_MAGIC);
पूर्ण
#अन्यथा
अटल अंतरभूत bool erofs_workgroup_try_to_मुक्तze(काष्ठा erofs_workgroup *grp,
						 पूर्णांक val)
अणु
	preempt_disable();
	/* no need to spin on UP platक्रमms, let's just disable preemption. */
	अगर (val != atomic_पढ़ो(&grp->refcount)) अणु
		preempt_enable();
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत व्योम erofs_workgroup_unमुक्तze(काष्ठा erofs_workgroup *grp,
					    पूर्णांक orig_val)
अणु
	preempt_enable();
पूर्ण

अटल अंतरभूत पूर्णांक erofs_रुको_on_workgroup_मुक्तzed(काष्ठा erofs_workgroup *grp)
अणु
	पूर्णांक v = atomic_पढ़ो(&grp->refcount);

	/* workgroup is never मुक्तzed on uniprocessor प्रणालीs */
	DBG_BUGON(v == EROFS_LOCKED_MAGIC);
	वापस v;
पूर्ण
#पूर्ण_अगर	/* !CONFIG_SMP */
#पूर्ण_अगर	/* !CONFIG_EROFS_FS_ZIP */

/* we strictly follow PAGE_SIZE and no buffer head yet */
#घोषणा LOG_BLOCK_SIZE		PAGE_SHIFT

#अघोषित LOG_SECTORS_PER_BLOCK
#घोषणा LOG_SECTORS_PER_BLOCK	(PAGE_SHIFT - 9)

#अघोषित SECTORS_PER_BLOCK
#घोषणा SECTORS_PER_BLOCK	(1 << SECTORS_PER_BLOCK)

#घोषणा EROFS_BLKSIZ		(1 << LOG_BLOCK_SIZE)

#अगर (EROFS_BLKSIZ % 4096 || !EROFS_BLKSIZ)
#त्रुटि erofs cannot be used in this platक्रमm
#पूर्ण_अगर

#घोषणा ROOT_NID(sb)		((sb)->root_nid)

#घोषणा erofs_blknr(addr)       ((addr) / EROFS_BLKSIZ)
#घोषणा erofs_blkoff(addr)      ((addr) % EROFS_BLKSIZ)
#घोषणा blknr_to_addr(nr)       ((erofs_off_t)(nr) * EROFS_BLKSIZ)

अटल अंतरभूत erofs_off_t iloc(काष्ठा erofs_sb_info *sbi, erofs_nid_t nid)
अणु
	वापस blknr_to_addr(sbi->meta_blkaddr) + (nid << sbi->islotbits);
पूर्ण

#घोषणा EROFS_FEATURE_FUNCS(name, compat, feature) \
अटल अंतरभूत bool erofs_sb_has_##name(काष्ठा erofs_sb_info *sbi) \
अणु \
	वापस sbi->feature_##compat & EROFS_FEATURE_##feature; \
पूर्ण

EROFS_FEATURE_FUNCS(lz4_0padding, incompat, INCOMPAT_LZ4_0PADDING)
EROFS_FEATURE_FUNCS(compr_cfgs, incompat, INCOMPAT_COMPR_CFGS)
EROFS_FEATURE_FUNCS(big_pcluster, incompat, INCOMPAT_BIG_PCLUSTER)
EROFS_FEATURE_FUNCS(sb_chksum, compat, COMPAT_SB_CHKSUM)

/* atomic flag definitions */
#घोषणा EROFS_I_EA_INITED_BIT	0
#घोषणा EROFS_I_Z_INITED_BIT	1

/* bitlock definitions (arranged in reverse order) */
#घोषणा EROFS_I_BL_XATTR_BIT	(BITS_PER_LONG - 1)
#घोषणा EROFS_I_BL_Z_BIT	(BITS_PER_LONG - 2)

काष्ठा erofs_inode अणु
	erofs_nid_t nid;

	/* atomic flags (including bitlocks) */
	अचिन्हित दीर्घ flags;

	अचिन्हित अक्षर datalayout;
	अचिन्हित अक्षर inode_isize;
	अचिन्हित लघु xattr_isize;

	अचिन्हित पूर्णांक xattr_shared_count;
	अचिन्हित पूर्णांक *xattr_shared_xattrs;

	जोड़ अणु
		erofs_blk_t raw_blkaddr;
#अगर_घोषित CONFIG_EROFS_FS_ZIP
		काष्ठा अणु
			अचिन्हित लघु z_advise;
			अचिन्हित अक्षर  z_algorithmtype[2];
			अचिन्हित अक्षर  z_logical_clusterbits;
		पूर्ण;
#पूर्ण_अगर	/* CONFIG_EROFS_FS_ZIP */
	पूर्ण;
	/* the corresponding vfs inode */
	काष्ठा inode vfs_inode;
पूर्ण;

#घोषणा EROFS_I(ptr)	\
	container_of(ptr, काष्ठा erofs_inode, vfs_inode)

अटल अंतरभूत अचिन्हित दीर्घ erofs_inode_datablocks(काष्ठा inode *inode)
अणु
	/* since i_size cannot be changed */
	वापस DIV_ROUND_UP(inode->i_size, EROFS_BLKSIZ);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक erofs_bitrange(अचिन्हित पूर्णांक value, अचिन्हित पूर्णांक bit,
					  अचिन्हित पूर्णांक bits)
अणु

	वापस (value >> bit) & ((1 << bits) - 1);
पूर्ण


अटल अंतरभूत अचिन्हित पूर्णांक erofs_inode_version(अचिन्हित पूर्णांक value)
अणु
	वापस erofs_bitrange(value, EROFS_I_VERSION_BIT,
			      EROFS_I_VERSION_BITS);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक erofs_inode_datalayout(अचिन्हित पूर्णांक value)
अणु
	वापस erofs_bitrange(value, EROFS_I_DATALAYOUT_BIT,
			      EROFS_I_DATALAYOUT_BITS);
पूर्ण

बाह्य स्थिर काष्ठा super_operations erofs_sops;

बाह्य स्थिर काष्ठा address_space_operations erofs_raw_access_aops;
बाह्य स्थिर काष्ठा address_space_operations z_erofs_aops;

/*
 * Logical to physical block mapping
 *
 * Dअगरferent with other file प्रणालीs, it is used क्रम 2 access modes:
 *
 * 1) RAW access mode:
 *
 * Users pass a valid (m_lblk, m_lofs -- usually 0) pair,
 * and get the valid m_pblk, m_pofs and the दीर्घest m_len(in bytes).
 *
 * Note that m_lblk in the RAW access mode refers to the number of
 * the compressed ondisk block rather than the uncompressed
 * in-memory block क्रम the compressed file.
 *
 * m_pofs equals to m_lofs except क्रम the अंतरभूत data page.
 *
 * 2) Normal access mode:
 *
 * If the inode is not compressed, it has no dअगरference with
 * the RAW access mode. However, अगर the inode is compressed,
 * users should pass a valid (m_lblk, m_lofs) pair, and get
 * the needed m_pblk, m_pofs, m_len to get the compressed data
 * and the updated m_lblk, m_lofs which indicates the start
 * of the corresponding uncompressed data in the file.
 */
क्रमागत अणु
	BH_Zipped = BH_PrivateStart,
	BH_FullMapped,
पूर्ण;

/* Has a disk mapping */
#घोषणा EROFS_MAP_MAPPED	(1 << BH_Mapped)
/* Located in metadata (could be copied from bd_inode) */
#घोषणा EROFS_MAP_META		(1 << BH_Meta)
/* The extent has been compressed */
#घोषणा EROFS_MAP_ZIPPED	(1 << BH_Zipped)
/* The length of extent is full */
#घोषणा EROFS_MAP_FULL_MAPPED	(1 << BH_FullMapped)

काष्ठा erofs_map_blocks अणु
	erofs_off_t m_pa, m_la;
	u64 m_plen, m_llen;

	अचिन्हित पूर्णांक m_flags;

	काष्ठा page *mpage;
पूर्ण;

/* Flags used by erofs_map_blocks_flaपंचांगode() */
#घोषणा EROFS_GET_BLOCKS_RAW    0x0001

/* zmap.c */
#अगर_घोषित CONFIG_EROFS_FS_ZIP
पूर्णांक z_erofs_fill_inode(काष्ठा inode *inode);
पूर्णांक z_erofs_map_blocks_iter(काष्ठा inode *inode,
			    काष्ठा erofs_map_blocks *map,
			    पूर्णांक flags);
#अन्यथा
अटल अंतरभूत पूर्णांक z_erofs_fill_inode(काष्ठा inode *inode) अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत पूर्णांक z_erofs_map_blocks_iter(काष्ठा inode *inode,
					  काष्ठा erofs_map_blocks *map,
					  पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर	/* !CONFIG_EROFS_FS_ZIP */

/* data.c */
काष्ठा page *erofs_get_meta_page(काष्ठा super_block *sb, erofs_blk_t blkaddr);

/* inode.c */
अटल अंतरभूत अचिन्हित दीर्घ erofs_inode_hash(erofs_nid_t nid)
अणु
#अगर BITS_PER_LONG == 32
	वापस (nid >> 32) ^ (nid & 0xffffffff);
#अन्यथा
	वापस nid;
#पूर्ण_अगर
पूर्ण

बाह्य स्थिर काष्ठा inode_operations erofs_generic_iops;
बाह्य स्थिर काष्ठा inode_operations erofs_symlink_iops;
बाह्य स्थिर काष्ठा inode_operations erofs_fast_symlink_iops;

काष्ठा inode *erofs_iget(काष्ठा super_block *sb, erofs_nid_t nid, bool dir);
पूर्णांक erofs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		  काष्ठा kstat *stat, u32 request_mask,
		  अचिन्हित पूर्णांक query_flags);

/* namei.c */
बाह्य स्थिर काष्ठा inode_operations erofs_dir_iops;

पूर्णांक erofs_namei(काष्ठा inode *dir, काष्ठा qstr *name,
		erofs_nid_t *nid, अचिन्हित पूर्णांक *d_type);

/* dir.c */
बाह्य स्थिर काष्ठा file_operations erofs_dir_fops;

अटल अंतरभूत व्योम *erofs_vm_map_ram(काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक retried = 0;

	जबतक (1) अणु
		व्योम *p = vm_map_ram(pages, count, -1);

		/* retry two more बार (totally 3 बार) */
		अगर (p || ++retried >= 3)
			वापस p;
		vm_unmap_aliases();
	पूर्ण
	वापस शून्य;
पूर्ण

/* pcpubuf.c */
व्योम *erofs_get_pcpubuf(अचिन्हित पूर्णांक requiredpages);
व्योम erofs_put_pcpubuf(व्योम *ptr);
पूर्णांक erofs_pcpubuf_growsize(अचिन्हित पूर्णांक nrpages);
व्योम erofs_pcpubuf_init(व्योम);
व्योम erofs_pcpubuf_निकास(व्योम);

/* utils.c / zdata.c */
काष्ठा page *erofs_allocpage(काष्ठा list_head *pool, gfp_t gfp);

#अगर_घोषित CONFIG_EROFS_FS_ZIP
पूर्णांक erofs_workgroup_put(काष्ठा erofs_workgroup *grp);
काष्ठा erofs_workgroup *erofs_find_workgroup(काष्ठा super_block *sb,
					     pgoff_t index);
काष्ठा erofs_workgroup *erofs_insert_workgroup(काष्ठा super_block *sb,
					       काष्ठा erofs_workgroup *grp);
व्योम erofs_workgroup_मुक्त_rcu(काष्ठा erofs_workgroup *grp);
व्योम erofs_shrinker_रेजिस्टर(काष्ठा super_block *sb);
व्योम erofs_shrinker_unरेजिस्टर(काष्ठा super_block *sb);
पूर्णांक __init erofs_init_shrinker(व्योम);
व्योम erofs_निकास_shrinker(व्योम);
पूर्णांक __init z_erofs_init_zip_subप्रणाली(व्योम);
व्योम z_erofs_निकास_zip_subप्रणाली(व्योम);
पूर्णांक erofs_try_to_मुक्त_all_cached_pages(काष्ठा erofs_sb_info *sbi,
				       काष्ठा erofs_workgroup *egrp);
पूर्णांक erofs_try_to_मुक्त_cached_page(काष्ठा address_space *mapping,
				  काष्ठा page *page);
पूर्णांक z_erofs_load_lz4_config(काष्ठा super_block *sb,
			    काष्ठा erofs_super_block *dsb,
			    काष्ठा z_erofs_lz4_cfgs *lz4, पूर्णांक len);
#अन्यथा
अटल अंतरभूत व्योम erofs_shrinker_रेजिस्टर(काष्ठा super_block *sb) अणुपूर्ण
अटल अंतरभूत व्योम erofs_shrinker_unरेजिस्टर(काष्ठा super_block *sb) अणुपूर्ण
अटल अंतरभूत पूर्णांक erofs_init_shrinker(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम erofs_निकास_shrinker(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक z_erofs_init_zip_subप्रणाली(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम z_erofs_निकास_zip_subप्रणाली(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक z_erofs_load_lz4_config(काष्ठा super_block *sb,
				  काष्ठा erofs_super_block *dsb,
				  काष्ठा z_erofs_lz4_cfgs *lz4, पूर्णांक len)
अणु
	अगर (lz4 || dsb->u1.lz4_max_distance) अणु
		erofs_err(sb, "lz4 algorithm isn't enabled");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* !CONFIG_EROFS_FS_ZIP */

#घोषणा EFSCORRUPTED    EUCLEAN         /* Fileप्रणाली is corrupted */

#पूर्ण_अगर	/* __EROFS_INTERNAL_H */


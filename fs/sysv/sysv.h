<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SYSV_H
#घोषणा _SYSV_H

#समावेश <linux/buffer_head.h>

प्रकार __u16 __bitwise __fs16;
प्रकार __u32 __bitwise __fs32;

#समावेश <linux/sysv_fs.h>

/*
 * SystemV/V7/Coherent super-block data in memory
 *
 * The SystemV/V7/Coherent superblock contains dynamic data (it माला_लो modअगरied
 * जबतक the प्रणाली is running). This is in contrast to the Minix and Berkeley
 * fileप्रणालीs (where the superblock is never modअगरied). This affects the
 * sync() operation: we must keep the superblock in a disk buffer and use this
 * one as our "working copy".
 */

काष्ठा sysv_sb_info अणु
	काष्ठा super_block *s_sb;	/* VFS superblock */
	पूर्णांक	       s_type;		/* file प्रणाली type: FSTYPE_अणुXENIX|SYSV|COHपूर्ण */
	अक्षर	       s_bytesex;	/* bytesex (le/be/pdp) */
	अचिन्हित पूर्णांक   s_inodes_per_block;	/* number of inodes per block */
	अचिन्हित पूर्णांक   s_inodes_per_block_1;	/* inodes_per_block - 1 */
	अचिन्हित पूर्णांक   s_inodes_per_block_bits;	/* log2(inodes_per_block) */
	अचिन्हित पूर्णांक   s_ind_per_block;		/* number of indirections per block */
	अचिन्हित पूर्णांक   s_ind_per_block_bits;	/* log2(ind_per_block) */
	अचिन्हित पूर्णांक   s_ind_per_block_2;	/* ind_per_block ^ 2 */
	अचिन्हित पूर्णांक   s_toobig_block;		/* 10 + ipb + ipb^2 + ipb^3 */
	अचिन्हित पूर्णांक   s_block_base;	/* physical block number of block 0 */
	अचिन्हित लघु s_fic_size;	/* मुक्त inode cache size, NICINOD */
	अचिन्हित लघु s_flc_size;	/* मुक्त block list chunk size, NICFREE */
	/* The superblock is kept in one or two disk buffers: */
	काष्ठा buffer_head *s_bh1;
	काष्ठा buffer_head *s_bh2;
	/* These are poपूर्णांकers पूर्णांकo the disk buffer, to compensate क्रम
	   dअगरferent superblock layout. */
	अक्षर *         s_sbd1;		/* entire superblock data, क्रम part 1 */
	अक्षर *         s_sbd2;		/* entire superblock data, क्रम part 2 */
	__fs16         *s_sb_fic_count;	/* poपूर्णांकer to s_sbd->s_ninode */
        sysv_ino_t     *s_sb_fic_inodes; /* poपूर्णांकer to s_sbd->s_inode */
	__fs16         *s_sb_total_मुक्त_inodes; /* poपूर्णांकer to s_sbd->s_tinode */
	__fs16         *s_bcache_count;	/* poपूर्णांकer to s_sbd->s_nमुक्त */
	sysv_zone_t    *s_bcache;	/* poपूर्णांकer to s_sbd->s_मुक्त */
	__fs32         *s_मुक्त_blocks;	/* poपूर्णांकer to s_sbd->s_tमुक्त */
	__fs32         *s_sb_समय;	/* poपूर्णांकer to s_sbd->s_समय */
	__fs32         *s_sb_state;	/* poपूर्णांकer to s_sbd->s_state, only FSTYPE_SYSV */
	/* We keep those superblock entities that करोn't change here;
	   this saves us an indirection and perhaps a conversion. */
	u32            s_firstinodezone; /* index of first inode zone */
	u32            s_firstdatazone;	/* same as s_sbd->s_isize */
	u32            s_ninodes;	/* total number of inodes */
	u32            s_ndatazones;	/* total number of data zones */
	u32            s_nzones;	/* same as s_sbd->s_fsize */
	u16	       s_namelen;       /* max length of dir entry */
	पूर्णांक	       s_क्रमced_ro;
	काष्ठा mutex s_lock;
पूर्ण;

/*
 * SystemV/V7/Coherent FS inode data in memory
 */
काष्ठा sysv_inode_info अणु
	__fs32		i_data[13];
	u32		i_dir_start_lookup;
	काष्ठा inode	vfs_inode;
पूर्ण;


अटल अंतरभूत काष्ठा sysv_inode_info *SYSV_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा sysv_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा sysv_sb_info *SYSV_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण


/* identअगरy the FS in memory */
क्रमागत अणु
	FSTYPE_NONE = 0,
	FSTYPE_XENIX,
	FSTYPE_SYSV4,
	FSTYPE_SYSV2,
	FSTYPE_COH,
	FSTYPE_V7,
	FSTYPE_AFS,
	FSTYPE_END,
पूर्ण;

#घोषणा SYSV_MAGIC_BASE		0x012FF7B3

#घोषणा XENIX_SUPER_MAGIC	(SYSV_MAGIC_BASE+FSTYPE_XENIX)
#घोषणा SYSV4_SUPER_MAGIC	(SYSV_MAGIC_BASE+FSTYPE_SYSV4)
#घोषणा SYSV2_SUPER_MAGIC	(SYSV_MAGIC_BASE+FSTYPE_SYSV2)
#घोषणा COH_SUPER_MAGIC		(SYSV_MAGIC_BASE+FSTYPE_COH)


/* Admissible values क्रम i_nlink: 0.._LINK_MAX */
क्रमागत अणु
	XENIX_LINK_MAX	=	126,	/* ?? */
	SYSV_LINK_MAX	=	126,	/* 127? 251? */
	V7_LINK_MAX     =	126,	/* ?? */
	COH_LINK_MAX	=	10000,
पूर्ण;


अटल अंतरभूत व्योम dirty_sb(काष्ठा super_block *sb)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);

	mark_buffer_dirty(sbi->s_bh1);
	अगर (sbi->s_bh1 != sbi->s_bh2)
		mark_buffer_dirty(sbi->s_bh2);
पूर्ण


/* ialloc.c */
बाह्य काष्ठा sysv_inode *sysv_raw_inode(काष्ठा super_block *, अचिन्हित,
			काष्ठा buffer_head **);
बाह्य काष्ठा inode * sysv_new_inode(स्थिर काष्ठा inode *, umode_t);
बाह्य व्योम sysv_मुक्त_inode(काष्ठा inode *);
बाह्य अचिन्हित दीर्घ sysv_count_मुक्त_inodes(काष्ठा super_block *);

/* balloc.c */
बाह्य sysv_zone_t sysv_new_block(काष्ठा super_block *);
बाह्य व्योम sysv_मुक्त_block(काष्ठा super_block *, sysv_zone_t);
बाह्य अचिन्हित दीर्घ sysv_count_मुक्त_blocks(काष्ठा super_block *);

/* itree.c */
बाह्य व्योम sysv_truncate(काष्ठा inode *);
बाह्य पूर्णांक sysv_prepare_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len);

/* inode.c */
बाह्य काष्ठा inode *sysv_iget(काष्ठा super_block *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक sysv_ग_लिखो_inode(काष्ठा inode *, काष्ठा ग_लिखोback_control *wbc);
बाह्य पूर्णांक sysv_sync_inode(काष्ठा inode *);
बाह्य व्योम sysv_set_inode(काष्ठा inode *, dev_t);
बाह्य पूर्णांक sysv_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *,
			काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य पूर्णांक sysv_init_icache(व्योम);
बाह्य व्योम sysv_destroy_icache(व्योम);


/* dir.c */
बाह्य काष्ठा sysv_dir_entry *sysv_find_entry(काष्ठा dentry *, काष्ठा page **);
बाह्य पूर्णांक sysv_add_link(काष्ठा dentry *, काष्ठा inode *);
बाह्य पूर्णांक sysv_delete_entry(काष्ठा sysv_dir_entry *, काष्ठा page *);
बाह्य पूर्णांक sysv_make_empty(काष्ठा inode *, काष्ठा inode *);
बाह्य पूर्णांक sysv_empty_dir(काष्ठा inode *);
बाह्य व्योम sysv_set_link(काष्ठा sysv_dir_entry *, काष्ठा page *,
			काष्ठा inode *);
बाह्य काष्ठा sysv_dir_entry *sysv_करोtकरोt(काष्ठा inode *, काष्ठा page **);
बाह्य ino_t sysv_inode_by_name(काष्ठा dentry *);


बाह्य स्थिर काष्ठा inode_operations sysv_file_inode_operations;
बाह्य स्थिर काष्ठा inode_operations sysv_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations sysv_file_operations;
बाह्य स्थिर काष्ठा file_operations sysv_dir_operations;
बाह्य स्थिर काष्ठा address_space_operations sysv_aops;
बाह्य स्थिर काष्ठा super_operations sysv_sops;


क्रमागत अणु
	BYTESEX_LE,
	BYTESEX_PDP,
	BYTESEX_BE,
पूर्ण;

अटल अंतरभूत u32 PDP_swab(u32 x)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	वापस ((x & 0xffff) << 16) | ((x & 0xffff0000) >> 16);
#अन्यथा
#अगर_घोषित __BIG_ENDIAN
	वापस ((x & 0xff00ff) << 8) | ((x & 0xff00ff00) >> 8);
#अन्यथा
#त्रुटि BYTESEX
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __u32 fs32_to_cpu(काष्ठा sysv_sb_info *sbi, __fs32 n)
अणु
	अगर (sbi->s_bytesex == BYTESEX_PDP)
		वापस PDP_swab((__क्रमce __u32)n);
	अन्यथा अगर (sbi->s_bytesex == BYTESEX_LE)
		वापस le32_to_cpu((__क्रमce __le32)n);
	अन्यथा
		वापस be32_to_cpu((__क्रमce __be32)n);
पूर्ण

अटल अंतरभूत __fs32 cpu_to_fs32(काष्ठा sysv_sb_info *sbi, __u32 n)
अणु
	अगर (sbi->s_bytesex == BYTESEX_PDP)
		वापस (__क्रमce __fs32)PDP_swab(n);
	अन्यथा अगर (sbi->s_bytesex == BYTESEX_LE)
		वापस (__क्रमce __fs32)cpu_to_le32(n);
	अन्यथा
		वापस (__क्रमce __fs32)cpu_to_be32(n);
पूर्ण

अटल अंतरभूत __fs32 fs32_add(काष्ठा sysv_sb_info *sbi, __fs32 *n, पूर्णांक d)
अणु
	अगर (sbi->s_bytesex == BYTESEX_PDP)
		*(__u32*)n = PDP_swab(PDP_swab(*(__u32*)n)+d);
	अन्यथा अगर (sbi->s_bytesex == BYTESEX_LE)
		le32_add_cpu((__le32 *)n, d);
	अन्यथा
		be32_add_cpu((__be32 *)n, d);
	वापस *n;
पूर्ण

अटल अंतरभूत __u16 fs16_to_cpu(काष्ठा sysv_sb_info *sbi, __fs16 n)
अणु
	अगर (sbi->s_bytesex != BYTESEX_BE)
		वापस le16_to_cpu((__क्रमce __le16)n);
	अन्यथा
		वापस be16_to_cpu((__क्रमce __be16)n);
पूर्ण

अटल अंतरभूत __fs16 cpu_to_fs16(काष्ठा sysv_sb_info *sbi, __u16 n)
अणु
	अगर (sbi->s_bytesex != BYTESEX_BE)
		वापस (__क्रमce __fs16)cpu_to_le16(n);
	अन्यथा
		वापस (__क्रमce __fs16)cpu_to_be16(n);
पूर्ण

अटल अंतरभूत __fs16 fs16_add(काष्ठा sysv_sb_info *sbi, __fs16 *n, पूर्णांक d)
अणु
	अगर (sbi->s_bytesex != BYTESEX_BE)
		le16_add_cpu((__le16 *)n, d);
	अन्यथा
		be16_add_cpu((__be16 *)n, d);
	वापस *n;
पूर्ण

#पूर्ण_अगर /* _SYSV_H */

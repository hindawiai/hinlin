<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SYSV_FS_H
#घोषणा _LINUX_SYSV_FS_H

#घोषणा __packed2__	__attribute__((packed, aligned(2)))


#अगर_अघोषित __KERNEL__
प्रकार u16 __fs16;
प्रकार u32 __fs16;
#पूर्ण_अगर

/* inode numbers are 16 bit */
प्रकार __fs16 sysv_ino_t;

/* Block numbers are 24 bit, someबार stored in 32 bit.
   On Coherent FS, they are always stored in PDP-11 manner: the least
   signअगरicant 16 bits come last. */
प्रकार __fs32 sysv_zone_t;

/* 0 is non-existent */
#घोषणा SYSV_BADBL_INO	1	/* inode of bad blocks file */
#घोषणा SYSV_ROOT_INO	2	/* inode of root directory */


/* Xenix super-block data on disk */
#घोषणा XENIX_NICINOD	100	/* number of inode cache entries */
#घोषणा XENIX_NICFREE	100	/* number of मुक्त block list chunk entries */
काष्ठा xenix_super_block अणु
	__fs16		s_isize; /* index of first data zone */
	__fs32		s_fsize __packed2__; /* total number of zones of this fs */
	/* the start of the मुक्त block list: */
	__fs16		s_nमुक्त;	/* number of मुक्त blocks in s_मुक्त, <= XENIX_NICFREE */
	sysv_zone_t	s_मुक्त[XENIX_NICFREE]; /* first मुक्त block list chunk */
	/* the cache of मुक्त inodes: */
	__fs16		s_ninode; /* number of मुक्त inodes in s_inode, <= XENIX_NICINOD */
	sysv_ino_t	s_inode[XENIX_NICINOD]; /* some मुक्त inodes */
	/* locks, not used by Linux: */
	अक्षर		s_flock;	/* lock during मुक्त block list manipulation */
	अक्षर		s_ilock;	/* lock during inode cache manipulation */
	अक्षर		s_भ_शेष;		/* super-block modअगरied flag */
	अक्षर		s_ronly;	/* flag whether fs is mounted पढ़ो-only */
	__fs32		s_समय __packed2__; /* समय of last super block update */
	__fs32		s_tमुक्त __packed2__; /* total number of मुक्त zones */
	__fs16		s_tinode;	/* total number of मुक्त inodes */
	__fs16		s_dinfo[4];	/* device inक्रमmation ?? */
	अक्षर		s_fname[6];	/* file प्रणाली volume name */
	अक्षर		s_fpack[6];	/* file प्रणाली pack name */
	अक्षर		s_clean;	/* set to 0x46 when fileप्रणाली is properly unmounted */
	अक्षर		s_fill[371];
	s32		s_magic;	/* version of file प्रणाली */
	__fs32		s_type;		/* type of file प्रणाली: 1 क्रम 512 byte blocks
								2 क्रम 1024 byte blocks
								3 क्रम 2048 byte blocks */
								
पूर्ण;

/*
 * SystemV FS comes in two variants:
 * sysv2: System V Release 2 (e.g. Microport), काष्ठाure elements aligned(2).
 * sysv4: System V Release 4 (e.g. Consensys), काष्ठाure elements aligned(4).
 */
#घोषणा SYSV_NICINOD	100	/* number of inode cache entries */
#घोषणा SYSV_NICFREE	50	/* number of मुक्त block list chunk entries */

/* SystemV4 super-block data on disk */
काष्ठा sysv4_super_block अणु
	__fs16	s_isize;	/* index of first data zone */
	u16	s_pad0;
	__fs32	s_fsize;	/* total number of zones of this fs */
	/* the start of the मुक्त block list: */
	__fs16	s_nमुक्त;	/* number of मुक्त blocks in s_मुक्त, <= SYSV_NICFREE */
	u16	s_pad1;
	sysv_zone_t	s_मुक्त[SYSV_NICFREE]; /* first मुक्त block list chunk */
	/* the cache of मुक्त inodes: */
	__fs16	s_ninode;	/* number of मुक्त inodes in s_inode, <= SYSV_NICINOD */
	u16	s_pad2;
	sysv_ino_t     s_inode[SYSV_NICINOD]; /* some मुक्त inodes */
	/* locks, not used by Linux: */
	अक्षर	s_flock;	/* lock during मुक्त block list manipulation */
	अक्षर	s_ilock;	/* lock during inode cache manipulation */
	अक्षर	s_भ_शेष;		/* super-block modअगरied flag */
	अक्षर	s_ronly;	/* flag whether fs is mounted पढ़ो-only */
	__fs32	s_समय;		/* समय of last super block update */
	__fs16	s_dinfo[4];	/* device inक्रमmation ?? */
	__fs32	s_tमुक्त;	/* total number of मुक्त zones */
	__fs16	s_tinode;	/* total number of मुक्त inodes */
	u16	s_pad3;
	अक्षर	s_fname[6];	/* file प्रणाली volume name */
	अक्षर	s_fpack[6];	/* file प्रणाली pack name */
	s32	s_fill[12];
	__fs32	s_state;	/* file प्रणाली state: 0x7c269d38-s_समय means clean */
	s32	s_magic;	/* version of file प्रणाली */
	__fs32	s_type;		/* type of file प्रणाली: 1 क्रम 512 byte blocks
								2 क्रम 1024 byte blocks */
पूर्ण;

/* SystemV2 super-block data on disk */
काष्ठा sysv2_super_block अणु
	__fs16	s_isize; 		/* index of first data zone */
	__fs32	s_fsize __packed2__;	/* total number of zones of this fs */
	/* the start of the मुक्त block list: */
	__fs16	s_nमुक्त;		/* number of मुक्त blocks in s_मुक्त, <= SYSV_NICFREE */
	sysv_zone_t s_मुक्त[SYSV_NICFREE];	/* first मुक्त block list chunk */
	/* the cache of मुक्त inodes: */
	__fs16	s_ninode;		/* number of मुक्त inodes in s_inode, <= SYSV_NICINOD */
	sysv_ino_t     s_inode[SYSV_NICINOD]; /* some मुक्त inodes */
	/* locks, not used by Linux: */
	अक्षर	s_flock;		/* lock during मुक्त block list manipulation */
	अक्षर	s_ilock;		/* lock during inode cache manipulation */
	अक्षर	s_भ_शेष;			/* super-block modअगरied flag */
	अक्षर	s_ronly;		/* flag whether fs is mounted पढ़ो-only */
	__fs32	s_समय __packed2__;	/* समय of last super block update */
	__fs16	s_dinfo[4];		/* device inक्रमmation ?? */
	__fs32	s_tमुक्त __packed2__;	/* total number of मुक्त zones */
	__fs16	s_tinode;		/* total number of मुक्त inodes */
	अक्षर	s_fname[6];		/* file प्रणाली volume name */
	अक्षर	s_fpack[6];		/* file प्रणाली pack name */
	s32	s_fill[14];
	__fs32	s_state;		/* file प्रणाली state: 0xcb096f43 means clean */
	s32	s_magic;		/* version of file प्रणाली */
	__fs32	s_type;			/* type of file प्रणाली: 1 क्रम 512 byte blocks
								2 क्रम 1024 byte blocks */
पूर्ण;

/* V7 super-block data on disk */
#घोषणा V7_NICINOD     100     /* number of inode cache entries */
#घोषणा V7_NICFREE     50      /* number of मुक्त block list chunk entries */
काष्ठा v7_super_block अणु
	__fs16 s_isize;        /* index of first data zone */
	__fs32 s_fsize __packed2__; /* total number of zones of this fs */
	/* the start of the मुक्त block list: */
	__fs16 s_nमुक्त;        /* number of मुक्त blocks in s_मुक्त, <= V7_NICFREE */
	sysv_zone_t s_मुक्त[V7_NICFREE]; /* first मुक्त block list chunk */
	/* the cache of मुक्त inodes: */
	__fs16 s_ninode;       /* number of मुक्त inodes in s_inode, <= V7_NICINOD */
	sysv_ino_t      s_inode[V7_NICINOD]; /* some मुक्त inodes */
	/* locks, not used by Linux or V7: */
	अक्षर    s_flock;        /* lock during मुक्त block list manipulation */
	अक्षर    s_ilock;        /* lock during inode cache manipulation */
	अक्षर    s_भ_शेष;         /* super-block modअगरied flag */
	अक्षर    s_ronly;        /* flag whether fs is mounted पढ़ो-only */
	__fs32  s_समय __packed2__; /* समय of last super block update */
	/* the following fields are not मुख्यtained by V7: */
	__fs32  s_tमुक्त __packed2__; /* total number of मुक्त zones */
	__fs16  s_tinode;       /* total number of मुक्त inodes */
	__fs16  s_m;            /* पूर्णांकerleave factor */
	__fs16  s_n;            /* पूर्णांकerleave factor */
	अक्षर    s_fname[6];     /* file प्रणाली name */
	अक्षर    s_fpack[6];     /* file प्रणाली pack name */
पूर्ण;
/* Constants to aid sanity checking */
/* This is not a hard limit, nor enक्रमced by v7 kernel. It's actually just
 * the limit used by Seventh Edition's ls, though is high enough to assume
 * that no reasonable file प्रणाली would have that much entries in root
 * directory. Thus, अगर we see anything higher, we just probably got the
 * endiannes wrong. */
#घोषणा V7_NखाताS	1024
/* The disk addresses are three-byte (despite direct block addresses being
 * aligned word-wise in inode). If the most signअगरicant byte is non-zero,
 * something is most likely wrong (not a fileप्रणाली, bad bytesex). */
#घोषणा V7_MAXSIZE	0x00ffffff

/* Coherent super-block data on disk */
#घोषणा COH_NICINOD	100	/* number of inode cache entries */
#घोषणा COH_NICFREE	64	/* number of मुक्त block list chunk entries */
काष्ठा coh_super_block अणु
	__fs16		s_isize;	/* index of first data zone */
	__fs32		s_fsize __packed2__; /* total number of zones of this fs */
	/* the start of the मुक्त block list: */
	__fs16 s_nमुक्त;	/* number of मुक्त blocks in s_मुक्त, <= COH_NICFREE */
	sysv_zone_t	s_मुक्त[COH_NICFREE] __packed2__; /* first मुक्त block list chunk */
	/* the cache of मुक्त inodes: */
	__fs16		s_ninode;	/* number of मुक्त inodes in s_inode, <= COH_NICINOD */
	sysv_ino_t	s_inode[COH_NICINOD]; /* some मुक्त inodes */
	/* locks, not used by Linux: */
	अक्षर		s_flock;	/* lock during मुक्त block list manipulation */
	अक्षर		s_ilock;	/* lock during inode cache manipulation */
	अक्षर		s_भ_शेष;		/* super-block modअगरied flag */
	अक्षर		s_ronly;	/* flag whether fs is mounted पढ़ो-only */
	__fs32		s_समय __packed2__; /* समय of last super block update */
	__fs32		s_tमुक्त __packed2__; /* total number of मुक्त zones */
	__fs16		s_tinode;	/* total number of मुक्त inodes */
	__fs16		s_पूर्णांकerleave_m;	/* पूर्णांकerleave factor */
	__fs16		s_पूर्णांकerleave_n;
	अक्षर		s_fname[6];	/* file प्रणाली volume name */
	अक्षर		s_fpack[6];	/* file प्रणाली pack name */
	__fs32		s_unique;	/* zero, not used */
पूर्ण;

/* SystemV/Coherent inode data on disk */
काष्ठा sysv_inode अणु
	__fs16 i_mode;
	__fs16 i_nlink;
	__fs16 i_uid;
	__fs16 i_gid;
	__fs32 i_size;
	u8  i_data[3*(10+1+1+1)];
	u8  i_gen;
	__fs32 i_aसमय;	/* समय of last access */
	__fs32 i_mसमय;	/* समय of last modअगरication */
	__fs32 i_स_समय;	/* समय of creation */
पूर्ण;

/* SystemV/Coherent directory entry on disk */
#घोषणा SYSV_NAMELEN	14	/* max size of name in काष्ठा sysv_dir_entry */
काष्ठा sysv_dir_entry अणु
	sysv_ino_t inode;
	अक्षर name[SYSV_NAMELEN]; /* up to 14 अक्षरacters, the rest are zeroes */
पूर्ण;

#घोषणा SYSV_सूचीSIZE	माप(काष्ठा sysv_dir_entry)	/* size of every directory entry */

#पूर्ण_अगर /* _LINUX_SYSV_FS_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2001
 */
#अगर_अघोषित _H_JFS_DINODE
#घोषणा _H_JFS_DINODE

/*
 *	jfs_dinode.h: on-disk inode manager
 */

#घोषणा INODESLOTSIZE		128
#घोषणा L2INODESLOTSIZE		7
#घोषणा log2INODESIZE		9	/* log2(bytes per dinode) */


/*
 *	on-disk inode : 512 bytes
 *
 * note: align 64-bit fields on 8-byte boundary.
 */
काष्ठा dinode अणु
	/*
	 *	I. base area (128 bytes)
	 *	------------------------
	 *
	 * define generic/POSIX attributes
	 */
	__le32 di_inostamp;	/* 4: stamp to show inode beदीर्घs to fileset */
	__le32 di_fileset;	/* 4: fileset number */
	__le32 di_number;	/* 4: inode number, aka file serial number */
	__le32 di_gen;		/* 4: inode generation number */

	pxd_t di_ixpxd;		/* 8: inode extent descriptor */

	__le64 di_size;		/* 8: size */
	__le64 di_nblocks;	/* 8: number of blocks allocated */

	__le32 di_nlink;	/* 4: number of links to the object */

	__le32 di_uid;		/* 4: user id of owner */
	__le32 di_gid;		/* 4: group id of owner */

	__le32 di_mode;		/* 4: attribute, क्रमmat and permission */

	काष्ठा बारtruc_t di_aसमय;	/* 8: समय last data accessed */
	काष्ठा बारtruc_t di_स_समय;	/* 8: समय last status changed */
	काष्ठा बारtruc_t di_mसमय;	/* 8: समय last data modअगरied */
	काष्ठा बारtruc_t di_oसमय;	/* 8: समय created */

	dxd_t di_acl;		/* 16: acl descriptor */

	dxd_t di_ea;		/* 16: ea descriptor */

	__le32 di_next_index;	/* 4: Next available dir_table index */

	__le32 di_acltype;	/* 4: Type of ACL */

	/*
	 *	Extension Areas.
	 *
	 *	Historically, the inode was partitioned पूर्णांकo 4 128-byte areas,
	 *	the last 3 being defined as जोड़s which could have multiple
	 *	uses.  The first 96 bytes had been completely unused until
	 *	an index table was added to the directory.  It is now more
	 *	useful to describe the last 3/4 of the inode as a single
	 *	जोड़.  We would probably be better off redesigning the
	 *	entire काष्ठाure from scratch, but we करोn't want to अवरोध
	 *	commonality with OS/2's JFS at this समय.
	 */
	जोड़ अणु
		काष्ठा अणु
			/*
			 * This table contains the inक्रमmation needed to
			 * find a directory entry from a 32-bit index.
			 * If the index is small enough, the table is अंतरभूत,
			 * otherwise, an x-tree root overlays this table
			 */
			काष्ठा dir_table_slot _table[12]; /* 96: अंतरभूत */

			dtroot_t _dtroot;		/* 288: dtree root */
		पूर्ण _dir;					/* (384) */
#घोषणा di_dirtable	u._dir._table
#घोषणा di_dtroot	u._dir._dtroot
#घोषणा di_parent	di_dtroot.header.iकरोtकरोt
#घोषणा di_DASD		di_dtroot.header.DASD

		काष्ठा अणु
			जोड़ अणु
				u8 _data[96];		/* 96: unused */
				काष्ठा अणु
					व्योम *_imap;	/* 4: unused */
					__le32 _gengen;	/* 4: generator */
				पूर्ण _imap;
			पूर्ण _u1;				/* 96: */
#घोषणा di_gengen	u._file._u1._imap._gengen

			जोड़ अणु
				xtpage_t _xtroot;
				काष्ठा अणु
					u8 unused[16];	/* 16: */
					dxd_t _dxd;	/* 16: */
					जोड़ अणु
						__le32 _rdev;	/* 4: */
						/*
						 * The fast symlink area
						 * is expected to overflow
						 * पूर्णांकo _अंतरभूतea when
						 * needed (which will clear
						 * INLINEEA).
						 */
						u8 _fastsymlink[128];
					पूर्ण _u;
					u8 _अंतरभूतea[128];
				पूर्ण _special;
			पूर्ण _u2;
		पूर्ण _file;
#घोषणा di_xtroot	u._file._u2._xtroot
#घोषणा di_dxd		u._file._u2._special._dxd
#घोषणा di_btroot	di_xtroot
#घोषणा di_अंतरभूतdata	u._file._u2._special._u
#घोषणा di_rdev		u._file._u2._special._u._rdev
#घोषणा di_fastsymlink	u._file._u2._special._u._fastsymlink
#घोषणा di_अंतरभूतea	u._file._u2._special._अंतरभूतea
	पूर्ण u;
पूर्ण;

/* extended mode bits (on-disk inode di_mode) */
#घोषणा IFJOURNAL	0x00010000	/* journalled file */
#घोषणा ISPARSE		0x00020000	/* sparse file enabled */
#घोषणा INLINEEA	0x00040000	/* अंतरभूत EA area मुक्त */
#घोषणा ISWAPखाता	0x00800000	/* file खोलो क्रम pager swap space */

/* more extended mode bits: attributes क्रम OS/2 */
#घोषणा IREADONLY	0x02000000	/* no ग_लिखो access to file */
#घोषणा IHIDDEN		0x04000000	/* hidden file */
#घोषणा ISYSTEM		0x08000000	/* प्रणाली file */

#घोषणा IसूचीECTORY	0x20000000	/* directory (shaकरोw of real bit) */
#घोषणा IARCHIVE	0x40000000	/* file archive bit */
#घोषणा INEWNAME	0x80000000	/* non-8.3 filename क्रमmat */

#घोषणा IRASH		0x4E000000	/* mask क्रम changeable attributes */
#घोषणा ATTRSHIFT	25	/* bits to shअगरt to move attribute
				   specअगरication to mode position */

/* extended attributes क्रम Linux */

#घोषणा JFS_NOATIME_FL		0x00080000 /* करो not update aसमय */

#घोषणा JFS_सूचीSYNC_FL		0x00100000 /* dirsync behaviour */
#घोषणा JFS_SYNC_FL		0x00200000 /* Synchronous updates */
#घोषणा JFS_SECRM_FL		0x00400000 /* Secure deletion */
#घोषणा JFS_UNRM_FL		0x00800000 /* allow क्रम undelete */

#घोषणा JFS_APPEND_FL		0x01000000 /* ग_लिखोs to file may only append */
#घोषणा JFS_IMMUTABLE_FL	0x02000000 /* Immutable file */

#घोषणा JFS_FL_USER_VISIBLE	0x03F80000
#घोषणा JFS_FL_USER_MODIFIABLE	0x03F80000
#घोषणा JFS_FL_INHERIT		0x03C80000

#पूर्ण_अगर /*_H_JFS_DINODE */

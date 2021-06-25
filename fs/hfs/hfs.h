<शैली गुरु>
/*
 *  linux/fs/hfs/hfs.h
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 */

#अगर_अघोषित _HFS_H
#घोषणा _HFS_H

/* offsets to various blocks */
#घोषणा HFS_DD_BLK		0 /* Driver Descriptor block */
#घोषणा HFS_PMAP_BLK		1 /* First block of partition map */
#घोषणा HFS_MDB_BLK		2 /* Block (w/i partition) of MDB */

/* magic numbers क्रम various disk blocks */
#घोषणा HFS_DRVR_DESC_MAGIC	0x4552 /* "ER": driver descriptor map */
#घोषणा HFS_OLD_PMAP_MAGIC	0x5453 /* "TS": old-type partition map */
#घोषणा HFS_NEW_PMAP_MAGIC	0x504D /* "PM": new-type partition map */
#घोषणा HFS_SUPER_MAGIC		0x4244 /* "BD": HFS MDB (super block) */
#घोषणा HFS_MFS_SUPER_MAGIC	0xD2D7 /* MFS MDB (super block) */

/* various FIXED size parameters */
#घोषणा HFS_SECTOR_SIZE		512    /* size of an HFS sector */
#घोषणा HFS_SECTOR_SIZE_BITS	9      /* log_2(HFS_SECTOR_SIZE) */
#घोषणा HFS_NAMELEN		31     /* maximum length of an HFS filename */
#घोषणा HFS_MAX_NAMELEN		128
#घोषणा HFS_MAX_VALENCE		32767U

/* Meanings of the drAtrb field of the MDB,
 * Reference: _Inside Macपूर्णांकosh: Files_ p. 2-61
 */
#घोषणा HFS_SB_ATTRIB_HLOCK	(1 << 7)
#घोषणा HFS_SB_ATTRIB_UNMNT	(1 << 8)
#घोषणा HFS_SB_ATTRIB_SPARED	(1 << 9)
#घोषणा HFS_SB_ATTRIB_INCNSTNT	(1 << 11)
#घोषणा HFS_SB_ATTRIB_SLOCK	(1 << 15)

/* Some special File ID numbers */
#घोषणा HFS_POR_CNID		1	/* Parent Of the Root */
#घोषणा HFS_ROOT_CNID		2	/* ROOT directory */
#घोषणा HFS_EXT_CNID		3	/* EXTents B-tree */
#घोषणा HFS_CAT_CNID		4	/* CATalog B-tree */
#घोषणा HFS_BAD_CNID		5	/* BAD blocks file */
#घोषणा HFS_ALLOC_CNID		6	/* ALLOCation file (HFS+) */
#घोषणा HFS_START_CNID		7	/* STARTup file (HFS+) */
#घोषणा HFS_ATTR_CNID		8	/* ATTRibutes file (HFS+) */
#घोषणा HFS_EXCH_CNID		15	/* ExchangeFiles temp id */
#घोषणा HFS_FIRSTUSER_CNID	16

/* values क्रम hfs_cat_rec.cdrType */
#घोषणा HFS_CDR_सूची    0x01    /* folder (directory) */
#घोषणा HFS_CDR_FIL    0x02    /* file */
#घोषणा HFS_CDR_THD    0x03    /* folder (directory) thपढ़ो */
#घोषणा HFS_CDR_FTH    0x04    /* file thपढ़ो */

/* legal values क्रम hfs_ext_key.FkType and hfs_file.विभाजन */
#घोषणा HFS_FK_DATA	0x00
#घोषणा HFS_FK_RSRC	0xFF

/* bits in hfs_fil_entry.Flags */
#घोषणा HFS_FIL_LOCK	0x01  /* locked */
#घोषणा HFS_FIL_THD	0x02  /* file thपढ़ो */
#घोषणा HFS_FIL_DOPEN   0x04  /* data विभाजन खोलो */
#घोषणा HFS_FIL_ROPEN   0x08  /* resource विभाजन खोलो */
#घोषणा HFS_FIL_सूची     0x10  /* directory (always clear) */
#घोषणा HFS_FIL_NOCOPY  0x40  /* copy-रक्षित file */
#घोषणा HFS_FIL_USED	0x80  /* खोलो */

/* bits in hfs_dir_entry.Flags. dirflags is 16 bits. */
#घोषणा HFS_सूची_LOCK        0x01  /* locked */
#घोषणा HFS_सूची_THD         0x02  /* directory thपढ़ो */
#घोषणा HFS_सूची_INEXPFOLDER 0x04  /* in a shared area */
#घोषणा HFS_सूची_MOUNTED     0x08  /* mounted */
#घोषणा HFS_सूची_सूची         0x10  /* directory (always set) */
#घोषणा HFS_सूची_EXPFOLDER   0x20  /* share poपूर्णांक */

/* bits hfs_finfo.fdFlags */
#घोषणा HFS_FLG_INITED		0x0100
#घोषणा HFS_FLG_LOCKED		0x1000
#घोषणा HFS_FLG_INVISIBLE	0x4000

/*======== HFS काष्ठाures as they appear on the disk ========*/

/* Pascal-style string of up to 31 अक्षरacters */
काष्ठा hfs_name अणु
	u8 len;
	u8 name[HFS_NAMELEN];
पूर्ण __packed;

काष्ठा hfs_poपूर्णांक अणु
	__be16 v;
	__be16 h;
पूर्ण __packed;

काष्ठा hfs_rect अणु
	__be16 top;
	__be16 left;
	__be16 bottom;
	__be16 right;
पूर्ण __packed;

काष्ठा hfs_finfo अणु
	__be32 fdType;
	__be32 fdCreator;
	__be16 fdFlags;
	काष्ठा hfs_poपूर्णांक fdLocation;
	__be16 fdFldr;
पूर्ण __packed;

काष्ठा hfs_fxinfo अणु
	__be16 fdIconID;
	u8 fdUnused[8];
	__be16 fdComment;
	__be32 fdPutAway;
पूर्ण __packed;

काष्ठा hfs_dinfo अणु
	काष्ठा hfs_rect frRect;
	__be16 frFlags;
	काष्ठा hfs_poपूर्णांक frLocation;
	__be16 frView;
पूर्ण __packed;

काष्ठा hfs_dxinfo अणु
	काष्ठा hfs_poपूर्णांक frScroll;
	__be32 frOpenChain;
	__be16 frUnused;
	__be16 frComment;
	__be32 frPutAway;
पूर्ण __packed;

जोड़ hfs_finder_info अणु
	काष्ठा अणु
		काष्ठा hfs_finfo finfo;
		काष्ठा hfs_fxinfo fxinfo;
	पूर्ण file;
	काष्ठा अणु
		काष्ठा hfs_dinfo dinfo;
		काष्ठा hfs_dxinfo dxinfo;
	पूर्ण dir;
पूर्ण __packed;

/* Cast to a poपूर्णांकer to a generic bkey */
#घोषणा	HFS_BKEY(X)	(((व्योम)((X)->KeyLen)), ((काष्ठा hfs_bkey *)(X)))

/* The key used in the catalog b-tree: */
काष्ठा hfs_cat_key अणु
	u8 key_len;		/* number of bytes in the key */
	u8 reserved;		/* padding */
	__be32 ParID;		/* CNID of the parent dir */
	काष्ठा hfs_name	CName;	/* The filename of the entry */
पूर्ण __packed;

/* The key used in the extents b-tree: */
काष्ठा hfs_ext_key अणु
	u8 key_len;		/* number of bytes in the key */
	u8 FkType;		/* HFS_FK_अणुDATA,RSRCपूर्ण */
	__be32 FNum;		/* The File ID of the file */
	__be16 FABN;		/* allocation blocks number*/
पूर्ण __packed;

प्रकार जोड़ hfs_btree_key अणु
	u8 key_len;			/* number of bytes in the key */
	काष्ठा hfs_cat_key cat;
	काष्ठा hfs_ext_key ext;
पूर्ण hfs_btree_key;

#घोषणा HFS_MAX_CAT_KEYLEN	(माप(काष्ठा hfs_cat_key) - माप(u8))
#घोषणा HFS_MAX_EXT_KEYLEN	(माप(काष्ठा hfs_ext_key) - माप(u8))

प्रकार जोड़ hfs_btree_key btree_key;

काष्ठा hfs_extent अणु
	__be16 block;
	__be16 count;
पूर्ण;
प्रकार काष्ठा hfs_extent hfs_extent_rec[3];

/* The catalog record क्रम a file */
काष्ठा hfs_cat_file अणु
	s8 type;			/* The type of entry */
	u8 reserved;
	u8 Flags;			/* Flags such as पढ़ो-only */
	s8 Typ;				/* file version number = 0 */
	काष्ठा hfs_finfo UsrWds;	/* data used by the Finder */
	__be32 FlNum;			/* The CNID */
	__be16 StBlk;			/* obsolete */
	__be32 LgLen;			/* The logical खातापूर्ण of the data विभाजन*/
	__be32 PyLen;			/* The physical खातापूर्ण of the data विभाजन */
	__be16 RStBlk;			/* obsolete */
	__be32 RLgLen;			/* The logical खातापूर्ण of the rsrc विभाजन */
	__be32 RPyLen;			/* The physical खातापूर्ण of the rsrc विभाजन */
	__be32 CrDat;			/* The creation date */
	__be32 MdDat;			/* The modअगरied date */
	__be32 BkDat;			/* The last backup date */
	काष्ठा hfs_fxinfo FndrInfo;	/* more data क्रम the Finder */
	__be16 ClpSize;			/* number of bytes to allocate
					   when extending files */
	hfs_extent_rec ExtRec;		/* first extent record
					   क्रम the data विभाजन */
	hfs_extent_rec RExtRec;		/* first extent record
					   क्रम the resource विभाजन */
	u32 Resrv;			/* reserved by Apple */
पूर्ण __packed;

/* the catalog record क्रम a directory */
काष्ठा hfs_cat_dir अणु
	s8 type;			/* The type of entry */
	u8 reserved;
	__be16 Flags;			/* flags */
	__be16 Val;			/* Valence: number of files and
					   dirs in the directory */
	__be32 DirID;			/* The CNID */
	__be32 CrDat;			/* The creation date */
	__be32 MdDat;			/* The modअगरication date */
	__be32 BkDat;			/* The last backup date */
	काष्ठा hfs_dinfo UsrInfo;	/* data used by the Finder */
	काष्ठा hfs_dxinfo FndrInfo;	/* more data used by Finder */
	u8 Resrv[16];			/* reserved by Apple */
पूर्ण __packed;

/* the catalog record क्रम a thपढ़ो */
काष्ठा hfs_cat_thपढ़ो अणु
	s8 type;			/* The type of entry */
	u8 reserved[9];			/* reserved by Apple */
	__be32 ParID;			/* CNID of parent directory */
	काष्ठा hfs_name CName;		/* The name of this entry */
पूर्ण  __packed;

/* A catalog tree record */
प्रकार जोड़ hfs_cat_rec अणु
	s8 type;			/* The type of entry */
	काष्ठा hfs_cat_file file;
	काष्ठा hfs_cat_dir dir;
	काष्ठा hfs_cat_thपढ़ो thपढ़ो;
पूर्ण hfs_cat_rec;

काष्ठा hfs_mdb अणु
	__be16 drSigWord;		/* Signature word indicating fs type */
	__be32 drCrDate;		/* fs creation date/समय */
	__be32 drLsMod;			/* fs modअगरication date/समय */
	__be16 drAtrb;			/* fs attributes */
	__be16 drNmFls;			/* number of files in root directory */
	__be16 drVBMSt;			/* location (in 512-byte blocks)
					   of the volume biपंचांगap */
	__be16 drAllocPtr;		/* location (in allocation blocks)
					   to begin next allocation search */
	__be16 drNmAlBlks;		/* number of allocation blocks */
	__be32 drAlBlkSiz;		/* bytes in an allocation block */
	__be32 drClpSiz;		/* clumpsize, the number of bytes to
					   allocate when extending a file */
	__be16 drAlBlSt;		/* location (in 512-byte blocks)
					   of the first allocation block */
	__be32 drNxtCNID;		/* CNID to assign to the next
					   file or directory created */
	__be16 drFreeBks;		/* number of मुक्त allocation blocks */
	u8 drVN[28];			/* the volume label */
	__be32 drVolBkUp;		/* fs backup date/समय */
	__be16 drVSeqNum;		/* backup sequence number */
	__be32 drWrCnt;			/* fs ग_लिखो count */
	__be32 drXTClpSiz;		/* clumpsize क्रम the extents B-tree */
	__be32 drCTClpSiz;		/* clumpsize क्रम the catalog B-tree */
	__be16 drNmRtDirs;		/* number of directories in
					   the root directory */
	__be32 drFilCnt;		/* number of files in the fs */
	__be32 drDirCnt;		/* number of directories in the fs */
	u8 drFndrInfo[32];		/* data used by the Finder */
	__be16 drEmbedSigWord;		/* embedded volume signature */
	__be32 drEmbedExtent;		/* starting block number (xdrStABN)
					   and number of allocation blocks
					   (xdrNumABlks) occupied by embedded
					   volume */
	__be32 drXTFlSize;		/* bytes in the extents B-tree */
	hfs_extent_rec drXTExtRec;	/* extents B-tree's first 3 extents */
	__be32 drCTFlSize;		/* bytes in the catalog B-tree */
	hfs_extent_rec drCTExtRec;	/* catalog B-tree's first 3 extents */
पूर्ण __packed;

/*======== Data काष्ठाures kept in memory ========*/

काष्ठा hfs_सूची_पढ़ो_data अणु
	काष्ठा list_head list;
	काष्ठा file *file;
	काष्ठा hfs_cat_key key;
पूर्ण;

#पूर्ण_अगर

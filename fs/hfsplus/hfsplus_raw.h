<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/hfsplus_raw.h
 *
 * Copyright (C) 1999
 * Brad Boyer (flar@pants.nu)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Format of काष्ठाures on disk
 * Inक्रमmation taken from Apple Technote #1150 (HFS Plus Volume Format)
 *
 */

#अगर_अघोषित _LINUX_HFSPLUS_RAW_H
#घोषणा _LINUX_HFSPLUS_RAW_H

#समावेश <linux/types.h>

/* Some स्थिरants */
#घोषणा HFSPLUS_SECTOR_SIZE        512
#घोषणा HFSPLUS_SECTOR_SHIFT         9
#घोषणा HFSPLUS_VOLHEAD_SECTOR       2
#घोषणा HFSPLUS_VOLHEAD_SIG     0x482b
#घोषणा HFSPLUS_VOLHEAD_SIGX    0x4858
#घोषणा HFSPLUS_SUPER_MAGIC     0x482b
#घोषणा HFSPLUS_MIN_VERSION          4
#घोषणा HFSPLUS_CURRENT_VERSION      5

#घोषणा HFSP_WRAP_MAGIC         0x4244
#घोषणा HFSP_WRAP_ATTRIB_SLOCK  0x8000
#घोषणा HFSP_WRAP_ATTRIB_SPARED 0x0200

#घोषणा HFSP_WRAPOFF_SIG          0x00
#घोषणा HFSP_WRAPOFF_ATTRIB       0x0A
#घोषणा HFSP_WRAPOFF_ABLKSIZE     0x14
#घोषणा HFSP_WRAPOFF_ABLKSTART    0x1C
#घोषणा HFSP_WRAPOFF_EMBEDSIG     0x7C
#घोषणा HFSP_WRAPOFF_EMBEDEXT     0x7E

#घोषणा HFSP_HIDDENसूची_NAME \
	"\xe2\x90\x80\xe2\x90\x80\xe2\x90\x80\xe2\x90\x80HFS+ Private Data"

#घोषणा HFSP_HARDLINK_TYPE	0x686c6e6b	/* 'hlnk' */
#घोषणा HFSP_HFSPLUS_CREATOR	0x6866732b	/* 'hfs+' */

#घोषणा HFSP_SYMLINK_TYPE	0x736c6e6b	/* 'slnk' */
#घोषणा HFSP_SYMLINK_CREATOR	0x72686170	/* 'rhap' */

#घोषणा HFSP_MOUNT_VERSION	0x482b4c78	/* 'H+Lx' */

/* Structures used on disk */

प्रकार __be32 hfsplus_cnid;
प्रकार __be16 hfsplus_unichr;

#घोषणा HFSPLUS_MAX_STRLEN 255
#घोषणा HFSPLUS_ATTR_MAX_STRLEN 127

/* A "string" as used in filenames, etc. */
काष्ठा hfsplus_unistr अणु
	__be16 length;
	hfsplus_unichr unicode[HFSPLUS_MAX_STRLEN];
पूर्ण __packed;

/*
 * A "string" is used in attributes file
 * क्रम name of extended attribute
 */
काष्ठा hfsplus_attr_unistr अणु
	__be16 length;
	hfsplus_unichr unicode[HFSPLUS_ATTR_MAX_STRLEN];
पूर्ण __packed;

/* POSIX permissions */
काष्ठा hfsplus_perm अणु
	__be32 owner;
	__be32 group;
	u8  rootflags;
	u8  userflags;
	__be16 mode;
	__be32 dev;
पूर्ण __packed;

#घोषणा HFSPLUS_FLG_NODUMP	0x01
#घोषणा HFSPLUS_FLG_IMMUTABLE	0x02
#घोषणा HFSPLUS_FLG_APPEND	0x04

/* A single contiguous area of a file */
काष्ठा hfsplus_extent अणु
	__be32 start_block;
	__be32 block_count;
पूर्ण __packed;
प्रकार काष्ठा hfsplus_extent hfsplus_extent_rec[8];

/* Inक्रमmation क्रम a "Fork" in a file */
काष्ठा hfsplus_विभाजन_raw अणु
	__be64 total_size;
	__be32 clump_size;
	__be32 total_blocks;
	hfsplus_extent_rec extents;
पूर्ण __packed;

/* HFS+ Volume Header */
काष्ठा hfsplus_vh अणु
	__be16 signature;
	__be16 version;
	__be32 attributes;
	__be32 last_mount_vers;
	u32 reserved;

	__be32 create_date;
	__be32 modअगरy_date;
	__be32 backup_date;
	__be32 checked_date;

	__be32 file_count;
	__be32 folder_count;

	__be32 blocksize;
	__be32 total_blocks;
	__be32 मुक्त_blocks;

	__be32 next_alloc;
	__be32 rsrc_clump_sz;
	__be32 data_clump_sz;
	hfsplus_cnid next_cnid;

	__be32 ग_लिखो_count;
	__be64 encodings_bmp;

	u32 finder_info[8];

	काष्ठा hfsplus_विभाजन_raw alloc_file;
	काष्ठा hfsplus_विभाजन_raw ext_file;
	काष्ठा hfsplus_विभाजन_raw cat_file;
	काष्ठा hfsplus_विभाजन_raw attr_file;
	काष्ठा hfsplus_विभाजन_raw start_file;
पूर्ण __packed;

/* HFS+ volume attributes */
#घोषणा HFSPLUS_VOL_UNMNT		(1 << 8)
#घोषणा HFSPLUS_VOL_SPARE_BLK		(1 << 9)
#घोषणा HFSPLUS_VOL_NOCACHE		(1 << 10)
#घोषणा HFSPLUS_VOL_INCNSTNT		(1 << 11)
#घोषणा HFSPLUS_VOL_NODEID_REUSED	(1 << 12)
#घोषणा HFSPLUS_VOL_JOURNALED		(1 << 13)
#घोषणा HFSPLUS_VOL_SOFTLOCK		(1 << 15)
#घोषणा HFSPLUS_VOL_UNUSED_NODE_FIX	(1 << 31)

/* HFS+ BTree node descriptor */
काष्ठा hfs_bnode_desc अणु
	__be32 next;
	__be32 prev;
	s8 type;
	u8 height;
	__be16 num_recs;
	u16 reserved;
पूर्ण __packed;

/* HFS+ BTree node types */
#घोषणा HFS_NODE_INDEX	0x00	/* An पूर्णांकernal (index) node */
#घोषणा HFS_NODE_HEADER	0x01	/* The tree header node (node 0) */
#घोषणा HFS_NODE_MAP	0x02	/* Holds part of the biपंचांगap of used nodes */
#घोषणा HFS_NODE_LEAF	0xFF	/* A leaf (ndNHeight==1) node */

/* HFS+ BTree header */
काष्ठा hfs_btree_header_rec अणु
	__be16 depth;
	__be32 root;
	__be32 leaf_count;
	__be32 leaf_head;
	__be32 leaf_tail;
	__be16 node_size;
	__be16 max_key_len;
	__be32 node_count;
	__be32 मुक्त_nodes;
	u16 reserved1;
	__be32 clump_size;
	u8 btree_type;
	u8 key_type;
	__be32 attributes;
	u32 reserved3[16];
पूर्ण __packed;

/* BTree attributes */
#घोषणा HFS_TREE_BIGKEYS	2
#घोषणा HFS_TREE_VARIDXKEYS	4

/* HFS+ BTree misc info */
#घोषणा HFSPLUS_TREE_HEAD 0
#घोषणा HFSPLUS_NODE_MXSZ 32768
#घोषणा HFSPLUS_ATTR_TREE_NODE_SIZE		8192
#घोषणा HFSPLUS_BTREE_HDR_NODE_RECS_COUNT	3
#घोषणा HFSPLUS_BTREE_HDR_USER_BYTES		128

/* Some special File ID numbers (stolen from hfs.h) */
#घोषणा HFSPLUS_POR_CNID		1	/* Parent Of the Root */
#घोषणा HFSPLUS_ROOT_CNID		2	/* ROOT directory */
#घोषणा HFSPLUS_EXT_CNID		3	/* EXTents B-tree */
#घोषणा HFSPLUS_CAT_CNID		4	/* CATalog B-tree */
#घोषणा HFSPLUS_BAD_CNID		5	/* BAD blocks file */
#घोषणा HFSPLUS_ALLOC_CNID		6	/* ALLOCation file */
#घोषणा HFSPLUS_START_CNID		7	/* STARTup file */
#घोषणा HFSPLUS_ATTR_CNID		8	/* ATTRibutes file */
#घोषणा HFSPLUS_EXCH_CNID		15	/* ExchangeFiles temp id */
#घोषणा HFSPLUS_FIRSTUSER_CNID		16	/* first available user id */

/* btree key type */
#घोषणा HFSPLUS_KEY_CASEFOLDING		0xCF	/* हाल-insensitive */
#घोषणा HFSPLUS_KEY_BINARY		0xBC	/* हाल-sensitive */

/* HFS+ catalog entry key */
काष्ठा hfsplus_cat_key अणु
	__be16 key_len;
	hfsplus_cnid parent;
	काष्ठा hfsplus_unistr name;
पूर्ण __packed;

#घोषणा HFSPLUS_CAT_KEYLEN	(माप(काष्ठा hfsplus_cat_key))

/* Structs from hfs.h */
काष्ठा hfsp_poपूर्णांक अणु
	__be16 v;
	__be16 h;
पूर्ण __packed;

काष्ठा hfsp_rect अणु
	__be16 top;
	__be16 left;
	__be16 bottom;
	__be16 right;
पूर्ण __packed;


/* HFS directory info (stolen from hfs.h */
काष्ठा DInfo अणु
	काष्ठा hfsp_rect frRect;
	__be16 frFlags;
	काष्ठा hfsp_poपूर्णांक frLocation;
	__be16 frView;
पूर्ण __packed;

काष्ठा DXInfo अणु
	काष्ठा hfsp_poपूर्णांक frScroll;
	__be32 frOpenChain;
	__be16 frUnused;
	__be16 frComment;
	__be32 frPutAway;
पूर्ण __packed;

/* HFS+ folder data (part of an hfsplus_cat_entry) */
काष्ठा hfsplus_cat_folder अणु
	__be16 type;
	__be16 flags;
	__be32 valence;
	hfsplus_cnid id;
	__be32 create_date;
	__be32 content_mod_date;
	__be32 attribute_mod_date;
	__be32 access_date;
	__be32 backup_date;
	काष्ठा hfsplus_perm permissions;
	काष्ठा DInfo user_info;
	काष्ठा DXInfo finder_info;
	__be32 text_encoding;
	__be32 subfolders;	/* Subfolder count in HFSX. Reserved in HFS+. */
पूर्ण __packed;

/* HFS file info (stolen from hfs.h) */
काष्ठा FInfo अणु
	__be32 fdType;
	__be32 fdCreator;
	__be16 fdFlags;
	काष्ठा hfsp_poपूर्णांक fdLocation;
	__be16 fdFldr;
पूर्ण __packed;

काष्ठा FXInfo अणु
	__be16 fdIconID;
	u8 fdUnused[8];
	__be16 fdComment;
	__be32 fdPutAway;
पूर्ण __packed;

/* HFS+ file data (part of a cat_entry) */
काष्ठा hfsplus_cat_file अणु
	__be16 type;
	__be16 flags;
	u32 reserved1;
	hfsplus_cnid id;
	__be32 create_date;
	__be32 content_mod_date;
	__be32 attribute_mod_date;
	__be32 access_date;
	__be32 backup_date;
	काष्ठा hfsplus_perm permissions;
	काष्ठा FInfo user_info;
	काष्ठा FXInfo finder_info;
	__be32 text_encoding;
	u32 reserved2;

	काष्ठा hfsplus_विभाजन_raw data_विभाजन;
	काष्ठा hfsplus_विभाजन_raw rsrc_विभाजन;
पूर्ण __packed;

/* File and folder flag bits */
#घोषणा HFSPLUS_खाता_LOCKED		0x0001
#घोषणा HFSPLUS_खाता_THREAD_EXISTS	0x0002
#घोषणा HFSPLUS_XATTR_EXISTS		0x0004
#घोषणा HFSPLUS_ACL_EXISTS		0x0008
#घोषणा HFSPLUS_HAS_FOLDER_COUNT	0x0010	/* Folder has subfolder count
						 * (HFSX only) */

/* HFS+ catalog thपढ़ो (part of a cat_entry) */
काष्ठा hfsplus_cat_thपढ़ो अणु
	__be16 type;
	s16 reserved;
	hfsplus_cnid parentID;
	काष्ठा hfsplus_unistr nodeName;
पूर्ण __packed;

#घोषणा HFSPLUS_MIN_THREAD_SZ 10

/* A data record in the catalog tree */
प्रकार जोड़ अणु
	__be16 type;
	काष्ठा hfsplus_cat_folder folder;
	काष्ठा hfsplus_cat_file file;
	काष्ठा hfsplus_cat_thपढ़ो thपढ़ो;
पूर्ण __packed hfsplus_cat_entry;

/* HFS+ catalog entry type */
#घोषणा HFSPLUS_FOLDER         0x0001
#घोषणा HFSPLUS_खाता           0x0002
#घोषणा HFSPLUS_FOLDER_THREAD  0x0003
#घोषणा HFSPLUS_खाता_THREAD    0x0004

/* HFS+ extents tree key */
काष्ठा hfsplus_ext_key अणु
	__be16 key_len;
	u8 विभाजन_type;
	u8 pad;
	hfsplus_cnid cnid;
	__be32 start_block;
पूर्ण __packed;

#घोषणा HFSPLUS_EXT_KEYLEN	माप(काष्ठा hfsplus_ext_key)

#घोषणा HFSPLUS_XATTR_FINDER_INFO_NAME "com.apple.FinderInfo"
#घोषणा HFSPLUS_XATTR_ACL_NAME "com.apple.system.Security"

#घोषणा HFSPLUS_ATTR_INLINE_DATA 0x10
#घोषणा HFSPLUS_ATTR_FORK_DATA   0x20
#घोषणा HFSPLUS_ATTR_EXTENTS     0x30

/* HFS+ attributes tree key */
काष्ठा hfsplus_attr_key अणु
	__be16 key_len;
	__be16 pad;
	hfsplus_cnid cnid;
	__be32 start_block;
	काष्ठा hfsplus_attr_unistr key_name;
पूर्ण __packed;

#घोषणा HFSPLUS_ATTR_KEYLEN	माप(काष्ठा hfsplus_attr_key)

/* HFS+ विभाजन data attribute */
काष्ठा hfsplus_attr_विभाजन_data अणु
	__be32 record_type;
	__be32 reserved;
	काष्ठा hfsplus_विभाजन_raw the_विभाजन;
पूर्ण __packed;

/* HFS+ extension attribute */
काष्ठा hfsplus_attr_extents अणु
	__be32 record_type;
	__be32 reserved;
	काष्ठा hfsplus_extent extents;
पूर्ण __packed;

#घोषणा HFSPLUS_MAX_INLINE_DATA_SIZE 3802

/* HFS+ attribute अंतरभूत data */
काष्ठा hfsplus_attr_अंतरभूत_data अणु
	__be32 record_type;
	__be32 reserved1;
	u8 reserved2[6];
	__be16 length;
	u8 raw_bytes[HFSPLUS_MAX_INLINE_DATA_SIZE];
पूर्ण __packed;

/* A data record in the attributes tree */
प्रकार जोड़ अणु
	__be32 record_type;
	काष्ठा hfsplus_attr_विभाजन_data विभाजन_data;
	काष्ठा hfsplus_attr_extents extents;
	काष्ठा hfsplus_attr_अंतरभूत_data अंतरभूत_data;
पूर्ण __packed hfsplus_attr_entry;

/* HFS+ generic BTree key */
प्रकार जोड़ अणु
	__be16 key_len;
	काष्ठा hfsplus_cat_key cat;
	काष्ठा hfsplus_ext_key ext;
	काष्ठा hfsplus_attr_key attr;
पूर्ण __packed hfsplus_btree_key;

#पूर्ण_अगर

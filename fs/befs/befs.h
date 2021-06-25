<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * befs.h
 *
 * Copyright (C) 2001-2002 Will Dyson <will_dyson@pobox.com>
 * Copyright (C) 1999 Makoto Kato (m_kato@ga2.so-net.ne.jp)
 */

#अगर_अघोषित _LINUX_BEFS_H
#घोषणा _LINUX_BEFS_H

#समावेश "befs_fs_types.h"

/* used in debug.c */
#घोषणा BEFS_VERSION "0.9.3"


प्रकार u64 befs_blocknr_t;
/*
 * BeFS in memory काष्ठाures
 */

काष्ठा befs_mount_options अणु
	kgid_t gid;
	kuid_t uid;
	पूर्णांक use_gid;
	पूर्णांक use_uid;
	पूर्णांक debug;
	अक्षर *ioअक्षरset;
पूर्ण;

काष्ठा befs_sb_info अणु
	u32 magic1;
	u32 block_size;
	u32 block_shअगरt;
	पूर्णांक byte_order;
	befs_off_t num_blocks;
	befs_off_t used_blocks;
	u32 inode_size;
	u32 magic2;

	/* Allocation group inक्रमmation */
	u32 blocks_per_ag;
	u32 ag_shअगरt;
	u32 num_ags;

	/* State of the superblock */
	u32 flags;

	/* Journal log entry */
	befs_block_run log_blocks;
	befs_off_t log_start;
	befs_off_t log_end;

	befs_inode_addr root_dir;
	befs_inode_addr indices;
	u32 magic3;

	काष्ठा befs_mount_options mount_opts;
	काष्ठा nls_table *nls;
पूर्ण;

काष्ठा befs_inode_info अणु
	u32 i_flags;
	u32 i_type;

	befs_inode_addr i_inode_num;
	befs_inode_addr i_parent;
	befs_inode_addr i_attribute;

	जोड़ अणु
		befs_data_stream ds;
		अक्षर symlink[BEFS_SYMLINK_LEN];
	पूर्ण i_data;

	काष्ठा inode vfs_inode;
पूर्ण;

क्रमागत befs_err अणु
	BEFS_OK,
	BEFS_ERR,
	BEFS_BAD_INODE,
	BEFS_BT_END,
	BEFS_BT_EMPTY,
	BEFS_BT_MATCH,
	BEFS_BT_OVERFLOW,
	BEFS_BT_NOT_FOUND
पूर्ण;


/****************************/
/* debug.c */
__म_लिखो(2, 3)
व्योम befs_error(स्थिर काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम befs_warning(स्थिर काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम befs_debug(स्थिर काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...);

व्योम befs_dump_super_block(स्थिर काष्ठा super_block *sb, befs_super_block *);
व्योम befs_dump_inode(स्थिर काष्ठा super_block *sb, befs_inode *);
व्योम befs_dump_index_entry(स्थिर काष्ठा super_block *sb, befs_disk_btree_super *);
व्योम befs_dump_index_node(स्थिर काष्ठा super_block *sb, befs_btree_nodehead *);
/****************************/


/* Gets a poपूर्णांकer to the निजी portion of the super_block
 * काष्ठाure from the खुला part
 */
अटल अंतरभूत काष्ठा befs_sb_info *
BEFS_SB(स्थिर काष्ठा super_block *super)
अणु
	वापस (काष्ठा befs_sb_info *) super->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा befs_inode_info *
BEFS_I(स्थिर काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा befs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत befs_blocknr_t
iaddr2blockno(काष्ठा super_block *sb, स्थिर befs_inode_addr *iaddr)
अणु
	वापस ((iaddr->allocation_group << BEFS_SB(sb)->ag_shअगरt) +
		iaddr->start);
पूर्ण

अटल अंतरभूत befs_inode_addr
blockno2iaddr(काष्ठा super_block *sb, befs_blocknr_t blockno)
अणु
	befs_inode_addr iaddr;

	iaddr.allocation_group = blockno >> BEFS_SB(sb)->ag_shअगरt;
	iaddr.start =
	    blockno - (iaddr.allocation_group << BEFS_SB(sb)->ag_shअगरt);
	iaddr.len = 1;

	वापस iaddr;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
befs_iaddrs_per_block(काष्ठा super_block *sb)
अणु
	वापस BEFS_SB(sb)->block_size / माप(befs_disk_inode_addr);
पूर्ण

#समावेश "endian.h"

#पूर्ण_अगर				/* _LINUX_BEFS_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _OMFS_H
#घोषणा _OMFS_H

#समावेश <linux/module.h>
#समावेश <linux/fs.h>

#समावेश "omfs_fs.h"

/* In-memory काष्ठाures */
काष्ठा omfs_sb_info अणु
	u64 s_num_blocks;
	u64 s_biपंचांगap_ino;
	u64 s_root_ino;
	u32 s_blocksize;
	u32 s_mirrors;
	u32 s_sys_blocksize;
	u32 s_clustersize;
	पूर्णांक s_block_shअगरt;
	अचिन्हित दीर्घ **s_imap;
	पूर्णांक s_imap_size;
	काष्ठा mutex s_biपंचांगap_lock;
	kuid_t s_uid;
	kgid_t s_gid;
	पूर्णांक s_dmask;
	पूर्णांक s_fmask;
पूर्ण;

/* convert a cluster number to a scaled block number */
अटल अंतरभूत sector_t clus_to_blk(काष्ठा omfs_sb_info *sbi, sector_t block)
अणु
	वापस block << sbi->s_block_shअगरt;
पूर्ण

अटल अंतरभूत काष्ठा omfs_sb_info *OMFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/* biपंचांगap.c */
बाह्य अचिन्हित दीर्घ omfs_count_मुक्त(काष्ठा super_block *sb);
बाह्य पूर्णांक omfs_allocate_block(काष्ठा super_block *sb, u64 block);
बाह्य पूर्णांक omfs_allocate_range(काष्ठा super_block *sb, पूर्णांक min_request,
			पूर्णांक max_request, u64 *वापस_block, पूर्णांक *वापस_size);
बाह्य पूर्णांक omfs_clear_range(काष्ठा super_block *sb, u64 block, पूर्णांक count);

/* dir.c */
बाह्य स्थिर काष्ठा file_operations omfs_dir_operations;
बाह्य स्थिर काष्ठा inode_operations omfs_dir_inops;
बाह्य पूर्णांक omfs_make_empty(काष्ठा inode *inode, काष्ठा super_block *sb);
बाह्य पूर्णांक omfs_is_bad(काष्ठा omfs_sb_info *sbi, काष्ठा omfs_header *header,
			u64 fsblock);

/* file.c */
बाह्य स्थिर काष्ठा file_operations omfs_file_operations;
बाह्य स्थिर काष्ठा inode_operations omfs_file_inops;
बाह्य स्थिर काष्ठा address_space_operations omfs_aops;
बाह्य व्योम omfs_make_empty_table(काष्ठा buffer_head *bh, पूर्णांक offset);
बाह्य पूर्णांक omfs_shrink_inode(काष्ठा inode *inode);

/* inode.c */
बाह्य काष्ठा buffer_head *omfs_bपढ़ो(काष्ठा super_block *sb, sector_t block);
बाह्य काष्ठा inode *omfs_iget(काष्ठा super_block *sb, ino_t inode);
बाह्य काष्ठा inode *omfs_new_inode(काष्ठा inode *dir, umode_t mode);
बाह्य पूर्णांक omfs_reserve_block(काष्ठा super_block *sb, sector_t block);
बाह्य पूर्णांक omfs_find_empty_block(काष्ठा super_block *sb, पूर्णांक mode, ino_t *ino);
बाह्य पूर्णांक omfs_sync_inode(काष्ठा inode *inode);

#पूर्ण_अगर

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित FS_MINIX_H
#घोषणा FS_MINIX_H

#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/minix_fs.h>

#घोषणा INODE_VERSION(inode)	minix_sb(inode->i_sb)->s_version
#घोषणा MINIX_V1		0x0001		/* original minix fs */
#घोषणा MINIX_V2		0x0002		/* minix V2 fs */
#घोषणा MINIX_V3		0x0003		/* minix V3 fs */

/*
 * minix fs inode data in memory
 */
काष्ठा minix_inode_info अणु
	जोड़ अणु
		__u16 i1_data[16];
		__u32 i2_data[16];
	पूर्ण u;
	काष्ठा inode vfs_inode;
पूर्ण;

/*
 * minix super-block data in memory
 */
काष्ठा minix_sb_info अणु
	अचिन्हित दीर्घ s_ninodes;
	अचिन्हित दीर्घ s_nzones;
	अचिन्हित दीर्घ s_imap_blocks;
	अचिन्हित दीर्घ s_zmap_blocks;
	अचिन्हित दीर्घ s_firstdatazone;
	अचिन्हित दीर्घ s_log_zone_size;
	पूर्णांक s_dirsize;
	पूर्णांक s_namelen;
	काष्ठा buffer_head ** s_imap;
	काष्ठा buffer_head ** s_zmap;
	काष्ठा buffer_head * s_sbh;
	काष्ठा minix_super_block * s_ms;
	अचिन्हित लघु s_mount_state;
	अचिन्हित लघु s_version;
पूर्ण;

बाह्य काष्ठा inode *minix_iget(काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य काष्ठा minix_inode * minix_V1_raw_inode(काष्ठा super_block *, ino_t, काष्ठा buffer_head **);
बाह्य काष्ठा minix2_inode * minix_V2_raw_inode(काष्ठा super_block *, ino_t, काष्ठा buffer_head **);
बाह्य काष्ठा inode * minix_new_inode(स्थिर काष्ठा inode *, umode_t, पूर्णांक *);
बाह्य व्योम minix_मुक्त_inode(काष्ठा inode * inode);
बाह्य अचिन्हित दीर्घ minix_count_मुक्त_inodes(काष्ठा super_block *sb);
बाह्य पूर्णांक minix_new_block(काष्ठा inode * inode);
बाह्य व्योम minix_मुक्त_block(काष्ठा inode *inode, अचिन्हित दीर्घ block);
बाह्य अचिन्हित दीर्घ minix_count_मुक्त_blocks(काष्ठा super_block *sb);
बाह्य पूर्णांक minix_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *,
			 काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य पूर्णांक minix_prepare_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len);

बाह्य व्योम V1_minix_truncate(काष्ठा inode *);
बाह्य व्योम V2_minix_truncate(काष्ठा inode *);
बाह्य व्योम minix_truncate(काष्ठा inode *);
बाह्य व्योम minix_set_inode(काष्ठा inode *, dev_t);
बाह्य पूर्णांक V1_minix_get_block(काष्ठा inode *, दीर्घ, काष्ठा buffer_head *, पूर्णांक);
बाह्य पूर्णांक V2_minix_get_block(काष्ठा inode *, दीर्घ, काष्ठा buffer_head *, पूर्णांक);
बाह्य अचिन्हित V1_minix_blocks(loff_t, काष्ठा super_block *);
बाह्य अचिन्हित V2_minix_blocks(loff_t, काष्ठा super_block *);

बाह्य काष्ठा minix_dir_entry *minix_find_entry(काष्ठा dentry*, काष्ठा page**);
बाह्य पूर्णांक minix_add_link(काष्ठा dentry*, काष्ठा inode*);
बाह्य पूर्णांक minix_delete_entry(काष्ठा minix_dir_entry*, काष्ठा page*);
बाह्य पूर्णांक minix_make_empty(काष्ठा inode*, काष्ठा inode*);
बाह्य पूर्णांक minix_empty_dir(काष्ठा inode*);
बाह्य व्योम minix_set_link(काष्ठा minix_dir_entry*, काष्ठा page*, काष्ठा inode*);
बाह्य काष्ठा minix_dir_entry *minix_करोtकरोt(काष्ठा inode*, काष्ठा page**);
बाह्य ino_t minix_inode_by_name(काष्ठा dentry*);

बाह्य स्थिर काष्ठा inode_operations minix_file_inode_operations;
बाह्य स्थिर काष्ठा inode_operations minix_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations minix_file_operations;
बाह्य स्थिर काष्ठा file_operations minix_dir_operations;

अटल अंतरभूत काष्ठा minix_sb_info *minix_sb(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा minix_inode_info *minix_i(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा minix_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत अचिन्हित minix_blocks_needed(अचिन्हित bits, अचिन्हित blocksize)
अणु
	वापस DIV_ROUND_UP(bits, blocksize * 8);
पूर्ण

#अगर defined(CONFIG_MINIX_FS_NATIVE_ENDIAN) && \
	defined(CONFIG_MINIX_FS_BIG_ENDIAN_16BIT_INDEXED)

#त्रुटि Minix file प्रणाली byte order broken

#या_अगर defined(CONFIG_MINIX_FS_NATIVE_ENDIAN)

/*
 * big-endian 32 or 64 bit indexed biपंचांगaps on big-endian प्रणाली or
 * little-endian biपंचांगaps on little-endian प्रणाली
 */

#घोषणा minix_test_and_set_bit(nr, addr)	\
	__test_and_set_bit((nr), (अचिन्हित दीर्घ *)(addr))
#घोषणा minix_set_bit(nr, addr)		\
	__set_bit((nr), (अचिन्हित दीर्घ *)(addr))
#घोषणा minix_test_and_clear_bit(nr, addr) \
	__test_and_clear_bit((nr), (अचिन्हित दीर्घ *)(addr))
#घोषणा minix_test_bit(nr, addr)		\
	test_bit((nr), (अचिन्हित दीर्घ *)(addr))
#घोषणा minix_find_first_zero_bit(addr, size) \
	find_first_zero_bit((अचिन्हित दीर्घ *)(addr), (size))

#या_अगर defined(CONFIG_MINIX_FS_BIG_ENDIAN_16BIT_INDEXED)

/*
 * big-endian 16bit indexed biपंचांगaps
 */

अटल अंतरभूत पूर्णांक minix_find_first_zero_bit(स्थिर व्योम *vaddr, अचिन्हित size)
अणु
	स्थिर अचिन्हित लघु *p = vaddr, *addr = vaddr;
	अचिन्हित लघु num;

	अगर (!size)
		वापस 0;

	size >>= 4;
	जबतक (*p++ == 0xffff) अणु
		अगर (--size == 0)
			वापस (p - addr) << 4;
	पूर्ण

	num = *--p;
	वापस ((p - addr) << 4) + ffz(num);
पूर्ण

#घोषणा minix_test_and_set_bit(nr, addr)	\
	__test_and_set_bit((nr) ^ 16, (अचिन्हित दीर्घ *)(addr))
#घोषणा minix_set_bit(nr, addr)	\
	__set_bit((nr) ^ 16, (अचिन्हित दीर्घ *)(addr))
#घोषणा minix_test_and_clear_bit(nr, addr)	\
	__test_and_clear_bit((nr) ^ 16, (अचिन्हित दीर्घ *)(addr))

अटल अंतरभूत पूर्णांक minix_test_bit(पूर्णांक nr, स्थिर व्योम *vaddr)
अणु
	स्थिर अचिन्हित लघु *p = vaddr;
	वापस (p[nr >> 4] & (1U << (nr & 15))) != 0;
पूर्ण

#अन्यथा

/*
 * little-endian biपंचांगaps
 */

#घोषणा minix_test_and_set_bit	__test_and_set_bit_le
#घोषणा minix_set_bit		__set_bit_le
#घोषणा minix_test_and_clear_bit	__test_and_clear_bit_le
#घोषणा minix_test_bit	test_bit_le
#घोषणा minix_find_first_zero_bit	find_first_zero_bit_le

#पूर्ण_अगर

#पूर्ण_अगर /* FS_MINIX_H */

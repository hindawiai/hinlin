<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/fs.h>
#समावेश <linux/qnx4_fs.h>

#घोषणा QNX4_DEBUG 0

#अगर QNX4_DEBUG
#घोषणा QNX4DEBUG(X) prपूर्णांकk X
#अन्यथा
#घोषणा QNX4DEBUG(X) (व्योम) 0
#पूर्ण_अगर

काष्ठा qnx4_sb_info अणु
	अचिन्हित पूर्णांक		Version;	/* may be useful */
	काष्ठा qnx4_inode_entry	*BitMap;	/* useful */
पूर्ण;

काष्ठा qnx4_inode_info अणु
	काष्ठा qnx4_inode_entry raw;
	loff_t mmu_निजी;
	काष्ठा inode vfs_inode;
पूर्ण;

बाह्य काष्ठा inode *qnx4_iget(काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य काष्ठा dentry *qnx4_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags);
बाह्य अचिन्हित दीर्घ qnx4_count_मुक्त_blocks(काष्ठा super_block *sb);
बाह्य अचिन्हित दीर्घ qnx4_block_map(काष्ठा inode *inode, दीर्घ iblock);

बाह्य स्थिर काष्ठा inode_operations qnx4_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations qnx4_dir_operations;
बाह्य पूर्णांक qnx4_is_मुक्त(काष्ठा super_block *sb, दीर्घ block);

अटल अंतरभूत काष्ठा qnx4_sb_info *qnx4_sb(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा qnx4_inode_info *qnx4_i(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा qnx4_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा qnx4_inode_entry *qnx4_raw_inode(काष्ठा inode *inode)
अणु
	वापस &qnx4_i(inode)->raw;
पूर्ण

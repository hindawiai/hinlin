<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XFS_PNFS_H
#घोषणा _XFS_PNFS_H 1

#अगर_घोषित CONFIG_EXPORTFS_BLOCK_OPS
पूर्णांक xfs_fs_get_uuid(काष्ठा super_block *sb, u8 *buf, u32 *len, u64 *offset);
पूर्णांक xfs_fs_map_blocks(काष्ठा inode *inode, loff_t offset, u64 length,
		काष्ठा iomap *iomap, bool ग_लिखो, u32 *device_generation);
पूर्णांक xfs_fs_commit_blocks(काष्ठा inode *inode, काष्ठा iomap *maps, पूर्णांक nr_maps,
		काष्ठा iattr *iattr);

पूर्णांक xfs_अवरोध_leased_layouts(काष्ठा inode *inode, uपूर्णांक *iolock,
		bool *did_unlock);
#अन्यथा
अटल अंतरभूत पूर्णांक
xfs_अवरोध_leased_layouts(काष्ठा inode *inode, uपूर्णांक *iolock, bool *did_unlock)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_EXPORTFS_BLOCK_OPS */
#पूर्ण_अगर /* _XFS_PNFS_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _UDF_I_H
#घोषणा _UDF_I_H

काष्ठा extent_position अणु
	काष्ठा buffer_head *bh;
	uपूर्णांक32_t offset;
	काष्ठा kernel_lb_addr block;
पूर्ण;

काष्ठा udf_ext_cache अणु
	/* Extent position */
	काष्ठा extent_position epos;
	/* Start logical offset in bytes */
	loff_t lstart;
पूर्ण;

/*
 * The i_data_sem and i_mutex serve क्रम protection of allocation inक्रमmation
 * of a regular files and symlinks. This includes all extents beदीर्घing to
 * the file/symlink, a fact whether data are in-inode or in बाह्यal data
 * blocks, pपुनः_स्मृतिation, goal block inक्रमmation... When extents are पढ़ो,
 * i_mutex or i_data_sem must be held (क्रम पढ़ोing is enough in हाल of
 * i_data_sem). When extents are changed, i_data_sem must be held क्रम writing
 * and also i_mutex must be held.
 *
 * For directories i_mutex is used क्रम all the necessary protection.
 */

काष्ठा udf_inode_info अणु
	काष्ठा बारpec64	i_crसमय;
	/* Physical address of inode */
	काष्ठा kernel_lb_addr		i_location;
	__u64			i_unique;
	__u32			i_lenEAttr;
	__u32			i_lenAlloc;
	__u64			i_lenExtents;
	__u32			i_next_alloc_block;
	__u32			i_next_alloc_goal;
	__u32			i_checkpoपूर्णांक;
	__u32			i_extraPerms;
	अचिन्हित		i_alloc_type : 3;
	अचिन्हित		i_efe : 1;	/* extendedFileEntry */
	अचिन्हित		i_use : 1;	/* unallocSpaceEntry */
	अचिन्हित		i_strat4096 : 1;
	अचिन्हित		i_streamdir : 1;
	अचिन्हित		reserved : 25;
	__u8			*i_data;
	काष्ठा kernel_lb_addr	i_locStreamdir;
	__u64			i_lenStreams;
	काष्ठा rw_semaphore	i_data_sem;
	काष्ठा udf_ext_cache cached_extent;
	/* Spinlock क्रम protecting extent cache */
	spinlock_t i_extent_cache_lock;
	काष्ठा inode vfs_inode;
पूर्ण;

अटल अंतरभूत काष्ठा udf_inode_info *UDF_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा udf_inode_info, vfs_inode);
पूर्ण

#पूर्ण_अगर /* _UDF_I_H) */

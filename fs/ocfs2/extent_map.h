<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * extent_map.h
 *
 * In-memory file extent mappings क्रम OCFS2.
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित _EXTENT_MAP_H
#घोषणा _EXTENT_MAP_H

काष्ठा ocfs2_extent_map_item अणु
	अचिन्हित पूर्णांक			ei_cpos;
	अचिन्हित पूर्णांक			ei_phys;
	अचिन्हित पूर्णांक			ei_clusters;
	अचिन्हित पूर्णांक			ei_flags;

	काष्ठा list_head		ei_list;
पूर्ण;

#घोषणा OCFS2_MAX_EXTENT_MAP_ITEMS			3
काष्ठा ocfs2_extent_map अणु
	अचिन्हित पूर्णांक			em_num_items;
	काष्ठा list_head		em_list;
पूर्ण;

व्योम ocfs2_extent_map_init(काष्ठा inode *inode);
व्योम ocfs2_extent_map_trunc(काष्ठा inode *inode, अचिन्हित पूर्णांक cluster);
व्योम ocfs2_extent_map_insert_rec(काष्ठा inode *inode,
				 काष्ठा ocfs2_extent_rec *rec);

पूर्णांक ocfs2_get_clusters(काष्ठा inode *inode, u32 v_cluster, u32 *p_cluster,
		       u32 *num_clusters, अचिन्हित पूर्णांक *extent_flags);
पूर्णांक ocfs2_extent_map_get_blocks(काष्ठा inode *inode, u64 v_blkno, u64 *p_blkno,
				u64 *ret_count, अचिन्हित पूर्णांक *extent_flags);

पूर्णांक ocfs2_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		 u64 map_start, u64 map_len);

पूर्णांक ocfs2_overग_लिखो_io(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
		       u64 map_start, u64 map_len);

पूर्णांक ocfs2_seek_data_hole_offset(काष्ठा file *file, loff_t *offset, पूर्णांक origin);

पूर्णांक ocfs2_xattr_get_clusters(काष्ठा inode *inode, u32 v_cluster,
			     u32 *p_cluster, u32 *num_clusters,
			     काष्ठा ocfs2_extent_list *el,
			     अचिन्हित पूर्णांक *extent_flags);

पूर्णांक ocfs2_पढ़ो_virt_blocks(काष्ठा inode *inode, u64 v_block, पूर्णांक nr,
			   काष्ठा buffer_head *bhs[], पूर्णांक flags,
			   पूर्णांक (*validate)(काष्ठा super_block *sb,
					   काष्ठा buffer_head *bh));
पूर्णांक ocfs2_figure_hole_clusters(काष्ठा ocfs2_caching_info *ci,
			       काष्ठा ocfs2_extent_list *el,
			       काष्ठा buffer_head *eb_bh,
			       u32 v_cluster,
			       u32 *num_clusters);
अटल अंतरभूत पूर्णांक ocfs2_पढ़ो_virt_block(काष्ठा inode *inode, u64 v_block,
					काष्ठा buffer_head **bh,
					पूर्णांक (*validate)(काष्ठा super_block *sb,
							काष्ठा buffer_head *bh))
अणु
	पूर्णांक status = 0;

	अगर (bh == शून्य) अणु
		prपूर्णांकk("ocfs2: bh == NULL\n");
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	status = ocfs2_पढ़ो_virt_blocks(inode, v_block, 1, bh, 0, validate);

bail:
	वापस status;
पूर्ण


#पूर्ण_अगर  /* _EXTENT_MAP_H */

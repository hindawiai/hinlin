<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_सूची2_H__
#घोषणा __XFS_सूची2_H__

#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"

काष्ठा xfs_da_args;
काष्ठा xfs_inode;
काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_dir2_sf_hdr;
काष्ठा xfs_dir2_sf_entry;
काष्ठा xfs_dir2_data_hdr;
काष्ठा xfs_dir2_data_entry;
काष्ठा xfs_dir2_data_unused;
काष्ठा xfs_dir3_icमुक्त_hdr;
काष्ठा xfs_dir3_icleaf_hdr;

बाह्य काष्ठा xfs_name	xfs_name_करोtकरोt;

/*
 * Convert inode mode to directory entry filetype
 */
बाह्य अचिन्हित अक्षर xfs_mode_to_ftype(पूर्णांक mode);

/*
 * Generic directory पूर्णांकerface routines
 */
बाह्य व्योम xfs_dir_startup(व्योम);
बाह्य पूर्णांक xfs_da_mount(काष्ठा xfs_mount *mp);
बाह्य व्योम xfs_da_unmount(काष्ठा xfs_mount *mp);

बाह्य पूर्णांक xfs_dir_isempty(काष्ठा xfs_inode *dp);
बाह्य पूर्णांक xfs_dir_init(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
				काष्ठा xfs_inode *pdp);
बाह्य पूर्णांक xfs_dir_createname(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
				काष्ठा xfs_name *name, xfs_ino_t inum,
				xfs_extlen_t tot);
बाह्य पूर्णांक xfs_dir_lookup(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
				काष्ठा xfs_name *name, xfs_ino_t *inum,
				काष्ठा xfs_name *ci_name);
बाह्य पूर्णांक xfs_dir_हटाओname(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
				काष्ठा xfs_name *name, xfs_ino_t ino,
				xfs_extlen_t tot);
बाह्य पूर्णांक xfs_dir_replace(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
				काष्ठा xfs_name *name, xfs_ino_t inum,
				xfs_extlen_t tot);
बाह्य पूर्णांक xfs_dir_canenter(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
				काष्ठा xfs_name *name);

/*
 * Direct call from the bmap code, bypassing the generic directory layer.
 */
बाह्य पूर्णांक xfs_dir2_sf_to_block(काष्ठा xfs_da_args *args);

/*
 * Interface routines used by userspace utilities
 */
बाह्य पूर्णांक xfs_dir2_isblock(काष्ठा xfs_da_args *args, पूर्णांक *r);
बाह्य पूर्णांक xfs_dir2_isleaf(काष्ठा xfs_da_args *args, पूर्णांक *r);
बाह्य पूर्णांक xfs_dir2_shrink_inode(काष्ठा xfs_da_args *args, xfs_dir2_db_t db,
				काष्ठा xfs_buf *bp);

बाह्य व्योम xfs_dir2_data_मुक्तscan(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_data_hdr *hdr, पूर्णांक *loghead);
बाह्य व्योम xfs_dir2_data_log_entry(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *bp, काष्ठा xfs_dir2_data_entry *dep);
बाह्य व्योम xfs_dir2_data_log_header(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *bp);
बाह्य व्योम xfs_dir2_data_log_unused(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *bp, काष्ठा xfs_dir2_data_unused *dup);
बाह्य व्योम xfs_dir2_data_make_मुक्त(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *bp, xfs_dir2_data_aoff_t offset,
		xfs_dir2_data_aoff_t len, पूर्णांक *needlogp, पूर्णांक *needscanp);
बाह्य पूर्णांक xfs_dir2_data_use_मुक्त(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *bp, काष्ठा xfs_dir2_data_unused *dup,
		xfs_dir2_data_aoff_t offset, xfs_dir2_data_aoff_t len,
		पूर्णांक *needlogp, पूर्णांक *needscanp);

बाह्य काष्ठा xfs_dir2_data_मुक्त *xfs_dir2_data_मुक्तfind(
		काष्ठा xfs_dir2_data_hdr *hdr, काष्ठा xfs_dir2_data_मुक्त *bf,
		काष्ठा xfs_dir2_data_unused *dup);

बाह्य पूर्णांक xfs_dir_ino_validate(काष्ठा xfs_mount *mp, xfs_ino_t ino);

बाह्य स्थिर काष्ठा xfs_buf_ops xfs_dir3_block_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_dir3_leafn_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_dir3_leaf1_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_dir3_मुक्त_buf_ops;
बाह्य स्थिर काष्ठा xfs_buf_ops xfs_dir3_data_buf_ops;

/*
 * Directory offset/block conversion functions.
 *
 * DB blocks here are logical directory block numbers, not fileप्रणाली blocks.
 */

/*
 * Convert dataptr to byte in file space
 */
अटल अंतरभूत xfs_dir2_off_t
xfs_dir2_dataptr_to_byte(xfs_dir2_dataptr_t dp)
अणु
	वापस (xfs_dir2_off_t)dp << XFS_सूची2_DATA_ALIGN_LOG;
पूर्ण

/*
 * Convert byte in file space to dataptr.  It had better be aligned.
 */
अटल अंतरभूत xfs_dir2_dataptr_t
xfs_dir2_byte_to_dataptr(xfs_dir2_off_t by)
अणु
	वापस (xfs_dir2_dataptr_t)(by >> XFS_सूची2_DATA_ALIGN_LOG);
पूर्ण

/*
 * Convert byte in space to (DB) block
 */
अटल अंतरभूत xfs_dir2_db_t
xfs_dir2_byte_to_db(काष्ठा xfs_da_geometry *geo, xfs_dir2_off_t by)
अणु
	वापस (xfs_dir2_db_t)(by >> geo->blklog);
पूर्ण

/*
 * Convert dataptr to a block number
 */
अटल अंतरभूत xfs_dir2_db_t
xfs_dir2_dataptr_to_db(काष्ठा xfs_da_geometry *geo, xfs_dir2_dataptr_t dp)
अणु
	वापस xfs_dir2_byte_to_db(geo, xfs_dir2_dataptr_to_byte(dp));
पूर्ण

/*
 * Convert byte in space to offset in a block
 */
अटल अंतरभूत xfs_dir2_data_aoff_t
xfs_dir2_byte_to_off(काष्ठा xfs_da_geometry *geo, xfs_dir2_off_t by)
अणु
	वापस (xfs_dir2_data_aoff_t)(by & (geo->blksize - 1));
पूर्ण

/*
 * Convert dataptr to a byte offset in a block
 */
अटल अंतरभूत xfs_dir2_data_aoff_t
xfs_dir2_dataptr_to_off(काष्ठा xfs_da_geometry *geo, xfs_dir2_dataptr_t dp)
अणु
	वापस xfs_dir2_byte_to_off(geo, xfs_dir2_dataptr_to_byte(dp));
पूर्ण

/*
 * Convert block and offset to byte in space
 */
अटल अंतरभूत xfs_dir2_off_t
xfs_dir2_db_off_to_byte(काष्ठा xfs_da_geometry *geo, xfs_dir2_db_t db,
			xfs_dir2_data_aoff_t o)
अणु
	वापस ((xfs_dir2_off_t)db << geo->blklog) + o;
पूर्ण

/*
 * Convert block (DB) to block (dablk)
 */
अटल अंतरभूत xfs_dablk_t
xfs_dir2_db_to_da(काष्ठा xfs_da_geometry *geo, xfs_dir2_db_t db)
अणु
	वापस (xfs_dablk_t)(db << (geo->blklog - geo->fsblog));
पूर्ण

/*
 * Convert byte in space to (DA) block
 */
अटल अंतरभूत xfs_dablk_t
xfs_dir2_byte_to_da(काष्ठा xfs_da_geometry *geo, xfs_dir2_off_t by)
अणु
	वापस xfs_dir2_db_to_da(geo, xfs_dir2_byte_to_db(geo, by));
पूर्ण

/*
 * Convert block and offset to dataptr
 */
अटल अंतरभूत xfs_dir2_dataptr_t
xfs_dir2_db_off_to_dataptr(काष्ठा xfs_da_geometry *geo, xfs_dir2_db_t db,
			   xfs_dir2_data_aoff_t o)
अणु
	वापस xfs_dir2_byte_to_dataptr(xfs_dir2_db_off_to_byte(geo, db, o));
पूर्ण

/*
 * Convert block (dablk) to block (DB)
 */
अटल अंतरभूत xfs_dir2_db_t
xfs_dir2_da_to_db(काष्ठा xfs_da_geometry *geo, xfs_dablk_t da)
अणु
	वापस (xfs_dir2_db_t)(da >> (geo->blklog - geo->fsblog));
पूर्ण

/*
 * Convert block (dablk) to byte offset in space
 */
अटल अंतरभूत xfs_dir2_off_t
xfs_dir2_da_to_byte(काष्ठा xfs_da_geometry *geo, xfs_dablk_t da)
अणु
	वापस xfs_dir2_db_off_to_byte(geo, xfs_dir2_da_to_db(geo, da), 0);
पूर्ण

/*
 * Directory tail poपूर्णांकer accessor functions. Based on block geometry.
 */
अटल अंतरभूत काष्ठा xfs_dir2_block_tail *
xfs_dir2_block_tail_p(काष्ठा xfs_da_geometry *geo, काष्ठा xfs_dir2_data_hdr *hdr)
अणु
	वापस ((काष्ठा xfs_dir2_block_tail *)
		((अक्षर *)hdr + geo->blksize)) - 1;
पूर्ण

अटल अंतरभूत काष्ठा xfs_dir2_leaf_tail *
xfs_dir2_leaf_tail_p(काष्ठा xfs_da_geometry *geo, काष्ठा xfs_dir2_leaf *lp)
अणु
	वापस (काष्ठा xfs_dir2_leaf_tail *)
		((अक्षर *)lp + geo->blksize -
		  माप(काष्ठा xfs_dir2_leaf_tail));
पूर्ण

/*
 * The Linux API करोesn't pass करोwn the total size of the buffer
 * we पढ़ो पूर्णांकo करोwn to the fileप्रणाली.  With the filldir concept
 * it's not needed क्रम correct inक्रमmation, but the XFS dir2 leaf
 * code wants an estimate of the buffer size to calculate it's
 * पढ़ोahead winकरोw and size the buffers used क्रम mapping to
 * physical blocks.
 *
 * Try to give it an estimate that's good enough, maybe at some
 * poपूर्णांक we can change the ->सूची_पढ़ो prototype to include the
 * buffer size.  For now we use the current glibc buffer size.
 * musl libc hardcodes 2k and dietlibc uses PAGE_SIZE.
 */
#घोषणा XFS_READसूची_बफ_मानE	(32768)

अचिन्हित अक्षर xfs_dir3_get_dtype(काष्ठा xfs_mount *mp, uपूर्णांक8_t filetype);
अचिन्हित पूर्णांक xfs_dir3_data_end_offset(काष्ठा xfs_da_geometry *geo,
		काष्ठा xfs_dir2_data_hdr *hdr);
bool xfs_dir2_namecheck(स्थिर व्योम *name, माप_प्रकार length);

#पूर्ण_अगर	/* __XFS_सूची2_H__ */

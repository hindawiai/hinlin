<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Oracle.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_ONDISK_H
#घोषणा __XFS_ONDISK_H

#घोषणा XFS_CHECK_STRUCT_SIZE(काष्ठाname, size) \
	BUILD_BUG_ON_MSG(माप(काष्ठाname) != (size), "XFS: sizeof(" \
		#काष्ठाname ") is wrong, expected " #size)

#घोषणा XFS_CHECK_OFFSET(काष्ठाname, member, off) \
	BUILD_BUG_ON_MSG(दुरत्व(काष्ठाname, member) != (off), \
		"XFS: offsetof(" #काष्ठाname ", " #member ") is wrong, " \
		"expected " #off)

#घोषणा XFS_CHECK_VALUE(value, expected) \
	BUILD_BUG_ON_MSG((value) != (expected), \
		"XFS: value of " #value " is wrong, expected " #expected)

अटल अंतरभूत व्योम __init
xfs_check_ondisk_काष्ठाs(व्योम)
अणु
	/* ag/file काष्ठाures */
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_acl,			4);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_acl_entry,		12);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_agf,			224);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_agfl,			36);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_agi,			344);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_bmbt_key,		8);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_bmbt_rec,		16);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_bmdr_block,		4);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_btree_block_shdr,	48);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_btree_block_lhdr,	64);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_btree_block,		72);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dinode,		176);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_disk_dquot,		104);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dqblk,			136);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dsb,			264);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dsymlink_hdr,		56);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_inobt_key,		4);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_inobt_rec,		16);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_refcount_key,		4);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_refcount_rec,		12);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_rmap_key,		20);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_rmap_rec,		24);
	XFS_CHECK_STRUCT_SIZE(xfs_बारtamp_t,			8);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_legacy_बारtamp,	8);
	XFS_CHECK_STRUCT_SIZE(xfs_alloc_key_t,			8);
	XFS_CHECK_STRUCT_SIZE(xfs_alloc_ptr_t,			4);
	XFS_CHECK_STRUCT_SIZE(xfs_alloc_rec_t,			8);
	XFS_CHECK_STRUCT_SIZE(xfs_inobt_ptr_t,			4);
	XFS_CHECK_STRUCT_SIZE(xfs_refcount_ptr_t,		4);
	XFS_CHECK_STRUCT_SIZE(xfs_rmap_ptr_t,			4);

	/* dir/attr trees */
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_attr3_leaf_hdr,	80);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_attr3_leafblock,	88);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_attr3_rmt_hdr,		56);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_da3_blkinfo,		56);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_da3_पूर्णांकnode,		64);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_da3_node_hdr,		64);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dir3_blk_hdr,		48);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dir3_data_hdr,		64);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dir3_मुक्त,		64);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dir3_मुक्त_hdr,		64);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dir3_leaf,		64);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dir3_leaf_hdr,		64);
	XFS_CHECK_STRUCT_SIZE(xfs_attr_leaf_entry_t,		8);
	XFS_CHECK_STRUCT_SIZE(xfs_attr_leaf_hdr_t,		32);
	XFS_CHECK_STRUCT_SIZE(xfs_attr_leaf_map_t,		4);
	XFS_CHECK_STRUCT_SIZE(xfs_attr_leaf_name_local_t,	4);

	/*
	 * m68k has problems with xfs_attr_leaf_name_remote_t, but we pad it to
	 * 4 bytes anyway so it's not obviously a problem.  Hence क्रम the moment
	 * we करोn't check this काष्ठाure. This can be re-instated when the attr
	 * definitions are updated to use c99 VLA definitions.
	 *
	XFS_CHECK_STRUCT_SIZE(xfs_attr_leaf_name_remote_t,	12);
	 */

	XFS_CHECK_OFFSET(xfs_attr_leaf_name_local_t, valuelen,	0);
	XFS_CHECK_OFFSET(xfs_attr_leaf_name_local_t, namelen,	2);
	XFS_CHECK_OFFSET(xfs_attr_leaf_name_local_t, nameval,	3);
	XFS_CHECK_OFFSET(xfs_attr_leaf_name_remote_t, valueblk,	0);
	XFS_CHECK_OFFSET(xfs_attr_leaf_name_remote_t, valuelen,	4);
	XFS_CHECK_OFFSET(xfs_attr_leaf_name_remote_t, namelen,	8);
	XFS_CHECK_OFFSET(xfs_attr_leaf_name_remote_t, name,	9);
	XFS_CHECK_STRUCT_SIZE(xfs_attr_leafblock_t,		40);
	XFS_CHECK_OFFSET(काष्ठा xfs_attr_लघुक्रमm, hdr.totsize, 0);
	XFS_CHECK_OFFSET(काष्ठा xfs_attr_लघुक्रमm, hdr.count,	 2);
	XFS_CHECK_OFFSET(काष्ठा xfs_attr_लघुक्रमm, list[0].namelen,	4);
	XFS_CHECK_OFFSET(काष्ठा xfs_attr_लघुक्रमm, list[0].valuelen,	5);
	XFS_CHECK_OFFSET(काष्ठा xfs_attr_लघुक्रमm, list[0].flags,	6);
	XFS_CHECK_OFFSET(काष्ठा xfs_attr_लघुक्रमm, list[0].nameval,	7);
	XFS_CHECK_STRUCT_SIZE(xfs_da_blkinfo_t,			12);
	XFS_CHECK_STRUCT_SIZE(xfs_da_पूर्णांकnode_t,			16);
	XFS_CHECK_STRUCT_SIZE(xfs_da_node_entry_t,		8);
	XFS_CHECK_STRUCT_SIZE(xfs_da_node_hdr_t,		16);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_data_मुक्त_t,		4);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_data_hdr_t,		16);
	XFS_CHECK_OFFSET(xfs_dir2_data_unused_t, मुक्तtag,	0);
	XFS_CHECK_OFFSET(xfs_dir2_data_unused_t, length,	2);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_मुक्त_hdr_t,		16);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_मुक्त_t,			16);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_leaf_entry_t,		8);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_leaf_hdr_t,		16);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_leaf_t,			16);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_leaf_tail_t,		4);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_sf_entry_t,		3);
	XFS_CHECK_OFFSET(xfs_dir2_sf_entry_t, namelen,		0);
	XFS_CHECK_OFFSET(xfs_dir2_sf_entry_t, offset,		1);
	XFS_CHECK_OFFSET(xfs_dir2_sf_entry_t, name,		3);
	XFS_CHECK_STRUCT_SIZE(xfs_dir2_sf_hdr_t,		10);

	/* log काष्ठाures */
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_buf_log_क्रमmat,	88);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_dq_logक्रमmat,		24);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_efd_log_क्रमmat_32,	28);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_efd_log_क्रमmat_64,	32);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_efi_log_क्रमmat_32,	28);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_efi_log_क्रमmat_64,	32);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_extent_32,		12);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_extent_64,		16);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_log_dinode,		176);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_icreate_log,		28);
	XFS_CHECK_STRUCT_SIZE(xfs_log_बारtamp_t,		8);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_log_legacy_बारtamp,	8);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_inode_log_क्रमmat_32,	52);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_inode_log_क्रमmat,	56);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_qoff_logक्रमmat,	20);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_trans_header,		16);

	/*
	 * The v5 superblock क्रमmat extended several v4 header काष्ठाures with
	 * additional data. While new fields are only accessible on v5
	 * superblocks, it's important that the v5 काष्ठाures place original v4
	 * fields/headers in the correct location on-disk. For example, we must
	 * be able to find magic values at the same location in certain blocks
	 * regardless of superblock version.
	 *
	 * The following checks ensure that various v5 data काष्ठाures place the
	 * subset of v4 metadata associated with the same type of block at the
	 * start of the on-disk block. If there is no data काष्ठाure definition
	 * क्रम certain types of v4 blocks, traverse करोwn to the first field of
	 * common metadata (e.g., magic value) and make sure it is at offset
	 * zero.
	 */
	XFS_CHECK_OFFSET(काष्ठा xfs_dir3_leaf, hdr.info.hdr,	0);
	XFS_CHECK_OFFSET(काष्ठा xfs_da3_पूर्णांकnode, hdr.info.hdr,	0);
	XFS_CHECK_OFFSET(काष्ठा xfs_dir3_data_hdr, hdr.magic,	0);
	XFS_CHECK_OFFSET(काष्ठा xfs_dir3_मुक्त, hdr.hdr.magic,	0);
	XFS_CHECK_OFFSET(काष्ठा xfs_attr3_leafblock, hdr.info.hdr, 0);

	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_bulkstat,		192);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_inumbers,		24);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_bulkstat_req,		64);
	XFS_CHECK_STRUCT_SIZE(काष्ठा xfs_inumbers_req,		64);

	/*
	 * Make sure the incore inode बारtamp range corresponds to hand
	 * converted values based on the ondisk क्रमmat specअगरication.
	 */
	XFS_CHECK_VALUE(XFS_BIGTIME_TIME_MIN - XFS_BIGTIME_EPOCH_OFFSET,
			XFS_LEGACY_TIME_MIN);
	XFS_CHECK_VALUE(XFS_BIGTIME_TIME_MAX - XFS_BIGTIME_EPOCH_OFFSET,
			16299260424LL);

	/* Do the same with the incore quota expiration range. */
	XFS_CHECK_VALUE(XFS_DQ_BIGTIME_EXPIRY_MIN << XFS_DQ_BIGTIME_SHIFT, 4);
	XFS_CHECK_VALUE(XFS_DQ_BIGTIME_EXPIRY_MAX << XFS_DQ_BIGTIME_SHIFT,
			16299260424LL);
पूर्ण

#पूर्ण_अगर /* __XFS_ONDISK_H */

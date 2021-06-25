<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_SB_H__
#घोषणा	__XFS_SB_H__

काष्ठा xfs_mount;
काष्ठा xfs_sb;
काष्ठा xfs_dsb;
काष्ठा xfs_trans;
काष्ठा xfs_fsop_geom;
काष्ठा xfs_perag;

/*
 * perag get/put wrappers क्रम ref counting
 */
बाह्य काष्ठा xfs_perag *xfs_perag_get(काष्ठा xfs_mount *, xfs_agnumber_t);
बाह्य काष्ठा xfs_perag *xfs_perag_get_tag(काष्ठा xfs_mount *, xfs_agnumber_t,
					   पूर्णांक tag);
बाह्य व्योम	xfs_perag_put(काष्ठा xfs_perag *pag);
बाह्य पूर्णांक	xfs_initialize_perag_data(काष्ठा xfs_mount *, xfs_agnumber_t);

बाह्य व्योम	xfs_log_sb(काष्ठा xfs_trans *tp);
बाह्य पूर्णांक	xfs_sync_sb(काष्ठा xfs_mount *mp, bool रुको);
बाह्य पूर्णांक	xfs_sync_sb_buf(काष्ठा xfs_mount *mp);
बाह्य व्योम	xfs_sb_mount_common(काष्ठा xfs_mount *mp, काष्ठा xfs_sb *sbp);
बाह्य व्योम	xfs_sb_from_disk(काष्ठा xfs_sb *to, काष्ठा xfs_dsb *from);
बाह्य व्योम	xfs_sb_to_disk(काष्ठा xfs_dsb *to, काष्ठा xfs_sb *from);
बाह्य व्योम	xfs_sb_quota_from_disk(काष्ठा xfs_sb *sbp);

बाह्य पूर्णांक	xfs_update_secondary_sbs(काष्ठा xfs_mount *mp);

#घोषणा XFS_FS_GEOM_MAX_STRUCT_VER	(4)
बाह्य व्योम	xfs_fs_geometry(काष्ठा xfs_sb *sbp, काष्ठा xfs_fsop_geom *geo,
				पूर्णांक काष्ठा_version);
बाह्य पूर्णांक	xfs_sb_पढ़ो_secondary(काष्ठा xfs_mount *mp,
				काष्ठा xfs_trans *tp, xfs_agnumber_t agno,
				काष्ठा xfs_buf **bpp);
बाह्य पूर्णांक	xfs_sb_get_secondary(काष्ठा xfs_mount *mp,
				काष्ठा xfs_trans *tp, xfs_agnumber_t agno,
				काष्ठा xfs_buf **bpp);

बाह्य bool	xfs_validate_stripe_geometry(काष्ठा xfs_mount *mp,
		__s64 sunit, __s64 swidth, पूर्णांक sectorsize, bool silent);

#पूर्ण_अगर	/* __XFS_SB_H__ */

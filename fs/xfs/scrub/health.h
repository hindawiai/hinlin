<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_HEALTH_H__
#घोषणा __XFS_SCRUB_HEALTH_H__

अचिन्हित पूर्णांक xchk_health_mask_क्रम_scrub_type(__u32 scrub_type);
व्योम xchk_update_health(काष्ठा xfs_scrub *sc);
bool xchk_ag_btree_healthy_enough(काष्ठा xfs_scrub *sc, काष्ठा xfs_perag *pag,
		xfs_btnum_t btnum);

#पूर्ण_अगर /* __XFS_SCRUB_HEALTH_H__ */

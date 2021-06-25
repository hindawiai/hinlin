<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_btree.h"
#समावेश "scrub/scrub.h"

/* Figure out which block the btree cursor was poपूर्णांकing to. */
अटल अंतरभूत xfs_fsblock_t
xchk_btree_cur_fsbno(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	अगर (level < cur->bc_nlevels && cur->bc_bufs[level])
		वापस XFS_DADDR_TO_FSB(cur->bc_mp, cur->bc_bufs[level]->b_bn);
	अन्यथा अगर (level == cur->bc_nlevels - 1 &&
		 cur->bc_flags & XFS_BTREE_LONG_PTRS)
		वापस XFS_INO_TO_FSB(cur->bc_mp, cur->bc_ino.ip->i_ino);
	अन्यथा अगर (!(cur->bc_flags & XFS_BTREE_LONG_PTRS))
		वापस XFS_AGB_TO_FSB(cur->bc_mp, cur->bc_ag.agno, 0);
	वापस शून्यFSBLOCK;
पूर्ण

/*
 * We include this last to have the helpers above available क्रम the trace
 * event implementations.
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "scrub/trace.h"

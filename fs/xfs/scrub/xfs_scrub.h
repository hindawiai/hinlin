<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_H__
#घोषणा __XFS_SCRUB_H__

#अगर_अघोषित CONFIG_XFS_ONLINE_SCRUB
# define xfs_scrub_metadata(file, sm)	(-ENOTTY)
#अन्यथा
पूर्णांक xfs_scrub_metadata(काष्ठा file *file, काष्ठा xfs_scrub_metadata *sm);
#पूर्ण_अगर /* CONFIG_XFS_ONLINE_SCRUB */

#पूर्ण_अगर	/* __XFS_SCRUB_H__ */

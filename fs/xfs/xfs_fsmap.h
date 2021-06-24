<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_FSMAP_H__
#घोषणा __XFS_FSMAP_H__

काष्ठा fsmap;

/* पूर्णांकernal fsmap representation */
काष्ठा xfs_fsmap अणु
	dev_t		fmr_device;	/* device id */
	uपूर्णांक32_t	fmr_flags;	/* mapping flags */
	uपूर्णांक64_t	fmr_physical;	/* device offset of segment */
	uपूर्णांक64_t	fmr_owner;	/* owner id */
	xfs_fileoff_t	fmr_offset;	/* file offset of segment */
	xfs_filblks_t	fmr_length;	/* length of segment, blocks */
पूर्ण;

काष्ठा xfs_fsmap_head अणु
	uपूर्णांक32_t	fmh_अगरlags;	/* control flags */
	uपूर्णांक32_t	fmh_oflags;	/* output flags */
	अचिन्हित पूर्णांक	fmh_count;	/* # of entries in array incl. input */
	अचिन्हित पूर्णांक	fmh_entries;	/* # of entries filled in (output). */

	काष्ठा xfs_fsmap fmh_keys[2];	/* low and high keys */
पूर्ण;

व्योम xfs_fsmap_to_पूर्णांकernal(काष्ठा xfs_fsmap *dest, काष्ठा fsmap *src);

पूर्णांक xfs_getfsmap(काष्ठा xfs_mount *mp, काष्ठा xfs_fsmap_head *head,
		काष्ठा fsmap *out_recs);

#पूर्ण_अगर /* __XFS_FSMAP_H__ */

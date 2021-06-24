<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_HEALTH_H__
#घोषणा __XFS_HEALTH_H__

/*
 * In-Core Fileप्रणाली Health Assessments
 * =====================================
 *
 * We'd like to be able to summarize the current health status of the
 * fileप्रणाली so that the administrator knows when it's necessary to schedule
 * some करोwnसमय क्रम repairs.  Until then, we would also like to aव्योम abrupt
 * shutकरोwns due to corrupt metadata.
 *
 * The online scrub feature evaluates the health of all fileप्रणाली metadata.
 * When scrub detects corruption in a piece of metadata it will set the
 * corresponding sickness flag, and repair will clear it अगर successful.  If
 * problems reमुख्य at unmount समय, we can also request manual पूर्णांकervention by
 * logging a notice to run xfs_repair.
 *
 * Each health tracking group uses a pair of fields क्रम reporting.  The
 * "checked" field tell us अगर a given piece of metadata has ever been examined,
 * and the "sick" field tells us अगर that piece was found to need repairs.
 * Thereक्रमe we can conclude that क्रम a given sick flag value:
 *
 *  - checked && sick  => metadata needs repair
 *  - checked && !sick => metadata is ok
 *  - !checked         => has not been examined since mount
 */

काष्ठा xfs_mount;
काष्ठा xfs_perag;
काष्ठा xfs_inode;
काष्ठा xfs_fsop_geom;

/* Observable health issues क्रम metadata spanning the entire fileप्रणाली. */
#घोषणा XFS_SICK_FS_COUNTERS	(1 << 0)  /* summary counters */
#घोषणा XFS_SICK_FS_UQUOTA	(1 << 1)  /* user quota */
#घोषणा XFS_SICK_FS_GQUOTA	(1 << 2)  /* group quota */
#घोषणा XFS_SICK_FS_PQUOTA	(1 << 3)  /* project quota */

/* Observable health issues क्रम realसमय volume metadata. */
#घोषणा XFS_SICK_RT_BITMAP	(1 << 0)  /* realसमय biपंचांगap */
#घोषणा XFS_SICK_RT_SUMMARY	(1 << 1)  /* realसमय summary */

/* Observable health issues क्रम AG metadata. */
#घोषणा XFS_SICK_AG_SB		(1 << 0)  /* superblock */
#घोषणा XFS_SICK_AG_AGF		(1 << 1)  /* AGF header */
#घोषणा XFS_SICK_AG_AGFL	(1 << 2)  /* AGFL header */
#घोषणा XFS_SICK_AG_AGI		(1 << 3)  /* AGI header */
#घोषणा XFS_SICK_AG_BNOBT	(1 << 4)  /* मुक्त space by block */
#घोषणा XFS_SICK_AG_CNTBT	(1 << 5)  /* मुक्त space by length */
#घोषणा XFS_SICK_AG_INOBT	(1 << 6)  /* inode index */
#घोषणा XFS_SICK_AG_FINOBT	(1 << 7)  /* मुक्त inode index */
#घोषणा XFS_SICK_AG_RMAPBT	(1 << 8)  /* reverse mappings */
#घोषणा XFS_SICK_AG_REFCNTBT	(1 << 9)  /* reference counts */

/* Observable health issues क्रम inode metadata. */
#घोषणा XFS_SICK_INO_CORE	(1 << 0)  /* inode core */
#घोषणा XFS_SICK_INO_BMBTD	(1 << 1)  /* data विभाजन */
#घोषणा XFS_SICK_INO_BMBTA	(1 << 2)  /* attr विभाजन */
#घोषणा XFS_SICK_INO_BMBTC	(1 << 3)  /* cow विभाजन */
#घोषणा XFS_SICK_INO_सूची	(1 << 4)  /* directory */
#घोषणा XFS_SICK_INO_XATTR	(1 << 5)  /* extended attributes */
#घोषणा XFS_SICK_INO_SYMLINK	(1 << 6)  /* symbolic link remote target */
#घोषणा XFS_SICK_INO_PARENT	(1 << 7)  /* parent poपूर्णांकers */

/* Primary evidence of health problems in a given group. */
#घोषणा XFS_SICK_FS_PRIMARY	(XFS_SICK_FS_COUNTERS | \
				 XFS_SICK_FS_UQUOTA | \
				 XFS_SICK_FS_GQUOTA | \
				 XFS_SICK_FS_PQUOTA)

#घोषणा XFS_SICK_RT_PRIMARY	(XFS_SICK_RT_BITMAP | \
				 XFS_SICK_RT_SUMMARY)

#घोषणा XFS_SICK_AG_PRIMARY	(XFS_SICK_AG_SB | \
				 XFS_SICK_AG_AGF | \
				 XFS_SICK_AG_AGFL | \
				 XFS_SICK_AG_AGI | \
				 XFS_SICK_AG_BNOBT | \
				 XFS_SICK_AG_CNTBT | \
				 XFS_SICK_AG_INOBT | \
				 XFS_SICK_AG_FINOBT | \
				 XFS_SICK_AG_RMAPBT | \
				 XFS_SICK_AG_REFCNTBT)

#घोषणा XFS_SICK_INO_PRIMARY	(XFS_SICK_INO_CORE | \
				 XFS_SICK_INO_BMBTD | \
				 XFS_SICK_INO_BMBTA | \
				 XFS_SICK_INO_BMBTC | \
				 XFS_SICK_INO_सूची | \
				 XFS_SICK_INO_XATTR | \
				 XFS_SICK_INO_SYMLINK | \
				 XFS_SICK_INO_PARENT)

/* These functions must be provided by the xfs implementation. */

व्योम xfs_fs_mark_sick(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक mask);
व्योम xfs_fs_mark_healthy(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक mask);
व्योम xfs_fs_measure_sickness(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक *sick,
		अचिन्हित पूर्णांक *checked);

व्योम xfs_rt_mark_sick(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक mask);
व्योम xfs_rt_mark_healthy(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक mask);
व्योम xfs_rt_measure_sickness(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक *sick,
		अचिन्हित पूर्णांक *checked);

व्योम xfs_ag_mark_sick(काष्ठा xfs_perag *pag, अचिन्हित पूर्णांक mask);
व्योम xfs_ag_mark_healthy(काष्ठा xfs_perag *pag, अचिन्हित पूर्णांक mask);
व्योम xfs_ag_measure_sickness(काष्ठा xfs_perag *pag, अचिन्हित पूर्णांक *sick,
		अचिन्हित पूर्णांक *checked);

व्योम xfs_inode_mark_sick(काष्ठा xfs_inode *ip, अचिन्हित पूर्णांक mask);
व्योम xfs_inode_mark_healthy(काष्ठा xfs_inode *ip, अचिन्हित पूर्णांक mask);
व्योम xfs_inode_measure_sickness(काष्ठा xfs_inode *ip, अचिन्हित पूर्णांक *sick,
		अचिन्हित पूर्णांक *checked);

व्योम xfs_health_unmount(काष्ठा xfs_mount *mp);

/* Now some helpers. */

अटल अंतरभूत bool
xfs_fs_has_sickness(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक	sick, checked;

	xfs_fs_measure_sickness(mp, &sick, &checked);
	वापस sick & mask;
पूर्ण

अटल अंतरभूत bool
xfs_rt_has_sickness(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक	sick, checked;

	xfs_rt_measure_sickness(mp, &sick, &checked);
	वापस sick & mask;
पूर्ण

अटल अंतरभूत bool
xfs_ag_has_sickness(काष्ठा xfs_perag *pag, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक	sick, checked;

	xfs_ag_measure_sickness(pag, &sick, &checked);
	वापस sick & mask;
पूर्ण

अटल अंतरभूत bool
xfs_inode_has_sickness(काष्ठा xfs_inode *ip, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक	sick, checked;

	xfs_inode_measure_sickness(ip, &sick, &checked);
	वापस sick & mask;
पूर्ण

अटल अंतरभूत bool
xfs_fs_is_healthy(काष्ठा xfs_mount *mp)
अणु
	वापस !xfs_fs_has_sickness(mp, -1U);
पूर्ण

अटल अंतरभूत bool
xfs_rt_is_healthy(काष्ठा xfs_mount *mp)
अणु
	वापस !xfs_rt_has_sickness(mp, -1U);
पूर्ण

अटल अंतरभूत bool
xfs_ag_is_healthy(काष्ठा xfs_perag *pag)
अणु
	वापस !xfs_ag_has_sickness(pag, -1U);
पूर्ण

अटल अंतरभूत bool
xfs_inode_is_healthy(काष्ठा xfs_inode *ip)
अणु
	वापस !xfs_inode_has_sickness(ip, -1U);
पूर्ण

व्योम xfs_fsop_geom_health(काष्ठा xfs_mount *mp, काष्ठा xfs_fsop_geom *geo);
व्योम xfs_ag_geom_health(काष्ठा xfs_perag *pag, काष्ठा xfs_ag_geometry *ageo);
व्योम xfs_bulkstat_health(काष्ठा xfs_inode *ip, काष्ठा xfs_bulkstat *bs);

#पूर्ण_अगर	/* __XFS_HEALTH_H__ */

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"

/*
 * Tunable XFS parameters.  xfs_params is required even when CONFIG_SYSCTL=n,
 * other XFS code uses these values.  Times are measured in centisecs (i.e.
 * 100ths of a second) with the exception of blockgc_समयr, which is measured
 * in seconds.
 */
xfs_param_t xfs_params = अणु
			  /*	MIN		DFLT		MAX	*/
	.sgid_inherit	= अणु	0,		0,		1	पूर्ण,
	.symlink_mode	= अणु	0,		0,		1	पूर्ण,
	.panic_mask	= अणु	0,		0,		256	पूर्ण,
	.error_level	= अणु	0,		3,		11	पूर्ण,
	.syncd_समयr	= अणु	1*100,		30*100,		7200*100पूर्ण,
	.stats_clear	= अणु	0,		0,		1	पूर्ण,
	.inherit_sync	= अणु	0,		1,		1	पूर्ण,
	.inherit_nodump	= अणु	0,		1,		1	पूर्ण,
	.inherit_noatim = अणु	0,		1,		1	पूर्ण,
	.xfs_buf_समयr	= अणु	100/2,		1*100,		30*100	पूर्ण,
	.xfs_buf_age	= अणु	1*100,		15*100,		7200*100पूर्ण,
	.inherit_nosym	= अणु	0,		0,		1	पूर्ण,
	.rotorstep	= अणु	1,		1,		255	पूर्ण,
	.inherit_nodfrg	= अणु	0,		1,		1	पूर्ण,
	.fstrm_समयr	= अणु	1,		30*100,		3600*100पूर्ण,
	.blockgc_समयr	= अणु	1,		300,		3600*24पूर्ण,
पूर्ण;

काष्ठा xfs_globals xfs_globals = अणु
	.log_recovery_delay	=	0,	/* no delay by शेष */
	.mount_delay		=	0,	/* no delay by शेष */
#अगर_घोषित XFS_ASSERT_FATAL
	.bug_on_निश्चित		=	true,	/* निश्चित failures BUG() */
#अन्यथा
	.bug_on_निश्चित		=	false,	/* निश्चित failures WARN() */
#पूर्ण_अगर
#अगर_घोषित DEBUG
	.pwork_thपढ़ोs		=	-1,	/* स्वतःmatic thपढ़ो detection */
#पूर्ण_अगर
पूर्ण;

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2001-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_error.h"

अटल काष्ठा ctl_table_header *xfs_table_header;

#अगर_घोषित CONFIG_PROC_FS
STATIC पूर्णांक
xfs_stats_clear_proc_handler(
	काष्ठा ctl_table	*ctl,
	पूर्णांक			ग_लिखो,
	व्योम			*buffer,
	माप_प्रकार			*lenp,
	loff_t			*ppos)
अणु
	पूर्णांक		ret, *valp = ctl->data;

	ret = proc_करोपूर्णांकvec_minmax(ctl, ग_लिखो, buffer, lenp, ppos);

	अगर (!ret && ग_लिखो && *valp) अणु
		xfs_stats_clearall(xfsstats.xs_stats);
		xfs_stats_clear = 0;
	पूर्ण

	वापस ret;
पूर्ण

STATIC पूर्णांक
xfs_panic_mask_proc_handler(
	काष्ठा ctl_table	*ctl,
	पूर्णांक			ग_लिखो,
	व्योम			*buffer,
	माप_प्रकार			*lenp,
	loff_t			*ppos)
अणु
	पूर्णांक		ret, *valp = ctl->data;

	ret = proc_करोपूर्णांकvec_minmax(ctl, ग_लिखो, buffer, lenp, ppos);
	अगर (!ret && ग_लिखो) अणु
		xfs_panic_mask = *valp;
#अगर_घोषित DEBUG
		xfs_panic_mask |= (XFS_PTAG_SHUTDOWN_CORRUPT | XFS_PTAG_LOGRES);
#पूर्ण_अगर
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

STATIC पूर्णांक
xfs_deprecated_करोपूर्णांकvec_minmax(
	काष्ठा ctl_table	*ctl,
	पूर्णांक			ग_लिखो,
	व्योम			*buffer,
	माप_प्रकार			*lenp,
	loff_t			*ppos)
अणु
	अगर (ग_लिखो) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING
				"XFS: %s sysctl option is deprecated.\n",
				ctl->procname);
	पूर्ण
	वापस proc_करोपूर्णांकvec_minmax(ctl, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल काष्ठा ctl_table xfs_table[] = अणु
	अणु
		.procname	= "irix_sgid_inherit",
		.data		= &xfs_params.sgid_inherit.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= xfs_deprecated_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.sgid_inherit.min,
		.extra2		= &xfs_params.sgid_inherit.max
	पूर्ण,
	अणु
		.procname	= "irix_symlink_mode",
		.data		= &xfs_params.symlink_mode.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= xfs_deprecated_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.symlink_mode.min,
		.extra2		= &xfs_params.symlink_mode.max
	पूर्ण,
	अणु
		.procname	= "panic_mask",
		.data		= &xfs_params.panic_mask.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= xfs_panic_mask_proc_handler,
		.extra1		= &xfs_params.panic_mask.min,
		.extra2		= &xfs_params.panic_mask.max
	पूर्ण,

	अणु
		.procname	= "error_level",
		.data		= &xfs_params.error_level.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.error_level.min,
		.extra2		= &xfs_params.error_level.max
	पूर्ण,
	अणु
		.procname	= "xfssyncd_centisecs",
		.data		= &xfs_params.syncd_समयr.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.syncd_समयr.min,
		.extra2		= &xfs_params.syncd_समयr.max
	पूर्ण,
	अणु
		.procname	= "inherit_sync",
		.data		= &xfs_params.inherit_sync.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.inherit_sync.min,
		.extra2		= &xfs_params.inherit_sync.max
	पूर्ण,
	अणु
		.procname	= "inherit_nodump",
		.data		= &xfs_params.inherit_nodump.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.inherit_nodump.min,
		.extra2		= &xfs_params.inherit_nodump.max
	पूर्ण,
	अणु
		.procname	= "inherit_noatime",
		.data		= &xfs_params.inherit_noatim.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.inherit_noatim.min,
		.extra2		= &xfs_params.inherit_noatim.max
	पूर्ण,
	अणु
		.procname	= "inherit_nosymlinks",
		.data		= &xfs_params.inherit_nosym.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.inherit_nosym.min,
		.extra2		= &xfs_params.inherit_nosym.max
	पूर्ण,
	अणु
		.procname	= "rotorstep",
		.data		= &xfs_params.rotorstep.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.rotorstep.min,
		.extra2		= &xfs_params.rotorstep.max
	पूर्ण,
	अणु
		.procname	= "inherit_nodefrag",
		.data		= &xfs_params.inherit_nodfrg.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.inherit_nodfrg.min,
		.extra2		= &xfs_params.inherit_nodfrg.max
	पूर्ण,
	अणु
		.procname	= "filestream_centisecs",
		.data		= &xfs_params.fstrm_समयr.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.fstrm_समयr.min,
		.extra2		= &xfs_params.fstrm_समयr.max,
	पूर्ण,
	अणु
		.procname	= "speculative_prealloc_lifetime",
		.data		= &xfs_params.blockgc_समयr.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.blockgc_समयr.min,
		.extra2		= &xfs_params.blockgc_समयr.max,
	पूर्ण,
	अणु
		.procname	= "speculative_cow_prealloc_lifetime",
		.data		= &xfs_params.blockgc_समयr.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= xfs_deprecated_करोपूर्णांकvec_minmax,
		.extra1		= &xfs_params.blockgc_समयr.min,
		.extra2		= &xfs_params.blockgc_समयr.max,
	पूर्ण,
	/* please keep this the last entry */
#अगर_घोषित CONFIG_PROC_FS
	अणु
		.procname	= "stats_clear",
		.data		= &xfs_params.stats_clear.val,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= xfs_stats_clear_proc_handler,
		.extra1		= &xfs_params.stats_clear.min,
		.extra2		= &xfs_params.stats_clear.max
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PROC_FS */

	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table xfs_dir_table[] = अणु
	अणु
		.procname	= "xfs",
		.mode		= 0555,
		.child		= xfs_table
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table xfs_root_table[] = अणु
	अणु
		.procname	= "fs",
		.mode		= 0555,
		.child		= xfs_dir_table
	पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
xfs_sysctl_रेजिस्टर(व्योम)
अणु
	xfs_table_header = रेजिस्टर_sysctl_table(xfs_root_table);
	अगर (!xfs_table_header)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम
xfs_sysctl_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_sysctl_table(xfs_table_header);
पूर्ण

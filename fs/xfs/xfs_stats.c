<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"

काष्ठा xstats xfsstats;

अटल पूर्णांक counter_val(काष्ठा xfsstats __percpu *stats, पूर्णांक idx)
अणु
	पूर्णांक val = 0, cpu;

	क्रम_each_possible_cpu(cpu)
		val += *(((__u32 *)per_cpu_ptr(stats, cpu) + idx));
	वापस val;
पूर्ण

पूर्णांक xfs_stats_क्रमmat(काष्ठा xfsstats __percpu *stats, अक्षर *buf)
अणु
	पूर्णांक		i, j;
	पूर्णांक		len = 0;
	uपूर्णांक64_t	xs_xstrat_bytes = 0;
	uपूर्णांक64_t	xs_ग_लिखो_bytes = 0;
	uपूर्णांक64_t	xs_पढ़ो_bytes = 0;
	uपूर्णांक64_t	defer_relog = 0;

	अटल स्थिर काष्ठा xstats_entry अणु
		अक्षर	*desc;
		पूर्णांक	endpoपूर्णांक;
	पूर्ण xstats[] = अणु
		अणु "extent_alloc",	xfsstats_offset(xs_abt_lookup)	पूर्ण,
		अणु "abt",		xfsstats_offset(xs_blk_mapr)	पूर्ण,
		अणु "blk_map",		xfsstats_offset(xs_bmbt_lookup)	पूर्ण,
		अणु "bmbt",		xfsstats_offset(xs_dir_lookup)	पूर्ण,
		अणु "dir",		xfsstats_offset(xs_trans_sync)	पूर्ण,
		अणु "trans",		xfsstats_offset(xs_ig_attempts)	पूर्ण,
		अणु "ig",			xfsstats_offset(xs_log_ग_लिखोs)	पूर्ण,
		अणु "log",		xfsstats_offset(xs_try_logspace)पूर्ण,
		अणु "push_ail",		xfsstats_offset(xs_xstrat_quick)पूर्ण,
		अणु "xstrat",		xfsstats_offset(xs_ग_लिखो_calls)	पूर्ण,
		अणु "rw",			xfsstats_offset(xs_attr_get)	पूर्ण,
		अणु "attr",		xfsstats_offset(xs_अगरlush_count)पूर्ण,
		अणु "icluster",		xfsstats_offset(vn_active)	पूर्ण,
		अणु "vnodes",		xfsstats_offset(xb_get)		पूर्ण,
		अणु "buf",		xfsstats_offset(xs_abtb_2)	पूर्ण,
		अणु "abtb2",		xfsstats_offset(xs_abtc_2)	पूर्ण,
		अणु "abtc2",		xfsstats_offset(xs_bmbt_2)	पूर्ण,
		अणु "bmbt2",		xfsstats_offset(xs_ibt_2)	पूर्ण,
		अणु "ibt2",		xfsstats_offset(xs_fibt_2)	पूर्ण,
		अणु "fibt2",		xfsstats_offset(xs_rmap_2)	पूर्ण,
		अणु "rmapbt",		xfsstats_offset(xs_refcbt_2)	पूर्ण,
		अणु "refcntbt",		xfsstats_offset(xs_qm_dqreclaims)पूर्ण,
		/* we prपूर्णांक both series of quota inक्रमmation together */
		अणु "qm",			xfsstats_offset(xs_xstrat_bytes)पूर्ण,
	पूर्ण;

	/* Loop over all stats groups */

	क्रम (i = j = 0; i < ARRAY_SIZE(xstats); i++) अणु
		len += scnम_लिखो(buf + len, PATH_MAX - len, "%s",
				xstats[i].desc);
		/* inner loop करोes each group */
		क्रम (; j < xstats[i].endpoपूर्णांक; j++)
			len += scnम_लिखो(buf + len, PATH_MAX - len, " %u",
					counter_val(stats, j));
		len += scnम_लिखो(buf + len, PATH_MAX - len, "\n");
	पूर्ण
	/* extra precision counters */
	क्रम_each_possible_cpu(i) अणु
		xs_xstrat_bytes += per_cpu_ptr(stats, i)->s.xs_xstrat_bytes;
		xs_ग_लिखो_bytes += per_cpu_ptr(stats, i)->s.xs_ग_लिखो_bytes;
		xs_पढ़ो_bytes += per_cpu_ptr(stats, i)->s.xs_पढ़ो_bytes;
		defer_relog += per_cpu_ptr(stats, i)->s.defer_relog;
	पूर्ण

	len += scnम_लिखो(buf + len, PATH_MAX-len, "xpc %Lu %Lu %Lu\n",
			xs_xstrat_bytes, xs_ग_लिखो_bytes, xs_पढ़ो_bytes);
	len += scnम_लिखो(buf + len, PATH_MAX-len, "defer_relog %llu\n",
			defer_relog);
	len += scnम_लिखो(buf + len, PATH_MAX-len, "debug %u\n",
#अगर defined(DEBUG)
		1);
#अन्यथा
		0);
#पूर्ण_अगर

	वापस len;
पूर्ण

व्योम xfs_stats_clearall(काष्ठा xfsstats __percpu *stats)
अणु
	पूर्णांक		c;
	uपूर्णांक32_t	vn_active;

	xfs_notice(शून्य, "Clearing xfsstats");
	क्रम_each_possible_cpu(c) अणु
		preempt_disable();
		/* save vn_active, it's a universal truth! */
		vn_active = per_cpu_ptr(stats, c)->s.vn_active;
		स_रखो(per_cpu_ptr(stats, c), 0, माप(*stats));
		per_cpu_ptr(stats, c)->s.vn_active = vn_active;
		preempt_enable();
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/* legacy quota पूर्णांकerfaces */
#अगर_घोषित CONFIG_XFS_QUOTA

#घोषणा XFSSTAT_START_XQMSTAT xfsstats_offset(xs_qm_dqreclaims)
#घोषणा XFSSTAT_END_XQMSTAT xfsstats_offset(xs_qm_dquot)

अटल पूर्णांक xqm_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	/* maximum; incore; ratio मुक्त to inuse; मुक्तlist */
	seq_म_लिखो(m, "%d\t%d\t%d\t%u\n",
		   0, counter_val(xfsstats.xs_stats, XFSSTAT_END_XQMSTAT),
		   0, counter_val(xfsstats.xs_stats, XFSSTAT_END_XQMSTAT + 1));
	वापस 0;
पूर्ण

/* legacy quota stats पूर्णांकerface no 2 */
अटल पूर्णांक xqmstat_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक j;

	seq_म_लिखो(m, "qm");
	क्रम (j = XFSSTAT_START_XQMSTAT; j < XFSSTAT_END_XQMSTAT; j++)
		seq_म_लिखो(m, " %u", counter_val(xfsstats.xs_stats, j));
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_XFS_QUOTA */

पूर्णांक
xfs_init_procfs(व्योम)
अणु
	अगर (!proc_सूची_गढ़ो("fs/xfs", शून्य))
		वापस -ENOMEM;

	अगर (!proc_symlink("fs/xfs/stat", शून्य,
			  "/sys/fs/xfs/stats/stats"))
		जाओ out;

#अगर_घोषित CONFIG_XFS_QUOTA
	अगर (!proc_create_single("fs/xfs/xqmstat", 0, शून्य, xqmstat_proc_show))
		जाओ out;
	अगर (!proc_create_single("fs/xfs/xqm", 0, शून्य, xqm_proc_show))
		जाओ out;
#पूर्ण_अगर
	वापस 0;

out:
	हटाओ_proc_subtree("fs/xfs", शून्य);
	वापस -ENOMEM;
पूर्ण

व्योम
xfs_cleanup_procfs(व्योम)
अणु
	हटाओ_proc_subtree("fs/xfs", शून्य);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

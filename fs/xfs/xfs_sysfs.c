<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Red Hat, Inc.
 * All Rights Reserved.
 */

#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sysfs.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_mount.h"

काष्ठा xfs_sysfs_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा kobject *kobject, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा kobject *kobject, स्थिर अक्षर *buf,
			 माप_प्रकार count);
पूर्ण;

अटल अंतरभूत काष्ठा xfs_sysfs_attr *
to_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा xfs_sysfs_attr, attr);
पूर्ण

#घोषणा XFS_SYSFS_ATTR_RW(name) \
	अटल काष्ठा xfs_sysfs_attr xfs_sysfs_attr_##name = __ATTR_RW(name)
#घोषणा XFS_SYSFS_ATTR_RO(name) \
	अटल काष्ठा xfs_sysfs_attr xfs_sysfs_attr_##name = __ATTR_RO(name)
#घोषणा XFS_SYSFS_ATTR_WO(name) \
	अटल काष्ठा xfs_sysfs_attr xfs_sysfs_attr_##name = __ATTR_WO(name)

#घोषणा ATTR_LIST(name) &xfs_sysfs_attr_##name.attr

STATIC sमाप_प्रकार
xfs_sysfs_object_show(
	काष्ठा kobject		*kobject,
	काष्ठा attribute	*attr,
	अक्षर			*buf)
अणु
	काष्ठा xfs_sysfs_attr *xfs_attr = to_attr(attr);

	वापस xfs_attr->show ? xfs_attr->show(kobject, buf) : 0;
पूर्ण

STATIC sमाप_प्रकार
xfs_sysfs_object_store(
	काष्ठा kobject		*kobject,
	काष्ठा attribute	*attr,
	स्थिर अक्षर		*buf,
	माप_प्रकार			count)
अणु
	काष्ठा xfs_sysfs_attr *xfs_attr = to_attr(attr);

	वापस xfs_attr->store ? xfs_attr->store(kobject, buf, count) : 0;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops xfs_sysfs_ops = अणु
	.show = xfs_sysfs_object_show,
	.store = xfs_sysfs_object_store,
पूर्ण;

अटल काष्ठा attribute *xfs_mp_attrs[] = अणु
	शून्य,
पूर्ण;

काष्ठा kobj_type xfs_mp_ktype = अणु
	.release = xfs_sysfs_release,
	.sysfs_ops = &xfs_sysfs_ops,
	.शेष_attrs = xfs_mp_attrs,
पूर्ण;

#अगर_घोषित DEBUG
/* debug */

STATIC sमाप_प्रकार
bug_on_निश्चित_store(
	काष्ठा kobject		*kobject,
	स्थिर अक्षर		*buf,
	माप_प्रकार			count)
अणु
	पूर्णांक			ret;
	पूर्णांक			val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val == 1)
		xfs_globals.bug_on_निश्चित = true;
	अन्यथा अगर (val == 0)
		xfs_globals.bug_on_निश्चित = false;
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

STATIC sमाप_प्रकार
bug_on_निश्चित_show(
	काष्ठा kobject		*kobject,
	अक्षर			*buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", xfs_globals.bug_on_निश्चित ? 1 : 0);
पूर्ण
XFS_SYSFS_ATTR_RW(bug_on_निश्चित);

STATIC sमाप_प्रकार
log_recovery_delay_store(
	काष्ठा kobject	*kobject,
	स्थिर अक्षर	*buf,
	माप_प्रकार		count)
अणु
	पूर्णांक		ret;
	पूर्णांक		val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val < 0 || val > 60)
		वापस -EINVAL;

	xfs_globals.log_recovery_delay = val;

	वापस count;
पूर्ण

STATIC sमाप_प्रकार
log_recovery_delay_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", xfs_globals.log_recovery_delay);
पूर्ण
XFS_SYSFS_ATTR_RW(log_recovery_delay);

STATIC sमाप_प्रकार
mount_delay_store(
	काष्ठा kobject	*kobject,
	स्थिर अक्षर	*buf,
	माप_प्रकार		count)
अणु
	पूर्णांक		ret;
	पूर्णांक		val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val < 0 || val > 60)
		वापस -EINVAL;

	xfs_globals.mount_delay = val;

	वापस count;
पूर्ण

STATIC sमाप_प्रकार
mount_delay_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", xfs_globals.mount_delay);
पूर्ण
XFS_SYSFS_ATTR_RW(mount_delay);

अटल sमाप_प्रकार
always_cow_store(
	काष्ठा kobject	*kobject,
	स्थिर अक्षर	*buf,
	माप_प्रकार		count)
अणु
	sमाप_प्रकार		ret;

	ret = kstrtobool(buf, &xfs_globals.always_cow);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार
always_cow_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", xfs_globals.always_cow);
पूर्ण
XFS_SYSFS_ATTR_RW(always_cow);

#अगर_घोषित DEBUG
/*
 * Override how many thपढ़ोs the parallel work queue is allowed to create.
 * This has to be a debug-only global (instead of an errortag) because one of
 * the मुख्य users of parallel workqueues is mount समय quotacheck.
 */
STATIC sमाप_प्रकार
pwork_thपढ़ोs_store(
	काष्ठा kobject	*kobject,
	स्थिर अक्षर	*buf,
	माप_प्रकार		count)
अणु
	पूर्णांक		ret;
	पूर्णांक		val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val < -1 || val > num_possible_cpus())
		वापस -EINVAL;

	xfs_globals.pwork_thपढ़ोs = val;

	वापस count;
पूर्ण

STATIC sमाप_प्रकार
pwork_thपढ़ोs_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", xfs_globals.pwork_thपढ़ोs);
पूर्ण
XFS_SYSFS_ATTR_RW(pwork_thपढ़ोs);
#पूर्ण_अगर /* DEBUG */

अटल काष्ठा attribute *xfs_dbg_attrs[] = अणु
	ATTR_LIST(bug_on_निश्चित),
	ATTR_LIST(log_recovery_delay),
	ATTR_LIST(mount_delay),
	ATTR_LIST(always_cow),
#अगर_घोषित DEBUG
	ATTR_LIST(pwork_thपढ़ोs),
#पूर्ण_अगर
	शून्य,
पूर्ण;

काष्ठा kobj_type xfs_dbg_ktype = अणु
	.release = xfs_sysfs_release,
	.sysfs_ops = &xfs_sysfs_ops,
	.शेष_attrs = xfs_dbg_attrs,
पूर्ण;

#पूर्ण_अगर /* DEBUG */

/* stats */

अटल अंतरभूत काष्ठा xstats *
to_xstats(काष्ठा kobject *kobject)
अणु
	काष्ठा xfs_kobj *kobj = to_kobj(kobject);

	वापस container_of(kobj, काष्ठा xstats, xs_kobj);
पूर्ण

STATIC sमाप_प्रकार
stats_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	काष्ठा xstats	*stats = to_xstats(kobject);

	वापस xfs_stats_क्रमmat(stats->xs_stats, buf);
पूर्ण
XFS_SYSFS_ATTR_RO(stats);

STATIC sमाप_प्रकार
stats_clear_store(
	काष्ठा kobject	*kobject,
	स्थिर अक्षर	*buf,
	माप_प्रकार		count)
अणु
	पूर्णांक		ret;
	पूर्णांक		val;
	काष्ठा xstats	*stats = to_xstats(kobject);

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val != 1)
		वापस -EINVAL;

	xfs_stats_clearall(stats->xs_stats);
	वापस count;
पूर्ण
XFS_SYSFS_ATTR_WO(stats_clear);

अटल काष्ठा attribute *xfs_stats_attrs[] = अणु
	ATTR_LIST(stats),
	ATTR_LIST(stats_clear),
	शून्य,
पूर्ण;

काष्ठा kobj_type xfs_stats_ktype = अणु
	.release = xfs_sysfs_release,
	.sysfs_ops = &xfs_sysfs_ops,
	.शेष_attrs = xfs_stats_attrs,
पूर्ण;

/* xlog */

अटल अंतरभूत काष्ठा xlog *
to_xlog(काष्ठा kobject *kobject)
अणु
	काष्ठा xfs_kobj *kobj = to_kobj(kobject);

	वापस container_of(kobj, काष्ठा xlog, l_kobj);
पूर्ण

STATIC sमाप_प्रकार
log_head_lsn_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	पूर्णांक cycle;
	पूर्णांक block;
	काष्ठा xlog *log = to_xlog(kobject);

	spin_lock(&log->l_icloglock);
	cycle = log->l_curr_cycle;
	block = log->l_curr_block;
	spin_unlock(&log->l_icloglock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d:%d\n", cycle, block);
पूर्ण
XFS_SYSFS_ATTR_RO(log_head_lsn);

STATIC sमाप_प्रकार
log_tail_lsn_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	पूर्णांक cycle;
	पूर्णांक block;
	काष्ठा xlog *log = to_xlog(kobject);

	xlog_crack_atomic_lsn(&log->l_tail_lsn, &cycle, &block);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d:%d\n", cycle, block);
पूर्ण
XFS_SYSFS_ATTR_RO(log_tail_lsn);

STATIC sमाप_प्रकार
reserve_grant_head_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)

अणु
	पूर्णांक cycle;
	पूर्णांक bytes;
	काष्ठा xlog *log = to_xlog(kobject);

	xlog_crack_grant_head(&log->l_reserve_head.grant, &cycle, &bytes);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d:%d\n", cycle, bytes);
पूर्ण
XFS_SYSFS_ATTR_RO(reserve_grant_head);

STATIC sमाप_प्रकार
ग_लिखो_grant_head_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	पूर्णांक cycle;
	पूर्णांक bytes;
	काष्ठा xlog *log = to_xlog(kobject);

	xlog_crack_grant_head(&log->l_ग_लिखो_head.grant, &cycle, &bytes);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d:%d\n", cycle, bytes);
पूर्ण
XFS_SYSFS_ATTR_RO(ग_लिखो_grant_head);

अटल काष्ठा attribute *xfs_log_attrs[] = अणु
	ATTR_LIST(log_head_lsn),
	ATTR_LIST(log_tail_lsn),
	ATTR_LIST(reserve_grant_head),
	ATTR_LIST(ग_लिखो_grant_head),
	शून्य,
पूर्ण;

काष्ठा kobj_type xfs_log_ktype = अणु
	.release = xfs_sysfs_release,
	.sysfs_ops = &xfs_sysfs_ops,
	.शेष_attrs = xfs_log_attrs,
पूर्ण;

/*
 * Metadata IO error configuration
 *
 * The sysfs काष्ठाure here is:
 *	...xfs/<dev>/error/<class>/<त्रुटि_सं>/<error_attrs>
 *
 * where <class> allows us to discriminate between data IO and metadata IO,
 * and any other future type of IO (e.g. special inode or directory error
 * handling) we care to support.
 */
अटल अंतरभूत काष्ठा xfs_error_cfg *
to_error_cfg(काष्ठा kobject *kobject)
अणु
	काष्ठा xfs_kobj *kobj = to_kobj(kobject);
	वापस container_of(kobj, काष्ठा xfs_error_cfg, kobj);
पूर्ण

अटल अंतरभूत काष्ठा xfs_mount *
err_to_mp(काष्ठा kobject *kobject)
अणु
	काष्ठा xfs_kobj *kobj = to_kobj(kobject);
	वापस container_of(kobj, काष्ठा xfs_mount, m_error_kobj);
पूर्ण

अटल sमाप_प्रकार
max_retries_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	पूर्णांक		retries;
	काष्ठा xfs_error_cfg *cfg = to_error_cfg(kobject);

	अगर (cfg->max_retries == XFS_ERR_RETRY_FOREVER)
		retries = -1;
	अन्यथा
		retries = cfg->max_retries;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", retries);
पूर्ण

अटल sमाप_प्रकार
max_retries_store(
	काष्ठा kobject	*kobject,
	स्थिर अक्षर	*buf,
	माप_प्रकार		count)
अणु
	काष्ठा xfs_error_cfg *cfg = to_error_cfg(kobject);
	पूर्णांक		ret;
	पूर्णांक		val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val < -1)
		वापस -EINVAL;

	अगर (val == -1)
		cfg->max_retries = XFS_ERR_RETRY_FOREVER;
	अन्यथा
		cfg->max_retries = val;
	वापस count;
पूर्ण
XFS_SYSFS_ATTR_RW(max_retries);

अटल sमाप_प्रकार
retry_समयout_seconds_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	पूर्णांक		समयout;
	काष्ठा xfs_error_cfg *cfg = to_error_cfg(kobject);

	अगर (cfg->retry_समयout == XFS_ERR_RETRY_FOREVER)
		समयout = -1;
	अन्यथा
		समयout = jअगरfies_to_msecs(cfg->retry_समयout) / MSEC_PER_SEC;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", समयout);
पूर्ण

अटल sमाप_प्रकार
retry_समयout_seconds_store(
	काष्ठा kobject	*kobject,
	स्थिर अक्षर	*buf,
	माप_प्रकार		count)
अणु
	काष्ठा xfs_error_cfg *cfg = to_error_cfg(kobject);
	पूर्णांक		ret;
	पूर्णांक		val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	/* 1 day समयout maximum, -1 means infinite */
	अगर (val < -1 || val > 86400)
		वापस -EINVAL;

	अगर (val == -1)
		cfg->retry_समयout = XFS_ERR_RETRY_FOREVER;
	अन्यथा अणु
		cfg->retry_समयout = msecs_to_jअगरfies(val * MSEC_PER_SEC);
		ASSERT(msecs_to_jअगरfies(val * MSEC_PER_SEC) < दीर्घ_उच्च);
	पूर्ण
	वापस count;
पूर्ण
XFS_SYSFS_ATTR_RW(retry_समयout_seconds);

अटल sमाप_प्रकार
fail_at_unmount_show(
	काष्ठा kobject	*kobject,
	अक्षर		*buf)
अणु
	काष्ठा xfs_mount	*mp = err_to_mp(kobject);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", mp->m_fail_unmount);
पूर्ण

अटल sमाप_प्रकार
fail_at_unmount_store(
	काष्ठा kobject	*kobject,
	स्थिर अक्षर	*buf,
	माप_प्रकार		count)
अणु
	काष्ठा xfs_mount	*mp = err_to_mp(kobject);
	पूर्णांक		ret;
	पूर्णांक		val;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val < 0 || val > 1)
		वापस -EINVAL;

	mp->m_fail_unmount = val;
	वापस count;
पूर्ण
XFS_SYSFS_ATTR_RW(fail_at_unmount);

अटल काष्ठा attribute *xfs_error_attrs[] = अणु
	ATTR_LIST(max_retries),
	ATTR_LIST(retry_समयout_seconds),
	शून्य,
पूर्ण;


अटल काष्ठा kobj_type xfs_error_cfg_ktype = अणु
	.release = xfs_sysfs_release,
	.sysfs_ops = &xfs_sysfs_ops,
	.शेष_attrs = xfs_error_attrs,
पूर्ण;

अटल काष्ठा kobj_type xfs_error_ktype = अणु
	.release = xfs_sysfs_release,
	.sysfs_ops = &xfs_sysfs_ops,
पूर्ण;

/*
 * Error initialization tables. These need to be ordered in the same
 * order as the क्रमागतs used to index the array. All class init tables need to
 * define a "default" behaviour as the first entry, all other entries can be
 * empty.
 */
काष्ठा xfs_error_init अणु
	अक्षर		*name;
	पूर्णांक		max_retries;
	पूर्णांक		retry_समयout;	/* in seconds */
पूर्ण;

अटल स्थिर काष्ठा xfs_error_init xfs_error_meta_init[XFS_ERR_ERRNO_MAX] = अणु
	अणु .name = "default",
	  .max_retries = XFS_ERR_RETRY_FOREVER,
	  .retry_समयout = XFS_ERR_RETRY_FOREVER,
	पूर्ण,
	अणु .name = "EIO",
	  .max_retries = XFS_ERR_RETRY_FOREVER,
	  .retry_समयout = XFS_ERR_RETRY_FOREVER,
	पूर्ण,
	अणु .name = "ENOSPC",
	  .max_retries = XFS_ERR_RETRY_FOREVER,
	  .retry_समयout = XFS_ERR_RETRY_FOREVER,
	पूर्ण,
	अणु .name = "ENODEV",
	  .max_retries = 0,	/* We can't recover from devices disappearing */
	  .retry_समयout = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक
xfs_error_sysfs_init_class(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			class,
	स्थिर अक्षर		*parent_name,
	काष्ठा xfs_kobj		*parent_kobj,
	स्थिर काष्ठा xfs_error_init init[])
अणु
	काष्ठा xfs_error_cfg	*cfg;
	पूर्णांक			error;
	पूर्णांक			i;

	ASSERT(class < XFS_ERR_CLASS_MAX);

	error = xfs_sysfs_init(parent_kobj, &xfs_error_ktype,
				&mp->m_error_kobj, parent_name);
	अगर (error)
		वापस error;

	क्रम (i = 0; i < XFS_ERR_ERRNO_MAX; i++) अणु
		cfg = &mp->m_error_cfg[class][i];
		error = xfs_sysfs_init(&cfg->kobj, &xfs_error_cfg_ktype,
					parent_kobj, init[i].name);
		अगर (error)
			जाओ out_error;

		cfg->max_retries = init[i].max_retries;
		अगर (init[i].retry_समयout == XFS_ERR_RETRY_FOREVER)
			cfg->retry_समयout = XFS_ERR_RETRY_FOREVER;
		अन्यथा
			cfg->retry_समयout = msecs_to_jअगरfies(
					init[i].retry_समयout * MSEC_PER_SEC);
	पूर्ण
	वापस 0;

out_error:
	/* unwind the entries that succeeded */
	क्रम (i--; i >= 0; i--) अणु
		cfg = &mp->m_error_cfg[class][i];
		xfs_sysfs_del(&cfg->kobj);
	पूर्ण
	xfs_sysfs_del(parent_kobj);
	वापस error;
पूर्ण

पूर्णांक
xfs_error_sysfs_init(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक			error;

	/* .../xfs/<dev>/error/ */
	error = xfs_sysfs_init(&mp->m_error_kobj, &xfs_error_ktype,
				&mp->m_kobj, "error");
	अगर (error)
		वापस error;

	error = sysfs_create_file(&mp->m_error_kobj.kobject,
				  ATTR_LIST(fail_at_unmount));

	अगर (error)
		जाओ out_error;

	/* .../xfs/<dev>/error/metadata/ */
	error = xfs_error_sysfs_init_class(mp, XFS_ERR_METADATA,
				"metadata", &mp->m_error_meta_kobj,
				xfs_error_meta_init);
	अगर (error)
		जाओ out_error;

	वापस 0;

out_error:
	xfs_sysfs_del(&mp->m_error_kobj);
	वापस error;
पूर्ण

व्योम
xfs_error_sysfs_del(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_error_cfg	*cfg;
	पूर्णांक			i, j;

	क्रम (i = 0; i < XFS_ERR_CLASS_MAX; i++) अणु
		क्रम (j = 0; j < XFS_ERR_ERRNO_MAX; j++) अणु
			cfg = &mp->m_error_cfg[i][j];

			xfs_sysfs_del(&cfg->kobj);
		पूर्ण
	पूर्ण
	xfs_sysfs_del(&mp->m_error_meta_kobj);
	xfs_sysfs_del(&mp->m_error_kobj);
पूर्ण

काष्ठा xfs_error_cfg *
xfs_error_get_cfg(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			error_class,
	पूर्णांक			error)
अणु
	काष्ठा xfs_error_cfg	*cfg;

	अगर (error < 0)
		error = -error;

	चयन (error) अणु
	हाल EIO:
		cfg = &mp->m_error_cfg[error_class][XFS_ERR_EIO];
		अवरोध;
	हाल ENOSPC:
		cfg = &mp->m_error_cfg[error_class][XFS_ERR_ENOSPC];
		अवरोध;
	हाल ENODEV:
		cfg = &mp->m_error_cfg[error_class][XFS_ERR_ENODEV];
		अवरोध;
	शेष:
		cfg = &mp->m_error_cfg[error_class][XFS_ERR_DEFAULT];
		अवरोध;
	पूर्ण

	वापस cfg;
पूर्ण

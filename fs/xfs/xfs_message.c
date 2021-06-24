<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011 Red Hat, Inc.  All Rights Reserved.
 */

#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_error.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"

/*
 * XFS logging functions
 */
अटल व्योम
__xfs_prपूर्णांकk(
	स्थिर अक्षर		*level,
	स्थिर काष्ठा xfs_mount	*mp,
	काष्ठा va_क्रमmat	*vaf)
अणु
	अगर (mp && mp->m_super) अणु
		prपूर्णांकk("%sXFS (%s): %pV\n", level, mp->m_super->s_id, vaf);
		वापस;
	पूर्ण
	prपूर्णांकk("%sXFS: %pV\n", level, vaf);
पूर्ण

#घोषणा define_xfs_prपूर्णांकk_level(func, kern_level)		\
व्योम func(स्थिर काष्ठा xfs_mount *mp, स्थिर अक्षर *fmt, ...)	\
अणु								\
	काष्ठा va_क्रमmat	vaf;				\
	बहु_सूची			args;				\
	पूर्णांक			level;				\
								\
	बहु_शुरू(args, fmt);					\
								\
	vaf.fmt = fmt;						\
	vaf.va = &args;						\
								\
	__xfs_prपूर्णांकk(kern_level, mp, &vaf);			\
	बहु_पूर्ण(args);						\
								\
	अगर (!kstrtoपूर्णांक(kern_level, 0, &level) &&		\
	    level <= LOGLEVEL_ERR &&				\
	    xfs_error_level >= XFS_ERRLEVEL_HIGH)		\
		xfs_stack_trace();				\
पूर्ण								\

define_xfs_prपूर्णांकk_level(xfs_emerg, KERN_EMERG);
define_xfs_prपूर्णांकk_level(xfs_alert, KERN_ALERT);
define_xfs_prपूर्णांकk_level(xfs_crit, KERN_CRIT);
define_xfs_prपूर्णांकk_level(xfs_err, KERN_ERR);
define_xfs_prपूर्णांकk_level(xfs_warn, KERN_WARNING);
define_xfs_prपूर्णांकk_level(xfs_notice, KERN_NOTICE);
define_xfs_prपूर्णांकk_level(xfs_info, KERN_INFO);
#अगर_घोषित DEBUG
define_xfs_prपूर्णांकk_level(xfs_debug, KERN_DEBUG);
#पूर्ण_अगर

व्योम
xfs_alert_tag(
	स्थिर काष्ठा xfs_mount	*mp,
	पूर्णांक			panic_tag,
	स्थिर अक्षर		*fmt, ...)
अणु
	काष्ठा va_क्रमmat	vaf;
	बहु_सूची			args;
	पूर्णांक			करो_panic = 0;

	अगर (xfs_panic_mask && (xfs_panic_mask & panic_tag)) अणु
		xfs_alert(mp, "Transforming an alert into a BUG.");
		करो_panic = 1;
	पूर्ण

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	__xfs_prपूर्णांकk(KERN_ALERT, mp, &vaf);
	बहु_पूर्ण(args);

	BUG_ON(करो_panic);
पूर्ण

व्योम
asswarn(
	काष्ठा xfs_mount	*mp,
	अक्षर			*expr,
	अक्षर			*file,
	पूर्णांक			line)
अणु
	xfs_warn(mp, "Assertion failed: %s, file: %s, line: %d",
		expr, file, line);
	WARN_ON(1);
पूर्ण

व्योम
assfail(
	काष्ठा xfs_mount	*mp,
	अक्षर			*expr,
	अक्षर			*file,
	पूर्णांक			line)
अणु
	xfs_emerg(mp, "Assertion failed: %s, file: %s, line: %d",
		expr, file, line);
	अगर (xfs_globals.bug_on_निश्चित)
		BUG();
	अन्यथा
		WARN_ON(1);
पूर्ण

व्योम
xfs_hex_dump(स्थिर व्योम *p, पूर्णांक length)
अणु
	prपूर्णांक_hex_dump(KERN_ALERT, "", DUMP_PREFIX_OFFSET, 16, 1, p, length, 1);
पूर्ण

व्योम
xfs_buf_alert_ratelimited(
	काष्ठा xfs_buf		*bp,
	स्थिर अक्षर		*rlmsg,
	स्थिर अक्षर		*fmt,
	...)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा va_क्रमmat	vaf;
	बहु_सूची			args;

	/* use the more aggressive per-target rate limit क्रम buffers */
	अगर (!___ratelimit(&bp->b_target->bt_ioerror_rl, rlmsg))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	__xfs_prपूर्णांकk(KERN_ALERT, mp, &vaf);
	बहु_पूर्ण(args);
पूर्ण

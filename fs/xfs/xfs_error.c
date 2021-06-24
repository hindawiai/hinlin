<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_sysfs.h"
#समावेश "xfs_inode.h"

#अगर_घोषित DEBUG

अटल अचिन्हित पूर्णांक xfs_errortag_अक्रमom_शेष[] = अणु
	XFS_RANDOM_DEFAULT,
	XFS_RANDOM_IFLUSH_1,
	XFS_RANDOM_IFLUSH_2,
	XFS_RANDOM_IFLUSH_3,
	XFS_RANDOM_IFLUSH_4,
	XFS_RANDOM_IFLUSH_5,
	XFS_RANDOM_IFLUSH_6,
	XFS_RANDOM_DA_READ_BUF,
	XFS_RANDOM_BTREE_CHECK_LBLOCK,
	XFS_RANDOM_BTREE_CHECK_SBLOCK,
	XFS_RANDOM_ALLOC_READ_AGF,
	XFS_RANDOM_IALLOC_READ_AGI,
	XFS_RANDOM_ITOBP_INOTOBP,
	XFS_RANDOM_IUNLINK,
	XFS_RANDOM_IUNLINK_REMOVE,
	XFS_RANDOM_सूची_INO_VALIDATE,
	XFS_RANDOM_BULKSTAT_READ_CHUNK,
	XFS_RANDOM_IODONE_IOERR,
	XFS_RANDOM_STRATREAD_IOERR,
	XFS_RANDOM_STRATCMPL_IOERR,
	XFS_RANDOM_DIOWRITE_IOERR,
	XFS_RANDOM_BMAPIFORMAT,
	XFS_RANDOM_FREE_EXTENT,
	XFS_RANDOM_RMAP_FINISH_ONE,
	XFS_RANDOM_REFCOUNT_CONTINUE_UPDATE,
	XFS_RANDOM_REFCOUNT_FINISH_ONE,
	XFS_RANDOM_BMAP_FINISH_ONE,
	XFS_RANDOM_AG_RESV_CRITICAL,
	XFS_RANDOM_DROP_WRITES,
	XFS_RANDOM_LOG_BAD_CRC,
	XFS_RANDOM_LOG_ITEM_PIN,
	XFS_RANDOM_BUF_LRU_REF,
	XFS_RANDOM_FORCE_SCRUB_REPAIR,
	XFS_RANDOM_FORCE_SUMMARY_RECALC,
	XFS_RANDOM_IUNLINK_FALLBACK,
	XFS_RANDOM_BUF_IOERROR,
	XFS_RANDOM_REDUCE_MAX_IEXTENTS,
	XFS_RANDOM_BMAP_ALLOC_MINLEN_EXTENT,
	XFS_RANDOM_AG_RESV_FAIL,
पूर्ण;

काष्ठा xfs_errortag_attr अणु
	काष्ठा attribute	attr;
	अचिन्हित पूर्णांक		tag;
पूर्ण;

अटल अंतरभूत काष्ठा xfs_errortag_attr *
to_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा xfs_errortag_attr, attr);
पूर्ण

अटल अंतरभूत काष्ठा xfs_mount *
to_mp(काष्ठा kobject *kobject)
अणु
	काष्ठा xfs_kobj *kobj = to_kobj(kobject);

	वापस container_of(kobj, काष्ठा xfs_mount, m_errortag_kobj);
पूर्ण

STATIC sमाप_प्रकार
xfs_errortag_attr_store(
	काष्ठा kobject		*kobject,
	काष्ठा attribute	*attr,
	स्थिर अक्षर		*buf,
	माप_प्रकार			count)
अणु
	काष्ठा xfs_mount	*mp = to_mp(kobject);
	काष्ठा xfs_errortag_attr *xfs_attr = to_attr(attr);
	पूर्णांक			ret;
	अचिन्हित पूर्णांक		val;

	अगर (म_भेद(buf, "default") == 0) अणु
		val = xfs_errortag_अक्रमom_शेष[xfs_attr->tag];
	पूर्ण अन्यथा अणु
		ret = kstrtouपूर्णांक(buf, 0, &val);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = xfs_errortag_set(mp, xfs_attr->tag, val);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

STATIC sमाप_प्रकार
xfs_errortag_attr_show(
	काष्ठा kobject		*kobject,
	काष्ठा attribute	*attr,
	अक्षर			*buf)
अणु
	काष्ठा xfs_mount	*mp = to_mp(kobject);
	काष्ठा xfs_errortag_attr *xfs_attr = to_attr(attr);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
			xfs_errortag_get(mp, xfs_attr->tag));
पूर्ण

अटल स्थिर काष्ठा sysfs_ops xfs_errortag_sysfs_ops = अणु
	.show = xfs_errortag_attr_show,
	.store = xfs_errortag_attr_store,
पूर्ण;

#घोषणा XFS_ERRORTAG_ATTR_RW(_name, _tag) \
अटल काष्ठा xfs_errortag_attr xfs_errortag_attr_##_name = अणु		\
	.attr = अणु.name = __stringअगरy(_name),				\
		 .mode = VERIFY_OCTAL_PERMISSIONS(S_IWUSR | S_IRUGO) पूर्ण,	\
	.tag	= (_tag),						\
पूर्ण

#घोषणा XFS_ERRORTAG_ATTR_LIST(_name) &xfs_errortag_attr_##_name.attr

XFS_ERRORTAG_ATTR_RW(noerror,		XFS_ERRTAG_NOERROR);
XFS_ERRORTAG_ATTR_RW(अगरlush1,		XFS_ERRTAG_IFLUSH_1);
XFS_ERRORTAG_ATTR_RW(अगरlush2,		XFS_ERRTAG_IFLUSH_2);
XFS_ERRORTAG_ATTR_RW(अगरlush3,		XFS_ERRTAG_IFLUSH_3);
XFS_ERRORTAG_ATTR_RW(अगरlush4,		XFS_ERRTAG_IFLUSH_4);
XFS_ERRORTAG_ATTR_RW(अगरlush5,		XFS_ERRTAG_IFLUSH_5);
XFS_ERRORTAG_ATTR_RW(अगरlush6,		XFS_ERRTAG_IFLUSH_6);
XFS_ERRORTAG_ATTR_RW(daपढ़ोbuf,		XFS_ERRTAG_DA_READ_BUF);
XFS_ERRORTAG_ATTR_RW(btree_chk_lblk,	XFS_ERRTAG_BTREE_CHECK_LBLOCK);
XFS_ERRORTAG_ATTR_RW(btree_chk_sblk,	XFS_ERRTAG_BTREE_CHECK_SBLOCK);
XFS_ERRORTAG_ATTR_RW(पढ़ोagf,		XFS_ERRTAG_ALLOC_READ_AGF);
XFS_ERRORTAG_ATTR_RW(पढ़ोagi,		XFS_ERRTAG_IALLOC_READ_AGI);
XFS_ERRORTAG_ATTR_RW(itobp,		XFS_ERRTAG_ITOBP_INOTOBP);
XFS_ERRORTAG_ATTR_RW(iunlink,		XFS_ERRTAG_IUNLINK);
XFS_ERRORTAG_ATTR_RW(iunlinkrm,		XFS_ERRTAG_IUNLINK_REMOVE);
XFS_ERRORTAG_ATTR_RW(dirinovalid,	XFS_ERRTAG_सूची_INO_VALIDATE);
XFS_ERRORTAG_ATTR_RW(bulkstat,		XFS_ERRTAG_BULKSTAT_READ_CHUNK);
XFS_ERRORTAG_ATTR_RW(logioकरोne,		XFS_ERRTAG_IODONE_IOERR);
XFS_ERRORTAG_ATTR_RW(stratपढ़ो,		XFS_ERRTAG_STRATREAD_IOERR);
XFS_ERRORTAG_ATTR_RW(stratcmpl,		XFS_ERRTAG_STRATCMPL_IOERR);
XFS_ERRORTAG_ATTR_RW(dioग_लिखो,		XFS_ERRTAG_DIOWRITE_IOERR);
XFS_ERRORTAG_ATTR_RW(bmapअगरmt,		XFS_ERRTAG_BMAPIFORMAT);
XFS_ERRORTAG_ATTR_RW(मुक्त_extent,	XFS_ERRTAG_FREE_EXTENT);
XFS_ERRORTAG_ATTR_RW(rmap_finish_one,	XFS_ERRTAG_RMAP_FINISH_ONE);
XFS_ERRORTAG_ATTR_RW(refcount_जारी_update,	XFS_ERRTAG_REFCOUNT_CONTINUE_UPDATE);
XFS_ERRORTAG_ATTR_RW(refcount_finish_one,	XFS_ERRTAG_REFCOUNT_FINISH_ONE);
XFS_ERRORTAG_ATTR_RW(bmap_finish_one,	XFS_ERRTAG_BMAP_FINISH_ONE);
XFS_ERRORTAG_ATTR_RW(ag_resv_critical,	XFS_ERRTAG_AG_RESV_CRITICAL);
XFS_ERRORTAG_ATTR_RW(drop_ग_लिखोs,	XFS_ERRTAG_DROP_WRITES);
XFS_ERRORTAG_ATTR_RW(log_bad_crc,	XFS_ERRTAG_LOG_BAD_CRC);
XFS_ERRORTAG_ATTR_RW(log_item_pin,	XFS_ERRTAG_LOG_ITEM_PIN);
XFS_ERRORTAG_ATTR_RW(buf_lru_ref,	XFS_ERRTAG_BUF_LRU_REF);
XFS_ERRORTAG_ATTR_RW(क्रमce_repair,	XFS_ERRTAG_FORCE_SCRUB_REPAIR);
XFS_ERRORTAG_ATTR_RW(bad_summary,	XFS_ERRTAG_FORCE_SUMMARY_RECALC);
XFS_ERRORTAG_ATTR_RW(iunlink_fallback,	XFS_ERRTAG_IUNLINK_FALLBACK);
XFS_ERRORTAG_ATTR_RW(buf_ioerror,	XFS_ERRTAG_BUF_IOERROR);
XFS_ERRORTAG_ATTR_RW(reduce_max_iextents,	XFS_ERRTAG_REDUCE_MAX_IEXTENTS);
XFS_ERRORTAG_ATTR_RW(bmap_alloc_minlen_extent,	XFS_ERRTAG_BMAP_ALLOC_MINLEN_EXTENT);
XFS_ERRORTAG_ATTR_RW(ag_resv_fail, XFS_ERRTAG_AG_RESV_FAIL);

अटल काष्ठा attribute *xfs_errortag_attrs[] = अणु
	XFS_ERRORTAG_ATTR_LIST(noerror),
	XFS_ERRORTAG_ATTR_LIST(अगरlush1),
	XFS_ERRORTAG_ATTR_LIST(अगरlush2),
	XFS_ERRORTAG_ATTR_LIST(अगरlush3),
	XFS_ERRORTAG_ATTR_LIST(अगरlush4),
	XFS_ERRORTAG_ATTR_LIST(अगरlush5),
	XFS_ERRORTAG_ATTR_LIST(अगरlush6),
	XFS_ERRORTAG_ATTR_LIST(daपढ़ोbuf),
	XFS_ERRORTAG_ATTR_LIST(btree_chk_lblk),
	XFS_ERRORTAG_ATTR_LIST(btree_chk_sblk),
	XFS_ERRORTAG_ATTR_LIST(पढ़ोagf),
	XFS_ERRORTAG_ATTR_LIST(पढ़ोagi),
	XFS_ERRORTAG_ATTR_LIST(itobp),
	XFS_ERRORTAG_ATTR_LIST(iunlink),
	XFS_ERRORTAG_ATTR_LIST(iunlinkrm),
	XFS_ERRORTAG_ATTR_LIST(dirinovalid),
	XFS_ERRORTAG_ATTR_LIST(bulkstat),
	XFS_ERRORTAG_ATTR_LIST(logioकरोne),
	XFS_ERRORTAG_ATTR_LIST(stratपढ़ो),
	XFS_ERRORTAG_ATTR_LIST(stratcmpl),
	XFS_ERRORTAG_ATTR_LIST(dioग_लिखो),
	XFS_ERRORTAG_ATTR_LIST(bmapअगरmt),
	XFS_ERRORTAG_ATTR_LIST(मुक्त_extent),
	XFS_ERRORTAG_ATTR_LIST(rmap_finish_one),
	XFS_ERRORTAG_ATTR_LIST(refcount_जारी_update),
	XFS_ERRORTAG_ATTR_LIST(refcount_finish_one),
	XFS_ERRORTAG_ATTR_LIST(bmap_finish_one),
	XFS_ERRORTAG_ATTR_LIST(ag_resv_critical),
	XFS_ERRORTAG_ATTR_LIST(drop_ग_लिखोs),
	XFS_ERRORTAG_ATTR_LIST(log_bad_crc),
	XFS_ERRORTAG_ATTR_LIST(log_item_pin),
	XFS_ERRORTAG_ATTR_LIST(buf_lru_ref),
	XFS_ERRORTAG_ATTR_LIST(क्रमce_repair),
	XFS_ERRORTAG_ATTR_LIST(bad_summary),
	XFS_ERRORTAG_ATTR_LIST(iunlink_fallback),
	XFS_ERRORTAG_ATTR_LIST(buf_ioerror),
	XFS_ERRORTAG_ATTR_LIST(reduce_max_iextents),
	XFS_ERRORTAG_ATTR_LIST(bmap_alloc_minlen_extent),
	XFS_ERRORTAG_ATTR_LIST(ag_resv_fail),
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type xfs_errortag_ktype = अणु
	.release = xfs_sysfs_release,
	.sysfs_ops = &xfs_errortag_sysfs_ops,
	.शेष_attrs = xfs_errortag_attrs,
पूर्ण;

पूर्णांक
xfs_errortag_init(
	काष्ठा xfs_mount	*mp)
अणु
	mp->m_errortag = kmem_zalloc(माप(अचिन्हित पूर्णांक) * XFS_ERRTAG_MAX,
			KM_MAYFAIL);
	अगर (!mp->m_errortag)
		वापस -ENOMEM;

	वापस xfs_sysfs_init(&mp->m_errortag_kobj, &xfs_errortag_ktype,
			       &mp->m_kobj, "errortag");
पूर्ण

व्योम
xfs_errortag_del(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_sysfs_del(&mp->m_errortag_kobj);
	kmem_मुक्त(mp->m_errortag);
पूर्ण

bool
xfs_errortag_test(
	काष्ठा xfs_mount	*mp,
	स्थिर अक्षर		*expression,
	स्थिर अक्षर		*file,
	पूर्णांक			line,
	अचिन्हित पूर्णांक		error_tag)
अणु
	अचिन्हित पूर्णांक		अक्रमfactor;

	/*
	 * To be able to use error injection anywhere, we need to ensure error
	 * injection mechanism is alपढ़ोy initialized.
	 *
	 * Code paths like I/O completion can be called beक्रमe the
	 * initialization is complete, but be able to inject errors in such
	 * places is still useful.
	 */
	अगर (!mp->m_errortag)
		वापस false;

	ASSERT(error_tag < XFS_ERRTAG_MAX);
	अक्रमfactor = mp->m_errortag[error_tag];
	अगर (!अक्रमfactor || pअक्रमom_u32() % अक्रमfactor)
		वापस false;

	xfs_warn_ratelimited(mp,
"Injecting error (%s) at file %s, line %d, on filesystem \"%s\"",
			expression, file, line, mp->m_super->s_id);
	वापस true;
पूर्ण

पूर्णांक
xfs_errortag_get(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		error_tag)
अणु
	अगर (error_tag >= XFS_ERRTAG_MAX)
		वापस -EINVAL;

	वापस mp->m_errortag[error_tag];
पूर्ण

पूर्णांक
xfs_errortag_set(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		error_tag,
	अचिन्हित पूर्णांक		tag_value)
अणु
	अगर (error_tag >= XFS_ERRTAG_MAX)
		वापस -EINVAL;

	mp->m_errortag[error_tag] = tag_value;
	वापस 0;
पूर्ण

पूर्णांक
xfs_errortag_add(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		error_tag)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(xfs_errortag_अक्रमom_शेष) != XFS_ERRTAG_MAX);

	अगर (error_tag >= XFS_ERRTAG_MAX)
		वापस -EINVAL;

	वापस xfs_errortag_set(mp, error_tag,
			xfs_errortag_अक्रमom_शेष[error_tag]);
पूर्ण

पूर्णांक
xfs_errortag_clearall(
	काष्ठा xfs_mount	*mp)
अणु
	स_रखो(mp->m_errortag, 0, माप(अचिन्हित पूर्णांक) * XFS_ERRTAG_MAX);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* DEBUG */

व्योम
xfs_error_report(
	स्थिर अक्षर		*tag,
	पूर्णांक			level,
	काष्ठा xfs_mount	*mp,
	स्थिर अक्षर		*filename,
	पूर्णांक			linक्रमागत,
	xfs_failaddr_t		failaddr)
अणु
	अगर (level <= xfs_error_level) अणु
		xfs_alert_tag(mp, XFS_PTAG_ERROR_REPORT,
		"Internal error %s at line %d of file %s.  Caller %pS",
			    tag, linक्रमागत, filename, failaddr);

		xfs_stack_trace();
	पूर्ण
पूर्ण

व्योम
xfs_corruption_error(
	स्थिर अक्षर		*tag,
	पूर्णांक			level,
	काष्ठा xfs_mount	*mp,
	स्थिर व्योम		*buf,
	माप_प्रकार			bufsize,
	स्थिर अक्षर		*filename,
	पूर्णांक			linक्रमागत,
	xfs_failaddr_t		failaddr)
अणु
	अगर (buf && level <= xfs_error_level)
		xfs_hex_dump(buf, bufsize);
	xfs_error_report(tag, level, mp, filename, linक्रमागत, failaddr);
	xfs_alert(mp, "Corruption detected. Unmount and run xfs_repair");
पूर्ण

/*
 * Complain about the kinds of metadata corruption that we can't detect from a
 * verअगरier, such as incorrect पूर्णांकer-block relationship data.  Does not set
 * bp->b_error.
 *
 * Call xfs_buf_mark_corrupt, not this function.
 */
व्योम
xfs_buf_corruption_error(
	काष्ठा xfs_buf		*bp,
	xfs_failaddr_t		fa)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;

	xfs_alert_tag(mp, XFS_PTAG_VERIFIER_ERROR,
		  "Metadata corruption detected at %pS, %s block 0x%llx",
		  fa, bp->b_ops->name, bp->b_bn);

	xfs_alert(mp, "Unmount and run xfs_repair");

	अगर (xfs_error_level >= XFS_ERRLEVEL_HIGH)
		xfs_stack_trace();
पूर्ण

/*
 * Warnings specअगरically क्रम verअगरier errors.  Dअगरferentiate CRC vs. invalid
 * values, and omit the stack trace unless the error level is tuned high.
 */
व्योम
xfs_buf_verअगरier_error(
	काष्ठा xfs_buf		*bp,
	पूर्णांक			error,
	स्थिर अक्षर		*name,
	स्थिर व्योम		*buf,
	माप_प्रकार			bufsz,
	xfs_failaddr_t		failaddr)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	xfs_failaddr_t		fa;
	पूर्णांक			sz;

	fa = failaddr ? failaddr : __वापस_address;
	__xfs_buf_ioerror(bp, error, fa);

	xfs_alert_tag(mp, XFS_PTAG_VERIFIER_ERROR,
		  "Metadata %s detected at %pS, %s block 0x%llx %s",
		  bp->b_error == -EFSBADCRC ? "CRC error" : "corruption",
		  fa, bp->b_ops->name, bp->b_bn, name);

	xfs_alert(mp, "Unmount and run xfs_repair");

	अगर (xfs_error_level >= XFS_ERRLEVEL_LOW) अणु
		sz = min_t(माप_प्रकार, XFS_CORRUPTION_DUMP_LEN, bufsz);
		xfs_alert(mp, "First %d bytes of corrupted metadata buffer:",
				sz);
		xfs_hex_dump(buf, sz);
	पूर्ण

	अगर (xfs_error_level >= XFS_ERRLEVEL_HIGH)
		xfs_stack_trace();
पूर्ण

/*
 * Warnings specअगरically क्रम verअगरier errors.  Dअगरferentiate CRC vs. invalid
 * values, and omit the stack trace unless the error level is tuned high.
 */
व्योम
xfs_verअगरier_error(
	काष्ठा xfs_buf		*bp,
	पूर्णांक			error,
	xfs_failaddr_t		failaddr)
अणु
	वापस xfs_buf_verअगरier_error(bp, error, "", xfs_buf_offset(bp, 0),
			XFS_CORRUPTION_DUMP_LEN, failaddr);
पूर्ण

/*
 * Warnings क्रम inode corruption problems.  Don't bother with the stack
 * trace unless the error level is turned up high.
 */
व्योम
xfs_inode_verअगरier_error(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			error,
	स्थिर अक्षर		*name,
	स्थिर व्योम		*buf,
	माप_प्रकार			bufsz,
	xfs_failaddr_t		failaddr)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_failaddr_t		fa;
	पूर्णांक			sz;

	fa = failaddr ? failaddr : __वापस_address;

	xfs_alert(mp, "Metadata %s detected at %pS, inode 0x%llx %s",
		  error == -EFSBADCRC ? "CRC error" : "corruption",
		  fa, ip->i_ino, name);

	xfs_alert(mp, "Unmount and run xfs_repair");

	अगर (buf && xfs_error_level >= XFS_ERRLEVEL_LOW) अणु
		sz = min_t(माप_प्रकार, XFS_CORRUPTION_DUMP_LEN, bufsz);
		xfs_alert(mp, "First %d bytes of corrupted metadata buffer:",
				sz);
		xfs_hex_dump(buf, sz);
	पूर्ण

	अगर (xfs_error_level >= XFS_ERRLEVEL_HIGH)
		xfs_stack_trace();
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_ERROR_H__
#घोषणा	__XFS_ERROR_H__

काष्ठा xfs_mount;

बाह्य व्योम xfs_error_report(स्थिर अक्षर *tag, पूर्णांक level, काष्ठा xfs_mount *mp,
			स्थिर अक्षर *filename, पूर्णांक linक्रमागत,
			xfs_failaddr_t failaddr);
बाह्य व्योम xfs_corruption_error(स्थिर अक्षर *tag, पूर्णांक level,
			काष्ठा xfs_mount *mp, स्थिर व्योम *buf, माप_प्रकार bufsize,
			स्थिर अक्षर *filename, पूर्णांक linक्रमागत,
			xfs_failaddr_t failaddr);
व्योम xfs_buf_corruption_error(काष्ठा xfs_buf *bp, xfs_failaddr_t fa);
बाह्य व्योम xfs_buf_verअगरier_error(काष्ठा xfs_buf *bp, पूर्णांक error,
			स्थिर अक्षर *name, स्थिर व्योम *buf, माप_प्रकार bufsz,
			xfs_failaddr_t failaddr);
बाह्य व्योम xfs_verअगरier_error(काष्ठा xfs_buf *bp, पूर्णांक error,
			xfs_failaddr_t failaddr);
बाह्य व्योम xfs_inode_verअगरier_error(काष्ठा xfs_inode *ip, पूर्णांक error,
			स्थिर अक्षर *name, स्थिर व्योम *buf, माप_प्रकार bufsz,
			xfs_failaddr_t failaddr);

#घोषणा	XFS_ERROR_REPORT(e, lvl, mp)	\
	xfs_error_report(e, lvl, mp, __खाता__, __LINE__, __वापस_address)
#घोषणा	XFS_CORRUPTION_ERROR(e, lvl, mp, buf, bufsize)	\
	xfs_corruption_error(e, lvl, mp, buf, bufsize, \
			     __खाता__, __LINE__, __वापस_address)

#घोषणा XFS_ERRLEVEL_OFF	0
#घोषणा XFS_ERRLEVEL_LOW	1
#घोषणा XFS_ERRLEVEL_HIGH	5

/* Dump 128 bytes of any corrupt buffer */
#घोषणा XFS_CORRUPTION_DUMP_LEN		(128)

#अगर_घोषित DEBUG
बाह्य पूर्णांक xfs_errortag_init(काष्ठा xfs_mount *mp);
बाह्य व्योम xfs_errortag_del(काष्ठा xfs_mount *mp);
बाह्य bool xfs_errortag_test(काष्ठा xfs_mount *mp, स्थिर अक्षर *expression,
		स्थिर अक्षर *file, पूर्णांक line, अचिन्हित पूर्णांक error_tag);
#घोषणा XFS_TEST_ERROR(expr, mp, tag)		\
	((expr) || xfs_errortag_test((mp), #expr, __खाता__, __LINE__, (tag)))

बाह्य पूर्णांक xfs_errortag_get(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक error_tag);
बाह्य पूर्णांक xfs_errortag_set(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक error_tag,
		अचिन्हित पूर्णांक tag_value);
बाह्य पूर्णांक xfs_errortag_add(काष्ठा xfs_mount *mp, अचिन्हित पूर्णांक error_tag);
बाह्य पूर्णांक xfs_errortag_clearall(काष्ठा xfs_mount *mp);
#अन्यथा
#घोषणा xfs_errortag_init(mp)			(0)
#घोषणा xfs_errortag_del(mp)
#घोषणा XFS_TEST_ERROR(expr, mp, tag)		(expr)
#घोषणा xfs_errortag_set(mp, tag, val)		(ENOSYS)
#घोषणा xfs_errortag_add(mp, tag)		(ENOSYS)
#घोषणा xfs_errortag_clearall(mp)		(ENOSYS)
#पूर्ण_अगर /* DEBUG */

/*
 * XFS panic tags -- allow a call to xfs_alert_tag() be turned पूर्णांकo
 *			a panic by setting xfs_panic_mask in a sysctl.
 */
#घोषणा		XFS_NO_PTAG			0
#घोषणा		XFS_PTAG_IFLUSH			0x00000001
#घोषणा		XFS_PTAG_LOGRES			0x00000002
#घोषणा		XFS_PTAG_AILDELETE		0x00000004
#घोषणा		XFS_PTAG_ERROR_REPORT		0x00000008
#घोषणा		XFS_PTAG_SHUTDOWN_CORRUPT	0x00000010
#घोषणा		XFS_PTAG_SHUTDOWN_IOERROR	0x00000020
#घोषणा		XFS_PTAG_SHUTDOWN_LOGERROR	0x00000040
#घोषणा		XFS_PTAG_FSBLOCK_ZERO		0x00000080
#घोषणा		XFS_PTAG_VERIFIER_ERROR		0x00000100

#पूर्ण_अगर	/* __XFS_ERROR_H__ */

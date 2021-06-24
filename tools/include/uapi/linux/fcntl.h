<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_FCNTL_H
#घोषणा _UAPI_LINUX_FCNTL_H

#समावेश <यंत्र/fcntl.h>
#समावेश <linux/खोलोat2.h>

#घोषणा F_SETLEASE	(F_LINUX_SPECIFIC_BASE + 0)
#घोषणा F_GETLEASE	(F_LINUX_SPECIFIC_BASE + 1)

/*
 * Cancel a blocking posix lock; पूर्णांकernal use only until we expose an
 * asynchronous lock api to userspace:
 */
#घोषणा F_CANCELLK	(F_LINUX_SPECIFIC_BASE + 5)

/* Create a file descriptor with FD_CLOEXEC set. */
#घोषणा F_DUPFD_CLOEXEC	(F_LINUX_SPECIFIC_BASE + 6)

/*
 * Request nofications on a directory.
 * See below क्रम events that may be notअगरied.
 */
#घोषणा F_NOTIFY	(F_LINUX_SPECIFIC_BASE+2)

/*
 * Set and get of pipe page size array
 */
#घोषणा F_SETPIPE_SZ	(F_LINUX_SPECIFIC_BASE + 7)
#घोषणा F_GETPIPE_SZ	(F_LINUX_SPECIFIC_BASE + 8)

/*
 * Set/Get seals
 */
#घोषणा F_ADD_SEALS	(F_LINUX_SPECIFIC_BASE + 9)
#घोषणा F_GET_SEALS	(F_LINUX_SPECIFIC_BASE + 10)

/*
 * Types of seals
 */
#घोषणा F_SEAL_SEAL	0x0001	/* prevent further seals from being set */
#घोषणा F_SEAL_SHRINK	0x0002	/* prevent file from shrinking */
#घोषणा F_SEAL_GROW	0x0004	/* prevent file from growing */
#घोषणा F_SEAL_WRITE	0x0008	/* prevent ग_लिखोs */
#घोषणा F_SEAL_FUTURE_WRITE	0x0010  /* prevent future ग_लिखोs जबतक mapped */
/* (1U << 31) is reserved क्रम चिन्हित error codes */

/*
 * Set/Get ग_लिखो lअगरe समय hपूर्णांकs. अणुGET,SETपूर्ण_RW_HINT operate on the
 * underlying inode, जबतक अणुGET,SETपूर्ण_खाता_RW_HINT operate only on
 * the specअगरic file.
 */
#घोषणा F_GET_RW_HINT		(F_LINUX_SPECIFIC_BASE + 11)
#घोषणा F_SET_RW_HINT		(F_LINUX_SPECIFIC_BASE + 12)
#घोषणा F_GET_खाता_RW_HINT	(F_LINUX_SPECIFIC_BASE + 13)
#घोषणा F_SET_खाता_RW_HINT	(F_LINUX_SPECIFIC_BASE + 14)

/*
 * Valid hपूर्णांक values क्रम F_अणुGET,SETपूर्ण_RW_HINT. 0 is "not set", or can be
 * used to clear any hपूर्णांकs previously set.
 */
#घोषणा RWH_WRITE_LIFE_NOT_SET	0
#घोषणा RWH_WRITE_LIFE_NONE	1
#घोषणा RWH_WRITE_LIFE_SHORT	2
#घोषणा RWH_WRITE_LIFE_MEDIUM	3
#घोषणा RWH_WRITE_LIFE_LONG	4
#घोषणा RWH_WRITE_LIFE_EXTREME	5

/*
 * The originally पूर्णांकroduced spelling is reमुख्यed from the first
 * versions of the patch set that पूर्णांकroduced the feature, see commit
 * v4.13-rc1~212^2~51.
 */
#घोषणा RWF_WRITE_LIFE_NOT_SET	RWH_WRITE_LIFE_NOT_SET

/*
 * Types of directory notअगरications that may be requested.
 */
#घोषणा DN_ACCESS	0x00000001	/* File accessed */
#घोषणा DN_MODIFY	0x00000002	/* File modअगरied */
#घोषणा DN_CREATE	0x00000004	/* File created */
#घोषणा DN_DELETE	0x00000008	/* File हटाओd */
#घोषणा DN_RENAME	0x00000010	/* File नामd */
#घोषणा DN_ATTRIB	0x00000020	/* File changed attibutes */
#घोषणा DN_MULTISHOT	0x80000000	/* Don't हटाओ notअगरier */

/*
 * The स्थिरants AT_REMOVEसूची and AT_EACCESS have the same value.  AT_EACCESS is
 * meaningful only to faccessat, जबतक AT_REMOVEसूची is meaningful only to
 * unlinkat.  The two functions करो completely dअगरferent things and thereक्रमe,
 * the flags can be allowed to overlap.  For example, passing AT_REMOVEसूची to
 * faccessat would be undefined behavior and thus treating it equivalent to
 * AT_EACCESS is valid undefined behavior.
 */
#घोषणा AT_FDCWD		-100    /* Special value used to indicate
                                           खोलोat should use the current
                                           working directory. */
#घोषणा AT_SYMLINK_NOFOLLOW	0x100   /* Do not follow symbolic links.  */
#घोषणा AT_EACCESS		0x200	/* Test access permitted क्रम
                                           effective IDs, not real IDs.  */
#घोषणा AT_REMOVEसूची		0x200   /* Remove directory instead of
                                           unlinking file.  */
#घोषणा AT_SYMLINK_FOLLOW	0x400   /* Follow symbolic links.  */
#घोषणा AT_NO_AUTOMOUNT		0x800	/* Suppress terminal स्वतःmount traversal */
#घोषणा AT_EMPTY_PATH		0x1000	/* Allow empty relative pathname */

#घोषणा AT_STATX_SYNC_TYPE	0x6000	/* Type of synchronisation required from statx() */
#घोषणा AT_STATX_SYNC_AS_STAT	0x0000	/* - Do whatever stat() करोes */
#घोषणा AT_STATX_FORCE_SYNC	0x2000	/* - Force the attributes to be sync'd with the server */
#घोषणा AT_STATX_DONT_SYNC	0x4000	/* - Don't sync attributes with the server */

#घोषणा AT_RECURSIVE		0x8000	/* Apply to the entire subtree */

#पूर्ण_अगर /* _UAPI_LINUX_FCNTL_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ALPHA_FCNTL_H
#घोषणा _ALPHA_FCNTL_H

#घोषणा O_CREAT		 01000	/* not fcntl */
#घोषणा O_TRUNC		 02000	/* not fcntl */
#घोषणा O_EXCL		 04000	/* not fcntl */
#घोषणा O_NOCTTY	010000	/* not fcntl */

#घोषणा O_NONBLOCK	 00004
#घोषणा O_APPEND	 00010
#घोषणा O_DSYNC		040000	/* used to be O_SYNC, see below */
#घोषणा O_सूचीECTORY	0100000	/* must be a directory */
#घोषणा O_NOFOLLOW	0200000 /* करोn't follow links */
#घोषणा O_LARGEखाता	0400000 /* will be set by the kernel on every खोलो */
#घोषणा O_सूचीECT	02000000 /* direct disk access - should check with OSF/1 */
#घोषणा O_NOATIME	04000000
#घोषणा O_CLOEXEC	010000000 /* set बंद_on_exec */
/*
 * Beक्रमe Linux 2.6.33 only O_DSYNC semantics were implemented, but using
 * the O_SYNC flag.  We जारी to use the existing numerical value
 * क्रम O_DSYNC semantics now, but using the correct symbolic name क्रम it.
 * This new value is used to request true Posix O_SYNC semantics.  It is
 * defined in this strange way to make sure applications compiled against
 * new headers get at least O_DSYNC semantics on older kernels.
 *
 * This has the nice side-effect that we can simply test क्रम O_DSYNC
 * wherever we करो not care अगर O_DSYNC or O_SYNC is used.
 *
 * Note: __O_SYNC must never be used directly.
 */
#घोषणा __O_SYNC	020000000
#घोषणा O_SYNC		(__O_SYNC|O_DSYNC)

#घोषणा O_PATH		040000000
#घोषणा __O_TMPखाता	0100000000

#घोषणा F_GETLK		7
#घोषणा F_SETLK		8
#घोषणा F_SETLKW	9

#घोषणा F_SETOWN	5	/*  क्रम sockets. */
#घोषणा F_GETOWN	6	/*  क्रम sockets. */
#घोषणा F_SETSIG	10	/*  क्रम sockets. */
#घोषणा F_GETSIG	11	/*  क्रम sockets. */

/* क्रम posix fcntl() and lockf() */
#घोषणा F_RDLCK		1
#घोषणा F_WRLCK		2
#घोषणा F_UNLCK		8

/* क्रम old implementation of bsd flock () */
#घोषणा F_EXLCK		16	/* or 3 */
#घोषणा F_SHLCK		32	/* or 4 */

#समावेश <यंत्र-generic/fcntl.h>

#पूर्ण_अगर

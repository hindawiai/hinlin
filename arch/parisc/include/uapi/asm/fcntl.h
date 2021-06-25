<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _PARISC_FCNTL_H
#घोषणा _PARISC_FCNTL_H

#घोषणा O_APPEND	000000010
#घोषणा O_CREAT		000000400 /* not fcntl */
#घोषणा O_EXCL		000002000 /* not fcntl */
#घोषणा O_LARGEखाता	000004000
#घोषणा __O_SYNC	000100000
#घोषणा O_SYNC		(__O_SYNC|O_DSYNC)
#घोषणा O_NONBLOCK	000200000
#घोषणा O_NOCTTY	000400000 /* not fcntl */
#घोषणा O_DSYNC		001000000
#घोषणा O_NOATIME	004000000
#घोषणा O_CLOEXEC	010000000 /* set बंद_on_exec */

#घोषणा O_सूचीECTORY	000010000 /* must be a directory */
#घोषणा O_NOFOLLOW	000000200 /* करोn't follow links */

#घोषणा O_PATH		020000000
#घोषणा __O_TMPखाता	040000000

#घोषणा F_GETLK64	8
#घोषणा F_SETLK64	9
#घोषणा F_SETLKW64	10

#घोषणा F_GETOWN	11	/*  क्रम sockets. */
#घोषणा F_SETOWN	12	/*  क्रम sockets. */
#घोषणा F_SETSIG	13	/*  क्रम sockets. */
#घोषणा F_GETSIG	14	/*  क्रम sockets. */

/* क्रम posix fcntl() and lockf() */
#घोषणा F_RDLCK		01
#घोषणा F_WRLCK		02
#घोषणा F_UNLCK		03

#समावेश <यंत्र-generic/fcntl.h>

#पूर्ण_अगर

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _SPARC_FCNTL_H
#घोषणा _SPARC_FCNTL_H

#घोषणा O_APPEND	0x0008
#घोषणा FASYNC		0x0040	/* fcntl, क्रम BSD compatibility */
#घोषणा O_CREAT		0x0200	/* not fcntl */
#घोषणा O_TRUNC		0x0400	/* not fcntl */
#घोषणा O_EXCL		0x0800	/* not fcntl */
#घोषणा O_DSYNC		0x2000	/* used to be O_SYNC, see below */
#घोषणा O_NONBLOCK	0x4000
#अगर defined(__sparc__) && defined(__arch64__)
#घोषणा O_NDELAY	0x0004
#अन्यथा
#घोषणा O_NDELAY	(0x0004 | O_NONBLOCK)
#पूर्ण_अगर
#घोषणा O_NOCTTY	0x8000	/* not fcntl */
#घोषणा O_LARGEखाता	0x40000
#घोषणा O_सूचीECT        0x100000 /* direct disk access hपूर्णांक */
#घोषणा O_NOATIME	0x200000
#घोषणा O_CLOEXEC	0x400000
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
#घोषणा __O_SYNC	0x800000
#घोषणा O_SYNC		(__O_SYNC|O_DSYNC)

#घोषणा O_PATH		0x1000000
#घोषणा __O_TMPखाता	0x2000000

#घोषणा F_GETOWN	5	/*  क्रम sockets. */
#घोषणा F_SETOWN	6	/*  क्रम sockets. */
#घोषणा F_GETLK		7
#घोषणा F_SETLK		8
#घोषणा F_SETLKW	9

/* क्रम posix fcntl() and lockf() */
#घोषणा F_RDLCK		1
#घोषणा F_WRLCK		2
#घोषणा F_UNLCK		3

#घोषणा __ARCH_FLOCK_PAD	लघु __unused;
#घोषणा __ARCH_FLOCK64_PAD	लघु __unused;

#समावेश <यंत्र-generic/fcntl.h>

#पूर्ण_अगर

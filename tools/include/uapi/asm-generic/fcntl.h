<शैली गुरु>
#अगर_अघोषित _ASM_GENERIC_FCNTL_H
#घोषणा _ASM_GENERIC_FCNTL_H

#समावेश <linux/types.h>

/*
 * FMODE_EXEC is 0x20
 * FMODE_NONOTIFY is 0x4000000
 * These cannot be used by userspace O_* until पूर्णांकernal and बाह्यal खोलो
 * flags are split.
 * -Eric Paris
 */

/*
 * When पूर्णांकroducing new O_* bits, please check its uniqueness in fcntl_init().
 */

#घोषणा O_ACCMODE	00000003
#घोषणा O_RDONLY	00000000
#घोषणा O_WRONLY	00000001
#घोषणा O_RDWR		00000002
#अगर_अघोषित O_CREAT
#घोषणा O_CREAT		00000100	/* not fcntl */
#पूर्ण_अगर
#अगर_अघोषित O_EXCL
#घोषणा O_EXCL		00000200	/* not fcntl */
#पूर्ण_अगर
#अगर_अघोषित O_NOCTTY
#घोषणा O_NOCTTY	00000400	/* not fcntl */
#पूर्ण_अगर
#अगर_अघोषित O_TRUNC
#घोषणा O_TRUNC		00001000	/* not fcntl */
#पूर्ण_अगर
#अगर_अघोषित O_APPEND
#घोषणा O_APPEND	00002000
#पूर्ण_अगर
#अगर_अघोषित O_NONBLOCK
#घोषणा O_NONBLOCK	00004000
#पूर्ण_अगर
#अगर_अघोषित O_DSYNC
#घोषणा O_DSYNC		00010000	/* used to be O_SYNC, see below */
#पूर्ण_अगर
#अगर_अघोषित FASYNC
#घोषणा FASYNC		00020000	/* fcntl, क्रम BSD compatibility */
#पूर्ण_अगर
#अगर_अघोषित O_सूचीECT
#घोषणा O_सूचीECT	00040000	/* direct disk access hपूर्णांक */
#पूर्ण_अगर
#अगर_अघोषित O_LARGEखाता
#घोषणा O_LARGEखाता	00100000
#पूर्ण_अगर
#अगर_अघोषित O_सूचीECTORY
#घोषणा O_सूचीECTORY	00200000	/* must be a directory */
#पूर्ण_अगर
#अगर_अघोषित O_NOFOLLOW
#घोषणा O_NOFOLLOW	00400000	/* करोn't follow links */
#पूर्ण_अगर
#अगर_अघोषित O_NOATIME
#घोषणा O_NOATIME	01000000
#पूर्ण_अगर
#अगर_अघोषित O_CLOEXEC
#घोषणा O_CLOEXEC	02000000	/* set बंद_on_exec */
#पूर्ण_अगर

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
#अगर_अघोषित O_SYNC
#घोषणा __O_SYNC	04000000
#घोषणा O_SYNC		(__O_SYNC|O_DSYNC)
#पूर्ण_अगर

#अगर_अघोषित O_PATH
#घोषणा O_PATH		010000000
#पूर्ण_अगर

#अगर_अघोषित __O_TMPखाता
#घोषणा __O_TMPखाता	020000000
#पूर्ण_अगर

/* a horrid kludge trying to make sure that this will fail on old kernels */
#घोषणा O_TMPखाता (__O_TMPखाता | O_सूचीECTORY)
#घोषणा O_TMPखाता_MASK (__O_TMPखाता | O_सूचीECTORY | O_CREAT)

#अगर_अघोषित O_NDELAY
#घोषणा O_NDELAY	O_NONBLOCK
#पूर्ण_अगर

#घोषणा F_DUPFD		0	/* dup */
#घोषणा F_GETFD		1	/* get बंद_on_exec */
#घोषणा F_SETFD		2	/* set/clear बंद_on_exec */
#घोषणा F_GETFL		3	/* get file->f_flags */
#घोषणा F_SETFL		4	/* set file->f_flags */
#अगर_अघोषित F_GETLK
#घोषणा F_GETLK		5
#घोषणा F_SETLK		6
#घोषणा F_SETLKW	7
#पूर्ण_अगर
#अगर_अघोषित F_SETOWN
#घोषणा F_SETOWN	8	/* क्रम sockets. */
#घोषणा F_GETOWN	9	/* क्रम sockets. */
#पूर्ण_अगर
#अगर_अघोषित F_SETSIG
#घोषणा F_SETSIG	10	/* क्रम sockets. */
#घोषणा F_GETSIG	11	/* क्रम sockets. */
#पूर्ण_अगर

#अगर_अघोषित CONFIG_64BIT
#अगर_अघोषित F_GETLK64
#घोषणा F_GETLK64	12	/*  using 'struct flock64' */
#घोषणा F_SETLK64	13
#घोषणा F_SETLKW64	14
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित F_SETOWN_EX
#घोषणा F_SETOWN_EX	15
#घोषणा F_GETOWN_EX	16
#पूर्ण_अगर

#अगर_अघोषित F_GETOWNER_UIDS
#घोषणा F_GETOWNER_UIDS	17
#पूर्ण_अगर

/*
 * Open File Description Locks
 *
 * Usually record locks held by a process are released on *any* बंद and are
 * not inherited across a विभाजन().
 *
 * These cmd values will set locks that conflict with process-associated
 * record  locks, but are "owned" by the खोलो file description, not the
 * process. This means that they are inherited across विभाजन() like BSD (flock)
 * locks, and they are only released स्वतःmatically when the last reference to
 * the the खोलो file against which they were acquired is put.
 */
#घोषणा F_OFD_GETLK	36
#घोषणा F_OFD_SETLK	37
#घोषणा F_OFD_SETLKW	38

#घोषणा F_OWNER_TID	0
#घोषणा F_OWNER_PID	1
#घोषणा F_OWNER_PGRP	2

काष्ठा f_owner_ex अणु
	पूर्णांक	type;
	__kernel_pid_t	pid;
पूर्ण;

/* क्रम F_[GET|SET]FL */
#घोषणा FD_CLOEXEC	1	/* actually anything with low bit set goes */

/* क्रम posix fcntl() and lockf() */
#अगर_अघोषित F_RDLCK
#घोषणा F_RDLCK		0
#घोषणा F_WRLCK		1
#घोषणा F_UNLCK		2
#पूर्ण_अगर

/* क्रम old implementation of bsd flock () */
#अगर_अघोषित F_EXLCK
#घोषणा F_EXLCK		4	/* or 3 */
#घोषणा F_SHLCK		8	/* or 4 */
#पूर्ण_अगर

/* operations क्रम bsd flock(), also used by the kernel implementation */
#घोषणा LOCK_SH		1	/* shared lock */
#घोषणा LOCK_EX		2	/* exclusive lock */
#घोषणा LOCK_NB		4	/* or'd with one of the above to prevent
				   blocking */
#घोषणा LOCK_UN		8	/* हटाओ lock */

#घोषणा LOCK_MAND	32	/* This is a mandatory flock ... */
#घोषणा LOCK_READ	64	/* which allows concurrent पढ़ो operations */
#घोषणा LOCK_WRITE	128	/* which allows concurrent ग_लिखो operations */
#घोषणा LOCK_RW		192	/* which allows concurrent पढ़ो & ग_लिखो ops */

#घोषणा F_LINUX_SPECIFIC_BASE	1024

#अगर_अघोषित HAVE_ARCH_STRUCT_FLOCK
#अगर_अघोषित __ARCH_FLOCK_PAD
#घोषणा __ARCH_FLOCK_PAD
#पूर्ण_अगर

काष्ठा flock अणु
	लघु	l_type;
	लघु	l_whence;
	__kernel_off_t	l_start;
	__kernel_off_t	l_len;
	__kernel_pid_t	l_pid;
	__ARCH_FLOCK_PAD
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित HAVE_ARCH_STRUCT_FLOCK64
#अगर_अघोषित __ARCH_FLOCK64_PAD
#घोषणा __ARCH_FLOCK64_PAD
#पूर्ण_अगर

काष्ठा flock64 अणु
	लघु  l_type;
	लघु  l_whence;
	__kernel_loff_t l_start;
	__kernel_loff_t l_len;
	__kernel_pid_t  l_pid;
	__ARCH_FLOCK64_PAD
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_FCNTL_H */

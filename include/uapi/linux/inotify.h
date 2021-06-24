<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Inode based directory notअगरication क्रम Linux
 *
 * Copyright (C) 2005 John McCutchan
 */

#अगर_अघोषित _UAPI_LINUX_INOTIFY_H
#घोषणा _UAPI_LINUX_INOTIFY_H

/* For O_CLOEXEC and O_NONBLOCK */
#समावेश <linux/fcntl.h>
#समावेश <linux/types.h>

/*
 * काष्ठा inotअगरy_event - काष्ठाure पढ़ो from the inotअगरy device क्रम each event
 *
 * When you are watching a directory, you will receive the filename क्रम events
 * such as IN_CREATE, IN_DELETE, IN_OPEN, IN_CLOSE, ..., relative to the wd.
 */
काष्ठा inotअगरy_event अणु
	__s32		wd;		/* watch descriptor */
	__u32		mask;		/* watch mask */
	__u32		cookie;		/* cookie to synchronize two events */
	__u32		len;		/* length (including nulls) of name */
	अक्षर		name[0];	/* stub क्रम possible name */
पूर्ण;

/* the following are legal, implemented events that user-space can watch क्रम */
#घोषणा IN_ACCESS		0x00000001	/* File was accessed */
#घोषणा IN_MODIFY		0x00000002	/* File was modअगरied */
#घोषणा IN_ATTRIB		0x00000004	/* Metadata changed */
#घोषणा IN_CLOSE_WRITE		0x00000008	/* Writtable file was बंदd */
#घोषणा IN_CLOSE_NOWRITE	0x00000010	/* Unwrittable file बंदd */
#घोषणा IN_OPEN			0x00000020	/* File was खोलोed */
#घोषणा IN_MOVED_FROM		0x00000040	/* File was moved from X */
#घोषणा IN_MOVED_TO		0x00000080	/* File was moved to Y */
#घोषणा IN_CREATE		0x00000100	/* Subfile was created */
#घोषणा IN_DELETE		0x00000200	/* Subfile was deleted */
#घोषणा IN_DELETE_SELF		0x00000400	/* Self was deleted */
#घोषणा IN_MOVE_SELF		0x00000800	/* Self was moved */

/* the following are legal events.  they are sent as needed to any watch */
#घोषणा IN_UNMOUNT		0x00002000	/* Backing fs was unmounted */
#घोषणा IN_Q_OVERFLOW		0x00004000	/* Event queued overflowed */
#घोषणा IN_IGNORED		0x00008000	/* File was ignored */

/* helper events */
#घोषणा IN_CLOSE		(IN_CLOSE_WRITE | IN_CLOSE_NOWRITE) /* बंद */
#घोषणा IN_MOVE			(IN_MOVED_FROM | IN_MOVED_TO) /* moves */

/* special flags */
#घोषणा IN_ONLYसूची		0x01000000	/* only watch the path अगर it is a directory */
#घोषणा IN_DONT_FOLLOW		0x02000000	/* करोn't follow a sym link */
#घोषणा IN_EXCL_UNLINK		0x04000000	/* exclude events on unlinked objects */
#घोषणा IN_MASK_CREATE		0x10000000	/* only create watches */
#घोषणा IN_MASK_ADD		0x20000000	/* add to the mask of an alपढ़ोy existing watch */
#घोषणा IN_ISसूची		0x40000000	/* event occurred against dir */
#घोषणा IN_ONESHOT		0x80000000	/* only send event once */

/*
 * All of the events - we build the list by hand so that we can add flags in
 * the future and not अवरोध backward compatibility.  Apps will get only the
 * events that they originally wanted.  Be sure to add new events here!
 */
#घोषणा IN_ALL_EVENTS	(IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | \
			 IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM | \
			 IN_MOVED_TO | IN_DELETE | IN_CREATE | IN_DELETE_SELF | \
			 IN_MOVE_SELF)

/* Flags क्रम sys_inotअगरy_init1.  */
#घोषणा IN_CLOEXEC O_CLOEXEC
#घोषणा IN_NONBLOCK O_NONBLOCK

/*
 * ioctl numbers: inotअगरy uses 'I' prefix क्रम all ioctls,
 * except historical FIONREAD, which is based on 'T'.
 *
 * INOTIFY_IOC_SETNEXTWD: set desired number of next created
 * watch descriptor.
 */
#घोषणा INOTIFY_IOC_SETNEXTWD	_IOW('I', 0, __s32)

#पूर्ण_अगर /* _UAPI_LINUX_INOTIFY_H */

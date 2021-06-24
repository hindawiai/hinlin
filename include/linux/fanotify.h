<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FANOTIFY_H
#घोषणा _LINUX_FANOTIFY_H

#समावेश <linux/sysctl.h>
#समावेश <uapi/linux/fanotअगरy.h>

बाह्य काष्ठा ctl_table fanotअगरy_table[]; /* क्रम sysctl */

#घोषणा FAN_GROUP_FLAG(group, flag) \
	((group)->fanotअगरy_data.flags & (flag))

/*
 * Flags allowed to be passed from/to userspace.
 *
 * We पूर्णांकentionally करो not add new bits to the old FAN_ALL_* स्थिरants, because
 * they are uapi exposed स्थिरants. If there are programs out there using
 * these स्थिरant, the programs may अवरोध अगर re-compiled with new uapi headers
 * and then run on an old kernel.
 */

/* Group classes where permission events are allowed */
#घोषणा FANOTIFY_PERM_CLASSES	(FAN_CLASS_CONTENT | \
				 FAN_CLASS_PRE_CONTENT)

#घोषणा FANOTIFY_CLASS_BITS	(FAN_CLASS_NOTIF | FANOTIFY_PERM_CLASSES)

#घोषणा FANOTIFY_FID_BITS	(FAN_REPORT_FID | FAN_REPORT_DFID_NAME)

/*
 * fanotअगरy_init() flags that require CAP_SYS_ADMIN.
 * We करो not allow unprivileged groups to request permission events.
 * We करो not allow unprivileged groups to get other process pid in events.
 * We करो not allow unprivileged groups to use unlimited resources.
 */
#घोषणा FANOTIFY_ADMIN_INIT_FLAGS	(FANOTIFY_PERM_CLASSES | \
					 FAN_REPORT_TID | \
					 FAN_UNLIMITED_QUEUE | \
					 FAN_UNLIMITED_MARKS)

/*
 * fanotअगरy_init() flags that are allowed क्रम user without CAP_SYS_ADMIN.
 * FAN_CLASS_NOTIF is the only class we allow क्रम unprivileged group.
 * We करो not allow unprivileged groups to get file descriptors in events,
 * so one of the flags क्रम reporting file handles is required.
 */
#घोषणा FANOTIFY_USER_INIT_FLAGS	(FAN_CLASS_NOTIF | \
					 FANOTIFY_FID_BITS | \
					 FAN_CLOEXEC | FAN_NONBLOCK)

#घोषणा FANOTIFY_INIT_FLAGS	(FANOTIFY_ADMIN_INIT_FLAGS | \
				 FANOTIFY_USER_INIT_FLAGS)

/* Internal group flags */
#घोषणा FANOTIFY_UNPRIV		0x80000000
#घोषणा FANOTIFY_INTERNAL_GROUP_FLAGS	(FANOTIFY_UNPRIV)

#घोषणा FANOTIFY_MARK_TYPE_BITS	(FAN_MARK_INODE | FAN_MARK_MOUNT | \
				 FAN_MARK_खाताSYSTEM)

#घोषणा FANOTIFY_MARK_FLAGS	(FANOTIFY_MARK_TYPE_BITS | \
				 FAN_MARK_ADD | \
				 FAN_MARK_REMOVE | \
				 FAN_MARK_DONT_FOLLOW | \
				 FAN_MARK_ONLYसूची | \
				 FAN_MARK_IGNORED_MASK | \
				 FAN_MARK_IGNORED_SURV_MODIFY | \
				 FAN_MARK_FLUSH)

/*
 * Events that can be reported with data type FSNOTIFY_EVENT_PATH.
 * Note that FAN_MODIFY can also be reported with data type
 * FSNOTIFY_EVENT_INODE.
 */
#घोषणा FANOTIFY_PATH_EVENTS	(FAN_ACCESS | FAN_MODIFY | \
				 FAN_CLOSE | FAN_OPEN | FAN_OPEN_EXEC)

/*
 * Directory entry modअगरication events - reported only to directory
 * where entry is modअगरied and not to a watching parent.
 */
#घोषणा FANOTIFY_सूचीENT_EVENTS	(FAN_MOVE | FAN_CREATE | FAN_DELETE)

/* Events that can only be reported with data type FSNOTIFY_EVENT_INODE */
#घोषणा FANOTIFY_INODE_EVENTS	(FANOTIFY_सूचीENT_EVENTS | \
				 FAN_ATTRIB | FAN_MOVE_SELF | FAN_DELETE_SELF)

/* Events that user can request to be notअगरied on */
#घोषणा FANOTIFY_EVENTS		(FANOTIFY_PATH_EVENTS | \
				 FANOTIFY_INODE_EVENTS)

/* Events that require a permission response from user */
#घोषणा FANOTIFY_PERM_EVENTS	(FAN_OPEN_PERM | FAN_ACCESS_PERM | \
				 FAN_OPEN_EXEC_PERM)

/* Extra flags that may be reported with event or control handling of events */
#घोषणा FANOTIFY_EVENT_FLAGS	(FAN_EVENT_ON_CHILD | FAN_ONसूची)

/* Events that may be reported to user */
#घोषणा FANOTIFY_OUTGOING_EVENTS	(FANOTIFY_EVENTS | \
					 FANOTIFY_PERM_EVENTS | \
					 FAN_Q_OVERFLOW | FAN_ONसूची)

#घोषणा ALL_FANOTIFY_EVENT_BITS		(FANOTIFY_OUTGOING_EVENTS | \
					 FANOTIFY_EVENT_FLAGS)

/* Do not use these old uapi स्थिरants पूर्णांकernally */
#अघोषित FAN_ALL_CLASS_BITS
#अघोषित FAN_ALL_INIT_FLAGS
#अघोषित FAN_ALL_MARK_FLAGS
#अघोषित FAN_ALL_EVENTS
#अघोषित FAN_ALL_PERM_EVENTS
#अघोषित FAN_ALL_OUTGOING_EVENTS

#पूर्ण_अगर /* _LINUX_FANOTIFY_H */

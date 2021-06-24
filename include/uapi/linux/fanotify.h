<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_FANOTIFY_H
#घोषणा _UAPI_LINUX_FANOTIFY_H

#समावेश <linux/types.h>

/* the following events that user-space can रेजिस्टर क्रम */
#घोषणा FAN_ACCESS		0x00000001	/* File was accessed */
#घोषणा FAN_MODIFY		0x00000002	/* File was modअगरied */
#घोषणा FAN_ATTRIB		0x00000004	/* Metadata changed */
#घोषणा FAN_CLOSE_WRITE		0x00000008	/* Writtable file बंदd */
#घोषणा FAN_CLOSE_NOWRITE	0x00000010	/* Unwrittable file बंदd */
#घोषणा FAN_OPEN		0x00000020	/* File was खोलोed */
#घोषणा FAN_MOVED_FROM		0x00000040	/* File was moved from X */
#घोषणा FAN_MOVED_TO		0x00000080	/* File was moved to Y */
#घोषणा FAN_CREATE		0x00000100	/* Subfile was created */
#घोषणा FAN_DELETE		0x00000200	/* Subfile was deleted */
#घोषणा FAN_DELETE_SELF		0x00000400	/* Self was deleted */
#घोषणा FAN_MOVE_SELF		0x00000800	/* Self was moved */
#घोषणा FAN_OPEN_EXEC		0x00001000	/* File was खोलोed क्रम exec */

#घोषणा FAN_Q_OVERFLOW		0x00004000	/* Event queued overflowed */

#घोषणा FAN_OPEN_PERM		0x00010000	/* File खोलो in perm check */
#घोषणा FAN_ACCESS_PERM		0x00020000	/* File accessed in perm check */
#घोषणा FAN_OPEN_EXEC_PERM	0x00040000	/* File खोलो/exec in perm check */

#घोषणा FAN_EVENT_ON_CHILD	0x08000000	/* Interested in child events */

#घोषणा FAN_ONसूची		0x40000000	/* Event occurred against dir */

/* helper events */
#घोषणा FAN_CLOSE		(FAN_CLOSE_WRITE | FAN_CLOSE_NOWRITE) /* बंद */
#घोषणा FAN_MOVE		(FAN_MOVED_FROM | FAN_MOVED_TO) /* moves */

/* flags used क्रम fanotअगरy_init() */
#घोषणा FAN_CLOEXEC		0x00000001
#घोषणा FAN_NONBLOCK		0x00000002

/* These are NOT bitwise flags.  Both bits are used together.  */
#घोषणा FAN_CLASS_NOTIF		0x00000000
#घोषणा FAN_CLASS_CONTENT	0x00000004
#घोषणा FAN_CLASS_PRE_CONTENT	0x00000008

/* Deprecated - करो not use this in programs and करो not add new flags here! */
#घोषणा FAN_ALL_CLASS_BITS	(FAN_CLASS_NOTIF | FAN_CLASS_CONTENT | \
				 FAN_CLASS_PRE_CONTENT)

#घोषणा FAN_UNLIMITED_QUEUE	0x00000010
#घोषणा FAN_UNLIMITED_MARKS	0x00000020
#घोषणा FAN_ENABLE_AUDIT	0x00000040

/* Flags to determine fanotअगरy event क्रमmat */
#घोषणा FAN_REPORT_TID		0x00000100	/* event->pid is thपढ़ो id */
#घोषणा FAN_REPORT_FID		0x00000200	/* Report unique file id */
#घोषणा FAN_REPORT_सूची_FID	0x00000400	/* Report unique directory id */
#घोषणा FAN_REPORT_NAME		0x00000800	/* Report events with name */

/* Convenience macro - FAN_REPORT_NAME requires FAN_REPORT_सूची_FID */
#घोषणा FAN_REPORT_DFID_NAME	(FAN_REPORT_सूची_FID | FAN_REPORT_NAME)

/* Deprecated - करो not use this in programs and करो not add new flags here! */
#घोषणा FAN_ALL_INIT_FLAGS	(FAN_CLOEXEC | FAN_NONBLOCK | \
				 FAN_ALL_CLASS_BITS | FAN_UNLIMITED_QUEUE |\
				 FAN_UNLIMITED_MARKS)

/* flags used क्रम fanotअगरy_modअगरy_mark() */
#घोषणा FAN_MARK_ADD		0x00000001
#घोषणा FAN_MARK_REMOVE		0x00000002
#घोषणा FAN_MARK_DONT_FOLLOW	0x00000004
#घोषणा FAN_MARK_ONLYसूची	0x00000008
/* FAN_MARK_MOUNT is		0x00000010 */
#घोषणा FAN_MARK_IGNORED_MASK	0x00000020
#घोषणा FAN_MARK_IGNORED_SURV_MODIFY	0x00000040
#घोषणा FAN_MARK_FLUSH		0x00000080
/* FAN_MARK_खाताSYSTEM is	0x00000100 */

/* These are NOT bitwise flags.  Both bits can be used togther.  */
#घोषणा FAN_MARK_INODE		0x00000000
#घोषणा FAN_MARK_MOUNT		0x00000010
#घोषणा FAN_MARK_खाताSYSTEM	0x00000100

/* Deprecated - करो not use this in programs and करो not add new flags here! */
#घोषणा FAN_ALL_MARK_FLAGS	(FAN_MARK_ADD |\
				 FAN_MARK_REMOVE |\
				 FAN_MARK_DONT_FOLLOW |\
				 FAN_MARK_ONLYसूची |\
				 FAN_MARK_MOUNT |\
				 FAN_MARK_IGNORED_MASK |\
				 FAN_MARK_IGNORED_SURV_MODIFY |\
				 FAN_MARK_FLUSH)

/* Deprecated - करो not use this in programs and करो not add new flags here! */
#घोषणा FAN_ALL_EVENTS (FAN_ACCESS |\
			FAN_MODIFY |\
			FAN_CLOSE |\
			FAN_OPEN)

/*
 * All events which require a permission response from userspace
 */
/* Deprecated - करो not use this in programs and करो not add new flags here! */
#घोषणा FAN_ALL_PERM_EVENTS (FAN_OPEN_PERM |\
			     FAN_ACCESS_PERM)

/* Deprecated - करो not use this in programs and करो not add new flags here! */
#घोषणा FAN_ALL_OUTGOING_EVENTS	(FAN_ALL_EVENTS |\
				 FAN_ALL_PERM_EVENTS |\
				 FAN_Q_OVERFLOW)

#घोषणा FANOTIFY_METADATA_VERSION	3

काष्ठा fanotअगरy_event_metadata अणु
	__u32 event_len;
	__u8 vers;
	__u8 reserved;
	__u16 metadata_len;
	__aligned_u64 mask;
	__s32 fd;
	__s32 pid;
पूर्ण;

#घोषणा FAN_EVENT_INFO_TYPE_FID		1
#घोषणा FAN_EVENT_INFO_TYPE_DFID_NAME	2
#घोषणा FAN_EVENT_INFO_TYPE_DFID	3

/* Variable length info record following event metadata */
काष्ठा fanotअगरy_event_info_header अणु
	__u8 info_type;
	__u8 pad;
	__u16 len;
पूर्ण;

/*
 * Unique file identअगरier info record.
 * This काष्ठाure is used क्रम records of types FAN_EVENT_INFO_TYPE_FID,
 * FAN_EVENT_INFO_TYPE_DFID and FAN_EVENT_INFO_TYPE_DFID_NAME.
 * For FAN_EVENT_INFO_TYPE_DFID_NAME there is additionally a null terminated
 * name immediately after the file handle.
 */
काष्ठा fanotअगरy_event_info_fid अणु
	काष्ठा fanotअगरy_event_info_header hdr;
	__kernel_fsid_t fsid;
	/*
	 * Following is an opaque काष्ठा file_handle that can be passed as
	 * an argument to खोलो_by_handle_at(2).
	 */
	अचिन्हित अक्षर handle[0];
पूर्ण;

काष्ठा fanotअगरy_response अणु
	__s32 fd;
	__u32 response;
पूर्ण;

/* Legit userspace responses to a _PERM event */
#घोषणा FAN_ALLOW	0x01
#घोषणा FAN_DENY	0x02
#घोषणा FAN_AUDIT	0x10	/* Bit mask to create audit record क्रम result */

/* No fd set in event */
#घोषणा FAN_NOFD	-1

/* Helper functions to deal with fanotअगरy_event_metadata buffers */
#घोषणा FAN_EVENT_METADATA_LEN (माप(काष्ठा fanotअगरy_event_metadata))

#घोषणा FAN_EVENT_NEXT(meta, len) ((len) -= (meta)->event_len, \
				   (काष्ठा fanotअगरy_event_metadata*)(((अक्षर *)(meta)) + \
				   (meta)->event_len))

#घोषणा FAN_EVENT_OK(meta, len)	((दीर्घ)(len) >= (दीर्घ)FAN_EVENT_METADATA_LEN && \
				(दीर्घ)(meta)->event_len >= (दीर्घ)FAN_EVENT_METADATA_LEN && \
				(दीर्घ)(meta)->event_len <= (दीर्घ)(len))

#पूर्ण_अगर /* _UAPI_LINUX_FANOTIFY_H */

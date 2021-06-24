<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_WATCH_QUEUE_H
#घोषणा _UAPI_LINUX_WATCH_QUEUE_H

#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/ioctl.h>

#घोषणा O_NOTIFICATION_PIPE	O_EXCL	/* Parameter to pipe2() selecting notअगरication pipe */

#घोषणा IOC_WATCH_QUEUE_SET_SIZE	_IO('W', 0x60)	/* Set the size in pages */
#घोषणा IOC_WATCH_QUEUE_SET_FILTER	_IO('W', 0x61)	/* Set the filter */

क्रमागत watch_notअगरication_type अणु
	WATCH_TYPE_META		= 0,	/* Special record */
	WATCH_TYPE_KEY_NOTIFY	= 1,	/* Key change event notअगरication */
	WATCH_TYPE__NR		= 2
पूर्ण;

क्रमागत watch_meta_notअगरication_subtype अणु
	WATCH_META_REMOVAL_NOTIFICATION	= 0,	/* Watched object was हटाओd */
	WATCH_META_LOSS_NOTIFICATION	= 1,	/* Data loss occurred */
पूर्ण;

/*
 * Notअगरication record header.  This is aligned to 64-bits so that subclasses
 * can contain __u64 fields.
 */
काष्ठा watch_notअगरication अणु
	__u32			type:24;	/* क्रमागत watch_notअगरication_type */
	__u32			subtype:8;	/* Type-specअगरic subtype (filterable) */
	__u32			info;
#घोषणा WATCH_INFO_LENGTH	0x0000007f	/* Length of record */
#घोषणा WATCH_INFO_LENGTH__SHIFT 0
#घोषणा WATCH_INFO_ID		0x0000ff00	/* ID of watchpoपूर्णांक */
#घोषणा WATCH_INFO_ID__SHIFT	8
#घोषणा WATCH_INFO_TYPE_INFO	0xffff0000	/* Type-specअगरic info */
#घोषणा WATCH_INFO_TYPE_INFO__SHIFT 16
#घोषणा WATCH_INFO_FLAG_0	0x00010000	/* Type-specअगरic info, flag bit 0 */
#घोषणा WATCH_INFO_FLAG_1	0x00020000	/* ... */
#घोषणा WATCH_INFO_FLAG_2	0x00040000
#घोषणा WATCH_INFO_FLAG_3	0x00080000
#घोषणा WATCH_INFO_FLAG_4	0x00100000
#घोषणा WATCH_INFO_FLAG_5	0x00200000
#घोषणा WATCH_INFO_FLAG_6	0x00400000
#घोषणा WATCH_INFO_FLAG_7	0x00800000
पूर्ण;

/*
 * Notअगरication filtering rules (IOC_WATCH_QUEUE_SET_FILTER).
 */
काष्ठा watch_notअगरication_type_filter अणु
	__u32	type;			/* Type to apply filter to */
	__u32	info_filter;		/* Filter on watch_notअगरication::info */
	__u32	info_mask;		/* Mask of relevant bits in info_filter */
	__u32	subtype_filter[8];	/* Biपंचांगask of subtypes to filter on */
पूर्ण;

काष्ठा watch_notअगरication_filter अणु
	__u32	nr_filters;		/* Number of filters */
	__u32	__reserved;		/* Must be 0 */
	काष्ठा watch_notअगरication_type_filter filters[];
पूर्ण;


/*
 * Extended watch removal notअगरication.  This is used optionally अगर the type
 * wants to indicate an identअगरier क्रम the object being watched, अगर there is
 * such.  This can be distinguished by the length.
 *
 * type -> WATCH_TYPE_META
 * subtype -> WATCH_META_REMOVAL_NOTIFICATION
 */
काष्ठा watch_notअगरication_removal अणु
	काष्ठा watch_notअगरication watch;
	__u64	id;		/* Type-dependent identअगरier */
पूर्ण;

/*
 * Type of key/keyring change notअगरication.
 */
क्रमागत key_notअगरication_subtype अणु
	NOTIFY_KEY_INSTANTIATED	= 0, /* Key was instantiated (aux is error code) */
	NOTIFY_KEY_UPDATED	= 1, /* Key was updated */
	NOTIFY_KEY_LINKED	= 2, /* Key (aux) was added to watched keyring */
	NOTIFY_KEY_UNLINKED	= 3, /* Key (aux) was हटाओd from watched keyring */
	NOTIFY_KEY_CLEARED	= 4, /* Keyring was cleared */
	NOTIFY_KEY_REVOKED	= 5, /* Key was revoked */
	NOTIFY_KEY_INVALIDATED	= 6, /* Key was invalidated */
	NOTIFY_KEY_SETATTR	= 7, /* Key's attributes got changed */
पूर्ण;

/*
 * Key/keyring notअगरication record.
 * - watch.type = WATCH_TYPE_KEY_NOTIFY
 * - watch.subtype = क्रमागत key_notअगरication_type
 */
काष्ठा key_notअगरication अणु
	काष्ठा watch_notअगरication watch;
	__u32	key_id;		/* The key/keyring affected */
	__u32	aux;		/* Per-type auxiliary data */
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_WATCH_QUEUE_H */

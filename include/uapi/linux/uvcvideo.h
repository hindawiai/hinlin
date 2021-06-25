<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_UVCVIDEO_H_
#घोषणा __LINUX_UVCVIDEO_H_

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/*
 * Dynamic controls
 */

/* Data types क्रम UVC control data */
#घोषणा UVC_CTRL_DATA_TYPE_RAW		0
#घोषणा UVC_CTRL_DATA_TYPE_SIGNED	1
#घोषणा UVC_CTRL_DATA_TYPE_UNSIGNED	2
#घोषणा UVC_CTRL_DATA_TYPE_BOOLEAN	3
#घोषणा UVC_CTRL_DATA_TYPE_ENUM		4
#घोषणा UVC_CTRL_DATA_TYPE_BITMASK	5

/* Control flags */
#घोषणा UVC_CTRL_FLAG_SET_CUR		(1 << 0)
#घोषणा UVC_CTRL_FLAG_GET_CUR		(1 << 1)
#घोषणा UVC_CTRL_FLAG_GET_MIN		(1 << 2)
#घोषणा UVC_CTRL_FLAG_GET_MAX		(1 << 3)
#घोषणा UVC_CTRL_FLAG_GET_RES		(1 << 4)
#घोषणा UVC_CTRL_FLAG_GET_DEF		(1 << 5)
/* Control should be saved at suspend and restored at resume. */
#घोषणा UVC_CTRL_FLAG_RESTORE		(1 << 6)
/* Control can be updated by the camera. */
#घोषणा UVC_CTRL_FLAG_AUTO_UPDATE	(1 << 7)
/* Control supports asynchronous reporting */
#घोषणा UVC_CTRL_FLAG_ASYNCHRONOUS	(1 << 8)

#घोषणा UVC_CTRL_FLAG_GET_RANGE \
	(UVC_CTRL_FLAG_GET_CUR | UVC_CTRL_FLAG_GET_MIN | \
	 UVC_CTRL_FLAG_GET_MAX | UVC_CTRL_FLAG_GET_RES | \
	 UVC_CTRL_FLAG_GET_DEF)

काष्ठा uvc_menu_info अणु
	__u32 value;
	__u8 name[32];
पूर्ण;

काष्ठा uvc_xu_control_mapping अणु
	__u32 id;
	__u8 name[32];
	__u8 entity[16];
	__u8 selector;

	__u8 size;
	__u8 offset;
	__u32 v4l2_type;
	__u32 data_type;

	काष्ठा uvc_menu_info __user *menu_info;
	__u32 menu_count;

	__u32 reserved[4];
पूर्ण;

काष्ठा uvc_xu_control_query अणु
	__u8 unit;
	__u8 selector;
	__u8 query;		/* Video Class-Specअगरic Request Code, */
				/* defined in linux/usb/video.h A.8.  */
	__u16 size;
	__u8 __user *data;
पूर्ण;

#घोषणा UVCIOC_CTRL_MAP		_IOWR('u', 0x20, काष्ठा uvc_xu_control_mapping)
#घोषणा UVCIOC_CTRL_QUERY	_IOWR('u', 0x21, काष्ठा uvc_xu_control_query)

/*
 * Metadata node
 */

/**
 * काष्ठा uvc_meta_buf - metadata buffer building block
 * @ns: प्रणाली बारtamp of the payload in nanoseconds
 * @sof: USB Frame Number
 * @length: length of the payload header
 * @flags: payload header flags
 * @buf: optional device-specअगरic header data
 *
 * UVC metadata nodes fill buffers with possibly multiple instances of this
 * काष्ठा. The first two fields are added by the driver, they can be used क्रम
 * घड़ी synchronisation. The rest is an exact copy of a UVC payload header.
 * Only complete objects with complete buffers are included. Thereक्रमe it's
 * always माप(meta->ts) + माप(meta->sof) + meta->length bytes large.
 */
काष्ठा uvc_meta_buf अणु
	__u64 ns;
	__u16 sof;
	__u8 length;
	__u8 flags;
	__u8 buf[];
पूर्ण __packed;

#पूर्ण_अगर

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Mulसमयdia device API
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __LINUX_MEDIA_H
#घोषणा __LINUX_MEDIA_H

#अगर_अघोषित __KERNEL__
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर
#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

काष्ठा media_device_info अणु
	अक्षर driver[16];
	अक्षर model[32];
	अक्षर serial[40];
	अक्षर bus_info[32];
	__u32 media_version;
	__u32 hw_revision;
	__u32 driver_version;
	__u32 reserved[31];
पूर्ण;

/*
 * Base number ranges क्रम entity functions
 *
 * NOTE: Userspace should not rely on these ranges to identअगरy a group
 * of function types, as newer functions can be added with any name within
 * the full u32 range.
 *
 * Some older functions use the MEDIA_ENT_F_OLD_*_BASE range. Do not
 * change this, this is क्रम backwards compatibility. When adding new
 * functions always use MEDIA_ENT_F_BASE.
 */
#घोषणा MEDIA_ENT_F_BASE			0x00000000
#घोषणा MEDIA_ENT_F_OLD_BASE			0x00010000
#घोषणा MEDIA_ENT_F_OLD_SUBDEV_BASE		0x00020000

/*
 * Initial value to be used when a new entity is created
 * Drivers should change it to something useful.
 */
#घोषणा MEDIA_ENT_F_UNKNOWN			MEDIA_ENT_F_BASE

/*
 * Subdevs are initialized with MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN in order
 * to preserve backward compatibility. Drivers must change to the proper
 * subdev type beक्रमe रेजिस्टरing the entity.
 */
#घोषणा MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN		MEDIA_ENT_F_OLD_SUBDEV_BASE

/*
 * DVB entity functions
 */
#घोषणा MEDIA_ENT_F_DTV_DEMOD			(MEDIA_ENT_F_BASE + 0x00001)
#घोषणा MEDIA_ENT_F_TS_DEMUX			(MEDIA_ENT_F_BASE + 0x00002)
#घोषणा MEDIA_ENT_F_DTV_CA			(MEDIA_ENT_F_BASE + 0x00003)
#घोषणा MEDIA_ENT_F_DTV_NET_DECAP		(MEDIA_ENT_F_BASE + 0x00004)

/*
 * I/O entity functions
 */
#घोषणा MEDIA_ENT_F_IO_V4L			(MEDIA_ENT_F_OLD_BASE + 1)
#घोषणा MEDIA_ENT_F_IO_DTV			(MEDIA_ENT_F_BASE + 0x01001)
#घोषणा MEDIA_ENT_F_IO_VBI			(MEDIA_ENT_F_BASE + 0x01002)
#घोषणा MEDIA_ENT_F_IO_SWRADIO			(MEDIA_ENT_F_BASE + 0x01003)

/*
 * Sensor functions
 */
#घोषणा MEDIA_ENT_F_CAM_SENSOR			(MEDIA_ENT_F_OLD_SUBDEV_BASE + 1)
#घोषणा MEDIA_ENT_F_FLASH			(MEDIA_ENT_F_OLD_SUBDEV_BASE + 2)
#घोषणा MEDIA_ENT_F_LENS			(MEDIA_ENT_F_OLD_SUBDEV_BASE + 3)

/*
 * Digital TV, analog TV, radio and/or software defined radio tuner functions.
 *
 * It is a responsibility of the master/bridge drivers to add connectors
 * and links क्रम MEDIA_ENT_F_TUNER. Please notice that some old tuners
 * may require the usage of separate I2C chips to decode analog TV संकेतs,
 * when the master/bridge chipset करोesn't have its own TV standard decoder.
 * On such हालs, the IF-PLL staging is mapped via one or two entities:
 * MEDIA_ENT_F_IF_VID_DECODER and/or MEDIA_ENT_F_IF_AUD_DECODER.
 */
#घोषणा MEDIA_ENT_F_TUNER			(MEDIA_ENT_F_OLD_SUBDEV_BASE + 5)

/*
 * Analog TV IF-PLL decoder functions
 *
 * It is a responsibility of the master/bridge drivers to create links
 * क्रम MEDIA_ENT_F_IF_VID_DECODER and MEDIA_ENT_F_IF_AUD_DECODER.
 */
#घोषणा MEDIA_ENT_F_IF_VID_DECODER		(MEDIA_ENT_F_BASE + 0x02001)
#घोषणा MEDIA_ENT_F_IF_AUD_DECODER		(MEDIA_ENT_F_BASE + 0x02002)

/*
 * Audio entity functions
 */
#घोषणा MEDIA_ENT_F_AUDIO_CAPTURE		(MEDIA_ENT_F_BASE + 0x03001)
#घोषणा MEDIA_ENT_F_AUDIO_PLAYBACK		(MEDIA_ENT_F_BASE + 0x03002)
#घोषणा MEDIA_ENT_F_AUDIO_MIXER			(MEDIA_ENT_F_BASE + 0x03003)

/*
 * Processing entity functions
 */
#घोषणा MEDIA_ENT_F_PROC_VIDEO_COMPOSER		(MEDIA_ENT_F_BASE + 0x4001)
#घोषणा MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER	(MEDIA_ENT_F_BASE + 0x4002)
#घोषणा MEDIA_ENT_F_PROC_VIDEO_PIXEL_ENC_CONV	(MEDIA_ENT_F_BASE + 0x4003)
#घोषणा MEDIA_ENT_F_PROC_VIDEO_LUT		(MEDIA_ENT_F_BASE + 0x4004)
#घोषणा MEDIA_ENT_F_PROC_VIDEO_SCALER		(MEDIA_ENT_F_BASE + 0x4005)
#घोषणा MEDIA_ENT_F_PROC_VIDEO_STATISTICS	(MEDIA_ENT_F_BASE + 0x4006)
#घोषणा MEDIA_ENT_F_PROC_VIDEO_ENCODER		(MEDIA_ENT_F_BASE + 0x4007)
#घोषणा MEDIA_ENT_F_PROC_VIDEO_DECODER		(MEDIA_ENT_F_BASE + 0x4008)
#घोषणा MEDIA_ENT_F_PROC_VIDEO_ISP		(MEDIA_ENT_F_BASE + 0x4009)

/*
 * Switch and bridge entity functions
 */
#घोषणा MEDIA_ENT_F_VID_MUX			(MEDIA_ENT_F_BASE + 0x5001)
#घोषणा MEDIA_ENT_F_VID_IF_BRIDGE		(MEDIA_ENT_F_BASE + 0x5002)

/*
 * Video decoder/encoder functions
 */
#घोषणा MEDIA_ENT_F_ATV_DECODER			(MEDIA_ENT_F_OLD_SUBDEV_BASE + 4)
#घोषणा MEDIA_ENT_F_DV_DECODER			(MEDIA_ENT_F_BASE + 0x6001)
#घोषणा MEDIA_ENT_F_DV_ENCODER			(MEDIA_ENT_F_BASE + 0x6002)

/* Entity flags */
#घोषणा MEDIA_ENT_FL_DEFAULT			(1 << 0)
#घोषणा MEDIA_ENT_FL_CONNECTOR			(1 << 1)

/* OR with the entity id value to find the next entity */
#घोषणा MEDIA_ENT_ID_FLAG_NEXT			(1U << 31)

काष्ठा media_entity_desc अणु
	__u32 id;
	अक्षर name[32];
	__u32 type;
	__u32 revision;
	__u32 flags;
	__u32 group_id;
	__u16 pads;
	__u16 links;

	__u32 reserved[4];

	जोड़ अणु
		/* Node specअगरications */
		काष्ठा अणु
			__u32 major;
			__u32 minor;
		पूर्ण dev;

#अगर !defined(__KERNEL__)
		/*
		 * TODO: this shouldn't have been added without
		 * actual drivers that use this. When the first real driver
		 * appears that sets this inक्रमmation, special attention
		 * should be given whether this inक्रमmation is 1) enough, and
		 * 2) can deal with udev rules that नाम devices. The काष्ठा
		 * dev would not be sufficient क्रम this since that करोes not
		 * contain the subdevice inक्रमmation. In addition, काष्ठा dev
		 * can only refer to a single device, and not to multiple (e.g.
		 * pcm and mixer devices).
		 */
		काष्ठा अणु
			__u32 card;
			__u32 device;
			__u32 subdevice;
		पूर्ण alsa;

		/*
		 * DEPRECATED: previous node specअगरications. Kept just to
		 * aव्योम अवरोधing compilation. Use media_entity_desc.dev
		 * instead.
		 */
		काष्ठा अणु
			__u32 major;
			__u32 minor;
		पूर्ण v4l;
		काष्ठा अणु
			__u32 major;
			__u32 minor;
		पूर्ण fb;
		पूर्णांक dvb;
#पूर्ण_अगर

		/* Sub-device specअगरications */
		/* Nothing needed yet */
		__u8 raw[184];
	पूर्ण;
पूर्ण;

#घोषणा MEDIA_PAD_FL_SINK			(1 << 0)
#घोषणा MEDIA_PAD_FL_SOURCE			(1 << 1)
#घोषणा MEDIA_PAD_FL_MUST_CONNECT		(1 << 2)

काष्ठा media_pad_desc अणु
	__u32 entity;		/* entity ID */
	__u16 index;		/* pad index */
	__u32 flags;		/* pad flags */
	__u32 reserved[2];
पूर्ण;

#घोषणा MEDIA_LNK_FL_ENABLED			(1 << 0)
#घोषणा MEDIA_LNK_FL_IMMUTABLE			(1 << 1)
#घोषणा MEDIA_LNK_FL_DYNAMIC			(1 << 2)

#घोषणा MEDIA_LNK_FL_LINK_TYPE			(0xf << 28)
#  define MEDIA_LNK_FL_DATA_LINK		(0 << 28)
#  define MEDIA_LNK_FL_INTERFACE_LINK		(1 << 28)

काष्ठा media_link_desc अणु
	काष्ठा media_pad_desc source;
	काष्ठा media_pad_desc sink;
	__u32 flags;
	__u32 reserved[2];
पूर्ण;

काष्ठा media_links_क्रमागत अणु
	__u32 entity;
	/* Should have enough room क्रम pads elements */
	काष्ठा media_pad_desc __user *pads;
	/* Should have enough room क्रम links elements */
	काष्ठा media_link_desc __user *links;
	__u32 reserved[4];
पूर्ण;

/* Interface type ranges */

#घोषणा MEDIA_INTF_T_DVB_BASE			0x00000100
#घोषणा MEDIA_INTF_T_V4L_BASE			0x00000200

/* Interface types */

#घोषणा MEDIA_INTF_T_DVB_FE			(MEDIA_INTF_T_DVB_BASE)
#घोषणा MEDIA_INTF_T_DVB_DEMUX			(MEDIA_INTF_T_DVB_BASE + 1)
#घोषणा MEDIA_INTF_T_DVB_DVR			(MEDIA_INTF_T_DVB_BASE + 2)
#घोषणा MEDIA_INTF_T_DVB_CA			(MEDIA_INTF_T_DVB_BASE + 3)
#घोषणा MEDIA_INTF_T_DVB_NET			(MEDIA_INTF_T_DVB_BASE + 4)

#घोषणा MEDIA_INTF_T_V4L_VIDEO			(MEDIA_INTF_T_V4L_BASE)
#घोषणा MEDIA_INTF_T_V4L_VBI			(MEDIA_INTF_T_V4L_BASE + 1)
#घोषणा MEDIA_INTF_T_V4L_RADIO			(MEDIA_INTF_T_V4L_BASE + 2)
#घोषणा MEDIA_INTF_T_V4L_SUBDEV			(MEDIA_INTF_T_V4L_BASE + 3)
#घोषणा MEDIA_INTF_T_V4L_SWRADIO		(MEDIA_INTF_T_V4L_BASE + 4)
#घोषणा MEDIA_INTF_T_V4L_TOUCH			(MEDIA_INTF_T_V4L_BASE + 5)

#घोषणा MEDIA_INTF_T_ALSA_BASE			0x00000300
#घोषणा MEDIA_INTF_T_ALSA_PCM_CAPTURE		(MEDIA_INTF_T_ALSA_BASE)
#घोषणा MEDIA_INTF_T_ALSA_PCM_PLAYBACK		(MEDIA_INTF_T_ALSA_BASE + 1)
#घोषणा MEDIA_INTF_T_ALSA_CONTROL		(MEDIA_INTF_T_ALSA_BASE + 2)

#अगर defined(__KERNEL__)

/*
 * Connector functions
 *
 * For now these should not be used in userspace, as some definitions may
 * change.
 *
 * It is the responsibility of the entity drivers to add connectors and links.
 */
#घोषणा MEDIA_ENT_F_CONN_RF			(MEDIA_ENT_F_BASE + 0x30001)
#घोषणा MEDIA_ENT_F_CONN_SVIDEO			(MEDIA_ENT_F_BASE + 0x30002)
#घोषणा MEDIA_ENT_F_CONN_COMPOSITE		(MEDIA_ENT_F_BASE + 0x30003)

#पूर्ण_अगर

/*
 * MC next gen API definitions
 */

/*
 * Appeared in 4.19.0.
 *
 * The media_version argument comes from the media_version field in
 * काष्ठा media_device_info.
 */
#घोषणा MEDIA_V2_ENTITY_HAS_FLAGS(media_version) \
	((media_version) >= ((4 << 16) | (19 << 8) | 0))

काष्ठा media_v2_entity अणु
	__u32 id;
	अक्षर name[64];
	__u32 function;		/* Main function of the entity */
	__u32 flags;
	__u32 reserved[5];
पूर्ण __attribute__ ((packed));

/* Should match the specअगरic fields at media_पूर्णांकf_devnode */
काष्ठा media_v2_पूर्णांकf_devnode अणु
	__u32 major;
	__u32 minor;
पूर्ण __attribute__ ((packed));

काष्ठा media_v2_पूर्णांकerface अणु
	__u32 id;
	__u32 पूर्णांकf_type;
	__u32 flags;
	__u32 reserved[9];

	जोड़ अणु
		काष्ठा media_v2_पूर्णांकf_devnode devnode;
		__u32 raw[16];
	पूर्ण;
पूर्ण __attribute__ ((packed));

/*
 * Appeared in 4.19.0.
 *
 * The media_version argument comes from the media_version field in
 * काष्ठा media_device_info.
 */
#घोषणा MEDIA_V2_PAD_HAS_INDEX(media_version) \
	((media_version) >= ((4 << 16) | (19 << 8) | 0))

काष्ठा media_v2_pad अणु
	__u32 id;
	__u32 entity_id;
	__u32 flags;
	__u32 index;
	__u32 reserved[4];
पूर्ण __attribute__ ((packed));

काष्ठा media_v2_link अणु
	__u32 id;
	__u32 source_id;
	__u32 sink_id;
	__u32 flags;
	__u32 reserved[6];
पूर्ण __attribute__ ((packed));

काष्ठा media_v2_topology अणु
	__u64 topology_version;

	__u32 num_entities;
	__u32 reserved1;
	__u64 ptr_entities;

	__u32 num_पूर्णांकerfaces;
	__u32 reserved2;
	__u64 ptr_पूर्णांकerfaces;

	__u32 num_pads;
	__u32 reserved3;
	__u64 ptr_pads;

	__u32 num_links;
	__u32 reserved4;
	__u64 ptr_links;
पूर्ण __attribute__ ((packed));

/* ioctls */

#घोषणा MEDIA_IOC_DEVICE_INFO	_IOWR('|', 0x00, काष्ठा media_device_info)
#घोषणा MEDIA_IOC_ENUM_ENTITIES	_IOWR('|', 0x01, काष्ठा media_entity_desc)
#घोषणा MEDIA_IOC_ENUM_LINKS	_IOWR('|', 0x02, काष्ठा media_links_क्रमागत)
#घोषणा MEDIA_IOC_SETUP_LINK	_IOWR('|', 0x03, काष्ठा media_link_desc)
#घोषणा MEDIA_IOC_G_TOPOLOGY	_IOWR('|', 0x04, काष्ठा media_v2_topology)
#घोषणा MEDIA_IOC_REQUEST_ALLOC	_IOR ('|', 0x05, पूर्णांक)

/*
 * These ioctls are called on the request file descriptor as वापसed
 * by MEDIA_IOC_REQUEST_ALLOC.
 */
#घोषणा MEDIA_REQUEST_IOC_QUEUE		_IO('|',  0x80)
#घोषणा MEDIA_REQUEST_IOC_REINIT	_IO('|',  0x81)

#अगर_अघोषित __KERNEL__

/*
 * Legacy symbols used to aव्योम userspace compilation अवरोधages.
 * Do not use any of this in new applications!
 *
 * Those symbols map the entity function पूर्णांकo types and should be
 * used only on legacy programs क्रम legacy hardware. Don't rely
 * on those क्रम MEDIA_IOC_G_TOPOLOGY.
 */
#घोषणा MEDIA_ENT_TYPE_SHIFT			16
#घोषणा MEDIA_ENT_TYPE_MASK			0x00ff0000
#घोषणा MEDIA_ENT_SUBTYPE_MASK			0x0000ffff

#घोषणा MEDIA_ENT_T_DEVNODE_UNKNOWN		(MEDIA_ENT_F_OLD_BASE | \
						 MEDIA_ENT_SUBTYPE_MASK)

#घोषणा MEDIA_ENT_T_DEVNODE			MEDIA_ENT_F_OLD_BASE
#घोषणा MEDIA_ENT_T_DEVNODE_V4L			MEDIA_ENT_F_IO_V4L
#घोषणा MEDIA_ENT_T_DEVNODE_FB			(MEDIA_ENT_F_OLD_BASE + 2)
#घोषणा MEDIA_ENT_T_DEVNODE_ALSA		(MEDIA_ENT_F_OLD_BASE + 3)
#घोषणा MEDIA_ENT_T_DEVNODE_DVB			(MEDIA_ENT_F_OLD_BASE + 4)

#घोषणा MEDIA_ENT_T_UNKNOWN			MEDIA_ENT_F_UNKNOWN
#घोषणा MEDIA_ENT_T_V4L2_VIDEO			MEDIA_ENT_F_IO_V4L
#घोषणा MEDIA_ENT_T_V4L2_SUBDEV			MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN
#घोषणा MEDIA_ENT_T_V4L2_SUBDEV_SENSOR		MEDIA_ENT_F_CAM_SENSOR
#घोषणा MEDIA_ENT_T_V4L2_SUBDEV_FLASH		MEDIA_ENT_F_FLASH
#घोषणा MEDIA_ENT_T_V4L2_SUBDEV_LENS		MEDIA_ENT_F_LENS
#घोषणा MEDIA_ENT_T_V4L2_SUBDEV_DECODER		MEDIA_ENT_F_ATV_DECODER
#घोषणा MEDIA_ENT_T_V4L2_SUBDEV_TUNER		MEDIA_ENT_F_TUNER

#घोषणा MEDIA_ENT_F_DTV_DECODER			MEDIA_ENT_F_DV_DECODER

/*
 * There is still no full ALSA support in the media controller. These
 * defines should not have been added and we leave them here only
 * in हाल some application tries to use these defines.
 *
 * The ALSA defines that are in use have been moved पूर्णांकo __KERNEL__
 * scope. As support माला_लो added to these पूर्णांकerface types, they should
 * be moved पूर्णांकo __KERNEL__ scope with the code that uses them.
 */
#घोषणा MEDIA_INTF_T_ALSA_COMPRESS             (MEDIA_INTF_T_ALSA_BASE + 3)
#घोषणा MEDIA_INTF_T_ALSA_RAWMIDI              (MEDIA_INTF_T_ALSA_BASE + 4)
#घोषणा MEDIA_INTF_T_ALSA_HWDEP                (MEDIA_INTF_T_ALSA_BASE + 5)
#घोषणा MEDIA_INTF_T_ALSA_SEQUENCER            (MEDIA_INTF_T_ALSA_BASE + 6)
#घोषणा MEDIA_INTF_T_ALSA_TIMER                (MEDIA_INTF_T_ALSA_BASE + 7)

/* Obsolete symbol क्रम media_version, no दीर्घer used in the kernel */
#घोषणा MEDIA_API_VERSION			((0 << 16) | (1 << 8) | 0)

#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_MEDIA_H */

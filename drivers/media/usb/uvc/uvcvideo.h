<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _USB_VIDEO_H_
#घोषणा _USB_VIDEO_H_

#अगर_अघोषित __KERNEL__
#त्रुटि "The uvcvideo.h header is deprecated, use linux/uvcvideo.h instead."
#पूर्ण_अगर /* __KERNEL__ */

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/poll.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/video.h>
#समावेश <linux/uvcvideo.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <media/media-device.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/videobuf2-v4l2.h>

/* --------------------------------------------------------------------------
 * UVC स्थिरants
 */

#घोषणा UVC_TERM_INPUT			0x0000
#घोषणा UVC_TERM_OUTPUT			0x8000
#घोषणा UVC_TERM_सूचीECTION(term)	((term)->type & 0x8000)

#घोषणा UVC_ENTITY_TYPE(entity)		((entity)->type & 0x7fff)
#घोषणा UVC_ENTITY_IS_UNIT(entity)	(((entity)->type & 0xff00) == 0)
#घोषणा UVC_ENTITY_IS_TERM(entity)	(((entity)->type & 0xff00) != 0)
#घोषणा UVC_ENTITY_IS_ITERM(entity) \
	(UVC_ENTITY_IS_TERM(entity) && \
	((entity)->type & 0x8000) == UVC_TERM_INPUT)
#घोषणा UVC_ENTITY_IS_OTERM(entity) \
	(UVC_ENTITY_IS_TERM(entity) && \
	((entity)->type & 0x8000) == UVC_TERM_OUTPUT)

#घोषणा UVC_EXT_GPIO_UNIT		0x7ffe
#घोषणा UVC_EXT_GPIO_UNIT_ID		0x100

/* ------------------------------------------------------------------------
 * GUIDs
 */
#घोषणा UVC_GUID_UVC_CAMERA \
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01पूर्ण
#घोषणा UVC_GUID_UVC_OUTPUT \
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02पूर्ण
#घोषणा UVC_GUID_UVC_MEDIA_TRANSPORT_INPUT \
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03पूर्ण
#घोषणा UVC_GUID_UVC_PROCESSING \
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01पूर्ण
#घोषणा UVC_GUID_UVC_SELECTOR \
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02पूर्ण
#घोषणा UVC_GUID_EXT_GPIO_CONTROLLER \
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03पूर्ण

#घोषणा UVC_GUID_FORMAT_MJPEG \
	अणु 'M',  'J',  'P',  'G', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_YUY2 \
	अणु 'Y',  'U',  'Y',  '2', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_YUY2_ISIGHT \
	अणु 'Y',  'U',  'Y',  '2', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0x00, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_NV12 \
	अणु 'N',  'V',  '1',  '2', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_YV12 \
	अणु 'Y',  'V',  '1',  '2', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_I420 \
	अणु 'I',  '4',  '2',  '0', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_UYVY \
	अणु 'U',  'Y',  'V',  'Y', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_Y800 \
	अणु 'Y',  '8',  '0',  '0', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_Y8 \
	अणु 'Y',  '8',  ' ',  ' ', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_Y10 \
	अणु 'Y',  '1',  '0',  ' ', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_Y12 \
	अणु 'Y',  '1',  '2',  ' ', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_Y16 \
	अणु 'Y',  '1',  '6',  ' ', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_BY8 \
	अणु 'B',  'Y',  '8',  ' ', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_BA81 \
	अणु 'B',  'A',  '8',  '1', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_GBRG \
	अणु 'G',  'B',  'R',  'G', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_GRBG \
	अणु 'G',  'R',  'B',  'G', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_RGGB \
	अणु 'R',  'G',  'G',  'B', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_BG16 \
	अणु 'B',  'G',  '1',  '6', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_GB16 \
	अणु 'G',  'B',  '1',  '6', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_RG16 \
	अणु 'R',  'G',  '1',  '6', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_GR16 \
	अणु 'G',  'R',  '1',  '6', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_RGBP \
	अणु 'R',  'G',  'B',  'P', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_BGR3 \
	अणु 0x7d, 0xeb, 0x36, 0xe4, 0x4f, 0x52, 0xce, 0x11, \
	 0x9f, 0x53, 0x00, 0x20, 0xaf, 0x0b, 0xa7, 0x70पूर्ण
#घोषणा UVC_GUID_FORMAT_M420 \
	अणु 'M',  '4',  '2',  '0', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण

#घोषणा UVC_GUID_FORMAT_H264 \
	अणु 'H',  '2',  '6',  '4', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_Y8I \
	अणु 'Y',  '8',  'I',  ' ', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_Y12I \
	अणु 'Y',  '1',  '2',  'I', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_Z16 \
	अणु 'Z',  '1',  '6',  ' ', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_RW10 \
	अणु 'R',  'W',  '1',  '0', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_INVZ \
	अणु 'I',  'N',  'V',  'Z', 0x90, 0x2d, 0x58, 0x4a, \
	 0x92, 0x0b, 0x77, 0x3f, 0x1f, 0x2c, 0x55, 0x6bपूर्ण
#घोषणा UVC_GUID_FORMAT_INZI \
	अणु 'I',  'N',  'Z',  'I', 0x66, 0x1a, 0x42, 0xa2, \
	 0x90, 0x65, 0xd0, 0x18, 0x14, 0xa8, 0xef, 0x8aपूर्ण
#घोषणा UVC_GUID_FORMAT_INVI \
	अणु 'I',  'N',  'V',  'I', 0xdb, 0x57, 0x49, 0x5e, \
	 0x8e, 0x3f, 0xf4, 0x79, 0x53, 0x2b, 0x94, 0x6fपूर्ण
#घोषणा UVC_GUID_FORMAT_CNF4 \
	अणु 'C',  ' ',  ' ',  ' ', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण

#घोषणा UVC_GUID_FORMAT_D3DFMT_L8 \
	अणु0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण
#घोषणा UVC_GUID_FORMAT_KSMEDIA_L8_IR \
	अणु0x32, 0x00, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण

#घोषणा UVC_GUID_FORMAT_HEVC \
	अणु 'H',  'E',  'V',  'C', 0x00, 0x00, 0x10, 0x00, \
	 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण


/* ------------------------------------------------------------------------
 * Driver specअगरic स्थिरants.
 */

#घोषणा DRIVER_VERSION		"1.1.1"

/* Number of isochronous URBs. */
#घोषणा UVC_URBS		5
/* Maximum number of packets per URB. */
#घोषणा UVC_MAX_PACKETS		32
/* Maximum status buffer size in bytes of पूर्णांकerrupt URB. */
#घोषणा UVC_MAX_STATUS_SIZE	16

#घोषणा UVC_CTRL_CONTROL_TIMEOUT	500
#घोषणा UVC_CTRL_STREAMING_TIMEOUT	5000

/* Maximum allowed number of control mappings per device */
#घोषणा UVC_MAX_CONTROL_MAPPINGS	1024
#घोषणा UVC_MAX_CONTROL_MENU_ENTRIES	32

/* Devices quirks */
#घोषणा UVC_QUIRK_STATUS_INTERVAL	0x00000001
#घोषणा UVC_QUIRK_PROBE_MINMAX		0x00000002
#घोषणा UVC_QUIRK_PROBE_EXTRAFIELDS	0x00000004
#घोषणा UVC_QUIRK_BUILTIN_ISIGHT	0x00000008
#घोषणा UVC_QUIRK_STREAM_NO_FID		0x00000010
#घोषणा UVC_QUIRK_IGNORE_SELECTOR_UNIT	0x00000020
#घोषणा UVC_QUIRK_FIX_BANDWIDTH		0x00000080
#घोषणा UVC_QUIRK_PROBE_DEF		0x00000100
#घोषणा UVC_QUIRK_RESTRICT_FRAME_RATE	0x00000200
#घोषणा UVC_QUIRK_RESTORE_CTRLS_ON_INIT	0x00000400
#घोषणा UVC_QUIRK_FORCE_Y8		0x00000800
#घोषणा UVC_QUIRK_FORCE_BPP		0x00001000

/* Format flags */
#घोषणा UVC_FMT_FLAG_COMPRESSED		0x00000001
#घोषणा UVC_FMT_FLAG_STREAM		0x00000002

/* ------------------------------------------------------------------------
 * Structures.
 */

काष्ठा gpio_desc;
काष्ठा sg_table;
काष्ठा uvc_device;

/* TODO: Put the most frequently accessed fields at the beginning of
 * काष्ठाures to maximize cache efficiency.
 */
काष्ठा uvc_control_info अणु
	काष्ठा list_head mappings;

	u8 entity[16];
	u8 index;	/* Bit index in bmControls */
	u8 selector;

	u16 size;
	u32 flags;
पूर्ण;

काष्ठा uvc_control_mapping अणु
	काष्ठा list_head list;
	काष्ठा list_head ev_subs;

	u32 id;
	u8 name[32];
	u8 entity[16];
	u8 selector;

	u8 size;
	u8 offset;
	क्रमागत v4l2_ctrl_type v4l2_type;
	u32 data_type;

	स्थिर काष्ठा uvc_menu_info *menu_info;
	u32 menu_count;

	u32 master_id;
	s32 master_manual;
	u32 slave_ids[2];

	s32 (*get)(काष्ठा uvc_control_mapping *mapping, u8 query,
		   स्थिर u8 *data);
	व्योम (*set)(काष्ठा uvc_control_mapping *mapping, s32 value,
		    u8 *data);
पूर्ण;

काष्ठा uvc_control अणु
	काष्ठा uvc_entity *entity;
	काष्ठा uvc_control_info info;

	u8 index;	/* Used to match the uvc_control entry with a
			   uvc_control_info. */
	u8 dirty:1,
	   loaded:1,
	   modअगरied:1,
	   cached:1,
	   initialized:1;

	u8 *uvc_data;

	काष्ठा uvc_fh *handle;	/* File handle that last changed the control. */
पूर्ण;

काष्ठा uvc_क्रमmat_desc अणु
	अक्षर *name;
	u8 guid[16];
	u32 fcc;
पूर्ण;

/* The term 'entity' refers to both UVC units and UVC terminals.
 *
 * The type field is either the terminal type (wTerminalType in the terminal
 * descriptor), or the unit type (bDescriptorSubtype in the unit descriptor).
 * As the bDescriptorSubtype field is one byte दीर्घ, the type value will
 * always have a null MSB क्रम units. All terminal types defined by the UVC
 * specअगरication have a non-null MSB, so it is safe to use the MSB to
 * dअगरferentiate between units and terminals as दीर्घ as the descriptor parsing
 * code makes sure terminal types have a non-null MSB.
 *
 * For terminals, the type's most signअगरicant bit stores the terminal
 * direction (either UVC_TERM_INPUT or UVC_TERM_OUTPUT). The type field should
 * always be accessed with the UVC_ENTITY_* macros and never directly.
 */

#घोषणा UVC_ENTITY_FLAG_DEFAULT		(1 << 0)

काष्ठा uvc_entity अणु
	काष्ठा list_head list;		/* Entity as part of a UVC device. */
	काष्ठा list_head chain;		/* Entity as part of a video device
					 * chain. */
	अचिन्हित पूर्णांक flags;

	/*
	 * Entities exposed by the UVC device use IDs 0-255, extra entities
	 * implemented by the driver (such as the GPIO entity) use IDs 256 and
	 * up.
	 */
	u16 id;
	u16 type;
	अक्षर name[64];
	u8 guid[16];

	/* Media controller-related fields. */
	काष्ठा video_device *vdev;
	काष्ठा v4l2_subdev subdev;
	अचिन्हित पूर्णांक num_pads;
	अचिन्हित पूर्णांक num_links;
	काष्ठा media_pad *pads;

	जोड़ अणु
		काष्ठा अणु
			u16 wObjectiveFocalLengthMin;
			u16 wObjectiveFocalLengthMax;
			u16 wOcularFocalLength;
			u8  bControlSize;
			u8  *bmControls;
		पूर्ण camera;

		काष्ठा अणु
			u8  bControlSize;
			u8  *bmControls;
			u8  bTransportModeSize;
			u8  *bmTransportModes;
		पूर्ण media;

		काष्ठा अणु
		पूर्ण output;

		काष्ठा अणु
			u16 wMaxMultiplier;
			u8  bControlSize;
			u8  *bmControls;
			u8  bmVideoStandards;
		पूर्ण processing;

		काष्ठा अणु
		पूर्ण selector;

		काष्ठा अणु
			u8  bNumControls;
			u8  bControlSize;
			u8  *bmControls;
			u8  *bmControlsType;
		पूर्ण extension;

		काष्ठा अणु
			u8  bControlSize;
			u8  *bmControls;
			काष्ठा gpio_desc *gpio_privacy;
			पूर्णांक irq;
		पूर्ण gpio;
	पूर्ण;

	u8 bNrInPins;
	u8 *baSourceID;

	पूर्णांक (*get_info)(काष्ठा uvc_device *dev, काष्ठा uvc_entity *entity,
			u8 cs, u8 *caps);
	पूर्णांक (*get_cur)(काष्ठा uvc_device *dev, काष्ठा uvc_entity *entity,
		       u8 cs, व्योम *data, u16 size);

	अचिन्हित पूर्णांक ncontrols;
	काष्ठा uvc_control *controls;
पूर्ण;

काष्ठा uvc_frame अणु
	u8  bFrameIndex;
	u8  bmCapabilities;
	u16 wWidth;
	u16 wHeight;
	u32 dwMinBitRate;
	u32 dwMaxBitRate;
	u32 dwMaxVideoFrameBufferSize;
	u8  bFrameIntervalType;
	u32 dwDefaultFrameInterval;
	u32 *dwFrameInterval;
पूर्ण;

काष्ठा uvc_क्रमmat अणु
	u8 type;
	u8 index;
	u8 bpp;
	क्रमागत v4l2_colorspace colorspace;
	क्रमागत v4l2_xfer_func xfer_func;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	u32 fcc;
	u32 flags;

	अक्षर name[32];

	अचिन्हित पूर्णांक nframes;
	काष्ठा uvc_frame *frame;
पूर्ण;

काष्ठा uvc_streaming_header अणु
	u8 bNumFormats;
	u8 bEndpoपूर्णांकAddress;
	u8 bTerminalLink;
	u8 bControlSize;
	u8 *bmaControls;
	/* The following fields are used by input headers only. */
	u8 bmInfo;
	u8 bStillCaptureMethod;
	u8 bTriggerSupport;
	u8 bTriggerUsage;
पूर्ण;

क्रमागत uvc_buffer_state अणु
	UVC_BUF_STATE_IDLE	= 0,
	UVC_BUF_STATE_QUEUED	= 1,
	UVC_BUF_STATE_ACTIVE	= 2,
	UVC_BUF_STATE_READY	= 3,
	UVC_BUF_STATE_DONE	= 4,
	UVC_BUF_STATE_ERROR	= 5,
पूर्ण;

काष्ठा uvc_buffer अणु
	काष्ठा vb2_v4l2_buffer buf;
	काष्ठा list_head queue;

	क्रमागत uvc_buffer_state state;
	अचिन्हित पूर्णांक error;

	व्योम *mem;
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक bytesused;

	u32 pts;

	/* Asynchronous buffer handling. */
	काष्ठा kref ref;
पूर्ण;

#घोषणा UVC_QUEUE_DISCONNECTED		(1 << 0)
#घोषणा UVC_QUEUE_DROP_CORRUPTED	(1 << 1)

काष्ठा uvc_video_queue अणु
	काष्ठा vb2_queue queue;
	काष्ठा mutex mutex;			/* Protects queue */

	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक buf_used;

	spinlock_t irqlock;			/* Protects irqqueue */
	काष्ठा list_head irqqueue;
पूर्ण;

काष्ठा uvc_video_chain अणु
	काष्ठा uvc_device *dev;
	काष्ठा list_head list;

	काष्ठा list_head entities;		/* All entities */
	काष्ठा uvc_entity *processing;		/* Processing unit */
	काष्ठा uvc_entity *selector;		/* Selector unit */

	काष्ठा mutex ctrl_mutex;		/* Protects ctrl.info */

	काष्ठा v4l2_prio_state prio;		/* V4L2 priority state */
	u32 caps;				/* V4L2 chain-wide caps */
पूर्ण;

काष्ठा uvc_stats_frame अणु
	अचिन्हित पूर्णांक size;		/* Number of bytes captured */
	अचिन्हित पूर्णांक first_data;	/* Index of the first non-empty packet */

	अचिन्हित पूर्णांक nb_packets;	/* Number of packets */
	अचिन्हित पूर्णांक nb_empty;		/* Number of empty packets */
	अचिन्हित पूर्णांक nb_invalid;	/* Number of packets with an invalid header */
	अचिन्हित पूर्णांक nb_errors;		/* Number of packets with the error bit set */

	अचिन्हित पूर्णांक nb_pts;		/* Number of packets with a PTS बारtamp */
	अचिन्हित पूर्णांक nb_pts_dअगरfs;	/* Number of PTS dअगरferences inside a frame */
	अचिन्हित पूर्णांक last_pts_dअगरf;	/* Index of the last PTS dअगरference */
	bool has_initial_pts;		/* Whether the first non-empty packet has a PTS */
	bool has_early_pts;		/* Whether a PTS is present beक्रमe the first non-empty packet */
	u32 pts;			/* PTS of the last packet */

	अचिन्हित पूर्णांक nb_scr;		/* Number of packets with a SCR बारtamp */
	अचिन्हित पूर्णांक nb_scr_dअगरfs;	/* Number of SCR.STC dअगरferences inside a frame */
	u16 scr_sof;			/* SCR.SOF of the last packet */
	u32 scr_stc;			/* SCR.STC of the last packet */
पूर्ण;

काष्ठा uvc_stats_stream अणु
	kसमय_प्रकार start_ts;		/* Stream start बारtamp */
	kसमय_प्रकार stop_ts;		/* Stream stop बारtamp */

	अचिन्हित पूर्णांक nb_frames;		/* Number of frames */

	अचिन्हित पूर्णांक nb_packets;	/* Number of packets */
	अचिन्हित पूर्णांक nb_empty;		/* Number of empty packets */
	अचिन्हित पूर्णांक nb_invalid;	/* Number of packets with an invalid header */
	अचिन्हित पूर्णांक nb_errors;		/* Number of packets with the error bit set */

	अचिन्हित पूर्णांक nb_pts_स्थिरant;	/* Number of frames with स्थिरant PTS */
	अचिन्हित पूर्णांक nb_pts_early;	/* Number of frames with early PTS */
	अचिन्हित पूर्णांक nb_pts_initial;	/* Number of frames with initial PTS */

	अचिन्हित पूर्णांक nb_scr_count_ok;	/* Number of frames with at least one SCR per non empty packet */
	अचिन्हित पूर्णांक nb_scr_dअगरfs_ok;	/* Number of frames with varying SCR.STC */
	अचिन्हित पूर्णांक scr_sof_count;	/* STC.SOF counter accumulated since stream start */
	अचिन्हित पूर्णांक scr_sof;		/* STC.SOF of the last packet */
	अचिन्हित पूर्णांक min_sof;		/* Minimum STC.SOF value */
	अचिन्हित पूर्णांक max_sof;		/* Maximum STC.SOF value */
पूर्ण;

#घोषणा UVC_METADATA_BUF_SIZE 1024

/**
 * काष्ठा uvc_copy_op: Context काष्ठाure to schedule asynchronous स_नकल
 *
 * @buf: active buf object क्रम this operation
 * @dst: copy destination address
 * @src: copy source address
 * @len: copy length
 */
काष्ठा uvc_copy_op अणु
	काष्ठा uvc_buffer *buf;
	व्योम *dst;
	स्थिर __u8 *src;
	माप_प्रकार len;
पूर्ण;

/**
 * काष्ठा uvc_urb - URB context management काष्ठाure
 *
 * @urb: the URB described by this context काष्ठाure
 * @stream: UVC streaming context
 * @buffer: memory storage क्रम the URB
 * @dma: Allocated DMA handle
 * @sgt: sgt_table with the urb locations in memory
 * @async_operations: counter to indicate the number of copy operations
 * @copy_operations: work descriptors क्रम asynchronous copy operations
 * @work: work queue entry क्रम asynchronous decode
 */
काष्ठा uvc_urb अणु
	काष्ठा urb *urb;
	काष्ठा uvc_streaming *stream;

	अक्षर *buffer;
	dma_addr_t dma;
	काष्ठा sg_table *sgt;

	अचिन्हित पूर्णांक async_operations;
	काष्ठा uvc_copy_op copy_operations[UVC_MAX_PACKETS];
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा uvc_streaming अणु
	काष्ठा list_head list;
	काष्ठा uvc_device *dev;
	काष्ठा video_device vdev;
	काष्ठा uvc_video_chain *chain;
	atomic_t active;

	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक पूर्णांकfnum;
	u16 maxpsize;

	काष्ठा uvc_streaming_header header;
	क्रमागत v4l2_buf_type type;

	अचिन्हित पूर्णांक nक्रमmats;
	काष्ठा uvc_क्रमmat *क्रमmat;

	काष्ठा uvc_streaming_control ctrl;
	काष्ठा uvc_क्रमmat *def_क्रमmat;
	काष्ठा uvc_क्रमmat *cur_क्रमmat;
	काष्ठा uvc_frame *cur_frame;

	/* Protect access to ctrl, cur_क्रमmat, cur_frame and hardware video
	 * probe control.
	 */
	काष्ठा mutex mutex;

	/* Buffers queue. */
	अचिन्हित पूर्णांक frozen : 1;
	काष्ठा uvc_video_queue queue;
	काष्ठा workqueue_काष्ठा *async_wq;
	व्योम (*decode)(काष्ठा uvc_urb *uvc_urb, काष्ठा uvc_buffer *buf,
		       काष्ठा uvc_buffer *meta_buf);

	काष्ठा अणु
		काष्ठा video_device vdev;
		काष्ठा uvc_video_queue queue;
		u32 क्रमmat;
	पूर्ण meta;

	/* Context data used by the bulk completion handler. */
	काष्ठा अणु
		u8 header[256];
		अचिन्हित पूर्णांक header_size;
		पूर्णांक skip_payload;
		u32 payload_size;
		u32 max_payload_size;
	पूर्ण bulk;

	काष्ठा uvc_urb uvc_urb[UVC_URBS];
	अचिन्हित पूर्णांक urb_size;

	u32 sequence;
	u8 last_fid;

	/* debugfs */
	काष्ठा dentry *debugfs_dir;
	काष्ठा अणु
		काष्ठा uvc_stats_frame frame;
		काष्ठा uvc_stats_stream stream;
	पूर्ण stats;

	/* Timestamps support. */
	काष्ठा uvc_घड़ी अणु
		काष्ठा uvc_घड़ी_sample अणु
			u32 dev_stc;
			u16 dev_sof;
			u16 host_sof;
			kसमय_प्रकार host_समय;
		पूर्ण *samples;

		अचिन्हित पूर्णांक head;
		अचिन्हित पूर्णांक count;
		अचिन्हित पूर्णांक size;

		u16 last_sof;
		u16 sof_offset;

		u8 last_scr[6];

		spinlock_t lock;
	पूर्ण घड़ी;
पूर्ण;

#घोषणा क्रम_each_uvc_urb(uvc_urb, uvc_streaming) \
	क्रम ((uvc_urb) = &(uvc_streaming)->uvc_urb[0]; \
	     (uvc_urb) < &(uvc_streaming)->uvc_urb[UVC_URBS]; \
	     ++(uvc_urb))

अटल अंतरभूत u32 uvc_urb_index(स्थिर काष्ठा uvc_urb *uvc_urb)
अणु
	वापस uvc_urb - &uvc_urb->stream->uvc_urb[0];
पूर्ण

काष्ठा uvc_device_info अणु
	u32	quirks;
	u32	meta_क्रमmat;
	u16	uvc_version;
पूर्ण;

काष्ठा uvc_device अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	अचिन्हित दीर्घ warnings;
	u32 quirks;
	पूर्णांक पूर्णांकfnum;
	अक्षर name[32];

	स्थिर काष्ठा uvc_device_info *info;

	काष्ठा mutex lock;		/* Protects users */
	अचिन्हित पूर्णांक users;
	atomic_t nmappings;

	/* Video control पूर्णांकerface */
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device mdev;
#पूर्ण_अगर
	काष्ठा v4l2_device vdev;
	u16 uvc_version;
	u32 घड़ी_frequency;

	काष्ठा list_head entities;
	काष्ठा list_head chains;

	/* Video Streaming पूर्णांकerfaces */
	काष्ठा list_head streams;
	काष्ठा kref ref;

	/* Status Interrupt Endpoपूर्णांक */
	काष्ठा usb_host_endpoपूर्णांक *पूर्णांक_ep;
	काष्ठा urb *पूर्णांक_urb;
	u8 *status;
	काष्ठा input_dev *input;
	अक्षर input_phys[64];

	काष्ठा uvc_ctrl_work अणु
		काष्ठा work_काष्ठा work;
		काष्ठा urb *urb;
		काष्ठा uvc_video_chain *chain;
		काष्ठा uvc_control *ctrl;
		स्थिर व्योम *data;
	पूर्ण async_ctrl;

	काष्ठा uvc_entity *gpio_unit;
पूर्ण;

क्रमागत uvc_handle_state अणु
	UVC_HANDLE_PASSIVE	= 0,
	UVC_HANDLE_ACTIVE	= 1,
पूर्ण;

काष्ठा uvc_fh अणु
	काष्ठा v4l2_fh vfh;
	काष्ठा uvc_video_chain *chain;
	काष्ठा uvc_streaming *stream;
	क्रमागत uvc_handle_state state;
पूर्ण;

काष्ठा uvc_driver अणु
	काष्ठा usb_driver driver;
पूर्ण;

/* ------------------------------------------------------------------------
 * Debugging, prपूर्णांकing and logging
 */

#घोषणा UVC_DBG_PROBE		(1 << 0)
#घोषणा UVC_DBG_DESCR		(1 << 1)
#घोषणा UVC_DBG_CONTROL		(1 << 2)
#घोषणा UVC_DBG_FORMAT		(1 << 3)
#घोषणा UVC_DBG_CAPTURE		(1 << 4)
#घोषणा UVC_DBG_CALLS		(1 << 5)
#घोषणा UVC_DBG_FRAME		(1 << 7)
#घोषणा UVC_DBG_SUSPEND		(1 << 8)
#घोषणा UVC_DBG_STATUS		(1 << 9)
#घोषणा UVC_DBG_VIDEO		(1 << 10)
#घोषणा UVC_DBG_STATS		(1 << 11)
#घोषणा UVC_DBG_CLOCK		(1 << 12)

#घोषणा UVC_WARN_MINMAX		0
#घोषणा UVC_WARN_PROBE_DEF	1
#घोषणा UVC_WARN_XU_GET_RES	2

बाह्य अचिन्हित पूर्णांक uvc_घड़ी_param;
बाह्य अचिन्हित पूर्णांक uvc_no_drop_param;
बाह्य अचिन्हित पूर्णांक uvc_dbg_param;
बाह्य अचिन्हित पूर्णांक uvc_समयout_param;
बाह्य अचिन्हित पूर्णांक uvc_hw_बारtamps_param;

#घोषणा uvc_dbg(_dev, flag, fmt, ...)					\
करो अणु									\
	अगर (uvc_dbg_param & UVC_DBG_##flag)				\
		dev_prपूर्णांकk(KERN_DEBUG, &(_dev)->udev->dev, fmt,		\
			   ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा uvc_dbg_cont(flag, fmt, ...)					\
करो अणु									\
	अगर (uvc_dbg_param & UVC_DBG_##flag)				\
		pr_cont(fmt, ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा uvc_warn_once(_dev, warn, fmt, ...)				\
करो अणु									\
	अगर (!test_and_set_bit(warn, &(_dev)->warnings))			\
		dev_info(&(_dev)->udev->dev, fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

/* --------------------------------------------------------------------------
 * Internal functions.
 */

/* Core driver */
बाह्य काष्ठा uvc_driver uvc_driver;

काष्ठा uvc_entity *uvc_entity_by_id(काष्ठा uvc_device *dev, पूर्णांक id);

/* Video buffers queue management. */
पूर्णांक uvc_queue_init(काष्ठा uvc_video_queue *queue, क्रमागत v4l2_buf_type type,
		   पूर्णांक drop_corrupted);
व्योम uvc_queue_release(काष्ठा uvc_video_queue *queue);
पूर्णांक uvc_request_buffers(काष्ठा uvc_video_queue *queue,
			काष्ठा v4l2_requestbuffers *rb);
पूर्णांक uvc_query_buffer(काष्ठा uvc_video_queue *queue,
		     काष्ठा v4l2_buffer *v4l2_buf);
पूर्णांक uvc_create_buffers(काष्ठा uvc_video_queue *queue,
		       काष्ठा v4l2_create_buffers *v4l2_cb);
पूर्णांक uvc_queue_buffer(काष्ठा uvc_video_queue *queue,
		     काष्ठा media_device *mdev,
		     काष्ठा v4l2_buffer *v4l2_buf);
पूर्णांक uvc_export_buffer(काष्ठा uvc_video_queue *queue,
		      काष्ठा v4l2_exportbuffer *exp);
पूर्णांक uvc_dequeue_buffer(काष्ठा uvc_video_queue *queue,
		       काष्ठा v4l2_buffer *v4l2_buf, पूर्णांक nonblocking);
पूर्णांक uvc_queue_streamon(काष्ठा uvc_video_queue *queue, क्रमागत v4l2_buf_type type);
पूर्णांक uvc_queue_streamoff(काष्ठा uvc_video_queue *queue, क्रमागत v4l2_buf_type type);
व्योम uvc_queue_cancel(काष्ठा uvc_video_queue *queue, पूर्णांक disconnect);
काष्ठा uvc_buffer *uvc_queue_next_buffer(काष्ठा uvc_video_queue *queue,
					 काष्ठा uvc_buffer *buf);
काष्ठा uvc_buffer *uvc_queue_get_current_buffer(काष्ठा uvc_video_queue *queue);
व्योम uvc_queue_buffer_release(काष्ठा uvc_buffer *buf);
पूर्णांक uvc_queue_mmap(काष्ठा uvc_video_queue *queue,
		   काष्ठा vm_area_काष्ठा *vma);
__poll_t uvc_queue_poll(काष्ठा uvc_video_queue *queue, काष्ठा file *file,
			poll_table *रुको);
#अगर_अघोषित CONFIG_MMU
अचिन्हित दीर्घ uvc_queue_get_unmapped_area(काष्ठा uvc_video_queue *queue,
					  अचिन्हित दीर्घ pgoff);
#पूर्ण_अगर
पूर्णांक uvc_queue_allocated(काष्ठा uvc_video_queue *queue);
अटल अंतरभूत पूर्णांक uvc_queue_streaming(काष्ठा uvc_video_queue *queue)
अणु
	वापस vb2_is_streaming(&queue->queue);
पूर्ण

अटल अंतरभूत काष्ठा uvc_streaming *
uvc_queue_to_stream(काष्ठा uvc_video_queue *queue)
अणु
	वापस container_of(queue, काष्ठा uvc_streaming, queue);
पूर्ण

/* V4L2 पूर्णांकerface */
बाह्य स्थिर काष्ठा v4l2_ioctl_ops uvc_ioctl_ops;
बाह्य स्थिर काष्ठा v4l2_file_operations uvc_fops;

/* Media controller */
पूर्णांक uvc_mc_रेजिस्टर_entities(काष्ठा uvc_video_chain *chain);
व्योम uvc_mc_cleanup_entity(काष्ठा uvc_entity *entity);

/* Video */
पूर्णांक uvc_video_init(काष्ठा uvc_streaming *stream);
पूर्णांक uvc_video_suspend(काष्ठा uvc_streaming *stream);
पूर्णांक uvc_video_resume(काष्ठा uvc_streaming *stream, पूर्णांक reset);
पूर्णांक uvc_video_start_streaming(काष्ठा uvc_streaming *stream);
व्योम uvc_video_stop_streaming(काष्ठा uvc_streaming *stream);
पूर्णांक uvc_probe_video(काष्ठा uvc_streaming *stream,
		    काष्ठा uvc_streaming_control *probe);
पूर्णांक uvc_query_ctrl(काष्ठा uvc_device *dev, u8 query, u8 unit,
		   u8 पूर्णांकfnum, u8 cs, व्योम *data, u16 size);
व्योम uvc_video_घड़ी_update(काष्ठा uvc_streaming *stream,
			    काष्ठा vb2_v4l2_buffer *vbuf,
			    काष्ठा uvc_buffer *buf);
पूर्णांक uvc_meta_रेजिस्टर(काष्ठा uvc_streaming *stream);

पूर्णांक uvc_रेजिस्टर_video_device(काष्ठा uvc_device *dev,
			      काष्ठा uvc_streaming *stream,
			      काष्ठा video_device *vdev,
			      काष्ठा uvc_video_queue *queue,
			      क्रमागत v4l2_buf_type type,
			      स्थिर काष्ठा v4l2_file_operations *fops,
			      स्थिर काष्ठा v4l2_ioctl_ops *ioctl_ops);

/* Status */
पूर्णांक uvc_status_init(काष्ठा uvc_device *dev);
व्योम uvc_status_unरेजिस्टर(काष्ठा uvc_device *dev);
व्योम uvc_status_cleanup(काष्ठा uvc_device *dev);
पूर्णांक uvc_status_start(काष्ठा uvc_device *dev, gfp_t flags);
व्योम uvc_status_stop(काष्ठा uvc_device *dev);

/* Controls */
बाह्य स्थिर काष्ठा v4l2_subscribed_event_ops uvc_ctrl_sub_ev_ops;

पूर्णांक uvc_query_v4l2_ctrl(काष्ठा uvc_video_chain *chain,
			काष्ठा v4l2_queryctrl *v4l2_ctrl);
पूर्णांक uvc_query_v4l2_menu(काष्ठा uvc_video_chain *chain,
			काष्ठा v4l2_querymenu *query_menu);

पूर्णांक uvc_ctrl_add_mapping(काष्ठा uvc_video_chain *chain,
			 स्थिर काष्ठा uvc_control_mapping *mapping);
पूर्णांक uvc_ctrl_init_device(काष्ठा uvc_device *dev);
व्योम uvc_ctrl_cleanup_device(काष्ठा uvc_device *dev);
पूर्णांक uvc_ctrl_restore_values(काष्ठा uvc_device *dev);
bool uvc_ctrl_status_event_async(काष्ठा urb *urb, काष्ठा uvc_video_chain *chain,
				 काष्ठा uvc_control *ctrl, स्थिर u8 *data);
व्योम uvc_ctrl_status_event(काष्ठा uvc_video_chain *chain,
			   काष्ठा uvc_control *ctrl, स्थिर u8 *data);

पूर्णांक uvc_ctrl_begin(काष्ठा uvc_video_chain *chain);
पूर्णांक __uvc_ctrl_commit(काष्ठा uvc_fh *handle, पूर्णांक rollback,
		      स्थिर काष्ठा v4l2_ext_control *xctrls,
		      अचिन्हित पूर्णांक xctrls_count);
अटल अंतरभूत पूर्णांक uvc_ctrl_commit(काष्ठा uvc_fh *handle,
				  स्थिर काष्ठा v4l2_ext_control *xctrls,
				  अचिन्हित पूर्णांक xctrls_count)
अणु
	वापस __uvc_ctrl_commit(handle, 0, xctrls, xctrls_count);
पूर्ण
अटल अंतरभूत पूर्णांक uvc_ctrl_rollback(काष्ठा uvc_fh *handle)
अणु
	वापस __uvc_ctrl_commit(handle, 1, शून्य, 0);
पूर्ण

पूर्णांक uvc_ctrl_get(काष्ठा uvc_video_chain *chain, काष्ठा v4l2_ext_control *xctrl);
पूर्णांक uvc_ctrl_set(काष्ठा uvc_fh *handle, काष्ठा v4l2_ext_control *xctrl);

पूर्णांक uvc_xu_ctrl_query(काष्ठा uvc_video_chain *chain,
		      काष्ठा uvc_xu_control_query *xqry);

/* Utility functions */
व्योम uvc_simplअगरy_fraction(u32 *numerator, u32 *denominator,
			   अचिन्हित पूर्णांक n_terms, अचिन्हित पूर्णांक threshold);
u32 uvc_fraction_to_पूर्णांकerval(u32 numerator, u32 denominator);
काष्ठा usb_host_endpoपूर्णांक *uvc_find_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *alts,
					    u8 epaddr);

/* Quirks support */
व्योम uvc_video_decode_isight(काष्ठा uvc_urb *uvc_urb,
			     काष्ठा uvc_buffer *buf,
			     काष्ठा uvc_buffer *meta_buf);

/* debugfs and statistics */
व्योम uvc_debugfs_init(व्योम);
व्योम uvc_debugfs_cleanup(व्योम);
व्योम uvc_debugfs_init_stream(काष्ठा uvc_streaming *stream);
व्योम uvc_debugfs_cleanup_stream(काष्ठा uvc_streaming *stream);

माप_प्रकार uvc_video_stats_dump(काष्ठा uvc_streaming *stream, अक्षर *buf,
			    माप_प्रकार size);

#पूर्ण_अगर

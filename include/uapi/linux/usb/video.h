<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * USB Video Class definitions.
 *
 * Copyright (C) 2009 Laurent Pinअक्षरt <laurent.pinअक्षरt@skynet.be>
 *
 * This file holds USB स्थिरants and काष्ठाures defined by the USB Device
 * Class Definition क्रम Video Devices. Unless otherwise stated, comments
 * below reference relevant sections of the USB Video Class 1.1 specअगरication
 * available at
 *
 * http://www.usb.org/developers/devclass_करोcs/USB_Video_Class_1_1.zip
 */

#अगर_अघोषित __LINUX_USB_VIDEO_H
#घोषणा __LINUX_USB_VIDEO_H

#समावेश <linux/types.h>

/* --------------------------------------------------------------------------
 * UVC स्थिरants
 */

/* A.2. Video Interface Subclass Codes */
#घोषणा UVC_SC_UNDEFINED				0x00
#घोषणा UVC_SC_VIDEOCONTROL				0x01
#घोषणा UVC_SC_VIDEOSTREAMING				0x02
#घोषणा UVC_SC_VIDEO_INTERFACE_COLLECTION		0x03

/* A.3. Video Interface Protocol Codes */
#घोषणा UVC_PC_PROTOCOL_UNDEFINED			0x00
#घोषणा UVC_PC_PROTOCOL_15				0x01

/* A.5. Video Class-Specअगरic VC Interface Descriptor Subtypes */
#घोषणा UVC_VC_DESCRIPTOR_UNDEFINED			0x00
#घोषणा UVC_VC_HEADER					0x01
#घोषणा UVC_VC_INPUT_TERMINAL				0x02
#घोषणा UVC_VC_OUTPUT_TERMINAL				0x03
#घोषणा UVC_VC_SELECTOR_UNIT				0x04
#घोषणा UVC_VC_PROCESSING_UNIT				0x05
#घोषणा UVC_VC_EXTENSION_UNIT				0x06

/* A.6. Video Class-Specअगरic VS Interface Descriptor Subtypes */
#घोषणा UVC_VS_UNDEFINED				0x00
#घोषणा UVC_VS_INPUT_HEADER				0x01
#घोषणा UVC_VS_OUTPUT_HEADER				0x02
#घोषणा UVC_VS_STILL_IMAGE_FRAME			0x03
#घोषणा UVC_VS_FORMAT_UNCOMPRESSED			0x04
#घोषणा UVC_VS_FRAME_UNCOMPRESSED			0x05
#घोषणा UVC_VS_FORMAT_MJPEG				0x06
#घोषणा UVC_VS_FRAME_MJPEG				0x07
#घोषणा UVC_VS_FORMAT_MPEG2TS				0x0a
#घोषणा UVC_VS_FORMAT_DV				0x0c
#घोषणा UVC_VS_COLORFORMAT				0x0d
#घोषणा UVC_VS_FORMAT_FRAME_BASED			0x10
#घोषणा UVC_VS_FRAME_FRAME_BASED			0x11
#घोषणा UVC_VS_FORMAT_STREAM_BASED			0x12

/* A.7. Video Class-Specअगरic Endpoपूर्णांक Descriptor Subtypes */
#घोषणा UVC_EP_UNDEFINED				0x00
#घोषणा UVC_EP_GENERAL					0x01
#घोषणा UVC_EP_ENDPOINT					0x02
#घोषणा UVC_EP_INTERRUPT				0x03

/* A.8. Video Class-Specअगरic Request Codes */
#घोषणा UVC_RC_UNDEFINED				0x00
#घोषणा UVC_SET_CUR					0x01
#घोषणा UVC_GET_CUR					0x81
#घोषणा UVC_GET_MIN					0x82
#घोषणा UVC_GET_MAX					0x83
#घोषणा UVC_GET_RES					0x84
#घोषणा UVC_GET_LEN					0x85
#घोषणा UVC_GET_INFO					0x86
#घोषणा UVC_GET_DEF					0x87

/* A.9.1. VideoControl Interface Control Selectors */
#घोषणा UVC_VC_CONTROL_UNDEFINED			0x00
#घोषणा UVC_VC_VIDEO_POWER_MODE_CONTROL			0x01
#घोषणा UVC_VC_REQUEST_ERROR_CODE_CONTROL		0x02

/* A.9.2. Terminal Control Selectors */
#घोषणा UVC_TE_CONTROL_UNDEFINED			0x00

/* A.9.3. Selector Unit Control Selectors */
#घोषणा UVC_SU_CONTROL_UNDEFINED			0x00
#घोषणा UVC_SU_INPUT_SELECT_CONTROL			0x01

/* A.9.4. Camera Terminal Control Selectors */
#घोषणा UVC_CT_CONTROL_UNDEFINED			0x00
#घोषणा UVC_CT_SCANNING_MODE_CONTROL			0x01
#घोषणा UVC_CT_AE_MODE_CONTROL				0x02
#घोषणा UVC_CT_AE_PRIORITY_CONTROL			0x03
#घोषणा UVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL		0x04
#घोषणा UVC_CT_EXPOSURE_TIME_RELATIVE_CONTROL		0x05
#घोषणा UVC_CT_FOCUS_ABSOLUTE_CONTROL			0x06
#घोषणा UVC_CT_FOCUS_RELATIVE_CONTROL			0x07
#घोषणा UVC_CT_FOCUS_AUTO_CONTROL			0x08
#घोषणा UVC_CT_IRIS_ABSOLUTE_CONTROL			0x09
#घोषणा UVC_CT_IRIS_RELATIVE_CONTROL			0x0a
#घोषणा UVC_CT_ZOOM_ABSOLUTE_CONTROL			0x0b
#घोषणा UVC_CT_ZOOM_RELATIVE_CONTROL			0x0c
#घोषणा UVC_CT_PANTILT_ABSOLUTE_CONTROL			0x0d
#घोषणा UVC_CT_PANTILT_RELATIVE_CONTROL			0x0e
#घोषणा UVC_CT_ROLL_ABSOLUTE_CONTROL			0x0f
#घोषणा UVC_CT_ROLL_RELATIVE_CONTROL			0x10
#घोषणा UVC_CT_PRIVACY_CONTROL				0x11

/* A.9.5. Processing Unit Control Selectors */
#घोषणा UVC_PU_CONTROL_UNDEFINED			0x00
#घोषणा UVC_PU_BACKLIGHT_COMPENSATION_CONTROL		0x01
#घोषणा UVC_PU_BRIGHTNESS_CONTROL			0x02
#घोषणा UVC_PU_CONTRAST_CONTROL				0x03
#घोषणा UVC_PU_GAIN_CONTROL				0x04
#घोषणा UVC_PU_POWER_LINE_FREQUENCY_CONTROL		0x05
#घोषणा UVC_PU_HUE_CONTROL				0x06
#घोषणा UVC_PU_SATURATION_CONTROL			0x07
#घोषणा UVC_PU_SHARPNESS_CONTROL			0x08
#घोषणा UVC_PU_GAMMA_CONTROL				0x09
#घोषणा UVC_PU_WHITE_BALANCE_TEMPERATURE_CONTROL	0x0a
#घोषणा UVC_PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL	0x0b
#घोषणा UVC_PU_WHITE_BALANCE_COMPONENT_CONTROL		0x0c
#घोषणा UVC_PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL	0x0d
#घोषणा UVC_PU_DIGITAL_MULTIPLIER_CONTROL		0x0e
#घोषणा UVC_PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL		0x0f
#घोषणा UVC_PU_HUE_AUTO_CONTROL				0x10
#घोषणा UVC_PU_ANALOG_VIDEO_STANDARD_CONTROL		0x11
#घोषणा UVC_PU_ANALOG_LOCK_STATUS_CONTROL		0x12

/* A.9.7. VideoStreaming Interface Control Selectors */
#घोषणा UVC_VS_CONTROL_UNDEFINED			0x00
#घोषणा UVC_VS_PROBE_CONTROL				0x01
#घोषणा UVC_VS_COMMIT_CONTROL				0x02
#घोषणा UVC_VS_STILL_PROBE_CONTROL			0x03
#घोषणा UVC_VS_STILL_COMMIT_CONTROL			0x04
#घोषणा UVC_VS_STILL_IMAGE_TRIGGER_CONTROL		0x05
#घोषणा UVC_VS_STREAM_ERROR_CODE_CONTROL		0x06
#घोषणा UVC_VS_GENERATE_KEY_FRAME_CONTROL		0x07
#घोषणा UVC_VS_UPDATE_FRAME_SEGMENT_CONTROL		0x08
#घोषणा UVC_VS_SYNC_DELAY_CONTROL			0x09

/* B.1. USB Terminal Types */
#घोषणा UVC_TT_VENDOR_SPECIFIC				0x0100
#घोषणा UVC_TT_STREAMING				0x0101

/* B.2. Input Terminal Types */
#घोषणा UVC_ITT_VENDOR_SPECIFIC				0x0200
#घोषणा UVC_ITT_CAMERA					0x0201
#घोषणा UVC_ITT_MEDIA_TRANSPORT_INPUT			0x0202

/* B.3. Output Terminal Types */
#घोषणा UVC_OTT_VENDOR_SPECIFIC				0x0300
#घोषणा UVC_OTT_DISPLAY					0x0301
#घोषणा UVC_OTT_MEDIA_TRANSPORT_OUTPUT			0x0302

/* B.4. External Terminal Types */
#घोषणा UVC_EXTERNAL_VENDOR_SPECIFIC			0x0400
#घोषणा UVC_COMPOSITE_CONNECTOR				0x0401
#घोषणा UVC_SVIDEO_CONNECTOR				0x0402
#घोषणा UVC_COMPONENT_CONNECTOR				0x0403

/* 2.4.2.2. Status Packet Type */
#घोषणा UVC_STATUS_TYPE_CONTROL				1
#घोषणा UVC_STATUS_TYPE_STREAMING			2

/* 2.4.3.3. Payload Header Inक्रमmation */
#घोषणा UVC_STREAM_EOH					(1 << 7)
#घोषणा UVC_STREAM_ERR					(1 << 6)
#घोषणा UVC_STREAM_STI					(1 << 5)
#घोषणा UVC_STREAM_RES					(1 << 4)
#घोषणा UVC_STREAM_SCR					(1 << 3)
#घोषणा UVC_STREAM_PTS					(1 << 2)
#घोषणा UVC_STREAM_खातापूर्ण					(1 << 1)
#घोषणा UVC_STREAM_FID					(1 << 0)

/* 4.1.2. Control Capabilities */
#घोषणा UVC_CONTROL_CAP_GET				(1 << 0)
#घोषणा UVC_CONTROL_CAP_SET				(1 << 1)
#घोषणा UVC_CONTROL_CAP_DISABLED			(1 << 2)
#घोषणा UVC_CONTROL_CAP_AUTOUPDATE			(1 << 3)
#घोषणा UVC_CONTROL_CAP_ASYNCHRONOUS			(1 << 4)

/* ------------------------------------------------------------------------
 * UVC काष्ठाures
 */

/* All UVC descriptors have these 3 fields at the beginning */
काष्ठा uvc_descriptor_header अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDescriptorSubType;
पूर्ण __attribute__((packed));

/* 3.7.2. Video Control Interface Header Descriptor */
काष्ठा uvc_header_descriptor अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__le16 bcdUVC;
	__le16 wTotalLength;
	__le32 dwClockFrequency;
	__u8   bInCollection;
	__u8   baInterfaceNr[];
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_HEADER_SIZE(n)				(12+(n))

#घोषणा UVC_HEADER_DESCRIPTOR(n) \
	uvc_header_descriptor_##n

#घोषणा DECLARE_UVC_HEADER_DESCRIPTOR(n)		\
काष्ठा UVC_HEADER_DESCRIPTOR(n) अणु			\
	__u8   bLength;					\
	__u8   bDescriptorType;				\
	__u8   bDescriptorSubType;			\
	__le16 bcdUVC;					\
	__le16 wTotalLength;				\
	__le32 dwClockFrequency;			\
	__u8   bInCollection;				\
	__u8   baInterfaceNr[n];			\
पूर्ण __attribute__ ((packed))

/* 3.7.2.1. Input Terminal Descriptor */
काष्ठा uvc_input_terminal_descriptor अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__u8   bTerminalID;
	__le16 wTerminalType;
	__u8   bAssocTerminal;
	__u8   iTerminal;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_INPUT_TERMINAL_SIZE			8

/* 3.7.2.2. Output Terminal Descriptor */
काष्ठा uvc_output_terminal_descriptor अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__u8   bTerminalID;
	__le16 wTerminalType;
	__u8   bAssocTerminal;
	__u8   bSourceID;
	__u8   iTerminal;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_OUTPUT_TERMINAL_SIZE			9

/* 3.7.2.3. Camera Terminal Descriptor */
काष्ठा uvc_camera_terminal_descriptor अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__u8   bTerminalID;
	__le16 wTerminalType;
	__u8   bAssocTerminal;
	__u8   iTerminal;
	__le16 wObjectiveFocalLengthMin;
	__le16 wObjectiveFocalLengthMax;
	__le16 wOcularFocalLength;
	__u8   bControlSize;
	__u8   bmControls[3];
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_CAMERA_TERMINAL_SIZE(n)			(15+(n))

/* 3.7.2.4. Selector Unit Descriptor */
काष्ठा uvc_selector_unit_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDescriptorSubType;
	__u8  bUnitID;
	__u8  bNrInPins;
	__u8  baSourceID[0];
	__u8  iSelector;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_SELECTOR_UNIT_SIZE(n)			(6+(n))

#घोषणा UVC_SELECTOR_UNIT_DESCRIPTOR(n)	\
	uvc_selector_unit_descriptor_##n

#घोषणा DECLARE_UVC_SELECTOR_UNIT_DESCRIPTOR(n)	\
काष्ठा UVC_SELECTOR_UNIT_DESCRIPTOR(n) अणु		\
	__u8  bLength;					\
	__u8  bDescriptorType;				\
	__u8  bDescriptorSubType;			\
	__u8  bUnitID;					\
	__u8  bNrInPins;				\
	__u8  baSourceID[n];				\
	__u8  iSelector;				\
पूर्ण __attribute__ ((packed))

/* 3.7.2.5. Processing Unit Descriptor */
काष्ठा uvc_processing_unit_descriptor अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__u8   bUnitID;
	__u8   bSourceID;
	__le16 wMaxMultiplier;
	__u8   bControlSize;
	__u8   bmControls[2];
	__u8   iProcessing;
	__u8   bmVideoStandards;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_PROCESSING_UNIT_SIZE(n)			(10+(n))

/* 3.7.2.6. Extension Unit Descriptor */
काष्ठा uvc_extension_unit_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDescriptorSubType;
	__u8  bUnitID;
	__u8  guidExtensionCode[16];
	__u8  bNumControls;
	__u8  bNrInPins;
	__u8  baSourceID[0];
	__u8  bControlSize;
	__u8  bmControls[0];
	__u8  iExtension;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_EXTENSION_UNIT_SIZE(p, n)		(24+(p)+(n))

#घोषणा UVC_EXTENSION_UNIT_DESCRIPTOR(p, n) \
	uvc_extension_unit_descriptor_##p_##n

#घोषणा DECLARE_UVC_EXTENSION_UNIT_DESCRIPTOR(p, n)	\
काष्ठा UVC_EXTENSION_UNIT_DESCRIPTOR(p, n) अणु		\
	__u8  bLength;					\
	__u8  bDescriptorType;				\
	__u8  bDescriptorSubType;			\
	__u8  bUnitID;					\
	__u8  guidExtensionCode[16];			\
	__u8  bNumControls;				\
	__u8  bNrInPins;				\
	__u8  baSourceID[p];				\
	__u8  bControlSize;				\
	__u8  bmControls[n];				\
	__u8  iExtension;				\
पूर्ण __attribute__ ((packed))

/* 3.8.2.2. Video Control Interrupt Endpoपूर्णांक Descriptor */
काष्ठा uvc_control_endpoपूर्णांक_descriptor अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__le16 wMaxTransferSize;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_CONTROL_ENDPOINT_SIZE			5

/* 3.9.2.1. Input Header Descriptor */
काष्ठा uvc_input_header_descriptor अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__u8   bNumFormats;
	__le16 wTotalLength;
	__u8   bEndpoपूर्णांकAddress;
	__u8   bmInfo;
	__u8   bTerminalLink;
	__u8   bStillCaptureMethod;
	__u8   bTriggerSupport;
	__u8   bTriggerUsage;
	__u8   bControlSize;
	__u8   bmaControls[];
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_INPUT_HEADER_SIZE(n, p)			(13+(n*p))

#घोषणा UVC_INPUT_HEADER_DESCRIPTOR(n, p) \
	uvc_input_header_descriptor_##n_##p

#घोषणा DECLARE_UVC_INPUT_HEADER_DESCRIPTOR(n, p)	\
काष्ठा UVC_INPUT_HEADER_DESCRIPTOR(n, p) अणु		\
	__u8   bLength;					\
	__u8   bDescriptorType;				\
	__u8   bDescriptorSubType;			\
	__u8   bNumFormats;				\
	__le16 wTotalLength;				\
	__u8   bEndpoपूर्णांकAddress;			\
	__u8   bmInfo;					\
	__u8   bTerminalLink;				\
	__u8   bStillCaptureMethod;			\
	__u8   bTriggerSupport;				\
	__u8   bTriggerUsage;				\
	__u8   bControlSize;				\
	__u8   bmaControls[p][n];			\
पूर्ण __attribute__ ((packed))

/* 3.9.2.2. Output Header Descriptor */
काष्ठा uvc_output_header_descriptor अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__u8   bNumFormats;
	__le16 wTotalLength;
	__u8   bEndpoपूर्णांकAddress;
	__u8   bTerminalLink;
	__u8   bControlSize;
	__u8   bmaControls[];
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_OUTPUT_HEADER_SIZE(n, p)			(9+(n*p))

#घोषणा UVC_OUTPUT_HEADER_DESCRIPTOR(n, p) \
	uvc_output_header_descriptor_##n_##p

#घोषणा DECLARE_UVC_OUTPUT_HEADER_DESCRIPTOR(n, p)	\
काष्ठा UVC_OUTPUT_HEADER_DESCRIPTOR(n, p) अणु		\
	__u8   bLength;					\
	__u8   bDescriptorType;				\
	__u8   bDescriptorSubType;			\
	__u8   bNumFormats;				\
	__le16 wTotalLength;				\
	__u8   bEndpoपूर्णांकAddress;			\
	__u8   bTerminalLink;				\
	__u8   bControlSize;				\
	__u8   bmaControls[p][n];			\
पूर्ण __attribute__ ((packed))

/* 3.9.2.6. Color matching descriptor */
काष्ठा uvc_color_matching_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDescriptorSubType;
	__u8  bColorPrimaries;
	__u8  bTransferCharacteristics;
	__u8  bMatrixCoefficients;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_COLOR_MATCHING_SIZE			6

/* 4.3.1.1. Video Probe and Commit Controls */
काष्ठा uvc_streaming_control अणु
	__u16 bmHपूर्णांक;
	__u8  bFormatIndex;
	__u8  bFrameIndex;
	__u32 dwFrameInterval;
	__u16 wKeyFrameRate;
	__u16 wPFrameRate;
	__u16 wCompQuality;
	__u16 wCompWinकरोwSize;
	__u16 wDelay;
	__u32 dwMaxVideoFrameSize;
	__u32 dwMaxPayloadTransferSize;
	__u32 dwClockFrequency;
	__u8  bmFramingInfo;
	__u8  bPreferedVersion;
	__u8  bMinVersion;
	__u8  bMaxVersion;
पूर्ण __attribute__((__packed__));

/* Uncompressed Payload - 3.1.1. Uncompressed Video Format Descriptor */
काष्ठा uvc_क्रमmat_uncompressed अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDescriptorSubType;
	__u8  bFormatIndex;
	__u8  bNumFrameDescriptors;
	__u8  guidFormat[16];
	__u8  bBitsPerPixel;
	__u8  bDefaultFrameIndex;
	__u8  bAspectRatioX;
	__u8  bAspectRatioY;
	__u8  bmInterfaceFlags;
	__u8  bCopyProtect;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_FORMAT_UNCOMPRESSED_SIZE			27

/* Uncompressed Payload - 3.1.2. Uncompressed Video Frame Descriptor */
काष्ठा uvc_frame_uncompressed अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__u8   bFrameIndex;
	__u8   bmCapabilities;
	__le16 wWidth;
	__le16 wHeight;
	__le32 dwMinBitRate;
	__le32 dwMaxBitRate;
	__le32 dwMaxVideoFrameBufferSize;
	__le32 dwDefaultFrameInterval;
	__u8   bFrameIntervalType;
	__le32 dwFrameInterval[];
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_FRAME_UNCOMPRESSED_SIZE(n)		(26+4*(n))

#घोषणा UVC_FRAME_UNCOMPRESSED(n) \
	uvc_frame_uncompressed_##n

#घोषणा DECLARE_UVC_FRAME_UNCOMPRESSED(n)		\
काष्ठा UVC_FRAME_UNCOMPRESSED(n) अणु			\
	__u8   bLength;					\
	__u8   bDescriptorType;				\
	__u8   bDescriptorSubType;			\
	__u8   bFrameIndex;				\
	__u8   bmCapabilities;				\
	__le16 wWidth;					\
	__le16 wHeight;					\
	__le32 dwMinBitRate;				\
	__le32 dwMaxBitRate;				\
	__le32 dwMaxVideoFrameBufferSize;		\
	__le32 dwDefaultFrameInterval;			\
	__u8   bFrameIntervalType;			\
	__le32 dwFrameInterval[n];			\
पूर्ण __attribute__ ((packed))

/* MJPEG Payload - 3.1.1. MJPEG Video Format Descriptor */
काष्ठा uvc_क्रमmat_mjpeg अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDescriptorSubType;
	__u8  bFormatIndex;
	__u8  bNumFrameDescriptors;
	__u8  bmFlags;
	__u8  bDefaultFrameIndex;
	__u8  bAspectRatioX;
	__u8  bAspectRatioY;
	__u8  bmInterfaceFlags;
	__u8  bCopyProtect;
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_FORMAT_MJPEG_SIZE			11

/* MJPEG Payload - 3.1.2. MJPEG Video Frame Descriptor */
काष्ठा uvc_frame_mjpeg अणु
	__u8   bLength;
	__u8   bDescriptorType;
	__u8   bDescriptorSubType;
	__u8   bFrameIndex;
	__u8   bmCapabilities;
	__le16 wWidth;
	__le16 wHeight;
	__le32 dwMinBitRate;
	__le32 dwMaxBitRate;
	__le32 dwMaxVideoFrameBufferSize;
	__le32 dwDefaultFrameInterval;
	__u8   bFrameIntervalType;
	__le32 dwFrameInterval[];
पूर्ण __attribute__((__packed__));

#घोषणा UVC_DT_FRAME_MJPEG_SIZE(n)			(26+4*(n))

#घोषणा UVC_FRAME_MJPEG(n) \
	uvc_frame_mjpeg_##n

#घोषणा DECLARE_UVC_FRAME_MJPEG(n)			\
काष्ठा UVC_FRAME_MJPEG(n) अणु				\
	__u8   bLength;					\
	__u8   bDescriptorType;				\
	__u8   bDescriptorSubType;			\
	__u8   bFrameIndex;				\
	__u8   bmCapabilities;				\
	__le16 wWidth;					\
	__le16 wHeight;					\
	__le32 dwMinBitRate;				\
	__le32 dwMaxBitRate;				\
	__le32 dwMaxVideoFrameBufferSize;		\
	__le32 dwDefaultFrameInterval;			\
	__u8   bFrameIntervalType;			\
	__le32 dwFrameInterval[n];			\
पूर्ण __attribute__ ((packed))

#पूर्ण_अगर /* __LINUX_USB_VIDEO_H */


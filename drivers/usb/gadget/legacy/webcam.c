<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	webcam.c -- USB webcam gadget driver
 *
 *	Copyright (C) 2009-2010
 *	    Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/video.h>

#समावेश "u_uvc.h"

USB_GADGET_COMPOSITE_OPTIONS();

/*-------------------------------------------------------------------------*/

/* module parameters specअगरic to the Video streaming endpoपूर्णांक */
अटल अचिन्हित पूर्णांक streaming_पूर्णांकerval = 1;
module_param(streaming_पूर्णांकerval, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(streaming_पूर्णांकerval, "1 - 16");

अटल अचिन्हित पूर्णांक streaming_maxpacket = 1024;
module_param(streaming_maxpacket, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(streaming_maxpacket, "1 - 1023 (FS), 1 - 3072 (hs/ss)");

अटल अचिन्हित पूर्णांक streaming_maxburst;
module_param(streaming_maxburst, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(streaming_maxburst, "0 - 15 (ss only)");

/* --------------------------------------------------------------------------
 * Device descriptor
 */

#घोषणा WEBCAM_VENDOR_ID		0x1d6b	/* Linux Foundation */
#घोषणा WEBCAM_PRODUCT_ID		0x0102	/* Webcam A/V gadget */
#घोषणा WEBCAM_DEVICE_BCD		0x0010	/* 0.10 */

अटल अक्षर webcam_venकरोr_label[] = "Linux Foundation";
अटल अक्षर webcam_product_label[] = "Webcam gadget";
अटल अक्षर webcam_config_label[] = "Video";

/* string IDs are asचिन्हित dynamically */

#घोषणा STRING_DESCRIPTION_IDX		USB_GADGET_FIRST_AVAIL_IDX

अटल काष्ठा usb_string webcam_strings[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = webcam_venकरोr_label,
	[USB_GADGET_PRODUCT_IDX].s = webcam_product_label,
	[USB_GADGET_SERIAL_IDX].s = "",
	[STRING_DESCRIPTION_IDX].s = webcam_config_label,
	अणु  पूर्ण
पूर्ण;

अटल काष्ठा usb_gadget_strings webcam_stringtab = अणु
	.language = 0x0409,	/* en-us */
	.strings = webcam_strings,
पूर्ण;

अटल काष्ठा usb_gadget_strings *webcam_device_strings[] = अणु
	&webcam_stringtab,
	शून्य,
पूर्ण;

अटल काष्ठा usb_function_instance *fi_uvc;
अटल काष्ठा usb_function *f_uvc;

अटल काष्ठा usb_device_descriptor webcam_device_descriptor = अणु
	.bLength		= USB_DT_DEVICE_SIZE,
	.bDescriptorType	= USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceClass		= USB_CLASS_MISC,
	.bDeviceSubClass	= 0x02,
	.bDeviceProtocol	= 0x01,
	.bMaxPacketSize0	= 0, /* dynamic */
	.idVenकरोr		= cpu_to_le16(WEBCAM_VENDOR_ID),
	.idProduct		= cpu_to_le16(WEBCAM_PRODUCT_ID),
	.bcdDevice		= cpu_to_le16(WEBCAM_DEVICE_BCD),
	.iManufacturer		= 0, /* dynamic */
	.iProduct		= 0, /* dynamic */
	.iSerialNumber		= 0, /* dynamic */
	.bNumConfigurations	= 0, /* dynamic */
पूर्ण;

DECLARE_UVC_HEADER_DESCRIPTOR(1);

अटल स्थिर काष्ठा UVC_HEADER_DESCRIPTOR(1) uvc_control_header = अणु
	.bLength		= UVC_DT_HEADER_SIZE(1),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VC_HEADER,
	.bcdUVC			= cpu_to_le16(0x0110),
	.wTotalLength		= 0, /* dynamic */
	.dwClockFrequency	= cpu_to_le32(48000000),
	.bInCollection		= 0, /* dynamic */
	.baInterfaceNr[0]	= 0, /* dynamic */
पूर्ण;

अटल स्थिर काष्ठा uvc_camera_terminal_descriptor uvc_camera_terminal = अणु
	.bLength		= UVC_DT_CAMERA_TERMINAL_SIZE(3),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VC_INPUT_TERMINAL,
	.bTerminalID		= 1,
	.wTerminalType		= cpu_to_le16(0x0201),
	.bAssocTerminal		= 0,
	.iTerminal		= 0,
	.wObjectiveFocalLengthMin	= cpu_to_le16(0),
	.wObjectiveFocalLengthMax	= cpu_to_le16(0),
	.wOcularFocalLength		= cpu_to_le16(0),
	.bControlSize		= 3,
	.bmControls[0]		= 2,
	.bmControls[1]		= 0,
	.bmControls[2]		= 0,
पूर्ण;

अटल स्थिर काष्ठा uvc_processing_unit_descriptor uvc_processing = अणु
	.bLength		= UVC_DT_PROCESSING_UNIT_SIZE(2),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VC_PROCESSING_UNIT,
	.bUnitID		= 2,
	.bSourceID		= 1,
	.wMaxMultiplier		= cpu_to_le16(16*1024),
	.bControlSize		= 2,
	.bmControls[0]		= 1,
	.bmControls[1]		= 0,
	.iProcessing		= 0,
	.bmVideoStandards	= 0,
पूर्ण;

अटल स्थिर काष्ठा uvc_output_terminal_descriptor uvc_output_terminal = अणु
	.bLength		= UVC_DT_OUTPUT_TERMINAL_SIZE,
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VC_OUTPUT_TERMINAL,
	.bTerminalID		= 3,
	.wTerminalType		= cpu_to_le16(0x0101),
	.bAssocTerminal		= 0,
	.bSourceID		= 2,
	.iTerminal		= 0,
पूर्ण;

DECLARE_UVC_INPUT_HEADER_DESCRIPTOR(1, 2);

अटल स्थिर काष्ठा UVC_INPUT_HEADER_DESCRIPTOR(1, 2) uvc_input_header = अणु
	.bLength		= UVC_DT_INPUT_HEADER_SIZE(1, 2),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VS_INPUT_HEADER,
	.bNumFormats		= 2,
	.wTotalLength		= 0, /* dynamic */
	.bEndpoपूर्णांकAddress	= 0, /* dynamic */
	.bmInfo			= 0,
	.bTerminalLink		= 3,
	.bStillCaptureMethod	= 0,
	.bTriggerSupport	= 0,
	.bTriggerUsage		= 0,
	.bControlSize		= 1,
	.bmaControls[0][0]	= 0,
	.bmaControls[1][0]	= 4,
पूर्ण;

अटल स्थिर काष्ठा uvc_क्रमmat_uncompressed uvc_क्रमmat_yuv = अणु
	.bLength		= UVC_DT_FORMAT_UNCOMPRESSED_SIZE,
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VS_FORMAT_UNCOMPRESSED,
	.bFormatIndex		= 1,
	.bNumFrameDescriptors	= 2,
	.guidFormat		=
		अणु 'Y',  'U',  'Y',  '2', 0x00, 0x00, 0x10, 0x00,
		 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71पूर्ण,
	.bBitsPerPixel		= 16,
	.bDefaultFrameIndex	= 1,
	.bAspectRatioX		= 0,
	.bAspectRatioY		= 0,
	.bmInterfaceFlags	= 0,
	.bCopyProtect		= 0,
पूर्ण;

DECLARE_UVC_FRAME_UNCOMPRESSED(1);
DECLARE_UVC_FRAME_UNCOMPRESSED(3);

अटल स्थिर काष्ठा UVC_FRAME_UNCOMPRESSED(3) uvc_frame_yuv_360p = अणु
	.bLength		= UVC_DT_FRAME_UNCOMPRESSED_SIZE(3),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VS_FRAME_UNCOMPRESSED,
	.bFrameIndex		= 1,
	.bmCapabilities		= 0,
	.wWidth			= cpu_to_le16(640),
	.wHeight		= cpu_to_le16(360),
	.dwMinBitRate		= cpu_to_le32(18432000),
	.dwMaxBitRate		= cpu_to_le32(55296000),
	.dwMaxVideoFrameBufferSize	= cpu_to_le32(460800),
	.dwDefaultFrameInterval	= cpu_to_le32(666666),
	.bFrameIntervalType	= 3,
	.dwFrameInterval[0]	= cpu_to_le32(666666),
	.dwFrameInterval[1]	= cpu_to_le32(1000000),
	.dwFrameInterval[2]	= cpu_to_le32(5000000),
पूर्ण;

अटल स्थिर काष्ठा UVC_FRAME_UNCOMPRESSED(1) uvc_frame_yuv_720p = अणु
	.bLength		= UVC_DT_FRAME_UNCOMPRESSED_SIZE(1),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VS_FRAME_UNCOMPRESSED,
	.bFrameIndex		= 2,
	.bmCapabilities		= 0,
	.wWidth			= cpu_to_le16(1280),
	.wHeight		= cpu_to_le16(720),
	.dwMinBitRate		= cpu_to_le32(29491200),
	.dwMaxBitRate		= cpu_to_le32(29491200),
	.dwMaxVideoFrameBufferSize	= cpu_to_le32(1843200),
	.dwDefaultFrameInterval	= cpu_to_le32(5000000),
	.bFrameIntervalType	= 1,
	.dwFrameInterval[0]	= cpu_to_le32(5000000),
पूर्ण;

अटल स्थिर काष्ठा uvc_क्रमmat_mjpeg uvc_क्रमmat_mjpg = अणु
	.bLength		= UVC_DT_FORMAT_MJPEG_SIZE,
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VS_FORMAT_MJPEG,
	.bFormatIndex		= 2,
	.bNumFrameDescriptors	= 2,
	.bmFlags		= 0,
	.bDefaultFrameIndex	= 1,
	.bAspectRatioX		= 0,
	.bAspectRatioY		= 0,
	.bmInterfaceFlags	= 0,
	.bCopyProtect		= 0,
पूर्ण;

DECLARE_UVC_FRAME_MJPEG(1);
DECLARE_UVC_FRAME_MJPEG(3);

अटल स्थिर काष्ठा UVC_FRAME_MJPEG(3) uvc_frame_mjpg_360p = अणु
	.bLength		= UVC_DT_FRAME_MJPEG_SIZE(3),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VS_FRAME_MJPEG,
	.bFrameIndex		= 1,
	.bmCapabilities		= 0,
	.wWidth			= cpu_to_le16(640),
	.wHeight		= cpu_to_le16(360),
	.dwMinBitRate		= cpu_to_le32(18432000),
	.dwMaxBitRate		= cpu_to_le32(55296000),
	.dwMaxVideoFrameBufferSize	= cpu_to_le32(460800),
	.dwDefaultFrameInterval	= cpu_to_le32(666666),
	.bFrameIntervalType	= 3,
	.dwFrameInterval[0]	= cpu_to_le32(666666),
	.dwFrameInterval[1]	= cpu_to_le32(1000000),
	.dwFrameInterval[2]	= cpu_to_le32(5000000),
पूर्ण;

अटल स्थिर काष्ठा UVC_FRAME_MJPEG(1) uvc_frame_mjpg_720p = अणु
	.bLength		= UVC_DT_FRAME_MJPEG_SIZE(1),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VS_FRAME_MJPEG,
	.bFrameIndex		= 2,
	.bmCapabilities		= 0,
	.wWidth			= cpu_to_le16(1280),
	.wHeight		= cpu_to_le16(720),
	.dwMinBitRate		= cpu_to_le32(29491200),
	.dwMaxBitRate		= cpu_to_le32(29491200),
	.dwMaxVideoFrameBufferSize	= cpu_to_le32(1843200),
	.dwDefaultFrameInterval	= cpu_to_le32(5000000),
	.bFrameIntervalType	= 1,
	.dwFrameInterval[0]	= cpu_to_le32(5000000),
पूर्ण;

अटल स्थिर काष्ठा uvc_color_matching_descriptor uvc_color_matching = अणु
	.bLength		= UVC_DT_COLOR_MATCHING_SIZE,
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubType	= UVC_VS_COLORFORMAT,
	.bColorPrimaries	= 1,
	.bTransferCharacteristics	= 1,
	.bMatrixCoefficients	= 4,
पूर्ण;

अटल स्थिर काष्ठा uvc_descriptor_header * स्थिर uvc_fs_control_cls[] = अणु
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_control_header,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_camera_terminal,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_processing,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_output_terminal,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvc_descriptor_header * स्थिर uvc_ss_control_cls[] = अणु
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_control_header,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_camera_terminal,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_processing,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_output_terminal,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvc_descriptor_header * स्थिर uvc_fs_streaming_cls[] = अणु
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_input_header,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_क्रमmat_yuv,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_yuv_360p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_yuv_720p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_क्रमmat_mjpg,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_mjpg_360p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_mjpg_720p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_color_matching,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvc_descriptor_header * स्थिर uvc_hs_streaming_cls[] = अणु
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_input_header,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_क्रमmat_yuv,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_yuv_360p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_yuv_720p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_क्रमmat_mjpg,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_mjpg_360p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_mjpg_720p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_color_matching,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा uvc_descriptor_header * स्थिर uvc_ss_streaming_cls[] = अणु
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_input_header,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_क्रमmat_yuv,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_yuv_360p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_yuv_720p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_क्रमmat_mjpg,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_mjpg_360p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_frame_mjpg_720p,
	(स्थिर काष्ठा uvc_descriptor_header *) &uvc_color_matching,
	शून्य,
पूर्ण;

/* --------------------------------------------------------------------------
 * USB configuration
 */

अटल पूर्णांक
webcam_config_bind(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status = 0;

	f_uvc = usb_get_function(fi_uvc);
	अगर (IS_ERR(f_uvc))
		वापस PTR_ERR(f_uvc);

	status = usb_add_function(c, f_uvc);
	अगर (status < 0)
		usb_put_function(f_uvc);

	वापस status;
पूर्ण

अटल काष्ठा usb_configuration webcam_config_driver = अणु
	.label			= webcam_config_label,
	.bConfigurationValue	= 1,
	.iConfiguration		= 0, /* dynamic */
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
	.MaxPower		= CONFIG_USB_GADGET_VBUS_DRAW,
पूर्ण;

अटल पूर्णांक
webcam_unbind(काष्ठा usb_composite_dev *cdev)
अणु
	अगर (!IS_ERR_OR_शून्य(f_uvc))
		usb_put_function(f_uvc);
	अगर (!IS_ERR_OR_शून्य(fi_uvc))
		usb_put_function_instance(fi_uvc);
	वापस 0;
पूर्ण

अटल पूर्णांक
webcam_bind(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा f_uvc_opts *uvc_opts;
	पूर्णांक ret;

	fi_uvc = usb_get_function_instance("uvc");
	अगर (IS_ERR(fi_uvc))
		वापस PTR_ERR(fi_uvc);

	uvc_opts = container_of(fi_uvc, काष्ठा f_uvc_opts, func_inst);

	uvc_opts->streaming_पूर्णांकerval = streaming_पूर्णांकerval;
	uvc_opts->streaming_maxpacket = streaming_maxpacket;
	uvc_opts->streaming_maxburst = streaming_maxburst;

	uvc_opts->fs_control = uvc_fs_control_cls;
	uvc_opts->ss_control = uvc_ss_control_cls;
	uvc_opts->fs_streaming = uvc_fs_streaming_cls;
	uvc_opts->hs_streaming = uvc_hs_streaming_cls;
	uvc_opts->ss_streaming = uvc_ss_streaming_cls;

	/* Allocate string descriptor numbers ... note that string contents
	 * can be overridden by the composite_dev glue.
	 */
	ret = usb_string_ids_tab(cdev, webcam_strings);
	अगर (ret < 0)
		जाओ error;
	webcam_device_descriptor.iManufacturer =
		webcam_strings[USB_GADGET_MANUFACTURER_IDX].id;
	webcam_device_descriptor.iProduct =
		webcam_strings[USB_GADGET_PRODUCT_IDX].id;
	webcam_config_driver.iConfiguration =
		webcam_strings[STRING_DESCRIPTION_IDX].id;

	/* Register our configuration. */
	अगर ((ret = usb_add_config(cdev, &webcam_config_driver,
					webcam_config_bind)) < 0)
		जाओ error;

	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);
	INFO(cdev, "Webcam Video Gadget\n");
	वापस 0;

error:
	usb_put_function_instance(fi_uvc);
	वापस ret;
पूर्ण

/* --------------------------------------------------------------------------
 * Driver
 */

अटल काष्ठा usb_composite_driver webcam_driver = अणु
	.name		= "g_webcam",
	.dev		= &webcam_device_descriptor,
	.strings	= webcam_device_strings,
	.max_speed	= USB_SPEED_SUPER,
	.bind		= webcam_bind,
	.unbind		= webcam_unbind,
पूर्ण;

module_usb_composite_driver(webcam_driver);

MODULE_AUTHOR("Laurent Pinchart");
MODULE_DESCRIPTION("Webcam Video Gadget");
MODULE_LICENSE("GPL");


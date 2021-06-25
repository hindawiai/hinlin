<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_uac1.c -- USB Audio Class 1.0 Function (using u_audio API)
 *
 * Copyright (C) 2016 Ruslan Bilovol <ruslan.bilovol@gmail.com>
 *
 * This driver करोesn't expect any real Audio codec to be present
 * on the device - the audio streams are simply sinked to and
 * sourced from a भव ALSA sound card created.
 *
 * This file is based on f_uac1.c which is
 *   Copyright (C) 2008 Bryan Wu <cooloney@kernel.org>
 *   Copyright (C) 2008 Analog Devices, Inc
 */

#समावेश <linux/usb/audपन.स>
#समावेश <linux/module.h>

#समावेश "u_audio.h"
#समावेश "u_uac1.h"

/* UAC1 spec: 3.7.2.3 Audio Channel Cluster Format */
#घोषणा UAC1_CHANNEL_MASK 0x0FFF

#घोषणा EPIN_EN(_opts) ((_opts)->p_chmask != 0)
#घोषणा EPOUT_EN(_opts) ((_opts)->c_chmask != 0)

काष्ठा f_uac1 अणु
	काष्ठा g_audio g_audio;
	u8 ac_पूर्णांकf, as_in_पूर्णांकf, as_out_पूर्णांकf;
	u8 ac_alt, as_in_alt, as_out_alt;	/* needed क्रम get_alt() */
पूर्ण;

अटल अंतरभूत काष्ठा f_uac1 *func_to_uac1(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_uac1, g_audio.func);
पूर्ण

अटल अंतरभूत काष्ठा f_uac1_opts *g_audio_to_uac1_opts(काष्ठा g_audio *audio)
अणु
	वापस container_of(audio->func.fi, काष्ठा f_uac1_opts, func_inst);
पूर्ण

/*
 * DESCRIPTORS ... most are अटल, but strings and full
 * configuration descriptors are built on demand.
 */

/*
 * We have three पूर्णांकerfaces - one AudioControl and two AudioStreaming
 *
 * The driver implements a simple UAC_1 topology.
 * USB-OUT -> IT_1 -> OT_2 -> ALSA_Capture
 * ALSA_Playback -> IT_3 -> OT_4 -> USB-IN
 */

/* B.3.1  Standard AC Interface Descriptor */
अटल काष्ठा usb_पूर्णांकerface_descriptor ac_पूर्णांकerface_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bNumEndpoपूर्णांकs =	0,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOCONTROL,
पूर्ण;

/* B.3.2  Class-Specअगरic AC Interface Descriptor */
अटल काष्ठा uac1_ac_header_descriptor *ac_header_desc;

अटल काष्ठा uac_input_terminal_descriptor usb_out_it_desc = अणु
	.bLength =		UAC_DT_INPUT_TERMINAL_SIZE,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_INPUT_TERMINAL,
	/* .bTerminalID =	DYNAMIC */
	.wTerminalType =	cpu_to_le16(UAC_TERMINAL_STREAMING),
	.bAssocTerminal =	0,
	.wChannelConfig =	cpu_to_le16(0x3),
पूर्ण;

अटल काष्ठा uac1_output_terminal_descriptor io_out_ot_desc = अणु
	.bLength		= UAC_DT_OUTPUT_TERMINAL_SIZE,
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubtype	= UAC_OUTPUT_TERMINAL,
	/* .bTerminalID =	DYNAMIC */
	.wTerminalType		= cpu_to_le16(UAC_OUTPUT_TERMINAL_SPEAKER),
	.bAssocTerminal		= 0,
	/* .bSourceID =		DYNAMIC */
पूर्ण;

अटल काष्ठा uac_input_terminal_descriptor io_in_it_desc = अणु
	.bLength		= UAC_DT_INPUT_TERMINAL_SIZE,
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubtype	= UAC_INPUT_TERMINAL,
	/* .bTerminalID		= DYNAMIC */
	.wTerminalType		= cpu_to_le16(UAC_INPUT_TERMINAL_MICROPHONE),
	.bAssocTerminal		= 0,
	.wChannelConfig		= cpu_to_le16(0x3),
पूर्ण;

अटल काष्ठा uac1_output_terminal_descriptor usb_in_ot_desc = अणु
	.bLength =		UAC_DT_OUTPUT_TERMINAL_SIZE,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_OUTPUT_TERMINAL,
	/* .bTerminalID =	DYNAMIC */
	.wTerminalType =	cpu_to_le16(UAC_TERMINAL_STREAMING),
	.bAssocTerminal =	0,
	/* .bSourceID =		DYNAMIC */
पूर्ण;

/* B.4.1  Standard AS Interface Descriptor */
अटल काष्ठा usb_पूर्णांकerface_descriptor as_out_पूर्णांकerface_alt_0_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bAlternateSetting =	0,
	.bNumEndpoपूर्णांकs =	0,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOSTREAMING,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor as_out_पूर्णांकerface_alt_1_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bAlternateSetting =	1,
	.bNumEndpoपूर्णांकs =	1,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOSTREAMING,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor as_in_पूर्णांकerface_alt_0_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bAlternateSetting =	0,
	.bNumEndpoपूर्णांकs =	0,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOSTREAMING,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor as_in_पूर्णांकerface_alt_1_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bAlternateSetting =	1,
	.bNumEndpoपूर्णांकs =	1,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOSTREAMING,
पूर्ण;

/* B.4.2  Class-Specअगरic AS Interface Descriptor */
अटल काष्ठा uac1_as_header_descriptor as_out_header_desc = अणु
	.bLength =		UAC_DT_AS_HEADER_SIZE,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_AS_GENERAL,
	/* .bTerminalLink =	DYNAMIC */
	.bDelay =		1,
	.wFormatTag =		cpu_to_le16(UAC_FORMAT_TYPE_I_PCM),
पूर्ण;

अटल काष्ठा uac1_as_header_descriptor as_in_header_desc = अणु
	.bLength =		UAC_DT_AS_HEADER_SIZE,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_AS_GENERAL,
	/* .bTerminalLink =	DYNAMIC */
	.bDelay =		1,
	.wFormatTag =		cpu_to_le16(UAC_FORMAT_TYPE_I_PCM),
पूर्ण;

DECLARE_UAC_FORMAT_TYPE_I_DISCRETE_DESC(1);

अटल काष्ठा uac_क्रमmat_type_i_discrete_descriptor_1 as_out_type_i_desc = अणु
	.bLength =		UAC_FORMAT_TYPE_I_DISCRETE_DESC_SIZE(1),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_FORMAT_TYPE,
	.bFormatType =		UAC_FORMAT_TYPE_I,
	.bSubframeSize =	2,
	.bBitResolution =	16,
	.bSamFreqType =		1,
पूर्ण;

/* Standard ISO OUT Endpoपूर्णांक Descriptor */
अटल काष्ठा usb_endpoपूर्णांक_descriptor as_out_ep_desc  = अणु
	.bLength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_SYNC_ADAPTIVE
				| USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize	=	cpu_to_le16(UAC1_OUT_EP_MAX_PACKET_SIZE),
	.bInterval =		4,
पूर्ण;

/* Class-specअगरic AS ISO OUT Endpoपूर्णांक Descriptor */
अटल काष्ठा uac_iso_endpoपूर्णांक_descriptor as_iso_out_desc = अणु
	.bLength =		UAC_ISO_ENDPOINT_DESC_SIZE,
	.bDescriptorType =	USB_DT_CS_ENDPOINT,
	.bDescriptorSubtype =	UAC_EP_GENERAL,
	.bmAttributes =		1,
	.bLockDelayUnits =	1,
	.wLockDelay =		cpu_to_le16(1),
पूर्ण;

अटल काष्ठा uac_क्रमmat_type_i_discrete_descriptor_1 as_in_type_i_desc = अणु
	.bLength =		UAC_FORMAT_TYPE_I_DISCRETE_DESC_SIZE(1),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_FORMAT_TYPE,
	.bFormatType =		UAC_FORMAT_TYPE_I,
	.bSubframeSize =	2,
	.bBitResolution =	16,
	.bSamFreqType =		1,
पूर्ण;

/* Standard ISO OUT Endpoपूर्णांक Descriptor */
अटल काष्ठा usb_endpoपूर्णांक_descriptor as_in_ep_desc  = अणु
	.bLength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize	=	cpu_to_le16(UAC1_OUT_EP_MAX_PACKET_SIZE),
	.bInterval =		4,
पूर्ण;

/* Class-specअगरic AS ISO OUT Endpoपूर्णांक Descriptor */
अटल काष्ठा uac_iso_endpoपूर्णांक_descriptor as_iso_in_desc = अणु
	.bLength =		UAC_ISO_ENDPOINT_DESC_SIZE,
	.bDescriptorType =	USB_DT_CS_ENDPOINT,
	.bDescriptorSubtype =	UAC_EP_GENERAL,
	.bmAttributes =		1,
	.bLockDelayUnits =	0,
	.wLockDelay =		0,
पूर्ण;

अटल काष्ठा usb_descriptor_header *f_audio_desc[] = अणु
	(काष्ठा usb_descriptor_header *)&ac_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *)&ac_header_desc,

	(काष्ठा usb_descriptor_header *)&usb_out_it_desc,
	(काष्ठा usb_descriptor_header *)&io_out_ot_desc,
	(काष्ठा usb_descriptor_header *)&io_in_it_desc,
	(काष्ठा usb_descriptor_header *)&usb_in_ot_desc,

	(काष्ठा usb_descriptor_header *)&as_out_पूर्णांकerface_alt_0_desc,
	(काष्ठा usb_descriptor_header *)&as_out_पूर्णांकerface_alt_1_desc,
	(काष्ठा usb_descriptor_header *)&as_out_header_desc,

	(काष्ठा usb_descriptor_header *)&as_out_type_i_desc,

	(काष्ठा usb_descriptor_header *)&as_out_ep_desc,
	(काष्ठा usb_descriptor_header *)&as_iso_out_desc,

	(काष्ठा usb_descriptor_header *)&as_in_पूर्णांकerface_alt_0_desc,
	(काष्ठा usb_descriptor_header *)&as_in_पूर्णांकerface_alt_1_desc,
	(काष्ठा usb_descriptor_header *)&as_in_header_desc,

	(काष्ठा usb_descriptor_header *)&as_in_type_i_desc,

	(काष्ठा usb_descriptor_header *)&as_in_ep_desc,
	(काष्ठा usb_descriptor_header *)&as_iso_in_desc,
	शून्य,
पूर्ण;

क्रमागत अणु
	STR_AC_IF,
	STR_USB_OUT_IT,
	STR_USB_OUT_IT_CH_NAMES,
	STR_IO_OUT_OT,
	STR_IO_IN_IT,
	STR_IO_IN_IT_CH_NAMES,
	STR_USB_IN_OT,
	STR_AS_OUT_IF_ALT0,
	STR_AS_OUT_IF_ALT1,
	STR_AS_IN_IF_ALT0,
	STR_AS_IN_IF_ALT1,
पूर्ण;

अटल काष्ठा usb_string strings_uac1[] = अणु
	[STR_AC_IF].s = "AC Interface",
	[STR_USB_OUT_IT].s = "Playback Input terminal",
	[STR_USB_OUT_IT_CH_NAMES].s = "Playback Channels",
	[STR_IO_OUT_OT].s = "Playback Output terminal",
	[STR_IO_IN_IT].s = "Capture Input terminal",
	[STR_IO_IN_IT_CH_NAMES].s = "Capture Channels",
	[STR_USB_IN_OT].s = "Capture Output terminal",
	[STR_AS_OUT_IF_ALT0].s = "Playback Inactive",
	[STR_AS_OUT_IF_ALT1].s = "Playback Active",
	[STR_AS_IN_IF_ALT0].s = "Capture Inactive",
	[STR_AS_IN_IF_ALT1].s = "Capture Active",
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा usb_gadget_strings str_uac1 = अणु
	.language = 0x0409,	/* en-us */
	.strings = strings_uac1,
पूर्ण;

अटल काष्ठा usb_gadget_strings *uac1_strings[] = अणु
	&str_uac1,
	शून्य,
पूर्ण;

/*
 * This function is an ALSA sound card following USB Audio Class Spec 1.0.
 */

अटल पूर्णांक audio_set_endpoपूर्णांक_req(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	पूर्णांक			value = -EOPNOTSUPP;
	u16			ep = le16_to_cpu(ctrl->wIndex);
	u16			len = le16_to_cpu(ctrl->wLength);
	u16			w_value = le16_to_cpu(ctrl->wValue);

	DBG(cdev, "bRequest 0x%x, w_value 0x%04x, len %d, endpoint %d\n",
			ctrl->bRequest, w_value, len, ep);

	चयन (ctrl->bRequest) अणु
	हाल UAC_SET_CUR:
		value = len;
		अवरोध;

	हाल UAC_SET_MIN:
		अवरोध;

	हाल UAC_SET_MAX:
		अवरोध;

	हाल UAC_SET_RES:
		अवरोध;

	हाल UAC_SET_MEM:
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक audio_get_endpoपूर्णांक_req(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	पूर्णांक value = -EOPNOTSUPP;
	u8 ep = ((le16_to_cpu(ctrl->wIndex) >> 8) & 0xFF);
	u16 len = le16_to_cpu(ctrl->wLength);
	u16 w_value = le16_to_cpu(ctrl->wValue);

	DBG(cdev, "bRequest 0x%x, w_value 0x%04x, len %d, endpoint %d\n",
			ctrl->bRequest, w_value, len, ep);

	चयन (ctrl->bRequest) अणु
	हाल UAC_GET_CUR:
	हाल UAC_GET_MIN:
	हाल UAC_GET_MAX:
	हाल UAC_GET_RES:
		value = len;
		अवरोध;
	हाल UAC_GET_MEM:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक
f_audio_setup(काष्ठा usb_function *f, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_request	*req = cdev->req;
	पूर्णांक			value = -EOPNOTSUPP;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	/* composite driver infraकाष्ठाure handles everything; पूर्णांकerface
	 * activation uses set_alt().
	 */
	चयन (ctrl->bRequestType) अणु
	हाल USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_ENDPOINT:
		value = audio_set_endpoपूर्णांक_req(f, ctrl);
		अवरोध;

	हाल USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT:
		value = audio_get_endpoपूर्णांक_req(f, ctrl);
		अवरोध;

	शेष:
		ERROR(cdev, "invalid control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
	पूर्ण

	/* respond with data transfer or status phase? */
	अगर (value >= 0) अणु
		DBG(cdev, "audio req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
		req->zero = 0;
		req->length = value;
		value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
		अगर (value < 0)
			ERROR(cdev, "audio response on err %d\n", value);
	पूर्ण

	/* device either stalls (value < 0) or reports success */
	वापस value;
पूर्ण

अटल पूर्णांक f_audio_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_gadget *gadget = cdev->gadget;
	काष्ठा device *dev = &gadget->dev;
	काष्ठा f_uac1 *uac1 = func_to_uac1(f);
	पूर्णांक ret = 0;

	/* No i/f has more than 2 alt settings */
	अगर (alt > 1) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकf == uac1->ac_पूर्णांकf) अणु
		/* Control I/f has only 1 AltSetting - 0 */
		अगर (alt) अणु
			dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (पूर्णांकf == uac1->as_out_पूर्णांकf) अणु
		uac1->as_out_alt = alt;

		अगर (alt)
			ret = u_audio_start_capture(&uac1->g_audio);
		अन्यथा
			u_audio_stop_capture(&uac1->g_audio);
	पूर्ण अन्यथा अगर (पूर्णांकf == uac1->as_in_पूर्णांकf) अणु
		uac1->as_in_alt = alt;

		अगर (alt)
			ret = u_audio_start_playback(&uac1->g_audio);
		अन्यथा
			u_audio_stop_playback(&uac1->g_audio);
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक f_audio_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf)
अणु
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_gadget *gadget = cdev->gadget;
	काष्ठा device *dev = &gadget->dev;
	काष्ठा f_uac1 *uac1 = func_to_uac1(f);

	अगर (पूर्णांकf == uac1->ac_पूर्णांकf)
		वापस uac1->ac_alt;
	अन्यथा अगर (पूर्णांकf == uac1->as_out_पूर्णांकf)
		वापस uac1->as_out_alt;
	अन्यथा अगर (पूर्णांकf == uac1->as_in_पूर्णांकf)
		वापस uac1->as_in_alt;
	अन्यथा
		dev_err(dev, "%s:%d Invalid Interface %d!\n",
			__func__, __LINE__, पूर्णांकf);

	वापस -EINVAL;
पूर्ण


अटल व्योम f_audio_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_uac1 *uac1 = func_to_uac1(f);

	uac1->as_out_alt = 0;
	uac1->as_in_alt = 0;

	u_audio_stop_playback(&uac1->g_audio);
	u_audio_stop_capture(&uac1->g_audio);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा
uac1_ac_header_descriptor *build_ac_header_desc(काष्ठा f_uac1_opts *opts)
अणु
	काष्ठा uac1_ac_header_descriptor *ac_desc;
	पूर्णांक ac_header_desc_size;
	पूर्णांक num_अगरaces = 0;

	अगर (EPOUT_EN(opts))
		num_अगरaces++;
	अगर (EPIN_EN(opts))
		num_अगरaces++;

	ac_header_desc_size = UAC_DT_AC_HEADER_SIZE(num_अगरaces);

	ac_desc = kzalloc(ac_header_desc_size, GFP_KERNEL);
	अगर (!ac_desc)
		वापस शून्य;

	ac_desc->bLength = ac_header_desc_size;
	ac_desc->bDescriptorType = USB_DT_CS_INTERFACE;
	ac_desc->bDescriptorSubtype = UAC_HEADER;
	ac_desc->bcdADC = cpu_to_le16(0x0100);
	ac_desc->bInCollection = num_अगरaces;

	/* wTotalLength and baInterfaceNr will be defined later */

	वापस ac_desc;
पूर्ण

/* Use macro to overcome line length limitation */
#घोषणा USBDHDR(p) (काष्ठा usb_descriptor_header *)(p)

अटल व्योम setup_descriptor(काष्ठा f_uac1_opts *opts)
अणु
	/* patch descriptors */
	पूर्णांक i = 1; /* ID's start with 1 */

	अगर (EPOUT_EN(opts))
		usb_out_it_desc.bTerminalID = i++;
	अगर (EPIN_EN(opts))
		io_in_it_desc.bTerminalID = i++;
	अगर (EPOUT_EN(opts))
		io_out_ot_desc.bTerminalID = i++;
	अगर (EPIN_EN(opts))
		usb_in_ot_desc.bTerminalID = i++;

	usb_in_ot_desc.bSourceID = io_in_it_desc.bTerminalID;
	io_out_ot_desc.bSourceID = usb_out_it_desc.bTerminalID;

	as_out_header_desc.bTerminalLink = usb_out_it_desc.bTerminalID;
	as_in_header_desc.bTerminalLink = usb_in_ot_desc.bTerminalID;

	ac_header_desc->wTotalLength = cpu_to_le16(ac_header_desc->bLength);

	अगर (EPIN_EN(opts)) अणु
		u16 len = le16_to_cpu(ac_header_desc->wTotalLength);

		len += माप(usb_in_ot_desc);
		len += माप(io_in_it_desc);
		ac_header_desc->wTotalLength = cpu_to_le16(len);
	पूर्ण
	अगर (EPOUT_EN(opts)) अणु
		u16 len = le16_to_cpu(ac_header_desc->wTotalLength);

		len += माप(usb_out_it_desc);
		len += माप(io_out_ot_desc);
		ac_header_desc->wTotalLength = cpu_to_le16(len);
	पूर्ण

	i = 0;
	f_audio_desc[i++] = USBDHDR(&ac_पूर्णांकerface_desc);
	f_audio_desc[i++] = USBDHDR(ac_header_desc);

	अगर (EPOUT_EN(opts)) अणु
		f_audio_desc[i++] = USBDHDR(&usb_out_it_desc);
		f_audio_desc[i++] = USBDHDR(&io_out_ot_desc);
	पूर्ण

	अगर (EPIN_EN(opts)) अणु
		f_audio_desc[i++] = USBDHDR(&io_in_it_desc);
		f_audio_desc[i++] = USBDHDR(&usb_in_ot_desc);
	पूर्ण

	अगर (EPOUT_EN(opts)) अणु
		f_audio_desc[i++] = USBDHDR(&as_out_पूर्णांकerface_alt_0_desc);
		f_audio_desc[i++] = USBDHDR(&as_out_पूर्णांकerface_alt_1_desc);
		f_audio_desc[i++] = USBDHDR(&as_out_header_desc);
		f_audio_desc[i++] = USBDHDR(&as_out_type_i_desc);
		f_audio_desc[i++] = USBDHDR(&as_out_ep_desc);
		f_audio_desc[i++] = USBDHDR(&as_iso_out_desc);
	पूर्ण
	अगर (EPIN_EN(opts)) अणु
		f_audio_desc[i++] = USBDHDR(&as_in_पूर्णांकerface_alt_0_desc);
		f_audio_desc[i++] = USBDHDR(&as_in_पूर्णांकerface_alt_1_desc);
		f_audio_desc[i++] = USBDHDR(&as_in_header_desc);
		f_audio_desc[i++] = USBDHDR(&as_in_type_i_desc);
		f_audio_desc[i++] = USBDHDR(&as_in_ep_desc);
		f_audio_desc[i++] = USBDHDR(&as_iso_in_desc);
	पूर्ण
	f_audio_desc[i] = शून्य;
पूर्ण

अटल पूर्णांक f_audio_validate_opts(काष्ठा g_audio *audio, काष्ठा device *dev)
अणु
	काष्ठा f_uac1_opts *opts = g_audio_to_uac1_opts(audio);

	अगर (!opts->p_chmask && !opts->c_chmask) अणु
		dev_err(dev, "Error: no playback and capture channels\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (opts->p_chmask & ~UAC1_CHANNEL_MASK) अणु
		dev_err(dev, "Error: unsupported playback channels mask\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (opts->c_chmask & ~UAC1_CHANNEL_MASK) अणु
		dev_err(dev, "Error: unsupported capture channels mask\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((opts->p_ssize < 1) || (opts->p_ssize > 4)) अणु
		dev_err(dev, "Error: incorrect playback sample size\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((opts->c_ssize < 1) || (opts->c_ssize > 4)) अणु
		dev_err(dev, "Error: incorrect capture sample size\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!opts->p_srate) अणु
		dev_err(dev, "Error: incorrect playback sampling rate\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!opts->c_srate) अणु
		dev_err(dev, "Error: incorrect capture sampling rate\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* audio function driver setup/binding */
अटल पूर्णांक f_audio_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev	*cdev = c->cdev;
	काष्ठा usb_gadget		*gadget = cdev->gadget;
	काष्ठा device			*dev = &gadget->dev;
	काष्ठा f_uac1			*uac1 = func_to_uac1(f);
	काष्ठा g_audio			*audio = func_to_g_audio(f);
	काष्ठा f_uac1_opts		*audio_opts;
	काष्ठा usb_ep			*ep = शून्य;
	काष्ठा usb_string		*us;
	u8				*sam_freq;
	पूर्णांक				rate;
	पूर्णांक				ba_अगरace_id;
	पूर्णांक				status;

	status = f_audio_validate_opts(audio, dev);
	अगर (status)
		वापस status;

	audio_opts = container_of(f->fi, काष्ठा f_uac1_opts, func_inst);

	us = usb_gstrings_attach(cdev, uac1_strings, ARRAY_SIZE(strings_uac1));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);

	ac_header_desc = build_ac_header_desc(audio_opts);
	अगर (!ac_header_desc)
		वापस -ENOMEM;

	ac_पूर्णांकerface_desc.iInterface = us[STR_AC_IF].id;
	usb_out_it_desc.iTerminal = us[STR_USB_OUT_IT].id;
	usb_out_it_desc.iChannelNames = us[STR_USB_OUT_IT_CH_NAMES].id;
	io_out_ot_desc.iTerminal = us[STR_IO_OUT_OT].id;
	as_out_पूर्णांकerface_alt_0_desc.iInterface = us[STR_AS_OUT_IF_ALT0].id;
	as_out_पूर्णांकerface_alt_1_desc.iInterface = us[STR_AS_OUT_IF_ALT1].id;
	io_in_it_desc.iTerminal = us[STR_IO_IN_IT].id;
	io_in_it_desc.iChannelNames = us[STR_IO_IN_IT_CH_NAMES].id;
	usb_in_ot_desc.iTerminal = us[STR_USB_IN_OT].id;
	as_in_पूर्णांकerface_alt_0_desc.iInterface = us[STR_AS_IN_IF_ALT0].id;
	as_in_पूर्णांकerface_alt_1_desc.iInterface = us[STR_AS_IN_IF_ALT1].id;

	/* Set channel numbers */
	usb_out_it_desc.bNrChannels = num_channels(audio_opts->c_chmask);
	usb_out_it_desc.wChannelConfig = cpu_to_le16(audio_opts->c_chmask);
	as_out_type_i_desc.bNrChannels = num_channels(audio_opts->c_chmask);
	as_out_type_i_desc.bSubframeSize = audio_opts->c_ssize;
	as_out_type_i_desc.bBitResolution = audio_opts->c_ssize * 8;
	io_in_it_desc.bNrChannels = num_channels(audio_opts->p_chmask);
	io_in_it_desc.wChannelConfig = cpu_to_le16(audio_opts->p_chmask);
	as_in_type_i_desc.bNrChannels = num_channels(audio_opts->p_chmask);
	as_in_type_i_desc.bSubframeSize = audio_opts->p_ssize;
	as_in_type_i_desc.bBitResolution = audio_opts->p_ssize * 8;

	/* Set sample rates */
	rate = audio_opts->c_srate;
	sam_freq = as_out_type_i_desc.tSamFreq[0];
	स_नकल(sam_freq, &rate, 3);
	rate = audio_opts->p_srate;
	sam_freq = as_in_type_i_desc.tSamFreq[0];
	स_नकल(sam_freq, &rate, 3);

	/* allocate instance-specअगरic पूर्णांकerface IDs, and patch descriptors */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	ac_पूर्णांकerface_desc.bInterfaceNumber = status;
	uac1->ac_पूर्णांकf = status;
	uac1->ac_alt = 0;

	ba_अगरace_id = 0;

	अगर (EPOUT_EN(audio_opts)) अणु
		status = usb_पूर्णांकerface_id(c, f);
		अगर (status < 0)
			जाओ fail;
		as_out_पूर्णांकerface_alt_0_desc.bInterfaceNumber = status;
		as_out_पूर्णांकerface_alt_1_desc.bInterfaceNumber = status;
		ac_header_desc->baInterfaceNr[ba_अगरace_id++] = status;
		uac1->as_out_पूर्णांकf = status;
		uac1->as_out_alt = 0;
	पूर्ण

	अगर (EPIN_EN(audio_opts)) अणु
		status = usb_पूर्णांकerface_id(c, f);
		अगर (status < 0)
			जाओ fail;
		as_in_पूर्णांकerface_alt_0_desc.bInterfaceNumber = status;
		as_in_पूर्णांकerface_alt_1_desc.bInterfaceNumber = status;
		ac_header_desc->baInterfaceNr[ba_अगरace_id++] = status;
		uac1->as_in_पूर्णांकf = status;
		uac1->as_in_alt = 0;
	पूर्ण

	audio->gadget = gadget;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	अगर (EPOUT_EN(audio_opts)) अणु
		ep = usb_ep_स्वतःconfig(cdev->gadget, &as_out_ep_desc);
		अगर (!ep)
			जाओ fail;
		audio->out_ep = ep;
		audio->out_ep->desc = &as_out_ep_desc;
	पूर्ण

	अगर (EPIN_EN(audio_opts)) अणु
		ep = usb_ep_स्वतःconfig(cdev->gadget, &as_in_ep_desc);
		अगर (!ep)
			जाओ fail;
		audio->in_ep = ep;
		audio->in_ep->desc = &as_in_ep_desc;
	पूर्ण

	setup_descriptor(audio_opts);

	/* copy descriptors, and track endpoपूर्णांक copies */
	status = usb_assign_descriptors(f, f_audio_desc, f_audio_desc, शून्य,
					शून्य);
	अगर (status)
		जाओ fail;

	audio->out_ep_maxpsize = le16_to_cpu(as_out_ep_desc.wMaxPacketSize);
	audio->in_ep_maxpsize = le16_to_cpu(as_in_ep_desc.wMaxPacketSize);
	audio->params.c_chmask = audio_opts->c_chmask;
	audio->params.c_srate = audio_opts->c_srate;
	audio->params.c_ssize = audio_opts->c_ssize;
	audio->params.p_chmask = audio_opts->p_chmask;
	audio->params.p_srate = audio_opts->p_srate;
	audio->params.p_ssize = audio_opts->p_ssize;
	audio->params.req_number = audio_opts->req_number;

	status = g_audio_setup(audio, "UAC1_PCM", "UAC1_Gadget");
	अगर (status)
		जाओ err_card_रेजिस्टर;

	वापस 0;

err_card_रेजिस्टर:
	usb_मुक्त_all_descriptors(f);
fail:
	kमुक्त(ac_header_desc);
	ac_header_desc = शून्य;
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत काष्ठा f_uac1_opts *to_f_uac1_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_uac1_opts,
			    func_inst.group);
पूर्ण

अटल व्योम f_uac1_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_uac1_opts *opts = to_f_uac1_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations f_uac1_item_ops = अणु
	.release	= f_uac1_attr_release,
पूर्ण;

#घोषणा UAC1_ATTRIBUTE(name)						\
अटल sमाप_प्रकार f_uac1_opts_##name##_show(				\
					  काष्ठा config_item *item,	\
					  अक्षर *page)			\
अणु									\
	काष्ठा f_uac1_opts *opts = to_f_uac1_opts(item);		\
	पूर्णांक result;							\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", opts->name);			\
	mutex_unlock(&opts->lock);					\
									\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार f_uac1_opts_##name##_store(				\
					  काष्ठा config_item *item,	\
					  स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा f_uac1_opts *opts = to_f_uac1_opts(item);		\
	पूर्णांक ret;							\
	u32 num;							\
									\
	mutex_lock(&opts->lock);					\
	अगर (opts->refcnt) अणु						\
		ret = -EBUSY;						\
		जाओ end;						\
	पूर्ण								\
									\
	ret = kstrtou32(page, 0, &num);					\
	अगर (ret)							\
		जाओ end;						\
									\
	opts->name = num;						\
	ret = len;							\
									\
end:									\
	mutex_unlock(&opts->lock);					\
	वापस ret;							\
पूर्ण									\
									\
CONFIGFS_ATTR(f_uac1_opts_, name)

UAC1_ATTRIBUTE(c_chmask);
UAC1_ATTRIBUTE(c_srate);
UAC1_ATTRIBUTE(c_ssize);
UAC1_ATTRIBUTE(p_chmask);
UAC1_ATTRIBUTE(p_srate);
UAC1_ATTRIBUTE(p_ssize);
UAC1_ATTRIBUTE(req_number);

अटल काष्ठा configfs_attribute *f_uac1_attrs[] = अणु
	&f_uac1_opts_attr_c_chmask,
	&f_uac1_opts_attr_c_srate,
	&f_uac1_opts_attr_c_ssize,
	&f_uac1_opts_attr_p_chmask,
	&f_uac1_opts_attr_p_srate,
	&f_uac1_opts_attr_p_ssize,
	&f_uac1_opts_attr_req_number,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type f_uac1_func_type = अणु
	.ct_item_ops	= &f_uac1_item_ops,
	.ct_attrs	= f_uac1_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम f_audio_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_uac1_opts *opts;

	opts = container_of(f, काष्ठा f_uac1_opts, func_inst);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *f_audio_alloc_inst(व्योम)
अणु
	काष्ठा f_uac1_opts *opts;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = f_audio_मुक्त_inst;

	config_group_init_type_name(&opts->func_inst.group, "",
				    &f_uac1_func_type);

	opts->c_chmask = UAC1_DEF_CCHMASK;
	opts->c_srate = UAC1_DEF_CSRATE;
	opts->c_ssize = UAC1_DEF_CSSIZE;
	opts->p_chmask = UAC1_DEF_PCHMASK;
	opts->p_srate = UAC1_DEF_PSRATE;
	opts->p_ssize = UAC1_DEF_PSSIZE;
	opts->req_number = UAC1_DEF_REQ_NUM;
	वापस &opts->func_inst;
पूर्ण

अटल व्योम f_audio_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा g_audio *audio;
	काष्ठा f_uac1_opts *opts;

	audio = func_to_g_audio(f);
	opts = container_of(f->fi, काष्ठा f_uac1_opts, func_inst);
	kमुक्त(audio);
	mutex_lock(&opts->lock);
	--opts->refcnt;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम f_audio_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा g_audio *audio = func_to_g_audio(f);

	g_audio_cleanup(audio);
	usb_मुक्त_all_descriptors(f);

	kमुक्त(ac_header_desc);
	ac_header_desc = शून्य;

	audio->gadget = शून्य;
पूर्ण

अटल काष्ठा usb_function *f_audio_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_uac1 *uac1;
	काष्ठा f_uac1_opts *opts;

	/* allocate and initialize one new instance */
	uac1 = kzalloc(माप(*uac1), GFP_KERNEL);
	अगर (!uac1)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_uac1_opts, func_inst);
	mutex_lock(&opts->lock);
	++opts->refcnt;
	mutex_unlock(&opts->lock);

	uac1->g_audio.func.name = "uac1_func";
	uac1->g_audio.func.bind = f_audio_bind;
	uac1->g_audio.func.unbind = f_audio_unbind;
	uac1->g_audio.func.set_alt = f_audio_set_alt;
	uac1->g_audio.func.get_alt = f_audio_get_alt;
	uac1->g_audio.func.setup = f_audio_setup;
	uac1->g_audio.func.disable = f_audio_disable;
	uac1->g_audio.func.मुक्त_func = f_audio_मुक्त;

	वापस &uac1->g_audio.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(uac1, f_audio_alloc_inst, f_audio_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ruslan Bilovol");

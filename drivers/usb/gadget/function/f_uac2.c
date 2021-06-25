<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_uac2.c -- USB Audio Class 2.0 Function
 *
 * Copyright (C) 2011
 *    Yadwinder Singh (yadi.brar01@gmail.com)
 *    Jaswinder Singh (jaswinder.singh@linaro.org)
 */

#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>
#समावेश <linux/module.h>

#समावेश "u_audio.h"
#समावेश "u_uac2.h"

/* UAC2 spec: 4.1 Audio Channel Cluster Descriptor */
#घोषणा UAC2_CHANNEL_MASK 0x07FFFFFF

/*
 * The driver implements a simple UAC_2 topology.
 * USB-OUT -> IT_1 -> OT_3 -> ALSA_Capture
 * ALSA_Playback -> IT_2 -> OT_4 -> USB-IN
 * Capture and Playback sampling rates are independently
 *  controlled by two घड़ी sources :
 *    CLK_5 := c_srate, and CLK_6 := p_srate
 */
#घोषणा USB_OUT_CLK_ID	(out_clk_src_desc.bClockID)
#घोषणा USB_IN_CLK_ID	(in_clk_src_desc.bClockID)

#घोषणा CONTROL_ABSENT	0
#घोषणा CONTROL_RDONLY	1
#घोषणा CONTROL_RDWR	3

#घोषणा CLK_FREQ_CTRL	0
#घोषणा CLK_VLD_CTRL	2

#घोषणा COPY_CTRL	0
#घोषणा CONN_CTRL	2
#घोषणा OVRLD_CTRL	4
#घोषणा CLSTR_CTRL	6
#घोषणा UNFLW_CTRL	8
#घोषणा OVFLW_CTRL	10

#घोषणा EPIN_EN(_opts) ((_opts)->p_chmask != 0)
#घोषणा EPOUT_EN(_opts) ((_opts)->c_chmask != 0)

काष्ठा f_uac2 अणु
	काष्ठा g_audio g_audio;
	u8 ac_पूर्णांकf, as_in_पूर्णांकf, as_out_पूर्णांकf;
	u8 ac_alt, as_in_alt, as_out_alt;	/* needed क्रम get_alt() */
पूर्ण;

अटल अंतरभूत काष्ठा f_uac2 *func_to_uac2(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_uac2, g_audio.func);
पूर्ण

अटल अंतरभूत
काष्ठा f_uac2_opts *g_audio_to_uac2_opts(काष्ठा g_audio *agdev)
अणु
	वापस container_of(agdev->func.fi, काष्ठा f_uac2_opts, func_inst);
पूर्ण

/* --------- USB Function Interface ------------- */

क्रमागत अणु
	STR_ASSOC,
	STR_IF_CTRL,
	STR_CLKSRC_IN,
	STR_CLKSRC_OUT,
	STR_USB_IT,
	STR_IO_IT,
	STR_USB_OT,
	STR_IO_OT,
	STR_AS_OUT_ALT0,
	STR_AS_OUT_ALT1,
	STR_AS_IN_ALT0,
	STR_AS_IN_ALT1,
पूर्ण;

अटल अक्षर clksrc_in[8];
अटल अक्षर clksrc_out[8];

अटल काष्ठा usb_string strings_fn[] = अणु
	[STR_ASSOC].s = "Source/Sink",
	[STR_IF_CTRL].s = "Topology Control",
	[STR_CLKSRC_IN].s = clksrc_in,
	[STR_CLKSRC_OUT].s = clksrc_out,
	[STR_USB_IT].s = "USBH Out",
	[STR_IO_IT].s = "USBD Out",
	[STR_USB_OT].s = "USBH In",
	[STR_IO_OT].s = "USBD In",
	[STR_AS_OUT_ALT0].s = "Playback Inactive",
	[STR_AS_OUT_ALT1].s = "Playback Active",
	[STR_AS_IN_ALT0].s = "Capture Inactive",
	[STR_AS_IN_ALT1].s = "Capture Active",
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा usb_gadget_strings str_fn = अणु
	.language = 0x0409,	/* en-us */
	.strings = strings_fn,
पूर्ण;

अटल काष्ठा usb_gadget_strings *fn_strings[] = अणु
	&str_fn,
	शून्य,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_assoc_descriptor iad_desc = अणु
	.bLength = माप iad_desc,
	.bDescriptorType = USB_DT_INTERFACE_ASSOCIATION,

	.bFirstInterface = 0,
	.bInterfaceCount = 3,
	.bFunctionClass = USB_CLASS_AUDIO,
	.bFunctionSubClass = UAC2_FUNCTION_SUBCLASS_UNDEFINED,
	.bFunctionProtocol = UAC_VERSION_2,
पूर्ण;

/* Audio Control Interface */
अटल काष्ठा usb_पूर्णांकerface_descriptor std_ac_अगर_desc = अणु
	.bLength = माप std_ac_अगर_desc,
	.bDescriptorType = USB_DT_INTERFACE,

	.bAlternateSetting = 0,
	.bNumEndpoपूर्णांकs = 0,
	.bInterfaceClass = USB_CLASS_AUDIO,
	.bInterfaceSubClass = USB_SUBCLASS_AUDIOCONTROL,
	.bInterfaceProtocol = UAC_VERSION_2,
पूर्ण;

/* Clock source क्रम IN traffic */
अटल काष्ठा uac_घड़ी_source_descriptor in_clk_src_desc = अणु
	.bLength = माप in_clk_src_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC2_CLOCK_SOURCE,
	/* .bClockID = DYNAMIC */
	.bmAttributes = UAC_CLOCK_SOURCE_TYPE_INT_FIXED,
	.bmControls = (CONTROL_RDONLY << CLK_FREQ_CTRL),
	.bAssocTerminal = 0,
पूर्ण;

/* Clock source क्रम OUT traffic */
अटल काष्ठा uac_घड़ी_source_descriptor out_clk_src_desc = अणु
	.bLength = माप out_clk_src_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC2_CLOCK_SOURCE,
	/* .bClockID = DYNAMIC */
	.bmAttributes = UAC_CLOCK_SOURCE_TYPE_INT_FIXED,
	.bmControls = (CONTROL_RDONLY << CLK_FREQ_CTRL),
	.bAssocTerminal = 0,
पूर्ण;

/* Input Terminal क्रम USB_OUT */
अटल काष्ठा uac2_input_terminal_descriptor usb_out_it_desc = अणु
	.bLength = माप usb_out_it_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC_INPUT_TERMINAL,
	/* .bTerminalID = DYNAMIC */
	.wTerminalType = cpu_to_le16(UAC_TERMINAL_STREAMING),
	.bAssocTerminal = 0,
	/* .bCSourceID = DYNAMIC */
	.iChannelNames = 0,
	.bmControls = cpu_to_le16(CONTROL_RDWR << COPY_CTRL),
पूर्ण;

/* Input Terminal क्रम I/O-In */
अटल काष्ठा uac2_input_terminal_descriptor io_in_it_desc = अणु
	.bLength = माप io_in_it_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC_INPUT_TERMINAL,
	/* .bTerminalID = DYNAMIC */
	.wTerminalType = cpu_to_le16(UAC_INPUT_TERMINAL_UNDEFINED),
	.bAssocTerminal = 0,
	/* .bCSourceID = DYNAMIC */
	.iChannelNames = 0,
	.bmControls = cpu_to_le16(CONTROL_RDWR << COPY_CTRL),
पूर्ण;

/* Ouput Terminal क्रम USB_IN */
अटल काष्ठा uac2_output_terminal_descriptor usb_in_ot_desc = अणु
	.bLength = माप usb_in_ot_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC_OUTPUT_TERMINAL,
	/* .bTerminalID = DYNAMIC */
	.wTerminalType = cpu_to_le16(UAC_TERMINAL_STREAMING),
	.bAssocTerminal = 0,
	/* .bSourceID = DYNAMIC */
	/* .bCSourceID = DYNAMIC */
	.bmControls = cpu_to_le16(CONTROL_RDWR << COPY_CTRL),
पूर्ण;

/* Ouput Terminal क्रम I/O-Out */
अटल काष्ठा uac2_output_terminal_descriptor io_out_ot_desc = अणु
	.bLength = माप io_out_ot_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC_OUTPUT_TERMINAL,
	/* .bTerminalID = DYNAMIC */
	.wTerminalType = cpu_to_le16(UAC_OUTPUT_TERMINAL_UNDEFINED),
	.bAssocTerminal = 0,
	/* .bSourceID = DYNAMIC */
	/* .bCSourceID = DYNAMIC */
	.bmControls = cpu_to_le16(CONTROL_RDWR << COPY_CTRL),
पूर्ण;

अटल काष्ठा uac2_ac_header_descriptor ac_hdr_desc = अणु
	.bLength = माप ac_hdr_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC_MS_HEADER,
	.bcdADC = cpu_to_le16(0x200),
	.bCategory = UAC2_FUNCTION_IO_BOX,
	/* .wTotalLength = DYNAMIC */
	.bmControls = 0,
पूर्ण;

/* Audio Streaming OUT Interface - Alt0 */
अटल काष्ठा usb_पूर्णांकerface_descriptor std_as_out_अगर0_desc = अणु
	.bLength = माप std_as_out_अगर0_desc,
	.bDescriptorType = USB_DT_INTERFACE,

	.bAlternateSetting = 0,
	.bNumEndpoपूर्णांकs = 0,
	.bInterfaceClass = USB_CLASS_AUDIO,
	.bInterfaceSubClass = USB_SUBCLASS_AUDIOSTREAMING,
	.bInterfaceProtocol = UAC_VERSION_2,
पूर्ण;

/* Audio Streaming OUT Interface - Alt1 */
अटल काष्ठा usb_पूर्णांकerface_descriptor std_as_out_अगर1_desc = अणु
	.bLength = माप std_as_out_अगर1_desc,
	.bDescriptorType = USB_DT_INTERFACE,

	.bAlternateSetting = 1,
	.bNumEndpoपूर्णांकs = 1,
	.bInterfaceClass = USB_CLASS_AUDIO,
	.bInterfaceSubClass = USB_SUBCLASS_AUDIOSTREAMING,
	.bInterfaceProtocol = UAC_VERSION_2,
पूर्ण;

/* Audio Stream OUT Intface Desc */
अटल काष्ठा uac2_as_header_descriptor as_out_hdr_desc = अणु
	.bLength = माप as_out_hdr_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC_AS_GENERAL,
	/* .bTerminalLink = DYNAMIC */
	.bmControls = 0,
	.bFormatType = UAC_FORMAT_TYPE_I,
	.bmFormats = cpu_to_le32(UAC_FORMAT_TYPE_I_PCM),
	.iChannelNames = 0,
पूर्ण;

/* Audio USB_OUT Format */
अटल काष्ठा uac2_क्रमmat_type_i_descriptor as_out_fmt1_desc = अणु
	.bLength = माप as_out_fmt1_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,
	.bDescriptorSubtype = UAC_FORMAT_TYPE,
	.bFormatType = UAC_FORMAT_TYPE_I,
पूर्ण;

/* STD AS ISO OUT Endpoपूर्णांक */
अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_epout_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress = USB_सूची_OUT,
	.bmAttributes = USB_ENDPOINT_XFER_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	.bInterval = 1,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_epout_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bmAttributes = USB_ENDPOINT_XFER_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	.bInterval = 4,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_epout_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress = USB_सूची_OUT,
	.bmAttributes = USB_ENDPOINT_XFER_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	.bInterval = 4,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_epout_desc_comp = अणु
	.bLength		= माप(ss_epout_desc_comp),
	.bDescriptorType	= USB_DT_SS_ENDPOINT_COMP,
	.bMaxBurst		= 0,
	.bmAttributes		= 0,
	/* wBytesPerInterval = DYNAMIC */
पूर्ण;

/* CS AS ISO OUT Endpoपूर्णांक */
अटल काष्ठा uac2_iso_endpoपूर्णांक_descriptor as_iso_out_desc = अणु
	.bLength = माप as_iso_out_desc,
	.bDescriptorType = USB_DT_CS_ENDPOINT,

	.bDescriptorSubtype = UAC_EP_GENERAL,
	.bmAttributes = 0,
	.bmControls = 0,
	.bLockDelayUnits = 0,
	.wLockDelay = 0,
पूर्ण;

/* Audio Streaming IN Interface - Alt0 */
अटल काष्ठा usb_पूर्णांकerface_descriptor std_as_in_अगर0_desc = अणु
	.bLength = माप std_as_in_अगर0_desc,
	.bDescriptorType = USB_DT_INTERFACE,

	.bAlternateSetting = 0,
	.bNumEndpoपूर्णांकs = 0,
	.bInterfaceClass = USB_CLASS_AUDIO,
	.bInterfaceSubClass = USB_SUBCLASS_AUDIOSTREAMING,
	.bInterfaceProtocol = UAC_VERSION_2,
पूर्ण;

/* Audio Streaming IN Interface - Alt1 */
अटल काष्ठा usb_पूर्णांकerface_descriptor std_as_in_अगर1_desc = अणु
	.bLength = माप std_as_in_अगर1_desc,
	.bDescriptorType = USB_DT_INTERFACE,

	.bAlternateSetting = 1,
	.bNumEndpoपूर्णांकs = 1,
	.bInterfaceClass = USB_CLASS_AUDIO,
	.bInterfaceSubClass = USB_SUBCLASS_AUDIOSTREAMING,
	.bInterfaceProtocol = UAC_VERSION_2,
पूर्ण;

/* Audio Stream IN Intface Desc */
अटल काष्ठा uac2_as_header_descriptor as_in_hdr_desc = अणु
	.bLength = माप as_in_hdr_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,

	.bDescriptorSubtype = UAC_AS_GENERAL,
	/* .bTerminalLink = DYNAMIC */
	.bmControls = 0,
	.bFormatType = UAC_FORMAT_TYPE_I,
	.bmFormats = cpu_to_le32(UAC_FORMAT_TYPE_I_PCM),
	.iChannelNames = 0,
पूर्ण;

/* Audio USB_IN Format */
अटल काष्ठा uac2_क्रमmat_type_i_descriptor as_in_fmt1_desc = अणु
	.bLength = माप as_in_fmt1_desc,
	.bDescriptorType = USB_DT_CS_INTERFACE,
	.bDescriptorSubtype = UAC_FORMAT_TYPE,
	.bFormatType = UAC_FORMAT_TYPE_I,
पूर्ण;

/* STD AS ISO IN Endpoपूर्णांक */
अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_epin_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress = USB_सूची_IN,
	.bmAttributes = USB_ENDPOINT_XFER_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	.bInterval = 1,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_epin_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bmAttributes = USB_ENDPOINT_XFER_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	.bInterval = 4,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_epin_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress = USB_सूची_IN,
	.bmAttributes = USB_ENDPOINT_XFER_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	.bInterval = 4,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_epin_desc_comp = अणु
	.bLength		= माप(ss_epin_desc_comp),
	.bDescriptorType	= USB_DT_SS_ENDPOINT_COMP,
	.bMaxBurst		= 0,
	.bmAttributes		= 0,
	/* wBytesPerInterval = DYNAMIC */
पूर्ण;

/* CS AS ISO IN Endpoपूर्णांक */
अटल काष्ठा uac2_iso_endpoपूर्णांक_descriptor as_iso_in_desc = अणु
	.bLength = माप as_iso_in_desc,
	.bDescriptorType = USB_DT_CS_ENDPOINT,

	.bDescriptorSubtype = UAC_EP_GENERAL,
	.bmAttributes = 0,
	.bmControls = 0,
	.bLockDelayUnits = 0,
	.wLockDelay = 0,
पूर्ण;

अटल काष्ठा usb_descriptor_header *fs_audio_desc[] = अणु
	(काष्ठा usb_descriptor_header *)&iad_desc,
	(काष्ठा usb_descriptor_header *)&std_ac_अगर_desc,

	(काष्ठा usb_descriptor_header *)&ac_hdr_desc,
	(काष्ठा usb_descriptor_header *)&in_clk_src_desc,
	(काष्ठा usb_descriptor_header *)&out_clk_src_desc,
	(काष्ठा usb_descriptor_header *)&usb_out_it_desc,
	(काष्ठा usb_descriptor_header *)&io_in_it_desc,
	(काष्ठा usb_descriptor_header *)&usb_in_ot_desc,
	(काष्ठा usb_descriptor_header *)&io_out_ot_desc,

	(काष्ठा usb_descriptor_header *)&std_as_out_अगर0_desc,
	(काष्ठा usb_descriptor_header *)&std_as_out_अगर1_desc,

	(काष्ठा usb_descriptor_header *)&as_out_hdr_desc,
	(काष्ठा usb_descriptor_header *)&as_out_fmt1_desc,
	(काष्ठा usb_descriptor_header *)&fs_epout_desc,
	(काष्ठा usb_descriptor_header *)&as_iso_out_desc,

	(काष्ठा usb_descriptor_header *)&std_as_in_अगर0_desc,
	(काष्ठा usb_descriptor_header *)&std_as_in_अगर1_desc,

	(काष्ठा usb_descriptor_header *)&as_in_hdr_desc,
	(काष्ठा usb_descriptor_header *)&as_in_fmt1_desc,
	(काष्ठा usb_descriptor_header *)&fs_epin_desc,
	(काष्ठा usb_descriptor_header *)&as_iso_in_desc,
	शून्य,
पूर्ण;

अटल काष्ठा usb_descriptor_header *hs_audio_desc[] = अणु
	(काष्ठा usb_descriptor_header *)&iad_desc,
	(काष्ठा usb_descriptor_header *)&std_ac_अगर_desc,

	(काष्ठा usb_descriptor_header *)&ac_hdr_desc,
	(काष्ठा usb_descriptor_header *)&in_clk_src_desc,
	(काष्ठा usb_descriptor_header *)&out_clk_src_desc,
	(काष्ठा usb_descriptor_header *)&usb_out_it_desc,
	(काष्ठा usb_descriptor_header *)&io_in_it_desc,
	(काष्ठा usb_descriptor_header *)&usb_in_ot_desc,
	(काष्ठा usb_descriptor_header *)&io_out_ot_desc,

	(काष्ठा usb_descriptor_header *)&std_as_out_अगर0_desc,
	(काष्ठा usb_descriptor_header *)&std_as_out_अगर1_desc,

	(काष्ठा usb_descriptor_header *)&as_out_hdr_desc,
	(काष्ठा usb_descriptor_header *)&as_out_fmt1_desc,
	(काष्ठा usb_descriptor_header *)&hs_epout_desc,
	(काष्ठा usb_descriptor_header *)&as_iso_out_desc,

	(काष्ठा usb_descriptor_header *)&std_as_in_अगर0_desc,
	(काष्ठा usb_descriptor_header *)&std_as_in_अगर1_desc,

	(काष्ठा usb_descriptor_header *)&as_in_hdr_desc,
	(काष्ठा usb_descriptor_header *)&as_in_fmt1_desc,
	(काष्ठा usb_descriptor_header *)&hs_epin_desc,
	(काष्ठा usb_descriptor_header *)&as_iso_in_desc,
	शून्य,
पूर्ण;

अटल काष्ठा usb_descriptor_header *ss_audio_desc[] = अणु
	(काष्ठा usb_descriptor_header *)&iad_desc,
	(काष्ठा usb_descriptor_header *)&std_ac_अगर_desc,

	(काष्ठा usb_descriptor_header *)&ac_hdr_desc,
	(काष्ठा usb_descriptor_header *)&in_clk_src_desc,
	(काष्ठा usb_descriptor_header *)&out_clk_src_desc,
	(काष्ठा usb_descriptor_header *)&usb_out_it_desc,
	(काष्ठा usb_descriptor_header *)&io_in_it_desc,
	(काष्ठा usb_descriptor_header *)&usb_in_ot_desc,
	(काष्ठा usb_descriptor_header *)&io_out_ot_desc,

	(काष्ठा usb_descriptor_header *)&std_as_out_अगर0_desc,
	(काष्ठा usb_descriptor_header *)&std_as_out_अगर1_desc,

	(काष्ठा usb_descriptor_header *)&as_out_hdr_desc,
	(काष्ठा usb_descriptor_header *)&as_out_fmt1_desc,
	(काष्ठा usb_descriptor_header *)&ss_epout_desc,
	(काष्ठा usb_descriptor_header *)&ss_epout_desc_comp,
	(काष्ठा usb_descriptor_header *)&as_iso_out_desc,

	(काष्ठा usb_descriptor_header *)&std_as_in_अगर0_desc,
	(काष्ठा usb_descriptor_header *)&std_as_in_अगर1_desc,

	(काष्ठा usb_descriptor_header *)&as_in_hdr_desc,
	(काष्ठा usb_descriptor_header *)&as_in_fmt1_desc,
	(काष्ठा usb_descriptor_header *)&ss_epin_desc,
	(काष्ठा usb_descriptor_header *)&ss_epin_desc_comp,
	(काष्ठा usb_descriptor_header *)&as_iso_in_desc,
	शून्य,
पूर्ण;

काष्ठा cntrl_cur_lay3 अणु
	__le32	dCUR;
पूर्ण;

काष्ठा cntrl_range_lay3 अणु
	__le16	wNumSubRanges;
	__le32	dMIN;
	__le32	dMAX;
	__le32	dRES;
पूर्ण __packed;

अटल पूर्णांक set_ep_max_packet_size(स्थिर काष्ठा f_uac2_opts *uac2_opts,
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc,
	क्रमागत usb_device_speed speed, bool is_playback)
अणु
	पूर्णांक chmask, srate, ssize;
	u16 max_size_bw, max_size_ep;
	अचिन्हित पूर्णांक factor;

	चयन (speed) अणु
	हाल USB_SPEED_FULL:
		max_size_ep = 1023;
		factor = 1000;
		अवरोध;

	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_SUPER:
		max_size_ep = 1024;
		factor = 8000;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (is_playback) अणु
		chmask = uac2_opts->p_chmask;
		srate = uac2_opts->p_srate;
		ssize = uac2_opts->p_ssize;
	पूर्ण अन्यथा अणु
		chmask = uac2_opts->c_chmask;
		srate = uac2_opts->c_srate;
		ssize = uac2_opts->c_ssize;
	पूर्ण

	max_size_bw = num_channels(chmask) * ssize *
		((srate / (factor / (1 << (ep_desc->bInterval - 1)))) + 1);
	ep_desc->wMaxPacketSize = cpu_to_le16(min_t(u16, max_size_bw,
						    max_size_ep));

	वापस 0;
पूर्ण

/* Use macro to overcome line length limitation */
#घोषणा USBDHDR(p) (काष्ठा usb_descriptor_header *)(p)

अटल व्योम setup_headers(काष्ठा f_uac2_opts *opts,
			  काष्ठा usb_descriptor_header **headers,
			  क्रमागत usb_device_speed speed)
अणु
	काष्ठा usb_ss_ep_comp_descriptor *epout_desc_comp = शून्य;
	काष्ठा usb_ss_ep_comp_descriptor *epin_desc_comp = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *epout_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *epin_desc;
	पूर्णांक i;

	चयन (speed) अणु
	हाल USB_SPEED_FULL:
		epout_desc = &fs_epout_desc;
		epin_desc = &fs_epin_desc;
		अवरोध;
	हाल USB_SPEED_HIGH:
		epout_desc = &hs_epout_desc;
		epin_desc = &hs_epin_desc;
		अवरोध;
	शेष:
		epout_desc = &ss_epout_desc;
		epin_desc = &ss_epin_desc;
		epout_desc_comp = &ss_epout_desc_comp;
		epin_desc_comp = &ss_epin_desc_comp;
	पूर्ण

	i = 0;
	headers[i++] = USBDHDR(&iad_desc);
	headers[i++] = USBDHDR(&std_ac_अगर_desc);
	headers[i++] = USBDHDR(&ac_hdr_desc);
	अगर (EPIN_EN(opts))
		headers[i++] = USBDHDR(&in_clk_src_desc);
	अगर (EPOUT_EN(opts)) अणु
		headers[i++] = USBDHDR(&out_clk_src_desc);
		headers[i++] = USBDHDR(&usb_out_it_desc);
	पूर्ण
	अगर (EPIN_EN(opts)) अणु
		headers[i++] = USBDHDR(&io_in_it_desc);
		headers[i++] = USBDHDR(&usb_in_ot_desc);
	पूर्ण
	अगर (EPOUT_EN(opts)) अणु
		headers[i++] = USBDHDR(&io_out_ot_desc);
		headers[i++] = USBDHDR(&std_as_out_अगर0_desc);
		headers[i++] = USBDHDR(&std_as_out_अगर1_desc);
		headers[i++] = USBDHDR(&as_out_hdr_desc);
		headers[i++] = USBDHDR(&as_out_fmt1_desc);
		headers[i++] = USBDHDR(epout_desc);
		अगर (epout_desc_comp)
			headers[i++] = USBDHDR(epout_desc_comp);

		headers[i++] = USBDHDR(&as_iso_out_desc);
	पूर्ण
	अगर (EPIN_EN(opts)) अणु
		headers[i++] = USBDHDR(&std_as_in_अगर0_desc);
		headers[i++] = USBDHDR(&std_as_in_अगर1_desc);
		headers[i++] = USBDHDR(&as_in_hdr_desc);
		headers[i++] = USBDHDR(&as_in_fmt1_desc);
		headers[i++] = USBDHDR(epin_desc);
		अगर (epin_desc_comp)
			headers[i++] = USBDHDR(epin_desc_comp);

		headers[i++] = USBDHDR(&as_iso_in_desc);
	पूर्ण
	headers[i] = शून्य;
पूर्ण

अटल व्योम setup_descriptor(काष्ठा f_uac2_opts *opts)
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
	अगर (EPOUT_EN(opts))
		out_clk_src_desc.bClockID = i++;
	अगर (EPIN_EN(opts))
		in_clk_src_desc.bClockID = i++;

	usb_out_it_desc.bCSourceID = out_clk_src_desc.bClockID;
	usb_in_ot_desc.bSourceID = io_in_it_desc.bTerminalID;
	usb_in_ot_desc.bCSourceID = in_clk_src_desc.bClockID;
	io_in_it_desc.bCSourceID = in_clk_src_desc.bClockID;
	io_out_ot_desc.bCSourceID = out_clk_src_desc.bClockID;
	io_out_ot_desc.bSourceID = usb_out_it_desc.bTerminalID;
	as_out_hdr_desc.bTerminalLink = usb_out_it_desc.bTerminalID;
	as_in_hdr_desc.bTerminalLink = usb_in_ot_desc.bTerminalID;

	iad_desc.bInterfaceCount = 1;
	ac_hdr_desc.wTotalLength = cpu_to_le16(माप(ac_hdr_desc));

	अगर (EPIN_EN(opts)) अणु
		u16 len = le16_to_cpu(ac_hdr_desc.wTotalLength);

		len += माप(in_clk_src_desc);
		len += माप(usb_in_ot_desc);
		len += माप(io_in_it_desc);
		ac_hdr_desc.wTotalLength = cpu_to_le16(len);
		iad_desc.bInterfaceCount++;
	पूर्ण
	अगर (EPOUT_EN(opts)) अणु
		u16 len = le16_to_cpu(ac_hdr_desc.wTotalLength);

		len += माप(out_clk_src_desc);
		len += माप(usb_out_it_desc);
		len += माप(io_out_ot_desc);
		ac_hdr_desc.wTotalLength = cpu_to_le16(len);
		iad_desc.bInterfaceCount++;
	पूर्ण

	setup_headers(opts, fs_audio_desc, USB_SPEED_FULL);
	setup_headers(opts, hs_audio_desc, USB_SPEED_HIGH);
	setup_headers(opts, ss_audio_desc, USB_SPEED_SUPER);
पूर्ण

अटल पूर्णांक afunc_validate_opts(काष्ठा g_audio *agdev, काष्ठा device *dev)
अणु
	काष्ठा f_uac2_opts *opts = g_audio_to_uac2_opts(agdev);

	अगर (!opts->p_chmask && !opts->c_chmask) अणु
		dev_err(dev, "Error: no playback and capture channels\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (opts->p_chmask & ~UAC2_CHANNEL_MASK) अणु
		dev_err(dev, "Error: unsupported playback channels mask\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (opts->c_chmask & ~UAC2_CHANNEL_MASK) अणु
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

अटल पूर्णांक
afunc_bind(काष्ठा usb_configuration *cfg, काष्ठा usb_function *fn)
अणु
	काष्ठा f_uac2 *uac2 = func_to_uac2(fn);
	काष्ठा g_audio *agdev = func_to_g_audio(fn);
	काष्ठा usb_composite_dev *cdev = cfg->cdev;
	काष्ठा usb_gadget *gadget = cdev->gadget;
	काष्ठा device *dev = &gadget->dev;
	काष्ठा f_uac2_opts *uac2_opts = g_audio_to_uac2_opts(agdev);
	काष्ठा usb_string *us;
	पूर्णांक ret;

	ret = afunc_validate_opts(agdev, dev);
	अगर (ret)
		वापस ret;

	us = usb_gstrings_attach(cdev, fn_strings, ARRAY_SIZE(strings_fn));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);
	iad_desc.iFunction = us[STR_ASSOC].id;
	std_ac_अगर_desc.iInterface = us[STR_IF_CTRL].id;
	in_clk_src_desc.iClockSource = us[STR_CLKSRC_IN].id;
	out_clk_src_desc.iClockSource = us[STR_CLKSRC_OUT].id;
	usb_out_it_desc.iTerminal = us[STR_USB_IT].id;
	io_in_it_desc.iTerminal = us[STR_IO_IT].id;
	usb_in_ot_desc.iTerminal = us[STR_USB_OT].id;
	io_out_ot_desc.iTerminal = us[STR_IO_OT].id;
	std_as_out_अगर0_desc.iInterface = us[STR_AS_OUT_ALT0].id;
	std_as_out_अगर1_desc.iInterface = us[STR_AS_OUT_ALT1].id;
	std_as_in_अगर0_desc.iInterface = us[STR_AS_IN_ALT0].id;
	std_as_in_अगर1_desc.iInterface = us[STR_AS_IN_ALT1].id;


	/* Initialize the configurable parameters */
	usb_out_it_desc.bNrChannels = num_channels(uac2_opts->c_chmask);
	usb_out_it_desc.bmChannelConfig = cpu_to_le32(uac2_opts->c_chmask);
	io_in_it_desc.bNrChannels = num_channels(uac2_opts->p_chmask);
	io_in_it_desc.bmChannelConfig = cpu_to_le32(uac2_opts->p_chmask);
	as_out_hdr_desc.bNrChannels = num_channels(uac2_opts->c_chmask);
	as_out_hdr_desc.bmChannelConfig = cpu_to_le32(uac2_opts->c_chmask);
	as_in_hdr_desc.bNrChannels = num_channels(uac2_opts->p_chmask);
	as_in_hdr_desc.bmChannelConfig = cpu_to_le32(uac2_opts->p_chmask);
	as_out_fmt1_desc.bSubslotSize = uac2_opts->c_ssize;
	as_out_fmt1_desc.bBitResolution = uac2_opts->c_ssize * 8;
	as_in_fmt1_desc.bSubslotSize = uac2_opts->p_ssize;
	as_in_fmt1_desc.bBitResolution = uac2_opts->p_ssize * 8;

	snम_लिखो(clksrc_in, माप(clksrc_in), "%uHz", uac2_opts->p_srate);
	snम_लिखो(clksrc_out, माप(clksrc_out), "%uHz", uac2_opts->c_srate);

	ret = usb_पूर्णांकerface_id(cfg, fn);
	अगर (ret < 0) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस ret;
	पूर्ण
	iad_desc.bFirstInterface = ret;

	std_ac_अगर_desc.bInterfaceNumber = ret;
	uac2->ac_पूर्णांकf = ret;
	uac2->ac_alt = 0;

	अगर (EPOUT_EN(uac2_opts)) अणु
		ret = usb_पूर्णांकerface_id(cfg, fn);
		अगर (ret < 0) अणु
			dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
			वापस ret;
		पूर्ण
		std_as_out_अगर0_desc.bInterfaceNumber = ret;
		std_as_out_अगर1_desc.bInterfaceNumber = ret;
		uac2->as_out_पूर्णांकf = ret;
		uac2->as_out_alt = 0;
	पूर्ण

	अगर (EPIN_EN(uac2_opts)) अणु
		ret = usb_पूर्णांकerface_id(cfg, fn);
		अगर (ret < 0) अणु
			dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
			वापस ret;
		पूर्ण
		std_as_in_अगर0_desc.bInterfaceNumber = ret;
		std_as_in_अगर1_desc.bInterfaceNumber = ret;
		uac2->as_in_पूर्णांकf = ret;
		uac2->as_in_alt = 0;
	पूर्ण

	/* Calculate wMaxPacketSize according to audio bandwidth */
	ret = set_ep_max_packet_size(uac2_opts, &fs_epin_desc, USB_SPEED_FULL,
				     true);
	अगर (ret < 0) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस ret;
	पूर्ण

	ret = set_ep_max_packet_size(uac2_opts, &fs_epout_desc, USB_SPEED_FULL,
				     false);
	अगर (ret < 0) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस ret;
	पूर्ण

	ret = set_ep_max_packet_size(uac2_opts, &hs_epin_desc, USB_SPEED_HIGH,
				     true);
	अगर (ret < 0) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस ret;
	पूर्ण

	ret = set_ep_max_packet_size(uac2_opts, &hs_epout_desc, USB_SPEED_HIGH,
				     false);
	अगर (ret < 0) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस ret;
	पूर्ण

	ret = set_ep_max_packet_size(uac2_opts, &ss_epin_desc, USB_SPEED_SUPER,
				     true);
	अगर (ret < 0) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस ret;
	पूर्ण

	ret = set_ep_max_packet_size(uac2_opts, &ss_epout_desc, USB_SPEED_SUPER,
				     false);
	अगर (ret < 0) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस ret;
	पूर्ण

	अगर (EPOUT_EN(uac2_opts)) अणु
		agdev->out_ep = usb_ep_स्वतःconfig(gadget, &fs_epout_desc);
		अगर (!agdev->out_ep) अणु
			dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (EPIN_EN(uac2_opts)) अणु
		agdev->in_ep = usb_ep_स्वतःconfig(gadget, &fs_epin_desc);
		अगर (!agdev->in_ep) अणु
			dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	agdev->in_ep_maxpsize = max_t(u16,
				le16_to_cpu(fs_epin_desc.wMaxPacketSize),
				le16_to_cpu(hs_epin_desc.wMaxPacketSize));
	agdev->out_ep_maxpsize = max_t(u16,
				le16_to_cpu(fs_epout_desc.wMaxPacketSize),
				le16_to_cpu(hs_epout_desc.wMaxPacketSize));

	agdev->in_ep_maxpsize = max_t(u16, agdev->in_ep_maxpsize,
				le16_to_cpu(ss_epin_desc.wMaxPacketSize));
	agdev->out_ep_maxpsize = max_t(u16, agdev->out_ep_maxpsize,
				le16_to_cpu(ss_epout_desc.wMaxPacketSize));

	hs_epout_desc.bEndpoपूर्णांकAddress = fs_epout_desc.bEndpoपूर्णांकAddress;
	hs_epin_desc.bEndpoपूर्णांकAddress = fs_epin_desc.bEndpoपूर्णांकAddress;
	ss_epout_desc.bEndpoपूर्णांकAddress = fs_epout_desc.bEndpoपूर्णांकAddress;
	ss_epin_desc.bEndpoपूर्णांकAddress = fs_epin_desc.bEndpoपूर्णांकAddress;

	setup_descriptor(uac2_opts);

	ret = usb_assign_descriptors(fn, fs_audio_desc, hs_audio_desc, ss_audio_desc,
				     ss_audio_desc);
	अगर (ret)
		वापस ret;

	agdev->gadget = gadget;

	agdev->params.p_chmask = uac2_opts->p_chmask;
	agdev->params.p_srate = uac2_opts->p_srate;
	agdev->params.p_ssize = uac2_opts->p_ssize;
	agdev->params.c_chmask = uac2_opts->c_chmask;
	agdev->params.c_srate = uac2_opts->c_srate;
	agdev->params.c_ssize = uac2_opts->c_ssize;
	agdev->params.req_number = uac2_opts->req_number;
	ret = g_audio_setup(agdev, "UAC2 PCM", "UAC2_Gadget");
	अगर (ret)
		जाओ err_मुक्त_descs;
	वापस 0;

err_मुक्त_descs:
	usb_मुक्त_all_descriptors(fn);
	agdev->gadget = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक
afunc_set_alt(काष्ठा usb_function *fn, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा usb_composite_dev *cdev = fn->config->cdev;
	काष्ठा f_uac2 *uac2 = func_to_uac2(fn);
	काष्ठा usb_gadget *gadget = cdev->gadget;
	काष्ठा device *dev = &gadget->dev;
	पूर्णांक ret = 0;

	/* No i/f has more than 2 alt settings */
	अगर (alt > 1) अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकf == uac2->ac_पूर्णांकf) अणु
		/* Control I/f has only 1 AltSetting - 0 */
		अगर (alt) अणु
			dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (पूर्णांकf == uac2->as_out_पूर्णांकf) अणु
		uac2->as_out_alt = alt;

		अगर (alt)
			ret = u_audio_start_capture(&uac2->g_audio);
		अन्यथा
			u_audio_stop_capture(&uac2->g_audio);
	पूर्ण अन्यथा अगर (पूर्णांकf == uac2->as_in_पूर्णांकf) अणु
		uac2->as_in_alt = alt;

		अगर (alt)
			ret = u_audio_start_playback(&uac2->g_audio);
		अन्यथा
			u_audio_stop_playback(&uac2->g_audio);
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
afunc_get_alt(काष्ठा usb_function *fn, अचिन्हित पूर्णांकf)
अणु
	काष्ठा f_uac2 *uac2 = func_to_uac2(fn);
	काष्ठा g_audio *agdev = func_to_g_audio(fn);

	अगर (पूर्णांकf == uac2->ac_पूर्णांकf)
		वापस uac2->ac_alt;
	अन्यथा अगर (पूर्णांकf == uac2->as_out_पूर्णांकf)
		वापस uac2->as_out_alt;
	अन्यथा अगर (पूर्णांकf == uac2->as_in_पूर्णांकf)
		वापस uac2->as_in_alt;
	अन्यथा
		dev_err(&agdev->gadget->dev,
			"%s:%d Invalid Interface %d!\n",
			__func__, __LINE__, पूर्णांकf);

	वापस -EINVAL;
पूर्ण

अटल व्योम
afunc_disable(काष्ठा usb_function *fn)
अणु
	काष्ठा f_uac2 *uac2 = func_to_uac2(fn);

	uac2->as_in_alt = 0;
	uac2->as_out_alt = 0;
	u_audio_stop_capture(&uac2->g_audio);
	u_audio_stop_playback(&uac2->g_audio);
पूर्ण

अटल पूर्णांक
in_rq_cur(काष्ठा usb_function *fn, स्थिर काष्ठा usb_ctrlrequest *cr)
अणु
	काष्ठा usb_request *req = fn->config->cdev->req;
	काष्ठा g_audio *agdev = func_to_g_audio(fn);
	काष्ठा f_uac2_opts *opts;
	u16 w_length = le16_to_cpu(cr->wLength);
	u16 w_index = le16_to_cpu(cr->wIndex);
	u16 w_value = le16_to_cpu(cr->wValue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 control_selector = w_value >> 8;
	पूर्णांक value = -EOPNOTSUPP;
	पूर्णांक p_srate, c_srate;

	opts = g_audio_to_uac2_opts(agdev);
	p_srate = opts->p_srate;
	c_srate = opts->c_srate;

	अगर (control_selector == UAC2_CS_CONTROL_SAM_FREQ) अणु
		काष्ठा cntrl_cur_lay3 c;
		स_रखो(&c, 0, माप(काष्ठा cntrl_cur_lay3));

		अगर (entity_id == USB_IN_CLK_ID)
			c.dCUR = cpu_to_le32(p_srate);
		अन्यथा अगर (entity_id == USB_OUT_CLK_ID)
			c.dCUR = cpu_to_le32(c_srate);

		value = min_t(अचिन्हित, w_length, माप c);
		स_नकल(req->buf, &c, value);
	पूर्ण अन्यथा अगर (control_selector == UAC2_CS_CONTROL_CLOCK_VALID) अणु
		*(u8 *)req->buf = 1;
		value = min_t(अचिन्हित, w_length, 1);
	पूर्ण अन्यथा अणु
		dev_err(&agdev->gadget->dev,
			"%s:%d control_selector=%d TODO!\n",
			__func__, __LINE__, control_selector);
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक
in_rq_range(काष्ठा usb_function *fn, स्थिर काष्ठा usb_ctrlrequest *cr)
अणु
	काष्ठा usb_request *req = fn->config->cdev->req;
	काष्ठा g_audio *agdev = func_to_g_audio(fn);
	काष्ठा f_uac2_opts *opts;
	u16 w_length = le16_to_cpu(cr->wLength);
	u16 w_index = le16_to_cpu(cr->wIndex);
	u16 w_value = le16_to_cpu(cr->wValue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 control_selector = w_value >> 8;
	काष्ठा cntrl_range_lay3 r;
	पूर्णांक value = -EOPNOTSUPP;
	पूर्णांक p_srate, c_srate;

	opts = g_audio_to_uac2_opts(agdev);
	p_srate = opts->p_srate;
	c_srate = opts->c_srate;

	अगर (control_selector == UAC2_CS_CONTROL_SAM_FREQ) अणु
		अगर (entity_id == USB_IN_CLK_ID)
			r.dMIN = cpu_to_le32(p_srate);
		अन्यथा अगर (entity_id == USB_OUT_CLK_ID)
			r.dMIN = cpu_to_le32(c_srate);
		अन्यथा
			वापस -EOPNOTSUPP;

		r.dMAX = r.dMIN;
		r.dRES = 0;
		r.wNumSubRanges = cpu_to_le16(1);

		value = min_t(अचिन्हित, w_length, माप r);
		स_नकल(req->buf, &r, value);
	पूर्ण अन्यथा अणु
		dev_err(&agdev->gadget->dev,
			"%s:%d control_selector=%d TODO!\n",
			__func__, __LINE__, control_selector);
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक
ac_rq_in(काष्ठा usb_function *fn, स्थिर काष्ठा usb_ctrlrequest *cr)
अणु
	अगर (cr->bRequest == UAC2_CS_CUR)
		वापस in_rq_cur(fn, cr);
	अन्यथा अगर (cr->bRequest == UAC2_CS_RANGE)
		वापस in_rq_range(fn, cr);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
out_rq_cur(काष्ठा usb_function *fn, स्थिर काष्ठा usb_ctrlrequest *cr)
अणु
	u16 w_length = le16_to_cpu(cr->wLength);
	u16 w_value = le16_to_cpu(cr->wValue);
	u8 control_selector = w_value >> 8;

	अगर (control_selector == UAC2_CS_CONTROL_SAM_FREQ)
		वापस w_length;

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
setup_rq_inf(काष्ठा usb_function *fn, स्थिर काष्ठा usb_ctrlrequest *cr)
अणु
	काष्ठा f_uac2 *uac2 = func_to_uac2(fn);
	काष्ठा g_audio *agdev = func_to_g_audio(fn);
	u16 w_index = le16_to_cpu(cr->wIndex);
	u8 पूर्णांकf = w_index & 0xff;

	अगर (पूर्णांकf != uac2->ac_पूर्णांकf) अणु
		dev_err(&agdev->gadget->dev,
			"%s:%d Error!\n", __func__, __LINE__);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (cr->bRequestType & USB_सूची_IN)
		वापस ac_rq_in(fn, cr);
	अन्यथा अगर (cr->bRequest == UAC2_CS_CUR)
		वापस out_rq_cur(fn, cr);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
afunc_setup(काष्ठा usb_function *fn, स्थिर काष्ठा usb_ctrlrequest *cr)
अणु
	काष्ठा usb_composite_dev *cdev = fn->config->cdev;
	काष्ठा g_audio *agdev = func_to_g_audio(fn);
	काष्ठा usb_request *req = cdev->req;
	u16 w_length = le16_to_cpu(cr->wLength);
	पूर्णांक value = -EOPNOTSUPP;

	/* Only Class specअगरic requests are supposed to reach here */
	अगर ((cr->bRequestType & USB_TYPE_MASK) != USB_TYPE_CLASS)
		वापस -EOPNOTSUPP;

	अगर ((cr->bRequestType & USB_RECIP_MASK) == USB_RECIP_INTERFACE)
		value = setup_rq_inf(fn, cr);
	अन्यथा
		dev_err(&agdev->gadget->dev, "%s:%d Error!\n",
				__func__, __LINE__);

	अगर (value >= 0) अणु
		req->length = value;
		req->zero = value < w_length;
		value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
		अगर (value < 0) अणु
			dev_err(&agdev->gadget->dev,
				"%s:%d Error!\n", __func__, __LINE__);
			req->status = 0;
		पूर्ण
	पूर्ण

	वापस value;
पूर्ण

अटल अंतरभूत काष्ठा f_uac2_opts *to_f_uac2_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_uac2_opts,
			    func_inst.group);
पूर्ण

अटल व्योम f_uac2_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_uac2_opts *opts = to_f_uac2_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations f_uac2_item_ops = अणु
	.release	= f_uac2_attr_release,
पूर्ण;

#घोषणा UAC2_ATTRIBUTE(name)						\
अटल sमाप_प्रकार f_uac2_opts_##name##_show(काष्ठा config_item *item,	\
					 अक्षर *page)			\
अणु									\
	काष्ठा f_uac2_opts *opts = to_f_uac2_opts(item);		\
	पूर्णांक result;							\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", opts->name);			\
	mutex_unlock(&opts->lock);					\
									\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार f_uac2_opts_##name##_store(काष्ठा config_item *item,	\
					  स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा f_uac2_opts *opts = to_f_uac2_opts(item);		\
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
CONFIGFS_ATTR(f_uac2_opts_, name)

UAC2_ATTRIBUTE(p_chmask);
UAC2_ATTRIBUTE(p_srate);
UAC2_ATTRIBUTE(p_ssize);
UAC2_ATTRIBUTE(c_chmask);
UAC2_ATTRIBUTE(c_srate);
UAC2_ATTRIBUTE(c_ssize);
UAC2_ATTRIBUTE(req_number);

अटल काष्ठा configfs_attribute *f_uac2_attrs[] = अणु
	&f_uac2_opts_attr_p_chmask,
	&f_uac2_opts_attr_p_srate,
	&f_uac2_opts_attr_p_ssize,
	&f_uac2_opts_attr_c_chmask,
	&f_uac2_opts_attr_c_srate,
	&f_uac2_opts_attr_c_ssize,
	&f_uac2_opts_attr_req_number,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type f_uac2_func_type = अणु
	.ct_item_ops	= &f_uac2_item_ops,
	.ct_attrs	= f_uac2_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम afunc_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_uac2_opts *opts;

	opts = container_of(f, काष्ठा f_uac2_opts, func_inst);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *afunc_alloc_inst(व्योम)
अणु
	काष्ठा f_uac2_opts *opts;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = afunc_मुक्त_inst;

	config_group_init_type_name(&opts->func_inst.group, "",
				    &f_uac2_func_type);

	opts->p_chmask = UAC2_DEF_PCHMASK;
	opts->p_srate = UAC2_DEF_PSRATE;
	opts->p_ssize = UAC2_DEF_PSSIZE;
	opts->c_chmask = UAC2_DEF_CCHMASK;
	opts->c_srate = UAC2_DEF_CSRATE;
	opts->c_ssize = UAC2_DEF_CSSIZE;
	opts->req_number = UAC2_DEF_REQ_NUM;
	वापस &opts->func_inst;
पूर्ण

अटल व्योम afunc_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा g_audio *agdev;
	काष्ठा f_uac2_opts *opts;

	agdev = func_to_g_audio(f);
	opts = container_of(f->fi, काष्ठा f_uac2_opts, func_inst);
	kमुक्त(agdev);
	mutex_lock(&opts->lock);
	--opts->refcnt;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम afunc_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा g_audio *agdev = func_to_g_audio(f);

	g_audio_cleanup(agdev);
	usb_मुक्त_all_descriptors(f);

	agdev->gadget = शून्य;
पूर्ण

अटल काष्ठा usb_function *afunc_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_uac2	*uac2;
	काष्ठा f_uac2_opts *opts;

	uac2 = kzalloc(माप(*uac2), GFP_KERNEL);
	अगर (uac2 == शून्य)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_uac2_opts, func_inst);
	mutex_lock(&opts->lock);
	++opts->refcnt;
	mutex_unlock(&opts->lock);

	uac2->g_audio.func.name = "uac2_func";
	uac2->g_audio.func.bind = afunc_bind;
	uac2->g_audio.func.unbind = afunc_unbind;
	uac2->g_audio.func.set_alt = afunc_set_alt;
	uac2->g_audio.func.get_alt = afunc_get_alt;
	uac2->g_audio.func.disable = afunc_disable;
	uac2->g_audio.func.setup = afunc_setup;
	uac2->g_audio.func.मुक्त_func = afunc_मुक्त;

	वापस &uac2->g_audio.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(uac2, afunc_alloc_inst, afunc_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yadwinder Singh");
MODULE_AUTHOR("Jaswinder Singh");

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_audio.c -- USB Audio class function driver
  *
 * Copyright (C) 2008 Bryan Wu <cooloney@kernel.org>
 * Copyright (C) 2008 Analog Devices, Inc
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/atomic.h>

#समावेश "u_uac1_legacy.h"

अटल पूर्णांक generic_set_cmd(काष्ठा usb_audio_control *con, u8 cmd, पूर्णांक value);
अटल पूर्णांक generic_get_cmd(काष्ठा usb_audio_control *con, u8 cmd);

/*
 * DESCRIPTORS ... most are अटल, but strings and full
 * configuration descriptors are built on demand.
 */

/*
 * We have two पूर्णांकerfaces- AudioControl and AudioStreaming
 * TODO: only supcard playback currently
 */
#घोषणा F_AUDIO_AC_INTERFACE	0
#घोषणा F_AUDIO_AS_INTERFACE	1
#घोषणा F_AUDIO_NUM_INTERFACES	1

/* B.3.1  Standard AC Interface Descriptor */
अटल काष्ठा usb_पूर्णांकerface_descriptor ac_पूर्णांकerface_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bNumEndpoपूर्णांकs =	0,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOCONTROL,
पूर्ण;

/*
 * The number of AudioStreaming and MIDIStreaming पूर्णांकerfaces
 * in the Audio Interface Collection
 */
DECLARE_UAC_AC_HEADER_DESCRIPTOR(1);

#घोषणा UAC_DT_AC_HEADER_LENGTH	UAC_DT_AC_HEADER_SIZE(F_AUDIO_NUM_INTERFACES)
/* 1 input terminal, 1 output terminal and 1 feature unit */
#घोषणा UAC_DT_TOTAL_LENGTH (UAC_DT_AC_HEADER_LENGTH + UAC_DT_INPUT_TERMINAL_SIZE \
	+ UAC_DT_OUTPUT_TERMINAL_SIZE + UAC_DT_FEATURE_UNIT_SIZE(0))
/* B.3.2  Class-Specअगरic AC Interface Descriptor */
अटल काष्ठा uac1_ac_header_descriptor_1 ac_header_desc = अणु
	.bLength =		UAC_DT_AC_HEADER_LENGTH,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_HEADER,
	.bcdADC =		cpu_to_le16(0x0100),
	.wTotalLength =		cpu_to_le16(UAC_DT_TOTAL_LENGTH),
	.bInCollection =	F_AUDIO_NUM_INTERFACES,
	.baInterfaceNr = अणु
	/* Interface number of the first AudioStream पूर्णांकerface */
		[0] =		1,
	पूर्ण
पूर्ण;

#घोषणा INPUT_TERMINAL_ID	1
अटल काष्ठा uac_input_terminal_descriptor input_terminal_desc = अणु
	.bLength =		UAC_DT_INPUT_TERMINAL_SIZE,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_INPUT_TERMINAL,
	.bTerminalID =		INPUT_TERMINAL_ID,
	.wTerminalType =	UAC_TERMINAL_STREAMING,
	.bAssocTerminal =	0,
	.wChannelConfig =	0x3,
पूर्ण;

DECLARE_UAC_FEATURE_UNIT_DESCRIPTOR(0);

#घोषणा FEATURE_UNIT_ID		2
अटल काष्ठा uac_feature_unit_descriptor_0 feature_unit_desc = अणु
	.bLength		= UAC_DT_FEATURE_UNIT_SIZE(0),
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubtype	= UAC_FEATURE_UNIT,
	.bUnitID		= FEATURE_UNIT_ID,
	.bSourceID		= INPUT_TERMINAL_ID,
	.bControlSize		= 2,
	.bmaControls[0]		= (UAC_FU_MUTE | UAC_FU_VOLUME),
पूर्ण;

अटल काष्ठा usb_audio_control mute_control = अणु
	.list = LIST_HEAD_INIT(mute_control.list),
	.name = "Mute Control",
	.type = UAC_FU_MUTE,
	/* Toकरो: add real Mute control code */
	.set = generic_set_cmd,
	.get = generic_get_cmd,
पूर्ण;

अटल काष्ठा usb_audio_control volume_control = अणु
	.list = LIST_HEAD_INIT(volume_control.list),
	.name = "Volume Control",
	.type = UAC_FU_VOLUME,
	/* Toकरो: add real Volume control code */
	.set = generic_set_cmd,
	.get = generic_get_cmd,
पूर्ण;

अटल काष्ठा usb_audio_control_selector feature_unit = अणु
	.list = LIST_HEAD_INIT(feature_unit.list),
	.id = FEATURE_UNIT_ID,
	.name = "Mute & Volume Control",
	.type = UAC_FEATURE_UNIT,
	.desc = (काष्ठा usb_descriptor_header *)&feature_unit_desc,
पूर्ण;

#घोषणा OUTPUT_TERMINAL_ID	3
अटल काष्ठा uac1_output_terminal_descriptor output_terminal_desc = अणु
	.bLength		= UAC_DT_OUTPUT_TERMINAL_SIZE,
	.bDescriptorType	= USB_DT_CS_INTERFACE,
	.bDescriptorSubtype	= UAC_OUTPUT_TERMINAL,
	.bTerminalID		= OUTPUT_TERMINAL_ID,
	.wTerminalType		= UAC_OUTPUT_TERMINAL_SPEAKER,
	.bAssocTerminal		= FEATURE_UNIT_ID,
	.bSourceID		= FEATURE_UNIT_ID,
पूर्ण;

/* B.4.1  Standard AS Interface Descriptor */
अटल काष्ठा usb_पूर्णांकerface_descriptor as_पूर्णांकerface_alt_0_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bAlternateSetting =	0,
	.bNumEndpoपूर्णांकs =	0,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOSTREAMING,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor as_पूर्णांकerface_alt_1_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bAlternateSetting =	1,
	.bNumEndpoपूर्णांकs =	1,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOSTREAMING,
पूर्ण;

/* B.4.2  Class-Specअगरic AS Interface Descriptor */
अटल काष्ठा uac1_as_header_descriptor as_header_desc = अणु
	.bLength =		UAC_DT_AS_HEADER_SIZE,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	UAC_AS_GENERAL,
	.bTerminalLink =	INPUT_TERMINAL_ID,
	.bDelay =		1,
	.wFormatTag =		UAC_FORMAT_TYPE_I_PCM,
पूर्ण;

DECLARE_UAC_FORMAT_TYPE_I_DISCRETE_DESC(1);

अटल काष्ठा uac_क्रमmat_type_i_discrete_descriptor_1 as_type_i_desc = अणु
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
	.bmAttributes = 	1,
	.bLockDelayUnits =	1,
	.wLockDelay =		cpu_to_le16(1),
पूर्ण;

अटल काष्ठा usb_descriptor_header *f_audio_desc[] = अणु
	(काष्ठा usb_descriptor_header *)&ac_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *)&ac_header_desc,

	(काष्ठा usb_descriptor_header *)&input_terminal_desc,
	(काष्ठा usb_descriptor_header *)&output_terminal_desc,
	(काष्ठा usb_descriptor_header *)&feature_unit_desc,

	(काष्ठा usb_descriptor_header *)&as_पूर्णांकerface_alt_0_desc,
	(काष्ठा usb_descriptor_header *)&as_पूर्णांकerface_alt_1_desc,
	(काष्ठा usb_descriptor_header *)&as_header_desc,

	(काष्ठा usb_descriptor_header *)&as_type_i_desc,

	(काष्ठा usb_descriptor_header *)&as_out_ep_desc,
	(काष्ठा usb_descriptor_header *)&as_iso_out_desc,
	शून्य,
पूर्ण;

क्रमागत अणु
	STR_AC_IF,
	STR_INPUT_TERMINAL,
	STR_INPUT_TERMINAL_CH_NAMES,
	STR_FEAT_DESC_0,
	STR_OUTPUT_TERMINAL,
	STR_AS_IF_ALT0,
	STR_AS_IF_ALT1,
पूर्ण;

अटल काष्ठा usb_string strings_uac1[] = अणु
	[STR_AC_IF].s = "AC Interface",
	[STR_INPUT_TERMINAL].s = "Input terminal",
	[STR_INPUT_TERMINAL_CH_NAMES].s = "Channels",
	[STR_FEAT_DESC_0].s = "Volume control & mute",
	[STR_OUTPUT_TERMINAL].s = "Output terminal",
	[STR_AS_IF_ALT0].s = "AS Interface",
	[STR_AS_IF_ALT1].s = "AS Interface",
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

/*-------------------------------------------------------------------------*/
काष्ठा f_audio_buf अणु
	u8 *buf;
	पूर्णांक actual;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा f_audio_buf *f_audio_buffer_alloc(पूर्णांक buf_size)
अणु
	काष्ठा f_audio_buf *copy_buf;

	copy_buf = kzalloc(माप *copy_buf, GFP_ATOMIC);
	अगर (!copy_buf)
		वापस ERR_PTR(-ENOMEM);

	copy_buf->buf = kzalloc(buf_size, GFP_ATOMIC);
	अगर (!copy_buf->buf) अणु
		kमुक्त(copy_buf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस copy_buf;
पूर्ण

अटल व्योम f_audio_buffer_मुक्त(काष्ठा f_audio_buf *audio_buf)
अणु
	kमुक्त(audio_buf->buf);
	kमुक्त(audio_buf);
पूर्ण
/*-------------------------------------------------------------------------*/

काष्ठा f_audio अणु
	काष्ठा gaudio			card;

	u8 ac_पूर्णांकf, ac_alt;
	u8 as_पूर्णांकf, as_alt;

	/* endpoपूर्णांकs handle full and/or high speeds */
	काष्ठा usb_ep			*out_ep;

	spinlock_t			lock;
	काष्ठा f_audio_buf *copy_buf;
	काष्ठा work_काष्ठा playback_work;
	काष्ठा list_head play_queue;

	/* Control Set command */
	काष्ठा list_head cs;
	u8 set_cmd;
	काष्ठा usb_audio_control *set_con;
पूर्ण;

अटल अंतरभूत काष्ठा f_audio *func_to_audio(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_audio, card.func);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम f_audio_playback_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा f_audio *audio = container_of(data, काष्ठा f_audio,
					playback_work);
	काष्ठा f_audio_buf *play_buf;

	spin_lock_irq(&audio->lock);
	अगर (list_empty(&audio->play_queue)) अणु
		spin_unlock_irq(&audio->lock);
		वापस;
	पूर्ण
	play_buf = list_first_entry(&audio->play_queue,
			काष्ठा f_audio_buf, list);
	list_del(&play_buf->list);
	spin_unlock_irq(&audio->lock);

	u_audio_playback(&audio->card, play_buf->buf, play_buf->actual);
	f_audio_buffer_मुक्त(play_buf);
पूर्ण

अटल पूर्णांक f_audio_out_ep_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_audio *audio = req->context;
	काष्ठा usb_composite_dev *cdev = audio->card.func.config->cdev;
	काष्ठा f_audio_buf *copy_buf = audio->copy_buf;
	काष्ठा f_uac1_legacy_opts *opts;
	पूर्णांक audio_buf_size;
	पूर्णांक err;

	opts = container_of(audio->card.func.fi, काष्ठा f_uac1_legacy_opts,
			    func_inst);
	audio_buf_size = opts->audio_buf_size;

	अगर (!copy_buf)
		वापस -EINVAL;

	/* Copy buffer is full, add it to the play_queue */
	अगर (audio_buf_size - copy_buf->actual < req->actual) अणु
		spin_lock_irq(&audio->lock);
		list_add_tail(&copy_buf->list, &audio->play_queue);
		spin_unlock_irq(&audio->lock);
		schedule_work(&audio->playback_work);
		copy_buf = f_audio_buffer_alloc(audio_buf_size);
		अगर (IS_ERR(copy_buf))
			वापस -ENOMEM;
	पूर्ण

	स_नकल(copy_buf->buf + copy_buf->actual, req->buf, req->actual);
	copy_buf->actual += req->actual;
	audio->copy_buf = copy_buf;

	err = usb_ep_queue(ep, req, GFP_ATOMIC);
	अगर (err)
		ERROR(cdev, "%s queue req: %d\n", ep->name, err);

	वापस 0;

पूर्ण

अटल व्योम f_audio_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_audio *audio = req->context;
	पूर्णांक status = req->status;
	u32 data = 0;
	काष्ठा usb_ep *out_ep = audio->out_ep;

	चयन (status) अणु

	हाल 0:				/* normal completion? */
		अगर (ep == out_ep)
			f_audio_out_ep_complete(ep, req);
		अन्यथा अगर (audio->set_con) अणु
			स_नकल(&data, req->buf, req->length);
			audio->set_con->set(audio->set_con, audio->set_cmd,
					le16_to_cpu(data));
			audio->set_con = शून्य;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक audio_set_पूर्णांकf_req(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_audio		*audio = func_to_audio(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_request	*req = cdev->req;
	u8			id = ((le16_to_cpu(ctrl->wIndex) >> 8) & 0xFF);
	u16			len = le16_to_cpu(ctrl->wLength);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u8			con_sel = (w_value >> 8) & 0xFF;
	u8			cmd = (ctrl->bRequest & 0x0F);
	काष्ठा usb_audio_control_selector *cs;
	काष्ठा usb_audio_control *con;

	DBG(cdev, "bRequest 0x%x, w_value 0x%04x, len %d, entity %d\n",
			ctrl->bRequest, w_value, len, id);

	list_क्रम_each_entry(cs, &audio->cs, list) अणु
		अगर (cs->id == id) अणु
			list_क्रम_each_entry(con, &cs->control, list) अणु
				अगर (con->type == con_sel) अणु
					audio->set_con = con;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	audio->set_cmd = cmd;
	req->context = audio;
	req->complete = f_audio_complete;

	वापस len;
पूर्ण

अटल पूर्णांक audio_get_पूर्णांकf_req(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_audio		*audio = func_to_audio(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_request	*req = cdev->req;
	पूर्णांक			value = -EOPNOTSUPP;
	u8			id = ((le16_to_cpu(ctrl->wIndex) >> 8) & 0xFF);
	u16			len = le16_to_cpu(ctrl->wLength);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u8			con_sel = (w_value >> 8) & 0xFF;
	u8			cmd = (ctrl->bRequest & 0x0F);
	काष्ठा usb_audio_control_selector *cs;
	काष्ठा usb_audio_control *con;

	DBG(cdev, "bRequest 0x%x, w_value 0x%04x, len %d, entity %d\n",
			ctrl->bRequest, w_value, len, id);

	list_क्रम_each_entry(cs, &audio->cs, list) अणु
		अगर (cs->id == id) अणु
			list_क्रम_each_entry(con, &cs->control, list) अणु
				अगर (con->type == con_sel && con->get) अणु
					value = con->get(con, cmd);
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	req->context = audio;
	req->complete = f_audio_complete;
	len = min_t(माप_प्रकार, माप(value), len);
	स_नकल(req->buf, &value, len);

	वापस len;
पूर्ण

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
	हाल USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE:
		value = audio_set_पूर्णांकf_req(f, ctrl);
		अवरोध;

	हाल USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE:
		value = audio_get_पूर्णांकf_req(f, ctrl);
		अवरोध;

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
	काष्ठा f_audio		*audio = func_to_audio(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_ep *out_ep = audio->out_ep;
	काष्ठा usb_request *req;
	काष्ठा f_uac1_legacy_opts *opts;
	पूर्णांक req_buf_size, req_count, audio_buf_size;
	पूर्णांक i = 0, err = 0;

	DBG(cdev, "intf %d, alt %d\n", पूर्णांकf, alt);

	opts = container_of(f->fi, काष्ठा f_uac1_legacy_opts, func_inst);
	req_buf_size = opts->req_buf_size;
	req_count = opts->req_count;
	audio_buf_size = opts->audio_buf_size;

	/* No i/f has more than 2 alt settings */
	अगर (alt > 1) अणु
		ERROR(cdev, "%s:%d Error!\n", __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकf == audio->ac_पूर्णांकf) अणु
		/* Control I/f has only 1 AltSetting - 0 */
		अगर (alt) अणु
			ERROR(cdev, "%s:%d Error!\n", __func__, __LINE__);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (पूर्णांकf == audio->as_पूर्णांकf) अणु
		अगर (alt == 1) अणु
			err = config_ep_by_speed(cdev->gadget, f, out_ep);
			अगर (err)
				वापस err;

			usb_ep_enable(out_ep);
			audio->copy_buf = f_audio_buffer_alloc(audio_buf_size);
			अगर (IS_ERR(audio->copy_buf))
				वापस -ENOMEM;

			/*
			 * allocate a bunch of पढ़ो buffers
			 * and queue them all at once.
			 */
			क्रम (i = 0; i < req_count && err == 0; i++) अणु
				req = usb_ep_alloc_request(out_ep, GFP_ATOMIC);
				अगर (req) अणु
					req->buf = kzalloc(req_buf_size,
							GFP_ATOMIC);
					अगर (req->buf) अणु
						req->length = req_buf_size;
						req->context = audio;
						req->complete =
							f_audio_complete;
						err = usb_ep_queue(out_ep,
							req, GFP_ATOMIC);
						अगर (err)
							ERROR(cdev,
							"%s queue req: %d\n",
							out_ep->name, err);
					पूर्ण अन्यथा
						err = -ENOMEM;
				पूर्ण अन्यथा
					err = -ENOMEM;
			पूर्ण

		पूर्ण अन्यथा अणु
			काष्ठा f_audio_buf *copy_buf = audio->copy_buf;
			अगर (copy_buf) अणु
				list_add_tail(&copy_buf->list,
						&audio->play_queue);
				schedule_work(&audio->playback_work);
			पूर्ण
		पूर्ण
		audio->as_alt = alt;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक f_audio_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf)
अणु
	काष्ठा f_audio		*audio = func_to_audio(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	अगर (पूर्णांकf == audio->ac_पूर्णांकf)
		वापस audio->ac_alt;
	अन्यथा अगर (पूर्णांकf == audio->as_पूर्णांकf)
		वापस audio->as_alt;
	अन्यथा
		ERROR(cdev, "%s:%d Invalid Interface %d!\n",
		      __func__, __LINE__, पूर्णांकf);

	वापस -EINVAL;
पूर्ण

अटल व्योम f_audio_disable(काष्ठा usb_function *f)
अणु
	वापस;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम f_audio_build_desc(काष्ठा f_audio *audio)
अणु
	काष्ठा gaudio *card = &audio->card;
	u8 *sam_freq;
	पूर्णांक rate;

	/* Set channel numbers */
	input_terminal_desc.bNrChannels = u_audio_get_playback_channels(card);
	as_type_i_desc.bNrChannels = u_audio_get_playback_channels(card);

	/* Set sample rates */
	rate = u_audio_get_playback_rate(card);
	sam_freq = as_type_i_desc.tSamFreq[0];
	स_नकल(sam_freq, &rate, 3);

	/* Toकरो: Set Sample bits and other parameters */

	वापस;
पूर्ण

/* audio function driver setup/binding */
अटल पूर्णांक
f_audio_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_audio		*audio = func_to_audio(f);
	काष्ठा usb_string	*us;
	पूर्णांक			status;
	काष्ठा usb_ep		*ep = शून्य;
	काष्ठा f_uac1_legacy_opts	*audio_opts;

	audio_opts = container_of(f->fi, काष्ठा f_uac1_legacy_opts, func_inst);
	audio->card.gadget = c->cdev->gadget;
	/* set up ASLA audio devices */
	अगर (!audio_opts->bound) अणु
		status = gaudio_setup(&audio->card);
		अगर (status < 0)
			वापस status;
		audio_opts->bound = true;
	पूर्ण
	us = usb_gstrings_attach(cdev, uac1_strings, ARRAY_SIZE(strings_uac1));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);
	ac_पूर्णांकerface_desc.iInterface = us[STR_AC_IF].id;
	input_terminal_desc.iTerminal = us[STR_INPUT_TERMINAL].id;
	input_terminal_desc.iChannelNames = us[STR_INPUT_TERMINAL_CH_NAMES].id;
	feature_unit_desc.iFeature = us[STR_FEAT_DESC_0].id;
	output_terminal_desc.iTerminal = us[STR_OUTPUT_TERMINAL].id;
	as_पूर्णांकerface_alt_0_desc.iInterface = us[STR_AS_IF_ALT0].id;
	as_पूर्णांकerface_alt_1_desc.iInterface = us[STR_AS_IF_ALT1].id;


	f_audio_build_desc(audio);

	/* allocate instance-specअगरic पूर्णांकerface IDs, and patch descriptors */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	ac_पूर्णांकerface_desc.bInterfaceNumber = status;
	audio->ac_पूर्णांकf = status;
	audio->ac_alt = 0;

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	as_पूर्णांकerface_alt_0_desc.bInterfaceNumber = status;
	as_पूर्णांकerface_alt_1_desc.bInterfaceNumber = status;
	audio->as_पूर्णांकf = status;
	audio->as_alt = 0;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &as_out_ep_desc);
	अगर (!ep)
		जाओ fail;
	audio->out_ep = ep;
	audio->out_ep->desc = &as_out_ep_desc;

	/* copy descriptors, and track endpoपूर्णांक copies */
	status = usb_assign_descriptors(f, f_audio_desc, f_audio_desc, शून्य,
					शून्य);
	अगर (status)
		जाओ fail;
	वापस 0;

fail:
	gaudio_cleanup(&audio->card);
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक generic_set_cmd(काष्ठा usb_audio_control *con, u8 cmd, पूर्णांक value)
अणु
	con->data[cmd] = value;

	वापस 0;
पूर्ण

अटल पूर्णांक generic_get_cmd(काष्ठा usb_audio_control *con, u8 cmd)
अणु
	वापस con->data[cmd];
पूर्ण

/* Toकरो: add more control selecotor dynamically */
अटल पूर्णांक control_selector_init(काष्ठा f_audio *audio)
अणु
	INIT_LIST_HEAD(&audio->cs);
	list_add(&feature_unit.list, &audio->cs);

	INIT_LIST_HEAD(&feature_unit.control);
	list_add(&mute_control.list, &feature_unit.control);
	list_add(&volume_control.list, &feature_unit.control);

	volume_control.data[UAC__CUR] = 0xffc0;
	volume_control.data[UAC__MIN] = 0xe3a0;
	volume_control.data[UAC__MAX] = 0xfff0;
	volume_control.data[UAC__RES] = 0x0030;

	वापस 0;
पूर्ण

अटल अंतरभूत
काष्ठा f_uac1_legacy_opts *to_f_uac1_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_uac1_legacy_opts,
			    func_inst.group);
पूर्ण

अटल व्योम f_uac1_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_uac1_legacy_opts *opts = to_f_uac1_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations f_uac1_item_ops = अणु
	.release	= f_uac1_attr_release,
पूर्ण;

#घोषणा UAC1_INT_ATTRIBUTE(name)					\
अटल sमाप_प्रकार f_uac1_opts_##name##_show(काष्ठा config_item *item,	\
					 अक्षर *page)			\
अणु									\
	काष्ठा f_uac1_legacy_opts *opts = to_f_uac1_opts(item);		\
	पूर्णांक result;							\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%u\n", opts->name);			\
	mutex_unlock(&opts->lock);					\
									\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार f_uac1_opts_##name##_store(काष्ठा config_item *item,		\
					  स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा f_uac1_legacy_opts *opts = to_f_uac1_opts(item);		\
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

UAC1_INT_ATTRIBUTE(req_buf_size);
UAC1_INT_ATTRIBUTE(req_count);
UAC1_INT_ATTRIBUTE(audio_buf_size);

#घोषणा UAC1_STR_ATTRIBUTE(name)					\
अटल sमाप_प्रकार f_uac1_opts_##name##_show(काष्ठा config_item *item,	\
					 अक्षर *page)			\
अणु									\
	काष्ठा f_uac1_legacy_opts *opts = to_f_uac1_opts(item);		\
	पूर्णांक result;							\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%s\n", opts->name);			\
	mutex_unlock(&opts->lock);					\
									\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार f_uac1_opts_##name##_store(काष्ठा config_item *item,	\
					  स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा f_uac1_legacy_opts *opts = to_f_uac1_opts(item);		\
	पूर्णांक ret = -EBUSY;						\
	अक्षर *पंचांगp;							\
									\
	mutex_lock(&opts->lock);					\
	अगर (opts->refcnt)						\
		जाओ end;						\
									\
	पंचांगp = kstrndup(page, len, GFP_KERNEL);				\
	अगर (पंचांगp) अणु							\
		ret = -ENOMEM;						\
		जाओ end;						\
	पूर्ण								\
	अगर (opts->name##_alloc)						\
		kमुक्त(opts->name);					\
	opts->name##_alloc = true;					\
	opts->name = पंचांगp;						\
	ret = len;							\
									\
end:									\
	mutex_unlock(&opts->lock);					\
	वापस ret;							\
पूर्ण									\
									\
CONFIGFS_ATTR(f_uac1_opts_, name)

UAC1_STR_ATTRIBUTE(fn_play);
UAC1_STR_ATTRIBUTE(fn_cap);
UAC1_STR_ATTRIBUTE(fn_cntl);

अटल काष्ठा configfs_attribute *f_uac1_attrs[] = अणु
	&f_uac1_opts_attr_req_buf_size,
	&f_uac1_opts_attr_req_count,
	&f_uac1_opts_attr_audio_buf_size,
	&f_uac1_opts_attr_fn_play,
	&f_uac1_opts_attr_fn_cap,
	&f_uac1_opts_attr_fn_cntl,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type f_uac1_func_type = अणु
	.ct_item_ops	= &f_uac1_item_ops,
	.ct_attrs	= f_uac1_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम f_audio_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_uac1_legacy_opts *opts;

	opts = container_of(f, काष्ठा f_uac1_legacy_opts, func_inst);
	अगर (opts->fn_play_alloc)
		kमुक्त(opts->fn_play);
	अगर (opts->fn_cap_alloc)
		kमुक्त(opts->fn_cap);
	अगर (opts->fn_cntl_alloc)
		kमुक्त(opts->fn_cntl);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *f_audio_alloc_inst(व्योम)
अणु
	काष्ठा f_uac1_legacy_opts *opts;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = f_audio_मुक्त_inst;

	config_group_init_type_name(&opts->func_inst.group, "",
				    &f_uac1_func_type);

	opts->req_buf_size = UAC1_OUT_EP_MAX_PACKET_SIZE;
	opts->req_count = UAC1_REQ_COUNT;
	opts->audio_buf_size = UAC1_AUDIO_BUF_SIZE;
	opts->fn_play = खाता_PCM_PLAYBACK;
	opts->fn_cap = खाता_PCM_CAPTURE;
	opts->fn_cntl = खाता_CONTROL;
	वापस &opts->func_inst;
पूर्ण

अटल व्योम f_audio_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_audio *audio = func_to_audio(f);
	काष्ठा f_uac1_legacy_opts *opts;

	gaudio_cleanup(&audio->card);
	opts = container_of(f->fi, काष्ठा f_uac1_legacy_opts, func_inst);
	kमुक्त(audio);
	mutex_lock(&opts->lock);
	--opts->refcnt;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम f_audio_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *f_audio_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_audio *audio;
	काष्ठा f_uac1_legacy_opts *opts;

	/* allocate and initialize one new instance */
	audio = kzalloc(माप(*audio), GFP_KERNEL);
	अगर (!audio)
		वापस ERR_PTR(-ENOMEM);

	audio->card.func.name = "g_audio";

	opts = container_of(fi, काष्ठा f_uac1_legacy_opts, func_inst);
	mutex_lock(&opts->lock);
	++opts->refcnt;
	mutex_unlock(&opts->lock);
	INIT_LIST_HEAD(&audio->play_queue);
	spin_lock_init(&audio->lock);

	audio->card.func.bind = f_audio_bind;
	audio->card.func.unbind = f_audio_unbind;
	audio->card.func.set_alt = f_audio_set_alt;
	audio->card.func.get_alt = f_audio_get_alt;
	audio->card.func.setup = f_audio_setup;
	audio->card.func.disable = f_audio_disable;
	audio->card.func.मुक्त_func = f_audio_मुक्त;

	control_selector_init(audio);

	INIT_WORK(&audio->playback_work, f_audio_playback_work);

	वापस &audio->card.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(uac1_legacy, f_audio_alloc_inst, f_audio_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bryan Wu");

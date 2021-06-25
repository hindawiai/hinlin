<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * audio.c -- Audio gadget driver
 *
 * Copyright (C) 2008 Bryan Wu <cooloney@kernel.org>
 * Copyright (C) 2008 Analog Devices, Inc
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/composite.h>

#घोषणा DRIVER_DESC		"Linux USB Audio Gadget"
#घोषणा DRIVER_VERSION		"Feb 2, 2012"

USB_GADGET_COMPOSITE_OPTIONS();

#अगर_अघोषित CONFIG_GADGET_UAC1
#समावेश "u_uac2.h"

/* Playback(USB-IN) Default Stereo - Fl/Fr */
अटल पूर्णांक p_chmask = UAC2_DEF_PCHMASK;
module_param(p_chmask, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(p_chmask, "Playback Channel Mask");

/* Playback Default 48 KHz */
अटल पूर्णांक p_srate = UAC2_DEF_PSRATE;
module_param(p_srate, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(p_srate, "Playback Sampling Rate");

/* Playback Default 16bits/sample */
अटल पूर्णांक p_ssize = UAC2_DEF_PSSIZE;
module_param(p_ssize, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(p_ssize, "Playback Sample Size(bytes)");

/* Capture(USB-OUT) Default Stereo - Fl/Fr */
अटल पूर्णांक c_chmask = UAC2_DEF_CCHMASK;
module_param(c_chmask, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(c_chmask, "Capture Channel Mask");

/* Capture Default 64 KHz */
अटल पूर्णांक c_srate = UAC2_DEF_CSRATE;
module_param(c_srate, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(c_srate, "Capture Sampling Rate");

/* Capture Default 16bits/sample */
अटल पूर्णांक c_ssize = UAC2_DEF_CSSIZE;
module_param(c_ssize, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(c_ssize, "Capture Sample Size(bytes)");
#अन्यथा
#अगर_अघोषित CONFIG_GADGET_UAC1_LEGACY
#समावेश "u_uac1.h"

/* Playback(USB-IN) Default Stereo - Fl/Fr */
अटल पूर्णांक p_chmask = UAC1_DEF_PCHMASK;
module_param(p_chmask, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(p_chmask, "Playback Channel Mask");

/* Playback Default 48 KHz */
अटल पूर्णांक p_srate = UAC1_DEF_PSRATE;
module_param(p_srate, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(p_srate, "Playback Sampling Rate");

/* Playback Default 16bits/sample */
अटल पूर्णांक p_ssize = UAC1_DEF_PSSIZE;
module_param(p_ssize, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(p_ssize, "Playback Sample Size(bytes)");

/* Capture(USB-OUT) Default Stereo - Fl/Fr */
अटल पूर्णांक c_chmask = UAC1_DEF_CCHMASK;
module_param(c_chmask, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(c_chmask, "Capture Channel Mask");

/* Capture Default 48 KHz */
अटल पूर्णांक c_srate = UAC1_DEF_CSRATE;
module_param(c_srate, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(c_srate, "Capture Sampling Rate");

/* Capture Default 16bits/sample */
अटल पूर्णांक c_ssize = UAC1_DEF_CSSIZE;
module_param(c_ssize, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(c_ssize, "Capture Sample Size(bytes)");
#अन्यथा /* CONFIG_GADGET_UAC1_LEGACY */
#समावेश "u_uac1_legacy.h"

अटल अक्षर *fn_play = खाता_PCM_PLAYBACK;
module_param(fn_play, अक्षरp, S_IRUGO);
MODULE_PARM_DESC(fn_play, "Playback PCM device file name");

अटल अक्षर *fn_cap = खाता_PCM_CAPTURE;
module_param(fn_cap, अक्षरp, S_IRUGO);
MODULE_PARM_DESC(fn_cap, "Capture PCM device file name");

अटल अक्षर *fn_cntl = खाता_CONTROL;
module_param(fn_cntl, अक्षरp, S_IRUGO);
MODULE_PARM_DESC(fn_cntl, "Control device file name");

अटल पूर्णांक req_buf_size = UAC1_OUT_EP_MAX_PACKET_SIZE;
module_param(req_buf_size, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(req_buf_size, "ISO OUT endpoint request buffer size");

अटल पूर्णांक req_count = UAC1_REQ_COUNT;
module_param(req_count, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(req_count, "ISO OUT endpoint request count");

अटल पूर्णांक audio_buf_size = UAC1_AUDIO_BUF_SIZE;
module_param(audio_buf_size, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(audio_buf_size, "Audio buffer size");
#पूर्ण_अगर /* CONFIG_GADGET_UAC1_LEGACY */
#पूर्ण_अगर

/* string IDs are asचिन्हित dynamically */

अटल काष्ठा usb_string strings_dev[] = अणु
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = DRIVER_DESC,
	[USB_GADGET_SERIAL_IDX].s = "",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings stringtab_dev = अणु
	.language = 0x0409,	/* en-us */
	.strings = strings_dev,
पूर्ण;

अटल काष्ठा usb_gadget_strings *audio_strings[] = अणु
	&stringtab_dev,
	शून्य,
पूर्ण;

#अगर_अघोषित CONFIG_GADGET_UAC1
अटल काष्ठा usb_function_instance *fi_uac2;
अटल काष्ठा usb_function *f_uac2;
#अन्यथा
अटल काष्ठा usb_function_instance *fi_uac1;
अटल काष्ठा usb_function *f_uac1;
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/* DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */

/* Thanks to Linux Foundation क्रम करोnating this product ID. */
#घोषणा AUDIO_VENDOR_NUM		0x1d6b	/* Linux Foundation */
#घोषणा AUDIO_PRODUCT_NUM		0x0101	/* Linux-USB Audio Gadget */

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength =		माप device_desc,
	.bDescriptorType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

#अगर_घोषित CONFIG_GADGET_UAC1_LEGACY
	.bDeviceClass =		USB_CLASS_PER_INTERFACE,
	.bDeviceSubClass =	0,
	.bDeviceProtocol =	0,
#अन्यथा
	.bDeviceClass =		USB_CLASS_MISC,
	.bDeviceSubClass =	0x02,
	.bDeviceProtocol =	0x01,
#पूर्ण_अगर
	/* .bMaxPacketSize0 = f(hardware) */

	/* Venकरोr and product id शेषs change according to what configs
	 * we support.  (As करोes bNumConfigurations.)  These values can
	 * also be overridden by module parameters.
	 */
	.idVenकरोr =		cpu_to_le16(AUDIO_VENDOR_NUM),
	.idProduct =		cpu_to_le16(AUDIO_PRODUCT_NUM),
	/* .bcdDevice = f(hardware) */
	/* .iManufacturer = DYNAMIC */
	/* .iProduct = DYNAMIC */
	/* NO SERIAL NUMBER */
	.bNumConfigurations =	1,
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header *otg_desc[2];

/*-------------------------------------------------------------------------*/

अटल पूर्णांक audio_करो_config(काष्ठा usb_configuration *c)
अणु
	पूर्णांक status;

	/* FIXME alloc iConfiguration string, set it in c->strings */

	अगर (gadget_is_otg(c->cdev->gadget)) अणु
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	पूर्ण

#अगर_घोषित CONFIG_GADGET_UAC1
	f_uac1 = usb_get_function(fi_uac1);
	अगर (IS_ERR(f_uac1)) अणु
		status = PTR_ERR(f_uac1);
		वापस status;
	पूर्ण

	status = usb_add_function(c, f_uac1);
	अगर (status < 0) अणु
		usb_put_function(f_uac1);
		वापस status;
	पूर्ण
#अन्यथा
	f_uac2 = usb_get_function(fi_uac2);
	अगर (IS_ERR(f_uac2)) अणु
		status = PTR_ERR(f_uac2);
		वापस status;
	पूर्ण

	status = usb_add_function(c, f_uac2);
	अगर (status < 0) अणु
		usb_put_function(f_uac2);
		वापस status;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल काष्ठा usb_configuration audio_config_driver = अणु
	.label			= DRIVER_DESC,
	.bConfigurationValue	= 1,
	/* .iConfiguration = DYNAMIC */
	.bmAttributes		= USB_CONFIG_ATT_SELFPOWER,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक audio_bind(काष्ठा usb_composite_dev *cdev)
अणु
#अगर_अघोषित CONFIG_GADGET_UAC1
	काष्ठा f_uac2_opts	*uac2_opts;
#अन्यथा
#अगर_अघोषित CONFIG_GADGET_UAC1_LEGACY
	काष्ठा f_uac1_opts	*uac1_opts;
#अन्यथा
	काष्ठा f_uac1_legacy_opts	*uac1_opts;
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्णांक			status;

#अगर_अघोषित CONFIG_GADGET_UAC1
	fi_uac2 = usb_get_function_instance("uac2");
	अगर (IS_ERR(fi_uac2))
		वापस PTR_ERR(fi_uac2);
#अन्यथा
#अगर_अघोषित CONFIG_GADGET_UAC1_LEGACY
	fi_uac1 = usb_get_function_instance("uac1");
#अन्यथा
	fi_uac1 = usb_get_function_instance("uac1_legacy");
#पूर्ण_अगर
	अगर (IS_ERR(fi_uac1))
		वापस PTR_ERR(fi_uac1);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_GADGET_UAC1
	uac2_opts = container_of(fi_uac2, काष्ठा f_uac2_opts, func_inst);
	uac2_opts->p_chmask = p_chmask;
	uac2_opts->p_srate = p_srate;
	uac2_opts->p_ssize = p_ssize;
	uac2_opts->c_chmask = c_chmask;
	uac2_opts->c_srate = c_srate;
	uac2_opts->c_ssize = c_ssize;
	uac2_opts->req_number = UAC2_DEF_REQ_NUM;
#अन्यथा
#अगर_अघोषित CONFIG_GADGET_UAC1_LEGACY
	uac1_opts = container_of(fi_uac1, काष्ठा f_uac1_opts, func_inst);
	uac1_opts->p_chmask = p_chmask;
	uac1_opts->p_srate = p_srate;
	uac1_opts->p_ssize = p_ssize;
	uac1_opts->c_chmask = c_chmask;
	uac1_opts->c_srate = c_srate;
	uac1_opts->c_ssize = c_ssize;
	uac1_opts->req_number = UAC1_DEF_REQ_NUM;
#अन्यथा /* CONFIG_GADGET_UAC1_LEGACY */
	uac1_opts = container_of(fi_uac1, काष्ठा f_uac1_legacy_opts, func_inst);
	uac1_opts->fn_play = fn_play;
	uac1_opts->fn_cap = fn_cap;
	uac1_opts->fn_cntl = fn_cntl;
	uac1_opts->req_buf_size = req_buf_size;
	uac1_opts->req_count = req_count;
	uac1_opts->audio_buf_size = audio_buf_size;
#पूर्ण_अगर /* CONFIG_GADGET_UAC1_LEGACY */
#पूर्ण_अगर

	status = usb_string_ids_tab(cdev, strings_dev);
	अगर (status < 0)
		जाओ fail;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;

	अगर (gadget_is_otg(cdev->gadget) && !otg_desc[0]) अणु
		काष्ठा usb_descriptor_header *usb_desc;

		usb_desc = usb_otg_descriptor_alloc(cdev->gadget);
		अगर (!usb_desc) अणु
			status = -ENOMEM;
			जाओ fail;
		पूर्ण
		usb_otg_descriptor_init(cdev->gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = शून्य;
	पूर्ण

	status = usb_add_config(cdev, &audio_config_driver, audio_करो_config);
	अगर (status < 0)
		जाओ fail_otg_desc;
	usb_composite_overग_लिखो_options(cdev, &coverग_लिखो);

	INFO(cdev, "%s, version: %s\n", DRIVER_DESC, DRIVER_VERSION);
	वापस 0;

fail_otg_desc:
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;
fail:
#अगर_अघोषित CONFIG_GADGET_UAC1
	usb_put_function_instance(fi_uac2);
#अन्यथा
	usb_put_function_instance(fi_uac1);
#पूर्ण_अगर
	वापस status;
पूर्ण

अटल पूर्णांक audio_unbind(काष्ठा usb_composite_dev *cdev)
अणु
#अगर_घोषित CONFIG_GADGET_UAC1
	अगर (!IS_ERR_OR_शून्य(f_uac1))
		usb_put_function(f_uac1);
	अगर (!IS_ERR_OR_शून्य(fi_uac1))
		usb_put_function_instance(fi_uac1);
#अन्यथा
	अगर (!IS_ERR_OR_शून्य(f_uac2))
		usb_put_function(f_uac2);
	अगर (!IS_ERR_OR_शून्य(fi_uac2))
		usb_put_function_instance(fi_uac2);
#पूर्ण_अगर
	kमुक्त(otg_desc[0]);
	otg_desc[0] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा usb_composite_driver audio_driver = अणु
	.name		= "g_audio",
	.dev		= &device_desc,
	.strings	= audio_strings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= audio_bind,
	.unbind		= audio_unbind,
पूर्ण;

module_usb_composite_driver(audio_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Bryan Wu <cooloney@kernel.org>");
MODULE_LICENSE("GPL");


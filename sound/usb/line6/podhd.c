<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Pod HD
 *
 * Copyright (C) 2011 Stefan Hajnoczi <stefanha@gmail.com>
 * Copyright (C) 2015 Andrej Krutak <dev@andree.sk>
 * Copyright (C) 2017 Hans P. Moller <hmoller@uc.cl>
 */

#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>

#समावेश "driver.h"
#समावेश "pcm.h"

#घोषणा PODHD_STARTUP_DELAY 500

क्रमागत अणु
	LINE6_PODHD300,
	LINE6_PODHD400,
	LINE6_PODHD500,
	LINE6_PODX3,
	LINE6_PODX3LIVE,
	LINE6_PODHD500X,
	LINE6_PODHDDESKTOP
पूर्ण;

काष्ठा usb_line6_podhd अणु
	/* Generic Line 6 USB data */
	काष्ठा usb_line6 line6;

	/* Serial number of device */
	u32 serial_number;

	/* Firmware version */
	पूर्णांक firmware_version;

	/* Monitor level */
	पूर्णांक monitor_level;
पूर्ण;

#घोषणा line6_to_podhd(x)	container_of(x, काष्ठा usb_line6_podhd, line6)

अटल स्थिर काष्ठा snd_ratden podhd_ratden = अणु
	.num_min = 48000,
	.num_max = 48000,
	.num_step = 1,
	.den = 1,
पूर्ण;

अटल काष्ठा line6_pcm_properties podhd_pcm_properties = अणु
	.playback_hw = अणु
				  .info = (SNDRV_PCM_INFO_MMAP |
					   SNDRV_PCM_INFO_INTERLEAVED |
					   SNDRV_PCM_INFO_BLOCK_TRANSFER |
					   SNDRV_PCM_INFO_MMAP_VALID |
					   SNDRV_PCM_INFO_PAUSE |
					   SNDRV_PCM_INFO_SYNC_START),
				  .क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
				  .rates = SNDRV_PCM_RATE_48000,
				  .rate_min = 48000,
				  .rate_max = 48000,
				  .channels_min = 2,
				  .channels_max = 2,
				  .buffer_bytes_max = 60000,
				  .period_bytes_min = 64,
				  .period_bytes_max = 8192,
				  .periods_min = 1,
				  .periods_max = 1024पूर्ण,
	.capture_hw = अणु
				 .info = (SNDRV_PCM_INFO_MMAP |
					  SNDRV_PCM_INFO_INTERLEAVED |
					  SNDRV_PCM_INFO_BLOCK_TRANSFER |
					  SNDRV_PCM_INFO_MMAP_VALID |
					  SNDRV_PCM_INFO_SYNC_START),
				 .क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
				 .rates = SNDRV_PCM_RATE_48000,
				 .rate_min = 48000,
				 .rate_max = 48000,
				 .channels_min = 2,
				 .channels_max = 2,
				 .buffer_bytes_max = 60000,
				 .period_bytes_min = 64,
				 .period_bytes_max = 8192,
				 .periods_min = 1,
				 .periods_max = 1024पूर्ण,
	.rates = अणु
			    .nrats = 1,
			    .rats = &podhd_ratdenपूर्ण,
	.bytes_per_channel = 3 /* SNDRV_PCM_FMTBIT_S24_3LE */
पूर्ण;

अटल काष्ठा line6_pcm_properties podx3_pcm_properties = अणु
	.playback_hw = अणु
				  .info = (SNDRV_PCM_INFO_MMAP |
					   SNDRV_PCM_INFO_INTERLEAVED |
					   SNDRV_PCM_INFO_BLOCK_TRANSFER |
					   SNDRV_PCM_INFO_MMAP_VALID |
					   SNDRV_PCM_INFO_PAUSE |
					   SNDRV_PCM_INFO_SYNC_START),
				  .क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
				  .rates = SNDRV_PCM_RATE_48000,
				  .rate_min = 48000,
				  .rate_max = 48000,
				  .channels_min = 2,
				  .channels_max = 2,
				  .buffer_bytes_max = 60000,
				  .period_bytes_min = 64,
				  .period_bytes_max = 8192,
				  .periods_min = 1,
				  .periods_max = 1024पूर्ण,
	.capture_hw = अणु
				 .info = (SNDRV_PCM_INFO_MMAP |
					  SNDRV_PCM_INFO_INTERLEAVED |
					  SNDRV_PCM_INFO_BLOCK_TRANSFER |
					  SNDRV_PCM_INFO_MMAP_VALID |
					  SNDRV_PCM_INFO_SYNC_START),
				 .क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
				 .rates = SNDRV_PCM_RATE_48000,
				 .rate_min = 48000,
				 .rate_max = 48000,
				 /* 1+2: Main संकेत (out), 3+4: Tone 1,
				  * 5+6: Tone 2, 7+8: raw
				  */
				 .channels_min = 8,
				 .channels_max = 8,
				 .buffer_bytes_max = 60000,
				 .period_bytes_min = 64,
				 .period_bytes_max = 8192,
				 .periods_min = 1,
				 .periods_max = 1024पूर्ण,
	.rates = अणु
			    .nrats = 1,
			    .rats = &podhd_ratdenपूर्ण,
	.bytes_per_channel = 3 /* SNDRV_PCM_FMTBIT_S24_3LE */
पूर्ण;
अटल काष्ठा usb_driver podhd_driver;

अटल sमाप_प्रकार serial_number_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_card *card = dev_to_snd_card(dev);
	काष्ठा usb_line6_podhd *pod = card->निजी_data;

	वापस प्र_लिखो(buf, "%u\n", pod->serial_number);
पूर्ण

अटल sमाप_प्रकार firmware_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_card *card = dev_to_snd_card(dev);
	काष्ठा usb_line6_podhd *pod = card->निजी_data;

	वापस प्र_लिखो(buf, "%06x\n", pod->firmware_version);
पूर्ण

अटल DEVICE_ATTR_RO(firmware_version);
अटल DEVICE_ATTR_RO(serial_number);

अटल काष्ठा attribute *podhd_dev_attrs[] = अणु
	&dev_attr_firmware_version.attr,
	&dev_attr_serial_number.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group podhd_dev_attr_group = अणु
	.name = "podhd",
	.attrs = podhd_dev_attrs,
पूर्ण;

/*
 * POD X3 startup procedure.
 *
 * May be compatible with other POD HD's, since it's also similar to the
 * previous POD setup. In any हाल, it करोesn't seem to be required क्रम the
 * audio nor bulk पूर्णांकerfaces to work.
 */

अटल पूर्णांक podhd_dev_start(काष्ठा usb_line6_podhd *pod)
अणु
	पूर्णांक ret;
	u8 init_bytes[8];
	पूर्णांक i;
	काष्ठा usb_device *usbdev = pod->line6.usbdev;

	ret = usb_control_msg_send(usbdev, 0,
					0x67, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
					0x11, 0,
					शून्य, 0, LINE6_TIMEOUT * HZ, GFP_KERNEL);
	अगर (ret) अणु
		dev_err(pod->line6.अगरcdev, "read request failed (error %d)\n", ret);
		जाओ निकास;
	पूर्ण

	/* NOTE: looks like some kind of ping message */
	ret = usb_control_msg_recv(usbdev, 0, 0x67,
					USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
					0x11, 0x0,
					init_bytes, 3, LINE6_TIMEOUT * HZ, GFP_KERNEL);
	अगर (ret) अणु
		dev_err(pod->line6.अगरcdev,
			"receive length failed (error %d)\n", ret);
		जाओ निकास;
	पूर्ण

	pod->firmware_version =
		(init_bytes[0] << 16) | (init_bytes[1] << 8) | (init_bytes[2] << 0);

	क्रम (i = 0; i <= 16; i++) अणु
		ret = line6_पढ़ो_data(&pod->line6, 0xf000 + 0x08 * i, init_bytes, 8);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	ret = usb_control_msg_send(usbdev, 0,
					USB_REQ_SET_FEATURE,
					USB_TYPE_STANDARD | USB_RECIP_DEVICE | USB_सूची_OUT,
					1, 0,
					शून्य, 0, LINE6_TIMEOUT * HZ, GFP_KERNEL);
निकास:
	वापस ret;
पूर्ण

अटल व्योम podhd_startup(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_line6_podhd *pod = line6_to_podhd(line6);

	podhd_dev_start(pod);
	line6_पढ़ो_serial_number(&pod->line6, &pod->serial_number);
	अगर (snd_card_रेजिस्टर(line6->card))
		dev_err(line6->अगरcdev, "Failed to register POD HD card.\n");
पूर्ण

अटल व्योम podhd_disconnect(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_line6_podhd *pod = line6_to_podhd(line6);

	अगर (pod->line6.properties->capabilities & LINE6_CAP_CONTROL_INFO) अणु
		काष्ठा usb_पूर्णांकerface *पूर्णांकf;

		पूर्णांकf = usb_अगरnum_to_अगर(line6->usbdev,
					pod->line6.properties->ctrl_अगर);
		अगर (पूर्णांकf)
			usb_driver_release_पूर्णांकerface(&podhd_driver, पूर्णांकf);
	पूर्ण
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक भग्न_zero_to_one_lookup[] = अणु
0x00000000, 0x3c23d70a, 0x3ca3d70a, 0x3cf5c28f, 0x3d23d70a, 0x3d4ccccd,
0x3d75c28f, 0x3d8f5c29, 0x3da3d70a, 0x3db851ec, 0x3dcccccd, 0x3de147ae,
0x3df5c28f, 0x3e051eb8, 0x3e0f5c29, 0x3e19999a, 0x3e23d70a, 0x3e2e147b,
0x3e3851ec, 0x3e428f5c, 0x3e4ccccd, 0x3e570a3d, 0x3e6147ae, 0x3e6b851f,
0x3e75c28f, 0x3e800000, 0x3e851eb8, 0x3e8a3d71, 0x3e8f5c29, 0x3e947ae1,
0x3e99999a, 0x3e9eb852, 0x3ea3d70a, 0x3ea8f5c3, 0x3eae147b, 0x3eb33333,
0x3eb851ec, 0x3ebd70a4, 0x3ec28f5c, 0x3ec7ae14, 0x3ecccccd, 0x3ed1eb85,
0x3ed70a3d, 0x3edc28f6, 0x3ee147ae, 0x3ee66666, 0x3eeb851f, 0x3ef0a3d7,
0x3ef5c28f, 0x3efae148, 0x3f000000, 0x3f028f5c, 0x3f051eb8, 0x3f07ae14,
0x3f0a3d71, 0x3f0ccccd, 0x3f0f5c29, 0x3f11eb85, 0x3f147ae1, 0x3f170a3d,
0x3f19999a, 0x3f1c28f6, 0x3f1eb852, 0x3f2147ae, 0x3f23d70a, 0x3f266666,
0x3f28f5c3, 0x3f2b851f, 0x3f2e147b, 0x3f30a3d7, 0x3f333333, 0x3f35c28f,
0x3f3851ec, 0x3f3ae148, 0x3f3d70a4, 0x3f400000, 0x3f428f5c, 0x3f451eb8,
0x3f47ae14, 0x3f4a3d71, 0x3f4ccccd, 0x3f4f5c29, 0x3f51eb85, 0x3f547ae1,
0x3f570a3d, 0x3f59999a, 0x3f5c28f6, 0x3f5eb852, 0x3f6147ae, 0x3f63d70a,
0x3f666666, 0x3f68f5c3, 0x3f6b851f, 0x3f6e147b, 0x3f70a3d7, 0x3f733333,
0x3f75c28f, 0x3f7851ec, 0x3f7ae148, 0x3f7d70a4, 0x3f800000
पूर्ण;

अटल व्योम podhd_set_monitor_level(काष्ठा usb_line6_podhd *podhd, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक fl;
	अटल स्थिर अचिन्हित अक्षर msg[16] = अणु
		/* Chunk is 0xc bytes (without first word) */
		0x0c, 0x00,
		/* First chunk in the message */
		0x01, 0x00,
		/* Message size is 2 4-byte words */
		0x02, 0x00,
		/* Unknown */
		0x04, 0x41,
		/* Unknown */
		0x04, 0x00, 0x13, 0x00,
		/* Volume, LE भग्न32, 0.0 - 1.0 */
		0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अचिन्हित अक्षर *buf;

	buf = kmemdup(msg, माप(msg), GFP_KERNEL);
	अगर (!buf)
		वापस;

	अगर (value < 0)
		value = 0;

	अगर (value >= ARRAY_SIZE(भग्न_zero_to_one_lookup))
		value = ARRAY_SIZE(भग्न_zero_to_one_lookup) - 1;

	fl = भग्न_zero_to_one_lookup[value];

	buf[12] = (fl >> 0) & 0xff;
	buf[13] = (fl >> 8) & 0xff;
	buf[14] = (fl >> 16) & 0xff;
	buf[15] = (fl >> 24) & 0xff;

	line6_send_raw_message(&podhd->line6, buf, माप(msg));
	kमुक्त(buf);

	podhd->monitor_level = value;
पूर्ण

/* control info callback */
अटल पूर्णांक snd_podhd_control_monitor_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 100;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण

/* control get callback */
अटल पूर्णांक snd_podhd_control_monitor_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_line6_podhd *podhd = line6_to_podhd(line6pcm->line6);

	ucontrol->value.पूर्णांकeger.value[0] = podhd->monitor_level;
	वापस 0;
पूर्ण

/* control put callback */
अटल पूर्णांक snd_podhd_control_monitor_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_line6_podhd *podhd = line6_to_podhd(line6pcm->line6);

	अगर (ucontrol->value.पूर्णांकeger.value[0] == podhd->monitor_level)
		वापस 0;

	podhd_set_monitor_level(podhd, ucontrol->value.पूर्णांकeger.value[0]);
	वापस 1;
पूर्ण

/* control definition */
अटल स्थिर काष्ठा snd_kcontrol_new podhd_control_monitor = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Monitor Playback Volume",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_podhd_control_monitor_info,
	.get = snd_podhd_control_monitor_get,
	.put = snd_podhd_control_monitor_put
पूर्ण;

/*
	Try to init POD HD device.
*/
अटल पूर्णांक podhd_init(काष्ठा usb_line6 *line6,
		      स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा usb_line6_podhd *pod = line6_to_podhd(line6);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	line6->disconnect = podhd_disconnect;
	line6->startup = podhd_startup;

	अगर (pod->line6.properties->capabilities & LINE6_CAP_CONTROL) अणु
		/* claim the data पूर्णांकerface */
		पूर्णांकf = usb_अगरnum_to_अगर(line6->usbdev,
					pod->line6.properties->ctrl_अगर);
		अगर (!पूर्णांकf) अणु
			dev_err(pod->line6.अगरcdev, "interface %d not found\n",
				pod->line6.properties->ctrl_अगर);
			वापस -ENODEV;
		पूर्ण

		err = usb_driver_claim_पूर्णांकerface(&podhd_driver, पूर्णांकf, शून्य);
		अगर (err != 0) अणु
			dev_err(pod->line6.अगरcdev, "can't claim interface %d, error %d\n",
				pod->line6.properties->ctrl_अगर, err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (pod->line6.properties->capabilities & LINE6_CAP_CONTROL_INFO) अणु
		/* create sysfs entries: */
		err = snd_card_add_dev_attr(line6->card, &podhd_dev_attr_group);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (pod->line6.properties->capabilities & LINE6_CAP_PCM) अणु
		/* initialize PCM subप्रणाली: */
		err = line6_init_pcm(line6,
			(id->driver_info == LINE6_PODX3 ||
			id->driver_info == LINE6_PODX3LIVE) ? &podx3_pcm_properties :
			&podhd_pcm_properties);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (pod->line6.properties->capabilities & LINE6_CAP_HWMON_CTL) अणु
		podhd_set_monitor_level(pod, 100);
		err = snd_ctl_add(line6->card,
				  snd_ctl_new1(&podhd_control_monitor,
					       line6->line6pcm));
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!(pod->line6.properties->capabilities & LINE6_CAP_CONTROL_INFO)) अणु
		/* रेजिस्टर USB audio प्रणाली directly */
		वापस snd_card_रेजिस्टर(line6->card);
	पूर्ण

	/* init device and delay रेजिस्टरing */
	schedule_delayed_work(&line6->startup_work,
			      msecs_to_jअगरfies(PODHD_STARTUP_DELAY));
	वापस 0;
पूर्ण

#घोषणा LINE6_DEVICE(prod) USB_DEVICE(0x0e41, prod)
#घोषणा LINE6_IF_NUM(prod, n) USB_DEVICE_INTERFACE_NUMBER(0x0e41, prod, n)

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id podhd_id_table[] = अणु
	/* TODO: no need to alloc data पूर्णांकerfaces when only audio is used */
	अणु LINE6_DEVICE(0x5057),    .driver_info = LINE6_PODHD300 पूर्ण,
	अणु LINE6_DEVICE(0x5058),    .driver_info = LINE6_PODHD400 पूर्ण,
	अणु LINE6_IF_NUM(0x414D, 0), .driver_info = LINE6_PODHD500 पूर्ण,
	अणु LINE6_IF_NUM(0x414A, 0), .driver_info = LINE6_PODX3 पूर्ण,
	अणु LINE6_IF_NUM(0x414B, 0), .driver_info = LINE6_PODX3LIVE पूर्ण,
	अणु LINE6_IF_NUM(0x4159, 0), .driver_info = LINE6_PODHD500X पूर्ण,
	अणु LINE6_IF_NUM(0x4156, 0), .driver_info = LINE6_PODHDDESKTOP पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, podhd_id_table);

अटल स्थिर काष्ठा line6_properties podhd_properties_table[] = अणु
	[LINE6_PODHD300] = अणु
		.id = "PODHD300",
		.name = "POD HD300",
		.capabilities	= LINE6_CAP_PCM
				| LINE6_CAP_HWMON,
		.altsetting = 5,
		.ep_ctrl_r = 0x84,
		.ep_ctrl_w = 0x03,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_PODHD400] = अणु
		.id = "PODHD400",
		.name = "POD HD400",
		.capabilities	= LINE6_CAP_PCM
				| LINE6_CAP_HWMON,
		.altsetting = 5,
		.ep_ctrl_r = 0x84,
		.ep_ctrl_w = 0x03,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_PODHD500] = अणु
		.id = "PODHD500",
		.name = "POD HD500",
		.capabilities	= LINE6_CAP_PCM | LINE6_CAP_CONTROL
				| LINE6_CAP_HWMON | LINE6_CAP_HWMON_CTL,
		.altsetting = 1,
		.ctrl_अगर = 1,
		.ep_ctrl_r = 0x81,
		.ep_ctrl_w = 0x01,
		.ep_audio_r = 0x86,
		.ep_audio_w = 0x02,
	पूर्ण,
	[LINE6_PODX3] = अणु
		.id = "PODX3",
		.name = "POD X3",
		.capabilities	= LINE6_CAP_CONTROL | LINE6_CAP_CONTROL_INFO
				| LINE6_CAP_PCM | LINE6_CAP_HWMON | LINE6_CAP_IN_NEEDS_OUT,
		.altsetting = 1,
		.ep_ctrl_r = 0x81,
		.ep_ctrl_w = 0x01,
		.ctrl_अगर = 1,
		.ep_audio_r = 0x86,
		.ep_audio_w = 0x02,
	पूर्ण,
	[LINE6_PODX3LIVE] = अणु
		.id = "PODX3LIVE",
		.name = "POD X3 LIVE",
		.capabilities	= LINE6_CAP_CONTROL | LINE6_CAP_CONTROL_INFO
				| LINE6_CAP_PCM | LINE6_CAP_HWMON | LINE6_CAP_IN_NEEDS_OUT,
		.altsetting = 1,
		.ep_ctrl_r = 0x81,
		.ep_ctrl_w = 0x01,
		.ctrl_अगर = 1,
		.ep_audio_r = 0x86,
		.ep_audio_w = 0x02,
	पूर्ण,
	[LINE6_PODHD500X] = अणु
		.id = "PODHD500X",
		.name = "POD HD500X",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_PCM | LINE6_CAP_HWMON,
		.altsetting = 1,
		.ep_ctrl_r = 0x81,
		.ep_ctrl_w = 0x01,
		.ctrl_अगर = 1,
		.ep_audio_r = 0x86,
		.ep_audio_w = 0x02,
	पूर्ण,
	[LINE6_PODHDDESKTOP] = अणु
		.id = "PODHDDESKTOP",
		.name = "POD HDDESKTOP",
		.capabilities    = LINE6_CAP_CONTROL
			| LINE6_CAP_PCM | LINE6_CAP_HWMON,
		.altsetting = 1,
		.ep_ctrl_r = 0x81,
		.ep_ctrl_w = 0x01,
		.ctrl_अगर = 1,
		.ep_audio_r = 0x86,
		.ep_audio_w = 0x02,
	पूर्ण,
पूर्ण;

/*
	Probe USB device.
*/
अटल पूर्णांक podhd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	वापस line6_probe(पूर्णांकerface, id, "Line6-PODHD",
			   &podhd_properties_table[id->driver_info],
			   podhd_init, माप(काष्ठा usb_line6_podhd));
पूर्ण

अटल काष्ठा usb_driver podhd_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = podhd_probe,
	.disconnect = line6_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = line6_suspend,
	.resume = line6_resume,
	.reset_resume = line6_resume,
#पूर्ण_अगर
	.id_table = podhd_id_table,
पूर्ण;

module_usb_driver(podhd_driver);

MODULE_DESCRIPTION("Line 6 PODHD USB driver");
MODULE_LICENSE("GPL");

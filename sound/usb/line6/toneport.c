<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 *                         Emil Myhrman (emil.myhrman@gmail.com)
 */

#समावेश <linux/रुको.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/leds.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>

#समावेश "capture.h"
#समावेश "driver.h"
#समावेश "playback.h"

क्रमागत line6_device_type अणु
	LINE6_GUITARPORT,
	LINE6_PODSTUDIO_GX,
	LINE6_PODSTUDIO_UX1,
	LINE6_PODSTUDIO_UX2,
	LINE6_TONEPORT_GX,
	LINE6_TONEPORT_UX1,
	LINE6_TONEPORT_UX2,
पूर्ण;

काष्ठा usb_line6_toneport;

काष्ठा toneport_led अणु
	काष्ठा led_classdev dev;
	अक्षर name[64];
	काष्ठा usb_line6_toneport *toneport;
	bool रेजिस्टरed;
पूर्ण;

काष्ठा usb_line6_toneport अणु
	/* Generic Line 6 USB data */
	काष्ठा usb_line6 line6;

	/* Source selector */
	पूर्णांक source;

	/* Serial number of device */
	u32 serial_number;

	/* Firmware version (x 100) */
	u8 firmware_version;

	/* Device type */
	क्रमागत line6_device_type type;

	/* LED instances */
	काष्ठा toneport_led leds[2];
पूर्ण;

#घोषणा line6_to_toneport(x) container_of(x, काष्ठा usb_line6_toneport, line6)

अटल पूर्णांक toneport_send_cmd(काष्ठा usb_device *usbdev, पूर्णांक cmd1, पूर्णांक cmd2);

#घोषणा TONEPORT_PCM_DELAY 1

अटल स्थिर काष्ठा snd_ratden toneport_ratden = अणु
	.num_min = 44100,
	.num_max = 44100,
	.num_step = 1,
	.den = 1
पूर्ण;

अटल काष्ठा line6_pcm_properties toneport_pcm_properties = अणु
	.playback_hw = अणु
				  .info = (SNDRV_PCM_INFO_MMAP |
					   SNDRV_PCM_INFO_INTERLEAVED |
					   SNDRV_PCM_INFO_BLOCK_TRANSFER |
					   SNDRV_PCM_INFO_MMAP_VALID |
					   SNDRV_PCM_INFO_PAUSE |
					   SNDRV_PCM_INFO_SYNC_START),
				  .क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
				  .rates = SNDRV_PCM_RATE_KNOT,
				  .rate_min = 44100,
				  .rate_max = 44100,
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
				 .क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
				 .rates = SNDRV_PCM_RATE_KNOT,
				 .rate_min = 44100,
				 .rate_max = 44100,
				 .channels_min = 2,
				 .channels_max = 2,
				 .buffer_bytes_max = 60000,
				 .period_bytes_min = 64,
				 .period_bytes_max = 8192,
				 .periods_min = 1,
				 .periods_max = 1024पूर्ण,
	.rates = अणु
			    .nrats = 1,
			    .rats = &toneport_ratdenपूर्ण,
	.bytes_per_channel = 2
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक code;
पूर्ण toneport_source_info[] = अणु
	अणु"Microphone", 0x0a01पूर्ण,
	अणु"Line", 0x0801पूर्ण,
	अणु"Instrument", 0x0b01पूर्ण,
	अणु"Inst & Mic", 0x0901पूर्ण
पूर्ण;

अटल पूर्णांक toneport_send_cmd(काष्ठा usb_device *usbdev, पूर्णांक cmd1, पूर्णांक cmd2)
अणु
	पूर्णांक ret;

	ret = usb_control_msg_send(usbdev, 0, 0x67,
				   USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
				   cmd1, cmd2, शून्य, 0, LINE6_TIMEOUT * HZ,
				   GFP_KERNEL);

	अगर (ret) अणु
		dev_err(&usbdev->dev, "send failed (error %d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* monitor info callback */
अटल पूर्णांक snd_toneport_monitor_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 256;
	वापस 0;
पूर्ण

/* monitor get callback */
अटल पूर्णांक snd_toneport_monitor_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = line6pcm->volume_monitor;
	वापस 0;
पूर्ण

/* monitor put callback */
अटल पूर्णांक snd_toneport_monitor_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	पूर्णांक err;

	अगर (ucontrol->value.पूर्णांकeger.value[0] == line6pcm->volume_monitor)
		वापस 0;

	line6pcm->volume_monitor = ucontrol->value.पूर्णांकeger.value[0];

	अगर (line6pcm->volume_monitor > 0) अणु
		err = line6_pcm_acquire(line6pcm, LINE6_STREAM_MONITOR, true);
		अगर (err < 0) अणु
			line6pcm->volume_monitor = 0;
			line6_pcm_release(line6pcm, LINE6_STREAM_MONITOR);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		line6_pcm_release(line6pcm, LINE6_STREAM_MONITOR);
	पूर्ण

	वापस 1;
पूर्ण

/* source info callback */
अटल पूर्णांक snd_toneport_source_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	स्थिर पूर्णांक size = ARRAY_SIZE(toneport_source_info);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = size;

	अगर (uinfo->value.क्रमागतerated.item >= size)
		uinfo->value.क्रमागतerated.item = size - 1;

	म_नकल(uinfo->value.क्रमागतerated.name,
	       toneport_source_info[uinfo->value.क्रमागतerated.item].name);

	वापस 0;
पूर्ण

/* source get callback */
अटल पूर्णांक snd_toneport_source_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_line6_toneport *toneport = line6_to_toneport(line6pcm->line6);

	ucontrol->value.क्रमागतerated.item[0] = toneport->source;
	वापस 0;
पूर्ण

/* source put callback */
अटल पूर्णांक snd_toneport_source_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_line6_toneport *toneport = line6_to_toneport(line6pcm->line6);
	अचिन्हित पूर्णांक source;

	source = ucontrol->value.क्रमागतerated.item[0];
	अगर (source >= ARRAY_SIZE(toneport_source_info))
		वापस -EINVAL;
	अगर (source == toneport->source)
		वापस 0;

	toneport->source = source;
	toneport_send_cmd(toneport->line6.usbdev,
			  toneport_source_info[source].code, 0x0000);
	वापस 1;
पूर्ण

अटल व्योम toneport_startup(काष्ठा usb_line6 *line6)
अणु
	line6_pcm_acquire(line6->line6pcm, LINE6_STREAM_MONITOR, true);
पूर्ण

/* control definition */
अटल स्थिर काष्ठा snd_kcontrol_new toneport_control_monitor = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Monitor Playback Volume",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_toneport_monitor_info,
	.get = snd_toneport_monitor_get,
	.put = snd_toneport_monitor_put
पूर्ण;

/* source selector definition */
अटल स्थिर काष्ठा snd_kcontrol_new toneport_control_source = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "PCM Capture Source",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_toneport_source_info,
	.get = snd_toneport_source_get,
	.put = snd_toneport_source_put
पूर्ण;

/*
	For the led on Guitarport.
	Brightness goes from 0x00 to 0x26. Set a value above this to have led
	blink.
	(व्योम cmd_0x02(byte red, byte green)
*/

अटल bool toneport_has_led(काष्ठा usb_line6_toneport *toneport)
अणु
	चयन (toneport->type) अणु
	हाल LINE6_GUITARPORT:
	हाल LINE6_TONEPORT_GX:
	/* add your device here अगर you are missing support क्रम the LEDs */
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर toneport_led_colors[2] = अणु "red", "green" पूर्ण;
अटल स्थिर पूर्णांक toneport_led_init_vals[2] = अणु 0x00, 0x26 पूर्ण;

अटल व्योम toneport_update_led(काष्ठा usb_line6_toneport *toneport)
अणु
	toneport_send_cmd(toneport->line6.usbdev,
			  (toneport->leds[0].dev.brightness << 8) | 0x0002,
			  toneport->leds[1].dev.brightness);
पूर्ण

अटल व्योम toneport_led_brightness_set(काष्ठा led_classdev *led_cdev,
					क्रमागत led_brightness brightness)
अणु
	काष्ठा toneport_led *leds =
		container_of(led_cdev, काष्ठा toneport_led, dev);
	toneport_update_led(leds->toneport);
पूर्ण

अटल पूर्णांक toneport_init_leds(काष्ठा usb_line6_toneport *toneport)
अणु
	काष्ठा device *dev = &toneport->line6.usbdev->dev;
	पूर्णांक i, err;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा toneport_led *led = &toneport->leds[i];
		काष्ठा led_classdev *leddev = &led->dev;

		led->toneport = toneport;
		snम_लिखो(led->name, माप(led->name), "%s::%s",
			 dev_name(dev), toneport_led_colors[i]);
		leddev->name = led->name;
		leddev->brightness = toneport_led_init_vals[i];
		leddev->max_brightness = 0x26;
		leddev->brightness_set = toneport_led_brightness_set;
		err = led_classdev_रेजिस्टर(dev, leddev);
		अगर (err)
			वापस err;
		led->रेजिस्टरed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम toneport_हटाओ_leds(काष्ठा usb_line6_toneport *toneport)
अणु
	काष्ठा toneport_led *led;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		led = &toneport->leds[i];
		अगर (!led->रेजिस्टरed)
			अवरोध;
		led_classdev_unरेजिस्टर(&led->dev);
		led->रेजिस्टरed = false;
	पूर्ण
पूर्ण

अटल bool toneport_has_source_select(काष्ठा usb_line6_toneport *toneport)
अणु
	चयन (toneport->type) अणु
	हाल LINE6_TONEPORT_UX1:
	हाल LINE6_TONEPORT_UX2:
	हाल LINE6_PODSTUDIO_UX1:
	हाल LINE6_PODSTUDIO_UX2:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
	Setup Toneport device.
*/
अटल पूर्णांक toneport_setup(काष्ठा usb_line6_toneport *toneport)
अणु
	u32 *ticks;
	काष्ठा usb_line6 *line6 = &toneport->line6;
	काष्ठा usb_device *usbdev = line6->usbdev;

	ticks = kदो_स्मृति(माप(*ticks), GFP_KERNEL);
	अगर (!ticks)
		वापस -ENOMEM;

	/* sync समय on device with host: */
	/* note: 32-bit बारtamps overflow in year 2106 */
	*ticks = (u32)kसमय_get_real_seconds();
	line6_ग_लिखो_data(line6, 0x80c6, ticks, 4);
	kमुक्त(ticks);

	/* enable device: */
	toneport_send_cmd(usbdev, 0x0301, 0x0000);

	/* initialize source select: */
	अगर (toneport_has_source_select(toneport))
		toneport_send_cmd(usbdev,
				  toneport_source_info[toneport->source].code,
				  0x0000);

	अगर (toneport_has_led(toneport))
		toneport_update_led(toneport);

	schedule_delayed_work(&toneport->line6.startup_work,
			      msecs_to_jअगरfies(TONEPORT_PCM_DELAY * 1000));
	वापस 0;
पूर्ण

/*
	Toneport device disconnected.
*/
अटल व्योम line6_toneport_disconnect(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_line6_toneport *toneport = line6_to_toneport(line6);

	अगर (toneport_has_led(toneport))
		toneport_हटाओ_leds(toneport);
पूर्ण


/*
	 Try to init Toneport device.
*/
अटल पूर्णांक toneport_init(काष्ठा usb_line6 *line6,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा usb_line6_toneport *toneport = line6_to_toneport(line6);

	toneport->type = id->driver_info;

	line6->disconnect = line6_toneport_disconnect;
	line6->startup = toneport_startup;

	/* initialize PCM subप्रणाली: */
	err = line6_init_pcm(line6, &toneport_pcm_properties);
	अगर (err < 0)
		वापस err;

	/* रेजिस्टर monitor control: */
	err = snd_ctl_add(line6->card,
			  snd_ctl_new1(&toneport_control_monitor,
				       line6->line6pcm));
	अगर (err < 0)
		वापस err;

	/* रेजिस्टर source select control: */
	अगर (toneport_has_source_select(toneport)) अणु
		err =
		    snd_ctl_add(line6->card,
				snd_ctl_new1(&toneport_control_source,
					     line6->line6pcm));
		अगर (err < 0)
			वापस err;
	पूर्ण

	line6_पढ़ो_serial_number(line6, &toneport->serial_number);
	line6_पढ़ो_data(line6, 0x80c2, &toneport->firmware_version, 1);

	अगर (toneport_has_led(toneport)) अणु
		err = toneport_init_leds(toneport);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = toneport_setup(toneport);
	अगर (err)
		वापस err;

	/* रेजिस्टर audio प्रणाली: */
	वापस snd_card_रेजिस्टर(line6->card);
पूर्ण

#अगर_घोषित CONFIG_PM
/*
	Resume Toneport device after reset.
*/
अटल पूर्णांक toneport_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	पूर्णांक err;

	err = toneport_setup(usb_get_पूर्णांकfdata(पूर्णांकerface));
	अगर (err)
		वापस err;
	वापस line6_resume(पूर्णांकerface);
पूर्ण
#पूर्ण_अगर

#घोषणा LINE6_DEVICE(prod) USB_DEVICE(0x0e41, prod)
#घोषणा LINE6_IF_NUM(prod, n) USB_DEVICE_INTERFACE_NUMBER(0x0e41, prod, n)

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id toneport_id_table[] = अणु
	अणु LINE6_DEVICE(0x4750),    .driver_info = LINE6_GUITARPORT पूर्ण,
	अणु LINE6_DEVICE(0x4153),    .driver_info = LINE6_PODSTUDIO_GX पूर्ण,
	अणु LINE6_DEVICE(0x4150),    .driver_info = LINE6_PODSTUDIO_UX1 पूर्ण,
	अणु LINE6_IF_NUM(0x4151, 0), .driver_info = LINE6_PODSTUDIO_UX2 पूर्ण,
	अणु LINE6_DEVICE(0x4147),    .driver_info = LINE6_TONEPORT_GX पूर्ण,
	अणु LINE6_DEVICE(0x4141),    .driver_info = LINE6_TONEPORT_UX1 पूर्ण,
	अणु LINE6_IF_NUM(0x4142, 0), .driver_info = LINE6_TONEPORT_UX2 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, toneport_id_table);

अटल स्थिर काष्ठा line6_properties toneport_properties_table[] = अणु
	[LINE6_GUITARPORT] = अणु
		.id = "GuitarPort",
		.name = "GuitarPort",
		.capabilities	= LINE6_CAP_PCM,
		.altsetting = 2,  /* 1..4 seem to be ok */
		/* no control channel */
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_PODSTUDIO_GX] = अणु
		.id = "PODStudioGX",
		.name = "POD Studio GX",
		.capabilities	= LINE6_CAP_PCM,
		.altsetting = 2,  /* 1..4 seem to be ok */
		/* no control channel */
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_PODSTUDIO_UX1] = अणु
		.id = "PODStudioUX1",
		.name = "POD Studio UX1",
		.capabilities	= LINE6_CAP_PCM,
		.altsetting = 2,  /* 1..4 seem to be ok */
		/* no control channel */
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_PODSTUDIO_UX2] = अणु
		.id = "PODStudioUX2",
		.name = "POD Studio UX2",
		.capabilities	= LINE6_CAP_PCM,
		.altsetting = 2,  /* शेषs to 44.1kHz, 16-bit */
		/* no control channel */
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_TONEPORT_GX] = अणु
		.id = "TonePortGX",
		.name = "TonePort GX",
		.capabilities	= LINE6_CAP_PCM,
		.altsetting = 2,  /* 1..4 seem to be ok */
		/* no control channel */
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_TONEPORT_UX1] = अणु
		.id = "TonePortUX1",
		.name = "TonePort UX1",
		.capabilities	= LINE6_CAP_PCM,
		.altsetting = 2,  /* 1..4 seem to be ok */
		/* no control channel */
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_TONEPORT_UX2] = अणु
		.id = "TonePortUX2",
		.name = "TonePort UX2",
		.capabilities	= LINE6_CAP_PCM,
		.altsetting = 2,  /* शेषs to 44.1kHz, 16-bit */
		/* no control channel */
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
पूर्ण;

/*
	Probe USB device.
*/
अटल पूर्णांक toneport_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	वापस line6_probe(पूर्णांकerface, id, "Line6-TonePort",
			   &toneport_properties_table[id->driver_info],
			   toneport_init, माप(काष्ठा usb_line6_toneport));
पूर्ण

अटल काष्ठा usb_driver toneport_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = toneport_probe,
	.disconnect = line6_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = line6_suspend,
	.resume = line6_resume,
	.reset_resume = toneport_reset_resume,
#पूर्ण_अगर
	.id_table = toneport_id_table,
पूर्ण;

module_usb_driver(toneport_driver);

MODULE_DESCRIPTION("TonePort USB driver");
MODULE_LICENSE("GPL");

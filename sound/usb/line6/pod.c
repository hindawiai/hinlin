<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>

#समावेश "capture.h"
#समावेश "driver.h"
#समावेश "playback.h"

/*
	Locate name in binary program dump
*/
#घोषणा	POD_NAME_OFFSET 0
#घोषणा	POD_NAME_LENGTH 16

/*
	Other स्थिरants
*/
#घोषणा POD_CONTROL_SIZE 0x80
#घोषणा POD_बफ_मानE_DUMPREQ 7
#घोषणा POD_STARTUP_DELAY 1000

/*
	Stages of POD startup procedure
*/
क्रमागत अणु
	POD_STARTUP_VERSIONREQ,
	POD_STARTUP_SETUP,
	POD_STARTUP_DONE,
पूर्ण;

क्रमागत अणु
	LINE6_BASSPODXT,
	LINE6_BASSPODXTLIVE,
	LINE6_BASSPODXTPRO,
	LINE6_POCKETPOD,
	LINE6_PODXT,
	LINE6_PODXTLIVE_POD,
	LINE6_PODXTPRO,
पूर्ण;

काष्ठा usb_line6_pod अणु
	/* Generic Line 6 USB data */
	काष्ठा usb_line6 line6;

	/* Instrument monitor level */
	पूर्णांक monitor_level;

	/* Current progress in startup procedure */
	पूर्णांक startup_progress;

	/* Serial number of device */
	u32 serial_number;

	/* Firmware version (x 100) */
	पूर्णांक firmware_version;

	/* Device ID */
	पूर्णांक device_id;
पूर्ण;

#घोषणा line6_to_pod(x)		container_of(x, काष्ठा usb_line6_pod, line6)

#घोषणा POD_SYSEX_CODE 3

/* *INDENT-OFF* */

क्रमागत अणु
	POD_SYSEX_SAVE      = 0x24,
	POD_SYSEX_SYSTEM    = 0x56,
	POD_SYSEX_SYSTEMREQ = 0x57,
	/* POD_SYSEX_UPDATE    = 0x6c, */  /* software update! */
	POD_SYSEX_STORE     = 0x71,
	POD_SYSEX_FINISH    = 0x72,
	POD_SYSEX_DUMPMEM   = 0x73,
	POD_SYSEX_DUMP      = 0x74,
	POD_SYSEX_DUMPREQ   = 0x75

	/* dumps entire पूर्णांकernal memory of PODxt Pro */
	/* POD_SYSEX_DUMPMEM2  = 0x76 */
पूर्ण;

क्रमागत अणु
	POD_MONITOR_LEVEL  = 0x04,
	POD_SYSTEM_INVALID = 0x10000
पूर्ण;

/* *INDENT-ON* */

क्रमागत अणु
	POD_DUMP_MEMORY = 2
पूर्ण;

क्रमागत अणु
	POD_BUSY_READ,
	POD_BUSY_WRITE,
	POD_CHANNEL_सूचीTY,
	POD_SAVE_PRESSED,
	POD_BUSY_MIDISEND
पूर्ण;

अटल स्थिर काष्ठा snd_ratden pod_ratden = अणु
	.num_min = 78125,
	.num_max = 78125,
	.num_step = 1,
	.den = 2
पूर्ण;

अटल काष्ठा line6_pcm_properties pod_pcm_properties = अणु
	.playback_hw = अणु
				  .info = (SNDRV_PCM_INFO_MMAP |
					   SNDRV_PCM_INFO_INTERLEAVED |
					   SNDRV_PCM_INFO_BLOCK_TRANSFER |
					   SNDRV_PCM_INFO_MMAP_VALID |
					   SNDRV_PCM_INFO_PAUSE |
					   SNDRV_PCM_INFO_SYNC_START),
				  .क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
				  .rates = SNDRV_PCM_RATE_KNOT,
				  .rate_min = 39062,
				  .rate_max = 39063,
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
				 .rates = SNDRV_PCM_RATE_KNOT,
				 .rate_min = 39062,
				 .rate_max = 39063,
				 .channels_min = 2,
				 .channels_max = 2,
				 .buffer_bytes_max = 60000,
				 .period_bytes_min = 64,
				 .period_bytes_max = 8192,
				 .periods_min = 1,
				 .periods_max = 1024पूर्ण,
	.rates = अणु
			    .nrats = 1,
			    .rats = &pod_ratdenपूर्ण,
	.bytes_per_channel = 3 /* SNDRV_PCM_FMTBIT_S24_3LE */
पूर्ण;

अटल स्थिर अक्षर pod_version_header[] = अणु
	0xf2, 0x7e, 0x7f, 0x06, 0x02
पूर्ण;

अटल अक्षर *pod_alloc_sysex_buffer(काष्ठा usb_line6_pod *pod, पूर्णांक code,
				    पूर्णांक size)
अणु
	वापस line6_alloc_sysex_buffer(&pod->line6, POD_SYSEX_CODE, code,
					size);
पूर्ण

/*
	Process a completely received message.
*/
अटल व्योम line6_pod_process_message(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_line6_pod *pod = line6_to_pod(line6);
	स्थिर अचिन्हित अक्षर *buf = pod->line6.buffer_message;

	अगर (स_भेद(buf, pod_version_header, माप(pod_version_header)) == 0) अणु
		pod->firmware_version = buf[13] * 100 + buf[14] * 10 + buf[15];
		pod->device_id = ((पूर्णांक)buf[8] << 16) | ((पूर्णांक)buf[9] << 8) |
				 (पूर्णांक) buf[10];
		अगर (pod->startup_progress == POD_STARTUP_VERSIONREQ) अणु
			pod->startup_progress = POD_STARTUP_SETUP;
			schedule_delayed_work(&line6->startup_work, 0);
		पूर्ण
		वापस;
	पूर्ण

	/* Only look क्रम sysex messages from this device */
	अगर (buf[0] != (LINE6_SYSEX_BEGIN | LINE6_CHANNEL_DEVICE) &&
	    buf[0] != (LINE6_SYSEX_BEGIN | LINE6_CHANNEL_UNKNOWN)) अणु
		वापस;
	पूर्ण
	अगर (स_भेद(buf + 1, line6_midi_id, माप(line6_midi_id)) != 0)
		वापस;

	अगर (buf[5] == POD_SYSEX_SYSTEM && buf[6] == POD_MONITOR_LEVEL) अणु
		लघु value = ((पूर्णांक)buf[7] << 12) | ((पूर्णांक)buf[8] << 8) |
			      ((पूर्णांक)buf[9] << 4) | (पूर्णांक)buf[10];
		pod->monitor_level = value;
	पूर्ण
पूर्ण

/*
	Send प्रणाली parameter (from पूर्णांकeger).
*/
अटल पूर्णांक pod_set_प्रणाली_param_पूर्णांक(काष्ठा usb_line6_pod *pod, पूर्णांक value,
				    पूर्णांक code)
अणु
	अक्षर *sysex;
	अटल स्थिर पूर्णांक size = 5;

	sysex = pod_alloc_sysex_buffer(pod, POD_SYSEX_SYSTEM, size);
	अगर (!sysex)
		वापस -ENOMEM;
	sysex[SYSEX_DATA_OFS] = code;
	sysex[SYSEX_DATA_OFS + 1] = (value >> 12) & 0x0f;
	sysex[SYSEX_DATA_OFS + 2] = (value >> 8) & 0x0f;
	sysex[SYSEX_DATA_OFS + 3] = (value >> 4) & 0x0f;
	sysex[SYSEX_DATA_OFS + 4] = (value) & 0x0f;
	line6_send_sysex_message(&pod->line6, sysex, size);
	kमुक्त(sysex);
	वापस 0;
पूर्ण

/*
	"read" request on "serial_number" special file.
*/
अटल sमाप_प्रकार serial_number_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_card *card = dev_to_snd_card(dev);
	काष्ठा usb_line6_pod *pod = card->निजी_data;

	वापस प्र_लिखो(buf, "%u\n", pod->serial_number);
पूर्ण

/*
	"read" request on "firmware_version" special file.
*/
अटल sमाप_प्रकार firmware_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_card *card = dev_to_snd_card(dev);
	काष्ठा usb_line6_pod *pod = card->निजी_data;

	वापस प्र_लिखो(buf, "%d.%02d\n", pod->firmware_version / 100,
		       pod->firmware_version % 100);
पूर्ण

/*
	"read" request on "device_id" special file.
*/
अटल sमाप_प्रकार device_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_card *card = dev_to_snd_card(dev);
	काष्ठा usb_line6_pod *pod = card->निजी_data;

	वापस प्र_लिखो(buf, "%d\n", pod->device_id);
पूर्ण

/*
	POD startup procedure.
	This is a sequence of functions with special requirements (e.g., must
	not run immediately after initialization, must not run in पूर्णांकerrupt
	context). After the last one has finished, the device is पढ़ोy to use.
*/

अटल व्योम pod_startup(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_line6_pod *pod = line6_to_pod(line6);

	चयन (pod->startup_progress) अणु
	हाल POD_STARTUP_VERSIONREQ:
		/* request firmware version: */
		line6_version_request_async(line6);
		अवरोध;
	हाल POD_STARTUP_SETUP:
		/* serial number: */
		line6_पढ़ो_serial_number(&pod->line6, &pod->serial_number);

		/* ALSA audio पूर्णांकerface: */
		अगर (snd_card_रेजिस्टर(line6->card))
			dev_err(line6->अगरcdev, "Failed to register POD card.\n");
		pod->startup_progress = POD_STARTUP_DONE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* POD special files: */
अटल DEVICE_ATTR_RO(device_id);
अटल DEVICE_ATTR_RO(firmware_version);
अटल DEVICE_ATTR_RO(serial_number);

अटल काष्ठा attribute *pod_dev_attrs[] = अणु
	&dev_attr_device_id.attr,
	&dev_attr_firmware_version.attr,
	&dev_attr_serial_number.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pod_dev_attr_group = अणु
	.name = "pod",
	.attrs = pod_dev_attrs,
पूर्ण;

/* control info callback */
अटल पूर्णांक snd_pod_control_monitor_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 65535;
	वापस 0;
पूर्ण

/* control get callback */
अटल पूर्णांक snd_pod_control_monitor_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_line6_pod *pod = line6_to_pod(line6pcm->line6);

	ucontrol->value.पूर्णांकeger.value[0] = pod->monitor_level;
	वापस 0;
पूर्ण

/* control put callback */
अटल पूर्णांक snd_pod_control_monitor_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_line6_pod *pod = line6_to_pod(line6pcm->line6);

	अगर (ucontrol->value.पूर्णांकeger.value[0] == pod->monitor_level)
		वापस 0;

	pod->monitor_level = ucontrol->value.पूर्णांकeger.value[0];
	pod_set_प्रणाली_param_पूर्णांक(pod, ucontrol->value.पूर्णांकeger.value[0],
				 POD_MONITOR_LEVEL);
	वापस 1;
पूर्ण

/* control definition */
अटल स्थिर काष्ठा snd_kcontrol_new pod_control_monitor = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Monitor Playback Volume",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_pod_control_monitor_info,
	.get = snd_pod_control_monitor_get,
	.put = snd_pod_control_monitor_put
पूर्ण;

/*
	 Try to init POD device.
*/
अटल पूर्णांक pod_init(काष्ठा usb_line6 *line6,
		    स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा usb_line6_pod *pod = line6_to_pod(line6);

	line6->process_message = line6_pod_process_message;
	line6->startup = pod_startup;

	/* create sysfs entries: */
	err = snd_card_add_dev_attr(line6->card, &pod_dev_attr_group);
	अगर (err < 0)
		वापस err;

	/* initialize PCM subप्रणाली: */
	err = line6_init_pcm(line6, &pod_pcm_properties);
	अगर (err < 0)
		वापस err;

	/* रेजिस्टर monitor control: */
	err = snd_ctl_add(line6->card,
			  snd_ctl_new1(&pod_control_monitor, line6->line6pcm));
	अगर (err < 0)
		वापस err;

	/*
	   When the sound card is रेजिस्टरed at this poपूर्णांक, the PODxt Live
	   displays "Invalid Code Error 07", so we करो it later in the event
	   handler.
	 */

	अगर (pod->line6.properties->capabilities & LINE6_CAP_CONTROL) अणु
		pod->monitor_level = POD_SYSTEM_INVALID;

		/* initiate startup procedure: */
		schedule_delayed_work(&line6->startup_work,
				      msecs_to_jअगरfies(POD_STARTUP_DELAY));
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा LINE6_DEVICE(prod) USB_DEVICE(0x0e41, prod)
#घोषणा LINE6_IF_NUM(prod, n) USB_DEVICE_INTERFACE_NUMBER(0x0e41, prod, n)

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id pod_id_table[] = अणु
	अणु LINE6_DEVICE(0x4250),    .driver_info = LINE6_BASSPODXT पूर्ण,
	अणु LINE6_DEVICE(0x4642),    .driver_info = LINE6_BASSPODXTLIVE पूर्ण,
	अणु LINE6_DEVICE(0x4252),    .driver_info = LINE6_BASSPODXTPRO पूर्ण,
	अणु LINE6_IF_NUM(0x5051, 1), .driver_info = LINE6_POCKETPOD पूर्ण,
	अणु LINE6_DEVICE(0x5044),    .driver_info = LINE6_PODXT पूर्ण,
	अणु LINE6_IF_NUM(0x4650, 0), .driver_info = LINE6_PODXTLIVE_POD पूर्ण,
	अणु LINE6_DEVICE(0x5050),    .driver_info = LINE6_PODXTPRO पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, pod_id_table);

अटल स्थिर काष्ठा line6_properties pod_properties_table[] = अणु
	[LINE6_BASSPODXT] = अणु
		.id = "BassPODxt",
		.name = "BassPODxt",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI
				| LINE6_CAP_PCM
				| LINE6_CAP_HWMON,
		.altsetting = 5,
		.ep_ctrl_r = 0x84,
		.ep_ctrl_w = 0x03,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_BASSPODXTLIVE] = अणु
		.id = "BassPODxtLive",
		.name = "BassPODxt Live",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI
				| LINE6_CAP_PCM
				| LINE6_CAP_HWMON,
		.altsetting = 1,
		.ep_ctrl_r = 0x84,
		.ep_ctrl_w = 0x03,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_BASSPODXTPRO] = अणु
		.id = "BassPODxtPro",
		.name = "BassPODxt Pro",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI
				| LINE6_CAP_PCM
				| LINE6_CAP_HWMON,
		.altsetting = 5,
		.ep_ctrl_r = 0x84,
		.ep_ctrl_w = 0x03,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_POCKETPOD] = अणु
		.id = "PocketPOD",
		.name = "Pocket POD",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI,
		.altsetting = 0,
		.ep_ctrl_r = 0x82,
		.ep_ctrl_w = 0x02,
		/* no audio channel */
	पूर्ण,
	[LINE6_PODXT] = अणु
		.id = "PODxt",
		.name = "PODxt",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI
				| LINE6_CAP_PCM
				| LINE6_CAP_HWMON,
		.altsetting = 5,
		.ep_ctrl_r = 0x84,
		.ep_ctrl_w = 0x03,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_PODXTLIVE_POD] = अणु
		.id = "PODxtLive",
		.name = "PODxt Live",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI
				| LINE6_CAP_PCM
				| LINE6_CAP_HWMON,
		.altsetting = 1,
		.ep_ctrl_r = 0x84,
		.ep_ctrl_w = 0x03,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_PODXTPRO] = अणु
		.id = "PODxtPro",
		.name = "PODxt Pro",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI
				| LINE6_CAP_PCM
				| LINE6_CAP_HWMON,
		.altsetting = 5,
		.ep_ctrl_r = 0x84,
		.ep_ctrl_w = 0x03,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
पूर्ण;

/*
	Probe USB device.
*/
अटल पूर्णांक pod_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	वापस line6_probe(पूर्णांकerface, id, "Line6-POD",
			   &pod_properties_table[id->driver_info],
			   pod_init, माप(काष्ठा usb_line6_pod));
पूर्ण

अटल काष्ठा usb_driver pod_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = pod_probe,
	.disconnect = line6_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = line6_suspend,
	.resume = line6_resume,
	.reset_resume = line6_resume,
#पूर्ण_अगर
	.id_table = pod_id_table,
पूर्ण;

module_usb_driver(pod_driver);

MODULE_DESCRIPTION("Line 6 POD USB driver");
MODULE_LICENSE("GPL");

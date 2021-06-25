<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#अगर_अघोषित DRIVER_H
#घोषणा DRIVER_H

#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kfअगरo.h>
#समावेश <sound/core.h>

#समावेश "midi.h"

/* USB 1.1 speed configuration */
#घोषणा USB_LOW_INTERVALS_PER_SECOND 1000
#घोषणा USB_LOW_ISO_BUFFERS 2

/* USB 2.0+ speed configuration */
#घोषणा USB_HIGH_INTERVALS_PER_SECOND 8000
#घोषणा USB_HIGH_ISO_BUFFERS 16

/* Fallback USB पूर्णांकerval and max packet size values */
#घोषणा LINE6_FALLBACK_INTERVAL 10
#घोषणा LINE6_FALLBACK_MAXPACKETSIZE 16

#घोषणा LINE6_TIMEOUT 1
#घोषणा LINE6_बफ_मानE_LISTEN 64
#घोषणा LINE6_MIDI_MESSAGE_MAXLEN 256

#घोषणा LINE6_RAW_MESSAGES_MAXCOUNT_ORDER 7
/* 4k packets are common, बफ_मानE * MAXCOUNT should be bigger... */
#घोषणा LINE6_RAW_MESSAGES_MAXCOUNT (1 << LINE6_RAW_MESSAGES_MAXCOUNT_ORDER)


#अगर LINE6_बफ_मानE_LISTEN > 65535
#त्रुटि "Use dynamic fifo instead"
#पूर्ण_अगर

/*
	Line 6 MIDI control commands
*/
#घोषणा LINE6_PARAM_CHANGE   0xb0
#घोषणा LINE6_PROGRAM_CHANGE 0xc0
#घोषणा LINE6_SYSEX_BEGIN    0xf0
#घोषणा LINE6_SYSEX_END      0xf7
#घोषणा LINE6_RESET          0xff

/*
	MIDI channel क्रम messages initiated by the host
	(and eventually echoed back by the device)
*/
#घोषणा LINE6_CHANNEL_HOST   0x00

/*
	MIDI channel क्रम messages initiated by the device
*/
#घोषणा LINE6_CHANNEL_DEVICE 0x02

#घोषणा LINE6_CHANNEL_UNKNOWN 5	/* करोn't know yet what this is good क्रम */

#घोषणा LINE6_CHANNEL_MASK 0x0f

बाह्य स्थिर अचिन्हित अक्षर line6_midi_id[3];

#घोषणा SYSEX_DATA_OFS (माप(line6_midi_id) + 3)
#घोषणा SYSEX_EXTRA_SIZE (माप(line6_midi_id) + 4)

/*
	 Common properties of Line 6 devices.
*/
काष्ठा line6_properties अणु
	/* Card id string (maximum 16 अक्षरacters).
	 * This can be used to address the device in ALSA programs as
	 * "default:CARD=<id>"
	 */
	स्थिर अक्षर *id;

	/* Card लघु name (maximum 32 अक्षरacters) */
	स्थिर अक्षर *name;

	/* Bit vector defining this device's capabilities in line6usb driver */
	पूर्णांक capabilities;

	पूर्णांक altsetting;

	अचिन्हित पूर्णांक ctrl_अगर;
	अचिन्हित पूर्णांक ep_ctrl_r;
	अचिन्हित पूर्णांक ep_ctrl_w;
	अचिन्हित पूर्णांक ep_audio_r;
	अचिन्हित पूर्णांक ep_audio_w;
पूर्ण;

/* Capability bits */
क्रमागत अणु
	/* device supports settings parameter via USB */
	LINE6_CAP_CONTROL =	1 << 0,
	/* device supports PCM input/output via USB */
	LINE6_CAP_PCM =		1 << 1,
	/* device supports hardware monitoring */
	LINE6_CAP_HWMON =	1 << 2,
	/* device requires output data when input is पढ़ो */
	LINE6_CAP_IN_NEEDS_OUT = 1 << 3,
	/* device uses raw MIDI via USB (data endpoपूर्णांकs) */
	LINE6_CAP_CONTROL_MIDI = 1 << 4,
	/* device provides low-level inक्रमmation */
	LINE6_CAP_CONTROL_INFO = 1 << 5,
	/* device provides hardware monitoring volume control */
	LINE6_CAP_HWMON_CTL =	1 << 6,
पूर्ण;

/*
	 Common data shared by all Line 6 devices.
	 Corresponds to a pair of USB endpoपूर्णांकs.
*/
काष्ठा usb_line6 अणु
	/* USB device */
	काष्ठा usb_device *usbdev;

	/* Properties */
	स्थिर काष्ठा line6_properties *properties;

	/* Interval क्रम data USB packets */
	पूर्णांक पूर्णांकerval;
	/* ...क्रम isochronous transfers framing */
	पूर्णांक पूर्णांकervals_per_second;

	/* Number of isochronous URBs used क्रम frame transfers */
	पूर्णांक iso_buffers;

	/* Maximum size of data USB packet */
	पूर्णांक max_packet_size;

	/* Device representing the USB पूर्णांकerface */
	काष्ठा device *अगरcdev;

	/* Line 6 sound card data काष्ठाure.
	 * Each device has at least MIDI or PCM.
	 */
	काष्ठा snd_card *card;

	/* Line 6 PCM device data काष्ठाure */
	काष्ठा snd_line6_pcm *line6pcm;

	/* Line 6 MIDI device data काष्ठाure */
	काष्ठा snd_line6_midi *line6midi;

	/* URB क्रम listening to POD data endpoपूर्णांक */
	काष्ठा urb *urb_listen;

	/* Buffer क्रम incoming data from POD data endpoपूर्णांक */
	अचिन्हित अक्षर *buffer_listen;

	/* Buffer क्रम message to be processed, generated from MIDI layer */
	अचिन्हित अक्षर *buffer_message;

	/* Length of message to be processed, generated from MIDI layer  */
	पूर्णांक message_length;

	/* Circular buffer क्रम non-MIDI control messages */
	काष्ठा अणु
		काष्ठा mutex पढ़ो_lock;
		रुको_queue_head_t रुको_queue;
		अचिन्हित पूर्णांक active:1;
		अचिन्हित पूर्णांक nonblock:1;
		STRUCT_KFIFO_REC_2(LINE6_बफ_मानE_LISTEN * LINE6_RAW_MESSAGES_MAXCOUNT)
			fअगरo;
	पूर्ण messages;

	/* Work क्रम delayed PCM startup */
	काष्ठा delayed_work startup_work;

	/* If MIDI is supported, buffer_message contains the pre-processed data;
	 * otherwise the data is only in urb_listen (buffer_incoming).
	 */
	व्योम (*process_message)(काष्ठा usb_line6 *);
	व्योम (*disconnect)(काष्ठा usb_line6 *line6);
	व्योम (*startup)(काष्ठा usb_line6 *line6);
पूर्ण;

बाह्य अक्षर *line6_alloc_sysex_buffer(काष्ठा usb_line6 *line6, पूर्णांक code1,
				      पूर्णांक code2, पूर्णांक size);
बाह्य पूर्णांक line6_पढ़ो_data(काष्ठा usb_line6 *line6, अचिन्हित address,
			   व्योम *data, अचिन्हित datalen);
बाह्य पूर्णांक line6_पढ़ो_serial_number(काष्ठा usb_line6 *line6,
				    u32 *serial_number);
बाह्य पूर्णांक line6_send_raw_message(काष्ठा usb_line6 *line6,
					स्थिर अक्षर *buffer, पूर्णांक size);
बाह्य पूर्णांक line6_send_raw_message_async(काष्ठा usb_line6 *line6,
					स्थिर अक्षर *buffer, पूर्णांक size);
बाह्य पूर्णांक line6_send_sysex_message(काष्ठा usb_line6 *line6,
				    स्थिर अक्षर *buffer, पूर्णांक size);
बाह्य sमाप_प्रकार line6_set_raw(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count);
बाह्य पूर्णांक line6_version_request_async(काष्ठा usb_line6 *line6);
बाह्य पूर्णांक line6_ग_लिखो_data(काष्ठा usb_line6 *line6, अचिन्हित address,
			    व्योम *data, अचिन्हित datalen);

पूर्णांक line6_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		स्थिर काष्ठा usb_device_id *id,
		स्थिर अक्षर *driver_name,
		स्थिर काष्ठा line6_properties *properties,
		पूर्णांक (*निजी_init)(काष्ठा usb_line6 *, स्थिर काष्ठा usb_device_id *id),
		माप_प्रकार data_size);

व्योम line6_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);

#अगर_घोषित CONFIG_PM
पूर्णांक line6_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, pm_message_t message);
पूर्णांक line6_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
#पूर्ण_अगर

#पूर्ण_अगर

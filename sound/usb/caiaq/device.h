<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CAIAQ_DEVICE_H
#घोषणा CAIAQ_DEVICE_H

#समावेश "../usbaudio.h"

#घोषणा USB_VID_NATIVEINSTRUMENTS 0x17cc

#घोषणा USB_PID_RIGKONTROL2		0x1969
#घोषणा USB_PID_RIGKONTROL3		0x1940
#घोषणा USB_PID_KORECONTROLLER		0x4711
#घोषणा USB_PID_KORECONTROLLER2		0x4712
#घोषणा USB_PID_AK1			0x0815
#घोषणा USB_PID_AUDIO2DJ		0x041c
#घोषणा USB_PID_AUDIO4DJ		0x0839
#घोषणा USB_PID_AUDIO8DJ		0x1978
#घोषणा USB_PID_SESSIONIO		0x1915
#घोषणा USB_PID_GUITARRIGMOBILE		0x0d8d
#घोषणा USB_PID_TRAKTORKONTROLX1	0x2305
#घोषणा USB_PID_TRAKTORKONTROLS4	0xbaff
#घोषणा USB_PID_TRAKTORAUDIO2		0x041d
#घोषणा USB_PID_MASCHINECONTROLLER  0x0808

#घोषणा EP1_बफ_मानE 64
#घोषणा EP4_बफ_मानE 512
#घोषणा CAIAQ_USB_STR_LEN 0xff
#घोषणा MAX_STREAMS 32

#घोषणा MODNAME "snd-usb-caiaq"

#घोषणा EP1_CMD_GET_DEVICE_INFO	0x1
#घोषणा EP1_CMD_READ_ERP	0x2
#घोषणा EP1_CMD_READ_ANALOG	0x3
#घोषणा EP1_CMD_READ_IO		0x4
#घोषणा EP1_CMD_WRITE_IO	0x5
#घोषणा EP1_CMD_MIDI_READ	0x6
#घोषणा EP1_CMD_MIDI_WRITE	0x7
#घोषणा EP1_CMD_AUDIO_PARAMS	0x9
#घोषणा EP1_CMD_AUTO_MSG	0xb
#घोषणा EP1_CMD_DIMM_LEDS       0xc

काष्ठा caiaq_device_spec अणु
	अचिन्हित लघु fw_version;
	अचिन्हित अक्षर hw_subtype;
	अचिन्हित अक्षर num_erp;
	अचिन्हित अक्षर num_analog_in;
	अचिन्हित अक्षर num_digital_in;
	अचिन्हित अक्षर num_digital_out;
	अचिन्हित अक्षर num_analog_audio_out;
	अचिन्हित अक्षर num_analog_audio_in;
	अचिन्हित अक्षर num_digital_audio_out;
	अचिन्हित अक्षर num_digital_audio_in;
	अचिन्हित अक्षर num_midi_out;
	अचिन्हित अक्षर num_midi_in;
	अचिन्हित अक्षर data_alignment;
पूर्ण __attribute__ ((packed));

काष्ठा snd_usb_caiaq_cb_info;

काष्ठा snd_usb_caiaqdev अणु
	काष्ठा snd_usb_audio chip;

	काष्ठा urb ep1_in_urb;
	काष्ठा urb midi_out_urb;
	काष्ठा urb **data_urbs_in;
	काष्ठा urb **data_urbs_out;
	काष्ठा snd_usb_caiaq_cb_info *data_cb_info;

	अचिन्हित अक्षर ep1_in_buf[EP1_बफ_मानE];
	अचिन्हित अक्षर ep1_out_buf[EP1_बफ_मानE];
	अचिन्हित अक्षर midi_out_buf[EP1_बफ_मानE];

	काष्ठा caiaq_device_spec spec;
	spinlock_t spinlock;
	रुको_queue_head_t ep1_रुको_queue;
	रुको_queue_head_t prepare_रुको_queue;
	पूर्णांक spec_received, audio_parm_answer;
	पूर्णांक midi_out_active;

	अक्षर venकरोr_name[CAIAQ_USB_STR_LEN];
	अक्षर product_name[CAIAQ_USB_STR_LEN];

	पूर्णांक n_streams, n_audio_in, n_audio_out;
	पूर्णांक streaming, first_packet, output_running;
	पूर्णांक audio_in_buf_pos[MAX_STREAMS];
	पूर्णांक audio_out_buf_pos[MAX_STREAMS];
	पूर्णांक period_in_count[MAX_STREAMS];
	पूर्णांक period_out_count[MAX_STREAMS];
	पूर्णांक input_panic, output_panic, warned;
	अक्षर *audio_in_buf, *audio_out_buf;
	अचिन्हित पूर्णांक samplerates, bpp;
	अचिन्हित दीर्घ outurb_active_mask;

	काष्ठा snd_pcm_substream *sub_playback[MAX_STREAMS];
	काष्ठा snd_pcm_substream *sub_capture[MAX_STREAMS];

	/* Controls */
	अचिन्हित अक्षर control_state[256];
	अचिन्हित अक्षर ep8_out_buf[2];

	/* Linux input */
#अगर_घोषित CONFIG_SND_USB_CAIAQ_INPUT
	काष्ठा input_dev *input_dev;
	अक्षर phys[64];			/* physical device path */
	अचिन्हित लघु keycode[128];
	काष्ठा urb *ep4_in_urb;
	अचिन्हित अक्षर ep4_in_buf[EP4_बफ_मानE];
#पूर्ण_अगर

	/* ALSA */
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_hardware pcm_info;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *midi_receive_substream;
	काष्ठा snd_rawmidi_substream *midi_out_substream;
पूर्ण;

काष्ठा snd_usb_caiaq_cb_info अणु
	काष्ठा snd_usb_caiaqdev *cdev;
	पूर्णांक index;
पूर्ण;

#घोषणा caiaqdev(c) ((काष्ठा snd_usb_caiaqdev*)(c)->निजी_data)
#घोषणा caiaqdev_to_dev(d)	(d->chip.card->dev)

पूर्णांक snd_usb_caiaq_set_audio_params (काष्ठा snd_usb_caiaqdev *cdev, पूर्णांक rate, पूर्णांक depth, पूर्णांक bbp);
पूर्णांक snd_usb_caiaq_set_स्वतः_msg (काष्ठा snd_usb_caiaqdev *cdev, पूर्णांक digital, पूर्णांक analog, पूर्णांक erp);
पूर्णांक snd_usb_caiaq_send_command(काष्ठा snd_usb_caiaqdev *cdev,
			       अचिन्हित अक्षर command,
			       स्थिर अचिन्हित अक्षर *buffer,
			       पूर्णांक len);
पूर्णांक snd_usb_caiaq_send_command_bank(काष्ठा snd_usb_caiaqdev *cdev,
			       अचिन्हित अक्षर command,
			       अचिन्हित अक्षर bank,
			       स्थिर अचिन्हित अक्षर *buffer,
			       पूर्णांक len);

#पूर्ण_अगर /* CAIAQ_DEVICE_H */

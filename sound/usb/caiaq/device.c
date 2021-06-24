<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * caiaq.c: ALSA driver क्रम caiaq/NativeInstruments devices
 *
 *   Copyright (c) 2007 Daniel Mack <daniel@caiaq.de>
 *                      Karsten Wiese <fzu@wemgehoertderstaat.de>
*/

#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <linux/usb.h>
#समावेश <sound/initval.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "device.h"
#समावेश "audio.h"
#समावेश "midi.h"
#समावेश "control.h"
#समावेश "input.h"

MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>");
MODULE_DESCRIPTION("caiaq USB audio");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX; /* Index 0-max */
अटल अक्षर* id[SNDRV_CARDS] = SNDRV_DEFAULT_STR; /* Id क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP; /* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the caiaq sound device");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the caiaq soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable the caiaq soundcard.");

क्रमागत अणु
	SAMPLERATE_44100	= 0,
	SAMPLERATE_48000	= 1,
	SAMPLERATE_96000	= 2,
	SAMPLERATE_192000	= 3,
	SAMPLERATE_88200	= 4,
	SAMPLERATE_INVALID	= 0xff
पूर्ण;

क्रमागत अणु
	DEPTH_NONE	= 0,
	DEPTH_16	= 1,
	DEPTH_24	= 2,
	DEPTH_32	= 3
पूर्ण;

अटल स्थिर काष्ठा usb_device_id snd_usb_id_table[] = अणु
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	USB_VID_NATIVEINSTRUMENTS,
		.idProduct =	USB_PID_RIGKONTROL2
	पूर्ण,
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	USB_VID_NATIVEINSTRUMENTS,
		.idProduct =	USB_PID_RIGKONTROL3
	पूर्ण,
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	USB_VID_NATIVEINSTRUMENTS,
		.idProduct =	USB_PID_KORECONTROLLER
	पूर्ण,
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	USB_VID_NATIVEINSTRUMENTS,
		.idProduct =	USB_PID_KORECONTROLLER2
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_AK1
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_AUDIO8DJ
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_SESSIONIO
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_GUITARRIGMOBILE
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_AUDIO4DJ
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_AUDIO2DJ
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_TRAKTORKONTROLX1
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_TRAKTORKONTROLS4
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_TRAKTORAUDIO2
	पूर्ण,
	अणु
		.match_flags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =     USB_VID_NATIVEINSTRUMENTS,
		.idProduct =    USB_PID_MASCHINECONTROLLER
	पूर्ण,
	अणु /* terminator */ पूर्ण
पूर्ण;

अटल व्योम usb_ep1_command_reply_dispatch (काष्ठा urb* urb)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &urb->dev->dev;
	काष्ठा snd_usb_caiaqdev *cdev = urb->context;
	अचिन्हित अक्षर *buf = urb->transfer_buffer;

	अगर (urb->status || !cdev) अणु
		dev_warn(dev, "received EP1 urb->status = %i\n", urb->status);
		वापस;
	पूर्ण

	चयन(buf[0]) अणु
	हाल EP1_CMD_GET_DEVICE_INFO:
	 	स_नकल(&cdev->spec, buf+1, माप(काष्ठा caiaq_device_spec));
		cdev->spec.fw_version = le16_to_cpu(cdev->spec.fw_version);
		dev_dbg(dev, "device spec (firmware %d): audio: %d in, %d out, "
			"MIDI: %d in, %d out, data alignment %d\n",
			cdev->spec.fw_version,
			cdev->spec.num_analog_audio_in,
			cdev->spec.num_analog_audio_out,
			cdev->spec.num_midi_in,
			cdev->spec.num_midi_out,
			cdev->spec.data_alignment);

		cdev->spec_received++;
		wake_up(&cdev->ep1_रुको_queue);
		अवरोध;
	हाल EP1_CMD_AUDIO_PARAMS:
		cdev->audio_parm_answer = buf[1];
		wake_up(&cdev->ep1_रुको_queue);
		अवरोध;
	हाल EP1_CMD_MIDI_READ:
		snd_usb_caiaq_midi_handle_input(cdev, buf[1], buf + 3, buf[2]);
		अवरोध;
	हाल EP1_CMD_READ_IO:
		अगर (cdev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO8DJ)) अणु
			अगर (urb->actual_length > माप(cdev->control_state))
				urb->actual_length = माप(cdev->control_state);
			स_नकल(cdev->control_state, buf + 1, urb->actual_length);
			wake_up(&cdev->ep1_रुको_queue);
			अवरोध;
		पूर्ण
#अगर_घोषित CONFIG_SND_USB_CAIAQ_INPUT
		fallthrough;
	हाल EP1_CMD_READ_ERP:
	हाल EP1_CMD_READ_ANALOG:
		snd_usb_caiaq_input_dispatch(cdev, buf, urb->actual_length);
#पूर्ण_अगर
		अवरोध;
	पूर्ण

	cdev->ep1_in_urb.actual_length = 0;
	ret = usb_submit_urb(&cdev->ep1_in_urb, GFP_ATOMIC);
	अगर (ret < 0)
		dev_err(dev, "unable to submit urb. OOM!?\n");
पूर्ण

पूर्णांक snd_usb_caiaq_send_command(काष्ठा snd_usb_caiaqdev *cdev,
			       अचिन्हित अक्षर command,
			       स्थिर अचिन्हित अक्षर *buffer,
			       पूर्णांक len)
अणु
	पूर्णांक actual_len;
	काष्ठा usb_device *usb_dev = cdev->chip.dev;

	अगर (!usb_dev)
		वापस -EIO;

	अगर (len > EP1_बफ_मानE - 1)
		len = EP1_बफ_मानE - 1;

	अगर (buffer && len > 0)
		स_नकल(cdev->ep1_out_buf+1, buffer, len);

	cdev->ep1_out_buf[0] = command;
	वापस usb_bulk_msg(usb_dev, usb_sndbulkpipe(usb_dev, 1),
			   cdev->ep1_out_buf, len+1, &actual_len, 200);
पूर्ण

पूर्णांक snd_usb_caiaq_send_command_bank(काष्ठा snd_usb_caiaqdev *cdev,
			       अचिन्हित अक्षर command,
			       अचिन्हित अक्षर bank,
			       स्थिर अचिन्हित अक्षर *buffer,
			       पूर्णांक len)
अणु
	पूर्णांक actual_len;
	काष्ठा usb_device *usb_dev = cdev->chip.dev;

	अगर (!usb_dev)
		वापस -EIO;

	अगर (len > EP1_बफ_मानE - 2)
		len = EP1_बफ_मानE - 2;

	अगर (buffer && len > 0)
		स_नकल(cdev->ep1_out_buf+2, buffer, len);

	cdev->ep1_out_buf[0] = command;
	cdev->ep1_out_buf[1] = bank;

	वापस usb_bulk_msg(usb_dev, usb_sndbulkpipe(usb_dev, 1),
			   cdev->ep1_out_buf, len+2, &actual_len, 200);
पूर्ण

पूर्णांक snd_usb_caiaq_set_audio_params (काष्ठा snd_usb_caiaqdev *cdev,
		   		    पूर्णांक rate, पूर्णांक depth, पूर्णांक bpp)
अणु
	पूर्णांक ret;
	अक्षर पंचांगp[5];
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	चयन (rate) अणु
	हाल 44100:	पंचांगp[0] = SAMPLERATE_44100;   अवरोध;
	हाल 48000:	पंचांगp[0] = SAMPLERATE_48000;   अवरोध;
	हाल 88200:	पंचांगp[0] = SAMPLERATE_88200;   अवरोध;
	हाल 96000:	पंचांगp[0] = SAMPLERATE_96000;   अवरोध;
	हाल 192000:	पंचांगp[0] = SAMPLERATE_192000;  अवरोध;
	शेष:	वापस -EINVAL;
	पूर्ण

	चयन (depth) अणु
	हाल 16:	पंचांगp[1] = DEPTH_16;   अवरोध;
	हाल 24:	पंचांगp[1] = DEPTH_24;   अवरोध;
	शेष:	वापस -EINVAL;
	पूर्ण

	पंचांगp[2] = bpp & 0xff;
	पंचांगp[3] = bpp >> 8;
	पंचांगp[4] = 1; /* packets per microframe */

	dev_dbg(dev, "setting audio params: %d Hz, %d bits, %d bpp\n",
		rate, depth, bpp);

	cdev->audio_parm_answer = -1;
	ret = snd_usb_caiaq_send_command(cdev, EP1_CMD_AUDIO_PARAMS,
					 पंचांगp, माप(पंचांगp));

	अगर (ret)
		वापस ret;

	अगर (!रुको_event_समयout(cdev->ep1_रुको_queue,
	    cdev->audio_parm_answer >= 0, HZ))
		वापस -EPIPE;

	अगर (cdev->audio_parm_answer != 1)
		dev_dbg(dev, "unable to set the device's audio params\n");
	अन्यथा
		cdev->bpp = bpp;

	वापस cdev->audio_parm_answer == 1 ? 0 : -EINVAL;
पूर्ण

पूर्णांक snd_usb_caiaq_set_स्वतः_msg(काष्ठा snd_usb_caiaqdev *cdev,
			       पूर्णांक digital, पूर्णांक analog, पूर्णांक erp)
अणु
	अक्षर पंचांगp[3] = अणु digital, analog, erp पूर्ण;
	वापस snd_usb_caiaq_send_command(cdev, EP1_CMD_AUTO_MSG,
					  पंचांगp, माप(पंचांगp));
पूर्ण

अटल व्योम setup_card(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	पूर्णांक ret;
	अक्षर val[4];
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	/* device-specअगरic startup specials */
	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL2):
		/* RigKontrol2 - display centered dash ('-') */
		val[0] = 0x00;
		val[1] = 0x00;
		val[2] = 0x01;
		snd_usb_caiaq_send_command(cdev, EP1_CMD_WRITE_IO, val, 3);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL3):
		/* RigKontrol2 - display two centered dashes ('--') */
		val[0] = 0x00;
		val[1] = 0x40;
		val[2] = 0x40;
		val[3] = 0x00;
		snd_usb_caiaq_send_command(cdev, EP1_CMD_WRITE_IO, val, 4);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AK1):
		/* Audio Kontrol 1 - make USB-LED stop blinking */
		val[0] = 0x00;
		snd_usb_caiaq_send_command(cdev, EP1_CMD_WRITE_IO, val, 1);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO8DJ):
		/* Audio 8 DJ - trigger पढ़ो of current settings */
		cdev->control_state[0] = 0xff;
		snd_usb_caiaq_set_स्वतः_msg(cdev, 1, 0, 0);
		snd_usb_caiaq_send_command(cdev, EP1_CMD_READ_IO, शून्य, 0);

		अगर (!रुको_event_समयout(cdev->ep1_रुको_queue,
					cdev->control_state[0] != 0xff, HZ))
			वापस;

		/* fix up some शेषs */
		अगर ((cdev->control_state[1] != 2) ||
		    (cdev->control_state[2] != 3) ||
		    (cdev->control_state[4] != 2)) अणु
			cdev->control_state[1] = 2;
			cdev->control_state[2] = 3;
			cdev->control_state[4] = 2;
			snd_usb_caiaq_send_command(cdev,
				EP1_CMD_WRITE_IO, cdev->control_state, 6);
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (cdev->spec.num_analog_audio_out +
	    cdev->spec.num_analog_audio_in +
	    cdev->spec.num_digital_audio_out +
	    cdev->spec.num_digital_audio_in > 0) अणु
		ret = snd_usb_caiaq_audio_init(cdev);
		अगर (ret < 0)
			dev_err(dev, "Unable to set up audio system (ret=%d)\n", ret);
	पूर्ण

	अगर (cdev->spec.num_midi_in +
	    cdev->spec.num_midi_out > 0) अणु
		ret = snd_usb_caiaq_midi_init(cdev);
		अगर (ret < 0)
			dev_err(dev, "Unable to set up MIDI system (ret=%d)\n", ret);
	पूर्ण

#अगर_घोषित CONFIG_SND_USB_CAIAQ_INPUT
	ret = snd_usb_caiaq_input_init(cdev);
	अगर (ret < 0)
		dev_err(dev, "Unable to set up input system (ret=%d)\n", ret);
#पूर्ण_अगर

	/* finally, रेजिस्टर the card and all its sub-instances */
	ret = snd_card_रेजिस्टर(cdev->chip.card);
	अगर (ret < 0) अणु
		dev_err(dev, "snd_card_register() returned %d\n", ret);
		snd_card_मुक्त(cdev->chip.card);
	पूर्ण

	ret = snd_usb_caiaq_control_init(cdev);
	अगर (ret < 0)
		dev_err(dev, "Unable to set up control system (ret=%d)\n", ret);
पूर्ण

अटल पूर्णांक create_card(काष्ठा usb_device *usb_dev,
		       काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       काष्ठा snd_card **cardp)
अणु
	पूर्णांक devnum;
	पूर्णांक err;
	काष्ठा snd_card *card;
	काष्ठा snd_usb_caiaqdev *cdev;

	क्रम (devnum = 0; devnum < SNDRV_CARDS; devnum++)
		अगर (enable[devnum])
			अवरोध;

	अगर (devnum >= SNDRV_CARDS)
		वापस -ENODEV;

	err = snd_card_new(&पूर्णांकf->dev,
			   index[devnum], id[devnum], THIS_MODULE,
			   माप(काष्ठा snd_usb_caiaqdev), &card);
	अगर (err < 0)
		वापस err;

	cdev = caiaqdev(card);
	cdev->chip.dev = usb_dev;
	cdev->chip.card = card;
	cdev->chip.usb_id = USB_ID(le16_to_cpu(usb_dev->descriptor.idVenकरोr),
				  le16_to_cpu(usb_dev->descriptor.idProduct));
	spin_lock_init(&cdev->spinlock);

	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक init_card(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	अक्षर *c, usbpath[32];
	काष्ठा usb_device *usb_dev = cdev->chip.dev;
	काष्ठा snd_card *card = cdev->chip.card;
	काष्ठा device *dev = caiaqdev_to_dev(cdev);
	पूर्णांक err, len;

	अगर (usb_set_पूर्णांकerface(usb_dev, 0, 1) != 0) अणु
		dev_err(dev, "can't set alt interface.\n");
		वापस -EIO;
	पूर्ण

	usb_init_urb(&cdev->ep1_in_urb);
	usb_init_urb(&cdev->midi_out_urb);

	usb_fill_bulk_urb(&cdev->ep1_in_urb, usb_dev,
			  usb_rcvbulkpipe(usb_dev, 0x1),
			  cdev->ep1_in_buf, EP1_बफ_मानE,
			  usb_ep1_command_reply_dispatch, cdev);

	usb_fill_bulk_urb(&cdev->midi_out_urb, usb_dev,
			  usb_sndbulkpipe(usb_dev, 0x1),
			  cdev->midi_out_buf, EP1_बफ_मानE,
			  snd_usb_caiaq_midi_output_करोne, cdev);

	/* sanity checks of EPs beक्रमe actually submitting */
	अगर (usb_urb_ep_type_check(&cdev->ep1_in_urb) ||
	    usb_urb_ep_type_check(&cdev->midi_out_urb)) अणु
		dev_err(dev, "invalid EPs\n");
		वापस -EINVAL;
	पूर्ण

	init_रुकोqueue_head(&cdev->ep1_रुको_queue);
	init_रुकोqueue_head(&cdev->prepare_रुको_queue);

	अगर (usb_submit_urb(&cdev->ep1_in_urb, GFP_KERNEL) != 0)
		वापस -EIO;

	err = snd_usb_caiaq_send_command(cdev, EP1_CMD_GET_DEVICE_INFO, शून्य, 0);
	अगर (err)
		जाओ err_समाप्त_urb;

	अगर (!रुको_event_समयout(cdev->ep1_रुको_queue, cdev->spec_received, HZ)) अणु
		err = -ENODEV;
		जाओ err_समाप्त_urb;
	पूर्ण

	usb_string(usb_dev, usb_dev->descriptor.iManufacturer,
		   cdev->venकरोr_name, CAIAQ_USB_STR_LEN);

	usb_string(usb_dev, usb_dev->descriptor.iProduct,
		   cdev->product_name, CAIAQ_USB_STR_LEN);

	strscpy(card->driver, MODNAME, माप(card->driver));
	strscpy(card->लघुname, cdev->product_name, माप(card->लघुname));
	strscpy(card->mixername, cdev->product_name, माप(card->mixername));

	/* अगर the id was not passed as module option, fill it with a लघुened
	 * version of the product string which करोes not contain any
	 * whitespaces */

	अगर (*card->id == '\0') अणु
		अक्षर id[माप(card->id)];

		स_रखो(id, 0, माप(id));

		क्रम (c = card->लघुname, len = 0;
			*c && len < माप(card->id); c++)
			अगर (*c != ' ')
				id[len++] = *c;

		snd_card_set_id(card, id);
	पूर्ण

	usb_make_path(usb_dev, usbpath, माप(usbpath));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname), "%s %s (%s)",
		       cdev->venकरोr_name, cdev->product_name, usbpath);

	setup_card(cdev);
	वापस 0;

 err_समाप्त_urb:
	usb_समाप्त_urb(&cdev->ep1_in_urb);
	वापस err;
पूर्ण

अटल पूर्णांक snd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा snd_card *card = शून्य;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	ret = create_card(usb_dev, पूर्णांकf, &card);

	अगर (ret < 0)
		वापस ret;

	usb_set_पूर्णांकfdata(पूर्णांकf, card);
	ret = init_card(caiaqdev(card));
	अगर (ret < 0) अणु
		dev_err(&usb_dev->dev, "unable to init card! (ret=%d)\n", ret);
		snd_card_मुक्त(card);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा snd_card *card = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा device *dev = पूर्णांकf->usb_dev;
	काष्ठा snd_usb_caiaqdev *cdev;

	अगर (!card)
		वापस;

	cdev = caiaqdev(card);
	dev_dbg(dev, "%s(%p)\n", __func__, पूर्णांकf);

	snd_card_disconnect(card);

#अगर_घोषित CONFIG_SND_USB_CAIAQ_INPUT
	snd_usb_caiaq_input_मुक्त(cdev);
#पूर्ण_अगर
	snd_usb_caiaq_audio_मुक्त(cdev);

	usb_समाप्त_urb(&cdev->ep1_in_urb);
	usb_समाप्त_urb(&cdev->midi_out_urb);

	snd_card_मुक्त(card);
	usb_reset_device(पूर्णांकerface_to_usbdev(पूर्णांकf));
पूर्ण


MODULE_DEVICE_TABLE(usb, snd_usb_id_table);
अटल काष्ठा usb_driver snd_usb_driver = अणु
	.name 		= MODNAME,
	.probe 		= snd_probe,
	.disconnect	= snd_disconnect,
	.id_table 	= snd_usb_id_table,
पूर्ण;

module_usb_driver(snd_usb_driver);

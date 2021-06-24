<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Behringer BCD2000 driver
 *
 *   Copyright (C) 2014 Mario Kicherer (dev@kicherer.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/rawmidi.h>

#घोषणा PREFIX "snd-bcd2000: "
#घोषणा बफ_मानE 64

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x1397, 0x00bd) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर device_cmd_prefix[] = अणु0x03, 0x00पूर्ण;

अटल स्थिर अचिन्हित अक्षर bcd2000_init_sequence[] = अणु
	0x07, 0x00, 0x00, 0x00, 0x78, 0x48, 0x1c, 0x81,
	0xc4, 0x00, 0x00, 0x00, 0x5e, 0x53, 0x4a, 0xf7,
	0x18, 0xfa, 0x11, 0xff, 0x6c, 0xf3, 0x90, 0xff,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x18, 0xfa, 0x11, 0xff, 0x14, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf2, 0x34, 0x4a, 0xf7,
	0x18, 0xfa, 0x11, 0xff
पूर्ण;

काष्ठा bcd2000 अणु
	काष्ठा usb_device *dev;
	काष्ठा snd_card *card;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक card_index;

	पूर्णांक midi_out_active;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *midi_receive_substream;
	काष्ठा snd_rawmidi_substream *midi_out_substream;

	अचिन्हित अक्षर midi_in_buf[बफ_मानE];
	अचिन्हित अक्षर midi_out_buf[बफ_मानE];

	काष्ठा urb *midi_out_urb;
	काष्ठा urb *midi_in_urb;

	काष्ठा usb_anchor anchor;
पूर्ण;

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;

अटल DEFINE_MUTEX(devices_mutex);
अटल DECLARE_BITMAP(devices_used, SNDRV_CARDS);
अटल काष्ठा usb_driver bcd2000_driver;

#अगर_घोषित CONFIG_SND_DEBUG
अटल व्योम bcd2000_dump_buffer(स्थिर अक्षर *prefix, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	prपूर्णांक_hex_dump(KERN_DEBUG, prefix,
			DUMP_PREFIX_NONE, 16, 1,
			buf, len, false);
पूर्ण
#अन्यथा
अटल व्योम bcd2000_dump_buffer(स्थिर अक्षर *prefix, स्थिर अक्षर *buf, पूर्णांक len) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक bcd2000_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक bcd2000_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

/* (de)रेजिस्टर midi substream from client */
अटल व्योम bcd2000_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream,
						पूर्णांक up)
अणु
	काष्ठा bcd2000 *bcd2k = substream->rmidi->निजी_data;
	bcd2k->midi_receive_substream = up ? substream : शून्य;
पूर्ण

अटल व्योम bcd2000_midi_handle_input(काष्ठा bcd2000 *bcd2k,
				स्थिर अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buf_len)
अणु
	अचिन्हित पूर्णांक payload_length, tocopy;
	काष्ठा snd_rawmidi_substream *midi_receive_substream;

	midi_receive_substream = READ_ONCE(bcd2k->midi_receive_substream);
	अगर (!midi_receive_substream)
		वापस;

	bcd2000_dump_buffer(PREFIX "received from device: ", buf, buf_len);

	अगर (buf_len < 2)
		वापस;

	payload_length = buf[0];

	/* ignore packets without payload */
	अगर (payload_length == 0)
		वापस;

	tocopy = min(payload_length, buf_len-1);

	bcd2000_dump_buffer(PREFIX "sending to userspace: ",
					&buf[1], tocopy);

	snd_rawmidi_receive(midi_receive_substream,
					&buf[1], tocopy);
पूर्ण

अटल व्योम bcd2000_midi_send(काष्ठा bcd2000 *bcd2k)
अणु
	पूर्णांक len, ret;
	काष्ठा snd_rawmidi_substream *midi_out_substream;

	BUILD_BUG_ON(माप(device_cmd_prefix) >= बफ_मानE);

	midi_out_substream = READ_ONCE(bcd2k->midi_out_substream);
	अगर (!midi_out_substream)
		वापस;

	/* copy command prefix bytes */
	स_नकल(bcd2k->midi_out_buf, device_cmd_prefix,
		माप(device_cmd_prefix));

	/*
	 * get MIDI packet and leave space क्रम command prefix
	 * and payload length
	 */
	len = snd_rawmidi_transmit(midi_out_substream,
				bcd2k->midi_out_buf + 3, बफ_मानE - 3);

	अगर (len < 0)
		dev_err(&bcd2k->dev->dev, "%s: snd_rawmidi_transmit error %d\n",
				__func__, len);

	अगर (len <= 0)
		वापस;

	/* set payload length */
	bcd2k->midi_out_buf[2] = len;
	bcd2k->midi_out_urb->transfer_buffer_length = बफ_मानE;

	bcd2000_dump_buffer(PREFIX "sending to device: ",
			bcd2k->midi_out_buf, len+3);

	/* send packet to the BCD2000 */
	ret = usb_submit_urb(bcd2k->midi_out_urb, GFP_ATOMIC);
	अगर (ret < 0)
		dev_err(&bcd2k->dev->dev, PREFIX
			"%s (%p): usb_submit_urb() failed, ret=%d, len=%d\n",
			__func__, midi_out_substream, ret, len);
	अन्यथा
		bcd2k->midi_out_active = 1;
पूर्ण

अटल पूर्णांक bcd2000_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक bcd2000_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा bcd2000 *bcd2k = substream->rmidi->निजी_data;

	अगर (bcd2k->midi_out_active) अणु
		usb_समाप्त_urb(bcd2k->midi_out_urb);
		bcd2k->midi_out_active = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* (de)रेजिस्टर midi substream from client */
अटल व्योम bcd2000_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream,
						पूर्णांक up)
अणु
	काष्ठा bcd2000 *bcd2k = substream->rmidi->निजी_data;

	अगर (up) अणु
		bcd2k->midi_out_substream = substream;
		/* check अगर there is data userspace wants to send */
		अगर (!bcd2k->midi_out_active)
			bcd2000_midi_send(bcd2k);
	पूर्ण अन्यथा अणु
		bcd2k->midi_out_substream = शून्य;
	पूर्ण
पूर्ण

अटल व्योम bcd2000_output_complete(काष्ठा urb *urb)
अणु
	काष्ठा bcd2000 *bcd2k = urb->context;

	bcd2k->midi_out_active = 0;

	अगर (urb->status)
		dev_warn(&urb->dev->dev,
			PREFIX "output urb->status: %d\n", urb->status);

	अगर (urb->status == -ESHUTDOWN)
		वापस;

	/* check अगर there is more data userspace wants to send */
	bcd2000_midi_send(bcd2k);
पूर्ण

अटल व्योम bcd2000_input_complete(काष्ठा urb *urb)
अणु
	पूर्णांक ret;
	काष्ठा bcd2000 *bcd2k = urb->context;

	अगर (urb->status)
		dev_warn(&urb->dev->dev,
			PREFIX "input urb->status: %i\n", urb->status);

	अगर (!bcd2k || urb->status == -ESHUTDOWN)
		वापस;

	अगर (urb->actual_length > 0)
		bcd2000_midi_handle_input(bcd2k, urb->transfer_buffer,
					urb->actual_length);

	/* वापस URB to device */
	ret = usb_submit_urb(bcd2k->midi_in_urb, GFP_ATOMIC);
	अगर (ret < 0)
		dev_err(&bcd2k->dev->dev, PREFIX
			"%s: usb_submit_urb() failed, ret=%d\n",
			__func__, ret);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops bcd2000_midi_output = अणु
	.खोलो =    bcd2000_midi_output_खोलो,
	.बंद =   bcd2000_midi_output_बंद,
	.trigger = bcd2000_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops bcd2000_midi_input = अणु
	.खोलो =    bcd2000_midi_input_खोलो,
	.बंद =   bcd2000_midi_input_बंद,
	.trigger = bcd2000_midi_input_trigger,
पूर्ण;

अटल व्योम bcd2000_init_device(काष्ठा bcd2000 *bcd2k)
अणु
	पूर्णांक ret;

	init_usb_anchor(&bcd2k->anchor);
	usb_anchor_urb(bcd2k->midi_out_urb, &bcd2k->anchor);
	usb_anchor_urb(bcd2k->midi_in_urb, &bcd2k->anchor);

	/* copy init sequence पूर्णांकo buffer */
	स_नकल(bcd2k->midi_out_buf, bcd2000_init_sequence, 52);
	bcd2k->midi_out_urb->transfer_buffer_length = 52;

	/* submit sequence */
	ret = usb_submit_urb(bcd2k->midi_out_urb, GFP_KERNEL);
	अगर (ret < 0)
		dev_err(&bcd2k->dev->dev, PREFIX
			"%s: usb_submit_urb() out failed, ret=%d: ",
			__func__, ret);
	अन्यथा
		bcd2k->midi_out_active = 1;

	/* pass URB to device to enable button and controller events */
	ret = usb_submit_urb(bcd2k->midi_in_urb, GFP_KERNEL);
	अगर (ret < 0)
		dev_err(&bcd2k->dev->dev, PREFIX
			"%s: usb_submit_urb() in failed, ret=%d: ",
			__func__, ret);

	/* ensure initialization is finished */
	usb_रुको_anchor_empty_समयout(&bcd2k->anchor, 1000);
पूर्ण

अटल पूर्णांक bcd2000_init_midi(काष्ठा bcd2000 *bcd2k)
अणु
	पूर्णांक ret;
	काष्ठा snd_rawmidi *rmidi;

	ret = snd_rawmidi_new(bcd2k->card, bcd2k->card->लघुname, 0,
					1, /* output */
					1, /* input */
					&rmidi);

	अगर (ret < 0)
		वापस ret;

	strscpy(rmidi->name, bcd2k->card->लघुname, माप(rmidi->name));

	rmidi->info_flags = SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = bcd2k;

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
					&bcd2000_midi_output);

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
					&bcd2000_midi_input);

	bcd2k->rmidi = rmidi;

	bcd2k->midi_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	bcd2k->midi_out_urb = usb_alloc_urb(0, GFP_KERNEL);

	अगर (!bcd2k->midi_in_urb || !bcd2k->midi_out_urb) अणु
		dev_err(&bcd2k->dev->dev, PREFIX "usb_alloc_urb failed\n");
		वापस -ENOMEM;
	पूर्ण

	usb_fill_पूर्णांक_urb(bcd2k->midi_in_urb, bcd2k->dev,
				usb_rcvपूर्णांकpipe(bcd2k->dev, 0x81),
				bcd2k->midi_in_buf, बफ_मानE,
				bcd2000_input_complete, bcd2k, 1);

	usb_fill_पूर्णांक_urb(bcd2k->midi_out_urb, bcd2k->dev,
				usb_sndपूर्णांकpipe(bcd2k->dev, 0x1),
				bcd2k->midi_out_buf, बफ_मानE,
				bcd2000_output_complete, bcd2k, 1);

	/* sanity checks of EPs beक्रमe actually submitting */
	अगर (usb_urb_ep_type_check(bcd2k->midi_in_urb) ||
	    usb_urb_ep_type_check(bcd2k->midi_out_urb)) अणु
		dev_err(&bcd2k->dev->dev, "invalid MIDI EP\n");
		वापस -EINVAL;
	पूर्ण

	bcd2000_init_device(bcd2k);

	वापस 0;
पूर्ण

अटल व्योम bcd2000_मुक्त_usb_related_resources(काष्ठा bcd2000 *bcd2k,
						काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	/* usb_समाप्त_urb not necessary, urb is पातed स्वतःmatically */

	usb_मुक्त_urb(bcd2k->midi_out_urb);
	usb_मुक्त_urb(bcd2k->midi_in_urb);

	अगर (bcd2k->पूर्णांकf) अणु
		usb_set_पूर्णांकfdata(bcd2k->पूर्णांकf, शून्य);
		bcd2k->पूर्णांकf = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bcd2000_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				स्थिर काष्ठा usb_device_id *usb_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा bcd2000 *bcd2k;
	अचिन्हित पूर्णांक card_index;
	अक्षर usb_path[32];
	पूर्णांक err;

	mutex_lock(&devices_mutex);

	क्रम (card_index = 0; card_index < SNDRV_CARDS; ++card_index)
		अगर (!test_bit(card_index, devices_used))
			अवरोध;

	अगर (card_index >= SNDRV_CARDS) अणु
		mutex_unlock(&devices_mutex);
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&पूर्णांकerface->dev, index[card_index], id[card_index],
			THIS_MODULE, माप(*bcd2k), &card);
	अगर (err < 0) अणु
		mutex_unlock(&devices_mutex);
		वापस err;
	पूर्ण

	bcd2k = card->निजी_data;
	bcd2k->dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	bcd2k->card = card;
	bcd2k->card_index = card_index;
	bcd2k->पूर्णांकf = पूर्णांकerface;

	snd_card_set_dev(card, &पूर्णांकerface->dev);

	म_नकलन(card->driver, "snd-bcd2000", माप(card->driver));
	म_नकलन(card->लघुname, "BCD2000", माप(card->लघुname));
	usb_make_path(bcd2k->dev, usb_path, माप(usb_path));
	snम_लिखो(bcd2k->card->दीर्घname, माप(bcd2k->card->दीर्घname),
		    "Behringer BCD2000 at %s",
			usb_path);

	err = bcd2000_init_midi(bcd2k);
	अगर (err < 0)
		जाओ probe_error;

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ probe_error;

	usb_set_पूर्णांकfdata(पूर्णांकerface, bcd2k);
	set_bit(card_index, devices_used);

	mutex_unlock(&devices_mutex);
	वापस 0;

probe_error:
	dev_info(&bcd2k->dev->dev, PREFIX "error during probing");
	bcd2000_मुक्त_usb_related_resources(bcd2k, पूर्णांकerface);
	snd_card_मुक्त(card);
	mutex_unlock(&devices_mutex);
	वापस err;
पूर्ण

अटल व्योम bcd2000_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा bcd2000 *bcd2k = usb_get_पूर्णांकfdata(पूर्णांकerface);

	अगर (!bcd2k)
		वापस;

	mutex_lock(&devices_mutex);

	/* make sure that userspace cannot create new requests */
	snd_card_disconnect(bcd2k->card);

	bcd2000_मुक्त_usb_related_resources(bcd2k, पूर्णांकerface);

	clear_bit(bcd2k->card_index, devices_used);

	snd_card_मुक्त_when_बंदd(bcd2k->card);

	mutex_unlock(&devices_mutex);
पूर्ण

अटल काष्ठा usb_driver bcd2000_driver = अणु
	.name =		"snd-bcd2000",
	.probe =	bcd2000_probe,
	.disconnect =	bcd2000_disconnect,
	.id_table =	id_table,
पूर्ण;

module_usb_driver(bcd2000_driver);

MODULE_DEVICE_TABLE(usb, id_table);
MODULE_AUTHOR("Mario Kicherer, dev@kicherer.org");
MODULE_DESCRIPTION("Behringer BCD2000 driver");
MODULE_LICENSE("GPL");

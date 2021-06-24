<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Generic MIDI synth driver क्रम ALSA sequencer
 *   Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 *                         Jaroslav Kysela <perex@perex.cz>
 */
 
/* 
Possible options क्रम midisynth module:
	- स्वतःmatic खोलोing of midi ports on first received event or subscription
	  (बंद will be perक्रमmed when client leaves)
*/


#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/seq_kernel.h>
#समावेश <sound/seq_device.h>
#समावेश <sound/seq_midi_event.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Frank van de Pol <fvdpol@coil.demon.nl>, Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Advanced Linux Sound Architecture sequencer MIDI synth.");
MODULE_LICENSE("GPL");
अटल पूर्णांक output_buffer_size = PAGE_SIZE;
module_param(output_buffer_size, पूर्णांक, 0644);
MODULE_PARM_DESC(output_buffer_size, "Output buffer size in bytes.");
अटल पूर्णांक input_buffer_size = PAGE_SIZE;
module_param(input_buffer_size, पूर्णांक, 0644);
MODULE_PARM_DESC(input_buffer_size, "Input buffer size in bytes.");

/* data क्रम this midi synth driver */
काष्ठा seq_midisynth अणु
	काष्ठा snd_card *card;
	पूर्णांक device;
	पूर्णांक subdevice;
	काष्ठा snd_rawmidi_file input_rfile;
	काष्ठा snd_rawmidi_file output_rfile;
	पूर्णांक seq_client;
	पूर्णांक seq_port;
	काष्ठा snd_midi_event *parser;
पूर्ण;

काष्ठा seq_midisynth_client अणु
	पूर्णांक seq_client;
	पूर्णांक num_ports;
	पूर्णांक ports_per_device[SNDRV_RAWMIDI_DEVICES];
 	काष्ठा seq_midisynth *ports[SNDRV_RAWMIDI_DEVICES];
पूर्ण;

अटल काष्ठा seq_midisynth_client *synths[SNDRV_CARDS];
अटल DEFINE_MUTEX(रेजिस्टर_mutex);

/* handle rawmidi input event (MIDI v1.0 stream) */
अटल व्योम snd_midi_input_event(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय;
	काष्ठा seq_midisynth *msynth;
	काष्ठा snd_seq_event ev;
	अक्षर buf[16], *pbuf;
	दीर्घ res;

	अगर (substream == शून्य)
		वापस;
	runसमय = substream->runसमय;
	msynth = runसमय->निजी_data;
	अगर (msynth == शून्य)
		वापस;
	स_रखो(&ev, 0, माप(ev));
	जबतक (runसमय->avail > 0) अणु
		res = snd_rawmidi_kernel_पढ़ो(substream, buf, माप(buf));
		अगर (res <= 0)
			जारी;
		अगर (msynth->parser == शून्य)
			जारी;
		pbuf = buf;
		जबतक (res-- > 0) अणु
			अगर (!snd_midi_event_encode_byte(msynth->parser,
							*pbuf++, &ev))
				जारी;
			ev.source.port = msynth->seq_port;
			ev.dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
			snd_seq_kernel_client_dispatch(msynth->seq_client, &ev, 1, 0);
			/* clear event and reset header */
			स_रखो(&ev, 0, माप(ev));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dump_midi(काष्ठा snd_rawmidi_substream *substream, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय;
	पूर्णांक पंचांगp;

	अगर (snd_BUG_ON(!substream || !buf))
		वापस -EINVAL;
	runसमय = substream->runसमय;
	अगर ((पंचांगp = runसमय->avail) < count) अणु
		अगर (prपूर्णांकk_ratelimit())
			pr_err("ALSA: seq_midi: MIDI output buffer overrun\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (snd_rawmidi_kernel_ग_लिखो(substream, buf, count) < count)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक event_process_midi(काष्ठा snd_seq_event *ev, पूर्णांक direct,
			      व्योम *निजी_data, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा seq_midisynth *msynth = निजी_data;
	अचिन्हित अक्षर msg[10];	/* buffer क्रम स्थिरructing midi messages */
	काष्ठा snd_rawmidi_substream *substream;
	पूर्णांक len;

	अगर (snd_BUG_ON(!msynth))
		वापस -EINVAL;
	substream = msynth->output_rfile.output;
	अगर (substream == शून्य)
		वापस -ENODEV;
	अगर (ev->type == SNDRV_SEQ_EVENT_SYSEX) अणु	/* special हाल, to save space */
		अगर ((ev->flags & SNDRV_SEQ_EVENT_LENGTH_MASK) != SNDRV_SEQ_EVENT_LENGTH_VARIABLE) अणु
			/* invalid event */
			pr_debug("ALSA: seq_midi: invalid sysex event flags = 0x%x\n", ev->flags);
			वापस 0;
		पूर्ण
		snd_seq_dump_var_event(ev, (snd_seq_dump_func_t)dump_midi, substream);
		snd_midi_event_reset_decode(msynth->parser);
	पूर्ण अन्यथा अणु
		अगर (msynth->parser == शून्य)
			वापस -EIO;
		len = snd_midi_event_decode(msynth->parser, msg, माप(msg), ev);
		अगर (len < 0)
			वापस 0;
		अगर (dump_midi(substream, msg, len) < 0)
			snd_midi_event_reset_decode(msynth->parser);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक snd_seq_midisynth_new(काष्ठा seq_midisynth *msynth,
				 काष्ठा snd_card *card,
				 पूर्णांक device,
				 पूर्णांक subdevice)
अणु
	अगर (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &msynth->parser) < 0)
		वापस -ENOMEM;
	msynth->card = card;
	msynth->device = device;
	msynth->subdevice = subdevice;
	वापस 0;
पूर्ण

/* खोलो associated midi device क्रम input */
अटल पूर्णांक midisynth_subscribe(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info)
अणु
	पूर्णांक err;
	काष्ठा seq_midisynth *msynth = निजी_data;
	काष्ठा snd_rawmidi_runसमय *runसमय;
	काष्ठा snd_rawmidi_params params;

	/* खोलो midi port */
	अगर ((err = snd_rawmidi_kernel_खोलो(msynth->card, msynth->device,
					   msynth->subdevice,
					   SNDRV_RAWMIDI_LFLG_INPUT,
					   &msynth->input_rfile)) < 0) अणु
		pr_debug("ALSA: seq_midi: midi input open failed!!!\n");
		वापस err;
	पूर्ण
	runसमय = msynth->input_rfile.input->runसमय;
	स_रखो(&params, 0, माप(params));
	params.avail_min = 1;
	params.buffer_size = input_buffer_size;
	अगर ((err = snd_rawmidi_input_params(msynth->input_rfile.input, &params)) < 0) अणु
		snd_rawmidi_kernel_release(&msynth->input_rfile);
		वापस err;
	पूर्ण
	snd_midi_event_reset_encode(msynth->parser);
	runसमय->event = snd_midi_input_event;
	runसमय->निजी_data = msynth;
	snd_rawmidi_kernel_पढ़ो(msynth->input_rfile.input, शून्य, 0);
	वापस 0;
पूर्ण

/* बंद associated midi device क्रम input */
अटल पूर्णांक midisynth_unsubscribe(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info)
अणु
	पूर्णांक err;
	काष्ठा seq_midisynth *msynth = निजी_data;

	अगर (snd_BUG_ON(!msynth->input_rfile.input))
		वापस -EINVAL;
	err = snd_rawmidi_kernel_release(&msynth->input_rfile);
	वापस err;
पूर्ण

/* खोलो associated midi device क्रम output */
अटल पूर्णांक midisynth_use(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info)
अणु
	पूर्णांक err;
	काष्ठा seq_midisynth *msynth = निजी_data;
	काष्ठा snd_rawmidi_params params;

	/* खोलो midi port */
	अगर ((err = snd_rawmidi_kernel_खोलो(msynth->card, msynth->device,
					   msynth->subdevice,
					   SNDRV_RAWMIDI_LFLG_OUTPUT,
					   &msynth->output_rfile)) < 0) अणु
		pr_debug("ALSA: seq_midi: midi output open failed!!!\n");
		वापस err;
	पूर्ण
	स_रखो(&params, 0, माप(params));
	params.avail_min = 1;
	params.buffer_size = output_buffer_size;
	params.no_active_sensing = 1;
	अगर ((err = snd_rawmidi_output_params(msynth->output_rfile.output, &params)) < 0) अणु
		snd_rawmidi_kernel_release(&msynth->output_rfile);
		वापस err;
	पूर्ण
	snd_midi_event_reset_decode(msynth->parser);
	वापस 0;
पूर्ण

/* बंद associated midi device क्रम output */
अटल पूर्णांक midisynth_unuse(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा seq_midisynth *msynth = निजी_data;

	अगर (snd_BUG_ON(!msynth->output_rfile.output))
		वापस -EINVAL;
	snd_rawmidi_drain_output(msynth->output_rfile.output);
	वापस snd_rawmidi_kernel_release(&msynth->output_rfile);
पूर्ण

/* delete given midi synth port */
अटल व्योम snd_seq_midisynth_delete(काष्ठा seq_midisynth *msynth)
अणु
	अगर (msynth == शून्य)
		वापस;

	अगर (msynth->seq_client > 0) अणु
		/* delete port */
		snd_seq_event_port_detach(msynth->seq_client, msynth->seq_port);
	पूर्ण

	snd_midi_event_मुक्त(msynth->parser);
पूर्ण

/* रेजिस्टर new midi synth port */
अटल पूर्णांक
snd_seq_midisynth_probe(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा seq_midisynth_client *client;
	काष्ठा seq_midisynth *msynth, *ms;
	काष्ठा snd_seq_port_info *port;
	काष्ठा snd_rawmidi_info *info;
	काष्ठा snd_rawmidi *rmidi = dev->निजी_data;
	पूर्णांक newclient = 0;
	अचिन्हित पूर्णांक p, ports;
	काष्ठा snd_seq_port_callback pcallbacks;
	काष्ठा snd_card *card = dev->card;
	पूर्णांक device = dev->device;
	अचिन्हित पूर्णांक input_count = 0, output_count = 0;

	अगर (snd_BUG_ON(!card || device < 0 || device >= SNDRV_RAWMIDI_DEVICES))
		वापस -EINVAL;
	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (! info)
		वापस -ENOMEM;
	info->device = device;
	info->stream = SNDRV_RAWMIDI_STREAM_OUTPUT;
	info->subdevice = 0;
	अगर (snd_rawmidi_info_select(card, info) >= 0)
		output_count = info->subdevices_count;
	info->stream = SNDRV_RAWMIDI_STREAM_INPUT;
	अगर (snd_rawmidi_info_select(card, info) >= 0) अणु
		input_count = info->subdevices_count;
	पूर्ण
	ports = output_count;
	अगर (ports < input_count)
		ports = input_count;
	अगर (ports == 0) अणु
		kमुक्त(info);
		वापस -ENODEV;
	पूर्ण
	अगर (ports > (256 / SNDRV_RAWMIDI_DEVICES))
		ports = 256 / SNDRV_RAWMIDI_DEVICES;

	mutex_lock(&रेजिस्टर_mutex);
	client = synths[card->number];
	अगर (client == शून्य) अणु
		newclient = 1;
		client = kzalloc(माप(*client), GFP_KERNEL);
		अगर (client == शून्य) अणु
			mutex_unlock(&रेजिस्टर_mutex);
			kमुक्त(info);
			वापस -ENOMEM;
		पूर्ण
		client->seq_client =
			snd_seq_create_kernel_client(
				card, 0, "%s", card->लघुname[0] ?
				(स्थिर अक्षर *)card->लघुname : "External MIDI");
		अगर (client->seq_client < 0) अणु
			kमुक्त(client);
			mutex_unlock(&रेजिस्टर_mutex);
			kमुक्त(info);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	msynth = kसुस्मृति(ports, माप(काष्ठा seq_midisynth), GFP_KERNEL);
	port = kदो_स्मृति(माप(*port), GFP_KERNEL);
	अगर (msynth == शून्य || port == शून्य)
		जाओ __nomem;

	क्रम (p = 0; p < ports; p++) अणु
		ms = &msynth[p];

		अगर (snd_seq_midisynth_new(ms, card, device, p) < 0)
			जाओ __nomem;

		/* declare port */
		स_रखो(port, 0, माप(*port));
		port->addr.client = client->seq_client;
		port->addr.port = device * (256 / SNDRV_RAWMIDI_DEVICES) + p;
		port->flags = SNDRV_SEQ_PORT_FLG_GIVEN_PORT;
		स_रखो(info, 0, माप(*info));
		info->device = device;
		अगर (p < output_count)
			info->stream = SNDRV_RAWMIDI_STREAM_OUTPUT;
		अन्यथा
			info->stream = SNDRV_RAWMIDI_STREAM_INPUT;
		info->subdevice = p;
		अगर (snd_rawmidi_info_select(card, info) >= 0)
			म_नकल(port->name, info->subname);
		अगर (! port->name[0]) अणु
			अगर (info->name[0]) अणु
				अगर (ports > 1)
					snम_लिखो(port->name, माप(port->name), "%s-%u", info->name, p);
				अन्यथा
					snम_लिखो(port->name, माप(port->name), "%s", info->name);
			पूर्ण अन्यथा अणु
				/* last resort */
				अगर (ports > 1)
					प्र_लिखो(port->name, "MIDI %d-%d-%u", card->number, device, p);
				अन्यथा
					प्र_लिखो(port->name, "MIDI %d-%d", card->number, device);
			पूर्ण
		पूर्ण
		अगर ((info->flags & SNDRV_RAWMIDI_INFO_OUTPUT) && p < output_count)
			port->capability |= SNDRV_SEQ_PORT_CAP_WRITE | SNDRV_SEQ_PORT_CAP_SYNC_WRITE | SNDRV_SEQ_PORT_CAP_SUBS_WRITE;
		अगर ((info->flags & SNDRV_RAWMIDI_INFO_INPUT) && p < input_count)
			port->capability |= SNDRV_SEQ_PORT_CAP_READ | SNDRV_SEQ_PORT_CAP_SYNC_READ | SNDRV_SEQ_PORT_CAP_SUBS_READ;
		अगर ((port->capability & (SNDRV_SEQ_PORT_CAP_WRITE|SNDRV_SEQ_PORT_CAP_READ)) == (SNDRV_SEQ_PORT_CAP_WRITE|SNDRV_SEQ_PORT_CAP_READ) &&
		    info->flags & SNDRV_RAWMIDI_INFO_DUPLEX)
			port->capability |= SNDRV_SEQ_PORT_CAP_DUPLEX;
		port->type = SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
			| SNDRV_SEQ_PORT_TYPE_HARDWARE
			| SNDRV_SEQ_PORT_TYPE_PORT;
		port->midi_channels = 16;
		स_रखो(&pcallbacks, 0, माप(pcallbacks));
		pcallbacks.owner = THIS_MODULE;
		pcallbacks.निजी_data = ms;
		pcallbacks.subscribe = midisynth_subscribe;
		pcallbacks.unsubscribe = midisynth_unsubscribe;
		pcallbacks.use = midisynth_use;
		pcallbacks.unuse = midisynth_unuse;
		pcallbacks.event_input = event_process_midi;
		port->kernel = &pcallbacks;
		अगर (rmidi->ops && rmidi->ops->get_port_info)
			rmidi->ops->get_port_info(rmidi, p, port);
		अगर (snd_seq_kernel_client_ctl(client->seq_client, SNDRV_SEQ_IOCTL_CREATE_PORT, port)<0)
			जाओ __nomem;
		ms->seq_client = client->seq_client;
		ms->seq_port = port->addr.port;
	पूर्ण
	client->ports_per_device[device] = ports;
	client->ports[device] = msynth;
	client->num_ports++;
	अगर (newclient)
		synths[card->number] = client;
	mutex_unlock(&रेजिस्टर_mutex);
	kमुक्त(info);
	kमुक्त(port);
	वापस 0;	/* success */

      __nomem:
	अगर (msynth != शून्य) अणु
	      	क्रम (p = 0; p < ports; p++)
	      		snd_seq_midisynth_delete(&msynth[p]);
		kमुक्त(msynth);
	पूर्ण
	अगर (newclient) अणु
		snd_seq_delete_kernel_client(client->seq_client);
		kमुक्त(client);
	पूर्ण
	kमुक्त(info);
	kमुक्त(port);
	mutex_unlock(&रेजिस्टर_mutex);
	वापस -ENOMEM;
पूर्ण

/* release midi synth port */
अटल पूर्णांक
snd_seq_midisynth_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा seq_midisynth_client *client;
	काष्ठा seq_midisynth *msynth;
	काष्ठा snd_card *card = dev->card;
	पूर्णांक device = dev->device, p, ports;
	
	mutex_lock(&रेजिस्टर_mutex);
	client = synths[card->number];
	अगर (client == शून्य || client->ports[device] == शून्य) अणु
		mutex_unlock(&रेजिस्टर_mutex);
		वापस -ENODEV;
	पूर्ण
	ports = client->ports_per_device[device];
	client->ports_per_device[device] = 0;
	msynth = client->ports[device];
	client->ports[device] = शून्य;
	क्रम (p = 0; p < ports; p++)
		snd_seq_midisynth_delete(&msynth[p]);
	kमुक्त(msynth);
	client->num_ports--;
	अगर (client->num_ports <= 0) अणु
		snd_seq_delete_kernel_client(client->seq_client);
		synths[card->number] = शून्य;
		kमुक्त(client);
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा snd_seq_driver seq_midisynth_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.probe = snd_seq_midisynth_probe,
		.हटाओ = snd_seq_midisynth_हटाओ,
	पूर्ण,
	.id = SNDRV_SEQ_DEV_ID_MIDISYNTH,
	.argsize = 0,
पूर्ण;

module_snd_seq_driver(seq_midisynth_driver);

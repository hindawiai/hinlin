<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Virtual Raw MIDI client on Sequencer
 *
 *  Copyright (c) 2000 by Takashi Iwai <tiwai@suse.de>,
 *                        Jaroslav Kysela <perex@perex.cz>
 */

/*
 * Virtual Raw MIDI client
 *
 * The भव rawmidi client is a sequencer client which associate
 * a rawmidi device file.  The created rawmidi device file can be
 * accessed as a normal raw midi, but its MIDI source and destination
 * are arbitrary.  For example, a user-client software synth connected
 * to this port can be used as a normal midi device as well.
 *
 * The भव rawmidi device accepts also multiple खोलोs.  Each file
 * has its own input buffer, so that no conflict would occur.  The drain
 * of input/output buffer acts only to the local buffer.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/minors.h>
#समावेश <sound/seq_kernel.h>
#समावेश <sound/seq_midi_event.h>
#समावेश <sound/seq_virmidi.h>

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("Virtual Raw MIDI client on Sequencer");
MODULE_LICENSE("GPL");

/*
 * initialize an event record
 */
अटल व्योम snd_virmidi_init_event(काष्ठा snd_virmidi *vmidi,
				   काष्ठा snd_seq_event *ev)
अणु
	स_रखो(ev, 0, माप(*ev));
	ev->source.port = vmidi->port;
	चयन (vmidi->seq_mode) अणु
	हाल SNDRV_VIRMIDI_SEQ_DISPATCH:
		ev->dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
		अवरोध;
	हाल SNDRV_VIRMIDI_SEQ_ATTACH:
		/* FIXME: source and destination are same - not good.. */
		ev->dest.client = vmidi->client;
		ev->dest.port = vmidi->port;
		अवरोध;
	पूर्ण
	ev->type = SNDRV_SEQ_EVENT_NONE;
पूर्ण

/*
 * decode input event and put to पढ़ो buffer of each खोलोed file
 */
अटल पूर्णांक snd_virmidi_dev_receive_event(काष्ठा snd_virmidi_dev *rdev,
					 काष्ठा snd_seq_event *ev,
					 bool atomic)
अणु
	काष्ठा snd_virmidi *vmidi;
	अचिन्हित अक्षर msg[4];
	पूर्णांक len;

	अगर (atomic)
		पढ़ो_lock(&rdev->filelist_lock);
	अन्यथा
		करोwn_पढ़ो(&rdev->filelist_sem);
	list_क्रम_each_entry(vmidi, &rdev->filelist, list) अणु
		अगर (!READ_ONCE(vmidi->trigger))
			जारी;
		अगर (ev->type == SNDRV_SEQ_EVENT_SYSEX) अणु
			अगर ((ev->flags & SNDRV_SEQ_EVENT_LENGTH_MASK) != SNDRV_SEQ_EVENT_LENGTH_VARIABLE)
				जारी;
			snd_seq_dump_var_event(ev, (snd_seq_dump_func_t)snd_rawmidi_receive, vmidi->substream);
			snd_midi_event_reset_decode(vmidi->parser);
		पूर्ण अन्यथा अणु
			len = snd_midi_event_decode(vmidi->parser, msg, माप(msg), ev);
			अगर (len > 0)
				snd_rawmidi_receive(vmidi->substream, msg, len);
		पूर्ण
	पूर्ण
	अगर (atomic)
		पढ़ो_unlock(&rdev->filelist_lock);
	अन्यथा
		up_पढ़ो(&rdev->filelist_sem);

	वापस 0;
पूर्ण

/*
 * event handler of virmidi port
 */
अटल पूर्णांक snd_virmidi_event_input(काष्ठा snd_seq_event *ev, पूर्णांक direct,
				   व्योम *निजी_data, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_virmidi_dev *rdev;

	rdev = निजी_data;
	अगर (!(rdev->flags & SNDRV_VIRMIDI_USE))
		वापस 0; /* ignored */
	वापस snd_virmidi_dev_receive_event(rdev, ev, atomic);
पूर्ण

/*
 * trigger rawmidi stream क्रम input
 */
अटल व्योम snd_virmidi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_virmidi *vmidi = substream->runसमय->निजी_data;

	WRITE_ONCE(vmidi->trigger, !!up);
पूर्ण

/* process rawmidi bytes and send events;
 * we need no lock here क्रम vmidi->event since it's handled only in this work
 */
अटल व्योम snd_vmidi_output_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_virmidi *vmidi;
	काष्ठा snd_rawmidi_substream *substream;
	अचिन्हित अक्षर input;
	पूर्णांक ret;

	vmidi = container_of(work, काष्ठा snd_virmidi, output_work);
	substream = vmidi->substream;

	/* discard the outमाला_दो in dispatch mode unless subscribed */
	अगर (vmidi->seq_mode == SNDRV_VIRMIDI_SEQ_DISPATCH &&
	    !(vmidi->rdev->flags & SNDRV_VIRMIDI_SUBSCRIBE)) अणु
		snd_rawmidi_proceed(substream);
		वापस;
	पूर्ण

	जबतक (READ_ONCE(vmidi->trigger)) अणु
		अगर (snd_rawmidi_transmit(substream, &input, 1) != 1)
			अवरोध;
		अगर (!snd_midi_event_encode_byte(vmidi->parser, input,
						&vmidi->event))
			जारी;
		अगर (vmidi->event.type != SNDRV_SEQ_EVENT_NONE) अणु
			ret = snd_seq_kernel_client_dispatch(vmidi->client,
							     &vmidi->event,
							     false, 0);
			vmidi->event.type = SNDRV_SEQ_EVENT_NONE;
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		/* rawmidi input might be huge, allow to have a अवरोध */
		cond_resched();
	पूर्ण
पूर्ण

/*
 * trigger rawmidi stream क्रम output
 */
अटल व्योम snd_virmidi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_virmidi *vmidi = substream->runसमय->निजी_data;

	WRITE_ONCE(vmidi->trigger, !!up);
	अगर (up)
		queue_work(प्रणाली_highpri_wq, &vmidi->output_work);
पूर्ण

/*
 * खोलो rawmidi handle क्रम input
 */
अटल पूर्णांक snd_virmidi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_virmidi_dev *rdev = substream->rmidi->निजी_data;
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_virmidi *vmidi;

	vmidi = kzalloc(माप(*vmidi), GFP_KERNEL);
	अगर (vmidi == शून्य)
		वापस -ENOMEM;
	vmidi->substream = substream;
	अगर (snd_midi_event_new(0, &vmidi->parser) < 0) अणु
		kमुक्त(vmidi);
		वापस -ENOMEM;
	पूर्ण
	vmidi->seq_mode = rdev->seq_mode;
	vmidi->client = rdev->client;
	vmidi->port = rdev->port;	
	runसमय->निजी_data = vmidi;
	करोwn_ग_लिखो(&rdev->filelist_sem);
	ग_लिखो_lock_irq(&rdev->filelist_lock);
	list_add_tail(&vmidi->list, &rdev->filelist);
	ग_लिखो_unlock_irq(&rdev->filelist_lock);
	up_ग_लिखो(&rdev->filelist_sem);
	vmidi->rdev = rdev;
	वापस 0;
पूर्ण

/*
 * खोलो rawmidi handle क्रम output
 */
अटल पूर्णांक snd_virmidi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_virmidi_dev *rdev = substream->rmidi->निजी_data;
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_virmidi *vmidi;

	vmidi = kzalloc(माप(*vmidi), GFP_KERNEL);
	अगर (vmidi == शून्य)
		वापस -ENOMEM;
	vmidi->substream = substream;
	अगर (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &vmidi->parser) < 0) अणु
		kमुक्त(vmidi);
		वापस -ENOMEM;
	पूर्ण
	vmidi->seq_mode = rdev->seq_mode;
	vmidi->client = rdev->client;
	vmidi->port = rdev->port;
	snd_virmidi_init_event(vmidi, &vmidi->event);
	vmidi->rdev = rdev;
	INIT_WORK(&vmidi->output_work, snd_vmidi_output_work);
	runसमय->निजी_data = vmidi;
	वापस 0;
पूर्ण

/*
 * बंद rawmidi handle क्रम input
 */
अटल पूर्णांक snd_virmidi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_virmidi_dev *rdev = substream->rmidi->निजी_data;
	काष्ठा snd_virmidi *vmidi = substream->runसमय->निजी_data;

	करोwn_ग_लिखो(&rdev->filelist_sem);
	ग_लिखो_lock_irq(&rdev->filelist_lock);
	list_del(&vmidi->list);
	ग_लिखो_unlock_irq(&rdev->filelist_lock);
	up_ग_लिखो(&rdev->filelist_sem);
	snd_midi_event_मुक्त(vmidi->parser);
	substream->runसमय->निजी_data = शून्य;
	kमुक्त(vmidi);
	वापस 0;
पूर्ण

/*
 * बंद rawmidi handle क्रम output
 */
अटल पूर्णांक snd_virmidi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_virmidi *vmidi = substream->runसमय->निजी_data;

	WRITE_ONCE(vmidi->trigger, false); /* to be sure */
	cancel_work_sync(&vmidi->output_work);
	snd_midi_event_मुक्त(vmidi->parser);
	substream->runसमय->निजी_data = शून्य;
	kमुक्त(vmidi);
	वापस 0;
पूर्ण

/*
 * subscribe callback - allow output to rawmidi device
 */
अटल पूर्णांक snd_virmidi_subscribe(व्योम *निजी_data,
				 काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_virmidi_dev *rdev;

	rdev = निजी_data;
	अगर (!try_module_get(rdev->card->module))
		वापस -EFAULT;
	rdev->flags |= SNDRV_VIRMIDI_SUBSCRIBE;
	वापस 0;
पूर्ण

/*
 * unsubscribe callback - disallow output to rawmidi device
 */
अटल पूर्णांक snd_virmidi_unsubscribe(व्योम *निजी_data,
				   काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_virmidi_dev *rdev;

	rdev = निजी_data;
	rdev->flags &= ~SNDRV_VIRMIDI_SUBSCRIBE;
	module_put(rdev->card->module);
	वापस 0;
पूर्ण


/*
 * use callback - allow input to rawmidi device
 */
अटल पूर्णांक snd_virmidi_use(व्योम *निजी_data,
			   काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_virmidi_dev *rdev;

	rdev = निजी_data;
	अगर (!try_module_get(rdev->card->module))
		वापस -EFAULT;
	rdev->flags |= SNDRV_VIRMIDI_USE;
	वापस 0;
पूर्ण

/*
 * unuse callback - disallow input to rawmidi device
 */
अटल पूर्णांक snd_virmidi_unuse(व्योम *निजी_data,
			     काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_virmidi_dev *rdev;

	rdev = निजी_data;
	rdev->flags &= ~SNDRV_VIRMIDI_USE;
	module_put(rdev->card->module);
	वापस 0;
पूर्ण


/*
 *  Register functions
 */

अटल स्थिर काष्ठा snd_rawmidi_ops snd_virmidi_input_ops = अणु
	.खोलो = snd_virmidi_input_खोलो,
	.बंद = snd_virmidi_input_बंद,
	.trigger = snd_virmidi_input_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_virmidi_output_ops = अणु
	.खोलो = snd_virmidi_output_खोलो,
	.बंद = snd_virmidi_output_बंद,
	.trigger = snd_virmidi_output_trigger,
पूर्ण;

/*
 * create a sequencer client and a port
 */
अटल पूर्णांक snd_virmidi_dev_attach_seq(काष्ठा snd_virmidi_dev *rdev)
अणु
	पूर्णांक client;
	काष्ठा snd_seq_port_callback pcallbacks;
	काष्ठा snd_seq_port_info *pinfo;
	पूर्णांक err;

	अगर (rdev->client >= 0)
		वापस 0;

	pinfo = kzalloc(माप(*pinfo), GFP_KERNEL);
	अगर (!pinfo) अणु
		err = -ENOMEM;
		जाओ __error;
	पूर्ण

	client = snd_seq_create_kernel_client(rdev->card, rdev->device,
					      "%s %d-%d", rdev->rmidi->name,
					      rdev->card->number,
					      rdev->device);
	अगर (client < 0) अणु
		err = client;
		जाओ __error;
	पूर्ण
	rdev->client = client;

	/* create a port */
	pinfo->addr.client = client;
	प्र_लिखो(pinfo->name, "VirMIDI %d-%d", rdev->card->number, rdev->device);
	/* set all capabilities */
	pinfo->capability |= SNDRV_SEQ_PORT_CAP_WRITE | SNDRV_SEQ_PORT_CAP_SYNC_WRITE | SNDRV_SEQ_PORT_CAP_SUBS_WRITE;
	pinfo->capability |= SNDRV_SEQ_PORT_CAP_READ | SNDRV_SEQ_PORT_CAP_SYNC_READ | SNDRV_SEQ_PORT_CAP_SUBS_READ;
	pinfo->capability |= SNDRV_SEQ_PORT_CAP_DUPLEX;
	pinfo->type = SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
		| SNDRV_SEQ_PORT_TYPE_SOFTWARE
		| SNDRV_SEQ_PORT_TYPE_PORT;
	pinfo->midi_channels = 16;
	स_रखो(&pcallbacks, 0, माप(pcallbacks));
	pcallbacks.owner = THIS_MODULE;
	pcallbacks.निजी_data = rdev;
	pcallbacks.subscribe = snd_virmidi_subscribe;
	pcallbacks.unsubscribe = snd_virmidi_unsubscribe;
	pcallbacks.use = snd_virmidi_use;
	pcallbacks.unuse = snd_virmidi_unuse;
	pcallbacks.event_input = snd_virmidi_event_input;
	pinfo->kernel = &pcallbacks;
	err = snd_seq_kernel_client_ctl(client, SNDRV_SEQ_IOCTL_CREATE_PORT, pinfo);
	अगर (err < 0) अणु
		snd_seq_delete_kernel_client(client);
		rdev->client = -1;
		जाओ __error;
	पूर्ण

	rdev->port = pinfo->addr.port;
	err = 0; /* success */

 __error:
	kमुक्त(pinfo);
	वापस err;
पूर्ण


/*
 * release the sequencer client
 */
अटल व्योम snd_virmidi_dev_detach_seq(काष्ठा snd_virmidi_dev *rdev)
अणु
	अगर (rdev->client >= 0) अणु
		snd_seq_delete_kernel_client(rdev->client);
		rdev->client = -1;
	पूर्ण
पूर्ण

/*
 * रेजिस्टर the device
 */
अटल पूर्णांक snd_virmidi_dev_रेजिस्टर(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_virmidi_dev *rdev = rmidi->निजी_data;
	पूर्णांक err;

	चयन (rdev->seq_mode) अणु
	हाल SNDRV_VIRMIDI_SEQ_DISPATCH:
		err = snd_virmidi_dev_attach_seq(rdev);
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल SNDRV_VIRMIDI_SEQ_ATTACH:
		अगर (rdev->client == 0)
			वापस -EINVAL;
		/* should check presence of port more strictly.. */
		अवरोध;
	शेष:
		pr_err("ALSA: seq_virmidi: seq_mode is not set: %d\n", rdev->seq_mode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * unरेजिस्टर the device
 */
अटल पूर्णांक snd_virmidi_dev_unरेजिस्टर(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_virmidi_dev *rdev = rmidi->निजी_data;

	अगर (rdev->seq_mode == SNDRV_VIRMIDI_SEQ_DISPATCH)
		snd_virmidi_dev_detach_seq(rdev);
	वापस 0;
पूर्ण

/*
 *
 */
अटल स्थिर काष्ठा snd_rawmidi_global_ops snd_virmidi_global_ops = अणु
	.dev_रेजिस्टर = snd_virmidi_dev_रेजिस्टर,
	.dev_unरेजिस्टर = snd_virmidi_dev_unरेजिस्टर,
पूर्ण;

/*
 * मुक्त device
 */
अटल व्योम snd_virmidi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_virmidi_dev *rdev = rmidi->निजी_data;
	kमुक्त(rdev);
पूर्ण

/*
 * create a new device
 *
 */
/* exported */
पूर्णांक snd_virmidi_new(काष्ठा snd_card *card, पूर्णांक device, काष्ठा snd_rawmidi **rrmidi)
अणु
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_virmidi_dev *rdev;
	पूर्णांक err;
	
	*rrmidi = शून्य;
	अगर ((err = snd_rawmidi_new(card, "VirMidi", device,
				   16,	/* may be configurable */
				   16,	/* may be configurable */
				   &rmidi)) < 0)
		वापस err;
	म_नकल(rmidi->name, rmidi->id);
	rdev = kzalloc(माप(*rdev), GFP_KERNEL);
	अगर (rdev == शून्य) अणु
		snd_device_मुक्त(card, rmidi);
		वापस -ENOMEM;
	पूर्ण
	rdev->card = card;
	rdev->rmidi = rmidi;
	rdev->device = device;
	rdev->client = -1;
	init_rwsem(&rdev->filelist_sem);
	rwlock_init(&rdev->filelist_lock);
	INIT_LIST_HEAD(&rdev->filelist);
	rdev->seq_mode = SNDRV_VIRMIDI_SEQ_DISPATCH;
	rmidi->निजी_data = rdev;
	rmidi->निजी_मुक्त = snd_virmidi_मुक्त;
	rmidi->ops = &snd_virmidi_global_ops;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_virmidi_input_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_virmidi_output_ops);
	rmidi->info_flags = SNDRV_RAWMIDI_INFO_INPUT |
			    SNDRV_RAWMIDI_INFO_OUTPUT |
			    SNDRV_RAWMIDI_INFO_DUPLEX;
	*rrmidi = rmidi;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_virmidi_new);

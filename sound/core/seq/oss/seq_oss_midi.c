<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * MIDI device handlers
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <sound/asoundef.h>
#समावेश "seq_oss_midi.h"
#समावेश "seq_oss_readq.h"
#समावेश "seq_oss_timer.h"
#समावेश "seq_oss_event.h"
#समावेश <sound/seq_midi_event.h>
#समावेश "../seq_lock.h"
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/nospec.h>


/*
 * स्थिरants
 */
#घोषणा SNDRV_SEQ_OSS_MAX_MIDI_NAME	30

/*
 * definition of midi device record
 */
काष्ठा seq_oss_midi अणु
	पूर्णांक seq_device;		/* device number */
	पूर्णांक client;		/* sequencer client number */
	पूर्णांक port;		/* sequencer port number */
	अचिन्हित पूर्णांक flags;	/* port capability */
	पूर्णांक खोलोed;		/* flag क्रम खोलोing */
	अचिन्हित अक्षर name[SNDRV_SEQ_OSS_MAX_MIDI_NAME];
	काष्ठा snd_midi_event *coder;	/* MIDI event coder */
	काष्ठा seq_oss_devinfo *devinfo;	/* asचिन्हित OSSseq device */
	snd_use_lock_t use_lock;
पूर्ण;


/*
 * midi device table
 */
अटल पूर्णांक max_midi_devs;
अटल काष्ठा seq_oss_midi *midi_devs[SNDRV_SEQ_OSS_MAX_MIDI_DEVS];

अटल DEFINE_SPINLOCK(रेजिस्टर_lock);

/*
 * prototypes
 */
अटल काष्ठा seq_oss_midi *get_mdev(पूर्णांक dev);
अटल काष्ठा seq_oss_midi *get_mididev(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev);
अटल पूर्णांक send_synth_event(काष्ठा seq_oss_devinfo *dp, काष्ठा snd_seq_event *ev, पूर्णांक dev);
अटल पूर्णांक send_midi_event(काष्ठा seq_oss_devinfo *dp, काष्ठा snd_seq_event *ev, काष्ठा seq_oss_midi *mdev);

/*
 * look up the existing ports
 * this looks a very exhausting job.
 */
पूर्णांक
snd_seq_oss_midi_lookup_ports(पूर्णांक client)
अणु
	काष्ठा snd_seq_client_info *clinfo;
	काष्ठा snd_seq_port_info *pinfo;

	clinfo = kzalloc(माप(*clinfo), GFP_KERNEL);
	pinfo = kzalloc(माप(*pinfo), GFP_KERNEL);
	अगर (! clinfo || ! pinfo) अणु
		kमुक्त(clinfo);
		kमुक्त(pinfo);
		वापस -ENOMEM;
	पूर्ण
	clinfo->client = -1;
	जबतक (snd_seq_kernel_client_ctl(client, SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT, clinfo) == 0) अणु
		अगर (clinfo->client == client)
			जारी; /* ignore myself */
		pinfo->addr.client = clinfo->client;
		pinfo->addr.port = -1;
		जबतक (snd_seq_kernel_client_ctl(client, SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT, pinfo) == 0)
			snd_seq_oss_midi_check_new_port(pinfo);
	पूर्ण
	kमुक्त(clinfo);
	kमुक्त(pinfo);
	वापस 0;
पूर्ण


/*
 */
अटल काष्ठा seq_oss_midi *
get_mdev(पूर्णांक dev)
अणु
	काष्ठा seq_oss_midi *mdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&रेजिस्टर_lock, flags);
	mdev = midi_devs[dev];
	अगर (mdev)
		snd_use_lock_use(&mdev->use_lock);
	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
	वापस mdev;
पूर्ण

/*
 * look क्रम the identical slot
 */
अटल काष्ठा seq_oss_midi *
find_slot(पूर्णांक client, पूर्णांक port)
अणु
	पूर्णांक i;
	काष्ठा seq_oss_midi *mdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&रेजिस्टर_lock, flags);
	क्रम (i = 0; i < max_midi_devs; i++) अणु
		mdev = midi_devs[i];
		अगर (mdev && mdev->client == client && mdev->port == port) अणु
			/* found! */
			snd_use_lock_use(&mdev->use_lock);
			spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
			वापस mdev;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
	वापस शून्य;
पूर्ण


#घोषणा PERM_WRITE (SNDRV_SEQ_PORT_CAP_WRITE|SNDRV_SEQ_PORT_CAP_SUBS_WRITE)
#घोषणा PERM_READ (SNDRV_SEQ_PORT_CAP_READ|SNDRV_SEQ_PORT_CAP_SUBS_READ)
/*
 * रेजिस्टर a new port अगर it करोesn't exist yet
 */
पूर्णांक
snd_seq_oss_midi_check_new_port(काष्ठा snd_seq_port_info *pinfo)
अणु
	पूर्णांक i;
	काष्ठा seq_oss_midi *mdev;
	अचिन्हित दीर्घ flags;

	/* the port must include generic midi */
	अगर (! (pinfo->type & SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC))
		वापस 0;
	/* either पढ़ो or ग_लिखो subscribable */
	अगर ((pinfo->capability & PERM_WRITE) != PERM_WRITE &&
	    (pinfo->capability & PERM_READ) != PERM_READ)
		वापस 0;

	/*
	 * look क्रम the identical slot
	 */
	अगर ((mdev = find_slot(pinfo->addr.client, pinfo->addr.port)) != शून्य) अणु
		/* alपढ़ोy exists */
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस 0;
	पूर्ण

	/*
	 * allocate midi info record
	 */
	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	/* copy the port inक्रमmation */
	mdev->client = pinfo->addr.client;
	mdev->port = pinfo->addr.port;
	mdev->flags = pinfo->capability;
	mdev->खोलोed = 0;
	snd_use_lock_init(&mdev->use_lock);

	/* copy and truncate the name of synth device */
	strscpy(mdev->name, pinfo->name, माप(mdev->name));

	/* create MIDI coder */
	अगर (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &mdev->coder) < 0) अणु
		pr_err("ALSA: seq_oss: can't malloc midi coder\n");
		kमुक्त(mdev);
		वापस -ENOMEM;
	पूर्ण
	/* OSS sequencer adds running status to all sequences */
	snd_midi_event_no_status(mdev->coder, 1);

	/*
	 * look क्रम en empty slot
	 */
	spin_lock_irqsave(&रेजिस्टर_lock, flags);
	क्रम (i = 0; i < max_midi_devs; i++) अणु
		अगर (midi_devs[i] == शून्य)
			अवरोध;
	पूर्ण
	अगर (i >= max_midi_devs) अणु
		अगर (max_midi_devs >= SNDRV_SEQ_OSS_MAX_MIDI_DEVS) अणु
			spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
			snd_midi_event_मुक्त(mdev->coder);
			kमुक्त(mdev);
			वापस -ENOMEM;
		पूर्ण
		max_midi_devs++;
	पूर्ण
	mdev->seq_device = i;
	midi_devs[mdev->seq_device] = mdev;
	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);

	वापस 0;
पूर्ण

/*
 * release the midi device अगर it was रेजिस्टरed
 */
पूर्णांक
snd_seq_oss_midi_check_निकास_port(पूर्णांक client, पूर्णांक port)
अणु
	काष्ठा seq_oss_midi *mdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक index;

	अगर ((mdev = find_slot(client, port)) != शून्य) अणु
		spin_lock_irqsave(&रेजिस्टर_lock, flags);
		midi_devs[mdev->seq_device] = शून्य;
		spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
		snd_use_lock_मुक्त(&mdev->use_lock);
		snd_use_lock_sync(&mdev->use_lock);
		snd_midi_event_मुक्त(mdev->coder);
		kमुक्त(mdev);
	पूर्ण
	spin_lock_irqsave(&रेजिस्टर_lock, flags);
	क्रम (index = max_midi_devs - 1; index >= 0; index--) अणु
		अगर (midi_devs[index])
			अवरोध;
	पूर्ण
	max_midi_devs = index + 1;
	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
	वापस 0;
पूर्ण


/*
 * release the midi device अगर it was रेजिस्टरed
 */
व्योम
snd_seq_oss_midi_clear_all(व्योम)
अणु
	पूर्णांक i;
	काष्ठा seq_oss_midi *mdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&रेजिस्टर_lock, flags);
	क्रम (i = 0; i < max_midi_devs; i++) अणु
		अगर ((mdev = midi_devs[i]) != शून्य) अणु
			snd_midi_event_मुक्त(mdev->coder);
			kमुक्त(mdev);
			midi_devs[i] = शून्य;
		पूर्ण
	पूर्ण
	max_midi_devs = 0;
	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
पूर्ण


/*
 * set up midi tables
 */
व्योम
snd_seq_oss_midi_setup(काष्ठा seq_oss_devinfo *dp)
अणु
	dp->max_mididev = max_midi_devs;
पूर्ण

/*
 * clean up midi tables
 */
व्योम
snd_seq_oss_midi_cleanup(काष्ठा seq_oss_devinfo *dp)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < dp->max_mididev; i++)
		snd_seq_oss_midi_बंद(dp, i);
	dp->max_mididev = 0;
पूर्ण


/*
 * खोलो all midi devices.  ignore errors.
 */
व्योम
snd_seq_oss_midi_खोलो_all(काष्ठा seq_oss_devinfo *dp, पूर्णांक file_mode)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < dp->max_mididev; i++)
		snd_seq_oss_midi_खोलो(dp, i, file_mode);
पूर्ण


/*
 * get the midi device inक्रमmation
 */
अटल काष्ठा seq_oss_midi *
get_mididev(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev)
अणु
	अगर (dev < 0 || dev >= dp->max_mididev)
		वापस शून्य;
	dev = array_index_nospec(dev, dp->max_mididev);
	वापस get_mdev(dev);
पूर्ण


/*
 * खोलो the midi device अगर not खोलोed yet
 */
पूर्णांक
snd_seq_oss_midi_खोलो(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक भ_शेषe)
अणु
	पूर्णांक perm;
	काष्ठा seq_oss_midi *mdev;
	काष्ठा snd_seq_port_subscribe subs;

	अगर ((mdev = get_mididev(dp, dev)) == शून्य)
		वापस -ENODEV;

	/* alपढ़ोy used? */
	अगर (mdev->खोलोed && mdev->devinfo != dp) अणु
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस -EBUSY;
	पूर्ण

	perm = 0;
	अगर (is_ग_लिखो_mode(भ_शेषe))
		perm |= PERM_WRITE;
	अगर (is_पढ़ो_mode(भ_शेषe))
		perm |= PERM_READ;
	perm &= mdev->flags;
	अगर (perm == 0) अणु
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस -ENXIO;
	पूर्ण

	/* alपढ़ोy खोलोed? */
	अगर ((mdev->खोलोed & perm) == perm) अणु
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस 0;
	पूर्ण

	perm &= ~mdev->खोलोed;

	स_रखो(&subs, 0, माप(subs));

	अगर (perm & PERM_WRITE) अणु
		subs.sender = dp->addr;
		subs.dest.client = mdev->client;
		subs.dest.port = mdev->port;
		अगर (snd_seq_kernel_client_ctl(dp->cseq, SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT, &subs) >= 0)
			mdev->खोलोed |= PERM_WRITE;
	पूर्ण
	अगर (perm & PERM_READ) अणु
		subs.sender.client = mdev->client;
		subs.sender.port = mdev->port;
		subs.dest = dp->addr;
		subs.flags = SNDRV_SEQ_PORT_SUBS_TIMESTAMP;
		subs.queue = dp->queue;		/* queue क्रम बारtamps */
		अगर (snd_seq_kernel_client_ctl(dp->cseq, SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT, &subs) >= 0)
			mdev->खोलोed |= PERM_READ;
	पूर्ण

	अगर (! mdev->खोलोed) अणु
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस -ENXIO;
	पूर्ण

	mdev->devinfo = dp;
	snd_use_lock_मुक्त(&mdev->use_lock);
	वापस 0;
पूर्ण

/*
 * बंद the midi device अगर alपढ़ोy खोलोed
 */
पूर्णांक
snd_seq_oss_midi_बंद(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev)
अणु
	काष्ठा seq_oss_midi *mdev;
	काष्ठा snd_seq_port_subscribe subs;

	अगर ((mdev = get_mididev(dp, dev)) == शून्य)
		वापस -ENODEV;
	अगर (! mdev->खोलोed || mdev->devinfo != dp) अणु
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस 0;
	पूर्ण

	स_रखो(&subs, 0, माप(subs));
	अगर (mdev->खोलोed & PERM_WRITE) अणु
		subs.sender = dp->addr;
		subs.dest.client = mdev->client;
		subs.dest.port = mdev->port;
		snd_seq_kernel_client_ctl(dp->cseq, SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT, &subs);
	पूर्ण
	अगर (mdev->खोलोed & PERM_READ) अणु
		subs.sender.client = mdev->client;
		subs.sender.port = mdev->port;
		subs.dest = dp->addr;
		snd_seq_kernel_client_ctl(dp->cseq, SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT, &subs);
	पूर्ण

	mdev->खोलोed = 0;
	mdev->devinfo = शून्य;

	snd_use_lock_मुक्त(&mdev->use_lock);
	वापस 0;
पूर्ण

/*
 * change seq capability flags to file mode flags
 */
पूर्णांक
snd_seq_oss_midi_filemode(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev)
अणु
	काष्ठा seq_oss_midi *mdev;
	पूर्णांक mode;

	अगर ((mdev = get_mididev(dp, dev)) == शून्य)
		वापस 0;

	mode = 0;
	अगर (mdev->खोलोed & PERM_WRITE)
		mode |= SNDRV_SEQ_OSS_खाता_WRITE;
	अगर (mdev->खोलोed & PERM_READ)
		mode |= SNDRV_SEQ_OSS_खाता_READ;

	snd_use_lock_मुक्त(&mdev->use_lock);
	वापस mode;
पूर्ण

/*
 * reset the midi device and बंद it:
 * so far, only बंद the device.
 */
व्योम
snd_seq_oss_midi_reset(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev)
अणु
	काष्ठा seq_oss_midi *mdev;

	अगर ((mdev = get_mididev(dp, dev)) == शून्य)
		वापस;
	अगर (! mdev->खोलोed) अणु
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस;
	पूर्ण

	अगर (mdev->खोलोed & PERM_WRITE) अणु
		काष्ठा snd_seq_event ev;
		पूर्णांक c;

		स_रखो(&ev, 0, माप(ev));
		ev.dest.client = mdev->client;
		ev.dest.port = mdev->port;
		ev.queue = dp->queue;
		ev.source.port = dp->port;
		अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_SYNTH) अणु
			ev.type = SNDRV_SEQ_EVENT_SENSING;
			snd_seq_oss_dispatch(dp, &ev, 0, 0);
		पूर्ण
		क्रम (c = 0; c < 16; c++) अणु
			ev.type = SNDRV_SEQ_EVENT_CONTROLLER;
			ev.data.control.channel = c;
			ev.data.control.param = MIDI_CTL_ALL_NOTES_OFF;
			snd_seq_oss_dispatch(dp, &ev, 0, 0);
			अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC) अणु
				ev.data.control.param =
					MIDI_CTL_RESET_CONTROLLERS;
				snd_seq_oss_dispatch(dp, &ev, 0, 0);
				ev.type = SNDRV_SEQ_EVENT_PITCHBEND;
				ev.data.control.value = 0;
				snd_seq_oss_dispatch(dp, &ev, 0, 0);
			पूर्ण
		पूर्ण
	पूर्ण
	// snd_seq_oss_midi_बंद(dp, dev);
	snd_use_lock_मुक्त(&mdev->use_lock);
पूर्ण


/*
 * get client/port of the specअगरied MIDI device
 */
व्योम
snd_seq_oss_midi_get_addr(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, काष्ठा snd_seq_addr *addr)
अणु
	काष्ठा seq_oss_midi *mdev;

	अगर ((mdev = get_mididev(dp, dev)) == शून्य)
		वापस;
	addr->client = mdev->client;
	addr->port = mdev->port;
	snd_use_lock_मुक्त(&mdev->use_lock);
पूर्ण


/*
 * input callback - this can be atomic
 */
पूर्णांक
snd_seq_oss_midi_input(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी_data)
अणु
	काष्ठा seq_oss_devinfo *dp = (काष्ठा seq_oss_devinfo *)निजी_data;
	काष्ठा seq_oss_midi *mdev;
	पूर्णांक rc;

	अगर (dp->पढ़ोq == शून्य)
		वापस 0;
	अगर ((mdev = find_slot(ev->source.client, ev->source.port)) == शून्य)
		वापस 0;
	अगर (! (mdev->खोलोed & PERM_READ)) अणु
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस 0;
	पूर्ण

	अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC)
		rc = send_synth_event(dp, ev, mdev->seq_device);
	अन्यथा
		rc = send_midi_event(dp, ev, mdev);

	snd_use_lock_मुक्त(&mdev->use_lock);
	वापस rc;
पूर्ण

/*
 * convert ALSA sequencer event to OSS synth event
 */
अटल पूर्णांक
send_synth_event(काष्ठा seq_oss_devinfo *dp, काष्ठा snd_seq_event *ev, पूर्णांक dev)
अणु
	जोड़ evrec ossev;

	स_रखो(&ossev, 0, माप(ossev));

	चयन (ev->type) अणु
	हाल SNDRV_SEQ_EVENT_NOTEON:
		ossev.v.cmd = MIDI_NOTEON; अवरोध;
	हाल SNDRV_SEQ_EVENT_NOTखातापूर्णF:
		ossev.v.cmd = MIDI_NOTखातापूर्णF; अवरोध;
	हाल SNDRV_SEQ_EVENT_KEYPRESS:
		ossev.v.cmd = MIDI_KEY_PRESSURE; अवरोध;
	हाल SNDRV_SEQ_EVENT_CONTROLLER:
		ossev.l.cmd = MIDI_CTL_CHANGE; अवरोध;
	हाल SNDRV_SEQ_EVENT_PGMCHANGE:
		ossev.l.cmd = MIDI_PGM_CHANGE; अवरोध;
	हाल SNDRV_SEQ_EVENT_CHANPRESS:
		ossev.l.cmd = MIDI_CHN_PRESSURE; अवरोध;
	हाल SNDRV_SEQ_EVENT_PITCHBEND:
		ossev.l.cmd = MIDI_PITCH_BEND; अवरोध;
	शेष:
		वापस 0; /* not supported */
	पूर्ण

	ossev.v.dev = dev;

	चयन (ev->type) अणु
	हाल SNDRV_SEQ_EVENT_NOTEON:
	हाल SNDRV_SEQ_EVENT_NOTखातापूर्णF:
	हाल SNDRV_SEQ_EVENT_KEYPRESS:
		ossev.v.code = EV_CHN_VOICE;
		ossev.v.note = ev->data.note.note;
		ossev.v.parm = ev->data.note.velocity;
		ossev.v.chn = ev->data.note.channel;
		अवरोध;
	हाल SNDRV_SEQ_EVENT_CONTROLLER:
	हाल SNDRV_SEQ_EVENT_PGMCHANGE:
	हाल SNDRV_SEQ_EVENT_CHANPRESS:
		ossev.l.code = EV_CHN_COMMON;
		ossev.l.p1 = ev->data.control.param;
		ossev.l.val = ev->data.control.value;
		ossev.l.chn = ev->data.control.channel;
		अवरोध;
	हाल SNDRV_SEQ_EVENT_PITCHBEND:
		ossev.l.code = EV_CHN_COMMON;
		ossev.l.val = ev->data.control.value + 8192;
		ossev.l.chn = ev->data.control.channel;
		अवरोध;
	पूर्ण
	
	snd_seq_oss_पढ़ोq_put_बारtamp(dp->पढ़ोq, ev->समय.tick, dp->seq_mode);
	snd_seq_oss_पढ़ोq_put_event(dp->पढ़ोq, &ossev);

	वापस 0;
पूर्ण

/*
 * decode event and send MIDI bytes to पढ़ो queue
 */
अटल पूर्णांक
send_midi_event(काष्ठा seq_oss_devinfo *dp, काष्ठा snd_seq_event *ev, काष्ठा seq_oss_midi *mdev)
अणु
	अक्षर msg[32];
	पूर्णांक len;
	
	snd_seq_oss_पढ़ोq_put_बारtamp(dp->पढ़ोq, ev->समय.tick, dp->seq_mode);
	अगर (!dp->समयr->running)
		len = snd_seq_oss_समयr_start(dp->समयr);
	अगर (ev->type == SNDRV_SEQ_EVENT_SYSEX) अणु
		snd_seq_oss_पढ़ोq_sysex(dp->पढ़ोq, mdev->seq_device, ev);
		snd_midi_event_reset_decode(mdev->coder);
	पूर्ण अन्यथा अणु
		len = snd_midi_event_decode(mdev->coder, msg, माप(msg), ev);
		अगर (len > 0)
			snd_seq_oss_पढ़ोq_माला_दो(dp->पढ़ोq, mdev->seq_device, msg, len);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * dump midi data
 * वापस 0 : enqueued
 *        non-zero : invalid - ignored
 */
पूर्णांक
snd_seq_oss_midi_अ_दो(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, अचिन्हित अक्षर c, काष्ठा snd_seq_event *ev)
अणु
	काष्ठा seq_oss_midi *mdev;

	अगर ((mdev = get_mididev(dp, dev)) == शून्य)
		वापस -ENODEV;
	अगर (snd_midi_event_encode_byte(mdev->coder, c, ev)) अणु
		snd_seq_oss_fill_addr(dp, ev, mdev->client, mdev->port);
		snd_use_lock_मुक्त(&mdev->use_lock);
		वापस 0;
	पूर्ण
	snd_use_lock_मुक्त(&mdev->use_lock);
	वापस -EINVAL;
पूर्ण

/*
 * create OSS compatible midi_info record
 */
पूर्णांक
snd_seq_oss_midi_make_info(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, काष्ठा midi_info *inf)
अणु
	काष्ठा seq_oss_midi *mdev;

	अगर ((mdev = get_mididev(dp, dev)) == शून्य)
		वापस -ENXIO;
	inf->device = dev;
	inf->dev_type = 0; /* FIXME: ?? */
	inf->capabilities = 0; /* FIXME: ?? */
	strscpy(inf->name, mdev->name, माप(inf->name));
	snd_use_lock_मुक्त(&mdev->use_lock);
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_SND_PROC_FS
/*
 * proc पूर्णांकerface
 */
अटल अक्षर *
capmode_str(पूर्णांक val)
अणु
	val &= PERM_READ|PERM_WRITE;
	अगर (val == (PERM_READ|PERM_WRITE))
		वापस "read/write";
	अन्यथा अगर (val == PERM_READ)
		वापस "read";
	अन्यथा अगर (val == PERM_WRITE)
		वापस "write";
	अन्यथा
		वापस "none";
पूर्ण

व्योम
snd_seq_oss_midi_info_पढ़ो(काष्ठा snd_info_buffer *buf)
अणु
	पूर्णांक i;
	काष्ठा seq_oss_midi *mdev;

	snd_iम_लिखो(buf, "\nNumber of MIDI devices: %d\n", max_midi_devs);
	क्रम (i = 0; i < max_midi_devs; i++) अणु
		snd_iम_लिखो(buf, "\nmidi %d: ", i);
		mdev = get_mdev(i);
		अगर (mdev == शून्य) अणु
			snd_iम_लिखो(buf, "*empty*\n");
			जारी;
		पूर्ण
		snd_iम_लिखो(buf, "[%s] ALSA port %d:%d\n", mdev->name,
			    mdev->client, mdev->port);
		snd_iम_लिखो(buf, "  capability %s / opened %s\n",
			    capmode_str(mdev->flags),
			    capmode_str(mdev->खोलोed));
		snd_use_lock_मुक्त(&mdev->use_lock);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

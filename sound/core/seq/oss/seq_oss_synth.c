<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * synth device handlers
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "seq_oss_synth.h"
#समावेश "seq_oss_midi.h"
#समावेश "../seq_lock.h"
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/nospec.h>

/*
 * स्थिरants
 */
#घोषणा SNDRV_SEQ_OSS_MAX_SYNTH_NAME	30
#घोषणा MAX_SYSEX_BUFLEN		128


/*
 * definition of synth info records
 */

/* sysex buffer */
काष्ठा seq_oss_synth_sysex अणु
	पूर्णांक len;
	पूर्णांक skip;
	अचिन्हित अक्षर buf[MAX_SYSEX_BUFLEN];
पूर्ण;

/* synth info */
काष्ठा seq_oss_synth अणु
	पूर्णांक seq_device;

	/* क्रम synth_info */
	पूर्णांक synth_type;
	पूर्णांक synth_subtype;
	पूर्णांक nr_voices;

	अक्षर name[SNDRV_SEQ_OSS_MAX_SYNTH_NAME];
	काष्ठा snd_seq_oss_callback oper;

	पूर्णांक खोलोed;

	व्योम *निजी_data;
	snd_use_lock_t use_lock;
पूर्ण;


/*
 * device table
 */
अटल पूर्णांक max_synth_devs;
अटल काष्ठा seq_oss_synth *synth_devs[SNDRV_SEQ_OSS_MAX_SYNTH_DEVS];
अटल काष्ठा seq_oss_synth midi_synth_dev = अणु
	.seq_device = -1,
	.synth_type = SYNTH_TYPE_MIDI,
	.synth_subtype = 0,
	.nr_voices = 16,
	.name = "MIDI",
पूर्ण;

अटल DEFINE_SPINLOCK(रेजिस्टर_lock);

/*
 * prototypes
 */
अटल काष्ठा seq_oss_synth *get_synthdev(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev);
अटल व्योम reset_channels(काष्ठा seq_oss_synthinfo *info);

/*
 * global initialization
 */
व्योम __init
snd_seq_oss_synth_init(व्योम)
अणु
	snd_use_lock_init(&midi_synth_dev.use_lock);
पूर्ण

/*
 * registration of the synth device
 */
पूर्णांक
snd_seq_oss_synth_probe(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	पूर्णांक i;
	काष्ठा seq_oss_synth *rec;
	काष्ठा snd_seq_oss_reg *reg = SNDRV_SEQ_DEVICE_ARGPTR(dev);
	अचिन्हित दीर्घ flags;

	rec = kzalloc(माप(*rec), GFP_KERNEL);
	अगर (!rec)
		वापस -ENOMEM;
	rec->seq_device = -1;
	rec->synth_type = reg->type;
	rec->synth_subtype = reg->subtype;
	rec->nr_voices = reg->nvoices;
	rec->oper = reg->oper;
	rec->निजी_data = reg->निजी_data;
	rec->खोलोed = 0;
	snd_use_lock_init(&rec->use_lock);

	/* copy and truncate the name of synth device */
	strscpy(rec->name, dev->name, माप(rec->name));

	/* registration */
	spin_lock_irqsave(&रेजिस्टर_lock, flags);
	क्रम (i = 0; i < max_synth_devs; i++) अणु
		अगर (synth_devs[i] == शून्य)
			अवरोध;
	पूर्ण
	अगर (i >= max_synth_devs) अणु
		अगर (max_synth_devs >= SNDRV_SEQ_OSS_MAX_SYNTH_DEVS) अणु
			spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
			pr_err("ALSA: seq_oss: no more synth slot\n");
			kमुक्त(rec);
			वापस -ENOMEM;
		पूर्ण
		max_synth_devs++;
	पूर्ण
	rec->seq_device = i;
	synth_devs[i] = rec;
	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
	dev->driver_data = rec;
#अगर_घोषित SNDRV_OSS_INFO_DEV_SYNTH
	अगर (i < SNDRV_CARDS)
		snd_oss_info_रेजिस्टर(SNDRV_OSS_INFO_DEV_SYNTH, i, rec->name);
#पूर्ण_अगर
	वापस 0;
पूर्ण


पूर्णांक
snd_seq_oss_synth_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	पूर्णांक index;
	काष्ठा seq_oss_synth *rec = dev->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&रेजिस्टर_lock, flags);
	क्रम (index = 0; index < max_synth_devs; index++) अणु
		अगर (synth_devs[index] == rec)
			अवरोध;
	पूर्ण
	अगर (index >= max_synth_devs) अणु
		spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
		pr_err("ALSA: seq_oss: can't unregister synth\n");
		वापस -EINVAL;
	पूर्ण
	synth_devs[index] = शून्य;
	अगर (index == max_synth_devs - 1) अणु
		क्रम (index--; index >= 0; index--) अणु
			अगर (synth_devs[index])
				अवरोध;
		पूर्ण
		max_synth_devs = index + 1;
	पूर्ण
	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
#अगर_घोषित SNDRV_OSS_INFO_DEV_SYNTH
	अगर (rec->seq_device < SNDRV_CARDS)
		snd_oss_info_unरेजिस्टर(SNDRV_OSS_INFO_DEV_SYNTH, rec->seq_device);
#पूर्ण_अगर

	snd_use_lock_sync(&rec->use_lock);
	kमुक्त(rec);

	वापस 0;
पूर्ण


/*
 */
अटल काष्ठा seq_oss_synth *
get_sdev(पूर्णांक dev)
अणु
	काष्ठा seq_oss_synth *rec;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&रेजिस्टर_lock, flags);
	rec = synth_devs[dev];
	अगर (rec)
		snd_use_lock_use(&rec->use_lock);
	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);
	वापस rec;
पूर्ण


/*
 * set up synth tables
 */

व्योम
snd_seq_oss_synth_setup(काष्ठा seq_oss_devinfo *dp)
अणु
	पूर्णांक i;
	काष्ठा seq_oss_synth *rec;
	काष्ठा seq_oss_synthinfo *info;

	dp->max_synthdev = max_synth_devs;
	dp->synth_खोलोed = 0;
	स_रखो(dp->synths, 0, माप(dp->synths));
	क्रम (i = 0; i < dp->max_synthdev; i++) अणु
		rec = get_sdev(i);
		अगर (rec == शून्य)
			जारी;
		अगर (rec->oper.खोलो == शून्य || rec->oper.बंद == शून्य) अणु
			snd_use_lock_मुक्त(&rec->use_lock);
			जारी;
		पूर्ण
		info = &dp->synths[i];
		info->arg.app_index = dp->port;
		info->arg.file_mode = dp->file_mode;
		info->arg.seq_mode = dp->seq_mode;
		अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_SYNTH)
			info->arg.event_passing = SNDRV_SEQ_OSS_PROCESS_EVENTS;
		अन्यथा
			info->arg.event_passing = SNDRV_SEQ_OSS_PASS_EVENTS;
		info->खोलोed = 0;
		अगर (!try_module_get(rec->oper.owner)) अणु
			snd_use_lock_मुक्त(&rec->use_lock);
			जारी;
		पूर्ण
		अगर (rec->oper.खोलो(&info->arg, rec->निजी_data) < 0) अणु
			module_put(rec->oper.owner);
			snd_use_lock_मुक्त(&rec->use_lock);
			जारी;
		पूर्ण
		info->nr_voices = rec->nr_voices;
		अगर (info->nr_voices > 0) अणु
			info->ch = kसुस्मृति(info->nr_voices, माप(काष्ठा seq_oss_chinfo), GFP_KERNEL);
			अगर (!info->ch) अणु
				rec->oper.बंद(&info->arg);
				module_put(rec->oper.owner);
				snd_use_lock_मुक्त(&rec->use_lock);
				जारी;
			पूर्ण
			reset_channels(info);
		पूर्ण
		info->खोलोed++;
		rec->खोलोed++;
		dp->synth_खोलोed++;
		snd_use_lock_मुक्त(&rec->use_lock);
	पूर्ण
पूर्ण


/*
 * set up synth tables क्रम MIDI emulation - /dev/music mode only
 */

व्योम
snd_seq_oss_synth_setup_midi(काष्ठा seq_oss_devinfo *dp)
अणु
	पूर्णांक i;

	अगर (dp->max_synthdev >= SNDRV_SEQ_OSS_MAX_SYNTH_DEVS)
		वापस;

	क्रम (i = 0; i < dp->max_mididev; i++) अणु
		काष्ठा seq_oss_synthinfo *info;
		info = &dp->synths[dp->max_synthdev];
		अगर (snd_seq_oss_midi_खोलो(dp, i, dp->file_mode) < 0)
			जारी;
		info->arg.app_index = dp->port;
		info->arg.file_mode = dp->file_mode;
		info->arg.seq_mode = dp->seq_mode;
		info->arg.निजी_data = info;
		info->is_midi = 1;
		info->midi_mapped = i;
		info->arg.event_passing = SNDRV_SEQ_OSS_PASS_EVENTS;
		snd_seq_oss_midi_get_addr(dp, i, &info->arg.addr);
		info->खोलोed = 1;
		midi_synth_dev.खोलोed++;
		dp->max_synthdev++;
		अगर (dp->max_synthdev >= SNDRV_SEQ_OSS_MAX_SYNTH_DEVS)
			अवरोध;
	पूर्ण
पूर्ण


/*
 * clean up synth tables
 */

व्योम
snd_seq_oss_synth_cleanup(काष्ठा seq_oss_devinfo *dp)
अणु
	पूर्णांक i;
	काष्ठा seq_oss_synth *rec;
	काष्ठा seq_oss_synthinfo *info;

	अगर (snd_BUG_ON(dp->max_synthdev > SNDRV_SEQ_OSS_MAX_SYNTH_DEVS))
		वापस;
	क्रम (i = 0; i < dp->max_synthdev; i++) अणु
		info = &dp->synths[i];
		अगर (! info->खोलोed)
			जारी;
		अगर (info->is_midi) अणु
			अगर (midi_synth_dev.खोलोed > 0) अणु
				snd_seq_oss_midi_बंद(dp, info->midi_mapped);
				midi_synth_dev.खोलोed--;
			पूर्ण
		पूर्ण अन्यथा अणु
			rec = get_sdev(i);
			अगर (rec == शून्य)
				जारी;
			अगर (rec->खोलोed > 0) अणु
				rec->oper.बंद(&info->arg);
				module_put(rec->oper.owner);
				rec->खोलोed = 0;
			पूर्ण
			snd_use_lock_मुक्त(&rec->use_lock);
		पूर्ण
		kमुक्त(info->sysex);
		info->sysex = शून्य;
		kमुक्त(info->ch);
		info->ch = शून्य;
	पूर्ण
	dp->synth_खोलोed = 0;
	dp->max_synthdev = 0;
पूर्ण

अटल काष्ठा seq_oss_synthinfo *
get_synthinfo_nospec(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev)
अणु
	अगर (dev < 0 || dev >= dp->max_synthdev)
		वापस शून्य;
	dev = array_index_nospec(dev, SNDRV_SEQ_OSS_MAX_SYNTH_DEVS);
	वापस &dp->synths[dev];
पूर्ण

/*
 * वापस synth device inक्रमmation poपूर्णांकer
 */
अटल काष्ठा seq_oss_synth *
get_synthdev(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev)
अणु
	काष्ठा seq_oss_synth *rec;
	काष्ठा seq_oss_synthinfo *info = get_synthinfo_nospec(dp, dev);

	अगर (!info)
		वापस शून्य;
	अगर (!info->खोलोed)
		वापस शून्य;
	अगर (info->is_midi) अणु
		rec = &midi_synth_dev;
		snd_use_lock_use(&rec->use_lock);
	पूर्ण अन्यथा अणु
		rec = get_sdev(dev);
		अगर (!rec)
			वापस शून्य;
	पूर्ण
	अगर (! rec->खोलोed) अणु
		snd_use_lock_मुक्त(&rec->use_lock);
		वापस शून्य;
	पूर्ण
	वापस rec;
पूर्ण


/*
 * reset note and velocity on each channel.
 */
अटल व्योम
reset_channels(काष्ठा seq_oss_synthinfo *info)
अणु
	पूर्णांक i;
	अगर (info->ch == शून्य || ! info->nr_voices)
		वापस;
	क्रम (i = 0; i < info->nr_voices; i++) अणु
		info->ch[i].note = -1;
		info->ch[i].vel = 0;
	पूर्ण
पूर्ण


/*
 * reset synth device:
 * call reset callback.  अगर no callback is defined, send a heartbeat
 * event to the corresponding port.
 */
व्योम
snd_seq_oss_synth_reset(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev)
अणु
	काष्ठा seq_oss_synth *rec;
	काष्ठा seq_oss_synthinfo *info;

	info = get_synthinfo_nospec(dp, dev);
	अगर (!info || !info->खोलोed)
		वापस;
	अगर (info->sysex)
		info->sysex->len = 0; /* reset sysex */
	reset_channels(info);
	अगर (info->is_midi) अणु
		अगर (midi_synth_dev.खोलोed <= 0)
			वापस;
		snd_seq_oss_midi_reset(dp, info->midi_mapped);
		/* reखोलो the device */
		snd_seq_oss_midi_बंद(dp, dev);
		अगर (snd_seq_oss_midi_खोलो(dp, info->midi_mapped,
					  dp->file_mode) < 0) अणु
			midi_synth_dev.खोलोed--;
			info->खोलोed = 0;
			kमुक्त(info->sysex);
			info->sysex = शून्य;
			kमुक्त(info->ch);
			info->ch = शून्य;
		पूर्ण
		वापस;
	पूर्ण

	rec = get_sdev(dev);
	अगर (rec == शून्य)
		वापस;
	अगर (rec->oper.reset) अणु
		rec->oper.reset(&info->arg);
	पूर्ण अन्यथा अणु
		काष्ठा snd_seq_event ev;
		स_रखो(&ev, 0, माप(ev));
		snd_seq_oss_fill_addr(dp, &ev, info->arg.addr.client,
				      info->arg.addr.port);
		ev.type = SNDRV_SEQ_EVENT_RESET;
		snd_seq_oss_dispatch(dp, &ev, 0, 0);
	पूर्ण
	snd_use_lock_मुक्त(&rec->use_lock);
पूर्ण


/*
 * load a patch record:
 * call load_patch callback function
 */
पूर्णांक
snd_seq_oss_synth_load_patch(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक fmt,
			    स्थिर अक्षर __user *buf, पूर्णांक p, पूर्णांक c)
अणु
	काष्ठा seq_oss_synth *rec;
	काष्ठा seq_oss_synthinfo *info;
	पूर्णांक rc;

	info = get_synthinfo_nospec(dp, dev);
	अगर (!info)
		वापस -ENXIO;

	अगर (info->is_midi)
		वापस 0;
	अगर ((rec = get_synthdev(dp, dev)) == शून्य)
		वापस -ENXIO;

	अगर (rec->oper.load_patch == शून्य)
		rc = -ENXIO;
	अन्यथा
		rc = rec->oper.load_patch(&info->arg, fmt, buf, p, c);
	snd_use_lock_मुक्त(&rec->use_lock);
	वापस rc;
पूर्ण

/*
 * check अगर the device is valid synth device and वापस the synth info
 */
काष्ठा seq_oss_synthinfo *
snd_seq_oss_synth_info(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev)
अणु
	काष्ठा seq_oss_synth *rec;

	rec = get_synthdev(dp, dev);
	अगर (rec) अणु
		snd_use_lock_मुक्त(&rec->use_lock);
		वापस get_synthinfo_nospec(dp, dev);
	पूर्ण
	वापस शून्य;
पूर्ण


/*
 * receive OSS 6 byte sysex packet:
 * the full sysex message will be sent अगर it reaches to the end of data
 * (0xff).
 */
पूर्णांक
snd_seq_oss_synth_sysex(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, अचिन्हित अक्षर *buf, काष्ठा snd_seq_event *ev)
अणु
	पूर्णांक i, send;
	अचिन्हित अक्षर *dest;
	काष्ठा seq_oss_synth_sysex *sysex;
	काष्ठा seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	अगर (!info)
		वापस -ENXIO;

	sysex = info->sysex;
	अगर (sysex == शून्य) अणु
		sysex = kzalloc(माप(*sysex), GFP_KERNEL);
		अगर (sysex == शून्य)
			वापस -ENOMEM;
		info->sysex = sysex;
	पूर्ण

	send = 0;
	dest = sysex->buf + sysex->len;
	/* copy 6 byte packet to the buffer */
	क्रम (i = 0; i < 6; i++) अणु
		अगर (buf[i] == 0xff) अणु
			send = 1;
			अवरोध;
		पूर्ण
		dest[i] = buf[i];
		sysex->len++;
		अगर (sysex->len >= MAX_SYSEX_BUFLEN) अणु
			sysex->len = 0;
			sysex->skip = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (sysex->len && send) अणु
		अगर (sysex->skip) अणु
			sysex->skip = 0;
			sysex->len = 0;
			वापस -EINVAL; /* skip */
		पूर्ण
		/* copy the data to event record and send it */
		ev->flags = SNDRV_SEQ_EVENT_LENGTH_VARIABLE;
		अगर (snd_seq_oss_synth_addr(dp, dev, ev))
			वापस -EINVAL;
		ev->data.ext.len = sysex->len;
		ev->data.ext.ptr = sysex->buf;
		sysex->len = 0;
		वापस 0;
	पूर्ण

	वापस -EINVAL; /* skip */
पूर्ण

/*
 * fill the event source/destination addresses
 */
पूर्णांक
snd_seq_oss_synth_addr(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, काष्ठा snd_seq_event *ev)
अणु
	काष्ठा seq_oss_synthinfo *info = snd_seq_oss_synth_info(dp, dev);

	अगर (!info)
		वापस -EINVAL;
	snd_seq_oss_fill_addr(dp, ev, info->arg.addr.client,
			      info->arg.addr.port);
	वापस 0;
पूर्ण


/*
 * OSS compatible ioctl
 */
पूर्णांक
snd_seq_oss_synth_ioctl(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ addr)
अणु
	काष्ठा seq_oss_synth *rec;
	काष्ठा seq_oss_synthinfo *info;
	पूर्णांक rc;

	info = get_synthinfo_nospec(dp, dev);
	अगर (!info || info->is_midi)
		वापस -ENXIO;
	अगर ((rec = get_synthdev(dp, dev)) == शून्य)
		वापस -ENXIO;
	अगर (rec->oper.ioctl == शून्य)
		rc = -ENXIO;
	अन्यथा
		rc = rec->oper.ioctl(&info->arg, cmd, addr);
	snd_use_lock_मुक्त(&rec->use_lock);
	वापस rc;
पूर्ण


/*
 * send OSS raw events - SEQ_PRIVATE and SEQ_VOLUME
 */
पूर्णांक
snd_seq_oss_synth_raw_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, अचिन्हित अक्षर *data, काष्ठा snd_seq_event *ev)
अणु
	काष्ठा seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	अगर (!info || info->is_midi)
		वापस -ENXIO;
	ev->type = SNDRV_SEQ_EVENT_OSS;
	स_नकल(ev->data.raw8.d, data, 8);
	वापस snd_seq_oss_synth_addr(dp, dev, ev);
पूर्ण


/*
 * create OSS compatible synth_info record
 */
पूर्णांक
snd_seq_oss_synth_make_info(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, काष्ठा synth_info *inf)
अणु
	काष्ठा seq_oss_synth *rec;
	काष्ठा seq_oss_synthinfo *info = get_synthinfo_nospec(dp, dev);

	अगर (!info)
		वापस -ENXIO;

	अगर (info->is_midi) अणु
		काष्ठा midi_info minf;
		अगर (snd_seq_oss_midi_make_info(dp, info->midi_mapped, &minf))
			वापस -ENXIO;
		inf->synth_type = SYNTH_TYPE_MIDI;
		inf->synth_subtype = 0;
		inf->nr_voices = 16;
		inf->device = dev;
		strscpy(inf->name, minf.name, माप(inf->name));
	पूर्ण अन्यथा अणु
		अगर ((rec = get_synthdev(dp, dev)) == शून्य)
			वापस -ENXIO;
		inf->synth_type = rec->synth_type;
		inf->synth_subtype = rec->synth_subtype;
		inf->nr_voices = rec->nr_voices;
		inf->device = dev;
		strscpy(inf->name, rec->name, माप(inf->name));
		snd_use_lock_मुक्त(&rec->use_lock);
	पूर्ण
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_SND_PROC_FS
/*
 * proc पूर्णांकerface
 */
व्योम
snd_seq_oss_synth_info_पढ़ो(काष्ठा snd_info_buffer *buf)
अणु
	पूर्णांक i;
	काष्ठा seq_oss_synth *rec;

	snd_iम_लिखो(buf, "\nNumber of synth devices: %d\n", max_synth_devs);
	क्रम (i = 0; i < max_synth_devs; i++) अणु
		snd_iम_लिखो(buf, "\nsynth %d: ", i);
		rec = get_sdev(i);
		अगर (rec == शून्य) अणु
			snd_iम_लिखो(buf, "*empty*\n");
			जारी;
		पूर्ण
		snd_iम_लिखो(buf, "[%s]\n", rec->name);
		snd_iम_लिखो(buf, "  type 0x%x : subtype 0x%x : voices %d\n",
			    rec->synth_type, rec->synth_subtype,
			    rec->nr_voices);
		snd_iम_लिखो(buf, "  capabilities : ioctl %s / load_patch %s\n",
			    enabled_str((दीर्घ)rec->oper.ioctl),
			    enabled_str((दीर्घ)rec->oper.load_patch));
		snd_use_lock_मुक्त(&rec->use_lock);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

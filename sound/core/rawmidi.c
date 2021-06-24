<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Abstract layer क्रम MIDI v1.0 stream
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/core.h>
#समावेश <linux/major.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/nospec.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/minors.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Midlevel RawMidi code for ALSA.");
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_SND_OSSEMUL
अटल पूर्णांक midi_map[SNDRV_CARDS];
अटल पूर्णांक amidi_map[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)] = 1पूर्ण;
module_param_array(midi_map, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(midi_map, "Raw MIDI device number assigned to 1st OSS device.");
module_param_array(amidi_map, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(amidi_map, "Raw MIDI device number assigned to 2nd OSS device.");
#पूर्ण_अगर /* CONFIG_SND_OSSEMUL */

अटल पूर्णांक snd_rawmidi_मुक्त(काष्ठा snd_rawmidi *rmidi);
अटल पूर्णांक snd_rawmidi_dev_मुक्त(काष्ठा snd_device *device);
अटल पूर्णांक snd_rawmidi_dev_रेजिस्टर(काष्ठा snd_device *device);
अटल पूर्णांक snd_rawmidi_dev_disconnect(काष्ठा snd_device *device);

अटल LIST_HEAD(snd_rawmidi_devices);
अटल DEFINE_MUTEX(रेजिस्टर_mutex);

#घोषणा rmidi_err(rmidi, fmt, args...) \
	dev_err(&(rmidi)->dev, fmt, ##args)
#घोषणा rmidi_warn(rmidi, fmt, args...) \
	dev_warn(&(rmidi)->dev, fmt, ##args)
#घोषणा rmidi_dbg(rmidi, fmt, args...) \
	dev_dbg(&(rmidi)->dev, fmt, ##args)

काष्ठा snd_rawmidi_status32 अणु
	s32 stream;
	s32 tstamp_sec;			/* Timestamp */
	s32 tstamp_nsec;
	u32 avail;			/* available bytes */
	u32 xruns;			/* count of overruns since last status (in bytes) */
	अचिन्हित अक्षर reserved[16];	/* reserved क्रम future use */
पूर्ण;

#घोषणा SNDRV_RAWMIDI_IOCTL_STATUS32	_IOWR('W', 0x20, काष्ठा snd_rawmidi_status32)

काष्ठा snd_rawmidi_status64 अणु
	पूर्णांक stream;
	u8 rsvd[4];			/* alignment */
	s64 tstamp_sec;			/* Timestamp */
	s64 tstamp_nsec;
	माप_प्रकार avail;			/* available bytes */
	माप_प्रकार xruns;			/* count of overruns since last status (in bytes) */
	अचिन्हित अक्षर reserved[16];	/* reserved क्रम future use */
पूर्ण;

#घोषणा SNDRV_RAWMIDI_IOCTL_STATUS64	_IOWR('W', 0x20, काष्ठा snd_rawmidi_status64)

अटल काष्ठा snd_rawmidi *snd_rawmidi_search(काष्ठा snd_card *card, पूर्णांक device)
अणु
	काष्ठा snd_rawmidi *rawmidi;

	list_क्रम_each_entry(rawmidi, &snd_rawmidi_devices, list)
		अगर (rawmidi->card == card && rawmidi->device == device)
			वापस rawmidi;
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित लघु snd_rawmidi_file_flags(काष्ठा file *file)
अणु
	चयन (file->f_mode & (FMODE_READ | FMODE_WRITE)) अणु
	हाल FMODE_WRITE:
		वापस SNDRV_RAWMIDI_LFLG_OUTPUT;
	हाल FMODE_READ:
		वापस SNDRV_RAWMIDI_LFLG_INPUT;
	शेष:
		वापस SNDRV_RAWMIDI_LFLG_OPEN;
	पूर्ण
पूर्ण

अटल अंतरभूत bool __snd_rawmidi_पढ़ोy(काष्ठा snd_rawmidi_runसमय *runसमय)
अणु
	वापस runसमय->avail >= runसमय->avail_min;
पूर्ण

अटल bool snd_rawmidi_पढ़ोy(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ flags;
	bool पढ़ोy;

	spin_lock_irqsave(&runसमय->lock, flags);
	पढ़ोy = __snd_rawmidi_पढ़ोy(runसमय);
	spin_unlock_irqrestore(&runसमय->lock, flags);
	वापस पढ़ोy;
पूर्ण

अटल अंतरभूत पूर्णांक snd_rawmidi_पढ़ोy_append(काष्ठा snd_rawmidi_substream *substream,
					   माप_प्रकार count)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;

	वापस runसमय->avail >= runसमय->avail_min &&
	       (!substream->append || runसमय->avail >= count);
पूर्ण

अटल व्योम snd_rawmidi_input_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय =
		container_of(work, काष्ठा snd_rawmidi_runसमय, event_work);

	अगर (runसमय->event)
		runसमय->event(runसमय->substream);
पूर्ण

/* buffer refcount management: call with runसमय->lock held */
अटल अंतरभूत व्योम snd_rawmidi_buffer_ref(काष्ठा snd_rawmidi_runसमय *runसमय)
अणु
	runसमय->buffer_ref++;
पूर्ण

अटल अंतरभूत व्योम snd_rawmidi_buffer_unref(काष्ठा snd_rawmidi_runसमय *runसमय)
अणु
	runसमय->buffer_ref--;
पूर्ण

अटल पूर्णांक snd_rawmidi_runसमय_create(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय;

	runसमय = kzalloc(माप(*runसमय), GFP_KERNEL);
	अगर (!runसमय)
		वापस -ENOMEM;
	runसमय->substream = substream;
	spin_lock_init(&runसमय->lock);
	init_रुकोqueue_head(&runसमय->sleep);
	INIT_WORK(&runसमय->event_work, snd_rawmidi_input_event_work);
	runसमय->event = शून्य;
	runसमय->buffer_size = PAGE_SIZE;
	runसमय->avail_min = 1;
	अगर (substream->stream == SNDRV_RAWMIDI_STREAM_INPUT)
		runसमय->avail = 0;
	अन्यथा
		runसमय->avail = runसमय->buffer_size;
	runसमय->buffer = kvzalloc(runसमय->buffer_size, GFP_KERNEL);
	अगर (!runसमय->buffer) अणु
		kमुक्त(runसमय);
		वापस -ENOMEM;
	पूर्ण
	runसमय->appl_ptr = runसमय->hw_ptr = 0;
	substream->runसमय = runसमय;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rawmidi_runसमय_मुक्त(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;

	kvमुक्त(runसमय->buffer);
	kमुक्त(runसमय);
	substream->runसमय = शून्य;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_rawmidi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अगर (!substream->खोलोed)
		वापस;
	substream->ops->trigger(substream, up);
पूर्ण

अटल व्योम snd_rawmidi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अगर (!substream->खोलोed)
		वापस;
	substream->ops->trigger(substream, up);
	अगर (!up)
		cancel_work_sync(&substream->runसमय->event_work);
पूर्ण

अटल व्योम __reset_runसमय_ptrs(काष्ठा snd_rawmidi_runसमय *runसमय,
				 bool is_input)
अणु
	runसमय->drain = 0;
	runसमय->appl_ptr = runसमय->hw_ptr = 0;
	runसमय->avail = is_input ? 0 : runसमय->buffer_size;
पूर्ण

अटल व्योम reset_runसमय_ptrs(काष्ठा snd_rawmidi_runसमय *runसमय,
			       bool is_input)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&runसमय->lock, flags);
	__reset_runसमय_ptrs(runसमय, is_input);
	spin_unlock_irqrestore(&runसमय->lock, flags);
पूर्ण

पूर्णांक snd_rawmidi_drop_output(काष्ठा snd_rawmidi_substream *substream)
अणु
	snd_rawmidi_output_trigger(substream, 0);
	reset_runसमय_ptrs(substream->runसमय, false);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_drop_output);

पूर्णांक snd_rawmidi_drain_output(काष्ठा snd_rawmidi_substream *substream)
अणु
	पूर्णांक err;
	दीर्घ समयout;
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;

	err = 0;
	runसमय->drain = 1;
	समयout = रुको_event_पूर्णांकerruptible_समयout(runसमय->sleep,
				(runसमय->avail >= runसमय->buffer_size),
				10*HZ);
	अगर (संकेत_pending(current))
		err = -ERESTARTSYS;
	अगर (runसमय->avail < runसमय->buffer_size && !समयout) अणु
		rmidi_warn(substream->rmidi,
			   "rawmidi drain error (avail = %li, buffer_size = %li)\n",
			   (दीर्घ)runसमय->avail, (दीर्घ)runसमय->buffer_size);
		err = -EIO;
	पूर्ण
	runसमय->drain = 0;
	अगर (err != -ERESTARTSYS) अणु
		/* we need रुको a जबतक to make sure that Tx FIFOs are empty */
		अगर (substream->ops->drain)
			substream->ops->drain(substream);
		अन्यथा
			msleep(50);
		snd_rawmidi_drop_output(substream);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_drain_output);

पूर्णांक snd_rawmidi_drain_input(काष्ठा snd_rawmidi_substream *substream)
अणु
	snd_rawmidi_input_trigger(substream, 0);
	reset_runसमय_ptrs(substream->runसमय, true);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_drain_input);

/* look क्रम an available substream क्रम the given stream direction;
 * अगर a specअगरic subdevice is given, try to assign it
 */
अटल पूर्णांक assign_substream(काष्ठा snd_rawmidi *rmidi, पूर्णांक subdevice,
			    पूर्णांक stream, पूर्णांक mode,
			    काष्ठा snd_rawmidi_substream **sub_ret)
अणु
	काष्ठा snd_rawmidi_substream *substream;
	काष्ठा snd_rawmidi_str *s = &rmidi->streams[stream];
	अटल स्थिर अचिन्हित पूर्णांक info_flags[2] = अणु
		[SNDRV_RAWMIDI_STREAM_OUTPUT] = SNDRV_RAWMIDI_INFO_OUTPUT,
		[SNDRV_RAWMIDI_STREAM_INPUT] = SNDRV_RAWMIDI_INFO_INPUT,
	पूर्ण;

	अगर (!(rmidi->info_flags & info_flags[stream]))
		वापस -ENXIO;
	अगर (subdevice >= 0 && subdevice >= s->substream_count)
		वापस -ENODEV;

	list_क्रम_each_entry(substream, &s->substreams, list) अणु
		अगर (substream->खोलोed) अणु
			अगर (stream == SNDRV_RAWMIDI_STREAM_INPUT ||
			    !(mode & SNDRV_RAWMIDI_LFLG_APPEND) ||
			    !substream->append)
				जारी;
		पूर्ण
		अगर (subdevice < 0 || subdevice == substream->number) अणु
			*sub_ret = substream;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EAGAIN;
पूर्ण

/* खोलो and करो ref-counting क्रम the given substream */
अटल पूर्णांक खोलो_substream(काष्ठा snd_rawmidi *rmidi,
			  काष्ठा snd_rawmidi_substream *substream,
			  पूर्णांक mode)
अणु
	पूर्णांक err;

	अगर (substream->use_count == 0) अणु
		err = snd_rawmidi_runसमय_create(substream);
		अगर (err < 0)
			वापस err;
		err = substream->ops->खोलो(substream);
		अगर (err < 0) अणु
			snd_rawmidi_runसमय_मुक्त(substream);
			वापस err;
		पूर्ण
		substream->खोलोed = 1;
		substream->active_sensing = 0;
		अगर (mode & SNDRV_RAWMIDI_LFLG_APPEND)
			substream->append = 1;
		substream->pid = get_pid(task_pid(current));
		rmidi->streams[substream->stream].substream_खोलोed++;
	पूर्ण
	substream->use_count++;
	वापस 0;
पूर्ण

अटल व्योम बंद_substream(काष्ठा snd_rawmidi *rmidi,
			    काष्ठा snd_rawmidi_substream *substream,
			    पूर्णांक cleanup);

अटल पूर्णांक rawmidi_खोलो_priv(काष्ठा snd_rawmidi *rmidi, पूर्णांक subdevice, पूर्णांक mode,
			     काष्ठा snd_rawmidi_file *rfile)
अणु
	काष्ठा snd_rawmidi_substream *sinput = शून्य, *soutput = शून्य;
	पूर्णांक err;

	rfile->input = rfile->output = शून्य;
	अगर (mode & SNDRV_RAWMIDI_LFLG_INPUT) अणु
		err = assign_substream(rmidi, subdevice,
				       SNDRV_RAWMIDI_STREAM_INPUT,
				       mode, &sinput);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (mode & SNDRV_RAWMIDI_LFLG_OUTPUT) अणु
		err = assign_substream(rmidi, subdevice,
				       SNDRV_RAWMIDI_STREAM_OUTPUT,
				       mode, &soutput);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (sinput) अणु
		err = खोलो_substream(rmidi, sinput, mode);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (soutput) अणु
		err = खोलो_substream(rmidi, soutput, mode);
		अगर (err < 0) अणु
			अगर (sinput)
				बंद_substream(rmidi, sinput, 0);
			वापस err;
		पूर्ण
	पूर्ण

	rfile->rmidi = rmidi;
	rfile->input = sinput;
	rfile->output = soutput;
	वापस 0;
पूर्ण

/* called from sound/core/seq/seq_midi.c */
पूर्णांक snd_rawmidi_kernel_खोलो(काष्ठा snd_card *card, पूर्णांक device, पूर्णांक subdevice,
			    पूर्णांक mode, काष्ठा snd_rawmidi_file *rfile)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err = 0;

	अगर (snd_BUG_ON(!rfile))
		वापस -EINVAL;

	mutex_lock(&रेजिस्टर_mutex);
	rmidi = snd_rawmidi_search(card, device);
	अगर (!rmidi)
		err = -ENODEV;
	अन्यथा अगर (!try_module_get(rmidi->card->module))
		err = -ENXIO;
	mutex_unlock(&रेजिस्टर_mutex);
	अगर (err < 0)
		वापस err;

	mutex_lock(&rmidi->खोलो_mutex);
	err = rawmidi_खोलो_priv(rmidi, subdevice, mode, rfile);
	mutex_unlock(&rmidi->खोलो_mutex);
	अगर (err < 0)
		module_put(rmidi->card->module);
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_kernel_खोलो);

अटल पूर्णांक snd_rawmidi_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक maj = imajor(inode);
	काष्ठा snd_card *card;
	पूर्णांक subdevice;
	अचिन्हित लघु fflags;
	पूर्णांक err;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_file *rawmidi_file = शून्य;
	रुको_queue_entry_t रुको;

	अगर ((file->f_flags & O_APPEND) && !(file->f_flags & O_NONBLOCK))
		वापस -EINVAL;		/* invalid combination */

	err = stream_खोलो(inode, file);
	अगर (err < 0)
		वापस err;

	अगर (maj == snd_major) अणु
		rmidi = snd_lookup_minor_data(iminor(inode),
					      SNDRV_DEVICE_TYPE_RAWMIDI);
#अगर_घोषित CONFIG_SND_OSSEMUL
	पूर्ण अन्यथा अगर (maj == SOUND_MAJOR) अणु
		rmidi = snd_lookup_oss_minor_data(iminor(inode),
						  SNDRV_OSS_DEVICE_TYPE_MIDI);
#पूर्ण_अगर
	पूर्ण अन्यथा
		वापस -ENXIO;

	अगर (rmidi == शून्य)
		वापस -ENODEV;

	अगर (!try_module_get(rmidi->card->module)) अणु
		snd_card_unref(rmidi->card);
		वापस -ENXIO;
	पूर्ण

	mutex_lock(&rmidi->खोलो_mutex);
	card = rmidi->card;
	err = snd_card_file_add(card, file);
	अगर (err < 0)
		जाओ __error_card;
	fflags = snd_rawmidi_file_flags(file);
	अगर ((file->f_flags & O_APPEND) || maj == SOUND_MAJOR) /* OSS emul? */
		fflags |= SNDRV_RAWMIDI_LFLG_APPEND;
	rawmidi_file = kदो_स्मृति(माप(*rawmidi_file), GFP_KERNEL);
	अगर (rawmidi_file == शून्य) अणु
		err = -ENOMEM;
		जाओ __error;
	पूर्ण
	init_रुकोqueue_entry(&रुको, current);
	add_रुको_queue(&rmidi->खोलो_रुको, &रुको);
	जबतक (1) अणु
		subdevice = snd_ctl_get_preferred_subdevice(card, SND_CTL_SUBDEV_RAWMIDI);
		err = rawmidi_खोलो_priv(rmidi, subdevice, fflags, rawmidi_file);
		अगर (err >= 0)
			अवरोध;
		अगर (err == -EAGAIN) अणु
			अगर (file->f_flags & O_NONBLOCK) अणु
				err = -EBUSY;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			अवरोध;
		set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&rmidi->खोलो_mutex);
		schedule();
		mutex_lock(&rmidi->खोलो_mutex);
		अगर (rmidi->card->shutकरोwn) अणु
			err = -ENODEV;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			अवरोध;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(&rmidi->खोलो_रुको, &रुको);
	अगर (err < 0) अणु
		kमुक्त(rawmidi_file);
		जाओ __error;
	पूर्ण
#अगर_घोषित CONFIG_SND_OSSEMUL
	अगर (rawmidi_file->input && rawmidi_file->input->runसमय)
		rawmidi_file->input->runसमय->oss = (maj == SOUND_MAJOR);
	अगर (rawmidi_file->output && rawmidi_file->output->runसमय)
		rawmidi_file->output->runसमय->oss = (maj == SOUND_MAJOR);
#पूर्ण_अगर
	file->निजी_data = rawmidi_file;
	mutex_unlock(&rmidi->खोलो_mutex);
	snd_card_unref(rmidi->card);
	वापस 0;

 __error:
	snd_card_file_हटाओ(card, file);
 __error_card:
	mutex_unlock(&rmidi->खोलो_mutex);
	module_put(rmidi->card->module);
	snd_card_unref(rmidi->card);
	वापस err;
पूर्ण

अटल व्योम बंद_substream(काष्ठा snd_rawmidi *rmidi,
			    काष्ठा snd_rawmidi_substream *substream,
			    पूर्णांक cleanup)
अणु
	अगर (--substream->use_count)
		वापस;

	अगर (cleanup) अणु
		अगर (substream->stream == SNDRV_RAWMIDI_STREAM_INPUT)
			snd_rawmidi_input_trigger(substream, 0);
		अन्यथा अणु
			अगर (substream->active_sensing) अणु
				अचिन्हित अक्षर buf = 0xfe;
				/* sending single active sensing message
				 * to shut the device up
				 */
				snd_rawmidi_kernel_ग_लिखो(substream, &buf, 1);
			पूर्ण
			अगर (snd_rawmidi_drain_output(substream) == -ERESTARTSYS)
				snd_rawmidi_output_trigger(substream, 0);
		पूर्ण
	पूर्ण
	substream->ops->बंद(substream);
	अगर (substream->runसमय->निजी_मुक्त)
		substream->runसमय->निजी_मुक्त(substream);
	snd_rawmidi_runसमय_मुक्त(substream);
	substream->खोलोed = 0;
	substream->append = 0;
	put_pid(substream->pid);
	substream->pid = शून्य;
	rmidi->streams[substream->stream].substream_खोलोed--;
पूर्ण

अटल व्योम rawmidi_release_priv(काष्ठा snd_rawmidi_file *rfile)
अणु
	काष्ठा snd_rawmidi *rmidi;

	rmidi = rfile->rmidi;
	mutex_lock(&rmidi->खोलो_mutex);
	अगर (rfile->input) अणु
		बंद_substream(rmidi, rfile->input, 1);
		rfile->input = शून्य;
	पूर्ण
	अगर (rfile->output) अणु
		बंद_substream(rmidi, rfile->output, 1);
		rfile->output = शून्य;
	पूर्ण
	rfile->rmidi = शून्य;
	mutex_unlock(&rmidi->खोलो_mutex);
	wake_up(&rmidi->खोलो_रुको);
पूर्ण

/* called from sound/core/seq/seq_midi.c */
पूर्णांक snd_rawmidi_kernel_release(काष्ठा snd_rawmidi_file *rfile)
अणु
	काष्ठा snd_rawmidi *rmidi;

	अगर (snd_BUG_ON(!rfile))
		वापस -ENXIO;

	rmidi = rfile->rmidi;
	rawmidi_release_priv(rfile);
	module_put(rmidi->card->module);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_kernel_release);

अटल पूर्णांक snd_rawmidi_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_rawmidi_file *rfile;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा module *module;

	rfile = file->निजी_data;
	rmidi = rfile->rmidi;
	rawmidi_release_priv(rfile);
	kमुक्त(rfile);
	module = rmidi->card->module;
	snd_card_file_हटाओ(rmidi->card, file);
	module_put(module);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rawmidi_info(काष्ठा snd_rawmidi_substream *substream,
			    काष्ठा snd_rawmidi_info *info)
अणु
	काष्ठा snd_rawmidi *rmidi;

	अगर (substream == शून्य)
		वापस -ENODEV;
	rmidi = substream->rmidi;
	स_रखो(info, 0, माप(*info));
	info->card = rmidi->card->number;
	info->device = rmidi->device;
	info->subdevice = substream->number;
	info->stream = substream->stream;
	info->flags = rmidi->info_flags;
	म_नकल(info->id, rmidi->id);
	म_नकल(info->name, rmidi->name);
	म_नकल(info->subname, substream->name);
	info->subdevices_count = substream->pstr->substream_count;
	info->subdevices_avail = (substream->pstr->substream_count -
				  substream->pstr->substream_खोलोed);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rawmidi_info_user(काष्ठा snd_rawmidi_substream *substream,
				 काष्ठा snd_rawmidi_info __user *_info)
अणु
	काष्ठा snd_rawmidi_info info;
	पूर्णांक err;

	err = snd_rawmidi_info(substream, &info);
	अगर (err < 0)
		वापस err;
	अगर (copy_to_user(_info, &info, माप(काष्ठा snd_rawmidi_info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक __snd_rawmidi_info_select(काष्ठा snd_card *card,
				     काष्ठा snd_rawmidi_info *info)
अणु
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_str *pstr;
	काष्ठा snd_rawmidi_substream *substream;

	rmidi = snd_rawmidi_search(card, info->device);
	अगर (!rmidi)
		वापस -ENXIO;
	अगर (info->stream < 0 || info->stream > 1)
		वापस -EINVAL;
	info->stream = array_index_nospec(info->stream, 2);
	pstr = &rmidi->streams[info->stream];
	अगर (pstr->substream_count == 0)
		वापस -ENOENT;
	अगर (info->subdevice >= pstr->substream_count)
		वापस -ENXIO;
	list_क्रम_each_entry(substream, &pstr->substreams, list) अणु
		अगर ((अचिन्हित पूर्णांक)substream->number == info->subdevice)
			वापस snd_rawmidi_info(substream, info);
	पूर्ण
	वापस -ENXIO;
पूर्ण

पूर्णांक snd_rawmidi_info_select(काष्ठा snd_card *card, काष्ठा snd_rawmidi_info *info)
अणु
	पूर्णांक ret;

	mutex_lock(&रेजिस्टर_mutex);
	ret = __snd_rawmidi_info_select(card, info);
	mutex_unlock(&रेजिस्टर_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_info_select);

अटल पूर्णांक snd_rawmidi_info_select_user(काष्ठा snd_card *card,
					काष्ठा snd_rawmidi_info __user *_info)
अणु
	पूर्णांक err;
	काष्ठा snd_rawmidi_info info;

	अगर (get_user(info.device, &_info->device))
		वापस -EFAULT;
	अगर (get_user(info.stream, &_info->stream))
		वापस -EFAULT;
	अगर (get_user(info.subdevice, &_info->subdevice))
		वापस -EFAULT;
	err = snd_rawmidi_info_select(card, &info);
	अगर (err < 0)
		वापस err;
	अगर (copy_to_user(_info, &info, माप(काष्ठा snd_rawmidi_info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक resize_runसमय_buffer(काष्ठा snd_rawmidi_runसमय *runसमय,
				 काष्ठा snd_rawmidi_params *params,
				 bool is_input)
अणु
	अक्षर *newbuf, *oldbuf;

	अगर (params->buffer_size < 32 || params->buffer_size > 1024L * 1024L)
		वापस -EINVAL;
	अगर (params->avail_min < 1 || params->avail_min > params->buffer_size)
		वापस -EINVAL;
	अगर (params->buffer_size != runसमय->buffer_size) अणु
		newbuf = kvzalloc(params->buffer_size, GFP_KERNEL);
		अगर (!newbuf)
			वापस -ENOMEM;
		spin_lock_irq(&runसमय->lock);
		अगर (runसमय->buffer_ref) अणु
			spin_unlock_irq(&runसमय->lock);
			kvमुक्त(newbuf);
			वापस -EBUSY;
		पूर्ण
		oldbuf = runसमय->buffer;
		runसमय->buffer = newbuf;
		runसमय->buffer_size = params->buffer_size;
		__reset_runसमय_ptrs(runसमय, is_input);
		spin_unlock_irq(&runसमय->lock);
		kvमुक्त(oldbuf);
	पूर्ण
	runसमय->avail_min = params->avail_min;
	वापस 0;
पूर्ण

पूर्णांक snd_rawmidi_output_params(काष्ठा snd_rawmidi_substream *substream,
			      काष्ठा snd_rawmidi_params *params)
अणु
	अगर (substream->append && substream->use_count > 1)
		वापस -EBUSY;
	snd_rawmidi_drain_output(substream);
	substream->active_sensing = !params->no_active_sensing;
	वापस resize_runसमय_buffer(substream->runसमय, params, false);
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_output_params);

पूर्णांक snd_rawmidi_input_params(काष्ठा snd_rawmidi_substream *substream,
			     काष्ठा snd_rawmidi_params *params)
अणु
	snd_rawmidi_drain_input(substream);
	वापस resize_runसमय_buffer(substream->runसमय, params, true);
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_input_params);

अटल पूर्णांक snd_rawmidi_output_status(काष्ठा snd_rawmidi_substream *substream,
				     काष्ठा snd_rawmidi_status64 *status)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;

	स_रखो(status, 0, माप(*status));
	status->stream = SNDRV_RAWMIDI_STREAM_OUTPUT;
	spin_lock_irq(&runसमय->lock);
	status->avail = runसमय->avail;
	spin_unlock_irq(&runसमय->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rawmidi_input_status(काष्ठा snd_rawmidi_substream *substream,
				    काष्ठा snd_rawmidi_status64 *status)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;

	स_रखो(status, 0, माप(*status));
	status->stream = SNDRV_RAWMIDI_STREAM_INPUT;
	spin_lock_irq(&runसमय->lock);
	status->avail = runसमय->avail;
	status->xruns = runसमय->xruns;
	runसमय->xruns = 0;
	spin_unlock_irq(&runसमय->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rawmidi_ioctl_status32(काष्ठा snd_rawmidi_file *rfile,
				      काष्ठा snd_rawmidi_status32 __user *argp)
अणु
	पूर्णांक err = 0;
	काष्ठा snd_rawmidi_status32 __user *status = argp;
	काष्ठा snd_rawmidi_status32 status32;
	काष्ठा snd_rawmidi_status64 status64;

	अगर (copy_from_user(&status32, argp,
			   माप(काष्ठा snd_rawmidi_status32)))
		वापस -EFAULT;

	चयन (status32.stream) अणु
	हाल SNDRV_RAWMIDI_STREAM_OUTPUT:
		अगर (rfile->output == शून्य)
			वापस -EINVAL;
		err = snd_rawmidi_output_status(rfile->output, &status64);
		अवरोध;
	हाल SNDRV_RAWMIDI_STREAM_INPUT:
		अगर (rfile->input == शून्य)
			वापस -EINVAL;
		err = snd_rawmidi_input_status(rfile->input, &status64);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (err < 0)
		वापस err;

	status32 = (काष्ठा snd_rawmidi_status32) अणु
		.stream = status64.stream,
		.tstamp_sec = status64.tstamp_sec,
		.tstamp_nsec = status64.tstamp_nsec,
		.avail = status64.avail,
		.xruns = status64.xruns,
	पूर्ण;

	अगर (copy_to_user(status, &status32, माप(*status)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_rawmidi_ioctl_status64(काष्ठा snd_rawmidi_file *rfile,
				      काष्ठा snd_rawmidi_status64 __user *argp)
अणु
	पूर्णांक err = 0;
	काष्ठा snd_rawmidi_status64 status;

	अगर (copy_from_user(&status, argp, माप(काष्ठा snd_rawmidi_status64)))
		वापस -EFAULT;

	चयन (status.stream) अणु
	हाल SNDRV_RAWMIDI_STREAM_OUTPUT:
		अगर (rfile->output == शून्य)
			वापस -EINVAL;
		err = snd_rawmidi_output_status(rfile->output, &status);
		अवरोध;
	हाल SNDRV_RAWMIDI_STREAM_INPUT:
		अगर (rfile->input == शून्य)
			वापस -EINVAL;
		err = snd_rawmidi_input_status(rfile->input, &status);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (err < 0)
		वापस err;
	अगर (copy_to_user(argp, &status,
			 माप(काष्ठा snd_rawmidi_status64)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल दीर्घ snd_rawmidi_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_rawmidi_file *rfile;
	व्योम __user *argp = (व्योम __user *)arg;

	rfile = file->निजी_data;
	अगर (((cmd >> 8) & 0xff) != 'W')
		वापस -ENOTTY;
	चयन (cmd) अणु
	हाल SNDRV_RAWMIDI_IOCTL_PVERSION:
		वापस put_user(SNDRV_RAWMIDI_VERSION, (पूर्णांक __user *)argp) ? -EFAULT : 0;
	हाल SNDRV_RAWMIDI_IOCTL_INFO:
	अणु
		पूर्णांक stream;
		काष्ठा snd_rawmidi_info __user *info = argp;

		अगर (get_user(stream, &info->stream))
			वापस -EFAULT;
		चयन (stream) अणु
		हाल SNDRV_RAWMIDI_STREAM_INPUT:
			वापस snd_rawmidi_info_user(rfile->input, info);
		हाल SNDRV_RAWMIDI_STREAM_OUTPUT:
			वापस snd_rawmidi_info_user(rfile->output, info);
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	हाल SNDRV_RAWMIDI_IOCTL_PARAMS:
	अणु
		काष्ठा snd_rawmidi_params params;

		अगर (copy_from_user(&params, argp, माप(काष्ठा snd_rawmidi_params)))
			वापस -EFAULT;
		चयन (params.stream) अणु
		हाल SNDRV_RAWMIDI_STREAM_OUTPUT:
			अगर (rfile->output == शून्य)
				वापस -EINVAL;
			वापस snd_rawmidi_output_params(rfile->output, &params);
		हाल SNDRV_RAWMIDI_STREAM_INPUT:
			अगर (rfile->input == शून्य)
				वापस -EINVAL;
			वापस snd_rawmidi_input_params(rfile->input, &params);
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	हाल SNDRV_RAWMIDI_IOCTL_STATUS32:
		वापस snd_rawmidi_ioctl_status32(rfile, argp);
	हाल SNDRV_RAWMIDI_IOCTL_STATUS64:
		वापस snd_rawmidi_ioctl_status64(rfile, argp);
	हाल SNDRV_RAWMIDI_IOCTL_DROP:
	अणु
		पूर्णांक val;

		अगर (get_user(val, (पूर्णांक __user *) argp))
			वापस -EFAULT;
		चयन (val) अणु
		हाल SNDRV_RAWMIDI_STREAM_OUTPUT:
			अगर (rfile->output == शून्य)
				वापस -EINVAL;
			वापस snd_rawmidi_drop_output(rfile->output);
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	हाल SNDRV_RAWMIDI_IOCTL_DRAIN:
	अणु
		पूर्णांक val;

		अगर (get_user(val, (पूर्णांक __user *) argp))
			वापस -EFAULT;
		चयन (val) अणु
		हाल SNDRV_RAWMIDI_STREAM_OUTPUT:
			अगर (rfile->output == शून्य)
				वापस -EINVAL;
			वापस snd_rawmidi_drain_output(rfile->output);
		हाल SNDRV_RAWMIDI_STREAM_INPUT:
			अगर (rfile->input == शून्य)
				वापस -EINVAL;
			वापस snd_rawmidi_drain_input(rfile->input);
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	शेष:
		rmidi_dbg(rfile->rmidi,
			  "rawmidi: unknown command = 0x%x\n", cmd);
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक snd_rawmidi_control_ioctl(काष्ठा snd_card *card,
				     काष्ठा snd_ctl_file *control,
				     अचिन्हित पूर्णांक cmd,
				     अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल SNDRV_CTL_IOCTL_RAWMIDI_NEXT_DEVICE:
	अणु
		पूर्णांक device;

		अगर (get_user(device, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		अगर (device >= SNDRV_RAWMIDI_DEVICES) /* next device is -1 */
			device = SNDRV_RAWMIDI_DEVICES - 1;
		mutex_lock(&रेजिस्टर_mutex);
		device = device < 0 ? 0 : device + 1;
		जबतक (device < SNDRV_RAWMIDI_DEVICES) अणु
			अगर (snd_rawmidi_search(card, device))
				अवरोध;
			device++;
		पूर्ण
		अगर (device == SNDRV_RAWMIDI_DEVICES)
			device = -1;
		mutex_unlock(&रेजिस्टर_mutex);
		अगर (put_user(device, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल SNDRV_CTL_IOCTL_RAWMIDI_PREFER_SUBDEVICE:
	अणु
		पूर्णांक val;

		अगर (get_user(val, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		control->preferred_subdevice[SND_CTL_SUBDEV_RAWMIDI] = val;
		वापस 0;
	पूर्ण
	हाल SNDRV_CTL_IOCTL_RAWMIDI_INFO:
		वापस snd_rawmidi_info_select_user(card, argp);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

/**
 * snd_rawmidi_receive - receive the input data from the device
 * @substream: the rawmidi substream
 * @buffer: the buffer poपूर्णांकer
 * @count: the data size to पढ़ो
 *
 * Reads the data from the पूर्णांकernal buffer.
 *
 * Return: The size of पढ़ो data, or a negative error code on failure.
 */
पूर्णांक snd_rawmidi_receive(काष्ठा snd_rawmidi_substream *substream,
			स्थिर अचिन्हित अक्षर *buffer, पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0, count1;
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;

	अगर (!substream->खोलोed)
		वापस -EBADFD;
	अगर (runसमय->buffer == शून्य) अणु
		rmidi_dbg(substream->rmidi,
			  "snd_rawmidi_receive: input is not active!!!\n");
		वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(&runसमय->lock, flags);
	अगर (count == 1) अणु	/* special हाल, faster code */
		substream->bytes++;
		अगर (runसमय->avail < runसमय->buffer_size) अणु
			runसमय->buffer[runसमय->hw_ptr++] = buffer[0];
			runसमय->hw_ptr %= runसमय->buffer_size;
			runसमय->avail++;
			result++;
		पूर्ण अन्यथा अणु
			runसमय->xruns++;
		पूर्ण
	पूर्ण अन्यथा अणु
		substream->bytes += count;
		count1 = runसमय->buffer_size - runसमय->hw_ptr;
		अगर (count1 > count)
			count1 = count;
		अगर (count1 > (पूर्णांक)(runसमय->buffer_size - runसमय->avail))
			count1 = runसमय->buffer_size - runसमय->avail;
		स_नकल(runसमय->buffer + runसमय->hw_ptr, buffer, count1);
		runसमय->hw_ptr += count1;
		runसमय->hw_ptr %= runसमय->buffer_size;
		runसमय->avail += count1;
		count -= count1;
		result += count1;
		अगर (count > 0) अणु
			buffer += count1;
			count1 = count;
			अगर (count1 > (पूर्णांक)(runसमय->buffer_size - runसमय->avail)) अणु
				count1 = runसमय->buffer_size - runसमय->avail;
				runसमय->xruns += count - count1;
			पूर्ण
			अगर (count1 > 0) अणु
				स_नकल(runसमय->buffer, buffer, count1);
				runसमय->hw_ptr = count1;
				runसमय->avail += count1;
				result += count1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (result > 0) अणु
		अगर (runसमय->event)
			schedule_work(&runसमय->event_work);
		अन्यथा अगर (__snd_rawmidi_पढ़ोy(runसमय))
			wake_up(&runसमय->sleep);
	पूर्ण
	spin_unlock_irqrestore(&runसमय->lock, flags);
	वापस result;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_receive);

अटल दीर्घ snd_rawmidi_kernel_पढ़ो1(काष्ठा snd_rawmidi_substream *substream,
				     अचिन्हित अक्षर __user *userbuf,
				     अचिन्हित अक्षर *kernelbuf, दीर्घ count)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ result = 0, count1;
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ appl_ptr;
	पूर्णांक err = 0;

	spin_lock_irqsave(&runसमय->lock, flags);
	snd_rawmidi_buffer_ref(runसमय);
	जबतक (count > 0 && runसमय->avail) अणु
		count1 = runसमय->buffer_size - runसमय->appl_ptr;
		अगर (count1 > count)
			count1 = count;
		अगर (count1 > (पूर्णांक)runसमय->avail)
			count1 = runसमय->avail;

		/* update runसमय->appl_ptr beक्रमe unlocking क्रम userbuf */
		appl_ptr = runसमय->appl_ptr;
		runसमय->appl_ptr += count1;
		runसमय->appl_ptr %= runसमय->buffer_size;
		runसमय->avail -= count1;

		अगर (kernelbuf)
			स_नकल(kernelbuf + result, runसमय->buffer + appl_ptr, count1);
		अगर (userbuf) अणु
			spin_unlock_irqrestore(&runसमय->lock, flags);
			अगर (copy_to_user(userbuf + result,
					 runसमय->buffer + appl_ptr, count1))
				err = -EFAULT;
			spin_lock_irqsave(&runसमय->lock, flags);
			अगर (err)
				जाओ out;
		पूर्ण
		result += count1;
		count -= count1;
	पूर्ण
 out:
	snd_rawmidi_buffer_unref(runसमय);
	spin_unlock_irqrestore(&runसमय->lock, flags);
	वापस result > 0 ? result : err;
पूर्ण

दीर्घ snd_rawmidi_kernel_पढ़ो(काष्ठा snd_rawmidi_substream *substream,
			     अचिन्हित अक्षर *buf, दीर्घ count)
अणु
	snd_rawmidi_input_trigger(substream, 1);
	वापस snd_rawmidi_kernel_पढ़ो1(substream, शून्य/*userbuf*/, buf, count);
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_kernel_पढ़ो);

अटल sमाप_प्रकार snd_rawmidi_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
				loff_t *offset)
अणु
	दीर्घ result;
	पूर्णांक count1;
	काष्ठा snd_rawmidi_file *rfile;
	काष्ठा snd_rawmidi_substream *substream;
	काष्ठा snd_rawmidi_runसमय *runसमय;

	rfile = file->निजी_data;
	substream = rfile->input;
	अगर (substream == शून्य)
		वापस -EIO;
	runसमय = substream->runसमय;
	snd_rawmidi_input_trigger(substream, 1);
	result = 0;
	जबतक (count > 0) अणु
		spin_lock_irq(&runसमय->lock);
		जबतक (!__snd_rawmidi_पढ़ोy(runसमय)) अणु
			रुको_queue_entry_t रुको;

			अगर ((file->f_flags & O_NONBLOCK) != 0 || result > 0) अणु
				spin_unlock_irq(&runसमय->lock);
				वापस result > 0 ? result : -EAGAIN;
			पूर्ण
			init_रुकोqueue_entry(&रुको, current);
			add_रुको_queue(&runसमय->sleep, &रुको);
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&runसमय->lock);
			schedule();
			हटाओ_रुको_queue(&runसमय->sleep, &रुको);
			अगर (rfile->rmidi->card->shutकरोwn)
				वापस -ENODEV;
			अगर (संकेत_pending(current))
				वापस result > 0 ? result : -ERESTARTSYS;
			spin_lock_irq(&runसमय->lock);
			अगर (!runसमय->avail) अणु
				spin_unlock_irq(&runसमय->lock);
				वापस result > 0 ? result : -EIO;
			पूर्ण
		पूर्ण
		spin_unlock_irq(&runसमय->lock);
		count1 = snd_rawmidi_kernel_पढ़ो1(substream,
						  (अचिन्हित अक्षर __user *)buf,
						  शून्य/*kernelbuf*/,
						  count);
		अगर (count1 < 0)
			वापस result > 0 ? result : count1;
		result += count1;
		buf += count1;
		count -= count1;
	पूर्ण
	वापस result;
पूर्ण

/**
 * snd_rawmidi_transmit_empty - check whether the output buffer is empty
 * @substream: the rawmidi substream
 *
 * Return: 1 अगर the पूर्णांकernal output buffer is empty, 0 अगर not.
 */
पूर्णांक snd_rawmidi_transmit_empty(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	अगर (runसमय->buffer == शून्य) अणु
		rmidi_dbg(substream->rmidi,
			  "snd_rawmidi_transmit_empty: output is not active!!!\n");
		वापस 1;
	पूर्ण
	spin_lock_irqsave(&runसमय->lock, flags);
	result = runसमय->avail >= runसमय->buffer_size;
	spin_unlock_irqrestore(&runसमय->lock, flags);
	वापस result;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_transmit_empty);

/**
 * __snd_rawmidi_transmit_peek - copy data from the पूर्णांकernal buffer
 * @substream: the rawmidi substream
 * @buffer: the buffer poपूर्णांकer
 * @count: data size to transfer
 *
 * This is a variant of snd_rawmidi_transmit_peek() without spinlock.
 */
पूर्णांक __snd_rawmidi_transmit_peek(काष्ठा snd_rawmidi_substream *substream,
			      अचिन्हित अक्षर *buffer, पूर्णांक count)
अणु
	पूर्णांक result, count1;
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;

	अगर (runसमय->buffer == शून्य) अणु
		rmidi_dbg(substream->rmidi,
			  "snd_rawmidi_transmit_peek: output is not active!!!\n");
		वापस -EINVAL;
	पूर्ण
	result = 0;
	अगर (runसमय->avail >= runसमय->buffer_size) अणु
		/* warning: lowlevel layer MUST trigger करोwn the hardware */
		जाओ __skip;
	पूर्ण
	अगर (count == 1) अणु	/* special हाल, faster code */
		*buffer = runसमय->buffer[runसमय->hw_ptr];
		result++;
	पूर्ण अन्यथा अणु
		count1 = runसमय->buffer_size - runसमय->hw_ptr;
		अगर (count1 > count)
			count1 = count;
		अगर (count1 > (पूर्णांक)(runसमय->buffer_size - runसमय->avail))
			count1 = runसमय->buffer_size - runसमय->avail;
		स_नकल(buffer, runसमय->buffer + runसमय->hw_ptr, count1);
		count -= count1;
		result += count1;
		अगर (count > 0) अणु
			अगर (count > (पूर्णांक)(runसमय->buffer_size - runसमय->avail - count1))
				count = runसमय->buffer_size - runसमय->avail - count1;
			स_नकल(buffer + count1, runसमय->buffer, count);
			result += count;
		पूर्ण
	पूर्ण
      __skip:
	वापस result;
पूर्ण
EXPORT_SYMBOL(__snd_rawmidi_transmit_peek);

/**
 * snd_rawmidi_transmit_peek - copy data from the पूर्णांकernal buffer
 * @substream: the rawmidi substream
 * @buffer: the buffer poपूर्णांकer
 * @count: data size to transfer
 *
 * Copies data from the पूर्णांकernal output buffer to the given buffer.
 *
 * Call this in the पूर्णांकerrupt handler when the midi output is पढ़ोy,
 * and call snd_rawmidi_transmit_ack() after the transmission is
 * finished.
 *
 * Return: The size of copied data, or a negative error code on failure.
 */
पूर्णांक snd_rawmidi_transmit_peek(काष्ठा snd_rawmidi_substream *substream,
			      अचिन्हित अक्षर *buffer, पूर्णांक count)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&runसमय->lock, flags);
	result = __snd_rawmidi_transmit_peek(substream, buffer, count);
	spin_unlock_irqrestore(&runसमय->lock, flags);
	वापस result;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_transmit_peek);

/**
 * __snd_rawmidi_transmit_ack - acknowledge the transmission
 * @substream: the rawmidi substream
 * @count: the transferred count
 *
 * This is a variant of __snd_rawmidi_transmit_ack() without spinlock.
 */
पूर्णांक __snd_rawmidi_transmit_ack(काष्ठा snd_rawmidi_substream *substream, पूर्णांक count)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;

	अगर (runसमय->buffer == शून्य) अणु
		rmidi_dbg(substream->rmidi,
			  "snd_rawmidi_transmit_ack: output is not active!!!\n");
		वापस -EINVAL;
	पूर्ण
	snd_BUG_ON(runसमय->avail + count > runसमय->buffer_size);
	runसमय->hw_ptr += count;
	runसमय->hw_ptr %= runसमय->buffer_size;
	runसमय->avail += count;
	substream->bytes += count;
	अगर (count > 0) अणु
		अगर (runसमय->drain || __snd_rawmidi_पढ़ोy(runसमय))
			wake_up(&runसमय->sleep);
	पूर्ण
	वापस count;
पूर्ण
EXPORT_SYMBOL(__snd_rawmidi_transmit_ack);

/**
 * snd_rawmidi_transmit_ack - acknowledge the transmission
 * @substream: the rawmidi substream
 * @count: the transferred count
 *
 * Advances the hardware poपूर्णांकer क्रम the पूर्णांकernal output buffer with
 * the given size and updates the condition.
 * Call after the transmission is finished.
 *
 * Return: The advanced size अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_rawmidi_transmit_ack(काष्ठा snd_rawmidi_substream *substream, पूर्णांक count)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&runसमय->lock, flags);
	result = __snd_rawmidi_transmit_ack(substream, count);
	spin_unlock_irqrestore(&runसमय->lock, flags);
	वापस result;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_transmit_ack);

/**
 * snd_rawmidi_transmit - copy from the buffer to the device
 * @substream: the rawmidi substream
 * @buffer: the buffer poपूर्णांकer
 * @count: the data size to transfer
 *
 * Copies data from the buffer to the device and advances the poपूर्णांकer.
 *
 * Return: The copied size अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_rawmidi_transmit(काष्ठा snd_rawmidi_substream *substream,
			 अचिन्हित अक्षर *buffer, पूर्णांक count)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&runसमय->lock, flags);
	अगर (!substream->खोलोed)
		result = -EBADFD;
	अन्यथा अणु
		count = __snd_rawmidi_transmit_peek(substream, buffer, count);
		अगर (count <= 0)
			result = count;
		अन्यथा
			result = __snd_rawmidi_transmit_ack(substream, count);
	पूर्ण
	spin_unlock_irqrestore(&runसमय->lock, flags);
	वापस result;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_transmit);

/**
 * snd_rawmidi_proceed - Discard the all pending bytes and proceed
 * @substream: rawmidi substream
 *
 * Return: the number of discarded bytes
 */
पूर्णांक snd_rawmidi_proceed(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ flags;
	पूर्णांक count = 0;

	spin_lock_irqsave(&runसमय->lock, flags);
	अगर (runसमय->avail < runसमय->buffer_size) अणु
		count = runसमय->buffer_size - runसमय->avail;
		__snd_rawmidi_transmit_ack(substream, count);
	पूर्ण
	spin_unlock_irqrestore(&runसमय->lock, flags);
	वापस count;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_proceed);

अटल दीर्घ snd_rawmidi_kernel_ग_लिखो1(काष्ठा snd_rawmidi_substream *substream,
				      स्थिर अचिन्हित अक्षर __user *userbuf,
				      स्थिर अचिन्हित अक्षर *kernelbuf,
				      दीर्घ count)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ count1, result;
	काष्ठा snd_rawmidi_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ appl_ptr;

	अगर (!kernelbuf && !userbuf)
		वापस -EINVAL;
	अगर (snd_BUG_ON(!runसमय->buffer))
		वापस -EINVAL;

	result = 0;
	spin_lock_irqsave(&runसमय->lock, flags);
	अगर (substream->append) अणु
		अगर ((दीर्घ)runसमय->avail < count) अणु
			spin_unlock_irqrestore(&runसमय->lock, flags);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	snd_rawmidi_buffer_ref(runसमय);
	जबतक (count > 0 && runसमय->avail > 0) अणु
		count1 = runसमय->buffer_size - runसमय->appl_ptr;
		अगर (count1 > count)
			count1 = count;
		अगर (count1 > (दीर्घ)runसमय->avail)
			count1 = runसमय->avail;

		/* update runसमय->appl_ptr beक्रमe unlocking क्रम userbuf */
		appl_ptr = runसमय->appl_ptr;
		runसमय->appl_ptr += count1;
		runसमय->appl_ptr %= runसमय->buffer_size;
		runसमय->avail -= count1;

		अगर (kernelbuf)
			स_नकल(runसमय->buffer + appl_ptr,
			       kernelbuf + result, count1);
		अन्यथा अगर (userbuf) अणु
			spin_unlock_irqrestore(&runसमय->lock, flags);
			अगर (copy_from_user(runसमय->buffer + appl_ptr,
					   userbuf + result, count1)) अणु
				spin_lock_irqsave(&runसमय->lock, flags);
				result = result > 0 ? result : -EFAULT;
				जाओ __end;
			पूर्ण
			spin_lock_irqsave(&runसमय->lock, flags);
		पूर्ण
		result += count1;
		count -= count1;
	पूर्ण
      __end:
	count1 = runसमय->avail < runसमय->buffer_size;
	snd_rawmidi_buffer_unref(runसमय);
	spin_unlock_irqrestore(&runसमय->lock, flags);
	अगर (count1)
		snd_rawmidi_output_trigger(substream, 1);
	वापस result;
पूर्ण

दीर्घ snd_rawmidi_kernel_ग_लिखो(काष्ठा snd_rawmidi_substream *substream,
			      स्थिर अचिन्हित अक्षर *buf, दीर्घ count)
अणु
	वापस snd_rawmidi_kernel_ग_लिखो1(substream, शून्य, buf, count);
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_kernel_ग_लिखो);

अटल sमाप_प्रकार snd_rawmidi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *offset)
अणु
	दीर्घ result, समयout;
	पूर्णांक count1;
	काष्ठा snd_rawmidi_file *rfile;
	काष्ठा snd_rawmidi_runसमय *runसमय;
	काष्ठा snd_rawmidi_substream *substream;

	rfile = file->निजी_data;
	substream = rfile->output;
	runसमय = substream->runसमय;
	/* we cannot put an atomic message to our buffer */
	अगर (substream->append && count > runसमय->buffer_size)
		वापस -EIO;
	result = 0;
	जबतक (count > 0) अणु
		spin_lock_irq(&runसमय->lock);
		जबतक (!snd_rawmidi_पढ़ोy_append(substream, count)) अणु
			रुको_queue_entry_t रुको;

			अगर (file->f_flags & O_NONBLOCK) अणु
				spin_unlock_irq(&runसमय->lock);
				वापस result > 0 ? result : -EAGAIN;
			पूर्ण
			init_रुकोqueue_entry(&रुको, current);
			add_रुको_queue(&runसमय->sleep, &रुको);
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&runसमय->lock);
			समयout = schedule_समयout(30 * HZ);
			हटाओ_रुको_queue(&runसमय->sleep, &रुको);
			अगर (rfile->rmidi->card->shutकरोwn)
				वापस -ENODEV;
			अगर (संकेत_pending(current))
				वापस result > 0 ? result : -ERESTARTSYS;
			spin_lock_irq(&runसमय->lock);
			अगर (!runसमय->avail && !समयout) अणु
				spin_unlock_irq(&runसमय->lock);
				वापस result > 0 ? result : -EIO;
			पूर्ण
		पूर्ण
		spin_unlock_irq(&runसमय->lock);
		count1 = snd_rawmidi_kernel_ग_लिखो1(substream, buf, शून्य, count);
		अगर (count1 < 0)
			वापस result > 0 ? result : count1;
		result += count1;
		buf += count1;
		अगर ((माप_प्रकार)count1 < count && (file->f_flags & O_NONBLOCK))
			अवरोध;
		count -= count1;
	पूर्ण
	अगर (file->f_flags & O_DSYNC) अणु
		spin_lock_irq(&runसमय->lock);
		जबतक (runसमय->avail != runसमय->buffer_size) अणु
			रुको_queue_entry_t रुको;
			अचिन्हित पूर्णांक last_avail = runसमय->avail;

			init_रुकोqueue_entry(&रुको, current);
			add_रुको_queue(&runसमय->sleep, &रुको);
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&runसमय->lock);
			समयout = schedule_समयout(30 * HZ);
			हटाओ_रुको_queue(&runसमय->sleep, &रुको);
			अगर (संकेत_pending(current))
				वापस result > 0 ? result : -ERESTARTSYS;
			अगर (runसमय->avail == last_avail && !समयout)
				वापस result > 0 ? result : -EIO;
			spin_lock_irq(&runसमय->lock);
		पूर्ण
		spin_unlock_irq(&runसमय->lock);
	पूर्ण
	वापस result;
पूर्ण

अटल __poll_t snd_rawmidi_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा snd_rawmidi_file *rfile;
	काष्ठा snd_rawmidi_runसमय *runसमय;
	__poll_t mask;

	rfile = file->निजी_data;
	अगर (rfile->input != शून्य) अणु
		runसमय = rfile->input->runसमय;
		snd_rawmidi_input_trigger(rfile->input, 1);
		poll_रुको(file, &runसमय->sleep, रुको);
	पूर्ण
	अगर (rfile->output != शून्य) अणु
		runसमय = rfile->output->runसमय;
		poll_रुको(file, &runसमय->sleep, रुको);
	पूर्ण
	mask = 0;
	अगर (rfile->input != शून्य) अणु
		अगर (snd_rawmidi_पढ़ोy(rfile->input))
			mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण
	अगर (rfile->output != शून्य) अणु
		अगर (snd_rawmidi_पढ़ोy(rfile->output))
			mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण
	वापस mask;
पूर्ण

/*
 */
#अगर_घोषित CONFIG_COMPAT
#समावेश "rawmidi_compat.c"
#अन्यथा
#घोषणा snd_rawmidi_ioctl_compat	शून्य
#पूर्ण_अगर

/*
 */

अटल व्योम snd_rawmidi_proc_info_पढ़ो(काष्ठा snd_info_entry *entry,
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *substream;
	काष्ठा snd_rawmidi_runसमय *runसमय;
	अचिन्हित दीर्घ buffer_size, avail, xruns;

	rmidi = entry->निजी_data;
	snd_iम_लिखो(buffer, "%s\n\n", rmidi->name);
	mutex_lock(&rmidi->खोलो_mutex);
	अगर (rmidi->info_flags & SNDRV_RAWMIDI_INFO_OUTPUT) अणु
		list_क्रम_each_entry(substream,
				    &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT].substreams,
				    list) अणु
			snd_iम_लिखो(buffer,
				    "Output %d\n"
				    "  Tx bytes     : %lu\n",
				    substream->number,
				    (अचिन्हित दीर्घ) substream->bytes);
			अगर (substream->खोलोed) अणु
				snd_iम_लिखो(buffer,
				    "  Owner PID    : %d\n",
				    pid_vnr(substream->pid));
				runसमय = substream->runसमय;
				spin_lock_irq(&runसमय->lock);
				buffer_size = runसमय->buffer_size;
				avail = runसमय->avail;
				spin_unlock_irq(&runसमय->lock);
				snd_iम_लिखो(buffer,
				    "  Mode         : %s\n"
				    "  Buffer size  : %lu\n"
				    "  Avail        : %lu\n",
				    runसमय->oss ? "OSS compatible" : "native",
				    buffer_size, avail);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (rmidi->info_flags & SNDRV_RAWMIDI_INFO_INPUT) अणु
		list_क्रम_each_entry(substream,
				    &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT].substreams,
				    list) अणु
			snd_iम_लिखो(buffer,
				    "Input %d\n"
				    "  Rx bytes     : %lu\n",
				    substream->number,
				    (अचिन्हित दीर्घ) substream->bytes);
			अगर (substream->खोलोed) अणु
				snd_iम_लिखो(buffer,
					    "  Owner PID    : %d\n",
					    pid_vnr(substream->pid));
				runसमय = substream->runसमय;
				spin_lock_irq(&runसमय->lock);
				buffer_size = runसमय->buffer_size;
				avail = runसमय->avail;
				xruns = runसमय->xruns;
				spin_unlock_irq(&runसमय->lock);
				snd_iम_लिखो(buffer,
					    "  Buffer size  : %lu\n"
					    "  Avail        : %lu\n"
					    "  Overruns     : %lu\n",
					    buffer_size, avail, xruns);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&rmidi->खोलो_mutex);
पूर्ण

/*
 *  Register functions
 */

अटल स्थिर काष्ठा file_operations snd_rawmidi_f_ops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		snd_rawmidi_पढ़ो,
	.ग_लिखो =	snd_rawmidi_ग_लिखो,
	.खोलो =		snd_rawmidi_खोलो,
	.release =	snd_rawmidi_release,
	.llseek =	no_llseek,
	.poll =		snd_rawmidi_poll,
	.unlocked_ioctl =	snd_rawmidi_ioctl,
	.compat_ioctl =	snd_rawmidi_ioctl_compat,
पूर्ण;

अटल पूर्णांक snd_rawmidi_alloc_substreams(काष्ठा snd_rawmidi *rmidi,
					काष्ठा snd_rawmidi_str *stream,
					पूर्णांक direction,
					पूर्णांक count)
अणु
	काष्ठा snd_rawmidi_substream *substream;
	पूर्णांक idx;

	क्रम (idx = 0; idx < count; idx++) अणु
		substream = kzalloc(माप(*substream), GFP_KERNEL);
		अगर (!substream)
			वापस -ENOMEM;
		substream->stream = direction;
		substream->number = idx;
		substream->rmidi = rmidi;
		substream->pstr = stream;
		list_add_tail(&substream->list, &stream->substreams);
		stream->substream_count++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम release_rawmidi_device(काष्ठा device *dev)
अणु
	kमुक्त(container_of(dev, काष्ठा snd_rawmidi, dev));
पूर्ण

/**
 * snd_rawmidi_new - create a rawmidi instance
 * @card: the card instance
 * @id: the id string
 * @device: the device index
 * @output_count: the number of output streams
 * @input_count: the number of input streams
 * @rrawmidi: the poपूर्णांकer to store the new rawmidi instance
 *
 * Creates a new rawmidi instance.
 * Use snd_rawmidi_set_ops() to set the चालकs to the new instance.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_rawmidi_new(काष्ठा snd_card *card, अक्षर *id, पूर्णांक device,
		    पूर्णांक output_count, पूर्णांक input_count,
		    काष्ठा snd_rawmidi **rrawmidi)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_rawmidi_dev_मुक्त,
		.dev_रेजिस्टर = snd_rawmidi_dev_रेजिस्टर,
		.dev_disconnect = snd_rawmidi_dev_disconnect,
	पूर्ण;

	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;
	अगर (rrawmidi)
		*rrawmidi = शून्य;
	rmidi = kzalloc(माप(*rmidi), GFP_KERNEL);
	अगर (!rmidi)
		वापस -ENOMEM;
	rmidi->card = card;
	rmidi->device = device;
	mutex_init(&rmidi->खोलो_mutex);
	init_रुकोqueue_head(&rmidi->खोलो_रुको);
	INIT_LIST_HEAD(&rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT].substreams);
	INIT_LIST_HEAD(&rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT].substreams);

	अगर (id != शून्य)
		strscpy(rmidi->id, id, माप(rmidi->id));

	snd_device_initialize(&rmidi->dev, card);
	rmidi->dev.release = release_rawmidi_device;
	dev_set_name(&rmidi->dev, "midiC%iD%i", card->number, device);

	err = snd_rawmidi_alloc_substreams(rmidi,
					   &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT],
					   SNDRV_RAWMIDI_STREAM_INPUT,
					   input_count);
	अगर (err < 0)
		जाओ error;
	err = snd_rawmidi_alloc_substreams(rmidi,
					   &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT],
					   SNDRV_RAWMIDI_STREAM_OUTPUT,
					   output_count);
	अगर (err < 0)
		जाओ error;
	err = snd_device_new(card, SNDRV_DEV_RAWMIDI, rmidi, &ops);
	अगर (err < 0)
		जाओ error;

	अगर (rrawmidi)
		*rrawmidi = rmidi;
	वापस 0;

 error:
	snd_rawmidi_मुक्त(rmidi);
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_new);

अटल व्योम snd_rawmidi_मुक्त_substreams(काष्ठा snd_rawmidi_str *stream)
अणु
	काष्ठा snd_rawmidi_substream *substream;

	जबतक (!list_empty(&stream->substreams)) अणु
		substream = list_entry(stream->substreams.next, काष्ठा snd_rawmidi_substream, list);
		list_del(&substream->list);
		kमुक्त(substream);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_rawmidi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	अगर (!rmidi)
		वापस 0;

	snd_info_मुक्त_entry(rmidi->proc_entry);
	rmidi->proc_entry = शून्य;
	mutex_lock(&रेजिस्टर_mutex);
	अगर (rmidi->ops && rmidi->ops->dev_unरेजिस्टर)
		rmidi->ops->dev_unरेजिस्टर(rmidi);
	mutex_unlock(&रेजिस्टर_mutex);

	snd_rawmidi_मुक्त_substreams(&rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT]);
	snd_rawmidi_मुक्त_substreams(&rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT]);
	अगर (rmidi->निजी_मुक्त)
		rmidi->निजी_मुक्त(rmidi);
	put_device(&rmidi->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rawmidi_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_rawmidi *rmidi = device->device_data;

	वापस snd_rawmidi_मुक्त(rmidi);
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
अटल व्योम snd_rawmidi_dev_seq_मुक्त(काष्ठा snd_seq_device *device)
अणु
	काष्ठा snd_rawmidi *rmidi = device->निजी_data;

	rmidi->seq_dev = शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_rawmidi_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	पूर्णांक err;
	काष्ठा snd_info_entry *entry;
	अक्षर name[16];
	काष्ठा snd_rawmidi *rmidi = device->device_data;

	अगर (rmidi->device >= SNDRV_RAWMIDI_DEVICES)
		वापस -ENOMEM;
	err = 0;
	mutex_lock(&रेजिस्टर_mutex);
	अगर (snd_rawmidi_search(rmidi->card, rmidi->device))
		err = -EBUSY;
	अन्यथा
		list_add_tail(&rmidi->list, &snd_rawmidi_devices);
	mutex_unlock(&रेजिस्टर_mutex);
	अगर (err < 0)
		वापस err;

	err = snd_रेजिस्टर_device(SNDRV_DEVICE_TYPE_RAWMIDI,
				  rmidi->card, rmidi->device,
				  &snd_rawmidi_f_ops, rmidi, &rmidi->dev);
	अगर (err < 0) अणु
		rmidi_err(rmidi, "unable to register\n");
		जाओ error;
	पूर्ण
	अगर (rmidi->ops && rmidi->ops->dev_रेजिस्टर) अणु
		err = rmidi->ops->dev_रेजिस्टर(rmidi);
		अगर (err < 0)
			जाओ error_unरेजिस्टर;
	पूर्ण
#अगर_घोषित CONFIG_SND_OSSEMUL
	rmidi->ossreg = 0;
	अगर ((पूर्णांक)rmidi->device == midi_map[rmidi->card->number]) अणु
		अगर (snd_रेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_MIDI,
					    rmidi->card, 0, &snd_rawmidi_f_ops,
					    rmidi) < 0) अणु
			rmidi_err(rmidi,
				  "unable to register OSS rawmidi device %i:%i\n",
				  rmidi->card->number, 0);
		पूर्ण अन्यथा अणु
			rmidi->ossreg++;
#अगर_घोषित SNDRV_OSS_INFO_DEV_MIDI
			snd_oss_info_रेजिस्टर(SNDRV_OSS_INFO_DEV_MIDI, rmidi->card->number, rmidi->name);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	अगर ((पूर्णांक)rmidi->device == amidi_map[rmidi->card->number]) अणु
		अगर (snd_रेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_MIDI,
					    rmidi->card, 1, &snd_rawmidi_f_ops,
					    rmidi) < 0) अणु
			rmidi_err(rmidi,
				  "unable to register OSS rawmidi device %i:%i\n",
				  rmidi->card->number, 1);
		पूर्ण अन्यथा अणु
			rmidi->ossreg++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_SND_OSSEMUL */
	प्र_लिखो(name, "midi%d", rmidi->device);
	entry = snd_info_create_card_entry(rmidi->card, name, rmidi->card->proc_root);
	अगर (entry) अणु
		entry->निजी_data = rmidi;
		entry->c.text.पढ़ो = snd_rawmidi_proc_info_पढ़ो;
		अगर (snd_info_रेजिस्टर(entry) < 0) अणु
			snd_info_मुक्त_entry(entry);
			entry = शून्य;
		पूर्ण
	पूर्ण
	rmidi->proc_entry = entry;
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
	अगर (!rmidi->ops || !rmidi->ops->dev_रेजिस्टर) अणु /* own registration mechanism */
		अगर (snd_seq_device_new(rmidi->card, rmidi->device, SNDRV_SEQ_DEV_ID_MIDISYNTH, 0, &rmidi->seq_dev) >= 0) अणु
			rmidi->seq_dev->निजी_data = rmidi;
			rmidi->seq_dev->निजी_मुक्त = snd_rawmidi_dev_seq_मुक्त;
			प्र_लिखो(rmidi->seq_dev->name, "MIDI %d-%d", rmidi->card->number, rmidi->device);
			snd_device_रेजिस्टर(rmidi->card, rmidi->seq_dev);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;

 error_unरेजिस्टर:
	snd_unरेजिस्टर_device(&rmidi->dev);
 error:
	mutex_lock(&रेजिस्टर_mutex);
	list_del(&rmidi->list);
	mutex_unlock(&रेजिस्टर_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक snd_rawmidi_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा snd_rawmidi *rmidi = device->device_data;
	पूर्णांक dir;

	mutex_lock(&रेजिस्टर_mutex);
	mutex_lock(&rmidi->खोलो_mutex);
	wake_up(&rmidi->खोलो_रुको);
	list_del_init(&rmidi->list);
	क्रम (dir = 0; dir < 2; dir++) अणु
		काष्ठा snd_rawmidi_substream *s;

		list_क्रम_each_entry(s, &rmidi->streams[dir].substreams, list) अणु
			अगर (s->runसमय)
				wake_up(&s->runसमय->sleep);
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_SND_OSSEMUL
	अगर (rmidi->ossreg) अणु
		अगर ((पूर्णांक)rmidi->device == midi_map[rmidi->card->number]) अणु
			snd_unरेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_MIDI, rmidi->card, 0);
#अगर_घोषित SNDRV_OSS_INFO_DEV_MIDI
			snd_oss_info_unरेजिस्टर(SNDRV_OSS_INFO_DEV_MIDI, rmidi->card->number);
#पूर्ण_अगर
		पूर्ण
		अगर ((पूर्णांक)rmidi->device == amidi_map[rmidi->card->number])
			snd_unरेजिस्टर_oss_device(SNDRV_OSS_DEVICE_TYPE_MIDI, rmidi->card, 1);
		rmidi->ossreg = 0;
	पूर्ण
#पूर्ण_अगर /* CONFIG_SND_OSSEMUL */
	snd_unरेजिस्टर_device(&rmidi->dev);
	mutex_unlock(&rmidi->खोलो_mutex);
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण

/**
 * snd_rawmidi_set_ops - set the rawmidi चालकs
 * @rmidi: the rawmidi instance
 * @stream: the stream direction, SNDRV_RAWMIDI_STREAM_XXX
 * @ops: the चालक table
 *
 * Sets the rawmidi चालकs क्रम the given stream direction.
 */
व्योम snd_rawmidi_set_ops(काष्ठा snd_rawmidi *rmidi, पूर्णांक stream,
			 स्थिर काष्ठा snd_rawmidi_ops *ops)
अणु
	काष्ठा snd_rawmidi_substream *substream;

	list_क्रम_each_entry(substream, &rmidi->streams[stream].substreams, list)
		substream->ops = ops;
पूर्ण
EXPORT_SYMBOL(snd_rawmidi_set_ops);

/*
 *  ENTRY functions
 */

अटल पूर्णांक __init alsa_rawmidi_init(व्योम)
अणु

	snd_ctl_रेजिस्टर_ioctl(snd_rawmidi_control_ioctl);
	snd_ctl_रेजिस्टर_ioctl_compat(snd_rawmidi_control_ioctl);
#अगर_घोषित CONFIG_SND_OSSEMUL
	अणु पूर्णांक i;
	/* check device map table */
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		अगर (midi_map[i] < 0 || midi_map[i] >= SNDRV_RAWMIDI_DEVICES) अणु
			pr_err("ALSA: rawmidi: invalid midi_map[%d] = %d\n",
			       i, midi_map[i]);
			midi_map[i] = 0;
		पूर्ण
		अगर (amidi_map[i] < 0 || amidi_map[i] >= SNDRV_RAWMIDI_DEVICES) अणु
			pr_err("ALSA: rawmidi: invalid amidi_map[%d] = %d\n",
			       i, amidi_map[i]);
			amidi_map[i] = 1;
		पूर्ण
	पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_SND_OSSEMUL */
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_rawmidi_निकास(व्योम)
अणु
	snd_ctl_unरेजिस्टर_ioctl(snd_rawmidi_control_ioctl);
	snd_ctl_unरेजिस्टर_ioctl_compat(snd_rawmidi_control_ioctl);
पूर्ण

module_init(alsa_rawmidi_init)
module_निकास(alsa_rawmidi_निकास)

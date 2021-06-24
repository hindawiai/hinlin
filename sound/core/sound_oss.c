<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Advanced Linux Sound Architecture
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/info.h>
#समावेश <linux/sound.h>
#समावेश <linux/mutex.h>

#घोषणा SNDRV_OSS_MINORS 256

अटल काष्ठा snd_minor *snd_oss_minors[SNDRV_OSS_MINORS];
अटल DEFINE_MUTEX(sound_oss_mutex);

/* NOTE: This function increments the refcount of the associated card like
 * snd_lookup_minor_data(); the caller must call snd_card_unref() appropriately
 */
व्योम *snd_lookup_oss_minor_data(अचिन्हित पूर्णांक minor, पूर्णांक type)
अणु
	काष्ठा snd_minor *mreg;
	व्योम *निजी_data;

	अगर (minor >= ARRAY_SIZE(snd_oss_minors))
		वापस शून्य;
	mutex_lock(&sound_oss_mutex);
	mreg = snd_oss_minors[minor];
	अगर (mreg && mreg->type == type) अणु
		निजी_data = mreg->निजी_data;
		अगर (निजी_data && mreg->card_ptr)
			get_device(&mreg->card_ptr->card_dev);
	पूर्ण अन्यथा
		निजी_data = शून्य;
	mutex_unlock(&sound_oss_mutex);
	वापस निजी_data;
पूर्ण
EXPORT_SYMBOL(snd_lookup_oss_minor_data);

अटल पूर्णांक snd_oss_kernel_minor(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev)
अणु
	पूर्णांक minor;

	चयन (type) अणु
	हाल SNDRV_OSS_DEVICE_TYPE_MIXER:
		अगर (snd_BUG_ON(!card || dev < 0 || dev > 1))
			वापस -EINVAL;
		minor = SNDRV_MINOR_OSS(card->number, (dev ? SNDRV_MINOR_OSS_MIXER1 : SNDRV_MINOR_OSS_MIXER));
		अवरोध;
	हाल SNDRV_OSS_DEVICE_TYPE_SEQUENCER:
		minor = SNDRV_MINOR_OSS_SEQUENCER;
		अवरोध;
	हाल SNDRV_OSS_DEVICE_TYPE_MUSIC:
		minor = SNDRV_MINOR_OSS_MUSIC;
		अवरोध;
	हाल SNDRV_OSS_DEVICE_TYPE_PCM:
		अगर (snd_BUG_ON(!card || dev < 0 || dev > 1))
			वापस -EINVAL;
		minor = SNDRV_MINOR_OSS(card->number, (dev ? SNDRV_MINOR_OSS_PCM1 : SNDRV_MINOR_OSS_PCM));
		अवरोध;
	हाल SNDRV_OSS_DEVICE_TYPE_MIDI:
		अगर (snd_BUG_ON(!card || dev < 0 || dev > 1))
			वापस -EINVAL;
		minor = SNDRV_MINOR_OSS(card->number, (dev ? SNDRV_MINOR_OSS_MIDI1 : SNDRV_MINOR_OSS_MIDI));
		अवरोध;
	हाल SNDRV_OSS_DEVICE_TYPE_DMFM:
		minor = SNDRV_MINOR_OSS(card->number, SNDRV_MINOR_OSS_DMFM);
		अवरोध;
	हाल SNDRV_OSS_DEVICE_TYPE_SNDSTAT:
		minor = SNDRV_MINOR_OSS_SNDSTAT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (minor < 0 || minor >= SNDRV_OSS_MINORS)
		वापस -EINVAL;
	वापस minor;
पूर्ण

पूर्णांक snd_रेजिस्टर_oss_device(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev,
			    स्थिर काष्ठा file_operations *f_ops, व्योम *निजी_data)
अणु
	पूर्णांक minor = snd_oss_kernel_minor(type, card, dev);
	पूर्णांक minor_unit;
	काष्ठा snd_minor *preg;
	पूर्णांक cidx = SNDRV_MINOR_OSS_CARD(minor);
	पूर्णांक track2 = -1;
	पूर्णांक रेजिस्टर1 = -1, रेजिस्टर2 = -1;
	काष्ठा device *carddev = snd_card_get_device_link(card);

	अगर (card && card->number >= SNDRV_MINOR_OSS_DEVICES)
		वापस 0; /* ignore silently */
	अगर (minor < 0)
		वापस minor;
	preg = kदो_स्मृति(माप(काष्ठा snd_minor), GFP_KERNEL);
	अगर (preg == शून्य)
		वापस -ENOMEM;
	preg->type = type;
	preg->card = card ? card->number : -1;
	preg->device = dev;
	preg->f_ops = f_ops;
	preg->निजी_data = निजी_data;
	preg->card_ptr = card;
	mutex_lock(&sound_oss_mutex);
	snd_oss_minors[minor] = preg;
	minor_unit = SNDRV_MINOR_OSS_DEVICE(minor);
	चयन (minor_unit) अणु
	हाल SNDRV_MINOR_OSS_PCM:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_AUDIO);
		अवरोध;
	हाल SNDRV_MINOR_OSS_MIDI:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_DMMIDI);
		अवरोध;
	हाल SNDRV_MINOR_OSS_MIDI1:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_DMMIDI1);
		अवरोध;
	पूर्ण
	रेजिस्टर1 = रेजिस्टर_sound_special_device(f_ops, minor, carddev);
	अगर (रेजिस्टर1 != minor)
		जाओ __end;
	अगर (track2 >= 0) अणु
		रेजिस्टर2 = रेजिस्टर_sound_special_device(f_ops, track2,
							  carddev);
		अगर (रेजिस्टर2 != track2)
			जाओ __end;
		snd_oss_minors[track2] = preg;
	पूर्ण
	mutex_unlock(&sound_oss_mutex);
	वापस 0;

      __end:
      	अगर (रेजिस्टर2 >= 0)
      		unरेजिस्टर_sound_special(रेजिस्टर2);
      	अगर (रेजिस्टर1 >= 0)
      		unरेजिस्टर_sound_special(रेजिस्टर1);
	snd_oss_minors[minor] = शून्य;
	mutex_unlock(&sound_oss_mutex);
	kमुक्त(preg);
      	वापस -EBUSY;
पूर्ण
EXPORT_SYMBOL(snd_रेजिस्टर_oss_device);

पूर्णांक snd_unरेजिस्टर_oss_device(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev)
अणु
	पूर्णांक minor = snd_oss_kernel_minor(type, card, dev);
	पूर्णांक cidx = SNDRV_MINOR_OSS_CARD(minor);
	पूर्णांक track2 = -1;
	काष्ठा snd_minor *mptr;

	अगर (card && card->number >= SNDRV_MINOR_OSS_DEVICES)
		वापस 0;
	अगर (minor < 0)
		वापस minor;
	mutex_lock(&sound_oss_mutex);
	mptr = snd_oss_minors[minor];
	अगर (mptr == शून्य) अणु
		mutex_unlock(&sound_oss_mutex);
		वापस -ENOENT;
	पूर्ण
	unरेजिस्टर_sound_special(minor);
	चयन (SNDRV_MINOR_OSS_DEVICE(minor)) अणु
	हाल SNDRV_MINOR_OSS_PCM:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_AUDIO);
		अवरोध;
	हाल SNDRV_MINOR_OSS_MIDI:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_DMMIDI);
		अवरोध;
	हाल SNDRV_MINOR_OSS_MIDI1:
		track2 = SNDRV_MINOR_OSS(cidx, SNDRV_MINOR_OSS_DMMIDI1);
		अवरोध;
	पूर्ण
	अगर (track2 >= 0) अणु
		unरेजिस्टर_sound_special(track2);
		snd_oss_minors[track2] = शून्य;
	पूर्ण
	snd_oss_minors[minor] = शून्य;
	mutex_unlock(&sound_oss_mutex);
	kमुक्त(mptr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_unरेजिस्टर_oss_device);

/*
 *  INFO PART
 */

#अगर_घोषित CONFIG_SND_PROC_FS
अटल स्थिर अक्षर *snd_oss_device_type_name(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल SNDRV_OSS_DEVICE_TYPE_MIXER:
		वापस "mixer";
	हाल SNDRV_OSS_DEVICE_TYPE_SEQUENCER:
	हाल SNDRV_OSS_DEVICE_TYPE_MUSIC:
		वापस "sequencer";
	हाल SNDRV_OSS_DEVICE_TYPE_PCM:
		वापस "digital audio";
	हाल SNDRV_OSS_DEVICE_TYPE_MIDI:
		वापस "raw midi";
	हाल SNDRV_OSS_DEVICE_TYPE_DMFM:
		वापस "hardware dependent";
	शेष:
		वापस "?";
	पूर्ण
पूर्ण

अटल व्योम snd_minor_info_oss_पढ़ो(काष्ठा snd_info_entry *entry,
				    काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक minor;
	काष्ठा snd_minor *mptr;

	mutex_lock(&sound_oss_mutex);
	क्रम (minor = 0; minor < SNDRV_OSS_MINORS; ++minor) अणु
		अगर (!(mptr = snd_oss_minors[minor]))
			जारी;
		अगर (mptr->card >= 0)
			snd_iम_लिखो(buffer, "%3i: [%i-%2i]: %s\n", minor,
				    mptr->card, mptr->device,
				    snd_oss_device_type_name(mptr->type));
		अन्यथा
			snd_iम_लिखो(buffer, "%3i:       : %s\n", minor,
				    snd_oss_device_type_name(mptr->type));
	पूर्ण
	mutex_unlock(&sound_oss_mutex);
पूर्ण


पूर्णांक __init snd_minor_info_oss_init(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(THIS_MODULE, "devices", snd_oss_root);
	अगर (!entry)
		वापस -ENOMEM;
	entry->c.text.पढ़ो = snd_minor_info_oss_पढ़ो;
	वापस snd_info_रेजिस्टर(entry); /* मुक्तd in error path */
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

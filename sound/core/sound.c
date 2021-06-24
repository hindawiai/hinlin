<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Advanced Linux Sound Architecture
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <linux/kmod.h>
#समावेश <linux/mutex.h>

अटल पूर्णांक major = CONFIG_SND_MAJOR;
पूर्णांक snd_major;
EXPORT_SYMBOL(snd_major);

अटल पूर्णांक cards_limit = 1;

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Advanced Linux Sound Architecture driver for soundcards.");
MODULE_LICENSE("GPL");
module_param(major, पूर्णांक, 0444);
MODULE_PARM_DESC(major, "Major # for sound driver.");
module_param(cards_limit, पूर्णांक, 0444);
MODULE_PARM_DESC(cards_limit, "Count of auto-loadable soundcards.");
MODULE_ALIAS_CHARDEV_MAJOR(CONFIG_SND_MAJOR);

/* this one holds the actual max. card number currently available.
 * as शेष, it's identical with cards_limit option.  when more
 * modules are loaded manually, this limit number increases, too.
 */
पूर्णांक snd_ecards_limit;
EXPORT_SYMBOL(snd_ecards_limit);

#अगर_घोषित CONFIG_SND_DEBUG
काष्ठा dentry *sound_debugfs_root;
EXPORT_SYMBOL_GPL(sound_debugfs_root);
#पूर्ण_अगर

अटल काष्ठा snd_minor *snd_minors[SNDRV_OS_MINORS];
अटल DEFINE_MUTEX(sound_mutex);

#अगर_घोषित CONFIG_MODULES

/**
 * snd_request_card - try to load the card module
 * @card: the card number
 *
 * Tries to load the module "snd-card-X" क्रम the given card number
 * via request_module.  Returns immediately अगर alपढ़ोy loaded.
 */
व्योम snd_request_card(पूर्णांक card)
अणु
	अगर (snd_card_locked(card))
		वापस;
	अगर (card < 0 || card >= cards_limit)
		वापस;
	request_module("snd-card-%i", card);
पूर्ण
EXPORT_SYMBOL(snd_request_card);

अटल व्योम snd_request_other(पूर्णांक minor)
अणु
	अक्षर *str;

	चयन (minor) अणु
	हाल SNDRV_MINOR_SEQUENCER:	str = "snd-seq";	अवरोध;
	हाल SNDRV_MINOR_TIMER:		str = "snd-timer";	अवरोध;
	शेष:			वापस;
	पूर्ण
	request_module(str);
पूर्ण

#पूर्ण_अगर	/* modular kernel */

/**
 * snd_lookup_minor_data - get user data of a रेजिस्टरed device
 * @minor: the minor number
 * @type: device type (SNDRV_DEVICE_TYPE_XXX)
 *
 * Checks that a minor device with the specअगरied type is रेजिस्टरed, and वापसs
 * its user data poपूर्णांकer.
 *
 * This function increments the reference counter of the card instance
 * अगर an associated instance with the given minor number and type is found.
 * The caller must call snd_card_unref() appropriately later.
 *
 * Return: The user data poपूर्णांकer अगर the specअगरied device is found. %शून्य
 * otherwise.
 */
व्योम *snd_lookup_minor_data(अचिन्हित पूर्णांक minor, पूर्णांक type)
अणु
	काष्ठा snd_minor *mreg;
	व्योम *निजी_data;

	अगर (minor >= ARRAY_SIZE(snd_minors))
		वापस शून्य;
	mutex_lock(&sound_mutex);
	mreg = snd_minors[minor];
	अगर (mreg && mreg->type == type) अणु
		निजी_data = mreg->निजी_data;
		अगर (निजी_data && mreg->card_ptr)
			get_device(&mreg->card_ptr->card_dev);
	पूर्ण अन्यथा
		निजी_data = शून्य;
	mutex_unlock(&sound_mutex);
	वापस निजी_data;
पूर्ण
EXPORT_SYMBOL(snd_lookup_minor_data);

#अगर_घोषित CONFIG_MODULES
अटल काष्ठा snd_minor *स्वतःload_device(अचिन्हित पूर्णांक minor)
अणु
	पूर्णांक dev;
	mutex_unlock(&sound_mutex); /* release lock temporarily */
	dev = SNDRV_MINOR_DEVICE(minor);
	अगर (dev == SNDRV_MINOR_CONTROL) अणु
		/* /dev/aloadC? */
		पूर्णांक card = SNDRV_MINOR_CARD(minor);
		काष्ठा snd_card *ref = snd_card_ref(card);
		अगर (!ref)
			snd_request_card(card);
		अन्यथा
			snd_card_unref(ref);
	पूर्ण अन्यथा अगर (dev == SNDRV_MINOR_GLOBAL) अणु
		/* /dev/aloadSEQ */
		snd_request_other(minor);
	पूर्ण
	mutex_lock(&sound_mutex); /* reacuire lock */
	वापस snd_minors[minor];
पूर्ण
#अन्यथा /* !CONFIG_MODULES */
#घोषणा स्वतःload_device(minor)	शून्य
#पूर्ण_अगर /* CONFIG_MODULES */

अटल पूर्णांक snd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा snd_minor *mptr = शून्य;
	स्थिर काष्ठा file_operations *new_fops;
	पूर्णांक err = 0;

	अगर (minor >= ARRAY_SIZE(snd_minors))
		वापस -ENODEV;
	mutex_lock(&sound_mutex);
	mptr = snd_minors[minor];
	अगर (mptr == शून्य) अणु
		mptr = स्वतःload_device(minor);
		अगर (!mptr) अणु
			mutex_unlock(&sound_mutex);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	new_fops = fops_get(mptr->f_ops);
	mutex_unlock(&sound_mutex);
	अगर (!new_fops)
		वापस -ENODEV;
	replace_fops(file, new_fops);

	अगर (file->f_op->खोलो)
		err = file->f_op->खोलो(inode, file);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations snd_fops =
अणु
	.owner =	THIS_MODULE,
	.खोलो =		snd_खोलो,
	.llseek =	noop_llseek,
पूर्ण;

#अगर_घोषित CONFIG_SND_DYNAMIC_MINORS
अटल पूर्णांक snd_find_मुक्त_minor(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev)
अणु
	पूर्णांक minor;

	/* अटल minors क्रम module स्वतः loading */
	अगर (type == SNDRV_DEVICE_TYPE_SEQUENCER)
		वापस SNDRV_MINOR_SEQUENCER;
	अगर (type == SNDRV_DEVICE_TYPE_TIMER)
		वापस SNDRV_MINOR_TIMER;

	क्रम (minor = 0; minor < ARRAY_SIZE(snd_minors); ++minor) अणु
		/* skip अटल minors still used क्रम module स्वतः loading */
		अगर (SNDRV_MINOR_DEVICE(minor) == SNDRV_MINOR_CONTROL)
			जारी;
		अगर (minor == SNDRV_MINOR_SEQUENCER ||
		    minor == SNDRV_MINOR_TIMER)
			जारी;
		अगर (!snd_minors[minor])
			वापस minor;
	पूर्ण
	वापस -EBUSY;
पूर्ण
#अन्यथा
अटल पूर्णांक snd_find_मुक्त_minor(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev)
अणु
	पूर्णांक minor;

	चयन (type) अणु
	हाल SNDRV_DEVICE_TYPE_SEQUENCER:
	हाल SNDRV_DEVICE_TYPE_TIMER:
		minor = type;
		अवरोध;
	हाल SNDRV_DEVICE_TYPE_CONTROL:
		अगर (snd_BUG_ON(!card))
			वापस -EINVAL;
		minor = SNDRV_MINOR(card->number, type);
		अवरोध;
	हाल SNDRV_DEVICE_TYPE_HWDEP:
	हाल SNDRV_DEVICE_TYPE_RAWMIDI:
	हाल SNDRV_DEVICE_TYPE_PCM_PLAYBACK:
	हाल SNDRV_DEVICE_TYPE_PCM_CAPTURE:
	हाल SNDRV_DEVICE_TYPE_COMPRESS:
		अगर (snd_BUG_ON(!card))
			वापस -EINVAL;
		minor = SNDRV_MINOR(card->number, type + dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (snd_BUG_ON(minor < 0 || minor >= SNDRV_OS_MINORS))
		वापस -EINVAL;
	अगर (snd_minors[minor])
		वापस -EBUSY;
	वापस minor;
पूर्ण
#पूर्ण_अगर

/**
 * snd_रेजिस्टर_device - Register the ALSA device file क्रम the card
 * @type: the device type, SNDRV_DEVICE_TYPE_XXX
 * @card: the card instance
 * @dev: the device index
 * @f_ops: the file operations
 * @निजी_data: user poपूर्णांकer क्रम f_ops->खोलो()
 * @device: the device to रेजिस्टर
 *
 * Registers an ALSA device file क्रम the given card.
 * The चालकs have to be set in reg parameter.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_रेजिस्टर_device(पूर्णांक type, काष्ठा snd_card *card, पूर्णांक dev,
			स्थिर काष्ठा file_operations *f_ops,
			व्योम *निजी_data, काष्ठा device *device)
अणु
	पूर्णांक minor;
	पूर्णांक err = 0;
	काष्ठा snd_minor *preg;

	अगर (snd_BUG_ON(!device))
		वापस -EINVAL;

	preg = kदो_स्मृति(माप *preg, GFP_KERNEL);
	अगर (preg == शून्य)
		वापस -ENOMEM;
	preg->type = type;
	preg->card = card ? card->number : -1;
	preg->device = dev;
	preg->f_ops = f_ops;
	preg->निजी_data = निजी_data;
	preg->card_ptr = card;
	mutex_lock(&sound_mutex);
	minor = snd_find_मुक्त_minor(type, card, dev);
	अगर (minor < 0) अणु
		err = minor;
		जाओ error;
	पूर्ण

	preg->dev = device;
	device->devt = MKDEV(major, minor);
	err = device_add(device);
	अगर (err < 0)
		जाओ error;

	snd_minors[minor] = preg;
 error:
	mutex_unlock(&sound_mutex);
	अगर (err < 0)
		kमुक्त(preg);
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_रेजिस्टर_device);

/**
 * snd_unरेजिस्टर_device - unरेजिस्टर the device on the given card
 * @dev: the device instance
 *
 * Unरेजिस्टरs the device file alपढ़ोy रेजिस्टरed via
 * snd_रेजिस्टर_device().
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_unरेजिस्टर_device(काष्ठा device *dev)
अणु
	पूर्णांक minor;
	काष्ठा snd_minor *preg;

	mutex_lock(&sound_mutex);
	क्रम (minor = 0; minor < ARRAY_SIZE(snd_minors); ++minor) अणु
		preg = snd_minors[minor];
		अगर (preg && preg->dev == dev) अणु
			snd_minors[minor] = शून्य;
			device_del(dev);
			kमुक्त(preg);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&sound_mutex);
	अगर (minor >= ARRAY_SIZE(snd_minors))
		वापस -ENOENT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_unरेजिस्टर_device);

#अगर_घोषित CONFIG_SND_PROC_FS
/*
 *  INFO PART
 */
अटल स्थिर अक्षर *snd_device_type_name(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल SNDRV_DEVICE_TYPE_CONTROL:
		वापस "control";
	हाल SNDRV_DEVICE_TYPE_HWDEP:
		वापस "hardware dependent";
	हाल SNDRV_DEVICE_TYPE_RAWMIDI:
		वापस "raw midi";
	हाल SNDRV_DEVICE_TYPE_PCM_PLAYBACK:
		वापस "digital audio playback";
	हाल SNDRV_DEVICE_TYPE_PCM_CAPTURE:
		वापस "digital audio capture";
	हाल SNDRV_DEVICE_TYPE_SEQUENCER:
		वापस "sequencer";
	हाल SNDRV_DEVICE_TYPE_TIMER:
		वापस "timer";
	हाल SNDRV_DEVICE_TYPE_COMPRESS:
		वापस "compress";
	शेष:
		वापस "?";
	पूर्ण
पूर्ण

अटल व्योम snd_minor_info_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक minor;
	काष्ठा snd_minor *mptr;

	mutex_lock(&sound_mutex);
	क्रम (minor = 0; minor < SNDRV_OS_MINORS; ++minor) अणु
		अगर (!(mptr = snd_minors[minor]))
			जारी;
		अगर (mptr->card >= 0) अणु
			अगर (mptr->device >= 0)
				snd_iम_लिखो(buffer, "%3i: [%2i-%2i]: %s\n",
					    minor, mptr->card, mptr->device,
					    snd_device_type_name(mptr->type));
			अन्यथा
				snd_iम_लिखो(buffer, "%3i: [%2i]   : %s\n",
					    minor, mptr->card,
					    snd_device_type_name(mptr->type));
		पूर्ण अन्यथा
			snd_iम_लिखो(buffer, "%3i:        : %s\n", minor,
				    snd_device_type_name(mptr->type));
	पूर्ण
	mutex_unlock(&sound_mutex);
पूर्ण

पूर्णांक __init snd_minor_info_init(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(THIS_MODULE, "devices", शून्य);
	अगर (!entry)
		वापस -ENOMEM;
	entry->c.text.पढ़ो = snd_minor_info_पढ़ो;
	वापस snd_info_रेजिस्टर(entry); /* मुक्तd in error path */
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

/*
 *  INIT PART
 */

अटल पूर्णांक __init alsa_sound_init(व्योम)
अणु
	snd_major = major;
	snd_ecards_limit = cards_limit;
	अगर (रेजिस्टर_chrdev(major, "alsa", &snd_fops)) अणु
		pr_err("ALSA core: unable to register native major device number %d\n", major);
		वापस -EIO;
	पूर्ण
	अगर (snd_info_init() < 0) अणु
		unरेजिस्टर_chrdev(major, "alsa");
		वापस -ENOMEM;
	पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG
	sound_debugfs_root = debugfs_create_dir("sound", शून्य);
#पूर्ण_अगर
#अगर_अघोषित MODULE
	pr_info("Advanced Linux Sound Architecture Driver Initialized.\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_sound_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_SND_DEBUG
	debugfs_हटाओ(sound_debugfs_root);
#पूर्ण_अगर
	snd_info_करोne();
	unरेजिस्टर_chrdev(major, "alsa");
पूर्ण

subsys_initcall(alsa_sound_init);
module_निकास(alsa_sound_निकास);

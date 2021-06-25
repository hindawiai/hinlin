<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Initialization routines
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/pm.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>

/* monitor files क्रम graceful shutकरोwn (hotplug) */
काष्ठा snd_monitor_file अणु
	काष्ठा file *file;
	स्थिर काष्ठा file_operations *disconnected_f_op;
	काष्ठा list_head shutकरोwn_list;	/* still need to shutकरोwn */
	काष्ठा list_head list;	/* link of monitor files */
पूर्ण;

अटल DEFINE_SPINLOCK(shutकरोwn_lock);
अटल LIST_HEAD(shutकरोwn_files);

अटल स्थिर काष्ठा file_operations snd_shutकरोwn_f_ops;

/* locked क्रम रेजिस्टरing/using */
अटल DECLARE_BITMAP(snd_cards_lock, SNDRV_CARDS);
अटल काष्ठा snd_card *snd_cards[SNDRV_CARDS];

अटल DEFINE_MUTEX(snd_card_mutex);

अटल अक्षर *slots[SNDRV_CARDS];
module_param_array(slots, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(slots, "Module names assigned to the slots.");

/* वापस non-zero अगर the given index is reserved क्रम the given
 * module via slots option
 */
अटल पूर्णांक module_slot_match(काष्ठा module *module, पूर्णांक idx)
अणु
	पूर्णांक match = 1;
#अगर_घोषित MODULE
	स्थिर अक्षर *s1, *s2;

	अगर (!module || !*module->name || !slots[idx])
		वापस 0;

	s1 = module->name;
	s2 = slots[idx];
	अगर (*s2 == '!') अणु
		match = 0; /* negative match */
		s2++;
	पूर्ण
	/* compare module name strings
	 * hyphens are handled as equivalent with underscore
	 */
	क्रम (;;) अणु
		अक्षर c1 = *s1++;
		अक्षर c2 = *s2++;
		अगर (c1 == '-')
			c1 = '_';
		अगर (c2 == '-')
			c2 = '_';
		अगर (c1 != c2)
			वापस !match;
		अगर (!c1)
			अवरोध;
	पूर्ण
#पूर्ण_अगर /* MODULE */
	वापस match;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_MIXER_OSS)
पूर्णांक (*snd_mixer_oss_notअगरy_callback)(काष्ठा snd_card *card, पूर्णांक मुक्त_flag);
EXPORT_SYMBOL(snd_mixer_oss_notअगरy_callback);
#पूर्ण_अगर

अटल पूर्णांक check_empty_slot(काष्ठा module *module, पूर्णांक slot)
अणु
	वापस !slots[slot] || !*slots[slot];
पूर्ण

/* वापस an empty slot number (>= 0) found in the given biपंचांगask @mask.
 * @mask == -1 == 0xffffffff means: take any मुक्त slot up to 32
 * when no slot is available, वापस the original @mask as is.
 */
अटल पूर्णांक get_slot_from_biपंचांगask(पूर्णांक mask, पूर्णांक (*check)(काष्ठा module *, पूर्णांक),
				 काष्ठा module *module)
अणु
	पूर्णांक slot;

	क्रम (slot = 0; slot < SNDRV_CARDS; slot++) अणु
		अगर (slot < 32 && !(mask & (1U << slot)))
			जारी;
		अगर (!test_bit(slot, snd_cards_lock)) अणु
			अगर (check(module, slot))
				वापस slot; /* found */
		पूर्ण
	पूर्ण
	वापस mask; /* unchanged */
पूर्ण

/* the शेष release callback set in snd_device_initialize() below;
 * this is just NOP क्रम now, as almost all jobs are alपढ़ोy करोne in
 * dev_मुक्त callback of snd_device chain instead.
 */
अटल व्योम शेष_release(काष्ठा device *dev)
अणु
पूर्ण

/**
 * snd_device_initialize - Initialize काष्ठा device क्रम sound devices
 * @dev: device to initialize
 * @card: card to assign, optional
 */
व्योम snd_device_initialize(काष्ठा device *dev, काष्ठा snd_card *card)
अणु
	device_initialize(dev);
	अगर (card)
		dev->parent = &card->card_dev;
	dev->class = sound_class;
	dev->release = शेष_release;
पूर्ण
EXPORT_SYMBOL_GPL(snd_device_initialize);

अटल पूर्णांक snd_card_करो_मुक्त(काष्ठा snd_card *card);
अटल स्थिर काष्ठा attribute_group card_dev_attr_group;

अटल व्योम release_card_device(काष्ठा device *dev)
अणु
	snd_card_करो_मुक्त(dev_to_snd_card(dev));
पूर्ण

/**
 *  snd_card_new - create and initialize a soundcard काष्ठाure
 *  @parent: the parent device object
 *  @idx: card index (address) [0 ... (SNDRV_CARDS-1)]
 *  @xid: card identअगरication (ASCII string)
 *  @module: top level module क्रम locking
 *  @extra_size: allocate this extra size after the मुख्य soundcard काष्ठाure
 *  @card_ret: the poपूर्णांकer to store the created card instance
 *
 *  The function allocates snd_card instance via kzalloc with the given
 *  space क्रम the driver to use मुक्तly.  The allocated काष्ठा is stored
 *  in the given card_ret poपूर्णांकer.
 *
 *  Return: Zero अगर successful or a negative error code.
 */
पूर्णांक snd_card_new(काष्ठा device *parent, पूर्णांक idx, स्थिर अक्षर *xid,
		    काष्ठा module *module, पूर्णांक extra_size,
		    काष्ठा snd_card **card_ret)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;
#अगर_घोषित CONFIG_SND_DEBUG
	अक्षर name[8];
#पूर्ण_अगर

	अगर (snd_BUG_ON(!card_ret))
		वापस -EINVAL;
	*card_ret = शून्य;

	अगर (extra_size < 0)
		extra_size = 0;
	card = kzalloc(माप(*card) + extra_size, GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;
	अगर (extra_size > 0)
		card->निजी_data = (अक्षर *)card + माप(काष्ठा snd_card);
	अगर (xid)
		strscpy(card->id, xid, माप(card->id));
	err = 0;
	mutex_lock(&snd_card_mutex);
	अगर (idx < 0) /* first check the matching module-name slot */
		idx = get_slot_from_biपंचांगask(idx, module_slot_match, module);
	अगर (idx < 0) /* अगर not matched, assign an empty slot */
		idx = get_slot_from_biपंचांगask(idx, check_empty_slot, module);
	अगर (idx < 0)
		err = -ENODEV;
	अन्यथा अगर (idx < snd_ecards_limit) अणु
		अगर (test_bit(idx, snd_cards_lock))
			err = -EBUSY;	/* invalid */
	पूर्ण अन्यथा अगर (idx >= SNDRV_CARDS)
		err = -ENODEV;
	अगर (err < 0) अणु
		mutex_unlock(&snd_card_mutex);
		dev_err(parent, "cannot find the slot for index %d (range 0-%i), error: %d\n",
			 idx, snd_ecards_limit - 1, err);
		kमुक्त(card);
		वापस err;
	पूर्ण
	set_bit(idx, snd_cards_lock);		/* lock it */
	अगर (idx >= snd_ecards_limit)
		snd_ecards_limit = idx + 1; /* increase the limit */
	mutex_unlock(&snd_card_mutex);
	card->dev = parent;
	card->number = idx;
#अगर_घोषित MODULE
	WARN_ON(!module);
	card->module = module;
#पूर्ण_अगर
	INIT_LIST_HEAD(&card->devices);
	init_rwsem(&card->controls_rwsem);
	rwlock_init(&card->ctl_files_rwlock);
	INIT_LIST_HEAD(&card->controls);
	INIT_LIST_HEAD(&card->ctl_files);
	spin_lock_init(&card->files_lock);
	INIT_LIST_HEAD(&card->files_list);
	mutex_init(&card->memory_mutex);
#अगर_घोषित CONFIG_PM
	init_रुकोqueue_head(&card->घातer_sleep);
#पूर्ण_अगर
	init_रुकोqueue_head(&card->हटाओ_sleep);
	card->sync_irq = -1;

	device_initialize(&card->card_dev);
	card->card_dev.parent = parent;
	card->card_dev.class = sound_class;
	card->card_dev.release = release_card_device;
	card->card_dev.groups = card->dev_groups;
	card->dev_groups[0] = &card_dev_attr_group;
	err = kobject_set_name(&card->card_dev.kobj, "card%d", idx);
	अगर (err < 0)
		जाओ __error;

	snम_लिखो(card->irq_descr, माप(card->irq_descr), "%s:%s",
		 dev_driver_string(card->dev), dev_name(&card->card_dev));

	/* the control पूर्णांकerface cannot be accessed from the user space until */
	/* snd_cards_biपंचांगask and snd_cards are set with snd_card_रेजिस्टर */
	err = snd_ctl_create(card);
	अगर (err < 0) अणु
		dev_err(parent, "unable to register control minors\n");
		जाओ __error;
	पूर्ण
	err = snd_info_card_create(card);
	अगर (err < 0) अणु
		dev_err(parent, "unable to create card info\n");
		जाओ __error_ctl;
	पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG
	प्र_लिखो(name, "card%d", idx);
	card->debugfs_root = debugfs_create_dir(name, sound_debugfs_root);
#पूर्ण_अगर

	*card_ret = card;
	वापस 0;

      __error_ctl:
	snd_device_मुक्त_all(card);
      __error:
	put_device(&card->card_dev);
  	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_card_new);

/**
 * snd_card_ref - Get the card object from the index
 * @idx: the card index
 *
 * Returns a card object corresponding to the given index or शून्य अगर not found.
 * Release the object via snd_card_unref().
 */
काष्ठा snd_card *snd_card_ref(पूर्णांक idx)
अणु
	काष्ठा snd_card *card;

	mutex_lock(&snd_card_mutex);
	card = snd_cards[idx];
	अगर (card)
		get_device(&card->card_dev);
	mutex_unlock(&snd_card_mutex);
	वापस card;
पूर्ण
EXPORT_SYMBOL_GPL(snd_card_ref);

/* वापस non-zero अगर a card is alपढ़ोy locked */
पूर्णांक snd_card_locked(पूर्णांक card)
अणु
	पूर्णांक locked;

	mutex_lock(&snd_card_mutex);
	locked = test_bit(card, snd_cards_lock);
	mutex_unlock(&snd_card_mutex);
	वापस locked;
पूर्ण

अटल loff_t snd_disconnect_llseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	वापस -ENODEV;
पूर्ण

अटल sमाप_प्रकार snd_disconnect_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *offset)
अणु
	वापस -ENODEV;
पूर्ण

अटल sमाप_प्रकार snd_disconnect_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *offset)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_disconnect_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_monitor_file *df = शून्य, *_df;

	spin_lock(&shutकरोwn_lock);
	list_क्रम_each_entry(_df, &shutकरोwn_files, shutकरोwn_list) अणु
		अगर (_df->file == file) अणु
			df = _df;
			list_del_init(&df->shutकरोwn_list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&shutकरोwn_lock);

	अगर (likely(df)) अणु
		अगर ((file->f_flags & FASYNC) && df->disconnected_f_op->fasync)
			df->disconnected_f_op->fasync(-1, file, 0);
		वापस df->disconnected_f_op->release(inode, file);
	पूर्ण

	panic("%s(%p, %p) failed!", __func__, inode, file);
पूर्ण

अटल __poll_t snd_disconnect_poll(काष्ठा file * file, poll_table * रुको)
अणु
	वापस EPOLLERR | EPOLLNVAL;
पूर्ण

अटल दीर्घ snd_disconnect_ioctl(काष्ठा file *file,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_disconnect_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_disconnect_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा file_operations snd_shutकरोwn_f_ops =
अणु
	.owner = 	THIS_MODULE,
	.llseek =	snd_disconnect_llseek,
	.पढ़ो = 	snd_disconnect_पढ़ो,
	.ग_लिखो =	snd_disconnect_ग_लिखो,
	.release =	snd_disconnect_release,
	.poll =		snd_disconnect_poll,
	.unlocked_ioctl = snd_disconnect_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = snd_disconnect_ioctl,
#पूर्ण_अगर
	.mmap =		snd_disconnect_mmap,
	.fasync =	snd_disconnect_fasync
पूर्ण;

/**
 *  snd_card_disconnect - disconnect all APIs from the file-operations (user space)
 *  @card: soundcard काष्ठाure
 *
 *  Disconnects all APIs from the file-operations (user space).
 *
 *  Return: Zero, otherwise a negative error code.
 *
 *  Note: The current implementation replaces all active file->f_op with special
 *        dummy file operations (they करो nothing except release).
 */
पूर्णांक snd_card_disconnect(काष्ठा snd_card *card)
अणु
	काष्ठा snd_monitor_file *mfile;

	अगर (!card)
		वापस -EINVAL;

	spin_lock(&card->files_lock);
	अगर (card->shutकरोwn) अणु
		spin_unlock(&card->files_lock);
		वापस 0;
	पूर्ण
	card->shutकरोwn = 1;

	/* replace file->f_op with special dummy operations */
	list_क्रम_each_entry(mfile, &card->files_list, list) अणु
		/* it's critical part, use endless loop */
		/* we have no room to fail */
		mfile->disconnected_f_op = mfile->file->f_op;

		spin_lock(&shutकरोwn_lock);
		list_add(&mfile->shutकरोwn_list, &shutकरोwn_files);
		spin_unlock(&shutकरोwn_lock);

		mfile->file->f_op = &snd_shutकरोwn_f_ops;
		fops_get(mfile->file->f_op);
	पूर्ण
	spin_unlock(&card->files_lock);	

	/* notअगरy all connected devices about disconnection */
	/* at this poपूर्णांक, they cannot respond to any calls except release() */

#अगर IS_ENABLED(CONFIG_SND_MIXER_OSS)
	अगर (snd_mixer_oss_notअगरy_callback)
		snd_mixer_oss_notअगरy_callback(card, SND_MIXER_OSS_NOTIFY_DISCONNECT);
#पूर्ण_अगर

	/* notअगरy all devices that we are disconnected */
	snd_device_disconnect_all(card);

	अगर (card->sync_irq > 0)
		synchronize_irq(card->sync_irq);

	snd_info_card_disconnect(card);
	अगर (card->रेजिस्टरed) अणु
		device_del(&card->card_dev);
		card->रेजिस्टरed = false;
	पूर्ण

	/* disable fops (user space) operations क्रम ALSA API */
	mutex_lock(&snd_card_mutex);
	snd_cards[card->number] = शून्य;
	clear_bit(card->number, snd_cards_lock);
	mutex_unlock(&snd_card_mutex);

#अगर_घोषित CONFIG_PM
	wake_up(&card->घातer_sleep);
#पूर्ण_अगर
	वापस 0;	
पूर्ण
EXPORT_SYMBOL(snd_card_disconnect);

/**
 * snd_card_disconnect_sync - disconnect card and रुको until files get बंदd
 * @card: card object to disconnect
 *
 * This calls snd_card_disconnect() क्रम disconnecting all beदीर्घing components
 * and रुकोs until all pending files get बंदd.
 * It assures that all accesses from user-space finished so that the driver
 * can release its resources gracefully.
 */
व्योम snd_card_disconnect_sync(काष्ठा snd_card *card)
अणु
	पूर्णांक err;

	err = snd_card_disconnect(card);
	अगर (err < 0) अणु
		dev_err(card->dev,
			"snd_card_disconnect error (%d), skipping sync\n",
			err);
		वापस;
	पूर्ण

	spin_lock_irq(&card->files_lock);
	रुको_event_lock_irq(card->हटाओ_sleep,
			    list_empty(&card->files_list),
			    card->files_lock);
	spin_unlock_irq(&card->files_lock);
पूर्ण
EXPORT_SYMBOL_GPL(snd_card_disconnect_sync);

अटल पूर्णांक snd_card_करो_मुक्त(काष्ठा snd_card *card)
अणु
#अगर IS_ENABLED(CONFIG_SND_MIXER_OSS)
	अगर (snd_mixer_oss_notअगरy_callback)
		snd_mixer_oss_notअगरy_callback(card, SND_MIXER_OSS_NOTIFY_FREE);
#पूर्ण_अगर
	snd_device_मुक्त_all(card);
	अगर (card->निजी_मुक्त)
		card->निजी_मुक्त(card);
	अगर (snd_info_card_मुक्त(card) < 0) अणु
		dev_warn(card->dev, "unable to free card info\n");
		/* Not fatal error */
	पूर्ण
#अगर_घोषित CONFIG_SND_DEBUG
	debugfs_हटाओ(card->debugfs_root);
	card->debugfs_root = शून्य;
#पूर्ण_अगर
	अगर (card->release_completion)
		complete(card->release_completion);
	kमुक्त(card);
	वापस 0;
पूर्ण

/**
 * snd_card_मुक्त_when_बंदd - Disconnect the card, मुक्त it later eventually
 * @card: soundcard काष्ठाure
 *
 * Unlike snd_card_मुक्त(), this function करोesn't try to release the card
 * resource immediately, but tries to disconnect at first.  When the card
 * is still in use, the function वापसs beक्रमe मुक्तing the resources.
 * The card resources will be मुक्तd when the refcount माला_लो to zero.
 */
पूर्णांक snd_card_मुक्त_when_बंदd(काष्ठा snd_card *card)
अणु
	पूर्णांक ret = snd_card_disconnect(card);
	अगर (ret)
		वापस ret;
	put_device(&card->card_dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_card_मुक्त_when_बंदd);

/**
 * snd_card_मुक्त - मुक्तs given soundcard काष्ठाure
 * @card: soundcard काष्ठाure
 *
 * This function releases the soundcard काष्ठाure and the all asचिन्हित
 * devices स्वतःmatically.  That is, you करोn't have to release the devices
 * by yourself.
 *
 * This function रुकोs until the all resources are properly released.
 *
 * Return: Zero. Frees all associated devices and मुक्तs the control
 * पूर्णांकerface associated to given soundcard.
 */
पूर्णांक snd_card_मुक्त(काष्ठा snd_card *card)
अणु
	DECLARE_COMPLETION_ONSTACK(released);
	पूर्णांक ret;

	card->release_completion = &released;
	ret = snd_card_मुक्त_when_बंदd(card);
	अगर (ret)
		वापस ret;
	/* रुको, until all devices are पढ़ोy क्रम the मुक्त operation */
	रुको_क्रम_completion(&released);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_card_मुक्त);

/* retrieve the last word of लघुname or दीर्घname */
अटल स्थिर अक्षर *retrieve_id_from_card_name(स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *spos = name;

	जबतक (*name) अणु
		अगर (है_खाली(*name) && है_अक्षर_अंक(name[1]))
			spos = name + 1;
		name++;
	पूर्ण
	वापस spos;
पूर्ण

/* वापस true अगर the given id string करोesn't conflict any other card ids */
अटल bool card_id_ok(काष्ठा snd_card *card, स्थिर अक्षर *id)
अणु
	पूर्णांक i;
	अगर (!snd_info_check_reserved_words(id))
		वापस false;
	क्रम (i = 0; i < snd_ecards_limit; i++) अणु
		अगर (snd_cards[i] && snd_cards[i] != card &&
		    !म_भेद(snd_cards[i]->id, id))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* copy to card->id only with valid letters from nid */
अटल व्योम copy_valid_id_string(काष्ठा snd_card *card, स्थिर अक्षर *src,
				 स्थिर अक्षर *nid)
अणु
	अक्षर *id = card->id;

	जबतक (*nid && !है_अक्षर_अंक(*nid))
		nid++;
	अगर (है_अंक(*nid))
		*id++ = है_अक्षर(*src) ? *src : 'D';
	जबतक (*nid && (माप_प्रकार)(id - card->id) < माप(card->id) - 1) अणु
		अगर (है_अक्षर_अंक(*nid))
			*id++ = *nid;
		nid++;
	पूर्ण
	*id = 0;
पूर्ण

/* Set card->id from the given string
 * If the string conflicts with other ids, add a suffix to make it unique.
 */
अटल व्योम snd_card_set_id_no_lock(काष्ठा snd_card *card, स्थिर अक्षर *src,
				    स्थिर अक्षर *nid)
अणु
	पूर्णांक len, loops;
	bool is_शेष = false;
	अक्षर *id;
	
	copy_valid_id_string(card, src, nid);
	id = card->id;

 again:
	/* use "Default" क्रम obviously invalid strings
	 * ("card" conflicts with proc directories)
	 */
	अगर (!*id || !म_भेदन(id, "card", 4)) अणु
		म_नकल(id, "Default");
		is_शेष = true;
	पूर्ण

	len = म_माप(id);
	क्रम (loops = 0; loops < SNDRV_CARDS; loops++) अणु
		अक्षर *spos;
		अक्षर sfxstr[5]; /* "_012" */
		पूर्णांक sfxlen;

		अगर (card_id_ok(card, id))
			वापस; /* OK */

		/* Add _XYZ suffix */
		प्र_लिखो(sfxstr, "_%X", loops + 1);
		sfxlen = म_माप(sfxstr);
		अगर (len + sfxlen >= माप(card->id))
			spos = id + माप(card->id) - sfxlen - 1;
		अन्यथा
			spos = id + len;
		म_नकल(spos, sfxstr);
	पूर्ण
	/* fallback to the शेष id */
	अगर (!is_शेष) अणु
		*id = 0;
		जाओ again;
	पूर्ण
	/* last resort... */
	dev_err(card->dev, "unable to set card id (%s)\n", id);
	अगर (card->proc_root->name)
		strscpy(card->id, card->proc_root->name, माप(card->id));
पूर्ण

/**
 *  snd_card_set_id - set card identअगरication name
 *  @card: soundcard काष्ठाure
 *  @nid: new identअगरication string
 *
 *  This function sets the card identअगरication and checks क्रम name
 *  collisions.
 */
व्योम snd_card_set_id(काष्ठा snd_card *card, स्थिर अक्षर *nid)
अणु
	/* check अगर user specअगरied own card->id */
	अगर (card->id[0] != '\0')
		वापस;
	mutex_lock(&snd_card_mutex);
	snd_card_set_id_no_lock(card, nid, nid);
	mutex_unlock(&snd_card_mutex);
पूर्ण
EXPORT_SYMBOL(snd_card_set_id);

अटल sमाप_प्रकार
card_id_show_attr(काष्ठा device *dev,
		  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_card *card = container_of(dev, काष्ठा snd_card, card_dev);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", card->id);
पूर्ण

अटल sमाप_प्रकार
card_id_store_attr(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा snd_card *card = container_of(dev, काष्ठा snd_card, card_dev);
	अक्षर buf1[माप(card->id)];
	माप_प्रकार copy = count > माप(card->id) - 1 ?
					माप(card->id) - 1 : count;
	माप_प्रकार idx;
	पूर्णांक c;

	क्रम (idx = 0; idx < copy; idx++) अणु
		c = buf[idx];
		अगर (!है_अक्षर_अंक(c) && c != '_' && c != '-')
			वापस -EINVAL;
	पूर्ण
	स_नकल(buf1, buf, copy);
	buf1[copy] = '\0';
	mutex_lock(&snd_card_mutex);
	अगर (!card_id_ok(शून्य, buf1)) अणु
		mutex_unlock(&snd_card_mutex);
		वापस -EEXIST;
	पूर्ण
	म_नकल(card->id, buf1);
	snd_info_card_id_change(card);
	mutex_unlock(&snd_card_mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(id, 0644, card_id_show_attr, card_id_store_attr);

अटल sमाप_प्रकार
card_number_show_attr(काष्ठा device *dev,
		     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_card *card = container_of(dev, काष्ठा snd_card, card_dev);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", card->number);
पूर्ण

अटल DEVICE_ATTR(number, 0444, card_number_show_attr, शून्य);

अटल काष्ठा attribute *card_dev_attrs[] = अणु
	&dev_attr_id.attr,
	&dev_attr_number.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group card_dev_attr_group = अणु
	.attrs	= card_dev_attrs,
पूर्ण;

/**
 * snd_card_add_dev_attr - Append a new sysfs attribute group to card
 * @card: card instance
 * @group: attribute group to append
 */
पूर्णांक snd_card_add_dev_attr(काष्ठा snd_card *card,
			  स्थिर काष्ठा attribute_group *group)
अणु
	पूर्णांक i;

	/* loop क्रम (arraysize-1) here to keep शून्य at the last entry */
	क्रम (i = 0; i < ARRAY_SIZE(card->dev_groups) - 1; i++) अणु
		अगर (!card->dev_groups[i]) अणु
			card->dev_groups[i] = group;
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(card->dev, "Too many groups assigned\n");
	वापस -ENOSPC;
पूर्ण
EXPORT_SYMBOL_GPL(snd_card_add_dev_attr);

/**
 *  snd_card_रेजिस्टर - रेजिस्टर the soundcard
 *  @card: soundcard काष्ठाure
 *
 *  This function रेजिस्टरs all the devices asचिन्हित to the soundcard.
 *  Until calling this, the ALSA control पूर्णांकerface is blocked from the
 *  बाह्यal accesses.  Thus, you should call this function at the end
 *  of the initialization of the card.
 *
 *  Return: Zero otherwise a negative error code अगर the registration failed.
 */
पूर्णांक snd_card_रेजिस्टर(काष्ठा snd_card *card)
अणु
	पूर्णांक err;

	अगर (snd_BUG_ON(!card))
		वापस -EINVAL;

	अगर (!card->रेजिस्टरed) अणु
		err = device_add(&card->card_dev);
		अगर (err < 0)
			वापस err;
		card->रेजिस्टरed = true;
	पूर्ण

	अगर ((err = snd_device_रेजिस्टर_all(card)) < 0)
		वापस err;
	mutex_lock(&snd_card_mutex);
	अगर (snd_cards[card->number]) अणु
		/* alपढ़ोy रेजिस्टरed */
		mutex_unlock(&snd_card_mutex);
		वापस snd_info_card_रेजिस्टर(card); /* रेजिस्टर pending info */
	पूर्ण
	अगर (*card->id) अणु
		/* make a unique id name from the given string */
		अक्षर पंचांगpid[माप(card->id)];
		स_नकल(पंचांगpid, card->id, माप(card->id));
		snd_card_set_id_no_lock(card, पंचांगpid, पंचांगpid);
	पूर्ण अन्यथा अणु
		/* create an id from either लघुname or दीर्घname */
		स्थिर अक्षर *src;
		src = *card->लघुname ? card->लघुname : card->दीर्घname;
		snd_card_set_id_no_lock(card, src,
					retrieve_id_from_card_name(src));
	पूर्ण
	snd_cards[card->number] = card;
	mutex_unlock(&snd_card_mutex);
	err = snd_info_card_रेजिस्टर(card);
	अगर (err < 0)
		वापस err;

#अगर IS_ENABLED(CONFIG_SND_MIXER_OSS)
	अगर (snd_mixer_oss_notअगरy_callback)
		snd_mixer_oss_notअगरy_callback(card, SND_MIXER_OSS_NOTIFY_REGISTER);
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_card_रेजिस्टर);

#अगर_घोषित CONFIG_SND_PROC_FS
अटल व्योम snd_card_info_पढ़ो(काष्ठा snd_info_entry *entry,
			       काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक idx, count;
	काष्ठा snd_card *card;

	क्रम (idx = count = 0; idx < SNDRV_CARDS; idx++) अणु
		mutex_lock(&snd_card_mutex);
		अगर ((card = snd_cards[idx]) != शून्य) अणु
			count++;
			snd_iम_लिखो(buffer, "%2i [%-15s]: %s - %s\n",
					idx,
					card->id,
					card->driver,
					card->लघुname);
			snd_iम_लिखो(buffer, "                      %s\n",
					card->दीर्घname);
		पूर्ण
		mutex_unlock(&snd_card_mutex);
	पूर्ण
	अगर (!count)
		snd_iम_लिखो(buffer, "--- no soundcards ---\n");
पूर्ण

#अगर_घोषित CONFIG_SND_OSSEMUL
व्योम snd_card_info_पढ़ो_oss(काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक idx, count;
	काष्ठा snd_card *card;

	क्रम (idx = count = 0; idx < SNDRV_CARDS; idx++) अणु
		mutex_lock(&snd_card_mutex);
		अगर ((card = snd_cards[idx]) != शून्य) अणु
			count++;
			snd_iम_लिखो(buffer, "%s\n", card->दीर्घname);
		पूर्ण
		mutex_unlock(&snd_card_mutex);
	पूर्ण
	अगर (!count) अणु
		snd_iम_लिखो(buffer, "--- no soundcards ---\n");
	पूर्ण
पूर्ण

#पूर्ण_अगर

#अगर_घोषित MODULE
अटल व्योम snd_card_module_info_पढ़ो(काष्ठा snd_info_entry *entry,
				      काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक idx;
	काष्ठा snd_card *card;

	क्रम (idx = 0; idx < SNDRV_CARDS; idx++) अणु
		mutex_lock(&snd_card_mutex);
		अगर ((card = snd_cards[idx]) != शून्य)
			snd_iम_लिखो(buffer, "%2i %s\n",
				    idx, card->module->name);
		mutex_unlock(&snd_card_mutex);
	पूर्ण
पूर्ण
#पूर्ण_अगर

पूर्णांक __init snd_card_info_init(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(THIS_MODULE, "cards", शून्य);
	अगर (! entry)
		वापस -ENOMEM;
	entry->c.text.पढ़ो = snd_card_info_पढ़ो;
	अगर (snd_info_रेजिस्टर(entry) < 0)
		वापस -ENOMEM; /* मुक्तd in error path */

#अगर_घोषित MODULE
	entry = snd_info_create_module_entry(THIS_MODULE, "modules", शून्य);
	अगर (!entry)
		वापस -ENOMEM;
	entry->c.text.पढ़ो = snd_card_module_info_पढ़ो;
	अगर (snd_info_रेजिस्टर(entry) < 0)
		वापस -ENOMEM; /* मुक्तd in error path */
#पूर्ण_अगर

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

/**
 *  snd_component_add - add a component string
 *  @card: soundcard काष्ठाure
 *  @component: the component id string
 *
 *  This function adds the component id string to the supported list.
 *  The component can be referred from the alsa-lib.
 *
 *  Return: Zero otherwise a negative error code.
 */
  
पूर्णांक snd_component_add(काष्ठा snd_card *card, स्थिर अक्षर *component)
अणु
	अक्षर *ptr;
	पूर्णांक len = म_माप(component);

	ptr = म_माला(card->components, component);
	अगर (ptr != शून्य) अणु
		अगर (ptr[len] == '\0' || ptr[len] == ' ')	/* alपढ़ोy there */
			वापस 1;
	पूर्ण
	अगर (म_माप(card->components) + 1 + len + 1 > माप(card->components)) अणु
		snd_BUG();
		वापस -ENOMEM;
	पूर्ण
	अगर (card->components[0] != '\0')
		म_जोड़ो(card->components, " ");
	म_जोड़ो(card->components, component);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_component_add);

/**
 *  snd_card_file_add - add the file to the file list of the card
 *  @card: soundcard काष्ठाure
 *  @file: file poपूर्णांकer
 *
 *  This function adds the file to the file linked-list of the card.
 *  This linked-list is used to keep tracking the connection state,
 *  and to aव्योम the release of busy resources by hotplug.
 *
 *  Return: zero or a negative error code.
 */
पूर्णांक snd_card_file_add(काष्ठा snd_card *card, काष्ठा file *file)
अणु
	काष्ठा snd_monitor_file *mfile;

	mfile = kदो_स्मृति(माप(*mfile), GFP_KERNEL);
	अगर (mfile == शून्य)
		वापस -ENOMEM;
	mfile->file = file;
	mfile->disconnected_f_op = शून्य;
	INIT_LIST_HEAD(&mfile->shutकरोwn_list);
	spin_lock(&card->files_lock);
	अगर (card->shutकरोwn) अणु
		spin_unlock(&card->files_lock);
		kमुक्त(mfile);
		वापस -ENODEV;
	पूर्ण
	list_add(&mfile->list, &card->files_list);
	get_device(&card->card_dev);
	spin_unlock(&card->files_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_card_file_add);

/**
 *  snd_card_file_हटाओ - हटाओ the file from the file list
 *  @card: soundcard काष्ठाure
 *  @file: file poपूर्णांकer
 *
 *  This function हटाओs the file क्रमmerly added to the card via
 *  snd_card_file_add() function.
 *  If all files are हटाओd and snd_card_मुक्त_when_बंदd() was
 *  called beक्रमehand, it processes the pending release of
 *  resources.
 *
 *  Return: Zero or a negative error code.
 */
पूर्णांक snd_card_file_हटाओ(काष्ठा snd_card *card, काष्ठा file *file)
अणु
	काष्ठा snd_monitor_file *mfile, *found = शून्य;

	spin_lock(&card->files_lock);
	list_क्रम_each_entry(mfile, &card->files_list, list) अणु
		अगर (mfile->file == file) अणु
			list_del(&mfile->list);
			spin_lock(&shutकरोwn_lock);
			list_del(&mfile->shutकरोwn_list);
			spin_unlock(&shutकरोwn_lock);
			अगर (mfile->disconnected_f_op)
				fops_put(mfile->disconnected_f_op);
			found = mfile;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (list_empty(&card->files_list))
		wake_up_all(&card->हटाओ_sleep);
	spin_unlock(&card->files_lock);
	अगर (!found) अणु
		dev_err(card->dev, "card file remove problem (%p)\n", file);
		वापस -ENOENT;
	पूर्ण
	kमुक्त(found);
	put_device(&card->card_dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_card_file_हटाओ);

#अगर_घोषित CONFIG_PM
/**
 *  snd_घातer_रुको - रुको until the घातer-state is changed.
 *  @card: soundcard काष्ठाure
 *  @घातer_state: expected घातer state
 *
 *  Waits until the घातer-state is changed.
 *
 *  Return: Zero अगर successful, or a negative error code.
 */
पूर्णांक snd_घातer_रुको(काष्ठा snd_card *card, अचिन्हित पूर्णांक घातer_state)
अणु
	रुको_queue_entry_t रुको;
	पूर्णांक result = 0;

	/* fastpath */
	अगर (snd_घातer_get_state(card) == घातer_state)
		वापस 0;
	init_रुकोqueue_entry(&रुको, current);
	add_रुको_queue(&card->घातer_sleep, &रुको);
	जबतक (1) अणु
		अगर (card->shutकरोwn) अणु
			result = -ENODEV;
			अवरोध;
		पूर्ण
		अगर (snd_घातer_get_state(card) == घातer_state)
			अवरोध;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(30 * HZ);
	पूर्ण
	हटाओ_रुको_queue(&card->घातer_sleep, &रुको);
	वापस result;
पूर्ण
EXPORT_SYMBOL(snd_घातer_रुको);
#पूर्ण_अगर /* CONFIG_PM */

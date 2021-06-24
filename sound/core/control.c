<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम driver control पूर्णांकerface
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/math64.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>

// Max allocation size क्रम user controls.
अटल पूर्णांक max_user_ctl_alloc_size = 8 * 1024 * 1024;
module_param_named(max_user_ctl_alloc_size, max_user_ctl_alloc_size, पूर्णांक, 0444);
MODULE_PARM_DESC(max_user_ctl_alloc_size, "Max allocation size for user controls");

#घोषणा MAX_CONTROL_COUNT	1028

काष्ठा snd_kctl_ioctl अणु
	काष्ठा list_head list;		/* list of all ioctls */
	snd_kctl_ioctl_func_t fioctl;
पूर्ण;

अटल DECLARE_RWSEM(snd_ioctl_rwsem);
अटल DECLARE_RWSEM(snd_ctl_layer_rwsem);
अटल LIST_HEAD(snd_control_ioctls);
#अगर_घोषित CONFIG_COMPAT
अटल LIST_HEAD(snd_control_compat_ioctls);
#पूर्ण_अगर
अटल काष्ठा snd_ctl_layer_ops *snd_ctl_layer;

अटल पूर्णांक snd_ctl_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_card *card;
	काष्ठा snd_ctl_file *ctl;
	पूर्णांक i, err;

	err = stream_खोलो(inode, file);
	अगर (err < 0)
		वापस err;

	card = snd_lookup_minor_data(iminor(inode), SNDRV_DEVICE_TYPE_CONTROL);
	अगर (!card) अणु
		err = -ENODEV;
		जाओ __error1;
	पूर्ण
	err = snd_card_file_add(card, file);
	अगर (err < 0) अणु
		err = -ENODEV;
		जाओ __error1;
	पूर्ण
	अगर (!try_module_get(card->module)) अणु
		err = -EFAULT;
		जाओ __error2;
	पूर्ण
	ctl = kzalloc(माप(*ctl), GFP_KERNEL);
	अगर (ctl == शून्य) अणु
		err = -ENOMEM;
		जाओ __error;
	पूर्ण
	INIT_LIST_HEAD(&ctl->events);
	init_रुकोqueue_head(&ctl->change_sleep);
	spin_lock_init(&ctl->पढ़ो_lock);
	ctl->card = card;
	क्रम (i = 0; i < SND_CTL_SUBDEV_ITEMS; i++)
		ctl->preferred_subdevice[i] = -1;
	ctl->pid = get_pid(task_pid(current));
	file->निजी_data = ctl;
	ग_लिखो_lock_irqsave(&card->ctl_files_rwlock, flags);
	list_add_tail(&ctl->list, &card->ctl_files);
	ग_लिखो_unlock_irqrestore(&card->ctl_files_rwlock, flags);
	snd_card_unref(card);
	वापस 0;

      __error:
	module_put(card->module);
      __error2:
	snd_card_file_हटाओ(card, file);
      __error1:
	अगर (card)
		snd_card_unref(card);
      	वापस err;
पूर्ण

अटल व्योम snd_ctl_empty_पढ़ो_queue(काष्ठा snd_ctl_file * ctl)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_kctl_event *cपढ़ो;

	spin_lock_irqsave(&ctl->पढ़ो_lock, flags);
	जबतक (!list_empty(&ctl->events)) अणु
		cपढ़ो = snd_kctl_event(ctl->events.next);
		list_del(&cपढ़ो->list);
		kमुक्त(cपढ़ो);
	पूर्ण
	spin_unlock_irqrestore(&ctl->पढ़ो_lock, flags);
पूर्ण

अटल पूर्णांक snd_ctl_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_card *card;
	काष्ठा snd_ctl_file *ctl;
	काष्ठा snd_kcontrol *control;
	अचिन्हित पूर्णांक idx;

	ctl = file->निजी_data;
	file->निजी_data = शून्य;
	card = ctl->card;
	ग_लिखो_lock_irqsave(&card->ctl_files_rwlock, flags);
	list_del(&ctl->list);
	ग_लिखो_unlock_irqrestore(&card->ctl_files_rwlock, flags);
	करोwn_ग_लिखो(&card->controls_rwsem);
	list_क्रम_each_entry(control, &card->controls, list)
		क्रम (idx = 0; idx < control->count; idx++)
			अगर (control->vd[idx].owner == ctl)
				control->vd[idx].owner = शून्य;
	up_ग_लिखो(&card->controls_rwsem);
	snd_ctl_empty_पढ़ो_queue(ctl);
	put_pid(ctl->pid);
	kमुक्त(ctl);
	module_put(card->module);
	snd_card_file_हटाओ(card, file);
	वापस 0;
पूर्ण

/**
 * snd_ctl_notअगरy - Send notअगरication to user-space क्रम a control change
 * @card: the card to send notअगरication
 * @mask: the event mask, SNDRV_CTL_EVENT_*
 * @id: the ctl element id to send notअगरication
 *
 * This function adds an event record with the given id and mask, appends
 * to the list and wakes up the user-space क्रम notअगरication.  This can be
 * called in the atomic context.
 */
व्योम snd_ctl_notअगरy(काष्ठा snd_card *card, अचिन्हित पूर्णांक mask,
		    काष्ठा snd_ctl_elem_id *id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_ctl_file *ctl;
	काष्ठा snd_kctl_event *ev;

	अगर (snd_BUG_ON(!card || !id))
		वापस;
	अगर (card->shutकरोwn)
		वापस;
	पढ़ो_lock_irqsave(&card->ctl_files_rwlock, flags);
#अगर IS_ENABLED(CONFIG_SND_MIXER_OSS)
	card->mixer_oss_change_count++;
#पूर्ण_अगर
	list_क्रम_each_entry(ctl, &card->ctl_files, list) अणु
		अगर (!ctl->subscribed)
			जारी;
		spin_lock(&ctl->पढ़ो_lock);
		list_क्रम_each_entry(ev, &ctl->events, list) अणु
			अगर (ev->id.numid == id->numid) अणु
				ev->mask |= mask;
				जाओ _found;
			पूर्ण
		पूर्ण
		ev = kzalloc(माप(*ev), GFP_ATOMIC);
		अगर (ev) अणु
			ev->id = *id;
			ev->mask = mask;
			list_add_tail(&ev->list, &ctl->events);
		पूर्ण अन्यथा अणु
			dev_err(card->dev, "No memory available to allocate event\n");
		पूर्ण
	_found:
		wake_up(&ctl->change_sleep);
		spin_unlock(&ctl->पढ़ो_lock);
		समाप्त_fasync(&ctl->fasync, SIGIO, POLL_IN);
	पूर्ण
	पढ़ो_unlock_irqrestore(&card->ctl_files_rwlock, flags);
पूर्ण
EXPORT_SYMBOL(snd_ctl_notअगरy);

/**
 * snd_ctl_notअगरy_one - Send notअगरication to user-space क्रम a control change
 * @card: the card to send notअगरication
 * @mask: the event mask, SNDRV_CTL_EVENT_*
 * @kctl: the poपूर्णांकer with the control instance
 * @ioff: the additional offset to the control index
 *
 * This function calls snd_ctl_notअगरy() and करोes additional jobs
 * like LED state changes.
 */
व्योम snd_ctl_notअगरy_one(काष्ठा snd_card *card, अचिन्हित पूर्णांक mask,
			काष्ठा snd_kcontrol *kctl, अचिन्हित पूर्णांक ioff)
अणु
	काष्ठा snd_ctl_elem_id id = kctl->id;
	काष्ठा snd_ctl_layer_ops *lops;

	id.index += ioff;
	id.numid += ioff;
	snd_ctl_notअगरy(card, mask, &id);
	करोwn_पढ़ो(&snd_ctl_layer_rwsem);
	क्रम (lops = snd_ctl_layer; lops; lops = lops->next)
		lops->lnotअगरy(card, mask, kctl, ioff);
	up_पढ़ो(&snd_ctl_layer_rwsem);
पूर्ण
EXPORT_SYMBOL(snd_ctl_notअगरy_one);

/**
 * snd_ctl_new - create a new control instance with some elements
 * @kctl: the poपूर्णांकer to store new control instance
 * @count: the number of elements in this control
 * @access: the शेष access flags क्रम elements in this control
 * @file: given when locking these elements
 *
 * Allocates a memory object क्रम a new control instance. The instance has
 * elements as many as the given number (@count). Each element has given
 * access permissions (@access). Each element is locked when @file is given.
 *
 * Return: 0 on success, error code on failure
 */
अटल पूर्णांक snd_ctl_new(काष्ठा snd_kcontrol **kctl, अचिन्हित पूर्णांक count,
		       अचिन्हित पूर्णांक access, काष्ठा snd_ctl_file *file)
अणु
	अचिन्हित पूर्णांक idx;

	अगर (count == 0 || count > MAX_CONTROL_COUNT)
		वापस -EINVAL;

	*kctl = kzalloc(काष्ठा_size(*kctl, vd, count), GFP_KERNEL);
	अगर (!*kctl)
		वापस -ENOMEM;

	क्रम (idx = 0; idx < count; idx++) अणु
		(*kctl)->vd[idx].access = access;
		(*kctl)->vd[idx].owner = file;
	पूर्ण
	(*kctl)->count = count;

	वापस 0;
पूर्ण

/**
 * snd_ctl_new1 - create a control instance from the ढाँचा
 * @ncontrol: the initialization record
 * @निजी_data: the निजी data to set
 *
 * Allocates a new काष्ठा snd_kcontrol instance and initialize from the given
 * ढाँचा.  When the access field of ncontrol is 0, it's assumed as
 * READWRITE access. When the count field is 0, it's assumes as one.
 *
 * Return: The poपूर्णांकer of the newly generated instance, or %शून्य on failure.
 */
काष्ठा snd_kcontrol *snd_ctl_new1(स्थिर काष्ठा snd_kcontrol_new *ncontrol,
				  व्योम *निजी_data)
अणु
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक access;
	पूर्णांक err;

	अगर (snd_BUG_ON(!ncontrol || !ncontrol->info))
		वापस शून्य;

	count = ncontrol->count;
	अगर (count == 0)
		count = 1;

	access = ncontrol->access;
	अगर (access == 0)
		access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	access &= (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_VOLATILE |
		   SNDRV_CTL_ELEM_ACCESS_INACTIVE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_COMMAND |
		   SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK |
		   SNDRV_CTL_ELEM_ACCESS_LED_MASK |
		   SNDRV_CTL_ELEM_ACCESS_SKIP_CHECK);

	err = snd_ctl_new(&kctl, count, access, शून्य);
	अगर (err < 0)
		वापस शून्य;

	/* The 'numid' member is decided when calling snd_ctl_add(). */
	kctl->id.अगरace = ncontrol->अगरace;
	kctl->id.device = ncontrol->device;
	kctl->id.subdevice = ncontrol->subdevice;
	अगर (ncontrol->name) अणु
		strscpy(kctl->id.name, ncontrol->name, माप(kctl->id.name));
		अगर (म_भेद(ncontrol->name, kctl->id.name) != 0)
			pr_warn("ALSA: Control name '%s' truncated to '%s'\n",
				ncontrol->name, kctl->id.name);
	पूर्ण
	kctl->id.index = ncontrol->index;

	kctl->info = ncontrol->info;
	kctl->get = ncontrol->get;
	kctl->put = ncontrol->put;
	kctl->tlv.p = ncontrol->tlv.p;

	kctl->निजी_value = ncontrol->निजी_value;
	kctl->निजी_data = निजी_data;

	वापस kctl;
पूर्ण
EXPORT_SYMBOL(snd_ctl_new1);

/**
 * snd_ctl_मुक्त_one - release the control instance
 * @kcontrol: the control instance
 *
 * Releases the control instance created via snd_ctl_new()
 * or snd_ctl_new1().
 * Don't call this after the control was added to the card.
 */
व्योम snd_ctl_मुक्त_one(काष्ठा snd_kcontrol *kcontrol)
अणु
	अगर (kcontrol) अणु
		अगर (kcontrol->निजी_मुक्त)
			kcontrol->निजी_मुक्त(kcontrol);
		kमुक्त(kcontrol);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_ctl_मुक्त_one);

अटल bool snd_ctl_हटाओ_numid_conflict(काष्ठा snd_card *card,
					  अचिन्हित पूर्णांक count)
अणु
	काष्ठा snd_kcontrol *kctl;

	/* Make sure that the ids asचिन्हित to the control करो not wrap around */
	अगर (card->last_numid >= अच_पूर्णांक_उच्च - count)
		card->last_numid = 0;

	list_क्रम_each_entry(kctl, &card->controls, list) अणु
		अगर (kctl->id.numid < card->last_numid + 1 + count &&
		    kctl->id.numid + kctl->count > card->last_numid + 1) अणु
		    	card->last_numid = kctl->id.numid + kctl->count - 1;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक snd_ctl_find_hole(काष्ठा snd_card *card, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक iter = 100000;

	जबतक (snd_ctl_हटाओ_numid_conflict(card, count)) अणु
		अगर (--iter == 0) अणु
			/* this situation is very unlikely */
			dev_err(card->dev, "unable to allocate new control numid\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत snd_ctl_add_mode अणु
	CTL_ADD_EXCLUSIVE, CTL_REPLACE, CTL_ADD_ON_REPLACE,
पूर्ण;

/* add/replace a new kcontrol object; call with card->controls_rwsem locked */
अटल पूर्णांक __snd_ctl_add_replace(काष्ठा snd_card *card,
				 काष्ठा snd_kcontrol *kcontrol,
				 क्रमागत snd_ctl_add_mode mode)
अणु
	काष्ठा snd_ctl_elem_id id;
	अचिन्हित पूर्णांक idx;
	काष्ठा snd_kcontrol *old;
	पूर्णांक err;

	id = kcontrol->id;
	अगर (id.index > अच_पूर्णांक_उच्च - kcontrol->count)
		वापस -EINVAL;

	old = snd_ctl_find_id(card, &id);
	अगर (!old) अणु
		अगर (mode == CTL_REPLACE)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (mode == CTL_ADD_EXCLUSIVE) अणु
			dev_err(card->dev,
				"control %i:%i:%i:%s:%i is already present\n",
				id.अगरace, id.device, id.subdevice, id.name,
				id.index);
			वापस -EBUSY;
		पूर्ण

		err = snd_ctl_हटाओ(card, old);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (snd_ctl_find_hole(card, kcontrol->count) < 0)
		वापस -ENOMEM;

	list_add_tail(&kcontrol->list, &card->controls);
	card->controls_count += kcontrol->count;
	kcontrol->id.numid = card->last_numid + 1;
	card->last_numid += kcontrol->count;

	क्रम (idx = 0; idx < kcontrol->count; idx++)
		snd_ctl_notअगरy_one(card, SNDRV_CTL_EVENT_MASK_ADD, kcontrol, idx);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_add_replace(काष्ठा snd_card *card,
			       काष्ठा snd_kcontrol *kcontrol,
			       क्रमागत snd_ctl_add_mode mode)
अणु
	पूर्णांक err = -EINVAL;

	अगर (! kcontrol)
		वापस err;
	अगर (snd_BUG_ON(!card || !kcontrol->info))
		जाओ error;

	करोwn_ग_लिखो(&card->controls_rwsem);
	err = __snd_ctl_add_replace(card, kcontrol, mode);
	up_ग_लिखो(&card->controls_rwsem);
	अगर (err < 0)
		जाओ error;
	वापस 0;

 error:
	snd_ctl_मुक्त_one(kcontrol);
	वापस err;
पूर्ण

/**
 * snd_ctl_add - add the control instance to the card
 * @card: the card instance
 * @kcontrol: the control instance to add
 *
 * Adds the control instance created via snd_ctl_new() or
 * snd_ctl_new1() to the given card. Assigns also an unique
 * numid used क्रम fast search.
 *
 * It मुक्तs स्वतःmatically the control which cannot be added.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 *
 */
पूर्णांक snd_ctl_add(काष्ठा snd_card *card, काष्ठा snd_kcontrol *kcontrol)
अणु
	वापस snd_ctl_add_replace(card, kcontrol, CTL_ADD_EXCLUSIVE);
पूर्ण
EXPORT_SYMBOL(snd_ctl_add);

/**
 * snd_ctl_replace - replace the control instance of the card
 * @card: the card instance
 * @kcontrol: the control instance to replace
 * @add_on_replace: add the control अगर not alपढ़ोy added
 *
 * Replaces the given control.  If the given control करोes not exist
 * and the add_on_replace flag is set, the control is added.  If the
 * control exists, it is destroyed first.
 *
 * It मुक्तs स्वतःmatically the control which cannot be added or replaced.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ctl_replace(काष्ठा snd_card *card, काष्ठा snd_kcontrol *kcontrol,
		    bool add_on_replace)
अणु
	वापस snd_ctl_add_replace(card, kcontrol,
				   add_on_replace ? CTL_ADD_ON_REPLACE : CTL_REPLACE);
पूर्ण
EXPORT_SYMBOL(snd_ctl_replace);

/**
 * snd_ctl_हटाओ - हटाओ the control from the card and release it
 * @card: the card instance
 * @kcontrol: the control instance to हटाओ
 *
 * Removes the control from the card and then releases the instance.
 * You करोn't need to call snd_ctl_मुक्त_one(). You must be in
 * the ग_लिखो lock - करोwn_ग_लिखो(&card->controls_rwsem).
 *
 * Return: 0 अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ctl_हटाओ(काष्ठा snd_card *card, काष्ठा snd_kcontrol *kcontrol)
अणु
	अचिन्हित पूर्णांक idx;

	अगर (snd_BUG_ON(!card || !kcontrol))
		वापस -EINVAL;
	list_del(&kcontrol->list);
	card->controls_count -= kcontrol->count;
	क्रम (idx = 0; idx < kcontrol->count; idx++)
		snd_ctl_notअगरy_one(card, SNDRV_CTL_EVENT_MASK_REMOVE, kcontrol, idx);
	snd_ctl_मुक्त_one(kcontrol);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_ctl_हटाओ);

/**
 * snd_ctl_हटाओ_id - हटाओ the control of the given id and release it
 * @card: the card instance
 * @id: the control id to हटाओ
 *
 * Finds the control instance with the given id, हटाओs it from the
 * card list and releases it.
 *
 * Return: 0 अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ctl_हटाओ_id(काष्ठा snd_card *card, काष्ठा snd_ctl_elem_id *id)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक ret;

	करोwn_ग_लिखो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, id);
	अगर (kctl == शून्य) अणु
		up_ग_लिखो(&card->controls_rwsem);
		वापस -ENOENT;
	पूर्ण
	ret = snd_ctl_हटाओ(card, kctl);
	up_ग_लिखो(&card->controls_rwsem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(snd_ctl_हटाओ_id);

/**
 * snd_ctl_हटाओ_user_ctl - हटाओ and release the unlocked user control
 * @file: active control handle
 * @id: the control id to हटाओ
 *
 * Finds the control instance with the given id, हटाओs it from the
 * card list and releases it.
 *
 * Return: 0 अगर successful, or a negative error code on failure.
 */
अटल पूर्णांक snd_ctl_हटाओ_user_ctl(काष्ठा snd_ctl_file * file,
				   काष्ठा snd_ctl_elem_id *id)
अणु
	काष्ठा snd_card *card = file->card;
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक idx, ret;

	करोwn_ग_लिखो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, id);
	अगर (kctl == शून्य) अणु
		ret = -ENOENT;
		जाओ error;
	पूर्ण
	अगर (!(kctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_USER)) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	क्रम (idx = 0; idx < kctl->count; idx++)
		अगर (kctl->vd[idx].owner != शून्य && kctl->vd[idx].owner != file) अणु
			ret = -EBUSY;
			जाओ error;
		पूर्ण
	ret = snd_ctl_हटाओ(card, kctl);
error:
	up_ग_लिखो(&card->controls_rwsem);
	वापस ret;
पूर्ण

/**
 * snd_ctl_activate_id - activate/inactivate the control of the given id
 * @card: the card instance
 * @id: the control id to activate/inactivate
 * @active: non-zero to activate
 *
 * Finds the control instance with the given id, and activate or
 * inactivate the control together with notअगरication, अगर changed.
 * The given ID data is filled with full inक्रमmation.
 *
 * Return: 0 अगर unchanged, 1 अगर changed, or a negative error code on failure.
 */
पूर्णांक snd_ctl_activate_id(काष्ठा snd_card *card, काष्ठा snd_ctl_elem_id *id,
			पूर्णांक active)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	अचिन्हित पूर्णांक index_offset;
	पूर्णांक ret;

	करोwn_ग_लिखो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, id);
	अगर (kctl == शून्य) अणु
		ret = -ENOENT;
		जाओ unlock;
	पूर्ण
	index_offset = snd_ctl_get_ioff(kctl, id);
	vd = &kctl->vd[index_offset];
	ret = 0;
	अगर (active) अणु
		अगर (!(vd->access & SNDRV_CTL_ELEM_ACCESS_INACTIVE))
			जाओ unlock;
		vd->access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	पूर्ण अन्यथा अणु
		अगर (vd->access & SNDRV_CTL_ELEM_ACCESS_INACTIVE)
			जाओ unlock;
		vd->access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	पूर्ण
	snd_ctl_build_ioff(id, kctl, index_offset);
	करोwngrade_ग_लिखो(&card->controls_rwsem);
	snd_ctl_notअगरy_one(card, SNDRV_CTL_EVENT_MASK_INFO, kctl, index_offset);
	up_पढ़ो(&card->controls_rwsem);
	वापस 1;

 unlock:
	up_ग_लिखो(&card->controls_rwsem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ctl_activate_id);

/**
 * snd_ctl_नाम_id - replace the id of a control on the card
 * @card: the card instance
 * @src_id: the old id
 * @dst_id: the new id
 *
 * Finds the control with the old id from the card, and replaces the
 * id with the new one.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ctl_नाम_id(काष्ठा snd_card *card, काष्ठा snd_ctl_elem_id *src_id,
		      काष्ठा snd_ctl_elem_id *dst_id)
अणु
	काष्ठा snd_kcontrol *kctl;

	करोwn_ग_लिखो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, src_id);
	अगर (kctl == शून्य) अणु
		up_ग_लिखो(&card->controls_rwsem);
		वापस -ENOENT;
	पूर्ण
	kctl->id = *dst_id;
	kctl->id.numid = card->last_numid + 1;
	card->last_numid += kctl->count;
	up_ग_लिखो(&card->controls_rwsem);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_ctl_नाम_id);

/**
 * snd_ctl_find_numid - find the control instance with the given number-id
 * @card: the card instance
 * @numid: the number-id to search
 *
 * Finds the control instance with the given number-id from the card.
 *
 * The caller must करोwn card->controls_rwsem beक्रमe calling this function
 * (अगर the race condition can happen).
 *
 * Return: The poपूर्णांकer of the instance अगर found, or %शून्य अगर not.
 *
 */
काष्ठा snd_kcontrol *snd_ctl_find_numid(काष्ठा snd_card *card, अचिन्हित पूर्णांक numid)
अणु
	काष्ठा snd_kcontrol *kctl;

	अगर (snd_BUG_ON(!card || !numid))
		वापस शून्य;
	list_क्रम_each_entry(kctl, &card->controls, list) अणु
		अगर (kctl->id.numid <= numid && kctl->id.numid + kctl->count > numid)
			वापस kctl;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(snd_ctl_find_numid);

/**
 * snd_ctl_find_id - find the control instance with the given id
 * @card: the card instance
 * @id: the id to search
 *
 * Finds the control instance with the given id from the card.
 *
 * The caller must करोwn card->controls_rwsem beक्रमe calling this function
 * (अगर the race condition can happen).
 *
 * Return: The poपूर्णांकer of the instance अगर found, or %शून्य अगर not.
 *
 */
काष्ठा snd_kcontrol *snd_ctl_find_id(काष्ठा snd_card *card,
				     काष्ठा snd_ctl_elem_id *id)
अणु
	काष्ठा snd_kcontrol *kctl;

	अगर (snd_BUG_ON(!card || !id))
		वापस शून्य;
	अगर (id->numid != 0)
		वापस snd_ctl_find_numid(card, id->numid);
	list_क्रम_each_entry(kctl, &card->controls, list) अणु
		अगर (kctl->id.अगरace != id->अगरace)
			जारी;
		अगर (kctl->id.device != id->device)
			जारी;
		अगर (kctl->id.subdevice != id->subdevice)
			जारी;
		अगर (म_भेदन(kctl->id.name, id->name, माप(kctl->id.name)))
			जारी;
		अगर (kctl->id.index > id->index)
			जारी;
		अगर (kctl->id.index + kctl->count <= id->index)
			जारी;
		वापस kctl;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(snd_ctl_find_id);

अटल पूर्णांक snd_ctl_card_info(काष्ठा snd_card *card, काष्ठा snd_ctl_file * ctl,
			     अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा snd_ctl_card_info *info;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (! info)
		वापस -ENOMEM;
	करोwn_पढ़ो(&snd_ioctl_rwsem);
	info->card = card->number;
	strscpy(info->id, card->id, माप(info->id));
	strscpy(info->driver, card->driver, माप(info->driver));
	strscpy(info->name, card->लघुname, माप(info->name));
	strscpy(info->दीर्घname, card->दीर्घname, माप(info->दीर्घname));
	strscpy(info->mixername, card->mixername, माप(info->mixername));
	strscpy(info->components, card->components, माप(info->components));
	up_पढ़ो(&snd_ioctl_rwsem);
	अगर (copy_to_user(arg, info, माप(काष्ठा snd_ctl_card_info))) अणु
		kमुक्त(info);
		वापस -EFAULT;
	पूर्ण
	kमुक्त(info);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_elem_list(काष्ठा snd_card *card,
			     काष्ठा snd_ctl_elem_list *list)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_ctl_elem_id id;
	अचिन्हित पूर्णांक offset, space, jidx;
	पूर्णांक err = 0;

	offset = list->offset;
	space = list->space;

	करोwn_पढ़ो(&card->controls_rwsem);
	list->count = card->controls_count;
	list->used = 0;
	अगर (space > 0) अणु
		list_क्रम_each_entry(kctl, &card->controls, list) अणु
			अगर (offset >= kctl->count) अणु
				offset -= kctl->count;
				जारी;
			पूर्ण
			क्रम (jidx = offset; jidx < kctl->count; jidx++) अणु
				snd_ctl_build_ioff(&id, kctl, jidx);
				अगर (copy_to_user(list->pids + list->used, &id,
						 माप(id))) अणु
					err = -EFAULT;
					जाओ out;
				पूर्ण
				list->used++;
				अगर (!--space)
					जाओ out;
			पूर्ण
			offset = 0;
		पूर्ण
	पूर्ण
 out:
	up_पढ़ो(&card->controls_rwsem);
	वापस err;
पूर्ण

अटल पूर्णांक snd_ctl_elem_list_user(काष्ठा snd_card *card,
				  काष्ठा snd_ctl_elem_list __user *_list)
अणु
	काष्ठा snd_ctl_elem_list list;
	पूर्णांक err;

	अगर (copy_from_user(&list, _list, माप(list)))
		वापस -EFAULT;
	err = snd_ctl_elem_list(card, &list);
	अगर (err)
		वापस err;
	अगर (copy_to_user(_list, &list, माप(list)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* Check whether the given kctl info is valid */
अटल पूर्णांक snd_ctl_check_elem_info(काष्ठा snd_card *card,
				   स्थिर काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अचिन्हित पूर्णांक max_value_counts[] = अणु
		[SNDRV_CTL_ELEM_TYPE_BOOLEAN]	= 128,
		[SNDRV_CTL_ELEM_TYPE_INTEGER]	= 128,
		[SNDRV_CTL_ELEM_TYPE_ENUMERATED] = 128,
		[SNDRV_CTL_ELEM_TYPE_BYTES]	= 512,
		[SNDRV_CTL_ELEM_TYPE_IEC958]	= 1,
		[SNDRV_CTL_ELEM_TYPE_INTEGER64] = 64,
	पूर्ण;

	अगर (info->type < SNDRV_CTL_ELEM_TYPE_BOOLEAN ||
	    info->type > SNDRV_CTL_ELEM_TYPE_INTEGER64) अणु
		अगर (card)
			dev_err(card->dev,
				"control %i:%i:%i:%s:%i: invalid type %d\n",
				info->id.अगरace, info->id.device,
				info->id.subdevice, info->id.name,
				info->id.index, info->type);
		वापस -EINVAL;
	पूर्ण
	अगर (info->type == SNDRV_CTL_ELEM_TYPE_ENUMERATED &&
	    info->value.क्रमागतerated.items == 0) अणु
		अगर (card)
			dev_err(card->dev,
				"control %i:%i:%i:%s:%i: zero enum items\n",
				info->id.अगरace, info->id.device,
				info->id.subdevice, info->id.name,
				info->id.index);
		वापस -EINVAL;
	पूर्ण
	अगर (info->count > max_value_counts[info->type]) अणु
		अगर (card)
			dev_err(card->dev,
				"control %i:%i:%i:%s:%i: invalid count %d\n",
				info->id.अगरace, info->id.device,
				info->id.subdevice, info->id.name,
				info->id.index, info->count);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* The capacity of काष्ठा snd_ctl_elem_value.value.*/
अटल स्थिर अचिन्हित पूर्णांक value_sizes[] = अणु
	[SNDRV_CTL_ELEM_TYPE_BOOLEAN]	= माप(दीर्घ),
	[SNDRV_CTL_ELEM_TYPE_INTEGER]	= माप(दीर्घ),
	[SNDRV_CTL_ELEM_TYPE_ENUMERATED] = माप(अचिन्हित पूर्णांक),
	[SNDRV_CTL_ELEM_TYPE_BYTES]	= माप(अचिन्हित अक्षर),
	[SNDRV_CTL_ELEM_TYPE_IEC958]	= माप(काष्ठा snd_aes_iec958),
	[SNDRV_CTL_ELEM_TYPE_INTEGER64] = माप(दीर्घ दीर्घ),
पूर्ण;

#अगर_घोषित CONFIG_SND_CTL_VALIDATION
/* fill the reमुख्यing snd_ctl_elem_value data with the given pattern */
अटल व्योम fill_reमुख्यing_elem_value(काष्ठा snd_ctl_elem_value *control,
				      काष्ठा snd_ctl_elem_info *info,
				      u32 pattern)
अणु
	माप_प्रकार offset = value_sizes[info->type] * info->count;

	offset = DIV_ROUND_UP(offset, माप(u32));
	स_रखो32((u32 *)control->value.bytes.data + offset, pattern,
		 माप(control->value) / माप(u32) - offset);
पूर्ण

/* check whether the given पूर्णांकeger ctl value is valid */
अटल पूर्णांक sanity_check_पूर्णांक_value(काष्ठा snd_card *card,
				  स्थिर काष्ठा snd_ctl_elem_value *control,
				  स्थिर काष्ठा snd_ctl_elem_info *info,
				  पूर्णांक i)
अणु
	दीर्घ दीर्घ lval, lmin, lmax, lstep;
	u64 rem;

	चयन (info->type) अणु
	शेष:
	हाल SNDRV_CTL_ELEM_TYPE_BOOLEAN:
		lval = control->value.पूर्णांकeger.value[i];
		lmin = 0;
		lmax = 1;
		lstep = 0;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER:
		lval = control->value.पूर्णांकeger.value[i];
		lmin = info->value.पूर्णांकeger.min;
		lmax = info->value.पूर्णांकeger.max;
		lstep = info->value.पूर्णांकeger.step;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER64:
		lval = control->value.पूर्णांकeger64.value[i];
		lmin = info->value.पूर्णांकeger64.min;
		lmax = info->value.पूर्णांकeger64.max;
		lstep = info->value.पूर्णांकeger64.step;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		lval = control->value.क्रमागतerated.item[i];
		lmin = 0;
		lmax = info->value.क्रमागतerated.items - 1;
		lstep = 0;
		अवरोध;
	पूर्ण

	अगर (lval < lmin || lval > lmax) अणु
		dev_err(card->dev,
			"control %i:%i:%i:%s:%i: value out of range %lld (%lld/%lld) at count %i\n",
			control->id.अगरace, control->id.device,
			control->id.subdevice, control->id.name,
			control->id.index, lval, lmin, lmax, i);
		वापस -EINVAL;
	पूर्ण
	अगर (lstep) अणु
		भाग64_u64_rem(lval, lstep, &rem);
		अगर (rem) अणु
			dev_err(card->dev,
				"control %i:%i:%i:%s:%i: unaligned value %lld (step %lld) at count %i\n",
				control->id.अगरace, control->id.device,
				control->id.subdevice, control->id.name,
				control->id.index, lval, lstep, i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* perक्रमm sanity checks to the given snd_ctl_elem_value object */
अटल पूर्णांक sanity_check_elem_value(काष्ठा snd_card *card,
				   स्थिर काष्ठा snd_ctl_elem_value *control,
				   स्थिर काष्ठा snd_ctl_elem_info *info,
				   u32 pattern)
अणु
	माप_प्रकार offset;
	पूर्णांक i, ret = 0;
	u32 *p;

	चयन (info->type) अणु
	हाल SNDRV_CTL_ELEM_TYPE_BOOLEAN:
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER:
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER64:
	हाल SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		क्रम (i = 0; i < info->count; i++) अणु
			ret = sanity_check_पूर्णांक_value(card, control, info, i);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* check whether the reमुख्यing area kept untouched */
	offset = value_sizes[info->type] * info->count;
	offset = DIV_ROUND_UP(offset, माप(u32));
	p = (u32 *)control->value.bytes.data + offset;
	क्रम (; offset < माप(control->value) / माप(u32); offset++, p++) अणु
		अगर (*p != pattern) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		*p = 0; /* clear the checked area */
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम fill_reमुख्यing_elem_value(काष्ठा snd_ctl_elem_value *control,
					     काष्ठा snd_ctl_elem_info *info,
					     u32 pattern)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sanity_check_elem_value(काष्ठा snd_card *card,
					  काष्ठा snd_ctl_elem_value *control,
					  काष्ठा snd_ctl_elem_info *info,
					  u32 pattern)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __snd_ctl_elem_info(काष्ठा snd_card *card,
			       काष्ठा snd_kcontrol *kctl,
			       काष्ठा snd_ctl_elem_info *info,
			       काष्ठा snd_ctl_file *ctl)
अणु
	काष्ठा snd_kcontrol_अस्थिर *vd;
	अचिन्हित पूर्णांक index_offset;
	पूर्णांक result;

#अगर_घोषित CONFIG_SND_DEBUG
	info->access = 0;
#पूर्ण_अगर
	result = kctl->info(kctl, info);
	अगर (result >= 0) अणु
		snd_BUG_ON(info->access);
		index_offset = snd_ctl_get_ioff(kctl, &info->id);
		vd = &kctl->vd[index_offset];
		snd_ctl_build_ioff(&info->id, kctl, index_offset);
		info->access = vd->access;
		अगर (vd->owner) अणु
			info->access |= SNDRV_CTL_ELEM_ACCESS_LOCK;
			अगर (vd->owner == ctl)
				info->access |= SNDRV_CTL_ELEM_ACCESS_OWNER;
			info->owner = pid_vnr(vd->owner->pid);
		पूर्ण अन्यथा अणु
			info->owner = -1;
		पूर्ण
		अगर (!snd_ctl_skip_validation(info) &&
		    snd_ctl_check_elem_info(card, info) < 0)
			result = -EINVAL;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक snd_ctl_elem_info(काष्ठा snd_ctl_file *ctl,
			     काष्ठा snd_ctl_elem_info *info)
अणु
	काष्ठा snd_card *card = ctl->card;
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक result;

	करोwn_पढ़ो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, &info->id);
	अगर (kctl == शून्य)
		result = -ENOENT;
	अन्यथा
		result = __snd_ctl_elem_info(card, kctl, info, ctl);
	up_पढ़ो(&card->controls_rwsem);
	वापस result;
पूर्ण

अटल पूर्णांक snd_ctl_elem_info_user(काष्ठा snd_ctl_file *ctl,
				  काष्ठा snd_ctl_elem_info __user *_info)
अणु
	काष्ठा snd_ctl_elem_info info;
	पूर्णांक result;

	अगर (copy_from_user(&info, _info, माप(info)))
		वापस -EFAULT;
	result = snd_घातer_रुको(ctl->card, SNDRV_CTL_POWER_D0);
	अगर (result < 0)
		वापस result;
	result = snd_ctl_elem_info(ctl, &info);
	अगर (result < 0)
		वापस result;
	/* drop पूर्णांकernal access flags */
	info.access &= ~(SNDRV_CTL_ELEM_ACCESS_SKIP_CHECK|
			 SNDRV_CTL_ELEM_ACCESS_LED_MASK);
	अगर (copy_to_user(_info, &info, माप(info)))
		वापस -EFAULT;
	वापस result;
पूर्ण

अटल पूर्णांक snd_ctl_elem_पढ़ो(काष्ठा snd_card *card,
			     काष्ठा snd_ctl_elem_value *control)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	अचिन्हित पूर्णांक index_offset;
	काष्ठा snd_ctl_elem_info info;
	स्थिर u32 pattern = 0xdeadbeef;
	पूर्णांक ret;

	kctl = snd_ctl_find_id(card, &control->id);
	अगर (kctl == शून्य)
		वापस -ENOENT;

	index_offset = snd_ctl_get_ioff(kctl, &control->id);
	vd = &kctl->vd[index_offset];
	अगर (!(vd->access & SNDRV_CTL_ELEM_ACCESS_READ) || kctl->get == शून्य)
		वापस -EPERM;

	snd_ctl_build_ioff(&control->id, kctl, index_offset);

#अगर_घोषित CONFIG_SND_CTL_VALIDATION
	/* info is needed only क्रम validation */
	स_रखो(&info, 0, माप(info));
	info.id = control->id;
	ret = __snd_ctl_elem_info(card, kctl, &info, शून्य);
	अगर (ret < 0)
		वापस ret;
#पूर्ण_अगर

	अगर (!snd_ctl_skip_validation(&info))
		fill_reमुख्यing_elem_value(control, &info, pattern);
	ret = kctl->get(kctl, control);
	अगर (ret < 0)
		वापस ret;
	अगर (!snd_ctl_skip_validation(&info) &&
	    sanity_check_elem_value(card, control, &info, pattern) < 0) अणु
		dev_err(card->dev,
			"control %i:%i:%i:%s:%i: access overflow\n",
			control->id.अगरace, control->id.device,
			control->id.subdevice, control->id.name,
			control->id.index);
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक snd_ctl_elem_पढ़ो_user(काष्ठा snd_card *card,
				  काष्ठा snd_ctl_elem_value __user *_control)
अणु
	काष्ठा snd_ctl_elem_value *control;
	पूर्णांक result;

	control = memdup_user(_control, माप(*control));
	अगर (IS_ERR(control))
		वापस PTR_ERR(control);

	result = snd_घातer_रुको(card, SNDRV_CTL_POWER_D0);
	अगर (result < 0)
		जाओ error;

	करोwn_पढ़ो(&card->controls_rwsem);
	result = snd_ctl_elem_पढ़ो(card, control);
	up_पढ़ो(&card->controls_rwsem);
	अगर (result < 0)
		जाओ error;

	अगर (copy_to_user(_control, control, माप(*control)))
		result = -EFAULT;
 error:
	kमुक्त(control);
	वापस result;
पूर्ण

अटल पूर्णांक snd_ctl_elem_ग_लिखो(काष्ठा snd_card *card, काष्ठा snd_ctl_file *file,
			      काष्ठा snd_ctl_elem_value *control)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	अचिन्हित पूर्णांक index_offset;
	पूर्णांक result;

	करोwn_ग_लिखो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, &control->id);
	अगर (kctl == शून्य) अणु
		up_ग_लिखो(&card->controls_rwsem);
		वापस -ENOENT;
	पूर्ण

	index_offset = snd_ctl_get_ioff(kctl, &control->id);
	vd = &kctl->vd[index_offset];
	अगर (!(vd->access & SNDRV_CTL_ELEM_ACCESS_WRITE) || kctl->put == शून्य ||
	    (file && vd->owner && vd->owner != file)) अणु
		up_ग_लिखो(&card->controls_rwsem);
		वापस -EPERM;
	पूर्ण

	snd_ctl_build_ioff(&control->id, kctl, index_offset);
	result = kctl->put(kctl, control);
	अगर (result < 0) अणु
		up_ग_लिखो(&card->controls_rwsem);
		वापस result;
	पूर्ण

	अगर (result > 0) अणु
		करोwngrade_ग_लिखो(&card->controls_rwsem);
		snd_ctl_notअगरy_one(card, SNDRV_CTL_EVENT_MASK_VALUE, kctl, index_offset);
		up_पढ़ो(&card->controls_rwsem);
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&card->controls_rwsem);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_elem_ग_लिखो_user(काष्ठा snd_ctl_file *file,
				   काष्ठा snd_ctl_elem_value __user *_control)
अणु
	काष्ठा snd_ctl_elem_value *control;
	काष्ठा snd_card *card;
	पूर्णांक result;

	control = memdup_user(_control, माप(*control));
	अगर (IS_ERR(control))
		वापस PTR_ERR(control);

	card = file->card;
	result = snd_घातer_रुको(card, SNDRV_CTL_POWER_D0);
	अगर (result < 0)
		जाओ error;

	result = snd_ctl_elem_ग_लिखो(card, file, control);
	अगर (result < 0)
		जाओ error;

	अगर (copy_to_user(_control, control, माप(*control)))
		result = -EFAULT;
 error:
	kमुक्त(control);
	वापस result;
पूर्ण

अटल पूर्णांक snd_ctl_elem_lock(काष्ठा snd_ctl_file *file,
			     काष्ठा snd_ctl_elem_id __user *_id)
अणु
	काष्ठा snd_card *card = file->card;
	काष्ठा snd_ctl_elem_id id;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	पूर्णांक result;

	अगर (copy_from_user(&id, _id, माप(id)))
		वापस -EFAULT;
	करोwn_ग_लिखो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, &id);
	अगर (kctl == शून्य) अणु
		result = -ENOENT;
	पूर्ण अन्यथा अणु
		vd = &kctl->vd[snd_ctl_get_ioff(kctl, &id)];
		अगर (vd->owner != शून्य)
			result = -EBUSY;
		अन्यथा अणु
			vd->owner = file;
			result = 0;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&card->controls_rwsem);
	वापस result;
पूर्ण

अटल पूर्णांक snd_ctl_elem_unlock(काष्ठा snd_ctl_file *file,
			       काष्ठा snd_ctl_elem_id __user *_id)
अणु
	काष्ठा snd_card *card = file->card;
	काष्ठा snd_ctl_elem_id id;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_अस्थिर *vd;
	पूर्णांक result;

	अगर (copy_from_user(&id, _id, माप(id)))
		वापस -EFAULT;
	करोwn_ग_लिखो(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, &id);
	अगर (kctl == शून्य) अणु
		result = -ENOENT;
	पूर्ण अन्यथा अणु
		vd = &kctl->vd[snd_ctl_get_ioff(kctl, &id)];
		अगर (vd->owner == शून्य)
			result = -EINVAL;
		अन्यथा अगर (vd->owner != file)
			result = -EPERM;
		अन्यथा अणु
			vd->owner = शून्य;
			result = 0;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&card->controls_rwsem);
	वापस result;
पूर्ण

काष्ठा user_element अणु
	काष्ठा snd_ctl_elem_info info;
	काष्ठा snd_card *card;
	अक्षर *elem_data;		/* element data */
	अचिन्हित दीर्घ elem_data_size;	/* size of element data in bytes */
	व्योम *tlv_data;			/* TLV data */
	अचिन्हित दीर्घ tlv_data_size;	/* TLV data size */
	व्योम *priv_data;		/* निजी data (like strings क्रम क्रमागतerated type) */
पूर्ण;

// check whether the addition (in bytes) of user ctl element may overflow the limit.
अटल bool check_user_elem_overflow(काष्ठा snd_card *card, sमाप_प्रकार add)
अणु
	वापस (sमाप_प्रकार)card->user_ctl_alloc_size + add > max_user_ctl_alloc_size;
पूर्ण

अटल पूर्णांक snd_ctl_elem_user_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा user_element *ue = kcontrol->निजी_data;
	अचिन्हित पूर्णांक offset;

	offset = snd_ctl_get_ioff(kcontrol, &uinfo->id);
	*uinfo = ue->info;
	snd_ctl_build_ioff(&uinfo->id, kcontrol, offset);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_elem_user_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा user_element *ue = kcontrol->निजी_data;
	स्थिर अक्षर *names;
	अचिन्हित पूर्णांक item;
	अचिन्हित पूर्णांक offset;

	item = uinfo->value.क्रमागतerated.item;

	offset = snd_ctl_get_ioff(kcontrol, &uinfo->id);
	*uinfo = ue->info;
	snd_ctl_build_ioff(&uinfo->id, kcontrol, offset);

	item = min(item, uinfo->value.क्रमागतerated.items - 1);
	uinfo->value.क्रमागतerated.item = item;

	names = ue->priv_data;
	क्रम (; item > 0; --item)
		names += म_माप(names) + 1;
	म_नकल(uinfo->value.क्रमागतerated.name, names);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_elem_user_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा user_element *ue = kcontrol->निजी_data;
	अचिन्हित पूर्णांक size = ue->elem_data_size;
	अक्षर *src = ue->elem_data +
			snd_ctl_get_ioff(kcontrol, &ucontrol->id) * size;

	स_नकल(&ucontrol->value, src, size);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_elem_user_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक change;
	काष्ठा user_element *ue = kcontrol->निजी_data;
	अचिन्हित पूर्णांक size = ue->elem_data_size;
	अक्षर *dst = ue->elem_data +
			snd_ctl_get_ioff(kcontrol, &ucontrol->id) * size;

	change = स_भेद(&ucontrol->value, dst, size) != 0;
	अगर (change)
		स_नकल(dst, &ucontrol->value, size);
	वापस change;
पूर्ण

/* called in controls_rwsem ग_लिखो lock */
अटल पूर्णांक replace_user_tlv(काष्ठा snd_kcontrol *kctl, अचिन्हित पूर्णांक __user *buf,
			    अचिन्हित पूर्णांक size)
अणु
	काष्ठा user_element *ue = kctl->निजी_data;
	अचिन्हित पूर्णांक *container;
	अचिन्हित पूर्णांक mask = 0;
	पूर्णांक i;
	पूर्णांक change;

	अगर (size > 1024 * 128)	/* sane value */
		वापस -EINVAL;

	// करोes the TLV size change cause overflow?
	अगर (check_user_elem_overflow(ue->card, (sमाप_प्रकार)(size - ue->tlv_data_size)))
		वापस -ENOMEM;

	container = vmemdup_user(buf, size);
	अगर (IS_ERR(container))
		वापस PTR_ERR(container);

	change = ue->tlv_data_size != size;
	अगर (!change)
		change = स_भेद(ue->tlv_data, container, size) != 0;
	अगर (!change) अणु
		kvमुक्त(container);
		वापस 0;
	पूर्ण

	अगर (ue->tlv_data == शून्य) अणु
		/* Now TLV data is available. */
		क्रम (i = 0; i < kctl->count; ++i)
			kctl->vd[i].access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		mask = SNDRV_CTL_EVENT_MASK_INFO;
	पूर्ण अन्यथा अणु
		ue->card->user_ctl_alloc_size -= ue->tlv_data_size;
		ue->tlv_data_size = 0;
		kvमुक्त(ue->tlv_data);
	पूर्ण

	ue->tlv_data = container;
	ue->tlv_data_size = size;
	// decremented at निजी_मुक्त.
	ue->card->user_ctl_alloc_size += size;

	mask |= SNDRV_CTL_EVENT_MASK_TLV;
	क्रम (i = 0; i < kctl->count; ++i)
		snd_ctl_notअगरy_one(ue->card, mask, kctl, i);

	वापस change;
पूर्ण

अटल पूर्णांक पढ़ो_user_tlv(काष्ठा snd_kcontrol *kctl, अचिन्हित पूर्णांक __user *buf,
			 अचिन्हित पूर्णांक size)
अणु
	काष्ठा user_element *ue = kctl->निजी_data;

	अगर (ue->tlv_data_size == 0 || ue->tlv_data == शून्य)
		वापस -ENXIO;

	अगर (size < ue->tlv_data_size)
		वापस -ENOSPC;

	अगर (copy_to_user(buf, ue->tlv_data, ue->tlv_data_size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_elem_user_tlv(काष्ठा snd_kcontrol *kctl, पूर्णांक op_flag,
				 अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *buf)
अणु
	अगर (op_flag == SNDRV_CTL_TLV_OP_WRITE)
		वापस replace_user_tlv(kctl, buf, size);
	अन्यथा
		वापस पढ़ो_user_tlv(kctl, buf, size);
पूर्ण

/* called in controls_rwsem ग_लिखो lock */
अटल पूर्णांक snd_ctl_elem_init_क्रमागत_names(काष्ठा user_element *ue)
अणु
	अक्षर *names, *p;
	माप_प्रकार buf_len, name_len;
	अचिन्हित पूर्णांक i;
	स्थिर uपूर्णांकptr_t user_ptrval = ue->info.value.क्रमागतerated.names_ptr;

	buf_len = ue->info.value.क्रमागतerated.names_length;
	अगर (buf_len > 64 * 1024)
		वापस -EINVAL;

	अगर (check_user_elem_overflow(ue->card, buf_len))
		वापस -ENOMEM;
	names = vmemdup_user((स्थिर व्योम __user *)user_ptrval, buf_len);
	अगर (IS_ERR(names))
		वापस PTR_ERR(names);

	/* check that there are enough valid names */
	p = names;
	क्रम (i = 0; i < ue->info.value.क्रमागतerated.items; ++i) अणु
		name_len = strnlen(p, buf_len);
		अगर (name_len == 0 || name_len >= 64 || name_len == buf_len) अणु
			kvमुक्त(names);
			वापस -EINVAL;
		पूर्ण
		p += name_len + 1;
		buf_len -= name_len + 1;
	पूर्ण

	ue->priv_data = names;
	ue->info.value.क्रमागतerated.names_ptr = 0;
	// increment the allocation size; decremented again at निजी_मुक्त.
	ue->card->user_ctl_alloc_size += ue->info.value.क्रमागतerated.names_length;

	वापस 0;
पूर्ण

अटल माप_प्रकार compute_user_elem_size(माप_प्रकार size, अचिन्हित पूर्णांक count)
अणु
	वापस माप(काष्ठा user_element) + size * count;
पूर्ण

अटल व्योम snd_ctl_elem_user_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा user_element *ue = kcontrol->निजी_data;

	// decrement the allocation size.
	ue->card->user_ctl_alloc_size -= compute_user_elem_size(ue->elem_data_size, kcontrol->count);
	ue->card->user_ctl_alloc_size -= ue->tlv_data_size;
	अगर (ue->priv_data)
		ue->card->user_ctl_alloc_size -= ue->info.value.क्रमागतerated.names_length;

	kvमुक्त(ue->tlv_data);
	kvमुक्त(ue->priv_data);
	kमुक्त(ue);
पूर्ण

अटल पूर्णांक snd_ctl_elem_add(काष्ठा snd_ctl_file *file,
			    काष्ठा snd_ctl_elem_info *info, पूर्णांक replace)
अणु
	काष्ठा snd_card *card = file->card;
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक access;
	दीर्घ निजी_size;
	माप_प्रकार alloc_size;
	काष्ठा user_element *ue;
	अचिन्हित पूर्णांक offset;
	पूर्णांक err;

	अगर (!*info->id.name)
		वापस -EINVAL;
	अगर (strnlen(info->id.name, माप(info->id.name)) >= माप(info->id.name))
		वापस -EINVAL;

	/* Delete a control to replace them अगर needed. */
	अगर (replace) अणु
		info->id.numid = 0;
		err = snd_ctl_हटाओ_user_ctl(file, &info->id);
		अगर (err)
			वापस err;
	पूर्ण

	/* Check the number of elements क्रम this userspace control. */
	count = info->owner;
	अगर (count == 0)
		count = 1;

	/* Arrange access permissions अगर needed. */
	access = info->access;
	अगर (access == 0)
		access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	access &= (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_INACTIVE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_WRITE);

	/* In initial state, nothing is available as TLV container. */
	अगर (access & SNDRV_CTL_ELEM_ACCESS_TLV_WRITE)
		access |= SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK;
	access |= SNDRV_CTL_ELEM_ACCESS_USER;

	/*
	 * Check inक्रमmation and calculate the size of data specअगरic to
	 * this userspace control.
	 */
	/* pass शून्य to card क्रम suppressing error messages */
	err = snd_ctl_check_elem_info(शून्य, info);
	अगर (err < 0)
		वापस err;
	/* user-space control करोesn't allow zero-size data */
	अगर (info->count < 1)
		वापस -EINVAL;
	निजी_size = value_sizes[info->type] * info->count;
	alloc_size = compute_user_elem_size(निजी_size, count);

	करोwn_ग_लिखो(&card->controls_rwsem);
	अगर (check_user_elem_overflow(card, alloc_size)) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	/*
	 * Keep memory object क्रम this userspace control. After passing this
	 * code block, the instance should be मुक्तd by snd_ctl_मुक्त_one().
	 *
	 * Note that these elements in this control are locked.
	 */
	err = snd_ctl_new(&kctl, count, access, file);
	अगर (err < 0)
		जाओ unlock;
	स_नकल(&kctl->id, &info->id, माप(kctl->id));
	ue = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!ue) अणु
		kमुक्त(kctl);
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण
	kctl->निजी_data = ue;
	kctl->निजी_मुक्त = snd_ctl_elem_user_मुक्त;

	// increment the allocated size; decremented again at निजी_मुक्त.
	card->user_ctl_alloc_size += alloc_size;

	/* Set निजी data क्रम this userspace control. */
	ue->card = card;
	ue->info = *info;
	ue->info.access = 0;
	ue->elem_data = (अक्षर *)ue + माप(*ue);
	ue->elem_data_size = निजी_size;
	अगर (ue->info.type == SNDRV_CTL_ELEM_TYPE_ENUMERATED) अणु
		err = snd_ctl_elem_init_क्रमागत_names(ue);
		अगर (err < 0) अणु
			snd_ctl_मुक्त_one(kctl);
			जाओ unlock;
		पूर्ण
	पूर्ण

	/* Set callback functions. */
	अगर (info->type == SNDRV_CTL_ELEM_TYPE_ENUMERATED)
		kctl->info = snd_ctl_elem_user_क्रमागत_info;
	अन्यथा
		kctl->info = snd_ctl_elem_user_info;
	अगर (access & SNDRV_CTL_ELEM_ACCESS_READ)
		kctl->get = snd_ctl_elem_user_get;
	अगर (access & SNDRV_CTL_ELEM_ACCESS_WRITE)
		kctl->put = snd_ctl_elem_user_put;
	अगर (access & SNDRV_CTL_ELEM_ACCESS_TLV_WRITE)
		kctl->tlv.c = snd_ctl_elem_user_tlv;

	/* This function manage to मुक्त the instance on failure. */
	err = __snd_ctl_add_replace(card, kctl, CTL_ADD_EXCLUSIVE);
	अगर (err < 0) अणु
		snd_ctl_मुक्त_one(kctl);
		जाओ unlock;
	पूर्ण
	offset = snd_ctl_get_ioff(kctl, &info->id);
	snd_ctl_build_ioff(&info->id, kctl, offset);
	/*
	 * Here we cannot fill any field क्रम the number of elements added by
	 * this operation because there're no specअगरic fields. The usage of
	 * 'owner' field क्रम this purpose may cause any bugs to userspace
	 * applications because the field originally means PID of a process
	 * which locks the element.
	 */
 unlock:
	up_ग_लिखो(&card->controls_rwsem);
	वापस err;
पूर्ण

अटल पूर्णांक snd_ctl_elem_add_user(काष्ठा snd_ctl_file *file,
				 काष्ठा snd_ctl_elem_info __user *_info, पूर्णांक replace)
अणु
	काष्ठा snd_ctl_elem_info info;
	पूर्णांक err;

	अगर (copy_from_user(&info, _info, माप(info)))
		वापस -EFAULT;
	err = snd_ctl_elem_add(file, &info, replace);
	अगर (err < 0)
		वापस err;
	अगर (copy_to_user(_info, &info, माप(info))) अणु
		snd_ctl_हटाओ_user_ctl(file, &info.id);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_elem_हटाओ(काष्ठा snd_ctl_file *file,
			       काष्ठा snd_ctl_elem_id __user *_id)
अणु
	काष्ठा snd_ctl_elem_id id;

	अगर (copy_from_user(&id, _id, माप(id)))
		वापस -EFAULT;
	वापस snd_ctl_हटाओ_user_ctl(file, &id);
पूर्ण

अटल पूर्णांक snd_ctl_subscribe_events(काष्ठा snd_ctl_file *file, पूर्णांक __user *ptr)
अणु
	पूर्णांक subscribe;
	अगर (get_user(subscribe, ptr))
		वापस -EFAULT;
	अगर (subscribe < 0) अणु
		subscribe = file->subscribed;
		अगर (put_user(subscribe, ptr))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	अगर (subscribe) अणु
		file->subscribed = 1;
		वापस 0;
	पूर्ण अन्यथा अगर (file->subscribed) अणु
		snd_ctl_empty_पढ़ो_queue(file);
		file->subscribed = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक call_tlv_handler(काष्ठा snd_ctl_file *file, पूर्णांक op_flag,
			    काष्ठा snd_kcontrol *kctl,
			    काष्ठा snd_ctl_elem_id *id,
			    अचिन्हित पूर्णांक __user *buf, अचिन्हित पूर्णांक size)
अणु
	अटल स्थिर काष्ठा अणु
		पूर्णांक op;
		पूर्णांक perm;
	पूर्ण pairs[] = अणु
		अणुSNDRV_CTL_TLV_OP_READ,  SNDRV_CTL_ELEM_ACCESS_TLV_READपूर्ण,
		अणुSNDRV_CTL_TLV_OP_WRITE, SNDRV_CTL_ELEM_ACCESS_TLV_WRITEपूर्ण,
		अणुSNDRV_CTL_TLV_OP_CMD,   SNDRV_CTL_ELEM_ACCESS_TLV_COMMANDपूर्ण,
	पूर्ण;
	काष्ठा snd_kcontrol_अस्थिर *vd = &kctl->vd[snd_ctl_get_ioff(kctl, id)];
	पूर्णांक i;

	/* Check support of the request क्रम this element. */
	क्रम (i = 0; i < ARRAY_SIZE(pairs); ++i) अणु
		अगर (op_flag == pairs[i].op && (vd->access & pairs[i].perm))
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(pairs))
		वापस -ENXIO;

	अगर (kctl->tlv.c == शून्य)
		वापस -ENXIO;

	/* Write and command operations are not allowed क्रम locked element. */
	अगर (op_flag != SNDRV_CTL_TLV_OP_READ &&
	    vd->owner != शून्य && vd->owner != file)
		वापस -EPERM;

	वापस kctl->tlv.c(kctl, op_flag, size, buf);
पूर्ण

अटल पूर्णांक पढ़ो_tlv_buf(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_id *id,
			अचिन्हित पूर्णांक __user *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा snd_kcontrol_अस्थिर *vd = &kctl->vd[snd_ctl_get_ioff(kctl, id)];
	अचिन्हित पूर्णांक len;

	अगर (!(vd->access & SNDRV_CTL_ELEM_ACCESS_TLV_READ))
		वापस -ENXIO;

	अगर (kctl->tlv.p == शून्य)
		वापस -ENXIO;

	len = माप(अचिन्हित पूर्णांक) * 2 + kctl->tlv.p[1];
	अगर (size < len)
		वापस -ENOMEM;

	अगर (copy_to_user(buf, kctl->tlv.p, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ctl_tlv_ioctl(काष्ठा snd_ctl_file *file,
			     काष्ठा snd_ctl_tlv __user *buf,
                             पूर्णांक op_flag)
अणु
	काष्ठा snd_ctl_tlv header;
	अचिन्हित पूर्णांक __user *container;
	अचिन्हित पूर्णांक container_size;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_ctl_elem_id id;
	काष्ठा snd_kcontrol_अस्थिर *vd;

	अगर (copy_from_user(&header, buf, माप(header)))
		वापस -EFAULT;

	/* In design of control core, numerical ID starts at 1. */
	अगर (header.numid == 0)
		वापस -EINVAL;

	/* At least, container should include type and length fields.  */
	अगर (header.length < माप(अचिन्हित पूर्णांक) * 2)
		वापस -EINVAL;
	container_size = header.length;
	container = buf->tlv;

	kctl = snd_ctl_find_numid(file->card, header.numid);
	अगर (kctl == शून्य)
		वापस -ENOENT;

	/* Calculate index of the element in this set. */
	id = kctl->id;
	snd_ctl_build_ioff(&id, kctl, header.numid - id.numid);
	vd = &kctl->vd[snd_ctl_get_ioff(kctl, &id)];

	अगर (vd->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) अणु
		वापस call_tlv_handler(file, op_flag, kctl, &id, container,
					container_size);
	पूर्ण अन्यथा अणु
		अगर (op_flag == SNDRV_CTL_TLV_OP_READ) अणु
			वापस पढ़ो_tlv_buf(kctl, &id, container,
					    container_size);
		पूर्ण
	पूर्ण

	/* Not supported. */
	वापस -ENXIO;
पूर्ण

अटल दीर्घ snd_ctl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_ctl_file *ctl;
	काष्ठा snd_card *card;
	काष्ठा snd_kctl_ioctl *p;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *ip = argp;
	पूर्णांक err;

	ctl = file->निजी_data;
	card = ctl->card;
	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;
	चयन (cmd) अणु
	हाल SNDRV_CTL_IOCTL_PVERSION:
		वापस put_user(SNDRV_CTL_VERSION, ip) ? -EFAULT : 0;
	हाल SNDRV_CTL_IOCTL_CARD_INFO:
		वापस snd_ctl_card_info(card, ctl, cmd, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_LIST:
		वापस snd_ctl_elem_list_user(card, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_INFO:
		वापस snd_ctl_elem_info_user(ctl, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_READ:
		वापस snd_ctl_elem_पढ़ो_user(card, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_WRITE:
		वापस snd_ctl_elem_ग_लिखो_user(ctl, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_LOCK:
		वापस snd_ctl_elem_lock(ctl, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_UNLOCK:
		वापस snd_ctl_elem_unlock(ctl, argp);
	हाल SNDRV_CTL_IOCTL_ELEM_ADD:
		वापस snd_ctl_elem_add_user(ctl, argp, 0);
	हाल SNDRV_CTL_IOCTL_ELEM_REPLACE:
		वापस snd_ctl_elem_add_user(ctl, argp, 1);
	हाल SNDRV_CTL_IOCTL_ELEM_REMOVE:
		वापस snd_ctl_elem_हटाओ(ctl, argp);
	हाल SNDRV_CTL_IOCTL_SUBSCRIBE_EVENTS:
		वापस snd_ctl_subscribe_events(ctl, ip);
	हाल SNDRV_CTL_IOCTL_TLV_READ:
		करोwn_पढ़ो(&ctl->card->controls_rwsem);
		err = snd_ctl_tlv_ioctl(ctl, argp, SNDRV_CTL_TLV_OP_READ);
		up_पढ़ो(&ctl->card->controls_rwsem);
		वापस err;
	हाल SNDRV_CTL_IOCTL_TLV_WRITE:
		करोwn_ग_लिखो(&ctl->card->controls_rwsem);
		err = snd_ctl_tlv_ioctl(ctl, argp, SNDRV_CTL_TLV_OP_WRITE);
		up_ग_लिखो(&ctl->card->controls_rwsem);
		वापस err;
	हाल SNDRV_CTL_IOCTL_TLV_COMMAND:
		करोwn_ग_लिखो(&ctl->card->controls_rwsem);
		err = snd_ctl_tlv_ioctl(ctl, argp, SNDRV_CTL_TLV_OP_CMD);
		up_ग_लिखो(&ctl->card->controls_rwsem);
		वापस err;
	हाल SNDRV_CTL_IOCTL_POWER:
		वापस -ENOPROTOOPT;
	हाल SNDRV_CTL_IOCTL_POWER_STATE:
#अगर_घोषित CONFIG_PM
		वापस put_user(card->घातer_state, ip) ? -EFAULT : 0;
#अन्यथा
		वापस put_user(SNDRV_CTL_POWER_D0, ip) ? -EFAULT : 0;
#पूर्ण_अगर
	पूर्ण
	करोwn_पढ़ो(&snd_ioctl_rwsem);
	list_क्रम_each_entry(p, &snd_control_ioctls, list) अणु
		err = p->fioctl(card, ctl, cmd, arg);
		अगर (err != -ENOIOCTLCMD) अणु
			up_पढ़ो(&snd_ioctl_rwsem);
			वापस err;
		पूर्ण
	पूर्ण
	up_पढ़ो(&snd_ioctl_rwsem);
	dev_dbg(card->dev, "unknown ioctl = 0x%x\n", cmd);
	वापस -ENOTTY;
पूर्ण

अटल sमाप_प्रकार snd_ctl_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			    माप_प्रकार count, loff_t * offset)
अणु
	काष्ठा snd_ctl_file *ctl;
	पूर्णांक err = 0;
	sमाप_प्रकार result = 0;

	ctl = file->निजी_data;
	अगर (snd_BUG_ON(!ctl || !ctl->card))
		वापस -ENXIO;
	अगर (!ctl->subscribed)
		वापस -EBADFD;
	अगर (count < माप(काष्ठा snd_ctl_event))
		वापस -EINVAL;
	spin_lock_irq(&ctl->पढ़ो_lock);
	जबतक (count >= माप(काष्ठा snd_ctl_event)) अणु
		काष्ठा snd_ctl_event ev;
		काष्ठा snd_kctl_event *kev;
		जबतक (list_empty(&ctl->events)) अणु
			रुको_queue_entry_t रुको;
			अगर ((file->f_flags & O_NONBLOCK) != 0 || result > 0) अणु
				err = -EAGAIN;
				जाओ __end_lock;
			पूर्ण
			init_रुकोqueue_entry(&रुको, current);
			add_रुको_queue(&ctl->change_sleep, &रुको);
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&ctl->पढ़ो_lock);
			schedule();
			हटाओ_रुको_queue(&ctl->change_sleep, &रुको);
			अगर (ctl->card->shutकरोwn)
				वापस -ENODEV;
			अगर (संकेत_pending(current))
				वापस -ERESTARTSYS;
			spin_lock_irq(&ctl->पढ़ो_lock);
		पूर्ण
		kev = snd_kctl_event(ctl->events.next);
		ev.type = SNDRV_CTL_EVENT_ELEM;
		ev.data.elem.mask = kev->mask;
		ev.data.elem.id = kev->id;
		list_del(&kev->list);
		spin_unlock_irq(&ctl->पढ़ो_lock);
		kमुक्त(kev);
		अगर (copy_to_user(buffer, &ev, माप(काष्ठा snd_ctl_event))) अणु
			err = -EFAULT;
			जाओ __end;
		पूर्ण
		spin_lock_irq(&ctl->पढ़ो_lock);
		buffer += माप(काष्ठा snd_ctl_event);
		count -= माप(काष्ठा snd_ctl_event);
		result += माप(काष्ठा snd_ctl_event);
	पूर्ण
      __end_lock:
	spin_unlock_irq(&ctl->पढ़ो_lock);
      __end:
      	वापस result > 0 ? result : err;
पूर्ण

अटल __poll_t snd_ctl_poll(काष्ठा file *file, poll_table * रुको)
अणु
	__poll_t mask;
	काष्ठा snd_ctl_file *ctl;

	ctl = file->निजी_data;
	अगर (!ctl->subscribed)
		वापस 0;
	poll_रुको(file, &ctl->change_sleep, रुको);

	mask = 0;
	अगर (!list_empty(&ctl->events))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

/*
 * रेजिस्टर the device-specअगरic control-ioctls.
 * called from each device manager like pcm.c, hwdep.c, etc.
 */
अटल पूर्णांक _snd_ctl_रेजिस्टर_ioctl(snd_kctl_ioctl_func_t fcn, काष्ठा list_head *lists)
अणु
	काष्ठा snd_kctl_ioctl *pn;

	pn = kzalloc(माप(काष्ठा snd_kctl_ioctl), GFP_KERNEL);
	अगर (pn == शून्य)
		वापस -ENOMEM;
	pn->fioctl = fcn;
	करोwn_ग_लिखो(&snd_ioctl_rwsem);
	list_add_tail(&pn->list, lists);
	up_ग_लिखो(&snd_ioctl_rwsem);
	वापस 0;
पूर्ण

/**
 * snd_ctl_रेजिस्टर_ioctl - रेजिस्टर the device-specअगरic control-ioctls
 * @fcn: ioctl callback function
 *
 * called from each device manager like pcm.c, hwdep.c, etc.
 */
पूर्णांक snd_ctl_रेजिस्टर_ioctl(snd_kctl_ioctl_func_t fcn)
अणु
	वापस _snd_ctl_रेजिस्टर_ioctl(fcn, &snd_control_ioctls);
पूर्ण
EXPORT_SYMBOL(snd_ctl_रेजिस्टर_ioctl);

#अगर_घोषित CONFIG_COMPAT
/**
 * snd_ctl_रेजिस्टर_ioctl_compat - रेजिस्टर the device-specअगरic 32bit compat
 * control-ioctls
 * @fcn: ioctl callback function
 */
पूर्णांक snd_ctl_रेजिस्टर_ioctl_compat(snd_kctl_ioctl_func_t fcn)
अणु
	वापस _snd_ctl_रेजिस्टर_ioctl(fcn, &snd_control_compat_ioctls);
पूर्ण
EXPORT_SYMBOL(snd_ctl_रेजिस्टर_ioctl_compat);
#पूर्ण_अगर

/*
 * de-रेजिस्टर the device-specअगरic control-ioctls.
 */
अटल पूर्णांक _snd_ctl_unरेजिस्टर_ioctl(snd_kctl_ioctl_func_t fcn,
				     काष्ठा list_head *lists)
अणु
	काष्ठा snd_kctl_ioctl *p;

	अगर (snd_BUG_ON(!fcn))
		वापस -EINVAL;
	करोwn_ग_लिखो(&snd_ioctl_rwsem);
	list_क्रम_each_entry(p, lists, list) अणु
		अगर (p->fioctl == fcn) अणु
			list_del(&p->list);
			up_ग_लिखो(&snd_ioctl_rwsem);
			kमुक्त(p);
			वापस 0;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&snd_ioctl_rwsem);
	snd_BUG();
	वापस -EINVAL;
पूर्ण

/**
 * snd_ctl_unरेजिस्टर_ioctl - de-रेजिस्टर the device-specअगरic control-ioctls
 * @fcn: ioctl callback function to unरेजिस्टर
 */
पूर्णांक snd_ctl_unरेजिस्टर_ioctl(snd_kctl_ioctl_func_t fcn)
अणु
	वापस _snd_ctl_unरेजिस्टर_ioctl(fcn, &snd_control_ioctls);
पूर्ण
EXPORT_SYMBOL(snd_ctl_unरेजिस्टर_ioctl);

#अगर_घोषित CONFIG_COMPAT
/**
 * snd_ctl_unरेजिस्टर_ioctl_compat - de-रेजिस्टर the device-specअगरic compat
 * 32bit control-ioctls
 * @fcn: ioctl callback function to unरेजिस्टर
 */
पूर्णांक snd_ctl_unरेजिस्टर_ioctl_compat(snd_kctl_ioctl_func_t fcn)
अणु
	वापस _snd_ctl_unरेजिस्टर_ioctl(fcn, &snd_control_compat_ioctls);
पूर्ण
EXPORT_SYMBOL(snd_ctl_unरेजिस्टर_ioctl_compat);
#पूर्ण_अगर

अटल पूर्णांक snd_ctl_fasync(पूर्णांक fd, काष्ठा file * file, पूर्णांक on)
अणु
	काष्ठा snd_ctl_file *ctl;

	ctl = file->निजी_data;
	वापस fasync_helper(fd, file, on, &ctl->fasync);
पूर्ण

/* वापस the preferred subdevice number अगर alपढ़ोy asचिन्हित;
 * otherwise वापस -1
 */
पूर्णांक snd_ctl_get_preferred_subdevice(काष्ठा snd_card *card, पूर्णांक type)
अणु
	काष्ठा snd_ctl_file *kctl;
	पूर्णांक subdevice = -1;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&card->ctl_files_rwlock, flags);
	list_क्रम_each_entry(kctl, &card->ctl_files, list) अणु
		अगर (kctl->pid == task_pid(current)) अणु
			subdevice = kctl->preferred_subdevice[type];
			अगर (subdevice != -1)
				अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_irqrestore(&card->ctl_files_rwlock, flags);
	वापस subdevice;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ctl_get_preferred_subdevice);

/*
 * ioctl32 compat
 */
#अगर_घोषित CONFIG_COMPAT
#समावेश "control_compat.c"
#अन्यथा
#घोषणा snd_ctl_ioctl_compat	शून्य
#पूर्ण_अगर

/*
 * control layers (audio LED etc.)
 */

/**
 * snd_ctl_request_layer - request to use the layer
 * @module_name: Name of the kernel module (शून्य == build-in)
 *
 * Return an error code when the module cannot be loaded.
 */
पूर्णांक snd_ctl_request_layer(स्थिर अक्षर *module_name)
अणु
	काष्ठा snd_ctl_layer_ops *lops;

	अगर (module_name == शून्य)
		वापस 0;
	करोwn_पढ़ो(&snd_ctl_layer_rwsem);
	क्रम (lops = snd_ctl_layer; lops; lops = lops->next)
		अगर (म_भेद(lops->module_name, module_name) == 0)
			अवरोध;
	up_पढ़ो(&snd_ctl_layer_rwsem);
	अगर (lops)
		वापस 0;
	वापस request_module(module_name);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ctl_request_layer);

/**
 * snd_ctl_रेजिस्टर_layer - रेजिस्टर new control layer
 * @lops: operation काष्ठाure
 *
 * The new layer can track all control elements and करो additional
 * operations on top (like audio LED handling).
 */
व्योम snd_ctl_रेजिस्टर_layer(काष्ठा snd_ctl_layer_ops *lops)
अणु
	काष्ठा snd_card *card;
	पूर्णांक card_number;

	करोwn_ग_लिखो(&snd_ctl_layer_rwsem);
	lops->next = snd_ctl_layer;
	snd_ctl_layer = lops;
	up_ग_लिखो(&snd_ctl_layer_rwsem);
	क्रम (card_number = 0; card_number < SNDRV_CARDS; card_number++) अणु
		card = snd_card_ref(card_number);
		अगर (card) अणु
			करोwn_पढ़ो(&card->controls_rwsem);
			lops->lरेजिस्टर(card);
			up_पढ़ो(&card->controls_rwsem);
			snd_card_unref(card);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_ctl_रेजिस्टर_layer);

/**
 * snd_ctl_disconnect_layer - disconnect control layer
 * @lops: operation काष्ठाure
 *
 * It is expected that the inक्रमmation about tracked cards
 * is मुक्तd beक्रमe this call (the disconnect callback is
 * not called here).
 */
व्योम snd_ctl_disconnect_layer(काष्ठा snd_ctl_layer_ops *lops)
अणु
	काष्ठा snd_ctl_layer_ops *lops2, *prev_lops2;

	करोwn_ग_लिखो(&snd_ctl_layer_rwsem);
	क्रम (lops2 = snd_ctl_layer, prev_lops2 = शून्य; lops2; lops2 = lops2->next) अणु
		अगर (lops2 == lops) अणु
			अगर (!prev_lops2)
				snd_ctl_layer = lops->next;
			अन्यथा
				prev_lops2->next = lops->next;
			अवरोध;
		पूर्ण
		prev_lops2 = lops2;
	पूर्ण
	up_ग_लिखो(&snd_ctl_layer_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ctl_disconnect_layer);

/*
 *  INIT PART
 */

अटल स्थिर काष्ठा file_operations snd_ctl_f_ops =
अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		snd_ctl_पढ़ो,
	.खोलो =		snd_ctl_खोलो,
	.release =	snd_ctl_release,
	.llseek =	no_llseek,
	.poll =		snd_ctl_poll,
	.unlocked_ioctl =	snd_ctl_ioctl,
	.compat_ioctl =	snd_ctl_ioctl_compat,
	.fasync =	snd_ctl_fasync,
पूर्ण;

/*
 * registration of the control device
 */
अटल पूर्णांक snd_ctl_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	काष्ठा snd_card *card = device->device_data;
	काष्ठा snd_ctl_layer_ops *lops;
	पूर्णांक err;

	err = snd_रेजिस्टर_device(SNDRV_DEVICE_TYPE_CONTROL, card, -1,
				  &snd_ctl_f_ops, card, &card->ctl_dev);
	अगर (err < 0)
		वापस err;
	करोwn_पढ़ो(&card->controls_rwsem);
	करोwn_पढ़ो(&snd_ctl_layer_rwsem);
	क्रम (lops = snd_ctl_layer; lops; lops = lops->next)
		lops->lरेजिस्टर(card);
	up_पढ़ो(&snd_ctl_layer_rwsem);
	up_पढ़ो(&card->controls_rwsem);
	वापस 0;
पूर्ण

/*
 * disconnection of the control device
 */
अटल पूर्णांक snd_ctl_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा snd_card *card = device->device_data;
	काष्ठा snd_ctl_file *ctl;
	काष्ठा snd_ctl_layer_ops *lops;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&card->ctl_files_rwlock, flags);
	list_क्रम_each_entry(ctl, &card->ctl_files, list) अणु
		wake_up(&ctl->change_sleep);
		समाप्त_fasync(&ctl->fasync, SIGIO, POLL_ERR);
	पूर्ण
	पढ़ो_unlock_irqrestore(&card->ctl_files_rwlock, flags);

	करोwn_पढ़ो(&card->controls_rwsem);
	करोwn_पढ़ो(&snd_ctl_layer_rwsem);
	क्रम (lops = snd_ctl_layer; lops; lops = lops->next)
		lops->ldisconnect(card);
	up_पढ़ो(&snd_ctl_layer_rwsem);
	up_पढ़ो(&card->controls_rwsem);

	वापस snd_unरेजिस्टर_device(&card->ctl_dev);
पूर्ण

/*
 * मुक्त all controls
 */
अटल पूर्णांक snd_ctl_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_card *card = device->device_data;
	काष्ठा snd_kcontrol *control;

	करोwn_ग_लिखो(&card->controls_rwsem);
	जबतक (!list_empty(&card->controls)) अणु
		control = snd_kcontrol(card->controls.next);
		snd_ctl_हटाओ(card, control);
	पूर्ण
	up_ग_लिखो(&card->controls_rwsem);
	put_device(&card->ctl_dev);
	वापस 0;
पूर्ण

/*
 * create control core:
 * called from init.c
 */
पूर्णांक snd_ctl_create(काष्ठा snd_card *card)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_ctl_dev_मुक्त,
		.dev_रेजिस्टर =	snd_ctl_dev_रेजिस्टर,
		.dev_disconnect = snd_ctl_dev_disconnect,
	पूर्ण;
	पूर्णांक err;

	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;
	अगर (snd_BUG_ON(card->number < 0 || card->number >= SNDRV_CARDS))
		वापस -ENXIO;

	snd_device_initialize(&card->ctl_dev, card);
	dev_set_name(&card->ctl_dev, "controlC%d", card->number);

	err = snd_device_new(card, SNDRV_DEV_CONTROL, card, &ops);
	अगर (err < 0)
		put_device(&card->ctl_dev);
	वापस err;
पूर्ण

/*
 * Frequently used control callbacks/helpers
 */

/**
 * snd_ctl_boolean_mono_info - Helper function क्रम a standard boolean info
 * callback with a mono channel
 * @kcontrol: the kcontrol instance
 * @uinfo: info to store
 *
 * This is a function that can be used as info callback क्रम a standard
 * boolean control with a single mono channel.
 */
पूर्णांक snd_ctl_boolean_mono_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_ctl_boolean_mono_info);

/**
 * snd_ctl_boolean_stereo_info - Helper function क्रम a standard boolean info
 * callback with stereo two channels
 * @kcontrol: the kcontrol instance
 * @uinfo: info to store
 *
 * This is a function that can be used as info callback क्रम a standard
 * boolean control with stereo two channels.
 */
पूर्णांक snd_ctl_boolean_stereo_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_ctl_boolean_stereo_info);

/**
 * snd_ctl_क्रमागत_info - fills the info काष्ठाure क्रम an क्रमागतerated control
 * @info: the काष्ठाure to be filled
 * @channels: the number of the control's channels; often one
 * @items: the number of control values; also the size of @names
 * @names: an array containing the names of all control values
 *
 * Sets all required fields in @info to their appropriate values.
 * If the control's accessibility is not the शेष (पढ़ोable and writable),
 * the caller has to fill @info->access.
 *
 * Return: Zero.
 */
पूर्णांक snd_ctl_क्रमागत_info(काष्ठा snd_ctl_elem_info *info, अचिन्हित पूर्णांक channels,
		      अचिन्हित पूर्णांक items, स्थिर अक्षर *स्थिर names[])
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	info->count = channels;
	info->value.क्रमागतerated.items = items;
	अगर (!items)
		वापस 0;
	अगर (info->value.क्रमागतerated.item >= items)
		info->value.क्रमागतerated.item = items - 1;
	WARN(म_माप(names[info->value.क्रमागतerated.item]) >= माप(info->value.क्रमागतerated.name),
	     "ALSA: too long item name '%s'\n",
	     names[info->value.क्रमागतerated.item]);
	strscpy(info->value.क्रमागतerated.name,
		names[info->value.क्रमागतerated.item],
		माप(info->value.क्रमागतerated.name));
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_ctl_क्रमागत_info);

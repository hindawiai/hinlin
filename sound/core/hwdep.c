<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Hardware dependent layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/major.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/minors.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/info.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Hardware dependent layer");
MODULE_LICENSE("GPL");

अटल LIST_HEAD(snd_hwdep_devices);
अटल DEFINE_MUTEX(रेजिस्टर_mutex);

अटल पूर्णांक snd_hwdep_dev_मुक्त(काष्ठा snd_device *device);
अटल पूर्णांक snd_hwdep_dev_रेजिस्टर(काष्ठा snd_device *device);
अटल पूर्णांक snd_hwdep_dev_disconnect(काष्ठा snd_device *device);


अटल काष्ठा snd_hwdep *snd_hwdep_search(काष्ठा snd_card *card, पूर्णांक device)
अणु
	काष्ठा snd_hwdep *hwdep;

	list_क्रम_each_entry(hwdep, &snd_hwdep_devices, list)
		अगर (hwdep->card == card && hwdep->device == device)
			वापस hwdep;
	वापस शून्य;
पूर्ण

अटल loff_t snd_hwdep_llseek(काष्ठा file * file, loff_t offset, पूर्णांक orig)
अणु
	काष्ठा snd_hwdep *hw = file->निजी_data;
	अगर (hw->ops.llseek)
		वापस hw->ops.llseek(hw, file, offset, orig);
	वापस -ENXIO;
पूर्ण

अटल sमाप_प्रकार snd_hwdep_पढ़ो(काष्ठा file * file, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा snd_hwdep *hw = file->निजी_data;
	अगर (hw->ops.पढ़ो)
		वापस hw->ops.पढ़ो(hw, buf, count, offset);
	वापस -ENXIO;	
पूर्ण

अटल sमाप_प्रकार snd_hwdep_ग_लिखो(काष्ठा file * file, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा snd_hwdep *hw = file->निजी_data;
	अगर (hw->ops.ग_लिखो)
		वापस hw->ops.ग_लिखो(hw, buf, count, offset);
	वापस -ENXIO;	
पूर्ण

अटल पूर्णांक snd_hwdep_खोलो(काष्ठा inode *inode, काष्ठा file * file)
अणु
	पूर्णांक major = imajor(inode);
	काष्ठा snd_hwdep *hw;
	पूर्णांक err;
	रुको_queue_entry_t रुको;

	अगर (major == snd_major) अणु
		hw = snd_lookup_minor_data(iminor(inode),
					   SNDRV_DEVICE_TYPE_HWDEP);
#अगर_घोषित CONFIG_SND_OSSEMUL
	पूर्ण अन्यथा अगर (major == SOUND_MAJOR) अणु
		hw = snd_lookup_oss_minor_data(iminor(inode),
					       SNDRV_OSS_DEVICE_TYPE_DMFM);
#पूर्ण_अगर
	पूर्ण अन्यथा
		वापस -ENXIO;
	अगर (hw == शून्य)
		वापस -ENODEV;

	अगर (!try_module_get(hw->card->module)) अणु
		snd_card_unref(hw->card);
		वापस -EFAULT;
	पूर्ण

	init_रुकोqueue_entry(&रुको, current);
	add_रुको_queue(&hw->खोलो_रुको, &रुको);
	mutex_lock(&hw->खोलो_mutex);
	जबतक (1) अणु
		अगर (hw->exclusive && hw->used > 0) अणु
			err = -EBUSY;
			अवरोध;
		पूर्ण
		अगर (!hw->ops.खोलो) अणु
			err = 0;
			अवरोध;
		पूर्ण
		err = hw->ops.खोलो(hw, file);
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
		mutex_unlock(&hw->खोलो_mutex);
		schedule();
		mutex_lock(&hw->खोलो_mutex);
		अगर (hw->card->shutकरोwn) अणु
			err = -ENODEV;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			अवरोध;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(&hw->खोलो_रुको, &रुको);
	अगर (err >= 0) अणु
		err = snd_card_file_add(hw->card, file);
		अगर (err >= 0) अणु
			file->निजी_data = hw;
			hw->used++;
		पूर्ण अन्यथा अणु
			अगर (hw->ops.release)
				hw->ops.release(hw, file);
		पूर्ण
	पूर्ण
	mutex_unlock(&hw->खोलो_mutex);
	अगर (err < 0)
		module_put(hw->card->module);
	snd_card_unref(hw->card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_hwdep_release(काष्ठा inode *inode, काष्ठा file * file)
अणु
	पूर्णांक err = 0;
	काष्ठा snd_hwdep *hw = file->निजी_data;
	काष्ठा module *mod = hw->card->module;

	mutex_lock(&hw->खोलो_mutex);
	अगर (hw->ops.release)
		err = hw->ops.release(hw, file);
	अगर (hw->used > 0)
		hw->used--;
	mutex_unlock(&hw->खोलो_mutex);
	wake_up(&hw->खोलो_रुको);

	snd_card_file_हटाओ(hw->card, file);
	module_put(mod);
	वापस err;
पूर्ण

अटल __poll_t snd_hwdep_poll(काष्ठा file * file, poll_table * रुको)
अणु
	काष्ठा snd_hwdep *hw = file->निजी_data;
	अगर (hw->ops.poll)
		वापस hw->ops.poll(hw, file, रुको);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hwdep_info(काष्ठा snd_hwdep *hw,
			  काष्ठा snd_hwdep_info __user *_info)
अणु
	काष्ठा snd_hwdep_info info;
	
	स_रखो(&info, 0, माप(info));
	info.card = hw->card->number;
	strscpy(info.id, hw->id, माप(info.id));
	strscpy(info.name, hw->name, माप(info.name));
	info.अगरace = hw->अगरace;
	अगर (copy_to_user(_info, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hwdep_dsp_status(काष्ठा snd_hwdep *hw,
				काष्ठा snd_hwdep_dsp_status __user *_info)
अणु
	काष्ठा snd_hwdep_dsp_status info;
	पूर्णांक err;
	
	अगर (! hw->ops.dsp_status)
		वापस -ENXIO;
	स_रखो(&info, 0, माप(info));
	info.dsp_loaded = hw->dsp_loaded;
	अगर ((err = hw->ops.dsp_status(hw, &info)) < 0)
		वापस err;
	अगर (copy_to_user(_info, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hwdep_dsp_load(काष्ठा snd_hwdep *hw,
			      काष्ठा snd_hwdep_dsp_image *info)
अणु
	पूर्णांक err;
	
	अगर (! hw->ops.dsp_load)
		वापस -ENXIO;
	अगर (info->index >= 32)
		वापस -EINVAL;
	/* check whether the dsp was alपढ़ोy loaded */
	अगर (hw->dsp_loaded & (1u << info->index))
		वापस -EBUSY;
	err = hw->ops.dsp_load(hw, info);
	अगर (err < 0)
		वापस err;
	hw->dsp_loaded |= (1u << info->index);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hwdep_dsp_load_user(काष्ठा snd_hwdep *hw,
				   काष्ठा snd_hwdep_dsp_image __user *_info)
अणु
	काष्ठा snd_hwdep_dsp_image info = अणुपूर्ण;

	अगर (copy_from_user(&info, _info, माप(info)))
		वापस -EFAULT;
	वापस snd_hwdep_dsp_load(hw, &info);
पूर्ण


अटल दीर्घ snd_hwdep_ioctl(काष्ठा file * file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_hwdep *hw = file->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	चयन (cmd) अणु
	हाल SNDRV_HWDEP_IOCTL_PVERSION:
		वापस put_user(SNDRV_HWDEP_VERSION, (पूर्णांक __user *)argp);
	हाल SNDRV_HWDEP_IOCTL_INFO:
		वापस snd_hwdep_info(hw, argp);
	हाल SNDRV_HWDEP_IOCTL_DSP_STATUS:
		वापस snd_hwdep_dsp_status(hw, argp);
	हाल SNDRV_HWDEP_IOCTL_DSP_LOAD:
		वापस snd_hwdep_dsp_load_user(hw, argp);
	पूर्ण
	अगर (hw->ops.ioctl)
		वापस hw->ops.ioctl(hw, file, cmd, arg);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक snd_hwdep_mmap(काष्ठा file * file, काष्ठा vm_area_काष्ठा * vma)
अणु
	काष्ठा snd_hwdep *hw = file->निजी_data;
	अगर (hw->ops.mmap)
		वापस hw->ops.mmap(hw, file, vma);
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक snd_hwdep_control_ioctl(काष्ठा snd_card *card,
				   काष्ठा snd_ctl_file * control,
				   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE:
		अणु
			पूर्णांक device;

			अगर (get_user(device, (पूर्णांक __user *)arg))
				वापस -EFAULT;
			mutex_lock(&रेजिस्टर_mutex);

			अगर (device < 0)
				device = 0;
			अन्यथा अगर (device < SNDRV_MINOR_HWDEPS)
				device++;
			अन्यथा
				device = SNDRV_MINOR_HWDEPS;

			जबतक (device < SNDRV_MINOR_HWDEPS) अणु
				अगर (snd_hwdep_search(card, device))
					अवरोध;
				device++;
			पूर्ण
			अगर (device >= SNDRV_MINOR_HWDEPS)
				device = -1;
			mutex_unlock(&रेजिस्टर_mutex);
			अगर (put_user(device, (पूर्णांक __user *)arg))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
	हाल SNDRV_CTL_IOCTL_HWDEP_INFO:
		अणु
			काष्ठा snd_hwdep_info __user *info = (काष्ठा snd_hwdep_info __user *)arg;
			पूर्णांक device, err;
			काष्ठा snd_hwdep *hwdep;

			अगर (get_user(device, &info->device))
				वापस -EFAULT;
			mutex_lock(&रेजिस्टर_mutex);
			hwdep = snd_hwdep_search(card, device);
			अगर (hwdep)
				err = snd_hwdep_info(hwdep, info);
			अन्यथा
				err = -ENXIO;
			mutex_unlock(&रेजिस्टर_mutex);
			वापस err;
		पूर्ण
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#समावेश "hwdep_compat.c"
#अन्यथा
#घोषणा snd_hwdep_ioctl_compat	शून्य
#पूर्ण_अगर

/*

 */

अटल स्थिर काष्ठा file_operations snd_hwdep_f_ops =
अणु
	.owner = 	THIS_MODULE,
	.llseek =	snd_hwdep_llseek,
	.पढ़ो = 	snd_hwdep_पढ़ो,
	.ग_लिखो =	snd_hwdep_ग_लिखो,
	.खोलो =		snd_hwdep_खोलो,
	.release =	snd_hwdep_release,
	.poll =		snd_hwdep_poll,
	.unlocked_ioctl =	snd_hwdep_ioctl,
	.compat_ioctl =	snd_hwdep_ioctl_compat,
	.mmap =		snd_hwdep_mmap,
पूर्ण;

अटल व्योम release_hwdep_device(काष्ठा device *dev)
अणु
	kमुक्त(container_of(dev, काष्ठा snd_hwdep, dev));
पूर्ण

/**
 * snd_hwdep_new - create a new hwdep instance
 * @card: the card instance
 * @id: the id string
 * @device: the device index (zero-based)
 * @rhwdep: the poपूर्णांकer to store the new hwdep instance
 *
 * Creates a new hwdep instance with the given index on the card.
 * The callbacks (hwdep->ops) must be set on the वापसed instance
 * after this call manually by the caller.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_hwdep_new(काष्ठा snd_card *card, अक्षर *id, पूर्णांक device,
		  काष्ठा snd_hwdep **rhwdep)
अणु
	काष्ठा snd_hwdep *hwdep;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_hwdep_dev_मुक्त,
		.dev_रेजिस्टर = snd_hwdep_dev_रेजिस्टर,
		.dev_disconnect = snd_hwdep_dev_disconnect,
	पूर्ण;

	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;
	अगर (rhwdep)
		*rhwdep = शून्य;
	hwdep = kzalloc(माप(*hwdep), GFP_KERNEL);
	अगर (!hwdep)
		वापस -ENOMEM;

	init_रुकोqueue_head(&hwdep->खोलो_रुको);
	mutex_init(&hwdep->खोलो_mutex);
	hwdep->card = card;
	hwdep->device = device;
	अगर (id)
		strscpy(hwdep->id, id, माप(hwdep->id));

	snd_device_initialize(&hwdep->dev, card);
	hwdep->dev.release = release_hwdep_device;
	dev_set_name(&hwdep->dev, "hwC%iD%i", card->number, device);
#अगर_घोषित CONFIG_SND_OSSEMUL
	hwdep->oss_type = -1;
#पूर्ण_अगर

	err = snd_device_new(card, SNDRV_DEV_HWDEP, hwdep, &ops);
	अगर (err < 0) अणु
		put_device(&hwdep->dev);
		वापस err;
	पूर्ण

	अगर (rhwdep)
		*rhwdep = hwdep;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_hwdep_new);

अटल पूर्णांक snd_hwdep_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_hwdep *hwdep = device->device_data;
	अगर (!hwdep)
		वापस 0;
	अगर (hwdep->निजी_मुक्त)
		hwdep->निजी_मुक्त(hwdep);
	put_device(&hwdep->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hwdep_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	काष्ठा snd_hwdep *hwdep = device->device_data;
	काष्ठा snd_card *card = hwdep->card;
	पूर्णांक err;

	mutex_lock(&रेजिस्टर_mutex);
	अगर (snd_hwdep_search(card, hwdep->device)) अणु
		mutex_unlock(&रेजिस्टर_mutex);
		वापस -EBUSY;
	पूर्ण
	list_add_tail(&hwdep->list, &snd_hwdep_devices);
	err = snd_रेजिस्टर_device(SNDRV_DEVICE_TYPE_HWDEP,
				  hwdep->card, hwdep->device,
				  &snd_hwdep_f_ops, hwdep, &hwdep->dev);
	अगर (err < 0) अणु
		dev_err(&hwdep->dev, "unable to register\n");
		list_del(&hwdep->list);
		mutex_unlock(&रेजिस्टर_mutex);
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_SND_OSSEMUL
	hwdep->ossreg = 0;
	अगर (hwdep->oss_type >= 0) अणु
		अगर (hwdep->oss_type == SNDRV_OSS_DEVICE_TYPE_DMFM &&
		    hwdep->device)
			dev_warn(&hwdep->dev,
				 "only hwdep device 0 can be registered as OSS direct FM device!\n");
		अन्यथा अगर (snd_रेजिस्टर_oss_device(hwdep->oss_type,
						 card, hwdep->device,
						 &snd_hwdep_f_ops, hwdep) < 0)
			dev_warn(&hwdep->dev,
				 "unable to register OSS compatibility device\n");
		अन्यथा
			hwdep->ossreg = 1;
	पूर्ण
#पूर्ण_अगर
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hwdep_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा snd_hwdep *hwdep = device->device_data;

	अगर (snd_BUG_ON(!hwdep))
		वापस -ENXIO;
	mutex_lock(&रेजिस्टर_mutex);
	अगर (snd_hwdep_search(hwdep->card, hwdep->device) != hwdep) अणु
		mutex_unlock(&रेजिस्टर_mutex);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&hwdep->खोलो_mutex);
	wake_up(&hwdep->खोलो_रुको);
#अगर_घोषित CONFIG_SND_OSSEMUL
	अगर (hwdep->ossreg)
		snd_unरेजिस्टर_oss_device(hwdep->oss_type, hwdep->card, hwdep->device);
#पूर्ण_अगर
	snd_unरेजिस्टर_device(&hwdep->dev);
	list_del_init(&hwdep->list);
	mutex_unlock(&hwdep->खोलो_mutex);
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_PROC_FS
/*
 *  Info पूर्णांकerface
 */

अटल व्योम snd_hwdep_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_hwdep *hwdep;

	mutex_lock(&रेजिस्टर_mutex);
	list_क्रम_each_entry(hwdep, &snd_hwdep_devices, list)
		snd_iम_लिखो(buffer, "%02i-%02i: %s\n",
			    hwdep->card->number, hwdep->device, hwdep->name);
	mutex_unlock(&रेजिस्टर_mutex);
पूर्ण

अटल काष्ठा snd_info_entry *snd_hwdep_proc_entry;

अटल व्योम __init snd_hwdep_proc_init(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	अगर ((entry = snd_info_create_module_entry(THIS_MODULE, "hwdep", शून्य)) != शून्य) अणु
		entry->c.text.पढ़ो = snd_hwdep_proc_पढ़ो;
		अगर (snd_info_रेजिस्टर(entry) < 0) अणु
			snd_info_मुक्त_entry(entry);
			entry = शून्य;
		पूर्ण
	पूर्ण
	snd_hwdep_proc_entry = entry;
पूर्ण

अटल व्योम __निकास snd_hwdep_proc_करोne(व्योम)
अणु
	snd_info_मुक्त_entry(snd_hwdep_proc_entry);
पूर्ण
#अन्यथा /* !CONFIG_SND_PROC_FS */
#घोषणा snd_hwdep_proc_init()
#घोषणा snd_hwdep_proc_करोne()
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */


/*
 *  ENTRY functions
 */

अटल पूर्णांक __init alsa_hwdep_init(व्योम)
अणु
	snd_hwdep_proc_init();
	snd_ctl_रेजिस्टर_ioctl(snd_hwdep_control_ioctl);
	snd_ctl_रेजिस्टर_ioctl_compat(snd_hwdep_control_ioctl);
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_hwdep_निकास(व्योम)
अणु
	snd_ctl_unरेजिस्टर_ioctl(snd_hwdep_control_ioctl);
	snd_ctl_unरेजिस्टर_ioctl_compat(snd_hwdep_control_ioctl);
	snd_hwdep_proc_करोne();
पूर्ण

module_init(alsa_hwdep_init)
module_निकास(alsa_hwdep_निकास)

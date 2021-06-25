<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ff-hwdep.c - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

/*
 * This codes give three functionality.
 *
 * 1.get firewire node inक्रमmation
 * 2.get notअगरication about starting/stopping stream
 * 3.lock/unlock stream
 */

#समावेश "ff.h"

अटल दीर्घ hwdep_पढ़ो(काष्ठा snd_hwdep *hwdep, अक्षर __user *buf,  दीर्घ count,
		       loff_t *offset)
अणु
	काष्ठा snd_ff *ff = hwdep->निजी_data;
	DEFINE_WAIT(रुको);
	जोड़ snd_firewire_event event;

	spin_lock_irq(&ff->lock);

	जबतक (!ff->dev_lock_changed) अणु
		prepare_to_रुको(&ff->hwdep_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_unlock_irq(&ff->lock);
		schedule();
		finish_रुको(&ff->hwdep_रुको, &रुको);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		spin_lock_irq(&ff->lock);
	पूर्ण

	स_रखो(&event, 0, माप(event));
	event.lock_status.type = SNDRV_FIREWIRE_EVENT_LOCK_STATUS;
	event.lock_status.status = (ff->dev_lock_count > 0);
	ff->dev_lock_changed = false;

	count = min_t(दीर्घ, count, माप(event.lock_status));

	spin_unlock_irq(&ff->lock);

	अगर (copy_to_user(buf, &event, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल __poll_t hwdep_poll(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
			       poll_table *रुको)
अणु
	काष्ठा snd_ff *ff = hwdep->निजी_data;
	__poll_t events;

	poll_रुको(file, &ff->hwdep_रुको, रुको);

	spin_lock_irq(&ff->lock);
	अगर (ff->dev_lock_changed)
		events = EPOLLIN | EPOLLRDNORM;
	अन्यथा
		events = 0;
	spin_unlock_irq(&ff->lock);

	वापस events;
पूर्ण

अटल पूर्णांक hwdep_get_info(काष्ठा snd_ff *ff, व्योम __user *arg)
अणु
	काष्ठा fw_device *dev = fw_parent_device(ff->unit);
	काष्ठा snd_firewire_get_info info;

	स_रखो(&info, 0, माप(info));
	info.type = SNDRV_FIREWIRE_TYPE_FIREFACE;
	info.card = dev->card->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_rom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_rom[4]);
	strscpy(info.device_name, dev_name(&dev->device),
		माप(info.device_name));

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_lock(काष्ठा snd_ff *ff)
अणु
	पूर्णांक err;

	spin_lock_irq(&ff->lock);

	अगर (ff->dev_lock_count == 0) अणु
		ff->dev_lock_count = -1;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBUSY;
	पूर्ण

	spin_unlock_irq(&ff->lock);

	वापस err;
पूर्ण

अटल पूर्णांक hwdep_unlock(काष्ठा snd_ff *ff)
अणु
	पूर्णांक err;

	spin_lock_irq(&ff->lock);

	अगर (ff->dev_lock_count == -1) अणु
		ff->dev_lock_count = 0;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBADFD;
	पूर्ण

	spin_unlock_irq(&ff->lock);

	वापस err;
पूर्ण

अटल पूर्णांक hwdep_release(काष्ठा snd_hwdep *hwdep, काष्ठा file *file)
अणु
	काष्ठा snd_ff *ff = hwdep->निजी_data;

	spin_lock_irq(&ff->lock);
	अगर (ff->dev_lock_count == -1)
		ff->dev_lock_count = 0;
	spin_unlock_irq(&ff->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_ioctl(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_ff *ff = hwdep->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_FIREWIRE_IOCTL_GET_INFO:
		वापस hwdep_get_info(ff, (व्योम __user *)arg);
	हाल SNDRV_FIREWIRE_IOCTL_LOCK:
		वापस hwdep_lock(ff);
	हाल SNDRV_FIREWIRE_IOCTL_UNLOCK:
		वापस hwdep_unlock(ff);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक hwdep_compat_ioctl(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस hwdep_ioctl(hwdep, file, cmd,
			   (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा hwdep_compat_ioctl शून्य
#पूर्ण_अगर

पूर्णांक snd_ff_create_hwdep_devices(काष्ठा snd_ff *ff)
अणु
	अटल स्थिर काष्ठा snd_hwdep_ops hwdep_ops = अणु
		.पढ़ो		= hwdep_पढ़ो,
		.release	= hwdep_release,
		.poll		= hwdep_poll,
		.ioctl		= hwdep_ioctl,
		.ioctl_compat	= hwdep_compat_ioctl,
	पूर्ण;
	काष्ठा snd_hwdep *hwdep;
	पूर्णांक err;

	err = snd_hwdep_new(ff->card, ff->card->driver, 0, &hwdep);
	अगर (err < 0)
		वापस err;

	म_नकल(hwdep->name, ff->card->driver);
	hwdep->अगरace = SNDRV_HWDEP_IFACE_FW_FIREFACE;
	hwdep->ops = hwdep_ops;
	hwdep->निजी_data = ff;
	hwdep->exclusive = true;

	वापस 0;
पूर्ण

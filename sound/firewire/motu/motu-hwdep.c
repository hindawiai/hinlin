<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu-hwdep.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

/*
 * This codes have five functionalities.
 *
 * 1.get inक्रमmation about firewire node
 * 2.get notअगरication about starting/stopping stream
 * 3.lock/unlock streaming
 *
 */

#समावेश "motu.h"

अटल दीर्घ hwdep_पढ़ो(काष्ठा snd_hwdep *hwdep, अक्षर __user *buf, दीर्घ count,
		       loff_t *offset)
अणु
	काष्ठा snd_motu *motu = hwdep->निजी_data;
	DEFINE_WAIT(रुको);
	जोड़ snd_firewire_event event;

	spin_lock_irq(&motu->lock);

	जबतक (!motu->dev_lock_changed && motu->msg == 0) अणु
		prepare_to_रुको(&motu->hwdep_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_unlock_irq(&motu->lock);
		schedule();
		finish_रुको(&motu->hwdep_रुको, &रुको);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		spin_lock_irq(&motu->lock);
	पूर्ण

	स_रखो(&event, 0, माप(event));
	अगर (motu->dev_lock_changed) अणु
		event.lock_status.type = SNDRV_FIREWIRE_EVENT_LOCK_STATUS;
		event.lock_status.status = (motu->dev_lock_count > 0);
		motu->dev_lock_changed = false;

		count = min_t(दीर्घ, count, माप(event.lock_status));
	पूर्ण अन्यथा अणु
		event.motu_notअगरication.type = SNDRV_FIREWIRE_EVENT_MOTU_NOTIFICATION;
		event.motu_notअगरication.message = motu->msg;
		motu->msg = 0;

		count = min_t(दीर्घ, count, माप(event.motu_notअगरication));
	पूर्ण

	spin_unlock_irq(&motu->lock);

	अगर (copy_to_user(buf, &event, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल __poll_t hwdep_poll(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
			       poll_table *रुको)
अणु
	काष्ठा snd_motu *motu = hwdep->निजी_data;
	__poll_t events;

	poll_रुको(file, &motu->hwdep_रुको, रुको);

	spin_lock_irq(&motu->lock);
	अगर (motu->dev_lock_changed || motu->msg)
		events = EPOLLIN | EPOLLRDNORM;
	अन्यथा
		events = 0;
	spin_unlock_irq(&motu->lock);

	वापस events | EPOLLOUT;
पूर्ण

अटल पूर्णांक hwdep_get_info(काष्ठा snd_motu *motu, व्योम __user *arg)
अणु
	काष्ठा fw_device *dev = fw_parent_device(motu->unit);
	काष्ठा snd_firewire_get_info info;

	स_रखो(&info, 0, माप(info));
	info.type = SNDRV_FIREWIRE_TYPE_MOTU;
	info.card = dev->card->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_rom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_rom[4]);
	strscpy(info.device_name, dev_name(&dev->device),
		माप(info.device_name));

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_lock(काष्ठा snd_motu *motu)
अणु
	पूर्णांक err;

	spin_lock_irq(&motu->lock);

	अगर (motu->dev_lock_count == 0) अणु
		motu->dev_lock_count = -1;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBUSY;
	पूर्ण

	spin_unlock_irq(&motu->lock);

	वापस err;
पूर्ण

अटल पूर्णांक hwdep_unlock(काष्ठा snd_motu *motu)
अणु
	पूर्णांक err;

	spin_lock_irq(&motu->lock);

	अगर (motu->dev_lock_count == -1) अणु
		motu->dev_lock_count = 0;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBADFD;
	पूर्ण

	spin_unlock_irq(&motu->lock);

	वापस err;
पूर्ण

अटल पूर्णांक hwdep_release(काष्ठा snd_hwdep *hwdep, काष्ठा file *file)
अणु
	काष्ठा snd_motu *motu = hwdep->निजी_data;

	spin_lock_irq(&motu->lock);
	अगर (motu->dev_lock_count == -1)
		motu->dev_lock_count = 0;
	spin_unlock_irq(&motu->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_ioctl(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
	    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_motu *motu = hwdep->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_FIREWIRE_IOCTL_GET_INFO:
		वापस hwdep_get_info(motu, (व्योम __user *)arg);
	हाल SNDRV_FIREWIRE_IOCTL_LOCK:
		वापस hwdep_lock(motu);
	हाल SNDRV_FIREWIRE_IOCTL_UNLOCK:
		वापस hwdep_unlock(motu);
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

पूर्णांक snd_motu_create_hwdep_device(काष्ठा snd_motu *motu)
अणु
	अटल स्थिर काष्ठा snd_hwdep_ops ops = अणु
		.पढ़ो		= hwdep_पढ़ो,
		.release	= hwdep_release,
		.poll		= hwdep_poll,
		.ioctl		= hwdep_ioctl,
		.ioctl_compat	= hwdep_compat_ioctl,
	पूर्ण;
	काष्ठा snd_hwdep *hwdep;
	पूर्णांक err;

	err = snd_hwdep_new(motu->card, motu->card->driver, 0, &hwdep);
	अगर (err < 0)
		वापस err;

	म_नकल(hwdep->name, "MOTU");
	hwdep->अगरace = SNDRV_HWDEP_IFACE_FW_MOTU;
	hwdep->ops = ops;
	hwdep->निजी_data = motu;
	hwdep->exclusive = true;

	वापस 0;
पूर्ण

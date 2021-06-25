<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_hwdep.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

/*
 * This codes give three functionality.
 *
 * 1.get firewire node infomation
 * 2.get notअगरication about starting/stopping stream
 * 3.lock/unlock stream
 */

#समावेश "bebob.h"

अटल दीर्घ
hwdep_पढ़ो(काष्ठा snd_hwdep *hwdep, अक्षर __user *buf,  दीर्घ count,
	   loff_t *offset)
अणु
	काष्ठा snd_bebob *bebob = hwdep->निजी_data;
	DEFINE_WAIT(रुको);
	जोड़ snd_firewire_event event;

	spin_lock_irq(&bebob->lock);

	जबतक (!bebob->dev_lock_changed) अणु
		prepare_to_रुको(&bebob->hwdep_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_unlock_irq(&bebob->lock);
		schedule();
		finish_रुको(&bebob->hwdep_रुको, &रुको);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		spin_lock_irq(&bebob->lock);
	पूर्ण

	स_रखो(&event, 0, माप(event));
	count = min_t(दीर्घ, count, माप(event.lock_status));
	event.lock_status.type = SNDRV_FIREWIRE_EVENT_LOCK_STATUS;
	event.lock_status.status = (bebob->dev_lock_count > 0);
	bebob->dev_lock_changed = false;

	spin_unlock_irq(&bebob->lock);

	अगर (copy_to_user(buf, &event, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल __poll_t
hwdep_poll(काष्ठा snd_hwdep *hwdep, काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा snd_bebob *bebob = hwdep->निजी_data;
	__poll_t events;

	poll_रुको(file, &bebob->hwdep_रुको, रुको);

	spin_lock_irq(&bebob->lock);
	अगर (bebob->dev_lock_changed)
		events = EPOLLIN | EPOLLRDNORM;
	अन्यथा
		events = 0;
	spin_unlock_irq(&bebob->lock);

	वापस events;
पूर्ण

अटल पूर्णांक
hwdep_get_info(काष्ठा snd_bebob *bebob, व्योम __user *arg)
अणु
	काष्ठा fw_device *dev = fw_parent_device(bebob->unit);
	काष्ठा snd_firewire_get_info info;

	स_रखो(&info, 0, माप(info));
	info.type = SNDRV_FIREWIRE_TYPE_BEBOB;
	info.card = dev->card->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_rom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_rom[4]);
	strscpy(info.device_name, dev_name(&dev->device),
		माप(info.device_name));

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
hwdep_lock(काष्ठा snd_bebob *bebob)
अणु
	पूर्णांक err;

	spin_lock_irq(&bebob->lock);

	अगर (bebob->dev_lock_count == 0) अणु
		bebob->dev_lock_count = -1;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBUSY;
	पूर्ण

	spin_unlock_irq(&bebob->lock);

	वापस err;
पूर्ण

अटल पूर्णांक
hwdep_unlock(काष्ठा snd_bebob *bebob)
अणु
	पूर्णांक err;

	spin_lock_irq(&bebob->lock);

	अगर (bebob->dev_lock_count == -1) अणु
		bebob->dev_lock_count = 0;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBADFD;
	पूर्ण

	spin_unlock_irq(&bebob->lock);

	वापस err;
पूर्ण

अटल पूर्णांक
hwdep_release(काष्ठा snd_hwdep *hwdep, काष्ठा file *file)
अणु
	काष्ठा snd_bebob *bebob = hwdep->निजी_data;

	spin_lock_irq(&bebob->lock);
	अगर (bebob->dev_lock_count == -1)
		bebob->dev_lock_count = 0;
	spin_unlock_irq(&bebob->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
hwdep_ioctl(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
	    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_bebob *bebob = hwdep->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_FIREWIRE_IOCTL_GET_INFO:
		वापस hwdep_get_info(bebob, (व्योम __user *)arg);
	हाल SNDRV_FIREWIRE_IOCTL_LOCK:
		वापस hwdep_lock(bebob);
	हाल SNDRV_FIREWIRE_IOCTL_UNLOCK:
		वापस hwdep_unlock(bebob);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक
hwdep_compat_ioctl(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
		   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस hwdep_ioctl(hwdep, file, cmd,
			   (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#अन्यथा
#घोषणा hwdep_compat_ioctl शून्य
#पूर्ण_अगर

पूर्णांक snd_bebob_create_hwdep_device(काष्ठा snd_bebob *bebob)
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

	err = snd_hwdep_new(bebob->card, "BeBoB", 0, &hwdep);
	अगर (err < 0)
		जाओ end;
	म_नकल(hwdep->name, "BeBoB");
	hwdep->अगरace = SNDRV_HWDEP_IFACE_FW_BEBOB;
	hwdep->ops = ops;
	hwdep->निजी_data = bebob;
	hwdep->exclusive = true;
end:
	वापस err;
पूर्ण


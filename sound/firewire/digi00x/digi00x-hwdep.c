<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * digi00x-hwdep.c - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 */

/*
 * This codes give three functionality.
 *
 * 1.get firewire node inक्रमmation
 * 2.get notअगरication about starting/stopping stream
 * 3.lock/unlock stream
 * 4.get asynchronous messaging
 */

#समावेश "digi00x.h"

अटल दीर्घ hwdep_पढ़ो(काष्ठा snd_hwdep *hwdep, अक्षर __user *buf,  दीर्घ count,
		       loff_t *offset)
अणु
	काष्ठा snd_dg00x *dg00x = hwdep->निजी_data;
	DEFINE_WAIT(रुको);
	जोड़ snd_firewire_event event;

	spin_lock_irq(&dg00x->lock);

	जबतक (!dg00x->dev_lock_changed && dg00x->msg == 0) अणु
		prepare_to_रुको(&dg00x->hwdep_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_unlock_irq(&dg00x->lock);
		schedule();
		finish_रुको(&dg00x->hwdep_रुको, &रुको);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		spin_lock_irq(&dg00x->lock);
	पूर्ण

	स_रखो(&event, 0, माप(event));
	अगर (dg00x->dev_lock_changed) अणु
		event.lock_status.type = SNDRV_FIREWIRE_EVENT_LOCK_STATUS;
		event.lock_status.status = (dg00x->dev_lock_count > 0);
		dg00x->dev_lock_changed = false;

		count = min_t(दीर्घ, count, माप(event.lock_status));
	पूर्ण अन्यथा अणु
		event.digi00x_message.type =
					SNDRV_FIREWIRE_EVENT_DIGI00X_MESSAGE;
		event.digi00x_message.message = dg00x->msg;
		dg00x->msg = 0;

		count = min_t(दीर्घ, count, माप(event.digi00x_message));
	पूर्ण

	spin_unlock_irq(&dg00x->lock);

	अगर (copy_to_user(buf, &event, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल __poll_t hwdep_poll(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
			       poll_table *रुको)
अणु
	काष्ठा snd_dg00x *dg00x = hwdep->निजी_data;
	__poll_t events;

	poll_रुको(file, &dg00x->hwdep_रुको, रुको);

	spin_lock_irq(&dg00x->lock);
	अगर (dg00x->dev_lock_changed || dg00x->msg)
		events = EPOLLIN | EPOLLRDNORM;
	अन्यथा
		events = 0;
	spin_unlock_irq(&dg00x->lock);

	वापस events;
पूर्ण

अटल पूर्णांक hwdep_get_info(काष्ठा snd_dg00x *dg00x, व्योम __user *arg)
अणु
	काष्ठा fw_device *dev = fw_parent_device(dg00x->unit);
	काष्ठा snd_firewire_get_info info;

	स_रखो(&info, 0, माप(info));
	info.type = SNDRV_FIREWIRE_TYPE_DIGI00X;
	info.card = dev->card->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_rom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_rom[4]);
	strscpy(info.device_name, dev_name(&dev->device),
		माप(info.device_name));

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_lock(काष्ठा snd_dg00x *dg00x)
अणु
	पूर्णांक err;

	spin_lock_irq(&dg00x->lock);

	अगर (dg00x->dev_lock_count == 0) अणु
		dg00x->dev_lock_count = -1;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBUSY;
	पूर्ण

	spin_unlock_irq(&dg00x->lock);

	वापस err;
पूर्ण

अटल पूर्णांक hwdep_unlock(काष्ठा snd_dg00x *dg00x)
अणु
	पूर्णांक err;

	spin_lock_irq(&dg00x->lock);

	अगर (dg00x->dev_lock_count == -1) अणु
		dg00x->dev_lock_count = 0;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBADFD;
	पूर्ण

	spin_unlock_irq(&dg00x->lock);

	वापस err;
पूर्ण

अटल पूर्णांक hwdep_release(काष्ठा snd_hwdep *hwdep, काष्ठा file *file)
अणु
	काष्ठा snd_dg00x *dg00x = hwdep->निजी_data;

	spin_lock_irq(&dg00x->lock);
	अगर (dg00x->dev_lock_count == -1)
		dg00x->dev_lock_count = 0;
	spin_unlock_irq(&dg00x->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_ioctl(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
	    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_dg00x *dg00x = hwdep->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_FIREWIRE_IOCTL_GET_INFO:
		वापस hwdep_get_info(dg00x, (व्योम __user *)arg);
	हाल SNDRV_FIREWIRE_IOCTL_LOCK:
		वापस hwdep_lock(dg00x);
	हाल SNDRV_FIREWIRE_IOCTL_UNLOCK:
		वापस hwdep_unlock(dg00x);
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

पूर्णांक snd_dg00x_create_hwdep_device(काष्ठा snd_dg00x *dg00x)
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

	err = snd_hwdep_new(dg00x->card, "Digi00x", 0, &hwdep);
	अगर (err < 0)
		वापस err;

	म_नकल(hwdep->name, "Digi00x");
	hwdep->अगरace = SNDRV_HWDEP_IFACE_FW_DIGI00X;
	hwdep->ops = ops;
	hwdep->निजी_data = dg00x;
	hwdep->exclusive = true;

	वापस err;
पूर्ण

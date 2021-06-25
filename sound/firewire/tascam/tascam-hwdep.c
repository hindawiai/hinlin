<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tascam-hwdep.c - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

/*
 * This codes give three functionality.
 *
 * 1.get firewire node inक्रमmation
 * 2.get notअगरication about starting/stopping stream
 * 3.lock/unlock stream
 */

#समावेश "tascam.h"

अटल दीर्घ tscm_hwdep_पढ़ो_locked(काष्ठा snd_tscm *tscm, अक्षर __user *buf,
				   दीर्घ count, loff_t *offset)
	__releases(&tscm->lock)
अणु
	काष्ठा snd_firewire_event_lock_status event = अणु
		.type = SNDRV_FIREWIRE_EVENT_LOCK_STATUS,
	पूर्ण;

	event.status = (tscm->dev_lock_count > 0);
	tscm->dev_lock_changed = false;
	count = min_t(दीर्घ, count, माप(event));

	spin_unlock_irq(&tscm->lock);

	अगर (copy_to_user(buf, &event, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल दीर्घ tscm_hwdep_पढ़ो_queue(काष्ठा snd_tscm *tscm, अक्षर __user *buf,
				  दीर्घ reमुख्यed, loff_t *offset)
	__releases(&tscm->lock)
अणु
	अक्षर __user *pos = buf;
	अचिन्हित पूर्णांक type = SNDRV_FIREWIRE_EVENT_TASCAM_CONTROL;
	काष्ठा snd_firewire_tascam_change *entries = tscm->queue;
	दीर्घ count;

	// At least, one control event can be copied.
	अगर (reमुख्यed < माप(type) + माप(*entries)) अणु
		spin_unlock_irq(&tscm->lock);
		वापस -EINVAL;
	पूर्ण

	// Copy the type field later.
	count = माप(type);
	reमुख्यed -= माप(type);
	pos += माप(type);

	जबतक (true) अणु
		अचिन्हित पूर्णांक head_pos;
		अचिन्हित पूर्णांक tail_pos;
		अचिन्हित पूर्णांक length;

		अगर (tscm->pull_pos == tscm->push_pos)
			अवरोध;
		अन्यथा अगर (tscm->pull_pos < tscm->push_pos)
			tail_pos = tscm->push_pos;
		अन्यथा
			tail_pos = SND_TSCM_QUEUE_COUNT;
		head_pos = tscm->pull_pos;

		length = (tail_pos - head_pos) * माप(*entries);
		अगर (reमुख्यed < length)
			length = roundकरोwn(reमुख्यed, माप(*entries));
		अगर (length == 0)
			अवरोध;

		spin_unlock_irq(&tscm->lock);
		अगर (copy_to_user(pos, &entries[head_pos], length))
			वापस -EFAULT;

		spin_lock_irq(&tscm->lock);

		tscm->pull_pos = tail_pos % SND_TSCM_QUEUE_COUNT;

		count += length;
		reमुख्यed -= length;
		pos += length;
	पूर्ण

	spin_unlock_irq(&tscm->lock);

	अगर (copy_to_user(buf, &type, माप(type)))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल दीर्घ hwdep_पढ़ो(काष्ठा snd_hwdep *hwdep, अक्षर __user *buf, दीर्घ count,
		       loff_t *offset)
अणु
	काष्ठा snd_tscm *tscm = hwdep->निजी_data;
	DEFINE_WAIT(रुको);

	spin_lock_irq(&tscm->lock);

	जबतक (!tscm->dev_lock_changed && tscm->push_pos == tscm->pull_pos) अणु
		prepare_to_रुको(&tscm->hwdep_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_unlock_irq(&tscm->lock);
		schedule();
		finish_रुको(&tscm->hwdep_रुको, &रुको);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		spin_lock_irq(&tscm->lock);
	पूर्ण

	// NOTE: The acquired lock should be released in callee side.
	अगर (tscm->dev_lock_changed) अणु
		count = tscm_hwdep_पढ़ो_locked(tscm, buf, count, offset);
	पूर्ण अन्यथा अगर (tscm->push_pos != tscm->pull_pos) अणु
		count = tscm_hwdep_पढ़ो_queue(tscm, buf, count, offset);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&tscm->lock);
		count = 0;
	पूर्ण

	वापस count;
पूर्ण

अटल __poll_t hwdep_poll(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
			       poll_table *रुको)
अणु
	काष्ठा snd_tscm *tscm = hwdep->निजी_data;
	__poll_t events;

	poll_रुको(file, &tscm->hwdep_रुको, रुको);

	spin_lock_irq(&tscm->lock);
	अगर (tscm->dev_lock_changed || tscm->push_pos != tscm->pull_pos)
		events = EPOLLIN | EPOLLRDNORM;
	अन्यथा
		events = 0;
	spin_unlock_irq(&tscm->lock);

	वापस events;
पूर्ण

अटल पूर्णांक hwdep_get_info(काष्ठा snd_tscm *tscm, व्योम __user *arg)
अणु
	काष्ठा fw_device *dev = fw_parent_device(tscm->unit);
	काष्ठा snd_firewire_get_info info;

	स_रखो(&info, 0, माप(info));
	info.type = SNDRV_FIREWIRE_TYPE_TASCAM;
	info.card = dev->card->index;
	*(__be32 *)&info.guid[0] = cpu_to_be32(dev->config_rom[3]);
	*(__be32 *)&info.guid[4] = cpu_to_be32(dev->config_rom[4]);
	strscpy(info.device_name, dev_name(&dev->device),
		माप(info.device_name));

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_lock(काष्ठा snd_tscm *tscm)
अणु
	पूर्णांक err;

	spin_lock_irq(&tscm->lock);

	अगर (tscm->dev_lock_count == 0) अणु
		tscm->dev_lock_count = -1;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBUSY;
	पूर्ण

	spin_unlock_irq(&tscm->lock);

	वापस err;
पूर्ण

अटल पूर्णांक hwdep_unlock(काष्ठा snd_tscm *tscm)
अणु
	पूर्णांक err;

	spin_lock_irq(&tscm->lock);

	अगर (tscm->dev_lock_count == -1) अणु
		tscm->dev_lock_count = 0;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBADFD;
	पूर्ण

	spin_unlock_irq(&tscm->lock);

	वापस err;
पूर्ण

अटल पूर्णांक tscm_hwdep_state(काष्ठा snd_tscm *tscm, व्योम __user *arg)
अणु
	अगर (copy_to_user(arg, tscm->state, माप(tscm->state)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_release(काष्ठा snd_hwdep *hwdep, काष्ठा file *file)
अणु
	काष्ठा snd_tscm *tscm = hwdep->निजी_data;

	spin_lock_irq(&tscm->lock);
	अगर (tscm->dev_lock_count == -1)
		tscm->dev_lock_count = 0;
	spin_unlock_irq(&tscm->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hwdep_ioctl(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
	    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_tscm *tscm = hwdep->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_FIREWIRE_IOCTL_GET_INFO:
		वापस hwdep_get_info(tscm, (व्योम __user *)arg);
	हाल SNDRV_FIREWIRE_IOCTL_LOCK:
		वापस hwdep_lock(tscm);
	हाल SNDRV_FIREWIRE_IOCTL_UNLOCK:
		वापस hwdep_unlock(tscm);
	हाल SNDRV_FIREWIRE_IOCTL_TASCAM_STATE:
		वापस tscm_hwdep_state(tscm, (व्योम __user *)arg);
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

पूर्णांक snd_tscm_create_hwdep_device(काष्ठा snd_tscm *tscm)
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

	err = snd_hwdep_new(tscm->card, "Tascam", 0, &hwdep);
	अगर (err < 0)
		वापस err;

	म_नकल(hwdep->name, "Tascam");
	hwdep->अगरace = SNDRV_HWDEP_IFACE_FW_TASCAM;
	hwdep->ops = ops;
	hwdep->निजी_data = tscm;
	hwdep->exclusive = true;

	tscm->hwdep = hwdep;

	वापस err;
पूर्ण

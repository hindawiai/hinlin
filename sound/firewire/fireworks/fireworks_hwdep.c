<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fireworks_hwdep.c - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

/*
 * This codes have five functionalities.
 *
 * 1.get inक्रमmation about firewire node
 * 2.get notअगरication about starting/stopping stream
 * 3.lock/unlock streaming
 * 4.transmit command of EFW transaction
 * 5.receive response of EFW transaction
 *
 */

#समावेश "fireworks.h"

अटल दीर्घ
hwdep_पढ़ो_resp_buf(काष्ठा snd_efw *efw, अक्षर __user *buf, दीर्घ reमुख्यed,
		    loff_t *offset)
अणु
	अचिन्हित पूर्णांक length, till_end, type;
	काष्ठा snd_efw_transaction *t;
	u8 *pull_ptr;
	दीर्घ count = 0;

	अगर (reमुख्यed < माप(type) + माप(काष्ठा snd_efw_transaction))
		वापस -ENOSPC;

	/* data type is SNDRV_FIREWIRE_EVENT_EFW_RESPONSE */
	type = SNDRV_FIREWIRE_EVENT_EFW_RESPONSE;
	अगर (copy_to_user(buf, &type, माप(type)))
		वापस -EFAULT;
	reमुख्यed -= माप(type);
	buf += माप(type);

	/* ग_लिखो पूर्णांकo buffer as many responses as possible */
	spin_lock_irq(&efw->lock);

	/*
	 * When another task reaches here during this task's access to user
	 * space, it picks up current position in buffer and can पढ़ो the same
	 * series of responses.
	 */
	pull_ptr = efw->pull_ptr;

	जबतक (efw->push_ptr != pull_ptr) अणु
		t = (काष्ठा snd_efw_transaction *)(pull_ptr);
		length = be32_to_cpu(t->length) * माप(__be32);

		/* confirm enough space क्रम this response */
		अगर (reमुख्यed < length)
			अवरोध;

		/* copy from ring buffer to user buffer */
		जबतक (length > 0) अणु
			till_end = snd_efw_resp_buf_size -
				(अचिन्हित पूर्णांक)(pull_ptr - efw->resp_buf);
			till_end = min_t(अचिन्हित पूर्णांक, length, till_end);

			spin_unlock_irq(&efw->lock);

			अगर (copy_to_user(buf, pull_ptr, till_end))
				वापस -EFAULT;

			spin_lock_irq(&efw->lock);

			pull_ptr += till_end;
			अगर (pull_ptr >= efw->resp_buf + snd_efw_resp_buf_size)
				pull_ptr -= snd_efw_resp_buf_size;

			length -= till_end;
			buf += till_end;
			count += till_end;
			reमुख्यed -= till_end;
		पूर्ण
	पूर्ण

	/*
	 * All of tasks can पढ़ो from the buffer nearly simultaneously, but the
	 * last position क्रम each task is dअगरferent depending on the length of
	 * given buffer. Here, क्रम simplicity, a position of buffer is set by
	 * the latest task. It's better क्रम a listening application to allow one
	 * thपढ़ो to पढ़ो from the buffer. Unless, each task can पढ़ो dअगरferent
	 * sequence of responses depending on variation of buffer length.
	 */
	efw->pull_ptr = pull_ptr;

	spin_unlock_irq(&efw->lock);

	वापस count;
पूर्ण

अटल दीर्घ
hwdep_पढ़ो_locked(काष्ठा snd_efw *efw, अक्षर __user *buf, दीर्घ count,
		  loff_t *offset)
अणु
	जोड़ snd_firewire_event event = अणु
		.lock_status.type = SNDRV_FIREWIRE_EVENT_LOCK_STATUS,
	पूर्ण;

	spin_lock_irq(&efw->lock);

	event.lock_status.status = (efw->dev_lock_count > 0);
	efw->dev_lock_changed = false;

	spin_unlock_irq(&efw->lock);

	count = min_t(दीर्घ, count, माप(event.lock_status));

	अगर (copy_to_user(buf, &event, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल दीर्घ
hwdep_पढ़ो(काष्ठा snd_hwdep *hwdep, अक्षर __user *buf, दीर्घ count,
	   loff_t *offset)
अणु
	काष्ठा snd_efw *efw = hwdep->निजी_data;
	DEFINE_WAIT(रुको);
	bool dev_lock_changed;
	bool queued;

	spin_lock_irq(&efw->lock);

	dev_lock_changed = efw->dev_lock_changed;
	queued = efw->push_ptr != efw->pull_ptr;

	जबतक (!dev_lock_changed && !queued) अणु
		prepare_to_रुको(&efw->hwdep_रुको, &रुको, TASK_INTERRUPTIBLE);
		spin_unlock_irq(&efw->lock);
		schedule();
		finish_रुको(&efw->hwdep_रुको, &रुको);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		spin_lock_irq(&efw->lock);
		dev_lock_changed = efw->dev_lock_changed;
		queued = efw->push_ptr != efw->pull_ptr;
	पूर्ण

	spin_unlock_irq(&efw->lock);

	अगर (dev_lock_changed)
		count = hwdep_पढ़ो_locked(efw, buf, count, offset);
	अन्यथा अगर (queued)
		count = hwdep_पढ़ो_resp_buf(efw, buf, count, offset);

	वापस count;
पूर्ण

अटल दीर्घ
hwdep_ग_लिखो(काष्ठा snd_hwdep *hwdep, स्थिर अक्षर __user *data, दीर्घ count,
	    loff_t *offset)
अणु
	काष्ठा snd_efw *efw = hwdep->निजी_data;
	u32 seqnum;
	u8 *buf;

	अगर (count < माप(काष्ठा snd_efw_transaction) ||
	    SND_EFW_RESPONSE_MAXIMUM_BYTES < count)
		वापस -EINVAL;

	buf = memdup_user(data, count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	/* check seqnum is not क्रम kernel-land */
	seqnum = be32_to_cpu(((काष्ठा snd_efw_transaction *)buf)->seqnum);
	अगर (seqnum > SND_EFW_TRANSACTION_USER_SEQNUM_MAX) अणु
		count = -EINVAL;
		जाओ end;
	पूर्ण

	अगर (snd_efw_transaction_cmd(efw->unit, buf, count) < 0)
		count = -EIO;
end:
	kमुक्त(buf);
	वापस count;
पूर्ण

अटल __poll_t
hwdep_poll(काष्ठा snd_hwdep *hwdep, काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा snd_efw *efw = hwdep->निजी_data;
	__poll_t events;

	poll_रुको(file, &efw->hwdep_रुको, रुको);

	spin_lock_irq(&efw->lock);
	अगर (efw->dev_lock_changed || efw->pull_ptr != efw->push_ptr)
		events = EPOLLIN | EPOLLRDNORM;
	अन्यथा
		events = 0;
	spin_unlock_irq(&efw->lock);

	वापस events | EPOLLOUT;
पूर्ण

अटल पूर्णांक
hwdep_get_info(काष्ठा snd_efw *efw, व्योम __user *arg)
अणु
	काष्ठा fw_device *dev = fw_parent_device(efw->unit);
	काष्ठा snd_firewire_get_info info;

	स_रखो(&info, 0, माप(info));
	info.type = SNDRV_FIREWIRE_TYPE_FIREWORKS;
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
hwdep_lock(काष्ठा snd_efw *efw)
अणु
	पूर्णांक err;

	spin_lock_irq(&efw->lock);

	अगर (efw->dev_lock_count == 0) अणु
		efw->dev_lock_count = -1;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBUSY;
	पूर्ण

	spin_unlock_irq(&efw->lock);

	वापस err;
पूर्ण

अटल पूर्णांक
hwdep_unlock(काष्ठा snd_efw *efw)
अणु
	पूर्णांक err;

	spin_lock_irq(&efw->lock);

	अगर (efw->dev_lock_count == -1) अणु
		efw->dev_lock_count = 0;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBADFD;
	पूर्ण

	spin_unlock_irq(&efw->lock);

	वापस err;
पूर्ण

अटल पूर्णांक
hwdep_release(काष्ठा snd_hwdep *hwdep, काष्ठा file *file)
अणु
	काष्ठा snd_efw *efw = hwdep->निजी_data;

	spin_lock_irq(&efw->lock);
	अगर (efw->dev_lock_count == -1)
		efw->dev_lock_count = 0;
	spin_unlock_irq(&efw->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
hwdep_ioctl(काष्ठा snd_hwdep *hwdep, काष्ठा file *file,
	    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_efw *efw = hwdep->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_FIREWIRE_IOCTL_GET_INFO:
		वापस hwdep_get_info(efw, (व्योम __user *)arg);
	हाल SNDRV_FIREWIRE_IOCTL_LOCK:
		वापस hwdep_lock(efw);
	हाल SNDRV_FIREWIRE_IOCTL_UNLOCK:
		वापस hwdep_unlock(efw);
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

पूर्णांक snd_efw_create_hwdep_device(काष्ठा snd_efw *efw)
अणु
	अटल स्थिर काष्ठा snd_hwdep_ops ops = अणु
		.पढ़ो		= hwdep_पढ़ो,
		.ग_लिखो		= hwdep_ग_लिखो,
		.release	= hwdep_release,
		.poll		= hwdep_poll,
		.ioctl		= hwdep_ioctl,
		.ioctl_compat	= hwdep_compat_ioctl,
	पूर्ण;
	काष्ठा snd_hwdep *hwdep;
	पूर्णांक err;

	err = snd_hwdep_new(efw->card, "Fireworks", 0, &hwdep);
	अगर (err < 0)
		जाओ end;
	म_नकल(hwdep->name, "Fireworks");
	hwdep->अगरace = SNDRV_HWDEP_IFACE_FW_FIREWORKS;
	hwdep->ops = ops;
	hwdep->निजी_data = efw;
	hwdep->exclusive = true;
end:
	वापस err;
पूर्ण


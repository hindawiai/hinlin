<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Timers असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <sound/core.h>
#समावेश <sound/समयr.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#समावेश <sound/minors.h>
#समावेश <sound/initval.h>
#समावेश <linux/kmod.h>

/* पूर्णांकernal flags */
#घोषणा SNDRV_TIMER_IFLG_PAUSED		0x00010000
#घोषणा SNDRV_TIMER_IFLG_DEAD		0x00020000

#अगर IS_ENABLED(CONFIG_SND_HRTIMER)
#घोषणा DEFAULT_TIMER_LIMIT 4
#अन्यथा
#घोषणा DEFAULT_TIMER_LIMIT 1
#पूर्ण_अगर

अटल पूर्णांक समयr_limit = DEFAULT_TIMER_LIMIT;
अटल पूर्णांक समयr_tstamp_monotonic = 1;
MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>, Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("ALSA timer interface");
MODULE_LICENSE("GPL");
module_param(समयr_limit, पूर्णांक, 0444);
MODULE_PARM_DESC(समयr_limit, "Maximum global timers in system.");
module_param(समयr_tstamp_monotonic, पूर्णांक, 0444);
MODULE_PARM_DESC(समयr_tstamp_monotonic, "Use posix monotonic clock source for timestamps (default).");

MODULE_ALIAS_CHARDEV(CONFIG_SND_MAJOR, SNDRV_MINOR_TIMER);
MODULE_ALIAS("devname:snd/timer");

क्रमागत समयr_tपढ़ो_क्रमmat अणु
	TREAD_FORMAT_NONE = 0,
	TREAD_FORMAT_TIME64,
	TREAD_FORMAT_TIME32,
पूर्ण;

काष्ठा snd_समयr_tपढ़ो32 अणु
	पूर्णांक event;
	s32 tstamp_sec;
	s32 tstamp_nsec;
	अचिन्हित पूर्णांक val;
पूर्ण;

काष्ठा snd_समयr_tपढ़ो64 अणु
	पूर्णांक event;
	u8 pad1[4];
	s64 tstamp_sec;
	s64 tstamp_nsec;
	अचिन्हित पूर्णांक val;
	u8 pad2[4];
पूर्ण;

काष्ठा snd_समयr_user अणु
	काष्ठा snd_समयr_instance *समयri;
	पूर्णांक tपढ़ो;		/* enhanced पढ़ो with बारtamps and events */
	अचिन्हित दीर्घ ticks;
	अचिन्हित दीर्घ overrun;
	पूर्णांक qhead;
	पूर्णांक qtail;
	पूर्णांक qused;
	पूर्णांक queue_size;
	bool disconnected;
	काष्ठा snd_समयr_पढ़ो *queue;
	काष्ठा snd_समयr_tपढ़ो64 *tqueue;
	spinlock_t qlock;
	अचिन्हित दीर्घ last_resolution;
	अचिन्हित पूर्णांक filter;
	काष्ठा बारpec64 tstamp;		/* trigger tstamp */
	रुको_queue_head_t qchange_sleep;
	काष्ठा fasync_काष्ठा *fasync;
	काष्ठा mutex ioctl_lock;
पूर्ण;

काष्ठा snd_समयr_status32 अणु
	s32 tstamp_sec;			/* Timestamp - last update */
	s32 tstamp_nsec;
	अचिन्हित पूर्णांक resolution;	/* current period resolution in ns */
	अचिन्हित पूर्णांक lost;		/* counter of master tick lost */
	अचिन्हित पूर्णांक overrun;		/* count of पढ़ो queue overruns */
	अचिन्हित पूर्णांक queue;		/* used queue size */
	अचिन्हित अक्षर reserved[64];	/* reserved */
पूर्ण;

#घोषणा SNDRV_TIMER_IOCTL_STATUS32	_IOR('T', 0x14, काष्ठा snd_समयr_status32)

काष्ठा snd_समयr_status64 अणु
	s64 tstamp_sec;			/* Timestamp - last update */
	s64 tstamp_nsec;
	अचिन्हित पूर्णांक resolution;	/* current period resolution in ns */
	अचिन्हित पूर्णांक lost;		/* counter of master tick lost */
	अचिन्हित पूर्णांक overrun;		/* count of पढ़ो queue overruns */
	अचिन्हित पूर्णांक queue;		/* used queue size */
	अचिन्हित अक्षर reserved[64];	/* reserved */
पूर्ण;

#घोषणा SNDRV_TIMER_IOCTL_STATUS64	_IOR('T', 0x14, काष्ठा snd_समयr_status64)

/* list of समयrs */
अटल LIST_HEAD(snd_समयr_list);

/* list of slave instances */
अटल LIST_HEAD(snd_समयr_slave_list);

/* lock क्रम slave active lists */
अटल DEFINE_SPINLOCK(slave_active_lock);

#घोषणा MAX_SLAVE_INSTANCES	1000
अटल पूर्णांक num_slaves;

अटल DEFINE_MUTEX(रेजिस्टर_mutex);

अटल पूर्णांक snd_समयr_मुक्त(काष्ठा snd_समयr *समयr);
अटल पूर्णांक snd_समयr_dev_मुक्त(काष्ठा snd_device *device);
अटल पूर्णांक snd_समयr_dev_रेजिस्टर(काष्ठा snd_device *device);
अटल पूर्णांक snd_समयr_dev_disconnect(काष्ठा snd_device *device);

अटल व्योम snd_समयr_reschedule(काष्ठा snd_समयr * समयr, अचिन्हित दीर्घ ticks_left);

/*
 * create a समयr instance with the given owner string.
 */
काष्ठा snd_समयr_instance *snd_समयr_instance_new(स्थिर अक्षर *owner)
अणु
	काष्ठा snd_समयr_instance *समयri;

	समयri = kzalloc(माप(*समयri), GFP_KERNEL);
	अगर (समयri == शून्य)
		वापस शून्य;
	समयri->owner = kstrdup(owner, GFP_KERNEL);
	अगर (! समयri->owner) अणु
		kमुक्त(समयri);
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&समयri->खोलो_list);
	INIT_LIST_HEAD(&समयri->active_list);
	INIT_LIST_HEAD(&समयri->ack_list);
	INIT_LIST_HEAD(&समयri->slave_list_head);
	INIT_LIST_HEAD(&समयri->slave_active_head);

	वापस समयri;
पूर्ण
EXPORT_SYMBOL(snd_समयr_instance_new);

व्योम snd_समयr_instance_मुक्त(काष्ठा snd_समयr_instance *समयri)
अणु
	अगर (समयri) अणु
		अगर (समयri->निजी_मुक्त)
			समयri->निजी_मुक्त(समयri);
		kमुक्त(समयri->owner);
		kमुक्त(समयri);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_समयr_instance_मुक्त);

/*
 * find a समयr instance from the given समयr id
 */
अटल काष्ठा snd_समयr *snd_समयr_find(काष्ठा snd_समयr_id *tid)
अणु
	काष्ठा snd_समयr *समयr;

	list_क्रम_each_entry(समयr, &snd_समयr_list, device_list) अणु
		अगर (समयr->पंचांगr_class != tid->dev_class)
			जारी;
		अगर ((समयr->पंचांगr_class == SNDRV_TIMER_CLASS_CARD ||
		     समयr->पंचांगr_class == SNDRV_TIMER_CLASS_PCM) &&
		    (समयr->card == शून्य ||
		     समयr->card->number != tid->card))
			जारी;
		अगर (समयr->पंचांगr_device != tid->device)
			जारी;
		अगर (समयr->पंचांगr_subdevice != tid->subdevice)
			जारी;
		वापस समयr;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_MODULES

अटल व्योम snd_समयr_request(काष्ठा snd_समयr_id *tid)
अणु
	चयन (tid->dev_class) अणु
	हाल SNDRV_TIMER_CLASS_GLOBAL:
		अगर (tid->device < समयr_limit)
			request_module("snd-timer-%i", tid->device);
		अवरोध;
	हाल SNDRV_TIMER_CLASS_CARD:
	हाल SNDRV_TIMER_CLASS_PCM:
		अगर (tid->card < snd_ecards_limit)
			request_module("snd-card-%i", tid->card);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#पूर्ण_अगर

/* move the slave अगर it beदीर्घs to the master; वापस 1 अगर match */
अटल पूर्णांक check_matching_master_slave(काष्ठा snd_समयr_instance *master,
				       काष्ठा snd_समयr_instance *slave)
अणु
	अगर (slave->slave_class != master->slave_class ||
	    slave->slave_id != master->slave_id)
		वापस 0;
	अगर (master->समयr->num_instances >= master->समयr->max_instances)
		वापस -EBUSY;
	list_move_tail(&slave->खोलो_list, &master->slave_list_head);
	master->समयr->num_instances++;
	spin_lock_irq(&slave_active_lock);
	spin_lock(&master->समयr->lock);
	slave->master = master;
	slave->समयr = master->समयr;
	अगर (slave->flags & SNDRV_TIMER_IFLG_RUNNING)
		list_add_tail(&slave->active_list, &master->slave_active_head);
	spin_unlock(&master->समयr->lock);
	spin_unlock_irq(&slave_active_lock);
	वापस 1;
पूर्ण

/*
 * look क्रम a master instance matching with the slave id of the given slave.
 * when found, relink the खोलो_link of the slave.
 *
 * call this with रेजिस्टर_mutex करोwn.
 */
अटल पूर्णांक snd_समयr_check_slave(काष्ठा snd_समयr_instance *slave)
अणु
	काष्ठा snd_समयr *समयr;
	काष्ठा snd_समयr_instance *master;
	पूर्णांक err = 0;

	/* FIXME: it's really dumb to look up all entries.. */
	list_क्रम_each_entry(समयr, &snd_समयr_list, device_list) अणु
		list_क्रम_each_entry(master, &समयr->खोलो_list_head, खोलो_list) अणु
			err = check_matching_master_slave(master, slave);
			अगर (err != 0) /* match found or error */
				जाओ out;
		पूर्ण
	पूर्ण
 out:
	वापस err < 0 ? err : 0;
पूर्ण

/*
 * look क्रम slave instances matching with the slave id of the given master.
 * when found, relink the खोलो_link of slaves.
 *
 * call this with रेजिस्टर_mutex करोwn.
 */
अटल पूर्णांक snd_समयr_check_master(काष्ठा snd_समयr_instance *master)
अणु
	काष्ठा snd_समयr_instance *slave, *पंचांगp;
	पूर्णांक err = 0;

	/* check all pending slaves */
	list_क्रम_each_entry_safe(slave, पंचांगp, &snd_समयr_slave_list, खोलो_list) अणु
		err = check_matching_master_slave(master, slave);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err < 0 ? err : 0;
पूर्ण

अटल व्योम snd_समयr_बंद_locked(काष्ठा snd_समयr_instance *समयri,
				   काष्ठा device **card_devp_to_put);

/*
 * खोलो a समयr instance
 * when खोलोing a master, the slave id must be here given.
 */
पूर्णांक snd_समयr_खोलो(काष्ठा snd_समयr_instance *समयri,
		   काष्ठा snd_समयr_id *tid,
		   अचिन्हित पूर्णांक slave_id)
अणु
	काष्ठा snd_समयr *समयr;
	काष्ठा device *card_dev_to_put = शून्य;
	पूर्णांक err;

	mutex_lock(&रेजिस्टर_mutex);
	अगर (tid->dev_class == SNDRV_TIMER_CLASS_SLAVE) अणु
		/* खोलो a slave instance */
		अगर (tid->dev_sclass <= SNDRV_TIMER_SCLASS_NONE ||
		    tid->dev_sclass > SNDRV_TIMER_SCLASS_OSS_SEQUENCER) अणु
			pr_debug("ALSA: timer: invalid slave class %i\n",
				 tid->dev_sclass);
			err = -EINVAL;
			जाओ unlock;
		पूर्ण
		अगर (num_slaves >= MAX_SLAVE_INSTANCES) अणु
			err = -EBUSY;
			जाओ unlock;
		पूर्ण
		समयri->slave_class = tid->dev_sclass;
		समयri->slave_id = tid->device;
		समयri->flags |= SNDRV_TIMER_IFLG_SLAVE;
		list_add_tail(&समयri->खोलो_list, &snd_समयr_slave_list);
		num_slaves++;
		err = snd_समयr_check_slave(समयri);
		जाओ list_added;
	पूर्ण

	/* खोलो a master instance */
	समयr = snd_समयr_find(tid);
#अगर_घोषित CONFIG_MODULES
	अगर (!समयr) अणु
		mutex_unlock(&रेजिस्टर_mutex);
		snd_समयr_request(tid);
		mutex_lock(&रेजिस्टर_mutex);
		समयr = snd_समयr_find(tid);
	पूर्ण
#पूर्ण_अगर
	अगर (!समयr) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण
	अगर (!list_empty(&समयr->खोलो_list_head)) अणु
		काष्ठा snd_समयr_instance *t =
			list_entry(समयr->खोलो_list_head.next,
				    काष्ठा snd_समयr_instance, खोलो_list);
		अगर (t->flags & SNDRV_TIMER_IFLG_EXCLUSIVE) अणु
			err = -EBUSY;
			जाओ unlock;
		पूर्ण
	पूर्ण
	अगर (समयr->num_instances >= समयr->max_instances) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण
	अगर (!try_module_get(समयr->module)) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण
	/* take a card refcount क्रम safe disconnection */
	अगर (समयr->card) अणु
		get_device(&समयr->card->card_dev);
		card_dev_to_put = &समयr->card->card_dev;
	पूर्ण

	अगर (list_empty(&समयr->खोलो_list_head) && समयr->hw.खोलो) अणु
		err = समयr->hw.खोलो(समयr);
		अगर (err) अणु
			module_put(समयr->module);
			जाओ unlock;
		पूर्ण
	पूर्ण

	समयri->समयr = समयr;
	समयri->slave_class = tid->dev_sclass;
	समयri->slave_id = slave_id;

	list_add_tail(&समयri->खोलो_list, &समयr->खोलो_list_head);
	समयr->num_instances++;
	err = snd_समयr_check_master(समयri);
list_added:
	अगर (err < 0)
		snd_समयr_बंद_locked(समयri, &card_dev_to_put);

 unlock:
	mutex_unlock(&रेजिस्टर_mutex);
	/* put_device() is called after unlock क्रम aव्योमing deadlock */
	अगर (err < 0 && card_dev_to_put)
		put_device(card_dev_to_put);
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_समयr_खोलो);

/*
 * बंद a समयr instance
 * call this with रेजिस्टर_mutex करोwn.
 */
अटल व्योम snd_समयr_बंद_locked(काष्ठा snd_समयr_instance *समयri,
				   काष्ठा device **card_devp_to_put)
अणु
	काष्ठा snd_समयr *समयr = समयri->समयr;
	काष्ठा snd_समयr_instance *slave, *पंचांगp;

	अगर (समयr) अणु
		spin_lock_irq(&समयr->lock);
		समयri->flags |= SNDRV_TIMER_IFLG_DEAD;
		spin_unlock_irq(&समयr->lock);
	पूर्ण

	अगर (!list_empty(&समयri->खोलो_list)) अणु
		list_del_init(&समयri->खोलो_list);
		अगर (समयri->flags & SNDRV_TIMER_IFLG_SLAVE)
			num_slaves--;
	पूर्ण

	/* क्रमce to stop the समयr */
	snd_समयr_stop(समयri);

	अगर (समयr) अणु
		समयr->num_instances--;
		/* रुको, until the active callback is finished */
		spin_lock_irq(&समयr->lock);
		जबतक (समयri->flags & SNDRV_TIMER_IFLG_CALLBACK) अणु
			spin_unlock_irq(&समयr->lock);
			udelay(10);
			spin_lock_irq(&समयr->lock);
		पूर्ण
		spin_unlock_irq(&समयr->lock);

		/* हटाओ slave links */
		spin_lock_irq(&slave_active_lock);
		spin_lock(&समयr->lock);
		समयri->समयr = शून्य;
		list_क्रम_each_entry_safe(slave, पंचांगp, &समयri->slave_list_head,
					 खोलो_list) अणु
			list_move_tail(&slave->खोलो_list, &snd_समयr_slave_list);
			समयr->num_instances--;
			slave->master = शून्य;
			slave->समयr = शून्य;
			list_del_init(&slave->ack_list);
			list_del_init(&slave->active_list);
		पूर्ण
		spin_unlock(&समयr->lock);
		spin_unlock_irq(&slave_active_lock);

		/* slave करोesn't need to release समयr resources below */
		अगर (समयri->flags & SNDRV_TIMER_IFLG_SLAVE)
			समयr = शून्य;
	पूर्ण

	अगर (समयr) अणु
		अगर (list_empty(&समयr->खोलो_list_head) && समयr->hw.बंद)
			समयr->hw.बंद(समयr);
		/* release a card refcount क्रम safe disconnection */
		अगर (समयr->card)
			*card_devp_to_put = &समयr->card->card_dev;
		module_put(समयr->module);
	पूर्ण
पूर्ण

/*
 * बंद a समयr instance
 */
व्योम snd_समयr_बंद(काष्ठा snd_समयr_instance *समयri)
अणु
	काष्ठा device *card_dev_to_put = शून्य;

	अगर (snd_BUG_ON(!समयri))
		वापस;

	mutex_lock(&रेजिस्टर_mutex);
	snd_समयr_बंद_locked(समयri, &card_dev_to_put);
	mutex_unlock(&रेजिस्टर_mutex);
	/* put_device() is called after unlock क्रम aव्योमing deadlock */
	अगर (card_dev_to_put)
		put_device(card_dev_to_put);
पूर्ण
EXPORT_SYMBOL(snd_समयr_बंद);

अटल अचिन्हित दीर्घ snd_समयr_hw_resolution(काष्ठा snd_समयr *समयr)
अणु
	अगर (समयr->hw.c_resolution)
		वापस समयr->hw.c_resolution(समयr);
	अन्यथा
		वापस समयr->hw.resolution;
पूर्ण

अचिन्हित दीर्घ snd_समयr_resolution(काष्ठा snd_समयr_instance *समयri)
अणु
	काष्ठा snd_समयr * समयr;
	अचिन्हित दीर्घ ret = 0;
	अचिन्हित दीर्घ flags;

	अगर (समयri == शून्य)
		वापस 0;
	समयr = समयri->समयr;
	अगर (समयr) अणु
		spin_lock_irqsave(&समयr->lock, flags);
		ret = snd_समयr_hw_resolution(समयr);
		spin_unlock_irqrestore(&समयr->lock, flags);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(snd_समयr_resolution);

अटल व्योम snd_समयr_notअगरy1(काष्ठा snd_समयr_instance *ti, पूर्णांक event)
अणु
	काष्ठा snd_समयr *समयr = ti->समयr;
	अचिन्हित दीर्घ resolution = 0;
	काष्ठा snd_समयr_instance *ts;
	काष्ठा बारpec64 tstamp;

	अगर (समयr_tstamp_monotonic)
		kसमय_get_ts64(&tstamp);
	अन्यथा
		kसमय_get_real_ts64(&tstamp);
	अगर (snd_BUG_ON(event < SNDRV_TIMER_EVENT_START ||
		       event > SNDRV_TIMER_EVENT_PAUSE))
		वापस;
	अगर (समयr &&
	    (event == SNDRV_TIMER_EVENT_START ||
	     event == SNDRV_TIMER_EVENT_CONTINUE))
		resolution = snd_समयr_hw_resolution(समयr);
	अगर (ti->ccallback)
		ti->ccallback(ti, event, &tstamp, resolution);
	अगर (ti->flags & SNDRV_TIMER_IFLG_SLAVE)
		वापस;
	अगर (समयr == शून्य)
		वापस;
	अगर (समयr->hw.flags & SNDRV_TIMER_HW_SLAVE)
		वापस;
	event += 10; /* convert to SNDRV_TIMER_EVENT_MXXX */
	list_क्रम_each_entry(ts, &ti->slave_active_head, active_list)
		अगर (ts->ccallback)
			ts->ccallback(ts, event, &tstamp, resolution);
पूर्ण

/* start/जारी a master समयr */
अटल पूर्णांक snd_समयr_start1(काष्ठा snd_समयr_instance *समयri,
			    bool start, अचिन्हित दीर्घ ticks)
अणु
	काष्ठा snd_समयr *समयr;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	समयr = समयri->समयr;
	अगर (!समयr)
		वापस -EINVAL;

	spin_lock_irqsave(&समयr->lock, flags);
	अगर (समयri->flags & SNDRV_TIMER_IFLG_DEAD) अणु
		result = -EINVAL;
		जाओ unlock;
	पूर्ण
	अगर (समयr->card && समयr->card->shutकरोwn) अणु
		result = -ENODEV;
		जाओ unlock;
	पूर्ण
	अगर (समयri->flags & (SNDRV_TIMER_IFLG_RUNNING |
			     SNDRV_TIMER_IFLG_START)) अणु
		result = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर (start)
		समयri->ticks = समयri->cticks = ticks;
	अन्यथा अगर (!समयri->cticks)
		समयri->cticks = 1;
	समयri->pticks = 0;

	list_move_tail(&समयri->active_list, &समयr->active_list_head);
	अगर (समयr->running) अणु
		अगर (समयr->hw.flags & SNDRV_TIMER_HW_SLAVE)
			जाओ __start_now;
		समयr->flags |= SNDRV_TIMER_FLG_RESCHED;
		समयri->flags |= SNDRV_TIMER_IFLG_START;
		result = 1; /* delayed start */
	पूर्ण अन्यथा अणु
		अगर (start)
			समयr->sticks = ticks;
		समयr->hw.start(समयr);
	      __start_now:
		समयr->running++;
		समयri->flags |= SNDRV_TIMER_IFLG_RUNNING;
		result = 0;
	पूर्ण
	snd_समयr_notअगरy1(समयri, start ? SNDRV_TIMER_EVENT_START :
			  SNDRV_TIMER_EVENT_CONTINUE);
 unlock:
	spin_unlock_irqrestore(&समयr->lock, flags);
	वापस result;
पूर्ण

/* start/जारी a slave समयr */
अटल पूर्णांक snd_समयr_start_slave(काष्ठा snd_समयr_instance *समयri,
				 bool start)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&slave_active_lock, flags);
	अगर (समयri->flags & SNDRV_TIMER_IFLG_DEAD) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण
	अगर (समयri->flags & SNDRV_TIMER_IFLG_RUNNING) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण
	समयri->flags |= SNDRV_TIMER_IFLG_RUNNING;
	अगर (समयri->master && समयri->समयr) अणु
		spin_lock(&समयri->समयr->lock);
		list_add_tail(&समयri->active_list,
			      &समयri->master->slave_active_head);
		snd_समयr_notअगरy1(समयri, start ? SNDRV_TIMER_EVENT_START :
				  SNDRV_TIMER_EVENT_CONTINUE);
		spin_unlock(&समयri->समयr->lock);
	पूर्ण
	err = 1; /* delayed start */
 unlock:
	spin_unlock_irqrestore(&slave_active_lock, flags);
	वापस err;
पूर्ण

/* stop/छोड़ो a master समयr */
अटल पूर्णांक snd_समयr_stop1(काष्ठा snd_समयr_instance *समयri, bool stop)
अणु
	काष्ठा snd_समयr *समयr;
	पूर्णांक result = 0;
	अचिन्हित दीर्घ flags;

	समयr = समयri->समयr;
	अगर (!समयr)
		वापस -EINVAL;
	spin_lock_irqsave(&समयr->lock, flags);
	अगर (!(समयri->flags & (SNDRV_TIMER_IFLG_RUNNING |
			       SNDRV_TIMER_IFLG_START))) अणु
		result = -EBUSY;
		जाओ unlock;
	पूर्ण
	list_del_init(&समयri->ack_list);
	list_del_init(&समयri->active_list);
	अगर (समयr->card && समयr->card->shutकरोwn)
		जाओ unlock;
	अगर (stop) अणु
		समयri->cticks = समयri->ticks;
		समयri->pticks = 0;
	पूर्ण
	अगर ((समयri->flags & SNDRV_TIMER_IFLG_RUNNING) &&
	    !(--समयr->running)) अणु
		समयr->hw.stop(समयr);
		अगर (समयr->flags & SNDRV_TIMER_FLG_RESCHED) अणु
			समयr->flags &= ~SNDRV_TIMER_FLG_RESCHED;
			snd_समयr_reschedule(समयr, 0);
			अगर (समयr->flags & SNDRV_TIMER_FLG_CHANGE) अणु
				समयr->flags &= ~SNDRV_TIMER_FLG_CHANGE;
				समयr->hw.start(समयr);
			पूर्ण
		पूर्ण
	पूर्ण
	समयri->flags &= ~(SNDRV_TIMER_IFLG_RUNNING | SNDRV_TIMER_IFLG_START);
	अगर (stop)
		समयri->flags &= ~SNDRV_TIMER_IFLG_PAUSED;
	अन्यथा
		समयri->flags |= SNDRV_TIMER_IFLG_PAUSED;
	snd_समयr_notअगरy1(समयri, stop ? SNDRV_TIMER_EVENT_STOP :
			  SNDRV_TIMER_EVENT_PAUSE);
 unlock:
	spin_unlock_irqrestore(&समयr->lock, flags);
	वापस result;
पूर्ण

/* stop/छोड़ो a slave समयr */
अटल पूर्णांक snd_समयr_stop_slave(काष्ठा snd_समयr_instance *समयri, bool stop)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&slave_active_lock, flags);
	अगर (!(समयri->flags & SNDRV_TIMER_IFLG_RUNNING)) अणु
		spin_unlock_irqrestore(&slave_active_lock, flags);
		वापस -EBUSY;
	पूर्ण
	समयri->flags &= ~SNDRV_TIMER_IFLG_RUNNING;
	अगर (समयri->समयr) अणु
		spin_lock(&समयri->समयr->lock);
		list_del_init(&समयri->ack_list);
		list_del_init(&समयri->active_list);
		snd_समयr_notअगरy1(समयri, stop ? SNDRV_TIMER_EVENT_STOP :
				  SNDRV_TIMER_EVENT_PAUSE);
		spin_unlock(&समयri->समयr->lock);
	पूर्ण
	spin_unlock_irqrestore(&slave_active_lock, flags);
	वापस 0;
पूर्ण

/*
 *  start the समयr instance
 */
पूर्णांक snd_समयr_start(काष्ठा snd_समयr_instance *समयri, अचिन्हित पूर्णांक ticks)
अणु
	अगर (समयri == शून्य || ticks < 1)
		वापस -EINVAL;
	अगर (समयri->flags & SNDRV_TIMER_IFLG_SLAVE)
		वापस snd_समयr_start_slave(समयri, true);
	अन्यथा
		वापस snd_समयr_start1(समयri, true, ticks);
पूर्ण
EXPORT_SYMBOL(snd_समयr_start);

/*
 * stop the समयr instance.
 *
 * करो not call this from the समयr callback!
 */
पूर्णांक snd_समयr_stop(काष्ठा snd_समयr_instance *समयri)
अणु
	अगर (समयri->flags & SNDRV_TIMER_IFLG_SLAVE)
		वापस snd_समयr_stop_slave(समयri, true);
	अन्यथा
		वापस snd_समयr_stop1(समयri, true);
पूर्ण
EXPORT_SYMBOL(snd_समयr_stop);

/*
 * start again..  the tick is kept.
 */
पूर्णांक snd_समयr_जारी(काष्ठा snd_समयr_instance *समयri)
अणु
	/* समयr can जारी only after छोड़ो */
	अगर (!(समयri->flags & SNDRV_TIMER_IFLG_PAUSED))
		वापस -EINVAL;

	अगर (समयri->flags & SNDRV_TIMER_IFLG_SLAVE)
		वापस snd_समयr_start_slave(समयri, false);
	अन्यथा
		वापस snd_समयr_start1(समयri, false, 0);
पूर्ण
EXPORT_SYMBOL(snd_समयr_जारी);

/*
 * छोड़ो.. remember the ticks left
 */
पूर्णांक snd_समयr_छोड़ो(काष्ठा snd_समयr_instance * समयri)
अणु
	अगर (समयri->flags & SNDRV_TIMER_IFLG_SLAVE)
		वापस snd_समयr_stop_slave(समयri, false);
	अन्यथा
		वापस snd_समयr_stop1(समयri, false);
पूर्ण
EXPORT_SYMBOL(snd_समयr_छोड़ो);

/*
 * reschedule the समयr
 *
 * start pending instances and check the scheduling ticks.
 * when the scheduling ticks is changed set CHANGE flag to reprogram the समयr.
 */
अटल व्योम snd_समयr_reschedule(काष्ठा snd_समयr * समयr, अचिन्हित दीर्घ ticks_left)
अणु
	काष्ठा snd_समयr_instance *ti;
	अचिन्हित दीर्घ ticks = ~0UL;

	list_क्रम_each_entry(ti, &समयr->active_list_head, active_list) अणु
		अगर (ti->flags & SNDRV_TIMER_IFLG_START) अणु
			ti->flags &= ~SNDRV_TIMER_IFLG_START;
			ti->flags |= SNDRV_TIMER_IFLG_RUNNING;
			समयr->running++;
		पूर्ण
		अगर (ti->flags & SNDRV_TIMER_IFLG_RUNNING) अणु
			अगर (ticks > ti->cticks)
				ticks = ti->cticks;
		पूर्ण
	पूर्ण
	अगर (ticks == ~0UL) अणु
		समयr->flags &= ~SNDRV_TIMER_FLG_RESCHED;
		वापस;
	पूर्ण
	अगर (ticks > समयr->hw.ticks)
		ticks = समयr->hw.ticks;
	अगर (ticks_left != ticks)
		समयr->flags |= SNDRV_TIMER_FLG_CHANGE;
	समयr->sticks = ticks;
पूर्ण

/* call callbacks in समयr ack list */
अटल व्योम snd_समयr_process_callbacks(काष्ठा snd_समयr *समयr,
					काष्ठा list_head *head)
अणु
	काष्ठा snd_समयr_instance *ti;
	अचिन्हित दीर्घ resolution, ticks;

	जबतक (!list_empty(head)) अणु
		ti = list_first_entry(head, काष्ठा snd_समयr_instance,
				      ack_list);

		/* हटाओ from ack_list and make empty */
		list_del_init(&ti->ack_list);

		अगर (!(ti->flags & SNDRV_TIMER_IFLG_DEAD)) अणु
			ticks = ti->pticks;
			ti->pticks = 0;
			resolution = ti->resolution;
			ti->flags |= SNDRV_TIMER_IFLG_CALLBACK;
			spin_unlock(&समयr->lock);
			अगर (ti->callback)
				ti->callback(ti, resolution, ticks);
			spin_lock(&समयr->lock);
			ti->flags &= ~SNDRV_TIMER_IFLG_CALLBACK;
		पूर्ण
	पूर्ण
पूर्ण

/* clear pending instances from ack list */
अटल व्योम snd_समयr_clear_callbacks(काष्ठा snd_समयr *समयr,
				      काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&समयr->lock, flags);
	जबतक (!list_empty(head))
		list_del_init(head->next);
	spin_unlock_irqrestore(&समयr->lock, flags);
पूर्ण

/*
 * समयr work
 *
 */
अटल व्योम snd_समयr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_समयr *समयr = container_of(work, काष्ठा snd_समयr, task_work);
	अचिन्हित दीर्घ flags;

	अगर (समयr->card && समयr->card->shutकरोwn) अणु
		snd_समयr_clear_callbacks(समयr, &समयr->sack_list_head);
		वापस;
	पूर्ण

	spin_lock_irqsave(&समयr->lock, flags);
	snd_समयr_process_callbacks(समयr, &समयr->sack_list_head);
	spin_unlock_irqrestore(&समयr->lock, flags);
पूर्ण

/*
 * समयr पूर्णांकerrupt
 *
 * ticks_left is usually equal to समयr->sticks.
 *
 */
व्योम snd_समयr_पूर्णांकerrupt(काष्ठा snd_समयr * समयr, अचिन्हित दीर्घ ticks_left)
अणु
	काष्ठा snd_समयr_instance *ti, *ts, *पंचांगp;
	अचिन्हित दीर्घ resolution;
	काष्ठा list_head *ack_list_head;
	अचिन्हित दीर्घ flags;
	bool use_work = false;

	अगर (समयr == शून्य)
		वापस;

	अगर (समयr->card && समयr->card->shutकरोwn) अणु
		snd_समयr_clear_callbacks(समयr, &समयr->ack_list_head);
		वापस;
	पूर्ण

	spin_lock_irqsave(&समयr->lock, flags);

	/* remember the current resolution */
	resolution = snd_समयr_hw_resolution(समयr);

	/* loop क्रम all active instances
	 * Here we cannot use list_क्रम_each_entry because the active_list of a
	 * processed instance is relinked to करोne_list_head beक्रमe the callback
	 * is called.
	 */
	list_क्रम_each_entry_safe(ti, पंचांगp, &समयr->active_list_head,
				 active_list) अणु
		अगर (ti->flags & SNDRV_TIMER_IFLG_DEAD)
			जारी;
		अगर (!(ti->flags & SNDRV_TIMER_IFLG_RUNNING))
			जारी;
		ti->pticks += ticks_left;
		ti->resolution = resolution;
		अगर (ti->cticks < ticks_left)
			ti->cticks = 0;
		अन्यथा
			ti->cticks -= ticks_left;
		अगर (ti->cticks) /* not expired */
			जारी;
		अगर (ti->flags & SNDRV_TIMER_IFLG_AUTO) अणु
			ti->cticks = ti->ticks;
		पूर्ण अन्यथा अणु
			ti->flags &= ~SNDRV_TIMER_IFLG_RUNNING;
			--समयr->running;
			list_del_init(&ti->active_list);
		पूर्ण
		अगर ((समयr->hw.flags & SNDRV_TIMER_HW_WORK) ||
		    (ti->flags & SNDRV_TIMER_IFLG_FAST))
			ack_list_head = &समयr->ack_list_head;
		अन्यथा
			ack_list_head = &समयr->sack_list_head;
		अगर (list_empty(&ti->ack_list))
			list_add_tail(&ti->ack_list, ack_list_head);
		list_क्रम_each_entry(ts, &ti->slave_active_head, active_list) अणु
			ts->pticks = ti->pticks;
			ts->resolution = resolution;
			अगर (list_empty(&ts->ack_list))
				list_add_tail(&ts->ack_list, ack_list_head);
		पूर्ण
	पूर्ण
	अगर (समयr->flags & SNDRV_TIMER_FLG_RESCHED)
		snd_समयr_reschedule(समयr, समयr->sticks);
	अगर (समयr->running) अणु
		अगर (समयr->hw.flags & SNDRV_TIMER_HW_STOP) अणु
			समयr->hw.stop(समयr);
			समयr->flags |= SNDRV_TIMER_FLG_CHANGE;
		पूर्ण
		अगर (!(समयr->hw.flags & SNDRV_TIMER_HW_AUTO) ||
		    (समयr->flags & SNDRV_TIMER_FLG_CHANGE)) अणु
			/* restart समयr */
			समयr->flags &= ~SNDRV_TIMER_FLG_CHANGE;
			समयr->hw.start(समयr);
		पूर्ण
	पूर्ण अन्यथा अणु
		समयr->hw.stop(समयr);
	पूर्ण

	/* now process all fast callbacks */
	snd_समयr_process_callbacks(समयr, &समयr->ack_list_head);

	/* करो we have any slow callbacks? */
	use_work = !list_empty(&समयr->sack_list_head);
	spin_unlock_irqrestore(&समयr->lock, flags);

	अगर (use_work)
		queue_work(प्रणाली_highpri_wq, &समयr->task_work);
पूर्ण
EXPORT_SYMBOL(snd_समयr_पूर्णांकerrupt);

/*

 */

पूर्णांक snd_समयr_new(काष्ठा snd_card *card, अक्षर *id, काष्ठा snd_समयr_id *tid,
		  काष्ठा snd_समयr **rसमयr)
अणु
	काष्ठा snd_समयr *समयr;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_समयr_dev_मुक्त,
		.dev_रेजिस्टर = snd_समयr_dev_रेजिस्टर,
		.dev_disconnect = snd_समयr_dev_disconnect,
	पूर्ण;

	अगर (snd_BUG_ON(!tid))
		वापस -EINVAL;
	अगर (tid->dev_class == SNDRV_TIMER_CLASS_CARD ||
	    tid->dev_class == SNDRV_TIMER_CLASS_PCM) अणु
		अगर (WARN_ON(!card))
			वापस -EINVAL;
	पूर्ण
	अगर (rसमयr)
		*rसमयr = शून्य;
	समयr = kzalloc(माप(*समयr), GFP_KERNEL);
	अगर (!समयr)
		वापस -ENOMEM;
	समयr->पंचांगr_class = tid->dev_class;
	समयr->card = card;
	समयr->पंचांगr_device = tid->device;
	समयr->पंचांगr_subdevice = tid->subdevice;
	अगर (id)
		strscpy(समयr->id, id, माप(समयr->id));
	समयr->sticks = 1;
	INIT_LIST_HEAD(&समयr->device_list);
	INIT_LIST_HEAD(&समयr->खोलो_list_head);
	INIT_LIST_HEAD(&समयr->active_list_head);
	INIT_LIST_HEAD(&समयr->ack_list_head);
	INIT_LIST_HEAD(&समयr->sack_list_head);
	spin_lock_init(&समयr->lock);
	INIT_WORK(&समयr->task_work, snd_समयr_work);
	समयr->max_instances = 1000; /* शेष limit per समयr */
	अगर (card != शून्य) अणु
		समयr->module = card->module;
		err = snd_device_new(card, SNDRV_DEV_TIMER, समयr, &ops);
		अगर (err < 0) अणु
			snd_समयr_मुक्त(समयr);
			वापस err;
		पूर्ण
	पूर्ण
	अगर (rसमयr)
		*rसमयr = समयr;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_समयr_new);

अटल पूर्णांक snd_समयr_मुक्त(काष्ठा snd_समयr *समयr)
अणु
	अगर (!समयr)
		वापस 0;

	mutex_lock(&रेजिस्टर_mutex);
	अगर (! list_empty(&समयr->खोलो_list_head)) अणु
		काष्ठा list_head *p, *n;
		काष्ठा snd_समयr_instance *ti;
		pr_warn("ALSA: timer %p is busy?\n", समयr);
		list_क्रम_each_safe(p, n, &समयr->खोलो_list_head) अणु
			list_del_init(p);
			ti = list_entry(p, काष्ठा snd_समयr_instance, खोलो_list);
			ti->समयr = शून्य;
		पूर्ण
	पूर्ण
	list_del(&समयr->device_list);
	mutex_unlock(&रेजिस्टर_mutex);

	अगर (समयr->निजी_मुक्त)
		समयr->निजी_मुक्त(समयr);
	kमुक्त(समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_समयr *समयr = device->device_data;
	वापस snd_समयr_मुक्त(समयr);
पूर्ण

अटल पूर्णांक snd_समयr_dev_रेजिस्टर(काष्ठा snd_device *dev)
अणु
	काष्ठा snd_समयr *समयr = dev->device_data;
	काष्ठा snd_समयr *समयr1;

	अगर (snd_BUG_ON(!समयr || !समयr->hw.start || !समयr->hw.stop))
		वापस -ENXIO;
	अगर (!(समयr->hw.flags & SNDRV_TIMER_HW_SLAVE) &&
	    !समयr->hw.resolution && समयr->hw.c_resolution == शून्य)
	    	वापस -EINVAL;

	mutex_lock(&रेजिस्टर_mutex);
	list_क्रम_each_entry(समयr1, &snd_समयr_list, device_list) अणु
		अगर (समयr1->पंचांगr_class > समयr->पंचांगr_class)
			अवरोध;
		अगर (समयr1->पंचांगr_class < समयr->पंचांगr_class)
			जारी;
		अगर (समयr1->card && समयr->card) अणु
			अगर (समयr1->card->number > समयr->card->number)
				अवरोध;
			अगर (समयr1->card->number < समयr->card->number)
				जारी;
		पूर्ण
		अगर (समयr1->पंचांगr_device > समयr->पंचांगr_device)
			अवरोध;
		अगर (समयr1->पंचांगr_device < समयr->पंचांगr_device)
			जारी;
		अगर (समयr1->पंचांगr_subdevice > समयr->पंचांगr_subdevice)
			अवरोध;
		अगर (समयr1->पंचांगr_subdevice < समयr->पंचांगr_subdevice)
			जारी;
		/* conflicts.. */
		mutex_unlock(&रेजिस्टर_mutex);
		वापस -EBUSY;
	पूर्ण
	list_add_tail(&समयr->device_list, &समयr1->device_list);
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा snd_समयr *समयr = device->device_data;
	काष्ठा snd_समयr_instance *ti;

	mutex_lock(&रेजिस्टर_mutex);
	list_del_init(&समयr->device_list);
	/* wake up pending sleepers */
	list_क्रम_each_entry(ti, &समयr->खोलो_list_head, खोलो_list) अणु
		अगर (ti->disconnect)
			ti->disconnect(ti);
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण

व्योम snd_समयr_notअगरy(काष्ठा snd_समयr *समयr, पूर्णांक event, काष्ठा बारpec64 *tstamp)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ resolution = 0;
	काष्ठा snd_समयr_instance *ti, *ts;

	अगर (समयr->card && समयr->card->shutकरोwn)
		वापस;
	अगर (! (समयr->hw.flags & SNDRV_TIMER_HW_SLAVE))
		वापस;
	अगर (snd_BUG_ON(event < SNDRV_TIMER_EVENT_MSTART ||
		       event > SNDRV_TIMER_EVENT_MRESUME))
		वापस;
	spin_lock_irqsave(&समयr->lock, flags);
	अगर (event == SNDRV_TIMER_EVENT_MSTART ||
	    event == SNDRV_TIMER_EVENT_MCONTINUE ||
	    event == SNDRV_TIMER_EVENT_MRESUME)
		resolution = snd_समयr_hw_resolution(समयr);
	list_क्रम_each_entry(ti, &समयr->active_list_head, active_list) अणु
		अगर (ti->ccallback)
			ti->ccallback(ti, event, tstamp, resolution);
		list_क्रम_each_entry(ts, &ti->slave_active_head, active_list)
			अगर (ts->ccallback)
				ts->ccallback(ts, event, tstamp, resolution);
	पूर्ण
	spin_unlock_irqrestore(&समयr->lock, flags);
पूर्ण
EXPORT_SYMBOL(snd_समयr_notअगरy);

/*
 * exported functions क्रम global समयrs
 */
पूर्णांक snd_समयr_global_new(अक्षर *id, पूर्णांक device, काष्ठा snd_समयr **rसमयr)
अणु
	काष्ठा snd_समयr_id tid;

	tid.dev_class = SNDRV_TIMER_CLASS_GLOBAL;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = -1;
	tid.device = device;
	tid.subdevice = 0;
	वापस snd_समयr_new(शून्य, id, &tid, rसमयr);
पूर्ण
EXPORT_SYMBOL(snd_समयr_global_new);

पूर्णांक snd_समयr_global_मुक्त(काष्ठा snd_समयr *समयr)
अणु
	वापस snd_समयr_मुक्त(समयr);
पूर्ण
EXPORT_SYMBOL(snd_समयr_global_मुक्त);

पूर्णांक snd_समयr_global_रेजिस्टर(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_device dev;

	स_रखो(&dev, 0, माप(dev));
	dev.device_data = समयr;
	वापस snd_समयr_dev_रेजिस्टर(&dev);
पूर्ण
EXPORT_SYMBOL(snd_समयr_global_रेजिस्टर);

/*
 *  System समयr
 */

काष्ठा snd_समयr_प्रणाली_निजी अणु
	काष्ठा समयr_list tlist;
	काष्ठा snd_समयr *snd_समयr;
	अचिन्हित दीर्घ last_expires;
	अचिन्हित दीर्घ last_jअगरfies;
	अचिन्हित दीर्घ correction;
पूर्ण;

अटल व्योम snd_समयr_s_function(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_समयr_प्रणाली_निजी *priv = from_समयr(priv, t,
								tlist);
	काष्ठा snd_समयr *समयr = priv->snd_समयr;
	अचिन्हित दीर्घ jअगरf = jअगरfies;
	अगर (समय_after(jअगरf, priv->last_expires))
		priv->correction += (दीर्घ)jअगरf - (दीर्घ)priv->last_expires;
	snd_समयr_पूर्णांकerrupt(समयr, (दीर्घ)jअगरf - (दीर्घ)priv->last_jअगरfies);
पूर्ण

अटल पूर्णांक snd_समयr_s_start(काष्ठा snd_समयr * समयr)
अणु
	काष्ठा snd_समयr_प्रणाली_निजी *priv;
	अचिन्हित दीर्घ njअगरf;

	priv = (काष्ठा snd_समयr_प्रणाली_निजी *) समयr->निजी_data;
	njअगरf = (priv->last_jअगरfies = jअगरfies);
	अगर (priv->correction > समयr->sticks - 1) अणु
		priv->correction -= समयr->sticks - 1;
		njअगरf++;
	पूर्ण अन्यथा अणु
		njअगरf += समयr->sticks - priv->correction;
		priv->correction = 0;
	पूर्ण
	priv->last_expires = njअगरf;
	mod_समयr(&priv->tlist, njअगरf);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_s_stop(काष्ठा snd_समयr * समयr)
अणु
	काष्ठा snd_समयr_प्रणाली_निजी *priv;
	अचिन्हित दीर्घ jअगरf;

	priv = (काष्ठा snd_समयr_प्रणाली_निजी *) समयr->निजी_data;
	del_समयr(&priv->tlist);
	jअगरf = jअगरfies;
	अगर (समय_beक्रमe(jअगरf, priv->last_expires))
		समयr->sticks = priv->last_expires - jअगरf;
	अन्यथा
		समयr->sticks = 1;
	priv->correction = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_s_बंद(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_समयr_प्रणाली_निजी *priv;

	priv = (काष्ठा snd_समयr_प्रणाली_निजी *)समयr->निजी_data;
	del_समयr_sync(&priv->tlist);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_समयr_hardware snd_समयr_प्रणाली =
अणु
	.flags =	SNDRV_TIMER_HW_FIRST | SNDRV_TIMER_HW_WORK,
	.resolution =	1000000000L / HZ,
	.ticks =	10000000L,
	.बंद =	snd_समयr_s_बंद,
	.start =	snd_समयr_s_start,
	.stop =		snd_समयr_s_stop
पूर्ण;

अटल व्योम snd_समयr_मुक्त_प्रणाली(काष्ठा snd_समयr *समयr)
अणु
	kमुक्त(समयr->निजी_data);
पूर्ण

अटल पूर्णांक snd_समयr_रेजिस्टर_प्रणाली(व्योम)
अणु
	काष्ठा snd_समयr *समयr;
	काष्ठा snd_समयr_प्रणाली_निजी *priv;
	पूर्णांक err;

	err = snd_समयr_global_new("system", SNDRV_TIMER_GLOBAL_SYSTEM, &समयr);
	अगर (err < 0)
		वापस err;
	म_नकल(समयr->name, "system timer");
	समयr->hw = snd_समयr_प्रणाली;
	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य) अणु
		snd_समयr_मुक्त(समयr);
		वापस -ENOMEM;
	पूर्ण
	priv->snd_समयr = समयr;
	समयr_setup(&priv->tlist, snd_समयr_s_function, 0);
	समयr->निजी_data = priv;
	समयr->निजी_मुक्त = snd_समयr_मुक्त_प्रणाली;
	वापस snd_समयr_global_रेजिस्टर(समयr);
पूर्ण

#अगर_घोषित CONFIG_SND_PROC_FS
/*
 *  Info पूर्णांकerface
 */

अटल व्योम snd_समयr_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_समयr *समयr;
	काष्ठा snd_समयr_instance *ti;

	mutex_lock(&रेजिस्टर_mutex);
	list_क्रम_each_entry(समयr, &snd_समयr_list, device_list) अणु
		अगर (समयr->card && समयr->card->shutकरोwn)
			जारी;
		चयन (समयr->पंचांगr_class) अणु
		हाल SNDRV_TIMER_CLASS_GLOBAL:
			snd_iम_लिखो(buffer, "G%i: ", समयr->पंचांगr_device);
			अवरोध;
		हाल SNDRV_TIMER_CLASS_CARD:
			snd_iम_लिखो(buffer, "C%i-%i: ",
				    समयr->card->number, समयr->पंचांगr_device);
			अवरोध;
		हाल SNDRV_TIMER_CLASS_PCM:
			snd_iम_लिखो(buffer, "P%i-%i-%i: ", समयr->card->number,
				    समयr->पंचांगr_device, समयr->पंचांगr_subdevice);
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "?%i-%i-%i-%i: ", समयr->पंचांगr_class,
				    समयr->card ? समयr->card->number : -1,
				    समयr->पंचांगr_device, समयr->पंचांगr_subdevice);
		पूर्ण
		snd_iम_लिखो(buffer, "%s :", समयr->name);
		अगर (समयr->hw.resolution)
			snd_iम_लिखो(buffer, " %lu.%03luus (%lu ticks)",
				    समयr->hw.resolution / 1000,
				    समयr->hw.resolution % 1000,
				    समयr->hw.ticks);
		अगर (समयr->hw.flags & SNDRV_TIMER_HW_SLAVE)
			snd_iम_लिखो(buffer, " SLAVE");
		snd_iम_लिखो(buffer, "\n");
		list_क्रम_each_entry(ti, &समयr->खोलो_list_head, खोलो_list)
			snd_iम_लिखो(buffer, "  Client %s : %s\n",
				    ti->owner ? ti->owner : "unknown",
				    (ti->flags & (SNDRV_TIMER_IFLG_START |
						  SNDRV_TIMER_IFLG_RUNNING))
				    ? "running" : "stopped");
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
पूर्ण

अटल काष्ठा snd_info_entry *snd_समयr_proc_entry;

अटल व्योम __init snd_समयr_proc_init(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(THIS_MODULE, "timers", शून्य);
	अगर (entry != शून्य) अणु
		entry->c.text.पढ़ो = snd_समयr_proc_पढ़ो;
		अगर (snd_info_रेजिस्टर(entry) < 0) अणु
			snd_info_मुक्त_entry(entry);
			entry = शून्य;
		पूर्ण
	पूर्ण
	snd_समयr_proc_entry = entry;
पूर्ण

अटल व्योम __निकास snd_समयr_proc_करोne(व्योम)
अणु
	snd_info_मुक्त_entry(snd_समयr_proc_entry);
पूर्ण
#अन्यथा /* !CONFIG_SND_PROC_FS */
#घोषणा snd_समयr_proc_init()
#घोषणा snd_समयr_proc_करोne()
#पूर्ण_अगर

/*
 *  USER SPACE पूर्णांकerface
 */

अटल व्योम snd_समयr_user_पूर्णांकerrupt(काष्ठा snd_समयr_instance *समयri,
				     अचिन्हित दीर्घ resolution,
				     अचिन्हित दीर्घ ticks)
अणु
	काष्ठा snd_समयr_user *tu = समयri->callback_data;
	काष्ठा snd_समयr_पढ़ो *r;
	पूर्णांक prev;

	spin_lock(&tu->qlock);
	अगर (tu->qused > 0) अणु
		prev = tu->qtail == 0 ? tu->queue_size - 1 : tu->qtail - 1;
		r = &tu->queue[prev];
		अगर (r->resolution == resolution) अणु
			r->ticks += ticks;
			जाओ __wake;
		पूर्ण
	पूर्ण
	अगर (tu->qused >= tu->queue_size) अणु
		tu->overrun++;
	पूर्ण अन्यथा अणु
		r = &tu->queue[tu->qtail++];
		tu->qtail %= tu->queue_size;
		r->resolution = resolution;
		r->ticks = ticks;
		tu->qused++;
	पूर्ण
      __wake:
	spin_unlock(&tu->qlock);
	समाप्त_fasync(&tu->fasync, SIGIO, POLL_IN);
	wake_up(&tu->qchange_sleep);
पूर्ण

अटल व्योम snd_समयr_user_append_to_tqueue(काष्ठा snd_समयr_user *tu,
					    काष्ठा snd_समयr_tपढ़ो64 *tपढ़ो)
अणु
	अगर (tu->qused >= tu->queue_size) अणु
		tu->overrun++;
	पूर्ण अन्यथा अणु
		स_नकल(&tu->tqueue[tu->qtail++], tपढ़ो, माप(*tपढ़ो));
		tu->qtail %= tu->queue_size;
		tu->qused++;
	पूर्ण
पूर्ण

अटल व्योम snd_समयr_user_ccallback(काष्ठा snd_समयr_instance *समयri,
				     पूर्णांक event,
				     काष्ठा बारpec64 *tstamp,
				     अचिन्हित दीर्घ resolution)
अणु
	काष्ठा snd_समयr_user *tu = समयri->callback_data;
	काष्ठा snd_समयr_tपढ़ो64 r1;
	अचिन्हित दीर्घ flags;

	अगर (event >= SNDRV_TIMER_EVENT_START &&
	    event <= SNDRV_TIMER_EVENT_PAUSE)
		tu->tstamp = *tstamp;
	अगर ((tu->filter & (1 << event)) == 0 || !tu->tपढ़ो)
		वापस;
	स_रखो(&r1, 0, माप(r1));
	r1.event = event;
	r1.tstamp_sec = tstamp->tv_sec;
	r1.tstamp_nsec = tstamp->tv_nsec;
	r1.val = resolution;
	spin_lock_irqsave(&tu->qlock, flags);
	snd_समयr_user_append_to_tqueue(tu, &r1);
	spin_unlock_irqrestore(&tu->qlock, flags);
	समाप्त_fasync(&tu->fasync, SIGIO, POLL_IN);
	wake_up(&tu->qchange_sleep);
पूर्ण

अटल व्योम snd_समयr_user_disconnect(काष्ठा snd_समयr_instance *समयri)
अणु
	काष्ठा snd_समयr_user *tu = समयri->callback_data;

	tu->disconnected = true;
	wake_up(&tu->qchange_sleep);
पूर्ण

अटल व्योम snd_समयr_user_tपूर्णांकerrupt(काष्ठा snd_समयr_instance *समयri,
				      अचिन्हित दीर्घ resolution,
				      अचिन्हित दीर्घ ticks)
अणु
	काष्ठा snd_समयr_user *tu = समयri->callback_data;
	काष्ठा snd_समयr_tपढ़ो64 *r, r1;
	काष्ठा बारpec64 tstamp;
	पूर्णांक prev, append = 0;

	स_रखो(&r1, 0, माप(r1));
	स_रखो(&tstamp, 0, माप(tstamp));
	spin_lock(&tu->qlock);
	अगर ((tu->filter & ((1 << SNDRV_TIMER_EVENT_RESOLUTION) |
			   (1 << SNDRV_TIMER_EVENT_TICK))) == 0) अणु
		spin_unlock(&tu->qlock);
		वापस;
	पूर्ण
	अगर (tu->last_resolution != resolution || ticks > 0) अणु
		अगर (समयr_tstamp_monotonic)
			kसमय_get_ts64(&tstamp);
		अन्यथा
			kसमय_get_real_ts64(&tstamp);
	पूर्ण
	अगर ((tu->filter & (1 << SNDRV_TIMER_EVENT_RESOLUTION)) &&
	    tu->last_resolution != resolution) अणु
		r1.event = SNDRV_TIMER_EVENT_RESOLUTION;
		r1.tstamp_sec = tstamp.tv_sec;
		r1.tstamp_nsec = tstamp.tv_nsec;
		r1.val = resolution;
		snd_समयr_user_append_to_tqueue(tu, &r1);
		tu->last_resolution = resolution;
		append++;
	पूर्ण
	अगर ((tu->filter & (1 << SNDRV_TIMER_EVENT_TICK)) == 0)
		जाओ __wake;
	अगर (ticks == 0)
		जाओ __wake;
	अगर (tu->qused > 0) अणु
		prev = tu->qtail == 0 ? tu->queue_size - 1 : tu->qtail - 1;
		r = &tu->tqueue[prev];
		अगर (r->event == SNDRV_TIMER_EVENT_TICK) अणु
			r->tstamp_sec = tstamp.tv_sec;
			r->tstamp_nsec = tstamp.tv_nsec;
			r->val += ticks;
			append++;
			जाओ __wake;
		पूर्ण
	पूर्ण
	r1.event = SNDRV_TIMER_EVENT_TICK;
	r1.tstamp_sec = tstamp.tv_sec;
	r1.tstamp_nsec = tstamp.tv_nsec;
	r1.val = ticks;
	snd_समयr_user_append_to_tqueue(tu, &r1);
	append++;
      __wake:
	spin_unlock(&tu->qlock);
	अगर (append == 0)
		वापस;
	समाप्त_fasync(&tu->fasync, SIGIO, POLL_IN);
	wake_up(&tu->qchange_sleep);
पूर्ण

अटल पूर्णांक पुनः_स्मृति_user_queue(काष्ठा snd_समयr_user *tu, पूर्णांक size)
अणु
	काष्ठा snd_समयr_पढ़ो *queue = शून्य;
	काष्ठा snd_समयr_tपढ़ो64 *tqueue = शून्य;

	अगर (tu->tपढ़ो) अणु
		tqueue = kसुस्मृति(size, माप(*tqueue), GFP_KERNEL);
		अगर (!tqueue)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		queue = kसुस्मृति(size, माप(*queue), GFP_KERNEL);
		अगर (!queue)
			वापस -ENOMEM;
	पूर्ण

	spin_lock_irq(&tu->qlock);
	kमुक्त(tu->queue);
	kमुक्त(tu->tqueue);
	tu->queue_size = size;
	tu->queue = queue;
	tu->tqueue = tqueue;
	tu->qhead = tu->qtail = tu->qused = 0;
	spin_unlock_irq(&tu->qlock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_समयr_user *tu;
	पूर्णांक err;

	err = stream_खोलो(inode, file);
	अगर (err < 0)
		वापस err;

	tu = kzalloc(माप(*tu), GFP_KERNEL);
	अगर (tu == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&tu->qlock);
	init_रुकोqueue_head(&tu->qchange_sleep);
	mutex_init(&tu->ioctl_lock);
	tu->ticks = 1;
	अगर (पुनः_स्मृति_user_queue(tu, 128) < 0) अणु
		kमुक्त(tu);
		वापस -ENOMEM;
	पूर्ण
	file->निजी_data = tu;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_समयr_user *tu;

	अगर (file->निजी_data) अणु
		tu = file->निजी_data;
		file->निजी_data = शून्य;
		mutex_lock(&tu->ioctl_lock);
		अगर (tu->समयri) अणु
			snd_समयr_बंद(tu->समयri);
			snd_समयr_instance_मुक्त(tu->समयri);
		पूर्ण
		mutex_unlock(&tu->ioctl_lock);
		kमुक्त(tu->queue);
		kमुक्त(tu->tqueue);
		kमुक्त(tu);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_समयr_user_zero_id(काष्ठा snd_समयr_id *id)
अणु
	id->dev_class = SNDRV_TIMER_CLASS_NONE;
	id->dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	id->card = -1;
	id->device = -1;
	id->subdevice = -1;
पूर्ण

अटल व्योम snd_समयr_user_copy_id(काष्ठा snd_समयr_id *id, काष्ठा snd_समयr *समयr)
अणु
	id->dev_class = समयr->पंचांगr_class;
	id->dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	id->card = समयr->card ? समयr->card->number : -1;
	id->device = समयr->पंचांगr_device;
	id->subdevice = समयr->पंचांगr_subdevice;
पूर्ण

अटल पूर्णांक snd_समयr_user_next_device(काष्ठा snd_समयr_id __user *_tid)
अणु
	काष्ठा snd_समयr_id id;
	काष्ठा snd_समयr *समयr;
	काष्ठा list_head *p;

	अगर (copy_from_user(&id, _tid, माप(id)))
		वापस -EFAULT;
	mutex_lock(&रेजिस्टर_mutex);
	अगर (id.dev_class < 0) अणु		/* first item */
		अगर (list_empty(&snd_समयr_list))
			snd_समयr_user_zero_id(&id);
		अन्यथा अणु
			समयr = list_entry(snd_समयr_list.next,
					   काष्ठा snd_समयr, device_list);
			snd_समयr_user_copy_id(&id, समयr);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (id.dev_class) अणु
		हाल SNDRV_TIMER_CLASS_GLOBAL:
			id.device = id.device < 0 ? 0 : id.device + 1;
			list_क्रम_each(p, &snd_समयr_list) अणु
				समयr = list_entry(p, काष्ठा snd_समयr, device_list);
				अगर (समयr->पंचांगr_class > SNDRV_TIMER_CLASS_GLOBAL) अणु
					snd_समयr_user_copy_id(&id, समयr);
					अवरोध;
				पूर्ण
				अगर (समयr->पंचांगr_device >= id.device) अणु
					snd_समयr_user_copy_id(&id, समयr);
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (p == &snd_समयr_list)
				snd_समयr_user_zero_id(&id);
			अवरोध;
		हाल SNDRV_TIMER_CLASS_CARD:
		हाल SNDRV_TIMER_CLASS_PCM:
			अगर (id.card < 0) अणु
				id.card = 0;
			पूर्ण अन्यथा अणु
				अगर (id.device < 0) अणु
					id.device = 0;
				पूर्ण अन्यथा अणु
					अगर (id.subdevice < 0)
						id.subdevice = 0;
					अन्यथा अगर (id.subdevice < पूर्णांक_उच्च)
						id.subdevice++;
				पूर्ण
			पूर्ण
			list_क्रम_each(p, &snd_समयr_list) अणु
				समयr = list_entry(p, काष्ठा snd_समयr, device_list);
				अगर (समयr->पंचांगr_class > id.dev_class) अणु
					snd_समयr_user_copy_id(&id, समयr);
					अवरोध;
				पूर्ण
				अगर (समयr->पंचांगr_class < id.dev_class)
					जारी;
				अगर (समयr->card->number > id.card) अणु
					snd_समयr_user_copy_id(&id, समयr);
					अवरोध;
				पूर्ण
				अगर (समयr->card->number < id.card)
					जारी;
				अगर (समयr->पंचांगr_device > id.device) अणु
					snd_समयr_user_copy_id(&id, समयr);
					अवरोध;
				पूर्ण
				अगर (समयr->पंचांगr_device < id.device)
					जारी;
				अगर (समयr->पंचांगr_subdevice > id.subdevice) अणु
					snd_समयr_user_copy_id(&id, समयr);
					अवरोध;
				पूर्ण
				अगर (समयr->पंचांगr_subdevice < id.subdevice)
					जारी;
				snd_समयr_user_copy_id(&id, समयr);
				अवरोध;
			पूर्ण
			अगर (p == &snd_समयr_list)
				snd_समयr_user_zero_id(&id);
			अवरोध;
		शेष:
			snd_समयr_user_zero_id(&id);
		पूर्ण
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
	अगर (copy_to_user(_tid, &id, माप(*_tid)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_ginfo(काष्ठा file *file,
				काष्ठा snd_समयr_ginfo __user *_ginfo)
अणु
	काष्ठा snd_समयr_ginfo *ginfo;
	काष्ठा snd_समयr_id tid;
	काष्ठा snd_समयr *t;
	काष्ठा list_head *p;
	पूर्णांक err = 0;

	ginfo = memdup_user(_ginfo, माप(*ginfo));
	अगर (IS_ERR(ginfo))
		वापस PTR_ERR(ginfo);

	tid = ginfo->tid;
	स_रखो(ginfo, 0, माप(*ginfo));
	ginfo->tid = tid;
	mutex_lock(&रेजिस्टर_mutex);
	t = snd_समयr_find(&tid);
	अगर (t != शून्य) अणु
		ginfo->card = t->card ? t->card->number : -1;
		अगर (t->hw.flags & SNDRV_TIMER_HW_SLAVE)
			ginfo->flags |= SNDRV_TIMER_FLG_SLAVE;
		strscpy(ginfo->id, t->id, माप(ginfo->id));
		strscpy(ginfo->name, t->name, माप(ginfo->name));
		ginfo->resolution = t->hw.resolution;
		अगर (t->hw.resolution_min > 0) अणु
			ginfo->resolution_min = t->hw.resolution_min;
			ginfo->resolution_max = t->hw.resolution_max;
		पूर्ण
		list_क्रम_each(p, &t->खोलो_list_head) अणु
			ginfo->clients++;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -ENODEV;
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
	अगर (err >= 0 && copy_to_user(_ginfo, ginfo, माप(*ginfo)))
		err = -EFAULT;
	kमुक्त(ginfo);
	वापस err;
पूर्ण

अटल पूर्णांक समयr_set_gparams(काष्ठा snd_समयr_gparams *gparams)
अणु
	काष्ठा snd_समयr *t;
	पूर्णांक err;

	mutex_lock(&रेजिस्टर_mutex);
	t = snd_समयr_find(&gparams->tid);
	अगर (!t) अणु
		err = -ENODEV;
		जाओ _error;
	पूर्ण
	अगर (!list_empty(&t->खोलो_list_head)) अणु
		err = -EBUSY;
		जाओ _error;
	पूर्ण
	अगर (!t->hw.set_period) अणु
		err = -ENOSYS;
		जाओ _error;
	पूर्ण
	err = t->hw.set_period(t, gparams->period_num, gparams->period_den);
_error:
	mutex_unlock(&रेजिस्टर_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक snd_समयr_user_gparams(काष्ठा file *file,
				  काष्ठा snd_समयr_gparams __user *_gparams)
अणु
	काष्ठा snd_समयr_gparams gparams;

	अगर (copy_from_user(&gparams, _gparams, माप(gparams)))
		वापस -EFAULT;
	वापस समयr_set_gparams(&gparams);
पूर्ण

अटल पूर्णांक snd_समयr_user_gstatus(काष्ठा file *file,
				  काष्ठा snd_समयr_gstatus __user *_gstatus)
अणु
	काष्ठा snd_समयr_gstatus gstatus;
	काष्ठा snd_समयr_id tid;
	काष्ठा snd_समयr *t;
	पूर्णांक err = 0;

	अगर (copy_from_user(&gstatus, _gstatus, माप(gstatus)))
		वापस -EFAULT;
	tid = gstatus.tid;
	स_रखो(&gstatus, 0, माप(gstatus));
	gstatus.tid = tid;
	mutex_lock(&रेजिस्टर_mutex);
	t = snd_समयr_find(&tid);
	अगर (t != शून्य) अणु
		spin_lock_irq(&t->lock);
		gstatus.resolution = snd_समयr_hw_resolution(t);
		अगर (t->hw.precise_resolution) अणु
			t->hw.precise_resolution(t, &gstatus.resolution_num,
						 &gstatus.resolution_den);
		पूर्ण अन्यथा अणु
			gstatus.resolution_num = gstatus.resolution;
			gstatus.resolution_den = 1000000000uL;
		पूर्ण
		spin_unlock_irq(&t->lock);
	पूर्ण अन्यथा अणु
		err = -ENODEV;
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
	अगर (err >= 0 && copy_to_user(_gstatus, &gstatus, माप(gstatus)))
		err = -EFAULT;
	वापस err;
पूर्ण

अटल पूर्णांक snd_समयr_user_tselect(काष्ठा file *file,
				  काष्ठा snd_समयr_select __user *_tselect)
अणु
	काष्ठा snd_समयr_user *tu;
	काष्ठा snd_समयr_select tselect;
	अक्षर str[32];
	पूर्णांक err = 0;

	tu = file->निजी_data;
	अगर (tu->समयri) अणु
		snd_समयr_बंद(tu->समयri);
		snd_समयr_instance_मुक्त(tu->समयri);
		tu->समयri = शून्य;
	पूर्ण
	अगर (copy_from_user(&tselect, _tselect, माप(tselect))) अणु
		err = -EFAULT;
		जाओ __err;
	पूर्ण
	प्र_लिखो(str, "application %i", current->pid);
	अगर (tselect.id.dev_class != SNDRV_TIMER_CLASS_SLAVE)
		tselect.id.dev_sclass = SNDRV_TIMER_SCLASS_APPLICATION;
	tu->समयri = snd_समयr_instance_new(str);
	अगर (!tu->समयri) अणु
		err = -ENOMEM;
		जाओ __err;
	पूर्ण

	tu->समयri->flags |= SNDRV_TIMER_IFLG_FAST;
	tu->समयri->callback = tu->tपढ़ो
			? snd_समयr_user_tपूर्णांकerrupt : snd_समयr_user_पूर्णांकerrupt;
	tu->समयri->ccallback = snd_समयr_user_ccallback;
	tu->समयri->callback_data = (व्योम *)tu;
	tu->समयri->disconnect = snd_समयr_user_disconnect;

	err = snd_समयr_खोलो(tu->समयri, &tselect.id, current->pid);
	अगर (err < 0) अणु
		snd_समयr_instance_मुक्त(tu->समयri);
		tu->समयri = शून्य;
	पूर्ण

      __err:
	वापस err;
पूर्ण

अटल पूर्णांक snd_समयr_user_info(काष्ठा file *file,
			       काष्ठा snd_समयr_info __user *_info)
अणु
	काष्ठा snd_समयr_user *tu;
	काष्ठा snd_समयr_info *info;
	काष्ठा snd_समयr *t;
	पूर्णांक err = 0;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	t = tu->समयri->समयr;
	अगर (!t)
		वापस -EBADFD;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (! info)
		वापस -ENOMEM;
	info->card = t->card ? t->card->number : -1;
	अगर (t->hw.flags & SNDRV_TIMER_HW_SLAVE)
		info->flags |= SNDRV_TIMER_FLG_SLAVE;
	strscpy(info->id, t->id, माप(info->id));
	strscpy(info->name, t->name, माप(info->name));
	info->resolution = t->hw.resolution;
	अगर (copy_to_user(_info, info, माप(*_info)))
		err = -EFAULT;
	kमुक्त(info);
	वापस err;
पूर्ण

अटल पूर्णांक snd_समयr_user_params(काष्ठा file *file,
				 काष्ठा snd_समयr_params __user *_params)
अणु
	काष्ठा snd_समयr_user *tu;
	काष्ठा snd_समयr_params params;
	काष्ठा snd_समयr *t;
	पूर्णांक err;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	t = tu->समयri->समयr;
	अगर (!t)
		वापस -EBADFD;
	अगर (copy_from_user(&params, _params, माप(params)))
		वापस -EFAULT;
	अगर (!(t->hw.flags & SNDRV_TIMER_HW_SLAVE)) अणु
		u64 resolution;

		अगर (params.ticks < 1) अणु
			err = -EINVAL;
			जाओ _end;
		पूर्ण

		/* Don't allow resolution less than 1ms */
		resolution = snd_समयr_resolution(tu->समयri);
		resolution *= params.ticks;
		अगर (resolution < 1000000) अणु
			err = -EINVAL;
			जाओ _end;
		पूर्ण
	पूर्ण
	अगर (params.queue_size > 0 &&
	    (params.queue_size < 32 || params.queue_size > 1024)) अणु
		err = -EINVAL;
		जाओ _end;
	पूर्ण
	अगर (params.filter & ~((1<<SNDRV_TIMER_EVENT_RESOLUTION)|
			      (1<<SNDRV_TIMER_EVENT_TICK)|
			      (1<<SNDRV_TIMER_EVENT_START)|
			      (1<<SNDRV_TIMER_EVENT_STOP)|
			      (1<<SNDRV_TIMER_EVENT_CONTINUE)|
			      (1<<SNDRV_TIMER_EVENT_PAUSE)|
			      (1<<SNDRV_TIMER_EVENT_SUSPEND)|
			      (1<<SNDRV_TIMER_EVENT_RESUME)|
			      (1<<SNDRV_TIMER_EVENT_MSTART)|
			      (1<<SNDRV_TIMER_EVENT_MSTOP)|
			      (1<<SNDRV_TIMER_EVENT_MCONTINUE)|
			      (1<<SNDRV_TIMER_EVENT_MPAUSE)|
			      (1<<SNDRV_TIMER_EVENT_MSUSPEND)|
			      (1<<SNDRV_TIMER_EVENT_MRESUME))) अणु
		err = -EINVAL;
		जाओ _end;
	पूर्ण
	snd_समयr_stop(tu->समयri);
	spin_lock_irq(&t->lock);
	tu->समयri->flags &= ~(SNDRV_TIMER_IFLG_AUTO|
			       SNDRV_TIMER_IFLG_EXCLUSIVE|
			       SNDRV_TIMER_IFLG_EARLY_EVENT);
	अगर (params.flags & SNDRV_TIMER_PSFLG_AUTO)
		tu->समयri->flags |= SNDRV_TIMER_IFLG_AUTO;
	अगर (params.flags & SNDRV_TIMER_PSFLG_EXCLUSIVE)
		tu->समयri->flags |= SNDRV_TIMER_IFLG_EXCLUSIVE;
	अगर (params.flags & SNDRV_TIMER_PSFLG_EARLY_EVENT)
		tu->समयri->flags |= SNDRV_TIMER_IFLG_EARLY_EVENT;
	spin_unlock_irq(&t->lock);
	अगर (params.queue_size > 0 &&
	    (अचिन्हित पूर्णांक)tu->queue_size != params.queue_size) अणु
		err = पुनः_स्मृति_user_queue(tu, params.queue_size);
		अगर (err < 0)
			जाओ _end;
	पूर्ण
	spin_lock_irq(&tu->qlock);
	tu->qhead = tu->qtail = tu->qused = 0;
	अगर (tu->समयri->flags & SNDRV_TIMER_IFLG_EARLY_EVENT) अणु
		अगर (tu->tपढ़ो) अणु
			काष्ठा snd_समयr_tपढ़ो64 tपढ़ो;
			स_रखो(&tपढ़ो, 0, माप(tपढ़ो));
			tपढ़ो.event = SNDRV_TIMER_EVENT_EARLY;
			tपढ़ो.tstamp_sec = 0;
			tपढ़ो.tstamp_nsec = 0;
			tपढ़ो.val = 0;
			snd_समयr_user_append_to_tqueue(tu, &tपढ़ो);
		पूर्ण अन्यथा अणु
			काष्ठा snd_समयr_पढ़ो *r = &tu->queue[0];
			r->resolution = 0;
			r->ticks = 0;
			tu->qused++;
			tu->qtail++;
		पूर्ण
	पूर्ण
	tu->filter = params.filter;
	tu->ticks = params.ticks;
	spin_unlock_irq(&tu->qlock);
	err = 0;
 _end:
	अगर (copy_to_user(_params, &params, माप(params)))
		वापस -EFAULT;
	वापस err;
पूर्ण

अटल पूर्णांक snd_समयr_user_status32(काष्ठा file *file,
				   काष्ठा snd_समयr_status32 __user *_status)
 अणु
	काष्ठा snd_समयr_user *tu;
	काष्ठा snd_समयr_status32 status;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	स_रखो(&status, 0, माप(status));
	status.tstamp_sec = tu->tstamp.tv_sec;
	status.tstamp_nsec = tu->tstamp.tv_nsec;
	status.resolution = snd_समयr_resolution(tu->समयri);
	status.lost = tu->समयri->lost;
	status.overrun = tu->overrun;
	spin_lock_irq(&tu->qlock);
	status.queue = tu->qused;
	spin_unlock_irq(&tu->qlock);
	अगर (copy_to_user(_status, &status, माप(status)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_status64(काष्ठा file *file,
				   काष्ठा snd_समयr_status64 __user *_status)
अणु
	काष्ठा snd_समयr_user *tu;
	काष्ठा snd_समयr_status64 status;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	स_रखो(&status, 0, माप(status));
	status.tstamp_sec = tu->tstamp.tv_sec;
	status.tstamp_nsec = tu->tstamp.tv_nsec;
	status.resolution = snd_समयr_resolution(tu->समयri);
	status.lost = tu->समयri->lost;
	status.overrun = tu->overrun;
	spin_lock_irq(&tu->qlock);
	status.queue = tu->qused;
	spin_unlock_irq(&tu->qlock);
	अगर (copy_to_user(_status, &status, माप(status)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_start(काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा snd_समयr_user *tu;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	snd_समयr_stop(tu->समयri);
	tu->समयri->lost = 0;
	tu->last_resolution = 0;
	err = snd_समयr_start(tu->समयri, tu->ticks);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_stop(काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा snd_समयr_user *tu;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	err = snd_समयr_stop(tu->समयri);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_जारी(काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा snd_समयr_user *tu;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	/* start समयr instead of जारी अगर it's not used beक्रमe */
	अगर (!(tu->समयri->flags & SNDRV_TIMER_IFLG_PAUSED))
		वापस snd_समयr_user_start(file);
	tu->समयri->lost = 0;
	err = snd_समयr_जारी(tu->समयri);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_छोड़ो(काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा snd_समयr_user *tu;

	tu = file->निजी_data;
	अगर (!tu->समयri)
		वापस -EBADFD;
	err = snd_समयr_छोड़ो(tu->समयri);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_समयr_user_tपढ़ो(व्योम __user *argp, काष्ठा snd_समयr_user *tu,
				अचिन्हित पूर्णांक cmd, bool compat)
अणु
	पूर्णांक __user *p = argp;
	पूर्णांक xarg, old_tपढ़ो;

	अगर (tu->समयri)	/* too late */
		वापस -EBUSY;
	अगर (get_user(xarg, p))
		वापस -EFAULT;

	old_tपढ़ो = tu->tपढ़ो;

	अगर (!xarg)
		tu->tपढ़ो = TREAD_FORMAT_NONE;
	अन्यथा अगर (cmd == SNDRV_TIMER_IOCTL_TREAD64 ||
		 (IS_ENABLED(CONFIG_64BIT) && !compat))
		tu->tपढ़ो = TREAD_FORMAT_TIME64;
	अन्यथा
		tu->tपढ़ो = TREAD_FORMAT_TIME32;

	अगर (tu->tपढ़ो != old_tपढ़ो &&
	    पुनः_स्मृति_user_queue(tu, tu->queue_size) < 0) अणु
		tu->tपढ़ो = old_tपढ़ो;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत अणु
	SNDRV_TIMER_IOCTL_START_OLD = _IO('T', 0x20),
	SNDRV_TIMER_IOCTL_STOP_OLD = _IO('T', 0x21),
	SNDRV_TIMER_IOCTL_CONTINUE_OLD = _IO('T', 0x22),
	SNDRV_TIMER_IOCTL_PAUSE_OLD = _IO('T', 0x23),
पूर्ण;

अटल दीर्घ __snd_समयr_user_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg, bool compat)
अणु
	काष्ठा snd_समयr_user *tu;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;

	tu = file->निजी_data;
	चयन (cmd) अणु
	हाल SNDRV_TIMER_IOCTL_PVERSION:
		वापस put_user(SNDRV_TIMER_VERSION, p) ? -EFAULT : 0;
	हाल SNDRV_TIMER_IOCTL_NEXT_DEVICE:
		वापस snd_समयr_user_next_device(argp);
	हाल SNDRV_TIMER_IOCTL_TREAD_OLD:
	हाल SNDRV_TIMER_IOCTL_TREAD64:
		वापस snd_समयr_user_tपढ़ो(argp, tu, cmd, compat);
	हाल SNDRV_TIMER_IOCTL_GINFO:
		वापस snd_समयr_user_ginfo(file, argp);
	हाल SNDRV_TIMER_IOCTL_GPARAMS:
		वापस snd_समयr_user_gparams(file, argp);
	हाल SNDRV_TIMER_IOCTL_GSTATUS:
		वापस snd_समयr_user_gstatus(file, argp);
	हाल SNDRV_TIMER_IOCTL_SELECT:
		वापस snd_समयr_user_tselect(file, argp);
	हाल SNDRV_TIMER_IOCTL_INFO:
		वापस snd_समयr_user_info(file, argp);
	हाल SNDRV_TIMER_IOCTL_PARAMS:
		वापस snd_समयr_user_params(file, argp);
	हाल SNDRV_TIMER_IOCTL_STATUS32:
		वापस snd_समयr_user_status32(file, argp);
	हाल SNDRV_TIMER_IOCTL_STATUS64:
		वापस snd_समयr_user_status64(file, argp);
	हाल SNDRV_TIMER_IOCTL_START:
	हाल SNDRV_TIMER_IOCTL_START_OLD:
		वापस snd_समयr_user_start(file);
	हाल SNDRV_TIMER_IOCTL_STOP:
	हाल SNDRV_TIMER_IOCTL_STOP_OLD:
		वापस snd_समयr_user_stop(file);
	हाल SNDRV_TIMER_IOCTL_CONTINUE:
	हाल SNDRV_TIMER_IOCTL_CONTINUE_OLD:
		वापस snd_समयr_user_जारी(file);
	हाल SNDRV_TIMER_IOCTL_PAUSE:
	हाल SNDRV_TIMER_IOCTL_PAUSE_OLD:
		वापस snd_समयr_user_छोड़ो(file);
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल दीर्घ snd_समयr_user_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_समयr_user *tu = file->निजी_data;
	दीर्घ ret;

	mutex_lock(&tu->ioctl_lock);
	ret = __snd_समयr_user_ioctl(file, cmd, arg, false);
	mutex_unlock(&tu->ioctl_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_समयr_user_fasync(पूर्णांक fd, काष्ठा file * file, पूर्णांक on)
अणु
	काष्ठा snd_समयr_user *tu;

	tu = file->निजी_data;
	वापस fasync_helper(fd, file, on, &tu->fasync);
पूर्ण

अटल sमाप_प्रकार snd_समयr_user_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा snd_समयr_tपढ़ो64 *tपढ़ो;
	काष्ठा snd_समयr_tपढ़ो32 tपढ़ो32;
	काष्ठा snd_समयr_user *tu;
	दीर्घ result = 0, unit;
	पूर्णांक qhead;
	पूर्णांक err = 0;

	tu = file->निजी_data;
	चयन (tu->tपढ़ो) अणु
	हाल TREAD_FORMAT_TIME64:
		unit = माप(काष्ठा snd_समयr_tपढ़ो64);
		अवरोध;
	हाल TREAD_FORMAT_TIME32:
		unit = माप(काष्ठा snd_समयr_tपढ़ो32);
		अवरोध;
	हाल TREAD_FORMAT_NONE:
		unit = माप(काष्ठा snd_समयr_पढ़ो);
		अवरोध;
	शेष:
		WARN_ONCE(1, "Corrupt snd_timer_user\n");
		वापस -ENOTSUPP;
	पूर्ण

	mutex_lock(&tu->ioctl_lock);
	spin_lock_irq(&tu->qlock);
	जबतक ((दीर्घ)count - result >= unit) अणु
		जबतक (!tu->qused) अणु
			रुको_queue_entry_t रुको;

			अगर ((file->f_flags & O_NONBLOCK) != 0 || result > 0) अणु
				err = -EAGAIN;
				जाओ _error;
			पूर्ण

			set_current_state(TASK_INTERRUPTIBLE);
			init_रुकोqueue_entry(&रुको, current);
			add_रुको_queue(&tu->qchange_sleep, &रुको);

			spin_unlock_irq(&tu->qlock);
			mutex_unlock(&tu->ioctl_lock);
			schedule();
			mutex_lock(&tu->ioctl_lock);
			spin_lock_irq(&tu->qlock);

			हटाओ_रुको_queue(&tu->qchange_sleep, &रुको);

			अगर (tu->disconnected) अणु
				err = -ENODEV;
				जाओ _error;
			पूर्ण
			अगर (संकेत_pending(current)) अणु
				err = -ERESTARTSYS;
				जाओ _error;
			पूर्ण
		पूर्ण

		qhead = tu->qhead++;
		tu->qhead %= tu->queue_size;
		tu->qused--;
		spin_unlock_irq(&tu->qlock);

		tपढ़ो = &tu->tqueue[qhead];

		चयन (tu->tपढ़ो) अणु
		हाल TREAD_FORMAT_TIME64:
			अगर (copy_to_user(buffer, tपढ़ो,
					 माप(काष्ठा snd_समयr_tपढ़ो64)))
				err = -EFAULT;
			अवरोध;
		हाल TREAD_FORMAT_TIME32:
			स_रखो(&tपढ़ो32, 0, माप(tपढ़ो32));
			tपढ़ो32 = (काष्ठा snd_समयr_tपढ़ो32) अणु
				.event = tपढ़ो->event,
				.tstamp_sec = tपढ़ो->tstamp_sec,
				.tstamp_nsec = tपढ़ो->tstamp_nsec,
				.val = tपढ़ो->val,
			पूर्ण;

			अगर (copy_to_user(buffer, &tपढ़ो32, माप(tपढ़ो32)))
				err = -EFAULT;
			अवरोध;
		हाल TREAD_FORMAT_NONE:
			अगर (copy_to_user(buffer, &tu->queue[qhead],
					 माप(काष्ठा snd_समयr_पढ़ो)))
				err = -EFAULT;
			अवरोध;
		शेष:
			err = -ENOTSUPP;
			अवरोध;
		पूर्ण

		spin_lock_irq(&tu->qlock);
		अगर (err < 0)
			जाओ _error;
		result += unit;
		buffer += unit;
	पूर्ण
 _error:
	spin_unlock_irq(&tu->qlock);
	mutex_unlock(&tu->ioctl_lock);
	वापस result > 0 ? result : err;
पूर्ण

अटल __poll_t snd_समयr_user_poll(काष्ठा file *file, poll_table * रुको)
अणु
        __poll_t mask;
        काष्ठा snd_समयr_user *tu;

        tu = file->निजी_data;

        poll_रुको(file, &tu->qchange_sleep, रुको);

	mask = 0;
	spin_lock_irq(&tu->qlock);
	अगर (tu->qused)
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (tu->disconnected)
		mask |= EPOLLERR;
	spin_unlock_irq(&tu->qlock);

	वापस mask;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#समावेश "timer_compat.c"
#अन्यथा
#घोषणा snd_समयr_user_ioctl_compat	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations snd_समयr_f_ops =
अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		snd_समयr_user_पढ़ो,
	.खोलो =		snd_समयr_user_खोलो,
	.release =	snd_समयr_user_release,
	.llseek =	no_llseek,
	.poll =		snd_समयr_user_poll,
	.unlocked_ioctl =	snd_समयr_user_ioctl,
	.compat_ioctl =	snd_समयr_user_ioctl_compat,
	.fasync = 	snd_समयr_user_fasync,
पूर्ण;

/* unरेजिस्टर the प्रणाली समयr */
अटल व्योम snd_समयr_मुक्त_all(व्योम)
अणु
	काष्ठा snd_समयr *समयr, *n;

	list_क्रम_each_entry_safe(समयr, n, &snd_समयr_list, device_list)
		snd_समयr_मुक्त(समयr);
पूर्ण

अटल काष्ठा device समयr_dev;

/*
 *  ENTRY functions
 */

अटल पूर्णांक __init alsa_समयr_init(व्योम)
अणु
	पूर्णांक err;

	snd_device_initialize(&समयr_dev, शून्य);
	dev_set_name(&समयr_dev, "timer");

#अगर_घोषित SNDRV_OSS_INFO_DEV_TIMERS
	snd_oss_info_रेजिस्टर(SNDRV_OSS_INFO_DEV_TIMERS, SNDRV_CARDS - 1,
			      "system timer");
#पूर्ण_अगर

	err = snd_समयr_रेजिस्टर_प्रणाली();
	अगर (err < 0) अणु
		pr_err("ALSA: unable to register system timer (%i)\n", err);
		जाओ put_समयr;
	पूर्ण

	err = snd_रेजिस्टर_device(SNDRV_DEVICE_TYPE_TIMER, शून्य, 0,
				  &snd_समयr_f_ops, शून्य, &समयr_dev);
	अगर (err < 0) अणु
		pr_err("ALSA: unable to register timer device (%i)\n", err);
		snd_समयr_मुक्त_all();
		जाओ put_समयr;
	पूर्ण

	snd_समयr_proc_init();
	वापस 0;

put_समयr:
	put_device(&समयr_dev);
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_समयr_निकास(व्योम)
अणु
	snd_unरेजिस्टर_device(&समयr_dev);
	snd_समयr_मुक्त_all();
	put_device(&समयr_dev);
	snd_समयr_proc_करोne();
#अगर_घोषित SNDRV_OSS_INFO_DEV_TIMERS
	snd_oss_info_unरेजिस्टर(SNDRV_OSS_INFO_DEV_TIMERS, SNDRV_CARDS - 1);
#पूर्ण_अगर
पूर्ण

module_init(alsa_समयr_init)
module_निकास(alsa_समयr_निकास)

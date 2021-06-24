<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * general समयr device क्रम using in ISDN stacks
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#समावेश <linux/poll.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mISDNअगर.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "core.h"

अटल DEFINE_MUTEX(mISDN_mutex);
अटल u_पूर्णांक	*debug;


काष्ठा mISDNसमयrdev अणु
	पूर्णांक			next_id;
	काष्ठा list_head	pending;
	काष्ठा list_head	expired;
	रुको_queue_head_t	रुको;
	u_पूर्णांक			work;
	spinlock_t		lock; /* protect lists */
पूर्ण;

काष्ठा mISDNसमयr अणु
	काष्ठा list_head	list;
	काष्ठा  mISDNसमयrdev	*dev;
	काष्ठा समयr_list	tl;
	पूर्णांक			id;
पूर्ण;

अटल पूर्णांक
mISDN_खोलो(काष्ठा inode *ino, काष्ठा file *filep)
अणु
	काष्ठा mISDNसमयrdev	*dev;

	अगर (*debug & DEBUG_TIMER)
		prपूर्णांकk(KERN_DEBUG "%s(%p,%p)\n", __func__, ino, filep);
	dev = kदो_स्मृति(माप(काष्ठा mISDNसमयrdev) , GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->next_id = 1;
	INIT_LIST_HEAD(&dev->pending);
	INIT_LIST_HEAD(&dev->expired);
	spin_lock_init(&dev->lock);
	dev->work = 0;
	init_रुकोqueue_head(&dev->रुको);
	filep->निजी_data = dev;
	वापस nonseekable_खोलो(ino, filep);
पूर्ण

अटल पूर्णांक
mISDN_बंद(काष्ठा inode *ino, काष्ठा file *filep)
अणु
	काष्ठा mISDNसमयrdev	*dev = filep->निजी_data;
	काष्ठा list_head	*list = &dev->pending;
	काष्ठा mISDNसमयr	*समयr, *next;

	अगर (*debug & DEBUG_TIMER)
		prपूर्णांकk(KERN_DEBUG "%s(%p,%p)\n", __func__, ino, filep);

	spin_lock_irq(&dev->lock);
	जबतक (!list_empty(list)) अणु
		समयr = list_first_entry(list, काष्ठा mISDNसमयr, list);
		spin_unlock_irq(&dev->lock);
		del_समयr_sync(&समयr->tl);
		spin_lock_irq(&dev->lock);
		/* it might have been moved to ->expired */
		list_del(&समयr->list);
		kमुक्त(समयr);
	पूर्ण
	spin_unlock_irq(&dev->lock);

	list_क्रम_each_entry_safe(समयr, next, &dev->expired, list) अणु
		kमुक्त(समयr);
	पूर्ण
	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
mISDN_पढ़ो(काष्ठा file *filep, अक्षर __user *buf, माप_प्रकार count, loff_t *off)
अणु
	काष्ठा mISDNसमयrdev	*dev = filep->निजी_data;
	काष्ठा list_head *list = &dev->expired;
	काष्ठा mISDNसमयr	*समयr;
	पूर्णांक	ret = 0;

	अगर (*debug & DEBUG_TIMER)
		prपूर्णांकk(KERN_DEBUG "%s(%p, %p, %d, %p)\n", __func__,
		       filep, buf, (पूर्णांक)count, off);

	अगर (count < माप(पूर्णांक))
		वापस -ENOSPC;

	spin_lock_irq(&dev->lock);
	जबतक (list_empty(list) && (dev->work == 0)) अणु
		spin_unlock_irq(&dev->lock);
		अगर (filep->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		रुको_event_पूर्णांकerruptible(dev->रुको, (dev->work ||
						     !list_empty(list)));
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		spin_lock_irq(&dev->lock);
	पूर्ण
	अगर (dev->work)
		dev->work = 0;
	अगर (!list_empty(list)) अणु
		समयr = list_first_entry(list, काष्ठा mISDNसमयr, list);
		list_del(&समयr->list);
		spin_unlock_irq(&dev->lock);
		अगर (put_user(समयr->id, (पूर्णांक __user *)buf))
			ret = -EFAULT;
		अन्यथा
			ret = माप(पूर्णांक);
		kमुक्त(समयr);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&dev->lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल __poll_t
mISDN_poll(काष्ठा file *filep, poll_table *रुको)
अणु
	काष्ठा mISDNसमयrdev	*dev = filep->निजी_data;
	__poll_t		mask = EPOLLERR;

	अगर (*debug & DEBUG_TIMER)
		prपूर्णांकk(KERN_DEBUG "%s(%p, %p)\n", __func__, filep, रुको);
	अगर (dev) अणु
		poll_रुको(filep, &dev->रुको, रुको);
		mask = 0;
		अगर (dev->work || !list_empty(&dev->expired))
			mask |= (EPOLLIN | EPOLLRDNORM);
		अगर (*debug & DEBUG_TIMER)
			prपूर्णांकk(KERN_DEBUG "%s work(%d) empty(%d)\n", __func__,
			       dev->work, list_empty(&dev->expired));
	पूर्ण
	वापस mask;
पूर्ण

अटल व्योम
dev_expire_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mISDNसमयr *समयr = from_समयr(समयr, t, tl);
	u_दीर्घ			flags;

	spin_lock_irqsave(&समयr->dev->lock, flags);
	अगर (समयr->id >= 0)
		list_move_tail(&समयr->list, &समयr->dev->expired);
	wake_up_पूर्णांकerruptible(&समयr->dev->रुको);
	spin_unlock_irqrestore(&समयr->dev->lock, flags);
पूर्ण

अटल पूर्णांक
misdn_add_समयr(काष्ठा mISDNसमयrdev *dev, पूर्णांक समयout)
अणु
	पूर्णांक			id;
	काष्ठा mISDNसमयr	*समयr;

	अगर (!समयout) अणु
		dev->work = 1;
		wake_up_पूर्णांकerruptible(&dev->रुको);
		id = 0;
	पूर्ण अन्यथा अणु
		समयr = kzalloc(माप(काष्ठा mISDNसमयr), GFP_KERNEL);
		अगर (!समयr)
			वापस -ENOMEM;
		समयr->dev = dev;
		समयr_setup(&समयr->tl, dev_expire_समयr, 0);
		spin_lock_irq(&dev->lock);
		id = समयr->id = dev->next_id++;
		अगर (dev->next_id < 0)
			dev->next_id = 1;
		list_add_tail(&समयr->list, &dev->pending);
		समयr->tl.expires = jअगरfies + ((HZ * (u_दीर्घ)समयout) / 1000);
		add_समयr(&समयr->tl);
		spin_unlock_irq(&dev->lock);
	पूर्ण
	वापस id;
पूर्ण

अटल पूर्णांक
misdn_del_समयr(काष्ठा mISDNसमयrdev *dev, पूर्णांक id)
अणु
	काष्ठा mISDNसमयr	*समयr;

	spin_lock_irq(&dev->lock);
	list_क्रम_each_entry(समयr, &dev->pending, list) अणु
		अगर (समयr->id == id) अणु
			list_del_init(&समयr->list);
			समयr->id = -1;
			spin_unlock_irq(&dev->lock);
			del_समयr_sync(&समयr->tl);
			kमुक्त(समयr);
			वापस id;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&dev->lock);
	वापस 0;
पूर्ण

अटल दीर्घ
mISDN_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mISDNसमयrdev	*dev = filep->निजी_data;
	पूर्णांक			id, tout, ret = 0;


	अगर (*debug & DEBUG_TIMER)
		prपूर्णांकk(KERN_DEBUG "%s(%p, %x, %lx)\n", __func__,
		       filep, cmd, arg);
	mutex_lock(&mISDN_mutex);
	चयन (cmd) अणु
	हाल IMADDTIMER:
		अगर (get_user(tout, (पूर्णांक __user *)arg)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		id = misdn_add_समयr(dev, tout);
		अगर (*debug & DEBUG_TIMER)
			prपूर्णांकk(KERN_DEBUG "%s add %d id %d\n", __func__,
			       tout, id);
		अगर (id < 0) अणु
			ret = id;
			अवरोध;
		पूर्ण
		अगर (put_user(id, (पूर्णांक __user *)arg))
			ret = -EFAULT;
		अवरोध;
	हाल IMDELTIMER:
		अगर (get_user(id, (पूर्णांक __user *)arg)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (*debug & DEBUG_TIMER)
			prपूर्णांकk(KERN_DEBUG "%s del id %d\n", __func__, id);
		id = misdn_del_समयr(dev, id);
		अगर (put_user(id, (पूर्णांक __user *)arg))
			ret = -EFAULT;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&mISDN_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations mISDN_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= mISDN_पढ़ो,
	.poll		= mISDN_poll,
	.unlocked_ioctl	= mISDN_ioctl,
	.खोलो		= mISDN_खोलो,
	.release	= mISDN_बंद,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice mISDNसमयr = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "mISDNtimer",
	.fops	= &mISDN_fops,
पूर्ण;

पूर्णांक
mISDN_initसमयr(u_पूर्णांक *deb)
अणु
	पूर्णांक	err;

	debug = deb;
	err = misc_रेजिस्टर(&mISDNसमयr);
	अगर (err)
		prपूर्णांकk(KERN_WARNING "mISDN: Could not register timer device\n");
	वापस err;
पूर्ण

व्योम mISDN_समयr_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&mISDNसमयr);
पूर्ण

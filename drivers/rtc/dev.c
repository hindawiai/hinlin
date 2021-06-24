<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC subप्रणाली, dev पूर्णांकerface
 *
 * Copyright (C) 2005 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 * based on arch/arm/common/rtस_समय.c
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "rtc-core.h"

अटल dev_t rtc_devt;

#घोषणा RTC_DEV_MAX 16 /* 16 RTCs should be enough क्रम everyone... */

अटल पूर्णांक rtc_dev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rtc_device *rtc = container_of(inode->i_cdev,
					काष्ठा rtc_device, अक्षर_dev);

	अगर (test_and_set_bit_lock(RTC_DEV_BUSY, &rtc->flags))
		वापस -EBUSY;

	file->निजी_data = rtc;

	spin_lock_irq(&rtc->irq_lock);
	rtc->irq_data = 0;
	spin_unlock_irq(&rtc->irq_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_RTC_INTF_DEV_UIE_EMUL
/*
 * Routine to poll RTC seconds field क्रम change as often as possible,
 * after first RTC_UIE use समयr to reduce polling
 */
अटल व्योम rtc_uie_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtc_device *rtc =
		container_of(work, काष्ठा rtc_device, uie_task);
	काष्ठा rtc_समय पंचांग;
	पूर्णांक num = 0;
	पूर्णांक err;

	err = rtc_पढ़ो_समय(rtc, &पंचांग);

	spin_lock_irq(&rtc->irq_lock);
	अगर (rtc->stop_uie_polling || err) अणु
		rtc->uie_task_active = 0;
	पूर्ण अन्यथा अगर (rtc->oldsecs != पंचांग.पंचांग_sec) अणु
		num = (पंचांग.पंचांग_sec + 60 - rtc->oldsecs) % 60;
		rtc->oldsecs = पंचांग.पंचांग_sec;
		rtc->uie_समयr.expires = jअगरfies + HZ - (HZ / 10);
		rtc->uie_समयr_active = 1;
		rtc->uie_task_active = 0;
		add_समयr(&rtc->uie_समयr);
	पूर्ण अन्यथा अगर (schedule_work(&rtc->uie_task) == 0) अणु
		rtc->uie_task_active = 0;
	पूर्ण
	spin_unlock_irq(&rtc->irq_lock);
	अगर (num)
		rtc_handle_legacy_irq(rtc, num, RTC_UF);
पूर्ण

अटल व्योम rtc_uie_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा rtc_device *rtc = from_समयr(rtc, t, uie_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc->irq_lock, flags);
	rtc->uie_समयr_active = 0;
	rtc->uie_task_active = 1;
	अगर ((schedule_work(&rtc->uie_task) == 0))
		rtc->uie_task_active = 0;
	spin_unlock_irqrestore(&rtc->irq_lock, flags);
पूर्ण

अटल पूर्णांक clear_uie(काष्ठा rtc_device *rtc)
अणु
	spin_lock_irq(&rtc->irq_lock);
	अगर (rtc->uie_irq_active) अणु
		rtc->stop_uie_polling = 1;
		अगर (rtc->uie_समयr_active) अणु
			spin_unlock_irq(&rtc->irq_lock);
			del_समयr_sync(&rtc->uie_समयr);
			spin_lock_irq(&rtc->irq_lock);
			rtc->uie_समयr_active = 0;
		पूर्ण
		अगर (rtc->uie_task_active) अणु
			spin_unlock_irq(&rtc->irq_lock);
			flush_scheduled_work();
			spin_lock_irq(&rtc->irq_lock);
		पूर्ण
		rtc->uie_irq_active = 0;
	पूर्ण
	spin_unlock_irq(&rtc->irq_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक set_uie(काष्ठा rtc_device *rtc)
अणु
	काष्ठा rtc_समय पंचांग;
	पूर्णांक err;

	err = rtc_पढ़ो_समय(rtc, &पंचांग);
	अगर (err)
		वापस err;
	spin_lock_irq(&rtc->irq_lock);
	अगर (!rtc->uie_irq_active) अणु
		rtc->uie_irq_active = 1;
		rtc->stop_uie_polling = 0;
		rtc->oldsecs = पंचांग.पंचांग_sec;
		rtc->uie_task_active = 1;
		अगर (schedule_work(&rtc->uie_task) == 0)
			rtc->uie_task_active = 0;
	पूर्ण
	rtc->irq_data = 0;
	spin_unlock_irq(&rtc->irq_lock);
	वापस 0;
पूर्ण

पूर्णांक rtc_dev_update_irq_enable_emul(काष्ठा rtc_device *rtc, अचिन्हित पूर्णांक enabled)
अणु
	अगर (enabled)
		वापस set_uie(rtc);
	अन्यथा
		वापस clear_uie(rtc);
पूर्ण
EXPORT_SYMBOL(rtc_dev_update_irq_enable_emul);

#पूर्ण_अगर /* CONFIG_RTC_INTF_DEV_UIE_EMUL */

अटल sमाप_प्रकार
rtc_dev_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rtc_device *rtc = file->निजी_data;

	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ data;
	sमाप_प्रकार ret;

	अगर (count != माप(अचिन्हित पूर्णांक) && count < माप(अचिन्हित दीर्घ))
		वापस -EINVAL;

	add_रुको_queue(&rtc->irq_queue, &रुको);
	करो अणु
		__set_current_state(TASK_INTERRUPTIBLE);

		spin_lock_irq(&rtc->irq_lock);
		data = rtc->irq_data;
		rtc->irq_data = 0;
		spin_unlock_irq(&rtc->irq_lock);

		अगर (data != 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		अगर (file->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		schedule();
	पूर्ण जबतक (1);
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&rtc->irq_queue, &रुको);

	अगर (ret == 0) अणु
		अगर (माप(पूर्णांक) != माप(दीर्घ) &&
		    count == माप(अचिन्हित पूर्णांक))
			ret = put_user(data, (अचिन्हित पूर्णांक __user *)buf) ?:
				माप(अचिन्हित पूर्णांक);
		अन्यथा
			ret = put_user(data, (अचिन्हित दीर्घ __user *)buf) ?:
				माप(अचिन्हित दीर्घ);
	पूर्ण
	वापस ret;
पूर्ण

अटल __poll_t rtc_dev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा rtc_device *rtc = file->निजी_data;
	अचिन्हित दीर्घ data;

	poll_रुको(file, &rtc->irq_queue, रुको);

	data = rtc->irq_data;

	वापस (data != 0) ? (EPOLLIN | EPOLLRDNORM) : 0;
पूर्ण

अटल दीर्घ rtc_dev_ioctl(काष्ठा file *file,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err = 0;
	काष्ठा rtc_device *rtc = file->निजी_data;
	स्थिर काष्ठा rtc_class_ops *ops = rtc->ops;
	काष्ठा rtc_समय पंचांग;
	काष्ठा rtc_wkalrm alarm;
	व्योम __user *uarg = (व्योम __user *)arg;

	err = mutex_lock_पूर्णांकerruptible(&rtc->ops_lock);
	अगर (err)
		वापस err;

	/* check that the calling task has appropriate permissions
	 * क्रम certain ioctls. करोing this check here is useful
	 * to aव्योम duplicate code in each driver.
	 */
	चयन (cmd) अणु
	हाल RTC_EPOCH_SET:
	हाल RTC_SET_TIME:
		अगर (!capable(CAP_SYS_TIME))
			err = -EACCES;
		अवरोध;

	हाल RTC_IRQP_SET:
		अगर (arg > rtc->max_user_freq && !capable(CAP_SYS_RESOURCE))
			err = -EACCES;
		अवरोध;

	हाल RTC_PIE_ON:
		अगर (rtc->irq_freq > rtc->max_user_freq &&
		    !capable(CAP_SYS_RESOURCE))
			err = -EACCES;
		अवरोध;
	पूर्ण

	अगर (err)
		जाओ करोne;

	/*
	 * Drivers *SHOULD NOT* provide ioctl implementations
	 * क्रम these requests.  Instead, provide methods to
	 * support the following code, so that the RTC's मुख्य
	 * features are accessible without using ioctls.
	 *
	 * RTC and alarm बार will be in UTC, by preference,
	 * but dual-booting with MS-Winकरोws implies RTCs must
	 * use the local wall घड़ी समय.
	 */

	चयन (cmd) अणु
	हाल RTC_ALM_READ:
		mutex_unlock(&rtc->ops_lock);

		err = rtc_पढ़ो_alarm(rtc, &alarm);
		अगर (err < 0)
			वापस err;

		अगर (copy_to_user(uarg, &alarm.समय, माप(पंचांग)))
			err = -EFAULT;
		वापस err;

	हाल RTC_ALM_SET:
		mutex_unlock(&rtc->ops_lock);

		अगर (copy_from_user(&alarm.समय, uarg, माप(पंचांग)))
			वापस -EFAULT;

		alarm.enabled = 0;
		alarm.pending = 0;
		alarm.समय.पंचांग_wday = -1;
		alarm.समय.पंचांग_yday = -1;
		alarm.समय.पंचांग_isdst = -1;

		/* RTC_ALM_SET alarms may be up to 24 hours in the future.
		 * Rather than expecting every RTC to implement "don't care"
		 * क्रम day/month/year fields, just क्रमce the alarm to have
		 * the right values क्रम those fields.
		 *
		 * RTC_WKALM_SET should be used instead.  Not only करोes it
		 * eliminate the need क्रम a separate RTC_AIE_ON call, it
		 * करोesn't have the "alarm 23:59:59 in the future" race.
		 *
		 * NOTE:  some legacy code may have used invalid fields as
		 * wildcards, exposing hardware "periodic alarm" capabilities.
		 * Not supported here.
		 */
		अणु
			समय64_t now, then;

			err = rtc_पढ़ो_समय(rtc, &पंचांग);
			अगर (err < 0)
				वापस err;
			now = rtc_पंचांग_to_समय64(&पंचांग);

			alarm.समय.पंचांग_mday = पंचांग.पंचांग_mday;
			alarm.समय.पंचांग_mon = पंचांग.पंचांग_mon;
			alarm.समय.पंचांग_year = पंचांग.पंचांग_year;
			err  = rtc_valid_पंचांग(&alarm.समय);
			अगर (err < 0)
				वापस err;
			then = rtc_पंचांग_to_समय64(&alarm.समय);

			/* alarm may need to wrap पूर्णांकo tomorrow */
			अगर (then < now) अणु
				rtc_समय64_to_पंचांग(now + 24 * 60 * 60, &पंचांग);
				alarm.समय.पंचांग_mday = पंचांग.पंचांग_mday;
				alarm.समय.पंचांग_mon = पंचांग.पंचांग_mon;
				alarm.समय.पंचांग_year = पंचांग.पंचांग_year;
			पूर्ण
		पूर्ण

		वापस rtc_set_alarm(rtc, &alarm);

	हाल RTC_RD_TIME:
		mutex_unlock(&rtc->ops_lock);

		err = rtc_पढ़ो_समय(rtc, &पंचांग);
		अगर (err < 0)
			वापस err;

		अगर (copy_to_user(uarg, &पंचांग, माप(पंचांग)))
			err = -EFAULT;
		वापस err;

	हाल RTC_SET_TIME:
		mutex_unlock(&rtc->ops_lock);

		अगर (copy_from_user(&पंचांग, uarg, माप(पंचांग)))
			वापस -EFAULT;

		वापस rtc_set_समय(rtc, &पंचांग);

	हाल RTC_PIE_ON:
		err = rtc_irq_set_state(rtc, 1);
		अवरोध;

	हाल RTC_PIE_OFF:
		err = rtc_irq_set_state(rtc, 0);
		अवरोध;

	हाल RTC_AIE_ON:
		mutex_unlock(&rtc->ops_lock);
		वापस rtc_alarm_irq_enable(rtc, 1);

	हाल RTC_AIE_OFF:
		mutex_unlock(&rtc->ops_lock);
		वापस rtc_alarm_irq_enable(rtc, 0);

	हाल RTC_UIE_ON:
		mutex_unlock(&rtc->ops_lock);
		वापस rtc_update_irq_enable(rtc, 1);

	हाल RTC_UIE_OFF:
		mutex_unlock(&rtc->ops_lock);
		वापस rtc_update_irq_enable(rtc, 0);

	हाल RTC_IRQP_SET:
		err = rtc_irq_set_freq(rtc, arg);
		अवरोध;
	हाल RTC_IRQP_READ:
		err = put_user(rtc->irq_freq, (अचिन्हित दीर्घ __user *)uarg);
		अवरोध;

	हाल RTC_WKALM_SET:
		mutex_unlock(&rtc->ops_lock);
		अगर (copy_from_user(&alarm, uarg, माप(alarm)))
			वापस -EFAULT;

		वापस rtc_set_alarm(rtc, &alarm);

	हाल RTC_WKALM_RD:
		mutex_unlock(&rtc->ops_lock);
		err = rtc_पढ़ो_alarm(rtc, &alarm);
		अगर (err < 0)
			वापस err;

		अगर (copy_to_user(uarg, &alarm, माप(alarm)))
			err = -EFAULT;
		वापस err;

	शेष:
		/* Finally try the driver's ioctl पूर्णांकerface */
		अगर (ops->ioctl) अणु
			err = ops->ioctl(rtc->dev.parent, cmd, arg);
			अगर (err == -ENOIOCTLCMD)
				err = -ENOTTY;
		पूर्ण अन्यथा अणु
			err = -ENOTTY;
		पूर्ण
		अवरोध;
	पूर्ण

करोne:
	mutex_unlock(&rtc->ops_lock);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#घोषणा RTC_IRQP_SET32		_IOW('p', 0x0c, __u32)
#घोषणा RTC_IRQP_READ32		_IOR('p', 0x0b, __u32)
#घोषणा RTC_EPOCH_SET32		_IOW('p', 0x0e, __u32)

अटल दीर्घ rtc_dev_compat_ioctl(काष्ठा file *file,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा rtc_device *rtc = file->निजी_data;
	व्योम __user *uarg = compat_ptr(arg);

	चयन (cmd) अणु
	हाल RTC_IRQP_READ32:
		वापस put_user(rtc->irq_freq, (__u32 __user *)uarg);

	हाल RTC_IRQP_SET32:
		/* arg is a plain पूर्णांकeger, not poपूर्णांकer */
		वापस rtc_dev_ioctl(file, RTC_IRQP_SET, arg);

	हाल RTC_EPOCH_SET32:
		/* arg is a plain पूर्णांकeger, not poपूर्णांकer */
		वापस rtc_dev_ioctl(file, RTC_EPOCH_SET, arg);
	पूर्ण

	वापस rtc_dev_ioctl(file, cmd, (अचिन्हित दीर्घ)uarg);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rtc_dev_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा rtc_device *rtc = file->निजी_data;

	वापस fasync_helper(fd, file, on, &rtc->async_queue);
पूर्ण

अटल पूर्णांक rtc_dev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rtc_device *rtc = file->निजी_data;

	/* We shut करोwn the repeating IRQs that userspace enabled,
	 * since nothing is listening to them.
	 *  - Update (UIE) ... currently only managed through ioctls
	 *  - Periodic (PIE) ... also used through rtc_*() पूर्णांकerface calls
	 *
	 * Leave the alarm alone; it may be set to trigger a प्रणाली wakeup
	 * later, or be used by kernel code, and is a one-shot event anyway.
	 */

	/* Keep ioctl until all drivers are converted */
	rtc_dev_ioctl(file, RTC_UIE_OFF, 0);
	rtc_update_irq_enable(rtc, 0);
	rtc_irq_set_state(rtc, 0);

	clear_bit_unlock(RTC_DEV_BUSY, &rtc->flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations rtc_dev_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= rtc_dev_पढ़ो,
	.poll		= rtc_dev_poll,
	.unlocked_ioctl	= rtc_dev_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= rtc_dev_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= rtc_dev_खोलो,
	.release	= rtc_dev_release,
	.fasync		= rtc_dev_fasync,
पूर्ण;

/* insertion/removal hooks */

व्योम rtc_dev_prepare(काष्ठा rtc_device *rtc)
अणु
	अगर (!rtc_devt)
		वापस;

	अगर (rtc->id >= RTC_DEV_MAX) अणु
		dev_dbg(&rtc->dev, "too many RTC devices\n");
		वापस;
	पूर्ण

	rtc->dev.devt = MKDEV(MAJOR(rtc_devt), rtc->id);

#अगर_घोषित CONFIG_RTC_INTF_DEV_UIE_EMUL
	INIT_WORK(&rtc->uie_task, rtc_uie_task);
	समयr_setup(&rtc->uie_समयr, rtc_uie_समयr, 0);
#पूर्ण_अगर

	cdev_init(&rtc->अक्षर_dev, &rtc_dev_fops);
	rtc->अक्षर_dev.owner = rtc->owner;
पूर्ण

व्योम __init rtc_dev_init(व्योम)
अणु
	पूर्णांक err;

	err = alloc_chrdev_region(&rtc_devt, 0, RTC_DEV_MAX, "rtc");
	अगर (err < 0)
		pr_err("failed to allocate char dev region\n");
पूर्ण

व्योम __निकास rtc_dev_निकास(व्योम)
अणु
	अगर (rtc_devt)
		unरेजिस्टर_chrdev_region(rtc_devt, RTC_DEV_MAX);
पूर्ण

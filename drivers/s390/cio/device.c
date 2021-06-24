<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 *  bus driver क्रम ccw devices
 *
 *    Copyright IBM Corp. 2002, 2008
 *    Author(s): Arnd Bergmann (arndb@de.ibm.com)
 *		 Cornelia Huck (cornelia.huck@de.ibm.com)
 *		 Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#घोषणा KMSG_COMPONENT "cio"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/param.h>		/* HZ */
#समावेश <यंत्र/cmb.h>
#समावेश <यंत्र/isc.h>

#समावेश "chp.h"
#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "css.h"
#समावेश "device.h"
#समावेश "ioasm.h"
#समावेश "io_sch.h"
#समावेश "blacklist.h"
#समावेश "chsc.h"

अटल काष्ठा समयr_list recovery_समयr;
अटल DEFINE_SPINLOCK(recovery_lock);
अटल पूर्णांक recovery_phase;
अटल स्थिर अचिन्हित दीर्घ recovery_delay[] = अणु 3, 30, 300 पूर्ण;

अटल atomic_t ccw_device_init_count = ATOMIC_INIT(0);
अटल DECLARE_WAIT_QUEUE_HEAD(ccw_device_init_wq);
अटल काष्ठा bus_type ccw_bus_type;

/******************* bus type handling ***********************/

/* The Linux driver model distinguishes between a bus type and
 * the bus itself. Of course we only have one channel
 * subप्रणाली driver and one channel प्रणाली per machine, but
 * we still use the असलtraction. T.R. says it's a good idea. */
अटल पूर्णांक
ccw_bus_match (काष्ठा device * dev, काष्ठा device_driver * drv)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_driver *cdrv = to_ccwdrv(drv);
	स्थिर काष्ठा ccw_device_id *ids = cdrv->ids, *found;

	अगर (!ids)
		वापस 0;

	found = ccw_device_id_match(ids, &cdev->id);
	अगर (!found)
		वापस 0;

	cdev->id.driver_info = found->driver_info;

	वापस 1;
पूर्ण

/* Store modalias string delimited by prefix/suffix string पूर्णांकo buffer with
 * specअगरied size. Return length of resulting string (excluding trailing '\0')
 * even अगर string करोesn't fit buffer (snम_लिखो semantics). */
अटल पूर्णांक snprपूर्णांक_alias(अक्षर *buf, माप_प्रकार size,
			 काष्ठा ccw_device_id *id, स्थिर अक्षर *suffix)
अणु
	पूर्णांक len;

	len = snम_लिखो(buf, size, "ccw:t%04Xm%02X", id->cu_type, id->cu_model);
	अगर (len > size)
		वापस len;
	buf += len;
	size -= len;

	अगर (id->dev_type != 0)
		len += snम_लिखो(buf, size, "dt%04Xdm%02X%s", id->dev_type,
				id->dev_model, suffix);
	अन्यथा
		len += snम_लिखो(buf, size, "dtdm%s", suffix);

	वापस len;
पूर्ण

/* Set up environment variables क्रम ccw device uevent. Return 0 on success,
 * non-zero otherwise. */
अटल पूर्णांक ccw_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_device_id *id = &(cdev->id);
	पूर्णांक ret;
	अक्षर modalias_buf[30];

	/* CU_TYPE= */
	ret = add_uevent_var(env, "CU_TYPE=%04X", id->cu_type);
	अगर (ret)
		वापस ret;

	/* CU_MODEL= */
	ret = add_uevent_var(env, "CU_MODEL=%02X", id->cu_model);
	अगर (ret)
		वापस ret;

	/* The next two can be zero, that's ok क्रम us */
	/* DEV_TYPE= */
	ret = add_uevent_var(env, "DEV_TYPE=%04X", id->dev_type);
	अगर (ret)
		वापस ret;

	/* DEV_MODEL= */
	ret = add_uevent_var(env, "DEV_MODEL=%02X", id->dev_model);
	अगर (ret)
		वापस ret;

	/* MODALIAS=  */
	snprपूर्णांक_alias(modalias_buf, माप(modalias_buf), id, "");
	ret = add_uevent_var(env, "MODALIAS=%s", modalias_buf);
	वापस ret;
पूर्ण

अटल व्योम io_subchannel_irq(काष्ठा subchannel *);
अटल पूर्णांक io_subchannel_probe(काष्ठा subchannel *);
अटल पूर्णांक io_subchannel_हटाओ(काष्ठा subchannel *);
अटल व्योम io_subchannel_shutकरोwn(काष्ठा subchannel *);
अटल पूर्णांक io_subchannel_sch_event(काष्ठा subchannel *, पूर्णांक);
अटल पूर्णांक io_subchannel_chp_event(काष्ठा subchannel *, काष्ठा chp_link *,
				   पूर्णांक);
अटल व्योम recovery_func(काष्ठा समयr_list *unused);

अटल काष्ठा css_device_id io_subchannel_ids[] = अणु
	अणु .match_flags = 0x1, .type = SUBCHANNEL_TYPE_IO, पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

अटल पूर्णांक io_subchannel_settle(व्योम)
अणु
	पूर्णांक ret;

	ret = रुको_event_पूर्णांकerruptible(ccw_device_init_wq,
				atomic_पढ़ो(&ccw_device_init_count) == 0);
	अगर (ret)
		वापस -EINTR;
	flush_workqueue(cio_work_q);
	वापस 0;
पूर्ण

अटल काष्ठा css_driver io_subchannel_driver = अणु
	.drv = अणु
		.owner = THIS_MODULE,
		.name = "io_subchannel",
	पूर्ण,
	.subchannel_type = io_subchannel_ids,
	.irq = io_subchannel_irq,
	.sch_event = io_subchannel_sch_event,
	.chp_event = io_subchannel_chp_event,
	.probe = io_subchannel_probe,
	.हटाओ = io_subchannel_हटाओ,
	.shutकरोwn = io_subchannel_shutकरोwn,
	.settle = io_subchannel_settle,
पूर्ण;

पूर्णांक __init io_subchannel_init(व्योम)
अणु
	पूर्णांक ret;

	समयr_setup(&recovery_समयr, recovery_func, 0);
	ret = bus_रेजिस्टर(&ccw_bus_type);
	अगर (ret)
		वापस ret;
	ret = css_driver_रेजिस्टर(&io_subchannel_driver);
	अगर (ret)
		bus_unरेजिस्टर(&ccw_bus_type);

	वापस ret;
पूर्ण


/************************ device handling **************************/

अटल sमाप_प्रकार
devtype_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_device_id *id = &(cdev->id);

	अगर (id->dev_type != 0)
		वापस प्र_लिखो(buf, "%04x/%02x\n",
				id->dev_type, id->dev_model);
	अन्यथा
		वापस प्र_लिखो(buf, "n/a\n");
पूर्ण

अटल sमाप_प्रकार
cutype_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_device_id *id = &(cdev->id);

	वापस प्र_लिखो(buf, "%04x/%02x\n",
		       id->cu_type, id->cu_model);
पूर्ण

अटल sमाप_प्रकार
modalias_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_device_id *id = &(cdev->id);
	पूर्णांक len;

	len = snprपूर्णांक_alias(buf, PAGE_SIZE, id, "\n");

	वापस len > PAGE_SIZE ? PAGE_SIZE : len;
पूर्ण

अटल sमाप_प्रकार
online_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);

	वापस प्र_लिखो(buf, cdev->online ? "1\n" : "0\n");
पूर्ण

पूर्णांक ccw_device_is_orphan(काष्ठा ccw_device *cdev)
अणु
	वापस sch_is_pseuकरो_sch(to_subchannel(cdev->dev.parent));
पूर्ण

अटल व्योम ccw_device_unरेजिस्टर(काष्ठा ccw_device *cdev)
अणु
	अगर (device_is_रेजिस्टरed(&cdev->dev)) अणु
		/* Unकरो device_add(). */
		device_del(&cdev->dev);
	पूर्ण
	अगर (cdev->निजी->flags.initialized) अणु
		cdev->निजी->flags.initialized = 0;
		/* Release reference from device_initialize(). */
		put_device(&cdev->dev);
	पूर्ण
पूर्ण

अटल व्योम io_subchannel_quiesce(काष्ठा subchannel *);

/**
 * ccw_device_set_offline() - disable a ccw device क्रम I/O
 * @cdev: target ccw device
 *
 * This function calls the driver's set_offline() function क्रम @cdev, अगर
 * given, and then disables @cdev.
 * Returns:
 *   %0 on success and a negative error value on failure.
 * Context:
 *  enabled, ccw device lock not held
 */
पूर्णांक ccw_device_set_offline(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret, state;

	अगर (!cdev)
		वापस -ENODEV;
	अगर (!cdev->online || !cdev->drv)
		वापस -EINVAL;

	अगर (cdev->drv->set_offline) अणु
		ret = cdev->drv->set_offline(cdev);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	spin_lock_irq(cdev->ccwlock);
	sch = to_subchannel(cdev->dev.parent);
	cdev->online = 0;
	/* Wait until a final state or DISCONNECTED is reached */
	जबतक (!dev_fsm_final_state(cdev) &&
	       cdev->निजी->state != DEV_STATE_DISCONNECTED) अणु
		spin_unlock_irq(cdev->ccwlock);
		रुको_event(cdev->निजी->रुको_q, (dev_fsm_final_state(cdev) ||
			   cdev->निजी->state == DEV_STATE_DISCONNECTED));
		spin_lock_irq(cdev->ccwlock);
	पूर्ण
	करो अणु
		ret = ccw_device_offline(cdev);
		अगर (!ret)
			अवरोध;
		CIO_MSG_EVENT(0, "ccw_device_offline returned %d, device "
			      "0.%x.%04x\n", ret, cdev->निजी->dev_id.ssid,
			      cdev->निजी->dev_id.devno);
		अगर (ret != -EBUSY)
			जाओ error;
		state = cdev->निजी->state;
		spin_unlock_irq(cdev->ccwlock);
		io_subchannel_quiesce(sch);
		spin_lock_irq(cdev->ccwlock);
		cdev->निजी->state = state;
	पूर्ण जबतक (ret == -EBUSY);
	spin_unlock_irq(cdev->ccwlock);
	रुको_event(cdev->निजी->रुको_q, (dev_fsm_final_state(cdev) ||
		   cdev->निजी->state == DEV_STATE_DISCONNECTED));
	/* Inक्रमm the user अगर set offline failed. */
	अगर (cdev->निजी->state == DEV_STATE_BOXED) अणु
		pr_warn("%s: The device entered boxed state while being set offline\n",
			dev_name(&cdev->dev));
	पूर्ण अन्यथा अगर (cdev->निजी->state == DEV_STATE_NOT_OPER) अणु
		pr_warn("%s: The device stopped operating while being set offline\n",
			dev_name(&cdev->dev));
	पूर्ण
	/* Give up reference from ccw_device_set_online(). */
	put_device(&cdev->dev);
	वापस 0;

error:
	cdev->निजी->state = DEV_STATE_OFFLINE;
	dev_fsm_event(cdev, DEV_EVENT_NOTOPER);
	spin_unlock_irq(cdev->ccwlock);
	/* Give up reference from ccw_device_set_online(). */
	put_device(&cdev->dev);
	वापस -ENODEV;
पूर्ण

/**
 * ccw_device_set_online() - enable a ccw device क्रम I/O
 * @cdev: target ccw device
 *
 * This function first enables @cdev and then calls the driver's set_online()
 * function क्रम @cdev, अगर given. If set_online() वापसs an error, @cdev is
 * disabled again.
 * Returns:
 *   %0 on success and a negative error value on failure.
 * Context:
 *  enabled, ccw device lock not held
 */
पूर्णांक ccw_device_set_online(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret;
	पूर्णांक ret2;

	अगर (!cdev)
		वापस -ENODEV;
	अगर (cdev->online || !cdev->drv)
		वापस -EINVAL;
	/* Hold on to an extra reference जबतक device is online. */
	अगर (!get_device(&cdev->dev))
		वापस -ENODEV;

	spin_lock_irq(cdev->ccwlock);
	ret = ccw_device_online(cdev);
	spin_unlock_irq(cdev->ccwlock);
	अगर (ret == 0)
		रुको_event(cdev->निजी->रुको_q, dev_fsm_final_state(cdev));
	अन्यथा अणु
		CIO_MSG_EVENT(0, "ccw_device_online returned %d, "
			      "device 0.%x.%04x\n",
			      ret, cdev->निजी->dev_id.ssid,
			      cdev->निजी->dev_id.devno);
		/* Give up online reference since onlining failed. */
		put_device(&cdev->dev);
		वापस ret;
	पूर्ण
	spin_lock_irq(cdev->ccwlock);
	/* Check अगर online processing was successful */
	अगर ((cdev->निजी->state != DEV_STATE_ONLINE) &&
	    (cdev->निजी->state != DEV_STATE_W4SENSE)) अणु
		spin_unlock_irq(cdev->ccwlock);
		/* Inक्रमm the user that set online failed. */
		अगर (cdev->निजी->state == DEV_STATE_BOXED) अणु
			pr_warn("%s: Setting the device online failed because it is boxed\n",
				dev_name(&cdev->dev));
		पूर्ण अन्यथा अगर (cdev->निजी->state == DEV_STATE_NOT_OPER) अणु
			pr_warn("%s: Setting the device online failed because it is not operational\n",
				dev_name(&cdev->dev));
		पूर्ण
		/* Give up online reference since onlining failed. */
		put_device(&cdev->dev);
		वापस -ENODEV;
	पूर्ण
	spin_unlock_irq(cdev->ccwlock);
	अगर (cdev->drv->set_online)
		ret = cdev->drv->set_online(cdev);
	अगर (ret)
		जाओ rollback;

	spin_lock_irq(cdev->ccwlock);
	cdev->online = 1;
	spin_unlock_irq(cdev->ccwlock);
	वापस 0;

rollback:
	spin_lock_irq(cdev->ccwlock);
	/* Wait until a final state or DISCONNECTED is reached */
	जबतक (!dev_fsm_final_state(cdev) &&
	       cdev->निजी->state != DEV_STATE_DISCONNECTED) अणु
		spin_unlock_irq(cdev->ccwlock);
		रुको_event(cdev->निजी->रुको_q, (dev_fsm_final_state(cdev) ||
			   cdev->निजी->state == DEV_STATE_DISCONNECTED));
		spin_lock_irq(cdev->ccwlock);
	पूर्ण
	ret2 = ccw_device_offline(cdev);
	अगर (ret2)
		जाओ error;
	spin_unlock_irq(cdev->ccwlock);
	रुको_event(cdev->निजी->रुको_q, (dev_fsm_final_state(cdev) ||
		   cdev->निजी->state == DEV_STATE_DISCONNECTED));
	/* Give up online reference since onlining failed. */
	put_device(&cdev->dev);
	वापस ret;

error:
	CIO_MSG_EVENT(0, "rollback ccw_device_offline returned %d, "
		      "device 0.%x.%04x\n",
		      ret2, cdev->निजी->dev_id.ssid,
		      cdev->निजी->dev_id.devno);
	cdev->निजी->state = DEV_STATE_OFFLINE;
	spin_unlock_irq(cdev->ccwlock);
	/* Give up online reference since onlining failed. */
	put_device(&cdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक online_store_handle_offline(काष्ठा ccw_device *cdev)
अणु
	अगर (cdev->निजी->state == DEV_STATE_DISCONNECTED) अणु
		spin_lock_irq(cdev->ccwlock);
		ccw_device_sched_toकरो(cdev, CDEV_TODO_UNREG_EVAL);
		spin_unlock_irq(cdev->ccwlock);
		वापस 0;
	पूर्ण
	अगर (cdev->drv && cdev->drv->set_offline)
		वापस ccw_device_set_offline(cdev);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक online_store_recog_and_online(काष्ठा ccw_device *cdev)
अणु
	/* Do device recognition, अगर needed. */
	अगर (cdev->निजी->state == DEV_STATE_BOXED) अणु
		spin_lock_irq(cdev->ccwlock);
		ccw_device_recognition(cdev);
		spin_unlock_irq(cdev->ccwlock);
		रुको_event(cdev->निजी->रुको_q,
			   cdev->निजी->flags.recog_करोne);
		अगर (cdev->निजी->state != DEV_STATE_OFFLINE)
			/* recognition failed */
			वापस -EAGAIN;
	पूर्ण
	अगर (cdev->drv && cdev->drv->set_online)
		वापस ccw_device_set_online(cdev);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक online_store_handle_online(काष्ठा ccw_device *cdev, पूर्णांक क्रमce)
अणु
	पूर्णांक ret;

	ret = online_store_recog_and_online(cdev);
	अगर (ret && !क्रमce)
		वापस ret;
	अगर (क्रमce && cdev->निजी->state == DEV_STATE_BOXED) अणु
		ret = ccw_device_stlck(cdev);
		अगर (ret)
			वापस ret;
		अगर (cdev->id.cu_type == 0)
			cdev->निजी->state = DEV_STATE_NOT_OPER;
		ret = online_store_recog_and_online(cdev);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार online_store (काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	पूर्णांक क्रमce, ret;
	अचिन्हित दीर्घ i;

	/* Prevent conflict between multiple on-/offline processing requests. */
	अगर (atomic_cmpxchg(&cdev->निजी->onoff, 0, 1) != 0)
		वापस -EAGAIN;
	/* Prevent conflict between पूर्णांकernal I/Os and on-/offline processing. */
	अगर (!dev_fsm_final_state(cdev) &&
	    cdev->निजी->state != DEV_STATE_DISCONNECTED) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	/* Prevent conflict between pending work and on-/offline processing.*/
	अगर (work_pending(&cdev->निजी->toकरो_work)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	अगर (!म_भेदन(buf, "force\n", count)) अणु
		क्रमce = 1;
		i = 1;
		ret = 0;
	पूर्ण अन्यथा अणु
		क्रमce = 0;
		ret = kम_से_अदीर्घ(buf, 16, &i);
	पूर्ण
	अगर (ret)
		जाओ out;

	device_lock(dev);
	चयन (i) अणु
	हाल 0:
		ret = online_store_handle_offline(cdev);
		अवरोध;
	हाल 1:
		ret = online_store_handle_online(cdev, क्रमce);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	device_unlock(dev);

out:
	atomic_set(&cdev->निजी->onoff, 0);
	वापस (ret < 0) ? ret : count;
पूर्ण

अटल sमाप_प्रकार
available_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा subchannel *sch;

	अगर (ccw_device_is_orphan(cdev))
		वापस प्र_लिखो(buf, "no device\n");
	चयन (cdev->निजी->state) अणु
	हाल DEV_STATE_BOXED:
		वापस प्र_लिखो(buf, "boxed\n");
	हाल DEV_STATE_DISCONNECTED:
	हाल DEV_STATE_DISCONNECTED_SENSE_ID:
	हाल DEV_STATE_NOT_OPER:
		sch = to_subchannel(dev->parent);
		अगर (!sch->lpm)
			वापस प्र_लिखो(buf, "no path\n");
		अन्यथा
			वापस प्र_लिखो(buf, "no device\n");
	शेष:
		/* All other states considered fine. */
		वापस प्र_लिखो(buf, "good\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
initiate_logging(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);
	पूर्णांक rc;

	rc = chsc_siosl(sch->schid);
	अगर (rc < 0) अणु
		pr_warn("Logging for subchannel 0.%x.%04x failed with errno=%d\n",
			sch->schid.ssid, sch->schid.sch_no, rc);
		वापस rc;
	पूर्ण
	pr_notice("Logging for subchannel 0.%x.%04x was triggered\n",
		  sch->schid.ssid, sch->schid.sch_no);
	वापस count;
पूर्ण

अटल sमाप_प्रकार vpm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा subchannel *sch = to_subchannel(dev);

	वापस प्र_लिखो(buf, "%02x\n", sch->vpm);
पूर्ण

अटल DEVICE_ATTR_RO(devtype);
अटल DEVICE_ATTR_RO(cutype);
अटल DEVICE_ATTR_RO(modalias);
अटल DEVICE_ATTR_RW(online);
अटल DEVICE_ATTR(availability, 0444, available_show, शून्य);
अटल DEVICE_ATTR(logging, 0200, शून्य, initiate_logging);
अटल DEVICE_ATTR_RO(vpm);

अटल काष्ठा attribute *io_subchannel_attrs[] = अणु
	&dev_attr_logging.attr,
	&dev_attr_vpm.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group io_subchannel_attr_group = अणु
	.attrs = io_subchannel_attrs,
पूर्ण;

अटल काष्ठा attribute * ccwdev_attrs[] = अणु
	&dev_attr_devtype.attr,
	&dev_attr_cutype.attr,
	&dev_attr_modalias.attr,
	&dev_attr_online.attr,
	&dev_attr_cmb_enable.attr,
	&dev_attr_availability.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ccwdev_attr_group = अणु
	.attrs = ccwdev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ccwdev_attr_groups[] = अणु
	&ccwdev_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक match_dev_id(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_dev_id *dev_id = (व्योम *)data;

	वापस ccw_dev_id_is_equal(&cdev->निजी->dev_id, dev_id);
पूर्ण

/**
 * get_ccwdev_by_dev_id() - obtain device from a ccw device id
 * @dev_id: id of the device to be searched
 *
 * This function searches all devices attached to the ccw bus क्रम a device
 * matching @dev_id.
 * Returns:
 *  If a device is found its reference count is increased and वापसed;
 *  अन्यथा %शून्य is वापसed.
 */
काष्ठा ccw_device *get_ccwdev_by_dev_id(काष्ठा ccw_dev_id *dev_id)
अणु
	काष्ठा device *dev;

	dev = bus_find_device(&ccw_bus_type, शून्य, dev_id, match_dev_id);

	वापस dev ? to_ccwdev(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(get_ccwdev_by_dev_id);

अटल व्योम ccw_device_करो_unbind_bind(काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret;

	अगर (device_is_रेजिस्टरed(&cdev->dev)) अणु
		device_release_driver(&cdev->dev);
		ret = device_attach(&cdev->dev);
		WARN_ON(ret == -ENODEV);
	पूर्ण
पूर्ण

अटल व्योम
ccw_device_release(काष्ठा device *dev)
अणु
	काष्ठा ccw_device *cdev;

	cdev = to_ccwdev(dev);
	cio_gp_dma_मुक्त(cdev->निजी->dma_pool, cdev->निजी->dma_area,
			माप(*cdev->निजी->dma_area));
	cio_gp_dma_destroy(cdev->निजी->dma_pool, &cdev->dev);
	/* Release reference of parent subchannel. */
	put_device(cdev->dev.parent);
	kमुक्त(cdev->निजी);
	kमुक्त(cdev);
पूर्ण

अटल काष्ठा ccw_device * io_subchannel_allocate_dev(काष्ठा subchannel *sch)
अणु
	काष्ठा ccw_device *cdev;
	काष्ठा gen_pool *dma_pool;
	पूर्णांक ret;

	cdev  = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev) अणु
		ret = -ENOMEM;
		जाओ err_cdev;
	पूर्ण
	cdev->निजी = kzalloc(माप(काष्ठा ccw_device_निजी),
				GFP_KERNEL | GFP_DMA);
	अगर (!cdev->निजी) अणु
		ret = -ENOMEM;
		जाओ err_priv;
	पूर्ण

	cdev->dev.dma_mask = sch->dev.dma_mask;
	ret = dma_set_coherent_mask(&cdev->dev, sch->dev.coherent_dma_mask);
	अगर (ret)
		जाओ err_coherent_mask;

	dma_pool = cio_gp_dma_create(&cdev->dev, 1);
	अगर (!dma_pool) अणु
		ret = -ENOMEM;
		जाओ err_dma_pool;
	पूर्ण
	cdev->निजी->dma_pool = dma_pool;
	cdev->निजी->dma_area = cio_gp_dma_zalloc(dma_pool, &cdev->dev,
					माप(*cdev->निजी->dma_area));
	अगर (!cdev->निजी->dma_area) अणु
		ret = -ENOMEM;
		जाओ err_dma_area;
	पूर्ण
	वापस cdev;
err_dma_area:
	cio_gp_dma_destroy(dma_pool, &cdev->dev);
err_dma_pool:
err_coherent_mask:
	kमुक्त(cdev->निजी);
err_priv:
	kमुक्त(cdev);
err_cdev:
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम ccw_device_toकरो(काष्ठा work_काष्ठा *work);

अटल पूर्णांक io_subchannel_initialize_dev(काष्ठा subchannel *sch,
					काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_device_निजी *priv = cdev->निजी;
	पूर्णांक ret;

	priv->cdev = cdev;
	priv->पूर्णांक_class = IRQIO_CIO;
	priv->state = DEV_STATE_NOT_OPER;
	priv->dev_id.devno = sch->schib.pmcw.dev;
	priv->dev_id.ssid = sch->schid.ssid;

	INIT_WORK(&priv->toकरो_work, ccw_device_toकरो);
	INIT_LIST_HEAD(&priv->cmb_list);
	init_रुकोqueue_head(&priv->रुको_q);
	समयr_setup(&priv->समयr, ccw_device_समयout, 0);

	atomic_set(&priv->onoff, 0);
	cdev->ccwlock = sch->lock;
	cdev->dev.parent = &sch->dev;
	cdev->dev.release = ccw_device_release;
	cdev->dev.bus = &ccw_bus_type;
	cdev->dev.groups = ccwdev_attr_groups;
	/* Do first half of device_रेजिस्टर. */
	device_initialize(&cdev->dev);
	ret = dev_set_name(&cdev->dev, "0.%x.%04x", cdev->निजी->dev_id.ssid,
			   cdev->निजी->dev_id.devno);
	अगर (ret)
		जाओ out_put;
	अगर (!get_device(&sch->dev)) अणु
		ret = -ENODEV;
		जाओ out_put;
	पूर्ण
	priv->flags.initialized = 1;
	spin_lock_irq(sch->lock);
	sch_set_cdev(sch, cdev);
	spin_unlock_irq(sch->lock);
	वापस 0;

out_put:
	/* Release reference from device_initialize(). */
	put_device(&cdev->dev);
	वापस ret;
पूर्ण

अटल काष्ठा ccw_device * io_subchannel_create_ccwdev(काष्ठा subchannel *sch)
अणु
	काष्ठा ccw_device *cdev;
	पूर्णांक ret;

	cdev = io_subchannel_allocate_dev(sch);
	अगर (!IS_ERR(cdev)) अणु
		ret = io_subchannel_initialize_dev(sch, cdev);
		अगर (ret)
			cdev = ERR_PTR(ret);
	पूर्ण
	वापस cdev;
पूर्ण

अटल व्योम io_subchannel_recog(काष्ठा ccw_device *, काष्ठा subchannel *);

अटल व्योम sch_create_and_recog_new_device(काष्ठा subchannel *sch)
अणु
	काष्ठा ccw_device *cdev;

	/* Need to allocate a new ccw device. */
	cdev = io_subchannel_create_ccwdev(sch);
	अगर (IS_ERR(cdev)) अणु
		/* OK, we did everything we could... */
		css_sch_device_unरेजिस्टर(sch);
		वापस;
	पूर्ण
	/* Start recognition क्रम the new ccw device. */
	io_subchannel_recog(cdev, sch);
पूर्ण

/*
 * Register recognized device.
 */
अटल व्योम io_subchannel_रेजिस्टर(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret, adjust_init_count = 1;
	अचिन्हित दीर्घ flags;

	sch = to_subchannel(cdev->dev.parent);
	/*
	 * Check अगर subchannel is still रेजिस्टरed. It may have become
	 * unरेजिस्टरed अगर a machine check hit us after finishing
	 * device recognition but beक्रमe the रेजिस्टर work could be
	 * queued.
	 */
	अगर (!device_is_रेजिस्टरed(&sch->dev))
		जाओ out_err;
	css_update_ssd_info(sch);
	/*
	 * io_subchannel_रेजिस्टर() will also be called after device
	 * recognition has been करोne क्रम a boxed device (which will alपढ़ोy
	 * be रेजिस्टरed). We need to reprobe since we may now have sense id
	 * inक्रमmation.
	 */
	अगर (device_is_रेजिस्टरed(&cdev->dev)) अणु
		अगर (!cdev->drv) अणु
			ret = device_reprobe(&cdev->dev);
			अगर (ret)
				/* We can't करो much here. */
				CIO_MSG_EVENT(0, "device_reprobe() returned"
					      " %d for 0.%x.%04x\n", ret,
					      cdev->निजी->dev_id.ssid,
					      cdev->निजी->dev_id.devno);
		पूर्ण
		adjust_init_count = 0;
		जाओ out;
	पूर्ण
	/*
	 * Now we know this subchannel will stay, we can throw
	 * our delayed uevent.
	 */
	अगर (dev_get_uevent_suppress(&sch->dev)) अणु
		dev_set_uevent_suppress(&sch->dev, 0);
		kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
	पूर्ण
	/* make it known to the प्रणाली */
	ret = device_add(&cdev->dev);
	अगर (ret) अणु
		CIO_MSG_EVENT(0, "Could not register ccw dev 0.%x.%04x: %d\n",
			      cdev->निजी->dev_id.ssid,
			      cdev->निजी->dev_id.devno, ret);
		spin_lock_irqsave(sch->lock, flags);
		sch_set_cdev(sch, शून्य);
		spin_unlock_irqrestore(sch->lock, flags);
		/* Release initial device reference. */
		put_device(&cdev->dev);
		जाओ out_err;
	पूर्ण
out:
	cdev->निजी->flags.recog_करोne = 1;
	wake_up(&cdev->निजी->रुको_q);
out_err:
	अगर (adjust_init_count && atomic_dec_and_test(&ccw_device_init_count))
		wake_up(&ccw_device_init_wq);
पूर्ण

अटल व्योम ccw_device_call_sch_unरेजिस्टर(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;

	/* Get subchannel reference क्रम local processing. */
	अगर (!get_device(cdev->dev.parent))
		वापस;
	sch = to_subchannel(cdev->dev.parent);
	css_sch_device_unरेजिस्टर(sch);
	/* Release subchannel reference क्रम local processing. */
	put_device(&sch->dev);
पूर्ण

/*
 * subchannel recognition करोne. Called from the state machine.
 */
व्योम
io_subchannel_recog_करोne(काष्ठा ccw_device *cdev)
अणु
	अगर (css_init_करोne == 0) अणु
		cdev->निजी->flags.recog_करोne = 1;
		वापस;
	पूर्ण
	चयन (cdev->निजी->state) अणु
	हाल DEV_STATE_BOXED:
		/* Device did not respond in समय. */
	हाल DEV_STATE_NOT_OPER:
		cdev->निजी->flags.recog_करोne = 1;
		/* Remove device found not operational. */
		ccw_device_sched_toकरो(cdev, CDEV_TODO_UNREG);
		अगर (atomic_dec_and_test(&ccw_device_init_count))
			wake_up(&ccw_device_init_wq);
		अवरोध;
	हाल DEV_STATE_OFFLINE:
		/*
		 * We can't रेजिस्टर the device in पूर्णांकerrupt context so
		 * we schedule a work item.
		 */
		ccw_device_sched_toकरो(cdev, CDEV_TODO_REGISTER);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम io_subchannel_recog(काष्ठा ccw_device *cdev, काष्ठा subchannel *sch)
अणु
	/* Increase counter of devices currently in recognition. */
	atomic_inc(&ccw_device_init_count);

	/* Start async. device sensing. */
	spin_lock_irq(sch->lock);
	ccw_device_recognition(cdev);
	spin_unlock_irq(sch->lock);
पूर्ण

अटल पूर्णांक ccw_device_move_to_sch(काष्ठा ccw_device *cdev,
				  काष्ठा subchannel *sch)
अणु
	काष्ठा subchannel *old_sch;
	पूर्णांक rc, old_enabled = 0;

	old_sch = to_subchannel(cdev->dev.parent);
	/* Obtain child reference क्रम new parent. */
	अगर (!get_device(&sch->dev))
		वापस -ENODEV;

	अगर (!sch_is_pseuकरो_sch(old_sch)) अणु
		spin_lock_irq(old_sch->lock);
		old_enabled = old_sch->schib.pmcw.ena;
		rc = 0;
		अगर (old_enabled)
			rc = cio_disable_subchannel(old_sch);
		spin_unlock_irq(old_sch->lock);
		अगर (rc == -EBUSY) अणु
			/* Release child reference क्रम new parent. */
			put_device(&sch->dev);
			वापस rc;
		पूर्ण
	पूर्ण

	mutex_lock(&sch->reg_mutex);
	rc = device_move(&cdev->dev, &sch->dev, DPM_ORDER_PARENT_BEFORE_DEV);
	mutex_unlock(&sch->reg_mutex);
	अगर (rc) अणु
		CIO_MSG_EVENT(0, "device_move(0.%x.%04x,0.%x.%04x)=%d\n",
			      cdev->निजी->dev_id.ssid,
			      cdev->निजी->dev_id.devno, sch->schid.ssid,
			      sch->schib.pmcw.dev, rc);
		अगर (old_enabled) अणु
			/* Try to reenable the old subchannel. */
			spin_lock_irq(old_sch->lock);
			cio_enable_subchannel(old_sch, (u32)(addr_t)old_sch);
			spin_unlock_irq(old_sch->lock);
		पूर्ण
		/* Release child reference क्रम new parent. */
		put_device(&sch->dev);
		वापस rc;
	पूर्ण
	/* Clean up old subchannel. */
	अगर (!sch_is_pseuकरो_sch(old_sch)) अणु
		spin_lock_irq(old_sch->lock);
		sch_set_cdev(old_sch, शून्य);
		spin_unlock_irq(old_sch->lock);
		css_schedule_eval(old_sch->schid);
	पूर्ण
	/* Release child reference क्रम old parent. */
	put_device(&old_sch->dev);
	/* Initialize new subchannel. */
	spin_lock_irq(sch->lock);
	cdev->ccwlock = sch->lock;
	अगर (!sch_is_pseuकरो_sch(sch))
		sch_set_cdev(sch, cdev);
	spin_unlock_irq(sch->lock);
	अगर (!sch_is_pseuकरो_sch(sch))
		css_update_ssd_info(sch);
	वापस 0;
पूर्ण

अटल पूर्णांक ccw_device_move_to_orph(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा channel_subप्रणाली *css = to_css(sch->dev.parent);

	वापस ccw_device_move_to_sch(cdev, css->pseuकरो_subchannel);
पूर्ण

अटल व्योम io_subchannel_irq(काष्ठा subchannel *sch)
अणु
	काष्ठा ccw_device *cdev;

	cdev = sch_get_cdev(sch);

	CIO_TRACE_EVENT(6, "IRQ");
	CIO_TRACE_EVENT(6, dev_name(&sch->dev));
	अगर (cdev)
		dev_fsm_event(cdev, DEV_EVENT_INTERRUPT);
	अन्यथा
		inc_irq_stat(IRQIO_CIO);
पूर्ण

व्योम io_subchannel_init_config(काष्ठा subchannel *sch)
अणु
	स_रखो(&sch->config, 0, माप(sch->config));
	sch->config.csense = 1;
पूर्ण

अटल व्योम io_subchannel_init_fields(काष्ठा subchannel *sch)
अणु
	अगर (cio_is_console(sch->schid))
		sch->opm = 0xff;
	अन्यथा
		sch->opm = chp_get_sch_opm(sch);
	sch->lpm = sch->schib.pmcw.pam & sch->opm;
	sch->isc = cio_is_console(sch->schid) ? CONSOLE_ISC : IO_SCH_ISC;

	CIO_MSG_EVENT(6, "Detected device %04x on subchannel 0.%x.%04X"
		      " - PIM = %02X, PAM = %02X, POM = %02X\n",
		      sch->schib.pmcw.dev, sch->schid.ssid,
		      sch->schid.sch_no, sch->schib.pmcw.pim,
		      sch->schib.pmcw.pam, sch->schib.pmcw.pom);

	io_subchannel_init_config(sch);
पूर्ण

/*
 * Note: We always वापस 0 so that we bind to the device even on error.
 * This is needed so that our हटाओ function is called on unरेजिस्टर.
 */
अटल पूर्णांक io_subchannel_probe(काष्ठा subchannel *sch)
अणु
	काष्ठा io_subchannel_निजी *io_priv;
	काष्ठा ccw_device *cdev;
	पूर्णांक rc;

	अगर (cio_is_console(sch->schid)) अणु
		rc = sysfs_create_group(&sch->dev.kobj,
					&io_subchannel_attr_group);
		अगर (rc)
			CIO_MSG_EVENT(0, "Failed to create io subchannel "
				      "attributes for subchannel "
				      "0.%x.%04x (rc=%d)\n",
				      sch->schid.ssid, sch->schid.sch_no, rc);
		/*
		 * The console subchannel alपढ़ोy has an associated ccw_device.
		 * Throw the delayed uevent क्रम the subchannel, रेजिस्टर
		 * the ccw_device and निकास.
		 */
		अगर (dev_get_uevent_suppress(&sch->dev)) अणु
			/* should always be the हाल क्रम the console */
			dev_set_uevent_suppress(&sch->dev, 0);
			kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
		पूर्ण
		cdev = sch_get_cdev(sch);
		rc = device_add(&cdev->dev);
		अगर (rc) अणु
			/* Release online reference. */
			put_device(&cdev->dev);
			जाओ out_schedule;
		पूर्ण
		अगर (atomic_dec_and_test(&ccw_device_init_count))
			wake_up(&ccw_device_init_wq);
		वापस 0;
	पूर्ण
	io_subchannel_init_fields(sch);
	rc = cio_commit_config(sch);
	अगर (rc)
		जाओ out_schedule;
	rc = sysfs_create_group(&sch->dev.kobj,
				&io_subchannel_attr_group);
	अगर (rc)
		जाओ out_schedule;
	/* Allocate I/O subchannel निजी data. */
	io_priv = kzalloc(माप(*io_priv), GFP_KERNEL | GFP_DMA);
	अगर (!io_priv)
		जाओ out_schedule;

	io_priv->dma_area = dma_alloc_coherent(&sch->dev,
				माप(*io_priv->dma_area),
				&io_priv->dma_area_dma, GFP_KERNEL);
	अगर (!io_priv->dma_area) अणु
		kमुक्त(io_priv);
		जाओ out_schedule;
	पूर्ण

	set_io_निजी(sch, io_priv);
	css_schedule_eval(sch->schid);
	वापस 0;

out_schedule:
	spin_lock_irq(sch->lock);
	css_sched_sch_toकरो(sch, SCH_TODO_UNREG);
	spin_unlock_irq(sch->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक io_subchannel_हटाओ(काष्ठा subchannel *sch)
अणु
	काष्ठा io_subchannel_निजी *io_priv = to_io_निजी(sch);
	काष्ठा ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	अगर (!cdev)
		जाओ out_मुक्त;

	ccw_device_unरेजिस्टर(cdev);
	spin_lock_irq(sch->lock);
	sch_set_cdev(sch, शून्य);
	set_io_निजी(sch, शून्य);
	spin_unlock_irq(sch->lock);
out_मुक्त:
	dma_मुक्त_coherent(&sch->dev, माप(*io_priv->dma_area),
			  io_priv->dma_area, io_priv->dma_area_dma);
	kमुक्त(io_priv);
	sysfs_हटाओ_group(&sch->dev.kobj, &io_subchannel_attr_group);
	वापस 0;
पूर्ण

अटल व्योम io_subchannel_verअगरy(काष्ठा subchannel *sch)
अणु
	काष्ठा ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	अगर (cdev)
		dev_fsm_event(cdev, DEV_EVENT_VERIFY);
पूर्ण

अटल व्योम io_subchannel_terminate_path(काष्ठा subchannel *sch, u8 mask)
अणु
	काष्ठा ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	अगर (!cdev)
		वापस;
	अगर (cio_update_schib(sch))
		जाओ err;
	/* Check क्रम I/O on path. */
	अगर (scsw_actl(&sch->schib.scsw) == 0 || sch->schib.pmcw.lpum != mask)
		जाओ out;
	अगर (cdev->निजी->state == DEV_STATE_ONLINE) अणु
		ccw_device_समाप्त_io(cdev);
		जाओ out;
	पूर्ण
	अगर (cio_clear(sch))
		जाओ err;
out:
	/* Trigger path verअगरication. */
	dev_fsm_event(cdev, DEV_EVENT_VERIFY);
	वापस;

err:
	dev_fsm_event(cdev, DEV_EVENT_NOTOPER);
पूर्ण

अटल पूर्णांक io_subchannel_chp_event(काष्ठा subchannel *sch,
				   काष्ठा chp_link *link, पूर्णांक event)
अणु
	काष्ठा ccw_device *cdev = sch_get_cdev(sch);
	पूर्णांक mask, chpid, valid_bit;
	पूर्णांक path_event[8];

	mask = chp_ssd_get_mask(&sch->ssd_info, link);
	अगर (!mask)
		वापस 0;
	चयन (event) अणु
	हाल CHP_VARY_OFF:
		sch->opm &= ~mask;
		sch->lpm &= ~mask;
		अगर (cdev)
			cdev->निजी->path_gone_mask |= mask;
		io_subchannel_terminate_path(sch, mask);
		अवरोध;
	हाल CHP_VARY_ON:
		sch->opm |= mask;
		sch->lpm |= mask;
		अगर (cdev)
			cdev->निजी->path_new_mask |= mask;
		io_subchannel_verअगरy(sch);
		अवरोध;
	हाल CHP_OFFLINE:
		अगर (cio_update_schib(sch))
			वापस -ENODEV;
		अगर (cdev)
			cdev->निजी->path_gone_mask |= mask;
		io_subchannel_terminate_path(sch, mask);
		अवरोध;
	हाल CHP_ONLINE:
		अगर (cio_update_schib(sch))
			वापस -ENODEV;
		sch->lpm |= mask & sch->opm;
		अगर (cdev)
			cdev->निजी->path_new_mask |= mask;
		io_subchannel_verअगरy(sch);
		अवरोध;
	हाल CHP_FCES_EVENT:
		/* Forward Endpoपूर्णांक Security event */
		क्रम (chpid = 0, valid_bit = 0x80; chpid < 8; chpid++,
				valid_bit >>= 1) अणु
			अगर (mask & valid_bit)
				path_event[chpid] = PE_PATH_FCES_EVENT;
			अन्यथा
				path_event[chpid] = PE_NONE;
		पूर्ण
		अगर (cdev)
			cdev->drv->path_event(cdev, path_event);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम io_subchannel_quiesce(काष्ठा subchannel *sch)
अणु
	काष्ठा ccw_device *cdev;
	पूर्णांक ret;

	spin_lock_irq(sch->lock);
	cdev = sch_get_cdev(sch);
	अगर (cio_is_console(sch->schid))
		जाओ out_unlock;
	अगर (!sch->schib.pmcw.ena)
		जाओ out_unlock;
	ret = cio_disable_subchannel(sch);
	अगर (ret != -EBUSY)
		जाओ out_unlock;
	अगर (cdev->handler)
		cdev->handler(cdev, cdev->निजी->पूर्णांकparm, ERR_PTR(-EIO));
	जबतक (ret == -EBUSY) अणु
		cdev->निजी->state = DEV_STATE_QUIESCE;
		cdev->निजी->iretry = 255;
		ret = ccw_device_cancel_halt_clear(cdev);
		अगर (ret == -EBUSY) अणु
			ccw_device_set_समयout(cdev, HZ/10);
			spin_unlock_irq(sch->lock);
			रुको_event(cdev->निजी->रुको_q,
				   cdev->निजी->state != DEV_STATE_QUIESCE);
			spin_lock_irq(sch->lock);
		पूर्ण
		ret = cio_disable_subchannel(sch);
	पूर्ण
out_unlock:
	spin_unlock_irq(sch->lock);
पूर्ण

अटल व्योम io_subchannel_shutकरोwn(काष्ठा subchannel *sch)
अणु
	io_subchannel_quiesce(sch);
पूर्ण

अटल पूर्णांक device_is_disconnected(काष्ठा ccw_device *cdev)
अणु
	अगर (!cdev)
		वापस 0;
	वापस (cdev->निजी->state == DEV_STATE_DISCONNECTED ||
		cdev->निजी->state == DEV_STATE_DISCONNECTED_SENSE_ID);
पूर्ण

अटल पूर्णांक recovery_check(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा subchannel *sch;
	पूर्णांक *reकरो = data;

	spin_lock_irq(cdev->ccwlock);
	चयन (cdev->निजी->state) अणु
	हाल DEV_STATE_ONLINE:
		sch = to_subchannel(cdev->dev.parent);
		अगर ((sch->schib.pmcw.pam & sch->opm) == sch->vpm)
			अवरोध;
		fallthrough;
	हाल DEV_STATE_DISCONNECTED:
		CIO_MSG_EVENT(3, "recovery: trigger 0.%x.%04x\n",
			      cdev->निजी->dev_id.ssid,
			      cdev->निजी->dev_id.devno);
		dev_fsm_event(cdev, DEV_EVENT_VERIFY);
		*reकरो = 1;
		अवरोध;
	हाल DEV_STATE_DISCONNECTED_SENSE_ID:
		*reकरो = 1;
		अवरोध;
	पूर्ण
	spin_unlock_irq(cdev->ccwlock);

	वापस 0;
पूर्ण

अटल व्योम recovery_work_func(काष्ठा work_काष्ठा *unused)
अणु
	पूर्णांक reकरो = 0;

	bus_क्रम_each_dev(&ccw_bus_type, शून्य, &reकरो, recovery_check);
	अगर (reकरो) अणु
		spin_lock_irq(&recovery_lock);
		अगर (!समयr_pending(&recovery_समयr)) अणु
			अगर (recovery_phase < ARRAY_SIZE(recovery_delay) - 1)
				recovery_phase++;
			mod_समयr(&recovery_समयr, jअगरfies +
				  recovery_delay[recovery_phase] * HZ);
		पूर्ण
		spin_unlock_irq(&recovery_lock);
	पूर्ण अन्यथा
		CIO_MSG_EVENT(3, "recovery: end\n");
पूर्ण

अटल DECLARE_WORK(recovery_work, recovery_work_func);

अटल व्योम recovery_func(काष्ठा समयr_list *unused)
अणु
	/*
	 * We can't do our recovery in softirq context and it's not
	 * perक्रमmance critical, so we schedule it.
	 */
	schedule_work(&recovery_work);
पूर्ण

व्योम ccw_device_schedule_recovery(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	CIO_MSG_EVENT(3, "recovery: schedule\n");
	spin_lock_irqsave(&recovery_lock, flags);
	अगर (!समयr_pending(&recovery_समयr) || (recovery_phase != 0)) अणु
		recovery_phase = 0;
		mod_समयr(&recovery_समयr, jअगरfies + recovery_delay[0] * HZ);
	पूर्ण
	spin_unlock_irqrestore(&recovery_lock, flags);
पूर्ण

अटल पूर्णांक purge_fn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_dev_id *id = &cdev->निजी->dev_id;

	spin_lock_irq(cdev->ccwlock);
	अगर (is_blacklisted(id->ssid, id->devno) &&
	    (cdev->निजी->state == DEV_STATE_OFFLINE) &&
	    (atomic_cmpxchg(&cdev->निजी->onoff, 0, 1) == 0)) अणु
		CIO_MSG_EVENT(3, "ccw: purging 0.%x.%04x\n", id->ssid,
			      id->devno);
		ccw_device_sched_toकरो(cdev, CDEV_TODO_UNREG);
		atomic_set(&cdev->निजी->onoff, 0);
	पूर्ण
	spin_unlock_irq(cdev->ccwlock);
	/* Abort loop in हाल of pending संकेत. */
	अगर (संकेत_pending(current))
		वापस -EINTR;

	वापस 0;
पूर्ण

/**
 * ccw_purge_blacklisted - purge unused, blacklisted devices
 *
 * Unरेजिस्टर all ccw devices that are offline and on the blacklist.
 */
पूर्णांक ccw_purge_blacklisted(व्योम)
अणु
	CIO_MSG_EVENT(2, "ccw: purging blacklisted devices\n");
	bus_क्रम_each_dev(&ccw_bus_type, शून्य, शून्य, purge_fn);
	वापस 0;
पूर्ण

व्योम ccw_device_set_disconnected(काष्ठा ccw_device *cdev)
अणु
	अगर (!cdev)
		वापस;
	ccw_device_set_समयout(cdev, 0);
	cdev->निजी->flags.fake_irb = 0;
	cdev->निजी->state = DEV_STATE_DISCONNECTED;
	अगर (cdev->online)
		ccw_device_schedule_recovery();
पूर्ण

व्योम ccw_device_set_notoper(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	CIO_TRACE_EVENT(2, "notoper");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));
	ccw_device_set_समयout(cdev, 0);
	cio_disable_subchannel(sch);
	cdev->निजी->state = DEV_STATE_NOT_OPER;
पूर्ण

क्रमागत io_sch_action अणु
	IO_SCH_UNREG,
	IO_SCH_ORPH_UNREG,
	IO_SCH_ATTACH,
	IO_SCH_UNREG_ATTACH,
	IO_SCH_ORPH_ATTACH,
	IO_SCH_REPROBE,
	IO_SCH_VERIFY,
	IO_SCH_DISC,
	IO_SCH_NOP,
पूर्ण;

अटल क्रमागत io_sch_action sch_get_action(काष्ठा subchannel *sch)
अणु
	काष्ठा ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	अगर (cio_update_schib(sch)) अणु
		/* Not operational. */
		अगर (!cdev)
			वापस IO_SCH_UNREG;
		अगर (ccw_device_notअगरy(cdev, CIO_GONE) != NOTIFY_OK)
			वापस IO_SCH_UNREG;
		वापस IO_SCH_ORPH_UNREG;
	पूर्ण
	/* Operational. */
	अगर (!cdev)
		वापस IO_SCH_ATTACH;
	अगर (sch->schib.pmcw.dev != cdev->निजी->dev_id.devno) अणु
		अगर (ccw_device_notअगरy(cdev, CIO_GONE) != NOTIFY_OK)
			वापस IO_SCH_UNREG_ATTACH;
		वापस IO_SCH_ORPH_ATTACH;
	पूर्ण
	अगर ((sch->schib.pmcw.pam & sch->opm) == 0) अणु
		अगर (ccw_device_notअगरy(cdev, CIO_NO_PATH) != NOTIFY_OK)
			वापस IO_SCH_UNREG;
		वापस IO_SCH_DISC;
	पूर्ण
	अगर (device_is_disconnected(cdev))
		वापस IO_SCH_REPROBE;
	अगर (cdev->online)
		वापस IO_SCH_VERIFY;
	अगर (cdev->निजी->state == DEV_STATE_NOT_OPER)
		वापस IO_SCH_UNREG_ATTACH;
	वापस IO_SCH_NOP;
पूर्ण

/**
 * io_subchannel_sch_event - process subchannel event
 * @sch: subchannel
 * @process: non-zero अगर function is called in process context
 *
 * An unspecअगरied event occurred क्रम this subchannel. Adjust data according
 * to the current operational state of the subchannel and device. Return
 * zero when the event has been handled sufficiently or -EAGAIN when this
 * function should be called again in process context.
 */
अटल पूर्णांक io_subchannel_sch_event(काष्ठा subchannel *sch, पूर्णांक process)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ccw_device *cdev;
	काष्ठा ccw_dev_id dev_id;
	क्रमागत io_sch_action action;
	पूर्णांक rc = -EAGAIN;

	spin_lock_irqsave(sch->lock, flags);
	अगर (!device_is_रेजिस्टरed(&sch->dev))
		जाओ out_unlock;
	अगर (work_pending(&sch->toकरो_work))
		जाओ out_unlock;
	cdev = sch_get_cdev(sch);
	अगर (cdev && work_pending(&cdev->निजी->toकरो_work))
		जाओ out_unlock;
	action = sch_get_action(sch);
	CIO_MSG_EVENT(2, "event: sch 0.%x.%04x, process=%d, action=%d\n",
		      sch->schid.ssid, sch->schid.sch_no, process,
		      action);
	/* Perक्रमm immediate actions जबतक holding the lock. */
	चयन (action) अणु
	हाल IO_SCH_REPROBE:
		/* Trigger device recognition. */
		ccw_device_trigger_reprobe(cdev);
		rc = 0;
		जाओ out_unlock;
	हाल IO_SCH_VERIFY:
		/* Trigger path verअगरication. */
		io_subchannel_verअगरy(sch);
		rc = 0;
		जाओ out_unlock;
	हाल IO_SCH_DISC:
		ccw_device_set_disconnected(cdev);
		rc = 0;
		जाओ out_unlock;
	हाल IO_SCH_ORPH_UNREG:
	हाल IO_SCH_ORPH_ATTACH:
		ccw_device_set_disconnected(cdev);
		अवरोध;
	हाल IO_SCH_UNREG_ATTACH:
	हाल IO_SCH_UNREG:
		अगर (!cdev)
			अवरोध;
		अगर (cdev->निजी->state == DEV_STATE_SENSE_ID) अणु
			/*
			 * Note: delayed work triggered by this event
			 * and repeated calls to sch_event are synchronized
			 * by the above check क्रम work_pending(cdev).
			 */
			dev_fsm_event(cdev, DEV_EVENT_NOTOPER);
		पूर्ण अन्यथा
			ccw_device_set_notoper(cdev);
		अवरोध;
	हाल IO_SCH_NOP:
		rc = 0;
		जाओ out_unlock;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(sch->lock, flags);
	/* All other actions require process context. */
	अगर (!process)
		जाओ out;
	/* Handle attached ccw device. */
	चयन (action) अणु
	हाल IO_SCH_ORPH_UNREG:
	हाल IO_SCH_ORPH_ATTACH:
		/* Move ccw device to orphanage. */
		rc = ccw_device_move_to_orph(cdev);
		अगर (rc)
			जाओ out;
		अवरोध;
	हाल IO_SCH_UNREG_ATTACH:
		spin_lock_irqsave(sch->lock, flags);
		sch_set_cdev(sch, शून्य);
		spin_unlock_irqrestore(sch->lock, flags);
		/* Unरेजिस्टर ccw device. */
		ccw_device_unरेजिस्टर(cdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* Handle subchannel. */
	चयन (action) अणु
	हाल IO_SCH_ORPH_UNREG:
	हाल IO_SCH_UNREG:
		css_sch_device_unरेजिस्टर(sch);
		अवरोध;
	हाल IO_SCH_ORPH_ATTACH:
	हाल IO_SCH_UNREG_ATTACH:
	हाल IO_SCH_ATTACH:
		dev_id.ssid = sch->schid.ssid;
		dev_id.devno = sch->schib.pmcw.dev;
		cdev = get_ccwdev_by_dev_id(&dev_id);
		अगर (!cdev) अणु
			sch_create_and_recog_new_device(sch);
			अवरोध;
		पूर्ण
		rc = ccw_device_move_to_sch(cdev, sch);
		अगर (rc) अणु
			/* Release reference from get_ccwdev_by_dev_id() */
			put_device(&cdev->dev);
			जाओ out;
		पूर्ण
		spin_lock_irqsave(sch->lock, flags);
		ccw_device_trigger_reprobe(cdev);
		spin_unlock_irqrestore(sch->lock, flags);
		/* Release reference from get_ccwdev_by_dev_id() */
		put_device(&cdev->dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;

out_unlock:
	spin_unlock_irqrestore(sch->lock, flags);
out:
	वापस rc;
पूर्ण

अटल व्योम ccw_device_set_पूर्णांक_class(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_driver *cdrv = cdev->drv;

	/* Note: we पूर्णांकerpret class 0 in this context as an uninitialized
	 * field since it translates to a non-I/O पूर्णांकerrupt class. */
	अगर (cdrv->पूर्णांक_class != 0)
		cdev->निजी->पूर्णांक_class = cdrv->पूर्णांक_class;
	अन्यथा
		cdev->निजी->पूर्णांक_class = IRQIO_CIO;
पूर्ण

#अगर_घोषित CONFIG_CCW_CONSOLE
पूर्णांक __init ccw_device_enable_console(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	पूर्णांक rc;

	अगर (!cdev->drv || !cdev->handler)
		वापस -EINVAL;

	io_subchannel_init_fields(sch);
	rc = cio_commit_config(sch);
	अगर (rc)
		वापस rc;
	sch->driver = &io_subchannel_driver;
	io_subchannel_recog(cdev, sch);
	/* Now रुको क्रम the async. recognition to come to an end. */
	spin_lock_irq(cdev->ccwlock);
	जबतक (!dev_fsm_final_state(cdev))
		ccw_device_रुको_idle(cdev);

	/* Hold on to an extra reference जबतक device is online. */
	get_device(&cdev->dev);
	rc = ccw_device_online(cdev);
	अगर (rc)
		जाओ out_unlock;

	जबतक (!dev_fsm_final_state(cdev))
		ccw_device_रुको_idle(cdev);

	अगर (cdev->निजी->state == DEV_STATE_ONLINE)
		cdev->online = 1;
	अन्यथा
		rc = -EIO;
out_unlock:
	spin_unlock_irq(cdev->ccwlock);
	अगर (rc) /* Give up online reference since onlining failed. */
		put_device(&cdev->dev);
	वापस rc;
पूर्ण

काष्ठा ccw_device * __init ccw_device_create_console(काष्ठा ccw_driver *drv)
अणु
	काष्ठा io_subchannel_निजी *io_priv;
	काष्ठा ccw_device *cdev;
	काष्ठा subchannel *sch;

	sch = cio_probe_console();
	अगर (IS_ERR(sch))
		वापस ERR_CAST(sch);

	io_priv = kzalloc(माप(*io_priv), GFP_KERNEL | GFP_DMA);
	अगर (!io_priv)
		जाओ err_priv;
	io_priv->dma_area = dma_alloc_coherent(&sch->dev,
				माप(*io_priv->dma_area),
				&io_priv->dma_area_dma, GFP_KERNEL);
	अगर (!io_priv->dma_area)
		जाओ err_dma_area;
	set_io_निजी(sch, io_priv);
	cdev = io_subchannel_create_ccwdev(sch);
	अगर (IS_ERR(cdev)) अणु
		dma_मुक्त_coherent(&sch->dev, माप(*io_priv->dma_area),
				  io_priv->dma_area, io_priv->dma_area_dma);
		set_io_निजी(sch, शून्य);
		put_device(&sch->dev);
		kमुक्त(io_priv);
		वापस cdev;
	पूर्ण
	cdev->drv = drv;
	ccw_device_set_पूर्णांक_class(cdev);
	वापस cdev;

err_dma_area:
	kमुक्त(io_priv);
err_priv:
	put_device(&sch->dev);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

व्योम __init ccw_device_destroy_console(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा io_subchannel_निजी *io_priv = to_io_निजी(sch);

	set_io_निजी(sch, शून्य);
	dma_मुक्त_coherent(&sch->dev, माप(*io_priv->dma_area),
			  io_priv->dma_area, io_priv->dma_area_dma);
	put_device(&sch->dev);
	put_device(&cdev->dev);
	kमुक्त(io_priv);
पूर्ण

/**
 * ccw_device_रुको_idle() - busy रुको क्रम device to become idle
 * @cdev: ccw device
 *
 * Poll until activity control is zero, that is, no function or data
 * transfer is pending/active.
 * Called with device lock being held.
 */
व्योम ccw_device_रुको_idle(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	जबतक (1) अणु
		cio_tsch(sch);
		अगर (sch->schib.scsw.cmd.actl == 0)
			अवरोध;
		udelay(100);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * get_ccwdev_by_busid() - obtain device from a bus id
 * @cdrv: driver the device is owned by
 * @bus_id: bus id of the device to be searched
 *
 * This function searches all devices owned by @cdrv क्रम a device with a bus
 * id matching @bus_id.
 * Returns:
 *  If a match is found, its reference count of the found device is increased
 *  and it is वापसed; अन्यथा %शून्य is वापसed.
 */
काष्ठा ccw_device *get_ccwdev_by_busid(काष्ठा ccw_driver *cdrv,
				       स्थिर अक्षर *bus_id)
अणु
	काष्ठा device *dev;

	dev = driver_find_device_by_name(&cdrv->driver, bus_id);

	वापस dev ? to_ccwdev(dev) : शून्य;
पूर्ण

/************************** device driver handling ************************/

/* This is the implementation of the ccw_driver class. The probe, हटाओ
 * and release methods are initially very similar to the device_driver
 * implementations, with the dअगरference that they have ccw_device
 * arguments.
 *
 * A ccw driver also contains the inक्रमmation that is needed क्रम
 * device matching.
 */
अटल पूर्णांक
ccw_device_probe (काष्ठा device *dev)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_driver *cdrv = to_ccwdrv(dev->driver);
	पूर्णांक ret;

	cdev->drv = cdrv; /* to let the driver call _set_online */
	ccw_device_set_पूर्णांक_class(cdev);
	ret = cdrv->probe ? cdrv->probe(cdev) : -ENODEV;
	अगर (ret) अणु
		cdev->drv = शून्य;
		cdev->निजी->पूर्णांक_class = IRQIO_CIO;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccw_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा ccw_driver *cdrv = cdev->drv;
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	अगर (cdrv->हटाओ)
		cdrv->हटाओ(cdev);

	spin_lock_irq(cdev->ccwlock);
	अगर (cdev->online) अणु
		cdev->online = 0;
		ret = ccw_device_offline(cdev);
		spin_unlock_irq(cdev->ccwlock);
		अगर (ret == 0)
			रुको_event(cdev->निजी->रुको_q,
				   dev_fsm_final_state(cdev));
		अन्यथा
			CIO_MSG_EVENT(0, "ccw_device_offline returned %d, "
				      "device 0.%x.%04x\n",
				      ret, cdev->निजी->dev_id.ssid,
				      cdev->निजी->dev_id.devno);
		/* Give up reference obtained in ccw_device_set_online(). */
		put_device(&cdev->dev);
		spin_lock_irq(cdev->ccwlock);
	पूर्ण
	ccw_device_set_समयout(cdev, 0);
	cdev->drv = शून्य;
	cdev->निजी->पूर्णांक_class = IRQIO_CIO;
	sch = to_subchannel(cdev->dev.parent);
	spin_unlock_irq(cdev->ccwlock);
	io_subchannel_quiesce(sch);
	__disable_cmf(cdev);

	वापस 0;
पूर्ण

अटल व्योम ccw_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा ccw_device *cdev;

	cdev = to_ccwdev(dev);
	अगर (cdev->drv && cdev->drv->shutकरोwn)
		cdev->drv->shutकरोwn(cdev);
	__disable_cmf(cdev);
पूर्ण

अटल काष्ठा bus_type ccw_bus_type = अणु
	.name   = "ccw",
	.match  = ccw_bus_match,
	.uevent = ccw_uevent,
	.probe  = ccw_device_probe,
	.हटाओ = ccw_device_हटाओ,
	.shutकरोwn = ccw_device_shutकरोwn,
पूर्ण;

/**
 * ccw_driver_रेजिस्टर() - रेजिस्टर a ccw driver
 * @cdriver: driver to be रेजिस्टरed
 *
 * This function is मुख्यly a wrapper around driver_रेजिस्टर().
 * Returns:
 *   %0 on success and a negative error value on failure.
 */
पूर्णांक ccw_driver_रेजिस्टर(काष्ठा ccw_driver *cdriver)
अणु
	काष्ठा device_driver *drv = &cdriver->driver;

	drv->bus = &ccw_bus_type;

	वापस driver_रेजिस्टर(drv);
पूर्ण

/**
 * ccw_driver_unरेजिस्टर() - deरेजिस्टर a ccw driver
 * @cdriver: driver to be deरेजिस्टरed
 *
 * This function is मुख्यly a wrapper around driver_unरेजिस्टर().
 */
व्योम ccw_driver_unरेजिस्टर(काष्ठा ccw_driver *cdriver)
अणु
	driver_unरेजिस्टर(&cdriver->driver);
पूर्ण

अटल व्योम ccw_device_toकरो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ccw_device_निजी *priv;
	काष्ठा ccw_device *cdev;
	काष्ठा subchannel *sch;
	क्रमागत cdev_toकरो toकरो;

	priv = container_of(work, काष्ठा ccw_device_निजी, toकरो_work);
	cdev = priv->cdev;
	sch = to_subchannel(cdev->dev.parent);
	/* Find out toकरो. */
	spin_lock_irq(cdev->ccwlock);
	toकरो = priv->toकरो;
	priv->toकरो = CDEV_TODO_NOTHING;
	CIO_MSG_EVENT(4, "cdev_todo: cdev=0.%x.%04x todo=%d\n",
		      priv->dev_id.ssid, priv->dev_id.devno, toकरो);
	spin_unlock_irq(cdev->ccwlock);
	/* Perक्रमm toकरो. */
	चयन (toकरो) अणु
	हाल CDEV_TODO_ENABLE_CMF:
		cmf_reenable(cdev);
		अवरोध;
	हाल CDEV_TODO_REBIND:
		ccw_device_करो_unbind_bind(cdev);
		अवरोध;
	हाल CDEV_TODO_REGISTER:
		io_subchannel_रेजिस्टर(cdev);
		अवरोध;
	हाल CDEV_TODO_UNREG_EVAL:
		अगर (!sch_is_pseuकरो_sch(sch))
			css_schedule_eval(sch->schid);
		fallthrough;
	हाल CDEV_TODO_UNREG:
		अगर (sch_is_pseuकरो_sch(sch))
			ccw_device_unरेजिस्टर(cdev);
		अन्यथा
			ccw_device_call_sch_unरेजिस्टर(cdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* Release workqueue ref. */
	put_device(&cdev->dev);
पूर्ण

/**
 * ccw_device_sched_toकरो - schedule ccw device operation
 * @cdev: ccw device
 * @toकरो: toकरो
 *
 * Schedule the operation identअगरied by @toकरो to be perक्रमmed on the slow path
 * workqueue. Do nothing अगर another operation with higher priority is alपढ़ोy
 * scheduled. Needs to be called with ccwdev lock held.
 */
व्योम ccw_device_sched_toकरो(काष्ठा ccw_device *cdev, क्रमागत cdev_toकरो toकरो)
अणु
	CIO_MSG_EVENT(4, "cdev_todo: sched cdev=0.%x.%04x todo=%d\n",
		      cdev->निजी->dev_id.ssid, cdev->निजी->dev_id.devno,
		      toकरो);
	अगर (cdev->निजी->toकरो >= toकरो)
		वापस;
	cdev->निजी->toकरो = toकरो;
	/* Get workqueue ref. */
	अगर (!get_device(&cdev->dev))
		वापस;
	अगर (!queue_work(cio_work_q, &cdev->निजी->toकरो_work)) अणु
		/* Alपढ़ोy queued, release workqueue ref. */
		put_device(&cdev->dev);
	पूर्ण
पूर्ण

/**
 * ccw_device_siosl() - initiate logging
 * @cdev: ccw device
 *
 * This function is used to invoke model-dependent logging within the channel
 * subप्रणाली.
 */
पूर्णांक ccw_device_siosl(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	वापस chsc_siosl(sch->schid);
पूर्ण
EXPORT_SYMBOL_GPL(ccw_device_siosl);

EXPORT_SYMBOL(ccw_device_set_online);
EXPORT_SYMBOL(ccw_device_set_offline);
EXPORT_SYMBOL(ccw_driver_रेजिस्टर);
EXPORT_SYMBOL(ccw_driver_unरेजिस्टर);
EXPORT_SYMBOL(get_ccwdev_by_busid);

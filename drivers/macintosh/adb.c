<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device driver क्रम the Apple Desktop Bus
 * and the /dev/adb device on macपूर्णांकoshes.
 *
 * Copyright (C) 1996 Paul Mackerras.
 *
 * Modअगरied to declare controllers as काष्ठाures, added
 * client notअगरication of bus reset and handles PowerBook
 * sleep, by Benjamin Herrenschmidt.
 *
 * To करो:
 *
 * - /sys/bus/adb to list the devices and infos
 * - more /dev/adb to allow userland to receive the
 *   flow of स्वतः-polling datas from a given device.
 * - move bus probe to a kernel thपढ़ो
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#समावेश <linux/pmu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/रुको.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>

#समावेश <linux/uaccess.h>
#अगर_घोषित CONFIG_PPC
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#पूर्ण_अगर


EXPORT_SYMBOL(adb_client_list);

बाह्य काष्ठा adb_driver via_macii_driver;
बाह्य काष्ठा adb_driver via_cuda_driver;
बाह्य काष्ठा adb_driver adb_iop_driver;
बाह्य काष्ठा adb_driver via_pmu_driver;
बाह्य काष्ठा adb_driver macio_adb_driver;

अटल DEFINE_MUTEX(adb_mutex);
अटल काष्ठा adb_driver *adb_driver_list[] = अणु
#अगर_घोषित CONFIG_ADB_MACII
	&via_macii_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_CUDA
	&via_cuda_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_IOP
	&adb_iop_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	&via_pmu_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_MACIO
	&macio_adb_driver,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल काष्ठा class *adb_dev_class;

अटल काष्ठा adb_driver *adb_controller;
BLOCKING_NOTIFIER_HEAD(adb_client_list);
अटल पूर्णांक adb_got_sleep;
अटल पूर्णांक adb_inited;
अटल DEFINE_SEMAPHORE(adb_probe_mutex);
अटल पूर्णांक sleepy_trackpad;
अटल पूर्णांक स्वतःpoll_devs;
पूर्णांक __adb_probe_sync;

अटल पूर्णांक adb_scan_bus(व्योम);
अटल पूर्णांक करो_adb_reset_bus(व्योम);
अटल व्योम adbdev_init(व्योम);
अटल पूर्णांक try_handler_change(पूर्णांक, पूर्णांक);

अटल काष्ठा adb_handler अणु
	व्योम (*handler)(अचिन्हित अक्षर *, पूर्णांक, पूर्णांक);
	पूर्णांक original_address;
	पूर्णांक handler_id;
	पूर्णांक busy;
पूर्ण adb_handler[16];

/*
 * The adb_handler_mutex mutex protects all accesses to the original_address
 * and handler_id fields of adb_handler[i] क्रम all i, and changes to the
 * handler field.
 * Accesses to the handler field are रक्षित by the adb_handler_lock
 * rwlock.  It is held across all calls to any handler, so that by the
 * समय adb_unरेजिस्टर वापसs, we know that the old handler isn't being
 * called.
 */
अटल DEFINE_MUTEX(adb_handler_mutex);
अटल DEFINE_RWLOCK(adb_handler_lock);

#अगर 0
अटल व्योम prपूर्णांकADBreply(काष्ठा adb_request *req)
अणु
        पूर्णांक i;

        prपूर्णांकk("adb reply (%d)", req->reply_len);
        क्रम(i = 0; i < req->reply_len; i++)
                prपूर्णांकk(" %x", req->reply[i]);
        prपूर्णांकk("\n");

पूर्ण
#पूर्ण_अगर

अटल पूर्णांक adb_scan_bus(व्योम)
अणु
	पूर्णांक i, highFree=0, noMovement;
	पूर्णांक devmask = 0;
	काष्ठा adb_request req;
	
	/* assumes adb_handler[] is all zeroes at this poपूर्णांक */
	क्रम (i = 1; i < 16; i++) अणु
		/* see अगर there is anything at address i */
		adb_request(&req, शून्य, ADBREQ_SYNC | ADBREQ_REPLY, 1,
                            (i << 4) | 0xf);
		अगर (req.reply_len > 1)
			/* one or more devices at this address */
			adb_handler[i].original_address = i;
		अन्यथा अगर (i > highFree)
			highFree = i;
	पूर्ण

	/* Note we reset noMovement to 0 each समय we move a device */
	क्रम (noMovement = 1; noMovement < 2 && highFree > 0; noMovement++) अणु
		क्रम (i = 1; i < 16; i++) अणु
			अगर (adb_handler[i].original_address == 0)
				जारी;
			/*
			 * Send a "talk register 3" command to address i
			 * to provoke a collision अगर there is more than
			 * one device at this address.
			 */
			adb_request(&req, शून्य, ADBREQ_SYNC | ADBREQ_REPLY, 1,
				    (i << 4) | 0xf);
			/*
			 * Move the device(s) which didn't detect a
			 * collision to address `highFree'.  Hopefully
			 * this only moves one device.
			 */
			adb_request(&req, शून्य, ADBREQ_SYNC, 3,
				    (i<< 4) | 0xb, (highFree | 0x60), 0xfe);
			/*
			 * See अगर anybody actually moved. This is suggested
			 * by HW TechNote 01:
			 *
			 * https://developer.apple.com/technotes/hw/hw_01.hपंचांगl
			 */
			adb_request(&req, शून्य, ADBREQ_SYNC | ADBREQ_REPLY, 1,
				    (highFree << 4) | 0xf);
			अगर (req.reply_len <= 1) जारी;
			/*
			 * Test whether there are any device(s) left
			 * at address i.
			 */
			adb_request(&req, शून्य, ADBREQ_SYNC | ADBREQ_REPLY, 1,
				    (i << 4) | 0xf);
			अगर (req.reply_len > 1) अणु
				/*
				 * There are still one or more devices
				 * left at address i.  Register the one(s)
				 * we moved to `highFree', and find a new
				 * value क्रम highFree.
				 */
				adb_handler[highFree].original_address =
					adb_handler[i].original_address;
				जबतक (highFree > 0 &&
				       adb_handler[highFree].original_address)
					highFree--;
				अगर (highFree <= 0)
					अवरोध;

				noMovement = 0;
			पूर्ण अन्यथा अणु
				/*
				 * No devices left at address i; move the
				 * one(s) we moved to `highFree' back to i.
				 */
				adb_request(&req, शून्य, ADBREQ_SYNC, 3,
					    (highFree << 4) | 0xb,
					    (i | 0x60), 0xfe);
			पूर्ण
		पूर्ण	
	पूर्ण

	/* Now fill in the handler_id field of the adb_handler entries. */
	क्रम (i = 1; i < 16; i++) अणु
		अगर (adb_handler[i].original_address == 0)
			जारी;
		adb_request(&req, शून्य, ADBREQ_SYNC | ADBREQ_REPLY, 1,
			    (i << 4) | 0xf);
		adb_handler[i].handler_id = req.reply[2];
		prपूर्णांकk(KERN_DEBUG "adb device [%d]: %d 0x%X\n", i,
		       adb_handler[i].original_address,
		       adb_handler[i].handler_id);
		devmask |= 1 << i;
	पूर्ण
	वापस devmask;
पूर्ण

/*
 * This kernel task handles ADB probing. It dies once probing is
 * completed.
 */
अटल पूर्णांक
adb_probe_task(व्योम *x)
अणु
	pr_debug("adb: starting probe task...\n");
	करो_adb_reset_bus();
	pr_debug("adb: finished probe task...\n");

	up(&adb_probe_mutex);

	वापस 0;
पूर्ण

अटल व्योम
__adb_probe_task(काष्ठा work_काष्ठा *bullshit)
अणु
	kthपढ़ो_run(adb_probe_task, शून्य, "kadbprobe");
पूर्ण

अटल DECLARE_WORK(adb_reset_work, __adb_probe_task);

पूर्णांक
adb_reset_bus(व्योम)
अणु
	अगर (__adb_probe_sync) अणु
		करो_adb_reset_bus();
		वापस 0;
	पूर्ण

	करोwn(&adb_probe_mutex);
	schedule_work(&adb_reset_work);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 * notअगरy clients beक्रमe sleep
 */
अटल पूर्णांक __adb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	adb_got_sleep = 1;
	/* We need to get a lock on the probe thपढ़ो */
	करोwn(&adb_probe_mutex);
	/* Stop स्वतःpoll */
	अगर (adb_controller->स्वतःpoll)
		adb_controller->स्वतःpoll(0);
	blocking_notअगरier_call_chain(&adb_client_list, ADB_MSG_POWERDOWN, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक adb_suspend(काष्ठा device *dev)
अणु
	वापस __adb_suspend(to_platक्रमm_device(dev), PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक adb_मुक्तze(काष्ठा device *dev)
अणु
	वापस __adb_suspend(to_platक्रमm_device(dev), PMSG_FREEZE);
पूर्ण

अटल पूर्णांक adb_घातeroff(काष्ठा device *dev)
अणु
	वापस __adb_suspend(to_platक्रमm_device(dev), PMSG_HIBERNATE);
पूर्ण

/*
 * reset bus after sleep
 */
अटल पूर्णांक __adb_resume(काष्ठा platक्रमm_device *dev)
अणु
	adb_got_sleep = 0;
	up(&adb_probe_mutex);
	adb_reset_bus();

	वापस 0;
पूर्ण

अटल पूर्णांक adb_resume(काष्ठा device *dev)
अणु
	वापस __adb_resume(to_platक्रमm_device(dev));
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक __init adb_init(व्योम)
अणु
	काष्ठा adb_driver *driver;
	पूर्णांक i;

#अगर_घोषित CONFIG_PPC32
	अगर (!machine_is(chrp) && !machine_is(घातermac))
		वापस 0;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MAC
	अगर (!MACH_IS_MAC)
		वापस 0;
#पूर्ण_अगर

	/* xmon may करो early-init */
	अगर (adb_inited)
		वापस 0;
	adb_inited = 1;
		
	adb_controller = शून्य;

	i = 0;
	जबतक ((driver = adb_driver_list[i++]) != शून्य) अणु
		अगर (!driver->probe()) अणु
			adb_controller = driver;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (adb_controller != शून्य && adb_controller->init &&
	    adb_controller->init())
		adb_controller = शून्य;
	अगर (adb_controller == शून्य) अणु
		pr_warn("Warning: no ADB interface detected\n");
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_PPC
		अगर (of_machine_is_compatible("AAPL,PowerBook1998") ||
			of_machine_is_compatible("PowerBook1,1"))
			sleepy_trackpad = 1;
#पूर्ण_अगर /* CONFIG_PPC */

		adbdev_init();
		adb_reset_bus();
	पूर्ण
	वापस 0;
पूर्ण

device_initcall(adb_init);

अटल पूर्णांक
करो_adb_reset_bus(व्योम)
अणु
	पूर्णांक ret;
	
	अगर (adb_controller == शून्य)
		वापस -ENXIO;
		
	अगर (adb_controller->स्वतःpoll)
		adb_controller->स्वतःpoll(0);

	blocking_notअगरier_call_chain(&adb_client_list,
		ADB_MSG_PRE_RESET, शून्य);

	अगर (sleepy_trackpad) अणु
		/* Let the trackpad settle करोwn */
		msleep(500);
	पूर्ण

	mutex_lock(&adb_handler_mutex);
	ग_लिखो_lock_irq(&adb_handler_lock);
	स_रखो(adb_handler, 0, माप(adb_handler));
	ग_लिखो_unlock_irq(&adb_handler_lock);

	/* That one is still a bit synchronous, oh well... */
	अगर (adb_controller->reset_bus)
		ret = adb_controller->reset_bus();
	अन्यथा
		ret = 0;

	अगर (sleepy_trackpad) अणु
		/* Let the trackpad settle करोwn */
		msleep(1500);
	पूर्ण

	अगर (!ret) अणु
		स्वतःpoll_devs = adb_scan_bus();
		अगर (adb_controller->स्वतःpoll)
			adb_controller->स्वतःpoll(स्वतःpoll_devs);
	पूर्ण
	mutex_unlock(&adb_handler_mutex);

	blocking_notअगरier_call_chain(&adb_client_list,
		ADB_MSG_POST_RESET, शून्य);
	
	वापस ret;
पूर्ण

व्योम
adb_poll(व्योम)
अणु
	अगर ((adb_controller == शून्य)||(adb_controller->poll == शून्य))
		वापस;
	adb_controller->poll();
पूर्ण
EXPORT_SYMBOL(adb_poll);

अटल व्योम adb_sync_req_करोne(काष्ठा adb_request *req)
अणु
	काष्ठा completion *comp = req->arg;

	complete(comp);
पूर्ण

पूर्णांक
adb_request(काष्ठा adb_request *req, व्योम (*करोne)(काष्ठा adb_request *),
	    पूर्णांक flags, पूर्णांक nbytes, ...)
अणु
	बहु_सूची list;
	पूर्णांक i;
	पूर्णांक rc;
	काष्ठा completion comp;

	अगर ((adb_controller == शून्य) || (adb_controller->send_request == शून्य))
		वापस -ENXIO;
	अगर (nbytes < 1)
		वापस -EINVAL;

	req->nbytes = nbytes+1;
	req->करोne = करोne;
	req->reply_expected = flags & ADBREQ_REPLY;
	req->data[0] = ADB_PACKET;
	बहु_शुरू(list, nbytes);
	क्रम (i = 0; i < nbytes; ++i)
		req->data[i+1] = बहु_तर्क(list, पूर्णांक);
	बहु_पूर्ण(list);

	अगर (flags & ADBREQ_NOSEND)
		वापस 0;

	/* Synchronous requests block using an on-stack completion */
	अगर (flags & ADBREQ_SYNC) अणु
		WARN_ON(करोne);
		req->करोne = adb_sync_req_करोne;
		req->arg = &comp;
		init_completion(&comp);
	पूर्ण

	rc = adb_controller->send_request(req, 0);

	अगर ((flags & ADBREQ_SYNC) && !rc && !req->complete)
		रुको_क्रम_completion(&comp);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(adb_request);

 /* Ultimately this should वापस the number of devices with
    the given शेष id.
    And it करोes it now ! Note: changed behaviour: This function
    will now रेजिस्टर अगर शेष_id _and_ handler_id both match
    but handler_id can be left to 0 to match with शेष_id only.
    When handler_id is set, this function will try to adjust
    the handler_id id it करोesn't match. */
पूर्णांक
adb_रेजिस्टर(पूर्णांक शेष_id, पूर्णांक handler_id, काष्ठा adb_ids *ids,
	     व्योम (*handler)(अचिन्हित अक्षर *, पूर्णांक, पूर्णांक))
अणु
	पूर्णांक i;

	mutex_lock(&adb_handler_mutex);
	ids->nids = 0;
	क्रम (i = 1; i < 16; i++) अणु
		अगर ((adb_handler[i].original_address == शेष_id) &&
		    (!handler_id || (handler_id == adb_handler[i].handler_id) || 
		    try_handler_change(i, handler_id))) अणु
			अगर (adb_handler[i].handler != 0) अणु
				pr_err("Two handlers for ADB device %d\n",
				       शेष_id);
				जारी;
			पूर्ण
			ग_लिखो_lock_irq(&adb_handler_lock);
			adb_handler[i].handler = handler;
			ग_लिखो_unlock_irq(&adb_handler_lock);
			ids->id[ids->nids++] = i;
		पूर्ण
	पूर्ण
	mutex_unlock(&adb_handler_mutex);
	वापस ids->nids;
पूर्ण
EXPORT_SYMBOL(adb_रेजिस्टर);

पूर्णांक
adb_unरेजिस्टर(पूर्णांक index)
अणु
	पूर्णांक ret = -ENODEV;

	mutex_lock(&adb_handler_mutex);
	ग_लिखो_lock_irq(&adb_handler_lock);
	अगर (adb_handler[index].handler) अणु
		जबतक(adb_handler[index].busy) अणु
			ग_लिखो_unlock_irq(&adb_handler_lock);
			yield();
			ग_लिखो_lock_irq(&adb_handler_lock);
		पूर्ण
		ret = 0;
		adb_handler[index].handler = शून्य;
	पूर्ण
	ग_लिखो_unlock_irq(&adb_handler_lock);
	mutex_unlock(&adb_handler_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(adb_unरेजिस्टर);

व्योम
adb_input(अचिन्हित अक्षर *buf, पूर्णांक nb, पूर्णांक स्वतःpoll)
अणु
	पूर्णांक i, id;
	अटल पूर्णांक dump_adb_input;
	अचिन्हित दीर्घ flags;
	
	व्योम (*handler)(अचिन्हित अक्षर *, पूर्णांक, पूर्णांक);

	/* We skip keystrokes and mouse moves when the sleep process
	 * has been started. We stop स्वतःpoll, but this is another security
	 */
	अगर (adb_got_sleep)
		वापस;
		
	id = buf[0] >> 4;
	अगर (dump_adb_input) अणु
		pr_info("adb packet: ");
		क्रम (i = 0; i < nb; ++i)
			pr_cont(" %x", buf[i]);
		pr_cont(", id = %d\n", id);
	पूर्ण
	ग_लिखो_lock_irqsave(&adb_handler_lock, flags);
	handler = adb_handler[id].handler;
	अगर (handler != शून्य)
		adb_handler[id].busy = 1;
	ग_लिखो_unlock_irqrestore(&adb_handler_lock, flags);
	अगर (handler != शून्य) अणु
		(*handler)(buf, nb, स्वतःpoll);
		wmb();
		adb_handler[id].busy = 0;
	पूर्ण
		
पूर्ण

/* Try to change handler to new_id. Will वापस 1 अगर successful. */
अटल पूर्णांक try_handler_change(पूर्णांक address, पूर्णांक new_id)
अणु
	काष्ठा adb_request req;

	अगर (adb_handler[address].handler_id == new_id)
	    वापस 1;
	adb_request(&req, शून्य, ADBREQ_SYNC, 3,
	    ADB_WRITEREG(address, 3), address | 0x20, new_id);
	adb_request(&req, शून्य, ADBREQ_SYNC | ADBREQ_REPLY, 1,
	    ADB_READREG(address, 3));
	अगर (req.reply_len < 2)
	    वापस 0;
	अगर (req.reply[2] != new_id)
	    वापस 0;
	adb_handler[address].handler_id = req.reply[2];

	वापस 1;
पूर्ण

पूर्णांक
adb_try_handler_change(पूर्णांक address, पूर्णांक new_id)
अणु
	पूर्णांक ret;

	mutex_lock(&adb_handler_mutex);
	ret = try_handler_change(address, new_id);
	mutex_unlock(&adb_handler_mutex);
	अगर (ret)
		pr_debug("adb handler change: [%d] 0x%X\n", address, new_id);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(adb_try_handler_change);

पूर्णांक
adb_get_infos(पूर्णांक address, पूर्णांक *original_address, पूर्णांक *handler_id)
अणु
	mutex_lock(&adb_handler_mutex);
	*original_address = adb_handler[address].original_address;
	*handler_id = adb_handler[address].handler_id;
	mutex_unlock(&adb_handler_mutex);

	वापस (*original_address != 0);
पूर्ण


/*
 * /dev/adb device driver.
 */

#घोषणा ADB_MAJOR	56	/* major number क्रम /dev/adb */

काष्ठा adbdev_state अणु
	spinlock_t	lock;
	atomic_t	n_pending;
	काष्ठा adb_request *completed;
  	रुको_queue_head_t रुको_queue;
	पूर्णांक		inuse;
पूर्ण;

अटल व्योम adb_ग_लिखो_करोne(काष्ठा adb_request *req)
अणु
	काष्ठा adbdev_state *state = (काष्ठा adbdev_state *) req->arg;
	अचिन्हित दीर्घ flags;

	अगर (!req->complete) अणु
		req->reply_len = 0;
		req->complete = 1;
	पूर्ण
	spin_lock_irqsave(&state->lock, flags);
	atomic_dec(&state->n_pending);
	अगर (!state->inuse) अणु
		kमुक्त(req);
		अगर (atomic_पढ़ो(&state->n_pending) == 0) अणु
			spin_unlock_irqrestore(&state->lock, flags);
			kमुक्त(state);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा adb_request **ap = &state->completed;
		जबतक (*ap != शून्य)
			ap = &(*ap)->next;
		req->next = शून्य;
		*ap = req;
		wake_up_पूर्णांकerruptible(&state->रुको_queue);
	पूर्ण
	spin_unlock_irqrestore(&state->lock, flags);
पूर्ण

अटल पूर्णांक
करो_adb_query(काष्ठा adb_request *req)
अणु
	पूर्णांक	ret = -EINVAL;

	चयन(req->data[1]) अणु
	हाल ADB_QUERY_GETDEVINFO:
		अगर (req->nbytes < 3)
			अवरोध;
		mutex_lock(&adb_handler_mutex);
		req->reply[0] = adb_handler[req->data[2]].original_address;
		req->reply[1] = adb_handler[req->data[2]].handler_id;
		mutex_unlock(&adb_handler_mutex);
		req->complete = 1;
		req->reply_len = 2;
		adb_ग_लिखो_करोne(req);
		ret = 0;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक adb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा adbdev_state *state;
	पूर्णांक ret = 0;

	mutex_lock(&adb_mutex);
	अगर (iminor(inode) > 0 || adb_controller == शून्य) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण
	state = kदो_स्मृति(माप(काष्ठा adbdev_state), GFP_KERNEL);
	अगर (state == 0) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	file->निजी_data = state;
	spin_lock_init(&state->lock);
	atomic_set(&state->n_pending, 0);
	state->completed = शून्य;
	init_रुकोqueue_head(&state->रुको_queue);
	state->inuse = 1;

out:
	mutex_unlock(&adb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक adb_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा adbdev_state *state = file->निजी_data;
	अचिन्हित दीर्घ flags;

	mutex_lock(&adb_mutex);
	अगर (state) अणु
		file->निजी_data = शून्य;
		spin_lock_irqsave(&state->lock, flags);
		अगर (atomic_पढ़ो(&state->n_pending) == 0
		    && state->completed == शून्य) अणु
			spin_unlock_irqrestore(&state->lock, flags);
			kमुक्त(state);
		पूर्ण अन्यथा अणु
			state->inuse = 0;
			spin_unlock_irqrestore(&state->lock, flags);
		पूर्ण
	पूर्ण
	mutex_unlock(&adb_mutex);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार adb_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret = 0;
	काष्ठा adbdev_state *state = file->निजी_data;
	काष्ठा adb_request *req;
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ flags;

	अगर (count < 2)
		वापस -EINVAL;
	अगर (count > माप(req->reply))
		count = माप(req->reply);

	req = शून्य;
	spin_lock_irqsave(&state->lock, flags);
	add_रुको_queue(&state->रुको_queue, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);

	क्रम (;;) अणु
		req = state->completed;
		अगर (req != शून्य)
			state->completed = req->next;
		अन्यथा अगर (atomic_पढ़ो(&state->n_pending) == 0)
			ret = -EIO;
		अगर (req != शून्य || ret != 0)
			अवरोध;
		
		अगर (file->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&state->lock, flags);
		schedule();
		spin_lock_irqsave(&state->lock, flags);
	पूर्ण

	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&state->रुको_queue, &रुको);
	spin_unlock_irqrestore(&state->lock, flags);
	
	अगर (ret)
		वापस ret;

	ret = req->reply_len;
	अगर (ret > count)
		ret = count;
	अगर (ret > 0 && copy_to_user(buf, req->reply, ret))
		ret = -EFAULT;

	kमुक्त(req);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार adb_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret/*, i*/;
	काष्ठा adbdev_state *state = file->निजी_data;
	काष्ठा adb_request *req;

	अगर (count < 2 || count > माप(req->data))
		वापस -EINVAL;
	अगर (adb_controller == शून्य)
		वापस -ENXIO;

	req = kदो_स्मृति(माप(काष्ठा adb_request),
					     GFP_KERNEL);
	अगर (req == शून्य)
		वापस -ENOMEM;

	req->nbytes = count;
	req->करोne = adb_ग_लिखो_करोne;
	req->arg = (व्योम *) state;
	req->complete = 0;
	
	ret = -EFAULT;
	अगर (copy_from_user(req->data, buf, count))
		जाओ out;

	atomic_inc(&state->n_pending);

	/* If a probe is in progress or we are sleeping, रुको क्रम it to complete */
	करोwn(&adb_probe_mutex);

	/* Queries are special requests sent to the ADB driver itself */
	अगर (req->data[0] == ADB_QUERY) अणु
		अगर (count > 1)
			ret = करो_adb_query(req);
		अन्यथा
			ret = -EINVAL;
		up(&adb_probe_mutex);
	पूर्ण
	/* Special हाल क्रम ADB_BUSRESET request, all others are sent to
	   the controller */
	अन्यथा अगर ((req->data[0] == ADB_PACKET) && (count > 1)
		&& (req->data[1] == ADB_BUSRESET)) अणु
		ret = करो_adb_reset_bus();
		up(&adb_probe_mutex);
		atomic_dec(&state->n_pending);
		अगर (ret == 0)
			ret = count;
		जाओ out;
	पूर्ण अन्यथा अणु	
		req->reply_expected = ((req->data[1] & 0xc) == 0xc);
		अगर (adb_controller && adb_controller->send_request)
			ret = adb_controller->send_request(req, 0);
		अन्यथा
			ret = -ENXIO;
		up(&adb_probe_mutex);
	पूर्ण

	अगर (ret != 0) अणु
		atomic_dec(&state->n_pending);
		जाओ out;
	पूर्ण
	वापस count;

out:
	kमुक्त(req);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations adb_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= adb_पढ़ो,
	.ग_लिखो		= adb_ग_लिखो,
	.खोलो		= adb_खोलो,
	.release	= adb_release,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा dev_pm_ops adb_dev_pm_ops = अणु
	.suspend = adb_suspend,
	.resume = adb_resume,
	/* Hibernate hooks */
	.मुक्तze = adb_मुक्तze,
	.thaw = adb_resume,
	.घातeroff = adb_घातeroff,
	.restore = adb_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver adb_pfdrv = अणु
	.driver = अणु
		.name = "adb",
#अगर_घोषित CONFIG_PM
		.pm = &adb_dev_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device adb_pfdev = अणु
	.name = "adb",
पूर्ण;

अटल पूर्णांक __init
adb_dummy_probe(काष्ठा platक्रमm_device *dev)
अणु
	अगर (dev == &adb_pfdev)
		वापस 0;
	वापस -ENODEV;
पूर्ण

अटल व्योम __init
adbdev_init(व्योम)
अणु
	अगर (रेजिस्टर_chrdev(ADB_MAJOR, "adb", &adb_fops)) अणु
		pr_err("adb: unable to get major %d\n", ADB_MAJOR);
		वापस;
	पूर्ण

	adb_dev_class = class_create(THIS_MODULE, "adb");
	अगर (IS_ERR(adb_dev_class))
		वापस;
	device_create(adb_dev_class, शून्य, MKDEV(ADB_MAJOR, 0), शून्य, "adb");

	platक्रमm_device_रेजिस्टर(&adb_pfdev);
	platक्रमm_driver_probe(&adb_pfdrv, adb_dummy_probe);
पूर्ण

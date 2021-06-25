<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Deliver z/VM CP special messages (SMSG) as uevents.
 *
 * The driver रेजिस्टरs क्रम z/VM CP special messages with the
 * "APP" prefix. Incoming messages are delivered to user space
 * as uevents.
 *
 * Copyright IBM Corp. 2010
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 *
 */
#घोषणा KMSG_COMPONENT		"smsgiucv_app"
#घोषणा pr_fmt(fmt)		KMSG_COMPONENT ": " fmt

#समावेश <linux/प्रकार.स>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/kobject.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <net/iucv/iucv.h>
#समावेश "smsgiucv.h"

/* prefix used क्रम SMSG registration */
#घोषणा SMSG_PREFIX		"APP"

/* SMSG related uevent environment variables */
#घोषणा ENV_SENDER_STR		"SMSG_SENDER="
#घोषणा ENV_SENDER_LEN		(म_माप(ENV_SENDER_STR) + 8 + 1)
#घोषणा ENV_PREFIX_STR		"SMSG_ID="
#घोषणा ENV_PREFIX_LEN		(म_माप(ENV_PREFIX_STR) + \
				 म_माप(SMSG_PREFIX) + 1)
#घोषणा ENV_TEXT_STR		"SMSG_TEXT="
#घोषणा ENV_TEXT_LEN(msg)	(म_माप(ENV_TEXT_STR) + म_माप((msg)) + 1)

/* z/VM user ID which is permitted to send SMSGs
 * If the value is undefined or empty (""), special messages are
 * accepted from any z/VM user ID. */
अटल अक्षर *sender;
module_param(sender, अक्षरp, 0400);
MODULE_PARM_DESC(sender, "z/VM user ID from which CP SMSGs are accepted");

/* SMSG device representation */
अटल काष्ठा device *smsg_app_dev;

/* list element क्रम queuing received messages क्रम delivery */
काष्ठा smsg_app_event अणु
	काष्ठा list_head list;
	अक्षर *buf;
	अक्षर *envp[4];
पूर्ण;

/* queue क्रम outgoing uevents */
अटल LIST_HEAD(smsg_event_queue);
अटल DEFINE_SPINLOCK(smsg_event_queue_lock);

अटल व्योम smsg_app_event_मुक्त(काष्ठा smsg_app_event *ev)
अणु
	kमुक्त(ev->buf);
	kमुक्त(ev);
पूर्ण

अटल काष्ठा smsg_app_event *smsg_app_event_alloc(स्थिर अक्षर *from,
						   स्थिर अक्षर *msg)
अणु
	काष्ठा smsg_app_event *ev;

	ev = kzalloc(माप(*ev), GFP_ATOMIC);
	अगर (!ev)
		वापस शून्य;

	ev->buf = kzalloc(ENV_SENDER_LEN + ENV_PREFIX_LEN +
			  ENV_TEXT_LEN(msg), GFP_ATOMIC);
	अगर (!ev->buf) अणु
		kमुक्त(ev);
		वापस शून्य;
	पूर्ण

	/* setting up environment poपूर्णांकers पूर्णांकo buf */
	ev->envp[0] = ev->buf;
	ev->envp[1] = ev->envp[0] + ENV_SENDER_LEN;
	ev->envp[2] = ev->envp[1] + ENV_PREFIX_LEN;
	ev->envp[3] = शून्य;

	/* setting up environment: sender, prefix name, and message text */
	snम_लिखो(ev->envp[0], ENV_SENDER_LEN, ENV_SENDER_STR "%s", from);
	snम_लिखो(ev->envp[1], ENV_PREFIX_LEN, ENV_PREFIX_STR "%s", SMSG_PREFIX);
	snम_लिखो(ev->envp[2], ENV_TEXT_LEN(msg), ENV_TEXT_STR "%s", msg);

	वापस ev;
पूर्ण

अटल व्योम smsg_event_work_fn(काष्ठा work_काष्ठा *work)
अणु
	LIST_HEAD(event_queue);
	काष्ठा smsg_app_event *p, *n;
	काष्ठा device *dev;

	dev = get_device(smsg_app_dev);
	अगर (!dev)
		वापस;

	spin_lock_bh(&smsg_event_queue_lock);
	list_splice_init(&smsg_event_queue, &event_queue);
	spin_unlock_bh(&smsg_event_queue_lock);

	list_क्रम_each_entry_safe(p, n, &event_queue, list) अणु
		list_del(&p->list);
		kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, p->envp);
		smsg_app_event_मुक्त(p);
	पूर्ण

	put_device(dev);
पूर्ण
अटल DECLARE_WORK(smsg_event_work, smsg_event_work_fn);

अटल व्योम smsg_app_callback(स्थिर अक्षर *from, अक्षर *msg)
अणु
	काष्ठा smsg_app_event *se;

	/* check अगर the originating z/VM user ID matches
	 * the configured sender. */
	अगर (sender && म_माप(sender) > 0 && म_भेद(from, sender) != 0)
		वापस;

	/* get start of message text (skip prefix and leading blanks) */
	msg += म_माप(SMSG_PREFIX);
	जबतक (*msg && है_खाली(*msg))
		msg++;
	अगर (*msg == '\0')
		वापस;

	/* allocate event list element and its environment */
	se = smsg_app_event_alloc(from, msg);
	अगर (!se)
		वापस;

	/* queue event and schedule work function */
	spin_lock(&smsg_event_queue_lock);
	list_add_tail(&se->list, &smsg_event_queue);
	spin_unlock(&smsg_event_queue_lock);

	schedule_work(&smsg_event_work);
	वापस;
पूर्ण

अटल पूर्णांक __init smsgiucv_app_init(व्योम)
अणु
	काष्ठा device_driver *smsgiucv_drv;
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM)
		वापस -ENODEV;

	smsg_app_dev = kzalloc(माप(*smsg_app_dev), GFP_KERNEL);
	अगर (!smsg_app_dev)
		वापस -ENOMEM;

	smsgiucv_drv = driver_find(SMSGIUCV_DRV_NAME, &iucv_bus);
	अगर (!smsgiucv_drv) अणु
		kमुक्त(smsg_app_dev);
		वापस -ENODEV;
	पूर्ण

	rc = dev_set_name(smsg_app_dev, KMSG_COMPONENT);
	अगर (rc) अणु
		kमुक्त(smsg_app_dev);
		जाओ fail;
	पूर्ण
	smsg_app_dev->bus = &iucv_bus;
	smsg_app_dev->parent = iucv_root;
	smsg_app_dev->release = (व्योम (*)(काष्ठा device *)) kमुक्त;
	smsg_app_dev->driver = smsgiucv_drv;
	rc = device_रेजिस्टर(smsg_app_dev);
	अगर (rc) अणु
		put_device(smsg_app_dev);
		जाओ fail;
	पूर्ण

	/* convert sender to upperहाल अक्षरacters */
	अगर (sender) अणु
		पूर्णांक len = म_माप(sender);
		जबतक (len--)
			sender[len] = बड़े(sender[len]);
	पूर्ण

	/* रेजिस्टर with the smsgiucv device driver */
	rc = smsg_रेजिस्टर_callback(SMSG_PREFIX, smsg_app_callback);
	अगर (rc) अणु
		device_unरेजिस्टर(smsg_app_dev);
		जाओ fail;
	पूर्ण

	rc = 0;
fail:
	वापस rc;
पूर्ण
module_init(smsgiucv_app_init);

अटल व्योम __निकास smsgiucv_app_निकास(व्योम)
अणु
	/* unरेजिस्टर callback */
	smsg_unरेजिस्टर_callback(SMSG_PREFIX, smsg_app_callback);

	/* cancel pending work and flush any queued event work */
	cancel_work_sync(&smsg_event_work);
	smsg_event_work_fn(&smsg_event_work);

	device_unरेजिस्टर(smsg_app_dev);
पूर्ण
module_निकास(smsgiucv_app_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Deliver z/VM CP SMSG as uevents");
MODULE_AUTHOR("Hendrik Brueckner <brueckner@linux.vnet.ibm.com>");

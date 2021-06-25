<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright IBM Corp. 2001, 2012
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *	       Cornelia Huck <cornelia.huck@de.ibm.com>
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *				  Ralph Wuerthner <rwuerthn@de.ibm.com>
 *  MSGTYPE reकाष्ठा:		  Holger Dengler <hd@linux.vnet.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/compat.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/debug.h>

#समावेश "zcrypt_debug.h"
#समावेश "zcrypt_api.h"

#समावेश "zcrypt_msgtype6.h"
#समावेश "zcrypt_msgtype50.h"

/*
 * Device attributes common क्रम all crypto queue devices.
 */

अटल sमाप_प्रकार online_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	काष्ठा zcrypt_queue *zq = aq->निजी;
	पूर्णांक online = aq->config && zq->online ? 1 : 0;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", online);
पूर्ण

अटल sमाप_प्रकार online_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ap_queue *aq = to_ap_queue(dev);
	काष्ठा zcrypt_queue *zq = aq->निजी;
	काष्ठा zcrypt_card *zc = zq->zcard;
	पूर्णांक online;

	अगर (माला_पूछो(buf, "%d\n", &online) != 1 || online < 0 || online > 1)
		वापस -EINVAL;

	अगर (online && (!aq->config || !aq->card->config))
		वापस -ENODEV;
	अगर (online && !zc->online)
		वापस -EINVAL;
	zq->online = online;

	ZCRYPT_DBF(DBF_INFO, "queue=%02x.%04x online=%d\n",
		   AP_QID_CARD(zq->queue->qid),
		   AP_QID_QUEUE(zq->queue->qid),
		   online);

	अगर (!online)
		ap_flush_queue(zq->queue);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(online);

अटल sमाप_प्रकार load_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा zcrypt_queue *zq = to_ap_queue(dev)->निजी;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", atomic_पढ़ो(&zq->load));
पूर्ण

अटल DEVICE_ATTR_RO(load);

अटल काष्ठा attribute *zcrypt_queue_attrs[] = अणु
	&dev_attr_online.attr,
	&dev_attr_load.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group zcrypt_queue_attr_group = अणु
	.attrs = zcrypt_queue_attrs,
पूर्ण;

व्योम zcrypt_queue_क्रमce_online(काष्ठा zcrypt_queue *zq, पूर्णांक online)
अणु
	zq->online = online;
	अगर (!online)
		ap_flush_queue(zq->queue);
पूर्ण

काष्ठा zcrypt_queue *zcrypt_queue_alloc(माप_प्रकार max_response_size)
अणु
	काष्ठा zcrypt_queue *zq;

	zq = kzalloc(माप(काष्ठा zcrypt_queue), GFP_KERNEL);
	अगर (!zq)
		वापस शून्य;
	zq->reply.msg = kदो_स्मृति(max_response_size, GFP_KERNEL);
	अगर (!zq->reply.msg)
		जाओ out_मुक्त;
	zq->reply.len = max_response_size;
	INIT_LIST_HEAD(&zq->list);
	kref_init(&zq->refcount);
	वापस zq;

out_मुक्त:
	kमुक्त(zq);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(zcrypt_queue_alloc);

व्योम zcrypt_queue_मुक्त(काष्ठा zcrypt_queue *zq)
अणु
	kमुक्त(zq->reply.msg);
	kमुक्त(zq);
पूर्ण
EXPORT_SYMBOL(zcrypt_queue_मुक्त);

अटल व्योम zcrypt_queue_release(काष्ठा kref *kref)
अणु
	काष्ठा zcrypt_queue *zq =
		container_of(kref, काष्ठा zcrypt_queue, refcount);
	zcrypt_queue_मुक्त(zq);
पूर्ण

व्योम zcrypt_queue_get(काष्ठा zcrypt_queue *zq)
अणु
	kref_get(&zq->refcount);
पूर्ण
EXPORT_SYMBOL(zcrypt_queue_get);

पूर्णांक zcrypt_queue_put(काष्ठा zcrypt_queue *zq)
अणु
	वापस kref_put(&zq->refcount, zcrypt_queue_release);
पूर्ण
EXPORT_SYMBOL(zcrypt_queue_put);

/**
 * zcrypt_queue_रेजिस्टर() - Register a crypto queue device.
 * @zq: Poपूर्णांकer to a crypto queue device
 *
 * Register a crypto queue device. Returns 0 अगर successful.
 */
पूर्णांक zcrypt_queue_रेजिस्टर(काष्ठा zcrypt_queue *zq)
अणु
	काष्ठा zcrypt_card *zc;
	पूर्णांक rc;

	spin_lock(&zcrypt_list_lock);
	zc = zq->queue->card->निजी;
	zcrypt_card_get(zc);
	zq->zcard = zc;
	zq->online = 1;	/* New devices are online by शेष. */

	ZCRYPT_DBF(DBF_INFO, "queue=%02x.%04x register online=1\n",
		   AP_QID_CARD(zq->queue->qid), AP_QID_QUEUE(zq->queue->qid));

	list_add_tail(&zq->list, &zc->zqueues);
	zcrypt_device_count++;
	spin_unlock(&zcrypt_list_lock);

	rc = sysfs_create_group(&zq->queue->ap_dev.device.kobj,
				&zcrypt_queue_attr_group);
	अगर (rc)
		जाओ out;

	अगर (zq->ops->rng) अणु
		rc = zcrypt_rng_device_add();
		अगर (rc)
			जाओ out_unरेजिस्टर;
	पूर्ण
	वापस 0;

out_unरेजिस्टर:
	sysfs_हटाओ_group(&zq->queue->ap_dev.device.kobj,
			   &zcrypt_queue_attr_group);
out:
	spin_lock(&zcrypt_list_lock);
	list_del_init(&zq->list);
	spin_unlock(&zcrypt_list_lock);
	zcrypt_card_put(zc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(zcrypt_queue_रेजिस्टर);

/**
 * zcrypt_queue_unरेजिस्टर(): Unरेजिस्टर a crypto queue device.
 * @zq: Poपूर्णांकer to crypto queue device
 *
 * Unरेजिस्टर a crypto queue device.
 */
व्योम zcrypt_queue_unरेजिस्टर(काष्ठा zcrypt_queue *zq)
अणु
	काष्ठा zcrypt_card *zc;

	ZCRYPT_DBF(DBF_INFO, "queue=%02x.%04x unregister\n",
		   AP_QID_CARD(zq->queue->qid), AP_QID_QUEUE(zq->queue->qid));

	zc = zq->zcard;
	spin_lock(&zcrypt_list_lock);
	list_del_init(&zq->list);
	zcrypt_device_count--;
	spin_unlock(&zcrypt_list_lock);
	अगर (zq->ops->rng)
		zcrypt_rng_device_हटाओ();
	sysfs_हटाओ_group(&zq->queue->ap_dev.device.kobj,
			   &zcrypt_queue_attr_group);
	zcrypt_card_put(zc);
	zcrypt_queue_put(zq);
पूर्ण
EXPORT_SYMBOL(zcrypt_queue_unरेजिस्टर);

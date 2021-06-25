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
 * Device attributes common क्रम all crypto card devices.
 */

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zcrypt_card *zc = to_ap_card(dev)->निजी;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", zc->type_string);
पूर्ण

अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार online_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);
	काष्ठा zcrypt_card *zc = ac->निजी;
	पूर्णांक online = ac->config && zc->online ? 1 : 0;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", online);
पूर्ण

अटल sमाप_प्रकार online_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ap_card *ac = to_ap_card(dev);
	काष्ठा zcrypt_card *zc = ac->निजी;
	काष्ठा zcrypt_queue *zq;
	पूर्णांक online, id;

	अगर (माला_पूछो(buf, "%d\n", &online) != 1 || online < 0 || online > 1)
		वापस -EINVAL;

	अगर (online && !ac->config)
		वापस -ENODEV;

	zc->online = online;
	id = zc->card->id;

	ZCRYPT_DBF(DBF_INFO, "card=%02x online=%d\n", id, online);

	spin_lock(&zcrypt_list_lock);
	list_क्रम_each_entry(zq, &zc->zqueues, list)
		zcrypt_queue_क्रमce_online(zq, online);
	spin_unlock(&zcrypt_list_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(online);

अटल sमाप_प्रकार load_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा zcrypt_card *zc = to_ap_card(dev)->निजी;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", atomic_पढ़ो(&zc->load));
पूर्ण

अटल DEVICE_ATTR_RO(load);

अटल काष्ठा attribute *zcrypt_card_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_online.attr,
	&dev_attr_load.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group zcrypt_card_attr_group = अणु
	.attrs = zcrypt_card_attrs,
पूर्ण;

काष्ठा zcrypt_card *zcrypt_card_alloc(व्योम)
अणु
	काष्ठा zcrypt_card *zc;

	zc = kzalloc(माप(काष्ठा zcrypt_card), GFP_KERNEL);
	अगर (!zc)
		वापस शून्य;
	INIT_LIST_HEAD(&zc->list);
	INIT_LIST_HEAD(&zc->zqueues);
	kref_init(&zc->refcount);
	वापस zc;
पूर्ण
EXPORT_SYMBOL(zcrypt_card_alloc);

व्योम zcrypt_card_मुक्त(काष्ठा zcrypt_card *zc)
अणु
	kमुक्त(zc);
पूर्ण
EXPORT_SYMBOL(zcrypt_card_मुक्त);

अटल व्योम zcrypt_card_release(काष्ठा kref *kref)
अणु
	काष्ठा zcrypt_card *zdev =
		container_of(kref, काष्ठा zcrypt_card, refcount);
	zcrypt_card_मुक्त(zdev);
पूर्ण

व्योम zcrypt_card_get(काष्ठा zcrypt_card *zc)
अणु
	kref_get(&zc->refcount);
पूर्ण
EXPORT_SYMBOL(zcrypt_card_get);

पूर्णांक zcrypt_card_put(काष्ठा zcrypt_card *zc)
अणु
	वापस kref_put(&zc->refcount, zcrypt_card_release);
पूर्ण
EXPORT_SYMBOL(zcrypt_card_put);

/**
 * zcrypt_card_रेजिस्टर() - Register a crypto card device.
 * @zc: Poपूर्णांकer to a crypto card device
 *
 * Register a crypto card device. Returns 0 अगर successful.
 */
पूर्णांक zcrypt_card_रेजिस्टर(काष्ठा zcrypt_card *zc)
अणु
	पूर्णांक rc;

	spin_lock(&zcrypt_list_lock);
	list_add_tail(&zc->list, &zcrypt_card_list);
	spin_unlock(&zcrypt_list_lock);

	zc->online = 1;

	ZCRYPT_DBF(DBF_INFO, "card=%02x register online=1\n", zc->card->id);

	rc = sysfs_create_group(&zc->card->ap_dev.device.kobj,
				&zcrypt_card_attr_group);
	अगर (rc) अणु
		spin_lock(&zcrypt_list_lock);
		list_del_init(&zc->list);
		spin_unlock(&zcrypt_list_lock);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL(zcrypt_card_रेजिस्टर);

/**
 * zcrypt_card_unरेजिस्टर(): Unरेजिस्टर a crypto card device.
 * @zc: Poपूर्णांकer to crypto card device
 *
 * Unरेजिस्टर a crypto card device.
 */
व्योम zcrypt_card_unरेजिस्टर(काष्ठा zcrypt_card *zc)
अणु
	ZCRYPT_DBF(DBF_INFO, "card=%02x unregister\n", zc->card->id);

	spin_lock(&zcrypt_list_lock);
	list_del_init(&zc->list);
	spin_unlock(&zcrypt_list_lock);
	sysfs_हटाओ_group(&zc->card->ap_dev.device.kobj,
			   &zcrypt_card_attr_group);
	zcrypt_card_put(zc);
पूर्ण
EXPORT_SYMBOL(zcrypt_card_unरेजिस्टर);

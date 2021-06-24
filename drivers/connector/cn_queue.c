<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	cn_queue.c
 *
 * 2004+ Copyright (c) Evgeniy Polyakov <zbr@ioremap.net>
 * All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/suspend.h>
#समावेश <linux/connector.h>
#समावेश <linux/delay.h>

अटल काष्ठा cn_callback_entry *
cn_queue_alloc_callback_entry(काष्ठा cn_queue_dev *dev, स्थिर अक्षर *name,
			      स्थिर काष्ठा cb_id *id,
			      व्योम (*callback)(काष्ठा cn_msg *,
					       काष्ठा netlink_skb_parms *))
अणु
	काष्ठा cn_callback_entry *cbq;

	cbq = kzalloc(माप(*cbq), GFP_KERNEL);
	अगर (!cbq) अणु
		pr_err("Failed to create new callback queue.\n");
		वापस शून्य;
	पूर्ण

	refcount_set(&cbq->refcnt, 1);

	atomic_inc(&dev->refcnt);
	cbq->pdev = dev;

	snम_लिखो(cbq->id.name, माप(cbq->id.name), "%s", name);
	स_नकल(&cbq->id.id, id, माप(काष्ठा cb_id));
	cbq->callback = callback;
	वापस cbq;
पूर्ण

व्योम cn_queue_release_callback(काष्ठा cn_callback_entry *cbq)
अणु
	अगर (!refcount_dec_and_test(&cbq->refcnt))
		वापस;

	atomic_dec(&cbq->pdev->refcnt);
	kमुक्त(cbq);
पूर्ण

पूर्णांक cn_cb_equal(स्थिर काष्ठा cb_id *i1, स्थिर काष्ठा cb_id *i2)
अणु
	वापस ((i1->idx == i2->idx) && (i1->val == i2->val));
पूर्ण

पूर्णांक cn_queue_add_callback(काष्ठा cn_queue_dev *dev, स्थिर अक्षर *name,
			  स्थिर काष्ठा cb_id *id,
			  व्योम (*callback)(काष्ठा cn_msg *,
					   काष्ठा netlink_skb_parms *))
अणु
	काष्ठा cn_callback_entry *cbq, *__cbq;
	पूर्णांक found = 0;

	cbq = cn_queue_alloc_callback_entry(dev, name, id, callback);
	अगर (!cbq)
		वापस -ENOMEM;

	spin_lock_bh(&dev->queue_lock);
	list_क्रम_each_entry(__cbq, &dev->queue_list, callback_entry) अणु
		अगर (cn_cb_equal(&__cbq->id.id, id)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		list_add_tail(&cbq->callback_entry, &dev->queue_list);
	spin_unlock_bh(&dev->queue_lock);

	अगर (found) अणु
		cn_queue_release_callback(cbq);
		वापस -EINVAL;
	पूर्ण

	cbq->seq = 0;
	cbq->group = cbq->id.id.idx;

	वापस 0;
पूर्ण

व्योम cn_queue_del_callback(काष्ठा cn_queue_dev *dev, स्थिर काष्ठा cb_id *id)
अणु
	काष्ठा cn_callback_entry *cbq, *n;
	पूर्णांक found = 0;

	spin_lock_bh(&dev->queue_lock);
	list_क्रम_each_entry_safe(cbq, n, &dev->queue_list, callback_entry) अणु
		अगर (cn_cb_equal(&cbq->id.id, id)) अणु
			list_del(&cbq->callback_entry);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&dev->queue_lock);

	अगर (found)
		cn_queue_release_callback(cbq);
पूर्ण

काष्ठा cn_queue_dev *cn_queue_alloc_dev(स्थिर अक्षर *name, काष्ठा sock *nls)
अणु
	काष्ठा cn_queue_dev *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	snम_लिखो(dev->name, माप(dev->name), "%s", name);
	atomic_set(&dev->refcnt, 0);
	INIT_LIST_HEAD(&dev->queue_list);
	spin_lock_init(&dev->queue_lock);

	dev->nls = nls;

	वापस dev;
पूर्ण

व्योम cn_queue_मुक्त_dev(काष्ठा cn_queue_dev *dev)
अणु
	काष्ठा cn_callback_entry *cbq, *n;

	spin_lock_bh(&dev->queue_lock);
	list_क्रम_each_entry_safe(cbq, n, &dev->queue_list, callback_entry)
		list_del(&cbq->callback_entry);
	spin_unlock_bh(&dev->queue_lock);

	जबतक (atomic_पढ़ो(&dev->refcnt)) अणु
		pr_info("Waiting for %s to become free: refcnt=%d.\n",
		       dev->name, atomic_पढ़ो(&dev->refcnt));
		msleep(1000);
	पूर्ण

	kमुक्त(dev);
	dev = शून्य;
पूर्ण

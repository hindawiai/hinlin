<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/qed/qede_rdma.h>
#समावेश "qede.h"

अटल काष्ठा qedr_driver *qedr_drv;
अटल LIST_HEAD(qedr_dev_list);
अटल DEFINE_MUTEX(qedr_dev_list_lock);

bool qede_rdma_supported(काष्ठा qede_dev *dev)
अणु
	वापस dev->dev_info.common.rdma_supported;
पूर्ण

अटल व्योम _qede_rdma_dev_add(काष्ठा qede_dev *edev)
अणु
	अगर (!qedr_drv)
		वापस;

	/* Leftovers from previous error recovery */
	edev->rdma_info.exp_recovery = false;
	edev->rdma_info.qedr_dev = qedr_drv->add(edev->cdev, edev->pdev,
						 edev->ndev);
पूर्ण

अटल पूर्णांक qede_rdma_create_wq(काष्ठा qede_dev *edev)
अणु
	INIT_LIST_HEAD(&edev->rdma_info.rdma_event_list);
	kref_init(&edev->rdma_info.refcnt);
	init_completion(&edev->rdma_info.event_comp);

	edev->rdma_info.rdma_wq = create_singlethपढ़ो_workqueue("rdma_wq");
	अगर (!edev->rdma_info.rdma_wq) अणु
		DP_NOTICE(edev, "qedr: Could not create workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qede_rdma_cleanup_event(काष्ठा qede_dev *edev)
अणु
	काष्ठा list_head *head = &edev->rdma_info.rdma_event_list;
	काष्ठा qede_rdma_event_work *event_node;

	flush_workqueue(edev->rdma_info.rdma_wq);
	जबतक (!list_empty(head)) अणु
		event_node = list_entry(head->next, काष्ठा qede_rdma_event_work,
					list);
		cancel_work_sync(&event_node->work);
		list_del(&event_node->list);
		kमुक्त(event_node);
	पूर्ण
पूर्ण

अटल व्योम qede_rdma_complete_event(काष्ठा kref *ref)
अणु
	काष्ठा qede_rdma_dev *rdma_dev =
		container_of(ref, काष्ठा qede_rdma_dev, refcnt);

	/* no more events will be added after this */
	complete(&rdma_dev->event_comp);
पूर्ण

अटल व्योम qede_rdma_destroy_wq(काष्ठा qede_dev *edev)
अणु
	/* Aव्योम race with add_event flow, make sure it finishes beक्रमe
	 * we start accessing the list and cleaning up the work
	 */
	kref_put(&edev->rdma_info.refcnt, qede_rdma_complete_event);
	रुको_क्रम_completion(&edev->rdma_info.event_comp);

	qede_rdma_cleanup_event(edev);
	destroy_workqueue(edev->rdma_info.rdma_wq);
	edev->rdma_info.rdma_wq = शून्य;
पूर्ण

पूर्णांक qede_rdma_dev_add(काष्ठा qede_dev *edev, bool recovery)
अणु
	पूर्णांक rc;

	अगर (!qede_rdma_supported(edev))
		वापस 0;

	/* Cannot start qedr जबतक recovering since it wasn't fully stopped */
	अगर (recovery)
		वापस 0;

	rc = qede_rdma_create_wq(edev);
	अगर (rc)
		वापस rc;

	INIT_LIST_HEAD(&edev->rdma_info.entry);
	mutex_lock(&qedr_dev_list_lock);
	list_add_tail(&edev->rdma_info.entry, &qedr_dev_list);
	_qede_rdma_dev_add(edev);
	mutex_unlock(&qedr_dev_list_lock);

	वापस rc;
पूर्ण

अटल व्योम _qede_rdma_dev_हटाओ(काष्ठा qede_dev *edev)
अणु
	अगर (qedr_drv && qedr_drv->हटाओ && edev->rdma_info.qedr_dev)
		qedr_drv->हटाओ(edev->rdma_info.qedr_dev);
पूर्ण

व्योम qede_rdma_dev_हटाओ(काष्ठा qede_dev *edev, bool recovery)
अणु
	अगर (!qede_rdma_supported(edev))
		वापस;

	/* Cannot हटाओ qedr जबतक recovering since it wasn't fully stopped */
	अगर (!recovery) अणु
		qede_rdma_destroy_wq(edev);
		mutex_lock(&qedr_dev_list_lock);
		अगर (!edev->rdma_info.exp_recovery)
			_qede_rdma_dev_हटाओ(edev);
		edev->rdma_info.qedr_dev = शून्य;
		list_del(&edev->rdma_info.entry);
		mutex_unlock(&qedr_dev_list_lock);
	पूर्ण अन्यथा अणु
		अगर (!edev->rdma_info.exp_recovery) अणु
			mutex_lock(&qedr_dev_list_lock);
			_qede_rdma_dev_हटाओ(edev);
			mutex_unlock(&qedr_dev_list_lock);
		पूर्ण
		edev->rdma_info.exp_recovery = true;
	पूर्ण
पूर्ण

अटल व्योम _qede_rdma_dev_खोलो(काष्ठा qede_dev *edev)
अणु
	अगर (qedr_drv && edev->rdma_info.qedr_dev && qedr_drv->notअगरy)
		qedr_drv->notअगरy(edev->rdma_info.qedr_dev, QEDE_UP);
पूर्ण

अटल व्योम qede_rdma_dev_खोलो(काष्ठा qede_dev *edev)
अणु
	अगर (!qede_rdma_supported(edev))
		वापस;

	mutex_lock(&qedr_dev_list_lock);
	_qede_rdma_dev_खोलो(edev);
	mutex_unlock(&qedr_dev_list_lock);
पूर्ण

अटल व्योम _qede_rdma_dev_बंद(काष्ठा qede_dev *edev)
अणु
	अगर (qedr_drv && edev->rdma_info.qedr_dev && qedr_drv->notअगरy)
		qedr_drv->notअगरy(edev->rdma_info.qedr_dev, QEDE_DOWN);
पूर्ण

अटल व्योम qede_rdma_dev_बंद(काष्ठा qede_dev *edev)
अणु
	अगर (!qede_rdma_supported(edev))
		वापस;

	mutex_lock(&qedr_dev_list_lock);
	_qede_rdma_dev_बंद(edev);
	mutex_unlock(&qedr_dev_list_lock);
पूर्ण

अटल व्योम qede_rdma_dev_shutकरोwn(काष्ठा qede_dev *edev)
अणु
	अगर (!qede_rdma_supported(edev))
		वापस;

	mutex_lock(&qedr_dev_list_lock);
	अगर (qedr_drv && edev->rdma_info.qedr_dev && qedr_drv->notअगरy)
		qedr_drv->notअगरy(edev->rdma_info.qedr_dev, QEDE_CLOSE);
	mutex_unlock(&qedr_dev_list_lock);
पूर्ण

पूर्णांक qede_rdma_रेजिस्टर_driver(काष्ठा qedr_driver *drv)
अणु
	काष्ठा qede_dev *edev;
	u8 qedr_counter = 0;

	mutex_lock(&qedr_dev_list_lock);
	अगर (qedr_drv) अणु
		mutex_unlock(&qedr_dev_list_lock);
		वापस -EINVAL;
	पूर्ण
	qedr_drv = drv;

	list_क्रम_each_entry(edev, &qedr_dev_list, rdma_info.entry) अणु
		काष्ठा net_device *ndev;

		qedr_counter++;
		_qede_rdma_dev_add(edev);
		ndev = edev->ndev;
		अगर (netअगर_running(ndev) && netअगर_oper_up(ndev))
			_qede_rdma_dev_खोलो(edev);
	पूर्ण
	mutex_unlock(&qedr_dev_list_lock);

	pr_notice("qedr: discovered and registered %d RDMA funcs\n",
		  qedr_counter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qede_rdma_रेजिस्टर_driver);

व्योम qede_rdma_unरेजिस्टर_driver(काष्ठा qedr_driver *drv)
अणु
	काष्ठा qede_dev *edev;

	mutex_lock(&qedr_dev_list_lock);
	list_क्रम_each_entry(edev, &qedr_dev_list, rdma_info.entry) अणु
		/* If device has experienced recovery it was alपढ़ोy हटाओd */
		अगर (edev->rdma_info.qedr_dev && !edev->rdma_info.exp_recovery)
			_qede_rdma_dev_हटाओ(edev);
	पूर्ण
	qedr_drv = शून्य;
	mutex_unlock(&qedr_dev_list_lock);
पूर्ण
EXPORT_SYMBOL(qede_rdma_unरेजिस्टर_driver);

अटल व्योम qede_rdma_changeaddr(काष्ठा qede_dev *edev)
अणु
	अगर (!qede_rdma_supported(edev))
		वापस;

	अगर (qedr_drv && edev->rdma_info.qedr_dev && qedr_drv->notअगरy)
		qedr_drv->notअगरy(edev->rdma_info.qedr_dev, QEDE_CHANGE_ADDR);
पूर्ण

अटल व्योम qede_rdma_change_mtu(काष्ठा qede_dev *edev)
अणु
	अगर (qede_rdma_supported(edev)) अणु
		अगर (qedr_drv && edev->rdma_info.qedr_dev && qedr_drv->notअगरy)
			qedr_drv->notअगरy(edev->rdma_info.qedr_dev,
					 QEDE_CHANGE_MTU);
	पूर्ण
पूर्ण

अटल काष्ठा qede_rdma_event_work *
qede_rdma_get_मुक्त_event_node(काष्ठा qede_dev *edev)
अणु
	काष्ठा qede_rdma_event_work *event_node = शून्य;
	काष्ठा list_head *list_node = शून्य;
	bool found = false;

	list_क्रम_each(list_node, &edev->rdma_info.rdma_event_list) अणु
		event_node = list_entry(list_node, काष्ठा qede_rdma_event_work,
					list);
		अगर (!work_pending(&event_node->work)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		event_node = kzalloc(माप(*event_node), GFP_ATOMIC);
		अगर (!event_node) अणु
			DP_NOTICE(edev,
				  "qedr: Could not allocate memory for rdma work\n");
			वापस शून्य;
		पूर्ण
		list_add_tail(&event_node->list,
			      &edev->rdma_info.rdma_event_list);
	पूर्ण

	वापस event_node;
पूर्ण

अटल व्योम qede_rdma_handle_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qede_rdma_event_work *event_node;
	क्रमागत qede_rdma_event event;
	काष्ठा qede_dev *edev;

	event_node = container_of(work, काष्ठा qede_rdma_event_work, work);
	event = event_node->event;
	edev = event_node->ptr;

	चयन (event) अणु
	हाल QEDE_UP:
		qede_rdma_dev_खोलो(edev);
		अवरोध;
	हाल QEDE_DOWN:
		qede_rdma_dev_बंद(edev);
		अवरोध;
	हाल QEDE_CLOSE:
		qede_rdma_dev_shutकरोwn(edev);
		अवरोध;
	हाल QEDE_CHANGE_ADDR:
		qede_rdma_changeaddr(edev);
		अवरोध;
	हाल QEDE_CHANGE_MTU:
		qede_rdma_change_mtu(edev);
		अवरोध;
	शेष:
		DP_NOTICE(edev, "Invalid rdma event %d", event);
	पूर्ण
पूर्ण

अटल व्योम qede_rdma_add_event(काष्ठा qede_dev *edev,
				क्रमागत qede_rdma_event event)
अणु
	काष्ठा qede_rdma_event_work *event_node;

	/* If a recovery was experienced aव्योम adding the event */
	अगर (edev->rdma_info.exp_recovery)
		वापस;

	अगर (!edev->rdma_info.qedr_dev || !edev->rdma_info.rdma_wq)
		वापस;

	/* We करोn't want the cleanup flow to start while we're allocating and
	 * scheduling the work
	 */
	अगर (!kref_get_unless_zero(&edev->rdma_info.refcnt))
		वापस; /* alपढ़ोy being destroyed */

	event_node = qede_rdma_get_मुक्त_event_node(edev);
	अगर (!event_node)
		जाओ out;

	event_node->event = event;
	event_node->ptr = edev;

	INIT_WORK(&event_node->work, qede_rdma_handle_event);
	queue_work(edev->rdma_info.rdma_wq, &event_node->work);

out:
	kref_put(&edev->rdma_info.refcnt, qede_rdma_complete_event);
पूर्ण

व्योम qede_rdma_dev_event_खोलो(काष्ठा qede_dev *edev)
अणु
	qede_rdma_add_event(edev, QEDE_UP);
पूर्ण

व्योम qede_rdma_dev_event_बंद(काष्ठा qede_dev *edev)
अणु
	qede_rdma_add_event(edev, QEDE_DOWN);
पूर्ण

व्योम qede_rdma_event_changeaddr(काष्ठा qede_dev *edev)
अणु
	qede_rdma_add_event(edev, QEDE_CHANGE_ADDR);
पूर्ण

व्योम qede_rdma_event_change_mtu(काष्ठा qede_dev *edev)
अणु
	qede_rdma_add_event(edev, QEDE_CHANGE_MTU);
पूर्ण

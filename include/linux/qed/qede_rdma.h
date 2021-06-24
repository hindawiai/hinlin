<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित QEDE_ROCE_H
#घोषणा QEDE_ROCE_H

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

काष्ठा qedr_dev;
काष्ठा qed_dev;
काष्ठा qede_dev;

क्रमागत qede_rdma_event अणु
	QEDE_UP,
	QEDE_DOWN,
	QEDE_CHANGE_ADDR,
	QEDE_CLOSE,
	QEDE_CHANGE_MTU,
पूर्ण;

काष्ठा qede_rdma_event_work अणु
	काष्ठा list_head list;
	काष्ठा work_काष्ठा work;
	व्योम *ptr;
	क्रमागत qede_rdma_event event;
पूर्ण;

काष्ठा qedr_driver अणु
	अचिन्हित अक्षर name[32];

	काष्ठा qedr_dev* (*add)(काष्ठा qed_dev *, काष्ठा pci_dev *,
				काष्ठा net_device *);

	व्योम (*हटाओ)(काष्ठा qedr_dev *);
	व्योम (*notअगरy)(काष्ठा qedr_dev *, क्रमागत qede_rdma_event);
पूर्ण;

/* APIs क्रम RDMA driver to रेजिस्टर callback handlers,
 * which will be invoked when device is added, हटाओd, अगरup, अगरकरोwn
 */
पूर्णांक qede_rdma_रेजिस्टर_driver(काष्ठा qedr_driver *drv);
व्योम qede_rdma_unरेजिस्टर_driver(काष्ठा qedr_driver *drv);

bool qede_rdma_supported(काष्ठा qede_dev *dev);

#अगर IS_ENABLED(CONFIG_QED_RDMA)
पूर्णांक qede_rdma_dev_add(काष्ठा qede_dev *dev, bool recovery);
व्योम qede_rdma_dev_event_खोलो(काष्ठा qede_dev *dev);
व्योम qede_rdma_dev_event_बंद(काष्ठा qede_dev *dev);
व्योम qede_rdma_dev_हटाओ(काष्ठा qede_dev *dev, bool recovery);
व्योम qede_rdma_event_changeaddr(काष्ठा qede_dev *edr);
व्योम qede_rdma_event_change_mtu(काष्ठा qede_dev *edev);

#अन्यथा
अटल अंतरभूत पूर्णांक qede_rdma_dev_add(काष्ठा qede_dev *dev,
				    bool recovery)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qede_rdma_dev_event_खोलो(काष्ठा qede_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम qede_rdma_dev_event_बंद(काष्ठा qede_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम qede_rdma_dev_हटाओ(काष्ठा qede_dev *dev,
					bool recovery) अणुपूर्ण
अटल अंतरभूत व्योम qede_rdma_event_changeaddr(काष्ठा qede_dev *edr) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

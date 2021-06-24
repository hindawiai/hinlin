<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005 - 2016 Broadcom
 * All rights reserved.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>

#समावेश "be.h"
#समावेश "be_cmds.h"

अटल काष्ठा ocrdma_driver *ocrdma_drv;
अटल LIST_HEAD(be_adapter_list);
अटल DEFINE_MUTEX(be_adapter_list_lock);

अटल व्योम _be_roce_dev_add(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_dev_info dev_info;
	पूर्णांक i, num_vec;
	काष्ठा pci_dev *pdev = adapter->pdev;

	अगर (!ocrdma_drv)
		वापस;

	अगर (ocrdma_drv->be_abi_version != BE_ROCE_ABI_VERSION) अणु
		dev_warn(&pdev->dev, "Cannot initialize RoCE due to ocrdma ABI mismatch\n");
		वापस;
	पूर्ण

	अगर (pdev->device == OC_DEVICE_ID5) अणु
		/* only msix is supported on these devices */
		अगर (!msix_enabled(adapter))
			वापस;
		/* DPP region address and length */
		dev_info.dpp_unmapped_addr = pci_resource_start(pdev, 2);
		dev_info.dpp_unmapped_len = pci_resource_len(pdev, 2);
	पूर्ण अन्यथा अणु
		dev_info.dpp_unmapped_addr = 0;
		dev_info.dpp_unmapped_len = 0;
	पूर्ण
	dev_info.pdev = adapter->pdev;
	dev_info.db = adapter->db;
	dev_info.unmapped_db = adapter->roce_db.io_addr;
	dev_info.db_page_size = adapter->roce_db.size;
	dev_info.db_total_size = adapter->roce_db.total_size;
	dev_info.netdev = adapter->netdev;
	स_नकल(dev_info.mac_addr, adapter->netdev->dev_addr, ETH_ALEN);
	dev_info.dev_family = adapter->sli_family;
	अगर (msix_enabled(adapter)) अणु
		/* provide all the vectors, so that EQ creation response
		 * can decide which one to use.
		 */
		num_vec = adapter->num_msix_vec + adapter->num_msix_roce_vec;
		dev_info.पूर्णांकr_mode = BE_INTERRUPT_MODE_MSIX;
		dev_info.msix.num_vectors = min(num_vec, MAX_MSIX_VECTORS);
		/* provide start index of the vector,
		 * so in हाल of linear usage,
		 * it can use the base as starting poपूर्णांक.
		 */
		dev_info.msix.start_vector = adapter->num_evt_qs;
		क्रम (i = 0; i < dev_info.msix.num_vectors; i++) अणु
			dev_info.msix.vector_list[i] =
			    adapter->msix_entries[i].vector;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info.msix.num_vectors = 0;
		dev_info.पूर्णांकr_mode = BE_INTERRUPT_MODE_INTX;
	पूर्ण
	adapter->ocrdma_dev = ocrdma_drv->add(&dev_info);
पूर्ण

व्योम be_roce_dev_add(काष्ठा be_adapter *adapter)
अणु
	अगर (be_roce_supported(adapter)) अणु
		INIT_LIST_HEAD(&adapter->entry);
		mutex_lock(&be_adapter_list_lock);
		list_add_tail(&adapter->entry, &be_adapter_list);

		/* invoke add() routine of roce driver only अगर
		 * valid driver रेजिस्टरed with add method and add() is not yet
		 * invoked on a given adapter.
		 */
		_be_roce_dev_add(adapter);
		mutex_unlock(&be_adapter_list_lock);
	पूर्ण
पूर्ण

अटल व्योम _be_roce_dev_हटाओ(काष्ठा be_adapter *adapter)
अणु
	अगर (ocrdma_drv && ocrdma_drv->हटाओ && adapter->ocrdma_dev)
		ocrdma_drv->हटाओ(adapter->ocrdma_dev);
	adapter->ocrdma_dev = शून्य;
पूर्ण

व्योम be_roce_dev_हटाओ(काष्ठा be_adapter *adapter)
अणु
	अगर (be_roce_supported(adapter)) अणु
		mutex_lock(&be_adapter_list_lock);
		_be_roce_dev_हटाओ(adapter);
		list_del(&adapter->entry);
		mutex_unlock(&be_adapter_list_lock);
	पूर्ण
पूर्ण

व्योम be_roce_dev_shutकरोwn(काष्ठा be_adapter *adapter)
अणु
	अगर (be_roce_supported(adapter)) अणु
		mutex_lock(&be_adapter_list_lock);
		अगर (ocrdma_drv && adapter->ocrdma_dev &&
		    ocrdma_drv->state_change_handler)
			ocrdma_drv->state_change_handler(adapter->ocrdma_dev,
							 BE_DEV_SHUTDOWN);
		mutex_unlock(&be_adapter_list_lock);
	पूर्ण
पूर्ण

पूर्णांक be_roce_रेजिस्टर_driver(काष्ठा ocrdma_driver *drv)
अणु
	काष्ठा be_adapter *dev;

	mutex_lock(&be_adapter_list_lock);
	अगर (ocrdma_drv) अणु
		mutex_unlock(&be_adapter_list_lock);
		वापस -EINVAL;
	पूर्ण
	ocrdma_drv = drv;
	list_क्रम_each_entry(dev, &be_adapter_list, entry) अणु
		_be_roce_dev_add(dev);
	पूर्ण
	mutex_unlock(&be_adapter_list_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(be_roce_रेजिस्टर_driver);

व्योम be_roce_unरेजिस्टर_driver(काष्ठा ocrdma_driver *drv)
अणु
	काष्ठा be_adapter *dev;

	mutex_lock(&be_adapter_list_lock);
	list_क्रम_each_entry(dev, &be_adapter_list, entry) अणु
		अगर (dev->ocrdma_dev)
			_be_roce_dev_हटाओ(dev);
	पूर्ण
	ocrdma_drv = शून्य;
	mutex_unlock(&be_adapter_list_lock);
पूर्ण
EXPORT_SYMBOL(be_roce_unरेजिस्टर_driver);

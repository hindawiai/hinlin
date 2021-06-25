<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Parav Pandit <pandit.parav@gmail.com>
 */

#समावेश "core_priv.h"

/**
 * ib_device_रेजिस्टर_rdmacg - रेजिस्टर with rdma cgroup.
 * @device: device to रेजिस्टर to participate in resource
 *          accounting by rdma cgroup.
 *
 * Register with the rdma cgroup. Should be called beक्रमe
 * exposing rdma device to user space applications to aव्योम
 * resource accounting leak.
 */
व्योम ib_device_रेजिस्टर_rdmacg(काष्ठा ib_device *device)
अणु
	device->cg_device.name = device->name;
	rdmacg_रेजिस्टर_device(&device->cg_device);
पूर्ण

/**
 * ib_device_unरेजिस्टर_rdmacg - unरेजिस्टर with rdma cgroup.
 * @device: device to unरेजिस्टर.
 *
 * Unरेजिस्टर with the rdma cgroup. Should be called after
 * all the resources are deallocated, and after a stage when any
 * other resource allocation by user application cannot be करोne
 * क्रम this device to aव्योम any leak in accounting.
 */
व्योम ib_device_unरेजिस्टर_rdmacg(काष्ठा ib_device *device)
अणु
	rdmacg_unरेजिस्टर_device(&device->cg_device);
पूर्ण

पूर्णांक ib_rdmacg_try_अक्षरge(काष्ठा ib_rdmacg_object *cg_obj,
			 काष्ठा ib_device *device,
			 क्रमागत rdmacg_resource_type resource_index)
अणु
	वापस rdmacg_try_अक्षरge(&cg_obj->cg, &device->cg_device,
				 resource_index);
पूर्ण
EXPORT_SYMBOL(ib_rdmacg_try_अक्षरge);

व्योम ib_rdmacg_unअक्षरge(काष्ठा ib_rdmacg_object *cg_obj,
			काष्ठा ib_device *device,
			क्रमागत rdmacg_resource_type resource_index)
अणु
	rdmacg_unअक्षरge(cg_obj->cg, &device->cg_device,
			resource_index);
पूर्ण
EXPORT_SYMBOL(ib_rdmacg_unअक्षरge);

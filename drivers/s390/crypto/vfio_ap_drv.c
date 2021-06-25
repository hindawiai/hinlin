<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * VFIO based AP device driver
 *
 * Copyright IBM Corp. 2018
 *
 * Author(s): Tony Krowiak <akrowiak@linux.ibm.com>
 *	      Pierre Morel <pmorel@linux.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/facility.h>
#समावेश "vfio_ap_private.h"

#घोषणा VFIO_AP_ROOT_NAME "vfio_ap"
#घोषणा VFIO_AP_DEV_NAME "matrix"

MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("VFIO AP device driver, Copyright IBM Corp. 2018");
MODULE_LICENSE("GPL v2");

अटल काष्ठा ap_driver vfio_ap_drv;

काष्ठा ap_matrix_dev *matrix_dev;

/* Only type 10 adapters (CEX4 and later) are supported
 * by the AP matrix device driver
 */
अटल काष्ठा ap_device_id ap_queue_ids[] = अणु
	अणु .dev_type = AP_DEVICE_TYPE_CEX4,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX5,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX6,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु .dev_type = AP_DEVICE_TYPE_CEX7,
	  .match_flags = AP_DEVICE_ID_MATCH_QUEUE_TYPE पूर्ण,
	अणु /* end of sibling */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(vfio_ap, ap_queue_ids);

/**
 * vfio_ap_queue_dev_probe:
 *
 * Allocate a vfio_ap_queue काष्ठाure and associate it
 * with the device as driver_data.
 */
अटल पूर्णांक vfio_ap_queue_dev_probe(काष्ठा ap_device *apdev)
अणु
	काष्ठा vfio_ap_queue *q;

	q = kzalloc(माप(*q), GFP_KERNEL);
	अगर (!q)
		वापस -ENOMEM;
	dev_set_drvdata(&apdev->device, q);
	q->apqn = to_ap_queue(&apdev->device)->qid;
	q->saved_isc = VFIO_AP_ISC_INVALID;
	वापस 0;
पूर्ण

/**
 * vfio_ap_queue_dev_हटाओ:
 *
 * Takes the matrix lock to aव्योम actions on this device जबतक removing
 * Free the associated vfio_ap_queue काष्ठाure
 */
अटल व्योम vfio_ap_queue_dev_हटाओ(काष्ठा ap_device *apdev)
अणु
	काष्ठा vfio_ap_queue *q;

	mutex_lock(&matrix_dev->lock);
	q = dev_get_drvdata(&apdev->device);
	vfio_ap_mdev_reset_queue(q, 1);
	dev_set_drvdata(&apdev->device, शून्य);
	kमुक्त(q);
	mutex_unlock(&matrix_dev->lock);
पूर्ण

अटल व्योम vfio_ap_matrix_dev_release(काष्ठा device *dev)
अणु
	काष्ठा ap_matrix_dev *matrix_dev = dev_get_drvdata(dev);

	kमुक्त(matrix_dev);
पूर्ण

अटल पूर्णांक matrix_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा bus_type matrix_bus = अणु
	.name = "matrix",
	.match = &matrix_bus_match,
पूर्ण;

अटल काष्ठा device_driver matrix_driver = अणु
	.name = "vfio_ap",
	.bus = &matrix_bus,
	.suppress_bind_attrs = true,
पूर्ण;

अटल पूर्णांक vfio_ap_matrix_dev_create(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा device *root_device;

	root_device = root_device_रेजिस्टर(VFIO_AP_ROOT_NAME);
	अगर (IS_ERR(root_device))
		वापस PTR_ERR(root_device);

	ret = bus_रेजिस्टर(&matrix_bus);
	अगर (ret)
		जाओ bus_रेजिस्टर_err;

	matrix_dev = kzalloc(माप(*matrix_dev), GFP_KERNEL);
	अगर (!matrix_dev) अणु
		ret = -ENOMEM;
		जाओ matrix_alloc_err;
	पूर्ण

	/* Fill in config info via PQAP(QCI), अगर available */
	अगर (test_facility(12)) अणु
		ret = ap_qci(&matrix_dev->info);
		अगर (ret)
			जाओ matrix_alloc_err;
	पूर्ण

	mutex_init(&matrix_dev->lock);
	INIT_LIST_HEAD(&matrix_dev->mdev_list);

	dev_set_name(&matrix_dev->device, "%s", VFIO_AP_DEV_NAME);
	matrix_dev->device.parent = root_device;
	matrix_dev->device.bus = &matrix_bus;
	matrix_dev->device.release = vfio_ap_matrix_dev_release;
	matrix_dev->vfio_ap_drv = &vfio_ap_drv;

	ret = device_रेजिस्टर(&matrix_dev->device);
	अगर (ret)
		जाओ matrix_reg_err;

	ret = driver_रेजिस्टर(&matrix_driver);
	अगर (ret)
		जाओ matrix_drv_err;

	वापस 0;

matrix_drv_err:
	device_unरेजिस्टर(&matrix_dev->device);
matrix_reg_err:
	put_device(&matrix_dev->device);
matrix_alloc_err:
	bus_unरेजिस्टर(&matrix_bus);
bus_रेजिस्टर_err:
	root_device_unरेजिस्टर(root_device);
	वापस ret;
पूर्ण

अटल व्योम vfio_ap_matrix_dev_destroy(व्योम)
अणु
	काष्ठा device *root_device = matrix_dev->device.parent;

	driver_unरेजिस्टर(&matrix_driver);
	device_unरेजिस्टर(&matrix_dev->device);
	bus_unरेजिस्टर(&matrix_bus);
	root_device_unरेजिस्टर(root_device);
पूर्ण

अटल पूर्णांक __init vfio_ap_init(व्योम)
अणु
	पूर्णांक ret;

	/* If there are no AP inकाष्ठाions, there is nothing to pass through. */
	अगर (!ap_inकाष्ठाions_available())
		वापस -ENODEV;

	ret = vfio_ap_matrix_dev_create();
	अगर (ret)
		वापस ret;

	स_रखो(&vfio_ap_drv, 0, माप(vfio_ap_drv));
	vfio_ap_drv.probe = vfio_ap_queue_dev_probe;
	vfio_ap_drv.हटाओ = vfio_ap_queue_dev_हटाओ;
	vfio_ap_drv.ids = ap_queue_ids;

	ret = ap_driver_रेजिस्टर(&vfio_ap_drv, THIS_MODULE, VFIO_AP_DRV_NAME);
	अगर (ret) अणु
		vfio_ap_matrix_dev_destroy();
		वापस ret;
	पूर्ण

	ret = vfio_ap_mdev_रेजिस्टर();
	अगर (ret) अणु
		ap_driver_unरेजिस्टर(&vfio_ap_drv);
		vfio_ap_matrix_dev_destroy();

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास vfio_ap_निकास(व्योम)
अणु
	vfio_ap_mdev_unरेजिस्टर();
	ap_driver_unरेजिस्टर(&vfio_ap_drv);
	vfio_ap_matrix_dev_destroy();
पूर्ण

module_init(vfio_ap_init);
module_निकास(vfio_ap_निकास);

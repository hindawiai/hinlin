<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 - Virtual Open Systems
 * Author: Antonios Motakis <a.motakis@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/amba/bus.h>

#समावेश "vfio_platform_private.h"

#घोषणा DRIVER_VERSION  "0.10"
#घोषणा DRIVER_AUTHOR   "Antonios Motakis <a.motakis@virtualopensystems.com>"
#घोषणा DRIVER_DESC     "VFIO for AMBA devices - User Level meta-driver"

/* probing devices from the AMBA bus */

अटल काष्ठा resource *get_amba_resource(काष्ठा vfio_platक्रमm_device *vdev,
					  पूर्णांक i)
अणु
	काष्ठा amba_device *adev = (काष्ठा amba_device *) vdev->opaque;

	अगर (i == 0)
		वापस &adev->res;

	वापस शून्य;
पूर्ण

अटल पूर्णांक get_amba_irq(काष्ठा vfio_platक्रमm_device *vdev, पूर्णांक i)
अणु
	काष्ठा amba_device *adev = (काष्ठा amba_device *) vdev->opaque;
	पूर्णांक ret = 0;

	अगर (i < AMBA_NR_IRQS)
		ret = adev->irq[i];

	/* zero is an unset IRQ क्रम AMBA devices */
	वापस ret ? ret : -ENXIO;
पूर्ण

अटल पूर्णांक vfio_amba_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा vfio_platक्रमm_device *vdev;
	पूर्णांक ret;

	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev)
		वापस -ENOMEM;

	vdev->name = kaप्र_लिखो(GFP_KERNEL, "vfio-amba-%08x", adev->periphid);
	अगर (!vdev->name) अणु
		kमुक्त(vdev);
		वापस -ENOMEM;
	पूर्ण

	vdev->opaque = (व्योम *) adev;
	vdev->flags = VFIO_DEVICE_FLAGS_AMBA;
	vdev->get_resource = get_amba_resource;
	vdev->get_irq = get_amba_irq;
	vdev->parent_module = THIS_MODULE;
	vdev->reset_required = false;

	ret = vfio_platक्रमm_probe_common(vdev, &adev->dev);
	अगर (ret) अणु
		kमुक्त(vdev->name);
		kमुक्त(vdev);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&adev->dev, vdev);
	वापस 0;
पूर्ण

अटल व्योम vfio_amba_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा vfio_platक्रमm_device *vdev = dev_get_drvdata(&adev->dev);

	vfio_platक्रमm_हटाओ_common(vdev);
	kमुक्त(vdev->name);
	kमुक्त(vdev);
पूर्ण

अटल स्थिर काष्ठा amba_id pl330_ids[] = अणु
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, pl330_ids);

अटल काष्ठा amba_driver vfio_amba_driver = अणु
	.probe = vfio_amba_probe,
	.हटाओ = vfio_amba_हटाओ,
	.id_table = pl330_ids,
	.drv = अणु
		.name = "vfio-amba",
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

module_amba_driver(vfio_amba_driver);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 - Virtual Open Systems
 * Author: Antonios Motakis <a.motakis@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश "vfio_platform_private.h"

#घोषणा DRIVER_VERSION  "0.10"
#घोषणा DRIVER_AUTHOR   "Antonios Motakis <a.motakis@virtualopensystems.com>"
#घोषणा DRIVER_DESC     "VFIO for platform devices - User Level meta-driver"

अटल bool reset_required = true;
module_param(reset_required, bool, 0444);
MODULE_PARM_DESC(reset_required, "override reset requirement (default: 1)");

/* probing devices from the linux platक्रमm bus */

अटल काष्ठा resource *get_platक्रमm_resource(काष्ठा vfio_platक्रमm_device *vdev,
					      पूर्णांक num)
अणु
	काष्ठा platक्रमm_device *dev = (काष्ठा platक्रमm_device *) vdev->opaque;

	वापस platक्रमm_get_mem_or_io(dev, num);
पूर्ण

अटल पूर्णांक get_platक्रमm_irq(काष्ठा vfio_platक्रमm_device *vdev, पूर्णांक i)
अणु
	काष्ठा platक्रमm_device *pdev = (काष्ठा platक्रमm_device *) vdev->opaque;

	वापस platक्रमm_get_irq_optional(pdev, i);
पूर्ण

अटल पूर्णांक vfio_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vfio_platक्रमm_device *vdev;
	पूर्णांक ret;

	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev)
		वापस -ENOMEM;

	vdev->opaque = (व्योम *) pdev;
	vdev->name = pdev->name;
	vdev->flags = VFIO_DEVICE_FLAGS_PLATFORM;
	vdev->get_resource = get_platक्रमm_resource;
	vdev->get_irq = get_platक्रमm_irq;
	vdev->parent_module = THIS_MODULE;
	vdev->reset_required = reset_required;

	ret = vfio_platक्रमm_probe_common(vdev, &pdev->dev);
	अगर (ret) अणु
		kमुक्त(vdev);
		वापस ret;
	पूर्ण
	dev_set_drvdata(&pdev->dev, vdev);
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vfio_platक्रमm_device *vdev = dev_get_drvdata(&pdev->dev);

	vfio_platक्रमm_हटाओ_common(vdev);
	kमुक्त(vdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vfio_platक्रमm_driver = अणु
	.probe		= vfio_platक्रमm_probe,
	.हटाओ		= vfio_platक्रमm_हटाओ,
	.driver	= अणु
		.name	= "vfio-platform",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vfio_platक्रमm_driver);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

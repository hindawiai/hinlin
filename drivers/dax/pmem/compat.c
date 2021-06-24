<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2016 - 2018 Intel Corporation. All rights reserved. */
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/memremap.h>
#समावेश <linux/module.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/nd.h>
#समावेश "../bus.h"

/* we need the निजी definitions to implement compat suport */
#समावेश "../dax-private.h"

अटल पूर्णांक dax_pmem_compat_probe(काष्ठा device *dev)
अणु
	काष्ठा dev_dax *dev_dax = __dax_pmem_probe(dev, DEV_DAX_CLASS);
	पूर्णांक rc;

	अगर (IS_ERR(dev_dax))
		वापस PTR_ERR(dev_dax);

        अगर (!devres_खोलो_group(&dev_dax->dev, dev_dax, GFP_KERNEL))
		वापस -ENOMEM;

	device_lock(&dev_dax->dev);
	rc = dev_dax_probe(dev_dax);
	device_unlock(&dev_dax->dev);

	devres_बंद_group(&dev_dax->dev, dev_dax);
	अगर (rc)
		devres_release_group(&dev_dax->dev, dev_dax);

	वापस rc;
पूर्ण

अटल पूर्णांक dax_pmem_compat_release(काष्ठा device *dev, व्योम *data)
अणु
	device_lock(dev);
	devres_release_group(dev, to_dev_dax(dev));
	device_unlock(dev);

	वापस 0;
पूर्ण

अटल व्योम dax_pmem_compat_हटाओ(काष्ठा device *dev)
अणु
	device_क्रम_each_child(dev, शून्य, dax_pmem_compat_release);
पूर्ण

अटल काष्ठा nd_device_driver dax_pmem_compat_driver = अणु
	.probe = dax_pmem_compat_probe,
	.हटाओ = dax_pmem_compat_हटाओ,
	.drv = अणु
		.name = "dax_pmem_compat",
	पूर्ण,
	.type = ND_DRIVER_DAX_PMEM,
पूर्ण;

अटल पूर्णांक __init dax_pmem_compat_init(व्योम)
अणु
	वापस nd_driver_रेजिस्टर(&dax_pmem_compat_driver);
पूर्ण
module_init(dax_pmem_compat_init);

अटल व्योम __निकास dax_pmem_compat_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&dax_pmem_compat_driver.drv);
पूर्ण
module_निकास(dax_pmem_compat_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
MODULE_ALIAS_ND_DEVICE(ND_DEVICE_DAX_PMEM);

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2016 - 2018 Intel Corporation. All rights reserved. */
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/memremap.h>
#समावेश <linux/module.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/nd.h>
#समावेश "../bus.h"

अटल पूर्णांक dax_pmem_probe(काष्ठा device *dev)
अणु
	वापस PTR_ERR_OR_ZERO(__dax_pmem_probe(dev, DEV_DAX_BUS));
पूर्ण

अटल काष्ठा nd_device_driver dax_pmem_driver = अणु
	.probe = dax_pmem_probe,
	.drv = अणु
		.name = "dax_pmem",
	पूर्ण,
	.type = ND_DRIVER_DAX_PMEM,
पूर्ण;

अटल पूर्णांक __init dax_pmem_init(व्योम)
अणु
	वापस nd_driver_रेजिस्टर(&dax_pmem_driver);
पूर्ण
module_init(dax_pmem_init);

अटल व्योम __निकास dax_pmem_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&dax_pmem_driver.drv);
पूर्ण
module_निकास(dax_pmem_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
#अगर !IS_ENABLED(CONFIG_DEV_DAX_PMEM_COMPAT)
/* For compat builds, करोn't load this module by शेष */
MODULE_ALIAS_ND_DEVICE(ND_DEVICE_DAX_PMEM);
#पूर्ण_अगर

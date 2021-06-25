<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2016 - 2018 Intel Corporation. All rights reserved. */
#अगर_अघोषित __DAX_BUS_H__
#घोषणा __DAX_BUS_H__
#समावेश <linux/device.h>
#समावेश <linux/range.h>

काष्ठा dev_dax;
काष्ठा resource;
काष्ठा dax_device;
काष्ठा dax_region;
व्योम dax_region_put(काष्ठा dax_region *dax_region);

#घोषणा IORESOURCE_DAX_STATIC (1UL << 0)
काष्ठा dax_region *alloc_dax_region(काष्ठा device *parent, पूर्णांक region_id,
		काष्ठा range *range, पूर्णांक target_node, अचिन्हित पूर्णांक align,
		अचिन्हित दीर्घ flags);

क्रमागत dev_dax_subsys अणु
	DEV_DAX_BUS = 0, /* zeroed dev_dax_data picks this by शेष */
	DEV_DAX_CLASS,
पूर्ण;

काष्ठा dev_dax_data अणु
	काष्ठा dax_region *dax_region;
	काष्ठा dev_pagemap *pgmap;
	क्रमागत dev_dax_subsys subsys;
	resource_माप_प्रकार size;
	पूर्णांक id;
पूर्ण;

काष्ठा dev_dax *devm_create_dev_dax(काष्ठा dev_dax_data *data);

/* to be deleted when DEV_DAX_CLASS is हटाओd */
काष्ठा dev_dax *__dax_pmem_probe(काष्ठा device *dev, क्रमागत dev_dax_subsys subsys);

काष्ठा dax_device_driver अणु
	काष्ठा device_driver drv;
	काष्ठा list_head ids;
	पूर्णांक match_always;
	पूर्णांक (*probe)(काष्ठा dev_dax *dev);
	व्योम (*हटाओ)(काष्ठा dev_dax *dev);
पूर्ण;

पूर्णांक __dax_driver_रेजिस्टर(काष्ठा dax_device_driver *dax_drv,
		काष्ठा module *module, स्थिर अक्षर *mod_name);
#घोषणा dax_driver_रेजिस्टर(driver) \
	__dax_driver_रेजिस्टर(driver, THIS_MODULE, KBUILD_MODNAME)
व्योम dax_driver_unरेजिस्टर(काष्ठा dax_device_driver *dax_drv);
व्योम समाप्त_dev_dax(काष्ठा dev_dax *dev_dax);

#अगर IS_ENABLED(CONFIG_DEV_DAX_PMEM_COMPAT)
पूर्णांक dev_dax_probe(काष्ठा dev_dax *dev_dax);
#पूर्ण_अगर

/*
 * While run_dax() is potentially a generic operation that could be
 * defined in include/linux/dax.h we करोn't want to grow any users
 * outside of drivers/dax/
 */
व्योम run_dax(काष्ठा dax_device *dax_dev);

#घोषणा MODULE_ALIAS_DAX_DEVICE(type) \
	MODULE_ALIAS("dax:t" __stringअगरy(type) "*")
#घोषणा DAX_DEVICE_MODALIAS_FMT "dax:t%d"

#पूर्ण_अगर /* __DAX_BUS_H__ */

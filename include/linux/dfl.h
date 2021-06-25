<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम DFL driver and device API
 *
 * Copyright (C) 2020 Intel Corporation, Inc.
 */

#अगर_अघोषित __LINUX_DFL_H
#घोषणा __LINUX_DFL_H

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>

/**
 * क्रमागत dfl_id_type - define the DFL FIU types
 */
क्रमागत dfl_id_type अणु
	FME_ID = 0,
	PORT_ID = 1,
	DFL_ID_MAX,
पूर्ण;

/**
 * काष्ठा dfl_device - represent an dfl device on dfl bus
 *
 * @dev: generic device पूर्णांकerface.
 * @id: id of the dfl device.
 * @type: type of DFL FIU of the device. See क्रमागत dfl_id_type.
 * @feature_id: feature identअगरier local to its DFL FIU type.
 * @mmio_res: mmio resource of this dfl device.
 * @irqs: list of Linux IRQ numbers of this dfl device.
 * @num_irqs: number of IRQs supported by this dfl device.
 * @cdev: poपूर्णांकer to DFL FPGA container device this dfl device beदीर्घs to.
 * @id_entry: matched id entry in dfl driver's id table.
 */
काष्ठा dfl_device अणु
	काष्ठा device dev;
	पूर्णांक id;
	u16 type;
	u16 feature_id;
	काष्ठा resource mmio_res;
	पूर्णांक *irqs;
	अचिन्हित पूर्णांक num_irqs;
	काष्ठा dfl_fpga_cdev *cdev;
	स्थिर काष्ठा dfl_device_id *id_entry;
पूर्ण;

/**
 * काष्ठा dfl_driver - represent an dfl device driver
 *
 * @drv: driver model काष्ठाure.
 * @id_table: poपूर्णांकer to table of device IDs the driver is पूर्णांकerested in.
 *	      अणु पूर्ण member terminated.
 * @probe: mandatory callback क्रम device binding.
 * @हटाओ: callback क्रम device unbinding.
 */
काष्ठा dfl_driver अणु
	काष्ठा device_driver drv;
	स्थिर काष्ठा dfl_device_id *id_table;

	पूर्णांक (*probe)(काष्ठा dfl_device *dfl_dev);
	व्योम (*हटाओ)(काष्ठा dfl_device *dfl_dev);
पूर्ण;

#घोषणा to_dfl_dev(d) container_of(d, काष्ठा dfl_device, dev)
#घोषणा to_dfl_drv(d) container_of(d, काष्ठा dfl_driver, drv)

/*
 * use a macro to aव्योम include chaining to get THIS_MODULE.
 */
#घोषणा dfl_driver_रेजिस्टर(drv) \
	__dfl_driver_रेजिस्टर(drv, THIS_MODULE)
पूर्णांक __dfl_driver_रेजिस्टर(काष्ठा dfl_driver *dfl_drv, काष्ठा module *owner);
व्योम dfl_driver_unरेजिस्टर(काष्ठा dfl_driver *dfl_drv);

/*
 * module_dfl_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास().
 */
#घोषणा module_dfl_driver(__dfl_driver) \
	module_driver(__dfl_driver, dfl_driver_रेजिस्टर, \
		      dfl_driver_unरेजिस्टर)

#पूर्ण_अगर /* __LINUX_DFL_H */

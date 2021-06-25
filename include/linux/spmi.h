<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित _LINUX_SPMI_H
#घोषणा _LINUX_SPMI_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>

/* Maximum slave identअगरier */
#घोषणा SPMI_MAX_SLAVE_ID		16

/* SPMI Commands */
#घोषणा SPMI_CMD_EXT_WRITE		0x00
#घोषणा SPMI_CMD_RESET			0x10
#घोषणा SPMI_CMD_SLEEP			0x11
#घोषणा SPMI_CMD_SHUTDOWN		0x12
#घोषणा SPMI_CMD_WAKEUP			0x13
#घोषणा SPMI_CMD_AUTHENTICATE		0x14
#घोषणा SPMI_CMD_MSTR_READ		0x15
#घोषणा SPMI_CMD_MSTR_WRITE		0x16
#घोषणा SPMI_CMD_TRANSFER_BUS_OWNERSHIP	0x1A
#घोषणा SPMI_CMD_DDB_MASTER_READ	0x1B
#घोषणा SPMI_CMD_DDB_SLAVE_READ		0x1C
#घोषणा SPMI_CMD_EXT_READ		0x20
#घोषणा SPMI_CMD_EXT_WRITEL		0x30
#घोषणा SPMI_CMD_EXT_READL		0x38
#घोषणा SPMI_CMD_WRITE			0x40
#घोषणा SPMI_CMD_READ			0x60
#घोषणा SPMI_CMD_ZERO_WRITE		0x80

/**
 * काष्ठा spmi_device - Basic representation of an SPMI device
 * @dev:	Driver model representation of the device.
 * @ctrl:	SPMI controller managing the bus hosting this device.
 * @usid:	This devices' Unique Slave IDentअगरier.
 */
काष्ठा spmi_device अणु
	काष्ठा device		dev;
	काष्ठा spmi_controller	*ctrl;
	u8			usid;
पूर्ण;

अटल अंतरभूत काष्ठा spmi_device *to_spmi_device(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा spmi_device, dev);
पूर्ण

अटल अंतरभूत व्योम *spmi_device_get_drvdata(स्थिर काष्ठा spmi_device *sdev)
अणु
	वापस dev_get_drvdata(&sdev->dev);
पूर्ण

अटल अंतरभूत व्योम spmi_device_set_drvdata(काष्ठा spmi_device *sdev, व्योम *data)
अणु
	dev_set_drvdata(&sdev->dev, data);
पूर्ण

काष्ठा spmi_device *spmi_device_alloc(काष्ठा spmi_controller *ctrl);

अटल अंतरभूत व्योम spmi_device_put(काष्ठा spmi_device *sdev)
अणु
	अगर (sdev)
		put_device(&sdev->dev);
पूर्ण

पूर्णांक spmi_device_add(काष्ठा spmi_device *sdev);

व्योम spmi_device_हटाओ(काष्ठा spmi_device *sdev);

/**
 * काष्ठा spmi_controller - पूर्णांकerface to the SPMI master controller
 * @dev:	Driver model representation of the device.
 * @nr:		board-specअगरic number identअगरier क्रम this controller/bus
 * @cmd:	sends a non-data command sequence on the SPMI bus.
 * @पढ़ो_cmd:	sends a रेजिस्टर पढ़ो command sequence on the SPMI bus.
 * @ग_लिखो_cmd:	sends a रेजिस्टर ग_लिखो command sequence on the SPMI bus.
 */
काष्ठा spmi_controller अणु
	काष्ठा device		dev;
	अचिन्हित पूर्णांक		nr;
	पूर्णांक	(*cmd)(काष्ठा spmi_controller *ctrl, u8 opcode, u8 sid);
	पूर्णांक	(*पढ़ो_cmd)(काष्ठा spmi_controller *ctrl, u8 opcode,
			    u8 sid, u16 addr, u8 *buf, माप_प्रकार len);
	पूर्णांक	(*ग_लिखो_cmd)(काष्ठा spmi_controller *ctrl, u8 opcode,
			     u8 sid, u16 addr, स्थिर u8 *buf, माप_प्रकार len);
पूर्ण;

अटल अंतरभूत काष्ठा spmi_controller *to_spmi_controller(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा spmi_controller, dev);
पूर्ण

अटल अंतरभूत
व्योम *spmi_controller_get_drvdata(स्थिर काष्ठा spmi_controller *ctrl)
अणु
	वापस dev_get_drvdata(&ctrl->dev);
पूर्ण

अटल अंतरभूत व्योम spmi_controller_set_drvdata(काष्ठा spmi_controller *ctrl,
					       व्योम *data)
अणु
	dev_set_drvdata(&ctrl->dev, data);
पूर्ण

काष्ठा spmi_controller *spmi_controller_alloc(काष्ठा device *parent,
					      माप_प्रकार size);

/**
 * spmi_controller_put() - decrement controller refcount
 * @ctrl	SPMI controller.
 */
अटल अंतरभूत व्योम spmi_controller_put(काष्ठा spmi_controller *ctrl)
अणु
	अगर (ctrl)
		put_device(&ctrl->dev);
पूर्ण

पूर्णांक spmi_controller_add(काष्ठा spmi_controller *ctrl);
व्योम spmi_controller_हटाओ(काष्ठा spmi_controller *ctrl);

/**
 * काष्ठा spmi_driver - SPMI slave device driver
 * @driver:	SPMI device drivers should initialize name and owner field of
 *		this काष्ठाure.
 * @probe:	binds this driver to a SPMI device.
 * @हटाओ:	unbinds this driver from the SPMI device.
 *
 * If PM runसमय support is desired क्रम a slave, a device driver can call
 * pm_runसमय_put() from their probe() routine (and a balancing
 * pm_runसमय_get() in हटाओ()).  PM runसमय support क्रम a slave is
 * implemented by issuing a SLEEP command to the slave on runसमय_suspend(),
 * transitioning the slave पूर्णांकo the SLEEP state.  On runसमय_resume(), a WAKEUP
 * command is sent to the slave to bring it back to ACTIVE.
 */
काष्ठा spmi_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक	(*probe)(काष्ठा spmi_device *sdev);
	व्योम	(*हटाओ)(काष्ठा spmi_device *sdev);
	व्योम	(*shutकरोwn)(काष्ठा spmi_device *sdev);
पूर्ण;

अटल अंतरभूत काष्ठा spmi_driver *to_spmi_driver(काष्ठा device_driver *d)
अणु
	वापस container_of(d, काष्ठा spmi_driver, driver);
पूर्ण

#घोषणा spmi_driver_रेजिस्टर(sdrv) \
	__spmi_driver_रेजिस्टर(sdrv, THIS_MODULE)
पूर्णांक __spmi_driver_रेजिस्टर(काष्ठा spmi_driver *sdrv, काष्ठा module *owner);

/**
 * spmi_driver_unरेजिस्टर() - unरेजिस्टर an SPMI client driver
 * @sdrv:	the driver to unरेजिस्टर
 */
अटल अंतरभूत व्योम spmi_driver_unरेजिस्टर(काष्ठा spmi_driver *sdrv)
अणु
	अगर (sdrv)
		driver_unरेजिस्टर(&sdrv->driver);
पूर्ण

#घोषणा module_spmi_driver(__spmi_driver) \
	module_driver(__spmi_driver, spmi_driver_रेजिस्टर, \
			spmi_driver_unरेजिस्टर)

पूर्णांक spmi_रेजिस्टर_पढ़ो(काष्ठा spmi_device *sdev, u8 addr, u8 *buf);
पूर्णांक spmi_ext_रेजिस्टर_पढ़ो(काष्ठा spmi_device *sdev, u8 addr, u8 *buf,
			   माप_प्रकार len);
पूर्णांक spmi_ext_रेजिस्टर_पढ़ोl(काष्ठा spmi_device *sdev, u16 addr, u8 *buf,
			    माप_प्रकार len);
पूर्णांक spmi_रेजिस्टर_ग_लिखो(काष्ठा spmi_device *sdev, u8 addr, u8 data);
पूर्णांक spmi_रेजिस्टर_zero_ग_लिखो(काष्ठा spmi_device *sdev, u8 data);
पूर्णांक spmi_ext_रेजिस्टर_ग_लिखो(काष्ठा spmi_device *sdev, u8 addr,
			    स्थिर u8 *buf, माप_प्रकार len);
पूर्णांक spmi_ext_रेजिस्टर_ग_लिखोl(काष्ठा spmi_device *sdev, u16 addr,
			     स्थिर u8 *buf, माप_प्रकार len);
पूर्णांक spmi_command_reset(काष्ठा spmi_device *sdev);
पूर्णांक spmi_command_sleep(काष्ठा spmi_device *sdev);
पूर्णांक spmi_command_wakeup(काष्ठा spmi_device *sdev);
पूर्णांक spmi_command_shutकरोwn(काष्ठा spmi_device *sdev);

#पूर्ण_अगर

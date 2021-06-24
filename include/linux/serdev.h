<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016-2017 Linaro Ltd., Rob Herring <robh@kernel.org>
 */
#अगर_अघोषित _LINUX_SERDEV_H
#घोषणा _LINUX_SERDEV_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/termios.h>
#समावेश <linux/delay.h>

काष्ठा serdev_controller;
काष्ठा serdev_device;

/*
 * serdev device काष्ठाures
 */

/**
 * काष्ठा serdev_device_ops - Callback operations क्रम a serdev device
 * @receive_buf:	Function called with data received from device;
 *			वापसs number of bytes accepted; may sleep.
 * @ग_लिखो_wakeup:	Function called when पढ़ोy to transmit more data; must
 *			not sleep.
 */
काष्ठा serdev_device_ops अणु
	पूर्णांक (*receive_buf)(काष्ठा serdev_device *, स्थिर अचिन्हित अक्षर *, माप_प्रकार);
	व्योम (*ग_लिखो_wakeup)(काष्ठा serdev_device *);
पूर्ण;

/**
 * काष्ठा serdev_device - Basic representation of an serdev device
 * @dev:	Driver model representation of the device.
 * @nr:		Device number on serdev bus.
 * @ctrl:	serdev controller managing this device.
 * @ops:	Device operations.
 * @ग_लिखो_comp	Completion used by serdev_device_ग_लिखो() पूर्णांकernally
 * @ग_लिखो_lock	Lock to serialize access when writing data
 */
काष्ठा serdev_device अणु
	काष्ठा device dev;
	पूर्णांक nr;
	काष्ठा serdev_controller *ctrl;
	स्थिर काष्ठा serdev_device_ops *ops;
	काष्ठा completion ग_लिखो_comp;
	काष्ठा mutex ग_लिखो_lock;
पूर्ण;

अटल अंतरभूत काष्ठा serdev_device *to_serdev_device(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा serdev_device, dev);
पूर्ण

/**
 * काष्ठा serdev_device_driver - serdev slave device driver
 * @driver:	serdev device drivers should initialize name field of this
 *		काष्ठाure.
 * @probe:	binds this driver to a serdev device.
 * @हटाओ:	unbinds this driver from the serdev device.
 */
काष्ठा serdev_device_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक	(*probe)(काष्ठा serdev_device *);
	व्योम	(*हटाओ)(काष्ठा serdev_device *);
पूर्ण;

अटल अंतरभूत काष्ठा serdev_device_driver *to_serdev_device_driver(काष्ठा device_driver *d)
अणु
	वापस container_of(d, काष्ठा serdev_device_driver, driver);
पूर्ण

क्रमागत serdev_parity अणु
	SERDEV_PARITY_NONE,
	SERDEV_PARITY_EVEN,
	SERDEV_PARITY_ODD,
पूर्ण;

/*
 * serdev controller काष्ठाures
 */
काष्ठा serdev_controller_ops अणु
	पूर्णांक (*ग_लिखो_buf)(काष्ठा serdev_controller *, स्थिर अचिन्हित अक्षर *, माप_प्रकार);
	व्योम (*ग_लिखो_flush)(काष्ठा serdev_controller *);
	पूर्णांक (*ग_लिखो_room)(काष्ठा serdev_controller *);
	पूर्णांक (*खोलो)(काष्ठा serdev_controller *);
	व्योम (*बंद)(काष्ठा serdev_controller *);
	व्योम (*set_flow_control)(काष्ठा serdev_controller *, bool);
	पूर्णांक (*set_parity)(काष्ठा serdev_controller *, क्रमागत serdev_parity);
	अचिन्हित पूर्णांक (*set_baudrate)(काष्ठा serdev_controller *, अचिन्हित पूर्णांक);
	व्योम (*रुको_until_sent)(काष्ठा serdev_controller *, दीर्घ);
	पूर्णांक (*get_tiocm)(काष्ठा serdev_controller *);
	पूर्णांक (*set_tiocm)(काष्ठा serdev_controller *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
पूर्ण;

/**
 * काष्ठा serdev_controller - पूर्णांकerface to the serdev controller
 * @dev:	Driver model representation of the device.
 * @nr:		number identअगरier क्रम this controller/bus.
 * @serdev:	Poपूर्णांकer to slave device क्रम this controller.
 * @ops:	Controller operations.
 */
काष्ठा serdev_controller अणु
	काष्ठा device		dev;
	अचिन्हित पूर्णांक		nr;
	काष्ठा serdev_device	*serdev;
	स्थिर काष्ठा serdev_controller_ops *ops;
पूर्ण;

अटल अंतरभूत काष्ठा serdev_controller *to_serdev_controller(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा serdev_controller, dev);
पूर्ण

अटल अंतरभूत व्योम *serdev_device_get_drvdata(स्थिर काष्ठा serdev_device *serdev)
अणु
	वापस dev_get_drvdata(&serdev->dev);
पूर्ण

अटल अंतरभूत व्योम serdev_device_set_drvdata(काष्ठा serdev_device *serdev, व्योम *data)
अणु
	dev_set_drvdata(&serdev->dev, data);
पूर्ण

/**
 * serdev_device_put() - decrement serdev device refcount
 * @serdev	serdev device.
 */
अटल अंतरभूत व्योम serdev_device_put(काष्ठा serdev_device *serdev)
अणु
	अगर (serdev)
		put_device(&serdev->dev);
पूर्ण

अटल अंतरभूत व्योम serdev_device_set_client_ops(काष्ठा serdev_device *serdev,
					      स्थिर काष्ठा serdev_device_ops *ops)
अणु
	serdev->ops = ops;
पूर्ण

अटल अंतरभूत
व्योम *serdev_controller_get_drvdata(स्थिर काष्ठा serdev_controller *ctrl)
अणु
	वापस ctrl ? dev_get_drvdata(&ctrl->dev) : शून्य;
पूर्ण

अटल अंतरभूत व्योम serdev_controller_set_drvdata(काष्ठा serdev_controller *ctrl,
					       व्योम *data)
अणु
	dev_set_drvdata(&ctrl->dev, data);
पूर्ण

/**
 * serdev_controller_put() - decrement controller refcount
 * @ctrl	serdev controller.
 */
अटल अंतरभूत व्योम serdev_controller_put(काष्ठा serdev_controller *ctrl)
अणु
	अगर (ctrl)
		put_device(&ctrl->dev);
पूर्ण

काष्ठा serdev_device *serdev_device_alloc(काष्ठा serdev_controller *);
पूर्णांक serdev_device_add(काष्ठा serdev_device *);
व्योम serdev_device_हटाओ(काष्ठा serdev_device *);

काष्ठा serdev_controller *serdev_controller_alloc(काष्ठा device *, माप_प्रकार);
पूर्णांक serdev_controller_add(काष्ठा serdev_controller *);
व्योम serdev_controller_हटाओ(काष्ठा serdev_controller *);

अटल अंतरभूत व्योम serdev_controller_ग_लिखो_wakeup(काष्ठा serdev_controller *ctrl)
अणु
	काष्ठा serdev_device *serdev = ctrl->serdev;

	अगर (!serdev || !serdev->ops->ग_लिखो_wakeup)
		वापस;

	serdev->ops->ग_लिखो_wakeup(serdev);
पूर्ण

अटल अंतरभूत पूर्णांक serdev_controller_receive_buf(काष्ठा serdev_controller *ctrl,
					      स्थिर अचिन्हित अक्षर *data,
					      माप_प्रकार count)
अणु
	काष्ठा serdev_device *serdev = ctrl->serdev;

	अगर (!serdev || !serdev->ops->receive_buf)
		वापस 0;

	वापस serdev->ops->receive_buf(serdev, data, count);
पूर्ण

#अगर IS_ENABLED(CONFIG_SERIAL_DEV_BUS)

पूर्णांक serdev_device_खोलो(काष्ठा serdev_device *);
व्योम serdev_device_बंद(काष्ठा serdev_device *);
पूर्णांक devm_serdev_device_खोलो(काष्ठा device *, काष्ठा serdev_device *);
अचिन्हित पूर्णांक serdev_device_set_baudrate(काष्ठा serdev_device *, अचिन्हित पूर्णांक);
व्योम serdev_device_set_flow_control(काष्ठा serdev_device *, bool);
पूर्णांक serdev_device_ग_लिखो_buf(काष्ठा serdev_device *, स्थिर अचिन्हित अक्षर *, माप_प्रकार);
व्योम serdev_device_रुको_until_sent(काष्ठा serdev_device *, दीर्घ);
पूर्णांक serdev_device_get_tiocm(काष्ठा serdev_device *);
पूर्णांक serdev_device_set_tiocm(काष्ठा serdev_device *, पूर्णांक, पूर्णांक);
व्योम serdev_device_ग_लिखो_wakeup(काष्ठा serdev_device *);
पूर्णांक serdev_device_ग_लिखो(काष्ठा serdev_device *, स्थिर अचिन्हित अक्षर *, माप_प्रकार, दीर्घ);
व्योम serdev_device_ग_लिखो_flush(काष्ठा serdev_device *);
पूर्णांक serdev_device_ग_लिखो_room(काष्ठा serdev_device *);

/*
 * serdev device driver functions
 */
पूर्णांक __serdev_device_driver_रेजिस्टर(काष्ठा serdev_device_driver *, काष्ठा module *);
#घोषणा serdev_device_driver_रेजिस्टर(sdrv) \
	__serdev_device_driver_रेजिस्टर(sdrv, THIS_MODULE)

/**
 * serdev_device_driver_unरेजिस्टर() - unरेजिस्टर an serdev client driver
 * @sdrv:	the driver to unरेजिस्टर
 */
अटल अंतरभूत व्योम serdev_device_driver_unरेजिस्टर(काष्ठा serdev_device_driver *sdrv)
अणु
	अगर (sdrv)
		driver_unरेजिस्टर(&sdrv->driver);
पूर्ण

#घोषणा module_serdev_device_driver(__serdev_device_driver) \
	module_driver(__serdev_device_driver, serdev_device_driver_रेजिस्टर, \
			serdev_device_driver_unरेजिस्टर)

#अन्यथा

अटल अंतरभूत पूर्णांक serdev_device_खोलो(काष्ठा serdev_device *sdev)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम serdev_device_बंद(काष्ठा serdev_device *sdev) अणुपूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक serdev_device_set_baudrate(काष्ठा serdev_device *sdev, अचिन्हित पूर्णांक baudrate)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम serdev_device_set_flow_control(काष्ठा serdev_device *sdev, bool enable) अणुपूर्ण
अटल अंतरभूत पूर्णांक serdev_device_ग_लिखो_buf(काष्ठा serdev_device *serdev,
					  स्थिर अचिन्हित अक्षर *buf,
					  माप_प्रकार count)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम serdev_device_रुको_until_sent(काष्ठा serdev_device *sdev, दीर्घ समयout) अणुपूर्ण
अटल अंतरभूत पूर्णांक serdev_device_get_tiocm(काष्ठा serdev_device *serdev)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक serdev_device_set_tiocm(काष्ठा serdev_device *serdev, पूर्णांक set, पूर्णांक clear)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक serdev_device_ग_लिखो(काष्ठा serdev_device *sdev, स्थिर अचिन्हित अक्षर *buf,
				      माप_प्रकार count, अचिन्हित दीर्घ समयout)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम serdev_device_ग_लिखो_flush(काष्ठा serdev_device *sdev) अणुपूर्ण
अटल अंतरभूत पूर्णांक serdev_device_ग_लिखो_room(काष्ठा serdev_device *sdev)
अणु
	वापस 0;
पूर्ण

#घोषणा serdev_device_driver_रेजिस्टर(x)
#घोषणा serdev_device_driver_unरेजिस्टर(x)

#पूर्ण_अगर /* CONFIG_SERIAL_DEV_BUS */

अटल अंतरभूत bool serdev_device_get_cts(काष्ठा serdev_device *serdev)
अणु
	पूर्णांक status = serdev_device_get_tiocm(serdev);
	वापस !!(status & TIOCM_CTS);
पूर्ण

अटल अंतरभूत पूर्णांक serdev_device_रुको_क्रम_cts(काष्ठा serdev_device *serdev, bool state, पूर्णांक समयout_ms)
अणु
	अचिन्हित दीर्घ समयout;
	bool संकेत;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms);
	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		संकेत = serdev_device_get_cts(serdev);
		अगर (संकेत == state)
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल अंतरभूत पूर्णांक serdev_device_set_rts(काष्ठा serdev_device *serdev, bool enable)
अणु
	अगर (enable)
		वापस serdev_device_set_tiocm(serdev, TIOCM_RTS, 0);
	अन्यथा
		वापस serdev_device_set_tiocm(serdev, 0, TIOCM_RTS);
पूर्ण

पूर्णांक serdev_device_set_parity(काष्ठा serdev_device *serdev,
			     क्रमागत serdev_parity parity);

/*
 * serdev hooks पूर्णांकo TTY core
 */
काष्ठा tty_port;
काष्ठा tty_driver;

#अगर_घोषित CONFIG_SERIAL_DEV_CTRL_TTYPORT
काष्ठा device *serdev_tty_port_रेजिस्टर(काष्ठा tty_port *port,
					काष्ठा device *parent,
					काष्ठा tty_driver *drv, पूर्णांक idx);
पूर्णांक serdev_tty_port_unरेजिस्टर(काष्ठा tty_port *port);
#अन्यथा
अटल अंतरभूत काष्ठा device *serdev_tty_port_रेजिस्टर(काष्ठा tty_port *port,
					   काष्ठा device *parent,
					   काष्ठा tty_driver *drv, पूर्णांक idx)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
अटल अंतरभूत पूर्णांक serdev_tty_port_unरेजिस्टर(काष्ठा tty_port *port)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_SERIAL_DEV_CTRL_TTYPORT */

#पूर्ण_अगर /*_LINUX_SERDEV_H */

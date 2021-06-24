<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#अगर_अघोषित _RMI_BUS_H
#घोषणा _RMI_BUS_H

#समावेश <linux/rmi.h>

काष्ठा rmi_device;

/*
 * The पूर्णांकerrupt source count in the function descriptor can represent up to
 * 6 पूर्णांकerrupt sources in the normal manner.
 */
#घोषणा RMI_FN_MAX_IRQS	6

/**
 * काष्ठा rmi_function - represents the implementation of an RMI4
 * function क्रम a particular device (basically, a driver क्रम that RMI4 function)
 *
 * @fd: The function descriptor of the RMI function
 * @rmi_dev: Poपूर्णांकer to the RMI device associated with this function container
 * @dev: The device associated with this particular function.
 *
 * @num_of_irqs: The number of irqs needed by this function
 * @irq_pos: The position in the irq bitfield this function holds
 * @irq_mask: For convenience, can be used to mask IRQ bits off during ATTN
 * पूर्णांकerrupt handling.
 * @irqs: asचिन्हित virq numbers (up to num_of_irqs)
 *
 * @node: entry in device's list of functions
 */
काष्ठा rmi_function अणु
	काष्ठा rmi_function_descriptor fd;
	काष्ठा rmi_device *rmi_dev;
	काष्ठा device dev;
	काष्ठा list_head node;

	अचिन्हित पूर्णांक num_of_irqs;
	पूर्णांक irq[RMI_FN_MAX_IRQS];
	अचिन्हित पूर्णांक irq_pos;
	अचिन्हित दीर्घ irq_mask[];
पूर्ण;

#घोषणा to_rmi_function(d)	container_of(d, काष्ठा rmi_function, dev)

bool rmi_is_function_device(काष्ठा device *dev);

पूर्णांक __must_check rmi_रेजिस्टर_function(काष्ठा rmi_function *);
व्योम rmi_unरेजिस्टर_function(काष्ठा rmi_function *);

/**
 * काष्ठा rmi_function_handler - driver routines क्रम a particular RMI function.
 *
 * @func: The RMI function number
 * @reset: Called when a reset of the touch sensor is detected.  The routine
 * should perक्रमm any out-of-the-ordinary reset handling that might be
 * necessary.  Restoring of touch sensor configuration रेजिस्टरs should be
 * handled in the config() callback, below.
 * @config: Called when the function container is first initialized, and
 * after a reset is detected.  This routine should ग_लिखो any necessary
 * configuration settings to the device.
 * @attention: Called when the IRQ(s) क्रम the function are set by the touch
 * sensor.
 * @suspend: Should perक्रमm any required operations to suspend the particular
 * function.
 * @resume: Should perक्रमm any required operations to resume the particular
 * function.
 *
 * All callbacks are expected to वापस 0 on success, error code on failure.
 */
काष्ठा rmi_function_handler अणु
	काष्ठा device_driver driver;

	u8 func;

	पूर्णांक (*probe)(काष्ठा rmi_function *fn);
	व्योम (*हटाओ)(काष्ठा rmi_function *fn);
	पूर्णांक (*config)(काष्ठा rmi_function *fn);
	पूर्णांक (*reset)(काष्ठा rmi_function *fn);
	irqवापस_t (*attention)(पूर्णांक irq, व्योम *ctx);
	पूर्णांक (*suspend)(काष्ठा rmi_function *fn);
	पूर्णांक (*resume)(काष्ठा rmi_function *fn);
पूर्ण;

#घोषणा to_rmi_function_handler(d) \
		container_of(d, काष्ठा rmi_function_handler, driver)

पूर्णांक __must_check __rmi_रेजिस्टर_function_handler(काष्ठा rmi_function_handler *,
						 काष्ठा module *, स्थिर अक्षर *);
#घोषणा rmi_रेजिस्टर_function_handler(handler) \
	__rmi_रेजिस्टर_function_handler(handler, THIS_MODULE, KBUILD_MODNAME)

व्योम rmi_unरेजिस्टर_function_handler(काष्ठा rmi_function_handler *);

#घोषणा to_rmi_driver(d) \
	container_of(d, काष्ठा rmi_driver, driver)

#घोषणा to_rmi_device(d) container_of(d, काष्ठा rmi_device, dev)

अटल अंतरभूत काष्ठा rmi_device_platक्रमm_data *
rmi_get_platक्रमm_data(काष्ठा rmi_device *d)
अणु
	वापस &d->xport->pdata;
पूर्ण

bool rmi_is_physical_device(काष्ठा device *dev);

/**
 * rmi_reset - reset a RMI4 device
 * @d: Poपूर्णांकer to an RMI device
 *
 * Calls क्रम a reset of each function implemented by a specअगरic device.
 * Returns 0 on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक rmi_reset(काष्ठा rmi_device *d)
अणु
	वापस d->driver->reset_handler(d);
पूर्ण

/**
 * rmi_पढ़ो - पढ़ो a single byte
 * @d: Poपूर्णांकer to an RMI device
 * @addr: The address to पढ़ो from
 * @buf: The पढ़ो buffer
 *
 * Reads a single byte of data using the underlying transport protocol
 * पूर्णांकo memory poपूर्णांकed by @buf. It वापसs 0 on success or a negative
 * error code.
 */
अटल अंतरभूत पूर्णांक rmi_पढ़ो(काष्ठा rmi_device *d, u16 addr, u8 *buf)
अणु
	वापस d->xport->ops->पढ़ो_block(d->xport, addr, buf, 1);
पूर्ण

/**
 * rmi_पढ़ो_block - पढ़ो a block of bytes
 * @d: Poपूर्णांकer to an RMI device
 * @addr: The start address to पढ़ो from
 * @buf: The पढ़ो buffer
 * @len: Length of the पढ़ो buffer
 *
 * Reads a block of byte data using the underlying transport protocol
 * पूर्णांकo memory poपूर्णांकed by @buf. It वापसs 0 on success or a negative
 * error code.
 */
अटल अंतरभूत पूर्णांक rmi_पढ़ो_block(काष्ठा rmi_device *d, u16 addr,
				 व्योम *buf, माप_प्रकार len)
अणु
	वापस d->xport->ops->पढ़ो_block(d->xport, addr, buf, len);
पूर्ण

/**
 * rmi_ग_लिखो - ग_लिखो a single byte
 * @d: Poपूर्णांकer to an RMI device
 * @addr: The address to ग_लिखो to
 * @data: The data to ग_लिखो
 *
 * Writes a single byte using the underlying transport protocol. It
 * वापसs zero on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक rmi_ग_लिखो(काष्ठा rmi_device *d, u16 addr, u8 data)
अणु
	वापस d->xport->ops->ग_लिखो_block(d->xport, addr, &data, 1);
पूर्ण

/**
 * rmi_ग_लिखो_block - ग_लिखो a block of bytes
 * @d: Poपूर्णांकer to an RMI device
 * @addr: The start address to ग_लिखो to
 * @buf: The ग_लिखो buffer
 * @len: Length of the ग_लिखो buffer
 *
 * Writes a block of byte data from buf using the underlaying transport
 * protocol.  It वापसs the amount of bytes written or a negative error code.
 */
अटल अंतरभूत पूर्णांक rmi_ग_लिखो_block(काष्ठा rmi_device *d, u16 addr,
				  स्थिर व्योम *buf, माप_प्रकार len)
अणु
	वापस d->xport->ops->ग_लिखो_block(d->xport, addr, buf, len);
पूर्ण

पूर्णांक rmi_क्रम_each_dev(व्योम *data, पूर्णांक (*func)(काष्ठा device *dev, व्योम *data));

बाह्य काष्ठा bus_type rmi_bus_type;

पूर्णांक rmi_of_property_पढ़ो_u32(काष्ठा device *dev, u32 *result,
				स्थिर अक्षर *prop, bool optional);

#घोषणा RMI_DEBUG_CORE			BIT(0)
#घोषणा RMI_DEBUG_XPORT			BIT(1)
#घोषणा RMI_DEBUG_FN			BIT(2)
#घोषणा RMI_DEBUG_2D_SENSOR		BIT(3)

व्योम rmi_dbg(पूर्णांक flags, काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
#पूर्ण_अगर

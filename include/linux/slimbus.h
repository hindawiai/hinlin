<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2017, The Linux Foundation
 */

#अगर_अघोषित _LINUX_SLIMBUS_H
#घोषणा _LINUX_SLIMBUS_H
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश <linux/mod_devicetable.h>

बाह्य काष्ठा bus_type slimbus_bus;

/**
 * काष्ठा slim_eaddr - Enumeration address क्रम a SLIMbus device
 * @instance: Instance value
 * @dev_index: Device index
 * @prod_code: Product code
 * @manf_id: Manufacturer Id क्रम the device
 */
काष्ठा slim_eaddr अणु
	u8 instance;
	u8 dev_index;
	u16 prod_code;
	u16 manf_id;
पूर्ण __packed;

/**
 * क्रमागत slim_device_status - slim device status
 * @SLIM_DEVICE_STATUS_DOWN: Slim device is असलent or not reported yet.
 * @SLIM_DEVICE_STATUS_UP: Slim device is announced on the bus.
 * @SLIM_DEVICE_STATUS_RESERVED: Reserved क्रम future use.
 */
क्रमागत slim_device_status अणु
	SLIM_DEVICE_STATUS_DOWN = 0,
	SLIM_DEVICE_STATUS_UP,
	SLIM_DEVICE_STATUS_RESERVED,
पूर्ण;

काष्ठा slim_controller;

/**
 * काष्ठा slim_device - Slim device handle.
 * @dev: Driver model representation of the device.
 * @e_addr: Enumeration address of this device.
 * @status: slim device status
 * @ctrl: slim controller instance.
 * @laddr: 1-byte Logical address of this device.
 * @is_laddr_valid: indicates अगर the laddr is valid or not
 * @stream_list: List of streams on this device
 * @stream_list_lock: lock to protect the stream list
 *
 * This is the client/device handle वापसed when a SLIMbus
 * device is रेजिस्टरed with a controller.
 * Poपूर्णांकer to this काष्ठाure is used by client-driver as a handle.
 */
काष्ठा slim_device अणु
	काष्ठा device		dev;
	काष्ठा slim_eaddr	e_addr;
	काष्ठा slim_controller	*ctrl;
	क्रमागत slim_device_status	status;
	u8			laddr;
	bool			is_laddr_valid;
	काष्ठा list_head	stream_list;
	spinlock_t stream_list_lock;
पूर्ण;

#घोषणा to_slim_device(d) container_of(d, काष्ठा slim_device, dev)

/**
 * काष्ठा slim_driver - SLIMbus 'generic device' (slave) device driver
 *				(similar to 'spi_device' on SPI)
 * @probe: Binds this driver to a SLIMbus device.
 * @हटाओ: Unbinds this driver from the SLIMbus device.
 * @shutकरोwn: Standard shutकरोwn callback used during घातerकरोwn/halt.
 * @device_status: This callback is called when
 *	- The device reports present and माला_लो a laddr asचिन्हित
 *	- The device reports असलent, or the bus goes करोwn.
 * @driver: SLIMbus device drivers should initialize name and owner field of
 *	    this काष्ठाure
 * @id_table: List of SLIMbus devices supported by this driver
 */

काष्ठा slim_driver अणु
	पूर्णांक	(*probe)(काष्ठा slim_device *sl);
	व्योम	(*हटाओ)(काष्ठा slim_device *sl);
	व्योम	(*shutकरोwn)(काष्ठा slim_device *sl);
	पूर्णांक	(*device_status)(काष्ठा slim_device *sl,
				 क्रमागत slim_device_status s);
	काष्ठा device_driver		driver;
	स्थिर काष्ठा slim_device_id	*id_table;
पूर्ण;
#घोषणा to_slim_driver(d) container_of(d, काष्ठा slim_driver, driver)

/**
 * काष्ठा slim_val_inf - Slimbus value or inक्रमmation element
 * @start_offset: Specअगरies starting offset in inक्रमmation/value element map
 * @rbuf: buffer to पढ़ो the values
 * @wbuf: buffer to ग_लिखो
 * @num_bytes: upto 16. This ensures that the message will fit the slicesize
 *		per SLIMbus spec
 * @comp: completion क्रम asynchronous operations, valid only अगर TID is
 *	  required क्रम transaction, like REQUEST operations.
 *	  Rest of the transactions are synchronous anyway.
 */
काष्ठा slim_val_inf अणु
	u16			start_offset;
	u8			num_bytes;
	u8			*rbuf;
	स्थिर u8		*wbuf;
	काष्ठा	completion	*comp;
पूर्ण;

#घोषणा SLIM_DEVICE_MAX_CHANNELS	256
/* A SLIMBus Device may have frmo 0 to 31 Ports (inclusive) */
#घोषणा SLIM_DEVICE_MAX_PORTS		32

/**
 * काष्ठा slim_stream_config - SLIMbus stream configuration
 *	Configuring a stream is करोne at hw_params or prepare call
 *	from audio drivers where they have all the required inक्रमmation
 *	regarding rate, number of channels and so on.
 *	There is a 1:1 mapping of channel and ports.
 *
 * @rate: data rate
 * @bps: bits per data sample
 * @ch_count: number of channels
 * @chs: poपूर्णांकer to list of channel numbers
 * @port_mask: port mask of ports to use क्रम this stream
 * @direction: direction of the stream, SNDRV_PCM_STREAM_PLAYBACK
 *	or SNDRV_PCM_STREAM_CAPTURE.
 */
काष्ठा slim_stream_config अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक bps;
	/* MAX 256 channels */
	अचिन्हित पूर्णांक ch_count;
	अचिन्हित पूर्णांक *chs;
	/* Max 32 ports per device */
	अचिन्हित दीर्घ port_mask;
	पूर्णांक direction;
पूर्ण;

/*
 * use a macro to aव्योम include chaining to get THIS_MODULE
 */
#घोषणा slim_driver_रेजिस्टर(drv) \
	__slim_driver_रेजिस्टर(drv, THIS_MODULE)
पूर्णांक __slim_driver_रेजिस्टर(काष्ठा slim_driver *drv, काष्ठा module *owner);
व्योम slim_driver_unरेजिस्टर(काष्ठा slim_driver *drv);

/**
 * module_slim_driver() - Helper macro क्रम रेजिस्टरing a SLIMbus driver
 * @__slim_driver: slimbus_driver काष्ठा
 *
 * Helper macro क्रम SLIMbus drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_slim_driver(__slim_driver) \
	module_driver(__slim_driver, slim_driver_रेजिस्टर, \
			slim_driver_unरेजिस्टर)

अटल अंतरभूत व्योम *slim_get_devicedata(स्थिर काष्ठा slim_device *dev)
अणु
	वापस dev_get_drvdata(&dev->dev);
पूर्ण

अटल अंतरभूत व्योम slim_set_devicedata(काष्ठा slim_device *dev, व्योम *data)
अणु
	dev_set_drvdata(&dev->dev, data);
पूर्ण

काष्ठा slim_device *of_slim_get_device(काष्ठा slim_controller *ctrl,
				       काष्ठा device_node *np);
काष्ठा slim_device *slim_get_device(काष्ठा slim_controller *ctrl,
				    काष्ठा slim_eaddr *e_addr);
पूर्णांक slim_get_logical_addr(काष्ठा slim_device *sbdev);

/* Inक्रमmation Element management messages */
#घोषणा SLIM_MSG_MC_REQUEST_INFORMATION          0x20
#घोषणा SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION    0x21
#घोषणा SLIM_MSG_MC_REPLY_INFORMATION            0x24
#घोषणा SLIM_MSG_MC_CLEAR_INFORMATION            0x28
#घोषणा SLIM_MSG_MC_REPORT_INFORMATION           0x29

/* Value Element management messages */
#घोषणा SLIM_MSG_MC_REQUEST_VALUE                0x60
#घोषणा SLIM_MSG_MC_REQUEST_CHANGE_VALUE         0x61
#घोषणा SLIM_MSG_MC_REPLY_VALUE                  0x64
#घोषणा SLIM_MSG_MC_CHANGE_VALUE                 0x68

पूर्णांक slim_xfer_msg(काष्ठा slim_device *sbdev, काष्ठा slim_val_inf *msg,
		  u8 mc);
पूर्णांक slim_पढ़ोb(काष्ठा slim_device *sdev, u32 addr);
पूर्णांक slim_ग_लिखोb(काष्ठा slim_device *sdev, u32 addr, u8 value);
पूर्णांक slim_पढ़ो(काष्ठा slim_device *sdev, u32 addr, माप_प्रकार count, u8 *val);
पूर्णांक slim_ग_लिखो(काष्ठा slim_device *sdev, u32 addr, माप_प्रकार count, u8 *val);

/* SLIMbus Stream apis */
काष्ठा slim_stream_runसमय;
काष्ठा slim_stream_runसमय *slim_stream_allocate(काष्ठा slim_device *dev,
						 स्थिर अक्षर *sname);
पूर्णांक slim_stream_prepare(काष्ठा slim_stream_runसमय *stream,
			काष्ठा slim_stream_config *c);
पूर्णांक slim_stream_enable(काष्ठा slim_stream_runसमय *stream);
पूर्णांक slim_stream_disable(काष्ठा slim_stream_runसमय *stream);
पूर्णांक slim_stream_unprepare(काष्ठा slim_stream_runसमय *stream);
पूर्णांक slim_stream_मुक्त(काष्ठा slim_stream_runसमय *stream);

#पूर्ण_अगर /* _LINUX_SLIMBUS_H */

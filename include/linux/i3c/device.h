<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Cadence Design Systems Inc.
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#अगर_अघोषित I3C_DEV_H
#घोषणा I3C_DEV_H

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>

/**
 * क्रमागत i3c_error_code - I3C error codes
 *
 * These are the standard error codes as defined by the I3C specअगरication.
 * When -EIO is वापसed by the i3c_device_करो_priv_xfers() or
 * i3c_device_send_hdr_cmds() one can check the error code in
 * &काष्ठा_i3c_priv_xfer.err or &काष्ठा i3c_hdr_cmd.err to get a better idea of
 * what went wrong.
 *
 * @I3C_ERROR_UNKNOWN: unknown error, usually means the error is not I3C
 *		       related
 * @I3C_ERROR_M0: M0 error
 * @I3C_ERROR_M1: M1 error
 * @I3C_ERROR_M2: M2 error
 */
क्रमागत i3c_error_code अणु
	I3C_ERROR_UNKNOWN = 0,
	I3C_ERROR_M0 = 1,
	I3C_ERROR_M1,
	I3C_ERROR_M2,
पूर्ण;

/**
 * क्रमागत i3c_hdr_mode - HDR mode ids
 * @I3C_HDR_DDR: DDR mode
 * @I3C_HDR_TSP: TSP mode
 * @I3C_HDR_TSL: TSL mode
 */
क्रमागत i3c_hdr_mode अणु
	I3C_HDR_DDR,
	I3C_HDR_TSP,
	I3C_HDR_TSL,
पूर्ण;

/**
 * काष्ठा i3c_priv_xfer - I3C SDR निजी transfer
 * @rnw: encodes the transfer direction. true क्रम a पढ़ो, false क्रम a ग_लिखो
 * @len: transfer length in bytes of the transfer
 * @data: input/output buffer
 * @data.in: input buffer. Must poपूर्णांक to a DMA-able buffer
 * @data.out: output buffer. Must poपूर्णांक to a DMA-able buffer
 * @err: I3C error code
 */
काष्ठा i3c_priv_xfer अणु
	u8 rnw;
	u16 len;
	जोड़ अणु
		व्योम *in;
		स्थिर व्योम *out;
	पूर्ण data;
	क्रमागत i3c_error_code err;
पूर्ण;

/**
 * क्रमागत i3c_dcr - I3C DCR values
 * @I3C_DCR_GENERIC_DEVICE: generic I3C device
 */
क्रमागत i3c_dcr अणु
	I3C_DCR_GENERIC_DEVICE = 0,
पूर्ण;

#घोषणा I3C_PID_MANUF_ID(pid)		(((pid) & GENMASK_ULL(47, 33)) >> 33)
#घोषणा I3C_PID_RND_LOWER_32BITS(pid)	(!!((pid) & BIT_ULL(32)))
#घोषणा I3C_PID_RND_VAL(pid)		((pid) & GENMASK_ULL(31, 0))
#घोषणा I3C_PID_PART_ID(pid)		(((pid) & GENMASK_ULL(31, 16)) >> 16)
#घोषणा I3C_PID_INSTANCE_ID(pid)	(((pid) & GENMASK_ULL(15, 12)) >> 12)
#घोषणा I3C_PID_EXTRA_INFO(pid)		((pid) & GENMASK_ULL(11, 0))

#घोषणा I3C_BCR_DEVICE_ROLE(bcr)	((bcr) & GENMASK(7, 6))
#घोषणा I3C_BCR_I3C_SLAVE		(0 << 6)
#घोषणा I3C_BCR_I3C_MASTER		(1 << 6)
#घोषणा I3C_BCR_HDR_CAP			BIT(5)
#घोषणा I3C_BCR_BRIDGE			BIT(4)
#घोषणा I3C_BCR_OFFLINE_CAP		BIT(3)
#घोषणा I3C_BCR_IBI_PAYLOAD		BIT(2)
#घोषणा I3C_BCR_IBI_REQ_CAP		BIT(1)
#घोषणा I3C_BCR_MAX_DATA_SPEED_LIM	BIT(0)

/**
 * काष्ठा i3c_device_info - I3C device inक्रमmation
 * @pid: Provisional ID
 * @bcr: Bus Characteristic Register
 * @dcr: Device Characteristic Register
 * @अटल_addr: अटल/I2C address
 * @dyn_addr: dynamic address
 * @hdr_cap: supported HDR modes
 * @max_पढ़ो_ds: max पढ़ो speed inक्रमmation
 * @max_ग_लिखो_ds: max ग_लिखो speed inक्रमmation
 * @max_ibi_len: max IBI payload length
 * @max_पढ़ो_turnaround: max पढ़ो turn-around समय in micro-seconds
 * @max_पढ़ो_len: max निजी SDR पढ़ो length in bytes
 * @max_ग_लिखो_len: max निजी SDR ग_लिखो length in bytes
 *
 * These are all basic inक्रमmation that should be advertised by an I3C device.
 * Some of them are optional depending on the device type and device
 * capabilities.
 * For each I3C slave attached to a master with
 * i3c_master_add_i3c_dev_locked(), the core will send the relevant CCC command
 * to retrieve these data.
 */
काष्ठा i3c_device_info अणु
	u64 pid;
	u8 bcr;
	u8 dcr;
	u8 अटल_addr;
	u8 dyn_addr;
	u8 hdr_cap;
	u8 max_पढ़ो_ds;
	u8 max_ग_लिखो_ds;
	u8 max_ibi_len;
	u32 max_पढ़ो_turnaround;
	u16 max_पढ़ो_len;
	u16 max_ग_लिखो_len;
पूर्ण;

/*
 * I3C device पूर्णांकernals are kept hidden from I3C device users. It's just
 * simpler to refactor things when everything goes through getter/setters, and
 * I3C device drivers should not have to worry about पूर्णांकernal representation
 * anyway.
 */
काष्ठा i3c_device;

/* These macros should be used to i3c_device_id entries. */
#घोषणा I3C_MATCH_MANUF_AND_PART (I3C_MATCH_MANUF | I3C_MATCH_PART)

#घोषणा I3C_DEVICE(_manufid, _partid, _drvdata)				\
	अणु								\
		.match_flags = I3C_MATCH_MANUF_AND_PART,		\
		.manuf_id = _manufid,					\
		.part_id = _partid,					\
		.data = _drvdata,					\
	पूर्ण

#घोषणा I3C_DEVICE_EXTRA_INFO(_manufid, _partid, _info, _drvdata)	\
	अणु								\
		.match_flags = I3C_MATCH_MANUF_AND_PART |		\
			       I3C_MATCH_EXTRA_INFO,			\
		.manuf_id = _manufid,					\
		.part_id = _partid,					\
		.extra_info = _info,					\
		.data = _drvdata,					\
	पूर्ण

#घोषणा I3C_CLASS(_dcr, _drvdata)					\
	अणु								\
		.match_flags = I3C_MATCH_DCR,				\
		.dcr = _dcr,						\
	पूर्ण

/**
 * काष्ठा i3c_driver - I3C device driver
 * @driver: inherit from device_driver
 * @probe: I3C device probe method
 * @हटाओ: I3C device हटाओ method
 * @id_table: I3C device match table. Will be used by the framework to decide
 *	      which device to bind to this driver
 */
काष्ठा i3c_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक (*probe)(काष्ठा i3c_device *dev);
	व्योम (*हटाओ)(काष्ठा i3c_device *dev);
	स्थिर काष्ठा i3c_device_id *id_table;
पूर्ण;

अटल अंतरभूत काष्ठा i3c_driver *drv_to_i3cdrv(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा i3c_driver, driver);
पूर्ण

काष्ठा device *i3cdev_to_dev(काष्ठा i3c_device *i3cdev);
काष्ठा i3c_device *dev_to_i3cdev(काष्ठा device *dev);

स्थिर काष्ठा i3c_device_id *
i3c_device_match_id(काष्ठा i3c_device *i3cdev,
		    स्थिर काष्ठा i3c_device_id *id_table);

अटल अंतरभूत व्योम i3cdev_set_drvdata(काष्ठा i3c_device *i3cdev,
				      व्योम *data)
अणु
	काष्ठा device *dev = i3cdev_to_dev(i3cdev);

	dev_set_drvdata(dev, data);
पूर्ण

अटल अंतरभूत व्योम *i3cdev_get_drvdata(काष्ठा i3c_device *i3cdev)
अणु
	काष्ठा device *dev = i3cdev_to_dev(i3cdev);

	वापस dev_get_drvdata(dev);
पूर्ण

पूर्णांक i3c_driver_रेजिस्टर_with_owner(काष्ठा i3c_driver *drv,
				   काष्ठा module *owner);
व्योम i3c_driver_unरेजिस्टर(काष्ठा i3c_driver *drv);

#घोषणा i3c_driver_रेजिस्टर(__drv)		\
	i3c_driver_रेजिस्टर_with_owner(__drv, THIS_MODULE)

/**
 * module_i3c_driver() - Register a module providing an I3C driver
 * @__drv: the I3C driver to रेजिस्टर
 *
 * Provide generic init/निकास functions that simply रेजिस्टर/unरेजिस्टर an I3C
 * driver.
 * Should be used by any driver that करोes not require extra init/cleanup steps.
 */
#घोषणा module_i3c_driver(__drv)		\
	module_driver(__drv, i3c_driver_रेजिस्टर, i3c_driver_unरेजिस्टर)

/**
 * i3c_i2c_driver_रेजिस्टर() - Register an i2c and an i3c driver
 * @i3cdrv: the I3C driver to रेजिस्टर
 * @i2cdrv: the I2C driver to रेजिस्टर
 *
 * This function रेजिस्टरs both @i2cdev and @i3cdev, and fails अगर one of these
 * registrations fails. This is मुख्यly useful क्रम devices that support both I2C
 * and I3C modes.
 * Note that when CONFIG_I3C is not enabled, this function only रेजिस्टरs the
 * I2C driver.
 *
 * Return: 0 अगर both registrations succeeds, a negative error code otherwise.
 */
अटल अंतरभूत पूर्णांक i3c_i2c_driver_रेजिस्टर(काष्ठा i3c_driver *i3cdrv,
					  काष्ठा i2c_driver *i2cdrv)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(i2cdrv);
	अगर (ret || !IS_ENABLED(CONFIG_I3C))
		वापस ret;

	ret = i3c_driver_रेजिस्टर(i3cdrv);
	अगर (ret)
		i2c_del_driver(i2cdrv);

	वापस ret;
पूर्ण

/**
 * i3c_i2c_driver_unरेजिस्टर() - Unरेजिस्टर an i2c and an i3c driver
 * @i3cdrv: the I3C driver to रेजिस्टर
 * @i2cdrv: the I2C driver to रेजिस्टर
 *
 * This function unरेजिस्टरs both @i3cdrv and @i2cdrv.
 * Note that when CONFIG_I3C is not enabled, this function only unरेजिस्टरs the
 * @i2cdrv.
 */
अटल अंतरभूत व्योम i3c_i2c_driver_unरेजिस्टर(काष्ठा i3c_driver *i3cdrv,
					     काष्ठा i2c_driver *i2cdrv)
अणु
	अगर (IS_ENABLED(CONFIG_I3C))
		i3c_driver_unरेजिस्टर(i3cdrv);

	i2c_del_driver(i2cdrv);
पूर्ण

/**
 * module_i3c_i2c_driver() - Register a module providing an I3C and an I2C
 *			     driver
 * @__i3cdrv: the I3C driver to रेजिस्टर
 * @__i2cdrv: the I3C driver to रेजिस्टर
 *
 * Provide generic init/निकास functions that simply रेजिस्टर/unरेजिस्टर an I3C
 * and an I2C driver.
 * This macro can be used even अगर CONFIG_I3C is disabled, in this हाल, only
 * the I2C driver will be रेजिस्टरed.
 * Should be used by any driver that करोes not require extra init/cleanup steps.
 */
#घोषणा module_i3c_i2c_driver(__i3cdrv, __i2cdrv)	\
	module_driver(__i3cdrv,				\
		      i3c_i2c_driver_रेजिस्टर,		\
		      i3c_i2c_driver_unरेजिस्टर)

पूर्णांक i3c_device_करो_priv_xfers(काष्ठा i3c_device *dev,
			     काष्ठा i3c_priv_xfer *xfers,
			     पूर्णांक nxfers);

व्योम i3c_device_get_info(काष्ठा i3c_device *dev, काष्ठा i3c_device_info *info);

काष्ठा i3c_ibi_payload अणु
	अचिन्हित पूर्णांक len;
	स्थिर व्योम *data;
पूर्ण;

/**
 * काष्ठा i3c_ibi_setup - IBI setup object
 * @max_payload_len: maximum length of the payload associated to an IBI. If one
 *		     IBI appears to have a payload that is bigger than this
 *		     number, the IBI will be rejected.
 * @num_slots: number of pre-allocated IBI slots. This should be chosen so that
 *	       the प्रणाली never runs out of IBI slots, otherwise you'll lose
 *	       IBIs.
 * @handler: IBI handler, every समय an IBI is received. This handler is called
 *	     in a workqueue context. It is allowed to sleep and send new
 *	     messages on the bus, though it's recommended to keep the
 *	     processing करोne there as fast as possible to aव्योम delaying
 *	     processing of other queued on the same workqueue.
 *
 * Temporary काष्ठाure used to pass inक्रमmation to i3c_device_request_ibi().
 * This object can be allocated on the stack since i3c_device_request_ibi()
 * copies every bit of inक्रमmation and करो not use it after
 * i3c_device_request_ibi() has वापसed.
 */
काष्ठा i3c_ibi_setup अणु
	अचिन्हित पूर्णांक max_payload_len;
	अचिन्हित पूर्णांक num_slots;
	व्योम (*handler)(काष्ठा i3c_device *dev,
			स्थिर काष्ठा i3c_ibi_payload *payload);
पूर्ण;

पूर्णांक i3c_device_request_ibi(काष्ठा i3c_device *dev,
			   स्थिर काष्ठा i3c_ibi_setup *setup);
व्योम i3c_device_मुक्त_ibi(काष्ठा i3c_device *dev);
पूर्णांक i3c_device_enable_ibi(काष्ठा i3c_device *dev);
पूर्णांक i3c_device_disable_ibi(काष्ठा i3c_device *dev);

#पूर्ण_अगर /* I3C_DEV_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * i2c.h - definitions क्रम the Linux i2c bus पूर्णांकerface
 * Copyright (C) 1995-2000 Simon G. Vogl
 * Copyright (C) 2013-2019 Wolfram Sang <wsa@kernel.org>
 *
 * With some changes from Kyथघsti Mथअlkki <kmalkki@cc.hut.fi> and
 * Froकरो Looijaard <froकरोl@dds.nl>
 */
#अगर_अघोषित _LINUX_I2C_H
#घोषणा _LINUX_I2C_H

#समावेश <linux/acpi.h>		/* क्रम acpi_handle */
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/device.h>	/* क्रम काष्ठा device */
#समावेश <linux/sched.h>	/* क्रम completion */
#समावेश <linux/mutex.h>
#समावेश <linux/rपंचांगutex.h>
#समावेश <linux/irqकरोमुख्य.h>		/* क्रम Host Notअगरy IRQ */
#समावेश <linux/of.h>		/* क्रम काष्ठा device_node */
#समावेश <linux/swab.h>		/* क्रम swab16 */
#समावेश <uapi/linux/i2c.h>

बाह्य काष्ठा bus_type i2c_bus_type;
बाह्य काष्ठा device_type i2c_adapter_type;
बाह्य काष्ठा device_type i2c_client_type;

/* --- General options ------------------------------------------------	*/

काष्ठा i2c_msg;
काष्ठा i2c_algorithm;
काष्ठा i2c_adapter;
काष्ठा i2c_client;
काष्ठा i2c_driver;
काष्ठा i2c_device_identity;
जोड़ i2c_smbus_data;
काष्ठा i2c_board_info;
क्रमागत i2c_slave_event;
प्रकार पूर्णांक (*i2c_slave_cb_t)(काष्ठा i2c_client *client,
			      क्रमागत i2c_slave_event event, u8 *val);

/* I2C Frequency Modes */
#घोषणा I2C_MAX_STANDARD_MODE_FREQ	100000
#घोषणा I2C_MAX_FAST_MODE_FREQ		400000
#घोषणा I2C_MAX_FAST_MODE_PLUS_FREQ	1000000
#घोषणा I2C_MAX_TURBO_MODE_FREQ		1400000
#घोषणा I2C_MAX_HIGH_SPEED_MODE_FREQ	3400000
#घोषणा I2C_MAX_ULTRA_FAST_MODE_FREQ	5000000

काष्ठा module;
काष्ठा property_entry;

#अगर IS_ENABLED(CONFIG_I2C)
/* Return the Frequency mode string based on the bus frequency */
स्थिर अक्षर *i2c_freq_mode_string(u32 bus_freq_hz);

/*
 * The master routines are the ones normally used to transmit data to devices
 * on a bus (or पढ़ो from them). Apart from two basic transfer functions to
 * transmit one message at a समय, a more complex version can be used to
 * transmit an arbitrary number of messages without पूर्णांकerruption.
 * @count must be less than 64k since msg.len is u16.
 */
पूर्णांक i2c_transfer_buffer_flags(स्थिर काष्ठा i2c_client *client,
			      अक्षर *buf, पूर्णांक count, u16 flags);

/**
 * i2c_master_recv - issue a single I2C message in master receive mode
 * @client: Handle to slave device
 * @buf: Where to store data पढ़ो from slave
 * @count: How many bytes to पढ़ो, must be less than 64k since msg.len is u16
 *
 * Returns negative त्रुटि_सं, or अन्यथा the number of bytes पढ़ो.
 */
अटल अंतरभूत पूर्णांक i2c_master_recv(स्थिर काष्ठा i2c_client *client,
				  अक्षर *buf, पूर्णांक count)
अणु
	वापस i2c_transfer_buffer_flags(client, buf, count, I2C_M_RD);
पूर्ण;

/**
 * i2c_master_recv_dmasafe - issue a single I2C message in master receive mode
 *			     using a DMA safe buffer
 * @client: Handle to slave device
 * @buf: Where to store data पढ़ो from slave, must be safe to use with DMA
 * @count: How many bytes to पढ़ो, must be less than 64k since msg.len is u16
 *
 * Returns negative त्रुटि_सं, or अन्यथा the number of bytes पढ़ो.
 */
अटल अंतरभूत पूर्णांक i2c_master_recv_dmasafe(स्थिर काष्ठा i2c_client *client,
					  अक्षर *buf, पूर्णांक count)
अणु
	वापस i2c_transfer_buffer_flags(client, buf, count,
					 I2C_M_RD | I2C_M_DMA_SAFE);
पूर्ण;

/**
 * i2c_master_send - issue a single I2C message in master transmit mode
 * @client: Handle to slave device
 * @buf: Data that will be written to the slave
 * @count: How many bytes to ग_लिखो, must be less than 64k since msg.len is u16
 *
 * Returns negative त्रुटि_सं, or अन्यथा the number of bytes written.
 */
अटल अंतरभूत पूर्णांक i2c_master_send(स्थिर काष्ठा i2c_client *client,
				  स्थिर अक्षर *buf, पूर्णांक count)
अणु
	वापस i2c_transfer_buffer_flags(client, (अक्षर *)buf, count, 0);
पूर्ण;

/**
 * i2c_master_send_dmasafe - issue a single I2C message in master transmit mode
 *			     using a DMA safe buffer
 * @client: Handle to slave device
 * @buf: Data that will be written to the slave, must be safe to use with DMA
 * @count: How many bytes to ग_लिखो, must be less than 64k since msg.len is u16
 *
 * Returns negative त्रुटि_सं, or अन्यथा the number of bytes written.
 */
अटल अंतरभूत पूर्णांक i2c_master_send_dmasafe(स्थिर काष्ठा i2c_client *client,
					  स्थिर अक्षर *buf, पूर्णांक count)
अणु
	वापस i2c_transfer_buffer_flags(client, (अक्षर *)buf, count,
					 I2C_M_DMA_SAFE);
पूर्ण;

/* Transfer num messages.
 */
पूर्णांक i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num);
/* Unlocked flavor */
पूर्णांक __i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num);

/* This is the very generalized SMBus access routine. You probably करो not
   want to use this, though; one of the functions below may be much easier,
   and probably just as fast.
   Note that we use i2c_adapter here, because you करो not need a specअगरic
   smbus adapter to call this function. */
s32 i2c_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
		   अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		   पूर्णांक protocol, जोड़ i2c_smbus_data *data);

/* Unlocked flavor */
s32 __i2c_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
		     अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		     पूर्णांक protocol, जोड़ i2c_smbus_data *data);

/* Now follow the 'nice' access routines. These also करोcument the calling
   conventions of i2c_smbus_xfer. */

s32 i2c_smbus_पढ़ो_byte(स्थिर काष्ठा i2c_client *client);
s32 i2c_smbus_ग_लिखो_byte(स्थिर काष्ठा i2c_client *client, u8 value);
s32 i2c_smbus_पढ़ो_byte_data(स्थिर काष्ठा i2c_client *client, u8 command);
s32 i2c_smbus_ग_लिखो_byte_data(स्थिर काष्ठा i2c_client *client,
			      u8 command, u8 value);
s32 i2c_smbus_पढ़ो_word_data(स्थिर काष्ठा i2c_client *client, u8 command);
s32 i2c_smbus_ग_लिखो_word_data(स्थिर काष्ठा i2c_client *client,
			      u8 command, u16 value);

अटल अंतरभूत s32
i2c_smbus_पढ़ो_word_swapped(स्थिर काष्ठा i2c_client *client, u8 command)
अणु
	s32 value = i2c_smbus_पढ़ो_word_data(client, command);

	वापस (value < 0) ? value : swab16(value);
पूर्ण

अटल अंतरभूत s32
i2c_smbus_ग_लिखो_word_swapped(स्थिर काष्ठा i2c_client *client,
			     u8 command, u16 value)
अणु
	वापस i2c_smbus_ग_लिखो_word_data(client, command, swab16(value));
पूर्ण

/* Returns the number of पढ़ो bytes */
s32 i2c_smbus_पढ़ो_block_data(स्थिर काष्ठा i2c_client *client,
			      u8 command, u8 *values);
s32 i2c_smbus_ग_लिखो_block_data(स्थिर काष्ठा i2c_client *client,
			       u8 command, u8 length, स्थिर u8 *values);
/* Returns the number of पढ़ो bytes */
s32 i2c_smbus_पढ़ो_i2c_block_data(स्थिर काष्ठा i2c_client *client,
				  u8 command, u8 length, u8 *values);
s32 i2c_smbus_ग_लिखो_i2c_block_data(स्थिर काष्ठा i2c_client *client,
				   u8 command, u8 length, स्थिर u8 *values);
s32 i2c_smbus_पढ़ो_i2c_block_data_or_emulated(स्थिर काष्ठा i2c_client *client,
					      u8 command, u8 length,
					      u8 *values);
पूर्णांक i2c_get_device_id(स्थिर काष्ठा i2c_client *client,
		      काष्ठा i2c_device_identity *id);
#पूर्ण_अगर /* I2C */

/**
 * काष्ठा i2c_device_identity - i2c client device identअगरication
 * @manufacturer_id: 0 - 4095, database मुख्यtained by NXP
 * @part_id: 0 - 511, according to manufacturer
 * @die_revision: 0 - 7, according to manufacturer
 */
काष्ठा i2c_device_identity अणु
	u16 manufacturer_id;
#घोषणा I2C_DEVICE_ID_NXP_SEMICONDUCTORS                0
#घोषणा I2C_DEVICE_ID_NXP_SEMICONDUCTORS_1              1
#घोषणा I2C_DEVICE_ID_NXP_SEMICONDUCTORS_2              2
#घोषणा I2C_DEVICE_ID_NXP_SEMICONDUCTORS_3              3
#घोषणा I2C_DEVICE_ID_RAMTRON_INTERNATIONAL             4
#घोषणा I2C_DEVICE_ID_ANALOG_DEVICES                    5
#घोषणा I2C_DEVICE_ID_STMICROELECTRONICS                6
#घोषणा I2C_DEVICE_ID_ON_SEMICONDUCTOR                  7
#घोषणा I2C_DEVICE_ID_SPRINTEK_CORPORATION              8
#घोषणा I2C_DEVICE_ID_ESPROS_PHOTONICS_AG               9
#घोषणा I2C_DEVICE_ID_FUJITSU_SEMICONDUCTOR            10
#घोषणा I2C_DEVICE_ID_FLIR                             11
#घोषणा I2C_DEVICE_ID_O2MICRO                          12
#घोषणा I2C_DEVICE_ID_ATMEL                            13
#घोषणा I2C_DEVICE_ID_NONE                         0xffff
	u16 part_id;
	u8 die_revision;
पूर्ण;

क्रमागत i2c_alert_protocol अणु
	I2C_PROTOCOL_SMBUS_ALERT,
	I2C_PROTOCOL_SMBUS_HOST_NOTIFY,
पूर्ण;

/**
 * काष्ठा i2c_driver - represent an I2C device driver
 * @class: What kind of i2c device we instantiate (क्रम detect)
 * @probe: Callback क्रम device binding - soon to be deprecated
 * @probe_new: New callback क्रम device binding
 * @हटाओ: Callback क्रम device unbinding
 * @shutकरोwn: Callback क्रम device shutकरोwn
 * @alert: Alert callback, क्रम example क्रम the SMBus alert protocol
 * @command: Callback क्रम bus-wide संकेतing (optional)
 * @driver: Device driver model driver
 * @id_table: List of I2C devices supported by this driver
 * @detect: Callback क्रम device detection
 * @address_list: The I2C addresses to probe (क्रम detect)
 * @clients: List of detected clients we created (क्रम i2c-core use only)
 *
 * The driver.owner field should be set to the module owner of this driver.
 * The driver.name field should be set to the name of this driver.
 *
 * For स्वतःmatic device detection, both @detect and @address_list must
 * be defined. @class should also be set, otherwise only devices क्रमced
 * with module parameters will be created. The detect function must
 * fill at least the name field of the i2c_board_info काष्ठाure it is
 * handed upon successful detection, and possibly also the flags field.
 *
 * If @detect is missing, the driver will still work fine क्रम क्रमागतerated
 * devices. Detected devices simply won't be supported. This is expected
 * क्रम the many I2C/SMBus devices which can't be detected reliably, and
 * the ones which can always be क्रमागतerated in practice.
 *
 * The i2c_client काष्ठाure which is handed to the @detect callback is
 * not a real i2c_client. It is initialized just enough so that you can
 * call i2c_smbus_पढ़ो_byte_data and मित्रs on it. Don't करो anything
 * अन्यथा with it. In particular, calling dev_dbg and मित्रs on it is
 * not allowed.
 */
काष्ठा i2c_driver अणु
	अचिन्हित पूर्णांक class;

	/* Standard driver model पूर्णांकerfaces */
	पूर्णांक (*probe)(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id);
	पूर्णांक (*हटाओ)(काष्ठा i2c_client *client);

	/* New driver model पूर्णांकerface to aid the seamless removal of the
	 * current probe()'s, more commonly unused than used second parameter.
	 */
	पूर्णांक (*probe_new)(काष्ठा i2c_client *client);

	/* driver model पूर्णांकerfaces that करोn't relate to क्रमागतeration  */
	व्योम (*shutकरोwn)(काष्ठा i2c_client *client);

	/* Alert callback, क्रम example क्रम the SMBus alert protocol.
	 * The क्रमmat and meaning of the data value depends on the protocol.
	 * For the SMBus alert protocol, there is a single bit of data passed
	 * as the alert response's low bit ("event flag").
	 * For the SMBus Host Notअगरy protocol, the data corresponds to the
	 * 16-bit payload data reported by the slave device acting as master.
	 */
	व्योम (*alert)(काष्ठा i2c_client *client, क्रमागत i2c_alert_protocol protocol,
		      अचिन्हित पूर्णांक data);

	/* a ioctl like command that can be used to perक्रमm specअगरic functions
	 * with the device.
	 */
	पूर्णांक (*command)(काष्ठा i2c_client *client, अचिन्हित पूर्णांक cmd, व्योम *arg);

	काष्ठा device_driver driver;
	स्थिर काष्ठा i2c_device_id *id_table;

	/* Device detection callback क्रम स्वतःmatic device creation */
	पूर्णांक (*detect)(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info);
	स्थिर अचिन्हित लघु *address_list;
	काष्ठा list_head clients;
पूर्ण;
#घोषणा to_i2c_driver(d) container_of(d, काष्ठा i2c_driver, driver)

/**
 * काष्ठा i2c_client - represent an I2C slave device
 * @flags: see I2C_CLIENT_* क्रम possible flags
 * @addr: Address used on the I2C bus connected to the parent adapter.
 * @name: Indicates the type of the device, usually a chip name that's
 *	generic enough to hide second-sourcing and compatible revisions.
 * @adapter: manages the bus segment hosting this I2C device
 * @dev: Driver model device node क्रम the slave.
 * @init_irq: IRQ that was set at initialization
 * @irq: indicates the IRQ generated by this device (अगर any)
 * @detected: member of an i2c_driver.clients list or i2c-core's
 *	userspace_devices list
 * @slave_cb: Callback when I2C slave mode of an adapter is used. The adapter
 *	calls it to pass on slave events to the slave driver.
 * @devres_group_id: id of the devres group that will be created क्रम resources
 *	acquired when probing this device.
 *
 * An i2c_client identअगरies a single device (i.e. chip) connected to an
 * i2c bus. The behaviour exposed to Linux is defined by the driver
 * managing the device.
 */
काष्ठा i2c_client अणु
	अचिन्हित लघु flags;		/* भाग., see below		*/
#घोषणा I2C_CLIENT_PEC		0x04	/* Use Packet Error Checking */
#घोषणा I2C_CLIENT_TEN		0x10	/* we have a ten bit chip address */
					/* Must equal I2C_M_TEN below */
#घोषणा I2C_CLIENT_SLAVE	0x20	/* we are the slave */
#घोषणा I2C_CLIENT_HOST_NOTIFY	0x40	/* We want to use I2C host notअगरy */
#घोषणा I2C_CLIENT_WAKE		0x80	/* क्रम board_info; true अगरf can wake */
#घोषणा I2C_CLIENT_SCCB		0x9000	/* Use Omnivision SCCB protocol */
					/* Must match I2C_M_STOP|IGNORE_NAK */

	अचिन्हित लघु addr;		/* chip address - NOTE: 7bit	*/
					/* addresses are stored in the	*/
					/* _LOWER_ 7 bits		*/
	अक्षर name[I2C_NAME_SIZE];
	काष्ठा i2c_adapter *adapter;	/* the adapter we sit on	*/
	काष्ठा device dev;		/* the device काष्ठाure		*/
	पूर्णांक init_irq;			/* irq set at initialization	*/
	पूर्णांक irq;			/* irq issued by device		*/
	काष्ठा list_head detected;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	i2c_slave_cb_t slave_cb;	/* callback क्रम slave mode	*/
#पूर्ण_अगर
	व्योम *devres_group_id;		/* ID of probe devres group	*/
पूर्ण;
#घोषणा to_i2c_client(d) container_of(d, काष्ठा i2c_client, dev)

काष्ठा i2c_client *i2c_verअगरy_client(काष्ठा device *dev);
काष्ठा i2c_adapter *i2c_verअगरy_adapter(काष्ठा device *dev);
स्थिर काष्ठा i2c_device_id *i2c_match_id(स्थिर काष्ठा i2c_device_id *id,
					 स्थिर काष्ठा i2c_client *client);

अटल अंतरभूत काष्ठा i2c_client *kobj_to_i2c_client(काष्ठा kobject *kobj)
अणु
	काष्ठा device * स्थिर dev = kobj_to_dev(kobj);
	वापस to_i2c_client(dev);
पूर्ण

अटल अंतरभूत व्योम *i2c_get_clientdata(स्थिर काष्ठा i2c_client *client)
अणु
	वापस dev_get_drvdata(&client->dev);
पूर्ण

अटल अंतरभूत व्योम i2c_set_clientdata(काष्ठा i2c_client *client, व्योम *data)
अणु
	dev_set_drvdata(&client->dev, data);
पूर्ण

/* I2C slave support */

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
क्रमागत i2c_slave_event अणु
	I2C_SLAVE_READ_REQUESTED,
	I2C_SLAVE_WRITE_REQUESTED,
	I2C_SLAVE_READ_PROCESSED,
	I2C_SLAVE_WRITE_RECEIVED,
	I2C_SLAVE_STOP,
पूर्ण;

पूर्णांक i2c_slave_रेजिस्टर(काष्ठा i2c_client *client, i2c_slave_cb_t slave_cb);
पूर्णांक i2c_slave_unरेजिस्टर(काष्ठा i2c_client *client);
bool i2c_detect_slave_mode(काष्ठा device *dev);

अटल अंतरभूत पूर्णांक i2c_slave_event(काष्ठा i2c_client *client,
				  क्रमागत i2c_slave_event event, u8 *val)
अणु
	वापस client->slave_cb(client, event, val);
पूर्ण
#अन्यथा
अटल अंतरभूत bool i2c_detect_slave_mode(काष्ठा device *dev) अणु वापस false; पूर्ण
#पूर्ण_अगर

/**
 * काष्ठा i2c_board_info - ढाँचा क्रम device creation
 * @type: chip type, to initialize i2c_client.name
 * @flags: to initialize i2c_client.flags
 * @addr: stored in i2c_client.addr
 * @dev_name: Overrides the शेष <busnr>-<addr> dev_name अगर set
 * @platक्रमm_data: stored in i2c_client.dev.platक्रमm_data
 * @of_node: poपूर्णांकer to OpenFirmware device node
 * @fwnode: device node supplied by the platक्रमm firmware
 * @swnode: software node क्रम the device
 * @resources: resources associated with the device
 * @num_resources: number of resources in the @resources array
 * @irq: stored in i2c_client.irq
 *
 * I2C करोesn't actually support hardware probing, although controllers and
 * devices may be able to use I2C_SMBUS_QUICK to tell whether or not there's
 * a device at a given address.  Drivers commonly need more inक्रमmation than
 * that, such as chip type, configuration, associated IRQ, and so on.
 *
 * i2c_board_info is used to build tables of inक्रमmation listing I2C devices
 * that are present.  This inक्रमmation is used to grow the driver model tree.
 * For मुख्यboards this is करोne अटलally using i2c_रेजिस्टर_board_info();
 * bus numbers identअगरy adapters that aren't yet available.  For add-on boards,
 * i2c_new_client_device() करोes this dynamically with the adapter alपढ़ोy known.
 */
काष्ठा i2c_board_info अणु
	अक्षर		type[I2C_NAME_SIZE];
	अचिन्हित लघु	flags;
	अचिन्हित लघु	addr;
	स्थिर अक्षर	*dev_name;
	व्योम		*platक्रमm_data;
	काष्ठा device_node *of_node;
	काष्ठा fwnode_handle *fwnode;
	स्थिर काष्ठा software_node *swnode;
	स्थिर काष्ठा resource *resources;
	अचिन्हित पूर्णांक	num_resources;
	पूर्णांक		irq;
पूर्ण;

/**
 * I2C_BOARD_INFO - macro used to list an i2c device and its address
 * @dev_type: identअगरies the device type
 * @dev_addr: the device's address on the bus.
 *
 * This macro initializes essential fields of a काष्ठा i2c_board_info,
 * declaring what has been provided on a particular board.  Optional
 * fields (such as associated irq, or device-specअगरic platक्रमm_data)
 * are provided using conventional syntax.
 */
#घोषणा I2C_BOARD_INFO(dev_type, dev_addr) \
	.type = dev_type, .addr = (dev_addr)


#अगर IS_ENABLED(CONFIG_I2C)
/*
 * Add-on boards should रेजिस्टर/unरेजिस्टर their devices; e.g. a board
 * with पूर्णांकegrated I2C, a config eeprom, sensors, and a codec that's
 * used in conjunction with the primary hardware.
 */
काष्ठा i2c_client *
i2c_new_client_device(काष्ठा i2c_adapter *adap, काष्ठा i2c_board_info स्थिर *info);

/* If you करोn't know the exact address of an I2C device, use this variant
 * instead, which can probe क्रम device presence in a list of possible
 * addresses. The "probe" callback function is optional. If it is provided,
 * it must वापस 1 on successful probe, 0 otherwise. If it is not provided,
 * a शेष probing method is used.
 */
काष्ठा i2c_client *
i2c_new_scanned_device(काष्ठा i2c_adapter *adap,
		       काष्ठा i2c_board_info *info,
		       अचिन्हित लघु स्थिर *addr_list,
		       पूर्णांक (*probe)(काष्ठा i2c_adapter *adap, अचिन्हित लघु addr));

/* Common custom probe functions */
पूर्णांक i2c_probe_func_quick_पढ़ो(काष्ठा i2c_adapter *adap, अचिन्हित लघु addr);

काष्ठा i2c_client *
i2c_new_dummy_device(काष्ठा i2c_adapter *adapter, u16 address);

काष्ठा i2c_client *
devm_i2c_new_dummy_device(काष्ठा device *dev, काष्ठा i2c_adapter *adap, u16 address);

काष्ठा i2c_client *
i2c_new_ancillary_device(काष्ठा i2c_client *client,
			 स्थिर अक्षर *name,
			 u16 शेष_addr);

व्योम i2c_unरेजिस्टर_device(काष्ठा i2c_client *client);
#पूर्ण_अगर /* I2C */

/* Mainboard arch_initcall() code should रेजिस्टर all its I2C devices.
 * This is करोne at arch_initcall समय, beक्रमe declaring any i2c adapters.
 * Modules क्रम add-on boards must use other calls.
 */
#अगर_घोषित CONFIG_I2C_BOARDINFO
पूर्णांक
i2c_रेजिस्टर_board_info(पूर्णांक busnum, काष्ठा i2c_board_info स्थिर *info,
			अचिन्हित n);
#अन्यथा
अटल अंतरभूत पूर्णांक
i2c_रेजिस्टर_board_info(पूर्णांक busnum, काष्ठा i2c_board_info स्थिर *info,
			अचिन्हित n)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* I2C_BOARDINFO */

/**
 * काष्ठा i2c_algorithm - represent I2C transfer method
 * @master_xfer: Issue a set of i2c transactions to the given I2C adapter
 *   defined by the msgs array, with num messages available to transfer via
 *   the adapter specअगरied by adap.
 * @master_xfer_atomic: same as @master_xfer. Yet, only using atomic context
 *   so e.g. PMICs can be accessed very late beक्रमe shutकरोwn. Optional.
 * @smbus_xfer: Issue smbus transactions to the given I2C adapter. If this
 *   is not present, then the bus layer will try and convert the SMBus calls
 *   पूर्णांकo I2C transfers instead.
 * @smbus_xfer_atomic: same as @smbus_xfer. Yet, only using atomic context
 *   so e.g. PMICs can be accessed very late beक्रमe shutकरोwn. Optional.
 * @functionality: Return the flags that this algorithm/adapter pair supports
 *   from the ``I2C_FUNC_*`` flags.
 * @reg_slave: Register given client to I2C slave mode of this adapter
 * @unreg_slave: Unरेजिस्टर given client from I2C slave mode of this adapter
 *
 * The following काष्ठाs are क्रम those who like to implement new bus drivers:
 * i2c_algorithm is the पूर्णांकerface to a class of hardware solutions which can
 * be addressed using the same bus algorithms - i.e. bit-banging or the PCF8584
 * to name two of the most common.
 *
 * The वापस codes from the ``master_xferअणु_atomicपूर्ण`` fields should indicate the
 * type of error code that occurred during the transfer, as करोcumented in the
 * Kernel Documentation file Documentation/i2c/fault-codes.rst.
 */
काष्ठा i2c_algorithm अणु
	/*
	 * If an adapter algorithm can't करो I2C-level access, set master_xfer
	 * to शून्य. If an adapter algorithm can करो SMBus access, set
	 * smbus_xfer. If set to शून्य, the SMBus protocol is simulated
	 * using common I2C messages.
	 *
	 * master_xfer should वापस the number of messages successfully
	 * processed, or a negative value on error
	 */
	पूर्णांक (*master_xfer)(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			   पूर्णांक num);
	पूर्णांक (*master_xfer_atomic)(काष्ठा i2c_adapter *adap,
				   काष्ठा i2c_msg *msgs, पूर्णांक num);
	पूर्णांक (*smbus_xfer)(काष्ठा i2c_adapter *adap, u16 addr,
			  अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			  u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data);
	पूर्णांक (*smbus_xfer_atomic)(काष्ठा i2c_adapter *adap, u16 addr,
				 अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
				 u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data);

	/* To determine what the adapter supports */
	u32 (*functionality)(काष्ठा i2c_adapter *adap);

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	पूर्णांक (*reg_slave)(काष्ठा i2c_client *client);
	पूर्णांक (*unreg_slave)(काष्ठा i2c_client *client);
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा i2c_lock_operations - represent I2C locking operations
 * @lock_bus: Get exclusive access to an I2C bus segment
 * @trylock_bus: Try to get exclusive access to an I2C bus segment
 * @unlock_bus: Release exclusive access to an I2C bus segment
 *
 * The मुख्य operations are wrapped by i2c_lock_bus and i2c_unlock_bus.
 */
काष्ठा i2c_lock_operations अणु
	व्योम (*lock_bus)(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags);
	पूर्णांक (*trylock_bus)(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags);
	व्योम (*unlock_bus)(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags);
पूर्ण;

/**
 * काष्ठा i2c_timings - I2C timing inक्रमmation
 * @bus_freq_hz: the bus frequency in Hz
 * @scl_rise_ns: समय SCL संकेत takes to rise in ns; t(r) in the I2C specअगरication
 * @scl_fall_ns: समय SCL संकेत takes to fall in ns; t(f) in the I2C specअगरication
 * @scl_पूर्णांक_delay_ns: समय IP core additionally needs to setup SCL in ns
 * @sda_fall_ns: समय SDA संकेत takes to fall in ns; t(f) in the I2C specअगरication
 * @sda_hold_ns: समय IP core additionally needs to hold SDA in ns
 * @digital_filter_width_ns: width in ns of spikes on i2c lines that the IP core
 *	digital filter can filter out
 * @analog_filter_cutoff_freq_hz: threshold frequency क्रम the low pass IP core
 *	analog filter
 */
काष्ठा i2c_timings अणु
	u32 bus_freq_hz;
	u32 scl_rise_ns;
	u32 scl_fall_ns;
	u32 scl_पूर्णांक_delay_ns;
	u32 sda_fall_ns;
	u32 sda_hold_ns;
	u32 digital_filter_width_ns;
	u32 analog_filter_cutoff_freq_hz;
पूर्ण;

/**
 * काष्ठा i2c_bus_recovery_info - I2C bus recovery inक्रमmation
 * @recover_bus: Recover routine. Either pass driver's recover_bus() routine, or
 *	i2c_generic_scl_recovery().
 * @get_scl: This माला_लो current value of SCL line. Mandatory क्रम generic SCL
 *      recovery. Populated पूर्णांकernally क्रम generic GPIO recovery.
 * @set_scl: This sets/clears the SCL line. Mandatory क्रम generic SCL recovery.
 *      Populated पूर्णांकernally क्रम generic GPIO recovery.
 * @get_sda: This माला_लो current value of SDA line. This or set_sda() is mandatory
 *	क्रम generic SCL recovery. Populated पूर्णांकernally, अगर sda_gpio is a valid
 *	GPIO, क्रम generic GPIO recovery.
 * @set_sda: This sets/clears the SDA line. This or get_sda() is mandatory क्रम
 *	generic SCL recovery. Populated पूर्णांकernally, अगर sda_gpio is a valid GPIO,
 *	क्रम generic GPIO recovery.
 * @get_bus_मुक्त: Returns the bus मुक्त state as seen from the IP core in हाल it
 *	has a more complex पूर्णांकernal logic than just पढ़ोing SDA. Optional.
 * @prepare_recovery: This will be called beक्रमe starting recovery. Platक्रमm may
 *	configure padmux here क्रम SDA/SCL line or something अन्यथा they want.
 * @unprepare_recovery: This will be called after completing recovery. Platक्रमm
 *	may configure padmux here क्रम SDA/SCL line or something अन्यथा they want.
 * @scl_gpiod: gpiod of the SCL line. Only required क्रम GPIO recovery.
 * @sda_gpiod: gpiod of the SDA line. Only required क्रम GPIO recovery.
 * @pinctrl: pinctrl used by GPIO recovery to change the state of the I2C pins.
 *      Optional.
 * @pins_शेष: शेष pinctrl state of SCL/SDA lines, when they are asचिन्हित
 *      to the I2C bus. Optional. Populated पूर्णांकernally क्रम GPIO recovery, अगर
 *      state with the name PINCTRL_STATE_DEFAULT is found and pinctrl is valid.
 * @pins_gpio: recovery pinctrl state of SCL/SDA lines, when they are used as
 *      GPIOs. Optional. Populated पूर्णांकernally क्रम GPIO recovery, अगर this state
 *      is called "gpio" or "recovery" and pinctrl is valid.
 */
काष्ठा i2c_bus_recovery_info अणु
	पूर्णांक (*recover_bus)(काष्ठा i2c_adapter *adap);

	पूर्णांक (*get_scl)(काष्ठा i2c_adapter *adap);
	व्योम (*set_scl)(काष्ठा i2c_adapter *adap, पूर्णांक val);
	पूर्णांक (*get_sda)(काष्ठा i2c_adapter *adap);
	व्योम (*set_sda)(काष्ठा i2c_adapter *adap, पूर्णांक val);
	पूर्णांक (*get_bus_मुक्त)(काष्ठा i2c_adapter *adap);

	व्योम (*prepare_recovery)(काष्ठा i2c_adapter *adap);
	व्योम (*unprepare_recovery)(काष्ठा i2c_adapter *adap);

	/* gpio recovery */
	काष्ठा gpio_desc *scl_gpiod;
	काष्ठा gpio_desc *sda_gpiod;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_शेष;
	काष्ठा pinctrl_state *pins_gpio;
पूर्ण;

पूर्णांक i2c_recover_bus(काष्ठा i2c_adapter *adap);

/* Generic recovery routines */
पूर्णांक i2c_generic_scl_recovery(काष्ठा i2c_adapter *adap);

/**
 * काष्ठा i2c_adapter_quirks - describe flaws of an i2c adapter
 * @flags: see I2C_AQ_* क्रम possible flags and पढ़ो below
 * @max_num_msgs: maximum number of messages per transfer
 * @max_ग_लिखो_len: maximum length of a ग_लिखो message
 * @max_पढ़ो_len: maximum length of a पढ़ो message
 * @max_comb_1st_msg_len: maximum length of the first msg in a combined message
 * @max_comb_2nd_msg_len: maximum length of the second msg in a combined message
 *
 * Note about combined messages: Some I2C controllers can only send one message
 * per transfer, plus something called combined message or ग_लिखो-then-पढ़ो.
 * This is (usually) a small ग_लिखो message followed by a पढ़ो message and
 * barely enough to access रेजिस्टर based devices like EEPROMs. There is a flag
 * to support this mode. It implies max_num_msg = 2 and करोes the length checks
 * with max_comb_*_len because combined message mode usually has its own
 * limitations. Because of HW implementations, some controllers can actually करो
 * ग_लिखो-then-anything or other variants. To support that, ग_लिखो-then-पढ़ो has
 * been broken out पूर्णांकo smaller bits like ग_लिखो-first and पढ़ो-second which can
 * be combined as needed.
 */

काष्ठा i2c_adapter_quirks अणु
	u64 flags;
	पूर्णांक max_num_msgs;
	u16 max_ग_लिखो_len;
	u16 max_पढ़ो_len;
	u16 max_comb_1st_msg_len;
	u16 max_comb_2nd_msg_len;
पूर्ण;

/* enक्रमce max_num_msgs = 2 and use max_comb_*_len क्रम length checks */
#घोषणा I2C_AQ_COMB			BIT(0)
/* first combined message must be ग_लिखो */
#घोषणा I2C_AQ_COMB_WRITE_FIRST		BIT(1)
/* second combined message must be पढ़ो */
#घोषणा I2C_AQ_COMB_READ_SECOND		BIT(2)
/* both combined messages must have the same target address */
#घोषणा I2C_AQ_COMB_SAME_ADDR		BIT(3)
/* convenience macro क्रम typical ग_लिखो-then पढ़ो हाल */
#घोषणा I2C_AQ_COMB_WRITE_THEN_READ	(I2C_AQ_COMB | I2C_AQ_COMB_WRITE_FIRST | \
					 I2C_AQ_COMB_READ_SECOND | I2C_AQ_COMB_SAME_ADDR)
/* घड़ी stretching is not supported */
#घोषणा I2C_AQ_NO_CLK_STRETCH		BIT(4)
/* message cannot have length of 0 */
#घोषणा I2C_AQ_NO_ZERO_LEN_READ		BIT(5)
#घोषणा I2C_AQ_NO_ZERO_LEN_WRITE	BIT(6)
#घोषणा I2C_AQ_NO_ZERO_LEN		(I2C_AQ_NO_ZERO_LEN_READ | I2C_AQ_NO_ZERO_LEN_WRITE)
/* adapter cannot करो repeated START */
#घोषणा I2C_AQ_NO_REP_START		BIT(7)

/*
 * i2c_adapter is the काष्ठाure used to identअगरy a physical i2c bus aदीर्घ
 * with the access algorithms necessary to access it.
 */
काष्ठा i2c_adapter अणु
	काष्ठा module *owner;
	अचिन्हित पूर्णांक class;		  /* classes to allow probing क्रम */
	स्थिर काष्ठा i2c_algorithm *algo; /* the algorithm to access the bus */
	व्योम *algo_data;

	/* data fields that are valid क्रम all devices	*/
	स्थिर काष्ठा i2c_lock_operations *lock_ops;
	काष्ठा rt_mutex bus_lock;
	काष्ठा rt_mutex mux_lock;

	पूर्णांक समयout;			/* in jअगरfies */
	पूर्णांक retries;
	काष्ठा device dev;		/* the adapter device */
	अचिन्हित दीर्घ locked_flags;	/* owned by the I2C core */
#घोषणा I2C_ALF_IS_SUSPENDED		0
#घोषणा I2C_ALF_SUSPEND_REPORTED	1

	पूर्णांक nr;
	अक्षर name[48];
	काष्ठा completion dev_released;

	काष्ठा mutex userspace_clients_lock;
	काष्ठा list_head userspace_clients;

	काष्ठा i2c_bus_recovery_info *bus_recovery_info;
	स्थिर काष्ठा i2c_adapter_quirks *quirks;

	काष्ठा irq_करोमुख्य *host_notअगरy_करोमुख्य;
पूर्ण;
#घोषणा to_i2c_adapter(d) container_of(d, काष्ठा i2c_adapter, dev)

अटल अंतरभूत व्योम *i2c_get_adapdata(स्थिर काष्ठा i2c_adapter *adap)
अणु
	वापस dev_get_drvdata(&adap->dev);
पूर्ण

अटल अंतरभूत व्योम i2c_set_adapdata(काष्ठा i2c_adapter *adap, व्योम *data)
अणु
	dev_set_drvdata(&adap->dev, data);
पूर्ण

अटल अंतरभूत काष्ठा i2c_adapter *
i2c_parent_is_i2c_adapter(स्थिर काष्ठा i2c_adapter *adapter)
अणु
#अगर IS_ENABLED(CONFIG_I2C_MUX)
	काष्ठा device *parent = adapter->dev.parent;

	अगर (parent != शून्य && parent->type == &i2c_adapter_type)
		वापस to_i2c_adapter(parent);
	अन्यथा
#पूर्ण_अगर
		वापस शून्य;
पूर्ण

पूर्णांक i2c_क्रम_each_dev(व्योम *data, पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data));

/* Adapter locking functions, exported क्रम shared pin हालs */
#घोषणा I2C_LOCK_ROOT_ADAPTER BIT(0)
#घोषणा I2C_LOCK_SEGMENT      BIT(1)

/**
 * i2c_lock_bus - Get exclusive access to an I2C bus segment
 * @adapter: Target I2C bus segment
 * @flags: I2C_LOCK_ROOT_ADAPTER locks the root i2c adapter, I2C_LOCK_SEGMENT
 *	locks only this branch in the adapter tree
 */
अटल अंतरभूत व्योम
i2c_lock_bus(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags)
अणु
	adapter->lock_ops->lock_bus(adapter, flags);
पूर्ण

/**
 * i2c_trylock_bus - Try to get exclusive access to an I2C bus segment
 * @adapter: Target I2C bus segment
 * @flags: I2C_LOCK_ROOT_ADAPTER tries to locks the root i2c adapter,
 *	I2C_LOCK_SEGMENT tries to lock only this branch in the adapter tree
 *
 * Return: true अगर the I2C bus segment is locked, false otherwise
 */
अटल अंतरभूत पूर्णांक
i2c_trylock_bus(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags)
अणु
	वापस adapter->lock_ops->trylock_bus(adapter, flags);
पूर्ण

/**
 * i2c_unlock_bus - Release exclusive access to an I2C bus segment
 * @adapter: Target I2C bus segment
 * @flags: I2C_LOCK_ROOT_ADAPTER unlocks the root i2c adapter, I2C_LOCK_SEGMENT
 *	unlocks only this branch in the adapter tree
 */
अटल अंतरभूत व्योम
i2c_unlock_bus(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक flags)
अणु
	adapter->lock_ops->unlock_bus(adapter, flags);
पूर्ण

/**
 * i2c_mark_adapter_suspended - Report suspended state of the adapter to the core
 * @adap: Adapter to mark as suspended
 *
 * When using this helper to mark an adapter as suspended, the core will reject
 * further transfers to this adapter. The usage of this helper is optional but
 * recommended क्रम devices having distinct handlers क्रम प्रणाली suspend and
 * runसमय suspend. More complex devices are मुक्त to implement custom solutions
 * to reject transfers when suspended.
 */
अटल अंतरभूत व्योम i2c_mark_adapter_suspended(काष्ठा i2c_adapter *adap)
अणु
	i2c_lock_bus(adap, I2C_LOCK_ROOT_ADAPTER);
	set_bit(I2C_ALF_IS_SUSPENDED, &adap->locked_flags);
	i2c_unlock_bus(adap, I2C_LOCK_ROOT_ADAPTER);
पूर्ण

/**
 * i2c_mark_adapter_resumed - Report resumed state of the adapter to the core
 * @adap: Adapter to mark as resumed
 *
 * When using this helper to mark an adapter as resumed, the core will allow
 * further transfers to this adapter. See also further notes to
 * @i2c_mark_adapter_suspended().
 */
अटल अंतरभूत व्योम i2c_mark_adapter_resumed(काष्ठा i2c_adapter *adap)
अणु
	i2c_lock_bus(adap, I2C_LOCK_ROOT_ADAPTER);
	clear_bit(I2C_ALF_IS_SUSPENDED, &adap->locked_flags);
	i2c_unlock_bus(adap, I2C_LOCK_ROOT_ADAPTER);
पूर्ण

/* i2c adapter classes (biपंचांगask) */
#घोषणा I2C_CLASS_HWMON		(1<<0)	/* lm_sensors, ... */
#घोषणा I2C_CLASS_DDC		(1<<3)	/* DDC bus on graphics adapters */
#घोषणा I2C_CLASS_SPD		(1<<7)	/* Memory modules */
/* Warn users that the adapter करोesn't support classes anymore */
#घोषणा I2C_CLASS_DEPRECATED	(1<<8)

/* Internal numbers to terminate lists */
#घोषणा I2C_CLIENT_END		0xfffeU

/* Conकाष्ठा an I2C_CLIENT_END-terminated array of i2c addresses */
#घोषणा I2C_ADDRS(addr, addrs...) \
	((स्थिर अचिन्हित लघु [])अणु addr, ## addrs, I2C_CLIENT_END पूर्ण)


/* ----- functions exported by i2c.o */

/* administration...
 */
#अगर IS_ENABLED(CONFIG_I2C)
पूर्णांक i2c_add_adapter(काष्ठा i2c_adapter *adap);
पूर्णांक devm_i2c_add_adapter(काष्ठा device *dev, काष्ठा i2c_adapter *adapter);
व्योम i2c_del_adapter(काष्ठा i2c_adapter *adap);
पूर्णांक i2c_add_numbered_adapter(काष्ठा i2c_adapter *adap);

पूर्णांक i2c_रेजिस्टर_driver(काष्ठा module *owner, काष्ठा i2c_driver *driver);
व्योम i2c_del_driver(काष्ठा i2c_driver *driver);

/* use a define to aव्योम include chaining to get THIS_MODULE */
#घोषणा i2c_add_driver(driver) \
	i2c_रेजिस्टर_driver(THIS_MODULE, driver)

अटल अंतरभूत bool i2c_client_has_driver(काष्ठा i2c_client *client)
अणु
	वापस !IS_ERR_OR_शून्य(client) && client->dev.driver;
पूर्ण

/* call the i2c_client->command() of all attached clients with
 * the given arguments */
व्योम i2c_clients_command(काष्ठा i2c_adapter *adap,
			 अचिन्हित पूर्णांक cmd, व्योम *arg);

काष्ठा i2c_adapter *i2c_get_adapter(पूर्णांक nr);
व्योम i2c_put_adapter(काष्ठा i2c_adapter *adap);
अचिन्हित पूर्णांक i2c_adapter_depth(काष्ठा i2c_adapter *adapter);

व्योम i2c_parse_fw_timings(काष्ठा device *dev, काष्ठा i2c_timings *t, bool use_शेषs);

/* Return the functionality mask */
अटल अंतरभूत u32 i2c_get_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस adap->algo->functionality(adap);
पूर्ण

/* Return 1 अगर adapter supports everything we need, 0 अगर not. */
अटल अंतरभूत पूर्णांक i2c_check_functionality(काष्ठा i2c_adapter *adap, u32 func)
अणु
	वापस (func & i2c_get_functionality(adap)) == func;
पूर्ण

/**
 * i2c_check_quirks() - Function क्रम checking the quirk flags in an i2c adapter
 * @adap: i2c adapter
 * @quirks: quirk flags
 *
 * Return: true अगर the adapter has all the specअगरied quirk flags, false अगर not
 */
अटल अंतरभूत bool i2c_check_quirks(काष्ठा i2c_adapter *adap, u64 quirks)
अणु
	अगर (!adap->quirks)
		वापस false;
	वापस (adap->quirks->flags & quirks) == quirks;
पूर्ण

/* Return the adapter number क्रम a specअगरic adapter */
अटल अंतरभूत पूर्णांक i2c_adapter_id(काष्ठा i2c_adapter *adap)
अणु
	वापस adap->nr;
पूर्ण

अटल अंतरभूत u8 i2c_8bit_addr_from_msg(स्थिर काष्ठा i2c_msg *msg)
अणु
	वापस (msg->addr << 1) | (msg->flags & I2C_M_RD ? 1 : 0);
पूर्ण

u8 *i2c_get_dma_safe_msg_buf(काष्ठा i2c_msg *msg, अचिन्हित पूर्णांक threshold);
व्योम i2c_put_dma_safe_msg_buf(u8 *buf, काष्ठा i2c_msg *msg, bool xferred);

पूर्णांक i2c_handle_smbus_host_notअगरy(काष्ठा i2c_adapter *adap, अचिन्हित लघु addr);
/**
 * module_i2c_driver() - Helper macro क्रम रेजिस्टरing a modular I2C driver
 * @__i2c_driver: i2c_driver काष्ठा
 *
 * Helper macro क्रम I2C drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_i2c_driver(__i2c_driver) \
	module_driver(__i2c_driver, i2c_add_driver, \
			i2c_del_driver)

/**
 * builtin_i2c_driver() - Helper macro क्रम रेजिस्टरing a builtin I2C driver
 * @__i2c_driver: i2c_driver काष्ठा
 *
 * Helper macro क्रम I2C drivers which करो not करो anything special in their
 * init. This eliminates a lot of boilerplate. Each driver may only
 * use this macro once, and calling it replaces device_initcall().
 */
#घोषणा builtin_i2c_driver(__i2c_driver) \
	builtin_driver(__i2c_driver, i2c_add_driver)

#पूर्ण_अगर /* I2C */

#अगर IS_ENABLED(CONFIG_OF)
/* must call put_device() when करोne with वापसed i2c_client device */
काष्ठा i2c_client *of_find_i2c_device_by_node(काष्ठा device_node *node);

/* must call put_device() when करोne with वापसed i2c_adapter device */
काष्ठा i2c_adapter *of_find_i2c_adapter_by_node(काष्ठा device_node *node);

/* must call i2c_put_adapter() when करोne with वापसed i2c_adapter device */
काष्ठा i2c_adapter *of_get_i2c_adapter_by_node(काष्ठा device_node *node);

स्थिर काष्ठा of_device_id
*i2c_of_match_device(स्थिर काष्ठा of_device_id *matches,
		     काष्ठा i2c_client *client);

पूर्णांक of_i2c_get_board_info(काष्ठा device *dev, काष्ठा device_node *node,
			  काष्ठा i2c_board_info *info);

#अन्यथा

अटल अंतरभूत काष्ठा i2c_client *of_find_i2c_device_by_node(काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा i2c_adapter *of_find_i2c_adapter_by_node(काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा i2c_adapter *of_get_i2c_adapter_by_node(काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा of_device_id
*i2c_of_match_device(स्थिर काष्ठा of_device_id *matches,
		     काष्ठा i2c_client *client)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_i2c_get_board_info(काष्ठा device *dev,
					काष्ठा device_node *node,
					काष्ठा i2c_board_info *info)
अणु
	वापस -ENOTSUPP;
पूर्ण

#पूर्ण_अगर /* CONFIG_OF */

काष्ठा acpi_resource;
काष्ठा acpi_resource_i2c_serialbus;

#अगर IS_ENABLED(CONFIG_ACPI)
bool i2c_acpi_get_i2c_resource(काष्ठा acpi_resource *ares,
			       काष्ठा acpi_resource_i2c_serialbus **i2c);
u32 i2c_acpi_find_bus_speed(काष्ठा device *dev);
काष्ठा i2c_client *i2c_acpi_new_device(काष्ठा device *dev, पूर्णांक index,
				       काष्ठा i2c_board_info *info);
काष्ठा i2c_adapter *i2c_acpi_find_adapter_by_handle(acpi_handle handle);
#अन्यथा
अटल अंतरभूत bool i2c_acpi_get_i2c_resource(काष्ठा acpi_resource *ares,
					     काष्ठा acpi_resource_i2c_serialbus **i2c)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत u32 i2c_acpi_find_bus_speed(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा i2c_client *i2c_acpi_new_device(काष्ठा device *dev,
					पूर्णांक index, काष्ठा i2c_board_info *info)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
अटल अंतरभूत काष्ठा i2c_adapter *i2c_acpi_find_adapter_by_handle(acpi_handle handle)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

#पूर्ण_अगर /* _LINUX_I2C_H */

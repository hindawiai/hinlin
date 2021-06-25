<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Industry-pack bus.
 *
 * Copyright (C) 2011-2012 CERN (www.cern.ch)
 * Author: Samuel Iglesias Gonsalvez <siglesias@igalia.com>
 */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा IPACK_IDPROM_OFFSET_I			0x01
#घोषणा IPACK_IDPROM_OFFSET_P			0x03
#घोषणा IPACK_IDPROM_OFFSET_A			0x05
#घोषणा IPACK_IDPROM_OFFSET_C			0x07
#घोषणा IPACK_IDPROM_OFFSET_MANUFACTURER_ID	0x09
#घोषणा IPACK_IDPROM_OFFSET_MODEL		0x0B
#घोषणा IPACK_IDPROM_OFFSET_REVISION		0x0D
#घोषणा IPACK_IDPROM_OFFSET_RESERVED		0x0F
#घोषणा IPACK_IDPROM_OFFSET_DRIVER_ID_L		0x11
#घोषणा IPACK_IDPROM_OFFSET_DRIVER_ID_H		0x13
#घोषणा IPACK_IDPROM_OFFSET_NUM_BYTES		0x15
#घोषणा IPACK_IDPROM_OFFSET_CRC			0x17

/*
 * IndustryPack Fromat, Venकरोr and Device IDs.
 */

/* ID section क्रमmat versions */
#घोषणा IPACK_ID_VERSION_INVALID	0x00
#घोषणा IPACK_ID_VERSION_1		0x01
#घोषणा IPACK_ID_VERSION_2		0x02

/* Venकरोrs and devices. Sort key: venकरोr first, device next. */
#घोषणा IPACK1_VENDOR_ID_RESERVED1	0x00
#घोषणा IPACK1_VENDOR_ID_RESERVED2	0xFF
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED01	0x01
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED02	0x02
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED03	0x03
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED04	0x04
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED05	0x05
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED06	0x06
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED07	0x07
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED08	0x08
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED09	0x09
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED10	0x0A
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED11	0x0B
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED12	0x0C
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED13	0x0D
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED14	0x0E
#घोषणा IPACK1_VENDOR_ID_UNREGISTRED15	0x0F

#घोषणा IPACK1_VENDOR_ID_SBS            0xF0
#घोषणा IPACK1_DEVICE_ID_SBS_OCTAL_232  0x22
#घोषणा IPACK1_DEVICE_ID_SBS_OCTAL_422  0x2A
#घोषणा IPACK1_DEVICE_ID_SBS_OCTAL_485  0x48

काष्ठा ipack_bus_ops;
काष्ठा ipack_driver;

क्रमागत ipack_space अणु
	IPACK_IO_SPACE    = 0,
	IPACK_ID_SPACE,
	IPACK_INT_SPACE,
	IPACK_MEM8_SPACE,
	IPACK_MEM16_SPACE,
	/* Dummy क्रम counting the number of entries.  Must reमुख्य the last
	 * entry */
	IPACK_SPACE_COUNT,
पूर्ण;

/**
 */
काष्ठा ipack_region अणु
	phys_addr_t start;
	माप_प्रकार      size;
पूर्ण;

/**
 *	काष्ठा ipack_device
 *
 *	@slot: Slot where the device is plugged in the carrier board
 *	@bus: ipack_bus_device where the device is plugged to.
 *	@id_space: Virtual address to ID space.
 *	@io_space: Virtual address to IO space.
 *	@mem_space: Virtual address to MEM space.
 *	@dev: device in kernel representation.
 *
 * Warning: Direct access to mapped memory is possible but the endianness
 * is not the same with PCI carrier or VME carrier. The endianness is managed
 * by the carrier board throught bus->ops.
 */
काष्ठा ipack_device अणु
	अचिन्हित पूर्णांक slot;
	काष्ठा ipack_bus_device *bus;
	काष्ठा device dev;
	व्योम (*release) (काष्ठा ipack_device *dev);
	काष्ठा ipack_region      region[IPACK_SPACE_COUNT];
	u8                      *id;
	माप_प्रकार			 id_avail;
	u32			 id_venकरोr;
	u32			 id_device;
	u8			 id_क्रमmat;
	अचिन्हित पूर्णांक		 id_crc_correct:1;
	अचिन्हित पूर्णांक		 speed_8mhz:1;
	अचिन्हित पूर्णांक		 speed_32mhz:1;
पूर्ण;

/**
 * काष्ठा ipack_driver_ops -- Callbacks to IPack device driver
 *
 * @probe:  Probe function
 * @हटाओ: Prepare imminent removal of the device.  Services provided by the
 *          device should be revoked.
 */

काष्ठा ipack_driver_ops अणु
	पूर्णांक (*probe) (काष्ठा ipack_device *dev);
	व्योम (*हटाओ) (काष्ठा ipack_device *dev);
पूर्ण;

/**
 * काष्ठा ipack_driver -- Specअगरic data to each ipack device driver
 *
 * @driver: Device driver kernel representation
 * @ops:    Callbacks provided by the IPack device driver
 */
काष्ठा ipack_driver अणु
	काष्ठा device_driver driver;
	स्थिर काष्ठा ipack_device_id *id_table;
	स्थिर काष्ठा ipack_driver_ops *ops;
पूर्ण;

/**
 *	काष्ठा ipack_bus_ops - available operations on a bridge module
 *
 *	@map_space: map IP address space
 *	@unmap_space: unmap IP address space
 *	@request_irq: request IRQ
 *	@मुक्त_irq: मुक्त IRQ
 *	@get_घड़ीrate: Returns the घड़ीrate the carrier is currently
 *		communicating with the device at.
 *	@set_घड़ीrate: Sets the घड़ी-rate क्रम carrier / module communication.
 *		Should वापस -EINVAL अगर the requested speed is not supported.
 *	@get_error: Returns the error state क्रम the slot the device is attached
 *		to.
 *	@get_समयout: Returns 1 अगर the communication with the device has
 *		previously समयd out.
 *	@reset_समयout: Resets the state वापसed by get_समयout.
 */
काष्ठा ipack_bus_ops अणु
	पूर्णांक (*request_irq) (काष्ठा ipack_device *dev,
			    irqवापस_t (*handler)(व्योम *), व्योम *arg);
	पूर्णांक (*मुक्त_irq) (काष्ठा ipack_device *dev);
	पूर्णांक (*get_घड़ीrate) (काष्ठा ipack_device *dev);
	पूर्णांक (*set_घड़ीrate) (काष्ठा ipack_device *dev, पूर्णांक mherz);
	पूर्णांक (*get_error) (काष्ठा ipack_device *dev);
	पूर्णांक (*get_समयout) (काष्ठा ipack_device *dev);
	पूर्णांक (*reset_समयout) (काष्ठा ipack_device *dev);
पूर्ण;

/**
 *	काष्ठा ipack_bus_device
 *
 *	@dev: poपूर्णांकer to carrier device
 *	@slots: number of slots available
 *	@bus_nr: ipack bus number
 *	@ops: bus operations क्रम the mezzanine drivers
 */
काष्ठा ipack_bus_device अणु
	काष्ठा module *owner;
	काष्ठा device *parent;
	पूर्णांक slots;
	पूर्णांक bus_nr;
	स्थिर काष्ठा ipack_bus_ops *ops;
पूर्ण;

/**
 *	ipack_bus_रेजिस्टर -- रेजिस्टर a new ipack bus
 *
 * @parent: poपूर्णांकer to the parent device, अगर any.
 * @slots: number of slots available in the bus device.
 * @ops: bus operations क्रम the mezzanine drivers.
 *
 * The carrier board device should call this function to रेजिस्टर itself as
 * available bus device in ipack.
 */
काष्ठा ipack_bus_device *ipack_bus_रेजिस्टर(काष्ठा device *parent, पूर्णांक slots,
					    स्थिर काष्ठा ipack_bus_ops *ops,
					    काष्ठा module *owner);

/**
 *	ipack_bus_unरेजिस्टर -- unरेजिस्टर an ipack bus
 */
पूर्णांक ipack_bus_unरेजिस्टर(काष्ठा ipack_bus_device *bus);

/**
 * ipack_driver_रेजिस्टर -- Register a new ipack device driver
 *
 * Called by a ipack driver to रेजिस्टर itself as a driver
 * that can manage ipack devices.
 */
पूर्णांक ipack_driver_रेजिस्टर(काष्ठा ipack_driver *edrv, काष्ठा module *owner,
			  स्थिर अक्षर *name);
व्योम ipack_driver_unरेजिस्टर(काष्ठा ipack_driver *edrv);

/**
 *	ipack_device_init -- initialize an IPack device
 * @dev: the new device to initialize.
 *
 * Initialize a new IPack device ("module" in IndustryPack jargon). The call
 * is करोne by the carrier driver.  The carrier should populate the fields
 * bus and slot as well as the region array of @dev prior to calling this
 * function.  The rest of the fields will be allocated and populated
 * during initalization.
 *
 * Return zero on success or error code on failure.
 *
 * NOTE: _Never_ directly मुक्त @dev after calling this function, even
 * अगर it वापसed an error! Always use ipack_put_device() to give up the
 * reference initialized in this function instead.
 */
पूर्णांक ipack_device_init(काष्ठा ipack_device *dev);

/**
 *	ipack_device_add -- Add an IPack device
 * @dev: the new device to add.
 *
 * Add a new IPack device. The call is करोne by the carrier driver
 * after calling ipack_device_init().
 *
 * Return zero on success or error code on failure.
 *
 * NOTE: _Never_ directly मुक्त @dev after calling this function, even
 * अगर it वापसed an error! Always use ipack_put_device() to give up the
 * reference initialized in this function instead.
 */
पूर्णांक ipack_device_add(काष्ठा ipack_device *dev);
व्योम ipack_device_del(काष्ठा ipack_device *dev);

व्योम ipack_get_device(काष्ठा ipack_device *dev);
व्योम ipack_put_device(काष्ठा ipack_device *dev);

/**
 * DEFINE_IPACK_DEVICE_TABLE - macro used to describe a IndustryPack table
 * @_table: device table name
 *
 * This macro is used to create a काष्ठा ipack_device_id array (a device table)
 * in a generic manner.
 */
#घोषणा DEFINE_IPACK_DEVICE_TABLE(_table) \
	स्थिर काष्ठा ipack_device_id _table[]
/**
 * IPACK_DEVICE - macro used to describe a specअगरic IndustryPack device
 * @_क्रमmat: the क्रमmat version (currently either 1 or 2, 8 bit value)
 * @vend:    the 8 or 24 bit IndustryPack Venकरोr ID
 * @dev:     the 8 or 16  bit IndustryPack Device ID
 *
 * This macro is used to create a काष्ठा ipack_device_id that matches a specअगरic
 * device.
 */
#घोषणा IPACK_DEVICE(_क्रमmat, vend, dev) \
	 .क्रमmat = (_क्रमmat), \
	 .venकरोr = (vend), \
	 .device = (dev)

/**
 * ipack_get_carrier - it increase the carrier ref. counter of
 *                     the carrier module
 * @dev: mezzanine device which wants to get the carrier
 */
अटल अंतरभूत पूर्णांक ipack_get_carrier(काष्ठा ipack_device *dev)
अणु
	वापस try_module_get(dev->bus->owner);
पूर्ण

/**
 * ipack_get_carrier - it decrease the carrier ref. counter of
 *                     the carrier module
 * @dev: mezzanine device which wants to get the carrier
 */
अटल अंतरभूत व्योम ipack_put_carrier(काष्ठा ipack_device *dev)
अणु
	module_put(dev->bus->owner);
पूर्ण

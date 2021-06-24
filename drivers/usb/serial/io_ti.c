<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Edgeport USB Serial Converter driver
 *
 * Copyright (C) 2000-2002 Inside Out Networks, All rights reserved.
 * Copyright (C) 2001-2002 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 * Supports the following devices:
 *	EP/1 EP/2 EP/4 EP/21 EP/22 EP/221 EP/42 EP/421 WATCHPORT
 *
 * For questions or problems with this driver, contact Inside Out
 * Networks technical support, or Peter Berger <pberger@brimson.com>,
 * or Al Borchers <alborchers@steinerpoपूर्णांक.com>.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/serial.h>
#समावेश <linux/swab.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/firmware.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#समावेश "io_16654.h"
#समावेश "io_usbvend.h"
#समावेश "io_ti.h"

#घोषणा DRIVER_AUTHOR "Greg Kroah-Hartman <greg@kroah.com> and David Iacovelli"
#घोषणा DRIVER_DESC "Edgeport USB Serial Driver"

#घोषणा EPROM_PAGE_SIZE		64


/* dअगरferent hardware types */
#घोषणा HARDWARE_TYPE_930	0
#घोषणा HARDWARE_TYPE_TIUMP	1

/* IOCTL_PRIVATE_TI_GET_MODE Definitions */
#घोषणा	TI_MODE_CONFIGURING	0   /* Device has not entered start device */
#घोषणा	TI_MODE_BOOT		1   /* Staying in boot mode		   */
#घोषणा TI_MODE_DOWNLOAD	2   /* Made it to करोwnload mode		   */
#घोषणा TI_MODE_TRANSITIONING	3   /*
				     * Currently in boot mode but
				     * transitioning to करोwnload mode
				     */

/* पढ़ो urb state */
#घोषणा EDGE_READ_URB_RUNNING	0
#घोषणा EDGE_READ_URB_STOPPING	1
#घोषणा EDGE_READ_URB_STOPPED	2


/* Product inक्रमmation पढ़ो from the Edgeport */
काष्ठा product_info अणु
	पूर्णांक	TiMode;			/* Current TI Mode  */
	u8	hardware_type;		/* Type of hardware */
पूर्ण __packed;

/*
 * Edgeport firmware header
 *
 * "build_number" has been set to 0 in all three of the images I have
 * seen, and Digi Tech Support suggests that it is safe to ignore it.
 *
 * "length" is the number of bytes of actual data following the header.
 *
 * "checksum" is the low order byte resulting from adding the values of
 * all the data bytes.
 */
काष्ठा edgeport_fw_hdr अणु
	u8 major_version;
	u8 minor_version;
	__le16 build_number;
	__le16 length;
	u8 checksum;
पूर्ण __packed;

काष्ठा edgeport_port अणु
	u16 uart_base;
	u16 dma_address;
	u8 shaकरोw_msr;
	u8 shaकरोw_mcr;
	u8 shaकरोw_lsr;
	u8 lsr_mask;
	u32 ump_पढ़ो_समयout;		/*
					 * Number of milliseconds the UMP will
					 * रुको without data beक्रमe completing
					 * a पढ़ो लघु
					 */
	पूर्णांक baud_rate;
	पूर्णांक बंद_pending;
	पूर्णांक lsr_event;

	काष्ठा edgeport_serial	*edge_serial;
	काष्ठा usb_serial_port	*port;
	u8 bUartMode;		/* Port type, 0: RS232, etc. */
	spinlock_t ep_lock;
	पूर्णांक ep_पढ़ो_urb_state;
	पूर्णांक ep_ग_लिखो_urb_in_use;
पूर्ण;

काष्ठा edgeport_serial अणु
	काष्ठा product_info product_info;
	u8 TI_I2C_Type;			/* Type of I2C in UMP */
	u8 TiReadI2C;			/*
					 * Set to TRUE अगर we have पढ़ो the
					 * I2c in Boot Mode
					 */
	काष्ठा mutex es_lock;
	पूर्णांक num_ports_खोलो;
	काष्ठा usb_serial *serial;
	काष्ठा delayed_work heartbeat_work;
	पूर्णांक fw_version;
	bool use_heartbeat;
पूर्ण;


/* Devices that this driver supports */
अटल स्थिर काष्ठा usb_device_id edgeport_1port_id_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_1) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_TI3410_EDGEPORT_1) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_TI3410_EDGEPORT_1I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_PROXIMITY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_MOTION) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_MOISTURE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_TEMPERATURE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_HUMIDITY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_POWER) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_LIGHT) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_RADIATION) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_DISTANCE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_ACCELERATION) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_PROX_DIST) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_PLUS_PWR_HP4CD) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_PLUS_PWR_PCI) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id edgeport_2port_id_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_2C) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_2I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_421) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_21) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_42) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_4I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_22I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_221C) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_22C) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_21C) पूर्ण,
	/* The 4, 8 and 16 port devices show up as multiple 2 port devices */
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_4S) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_8) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_8S) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_416) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_416B) पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Devices that this driver supports */
अटल स्थिर काष्ठा usb_device_id id_table_combined[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_1) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_TI3410_EDGEPORT_1) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_TI3410_EDGEPORT_1I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_PROXIMITY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_MOTION) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_MOISTURE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_TEMPERATURE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_HUMIDITY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_POWER) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_LIGHT) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_RADIATION) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_DISTANCE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_ACCELERATION) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_WP_PROX_DIST) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_PLUS_PWR_HP4CD) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_PLUS_PWR_PCI) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_2C) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_2I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_421) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_21) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_42) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_4I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_22I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_221C) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_22C) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_21C) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_4S) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_8) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_8S) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_416) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_TI_EDGEPORT_416B) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table_combined);

अटल bool ignore_cpu_rev;
अटल पूर्णांक शेष_uart_mode;		/* RS232 */

अटल व्योम edge_tty_recv(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *data,
		पूर्णांक length);

अटल व्योम stop_पढ़ो(काष्ठा edgeport_port *edge_port);
अटल पूर्णांक restart_पढ़ो(काष्ठा edgeport_port *edge_port);

अटल व्योम edge_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios);
अटल व्योम edge_send(काष्ठा usb_serial_port *port, काष्ठा tty_काष्ठा *tty);

अटल पूर्णांक करो_करोwnload_mode(काष्ठा edgeport_serial *serial,
		स्थिर काष्ठा firmware *fw);
अटल पूर्णांक करो_boot_mode(काष्ठा edgeport_serial *serial,
		स्थिर काष्ठा firmware *fw);

/* sysfs attributes */
अटल पूर्णांक edge_create_sysfs_attrs(काष्ठा usb_serial_port *port);
अटल पूर्णांक edge_हटाओ_sysfs_attrs(काष्ठा usb_serial_port *port);

/*
 * Some release of Edgeport firmware "down3.bin" after version 4.80
 * पूर्णांकroduced code to स्वतःmatically disconnect idle devices on some
 * Edgeport models after periods of inactivity, typically ~60 seconds.
 * This occurs without regard to whether ports on the device are खोलो
 * or not.  Digi International Tech Support suggested:
 *
 * 1.  Adding driver "heartbeat" code to reset the firmware समयr by
 *     requesting a descriptor record every 15 seconds, which should be
 *     effective with newer firmware versions that require it, and benign
 *     with older versions that करो not. In practice 40 seconds seems often
 *     enough.
 * 2.  The heartbeat code is currently required only on Edgeport/416 models.
 */
#घोषणा FW_HEARTBEAT_VERSION_CUTOFF ((4 << 8) + 80)
#घोषणा FW_HEARTBEAT_SECS 40

/* Timeouts in msecs: firmware करोwnloads take दीर्घer */
#घोषणा TI_VSEND_TIMEOUT_DEFAULT 1000
#घोषणा TI_VSEND_TIMEOUT_FW_DOWNLOAD 10000

अटल पूर्णांक ti_vपढ़ो_sync(काष्ठा usb_device *dev, u8 request, u16 value,
		u16 index, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक status;

	status = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), request,
			(USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN),
			value, index, data, size, 1000);
	अगर (status < 0)
		वापस status;
	अगर (status != size) अणु
		dev_dbg(&dev->dev, "%s - wanted to read %d, but only read %d\n",
			__func__, size, status);
		वापस -ECOMM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ti_vsend_sync(काष्ठा usb_device *dev, u8 request, u16 value,
		u16 index, व्योम *data, पूर्णांक size, पूर्णांक समयout)
अणु
	पूर्णांक status;

	status = usb_control_msg(dev, usb_sndctrlpipe(dev, 0), request,
			(USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT),
			value, index, data, size, समयout);
	अगर (status < 0)
		वापस status;

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_port_cmd(काष्ठा usb_serial_port *port, u8 command, u16 value,
		व्योम *data, पूर्णांक size)
अणु
	वापस ti_vपढ़ो_sync(port->serial->dev, command, value,
			UMPM_UART1_PORT + port->port_number,
			data, size);
पूर्ण

अटल पूर्णांक send_port_cmd(काष्ठा usb_serial_port *port, u8 command, u16 value,
		व्योम *data, पूर्णांक size)
अणु
	वापस ti_vsend_sync(port->serial->dev, command, value,
			UMPM_UART1_PORT + port->port_number,
			data, size, TI_VSEND_TIMEOUT_DEFAULT);
पूर्ण

/* clear tx/rx buffers and fअगरo in TI UMP */
अटल पूर्णांक purge_port(काष्ठा usb_serial_port *port, u16 mask)
अणु
	पूर्णांक port_number = port->port_number;

	dev_dbg(&port->dev, "%s - port %d, mask %x\n", __func__, port_number, mask);

	वापस send_port_cmd(port, UMPC_PURGE_PORT, mask, शून्य, 0);
पूर्ण

/**
 * पढ़ो_करोwnload_mem - Read edgeport memory from TI chip
 * @dev: usb device poपूर्णांकer
 * @start_address: Device CPU address at which to पढ़ो
 * @length: Length of above data
 * @address_type: Can पढ़ो both XDATA and I2C
 * @buffer: poपूर्णांकer to input data buffer
 */
अटल पूर्णांक पढ़ो_करोwnload_mem(काष्ठा usb_device *dev, पूर्णांक start_address,
				पूर्णांक length, u8 address_type, u8 *buffer)
अणु
	पूर्णांक status = 0;
	u8 पढ़ो_length;
	u16 be_start_address;

	dev_dbg(&dev->dev, "%s - @ %x for %d\n", __func__, start_address, length);

	/*
	 * Read in blocks of 64 bytes
	 * (TI firmware can't handle more than 64 byte पढ़ोs)
	 */
	जबतक (length) अणु
		अगर (length > 64)
			पढ़ो_length = 64;
		अन्यथा
			पढ़ो_length = (u8)length;

		अगर (पढ़ो_length > 1) अणु
			dev_dbg(&dev->dev, "%s - @ %x for %d\n", __func__, start_address, पढ़ो_length);
		पूर्ण
		/*
		 * NOTE: Must use swab as wIndex is sent in little-endian
		 *       byte order regardless of host byte order.
		 */
		be_start_address = swab16((u16)start_address);
		status = ti_vपढ़ो_sync(dev, UMPC_MEMORY_READ,
					(u16)address_type,
					be_start_address,
					buffer, पढ़ो_length);

		अगर (status) अणु
			dev_dbg(&dev->dev, "%s - ERROR %x\n", __func__, status);
			वापस status;
		पूर्ण

		अगर (पढ़ो_length > 1)
			usb_serial_debug_data(&dev->dev, __func__, पढ़ो_length, buffer);

		/* Update poपूर्णांकers/length */
		start_address += पढ़ो_length;
		buffer += पढ़ो_length;
		length -= पढ़ो_length;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक पढ़ो_ram(काष्ठा usb_device *dev, पूर्णांक start_address,
						पूर्णांक length, u8 *buffer)
अणु
	वापस पढ़ो_करोwnload_mem(dev, start_address, length,
					DTK_ADDR_SPACE_XDATA, buffer);
पूर्ण

/* Read edgeport memory to a given block */
अटल पूर्णांक पढ़ो_boot_mem(काष्ठा edgeport_serial *serial,
				पूर्णांक start_address, पूर्णांक length, u8 *buffer)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;

	क्रम (i = 0; i < length; i++) अणु
		status = ti_vपढ़ो_sync(serial->serial->dev,
				UMPC_MEMORY_READ, serial->TI_I2C_Type,
				(u16)(start_address+i), &buffer[i], 0x01);
		अगर (status) अणु
			dev_dbg(&serial->serial->dev->dev, "%s - ERROR %x\n", __func__, status);
			वापस status;
		पूर्ण
	पूर्ण

	dev_dbg(&serial->serial->dev->dev, "%s - start_address = %x, length = %d\n",
		__func__, start_address, length);
	usb_serial_debug_data(&serial->serial->dev->dev, __func__, length, buffer);

	serial->TiReadI2C = 1;

	वापस status;
पूर्ण

/* Write given block to TI EPROM memory */
अटल पूर्णांक ग_लिखो_boot_mem(काष्ठा edgeport_serial *serial,
				पूर्णांक start_address, पूर्णांक length, u8 *buffer)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;
	u8 *temp;

	/* Must करो a पढ़ो beक्रमe ग_लिखो */
	अगर (!serial->TiReadI2C) अणु
		temp = kदो_स्मृति(1, GFP_KERNEL);
		अगर (!temp)
			वापस -ENOMEM;

		status = पढ़ो_boot_mem(serial, 0, 1, temp);
		kमुक्त(temp);
		अगर (status)
			वापस status;
	पूर्ण

	क्रम (i = 0; i < length; ++i) अणु
		status = ti_vsend_sync(serial->serial->dev, UMPC_MEMORY_WRITE,
				buffer[i], (u16)(i + start_address), शून्य,
				0, TI_VSEND_TIMEOUT_DEFAULT);
		अगर (status)
			वापस status;
	पूर्ण

	dev_dbg(&serial->serial->dev->dev, "%s - start_sddr = %x, length = %d\n", __func__, start_address, length);
	usb_serial_debug_data(&serial->serial->dev->dev, __func__, length, buffer);

	वापस status;
पूर्ण

/* Write edgeport I2C memory to TI chip	*/
अटल पूर्णांक ग_लिखो_i2c_mem(काष्ठा edgeport_serial *serial,
		पूर्णांक start_address, पूर्णांक length, u8 address_type, u8 *buffer)
अणु
	काष्ठा device *dev = &serial->serial->dev->dev;
	पूर्णांक status = 0;
	पूर्णांक ग_लिखो_length;
	u16 be_start_address;

	/* We can only send a maximum of 1 aligned byte page at a समय */

	/* calculate the number of bytes left in the first page */
	ग_लिखो_length = EPROM_PAGE_SIZE -
				(start_address & (EPROM_PAGE_SIZE - 1));

	अगर (ग_लिखो_length > length)
		ग_लिखो_length = length;

	dev_dbg(dev, "%s - BytesInFirstPage Addr = %x, length = %d\n",
		__func__, start_address, ग_लिखो_length);
	usb_serial_debug_data(dev, __func__, ग_लिखो_length, buffer);

	/*
	 * Write first page.
	 *
	 * NOTE: Must use swab as wIndex is sent in little-endian byte order
	 *       regardless of host byte order.
	 */
	be_start_address = swab16((u16)start_address);
	status = ti_vsend_sync(serial->serial->dev, UMPC_MEMORY_WRITE,
				(u16)address_type, be_start_address,
				buffer,	ग_लिखो_length, TI_VSEND_TIMEOUT_DEFAULT);
	अगर (status) अणु
		dev_dbg(dev, "%s - ERROR %d\n", __func__, status);
		वापस status;
	पूर्ण

	length		-= ग_लिखो_length;
	start_address	+= ग_लिखो_length;
	buffer		+= ग_लिखो_length;

	/*
	 * We should be aligned now -- can ग_लिखो max page size bytes at a
	 * समय.
	 */
	जबतक (length) अणु
		अगर (length > EPROM_PAGE_SIZE)
			ग_लिखो_length = EPROM_PAGE_SIZE;
		अन्यथा
			ग_लिखो_length = length;

		dev_dbg(dev, "%s - Page Write Addr = %x, length = %d\n",
			__func__, start_address, ग_लिखो_length);
		usb_serial_debug_data(dev, __func__, ग_लिखो_length, buffer);

		/*
		 * Write next page.
		 *
		 * NOTE: Must use swab as wIndex is sent in little-endian byte
		 *       order regardless of host byte order.
		 */
		be_start_address = swab16((u16)start_address);
		status = ti_vsend_sync(serial->serial->dev, UMPC_MEMORY_WRITE,
				(u16)address_type, be_start_address, buffer,
				ग_लिखो_length, TI_VSEND_TIMEOUT_DEFAULT);
		अगर (status) अणु
			dev_err(dev, "%s - ERROR %d\n", __func__, status);
			वापस status;
		पूर्ण

		length		-= ग_लिखो_length;
		start_address	+= ग_लिखो_length;
		buffer		+= ग_लिखो_length;
	पूर्ण
	वापस status;
पूर्ण

/*
 * Examine the UMP DMA रेजिस्टरs and LSR
 *
 * Check the MSBit of the X and Y DMA byte count रेजिस्टरs.
 * A zero in this bit indicates that the TX DMA buffers are empty
 * then check the TX Empty bit in the UART.
 */
अटल पूर्णांक tx_active(काष्ठा edgeport_port *port)
अणु
	पूर्णांक status;
	काष्ठा out_endpoपूर्णांक_desc_block *oedb;
	u8 *lsr;
	पूर्णांक bytes_left = 0;

	oedb = kदो_स्मृति(माप(*oedb), GFP_KERNEL);
	अगर (!oedb)
		वापस -ENOMEM;

	/*
	 * Sigh, that's right, just one byte, as not all platक्रमms can
	 * करो DMA from stack
	 */
	lsr = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!lsr) अणु
		kमुक्त(oedb);
		वापस -ENOMEM;
	पूर्ण
	/* Read the DMA Count Registers */
	status = पढ़ो_ram(port->port->serial->dev, port->dma_address,
						माप(*oedb), (व्योम *)oedb);
	अगर (status)
		जाओ निकास_is_tx_active;

	dev_dbg(&port->port->dev, "%s - XByteCount    0x%X\n", __func__, oedb->XByteCount);

	/* and the LSR */
	status = पढ़ो_ram(port->port->serial->dev,
			port->uart_base + UMPMEM_OFFS_UART_LSR, 1, lsr);

	अगर (status)
		जाओ निकास_is_tx_active;
	dev_dbg(&port->port->dev, "%s - LSR = 0x%X\n", __func__, *lsr);

	/* If either buffer has data or we are transmitting then वापस TRUE */
	अगर ((oedb->XByteCount & 0x80) != 0)
		bytes_left += 64;

	अगर ((*lsr & UMP_UART_LSR_TX_MASK) == 0)
		bytes_left += 1;

	/* We वापस Not Active अगर we get any kind of error */
निकास_is_tx_active:
	dev_dbg(&port->port->dev, "%s - return %d\n", __func__, bytes_left);

	kमुक्त(lsr);
	kमुक्त(oedb);
	वापस bytes_left;
पूर्ण

अटल पूर्णांक choose_config(काष्ठा usb_device *dev)
अणु
	/*
	 * There may be multiple configurations on this device, in which हाल
	 * we would need to पढ़ो and parse all of them to find out which one
	 * we want. However, we just support one config at this poपूर्णांक,
	 * configuration # 1, which is Config Descriptor 0.
	 */

	dev_dbg(&dev->dev, "%s - Number of Interfaces = %d\n",
		__func__, dev->config->desc.bNumInterfaces);
	dev_dbg(&dev->dev, "%s - MAX Power            = %d\n",
		__func__, dev->config->desc.bMaxPower * 2);

	अगर (dev->config->desc.bNumInterfaces != 1) अणु
		dev_err(&dev->dev, "%s - bNumInterfaces is not 1, ERROR!\n", __func__);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_rom(काष्ठा edgeport_serial *serial,
				पूर्णांक start_address, पूर्णांक length, u8 *buffer)
अणु
	पूर्णांक status;

	अगर (serial->product_info.TiMode == TI_MODE_DOWNLOAD) अणु
		status = पढ़ो_करोwnload_mem(serial->serial->dev,
					       start_address,
					       length,
					       serial->TI_I2C_Type,
					       buffer);
	पूर्ण अन्यथा अणु
		status = पढ़ो_boot_mem(serial, start_address, length,
								buffer);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक ग_लिखो_rom(काष्ठा edgeport_serial *serial, पूर्णांक start_address,
						पूर्णांक length, u8 *buffer)
अणु
	अगर (serial->product_info.TiMode == TI_MODE_BOOT)
		वापस ग_लिखो_boot_mem(serial, start_address, length,
								buffer);

	अगर (serial->product_info.TiMode == TI_MODE_DOWNLOAD)
		वापस ग_लिखो_i2c_mem(serial, start_address, length,
						serial->TI_I2C_Type, buffer);
	वापस -EINVAL;
पूर्ण

/* Read a descriptor header from I2C based on type */
अटल पूर्णांक get_descriptor_addr(काष्ठा edgeport_serial *serial,
				पूर्णांक desc_type, काष्ठा ti_i2c_desc *rom_desc)
अणु
	पूर्णांक start_address;
	पूर्णांक status;

	/* Search क्रम requested descriptor in I2C */
	start_address = 2;
	करो अणु
		status = पढ़ो_rom(serial,
				   start_address,
				   माप(काष्ठा ti_i2c_desc),
				   (u8 *)rom_desc);
		अगर (status)
			वापस 0;

		अगर (rom_desc->Type == desc_type)
			वापस start_address;

		start_address = start_address + माप(काष्ठा ti_i2c_desc) +
						le16_to_cpu(rom_desc->Size);

	पूर्ण जबतक ((start_address < TI_MAX_I2C_SIZE) && rom_desc->Type);

	वापस 0;
पूर्ण

/* Validate descriptor checksum */
अटल पूर्णांक valid_csum(काष्ठा ti_i2c_desc *rom_desc, u8 *buffer)
अणु
	u16 i;
	u8 cs = 0;

	क्रम (i = 0; i < le16_to_cpu(rom_desc->Size); i++)
		cs = (u8)(cs + buffer[i]);

	अगर (cs != rom_desc->CheckSum) अणु
		pr_debug("%s - Mismatch %x - %x", __func__, rom_desc->CheckSum, cs);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Make sure that the I2C image is good */
अटल पूर्णांक check_i2c_image(काष्ठा edgeport_serial *serial)
अणु
	काष्ठा device *dev = &serial->serial->dev->dev;
	पूर्णांक status = 0;
	काष्ठा ti_i2c_desc *rom_desc;
	पूर्णांक start_address = 2;
	u8 *buffer;
	u16 ttype;

	rom_desc = kदो_स्मृति(माप(*rom_desc), GFP_KERNEL);
	अगर (!rom_desc)
		वापस -ENOMEM;

	buffer = kदो_स्मृति(TI_MAX_I2C_SIZE, GFP_KERNEL);
	अगर (!buffer) अणु
		kमुक्त(rom_desc);
		वापस -ENOMEM;
	पूर्ण

	/* Read the first byte (Signature0) must be 0x52 or 0x10 */
	status = पढ़ो_rom(serial, 0, 1, buffer);
	अगर (status)
		जाओ out;

	अगर (*buffer != UMP5152 && *buffer != UMP3410) अणु
		dev_err(dev, "%s - invalid buffer signature\n", __func__);
		status = -ENODEV;
		जाओ out;
	पूर्ण

	करो अणु
		/* Validate the I2C */
		status = पढ़ो_rom(serial,
				start_address,
				माप(काष्ठा ti_i2c_desc),
				(u8 *)rom_desc);
		अगर (status)
			अवरोध;

		अगर ((start_address + माप(काष्ठा ti_i2c_desc) +
			le16_to_cpu(rom_desc->Size)) > TI_MAX_I2C_SIZE) अणु
			status = -ENODEV;
			dev_dbg(dev, "%s - structure too big, erroring out.\n", __func__);
			अवरोध;
		पूर्ण

		dev_dbg(dev, "%s Type = 0x%x\n", __func__, rom_desc->Type);

		/* Skip type 2 record */
		ttype = rom_desc->Type & 0x0f;
		अगर (ttype != I2C_DESC_TYPE_FIRMWARE_BASIC
			&& ttype != I2C_DESC_TYPE_FIRMWARE_AUTO) अणु
			/* Read the descriptor data */
			status = पढ़ो_rom(serial, start_address +
						माप(काष्ठा ti_i2c_desc),
						le16_to_cpu(rom_desc->Size),
						buffer);
			अगर (status)
				अवरोध;

			status = valid_csum(rom_desc, buffer);
			अगर (status)
				अवरोध;
		पूर्ण
		start_address = start_address + माप(काष्ठा ti_i2c_desc) +
						le16_to_cpu(rom_desc->Size);

	पूर्ण जबतक ((rom_desc->Type != I2C_DESC_TYPE_ION) &&
				(start_address < TI_MAX_I2C_SIZE));

	अगर ((rom_desc->Type != I2C_DESC_TYPE_ION) ||
				(start_address > TI_MAX_I2C_SIZE))
		status = -ENODEV;

out:
	kमुक्त(buffer);
	kमुक्त(rom_desc);
	वापस status;
पूर्ण

अटल पूर्णांक get_manuf_info(काष्ठा edgeport_serial *serial, u8 *buffer)
अणु
	पूर्णांक status;
	पूर्णांक start_address;
	काष्ठा ti_i2c_desc *rom_desc;
	काष्ठा edge_ti_manuf_descriptor *desc;
	काष्ठा device *dev = &serial->serial->dev->dev;

	rom_desc = kदो_स्मृति(माप(*rom_desc), GFP_KERNEL);
	अगर (!rom_desc)
		वापस -ENOMEM;

	start_address = get_descriptor_addr(serial, I2C_DESC_TYPE_ION,
								rom_desc);

	अगर (!start_address) अणु
		dev_dbg(dev, "%s - Edge Descriptor not found in I2C\n", __func__);
		status = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* Read the descriptor data */
	status = पढ़ो_rom(serial, start_address+माप(काष्ठा ti_i2c_desc),
					le16_to_cpu(rom_desc->Size), buffer);
	अगर (status)
		जाओ निकास;

	status = valid_csum(rom_desc, buffer);

	desc = (काष्ठा edge_ti_manuf_descriptor *)buffer;
	dev_dbg(dev, "%s - IonConfig      0x%x\n", __func__, desc->IonConfig);
	dev_dbg(dev, "%s - Version          %d\n", __func__, desc->Version);
	dev_dbg(dev, "%s - Cpu/Board      0x%x\n", __func__, desc->CpuRev_BoardRev);
	dev_dbg(dev, "%s - NumPorts         %d\n", __func__, desc->NumPorts);
	dev_dbg(dev, "%s - NumVirtualPorts  %d\n", __func__, desc->NumVirtualPorts);
	dev_dbg(dev, "%s - TotalPorts       %d\n", __func__, desc->TotalPorts);

निकास:
	kमुक्त(rom_desc);
	वापस status;
पूर्ण

/* Build firmware header used क्रम firmware update */
अटल पूर्णांक build_i2c_fw_hdr(u8 *header, स्थिर काष्ठा firmware *fw)
अणु
	u8 *buffer;
	पूर्णांक buffer_size;
	पूर्णांक i;
	u8 cs = 0;
	काष्ठा ti_i2c_desc *i2c_header;
	काष्ठा ti_i2c_image_header *img_header;
	काष्ठा ti_i2c_firmware_rec *firmware_rec;
	काष्ठा edgeport_fw_hdr *fw_hdr = (काष्ठा edgeport_fw_hdr *)fw->data;

	/*
	 * In order to update the I2C firmware we must change the type 2 record
	 * to type 0xF2.  This will क्रमce the UMP to come up in Boot Mode.
	 * Then जबतक in boot mode, the driver will करोwnload the latest
	 * firmware (padded to 15.5k) पूर्णांकo the UMP ram.  And finally when the
	 * device comes back up in करोwnload mode the driver will cause the new
	 * firmware to be copied from the UMP Ram to I2C and the firmware will
	 * update the record type from 0xf2 to 0x02.
	 */

	/*
	 * Allocate a 15.5k buffer + 2 bytes क्रम version number (Firmware
	 * Record)
	 */
	buffer_size = (((1024 * 16) - 512 ) +
			माप(काष्ठा ti_i2c_firmware_rec));

	buffer = kदो_स्मृति(buffer_size, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/* Set entire image of 0xffs */
	स_रखो(buffer, 0xff, buffer_size);

	/* Copy version number पूर्णांकo firmware record */
	firmware_rec = (काष्ठा ti_i2c_firmware_rec *)buffer;

	firmware_rec->Ver_Major	= fw_hdr->major_version;
	firmware_rec->Ver_Minor	= fw_hdr->minor_version;

	/* Poपूर्णांकer to fw_करोwn memory image */
	img_header = (काष्ठा ti_i2c_image_header *)&fw->data[4];

	स_नकल(buffer + माप(काष्ठा ti_i2c_firmware_rec),
		&fw->data[4 + माप(काष्ठा ti_i2c_image_header)],
		le16_to_cpu(img_header->Length));

	क्रम (i=0; i < buffer_size; i++) अणु
		cs = (u8)(cs + buffer[i]);
	पूर्ण

	kमुक्त(buffer);

	/* Build new header */
	i2c_header =  (काष्ठा ti_i2c_desc *)header;
	firmware_rec =  (काष्ठा ti_i2c_firmware_rec*)i2c_header->Data;

	i2c_header->Type	= I2C_DESC_TYPE_FIRMWARE_BLANK;
	i2c_header->Size	= cpu_to_le16(buffer_size);
	i2c_header->CheckSum	= cs;
	firmware_rec->Ver_Major	= fw_hdr->major_version;
	firmware_rec->Ver_Minor	= fw_hdr->minor_version;

	वापस 0;
पूर्ण

/* Try to figure out what type of I2c we have */
अटल पूर्णांक i2c_type_booपंचांगode(काष्ठा edgeport_serial *serial)
अणु
	काष्ठा device *dev = &serial->serial->dev->dev;
	पूर्णांक status;
	u8 *data;

	data = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* Try to पढ़ो type 2 */
	status = ti_vपढ़ो_sync(serial->serial->dev, UMPC_MEMORY_READ,
				DTK_ADDR_SPACE_I2C_TYPE_II, 0, data, 0x01);
	अगर (status)
		dev_dbg(dev, "%s - read 2 status error = %d\n", __func__, status);
	अन्यथा
		dev_dbg(dev, "%s - read 2 data = 0x%x\n", __func__, *data);
	अगर ((!status) && (*data == UMP5152 || *data == UMP3410)) अणु
		dev_dbg(dev, "%s - ROM_TYPE_II\n", __func__);
		serial->TI_I2C_Type = DTK_ADDR_SPACE_I2C_TYPE_II;
		जाओ out;
	पूर्ण

	/* Try to पढ़ो type 3 */
	status = ti_vपढ़ो_sync(serial->serial->dev, UMPC_MEMORY_READ,
				DTK_ADDR_SPACE_I2C_TYPE_III, 0,	data, 0x01);
	अगर (status)
		dev_dbg(dev, "%s - read 3 status error = %d\n", __func__, status);
	अन्यथा
		dev_dbg(dev, "%s - read 2 data = 0x%x\n", __func__, *data);
	अगर ((!status) && (*data == UMP5152 || *data == UMP3410)) अणु
		dev_dbg(dev, "%s - ROM_TYPE_III\n", __func__);
		serial->TI_I2C_Type = DTK_ADDR_SPACE_I2C_TYPE_III;
		जाओ out;
	पूर्ण

	dev_dbg(dev, "%s - Unknown\n", __func__);
	serial->TI_I2C_Type = DTK_ADDR_SPACE_I2C_TYPE_II;
	status = -ENODEV;
out:
	kमुक्त(data);
	वापस status;
पूर्ण

अटल पूर्णांक bulk_xfer(काष्ठा usb_serial *serial, व्योम *buffer,
						पूर्णांक length, पूर्णांक *num_sent)
अणु
	पूर्णांक status;

	status = usb_bulk_msg(serial->dev,
			usb_sndbulkpipe(serial->dev,
				serial->port[0]->bulk_out_endpoपूर्णांकAddress),
			buffer, length, num_sent, 1000);
	वापस status;
पूर्ण

/* Download given firmware image to the device (IN BOOT MODE) */
अटल पूर्णांक करोwnload_code(काष्ठा edgeport_serial *serial, u8 *image,
							पूर्णांक image_length)
अणु
	पूर्णांक status = 0;
	पूर्णांक pos;
	पूर्णांक transfer;
	पूर्णांक करोne;

	/* Transfer firmware image */
	क्रम (pos = 0; pos < image_length; ) अणु
		/* Read the next buffer from file */
		transfer = image_length - pos;
		अगर (transfer > EDGE_FW_BULK_MAX_PACKET_SIZE)
			transfer = EDGE_FW_BULK_MAX_PACKET_SIZE;

		/* Transfer data */
		status = bulk_xfer(serial->serial, &image[pos],
							transfer, &करोne);
		अगर (status)
			अवरोध;
		/* Advance buffer poपूर्णांकer */
		pos += करोne;
	पूर्ण

	वापस status;
पूर्ण

/* FIXME!!! */
अटल पूर्णांक config_boot_dev(काष्ठा usb_device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ti_cpu_rev(काष्ठा edge_ti_manuf_descriptor *desc)
अणु
	वापस TI_GET_CPU_REVISION(desc->CpuRev_BoardRev);
पूर्ण

अटल पूर्णांक check_fw_sanity(काष्ठा edgeport_serial *serial,
		स्थिर काष्ठा firmware *fw)
अणु
	u16 length_total;
	u8 checksum = 0;
	पूर्णांक pos;
	काष्ठा device *dev = &serial->serial->पूर्णांकerface->dev;
	काष्ठा edgeport_fw_hdr *fw_hdr = (काष्ठा edgeport_fw_hdr *)fw->data;

	अगर (fw->size < माप(काष्ठा edgeport_fw_hdr)) अणु
		dev_err(dev, "incomplete fw header\n");
		वापस -EINVAL;
	पूर्ण

	length_total = le16_to_cpu(fw_hdr->length) +
			माप(काष्ठा edgeport_fw_hdr);

	अगर (fw->size != length_total) अणु
		dev_err(dev, "bad fw size (expected: %u, got: %zu)\n",
				length_total, fw->size);
		वापस -EINVAL;
	पूर्ण

	क्रम (pos = माप(काष्ठा edgeport_fw_hdr); pos < fw->size; ++pos)
		checksum += fw->data[pos];

	अगर (checksum != fw_hdr->checksum) अणु
		dev_err(dev, "bad fw checksum (expected: 0x%x, got: 0x%x)\n",
				fw_hdr->checksum, checksum);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * DownloadTIFirmware - Download run-समय operating firmware to the TI5052
 *
 * This routine करोwnloads the मुख्य operating code पूर्णांकo the TI5052, using the
 * boot code alपढ़ोy burned पूर्णांकo E2PROM or ROM.
 */
अटल पूर्णांक करोwnload_fw(काष्ठा edgeport_serial *serial)
अणु
	काष्ठा device *dev = &serial->serial->पूर्णांकerface->dev;
	पूर्णांक status = 0;
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकerface;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name = "edgeport/down3.bin";
	काष्ठा edgeport_fw_hdr *fw_hdr;

	status = request_firmware(&fw, fw_name, dev);
	अगर (status) अणु
		dev_err(dev, "Failed to load image \"%s\" err %d\n",
				fw_name, status);
		वापस status;
	पूर्ण

	अगर (check_fw_sanity(serial, fw)) अणु
		status = -EINVAL;
		जाओ out;
	पूर्ण

	fw_hdr = (काष्ठा edgeport_fw_hdr *)fw->data;

	/* If on-board version is newer, "fw_version" will be updated later. */
	serial->fw_version = (fw_hdr->major_version << 8) +
			fw_hdr->minor_version;

	/*
	 * This routine is entered by both the BOOT mode and the Download mode
	 * We can determine which code is running by the पढ़ोing the config
	 * descriptor and अगर we have only one bulk pipe it is in boot mode
	 */
	serial->product_info.hardware_type = HARDWARE_TYPE_TIUMP;

	/* Default to type 2 i2c */
	serial->TI_I2C_Type = DTK_ADDR_SPACE_I2C_TYPE_II;

	status = choose_config(serial->serial->dev);
	अगर (status)
		जाओ out;

	पूर्णांकerface = &serial->serial->पूर्णांकerface->cur_altsetting->desc;
	अगर (!पूर्णांकerface) अणु
		dev_err(dev, "%s - no interface set, error!\n", __func__);
		status = -ENODEV;
		जाओ out;
	पूर्ण

	/*
	 * Setup initial mode -- the शेष mode 0 is TI_MODE_CONFIGURING
	 * अगर we have more than one endpoपूर्णांक we are definitely in करोwnload
	 * mode
	 */
	अगर (पूर्णांकerface->bNumEndpoपूर्णांकs > 1) अणु
		serial->product_info.TiMode = TI_MODE_DOWNLOAD;
		status = करो_करोwnload_mode(serial, fw);
	पूर्ण अन्यथा अणु
		/* Otherwise we will reमुख्य in configuring mode */
		serial->product_info.TiMode = TI_MODE_CONFIGURING;
		status = करो_boot_mode(serial, fw);
	पूर्ण

out:
	release_firmware(fw);
	वापस status;
पूर्ण

अटल पूर्णांक करो_करोwnload_mode(काष्ठा edgeport_serial *serial,
		स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &serial->serial->पूर्णांकerface->dev;
	पूर्णांक status = 0;
	पूर्णांक start_address;
	काष्ठा edge_ti_manuf_descriptor *ti_manuf_desc;
	पूर्णांक करोwnload_cur_ver;
	पूर्णांक करोwnload_new_ver;
	काष्ठा edgeport_fw_hdr *fw_hdr = (काष्ठा edgeport_fw_hdr *)fw->data;
	काष्ठा ti_i2c_desc *rom_desc;

	dev_dbg(dev, "%s - RUNNING IN DOWNLOAD MODE\n", __func__);

	status = check_i2c_image(serial);
	अगर (status) अणु
		dev_dbg(dev, "%s - DOWNLOAD MODE -- BAD I2C\n", __func__);
		वापस status;
	पूर्ण

	/*
	 * Validate Hardware version number
	 * Read Manufacturing Descriptor from TI Based Edgeport
	 */
	ti_manuf_desc = kदो_स्मृति(माप(*ti_manuf_desc), GFP_KERNEL);
	अगर (!ti_manuf_desc)
		वापस -ENOMEM;

	status = get_manuf_info(serial, (u8 *)ti_manuf_desc);
	अगर (status) अणु
		kमुक्त(ti_manuf_desc);
		वापस status;
	पूर्ण

	/* Check version number of ION descriptor */
	अगर (!ignore_cpu_rev && ti_cpu_rev(ti_manuf_desc) < 2) अणु
		dev_dbg(dev, "%s - Wrong CPU Rev %d (Must be 2)\n",
			__func__, ti_cpu_rev(ti_manuf_desc));
		kमुक्त(ti_manuf_desc);
		वापस -EINVAL;
	पूर्ण

	rom_desc = kदो_स्मृति(माप(*rom_desc), GFP_KERNEL);
	अगर (!rom_desc) अणु
		kमुक्त(ti_manuf_desc);
		वापस -ENOMEM;
	पूर्ण

	/* Search क्रम type 2 record (firmware record) */
	start_address = get_descriptor_addr(serial,
			I2C_DESC_TYPE_FIRMWARE_BASIC, rom_desc);
	अगर (start_address != 0) अणु
		काष्ठा ti_i2c_firmware_rec *firmware_version;
		u8 *record;

		dev_dbg(dev, "%s - Found Type FIRMWARE (Type 2) record\n",
				__func__);

		firmware_version = kदो_स्मृति(माप(*firmware_version),
							GFP_KERNEL);
		अगर (!firmware_version) अणु
			kमुक्त(rom_desc);
			kमुक्त(ti_manuf_desc);
			वापस -ENOMEM;
		पूर्ण

		/*
		 * Validate version number
		 * Read the descriptor data
		 */
		status = पढ़ो_rom(serial, start_address +
				माप(काष्ठा ti_i2c_desc),
				माप(काष्ठा ti_i2c_firmware_rec),
				(u8 *)firmware_version);
		अगर (status) अणु
			kमुक्त(firmware_version);
			kमुक्त(rom_desc);
			kमुक्त(ti_manuf_desc);
			वापस status;
		पूर्ण

		/*
		 * Check version number of करोwnload with current
		 * version in I2c
		 */
		करोwnload_cur_ver = (firmware_version->Ver_Major << 8) +
				   (firmware_version->Ver_Minor);
		करोwnload_new_ver = (fw_hdr->major_version << 8) +
				   (fw_hdr->minor_version);

		dev_dbg(dev, "%s - >> FW Versions Device %d.%d  Driver %d.%d\n",
			__func__, firmware_version->Ver_Major,
			firmware_version->Ver_Minor,
			fw_hdr->major_version, fw_hdr->minor_version);

		/*
		 * Check अगर we have an old version in the I2C and
		 * update अगर necessary
		 */
		अगर (करोwnload_cur_ver < करोwnload_new_ver) अणु
			dev_dbg(dev, "%s - Update I2C dld from %d.%d to %d.%d\n",
				__func__,
				firmware_version->Ver_Major,
				firmware_version->Ver_Minor,
				fw_hdr->major_version,
				fw_hdr->minor_version);

			record = kदो_स्मृति(1, GFP_KERNEL);
			अगर (!record) अणु
				kमुक्त(firmware_version);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस -ENOMEM;
			पूर्ण
			/*
			 * In order to update the I2C firmware we must
			 * change the type 2 record to type 0xF2. This
			 * will क्रमce the UMP to come up in Boot Mode.
			 * Then जबतक in boot mode, the driver will
			 * करोwnload the latest firmware (padded to
			 * 15.5k) पूर्णांकo the UMP ram. Finally when the
			 * device comes back up in करोwnload mode the
			 * driver will cause the new firmware to be
			 * copied from the UMP Ram to I2C and the
			 * firmware will update the record type from
			 * 0xf2 to 0x02.
			 */
			*record = I2C_DESC_TYPE_FIRMWARE_BLANK;

			/*
			 * Change the I2C Firmware record type to
			 * 0xf2 to trigger an update
			 */
			status = ग_लिखो_rom(serial, start_address,
					माप(*record), record);
			अगर (status) अणु
				kमुक्त(record);
				kमुक्त(firmware_version);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस status;
			पूर्ण

			/*
			 * verअगरy the ग_लिखो -- must करो this in order
			 * क्रम ग_लिखो to complete beक्रमe we करो the
			 * hardware reset
			 */
			status = पढ़ो_rom(serial,
						start_address,
						माप(*record),
						record);
			अगर (status) अणु
				kमुक्त(record);
				kमुक्त(firmware_version);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस status;
			पूर्ण

			अगर (*record != I2C_DESC_TYPE_FIRMWARE_BLANK) अणु
				dev_err(dev, "%s - error resetting device\n",
						__func__);
				kमुक्त(record);
				kमुक्त(firmware_version);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस -ENODEV;
			पूर्ण

			dev_dbg(dev, "%s - HARDWARE RESET\n", __func__);

			/* Reset UMP -- Back to BOOT MODE */
			status = ti_vsend_sync(serial->serial->dev,
					UMPC_HARDWARE_RESET,
					0, 0, शून्य, 0,
					TI_VSEND_TIMEOUT_DEFAULT);

			dev_dbg(dev, "%s - HARDWARE RESET return %d\n",
					__func__, status);

			/* वापस an error on purpose. */
			kमुक्त(record);
			kमुक्त(firmware_version);
			kमुक्त(rom_desc);
			kमुक्त(ti_manuf_desc);
			वापस -ENODEV;
		पूर्ण
		/* Same or newer fw version is alपढ़ोy loaded */
		serial->fw_version = करोwnload_cur_ver;
		kमुक्त(firmware_version);
	पूर्ण
	/* Search क्रम type 0xF2 record (firmware blank record) */
	अन्यथा अणु
		start_address = get_descriptor_addr(serial,
				I2C_DESC_TYPE_FIRMWARE_BLANK, rom_desc);
		अगर (start_address != 0) अणु
#घोषणा HEADER_SIZE	(माप(काष्ठा ti_i2c_desc) + \
				माप(काष्ठा ti_i2c_firmware_rec))
			u8 *header;
			u8 *vheader;

			header = kदो_स्मृति(HEADER_SIZE, GFP_KERNEL);
			अगर (!header) अणु
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस -ENOMEM;
			पूर्ण

			vheader = kदो_स्मृति(HEADER_SIZE, GFP_KERNEL);
			अगर (!vheader) अणु
				kमुक्त(header);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस -ENOMEM;
			पूर्ण

			dev_dbg(dev, "%s - Found Type BLANK FIRMWARE (Type F2) record\n",
					__func__);

			/*
			 * In order to update the I2C firmware we must change
			 * the type 2 record to type 0xF2. This will क्रमce the
			 * UMP to come up in Boot Mode.  Then जबतक in boot
			 * mode, the driver will करोwnload the latest firmware
			 * (padded to 15.5k) पूर्णांकo the UMP ram. Finally when the
			 * device comes back up in करोwnload mode the driver
			 * will cause the new firmware to be copied from the
			 * UMP Ram to I2C and the firmware will update the
			 * record type from 0xf2 to 0x02.
			 */
			status = build_i2c_fw_hdr(header, fw);
			अगर (status) अणु
				kमुक्त(vheader);
				kमुक्त(header);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस -EINVAL;
			पूर्ण

			/*
			 * Update I2C with type 0xf2 record with correct
			 * size and checksum
			 */
			status = ग_लिखो_rom(serial,
						start_address,
						HEADER_SIZE,
						header);
			अगर (status) अणु
				kमुक्त(vheader);
				kमुक्त(header);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस -EINVAL;
			पूर्ण

			/*
			 * verअगरy the ग_लिखो -- must करो this in order क्रम
			 * ग_लिखो to complete beक्रमe we करो the hardware reset
			 */
			status = पढ़ो_rom(serial, start_address,
							HEADER_SIZE, vheader);

			अगर (status) अणु
				dev_dbg(dev, "%s - can't read header back\n",
						__func__);
				kमुक्त(vheader);
				kमुक्त(header);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस status;
			पूर्ण
			अगर (स_भेद(vheader, header, HEADER_SIZE)) अणु
				dev_dbg(dev, "%s - write download record failed\n",
						__func__);
				kमुक्त(vheader);
				kमुक्त(header);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस -EINVAL;
			पूर्ण

			kमुक्त(vheader);
			kमुक्त(header);

			dev_dbg(dev, "%s - Start firmware update\n", __func__);

			/* Tell firmware to copy करोwnload image पूर्णांकo I2C */
			status = ti_vsend_sync(serial->serial->dev,
					UMPC_COPY_DNLD_TO_I2C,
					0, 0, शून्य, 0,
					TI_VSEND_TIMEOUT_FW_DOWNLOAD);

			dev_dbg(dev, "%s - Update complete 0x%x\n", __func__,
					status);
			अगर (status) अणु
				dev_err(dev,
					"%s - UMPC_COPY_DNLD_TO_I2C failed\n",
					__func__);
				kमुक्त(rom_desc);
				kमुक्त(ti_manuf_desc);
				वापस status;
			पूर्ण
		पूर्ण
	पूर्ण

	/* The device is running the करोwnload code */
	kमुक्त(rom_desc);
	kमुक्त(ti_manuf_desc);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_boot_mode(काष्ठा edgeport_serial *serial,
		स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &serial->serial->पूर्णांकerface->dev;
	पूर्णांक status = 0;
	काष्ठा edge_ti_manuf_descriptor *ti_manuf_desc;
	काष्ठा edgeport_fw_hdr *fw_hdr = (काष्ठा edgeport_fw_hdr *)fw->data;

	dev_dbg(dev, "%s - RUNNING IN BOOT MODE\n", __func__);

	/* Configure the TI device so we can use the BULK pipes क्रम करोwnload */
	status = config_boot_dev(serial->serial->dev);
	अगर (status)
		वापस status;

	अगर (le16_to_cpu(serial->serial->dev->descriptor.idVenकरोr)
							!= USB_VENDOR_ID_ION) अणु
		dev_dbg(dev, "%s - VID = 0x%x\n", __func__,
			le16_to_cpu(serial->serial->dev->descriptor.idVenकरोr));
		serial->TI_I2C_Type = DTK_ADDR_SPACE_I2C_TYPE_II;
		जाओ stayinbooपंचांगode;
	पूर्ण

	/*
	 * We have an ION device (I2c Must be programmed)
	 * Determine I2C image type
	 */
	अगर (i2c_type_booपंचांगode(serial))
		जाओ stayinbooपंचांगode;

	/* Check क्रम ION Venकरोr ID and that the I2C is valid */
	अगर (!check_i2c_image(serial)) अणु
		काष्ठा ti_i2c_image_header *header;
		पूर्णांक i;
		u8 cs = 0;
		u8 *buffer;
		पूर्णांक buffer_size;

		/*
		 * Validate Hardware version number
		 * Read Manufacturing Descriptor from TI Based Edgeport
		 */
		ti_manuf_desc = kदो_स्मृति(माप(*ti_manuf_desc), GFP_KERNEL);
		अगर (!ti_manuf_desc)
			वापस -ENOMEM;

		status = get_manuf_info(serial, (u8 *)ti_manuf_desc);
		अगर (status) अणु
			kमुक्त(ti_manuf_desc);
			जाओ stayinbooपंचांगode;
		पूर्ण

		/* Check क्रम version 2 */
		अगर (!ignore_cpu_rev && ti_cpu_rev(ti_manuf_desc) < 2) अणु
			dev_dbg(dev, "%s - Wrong CPU Rev %d (Must be 2)\n",
				__func__, ti_cpu_rev(ti_manuf_desc));
			kमुक्त(ti_manuf_desc);
			जाओ stayinbooपंचांगode;
		पूर्ण

		kमुक्त(ti_manuf_desc);

		/*
		 * In order to update the I2C firmware we must change the type
		 * 2 record to type 0xF2. This will क्रमce the UMP to come up
		 * in Boot Mode.  Then जबतक in boot mode, the driver will
		 * करोwnload the latest firmware (padded to 15.5k) पूर्णांकo the
		 * UMP ram. Finally when the device comes back up in करोwnload
		 * mode the driver will cause the new firmware to be copied
		 * from the UMP Ram to I2C and the firmware will update the
		 * record type from 0xf2 to 0x02.
		 *
		 * Do we really have to copy the whole firmware image,
		 * or could we करो this in place!
		 */

		/* Allocate a 15.5k buffer + 3 byte header */
		buffer_size = (((1024 * 16) - 512) +
					माप(काष्ठा ti_i2c_image_header));
		buffer = kदो_स्मृति(buffer_size, GFP_KERNEL);
		अगर (!buffer)
			वापस -ENOMEM;

		/* Initialize the buffer to 0xff (pad the buffer) */
		स_रखो(buffer, 0xff, buffer_size);
		स_नकल(buffer, &fw->data[4], fw->size - 4);

		क्रम (i = माप(काष्ठा ti_i2c_image_header);
				i < buffer_size; i++) अणु
			cs = (u8)(cs + buffer[i]);
		पूर्ण

		header = (काष्ठा ti_i2c_image_header *)buffer;

		/* update length and checksum after padding */
		header->Length = cpu_to_le16((u16)(buffer_size -
					माप(काष्ठा ti_i2c_image_header)));
		header->CheckSum = cs;

		/* Download the operational code  */
		dev_dbg(dev, "%s - Downloading operational code image version %d.%d (TI UMP)\n",
				__func__,
				fw_hdr->major_version, fw_hdr->minor_version);
		status = करोwnload_code(serial, buffer, buffer_size);

		kमुक्त(buffer);

		अगर (status) अणु
			dev_dbg(dev, "%s - Error downloading operational code image\n", __func__);
			वापस status;
		पूर्ण

		/* Device will reboot */
		serial->product_info.TiMode = TI_MODE_TRANSITIONING;

		dev_dbg(dev, "%s - Download successful -- Device rebooting...\n", __func__);

		वापस 1;
	पूर्ण

stayinbooपंचांगode:
	/* Eprom is invalid or blank stay in boot mode */
	dev_dbg(dev, "%s - STAYING IN BOOT MODE\n", __func__);
	serial->product_info.TiMode = TI_MODE_BOOT;

	वापस 1;
पूर्ण

अटल पूर्णांक ti_करो_config(काष्ठा edgeport_port *port, पूर्णांक feature, पूर्णांक on)
अणु
	on = !!on;	/* 1 or 0 not biपंचांगask */

	वापस send_port_cmd(port->port, feature, on, शून्य, 0);
पूर्ण

अटल पूर्णांक restore_mcr(काष्ठा edgeport_port *port, u8 mcr)
अणु
	पूर्णांक status = 0;

	dev_dbg(&port->port->dev, "%s - %x\n", __func__, mcr);

	status = ti_करो_config(port, UMPC_SET_CLR_DTR, mcr & MCR_DTR);
	अगर (status)
		वापस status;
	status = ti_करो_config(port, UMPC_SET_CLR_RTS, mcr & MCR_RTS);
	अगर (status)
		वापस status;
	वापस ti_करो_config(port, UMPC_SET_CLR_LOOPBACK, mcr & MCR_LOOPBACK);
पूर्ण

/* Convert TI LSR to standard UART flags */
अटल u8 map_line_status(u8 ti_lsr)
अणु
	u8 lsr = 0;

#घोषणा MAP_FLAG(flagUmp, flagUart)    \
	अगर (ti_lsr & flagUmp) \
		lsr |= flagUart;

	MAP_FLAG(UMP_UART_LSR_OV_MASK, LSR_OVER_ERR)	/* overrun */
	MAP_FLAG(UMP_UART_LSR_PE_MASK, LSR_PAR_ERR)	/* parity error */
	MAP_FLAG(UMP_UART_LSR_FE_MASK, LSR_FRM_ERR)	/* framing error */
	MAP_FLAG(UMP_UART_LSR_BR_MASK, LSR_BREAK)	/* अवरोध detected */
	MAP_FLAG(UMP_UART_LSR_RX_MASK, LSR_RX_AVAIL)	/* rx data available */
	MAP_FLAG(UMP_UART_LSR_TX_MASK, LSR_TX_EMPTY)	/* tx hold reg empty */

#अघोषित MAP_FLAG

	वापस lsr;
पूर्ण

अटल व्योम handle_new_msr(काष्ठा edgeport_port *edge_port, u8 msr)
अणु
	काष्ठा async_icount *icount;
	काष्ठा tty_काष्ठा *tty;

	dev_dbg(&edge_port->port->dev, "%s - %02x\n", __func__, msr);

	अगर (msr & (EDGEPORT_MSR_DELTA_CTS | EDGEPORT_MSR_DELTA_DSR |
			EDGEPORT_MSR_DELTA_RI | EDGEPORT_MSR_DELTA_CD)) अणु
		icount = &edge_port->port->icount;

		/* update input line counters */
		अगर (msr & EDGEPORT_MSR_DELTA_CTS)
			icount->cts++;
		अगर (msr & EDGEPORT_MSR_DELTA_DSR)
			icount->dsr++;
		अगर (msr & EDGEPORT_MSR_DELTA_CD)
			icount->dcd++;
		अगर (msr & EDGEPORT_MSR_DELTA_RI)
			icount->rng++;
		wake_up_पूर्णांकerruptible(&edge_port->port->port.delta_msr_रुको);
	पूर्ण

	/* Save the new modem status */
	edge_port->shaकरोw_msr = msr & 0xf0;

	tty = tty_port_tty_get(&edge_port->port->port);
	/* handle CTS flow control */
	अगर (tty && C_CRTSCTS(tty)) अणु
		अगर (msr & EDGEPORT_MSR_CTS)
			tty_wakeup(tty);
	पूर्ण
	tty_kref_put(tty);
पूर्ण

अटल व्योम handle_new_lsr(काष्ठा edgeport_port *edge_port, पूर्णांक lsr_data,
							u8 lsr, u8 data)
अणु
	काष्ठा async_icount *icount;
	u8 new_lsr = (u8)(lsr & (u8)(LSR_OVER_ERR | LSR_PAR_ERR |
						LSR_FRM_ERR | LSR_BREAK));

	dev_dbg(&edge_port->port->dev, "%s - %02x\n", __func__, new_lsr);

	edge_port->shaकरोw_lsr = lsr;

	अगर (new_lsr & LSR_BREAK)
		/*
		 * Parity and Framing errors only count अगर they
		 * occur exclusive of a अवरोध being received.
		 */
		new_lsr &= (u8)(LSR_OVER_ERR | LSR_BREAK);

	/* Place LSR data byte पूर्णांकo Rx buffer */
	अगर (lsr_data)
		edge_tty_recv(edge_port->port, &data, 1);

	/* update input line counters */
	icount = &edge_port->port->icount;
	अगर (new_lsr & LSR_BREAK)
		icount->brk++;
	अगर (new_lsr & LSR_OVER_ERR)
		icount->overrun++;
	अगर (new_lsr & LSR_PAR_ERR)
		icount->parity++;
	अगर (new_lsr & LSR_FRM_ERR)
		icount->frame++;
पूर्ण

अटल व्योम edge_पूर्णांकerrupt_callback(काष्ठा urb *urb)
अणु
	काष्ठा edgeport_serial *edge_serial = urb->context;
	काष्ठा usb_serial_port *port;
	काष्ठा edgeport_port *edge_port;
	काष्ठा device *dev;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक length = urb->actual_length;
	पूर्णांक port_number;
	पूर्णांक function;
	पूर्णांक retval;
	u8 lsr;
	u8 msr;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s - urb shutting down with status: %d\n",
		    __func__, status);
		वापस;
	शेष:
		dev_err(&urb->dev->dev, "%s - nonzero urb status received: "
			"%d\n", __func__, status);
		जाओ निकास;
	पूर्ण

	अगर (!length) अणु
		dev_dbg(&urb->dev->dev, "%s - no data in urb\n", __func__);
		जाओ निकास;
	पूर्ण

	dev = &edge_serial->serial->dev->dev;
	usb_serial_debug_data(dev, __func__, length, data);

	अगर (length != 2) अणु
		dev_dbg(dev, "%s - expecting packet of size 2, got %d\n", __func__, length);
		जाओ निकास;
	पूर्ण

	port_number = TIUMP_GET_PORT_FROM_CODE(data[0]);
	function    = TIUMP_GET_FUNC_FROM_CODE(data[0]);
	dev_dbg(dev, "%s - port_number %d, function %d, info 0x%x\n", __func__,
		port_number, function, data[1]);

	अगर (port_number >= edge_serial->serial->num_ports) अणु
		dev_err(dev, "bad port number %d\n", port_number);
		जाओ निकास;
	पूर्ण

	port = edge_serial->serial->port[port_number];
	edge_port = usb_get_serial_port_data(port);
	अगर (!edge_port) अणु
		dev_dbg(dev, "%s - edge_port not found\n", __func__);
		वापस;
	पूर्ण
	चयन (function) अणु
	हाल TIUMP_INTERRUPT_CODE_LSR:
		lsr = map_line_status(data[1]);
		अगर (lsr & UMP_UART_LSR_DATA_MASK) अणु
			/*
			 * Save the LSR event क्रम bulk पढ़ो completion routine
			 */
			dev_dbg(dev, "%s - LSR Event Port %u LSR Status = %02x\n",
				__func__, port_number, lsr);
			edge_port->lsr_event = 1;
			edge_port->lsr_mask = lsr;
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "%s - ===== Port %d LSR Status = %02x ======\n",
				__func__, port_number, lsr);
			handle_new_lsr(edge_port, 0, lsr, 0);
		पूर्ण
		अवरोध;

	हाल TIUMP_INTERRUPT_CODE_MSR:	/* MSR */
		/* Copy MSR from UMP */
		msr = data[1];
		dev_dbg(dev, "%s - ===== Port %u MSR Status = %02x ======\n",
			__func__, port_number, msr);
		handle_new_msr(edge_port, msr);
		अवरोध;

	शेष:
		dev_err(&urb->dev->dev,
			"%s - Unknown Interrupt code from UMP %x\n",
			__func__, data[1]);
		अवरोध;

	पूर्ण

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&urb->dev->dev,
			"%s - usb_submit_urb failed with result %d\n",
			 __func__, retval);
पूर्ण

अटल व्योम edge_bulk_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा edgeport_port *edge_port = urb->context;
	काष्ठा device *dev = &edge_port->port->dev;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;
	पूर्णांक port_number;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s - urb shutting down with status: %d\n", __func__, status);
		वापस;
	शेष:
		dev_err(&urb->dev->dev, "%s - nonzero read bulk status received: %d\n", __func__, status);
	पूर्ण

	अगर (status == -EPIPE)
		जाओ निकास;

	अगर (status) अणु
		dev_err(&urb->dev->dev, "%s - stopping read!\n", __func__);
		वापस;
	पूर्ण

	port_number = edge_port->port->port_number;

	अगर (urb->actual_length > 0 && edge_port->lsr_event) अणु
		edge_port->lsr_event = 0;
		dev_dbg(dev, "%s ===== Port %u LSR Status = %02x, Data = %02x ======\n",
			__func__, port_number, edge_port->lsr_mask, *data);
		handle_new_lsr(edge_port, 1, edge_port->lsr_mask, *data);
		/* Adjust buffer length/poपूर्णांकer */
		--urb->actual_length;
		++data;
	पूर्ण

	अगर (urb->actual_length) अणु
		usb_serial_debug_data(dev, __func__, urb->actual_length, data);
		अगर (edge_port->बंद_pending)
			dev_dbg(dev, "%s - close pending, dropping data on the floor\n",
								__func__);
		अन्यथा
			edge_tty_recv(edge_port->port, data,
					urb->actual_length);
		edge_port->port->icount.rx += urb->actual_length;
	पूर्ण

निकास:
	/* जारी पढ़ो unless stopped */
	spin_lock_irqsave(&edge_port->ep_lock, flags);
	अगर (edge_port->ep_पढ़ो_urb_state == EDGE_READ_URB_RUNNING)
		retval = usb_submit_urb(urb, GFP_ATOMIC);
	अन्यथा अगर (edge_port->ep_पढ़ो_urb_state == EDGE_READ_URB_STOPPING)
		edge_port->ep_पढ़ो_urb_state = EDGE_READ_URB_STOPPED;

	spin_unlock_irqrestore(&edge_port->ep_lock, flags);
	अगर (retval)
		dev_err(dev, "%s - usb_submit_urb failed with result %d\n", __func__, retval);
पूर्ण

अटल व्योम edge_tty_recv(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *data,
		पूर्णांक length)
अणु
	पूर्णांक queued;

	queued = tty_insert_flip_string(&port->port, data, length);
	अगर (queued < length)
		dev_err(&port->dev, "%s - dropping data, %d bytes lost\n",
			__func__, length - queued);
	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम edge_bulk_out_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक status = urb->status;
	काष्ठा tty_काष्ठा *tty;

	edge_port->ep_ग_लिखो_urb_in_use = 0;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s - urb shutting down with status: %d\n",
		    __func__, status);
		वापस;
	शेष:
		dev_err_console(port, "%s - nonzero write bulk status "
			"received: %d\n", __func__, status);
	पूर्ण

	/* send any buffered data */
	tty = tty_port_tty_get(&port->port);
	edge_send(port, tty);
	tty_kref_put(tty);
पूर्ण

अटल पूर्णांक edge_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	काष्ठा edgeport_serial *edge_serial;
	काष्ठा usb_device *dev;
	काष्ठा urb *urb;
	पूर्णांक status;
	u16 खोलो_settings;
	u8 transaction_समयout;

	अगर (edge_port == शून्य)
		वापस -ENODEV;

	dev = port->serial->dev;

	/* turn off loopback */
	status = ti_करो_config(edge_port, UMPC_SET_CLR_LOOPBACK, 0);
	अगर (status) अणु
		dev_err(&port->dev,
				"%s - cannot send clear loopback command, %d\n",
			__func__, status);
		वापस status;
	पूर्ण

	/* set up the port settings */
	अगर (tty)
		edge_set_termios(tty, port, &tty->termios);

	/* खोलो up the port */

	/* milliseconds to समयout क्रम DMA transfer */
	transaction_समयout = 2;

	edge_port->ump_पढ़ो_समयout =
				max(20, ((transaction_समयout * 3) / 2));

	/* milliseconds to समयout क्रम DMA transfer */
	खोलो_settings = (u8)(UMP_DMA_MODE_CONTINOUS |
			     UMP_PIPE_TRANS_TIMEOUT_ENA |
			     (transaction_समयout << 2));

	dev_dbg(&port->dev, "%s - Sending UMPC_OPEN_PORT\n", __func__);

	/* Tell TI to खोलो and start the port */
	status = send_port_cmd(port, UMPC_OPEN_PORT, खोलो_settings, शून्य, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot send open command, %d\n",
							__func__, status);
		वापस status;
	पूर्ण

	/* Start the DMA? */
	status = send_port_cmd(port, UMPC_START_PORT, 0, शून्य, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot send start DMA command, %d\n",
							__func__, status);
		वापस status;
	पूर्ण

	/* Clear TX and RX buffers in UMP */
	status = purge_port(port, UMP_PORT_सूची_OUT | UMP_PORT_सूची_IN);
	अगर (status) अणु
		dev_err(&port->dev,
			"%s - cannot send clear buffers command, %d\n",
			__func__, status);
		वापस status;
	पूर्ण

	/* Read Initial MSR */
	status = पढ़ो_port_cmd(port, UMPC_READ_MSR, 0, &edge_port->shaकरोw_msr, 1);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot send read MSR command, %d\n",
							__func__, status);
		वापस status;
	पूर्ण

	dev_dbg(&port->dev, "ShadowMSR 0x%X\n", edge_port->shaकरोw_msr);

	/* Set Initial MCR */
	edge_port->shaकरोw_mcr = MCR_RTS | MCR_DTR;
	dev_dbg(&port->dev, "ShadowMCR 0x%X\n", edge_port->shaकरोw_mcr);

	edge_serial = edge_port->edge_serial;
	अगर (mutex_lock_पूर्णांकerruptible(&edge_serial->es_lock))
		वापस -ERESTARTSYS;
	अगर (edge_serial->num_ports_खोलो == 0) अणु
		/* we are the first port to खोलो, post the पूर्णांकerrupt urb */
		urb = edge_serial->serial->port[0]->पूर्णांकerrupt_in_urb;
		urb->context = edge_serial;
		status = usb_submit_urb(urb, GFP_KERNEL);
		अगर (status) अणु
			dev_err(&port->dev,
				"%s - usb_submit_urb failed with value %d\n",
					__func__, status);
			जाओ release_es_lock;
		पूर्ण
	पूर्ण

	/*
	 * reset the data toggle on the bulk endpoपूर्णांकs to work around bug in
	 * host controllers where things get out of sync some बार
	 */
	usb_clear_halt(dev, port->ग_लिखो_urb->pipe);
	usb_clear_halt(dev, port->पढ़ो_urb->pipe);

	/* start up our bulk पढ़ो urb */
	urb = port->पढ़ो_urb;
	edge_port->ep_पढ़ो_urb_state = EDGE_READ_URB_RUNNING;
	urb->context = edge_port;
	status = usb_submit_urb(urb, GFP_KERNEL);
	अगर (status) अणु
		dev_err(&port->dev,
			"%s - read bulk usb_submit_urb failed with value %d\n",
				__func__, status);
		जाओ unlink_पूर्णांक_urb;
	पूर्ण

	++edge_serial->num_ports_खोलो;

	जाओ release_es_lock;

unlink_पूर्णांक_urb:
	अगर (edge_port->edge_serial->num_ports_खोलो == 0)
		usb_समाप्त_urb(port->serial->port[0]->पूर्णांकerrupt_in_urb);
release_es_lock:
	mutex_unlock(&edge_serial->es_lock);
	वापस status;
पूर्ण

अटल व्योम edge_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_serial *edge_serial;
	काष्ठा edgeport_port *edge_port;
	अचिन्हित दीर्घ flags;

	edge_serial = usb_get_serial_data(port->serial);
	edge_port = usb_get_serial_port_data(port);
	अगर (edge_serial == शून्य || edge_port == शून्य)
		वापस;

	/*
	 * The bulkपढ़ोcompletion routine will check
	 * this flag and dump add पढ़ो data
	 */
	edge_port->बंद_pending = 1;

	usb_समाप्त_urb(port->पढ़ो_urb);
	usb_समाप्त_urb(port->ग_लिखो_urb);
	edge_port->ep_ग_लिखो_urb_in_use = 0;
	spin_lock_irqsave(&edge_port->ep_lock, flags);
	kfअगरo_reset_out(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	dev_dbg(&port->dev, "%s - send umpc_close_port\n", __func__);
	send_port_cmd(port, UMPC_CLOSE_PORT, 0, शून्य, 0);

	mutex_lock(&edge_serial->es_lock);
	--edge_port->edge_serial->num_ports_खोलो;
	अगर (edge_port->edge_serial->num_ports_खोलो <= 0) अणु
		/* last port is now बंदd, let's shut करोwn our पूर्णांकerrupt urb */
		usb_समाप्त_urb(port->serial->port[0]->पूर्णांकerrupt_in_urb);
		edge_port->edge_serial->num_ports_खोलो = 0;
	पूर्ण
	mutex_unlock(&edge_serial->es_lock);
	edge_port->बंद_pending = 0;
पूर्ण

अटल पूर्णांक edge_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
				स्थिर अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);

	अगर (count == 0) अणु
		dev_dbg(&port->dev, "%s - write request of 0 bytes\n", __func__);
		वापस 0;
	पूर्ण

	अगर (edge_port == शून्य)
		वापस -ENODEV;
	अगर (edge_port->बंद_pending == 1)
		वापस -ENODEV;

	count = kfअगरo_in_locked(&port->ग_लिखो_fअगरo, data, count,
							&edge_port->ep_lock);
	edge_send(port, tty);

	वापस count;
पूर्ण

अटल व्योम edge_send(काष्ठा usb_serial_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक count, result;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);

	अगर (edge_port->ep_ग_लिखो_urb_in_use) अणु
		spin_unlock_irqrestore(&edge_port->ep_lock, flags);
		वापस;
	पूर्ण

	count = kfअगरo_out(&port->ग_लिखो_fअगरo,
				port->ग_लिखो_urb->transfer_buffer,
				port->bulk_out_size);

	अगर (count == 0) अणु
		spin_unlock_irqrestore(&edge_port->ep_lock, flags);
		वापस;
	पूर्ण

	edge_port->ep_ग_लिखो_urb_in_use = 1;

	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	usb_serial_debug_data(&port->dev, __func__, count, port->ग_लिखो_urb->transfer_buffer);

	/* set up our urb */
	port->ग_लिखो_urb->transfer_buffer_length = count;

	/* send the data out the bulk port */
	result = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
	अगर (result) अणु
		dev_err_console(port,
			"%s - failed submitting write urb, error %d\n",
				__func__, result);
		edge_port->ep_ग_लिखो_urb_in_use = 0;
		/* TODO: reschedule edge_send */
	पूर्ण अन्यथा
		edge_port->port->icount.tx += count;

	/*
	 * wakeup any process रुकोing क्रम ग_लिखोs to complete
	 * there is now more room in the buffer क्रम new ग_लिखोs
	 */
	अगर (tty)
		tty_wakeup(tty);
पूर्ण

अटल पूर्णांक edge_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक room = 0;
	अचिन्हित दीर्घ flags;

	अगर (edge_port == शून्य)
		वापस 0;
	अगर (edge_port->बंद_pending == 1)
		वापस 0;

	spin_lock_irqsave(&edge_port->ep_lock, flags);
	room = kfअगरo_avail(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, room);
	वापस room;
पूर्ण

अटल पूर्णांक edge_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक अक्षरs = 0;
	अचिन्हित दीर्घ flags;
	अगर (edge_port == शून्य)
		वापस 0;

	spin_lock_irqsave(&edge_port->ep_lock, flags);
	अक्षरs = kfअगरo_len(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, अक्षरs);
	वापस अक्षरs;
पूर्ण

अटल bool edge_tx_empty(काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक ret;

	ret = tx_active(edge_port);
	अगर (ret > 0)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम edge_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक status;

	अगर (edge_port == शून्य)
		वापस;

	/* अगर we are implementing XON/XOFF, send the stop अक्षरacter */
	अगर (I_IXOFF(tty)) अणु
		अचिन्हित अक्षर stop_अक्षर = STOP_CHAR(tty);
		status = edge_ग_लिखो(tty, port, &stop_अक्षर, 1);
		अगर (status <= 0) अणु
			dev_err(&port->dev, "%s - failed to write stop character, %d\n", __func__, status);
		पूर्ण
	पूर्ण

	/*
	 * अगर we are implementing RTS/CTS, stop पढ़ोs
	 * and the Edgeport will clear the RTS line
	 */
	अगर (C_CRTSCTS(tty))
		stop_पढ़ो(edge_port);

पूर्ण

अटल व्योम edge_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक status;

	अगर (edge_port == शून्य)
		वापस;

	/* अगर we are implementing XON/XOFF, send the start अक्षरacter */
	अगर (I_IXOFF(tty)) अणु
		अचिन्हित अक्षर start_अक्षर = START_CHAR(tty);
		status = edge_ग_लिखो(tty, port, &start_अक्षर, 1);
		अगर (status <= 0) अणु
			dev_err(&port->dev, "%s - failed to write start character, %d\n", __func__, status);
		पूर्ण
	पूर्ण
	/*
	 * अगर we are implementing RTS/CTS, restart पढ़ोs
	 * are the Edgeport will निश्चित the RTS line
	 */
	अगर (C_CRTSCTS(tty)) अणु
		status = restart_पढ़ो(edge_port);
		अगर (status)
			dev_err(&port->dev,
				"%s - read bulk usb_submit_urb failed: %d\n",
							__func__, status);
	पूर्ण

पूर्ण

अटल व्योम stop_पढ़ो(काष्ठा edgeport_port *edge_port)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);

	अगर (edge_port->ep_पढ़ो_urb_state == EDGE_READ_URB_RUNNING)
		edge_port->ep_पढ़ो_urb_state = EDGE_READ_URB_STOPPING;
	edge_port->shaकरोw_mcr &= ~MCR_RTS;

	spin_unlock_irqrestore(&edge_port->ep_lock, flags);
पूर्ण

अटल पूर्णांक restart_पढ़ो(काष्ठा edgeport_port *edge_port)
अणु
	काष्ठा urb *urb;
	पूर्णांक status = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);

	अगर (edge_port->ep_पढ़ो_urb_state == EDGE_READ_URB_STOPPED) अणु
		urb = edge_port->port->पढ़ो_urb;
		status = usb_submit_urb(urb, GFP_ATOMIC);
	पूर्ण
	edge_port->ep_पढ़ो_urb_state = EDGE_READ_URB_RUNNING;
	edge_port->shaकरोw_mcr |= MCR_RTS;

	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	वापस status;
पूर्ण

अटल व्योम change_port_settings(काष्ठा tty_काष्ठा *tty,
		काष्ठा edgeport_port *edge_port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा device *dev = &edge_port->port->dev;
	काष्ठा ump_uart_config *config;
	पूर्णांक baud;
	अचिन्हित cflag;
	पूर्णांक status;

	config = kदो_स्मृति (माप (*config), GFP_KERNEL);
	अगर (!config) अणु
		tty->termios = *old_termios;
		वापस;
	पूर्ण

	cflag = tty->termios.c_cflag;

	config->wFlags = 0;

	/* These flags must be set */
	config->wFlags |= UMP_MASK_UART_FLAGS_RECEIVE_MS_INT;
	config->wFlags |= UMP_MASK_UART_FLAGS_AUTO_START_ON_ERR;
	config->bUartMode = (u8)(edge_port->bUartMode);

	चयन (cflag & CSIZE) अणु
	हाल CS5:
		    config->bDataBits = UMP_UART_CHAR5BITS;
		    dev_dbg(dev, "%s - data bits = 5\n", __func__);
		    अवरोध;
	हाल CS6:
		    config->bDataBits = UMP_UART_CHAR6BITS;
		    dev_dbg(dev, "%s - data bits = 6\n", __func__);
		    अवरोध;
	हाल CS7:
		    config->bDataBits = UMP_UART_CHAR7BITS;
		    dev_dbg(dev, "%s - data bits = 7\n", __func__);
		    अवरोध;
	शेष:
	हाल CS8:
		    config->bDataBits = UMP_UART_CHAR8BITS;
		    dev_dbg(dev, "%s - data bits = 8\n", __func__);
			    अवरोध;
	पूर्ण

	अगर (cflag & PARENB) अणु
		अगर (cflag & PARODD) अणु
			config->wFlags |= UMP_MASK_UART_FLAGS_PARITY;
			config->bParity = UMP_UART_ODDPARITY;
			dev_dbg(dev, "%s - parity = odd\n", __func__);
		पूर्ण अन्यथा अणु
			config->wFlags |= UMP_MASK_UART_FLAGS_PARITY;
			config->bParity = UMP_UART_EVENPARITY;
			dev_dbg(dev, "%s - parity = even\n", __func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		config->bParity = UMP_UART_NOPARITY;
		dev_dbg(dev, "%s - parity = none\n", __func__);
	पूर्ण

	अगर (cflag & CSTOPB) अणु
		config->bStopBits = UMP_UART_STOPBIT2;
		dev_dbg(dev, "%s - stop bits = 2\n", __func__);
	पूर्ण अन्यथा अणु
		config->bStopBits = UMP_UART_STOPBIT1;
		dev_dbg(dev, "%s - stop bits = 1\n", __func__);
	पूर्ण

	/* figure out the flow control settings */
	अगर (cflag & CRTSCTS) अणु
		config->wFlags |= UMP_MASK_UART_FLAGS_OUT_X_CTS_FLOW;
		config->wFlags |= UMP_MASK_UART_FLAGS_RTS_FLOW;
		dev_dbg(dev, "%s - RTS/CTS is enabled\n", __func__);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s - RTS/CTS is disabled\n", __func__);
		restart_पढ़ो(edge_port);
	पूर्ण

	/*
	 * अगर we are implementing XON/XOFF, set the start and stop
	 * अक्षरacter in the device
	 */
	config->cXon  = START_CHAR(tty);
	config->cXoff = STOP_CHAR(tty);

	/* अगर we are implementing INBOUND XON/XOFF */
	अगर (I_IXOFF(tty)) अणु
		config->wFlags |= UMP_MASK_UART_FLAGS_IN_X;
		dev_dbg(dev, "%s - INBOUND XON/XOFF is enabled, XON = %2x, XOFF = %2x\n",
			__func__, config->cXon, config->cXoff);
	पूर्ण अन्यथा
		dev_dbg(dev, "%s - INBOUND XON/XOFF is disabled\n", __func__);

	/* अगर we are implementing OUTBOUND XON/XOFF */
	अगर (I_IXON(tty)) अणु
		config->wFlags |= UMP_MASK_UART_FLAGS_OUT_X;
		dev_dbg(dev, "%s - OUTBOUND XON/XOFF is enabled, XON = %2x, XOFF = %2x\n",
			__func__, config->cXon, config->cXoff);
	पूर्ण अन्यथा
		dev_dbg(dev, "%s - OUTBOUND XON/XOFF is disabled\n", __func__);

	tty->termios.c_cflag &= ~CMSPAR;

	/* Round the baud rate */
	baud = tty_get_baud_rate(tty);
	अगर (!baud) अणु
		/* pick a शेष, any शेष... */
		baud = 9600;
	पूर्ण अन्यथा अणु
		/* Aव्योम a zero भागisor. */
		baud = min(baud, 461550);
		tty_encode_baud_rate(tty, baud, baud);
	पूर्ण

	edge_port->baud_rate = baud;
	config->wBaudRate = (u16)((461550L + baud/2) / baud);

	/* FIXME: Recompute actual baud from भागisor here */

	dev_dbg(dev, "%s - baud rate = %d, wBaudRate = %d\n", __func__, baud, config->wBaudRate);

	dev_dbg(dev, "wBaudRate:   %d\n", (पूर्णांक)(461550L / config->wBaudRate));
	dev_dbg(dev, "wFlags:    0x%x\n", config->wFlags);
	dev_dbg(dev, "bDataBits:   %d\n", config->bDataBits);
	dev_dbg(dev, "bParity:     %d\n", config->bParity);
	dev_dbg(dev, "bStopBits:   %d\n", config->bStopBits);
	dev_dbg(dev, "cXon:        %d\n", config->cXon);
	dev_dbg(dev, "cXoff:       %d\n", config->cXoff);
	dev_dbg(dev, "bUartMode:   %d\n", config->bUartMode);

	/* move the word values पूर्णांकo big endian mode */
	cpu_to_be16s(&config->wFlags);
	cpu_to_be16s(&config->wBaudRate);

	status = send_port_cmd(edge_port->port, UMPC_SET_CONFIG, 0, config,
			माप(*config));
	अगर (status)
		dev_dbg(dev, "%s - error %d when trying to write config to device\n",
			__func__, status);
	kमुक्त(config);
पूर्ण

अटल व्योम edge_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);

	अगर (edge_port == शून्य)
		वापस;
	/* change the port settings to the new ones specअगरied */
	change_port_settings(tty, edge_port, old_termios);
पूर्ण

अटल पूर्णांक edge_tiocmset(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक mcr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);
	mcr = edge_port->shaकरोw_mcr;
	अगर (set & TIOCM_RTS)
		mcr |= MCR_RTS;
	अगर (set & TIOCM_DTR)
		mcr |= MCR_DTR;
	अगर (set & TIOCM_LOOP)
		mcr |= MCR_LOOPBACK;

	अगर (clear & TIOCM_RTS)
		mcr &= ~MCR_RTS;
	अगर (clear & TIOCM_DTR)
		mcr &= ~MCR_DTR;
	अगर (clear & TIOCM_LOOP)
		mcr &= ~MCR_LOOPBACK;

	edge_port->shaकरोw_mcr = mcr;
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	restore_mcr(edge_port, mcr);
	वापस 0;
पूर्ण

अटल पूर्णांक edge_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित पूर्णांक msr;
	अचिन्हित पूर्णांक mcr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);

	msr = edge_port->shaकरोw_msr;
	mcr = edge_port->shaकरोw_mcr;
	result = ((mcr & MCR_DTR)	? TIOCM_DTR: 0)	  /* 0x002 */
		  | ((mcr & MCR_RTS)	? TIOCM_RTS: 0)   /* 0x004 */
		  | ((msr & EDGEPORT_MSR_CTS)	? TIOCM_CTS: 0)   /* 0x020 */
		  | ((msr & EDGEPORT_MSR_CD)	? TIOCM_CAR: 0)   /* 0x040 */
		  | ((msr & EDGEPORT_MSR_RI)	? TIOCM_RI:  0)   /* 0x080 */
		  | ((msr & EDGEPORT_MSR_DSR)	? TIOCM_DSR: 0);  /* 0x100 */


	dev_dbg(&port->dev, "%s -- %x\n", __func__, result);
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	वापस result;
पूर्ण

अटल व्योम edge_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक status;
	पूर्णांक bv = 0;	/* Off */

	अगर (अवरोध_state == -1)
		bv = 1;	/* On */
	status = ti_करो_config(edge_port, UMPC_SET_CLR_BREAK, bv);
	अगर (status)
		dev_dbg(&port->dev, "%s - error %d sending break set/clear command.\n",
			__func__, status);
पूर्ण

अटल व्योम edge_heartbeat_schedule(काष्ठा edgeport_serial *edge_serial)
अणु
	अगर (!edge_serial->use_heartbeat)
		वापस;

	schedule_delayed_work(&edge_serial->heartbeat_work,
			FW_HEARTBEAT_SECS * HZ);
पूर्ण

अटल व्योम edge_heartbeat_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा edgeport_serial *serial;
	काष्ठा ti_i2c_desc *rom_desc;

	serial = container_of(work, काष्ठा edgeport_serial,
			heartbeat_work.work);

	rom_desc = kदो_स्मृति(माप(*rom_desc), GFP_KERNEL);

	/* Descriptor address request is enough to reset the firmware समयr */
	अगर (!rom_desc || !get_descriptor_addr(serial, I2C_DESC_TYPE_ION,
			rom_desc)) अणु
		dev_err(&serial->serial->पूर्णांकerface->dev,
				"%s - Incomplete heartbeat\n", __func__);
	पूर्ण
	kमुक्त(rom_desc);

	edge_heartbeat_schedule(serial);
पूर्ण

अटल पूर्णांक edge_calc_num_ports(काष्ठा usb_serial *serial,
				काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	अचिन्हित अक्षर num_ports = serial->type->num_ports;

	/* Make sure we have the required endpoपूर्णांकs when in करोwnload mode. */
	अगर (serial->पूर्णांकerface->cur_altsetting->desc.bNumEndpoपूर्णांकs > 1) अणु
		अगर (epds->num_bulk_in < num_ports ||
				epds->num_bulk_out < num_ports ||
				epds->num_पूर्णांकerrupt_in < 1) अणु
			dev_err(dev, "required endpoints missing\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस num_ports;
पूर्ण

अटल पूर्णांक edge_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा edgeport_serial *edge_serial;
	पूर्णांक status;
	u16 product_id;

	/* create our निजी serial काष्ठाure */
	edge_serial = kzalloc(माप(काष्ठा edgeport_serial), GFP_KERNEL);
	अगर (!edge_serial)
		वापस -ENOMEM;

	mutex_init(&edge_serial->es_lock);
	edge_serial->serial = serial;
	INIT_DELAYED_WORK(&edge_serial->heartbeat_work, edge_heartbeat_work);
	usb_set_serial_data(serial, edge_serial);

	status = करोwnload_fw(edge_serial);
	अगर (status < 0) अणु
		kमुक्त(edge_serial);
		वापस status;
	पूर्ण

	अगर (status > 0)
		वापस 1;	/* bind but करो not रेजिस्टर any ports */

	product_id = le16_to_cpu(
			edge_serial->serial->dev->descriptor.idProduct);

	/* Currently only the EP/416 models require heartbeat support */
	अगर (edge_serial->fw_version > FW_HEARTBEAT_VERSION_CUTOFF) अणु
		अगर (product_id == ION_DEVICE_ID_TI_EDGEPORT_416 ||
			product_id == ION_DEVICE_ID_TI_EDGEPORT_416B) अणु
			edge_serial->use_heartbeat = true;
		पूर्ण
	पूर्ण

	edge_heartbeat_schedule(edge_serial);

	वापस 0;
पूर्ण

अटल व्योम edge_disconnect(काष्ठा usb_serial *serial)
अणु
	काष्ठा edgeport_serial *edge_serial = usb_get_serial_data(serial);

	cancel_delayed_work_sync(&edge_serial->heartbeat_work);
पूर्ण

अटल व्योम edge_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा edgeport_serial *edge_serial = usb_get_serial_data(serial);

	cancel_delayed_work_sync(&edge_serial->heartbeat_work);
	kमुक्त(edge_serial);
पूर्ण

अटल पूर्णांक edge_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_port *edge_port;
	पूर्णांक ret;

	edge_port = kzalloc(माप(*edge_port), GFP_KERNEL);
	अगर (!edge_port)
		वापस -ENOMEM;

	spin_lock_init(&edge_port->ep_lock);
	edge_port->port = port;
	edge_port->edge_serial = usb_get_serial_data(port->serial);
	edge_port->bUartMode = शेष_uart_mode;

	चयन (port->port_number) अणु
	हाल 0:
		edge_port->uart_base = UMPMEM_BASE_UART1;
		edge_port->dma_address = UMPD_OEDB1_ADDRESS;
		अवरोध;
	हाल 1:
		edge_port->uart_base = UMPMEM_BASE_UART2;
		edge_port->dma_address = UMPD_OEDB2_ADDRESS;
		अवरोध;
	शेष:
		dev_err(&port->dev, "unknown port number\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	dev_dbg(&port->dev,
		"%s - port_number = %d, uart_base = %04x, dma_address = %04x\n",
		__func__, port->port_number, edge_port->uart_base,
		edge_port->dma_address);

	usb_set_serial_port_data(port, edge_port);

	ret = edge_create_sysfs_attrs(port);
	अगर (ret)
		जाओ err;

	/*
	 * The LSR करोes not tell when the transmitter shअगरt रेजिस्टर has
	 * emptied so add a one-अक्षरacter drain delay.
	 */
	port->port.drain_delay = 1;

	वापस 0;
err:
	kमुक्त(edge_port);

	वापस ret;
पूर्ण

अटल व्योम edge_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_port *edge_port;

	edge_port = usb_get_serial_port_data(port);
	edge_हटाओ_sysfs_attrs(port);
	kमुक्त(edge_port);
पूर्ण

/* Sysfs Attributes */

अटल sमाप_प्रकार uart_mode_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_serial_port *port = to_usb_serial_port(dev);
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);

	वापस प्र_लिखो(buf, "%d\n", edge_port->bUartMode);
पूर्ण

अटल sमाप_प्रकार uart_mode_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *valbuf, माप_प्रकार count)
अणु
	काष्ठा usb_serial_port *port = to_usb_serial_port(dev);
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक v = simple_म_से_अदीर्घ(valbuf, शून्य, 0);

	dev_dbg(dev, "%s: setting uart_mode = %d\n", __func__, v);

	अगर (v < 256)
		edge_port->bUartMode = v;
	अन्यथा
		dev_err(dev, "%s - uart_mode %d is invalid\n", __func__, v);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(uart_mode);

अटल पूर्णांक edge_create_sysfs_attrs(काष्ठा usb_serial_port *port)
अणु
	वापस device_create_file(&port->dev, &dev_attr_uart_mode);
पूर्ण

अटल पूर्णांक edge_हटाओ_sysfs_attrs(काष्ठा usb_serial_port *port)
अणु
	device_हटाओ_file(&port->dev, &dev_attr_uart_mode);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक edge_suspend(काष्ठा usb_serial *serial, pm_message_t message)
अणु
	काष्ठा edgeport_serial *edge_serial = usb_get_serial_data(serial);

	cancel_delayed_work_sync(&edge_serial->heartbeat_work);

	वापस 0;
पूर्ण

अटल पूर्णांक edge_resume(काष्ठा usb_serial *serial)
अणु
	काष्ठा edgeport_serial *edge_serial = usb_get_serial_data(serial);

	edge_heartbeat_schedule(edge_serial);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा usb_serial_driver edgeport_1port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "edgeport_ti_1",
	पूर्ण,
	.description		= "Edgeport TI 1 port adapter",
	.id_table		= edgeport_1port_id_table,
	.num_ports		= 1,
	.num_bulk_out		= 1,
	.खोलो			= edge_खोलो,
	.बंद			= edge_बंद,
	.throttle		= edge_throttle,
	.unthrottle		= edge_unthrottle,
	.attach			= edge_startup,
	.calc_num_ports		= edge_calc_num_ports,
	.disconnect		= edge_disconnect,
	.release		= edge_release,
	.port_probe		= edge_port_probe,
	.port_हटाओ		= edge_port_हटाओ,
	.set_termios		= edge_set_termios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.ग_लिखो			= edge_ग_लिखो,
	.ग_लिखो_room		= edge_ग_लिखो_room,
	.अक्षरs_in_buffer	= edge_अक्षरs_in_buffer,
	.tx_empty		= edge_tx_empty,
	.अवरोध_ctl		= edge_अवरोध,
	.पढ़ो_पूर्णांक_callback	= edge_पूर्णांकerrupt_callback,
	.पढ़ो_bulk_callback	= edge_bulk_in_callback,
	.ग_लिखो_bulk_callback	= edge_bulk_out_callback,
#अगर_घोषित CONFIG_PM
	.suspend		= edge_suspend,
	.resume			= edge_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा usb_serial_driver edgeport_2port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "edgeport_ti_2",
	पूर्ण,
	.description		= "Edgeport TI 2 port adapter",
	.id_table		= edgeport_2port_id_table,
	.num_ports		= 2,
	.num_bulk_out		= 1,
	.खोलो			= edge_खोलो,
	.बंद			= edge_बंद,
	.throttle		= edge_throttle,
	.unthrottle		= edge_unthrottle,
	.attach			= edge_startup,
	.calc_num_ports		= edge_calc_num_ports,
	.disconnect		= edge_disconnect,
	.release		= edge_release,
	.port_probe		= edge_port_probe,
	.port_हटाओ		= edge_port_हटाओ,
	.set_termios		= edge_set_termios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.ग_लिखो			= edge_ग_लिखो,
	.ग_लिखो_room		= edge_ग_लिखो_room,
	.अक्षरs_in_buffer	= edge_अक्षरs_in_buffer,
	.tx_empty		= edge_tx_empty,
	.अवरोध_ctl		= edge_अवरोध,
	.पढ़ो_पूर्णांक_callback	= edge_पूर्णांकerrupt_callback,
	.पढ़ो_bulk_callback	= edge_bulk_in_callback,
	.ग_लिखो_bulk_callback	= edge_bulk_out_callback,
#अगर_घोषित CONFIG_PM
	.suspend		= edge_suspend,
	.resume			= edge_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&edgeport_1port_device, &edgeport_2port_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table_combined);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("edgeport/down3.bin");

module_param(ignore_cpu_rev, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ignore_cpu_rev,
			"Ignore the cpu revision when connecting to a device");

module_param(शेष_uart_mode, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(शेष_uart_mode, "Default uart_mode, 0=RS232, ...");

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI 3410/5052 USB Serial Driver
 *
 * Copyright (C) 2004 Texas Instruments
 *
 * This driver is based on the Linux io_ti driver, which is
 *   Copyright (C) 2000-2002 Inside Out Networks
 *   Copyright (C) 2001-2002 Greg Kroah-Harपंचांगan
 *
 * For questions or problems with this driver, contact Texas Instruments
 * technical support, or Al Borchers <alborchers@steinerpoपूर्णांक.com>, or
 * Peter Berger <pberger@brimson.com>.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/serial.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

/* Configuration ids */
#घोषणा TI_BOOT_CONFIG			1
#घोषणा TI_ACTIVE_CONFIG		2

/* Venकरोr and product ids */
#घोषणा TI_VENDOR_ID			0x0451
#घोषणा IBM_VENDOR_ID			0x04b3
#घोषणा STARTECH_VENDOR_ID		0x14b0
#घोषणा TI_3410_PRODUCT_ID		0x3410
#घोषणा IBM_4543_PRODUCT_ID		0x4543
#घोषणा IBM_454B_PRODUCT_ID		0x454b
#घोषणा IBM_454C_PRODUCT_ID		0x454c
#घोषणा TI_3410_EZ430_ID		0xF430  /* TI ez430 development tool */
#घोषणा TI_5052_BOOT_PRODUCT_ID		0x5052	/* no EEPROM, no firmware */
#घोषणा TI_5152_BOOT_PRODUCT_ID		0x5152	/* no EEPROM, no firmware */
#घोषणा TI_5052_EEPROM_PRODUCT_ID	0x505A	/* EEPROM, no firmware */
#घोषणा TI_5052_FIRMWARE_PRODUCT_ID	0x505F	/* firmware is running */
#घोषणा FRI2_PRODUCT_ID			0x5053  /* Fish River Island II */

/* Multi-Tech venकरोr and product ids */
#घोषणा MTS_VENDOR_ID			0x06E0
#घोषणा MTS_GSM_NO_FW_PRODUCT_ID	0xF108
#घोषणा MTS_CDMA_NO_FW_PRODUCT_ID	0xF109
#घोषणा MTS_CDMA_PRODUCT_ID		0xF110
#घोषणा MTS_GSM_PRODUCT_ID		0xF111
#घोषणा MTS_EDGE_PRODUCT_ID		0xF112
#घोषणा MTS_MT9234MU_PRODUCT_ID		0xF114
#घोषणा MTS_MT9234ZBA_PRODUCT_ID	0xF115
#घोषणा MTS_MT9234ZBAOLD_PRODUCT_ID	0x0319

/* Abbott Diabetics venकरोr and product ids */
#घोषणा ABBOTT_VENDOR_ID		0x1a61
#घोषणा ABBOTT_STEREO_PLUG_ID		0x3410
#घोषणा ABBOTT_PRODUCT_ID		ABBOTT_STEREO_PLUG_ID
#घोषणा ABBOTT_STRIP_PORT_ID		0x3420

/* Honeywell venकरोr and product IDs */
#घोषणा HONEYWELL_VENDOR_ID		0x10ac
#घोषणा HONEYWELL_HGI80_PRODUCT_ID	0x0102  /* Honeywell HGI80 */

/* Moxa UPORT 11x0 venकरोr and product IDs */
#घोषणा MXU1_VENDOR_ID				0x110a
#घोषणा MXU1_1110_PRODUCT_ID			0x1110
#घोषणा MXU1_1130_PRODUCT_ID			0x1130
#घोषणा MXU1_1150_PRODUCT_ID			0x1150
#घोषणा MXU1_1151_PRODUCT_ID			0x1151
#घोषणा MXU1_1131_PRODUCT_ID			0x1131

/* Commands */
#घोषणा TI_GET_VERSION			0x01
#घोषणा TI_GET_PORT_STATUS		0x02
#घोषणा TI_GET_PORT_DEV_INFO		0x03
#घोषणा TI_GET_CONFIG			0x04
#घोषणा TI_SET_CONFIG			0x05
#घोषणा TI_OPEN_PORT			0x06
#घोषणा TI_CLOSE_PORT			0x07
#घोषणा TI_START_PORT			0x08
#घोषणा TI_STOP_PORT			0x09
#घोषणा TI_TEST_PORT			0x0A
#घोषणा TI_PURGE_PORT			0x0B
#घोषणा TI_RESET_EXT_DEVICE		0x0C
#घोषणा TI_WRITE_DATA			0x80
#घोषणा TI_READ_DATA			0x81
#घोषणा TI_REQ_TYPE_CLASS		0x82

/* Module identअगरiers */
#घोषणा TI_I2C_PORT			0x01
#घोषणा TI_IEEE1284_PORT		0x02
#घोषणा TI_UART1_PORT			0x03
#घोषणा TI_UART2_PORT			0x04
#घोषणा TI_RAM_PORT			0x05

/* Modem status */
#घोषणा TI_MSR_DELTA_CTS		0x01
#घोषणा TI_MSR_DELTA_DSR		0x02
#घोषणा TI_MSR_DELTA_RI			0x04
#घोषणा TI_MSR_DELTA_CD			0x08
#घोषणा TI_MSR_CTS			0x10
#घोषणा TI_MSR_DSR			0x20
#घोषणा TI_MSR_RI			0x40
#घोषणा TI_MSR_CD			0x80
#घोषणा TI_MSR_DELTA_MASK		0x0F
#घोषणा TI_MSR_MASK			0xF0

/* Line status */
#घोषणा TI_LSR_OVERRUN_ERROR		0x01
#घोषणा TI_LSR_PARITY_ERROR		0x02
#घोषणा TI_LSR_FRAMING_ERROR		0x04
#घोषणा TI_LSR_BREAK			0x08
#घोषणा TI_LSR_ERROR			0x0F
#घोषणा TI_LSR_RX_FULL			0x10
#घोषणा TI_LSR_TX_EMPTY			0x20
#घोषणा TI_LSR_TX_EMPTY_BOTH		0x40

/* Line control */
#घोषणा TI_LCR_BREAK			0x40

/* Modem control */
#घोषणा TI_MCR_LOOP			0x04
#घोषणा TI_MCR_DTR			0x10
#घोषणा TI_MCR_RTS			0x20

/* Mask settings */
#घोषणा TI_UART_ENABLE_RTS_IN		0x0001
#घोषणा TI_UART_DISABLE_RTS		0x0002
#घोषणा TI_UART_ENABLE_PARITY_CHECKING	0x0008
#घोषणा TI_UART_ENABLE_DSR_OUT		0x0010
#घोषणा TI_UART_ENABLE_CTS_OUT		0x0020
#घोषणा TI_UART_ENABLE_X_OUT		0x0040
#घोषणा TI_UART_ENABLE_XA_OUT		0x0080
#घोषणा TI_UART_ENABLE_X_IN		0x0100
#घोषणा TI_UART_ENABLE_DTR_IN		0x0800
#घोषणा TI_UART_DISABLE_DTR		0x1000
#घोषणा TI_UART_ENABLE_MS_INTS		0x2000
#घोषणा TI_UART_ENABLE_AUTO_START_DMA	0x4000

/* Parity */
#घोषणा TI_UART_NO_PARITY		0x00
#घोषणा TI_UART_ODD_PARITY		0x01
#घोषणा TI_UART_EVEN_PARITY		0x02
#घोषणा TI_UART_MARK_PARITY		0x03
#घोषणा TI_UART_SPACE_PARITY		0x04

/* Stop bits */
#घोषणा TI_UART_1_STOP_BITS		0x00
#घोषणा TI_UART_1_5_STOP_BITS		0x01
#घोषणा TI_UART_2_STOP_BITS		0x02

/* Bits per अक्षरacter */
#घोषणा TI_UART_5_DATA_BITS		0x00
#घोषणा TI_UART_6_DATA_BITS		0x01
#घोषणा TI_UART_7_DATA_BITS		0x02
#घोषणा TI_UART_8_DATA_BITS		0x03

/* 232/485 modes */
#घोषणा TI_UART_232			0x00
#घोषणा TI_UART_485_RECEIVER_DISABLED	0x01
#घोषणा TI_UART_485_RECEIVER_ENABLED	0x02

/* Pipe transfer mode and समयout */
#घोषणा TI_PIPE_MODE_CONTINUOUS		0x01
#घोषणा TI_PIPE_MODE_MASK		0x03
#घोषणा TI_PIPE_TIMEOUT_MASK		0x7C
#घोषणा TI_PIPE_TIMEOUT_ENABLE		0x80

/* Config काष्ठा */
काष्ठा ti_uart_config अणु
	__be16	wBaudRate;
	__be16	wFlags;
	u8	bDataBits;
	u8	bParity;
	u8	bStopBits;
	अक्षर	cXon;
	अक्षर	cXoff;
	u8	bUartMode;
पूर्ण;

/* Get port status */
काष्ठा ti_port_status अणु
	u8 bCmdCode;
	u8 bModuleId;
	u8 bErrorCode;
	u8 bMSR;
	u8 bLSR;
पूर्ण;

/* Purge modes */
#घोषणा TI_PURGE_OUTPUT			0x00
#घोषणा TI_PURGE_INPUT			0x80

/* Read/Write data */
#घोषणा TI_RW_DATA_ADDR_SFR		0x10
#घोषणा TI_RW_DATA_ADDR_IDATA		0x20
#घोषणा TI_RW_DATA_ADDR_XDATA		0x30
#घोषणा TI_RW_DATA_ADDR_CODE		0x40
#घोषणा TI_RW_DATA_ADDR_GPIO		0x50
#घोषणा TI_RW_DATA_ADDR_I2C		0x60
#घोषणा TI_RW_DATA_ADDR_FLASH		0x70
#घोषणा TI_RW_DATA_ADDR_DSP		0x80

#घोषणा TI_RW_DATA_UNSPECIFIED		0x00
#घोषणा TI_RW_DATA_BYTE			0x01
#घोषणा TI_RW_DATA_WORD			0x02
#घोषणा TI_RW_DATA_DOUBLE_WORD		0x04

काष्ठा ti_ग_लिखो_data_bytes अणु
	u8	bAddrType;
	u8	bDataType;
	u8	bDataCounter;
	__be16	wBaseAddrHi;
	__be16	wBaseAddrLo;
	u8	bData[];
पूर्ण __packed;

काष्ठा ti_पढ़ो_data_request अणु
	u8	bAddrType;
	u8	bDataType;
	u8	bDataCounter;
	__be16	wBaseAddrHi;
	__be16	wBaseAddrLo;
पूर्ण __packed;

काष्ठा ti_पढ़ो_data_bytes अणु
	u8	bCmdCode;
	u8	bModuleId;
	u8	bErrorCode;
	u8	bData[];
पूर्ण;

/* Interrupt काष्ठा */
काष्ठा ti_पूर्णांकerrupt अणु
	u8	bICode;
	u8	bIInfo;
पूर्ण;

/* Interrupt codes */
#घोषणा TI_CODE_HARDWARE_ERROR		0xFF
#घोषणा TI_CODE_DATA_ERROR		0x03
#घोषणा TI_CODE_MODEM_STATUS		0x04

/* Download firmware max packet size */
#घोषणा TI_DOWNLOAD_MAX_PACKET_SIZE	64

/* Firmware image header */
काष्ठा ti_firmware_header अणु
	__le16	wLength;
	u8	bCheckSum;
पूर्ण __packed;

/* UART addresses */
#घोषणा TI_UART1_BASE_ADDR		0xFFA0	/* UART 1 base address */
#घोषणा TI_UART2_BASE_ADDR		0xFFB0	/* UART 2 base address */
#घोषणा TI_UART_OFFSET_LCR		0x0002	/* UART MCR रेजिस्टर offset */
#घोषणा TI_UART_OFFSET_MCR		0x0004	/* UART MCR रेजिस्टर offset */

#घोषणा TI_DRIVER_AUTHOR	"Al Borchers <alborchers@steinerpoint.com>"
#घोषणा TI_DRIVER_DESC		"TI USB 3410/5052 Serial Driver"

#घोषणा TI_FIRMWARE_BUF_SIZE	16284

#घोषणा TI_TRANSFER_TIMEOUT	2

/* पढ़ो urb states */
#घोषणा TI_READ_URB_RUNNING	0
#घोषणा TI_READ_URB_STOPPING	1
#घोषणा TI_READ_URB_STOPPED	2

#घोषणा TI_EXTRA_VID_PID_COUNT	5

काष्ठा ti_port अणु
	पूर्णांक			tp_is_खोलो;
	u8			tp_msr;
	u8			tp_shaकरोw_mcr;
	u8			tp_uart_mode;	/* 232 or 485 modes */
	अचिन्हित पूर्णांक		tp_uart_base_addr;
	काष्ठा ti_device	*tp_tdev;
	काष्ठा usb_serial_port	*tp_port;
	spinlock_t		tp_lock;
	पूर्णांक			tp_पढ़ो_urb_state;
	पूर्णांक			tp_ग_लिखो_urb_in_use;
पूर्ण;

काष्ठा ti_device अणु
	काष्ठा mutex		td_खोलो_बंद_lock;
	पूर्णांक			td_खोलो_port_count;
	काष्ठा usb_serial	*td_serial;
	पूर्णांक			td_is_3410;
	bool			td_rs485_only;
पूर्ण;

अटल पूर्णांक ti_startup(काष्ठा usb_serial *serial);
अटल व्योम ti_release(काष्ठा usb_serial *serial);
अटल पूर्णांक ti_port_probe(काष्ठा usb_serial_port *port);
अटल व्योम ti_port_हटाओ(काष्ठा usb_serial_port *port);
अटल पूर्णांक ti_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
अटल व्योम ti_बंद(काष्ठा usb_serial_port *port);
अटल पूर्णांक ti_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
		स्थिर अचिन्हित अक्षर *data, पूर्णांक count);
अटल पूर्णांक ti_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक ti_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty);
अटल bool ti_tx_empty(काष्ठा usb_serial_port *port);
अटल व्योम ti_throttle(काष्ठा tty_काष्ठा *tty);
अटल व्योम ti_unthrottle(काष्ठा tty_काष्ठा *tty);
अटल व्योम ti_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios);
अटल पूर्णांक ti_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक ti_tiocmset(काष्ठा tty_काष्ठा *tty,
		अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल व्योम ti_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state);
अटल व्योम ti_पूर्णांकerrupt_callback(काष्ठा urb *urb);
अटल व्योम ti_bulk_in_callback(काष्ठा urb *urb);
अटल व्योम ti_bulk_out_callback(काष्ठा urb *urb);

अटल व्योम ti_recv(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *data,
		पूर्णांक length);
अटल व्योम ti_send(काष्ठा ti_port *tport);
अटल पूर्णांक ti_set_mcr(काष्ठा ti_port *tport, अचिन्हित पूर्णांक mcr);
अटल पूर्णांक ti_get_lsr(काष्ठा ti_port *tport, u8 *lsr);
अटल व्योम ti_get_serial_info(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss);
अटल व्योम ti_handle_new_msr(काष्ठा ti_port *tport, u8 msr);

अटल व्योम ti_stop_पढ़ो(काष्ठा ti_port *tport, काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक ti_restart_पढ़ो(काष्ठा ti_port *tport, काष्ठा tty_काष्ठा *tty);

अटल पूर्णांक ti_command_out_sync(काष्ठा usb_device *udev, u8 command,
		u16 moduleid, u16 value, व्योम *data, पूर्णांक size);
अटल पूर्णांक ti_command_in_sync(काष्ठा usb_device *udev, u8 command,
		u16 moduleid, u16 value, व्योम *data, पूर्णांक size);
अटल पूर्णांक ti_port_cmd_out(काष्ठा usb_serial_port *port, u8 command,
		u16 value, व्योम *data, पूर्णांक size);
अटल पूर्णांक ti_port_cmd_in(काष्ठा usb_serial_port *port, u8 command,
		u16 value, व्योम *data, पूर्णांक size);

अटल पूर्णांक ti_ग_लिखो_byte(काष्ठा usb_serial_port *port, काष्ठा ti_device *tdev,
			 अचिन्हित दीर्घ addr, u8 mask, u8 byte);

अटल पूर्णांक ti_करोwnload_firmware(काष्ठा ti_device *tdev);

अटल स्थिर काष्ठा usb_device_id ti_id_table_3410[] = अणु
	अणु USB_DEVICE(TI_VENDOR_ID, TI_3410_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_3410_EZ430_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_GSM_NO_FW_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_CDMA_NO_FW_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_CDMA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_GSM_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_EDGE_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_MT9234MU_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_MT9234ZBA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_MT9234ZBAOLD_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(IBM_VENDOR_ID, IBM_4543_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(IBM_VENDOR_ID, IBM_454B_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(IBM_VENDOR_ID, IBM_454C_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ABBOTT_VENDOR_ID, ABBOTT_STEREO_PLUG_ID) पूर्ण,
	अणु USB_DEVICE(ABBOTT_VENDOR_ID, ABBOTT_STRIP_PORT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, FRI2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HONEYWELL_VENDOR_ID, HONEYWELL_HGI80_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1110_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1130_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1131_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1150_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1151_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(STARTECH_VENDOR_ID, TI_3410_PRODUCT_ID) पूर्ण,
	अणु पूर्ण	/* terminator */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id ti_id_table_5052[] = अणु
	अणु USB_DEVICE(TI_VENDOR_ID, TI_5052_BOOT_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_5152_BOOT_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_5052_EEPROM_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_5052_FIRMWARE_PRODUCT_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id ti_id_table_combined[] = अणु
	अणु USB_DEVICE(TI_VENDOR_ID, TI_3410_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_3410_EZ430_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_GSM_NO_FW_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_CDMA_NO_FW_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_CDMA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_GSM_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_EDGE_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_MT9234MU_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_MT9234ZBA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MTS_VENDOR_ID, MTS_MT9234ZBAOLD_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_5052_BOOT_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_5152_BOOT_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_5052_EEPROM_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, TI_5052_FIRMWARE_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(IBM_VENDOR_ID, IBM_4543_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(IBM_VENDOR_ID, IBM_454B_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(IBM_VENDOR_ID, IBM_454C_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ABBOTT_VENDOR_ID, ABBOTT_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ABBOTT_VENDOR_ID, ABBOTT_STRIP_PORT_ID) पूर्ण,
	अणु USB_DEVICE(TI_VENDOR_ID, FRI2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HONEYWELL_VENDOR_ID, HONEYWELL_HGI80_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1110_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1130_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1131_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1150_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(MXU1_VENDOR_ID, MXU1_1151_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(STARTECH_VENDOR_ID, TI_3410_PRODUCT_ID) पूर्ण,
	अणु पूर्ण	/* terminator */
पूर्ण;

अटल काष्ठा usb_serial_driver ti_1port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "ti_usb_3410_5052_1",
	पूर्ण,
	.description		= "TI USB 3410 1 port adapter",
	.id_table		= ti_id_table_3410,
	.num_ports		= 1,
	.num_bulk_out		= 1,
	.attach			= ti_startup,
	.release		= ti_release,
	.port_probe		= ti_port_probe,
	.port_हटाओ		= ti_port_हटाओ,
	.खोलो			= ti_खोलो,
	.बंद			= ti_बंद,
	.ग_लिखो			= ti_ग_लिखो,
	.ग_लिखो_room		= ti_ग_लिखो_room,
	.अक्षरs_in_buffer	= ti_अक्षरs_in_buffer,
	.tx_empty		= ti_tx_empty,
	.throttle		= ti_throttle,
	.unthrottle		= ti_unthrottle,
	.get_serial		= ti_get_serial_info,
	.set_termios		= ti_set_termios,
	.tiocmget		= ti_tiocmget,
	.tiocmset		= ti_tiocmset,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.अवरोध_ctl		= ti_अवरोध,
	.पढ़ो_पूर्णांक_callback	= ti_पूर्णांकerrupt_callback,
	.पढ़ो_bulk_callback	= ti_bulk_in_callback,
	.ग_लिखो_bulk_callback	= ti_bulk_out_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver ti_2port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "ti_usb_3410_5052_2",
	पूर्ण,
	.description		= "TI USB 5052 2 port adapter",
	.id_table		= ti_id_table_5052,
	.num_ports		= 2,
	.num_bulk_out		= 1,
	.attach			= ti_startup,
	.release		= ti_release,
	.port_probe		= ti_port_probe,
	.port_हटाओ		= ti_port_हटाओ,
	.खोलो			= ti_खोलो,
	.बंद			= ti_बंद,
	.ग_लिखो			= ti_ग_लिखो,
	.ग_लिखो_room		= ti_ग_लिखो_room,
	.अक्षरs_in_buffer	= ti_अक्षरs_in_buffer,
	.tx_empty		= ti_tx_empty,
	.throttle		= ti_throttle,
	.unthrottle		= ti_unthrottle,
	.get_serial		= ti_get_serial_info,
	.set_termios		= ti_set_termios,
	.tiocmget		= ti_tiocmget,
	.tiocmset		= ti_tiocmset,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.अवरोध_ctl		= ti_अवरोध,
	.पढ़ो_पूर्णांक_callback	= ti_पूर्णांकerrupt_callback,
	.पढ़ो_bulk_callback	= ti_bulk_in_callback,
	.ग_लिखो_bulk_callback	= ti_bulk_out_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&ti_1port_device, &ti_2port_device, शून्य
पूर्ण;

MODULE_AUTHOR(TI_DRIVER_AUTHOR);
MODULE_DESCRIPTION(TI_DRIVER_DESC);
MODULE_LICENSE("GPL");

MODULE_FIRMWARE("ti_3410.fw");
MODULE_FIRMWARE("ti_5052.fw");
MODULE_FIRMWARE("mts_cdma.fw");
MODULE_FIRMWARE("mts_gsm.fw");
MODULE_FIRMWARE("mts_edge.fw");
MODULE_FIRMWARE("mts_mt9234mu.fw");
MODULE_FIRMWARE("mts_mt9234zba.fw");
MODULE_FIRMWARE("moxa/moxa-1110.fw");
MODULE_FIRMWARE("moxa/moxa-1130.fw");
MODULE_FIRMWARE("moxa/moxa-1131.fw");
MODULE_FIRMWARE("moxa/moxa-1150.fw");
MODULE_FIRMWARE("moxa/moxa-1151.fw");

MODULE_DEVICE_TABLE(usb, ti_id_table_combined);

module_usb_serial_driver(serial_drivers, ti_id_table_combined);

अटल पूर्णांक ti_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा ti_device *tdev;
	काष्ठा usb_device *dev = serial->dev;
	काष्ठा usb_host_पूर्णांकerface *cur_altsetting;
	पूर्णांक num_endpoपूर्णांकs;
	u16 vid, pid;
	पूर्णांक status;

	dev_dbg(&dev->dev,
		"%s - product 0x%4X, num configurations %d, configuration value %d\n",
		__func__, le16_to_cpu(dev->descriptor.idProduct),
		dev->descriptor.bNumConfigurations,
		dev->actconfig->desc.bConfigurationValue);

	tdev = kzalloc(माप(काष्ठा ti_device), GFP_KERNEL);
	अगर (!tdev)
		वापस -ENOMEM;

	mutex_init(&tdev->td_खोलो_बंद_lock);
	tdev->td_serial = serial;
	usb_set_serial_data(serial, tdev);

	/* determine device type */
	अगर (serial->type == &ti_1port_device)
		tdev->td_is_3410 = 1;
	dev_dbg(&dev->dev, "%s - device type is %s\n", __func__,
		tdev->td_is_3410 ? "3410" : "5052");

	vid = le16_to_cpu(dev->descriptor.idVenकरोr);
	pid = le16_to_cpu(dev->descriptor.idProduct);
	अगर (vid == MXU1_VENDOR_ID) अणु
		चयन (pid) अणु
		हाल MXU1_1130_PRODUCT_ID:
		हाल MXU1_1131_PRODUCT_ID:
			tdev->td_rs485_only = true;
			अवरोध;
		पूर्ण
	पूर्ण

	cur_altsetting = serial->पूर्णांकerface->cur_altsetting;
	num_endpoपूर्णांकs = cur_altsetting->desc.bNumEndpoपूर्णांकs;

	/* अगर we have only 1 configuration and 1 endpoपूर्णांक, करोwnload firmware */
	अगर (dev->descriptor.bNumConfigurations == 1 && num_endpoपूर्णांकs == 1) अणु
		status = ti_करोwnload_firmware(tdev);

		अगर (status != 0)
			जाओ मुक्त_tdev;

		/* 3410 must be reset, 5052 resets itself */
		अगर (tdev->td_is_3410) अणु
			msleep_पूर्णांकerruptible(100);
			usb_reset_device(dev);
		पूर्ण

		status = -ENODEV;
		जाओ मुक्त_tdev;
	पूर्ण

	/* the second configuration must be set */
	अगर (dev->actconfig->desc.bConfigurationValue == TI_BOOT_CONFIG) अणु
		status = usb_driver_set_configuration(dev, TI_ACTIVE_CONFIG);
		status = status ? status : -ENODEV;
		जाओ मुक्त_tdev;
	पूर्ण

	अगर (serial->num_bulk_in < serial->num_ports ||
			serial->num_bulk_out < serial->num_ports) अणु
		dev_err(&serial->पूर्णांकerface->dev, "missing endpoints\n");
		status = -ENODEV;
		जाओ मुक्त_tdev;
	पूर्ण

	वापस 0;

मुक्त_tdev:
	kमुक्त(tdev);
	usb_set_serial_data(serial, शून्य);
	वापस status;
पूर्ण


अटल व्योम ti_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा ti_device *tdev = usb_get_serial_data(serial);

	kमुक्त(tdev);
पूर्ण

अटल पूर्णांक ti_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ti_port *tport;

	tport = kzalloc(माप(*tport), GFP_KERNEL);
	अगर (!tport)
		वापस -ENOMEM;

	spin_lock_init(&tport->tp_lock);
	अगर (port == port->serial->port[0])
		tport->tp_uart_base_addr = TI_UART1_BASE_ADDR;
	अन्यथा
		tport->tp_uart_base_addr = TI_UART2_BASE_ADDR;
	tport->tp_port = port;
	tport->tp_tdev = usb_get_serial_data(port->serial);

	अगर (tport->tp_tdev->td_rs485_only)
		tport->tp_uart_mode = TI_UART_485_RECEIVER_DISABLED;
	अन्यथा
		tport->tp_uart_mode = TI_UART_232;

	usb_set_serial_port_data(port, tport);

	/*
	 * The TUSB5052 LSR करोes not tell when the transmitter shअगरt रेजिस्टर
	 * has emptied so add a one-अक्षरacter drain delay.
	 */
	अगर (!tport->tp_tdev->td_is_3410)
		port->port.drain_delay = 1;

	वापस 0;
पूर्ण

अटल व्योम ti_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ti_port *tport;

	tport = usb_get_serial_port_data(port);
	kमुक्त(tport);
पूर्ण

अटल पूर्णांक ti_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	काष्ठा ti_device *tdev;
	काष्ठा usb_device *dev;
	काष्ठा urb *urb;
	पूर्णांक status;
	u16 खोलो_settings;

	खोलो_settings = (TI_PIPE_MODE_CONTINUOUS |
			 TI_PIPE_TIMEOUT_ENABLE |
			 (TI_TRANSFER_TIMEOUT << 2));

	dev = port->serial->dev;
	tdev = tport->tp_tdev;

	/* only one खोलो on any port on a device at a समय */
	अगर (mutex_lock_पूर्णांकerruptible(&tdev->td_खोलो_बंद_lock))
		वापस -ERESTARTSYS;

	tport->tp_msr = 0;
	tport->tp_shaकरोw_mcr |= (TI_MCR_RTS | TI_MCR_DTR);

	/* start पूर्णांकerrupt urb the first समय a port is खोलोed on this device */
	अगर (tdev->td_खोलो_port_count == 0) अणु
		dev_dbg(&port->dev, "%s - start interrupt in urb\n", __func__);
		urb = tdev->td_serial->port[0]->पूर्णांकerrupt_in_urb;
		अगर (!urb) अणु
			dev_err(&port->dev, "%s - no interrupt urb\n", __func__);
			status = -EINVAL;
			जाओ release_lock;
		पूर्ण
		urb->context = tdev;
		status = usb_submit_urb(urb, GFP_KERNEL);
		अगर (status) अणु
			dev_err(&port->dev, "%s - submit interrupt urb failed, %d\n", __func__, status);
			जाओ release_lock;
		पूर्ण
	पूर्ण

	अगर (tty)
		ti_set_termios(tty, port, &tty->termios);

	status = ti_port_cmd_out(port, TI_OPEN_PORT, खोलो_settings, शून्य, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot send open command, %d\n",
			__func__, status);
		जाओ unlink_पूर्णांक_urb;
	पूर्ण

	status = ti_port_cmd_out(port, TI_START_PORT, 0, शून्य, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot send start command, %d\n",
							__func__, status);
		जाओ unlink_पूर्णांक_urb;
	पूर्ण

	status = ti_port_cmd_out(port, TI_PURGE_PORT, TI_PURGE_INPUT, शून्य, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot clear input buffers, %d\n",
							__func__, status);
		जाओ unlink_पूर्णांक_urb;
	पूर्ण
	status = ti_port_cmd_out(port, TI_PURGE_PORT, TI_PURGE_OUTPUT, शून्य, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot clear output buffers, %d\n",
							__func__, status);
		जाओ unlink_पूर्णांक_urb;
	पूर्ण

	/* reset the data toggle on the bulk endpoपूर्णांकs to work around bug in
	 * host controllers where things get out of sync some बार */
	usb_clear_halt(dev, port->ग_लिखो_urb->pipe);
	usb_clear_halt(dev, port->पढ़ो_urb->pipe);

	अगर (tty)
		ti_set_termios(tty, port, &tty->termios);

	status = ti_port_cmd_out(port, TI_OPEN_PORT, खोलो_settings, शून्य, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot send open command (2), %d\n",
							__func__, status);
		जाओ unlink_पूर्णांक_urb;
	पूर्ण

	status = ti_port_cmd_out(port, TI_START_PORT, 0, शून्य, 0);
	अगर (status) अणु
		dev_err(&port->dev, "%s - cannot send start command (2), %d\n",
							__func__, status);
		जाओ unlink_पूर्णांक_urb;
	पूर्ण

	/* start पढ़ो urb */
	urb = port->पढ़ो_urb;
	अगर (!urb) अणु
		dev_err(&port->dev, "%s - no read urb\n", __func__);
		status = -EINVAL;
		जाओ unlink_पूर्णांक_urb;
	पूर्ण
	tport->tp_पढ़ो_urb_state = TI_READ_URB_RUNNING;
	urb->context = tport;
	status = usb_submit_urb(urb, GFP_KERNEL);
	अगर (status) अणु
		dev_err(&port->dev, "%s - submit read urb failed, %d\n",
							__func__, status);
		जाओ unlink_पूर्णांक_urb;
	पूर्ण

	tport->tp_is_खोलो = 1;
	++tdev->td_खोलो_port_count;

	जाओ release_lock;

unlink_पूर्णांक_urb:
	अगर (tdev->td_खोलो_port_count == 0)
		usb_समाप्त_urb(port->serial->port[0]->पूर्णांकerrupt_in_urb);
release_lock:
	mutex_unlock(&tdev->td_खोलो_बंद_lock);
	वापस status;
पूर्ण


अटल व्योम ti_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ti_device *tdev;
	काष्ठा ti_port *tport;
	पूर्णांक status;
	अचिन्हित दीर्घ flags;

	tdev = usb_get_serial_data(port->serial);
	tport = usb_get_serial_port_data(port);

	tport->tp_is_खोलो = 0;

	usb_समाप्त_urb(port->पढ़ो_urb);
	usb_समाप्त_urb(port->ग_लिखो_urb);
	tport->tp_ग_लिखो_urb_in_use = 0;
	spin_lock_irqsave(&tport->tp_lock, flags);
	kfअगरo_reset_out(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&tport->tp_lock, flags);

	status = ti_port_cmd_out(port, TI_CLOSE_PORT, 0, शून्य, 0);
	अगर (status)
		dev_err(&port->dev,
			"%s - cannot send close port command, %d\n"
							, __func__, status);

	mutex_lock(&tdev->td_खोलो_बंद_lock);
	--tdev->td_खोलो_port_count;
	अगर (tdev->td_खोलो_port_count == 0) अणु
		/* last port is बंदd, shut करोwn पूर्णांकerrupt urb */
		usb_समाप्त_urb(port->serial->port[0]->पूर्णांकerrupt_in_urb);
	पूर्ण
	mutex_unlock(&tdev->td_खोलो_बंद_lock);
पूर्ण


अटल पूर्णांक ti_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			स्थिर अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);

	अगर (count == 0) अणु
		वापस 0;
	पूर्ण

	अगर (!tport->tp_is_खोलो)
		वापस -ENODEV;

	count = kfअगरo_in_locked(&port->ग_लिखो_fअगरo, data, count,
							&tport->tp_lock);
	ti_send(tport);

	वापस count;
पूर्ण


अटल पूर्णांक ti_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	पूर्णांक room = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tport->tp_lock, flags);
	room = kfअगरo_avail(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&tport->tp_lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, room);
	वापस room;
पूर्ण


अटल पूर्णांक ti_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	पूर्णांक अक्षरs = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tport->tp_lock, flags);
	अक्षरs = kfअगरo_len(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&tport->tp_lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, अक्षरs);
	वापस अक्षरs;
पूर्ण

अटल bool ti_tx_empty(काष्ठा usb_serial_port *port)
अणु
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	u8 lsr, mask;
	पूर्णांक ret;

	/*
	 * TUSB5052 करोes not have the TEMT bit to tell अगर the shअगरt रेजिस्टर
	 * is empty.
	 */
	अगर (tport->tp_tdev->td_is_3410)
		mask = TI_LSR_TX_EMPTY_BOTH;
	अन्यथा
		mask = TI_LSR_TX_EMPTY;

	ret = ti_get_lsr(tport, &lsr);
	अगर (!ret && !(lsr & mask))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम ti_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);

	अगर (I_IXOFF(tty) || C_CRTSCTS(tty))
		ti_stop_पढ़ो(tport, tty);

पूर्ण


अटल व्योम ti_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	पूर्णांक status;

	अगर (I_IXOFF(tty) || C_CRTSCTS(tty)) अणु
		status = ti_restart_पढ़ो(tport, tty);
		अगर (status)
			dev_err(&port->dev, "%s - cannot restart read, %d\n",
							__func__, status);
	पूर्ण
पूर्ण

अटल व्योम ti_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	काष्ठा ti_uart_config *config;
	पूर्णांक baud;
	पूर्णांक status;
	अचिन्हित पूर्णांक mcr;
	u16 wbaudrate;
	u16 wflags = 0;

	config = kदो_स्मृति(माप(*config), GFP_KERNEL);
	अगर (!config)
		वापस;

	/* these flags must be set */
	wflags |= TI_UART_ENABLE_MS_INTS;
	wflags |= TI_UART_ENABLE_AUTO_START_DMA;
	config->bUartMode = tport->tp_uart_mode;

	चयन (C_CSIZE(tty)) अणु
	हाल CS5:
		config->bDataBits = TI_UART_5_DATA_BITS;
		अवरोध;
	हाल CS6:
		config->bDataBits = TI_UART_6_DATA_BITS;
		अवरोध;
	हाल CS7:
		config->bDataBits = TI_UART_7_DATA_BITS;
		अवरोध;
	शेष:
	हाल CS8:
		config->bDataBits = TI_UART_8_DATA_BITS;
		अवरोध;
	पूर्ण

	/* CMSPAR isn't supported by this driver */
	tty->termios.c_cflag &= ~CMSPAR;

	अगर (C_PARENB(tty)) अणु
		अगर (C_PARODD(tty)) अणु
			wflags |= TI_UART_ENABLE_PARITY_CHECKING;
			config->bParity = TI_UART_ODD_PARITY;
		पूर्ण अन्यथा अणु
			wflags |= TI_UART_ENABLE_PARITY_CHECKING;
			config->bParity = TI_UART_EVEN_PARITY;
		पूर्ण
	पूर्ण अन्यथा अणु
		wflags &= ~TI_UART_ENABLE_PARITY_CHECKING;
		config->bParity = TI_UART_NO_PARITY;
	पूर्ण

	अगर (C_CSTOPB(tty))
		config->bStopBits = TI_UART_2_STOP_BITS;
	अन्यथा
		config->bStopBits = TI_UART_1_STOP_BITS;

	अगर (C_CRTSCTS(tty)) अणु
		/* RTS flow control must be off to drop RTS क्रम baud rate B0 */
		अगर ((C_BAUD(tty)) != B0)
			wflags |= TI_UART_ENABLE_RTS_IN;
		wflags |= TI_UART_ENABLE_CTS_OUT;
	पूर्ण अन्यथा अणु
		ti_restart_पढ़ो(tport, tty);
	पूर्ण

	अगर (I_IXOFF(tty) || I_IXON(tty)) अणु
		config->cXon  = START_CHAR(tty);
		config->cXoff = STOP_CHAR(tty);

		अगर (I_IXOFF(tty))
			wflags |= TI_UART_ENABLE_X_IN;
		अन्यथा
			ti_restart_पढ़ो(tport, tty);

		अगर (I_IXON(tty))
			wflags |= TI_UART_ENABLE_X_OUT;
	पूर्ण

	baud = tty_get_baud_rate(tty);
	अगर (!baud)
		baud = 9600;
	अगर (tport->tp_tdev->td_is_3410)
		wbaudrate = (923077 + baud/2) / baud;
	अन्यथा
		wbaudrate = (461538 + baud/2) / baud;

	/* FIXME: Should calculate resulting baud here and report it back */
	अगर ((C_BAUD(tty)) != B0)
		tty_encode_baud_rate(tty, baud, baud);

	dev_dbg(&port->dev,
		"%s - BaudRate=%d, wBaudRate=%d, wFlags=0x%04X, bDataBits=%d, bParity=%d, bStopBits=%d, cXon=%d, cXoff=%d, bUartMode=%d\n",
		__func__, baud, wbaudrate, wflags,
		config->bDataBits, config->bParity, config->bStopBits,
		config->cXon, config->cXoff, config->bUartMode);

	config->wBaudRate = cpu_to_be16(wbaudrate);
	config->wFlags = cpu_to_be16(wflags);

	status = ti_port_cmd_out(port, TI_SET_CONFIG, 0, config,
			माप(*config));
	अगर (status)
		dev_err(&port->dev, "%s - cannot set config on port %d, %d\n",
				__func__, port->port_number, status);

	/* SET_CONFIG निश्चितs RTS and DTR, reset them correctly */
	mcr = tport->tp_shaकरोw_mcr;
	/* अगर baud rate is B0, clear RTS and DTR */
	अगर (C_BAUD(tty) == B0)
		mcr &= ~(TI_MCR_DTR | TI_MCR_RTS);
	status = ti_set_mcr(tport, mcr);
	अगर (status)
		dev_err(&port->dev, "%s - cannot set modem control on port %d, %d\n",
				__func__, port->port_number, status);

	kमुक्त(config);
पूर्ण


अटल पूर्णांक ti_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक result;
	अचिन्हित पूर्णांक msr;
	अचिन्हित पूर्णांक mcr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tport->tp_lock, flags);
	msr = tport->tp_msr;
	mcr = tport->tp_shaकरोw_mcr;
	spin_unlock_irqrestore(&tport->tp_lock, flags);

	result = ((mcr & TI_MCR_DTR) ? TIOCM_DTR : 0)
		| ((mcr & TI_MCR_RTS) ? TIOCM_RTS : 0)
		| ((mcr & TI_MCR_LOOP) ? TIOCM_LOOP : 0)
		| ((msr & TI_MSR_CTS) ? TIOCM_CTS : 0)
		| ((msr & TI_MSR_CD) ? TIOCM_CAR : 0)
		| ((msr & TI_MSR_RI) ? TIOCM_RI : 0)
		| ((msr & TI_MSR_DSR) ? TIOCM_DSR : 0);

	dev_dbg(&port->dev, "%s - 0x%04X\n", __func__, result);

	वापस result;
पूर्ण


अटल पूर्णांक ti_tiocmset(काष्ठा tty_काष्ठा *tty,
				अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक mcr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tport->tp_lock, flags);
	mcr = tport->tp_shaकरोw_mcr;

	अगर (set & TIOCM_RTS)
		mcr |= TI_MCR_RTS;
	अगर (set & TIOCM_DTR)
		mcr |= TI_MCR_DTR;
	अगर (set & TIOCM_LOOP)
		mcr |= TI_MCR_LOOP;

	अगर (clear & TIOCM_RTS)
		mcr &= ~TI_MCR_RTS;
	अगर (clear & TIOCM_DTR)
		mcr &= ~TI_MCR_DTR;
	अगर (clear & TIOCM_LOOP)
		mcr &= ~TI_MCR_LOOP;
	spin_unlock_irqrestore(&tport->tp_lock, flags);

	वापस ti_set_mcr(tport, mcr);
पूर्ण


अटल व्योम ti_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);
	पूर्णांक status;

	dev_dbg(&port->dev, "%s - state = %d\n", __func__, अवरोध_state);

	status = ti_ग_लिखो_byte(port, tport->tp_tdev,
		tport->tp_uart_base_addr + TI_UART_OFFSET_LCR,
		TI_LCR_BREAK, अवरोध_state == -1 ? TI_LCR_BREAK : 0);

	अगर (status)
		dev_dbg(&port->dev, "%s - error setting break, %d\n", __func__, status);
पूर्ण

अटल पूर्णांक ti_get_port_from_code(अचिन्हित अक्षर code)
अणु
	वापस (code >> 6) & 0x01;
पूर्ण

अटल पूर्णांक ti_get_func_from_code(अचिन्हित अक्षर code)
अणु
	वापस code & 0x0f;
पूर्ण

अटल व्योम ti_पूर्णांकerrupt_callback(काष्ठा urb *urb)
अणु
	काष्ठा ti_device *tdev = urb->context;
	काष्ठा usb_serial_port *port;
	काष्ठा usb_serial *serial = tdev->td_serial;
	काष्ठा ti_port *tport;
	काष्ठा device *dev = &urb->dev->dev;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक length = urb->actual_length;
	पूर्णांक port_number;
	पूर्णांक function;
	पूर्णांक status = urb->status;
	पूर्णांक retval;
	u8 msr;

	चयन (status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		dev_dbg(dev, "%s - urb shutting down, %d\n", __func__, status);
		वापस;
	शेष:
		dev_err(dev, "%s - nonzero urb status, %d\n", __func__, status);
		जाओ निकास;
	पूर्ण

	अगर (length != 2) अणु
		dev_dbg(dev, "%s - bad packet size, %d\n", __func__, length);
		जाओ निकास;
	पूर्ण

	अगर (data[0] == TI_CODE_HARDWARE_ERROR) अणु
		dev_err(dev, "%s - hardware error, %d\n", __func__, data[1]);
		जाओ निकास;
	पूर्ण

	port_number = ti_get_port_from_code(data[0]);
	function = ti_get_func_from_code(data[0]);

	dev_dbg(dev, "%s - port_number %d, function %d, data 0x%02X\n",
		__func__, port_number, function, data[1]);

	अगर (port_number >= serial->num_ports) अणु
		dev_err(dev, "%s - bad port number, %d\n",
						__func__, port_number);
		जाओ निकास;
	पूर्ण

	port = serial->port[port_number];

	tport = usb_get_serial_port_data(port);
	अगर (!tport)
		जाओ निकास;

	चयन (function) अणु
	हाल TI_CODE_DATA_ERROR:
		dev_err(dev, "%s - DATA ERROR, port %d, data 0x%02X\n",
			__func__, port_number, data[1]);
		अवरोध;

	हाल TI_CODE_MODEM_STATUS:
		msr = data[1];
		dev_dbg(dev, "%s - port %d, msr 0x%02X\n", __func__, port_number, msr);
		ti_handle_new_msr(tport, msr);
		अवरोध;

	शेष:
		dev_err(dev, "%s - unknown interrupt code, 0x%02X\n",
							__func__, data[1]);
		अवरोध;
	पूर्ण

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(dev, "%s - resubmit interrupt urb failed, %d\n",
			__func__, retval);
पूर्ण


अटल व्योम ti_bulk_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा ti_port *tport = urb->context;
	काष्ठा usb_serial_port *port = tport->tp_port;
	काष्ठा device *dev = &urb->dev->dev;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	चयन (status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		dev_dbg(dev, "%s - urb shutting down, %d\n", __func__, status);
		वापस;
	शेष:
		dev_err(dev, "%s - nonzero urb status, %d\n",
			__func__, status);
	पूर्ण

	अगर (status == -EPIPE)
		जाओ निकास;

	अगर (status) अणु
		dev_err(dev, "%s - stopping read!\n", __func__);
		वापस;
	पूर्ण

	अगर (urb->actual_length) अणु
		usb_serial_debug_data(dev, __func__, urb->actual_length,
				      urb->transfer_buffer);

		अगर (!tport->tp_is_खोलो)
			dev_dbg(dev, "%s - port closed, dropping data\n",
				__func__);
		अन्यथा
			ti_recv(port, urb->transfer_buffer, urb->actual_length);
		spin_lock_irqsave(&tport->tp_lock, flags);
		port->icount.rx += urb->actual_length;
		spin_unlock_irqrestore(&tport->tp_lock, flags);
	पूर्ण

निकास:
	/* जारी to पढ़ो unless stopping */
	spin_lock_irqsave(&tport->tp_lock, flags);
	अगर (tport->tp_पढ़ो_urb_state == TI_READ_URB_RUNNING)
		retval = usb_submit_urb(urb, GFP_ATOMIC);
	अन्यथा अगर (tport->tp_पढ़ो_urb_state == TI_READ_URB_STOPPING)
		tport->tp_पढ़ो_urb_state = TI_READ_URB_STOPPED;

	spin_unlock_irqrestore(&tport->tp_lock, flags);
	अगर (retval)
		dev_err(dev, "%s - resubmit read urb failed, %d\n",
			__func__, retval);
पूर्ण


अटल व्योम ti_bulk_out_callback(काष्ठा urb *urb)
अणु
	काष्ठा ti_port *tport = urb->context;
	काष्ठा usb_serial_port *port = tport->tp_port;
	पूर्णांक status = urb->status;

	tport->tp_ग_लिखो_urb_in_use = 0;

	चयन (status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		dev_dbg(&port->dev, "%s - urb shutting down, %d\n", __func__, status);
		वापस;
	शेष:
		dev_err_console(port, "%s - nonzero urb status, %d\n",
			__func__, status);
	पूर्ण

	/* send any buffered data */
	ti_send(tport);
पूर्ण


अटल व्योम ti_recv(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *data,
		पूर्णांक length)
अणु
	पूर्णांक cnt;

	करो अणु
		cnt = tty_insert_flip_string(&port->port, data, length);
		अगर (cnt < length) अणु
			dev_err(&port->dev, "%s - dropping data, %d bytes lost\n",
						__func__, length - cnt);
			अगर (cnt == 0)
				अवरोध;
		पूर्ण
		tty_flip_buffer_push(&port->port);
		data += cnt;
		length -= cnt;
	पूर्ण जबतक (length > 0);
पूर्ण


अटल व्योम ti_send(काष्ठा ti_port *tport)
अणु
	पूर्णांक count, result;
	काष्ठा usb_serial_port *port = tport->tp_port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tport->tp_lock, flags);

	अगर (tport->tp_ग_लिखो_urb_in_use)
		जाओ unlock;

	count = kfअगरo_out(&port->ग_लिखो_fअगरo,
				port->ग_लिखो_urb->transfer_buffer,
				port->bulk_out_size);

	अगर (count == 0)
		जाओ unlock;

	tport->tp_ग_लिखो_urb_in_use = 1;

	spin_unlock_irqrestore(&tport->tp_lock, flags);

	usb_serial_debug_data(&port->dev, __func__, count,
			      port->ग_लिखो_urb->transfer_buffer);

	usb_fill_bulk_urb(port->ग_लिखो_urb, port->serial->dev,
			   usb_sndbulkpipe(port->serial->dev,
					    port->bulk_out_endpoपूर्णांकAddress),
			   port->ग_लिखो_urb->transfer_buffer, count,
			   ti_bulk_out_callback, tport);

	result = usb_submit_urb(port->ग_लिखो_urb, GFP_ATOMIC);
	अगर (result) अणु
		dev_err_console(port, "%s - submit write urb failed, %d\n",
							__func__, result);
		tport->tp_ग_लिखो_urb_in_use = 0;
		/* TODO: reschedule ti_send */
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&tport->tp_lock, flags);
		port->icount.tx += count;
		spin_unlock_irqrestore(&tport->tp_lock, flags);
	पूर्ण

	/* more room in the buffer क्रम new ग_लिखोs, wakeup */
	tty_port_tty_wakeup(&port->port);

	वापस;
unlock:
	spin_unlock_irqrestore(&tport->tp_lock, flags);
	वापस;
पूर्ण


अटल पूर्णांक ti_set_mcr(काष्ठा ti_port *tport, अचिन्हित पूर्णांक mcr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status;

	status = ti_ग_लिखो_byte(tport->tp_port, tport->tp_tdev,
		tport->tp_uart_base_addr + TI_UART_OFFSET_MCR,
		TI_MCR_RTS | TI_MCR_DTR | TI_MCR_LOOP, mcr);

	spin_lock_irqsave(&tport->tp_lock, flags);
	अगर (!status)
		tport->tp_shaकरोw_mcr = mcr;
	spin_unlock_irqrestore(&tport->tp_lock, flags);

	वापस status;
पूर्ण


अटल पूर्णांक ti_get_lsr(काष्ठा ti_port *tport, u8 *lsr)
अणु
	पूर्णांक size, status;
	काष्ठा usb_serial_port *port = tport->tp_port;
	काष्ठा ti_port_status *data;

	size = माप(काष्ठा ti_port_status);
	data = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	status = ti_port_cmd_in(port, TI_GET_PORT_STATUS, 0, data, size);
	अगर (status) अणु
		dev_err(&port->dev,
			"%s - get port status command failed, %d\n",
							__func__, status);
		जाओ मुक्त_data;
	पूर्ण

	dev_dbg(&port->dev, "%s - lsr 0x%02X\n", __func__, data->bLSR);

	*lsr = data->bLSR;

मुक्त_data:
	kमुक्त(data);
	वापस status;
पूर्ण


अटल व्योम ti_get_serial_info(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा ti_port *tport = usb_get_serial_port_data(port);

	ss->baud_base = tport->tp_tdev->td_is_3410 ? 921600 : 460800;
पूर्ण


अटल व्योम ti_handle_new_msr(काष्ठा ti_port *tport, u8 msr)
अणु
	काष्ठा async_icount *icount;
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित दीर्घ flags;

	dev_dbg(&tport->tp_port->dev, "%s - msr 0x%02X\n", __func__, msr);

	अगर (msr & TI_MSR_DELTA_MASK) अणु
		spin_lock_irqsave(&tport->tp_lock, flags);
		icount = &tport->tp_port->icount;
		अगर (msr & TI_MSR_DELTA_CTS)
			icount->cts++;
		अगर (msr & TI_MSR_DELTA_DSR)
			icount->dsr++;
		अगर (msr & TI_MSR_DELTA_CD)
			icount->dcd++;
		अगर (msr & TI_MSR_DELTA_RI)
			icount->rng++;
		wake_up_पूर्णांकerruptible(&tport->tp_port->port.delta_msr_रुको);
		spin_unlock_irqrestore(&tport->tp_lock, flags);
	पूर्ण

	tport->tp_msr = msr & TI_MSR_MASK;

	/* handle CTS flow control */
	tty = tty_port_tty_get(&tport->tp_port->port);
	अगर (tty && C_CRTSCTS(tty)) अणु
		अगर (msr & TI_MSR_CTS)
			tty_wakeup(tty);
	पूर्ण
	tty_kref_put(tty);
पूर्ण


अटल व्योम ti_stop_पढ़ो(काष्ठा ti_port *tport, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tport->tp_lock, flags);

	अगर (tport->tp_पढ़ो_urb_state == TI_READ_URB_RUNNING)
		tport->tp_पढ़ो_urb_state = TI_READ_URB_STOPPING;

	spin_unlock_irqrestore(&tport->tp_lock, flags);
पूर्ण


अटल पूर्णांक ti_restart_पढ़ो(काष्ठा ti_port *tport, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा urb *urb;
	पूर्णांक status = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tport->tp_lock, flags);

	अगर (tport->tp_पढ़ो_urb_state == TI_READ_URB_STOPPED) अणु
		tport->tp_पढ़ो_urb_state = TI_READ_URB_RUNNING;
		urb = tport->tp_port->पढ़ो_urb;
		spin_unlock_irqrestore(&tport->tp_lock, flags);
		urb->context = tport;
		status = usb_submit_urb(urb, GFP_KERNEL);
	पूर्ण अन्यथा  अणु
		tport->tp_पढ़ो_urb_state = TI_READ_URB_RUNNING;
		spin_unlock_irqrestore(&tport->tp_lock, flags);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ti_command_out_sync(काष्ठा usb_device *udev, u8 command,
		u16 moduleid, u16 value, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक status;

	status = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), command,
			USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
			value, moduleid, data, size, 1000);
	अगर (status < 0)
		वापस status;

	वापस 0;
पूर्ण

अटल पूर्णांक ti_command_in_sync(काष्ठा usb_device *udev, u8 command,
		u16 moduleid, u16 value, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक status;

	status = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), command,
			USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			value, moduleid, data, size, 1000);
	अगर (status == size)
		status = 0;
	अन्यथा अगर (status >= 0)
		status = -ECOMM;

	वापस status;
पूर्ण

अटल पूर्णांक ti_port_cmd_out(काष्ठा usb_serial_port *port, u8 command,
		u16 value, व्योम *data, पूर्णांक size)
अणु
	वापस ti_command_out_sync(port->serial->dev, command,
			TI_UART1_PORT + port->port_number,
			value, data, size);
पूर्ण

अटल पूर्णांक ti_port_cmd_in(काष्ठा usb_serial_port *port, u8 command,
		u16 value, व्योम *data, पूर्णांक size)
अणु
	वापस ti_command_in_sync(port->serial->dev, command,
			TI_UART1_PORT + port->port_number,
			value, data, size);
पूर्ण

अटल पूर्णांक ti_ग_लिखो_byte(काष्ठा usb_serial_port *port,
			 काष्ठा ti_device *tdev, अचिन्हित दीर्घ addr,
			 u8 mask, u8 byte)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक size;
	काष्ठा ti_ग_लिखो_data_bytes *data;

	dev_dbg(&port->dev, "%s - addr 0x%08lX, mask 0x%02X, byte 0x%02X\n", __func__,
		addr, mask, byte);

	size = माप(काष्ठा ti_ग_लिखो_data_bytes) + 2;
	data = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->bAddrType = TI_RW_DATA_ADDR_XDATA;
	data->bDataType = TI_RW_DATA_BYTE;
	data->bDataCounter = 1;
	data->wBaseAddrHi = cpu_to_be16(addr>>16);
	data->wBaseAddrLo = cpu_to_be16(addr);
	data->bData[0] = mask;
	data->bData[1] = byte;

	status = ti_command_out_sync(port->serial->dev, TI_WRITE_DATA,
			TI_RAM_PORT, 0, data, size);
	अगर (status < 0)
		dev_err(&port->dev, "%s - failed, %d\n", __func__, status);

	kमुक्त(data);

	वापस status;
पूर्ण

अटल पूर्णांक ti_करो_करोwnload(काष्ठा usb_device *dev, पूर्णांक pipe,
						u8 *buffer, पूर्णांक size)
अणु
	पूर्णांक pos;
	u8 cs = 0;
	पूर्णांक करोne;
	काष्ठा ti_firmware_header *header;
	पूर्णांक status = 0;
	पूर्णांक len;

	क्रम (pos = माप(काष्ठा ti_firmware_header); pos < size; pos++)
		cs = (u8)(cs + buffer[pos]);

	header = (काष्ठा ti_firmware_header *)buffer;
	header->wLength = cpu_to_le16(size - माप(*header));
	header->bCheckSum = cs;

	dev_dbg(&dev->dev, "%s - downloading firmware\n", __func__);
	क्रम (pos = 0; pos < size; pos += करोne) अणु
		len = min(size - pos, TI_DOWNLOAD_MAX_PACKET_SIZE);
		status = usb_bulk_msg(dev, pipe, buffer + pos, len,
								&करोne, 1000);
		अगर (status)
			अवरोध;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक ti_करोwnload_firmware(काष्ठा ti_device *tdev)
अणु
	पूर्णांक status;
	पूर्णांक buffer_size;
	u8 *buffer;
	काष्ठा usb_device *dev = tdev->td_serial->dev;
	अचिन्हित पूर्णांक pipe = usb_sndbulkpipe(dev,
		tdev->td_serial->port[0]->bulk_out_endpoपूर्णांकAddress);
	स्थिर काष्ठा firmware *fw_p;
	अक्षर buf[32];

	अगर (le16_to_cpu(dev->descriptor.idVenकरोr) == MXU1_VENDOR_ID) अणु
		snम_लिखो(buf,
			माप(buf),
			"moxa/moxa-%04x.fw",
			le16_to_cpu(dev->descriptor.idProduct));

		status = request_firmware(&fw_p, buf, &dev->dev);
		जाओ check_firmware;
	पूर्ण

	/* try ID specअगरic firmware first, then try generic firmware */
	प्र_लिखो(buf, "ti_usb-v%04x-p%04x.fw",
			le16_to_cpu(dev->descriptor.idVenकरोr),
			le16_to_cpu(dev->descriptor.idProduct));
	status = request_firmware(&fw_p, buf, &dev->dev);

	अगर (status != 0) अणु
		buf[0] = '\0';
		अगर (le16_to_cpu(dev->descriptor.idVenकरोr) == MTS_VENDOR_ID) अणु
			चयन (le16_to_cpu(dev->descriptor.idProduct)) अणु
			हाल MTS_CDMA_PRODUCT_ID:
				म_नकल(buf, "mts_cdma.fw");
				अवरोध;
			हाल MTS_GSM_PRODUCT_ID:
				म_नकल(buf, "mts_gsm.fw");
				अवरोध;
			हाल MTS_EDGE_PRODUCT_ID:
				म_नकल(buf, "mts_edge.fw");
				अवरोध;
			हाल MTS_MT9234MU_PRODUCT_ID:
				म_नकल(buf, "mts_mt9234mu.fw");
				अवरोध;
			हाल MTS_MT9234ZBA_PRODUCT_ID:
				म_नकल(buf, "mts_mt9234zba.fw");
				अवरोध;
			हाल MTS_MT9234ZBAOLD_PRODUCT_ID:
				म_नकल(buf, "mts_mt9234zba.fw");
				अवरोध;			पूर्ण
		पूर्ण
		अगर (buf[0] == '\0') अणु
			अगर (tdev->td_is_3410)
				म_नकल(buf, "ti_3410.fw");
			अन्यथा
				म_नकल(buf, "ti_5052.fw");
		पूर्ण
		status = request_firmware(&fw_p, buf, &dev->dev);
	पूर्ण

check_firmware:
	अगर (status) अणु
		dev_err(&dev->dev, "%s - firmware not found\n", __func__);
		वापस -ENOENT;
	पूर्ण
	अगर (fw_p->size > TI_FIRMWARE_BUF_SIZE) अणु
		dev_err(&dev->dev, "%s - firmware too large %zu\n", __func__, fw_p->size);
		release_firmware(fw_p);
		वापस -ENOENT;
	पूर्ण

	buffer_size = TI_FIRMWARE_BUF_SIZE + माप(काष्ठा ti_firmware_header);
	buffer = kदो_स्मृति(buffer_size, GFP_KERNEL);
	अगर (buffer) अणु
		स_नकल(buffer, fw_p->data, fw_p->size);
		स_रखो(buffer + fw_p->size, 0xff, buffer_size - fw_p->size);
		status = ti_करो_करोwnload(dev, pipe, buffer, fw_p->size);
		kमुक्त(buffer);
	पूर्ण अन्यथा अणु
		status = -ENOMEM;
	पूर्ण
	release_firmware(fw_p);
	अगर (status) अणु
		dev_err(&dev->dev, "%s - error downloading firmware, %d\n",
							__func__, status);
		वापस status;
	पूर्ण

	dev_dbg(&dev->dev, "%s - download successful\n", __func__);

	वापस 0;
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Prolअगरic PL2303 USB to serial adaptor driver
 *
 * Copyright (C) 2001-2007 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2003 IBM Corp.
 *
 * Original driver क्रम 2.2.x by anonymous
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "pl2303.h"


#घोषणा PL2303_QUIRK_UART_STATE_IDX0		BIT(0)
#घोषणा PL2303_QUIRK_LEGACY			BIT(1)
#घोषणा PL2303_QUIRK_ENDPOINT_HACK		BIT(2)

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID),
		.driver_info = PL2303_QUIRK_ENDPOINT_HACK पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_RSAQ2) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_DCU11) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_RSAQ3) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_CHILITAG) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_PHAROS) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_ALDIGA) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_MMX) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_GPRS) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_HCR331) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_MOTOROLA) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_ZTEK) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_TB) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_GC) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_GB) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_GT) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_GL) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_GE) पूर्ण,
	अणु USB_DEVICE(PL2303_VENDOR_ID, PL2303_PRODUCT_ID_GS) पूर्ण,
	अणु USB_DEVICE(IODATA_VENDOR_ID, IODATA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(IODATA_VENDOR_ID, IODATA_PRODUCT_ID_RSAQ5) पूर्ण,
	अणु USB_DEVICE(ATEN_VENDOR_ID, ATEN_PRODUCT_ID),
		.driver_info = PL2303_QUIRK_ENDPOINT_HACK पूर्ण,
	अणु USB_DEVICE(ATEN_VENDOR_ID, ATEN_PRODUCT_UC485),
		.driver_info = PL2303_QUIRK_ENDPOINT_HACK पूर्ण,
	अणु USB_DEVICE(ATEN_VENDOR_ID, ATEN_PRODUCT_UC232B),
		.driver_info = PL2303_QUIRK_ENDPOINT_HACK पूर्ण,
	अणु USB_DEVICE(ATEN_VENDOR_ID, ATEN_PRODUCT_ID2) पूर्ण,
	अणु USB_DEVICE(ATEN_VENDOR_ID2, ATEN_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ELCOM_VENDOR_ID, ELCOM_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ELCOM_VENDOR_ID, ELCOM_PRODUCT_ID_UCSGT) पूर्ण,
	अणु USB_DEVICE(ITEGNO_VENDOR_ID, ITEGNO_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ITEGNO_VENDOR_ID, ITEGNO_PRODUCT_ID_2080) पूर्ण,
	अणु USB_DEVICE(MA620_VENDOR_ID, MA620_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(RATOC_VENDOR_ID, RATOC_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(TRIPP_VENDOR_ID, TRIPP_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(RADIOSHACK_VENDOR_ID, RADIOSHACK_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(DCU10_VENDOR_ID, DCU10_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(SITECOM_VENDOR_ID, SITECOM_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ALCATEL_VENDOR_ID, ALCATEL_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(SIEMENS_VENDOR_ID, SIEMENS_PRODUCT_ID_SX1),
		.driver_info = PL2303_QUIRK_UART_STATE_IDX0 पूर्ण,
	अणु USB_DEVICE(SIEMENS_VENDOR_ID, SIEMENS_PRODUCT_ID_X65),
		.driver_info = PL2303_QUIRK_UART_STATE_IDX0 पूर्ण,
	अणु USB_DEVICE(SIEMENS_VENDOR_ID, SIEMENS_PRODUCT_ID_X75),
		.driver_info = PL2303_QUIRK_UART_STATE_IDX0 पूर्ण,
	अणु USB_DEVICE(SIEMENS_VENDOR_ID, SIEMENS_PRODUCT_ID_EF81),
		.driver_info = PL2303_QUIRK_ENDPOINT_HACK पूर्ण,
	अणु USB_DEVICE(BENQ_VENDOR_ID, BENQ_PRODUCT_ID_S81) पूर्ण, /* Benq/Siemens S81 */
	अणु USB_DEVICE(SYNTECH_VENDOR_ID, SYNTECH_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(NOKIA_CA42_VENDOR_ID, NOKIA_CA42_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(CA_42_CA42_VENDOR_ID, CA_42_CA42_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(SAGEM_VENDOR_ID, SAGEM_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(LEADTEK_VENDOR_ID, LEADTEK_9531_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(SPEEDDRAGON_VENDOR_ID, SPEEDDRAGON_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(DATAPILOT_U2_VENDOR_ID, DATAPILOT_U2_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(BELKIN_VENDOR_ID, BELKIN_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ALCOR_VENDOR_ID, ALCOR_PRODUCT_ID),
		.driver_info = PL2303_QUIRK_ENDPOINT_HACK पूर्ण,
	अणु USB_DEVICE(WS002IN_VENDOR_ID, WS002IN_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(COREGA_VENDOR_ID, COREGA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(YCCABLE_VENDOR_ID, YCCABLE_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(SUPERIAL_VENDOR_ID, SUPERIAL_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LD220_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LD220TA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LD381_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LD381GC_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LD960_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LD960TA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LCM220_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LCM960_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LM920_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_LM940_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HP_VENDOR_ID, HP_TD620_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(CRESSI_VENDOR_ID, CRESSI_EDY_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ZEAGLE_VENDOR_ID, ZEAGLE_N2ITION3_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, SONY_QN3USB_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(SANWA_VENDOR_ID, SANWA_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ADLINK_VENDOR_ID, ADLINK_ND6530_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(ADLINK_VENDOR_ID, ADLINK_ND6530GC_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(SMART_VENDOR_ID, SMART_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(AT_VENDOR_ID, AT_VTKIT3_PRODUCT_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

#घोषणा SET_LINE_REQUEST_TYPE		0x21
#घोषणा SET_LINE_REQUEST		0x20

#घोषणा SET_CONTROL_REQUEST_TYPE	0x21
#घोषणा SET_CONTROL_REQUEST		0x22
#घोषणा CONTROL_DTR			0x01
#घोषणा CONTROL_RTS			0x02

#घोषणा BREAK_REQUEST_TYPE		0x21
#घोषणा BREAK_REQUEST			0x23
#घोषणा BREAK_ON			0xffff
#घोषणा BREAK_OFF			0x0000

#घोषणा GET_LINE_REQUEST_TYPE		0xa1
#घोषणा GET_LINE_REQUEST		0x21

#घोषणा VENDOR_WRITE_REQUEST_TYPE	0x40
#घोषणा VENDOR_WRITE_REQUEST		0x01
#घोषणा VENDOR_WRITE_NREQUEST		0x80

#घोषणा VENDOR_READ_REQUEST_TYPE	0xc0
#घोषणा VENDOR_READ_REQUEST		0x01
#घोषणा VENDOR_READ_NREQUEST		0x81

#घोषणा UART_STATE_INDEX		8
#घोषणा UART_STATE_MSR_MASK		0x8b
#घोषणा UART_STATE_TRANSIENT_MASK	0x74
#घोषणा UART_DCD			0x01
#घोषणा UART_DSR			0x02
#घोषणा UART_BREAK_ERROR		0x04
#घोषणा UART_RING			0x08
#घोषणा UART_FRAME_ERROR		0x10
#घोषणा UART_PARITY_ERROR		0x20
#घोषणा UART_OVERRUN_ERROR		0x40
#घोषणा UART_CTS			0x80

#घोषणा PL2303_FLOWCTRL_MASK		0xf0

#घोषणा PL2303_READ_TYPE_HX_STATUS	0x8080

#घोषणा PL2303_HXN_RESET_REG		0x07
#घोषणा PL2303_HXN_RESET_UPSTREAM_PIPE	0x02
#घोषणा PL2303_HXN_RESET_DOWNSTREAM_PIPE	0x01

#घोषणा PL2303_HXN_FLOWCTRL_REG		0x0a
#घोषणा PL2303_HXN_FLOWCTRL_MASK	0x1c
#घोषणा PL2303_HXN_FLOWCTRL_NONE	0x1c
#घोषणा PL2303_HXN_FLOWCTRL_RTS_CTS	0x18
#घोषणा PL2303_HXN_FLOWCTRL_XON_XOFF	0x0c

अटल व्योम pl2303_set_अवरोध(काष्ठा usb_serial_port *port, bool enable);

क्रमागत pl2303_type अणु
	TYPE_H,
	TYPE_HX,
	TYPE_TA,
	TYPE_TB,
	TYPE_HXD,
	TYPE_HXN,
	TYPE_COUNT
पूर्ण;

काष्ठा pl2303_type_data अणु
	स्थिर अक्षर *name;
	speed_t max_baud_rate;
	अचिन्हित दीर्घ quirks;
	अचिन्हित पूर्णांक no_स्वतःxonxoff:1;
	अचिन्हित पूर्णांक no_भागisors:1;
	अचिन्हित पूर्णांक alt_भागisors:1;
पूर्ण;

काष्ठा pl2303_serial_निजी अणु
	स्थिर काष्ठा pl2303_type_data *type;
	अचिन्हित दीर्घ quirks;
पूर्ण;

काष्ठा pl2303_निजी अणु
	spinlock_t lock;
	u8 line_control;
	u8 line_status;

	u8 line_settings[7];
पूर्ण;

अटल स्थिर काष्ठा pl2303_type_data pl2303_type_data[TYPE_COUNT] = अणु
	[TYPE_H] = अणु
		.name			= "H",
		.max_baud_rate		= 1228800,
		.quirks			= PL2303_QUIRK_LEGACY,
		.no_स्वतःxonxoff		= true,
	पूर्ण,
	[TYPE_HX] = अणु
		.name			= "HX",
		.max_baud_rate		= 6000000,
	पूर्ण,
	[TYPE_TA] = अणु
		.name			= "TA",
		.max_baud_rate		= 6000000,
		.alt_भागisors		= true,
	पूर्ण,
	[TYPE_TB] = अणु
		.name			= "TB",
		.max_baud_rate		= 12000000,
		.alt_भागisors		= true,
	पूर्ण,
	[TYPE_HXD] = अणु
		.name			= "HXD",
		.max_baud_rate		= 12000000,
	पूर्ण,
	[TYPE_HXN] = अणु
		.name			= "G",
		.max_baud_rate		= 12000000,
		.no_भागisors		= true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक pl2303_venकरोr_पढ़ो(काष्ठा usb_serial *serial, u16 value,
							अचिन्हित अक्षर buf[1])
अणु
	काष्ठा pl2303_serial_निजी *spriv = usb_get_serial_data(serial);
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	u8 request;
	पूर्णांक res;

	अगर (spriv->type == &pl2303_type_data[TYPE_HXN])
		request = VENDOR_READ_NREQUEST;
	अन्यथा
		request = VENDOR_READ_REQUEST;

	res = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			request, VENDOR_READ_REQUEST_TYPE,
			value, 0, buf, 1, 100);
	अगर (res != 1) अणु
		dev_err(dev, "%s - failed to read [%04x]: %d\n", __func__,
								value, res);
		अगर (res >= 0)
			res = -EIO;

		वापस res;
	पूर्ण

	dev_dbg(dev, "%s - [%04x] = %02x\n", __func__, value, buf[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक pl2303_venकरोr_ग_लिखो(काष्ठा usb_serial *serial, u16 value, u16 index)
अणु
	काष्ठा pl2303_serial_निजी *spriv = usb_get_serial_data(serial);
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	u8 request;
	पूर्णांक res;

	dev_dbg(dev, "%s - [%04x] = %02x\n", __func__, value, index);

	अगर (spriv->type == &pl2303_type_data[TYPE_HXN])
		request = VENDOR_WRITE_NREQUEST;
	अन्यथा
		request = VENDOR_WRITE_REQUEST;

	res = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			request, VENDOR_WRITE_REQUEST_TYPE,
			value, index, शून्य, 0, 100);
	अगर (res) अणु
		dev_err(dev, "%s - failed to write [%04x]: %d\n", __func__,
								value, res);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pl2303_update_reg(काष्ठा usb_serial *serial, u8 reg, u8 mask, u8 val)
अणु
	काष्ठा pl2303_serial_निजी *spriv = usb_get_serial_data(serial);
	पूर्णांक ret = 0;
	u8 *buf;

	buf = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (spriv->type == &pl2303_type_data[TYPE_HXN])
		ret = pl2303_venकरोr_पढ़ो(serial, reg, buf);
	अन्यथा
		ret = pl2303_venकरोr_पढ़ो(serial, reg | 0x80, buf);

	अगर (ret)
		जाओ out_मुक्त;

	*buf &= ~mask;
	*buf |= val & mask;

	ret = pl2303_venकरोr_ग_लिखो(serial, reg, *buf);
out_मुक्त:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक pl2303_probe(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id)
अणु
	usb_set_serial_data(serial, (व्योम *)id->driver_info);

	वापस 0;
पूर्ण

/*
 * Use पूर्णांकerrupt endpoपूर्णांक from first पूर्णांकerface अगर available.
 *
 * This is needed due to the looney way its endpoपूर्णांकs are set up.
 */
अटल पूर्णांक pl2303_endpoपूर्णांक_hack(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface = serial->पूर्णांकerface;
	काष्ठा usb_device *dev = serial->dev;
	काष्ठा device *ddev = &पूर्णांकerface->dev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	अचिन्हित पूर्णांक i;

	अगर (पूर्णांकerface == dev->actconfig->पूर्णांकerface[0])
		वापस 0;

	/* check out the endpoपूर्णांकs of the other पूर्णांकerface */
	अगरace_desc = dev->actconfig->पूर्णांकerface[0]->cur_altsetting;

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
			जारी;

		dev_dbg(ddev, "found interrupt in on separate interface\n");
		अगर (epds->num_पूर्णांकerrupt_in < ARRAY_SIZE(epds->पूर्णांकerrupt_in))
			epds->पूर्णांकerrupt_in[epds->num_पूर्णांकerrupt_in++] = endpoपूर्णांक;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pl2303_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	अचिन्हित दीर्घ quirks = (अचिन्हित दीर्घ)usb_get_serial_data(serial);
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	पूर्णांक ret;

	अगर (quirks & PL2303_QUIRK_ENDPOINT_HACK) अणु
		ret = pl2303_endpoपूर्णांक_hack(serial, epds);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (epds->num_पूर्णांकerrupt_in < 1) अणु
		dev_err(dev, "required interrupt-in endpoint missing\n");
		वापस -ENODEV;
	पूर्ण

	वापस 1;
पूर्ण

अटल bool pl2303_supports_hx_status(काष्ठा usb_serial *serial)
अणु
	पूर्णांक ret;
	u8 buf;

	ret = usb_control_msg_recv(serial->dev, 0, VENDOR_READ_REQUEST,
			VENDOR_READ_REQUEST_TYPE, PL2303_READ_TYPE_HX_STATUS,
			0, &buf, 1, 100, GFP_KERNEL);

	वापस ret == 0;
पूर्ण

अटल पूर्णांक pl2303_detect_type(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_device_descriptor *desc = &serial->dev->descriptor;
	u16 bcdDevice, bcdUSB;

	/*
	 * Legacy PL2303H, variants 0 and 1 (dअगरference unknown).
	 */
	अगर (desc->bDeviceClass == 0x02)
		वापस TYPE_H;		/* variant 0 */

	अगर (desc->bMaxPacketSize0 != 0x40) अणु
		अगर (desc->bDeviceClass == 0x00 || desc->bDeviceClass == 0xff)
			वापस TYPE_H;	/* variant 1 */

		वापस TYPE_H;		/* variant 0 */
	पूर्ण

	bcdDevice = le16_to_cpu(desc->bcdDevice);
	bcdUSB = le16_to_cpu(desc->bcdUSB);

	चयन (bcdDevice) अणु
	हाल 0x100:
		/*
		 * Assume it's an HXN-type if the device doesn't support the old पढ़ो
		 * request value.
		 */
		अगर (bcdUSB == 0x200 && !pl2303_supports_hx_status(serial))
			वापस TYPE_HXN;
		अवरोध;
	हाल 0x300:
		अगर (bcdUSB == 0x200)
			वापस TYPE_TA;

		वापस TYPE_HX;
	हाल 0x400:
		वापस TYPE_HXD;
	हाल 0x500:
		वापस TYPE_TB;
	पूर्ण

	dev_err(&serial->पूर्णांकerface->dev,
			"unknown device type, please report to linux-usb@vger.kernel.org\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक pl2303_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा pl2303_serial_निजी *spriv;
	क्रमागत pl2303_type type;
	अचिन्हित अक्षर *buf;
	पूर्णांक ret;

	ret = pl2303_detect_type(serial);
	अगर (ret < 0)
		वापस ret;

	type = ret;
	dev_dbg(&serial->पूर्णांकerface->dev, "device type: %s\n", pl2303_type_data[type].name);

	spriv = kzalloc(माप(*spriv), GFP_KERNEL);
	अगर (!spriv)
		वापस -ENOMEM;

	spriv->type = &pl2303_type_data[type];
	spriv->quirks = (अचिन्हित दीर्घ)usb_get_serial_data(serial);
	spriv->quirks |= spriv->type->quirks;

	usb_set_serial_data(serial, spriv);

	अगर (type != TYPE_HXN) अणु
		buf = kदो_स्मृति(1, GFP_KERNEL);
		अगर (!buf) अणु
			kमुक्त(spriv);
			वापस -ENOMEM;
		पूर्ण

		pl2303_venकरोr_पढ़ो(serial, 0x8484, buf);
		pl2303_venकरोr_ग_लिखो(serial, 0x0404, 0);
		pl2303_venकरोr_पढ़ो(serial, 0x8484, buf);
		pl2303_venकरोr_पढ़ो(serial, 0x8383, buf);
		pl2303_venकरोr_पढ़ो(serial, 0x8484, buf);
		pl2303_venकरोr_ग_लिखो(serial, 0x0404, 1);
		pl2303_venकरोr_पढ़ो(serial, 0x8484, buf);
		pl2303_venकरोr_पढ़ो(serial, 0x8383, buf);
		pl2303_venकरोr_ग_लिखो(serial, 0, 1);
		pl2303_venकरोr_ग_लिखो(serial, 1, 0);
		अगर (spriv->quirks & PL2303_QUIRK_LEGACY)
			pl2303_venकरोr_ग_लिखो(serial, 2, 0x24);
		अन्यथा
			pl2303_venकरोr_ग_लिखो(serial, 2, 0x44);

		kमुक्त(buf);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pl2303_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा pl2303_serial_निजी *spriv = usb_get_serial_data(serial);

	kमुक्त(spriv);
पूर्ण

अटल पूर्णांक pl2303_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा pl2303_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);

	usb_set_serial_port_data(port, priv);

	port->port.drain_delay = 256;

	वापस 0;
पूर्ण

अटल व्योम pl2303_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा pl2303_निजी *priv = usb_get_serial_port_data(port);

	kमुक्त(priv);
पूर्ण

अटल पूर्णांक pl2303_set_control_lines(काष्ठा usb_serial_port *port, u8 value)
अणु
	काष्ठा usb_device *dev = port->serial->dev;
	पूर्णांक retval;

	dev_dbg(&port->dev, "%s - %02x\n", __func__, value);

	retval = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				 SET_CONTROL_REQUEST, SET_CONTROL_REQUEST_TYPE,
				 value, 0, शून्य, 0, 100);
	अगर (retval)
		dev_err(&port->dev, "%s - failed: %d\n", __func__, retval);

	वापस retval;
पूर्ण

/*
 * Returns the nearest supported baud rate that can be set directly without
 * using भागisors.
 */
अटल speed_t pl2303_get_supported_baud_rate(speed_t baud)
अणु
	अटल स्थिर speed_t baud_sup[] = अणु
		75, 150, 300, 600, 1200, 1800, 2400, 3600, 4800, 7200, 9600,
		14400, 19200, 28800, 38400, 57600, 115200, 230400, 460800,
		614400, 921600, 1228800, 2457600, 3000000, 6000000
	पूर्ण;

	अचिन्हित i;

	क्रम (i = 0; i < ARRAY_SIZE(baud_sup); ++i) अणु
		अगर (baud_sup[i] > baud)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(baud_sup))
		baud = baud_sup[i - 1];
	अन्यथा अगर (i > 0 && (baud_sup[i] - baud) > (baud - baud_sup[i - 1]))
		baud = baud_sup[i - 1];
	अन्यथा
		baud = baud_sup[i];

	वापस baud;
पूर्ण

/*
 * NOTE: If unsupported baud rates are set directly, the PL2303 seems to
 *       use 9600 baud.
 */
अटल speed_t pl2303_encode_baud_rate_direct(अचिन्हित अक्षर buf[4],
								speed_t baud)
अणु
	put_unaligned_le32(baud, buf);

	वापस baud;
पूर्ण

अटल speed_t pl2303_encode_baud_rate_भागisor(अचिन्हित अक्षर buf[4],
								speed_t baud)
अणु
	अचिन्हित पूर्णांक baseline, mantissa, exponent;

	/*
	 * Apparently the क्रमmula is:
	 *   baudrate = 12M * 32 / (mantissa * 4^exponent)
	 * where
	 *   mantissa = buf[8:0]
	 *   exponent = buf[11:9]
	 */
	baseline = 12000000 * 32;
	mantissa = baseline / baud;
	अगर (mantissa == 0)
		mantissa = 1;	/* Aव्योम भागiding by zero अगर baud > 32*12M. */
	exponent = 0;
	जबतक (mantissa >= 512) अणु
		अगर (exponent < 7) अणु
			mantissa >>= 2;	/* भागide by 4 */
			exponent++;
		पूर्ण अन्यथा अणु
			/* Exponent is maxed. Trim mantissa and leave. */
			mantissa = 511;
			अवरोध;
		पूर्ण
	पूर्ण

	buf[3] = 0x80;
	buf[2] = 0;
	buf[1] = exponent << 1 | mantissa >> 8;
	buf[0] = mantissa & 0xff;

	/* Calculate and वापस the exact baud rate. */
	baud = (baseline / mantissa) >> (exponent << 1);

	वापस baud;
पूर्ण

अटल speed_t pl2303_encode_baud_rate_भागisor_alt(अचिन्हित अक्षर buf[4],
								speed_t baud)
अणु
	अचिन्हित पूर्णांक baseline, mantissa, exponent;

	/*
	 * Apparently, क्रम the TA version the क्रमmula is:
	 *   baudrate = 12M * 32 / (mantissa * 2^exponent)
	 * where
	 *   mantissa = buf[10:0]
	 *   exponent = buf[15:13 16]
	 */
	baseline = 12000000 * 32;
	mantissa = baseline / baud;
	अगर (mantissa == 0)
		mantissa = 1;   /* Aव्योम भागiding by zero अगर baud > 32*12M. */
	exponent = 0;
	जबतक (mantissa >= 2048) अणु
		अगर (exponent < 15) अणु
			mantissa >>= 1; /* भागide by 2 */
			exponent++;
		पूर्ण अन्यथा अणु
			/* Exponent is maxed. Trim mantissa and leave. */
			mantissa = 2047;
			अवरोध;
		पूर्ण
	पूर्ण

	buf[3] = 0x80;
	buf[2] = exponent & 0x01;
	buf[1] = (exponent & ~0x01) << 4 | mantissa >> 8;
	buf[0] = mantissa & 0xff;

	/* Calculate and वापस the exact baud rate. */
	baud = (baseline / mantissa) >> exponent;

	वापस baud;
पूर्ण

अटल व्योम pl2303_encode_baud_rate(काष्ठा tty_काष्ठा *tty,
					काष्ठा usb_serial_port *port,
					u8 buf[4])
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा pl2303_serial_निजी *spriv = usb_get_serial_data(serial);
	speed_t	baud_sup;
	speed_t baud;

	baud = tty_get_baud_rate(tty);
	dev_dbg(&port->dev, "baud requested = %u\n", baud);
	अगर (!baud)
		वापस;

	अगर (spriv->type->max_baud_rate)
		baud = min_t(speed_t, baud, spriv->type->max_baud_rate);
	/*
	 * Use direct method क्रम supported baud rates, otherwise use भागisors.
	 * Newer chip types करो not support भागisor encoding.
	 */
	अगर (spriv->type->no_भागisors)
		baud_sup = baud;
	अन्यथा
		baud_sup = pl2303_get_supported_baud_rate(baud);

	अगर (baud == baud_sup)
		baud = pl2303_encode_baud_rate_direct(buf, baud);
	अन्यथा अगर (spriv->type->alt_भागisors)
		baud = pl2303_encode_baud_rate_भागisor_alt(buf, baud);
	अन्यथा
		baud = pl2303_encode_baud_rate_भागisor(buf, baud);

	/* Save resulting baud rate */
	tty_encode_baud_rate(tty, baud, baud);
	dev_dbg(&port->dev, "baud set = %u\n", baud);
पूर्ण

अटल पूर्णांक pl2303_get_line_request(काष्ठा usb_serial_port *port,
							अचिन्हित अक्षर buf[7])
अणु
	काष्ठा usb_device *udev = port->serial->dev;
	पूर्णांक ret;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				GET_LINE_REQUEST, GET_LINE_REQUEST_TYPE,
				0, 0, buf, 7, 100);
	अगर (ret != 7) अणु
		dev_err(&port->dev, "%s - failed: %d\n", __func__, ret);

		अगर (ret >= 0)
			ret = -EIO;

		वापस ret;
	पूर्ण

	dev_dbg(&port->dev, "%s - %7ph\n", __func__, buf);

	वापस 0;
पूर्ण

अटल पूर्णांक pl2303_set_line_request(काष्ठा usb_serial_port *port,
							अचिन्हित अक्षर buf[7])
अणु
	काष्ठा usb_device *udev = port->serial->dev;
	पूर्णांक ret;

	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				SET_LINE_REQUEST, SET_LINE_REQUEST_TYPE,
				0, 0, buf, 7, 100);
	अगर (ret < 0) अणु
		dev_err(&port->dev, "%s - failed: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	dev_dbg(&port->dev, "%s - %7ph\n", __func__, buf);

	वापस 0;
पूर्ण

अटल bool pl2303_termios_change(स्थिर काष्ठा ktermios *a, स्थिर काष्ठा ktermios *b)
अणु
	bool ixon_change;

	ixon_change = ((a->c_अगरlag ^ b->c_अगरlag) & (IXON | IXANY)) ||
			a->c_cc[VSTART] != b->c_cc[VSTART] ||
			a->c_cc[VSTOP] != b->c_cc[VSTOP];

	वापस tty_termios_hw_change(a, b) || ixon_change;
पूर्ण

अटल bool pl2303_enable_xonxoff(काष्ठा tty_काष्ठा *tty, स्थिर काष्ठा pl2303_type_data *type)
अणु
	अगर (!I_IXON(tty) || I_IXANY(tty))
		वापस false;

	अगर (START_CHAR(tty) != 0x11 || STOP_CHAR(tty) != 0x13)
		वापस false;

	अगर (type->no_स्वतःxonxoff)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम pl2303_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा pl2303_serial_निजी *spriv = usb_get_serial_data(serial);
	काष्ठा pl2303_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर *buf;
	पूर्णांक ret;
	u8 control;

	अगर (old_termios && !pl2303_termios_change(&tty->termios, old_termios))
		वापस;

	buf = kzalloc(7, GFP_KERNEL);
	अगर (!buf) अणु
		/* Report back no change occurred */
		अगर (old_termios)
			tty->termios = *old_termios;
		वापस;
	पूर्ण

	pl2303_get_line_request(port, buf);

	चयन (C_CSIZE(tty)) अणु
	हाल CS5:
		buf[6] = 5;
		अवरोध;
	हाल CS6:
		buf[6] = 6;
		अवरोध;
	हाल CS7:
		buf[6] = 7;
		अवरोध;
	शेष:
	हाल CS8:
		buf[6] = 8;
	पूर्ण
	dev_dbg(&port->dev, "data bits = %d\n", buf[6]);

	/* For reference buf[0]:buf[3] baud rate value */
	pl2303_encode_baud_rate(tty, port, &buf[0]);

	/* For reference buf[4]=0 is 1 stop bits */
	/* For reference buf[4]=1 is 1.5 stop bits */
	/* For reference buf[4]=2 is 2 stop bits */
	अगर (C_CSTOPB(tty)) अणु
		/*
		 * NOTE: Comply with "real" UARTs / RS232:
		 *       use 1.5 instead of 2 stop bits with 5 data bits
		 */
		अगर (C_CSIZE(tty) == CS5) अणु
			buf[4] = 1;
			dev_dbg(&port->dev, "stop bits = 1.5\n");
		पूर्ण अन्यथा अणु
			buf[4] = 2;
			dev_dbg(&port->dev, "stop bits = 2\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		buf[4] = 0;
		dev_dbg(&port->dev, "stop bits = 1\n");
	पूर्ण

	अगर (C_PARENB(tty)) अणु
		/* For reference buf[5]=0 is none parity */
		/* For reference buf[5]=1 is odd parity */
		/* For reference buf[5]=2 is even parity */
		/* For reference buf[5]=3 is mark parity */
		/* For reference buf[5]=4 is space parity */
		अगर (C_PARODD(tty)) अणु
			अगर (C_CMSPAR(tty)) अणु
				buf[5] = 3;
				dev_dbg(&port->dev, "parity = mark\n");
			पूर्ण अन्यथा अणु
				buf[5] = 1;
				dev_dbg(&port->dev, "parity = odd\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (C_CMSPAR(tty)) अणु
				buf[5] = 4;
				dev_dbg(&port->dev, "parity = space\n");
			पूर्ण अन्यथा अणु
				buf[5] = 2;
				dev_dbg(&port->dev, "parity = even\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		buf[5] = 0;
		dev_dbg(&port->dev, "parity = none\n");
	पूर्ण

	/*
	 * Some PL2303 are known to lose bytes अगर you change serial settings
	 * even to the same values as beक्रमe. Thus we actually need to filter
	 * in this specअगरic हाल.
	 *
	 * Note that the tty_termios_hw_change check above is not sufficient
	 * as a previously requested baud rate may dअगरfer from the one
	 * actually used (and stored in old_termios).
	 *
	 * NOTE: No additional locking needed क्रम line_settings as it is
	 *       only used in set_termios, which is serialised against itself.
	 */
	अगर (!old_termios || स_भेद(buf, priv->line_settings, 7)) अणु
		ret = pl2303_set_line_request(port, buf);
		अगर (!ret)
			स_नकल(priv->line_settings, buf, 7);
	पूर्ण

	/* change control lines अगर we are चयनing to or from B0 */
	spin_lock_irqsave(&priv->lock, flags);
	control = priv->line_control;
	अगर (C_BAUD(tty) == B0)
		priv->line_control &= ~(CONTROL_DTR | CONTROL_RTS);
	अन्यथा अगर (old_termios && (old_termios->c_cflag & CBAUD) == B0)
		priv->line_control |= (CONTROL_DTR | CONTROL_RTS);
	अगर (control != priv->line_control) अणु
		control = priv->line_control;
		spin_unlock_irqrestore(&priv->lock, flags);
		pl2303_set_control_lines(port, control);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण

	अगर (C_CRTSCTS(tty)) अणु
		अगर (spriv->quirks & PL2303_QUIRK_LEGACY) अणु
			pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0x40);
		पूर्ण अन्यथा अगर (spriv->type == &pl2303_type_data[TYPE_HXN]) अणु
			pl2303_update_reg(serial, PL2303_HXN_FLOWCTRL_REG,
					PL2303_HXN_FLOWCTRL_MASK,
					PL2303_HXN_FLOWCTRL_RTS_CTS);
		पूर्ण अन्यथा अणु
			pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0x60);
		पूर्ण
	पूर्ण अन्यथा अगर (pl2303_enable_xonxoff(tty, spriv->type)) अणु
		अगर (spriv->type == &pl2303_type_data[TYPE_HXN]) अणु
			pl2303_update_reg(serial, PL2303_HXN_FLOWCTRL_REG,
					PL2303_HXN_FLOWCTRL_MASK,
					PL2303_HXN_FLOWCTRL_XON_XOFF);
		पूर्ण अन्यथा अणु
			pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0xc0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (spriv->type == &pl2303_type_data[TYPE_HXN]) अणु
			pl2303_update_reg(serial, PL2303_HXN_FLOWCTRL_REG,
					PL2303_HXN_FLOWCTRL_MASK,
					PL2303_HXN_FLOWCTRL_NONE);
		पूर्ण अन्यथा अणु
			pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0);
		पूर्ण
	पूर्ण

	kमुक्त(buf);
पूर्ण

अटल व्योम pl2303_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा pl2303_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	u8 control;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (on)
		priv->line_control |= (CONTROL_DTR | CONTROL_RTS);
	अन्यथा
		priv->line_control &= ~(CONTROL_DTR | CONTROL_RTS);
	control = priv->line_control;
	spin_unlock_irqrestore(&priv->lock, flags);

	pl2303_set_control_lines(port, control);
पूर्ण

अटल व्योम pl2303_बंद(काष्ठा usb_serial_port *port)
अणु
	usb_serial_generic_बंद(port);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
	pl2303_set_अवरोध(port, false);
पूर्ण

अटल पूर्णांक pl2303_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा pl2303_serial_निजी *spriv = usb_get_serial_data(serial);
	पूर्णांक result;

	अगर (spriv->quirks & PL2303_QUIRK_LEGACY) अणु
		usb_clear_halt(serial->dev, port->ग_लिखो_urb->pipe);
		usb_clear_halt(serial->dev, port->पढ़ो_urb->pipe);
	पूर्ण अन्यथा अणु
		/* reset upstream data pipes */
		अगर (spriv->type == &pl2303_type_data[TYPE_HXN]) अणु
			pl2303_venकरोr_ग_लिखो(serial, PL2303_HXN_RESET_REG,
					PL2303_HXN_RESET_UPSTREAM_PIPE |
					PL2303_HXN_RESET_DOWNSTREAM_PIPE);
		पूर्ण अन्यथा अणु
			pl2303_venकरोr_ग_लिखो(serial, 8, 0);
			pl2303_venकरोr_ग_लिखो(serial, 9, 0);
		पूर्ण
	पूर्ण

	/* Setup termios */
	अगर (tty)
		pl2303_set_termios(tty, port, शून्य);

	result = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (result) अणु
		dev_err(&port->dev, "failed to submit interrupt urb: %d\n",
			result);
		वापस result;
	पूर्ण

	result = usb_serial_generic_खोलो(tty, port);
	अगर (result) अणु
		usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pl2303_tiocmset(काष्ठा tty_काष्ठा *tty,
			   अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा pl2303_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	u8 control;
	पूर्णांक ret;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (set & TIOCM_RTS)
		priv->line_control |= CONTROL_RTS;
	अगर (set & TIOCM_DTR)
		priv->line_control |= CONTROL_DTR;
	अगर (clear & TIOCM_RTS)
		priv->line_control &= ~CONTROL_RTS;
	अगर (clear & TIOCM_DTR)
		priv->line_control &= ~CONTROL_DTR;
	control = priv->line_control;
	spin_unlock_irqrestore(&priv->lock, flags);

	ret = pl2303_set_control_lines(port, control);
	अगर (ret)
		वापस usb_translate_errors(ret);

	वापस 0;
पूर्ण

अटल पूर्णांक pl2303_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा pl2303_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mcr;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक result;

	spin_lock_irqsave(&priv->lock, flags);
	mcr = priv->line_control;
	status = priv->line_status;
	spin_unlock_irqrestore(&priv->lock, flags);

	result = ((mcr & CONTROL_DTR)		? TIOCM_DTR : 0)
		  | ((mcr & CONTROL_RTS)	? TIOCM_RTS : 0)
		  | ((status & UART_CTS)	? TIOCM_CTS : 0)
		  | ((status & UART_DSR)	? TIOCM_DSR : 0)
		  | ((status & UART_RING)	? TIOCM_RI  : 0)
		  | ((status & UART_DCD)	? TIOCM_CD  : 0);

	dev_dbg(&port->dev, "%s - result = %x\n", __func__, result);

	वापस result;
पूर्ण

अटल पूर्णांक pl2303_carrier_उठाओd(काष्ठा usb_serial_port *port)
अणु
	काष्ठा pl2303_निजी *priv = usb_get_serial_port_data(port);

	अगर (priv->line_status & UART_DCD)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम pl2303_set_अवरोध(काष्ठा usb_serial_port *port, bool enable)
अणु
	काष्ठा usb_serial *serial = port->serial;
	u16 state;
	पूर्णांक result;

	अगर (enable)
		state = BREAK_ON;
	अन्यथा
		state = BREAK_OFF;

	dev_dbg(&port->dev, "%s - turning break %s\n", __func__,
			state == BREAK_OFF ? "off" : "on");

	result = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				 BREAK_REQUEST, BREAK_REQUEST_TYPE, state,
				 0, शून्य, 0, 100);
	अगर (result)
		dev_err(&port->dev, "error sending break = %d\n", result);
पूर्ण

अटल व्योम pl2303_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	pl2303_set_अवरोध(port, state);
पूर्ण

अटल व्योम pl2303_update_line_status(काष्ठा usb_serial_port *port,
				      अचिन्हित अक्षर *data,
				      अचिन्हित पूर्णांक actual_length)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा pl2303_serial_निजी *spriv = usb_get_serial_data(serial);
	काष्ठा pl2303_निजी *priv = usb_get_serial_port_data(port);
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status_idx = UART_STATE_INDEX;
	u8 status;
	u8 delta;

	अगर (spriv->quirks & PL2303_QUIRK_UART_STATE_IDX0)
		status_idx = 0;

	अगर (actual_length < status_idx + 1)
		वापस;

	status = data[status_idx];

	/* Save off the uart status क्रम others to look at */
	spin_lock_irqsave(&priv->lock, flags);
	delta = priv->line_status ^ status;
	priv->line_status = status;
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (status & UART_BREAK_ERROR)
		usb_serial_handle_अवरोध(port);

	अगर (delta & UART_STATE_MSR_MASK) अणु
		अगर (delta & UART_CTS)
			port->icount.cts++;
		अगर (delta & UART_DSR)
			port->icount.dsr++;
		अगर (delta & UART_RING)
			port->icount.rng++;
		अगर (delta & UART_DCD) अणु
			port->icount.dcd++;
			tty = tty_port_tty_get(&port->port);
			अगर (tty) अणु
				usb_serial_handle_dcd_change(port, tty,
							status & UART_DCD);
				tty_kref_put(tty);
			पूर्ण
		पूर्ण

		wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
	पूर्ण
पूर्ण

अटल व्योम pl2303_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port =  urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अचिन्हित पूर्णांक actual_length = urb->actual_length;
	पूर्णांक status = urb->status;
	पूर्णांक retval;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&port->dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(&port->dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		जाओ निकास;
	पूर्ण

	usb_serial_debug_data(&port->dev, __func__,
			      urb->actual_length, urb->transfer_buffer);

	pl2303_update_line_status(port, data, actual_length);

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval) अणु
		dev_err(&port->dev,
			"%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
	पूर्ण
पूर्ण

अटल व्योम pl2303_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा pl2303_निजी *priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	अक्षर tty_flag = TTY_NORMAL;
	अचिन्हित दीर्घ flags;
	u8 line_status;
	पूर्णांक i;

	/* update line status */
	spin_lock_irqsave(&priv->lock, flags);
	line_status = priv->line_status;
	priv->line_status &= ~UART_STATE_TRANSIENT_MASK;
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (!urb->actual_length)
		वापस;

	/*
	 * Break takes precedence over parity, which takes precedence over
	 * framing errors.
	 */
	अगर (line_status & UART_BREAK_ERROR)
		tty_flag = TTY_BREAK;
	अन्यथा अगर (line_status & UART_PARITY_ERROR)
		tty_flag = TTY_PARITY;
	अन्यथा अगर (line_status & UART_FRAME_ERROR)
		tty_flag = TTY_FRAME;

	अगर (tty_flag != TTY_NORMAL)
		dev_dbg(&port->dev, "%s - tty_flag = %d\n", __func__,
								tty_flag);
	/* overrun is special, not associated with a अक्षर */
	अगर (line_status & UART_OVERRUN_ERROR)
		tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN);

	अगर (port->sysrq) अणु
		क्रम (i = 0; i < urb->actual_length; ++i)
			अगर (!usb_serial_handle_sysrq_अक्षर(port, data[i]))
				tty_insert_flip_अक्षर(&port->port, data[i],
						tty_flag);
	पूर्ण अन्यथा अणु
		tty_insert_flip_string_fixed_flag(&port->port, data, tty_flag,
							urb->actual_length);
	पूर्ण

	tty_flip_buffer_push(&port->port);
पूर्ण

अटल काष्ठा usb_serial_driver pl2303_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"pl2303",
	पूर्ण,
	.id_table =		id_table,
	.num_bulk_in =		1,
	.num_bulk_out =		1,
	.num_पूर्णांकerrupt_in =	0,	/* see pl2303_calc_num_ports */
	.bulk_in_size =		256,
	.bulk_out_size =	256,
	.खोलो =			pl2303_खोलो,
	.बंद =		pl2303_बंद,
	.dtr_rts =		pl2303_dtr_rts,
	.carrier_उठाओd =	pl2303_carrier_उठाओd,
	.अवरोध_ctl =		pl2303_अवरोध_ctl,
	.set_termios =		pl2303_set_termios,
	.tiocmget =		pl2303_tiocmget,
	.tiocmset =		pl2303_tiocmset,
	.tiocmiरुको =		usb_serial_generic_tiocmiरुको,
	.process_पढ़ो_urb =	pl2303_process_पढ़ो_urb,
	.पढ़ो_पूर्णांक_callback =	pl2303_पढ़ो_पूर्णांक_callback,
	.probe =		pl2303_probe,
	.calc_num_ports =	pl2303_calc_num_ports,
	.attach =		pl2303_startup,
	.release =		pl2303_release,
	.port_probe =		pl2303_port_probe,
	.port_हटाओ =		pl2303_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&pl2303_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION("Prolific PL2303 USB to serial adaptor driver");
MODULE_LICENSE("GPL v2");

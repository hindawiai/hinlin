<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
  Keyspan USB to Serial Converter driver

  (C) Copyright (C) 2000-2001	Hugh Blemings <hugh@blemings.org>
  (C) Copyright (C) 2002	Greg Kroah-Harपंचांगan <greg@kroah.com>

  See http://blemings.org/hugh/keyspan.hपंचांगl क्रम more inक्रमmation.

  Code in this driver inspired by and in a number of places taken
  from Brian Warner's original Keyspan-PDA driver.

  This driver has been put together with the support of Innosys, Inc.
  and Keyspan, Inc the manufacturers of the Keyspan USB-serial products.
  Thanks Guys :)

  Thanks to Paulus क्रम miscellaneous tidy ups, some largish chunks
  of much nicer and/or completely new code and (perhaps most uniquely)
  having the patience to sit करोwn and explain why and where he'd changed
  stuff.

  Tip 'o the hat to IBM (and previously Linuxcare :) क्रम supporting
  staff in their work on खोलो source projects.
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
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/usb/ezusb.h>

#घोषणा DRIVER_AUTHOR "Hugh Blemings <hugh@misc.nu"
#घोषणा DRIVER_DESC "Keyspan USB to Serial Converter Driver"

अटल व्योम keyspan_send_setup(काष्ठा usb_serial_port *port, पूर्णांक reset_port);

अटल पूर्णांक keyspan_usa19_calc_baud(काष्ठा usb_serial_port *port,
				   u32 baud_rate, u32 baudclk,
				   u8 *rate_hi, u8 *rate_low,
				   u8 *prescaler, पूर्णांक portnum);
अटल पूर्णांक keyspan_usa19w_calc_baud(काष्ठा usb_serial_port *port,
				    u32 baud_rate, u32 baudclk,
				    u8 *rate_hi, u8 *rate_low,
				    u8 *prescaler, पूर्णांक portnum);
अटल पूर्णांक keyspan_usa28_calc_baud(काष्ठा usb_serial_port *port,
				   u32 baud_rate, u32 baudclk,
				   u8 *rate_hi, u8 *rate_low,
				   u8 *prescaler, पूर्णांक portnum);
अटल पूर्णांक keyspan_usa19hs_calc_baud(काष्ठा usb_serial_port *port,
				     u32 baud_rate, u32 baudclk,
				     u8 *rate_hi, u8 *rate_low,
				     u8 *prescaler, पूर्णांक portnum);

अटल पूर्णांक keyspan_usa28_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port);
अटल पूर्णांक keyspan_usa26_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port);
अटल पूर्णांक keyspan_usa49_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port);
अटल पूर्णांक keyspan_usa90_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port);
अटल पूर्णांक keyspan_usa67_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port);

/* Values used क्रम baud rate calculation - device specअगरic */
#घोषणा KEYSPAN_INVALID_BAUD_RATE		(-1)
#घोषणा KEYSPAN_BAUD_RATE_OK			(0)
#घोषणा KEYSPAN_USA18X_BAUDCLK			(12000000L)	/* a guess */
#घोषणा KEYSPAN_USA19_BAUDCLK			(12000000L)
#घोषणा KEYSPAN_USA19W_BAUDCLK			(24000000L)
#घोषणा KEYSPAN_USA19HS_BAUDCLK			(14769231L)
#घोषणा KEYSPAN_USA28_BAUDCLK			(1843200L)
#घोषणा KEYSPAN_USA28X_BAUDCLK			(12000000L)
#घोषणा KEYSPAN_USA49W_BAUDCLK			(48000000L)

/* Some स्थिरants used to अक्षरacterise each device.  */
#घोषणा KEYSPAN_MAX_NUM_PORTS			(4)
#घोषणा KEYSPAN_MAX_FLIPS			(2)

/*
 * Device info क्रम the Keyspan serial converter, used by the overall
 * usb-serial probe function.
 */
#घोषणा KEYSPAN_VENDOR_ID			(0x06cd)

/* Product IDs क्रम the products supported, pre-rक्रमागतeration */
#घोषणा keyspan_usa18x_pre_product_id		0x0105
#घोषणा keyspan_usa19_pre_product_id		0x0103
#घोषणा keyspan_usa19qi_pre_product_id		0x010b
#घोषणा keyspan_mpr_pre_product_id		0x011b
#घोषणा keyspan_usa19qw_pre_product_id		0x0118
#घोषणा keyspan_usa19w_pre_product_id		0x0106
#घोषणा keyspan_usa28_pre_product_id		0x0101
#घोषणा keyspan_usa28x_pre_product_id		0x0102
#घोषणा keyspan_usa28xa_pre_product_id		0x0114
#घोषणा keyspan_usa28xb_pre_product_id		0x0113
#घोषणा keyspan_usa49w_pre_product_id		0x0109
#घोषणा keyspan_usa49wlc_pre_product_id		0x011a

/*
 * Product IDs post-rक्रमागतeration.  Note that the 28x and 28xb have the same
 * id's post-renumeration but behave identically so it's not an issue. As
 * such, the 28xb is not listed in any of the device tables.
 */
#घोषणा keyspan_usa18x_product_id		0x0112
#घोषणा keyspan_usa19_product_id		0x0107
#घोषणा keyspan_usa19qi_product_id		0x010c
#घोषणा keyspan_usa19hs_product_id		0x0121
#घोषणा keyspan_mpr_product_id			0x011c
#घोषणा keyspan_usa19qw_product_id		0x0119
#घोषणा keyspan_usa19w_product_id		0x0108
#घोषणा keyspan_usa28_product_id		0x010f
#घोषणा keyspan_usa28x_product_id		0x0110
#घोषणा keyspan_usa28xa_product_id		0x0115
#घोषणा keyspan_usa28xb_product_id		0x0110
#घोषणा keyspan_usa28xg_product_id		0x0135
#घोषणा keyspan_usa49w_product_id		0x010a
#घोषणा keyspan_usa49wlc_product_id		0x012a
#घोषणा keyspan_usa49wg_product_id		0x0131

काष्ठा keyspan_device_details अणु
	/* product ID value */
	पूर्णांक	product_id;

	क्रमागत	अणुmsg_usa26, msg_usa28, msg_usa49, msg_usa90, msg_usa67पूर्ण msg_क्रमmat;

		/* Number of physical ports */
	पूर्णांक	num_ports;

		/* 1 अगर endpoपूर्णांक flipping used on input, 0 अगर not */
	पूर्णांक	indat_endp_flip;

		/* 1 अगर endpoपूर्णांक flipping used on output, 0 अगर not */
	पूर्णांक	outdat_endp_flip;

		/*
		 * Table mapping input data endpoपूर्णांक IDs to physical port
		 * number and flip अगर used
		 */
	पूर्णांक	indat_endpoपूर्णांकs[KEYSPAN_MAX_NUM_PORTS];

		/* Same क्रम output endpoपूर्णांकs */
	पूर्णांक	outdat_endpoपूर्णांकs[KEYSPAN_MAX_NUM_PORTS];

		/* Input acknowledge endpoपूर्णांकs */
	पूर्णांक	inack_endpoपूर्णांकs[KEYSPAN_MAX_NUM_PORTS];

		/* Output control endpoपूर्णांकs */
	पूर्णांक	outcont_endpoपूर्णांकs[KEYSPAN_MAX_NUM_PORTS];

		/* Endpoपूर्णांक used क्रम input status */
	पूर्णांक	instat_endpoपूर्णांक;

		/* Endpoपूर्णांक used क्रम input data 49WG only */
	पूर्णांक	indat_endpoपूर्णांक;

		/* Endpoपूर्णांक used क्रम global control functions */
	पूर्णांक	glocont_endpoपूर्णांक;

	पूर्णांक	(*calculate_baud_rate)(काष्ठा usb_serial_port *port,
				       u32 baud_rate, u32 baudclk,
				       u8 *rate_hi, u8 *rate_low, u8 *prescaler,
				       पूर्णांक portnum);
	u32	baudclk;
पूर्ण;

/*
 * Now क्रम each device type we setup the device detail काष्ठाure with the
 * appropriate inक्रमmation (provided in Keyspan's करोcumentation)
 */

अटल स्थिर काष्ठा keyspan_device_details usa18x_device_details = अणु
	.product_id		= keyspan_usa18x_product_id,
	.msg_क्रमmat		= msg_usa26,
	.num_ports		= 1,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x85पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x05पूर्ण,
	.instat_endpoपूर्णांक	= 0x87,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x07,
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA18X_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa19_device_details = अणु
	.product_id		= keyspan_usa19_product_id,
	.msg_क्रमmat		= msg_usa28,
	.num_ports		= 1,
	.indat_endp_flip	= 1,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x83पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x03पूर्ण,
	.instat_endpoपूर्णांक	= 0x84,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= -1,
	.calculate_baud_rate	= keyspan_usa19_calc_baud,
	.baudclk		= KEYSPAN_USA19_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa19qi_device_details = अणु
	.product_id		= keyspan_usa19qi_product_id,
	.msg_क्रमmat		= msg_usa28,
	.num_ports		= 1,
	.indat_endp_flip	= 1,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x83पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x03पूर्ण,
	.instat_endpoपूर्णांक	= 0x84,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= -1,
	.calculate_baud_rate	= keyspan_usa28_calc_baud,
	.baudclk		= KEYSPAN_USA19_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details mpr_device_details = अणु
	.product_id		= keyspan_mpr_product_id,
	.msg_क्रमmat		= msg_usa28,
	.num_ports		= 1,
	.indat_endp_flip	= 1,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x83पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x03पूर्ण,
	.instat_endpoपूर्णांक	= 0x84,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= -1,
	.calculate_baud_rate	= keyspan_usa28_calc_baud,
	.baudclk		= KEYSPAN_USA19_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa19qw_device_details = अणु
	.product_id		= keyspan_usa19qw_product_id,
	.msg_क्रमmat		= msg_usa26,
	.num_ports		= 1,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x85पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x05पूर्ण,
	.instat_endpoपूर्णांक	= 0x87,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x07,
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA19W_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa19w_device_details = अणु
	.product_id		= keyspan_usa19w_product_id,
	.msg_क्रमmat		= msg_usa26,
	.num_ports		= 1,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x85पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x05पूर्ण,
	.instat_endpoपूर्णांक	= 0x87,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x07,
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA19W_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa19hs_device_details = अणु
	.product_id		= keyspan_usa19hs_product_id,
	.msg_क्रमmat		= msg_usa90,
	.num_ports		= 1,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 0,
	.indat_endpoपूर्णांकs	= अणु0x81पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01पूर्ण,
	.inack_endpoपूर्णांकs	= अणु-1पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x02पूर्ण,
	.instat_endpoपूर्णांक	= 0x82,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= -1,
	.calculate_baud_rate	= keyspan_usa19hs_calc_baud,
	.baudclk		= KEYSPAN_USA19HS_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa28_device_details = अणु
	.product_id		= keyspan_usa28_product_id,
	.msg_क्रमmat		= msg_usa28,
	.num_ports		= 2,
	.indat_endp_flip	= 1,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81, 0x83पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01, 0x03पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x85, 0x86पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x05, 0x06पूर्ण,
	.instat_endpoपूर्णांक	= 0x87,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x07,
	.calculate_baud_rate	= keyspan_usa28_calc_baud,
	.baudclk		= KEYSPAN_USA28_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa28x_device_details = अणु
	.product_id		= keyspan_usa28x_product_id,
	.msg_क्रमmat		= msg_usa26,
	.num_ports		= 2,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81, 0x83पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01, 0x03पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x85, 0x86पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x05, 0x06पूर्ण,
	.instat_endpoपूर्णांक	= 0x87,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x07,
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA28X_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa28xa_device_details = अणु
	.product_id		= keyspan_usa28xa_product_id,
	.msg_क्रमmat		= msg_usa26,
	.num_ports		= 2,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 1,
	.indat_endpoपूर्णांकs	= अणु0x81, 0x83पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01, 0x03पूर्ण,
	.inack_endpoपूर्णांकs	= अणु0x85, 0x86पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु0x05, 0x06पूर्ण,
	.instat_endpoपूर्णांक	= 0x87,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x07,
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA28X_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa28xg_device_details = अणु
	.product_id		= keyspan_usa28xg_product_id,
	.msg_क्रमmat		= msg_usa67,
	.num_ports		= 2,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 0,
	.indat_endpoपूर्णांकs	= अणु0x84, 0x88पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x02, 0x06पूर्ण,
	.inack_endpoपूर्णांकs	= अणु-1, -1पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु-1, -1पूर्ण,
	.instat_endpoपूर्णांक	= 0x81,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x01,
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA28X_BAUDCLK,
पूर्ण;
/*
 * We करोn't need a separate entry क्रम the usa28xb as it appears as a 28x
 * anyway.
 */

अटल स्थिर काष्ठा keyspan_device_details usa49w_device_details = अणु
	.product_id		= keyspan_usa49w_product_id,
	.msg_क्रमmat		= msg_usa49,
	.num_ports		= 4,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 0,
	.indat_endpoपूर्णांकs	= अणु0x81, 0x82, 0x83, 0x84पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01, 0x02, 0x03, 0x04पूर्ण,
	.inack_endpoपूर्णांकs	= अणु-1, -1, -1, -1पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु-1, -1, -1, -1पूर्ण,
	.instat_endpoपूर्णांक	= 0x87,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x07,
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA49W_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa49wlc_device_details = अणु
	.product_id		= keyspan_usa49wlc_product_id,
	.msg_क्रमmat		= msg_usa49,
	.num_ports		= 4,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 0,
	.indat_endpoपूर्णांकs	= अणु0x81, 0x82, 0x83, 0x84पूर्ण,
	.outdat_endpoपूर्णांकs	= अणु0x01, 0x02, 0x03, 0x04पूर्ण,
	.inack_endpoपूर्णांकs	= अणु-1, -1, -1, -1पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु-1, -1, -1, -1पूर्ण,
	.instat_endpoपूर्णांक	= 0x87,
	.indat_endpoपूर्णांक		= -1,
	.glocont_endpoपूर्णांक	= 0x07,
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA19W_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details usa49wg_device_details = अणु
	.product_id		= keyspan_usa49wg_product_id,
	.msg_क्रमmat		= msg_usa49,
	.num_ports		= 4,
	.indat_endp_flip	= 0,
	.outdat_endp_flip	= 0,
	.indat_endpoपूर्णांकs	= अणु-1, -1, -1, -1पूर्ण,	/* single 'global' data in EP */
	.outdat_endpoपूर्णांकs	= अणु0x01, 0x02, 0x04, 0x06पूर्ण,
	.inack_endpoपूर्णांकs	= अणु-1, -1, -1, -1पूर्ण,
	.outcont_endpoपूर्णांकs	= अणु-1, -1, -1, -1पूर्ण,
	.instat_endpoपूर्णांक	= 0x81,
	.indat_endpoपूर्णांक		= 0x88,
	.glocont_endpoपूर्णांक	= 0x00,			/* uses control EP */
	.calculate_baud_rate	= keyspan_usa19w_calc_baud,
	.baudclk		= KEYSPAN_USA19W_BAUDCLK,
पूर्ण;

अटल स्थिर काष्ठा keyspan_device_details *keyspan_devices[] = अणु
	&usa18x_device_details,
	&usa19_device_details,
	&usa19qi_device_details,
	&mpr_device_details,
	&usa19qw_device_details,
	&usa19w_device_details,
	&usa19hs_device_details,
	&usa28_device_details,
	&usa28x_device_details,
	&usa28xa_device_details,
	&usa28xg_device_details,
	/* 28xb not required as it rक्रमागतerates as a 28x */
	&usa49w_device_details,
	&usa49wlc_device_details,
	&usa49wg_device_details,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id keyspan_ids_combined[] = अणु
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa18x_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19w_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19qi_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19qw_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_mpr_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28x_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28xa_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28xb_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49w_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49wlc_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa18x_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19w_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19qi_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19qw_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19hs_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_mpr_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28x_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28xa_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28xg_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49w_product_id)पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49wlc_product_id)पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49wg_product_id)पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, keyspan_ids_combined);

/* usb_device_id table क्रम the pre-firmware करोwnload keyspan devices */
अटल स्थिर काष्ठा usb_device_id keyspan_pre_ids[] = अणु
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa18x_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19qi_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19qw_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19w_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_mpr_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28x_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28xa_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28xb_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49w_pre_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49wlc_pre_product_id) पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id keyspan_1port_ids[] = अणु
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa18x_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19qi_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19qw_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19w_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa19hs_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_mpr_product_id) पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id keyspan_2port_ids[] = अणु
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28x_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28xa_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa28xg_product_id) पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id keyspan_4port_ids[] = अणु
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49w_product_id) पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49wlc_product_id)पूर्ण,
	अणु USB_DEVICE(KEYSPAN_VENDOR_ID, keyspan_usa49wg_product_id)पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

#घोषणा INSTAT_BUFLEN	32
#घोषणा GLOCONT_BUFLEN	64
#घोषणा INDAT49W_BUFLEN	512
#घोषणा IN_BUFLEN	64
#घोषणा OUT_BUFLEN	64
#घोषणा INACK_BUFLEN	1
#घोषणा OUTCONT_BUFLEN	64

	/* Per device and per port निजी data */
काष्ठा keyspan_serial_निजी अणु
	स्थिर काष्ठा keyspan_device_details	*device_details;

	काष्ठा urb	*instat_urb;
	अक्षर		*instat_buf;

	/* added to support 49wg, where data from all 4 ports comes in
	   on 1 EP and high-speed supported */
	काष्ठा urb	*indat_urb;
	अक्षर		*indat_buf;

	/* XXX this one probably will need a lock */
	काष्ठा urb	*glocont_urb;
	अक्षर		*glocont_buf;
	अक्षर		*ctrl_buf;	/* क्रम EP0 control message */
पूर्ण;

काष्ठा keyspan_port_निजी अणु
	/* Keep track of which input & output endpoपूर्णांकs to use */
	पूर्णांक		in_flip;
	पूर्णांक		out_flip;

	/* Keep duplicate of device details in each port
	   काष्ठाure as well - simplअगरies some of the
	   callback functions etc. */
	स्थिर काष्ठा keyspan_device_details	*device_details;

	/* Input endpoपूर्णांकs and buffer क्रम this port */
	काष्ठा urb	*in_urbs[2];
	अक्षर		*in_buffer[2];
	/* Output endpoपूर्णांकs and buffer क्रम this port */
	काष्ठा urb	*out_urbs[2];
	अक्षर		*out_buffer[2];

	/* Input ack endpoपूर्णांक */
	काष्ठा urb	*inack_urb;
	अक्षर		*inack_buffer;

	/* Output control endpoपूर्णांक */
	काष्ठा urb	*outcont_urb;
	अक्षर		*outcont_buffer;

	/* Settings क्रम the port */
	पूर्णांक		baud;
	पूर्णांक		old_baud;
	अचिन्हित पूर्णांक	cflag;
	अचिन्हित पूर्णांक	old_cflag;
	क्रमागत		अणुflow_none, flow_cts, flow_xonपूर्ण flow_control;
	पूर्णांक		rts_state;	/* Handshaking pins (outमाला_दो) */
	पूर्णांक		dtr_state;
	पूर्णांक		cts_state;	/* Handshaking pins (inमाला_दो) */
	पूर्णांक		dsr_state;
	पूर्णांक		dcd_state;
	पूर्णांक		ri_state;
	पूर्णांक		अवरोध_on;

	अचिन्हित दीर्घ	tx_start_समय[2];
	पूर्णांक		resend_cont;	/* need to resend control packet */
पूर्ण;

/* Include Keyspan message headers.  All current Keyspan Adapters
   make use of one of five message क्रमmats which are referred
   to as USA-26, USA-28, USA-49, USA-90, USA-67 by Keyspan and
   within this driver. */
#समावेश "keyspan_usa26msg.h"
#समावेश "keyspan_usa28msg.h"
#समावेश "keyspan_usa49msg.h"
#समावेश "keyspan_usa90msg.h"
#समावेश "keyspan_usa67msg.h"


अटल व्योम keyspan_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा keyspan_port_निजी 	*p_priv;

	p_priv = usb_get_serial_port_data(port);

	अगर (अवरोध_state == -1)
		p_priv->अवरोध_on = 1;
	अन्यथा
		p_priv->अवरोध_on = 0;

	keyspan_send_setup(port, 0);
पूर्ण


अटल व्योम keyspan_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	पूर्णांक				baud_rate, device_port;
	काष्ठा keyspan_port_निजी 	*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	अचिन्हित पूर्णांक 			cflag;

	p_priv = usb_get_serial_port_data(port);
	d_details = p_priv->device_details;
	cflag = tty->termios.c_cflag;
	device_port = port->port_number;

	/* Baud rate calculation takes baud rate as an पूर्णांकeger
	   so other rates can be generated अगर desired. */
	baud_rate = tty_get_baud_rate(tty);
	/* If no match or invalid, करोn't change */
	अगर (d_details->calculate_baud_rate(port, baud_rate, d_details->baudclk,
				शून्य, शून्य, शून्य, device_port) == KEYSPAN_BAUD_RATE_OK) अणु
		/* FIXME - more to करो here to ensure rate changes cleanly */
		/* FIXME - calculate exact rate from भागisor ? */
		p_priv->baud = baud_rate;
	पूर्ण अन्यथा
		baud_rate = tty_termios_baud_rate(old_termios);

	tty_encode_baud_rate(tty, baud_rate, baud_rate);
	/* set CTS/RTS handshake etc. */
	p_priv->cflag = cflag;
	p_priv->flow_control = (cflag & CRTSCTS) ? flow_cts : flow_none;

	/* Mark/Space not supported */
	tty->termios.c_cflag &= ~CMSPAR;

	keyspan_send_setup(port, 0);
पूर्ण

अटल पूर्णांक keyspan_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा keyspan_port_निजी *p_priv = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक			value;

	value = ((p_priv->rts_state) ? TIOCM_RTS : 0) |
		((p_priv->dtr_state) ? TIOCM_DTR : 0) |
		((p_priv->cts_state) ? TIOCM_CTS : 0) |
		((p_priv->dsr_state) ? TIOCM_DSR : 0) |
		((p_priv->dcd_state) ? TIOCM_CAR : 0) |
		((p_priv->ri_state) ? TIOCM_RNG : 0);

	वापस value;
पूर्ण

अटल पूर्णांक keyspan_tiocmset(काष्ठा tty_काष्ठा *tty,
			    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा keyspan_port_निजी *p_priv = usb_get_serial_port_data(port);

	अगर (set & TIOCM_RTS)
		p_priv->rts_state = 1;
	अगर (set & TIOCM_DTR)
		p_priv->dtr_state = 1;
	अगर (clear & TIOCM_RTS)
		p_priv->rts_state = 0;
	अगर (clear & TIOCM_DTR)
		p_priv->dtr_state = 0;
	keyspan_send_setup(port, 0);
	वापस 0;
पूर्ण

/* Write function is similar क्रम the four protocols used
   with only a minor change क्रम usa90 (usa19hs) required */
अटल पूर्णांक keyspan_ग_लिखो(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा keyspan_port_निजी 	*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	पूर्णांक				flip;
	पूर्णांक 				left, toकरो;
	काष्ठा urb			*this_urb;
	पूर्णांक 				err, maxDataLen, dataOffset;

	p_priv = usb_get_serial_port_data(port);
	d_details = p_priv->device_details;

	अगर (d_details->msg_क्रमmat == msg_usa90) अणु
		maxDataLen = 64;
		dataOffset = 0;
	पूर्ण अन्यथा अणु
		maxDataLen = 63;
		dataOffset = 1;
	पूर्ण

	dev_dbg(&port->dev, "%s - %d chars, flip=%d\n", __func__, count,
		p_priv->out_flip);

	क्रम (left = count; left > 0; left -= toकरो) अणु
		toकरो = left;
		अगर (toकरो > maxDataLen)
			toकरो = maxDataLen;

		flip = p_priv->out_flip;

		/* Check we have a valid urb/endpoपूर्णांक beक्रमe we use it... */
		this_urb = p_priv->out_urbs[flip];
		अगर (this_urb == शून्य) अणु
			/* no bulk out, so वापस 0 bytes written */
			dev_dbg(&port->dev, "%s - no output urb :(\n", __func__);
			वापस count;
		पूर्ण

		dev_dbg(&port->dev, "%s - endpoint %x flip %d\n",
			__func__, usb_pipeendpoपूर्णांक(this_urb->pipe), flip);

		अगर (this_urb->status == -EINPROGRESS) अणु
			अगर (समय_beक्रमe(jअगरfies,
					p_priv->tx_start_समय[flip] + 10 * HZ))
				अवरोध;
			usb_unlink_urb(this_urb);
			अवरोध;
		पूर्ण

		/* First byte in buffer is "last flag" (except क्रम usa19hx)
		   - unused so क्रम now so set to zero */
		((अक्षर *)this_urb->transfer_buffer)[0] = 0;

		स_नकल(this_urb->transfer_buffer + dataOffset, buf, toकरो);
		buf += toकरो;

		/* send the data out the bulk port */
		this_urb->transfer_buffer_length = toकरो + dataOffset;

		err = usb_submit_urb(this_urb, GFP_ATOMIC);
		अगर (err != 0)
			dev_dbg(&port->dev, "usb_submit_urb(write bulk) failed (%d)\n", err);
		p_priv->tx_start_समय[flip] = jअगरfies;

		/* Flip क्रम next समय अगर usa26 or usa28 पूर्णांकerface
		   (not used on usa49) */
		p_priv->out_flip = (flip + 1) & d_details->outdat_endp_flip;
	पूर्ण

	वापस count - left;
पूर्ण

अटल व्योम	usa26_indat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक			i, err;
	पूर्णांक			endpoपूर्णांक;
	काष्ठा usb_serial_port	*port;
	अचिन्हित अक्षर 		*data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	endpoपूर्णांक = usb_pipeendpoपूर्णांक(urb->pipe);

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status %d on endpoint %x\n",
			__func__, status, endpoपूर्णांक);
		वापस;
	पूर्ण

	port =  urb->context;
	अगर (urb->actual_length) अणु
		/* 0x80 bit is error flag */
		अगर ((data[0] & 0x80) == 0) अणु
			/* no errors on inभागidual bytes, only
			   possible overrun err */
			अगर (data[0] & RXERROR_OVERRUN) अणु
				tty_insert_flip_अक्षर(&port->port, 0,
								TTY_OVERRUN);
			पूर्ण
			क्रम (i = 1; i < urb->actual_length ; ++i)
				tty_insert_flip_अक्षर(&port->port, data[i],
								TTY_NORMAL);
		पूर्ण अन्यथा अणु
			/* some bytes had errors, every byte has status */
			dev_dbg(&port->dev, "%s - RX error!!!!\n", __func__);
			क्रम (i = 0; i + 1 < urb->actual_length; i += 2) अणु
				पूर्णांक stat = data[i];
				पूर्णांक flag = TTY_NORMAL;

				अगर (stat & RXERROR_OVERRUN) अणु
					tty_insert_flip_अक्षर(&port->port, 0,
								TTY_OVERRUN);
				पूर्ण
				/* XXX should handle अवरोध (0x10) */
				अगर (stat & RXERROR_PARITY)
					flag = TTY_PARITY;
				अन्यथा अगर (stat & RXERROR_FRAMING)
					flag = TTY_FRAME;

				tty_insert_flip_अक्षर(&port->port, data[i+1],
						flag);
			पूर्ण
		पूर्ण
		tty_flip_buffer_push(&port->port);
	पूर्ण

	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
पूर्ण

/* Outdat handling is common क्रम all devices */
अटल व्योम	usa2x_outdat_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा keyspan_port_निजी *p_priv;

	port =  urb->context;
	p_priv = usb_get_serial_port_data(port);
	dev_dbg(&port->dev, "%s - urb %d\n", __func__, urb == p_priv->out_urbs[1]);

	usb_serial_port_softपूर्णांक(port);
पूर्ण

अटल व्योम	usa26_inack_callback(काष्ठा urb *urb)
अणु
पूर्ण

अटल व्योम	usa26_outcont_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा keyspan_port_निजी *p_priv;

	port =  urb->context;
	p_priv = usb_get_serial_port_data(port);

	अगर (p_priv->resend_cont) अणु
		dev_dbg(&port->dev, "%s - sending setup\n", __func__);
		keyspan_usa26_send_setup(port->serial, port,
						p_priv->resend_cont - 1);
	पूर्ण
पूर्ण

अटल व्योम	usa26_instat_callback(काष्ठा urb *urb)
अणु
	अचिन्हित अक्षर 				*data = urb->transfer_buffer;
	काष्ठा keyspan_usa26_portStatusMessage	*msg;
	काष्ठा usb_serial			*serial;
	काष्ठा usb_serial_port			*port;
	काष्ठा keyspan_port_निजी	 	*p_priv;
	पूर्णांक old_dcd_state, err;
	पूर्णांक status = urb->status;

	serial =  urb->context;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status: %d\n",
				__func__, status);
		वापस;
	पूर्ण
	अगर (urb->actual_length != 9) अणु
		dev_dbg(&urb->dev->dev, "%s - %d byte report??\n", __func__, urb->actual_length);
		जाओ निकास;
	पूर्ण

	msg = (काष्ठा keyspan_usa26_portStatusMessage *)data;

	/* Check port number from message and retrieve निजी data */
	अगर (msg->port >= serial->num_ports) अणु
		dev_dbg(&urb->dev->dev, "%s - Unexpected port number %d\n", __func__, msg->port);
		जाओ निकास;
	पूर्ण
	port = serial->port[msg->port];
	p_priv = usb_get_serial_port_data(port);
	अगर (!p_priv)
		जाओ resubmit;

	/* Update handshaking pin state inक्रमmation */
	old_dcd_state = p_priv->dcd_state;
	p_priv->cts_state = ((msg->hskia_cts) ? 1 : 0);
	p_priv->dsr_state = ((msg->dsr) ? 1 : 0);
	p_priv->dcd_state = ((msg->gpia_dcd) ? 1 : 0);
	p_priv->ri_state = ((msg->ri) ? 1 : 0);

	अगर (old_dcd_state != p_priv->dcd_state)
		tty_port_tty_hangup(&port->port, true);
resubmit:
	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
निकास: ;
पूर्ण

अटल व्योम	usa26_glocont_callback(काष्ठा urb *urb)
अणु
पूर्ण


अटल व्योम usa28_indat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक                     err;
	काष्ठा usb_serial_port  *port;
	अचिन्हित अक्षर           *data;
	काष्ठा keyspan_port_निजी             *p_priv;
	पूर्णांक status = urb->status;

	port =  urb->context;
	p_priv = usb_get_serial_port_data(port);
	data = urb->transfer_buffer;

	अगर (urb != p_priv->in_urbs[p_priv->in_flip])
		वापस;

	करो अणु
		अगर (status) अणु
			dev_dbg(&urb->dev->dev, "%s - nonzero status %d on endpoint %x\n",
				__func__, status, usb_pipeendpoपूर्णांक(urb->pipe));
			वापस;
		पूर्ण

		port =  urb->context;
		p_priv = usb_get_serial_port_data(port);
		data = urb->transfer_buffer;

		अगर (urb->actual_length) अणु
			tty_insert_flip_string(&port->port, data,
					urb->actual_length);
			tty_flip_buffer_push(&port->port);
		पूर्ण

		/* Resubmit urb so we जारी receiving */
		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err != 0)
			dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n",
							__func__, err);
		p_priv->in_flip ^= 1;

		urb = p_priv->in_urbs[p_priv->in_flip];
	पूर्ण जबतक (urb->status != -EINPROGRESS);
पूर्ण

अटल व्योम	usa28_inack_callback(काष्ठा urb *urb)
अणु
पूर्ण

अटल व्योम	usa28_outcont_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा keyspan_port_निजी *p_priv;

	port =  urb->context;
	p_priv = usb_get_serial_port_data(port);

	अगर (p_priv->resend_cont) अणु
		dev_dbg(&port->dev, "%s - sending setup\n", __func__);
		keyspan_usa28_send_setup(port->serial, port,
						p_priv->resend_cont - 1);
	पूर्ण
पूर्ण

अटल व्योम	usa28_instat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक					err;
	अचिन्हित अक्षर 				*data = urb->transfer_buffer;
	काष्ठा keyspan_usa28_portStatusMessage	*msg;
	काष्ठा usb_serial			*serial;
	काष्ठा usb_serial_port			*port;
	काष्ठा keyspan_port_निजी	 	*p_priv;
	पूर्णांक old_dcd_state;
	पूर्णांक status = urb->status;

	serial =  urb->context;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status: %d\n",
				__func__, status);
		वापस;
	पूर्ण

	अगर (urb->actual_length != माप(काष्ठा keyspan_usa28_portStatusMessage)) अणु
		dev_dbg(&urb->dev->dev, "%s - bad length %d\n", __func__, urb->actual_length);
		जाओ निकास;
	पूर्ण

	msg = (काष्ठा keyspan_usa28_portStatusMessage *)data;

	/* Check port number from message and retrieve निजी data */
	अगर (msg->port >= serial->num_ports) अणु
		dev_dbg(&urb->dev->dev, "%s - Unexpected port number %d\n", __func__, msg->port);
		जाओ निकास;
	पूर्ण
	port = serial->port[msg->port];
	p_priv = usb_get_serial_port_data(port);
	अगर (!p_priv)
		जाओ resubmit;

	/* Update handshaking pin state inक्रमmation */
	old_dcd_state = p_priv->dcd_state;
	p_priv->cts_state = ((msg->cts) ? 1 : 0);
	p_priv->dsr_state = ((msg->dsr) ? 1 : 0);
	p_priv->dcd_state = ((msg->dcd) ? 1 : 0);
	p_priv->ri_state = ((msg->ri) ? 1 : 0);

	अगर (old_dcd_state != p_priv->dcd_state && old_dcd_state)
		tty_port_tty_hangup(&port->port, true);
resubmit:
		/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
निकास: ;
पूर्ण

अटल व्योम	usa28_glocont_callback(काष्ठा urb *urb)
अणु
पूर्ण


अटल व्योम	usa49_glocont_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा usb_serial_port *port;
	काष्ठा keyspan_port_निजी *p_priv;
	पूर्णांक i;

	serial =  urb->context;
	क्रम (i = 0; i < serial->num_ports; ++i) अणु
		port = serial->port[i];
		p_priv = usb_get_serial_port_data(port);
		अगर (!p_priv)
			जारी;

		अगर (p_priv->resend_cont) अणु
			dev_dbg(&port->dev, "%s - sending setup\n", __func__);
			keyspan_usa49_send_setup(serial, port,
						p_priv->resend_cont - 1);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

	/* This is actually called glostat in the Keyspan
	   करोco */
अटल व्योम	usa49_instat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक					err;
	अचिन्हित अक्षर 				*data = urb->transfer_buffer;
	काष्ठा keyspan_usa49_portStatusMessage	*msg;
	काष्ठा usb_serial			*serial;
	काष्ठा usb_serial_port			*port;
	काष्ठा keyspan_port_निजी	 	*p_priv;
	पूर्णांक old_dcd_state;
	पूर्णांक status = urb->status;

	serial =  urb->context;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status: %d\n",
				__func__, status);
		वापस;
	पूर्ण

	अगर (urb->actual_length !=
			माप(काष्ठा keyspan_usa49_portStatusMessage)) अणु
		dev_dbg(&urb->dev->dev, "%s - bad length %d\n", __func__, urb->actual_length);
		जाओ निकास;
	पूर्ण

	msg = (काष्ठा keyspan_usa49_portStatusMessage *)data;

	/* Check port number from message and retrieve निजी data */
	अगर (msg->portNumber >= serial->num_ports) अणु
		dev_dbg(&urb->dev->dev, "%s - Unexpected port number %d\n",
			__func__, msg->portNumber);
		जाओ निकास;
	पूर्ण
	port = serial->port[msg->portNumber];
	p_priv = usb_get_serial_port_data(port);
	अगर (!p_priv)
		जाओ resubmit;

	/* Update handshaking pin state inक्रमmation */
	old_dcd_state = p_priv->dcd_state;
	p_priv->cts_state = ((msg->cts) ? 1 : 0);
	p_priv->dsr_state = ((msg->dsr) ? 1 : 0);
	p_priv->dcd_state = ((msg->dcd) ? 1 : 0);
	p_priv->ri_state = ((msg->ri) ? 1 : 0);

	अगर (old_dcd_state != p_priv->dcd_state && old_dcd_state)
		tty_port_tty_hangup(&port->port, true);
resubmit:
	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
निकास:	;
पूर्ण

अटल व्योम	usa49_inack_callback(काष्ठा urb *urb)
अणु
पूर्ण

अटल व्योम	usa49_indat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक			i, err;
	पूर्णांक			endpoपूर्णांक;
	काष्ठा usb_serial_port	*port;
	अचिन्हित अक्षर 		*data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	endpoपूर्णांक = usb_pipeendpoपूर्णांक(urb->pipe);

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status %d on endpoint %x\n",
			__func__, status, endpoपूर्णांक);
		वापस;
	पूर्ण

	port =  urb->context;
	अगर (urb->actual_length) अणु
		/* 0x80 bit is error flag */
		अगर ((data[0] & 0x80) == 0) अणु
			/* no error on any byte */
			tty_insert_flip_string(&port->port, data + 1,
						urb->actual_length - 1);
		पूर्ण अन्यथा अणु
			/* some bytes had errors, every byte has status */
			क्रम (i = 0; i + 1 < urb->actual_length; i += 2) अणु
				पूर्णांक stat = data[i];
				पूर्णांक flag = TTY_NORMAL;

				अगर (stat & RXERROR_OVERRUN) अणु
					tty_insert_flip_अक्षर(&port->port, 0,
								TTY_OVERRUN);
				पूर्ण
				/* XXX should handle अवरोध (0x10) */
				अगर (stat & RXERROR_PARITY)
					flag = TTY_PARITY;
				अन्यथा अगर (stat & RXERROR_FRAMING)
					flag = TTY_FRAME;

				tty_insert_flip_अक्षर(&port->port, data[i+1],
						flag);
			पूर्ण
		पूर्ण
		tty_flip_buffer_push(&port->port);
	पूर्ण

	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
पूर्ण

अटल व्योम usa49wg_indat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक			i, len, x, err;
	काष्ठा usb_serial	*serial;
	काष्ठा usb_serial_port	*port;
	अचिन्हित अक्षर 		*data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	serial = urb->context;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status: %d\n",
				__func__, status);
		वापस;
	पूर्ण

	/* inbound data is in the क्रमm P#, len, status, data */
	i = 0;
	len = 0;

	जबतक (i < urb->actual_length) अणु

		/* Check port number from message */
		अगर (data[i] >= serial->num_ports) अणु
			dev_dbg(&urb->dev->dev, "%s - Unexpected port number %d\n",
				__func__, data[i]);
			वापस;
		पूर्ण
		port = serial->port[data[i++]];
		len = data[i++];

		/* 0x80 bit is error flag */
		अगर ((data[i] & 0x80) == 0) अणु
			/* no error on any byte */
			i++;
			क्रम (x = 1; x < len && i < urb->actual_length; ++x)
				tty_insert_flip_अक्षर(&port->port,
						data[i++], 0);
		पूर्ण अन्यथा अणु
			/*
			 * some bytes had errors, every byte has status
			 */
			क्रम (x = 0; x + 1 < len &&
				    i + 1 < urb->actual_length; x += 2) अणु
				पूर्णांक stat = data[i];
				पूर्णांक flag = TTY_NORMAL;

				अगर (stat & RXERROR_OVERRUN) अणु
					tty_insert_flip_अक्षर(&port->port, 0,
								TTY_OVERRUN);
				पूर्ण
				/* XXX should handle अवरोध (0x10) */
				अगर (stat & RXERROR_PARITY)
					flag = TTY_PARITY;
				अन्यथा अगर (stat & RXERROR_FRAMING)
					flag = TTY_FRAME;

				tty_insert_flip_अक्षर(&port->port, data[i+1],
						     flag);
				i += 2;
			पूर्ण
		पूर्ण
		tty_flip_buffer_push(&port->port);
	पूर्ण

	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&urb->dev->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
पूर्ण

/* not used, usa-49 करोesn't have per-port control endpoपूर्णांकs */
अटल व्योम usa49_outcont_callback(काष्ठा urb *urb)
अणु
पूर्ण

अटल व्योम usa90_indat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक			i, err;
	पूर्णांक			endpoपूर्णांक;
	काष्ठा usb_serial_port	*port;
	काष्ठा keyspan_port_निजी	 	*p_priv;
	अचिन्हित अक्षर 		*data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	endpoपूर्णांक = usb_pipeendpoपूर्णांक(urb->pipe);

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status %d on endpoint %x\n",
			__func__, status, endpoपूर्णांक);
		वापस;
	पूर्ण

	port =  urb->context;
	p_priv = usb_get_serial_port_data(port);

	अगर (urb->actual_length) अणु
		/* अगर current mode is DMA, looks like usa28 क्रमmat
		   otherwise looks like usa26 data क्रमmat */

		अगर (p_priv->baud > 57600)
			tty_insert_flip_string(&port->port, data,
					urb->actual_length);
		अन्यथा अणु
			/* 0x80 bit is error flag */
			अगर ((data[0] & 0x80) == 0) अणु
				/* no errors on inभागidual bytes, only
				   possible overrun err*/
				अगर (data[0] & RXERROR_OVERRUN) अणु
					tty_insert_flip_अक्षर(&port->port, 0,
								TTY_OVERRUN);
				पूर्ण
				क्रम (i = 1; i < urb->actual_length ; ++i)
					tty_insert_flip_अक्षर(&port->port,
							data[i], TTY_NORMAL);
			पूर्ण  अन्यथा अणु
			/* some bytes had errors, every byte has status */
				dev_dbg(&port->dev, "%s - RX error!!!!\n", __func__);
				क्रम (i = 0; i + 1 < urb->actual_length; i += 2) अणु
					पूर्णांक stat = data[i];
					पूर्णांक flag = TTY_NORMAL;

					अगर (stat & RXERROR_OVERRUN) अणु
						tty_insert_flip_अक्षर(
								&port->port, 0,
								TTY_OVERRUN);
					पूर्ण
					/* XXX should handle अवरोध (0x10) */
					अगर (stat & RXERROR_PARITY)
						flag = TTY_PARITY;
					अन्यथा अगर (stat & RXERROR_FRAMING)
						flag = TTY_FRAME;

					tty_insert_flip_अक्षर(&port->port,
							data[i+1], flag);
				पूर्ण
			पूर्ण
		पूर्ण
		tty_flip_buffer_push(&port->port);
	पूर्ण

	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
पूर्ण


अटल व्योम	usa90_instat_callback(काष्ठा urb *urb)
अणु
	अचिन्हित अक्षर 				*data = urb->transfer_buffer;
	काष्ठा keyspan_usa90_portStatusMessage	*msg;
	काष्ठा usb_serial			*serial;
	काष्ठा usb_serial_port			*port;
	काष्ठा keyspan_port_निजी	 	*p_priv;
	पूर्णांक old_dcd_state, err;
	पूर्णांक status = urb->status;

	serial =  urb->context;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status: %d\n",
				__func__, status);
		वापस;
	पूर्ण
	अगर (urb->actual_length < 14) अणु
		dev_dbg(&urb->dev->dev, "%s - %d byte report??\n", __func__, urb->actual_length);
		जाओ निकास;
	पूर्ण

	msg = (काष्ठा keyspan_usa90_portStatusMessage *)data;

	/* Now करो something useful with the data */

	port = serial->port[0];
	p_priv = usb_get_serial_port_data(port);
	अगर (!p_priv)
		जाओ resubmit;

	/* Update handshaking pin state inक्रमmation */
	old_dcd_state = p_priv->dcd_state;
	p_priv->cts_state = ((msg->cts) ? 1 : 0);
	p_priv->dsr_state = ((msg->dsr) ? 1 : 0);
	p_priv->dcd_state = ((msg->dcd) ? 1 : 0);
	p_priv->ri_state = ((msg->ri) ? 1 : 0);

	अगर (old_dcd_state != p_priv->dcd_state && old_dcd_state)
		tty_port_tty_hangup(&port->port, true);
resubmit:
	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
निकास:
	;
पूर्ण

अटल व्योम	usa90_outcont_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा keyspan_port_निजी *p_priv;

	port =  urb->context;
	p_priv = usb_get_serial_port_data(port);

	अगर (p_priv->resend_cont) अणु
		dev_dbg(&urb->dev->dev, "%s - sending setup\n", __func__);
		keyspan_usa90_send_setup(port->serial, port,
						p_priv->resend_cont - 1);
	पूर्ण
पूर्ण

/* Status messages from the 28xg */
अटल व्योम	usa67_instat_callback(काष्ठा urb *urb)
अणु
	पूर्णांक					err;
	अचिन्हित अक्षर 				*data = urb->transfer_buffer;
	काष्ठा keyspan_usa67_portStatusMessage	*msg;
	काष्ठा usb_serial			*serial;
	काष्ठा usb_serial_port			*port;
	काष्ठा keyspan_port_निजी	 	*p_priv;
	पूर्णांक old_dcd_state;
	पूर्णांक status = urb->status;

	serial = urb->context;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero status: %d\n",
				__func__, status);
		वापस;
	पूर्ण

	अगर (urb->actual_length !=
			माप(काष्ठा keyspan_usa67_portStatusMessage)) अणु
		dev_dbg(&urb->dev->dev, "%s - bad length %d\n", __func__, urb->actual_length);
		वापस;
	पूर्ण


	/* Now करो something useful with the data */
	msg = (काष्ठा keyspan_usa67_portStatusMessage *)data;

	/* Check port number from message and retrieve निजी data */
	अगर (msg->port >= serial->num_ports) अणु
		dev_dbg(&urb->dev->dev, "%s - Unexpected port number %d\n", __func__, msg->port);
		वापस;
	पूर्ण

	port = serial->port[msg->port];
	p_priv = usb_get_serial_port_data(port);
	अगर (!p_priv)
		जाओ resubmit;

	/* Update handshaking pin state inक्रमmation */
	old_dcd_state = p_priv->dcd_state;
	p_priv->cts_state = ((msg->hskia_cts) ? 1 : 0);
	p_priv->dcd_state = ((msg->gpia_dcd) ? 1 : 0);

	अगर (old_dcd_state != p_priv->dcd_state && old_dcd_state)
		tty_port_tty_hangup(&port->port, true);
resubmit:
	/* Resubmit urb so we जारी receiving */
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - resubmit read urb failed. (%d)\n", __func__, err);
पूर्ण

अटल व्योम usa67_glocont_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा usb_serial_port *port;
	काष्ठा keyspan_port_निजी *p_priv;
	पूर्णांक i;

	serial = urb->context;
	क्रम (i = 0; i < serial->num_ports; ++i) अणु
		port = serial->port[i];
		p_priv = usb_get_serial_port_data(port);
		अगर (!p_priv)
			जारी;

		अगर (p_priv->resend_cont) अणु
			dev_dbg(&port->dev, "%s - sending setup\n", __func__);
			keyspan_usa67_send_setup(serial, port,
						p_priv->resend_cont - 1);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक keyspan_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा keyspan_port_निजी	*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	पूर्णांक				flip;
	पूर्णांक				data_len;
	काष्ठा urb			*this_urb;

	p_priv = usb_get_serial_port_data(port);
	d_details = p_priv->device_details;

	/* FIXME: locking */
	अगर (d_details->msg_क्रमmat == msg_usa90)
		data_len = 64;
	अन्यथा
		data_len = 63;

	flip = p_priv->out_flip;

	/* Check both endpoपूर्णांकs to see अगर any are available. */
	this_urb = p_priv->out_urbs[flip];
	अगर (this_urb != शून्य) अणु
		अगर (this_urb->status != -EINPROGRESS)
			वापस data_len;
		flip = (flip + 1) & d_details->outdat_endp_flip;
		this_urb = p_priv->out_urbs[flip];
		अगर (this_urb != शून्य) अणु
			अगर (this_urb->status != -EINPROGRESS)
				वापस data_len;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक keyspan_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा keyspan_port_निजी 	*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	पूर्णांक				i, err;
	पूर्णांक				baud_rate, device_port;
	काष्ठा urb			*urb;
	अचिन्हित पूर्णांक			cflag = 0;

	p_priv = usb_get_serial_port_data(port);
	d_details = p_priv->device_details;

	/* Set some sane शेषs */
	p_priv->rts_state = 1;
	p_priv->dtr_state = 1;
	p_priv->baud = 9600;

	/* क्रमce baud and lcr to be set on खोलो */
	p_priv->old_baud = 0;
	p_priv->old_cflag = 0;

	p_priv->out_flip = 0;
	p_priv->in_flip = 0;

	/* Reset low level data toggle and start पढ़ोing from endpoपूर्णांकs */
	क्रम (i = 0; i < 2; i++) अणु
		urb = p_priv->in_urbs[i];
		अगर (urb == शून्य)
			जारी;

		/* make sure endpoपूर्णांक data toggle is synchronized
		   with the device */
		usb_clear_halt(urb->dev, urb->pipe);
		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err != 0)
			dev_dbg(&port->dev, "%s - submit urb %d failed (%d)\n", __func__, i, err);
	पूर्ण

	/* Reset low level data toggle on out endpoपूर्णांकs */
	क्रम (i = 0; i < 2; i++) अणु
		urb = p_priv->out_urbs[i];
		अगर (urb == शून्य)
			जारी;
		/* usb_settoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
						usb_pipeout(urb->pipe), 0); */
	पूर्ण

	/* get the terminal config क्रम the setup message now so we करोn't
	 * need to send 2 of them */

	device_port = port->port_number;
	अगर (tty) अणु
		cflag = tty->termios.c_cflag;
		/* Baud rate calculation takes baud rate as an पूर्णांकeger
		   so other rates can be generated अगर desired. */
		baud_rate = tty_get_baud_rate(tty);
		/* If no match or invalid, leave as शेष */
		अगर (baud_rate >= 0
		    && d_details->calculate_baud_rate(port, baud_rate, d_details->baudclk,
					शून्य, शून्य, शून्य, device_port) == KEYSPAN_BAUD_RATE_OK) अणु
			p_priv->baud = baud_rate;
		पूर्ण
	पूर्ण
	/* set CTS/RTS handshake etc. */
	p_priv->cflag = cflag;
	p_priv->flow_control = (cflag & CRTSCTS) ? flow_cts : flow_none;

	keyspan_send_setup(port, 1);
	/* mdelay(100); */
	/* keyspan_set_termios(port, शून्य); */

	वापस 0;
पूर्ण

अटल व्योम keyspan_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	काष्ठा keyspan_port_निजी *p_priv = usb_get_serial_port_data(port);

	p_priv->rts_state = on;
	p_priv->dtr_state = on;
	keyspan_send_setup(port, 0);
पूर्ण

अटल व्योम keyspan_बंद(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक			i;
	काष्ठा keyspan_port_निजी 	*p_priv;

	p_priv = usb_get_serial_port_data(port);

	p_priv->rts_state = 0;
	p_priv->dtr_state = 0;

	keyspan_send_setup(port, 2);
	/* pilot-xfer seems to work best with this delay */
	mdelay(100);

	p_priv->out_flip = 0;
	p_priv->in_flip = 0;

	usb_समाप्त_urb(p_priv->inack_urb);
	क्रम (i = 0; i < 2; i++) अणु
		usb_समाप्त_urb(p_priv->in_urbs[i]);
		usb_समाप्त_urb(p_priv->out_urbs[i]);
	पूर्ण
पूर्ण

/* करोwnload the firmware to a pre-rक्रमागतeration device */
अटल पूर्णांक keyspan_fake_startup(काष्ठा usb_serial *serial)
अणु
	अक्षर	*fw_name;

	dev_dbg(&serial->dev->dev, "Keyspan startup version %04x product %04x\n",
		le16_to_cpu(serial->dev->descriptor.bcdDevice),
		le16_to_cpu(serial->dev->descriptor.idProduct));

	अगर ((le16_to_cpu(serial->dev->descriptor.bcdDevice) & 0x8000)
								!= 0x8000) अणु
		dev_dbg(&serial->dev->dev, "Firmware already loaded.  Quitting.\n");
		वापस 1;
	पूर्ण

		/* Select firmware image on the basis of idProduct */
	चयन (le16_to_cpu(serial->dev->descriptor.idProduct)) अणु
	हाल keyspan_usa28_pre_product_id:
		fw_name = "keyspan/usa28.fw";
		अवरोध;

	हाल keyspan_usa28x_pre_product_id:
		fw_name = "keyspan/usa28x.fw";
		अवरोध;

	हाल keyspan_usa28xa_pre_product_id:
		fw_name = "keyspan/usa28xa.fw";
		अवरोध;

	हाल keyspan_usa28xb_pre_product_id:
		fw_name = "keyspan/usa28xb.fw";
		अवरोध;

	हाल keyspan_usa19_pre_product_id:
		fw_name = "keyspan/usa19.fw";
		अवरोध;

	हाल keyspan_usa19qi_pre_product_id:
		fw_name = "keyspan/usa19qi.fw";
		अवरोध;

	हाल keyspan_mpr_pre_product_id:
		fw_name = "keyspan/mpr.fw";
		अवरोध;

	हाल keyspan_usa19qw_pre_product_id:
		fw_name = "keyspan/usa19qw.fw";
		अवरोध;

	हाल keyspan_usa18x_pre_product_id:
		fw_name = "keyspan/usa18x.fw";
		अवरोध;

	हाल keyspan_usa19w_pre_product_id:
		fw_name = "keyspan/usa19w.fw";
		अवरोध;

	हाल keyspan_usa49w_pre_product_id:
		fw_name = "keyspan/usa49w.fw";
		अवरोध;

	हाल keyspan_usa49wlc_pre_product_id:
		fw_name = "keyspan/usa49wlc.fw";
		अवरोध;

	शेष:
		dev_err(&serial->dev->dev, "Unknown product ID (%04x)\n",
			le16_to_cpu(serial->dev->descriptor.idProduct));
		वापस 1;
	पूर्ण

	dev_dbg(&serial->dev->dev, "Uploading Keyspan %s firmware.\n", fw_name);

	अगर (ezusb_fx1_ihex_firmware_करोwnload(serial->dev, fw_name) < 0) अणु
		dev_err(&serial->dev->dev, "failed to load firmware \"%s\"\n",
			fw_name);
		वापस -ENOENT;
	पूर्ण

	/* after करोwnloading firmware Rक्रमागतeration will occur in a
	  moment and the new device will bind to the real driver */

	/* we करोn't want this device to have a driver asचिन्हित to it. */
	वापस 1;
पूर्ण

/* Helper functions used by keyspan_setup_urbs */
अटल काष्ठा usb_endpoपूर्णांक_descriptor स्थिर *find_ep(काष्ठा usb_serial स्थिर *serial,
						     पूर्णांक endpoपूर्णांक)
अणु
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	पूर्णांक i;

	अगरace_desc = serial->पूर्णांकerface->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		ep = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (ep->bEndpoपूर्णांकAddress == endpoपूर्णांक)
			वापस ep;
	पूर्ण
	dev_warn(&serial->पूर्णांकerface->dev, "found no endpoint descriptor for endpoint %x\n",
			endpoपूर्णांक);
	वापस शून्य;
पूर्ण

अटल काष्ठा urb *keyspan_setup_urb(काष्ठा usb_serial *serial, पूर्णांक endpoपूर्णांक,
				      पूर्णांक dir, व्योम *ctx, अक्षर *buf, पूर्णांक len,
				      व्योम (*callback)(काष्ठा urb *))
अणु
	काष्ठा urb *urb;
	काष्ठा usb_endpoपूर्णांक_descriptor स्थिर *ep_desc;
	अक्षर स्थिर *ep_type_name;

	अगर (endpoपूर्णांक == -1)
		वापस शून्य;		/* endpoपूर्णांक not needed */

	dev_dbg(&serial->पूर्णांकerface->dev, "%s - alloc for endpoint %x\n",
			__func__, endpoपूर्णांक);
	urb = usb_alloc_urb(0, GFP_KERNEL);		/* No ISO */
	अगर (!urb)
		वापस शून्य;

	अगर (endpoपूर्णांक == 0) अणु
		/* control EP filled in when used */
		वापस urb;
	पूर्ण

	ep_desc = find_ep(serial, endpoपूर्णांक);
	अगर (!ep_desc) अणु
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep_desc)) अणु
		ep_type_name = "INT";
		usb_fill_पूर्णांक_urb(urb, serial->dev,
				 usb_sndपूर्णांकpipe(serial->dev, endpoपूर्णांक) | dir,
				 buf, len, callback, ctx,
				 ep_desc->bInterval);
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_bulk(ep_desc)) अणु
		ep_type_name = "BULK";
		usb_fill_bulk_urb(urb, serial->dev,
				  usb_sndbulkpipe(serial->dev, endpoपूर्णांक) | dir,
				  buf, len, callback, ctx);
	पूर्ण अन्यथा अणु
		dev_warn(&serial->पूर्णांकerface->dev,
			 "unsupported endpoint type %x\n",
			 usb_endpoपूर्णांक_type(ep_desc));
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण

	dev_dbg(&serial->पूर्णांकerface->dev, "%s - using urb %p for %s endpoint %x\n",
	    __func__, urb, ep_type_name, endpoपूर्णांक);
	वापस urb;
पूर्ण

अटल काष्ठा callbacks अणु
	व्योम	(*instat_callback)(काष्ठा urb *);
	व्योम	(*glocont_callback)(काष्ठा urb *);
	व्योम	(*indat_callback)(काष्ठा urb *);
	व्योम	(*outdat_callback)(काष्ठा urb *);
	व्योम	(*inack_callback)(काष्ठा urb *);
	व्योम	(*outcont_callback)(काष्ठा urb *);
पूर्ण keyspan_callbacks[] = अणु
	अणु
		/* msg_usa26 callbacks */
		.instat_callback =	usa26_instat_callback,
		.glocont_callback =	usa26_glocont_callback,
		.indat_callback =	usa26_indat_callback,
		.outdat_callback =	usa2x_outdat_callback,
		.inack_callback =	usa26_inack_callback,
		.outcont_callback =	usa26_outcont_callback,
	पूर्ण, अणु
		/* msg_usa28 callbacks */
		.instat_callback =	usa28_instat_callback,
		.glocont_callback =	usa28_glocont_callback,
		.indat_callback =	usa28_indat_callback,
		.outdat_callback =	usa2x_outdat_callback,
		.inack_callback =	usa28_inack_callback,
		.outcont_callback =	usa28_outcont_callback,
	पूर्ण, अणु
		/* msg_usa49 callbacks */
		.instat_callback =	usa49_instat_callback,
		.glocont_callback =	usa49_glocont_callback,
		.indat_callback =	usa49_indat_callback,
		.outdat_callback =	usa2x_outdat_callback,
		.inack_callback =	usa49_inack_callback,
		.outcont_callback =	usa49_outcont_callback,
	पूर्ण, अणु
		/* msg_usa90 callbacks */
		.instat_callback =	usa90_instat_callback,
		.glocont_callback =	usa28_glocont_callback,
		.indat_callback =	usa90_indat_callback,
		.outdat_callback =	usa2x_outdat_callback,
		.inack_callback =	usa28_inack_callback,
		.outcont_callback =	usa90_outcont_callback,
	पूर्ण, अणु
		/* msg_usa67 callbacks */
		.instat_callback =	usa67_instat_callback,
		.glocont_callback =	usa67_glocont_callback,
		.indat_callback =	usa26_indat_callback,
		.outdat_callback =	usa2x_outdat_callback,
		.inack_callback =	usa26_inack_callback,
		.outcont_callback =	usa26_outcont_callback,
	पूर्ण
पूर्ण;

	/* Generic setup urbs function that uses
	   data in device_details */
अटल व्योम keyspan_setup_urbs(काष्ठा usb_serial *serial)
अणु
	काष्ठा keyspan_serial_निजी 	*s_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	काष्ठा callbacks		*cback;

	s_priv = usb_get_serial_data(serial);
	d_details = s_priv->device_details;

	/* Setup values क्रम the various callback routines */
	cback = &keyspan_callbacks[d_details->msg_क्रमmat];

	/* Allocate and set up urbs क्रम each one that is in use,
	   starting with instat endpoपूर्णांकs */
	s_priv->instat_urb = keyspan_setup_urb
		(serial, d_details->instat_endpoपूर्णांक, USB_सूची_IN,
		 serial, s_priv->instat_buf, INSTAT_BUFLEN,
		 cback->instat_callback);

	s_priv->indat_urb = keyspan_setup_urb
		(serial, d_details->indat_endpoपूर्णांक, USB_सूची_IN,
		 serial, s_priv->indat_buf, INDAT49W_BUFLEN,
		 usa49wg_indat_callback);

	s_priv->glocont_urb = keyspan_setup_urb
		(serial, d_details->glocont_endpoपूर्णांक, USB_सूची_OUT,
		 serial, s_priv->glocont_buf, GLOCONT_BUFLEN,
		 cback->glocont_callback);
पूर्ण

/* usa19 function करोesn't require prescaler */
अटल पूर्णांक keyspan_usa19_calc_baud(काष्ठा usb_serial_port *port,
				   u32 baud_rate, u32 baudclk, u8 *rate_hi,
				   u8 *rate_low, u8 *prescaler, पूर्णांक portnum)
अणु
	u32 	b16,	/* baud rate बार 16 (actual rate used पूर्णांकernally) */
		भाग,	/* भागisor */
		cnt;	/* inverse of भागisor (programmed पूर्णांकo 8051) */

	dev_dbg(&port->dev, "%s - %d.\n", __func__, baud_rate);

	/* prevent भागide by zero...  */
	b16 = baud_rate * 16L;
	अगर (b16 == 0)
		वापस KEYSPAN_INVALID_BAUD_RATE;
	/* Any "standard" rate over 57k6 is marginal on the USA-19
	   as we run out of भागisor resolution. */
	अगर (baud_rate > 57600)
		वापस KEYSPAN_INVALID_BAUD_RATE;

	/* calculate the भागisor and the counter (its inverse) */
	भाग = baudclk / b16;
	अगर (भाग == 0)
		वापस KEYSPAN_INVALID_BAUD_RATE;
	अन्यथा
		cnt = 0 - भाग;

	अगर (भाग > 0xffff)
		वापस KEYSPAN_INVALID_BAUD_RATE;

	/* वापस the counter values अगर non-null */
	अगर (rate_low)
		*rate_low = (u8) (cnt & 0xff);
	अगर (rate_hi)
		*rate_hi = (u8) ((cnt >> 8) & 0xff);
	अगर (rate_low && rate_hi)
		dev_dbg(&port->dev, "%s - %d %02x %02x.\n",
				__func__, baud_rate, *rate_hi, *rate_low);
	वापस KEYSPAN_BAUD_RATE_OK;
पूर्ण

/* usa19hs function करोesn't require prescaler */
अटल पूर्णांक keyspan_usa19hs_calc_baud(काष्ठा usb_serial_port *port,
				     u32 baud_rate, u32 baudclk, u8 *rate_hi,
				     u8 *rate_low, u8 *prescaler, पूर्णांक portnum)
अणु
	u32 	b16,	/* baud rate बार 16 (actual rate used पूर्णांकernally) */
			भाग;	/* भागisor */

	dev_dbg(&port->dev, "%s - %d.\n", __func__, baud_rate);

	/* prevent भागide by zero...  */
	b16 = baud_rate * 16L;
	अगर (b16 == 0)
		वापस KEYSPAN_INVALID_BAUD_RATE;

	/* calculate the भागisor */
	भाग = baudclk / b16;
	अगर (भाग == 0)
		वापस KEYSPAN_INVALID_BAUD_RATE;

	अगर (भाग > 0xffff)
		वापस KEYSPAN_INVALID_BAUD_RATE;

	/* वापस the counter values अगर non-null */
	अगर (rate_low)
		*rate_low = (u8) (भाग & 0xff);

	अगर (rate_hi)
		*rate_hi = (u8) ((भाग >> 8) & 0xff);

	अगर (rate_low && rate_hi)
		dev_dbg(&port->dev, "%s - %d %02x %02x.\n",
			__func__, baud_rate, *rate_hi, *rate_low);

	वापस KEYSPAN_BAUD_RATE_OK;
पूर्ण

अटल पूर्णांक keyspan_usa19w_calc_baud(काष्ठा usb_serial_port *port,
				    u32 baud_rate, u32 baudclk, u8 *rate_hi,
				    u8 *rate_low, u8 *prescaler, पूर्णांक portnum)
अणु
	u32 	b16,	/* baud rate बार 16 (actual rate used पूर्णांकernally) */
		clk,	/* घड़ी with 13/8 prescaler */
		भाग,	/* भागisor using 13/8 prescaler */
		res,	/* resulting baud rate using 13/8 prescaler */
		dअगरf,	/* error using 13/8 prescaler */
		smallest_dअगरf;
	u8	best_prescaler;
	पूर्णांक	i;

	dev_dbg(&port->dev, "%s - %d.\n", __func__, baud_rate);

	/* prevent भागide by zero */
	b16 = baud_rate * 16L;
	अगर (b16 == 0)
		वापस KEYSPAN_INVALID_BAUD_RATE;

	/* Calculate prescaler by trying them all and looking
	   क्रम best fit */

	/* start with largest possible dअगरference */
	smallest_dअगरf = 0xffffffff;

		/* 0 is an invalid prescaler, used as a flag */
	best_prescaler = 0;

	क्रम (i = 8; i <= 0xff; ++i) अणु
		clk = (baudclk * 8) / (u32) i;

		भाग = clk / b16;
		अगर (भाग == 0)
			जारी;

		res = clk / भाग;
		dअगरf = (res > b16) ? (res-b16) : (b16-res);

		अगर (dअगरf < smallest_dअगरf) अणु
			best_prescaler = i;
			smallest_dअगरf = dअगरf;
		पूर्ण
	पूर्ण

	अगर (best_prescaler == 0)
		वापस KEYSPAN_INVALID_BAUD_RATE;

	clk = (baudclk * 8) / (u32) best_prescaler;
	भाग = clk / b16;

	/* वापस the भागisor and prescaler अगर non-null */
	अगर (rate_low)
		*rate_low = (u8) (भाग & 0xff);
	अगर (rate_hi)
		*rate_hi = (u8) ((भाग >> 8) & 0xff);
	अगर (prescaler) अणु
		*prescaler = best_prescaler;
		/*  dev_dbg(&port->dev, "%s - %d %d\n", __func__, *prescaler, भाग); */
	पूर्ण
	वापस KEYSPAN_BAUD_RATE_OK;
पूर्ण

	/* USA-28 supports dअगरferent maximum baud rates on each port */
अटल पूर्णांक keyspan_usa28_calc_baud(काष्ठा usb_serial_port *port,
				   u32 baud_rate, u32 baudclk, u8 *rate_hi,
				   u8 *rate_low, u8 *prescaler, पूर्णांक portnum)
अणु
	u32 	b16,	/* baud rate बार 16 (actual rate used पूर्णांकernally) */
		भाग,	/* भागisor */
		cnt;	/* inverse of भागisor (programmed पूर्णांकo 8051) */

	dev_dbg(&port->dev, "%s - %d.\n", __func__, baud_rate);

		/* prevent भागide by zero */
	b16 = baud_rate * 16L;
	अगर (b16 == 0)
		वापस KEYSPAN_INVALID_BAUD_RATE;

	/* calculate the भागisor and the counter (its inverse) */
	भाग = KEYSPAN_USA28_BAUDCLK / b16;
	अगर (भाग == 0)
		वापस KEYSPAN_INVALID_BAUD_RATE;
	अन्यथा
		cnt = 0 - भाग;

	/* check क्रम out of range, based on portnum,
	   and वापस result */
	अगर (portnum == 0) अणु
		अगर (भाग > 0xffff)
			वापस KEYSPAN_INVALID_BAUD_RATE;
	पूर्ण अन्यथा अणु
		अगर (portnum == 1) अणु
			अगर (भाग > 0xff)
				वापस KEYSPAN_INVALID_BAUD_RATE;
		पूर्ण अन्यथा
			वापस KEYSPAN_INVALID_BAUD_RATE;
	पूर्ण

		/* वापस the counter values अगर not शून्य
		   (port 1 will ignore retHi) */
	अगर (rate_low)
		*rate_low = (u8) (cnt & 0xff);
	अगर (rate_hi)
		*rate_hi = (u8) ((cnt >> 8) & 0xff);
	dev_dbg(&port->dev, "%s - %d OK.\n", __func__, baud_rate);
	वापस KEYSPAN_BAUD_RATE_OK;
पूर्ण

अटल पूर्णांक keyspan_usa26_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port)
अणु
	काष्ठा keyspan_usa26_portControlMessage	msg;
	काष्ठा keyspan_serial_निजी 		*s_priv;
	काष्ठा keyspan_port_निजी 		*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	काष्ठा urb				*this_urb;
	पूर्णांक 					device_port, err;

	dev_dbg(&port->dev, "%s reset=%d\n", __func__, reset_port);

	s_priv = usb_get_serial_data(serial);
	p_priv = usb_get_serial_port_data(port);
	d_details = s_priv->device_details;
	device_port = port->port_number;

	this_urb = p_priv->outcont_urb;

		/* Make sure we have an urb then send the message */
	अगर (this_urb == शून्य) अणु
		dev_dbg(&port->dev, "%s - oops no urb.\n", __func__);
		वापस -1;
	पूर्ण

	dev_dbg(&port->dev, "%s - endpoint %x\n",
			__func__, usb_pipeendpoपूर्णांक(this_urb->pipe));

	/* Save reset port val क्रम resend.
	   Don't overग_लिखो resend क्रम खोलो/बंद condition. */
	अगर ((reset_port + 1) > p_priv->resend_cont)
		p_priv->resend_cont = reset_port + 1;
	अगर (this_urb->status == -EINPROGRESS) अणु
		/*  dev_dbg(&port->dev, "%s - already writing\n", __func__); */
		mdelay(5);
		वापस -1;
	पूर्ण

	स_रखो(&msg, 0, माप(काष्ठा keyspan_usa26_portControlMessage));

	/* Only set baud rate अगर it's changed */
	अगर (p_priv->old_baud != p_priv->baud) अणु
		p_priv->old_baud = p_priv->baud;
		msg.setClocking = 0xff;
		अगर (d_details->calculate_baud_rate(port, p_priv->baud, d_details->baudclk,
						   &msg.baudHi, &msg.baudLo, &msg.prescaler,
						   device_port) == KEYSPAN_INVALID_BAUD_RATE) अणु
			dev_dbg(&port->dev, "%s - Invalid baud rate %d requested, using 9600.\n",
				__func__, p_priv->baud);
			msg.baudLo = 0;
			msg.baudHi = 125;	/* Values क्रम 9600 baud */
			msg.prescaler = 10;
		पूर्ण
		msg.setPrescaler = 0xff;
	पूर्ण

	msg.lcr = (p_priv->cflag & CSTOPB) ? STOPBITS_678_2 : STOPBITS_5678_1;
	चयन (p_priv->cflag & CSIZE) अणु
	हाल CS5:
		msg.lcr |= USA_DATABITS_5;
		अवरोध;
	हाल CS6:
		msg.lcr |= USA_DATABITS_6;
		अवरोध;
	हाल CS7:
		msg.lcr |= USA_DATABITS_7;
		अवरोध;
	हाल CS8:
		msg.lcr |= USA_DATABITS_8;
		अवरोध;
	पूर्ण
	अगर (p_priv->cflag & PARENB) अणु
		/* note USA_PARITY_NONE == 0 */
		msg.lcr |= (p_priv->cflag & PARODD) ?
			USA_PARITY_ODD : USA_PARITY_EVEN;
	पूर्ण
	msg.setLcr = 0xff;

	msg.ctsFlowControl = (p_priv->flow_control == flow_cts);
	msg.xonFlowControl = 0;
	msg.setFlowControl = 0xff;
	msg.क्रमwardingLength = 16;
	msg.xonChar = 17;
	msg.xoffChar = 19;

	/* Opening port */
	अगर (reset_port == 1) अणु
		msg._txOn = 1;
		msg._txOff = 0;
		msg.txFlush = 0;
		msg.txBreak = 0;
		msg.rxOn = 1;
		msg.rxOff = 0;
		msg.rxFlush = 1;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0xff;
	पूर्ण

	/* Closing port */
	अन्यथा अगर (reset_port == 2) अणु
		msg._txOn = 0;
		msg._txOff = 1;
		msg.txFlush = 0;
		msg.txBreak = 0;
		msg.rxOn = 0;
		msg.rxOff = 1;
		msg.rxFlush = 1;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0;
	पूर्ण

	/* Sending पूर्णांकermediate configs */
	अन्यथा अणु
		msg._txOn = (!p_priv->अवरोध_on);
		msg._txOff = 0;
		msg.txFlush = 0;
		msg.txBreak = (p_priv->अवरोध_on);
		msg.rxOn = 0;
		msg.rxOff = 0;
		msg.rxFlush = 0;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0x0;
	पूर्ण

	/* Do handshaking outमाला_दो */
	msg.setTxTriState_setRts = 0xff;
	msg.txTriState_rts = p_priv->rts_state;

	msg.setHskoa_setDtr = 0xff;
	msg.hskoa_dtr = p_priv->dtr_state;

	p_priv->resend_cont = 0;
	स_नकल(this_urb->transfer_buffer, &msg, माप(msg));

	/* send the data out the device on control endpoपूर्णांक */
	this_urb->transfer_buffer_length = माप(msg);

	err = usb_submit_urb(this_urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - usb_submit_urb(setup) failed (%d)\n", __func__, err);
	वापस 0;
पूर्ण

अटल पूर्णांक keyspan_usa28_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port)
अणु
	काष्ठा keyspan_usa28_portControlMessage	msg;
	काष्ठा keyspan_serial_निजी	 	*s_priv;
	काष्ठा keyspan_port_निजी 		*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	काष्ठा urb				*this_urb;
	पूर्णांक 					device_port, err;

	s_priv = usb_get_serial_data(serial);
	p_priv = usb_get_serial_port_data(port);
	d_details = s_priv->device_details;
	device_port = port->port_number;

	/* only करो something अगर we have a bulk out endpoपूर्णांक */
	this_urb = p_priv->outcont_urb;
	अगर (this_urb == शून्य) अणु
		dev_dbg(&port->dev, "%s - oops no urb.\n", __func__);
		वापस -1;
	पूर्ण

	/* Save reset port val क्रम resend.
	   Don't overग_लिखो resend क्रम खोलो/बंद condition. */
	अगर ((reset_port + 1) > p_priv->resend_cont)
		p_priv->resend_cont = reset_port + 1;
	अगर (this_urb->status == -EINPROGRESS) अणु
		dev_dbg(&port->dev, "%s already writing\n", __func__);
		mdelay(5);
		वापस -1;
	पूर्ण

	स_रखो(&msg, 0, माप(काष्ठा keyspan_usa28_portControlMessage));

	msg.setBaudRate = 1;
	अगर (d_details->calculate_baud_rate(port, p_priv->baud, d_details->baudclk,
					   &msg.baudHi, &msg.baudLo, शून्य,
					   device_port) == KEYSPAN_INVALID_BAUD_RATE) अणु
		dev_dbg(&port->dev, "%s - Invalid baud rate requested %d.\n",
						__func__, p_priv->baud);
		msg.baudLo = 0xff;
		msg.baudHi = 0xb2;	/* Values क्रम 9600 baud */
	पूर्ण

	/* If parity is enabled, we must calculate it ourselves. */
	msg.parity = 0;		/* XXX क्रम now */

	msg.ctsFlowControl = (p_priv->flow_control == flow_cts);
	msg.xonFlowControl = 0;

	/* Do handshaking outमाला_दो, DTR is inverted relative to RTS */
	msg.rts = p_priv->rts_state;
	msg.dtr = p_priv->dtr_state;

	msg.क्रमwardingLength = 16;
	msg.क्रमwardMs = 10;
	msg.अवरोधThreshold = 45;
	msg.xonChar = 17;
	msg.xoffChar = 19;

	/*msg.वापसStatus = 1;
	msg.resetDataToggle = 0xff;*/
	/* Opening port */
	अगर (reset_port == 1) अणु
		msg._txOn = 1;
		msg._txOff = 0;
		msg.txFlush = 0;
		msg.txForceXoff = 0;
		msg.txBreak = 0;
		msg.rxOn = 1;
		msg.rxOff = 0;
		msg.rxFlush = 1;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0xff;
	पूर्ण
	/* Closing port */
	अन्यथा अगर (reset_port == 2) अणु
		msg._txOn = 0;
		msg._txOff = 1;
		msg.txFlush = 0;
		msg.txForceXoff = 0;
		msg.txBreak = 0;
		msg.rxOn = 0;
		msg.rxOff = 1;
		msg.rxFlush = 1;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0;
	पूर्ण
	/* Sending पूर्णांकermediate configs */
	अन्यथा अणु
		msg._txOn = (!p_priv->अवरोध_on);
		msg._txOff = 0;
		msg.txFlush = 0;
		msg.txForceXoff = 0;
		msg.txBreak = (p_priv->अवरोध_on);
		msg.rxOn = 0;
		msg.rxOff = 0;
		msg.rxFlush = 0;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0x0;
	पूर्ण

	p_priv->resend_cont = 0;
	स_नकल(this_urb->transfer_buffer, &msg, माप(msg));

	/* send the data out the device on control endpoपूर्णांक */
	this_urb->transfer_buffer_length = माप(msg);

	err = usb_submit_urb(this_urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - usb_submit_urb(setup) failed\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक keyspan_usa49_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port)
अणु
	काष्ठा keyspan_usa49_portControlMessage	msg;
	काष्ठा usb_ctrlrequest 			*dr = शून्य;
	काष्ठा keyspan_serial_निजी 		*s_priv;
	काष्ठा keyspan_port_निजी 		*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	काष्ठा urb				*this_urb;
	पूर्णांक 					err, device_port;

	s_priv = usb_get_serial_data(serial);
	p_priv = usb_get_serial_port_data(port);
	d_details = s_priv->device_details;

	this_urb = s_priv->glocont_urb;

	/* Work out which port within the device is being setup */
	device_port = port->port_number;

	/* Make sure we have an urb then send the message */
	अगर (this_urb == शून्य) अणु
		dev_dbg(&port->dev, "%s - oops no urb for port.\n", __func__);
		वापस -1;
	पूर्ण

	dev_dbg(&port->dev, "%s - endpoint %x (%d)\n",
		__func__, usb_pipeendpoपूर्णांक(this_urb->pipe), device_port);

	/* Save reset port val क्रम resend.
	   Don't overग_लिखो resend क्रम खोलो/बंद condition. */
	अगर ((reset_port + 1) > p_priv->resend_cont)
		p_priv->resend_cont = reset_port + 1;

	अगर (this_urb->status == -EINPROGRESS) अणु
		/*  dev_dbg(&port->dev, "%s - already writing\n", __func__); */
		mdelay(5);
		वापस -1;
	पूर्ण

	स_रखो(&msg, 0, माप(काष्ठा keyspan_usa49_portControlMessage));

	msg.portNumber = device_port;

	/* Only set baud rate अगर it's changed */
	अगर (p_priv->old_baud != p_priv->baud) अणु
		p_priv->old_baud = p_priv->baud;
		msg.setClocking = 0xff;
		अगर (d_details->calculate_baud_rate(port, p_priv->baud, d_details->baudclk,
						   &msg.baudHi, &msg.baudLo, &msg.prescaler,
						   device_port) == KEYSPAN_INVALID_BAUD_RATE) अणु
			dev_dbg(&port->dev, "%s - Invalid baud rate %d requested, using 9600.\n",
				__func__, p_priv->baud);
			msg.baudLo = 0;
			msg.baudHi = 125;	/* Values क्रम 9600 baud */
			msg.prescaler = 10;
		पूर्ण
		/* msg.setPrescaler = 0xff; */
	पूर्ण

	msg.lcr = (p_priv->cflag & CSTOPB) ? STOPBITS_678_2 : STOPBITS_5678_1;
	चयन (p_priv->cflag & CSIZE) अणु
	हाल CS5:
		msg.lcr |= USA_DATABITS_5;
		अवरोध;
	हाल CS6:
		msg.lcr |= USA_DATABITS_6;
		अवरोध;
	हाल CS7:
		msg.lcr |= USA_DATABITS_7;
		अवरोध;
	हाल CS8:
		msg.lcr |= USA_DATABITS_8;
		अवरोध;
	पूर्ण
	अगर (p_priv->cflag & PARENB) अणु
		/* note USA_PARITY_NONE == 0 */
		msg.lcr |= (p_priv->cflag & PARODD) ?
			USA_PARITY_ODD : USA_PARITY_EVEN;
	पूर्ण
	msg.setLcr = 0xff;

	msg.ctsFlowControl = (p_priv->flow_control == flow_cts);
	msg.xonFlowControl = 0;
	msg.setFlowControl = 0xff;

	msg.क्रमwardingLength = 16;
	msg.xonChar = 17;
	msg.xoffChar = 19;

	/* Opening port */
	अगर (reset_port == 1) अणु
		msg._txOn = 1;
		msg._txOff = 0;
		msg.txFlush = 0;
		msg.txBreak = 0;
		msg.rxOn = 1;
		msg.rxOff = 0;
		msg.rxFlush = 1;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0xff;
		msg.enablePort = 1;
		msg.disablePort = 0;
	पूर्ण
	/* Closing port */
	अन्यथा अगर (reset_port == 2) अणु
		msg._txOn = 0;
		msg._txOff = 1;
		msg.txFlush = 0;
		msg.txBreak = 0;
		msg.rxOn = 0;
		msg.rxOff = 1;
		msg.rxFlush = 1;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0;
		msg.enablePort = 0;
		msg.disablePort = 1;
	पूर्ण
	/* Sending पूर्णांकermediate configs */
	अन्यथा अणु
		msg._txOn = (!p_priv->अवरोध_on);
		msg._txOff = 0;
		msg.txFlush = 0;
		msg.txBreak = (p_priv->अवरोध_on);
		msg.rxOn = 0;
		msg.rxOff = 0;
		msg.rxFlush = 0;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0x0;
		msg.enablePort = 0;
		msg.disablePort = 0;
	पूर्ण

	/* Do handshaking outमाला_दो */
	msg.setRts = 0xff;
	msg.rts = p_priv->rts_state;

	msg.setDtr = 0xff;
	msg.dtr = p_priv->dtr_state;

	p_priv->resend_cont = 0;

	/* अगर the device is a 49wg, we send control message on usb
	   control EP 0 */

	अगर (d_details->product_id == keyspan_usa49wg_product_id) अणु
		dr = (व्योम *)(s_priv->ctrl_buf);
		dr->bRequestType = USB_TYPE_VENDOR | USB_सूची_OUT;
		dr->bRequest = 0xB0;	/* 49wg control message */
		dr->wValue = 0;
		dr->wIndex = 0;
		dr->wLength = cpu_to_le16(माप(msg));

		स_नकल(s_priv->glocont_buf, &msg, माप(msg));

		usb_fill_control_urb(this_urb, serial->dev,
				usb_sndctrlpipe(serial->dev, 0),
				(अचिन्हित अक्षर *)dr, s_priv->glocont_buf,
				माप(msg), usa49_glocont_callback, serial);

	पूर्ण अन्यथा अणु
		स_नकल(this_urb->transfer_buffer, &msg, माप(msg));

		/* send the data out the device on control endpoपूर्णांक */
		this_urb->transfer_buffer_length = माप(msg);
	पूर्ण
	err = usb_submit_urb(this_urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - usb_submit_urb(setup) failed (%d)\n", __func__, err);

	वापस 0;
पूर्ण

अटल पूर्णांक keyspan_usa90_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port)
अणु
	काष्ठा keyspan_usa90_portControlMessage	msg;
	काष्ठा keyspan_serial_निजी 		*s_priv;
	काष्ठा keyspan_port_निजी 		*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	काष्ठा urb				*this_urb;
	पूर्णांक 					err;
	u8						prescaler;

	s_priv = usb_get_serial_data(serial);
	p_priv = usb_get_serial_port_data(port);
	d_details = s_priv->device_details;

	/* only करो something अगर we have a bulk out endpoपूर्णांक */
	this_urb = p_priv->outcont_urb;
	अगर (this_urb == शून्य) अणु
		dev_dbg(&port->dev, "%s - oops no urb.\n", __func__);
		वापस -1;
	पूर्ण

	/* Save reset port val क्रम resend.
	   Don't overग_लिखो resend क्रम खोलो/बंद condition. */
	अगर ((reset_port + 1) > p_priv->resend_cont)
		p_priv->resend_cont = reset_port + 1;
	अगर (this_urb->status == -EINPROGRESS) अणु
		dev_dbg(&port->dev, "%s already writing\n", __func__);
		mdelay(5);
		वापस -1;
	पूर्ण

	स_रखो(&msg, 0, माप(काष्ठा keyspan_usa90_portControlMessage));

	/* Only set baud rate अगर it's changed */
	अगर (p_priv->old_baud != p_priv->baud) अणु
		p_priv->old_baud = p_priv->baud;
		msg.setClocking = 0x01;
		अगर (d_details->calculate_baud_rate(port, p_priv->baud, d_details->baudclk,
						   &msg.baudHi, &msg.baudLo, &prescaler, 0) == KEYSPAN_INVALID_BAUD_RATE) अणु
			dev_dbg(&port->dev, "%s - Invalid baud rate %d requested, using 9600.\n",
				__func__, p_priv->baud);
			p_priv->baud = 9600;
			d_details->calculate_baud_rate(port, p_priv->baud, d_details->baudclk,
				&msg.baudHi, &msg.baudLo, &prescaler, 0);
		पूर्ण
		msg.setRxMode = 1;
		msg.setTxMode = 1;
	पूर्ण

	/* modes must always be correctly specअगरied */
	अगर (p_priv->baud > 57600) अणु
		msg.rxMode = RXMODE_DMA;
		msg.txMode = TXMODE_DMA;
	पूर्ण अन्यथा अणु
		msg.rxMode = RXMODE_BYHAND;
		msg.txMode = TXMODE_BYHAND;
	पूर्ण

	msg.lcr = (p_priv->cflag & CSTOPB) ? STOPBITS_678_2 : STOPBITS_5678_1;
	चयन (p_priv->cflag & CSIZE) अणु
	हाल CS5:
		msg.lcr |= USA_DATABITS_5;
		अवरोध;
	हाल CS6:
		msg.lcr |= USA_DATABITS_6;
		अवरोध;
	हाल CS7:
		msg.lcr |= USA_DATABITS_7;
		अवरोध;
	हाल CS8:
		msg.lcr |= USA_DATABITS_8;
		अवरोध;
	पूर्ण
	अगर (p_priv->cflag & PARENB) अणु
		/* note USA_PARITY_NONE == 0 */
		msg.lcr |= (p_priv->cflag & PARODD) ?
			USA_PARITY_ODD : USA_PARITY_EVEN;
	पूर्ण
	अगर (p_priv->old_cflag != p_priv->cflag) अणु
		p_priv->old_cflag = p_priv->cflag;
		msg.setLcr = 0x01;
	पूर्ण

	अगर (p_priv->flow_control == flow_cts)
		msg.txFlowControl = TXFLOW_CTS;
	msg.setTxFlowControl = 0x01;
	msg.setRxFlowControl = 0x01;

	msg.rxForwardingLength = 16;
	msg.rxForwardingTimeout = 16;
	msg.txAckSetting = 0;
	msg.xonChar = 17;
	msg.xoffChar = 19;

	/* Opening port */
	अगर (reset_port == 1) अणु
		msg.portEnabled = 1;
		msg.rxFlush = 1;
		msg.txBreak = (p_priv->अवरोध_on);
	पूर्ण
	/* Closing port */
	अन्यथा अगर (reset_port == 2)
		msg.portEnabled = 0;
	/* Sending पूर्णांकermediate configs */
	अन्यथा अणु
		msg.portEnabled = 1;
		msg.txBreak = (p_priv->अवरोध_on);
	पूर्ण

	/* Do handshaking outमाला_दो */
	msg.setRts = 0x01;
	msg.rts = p_priv->rts_state;

	msg.setDtr = 0x01;
	msg.dtr = p_priv->dtr_state;

	p_priv->resend_cont = 0;
	स_नकल(this_urb->transfer_buffer, &msg, माप(msg));

	/* send the data out the device on control endpoपूर्णांक */
	this_urb->transfer_buffer_length = माप(msg);

	err = usb_submit_urb(this_urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - usb_submit_urb(setup) failed (%d)\n", __func__, err);
	वापस 0;
पूर्ण

अटल पूर्णांक keyspan_usa67_send_setup(काष्ठा usb_serial *serial,
				    काष्ठा usb_serial_port *port,
				    पूर्णांक reset_port)
अणु
	काष्ठा keyspan_usa67_portControlMessage	msg;
	काष्ठा keyspan_serial_निजी 		*s_priv;
	काष्ठा keyspan_port_निजी 		*p_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;
	काष्ठा urb				*this_urb;
	पूर्णांक 					err, device_port;

	s_priv = usb_get_serial_data(serial);
	p_priv = usb_get_serial_port_data(port);
	d_details = s_priv->device_details;

	this_urb = s_priv->glocont_urb;

	/* Work out which port within the device is being setup */
	device_port = port->port_number;

	/* Make sure we have an urb then send the message */
	अगर (this_urb == शून्य) अणु
		dev_dbg(&port->dev, "%s - oops no urb for port.\n", __func__);
		वापस -1;
	पूर्ण

	/* Save reset port val क्रम resend.
	   Don't overग_लिखो resend क्रम खोलो/बंद condition. */
	अगर ((reset_port + 1) > p_priv->resend_cont)
		p_priv->resend_cont = reset_port + 1;
	अगर (this_urb->status == -EINPROGRESS) अणु
		/*  dev_dbg(&port->dev, "%s - already writing\n", __func__); */
		mdelay(5);
		वापस -1;
	पूर्ण

	स_रखो(&msg, 0, माप(काष्ठा keyspan_usa67_portControlMessage));

	msg.port = device_port;

	/* Only set baud rate अगर it's changed */
	अगर (p_priv->old_baud != p_priv->baud) अणु
		p_priv->old_baud = p_priv->baud;
		msg.setClocking = 0xff;
		अगर (d_details->calculate_baud_rate(port, p_priv->baud, d_details->baudclk,
						   &msg.baudHi, &msg.baudLo, &msg.prescaler,
						   device_port) == KEYSPAN_INVALID_BAUD_RATE) अणु
			dev_dbg(&port->dev, "%s - Invalid baud rate %d requested, using 9600.\n",
				__func__, p_priv->baud);
			msg.baudLo = 0;
			msg.baudHi = 125;	/* Values क्रम 9600 baud */
			msg.prescaler = 10;
		पूर्ण
		msg.setPrescaler = 0xff;
	पूर्ण

	msg.lcr = (p_priv->cflag & CSTOPB) ? STOPBITS_678_2 : STOPBITS_5678_1;
	चयन (p_priv->cflag & CSIZE) अणु
	हाल CS5:
		msg.lcr |= USA_DATABITS_5;
		अवरोध;
	हाल CS6:
		msg.lcr |= USA_DATABITS_6;
		अवरोध;
	हाल CS7:
		msg.lcr |= USA_DATABITS_7;
		अवरोध;
	हाल CS8:
		msg.lcr |= USA_DATABITS_8;
		अवरोध;
	पूर्ण
	अगर (p_priv->cflag & PARENB) अणु
		/* note USA_PARITY_NONE == 0 */
		msg.lcr |= (p_priv->cflag & PARODD) ?
					USA_PARITY_ODD : USA_PARITY_EVEN;
	पूर्ण
	msg.setLcr = 0xff;

	msg.ctsFlowControl = (p_priv->flow_control == flow_cts);
	msg.xonFlowControl = 0;
	msg.setFlowControl = 0xff;
	msg.क्रमwardingLength = 16;
	msg.xonChar = 17;
	msg.xoffChar = 19;

	अगर (reset_port == 1) अणु
		/* Opening port */
		msg._txOn = 1;
		msg._txOff = 0;
		msg.txFlush = 0;
		msg.txBreak = 0;
		msg.rxOn = 1;
		msg.rxOff = 0;
		msg.rxFlush = 1;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0xff;
	पूर्ण अन्यथा अगर (reset_port == 2) अणु
		/* Closing port */
		msg._txOn = 0;
		msg._txOff = 1;
		msg.txFlush = 0;
		msg.txBreak = 0;
		msg.rxOn = 0;
		msg.rxOff = 1;
		msg.rxFlush = 1;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0;
	पूर्ण अन्यथा अणु
		/* Sending पूर्णांकermediate configs */
		msg._txOn = (!p_priv->अवरोध_on);
		msg._txOff = 0;
		msg.txFlush = 0;
		msg.txBreak = (p_priv->अवरोध_on);
		msg.rxOn = 0;
		msg.rxOff = 0;
		msg.rxFlush = 0;
		msg.rxForward = 0;
		msg.वापसStatus = 0;
		msg.resetDataToggle = 0x0;
	पूर्ण

	/* Do handshaking outमाला_दो */
	msg.setTxTriState_setRts = 0xff;
	msg.txTriState_rts = p_priv->rts_state;

	msg.setHskoa_setDtr = 0xff;
	msg.hskoa_dtr = p_priv->dtr_state;

	p_priv->resend_cont = 0;

	स_नकल(this_urb->transfer_buffer, &msg, माप(msg));

	/* send the data out the device on control endpoपूर्णांक */
	this_urb->transfer_buffer_length = माप(msg);

	err = usb_submit_urb(this_urb, GFP_ATOMIC);
	अगर (err != 0)
		dev_dbg(&port->dev, "%s - usb_submit_urb(setup) failed (%d)\n", __func__, err);
	वापस 0;
पूर्ण

अटल व्योम keyspan_send_setup(काष्ठा usb_serial_port *port, पूर्णांक reset_port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा keyspan_serial_निजी *s_priv;
	स्थिर काष्ठा keyspan_device_details *d_details;

	s_priv = usb_get_serial_data(serial);
	d_details = s_priv->device_details;

	चयन (d_details->msg_क्रमmat) अणु
	हाल msg_usa26:
		keyspan_usa26_send_setup(serial, port, reset_port);
		अवरोध;
	हाल msg_usa28:
		keyspan_usa28_send_setup(serial, port, reset_port);
		अवरोध;
	हाल msg_usa49:
		keyspan_usa49_send_setup(serial, port, reset_port);
		अवरोध;
	हाल msg_usa90:
		keyspan_usa90_send_setup(serial, port, reset_port);
		अवरोध;
	हाल msg_usa67:
		keyspan_usa67_send_setup(serial, port, reset_port);
		अवरोध;
	पूर्ण
पूर्ण


/* Gets called by the "real" driver (ie once firmware is loaded
   and rक्रमागतeration has taken place. */
अटल पूर्णांक keyspan_startup(काष्ठा usb_serial *serial)
अणु
	पूर्णांक				i, err;
	काष्ठा keyspan_serial_निजी 	*s_priv;
	स्थिर काष्ठा keyspan_device_details	*d_details;

	क्रम (i = 0; (d_details = keyspan_devices[i]) != शून्य; ++i)
		अगर (d_details->product_id ==
				le16_to_cpu(serial->dev->descriptor.idProduct))
			अवरोध;
	अगर (d_details == शून्य) अणु
		dev_err(&serial->dev->dev, "%s - unknown product id %x\n",
		    __func__, le16_to_cpu(serial->dev->descriptor.idProduct));
		वापस -ENODEV;
	पूर्ण

	/* Setup निजी data क्रम serial driver */
	s_priv = kzalloc(माप(काष्ठा keyspan_serial_निजी), GFP_KERNEL);
	अगर (!s_priv)
		वापस -ENOMEM;

	s_priv->instat_buf = kzalloc(INSTAT_BUFLEN, GFP_KERNEL);
	अगर (!s_priv->instat_buf)
		जाओ err_instat_buf;

	s_priv->indat_buf = kzalloc(INDAT49W_BUFLEN, GFP_KERNEL);
	अगर (!s_priv->indat_buf)
		जाओ err_indat_buf;

	s_priv->glocont_buf = kzalloc(GLOCONT_BUFLEN, GFP_KERNEL);
	अगर (!s_priv->glocont_buf)
		जाओ err_glocont_buf;

	s_priv->ctrl_buf = kzalloc(माप(काष्ठा usb_ctrlrequest), GFP_KERNEL);
	अगर (!s_priv->ctrl_buf)
		जाओ err_ctrl_buf;

	s_priv->device_details = d_details;
	usb_set_serial_data(serial, s_priv);

	keyspan_setup_urbs(serial);

	अगर (s_priv->instat_urb != शून्य) अणु
		err = usb_submit_urb(s_priv->instat_urb, GFP_KERNEL);
		अगर (err != 0)
			dev_dbg(&serial->dev->dev, "%s - submit instat urb failed %d\n", __func__, err);
	पूर्ण
	अगर (s_priv->indat_urb != शून्य) अणु
		err = usb_submit_urb(s_priv->indat_urb, GFP_KERNEL);
		अगर (err != 0)
			dev_dbg(&serial->dev->dev, "%s - submit indat urb failed %d\n", __func__, err);
	पूर्ण

	वापस 0;

err_ctrl_buf:
	kमुक्त(s_priv->glocont_buf);
err_glocont_buf:
	kमुक्त(s_priv->indat_buf);
err_indat_buf:
	kमुक्त(s_priv->instat_buf);
err_instat_buf:
	kमुक्त(s_priv);

	वापस -ENOMEM;
पूर्ण

अटल व्योम keyspan_disconnect(काष्ठा usb_serial *serial)
अणु
	काष्ठा keyspan_serial_निजी *s_priv;

	s_priv = usb_get_serial_data(serial);

	usb_समाप्त_urb(s_priv->instat_urb);
	usb_समाप्त_urb(s_priv->glocont_urb);
	usb_समाप्त_urb(s_priv->indat_urb);
पूर्ण

अटल व्योम keyspan_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा keyspan_serial_निजी *s_priv;

	s_priv = usb_get_serial_data(serial);

	/* Make sure to unlink the URBs submitted in attach. */
	usb_समाप्त_urb(s_priv->instat_urb);
	usb_समाप्त_urb(s_priv->indat_urb);

	usb_मुक्त_urb(s_priv->instat_urb);
	usb_मुक्त_urb(s_priv->indat_urb);
	usb_मुक्त_urb(s_priv->glocont_urb);

	kमुक्त(s_priv->ctrl_buf);
	kमुक्त(s_priv->glocont_buf);
	kमुक्त(s_priv->indat_buf);
	kमुक्त(s_priv->instat_buf);

	kमुक्त(s_priv);
पूर्ण

अटल पूर्णांक keyspan_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा keyspan_serial_निजी *s_priv;
	काष्ठा keyspan_port_निजी *p_priv;
	स्थिर काष्ठा keyspan_device_details *d_details;
	काष्ठा callbacks *cback;
	पूर्णांक endp;
	पूर्णांक port_num;
	पूर्णांक i;

	s_priv = usb_get_serial_data(serial);
	d_details = s_priv->device_details;

	p_priv = kzalloc(माप(*p_priv), GFP_KERNEL);
	अगर (!p_priv)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(p_priv->in_buffer); ++i) अणु
		p_priv->in_buffer[i] = kzalloc(IN_BUFLEN, GFP_KERNEL);
		अगर (!p_priv->in_buffer[i])
			जाओ err_in_buffer;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(p_priv->out_buffer); ++i) अणु
		p_priv->out_buffer[i] = kzalloc(OUT_BUFLEN, GFP_KERNEL);
		अगर (!p_priv->out_buffer[i])
			जाओ err_out_buffer;
	पूर्ण

	p_priv->inack_buffer = kzalloc(INACK_BUFLEN, GFP_KERNEL);
	अगर (!p_priv->inack_buffer)
		जाओ err_inack_buffer;

	p_priv->outcont_buffer = kzalloc(OUTCONT_BUFLEN, GFP_KERNEL);
	अगर (!p_priv->outcont_buffer)
		जाओ err_outcont_buffer;

	p_priv->device_details = d_details;

	/* Setup values क्रम the various callback routines */
	cback = &keyspan_callbacks[d_details->msg_क्रमmat];

	port_num = port->port_number;

	/* Do indat endpoपूर्णांकs first, once क्रम each flip */
	endp = d_details->indat_endpoपूर्णांकs[port_num];
	क्रम (i = 0; i <= d_details->indat_endp_flip; ++i, ++endp) अणु
		p_priv->in_urbs[i] = keyspan_setup_urb(serial, endp,
						USB_सूची_IN, port,
						p_priv->in_buffer[i],
						IN_BUFLEN,
						cback->indat_callback);
	पूर्ण
	/* outdat endpoपूर्णांकs also have flip */
	endp = d_details->outdat_endpoपूर्णांकs[port_num];
	क्रम (i = 0; i <= d_details->outdat_endp_flip; ++i, ++endp) अणु
		p_priv->out_urbs[i] = keyspan_setup_urb(serial, endp,
						USB_सूची_OUT, port,
						p_priv->out_buffer[i],
						OUT_BUFLEN,
						cback->outdat_callback);
	पूर्ण
	/* inack endpoपूर्णांक */
	p_priv->inack_urb = keyspan_setup_urb(serial,
					d_details->inack_endpoपूर्णांकs[port_num],
					USB_सूची_IN, port,
					p_priv->inack_buffer,
					INACK_BUFLEN,
					cback->inack_callback);
	/* outcont endpoपूर्णांक */
	p_priv->outcont_urb = keyspan_setup_urb(serial,
					d_details->outcont_endpoपूर्णांकs[port_num],
					USB_सूची_OUT, port,
					p_priv->outcont_buffer,
					OUTCONT_BUFLEN,
					 cback->outcont_callback);

	usb_set_serial_port_data(port, p_priv);

	वापस 0;

err_outcont_buffer:
	kमुक्त(p_priv->inack_buffer);
err_inack_buffer:
	क्रम (i = 0; i < ARRAY_SIZE(p_priv->out_buffer); ++i)
		kमुक्त(p_priv->out_buffer[i]);
err_out_buffer:
	क्रम (i = 0; i < ARRAY_SIZE(p_priv->in_buffer); ++i)
		kमुक्त(p_priv->in_buffer[i]);
err_in_buffer:
	kमुक्त(p_priv);

	वापस -ENOMEM;
पूर्ण

अटल व्योम keyspan_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा keyspan_port_निजी *p_priv;
	पूर्णांक i;

	p_priv = usb_get_serial_port_data(port);

	usb_समाप्त_urb(p_priv->inack_urb);
	usb_समाप्त_urb(p_priv->outcont_urb);
	क्रम (i = 0; i < 2; i++) अणु
		usb_समाप्त_urb(p_priv->in_urbs[i]);
		usb_समाप्त_urb(p_priv->out_urbs[i]);
	पूर्ण

	usb_मुक्त_urb(p_priv->inack_urb);
	usb_मुक्त_urb(p_priv->outcont_urb);
	क्रम (i = 0; i < 2; i++) अणु
		usb_मुक्त_urb(p_priv->in_urbs[i]);
		usb_मुक्त_urb(p_priv->out_urbs[i]);
	पूर्ण

	kमुक्त(p_priv->outcont_buffer);
	kमुक्त(p_priv->inack_buffer);
	क्रम (i = 0; i < ARRAY_SIZE(p_priv->out_buffer); ++i)
		kमुक्त(p_priv->out_buffer[i]);
	क्रम (i = 0; i < ARRAY_SIZE(p_priv->in_buffer); ++i)
		kमुक्त(p_priv->in_buffer[i]);

	kमुक्त(p_priv);
पूर्ण

/* Structs क्रम the devices, pre and post rक्रमागतeration. */
अटल काष्ठा usb_serial_driver keyspan_pre_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "keyspan_no_firm",
	पूर्ण,
	.description		= "Keyspan - (without firmware)",
	.id_table		= keyspan_pre_ids,
	.num_ports		= 1,
	.attach			= keyspan_fake_startup,
पूर्ण;

अटल काष्ठा usb_serial_driver keyspan_1port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "keyspan_1",
	पूर्ण,
	.description		= "Keyspan 1 port adapter",
	.id_table		= keyspan_1port_ids,
	.num_ports		= 1,
	.खोलो			= keyspan_खोलो,
	.बंद			= keyspan_बंद,
	.dtr_rts		= keyspan_dtr_rts,
	.ग_लिखो			= keyspan_ग_लिखो,
	.ग_लिखो_room		= keyspan_ग_लिखो_room,
	.set_termios		= keyspan_set_termios,
	.अवरोध_ctl		= keyspan_अवरोध_ctl,
	.tiocmget		= keyspan_tiocmget,
	.tiocmset		= keyspan_tiocmset,
	.attach			= keyspan_startup,
	.disconnect		= keyspan_disconnect,
	.release		= keyspan_release,
	.port_probe		= keyspan_port_probe,
	.port_हटाओ		= keyspan_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver keyspan_2port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "keyspan_2",
	पूर्ण,
	.description		= "Keyspan 2 port adapter",
	.id_table		= keyspan_2port_ids,
	.num_ports		= 2,
	.खोलो			= keyspan_खोलो,
	.बंद			= keyspan_बंद,
	.dtr_rts		= keyspan_dtr_rts,
	.ग_लिखो			= keyspan_ग_लिखो,
	.ग_लिखो_room		= keyspan_ग_लिखो_room,
	.set_termios		= keyspan_set_termios,
	.अवरोध_ctl		= keyspan_अवरोध_ctl,
	.tiocmget		= keyspan_tiocmget,
	.tiocmset		= keyspan_tiocmset,
	.attach			= keyspan_startup,
	.disconnect		= keyspan_disconnect,
	.release		= keyspan_release,
	.port_probe		= keyspan_port_probe,
	.port_हटाओ		= keyspan_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver keyspan_4port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "keyspan_4",
	पूर्ण,
	.description		= "Keyspan 4 port adapter",
	.id_table		= keyspan_4port_ids,
	.num_ports		= 4,
	.खोलो			= keyspan_खोलो,
	.बंद			= keyspan_बंद,
	.dtr_rts		= keyspan_dtr_rts,
	.ग_लिखो			= keyspan_ग_लिखो,
	.ग_लिखो_room		= keyspan_ग_लिखो_room,
	.set_termios		= keyspan_set_termios,
	.अवरोध_ctl		= keyspan_अवरोध_ctl,
	.tiocmget		= keyspan_tiocmget,
	.tiocmset		= keyspan_tiocmset,
	.attach			= keyspan_startup,
	.disconnect		= keyspan_disconnect,
	.release		= keyspan_release,
	.port_probe		= keyspan_port_probe,
	.port_हटाओ		= keyspan_port_हटाओ,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&keyspan_pre_device, &keyspan_1port_device,
	&keyspan_2port_device, &keyspan_4port_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, keyspan_ids_combined);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

MODULE_FIRMWARE("keyspan/usa28.fw");
MODULE_FIRMWARE("keyspan/usa28x.fw");
MODULE_FIRMWARE("keyspan/usa28xa.fw");
MODULE_FIRMWARE("keyspan/usa28xb.fw");
MODULE_FIRMWARE("keyspan/usa19.fw");
MODULE_FIRMWARE("keyspan/usa19qi.fw");
MODULE_FIRMWARE("keyspan/mpr.fw");
MODULE_FIRMWARE("keyspan/usa19qw.fw");
MODULE_FIRMWARE("keyspan/usa18x.fw");
MODULE_FIRMWARE("keyspan/usa19w.fw");
MODULE_FIRMWARE("keyspan/usa49w.fw");
MODULE_FIRMWARE("keyspan/usa49wlc.fw");

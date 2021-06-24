<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver definitions क्रम the FTDI USB Single Port Serial Converter -
 * known as FTDI_SIO (Serial Input/Output application of the chipset)
 *
 * For USB venकरोr/product IDs (VID/PID), please see ftdi_sio_ids.h
 *
 *
 * The example I have is known as the USC-1000 which is available from
 * http://www.dse.co.nz - cat no XH4214 It looks similar to this:
 * http://www.dansdata.com/usbser.hपंचांग but I can't be sure There are other
 * USC-1000s which करोn't look like my device though so beware!
 *
 * The device is based on the FTDI FT8U100AX chip. It has a DB25 on one side,
 * USB on the other.
 *
 * Thanx to FTDI (http://www.ftdichip.com) क्रम so kindly providing details
 * of the protocol required to talk to the device and ongoing assistence
 * during development.
 *
 * Bill Ryder - bryder@sgi.com क्रमmerly of Silicon Graphics, Inc.- wrote the
 * FTDI_SIO implementation.
 *
 */

/* Commands */
#घोषणा FTDI_SIO_RESET			0 /* Reset the port */
#घोषणा FTDI_SIO_MODEM_CTRL		1 /* Set the modem control रेजिस्टर */
#घोषणा FTDI_SIO_SET_FLOW_CTRL		2 /* Set flow control रेजिस्टर */
#घोषणा FTDI_SIO_SET_BAUD_RATE		3 /* Set baud rate */
#घोषणा FTDI_SIO_SET_DATA		4 /* Set the data अक्षरacteristics of
					     the port */
#घोषणा FTDI_SIO_GET_MODEM_STATUS	5 /* Retrieve current value of modem
					     status रेजिस्टर */
#घोषणा FTDI_SIO_SET_EVENT_CHAR		6 /* Set the event अक्षरacter */
#घोषणा FTDI_SIO_SET_ERROR_CHAR		7 /* Set the error अक्षरacter */
#घोषणा FTDI_SIO_SET_LATENCY_TIMER	9 /* Set the latency समयr */
#घोषणा FTDI_SIO_GET_LATENCY_TIMER	0x0a /* Get the latency समयr */
#घोषणा FTDI_SIO_SET_BITMODE		0x0b /* Set bitbang mode */
#घोषणा FTDI_SIO_READ_PINS		0x0c /* Read immediate value of pins */
#घोषणा FTDI_SIO_READ_EEPROM		0x90 /* Read EEPROM */

/* Interface indices क्रम FT2232, FT2232H and FT4232H devices */
#घोषणा INTERFACE_A		1
#घोषणा INTERFACE_B		2
#घोषणा INTERFACE_C		3
#घोषणा INTERFACE_D		4


/*
 *   BmRequestType:  1100 0000b
 *   bRequest:       FTDI_E2_READ
 *   wValue:         0
 *   wIndex:         Address of word to पढ़ो
 *   wLength:        2
 *   Data:           Will वापस a word of data from E2Address
 *
 */

/* Port Identअगरier Table */
#घोषणा PIT_DEFAULT		0 /* SIOA */
#घोषणा PIT_SIOA		1 /* SIOA */
/* The device this driver is tested with one has only one port */
#घोषणा PIT_SIOB		2 /* SIOB */
#घोषणा PIT_PARALLEL		3 /* Parallel */

/* FTDI_SIO_RESET */
#घोषणा FTDI_SIO_RESET_REQUEST FTDI_SIO_RESET
#घोषणा FTDI_SIO_RESET_REQUEST_TYPE 0x40
#घोषणा FTDI_SIO_RESET_SIO 0
#घोषणा FTDI_SIO_RESET_PURGE_RX 1
#घोषणा FTDI_SIO_RESET_PURGE_TX 2

/*
 * BmRequestType:  0100 0000B
 * bRequest:       FTDI_SIO_RESET
 * wValue:         Control Value
 *                   0 = Reset SIO
 *                   1 = Purge RX buffer
 *                   2 = Purge TX buffer
 * wIndex:         Port
 * wLength:        0
 * Data:           None
 *
 * The Reset SIO command has this effect:
 *
 *    Sets flow control set to 'none'
 *    Event अक्षर = $0D
 *    Event trigger = disabled
 *    Purge RX buffer
 *    Purge TX buffer
 *    Clear DTR
 *    Clear RTS
 *    baud and data क्रमmat not reset
 *
 * The Purge RX and TX buffer commands affect nothing except the buffers
 *
   */

/* FTDI_SIO_SET_BAUDRATE */
#घोषणा FTDI_SIO_SET_BAUDRATE_REQUEST_TYPE 0x40
#घोषणा FTDI_SIO_SET_BAUDRATE_REQUEST 3

/*
 * BmRequestType:  0100 0000B
 * bRequest:       FTDI_SIO_SET_BAUDRATE
 * wValue:         BaudDivisor value - see below
 * wIndex:         Port
 * wLength:        0
 * Data:           None
 * The BaudDivisor values are calculated as follows:
 * - BaseClock is either 12000000 or 48000000 depending on the device.
 *   FIXME: I wish I knew how to detect old chips to select proper base घड़ी!
 * - BaudDivisor is a fixed poपूर्णांक number encoded in a funny way.
 *   (--WRONG WAY OF THINKING--)
 *   BaudDivisor is a fixed poपूर्णांक number encoded with following bit weighs:
 *   (-2)(-1)(13..0). It is a radical with a denominator of 4, so values
 *   end with 0.0 (00...), 0.25 (10...), 0.5 (01...), and 0.75 (11...).
 *   (--THE REALITY--)
 *   The both-bits-set has quite dअगरferent meaning from 0.75 - the chip
 *   designers have decided it to mean 0.125 instead of 0.75.
 *   This info looked up in FTDI application note "FT8U232 DEVICES \ Data Rates
 *   and Flow Control Consideration क्रम USB to RS232".
 * - BaudDivisor = (BaseClock / 16) / BaudRate, where the (=) operation should
 *   स्वतःmagically re-encode the resulting value to take fractions पूर्णांकo
 *   consideration.
 * As all values are पूर्णांकegers, some bit twiddling is in order:
 *   BaudDivisor = (BaseClock / 16 / BaudRate) |
 *   (((BaseClock / 2 / BaudRate) & 4) ? 0x4000    // 0.5
 *    : ((BaseClock / 2 / BaudRate) & 2) ? 0x8000  // 0.25
 *    : ((BaseClock / 2 / BaudRate) & 1) ? 0xc000  // 0.125
 *    : 0)
 *
 * For the FT232BM, a 17th भागisor bit was पूर्णांकroduced to encode the multiples
 * of 0.125 missing from the FT8U232AM.  Bits 16 to 14 are coded as follows
 * (the first four codes are the same as क्रम the FT8U232AM, where bit 16 is
 * always 0):
 *   000 - add .000 to भागisor
 *   001 - add .500 to भागisor
 *   010 - add .250 to भागisor
 *   011 - add .125 to भागisor
 *   100 - add .375 to भागisor
 *   101 - add .625 to भागisor
 *   110 - add .750 to भागisor
 *   111 - add .875 to भागisor
 * Bits 15 to 0 of the 17-bit भागisor are placed in the urb value.  Bit 16 is
 * placed in bit 0 of the urb index.
 *
 * Note that there are a couple of special हालs to support the highest baud
 * rates.  If the calculated भागisor value is 1, this needs to be replaced with
 * 0.  Additionally क्रम the FT232BM, अगर the calculated भागisor value is 0x4001
 * (1.5), this needs to be replaced with 0x0001 (1) (but this भागisor value is
 * not supported by the FT8U232AM).
 */

क्रमागत ftdi_chip_type अणु
	SIO = 1,
	FT8U232AM = 2,
	FT232BM = 3,
	FT2232C = 4,
	FT232RL = 5,
	FT2232H = 6,
	FT4232H = 7,
	FT232H  = 8,
	FTX     = 9,
पूर्ण;

क्रमागत ftdi_sio_baudrate अणु
	ftdi_sio_b300 = 0,
	ftdi_sio_b600 = 1,
	ftdi_sio_b1200 = 2,
	ftdi_sio_b2400 = 3,
	ftdi_sio_b4800 = 4,
	ftdi_sio_b9600 = 5,
	ftdi_sio_b19200 = 6,
	ftdi_sio_b38400 = 7,
	ftdi_sio_b57600 = 8,
	ftdi_sio_b115200 = 9
पूर्ण;

/*
 * The ftdi_8U232AM_xxMHz_byyy स्थिरants have been हटाओd. The encoded भागisor
 * values are calculated पूर्णांकernally.
 */
#घोषणा FTDI_SIO_SET_DATA_REQUEST	FTDI_SIO_SET_DATA
#घोषणा FTDI_SIO_SET_DATA_REQUEST_TYPE	0x40
#घोषणा FTDI_SIO_SET_DATA_PARITY_NONE	(0x0 << 8)
#घोषणा FTDI_SIO_SET_DATA_PARITY_ODD	(0x1 << 8)
#घोषणा FTDI_SIO_SET_DATA_PARITY_EVEN	(0x2 << 8)
#घोषणा FTDI_SIO_SET_DATA_PARITY_MARK	(0x3 << 8)
#घोषणा FTDI_SIO_SET_DATA_PARITY_SPACE	(0x4 << 8)
#घोषणा FTDI_SIO_SET_DATA_STOP_BITS_1	(0x0 << 11)
#घोषणा FTDI_SIO_SET_DATA_STOP_BITS_15	(0x1 << 11)
#घोषणा FTDI_SIO_SET_DATA_STOP_BITS_2	(0x2 << 11)
#घोषणा FTDI_SIO_SET_BREAK		(0x1 << 14)
/* FTDI_SIO_SET_DATA */

/*
 * BmRequestType:  0100 0000B
 * bRequest:       FTDI_SIO_SET_DATA
 * wValue:         Data अक्षरacteristics (see below)
 * wIndex:         Port
 * wLength:        0
 * Data:           No
 *
 * Data अक्षरacteristics
 *
 *   B0..7   Number of data bits
 *   B8..10  Parity
 *           0 = None
 *           1 = Odd
 *           2 = Even
 *           3 = Mark
 *           4 = Space
 *   B11..13 Stop Bits
 *           0 = 1
 *           1 = 1.5
 *           2 = 2
 *   B14
 *           1 = TX ON (अवरोध)
 *           0 = TX OFF (normal state)
 *   B15 Reserved
 *
 */



/* FTDI_SIO_MODEM_CTRL */
#घोषणा FTDI_SIO_SET_MODEM_CTRL_REQUEST_TYPE 0x40
#घोषणा FTDI_SIO_SET_MODEM_CTRL_REQUEST FTDI_SIO_MODEM_CTRL

/*
 * BmRequestType:   0100 0000B
 * bRequest:        FTDI_SIO_MODEM_CTRL
 * wValue:          ControlValue (see below)
 * wIndex:          Port
 * wLength:         0
 * Data:            None
 *
 * NOTE: If the device is in RTS/CTS flow control, the RTS set by this
 * command will be IGNORED without an error being वापसed
 * Also - you can not set DTR and RTS with one control message
 */

#घोषणा FTDI_SIO_SET_DTR_MASK 0x1
#घोषणा FTDI_SIO_SET_DTR_HIGH ((FTDI_SIO_SET_DTR_MASK  << 8) | 1)
#घोषणा FTDI_SIO_SET_DTR_LOW  ((FTDI_SIO_SET_DTR_MASK  << 8) | 0)
#घोषणा FTDI_SIO_SET_RTS_MASK 0x2
#घोषणा FTDI_SIO_SET_RTS_HIGH ((FTDI_SIO_SET_RTS_MASK << 8) | 2)
#घोषणा FTDI_SIO_SET_RTS_LOW  ((FTDI_SIO_SET_RTS_MASK << 8) | 0)

/*
 * ControlValue
 * B0    DTR state
 *          0 = reset
 *          1 = set
 * B1    RTS state
 *          0 = reset
 *          1 = set
 * B2..7 Reserved
 * B8    DTR state enable
 *          0 = ignore
 *          1 = use DTR state
 * B9    RTS state enable
 *          0 = ignore
 *          1 = use RTS state
 * B10..15 Reserved
 */

/* FTDI_SIO_SET_FLOW_CTRL */
#घोषणा FTDI_SIO_SET_FLOW_CTRL_REQUEST_TYPE 0x40
#घोषणा FTDI_SIO_SET_FLOW_CTRL_REQUEST FTDI_SIO_SET_FLOW_CTRL
#घोषणा FTDI_SIO_DISABLE_FLOW_CTRL 0x0
#घोषणा FTDI_SIO_RTS_CTS_HS (0x1 << 8)
#घोषणा FTDI_SIO_DTR_DSR_HS (0x2 << 8)
#घोषणा FTDI_SIO_XON_XOFF_HS (0x4 << 8)
/*
 *   BmRequestType:  0100 0000b
 *   bRequest:       FTDI_SIO_SET_FLOW_CTRL
 *   wValue:         Xoff/Xon
 *   wIndex:         Protocol/Port - hIndex is protocol / lIndex is port
 *   wLength:        0
 *   Data:           None
 *
 * hIndex protocol is:
 *   B0 Output handshaking using RTS/CTS
 *       0 = disabled
 *       1 = enabled
 *   B1 Output handshaking using DTR/DSR
 *       0 = disabled
 *       1 = enabled
 *   B2 Xon/Xoff handshaking
 *       0 = disabled
 *       1 = enabled
 *
 * A value of zero in the hIndex field disables handshaking
 *
 * If Xon/Xoff handshaking is specअगरied, the hValue field should contain the
 * XOFF अक्षरacter and the lValue field contains the XON अक्षरacter.
 */

/*
 * FTDI_SIO_GET_LATENCY_TIMER
 *
 * Set the समयout पूर्णांकerval. The FTDI collects data from the
 * device, transmitting it to the host when either A) 62 bytes are
 * received, or B) the समयout पूर्णांकerval has elapsed and the buffer
 * contains at least 1 byte.  Setting this value to a small number
 * can dramatically improve perक्रमmance क्रम applications which send
 * small packets, since the शेष value is 16ms.
 */
#घोषणा  FTDI_SIO_GET_LATENCY_TIMER_REQUEST FTDI_SIO_GET_LATENCY_TIMER
#घोषणा  FTDI_SIO_GET_LATENCY_TIMER_REQUEST_TYPE 0xC0

/*
 *  BmRequestType:   1100 0000b
 *  bRequest:        FTDI_SIO_GET_LATENCY_TIMER
 *  wValue:          0
 *  wIndex:          Port
 *  wLength:         0
 *  Data:            latency (on वापस)
 */

/*
 * FTDI_SIO_SET_LATENCY_TIMER
 *
 * Set the समयout पूर्णांकerval. The FTDI collects data from the
 * device, transmitting it to the host when either A) 62 bytes are
 * received, or B) the समयout पूर्णांकerval has elapsed and the buffer
 * contains at least 1 byte.  Setting this value to a small number
 * can dramatically improve perक्रमmance क्रम applications which send
 * small packets, since the शेष value is 16ms.
 */
#घोषणा  FTDI_SIO_SET_LATENCY_TIMER_REQUEST FTDI_SIO_SET_LATENCY_TIMER
#घोषणा  FTDI_SIO_SET_LATENCY_TIMER_REQUEST_TYPE 0x40

/*
 *  BmRequestType:   0100 0000b
 *  bRequest:        FTDI_SIO_SET_LATENCY_TIMER
 *  wValue:          Latency (milliseconds)
 *  wIndex:          Port
 *  wLength:         0
 *  Data:            None
 *
 * wValue:
 *   B0..7   Latency समयr
 *   B8..15  0
 *
 */

/*
 * FTDI_SIO_SET_EVENT_CHAR
 *
 * Set the special event अक्षरacter क्रम the specअगरied communications port.
 * If the device sees this अक्षरacter it will immediately वापस the
 * data पढ़ो so far - rather than रुको 40ms or until 62 bytes are पढ़ो
 * which is what normally happens.
 */


#घोषणा  FTDI_SIO_SET_EVENT_CHAR_REQUEST FTDI_SIO_SET_EVENT_CHAR
#घोषणा  FTDI_SIO_SET_EVENT_CHAR_REQUEST_TYPE 0x40


/*
 *  BmRequestType:   0100 0000b
 *  bRequest:        FTDI_SIO_SET_EVENT_CHAR
 *  wValue:          EventChar
 *  wIndex:          Port
 *  wLength:         0
 *  Data:            None
 *
 * wValue:
 *   B0..7   Event Character
 *   B8      Event Character Processing
 *             0 = disabled
 *             1 = enabled
 *   B9..15  Reserved
 *
 */

/* FTDI_SIO_SET_ERROR_CHAR */

/*
 * Set the parity error replacement अक्षरacter क्रम the specअगरied communications
 * port
 */

/*
 *  BmRequestType:  0100 0000b
 *  bRequest:       FTDI_SIO_SET_EVENT_CHAR
 *  wValue:         Error Char
 *  wIndex:         Port
 *  wLength:        0
 *  Data:           None
 *
 *Error Char
 *  B0..7  Error Character
 *  B8     Error Character Processing
 *           0 = disabled
 *           1 = enabled
 *  B9..15 Reserved
 *
 */

/* FTDI_SIO_GET_MODEM_STATUS */
/* Retrieve the current value of the modem status रेजिस्टर */

#घोषणा FTDI_SIO_GET_MODEM_STATUS_REQUEST_TYPE 0xc0
#घोषणा FTDI_SIO_GET_MODEM_STATUS_REQUEST FTDI_SIO_GET_MODEM_STATUS
#घोषणा FTDI_SIO_CTS_MASK 0x10
#घोषणा FTDI_SIO_DSR_MASK 0x20
#घोषणा FTDI_SIO_RI_MASK  0x40
#घोषणा FTDI_SIO_RLSD_MASK 0x80
/*
 *   BmRequestType:   1100 0000b
 *   bRequest:        FTDI_SIO_GET_MODEM_STATUS
 *   wValue:          zero
 *   wIndex:          Port
 *   wLength:         1
 *   Data:            Status
 *
 * One byte of data is वापसed
 * B0..3 0
 * B4    CTS
 *         0 = inactive
 *         1 = active
 * B5    DSR
 *         0 = inactive
 *         1 = active
 * B6    Ring Indicator (RI)
 *         0 = inactive
 *         1 = active
 * B7    Receive Line Signal Detect (RLSD)
 *         0 = inactive
 *         1 = active
 */

/* FTDI_SIO_SET_BITMODE */
#घोषणा FTDI_SIO_SET_BITMODE_REQUEST_TYPE 0x40
#घोषणा FTDI_SIO_SET_BITMODE_REQUEST FTDI_SIO_SET_BITMODE

/* Possible biपंचांगodes क्रम FTDI_SIO_SET_BITMODE_REQUEST */
#घोषणा FTDI_SIO_BITMODE_RESET		0x00
#घोषणा FTDI_SIO_BITMODE_CBUS		0x20

/* FTDI_SIO_READ_PINS */
#घोषणा FTDI_SIO_READ_PINS_REQUEST_TYPE 0xc0
#घोषणा FTDI_SIO_READ_PINS_REQUEST FTDI_SIO_READ_PINS

/*
 * FTDI_SIO_READ_EEPROM
 *
 * EEPROM क्रमmat found in FTDI AN_201, "FT-X MTP memory Configuration",
 * http://www.ftdichip.com/Support/Documents/AppNotes/AN_201_FT-X%20MTP%20Memory%20Configuration.pdf
 */
#घोषणा FTDI_SIO_READ_EEPROM_REQUEST_TYPE 0xc0
#घोषणा FTDI_SIO_READ_EEPROM_REQUEST FTDI_SIO_READ_EEPROM

#घोषणा FTDI_FTX_CBUS_MUX_GPIO		0x8
#घोषणा FTDI_FT232R_CBUS_MUX_GPIO	0xa


/* Descriptors वापसed by the device
 *
 *  Device Descriptor
 *
 * Offset	Field		Size	Value	Description
 * 0	bLength		1	0x12	Size of descriptor in bytes
 * 1	bDescriptorType	1	0x01	DEVICE Descriptor Type
 * 2	bcdUSB		2	0x0110	USB Spec Release Number
 * 4	bDeviceClass	1	0x00	Class Code
 * 5	bDeviceSubClass	1	0x00	SubClass Code
 * 6	bDeviceProtocol	1	0x00	Protocol Code
 * 7	bMaxPacketSize0 1	0x08	Maximum packet size क्रम endpoपूर्णांक 0
 * 8	idVenकरोr	2	0x0403	Venकरोr ID
 * 10	idProduct	2	0x8372	Product ID (FTDI_SIO_PID)
 * 12	bcdDevice	2	0x0001	Device release number
 * 14	iManufacturer	1	0x01	Index of man. string desc
 * 15	iProduct	1	0x02	Index of prod string desc
 * 16	iSerialNumber	1	0x02	Index of serial nmr string desc
 * 17	bNumConfigurations 1    0x01	Number of possible configurations
 *
 * Configuration Descriptor
 *
 * Offset	Field			Size	Value
 * 0	bLength			1	0x09	Size of descriptor in bytes
 * 1	bDescriptorType		1	0x02	CONFIGURATION Descriptor Type
 * 2	wTotalLength		2	0x0020	Total length of data
 * 4	bNumInterfaces		1	0x01	Number of पूर्णांकerfaces supported
 * 5	bConfigurationValue	1	0x01	Argument क्रम SetCOnfiguration() req
 * 6	iConfiguration		1	0x02	Index of config string descriptor
 * 7	bmAttributes		1	0x20	Config अक्षरacteristics Remote Wakeup
 * 8	MaxPower		1	0x1E	Max घातer consumption
 *
 * Interface Descriptor
 *
 * Offset	Field			Size	Value
 * 0	bLength			1	0x09	Size of descriptor in bytes
 * 1	bDescriptorType		1	0x04	INTERFACE Descriptor Type
 * 2	bInterfaceNumber	1	0x00	Number of पूर्णांकerface
 * 3	bAlternateSetting	1	0x00	Value used to select alternate
 * 4	bNumEndpoपूर्णांकs		1	0x02	Number of endpoपूर्णांकs
 * 5	bInterfaceClass		1	0xFF	Class Code
 * 6	bInterfaceSubClass	1	0xFF	Subclass Code
 * 7	bInterfaceProtocol	1	0xFF	Protocol Code
 * 8	iInterface		1	0x02	Index of पूर्णांकerface string description
 *
 * IN Endpoपूर्णांक Descriptor
 *
 * Offset	Field			Size	Value
 * 0	bLength			1	0x07	Size of descriptor in bytes
 * 1	bDescriptorType		1	0x05	ENDPOINT descriptor type
 * 2	bEndpoपूर्णांकAddress	1	0x82	Address of endpoपूर्णांक
 * 3	bmAttributes		1	0x02	Endpoपूर्णांक attributes - Bulk
 * 4	bNumEndpoपूर्णांकs		2	0x0040	maximum packet size
 * 5	bInterval		1	0x00	Interval क्रम polling endpoपूर्णांक
 *
 * OUT Endpoपूर्णांक Descriptor
 *
 * Offset	Field			Size	Value
 * 0	bLength			1	0x07	Size of descriptor in bytes
 * 1	bDescriptorType		1	0x05	ENDPOINT descriptor type
 * 2	bEndpoपूर्णांकAddress	1	0x02	Address of endpoपूर्णांक
 * 3	bmAttributes		1	0x02	Endpoपूर्णांक attributes - Bulk
 * 4	bNumEndpoपूर्णांकs		2	0x0040	maximum packet size
 * 5	bInterval		1	0x00	Interval क्रम polling endpoपूर्णांक
 *
 * DATA FORMAT
 *
 * IN Endpoपूर्णांक
 *
 * The device reserves the first two bytes of data on this endpoपूर्णांक to contain
 * the current values of the modem and line status रेजिस्टरs. In the असलence of
 * data, the device generates a message consisting of these two status bytes
 * every 40 ms
 *
 * Byte 0: Modem Status
 *
 * Offset	Description
 * B0	Reserved - must be 1
 * B1	Reserved - must be 0
 * B2	Reserved - must be 0
 * B3	Reserved - must be 0
 * B4	Clear to Send (CTS)
 * B5	Data Set Ready (DSR)
 * B6	Ring Indicator (RI)
 * B7	Receive Line Signal Detect (RLSD)
 *
 * Byte 1: Line Status
 *
 * Offset	Description
 * B0	Data Ready (DR)
 * B1	Overrun Error (OE)
 * B2	Parity Error (PE)
 * B3	Framing Error (FE)
 * B4	Break Interrupt (BI)
 * B5	Transmitter Holding Register (THRE)
 * B6	Transmitter Empty (TEMT)
 * B7	Error in RCVR FIFO
 *
 */
#घोषणा FTDI_RS0_CTS	(1 << 4)
#घोषणा FTDI_RS0_DSR	(1 << 5)
#घोषणा FTDI_RS0_RI	(1 << 6)
#घोषणा FTDI_RS0_RLSD	(1 << 7)

#घोषणा FTDI_RS_DR	1
#घोषणा FTDI_RS_OE	(1<<1)
#घोषणा FTDI_RS_PE	(1<<2)
#घोषणा FTDI_RS_FE	(1<<3)
#घोषणा FTDI_RS_BI	(1<<4)
#घोषणा FTDI_RS_THRE	(1<<5)
#घोषणा FTDI_RS_TEMT	(1<<6)
#घोषणा FTDI_RS_FIFO	(1<<7)

/*
 * OUT Endpoपूर्णांक
 *
 * This device reserves the first bytes of data on this endpoपूर्णांक contain the
 * length and port identअगरier of the message. For the FTDI USB Serial converter
 * the port identअगरier is always 1.
 *
 * Byte 0: Line Status
 *
 * Offset	Description
 * B0	Reserved - must be 1
 * B1	Reserved - must be 0
 * B2..7	Length of message - (not including Byte 0)
 *
 */

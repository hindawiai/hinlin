<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * USB ConnectTech WhiteHEAT driver
 *
 *      Copyright (C) 2002
 *          Connect Tech Inc.
 *
 *      Copyright (C) 1999, 2000
 *          Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 *
 */

#अगर_अघोषित __LINUX_USB_SERIAL_WHITEHEAT_H
#घोषणा __LINUX_USB_SERIAL_WHITEHEAT_H


/* WhiteHEAT commands */
#घोषणा WHITEHEAT_OPEN			1	/* खोलो the port */
#घोषणा WHITEHEAT_CLOSE			2	/* बंद the port */
#घोषणा WHITEHEAT_SETUP_PORT		3	/* change port settings */
#घोषणा WHITEHEAT_SET_RTS		4	/* turn RTS on or off */
#घोषणा WHITEHEAT_SET_DTR		5	/* turn DTR on or off */
#घोषणा WHITEHEAT_SET_BREAK		6	/* turn BREAK on or off */
#घोषणा WHITEHEAT_DUMP			7	/* dump memory */
#घोषणा WHITEHEAT_STATUS		8	/* get status */
#घोषणा WHITEHEAT_PURGE			9	/* clear the UART fअगरos */
#घोषणा WHITEHEAT_GET_DTR_RTS		10	/* get the state of DTR and RTS
							क्रम a port */
#घोषणा WHITEHEAT_GET_HW_INFO		11	/* get EEPROM info and
							hardware ID */
#घोषणा WHITEHEAT_REPORT_TX_DONE	12	/* get the next TX करोne */
#घोषणा WHITEHEAT_EVENT			13	/* unsolicited status events */
#घोषणा WHITEHEAT_ECHO			14	/* send data to the indicated
						   IN endpoपूर्णांक */
#घोषणा WHITEHEAT_DO_TEST		15	/* perक्रमm specअगरied test */
#घोषणा WHITEHEAT_CMD_COMPLETE		16	/* reply क्रम some commands */
#घोषणा WHITEHEAT_CMD_FAILURE		17	/* reply क्रम failed commands */


/*
 * Commands to the firmware
 */


/*
 * WHITEHEAT_OPEN
 * WHITEHEAT_CLOSE
 * WHITEHEAT_STATUS
 * WHITEHEAT_GET_DTR_RTS
 * WHITEHEAT_REPORT_TX_DONE
*/
काष्ठा whiteheat_simple अणु
	__u8	port;	/* port number (1 to N) */
पूर्ण;


/*
 * WHITEHEAT_SETUP_PORT
 */
#घोषणा WHITEHEAT_PAR_NONE	'n'	/* no parity */
#घोषणा WHITEHEAT_PAR_EVEN	'e'	/* even parity */
#घोषणा WHITEHEAT_PAR_ODD	'o'	/* odd parity */
#घोषणा WHITEHEAT_PAR_SPACE	'0'	/* space (क्रमce 0) parity */
#घोषणा WHITEHEAT_PAR_MARK	'1'	/* mark (क्रमce 1) parity */

#घोषणा WHITEHEAT_SFLOW_NONE	'n'	/* no software flow control */
#घोषणा WHITEHEAT_SFLOW_RX	'r'	/* XOFF/ON is sent when RX
					   fills/empties */
#घोषणा WHITEHEAT_SFLOW_TX	't'	/* when received XOFF/ON will
					   stop/start TX */
#घोषणा WHITEHEAT_SFLOW_RXTX	'b'	/* both SFLOW_RX and SFLOW_TX */

#घोषणा WHITEHEAT_HFLOW_NONE		0x00	/* no hardware flow control */
#घोषणा WHITEHEAT_HFLOW_RTS_TOGGLE	0x01	/* RTS is on during transmit,
						   off otherwise */
#घोषणा WHITEHEAT_HFLOW_DTR		0x02	/* DTR is off/on when RX
						   fills/empties */
#घोषणा WHITEHEAT_HFLOW_CTS		0x08	/* when received CTS off/on
						   will stop/start TX */
#घोषणा WHITEHEAT_HFLOW_DSR		0x10	/* when received DSR off/on
						   will stop/start TX */
#घोषणा WHITEHEAT_HFLOW_RTS		0x80	/* RTS is off/on when RX
						   fills/empties */

काष्ठा whiteheat_port_settings अणु
	__u8	port;		/* port number (1 to N) */
	__le32	baud;		/* any value 7 - 460800, firmware calculates
				   best fit; arrives little endian */
	__u8	bits;		/* 5, 6, 7, or 8 */
	__u8	stop;		/* 1 or 2, शेष 1 (2 = 1.5 अगर bits = 5) */
	__u8	parity;		/* see WHITEHEAT_PAR_* above */
	__u8	sflow;		/* see WHITEHEAT_SFLOW_* above */
	__u8	xoff;		/* XOFF byte value */
	__u8	xon;		/* XON byte value */
	__u8	hflow;		/* see WHITEHEAT_HFLOW_* above */
	__u8	lloop;		/* 0/1 turns local loopback mode off/on */
पूर्ण __attribute__ ((packed));


/*
 * WHITEHEAT_SET_RTS
 * WHITEHEAT_SET_DTR
 * WHITEHEAT_SET_BREAK
 */
#घोषणा WHITEHEAT_RTS_OFF	0x00
#घोषणा WHITEHEAT_RTS_ON	0x01
#घोषणा WHITEHEAT_DTR_OFF	0x00
#घोषणा WHITEHEAT_DTR_ON	0x01
#घोषणा WHITEHEAT_BREAK_OFF	0x00
#घोषणा WHITEHEAT_BREAK_ON	0x01

काष्ठा whiteheat_set_rdb अणु
	__u8	port;		/* port number (1 to N) */
	__u8	state;		/* 0/1 turns संकेत off/on */
पूर्ण;


/*
 * WHITEHEAT_DUMP
 */
#घोषणा WHITEHEAT_DUMP_MEM_DATA		'd'  /* data */
#घोषणा WHITEHEAT_DUMP_MEM_IDATA	'i'  /* idata */
#घोषणा WHITEHEAT_DUMP_MEM_BDATA	'b'  /* bdata */
#घोषणा WHITEHEAT_DUMP_MEM_XDATA	'x'  /* xdata */

/*
 * Allowable address ranges (firmware checks address):
 * Type DATA:  0x00 - 0xff
 * Type IDATA: 0x80 - 0xff
 * Type BDATA: 0x20 - 0x2f
 * Type XDATA: 0x0000 - 0xffff
 *
 * B/I/DATA all पढ़ो the local memory space
 * XDATA पढ़ोs the बाह्यal memory space
 * BDATA वापसs bits as bytes
 *
 * NOTE: 0x80 - 0xff (local space) are the Special Function Registers
 *       of the 8051, and some have on-पढ़ो side-effects.
 */

काष्ठा whiteheat_dump अणु
	__u8	mem_type;	/* see WHITEHEAT_DUMP_* above */
	__u16	addr;		/* address, see restrictions above */
	__u16	length;		/* number of bytes to dump, max 63 bytes */
पूर्ण;


/*
 * WHITEHEAT_PURGE
 */
#घोषणा WHITEHEAT_PURGE_RX	0x01	/* purge rx fअगरos */
#घोषणा WHITEHEAT_PURGE_TX	0x02	/* purge tx fअगरos */

काष्ठा whiteheat_purge अणु
	__u8	port;		/* port number (1 to N) */
	__u8	what;		/* bit pattern of what to purge */
पूर्ण;


/*
 * WHITEHEAT_ECHO
 */
काष्ठा whiteheat_echo अणु
	__u8	port;		/* port number (1 to N) */
	__u8	length;		/* length of message to echo, max 61 bytes */
	__u8	echo_data[61];	/* data to echo */
पूर्ण;


/*
 * WHITEHEAT_DO_TEST
 */
#घोषणा WHITEHEAT_TEST_UART_RW		0x01  /* पढ़ो/ग_लिखो uart रेजिस्टरs */
#घोषणा WHITEHEAT_TEST_UART_INTR	0x02  /* uart पूर्णांकerrupt */
#घोषणा WHITEHEAT_TEST_SETUP_CONT	0x03  /* setup क्रम
						PORT_CONT/PORT_DISCONT */
#घोषणा WHITEHEAT_TEST_PORT_CONT	0x04  /* port connect */
#घोषणा WHITEHEAT_TEST_PORT_DISCONT	0x05  /* port disconnect */
#घोषणा WHITEHEAT_TEST_UART_CLK_START	0x06  /* uart घड़ी test start */
#घोषणा WHITEHEAT_TEST_UART_CLK_STOP	0x07  /* uart घड़ी test stop */
#घोषणा WHITEHEAT_TEST_MODEM_FT		0x08  /* modem संकेतs, requires a
						loopback cable/connector */
#घोषणा WHITEHEAT_TEST_ERASE_EEPROM	0x09  /* erase eeprom */
#घोषणा WHITEHEAT_TEST_READ_EEPROM	0x0a  /* पढ़ो eeprom */
#घोषणा WHITEHEAT_TEST_PROGRAM_EEPROM	0x0b  /* program eeprom */

काष्ठा whiteheat_test अणु
	__u8	port;		/* port number (1 to n) */
	__u8	test;		/* see WHITEHEAT_TEST_* above*/
	__u8	info[32];	/* additional info */
पूर्ण;


/*
 * Replies from the firmware
 */


/*
 * WHITEHEAT_STATUS
 */
#घोषणा WHITEHEAT_EVENT_MODEM		0x01	/* modem field is valid */
#घोषणा WHITEHEAT_EVENT_ERROR		0x02	/* error field is valid */
#घोषणा WHITEHEAT_EVENT_FLOW		0x04	/* flow field is valid */
#घोषणा WHITEHEAT_EVENT_CONNECT		0x08	/* connect field is valid */

#घोषणा WHITEHEAT_FLOW_NONE		0x00	/* no flow control active */
#घोषणा WHITEHEAT_FLOW_HARD_OUT		0x01	/* TX is stopped by CTS
						  (रुकोing क्रम CTS to go on) */
#घोषणा WHITEHEAT_FLOW_HARD_IN		0x02	/* remote TX is stopped
						  by RTS */
#घोषणा WHITEHEAT_FLOW_SOFT_OUT		0x04	/* TX is stopped by XOFF
						  received (रुकोing क्रम XON) */
#घोषणा WHITEHEAT_FLOW_SOFT_IN		0x08	/* remote TX is stopped by XOFF
						  transmitted */
#घोषणा WHITEHEAT_FLOW_TX_DONE		0x80	/* TX has completed */

काष्ठा whiteheat_status_info अणु
	__u8	port;		/* port number (1 to N) */
	__u8	event;		/* indicates what the current event is,
					see WHITEHEAT_EVENT_* above */
	__u8	modem;		/* modem संकेत status (copy of uart's
					MSR रेजिस्टर) */
	__u8	error;		/* line status (copy of uart's LSR रेजिस्टर) */
	__u8	flow;		/* flow control state, see WHITEHEAT_FLOW_*
					above */
	__u8	connect;	/* 0 means not connected, non-zero means
					connected */
पूर्ण;


/*
 * WHITEHEAT_GET_DTR_RTS
 */
काष्ठा whiteheat_dr_info अणु
	__u8	mcr;		/* copy of uart's MCR रेजिस्टर */
पूर्ण;


/*
 * WHITEHEAT_GET_HW_INFO
 */
काष्ठा whiteheat_hw_info अणु
	__u8	hw_id;		/* hardware id number, WhiteHEAT = 0 */
	__u8	sw_major_rev;	/* major version number */
	__u8	sw_minor_rev;	/* minor version number */
	काष्ठा whiteheat_hw_eeprom_info अणु
		__u8	b0;			/* B0 */
		__u8	venकरोr_id_low;		/* venकरोr id (low byte) */
		__u8	venकरोr_id_high;		/* venकरोr id (high byte) */
		__u8	product_id_low;		/* product id (low byte) */
		__u8	product_id_high;	/* product id (high byte) */
		__u8	device_id_low;		/* device id (low byte) */
		__u8	device_id_high;		/* device id (high byte) */
		__u8	not_used_1;
		__u8	serial_number_0;	/* serial number (low byte) */
		__u8	serial_number_1;	/* serial number */
		__u8	serial_number_2;	/* serial number */
		__u8	serial_number_3;	/* serial number (high byte) */
		__u8	not_used_2;
		__u8	not_used_3;
		__u8	checksum_low;		/* checksum (low byte) */
		__u8	checksum_high;		/* checksum (high byte */
	पूर्ण hw_eeprom_info;	/* EEPROM contents */
पूर्ण;


/*
 * WHITEHEAT_EVENT
 */
काष्ठा whiteheat_event_info अणु
	__u8	port;		/* port number (1 to N) */
	__u8	event;		/* see whiteheat_status_info.event */
	__u8	info;		/* see whiteheat_status_info.modem, .error,
					.flow, .connect */
पूर्ण;


/*
 * WHITEHEAT_DO_TEST
 */
#घोषणा WHITEHEAT_TEST_FAIL	0x00  /* test failed */
#घोषणा WHITEHEAT_TEST_UNKNOWN	0x01  /* unknown test requested */
#घोषणा WHITEHEAT_TEST_PASS	0xff  /* test passed */

काष्ठा whiteheat_test_info अणु
	__u8	port;		/* port number (1 to N) */
	__u8	test;		/* indicates which test this is a response क्रम,
				   see WHITEHEAT_DO_TEST above */
	__u8	status;		/* see WHITEHEAT_TEST_* above */
	__u8	results[32];	/* test-dependent results */
पूर्ण;


#पूर्ण_अगर

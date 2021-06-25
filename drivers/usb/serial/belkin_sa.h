<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Definitions क्रम Belkin USB Serial Adapter Driver
 *
 *  Copyright (C) 2000
 *      William Greathouse (wgreathouse@smva.com)
 *
 *  This program is largely derived from work by the linux-usb group
 *  and associated source files.  Please see the usb/serial files क्रम
 *  inभागidual credits and copyrights.
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 *
 * 12-Mar-2001 gkh
 *	Added GoHubs GO-COM232 device id.
 *
 * 06-Nov-2000 gkh
 *	Added old Belkin and Peracom device ids, which this driver supports
 *
 * 12-Oct-2000 William Greathouse
 *    First cut at supporting Belkin USB Serial Adapter F5U103
 *    I did not have a copy of the original work to support this
 *    adapter, so parकरोn any stupid mistakes.  All of the inक्रमmation
 *    I am using to ग_लिखो this driver was acquired by using a modअगरied
 *    UsbSnoop on Winकरोws2000.
 *
 */

#अगर_अघोषित __LINUX_USB_SERIAL_BSA_H
#घोषणा __LINUX_USB_SERIAL_BSA_H

#घोषणा BELKIN_DOCKSTATION_VID	0x050d	/* Venकरोr Id */
#घोषणा BELKIN_DOCKSTATION_PID	0x1203	/* Product Id */

#घोषणा BELKIN_SA_VID	0x050d	/* Venकरोr Id */
#घोषणा BELKIN_SA_PID	0x0103	/* Product Id */

#घोषणा BELKIN_OLD_VID	0x056c	/* Belkin's "old" venकरोr id */
#घोषणा BELKIN_OLD_PID	0x8007	/* Belkin's "old" single port serial converter's id */

#घोषणा PERACOM_VID	0x0565	/* Peracom's venकरोr id */
#घोषणा PERACOM_PID	0x0001	/* Peracom's single port serial converter's id */

#घोषणा GOHUBS_VID	0x0921	/* GoHubs venकरोr id */
#घोषणा GOHUBS_PID	0x1000	/* GoHubs single port serial converter's id (identical to the Peracom device) */
#घोषणा HANDYLINK_PID	0x1200	/* HandyLink USB's id (identical to the Peracom device) */

/* Venकरोr Request Interface */
#घोषणा BELKIN_SA_SET_BAUDRATE_REQUEST	0  /* Set baud rate */
#घोषणा BELKIN_SA_SET_STOP_BITS_REQUEST	1  /* Set stop bits (1,2) */
#घोषणा BELKIN_SA_SET_DATA_BITS_REQUEST	2  /* Set data bits (5,6,7,8) */
#घोषणा BELKIN_SA_SET_PARITY_REQUEST	3  /* Set parity (None, Even, Odd) */

#घोषणा BELKIN_SA_SET_DTR_REQUEST	10 /* Set DTR state */
#घोषणा BELKIN_SA_SET_RTS_REQUEST	11 /* Set RTS state */
#घोषणा BELKIN_SA_SET_BREAK_REQUEST	12 /* Set BREAK state */

#घोषणा BELKIN_SA_SET_FLOW_CTRL_REQUEST	16 /* Set flow control mode */


#अगर_घोषित WHEN_I_LEARN_THIS
#घोषणा BELKIN_SA_SET_MAGIC_REQUEST	17 /* I करोn't know, possibly flush */
					   /* (always in Wininit sequence beक्रमe flow control) */
#घोषणा BELKIN_SA_RESET			xx /* Reset the port */
#घोषणा BELKIN_SA_GET_MODEM_STATUS	xx /* Force वापस of modem status रेजिस्टर */
#पूर्ण_अगर

#घोषणा BELKIN_SA_SET_REQUEST_TYPE	0x40

#घोषणा BELKIN_SA_BAUD(b)		(230400/b)

#घोषणा BELKIN_SA_STOP_BITS(b)		(b-1)

#घोषणा BELKIN_SA_DATA_BITS(b)		(b-5)

#घोषणा BELKIN_SA_PARITY_NONE		0
#घोषणा BELKIN_SA_PARITY_EVEN		1
#घोषणा BELKIN_SA_PARITY_ODD		2
#घोषणा BELKIN_SA_PARITY_MARK		3
#घोषणा BELKIN_SA_PARITY_SPACE		4

#घोषणा BELKIN_SA_FLOW_NONE		0x0000	/* No flow control */
#घोषणा BELKIN_SA_FLOW_OCTS		0x0001	/* use CTS input to throttle output */
#घोषणा BELKIN_SA_FLOW_ODSR		0x0002	/* use DSR input to throttle output */
#घोषणा BELKIN_SA_FLOW_IDSR		0x0004	/* use DSR input to enable receive */
#घोषणा BELKIN_SA_FLOW_IDTR		0x0008	/* use DTR output क्रम input flow control */
#घोषणा BELKIN_SA_FLOW_IRTS		0x0010	/* use RTS output क्रम input flow control */
#घोषणा BELKIN_SA_FLOW_ORTS		0x0020	/* use RTS to indicate data available to send */
#घोषणा BELKIN_SA_FLOW_ERRSUB		0x0040	/* ???? guess ???? substitute अंतरभूत errors */
#घोषणा BELKIN_SA_FLOW_OXON		0x0080	/* use XON/XOFF क्रम output flow control */
#घोषणा BELKIN_SA_FLOW_IXON		0x0100	/* use XON/XOFF क्रम input flow control */

/*
 * It seems that the पूर्णांकerrupt pipe is बंदly modelled after the
 * 16550 रेजिस्टर layout.  This is probably because the adapter can
 * be used in a "DOS" environment to simulate a standard hardware port.
 */
#घोषणा BELKIN_SA_LSR_INDEX		2	/*     Line Status Register */
#घोषणा BELKIN_SA_LSR_RDR		0x01	/* receive data पढ़ोy */
#घोषणा BELKIN_SA_LSR_OE		0x02	/* overrun error */
#घोषणा BELKIN_SA_LSR_PE		0x04	/* parity error */
#घोषणा BELKIN_SA_LSR_FE		0x08	/* framing error */
#घोषणा BELKIN_SA_LSR_BI		0x10	/* अवरोध indicator */
#घोषणा BELKIN_SA_LSR_THE		0x20	/* tx holding रेजिस्टर empty */
#घोषणा BELKIN_SA_LSR_TE		0x40	/* transmit रेजिस्टर empty */
#घोषणा BELKIN_SA_LSR_ERR		0x80	/* OE | PE | FE | BI */

#घोषणा BELKIN_SA_MSR_INDEX		3	/*     Modem Status Register */
#घोषणा BELKIN_SA_MSR_DCTS		0x01	/* Delta CTS */
#घोषणा BELKIN_SA_MSR_DDSR		0x02	/* Delta DSR */
#घोषणा BELKIN_SA_MSR_DRI		0x04	/* Delta RI */
#घोषणा BELKIN_SA_MSR_DCD		0x08	/* Delta CD */
#घोषणा BELKIN_SA_MSR_CTS		0x10	/* Current CTS */
#घोषणा BELKIN_SA_MSR_DSR		0x20	/* Current DSR */
#घोषणा BELKIN_SA_MSR_RI		0x40	/* Current RI */
#घोषणा BELKIN_SA_MSR_CD		0x80	/* Current CD */

#पूर्ण_अगर /* __LINUX_USB_SERIAL_BSA_H */


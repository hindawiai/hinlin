<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MXSER_H
#घोषणा _MXSER_H

/*
 *	Semi-खुला control पूर्णांकerfaces
 */

/*
 *	MOXA ioctls
 */

#घोषणा MOXA			0x400
#घोषणा MOXA_GETDATACOUNT	(MOXA + 23)
#घोषणा MOXA_DIAGNOSE		(MOXA + 50)
#घोषणा MOXA_CHKPORTENABLE	(MOXA + 60)
#घोषणा MOXA_HighSpeedOn	(MOXA + 61)
#घोषणा MOXA_GET_MAJOR		(MOXA + 63)
#घोषणा MOXA_GETMSTATUS		(MOXA + 65)
#घोषणा MOXA_SET_OP_MODE	(MOXA + 66)
#घोषणा MOXA_GET_OP_MODE	(MOXA + 67)

#घोषणा RS232_MODE		0
#घोषणा RS485_2WIRE_MODE	1
#घोषणा RS422_MODE		2
#घोषणा RS485_4WIRE_MODE	3
#घोषणा OP_MODE_MASK		3

#घोषणा MOXA_SDS_RSTICOUNTER	(MOXA + 69)
#घोषणा MOXA_ASPP_OQUEUE  	(MOXA + 70)
#घोषणा MOXA_ASPP_MON     	(MOXA + 73)
#घोषणा MOXA_ASPP_LSTATUS 	(MOXA + 74)
#घोषणा MOXA_ASPP_MON_EXT 	(MOXA + 75)
#घोषणा MOXA_SET_BAUD_METHOD	(MOXA + 76)

/* --------------------------------------------------- */

#घोषणा NPPI_NOTIFY_PARITY	0x01
#घोषणा NPPI_NOTIFY_FRAMING	0x02
#घोषणा NPPI_NOTIFY_HW_OVERRUN	0x04
#घोषणा NPPI_NOTIFY_SW_OVERRUN	0x08
#घोषणा NPPI_NOTIFY_BREAK	0x10

#घोषणा NPPI_NOTIFY_CTSHOLD         0x01	/* Tx hold by CTS low */
#घोषणा NPPI_NOTIFY_DSRHOLD         0x02	/* Tx hold by DSR low */
#घोषणा NPPI_NOTIFY_XOFFHOLD        0x08	/* Tx hold by Xoff received */
#घोषणा NPPI_NOTIFY_XOFFXENT        0x10	/* Xoff Sent */

/* follow just क्रम Moxa Must chip define. */
/* */
/* when LCR रेजिस्टर (offset 0x03) ग_लिखो following value, */
/* the Must chip will enter enchance mode. And ग_लिखो value */
/* on EFR (offset 0x02) bit 6,7 to change bank. */
#घोषणा MOXA_MUST_ENTER_ENCHANCE	0xBF

/* when enhance mode enable, access on general bank रेजिस्टर */
#घोषणा MOXA_MUST_GDL_REGISTER		0x07
#घोषणा MOXA_MUST_GDL_MASK		0x7F
#घोषणा MOXA_MUST_GDL_HAS_BAD_DATA	0x80

#घोषणा MOXA_MUST_LSR_RERR		0x80	/* error in receive FIFO */
/* enchance रेजिस्टर bank select and enchance mode setting रेजिस्टर */
/* when LCR रेजिस्टर equal to 0xBF */
#घोषणा MOXA_MUST_EFR_REGISTER		0x02
/* enchance mode enable */
#घोषणा MOXA_MUST_EFR_EFRB_ENABLE	0x10
/* enchance reister bank set 0, 1, 2 */
#घोषणा MOXA_MUST_EFR_BANK0		0x00
#घोषणा MOXA_MUST_EFR_BANK1		0x40
#घोषणा MOXA_MUST_EFR_BANK2		0x80
#घोषणा MOXA_MUST_EFR_BANK3		0xC0
#घोषणा MOXA_MUST_EFR_BANK_MASK		0xC0

/* set XON1 value रेजिस्टर, when LCR=0xBF and change to bank0 */
#घोषणा MOXA_MUST_XON1_REGISTER		0x04

/* set XON2 value रेजिस्टर, when LCR=0xBF and change to bank0 */
#घोषणा MOXA_MUST_XON2_REGISTER		0x05

/* set XOFF1 value रेजिस्टर, when LCR=0xBF and change to bank0 */
#घोषणा MOXA_MUST_XOFF1_REGISTER	0x06

/* set XOFF2 value रेजिस्टर, when LCR=0xBF and change to bank0 */
#घोषणा MOXA_MUST_XOFF2_REGISTER	0x07

#घोषणा MOXA_MUST_RBRTL_REGISTER	0x04
#घोषणा MOXA_MUST_RBRTH_REGISTER	0x05
#घोषणा MOXA_MUST_RBRTI_REGISTER	0x06
#घोषणा MOXA_MUST_THRTL_REGISTER	0x07
#घोषणा MOXA_MUST_ENUM_REGISTER		0x04
#घोषणा MOXA_MUST_HWID_REGISTER		0x05
#घोषणा MOXA_MUST_ECR_REGISTER		0x06
#घोषणा MOXA_MUST_CSR_REGISTER		0x07

/* good data mode enable */
#घोषणा MOXA_MUST_FCR_GDA_MODE_ENABLE	0x20
/* only good data put पूर्णांकo RxFIFO */
#घोषणा MOXA_MUST_FCR_GDA_ONLY_ENABLE	0x10

/* enable CTS पूर्णांकerrupt */
#घोषणा MOXA_MUST_IER_ECTSI		0x80
/* enable RTS पूर्णांकerrupt */
#घोषणा MOXA_MUST_IER_ERTSI		0x40
/* enable Xon/Xoff पूर्णांकerrupt */
#घोषणा MOXA_MUST_IER_XINT		0x20
/* enable GDA पूर्णांकerrupt */
#घोषणा MOXA_MUST_IER_EGDAI		0x10

#घोषणा MOXA_MUST_RECV_ISR		(UART_IER_RDI | MOXA_MUST_IER_EGDAI)

/* GDA पूर्णांकerrupt pending */
#घोषणा MOXA_MUST_IIR_GDA		0x1C
#घोषणा MOXA_MUST_IIR_RDA		0x04
#घोषणा MOXA_MUST_IIR_RTO		0x0C
#घोषणा MOXA_MUST_IIR_LSR		0x06

/* received Xon/Xoff or specical पूर्णांकerrupt pending */
#घोषणा MOXA_MUST_IIR_XSC		0x10

/* RTS/CTS change state पूर्णांकerrupt pending */
#घोषणा MOXA_MUST_IIR_RTSCTS		0x20
#घोषणा MOXA_MUST_IIR_MASK		0x3E

#घोषणा MOXA_MUST_MCR_XON_FLAG		0x40
#घोषणा MOXA_MUST_MCR_XON_ANY		0x80
#घोषणा MOXA_MUST_MCR_TX_XON		0x08

/* software flow control on chip mask value */
#घोषणा MOXA_MUST_EFR_SF_MASK		0x0F
/* send Xon1/Xoff1 */
#घोषणा MOXA_MUST_EFR_SF_TX1		0x08
/* send Xon2/Xoff2 */
#घोषणा MOXA_MUST_EFR_SF_TX2		0x04
/* send Xon1,Xon2/Xoff1,Xoff2 */
#घोषणा MOXA_MUST_EFR_SF_TX12		0x0C
/* करोn't send Xon/Xoff */
#घोषणा MOXA_MUST_EFR_SF_TX_NO		0x00
/* Tx software flow control mask */
#घोषणा MOXA_MUST_EFR_SF_TX_MASK	0x0C
/* करोn't receive Xon/Xoff */
#घोषणा MOXA_MUST_EFR_SF_RX_NO		0x00
/* receive Xon1/Xoff1 */
#घोषणा MOXA_MUST_EFR_SF_RX1		0x02
/* receive Xon2/Xoff2 */
#घोषणा MOXA_MUST_EFR_SF_RX2		0x01
/* receive Xon1,Xon2/Xoff1,Xoff2 */
#घोषणा MOXA_MUST_EFR_SF_RX12		0x03
/* Rx software flow control mask */
#घोषणा MOXA_MUST_EFR_SF_RX_MASK	0x03

#पूर्ण_अगर

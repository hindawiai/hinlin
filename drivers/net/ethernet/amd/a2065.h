<शैली गुरु>
/*
 * Amiga Linux/68k A2065 Ethernet Driver
 *
 * (C) Copyright 1995 by Geert Uytterhoeven <geert@linux-m68k.org>
 *
 * ---------------------------------------------------------------------------
 *
 * This program is based on
 *
 *	ariadne.?:	Amiga Linux/68k Ariadne Ethernet Driver
 *			(C) Copyright 1995 by Geert Uytterhoeven,
 *			Peter De Schrijver
 *
 *	lance.c:	An AMD LANCE ethernet driver क्रम linux.
 *			Written 1993-94 by Donald Becker.
 *
 *	Am79C960:	PCnet(पंचांग)-ISA Single-Chip Ethernet Controller
 *			Advanced Micro Devices
 *			Publication #16907, Rev. B, Amendment/0, May 1994
 *
 * ---------------------------------------------------------------------------
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of the Linux
 * distribution क्रम more details.
 *
 * ---------------------------------------------------------------------------
 *
 * The A2065 is a Zorro-II board made by Commoकरोre/Ameristar. It contains:
 *
 *	- an Am7990 Local Area Network Controller क्रम Ethernet (LANCE) with
 *	  both 10BASE-2 (thin coax) and AUI (DB-15) connectors
 */


/*
 *		Am7990 Local Area Network Controller क्रम Ethernet (LANCE)
 */

काष्ठा lance_regs अणु
	अचिन्हित लघु rdp;		/* Register Data Port */
	अचिन्हित लघु rap;		/* Register Address Port */
पूर्ण;


/*
 *		Am7990 Control and Status Registers
 */

#घोषणा LE_CSR0		0x0000		/* LANCE Controller Status */
#घोषणा LE_CSR1		0x0001		/* IADR[15:0] */
#घोषणा LE_CSR2		0x0002		/* IADR[23:16] */
#घोषणा LE_CSR3		0x0003		/* Misc */


/*
 *		Bit definitions क्रम CSR0 (LANCE Controller Status)
 */

#घोषणा LE_C0_ERR	0x8000		/* Error */
#घोषणा LE_C0_BABL	0x4000		/* Babble: Transmitted too many bits */
#घोषणा LE_C0_CERR	0x2000		/* No Heartbeat (10BASE-T) */
#घोषणा LE_C0_MISS	0x1000		/* Missed Frame */
#घोषणा LE_C0_MERR	0x0800		/* Memory Error */
#घोषणा LE_C0_RINT	0x0400		/* Receive Interrupt */
#घोषणा LE_C0_TINT	0x0200		/* Transmit Interrupt */
#घोषणा LE_C0_IDON	0x0100		/* Initialization Done */
#घोषणा LE_C0_INTR	0x0080		/* Interrupt Flag */
#घोषणा LE_C0_INEA	0x0040		/* Interrupt Enable */
#घोषणा LE_C0_RXON	0x0020		/* Receive On */
#घोषणा LE_C0_TXON	0x0010		/* Transmit On */
#घोषणा LE_C0_TDMD	0x0008		/* Transmit Demand */
#घोषणा LE_C0_STOP	0x0004		/* Stop */
#घोषणा LE_C0_STRT	0x0002		/* Start */
#घोषणा LE_C0_INIT	0x0001		/* Initialize */


/*
 *		Bit definitions क्रम CSR3
 */

#घोषणा LE_C3_BSWP	0x0004		/* Byte Swap
					   (on क्रम big endian byte order) */
#घोषणा LE_C3_ACON	0x0002		/* ALE Control
					   (on क्रम active low ALE) */
#घोषणा LE_C3_BCON	0x0001		/* Byte Control */


/*
 *		Mode Flags
 */

#घोषणा LE_MO_PROM	0x8000		/* Promiscuous Mode */
#घोषणा LE_MO_INTL	0x0040		/* Internal Loopback */
#घोषणा LE_MO_DRTY	0x0020		/* Disable Retry */
#घोषणा LE_MO_FCOLL	0x0010		/* Force Collision */
#घोषणा LE_MO_DXMTFCS	0x0008		/* Disable Transmit CRC */
#घोषणा LE_MO_LOOP	0x0004		/* Loopback Enable */
#घोषणा LE_MO_DTX	0x0002		/* Disable Transmitter */
#घोषणा LE_MO_DRX	0x0001		/* Disable Receiver */


काष्ठा lance_rx_desc अणु
	अचिन्हित लघु rmd0;        /* low address of packet */
	अचिन्हित अक्षर  rmd1_bits;   /* descriptor bits */
	अचिन्हित अक्षर  rmd1_hadr;   /* high address of packet */
	लघु    length;    	    /* This length is 2s complement (negative)!
				     * Buffer length
				     */
	अचिन्हित लघु mblength;    /* Aactual number of bytes received */
पूर्ण;

काष्ठा lance_tx_desc अणु
	अचिन्हित लघु पंचांगd0;        /* low address of packet */
	अचिन्हित अक्षर  पंचांगd1_bits;   /* descriptor bits */
	अचिन्हित अक्षर  पंचांगd1_hadr;   /* high address of packet */
	लघु    length;       	    /* Length is 2s complement (negative)! */
	अचिन्हित लघु misc;
पूर्ण;


/*
 *		Receive Flags
 */

#घोषणा LE_R1_OWN	0x80		/* LANCE owns the descriptor */
#घोषणा LE_R1_ERR	0x40		/* Error */
#घोषणा LE_R1_FRA	0x20		/* Framing Error */
#घोषणा LE_R1_OFL	0x10		/* Overflow Error */
#घोषणा LE_R1_CRC	0x08		/* CRC Error */
#घोषणा LE_R1_BUF	0x04		/* Buffer Error */
#घोषणा LE_R1_SOP	0x02		/* Start of Packet */
#घोषणा LE_R1_EOP	0x01		/* End of Packet */
#घोषणा LE_R1_POK       0x03		/* Packet is complete: SOP + EOP */


/*
 *		Transmit Flags
 */

#घोषणा LE_T1_OWN	0x80		/* LANCE owns the descriptor */
#घोषणा LE_T1_ERR	0x40		/* Error */
#घोषणा LE_T1_RES	0x20		/* Reserved,
					   LANCE ग_लिखोs this with a zero */
#घोषणा LE_T1_EMORE	0x10		/* More than one retry needed */
#घोषणा LE_T1_EONE	0x08		/* One retry needed */
#घोषणा LE_T1_EDEF	0x04		/* Deferred */
#घोषणा LE_T1_SOP	0x02		/* Start of Packet */
#घोषणा LE_T1_EOP	0x01		/* End of Packet */
#घोषणा LE_T1_POK	0x03		/* Packet is complete: SOP + EOP */


/*
 *		Error Flags
 */

#घोषणा LE_T3_BUF 	0x8000		/* Buffer Error */
#घोषणा LE_T3_UFL 	0x4000		/* Underflow Error */
#घोषणा LE_T3_LCOL 	0x1000		/* Late Collision */
#घोषणा LE_T3_CLOS 	0x0800		/* Loss of Carrier */
#घोषणा LE_T3_RTY 	0x0400		/* Retry Error */
#घोषणा LE_T3_TDR	0x03ff		/* Time Doमुख्य Reflectometry */


/*
 *		A2065 Expansion Board Structure
 */

#घोषणा A2065_LANCE		0x4000

#घोषणा A2065_RAM		0x8000
#घोषणा A2065_RAM_SIZE		0x8000


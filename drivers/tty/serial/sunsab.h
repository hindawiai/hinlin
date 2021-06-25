<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* sunsab.h: Register Definitions क्रम the Siemens SAB82532 DUSCC
 *
 * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 */

#अगर_अघोषित _SUNSAB_H
#घोषणा _SUNSAB_H

काष्ठा sab82532_async_rd_regs अणु
	u8	rfअगरo[0x20];	/* Receive FIFO				*/
	u8	star;		/* Status Register			*/
	u8	__pad1;
	u8	mode;		/* Mode Register			*/
	u8	timr;		/* Timer Register			*/
	u8	xon;		/* XON Character			*/
	u8	xoff;		/* XOFF Character			*/
	u8	tcr;		/* Termination Character Register	*/
	u8	dafo;		/* Data Format				*/
	u8	rfc;		/* RFIFO Control Register		*/
	u8	__pad2;
	u8	rbcl;		/* Receive Byte Count Low		*/
	u8	rbch;		/* Receive Byte Count High		*/
	u8	ccr0;		/* Channel Configuration Register 0	*/
	u8	ccr1;		/* Channel Configuration Register 1	*/
	u8	ccr2;		/* Channel Configuration Register 2	*/
	u8	ccr3;		/* Channel Configuration Register 3	*/
	u8	__pad3[4];
	u8	vstr;		/* Version Status Register		*/
	u8	__pad4[3];
	u8	gis;		/* Global Interrupt Status		*/
	u8	ipc;		/* Interrupt Port Configuration		*/
	u8	isr0;		/* Interrupt Status 0			*/
	u8	isr1;		/* Interrupt Status 1			*/
	u8	pvr;		/* Port Value Register			*/
	u8	pis;		/* Port Interrupt Status		*/
	u8	pcr;		/* Port Configuration Register		*/
	u8	ccr4;		/* Channel Configuration Register 4	*/
पूर्ण;

काष्ठा sab82532_async_wr_regs अणु
	u8	xfअगरo[0x20];	/* Transmit FIFO			*/
	u8	cmdr;		/* Command Register			*/
	u8	__pad1;
	u8	mode;
	u8	timr;
	u8	xon;
	u8	xoff;
	u8	tcr;
	u8	dafo;
	u8	rfc;
	u8	__pad2;
	u8	xbcl;		/* Transmit Byte Count Low		*/
	u8	xbch;		/* Transmit Byte Count High		*/
	u8	ccr0;
	u8	ccr1;
	u8	ccr2;
	u8	ccr3;
	u8	tsax;		/* Time-Slot Assignment Reg. Transmit	*/
	u8	tsar;		/* Time-Slot Assignment Reg. Receive	*/
	u8	xccr;		/* Transmit Channel Capacity Register	*/
	u8	rccr;		/* Receive Channel Capacity Register	*/
	u8	bgr;		/* Baud Rate Generator Register		*/
	u8	tic;		/* Transmit Immediate Character		*/
	u8	mxn;		/* Mask XON Character			*/
	u8	mxf;		/* Mask XOFF Character			*/
	u8	iva;		/* Interrupt Vector Address		*/
	u8	ipc;
	u8	imr0;		/* Interrupt Mask Register 0		*/
	u8	imr1;		/* Interrupt Mask Register 1		*/
	u8	pvr;
	u8	pim;		/* Port Interrupt Mask			*/
	u8	pcr;
	u8	ccr4;
पूर्ण;

काष्ठा sab82532_async_rw_regs अणु	/* Read/Write रेजिस्टरs			*/
	u8	__pad1[0x20];
	u8	__pad2;
	u8	__pad3;
	u8	mode;
	u8	timr;
	u8	xon;
	u8	xoff;
	u8	tcr;
	u8	dafo;
	u8	rfc;
	u8	__pad4;
	u8	__pad5;
	u8	__pad6;
	u8	ccr0;
	u8	ccr1;
	u8	ccr2;
	u8	ccr3;
	u8	__pad7;
	u8	__pad8;
	u8	__pad9;
	u8	__pad10;
	u8	__pad11;
	u8	__pad12;
	u8	__pad13;
	u8	__pad14;
	u8	__pad15;
	u8	ipc;
	u8	__pad16;
	u8	__pad17;
	u8	pvr;
	u8	__pad18;
	u8	pcr;
	u8	ccr4;
पूर्ण;

जोड़ sab82532_async_regs अणु
	__अस्थिर__ काष्ठा sab82532_async_rd_regs	r;
	__अस्थिर__ काष्ठा sab82532_async_wr_regs	w;
	__अस्थिर__ काष्ठा sab82532_async_rw_regs	rw;
पूर्ण;

जोड़ sab82532_irq_status अणु
	अचिन्हित लघु			 stat;
	काष्ठा अणु
		अचिन्हित अक्षर		 isr0;
		अचिन्हित अक्षर		 isr1;
	पूर्ण sreg;
पूर्ण;

/* irqflags bits */
#घोषणा SAB82532_ALLS			0x00000001
#घोषणा SAB82532_XPR			0x00000002
#घोषणा SAB82532_REGS_PENDING		0x00000004

/* RFIFO Status Byte */
#घोषणा SAB82532_RSTAT_PE		0x80
#घोषणा SAB82532_RSTAT_FE		0x40
#घोषणा SAB82532_RSTAT_PARITY		0x01

/* Status Register (STAR) */
#घोषणा SAB82532_STAR_XDOV		0x80
#घोषणा SAB82532_STAR_XFW		0x40
#घोषणा SAB82532_STAR_RFNE		0x20
#घोषणा SAB82532_STAR_FCS		0x10
#घोषणा SAB82532_STAR_TEC		0x08
#घोषणा SAB82532_STAR_CEC		0x04
#घोषणा SAB82532_STAR_CTS		0x02

/* Command Register (CMDR) */
#घोषणा SAB82532_CMDR_RMC		0x80
#घोषणा SAB82532_CMDR_RRES		0x40
#घोषणा SAB82532_CMDR_RFRD		0x20
#घोषणा SAB82532_CMDR_STI		0x10
#घोषणा SAB82532_CMDR_XF		0x08
#घोषणा SAB82532_CMDR_XRES		0x01

/* Mode Register (MODE) */
#घोषणा SAB82532_MODE_FRTS		0x40
#घोषणा SAB82532_MODE_FCTS		0x20
#घोषणा SAB82532_MODE_FLON		0x10
#घोषणा SAB82532_MODE_RAC		0x08
#घोषणा SAB82532_MODE_RTS		0x04
#घोषणा SAB82532_MODE_TRS		0x02
#घोषणा SAB82532_MODE_TLP		0x01

/* Timer Register (TIMR) */
#घोषणा SAB82532_TIMR_CNT_MASK		0xe0
#घोषणा SAB82532_TIMR_VALUE_MASK	0x1f

/* Data Format (DAFO) */
#घोषणा SAB82532_DAFO_XBRK		0x40
#घोषणा SAB82532_DAFO_STOP		0x20
#घोषणा SAB82532_DAFO_PAR_SPACE		0x00
#घोषणा SAB82532_DAFO_PAR_ODD		0x08
#घोषणा SAB82532_DAFO_PAR_EVEN		0x10
#घोषणा SAB82532_DAFO_PAR_MARK		0x18
#घोषणा SAB82532_DAFO_PARE		0x04
#घोषणा SAB82532_DAFO_CHL8		0x00
#घोषणा SAB82532_DAFO_CHL7		0x01
#घोषणा SAB82532_DAFO_CHL6		0x02
#घोषणा SAB82532_DAFO_CHL5		0x03

/* RFIFO Control Register (RFC) */
#घोषणा SAB82532_RFC_DPS		0x40
#घोषणा SAB82532_RFC_DXS		0x20
#घोषणा SAB82532_RFC_RFDF		0x10
#घोषणा SAB82532_RFC_RFTH_1		0x00
#घोषणा SAB82532_RFC_RFTH_4		0x04
#घोषणा SAB82532_RFC_RFTH_16		0x08
#घोषणा SAB82532_RFC_RFTH_32		0x0c
#घोषणा SAB82532_RFC_TCDE		0x01

/* Received Byte Count High (RBCH) */
#घोषणा SAB82532_RBCH_DMA		0x80
#घोषणा SAB82532_RBCH_CAS		0x20

/* Transmit Byte Count High (XBCH) */
#घोषणा SAB82532_XBCH_DMA		0x80
#घोषणा SAB82532_XBCH_CAS		0x20
#घोषणा SAB82532_XBCH_XC		0x10

/* Channel Configuration Register 0 (CCR0) */
#घोषणा SAB82532_CCR0_PU		0x80
#घोषणा SAB82532_CCR0_MCE		0x40
#घोषणा SAB82532_CCR0_SC_NRZ		0x00
#घोषणा SAB82532_CCR0_SC_NRZI		0x08
#घोषणा SAB82532_CCR0_SC_FM0		0x10
#घोषणा SAB82532_CCR0_SC_FM1		0x14
#घोषणा SAB82532_CCR0_SC_MANCH		0x18
#घोषणा SAB82532_CCR0_SM_HDLC		0x00
#घोषणा SAB82532_CCR0_SM_SDLC_LOOP	0x01
#घोषणा SAB82532_CCR0_SM_BISYNC		0x02
#घोषणा SAB82532_CCR0_SM_ASYNC		0x03

/* Channel Configuration Register 1 (CCR1) */
#घोषणा SAB82532_CCR1_ODS		0x10
#घोषणा SAB82532_CCR1_BCR		0x08
#घोषणा SAB82532_CCR1_CM_MASK		0x07

/* Channel Configuration Register 2 (CCR2) */
#घोषणा SAB82532_CCR2_SOC1		0x80
#घोषणा SAB82532_CCR2_SOC0		0x40
#घोषणा SAB82532_CCR2_BR9		0x80
#घोषणा SAB82532_CCR2_BR8		0x40
#घोषणा SAB82532_CCR2_BDF		0x20
#घोषणा SAB82532_CCR2_SSEL		0x10
#घोषणा SAB82532_CCR2_XCS0		0x20
#घोषणा SAB82532_CCR2_RCS0		0x10
#घोषणा SAB82532_CCR2_TOE		0x08
#घोषणा SAB82532_CCR2_RWX		0x04
#घोषणा SAB82532_CCR2_DIV		0x01

/* Channel Configuration Register 3 (CCR3) */
#घोषणा SAB82532_CCR3_PSD		0x01

/* Time Slot Assignment Register Transmit (TSAX) */
#घोषणा SAB82532_TSAX_TSNX_MASK		0xfc
#घोषणा SAB82532_TSAX_XCS2		0x02	/* see also CCR2 */
#घोषणा SAB82532_TSAX_XCS1		0x01

/* Time Slot Assignment Register Receive (TSAR) */
#घोषणा SAB82532_TSAR_TSNR_MASK		0xfc
#घोषणा SAB82532_TSAR_RCS2		0x02	/* see also CCR2 */
#घोषणा SAB82532_TSAR_RCS1		0x01

/* Version Status Register (VSTR) */
#घोषणा SAB82532_VSTR_CD		0x80
#घोषणा SAB82532_VSTR_DPLA		0x40
#घोषणा SAB82532_VSTR_VN_MASK		0x0f
#घोषणा SAB82532_VSTR_VN_1		0x00
#घोषणा SAB82532_VSTR_VN_2		0x01
#घोषणा SAB82532_VSTR_VN_3_2		0x02

/* Global Interrupt Status Register (GIS) */
#घोषणा SAB82532_GIS_PI			0x80
#घोषणा SAB82532_GIS_ISA1		0x08
#घोषणा SAB82532_GIS_ISA0		0x04
#घोषणा SAB82532_GIS_ISB1		0x02
#घोषणा SAB82532_GIS_ISB0		0x01

/* Interrupt Vector Address (IVA) */
#घोषणा SAB82532_IVA_MASK		0xf1

/* Interrupt Port Configuration (IPC) */
#घोषणा SAB82532_IPC_VIS		0x80
#घोषणा SAB82532_IPC_SLA1		0x10
#घोषणा SAB82532_IPC_SLA0		0x08
#घोषणा SAB82532_IPC_CASM		0x04
#घोषणा SAB82532_IPC_IC_OPEN_DRAIN	0x00
#घोषणा SAB82532_IPC_IC_ACT_LOW		0x01
#घोषणा SAB82532_IPC_IC_ACT_HIGH	0x03

/* Interrupt Status Register 0 (ISR0) */
#घोषणा SAB82532_ISR0_TCD		0x80
#घोषणा SAB82532_ISR0_TIME		0x40
#घोषणा SAB82532_ISR0_PERR		0x20
#घोषणा SAB82532_ISR0_FERR		0x10
#घोषणा SAB82532_ISR0_PLLA		0x08
#घोषणा SAB82532_ISR0_CDSC		0x04
#घोषणा SAB82532_ISR0_RFO		0x02
#घोषणा SAB82532_ISR0_RPF		0x01

/* Interrupt Status Register 1 (ISR1) */
#घोषणा SAB82532_ISR1_BRK		0x80
#घोषणा SAB82532_ISR1_BRKT		0x40
#घोषणा SAB82532_ISR1_ALLS		0x20
#घोषणा SAB82532_ISR1_XOFF		0x10
#घोषणा SAB82532_ISR1_TIN		0x08
#घोषणा SAB82532_ISR1_CSC		0x04
#घोषणा SAB82532_ISR1_XON		0x02
#घोषणा SAB82532_ISR1_XPR		0x01

/* Interrupt Mask Register 0 (IMR0) */
#घोषणा SAB82532_IMR0_TCD		0x80
#घोषणा SAB82532_IMR0_TIME		0x40
#घोषणा SAB82532_IMR0_PERR		0x20
#घोषणा SAB82532_IMR0_FERR		0x10
#घोषणा SAB82532_IMR0_PLLA		0x08
#घोषणा SAB82532_IMR0_CDSC		0x04
#घोषणा SAB82532_IMR0_RFO		0x02
#घोषणा SAB82532_IMR0_RPF		0x01

/* Interrupt Mask Register 1 (IMR1) */
#घोषणा SAB82532_IMR1_BRK		0x80
#घोषणा SAB82532_IMR1_BRKT		0x40
#घोषणा SAB82532_IMR1_ALLS		0x20
#घोषणा SAB82532_IMR1_XOFF		0x10
#घोषणा SAB82532_IMR1_TIN		0x08
#घोषणा SAB82532_IMR1_CSC		0x04
#घोषणा SAB82532_IMR1_XON		0x02
#घोषणा SAB82532_IMR1_XPR		0x01

/* Port Interrupt Status Register (PIS) */
#घोषणा SAB82532_PIS_SYNC_B		0x08
#घोषणा SAB82532_PIS_DTR_B		0x04
#घोषणा SAB82532_PIS_DTR_A		0x02
#घोषणा SAB82532_PIS_SYNC_A		0x01

/* Channel Configuration Register 4 (CCR4) */
#घोषणा SAB82532_CCR4_MCK4		0x80
#घोषणा SAB82532_CCR4_EBRG		0x40
#घोषणा SAB82532_CCR4_TST1		0x20
#घोषणा SAB82532_CCR4_ICD		0x10


#पूर्ण_अगर /* !(_SUNSAB_H) */

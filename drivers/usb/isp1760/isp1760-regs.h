<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the NXP ISP1760 chip
 *
 * Copyright 2014 Laurent Pinअक्षरt
 * Copyright 2007 Sebastian Siewior
 *
 * Contacts:
 *     Sebastian Siewior <bigeasy@linutronix.de>
 *     Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित _ISP1760_REGS_H_
#घोषणा _ISP1760_REGS_H_

/* -----------------------------------------------------------------------------
 * Host Controller
 */

/* EHCI capability रेजिस्टरs */
#घोषणा HC_CAPLENGTH		0x000
#घोषणा HC_LENGTH(p)		(((p) >> 00) & 0x00ff)	/* bits 7:0 */
#घोषणा HC_VERSION(p)		(((p) >> 16) & 0xffff)	/* bits 31:16 */

#घोषणा HC_HCSPARAMS		0x004
#घोषणा HCS_INDICATOR(p)	((p) & (1 << 16))	/* true: has port indicators */
#घोषणा HCS_PPC(p)		((p) & (1 << 4))	/* true: port घातer control */
#घोषणा HCS_N_PORTS(p)		(((p) >> 0) & 0xf)	/* bits 3:0, ports on HC */

#घोषणा HC_HCCPARAMS		0x008
#घोषणा HCC_ISOC_CACHE(p)       ((p) & (1 << 7))	/* true: can cache isoc frame */
#घोषणा HCC_ISOC_THRES(p)       (((p) >> 4) & 0x7)	/* bits 6:4, uframes cached */

/* EHCI operational रेजिस्टरs */
#घोषणा HC_USBCMD		0x020
#घोषणा CMD_LRESET		(1 << 7)		/* partial reset (no ports, etc) */
#घोषणा CMD_RESET		(1 << 1)		/* reset HC not bus */
#घोषणा CMD_RUN			(1 << 0)		/* start/stop HC */

#घोषणा HC_USBSTS		0x024
#घोषणा STS_PCD			(1 << 2)		/* port change detect */

#घोषणा HC_FRINDEX		0x02c

#घोषणा HC_CONFIGFLAG		0x060
#घोषणा FLAG_CF			(1 << 0)		/* true: we'll support "high speed" */

#घोषणा HC_PORTSC1		0x064
#घोषणा PORT_OWNER		(1 << 13)		/* true: companion hc owns this port */
#घोषणा PORT_POWER		(1 << 12)		/* true: has घातer (see PPC) */
#घोषणा PORT_USB11(x)		(((x) & (3 << 10)) == (1 << 10))	/* USB 1.1 device */
#घोषणा PORT_RESET		(1 << 8)		/* reset port */
#घोषणा PORT_SUSPEND		(1 << 7)		/* suspend port */
#घोषणा PORT_RESUME		(1 << 6)		/* resume it */
#घोषणा PORT_PE			(1 << 2)		/* port enable */
#घोषणा PORT_CSC		(1 << 1)		/* connect status change */
#घोषणा PORT_CONNECT		(1 << 0)		/* device connected */
#घोषणा PORT_RWC_BITS		(PORT_CSC)

#घोषणा HC_ISO_PTD_DONEMAP_REG	0x130
#घोषणा HC_ISO_PTD_SKIPMAP_REG	0x134
#घोषणा HC_ISO_PTD_LASTPTD_REG	0x138
#घोषणा HC_INT_PTD_DONEMAP_REG	0x140
#घोषणा HC_INT_PTD_SKIPMAP_REG	0x144
#घोषणा HC_INT_PTD_LASTPTD_REG	0x148
#घोषणा HC_ATL_PTD_DONEMAP_REG	0x150
#घोषणा HC_ATL_PTD_SKIPMAP_REG	0x154
#घोषणा HC_ATL_PTD_LASTPTD_REG	0x158

/* Configuration Register */
#घोषणा HC_HW_MODE_CTRL		0x300
#घोषणा ALL_ATX_RESET		(1 << 31)
#घोषणा HW_ANA_DIGI_OC		(1 << 15)
#घोषणा HW_DEV_DMA		(1 << 11)
#घोषणा HW_COMN_IRQ		(1 << 10)
#घोषणा HW_COMN_DMA		(1 << 9)
#घोषणा HW_DATA_BUS_32BIT	(1 << 8)
#घोषणा HW_DACK_POL_HIGH	(1 << 6)
#घोषणा HW_DREQ_POL_HIGH	(1 << 5)
#घोषणा HW_INTR_HIGH_ACT	(1 << 2)
#घोषणा HW_INTR_EDGE_TRIG	(1 << 1)
#घोषणा HW_GLOBAL_INTR_EN	(1 << 0)

#घोषणा HC_CHIP_ID_REG		0x304
#घोषणा HC_SCRATCH_REG		0x308

#घोषणा HC_RESET_REG		0x30c
#घोषणा SW_RESET_RESET_HC	(1 << 1)
#घोषणा SW_RESET_RESET_ALL	(1 << 0)

#घोषणा HC_BUFFER_STATUS_REG	0x334
#घोषणा ISO_BUF_FILL		(1 << 2)
#घोषणा INT_BUF_FILL		(1 << 1)
#घोषणा ATL_BUF_FILL		(1 << 0)

#घोषणा HC_MEMORY_REG		0x33c
#घोषणा ISP_BANK(x)		((x) << 16)

#घोषणा HC_PORT1_CTRL		0x374
#घोषणा PORT1_POWER		(3 << 3)
#घोषणा PORT1_INIT1		(1 << 7)
#घोषणा PORT1_INIT2		(1 << 23)
#घोषणा HW_OTG_CTRL_SET		0x374
#घोषणा HW_OTG_CTRL_CLR		0x376
#घोषणा HW_OTG_DISABLE		(1 << 10)
#घोषणा HW_OTG_SE0_EN		(1 << 9)
#घोषणा HW_BDIS_ACON_EN		(1 << 8)
#घोषणा HW_SW_SEL_HC_DC		(1 << 7)
#घोषणा HW_VBUS_CHRG		(1 << 6)
#घोषणा HW_VBUS_DISCHRG		(1 << 5)
#घोषणा HW_VBUS_DRV		(1 << 4)
#घोषणा HW_SEL_CP_EXT		(1 << 3)
#घोषणा HW_DM_PULLDOWN		(1 << 2)
#घोषणा HW_DP_PULLDOWN		(1 << 1)
#घोषणा HW_DP_PULLUP		(1 << 0)

/* Interrupt Register */
#घोषणा HC_INTERRUPT_REG	0x310

#घोषणा HC_INTERRUPT_ENABLE	0x314
#घोषणा HC_ISO_INT		(1 << 9)
#घोषणा HC_ATL_INT		(1 << 8)
#घोषणा HC_INTL_INT		(1 << 7)
#घोषणा HC_EOT_INT		(1 << 3)
#घोषणा HC_SOT_INT		(1 << 1)
#घोषणा INTERRUPT_ENABLE_MASK	(HC_INTL_INT | HC_ATL_INT)

#घोषणा HC_ISO_IRQ_MASK_OR_REG	0x318
#घोषणा HC_INT_IRQ_MASK_OR_REG	0x31c
#घोषणा HC_ATL_IRQ_MASK_OR_REG	0x320
#घोषणा HC_ISO_IRQ_MASK_AND_REG	0x324
#घोषणा HC_INT_IRQ_MASK_AND_REG	0x328
#घोषणा HC_ATL_IRQ_MASK_AND_REG	0x32c

/* -----------------------------------------------------------------------------
 * Peripheral Controller
 */

/* Initialization Registers */
#घोषणा DC_ADDRESS			0x0200
#घोषणा DC_DEVEN			(1 << 7)

#घोषणा DC_MODE				0x020c
#घोषणा DC_DMACLKON			(1 << 9)
#घोषणा DC_VBUSSTAT			(1 << 8)
#घोषणा DC_CLKAON			(1 << 7)
#घोषणा DC_SNDRSU			(1 << 6)
#घोषणा DC_GOSUSP			(1 << 5)
#घोषणा DC_SFRESET			(1 << 4)
#घोषणा DC_GLINTENA			(1 << 3)
#घोषणा DC_WKUPCS			(1 << 2)

#घोषणा DC_INTCONF			0x0210
#घोषणा DC_CDBGMOD_ACK_NAK		(0 << 6)
#घोषणा DC_CDBGMOD_ACK			(1 << 6)
#घोषणा DC_CDBGMOD_ACK_1NAK		(2 << 6)
#घोषणा DC_DDBGMODIN_ACK_NAK		(0 << 4)
#घोषणा DC_DDBGMODIN_ACK		(1 << 4)
#घोषणा DC_DDBGMODIN_ACK_1NAK		(2 << 4)
#घोषणा DC_DDBGMODOUT_ACK_NYET_NAK	(0 << 2)
#घोषणा DC_DDBGMODOUT_ACK_NYET		(1 << 2)
#घोषणा DC_DDBGMODOUT_ACK_NYET_1NAK	(2 << 2)
#घोषणा DC_INTLVL			(1 << 1)
#घोषणा DC_INTPOL			(1 << 0)

#घोषणा DC_DEBUG			0x0212
#घोषणा DC_INTENABLE			0x0214
#घोषणा DC_IEPTX(n)			(1 << (11 + 2 * (n)))
#घोषणा DC_IEPRX(n)			(1 << (10 + 2 * (n)))
#घोषणा DC_IEPRXTX(n)			(3 << (10 + 2 * (n)))
#घोषणा DC_IEP0SETUP			(1 << 8)
#घोषणा DC_IEVBUS			(1 << 7)
#घोषणा DC_IEDMA			(1 << 6)
#घोषणा DC_IEHS_STA			(1 << 5)
#घोषणा DC_IERESM			(1 << 4)
#घोषणा DC_IESUSP			(1 << 3)
#घोषणा DC_IEPSOF			(1 << 2)
#घोषणा DC_IESOF			(1 << 1)
#घोषणा DC_IEBRST			(1 << 0)

/* Data Flow Registers */
#घोषणा DC_EPINDEX			0x022c
#घोषणा DC_EP0SETUP			(1 << 5)
#घोषणा DC_ENDPIDX(n)			((n) << 1)
#घोषणा DC_EPसूची			(1 << 0)

#घोषणा DC_CTRLFUNC			0x0228
#घोषणा DC_CLBUF			(1 << 4)
#घोषणा DC_VENDP			(1 << 3)
#घोषणा DC_DSEN				(1 << 2)
#घोषणा DC_STATUS			(1 << 1)
#घोषणा DC_STALL			(1 << 0)

#घोषणा DC_DATAPORT			0x0220
#घोषणा DC_BUFLEN			0x021c
#घोषणा DC_DATACOUNT_MASK		0xffff
#घोषणा DC_BUFSTAT			0x021e
#घोषणा DC_EPMAXPKTSZ			0x0204

#घोषणा DC_EPTYPE			0x0208
#घोषणा DC_NOEMPKT			(1 << 4)
#घोषणा DC_EPENABLE			(1 << 3)
#घोषणा DC_DBLBUF			(1 << 2)
#घोषणा DC_ENDPTYP_ISOC			(1 << 0)
#घोषणा DC_ENDPTYP_BULK			(2 << 0)
#घोषणा DC_ENDPTYP_INTERRUPT		(3 << 0)

/* DMA Registers */
#घोषणा DC_DMACMD			0x0230
#घोषणा DC_DMATXCOUNT			0x0234
#घोषणा DC_DMACONF			0x0238
#घोषणा DC_DMAHW			0x023c
#घोषणा DC_DMAINTREASON			0x0250
#घोषणा DC_DMAINTEN			0x0254
#घोषणा DC_DMAEP			0x0258
#घोषणा DC_DMABURSTCOUNT		0x0264

/* General Registers */
#घोषणा DC_INTERRUPT			0x0218
#घोषणा DC_CHIPID			0x0270
#घोषणा DC_FRAMENUM			0x0274
#घोषणा DC_SCRATCH			0x0278
#घोषणा DC_UNLOCKDEV			0x027c
#घोषणा DC_INTPULSEWIDTH		0x0280
#घोषणा DC_TESTMODE			0x0284

#पूर्ण_अगर

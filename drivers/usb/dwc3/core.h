<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * core.h - DesignWare USB3 DRD Core Header
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#अगर_अघोषित __DRIVERS_USB_DWC3_CORE_H
#घोषणा __DRIVERS_USB_DWC3_CORE_H

#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mm.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/ulpi/पूर्णांकerface.h>

#समावेश <linux/phy/phy.h>

#समावेश <linux/घातer_supply.h>

#घोषणा DWC3_MSG_MAX	500

/* Global स्थिरants */
#घोषणा DWC3_PULL_UP_TIMEOUT	500	/* ms */
#घोषणा DWC3_BOUNCE_SIZE	1024	/* size of a superspeed bulk */
#घोषणा DWC3_EP0_SETUP_SIZE	512
#घोषणा DWC3_ENDPOINTS_NUM	32
#घोषणा DWC3_XHCI_RESOURCES_NUM	2
#घोषणा DWC3_ISOC_MAX_RETRIES	5

#घोषणा DWC3_SCRATCHBUF_SIZE	4096	/* each buffer is assumed to be 4KiB */
#घोषणा DWC3_EVENT_BUFFERS_SIZE	4096
#घोषणा DWC3_EVENT_TYPE_MASK	0xfe

#घोषणा DWC3_EVENT_TYPE_DEV	0
#घोषणा DWC3_EVENT_TYPE_CARKIT	3
#घोषणा DWC3_EVENT_TYPE_I2C	4

#घोषणा DWC3_DEVICE_EVENT_DISCONNECT		0
#घोषणा DWC3_DEVICE_EVENT_RESET			1
#घोषणा DWC3_DEVICE_EVENT_CONNECT_DONE		2
#घोषणा DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE	3
#घोषणा DWC3_DEVICE_EVENT_WAKEUP		4
#घोषणा DWC3_DEVICE_EVENT_HIBER_REQ		5
#घोषणा DWC3_DEVICE_EVENT_SUSPEND		6
#घोषणा DWC3_DEVICE_EVENT_SOF			7
#घोषणा DWC3_DEVICE_EVENT_ERRATIC_ERROR		9
#घोषणा DWC3_DEVICE_EVENT_CMD_CMPL		10
#घोषणा DWC3_DEVICE_EVENT_OVERFLOW		11

/* Controller's role जबतक using the OTG block */
#घोषणा DWC3_OTG_ROLE_IDLE	0
#घोषणा DWC3_OTG_ROLE_HOST	1
#घोषणा DWC3_OTG_ROLE_DEVICE	2

#घोषणा DWC3_GEVNTCOUNT_MASK	0xfffc
#घोषणा DWC3_GEVNTCOUNT_EHB	BIT(31)
#घोषणा DWC3_GSNPSID_MASK	0xffff0000
#घोषणा DWC3_GSNPSREV_MASK	0xffff
#घोषणा DWC3_GSNPS_ID(p)	(((p) & DWC3_GSNPSID_MASK) >> 16)

/* DWC3 रेजिस्टरs memory space boundries */
#घोषणा DWC3_XHCI_REGS_START		0x0
#घोषणा DWC3_XHCI_REGS_END		0x7fff
#घोषणा DWC3_GLOBALS_REGS_START		0xc100
#घोषणा DWC3_GLOBALS_REGS_END		0xc6ff
#घोषणा DWC3_DEVICE_REGS_START		0xc700
#घोषणा DWC3_DEVICE_REGS_END		0xcbff
#घोषणा DWC3_OTG_REGS_START		0xcc00
#घोषणा DWC3_OTG_REGS_END		0xccff

/* Global Registers */
#घोषणा DWC3_GSBUSCFG0		0xc100
#घोषणा DWC3_GSBUSCFG1		0xc104
#घोषणा DWC3_GTXTHRCFG		0xc108
#घोषणा DWC3_GRXTHRCFG		0xc10c
#घोषणा DWC3_GCTL		0xc110
#घोषणा DWC3_GEVTEN		0xc114
#घोषणा DWC3_GSTS		0xc118
#घोषणा DWC3_GUCTL1		0xc11c
#घोषणा DWC3_GSNPSID		0xc120
#घोषणा DWC3_GGPIO		0xc124
#घोषणा DWC3_GUID		0xc128
#घोषणा DWC3_GUCTL		0xc12c
#घोषणा DWC3_GBUSERRADDR0	0xc130
#घोषणा DWC3_GBUSERRADDR1	0xc134
#घोषणा DWC3_GPRTBIMAP0		0xc138
#घोषणा DWC3_GPRTBIMAP1		0xc13c
#घोषणा DWC3_GHWPARAMS0		0xc140
#घोषणा DWC3_GHWPARAMS1		0xc144
#घोषणा DWC3_GHWPARAMS2		0xc148
#घोषणा DWC3_GHWPARAMS3		0xc14c
#घोषणा DWC3_GHWPARAMS4		0xc150
#घोषणा DWC3_GHWPARAMS5		0xc154
#घोषणा DWC3_GHWPARAMS6		0xc158
#घोषणा DWC3_GHWPARAMS7		0xc15c
#घोषणा DWC3_GDBGFIFOSPACE	0xc160
#घोषणा DWC3_GDBGLTSSM		0xc164
#घोषणा DWC3_GDBGBMU		0xc16c
#घोषणा DWC3_GDBGLSPMUX		0xc170
#घोषणा DWC3_GDBGLSP		0xc174
#घोषणा DWC3_GDBGEPINFO0	0xc178
#घोषणा DWC3_GDBGEPINFO1	0xc17c
#घोषणा DWC3_GPRTBIMAP_HS0	0xc180
#घोषणा DWC3_GPRTBIMAP_HS1	0xc184
#घोषणा DWC3_GPRTBIMAP_FS0	0xc188
#घोषणा DWC3_GPRTBIMAP_FS1	0xc18c
#घोषणा DWC3_GUCTL2		0xc19c

#घोषणा DWC3_VER_NUMBER		0xc1a0
#घोषणा DWC3_VER_TYPE		0xc1a4

#घोषणा DWC3_GUSB2PHYCFG(n)	(0xc200 + ((n) * 0x04))
#घोषणा DWC3_GUSB2I2CCTL(n)	(0xc240 + ((n) * 0x04))

#घोषणा DWC3_GUSB2PHYACC(n)	(0xc280 + ((n) * 0x04))

#घोषणा DWC3_GUSB3PIPECTL(n)	(0xc2c0 + ((n) * 0x04))

#घोषणा DWC3_GTXFIFOSIZ(n)	(0xc300 + ((n) * 0x04))
#घोषणा DWC3_GRXFIFOSIZ(n)	(0xc380 + ((n) * 0x04))

#घोषणा DWC3_GEVNTADRLO(n)	(0xc400 + ((n) * 0x10))
#घोषणा DWC3_GEVNTADRHI(n)	(0xc404 + ((n) * 0x10))
#घोषणा DWC3_GEVNTSIZ(n)	(0xc408 + ((n) * 0x10))
#घोषणा DWC3_GEVNTCOUNT(n)	(0xc40c + ((n) * 0x10))

#घोषणा DWC3_GHWPARAMS8		0xc600
#घोषणा DWC3_GUCTL3		0xc60c
#घोषणा DWC3_GFLADJ		0xc630
#घोषणा DWC3_GHWPARAMS9		0xc680

/* Device Registers */
#घोषणा DWC3_DCFG		0xc700
#घोषणा DWC3_DCTL		0xc704
#घोषणा DWC3_DEVTEN		0xc708
#घोषणा DWC3_DSTS		0xc70c
#घोषणा DWC3_DGCMDPAR		0xc710
#घोषणा DWC3_DGCMD		0xc714
#घोषणा DWC3_DALEPENA		0xc720

#घोषणा DWC3_DEP_BASE(n)	(0xc800 + ((n) * 0x10))
#घोषणा DWC3_DEPCMDPAR2		0x00
#घोषणा DWC3_DEPCMDPAR1		0x04
#घोषणा DWC3_DEPCMDPAR0		0x08
#घोषणा DWC3_DEPCMD		0x0c

#घोषणा DWC3_DEV_IMOD(n)	(0xca00 + ((n) * 0x4))

/* OTG Registers */
#घोषणा DWC3_OCFG		0xcc00
#घोषणा DWC3_OCTL		0xcc04
#घोषणा DWC3_OEVT		0xcc08
#घोषणा DWC3_OEVTEN		0xcc0C
#घोषणा DWC3_OSTS		0xcc10

/* Bit fields */

/* Global SoC Bus Configuration INCRx Register 0 */
#घोषणा DWC3_GSBUSCFG0_INCR256BRSTENA	(1 << 7) /* INCR256 burst */
#घोषणा DWC3_GSBUSCFG0_INCR128BRSTENA	(1 << 6) /* INCR128 burst */
#घोषणा DWC3_GSBUSCFG0_INCR64BRSTENA	(1 << 5) /* INCR64 burst */
#घोषणा DWC3_GSBUSCFG0_INCR32BRSTENA	(1 << 4) /* INCR32 burst */
#घोषणा DWC3_GSBUSCFG0_INCR16BRSTENA	(1 << 3) /* INCR16 burst */
#घोषणा DWC3_GSBUSCFG0_INCR8BRSTENA	(1 << 2) /* INCR8 burst */
#घोषणा DWC3_GSBUSCFG0_INCR4BRSTENA	(1 << 1) /* INCR4 burst */
#घोषणा DWC3_GSBUSCFG0_INCRBRSTENA	(1 << 0) /* undefined length enable */
#घोषणा DWC3_GSBUSCFG0_INCRBRST_MASK	0xff

/* Global Debug LSP MUX Select */
#घोषणा DWC3_GDBGLSPMUX_ENDBC		BIT(15)	/* Host only */
#घोषणा DWC3_GDBGLSPMUX_HOSTSELECT(n)	((n) & 0x3fff)
#घोषणा DWC3_GDBGLSPMUX_DEVSELECT(n)	(((n) & 0xf) << 4)
#घोषणा DWC3_GDBGLSPMUX_EPSELECT(n)	((n) & 0xf)

/* Global Debug Queue/FIFO Space Available Register */
#घोषणा DWC3_GDBGFIFOSPACE_NUM(n)	((n) & 0x1f)
#घोषणा DWC3_GDBGFIFOSPACE_TYPE(n)	(((n) << 5) & 0x1e0)
#घोषणा DWC3_GDBGFIFOSPACE_SPACE_AVAILABLE(n) (((n) >> 16) & 0xffff)

#घोषणा DWC3_TXFIFO		0
#घोषणा DWC3_RXFIFO		1
#घोषणा DWC3_TXREQQ		2
#घोषणा DWC3_RXREQQ		3
#घोषणा DWC3_RXINFOQ		4
#घोषणा DWC3_PSTATQ		5
#घोषणा DWC3_DESCFETCHQ		6
#घोषणा DWC3_EVENTQ		7
#घोषणा DWC3_AUXEVENTQ		8

/* Global RX Threshold Configuration Register */
#घोषणा DWC3_GRXTHRCFG_MAXRXBURSTSIZE(n) (((n) & 0x1f) << 19)
#घोषणा DWC3_GRXTHRCFG_RXPKTCNT(n) (((n) & 0xf) << 24)
#घोषणा DWC3_GRXTHRCFG_PKTCNTSEL BIT(29)

/* Global RX Threshold Configuration Register क्रम DWC_usb31 only */
#घोषणा DWC31_GRXTHRCFG_MAXRXBURSTSIZE(n)	(((n) & 0x1f) << 16)
#घोषणा DWC31_GRXTHRCFG_RXPKTCNT(n)		(((n) & 0x1f) << 21)
#घोषणा DWC31_GRXTHRCFG_PKTCNTSEL		BIT(26)
#घोषणा DWC31_RXTHRNUMPKTSEL_HS_PRD		BIT(15)
#घोषणा DWC31_RXTHRNUMPKT_HS_PRD(n)		(((n) & 0x3) << 13)
#घोषणा DWC31_RXTHRNUMPKTSEL_PRD		BIT(10)
#घोषणा DWC31_RXTHRNUMPKT_PRD(n)		(((n) & 0x1f) << 5)
#घोषणा DWC31_MAXRXBURSTSIZE_PRD(n)		((n) & 0x1f)

/* Global TX Threshold Configuration Register क्रम DWC_usb31 only */
#घोषणा DWC31_GTXTHRCFG_MAXTXBURSTSIZE(n)	(((n) & 0x1f) << 16)
#घोषणा DWC31_GTXTHRCFG_TXPKTCNT(n)		(((n) & 0x1f) << 21)
#घोषणा DWC31_GTXTHRCFG_PKTCNTSEL		BIT(26)
#घोषणा DWC31_TXTHRNUMPKTSEL_HS_PRD		BIT(15)
#घोषणा DWC31_TXTHRNUMPKT_HS_PRD(n)		(((n) & 0x3) << 13)
#घोषणा DWC31_TXTHRNUMPKTSEL_PRD		BIT(10)
#घोषणा DWC31_TXTHRNUMPKT_PRD(n)		(((n) & 0x1f) << 5)
#घोषणा DWC31_MAXTXBURSTSIZE_PRD(n)		((n) & 0x1f)

/* Global Configuration Register */
#घोषणा DWC3_GCTL_PWRDNSCALE(n)	((n) << 19)
#घोषणा DWC3_GCTL_U2RSTECN	BIT(16)
#घोषणा DWC3_GCTL_RAMCLKSEL(x)	(((x) & DWC3_GCTL_CLK_MASK) << 6)
#घोषणा DWC3_GCTL_CLK_BUS	(0)
#घोषणा DWC3_GCTL_CLK_PIPE	(1)
#घोषणा DWC3_GCTL_CLK_PIPEHALF	(2)
#घोषणा DWC3_GCTL_CLK_MASK	(3)

#घोषणा DWC3_GCTL_PRTCAP(n)	(((n) & (3 << 12)) >> 12)
#घोषणा DWC3_GCTL_PRTCAPसूची(n)	((n) << 12)
#घोषणा DWC3_GCTL_PRTCAP_HOST	1
#घोषणा DWC3_GCTL_PRTCAP_DEVICE	2
#घोषणा DWC3_GCTL_PRTCAP_OTG	3

#घोषणा DWC3_GCTL_CORESOFTRESET		BIT(11)
#घोषणा DWC3_GCTL_SOFITPSYNC		BIT(10)
#घोषणा DWC3_GCTL_SCALEDOWN(n)		((n) << 4)
#घोषणा DWC3_GCTL_SCALEDOWN_MASK	DWC3_GCTL_SCALEDOWN(3)
#घोषणा DWC3_GCTL_DISSCRAMBLE		BIT(3)
#घोषणा DWC3_GCTL_U2EXIT_LFPS		BIT(2)
#घोषणा DWC3_GCTL_GBLHIBERNATIONEN	BIT(1)
#घोषणा DWC3_GCTL_DSBLCLKGTNG		BIT(0)

/* Global User Control Register */
#घोषणा DWC3_GUCTL_HSTINAUTORETRY	BIT(14)

/* Global User Control 1 Register */
#घोषणा DWC3_GUCTL1_PARKMODE_DISABLE_SS	BIT(17)
#घोषणा DWC3_GUCTL1_TX_IPGAP_LINECHECK_DIS	BIT(28)
#घोषणा DWC3_GUCTL1_DEV_L1_EXIT_BY_HW	BIT(24)

/* Global Status Register */
#घोषणा DWC3_GSTS_OTG_IP	BIT(10)
#घोषणा DWC3_GSTS_BC_IP		BIT(9)
#घोषणा DWC3_GSTS_ADP_IP	BIT(8)
#घोषणा DWC3_GSTS_HOST_IP	BIT(7)
#घोषणा DWC3_GSTS_DEVICE_IP	BIT(6)
#घोषणा DWC3_GSTS_CSR_TIMEOUT	BIT(5)
#घोषणा DWC3_GSTS_BUS_ERR_ADDR_VLD	BIT(4)
#घोषणा DWC3_GSTS_CURMOD(n)	((n) & 0x3)
#घोषणा DWC3_GSTS_CURMOD_DEVICE	0
#घोषणा DWC3_GSTS_CURMOD_HOST	1

/* Global USB2 PHY Configuration Register */
#घोषणा DWC3_GUSB2PHYCFG_PHYSOFTRST	BIT(31)
#घोषणा DWC3_GUSB2PHYCFG_U2_FREECLK_EXISTS	BIT(30)
#घोषणा DWC3_GUSB2PHYCFG_SUSPHY		BIT(6)
#घोषणा DWC3_GUSB2PHYCFG_ULPI_UTMI	BIT(4)
#घोषणा DWC3_GUSB2PHYCFG_ENBLSLPM	BIT(8)
#घोषणा DWC3_GUSB2PHYCFG_PHYIF(n)	(n << 3)
#घोषणा DWC3_GUSB2PHYCFG_PHYIF_MASK	DWC3_GUSB2PHYCFG_PHYIF(1)
#घोषणा DWC3_GUSB2PHYCFG_USBTRDTIM(n)	(n << 10)
#घोषणा DWC3_GUSB2PHYCFG_USBTRDTIM_MASK	DWC3_GUSB2PHYCFG_USBTRDTIM(0xf)
#घोषणा USBTRDTIM_UTMI_8_BIT		9
#घोषणा USBTRDTIM_UTMI_16_BIT		5
#घोषणा UTMI_PHYIF_16_BIT		1
#घोषणा UTMI_PHYIF_8_BIT		0

/* Global USB2 PHY Venकरोr Control Register */
#घोषणा DWC3_GUSB2PHYACC_NEWREGREQ	BIT(25)
#घोषणा DWC3_GUSB2PHYACC_DONE		BIT(24)
#घोषणा DWC3_GUSB2PHYACC_BUSY		BIT(23)
#घोषणा DWC3_GUSB2PHYACC_WRITE		BIT(22)
#घोषणा DWC3_GUSB2PHYACC_ADDR(n)	(n << 16)
#घोषणा DWC3_GUSB2PHYACC_EXTEND_ADDR(n)	(n << 8)
#घोषणा DWC3_GUSB2PHYACC_DATA(n)	(n & 0xff)

/* Global USB3 PIPE Control Register */
#घोषणा DWC3_GUSB3PIPECTL_PHYSOFTRST	BIT(31)
#घोषणा DWC3_GUSB3PIPECTL_U2SSINP3OK	BIT(29)
#घोषणा DWC3_GUSB3PIPECTL_DISRXDETINP3	BIT(28)
#घोषणा DWC3_GUSB3PIPECTL_UX_EXIT_PX	BIT(27)
#घोषणा DWC3_GUSB3PIPECTL_REQP1P2P3	BIT(24)
#घोषणा DWC3_GUSB3PIPECTL_DEP1P2P3(n)	((n) << 19)
#घोषणा DWC3_GUSB3PIPECTL_DEP1P2P3_MASK	DWC3_GUSB3PIPECTL_DEP1P2P3(7)
#घोषणा DWC3_GUSB3PIPECTL_DEP1P2P3_EN	DWC3_GUSB3PIPECTL_DEP1P2P3(1)
#घोषणा DWC3_GUSB3PIPECTL_DEPOCHANGE	BIT(18)
#घोषणा DWC3_GUSB3PIPECTL_SUSPHY	BIT(17)
#घोषणा DWC3_GUSB3PIPECTL_LFPSFILT	BIT(9)
#घोषणा DWC3_GUSB3PIPECTL_RX_DETOPOLL	BIT(8)
#घोषणा DWC3_GUSB3PIPECTL_TX_DEEPH_MASK	DWC3_GUSB3PIPECTL_TX_DEEPH(3)
#घोषणा DWC3_GUSB3PIPECTL_TX_DEEPH(n)	((n) << 1)

/* Global TX Fअगरo Size Register */
#घोषणा DWC31_GTXFIFOSIZ_TXFRAMNUM	BIT(15)		/* DWC_usb31 only */
#घोषणा DWC31_GTXFIFOSIZ_TXFDEP(n)	((n) & 0x7fff)	/* DWC_usb31 only */
#घोषणा DWC3_GTXFIFOSIZ_TXFDEP(n)	((n) & 0xffff)
#घोषणा DWC3_GTXFIFOSIZ_TXFSTADDR(n)	((n) & 0xffff0000)

/* Global RX Fअगरo Size Register */
#घोषणा DWC31_GRXFIFOSIZ_RXFDEP(n)	((n) & 0x7fff)	/* DWC_usb31 only */
#घोषणा DWC3_GRXFIFOSIZ_RXFDEP(n)	((n) & 0xffff)

/* Global Event Size Registers */
#घोषणा DWC3_GEVNTSIZ_INTMASK		BIT(31)
#घोषणा DWC3_GEVNTSIZ_SIZE(n)		((n) & 0xffff)

/* Global HWPARAMS0 Register */
#घोषणा DWC3_GHWPARAMS0_MODE(n)		((n) & 0x3)
#घोषणा DWC3_GHWPARAMS0_MODE_GADGET	0
#घोषणा DWC3_GHWPARAMS0_MODE_HOST	1
#घोषणा DWC3_GHWPARAMS0_MODE_DRD	2
#घोषणा DWC3_GHWPARAMS0_MBUS_TYPE(n)	(((n) >> 3) & 0x7)
#घोषणा DWC3_GHWPARAMS0_SBUS_TYPE(n)	(((n) >> 6) & 0x3)
#घोषणा DWC3_GHWPARAMS0_MDWIDTH(n)	(((n) >> 8) & 0xff)
#घोषणा DWC3_GHWPARAMS0_SDWIDTH(n)	(((n) >> 16) & 0xff)
#घोषणा DWC3_GHWPARAMS0_AWIDTH(n)	(((n) >> 24) & 0xff)

/* Global HWPARAMS1 Register */
#घोषणा DWC3_GHWPARAMS1_EN_PWROPT(n)	(((n) & (3 << 24)) >> 24)
#घोषणा DWC3_GHWPARAMS1_EN_PWROPT_NO	0
#घोषणा DWC3_GHWPARAMS1_EN_PWROPT_CLK	1
#घोषणा DWC3_GHWPARAMS1_EN_PWROPT_HIB	2
#घोषणा DWC3_GHWPARAMS1_PWROPT(n)	((n) << 24)
#घोषणा DWC3_GHWPARAMS1_PWROPT_MASK	DWC3_GHWPARAMS1_PWROPT(3)
#घोषणा DWC3_GHWPARAMS1_ENDBC		BIT(31)

/* Global HWPARAMS3 Register */
#घोषणा DWC3_GHWPARAMS3_SSPHY_IFC(n)		((n) & 3)
#घोषणा DWC3_GHWPARAMS3_SSPHY_IFC_DIS		0
#घोषणा DWC3_GHWPARAMS3_SSPHY_IFC_GEN1		1
#घोषणा DWC3_GHWPARAMS3_SSPHY_IFC_GEN2		2 /* DWC_usb31 only */
#घोषणा DWC3_GHWPARAMS3_HSPHY_IFC(n)		(((n) & (3 << 2)) >> 2)
#घोषणा DWC3_GHWPARAMS3_HSPHY_IFC_DIS		0
#घोषणा DWC3_GHWPARAMS3_HSPHY_IFC_UTMI		1
#घोषणा DWC3_GHWPARAMS3_HSPHY_IFC_ULPI		2
#घोषणा DWC3_GHWPARAMS3_HSPHY_IFC_UTMI_ULPI	3
#घोषणा DWC3_GHWPARAMS3_FSPHY_IFC(n)		(((n) & (3 << 4)) >> 4)
#घोषणा DWC3_GHWPARAMS3_FSPHY_IFC_DIS		0
#घोषणा DWC3_GHWPARAMS3_FSPHY_IFC_ENA		1

/* Global HWPARAMS4 Register */
#घोषणा DWC3_GHWPARAMS4_HIBER_SCRATCHBUFS(n)	(((n) & (0x0f << 13)) >> 13)
#घोषणा DWC3_MAX_HIBER_SCRATCHBUFS		15

/* Global HWPARAMS6 Register */
#घोषणा DWC3_GHWPARAMS6_BCSUPPORT		BIT(14)
#घोषणा DWC3_GHWPARAMS6_OTG3SUPPORT		BIT(13)
#घोषणा DWC3_GHWPARAMS6_ADPSUPPORT		BIT(12)
#घोषणा DWC3_GHWPARAMS6_HNPSUPPORT		BIT(11)
#घोषणा DWC3_GHWPARAMS6_SRPSUPPORT		BIT(10)
#घोषणा DWC3_GHWPARAMS6_EN_FPGA			BIT(7)

/* DWC_usb32 only */
#घोषणा DWC3_GHWPARAMS6_MDWIDTH(n)		((n) & (0x3 << 8))

/* Global HWPARAMS7 Register */
#घोषणा DWC3_GHWPARAMS7_RAM1_DEPTH(n)	((n) & 0xffff)
#घोषणा DWC3_GHWPARAMS7_RAM2_DEPTH(n)	(((n) >> 16) & 0xffff)

/* Global HWPARAMS9 Register */
#घोषणा DWC3_GHWPARAMS9_DEV_TXF_FLUSH_BYPASS	BIT(0)

/* Global Frame Length Adjusपंचांगent Register */
#घोषणा DWC3_GFLADJ_30MHZ_SDBND_SEL		BIT(7)
#घोषणा DWC3_GFLADJ_30MHZ_MASK			0x3f

/* Global User Control Register 2 */
#घोषणा DWC3_GUCTL2_RST_ACTBITLATER		BIT(14)

/* Global User Control Register 3 */
#घोषणा DWC3_GUCTL3_SPLITDISABLE		BIT(14)

/* Device Configuration Register */
#घोषणा DWC3_DCFG_NUMLANES(n)	(((n) & 0x3) << 30) /* DWC_usb32 only */

#घोषणा DWC3_DCFG_DEVADDR(addr)	((addr) << 3)
#घोषणा DWC3_DCFG_DEVADDR_MASK	DWC3_DCFG_DEVADDR(0x7f)

#घोषणा DWC3_DCFG_SPEED_MASK	(7 << 0)
#घोषणा DWC3_DCFG_SUPERSPEED_PLUS (5 << 0)  /* DWC_usb31 only */
#घोषणा DWC3_DCFG_SUPERSPEED	(4 << 0)
#घोषणा DWC3_DCFG_HIGHSPEED	(0 << 0)
#घोषणा DWC3_DCFG_FULLSPEED	BIT(0)

#घोषणा DWC3_DCFG_NUMP_SHIFT	17
#घोषणा DWC3_DCFG_NUMP(n)	(((n) >> DWC3_DCFG_NUMP_SHIFT) & 0x1f)
#घोषणा DWC3_DCFG_NUMP_MASK	(0x1f << DWC3_DCFG_NUMP_SHIFT)
#घोषणा DWC3_DCFG_LPM_CAP	BIT(22)
#घोषणा DWC3_DCFG_IGNSTRMPP	BIT(23)

/* Device Control Register */
#घोषणा DWC3_DCTL_RUN_STOP	BIT(31)
#घोषणा DWC3_DCTL_CSFTRST	BIT(30)
#घोषणा DWC3_DCTL_LSFTRST	BIT(29)

#घोषणा DWC3_DCTL_HIRD_THRES_MASK	(0x1f << 24)
#घोषणा DWC3_DCTL_HIRD_THRES(n)	((n) << 24)

#घोषणा DWC3_DCTL_APPL1RES	BIT(23)

/* These apply क्रम core versions 1.87a and earlier */
#घोषणा DWC3_DCTL_TRGTULST_MASK		(0x0f << 17)
#घोषणा DWC3_DCTL_TRGTULST(n)		((n) << 17)
#घोषणा DWC3_DCTL_TRGTULST_U2		(DWC3_DCTL_TRGTULST(2))
#घोषणा DWC3_DCTL_TRGTULST_U3		(DWC3_DCTL_TRGTULST(3))
#घोषणा DWC3_DCTL_TRGTULST_SS_DIS	(DWC3_DCTL_TRGTULST(4))
#घोषणा DWC3_DCTL_TRGTULST_RX_DET	(DWC3_DCTL_TRGTULST(5))
#घोषणा DWC3_DCTL_TRGTULST_SS_INACT	(DWC3_DCTL_TRGTULST(6))

/* These apply क्रम core versions 1.94a and later */
#घोषणा DWC3_DCTL_NYET_THRES(n)		(((n) & 0xf) << 20)

#घोषणा DWC3_DCTL_KEEP_CONNECT		BIT(19)
#घोषणा DWC3_DCTL_L1_HIBER_EN		BIT(18)
#घोषणा DWC3_DCTL_CRS			BIT(17)
#घोषणा DWC3_DCTL_CSS			BIT(16)

#घोषणा DWC3_DCTL_INITU2ENA		BIT(12)
#घोषणा DWC3_DCTL_ACCEPTU2ENA		BIT(11)
#घोषणा DWC3_DCTL_INITU1ENA		BIT(10)
#घोषणा DWC3_DCTL_ACCEPTU1ENA		BIT(9)
#घोषणा DWC3_DCTL_TSTCTRL_MASK		(0xf << 1)

#घोषणा DWC3_DCTL_ULSTCHNGREQ_MASK	(0x0f << 5)
#घोषणा DWC3_DCTL_ULSTCHNGREQ(n) (((n) << 5) & DWC3_DCTL_ULSTCHNGREQ_MASK)

#घोषणा DWC3_DCTL_ULSTCHNG_NO_ACTION	(DWC3_DCTL_ULSTCHNGREQ(0))
#घोषणा DWC3_DCTL_ULSTCHNG_SS_DISABLED	(DWC3_DCTL_ULSTCHNGREQ(4))
#घोषणा DWC3_DCTL_ULSTCHNG_RX_DETECT	(DWC3_DCTL_ULSTCHNGREQ(5))
#घोषणा DWC3_DCTL_ULSTCHNG_SS_INACTIVE	(DWC3_DCTL_ULSTCHNGREQ(6))
#घोषणा DWC3_DCTL_ULSTCHNG_RECOVERY	(DWC3_DCTL_ULSTCHNGREQ(8))
#घोषणा DWC3_DCTL_ULSTCHNG_COMPLIANCE	(DWC3_DCTL_ULSTCHNGREQ(10))
#घोषणा DWC3_DCTL_ULSTCHNG_LOOPBACK	(DWC3_DCTL_ULSTCHNGREQ(11))

/* Device Event Enable Register */
#घोषणा DWC3_DEVTEN_VNDRDEVTSTRCVEDEN	BIT(12)
#घोषणा DWC3_DEVTEN_EVNTOVERFLOWEN	BIT(11)
#घोषणा DWC3_DEVTEN_CMDCMPLTEN		BIT(10)
#घोषणा DWC3_DEVTEN_ERRTICERREN		BIT(9)
#घोषणा DWC3_DEVTEN_SOFEN		BIT(7)
#घोषणा DWC3_DEVTEN_U3L2L1SUSPEN	BIT(6)
#घोषणा DWC3_DEVTEN_HIBERNATIONREQEVTEN	BIT(5)
#घोषणा DWC3_DEVTEN_WKUPEVTEN		BIT(4)
#घोषणा DWC3_DEVTEN_ULSTCNGEN		BIT(3)
#घोषणा DWC3_DEVTEN_CONNECTDONEEN	BIT(2)
#घोषणा DWC3_DEVTEN_USBRSTEN		BIT(1)
#घोषणा DWC3_DEVTEN_DISCONNEVTEN	BIT(0)

#घोषणा DWC3_DSTS_CONNLANES(n)		(((n) >> 30) & 0x3) /* DWC_usb32 only */

/* Device Status Register */
#घोषणा DWC3_DSTS_DCNRD			BIT(29)

/* This applies क्रम core versions 1.87a and earlier */
#घोषणा DWC3_DSTS_PWRUPREQ		BIT(24)

/* These apply क्रम core versions 1.94a and later */
#घोषणा DWC3_DSTS_RSS			BIT(25)
#घोषणा DWC3_DSTS_SSS			BIT(24)

#घोषणा DWC3_DSTS_COREIDLE		BIT(23)
#घोषणा DWC3_DSTS_DEVCTRLHLT		BIT(22)

#घोषणा DWC3_DSTS_USBLNKST_MASK		(0x0f << 18)
#घोषणा DWC3_DSTS_USBLNKST(n)		(((n) & DWC3_DSTS_USBLNKST_MASK) >> 18)

#घोषणा DWC3_DSTS_RXFIFOEMPTY		BIT(17)

#घोषणा DWC3_DSTS_SOFFN_MASK		(0x3fff << 3)
#घोषणा DWC3_DSTS_SOFFN(n)		(((n) & DWC3_DSTS_SOFFN_MASK) >> 3)

#घोषणा DWC3_DSTS_CONNECTSPD		(7 << 0)

#घोषणा DWC3_DSTS_SUPERSPEED_PLUS	(5 << 0) /* DWC_usb31 only */
#घोषणा DWC3_DSTS_SUPERSPEED		(4 << 0)
#घोषणा DWC3_DSTS_HIGHSPEED		(0 << 0)
#घोषणा DWC3_DSTS_FULLSPEED		BIT(0)

/* Device Generic Command Register */
#घोषणा DWC3_DGCMD_SET_LMP		0x01
#घोषणा DWC3_DGCMD_SET_PERIODIC_PAR	0x02
#घोषणा DWC3_DGCMD_XMIT_FUNCTION	0x03

/* These apply क्रम core versions 1.94a and later */
#घोषणा DWC3_DGCMD_SET_SCRATCHPAD_ADDR_LO	0x04
#घोषणा DWC3_DGCMD_SET_SCRATCHPAD_ADDR_HI	0x05

#घोषणा DWC3_DGCMD_SELECTED_FIFO_FLUSH	0x09
#घोषणा DWC3_DGCMD_ALL_FIFO_FLUSH	0x0a
#घोषणा DWC3_DGCMD_SET_ENDPOINT_NRDY	0x0c
#घोषणा DWC3_DGCMD_SET_ENDPOINT_PRIME	0x0d
#घोषणा DWC3_DGCMD_RUN_SOC_BUS_LOOPBACK	0x10

#घोषणा DWC3_DGCMD_STATUS(n)		(((n) >> 12) & 0x0F)
#घोषणा DWC3_DGCMD_CMDACT		BIT(10)
#घोषणा DWC3_DGCMD_CMDIOC		BIT(8)

/* Device Generic Command Parameter Register */
#घोषणा DWC3_DGCMDPAR_FORCE_LINKPM_ACCEPT	BIT(0)
#घोषणा DWC3_DGCMDPAR_FIFO_NUM(n)		((n) << 0)
#घोषणा DWC3_DGCMDPAR_RX_FIFO			(0 << 5)
#घोषणा DWC3_DGCMDPAR_TX_FIFO			BIT(5)
#घोषणा DWC3_DGCMDPAR_LOOPBACK_DIS		(0 << 0)
#घोषणा DWC3_DGCMDPAR_LOOPBACK_ENA		BIT(0)

/* Device Endpoपूर्णांक Command Register */
#घोषणा DWC3_DEPCMD_PARAM_SHIFT		16
#घोषणा DWC3_DEPCMD_PARAM(x)		((x) << DWC3_DEPCMD_PARAM_SHIFT)
#घोषणा DWC3_DEPCMD_GET_RSC_IDX(x)	(((x) >> DWC3_DEPCMD_PARAM_SHIFT) & 0x7f)
#घोषणा DWC3_DEPCMD_STATUS(x)		(((x) >> 12) & 0x0F)
#घोषणा DWC3_DEPCMD_HIPRI_FORCERM	BIT(11)
#घोषणा DWC3_DEPCMD_CLEARPENDIN		BIT(11)
#घोषणा DWC3_DEPCMD_CMDACT		BIT(10)
#घोषणा DWC3_DEPCMD_CMDIOC		BIT(8)

#घोषणा DWC3_DEPCMD_DEPSTARTCFG		(0x09 << 0)
#घोषणा DWC3_DEPCMD_ENDTRANSFER		(0x08 << 0)
#घोषणा DWC3_DEPCMD_UPDATETRANSFER	(0x07 << 0)
#घोषणा DWC3_DEPCMD_STARTTRANSFER	(0x06 << 0)
#घोषणा DWC3_DEPCMD_CLEARSTALL		(0x05 << 0)
#घोषणा DWC3_DEPCMD_SETSTALL		(0x04 << 0)
/* This applies क्रम core versions 1.90a and earlier */
#घोषणा DWC3_DEPCMD_GETSEQNUMBER	(0x03 << 0)
/* This applies क्रम core versions 1.94a and later */
#घोषणा DWC3_DEPCMD_GETEPSTATE		(0x03 << 0)
#घोषणा DWC3_DEPCMD_SETTRANSFRESOURCE	(0x02 << 0)
#घोषणा DWC3_DEPCMD_SETEPCONFIG		(0x01 << 0)

#घोषणा DWC3_DEPCMD_CMD(x)		((x) & 0xf)

/* The EP number goes 0..31 so ep0 is always out and ep1 is always in */
#घोषणा DWC3_DALEPENA_EP(n)		BIT(n)

#घोषणा DWC3_DEPCMD_TYPE_CONTROL	0
#घोषणा DWC3_DEPCMD_TYPE_ISOC		1
#घोषणा DWC3_DEPCMD_TYPE_BULK		2
#घोषणा DWC3_DEPCMD_TYPE_INTR		3

#घोषणा DWC3_DEV_IMOD_COUNT_SHIFT	16
#घोषणा DWC3_DEV_IMOD_COUNT_MASK	(0xffff << 16)
#घोषणा DWC3_DEV_IMOD_INTERVAL_SHIFT	0
#घोषणा DWC3_DEV_IMOD_INTERVAL_MASK	(0xffff << 0)

/* OTG Configuration Register */
#घोषणा DWC3_OCFG_DISPWRCUTTOFF		BIT(5)
#घोषणा DWC3_OCFG_HIBDISMASK		BIT(4)
#घोषणा DWC3_OCFG_SFTRSTMASK		BIT(3)
#घोषणा DWC3_OCFG_OTGVERSION		BIT(2)
#घोषणा DWC3_OCFG_HNPCAP		BIT(1)
#घोषणा DWC3_OCFG_SRPCAP		BIT(0)

/* OTG CTL Register */
#घोषणा DWC3_OCTL_OTG3GOERR		BIT(7)
#घोषणा DWC3_OCTL_PERIMODE		BIT(6)
#घोषणा DWC3_OCTL_PRTPWRCTL		BIT(5)
#घोषणा DWC3_OCTL_HNPREQ		BIT(4)
#घोषणा DWC3_OCTL_SESREQ		BIT(3)
#घोषणा DWC3_OCTL_TERMSELIDPULSE	BIT(2)
#घोषणा DWC3_OCTL_DEVSETHNPEN		BIT(1)
#घोषणा DWC3_OCTL_HSTSETHNPEN		BIT(0)

/* OTG Event Register */
#घोषणा DWC3_OEVT_DEVICEMODE		BIT(31)
#घोषणा DWC3_OEVT_XHCIRUNSTPSET		BIT(27)
#घोषणा DWC3_OEVT_DEVRUNSTPSET		BIT(26)
#घोषणा DWC3_OEVT_HIBENTRY		BIT(25)
#घोषणा DWC3_OEVT_CONIDSTSCHNG		BIT(24)
#घोषणा DWC3_OEVT_HRRCONFNOTIF		BIT(23)
#घोषणा DWC3_OEVT_HRRINITNOTIF		BIT(22)
#घोषणा DWC3_OEVT_ADEVIDLE		BIT(21)
#घोषणा DWC3_OEVT_ADEVBHOSTEND		BIT(20)
#घोषणा DWC3_OEVT_ADEVHOST		BIT(19)
#घोषणा DWC3_OEVT_ADEVHNPCHNG		BIT(18)
#घोषणा DWC3_OEVT_ADEVSRPDET		BIT(17)
#घोषणा DWC3_OEVT_ADEVSESSENDDET	BIT(16)
#घोषणा DWC3_OEVT_BDEVBHOSTEND		BIT(11)
#घोषणा DWC3_OEVT_BDEVHNPCHNG		BIT(10)
#घोषणा DWC3_OEVT_BDEVSESSVLDDET	BIT(9)
#घोषणा DWC3_OEVT_BDEVVBUSCHNG		BIT(8)
#घोषणा DWC3_OEVT_BSESSVLD		BIT(3)
#घोषणा DWC3_OEVT_HSTNEGSTS		BIT(2)
#घोषणा DWC3_OEVT_SESREQSTS		BIT(1)
#घोषणा DWC3_OEVT_ERROR			BIT(0)

/* OTG Event Enable Register */
#घोषणा DWC3_OEVTEN_XHCIRUNSTPSETEN	BIT(27)
#घोषणा DWC3_OEVTEN_DEVRUNSTPSETEN	BIT(26)
#घोषणा DWC3_OEVTEN_HIBENTRYEN		BIT(25)
#घोषणा DWC3_OEVTEN_CONIDSTSCHNGEN	BIT(24)
#घोषणा DWC3_OEVTEN_HRRCONFNOTIFEN	BIT(23)
#घोषणा DWC3_OEVTEN_HRRINITNOTIFEN	BIT(22)
#घोषणा DWC3_OEVTEN_ADEVIDLEEN		BIT(21)
#घोषणा DWC3_OEVTEN_ADEVBHOSTENDEN	BIT(20)
#घोषणा DWC3_OEVTEN_ADEVHOSTEN		BIT(19)
#घोषणा DWC3_OEVTEN_ADEVHNPCHNGEN	BIT(18)
#घोषणा DWC3_OEVTEN_ADEVSRPDETEN	BIT(17)
#घोषणा DWC3_OEVTEN_ADEVSESSENDDETEN	BIT(16)
#घोषणा DWC3_OEVTEN_BDEVBHOSTENDEN	BIT(11)
#घोषणा DWC3_OEVTEN_BDEVHNPCHNGEN	BIT(10)
#घोषणा DWC3_OEVTEN_BDEVSESSVLDDETEN	BIT(9)
#घोषणा DWC3_OEVTEN_BDEVVBUSCHNGEN	BIT(8)

/* OTG Status Register */
#घोषणा DWC3_OSTS_DEVRUNSTP		BIT(13)
#घोषणा DWC3_OSTS_XHCIRUNSTP		BIT(12)
#घोषणा DWC3_OSTS_PERIPHERALSTATE	BIT(4)
#घोषणा DWC3_OSTS_XHCIPRTPOWER		BIT(3)
#घोषणा DWC3_OSTS_BSESVLD		BIT(2)
#घोषणा DWC3_OSTS_VBUSVLD		BIT(1)
#घोषणा DWC3_OSTS_CONIDSTS		BIT(0)

/* Structures */

काष्ठा dwc3_trb;

/**
 * काष्ठा dwc3_event_buffer - Software event buffer representation
 * @buf: _THE_ buffer
 * @cache: The buffer cache used in the thपढ़ोed पूर्णांकerrupt
 * @length: size of this buffer
 * @lpos: event offset
 * @count: cache of last पढ़ो event count रेजिस्टर
 * @flags: flags related to this event buffer
 * @dma: dma_addr_t
 * @dwc: poपूर्णांकer to DWC controller
 */
काष्ठा dwc3_event_buffer अणु
	व्योम			*buf;
	व्योम			*cache;
	अचिन्हित पूर्णांक		length;
	अचिन्हित पूर्णांक		lpos;
	अचिन्हित पूर्णांक		count;
	अचिन्हित पूर्णांक		flags;

#घोषणा DWC3_EVENT_PENDING	BIT(0)

	dma_addr_t		dma;

	काष्ठा dwc3		*dwc;
पूर्ण;

#घोषणा DWC3_EP_FLAG_STALLED	BIT(0)
#घोषणा DWC3_EP_FLAG_WEDGED	BIT(1)

#घोषणा DWC3_EP_सूचीECTION_TX	true
#घोषणा DWC3_EP_सूचीECTION_RX	false

#घोषणा DWC3_TRB_NUM		256

/**
 * काष्ठा dwc3_ep - device side endpoपूर्णांक representation
 * @endpoपूर्णांक: usb endpoपूर्णांक
 * @cancelled_list: list of cancelled requests क्रम this endpoपूर्णांक
 * @pending_list: list of pending requests क्रम this endpoपूर्णांक
 * @started_list: list of started requests on this endpoपूर्णांक
 * @regs: poपूर्णांकer to first endpoपूर्णांक रेजिस्टर
 * @trb_pool: array of transaction buffers
 * @trb_pool_dma: dma address of @trb_pool
 * @trb_enqueue: enqueue 'pointer' पूर्णांकo TRB array
 * @trb_dequeue: dequeue 'pointer' पूर्णांकo TRB array
 * @dwc: poपूर्णांकer to DWC controller
 * @saved_state: ep state saved during hibernation
 * @flags: endpoपूर्णांक flags (wedged, stalled, ...)
 * @number: endpoपूर्णांक number (1 - 15)
 * @type: set to bmAttributes & USB_ENDPOINT_XFERTYPE_MASK
 * @resource_index: Resource transfer index
 * @frame_number: set to the frame number we want this transfer to start (ISOC)
 * @पूर्णांकerval: the पूर्णांकerval on which the ISOC transfer is started
 * @name: a human पढ़ोable name e.g. ep1out-bulk
 * @direction: true क्रम TX, false क्रम RX
 * @stream_capable: true when streams are enabled
 * @combo_num: the test combination BIT[15:14] of the frame number to test
 *		isochronous START TRANSFER command failure workaround
 * @start_cmd_status: the status of testing START TRANSFER command with
 *		combo_num = 'b00
 */
काष्ठा dwc3_ep अणु
	काष्ठा usb_ep		endpoपूर्णांक;
	काष्ठा list_head	cancelled_list;
	काष्ठा list_head	pending_list;
	काष्ठा list_head	started_list;

	व्योम __iomem		*regs;

	काष्ठा dwc3_trb		*trb_pool;
	dma_addr_t		trb_pool_dma;
	काष्ठा dwc3		*dwc;

	u32			saved_state;
	अचिन्हित पूर्णांक		flags;
#घोषणा DWC3_EP_ENABLED		BIT(0)
#घोषणा DWC3_EP_STALL		BIT(1)
#घोषणा DWC3_EP_WEDGE		BIT(2)
#घोषणा DWC3_EP_TRANSFER_STARTED BIT(3)
#घोषणा DWC3_EP_END_TRANSFER_PENDING BIT(4)
#घोषणा DWC3_EP_PENDING_REQUEST	BIT(5)
#घोषणा DWC3_EP_DELAY_START	BIT(6)
#घोषणा DWC3_EP_WAIT_TRANSFER_COMPLETE	BIT(7)
#घोषणा DWC3_EP_IGNORE_NEXT_NOSTREAM	BIT(8)
#घोषणा DWC3_EP_FORCE_RESTART_STREAM	BIT(9)
#घोषणा DWC3_EP_FIRST_STREAM_PRIMED	BIT(10)
#घोषणा DWC3_EP_PENDING_CLEAR_STALL	BIT(11)

	/* This last one is specअगरic to EP0 */
#घोषणा DWC3_EP0_सूची_IN		BIT(31)

	/*
	 * IMPORTANT: we *know* we have 256 TRBs in our @trb_pool, so we will
	 * use a u8 type here. If anybody decides to increase number of TRBs to
	 * anything larger than 256 - I can't see why people would want to करो
	 * this though - then this type needs to be changed.
	 *
	 * By using u8 types we ensure that our % चालक when incrementing
	 * enqueue and dequeue get optimized away by the compiler.
	 */
	u8			trb_enqueue;
	u8			trb_dequeue;

	u8			number;
	u8			type;
	u8			resource_index;
	u32			frame_number;
	u32			पूर्णांकerval;

	अक्षर			name[20];

	अचिन्हित		direction:1;
	अचिन्हित		stream_capable:1;

	/* For isochronous START TRANSFER workaround only */
	u8			combo_num;
	पूर्णांक			start_cmd_status;
पूर्ण;

क्रमागत dwc3_phy अणु
	DWC3_PHY_UNKNOWN = 0,
	DWC3_PHY_USB3,
	DWC3_PHY_USB2,
पूर्ण;

क्रमागत dwc3_ep0_next अणु
	DWC3_EP0_UNKNOWN = 0,
	DWC3_EP0_COMPLETE,
	DWC3_EP0_NRDY_DATA,
	DWC3_EP0_NRDY_STATUS,
पूर्ण;

क्रमागत dwc3_ep0_state अणु
	EP0_UNCONNECTED		= 0,
	EP0_SETUP_PHASE,
	EP0_DATA_PHASE,
	EP0_STATUS_PHASE,
पूर्ण;

क्रमागत dwc3_link_state अणु
	/* In SuperSpeed */
	DWC3_LINK_STATE_U0		= 0x00, /* in HS, means ON */
	DWC3_LINK_STATE_U1		= 0x01,
	DWC3_LINK_STATE_U2		= 0x02, /* in HS, means SLEEP */
	DWC3_LINK_STATE_U3		= 0x03, /* in HS, means SUSPEND */
	DWC3_LINK_STATE_SS_DIS		= 0x04,
	DWC3_LINK_STATE_RX_DET		= 0x05, /* in HS, means Early Suspend */
	DWC3_LINK_STATE_SS_INACT	= 0x06,
	DWC3_LINK_STATE_POLL		= 0x07,
	DWC3_LINK_STATE_RECOV		= 0x08,
	DWC3_LINK_STATE_HRESET		= 0x09,
	DWC3_LINK_STATE_CMPLY		= 0x0a,
	DWC3_LINK_STATE_LPBK		= 0x0b,
	DWC3_LINK_STATE_RESET		= 0x0e,
	DWC3_LINK_STATE_RESUME		= 0x0f,
	DWC3_LINK_STATE_MASK		= 0x0f,
पूर्ण;

/* TRB Length, PCM and Status */
#घोषणा DWC3_TRB_SIZE_MASK	(0x00ffffff)
#घोषणा DWC3_TRB_SIZE_LENGTH(n)	((n) & DWC3_TRB_SIZE_MASK)
#घोषणा DWC3_TRB_SIZE_PCM1(n)	(((n) & 0x03) << 24)
#घोषणा DWC3_TRB_SIZE_TRBSTS(n)	(((n) & (0x0f << 28)) >> 28)

#घोषणा DWC3_TRBSTS_OK			0
#घोषणा DWC3_TRBSTS_MISSED_ISOC		1
#घोषणा DWC3_TRBSTS_SETUP_PENDING	2
#घोषणा DWC3_TRB_STS_XFER_IN_PROG	4

/* TRB Control */
#घोषणा DWC3_TRB_CTRL_HWO		BIT(0)
#घोषणा DWC3_TRB_CTRL_LST		BIT(1)
#घोषणा DWC3_TRB_CTRL_CHN		BIT(2)
#घोषणा DWC3_TRB_CTRL_CSP		BIT(3)
#घोषणा DWC3_TRB_CTRL_TRBCTL(n)		(((n) & 0x3f) << 4)
#घोषणा DWC3_TRB_CTRL_ISP_IMI		BIT(10)
#घोषणा DWC3_TRB_CTRL_IOC		BIT(11)
#घोषणा DWC3_TRB_CTRL_SID_SOFN(n)	(((n) & 0xffff) << 14)
#घोषणा DWC3_TRB_CTRL_GET_SID_SOFN(n)	(((n) & (0xffff << 14)) >> 14)

#घोषणा DWC3_TRBCTL_TYPE(n)		((n) & (0x3f << 4))
#घोषणा DWC3_TRBCTL_NORMAL		DWC3_TRB_CTRL_TRBCTL(1)
#घोषणा DWC3_TRBCTL_CONTROL_SETUP	DWC3_TRB_CTRL_TRBCTL(2)
#घोषणा DWC3_TRBCTL_CONTROL_STATUS2	DWC3_TRB_CTRL_TRBCTL(3)
#घोषणा DWC3_TRBCTL_CONTROL_STATUS3	DWC3_TRB_CTRL_TRBCTL(4)
#घोषणा DWC3_TRBCTL_CONTROL_DATA	DWC3_TRB_CTRL_TRBCTL(5)
#घोषणा DWC3_TRBCTL_ISOCHRONOUS_FIRST	DWC3_TRB_CTRL_TRBCTL(6)
#घोषणा DWC3_TRBCTL_ISOCHRONOUS		DWC3_TRB_CTRL_TRBCTL(7)
#घोषणा DWC3_TRBCTL_LINK_TRB		DWC3_TRB_CTRL_TRBCTL(8)

/**
 * काष्ठा dwc3_trb - transfer request block (hw क्रमmat)
 * @bpl: DW0-3
 * @bph: DW4-7
 * @size: DW8-B
 * @ctrl: DWC-F
 */
काष्ठा dwc3_trb अणु
	u32		bpl;
	u32		bph;
	u32		size;
	u32		ctrl;
पूर्ण __packed;

/**
 * काष्ठा dwc3_hwparams - copy of HWPARAMS रेजिस्टरs
 * @hwparams0: GHWPARAMS0
 * @hwparams1: GHWPARAMS1
 * @hwparams2: GHWPARAMS2
 * @hwparams3: GHWPARAMS3
 * @hwparams4: GHWPARAMS4
 * @hwparams5: GHWPARAMS5
 * @hwparams6: GHWPARAMS6
 * @hwparams7: GHWPARAMS7
 * @hwparams8: GHWPARAMS8
 * @hwparams9: GHWPARAMS9
 */
काष्ठा dwc3_hwparams अणु
	u32	hwparams0;
	u32	hwparams1;
	u32	hwparams2;
	u32	hwparams3;
	u32	hwparams4;
	u32	hwparams5;
	u32	hwparams6;
	u32	hwparams7;
	u32	hwparams8;
	u32	hwparams9;
पूर्ण;

/* HWPARAMS0 */
#घोषणा DWC3_MODE(n)		((n) & 0x7)

/* HWPARAMS1 */
#घोषणा DWC3_NUM_INT(n)		(((n) & (0x3f << 15)) >> 15)

/* HWPARAMS3 */
#घोषणा DWC3_NUM_IN_EPS_MASK	(0x1f << 18)
#घोषणा DWC3_NUM_EPS_MASK	(0x3f << 12)
#घोषणा DWC3_NUM_EPS(p)		(((p)->hwparams3 &		\
			(DWC3_NUM_EPS_MASK)) >> 12)
#घोषणा DWC3_NUM_IN_EPS(p)	(((p)->hwparams3 &		\
			(DWC3_NUM_IN_EPS_MASK)) >> 18)

/* HWPARAMS7 */
#घोषणा DWC3_RAM1_DEPTH(n)	((n) & 0xffff)

/**
 * काष्ठा dwc3_request - representation of a transfer request
 * @request: काष्ठा usb_request to be transferred
 * @list: a list_head used क्रम request queueing
 * @dep: काष्ठा dwc3_ep owning this request
 * @sg: poपूर्णांकer to first incomplete sg
 * @start_sg: poपूर्णांकer to the sg which should be queued next
 * @num_pending_sgs: counter to pending sgs
 * @num_queued_sgs: counter to the number of sgs which alपढ़ोy got queued
 * @reमुख्यing: amount of data reमुख्यing
 * @status: पूर्णांकernal dwc3 request status tracking
 * @epnum: endpoपूर्णांक number to which this request refers
 * @trb: poपूर्णांकer to काष्ठा dwc3_trb
 * @trb_dma: DMA address of @trb
 * @num_trbs: number of TRBs used by this request
 * @needs_extra_trb: true when request needs one extra TRB (either due to ZLP
 *	or unaligned OUT)
 * @direction: IN or OUT direction flag
 * @mapped: true when request has been dma-mapped
 */
काष्ठा dwc3_request अणु
	काष्ठा usb_request	request;
	काष्ठा list_head	list;
	काष्ठा dwc3_ep		*dep;
	काष्ठा scatterlist	*sg;
	काष्ठा scatterlist	*start_sg;

	अचिन्हित पूर्णांक		num_pending_sgs;
	अचिन्हित पूर्णांक		num_queued_sgs;
	अचिन्हित पूर्णांक		reमुख्यing;

	अचिन्हित पूर्णांक		status;
#घोषणा DWC3_REQUEST_STATUS_QUEUED		0
#घोषणा DWC3_REQUEST_STATUS_STARTED		1
#घोषणा DWC3_REQUEST_STATUS_DISCONNECTED	2
#घोषणा DWC3_REQUEST_STATUS_DEQUEUED		3
#घोषणा DWC3_REQUEST_STATUS_STALLED		4
#घोषणा DWC3_REQUEST_STATUS_COMPLETED		5
#घोषणा DWC3_REQUEST_STATUS_UNKNOWN		-1

	u8			epnum;
	काष्ठा dwc3_trb		*trb;
	dma_addr_t		trb_dma;

	अचिन्हित पूर्णांक		num_trbs;

	अचिन्हित पूर्णांक		needs_extra_trb:1;
	अचिन्हित पूर्णांक		direction:1;
	अचिन्हित पूर्णांक		mapped:1;
पूर्ण;

/*
 * काष्ठा dwc3_scratchpad_array - hibernation scratchpad array
 * (क्रमmat defined by hw)
 */
काष्ठा dwc3_scratchpad_array अणु
	__le64	dma_adr[DWC3_MAX_HIBER_SCRATCHBUFS];
पूर्ण;

/**
 * काष्ठा dwc3 - representation of our controller
 * @drd_work: workqueue used क्रम role swapping
 * @ep0_trb: trb which is used क्रम the ctrl_req
 * @bounce: address of bounce buffer
 * @scratchbuf: address of scratch buffer
 * @setup_buf: used जबतक precessing STD USB requests
 * @ep0_trb_addr: dma address of @ep0_trb
 * @bounce_addr: dma address of @bounce
 * @ep0_usb_req: dummy req used जबतक handling STD USB requests
 * @scratch_addr: dma address of scratchbuf
 * @ep0_in_setup: one control transfer is completed and enter setup phase
 * @lock: क्रम synchronizing
 * @mutex: क्रम mode चयनing
 * @dev: poपूर्णांकer to our काष्ठा device
 * @sysdev: poपूर्णांकer to the DMA-capable device
 * @xhci: poपूर्णांकer to our xHCI child
 * @xhci_resources: काष्ठा resources क्रम our @xhci child
 * @ev_buf: काष्ठा dwc3_event_buffer poपूर्णांकer
 * @eps: endpoपूर्णांक array
 * @gadget: device side representation of the peripheral controller
 * @gadget_driver: poपूर्णांकer to the gadget driver
 * @clks: array of घड़ीs
 * @num_clks: number of घड़ीs
 * @reset: reset control
 * @regs: base address क्रम our रेजिस्टरs
 * @regs_size: address space size
 * @fladj: frame length adjusपंचांगent
 * @irq_gadget: peripheral controller's IRQ number
 * @otg_irq: IRQ number क्रम OTG IRQs
 * @current_otg_role: current role of operation जबतक using the OTG block
 * @desired_otg_role: desired role of operation जबतक using the OTG block
 * @otg_restart_host: flag that OTG controller needs to restart host
 * @nr_scratch: number of scratch buffers
 * @u1u2: only used on revisions <1.83a क्रम workaround
 * @maximum_speed: maximum speed requested (मुख्यly क्रम testing purposes)
 * @max_ssp_rate: SuperSpeed Plus maximum संकेतing rate and lane count
 * @gadget_max_speed: maximum gadget speed requested
 * @gadget_ssp_rate: Gadget driver's maximum supported SuperSpeed Plus संकेतing
 *			rate and lane count.
 * @ip: controller's ID
 * @revision: controller's version of an IP
 * @version_type: VERSIONTYPE रेजिस्टर contents, a sub release of a revision
 * @dr_mode: requested mode of operation
 * @current_dr_role: current role of operation when in dual-role mode
 * @desired_dr_role: desired role of operation when in dual-role mode
 * @edev: extcon handle
 * @edev_nb: extcon notअगरier
 * @hsphy_mode: UTMI phy mode, one of following:
 *		- USBPHY_INTERFACE_MODE_UTMI
 *		- USBPHY_INTERFACE_MODE_UTMIW
 * @role_sw: usb_role_चयन handle
 * @role_चयन_शेष_mode: शेष operation mode of controller जबतक
 *			usb role is USB_ROLE_NONE.
 * @usb_psy: poपूर्णांकer to घातer supply पूर्णांकerface.
 * @usb2_phy: poपूर्णांकer to USB2 PHY
 * @usb3_phy: poपूर्णांकer to USB3 PHY
 * @usb2_generic_phy: poपूर्णांकer to USB2 PHY
 * @usb3_generic_phy: poपूर्णांकer to USB3 PHY
 * @phys_पढ़ोy: flag to indicate that PHYs are पढ़ोy
 * @ulpi: poपूर्णांकer to ulpi पूर्णांकerface
 * @ulpi_पढ़ोy: flag to indicate that ULPI is initialized
 * @u2sel: parameter from Set SEL request.
 * @u2pel: parameter from Set SEL request.
 * @u1sel: parameter from Set SEL request.
 * @u1pel: parameter from Set SEL request.
 * @num_eps: number of endpoपूर्णांकs
 * @ep0_next_event: hold the next expected event
 * @ep0state: state of endpoपूर्णांक zero
 * @link_state: link state
 * @speed: device speed (super, high, full, low)
 * @hwparams: copy of hwparams रेजिस्टरs
 * @root: debugfs root folder poपूर्णांकer
 * @regset: debugfs poपूर्णांकer to regdump file
 * @dbg_lsp_select: current debug lsp mux रेजिस्टर selection
 * @test_mode: true when we're entering a USB test mode
 * @test_mode_nr: test feature selector
 * @lpm_nyet_threshold: LPM NYET response threshold
 * @hird_threshold: HIRD threshold
 * @rx_thr_num_pkt_prd: periodic ESS receive packet count
 * @rx_max_burst_prd: max periodic ESS receive burst size
 * @tx_thr_num_pkt_prd: periodic ESS transmit packet count
 * @tx_max_burst_prd: max periodic ESS transmit burst size
 * @hsphy_पूर्णांकerface: "utmi" or "ulpi"
 * @connected: true when we're connected to a host, false otherwise
 * @delayed_status: true when gadget driver asks क्रम delayed status
 * @ep0_bounced: true when we used bounce buffer
 * @ep0_expect_in: true when we expect a DATA IN transfer
 * @has_hibernation: true when dwc3 was configured with Hibernation
 * @sysdev_is_parent: true when dwc3 device has a parent driver
 * @has_lpm_erratum: true when core was configured with LPM Erratum. Note that
 *			there's now way क्रम software to detect this in runसमय.
 * @is_uपंचांगi_l1_suspend: the core निश्चितs output संकेत
 *	0	- uपंचांगi_sleep_n
 *	1	- uपंचांगi_l1_suspend_n
 * @is_fpga: true when we are using the FPGA board
 * @pending_events: true when we have pending IRQs to be handled
 * @pullups_connected: true when Run/Stop bit is set
 * @setup_packet_pending: true when there's a Setup Packet in FIFO. Workaround
 * @three_stage_setup: set अगर we perक्रमm a three phase setup
 * @dis_start_transfer_quirk: set अगर start_transfer failure SW workaround is
 *			not needed क्रम DWC_usb31 version 1.70a-ea06 and below
 * @usb3_lpm_capable: set अगर hadrware supports Link Power Management
 * @usb2_lpm_disable: set to disable usb2 lpm क्रम host
 * @usb2_gadget_lpm_disable: set to disable usb2 lpm क्रम gadget
 * @disable_scramble_quirk: set अगर we enable the disable scramble quirk
 * @u2निकास_lfps_quirk: set अगर we enable u2निकास lfps quirk
 * @u2ss_inp3_quirk: set अगर we enable P3 OK क्रम U2/SS Inactive quirk
 * @req_p1p2p3_quirk: set अगर we enable request p1p2p3 quirk
 * @del_p1p2p3_quirk: set अगर we enable delay p1p2p3 quirk
 * @del_phy_घातer_chg_quirk: set अगर we enable delay phy घातer change quirk
 * @lfps_filter_quirk: set अगर we enable LFPS filter quirk
 * @rx_detect_poll_quirk: set अगर we enable rx_detect to polling lfps quirk
 * @dis_u3_susphy_quirk: set अगर we disable usb3 suspend phy
 * @dis_u2_susphy_quirk: set अगर we disable usb2 suspend phy
 * @dis_enblslpm_quirk: set अगर we clear enblslpm in GUSB2PHYCFG,
 *                      disabling the suspend संकेत to the PHY.
 * @dis_u1_entry_quirk: set अगर link entering पूर्णांकo U1 state needs to be disabled.
 * @dis_u2_entry_quirk: set अगर link entering पूर्णांकo U2 state needs to be disabled.
 * @dis_rxdet_inp3_quirk: set अगर we disable Rx.Detect in P3
 * @dis_u2_मुक्तclk_exists_quirk : set अगर we clear u2_मुक्तclk_exists
 *			in GUSB2PHYCFG, specअगरy that USB2 PHY करोesn't
 *			provide a मुक्त-running PHY घड़ी.
 * @dis_del_phy_घातer_chg_quirk: set अगर we disable delay phy घातer
 *			change quirk.
 * @dis_tx_ipgap_linecheck_quirk: set अगर we disable u2mac linestate
 *			check during HS transmit.
 * @parkmode_disable_ss_quirk: set अगर we need to disable all SuperSpeed
 *			instances in park mode.
 * @tx_de_emphasis_quirk: set अगर we enable Tx de-emphasis quirk
 * @tx_de_emphasis: Tx de-emphasis value
 *	0	- -6dB de-emphasis
 *	1	- -3.5dB de-emphasis
 *	2	- No de-emphasis
 *	3	- Reserved
 * @dis_metastability_quirk: set to disable metastability quirk.
 * @dis_split_quirk: set to disable split boundary.
 * @imod_पूर्णांकerval: set the पूर्णांकerrupt moderation पूर्णांकerval in 250ns
 *			increments or 0 to disable.
 */
काष्ठा dwc3 अणु
	काष्ठा work_काष्ठा	drd_work;
	काष्ठा dwc3_trb		*ep0_trb;
	व्योम			*bounce;
	व्योम			*scratchbuf;
	u8			*setup_buf;
	dma_addr_t		ep0_trb_addr;
	dma_addr_t		bounce_addr;
	dma_addr_t		scratch_addr;
	काष्ठा dwc3_request	ep0_usb_req;
	काष्ठा completion	ep0_in_setup;

	/* device lock */
	spinlock_t		lock;

	/* mode चयनing lock */
	काष्ठा mutex		mutex;

	काष्ठा device		*dev;
	काष्ठा device		*sysdev;

	काष्ठा platक्रमm_device	*xhci;
	काष्ठा resource		xhci_resources[DWC3_XHCI_RESOURCES_NUM];

	काष्ठा dwc3_event_buffer *ev_buf;
	काष्ठा dwc3_ep		*eps[DWC3_ENDPOINTS_NUM];

	काष्ठा usb_gadget	*gadget;
	काष्ठा usb_gadget_driver *gadget_driver;

	काष्ठा clk_bulk_data	*clks;
	पूर्णांक			num_clks;

	काष्ठा reset_control	*reset;

	काष्ठा usb_phy		*usb2_phy;
	काष्ठा usb_phy		*usb3_phy;

	काष्ठा phy		*usb2_generic_phy;
	काष्ठा phy		*usb3_generic_phy;

	bool			phys_पढ़ोy;

	काष्ठा ulpi		*ulpi;
	bool			ulpi_पढ़ोy;

	व्योम __iomem		*regs;
	माप_प्रकार			regs_size;

	क्रमागत usb_dr_mode	dr_mode;
	u32			current_dr_role;
	u32			desired_dr_role;
	काष्ठा extcon_dev	*edev;
	काष्ठा notअगरier_block	edev_nb;
	क्रमागत usb_phy_पूर्णांकerface	hsphy_mode;
	काष्ठा usb_role_चयन	*role_sw;
	क्रमागत usb_dr_mode	role_चयन_शेष_mode;

	काष्ठा घातer_supply	*usb_psy;

	u32			fladj;
	u32			irq_gadget;
	u32			otg_irq;
	u32			current_otg_role;
	u32			desired_otg_role;
	bool			otg_restart_host;
	u32			nr_scratch;
	u32			u1u2;
	u32			maximum_speed;
	u32			gadget_max_speed;
	क्रमागत usb_ssp_rate	max_ssp_rate;
	क्रमागत usb_ssp_rate	gadget_ssp_rate;

	u32			ip;

#घोषणा DWC3_IP			0x5533
#घोषणा DWC31_IP		0x3331
#घोषणा DWC32_IP		0x3332

	u32			revision;

#घोषणा DWC3_REVISION_ANY	0x0
#घोषणा DWC3_REVISION_173A	0x5533173a
#घोषणा DWC3_REVISION_175A	0x5533175a
#घोषणा DWC3_REVISION_180A	0x5533180a
#घोषणा DWC3_REVISION_183A	0x5533183a
#घोषणा DWC3_REVISION_185A	0x5533185a
#घोषणा DWC3_REVISION_187A	0x5533187a
#घोषणा DWC3_REVISION_188A	0x5533188a
#घोषणा DWC3_REVISION_190A	0x5533190a
#घोषणा DWC3_REVISION_194A	0x5533194a
#घोषणा DWC3_REVISION_200A	0x5533200a
#घोषणा DWC3_REVISION_202A	0x5533202a
#घोषणा DWC3_REVISION_210A	0x5533210a
#घोषणा DWC3_REVISION_220A	0x5533220a
#घोषणा DWC3_REVISION_230A	0x5533230a
#घोषणा DWC3_REVISION_240A	0x5533240a
#घोषणा DWC3_REVISION_250A	0x5533250a
#घोषणा DWC3_REVISION_260A	0x5533260a
#घोषणा DWC3_REVISION_270A	0x5533270a
#घोषणा DWC3_REVISION_280A	0x5533280a
#घोषणा DWC3_REVISION_290A	0x5533290a
#घोषणा DWC3_REVISION_300A	0x5533300a
#घोषणा DWC3_REVISION_310A	0x5533310a
#घोषणा DWC3_REVISION_330A	0x5533330a

#घोषणा DWC31_REVISION_ANY	0x0
#घोषणा DWC31_REVISION_110A	0x3131302a
#घोषणा DWC31_REVISION_120A	0x3132302a
#घोषणा DWC31_REVISION_160A	0x3136302a
#घोषणा DWC31_REVISION_170A	0x3137302a
#घोषणा DWC31_REVISION_180A	0x3138302a
#घोषणा DWC31_REVISION_190A	0x3139302a

#घोषणा DWC32_REVISION_ANY	0x0
#घोषणा DWC32_REVISION_100A	0x3130302a

	u32			version_type;

#घोषणा DWC31_VERSIONTYPE_ANY		0x0
#घोषणा DWC31_VERSIONTYPE_EA01		0x65613031
#घोषणा DWC31_VERSIONTYPE_EA02		0x65613032
#घोषणा DWC31_VERSIONTYPE_EA03		0x65613033
#घोषणा DWC31_VERSIONTYPE_EA04		0x65613034
#घोषणा DWC31_VERSIONTYPE_EA05		0x65613035
#घोषणा DWC31_VERSIONTYPE_EA06		0x65613036

	क्रमागत dwc3_ep0_next	ep0_next_event;
	क्रमागत dwc3_ep0_state	ep0state;
	क्रमागत dwc3_link_state	link_state;

	u16			u2sel;
	u16			u2pel;
	u8			u1sel;
	u8			u1pel;

	u8			speed;

	u8			num_eps;

	काष्ठा dwc3_hwparams	hwparams;
	काष्ठा dentry		*root;
	काष्ठा debugfs_regset32	*regset;

	u32			dbg_lsp_select;

	u8			test_mode;
	u8			test_mode_nr;
	u8			lpm_nyet_threshold;
	u8			hird_threshold;
	u8			rx_thr_num_pkt_prd;
	u8			rx_max_burst_prd;
	u8			tx_thr_num_pkt_prd;
	u8			tx_max_burst_prd;

	स्थिर अक्षर		*hsphy_पूर्णांकerface;

	अचिन्हित		connected:1;
	अचिन्हित		delayed_status:1;
	अचिन्हित		ep0_bounced:1;
	अचिन्हित		ep0_expect_in:1;
	अचिन्हित		has_hibernation:1;
	अचिन्हित		sysdev_is_parent:1;
	अचिन्हित		has_lpm_erratum:1;
	अचिन्हित		is_uपंचांगi_l1_suspend:1;
	अचिन्हित		is_fpga:1;
	अचिन्हित		pending_events:1;
	अचिन्हित		pullups_connected:1;
	अचिन्हित		setup_packet_pending:1;
	अचिन्हित		three_stage_setup:1;
	अचिन्हित		dis_start_transfer_quirk:1;
	अचिन्हित		usb3_lpm_capable:1;
	अचिन्हित		usb2_lpm_disable:1;
	अचिन्हित		usb2_gadget_lpm_disable:1;

	अचिन्हित		disable_scramble_quirk:1;
	अचिन्हित		u2निकास_lfps_quirk:1;
	अचिन्हित		u2ss_inp3_quirk:1;
	अचिन्हित		req_p1p2p3_quirk:1;
	अचिन्हित                del_p1p2p3_quirk:1;
	अचिन्हित		del_phy_घातer_chg_quirk:1;
	अचिन्हित		lfps_filter_quirk:1;
	अचिन्हित		rx_detect_poll_quirk:1;
	अचिन्हित		dis_u3_susphy_quirk:1;
	अचिन्हित		dis_u2_susphy_quirk:1;
	अचिन्हित		dis_enblslpm_quirk:1;
	अचिन्हित		dis_u1_entry_quirk:1;
	अचिन्हित		dis_u2_entry_quirk:1;
	अचिन्हित		dis_rxdet_inp3_quirk:1;
	अचिन्हित		dis_u2_मुक्तclk_exists_quirk:1;
	अचिन्हित		dis_del_phy_घातer_chg_quirk:1;
	अचिन्हित		dis_tx_ipgap_linecheck_quirk:1;
	अचिन्हित		parkmode_disable_ss_quirk:1;

	अचिन्हित		tx_de_emphasis_quirk:1;
	अचिन्हित		tx_de_emphasis:2;

	अचिन्हित		dis_metastability_quirk:1;

	अचिन्हित		dis_split_quirk:1;

	u16			imod_पूर्णांकerval;
पूर्ण;

#घोषणा INCRX_BURST_MODE 0
#घोषणा INCRX_UNDEF_LENGTH_BURST_MODE 1

#घोषणा work_to_dwc(w)		(container_of((w), काष्ठा dwc3, drd_work))

/* -------------------------------------------------------------------------- */

काष्ठा dwc3_event_type अणु
	u32	is_devspec:1;
	u32	type:7;
	u32	reserved8_31:24;
पूर्ण __packed;

#घोषणा DWC3_DEPEVT_XFERCOMPLETE	0x01
#घोषणा DWC3_DEPEVT_XFERINPROGRESS	0x02
#घोषणा DWC3_DEPEVT_XFERNOTREADY	0x03
#घोषणा DWC3_DEPEVT_RXTXFIFOEVT		0x04
#घोषणा DWC3_DEPEVT_STREAMEVT		0x06
#घोषणा DWC3_DEPEVT_EPCMDCMPLT		0x07

/**
 * काष्ठा dwc3_event_depevt - Device Endpoपूर्णांक Events
 * @one_bit: indicates this is an endpoपूर्णांक event (not used)
 * @endpoपूर्णांक_number: number of the endpoपूर्णांक
 * @endpoपूर्णांक_event: The event we have:
 *	0x00	- Reserved
 *	0x01	- XferComplete
 *	0x02	- XferInProgress
 *	0x03	- XferNotReady
 *	0x04	- RxTxFअगरoEvt (IN->Underrun, OUT->Overrun)
 *	0x05	- Reserved
 *	0x06	- StreamEvt
 *	0x07	- EPCmdCmplt
 * @reserved11_10: Reserved, करोn't use.
 * @status: Indicates the status of the event. Refer to databook क्रम
 *	more inक्रमmation.
 * @parameters: Parameters of the current event. Refer to databook क्रम
 *	more inक्रमmation.
 */
काष्ठा dwc3_event_depevt अणु
	u32	one_bit:1;
	u32	endpoपूर्णांक_number:5;
	u32	endpoपूर्णांक_event:4;
	u32	reserved11_10:2;
	u32	status:4;

/* Within XferNotReady */
#घोषणा DEPEVT_STATUS_TRANSFER_ACTIVE	BIT(3)

/* Within XferComplete or XferInProgress */
#घोषणा DEPEVT_STATUS_BUSERR	BIT(0)
#घोषणा DEPEVT_STATUS_SHORT	BIT(1)
#घोषणा DEPEVT_STATUS_IOC	BIT(2)
#घोषणा DEPEVT_STATUS_LST	BIT(3) /* XferComplete */
#घोषणा DEPEVT_STATUS_MISSED_ISOC BIT(3) /* XferInProgress */

/* Stream event only */
#घोषणा DEPEVT_STREAMEVT_FOUND		1
#घोषणा DEPEVT_STREAMEVT_NOTFOUND	2

/* Stream event parameter */
#घोषणा DEPEVT_STREAM_PRIME		0xfffe
#घोषणा DEPEVT_STREAM_NOSTREAM		0x0

/* Control-only Status */
#घोषणा DEPEVT_STATUS_CONTROL_DATA	1
#घोषणा DEPEVT_STATUS_CONTROL_STATUS	2
#घोषणा DEPEVT_STATUS_CONTROL_PHASE(n)	((n) & 3)

/* In response to Start Transfer */
#घोषणा DEPEVT_TRANSFER_NO_RESOURCE	1
#घोषणा DEPEVT_TRANSFER_BUS_EXPIRY	2

	u32	parameters:16;

/* For Command Complete Events */
#घोषणा DEPEVT_PARAMETER_CMD(n)	(((n) & (0xf << 8)) >> 8)
पूर्ण __packed;

/**
 * काष्ठा dwc3_event_devt - Device Events
 * @one_bit: indicates this is a non-endpoपूर्णांक event (not used)
 * @device_event: indicates it's a device event. Should पढ़ो as 0x00
 * @type: indicates the type of device event.
 *	0	- DisconnEvt
 *	1	- USBRst
 *	2	- ConnectDone
 *	3	- ULStChng
 *	4	- WkUpEvt
 *	5	- Reserved
 *	6	- Suspend (EOPF on revisions 2.10a and prior)
 *	7	- SOF
 *	8	- Reserved
 *	9	- ErrticErr
 *	10	- CmdCmplt
 *	11	- EvntOverflow
 *	12	- VndrDevTstRcved
 * @reserved15_12: Reserved, not used
 * @event_info: Inक्रमmation about this event
 * @reserved31_25: Reserved, not used
 */
काष्ठा dwc3_event_devt अणु
	u32	one_bit:1;
	u32	device_event:7;
	u32	type:4;
	u32	reserved15_12:4;
	u32	event_info:9;
	u32	reserved31_25:7;
पूर्ण __packed;

/**
 * काष्ठा dwc3_event_gevt - Other Core Events
 * @one_bit: indicates this is a non-endpoपूर्णांक event (not used)
 * @device_event: indicates it's (0x03) Carkit or (0x04) I2C event.
 * @phy_port_number: self-explanatory
 * @reserved31_12: Reserved, not used.
 */
काष्ठा dwc3_event_gevt अणु
	u32	one_bit:1;
	u32	device_event:7;
	u32	phy_port_number:4;
	u32	reserved31_12:20;
पूर्ण __packed;

/**
 * जोड़ dwc3_event - representation of Event Buffer contents
 * @raw: raw 32-bit event
 * @type: the type of the event
 * @depevt: Device Endpoपूर्णांक Event
 * @devt: Device Event
 * @gevt: Global Event
 */
जोड़ dwc3_event अणु
	u32				raw;
	काष्ठा dwc3_event_type		type;
	काष्ठा dwc3_event_depevt	depevt;
	काष्ठा dwc3_event_devt		devt;
	काष्ठा dwc3_event_gevt		gevt;
पूर्ण;

/**
 * काष्ठा dwc3_gadget_ep_cmd_params - representation of endpoपूर्णांक command
 * parameters
 * @param2: third parameter
 * @param1: second parameter
 * @param0: first parameter
 */
काष्ठा dwc3_gadget_ep_cmd_params अणु
	u32	param2;
	u32	param1;
	u32	param0;
पूर्ण;

/*
 * DWC3 Features to be used as Driver Data
 */

#घोषणा DWC3_HAS_PERIPHERAL		BIT(0)
#घोषणा DWC3_HAS_XHCI			BIT(1)
#घोषणा DWC3_HAS_OTG			BIT(3)

/* prototypes */
व्योम dwc3_set_prtcap(काष्ठा dwc3 *dwc, u32 mode);
व्योम dwc3_set_mode(काष्ठा dwc3 *dwc, u32 mode);
u32 dwc3_core_fअगरo_space(काष्ठा dwc3_ep *dep, u8 type);

#घोषणा DWC3_IP_IS(_ip)							\
	(dwc->ip == _ip##_IP)

#घोषणा DWC3_VER_IS(_ip, _ver)						\
	(DWC3_IP_IS(_ip) && dwc->revision == _ip##_REVISION_##_ver)

#घोषणा DWC3_VER_IS_PRIOR(_ip, _ver)					\
	(DWC3_IP_IS(_ip) && dwc->revision < _ip##_REVISION_##_ver)

#घोषणा DWC3_VER_IS_WITHIN(_ip, _from, _to)				\
	(DWC3_IP_IS(_ip) &&						\
	 dwc->revision >= _ip##_REVISION_##_from &&			\
	 (!(_ip##_REVISION_##_to) ||					\
	  dwc->revision <= _ip##_REVISION_##_to))

#घोषणा DWC3_VER_TYPE_IS_WITHIN(_ip, _ver, _from, _to)			\
	(DWC3_VER_IS(_ip, _ver) &&					\
	 dwc->version_type >= _ip##_VERSIONTYPE_##_from &&		\
	 (!(_ip##_VERSIONTYPE_##_to) ||					\
	  dwc->version_type <= _ip##_VERSIONTYPE_##_to))

/**
 * dwc3_mdwidth - get MDWIDTH value in bits
 * @dwc: poपूर्णांकer to our context काष्ठाure
 *
 * Return MDWIDTH configuration value in bits.
 */
अटल अंतरभूत u32 dwc3_mdwidth(काष्ठा dwc3 *dwc)
अणु
	u32 mdwidth;

	mdwidth = DWC3_GHWPARAMS0_MDWIDTH(dwc->hwparams.hwparams0);
	अगर (DWC3_IP_IS(DWC32))
		mdwidth += DWC3_GHWPARAMS6_MDWIDTH(dwc->hwparams.hwparams6);

	वापस mdwidth;
पूर्ण

bool dwc3_has_imod(काष्ठा dwc3 *dwc);

पूर्णांक dwc3_event_buffers_setup(काष्ठा dwc3 *dwc);
व्योम dwc3_event_buffers_cleanup(काष्ठा dwc3 *dwc);

#अगर IS_ENABLED(CONFIG_USB_DWC3_HOST) || IS_ENABLED(CONFIG_USB_DWC3_DUAL_ROLE)
पूर्णांक dwc3_host_init(काष्ठा dwc3 *dwc);
व्योम dwc3_host_निकास(काष्ठा dwc3 *dwc);
#अन्यथा
अटल अंतरभूत पूर्णांक dwc3_host_init(काष्ठा dwc3 *dwc)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc3_host_निकास(काष्ठा dwc3 *dwc)
अणु पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_DWC3_GADGET) || IS_ENABLED(CONFIG_USB_DWC3_DUAL_ROLE)
पूर्णांक dwc3_gadget_init(काष्ठा dwc3 *dwc);
व्योम dwc3_gadget_निकास(काष्ठा dwc3 *dwc);
पूर्णांक dwc3_gadget_set_test_mode(काष्ठा dwc3 *dwc, पूर्णांक mode);
पूर्णांक dwc3_gadget_get_link_state(काष्ठा dwc3 *dwc);
पूर्णांक dwc3_gadget_set_link_state(काष्ठा dwc3 *dwc, क्रमागत dwc3_link_state state);
पूर्णांक dwc3_send_gadget_ep_cmd(काष्ठा dwc3_ep *dep, अचिन्हित पूर्णांक cmd,
		काष्ठा dwc3_gadget_ep_cmd_params *params);
पूर्णांक dwc3_send_gadget_generic_command(काष्ठा dwc3 *dwc, अचिन्हित पूर्णांक cmd,
		u32 param);
#अन्यथा
अटल अंतरभूत पूर्णांक dwc3_gadget_init(काष्ठा dwc3 *dwc)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc3_gadget_निकास(काष्ठा dwc3 *dwc)
अणु पूर्ण
अटल अंतरभूत पूर्णांक dwc3_gadget_set_test_mode(काष्ठा dwc3 *dwc, पूर्णांक mode)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc3_gadget_get_link_state(काष्ठा dwc3 *dwc)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc3_gadget_set_link_state(काष्ठा dwc3 *dwc,
		क्रमागत dwc3_link_state state)
अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक dwc3_send_gadget_ep_cmd(काष्ठा dwc3_ep *dep, अचिन्हित पूर्णांक cmd,
		काष्ठा dwc3_gadget_ep_cmd_params *params)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc3_send_gadget_generic_command(काष्ठा dwc3 *dwc,
		पूर्णांक cmd, u32 param)
अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_DWC3_DUAL_ROLE)
पूर्णांक dwc3_drd_init(काष्ठा dwc3 *dwc);
व्योम dwc3_drd_निकास(काष्ठा dwc3 *dwc);
व्योम dwc3_otg_init(काष्ठा dwc3 *dwc);
व्योम dwc3_otg_निकास(काष्ठा dwc3 *dwc);
व्योम dwc3_otg_update(काष्ठा dwc3 *dwc, bool ignore_idstatus);
व्योम dwc3_otg_host_init(काष्ठा dwc3 *dwc);
#अन्यथा
अटल अंतरभूत पूर्णांक dwc3_drd_init(काष्ठा dwc3 *dwc)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc3_drd_निकास(काष्ठा dwc3 *dwc)
अणु पूर्ण
अटल अंतरभूत व्योम dwc3_otg_init(काष्ठा dwc3 *dwc)
अणु पूर्ण
अटल अंतरभूत व्योम dwc3_otg_निकास(काष्ठा dwc3 *dwc)
अणु पूर्ण
अटल अंतरभूत व्योम dwc3_otg_update(काष्ठा dwc3 *dwc, bool ignore_idstatus)
अणु पूर्ण
अटल अंतरभूत व्योम dwc3_otg_host_init(काष्ठा dwc3 *dwc)
अणु पूर्ण
#पूर्ण_अगर

/* घातer management पूर्णांकerface */
#अगर !IS_ENABLED(CONFIG_USB_DWC3_HOST)
पूर्णांक dwc3_gadget_suspend(काष्ठा dwc3 *dwc);
पूर्णांक dwc3_gadget_resume(काष्ठा dwc3 *dwc);
व्योम dwc3_gadget_process_pending_events(काष्ठा dwc3 *dwc);
#अन्यथा
अटल अंतरभूत पूर्णांक dwc3_gadget_suspend(काष्ठा dwc3 *dwc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dwc3_gadget_resume(काष्ठा dwc3 *dwc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dwc3_gadget_process_pending_events(काष्ठा dwc3 *dwc)
अणु
पूर्ण
#पूर्ण_अगर /* !IS_ENABLED(CONFIG_USB_DWC3_HOST) */

#अगर IS_ENABLED(CONFIG_USB_DWC3_ULPI)
पूर्णांक dwc3_ulpi_init(काष्ठा dwc3 *dwc);
व्योम dwc3_ulpi_निकास(काष्ठा dwc3 *dwc);
#अन्यथा
अटल अंतरभूत पूर्णांक dwc3_ulpi_init(काष्ठा dwc3 *dwc)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc3_ulpi_निकास(काष्ठा dwc3 *dwc)
अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __DRIVERS_USB_DWC3_CORE_H */

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * amd5536.h -- header क्रम AMD 5536 UDC high/full speed USB device controller
 *
 * Copyright (C) 2007 AMD (https://www.amd.com)
 * Author: Thomas Dahlmann
 */

#अगर_अघोषित AMD5536UDC_H
#घोषणा AMD5536UDC_H

/* debug control */
/* #घोषणा UDC_VERBOSE */

#समावेश <linux/extcon.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

/* various स्थिरants */
#घोषणा UDC_RDE_TIMER_SECONDS		1
#घोषणा UDC_RDE_TIMER_DIV		10
#घोषणा UDC_POLLSTALL_TIMER_USECONDS	500

/* Hs AMD5536 chip rev. */
#घोषणा UDC_HSA0_REV 1
#घोषणा UDC_HSB1_REV 2

/* Broadcom chip rev. */
#घोषणा UDC_BCM_REV 10

/*
 * SETUP usb commands
 * needed, because some SETUP's are handled in hw, but must be passed to
 * gadget driver above
 * SET_CONFIG
 */
#घोषणा UDC_SETCONFIG_DWORD0			0x00000900
#घोषणा UDC_SETCONFIG_DWORD0_VALUE_MASK		0xffff0000
#घोषणा UDC_SETCONFIG_DWORD0_VALUE_OFS		16

#घोषणा UDC_SETCONFIG_DWORD1			0x00000000

/* SET_INTERFACE */
#घोषणा UDC_SETINTF_DWORD0			0x00000b00
#घोषणा UDC_SETINTF_DWORD0_ALT_MASK		0xffff0000
#घोषणा UDC_SETINTF_DWORD0_ALT_OFS		16

#घोषणा UDC_SETINTF_DWORD1			0x00000000
#घोषणा UDC_SETINTF_DWORD1_INTF_MASK		0x0000ffff
#घोषणा UDC_SETINTF_DWORD1_INTF_OFS		0

/* Mass storage reset */
#घोषणा UDC_MSCRES_DWORD0			0x0000ff21
#घोषणा UDC_MSCRES_DWORD1			0x00000000

/* Global CSR's -------------------------------------------------------------*/
#घोषणा UDC_CSR_ADDR				0x500

/* EP NE bits */
/* EP number */
#घोषणा UDC_CSR_NE_NUM_MASK			0x0000000f
#घोषणा UDC_CSR_NE_NUM_OFS			0
/* EP direction */
#घोषणा UDC_CSR_NE_सूची_MASK			0x00000010
#घोषणा UDC_CSR_NE_सूची_OFS			4
/* EP type */
#घोषणा UDC_CSR_NE_TYPE_MASK			0x00000060
#घोषणा UDC_CSR_NE_TYPE_OFS			5
/* EP config number */
#घोषणा UDC_CSR_NE_CFG_MASK			0x00000780
#घोषणा UDC_CSR_NE_CFG_OFS			7
/* EP पूर्णांकerface number */
#घोषणा UDC_CSR_NE_INTF_MASK			0x00007800
#घोषणा UDC_CSR_NE_INTF_OFS			11
/* EP alt setting */
#घोषणा UDC_CSR_NE_ALT_MASK			0x00078000
#घोषणा UDC_CSR_NE_ALT_OFS			15

/* max pkt */
#घोषणा UDC_CSR_NE_MAX_PKT_MASK			0x3ff80000
#घोषणा UDC_CSR_NE_MAX_PKT_OFS			19

/* Device Config Register ---------------------------------------------------*/
#घोषणा UDC_DEVCFG_ADDR				0x400

#घोषणा UDC_DEVCFG_SOFTRESET			31
#घोषणा UDC_DEVCFG_HNPSFEN			30
#घोषणा UDC_DEVCFG_DMARST			29
#घोषणा UDC_DEVCFG_SET_DESC			18
#घोषणा UDC_DEVCFG_CSR_PRG			17
#घोषणा UDC_DEVCFG_STATUS			7
#घोषणा UDC_DEVCFG_सूची				6
#घोषणा UDC_DEVCFG_PI				5
#घोषणा UDC_DEVCFG_SS				4
#घोषणा UDC_DEVCFG_SP				3
#घोषणा UDC_DEVCFG_RWKP				2

#घोषणा UDC_DEVCFG_SPD_MASK			0x3
#घोषणा UDC_DEVCFG_SPD_OFS			0
#घोषणा UDC_DEVCFG_SPD_HS			0x0
#घोषणा UDC_DEVCFG_SPD_FS			0x1
#घोषणा UDC_DEVCFG_SPD_LS			0x2
/*#घोषणा UDC_DEVCFG_SPD_FS			0x3*/


/* Device Control Register --------------------------------------------------*/
#घोषणा UDC_DEVCTL_ADDR				0x404

#घोषणा UDC_DEVCTL_THLEN_MASK			0xff000000
#घोषणा UDC_DEVCTL_THLEN_OFS			24

#घोषणा UDC_DEVCTL_BRLEN_MASK			0x00ff0000
#घोषणा UDC_DEVCTL_BRLEN_OFS			16

#घोषणा UDC_DEVCTL_SRX_FLUSH			14
#घोषणा UDC_DEVCTL_CSR_DONE			13
#घोषणा UDC_DEVCTL_DEVNAK			12
#घोषणा UDC_DEVCTL_SD				10
#घोषणा UDC_DEVCTL_MODE				9
#घोषणा UDC_DEVCTL_BREN				8
#घोषणा UDC_DEVCTL_THE				7
#घोषणा UDC_DEVCTL_BF				6
#घोषणा UDC_DEVCTL_BE				5
#घोषणा UDC_DEVCTL_DU				4
#घोषणा UDC_DEVCTL_TDE				3
#घोषणा UDC_DEVCTL_RDE				2
#घोषणा UDC_DEVCTL_RES				0


/* Device Status Register ---------------------------------------------------*/
#घोषणा UDC_DEVSTS_ADDR				0x408

#घोषणा UDC_DEVSTS_TS_MASK			0xfffc0000
#घोषणा UDC_DEVSTS_TS_OFS			18

#घोषणा UDC_DEVSTS_SESSVLD			17
#घोषणा UDC_DEVSTS_PHY_ERROR			16
#घोषणा UDC_DEVSTS_RXFIFO_EMPTY			15

#घोषणा UDC_DEVSTS_ENUM_SPEED_MASK		0x00006000
#घोषणा UDC_DEVSTS_ENUM_SPEED_OFS		13
#घोषणा UDC_DEVSTS_ENUM_SPEED_FULL		1
#घोषणा UDC_DEVSTS_ENUM_SPEED_HIGH		0

#घोषणा UDC_DEVSTS_SUSP				12

#घोषणा UDC_DEVSTS_ALT_MASK			0x00000f00
#घोषणा UDC_DEVSTS_ALT_OFS			8

#घोषणा UDC_DEVSTS_INTF_MASK			0x000000f0
#घोषणा UDC_DEVSTS_INTF_OFS			4

#घोषणा UDC_DEVSTS_CFG_MASK			0x0000000f
#घोषणा UDC_DEVSTS_CFG_OFS			0


/* Device Interrupt Register ------------------------------------------------*/
#घोषणा UDC_DEVINT_ADDR				0x40c

#घोषणा UDC_DEVINT_SVC				7
#घोषणा UDC_DEVINT_ENUM				6
#घोषणा UDC_DEVINT_SOF				5
#घोषणा UDC_DEVINT_US				4
#घोषणा UDC_DEVINT_UR				3
#घोषणा UDC_DEVINT_ES				2
#घोषणा UDC_DEVINT_SI				1
#घोषणा UDC_DEVINT_SC				0

/* Device Interrupt Mask Register -------------------------------------------*/
#घोषणा UDC_DEVINT_MSK_ADDR			0x410

#घोषणा UDC_DEVINT_MSK				0x7f

/* Endpoपूर्णांक Interrupt Register ----------------------------------------------*/
#घोषणा UDC_EPINT_ADDR				0x414

#घोषणा UDC_EPINT_OUT_MASK			0xffff0000
#घोषणा UDC_EPINT_OUT_OFS			16
#घोषणा UDC_EPINT_IN_MASK			0x0000ffff
#घोषणा UDC_EPINT_IN_OFS			0

#घोषणा UDC_EPINT_IN_EP0			0
#घोषणा UDC_EPINT_IN_EP1			1
#घोषणा UDC_EPINT_IN_EP2			2
#घोषणा UDC_EPINT_IN_EP3			3
#घोषणा UDC_EPINT_OUT_EP0			16
#घोषणा UDC_EPINT_OUT_EP1			17
#घोषणा UDC_EPINT_OUT_EP2			18
#घोषणा UDC_EPINT_OUT_EP3			19

#घोषणा UDC_EPINT_EP0_ENABLE_MSK		0x001e001e

/* Endpoपूर्णांक Interrupt Mask Register -----------------------------------------*/
#घोषणा UDC_EPINT_MSK_ADDR			0x418

#घोषणा UDC_EPINT_OUT_MSK_MASK			0xffff0000
#घोषणा UDC_EPINT_OUT_MSK_OFS			16
#घोषणा UDC_EPINT_IN_MSK_MASK			0x0000ffff
#घोषणा UDC_EPINT_IN_MSK_OFS			0

#घोषणा UDC_EPINT_MSK_DISABLE_ALL		0xffffffff
/* mask non-EP0 endpoपूर्णांकs */
#घोषणा UDC_EPDATAINT_MSK_DISABLE		0xfffefffe
/* mask all dev पूर्णांकerrupts */
#घोषणा UDC_DEV_MSK_DISABLE			0x7f

/* Endpoपूर्णांक-specअगरic CSR's --------------------------------------------------*/
#घोषणा UDC_EPREGS_ADDR				0x0
#घोषणा UDC_EPIN_REGS_ADDR			0x0
#घोषणा UDC_EPOUT_REGS_ADDR			0x200

#घोषणा UDC_EPCTL_ADDR				0x0

#घोषणा UDC_EPCTL_RRDY				9
#घोषणा UDC_EPCTL_CNAK				8
#घोषणा UDC_EPCTL_SNAK				7
#घोषणा UDC_EPCTL_NAK				6

#घोषणा UDC_EPCTL_ET_MASK			0x00000030
#घोषणा UDC_EPCTL_ET_OFS			4
#घोषणा UDC_EPCTL_ET_CONTROL			0
#घोषणा UDC_EPCTL_ET_ISO			1
#घोषणा UDC_EPCTL_ET_BULK			2
#घोषणा UDC_EPCTL_ET_INTERRUPT			3

#घोषणा UDC_EPCTL_P				3
#घोषणा UDC_EPCTL_SN				2
#घोषणा UDC_EPCTL_F				1
#घोषणा UDC_EPCTL_S				0

/* Endpoपूर्णांक Status Registers ------------------------------------------------*/
#घोषणा UDC_EPSTS_ADDR				0x4

#घोषणा UDC_EPSTS_RX_PKT_SIZE_MASK		0x007ff800
#घोषणा UDC_EPSTS_RX_PKT_SIZE_OFS		11

#घोषणा UDC_EPSTS_TDC				10
#घोषणा UDC_EPSTS_HE				9
#घोषणा UDC_EPSTS_BNA				7
#घोषणा UDC_EPSTS_IN				6

#घोषणा UDC_EPSTS_OUT_MASK			0x00000030
#घोषणा UDC_EPSTS_OUT_OFS			4
#घोषणा UDC_EPSTS_OUT_DATA			1
#घोषणा UDC_EPSTS_OUT_DATA_CLEAR		0x10
#घोषणा UDC_EPSTS_OUT_SETUP			2
#घोषणा UDC_EPSTS_OUT_SETUP_CLEAR		0x20
#घोषणा UDC_EPSTS_OUT_CLEAR			0x30

/* Endpoपूर्णांक Buffer Size IN/ Receive Packet Frame Number OUT Registers ------*/
#घोषणा UDC_EPIN_BUFF_SIZE_ADDR			0x8
#घोषणा UDC_EPOUT_FRAME_NUMBER_ADDR		0x8

#घोषणा UDC_EPIN_BUFF_SIZE_MASK			0x0000ffff
#घोषणा UDC_EPIN_BUFF_SIZE_OFS			0
/* EP0in txfअगरo = 128 bytes*/
#घोषणा UDC_EPIN0_BUFF_SIZE			32
/* EP0in fullspeed txfअगरo = 128 bytes*/
#घोषणा UDC_FS_EPIN0_BUFF_SIZE			32

/* fअगरo size mult = fअगरo size / max packet */
#घोषणा UDC_EPIN_BUFF_SIZE_MULT			2

/* EPin data fअगरo size = 1024 bytes DOUBLE BUFFERING */
#घोषणा UDC_EPIN_BUFF_SIZE			256
/* EPin small INT data fअगरo size = 128 bytes */
#घोषणा UDC_EPIN_SMALLINT_BUFF_SIZE		32

/* EPin fullspeed data fअगरo size = 128 bytes DOUBLE BUFFERING */
#घोषणा UDC_FS_EPIN_BUFF_SIZE			32

#घोषणा UDC_EPOUT_FRAME_NUMBER_MASK		0x0000ffff
#घोषणा UDC_EPOUT_FRAME_NUMBER_OFS		0

/* Endpoपूर्णांक Buffer Size OUT/Max Packet Size Registers -----------------------*/
#घोषणा UDC_EPOUT_BUFF_SIZE_ADDR		0x0c
#घोषणा UDC_EP_MAX_PKT_SIZE_ADDR		0x0c

#घोषणा UDC_EPOUT_BUFF_SIZE_MASK		0xffff0000
#घोषणा UDC_EPOUT_BUFF_SIZE_OFS			16
#घोषणा UDC_EP_MAX_PKT_SIZE_MASK		0x0000ffff
#घोषणा UDC_EP_MAX_PKT_SIZE_OFS			0
/* EP0in max packet size = 64 bytes */
#घोषणा UDC_EP0IN_MAX_PKT_SIZE			64
/* EP0out max packet size = 64 bytes */
#घोषणा UDC_EP0OUT_MAX_PKT_SIZE			64
/* EP0in fullspeed max packet size = 64 bytes */
#घोषणा UDC_FS_EP0IN_MAX_PKT_SIZE		64
/* EP0out fullspeed max packet size = 64 bytes */
#घोषणा UDC_FS_EP0OUT_MAX_PKT_SIZE		64

/*
 * Endpoपूर्णांक dma descriptors ------------------------------------------------
 *
 * Setup data, Status dword
 */
#घोषणा UDC_DMA_STP_STS_CFG_MASK		0x0fff0000
#घोषणा UDC_DMA_STP_STS_CFG_OFS			16
#घोषणा UDC_DMA_STP_STS_CFG_ALT_MASK		0x000f0000
#घोषणा UDC_DMA_STP_STS_CFG_ALT_OFS		16
#घोषणा UDC_DMA_STP_STS_CFG_INTF_MASK		0x00f00000
#घोषणा UDC_DMA_STP_STS_CFG_INTF_OFS		20
#घोषणा UDC_DMA_STP_STS_CFG_NUM_MASK		0x0f000000
#घोषणा UDC_DMA_STP_STS_CFG_NUM_OFS		24
#घोषणा UDC_DMA_STP_STS_RX_MASK			0x30000000
#घोषणा UDC_DMA_STP_STS_RX_OFS			28
#घोषणा UDC_DMA_STP_STS_BS_MASK			0xc0000000
#घोषणा UDC_DMA_STP_STS_BS_OFS			30
#घोषणा UDC_DMA_STP_STS_BS_HOST_READY		0
#घोषणा UDC_DMA_STP_STS_BS_DMA_BUSY		1
#घोषणा UDC_DMA_STP_STS_BS_DMA_DONE		2
#घोषणा UDC_DMA_STP_STS_BS_HOST_BUSY		3
/* IN data, Status dword */
#घोषणा UDC_DMA_IN_STS_TXBYTES_MASK		0x0000ffff
#घोषणा UDC_DMA_IN_STS_TXBYTES_OFS		0
#घोषणा	UDC_DMA_IN_STS_FRAMENUM_MASK		0x07ff0000
#घोषणा UDC_DMA_IN_STS_FRAMENUM_OFS		0
#घोषणा UDC_DMA_IN_STS_L			27
#घोषणा UDC_DMA_IN_STS_TX_MASK			0x30000000
#घोषणा UDC_DMA_IN_STS_TX_OFS			28
#घोषणा UDC_DMA_IN_STS_BS_MASK			0xc0000000
#घोषणा UDC_DMA_IN_STS_BS_OFS			30
#घोषणा UDC_DMA_IN_STS_BS_HOST_READY		0
#घोषणा UDC_DMA_IN_STS_BS_DMA_BUSY		1
#घोषणा UDC_DMA_IN_STS_BS_DMA_DONE		2
#घोषणा UDC_DMA_IN_STS_BS_HOST_BUSY		3
/* OUT data, Status dword */
#घोषणा UDC_DMA_OUT_STS_RXBYTES_MASK		0x0000ffff
#घोषणा UDC_DMA_OUT_STS_RXBYTES_OFS		0
#घोषणा UDC_DMA_OUT_STS_FRAMENUM_MASK		0x07ff0000
#घोषणा UDC_DMA_OUT_STS_FRAMENUM_OFS		0
#घोषणा UDC_DMA_OUT_STS_L			27
#घोषणा UDC_DMA_OUT_STS_RX_MASK			0x30000000
#घोषणा UDC_DMA_OUT_STS_RX_OFS			28
#घोषणा UDC_DMA_OUT_STS_BS_MASK			0xc0000000
#घोषणा UDC_DMA_OUT_STS_BS_OFS			30
#घोषणा UDC_DMA_OUT_STS_BS_HOST_READY		0
#घोषणा UDC_DMA_OUT_STS_BS_DMA_BUSY		1
#घोषणा UDC_DMA_OUT_STS_BS_DMA_DONE		2
#घोषणा UDC_DMA_OUT_STS_BS_HOST_BUSY		3
/* max ep0in packet */
#घोषणा UDC_EP0IN_MAXPACKET			1000
/* max dma packet */
#घोषणा UDC_DMA_MAXPACKET			65536

/* un-usable DMA address */
#घोषणा DMA_DONT_USE				(~(dma_addr_t) 0 )

/* other Endpoपूर्णांक रेजिस्टर addresses and values-----------------------------*/
#घोषणा UDC_EP_SUBPTR_ADDR			0x10
#घोषणा UDC_EP_DESPTR_ADDR			0x14
#घोषणा UDC_EP_WRITE_CONFIRM_ADDR		0x1c

/* EP number as layouted in AHB space */
#घोषणा UDC_EP_NUM				32
#घोषणा UDC_EPIN_NUM				16
#घोषणा UDC_EPIN_NUM_USED			5
#घोषणा UDC_EPOUT_NUM				16
/* EP number of EP's really used = EP0 + 8 data EP's */
#घोषणा UDC_USED_EP_NUM				9
/* UDC CSR regs are aligned but AHB regs not - offset क्रम OUT EP's */
#घोषणा UDC_CSR_EP_OUT_IX_OFS			12

#घोषणा UDC_EP0OUT_IX				16
#घोषणा UDC_EP0IN_IX				0

/* Rx fअगरo address and size = 1k -------------------------------------------*/
#घोषणा UDC_RXFIFO_ADDR				0x800
#घोषणा UDC_RXFIFO_SIZE				0x400

/* Tx fअगरo address and size = 1.5k -----------------------------------------*/
#घोषणा UDC_TXFIFO_ADDR				0xc00
#घोषणा UDC_TXFIFO_SIZE				0x600

/* शेष data endpoपूर्णांकs --------------------------------------------------*/
#घोषणा UDC_EPIN_STATUS_IX			1
#घोषणा UDC_EPIN_IX				2
#घोषणा UDC_EPOUT_IX				18

/* general स्थिरants -------------------------------------------------------*/
#घोषणा UDC_DWORD_BYTES				4
#घोषणा UDC_BITS_PER_BYTE_SHIFT			3
#घोषणा UDC_BYTE_MASK				0xff
#घोषणा UDC_BITS_PER_BYTE			8

/*---------------------------------------------------------------------------*/
/* UDC CSR's */
काष्ठा udc_csrs अणु

	/* sca - setup command address */
	u32 sca;

	/* ep ne's */
	u32 ne[UDC_USED_EP_NUM];
पूर्ण __attribute__ ((packed));

/* AHB subप्रणाली CSR रेजिस्टरs */
काष्ठा udc_regs अणु

	/* device configuration */
	u32 cfg;

	/* device control */
	u32 ctl;

	/* device status */
	u32 sts;

	/* device पूर्णांकerrupt */
	u32 irqsts;

	/* device पूर्णांकerrupt mask */
	u32 irqmsk;

	/* endpoपूर्णांक पूर्णांकerrupt */
	u32 ep_irqsts;

	/* endpoपूर्णांक पूर्णांकerrupt mask */
	u32 ep_irqmsk;
पूर्ण __attribute__ ((packed));

/* endpoपूर्णांक specअगरic रेजिस्टरs */
काष्ठा udc_ep_regs अणु

	/* endpoपूर्णांक control */
	u32 ctl;

	/* endpoपूर्णांक status */
	u32 sts;

	/* endpoपूर्णांक buffer size in/ receive packet frame number out */
	u32 bufin_framक्रमागत;

	/* endpoपूर्णांक buffer size out/max packet size */
	u32 bufout_maxpkt;

	/* endpoपूर्णांक setup buffer poपूर्णांकer */
	u32 subptr;

	/* endpoपूर्णांक data descriptor poपूर्णांकer */
	u32 desptr;

	/* reserved */
	u32 reserved;

	/* ग_लिखो/पढ़ो confirmation */
	u32 confirm;

पूर्ण __attribute__ ((packed));

/* control data DMA desc */
काष्ठा udc_stp_dma अणु
	/* status quadlet */
	u32	status;
	/* reserved */
	u32	_reserved;
	/* first setup word */
	u32	data12;
	/* second setup word */
	u32	data34;
पूर्ण __attribute__ ((aligned (16)));

/* normal data DMA desc */
काष्ठा udc_data_dma अणु
	/* status quadlet */
	u32	status;
	/* reserved */
	u32	_reserved;
	/* buffer poपूर्णांकer */
	u32	bufptr;
	/* next descriptor poपूर्णांकer */
	u32	next;
पूर्ण __attribute__ ((aligned (16)));

/* request packet */
काष्ठा udc_request अणु
	/* embedded gadget ep */
	काष्ठा usb_request		req;

	/* flags */
	अचिन्हित			dma_going : 1,
					dma_करोne : 1;
	/* phys. address */
	dma_addr_t			td_phys;
	/* first dma desc. of chain */
	काष्ठा udc_data_dma		*td_data;
	/* last dma desc. of chain */
	काष्ठा udc_data_dma		*td_data_last;
	काष्ठा list_head		queue;

	/* chain length */
	अचिन्हित			chain_len;

पूर्ण;

/* UDC specअगरic endpoपूर्णांक parameters */
काष्ठा udc_ep अणु
	काष्ठा usb_ep			ep;
	काष्ठा udc_ep_regs __iomem	*regs;
	u32 __iomem			*txfअगरo;
	u32 __iomem			*dma;
	dma_addr_t			td_phys;
	dma_addr_t			td_stp_dma;
	काष्ठा udc_stp_dma		*td_stp;
	काष्ठा udc_data_dma		*td;
	/* temp request */
	काष्ठा udc_request		*req;
	अचिन्हित			req_used;
	अचिन्हित			req_completed;
	/* dummy DMA desc क्रम BNA dummy */
	काष्ठा udc_request		*bna_dummy_req;
	अचिन्हित			bna_occurred;

	/* NAK state */
	अचिन्हित			naking;

	काष्ठा udc			*dev;

	/* queue क्रम requests */
	काष्ठा list_head		queue;
	अचिन्हित			halted;
	अचिन्हित			cancel_transfer;
	अचिन्हित			num : 5,
					fअगरo_depth : 14,
					in : 1;
पूर्ण;

/* device काष्ठा */
काष्ठा udc अणु
	काष्ठा usb_gadget		gadget;
	spinlock_t			lock;	/* protects all state */
	/* all endpoपूर्णांकs */
	काष्ठा udc_ep			ep[UDC_EP_NUM];
	काष्ठा usb_gadget_driver	*driver;
	/* operational flags */
	अचिन्हित			stall_ep0in : 1,
					रुकोing_zlp_ack_ep0in : 1,
					set_cfg_not_acked : 1,
					data_ep_enabled : 1,
					data_ep_queued : 1,
					sys_suspended : 1,
					connected;

	u16				chiprev;

	/* रेजिस्टरs */
	काष्ठा pci_dev			*pdev;
	काष्ठा udc_csrs __iomem		*csr;
	काष्ठा udc_regs __iomem		*regs;
	काष्ठा udc_ep_regs __iomem	*ep_regs;
	u32 __iomem			*rxfअगरo;
	u32 __iomem			*txfअगरo;

	/* DMA desc pools */
	काष्ठा dma_pool			*data_requests;
	काष्ठा dma_pool			*stp_requests;

	/* device data */
	अचिन्हित दीर्घ			phys_addr;
	व्योम __iomem			*virt_addr;
	अचिन्हित			irq;

	/* states */
	u16				cur_config;
	u16				cur_पूर्णांकf;
	u16				cur_alt;

	/* क्रम platक्रमm device and extcon support */
	काष्ठा device			*dev;
	काष्ठा phy			*udc_phy;
	काष्ठा extcon_dev		*edev;
	काष्ठा extcon_specअगरic_cable_nb	extcon_nb;
	काष्ठा notअगरier_block		nb;
	काष्ठा delayed_work		drd_work;
	काष्ठा workqueue_काष्ठा		*drd_wq;
	u32				conn_type;
पूर्ण;

#घोषणा to_amd5536_udc(g)	(container_of((g), काष्ठा udc, gadget))

/* setup request data */
जोड़ udc_setup_data अणु
	u32			data[2];
	काष्ठा usb_ctrlrequest	request;
पूर्ण;

/* Function declarations */
पूर्णांक udc_enable_dev_setup_पूर्णांकerrupts(काष्ठा udc *dev);
पूर्णांक udc_mask_unused_पूर्णांकerrupts(काष्ठा udc *dev);
irqवापस_t udc_irq(पूर्णांक irq, व्योम *pdev);
व्योम gadget_release(काष्ठा device *pdev);
व्योम empty_req_queue(काष्ठा udc_ep *ep);
व्योम udc_basic_init(काष्ठा udc *dev);
व्योम मुक्त_dma_pools(काष्ठा udc *dev);
पूर्णांक init_dma_pools(काष्ठा udc *dev);
व्योम udc_हटाओ(काष्ठा udc *dev);
पूर्णांक udc_probe(काष्ठा udc *dev);

/* DMA usage flag */
अटल bool use_dma = 1;
/* packet per buffer dma */
अटल bool use_dma_ppb = 1;
/* with per descr. update */
अटल bool use_dma_ppb_du;
/* full speed only mode */
अटल bool use_fullspeed;

/* module parameters */
module_param(use_dma, bool, S_IRUGO);
MODULE_PARM_DESC(use_dma, "true for DMA");
module_param(use_dma_ppb, bool, S_IRUGO);
MODULE_PARM_DESC(use_dma_ppb, "true for DMA in packet per buffer mode");
module_param(use_dma_ppb_du, bool, S_IRUGO);
MODULE_PARM_DESC(use_dma_ppb_du,
	"true for DMA in packet per buffer mode with descriptor update");
module_param(use_fullspeed, bool, S_IRUGO);
MODULE_PARM_DESC(use_fullspeed, "true for fullspeed only");
/*
 *---------------------------------------------------------------------------
 * SET and GET bitfields in u32 values
 * via स्थिरants क्रम mask/offset:
 * <bit_field_stub_name> is the text between
 * UDC_ and _MASK|_OFS of appropriate
 * स्थिरant
 *
 * set bitfield value in u32 u32Val
 */
#घोषणा AMD_ADDBITS(u32Val, bitfield_val, bitfield_stub_name)		\
	(((u32Val) & (((u32) ~((u32) bitfield_stub_name##_MASK))))	\
	| (((bitfield_val) << ((u32) bitfield_stub_name##_OFS))		\
		& ((u32) bitfield_stub_name##_MASK)))

/*
 * set bitfield value in zero-initialized u32 u32Val
 * => bitfield bits in u32Val are all zero
 */
#घोषणा AMD_INIT_SETBITS(u32Val, bitfield_val, bitfield_stub_name)	\
	((u32Val)							\
	| (((bitfield_val) << ((u32) bitfield_stub_name##_OFS))		\
		& ((u32) bitfield_stub_name##_MASK)))

/* get bitfield value from u32 u32Val */
#घोषणा AMD_GETBITS(u32Val, bitfield_stub_name)				\
	((u32Val & ((u32) bitfield_stub_name##_MASK))			\
		>> ((u32) bitfield_stub_name##_OFS))

/* SET and GET bits in u32 values ------------------------------------------*/
#घोषणा AMD_BIT(bit_stub_name) (1 << bit_stub_name)
#घोषणा AMD_UNMASK_BIT(bit_stub_name) (~AMD_BIT(bit_stub_name))
#घोषणा AMD_CLEAR_BIT(bit_stub_name) (~AMD_BIT(bit_stub_name))

/* debug macros ------------------------------------------------------------*/

#घोषणा DBG(udc , args...)	dev_dbg(udc->dev, args)

#अगर_घोषित UDC_VERBOSE
#घोषणा VDBG			DBG
#अन्यथा
#घोषणा VDBG(udc , args...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* #अगर_घोषित AMD5536UDC_H */

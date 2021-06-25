<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Faraday FOTG210 USB OTG controller
 *
 * Copyright (C) 2013 Faraday Technology Corporation
 * Author: Yuan-Hsin Chen <yhchen@faraday-tech.com>
 */

#समावेश <linux/kernel.h>

#घोषणा FOTG210_MAX_NUM_EP	5 /* ep0...ep4 */
#घोषणा FOTG210_MAX_FIFO_NUM	4 /* fअगरo0...fअगरo4 */

/* Global Mask of HC/OTG/DEV पूर्णांकerrupt Register(0xC4) */
#घोषणा FOTG210_GMIR		0xC4
#घोषणा GMIR_INT_POLARITY	0x8 /*Active High*/
#घोषणा GMIR_MHC_INT		0x4
#घोषणा GMIR_MOTG_INT		0x2
#घोषणा GMIR_MDEV_INT		0x1

/*  Device Main Control Register(0x100) */
#घोषणा FOTG210_DMCR		0x100
#घोषणा DMCR_HS_EN		(1 << 6)
#घोषणा DMCR_CHIP_EN		(1 << 5)
#घोषणा DMCR_SFRST		(1 << 4)
#घोषणा DMCR_GOSUSP		(1 << 3)
#घोषणा DMCR_GLINT_EN		(1 << 2)
#घोषणा DMCR_HALF_SPEED		(1 << 1)
#घोषणा DMCR_CAP_RMWAKUP	(1 << 0)

/* Device Address Register(0x104) */
#घोषणा FOTG210_DAR		0x104
#घोषणा DAR_AFT_CONF		(1 << 7)

/* Device Test Register(0x108) */
#घोषणा FOTG210_DTR		0x108
#घोषणा DTR_TST_CLRFF		(1 << 0)

/* PHY Test Mode Selector रेजिस्टर(0x114) */
#घोषणा FOTG210_PHYTMSR		0x114
#घोषणा PHYTMSR_TST_PKT		(1 << 4)
#घोषणा PHYTMSR_TST_SE0NAK	(1 << 3)
#घोषणा PHYTMSR_TST_KSTA	(1 << 2)
#घोषणा PHYTMSR_TST_JSTA	(1 << 1)
#घोषणा PHYTMSR_UNPLUG		(1 << 0)

/* Cx configuration and FIFO Empty Status रेजिस्टर(0x120) */
#घोषणा FOTG210_DCFESR		0x120
#घोषणा DCFESR_FIFO_EMPTY(fअगरo)	(1 << 8 << (fअगरo))
#घोषणा DCFESR_CX_EMP		(1 << 5)
#घोषणा DCFESR_CX_CLR		(1 << 3)
#घोषणा DCFESR_CX_STL		(1 << 2)
#घोषणा DCFESR_TST_PKDONE	(1 << 1)
#घोषणा DCFESR_CX_DONE		(1 << 0)

/* Device IDLE Counter Register(0x124) */
#घोषणा FOTG210_DICR		0x124

/* Device Mask of Interrupt Group Register (0x130) */
#घोषणा FOTG210_DMIGR		0x130
#घोषणा DMIGR_MINT_G0		(1 << 0)

/* Device Mask of Interrupt Source Group 0(0x134) */
#घोषणा FOTG210_DMISGR0		0x134
#घोषणा DMISGR0_MCX_COMEND	(1 << 3)
#घोषणा DMISGR0_MCX_OUT_INT	(1 << 2)
#घोषणा DMISGR0_MCX_IN_INT	(1 << 1)
#घोषणा DMISGR0_MCX_SETUP_INT	(1 << 0)

/* Device Mask of Interrupt Source Group 1 Register(0x138)*/
#घोषणा FOTG210_DMISGR1		0x138
#घोषणा DMISGR1_MF3_IN_INT	(1 << 19)
#घोषणा DMISGR1_MF2_IN_INT	(1 << 18)
#घोषणा DMISGR1_MF1_IN_INT	(1 << 17)
#घोषणा DMISGR1_MF0_IN_INT	(1 << 16)
#घोषणा DMISGR1_MF_IN_INT(fअगरo)	(1 << (16 + (fअगरo)))
#घोषणा DMISGR1_MF3_SPK_INT	(1 << 7)
#घोषणा DMISGR1_MF3_OUT_INT	(1 << 6)
#घोषणा DMISGR1_MF2_SPK_INT	(1 << 5)
#घोषणा DMISGR1_MF2_OUT_INT	(1 << 4)
#घोषणा DMISGR1_MF1_SPK_INT	(1 << 3)
#घोषणा DMISGR1_MF1_OUT_INT	(1 << 2)
#घोषणा DMISGR1_MF0_SPK_INT	(1 << 1)
#घोषणा DMISGR1_MF0_OUT_INT	(1 << 0)
#घोषणा DMISGR1_MF_OUTSPK_INT(fअगरo)	(0x3 << (fअगरo) * 2)

/* Device Mask of Interrupt Source Group 2 Register (0x13C) */
#घोषणा FOTG210_DMISGR2		0x13C
#घोषणा DMISGR2_MDMA_ERROR	(1 << 8)
#घोषणा DMISGR2_MDMA_CMPLT	(1 << 7)

/* Device Interrupt group Register (0x140) */
#घोषणा FOTG210_DIGR		0x140
#घोषणा DIGR_INT_G2		(1 << 2)
#घोषणा DIGR_INT_G1		(1 << 1)
#घोषणा DIGR_INT_G0		(1 << 0)

/* Device Interrupt Source Group 0 Register (0x144) */
#घोषणा FOTG210_DISGR0		0x144
#घोषणा DISGR0_CX_COMABT_INT	(1 << 5)
#घोषणा DISGR0_CX_COMFAIL_INT	(1 << 4)
#घोषणा DISGR0_CX_COMEND_INT	(1 << 3)
#घोषणा DISGR0_CX_OUT_INT	(1 << 2)
#घोषणा DISGR0_CX_IN_INT	(1 << 1)
#घोषणा DISGR0_CX_SETUP_INT	(1 << 0)

/* Device Interrupt Source Group 1 Register (0x148) */
#घोषणा FOTG210_DISGR1		0x148
#घोषणा DISGR1_OUT_INT(fअगरo)	(1 << ((fअगरo) * 2))
#घोषणा DISGR1_SPK_INT(fअगरo)	(1 << 1 << ((fअगरo) * 2))
#घोषणा DISGR1_IN_INT(fअगरo)	(1 << 16 << (fअगरo))

/* Device Interrupt Source Group 2 Register (0x14C) */
#घोषणा FOTG210_DISGR2		0x14C
#घोषणा DISGR2_DMA_ERROR	(1 << 8)
#घोषणा DISGR2_DMA_CMPLT	(1 << 7)
#घोषणा DISGR2_RX0BYTE_INT	(1 << 6)
#घोषणा DISGR2_TX0BYTE_INT	(1 << 5)
#घोषणा DISGR2_ISO_SEQ_ABORT_INT	(1 << 4)
#घोषणा DISGR2_ISO_SEQ_ERR_INT	(1 << 3)
#घोषणा DISGR2_RESM_INT		(1 << 2)
#घोषणा DISGR2_SUSP_INT		(1 << 1)
#घोषणा DISGR2_USBRST_INT	(1 << 0)

/* Device Receive Zero-Length Data Packet Register (0x150)*/
#घोषणा FOTG210_RX0BYTE		0x150
#घोषणा RX0BYTE_EP8		(1 << 7)
#घोषणा RX0BYTE_EP7		(1 << 6)
#घोषणा RX0BYTE_EP6		(1 << 5)
#घोषणा RX0BYTE_EP5		(1 << 4)
#घोषणा RX0BYTE_EP4		(1 << 3)
#घोषणा RX0BYTE_EP3		(1 << 2)
#घोषणा RX0BYTE_EP2		(1 << 1)
#घोषणा RX0BYTE_EP1		(1 << 0)

/* Device Transfer Zero-Length Data Packet Register (0x154)*/
#घोषणा FOTG210_TX0BYTE		0x154
#घोषणा TX0BYTE_EP8		(1 << 7)
#घोषणा TX0BYTE_EP7		(1 << 6)
#घोषणा TX0BYTE_EP6		(1 << 5)
#घोषणा TX0BYTE_EP5		(1 << 4)
#घोषणा TX0BYTE_EP4		(1 << 3)
#घोषणा TX0BYTE_EP3		(1 << 2)
#घोषणा TX0BYTE_EP2		(1 << 1)
#घोषणा TX0BYTE_EP1		(1 << 0)

/* Device IN Endpoपूर्णांक x MaxPacketSize Register(0x160+4*(x-1)) */
#घोषणा FOTG210_INEPMPSR(ep)	(0x160 + 4 * ((ep) - 1))
#घोषणा INOUTEPMPSR_MPS(mps)	((mps) & 0x2FF)
#घोषणा INOUTEPMPSR_STL_EP	(1 << 11)
#घोषणा INOUTEPMPSR_RESET_TSEQ	(1 << 12)

/* Device OUT Endpoपूर्णांक x MaxPacketSize Register(0x180+4*(x-1)) */
#घोषणा FOTG210_OUTEPMPSR(ep)	(0x180 + 4 * ((ep) - 1))

/* Device Endpoपूर्णांक 1~4 Map Register (0x1A0) */
#घोषणा FOTG210_EPMAP		0x1A0
#घोषणा EPMAP_FIFONO(ep, dir)		\
	((((ep) - 1) << ((ep) - 1) * 8) << ((dir) ? 0 : 4))
#घोषणा EPMAP_FIFONOMSK(ep, dir)	\
	((3 << ((ep) - 1) * 8) << ((dir) ? 0 : 4))

/* Device FIFO Map Register (0x1A8) */
#घोषणा FOTG210_FIFOMAP		0x1A8
#घोषणा FIFOMAP_सूचीOUT(fअगरo)	(0x0 << 4 << (fअगरo) * 8)
#घोषणा FIFOMAP_सूचीIN(fअगरo)	(0x1 << 4 << (fअगरo) * 8)
#घोषणा FIFOMAP_BIसूची(fअगरo)	(0x2 << 4 << (fअगरo) * 8)
#घोषणा FIFOMAP_NA(fअगरo)	(0x3 << 4 << (fअगरo) * 8)
#घोषणा FIFOMAP_EPNO(ep)	((ep) << ((ep) - 1) * 8)
#घोषणा FIFOMAP_EPNOMSK(ep)	(0xF << ((ep) - 1) * 8)

/* Device FIFO Confuguration Register (0x1AC) */
#घोषणा FOTG210_FIFOCF		0x1AC
#घोषणा FIFOCF_TYPE(type, fअगरo)	((type) << (fअगरo) * 8)
#घोषणा FIFOCF_BLK_SIN(fअगरo)	(0x0 << (fअगरo) * 8 << 2)
#घोषणा FIFOCF_BLK_DUB(fअगरo)	(0x1 << (fअगरo) * 8 << 2)
#घोषणा FIFOCF_BLK_TRI(fअगरo)	(0x2 << (fअगरo) * 8 << 2)
#घोषणा FIFOCF_BLKSZ_512(fअगरo)	(0x0 << (fअगरo) * 8 << 4)
#घोषणा FIFOCF_BLKSZ_1024(fअगरo)	(0x1 << (fअगरo) * 8 << 4)
#घोषणा FIFOCF_FIFO_EN(fअगरo)	(0x1 << (fअगरo) * 8 << 5)

/* Device FIFO n Inकाष्ठाion and Byte Count Register (0x1B0+4*n) */
#घोषणा FOTG210_FIBCR(fअगरo)	(0x1B0 + (fअगरo) * 4)
#घोषणा FIBCR_BCFX		0x7FF
#घोषणा FIBCR_FFRST		(1 << 12)

/* Device DMA Target FIFO Number Register (0x1C0) */
#घोषणा FOTG210_DMATFNR		0x1C0
#घोषणा DMATFNR_ACC_CXF		(1 << 4)
#घोषणा DMATFNR_ACC_F3		(1 << 3)
#घोषणा DMATFNR_ACC_F2		(1 << 2)
#घोषणा DMATFNR_ACC_F1		(1 << 1)
#घोषणा DMATFNR_ACC_F0		(1 << 0)
#घोषणा DMATFNR_ACC_FN(fअगरo)	(1 << (fअगरo))
#घोषणा DMATFNR_DISDMA		0

/* Device DMA Controller Parameter setting 1 Register (0x1C8) */
#घोषणा FOTG210_DMACPSR1	0x1C8
#घोषणा DMACPSR1_DMA_LEN(len)	(((len) & 0xFFFF) << 8)
#घोषणा DMACPSR1_DMA_ABORT	(1 << 3)
#घोषणा DMACPSR1_DMA_TYPE(dir_in)	(((dir_in) ? 1 : 0) << 1)
#घोषणा DMACPSR1_DMA_START	(1 << 0)

/* Device DMA Controller Parameter setting 2 Register (0x1CC) */
#घोषणा FOTG210_DMACPSR2	0x1CC

/* Device DMA Controller Parameter setting 3 Register (0x1CC) */
#घोषणा FOTG210_CXPORT		0x1D0

काष्ठा fotg210_request अणु
	काष्ठा usb_request	req;
	काष्ठा list_head	queue;
पूर्ण;

काष्ठा fotg210_ep अणु
	काष्ठा usb_ep		ep;
	काष्ठा fotg210_udc	*fotg210;

	काष्ठा list_head	queue;
	अचिन्हित		stall:1;
	अचिन्हित		wedged:1;
	अचिन्हित		use_dma:1;

	अचिन्हित अक्षर		epnum;
	अचिन्हित अक्षर		type;
	अचिन्हित अक्षर		dir_in;
	अचिन्हित पूर्णांक		maxp;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor	*desc;
पूर्ण;

काष्ठा fotg210_udc अणु
	spinlock_t		lock; /* protect the काष्ठा */
	व्योम __iomem		*reg;

	अचिन्हित दीर्घ		irq_trigger;

	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;

	काष्ठा fotg210_ep	*ep[FOTG210_MAX_NUM_EP];

	काष्ठा usb_request	*ep0_req;	/* क्रम पूर्णांकernal request */
	__le16			ep0_data;
	u8			ep0_dir;	/* 0/0x80  out/in */

	u8			reक्रमागत;		/* अगर re-क्रमागतeration */
पूर्ण;

#घोषणा gadget_to_fotg210(g)	container_of((g), काष्ठा fotg210_udc, gadget)

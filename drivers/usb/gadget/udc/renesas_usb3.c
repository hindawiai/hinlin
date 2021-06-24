<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas USB3.0 Peripheral driver (USB gadget)
 *
 * Copyright (C) 2015-2017  Renesas Electronics Corporation
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sys_soc.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/role.h>

/* रेजिस्टर definitions */
#घोषणा USB3_AXI_INT_STA	0x008
#घोषणा USB3_AXI_INT_ENA	0x00c
#घोषणा USB3_DMA_INT_STA	0x010
#घोषणा USB3_DMA_INT_ENA	0x014
#घोषणा USB3_DMA_CH0_CON(n)	(0x030 + ((n) - 1) * 0x10) /* n = 1 to 4 */
#घोषणा USB3_DMA_CH0_PRD_ADR(n)	(0x034 + ((n) - 1) * 0x10) /* n = 1 to 4 */
#घोषणा USB3_USB_COM_CON	0x200
#घोषणा USB3_USB20_CON		0x204
#घोषणा USB3_USB30_CON		0x208
#घोषणा USB3_USB_STA		0x210
#घोषणा USB3_DRD_CON		0x218
#घोषणा USB3_USB_INT_STA_1	0x220
#घोषणा USB3_USB_INT_STA_2	0x224
#घोषणा USB3_USB_INT_ENA_1	0x228
#घोषणा USB3_USB_INT_ENA_2	0x22c
#घोषणा USB3_STUP_DAT_0		0x230
#घोषणा USB3_STUP_DAT_1		0x234
#घोषणा USB3_USB_OTG_STA	0x268
#घोषणा USB3_USB_OTG_INT_STA	0x26c
#घोषणा USB3_USB_OTG_INT_ENA	0x270
#घोषणा USB3_P0_MOD		0x280
#घोषणा USB3_P0_CON		0x288
#घोषणा USB3_P0_STA		0x28c
#घोषणा USB3_P0_INT_STA		0x290
#घोषणा USB3_P0_INT_ENA		0x294
#घोषणा USB3_P0_LNG		0x2a0
#घोषणा USB3_P0_READ		0x2a4
#घोषणा USB3_P0_WRITE		0x2a8
#घोषणा USB3_PIPE_COM		0x2b0
#घोषणा USB3_PN_MOD		0x2c0
#घोषणा USB3_PN_RAMMAP		0x2c4
#घोषणा USB3_PN_CON		0x2c8
#घोषणा USB3_PN_STA		0x2cc
#घोषणा USB3_PN_INT_STA		0x2d0
#घोषणा USB3_PN_INT_ENA		0x2d4
#घोषणा USB3_PN_LNG		0x2e0
#घोषणा USB3_PN_READ		0x2e4
#घोषणा USB3_PN_WRITE		0x2e8
#घोषणा USB3_SSIFCMD		0x340

/* AXI_INT_ENA and AXI_INT_STA */
#घोषणा AXI_INT_DMAINT		BIT(31)
#घोषणा AXI_INT_EPCINT		BIT(30)
/* PRD's n = from 1 to 4 */
#घोषणा AXI_INT_PRDEN_CLR_STA_SHIFT(n)	(16 + (n) - 1)
#घोषणा AXI_INT_PRDERR_STA_SHIFT(n)	(0 + (n) - 1)
#घोषणा AXI_INT_PRDEN_CLR_STA(n)	(1 << AXI_INT_PRDEN_CLR_STA_SHIFT(n))
#घोषणा AXI_INT_PRDERR_STA(n)		(1 << AXI_INT_PRDERR_STA_SHIFT(n))

/* DMA_INT_ENA and DMA_INT_STA */
#घोषणा DMA_INT(n)		BIT(n)

/* DMA_CH0_CONn */
#घोषणा DMA_CON_PIPE_सूची	BIT(15)		/* 1: In Transfer */
#घोषणा DMA_CON_PIPE_NO_SHIFT	8
#घोषणा DMA_CON_PIPE_NO_MASK	GENMASK(12, DMA_CON_PIPE_NO_SHIFT)
#घोषणा DMA_COM_PIPE_NO(n)	(((n) << DMA_CON_PIPE_NO_SHIFT) & \
					 DMA_CON_PIPE_NO_MASK)
#घोषणा DMA_CON_PRD_EN		BIT(0)

/* LCLKSEL */
#घोषणा LCLKSEL_LSEL		BIT(18)

/* USB_COM_CON */
#घोषणा USB_COM_CON_CONF		BIT(24)
#घोषणा USB_COM_CON_PN_WDATAIF_NL	BIT(23)
#घोषणा USB_COM_CON_PN_RDATAIF_NL	BIT(22)
#घोषणा USB_COM_CON_PN_LSTTR_PP		BIT(21)
#घोषणा USB_COM_CON_SPD_MODE		BIT(17)
#घोषणा USB_COM_CON_EP0_EN		BIT(16)
#घोषणा USB_COM_CON_DEV_ADDR_SHIFT	8
#घोषणा USB_COM_CON_DEV_ADDR_MASK	GENMASK(14, USB_COM_CON_DEV_ADDR_SHIFT)
#घोषणा USB_COM_CON_DEV_ADDR(n)		(((n) << USB_COM_CON_DEV_ADDR_SHIFT) & \
					 USB_COM_CON_DEV_ADDR_MASK)
#घोषणा USB_COM_CON_RX_DETECTION	BIT(1)
#घोषणा USB_COM_CON_PIPE_CLR		BIT(0)

/* USB20_CON */
#घोषणा USB20_CON_B2_PUE		BIT(31)
#घोषणा USB20_CON_B2_SUSPEND		BIT(24)
#घोषणा USB20_CON_B2_CONNECT		BIT(17)
#घोषणा USB20_CON_B2_TSTMOD_SHIFT	8
#घोषणा USB20_CON_B2_TSTMOD_MASK	GENMASK(10, USB20_CON_B2_TSTMOD_SHIFT)
#घोषणा USB20_CON_B2_TSTMOD(n)		(((n) << USB20_CON_B2_TSTMOD_SHIFT) & \
					 USB20_CON_B2_TSTMOD_MASK)
#घोषणा USB20_CON_B2_TSTMOD_EN		BIT(0)

/* USB30_CON */
#घोषणा USB30_CON_POW_SEL_SHIFT		24
#घोषणा USB30_CON_POW_SEL_MASK		GENMASK(26, USB30_CON_POW_SEL_SHIFT)
#घोषणा USB30_CON_POW_SEL_IN_U3		BIT(26)
#घोषणा USB30_CON_POW_SEL_IN_DISCON	0
#घोषणा USB30_CON_POW_SEL_P2_TO_P0	BIT(25)
#घोषणा USB30_CON_POW_SEL_P0_TO_P3	BIT(24)
#घोषणा USB30_CON_POW_SEL_P0_TO_P2	0
#घोषणा USB30_CON_B3_PLLWAKE		BIT(23)
#घोषणा USB30_CON_B3_CONNECT		BIT(17)
#घोषणा USB30_CON_B3_HOTRST_CMP		BIT(1)

/* USB_STA */
#घोषणा USB_STA_SPEED_MASK	(BIT(2) | BIT(1))
#घोषणा USB_STA_SPEED_HS	BIT(2)
#घोषणा USB_STA_SPEED_FS	BIT(1)
#घोषणा USB_STA_SPEED_SS	0
#घोषणा USB_STA_VBUS_STA	BIT(0)

/* DRD_CON */
#घोषणा DRD_CON_PERI_CON	BIT(24)
#घोषणा DRD_CON_VBOUT		BIT(0)

/* USB_INT_ENA_1 and USB_INT_STA_1 */
#घोषणा USB_INT_1_B3_PLLWKUP	BIT(31)
#घोषणा USB_INT_1_B3_LUPSUCS	BIT(30)
#घोषणा USB_INT_1_B3_DISABLE	BIT(27)
#घोषणा USB_INT_1_B3_WRMRST	BIT(21)
#घोषणा USB_INT_1_B3_HOTRST	BIT(20)
#घोषणा USB_INT_1_B2_USBRST	BIT(12)
#घोषणा USB_INT_1_B2_L1SPND	BIT(11)
#घोषणा USB_INT_1_B2_SPND	BIT(9)
#घोषणा USB_INT_1_B2_RSUM	BIT(8)
#घोषणा USB_INT_1_SPEED		BIT(1)
#घोषणा USB_INT_1_VBUS_CNG	BIT(0)

/* USB_INT_ENA_2 and USB_INT_STA_2 */
#घोषणा USB_INT_2_PIPE(n)	BIT(n)

/* USB_OTG_STA, USB_OTG_INT_STA and USB_OTG_INT_ENA */
#घोषणा USB_OTG_IDMON		BIT(4)

/* P0_MOD */
#घोषणा P0_MOD_सूची		BIT(6)

/* P0_CON and PN_CON */
#घोषणा PX_CON_BYTE_EN_MASK		(BIT(10) | BIT(9))
#घोषणा PX_CON_BYTE_EN_SHIFT		9
#घोषणा PX_CON_BYTE_EN_BYTES(n)		(((n) << PX_CON_BYTE_EN_SHIFT) & \
					 PX_CON_BYTE_EN_MASK)
#घोषणा PX_CON_SEND			BIT(8)

/* P0_CON */
#घोषणा P0_CON_ST_RES_MASK		(BIT(27) | BIT(26))
#घोषणा P0_CON_ST_RES_FORCE_STALL	BIT(27)
#घोषणा P0_CON_ST_RES_NORMAL		BIT(26)
#घोषणा P0_CON_ST_RES_FORCE_NRDY	0
#घोषणा P0_CON_OT_RES_MASK		(BIT(25) | BIT(24))
#घोषणा P0_CON_OT_RES_FORCE_STALL	BIT(25)
#घोषणा P0_CON_OT_RES_NORMAL		BIT(24)
#घोषणा P0_CON_OT_RES_FORCE_NRDY	0
#घोषणा P0_CON_IN_RES_MASK		(BIT(17) | BIT(16))
#घोषणा P0_CON_IN_RES_FORCE_STALL	BIT(17)
#घोषणा P0_CON_IN_RES_NORMAL		BIT(16)
#घोषणा P0_CON_IN_RES_FORCE_NRDY	0
#घोषणा P0_CON_RES_WEN			BIT(7)
#घोषणा P0_CON_BCLR			BIT(1)

/* P0_STA and PN_STA */
#घोषणा PX_STA_BUFSTS		BIT(0)

/* P0_INT_ENA and P0_INT_STA */
#घोषणा P0_INT_STSED		BIT(18)
#घोषणा P0_INT_STSST		BIT(17)
#घोषणा P0_INT_SETUP		BIT(16)
#घोषणा P0_INT_RCVNL		BIT(8)
#घोषणा P0_INT_ERDY		BIT(7)
#घोषणा P0_INT_FLOW		BIT(6)
#घोषणा P0_INT_STALL		BIT(2)
#घोषणा P0_INT_NRDY		BIT(1)
#घोषणा P0_INT_BFRDY		BIT(0)
#घोषणा P0_INT_ALL_BITS		(P0_INT_STSED | P0_INT_SETUP | P0_INT_BFRDY)

/* PN_MOD */
#घोषणा PN_MOD_सूची		BIT(6)
#घोषणा PN_MOD_TYPE_SHIFT	4
#घोषणा PN_MOD_TYPE_MASK	GENMASK(5, PN_MOD_TYPE_SHIFT)
#घोषणा PN_MOD_TYPE(n)		(((n) << PN_MOD_TYPE_SHIFT) & \
				 PN_MOD_TYPE_MASK)
#घोषणा PN_MOD_EPNUM_MASK	GENMASK(3, 0)
#घोषणा PN_MOD_EPNUM(n)		((n) & PN_MOD_EPNUM_MASK)

/* PN_RAMMAP */
#घोषणा PN_RAMMAP_RAMAREA_SHIFT	29
#घोषणा PN_RAMMAP_RAMAREA_MASK	GENMASK(31, PN_RAMMAP_RAMAREA_SHIFT)
#घोषणा PN_RAMMAP_RAMAREA_16KB	BIT(31)
#घोषणा PN_RAMMAP_RAMAREA_8KB	(BIT(30) | BIT(29))
#घोषणा PN_RAMMAP_RAMAREA_4KB	BIT(30)
#घोषणा PN_RAMMAP_RAMAREA_2KB	BIT(29)
#घोषणा PN_RAMMAP_RAMAREA_1KB	0
#घोषणा PN_RAMMAP_MPKT_SHIFT	16
#घोषणा PN_RAMMAP_MPKT_MASK	GENMASK(26, PN_RAMMAP_MPKT_SHIFT)
#घोषणा PN_RAMMAP_MPKT(n)	(((n) << PN_RAMMAP_MPKT_SHIFT) & \
				 PN_RAMMAP_MPKT_MASK)
#घोषणा PN_RAMMAP_RAMIF_SHIFT	14
#घोषणा PN_RAMMAP_RAMIF_MASK	GENMASK(15, PN_RAMMAP_RAMIF_SHIFT)
#घोषणा PN_RAMMAP_RAMIF(n)	(((n) << PN_RAMMAP_RAMIF_SHIFT) & \
				 PN_RAMMAP_RAMIF_MASK)
#घोषणा PN_RAMMAP_BASEAD_MASK	GENMASK(13, 0)
#घोषणा PN_RAMMAP_BASEAD(offs)	(((offs) >> 3) & PN_RAMMAP_BASEAD_MASK)
#घोषणा PN_RAMMAP_DATA(area, ramअगर, basead)	((PN_RAMMAP_##area) | \
						 (PN_RAMMAP_RAMIF(ramअगर)) | \
						 (PN_RAMMAP_BASEAD(basead)))

/* PN_CON */
#घोषणा PN_CON_EN		BIT(31)
#घोषणा PN_CON_DATAIF_EN	BIT(30)
#घोषणा PN_CON_RES_MASK		(BIT(17) | BIT(16))
#घोषणा PN_CON_RES_FORCE_STALL	BIT(17)
#घोषणा PN_CON_RES_NORMAL	BIT(16)
#घोषणा PN_CON_RES_FORCE_NRDY	0
#घोषणा PN_CON_LAST		BIT(11)
#घोषणा PN_CON_RES_WEN		BIT(7)
#घोषणा PN_CON_CLR		BIT(0)

/* PN_INT_STA and PN_INT_ENA */
#घोषणा PN_INT_LSTTR	BIT(4)
#घोषणा PN_INT_BFRDY	BIT(0)

/* USB3_SSIFCMD */
#घोषणा SSIFCMD_URES_U2		BIT(9)
#घोषणा SSIFCMD_URES_U1		BIT(8)
#घोषणा SSIFCMD_Uसूची_U2		BIT(7)
#घोषणा SSIFCMD_Uसूची_U1		BIT(6)
#घोषणा SSIFCMD_UREQ_U2		BIT(5)
#घोषणा SSIFCMD_UREQ_U1		BIT(4)

#घोषणा USB3_EP0_SS_MAX_PACKET_SIZE	512
#घोषणा USB3_EP0_HSFS_MAX_PACKET_SIZE	64
#घोषणा USB3_EP0_BUF_SIZE		8
#घोषणा USB3_MAX_NUM_PIPES		6	/* This includes PIPE 0 */
#घोषणा USB3_WAIT_US			3
#घोषणा USB3_DMA_NUM_SETTING_AREA	4
/*
 * To aव्योम द्विगुन-meaning of "0" (xferred 65536 bytes or received zlp अगर
 * buffer size is 65536), this driver uses the maximum size per a entry is
 * 32768 bytes.
 */
#घोषणा USB3_DMA_MAX_XFER_SIZE		32768
#घोषणा USB3_DMA_PRD_SIZE		4096

काष्ठा renesas_usb3;

/* Physical Region Descriptor Table */
काष्ठा renesas_usb3_prd अणु
	u32 word1;
#घोषणा USB3_PRD1_E		BIT(30)		/* the end of chain */
#घोषणा USB3_PRD1_U		BIT(29)		/* completion of transfer */
#घोषणा USB3_PRD1_D		BIT(28)		/* Error occurred */
#घोषणा USB3_PRD1_INT		BIT(27)		/* Interrupt occurred */
#घोषणा USB3_PRD1_LST		BIT(26)		/* Last Packet */
#घोषणा USB3_PRD1_B_INC		BIT(24)
#घोषणा USB3_PRD1_MPS_8		0
#घोषणा USB3_PRD1_MPS_16	BIT(21)
#घोषणा USB3_PRD1_MPS_32	BIT(22)
#घोषणा USB3_PRD1_MPS_64	(BIT(22) | BIT(21))
#घोषणा USB3_PRD1_MPS_512	BIT(23)
#घोषणा USB3_PRD1_MPS_1024	(BIT(23) | BIT(21))
#घोषणा USB3_PRD1_MPS_RESERVED	(BIT(23) | BIT(22) | BIT(21))
#घोषणा USB3_PRD1_SIZE_MASK	GENMASK(15, 0)

	u32 bap;
पूर्ण;
#घोषणा USB3_DMA_NUM_PRD_ENTRIES	(USB3_DMA_PRD_SIZE / \
					  माप(काष्ठा renesas_usb3_prd))
#घोषणा USB3_DMA_MAX_XFER_SIZE_ALL_PRDS	(USB3_DMA_PRD_SIZE / \
					 माप(काष्ठा renesas_usb3_prd) * \
					 USB3_DMA_MAX_XFER_SIZE)

काष्ठा renesas_usb3_dma अणु
	काष्ठा renesas_usb3_prd *prd;
	dma_addr_t prd_dma;
	पूर्णांक num;	/* Setting area number (from 1 to 4) */
	bool used;
पूर्ण;

काष्ठा renesas_usb3_request अणु
	काष्ठा usb_request	req;
	काष्ठा list_head	queue;
पूर्ण;

#घोषणा USB3_EP_NAME_SIZE	8
काष्ठा renesas_usb3_ep अणु
	काष्ठा usb_ep ep;
	काष्ठा renesas_usb3 *usb3;
	काष्ठा renesas_usb3_dma *dma;
	पूर्णांक num;
	अक्षर ep_name[USB3_EP_NAME_SIZE];
	काष्ठा list_head queue;
	u32 rammap_val;
	bool dir_in;
	bool halt;
	bool wedge;
	bool started;
पूर्ण;

काष्ठा renesas_usb3_priv अणु
	पूर्णांक ramsize_per_ramअगर;		/* unit = bytes */
	पूर्णांक num_ramअगर;
	पूर्णांक ramsize_per_pipe;		/* unit = bytes */
	bool workaround_क्रम_vbus;	/* अगर true, करोn't check vbus संकेत */
पूर्ण;

काष्ठा renesas_usb3 अणु
	व्योम __iomem *reg;

	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *driver;
	काष्ठा extcon_dev *extcon;
	काष्ठा work_काष्ठा extcon_work;
	काष्ठा phy *phy;
	काष्ठा dentry *dentry;

	काष्ठा usb_role_चयन *role_sw;
	काष्ठा device *host_dev;
	काष्ठा work_काष्ठा role_work;
	क्रमागत usb_role role;

	काष्ठा renesas_usb3_ep *usb3_ep;
	पूर्णांक num_usb3_eps;

	काष्ठा renesas_usb3_dma dma[USB3_DMA_NUM_SETTING_AREA];

	spinlock_t lock;
	पूर्णांक disabled_count;

	काष्ठा usb_request *ep0_req;

	क्रमागत usb_role connection_state;
	u16 test_mode;
	u8 ep0_buf[USB3_EP0_BUF_SIZE];
	bool softconnect;
	bool workaround_क्रम_vbus;
	bool extcon_host;		/* check id and set EXTCON_USB_HOST */
	bool extcon_usb;		/* check vbus and set EXTCON_USB */
	bool क्रमced_b_device;
	bool start_to_connect;
	bool role_sw_by_connector;
पूर्ण;

#घोषणा gadget_to_renesas_usb3(_gadget)	\
		container_of(_gadget, काष्ठा renesas_usb3, gadget)
#घोषणा renesas_usb3_to_gadget(renesas_usb3) (&renesas_usb3->gadget)
#घोषणा usb3_to_dev(_usb3)	(_usb3->gadget.dev.parent)

#घोषणा usb_ep_to_usb3_ep(_ep) container_of(_ep, काष्ठा renesas_usb3_ep, ep)
#घोषणा usb3_ep_to_usb3(_usb3_ep) (_usb3_ep->usb3)
#घोषणा usb_req_to_usb3_req(_req) container_of(_req, \
					    काष्ठा renesas_usb3_request, req)

#घोषणा usb3_get_ep(usb3, n) ((usb3)->usb3_ep + (n))
#घोषणा usb3_क्रम_each_ep(usb3_ep, usb3, i)			\
		क्रम ((i) = 0, usb3_ep = usb3_get_ep(usb3, (i));	\
		     (i) < (usb3)->num_usb3_eps;		\
		     (i)++, usb3_ep = usb3_get_ep(usb3, (i)))

#घोषणा usb3_get_dma(usb3, i)	(&(usb3)->dma[i])
#घोषणा usb3_क्रम_each_dma(usb3, dma, i)				\
		क्रम ((i) = 0, dma = usb3_get_dma((usb3), (i));	\
		     (i) < USB3_DMA_NUM_SETTING_AREA;		\
		     (i)++, dma = usb3_get_dma((usb3), (i)))

अटल स्थिर अक्षर udc_name[] = "renesas_usb3";

अटल bool use_dma = 1;
module_param(use_dma, bool, 0644);
MODULE_PARM_DESC(use_dma, "use dedicated DMAC");

अटल व्योम usb3_ग_लिखो(काष्ठा renesas_usb3 *usb3, u32 data, u32 offs)
अणु
	ioग_लिखो32(data, usb3->reg + offs);
पूर्ण

अटल u32 usb3_पढ़ो(काष्ठा renesas_usb3 *usb3, u32 offs)
अणु
	वापस ioपढ़ो32(usb3->reg + offs);
पूर्ण

अटल व्योम usb3_set_bit(काष्ठा renesas_usb3 *usb3, u32 bits, u32 offs)
अणु
	u32 val = usb3_पढ़ो(usb3, offs);

	val |= bits;
	usb3_ग_लिखो(usb3, val, offs);
पूर्ण

अटल व्योम usb3_clear_bit(काष्ठा renesas_usb3 *usb3, u32 bits, u32 offs)
अणु
	u32 val = usb3_पढ़ो(usb3, offs);

	val &= ~bits;
	usb3_ग_लिखो(usb3, val, offs);
पूर्ण

अटल पूर्णांक usb3_रुको(काष्ठा renesas_usb3 *usb3, u32 reg, u32 mask,
		     u32 expected)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < USB3_WAIT_US; i++) अणु
		अगर ((usb3_पढ़ो(usb3, reg) & mask) == expected)
			वापस 0;
		udelay(1);
	पूर्ण

	dev_dbg(usb3_to_dev(usb3), "%s: timed out (%8x, %08x, %08x)\n",
		__func__, reg, mask, expected);

	वापस -EBUSY;
पूर्ण

अटल व्योम renesas_usb3_extcon_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा renesas_usb3 *usb3 = container_of(work, काष्ठा renesas_usb3,
						 extcon_work);

	extcon_set_state_sync(usb3->extcon, EXTCON_USB_HOST, usb3->extcon_host);
	extcon_set_state_sync(usb3->extcon, EXTCON_USB, usb3->extcon_usb);
पूर्ण

अटल व्योम usb3_enable_irq_1(काष्ठा renesas_usb3 *usb3, u32 bits)
अणु
	usb3_set_bit(usb3, bits, USB3_USB_INT_ENA_1);
पूर्ण

अटल व्योम usb3_disable_irq_1(काष्ठा renesas_usb3 *usb3, u32 bits)
अणु
	usb3_clear_bit(usb3, bits, USB3_USB_INT_ENA_1);
पूर्ण

अटल व्योम usb3_enable_pipe_irq(काष्ठा renesas_usb3 *usb3, पूर्णांक num)
अणु
	usb3_set_bit(usb3, USB_INT_2_PIPE(num), USB3_USB_INT_ENA_2);
पूर्ण

अटल व्योम usb3_disable_pipe_irq(काष्ठा renesas_usb3 *usb3, पूर्णांक num)
अणु
	usb3_clear_bit(usb3, USB_INT_2_PIPE(num), USB3_USB_INT_ENA_2);
पूर्ण

अटल bool usb3_is_host(काष्ठा renesas_usb3 *usb3)
अणु
	वापस !(usb3_पढ़ो(usb3, USB3_DRD_CON) & DRD_CON_PERI_CON);
पूर्ण

अटल व्योम usb3_init_axi_bridge(काष्ठा renesas_usb3 *usb3)
अणु
	/* Set AXI_INT */
	usb3_ग_लिखो(usb3, ~0, USB3_DMA_INT_STA);
	usb3_ग_लिखो(usb3, 0, USB3_DMA_INT_ENA);
	usb3_set_bit(usb3, AXI_INT_DMAINT | AXI_INT_EPCINT, USB3_AXI_INT_ENA);
पूर्ण

अटल व्योम usb3_init_epc_रेजिस्टरs(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_ग_लिखो(usb3, ~0, USB3_USB_INT_STA_1);
	अगर (!usb3->workaround_क्रम_vbus)
		usb3_enable_irq_1(usb3, USB_INT_1_VBUS_CNG);
पूर्ण

अटल bool usb3_wakeup_usb2_phy(काष्ठा renesas_usb3 *usb3)
अणु
	अगर (!(usb3_पढ़ो(usb3, USB3_USB20_CON) & USB20_CON_B2_SUSPEND))
		वापस true;	/* alपढ़ोy waked it up */

	usb3_clear_bit(usb3, USB20_CON_B2_SUSPEND, USB3_USB20_CON);
	usb3_enable_irq_1(usb3, USB_INT_1_B2_RSUM);

	वापस false;
पूर्ण

अटल व्योम usb3_usb2_pullup(काष्ठा renesas_usb3 *usb3, पूर्णांक pullup)
अणु
	u32 bits = USB20_CON_B2_PUE | USB20_CON_B2_CONNECT;

	अगर (usb3->softconnect && pullup)
		usb3_set_bit(usb3, bits, USB3_USB20_CON);
	अन्यथा
		usb3_clear_bit(usb3, bits, USB3_USB20_CON);
पूर्ण

अटल व्योम usb3_set_test_mode(काष्ठा renesas_usb3 *usb3)
अणु
	u32 val = usb3_पढ़ो(usb3, USB3_USB20_CON);

	val &= ~USB20_CON_B2_TSTMOD_MASK;
	val |= USB20_CON_B2_TSTMOD(usb3->test_mode);
	usb3_ग_लिखो(usb3, val | USB20_CON_B2_TSTMOD_EN, USB3_USB20_CON);
	अगर (!usb3->test_mode)
		usb3_clear_bit(usb3, USB20_CON_B2_TSTMOD_EN, USB3_USB20_CON);
पूर्ण

अटल व्योम usb3_start_usb2_connection(काष्ठा renesas_usb3 *usb3)
अणु
	usb3->disabled_count++;
	usb3_set_bit(usb3, USB_COM_CON_EP0_EN, USB3_USB_COM_CON);
	usb3_set_bit(usb3, USB_COM_CON_SPD_MODE, USB3_USB_COM_CON);
	usb3_usb2_pullup(usb3, 1);
पूर्ण

अटल पूर्णांक usb3_is_usb3_phy_in_u3(काष्ठा renesas_usb3 *usb3)
अणु
	वापस usb3_पढ़ो(usb3, USB3_USB30_CON) & USB30_CON_POW_SEL_IN_U3;
पूर्ण

अटल bool usb3_wakeup_usb3_phy(काष्ठा renesas_usb3 *usb3)
अणु
	अगर (!usb3_is_usb3_phy_in_u3(usb3))
		वापस true;	/* alपढ़ोy waked it up */

	usb3_set_bit(usb3, USB30_CON_B3_PLLWAKE, USB3_USB30_CON);
	usb3_enable_irq_1(usb3, USB_INT_1_B3_PLLWKUP);

	वापस false;
पूर्ण

अटल u16 usb3_feature_get_un_enabled(काष्ठा renesas_usb3 *usb3)
अणु
	u32 mask_u2 = SSIFCMD_Uसूची_U2 | SSIFCMD_UREQ_U2;
	u32 mask_u1 = SSIFCMD_Uसूची_U1 | SSIFCMD_UREQ_U1;
	u32 val = usb3_पढ़ो(usb3, USB3_SSIFCMD);
	u16 ret = 0;

	/* Enables अणुU2,U1पूर्ण अगर the bits of Uसूची and UREQ are set to 0 */
	अगर (!(val & mask_u2))
		ret |= 1 << USB_DEV_STAT_U2_ENABLED;
	अगर (!(val & mask_u1))
		ret |= 1 << USB_DEV_STAT_U1_ENABLED;

	वापस ret;
पूर्ण

अटल व्योम usb3_feature_u2_enable(काष्ठा renesas_usb3 *usb3, bool enable)
अणु
	u32 bits = SSIFCMD_Uसूची_U2 | SSIFCMD_UREQ_U2;

	/* Enables U2 अगर the bits of Uसूची and UREQ are set to 0 */
	अगर (enable)
		usb3_clear_bit(usb3, bits, USB3_SSIFCMD);
	अन्यथा
		usb3_set_bit(usb3, bits, USB3_SSIFCMD);
पूर्ण

अटल व्योम usb3_feature_u1_enable(काष्ठा renesas_usb3 *usb3, bool enable)
अणु
	u32 bits = SSIFCMD_Uसूची_U1 | SSIFCMD_UREQ_U1;

	/* Enables U1 अगर the bits of Uसूची and UREQ are set to 0 */
	अगर (enable)
		usb3_clear_bit(usb3, bits, USB3_SSIFCMD);
	अन्यथा
		usb3_set_bit(usb3, bits, USB3_SSIFCMD);
पूर्ण

अटल व्योम usb3_start_operation_क्रम_usb3(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_bit(usb3, USB_COM_CON_EP0_EN, USB3_USB_COM_CON);
	usb3_clear_bit(usb3, USB_COM_CON_SPD_MODE, USB3_USB_COM_CON);
	usb3_set_bit(usb3, USB30_CON_B3_CONNECT, USB3_USB30_CON);
पूर्ण

अटल व्योम usb3_start_usb3_connection(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_start_operation_क्रम_usb3(usb3);
	usb3_set_bit(usb3, USB_COM_CON_RX_DETECTION, USB3_USB_COM_CON);

	usb3_enable_irq_1(usb3, USB_INT_1_B3_LUPSUCS | USB_INT_1_B3_DISABLE |
			  USB_INT_1_SPEED);
पूर्ण

अटल व्योम usb3_stop_usb3_connection(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_clear_bit(usb3, USB30_CON_B3_CONNECT, USB3_USB30_CON);
पूर्ण

अटल व्योम usb3_transition_to_शेष_state(काष्ठा renesas_usb3 *usb3,
					     bool is_usb3)
अणु
	usb3_set_bit(usb3, USB_INT_2_PIPE(0), USB3_USB_INT_ENA_2);
	usb3_ग_लिखो(usb3, P0_INT_ALL_BITS, USB3_P0_INT_STA);
	usb3_set_bit(usb3, P0_INT_ALL_BITS, USB3_P0_INT_ENA);

	अगर (is_usb3)
		usb3_enable_irq_1(usb3, USB_INT_1_B3_WRMRST |
				  USB_INT_1_B3_HOTRST);
	अन्यथा
		usb3_enable_irq_1(usb3, USB_INT_1_B2_SPND |
				  USB_INT_1_B2_L1SPND | USB_INT_1_B2_USBRST);
पूर्ण

अटल व्योम usb3_connect(काष्ठा renesas_usb3 *usb3)
अणु
	अगर (usb3_wakeup_usb3_phy(usb3))
		usb3_start_usb3_connection(usb3);
पूर्ण

अटल व्योम usb3_reset_epc(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_clear_bit(usb3, USB_COM_CON_CONF, USB3_USB_COM_CON);
	usb3_clear_bit(usb3, USB_COM_CON_EP0_EN, USB3_USB_COM_CON);
	usb3_set_bit(usb3, USB_COM_CON_PIPE_CLR, USB3_USB_COM_CON);
	usb3->test_mode = 0;
	usb3_set_test_mode(usb3);
पूर्ण

अटल व्योम usb3_disconnect(काष्ठा renesas_usb3 *usb3)
अणु
	usb3->disabled_count = 0;
	usb3_usb2_pullup(usb3, 0);
	usb3_clear_bit(usb3, USB30_CON_B3_CONNECT, USB3_USB30_CON);
	usb3_reset_epc(usb3);
	usb3_disable_irq_1(usb3, USB_INT_1_B2_RSUM | USB_INT_1_B3_PLLWKUP |
			   USB_INT_1_B3_LUPSUCS | USB_INT_1_B3_DISABLE |
			   USB_INT_1_SPEED | USB_INT_1_B3_WRMRST |
			   USB_INT_1_B3_HOTRST | USB_INT_1_B2_SPND |
			   USB_INT_1_B2_L1SPND | USB_INT_1_B2_USBRST);
	usb3_clear_bit(usb3, USB_COM_CON_SPD_MODE, USB3_USB_COM_CON);
	usb3_init_epc_रेजिस्टरs(usb3);

	अगर (usb3->driver)
		usb3->driver->disconnect(&usb3->gadget);
पूर्ण

अटल व्योम usb3_check_vbus(काष्ठा renesas_usb3 *usb3)
अणु
	अगर (usb3->workaround_क्रम_vbus) अणु
		usb3_connect(usb3);
	पूर्ण अन्यथा अणु
		usb3->extcon_usb = !!(usb3_पढ़ो(usb3, USB3_USB_STA) &
							USB_STA_VBUS_STA);
		अगर (usb3->extcon_usb)
			usb3_connect(usb3);
		अन्यथा
			usb3_disconnect(usb3);

		schedule_work(&usb3->extcon_work);
	पूर्ण
पूर्ण

अटल व्योम renesas_usb3_role_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा renesas_usb3 *usb3 =
			container_of(work, काष्ठा renesas_usb3, role_work);

	usb_role_चयन_set_role(usb3->role_sw, usb3->role);
पूर्ण

अटल व्योम usb3_set_mode(काष्ठा renesas_usb3 *usb3, bool host)
अणु
	अगर (host)
		usb3_clear_bit(usb3, DRD_CON_PERI_CON, USB3_DRD_CON);
	अन्यथा
		usb3_set_bit(usb3, DRD_CON_PERI_CON, USB3_DRD_CON);
पूर्ण

अटल व्योम usb3_set_mode_by_role_sw(काष्ठा renesas_usb3 *usb3, bool host)
अणु
	अगर (usb3->role_sw) अणु
		usb3->role = host ? USB_ROLE_HOST : USB_ROLE_DEVICE;
		schedule_work(&usb3->role_work);
	पूर्ण अन्यथा अणु
		usb3_set_mode(usb3, host);
	पूर्ण
पूर्ण

अटल व्योम usb3_vbus_out(काष्ठा renesas_usb3 *usb3, bool enable)
अणु
	अगर (enable)
		usb3_set_bit(usb3, DRD_CON_VBOUT, USB3_DRD_CON);
	अन्यथा
		usb3_clear_bit(usb3, DRD_CON_VBOUT, USB3_DRD_CON);
पूर्ण

अटल व्योम usb3_mode_config(काष्ठा renesas_usb3 *usb3, bool host, bool a_dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usb3->lock, flags);
	अगर (!usb3->role_sw_by_connector ||
	    usb3->connection_state != USB_ROLE_NONE) अणु
		usb3_set_mode_by_role_sw(usb3, host);
		usb3_vbus_out(usb3, a_dev);
	पूर्ण
	/* क्रम A-Peripheral or क्रमced B-device mode */
	अगर ((!host && a_dev) || usb3->start_to_connect)
		usb3_connect(usb3);
	spin_unlock_irqrestore(&usb3->lock, flags);
पूर्ण

अटल bool usb3_is_a_device(काष्ठा renesas_usb3 *usb3)
अणु
	वापस !(usb3_पढ़ो(usb3, USB3_USB_OTG_STA) & USB_OTG_IDMON);
पूर्ण

अटल व्योम usb3_check_id(काष्ठा renesas_usb3 *usb3)
अणु
	usb3->extcon_host = usb3_is_a_device(usb3);

	अगर ((!usb3->role_sw_by_connector && usb3->extcon_host &&
	     !usb3->क्रमced_b_device) || usb3->connection_state == USB_ROLE_HOST)
		usb3_mode_config(usb3, true, true);
	अन्यथा
		usb3_mode_config(usb3, false, false);

	schedule_work(&usb3->extcon_work);
पूर्ण

अटल व्योम renesas_usb3_init_controller(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_init_axi_bridge(usb3);
	usb3_init_epc_रेजिस्टरs(usb3);
	usb3_set_bit(usb3, USB_COM_CON_PN_WDATAIF_NL |
		     USB_COM_CON_PN_RDATAIF_NL | USB_COM_CON_PN_LSTTR_PP,
		     USB3_USB_COM_CON);
	usb3_ग_लिखो(usb3, USB_OTG_IDMON, USB3_USB_OTG_INT_STA);
	usb3_ग_लिखो(usb3, USB_OTG_IDMON, USB3_USB_OTG_INT_ENA);

	usb3_check_id(usb3);
	usb3_check_vbus(usb3);
पूर्ण

अटल व्योम renesas_usb3_stop_controller(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_disconnect(usb3);
	usb3_ग_लिखो(usb3, 0, USB3_P0_INT_ENA);
	usb3_ग_लिखो(usb3, 0, USB3_USB_OTG_INT_ENA);
	usb3_ग_लिखो(usb3, 0, USB3_USB_INT_ENA_1);
	usb3_ग_लिखो(usb3, 0, USB3_USB_INT_ENA_2);
	usb3_ग_लिखो(usb3, 0, USB3_AXI_INT_ENA);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_pll_wakeup(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_disable_irq_1(usb3, USB_INT_1_B3_PLLWKUP);
	usb3_clear_bit(usb3, USB30_CON_B3_PLLWAKE, USB3_USB30_CON);
	usb3_start_usb3_connection(usb3);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_linkup_success(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_transition_to_शेष_state(usb3, true);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_resume(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_disable_irq_1(usb3, USB_INT_1_B2_RSUM);
	usb3_start_usb2_connection(usb3);
	usb3_transition_to_शेष_state(usb3, false);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_suspend(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_disable_irq_1(usb3, USB_INT_1_B2_SPND);

	अगर (usb3->gadget.speed != USB_SPEED_UNKNOWN &&
	    usb3->gadget.state != USB_STATE_NOTATTACHED) अणु
		अगर (usb3->driver && usb3->driver->suspend)
			usb3->driver->suspend(&usb3->gadget);
		usb_gadget_set_state(&usb3->gadget, USB_STATE_SUSPENDED);
	पूर्ण
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_disable(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_stop_usb3_connection(usb3);
	अगर (usb3_wakeup_usb2_phy(usb3))
		usb3_irq_epc_पूर्णांक_1_resume(usb3);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_bus_reset(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_reset_epc(usb3);
	अगर (usb3->disabled_count < 3)
		usb3_start_usb3_connection(usb3);
	अन्यथा
		usb3_start_usb2_connection(usb3);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_vbus_change(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_check_vbus(usb3);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_hot_reset(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_reset_epc(usb3);
	usb3_set_bit(usb3, USB_COM_CON_EP0_EN, USB3_USB_COM_CON);

	/* This bit shall be set within 12ms from the start of HotReset */
	usb3_set_bit(usb3, USB30_CON_B3_HOTRST_CMP, USB3_USB30_CON);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_warm_reset(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_reset_epc(usb3);
	usb3_set_bit(usb3, USB_COM_CON_EP0_EN, USB3_USB_COM_CON);

	usb3_start_operation_क्रम_usb3(usb3);
	usb3_enable_irq_1(usb3, USB_INT_1_SPEED);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1_speed(काष्ठा renesas_usb3 *usb3)
अणु
	u32 speed = usb3_पढ़ो(usb3, USB3_USB_STA) & USB_STA_SPEED_MASK;

	चयन (speed) अणु
	हाल USB_STA_SPEED_SS:
		usb3->gadget.speed = USB_SPEED_SUPER;
		usb3->gadget.ep0->maxpacket = USB3_EP0_SS_MAX_PACKET_SIZE;
		अवरोध;
	हाल USB_STA_SPEED_HS:
		usb3->gadget.speed = USB_SPEED_HIGH;
		usb3->gadget.ep0->maxpacket = USB3_EP0_HSFS_MAX_PACKET_SIZE;
		अवरोध;
	हाल USB_STA_SPEED_FS:
		usb3->gadget.speed = USB_SPEED_FULL;
		usb3->gadget.ep0->maxpacket = USB3_EP0_HSFS_MAX_PACKET_SIZE;
		अवरोध;
	शेष:
		usb3->gadget.speed = USB_SPEED_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_1(काष्ठा renesas_usb3 *usb3, u32 पूर्णांक_sta_1)
अणु
	अगर (पूर्णांक_sta_1 & USB_INT_1_B3_PLLWKUP)
		usb3_irq_epc_पूर्णांक_1_pll_wakeup(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_B3_LUPSUCS)
		usb3_irq_epc_पूर्णांक_1_linkup_success(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_B3_HOTRST)
		usb3_irq_epc_पूर्णांक_1_hot_reset(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_B3_WRMRST)
		usb3_irq_epc_पूर्णांक_1_warm_reset(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_B3_DISABLE)
		usb3_irq_epc_पूर्णांक_1_disable(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_B2_USBRST)
		usb3_irq_epc_पूर्णांक_1_bus_reset(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_B2_RSUM)
		usb3_irq_epc_पूर्णांक_1_resume(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_B2_SPND)
		usb3_irq_epc_पूर्णांक_1_suspend(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_SPEED)
		usb3_irq_epc_पूर्णांक_1_speed(usb3);

	अगर (पूर्णांक_sta_1 & USB_INT_1_VBUS_CNG)
		usb3_irq_epc_पूर्णांक_1_vbus_change(usb3);
पूर्ण

अटल काष्ठा renesas_usb3_request *__usb3_get_request(काष्ठा renesas_usb3_ep
						       *usb3_ep)
अणु
	वापस list_first_entry_or_null(&usb3_ep->queue,
					काष्ठा renesas_usb3_request, queue);
पूर्ण

अटल काष्ठा renesas_usb3_request *usb3_get_request(काष्ठा renesas_usb3_ep
						     *usb3_ep)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	काष्ठा renesas_usb3_request *usb3_req;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usb3->lock, flags);
	usb3_req = __usb3_get_request(usb3_ep);
	spin_unlock_irqrestore(&usb3->lock, flags);

	वापस usb3_req;
पूर्ण

अटल व्योम __usb3_request_करोne(काष्ठा renesas_usb3_ep *usb3_ep,
				काष्ठा renesas_usb3_request *usb3_req,
				पूर्णांक status)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	dev_dbg(usb3_to_dev(usb3), "giveback: ep%2d, %u, %u, %d\n",
		usb3_ep->num, usb3_req->req.length, usb3_req->req.actual,
		status);
	usb3_req->req.status = status;
	usb3_ep->started = false;
	list_del_init(&usb3_req->queue);
	spin_unlock(&usb3->lock);
	usb_gadget_giveback_request(&usb3_ep->ep, &usb3_req->req);
	spin_lock(&usb3->lock);
पूर्ण

अटल व्योम usb3_request_करोne(काष्ठा renesas_usb3_ep *usb3_ep,
			      काष्ठा renesas_usb3_request *usb3_req, पूर्णांक status)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usb3->lock, flags);
	__usb3_request_करोne(usb3_ep, usb3_req, status);
	spin_unlock_irqrestore(&usb3->lock, flags);
पूर्ण

अटल व्योम usb3_irq_epc_pipe0_status_end(काष्ठा renesas_usb3 *usb3)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, 0);
	काष्ठा renesas_usb3_request *usb3_req = usb3_get_request(usb3_ep);

	अगर (usb3_req)
		usb3_request_करोne(usb3_ep, usb3_req, 0);
	अगर (usb3->test_mode)
		usb3_set_test_mode(usb3);
पूर्ण

अटल व्योम usb3_get_setup_data(काष्ठा renesas_usb3 *usb3,
				काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, 0);
	u32 *data = (u32 *)ctrl;

	*data++ = usb3_पढ़ो(usb3, USB3_STUP_DAT_0);
	*data = usb3_पढ़ो(usb3, USB3_STUP_DAT_1);

	/* update this driver's flag */
	usb3_ep->dir_in = !!(ctrl->bRequestType & USB_सूची_IN);
पूर्ण

अटल व्योम usb3_set_p0_con_update_res(काष्ठा renesas_usb3 *usb3, u32 res)
अणु
	u32 val = usb3_पढ़ो(usb3, USB3_P0_CON);

	val &= ~(P0_CON_ST_RES_MASK | P0_CON_OT_RES_MASK | P0_CON_IN_RES_MASK);
	val |= res | P0_CON_RES_WEN;
	usb3_ग_लिखो(usb3, val, USB3_P0_CON);
पूर्ण

अटल व्योम usb3_set_p0_con_क्रम_ctrl_पढ़ो_data(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_p0_con_update_res(usb3, P0_CON_ST_RES_FORCE_NRDY |
				   P0_CON_OT_RES_FORCE_STALL |
				   P0_CON_IN_RES_NORMAL);
पूर्ण

अटल व्योम usb3_set_p0_con_क्रम_ctrl_पढ़ो_status(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_p0_con_update_res(usb3, P0_CON_ST_RES_NORMAL |
				   P0_CON_OT_RES_FORCE_STALL |
				   P0_CON_IN_RES_NORMAL);
पूर्ण

अटल व्योम usb3_set_p0_con_क्रम_ctrl_ग_लिखो_data(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_p0_con_update_res(usb3, P0_CON_ST_RES_FORCE_NRDY |
				   P0_CON_OT_RES_NORMAL |
				   P0_CON_IN_RES_FORCE_STALL);
पूर्ण

अटल व्योम usb3_set_p0_con_क्रम_ctrl_ग_लिखो_status(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_p0_con_update_res(usb3, P0_CON_ST_RES_NORMAL |
				   P0_CON_OT_RES_NORMAL |
				   P0_CON_IN_RES_FORCE_STALL);
पूर्ण

अटल व्योम usb3_set_p0_con_क्रम_no_data(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_p0_con_update_res(usb3, P0_CON_ST_RES_NORMAL |
				   P0_CON_OT_RES_FORCE_STALL |
				   P0_CON_IN_RES_FORCE_STALL);
पूर्ण

अटल व्योम usb3_set_p0_con_stall(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_p0_con_update_res(usb3, P0_CON_ST_RES_FORCE_STALL |
				   P0_CON_OT_RES_FORCE_STALL |
				   P0_CON_IN_RES_FORCE_STALL);
पूर्ण

अटल व्योम usb3_set_p0_con_stop(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_p0_con_update_res(usb3, P0_CON_ST_RES_FORCE_NRDY |
				   P0_CON_OT_RES_FORCE_NRDY |
				   P0_CON_IN_RES_FORCE_NRDY);
पूर्ण

अटल पूर्णांक usb3_pn_change(काष्ठा renesas_usb3 *usb3, पूर्णांक num)
अणु
	अगर (num == 0 || num > usb3->num_usb3_eps)
		वापस -ENXIO;

	usb3_ग_लिखो(usb3, num, USB3_PIPE_COM);

	वापस 0;
पूर्ण

अटल व्योम usb3_set_pn_con_update_res(काष्ठा renesas_usb3 *usb3, u32 res)
अणु
	u32 val = usb3_पढ़ो(usb3, USB3_PN_CON);

	val &= ~PN_CON_RES_MASK;
	val |= res & PN_CON_RES_MASK;
	val |= PN_CON_RES_WEN;
	usb3_ग_लिखो(usb3, val, USB3_PN_CON);
पूर्ण

अटल व्योम usb3_pn_start(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_pn_con_update_res(usb3, PN_CON_RES_NORMAL);
पूर्ण

अटल व्योम usb3_pn_stop(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_pn_con_update_res(usb3, PN_CON_RES_FORCE_NRDY);
पूर्ण

अटल व्योम usb3_pn_stall(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_pn_con_update_res(usb3, PN_CON_RES_FORCE_STALL);
पूर्ण

अटल पूर्णांक usb3_pn_con_clear(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_bit(usb3, PN_CON_CLR, USB3_PN_CON);

	वापस usb3_रुको(usb3, USB3_PN_CON, PN_CON_CLR, 0);
पूर्ण

अटल bool usb3_is_transfer_complete(काष्ठा renesas_usb3_ep *usb3_ep,
				      काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा usb_request *req = &usb3_req->req;

	अगर ((!req->zero && req->actual == req->length) ||
	    (req->actual % usb3_ep->ep.maxpacket) || (req->length == 0))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक usb3_रुको_pipe_status(काष्ठा renesas_usb3_ep *usb3_ep, u32 mask)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 sta_reg = usb3_ep->num ? USB3_PN_STA : USB3_P0_STA;

	वापस usb3_रुको(usb3, sta_reg, mask, mask);
पूर्ण

अटल व्योम usb3_set_px_con_send(काष्ठा renesas_usb3_ep *usb3_ep, पूर्णांक bytes,
				 bool last)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 con_reg = usb3_ep->num ? USB3_PN_CON : USB3_P0_CON;
	u32 val = usb3_पढ़ो(usb3, con_reg);

	val |= PX_CON_SEND | PX_CON_BYTE_EN_BYTES(bytes);
	val |= (usb3_ep->num && last) ? PN_CON_LAST : 0;
	usb3_ग_लिखो(usb3, val, con_reg);
पूर्ण

अटल पूर्णांक usb3_ग_लिखो_pipe(काष्ठा renesas_usb3_ep *usb3_ep,
			   काष्ठा renesas_usb3_request *usb3_req,
			   u32 fअगरo_reg)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	पूर्णांक i;
	पूर्णांक len = min_t(अचिन्हित, usb3_req->req.length - usb3_req->req.actual,
			usb3_ep->ep.maxpacket);
	u8 *buf = usb3_req->req.buf + usb3_req->req.actual;
	u32 पंचांगp = 0;
	bool is_last = !len ? true : false;

	अगर (usb3_रुको_pipe_status(usb3_ep, PX_STA_BUFSTS) < 0)
		वापस -EBUSY;

	/* Update gadget driver parameter */
	usb3_req->req.actual += len;

	/* Write data to the रेजिस्टर */
	अगर (len >= 4) अणु
		ioग_लिखो32_rep(usb3->reg + fअगरo_reg, buf, len / 4);
		buf += (len / 4) * 4;
		len %= 4;	/* update len to use usb3_set_pX_con_send() */
	पूर्ण

	अगर (len) अणु
		क्रम (i = 0; i < len; i++)
			पंचांगp |= buf[i] << (8 * i);
		usb3_ग_लिखो(usb3, पंचांगp, fअगरo_reg);
	पूर्ण

	अगर (!is_last)
		is_last = usb3_is_transfer_complete(usb3_ep, usb3_req);
	/* Send the data */
	usb3_set_px_con_send(usb3_ep, len, is_last);

	वापस is_last ? 0 : -EAGAIN;
पूर्ण

अटल u32 usb3_get_received_length(काष्ठा renesas_usb3_ep *usb3_ep)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 lng_reg = usb3_ep->num ? USB3_PN_LNG : USB3_P0_LNG;

	वापस usb3_पढ़ो(usb3, lng_reg);
पूर्ण

अटल पूर्णांक usb3_पढ़ो_pipe(काष्ठा renesas_usb3_ep *usb3_ep,
			  काष्ठा renesas_usb3_request *usb3_req, u32 fअगरo_reg)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	पूर्णांक i;
	पूर्णांक len = min_t(अचिन्हित, usb3_req->req.length - usb3_req->req.actual,
			usb3_get_received_length(usb3_ep));
	u8 *buf = usb3_req->req.buf + usb3_req->req.actual;
	u32 पंचांगp = 0;

	अगर (!len)
		वापस 0;

	/* Update gadget driver parameter */
	usb3_req->req.actual += len;

	/* Read data from the रेजिस्टर */
	अगर (len >= 4) अणु
		ioपढ़ो32_rep(usb3->reg + fअगरo_reg, buf, len / 4);
		buf += (len / 4) * 4;
		len %= 4;
	पूर्ण

	अगर (len) अणु
		पंचांगp = usb3_पढ़ो(usb3, fअगरo_reg);
		क्रम (i = 0; i < len; i++)
			buf[i] = (पंचांगp >> (8 * i)) & 0xff;
	पूर्ण

	वापस usb3_is_transfer_complete(usb3_ep, usb3_req) ? 0 : -EAGAIN;
पूर्ण

अटल व्योम usb3_set_status_stage(काष्ठा renesas_usb3_ep *usb3_ep,
				  काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	अगर (usb3_ep->dir_in) अणु
		usb3_set_p0_con_क्रम_ctrl_पढ़ो_status(usb3);
	पूर्ण अन्यथा अणु
		अगर (!usb3_req->req.length)
			usb3_set_p0_con_क्रम_no_data(usb3);
		अन्यथा
			usb3_set_p0_con_क्रम_ctrl_ग_लिखो_status(usb3);
	पूर्ण
पूर्ण

अटल व्योम usb3_p0_xfer(काष्ठा renesas_usb3_ep *usb3_ep,
			 काष्ठा renesas_usb3_request *usb3_req)
अणु
	पूर्णांक ret;

	अगर (usb3_ep->dir_in)
		ret = usb3_ग_लिखो_pipe(usb3_ep, usb3_req, USB3_P0_WRITE);
	अन्यथा
		ret = usb3_पढ़ो_pipe(usb3_ep, usb3_req, USB3_P0_READ);

	अगर (!ret)
		usb3_set_status_stage(usb3_ep, usb3_req);
पूर्ण

अटल व्योम usb3_start_pipe0(काष्ठा renesas_usb3_ep *usb3_ep,
			     काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	अगर (usb3_ep->started)
		वापस;

	usb3_ep->started = true;

	अगर (usb3_ep->dir_in) अणु
		usb3_set_bit(usb3, P0_MOD_सूची, USB3_P0_MOD);
		usb3_set_p0_con_क्रम_ctrl_पढ़ो_data(usb3);
	पूर्ण अन्यथा अणु
		usb3_clear_bit(usb3, P0_MOD_सूची, USB3_P0_MOD);
		अगर (usb3_req->req.length)
			usb3_set_p0_con_क्रम_ctrl_ग_लिखो_data(usb3);
	पूर्ण

	usb3_p0_xfer(usb3_ep, usb3_req);
पूर्ण

अटल व्योम usb3_enable_dma_pipen(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_bit(usb3, PN_CON_DATAIF_EN, USB3_PN_CON);
पूर्ण

अटल व्योम usb3_disable_dma_pipen(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_clear_bit(usb3, PN_CON_DATAIF_EN, USB3_PN_CON);
पूर्ण

अटल व्योम usb3_enable_dma_irq(काष्ठा renesas_usb3 *usb3, पूर्णांक num)
अणु
	usb3_set_bit(usb3, DMA_INT(num), USB3_DMA_INT_ENA);
पूर्ण

अटल व्योम usb3_disable_dma_irq(काष्ठा renesas_usb3 *usb3, पूर्णांक num)
अणु
	usb3_clear_bit(usb3, DMA_INT(num), USB3_DMA_INT_ENA);
पूर्ण

अटल u32 usb3_dma_mps_to_prd_word1(काष्ठा renesas_usb3_ep *usb3_ep)
अणु
	चयन (usb3_ep->ep.maxpacket) अणु
	हाल 8:
		वापस USB3_PRD1_MPS_8;
	हाल 16:
		वापस USB3_PRD1_MPS_16;
	हाल 32:
		वापस USB3_PRD1_MPS_32;
	हाल 64:
		वापस USB3_PRD1_MPS_64;
	हाल 512:
		वापस USB3_PRD1_MPS_512;
	हाल 1024:
		वापस USB3_PRD1_MPS_1024;
	शेष:
		वापस USB3_PRD1_MPS_RESERVED;
	पूर्ण
पूर्ण

अटल bool usb3_dma_get_setting_area(काष्ठा renesas_usb3_ep *usb3_ep,
				      काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	काष्ठा renesas_usb3_dma *dma;
	पूर्णांक i;
	bool ret = false;

	अगर (usb3_req->req.length > USB3_DMA_MAX_XFER_SIZE_ALL_PRDS) अणु
		dev_dbg(usb3_to_dev(usb3), "%s: the length is too big (%d)\n",
			__func__, usb3_req->req.length);
		वापस false;
	पूर्ण

	/* The driver करोesn't handle zero-length packet via dmac */
	अगर (!usb3_req->req.length)
		वापस false;

	अगर (usb3_dma_mps_to_prd_word1(usb3_ep) == USB3_PRD1_MPS_RESERVED)
		वापस false;

	usb3_क्रम_each_dma(usb3, dma, i) अणु
		अगर (dma->used)
			जारी;

		अगर (usb_gadget_map_request(&usb3->gadget, &usb3_req->req,
					   usb3_ep->dir_in) < 0)
			अवरोध;

		dma->used = true;
		usb3_ep->dma = dma;
		ret = true;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम usb3_dma_put_setting_area(काष्ठा renesas_usb3_ep *usb3_ep,
				      काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	पूर्णांक i;
	काष्ठा renesas_usb3_dma *dma;

	usb3_क्रम_each_dma(usb3, dma, i) अणु
		अगर (usb3_ep->dma == dma) अणु
			usb_gadget_unmap_request(&usb3->gadget, &usb3_req->req,
						 usb3_ep->dir_in);
			dma->used = false;
			usb3_ep->dma = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usb3_dma_fill_prd(काष्ठा renesas_usb3_ep *usb3_ep,
			      काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3_prd *cur_prd = usb3_ep->dma->prd;
	u32 reमुख्य = usb3_req->req.length;
	u32 dma = usb3_req->req.dma;
	u32 len;
	पूर्णांक i = 0;

	करो अणु
		len = min_t(u32, reमुख्य, USB3_DMA_MAX_XFER_SIZE) &
			    USB3_PRD1_SIZE_MASK;
		cur_prd->word1 = usb3_dma_mps_to_prd_word1(usb3_ep) |
				 USB3_PRD1_B_INC | len;
		cur_prd->bap = dma;
		reमुख्य -= len;
		dma += len;
		अगर (!reमुख्य || (i + 1) < USB3_DMA_NUM_PRD_ENTRIES)
			अवरोध;

		cur_prd++;
		i++;
	पूर्ण जबतक (1);

	cur_prd->word1 |= USB3_PRD1_E | USB3_PRD1_INT;
	अगर (usb3_ep->dir_in)
		cur_prd->word1 |= USB3_PRD1_LST;
पूर्ण

अटल व्योम usb3_dma_kick_prd(काष्ठा renesas_usb3_ep *usb3_ep)
अणु
	काष्ठा renesas_usb3_dma *dma = usb3_ep->dma;
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 dma_con = DMA_COM_PIPE_NO(usb3_ep->num) | DMA_CON_PRD_EN;

	अगर (usb3_ep->dir_in)
		dma_con |= DMA_CON_PIPE_सूची;

	wmb();	/* prd entries should be in प्रणाली memory here */

	usb3_ग_लिखो(usb3, 1 << usb3_ep->num, USB3_DMA_INT_STA);
	usb3_ग_लिखो(usb3, AXI_INT_PRDEN_CLR_STA(dma->num) |
		   AXI_INT_PRDERR_STA(dma->num), USB3_AXI_INT_STA);

	usb3_ग_लिखो(usb3, dma->prd_dma, USB3_DMA_CH0_PRD_ADR(dma->num));
	usb3_ग_लिखो(usb3, dma_con, USB3_DMA_CH0_CON(dma->num));
	usb3_enable_dma_irq(usb3, usb3_ep->num);
पूर्ण

अटल व्योम usb3_dma_stop_prd(काष्ठा renesas_usb3_ep *usb3_ep)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	काष्ठा renesas_usb3_dma *dma = usb3_ep->dma;

	usb3_disable_dma_irq(usb3, usb3_ep->num);
	usb3_ग_लिखो(usb3, 0, USB3_DMA_CH0_CON(dma->num));
पूर्ण

अटल पूर्णांक usb3_dma_update_status(काष्ठा renesas_usb3_ep *usb3_ep,
				  काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3_prd *cur_prd = usb3_ep->dma->prd;
	काष्ठा usb_request *req = &usb3_req->req;
	u32 reमुख्य, len;
	पूर्णांक i = 0;
	पूर्णांक status = 0;

	rmb();	/* The controller updated prd entries */

	करो अणु
		अगर (cur_prd->word1 & USB3_PRD1_D)
			status = -EIO;
		अगर (cur_prd->word1 & USB3_PRD1_E)
			len = req->length % USB3_DMA_MAX_XFER_SIZE;
		अन्यथा
			len = USB3_DMA_MAX_XFER_SIZE;
		reमुख्य = cur_prd->word1 & USB3_PRD1_SIZE_MASK;
		req->actual += len - reमुख्य;

		अगर (cur_prd->word1 & USB3_PRD1_E ||
		    (i + 1) < USB3_DMA_NUM_PRD_ENTRIES)
			अवरोध;

		cur_prd++;
		i++;
	पूर्ण जबतक (1);

	वापस status;
पूर्ण

अटल bool usb3_dma_try_start(काष्ठा renesas_usb3_ep *usb3_ep,
			       काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	अगर (!use_dma)
		वापस false;

	अगर (usb3_dma_get_setting_area(usb3_ep, usb3_req)) अणु
		usb3_pn_stop(usb3);
		usb3_enable_dma_pipen(usb3);
		usb3_dma_fill_prd(usb3_ep, usb3_req);
		usb3_dma_kick_prd(usb3_ep);
		usb3_pn_start(usb3);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक usb3_dma_try_stop(काष्ठा renesas_usb3_ep *usb3_ep,
			     काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	अचिन्हित दीर्घ flags;
	पूर्णांक status = 0;

	spin_lock_irqsave(&usb3->lock, flags);
	अगर (!usb3_ep->dma)
		जाओ out;

	अगर (!usb3_pn_change(usb3, usb3_ep->num))
		usb3_disable_dma_pipen(usb3);
	usb3_dma_stop_prd(usb3_ep);
	status = usb3_dma_update_status(usb3_ep, usb3_req);
	usb3_dma_put_setting_area(usb3_ep, usb3_req);

out:
	spin_unlock_irqrestore(&usb3->lock, flags);
	वापस status;
पूर्ण

अटल पूर्णांक renesas_usb3_dma_मुक्त_prd(काष्ठा renesas_usb3 *usb3,
				     काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा renesas_usb3_dma *dma;

	usb3_क्रम_each_dma(usb3, dma, i) अणु
		अगर (dma->prd) अणु
			dma_मुक्त_coherent(dev, USB3_DMA_PRD_SIZE,
					  dma->prd, dma->prd_dma);
			dma->prd = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_usb3_dma_alloc_prd(काष्ठा renesas_usb3 *usb3,
				      काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा renesas_usb3_dma *dma;

	अगर (!use_dma)
		वापस 0;

	usb3_क्रम_each_dma(usb3, dma, i) अणु
		dma->prd = dma_alloc_coherent(dev, USB3_DMA_PRD_SIZE,
					      &dma->prd_dma, GFP_KERNEL);
		अगर (!dma->prd) अणु
			renesas_usb3_dma_मुक्त_prd(usb3, dev);
			वापस -ENOMEM;
		पूर्ण
		dma->num = i + 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usb3_start_pipen(काष्ठा renesas_usb3_ep *usb3_ep,
			     काष्ठा renesas_usb3_request *usb3_req)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	काष्ठा renesas_usb3_request *usb3_req_first;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EAGAIN;
	u32 enable_bits = 0;

	spin_lock_irqsave(&usb3->lock, flags);
	अगर (usb3_ep->halt || usb3_ep->started)
		जाओ out;
	usb3_req_first = __usb3_get_request(usb3_ep);
	अगर (!usb3_req_first || usb3_req != usb3_req_first)
		जाओ out;

	अगर (usb3_pn_change(usb3, usb3_ep->num) < 0)
		जाओ out;

	usb3_ep->started = true;

	अगर (usb3_dma_try_start(usb3_ep, usb3_req))
		जाओ out;

	usb3_pn_start(usb3);

	अगर (usb3_ep->dir_in) अणु
		ret = usb3_ग_लिखो_pipe(usb3_ep, usb3_req, USB3_PN_WRITE);
		enable_bits |= PN_INT_LSTTR;
	पूर्ण

	अगर (ret < 0)
		enable_bits |= PN_INT_BFRDY;

	अगर (enable_bits) अणु
		usb3_set_bit(usb3, enable_bits, USB3_PN_INT_ENA);
		usb3_enable_pipe_irq(usb3, usb3_ep->num);
	पूर्ण
out:
	spin_unlock_irqrestore(&usb3->lock, flags);
पूर्ण

अटल पूर्णांक renesas_usb3_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
				 gfp_t gfp_flags)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb_ep_to_usb3_ep(_ep);
	काष्ठा renesas_usb3_request *usb3_req = usb_req_to_usb3_req(_req);
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	अचिन्हित दीर्घ flags;

	dev_dbg(usb3_to_dev(usb3), "ep_queue: ep%2d, %u\n", usb3_ep->num,
		_req->length);

	_req->status = -EINPROGRESS;
	_req->actual = 0;
	spin_lock_irqsave(&usb3->lock, flags);
	list_add_tail(&usb3_req->queue, &usb3_ep->queue);
	spin_unlock_irqrestore(&usb3->lock, flags);

	अगर (!usb3_ep->num)
		usb3_start_pipe0(usb3_ep, usb3_req);
	अन्यथा
		usb3_start_pipen(usb3_ep, usb3_req);

	वापस 0;
पूर्ण

अटल व्योम usb3_set_device_address(काष्ठा renesas_usb3 *usb3, u16 addr)
अणु
	/* DEV_ADDR bit field is cleared by WarmReset, HotReset and BusReset */
	usb3_set_bit(usb3, USB_COM_CON_DEV_ADDR(addr), USB3_USB_COM_CON);
पूर्ण

अटल bool usb3_std_req_set_address(काष्ठा renesas_usb3 *usb3,
				     काष्ठा usb_ctrlrequest *ctrl)
अणु
	अगर (le16_to_cpu(ctrl->wValue) >= 128)
		वापस true;	/* stall */

	usb3_set_device_address(usb3, le16_to_cpu(ctrl->wValue));
	usb3_set_p0_con_क्रम_no_data(usb3);

	वापस false;
पूर्ण

अटल व्योम usb3_pipe0_पूर्णांकernal_xfer(काष्ठा renesas_usb3 *usb3,
				     व्योम *tx_data, माप_प्रकार len,
				     व्योम (*complete)(काष्ठा usb_ep *ep,
						      काष्ठा usb_request *req))
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, 0);

	अगर (tx_data)
		स_नकल(usb3->ep0_buf, tx_data,
		       min_t(माप_प्रकार, len, USB3_EP0_BUF_SIZE));

	usb3->ep0_req->buf = &usb3->ep0_buf;
	usb3->ep0_req->length = len;
	usb3->ep0_req->complete = complete;
	renesas_usb3_ep_queue(&usb3_ep->ep, usb3->ep0_req, GFP_ATOMIC);
पूर्ण

अटल व्योम usb3_pipe0_get_status_completion(काष्ठा usb_ep *ep,
					     काष्ठा usb_request *req)
अणु
पूर्ण

अटल bool usb3_std_req_get_status(काष्ठा renesas_usb3 *usb3,
				    काष्ठा usb_ctrlrequest *ctrl)
अणु
	bool stall = false;
	काष्ठा renesas_usb3_ep *usb3_ep;
	पूर्णांक num;
	u16 status = 0;
	__le16 tx_data;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		अगर (usb3->gadget.is_selfघातered)
			status |= 1 << USB_DEVICE_SELF_POWERED;
		अगर (usb3->gadget.speed == USB_SPEED_SUPER)
			status |= usb3_feature_get_un_enabled(usb3);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		num = le16_to_cpu(ctrl->wIndex) & USB_ENDPOINT_NUMBER_MASK;
		usb3_ep = usb3_get_ep(usb3, num);
		अगर (usb3_ep->halt)
			status |= 1 << USB_ENDPOINT_HALT;
		अवरोध;
	शेष:
		stall = true;
		अवरोध;
	पूर्ण

	अगर (!stall) अणु
		tx_data = cpu_to_le16(status);
		dev_dbg(usb3_to_dev(usb3), "get_status: req = %p\n",
			usb_req_to_usb3_req(usb3->ep0_req));
		usb3_pipe0_पूर्णांकernal_xfer(usb3, &tx_data, माप(tx_data),
					 usb3_pipe0_get_status_completion);
	पूर्ण

	वापस stall;
पूर्ण

अटल bool usb3_std_req_feature_device(काष्ठा renesas_usb3 *usb3,
					काष्ठा usb_ctrlrequest *ctrl, bool set)
अणु
	bool stall = true;
	u16 w_value = le16_to_cpu(ctrl->wValue);

	चयन (w_value) अणु
	हाल USB_DEVICE_TEST_MODE:
		अगर (!set)
			अवरोध;
		usb3->test_mode = le16_to_cpu(ctrl->wIndex) >> 8;
		stall = false;
		अवरोध;
	हाल USB_DEVICE_U1_ENABLE:
	हाल USB_DEVICE_U2_ENABLE:
		अगर (usb3->gadget.speed != USB_SPEED_SUPER)
			अवरोध;
		अगर (w_value == USB_DEVICE_U1_ENABLE)
			usb3_feature_u1_enable(usb3, set);
		अगर (w_value == USB_DEVICE_U2_ENABLE)
			usb3_feature_u2_enable(usb3, set);
		stall = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस stall;
पूर्ण

अटल पूर्णांक usb3_set_halt_p0(काष्ठा renesas_usb3_ep *usb3_ep, bool halt)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	अगर (unlikely(usb3_ep->num))
		वापस -EINVAL;

	usb3_ep->halt = halt;
	अगर (halt)
		usb3_set_p0_con_stall(usb3);
	अन्यथा
		usb3_set_p0_con_stop(usb3);

	वापस 0;
पूर्ण

अटल पूर्णांक usb3_set_halt_pn(काष्ठा renesas_usb3_ep *usb3_ep, bool halt,
			    bool is_clear_feature)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usb3->lock, flags);
	अगर (!usb3_pn_change(usb3, usb3_ep->num)) अणु
		usb3_ep->halt = halt;
		अगर (halt) अणु
			usb3_pn_stall(usb3);
		पूर्ण अन्यथा अगर (!is_clear_feature || !usb3_ep->wedge) अणु
			usb3_pn_con_clear(usb3);
			usb3_set_bit(usb3, PN_CON_EN, USB3_PN_CON);
			usb3_pn_stop(usb3);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&usb3->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक usb3_set_halt(काष्ठा renesas_usb3_ep *usb3_ep, bool halt,
			 bool is_clear_feature)
अणु
	पूर्णांक ret = 0;

	अगर (halt && usb3_ep->started)
		वापस -EAGAIN;

	अगर (usb3_ep->num)
		ret = usb3_set_halt_pn(usb3_ep, halt, is_clear_feature);
	अन्यथा
		ret = usb3_set_halt_p0(usb3_ep, halt);

	वापस ret;
पूर्ण

अटल bool usb3_std_req_feature_endpoपूर्णांक(काष्ठा renesas_usb3 *usb3,
					  काष्ठा usb_ctrlrequest *ctrl,
					  bool set)
अणु
	पूर्णांक num = le16_to_cpu(ctrl->wIndex) & USB_ENDPOINT_NUMBER_MASK;
	काष्ठा renesas_usb3_ep *usb3_ep;
	काष्ठा renesas_usb3_request *usb3_req;

	अगर (le16_to_cpu(ctrl->wValue) != USB_ENDPOINT_HALT)
		वापस true;	/* stall */

	usb3_ep = usb3_get_ep(usb3, num);
	usb3_set_halt(usb3_ep, set, true);

	/* Restarts a queue अगर clear feature */
	अगर (!set) अणु
		usb3_ep->started = false;
		usb3_req = usb3_get_request(usb3_ep);
		अगर (usb3_req)
			usb3_start_pipen(usb3_ep, usb3_req);
	पूर्ण

	वापस false;
पूर्ण

अटल bool usb3_std_req_feature(काष्ठा renesas_usb3 *usb3,
				 काष्ठा usb_ctrlrequest *ctrl, bool set)
अणु
	bool stall = false;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		stall = usb3_std_req_feature_device(usb3, ctrl, set);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		stall = usb3_std_req_feature_endpoपूर्णांक(usb3, ctrl, set);
		अवरोध;
	शेष:
		stall = true;
		अवरोध;
	पूर्ण

	अगर (!stall)
		usb3_set_p0_con_क्रम_no_data(usb3);

	वापस stall;
पूर्ण

अटल व्योम usb3_pipe0_set_sel_completion(काष्ठा usb_ep *ep,
					  काष्ठा usb_request *req)
अणु
	/* TODO */
पूर्ण

अटल bool usb3_std_req_set_sel(काष्ठा renesas_usb3 *usb3,
				 काष्ठा usb_ctrlrequest *ctrl)
अणु
	u16 w_length = le16_to_cpu(ctrl->wLength);

	अगर (w_length != 6)
		वापस true;	/* stall */

	dev_dbg(usb3_to_dev(usb3), "set_sel: req = %p\n",
		usb_req_to_usb3_req(usb3->ep0_req));
	usb3_pipe0_पूर्णांकernal_xfer(usb3, शून्य, 6, usb3_pipe0_set_sel_completion);

	वापस false;
पूर्ण

अटल bool usb3_std_req_set_configuration(काष्ठा renesas_usb3 *usb3,
					   काष्ठा usb_ctrlrequest *ctrl)
अणु
	अगर (le16_to_cpu(ctrl->wValue) > 0)
		usb3_set_bit(usb3, USB_COM_CON_CONF, USB3_USB_COM_CON);
	अन्यथा
		usb3_clear_bit(usb3, USB_COM_CON_CONF, USB3_USB_COM_CON);

	वापस false;
पूर्ण

/**
 * usb3_handle_standard_request - handle some standard requests
 * @usb3: the renesas_usb3 poपूर्णांकer
 * @ctrl: a poपूर्णांकer of setup data
 *
 * Returns true अगर this function handled a standard request
 */
अटल bool usb3_handle_standard_request(काष्ठा renesas_usb3 *usb3,
					 काष्ठा usb_ctrlrequest *ctrl)
अणु
	bool ret = false;
	bool stall = false;

	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (ctrl->bRequest) अणु
		हाल USB_REQ_SET_ADDRESS:
			stall = usb3_std_req_set_address(usb3, ctrl);
			ret = true;
			अवरोध;
		हाल USB_REQ_GET_STATUS:
			stall = usb3_std_req_get_status(usb3, ctrl);
			ret = true;
			अवरोध;
		हाल USB_REQ_CLEAR_FEATURE:
			stall = usb3_std_req_feature(usb3, ctrl, false);
			ret = true;
			अवरोध;
		हाल USB_REQ_SET_FEATURE:
			stall = usb3_std_req_feature(usb3, ctrl, true);
			ret = true;
			अवरोध;
		हाल USB_REQ_SET_SEL:
			stall = usb3_std_req_set_sel(usb3, ctrl);
			ret = true;
			अवरोध;
		हाल USB_REQ_SET_ISOCH_DELAY:
			/* This hardware करोesn't support Isochronous xfer */
			stall = true;
			ret = true;
			अवरोध;
		हाल USB_REQ_SET_CONFIGURATION:
			usb3_std_req_set_configuration(usb3, ctrl);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stall)
		usb3_set_p0_con_stall(usb3);

	वापस ret;
पूर्ण

अटल पूर्णांक usb3_p0_con_clear_buffer(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_set_bit(usb3, P0_CON_BCLR, USB3_P0_CON);

	वापस usb3_रुको(usb3, USB3_P0_CON, P0_CON_BCLR, 0);
पूर्ण

अटल व्योम usb3_irq_epc_pipe0_setup(काष्ठा renesas_usb3 *usb3)
अणु
	काष्ठा usb_ctrlrequest ctrl;
	काष्ठा renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, 0);

	/* Call giveback function अगर previous transfer is not completed */
	अगर (usb3_ep->started)
		usb3_request_करोne(usb3_ep, usb3_get_request(usb3_ep),
				  -ECONNRESET);

	usb3_p0_con_clear_buffer(usb3);
	usb3_get_setup_data(usb3, &ctrl);
	अगर (!usb3_handle_standard_request(usb3, &ctrl))
		अगर (usb3->driver->setup(&usb3->gadget, &ctrl) < 0)
			usb3_set_p0_con_stall(usb3);
पूर्ण

अटल व्योम usb3_irq_epc_pipe0_bfrdy(काष्ठा renesas_usb3 *usb3)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, 0);
	काष्ठा renesas_usb3_request *usb3_req = usb3_get_request(usb3_ep);

	अगर (!usb3_req)
		वापस;

	usb3_p0_xfer(usb3_ep, usb3_req);
पूर्ण

अटल व्योम usb3_irq_epc_pipe0(काष्ठा renesas_usb3 *usb3)
अणु
	u32 p0_पूर्णांक_sta = usb3_पढ़ो(usb3, USB3_P0_INT_STA);

	p0_पूर्णांक_sta &= usb3_पढ़ो(usb3, USB3_P0_INT_ENA);
	usb3_ग_लिखो(usb3, p0_पूर्णांक_sta, USB3_P0_INT_STA);
	अगर (p0_पूर्णांक_sta & P0_INT_STSED)
		usb3_irq_epc_pipe0_status_end(usb3);
	अगर (p0_पूर्णांक_sta & P0_INT_SETUP)
		usb3_irq_epc_pipe0_setup(usb3);
	अगर (p0_पूर्णांक_sta & P0_INT_BFRDY)
		usb3_irq_epc_pipe0_bfrdy(usb3);
पूर्ण

अटल व्योम usb3_request_करोne_pipen(काष्ठा renesas_usb3 *usb3,
				    काष्ठा renesas_usb3_ep *usb3_ep,
				    काष्ठा renesas_usb3_request *usb3_req,
				    पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usb3->lock, flags);
	अगर (usb3_pn_change(usb3, usb3_ep->num))
		usb3_pn_stop(usb3);
	spin_unlock_irqrestore(&usb3->lock, flags);

	usb3_disable_pipe_irq(usb3, usb3_ep->num);
	usb3_request_करोne(usb3_ep, usb3_req, status);

	/* get next usb3_req */
	usb3_req = usb3_get_request(usb3_ep);
	अगर (usb3_req)
		usb3_start_pipen(usb3_ep, usb3_req);
पूर्ण

अटल व्योम usb3_irq_epc_pipen_lsttr(काष्ठा renesas_usb3 *usb3, पूर्णांक num)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, num);
	काष्ठा renesas_usb3_request *usb3_req = usb3_get_request(usb3_ep);

	अगर (!usb3_req)
		वापस;

	अगर (usb3_ep->dir_in) अणु
		dev_dbg(usb3_to_dev(usb3), "%s: len = %u, actual = %u\n",
			__func__, usb3_req->req.length, usb3_req->req.actual);
		usb3_request_करोne_pipen(usb3, usb3_ep, usb3_req, 0);
	पूर्ण
पूर्ण

अटल व्योम usb3_irq_epc_pipen_bfrdy(काष्ठा renesas_usb3 *usb3, पूर्णांक num)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, num);
	काष्ठा renesas_usb3_request *usb3_req = usb3_get_request(usb3_ep);
	bool करोne = false;

	अगर (!usb3_req)
		वापस;

	spin_lock(&usb3->lock);
	अगर (usb3_pn_change(usb3, num))
		जाओ out;

	अगर (usb3_ep->dir_in) अणु
		/* Do not stop the IN pipe here to detect LSTTR पूर्णांकerrupt */
		अगर (!usb3_ग_लिखो_pipe(usb3_ep, usb3_req, USB3_PN_WRITE))
			usb3_clear_bit(usb3, PN_INT_BFRDY, USB3_PN_INT_ENA);
	पूर्ण अन्यथा अणु
		अगर (!usb3_पढ़ो_pipe(usb3_ep, usb3_req, USB3_PN_READ))
			करोne = true;
	पूर्ण

out:
	/* need to unlock because usb3_request_करोne_pipen() locks it */
	spin_unlock(&usb3->lock);

	अगर (करोne)
		usb3_request_करोne_pipen(usb3, usb3_ep, usb3_req, 0);
पूर्ण

अटल व्योम usb3_irq_epc_pipen(काष्ठा renesas_usb3 *usb3, पूर्णांक num)
अणु
	u32 pn_पूर्णांक_sta;

	spin_lock(&usb3->lock);
	अगर (usb3_pn_change(usb3, num) < 0) अणु
		spin_unlock(&usb3->lock);
		वापस;
	पूर्ण

	pn_पूर्णांक_sta = usb3_पढ़ो(usb3, USB3_PN_INT_STA);
	pn_पूर्णांक_sta &= usb3_पढ़ो(usb3, USB3_PN_INT_ENA);
	usb3_ग_लिखो(usb3, pn_पूर्णांक_sta, USB3_PN_INT_STA);
	spin_unlock(&usb3->lock);
	अगर (pn_पूर्णांक_sta & PN_INT_LSTTR)
		usb3_irq_epc_pipen_lsttr(usb3, num);
	अगर (pn_पूर्णांक_sta & PN_INT_BFRDY)
		usb3_irq_epc_pipen_bfrdy(usb3, num);
पूर्ण

अटल व्योम usb3_irq_epc_पूर्णांक_2(काष्ठा renesas_usb3 *usb3, u32 पूर्णांक_sta_2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < usb3->num_usb3_eps; i++) अणु
		अगर (पूर्णांक_sta_2 & USB_INT_2_PIPE(i)) अणु
			अगर (!i)
				usb3_irq_epc_pipe0(usb3);
			अन्यथा
				usb3_irq_epc_pipen(usb3, i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usb3_irq_idmon_change(काष्ठा renesas_usb3 *usb3)
अणु
	usb3_check_id(usb3);
पूर्ण

अटल व्योम usb3_irq_otg_पूर्णांक(काष्ठा renesas_usb3 *usb3, u32 otg_पूर्णांक_sta)
अणु
	अगर (otg_पूर्णांक_sta & USB_OTG_IDMON)
		usb3_irq_idmon_change(usb3);
पूर्ण

अटल व्योम usb3_irq_epc(काष्ठा renesas_usb3 *usb3)
अणु
	u32 पूर्णांक_sta_1 = usb3_पढ़ो(usb3, USB3_USB_INT_STA_1);
	u32 पूर्णांक_sta_2 = usb3_पढ़ो(usb3, USB3_USB_INT_STA_2);
	u32 otg_पूर्णांक_sta = usb3_पढ़ो(usb3, USB3_USB_OTG_INT_STA);

	पूर्णांक_sta_1 &= usb3_पढ़ो(usb3, USB3_USB_INT_ENA_1);
	अगर (पूर्णांक_sta_1) अणु
		usb3_ग_लिखो(usb3, पूर्णांक_sta_1, USB3_USB_INT_STA_1);
		usb3_irq_epc_पूर्णांक_1(usb3, पूर्णांक_sta_1);
	पूर्ण

	पूर्णांक_sta_2 &= usb3_पढ़ो(usb3, USB3_USB_INT_ENA_2);
	अगर (पूर्णांक_sta_2)
		usb3_irq_epc_पूर्णांक_2(usb3, पूर्णांक_sta_2);

	otg_पूर्णांक_sta &= usb3_पढ़ो(usb3, USB3_USB_OTG_INT_ENA);
	अगर (otg_पूर्णांक_sta) अणु
		usb3_ग_लिखो(usb3, otg_पूर्णांक_sta, USB3_USB_OTG_INT_STA);
		usb3_irq_otg_पूर्णांक(usb3, otg_पूर्णांक_sta);
	पूर्ण
पूर्ण

अटल व्योम usb3_irq_dma_पूर्णांक(काष्ठा renesas_usb3 *usb3, u32 dma_sta)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep;
	काष्ठा renesas_usb3_request *usb3_req;
	पूर्णांक i, status;

	क्रम (i = 0; i < usb3->num_usb3_eps; i++) अणु
		अगर (!(dma_sta & DMA_INT(i)))
			जारी;

		usb3_ep = usb3_get_ep(usb3, i);
		अगर (!(usb3_पढ़ो(usb3, USB3_AXI_INT_STA) &
		    AXI_INT_PRDEN_CLR_STA(usb3_ep->dma->num)))
			जारी;

		usb3_req = usb3_get_request(usb3_ep);
		status = usb3_dma_try_stop(usb3_ep, usb3_req);
		usb3_request_करोne_pipen(usb3, usb3_ep, usb3_req, status);
	पूर्ण
पूर्ण

अटल व्योम usb3_irq_dma(काष्ठा renesas_usb3 *usb3)
अणु
	u32 dma_sta = usb3_पढ़ो(usb3, USB3_DMA_INT_STA);

	dma_sta &= usb3_पढ़ो(usb3, USB3_DMA_INT_ENA);
	अगर (dma_sta) अणु
		usb3_ग_लिखो(usb3, dma_sta, USB3_DMA_INT_STA);
		usb3_irq_dma_पूर्णांक(usb3, dma_sta);
	पूर्ण
पूर्ण

अटल irqवापस_t renesas_usb3_irq(पूर्णांक irq, व्योम *_usb3)
अणु
	काष्ठा renesas_usb3 *usb3 = _usb3;
	irqवापस_t ret = IRQ_NONE;
	u32 axi_पूर्णांक_sta = usb3_पढ़ो(usb3, USB3_AXI_INT_STA);

	अगर (axi_पूर्णांक_sta & AXI_INT_DMAINT) अणु
		usb3_irq_dma(usb3);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (axi_पूर्णांक_sta & AXI_INT_EPCINT) अणु
		usb3_irq_epc(usb3);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम usb3_ग_लिखो_pn_mod(काष्ठा renesas_usb3_ep *usb3_ep,
			      स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 val = 0;

	val |= usb3_ep->dir_in ? PN_MOD_सूची : 0;
	val |= PN_MOD_TYPE(usb_endpoपूर्णांक_type(desc));
	val |= PN_MOD_EPNUM(usb_endpoपूर्णांक_num(desc));
	usb3_ग_लिखो(usb3, val, USB3_PN_MOD);
पूर्ण

अटल u32 usb3_calc_ramarea(पूर्णांक ram_size)
अणु
	WARN_ON(ram_size > SZ_16K);

	अगर (ram_size <= SZ_1K)
		वापस PN_RAMMAP_RAMAREA_1KB;
	अन्यथा अगर (ram_size <= SZ_2K)
		वापस PN_RAMMAP_RAMAREA_2KB;
	अन्यथा अगर (ram_size <= SZ_4K)
		वापस PN_RAMMAP_RAMAREA_4KB;
	अन्यथा अगर (ram_size <= SZ_8K)
		वापस PN_RAMMAP_RAMAREA_8KB;
	अन्यथा
		वापस PN_RAMMAP_RAMAREA_16KB;
पूर्ण

अटल u32 usb3_calc_rammap_val(काष्ठा renesas_usb3_ep *usb3_ep,
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	पूर्णांक i;
	अटल स्थिर u32 max_packet_array[] = अणु8, 16, 32, 64, 512पूर्ण;
	u32 mpkt = PN_RAMMAP_MPKT(1024);

	क्रम (i = 0; i < ARRAY_SIZE(max_packet_array); i++) अणु
		अगर (usb_endpoपूर्णांक_maxp(desc) <= max_packet_array[i])
			mpkt = PN_RAMMAP_MPKT(max_packet_array[i]);
	पूर्ण

	वापस usb3_ep->rammap_val | mpkt;
पूर्ण

अटल पूर्णांक usb3_enable_pipe_n(काष्ठा renesas_usb3_ep *usb3_ep,
			      स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	अचिन्हित दीर्घ flags;

	usb3_ep->dir_in = usb_endpoपूर्णांक_dir_in(desc);

	spin_lock_irqsave(&usb3->lock, flags);
	अगर (!usb3_pn_change(usb3, usb3_ep->num)) अणु
		usb3_ग_लिखो_pn_mod(usb3_ep, desc);
		usb3_ग_लिखो(usb3, usb3_calc_rammap_val(usb3_ep, desc),
			   USB3_PN_RAMMAP);
		usb3_pn_con_clear(usb3);
		usb3_set_bit(usb3, PN_CON_EN, USB3_PN_CON);
	पूर्ण
	spin_unlock_irqrestore(&usb3->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक usb3_disable_pipe_n(काष्ठा renesas_usb3_ep *usb3_ep)
अणु
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	अचिन्हित दीर्घ flags;

	usb3_ep->halt = false;

	spin_lock_irqsave(&usb3->lock, flags);
	अगर (!usb3_pn_change(usb3, usb3_ep->num)) अणु
		usb3_ग_लिखो(usb3, 0, USB3_PN_INT_ENA);
		usb3_ग_लिखो(usb3, 0, USB3_PN_RAMMAP);
		usb3_clear_bit(usb3, PN_CON_EN, USB3_PN_CON);
	पूर्ण
	spin_unlock_irqrestore(&usb3->lock, flags);

	वापस 0;
पूर्ण

/*------- usb_ep_ops -----------------------------------------------------*/
अटल पूर्णांक renesas_usb3_ep_enable(काष्ठा usb_ep *_ep,
				  स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb_ep_to_usb3_ep(_ep);

	वापस usb3_enable_pipe_n(usb3_ep, desc);
पूर्ण

अटल पूर्णांक renesas_usb3_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb_ep_to_usb3_ep(_ep);
	काष्ठा renesas_usb3_request *usb3_req;

	करो अणु
		usb3_req = usb3_get_request(usb3_ep);
		अगर (!usb3_req)
			अवरोध;
		usb3_dma_try_stop(usb3_ep, usb3_req);
		usb3_request_करोne(usb3_ep, usb3_req, -ESHUTDOWN);
	पूर्ण जबतक (1);

	वापस usb3_disable_pipe_n(usb3_ep);
पूर्ण

अटल काष्ठा usb_request *__renesas_usb3_ep_alloc_request(gfp_t gfp_flags)
अणु
	काष्ठा renesas_usb3_request *usb3_req;

	usb3_req = kzalloc(माप(काष्ठा renesas_usb3_request), gfp_flags);
	अगर (!usb3_req)
		वापस शून्य;

	INIT_LIST_HEAD(&usb3_req->queue);

	वापस &usb3_req->req;
पूर्ण

अटल व्योम __renesas_usb3_ep_मुक्त_request(काष्ठा usb_request *_req)
अणु
	काष्ठा renesas_usb3_request *usb3_req = usb_req_to_usb3_req(_req);

	kमुक्त(usb3_req);
पूर्ण

अटल काष्ठा usb_request *renesas_usb3_ep_alloc_request(काष्ठा usb_ep *_ep,
							 gfp_t gfp_flags)
अणु
	वापस __renesas_usb3_ep_alloc_request(gfp_flags);
पूर्ण

अटल व्योम renesas_usb3_ep_मुक्त_request(काष्ठा usb_ep *_ep,
					 काष्ठा usb_request *_req)
अणु
	__renesas_usb3_ep_मुक्त_request(_req);
पूर्ण

अटल पूर्णांक renesas_usb3_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb_ep_to_usb3_ep(_ep);
	काष्ठा renesas_usb3_request *usb3_req = usb_req_to_usb3_req(_req);
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	dev_dbg(usb3_to_dev(usb3), "ep_dequeue: ep%2d, %u\n", usb3_ep->num,
		_req->length);

	usb3_dma_try_stop(usb3_ep, usb3_req);
	usb3_request_करोne_pipen(usb3, usb3_ep, usb3_req, -ECONNRESET);

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_usb3_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	वापस usb3_set_halt(usb_ep_to_usb3_ep(_ep), !!value, false);
पूर्ण

अटल पूर्णांक renesas_usb3_ep_set_wedge(काष्ठा usb_ep *_ep)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb_ep_to_usb3_ep(_ep);

	usb3_ep->wedge = true;
	वापस usb3_set_halt(usb3_ep, true, false);
पूर्ण

अटल व्योम renesas_usb3_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep = usb_ep_to_usb3_ep(_ep);
	काष्ठा renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	अचिन्हित दीर्घ flags;

	अगर (usb3_ep->num) अणु
		spin_lock_irqsave(&usb3->lock, flags);
		अगर (!usb3_pn_change(usb3, usb3_ep->num)) अणु
			usb3_pn_con_clear(usb3);
			usb3_set_bit(usb3, PN_CON_EN, USB3_PN_CON);
		पूर्ण
		spin_unlock_irqrestore(&usb3->lock, flags);
	पूर्ण अन्यथा अणु
		usb3_p0_con_clear_buffer(usb3);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops renesas_usb3_ep_ops = अणु
	.enable		= renesas_usb3_ep_enable,
	.disable	= renesas_usb3_ep_disable,

	.alloc_request	= renesas_usb3_ep_alloc_request,
	.मुक्त_request	= renesas_usb3_ep_मुक्त_request,

	.queue		= renesas_usb3_ep_queue,
	.dequeue	= renesas_usb3_ep_dequeue,

	.set_halt	= renesas_usb3_ep_set_halt,
	.set_wedge	= renesas_usb3_ep_set_wedge,
	.fअगरo_flush	= renesas_usb3_ep_fअगरo_flush,
पूर्ण;

/*------- usb_gadget_ops -------------------------------------------------*/
अटल पूर्णांक renesas_usb3_start(काष्ठा usb_gadget *gadget,
			      काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा renesas_usb3 *usb3;

	अगर (!driver || driver->max_speed < USB_SPEED_FULL ||
	    !driver->setup)
		वापस -EINVAL;

	usb3 = gadget_to_renesas_usb3(gadget);

	/* hook up the driver */
	usb3->driver = driver;

	अगर (usb3->phy)
		phy_init(usb3->phy);

	pm_runसमय_get_sync(usb3_to_dev(usb3));

	renesas_usb3_init_controller(usb3);

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_usb3_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा renesas_usb3 *usb3 = gadget_to_renesas_usb3(gadget);

	usb3->softconnect = false;
	usb3->gadget.speed = USB_SPEED_UNKNOWN;
	usb3->driver = शून्य;
	renesas_usb3_stop_controller(usb3);

	अगर (usb3->phy)
		phy_निकास(usb3->phy);

	pm_runसमय_put(usb3_to_dev(usb3));

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_usb3_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक renesas_usb3_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा renesas_usb3 *usb3 = gadget_to_renesas_usb3(gadget);

	usb3->softconnect = !!is_on;

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_usb3_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक is_self)
अणु
	gadget->is_selfघातered = !!is_self;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops renesas_usb3_gadget_ops = अणु
	.get_frame		= renesas_usb3_get_frame,
	.udc_start		= renesas_usb3_start,
	.udc_stop		= renesas_usb3_stop,
	.pullup			= renesas_usb3_pullup,
	.set_selfघातered	= renesas_usb3_set_selfघातered,
पूर्ण;

अटल क्रमागत usb_role renesas_usb3_role_चयन_get(काष्ठा usb_role_चयन *sw)
अणु
	काष्ठा renesas_usb3 *usb3 = usb_role_चयन_get_drvdata(sw);
	क्रमागत usb_role cur_role;

	pm_runसमय_get_sync(usb3_to_dev(usb3));
	cur_role = usb3_is_host(usb3) ? USB_ROLE_HOST : USB_ROLE_DEVICE;
	pm_runसमय_put(usb3_to_dev(usb3));

	वापस cur_role;
पूर्ण

अटल व्योम handle_ext_role_चयन_states(काष्ठा device *dev,
					    क्रमागत usb_role role)
अणु
	काष्ठा renesas_usb3 *usb3 = dev_get_drvdata(dev);
	काष्ठा device *host = usb3->host_dev;
	क्रमागत usb_role cur_role = renesas_usb3_role_चयन_get(usb3->role_sw);

	चयन (role) अणु
	हाल USB_ROLE_NONE:
		usb3->connection_state = USB_ROLE_NONE;
		अगर (usb3->driver)
			usb3_disconnect(usb3);
		usb3_vbus_out(usb3, false);
		अवरोध;
	हाल USB_ROLE_DEVICE:
		अगर (usb3->connection_state == USB_ROLE_NONE) अणु
			usb3->connection_state = USB_ROLE_DEVICE;
			usb3_set_mode(usb3, false);
			अगर (usb3->driver)
				usb3_connect(usb3);
		पूर्ण अन्यथा अगर (cur_role == USB_ROLE_HOST)  अणु
			device_release_driver(host);
			usb3_set_mode(usb3, false);
			अगर (usb3->driver)
				usb3_connect(usb3);
		पूर्ण
		usb3_vbus_out(usb3, false);
		अवरोध;
	हाल USB_ROLE_HOST:
		अगर (usb3->connection_state == USB_ROLE_NONE) अणु
			अगर (usb3->driver)
				usb3_disconnect(usb3);

			usb3->connection_state = USB_ROLE_HOST;
			usb3_set_mode(usb3, true);
			usb3_vbus_out(usb3, true);
			अगर (device_attach(host) < 0)
				dev_err(dev, "device_attach(host) failed\n");
		पूर्ण अन्यथा अगर (cur_role == USB_ROLE_DEVICE) अणु
			usb3_disconnect(usb3);
			/* Must set the mode beक्रमe device_attach of the host */
			usb3_set_mode(usb3, true);
			/* This device_attach() might sleep */
			अगर (device_attach(host) < 0)
				dev_err(dev, "device_attach(host) failed\n");
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_role_चयन_states(काष्ठा device *dev,
					    क्रमागत usb_role role)
अणु
	काष्ठा renesas_usb3 *usb3 = dev_get_drvdata(dev);
	काष्ठा device *host = usb3->host_dev;
	क्रमागत usb_role cur_role = renesas_usb3_role_चयन_get(usb3->role_sw);

	अगर (cur_role == USB_ROLE_HOST && role == USB_ROLE_DEVICE) अणु
		device_release_driver(host);
		usb3_set_mode(usb3, false);
	पूर्ण अन्यथा अगर (cur_role == USB_ROLE_DEVICE && role == USB_ROLE_HOST) अणु
		/* Must set the mode beक्रमe device_attach of the host */
		usb3_set_mode(usb3, true);
		/* This device_attach() might sleep */
		अगर (device_attach(host) < 0)
			dev_err(dev, "device_attach(host) failed\n");
	पूर्ण
पूर्ण

अटल पूर्णांक renesas_usb3_role_चयन_set(काष्ठा usb_role_चयन *sw,
					क्रमागत usb_role role)
अणु
	काष्ठा renesas_usb3 *usb3 = usb_role_चयन_get_drvdata(sw);

	pm_runसमय_get_sync(usb3_to_dev(usb3));

	अगर (usb3->role_sw_by_connector)
		handle_ext_role_चयन_states(usb3_to_dev(usb3), role);
	अन्यथा
		handle_role_चयन_states(usb3_to_dev(usb3), role);

	pm_runसमय_put(usb3_to_dev(usb3));

	वापस 0;
पूर्ण

अटल sमाप_प्रकार role_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा renesas_usb3 *usb3 = dev_get_drvdata(dev);
	bool new_mode_is_host;

	अगर (!usb3->driver)
		वापस -ENODEV;

	अगर (usb3->क्रमced_b_device)
		वापस -EBUSY;

	अगर (sysfs_streq(buf, "host"))
		new_mode_is_host = true;
	अन्यथा अगर (sysfs_streq(buf, "peripheral"))
		new_mode_is_host = false;
	अन्यथा
		वापस -EINVAL;

	अगर (new_mode_is_host == usb3_is_host(usb3))
		वापस -EINVAL;

	usb3_mode_config(usb3, new_mode_is_host, usb3_is_a_device(usb3));

	वापस count;
पूर्ण

अटल sमाप_प्रकार role_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा renesas_usb3 *usb3 = dev_get_drvdata(dev);

	अगर (!usb3->driver)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%s\n", usb3_is_host(usb3) ? "host" : "peripheral");
पूर्ण
अटल DEVICE_ATTR_RW(role);

अटल पूर्णांक renesas_usb3_b_device_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा renesas_usb3 *usb3 = s->निजी;

	seq_म_लिखो(s, "%d\n", usb3->क्रमced_b_device);

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_usb3_b_device_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, renesas_usb3_b_device_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार renesas_usb3_b_device_ग_लिखो(काष्ठा file *file,
					   स्थिर अक्षर __user *ubuf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा renesas_usb3 *usb3 = s->निजी;
	अक्षर buf[32];

	अगर (!usb3->driver)
		वापस -ENODEV;

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	usb3->start_to_connect = false;
	अगर (usb3->workaround_क्रम_vbus && usb3->क्रमced_b_device &&
	    !म_भेदन(buf, "2", 1))
		usb3->start_to_connect = true;
	अन्यथा अगर (!म_भेदन(buf, "1", 1))
		usb3->क्रमced_b_device = true;
	अन्यथा
		usb3->क्रमced_b_device = false;

	अगर (usb3->workaround_क्रम_vbus)
		usb3_disconnect(usb3);

	/* Let this driver call usb3_connect() अगर needed */
	usb3_check_id(usb3);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations renesas_usb3_b_device_fops = अणु
	.खोलो = renesas_usb3_b_device_खोलो,
	.ग_लिखो = renesas_usb3_b_device_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम renesas_usb3_debugfs_init(काष्ठा renesas_usb3 *usb3,
				      काष्ठा device *dev)
अणु
	usb3->dentry = debugfs_create_dir(dev_name(dev), usb_debug_root);

	debugfs_create_file("b_device", 0644, usb3->dentry, usb3,
			    &renesas_usb3_b_device_fops);
पूर्ण

/*------- platक्रमm_driver ------------------------------------------------*/
अटल पूर्णांक renesas_usb3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा renesas_usb3 *usb3 = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(usb3->dentry);
	device_हटाओ_file(&pdev->dev, &dev_attr_role);

	usb_role_चयन_unरेजिस्टर(usb3->role_sw);

	usb_del_gadget_udc(&usb3->gadget);
	renesas_usb3_dma_मुक्त_prd(usb3, &pdev->dev);

	__renesas_usb3_ep_मुक्त_request(usb3->ep0_req);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_usb3_init_ep(काष्ठा renesas_usb3 *usb3, काष्ठा device *dev,
				स्थिर काष्ठा renesas_usb3_priv *priv)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep;
	पूर्णांक i;

	/* calculate num_usb3_eps from renesas_usb3_priv */
	usb3->num_usb3_eps = priv->ramsize_per_ramअगर * priv->num_ramअगर * 2 /
			     priv->ramsize_per_pipe + 1;

	अगर (usb3->num_usb3_eps > USB3_MAX_NUM_PIPES)
		usb3->num_usb3_eps = USB3_MAX_NUM_PIPES;

	usb3->usb3_ep = devm_kसुस्मृति(dev,
				     usb3->num_usb3_eps, माप(*usb3_ep),
				     GFP_KERNEL);
	अगर (!usb3->usb3_ep)
		वापस -ENOMEM;

	dev_dbg(dev, "%s: num_usb3_eps = %d\n", __func__, usb3->num_usb3_eps);
	/*
	 * This driver prepares pipes as follows:
	 *  - odd pipes = IN pipe
	 *  - even pipes = OUT pipe (except pipe 0)
	 */
	usb3_क्रम_each_ep(usb3_ep, usb3, i) अणु
		snम_लिखो(usb3_ep->ep_name, माप(usb3_ep->ep_name), "ep%d", i);
		usb3_ep->usb3 = usb3;
		usb3_ep->num = i;
		usb3_ep->ep.name = usb3_ep->ep_name;
		usb3_ep->ep.ops = &renesas_usb3_ep_ops;
		INIT_LIST_HEAD(&usb3_ep->queue);
		INIT_LIST_HEAD(&usb3_ep->ep.ep_list);
		अगर (!i) अणु
			/* क्रम control pipe */
			usb3->gadget.ep0 = &usb3_ep->ep;
			usb_ep_set_maxpacket_limit(&usb3_ep->ep,
						USB3_EP0_SS_MAX_PACKET_SIZE);
			usb3_ep->ep.caps.type_control = true;
			usb3_ep->ep.caps.dir_in = true;
			usb3_ep->ep.caps.dir_out = true;
			जारी;
		पूर्ण

		/* क्रम bulk or पूर्णांकerrupt pipe */
		usb_ep_set_maxpacket_limit(&usb3_ep->ep, ~0);
		list_add_tail(&usb3_ep->ep.ep_list, &usb3->gadget.ep_list);
		usb3_ep->ep.caps.type_bulk = true;
		usb3_ep->ep.caps.type_पूर्णांक = true;
		अगर (i & 1)
			usb3_ep->ep.caps.dir_in = true;
		अन्यथा
			usb3_ep->ep.caps.dir_out = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम renesas_usb3_init_ram(काष्ठा renesas_usb3 *usb3, काष्ठा device *dev,
				  स्थिर काष्ठा renesas_usb3_priv *priv)
अणु
	काष्ठा renesas_usb3_ep *usb3_ep;
	पूर्णांक i;
	u32 ramअगर[2], basead[2];	/* index 0 = क्रम IN pipes */
	u32 *cur_ramअगर, *cur_basead;
	u32 val;

	स_रखो(ramअगर, 0, माप(ramअगर));
	स_रखो(basead, 0, माप(basead));

	/*
	 * This driver prepares pipes as follows:
	 *  - all pipes = the same size as "ramsize_per_pipe"
	 * Please refer to the "Method of Specifying RAM Mapping"
	 */
	usb3_क्रम_each_ep(usb3_ep, usb3, i) अणु
		अगर (!i)
			जारी;	/* out of scope अगर ep num = 0 */
		अगर (usb3_ep->ep.caps.dir_in) अणु
			cur_ramअगर = &ramअगर[0];
			cur_basead = &basead[0];
		पूर्ण अन्यथा अणु
			cur_ramअगर = &ramअगर[1];
			cur_basead = &basead[1];
		पूर्ण

		अगर (*cur_basead > priv->ramsize_per_ramअगर)
			जारी;	/* out of memory क्रम IN or OUT pipe */

		/* calculate rammap_val */
		val = PN_RAMMAP_RAMIF(*cur_ramअगर);
		val |= usb3_calc_ramarea(priv->ramsize_per_pipe);
		val |= PN_RAMMAP_BASEAD(*cur_basead);
		usb3_ep->rammap_val = val;

		dev_dbg(dev, "ep%2d: val = %08x, ramif = %d, base = %x\n",
			i, val, *cur_ramअगर, *cur_basead);

		/* update current ramअगर */
		अगर (*cur_ramअगर + 1 == priv->num_ramअगर) अणु
			*cur_ramअगर = 0;
			*cur_basead += priv->ramsize_per_pipe;
		पूर्ण अन्यथा अणु
			(*cur_ramअगर)++;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा renesas_usb3_priv renesas_usb3_priv_r8a7795_es1 = अणु
	.ramsize_per_ramअगर = SZ_16K,
	.num_ramअगर = 2,
	.ramsize_per_pipe = SZ_4K,
	.workaround_क्रम_vbus = true,
पूर्ण;

अटल स्थिर काष्ठा renesas_usb3_priv renesas_usb3_priv_gen3 = अणु
	.ramsize_per_ramअगर = SZ_16K,
	.num_ramअगर = 4,
	.ramsize_per_pipe = SZ_4K,
पूर्ण;

अटल स्थिर काष्ठा renesas_usb3_priv renesas_usb3_priv_r8a77990 = अणु
	.ramsize_per_ramअगर = SZ_16K,
	.num_ramअगर = 4,
	.ramsize_per_pipe = SZ_4K,
	.workaround_क्रम_vbus = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id usb3_of_match[] = अणु
	अणु
		.compatible = "renesas,r8a7795-usb3-peri",
		.data = &renesas_usb3_priv_gen3,
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen3-usb3-peri",
		.data = &renesas_usb3_priv_gen3,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, usb3_of_match);

अटल स्थिर काष्ठा soc_device_attribute renesas_usb3_quirks_match[] = अणु
	अणु
		.soc_id = "r8a774c0",
		.data = &renesas_usb3_priv_r8a77990,
	पूर्ण,
	अणु
		.soc_id = "r8a7795", .revision = "ES1.*",
		.data = &renesas_usb3_priv_r8a7795_es1,
	पूर्ण,
	अणु
		.soc_id = "r8a77990",
		.data = &renesas_usb3_priv_r8a77990,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक renesas_usb3_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल काष्ठा usb_role_चयन_desc renesas_usb3_role_चयन_desc = अणु
	.set = renesas_usb3_role_चयन_set,
	.get = renesas_usb3_role_चयन_get,
	.allow_userspace_control = true,
पूर्ण;

अटल पूर्णांक renesas_usb3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा renesas_usb3 *usb3;
	पूर्णांक irq, ret;
	स्थिर काष्ठा renesas_usb3_priv *priv;
	स्थिर काष्ठा soc_device_attribute *attr;

	attr = soc_device_match(renesas_usb3_quirks_match);
	अगर (attr)
		priv = attr->data;
	अन्यथा
		priv = of_device_get_match_data(&pdev->dev);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	usb3 = devm_kzalloc(&pdev->dev, माप(*usb3), GFP_KERNEL);
	अगर (!usb3)
		वापस -ENOMEM;

	usb3->reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(usb3->reg))
		वापस PTR_ERR(usb3->reg);

	platक्रमm_set_drvdata(pdev, usb3);
	spin_lock_init(&usb3->lock);

	usb3->gadget.ops = &renesas_usb3_gadget_ops;
	usb3->gadget.name = udc_name;
	usb3->gadget.max_speed = USB_SPEED_SUPER;
	INIT_LIST_HEAD(&usb3->gadget.ep_list);
	ret = renesas_usb3_init_ep(usb3, &pdev->dev, priv);
	अगर (ret < 0)
		वापस ret;
	renesas_usb3_init_ram(usb3, &pdev->dev, priv);

	ret = devm_request_irq(&pdev->dev, irq, renesas_usb3_irq, 0,
			       dev_name(&pdev->dev), usb3);
	अगर (ret < 0)
		वापस ret;

	INIT_WORK(&usb3->extcon_work, renesas_usb3_extcon_work);
	usb3->extcon = devm_extcon_dev_allocate(&pdev->dev, renesas_usb3_cable);
	अगर (IS_ERR(usb3->extcon))
		वापस PTR_ERR(usb3->extcon);

	ret = devm_extcon_dev_रेजिस्टर(&pdev->dev, usb3->extcon);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register extcon\n");
		वापस ret;
	पूर्ण

	/* क्रम ep0 handling */
	usb3->ep0_req = __renesas_usb3_ep_alloc_request(GFP_KERNEL);
	अगर (!usb3->ep0_req)
		वापस -ENOMEM;

	ret = renesas_usb3_dma_alloc_prd(usb3, &pdev->dev);
	अगर (ret < 0)
		जाओ err_alloc_prd;

	/*
	 * This is optional. So, अगर this driver cannot get a phy,
	 * this driver will not handle a phy anymore.
	 */
	usb3->phy = devm_phy_optional_get(&pdev->dev, "usb");
	अगर (IS_ERR(usb3->phy)) अणु
		ret = PTR_ERR(usb3->phy);
		जाओ err_add_udc;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	ret = usb_add_gadget_udc(&pdev->dev, &usb3->gadget);
	अगर (ret < 0)
		जाओ err_add_udc;

	ret = device_create_file(&pdev->dev, &dev_attr_role);
	अगर (ret < 0)
		जाओ err_dev_create;

	अगर (device_property_पढ़ो_bool(&pdev->dev, "usb-role-switch")) अणु
		usb3->role_sw_by_connector = true;
		renesas_usb3_role_चयन_desc.fwnode = dev_fwnode(&pdev->dev);
	पूर्ण

	renesas_usb3_role_चयन_desc.driver_data = usb3;

	INIT_WORK(&usb3->role_work, renesas_usb3_role_work);
	usb3->role_sw = usb_role_चयन_रेजिस्टर(&pdev->dev,
					&renesas_usb3_role_चयन_desc);
	अगर (!IS_ERR(usb3->role_sw)) अणु
		usb3->host_dev = usb_of_get_companion_dev(&pdev->dev);
		अगर (!usb3->host_dev) अणु
			/* If not found, this driver will not use a role sw */
			usb_role_चयन_unरेजिस्टर(usb3->role_sw);
			usb3->role_sw = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		usb3->role_sw = शून्य;
	पूर्ण

	usb3->workaround_क्रम_vbus = priv->workaround_क्रम_vbus;

	renesas_usb3_debugfs_init(usb3, &pdev->dev);

	dev_info(&pdev->dev, "probed%s\n", usb3->phy ? " with phy" : "");

	वापस 0;

err_dev_create:
	usb_del_gadget_udc(&usb3->gadget);

err_add_udc:
	renesas_usb3_dma_मुक्त_prd(usb3, &pdev->dev);

err_alloc_prd:
	__renesas_usb3_ep_मुक्त_request(usb3->ep0_req);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक renesas_usb3_suspend(काष्ठा device *dev)
अणु
	काष्ठा renesas_usb3 *usb3 = dev_get_drvdata(dev);

	/* Not started */
	अगर (!usb3->driver)
		वापस 0;

	renesas_usb3_stop_controller(usb3);
	अगर (usb3->phy)
		phy_निकास(usb3->phy);
	pm_runसमय_put(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_usb3_resume(काष्ठा device *dev)
अणु
	काष्ठा renesas_usb3 *usb3 = dev_get_drvdata(dev);

	/* Not started */
	अगर (!usb3->driver)
		वापस 0;

	अगर (usb3->phy)
		phy_init(usb3->phy);
	pm_runसमय_get_sync(dev);
	renesas_usb3_init_controller(usb3);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(renesas_usb3_pm_ops, renesas_usb3_suspend,
			renesas_usb3_resume);

अटल काष्ठा platक्रमm_driver renesas_usb3_driver = अणु
	.probe		= renesas_usb3_probe,
	.हटाओ		= renesas_usb3_हटाओ,
	.driver		= अणु
		.name =	udc_name,
		.pm		= &renesas_usb3_pm_ops,
		.of_match_table = of_match_ptr(usb3_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(renesas_usb3_driver);

MODULE_DESCRIPTION("Renesas USB3.0 Peripheral driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>");
MODULE_ALIAS("platform:renesas_usb3");

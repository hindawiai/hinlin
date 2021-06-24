<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB Peripheral Controller driver क्रम Aeroflex Gaisler GRUSBDC.
 *
 * 2013 (c) Aeroflex Gaisler AB
 *
 * This driver supports GRUSBDC USB Device Controller cores available in the
 * GRLIB VHDL IP core library.
 *
 * Full करोcumentation of the GRUSBDC core can be found here:
 * https://www.gaisler.com/products/grlib/grip.pdf
 *
 * Contributors:
 * - Andreas Larsson <andreas@gaisler.com>
 * - Marko Isomaki
 */

/* Control रेजिस्टरs on the AMBA bus */

#घोषणा GR_MAXEP	16	/* Max # endpoपूर्णांकs क्रम *each* direction */

काष्ठा gr_epregs अणु
	u32 epctrl;
	जोड़ अणु
		काष्ठा अणु /* Slave mode*/
			u32 slvctrl;
			u32 slvdata;
		पूर्ण;
		काष्ठा अणु /* DMA mode*/
			u32 dmactrl;
			u32 dmaaddr;
		पूर्ण;
	पूर्ण;
	u32 epstat;
पूर्ण;

काष्ठा gr_regs अणु
	काष्ठा gr_epregs	epo[GR_MAXEP];	/* 0x000 - 0x0fc */
	काष्ठा gr_epregs	epi[GR_MAXEP];	/* 0x100 - 0x1fc */
	u32			control;	/* 0x200 */
	u32			status;		/* 0x204 */
पूर्ण;

#घोषणा GR_EPCTRL_BUFSZ_SCALER	8
#घोषणा GR_EPCTRL_BUFSZ_MASK	0xffe00000
#घोषणा GR_EPCTRL_BUFSZ_POS	21
#घोषणा GR_EPCTRL_PI		BIT(20)
#घोषणा GR_EPCTRL_CB		BIT(19)
#घोषणा GR_EPCTRL_CS		BIT(18)
#घोषणा GR_EPCTRL_MAXPL_MASK	0x0003ff80
#घोषणा GR_EPCTRL_MAXPL_POS	7
#घोषणा GR_EPCTRL_NT_MASK	0x00000060
#घोषणा GR_EPCTRL_NT_POS	5
#घोषणा GR_EPCTRL_TT_MASK	0x00000018
#घोषणा GR_EPCTRL_TT_POS	3
#घोषणा GR_EPCTRL_EH		BIT(2)
#घोषणा GR_EPCTRL_ED		BIT(1)
#घोषणा GR_EPCTRL_EV		BIT(0)

#घोषणा GR_DMACTRL_AE		BIT(10)
#घोषणा GR_DMACTRL_AD		BIT(3)
#घोषणा GR_DMACTRL_AI		BIT(2)
#घोषणा GR_DMACTRL_IE		BIT(1)
#घोषणा GR_DMACTRL_DA		BIT(0)

#घोषणा GR_EPSTAT_PT		BIT(29)
#घोषणा GR_EPSTAT_PR		BIT(29)
#घोषणा GR_EPSTAT_B1CNT_MASK	0x1fff0000
#घोषणा GR_EPSTAT_B1CNT_POS	16
#घोषणा GR_EPSTAT_B0CNT_MASK	0x0000fff8
#घोषणा GR_EPSTAT_B0CNT_POS	3
#घोषणा GR_EPSTAT_B1		BIT(2)
#घोषणा GR_EPSTAT_B0		BIT(1)
#घोषणा GR_EPSTAT_BS		BIT(0)

#घोषणा GR_CONTROL_SI		BIT(31)
#घोषणा GR_CONTROL_UI		BIT(30)
#घोषणा GR_CONTROL_VI		BIT(29)
#घोषणा GR_CONTROL_SP		BIT(28)
#घोषणा GR_CONTROL_FI		BIT(27)
#घोषणा GR_CONTROL_EP		BIT(14)
#घोषणा GR_CONTROL_DH		BIT(13)
#घोषणा GR_CONTROL_RW		BIT(12)
#घोषणा GR_CONTROL_TS_MASK	0x00000e00
#घोषणा GR_CONTROL_TS_POS	9
#घोषणा GR_CONTROL_TM		BIT(8)
#घोषणा GR_CONTROL_UA_MASK	0x000000fe
#घोषणा GR_CONTROL_UA_POS	1
#घोषणा GR_CONTROL_SU		BIT(0)

#घोषणा GR_STATUS_NEPI_MASK	0xf0000000
#घोषणा GR_STATUS_NEPI_POS	28
#घोषणा GR_STATUS_NEPO_MASK	0x0f000000
#घोषणा GR_STATUS_NEPO_POS	24
#घोषणा GR_STATUS_DM		BIT(23)
#घोषणा GR_STATUS_SU		BIT(17)
#घोषणा GR_STATUS_UR		BIT(16)
#घोषणा GR_STATUS_VB		BIT(15)
#घोषणा GR_STATUS_SP		BIT(14)
#घोषणा GR_STATUS_AF_MASK	0x00003800
#घोषणा GR_STATUS_AF_POS	11
#घोषणा GR_STATUS_FN_MASK	0x000007ff
#घोषणा GR_STATUS_FN_POS	0


#घोषणा MAX_CTRL_PL_SIZE 64 /* As per USB standard क्रम full and high speed */

/*-------------------------------------------------------------------------*/

/* Driver data काष्ठाures and utilities */

काष्ठा gr_dma_desc अणु
	u32 ctrl;
	u32 data;
	u32 next;

	/* These must be last because hw uses the previous three */
	u32 paddr;
	काष्ठा gr_dma_desc *next_desc;
पूर्ण;

#घोषणा GR_DESC_OUT_CTRL_SE		BIT(17)
#घोषणा GR_DESC_OUT_CTRL_IE		BIT(15)
#घोषणा GR_DESC_OUT_CTRL_NX		BIT(14)
#घोषणा GR_DESC_OUT_CTRL_EN		BIT(13)
#घोषणा GR_DESC_OUT_CTRL_LEN_MASK	0x00001fff

#घोषणा GR_DESC_IN_CTRL_MO		BIT(18)
#घोषणा GR_DESC_IN_CTRL_PI		BIT(17)
#घोषणा GR_DESC_IN_CTRL_ML		BIT(16)
#घोषणा GR_DESC_IN_CTRL_IE		BIT(15)
#घोषणा GR_DESC_IN_CTRL_NX		BIT(14)
#घोषणा GR_DESC_IN_CTRL_EN		BIT(13)
#घोषणा GR_DESC_IN_CTRL_LEN_MASK	0x00001fff

#घोषणा GR_DESC_DMAADDR_MASK		0xfffffffc

काष्ठा gr_ep अणु
	काष्ठा usb_ep ep;
	काष्ठा gr_udc *dev;
	u16 bytes_per_buffer;
	अचिन्हित पूर्णांक dma_start;
	काष्ठा gr_epregs __iomem *regs;

	अचिन्हित num:8;
	अचिन्हित is_in:1;
	अचिन्हित stopped:1;
	अचिन्हित wedged:1;
	अचिन्हित callback:1;

	/* analogous to a host-side qh */
	काष्ठा list_head queue;

	काष्ठा list_head ep_list;

	/* Bounce buffer क्रम end of "odd" sized OUT requests */
	व्योम *tailbuf;
	dma_addr_t tailbuf_paddr;
पूर्ण;

काष्ठा gr_request अणु
	काष्ठा usb_request req;
	काष्ठा list_head queue;

	/* Chain of dma descriptors */
	काष्ठा gr_dma_desc *first_desc; /* First in the chain */
	काष्ठा gr_dma_desc *curr_desc; /* Current descriptor */
	काष्ठा gr_dma_desc *last_desc; /* Last in the chain */

	u16 evenlen; /* Size of even length head (अगर oddlen != 0) */
	u16 oddlen; /* Size of odd length tail अगर buffer length is "odd" */

	u8 setup; /* Setup packet */
पूर्ण;

क्रमागत gr_ep0state अणु
	GR_EP0_DISCONNECT = 0,	/* No host */
	GR_EP0_SETUP,		/* Between STATUS ack and SETUP report */
	GR_EP0_IDATA,		/* IN data stage */
	GR_EP0_ODATA,		/* OUT data stage */
	GR_EP0_ISTATUS,		/* Status stage after IN data stage */
	GR_EP0_OSTATUS,		/* Status stage after OUT data stage */
	GR_EP0_STALL,		/* Data or status stages */
	GR_EP0_SUSPEND,		/* USB suspend */
पूर्ण;

काष्ठा gr_udc अणु
	काष्ठा usb_gadget gadget;
	काष्ठा gr_ep epi[GR_MAXEP];
	काष्ठा gr_ep epo[GR_MAXEP];
	काष्ठा usb_gadget_driver *driver;
	काष्ठा dma_pool *desc_pool;
	काष्ठा device *dev;

	क्रमागत gr_ep0state ep0state;
	काष्ठा gr_request *ep0reqo;
	काष्ठा gr_request *ep0reqi;

	काष्ठा gr_regs __iomem *regs;
	पूर्णांक irq;
	पूर्णांक irqi;
	पूर्णांक irqo;

	अचिन्हित added:1;
	अचिन्हित irq_enabled:1;
	अचिन्हित remote_wakeup:1;

	u8 test_mode;

	क्रमागत usb_device_state suspended_from;

	अचिन्हित पूर्णांक nepi;
	अचिन्हित पूर्णांक nepo;

	काष्ठा list_head ep_list;

	spinlock_t lock; /* General lock, a.k.a. "dev->lock" in comments */

	काष्ठा dentry *dfs_root;
पूर्ण;

#घोषणा to_gr_udc(gadget)	(container_of((gadget), काष्ठा gr_udc, gadget))

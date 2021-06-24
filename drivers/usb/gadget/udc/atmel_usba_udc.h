<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Aपंचांगel USBA high speed USB device controller
 *
 * Copyright (C) 2005-2007 Aपंचांगel Corporation
 */
#अगर_अघोषित __LINUX_USB_GADGET_USBA_UDC_H__
#घोषणा __LINUX_USB_GADGET_USBA_UDC_H__

#समावेश <linux/gpio/consumer.h>

/* USB रेजिस्टर offsets */
#घोषणा USBA_CTRL				0x0000
#घोषणा USBA_FNUM				0x0004
#घोषणा USBA_INT_ENB				0x0010
#घोषणा USBA_INT_STA				0x0014
#घोषणा USBA_INT_CLR				0x0018
#घोषणा USBA_EPT_RST				0x001c
#घोषणा USBA_TST				0x00e0

/* USB endpoपूर्णांक रेजिस्टर offsets */
#घोषणा USBA_EPT_CFG				0x0000
#घोषणा USBA_EPT_CTL_ENB			0x0004
#घोषणा USBA_EPT_CTL_DIS			0x0008
#घोषणा USBA_EPT_CTL				0x000c
#घोषणा USBA_EPT_SET_STA			0x0014
#घोषणा USBA_EPT_CLR_STA			0x0018
#घोषणा USBA_EPT_STA				0x001c

/* USB DMA रेजिस्टर offsets */
#घोषणा USBA_DMA_NXT_DSC			0x0000
#घोषणा USBA_DMA_ADDRESS			0x0004
#घोषणा USBA_DMA_CONTROL			0x0008
#घोषणा USBA_DMA_STATUS				0x000c

/* Bitfields in CTRL */
#घोषणा USBA_DEV_ADDR_OFFSET			0
#घोषणा USBA_DEV_ADDR_SIZE			7
#घोषणा USBA_FADDR_EN				(1 <<  7)
#घोषणा USBA_EN_USBA				(1 <<  8)
#घोषणा USBA_DETACH				(1 <<  9)
#घोषणा USBA_REMOTE_WAKE_UP			(1 << 10)
#घोषणा USBA_PULLD_DIS				(1 << 11)

#घोषणा USBA_ENABLE_MASK			(USBA_EN_USBA | USBA_PULLD_DIS)
#घोषणा USBA_DISABLE_MASK			USBA_DETACH

/* Bitfields in FNUM */
#घोषणा USBA_MICRO_FRAME_NUM_OFFSET		0
#घोषणा USBA_MICRO_FRAME_NUM_SIZE		3
#घोषणा USBA_FRAME_NUMBER_OFFSET		3
#घोषणा USBA_FRAME_NUMBER_SIZE			11
#घोषणा USBA_FRAME_NUM_ERROR			(1 << 31)

/* Bitfields in INT_ENB/INT_STA/INT_CLR */
#घोषणा USBA_HIGH_SPEED				(1 <<  0)
#घोषणा USBA_DET_SUSPEND			(1 <<  1)
#घोषणा USBA_MICRO_SOF				(1 <<  2)
#घोषणा USBA_SOF				(1 <<  3)
#घोषणा USBA_END_OF_RESET			(1 <<  4)
#घोषणा USBA_WAKE_UP				(1 <<  5)
#घोषणा USBA_END_OF_RESUME			(1 <<  6)
#घोषणा USBA_UPSTREAM_RESUME			(1 <<  7)
#घोषणा USBA_EPT_INT_OFFSET			8
#घोषणा USBA_EPT_INT_SIZE			16
#घोषणा USBA_DMA_INT_OFFSET			24
#घोषणा USBA_DMA_INT_SIZE			8

/* Bitfields in EPT_RST */
#घोषणा USBA_RST_OFFSET				0
#घोषणा USBA_RST_SIZE				16

/* Bitfields in USBA_TST */
#घोषणा USBA_SPEED_CFG_OFFSET			0
#घोषणा USBA_SPEED_CFG_SIZE			2
#घोषणा USBA_TST_J_MODE				(1 <<  2)
#घोषणा USBA_TST_K_MODE				(1 <<  3)
#घोषणा USBA_TST_PKT_MODE			(1 <<  4)
#घोषणा USBA_OPMODE2				(1 <<  5)

/* Bitfields in EPT_CFG */
#घोषणा USBA_EPT_SIZE_OFFSET			0
#घोषणा USBA_EPT_SIZE_SIZE			3
#घोषणा USBA_EPT_सूची_IN				(1 <<  3)
#घोषणा USBA_EPT_TYPE_OFFSET			4
#घोषणा USBA_EPT_TYPE_SIZE			2
#घोषणा USBA_BK_NUMBER_OFFSET			6
#घोषणा USBA_BK_NUMBER_SIZE			2
#घोषणा USBA_NB_TRANS_OFFSET			8
#घोषणा USBA_NB_TRANS_SIZE			2
#घोषणा USBA_EPT_MAPPED				(1 << 31)

/* Bitfields in EPT_CTL/EPT_CTL_ENB/EPT_CTL_DIS */
#घोषणा USBA_EPT_ENABLE				(1 <<  0)
#घोषणा USBA_AUTO_VALID				(1 <<  1)
#घोषणा USBA_INTDIS_DMA				(1 <<  3)
#घोषणा USBA_NYET_DIS				(1 <<  4)
#घोषणा USBA_DATAX_RX				(1 <<  6)
#घोषणा USBA_MDATA_RX				(1 <<  7)
/* Bits 8-15 and 31 enable पूर्णांकerrupts क्रम respective bits in EPT_STA */
#घोषणा USBA_BUSY_BANK_IE			(1 << 18)

/* Bitfields in EPT_SET_STA/EPT_CLR_STA/EPT_STA */
#घोषणा USBA_FORCE_STALL			(1 <<  5)
#घोषणा USBA_TOGGLE_CLR				(1 <<  6)
#घोषणा USBA_TOGGLE_SEQ_OFFSET			6
#घोषणा USBA_TOGGLE_SEQ_SIZE			2
#घोषणा USBA_ERR_OVFLW				(1 <<  8)
#घोषणा USBA_RX_BK_RDY				(1 <<  9)
#घोषणा USBA_KILL_BANK				(1 <<  9)
#घोषणा USBA_TX_COMPLETE			(1 << 10)
#घोषणा USBA_TX_PK_RDY				(1 << 11)
#घोषणा USBA_ISO_ERR_TRANS			(1 << 11)
#घोषणा USBA_RX_SETUP				(1 << 12)
#घोषणा USBA_ISO_ERR_FLOW			(1 << 12)
#घोषणा USBA_STALL_SENT				(1 << 13)
#घोषणा USBA_ISO_ERR_CRC			(1 << 13)
#घोषणा USBA_ISO_ERR_NBTRANS			(1 << 13)
#घोषणा USBA_NAK_IN				(1 << 14)
#घोषणा USBA_ISO_ERR_FLUSH			(1 << 14)
#घोषणा USBA_NAK_OUT				(1 << 15)
#घोषणा USBA_CURRENT_BANK_OFFSET		16
#घोषणा USBA_CURRENT_BANK_SIZE			2
#घोषणा USBA_BUSY_BANKS_OFFSET			18
#घोषणा USBA_BUSY_BANKS_SIZE			2
#घोषणा USBA_BYTE_COUNT_OFFSET			20
#घोषणा USBA_BYTE_COUNT_SIZE			11
#घोषणा USBA_SHORT_PACKET			(1 << 31)

/* Bitfields in DMA_CONTROL */
#घोषणा USBA_DMA_CH_EN				(1 <<  0)
#घोषणा USBA_DMA_LINK				(1 <<  1)
#घोषणा USBA_DMA_END_TR_EN			(1 <<  2)
#घोषणा USBA_DMA_END_BUF_EN			(1 <<  3)
#घोषणा USBA_DMA_END_TR_IE			(1 <<  4)
#घोषणा USBA_DMA_END_BUF_IE			(1 <<  5)
#घोषणा USBA_DMA_DESC_LOAD_IE			(1 <<  6)
#घोषणा USBA_DMA_BURST_LOCK			(1 <<  7)
#घोषणा USBA_DMA_BUF_LEN_OFFSET			16
#घोषणा USBA_DMA_BUF_LEN_SIZE			16

/* Bitfields in DMA_STATUS */
#घोषणा USBA_DMA_CH_ACTIVE			(1 <<  1)
#घोषणा USBA_DMA_END_TR_ST			(1 <<  4)
#घोषणा USBA_DMA_END_BUF_ST			(1 <<  5)
#घोषणा USBA_DMA_DESC_LOAD_ST			(1 <<  6)

/* Constants क्रम SPEED_CFG */
#घोषणा USBA_SPEED_CFG_NORMAL			0
#घोषणा USBA_SPEED_CFG_FORCE_HIGH		2
#घोषणा USBA_SPEED_CFG_FORCE_FULL		3

/* Constants क्रम EPT_SIZE */
#घोषणा USBA_EPT_SIZE_8				0
#घोषणा USBA_EPT_SIZE_16			1
#घोषणा USBA_EPT_SIZE_32			2
#घोषणा USBA_EPT_SIZE_64			3
#घोषणा USBA_EPT_SIZE_128			4
#घोषणा USBA_EPT_SIZE_256			5
#घोषणा USBA_EPT_SIZE_512			6
#घोषणा USBA_EPT_SIZE_1024			7

/* Constants क्रम EPT_TYPE */
#घोषणा USBA_EPT_TYPE_CONTROL			0
#घोषणा USBA_EPT_TYPE_ISO			1
#घोषणा USBA_EPT_TYPE_BULK			2
#घोषणा USBA_EPT_TYPE_INT			3

/* Constants क्रम BK_NUMBER */
#घोषणा USBA_BK_NUMBER_ZERO			0
#घोषणा USBA_BK_NUMBER_ONE			1
#घोषणा USBA_BK_NUMBER_DOUBLE			2
#घोषणा USBA_BK_NUMBER_TRIPLE			3

/* Bit manipulation macros */
#घोषणा USBA_BF(name, value)					\
	(((value) & ((1 << USBA_##name##_SIZE) - 1))		\
	 << USBA_##name##_OFFSET)
#घोषणा USBA_BFEXT(name, value)					\
	(((value) >> USBA_##name##_OFFSET)			\
	 & ((1 << USBA_##name##_SIZE) - 1))
#घोषणा USBA_BFINS(name, value, old)				\
	(((old) & ~(((1 << USBA_##name##_SIZE) - 1)		\
		    << USBA_##name##_OFFSET))			\
	 | USBA_BF(name, value))

/* Register access macros */
#घोषणा usba_पढ़ोl(udc, reg)					\
	पढ़ोl_relaxed((udc)->regs + USBA_##reg)
#घोषणा usba_ग_लिखोl(udc, reg, value)				\
	ग_लिखोl_relaxed((value), (udc)->regs + USBA_##reg)
#घोषणा usba_ep_पढ़ोl(ep, reg)					\
	पढ़ोl_relaxed((ep)->ep_regs + USBA_EPT_##reg)
#घोषणा usba_ep_ग_लिखोl(ep, reg, value)				\
	ग_लिखोl_relaxed((value), (ep)->ep_regs + USBA_EPT_##reg)
#घोषणा usba_dma_पढ़ोl(ep, reg)					\
	पढ़ोl_relaxed((ep)->dma_regs + USBA_DMA_##reg)
#घोषणा usba_dma_ग_लिखोl(ep, reg, value)				\
	ग_लिखोl_relaxed((value), (ep)->dma_regs + USBA_DMA_##reg)

/* Calculate base address क्रम a given endpoपूर्णांक or DMA controller */
#घोषणा USBA_EPT_BASE(x)	(0x100 + (x) * 0x20)
#घोषणा USBA_DMA_BASE(x)	(0x300 + (x) * 0x10)
#घोषणा USBA_FIFO_BASE(x)	((x) << 16)

/* Synth parameters */
#घोषणा USBA_NR_DMAS		7

#घोषणा EP0_FIFO_SIZE		64
#घोषणा EP0_EPT_SIZE		USBA_EPT_SIZE_64
#घोषणा EP0_NR_BANKS		1

#घोषणा FIFO_IOMEM_ID	0
#घोषणा CTRL_IOMEM_ID	1

#घोषणा DBG_ERR		0x0001	/* report all error वापसs */
#घोषणा DBG_HW		0x0002	/* debug hardware initialization */
#घोषणा DBG_GADGET	0x0004	/* calls to/from gadget driver */
#घोषणा DBG_INT		0x0008	/* पूर्णांकerrupts */
#घोषणा DBG_BUS		0x0010	/* report changes in bus state */
#घोषणा DBG_QUEUE	0x0020  /* debug request queue processing */
#घोषणा DBG_FIFO	0x0040  /* debug FIFO contents */
#घोषणा DBG_DMA		0x0080  /* debug DMA handling */
#घोषणा DBG_REQ		0x0100	/* prपूर्णांक out queued request length */
#घोषणा DBG_ALL		0xffff
#घोषणा DBG_NONE	0x0000

#घोषणा DEBUG_LEVEL	(DBG_ERR)

#घोषणा DBG(level, fmt, ...)					\
	करो अणु							\
		अगर ((level) & DEBUG_LEVEL)			\
			pr_debug("udc: " fmt, ## __VA_ARGS__);	\
	पूर्ण जबतक (0)

क्रमागत usba_ctrl_state अणु
	WAIT_FOR_SETUP,
	DATA_STAGE_IN,
	DATA_STAGE_OUT,
	STATUS_STAGE_IN,
	STATUS_STAGE_OUT,
	STATUS_STAGE_ADDR,
	STATUS_STAGE_TEST,
पूर्ण;
/*
  EP_STATE_IDLE,
  EP_STATE_SETUP,
  EP_STATE_IN_DATA,
  EP_STATE_OUT_DATA,
  EP_STATE_SET_ADDR_STATUS,
  EP_STATE_RX_STATUS,
  EP_STATE_TX_STATUS,
  EP_STATE_HALT,
*/

काष्ठा usba_dma_desc अणु
	dma_addr_t next;
	dma_addr_t addr;
	u32 ctrl;
पूर्ण;

काष्ठा usba_fअगरo_cfg अणु
	u8			hw_ep_num;
	u16			fअगरo_size;
	u8			nr_banks;
पूर्ण;

काष्ठा usba_ep अणु
	पूर्णांक					state;
	व्योम __iomem				*ep_regs;
	व्योम __iomem				*dma_regs;
	व्योम __iomem				*fअगरo;
	अक्षर					name[8];
	काष्ठा usb_ep				ep;
	काष्ठा usba_udc				*udc;

	काष्ठा list_head			queue;

	u16					fअगरo_size;
	u8					nr_banks;
	u8					index;
	अचिन्हित पूर्णांक				can_dma:1;
	अचिन्हित पूर्णांक				can_isoc:1;
	अचिन्हित पूर्णांक				is_isoc:1;
	अचिन्हित पूर्णांक				is_in:1;
	अचिन्हित दीर्घ				ept_cfg;
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS
	u32					last_dma_status;
	काष्ठा dentry				*debugfs_dir;
#पूर्ण_अगर
पूर्ण;

काष्ठा usba_ep_config अणु
	u8					nr_banks;
	अचिन्हित पूर्णांक				can_dma:1;
	अचिन्हित पूर्णांक				can_isoc:1;
पूर्ण;

काष्ठा usba_request अणु
	काष्ठा usb_request			req;
	काष्ठा list_head			queue;

	u32					ctrl;

	अचिन्हित पूर्णांक				submitted:1;
	अचिन्हित पूर्णांक				last_transaction:1;
	अचिन्हित पूर्णांक				using_dma:1;
	अचिन्हित पूर्णांक				mapped:1;
पूर्ण;

काष्ठा usba_udc_errata अणु
	व्योम (*toggle_bias)(काष्ठा usba_udc *udc, पूर्णांक is_on);
	व्योम (*pulse_bias)(काष्ठा usba_udc *udc);
पूर्ण;

काष्ठा usba_udc_config अणु
	स्थिर काष्ठा usba_udc_errata *errata;
	स्थिर काष्ठा usba_ep_config *config;
	स्थिर पूर्णांक num_ep;
	स्थिर bool ep_pपुनः_स्मृति;
पूर्ण;

काष्ठा usba_udc अणु
	/* Protect hw रेजिस्टरs from concurrent modअगरications */
	spinlock_t lock;

	/* Mutex to prevent concurrent start or stop */
	काष्ठा mutex vbus_mutex;

	व्योम __iomem *regs;
	व्योम __iomem *fअगरo;

	काष्ठा usb_gadget gadget;
	काष्ठा usb_gadget_driver *driver;
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा usba_udc_errata *errata;
	पूर्णांक irq;
	काष्ठा gpio_desc *vbus_pin;
	पूर्णांक num_ep;
	काष्ठा usba_fअगरo_cfg *fअगरo_cfg;
	काष्ठा clk *pclk;
	काष्ठा clk *hclk;
	काष्ठा usba_ep *usba_ep;
	bool bias_pulse_needed;
	bool घड़ीed;
	bool suspended;
	bool ep_pपुनः_स्मृति;

	u16 devstatus;

	u16 test_mode;
	पूर्णांक vbus_prev;

	u32 पूर्णांक_enb_cache;

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS
	काष्ठा dentry *debugfs_root;
#पूर्ण_अगर

	काष्ठा regmap *pmc;
पूर्ण;

अटल अंतरभूत काष्ठा usba_ep *to_usba_ep(काष्ठा usb_ep *ep)
अणु
	वापस container_of(ep, काष्ठा usba_ep, ep);
पूर्ण

अटल अंतरभूत काष्ठा usba_request *to_usba_req(काष्ठा usb_request *req)
अणु
	वापस container_of(req, काष्ठा usba_request, req);
पूर्ण

अटल अंतरभूत काष्ठा usba_udc *to_usba_udc(काष्ठा usb_gadget *gadget)
अणु
	वापस container_of(gadget, काष्ठा usba_udc, gadget);
पूर्ण

#घोषणा ep_is_control(ep)	((ep)->index == 0)
#घोषणा ep_is_idle(ep)		((ep)->state == EP_STATE_IDLE)

#पूर्ण_अगर /* __LINUX_USB_GADGET_USBA_UDC_H */

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 LAPIS Semiconductor Co., Ltd.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/irq.h>

#घोषणा PCH_VBUS_PERIOD		3000	/* VBUS polling period (msec) */
#घोषणा PCH_VBUS_INTERVAL	10	/* VBUS polling पूर्णांकerval (msec) */

/* Address offset of Registers */
#घोषणा UDC_EP_REG_SHIFT	0x20	/* Offset to next EP */

#घोषणा UDC_EPCTL_ADDR		0x00	/* Endpoपूर्णांक control */
#घोषणा UDC_EPSTS_ADDR		0x04	/* Endpoपूर्णांक status */
#घोषणा UDC_BUFIN_FRAMENUM_ADDR	0x08	/* buffer size in / frame number out */
#घोषणा UDC_BUFOUT_MAXPKT_ADDR	0x0C	/* buffer size out / maxpkt in */
#घोषणा UDC_SUBPTR_ADDR		0x10	/* setup buffer poपूर्णांकer */
#घोषणा UDC_DESPTR_ADDR		0x14	/* Data descriptor poपूर्णांकer */
#घोषणा UDC_CONFIRM_ADDR	0x18	/* Write/Read confirmation */

#घोषणा UDC_DEVCFG_ADDR		0x400	/* Device configuration */
#घोषणा UDC_DEVCTL_ADDR		0x404	/* Device control */
#घोषणा UDC_DEVSTS_ADDR		0x408	/* Device status */
#घोषणा UDC_DEVIRQSTS_ADDR	0x40C	/* Device irq status */
#घोषणा UDC_DEVIRQMSK_ADDR	0x410	/* Device irq mask */
#घोषणा UDC_EPIRQSTS_ADDR	0x414	/* Endpoपूर्णांक irq status */
#घोषणा UDC_EPIRQMSK_ADDR	0x418	/* Endpoपूर्णांक irq mask */
#घोषणा UDC_DEVLPM_ADDR		0x41C	/* LPM control / status */
#घोषणा UDC_CSR_BUSY_ADDR	0x4f0	/* UDC_CSR_BUSY Status रेजिस्टर */
#घोषणा UDC_SRST_ADDR		0x4fc	/* SOFT RESET रेजिस्टर */
#घोषणा UDC_CSR_ADDR		0x500	/* USB_DEVICE endpoपूर्णांक रेजिस्टर */

/* Endpoपूर्णांक control रेजिस्टर */
/* Bit position */
#घोषणा UDC_EPCTL_MRXFLUSH		(1 << 12)
#घोषणा UDC_EPCTL_RRDY			(1 << 9)
#घोषणा UDC_EPCTL_CNAK			(1 << 8)
#घोषणा UDC_EPCTL_SNAK			(1 << 7)
#घोषणा UDC_EPCTL_NAK			(1 << 6)
#घोषणा UDC_EPCTL_P			(1 << 3)
#घोषणा UDC_EPCTL_F			(1 << 1)
#घोषणा UDC_EPCTL_S			(1 << 0)
#घोषणा UDC_EPCTL_ET_SHIFT		4
/* Mask patern */
#घोषणा UDC_EPCTL_ET_MASK		0x00000030
/* Value क्रम ET field */
#घोषणा UDC_EPCTL_ET_CONTROL		0
#घोषणा UDC_EPCTL_ET_ISO		1
#घोषणा UDC_EPCTL_ET_BULK		2
#घोषणा UDC_EPCTL_ET_INTERRUPT		3

/* Endpoपूर्णांक status रेजिस्टर */
/* Bit position */
#घोषणा UDC_EPSTS_XFERDONE		(1 << 27)
#घोषणा UDC_EPSTS_RSS			(1 << 26)
#घोषणा UDC_EPSTS_RCS			(1 << 25)
#घोषणा UDC_EPSTS_TXEMPTY		(1 << 24)
#घोषणा UDC_EPSTS_TDC			(1 << 10)
#घोषणा UDC_EPSTS_HE			(1 << 9)
#घोषणा UDC_EPSTS_MRXFIFO_EMP		(1 << 8)
#घोषणा UDC_EPSTS_BNA			(1 << 7)
#घोषणा UDC_EPSTS_IN			(1 << 6)
#घोषणा UDC_EPSTS_OUT_SHIFT		4
/* Mask patern */
#घोषणा UDC_EPSTS_OUT_MASK		0x00000030
#घोषणा UDC_EPSTS_ALL_CLR_MASK		0x1F0006F0
/* Value क्रम OUT field */
#घोषणा UDC_EPSTS_OUT_SETUP		2
#घोषणा UDC_EPSTS_OUT_DATA		1

/* Device configuration रेजिस्टर */
/* Bit position */
#घोषणा UDC_DEVCFG_CSR_PRG		(1 << 17)
#घोषणा UDC_DEVCFG_SP			(1 << 3)
/* SPD Valee */
#घोषणा UDC_DEVCFG_SPD_HS		0x0
#घोषणा UDC_DEVCFG_SPD_FS		0x1
#घोषणा UDC_DEVCFG_SPD_LS		0x2

/* Device control रेजिस्टर */
/* Bit position */
#घोषणा UDC_DEVCTL_THLEN_SHIFT		24
#घोषणा UDC_DEVCTL_BRLEN_SHIFT		16
#घोषणा UDC_DEVCTL_CSR_DONE		(1 << 13)
#घोषणा UDC_DEVCTL_SD			(1 << 10)
#घोषणा UDC_DEVCTL_MODE			(1 << 9)
#घोषणा UDC_DEVCTL_BREN			(1 << 8)
#घोषणा UDC_DEVCTL_THE			(1 << 7)
#घोषणा UDC_DEVCTL_DU			(1 << 4)
#घोषणा UDC_DEVCTL_TDE			(1 << 3)
#घोषणा UDC_DEVCTL_RDE			(1 << 2)
#घोषणा UDC_DEVCTL_RES			(1 << 0)

/* Device status रेजिस्टर */
/* Bit position */
#घोषणा UDC_DEVSTS_TS_SHIFT		18
#घोषणा UDC_DEVSTS_ENUM_SPEED_SHIFT	13
#घोषणा UDC_DEVSTS_ALT_SHIFT		8
#घोषणा UDC_DEVSTS_INTF_SHIFT		4
#घोषणा UDC_DEVSTS_CFG_SHIFT		0
/* Mask patern */
#घोषणा UDC_DEVSTS_TS_MASK		0xfffc0000
#घोषणा UDC_DEVSTS_ENUM_SPEED_MASK	0x00006000
#घोषणा UDC_DEVSTS_ALT_MASK		0x00000f00
#घोषणा UDC_DEVSTS_INTF_MASK		0x000000f0
#घोषणा UDC_DEVSTS_CFG_MASK		0x0000000f
/* value क्रम maximum speed क्रम SPEED field */
#घोषणा UDC_DEVSTS_ENUM_SPEED_FULL	1
#घोषणा UDC_DEVSTS_ENUM_SPEED_HIGH	0
#घोषणा UDC_DEVSTS_ENUM_SPEED_LOW	2
#घोषणा UDC_DEVSTS_ENUM_SPEED_FULLX	3

/* Device irq रेजिस्टर */
/* Bit position */
#घोषणा UDC_DEVINT_RWKP			(1 << 7)
#घोषणा UDC_DEVINT_ENUM			(1 << 6)
#घोषणा UDC_DEVINT_SOF			(1 << 5)
#घोषणा UDC_DEVINT_US			(1 << 4)
#घोषणा UDC_DEVINT_UR			(1 << 3)
#घोषणा UDC_DEVINT_ES			(1 << 2)
#घोषणा UDC_DEVINT_SI			(1 << 1)
#घोषणा UDC_DEVINT_SC			(1 << 0)
/* Mask patern */
#घोषणा UDC_DEVINT_MSK			0x7f

/* Endpoपूर्णांक irq रेजिस्टर */
/* Bit position */
#घोषणा UDC_EPINT_IN_SHIFT		0
#घोषणा UDC_EPINT_OUT_SHIFT		16
#घोषणा UDC_EPINT_IN_EP0		(1 << 0)
#घोषणा UDC_EPINT_OUT_EP0		(1 << 16)
/* Mask patern */
#घोषणा UDC_EPINT_MSK_DISABLE_ALL	0xffffffff

/* UDC_CSR_BUSY Status रेजिस्टर */
/* Bit position */
#घोषणा UDC_CSR_BUSY			(1 << 0)

/* SOFT RESET रेजिस्टर */
/* Bit position */
#घोषणा UDC_PSRST			(1 << 1)
#घोषणा UDC_SRST			(1 << 0)

/* USB_DEVICE endpoपूर्णांक रेजिस्टर */
/* Bit position */
#घोषणा UDC_CSR_NE_NUM_SHIFT		0
#घोषणा UDC_CSR_NE_सूची_SHIFT		4
#घोषणा UDC_CSR_NE_TYPE_SHIFT		5
#घोषणा UDC_CSR_NE_CFG_SHIFT		7
#घोषणा UDC_CSR_NE_INTF_SHIFT		11
#घोषणा UDC_CSR_NE_ALT_SHIFT		15
#घोषणा UDC_CSR_NE_MAX_PKT_SHIFT	19
/* Mask patern */
#घोषणा UDC_CSR_NE_NUM_MASK		0x0000000f
#घोषणा UDC_CSR_NE_सूची_MASK		0x00000010
#घोषणा UDC_CSR_NE_TYPE_MASK		0x00000060
#घोषणा UDC_CSR_NE_CFG_MASK		0x00000780
#घोषणा UDC_CSR_NE_INTF_MASK		0x00007800
#घोषणा UDC_CSR_NE_ALT_MASK		0x00078000
#घोषणा UDC_CSR_NE_MAX_PKT_MASK		0x3ff80000

#घोषणा PCH_UDC_CSR(ep)	(UDC_CSR_ADDR + ep*4)
#घोषणा PCH_UDC_EPINT(in, num)\
		(1 << (num + (in ? UDC_EPINT_IN_SHIFT : UDC_EPINT_OUT_SHIFT)))

/* Index of endpoपूर्णांक */
#घोषणा UDC_EP0IN_IDX		0
#घोषणा UDC_EP0OUT_IDX		1
#घोषणा UDC_EPIN_IDX(ep)	(ep * 2)
#घोषणा UDC_EPOUT_IDX(ep)	(ep * 2 + 1)
#घोषणा PCH_UDC_EP0		0
#घोषणा PCH_UDC_EP1		1
#घोषणा PCH_UDC_EP2		2
#घोषणा PCH_UDC_EP3		3

/* Number of endpoपूर्णांक */
#घोषणा PCH_UDC_EP_NUM		32	/* Total number of EPs (16 IN,16 OUT) */
#घोषणा PCH_UDC_USED_EP_NUM	4	/* EP number of EP's really used */
/* Length Value */
#घोषणा PCH_UDC_BRLEN		0x0F	/* Burst length */
#घोषणा PCH_UDC_THLEN		0x1F	/* Threshold length */
/* Value of EP Buffer Size */
#घोषणा UDC_EP0IN_BUFF_SIZE	16
#घोषणा UDC_EPIN_BUFF_SIZE	256
#घोषणा UDC_EP0OUT_BUFF_SIZE	16
#घोषणा UDC_EPOUT_BUFF_SIZE	256
/* Value of EP maximum packet size */
#घोषणा UDC_EP0IN_MAX_PKT_SIZE	64
#घोषणा UDC_EP0OUT_MAX_PKT_SIZE	64
#घोषणा UDC_BULK_MAX_PKT_SIZE	512

/* DMA */
#घोषणा DMA_सूची_RX		1	/* DMA क्रम data receive */
#घोषणा DMA_सूची_TX		2	/* DMA क्रम data transmit */
#घोषणा DMA_ADDR_INVALID	(~(dma_addr_t)0)
#घोषणा UDC_DMA_MAXPACKET	65536	/* maximum packet size क्रम DMA */

/**
 * काष्ठा pch_udc_data_dma_desc - Structure to hold DMA descriptor inक्रमmation
 *				  क्रम data
 * @status:		Status quadlet
 * @reserved:		Reserved
 * @dataptr:		Buffer descriptor
 * @next:		Next descriptor
 */
काष्ठा pch_udc_data_dma_desc अणु
	u32 status;
	u32 reserved;
	u32 dataptr;
	u32 next;
पूर्ण;

/**
 * काष्ठा pch_udc_stp_dma_desc - Structure to hold DMA descriptor inक्रमmation
 *				 क्रम control data
 * @status:	Status
 * @reserved:	Reserved
 * @request:	Control Request
 */
काष्ठा pch_udc_stp_dma_desc अणु
	u32 status;
	u32 reserved;
	काष्ठा usb_ctrlrequest request;
पूर्ण __attribute((packed));

/* DMA status definitions */
/* Buffer status */
#घोषणा PCH_UDC_BUFF_STS	0xC0000000
#घोषणा PCH_UDC_BS_HST_RDY	0x00000000
#घोषणा PCH_UDC_BS_DMA_BSY	0x40000000
#घोषणा PCH_UDC_BS_DMA_DONE	0x80000000
#घोषणा PCH_UDC_BS_HST_BSY	0xC0000000
/*  Rx/Tx Status */
#घोषणा PCH_UDC_RXTX_STS	0x30000000
#घोषणा PCH_UDC_RTS_SUCC	0x00000000
#घोषणा PCH_UDC_RTS_DESERR	0x10000000
#घोषणा PCH_UDC_RTS_BUFERR	0x30000000
/* Last Descriptor Indication */
#घोषणा PCH_UDC_DMA_LAST	0x08000000
/* Number of Rx/Tx Bytes Mask */
#घोषणा PCH_UDC_RXTX_BYTES	0x0000ffff

/**
 * काष्ठा pch_udc_cfg_data - Structure to hold current configuration
 *			     and पूर्णांकerface inक्रमmation
 * @cur_cfg:	current configuration in use
 * @cur_पूर्णांकf:	current पूर्णांकerface in use
 * @cur_alt:	current alt पूर्णांकerface in use
 */
काष्ठा pch_udc_cfg_data अणु
	u16 cur_cfg;
	u16 cur_पूर्णांकf;
	u16 cur_alt;
पूर्ण;

/**
 * काष्ठा pch_udc_ep - Structure holding a PCH USB device Endpoपूर्णांक inक्रमmation
 * @ep:			embedded ep request
 * @td_stp_phys:	क्रम setup request
 * @td_data_phys:	क्रम data request
 * @td_stp:		क्रम setup request
 * @td_data:		क्रम data request
 * @dev:		reference to device काष्ठा
 * @offset_addr:	offset address of ep रेजिस्टर
 * @desc:		क्रम this ep
 * @queue:		queue क्रम requests
 * @num:		endpoपूर्णांक number
 * @in:			endpoपूर्णांक is IN
 * @halted:		endpoपूर्णांक halted?
 * @epsts:		Endpoपूर्णांक status
 */
काष्ठा pch_udc_ep अणु
	काष्ठा usb_ep			ep;
	dma_addr_t			td_stp_phys;
	dma_addr_t			td_data_phys;
	काष्ठा pch_udc_stp_dma_desc	*td_stp;
	काष्ठा pch_udc_data_dma_desc	*td_data;
	काष्ठा pch_udc_dev		*dev;
	अचिन्हित दीर्घ			offset_addr;
	काष्ठा list_head		queue;
	अचिन्हित			num:5,
					in:1,
					halted:1;
	अचिन्हित दीर्घ			epsts;
पूर्ण;

/**
 * काष्ठा pch_vbus_gpio_data - Structure holding GPIO inक्रमmaton
 *					क्रम detecting VBUS
 * @port:		gpio descriptor क्रम the VBUS GPIO
 * @पूर्णांकr:		gpio पूर्णांकerrupt number
 * @irq_work_fall:	Structure क्रम WorkQueue
 * @irq_work_rise:	Structure क्रम WorkQueue
 */
काष्ठा pch_vbus_gpio_data अणु
	काष्ठा gpio_desc	*port;
	पूर्णांक			पूर्णांकr;
	काष्ठा work_काष्ठा	irq_work_fall;
	काष्ठा work_काष्ठा	irq_work_rise;
पूर्ण;

/**
 * काष्ठा pch_udc_dev - Structure holding complete inक्रमmation
 *			of the PCH USB device
 * @gadget:		gadget driver data
 * @driver:		reference to gadget driver bound
 * @pdev:		reference to the PCI device
 * @ep:			array of endpoपूर्णांकs
 * @lock:		protects all state
 * @stall:		stall requested
 * @prot_stall:		protcol stall requested
 * @रेजिस्टरed:		driver रेजिस्टरed with प्रणाली
 * @suspended:		driver in suspended state
 * @connected:		gadget driver associated
 * @vbus_session:	required vbus_session state
 * @set_cfg_not_acked:	pending acknowledgement 4 setup
 * @रुकोing_zlp_ack:	pending acknowledgement 4 ZLP
 * @data_requests:	DMA pool क्रम data requests
 * @stp_requests:	DMA pool क्रम setup requests
 * @dma_addr:		DMA pool क्रम received
 * @setup_data:		Received setup data
 * @base_addr:		क्रम mapped device memory
 * @bar:		PCI BAR used क्रम mapped device memory
 * @cfg_data:		current cfg, पूर्णांकf, and alt in use
 * @vbus_gpio:		GPIO inक्रमmaton क्रम detecting VBUS
 */
काष्ठा pch_udc_dev अणु
	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;
	काष्ठा pci_dev			*pdev;
	काष्ठा pch_udc_ep		ep[PCH_UDC_EP_NUM];
	spinlock_t			lock; /* protects all state */
	अचिन्हित
			stall:1,
			prot_stall:1,
			suspended:1,
			connected:1,
			vbus_session:1,
			set_cfg_not_acked:1,
			रुकोing_zlp_ack:1;
	काष्ठा dma_pool		*data_requests;
	काष्ठा dma_pool		*stp_requests;
	dma_addr_t			dma_addr;
	काष्ठा usb_ctrlrequest		setup_data;
	व्योम __iomem			*base_addr;
	अचिन्हित लघु			bar;
	काष्ठा pch_udc_cfg_data		cfg_data;
	काष्ठा pch_vbus_gpio_data	vbus_gpio;
पूर्ण;
#घोषणा to_pch_udc(g)	(container_of((g), काष्ठा pch_udc_dev, gadget))

#घोषणा PCH_UDC_PCI_BAR_QUARK_X1000	0
#घोषणा PCH_UDC_PCI_BAR			1

#घोषणा PCI_DEVICE_ID_INTEL_QUARK_X1000_UDC	0x0939
#घोषणा PCI_DEVICE_ID_INTEL_EG20T_UDC		0x8808

#घोषणा PCI_DEVICE_ID_ML7213_IOH_UDC	0x801D
#घोषणा PCI_DEVICE_ID_ML7831_IOH_UDC	0x8808

अटल स्थिर अक्षर	ep0_string[] = "ep0in";
अटल DEFINE_SPINLOCK(udc_stall_spinlock);	/* stall spin lock */
अटल bool speed_fs;
module_param_named(speed_fs, speed_fs, bool, S_IRUGO);
MODULE_PARM_DESC(speed_fs, "true for Full speed operation");

/**
 * काष्ठा pch_udc_request - Structure holding a PCH USB device request packet
 * @req:		embedded ep request
 * @td_data_phys:	phys. address
 * @td_data:		first dma desc. of chain
 * @td_data_last:	last dma desc. of chain
 * @queue:		associated queue
 * @dma_going:		DMA in progress क्रम request
 * @dma_करोne:		DMA completed क्रम request
 * @chain_len:		chain length
 */
काष्ठा pch_udc_request अणु
	काष्ठा usb_request		req;
	dma_addr_t			td_data_phys;
	काष्ठा pch_udc_data_dma_desc	*td_data;
	काष्ठा pch_udc_data_dma_desc	*td_data_last;
	काष्ठा list_head		queue;
	अचिन्हित			dma_going:1,
					dma_करोne:1;
	अचिन्हित			chain_len;
पूर्ण;

अटल अंतरभूत u32 pch_udc_पढ़ोl(काष्ठा pch_udc_dev *dev, अचिन्हित दीर्घ reg)
अणु
	वापस ioपढ़ो32(dev->base_addr + reg);
पूर्ण

अटल अंतरभूत व्योम pch_udc_ग_लिखोl(काष्ठा pch_udc_dev *dev,
				    अचिन्हित दीर्घ val, अचिन्हित दीर्घ reg)
अणु
	ioग_लिखो32(val, dev->base_addr + reg);
पूर्ण

अटल अंतरभूत व्योम pch_udc_bit_set(काष्ठा pch_udc_dev *dev,
				     अचिन्हित दीर्घ reg,
				     अचिन्हित दीर्घ biपंचांगask)
अणु
	pch_udc_ग_लिखोl(dev, pch_udc_पढ़ोl(dev, reg) | biपंचांगask, reg);
पूर्ण

अटल अंतरभूत व्योम pch_udc_bit_clr(काष्ठा pch_udc_dev *dev,
				     अचिन्हित दीर्घ reg,
				     अचिन्हित दीर्घ biपंचांगask)
अणु
	pch_udc_ग_लिखोl(dev, pch_udc_पढ़ोl(dev, reg) & ~(biपंचांगask), reg);
पूर्ण

अटल अंतरभूत u32 pch_udc_ep_पढ़ोl(काष्ठा pch_udc_ep *ep, अचिन्हित दीर्घ reg)
अणु
	वापस ioपढ़ो32(ep->dev->base_addr + ep->offset_addr + reg);
पूर्ण

अटल अंतरभूत व्योम pch_udc_ep_ग_लिखोl(काष्ठा pch_udc_ep *ep,
				    अचिन्हित दीर्घ val, अचिन्हित दीर्घ reg)
अणु
	ioग_लिखो32(val, ep->dev->base_addr + ep->offset_addr + reg);
पूर्ण

अटल अंतरभूत व्योम pch_udc_ep_bit_set(काष्ठा pch_udc_ep *ep,
				     अचिन्हित दीर्घ reg,
				     अचिन्हित दीर्घ biपंचांगask)
अणु
	pch_udc_ep_ग_लिखोl(ep, pch_udc_ep_पढ़ोl(ep, reg) | biपंचांगask, reg);
पूर्ण

अटल अंतरभूत व्योम pch_udc_ep_bit_clr(काष्ठा pch_udc_ep *ep,
				     अचिन्हित दीर्घ reg,
				     अचिन्हित दीर्घ biपंचांगask)
अणु
	pch_udc_ep_ग_लिखोl(ep, pch_udc_ep_पढ़ोl(ep, reg) & ~(biपंचांगask), reg);
पूर्ण

/**
 * pch_udc_csr_busy() - Wait till idle.
 * @dev:	Reference to pch_udc_dev काष्ठाure
 */
अटल व्योम pch_udc_csr_busy(काष्ठा pch_udc_dev *dev)
अणु
	अचिन्हित पूर्णांक count = 200;

	/* Wait till idle */
	जबतक ((pch_udc_पढ़ोl(dev, UDC_CSR_BUSY_ADDR) & UDC_CSR_BUSY)
		&& --count)
		cpu_relax();
	अगर (!count)
		dev_err(&dev->pdev->dev, "%s: wait error\n", __func__);
पूर्ण

/**
 * pch_udc_ग_लिखो_csr() - Write the command and status रेजिस्टरs.
 * @dev:	Reference to pch_udc_dev काष्ठाure
 * @val:	value to be written to CSR रेजिस्टर
 * @ep:		end-poपूर्णांक number
 */
अटल व्योम pch_udc_ग_लिखो_csr(काष्ठा pch_udc_dev *dev, अचिन्हित दीर्घ val,
			       अचिन्हित पूर्णांक ep)
अणु
	अचिन्हित दीर्घ reg = PCH_UDC_CSR(ep);

	pch_udc_csr_busy(dev);		/* Wait till idle */
	pch_udc_ग_लिखोl(dev, val, reg);
	pch_udc_csr_busy(dev);		/* Wait till idle */
पूर्ण

/**
 * pch_udc_पढ़ो_csr() - Read the command and status रेजिस्टरs.
 * @dev:	Reference to pch_udc_dev काष्ठाure
 * @ep:		end-poपूर्णांक number
 *
 * Return codes:	content of CSR रेजिस्टर
 */
अटल u32 pch_udc_पढ़ो_csr(काष्ठा pch_udc_dev *dev, अचिन्हित पूर्णांक ep)
अणु
	अचिन्हित दीर्घ reg = PCH_UDC_CSR(ep);

	pch_udc_csr_busy(dev);		/* Wait till idle */
	pch_udc_पढ़ोl(dev, reg);	/* Dummy पढ़ो */
	pch_udc_csr_busy(dev);		/* Wait till idle */
	वापस pch_udc_पढ़ोl(dev, reg);
पूर्ण

/**
 * pch_udc_rmt_wakeup() - Initiate क्रम remote wakeup
 * @dev:	Reference to pch_udc_dev काष्ठाure
 */
अटल अंतरभूत व्योम pch_udc_rmt_wakeup(काष्ठा pch_udc_dev *dev)
अणु
	pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
	mdelay(1);
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
पूर्ण

/**
 * pch_udc_get_frame() - Get the current frame from device status रेजिस्टर
 * @dev:	Reference to pch_udc_dev काष्ठाure
 * Retern	current frame
 */
अटल अंतरभूत पूर्णांक pch_udc_get_frame(काष्ठा pch_udc_dev *dev)
अणु
	u32 frame = pch_udc_पढ़ोl(dev, UDC_DEVSTS_ADDR);
	वापस (frame & UDC_DEVSTS_TS_MASK) >> UDC_DEVSTS_TS_SHIFT;
पूर्ण

/**
 * pch_udc_clear_selfघातered() - Clear the self घातer control
 * @dev:	Reference to pch_udc_regs काष्ठाure
 */
अटल अंतरभूत व्योम pch_udc_clear_selfघातered(काष्ठा pch_udc_dev *dev)
अणु
	pch_udc_bit_clr(dev, UDC_DEVCFG_ADDR, UDC_DEVCFG_SP);
पूर्ण

/**
 * pch_udc_set_selfघातered() - Set the self घातer control
 * @dev:	Reference to pch_udc_regs काष्ठाure
 */
अटल अंतरभूत व्योम pch_udc_set_selfघातered(काष्ठा pch_udc_dev *dev)
अणु
	pch_udc_bit_set(dev, UDC_DEVCFG_ADDR, UDC_DEVCFG_SP);
पूर्ण

/**
 * pch_udc_set_disconnect() - Set the disconnect status.
 * @dev:	Reference to pch_udc_regs काष्ठाure
 */
अटल अंतरभूत व्योम pch_udc_set_disconnect(काष्ठा pch_udc_dev *dev)
अणु
	pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_SD);
पूर्ण

/**
 * pch_udc_clear_disconnect() - Clear the disconnect status.
 * @dev:	Reference to pch_udc_regs काष्ठाure
 */
अटल व्योम pch_udc_clear_disconnect(काष्ठा pch_udc_dev *dev)
अणु
	/* Clear the disconnect */
	pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_SD);
	mdelay(1);
	/* Resume USB संकेतling */
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
पूर्ण

अटल व्योम pch_udc_init(काष्ठा pch_udc_dev *dev);

/**
 * pch_udc_reconnect() - This API initializes usb device controller,
 *						and clear the disconnect status.
 * @dev:		Reference to pch_udc_regs काष्ठाure
 */
अटल व्योम pch_udc_reconnect(काष्ठा pch_udc_dev *dev)
अणु
	pch_udc_init(dev);

	/* enable device पूर्णांकerrupts */
	/* pch_udc_enable_पूर्णांकerrupts() */
	pch_udc_bit_clr(dev, UDC_DEVIRQMSK_ADDR,
			UDC_DEVINT_UR | UDC_DEVINT_ENUM);

	/* Clear the disconnect */
	pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_SD);
	mdelay(1);
	/* Resume USB संकेतling */
	pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RES);
पूर्ण

/**
 * pch_udc_vbus_session() - set or clearr the disconnect status.
 * @dev:	Reference to pch_udc_regs काष्ठाure
 * @is_active:	Parameter specअगरying the action
 *		  0:   indicating VBUS घातer is ending
 *		  !0:  indicating VBUS घातer is starting
 */
अटल अंतरभूत व्योम pch_udc_vbus_session(काष्ठा pch_udc_dev *dev,
					  पूर्णांक is_active)
अणु
	अचिन्हित दीर्घ		अगरlags;

	spin_lock_irqsave(&dev->lock, अगरlags);
	अगर (is_active) अणु
		pch_udc_reconnect(dev);
		dev->vbus_session = 1;
	पूर्ण अन्यथा अणु
		अगर (dev->driver && dev->driver->disconnect) अणु
			spin_unlock_irqrestore(&dev->lock, अगरlags);
			dev->driver->disconnect(&dev->gadget);
			spin_lock_irqsave(&dev->lock, अगरlags);
		पूर्ण
		pch_udc_set_disconnect(dev);
		dev->vbus_session = 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, अगरlags);
पूर्ण

/**
 * pch_udc_ep_set_stall() - Set the stall of endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल व्योम pch_udc_ep_set_stall(काष्ठा pch_udc_ep *ep)
अणु
	अगर (ep->in) अणु
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_F);
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_S);
	पूर्ण अन्यथा अणु
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_S);
	पूर्ण
पूर्ण

/**
 * pch_udc_ep_clear_stall() - Clear the stall of endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल अंतरभूत व्योम pch_udc_ep_clear_stall(काष्ठा pch_udc_ep *ep)
अणु
	/* Clear the stall */
	pch_udc_ep_bit_clr(ep, UDC_EPCTL_ADDR, UDC_EPCTL_S);
	/* Clear NAK by writing CNAK */
	pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_CNAK);
पूर्ण

/**
 * pch_udc_ep_set_trfr_type() - Set the transfer type of endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * @type:	Type of endpoपूर्णांक
 */
अटल अंतरभूत व्योम pch_udc_ep_set_trfr_type(काष्ठा pch_udc_ep *ep,
					u8 type)
अणु
	pch_udc_ep_ग_लिखोl(ep, ((type << UDC_EPCTL_ET_SHIFT) &
				UDC_EPCTL_ET_MASK), UDC_EPCTL_ADDR);
पूर्ण

/**
 * pch_udc_ep_set_bufsz() - Set the maximum packet size क्रम the endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * @buf_size:	The buffer word size
 * @ep_in:	EP is IN
 */
अटल व्योम pch_udc_ep_set_bufsz(काष्ठा pch_udc_ep *ep,
						 u32 buf_size, u32 ep_in)
अणु
	u32 data;
	अगर (ep_in) अणु
		data = pch_udc_ep_पढ़ोl(ep, UDC_BUFIN_FRAMENUM_ADDR);
		data = (data & 0xffff0000) | (buf_size & 0xffff);
		pch_udc_ep_ग_लिखोl(ep, data, UDC_BUFIN_FRAMENUM_ADDR);
	पूर्ण अन्यथा अणु
		data = pch_udc_ep_पढ़ोl(ep, UDC_BUFOUT_MAXPKT_ADDR);
		data = (buf_size << 16) | (data & 0xffff);
		pch_udc_ep_ग_लिखोl(ep, data, UDC_BUFOUT_MAXPKT_ADDR);
	पूर्ण
पूर्ण

/**
 * pch_udc_ep_set_maxpkt() - Set the Max packet size क्रम the endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * @pkt_size:	The packet byte size
 */
अटल व्योम pch_udc_ep_set_maxpkt(काष्ठा pch_udc_ep *ep, u32 pkt_size)
अणु
	u32 data = pch_udc_ep_पढ़ोl(ep, UDC_BUFOUT_MAXPKT_ADDR);
	data = (data & 0xffff0000) | (pkt_size & 0xffff);
	pch_udc_ep_ग_लिखोl(ep, data, UDC_BUFOUT_MAXPKT_ADDR);
पूर्ण

/**
 * pch_udc_ep_set_subptr() - Set the Setup buffer poपूर्णांकer क्रम the endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * @addr:	Address of the रेजिस्टर
 */
अटल अंतरभूत व्योम pch_udc_ep_set_subptr(काष्ठा pch_udc_ep *ep, u32 addr)
अणु
	pch_udc_ep_ग_लिखोl(ep, addr, UDC_SUBPTR_ADDR);
पूर्ण

/**
 * pch_udc_ep_set_ddptr() - Set the Data descriptor poपूर्णांकer क्रम the endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * @addr:	Address of the रेजिस्टर
 */
अटल अंतरभूत व्योम pch_udc_ep_set_ddptr(काष्ठा pch_udc_ep *ep, u32 addr)
अणु
	pch_udc_ep_ग_लिखोl(ep, addr, UDC_DESPTR_ADDR);
पूर्ण

/**
 * pch_udc_ep_set_pd() - Set the poll demand bit क्रम the endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल अंतरभूत व्योम pch_udc_ep_set_pd(काष्ठा pch_udc_ep *ep)
अणु
	pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_P);
पूर्ण

/**
 * pch_udc_ep_set_rrdy() - Set the receive पढ़ोy bit क्रम the endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल अंतरभूत व्योम pch_udc_ep_set_rrdy(काष्ठा pch_udc_ep *ep)
अणु
	pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_RRDY);
पूर्ण

/**
 * pch_udc_ep_clear_rrdy() - Clear the receive पढ़ोy bit क्रम the endpoपूर्णांक
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल अंतरभूत व्योम pch_udc_ep_clear_rrdy(काष्ठा pch_udc_ep *ep)
अणु
	pch_udc_ep_bit_clr(ep, UDC_EPCTL_ADDR, UDC_EPCTL_RRDY);
पूर्ण

/**
 * pch_udc_set_dma() - Set the 'TDE' or RDE bit of device control
 *			रेजिस्टर depending on the direction specअगरied
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * @dir:	whether Tx or Rx
 *		  DMA_सूची_RX: Receive
 *		  DMA_सूची_TX: Transmit
 */
अटल अंतरभूत व्योम pch_udc_set_dma(काष्ठा pch_udc_dev *dev, पूर्णांक dir)
अणु
	अगर (dir == DMA_सूची_RX)
		pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RDE);
	अन्यथा अगर (dir == DMA_सूची_TX)
		pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_TDE);
पूर्ण

/**
 * pch_udc_clear_dma() - Clear the 'TDE' or RDE bit of device control
 *				 रेजिस्टर depending on the direction specअगरied
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * @dir:	Whether Tx or Rx
 *		  DMA_सूची_RX: Receive
 *		  DMA_सूची_TX: Transmit
 */
अटल अंतरभूत व्योम pch_udc_clear_dma(काष्ठा pch_udc_dev *dev, पूर्णांक dir)
अणु
	अगर (dir == DMA_सूची_RX)
		pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RDE);
	अन्यथा अगर (dir == DMA_सूची_TX)
		pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_TDE);
पूर्ण

/**
 * pch_udc_set_csr_करोne() - Set the device control रेजिस्टर
 *				CSR करोne field (bit 13)
 * @dev:	reference to काष्ठाure of type pch_udc_regs
 */
अटल अंतरभूत व्योम pch_udc_set_csr_करोne(काष्ठा pch_udc_dev *dev)
अणु
	pch_udc_bit_set(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_CSR_DONE);
पूर्ण

/**
 * pch_udc_disable_पूर्णांकerrupts() - Disables the specअगरied पूर्णांकerrupts
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * @mask:	Mask to disable पूर्णांकerrupts
 */
अटल अंतरभूत व्योम pch_udc_disable_पूर्णांकerrupts(काष्ठा pch_udc_dev *dev,
					    u32 mask)
अणु
	pch_udc_bit_set(dev, UDC_DEVIRQMSK_ADDR, mask);
पूर्ण

/**
 * pch_udc_enable_पूर्णांकerrupts() - Enable the specअगरied पूर्णांकerrupts
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * @mask:	Mask to enable पूर्णांकerrupts
 */
अटल अंतरभूत व्योम pch_udc_enable_पूर्णांकerrupts(काष्ठा pch_udc_dev *dev,
					   u32 mask)
अणु
	pch_udc_bit_clr(dev, UDC_DEVIRQMSK_ADDR, mask);
पूर्ण

/**
 * pch_udc_disable_ep_पूर्णांकerrupts() - Disable endpoपूर्णांक पूर्णांकerrupts
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * @mask:	Mask to disable पूर्णांकerrupts
 */
अटल अंतरभूत व्योम pch_udc_disable_ep_पूर्णांकerrupts(काष्ठा pch_udc_dev *dev,
						u32 mask)
अणु
	pch_udc_bit_set(dev, UDC_EPIRQMSK_ADDR, mask);
पूर्ण

/**
 * pch_udc_enable_ep_पूर्णांकerrupts() - Enable endpoपूर्णांक पूर्णांकerrupts
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * @mask:	Mask to enable पूर्णांकerrupts
 */
अटल अंतरभूत व्योम pch_udc_enable_ep_पूर्णांकerrupts(काष्ठा pch_udc_dev *dev,
					      u32 mask)
अणु
	pch_udc_bit_clr(dev, UDC_EPIRQMSK_ADDR, mask);
पूर्ण

/**
 * pch_udc_पढ़ो_device_पूर्णांकerrupts() - Read the device पूर्णांकerrupts
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * Retern	The device पूर्णांकerrupts
 */
अटल अंतरभूत u32 pch_udc_पढ़ो_device_पूर्णांकerrupts(काष्ठा pch_udc_dev *dev)
अणु
	वापस pch_udc_पढ़ोl(dev, UDC_DEVIRQSTS_ADDR);
पूर्ण

/**
 * pch_udc_ग_लिखो_device_पूर्णांकerrupts() - Write device पूर्णांकerrupts
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * @val:	The value to be written to पूर्णांकerrupt रेजिस्टर
 */
अटल अंतरभूत व्योम pch_udc_ग_लिखो_device_पूर्णांकerrupts(काष्ठा pch_udc_dev *dev,
						     u32 val)
अणु
	pch_udc_ग_लिखोl(dev, val, UDC_DEVIRQSTS_ADDR);
पूर्ण

/**
 * pch_udc_पढ़ो_ep_पूर्णांकerrupts() - Read the endpoपूर्णांक पूर्णांकerrupts
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * Retern	The endpoपूर्णांक पूर्णांकerrupt
 */
अटल अंतरभूत u32 pch_udc_पढ़ो_ep_पूर्णांकerrupts(काष्ठा pch_udc_dev *dev)
अणु
	वापस pch_udc_पढ़ोl(dev, UDC_EPIRQSTS_ADDR);
पूर्ण

/**
 * pch_udc_ग_लिखो_ep_पूर्णांकerrupts() - Clear endpoपूर्णांक पूर्णांकerupts
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * @val:	The value to be written to पूर्णांकerrupt रेजिस्टर
 */
अटल अंतरभूत व्योम pch_udc_ग_लिखो_ep_पूर्णांकerrupts(काष्ठा pch_udc_dev *dev,
					     u32 val)
अणु
	pch_udc_ग_लिखोl(dev, val, UDC_EPIRQSTS_ADDR);
पूर्ण

/**
 * pch_udc_पढ़ो_device_status() - Read the device status
 * @dev:	Reference to काष्ठाure of type pch_udc_regs
 * Retern	The device status
 */
अटल अंतरभूत u32 pch_udc_पढ़ो_device_status(काष्ठा pch_udc_dev *dev)
अणु
	वापस pch_udc_पढ़ोl(dev, UDC_DEVSTS_ADDR);
पूर्ण

/**
 * pch_udc_पढ़ो_ep_control() - Read the endpoपूर्णांक control
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * Retern	The endpoपूर्णांक control रेजिस्टर value
 */
अटल अंतरभूत u32 pch_udc_पढ़ो_ep_control(काष्ठा pch_udc_ep *ep)
अणु
	वापस pch_udc_ep_पढ़ोl(ep, UDC_EPCTL_ADDR);
पूर्ण

/**
 * pch_udc_clear_ep_control() - Clear the endpoपूर्णांक control रेजिस्टर
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * Retern	The endpoपूर्णांक control रेजिस्टर value
 */
अटल अंतरभूत व्योम pch_udc_clear_ep_control(काष्ठा pch_udc_ep *ep)
अणु
	वापस pch_udc_ep_ग_लिखोl(ep, 0, UDC_EPCTL_ADDR);
पूर्ण

/**
 * pch_udc_पढ़ो_ep_status() - Read the endpoपूर्णांक status
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * Retern	The endpoपूर्णांक status
 */
अटल अंतरभूत u32 pch_udc_पढ़ो_ep_status(काष्ठा pch_udc_ep *ep)
अणु
	वापस pch_udc_ep_पढ़ोl(ep, UDC_EPSTS_ADDR);
पूर्ण

/**
 * pch_udc_clear_ep_status() - Clear the endpoपूर्णांक status
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 * @stat:	Endpoपूर्णांक status
 */
अटल अंतरभूत व्योम pch_udc_clear_ep_status(काष्ठा pch_udc_ep *ep,
					 u32 stat)
अणु
	वापस pch_udc_ep_ग_लिखोl(ep, stat, UDC_EPSTS_ADDR);
पूर्ण

/**
 * pch_udc_ep_set_nak() - Set the bit 7 (SNAK field)
 *				of the endpoपूर्णांक control रेजिस्टर
 * @ep:		Reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल अंतरभूत व्योम pch_udc_ep_set_nak(काष्ठा pch_udc_ep *ep)
अणु
	pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_SNAK);
पूर्ण

/**
 * pch_udc_ep_clear_nak() - Set the bit 8 (CNAK field)
 *				of the endpoपूर्णांक control रेजिस्टर
 * @ep:		reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल व्योम pch_udc_ep_clear_nak(काष्ठा pch_udc_ep *ep)
अणु
	अचिन्हित पूर्णांक loopcnt = 0;
	काष्ठा pch_udc_dev *dev = ep->dev;

	अगर (!(pch_udc_ep_पढ़ोl(ep, UDC_EPCTL_ADDR) & UDC_EPCTL_NAK))
		वापस;
	अगर (!ep->in) अणु
		loopcnt = 10000;
		जबतक (!(pch_udc_पढ़ो_ep_status(ep) & UDC_EPSTS_MRXFIFO_EMP) &&
			--loopcnt)
			udelay(5);
		अगर (!loopcnt)
			dev_err(&dev->pdev->dev, "%s: RxFIFO not Empty\n",
				__func__);
	पूर्ण
	loopcnt = 10000;
	जबतक ((pch_udc_पढ़ो_ep_control(ep) & UDC_EPCTL_NAK) && --loopcnt) अणु
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_CNAK);
		udelay(5);
	पूर्ण
	अगर (!loopcnt)
		dev_err(&dev->pdev->dev, "%s: Clear NAK not set for ep%d%s\n",
			__func__, ep->num, (ep->in ? "in" : "out"));
पूर्ण

/**
 * pch_udc_ep_fअगरo_flush() - Flush the endpoपूर्णांक fअगरo
 * @ep:	reference to काष्ठाure of type pch_udc_ep_regs
 * @dir:	direction of endpoपूर्णांक
 *		  0:  endpoपूर्णांक is OUT
 *		  !0: endpoपूर्णांक is IN
 */
अटल व्योम pch_udc_ep_fअगरo_flush(काष्ठा pch_udc_ep *ep, पूर्णांक dir)
अणु
	अगर (dir) अणु	/* IN ep */
		pch_udc_ep_bit_set(ep, UDC_EPCTL_ADDR, UDC_EPCTL_F);
		वापस;
	पूर्ण
पूर्ण

/**
 * pch_udc_ep_enable() - This api enables endpoपूर्णांक
 * @ep:		reference to काष्ठाure of type pch_udc_ep_regs
 * @cfg:	current configuration inक्रमmation
 * @desc:	endpoपूर्णांक descriptor
 */
अटल व्योम pch_udc_ep_enable(काष्ठा pch_udc_ep *ep,
			       काष्ठा pch_udc_cfg_data *cfg,
			       स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	u32 val = 0;
	u32 buff_size = 0;

	pch_udc_ep_set_trfr_type(ep, desc->bmAttributes);
	अगर (ep->in)
		buff_size = UDC_EPIN_BUFF_SIZE;
	अन्यथा
		buff_size = UDC_EPOUT_BUFF_SIZE;
	pch_udc_ep_set_bufsz(ep, buff_size, ep->in);
	pch_udc_ep_set_maxpkt(ep, usb_endpoपूर्णांक_maxp(desc));
	pch_udc_ep_set_nak(ep);
	pch_udc_ep_fअगरo_flush(ep, ep->in);
	/* Configure the endpoपूर्णांक */
	val = ep->num << UDC_CSR_NE_NUM_SHIFT | ep->in << UDC_CSR_NE_सूची_SHIFT |
	      ((desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) <<
		UDC_CSR_NE_TYPE_SHIFT) |
	      (cfg->cur_cfg << UDC_CSR_NE_CFG_SHIFT) |
	      (cfg->cur_पूर्णांकf << UDC_CSR_NE_INTF_SHIFT) |
	      (cfg->cur_alt << UDC_CSR_NE_ALT_SHIFT) |
	      usb_endpoपूर्णांक_maxp(desc) << UDC_CSR_NE_MAX_PKT_SHIFT;

	अगर (ep->in)
		pch_udc_ग_लिखो_csr(ep->dev, val, UDC_EPIN_IDX(ep->num));
	अन्यथा
		pch_udc_ग_लिखो_csr(ep->dev, val, UDC_EPOUT_IDX(ep->num));
पूर्ण

/**
 * pch_udc_ep_disable() - This api disables endpoपूर्णांक
 * @ep:		reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल व्योम pch_udc_ep_disable(काष्ठा pch_udc_ep *ep)
अणु
	अगर (ep->in) अणु
		/* flush the fअगरo */
		pch_udc_ep_ग_लिखोl(ep, UDC_EPCTL_F, UDC_EPCTL_ADDR);
		/* set NAK */
		pch_udc_ep_ग_लिखोl(ep, UDC_EPCTL_SNAK, UDC_EPCTL_ADDR);
		pch_udc_ep_bit_set(ep, UDC_EPSTS_ADDR, UDC_EPSTS_IN);
	पूर्ण अन्यथा अणु
		/* set NAK */
		pch_udc_ep_ग_लिखोl(ep, UDC_EPCTL_SNAK, UDC_EPCTL_ADDR);
	पूर्ण
	/* reset desc poपूर्णांकer */
	pch_udc_ep_ग_लिखोl(ep, 0, UDC_DESPTR_ADDR);
पूर्ण

/**
 * pch_udc_रुको_ep_stall() - Wait EP stall.
 * @ep:		reference to काष्ठाure of type pch_udc_ep_regs
 */
अटल व्योम pch_udc_रुको_ep_stall(काष्ठा pch_udc_ep *ep)
अणु
	अचिन्हित पूर्णांक count = 10000;

	/* Wait till idle */
	जबतक ((pch_udc_पढ़ो_ep_control(ep) & UDC_EPCTL_S) && --count)
		udelay(5);
	अगर (!count)
		dev_err(&ep->dev->pdev->dev, "%s: wait error\n", __func__);
पूर्ण

/**
 * pch_udc_init() - This API initializes usb device controller
 * @dev:	Rreference to pch_udc_regs काष्ठाure
 */
अटल व्योम pch_udc_init(काष्ठा pch_udc_dev *dev)
अणु
	अगर (शून्य == dev) अणु
		pr_err("%s: Invalid address\n", __func__);
		वापस;
	पूर्ण
	/* Soft Reset and Reset PHY */
	pch_udc_ग_लिखोl(dev, UDC_SRST, UDC_SRST_ADDR);
	pch_udc_ग_लिखोl(dev, UDC_SRST | UDC_PSRST, UDC_SRST_ADDR);
	mdelay(1);
	pch_udc_ग_लिखोl(dev, UDC_SRST, UDC_SRST_ADDR);
	pch_udc_ग_लिखोl(dev, 0x00, UDC_SRST_ADDR);
	mdelay(1);
	/* mask and clear all device पूर्णांकerrupts */
	pch_udc_bit_set(dev, UDC_DEVIRQMSK_ADDR, UDC_DEVINT_MSK);
	pch_udc_bit_set(dev, UDC_DEVIRQSTS_ADDR, UDC_DEVINT_MSK);

	/* mask and clear all ep पूर्णांकerrupts */
	pch_udc_bit_set(dev, UDC_EPIRQMSK_ADDR, UDC_EPINT_MSK_DISABLE_ALL);
	pch_udc_bit_set(dev, UDC_EPIRQSTS_ADDR, UDC_EPINT_MSK_DISABLE_ALL);

	/* enable dynamic CSR programmingi, self घातered and device speed */
	अगर (speed_fs)
		pch_udc_bit_set(dev, UDC_DEVCFG_ADDR, UDC_DEVCFG_CSR_PRG |
				UDC_DEVCFG_SP | UDC_DEVCFG_SPD_FS);
	अन्यथा /* defaul high speed */
		pch_udc_bit_set(dev, UDC_DEVCFG_ADDR, UDC_DEVCFG_CSR_PRG |
				UDC_DEVCFG_SP | UDC_DEVCFG_SPD_HS);
	pch_udc_bit_set(dev, UDC_DEVCTL_ADDR,
			(PCH_UDC_THLEN << UDC_DEVCTL_THLEN_SHIFT) |
			(PCH_UDC_BRLEN << UDC_DEVCTL_BRLEN_SHIFT) |
			UDC_DEVCTL_MODE | UDC_DEVCTL_BREN |
			UDC_DEVCTL_THE);
पूर्ण

/**
 * pch_udc_निकास() - This API निकास usb device controller
 * @dev:	Reference to pch_udc_regs काष्ठाure
 */
अटल व्योम pch_udc_निकास(काष्ठा pch_udc_dev *dev)
अणु
	/* mask all device पूर्णांकerrupts */
	pch_udc_bit_set(dev, UDC_DEVIRQMSK_ADDR, UDC_DEVINT_MSK);
	/* mask all ep पूर्णांकerrupts */
	pch_udc_bit_set(dev, UDC_EPIRQMSK_ADDR, UDC_EPINT_MSK_DISABLE_ALL);
	/* put device in disconnected state */
	pch_udc_set_disconnect(dev);
पूर्ण

/**
 * pch_udc_pcd_get_frame() - This API is invoked to get the current frame number
 * @gadget:	Reference to the gadget driver
 *
 * Return codes:
 *	0:		Success
 *	-EINVAL:	If the gadget passed is शून्य
 */
अटल पूर्णांक pch_udc_pcd_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा pch_udc_dev	*dev;

	अगर (!gadget)
		वापस -EINVAL;
	dev = container_of(gadget, काष्ठा pch_udc_dev, gadget);
	वापस pch_udc_get_frame(dev);
पूर्ण

/**
 * pch_udc_pcd_wakeup() - This API is invoked to initiate a remote wakeup
 * @gadget:	Reference to the gadget driver
 *
 * Return codes:
 *	0:		Success
 *	-EINVAL:	If the gadget passed is शून्य
 */
अटल पूर्णांक pch_udc_pcd_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा pch_udc_dev	*dev;
	अचिन्हित दीर्घ		flags;

	अगर (!gadget)
		वापस -EINVAL;
	dev = container_of(gadget, काष्ठा pch_udc_dev, gadget);
	spin_lock_irqsave(&dev->lock, flags);
	pch_udc_rmt_wakeup(dev);
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस 0;
पूर्ण

/**
 * pch_udc_pcd_selfघातered() - This API is invoked to specअगरy whether the device
 *				is self घातered or not
 * @gadget:	Reference to the gadget driver
 * @value:	Specअगरies self घातered or not
 *
 * Return codes:
 *	0:		Success
 *	-EINVAL:	If the gadget passed is शून्य
 */
अटल पूर्णांक pch_udc_pcd_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक value)
अणु
	काष्ठा pch_udc_dev	*dev;

	अगर (!gadget)
		वापस -EINVAL;
	gadget->is_selfघातered = (value != 0);
	dev = container_of(gadget, काष्ठा pch_udc_dev, gadget);
	अगर (value)
		pch_udc_set_selfघातered(dev);
	अन्यथा
		pch_udc_clear_selfघातered(dev);
	वापस 0;
पूर्ण

/**
 * pch_udc_pcd_pullup() - This API is invoked to make the device
 *				visible/invisible to the host
 * @gadget:	Reference to the gadget driver
 * @is_on:	Specअगरies whether the pull up is made active or inactive
 *
 * Return codes:
 *	0:		Success
 *	-EINVAL:	If the gadget passed is शून्य
 */
अटल पूर्णांक pch_udc_pcd_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा pch_udc_dev	*dev;
	अचिन्हित दीर्घ		अगरlags;

	अगर (!gadget)
		वापस -EINVAL;

	dev = container_of(gadget, काष्ठा pch_udc_dev, gadget);

	spin_lock_irqsave(&dev->lock, अगरlags);
	अगर (is_on) अणु
		pch_udc_reconnect(dev);
	पूर्ण अन्यथा अणु
		अगर (dev->driver && dev->driver->disconnect) अणु
			spin_unlock_irqrestore(&dev->lock, अगरlags);
			dev->driver->disconnect(&dev->gadget);
			spin_lock_irqsave(&dev->lock, अगरlags);
		पूर्ण
		pch_udc_set_disconnect(dev);
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, अगरlags);

	वापस 0;
पूर्ण

/**
 * pch_udc_pcd_vbus_session() - This API is used by a driver क्रम an बाह्यal
 *				transceiver (or GPIO) that
 *				detects a VBUS घातer session starting/ending
 * @gadget:	Reference to the gadget driver
 * @is_active:	specअगरies whether the session is starting or ending
 *
 * Return codes:
 *	0:		Success
 *	-EINVAL:	If the gadget passed is शून्य
 */
अटल पूर्णांक pch_udc_pcd_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा pch_udc_dev	*dev;

	अगर (!gadget)
		वापस -EINVAL;
	dev = container_of(gadget, काष्ठा pch_udc_dev, gadget);
	pch_udc_vbus_session(dev, is_active);
	वापस 0;
पूर्ण

/**
 * pch_udc_pcd_vbus_draw() - This API is used by gadget drivers during
 *				SET_CONFIGURATION calls to
 *				specअगरy how much घातer the device can consume
 * @gadget:	Reference to the gadget driver
 * @mA:		specअगरies the current limit in 2mA unit
 *
 * Return codes:
 *	-EINVAL:	If the gadget passed is शून्य
 *	-EOPNOTSUPP:
 */
अटल पूर्णांक pch_udc_pcd_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित पूर्णांक mA)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक pch_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक pch_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops pch_udc_ops = अणु
	.get_frame = pch_udc_pcd_get_frame,
	.wakeup = pch_udc_pcd_wakeup,
	.set_selfघातered = pch_udc_pcd_selfघातered,
	.pullup = pch_udc_pcd_pullup,
	.vbus_session = pch_udc_pcd_vbus_session,
	.vbus_draw = pch_udc_pcd_vbus_draw,
	.udc_start = pch_udc_start,
	.udc_stop = pch_udc_stop,
पूर्ण;

/**
 * pch_vbus_gpio_get_value() - This API माला_लो value of GPIO port as VBUS status.
 * @dev:	Reference to the driver काष्ठाure
 *
 * Return value:
 *	1: VBUS is high
 *	0: VBUS is low
 *     -1: It is not enable to detect VBUS using GPIO
 */
अटल पूर्णांक pch_vbus_gpio_get_value(काष्ठा pch_udc_dev *dev)
अणु
	पूर्णांक vbus = 0;

	अगर (dev->vbus_gpio.port)
		vbus = gpiod_get_value(dev->vbus_gpio.port) ? 1 : 0;
	अन्यथा
		vbus = -1;

	वापस vbus;
पूर्ण

/**
 * pch_vbus_gpio_work_fall() - This API keeps watch on VBUS becoming Low.
 *                             If VBUS is Low, disconnect is processed
 * @irq_work:	Structure क्रम WorkQueue
 *
 */
अटल व्योम pch_vbus_gpio_work_fall(काष्ठा work_काष्ठा *irq_work)
अणु
	काष्ठा pch_vbus_gpio_data *vbus_gpio = container_of(irq_work,
		काष्ठा pch_vbus_gpio_data, irq_work_fall);
	काष्ठा pch_udc_dev *dev =
		container_of(vbus_gpio, काष्ठा pch_udc_dev, vbus_gpio);
	पूर्णांक vbus_saved = -1;
	पूर्णांक vbus;
	पूर्णांक count;

	अगर (!dev->vbus_gpio.port)
		वापस;

	क्रम (count = 0; count < (PCH_VBUS_PERIOD / PCH_VBUS_INTERVAL);
		count++) अणु
		vbus = pch_vbus_gpio_get_value(dev);

		अगर ((vbus_saved == vbus) && (vbus == 0)) अणु
			dev_dbg(&dev->pdev->dev, "VBUS fell");
			अगर (dev->driver
				&& dev->driver->disconnect) अणु
				dev->driver->disconnect(
					&dev->gadget);
			पूर्ण
			अगर (dev->vbus_gpio.पूर्णांकr)
				pch_udc_init(dev);
			अन्यथा
				pch_udc_reconnect(dev);
			वापस;
		पूर्ण
		vbus_saved = vbus;
		mdelay(PCH_VBUS_INTERVAL);
	पूर्ण
पूर्ण

/**
 * pch_vbus_gpio_work_rise() - This API checks VBUS is High.
 *                             If VBUS is High, connect is processed
 * @irq_work:	Structure क्रम WorkQueue
 *
 */
अटल व्योम pch_vbus_gpio_work_rise(काष्ठा work_काष्ठा *irq_work)
अणु
	काष्ठा pch_vbus_gpio_data *vbus_gpio = container_of(irq_work,
		काष्ठा pch_vbus_gpio_data, irq_work_rise);
	काष्ठा pch_udc_dev *dev =
		container_of(vbus_gpio, काष्ठा pch_udc_dev, vbus_gpio);
	पूर्णांक vbus;

	अगर (!dev->vbus_gpio.port)
		वापस;

	mdelay(PCH_VBUS_INTERVAL);
	vbus = pch_vbus_gpio_get_value(dev);

	अगर (vbus == 1) अणु
		dev_dbg(&dev->pdev->dev, "VBUS rose");
		pch_udc_reconnect(dev);
		वापस;
	पूर्ण
पूर्ण

/**
 * pch_vbus_gpio_irq() - IRQ handler क्रम GPIO पूर्णांकerrupt क्रम changing VBUS
 * @irq:	Interrupt request number
 * @data:	Reference to the device काष्ठाure
 *
 * Return codes:
 *	0: Success
 *	-EINVAL: GPIO port is invalid or can't be initialized.
 */
अटल irqवापस_t pch_vbus_gpio_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pch_udc_dev *dev = (काष्ठा pch_udc_dev *)data;

	अगर (!dev->vbus_gpio.port || !dev->vbus_gpio.पूर्णांकr)
		वापस IRQ_NONE;

	अगर (pch_vbus_gpio_get_value(dev))
		schedule_work(&dev->vbus_gpio.irq_work_rise);
	अन्यथा
		schedule_work(&dev->vbus_gpio.irq_work_fall);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * pch_vbus_gpio_init() - This API initializes GPIO port detecting VBUS.
 * @dev:		Reference to the driver काष्ठाure
 *
 * Return codes:
 *	0: Success
 *	-EINVAL: GPIO port is invalid or can't be initialized.
 */
अटल पूर्णांक pch_vbus_gpio_init(काष्ठा pch_udc_dev *dev)
अणु
	काष्ठा device *d = &dev->pdev->dev;
	पूर्णांक err;
	पूर्णांक irq_num = 0;
	काष्ठा gpio_desc *gpiod;

	dev->vbus_gpio.port = शून्य;
	dev->vbus_gpio.पूर्णांकr = 0;

	/* Retrieve the GPIO line from the USB gadget device */
	gpiod = devm_gpiod_get_optional(d, शून्य, GPIOD_IN);
	अगर (IS_ERR(gpiod))
		वापस PTR_ERR(gpiod);
	gpiod_set_consumer_name(gpiod, "pch_vbus");

	dev->vbus_gpio.port = gpiod;
	INIT_WORK(&dev->vbus_gpio.irq_work_fall, pch_vbus_gpio_work_fall);

	irq_num = gpiod_to_irq(gpiod);
	अगर (irq_num > 0) अणु
		irq_set_irq_type(irq_num, IRQ_TYPE_EDGE_BOTH);
		err = request_irq(irq_num, pch_vbus_gpio_irq, 0,
			"vbus_detect", dev);
		अगर (!err) अणु
			dev->vbus_gpio.पूर्णांकr = irq_num;
			INIT_WORK(&dev->vbus_gpio.irq_work_rise,
				pch_vbus_gpio_work_rise);
		पूर्ण अन्यथा अणु
			pr_err("%s: can't request irq %d, err: %d\n",
				__func__, irq_num, err);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pch_vbus_gpio_मुक्त() - This API मुक्तs resources of GPIO port
 * @dev:	Reference to the driver काष्ठाure
 */
अटल व्योम pch_vbus_gpio_मुक्त(काष्ठा pch_udc_dev *dev)
अणु
	अगर (dev->vbus_gpio.पूर्णांकr)
		मुक्त_irq(dev->vbus_gpio.पूर्णांकr, dev);
पूर्ण

/**
 * complete_req() - This API is invoked from the driver when processing
 *			of a request is complete
 * @ep:		Reference to the endpoपूर्णांक काष्ठाure
 * @req:	Reference to the request काष्ठाure
 * @status:	Indicates the success/failure of completion
 */
अटल व्योम complete_req(काष्ठा pch_udc_ep *ep, काष्ठा pch_udc_request *req,
								 पूर्णांक status)
	__releases(&dev->lock)
	__acquires(&dev->lock)
अणु
	काष्ठा pch_udc_dev	*dev;
	अचिन्हित halted = ep->halted;

	list_del_init(&req->queue);

	/* set new status अगर pending */
	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	dev = ep->dev;
	usb_gadget_unmap_request(&dev->gadget, &req->req, ep->in);
	ep->halted = 1;
	spin_unlock(&dev->lock);
	अगर (!ep->in)
		pch_udc_ep_clear_rrdy(ep);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&dev->lock);
	ep->halted = halted;
पूर्ण

/**
 * empty_req_queue() - This API empties the request queue of an endpoपूर्णांक
 * @ep:		Reference to the endpoपूर्णांक काष्ठाure
 */
अटल व्योम empty_req_queue(काष्ठा pch_udc_ep *ep)
अणु
	काष्ठा pch_udc_request	*req;

	ep->halted = 1;
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा pch_udc_request, queue);
		complete_req(ep, req, -ESHUTDOWN);	/* Remove from list */
	पूर्ण
पूर्ण

/**
 * pch_udc_मुक्त_dma_chain() - This function मुक्तs the DMA chain created
 *				क्रम the request
 * @dev:	Reference to the driver काष्ठाure
 * @req:	Reference to the request to be मुक्तd
 *
 * Return codes:
 *	0: Success
 */
अटल व्योम pch_udc_मुक्त_dma_chain(काष्ठा pch_udc_dev *dev,
				   काष्ठा pch_udc_request *req)
अणु
	काष्ठा pch_udc_data_dma_desc *td = req->td_data;
	अचिन्हित i = req->chain_len;

	dma_addr_t addr2;
	dma_addr_t addr = (dma_addr_t)td->next;
	td->next = 0x00;
	क्रम (; i > 1; --i) अणु
		/* करो not मुक्त first desc., will be करोne by मुक्त क्रम request */
		td = phys_to_virt(addr);
		addr2 = (dma_addr_t)td->next;
		dma_pool_मुक्त(dev->data_requests, td, addr);
		addr = addr2;
	पूर्ण
	req->chain_len = 1;
पूर्ण

/**
 * pch_udc_create_dma_chain() - This function creates or reinitializes
 *				a DMA chain
 * @ep:		Reference to the endpoपूर्णांक काष्ठाure
 * @req:	Reference to the request
 * @buf_len:	The buffer length
 * @gfp_flags:	Flags to be used जबतक mapping the data buffer
 *
 * Return codes:
 *	0:		success,
 *	-ENOMEM:	dma_pool_alloc invocation fails
 */
अटल पूर्णांक pch_udc_create_dma_chain(काष्ठा pch_udc_ep *ep,
				    काष्ठा pch_udc_request *req,
				    अचिन्हित दीर्घ buf_len,
				    gfp_t gfp_flags)
अणु
	काष्ठा pch_udc_data_dma_desc *td = req->td_data, *last;
	अचिन्हित दीर्घ bytes = req->req.length, i = 0;
	dma_addr_t dma_addr;
	अचिन्हित len = 1;

	अगर (req->chain_len > 1)
		pch_udc_मुक्त_dma_chain(ep->dev, req);

	td->dataptr = req->req.dma;
	td->status = PCH_UDC_BS_HST_BSY;

	क्रम (; ; bytes -= buf_len, ++len) अणु
		td->status = PCH_UDC_BS_HST_BSY | min(buf_len, bytes);
		अगर (bytes <= buf_len)
			अवरोध;
		last = td;
		td = dma_pool_alloc(ep->dev->data_requests, gfp_flags,
				    &dma_addr);
		अगर (!td)
			जाओ nomem;
		i += buf_len;
		td->dataptr = req->td_data->dataptr + i;
		last->next = dma_addr;
	पूर्ण

	req->td_data_last = td;
	td->status |= PCH_UDC_DMA_LAST;
	td->next = req->td_data_phys;
	req->chain_len = len;
	वापस 0;

nomem:
	अगर (len > 1) अणु
		req->chain_len = len;
		pch_udc_मुक्त_dma_chain(ep->dev, req);
	पूर्ण
	req->chain_len = 1;
	वापस -ENOMEM;
पूर्ण

/**
 * prepare_dma() - This function creates and initializes the DMA chain
 *			क्रम the request
 * @ep:		Reference to the endpoपूर्णांक काष्ठाure
 * @req:	Reference to the request
 * @gfp:	Flag to be used जबतक mapping the data buffer
 *
 * Return codes:
 *	0:		Success
 *	Other 0:	linux error number on failure
 */
अटल पूर्णांक prepare_dma(काष्ठा pch_udc_ep *ep, काष्ठा pch_udc_request *req,
			  gfp_t gfp)
अणु
	पूर्णांक	retval;

	/* Allocate and create a DMA chain */
	retval = pch_udc_create_dma_chain(ep, req, ep->ep.maxpacket, gfp);
	अगर (retval) अणु
		pr_err("%s: could not create DMA chain:%d\n", __func__, retval);
		वापस retval;
	पूर्ण
	अगर (ep->in)
		req->td_data->status = (req->td_data->status &
				~PCH_UDC_BUFF_STS) | PCH_UDC_BS_HST_RDY;
	वापस 0;
पूर्ण

/**
 * process_zlp() - This function process zero length packets
 *			from the gadget driver
 * @ep:		Reference to the endpoपूर्णांक काष्ठाure
 * @req:	Reference to the request
 */
अटल व्योम process_zlp(काष्ठा pch_udc_ep *ep, काष्ठा pch_udc_request *req)
अणु
	काष्ठा pch_udc_dev	*dev = ep->dev;

	/* IN zlp's are handled by hardware */
	complete_req(ep, req, 0);

	/* अगर set_config or set_पूर्णांकf is रुकोing क्रम ack by zlp
	 * then set CSR_DONE
	 */
	अगर (dev->set_cfg_not_acked) अणु
		pch_udc_set_csr_करोne(dev);
		dev->set_cfg_not_acked = 0;
	पूर्ण
	/* setup command is ACK'ed now by zlp */
	अगर (!dev->stall && dev->रुकोing_zlp_ack) अणु
		pch_udc_ep_clear_nak(&(dev->ep[UDC_EP0IN_IDX]));
		dev->रुकोing_zlp_ack = 0;
	पूर्ण
पूर्ण

/**
 * pch_udc_start_rxrequest() - This function starts the receive requirement.
 * @ep:		Reference to the endpoपूर्णांक काष्ठाure
 * @req:	Reference to the request काष्ठाure
 */
अटल व्योम pch_udc_start_rxrequest(काष्ठा pch_udc_ep *ep,
					 काष्ठा pch_udc_request *req)
अणु
	काष्ठा pch_udc_data_dma_desc *td_data;

	pch_udc_clear_dma(ep->dev, DMA_सूची_RX);
	td_data = req->td_data;
	/* Set the status bits क्रम all descriptors */
	जबतक (1) अणु
		td_data->status = (td_data->status & ~PCH_UDC_BUFF_STS) |
				    PCH_UDC_BS_HST_RDY;
		अगर ((td_data->status & PCH_UDC_DMA_LAST) ==  PCH_UDC_DMA_LAST)
			अवरोध;
		td_data = phys_to_virt(td_data->next);
	पूर्ण
	/* Write the descriptor poपूर्णांकer */
	pch_udc_ep_set_ddptr(ep, req->td_data_phys);
	req->dma_going = 1;
	pch_udc_enable_ep_पूर्णांकerrupts(ep->dev, UDC_EPINT_OUT_EP0 << ep->num);
	pch_udc_set_dma(ep->dev, DMA_सूची_RX);
	pch_udc_ep_clear_nak(ep);
	pch_udc_ep_set_rrdy(ep);
पूर्ण

/**
 * pch_udc_pcd_ep_enable() - This API enables the endpoपूर्णांक. It is called
 *				from gadget driver
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 * @desc:	Reference to the USB endpoपूर्णांक descriptor काष्ठाure
 *
 * Return codes:
 *	0:		Success
 *	-EINVAL:
 *	-ESHUTDOWN:
 */
अटल पूर्णांक pch_udc_pcd_ep_enable(काष्ठा usb_ep *usbep,
				    स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा pch_udc_ep	*ep;
	काष्ठा pch_udc_dev	*dev;
	अचिन्हित दीर्घ		अगरlags;

	अगर (!usbep || (usbep->name == ep0_string) || !desc ||
	    (desc->bDescriptorType != USB_DT_ENDPOINT) || !desc->wMaxPacketSize)
		वापस -EINVAL;

	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	dev = ep->dev;
	अगर (!dev->driver || (dev->gadget.speed == USB_SPEED_UNKNOWN))
		वापस -ESHUTDOWN;
	spin_lock_irqsave(&dev->lock, अगरlags);
	ep->ep.desc = desc;
	ep->halted = 0;
	pch_udc_ep_enable(ep, &ep->dev->cfg_data, desc);
	ep->ep.maxpacket = usb_endpoपूर्णांक_maxp(desc);
	pch_udc_enable_ep_पूर्णांकerrupts(ep->dev, PCH_UDC_EPINT(ep->in, ep->num));
	spin_unlock_irqrestore(&dev->lock, अगरlags);
	वापस 0;
पूर्ण

/**
 * pch_udc_pcd_ep_disable() - This API disables endpoपूर्णांक and is called
 *				from gadget driver
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 *
 * Return codes:
 *	0:		Success
 *	-EINVAL:
 */
अटल पूर्णांक pch_udc_pcd_ep_disable(काष्ठा usb_ep *usbep)
अणु
	काष्ठा pch_udc_ep	*ep;
	अचिन्हित दीर्घ	अगरlags;

	अगर (!usbep)
		वापस -EINVAL;

	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	अगर ((usbep->name == ep0_string) || !ep->ep.desc)
		वापस -EINVAL;

	spin_lock_irqsave(&ep->dev->lock, अगरlags);
	empty_req_queue(ep);
	ep->halted = 1;
	pch_udc_ep_disable(ep);
	pch_udc_disable_ep_पूर्णांकerrupts(ep->dev, PCH_UDC_EPINT(ep->in, ep->num));
	ep->ep.desc = शून्य;
	INIT_LIST_HEAD(&ep->queue);
	spin_unlock_irqrestore(&ep->dev->lock, अगरlags);
	वापस 0;
पूर्ण

/**
 * pch_udc_alloc_request() - This function allocates request काष्ठाure.
 *				It is called by gadget driver
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 * @gfp:	Flag to be used जबतक allocating memory
 *
 * Return codes:
 *	शून्य:			Failure
 *	Allocated address:	Success
 */
अटल काष्ठा usb_request *pch_udc_alloc_request(काष्ठा usb_ep *usbep,
						  gfp_t gfp)
अणु
	काष्ठा pch_udc_request		*req;
	काष्ठा pch_udc_ep		*ep;
	काष्ठा pch_udc_data_dma_desc	*dma_desc;

	अगर (!usbep)
		वापस शून्य;
	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	req = kzalloc(माप *req, gfp);
	अगर (!req)
		वापस शून्य;
	req->req.dma = DMA_ADDR_INVALID;
	INIT_LIST_HEAD(&req->queue);
	अगर (!ep->dev->dma_addr)
		वापस &req->req;
	/* ep0 in requests are allocated from data pool here */
	dma_desc = dma_pool_alloc(ep->dev->data_requests, gfp,
				  &req->td_data_phys);
	अगर (शून्य == dma_desc) अणु
		kमुक्त(req);
		वापस शून्य;
	पूर्ण
	/* prevent from using desc. - set HOST BUSY */
	dma_desc->status |= PCH_UDC_BS_HST_BSY;
	dma_desc->dataptr = lower_32_bits(DMA_ADDR_INVALID);
	req->td_data = dma_desc;
	req->td_data_last = dma_desc;
	req->chain_len = 1;
	वापस &req->req;
पूर्ण

/**
 * pch_udc_मुक्त_request() - This function मुक्तs request काष्ठाure.
 *				It is called by gadget driver
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 * @usbreq:	Reference to the USB request
 */
अटल व्योम pch_udc_मुक्त_request(काष्ठा usb_ep *usbep,
				  काष्ठा usb_request *usbreq)
अणु
	काष्ठा pch_udc_ep	*ep;
	काष्ठा pch_udc_request	*req;
	काष्ठा pch_udc_dev	*dev;

	अगर (!usbep || !usbreq)
		वापस;
	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	req = container_of(usbreq, काष्ठा pch_udc_request, req);
	dev = ep->dev;
	अगर (!list_empty(&req->queue))
		dev_err(&dev->pdev->dev, "%s: %s req=0x%p queue not empty\n",
			__func__, usbep->name, req);
	अगर (req->td_data != शून्य) अणु
		अगर (req->chain_len > 1)
			pch_udc_मुक्त_dma_chain(ep->dev, req);
		dma_pool_मुक्त(ep->dev->data_requests, req->td_data,
			      req->td_data_phys);
	पूर्ण
	kमुक्त(req);
पूर्ण

/**
 * pch_udc_pcd_queue() - This function queues a request packet. It is called
 *			by gadget driver
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 * @usbreq:	Reference to the USB request
 * @gfp:	Flag to be used जबतक mapping the data buffer
 *
 * Return codes:
 *	0:			Success
 *	linux error number:	Failure
 */
अटल पूर्णांक pch_udc_pcd_queue(काष्ठा usb_ep *usbep, काष्ठा usb_request *usbreq,
								 gfp_t gfp)
अणु
	पूर्णांक retval = 0;
	काष्ठा pch_udc_ep	*ep;
	काष्ठा pch_udc_dev	*dev;
	काष्ठा pch_udc_request	*req;
	अचिन्हित दीर्घ	अगरlags;

	अगर (!usbep || !usbreq || !usbreq->complete || !usbreq->buf)
		वापस -EINVAL;
	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	dev = ep->dev;
	अगर (!ep->ep.desc && ep->num)
		वापस -EINVAL;
	req = container_of(usbreq, काष्ठा pch_udc_request, req);
	अगर (!list_empty(&req->queue))
		वापस -EINVAL;
	अगर (!dev->driver || (dev->gadget.speed == USB_SPEED_UNKNOWN))
		वापस -ESHUTDOWN;
	spin_lock_irqsave(&dev->lock, अगरlags);
	/* map the buffer क्रम dma */
	retval = usb_gadget_map_request(&dev->gadget, usbreq, ep->in);
	अगर (retval)
		जाओ probe_end;
	अगर (usbreq->length > 0) अणु
		retval = prepare_dma(ep, req, GFP_ATOMIC);
		अगर (retval)
			जाओ probe_end;
	पूर्ण
	usbreq->actual = 0;
	usbreq->status = -EINPROGRESS;
	req->dma_करोne = 0;
	अगर (list_empty(&ep->queue) && !ep->halted) अणु
		/* no pending transfer, so start this req */
		अगर (!usbreq->length) अणु
			process_zlp(ep, req);
			retval = 0;
			जाओ probe_end;
		पूर्ण
		अगर (!ep->in) अणु
			pch_udc_start_rxrequest(ep, req);
		पूर्ण अन्यथा अणु
			/*
			* For IN trfr the descriptors will be programmed and
			* P bit will be set when
			* we get an IN token
			*/
			pch_udc_रुको_ep_stall(ep);
			pch_udc_ep_clear_nak(ep);
			pch_udc_enable_ep_पूर्णांकerrupts(ep->dev, (1 << ep->num));
		पूर्ण
	पूर्ण
	/* Now add this request to the ep's pending requests */
	अगर (req != शून्य)
		list_add_tail(&req->queue, &ep->queue);

probe_end:
	spin_unlock_irqrestore(&dev->lock, अगरlags);
	वापस retval;
पूर्ण

/**
 * pch_udc_pcd_dequeue() - This function de-queues a request packet.
 *				It is called by gadget driver
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 * @usbreq:	Reference to the USB request
 *
 * Return codes:
 *	0:			Success
 *	linux error number:	Failure
 */
अटल पूर्णांक pch_udc_pcd_dequeue(काष्ठा usb_ep *usbep,
				काष्ठा usb_request *usbreq)
अणु
	काष्ठा pch_udc_ep	*ep;
	काष्ठा pch_udc_request	*req;
	अचिन्हित दीर्घ		flags;
	पूर्णांक ret = -EINVAL;

	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	अगर (!usbep || !usbreq || (!ep->ep.desc && ep->num))
		वापस ret;
	req = container_of(usbreq, काष्ठा pch_udc_request, req);
	spin_lock_irqsave(&ep->dev->lock, flags);
	/* make sure it's still queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == usbreq) अणु
			pch_udc_ep_set_nak(ep);
			अगर (!list_empty(&req->queue))
				complete_req(ep, req, -ECONNRESET);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ep->dev->lock, flags);
	वापस ret;
पूर्ण

/**
 * pch_udc_pcd_set_halt() - This function Sets or clear the endpoपूर्णांक halt
 *			    feature
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 * @halt:	Specअगरies whether to set or clear the feature
 *
 * Return codes:
 *	0:			Success
 *	linux error number:	Failure
 */
अटल पूर्णांक pch_udc_pcd_set_halt(काष्ठा usb_ep *usbep, पूर्णांक halt)
अणु
	काष्ठा pch_udc_ep	*ep;
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक ret;

	अगर (!usbep)
		वापस -EINVAL;
	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	अगर (!ep->ep.desc && !ep->num)
		वापस -EINVAL;
	अगर (!ep->dev->driver || (ep->dev->gadget.speed == USB_SPEED_UNKNOWN))
		वापस -ESHUTDOWN;
	spin_lock_irqsave(&udc_stall_spinlock, अगरlags);
	अगर (list_empty(&ep->queue)) अणु
		अगर (halt) अणु
			अगर (ep->num == PCH_UDC_EP0)
				ep->dev->stall = 1;
			pch_udc_ep_set_stall(ep);
			pch_udc_enable_ep_पूर्णांकerrupts(
				ep->dev, PCH_UDC_EPINT(ep->in, ep->num));
		पूर्ण अन्यथा अणु
			pch_udc_ep_clear_stall(ep);
		पूर्ण
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EAGAIN;
	पूर्ण
	spin_unlock_irqrestore(&udc_stall_spinlock, अगरlags);
	वापस ret;
पूर्ण

/**
 * pch_udc_pcd_set_wedge() - This function Sets or clear the endpoपूर्णांक
 *				halt feature
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 *
 * Return codes:
 *	0:			Success
 *	linux error number:	Failure
 */
अटल पूर्णांक pch_udc_pcd_set_wedge(काष्ठा usb_ep *usbep)
अणु
	काष्ठा pch_udc_ep	*ep;
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक ret;

	अगर (!usbep)
		वापस -EINVAL;
	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	अगर (!ep->ep.desc && !ep->num)
		वापस -EINVAL;
	अगर (!ep->dev->driver || (ep->dev->gadget.speed == USB_SPEED_UNKNOWN))
		वापस -ESHUTDOWN;
	spin_lock_irqsave(&udc_stall_spinlock, अगरlags);
	अगर (!list_empty(&ep->queue)) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		अगर (ep->num == PCH_UDC_EP0)
			ep->dev->stall = 1;
		pch_udc_ep_set_stall(ep);
		pch_udc_enable_ep_पूर्णांकerrupts(ep->dev,
					     PCH_UDC_EPINT(ep->in, ep->num));
		ep->dev->prot_stall = 1;
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&udc_stall_spinlock, अगरlags);
	वापस ret;
पूर्ण

/**
 * pch_udc_pcd_fअगरo_flush() - This function Flush the FIFO of specअगरied endpoपूर्णांक
 * @usbep:	Reference to the USB endpoपूर्णांक काष्ठाure
 */
अटल व्योम pch_udc_pcd_fअगरo_flush(काष्ठा usb_ep *usbep)
अणु
	काष्ठा pch_udc_ep  *ep;

	अगर (!usbep)
		वापस;

	ep = container_of(usbep, काष्ठा pch_udc_ep, ep);
	अगर (ep->ep.desc || !ep->num)
		pch_udc_ep_fअगरo_flush(ep, ep->in);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops pch_udc_ep_ops = अणु
	.enable		= pch_udc_pcd_ep_enable,
	.disable	= pch_udc_pcd_ep_disable,
	.alloc_request	= pch_udc_alloc_request,
	.मुक्त_request	= pch_udc_मुक्त_request,
	.queue		= pch_udc_pcd_queue,
	.dequeue	= pch_udc_pcd_dequeue,
	.set_halt	= pch_udc_pcd_set_halt,
	.set_wedge	= pch_udc_pcd_set_wedge,
	.fअगरo_status	= शून्य,
	.fअगरo_flush	= pch_udc_pcd_fअगरo_flush,
पूर्ण;

/**
 * pch_udc_init_setup_buff() - This function initializes the SETUP buffer
 * @td_stp:	Reference to the SETP buffer काष्ठाure
 */
अटल व्योम pch_udc_init_setup_buff(काष्ठा pch_udc_stp_dma_desc *td_stp)
अणु
	अटल u32	pky_marker;

	अगर (!td_stp)
		वापस;
	td_stp->reserved = ++pky_marker;
	स_रखो(&td_stp->request, 0xFF, माप td_stp->request);
	td_stp->status = PCH_UDC_BS_HST_RDY;
पूर्ण

/**
 * pch_udc_start_next_txrequest() - This function starts
 *					the next transmission requirement
 * @ep:	Reference to the endpoपूर्णांक काष्ठाure
 */
अटल व्योम pch_udc_start_next_txrequest(काष्ठा pch_udc_ep *ep)
अणु
	काष्ठा pch_udc_request *req;
	काष्ठा pch_udc_data_dma_desc *td_data;

	अगर (pch_udc_पढ़ो_ep_control(ep) & UDC_EPCTL_P)
		वापस;

	अगर (list_empty(&ep->queue))
		वापस;

	/* next request */
	req = list_entry(ep->queue.next, काष्ठा pch_udc_request, queue);
	अगर (req->dma_going)
		वापस;
	अगर (!req->td_data)
		वापस;
	pch_udc_रुको_ep_stall(ep);
	req->dma_going = 1;
	pch_udc_ep_set_ddptr(ep, 0);
	td_data = req->td_data;
	जबतक (1) अणु
		td_data->status = (td_data->status & ~PCH_UDC_BUFF_STS) |
				   PCH_UDC_BS_HST_RDY;
		अगर ((td_data->status & PCH_UDC_DMA_LAST) == PCH_UDC_DMA_LAST)
			अवरोध;
		td_data = phys_to_virt(td_data->next);
	पूर्ण
	pch_udc_ep_set_ddptr(ep, req->td_data_phys);
	pch_udc_set_dma(ep->dev, DMA_सूची_TX);
	pch_udc_ep_set_pd(ep);
	pch_udc_enable_ep_पूर्णांकerrupts(ep->dev, PCH_UDC_EPINT(ep->in, ep->num));
	pch_udc_ep_clear_nak(ep);
पूर्ण

/**
 * pch_udc_complete_transfer() - This function completes a transfer
 * @ep:		Reference to the endpoपूर्णांक काष्ठाure
 */
अटल व्योम pch_udc_complete_transfer(काष्ठा pch_udc_ep *ep)
अणु
	काष्ठा pch_udc_request *req;
	काष्ठा pch_udc_dev *dev = ep->dev;

	अगर (list_empty(&ep->queue))
		वापस;
	req = list_entry(ep->queue.next, काष्ठा pch_udc_request, queue);
	अगर ((req->td_data_last->status & PCH_UDC_BUFF_STS) !=
	    PCH_UDC_BS_DMA_DONE)
		वापस;
	अगर ((req->td_data_last->status & PCH_UDC_RXTX_STS) !=
	     PCH_UDC_RTS_SUCC) अणु
		dev_err(&dev->pdev->dev, "Invalid RXTX status (0x%08x) "
			"epstatus=0x%08x\n",
		       (req->td_data_last->status & PCH_UDC_RXTX_STS),
		       (पूर्णांक)(ep->epsts));
		वापस;
	पूर्ण

	req->req.actual = req->req.length;
	req->td_data_last->status = PCH_UDC_BS_HST_BSY | PCH_UDC_DMA_LAST;
	req->td_data->status = PCH_UDC_BS_HST_BSY | PCH_UDC_DMA_LAST;
	complete_req(ep, req, 0);
	req->dma_going = 0;
	अगर (!list_empty(&ep->queue)) अणु
		pch_udc_रुको_ep_stall(ep);
		pch_udc_ep_clear_nak(ep);
		pch_udc_enable_ep_पूर्णांकerrupts(ep->dev,
					     PCH_UDC_EPINT(ep->in, ep->num));
	पूर्ण अन्यथा अणु
		pch_udc_disable_ep_पूर्णांकerrupts(ep->dev,
					      PCH_UDC_EPINT(ep->in, ep->num));
	पूर्ण
पूर्ण

/**
 * pch_udc_complete_receiver() - This function completes a receiver
 * @ep:		Reference to the endpoपूर्णांक काष्ठाure
 */
अटल व्योम pch_udc_complete_receiver(काष्ठा pch_udc_ep *ep)
अणु
	काष्ठा pch_udc_request *req;
	काष्ठा pch_udc_dev *dev = ep->dev;
	अचिन्हित पूर्णांक count;
	काष्ठा pch_udc_data_dma_desc *td;
	dma_addr_t addr;

	अगर (list_empty(&ep->queue))
		वापस;
	/* next request */
	req = list_entry(ep->queue.next, काष्ठा pch_udc_request, queue);
	pch_udc_clear_dma(ep->dev, DMA_सूची_RX);
	pch_udc_ep_set_ddptr(ep, 0);
	अगर ((req->td_data_last->status & PCH_UDC_BUFF_STS) ==
	    PCH_UDC_BS_DMA_DONE)
		td = req->td_data_last;
	अन्यथा
		td = req->td_data;

	जबतक (1) अणु
		अगर ((td->status & PCH_UDC_RXTX_STS) != PCH_UDC_RTS_SUCC) अणु
			dev_err(&dev->pdev->dev, "Invalid RXTX status=0x%08x "
				"epstatus=0x%08x\n",
				(req->td_data->status & PCH_UDC_RXTX_STS),
				(पूर्णांक)(ep->epsts));
			वापस;
		पूर्ण
		अगर ((td->status & PCH_UDC_BUFF_STS) == PCH_UDC_BS_DMA_DONE)
			अगर (td->status & PCH_UDC_DMA_LAST) अणु
				count = td->status & PCH_UDC_RXTX_BYTES;
				अवरोध;
			पूर्ण
		अगर (td == req->td_data_last) अणु
			dev_err(&dev->pdev->dev, "Not complete RX descriptor");
			वापस;
		पूर्ण
		addr = (dma_addr_t)td->next;
		td = phys_to_virt(addr);
	पूर्ण
	/* on 64k packets the RXBYTES field is zero */
	अगर (!count && (req->req.length == UDC_DMA_MAXPACKET))
		count = UDC_DMA_MAXPACKET;
	req->td_data->status |= PCH_UDC_DMA_LAST;
	td->status |= PCH_UDC_BS_HST_BSY;

	req->dma_going = 0;
	req->req.actual = count;
	complete_req(ep, req, 0);
	/* If there is a new/failed requests try that now */
	अगर (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा pch_udc_request, queue);
		pch_udc_start_rxrequest(ep, req);
	पूर्ण
पूर्ण

/**
 * pch_udc_svc_data_in() - This function process endpoपूर्णांक पूर्णांकerrupts
 *				क्रम IN endpoपूर्णांकs
 * @dev:	Reference to the device काष्ठाure
 * @ep_num:	Endpoपूर्णांक that generated the पूर्णांकerrupt
 */
अटल व्योम pch_udc_svc_data_in(काष्ठा pch_udc_dev *dev, पूर्णांक ep_num)
अणु
	u32	epsts;
	काष्ठा pch_udc_ep	*ep;

	ep = &dev->ep[UDC_EPIN_IDX(ep_num)];
	epsts = ep->epsts;
	ep->epsts = 0;

	अगर (!(epsts & (UDC_EPSTS_IN | UDC_EPSTS_BNA  | UDC_EPSTS_HE |
		       UDC_EPSTS_TDC | UDC_EPSTS_RCS | UDC_EPSTS_TXEMPTY |
		       UDC_EPSTS_RSS | UDC_EPSTS_XFERDONE)))
		वापस;
	अगर ((epsts & UDC_EPSTS_BNA))
		वापस;
	अगर (epsts & UDC_EPSTS_HE)
		वापस;
	अगर (epsts & UDC_EPSTS_RSS) अणु
		pch_udc_ep_set_stall(ep);
		pch_udc_enable_ep_पूर्णांकerrupts(ep->dev,
					     PCH_UDC_EPINT(ep->in, ep->num));
	पूर्ण
	अगर (epsts & UDC_EPSTS_RCS) अणु
		अगर (!dev->prot_stall) अणु
			pch_udc_ep_clear_stall(ep);
		पूर्ण अन्यथा अणु
			pch_udc_ep_set_stall(ep);
			pch_udc_enable_ep_पूर्णांकerrupts(ep->dev,
						PCH_UDC_EPINT(ep->in, ep->num));
		पूर्ण
	पूर्ण
	अगर (epsts & UDC_EPSTS_TDC)
		pch_udc_complete_transfer(ep);
	/* On IN पूर्णांकerrupt, provide data अगर we have any */
	अगर ((epsts & UDC_EPSTS_IN) && !(epsts & UDC_EPSTS_RSS) &&
	    !(epsts & UDC_EPSTS_TDC) && !(epsts & UDC_EPSTS_TXEMPTY))
		pch_udc_start_next_txrequest(ep);
पूर्ण

/**
 * pch_udc_svc_data_out() - Handles पूर्णांकerrupts from OUT endpoपूर्णांक
 * @dev:	Reference to the device काष्ठाure
 * @ep_num:	Endpoपूर्णांक that generated the पूर्णांकerrupt
 */
अटल व्योम pch_udc_svc_data_out(काष्ठा pch_udc_dev *dev, पूर्णांक ep_num)
अणु
	u32			epsts;
	काष्ठा pch_udc_ep		*ep;
	काष्ठा pch_udc_request		*req = शून्य;

	ep = &dev->ep[UDC_EPOUT_IDX(ep_num)];
	epsts = ep->epsts;
	ep->epsts = 0;

	अगर ((epsts & UDC_EPSTS_BNA) && (!list_empty(&ep->queue))) अणु
		/* next request */
		req = list_entry(ep->queue.next, काष्ठा pch_udc_request,
				 queue);
		अगर ((req->td_data_last->status & PCH_UDC_BUFF_STS) !=
		     PCH_UDC_BS_DMA_DONE) अणु
			अगर (!req->dma_going)
				pch_udc_start_rxrequest(ep, req);
			वापस;
		पूर्ण
	पूर्ण
	अगर (epsts & UDC_EPSTS_HE)
		वापस;
	अगर (epsts & UDC_EPSTS_RSS) अणु
		pch_udc_ep_set_stall(ep);
		pch_udc_enable_ep_पूर्णांकerrupts(ep->dev,
					     PCH_UDC_EPINT(ep->in, ep->num));
	पूर्ण
	अगर (epsts & UDC_EPSTS_RCS) अणु
		अगर (!dev->prot_stall) अणु
			pch_udc_ep_clear_stall(ep);
		पूर्ण अन्यथा अणु
			pch_udc_ep_set_stall(ep);
			pch_udc_enable_ep_पूर्णांकerrupts(ep->dev,
						PCH_UDC_EPINT(ep->in, ep->num));
		पूर्ण
	पूर्ण
	अगर (((epsts & UDC_EPSTS_OUT_MASK) >> UDC_EPSTS_OUT_SHIFT) ==
	    UDC_EPSTS_OUT_DATA) अणु
		अगर (ep->dev->prot_stall == 1) अणु
			pch_udc_ep_set_stall(ep);
			pch_udc_enable_ep_पूर्णांकerrupts(ep->dev,
						PCH_UDC_EPINT(ep->in, ep->num));
		पूर्ण अन्यथा अणु
			pch_udc_complete_receiver(ep);
		पूर्ण
	पूर्ण
	अगर (list_empty(&ep->queue))
		pch_udc_set_dma(dev, DMA_सूची_RX);
पूर्ण

अटल पूर्णांक pch_udc_gadget_setup(काष्ठा pch_udc_dev *dev)
	__must_hold(&dev->lock)
अणु
	पूर्णांक rc;

	/* In some हालs we can get an पूर्णांकerrupt beक्रमe driver माला_लो setup */
	अगर (!dev->driver)
		वापस -ESHUTDOWN;

	spin_unlock(&dev->lock);
	rc = dev->driver->setup(&dev->gadget, &dev->setup_data);
	spin_lock(&dev->lock);
	वापस rc;
पूर्ण

/**
 * pch_udc_svc_control_in() - Handle Control IN endpoपूर्णांक पूर्णांकerrupts
 * @dev:	Reference to the device काष्ठाure
 */
अटल व्योम pch_udc_svc_control_in(काष्ठा pch_udc_dev *dev)
अणु
	u32	epsts;
	काष्ठा pch_udc_ep	*ep;
	काष्ठा pch_udc_ep	*ep_out;

	ep = &dev->ep[UDC_EP0IN_IDX];
	ep_out = &dev->ep[UDC_EP0OUT_IDX];
	epsts = ep->epsts;
	ep->epsts = 0;

	अगर (!(epsts & (UDC_EPSTS_IN | UDC_EPSTS_BNA | UDC_EPSTS_HE |
		       UDC_EPSTS_TDC | UDC_EPSTS_RCS | UDC_EPSTS_TXEMPTY |
		       UDC_EPSTS_XFERDONE)))
		वापस;
	अगर ((epsts & UDC_EPSTS_BNA))
		वापस;
	अगर (epsts & UDC_EPSTS_HE)
		वापस;
	अगर ((epsts & UDC_EPSTS_TDC) && (!dev->stall)) अणु
		pch_udc_complete_transfer(ep);
		pch_udc_clear_dma(dev, DMA_सूची_RX);
		ep_out->td_data->status = (ep_out->td_data->status &
					~PCH_UDC_BUFF_STS) |
					PCH_UDC_BS_HST_RDY;
		pch_udc_ep_clear_nak(ep_out);
		pch_udc_set_dma(dev, DMA_सूची_RX);
		pch_udc_ep_set_rrdy(ep_out);
	पूर्ण
	/* On IN पूर्णांकerrupt, provide data अगर we have any */
	अगर ((epsts & UDC_EPSTS_IN) && !(epsts & UDC_EPSTS_TDC) &&
	     !(epsts & UDC_EPSTS_TXEMPTY))
		pch_udc_start_next_txrequest(ep);
पूर्ण

/**
 * pch_udc_svc_control_out() - Routine that handle Control
 *					OUT endpoपूर्णांक पूर्णांकerrupts
 * @dev:	Reference to the device काष्ठाure
 */
अटल व्योम pch_udc_svc_control_out(काष्ठा pch_udc_dev *dev)
	__releases(&dev->lock)
	__acquires(&dev->lock)
अणु
	u32	stat;
	पूर्णांक setup_supported;
	काष्ठा pch_udc_ep	*ep;

	ep = &dev->ep[UDC_EP0OUT_IDX];
	stat = ep->epsts;
	ep->epsts = 0;

	/* If setup data */
	अगर (((stat & UDC_EPSTS_OUT_MASK) >> UDC_EPSTS_OUT_SHIFT) ==
	    UDC_EPSTS_OUT_SETUP) अणु
		dev->stall = 0;
		dev->ep[UDC_EP0IN_IDX].halted = 0;
		dev->ep[UDC_EP0OUT_IDX].halted = 0;
		dev->setup_data = ep->td_stp->request;
		pch_udc_init_setup_buff(ep->td_stp);
		pch_udc_clear_dma(dev, DMA_सूची_RX);
		pch_udc_ep_fअगरo_flush(&(dev->ep[UDC_EP0IN_IDX]),
				      dev->ep[UDC_EP0IN_IDX].in);
		अगर ((dev->setup_data.bRequestType & USB_सूची_IN))
			dev->gadget.ep0 = &dev->ep[UDC_EP0IN_IDX].ep;
		अन्यथा /* OUT */
			dev->gadget.ep0 = &ep->ep;
		/* If Mass storage Reset */
		अगर ((dev->setup_data.bRequestType == 0x21) &&
		    (dev->setup_data.bRequest == 0xFF))
			dev->prot_stall = 0;
		/* call gadget with setup data received */
		setup_supported = pch_udc_gadget_setup(dev);

		अगर (dev->setup_data.bRequestType & USB_सूची_IN) अणु
			ep->td_data->status = (ep->td_data->status &
						~PCH_UDC_BUFF_STS) |
						PCH_UDC_BS_HST_RDY;
			pch_udc_ep_set_ddptr(ep, ep->td_data_phys);
		पूर्ण
		/* ep0 in वापसs data on IN phase */
		अगर (setup_supported >= 0 && setup_supported <
					    UDC_EP0IN_MAX_PKT_SIZE) अणु
			pch_udc_ep_clear_nak(&(dev->ep[UDC_EP0IN_IDX]));
			/* Gadget would have queued a request when
			 * we called the setup */
			अगर (!(dev->setup_data.bRequestType & USB_सूची_IN)) अणु
				pch_udc_set_dma(dev, DMA_सूची_RX);
				pch_udc_ep_clear_nak(ep);
			पूर्ण
		पूर्ण अन्यथा अगर (setup_supported < 0) अणु
			/* अगर unsupported request, then stall */
			pch_udc_ep_set_stall(&(dev->ep[UDC_EP0IN_IDX]));
			pch_udc_enable_ep_पूर्णांकerrupts(ep->dev,
						PCH_UDC_EPINT(ep->in, ep->num));
			dev->stall = 0;
			pch_udc_set_dma(dev, DMA_सूची_RX);
		पूर्ण अन्यथा अणु
			dev->रुकोing_zlp_ack = 1;
		पूर्ण
	पूर्ण अन्यथा अगर ((((stat & UDC_EPSTS_OUT_MASK) >> UDC_EPSTS_OUT_SHIFT) ==
		     UDC_EPSTS_OUT_DATA) && !dev->stall) अणु
		pch_udc_clear_dma(dev, DMA_सूची_RX);
		pch_udc_ep_set_ddptr(ep, 0);
		अगर (!list_empty(&ep->queue)) अणु
			ep->epsts = stat;
			pch_udc_svc_data_out(dev, PCH_UDC_EP0);
		पूर्ण
		pch_udc_set_dma(dev, DMA_सूची_RX);
	पूर्ण
	pch_udc_ep_set_rrdy(ep);
पूर्ण


/**
 * pch_udc_postsvc_epपूर्णांकers() - This function enables end poपूर्णांक पूर्णांकerrupts
 *				and clears NAK status
 * @dev:	Reference to the device काष्ठाure
 * @ep_num:	End poपूर्णांक number
 */
अटल व्योम pch_udc_postsvc_epपूर्णांकers(काष्ठा pch_udc_dev *dev, पूर्णांक ep_num)
अणु
	काष्ठा pch_udc_ep	*ep = &dev->ep[UDC_EPIN_IDX(ep_num)];
	अगर (list_empty(&ep->queue))
		वापस;
	pch_udc_enable_ep_पूर्णांकerrupts(ep->dev, PCH_UDC_EPINT(ep->in, ep->num));
	pch_udc_ep_clear_nak(ep);
पूर्ण

/**
 * pch_udc_पढ़ो_all_epstatus() - This function पढ़ो all endpoपूर्णांक status
 * @dev:	Reference to the device काष्ठाure
 * @ep_पूर्णांकr:	Status of endpoपूर्णांक पूर्णांकerrupt
 */
अटल व्योम pch_udc_पढ़ो_all_epstatus(काष्ठा pch_udc_dev *dev, u32 ep_पूर्णांकr)
अणु
	पूर्णांक i;
	काष्ठा pch_udc_ep	*ep;

	क्रम (i = 0; i < PCH_UDC_USED_EP_NUM; i++) अणु
		/* IN */
		अगर (ep_पूर्णांकr & (0x1 << i)) अणु
			ep = &dev->ep[UDC_EPIN_IDX(i)];
			ep->epsts = pch_udc_पढ़ो_ep_status(ep);
			pch_udc_clear_ep_status(ep, ep->epsts);
		पूर्ण
		/* OUT */
		अगर (ep_पूर्णांकr & (0x10000 << i)) अणु
			ep = &dev->ep[UDC_EPOUT_IDX(i)];
			ep->epsts = pch_udc_पढ़ो_ep_status(ep);
			pch_udc_clear_ep_status(ep, ep->epsts);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * pch_udc_activate_control_ep() - This function enables the control endpoपूर्णांकs
 *					क्रम traffic after a reset
 * @dev:	Reference to the device काष्ठाure
 */
अटल व्योम pch_udc_activate_control_ep(काष्ठा pch_udc_dev *dev)
अणु
	काष्ठा pch_udc_ep	*ep;
	u32 val;

	/* Setup the IN endpoपूर्णांक */
	ep = &dev->ep[UDC_EP0IN_IDX];
	pch_udc_clear_ep_control(ep);
	pch_udc_ep_fअगरo_flush(ep, ep->in);
	pch_udc_ep_set_bufsz(ep, UDC_EP0IN_BUFF_SIZE, ep->in);
	pch_udc_ep_set_maxpkt(ep, UDC_EP0IN_MAX_PKT_SIZE);
	/* Initialize the IN EP Descriptor */
	ep->td_data      = शून्य;
	ep->td_stp       = शून्य;
	ep->td_data_phys = 0;
	ep->td_stp_phys  = 0;

	/* Setup the OUT endpoपूर्णांक */
	ep = &dev->ep[UDC_EP0OUT_IDX];
	pch_udc_clear_ep_control(ep);
	pch_udc_ep_fअगरo_flush(ep, ep->in);
	pch_udc_ep_set_bufsz(ep, UDC_EP0OUT_BUFF_SIZE, ep->in);
	pch_udc_ep_set_maxpkt(ep, UDC_EP0OUT_MAX_PKT_SIZE);
	val = UDC_EP0OUT_MAX_PKT_SIZE << UDC_CSR_NE_MAX_PKT_SHIFT;
	pch_udc_ग_लिखो_csr(ep->dev, val, UDC_EP0OUT_IDX);

	/* Initialize the SETUP buffer */
	pch_udc_init_setup_buff(ep->td_stp);
	/* Write the poपूर्णांकer address of dma descriptor */
	pch_udc_ep_set_subptr(ep, ep->td_stp_phys);
	/* Write the poपूर्णांकer address of Setup descriptor */
	pch_udc_ep_set_ddptr(ep, ep->td_data_phys);

	/* Initialize the dma descriptor */
	ep->td_data->status  = PCH_UDC_DMA_LAST;
	ep->td_data->dataptr = dev->dma_addr;
	ep->td_data->next    = ep->td_data_phys;

	pch_udc_ep_clear_nak(ep);
पूर्ण


/**
 * pch_udc_svc_ur_पूर्णांकerrupt() - This function handles a USB reset पूर्णांकerrupt
 * @dev:	Reference to driver काष्ठाure
 */
अटल व्योम pch_udc_svc_ur_पूर्णांकerrupt(काष्ठा pch_udc_dev *dev)
अणु
	काष्ठा pch_udc_ep	*ep;
	पूर्णांक i;

	pch_udc_clear_dma(dev, DMA_सूची_TX);
	pch_udc_clear_dma(dev, DMA_सूची_RX);
	/* Mask all endpoपूर्णांक पूर्णांकerrupts */
	pch_udc_disable_ep_पूर्णांकerrupts(dev, UDC_EPINT_MSK_DISABLE_ALL);
	/* clear all endpoपूर्णांक पूर्णांकerrupts */
	pch_udc_ग_लिखो_ep_पूर्णांकerrupts(dev, UDC_EPINT_MSK_DISABLE_ALL);

	क्रम (i = 0; i < PCH_UDC_EP_NUM; i++) अणु
		ep = &dev->ep[i];
		pch_udc_clear_ep_status(ep, UDC_EPSTS_ALL_CLR_MASK);
		pch_udc_clear_ep_control(ep);
		pch_udc_ep_set_ddptr(ep, 0);
		pch_udc_ग_लिखो_csr(ep->dev, 0x00, i);
	पूर्ण
	dev->stall = 0;
	dev->prot_stall = 0;
	dev->रुकोing_zlp_ack = 0;
	dev->set_cfg_not_acked = 0;

	/* disable ep to empty req queue. Skip the control EP's */
	क्रम (i = 0; i < (PCH_UDC_USED_EP_NUM*2); i++) अणु
		ep = &dev->ep[i];
		pch_udc_ep_set_nak(ep);
		pch_udc_ep_fअगरo_flush(ep, ep->in);
		/* Complete request queue */
		empty_req_queue(ep);
	पूर्ण
	अगर (dev->driver) अणु
		spin_unlock(&dev->lock);
		usb_gadget_udc_reset(&dev->gadget, dev->driver);
		spin_lock(&dev->lock);
	पूर्ण
पूर्ण

/**
 * pch_udc_svc_क्रमागत_पूर्णांकerrupt() - This function handles a USB speed क्रमागतeration
 *				करोne पूर्णांकerrupt
 * @dev:	Reference to driver काष्ठाure
 */
अटल व्योम pch_udc_svc_क्रमागत_पूर्णांकerrupt(काष्ठा pch_udc_dev *dev)
अणु
	u32 dev_stat, dev_speed;
	u32 speed = USB_SPEED_FULL;

	dev_stat = pch_udc_पढ़ो_device_status(dev);
	dev_speed = (dev_stat & UDC_DEVSTS_ENUM_SPEED_MASK) >>
						 UDC_DEVSTS_ENUM_SPEED_SHIFT;
	चयन (dev_speed) अणु
	हाल UDC_DEVSTS_ENUM_SPEED_HIGH:
		speed = USB_SPEED_HIGH;
		अवरोध;
	हाल  UDC_DEVSTS_ENUM_SPEED_FULL:
		speed = USB_SPEED_FULL;
		अवरोध;
	हाल  UDC_DEVSTS_ENUM_SPEED_LOW:
		speed = USB_SPEED_LOW;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	dev->gadget.speed = speed;
	pch_udc_activate_control_ep(dev);
	pch_udc_enable_ep_पूर्णांकerrupts(dev, UDC_EPINT_IN_EP0 | UDC_EPINT_OUT_EP0);
	pch_udc_set_dma(dev, DMA_सूची_TX);
	pch_udc_set_dma(dev, DMA_सूची_RX);
	pch_udc_ep_set_rrdy(&(dev->ep[UDC_EP0OUT_IDX]));

	/* enable device पूर्णांकerrupts */
	pch_udc_enable_पूर्णांकerrupts(dev, UDC_DEVINT_UR | UDC_DEVINT_US |
					UDC_DEVINT_ES | UDC_DEVINT_ENUM |
					UDC_DEVINT_SI | UDC_DEVINT_SC);
पूर्ण

/**
 * pch_udc_svc_पूर्णांकf_पूर्णांकerrupt() - This function handles a set पूर्णांकerface
 *				  पूर्णांकerrupt
 * @dev:	Reference to driver काष्ठाure
 */
अटल व्योम pch_udc_svc_पूर्णांकf_पूर्णांकerrupt(काष्ठा pch_udc_dev *dev)
अणु
	u32 reg, dev_stat = 0;
	पूर्णांक i;

	dev_stat = pch_udc_पढ़ो_device_status(dev);
	dev->cfg_data.cur_पूर्णांकf = (dev_stat & UDC_DEVSTS_INTF_MASK) >>
							 UDC_DEVSTS_INTF_SHIFT;
	dev->cfg_data.cur_alt = (dev_stat & UDC_DEVSTS_ALT_MASK) >>
							 UDC_DEVSTS_ALT_SHIFT;
	dev->set_cfg_not_acked = 1;
	/* Conकाष्ठा the usb request क्रम gadget driver and inक्रमm it */
	स_रखो(&dev->setup_data, 0 , माप dev->setup_data);
	dev->setup_data.bRequest = USB_REQ_SET_INTERFACE;
	dev->setup_data.bRequestType = USB_RECIP_INTERFACE;
	dev->setup_data.wValue = cpu_to_le16(dev->cfg_data.cur_alt);
	dev->setup_data.wIndex = cpu_to_le16(dev->cfg_data.cur_पूर्णांकf);
	/* programm the Endpoपूर्णांक Cfg रेजिस्टरs */
	/* Only one end poपूर्णांक cfg रेजिस्टर */
	reg = pch_udc_पढ़ो_csr(dev, UDC_EP0OUT_IDX);
	reg = (reg & ~UDC_CSR_NE_INTF_MASK) |
	      (dev->cfg_data.cur_पूर्णांकf << UDC_CSR_NE_INTF_SHIFT);
	reg = (reg & ~UDC_CSR_NE_ALT_MASK) |
	      (dev->cfg_data.cur_alt << UDC_CSR_NE_ALT_SHIFT);
	pch_udc_ग_लिखो_csr(dev, reg, UDC_EP0OUT_IDX);
	क्रम (i = 0; i < PCH_UDC_USED_EP_NUM * 2; i++) अणु
		/* clear stall bits */
		pch_udc_ep_clear_stall(&(dev->ep[i]));
		dev->ep[i].halted = 0;
	पूर्ण
	dev->stall = 0;
	pch_udc_gadget_setup(dev);
पूर्ण

/**
 * pch_udc_svc_cfg_पूर्णांकerrupt() - This function handles a set configuration
 *				पूर्णांकerrupt
 * @dev:	Reference to driver काष्ठाure
 */
अटल व्योम pch_udc_svc_cfg_पूर्णांकerrupt(काष्ठा pch_udc_dev *dev)
अणु
	पूर्णांक i;
	u32 reg, dev_stat = 0;

	dev_stat = pch_udc_पढ़ो_device_status(dev);
	dev->set_cfg_not_acked = 1;
	dev->cfg_data.cur_cfg = (dev_stat & UDC_DEVSTS_CFG_MASK) >>
				UDC_DEVSTS_CFG_SHIFT;
	/* make usb request क्रम gadget driver */
	स_रखो(&dev->setup_data, 0 , माप dev->setup_data);
	dev->setup_data.bRequest = USB_REQ_SET_CONFIGURATION;
	dev->setup_data.wValue = cpu_to_le16(dev->cfg_data.cur_cfg);
	/* program the NE रेजिस्टरs */
	/* Only one end poपूर्णांक cfg रेजिस्टर */
	reg = pch_udc_पढ़ो_csr(dev, UDC_EP0OUT_IDX);
	reg = (reg & ~UDC_CSR_NE_CFG_MASK) |
	      (dev->cfg_data.cur_cfg << UDC_CSR_NE_CFG_SHIFT);
	pch_udc_ग_लिखो_csr(dev, reg, UDC_EP0OUT_IDX);
	क्रम (i = 0; i < PCH_UDC_USED_EP_NUM * 2; i++) अणु
		/* clear stall bits */
		pch_udc_ep_clear_stall(&(dev->ep[i]));
		dev->ep[i].halted = 0;
	पूर्ण
	dev->stall = 0;

	/* call gadget zero with setup data received */
	pch_udc_gadget_setup(dev);
पूर्ण

/**
 * pch_udc_dev_isr() - This function services device पूर्णांकerrupts
 *			by invoking appropriate routines.
 * @dev:	Reference to the device काष्ठाure
 * @dev_पूर्णांकr:	The Device पूर्णांकerrupt status.
 */
अटल व्योम pch_udc_dev_isr(काष्ठा pch_udc_dev *dev, u32 dev_पूर्णांकr)
अणु
	पूर्णांक vbus;

	/* USB Reset Interrupt */
	अगर (dev_पूर्णांकr & UDC_DEVINT_UR) अणु
		pch_udc_svc_ur_पूर्णांकerrupt(dev);
		dev_dbg(&dev->pdev->dev, "USB_RESET\n");
	पूर्ण
	/* Enumeration Done Interrupt */
	अगर (dev_पूर्णांकr & UDC_DEVINT_ENUM) अणु
		pch_udc_svc_क्रमागत_पूर्णांकerrupt(dev);
		dev_dbg(&dev->pdev->dev, "USB_ENUM\n");
	पूर्ण
	/* Set Interface Interrupt */
	अगर (dev_पूर्णांकr & UDC_DEVINT_SI)
		pch_udc_svc_पूर्णांकf_पूर्णांकerrupt(dev);
	/* Set Config Interrupt */
	अगर (dev_पूर्णांकr & UDC_DEVINT_SC)
		pch_udc_svc_cfg_पूर्णांकerrupt(dev);
	/* USB Suspend पूर्णांकerrupt */
	अगर (dev_पूर्णांकr & UDC_DEVINT_US) अणु
		अगर (dev->driver
			&& dev->driver->suspend) अणु
			spin_unlock(&dev->lock);
			dev->driver->suspend(&dev->gadget);
			spin_lock(&dev->lock);
		पूर्ण

		vbus = pch_vbus_gpio_get_value(dev);
		अगर ((dev->vbus_session == 0)
			&& (vbus != 1)) अणु
			अगर (dev->driver && dev->driver->disconnect) अणु
				spin_unlock(&dev->lock);
				dev->driver->disconnect(&dev->gadget);
				spin_lock(&dev->lock);
			पूर्ण
			pch_udc_reconnect(dev);
		पूर्ण अन्यथा अगर ((dev->vbus_session == 0)
			&& (vbus == 1)
			&& !dev->vbus_gpio.पूर्णांकr)
			schedule_work(&dev->vbus_gpio.irq_work_fall);

		dev_dbg(&dev->pdev->dev, "USB_SUSPEND\n");
	पूर्ण
	/* Clear the SOF पूर्णांकerrupt, अगर enabled */
	अगर (dev_पूर्णांकr & UDC_DEVINT_SOF)
		dev_dbg(&dev->pdev->dev, "SOF\n");
	/* ES पूर्णांकerrupt, IDLE > 3ms on the USB */
	अगर (dev_पूर्णांकr & UDC_DEVINT_ES)
		dev_dbg(&dev->pdev->dev, "ES\n");
	/* RWKP पूर्णांकerrupt */
	अगर (dev_पूर्णांकr & UDC_DEVINT_RWKP)
		dev_dbg(&dev->pdev->dev, "RWKP\n");
पूर्ण

/**
 * pch_udc_isr() - This function handles पूर्णांकerrupts from the PCH USB Device
 * @irq:	Interrupt request number
 * @pdev:	Reference to the device काष्ठाure
 */
अटल irqवापस_t pch_udc_isr(पूर्णांक irq, व्योम *pdev)
अणु
	काष्ठा pch_udc_dev *dev = (काष्ठा pch_udc_dev *) pdev;
	u32 dev_पूर्णांकr, ep_पूर्णांकr;
	पूर्णांक i;

	dev_पूर्णांकr = pch_udc_पढ़ो_device_पूर्णांकerrupts(dev);
	ep_पूर्णांकr = pch_udc_पढ़ो_ep_पूर्णांकerrupts(dev);

	/* For a hot plug, this find that the controller is hung up. */
	अगर (dev_पूर्णांकr == ep_पूर्णांकr)
		अगर (dev_पूर्णांकr == pch_udc_पढ़ोl(dev, UDC_DEVCFG_ADDR)) अणु
			dev_dbg(&dev->pdev->dev, "UDC: Hung up\n");
			/* The controller is reset */
			pch_udc_ग_लिखोl(dev, UDC_SRST, UDC_SRST_ADDR);
			वापस IRQ_HANDLED;
		पूर्ण
	अगर (dev_पूर्णांकr)
		/* Clear device पूर्णांकerrupts */
		pch_udc_ग_लिखो_device_पूर्णांकerrupts(dev, dev_पूर्णांकr);
	अगर (ep_पूर्णांकr)
		/* Clear ep पूर्णांकerrupts */
		pch_udc_ग_लिखो_ep_पूर्णांकerrupts(dev, ep_पूर्णांकr);
	अगर (!dev_पूर्णांकr && !ep_पूर्णांकr)
		वापस IRQ_NONE;
	spin_lock(&dev->lock);
	अगर (dev_पूर्णांकr)
		pch_udc_dev_isr(dev, dev_पूर्णांकr);
	अगर (ep_पूर्णांकr) अणु
		pch_udc_पढ़ो_all_epstatus(dev, ep_पूर्णांकr);
		/* Process Control In पूर्णांकerrupts, अगर present */
		अगर (ep_पूर्णांकr & UDC_EPINT_IN_EP0) अणु
			pch_udc_svc_control_in(dev);
			pch_udc_postsvc_epपूर्णांकers(dev, 0);
		पूर्ण
		/* Process Control Out पूर्णांकerrupts, अगर present */
		अगर (ep_पूर्णांकr & UDC_EPINT_OUT_EP0)
			pch_udc_svc_control_out(dev);
		/* Process data in end poपूर्णांक पूर्णांकerrupts */
		क्रम (i = 1; i < PCH_UDC_USED_EP_NUM; i++) अणु
			अगर (ep_पूर्णांकr & (1 <<  i)) अणु
				pch_udc_svc_data_in(dev, i);
				pch_udc_postsvc_epपूर्णांकers(dev, i);
			पूर्ण
		पूर्ण
		/* Process data out end poपूर्णांक पूर्णांकerrupts */
		क्रम (i = UDC_EPINT_OUT_SHIFT + 1; i < (UDC_EPINT_OUT_SHIFT +
						 PCH_UDC_USED_EP_NUM); i++)
			अगर (ep_पूर्णांकr & (1 <<  i))
				pch_udc_svc_data_out(dev, i -
							 UDC_EPINT_OUT_SHIFT);
	पूर्ण
	spin_unlock(&dev->lock);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * pch_udc_setup_ep0() - This function enables control endpoपूर्णांक क्रम traffic
 * @dev:	Reference to the device काष्ठाure
 */
अटल व्योम pch_udc_setup_ep0(काष्ठा pch_udc_dev *dev)
अणु
	/* enable ep0 पूर्णांकerrupts */
	pch_udc_enable_ep_पूर्णांकerrupts(dev, UDC_EPINT_IN_EP0 |
						UDC_EPINT_OUT_EP0);
	/* enable device पूर्णांकerrupts */
	pch_udc_enable_पूर्णांकerrupts(dev, UDC_DEVINT_UR | UDC_DEVINT_US |
				       UDC_DEVINT_ES | UDC_DEVINT_ENUM |
				       UDC_DEVINT_SI | UDC_DEVINT_SC);
पूर्ण

/**
 * pch_udc_pcd_reinit() - This API initializes the endpoपूर्णांक काष्ठाures
 * @dev:	Reference to the driver काष्ठाure
 */
अटल व्योम pch_udc_pcd_reinit(काष्ठा pch_udc_dev *dev)
अणु
	स्थिर अक्षर *स्थिर ep_string[] = अणु
		ep0_string, "ep0out", "ep1in", "ep1out", "ep2in", "ep2out",
		"ep3in", "ep3out", "ep4in", "ep4out", "ep5in", "ep5out",
		"ep6in", "ep6out", "ep7in", "ep7out", "ep8in", "ep8out",
		"ep9in", "ep9out", "ep10in", "ep10out", "ep11in", "ep11out",
		"ep12in", "ep12out", "ep13in", "ep13out", "ep14in", "ep14out",
		"ep15in", "ep15out",
	पूर्ण;
	पूर्णांक i;

	dev->gadget.speed = USB_SPEED_UNKNOWN;
	INIT_LIST_HEAD(&dev->gadget.ep_list);

	/* Initialize the endpoपूर्णांकs काष्ठाures */
	स_रखो(dev->ep, 0, माप dev->ep);
	क्रम (i = 0; i < PCH_UDC_EP_NUM; i++) अणु
		काष्ठा pch_udc_ep *ep = &dev->ep[i];
		ep->dev = dev;
		ep->halted = 1;
		ep->num = i / 2;
		ep->in = ~i & 1;
		ep->ep.name = ep_string[i];
		ep->ep.ops = &pch_udc_ep_ops;
		अगर (ep->in) अणु
			ep->offset_addr = ep->num * UDC_EP_REG_SHIFT;
			ep->ep.caps.dir_in = true;
		पूर्ण अन्यथा अणु
			ep->offset_addr = (UDC_EPINT_OUT_SHIFT + ep->num) *
					  UDC_EP_REG_SHIFT;
			ep->ep.caps.dir_out = true;
		पूर्ण
		अगर (i == UDC_EP0IN_IDX || i == UDC_EP0OUT_IDX) अणु
			ep->ep.caps.type_control = true;
		पूर्ण अन्यथा अणु
			ep->ep.caps.type_iso = true;
			ep->ep.caps.type_bulk = true;
			ep->ep.caps.type_पूर्णांक = true;
		पूर्ण
		/* need to set ep->ep.maxpacket and set Default Configuration?*/
		usb_ep_set_maxpacket_limit(&ep->ep, UDC_BULK_MAX_PKT_SIZE);
		list_add_tail(&ep->ep.ep_list, &dev->gadget.ep_list);
		INIT_LIST_HEAD(&ep->queue);
	पूर्ण
	usb_ep_set_maxpacket_limit(&dev->ep[UDC_EP0IN_IDX].ep, UDC_EP0IN_MAX_PKT_SIZE);
	usb_ep_set_maxpacket_limit(&dev->ep[UDC_EP0OUT_IDX].ep, UDC_EP0OUT_MAX_PKT_SIZE);

	/* हटाओ ep0 in and out from the list.  They have own poपूर्णांकer */
	list_del_init(&dev->ep[UDC_EP0IN_IDX].ep.ep_list);
	list_del_init(&dev->ep[UDC_EP0OUT_IDX].ep.ep_list);

	dev->gadget.ep0 = &dev->ep[UDC_EP0IN_IDX].ep;
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);
पूर्ण

/**
 * pch_udc_pcd_init() - This API initializes the driver काष्ठाure
 * @dev:	Reference to the driver काष्ठाure
 *
 * Return codes:
 *	0:		Success
 *	-ERRNO:		All kind of errors when retrieving VBUS GPIO
 */
अटल पूर्णांक pch_udc_pcd_init(काष्ठा pch_udc_dev *dev)
अणु
	पूर्णांक ret;

	pch_udc_init(dev);
	pch_udc_pcd_reinit(dev);

	ret = pch_vbus_gpio_init(dev);
	अगर (ret)
		pch_udc_निकास(dev);
	वापस ret;
पूर्ण

/**
 * init_dma_pools() - create dma pools during initialization
 * @dev:	reference to काष्ठा pci_dev
 */
अटल पूर्णांक init_dma_pools(काष्ठा pch_udc_dev *dev)
अणु
	काष्ठा pch_udc_stp_dma_desc	*td_stp;
	काष्ठा pch_udc_data_dma_desc	*td_data;
	व्योम				*ep0out_buf;

	/* DMA setup */
	dev->data_requests = dma_pool_create("data_requests", &dev->pdev->dev,
		माप(काष्ठा pch_udc_data_dma_desc), 0, 0);
	अगर (!dev->data_requests) अणु
		dev_err(&dev->pdev->dev, "%s: can't get request data pool\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	/* dma desc क्रम setup data */
	dev->stp_requests = dma_pool_create("setup requests", &dev->pdev->dev,
		माप(काष्ठा pch_udc_stp_dma_desc), 0, 0);
	अगर (!dev->stp_requests) अणु
		dev_err(&dev->pdev->dev, "%s: can't get setup request pool\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	/* setup */
	td_stp = dma_pool_alloc(dev->stp_requests, GFP_KERNEL,
				&dev->ep[UDC_EP0OUT_IDX].td_stp_phys);
	अगर (!td_stp) अणु
		dev_err(&dev->pdev->dev,
			"%s: can't allocate setup dma descriptor\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	dev->ep[UDC_EP0OUT_IDX].td_stp = td_stp;

	/* data: 0 packets !? */
	td_data = dma_pool_alloc(dev->data_requests, GFP_KERNEL,
				&dev->ep[UDC_EP0OUT_IDX].td_data_phys);
	अगर (!td_data) अणु
		dev_err(&dev->pdev->dev,
			"%s: can't allocate data dma descriptor\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	dev->ep[UDC_EP0OUT_IDX].td_data = td_data;
	dev->ep[UDC_EP0IN_IDX].td_stp = शून्य;
	dev->ep[UDC_EP0IN_IDX].td_stp_phys = 0;
	dev->ep[UDC_EP0IN_IDX].td_data = शून्य;
	dev->ep[UDC_EP0IN_IDX].td_data_phys = 0;

	ep0out_buf = devm_kzalloc(&dev->pdev->dev, UDC_EP0OUT_BUFF_SIZE * 4,
				  GFP_KERNEL);
	अगर (!ep0out_buf)
		वापस -ENOMEM;
	dev->dma_addr = dma_map_single(&dev->pdev->dev, ep0out_buf,
				       UDC_EP0OUT_BUFF_SIZE * 4,
				       DMA_FROM_DEVICE);
	वापस dma_mapping_error(&dev->pdev->dev, dev->dma_addr);
पूर्ण

अटल पूर्णांक pch_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा pch_udc_dev	*dev = to_pch_udc(g);

	driver->driver.bus = शून्य;
	dev->driver = driver;

	/* get पढ़ोy क्रम ep0 traffic */
	pch_udc_setup_ep0(dev);

	/* clear SD */
	अगर ((pch_vbus_gpio_get_value(dev) != 0) || !dev->vbus_gpio.पूर्णांकr)
		pch_udc_clear_disconnect(dev);

	dev->connected = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक pch_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा pch_udc_dev	*dev = to_pch_udc(g);

	pch_udc_disable_पूर्णांकerrupts(dev, UDC_DEVINT_MSK);

	/* Assures that there are no pending requests with this driver */
	dev->driver = शून्य;
	dev->connected = 0;

	/* set SD */
	pch_udc_set_disconnect(dev);

	वापस 0;
पूर्ण

अटल व्योम pch_vbus_gpio_हटाओ_table(व्योम *table)
अणु
	gpiod_हटाओ_lookup_table(table);
पूर्ण

अटल पूर्णांक pch_vbus_gpio_add_table(काष्ठा device *d, व्योम *table)
अणु
	gpiod_add_lookup_table(table);
	वापस devm_add_action_or_reset(d, pch_vbus_gpio_हटाओ_table, table);
पूर्ण

अटल काष्ठा gpiod_lookup_table pch_udc_minnow_vbus_gpio_table = अणु
	.dev_id		= "0000:02:02.4",
	.table		= अणु
		GPIO_LOOKUP("sch_gpio.33158", 12, शून्य, GPIO_ACTIVE_HIGH),
		अणुपूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक pch_udc_minnow_platक्रमm_init(काष्ठा device *d)
अणु
	वापस pch_vbus_gpio_add_table(d, &pch_udc_minnow_vbus_gpio_table);
पूर्ण

अटल पूर्णांक pch_udc_quark_platक्रमm_init(काष्ठा device *d)
अणु
	काष्ठा pch_udc_dev *dev = dev_get_drvdata(d);

	dev->bar = PCH_UDC_PCI_BAR_QUARK_X1000;
	वापस 0;
पूर्ण

अटल व्योम pch_udc_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_udc_dev *dev = pci_get_drvdata(pdev);

	pch_udc_disable_पूर्णांकerrupts(dev, UDC_DEVINT_MSK);
	pch_udc_disable_ep_पूर्णांकerrupts(dev, UDC_EPINT_MSK_DISABLE_ALL);

	/* disable the pullup so the host will think we're gone */
	pch_udc_set_disconnect(dev);
पूर्ण

अटल व्योम pch_udc_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_udc_dev	*dev = pci_get_drvdata(pdev);

	usb_del_gadget_udc(&dev->gadget);

	/* gadget driver must not be रेजिस्टरed */
	अगर (dev->driver)
		dev_err(&pdev->dev,
			"%s: gadget driver still bound!!!\n", __func__);
	/* dma pool cleanup */
	dma_pool_destroy(dev->data_requests);

	अगर (dev->stp_requests) अणु
		/* cleanup DMA desc's क्रम ep0in */
		अगर (dev->ep[UDC_EP0OUT_IDX].td_stp) अणु
			dma_pool_मुक्त(dev->stp_requests,
				dev->ep[UDC_EP0OUT_IDX].td_stp,
				dev->ep[UDC_EP0OUT_IDX].td_stp_phys);
		पूर्ण
		अगर (dev->ep[UDC_EP0OUT_IDX].td_data) अणु
			dma_pool_मुक्त(dev->stp_requests,
				dev->ep[UDC_EP0OUT_IDX].td_data,
				dev->ep[UDC_EP0OUT_IDX].td_data_phys);
		पूर्ण
		dma_pool_destroy(dev->stp_requests);
	पूर्ण

	अगर (dev->dma_addr)
		dma_unmap_single(&dev->pdev->dev, dev->dma_addr,
				 UDC_EP0OUT_BUFF_SIZE * 4, DMA_FROM_DEVICE);

	pch_vbus_gpio_मुक्त(dev);

	pch_udc_निकास(dev);
पूर्ण

अटल पूर्णांक __maybe_unused pch_udc_suspend(काष्ठा device *d)
अणु
	काष्ठा pch_udc_dev *dev = dev_get_drvdata(d);

	pch_udc_disable_पूर्णांकerrupts(dev, UDC_DEVINT_MSK);
	pch_udc_disable_ep_पूर्णांकerrupts(dev, UDC_EPINT_MSK_DISABLE_ALL);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pch_udc_resume(काष्ठा device *d)
अणु
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pch_udc_pm, pch_udc_suspend, pch_udc_resume);

प्रकार पूर्णांक (*platक्रमm_init_fn)(काष्ठा device *);

अटल पूर्णांक pch_udc_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	platक्रमm_init_fn platक्रमm_init = (platक्रमm_init_fn)id->driver_data;
	पूर्णांक			retval;
	काष्ठा pch_udc_dev	*dev;

	/* init */
	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* pci setup */
	retval = pcim_enable_device(pdev);
	अगर (retval)
		वापस retval;

	dev->bar = PCH_UDC_PCI_BAR;
	dev->pdev = pdev;
	pci_set_drvdata(pdev, dev);

	/* Platक्रमm specअगरic hook */
	अगर (platक्रमm_init) अणु
		retval = platक्रमm_init(&pdev->dev);
		अगर (retval)
			वापस retval;
	पूर्ण

	/* PCI resource allocation */
	retval = pcim_iomap_regions(pdev, BIT(dev->bar), pci_name(pdev));
	अगर (retval)
		वापस retval;

	dev->base_addr = pcim_iomap_table(pdev)[dev->bar];

	/* initialize the hardware */
	retval = pch_udc_pcd_init(dev);
	अगर (retval)
		वापस retval;

	pci_enable_msi(pdev);

	retval = devm_request_irq(&pdev->dev, pdev->irq, pch_udc_isr,
				  IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (retval) अणु
		dev_err(&pdev->dev, "%s: request_irq(%d) fail\n", __func__,
			pdev->irq);
		जाओ finished;
	पूर्ण

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	/* device काष्ठा setup */
	spin_lock_init(&dev->lock);
	dev->gadget.ops = &pch_udc_ops;

	retval = init_dma_pools(dev);
	अगर (retval)
		जाओ finished;

	dev->gadget.name = KBUILD_MODNAME;
	dev->gadget.max_speed = USB_SPEED_HIGH;

	/* Put the device in disconnected state till a driver is bound */
	pch_udc_set_disconnect(dev);
	retval = usb_add_gadget_udc(&pdev->dev, &dev->gadget);
	अगर (retval)
		जाओ finished;
	वापस 0;

finished:
	pch_udc_हटाओ(pdev);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा pci_device_id pch_udc_pcidev_id[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_QUARK_X1000_UDC),
		.class = PCI_CLASS_SERIAL_USB_DEVICE,
		.class_mask = 0xffffffff,
		.driver_data = (kernel_uदीर्घ_t)&pch_udc_quark_platक्रमm_init,
	पूर्ण,
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_EG20T_UDC,
			       PCI_VENDOR_ID_CIRCUITCO, PCI_SUBSYSTEM_ID_CIRCUITCO_MINNOWBOARD),
		.class = PCI_CLASS_SERIAL_USB_DEVICE,
		.class_mask = 0xffffffff,
		.driver_data = (kernel_uदीर्घ_t)&pch_udc_minnow_platक्रमm_init,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_EG20T_UDC),
		.class = PCI_CLASS_SERIAL_USB_DEVICE,
		.class_mask = 0xffffffff,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_ROHM, PCI_DEVICE_ID_ML7213_IOH_UDC),
		.class = PCI_CLASS_SERIAL_USB_DEVICE,
		.class_mask = 0xffffffff,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_ROHM, PCI_DEVICE_ID_ML7831_IOH_UDC),
		.class = PCI_CLASS_SERIAL_USB_DEVICE,
		.class_mask = 0xffffffff,
	पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pch_udc_pcidev_id);

अटल काष्ठा pci_driver pch_udc_driver = अणु
	.name =	KBUILD_MODNAME,
	.id_table =	pch_udc_pcidev_id,
	.probe =	pch_udc_probe,
	.हटाओ =	pch_udc_हटाओ,
	.shutकरोwn =	pch_udc_shutकरोwn,
	.driver = अणु
		.pm = &pch_udc_pm,
	पूर्ण,
पूर्ण;

module_pci_driver(pch_udc_driver);

MODULE_DESCRIPTION("Intel EG20T USB Device Controller");
MODULE_AUTHOR("LAPIS Semiconductor, <tomoya-linux@dsn.lapis-semi.com>");
MODULE_LICENSE("GPL");

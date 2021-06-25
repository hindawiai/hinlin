<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Aपंचांगel Extensible DMA Controller (aka XDMAC on AT91 प्रणालीs)
 *
 * Copyright (C) 2014 Aपंचांगel Corporation
 *
 * Author: Luकरोvic Desroches <luकरोvic.desroches@aपंचांगel.com>
 */

#समावेश <यंत्र/barrier.h>
#समावेश <dt-bindings/dma/at91.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>

#समावेश "dmaengine.h"

/* Global रेजिस्टरs */
#घोषणा AT_XDMAC_GTYPE		0x00	/* Global Type Register */
#घोषणा		AT_XDMAC_NB_CH(i)	(((i) & 0x1F) + 1)		/* Number of Channels Minus One */
#घोषणा		AT_XDMAC_FIFO_SZ(i)	(((i) >> 5) & 0x7FF)		/* Number of Bytes */
#घोषणा		AT_XDMAC_NB_REQ(i)	((((i) >> 16) & 0x3F) + 1)	/* Number of Peripheral Requests Minus One */
#घोषणा AT_XDMAC_GCFG		0x04	/* Global Configuration Register */
#घोषणा		AT_XDMAC_WRHP(i)		(((i) & 0xF) << 4)
#घोषणा		AT_XDMAC_WRMP(i)		(((i) & 0xF) << 8)
#घोषणा		AT_XDMAC_WRLP(i)		(((i) & 0xF) << 12)
#घोषणा		AT_XDMAC_RDHP(i)		(((i) & 0xF) << 16)
#घोषणा		AT_XDMAC_RDMP(i)		(((i) & 0xF) << 20)
#घोषणा		AT_XDMAC_RDLP(i)		(((i) & 0xF) << 24)
#घोषणा		AT_XDMAC_RDSG(i)		(((i) & 0xF) << 28)
#घोषणा AT_XDMAC_GCFG_M2M	(AT_XDMAC_RDLP(0xF) | AT_XDMAC_WRLP(0xF))
#घोषणा AT_XDMAC_GCFG_P2M	(AT_XDMAC_RDSG(0x1) | AT_XDMAC_RDHP(0x3) | \
				AT_XDMAC_WRHP(0x5))
#घोषणा AT_XDMAC_GWAC		0x08	/* Global Weighted Arbiter Configuration Register */
#घोषणा		AT_XDMAC_PW0(i)		(((i) & 0xF) << 0)
#घोषणा		AT_XDMAC_PW1(i)		(((i) & 0xF) << 4)
#घोषणा		AT_XDMAC_PW2(i)		(((i) & 0xF) << 8)
#घोषणा		AT_XDMAC_PW3(i)		(((i) & 0xF) << 12)
#घोषणा AT_XDMAC_GWAC_M2M	0
#घोषणा AT_XDMAC_GWAC_P2M	(AT_XDMAC_PW0(0xF) | AT_XDMAC_PW2(0xF))

#घोषणा AT_XDMAC_GIE		0x0C	/* Global Interrupt Enable Register */
#घोषणा AT_XDMAC_GID		0x10	/* Global Interrupt Disable Register */
#घोषणा AT_XDMAC_GIM		0x14	/* Global Interrupt Mask Register */
#घोषणा AT_XDMAC_GIS		0x18	/* Global Interrupt Status Register */
#घोषणा AT_XDMAC_GE		0x1C	/* Global Channel Enable Register */
#घोषणा AT_XDMAC_GD		0x20	/* Global Channel Disable Register */
#घोषणा AT_XDMAC_GS		0x24	/* Global Channel Status Register */
#घोषणा AT_XDMAC_VERSION	0xFFC	/* XDMAC Version Register */

/* Channel relative रेजिस्टरs offsets */
#घोषणा AT_XDMAC_CIE		0x00	/* Channel Interrupt Enable Register */
#घोषणा		AT_XDMAC_CIE_BIE	BIT(0)	/* End of Block Interrupt Enable Bit */
#घोषणा		AT_XDMAC_CIE_LIE	BIT(1)	/* End of Linked List Interrupt Enable Bit */
#घोषणा		AT_XDMAC_CIE_DIE	BIT(2)	/* End of Disable Interrupt Enable Bit */
#घोषणा		AT_XDMAC_CIE_FIE	BIT(3)	/* End of Flush Interrupt Enable Bit */
#घोषणा		AT_XDMAC_CIE_RBEIE	BIT(4)	/* Read Bus Error Interrupt Enable Bit */
#घोषणा		AT_XDMAC_CIE_WBEIE	BIT(5)	/* Write Bus Error Interrupt Enable Bit */
#घोषणा		AT_XDMAC_CIE_ROIE	BIT(6)	/* Request Overflow Interrupt Enable Bit */
#घोषणा AT_XDMAC_CID		0x04	/* Channel Interrupt Disable Register */
#घोषणा		AT_XDMAC_CID_BID	BIT(0)	/* End of Block Interrupt Disable Bit */
#घोषणा		AT_XDMAC_CID_LID	BIT(1)	/* End of Linked List Interrupt Disable Bit */
#घोषणा		AT_XDMAC_CID_DID	BIT(2)	/* End of Disable Interrupt Disable Bit */
#घोषणा		AT_XDMAC_CID_FID	BIT(3)	/* End of Flush Interrupt Disable Bit */
#घोषणा		AT_XDMAC_CID_RBEID	BIT(4)	/* Read Bus Error Interrupt Disable Bit */
#घोषणा		AT_XDMAC_CID_WBEID	BIT(5)	/* Write Bus Error Interrupt Disable Bit */
#घोषणा		AT_XDMAC_CID_ROID	BIT(6)	/* Request Overflow Interrupt Disable Bit */
#घोषणा AT_XDMAC_CIM		0x08	/* Channel Interrupt Mask Register */
#घोषणा		AT_XDMAC_CIM_BIM	BIT(0)	/* End of Block Interrupt Mask Bit */
#घोषणा		AT_XDMAC_CIM_LIM	BIT(1)	/* End of Linked List Interrupt Mask Bit */
#घोषणा		AT_XDMAC_CIM_DIM	BIT(2)	/* End of Disable Interrupt Mask Bit */
#घोषणा		AT_XDMAC_CIM_FIM	BIT(3)	/* End of Flush Interrupt Mask Bit */
#घोषणा		AT_XDMAC_CIM_RBEIM	BIT(4)	/* Read Bus Error Interrupt Mask Bit */
#घोषणा		AT_XDMAC_CIM_WBEIM	BIT(5)	/* Write Bus Error Interrupt Mask Bit */
#घोषणा		AT_XDMAC_CIM_ROIM	BIT(6)	/* Request Overflow Interrupt Mask Bit */
#घोषणा AT_XDMAC_CIS		0x0C	/* Channel Interrupt Status Register */
#घोषणा		AT_XDMAC_CIS_BIS	BIT(0)	/* End of Block Interrupt Status Bit */
#घोषणा		AT_XDMAC_CIS_LIS	BIT(1)	/* End of Linked List Interrupt Status Bit */
#घोषणा		AT_XDMAC_CIS_DIS	BIT(2)	/* End of Disable Interrupt Status Bit */
#घोषणा		AT_XDMAC_CIS_FIS	BIT(3)	/* End of Flush Interrupt Status Bit */
#घोषणा		AT_XDMAC_CIS_RBEIS	BIT(4)	/* Read Bus Error Interrupt Status Bit */
#घोषणा		AT_XDMAC_CIS_WBEIS	BIT(5)	/* Write Bus Error Interrupt Status Bit */
#घोषणा		AT_XDMAC_CIS_ROIS	BIT(6)	/* Request Overflow Interrupt Status Bit */
#घोषणा AT_XDMAC_CSA		0x10	/* Channel Source Address Register */
#घोषणा AT_XDMAC_CDA		0x14	/* Channel Destination Address Register */
#घोषणा AT_XDMAC_CNDA		0x18	/* Channel Next Descriptor Address Register */
#घोषणा		AT_XDMAC_CNDA_NDAIF(i)	((i) & 0x1)			/* Channel x Next Descriptor Interface */
#घोषणा		AT_XDMAC_CNDA_NDA(i)	((i) & 0xfffffffc)		/* Channel x Next Descriptor Address */
#घोषणा AT_XDMAC_CNDC		0x1C	/* Channel Next Descriptor Control Register */
#घोषणा		AT_XDMAC_CNDC_NDE		(0x1 << 0)		/* Channel x Next Descriptor Enable */
#घोषणा		AT_XDMAC_CNDC_NDSUP		(0x1 << 1)		/* Channel x Next Descriptor Source Update */
#घोषणा		AT_XDMAC_CNDC_NDDUP		(0x1 << 2)		/* Channel x Next Descriptor Destination Update */
#घोषणा		AT_XDMAC_CNDC_NDVIEW_NDV0	(0x0 << 3)		/* Channel x Next Descriptor View 0 */
#घोषणा		AT_XDMAC_CNDC_NDVIEW_NDV1	(0x1 << 3)		/* Channel x Next Descriptor View 1 */
#घोषणा		AT_XDMAC_CNDC_NDVIEW_NDV2	(0x2 << 3)		/* Channel x Next Descriptor View 2 */
#घोषणा		AT_XDMAC_CNDC_NDVIEW_NDV3	(0x3 << 3)		/* Channel x Next Descriptor View 3 */
#घोषणा AT_XDMAC_CUBC		0x20	/* Channel Microblock Control Register */
#घोषणा AT_XDMAC_CBC		0x24	/* Channel Block Control Register */
#घोषणा AT_XDMAC_CC		0x28	/* Channel Configuration Register */
#घोषणा		AT_XDMAC_CC_TYPE	(0x1 << 0)	/* Channel Transfer Type */
#घोषणा			AT_XDMAC_CC_TYPE_MEM_TRAN	(0x0 << 0)	/* Memory to Memory Transfer */
#घोषणा			AT_XDMAC_CC_TYPE_PER_TRAN	(0x1 << 0)	/* Peripheral to Memory or Memory to Peripheral Transfer */
#घोषणा		AT_XDMAC_CC_MBSIZE_MASK	(0x3 << 1)
#घोषणा			AT_XDMAC_CC_MBSIZE_SINGLE	(0x0 << 1)
#घोषणा			AT_XDMAC_CC_MBSIZE_FOUR		(0x1 << 1)
#घोषणा			AT_XDMAC_CC_MBSIZE_EIGHT	(0x2 << 1)
#घोषणा			AT_XDMAC_CC_MBSIZE_SIXTEEN	(0x3 << 1)
#घोषणा		AT_XDMAC_CC_DSYNC	(0x1 << 4)	/* Channel Synchronization */
#घोषणा			AT_XDMAC_CC_DSYNC_PER2MEM	(0x0 << 4)
#घोषणा			AT_XDMAC_CC_DSYNC_MEM2PER	(0x1 << 4)
#घोषणा		AT_XDMAC_CC_PROT	(0x1 << 5)	/* Channel Protection */
#घोषणा			AT_XDMAC_CC_PROT_SEC		(0x0 << 5)
#घोषणा			AT_XDMAC_CC_PROT_UNSEC		(0x1 << 5)
#घोषणा		AT_XDMAC_CC_SWREQ	(0x1 << 6)	/* Channel Software Request Trigger */
#घोषणा			AT_XDMAC_CC_SWREQ_HWR_CONNECTED	(0x0 << 6)
#घोषणा			AT_XDMAC_CC_SWREQ_SWR_CONNECTED	(0x1 << 6)
#घोषणा		AT_XDMAC_CC_MEMSET	(0x1 << 7)	/* Channel Fill Block of memory */
#घोषणा			AT_XDMAC_CC_MEMSET_NORMAL_MODE	(0x0 << 7)
#घोषणा			AT_XDMAC_CC_MEMSET_HW_MODE	(0x1 << 7)
#घोषणा		AT_XDMAC_CC_CSIZE(i)	((0x7 & (i)) << 8)	/* Channel Chunk Size */
#घोषणा		AT_XDMAC_CC_DWIDTH_OFFSET	11
#घोषणा		AT_XDMAC_CC_DWIDTH_MASK	(0x3 << AT_XDMAC_CC_DWIDTH_OFFSET)
#घोषणा		AT_XDMAC_CC_DWIDTH(i)	((0x3 & (i)) << AT_XDMAC_CC_DWIDTH_OFFSET)	/* Channel Data Width */
#घोषणा			AT_XDMAC_CC_DWIDTH_BYTE		0x0
#घोषणा			AT_XDMAC_CC_DWIDTH_HALFWORD	0x1
#घोषणा			AT_XDMAC_CC_DWIDTH_WORD		0x2
#घोषणा			AT_XDMAC_CC_DWIDTH_DWORD	0x3
#घोषणा		AT_XDMAC_CC_SIF(i)	((0x1 & (i)) << 13)	/* Channel Source Interface Identअगरier */
#घोषणा		AT_XDMAC_CC_DIF(i)	((0x1 & (i)) << 14)	/* Channel Destination Interface Identअगरier */
#घोषणा		AT_XDMAC_CC_SAM_MASK	(0x3 << 16)	/* Channel Source Addressing Mode */
#घोषणा			AT_XDMAC_CC_SAM_FIXED_AM	(0x0 << 16)
#घोषणा			AT_XDMAC_CC_SAM_INCREMENTED_AM	(0x1 << 16)
#घोषणा			AT_XDMAC_CC_SAM_UBS_AM		(0x2 << 16)
#घोषणा			AT_XDMAC_CC_SAM_UBS_DS_AM	(0x3 << 16)
#घोषणा		AT_XDMAC_CC_DAM_MASK	(0x3 << 18)	/* Channel Source Addressing Mode */
#घोषणा			AT_XDMAC_CC_DAM_FIXED_AM	(0x0 << 18)
#घोषणा			AT_XDMAC_CC_DAM_INCREMENTED_AM	(0x1 << 18)
#घोषणा			AT_XDMAC_CC_DAM_UBS_AM		(0x2 << 18)
#घोषणा			AT_XDMAC_CC_DAM_UBS_DS_AM	(0x3 << 18)
#घोषणा		AT_XDMAC_CC_INITD	(0x1 << 21)	/* Channel Initialization Terminated (पढ़ो only) */
#घोषणा			AT_XDMAC_CC_INITD_TERMINATED	(0x0 << 21)
#घोषणा			AT_XDMAC_CC_INITD_IN_PROGRESS	(0x1 << 21)
#घोषणा		AT_XDMAC_CC_RDIP	(0x1 << 22)	/* Read in Progress (पढ़ो only) */
#घोषणा			AT_XDMAC_CC_RDIP_DONE		(0x0 << 22)
#घोषणा			AT_XDMAC_CC_RDIP_IN_PROGRESS	(0x1 << 22)
#घोषणा		AT_XDMAC_CC_WRIP	(0x1 << 23)	/* Write in Progress (पढ़ो only) */
#घोषणा			AT_XDMAC_CC_WRIP_DONE		(0x0 << 23)
#घोषणा			AT_XDMAC_CC_WRIP_IN_PROGRESS	(0x1 << 23)
#घोषणा		AT_XDMAC_CC_PERID(i)	(0x7f & (i) << 24)	/* Channel Peripheral Identअगरier */
#घोषणा AT_XDMAC_CDS_MSP	0x2C	/* Channel Data Stride Memory Set Pattern */
#घोषणा AT_XDMAC_CSUS		0x30	/* Channel Source Microblock Stride */
#घोषणा AT_XDMAC_CDUS		0x34	/* Channel Destination Microblock Stride */

/* Microblock control members */
#घोषणा AT_XDMAC_MBR_UBC_UBLEN_MAX	0xFFFFFFUL	/* Maximum Microblock Length */
#घोषणा AT_XDMAC_MBR_UBC_NDE		(0x1 << 24)	/* Next Descriptor Enable */
#घोषणा AT_XDMAC_MBR_UBC_NSEN		(0x1 << 25)	/* Next Descriptor Source Update */
#घोषणा AT_XDMAC_MBR_UBC_NDEN		(0x1 << 26)	/* Next Descriptor Destination Update */
#घोषणा AT_XDMAC_MBR_UBC_NDV0		(0x0 << 27)	/* Next Descriptor View 0 */
#घोषणा AT_XDMAC_MBR_UBC_NDV1		(0x1 << 27)	/* Next Descriptor View 1 */
#घोषणा AT_XDMAC_MBR_UBC_NDV2		(0x2 << 27)	/* Next Descriptor View 2 */
#घोषणा AT_XDMAC_MBR_UBC_NDV3		(0x3 << 27)	/* Next Descriptor View 3 */

#घोषणा AT_XDMAC_MAX_CHAN	0x20
#घोषणा AT_XDMAC_MAX_CSIZE	16	/* 16 data */
#घोषणा AT_XDMAC_MAX_DWIDTH	8	/* 64 bits */
#घोषणा AT_XDMAC_RESIDUE_MAX_RETRIES	5

#घोषणा AT_XDMAC_DMA_BUSWIDTHS\
	(BIT(DMA_SLAVE_BUSWIDTH_UNDEFINED) |\
	BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |\
	BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |\
	BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |\
	BIT(DMA_SLAVE_BUSWIDTH_8_BYTES))

क्रमागत atc_status अणु
	AT_XDMAC_CHAN_IS_CYCLIC = 0,
	AT_XDMAC_CHAN_IS_PAUSED,
पूर्ण;

काष्ठा at_xdmac_layout अणु
	/* Global Channel Read Suspend Register */
	u8				grs;
	/* Global Write Suspend Register */
	u8				gws;
	/* Global Channel Read Write Suspend Register */
	u8				grws;
	/* Global Channel Read Write Resume Register */
	u8				grwr;
	/* Global Channel Software Request Register */
	u8				gswr;
	/* Global channel Software Request Status Register */
	u8				gsws;
	/* Global Channel Software Flush Request Register */
	u8				gswf;
	/* Channel reg base */
	u8				chan_cc_reg_base;
	/* Source/Destination Interface must be specअगरied or not */
	bool				sdअगर;
	/* AXI queue priority configuration supported */
	bool				axi_config;
पूर्ण;

/* ----- Channels ----- */
काष्ठा at_xdmac_chan अणु
	काष्ठा dma_chan			chan;
	व्योम __iomem			*ch_regs;
	u32				mask;		/* Channel Mask */
	u32				cfg;		/* Channel Configuration Register */
	u8				perid;		/* Peripheral ID */
	u8				perअगर;		/* Peripheral Interface */
	u8				memअगर;		/* Memory Interface */
	u32				save_cc;
	u32				save_cim;
	u32				save_cnda;
	u32				save_cndc;
	u32				irq_status;
	अचिन्हित दीर्घ			status;
	काष्ठा tasklet_काष्ठा		tasklet;
	काष्ठा dma_slave_config		sconfig;

	spinlock_t			lock;

	काष्ठा list_head		xfers_list;
	काष्ठा list_head		मुक्त_descs_list;
पूर्ण;


/* ----- Controller ----- */
काष्ठा at_xdmac अणु
	काष्ठा dma_device	dma;
	व्योम __iomem		*regs;
	पूर्णांक			irq;
	काष्ठा clk		*clk;
	u32			save_gim;
	काष्ठा dma_pool		*at_xdmac_desc_pool;
	स्थिर काष्ठा at_xdmac_layout	*layout;
	काष्ठा at_xdmac_chan	chan[];
पूर्ण;


/* ----- Descriptors ----- */

/* Linked List Descriptor */
काष्ठा at_xdmac_lld अणु
	dma_addr_t	mbr_nda;	/* Next Descriptor Member */
	u32		mbr_ubc;	/* Microblock Control Member */
	dma_addr_t	mbr_sa;		/* Source Address Member */
	dma_addr_t	mbr_da;		/* Destination Address Member */
	u32		mbr_cfg;	/* Configuration Register */
	u32		mbr_bc;		/* Block Control Register */
	u32		mbr_ds;		/* Data Stride Register */
	u32		mbr_sus;	/* Source Microblock Stride Register */
	u32		mbr_dus;	/* Destination Microblock Stride Register */
पूर्ण;

/* 64-bit alignment needed to update CNDA and CUBC रेजिस्टरs in an atomic way. */
काष्ठा at_xdmac_desc अणु
	काष्ठा at_xdmac_lld		lld;
	क्रमागत dma_transfer_direction	direction;
	काष्ठा dma_async_tx_descriptor	tx_dma_desc;
	काष्ठा list_head		desc_node;
	/* Following members are only used by the first descriptor */
	bool				active_xfer;
	अचिन्हित पूर्णांक			xfer_size;
	काष्ठा list_head		descs_list;
	काष्ठा list_head		xfer_node;
पूर्ण __aligned(माप(u64));

अटल स्थिर काष्ठा at_xdmac_layout at_xdmac_sama5d4_layout = अणु
	.grs = 0x28,
	.gws = 0x2C,
	.grws = 0x30,
	.grwr = 0x34,
	.gswr = 0x38,
	.gsws = 0x3C,
	.gswf = 0x40,
	.chan_cc_reg_base = 0x50,
	.sdअगर = true,
	.axi_config = false,
पूर्ण;

अटल स्थिर काष्ठा at_xdmac_layout at_xdmac_sama7g5_layout = अणु
	.grs = 0x30,
	.gws = 0x38,
	.grws = 0x40,
	.grwr = 0x44,
	.gswr = 0x48,
	.gsws = 0x4C,
	.gswf = 0x50,
	.chan_cc_reg_base = 0x60,
	.sdअगर = false,
	.axi_config = true,
पूर्ण;

अटल अंतरभूत व्योम __iomem *at_xdmac_chan_reg_base(काष्ठा at_xdmac *atxdmac, अचिन्हित पूर्णांक chan_nb)
अणु
	वापस atxdmac->regs + (atxdmac->layout->chan_cc_reg_base + chan_nb * 0x40);
पूर्ण

#घोषणा at_xdmac_पढ़ो(atxdmac, reg) पढ़ोl_relaxed((atxdmac)->regs + (reg))
#घोषणा at_xdmac_ग_लिखो(atxdmac, reg, value) \
	ग_लिखोl_relaxed((value), (atxdmac)->regs + (reg))

#घोषणा at_xdmac_chan_पढ़ो(atchan, reg) पढ़ोl_relaxed((atchan)->ch_regs + (reg))
#घोषणा at_xdmac_chan_ग_लिखो(atchan, reg, value) ग_लिखोl_relaxed((value), (atchan)->ch_regs + (reg))

अटल अंतरभूत काष्ठा at_xdmac_chan *to_at_xdmac_chan(काष्ठा dma_chan *dchan)
अणु
	वापस container_of(dchan, काष्ठा at_xdmac_chan, chan);
पूर्ण

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

अटल अंतरभूत काष्ठा at_xdmac *to_at_xdmac(काष्ठा dma_device *ddev)
अणु
	वापस container_of(ddev, काष्ठा at_xdmac, dma);
पूर्ण

अटल अंतरभूत काष्ठा at_xdmac_desc *txd_to_at_desc(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस container_of(txd, काष्ठा at_xdmac_desc, tx_dma_desc);
पूर्ण

अटल अंतरभूत पूर्णांक at_xdmac_chan_is_cyclic(काष्ठा at_xdmac_chan *atchan)
अणु
	वापस test_bit(AT_XDMAC_CHAN_IS_CYCLIC, &atchan->status);
पूर्ण

अटल अंतरभूत पूर्णांक at_xdmac_chan_is_छोड़ोd(काष्ठा at_xdmac_chan *atchan)
अणु
	वापस test_bit(AT_XDMAC_CHAN_IS_PAUSED, &atchan->status);
पूर्ण

अटल अंतरभूत bool at_xdmac_chan_is_peripheral_xfer(u32 cfg)
अणु
	वापस cfg & AT_XDMAC_CC_TYPE_PER_TRAN;
पूर्ण

अटल अंतरभूत u8 at_xdmac_get_dwidth(u32 cfg)
अणु
	वापस (cfg & AT_XDMAC_CC_DWIDTH_MASK) >> AT_XDMAC_CC_DWIDTH_OFFSET;
पूर्ण;

अटल अचिन्हित पूर्णांक init_nr_desc_per_channel = 64;
module_param(init_nr_desc_per_channel, uपूर्णांक, 0644);
MODULE_PARM_DESC(init_nr_desc_per_channel,
		 "initial descriptors per channel (default: 64)");


अटल bool at_xdmac_chan_is_enabled(काष्ठा at_xdmac_chan *atchan)
अणु
	वापस at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_GS) & atchan->mask;
पूर्ण

अटल व्योम at_xdmac_off(काष्ठा at_xdmac *atxdmac)
अणु
	at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GD, -1L);

	/* Wait that all chans are disabled. */
	जबतक (at_xdmac_पढ़ो(atxdmac, AT_XDMAC_GS))
		cpu_relax();

	at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GID, -1L);
पूर्ण

/* Call with lock hold. */
अटल व्योम at_xdmac_start_xfer(काष्ठा at_xdmac_chan *atchan,
				काष्ठा at_xdmac_desc *first)
अणु
	काष्ठा at_xdmac	*atxdmac = to_at_xdmac(atchan->chan.device);
	u32		reg;

	dev_vdbg(chan2dev(&atchan->chan), "%s: desc 0x%p\n", __func__, first);

	अगर (at_xdmac_chan_is_enabled(atchan))
		वापस;

	/* Set transfer as active to not try to start it again. */
	first->active_xfer = true;

	/* Tell xdmac where to get the first descriptor. */
	reg = AT_XDMAC_CNDA_NDA(first->tx_dma_desc.phys);
	अगर (atxdmac->layout->sdअगर)
		reg |= AT_XDMAC_CNDA_NDAIF(atchan->memअगर);

	at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CNDA, reg);

	/*
	 * When करोing non cyclic transfer we need to use the next
	 * descriptor view 2 since some fields of the configuration रेजिस्टर
	 * depend on transfer size and src/dest addresses.
	 */
	अगर (at_xdmac_chan_is_cyclic(atchan))
		reg = AT_XDMAC_CNDC_NDVIEW_NDV1;
	अन्यथा अगर (first->lld.mbr_ubc & AT_XDMAC_MBR_UBC_NDV3)
		reg = AT_XDMAC_CNDC_NDVIEW_NDV3;
	अन्यथा
		reg = AT_XDMAC_CNDC_NDVIEW_NDV2;
	/*
	 * Even अगर the रेजिस्टर will be updated from the configuration in the
	 * descriptor when using view 2 or higher, the PROT bit won't be set
	 * properly. This bit can be modअगरied only by using the channel
	 * configuration रेजिस्टर.
	 */
	at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CC, first->lld.mbr_cfg);

	reg |= AT_XDMAC_CNDC_NDDUP
	       | AT_XDMAC_CNDC_NDSUP
	       | AT_XDMAC_CNDC_NDE;
	at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CNDC, reg);

	dev_vdbg(chan2dev(&atchan->chan),
		 "%s: CC=0x%08x CNDA=0x%08x, CNDC=0x%08x, CSA=0x%08x, CDA=0x%08x, CUBC=0x%08x\n",
		 __func__, at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CC),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDA),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDC),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CSA),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CDA),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CUBC));

	at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CID, 0xffffffff);
	reg = AT_XDMAC_CIE_RBEIE | AT_XDMAC_CIE_WBEIE;
	/*
	 * Request Overflow Error is only क्रम peripheral synchronized transfers
	 */
	अगर (at_xdmac_chan_is_peripheral_xfer(first->lld.mbr_cfg))
		reg |= AT_XDMAC_CIE_ROIE;

	/*
	 * There is no end of list when करोing cyclic dma, we need to get
	 * an पूर्णांकerrupt after each periods.
	 */
	अगर (at_xdmac_chan_is_cyclic(atchan))
		at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CIE,
				    reg | AT_XDMAC_CIE_BIE);
	अन्यथा
		at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CIE,
				    reg | AT_XDMAC_CIE_LIE);
	at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GIE, atchan->mask);
	dev_vdbg(chan2dev(&atchan->chan),
		 "%s: enable channel (0x%08x)\n", __func__, atchan->mask);
	wmb();
	at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GE, atchan->mask);

	dev_vdbg(chan2dev(&atchan->chan),
		 "%s: CC=0x%08x CNDA=0x%08x, CNDC=0x%08x, CSA=0x%08x, CDA=0x%08x, CUBC=0x%08x\n",
		 __func__, at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CC),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDA),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDC),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CSA),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CDA),
		 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CUBC));

पूर्ण

अटल dma_cookie_t at_xdmac_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा at_xdmac_desc	*desc = txd_to_at_desc(tx);
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(tx->chan);
	dma_cookie_t		cookie;
	अचिन्हित दीर्घ		irqflags;

	spin_lock_irqsave(&atchan->lock, irqflags);
	cookie = dma_cookie_assign(tx);

	dev_vdbg(chan2dev(tx->chan), "%s: atchan 0x%p, add desc 0x%p to xfers_list\n",
		 __func__, atchan, desc);
	list_add_tail(&desc->xfer_node, &atchan->xfers_list);
	अगर (list_is_singular(&atchan->xfers_list))
		at_xdmac_start_xfer(atchan, desc);

	spin_unlock_irqrestore(&atchan->lock, irqflags);
	वापस cookie;
पूर्ण

अटल काष्ठा at_xdmac_desc *at_xdmac_alloc_desc(काष्ठा dma_chan *chan,
						 gfp_t gfp_flags)
अणु
	काष्ठा at_xdmac_desc	*desc;
	काष्ठा at_xdmac		*atxdmac = to_at_xdmac(chan->device);
	dma_addr_t		phys;

	desc = dma_pool_zalloc(atxdmac->at_xdmac_desc_pool, gfp_flags, &phys);
	अगर (desc) अणु
		INIT_LIST_HEAD(&desc->descs_list);
		dma_async_tx_descriptor_init(&desc->tx_dma_desc, chan);
		desc->tx_dma_desc.tx_submit = at_xdmac_tx_submit;
		desc->tx_dma_desc.phys = phys;
	पूर्ण

	वापस desc;
पूर्ण

अटल व्योम at_xdmac_init_used_desc(काष्ठा at_xdmac_desc *desc)
अणु
	स_रखो(&desc->lld, 0, माप(desc->lld));
	INIT_LIST_HEAD(&desc->descs_list);
	desc->direction = DMA_TRANS_NONE;
	desc->xfer_size = 0;
	desc->active_xfer = false;
पूर्ण

/* Call must be रक्षित by lock. */
अटल काष्ठा at_xdmac_desc *at_xdmac_get_desc(काष्ठा at_xdmac_chan *atchan)
अणु
	काष्ठा at_xdmac_desc *desc;

	अगर (list_empty(&atchan->मुक्त_descs_list)) अणु
		desc = at_xdmac_alloc_desc(&atchan->chan, GFP_NOWAIT);
	पूर्ण अन्यथा अणु
		desc = list_first_entry(&atchan->मुक्त_descs_list,
					काष्ठा at_xdmac_desc, desc_node);
		list_del(&desc->desc_node);
		at_xdmac_init_used_desc(desc);
	पूर्ण

	वापस desc;
पूर्ण

अटल व्योम at_xdmac_queue_desc(काष्ठा dma_chan *chan,
				काष्ठा at_xdmac_desc *prev,
				काष्ठा at_xdmac_desc *desc)
अणु
	अगर (!prev || !desc)
		वापस;

	prev->lld.mbr_nda = desc->tx_dma_desc.phys;
	prev->lld.mbr_ubc |= AT_XDMAC_MBR_UBC_NDE;

	dev_dbg(chan2dev(chan),	"%s: chain lld: prev=0x%p, mbr_nda=%pad\n",
		__func__, prev, &prev->lld.mbr_nda);
पूर्ण

अटल अंतरभूत व्योम at_xdmac_increment_block_count(काष्ठा dma_chan *chan,
						  काष्ठा at_xdmac_desc *desc)
अणु
	अगर (!desc)
		वापस;

	desc->lld.mbr_bc++;

	dev_dbg(chan2dev(chan),
		"%s: incrementing the block count of the desc 0x%p\n",
		__func__, desc);
पूर्ण

अटल काष्ठा dma_chan *at_xdmac_xlate(काष्ठा of_phandle_args *dma_spec,
				       काष्ठा of_dma *of_dma)
अणु
	काष्ठा at_xdmac		*atxdmac = of_dma->of_dma_data;
	काष्ठा at_xdmac_chan	*atchan;
	काष्ठा dma_chan		*chan;
	काष्ठा device		*dev = atxdmac->dma.dev;

	अगर (dma_spec->args_count != 1) अणु
		dev_err(dev, "dma phandler args: bad number of args\n");
		वापस शून्य;
	पूर्ण

	chan = dma_get_any_slave_channel(&atxdmac->dma);
	अगर (!chan) अणु
		dev_err(dev, "can't get a dma channel\n");
		वापस शून्य;
	पूर्ण

	atchan = to_at_xdmac_chan(chan);
	atchan->memअगर = AT91_XDMAC_DT_GET_MEM_IF(dma_spec->args[0]);
	atchan->perअगर = AT91_XDMAC_DT_GET_PER_IF(dma_spec->args[0]);
	atchan->perid = AT91_XDMAC_DT_GET_PERID(dma_spec->args[0]);
	dev_dbg(dev, "chan dt cfg: memif=%u perif=%u perid=%u\n",
		 atchan->memअगर, atchan->perअगर, atchan->perid);

	वापस chan;
पूर्ण

अटल पूर्णांक at_xdmac_compute_chan_conf(काष्ठा dma_chan *chan,
				      क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac		*atxdmac = to_at_xdmac(atchan->chan.device);
	पूर्णांक			csize, dwidth;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		atchan->cfg =
			AT91_XDMAC_DT_PERID(atchan->perid)
			| AT_XDMAC_CC_DAM_INCREMENTED_AM
			| AT_XDMAC_CC_SAM_FIXED_AM
			| AT_XDMAC_CC_SWREQ_HWR_CONNECTED
			| AT_XDMAC_CC_DSYNC_PER2MEM
			| AT_XDMAC_CC_MBSIZE_SIXTEEN
			| AT_XDMAC_CC_TYPE_PER_TRAN;
		अगर (atxdmac->layout->sdअगर)
			atchan->cfg |= AT_XDMAC_CC_DIF(atchan->memअगर) |
				       AT_XDMAC_CC_SIF(atchan->perअगर);

		csize = ffs(atchan->sconfig.src_maxburst) - 1;
		अगर (csize < 0) अणु
			dev_err(chan2dev(chan), "invalid src maxburst value\n");
			वापस -EINVAL;
		पूर्ण
		atchan->cfg |= AT_XDMAC_CC_CSIZE(csize);
		dwidth = ffs(atchan->sconfig.src_addr_width) - 1;
		अगर (dwidth < 0) अणु
			dev_err(chan2dev(chan), "invalid src addr width value\n");
			वापस -EINVAL;
		पूर्ण
		atchan->cfg |= AT_XDMAC_CC_DWIDTH(dwidth);
	पूर्ण अन्यथा अगर (direction == DMA_MEM_TO_DEV) अणु
		atchan->cfg =
			AT91_XDMAC_DT_PERID(atchan->perid)
			| AT_XDMAC_CC_DAM_FIXED_AM
			| AT_XDMAC_CC_SAM_INCREMENTED_AM
			| AT_XDMAC_CC_SWREQ_HWR_CONNECTED
			| AT_XDMAC_CC_DSYNC_MEM2PER
			| AT_XDMAC_CC_MBSIZE_SIXTEEN
			| AT_XDMAC_CC_TYPE_PER_TRAN;
		अगर (atxdmac->layout->sdअगर)
			atchan->cfg |= AT_XDMAC_CC_DIF(atchan->perअगर) |
				       AT_XDMAC_CC_SIF(atchan->memअगर);

		csize = ffs(atchan->sconfig.dst_maxburst) - 1;
		अगर (csize < 0) अणु
			dev_err(chan2dev(chan), "invalid src maxburst value\n");
			वापस -EINVAL;
		पूर्ण
		atchan->cfg |= AT_XDMAC_CC_CSIZE(csize);
		dwidth = ffs(atchan->sconfig.dst_addr_width) - 1;
		अगर (dwidth < 0) अणु
			dev_err(chan2dev(chan), "invalid dst addr width value\n");
			वापस -EINVAL;
		पूर्ण
		atchan->cfg |= AT_XDMAC_CC_DWIDTH(dwidth);
	पूर्ण

	dev_dbg(chan2dev(chan),	"%s: cfg=0x%08x\n", __func__, atchan->cfg);

	वापस 0;
पूर्ण

/*
 * Only check that maxburst and addr width values are supported by the
 * the controller but not that the configuration is good to perक्रमm the
 * transfer since we करोn't know the direction at this stage.
 */
अटल पूर्णांक at_xdmac_check_slave_config(काष्ठा dma_slave_config *sconfig)
अणु
	अगर ((sconfig->src_maxburst > AT_XDMAC_MAX_CSIZE)
	    || (sconfig->dst_maxburst > AT_XDMAC_MAX_CSIZE))
		वापस -EINVAL;

	अगर ((sconfig->src_addr_width > AT_XDMAC_MAX_DWIDTH)
	    || (sconfig->dst_addr_width > AT_XDMAC_MAX_DWIDTH))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक at_xdmac_set_slave_config(काष्ठा dma_chan *chan,
				      काष्ठा dma_slave_config *sconfig)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);

	अगर (at_xdmac_check_slave_config(sconfig)) अणु
		dev_err(chan2dev(chan), "invalid slave configuration\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(&atchan->sconfig, sconfig, माप(atchan->sconfig));

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
at_xdmac_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		       अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		       अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा at_xdmac_chan		*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac_desc		*first = शून्य, *prev = शून्य;
	काष्ठा scatterlist		*sg;
	पूर्णांक				i;
	अचिन्हित पूर्णांक			xfer_size = 0;
	अचिन्हित दीर्घ			irqflags;
	काष्ठा dma_async_tx_descriptor	*ret = शून्य;

	अगर (!sgl)
		वापस शून्य;

	अगर (!is_slave_direction(direction)) अणु
		dev_err(chan2dev(chan), "invalid DMA direction\n");
		वापस शून्य;
	पूर्ण

	dev_dbg(chan2dev(chan), "%s: sg_len=%d, dir=%s, flags=0x%lx\n",
		 __func__, sg_len,
		 direction == DMA_MEM_TO_DEV ? "to device" : "from device",
		 flags);

	/* Protect dma_sconfig field that can be modअगरied by set_slave_conf. */
	spin_lock_irqsave(&atchan->lock, irqflags);

	अगर (at_xdmac_compute_chan_conf(chan, direction))
		जाओ spin_unlock;

	/* Prepare descriptors. */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		काष्ठा at_xdmac_desc	*desc = शून्य;
		u32			len, mem, dwidth, fixed_dwidth;

		len = sg_dma_len(sg);
		mem = sg_dma_address(sg);
		अगर (unlikely(!len)) अणु
			dev_err(chan2dev(chan), "sg data length is zero\n");
			जाओ spin_unlock;
		पूर्ण
		dev_dbg(chan2dev(chan), "%s: * sg%d len=%u, mem=0x%08x\n",
			 __func__, i, len, mem);

		desc = at_xdmac_get_desc(atchan);
		अगर (!desc) अणु
			dev_err(chan2dev(chan), "can't get descriptor\n");
			अगर (first)
				list_splice_init(&first->descs_list, &atchan->मुक्त_descs_list);
			जाओ spin_unlock;
		पूर्ण

		/* Linked list descriptor setup. */
		अगर (direction == DMA_DEV_TO_MEM) अणु
			desc->lld.mbr_sa = atchan->sconfig.src_addr;
			desc->lld.mbr_da = mem;
		पूर्ण अन्यथा अणु
			desc->lld.mbr_sa = mem;
			desc->lld.mbr_da = atchan->sconfig.dst_addr;
		पूर्ण
		dwidth = at_xdmac_get_dwidth(atchan->cfg);
		fixed_dwidth = IS_ALIGNED(len, 1 << dwidth)
			       ? dwidth
			       : AT_XDMAC_CC_DWIDTH_BYTE;
		desc->lld.mbr_ubc = AT_XDMAC_MBR_UBC_NDV2			/* next descriptor view */
			| AT_XDMAC_MBR_UBC_NDEN					/* next descriptor dst parameter update */
			| AT_XDMAC_MBR_UBC_NSEN					/* next descriptor src parameter update */
			| (len >> fixed_dwidth);				/* microblock length */
		desc->lld.mbr_cfg = (atchan->cfg & ~AT_XDMAC_CC_DWIDTH_MASK) |
				    AT_XDMAC_CC_DWIDTH(fixed_dwidth);
		dev_dbg(chan2dev(chan),
			 "%s: lld: mbr_sa=%pad, mbr_da=%pad, mbr_ubc=0x%08x\n",
			 __func__, &desc->lld.mbr_sa, &desc->lld.mbr_da, desc->lld.mbr_ubc);

		/* Chain lld. */
		अगर (prev)
			at_xdmac_queue_desc(chan, prev, desc);

		prev = desc;
		अगर (!first)
			first = desc;

		dev_dbg(chan2dev(chan), "%s: add desc 0x%p to descs_list 0x%p\n",
			 __func__, desc, first);
		list_add_tail(&desc->desc_node, &first->descs_list);
		xfer_size += len;
	पूर्ण


	first->tx_dma_desc.flags = flags;
	first->xfer_size = xfer_size;
	first->direction = direction;
	ret = &first->tx_dma_desc;

spin_unlock:
	spin_unlock_irqrestore(&atchan->lock, irqflags);
	वापस ret;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
at_xdmac_prep_dma_cyclic(काष्ठा dma_chan *chan, dma_addr_t buf_addr,
			 माप_प्रकार buf_len, माप_प्रकार period_len,
			 क्रमागत dma_transfer_direction direction,
			 अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac_desc	*first = शून्य, *prev = शून्य;
	अचिन्हित पूर्णांक		periods = buf_len / period_len;
	पूर्णांक			i;
	अचिन्हित दीर्घ		irqflags;

	dev_dbg(chan2dev(chan), "%s: buf_addr=%pad, buf_len=%zd, period_len=%zd, dir=%s, flags=0x%lx\n",
		__func__, &buf_addr, buf_len, period_len,
		direction == DMA_MEM_TO_DEV ? "mem2per" : "per2mem", flags);

	अगर (!is_slave_direction(direction)) अणु
		dev_err(chan2dev(chan), "invalid DMA direction\n");
		वापस शून्य;
	पूर्ण

	अगर (test_and_set_bit(AT_XDMAC_CHAN_IS_CYCLIC, &atchan->status)) अणु
		dev_err(chan2dev(chan), "channel currently used\n");
		वापस शून्य;
	पूर्ण

	अगर (at_xdmac_compute_chan_conf(chan, direction))
		वापस शून्य;

	क्रम (i = 0; i < periods; i++) अणु
		काष्ठा at_xdmac_desc	*desc = शून्य;

		spin_lock_irqsave(&atchan->lock, irqflags);
		desc = at_xdmac_get_desc(atchan);
		अगर (!desc) अणु
			dev_err(chan2dev(chan), "can't get descriptor\n");
			अगर (first)
				list_splice_init(&first->descs_list, &atchan->मुक्त_descs_list);
			spin_unlock_irqrestore(&atchan->lock, irqflags);
			वापस शून्य;
		पूर्ण
		spin_unlock_irqrestore(&atchan->lock, irqflags);
		dev_dbg(chan2dev(chan),
			"%s: desc=0x%p, tx_dma_desc.phys=%pad\n",
			__func__, desc, &desc->tx_dma_desc.phys);

		अगर (direction == DMA_DEV_TO_MEM) अणु
			desc->lld.mbr_sa = atchan->sconfig.src_addr;
			desc->lld.mbr_da = buf_addr + i * period_len;
		पूर्ण अन्यथा अणु
			desc->lld.mbr_sa = buf_addr + i * period_len;
			desc->lld.mbr_da = atchan->sconfig.dst_addr;
		पूर्ण
		desc->lld.mbr_cfg = atchan->cfg;
		desc->lld.mbr_ubc = AT_XDMAC_MBR_UBC_NDV1
			| AT_XDMAC_MBR_UBC_NDEN
			| AT_XDMAC_MBR_UBC_NSEN
			| period_len >> at_xdmac_get_dwidth(desc->lld.mbr_cfg);

		dev_dbg(chan2dev(chan),
			 "%s: lld: mbr_sa=%pad, mbr_da=%pad, mbr_ubc=0x%08x\n",
			 __func__, &desc->lld.mbr_sa, &desc->lld.mbr_da, desc->lld.mbr_ubc);

		/* Chain lld. */
		अगर (prev)
			at_xdmac_queue_desc(chan, prev, desc);

		prev = desc;
		अगर (!first)
			first = desc;

		dev_dbg(chan2dev(chan), "%s: add desc 0x%p to descs_list 0x%p\n",
			 __func__, desc, first);
		list_add_tail(&desc->desc_node, &first->descs_list);
	पूर्ण

	at_xdmac_queue_desc(chan, prev, first);
	first->tx_dma_desc.flags = flags;
	first->xfer_size = buf_len;
	first->direction = direction;

	वापस &first->tx_dma_desc;
पूर्ण

अटल अंतरभूत u32 at_xdmac_align_width(काष्ठा dma_chan *chan, dma_addr_t addr)
अणु
	u32 width;

	/*
	 * Check address alignment to select the greater data width we
	 * can use.
	 *
	 * Some XDMAC implementations करोn't provide dword transfer, in
	 * this हाल selecting dword has the same behavior as
	 * selecting word transfers.
	 */
	अगर (!(addr & 7)) अणु
		width = AT_XDMAC_CC_DWIDTH_DWORD;
		dev_dbg(chan2dev(chan), "%s: dwidth: double word\n", __func__);
	पूर्ण अन्यथा अगर (!(addr & 3)) अणु
		width = AT_XDMAC_CC_DWIDTH_WORD;
		dev_dbg(chan2dev(chan), "%s: dwidth: word\n", __func__);
	पूर्ण अन्यथा अगर (!(addr & 1)) अणु
		width = AT_XDMAC_CC_DWIDTH_HALFWORD;
		dev_dbg(chan2dev(chan), "%s: dwidth: half word\n", __func__);
	पूर्ण अन्यथा अणु
		width = AT_XDMAC_CC_DWIDTH_BYTE;
		dev_dbg(chan2dev(chan), "%s: dwidth: byte\n", __func__);
	पूर्ण

	वापस width;
पूर्ण

अटल काष्ठा at_xdmac_desc *
at_xdmac_पूर्णांकerleaved_queue_desc(काष्ठा dma_chan *chan,
				काष्ठा at_xdmac_chan *atchan,
				काष्ठा at_xdmac_desc *prev,
				dma_addr_t src, dma_addr_t dst,
				काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
				काष्ठा data_chunk *chunk)
अणु
	काष्ठा at_xdmac_desc	*desc;
	u32			dwidth;
	अचिन्हित दीर्घ		flags;
	माप_प्रकार			ublen;
	/*
	 * WARNING: The channel configuration is set here since there is no
	 * dmaengine_slave_config call in this हाल. Moreover we करोn't know the
	 * direction, it involves we can't dynamically set the source and dest
	 * पूर्णांकerface so we have to use the same one. Only पूर्णांकerface 0 allows EBI
	 * access. Hopefully we can access DDR through both ports (at least on
	 * SAMA5D4x), so we can use the same पूर्णांकerface क्रम source and dest,
	 * that solves the fact we करोn't know the direction.
	 * ERRATA: Even अगर useless क्रम memory transfers, the PERID has to not
	 * match the one of another channel. If not, it could lead to spurious
	 * flag status.
	 * For SAMA7G5x हाल, the SIF and DIF fields are no दीर्घer used.
	 * Thus, no need to have the SIF/DIF पूर्णांकerfaces here.
	 * For SAMA5D4x and SAMA5D2x the SIF and DIF are alपढ़ोy configured as
	 * zero.
	 */
	u32			chan_cc = AT_XDMAC_CC_PERID(0x7f)
					| AT_XDMAC_CC_MBSIZE_SIXTEEN
					| AT_XDMAC_CC_TYPE_MEM_TRAN;

	dwidth = at_xdmac_align_width(chan, src | dst | chunk->size);
	अगर (chunk->size >= (AT_XDMAC_MBR_UBC_UBLEN_MAX << dwidth)) अणु
		dev_dbg(chan2dev(chan),
			"%s: chunk too big (%zu, max size %lu)...\n",
			__func__, chunk->size,
			AT_XDMAC_MBR_UBC_UBLEN_MAX << dwidth);
		वापस शून्य;
	पूर्ण

	अगर (prev)
		dev_dbg(chan2dev(chan),
			"Adding items at the end of desc 0x%p\n", prev);

	अगर (xt->src_inc) अणु
		अगर (xt->src_sgl)
			chan_cc |=  AT_XDMAC_CC_SAM_UBS_AM;
		अन्यथा
			chan_cc |=  AT_XDMAC_CC_SAM_INCREMENTED_AM;
	पूर्ण

	अगर (xt->dst_inc) अणु
		अगर (xt->dst_sgl)
			chan_cc |=  AT_XDMAC_CC_DAM_UBS_AM;
		अन्यथा
			chan_cc |=  AT_XDMAC_CC_DAM_INCREMENTED_AM;
	पूर्ण

	spin_lock_irqsave(&atchan->lock, flags);
	desc = at_xdmac_get_desc(atchan);
	spin_unlock_irqrestore(&atchan->lock, flags);
	अगर (!desc) अणु
		dev_err(chan2dev(chan), "can't get descriptor\n");
		वापस शून्य;
	पूर्ण

	chan_cc |= AT_XDMAC_CC_DWIDTH(dwidth);

	ublen = chunk->size >> dwidth;

	desc->lld.mbr_sa = src;
	desc->lld.mbr_da = dst;
	desc->lld.mbr_sus = dmaengine_get_src_icg(xt, chunk);
	desc->lld.mbr_dus = dmaengine_get_dst_icg(xt, chunk);

	desc->lld.mbr_ubc = AT_XDMAC_MBR_UBC_NDV3
		| AT_XDMAC_MBR_UBC_NDEN
		| AT_XDMAC_MBR_UBC_NSEN
		| ublen;
	desc->lld.mbr_cfg = chan_cc;

	dev_dbg(chan2dev(chan),
		"%s: lld: mbr_sa=%pad, mbr_da=%pad, mbr_ubc=0x%08x, mbr_cfg=0x%08x\n",
		__func__, &desc->lld.mbr_sa, &desc->lld.mbr_da,
		desc->lld.mbr_ubc, desc->lld.mbr_cfg);

	/* Chain lld. */
	अगर (prev)
		at_xdmac_queue_desc(chan, prev, desc);

	वापस desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
at_xdmac_prep_पूर्णांकerleaved(काष्ठा dma_chan *chan,
			  काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
			  अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac_desc	*prev = शून्य, *first = शून्य;
	dma_addr_t		dst_addr, src_addr;
	माप_प्रकार			src_skip = 0, dst_skip = 0, len = 0;
	काष्ठा data_chunk	*chunk;
	पूर्णांक			i;

	अगर (!xt || !xt->numf || (xt->dir != DMA_MEM_TO_MEM))
		वापस शून्य;

	/*
	 * TODO: Handle the हाल where we have to repeat a chain of
	 * descriptors...
	 */
	अगर ((xt->numf > 1) && (xt->frame_size > 1))
		वापस शून्य;

	dev_dbg(chan2dev(chan), "%s: src=%pad, dest=%pad, numf=%zu, frame_size=%zu, flags=0x%lx\n",
		__func__, &xt->src_start, &xt->dst_start,	xt->numf,
		xt->frame_size, flags);

	src_addr = xt->src_start;
	dst_addr = xt->dst_start;

	अगर (xt->numf > 1) अणु
		first = at_xdmac_पूर्णांकerleaved_queue_desc(chan, atchan,
							शून्य,
							src_addr, dst_addr,
							xt, xt->sgl);

		/* Length of the block is (BLEN+1) microblocks. */
		क्रम (i = 0; i < xt->numf - 1; i++)
			at_xdmac_increment_block_count(chan, first);

		dev_dbg(chan2dev(chan), "%s: add desc 0x%p to descs_list 0x%p\n",
			__func__, first, first);
		list_add_tail(&first->desc_node, &first->descs_list);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < xt->frame_size; i++) अणु
			माप_प्रकार src_icg = 0, dst_icg = 0;
			काष्ठा at_xdmac_desc *desc;

			chunk = xt->sgl + i;

			dst_icg = dmaengine_get_dst_icg(xt, chunk);
			src_icg = dmaengine_get_src_icg(xt, chunk);

			src_skip = chunk->size + src_icg;
			dst_skip = chunk->size + dst_icg;

			dev_dbg(chan2dev(chan),
				"%s: chunk size=%zu, src icg=%zu, dst icg=%zu\n",
				__func__, chunk->size, src_icg, dst_icg);

			desc = at_xdmac_पूर्णांकerleaved_queue_desc(chan, atchan,
							       prev,
							       src_addr, dst_addr,
							       xt, chunk);
			अगर (!desc) अणु
				list_splice_init(&first->descs_list,
						 &atchan->मुक्त_descs_list);
				वापस शून्य;
			पूर्ण

			अगर (!first)
				first = desc;

			dev_dbg(chan2dev(chan), "%s: add desc 0x%p to descs_list 0x%p\n",
				__func__, desc, first);
			list_add_tail(&desc->desc_node, &first->descs_list);

			अगर (xt->src_sgl)
				src_addr += src_skip;

			अगर (xt->dst_sgl)
				dst_addr += dst_skip;

			len += chunk->size;
			prev = desc;
		पूर्ण
	पूर्ण

	first->tx_dma_desc.cookie = -EBUSY;
	first->tx_dma_desc.flags = flags;
	first->xfer_size = len;

	वापस &first->tx_dma_desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
at_xdmac_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
			 माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac_desc	*first = शून्य, *prev = शून्य;
	माप_प्रकार			reमुख्यing_size = len, xfer_size = 0, ublen;
	dma_addr_t		src_addr = src, dst_addr = dest;
	u32			dwidth;
	/*
	 * WARNING: We करोn't know the direction, it involves we can't
	 * dynamically set the source and dest पूर्णांकerface so we have to use the
	 * same one. Only पूर्णांकerface 0 allows EBI access. Hopefully we can
	 * access DDR through both ports (at least on SAMA5D4x), so we can use
	 * the same पूर्णांकerface क्रम source and dest, that solves the fact we
	 * करोn't know the direction.
	 * ERRATA: Even अगर useless क्रम memory transfers, the PERID has to not
	 * match the one of another channel. If not, it could lead to spurious
	 * flag status.
	 * For SAMA7G5x हाल, the SIF and DIF fields are no दीर्घer used.
	 * Thus, no need to have the SIF/DIF पूर्णांकerfaces here.
	 * For SAMA5D4x and SAMA5D2x the SIF and DIF are alपढ़ोy configured as
	 * zero.
	 */
	u32			chan_cc = AT_XDMAC_CC_PERID(0x7f)
					| AT_XDMAC_CC_DAM_INCREMENTED_AM
					| AT_XDMAC_CC_SAM_INCREMENTED_AM
					| AT_XDMAC_CC_MBSIZE_SIXTEEN
					| AT_XDMAC_CC_TYPE_MEM_TRAN;
	अचिन्हित दीर्घ		irqflags;

	dev_dbg(chan2dev(chan), "%s: src=%pad, dest=%pad, len=%zd, flags=0x%lx\n",
		__func__, &src, &dest, len, flags);

	अगर (unlikely(!len))
		वापस शून्य;

	dwidth = at_xdmac_align_width(chan, src_addr | dst_addr);

	/* Prepare descriptors. */
	जबतक (reमुख्यing_size) अणु
		काष्ठा at_xdmac_desc	*desc = शून्य;

		dev_dbg(chan2dev(chan), "%s: remaining_size=%zu\n", __func__, reमुख्यing_size);

		spin_lock_irqsave(&atchan->lock, irqflags);
		desc = at_xdmac_get_desc(atchan);
		spin_unlock_irqrestore(&atchan->lock, irqflags);
		अगर (!desc) अणु
			dev_err(chan2dev(chan), "can't get descriptor\n");
			अगर (first)
				list_splice_init(&first->descs_list, &atchan->मुक्त_descs_list);
			वापस शून्य;
		पूर्ण

		/* Update src and dest addresses. */
		src_addr += xfer_size;
		dst_addr += xfer_size;

		अगर (reमुख्यing_size >= AT_XDMAC_MBR_UBC_UBLEN_MAX << dwidth)
			xfer_size = AT_XDMAC_MBR_UBC_UBLEN_MAX << dwidth;
		अन्यथा
			xfer_size = reमुख्यing_size;

		dev_dbg(chan2dev(chan), "%s: xfer_size=%zu\n", __func__, xfer_size);

		/* Check reमुख्यing length and change data width अगर needed. */
		dwidth = at_xdmac_align_width(chan,
					      src_addr | dst_addr | xfer_size);
		chan_cc &= ~AT_XDMAC_CC_DWIDTH_MASK;
		chan_cc |= AT_XDMAC_CC_DWIDTH(dwidth);

		ublen = xfer_size >> dwidth;
		reमुख्यing_size -= xfer_size;

		desc->lld.mbr_sa = src_addr;
		desc->lld.mbr_da = dst_addr;
		desc->lld.mbr_ubc = AT_XDMAC_MBR_UBC_NDV2
			| AT_XDMAC_MBR_UBC_NDEN
			| AT_XDMAC_MBR_UBC_NSEN
			| ublen;
		desc->lld.mbr_cfg = chan_cc;

		dev_dbg(chan2dev(chan),
			 "%s: lld: mbr_sa=%pad, mbr_da=%pad, mbr_ubc=0x%08x, mbr_cfg=0x%08x\n",
			 __func__, &desc->lld.mbr_sa, &desc->lld.mbr_da, desc->lld.mbr_ubc, desc->lld.mbr_cfg);

		/* Chain lld. */
		अगर (prev)
			at_xdmac_queue_desc(chan, prev, desc);

		prev = desc;
		अगर (!first)
			first = desc;

		dev_dbg(chan2dev(chan), "%s: add desc 0x%p to descs_list 0x%p\n",
			 __func__, desc, first);
		list_add_tail(&desc->desc_node, &first->descs_list);
	पूर्ण

	first->tx_dma_desc.flags = flags;
	first->xfer_size = len;

	वापस &first->tx_dma_desc;
पूर्ण

अटल काष्ठा at_xdmac_desc *at_xdmac_स_रखो_create_desc(काष्ठा dma_chan *chan,
							 काष्ठा at_xdmac_chan *atchan,
							 dma_addr_t dst_addr,
							 माप_प्रकार len,
							 पूर्णांक value)
अणु
	काष्ठा at_xdmac_desc	*desc;
	अचिन्हित दीर्घ		flags;
	माप_प्रकार			ublen;
	u32			dwidth;
	/*
	 * WARNING: The channel configuration is set here since there is no
	 * dmaengine_slave_config call in this हाल. Moreover we करोn't know the
	 * direction, it involves we can't dynamically set the source and dest
	 * पूर्णांकerface so we have to use the same one. Only पूर्णांकerface 0 allows EBI
	 * access. Hopefully we can access DDR through both ports (at least on
	 * SAMA5D4x), so we can use the same पूर्णांकerface क्रम source and dest,
	 * that solves the fact we करोn't know the direction.
	 * ERRATA: Even अगर useless क्रम memory transfers, the PERID has to not
	 * match the one of another channel. If not, it could lead to spurious
	 * flag status.
	 * For SAMA7G5x हाल, the SIF and DIF fields are no दीर्घer used.
	 * Thus, no need to have the SIF/DIF पूर्णांकerfaces here.
	 * For SAMA5D4x and SAMA5D2x the SIF and DIF are alपढ़ोy configured as
	 * zero.
	 */
	u32			chan_cc = AT_XDMAC_CC_PERID(0x7f)
					| AT_XDMAC_CC_DAM_UBS_AM
					| AT_XDMAC_CC_SAM_INCREMENTED_AM
					| AT_XDMAC_CC_MBSIZE_SIXTEEN
					| AT_XDMAC_CC_MEMSET_HW_MODE
					| AT_XDMAC_CC_TYPE_MEM_TRAN;

	dwidth = at_xdmac_align_width(chan, dst_addr);

	अगर (len >= (AT_XDMAC_MBR_UBC_UBLEN_MAX << dwidth)) अणु
		dev_err(chan2dev(chan),
			"%s: Transfer too large, aborting...\n",
			__func__);
		वापस शून्य;
	पूर्ण

	spin_lock_irqsave(&atchan->lock, flags);
	desc = at_xdmac_get_desc(atchan);
	spin_unlock_irqrestore(&atchan->lock, flags);
	अगर (!desc) अणु
		dev_err(chan2dev(chan), "can't get descriptor\n");
		वापस शून्य;
	पूर्ण

	chan_cc |= AT_XDMAC_CC_DWIDTH(dwidth);

	ublen = len >> dwidth;

	desc->lld.mbr_da = dst_addr;
	desc->lld.mbr_ds = value;
	desc->lld.mbr_ubc = AT_XDMAC_MBR_UBC_NDV3
		| AT_XDMAC_MBR_UBC_NDEN
		| AT_XDMAC_MBR_UBC_NSEN
		| ublen;
	desc->lld.mbr_cfg = chan_cc;

	dev_dbg(chan2dev(chan),
		"%s: lld: mbr_da=%pad, mbr_ds=0x%08x, mbr_ubc=0x%08x, mbr_cfg=0x%08x\n",
		__func__, &desc->lld.mbr_da, desc->lld.mbr_ds, desc->lld.mbr_ubc,
		desc->lld.mbr_cfg);

	वापस desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
at_xdmac_prep_dma_स_रखो(काष्ठा dma_chan *chan, dma_addr_t dest, पूर्णांक value,
			 माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac_desc	*desc;

	dev_dbg(chan2dev(chan), "%s: dest=%pad, len=%zu, pattern=0x%x, flags=0x%lx\n",
		__func__, &dest, len, value, flags);

	अगर (unlikely(!len))
		वापस शून्य;

	desc = at_xdmac_स_रखो_create_desc(chan, atchan, dest, len, value);
	list_add_tail(&desc->desc_node, &desc->descs_list);

	desc->tx_dma_desc.cookie = -EBUSY;
	desc->tx_dma_desc.flags = flags;
	desc->xfer_size = len;

	वापस &desc->tx_dma_desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
at_xdmac_prep_dma_स_रखो_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
			    अचिन्हित पूर्णांक sg_len, पूर्णांक value,
			    अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac_desc	*desc, *pdesc = शून्य,
				*ppdesc = शून्य, *first = शून्य;
	काष्ठा scatterlist	*sg, *psg = शून्य, *ppsg = शून्य;
	माप_प्रकार			stride = 0, pstride = 0, len = 0;
	पूर्णांक			i;

	अगर (!sgl)
		वापस शून्य;

	dev_dbg(chan2dev(chan), "%s: sg_len=%d, value=0x%x, flags=0x%lx\n",
		__func__, sg_len, value, flags);

	/* Prepare descriptors. */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		dev_dbg(chan2dev(chan), "%s: dest=%pad, len=%d, pattern=0x%x, flags=0x%lx\n",
			__func__, &sg_dma_address(sg), sg_dma_len(sg),
			value, flags);
		desc = at_xdmac_स_रखो_create_desc(chan, atchan,
						   sg_dma_address(sg),
						   sg_dma_len(sg),
						   value);
		अगर (!desc && first)
			list_splice_init(&first->descs_list,
					 &atchan->मुक्त_descs_list);

		अगर (!first)
			first = desc;

		/* Update our strides */
		pstride = stride;
		अगर (psg)
			stride = sg_dma_address(sg) -
				(sg_dma_address(psg) + sg_dma_len(psg));

		/*
		 * The scatterlist API gives us only the address and
		 * length of each elements.
		 *
		 * Unक्रमtunately, we करोn't have the stride, which we
		 * will need to compute.
		 *
		 * That make us end up in a situation like this one:
		 *    len    stride    len    stride    len
		 * +-------+        +-------+        +-------+
		 * |  N-2  |        |  N-1  |        |   N   |
		 * +-------+        +-------+        +-------+
		 *
		 * We need all these three elements (N-2, N-1 and N)
		 * to actually take the decision on whether we need to
		 * queue N-1 or reuse N-2.
		 *
		 * We will only consider N अगर it is the last element.
		 */
		अगर (ppdesc && pdesc) अणु
			अगर ((stride == pstride) &&
			    (sg_dma_len(ppsg) == sg_dma_len(psg))) अणु
				dev_dbg(chan2dev(chan),
					"%s: desc 0x%p can be merged with desc 0x%p\n",
					__func__, pdesc, ppdesc);

				/*
				 * Increment the block count of the
				 * N-2 descriptor
				 */
				at_xdmac_increment_block_count(chan, ppdesc);
				ppdesc->lld.mbr_dus = stride;

				/*
				 * Put back the N-1 descriptor in the
				 * मुक्त descriptor list
				 */
				list_add_tail(&pdesc->desc_node,
					      &atchan->मुक्त_descs_list);

				/*
				 * Make our N-1 descriptor poपूर्णांकer
				 * poपूर्णांक to the N-2 since they were
				 * actually merged.
				 */
				pdesc = ppdesc;

			/*
			 * Rule out the हाल where we करोn't have
			 * pstride computed yet (our second sg
			 * element)
			 *
			 * We also want to catch the हाल where there
			 * would be a negative stride,
			 */
			पूर्ण अन्यथा अगर (pstride ||
				   sg_dma_address(sg) < sg_dma_address(psg)) अणु
				/*
				 * Queue the N-1 descriptor after the
				 * N-2
				 */
				at_xdmac_queue_desc(chan, ppdesc, pdesc);

				/*
				 * Add the N-1 descriptor to the list
				 * of the descriptors used क्रम this
				 * transfer
				 */
				list_add_tail(&desc->desc_node,
					      &first->descs_list);
				dev_dbg(chan2dev(chan),
					"%s: add desc 0x%p to descs_list 0x%p\n",
					__func__, desc, first);
			पूर्ण
		पूर्ण

		/*
		 * If we are the last element, just see अगर we have the
		 * same size than the previous element.
		 *
		 * If so, we can merge it with the previous descriptor
		 * since we करोn't care about the stride anymore.
		 */
		अगर ((i == (sg_len - 1)) &&
		    sg_dma_len(psg) == sg_dma_len(sg)) अणु
			dev_dbg(chan2dev(chan),
				"%s: desc 0x%p can be merged with desc 0x%p\n",
				__func__, desc, pdesc);

			/*
			 * Increment the block count of the N-1
			 * descriptor
			 */
			at_xdmac_increment_block_count(chan, pdesc);
			pdesc->lld.mbr_dus = stride;

			/*
			 * Put back the N descriptor in the मुक्त
			 * descriptor list
			 */
			list_add_tail(&desc->desc_node,
				      &atchan->मुक्त_descs_list);
		पूर्ण

		/* Update our descriptors */
		ppdesc = pdesc;
		pdesc = desc;

		/* Update our scatter poपूर्णांकers */
		ppsg = psg;
		psg = sg;

		len += sg_dma_len(sg);
	पूर्ण

	first->tx_dma_desc.cookie = -EBUSY;
	first->tx_dma_desc.flags = flags;
	first->xfer_size = len;

	वापस &first->tx_dma_desc;
पूर्ण

अटल क्रमागत dma_status
at_xdmac_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
		काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac		*atxdmac = to_at_xdmac(atchan->chan.device);
	काष्ठा at_xdmac_desc	*desc, *_desc;
	काष्ठा list_head	*descs_list;
	क्रमागत dma_status		ret;
	पूर्णांक			residue, retry;
	u32			cur_nda, check_nda, cur_ubc, mask, value;
	u8			dwidth = 0;
	अचिन्हित दीर्घ		flags;
	bool			initd;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	अगर (!txstate)
		वापस ret;

	spin_lock_irqsave(&atchan->lock, flags);

	desc = list_first_entry(&atchan->xfers_list, काष्ठा at_xdmac_desc, xfer_node);

	/*
	 * If the transfer has not been started yet, करोn't need to compute the
	 * residue, it's the transfer length.
	 */
	अगर (!desc->active_xfer) अणु
		dma_set_residue(txstate, desc->xfer_size);
		जाओ spin_unlock;
	पूर्ण

	residue = desc->xfer_size;
	/*
	 * Flush FIFO: only relevant when the transfer is source peripheral
	 * synchronized. Flush is needed beक्रमe पढ़ोing CUBC because data in
	 * the FIFO are not reported by CUBC. Reporting a residue of the
	 * transfer length जबतक we have data in FIFO can cause issue.
	 * Useहाल: aपंचांगel USART has a समयout which means I have received
	 * अक्षरacters but there is no more अक्षरacter received क्रम a जबतक. On
	 * समयout, it requests the residue. If the data are in the DMA FIFO,
	 * we will वापस a residue of the transfer length. It means no data
	 * received. If an application is रुकोing क्रम these data, it will hang
	 * since we won't have another USART समयout without receiving new
	 * data.
	 */
	mask = AT_XDMAC_CC_TYPE | AT_XDMAC_CC_DSYNC;
	value = AT_XDMAC_CC_TYPE_PER_TRAN | AT_XDMAC_CC_DSYNC_PER2MEM;
	अगर ((desc->lld.mbr_cfg & mask) == value) अणु
		at_xdmac_ग_लिखो(atxdmac, atxdmac->layout->gswf, atchan->mask);
		जबतक (!(at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CIS) & AT_XDMAC_CIS_FIS))
			cpu_relax();
	पूर्ण

	/*
	 * The easiest way to compute the residue should be to छोड़ो the DMA
	 * but करोing this can lead to miss some data as some devices करोn't
	 * have FIFO.
	 * We need to पढ़ो several रेजिस्टरs because:
	 * - DMA is running thereक्रमe a descriptor change is possible जबतक
	 * पढ़ोing these रेजिस्टरs
	 * - When the block transfer is करोne, the value of the CUBC रेजिस्टर
	 * is set to its initial value until the fetch of the next descriptor.
	 * This value will corrupt the residue calculation so we have to skip
	 * it.
	 *
	 * INITD --------                    ------------
	 *              |____________________|
	 *       _______________________  _______________
	 * NDA       @desc2             \/   @desc3
	 *       _______________________/\_______________
	 *       __________  ___________  _______________
	 * CUBC       0    \/ MAX desc1 \/  MAX desc2
	 *       __________/\___________/\_______________
	 *
	 * Since descriptors are aligned on 64 bits, we can assume that
	 * the update of NDA and CUBC is atomic.
	 * Memory barriers are used to ensure the पढ़ो order of the रेजिस्टरs.
	 * A max number of retries is set because unlikely it could never ends.
	 */
	क्रम (retry = 0; retry < AT_XDMAC_RESIDUE_MAX_RETRIES; retry++) अणु
		check_nda = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDA) & 0xfffffffc;
		rmb();
		cur_ubc = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CUBC);
		rmb();
		initd = !!(at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CC) & AT_XDMAC_CC_INITD);
		rmb();
		cur_nda = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDA) & 0xfffffffc;
		rmb();

		अगर ((check_nda == cur_nda) && initd)
			अवरोध;
	पूर्ण

	अगर (unlikely(retry >= AT_XDMAC_RESIDUE_MAX_RETRIES)) अणु
		ret = DMA_ERROR;
		जाओ spin_unlock;
	पूर्ण

	/*
	 * Flush FIFO: only relevant when the transfer is source peripheral
	 * synchronized. Another flush is needed here because CUBC is updated
	 * when the controller sends the data ग_लिखो command. It can lead to
	 * report data that are not written in the memory or the device. The
	 * FIFO flush ensures that data are really written.
	 */
	अगर ((desc->lld.mbr_cfg & mask) == value) अणु
		at_xdmac_ग_लिखो(atxdmac, atxdmac->layout->gswf, atchan->mask);
		जबतक (!(at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CIS) & AT_XDMAC_CIS_FIS))
			cpu_relax();
	पूर्ण

	/*
	 * Remove size of all microblocks alपढ़ोy transferred and the current
	 * one. Then add the reमुख्यing size to transfer of the current
	 * microblock.
	 */
	descs_list = &desc->descs_list;
	list_क्रम_each_entry_safe(desc, _desc, descs_list, desc_node) अणु
		dwidth = at_xdmac_get_dwidth(desc->lld.mbr_cfg);
		residue -= (desc->lld.mbr_ubc & 0xffffff) << dwidth;
		अगर ((desc->lld.mbr_nda & 0xfffffffc) == cur_nda)
			अवरोध;
	पूर्ण
	residue += cur_ubc << dwidth;

	dma_set_residue(txstate, residue);

	dev_dbg(chan2dev(chan),
		 "%s: desc=0x%p, tx_dma_desc.phys=%pad, tx_status=%d, cookie=%d, residue=%d\n",
		 __func__, desc, &desc->tx_dma_desc.phys, ret, cookie, residue);

spin_unlock:
	spin_unlock_irqrestore(&atchan->lock, flags);
	वापस ret;
पूर्ण

/* Call must be रक्षित by lock. */
अटल व्योम at_xdmac_हटाओ_xfer(काष्ठा at_xdmac_chan *atchan,
				    काष्ठा at_xdmac_desc *desc)
अणु
	dev_dbg(chan2dev(&atchan->chan), "%s: desc 0x%p\n", __func__, desc);

	/*
	 * Remove the transfer from the transfer list then move the transfer
	 * descriptors पूर्णांकo the मुक्त descriptors list.
	 */
	list_del(&desc->xfer_node);
	list_splice_init(&desc->descs_list, &atchan->मुक्त_descs_list);
पूर्ण

अटल व्योम at_xdmac_advance_work(काष्ठा at_xdmac_chan *atchan)
अणु
	काष्ठा at_xdmac_desc	*desc;

	/*
	 * If channel is enabled, करो nothing, advance_work will be triggered
	 * after the पूर्णांकerruption.
	 */
	अगर (!at_xdmac_chan_is_enabled(atchan) && !list_empty(&atchan->xfers_list)) अणु
		desc = list_first_entry(&atchan->xfers_list,
					काष्ठा at_xdmac_desc,
					xfer_node);
		dev_vdbg(chan2dev(&atchan->chan), "%s: desc 0x%p\n", __func__, desc);
		अगर (!desc->active_xfer)
			at_xdmac_start_xfer(atchan, desc);
	पूर्ण
पूर्ण

अटल व्योम at_xdmac_handle_cyclic(काष्ठा at_xdmac_chan *atchan)
अणु
	काष्ठा at_xdmac_desc		*desc;
	काष्ठा dma_async_tx_descriptor	*txd;

	अगर (!list_empty(&atchan->xfers_list)) अणु
		desc = list_first_entry(&atchan->xfers_list,
					काष्ठा at_xdmac_desc, xfer_node);
		txd = &desc->tx_dma_desc;

		अगर (txd->flags & DMA_PREP_INTERRUPT)
			dmaengine_desc_get_callback_invoke(txd, शून्य);
	पूर्ण
पूर्ण

अटल व्योम at_xdmac_handle_error(काष्ठा at_xdmac_chan *atchan)
अणु
	काष्ठा at_xdmac		*atxdmac = to_at_xdmac(atchan->chan.device);
	काष्ठा at_xdmac_desc	*bad_desc;

	/*
	 * The descriptor currently at the head of the active list is
	 * broken. Since we करोn't have any way to report errors, we'll
	 * just have to scream loudly and try to जारी with other
	 * descriptors queued (अगर any).
	 */
	अगर (atchan->irq_status & AT_XDMAC_CIS_RBEIS)
		dev_err(chan2dev(&atchan->chan), "read bus error!!!");
	अगर (atchan->irq_status & AT_XDMAC_CIS_WBEIS)
		dev_err(chan2dev(&atchan->chan), "write bus error!!!");
	अगर (atchan->irq_status & AT_XDMAC_CIS_ROIS)
		dev_err(chan2dev(&atchan->chan), "request overflow error!!!");

	spin_lock_irq(&atchan->lock);

	/* Channel must be disabled first as it's not करोne स्वतःmatically */
	at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GD, atchan->mask);
	जबतक (at_xdmac_पढ़ो(atxdmac, AT_XDMAC_GS) & atchan->mask)
		cpu_relax();

	bad_desc = list_first_entry(&atchan->xfers_list,
				    काष्ठा at_xdmac_desc,
				    xfer_node);

	spin_unlock_irq(&atchan->lock);

	/* Prपूर्णांक bad descriptor's details अगर needed */
	dev_dbg(chan2dev(&atchan->chan),
		"%s: lld: mbr_sa=%pad, mbr_da=%pad, mbr_ubc=0x%08x\n",
		__func__, &bad_desc->lld.mbr_sa, &bad_desc->lld.mbr_da,
		bad_desc->lld.mbr_ubc);

	/* Then जारी with usual descriptor management */
पूर्ण

अटल व्योम at_xdmac_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा at_xdmac_chan	*atchan = from_tasklet(atchan, t, tasklet);
	काष्ठा at_xdmac_desc	*desc;
	u32			error_mask;

	dev_dbg(chan2dev(&atchan->chan), "%s: status=0x%08x\n",
		__func__, atchan->irq_status);

	error_mask = AT_XDMAC_CIS_RBEIS
		     | AT_XDMAC_CIS_WBEIS
		     | AT_XDMAC_CIS_ROIS;

	अगर (at_xdmac_chan_is_cyclic(atchan)) अणु
		at_xdmac_handle_cyclic(atchan);
	पूर्ण अन्यथा अगर ((atchan->irq_status & AT_XDMAC_CIS_LIS)
		   || (atchan->irq_status & error_mask)) अणु
		काष्ठा dma_async_tx_descriptor  *txd;

		अगर (atchan->irq_status & error_mask)
			at_xdmac_handle_error(atchan);

		spin_lock_irq(&atchan->lock);
		desc = list_first_entry(&atchan->xfers_list,
					काष्ठा at_xdmac_desc,
					xfer_node);
		dev_vdbg(chan2dev(&atchan->chan), "%s: desc 0x%p\n", __func__, desc);
		अगर (!desc->active_xfer) अणु
			dev_err(chan2dev(&atchan->chan), "Xfer not active: exiting");
			spin_unlock_irq(&atchan->lock);
			वापस;
		पूर्ण

		txd = &desc->tx_dma_desc;

		at_xdmac_हटाओ_xfer(atchan, desc);
		spin_unlock_irq(&atchan->lock);

		dma_cookie_complete(txd);
		अगर (txd->flags & DMA_PREP_INTERRUPT)
			dmaengine_desc_get_callback_invoke(txd, शून्य);

		dma_run_dependencies(txd);

		spin_lock_irq(&atchan->lock);
		at_xdmac_advance_work(atchan);
		spin_unlock_irq(&atchan->lock);
	पूर्ण
पूर्ण

अटल irqवापस_t at_xdmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा at_xdmac		*atxdmac = (काष्ठा at_xdmac *)dev_id;
	काष्ठा at_xdmac_chan	*atchan;
	u32			imr, status, pending;
	u32			chan_imr, chan_status;
	पूर्णांक			i, ret = IRQ_NONE;

	करो अणु
		imr = at_xdmac_पढ़ो(atxdmac, AT_XDMAC_GIM);
		status = at_xdmac_पढ़ो(atxdmac, AT_XDMAC_GIS);
		pending = status & imr;

		dev_vdbg(atxdmac->dma.dev,
			 "%s: status=0x%08x, imr=0x%08x, pending=0x%08x\n",
			 __func__, status, imr, pending);

		अगर (!pending)
			अवरोध;

		/* We have to find which channel has generated the पूर्णांकerrupt. */
		क्रम (i = 0; i < atxdmac->dma.chancnt; i++) अणु
			अगर (!((1 << i) & pending))
				जारी;

			atchan = &atxdmac->chan[i];
			chan_imr = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CIM);
			chan_status = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CIS);
			atchan->irq_status = chan_status & chan_imr;
			dev_vdbg(atxdmac->dma.dev,
				 "%s: chan%d: imr=0x%x, status=0x%x\n",
				 __func__, i, chan_imr, chan_status);
			dev_vdbg(chan2dev(&atchan->chan),
				 "%s: CC=0x%08x CNDA=0x%08x, CNDC=0x%08x, CSA=0x%08x, CDA=0x%08x, CUBC=0x%08x\n",
				 __func__,
				 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CC),
				 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDA),
				 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDC),
				 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CSA),
				 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CDA),
				 at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CUBC));

			अगर (atchan->irq_status & (AT_XDMAC_CIS_RBEIS | AT_XDMAC_CIS_WBEIS))
				at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GD, atchan->mask);

			tasklet_schedule(&atchan->tasklet);
			ret = IRQ_HANDLED;
		पूर्ण

	पूर्ण जबतक (pending);

	वापस ret;
पूर्ण

अटल व्योम at_xdmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_xdmac_chan *atchan = to_at_xdmac_chan(chan);
	अचिन्हित दीर्घ flags;

	dev_dbg(chan2dev(&atchan->chan), "%s\n", __func__);

	अगर (!at_xdmac_chan_is_cyclic(atchan)) अणु
		spin_lock_irqsave(&atchan->lock, flags);
		at_xdmac_advance_work(atchan);
		spin_unlock_irqrestore(&atchan->lock, flags);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक at_xdmac_device_config(काष्ठा dma_chan *chan,
				  काष्ठा dma_slave_config *config)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	पूर्णांक ret;
	अचिन्हित दीर्घ		flags;

	dev_dbg(chan2dev(chan), "%s\n", __func__);

	spin_lock_irqsave(&atchan->lock, flags);
	ret = at_xdmac_set_slave_config(chan, config);
	spin_unlock_irqrestore(&atchan->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक at_xdmac_device_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac		*atxdmac = to_at_xdmac(atchan->chan.device);
	अचिन्हित दीर्घ		flags;

	dev_dbg(chan2dev(chan), "%s\n", __func__);

	अगर (test_and_set_bit(AT_XDMAC_CHAN_IS_PAUSED, &atchan->status))
		वापस 0;

	spin_lock_irqsave(&atchan->lock, flags);
	at_xdmac_ग_लिखो(atxdmac, atxdmac->layout->grws, atchan->mask);
	जबतक (at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CC)
	       & (AT_XDMAC_CC_WRIP | AT_XDMAC_CC_RDIP))
		cpu_relax();
	spin_unlock_irqrestore(&atchan->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक at_xdmac_device_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac		*atxdmac = to_at_xdmac(atchan->chan.device);
	अचिन्हित दीर्घ		flags;

	dev_dbg(chan2dev(chan), "%s\n", __func__);

	spin_lock_irqsave(&atchan->lock, flags);
	अगर (!at_xdmac_chan_is_छोड़ोd(atchan)) अणु
		spin_unlock_irqrestore(&atchan->lock, flags);
		वापस 0;
	पूर्ण

	at_xdmac_ग_लिखो(atxdmac, atxdmac->layout->grwr, atchan->mask);
	clear_bit(AT_XDMAC_CHAN_IS_PAUSED, &atchan->status);
	spin_unlock_irqrestore(&atchan->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक at_xdmac_device_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_xdmac_desc	*desc, *_desc;
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac		*atxdmac = to_at_xdmac(atchan->chan.device);
	अचिन्हित दीर्घ		flags;

	dev_dbg(chan2dev(chan), "%s\n", __func__);

	spin_lock_irqsave(&atchan->lock, flags);
	at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GD, atchan->mask);
	जबतक (at_xdmac_पढ़ो(atxdmac, AT_XDMAC_GS) & atchan->mask)
		cpu_relax();

	/* Cancel all pending transfers. */
	list_क्रम_each_entry_safe(desc, _desc, &atchan->xfers_list, xfer_node)
		at_xdmac_हटाओ_xfer(atchan, desc);

	clear_bit(AT_XDMAC_CHAN_IS_PAUSED, &atchan->status);
	clear_bit(AT_XDMAC_CHAN_IS_CYCLIC, &atchan->status);
	spin_unlock_irqrestore(&atchan->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक at_xdmac_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac_desc	*desc;
	पूर्णांक			i;

	अगर (at_xdmac_chan_is_enabled(atchan)) अणु
		dev_err(chan2dev(chan),
			"can't allocate channel resources (channel enabled)\n");
		वापस -EIO;
	पूर्ण

	अगर (!list_empty(&atchan->मुक्त_descs_list)) अणु
		dev_err(chan2dev(chan),
			"can't allocate channel resources (channel not free from a previous use)\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < init_nr_desc_per_channel; i++) अणु
		desc = at_xdmac_alloc_desc(chan, GFP_KERNEL);
		अगर (!desc) अणु
			dev_warn(chan2dev(chan),
				"only %d descriptors have been allocated\n", i);
			अवरोध;
		पूर्ण
		list_add_tail(&desc->desc_node, &atchan->मुक्त_descs_list);
	पूर्ण

	dma_cookie_init(chan);

	dev_dbg(chan2dev(chan), "%s: allocated %d descriptors\n", __func__, i);

	वापस i;
पूर्ण

अटल व्योम at_xdmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);
	काष्ठा at_xdmac		*atxdmac = to_at_xdmac(chan->device);
	काष्ठा at_xdmac_desc	*desc, *_desc;

	list_क्रम_each_entry_safe(desc, _desc, &atchan->मुक्त_descs_list, desc_node) अणु
		dev_dbg(chan2dev(chan), "%s: freeing descriptor %p\n", __func__, desc);
		list_del(&desc->desc_node);
		dma_pool_मुक्त(atxdmac->at_xdmac_desc_pool, desc, desc->tx_dma_desc.phys);
	पूर्ण

	वापस;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक aपंचांगel_xdmac_prepare(काष्ठा device *dev)
अणु
	काष्ठा at_xdmac		*atxdmac = dev_get_drvdata(dev);
	काष्ठा dma_chan		*chan, *_chan;

	list_क्रम_each_entry_safe(chan, _chan, &atxdmac->dma.channels, device_node) अणु
		काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);

		/* Wait क्रम transfer completion, except in cyclic हाल. */
		अगर (at_xdmac_chan_is_enabled(atchan) && !at_xdmac_chan_is_cyclic(atchan))
			वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#	define aपंचांगel_xdmac_prepare शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aपंचांगel_xdmac_suspend(काष्ठा device *dev)
अणु
	काष्ठा at_xdmac		*atxdmac = dev_get_drvdata(dev);
	काष्ठा dma_chan		*chan, *_chan;

	list_क्रम_each_entry_safe(chan, _chan, &atxdmac->dma.channels, device_node) अणु
		काष्ठा at_xdmac_chan	*atchan = to_at_xdmac_chan(chan);

		atchan->save_cc = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CC);
		अगर (at_xdmac_chan_is_cyclic(atchan)) अणु
			अगर (!at_xdmac_chan_is_छोड़ोd(atchan))
				at_xdmac_device_छोड़ो(chan);
			atchan->save_cim = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CIM);
			atchan->save_cnda = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDA);
			atchan->save_cndc = at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CNDC);
		पूर्ण
	पूर्ण
	atxdmac->save_gim = at_xdmac_पढ़ो(atxdmac, AT_XDMAC_GIM);

	at_xdmac_off(atxdmac);
	clk_disable_unprepare(atxdmac->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_xdmac_resume(काष्ठा device *dev)
अणु
	काष्ठा at_xdmac		*atxdmac = dev_get_drvdata(dev);
	काष्ठा at_xdmac_chan	*atchan;
	काष्ठा dma_chan		*chan, *_chan;
	पूर्णांक			i;
	पूर्णांक ret;

	ret = clk_prepare_enable(atxdmac->clk);
	अगर (ret)
		वापस ret;

	/* Clear pending पूर्णांकerrupts. */
	क्रम (i = 0; i < atxdmac->dma.chancnt; i++) अणु
		atchan = &atxdmac->chan[i];
		जबतक (at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CIS))
			cpu_relax();
	पूर्ण

	at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GIE, atxdmac->save_gim);
	list_क्रम_each_entry_safe(chan, _chan, &atxdmac->dma.channels, device_node) अणु
		atchan = to_at_xdmac_chan(chan);
		at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CC, atchan->save_cc);
		अगर (at_xdmac_chan_is_cyclic(atchan)) अणु
			अगर (at_xdmac_chan_is_छोड़ोd(atchan))
				at_xdmac_device_resume(chan);
			at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CNDA, atchan->save_cnda);
			at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CNDC, atchan->save_cndc);
			at_xdmac_chan_ग_लिखो(atchan, AT_XDMAC_CIE, atchan->save_cim);
			wmb();
			at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GE, atchan->mask);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल व्योम at_xdmac_axi_config(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at_xdmac	*atxdmac = (काष्ठा at_xdmac *)platक्रमm_get_drvdata(pdev);
	bool dev_m2m = false;
	u32 dma_requests;

	अगर (!atxdmac->layout->axi_config)
		वापस; /* Not supported */

	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "dma-requests",
				  &dma_requests)) अणु
		dev_info(&pdev->dev, "controller in mem2mem mode.\n");
		dev_m2m = true;
	पूर्ण

	अगर (dev_m2m) अणु
		at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GCFG, AT_XDMAC_GCFG_M2M);
		at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GWAC, AT_XDMAC_GWAC_M2M);
	पूर्ण अन्यथा अणु
		at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GCFG, AT_XDMAC_GCFG_P2M);
		at_xdmac_ग_लिखो(atxdmac, AT_XDMAC_GWAC, AT_XDMAC_GWAC_P2M);
	पूर्ण
पूर्ण

अटल पूर्णांक at_xdmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at_xdmac	*atxdmac;
	पूर्णांक		irq, size, nr_channels, i, ret;
	व्योम __iomem	*base;
	u32		reg;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	/*
	 * Read number of xdmac channels, पढ़ो helper function can't be used
	 * since atxdmac is not yet allocated and we need to know the number
	 * of channels to करो the allocation.
	 */
	reg = पढ़ोl_relaxed(base + AT_XDMAC_GTYPE);
	nr_channels = AT_XDMAC_NB_CH(reg);
	अगर (nr_channels > AT_XDMAC_MAX_CHAN) अणु
		dev_err(&pdev->dev, "invalid number of channels (%u)\n",
			nr_channels);
		वापस -EINVAL;
	पूर्ण

	size = माप(*atxdmac);
	size += nr_channels * माप(काष्ठा at_xdmac_chan);
	atxdmac = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!atxdmac) अणु
		dev_err(&pdev->dev, "can't allocate at_xdmac structure\n");
		वापस -ENOMEM;
	पूर्ण

	atxdmac->regs = base;
	atxdmac->irq = irq;

	atxdmac->layout = of_device_get_match_data(&pdev->dev);
	अगर (!atxdmac->layout)
		वापस -ENODEV;

	atxdmac->clk = devm_clk_get(&pdev->dev, "dma_clk");
	अगर (IS_ERR(atxdmac->clk)) अणु
		dev_err(&pdev->dev, "can't get dma_clk\n");
		वापस PTR_ERR(atxdmac->clk);
	पूर्ण

	/* Do not use dev res to prevent races with tasklet */
	ret = request_irq(atxdmac->irq, at_xdmac_पूर्णांकerrupt, 0, "at_xdmac", atxdmac);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't request irq\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(atxdmac->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't prepare or enable clock\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	atxdmac->at_xdmac_desc_pool =
		dmam_pool_create(dev_name(&pdev->dev), &pdev->dev,
				माप(काष्ठा at_xdmac_desc), 4, 0);
	अगर (!atxdmac->at_xdmac_desc_pool) अणु
		dev_err(&pdev->dev, "no memory for descriptors dma pool\n");
		ret = -ENOMEM;
		जाओ err_clk_disable;
	पूर्ण

	dma_cap_set(DMA_CYCLIC, atxdmac->dma.cap_mask);
	dma_cap_set(DMA_INTERLEAVE, atxdmac->dma.cap_mask);
	dma_cap_set(DMA_MEMCPY, atxdmac->dma.cap_mask);
	dma_cap_set(DMA_MEMSET, atxdmac->dma.cap_mask);
	dma_cap_set(DMA_MEMSET_SG, atxdmac->dma.cap_mask);
	dma_cap_set(DMA_SLAVE, atxdmac->dma.cap_mask);
	/*
	 * Without DMA_PRIVATE the driver is not able to allocate more than
	 * one channel, second allocation fails in निजी_candidate.
	 */
	dma_cap_set(DMA_PRIVATE, atxdmac->dma.cap_mask);
	atxdmac->dma.dev				= &pdev->dev;
	atxdmac->dma.device_alloc_chan_resources	= at_xdmac_alloc_chan_resources;
	atxdmac->dma.device_मुक्त_chan_resources		= at_xdmac_मुक्त_chan_resources;
	atxdmac->dma.device_tx_status			= at_xdmac_tx_status;
	atxdmac->dma.device_issue_pending		= at_xdmac_issue_pending;
	atxdmac->dma.device_prep_dma_cyclic		= at_xdmac_prep_dma_cyclic;
	atxdmac->dma.device_prep_पूर्णांकerleaved_dma	= at_xdmac_prep_पूर्णांकerleaved;
	atxdmac->dma.device_prep_dma_स_नकल		= at_xdmac_prep_dma_स_नकल;
	atxdmac->dma.device_prep_dma_स_रखो		= at_xdmac_prep_dma_स_रखो;
	atxdmac->dma.device_prep_dma_स_रखो_sg		= at_xdmac_prep_dma_स_रखो_sg;
	atxdmac->dma.device_prep_slave_sg		= at_xdmac_prep_slave_sg;
	atxdmac->dma.device_config			= at_xdmac_device_config;
	atxdmac->dma.device_छोड़ो			= at_xdmac_device_छोड़ो;
	atxdmac->dma.device_resume			= at_xdmac_device_resume;
	atxdmac->dma.device_terminate_all		= at_xdmac_device_terminate_all;
	atxdmac->dma.src_addr_widths = AT_XDMAC_DMA_BUSWIDTHS;
	atxdmac->dma.dst_addr_widths = AT_XDMAC_DMA_BUSWIDTHS;
	atxdmac->dma.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	atxdmac->dma.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	/* Disable all chans and पूर्णांकerrupts. */
	at_xdmac_off(atxdmac);

	/* Init channels. */
	INIT_LIST_HEAD(&atxdmac->dma.channels);
	क्रम (i = 0; i < nr_channels; i++) अणु
		काष्ठा at_xdmac_chan *atchan = &atxdmac->chan[i];

		atchan->chan.device = &atxdmac->dma;
		list_add_tail(&atchan->chan.device_node,
			      &atxdmac->dma.channels);

		atchan->ch_regs = at_xdmac_chan_reg_base(atxdmac, i);
		atchan->mask = 1 << i;

		spin_lock_init(&atchan->lock);
		INIT_LIST_HEAD(&atchan->xfers_list);
		INIT_LIST_HEAD(&atchan->मुक्त_descs_list);
		tasklet_setup(&atchan->tasklet, at_xdmac_tasklet);

		/* Clear pending पूर्णांकerrupts. */
		जबतक (at_xdmac_chan_पढ़ो(atchan, AT_XDMAC_CIS))
			cpu_relax();
	पूर्ण
	platक्रमm_set_drvdata(pdev, atxdmac);

	ret = dma_async_device_रेजिस्टर(&atxdmac->dma);
	अगर (ret) अणु
		dev_err(&pdev->dev, "fail to register DMA engine device\n");
		जाओ err_clk_disable;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 at_xdmac_xlate, atxdmac);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register of dma controller\n");
		जाओ err_dma_unरेजिस्टर;
	पूर्ण

	dev_info(&pdev->dev, "%d channels, mapped at 0x%p\n",
		 nr_channels, atxdmac->regs);

	at_xdmac_axi_config(pdev);

	वापस 0;

err_dma_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(&atxdmac->dma);
err_clk_disable:
	clk_disable_unprepare(atxdmac->clk);
err_मुक्त_irq:
	मुक्त_irq(atxdmac->irq, atxdmac);
	वापस ret;
पूर्ण

अटल पूर्णांक at_xdmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at_xdmac	*atxdmac = (काष्ठा at_xdmac *)platक्रमm_get_drvdata(pdev);
	पूर्णांक		i;

	at_xdmac_off(atxdmac);
	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&atxdmac->dma);
	clk_disable_unprepare(atxdmac->clk);

	मुक्त_irq(atxdmac->irq, atxdmac);

	क्रम (i = 0; i < atxdmac->dma.chancnt; i++) अणु
		काष्ठा at_xdmac_chan *atchan = &atxdmac->chan[i];

		tasklet_समाप्त(&atchan->tasklet);
		at_xdmac_मुक्त_chan_resources(&atchan->chan);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops aपंचांगel_xdmac_dev_pm_ops = अणु
	.prepare	= aपंचांगel_xdmac_prepare,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(aपंचांगel_xdmac_suspend, aपंचांगel_xdmac_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_xdmac_dt_ids[] = अणु
	अणु
		.compatible = "atmel,sama5d4-dma",
		.data = &at_xdmac_sama5d4_layout,
	पूर्ण, अणु
		.compatible = "microchip,sama7g5-dma",
		.data = &at_xdmac_sama7g5_layout,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_xdmac_dt_ids);

अटल काष्ठा platक्रमm_driver at_xdmac_driver = अणु
	.probe		= at_xdmac_probe,
	.हटाओ		= at_xdmac_हटाओ,
	.driver = अणु
		.name		= "at_xdmac",
		.of_match_table	= of_match_ptr(aपंचांगel_xdmac_dt_ids),
		.pm		= &aपंचांगel_xdmac_dev_pm_ops,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init at_xdmac_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&at_xdmac_driver, at_xdmac_probe);
पूर्ण
subsys_initcall(at_xdmac_init);

MODULE_DESCRIPTION("Atmel Extended DMA Controller driver");
MODULE_AUTHOR("Ludovic Desroches <ludovic.desroches@atmel.com>");
MODULE_LICENSE("GPL");

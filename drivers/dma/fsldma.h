<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2007-2010 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author:
 *   Zhang Wei <wei.zhang@मुक्तscale.com>, Jul 2007
 *   Ebony Zhu <ebony.zhu@मुक्तscale.com>, May 2007
 */
#अगर_अघोषित __DMA_FSLDMA_H
#घोषणा __DMA_FSLDMA_H

#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dmaengine.h>

/* Define data काष्ठाures needed by Freescale
 * MPC8540 and MPC8349 DMA controller.
 */
#घोषणा FSL_DMA_MR_CS		0x00000001
#घोषणा FSL_DMA_MR_CC		0x00000002
#घोषणा FSL_DMA_MR_CA		0x00000008
#घोषणा FSL_DMA_MR_EIE		0x00000040
#घोषणा FSL_DMA_MR_XFE		0x00000020
#घोषणा FSL_DMA_MR_EOLNIE	0x00000100
#घोषणा FSL_DMA_MR_EOLSIE	0x00000080
#घोषणा FSL_DMA_MR_EOSIE	0x00000200
#घोषणा FSL_DMA_MR_CDSM		0x00000010
#घोषणा FSL_DMA_MR_CTM		0x00000004
#घोषणा FSL_DMA_MR_EMP_EN	0x00200000
#घोषणा FSL_DMA_MR_EMS_EN	0x00040000
#घोषणा FSL_DMA_MR_DAHE		0x00002000
#घोषणा FSL_DMA_MR_SAHE		0x00001000

#घोषणा FSL_DMA_MR_SAHTS_MASK	0x0000C000
#घोषणा FSL_DMA_MR_DAHTS_MASK	0x00030000
#घोषणा FSL_DMA_MR_BWC_MASK	0x0f000000

/*
 * Bandwidth/छोड़ो control determines how many bytes a given
 * channel is allowed to transfer beक्रमe the DMA engine छोड़ोs
 * the current channel and चयनes to the next channel
 */
#घोषणा FSL_DMA_MR_BWC         0x0A000000

/* Special MR definition क्रम MPC8349 */
#घोषणा FSL_DMA_MR_EOTIE	0x00000080
#घोषणा FSL_DMA_MR_PRC_RM	0x00000800

#घोषणा FSL_DMA_SR_CH		0x00000020
#घोषणा FSL_DMA_SR_PE		0x00000010
#घोषणा FSL_DMA_SR_CB		0x00000004
#घोषणा FSL_DMA_SR_TE		0x00000080
#घोषणा FSL_DMA_SR_EOSI		0x00000002
#घोषणा FSL_DMA_SR_EOLSI	0x00000001
#घोषणा FSL_DMA_SR_EOCDI	0x00000001
#घोषणा FSL_DMA_SR_EOLNI	0x00000008

#घोषणा FSL_DMA_SATR_SBPATMU			0x20000000
#घोषणा FSL_DMA_SATR_STRANSINT_RIO		0x00c00000
#घोषणा FSL_DMA_SATR_SREADTYPE_SNOOP_READ	0x00050000
#घोषणा FSL_DMA_SATR_SREADTYPE_BP_IORH		0x00020000
#घोषणा FSL_DMA_SATR_SREADTYPE_BP_NREAD		0x00040000
#घोषणा FSL_DMA_SATR_SREADTYPE_BP_MREAD		0x00070000

#घोषणा FSL_DMA_DATR_DBPATMU			0x20000000
#घोषणा FSL_DMA_DATR_DTRANSINT_RIO		0x00c00000
#घोषणा FSL_DMA_DATR_DWRITETYPE_SNOOP_WRITE	0x00050000
#घोषणा FSL_DMA_DATR_DWRITETYPE_BP_FLUSH	0x00010000

#घोषणा FSL_DMA_EOL		((u64)0x1)
#घोषणा FSL_DMA_SNEN		((u64)0x10)
#घोषणा FSL_DMA_EOSIE		0x8
#घोषणा FSL_DMA_NLDA_MASK	(~(u64)0x1f)

#घोषणा FSL_DMA_BCR_MAX_CNT	0x03ffffffu

#घोषणा FSL_DMA_DGSR_TE		0x80
#घोषणा FSL_DMA_DGSR_CH		0x20
#घोषणा FSL_DMA_DGSR_PE		0x10
#घोषणा FSL_DMA_DGSR_EOLNI	0x08
#घोषणा FSL_DMA_DGSR_CB		0x04
#घोषणा FSL_DMA_DGSR_EOSI	0x02
#घोषणा FSL_DMA_DGSR_EOLSI	0x01

#घोषणा FSL_DMA_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) | \
				BIT(DMA_SLAVE_BUSWIDTH_8_BYTES))
प्रकार u64 __bitwise v64;
प्रकार u32 __bitwise v32;

काष्ठा fsl_dma_ld_hw अणु
	v64 src_addr;
	v64 dst_addr;
	v64 next_ln_addr;
	v32 count;
	v32 reserve;
पूर्ण __attribute__((aligned(32)));

काष्ठा fsl_desc_sw अणु
	काष्ठा fsl_dma_ld_hw hw;
	काष्ठा list_head node;
	काष्ठा list_head tx_list;
	काष्ठा dma_async_tx_descriptor async_tx;
पूर्ण __attribute__((aligned(32)));

काष्ठा fsldma_chan_regs अणु
	u32 mr;		/* 0x00 - Mode Register */
	u32 sr;		/* 0x04 - Status Register */
	u64 cdar;	/* 0x08 - Current descriptor address रेजिस्टर */
	u64 sar;	/* 0x10 - Source Address Register */
	u64 dar;	/* 0x18 - Destination Address Register */
	u32 bcr;	/* 0x20 - Byte Count Register */
	u64 ndar;	/* 0x24 - Next Descriptor Address Register */
पूर्ण;

काष्ठा fsldma_chan;
#घोषणा FSL_DMA_MAX_CHANS_PER_DEVICE 8

काष्ठा fsldma_device अणु
	व्योम __iomem *regs;	/* DGSR रेजिस्टर base */
	काष्ठा device *dev;
	काष्ठा dma_device common;
	काष्ठा fsldma_chan *chan[FSL_DMA_MAX_CHANS_PER_DEVICE];
	u32 feature;		/* The same as DMA channels */
	पूर्णांक irq;		/* Channel IRQ */
पूर्ण;

/* Define macros क्रम fsldma_chan->feature property */
#घोषणा FSL_DMA_LITTLE_ENDIAN	0x00000000
#घोषणा FSL_DMA_BIG_ENDIAN	0x00000001

#घोषणा FSL_DMA_IP_MASK		0x00000ff0
#घोषणा FSL_DMA_IP_85XX		0x00000010
#घोषणा FSL_DMA_IP_83XX		0x00000020

#घोषणा FSL_DMA_CHAN_PAUSE_EXT	0x00001000
#घोषणा FSL_DMA_CHAN_START_EXT	0x00002000

#अगर_घोषित CONFIG_PM
काष्ठा fsldma_chan_regs_save अणु
	u32 mr;
पूर्ण;

क्रमागत fsldma_pm_state अणु
	RUNNING = 0,
	SUSPENDED,
पूर्ण;
#पूर्ण_अगर

काष्ठा fsldma_chan अणु
	अक्षर name[8];			/* Channel name */
	काष्ठा fsldma_chan_regs __iomem *regs;
	spinlock_t desc_lock;		/* Descriptor operation lock */
	/*
	 * Descriptors which are queued to run, but have not yet been
	 * submitted to the hardware क्रम execution
	 */
	काष्ठा list_head ld_pending;
	/*
	 * Descriptors which are currently being executed by the hardware
	 */
	काष्ठा list_head ld_running;
	/*
	 * Descriptors which have finished execution by the hardware. These
	 * descriptors have alपढ़ोy had their cleanup actions run. They are
	 * रुकोing क्रम the ACK bit to be set by the async_tx API.
	 */
	काष्ठा list_head ld_completed;	/* Link descriptors queue */
	काष्ठा dma_chan common;		/* DMA common channel */
	काष्ठा dma_pool *desc_pool;	/* Descriptors pool */
	काष्ठा device *dev;		/* Channel device */
	पूर्णांक irq;			/* Channel IRQ */
	पूर्णांक id;				/* Raw id of this channel */
	काष्ठा tasklet_काष्ठा tasklet;
	u32 feature;
	bool idle;			/* DMA controller is idle */
#अगर_घोषित CONFIG_PM
	काष्ठा fsldma_chan_regs_save regs_save;
	क्रमागत fsldma_pm_state pm_state;
#पूर्ण_अगर

	व्योम (*toggle_ext_छोड़ो)(काष्ठा fsldma_chan *fsl_chan, पूर्णांक enable);
	व्योम (*toggle_ext_start)(काष्ठा fsldma_chan *fsl_chan, पूर्णांक enable);
	व्योम (*set_src_loop_size)(काष्ठा fsldma_chan *fsl_chan, पूर्णांक size);
	व्योम (*set_dst_loop_size)(काष्ठा fsldma_chan *fsl_chan, पूर्णांक size);
	व्योम (*set_request_count)(काष्ठा fsldma_chan *fsl_chan, पूर्णांक size);
पूर्ण;

#घोषणा to_fsl_chan(chan) container_of(chan, काष्ठा fsldma_chan, common)
#घोषणा to_fsl_desc(lh) container_of(lh, काष्ठा fsl_desc_sw, node)
#घोषणा tx_to_fsl_desc(tx) container_of(tx, काष्ठा fsl_desc_sw, async_tx)

#अगर_घोषित	CONFIG_PPC
#घोषणा fsl_ioपढ़ो32(p)		in_le32(p)
#घोषणा fsl_ioपढ़ो32be(p)	in_be32(p)
#घोषणा fsl_ioग_लिखो32(v, p)	out_le32(p, v)
#घोषणा fsl_ioग_लिखो32be(v, p)	out_be32(p, v)

#अगर_घोषित __घातerpc64__
#घोषणा fsl_ioपढ़ो64(p)		in_le64(p)
#घोषणा fsl_ioपढ़ो64be(p)	in_be64(p)
#घोषणा fsl_ioग_लिखो64(v, p)	out_le64(p, v)
#घोषणा fsl_ioग_लिखो64be(v, p)	out_be64(p, v)
#अन्यथा
अटल u64 fsl_ioपढ़ो64(स्थिर u64 __iomem *addr)
अणु
	u32 val_lo = in_le32((u32 __iomem *)addr);
	u32 val_hi = in_le32((u32 __iomem *)addr + 1);

	वापस ((u64)val_hi << 32) + val_lo;
पूर्ण

अटल व्योम fsl_ioग_लिखो64(u64 val, u64 __iomem *addr)
अणु
	out_le32((u32 __iomem *)addr + 1, val >> 32);
	out_le32((u32 __iomem *)addr, (u32)val);
पूर्ण

अटल u64 fsl_ioपढ़ो64be(स्थिर u64 __iomem *addr)
अणु
	u32 val_hi = in_be32((u32 __iomem *)addr);
	u32 val_lo = in_be32((u32 __iomem *)addr + 1);

	वापस ((u64)val_hi << 32) + val_lo;
पूर्ण

अटल व्योम fsl_ioग_लिखो64be(u64 val, u64 __iomem *addr)
अणु
	out_be32((u32 __iomem *)addr, val >> 32);
	out_be32((u32 __iomem *)addr + 1, (u32)val);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(CONFIG_ARM64) || defined(CONFIG_ARM)
#घोषणा fsl_ioपढ़ो32(p)		ioपढ़ो32(p)
#घोषणा fsl_ioपढ़ो32be(p)	ioपढ़ो32be(p)
#घोषणा fsl_ioग_लिखो32(v, p)	ioग_लिखो32(v, p)
#घोषणा fsl_ioग_लिखो32be(v, p)	ioग_लिखो32be(v, p)
#घोषणा fsl_ioपढ़ो64(p)		ioपढ़ो64(p)
#घोषणा fsl_ioपढ़ो64be(p)	ioपढ़ो64be(p)
#घोषणा fsl_ioग_लिखो64(v, p)	ioग_लिखो64(v, p)
#घोषणा fsl_ioग_लिखो64be(v, p)	ioग_लिखो64be(v, p)
#पूर्ण_अगर

#घोषणा FSL_DMA_IN(fsl_dma, addr, width)			\
		(((fsl_dma)->feature & FSL_DMA_BIG_ENDIAN) ?	\
			fsl_ioपढ़ो##width##be(addr) : fsl_ioपढ़ो##width(addr))

#घोषणा FSL_DMA_OUT(fsl_dma, addr, val, width)			\
		(((fsl_dma)->feature & FSL_DMA_BIG_ENDIAN) ?	\
			fsl_ioग_लिखो##width##be(val, addr) : fsl_ioग_लिखो	\
		##width(val, addr))

#घोषणा DMA_TO_CPU(fsl_chan, d, width)					\
		(((fsl_chan)->feature & FSL_DMA_BIG_ENDIAN) ?		\
			be##width##_to_cpu((__क्रमce __be##width)(v##width)d) : \
			le##width##_to_cpu((__क्रमce __le##width)(v##width)d))
#घोषणा CPU_TO_DMA(fsl_chan, c, width)					\
		(((fsl_chan)->feature & FSL_DMA_BIG_ENDIAN) ?		\
			(__क्रमce v##width)cpu_to_be##width(c) :		\
			(__क्रमce v##width)cpu_to_le##width(c))

#पूर्ण_अगर	/* __DMA_FSLDMA_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the Intel पूर्णांकegrated DMA 64-bit
 *
 * Copyright (C) 2015 Intel Corporation
 */

#अगर_अघोषित __DMA_IDMA64_H__
#घोषणा __DMA_IDMA64_H__

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <linux/io-64-nonatomic-lo-hi.h>

#समावेश "virt-dma.h"

/* Channel रेजिस्टरs */

#घोषणा IDMA64_CH_SAR		0x00	/* Source Address Register */
#घोषणा IDMA64_CH_DAR		0x08	/* Destination Address Register */
#घोषणा IDMA64_CH_LLP		0x10	/* Linked List Poपूर्णांकer */
#घोषणा IDMA64_CH_CTL_LO	0x18	/* Control Register Low */
#घोषणा IDMA64_CH_CTL_HI	0x1c	/* Control Register High */
#घोषणा IDMA64_CH_SSTAT		0x20
#घोषणा IDMA64_CH_DSTAT		0x28
#घोषणा IDMA64_CH_SSTATAR	0x30
#घोषणा IDMA64_CH_DSTATAR	0x38
#घोषणा IDMA64_CH_CFG_LO	0x40	/* Configuration Register Low */
#घोषणा IDMA64_CH_CFG_HI	0x44	/* Configuration Register High */
#घोषणा IDMA64_CH_SGR		0x48
#घोषणा IDMA64_CH_DSR		0x50

#घोषणा IDMA64_CH_LENGTH	0x58

/* Bitfields in CTL_LO */
#घोषणा IDMA64C_CTLL_INT_EN		(1 << 0)	/* irqs enabled? */
#घोषणा IDMA64C_CTLL_DST_WIDTH(x)	((x) << 1)	/* bytes per element */
#घोषणा IDMA64C_CTLL_SRC_WIDTH(x)	((x) << 4)
#घोषणा IDMA64C_CTLL_DST_INC		(0 << 8)	/* DAR update/not */
#घोषणा IDMA64C_CTLL_DST_FIX		(1 << 8)
#घोषणा IDMA64C_CTLL_SRC_INC		(0 << 10)	/* SAR update/not */
#घोषणा IDMA64C_CTLL_SRC_FIX		(1 << 10)
#घोषणा IDMA64C_CTLL_DST_MSIZE(x)	((x) << 11)	/* burst, #elements */
#घोषणा IDMA64C_CTLL_SRC_MSIZE(x)	((x) << 14)
#घोषणा IDMA64C_CTLL_FC_M2P		(1 << 20)	/* mem-to-periph */
#घोषणा IDMA64C_CTLL_FC_P2M		(2 << 20)	/* periph-to-mem */
#घोषणा IDMA64C_CTLL_LLP_D_EN		(1 << 27)	/* dest block chain */
#घोषणा IDMA64C_CTLL_LLP_S_EN		(1 << 28)	/* src block chain */

/* Bitfields in CTL_HI */
#घोषणा IDMA64C_CTLH_BLOCK_TS_MASK	((1 << 17) - 1)
#घोषणा IDMA64C_CTLH_BLOCK_TS(x)	((x) & IDMA64C_CTLH_BLOCK_TS_MASK)
#घोषणा IDMA64C_CTLH_DONE		(1 << 17)

/* Bitfields in CFG_LO */
#घोषणा IDMA64C_CFGL_DST_BURST_ALIGN	(1 << 0)	/* dst burst align */
#घोषणा IDMA64C_CFGL_SRC_BURST_ALIGN	(1 << 1)	/* src burst align */
#घोषणा IDMA64C_CFGL_CH_SUSP		(1 << 8)
#घोषणा IDMA64C_CFGL_FIFO_EMPTY		(1 << 9)
#घोषणा IDMA64C_CFGL_CH_DRAIN		(1 << 10)	/* drain FIFO */
#घोषणा IDMA64C_CFGL_DST_OPT_BL		(1 << 20)	/* optimize dst burst length */
#घोषणा IDMA64C_CFGL_SRC_OPT_BL		(1 << 21)	/* optimize src burst length */

/* Bitfields in CFG_HI */
#घोषणा IDMA64C_CFGH_SRC_PER(x)		((x) << 0)	/* src peripheral */
#घोषणा IDMA64C_CFGH_DST_PER(x)		((x) << 4)	/* dst peripheral */
#घोषणा IDMA64C_CFGH_RD_ISSUE_THD(x)	((x) << 8)
#घोषणा IDMA64C_CFGH_WR_ISSUE_THD(x)	((x) << 18)

/* Interrupt रेजिस्टरs */

#घोषणा IDMA64_INT_XFER		0x00
#घोषणा IDMA64_INT_BLOCK	0x08
#घोषणा IDMA64_INT_SRC_TRAN	0x10
#घोषणा IDMA64_INT_DST_TRAN	0x18
#घोषणा IDMA64_INT_ERROR	0x20

#घोषणा IDMA64_RAW(x)		(0x2c0 + IDMA64_INT_##x)	/* r */
#घोषणा IDMA64_STATUS(x)	(0x2e8 + IDMA64_INT_##x)	/* r (raw & mask) */
#घोषणा IDMA64_MASK(x)		(0x310 + IDMA64_INT_##x)	/* rw (set = irq enabled) */
#घोषणा IDMA64_CLEAR(x)		(0x338 + IDMA64_INT_##x)	/* w (ack, affects "raw") */

/* Common रेजिस्टरs */

#घोषणा IDMA64_STATUS_INT	0x360	/* r */
#घोषणा IDMA64_CFG		0x398
#घोषणा IDMA64_CH_EN		0x3a0

/* Bitfields in CFG */
#घोषणा IDMA64_CFG_DMA_EN		(1 << 0)

/* Hardware descriptor क्रम Linked LIst transfers */
काष्ठा idma64_lli अणु
	u64		sar;
	u64		dar;
	u64		llp;
	u32		ctllo;
	u32		ctlhi;
	u32		sstat;
	u32		dstat;
पूर्ण;

काष्ठा idma64_hw_desc अणु
	काष्ठा idma64_lli *lli;
	dma_addr_t llp;
	dma_addr_t phys;
	अचिन्हित पूर्णांक len;
पूर्ण;

काष्ठा idma64_desc अणु
	काष्ठा virt_dma_desc vdesc;
	क्रमागत dma_transfer_direction direction;
	काष्ठा idma64_hw_desc *hw;
	अचिन्हित पूर्णांक ndesc;
	माप_प्रकार length;
	क्रमागत dma_status status;
पूर्ण;

अटल अंतरभूत काष्ठा idma64_desc *to_idma64_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा idma64_desc, vdesc);
पूर्ण

काष्ठा idma64_chan अणु
	काष्ठा virt_dma_chan vchan;

	व्योम __iomem *regs;

	/* hardware configuration */
	क्रमागत dma_transfer_direction direction;
	अचिन्हित पूर्णांक mask;
	काष्ठा dma_slave_config config;

	व्योम *pool;
	काष्ठा idma64_desc *desc;
पूर्ण;

अटल अंतरभूत काष्ठा idma64_chan *to_idma64_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा idma64_chan, vchan.chan);
पूर्ण

#घोषणा channel_set_bit(idma64, reg, mask)	\
	dma_ग_लिखोl(idma64, reg, ((mask) << 8) | (mask))
#घोषणा channel_clear_bit(idma64, reg, mask)	\
	dma_ग_लिखोl(idma64, reg, ((mask) << 8) | 0)

अटल अंतरभूत u32 idma64c_पढ़ोl(काष्ठा idma64_chan *idma64c, पूर्णांक offset)
अणु
	वापस पढ़ोl(idma64c->regs + offset);
पूर्ण

अटल अंतरभूत व्योम idma64c_ग_लिखोl(काष्ठा idma64_chan *idma64c, पूर्णांक offset,
				  u32 value)
अणु
	ग_लिखोl(value, idma64c->regs + offset);
पूर्ण

#घोषणा channel_पढ़ोl(idma64c, reg)		\
	idma64c_पढ़ोl(idma64c, IDMA64_CH_##reg)
#घोषणा channel_ग_लिखोl(idma64c, reg, value)	\
	idma64c_ग_लिखोl(idma64c, IDMA64_CH_##reg, (value))

अटल अंतरभूत u64 idma64c_पढ़ोq(काष्ठा idma64_chan *idma64c, पूर्णांक offset)
अणु
	वापस lo_hi_पढ़ोq(idma64c->regs + offset);
पूर्ण

अटल अंतरभूत व्योम idma64c_ग_लिखोq(काष्ठा idma64_chan *idma64c, पूर्णांक offset,
				  u64 value)
अणु
	lo_hi_ग_लिखोq(value, idma64c->regs + offset);
पूर्ण

#घोषणा channel_पढ़ोq(idma64c, reg)		\
	idma64c_पढ़ोq(idma64c, IDMA64_CH_##reg)
#घोषणा channel_ग_लिखोq(idma64c, reg, value)	\
	idma64c_ग_लिखोq(idma64c, IDMA64_CH_##reg, (value))

काष्ठा idma64 अणु
	काष्ठा dma_device dma;

	व्योम __iomem *regs;

	/* channels */
	अचिन्हित लघु all_chan_mask;
	काष्ठा idma64_chan *chan;
पूर्ण;

अटल अंतरभूत काष्ठा idma64 *to_idma64(काष्ठा dma_device *ddev)
अणु
	वापस container_of(ddev, काष्ठा idma64, dma);
पूर्ण

अटल अंतरभूत u32 idma64_पढ़ोl(काष्ठा idma64 *idma64, पूर्णांक offset)
अणु
	वापस पढ़ोl(idma64->regs + offset);
पूर्ण

अटल अंतरभूत व्योम idma64_ग_लिखोl(काष्ठा idma64 *idma64, पूर्णांक offset, u32 value)
अणु
	ग_लिखोl(value, idma64->regs + offset);
पूर्ण

#घोषणा dma_पढ़ोl(idma64, reg)			\
	idma64_पढ़ोl(idma64, IDMA64_##reg)
#घोषणा dma_ग_लिखोl(idma64, reg, value)		\
	idma64_ग_लिखोl(idma64, IDMA64_##reg, (value))

/**
 * काष्ठा idma64_chip - representation of iDMA 64-bit controller hardware
 * @dev:		काष्ठा device of the DMA controller
 * @sysdev:		काष्ठा device of the physical device that करोes DMA
 * @irq:		irq line
 * @regs:		memory mapped I/O space
 * @idma64:		काष्ठा idma64 that is filed by idma64_probe()
 */
काष्ठा idma64_chip अणु
	काष्ठा device	*dev;
	काष्ठा device	*sysdev;
	पूर्णांक		irq;
	व्योम __iomem	*regs;
	काष्ठा idma64	*idma64;
पूर्ण;

#पूर्ण_अगर /* __DMA_IDMA64_H__ */

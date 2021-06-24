<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the High Speed UART DMA
 *
 * Copyright (C) 2015 Intel Corporation
 *
 * Partially based on the bits found in drivers/tty/serial/mfd.c.
 */

#अगर_अघोषित __DMA_HSU_H__
#घोषणा __DMA_HSU_H__

#समावेश <linux/spinlock.h>
#समावेश <linux/dma/hsu.h>

#समावेश "../virt-dma.h"

#घोषणा HSU_CH_SR		0x00			/* channel status */
#घोषणा HSU_CH_CR		0x04			/* channel control */
#घोषणा HSU_CH_DCR		0x08			/* descriptor control */
#घोषणा HSU_CH_BSR		0x10			/* FIFO buffer size */
#घोषणा HSU_CH_MTSR		0x14			/* minimum transfer size */
#घोषणा HSU_CH_DxSAR(x)		(0x20 + 8 * (x))	/* desc start addr */
#घोषणा HSU_CH_DxTSR(x)		(0x24 + 8 * (x))	/* desc transfer size */
#घोषणा HSU_CH_D0SAR		0x20			/* desc 0 start addr */
#घोषणा HSU_CH_D0TSR		0x24			/* desc 0 transfer size */
#घोषणा HSU_CH_D1SAR		0x28
#घोषणा HSU_CH_D1TSR		0x2c
#घोषणा HSU_CH_D2SAR		0x30
#घोषणा HSU_CH_D2TSR		0x34
#घोषणा HSU_CH_D3SAR		0x38
#घोषणा HSU_CH_D3TSR		0x3c

#घोषणा HSU_DMA_CHAN_NR_DESC	4
#घोषणा HSU_DMA_CHAN_LENGTH	0x40

/* Bits in HSU_CH_SR */
#घोषणा HSU_CH_SR_DESCTO(x)	BIT(8 + (x))
#घोषणा HSU_CH_SR_DESCTO_ANY	(BIT(11) | BIT(10) | BIT(9) | BIT(8))
#घोषणा HSU_CH_SR_CHE		BIT(15)
#घोषणा HSU_CH_SR_DESCE(x)	BIT(16 + (x))
#घोषणा HSU_CH_SR_DESCE_ANY	(BIT(19) | BIT(18) | BIT(17) | BIT(16))
#घोषणा HSU_CH_SR_CDESC_ANY	(BIT(31) | BIT(30))

/* Bits in HSU_CH_CR */
#घोषणा HSU_CH_CR_CHA		BIT(0)
#घोषणा HSU_CH_CR_CHD		BIT(1)

/* Bits in HSU_CH_DCR */
#घोषणा HSU_CH_DCR_DESCA(x)	BIT(0 + (x))
#घोषणा HSU_CH_DCR_CHSOD(x)	BIT(8 + (x))
#घोषणा HSU_CH_DCR_CHSOTO	BIT(14)
#घोषणा HSU_CH_DCR_CHSOE	BIT(15)
#घोषणा HSU_CH_DCR_CHDI(x)	BIT(16 + (x))
#घोषणा HSU_CH_DCR_CHEI		BIT(23)
#घोषणा HSU_CH_DCR_CHTOI(x)	BIT(24 + (x))

/* Bits in HSU_CH_DxTSR */
#घोषणा HSU_CH_DxTSR_MASK	GENMASK(15, 0)
#घोषणा HSU_CH_DxTSR_TSR(x)	((x) & HSU_CH_DxTSR_MASK)

काष्ठा hsu_dma_sg अणु
	dma_addr_t addr;
	अचिन्हित पूर्णांक len;
पूर्ण;

काष्ठा hsu_dma_desc अणु
	काष्ठा virt_dma_desc vdesc;
	क्रमागत dma_transfer_direction direction;
	काष्ठा hsu_dma_sg *sg;
	अचिन्हित पूर्णांक nents;
	माप_प्रकार length;
	अचिन्हित पूर्णांक active;
	क्रमागत dma_status status;
पूर्ण;

अटल अंतरभूत काष्ठा hsu_dma_desc *to_hsu_dma_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा hsu_dma_desc, vdesc);
पूर्ण

काष्ठा hsu_dma_chan अणु
	काष्ठा virt_dma_chan vchan;

	व्योम __iomem *reg;

	/* hardware configuration */
	क्रमागत dma_transfer_direction direction;
	काष्ठा dma_slave_config config;

	काष्ठा hsu_dma_desc *desc;
पूर्ण;

अटल अंतरभूत काष्ठा hsu_dma_chan *to_hsu_dma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा hsu_dma_chan, vchan.chan);
पूर्ण

अटल अंतरभूत u32 hsu_chan_पढ़ोl(काष्ठा hsu_dma_chan *hsuc, पूर्णांक offset)
अणु
	वापस पढ़ोl(hsuc->reg + offset);
पूर्ण

अटल अंतरभूत व्योम hsu_chan_ग_लिखोl(काष्ठा hsu_dma_chan *hsuc, पूर्णांक offset,
				   u32 value)
अणु
	ग_लिखोl(value, hsuc->reg + offset);
पूर्ण

काष्ठा hsu_dma अणु
	काष्ठा dma_device		dma;

	/* channels */
	काष्ठा hsu_dma_chan		*chan;
	अचिन्हित लघु			nr_channels;
पूर्ण;

अटल अंतरभूत काष्ठा hsu_dma *to_hsu_dma(काष्ठा dma_device *ddev)
अणु
	वापस container_of(ddev, काष्ठा hsu_dma, dma);
पूर्ण

#पूर्ण_अगर /* __DMA_HSU_H__ */

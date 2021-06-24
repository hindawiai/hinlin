<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Spपढ़ोtrum Communications Inc.

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#समावेश "sprd-mcdt.h"

/* MCDT रेजिस्टरs definition */
#घोषणा MCDT_CH0_TXD		0x0
#घोषणा MCDT_CH0_RXD		0x28
#घोषणा MCDT_DAC0_WTMK		0x60
#घोषणा MCDT_ADC0_WTMK		0x88
#घोषणा MCDT_DMA_EN		0xb0

#घोषणा MCDT_INT_EN0		0xb4
#घोषणा MCDT_INT_EN1		0xb8
#घोषणा MCDT_INT_EN2		0xbc

#घोषणा MCDT_INT_CLR0		0xc0
#घोषणा MCDT_INT_CLR1		0xc4
#घोषणा MCDT_INT_CLR2		0xc8

#घोषणा MCDT_INT_RAW1		0xcc
#घोषणा MCDT_INT_RAW2		0xd0
#घोषणा MCDT_INT_RAW3		0xd4

#घोषणा MCDT_INT_MSK1		0xd8
#घोषणा MCDT_INT_MSK2		0xdc
#घोषणा MCDT_INT_MSK3		0xe0

#घोषणा MCDT_DAC0_FIFO_ADDR_ST	0xe4
#घोषणा MCDT_ADC0_FIFO_ADDR_ST	0xe8

#घोषणा MCDT_CH_FIFO_ST0	0x134
#घोषणा MCDT_CH_FIFO_ST1	0x138
#घोषणा MCDT_CH_FIFO_ST2	0x13c

#घोषणा MCDT_INT_MSK_CFG0	0x140
#घोषणा MCDT_INT_MSK_CFG1	0x144

#घोषणा MCDT_DMA_CFG0		0x148
#घोषणा MCDT_FIFO_CLR		0x14c
#घोषणा MCDT_DMA_CFG1		0x150
#घोषणा MCDT_DMA_CFG2		0x154
#घोषणा MCDT_DMA_CFG3		0x158
#घोषणा MCDT_DMA_CFG4		0x15c
#घोषणा MCDT_DMA_CFG5		0x160

/* Channel water mark definition */
#घोषणा MCDT_CH_FIFO_AE_SHIFT	16
#घोषणा MCDT_CH_FIFO_AE_MASK	GENMASK(24, 16)
#घोषणा MCDT_CH_FIFO_AF_MASK	GENMASK(8, 0)

/* DMA channel select definition */
#घोषणा MCDT_DMA_CH0_SEL_MASK	GENMASK(3, 0)
#घोषणा MCDT_DMA_CH0_SEL_SHIFT	0
#घोषणा MCDT_DMA_CH1_SEL_MASK	GENMASK(7, 4)
#घोषणा MCDT_DMA_CH1_SEL_SHIFT	4
#घोषणा MCDT_DMA_CH2_SEL_MASK	GENMASK(11, 8)
#घोषणा MCDT_DMA_CH2_SEL_SHIFT	8
#घोषणा MCDT_DMA_CH3_SEL_MASK	GENMASK(15, 12)
#घोषणा MCDT_DMA_CH3_SEL_SHIFT	12
#घोषणा MCDT_DMA_CH4_SEL_MASK	GENMASK(19, 16)
#घोषणा MCDT_DMA_CH4_SEL_SHIFT	16
#घोषणा MCDT_DAC_DMA_SHIFT	16

/* DMA channel ACK select definition */
#घोषणा MCDT_DMA_ACK_SEL_MASK	GENMASK(3, 0)

/* Channel FIFO definition */
#घोषणा MCDT_CH_FIFO_ADDR_SHIFT	16
#घोषणा MCDT_CH_FIFO_ADDR_MASK	GENMASK(9, 0)
#घोषणा MCDT_ADC_FIFO_SHIFT	16
#घोषणा MCDT_FIFO_LENGTH	512

#घोषणा MCDT_ADC_CHANNEL_NUM	10
#घोषणा MCDT_DAC_CHANNEL_NUM	10
#घोषणा MCDT_CHANNEL_NUM	(MCDT_ADC_CHANNEL_NUM + MCDT_DAC_CHANNEL_NUM)

क्रमागत sprd_mcdt_fअगरo_पूर्णांक अणु
	MCDT_ADC_FIFO_AE_INT,
	MCDT_ADC_FIFO_AF_INT,
	MCDT_DAC_FIFO_AE_INT,
	MCDT_DAC_FIFO_AF_INT,
	MCDT_ADC_FIFO_OV_INT,
	MCDT_DAC_FIFO_OV_INT
पूर्ण;

क्रमागत sprd_mcdt_fअगरo_sts अणु
	MCDT_ADC_FIFO_REAL_FULL,
	MCDT_ADC_FIFO_REAL_EMPTY,
	MCDT_ADC_FIFO_AF,
	MCDT_ADC_FIFO_AE,
	MCDT_DAC_FIFO_REAL_FULL,
	MCDT_DAC_FIFO_REAL_EMPTY,
	MCDT_DAC_FIFO_AF,
	MCDT_DAC_FIFO_AE
पूर्ण;

काष्ठा sprd_mcdt_dev अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	spinlock_t lock;
	काष्ठा sprd_mcdt_chan chan[MCDT_CHANNEL_NUM];
पूर्ण;

अटल LIST_HEAD(sprd_mcdt_chan_list);
अटल DEFINE_MUTEX(sprd_mcdt_list_mutex);

अटल व्योम sprd_mcdt_update(काष्ठा sprd_mcdt_dev *mcdt, u32 reg, u32 val,
			     u32 mask)
अणु
	u32 orig = पढ़ोl_relaxed(mcdt->base + reg);
	u32 पंचांगp;

	पंचांगp = (orig & ~mask) | val;
	ग_लिखोl_relaxed(पंचांगp, mcdt->base + reg);
पूर्ण

अटल व्योम sprd_mcdt_dac_set_watermark(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
					u32 full, u32 empty)
अणु
	u32 reg = MCDT_DAC0_WTMK + channel * 4;
	u32 water_mark =
		(empty << MCDT_CH_FIFO_AE_SHIFT) & MCDT_CH_FIFO_AE_MASK;

	water_mark |= full & MCDT_CH_FIFO_AF_MASK;
	sprd_mcdt_update(mcdt, reg, water_mark,
			 MCDT_CH_FIFO_AE_MASK | MCDT_CH_FIFO_AF_MASK);
पूर्ण

अटल व्योम sprd_mcdt_adc_set_watermark(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
					u32 full, u32 empty)
अणु
	u32 reg = MCDT_ADC0_WTMK + channel * 4;
	u32 water_mark =
		(empty << MCDT_CH_FIFO_AE_SHIFT) & MCDT_CH_FIFO_AE_MASK;

	water_mark |= full & MCDT_CH_FIFO_AF_MASK;
	sprd_mcdt_update(mcdt, reg, water_mark,
			 MCDT_CH_FIFO_AE_MASK | MCDT_CH_FIFO_AF_MASK);
पूर्ण

अटल व्योम sprd_mcdt_dac_dma_enable(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				     bool enable)
अणु
	u32 shअगरt = MCDT_DAC_DMA_SHIFT + channel;

	अगर (enable)
		sprd_mcdt_update(mcdt, MCDT_DMA_EN, BIT(shअगरt), BIT(shअगरt));
	अन्यथा
		sprd_mcdt_update(mcdt, MCDT_DMA_EN, 0, BIT(shअगरt));
पूर्ण

अटल व्योम sprd_mcdt_adc_dma_enable(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				     bool enable)
अणु
	अगर (enable)
		sprd_mcdt_update(mcdt, MCDT_DMA_EN, BIT(channel), BIT(channel));
	अन्यथा
		sprd_mcdt_update(mcdt, MCDT_DMA_EN, 0, BIT(channel));
पूर्ण

अटल व्योम sprd_mcdt_ap_पूर्णांक_enable(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				    bool enable)
अणु
	अगर (enable)
		sprd_mcdt_update(mcdt, MCDT_INT_MSK_CFG0, BIT(channel),
				 BIT(channel));
	अन्यथा
		sprd_mcdt_update(mcdt, MCDT_INT_MSK_CFG0, 0, BIT(channel));
पूर्ण

अटल व्योम sprd_mcdt_dac_ग_लिखो_fअगरo(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				     u32 val)
अणु
	u32 reg = MCDT_CH0_TXD + channel * 4;

	ग_लिखोl_relaxed(val, mcdt->base + reg);
पूर्ण

अटल व्योम sprd_mcdt_adc_पढ़ो_fअगरo(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				    u32 *val)
अणु
	u32 reg = MCDT_CH0_RXD + channel * 4;

	*val = पढ़ोl_relaxed(mcdt->base + reg);
पूर्ण

अटल व्योम sprd_mcdt_dac_dma_chn_select(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
					 क्रमागत sprd_mcdt_dma_chan dma_chan)
अणु
	चयन (dma_chan) अणु
	हाल SPRD_MCDT_DMA_CH0:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH0_SEL_SHIFT,
				 MCDT_DMA_CH0_SEL_MASK);
		अवरोध;

	हाल SPRD_MCDT_DMA_CH1:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH1_SEL_SHIFT,
				 MCDT_DMA_CH1_SEL_MASK);
		अवरोध;

	हाल SPRD_MCDT_DMA_CH2:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH2_SEL_SHIFT,
				 MCDT_DMA_CH2_SEL_MASK);
		अवरोध;

	हाल SPRD_MCDT_DMA_CH3:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH3_SEL_SHIFT,
				 MCDT_DMA_CH3_SEL_MASK);
		अवरोध;

	हाल SPRD_MCDT_DMA_CH4:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH4_SEL_SHIFT,
				 MCDT_DMA_CH4_SEL_MASK);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sprd_mcdt_adc_dma_chn_select(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
					 क्रमागत sprd_mcdt_dma_chan dma_chan)
अणु
	चयन (dma_chan) अणु
	हाल SPRD_MCDT_DMA_CH0:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channel << MCDT_DMA_CH0_SEL_SHIFT,
				 MCDT_DMA_CH0_SEL_MASK);
		अवरोध;

	हाल SPRD_MCDT_DMA_CH1:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channel << MCDT_DMA_CH1_SEL_SHIFT,
				 MCDT_DMA_CH1_SEL_MASK);
		अवरोध;

	हाल SPRD_MCDT_DMA_CH2:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channel << MCDT_DMA_CH2_SEL_SHIFT,
				 MCDT_DMA_CH2_SEL_MASK);
		अवरोध;

	हाल SPRD_MCDT_DMA_CH3:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channel << MCDT_DMA_CH3_SEL_SHIFT,
				 MCDT_DMA_CH3_SEL_MASK);
		अवरोध;

	हाल SPRD_MCDT_DMA_CH4:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channel << MCDT_DMA_CH4_SEL_SHIFT,
				 MCDT_DMA_CH4_SEL_MASK);
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 sprd_mcdt_dma_ack_shअगरt(u8 channel)
अणु
	चयन (channel) अणु
	शेष:
	हाल 0:
	हाल 8:
		वापस 0;
	हाल 1:
	हाल 9:
		वापस 4;
	हाल 2:
		वापस 8;
	हाल 3:
		वापस 12;
	हाल 4:
		वापस 16;
	हाल 5:
		वापस 20;
	हाल 6:
		वापस 24;
	हाल 7:
		वापस 28;
	पूर्ण
पूर्ण

अटल व्योम sprd_mcdt_dac_dma_ack_select(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
					 क्रमागत sprd_mcdt_dma_chan dma_chan)
अणु
	u32 reg, shअगरt = sprd_mcdt_dma_ack_shअगरt(channel), ack = dma_chan;

	चयन (channel) अणु
	हाल 0 ... 7:
		reg = MCDT_DMA_CFG2;
		अवरोध;

	हाल 8 ... 9:
		reg = MCDT_DMA_CFG3;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	sprd_mcdt_update(mcdt, reg, ack << shअगरt,
			 MCDT_DMA_ACK_SEL_MASK << shअगरt);
पूर्ण

अटल व्योम sprd_mcdt_adc_dma_ack_select(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
					 क्रमागत sprd_mcdt_dma_chan dma_chan)
अणु
	u32 reg, shअगरt = sprd_mcdt_dma_ack_shअगरt(channel), ack = dma_chan;

	चयन (channel) अणु
	हाल 0 ... 7:
		reg = MCDT_DMA_CFG4;
		अवरोध;

	हाल 8 ... 9:
		reg = MCDT_DMA_CFG5;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	sprd_mcdt_update(mcdt, reg, ack << shअगरt,
			 MCDT_DMA_ACK_SEL_MASK << shअगरt);
पूर्ण

अटल bool sprd_mcdt_chan_fअगरo_sts(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				    क्रमागत sprd_mcdt_fअगरo_sts fअगरo_sts)
अणु
	u32 reg, shअगरt;

	चयन (channel) अणु
	हाल 0 ... 3:
		reg = MCDT_CH_FIFO_ST0;
		अवरोध;
	हाल 4 ... 7:
		reg = MCDT_CH_FIFO_ST1;
		अवरोध;
	हाल 8 ... 9:
		reg = MCDT_CH_FIFO_ST2;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (channel) अणु
	हाल 0:
	हाल 4:
	हाल 8:
		shअगरt = fअगरo_sts;
		अवरोध;

	हाल 1:
	हाल 5:
	हाल 9:
		shअगरt = 8 + fअगरo_sts;
		अवरोध;

	हाल 2:
	हाल 6:
		shअगरt = 16 + fअगरo_sts;
		अवरोध;

	हाल 3:
	हाल 7:
		shअगरt = 24 + fअगरo_sts;
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	वापस !!(पढ़ोl_relaxed(mcdt->base + reg) & BIT(shअगरt));
पूर्ण

अटल व्योम sprd_mcdt_dac_fअगरo_clear(काष्ठा sprd_mcdt_dev *mcdt, u8 channel)
अणु
	sprd_mcdt_update(mcdt, MCDT_FIFO_CLR, BIT(channel), BIT(channel));
पूर्ण

अटल व्योम sprd_mcdt_adc_fअगरo_clear(काष्ठा sprd_mcdt_dev *mcdt, u8 channel)
अणु
	u32 shअगरt = MCDT_ADC_FIFO_SHIFT + channel;

	sprd_mcdt_update(mcdt, MCDT_FIFO_CLR, BIT(shअगरt), BIT(shअगरt));
पूर्ण

अटल u32 sprd_mcdt_dac_fअगरo_avail(काष्ठा sprd_mcdt_dev *mcdt, u8 channel)
अणु
	u32 reg = MCDT_DAC0_FIFO_ADDR_ST + channel * 8;
	u32 r_addr = (पढ़ोl_relaxed(mcdt->base + reg) >>
		      MCDT_CH_FIFO_ADDR_SHIFT) & MCDT_CH_FIFO_ADDR_MASK;
	u32 w_addr = पढ़ोl_relaxed(mcdt->base + reg) & MCDT_CH_FIFO_ADDR_MASK;

	अगर (w_addr >= r_addr)
		वापस 4 * (MCDT_FIFO_LENGTH - w_addr + r_addr);
	अन्यथा
		वापस 4 * (r_addr - w_addr);
पूर्ण

अटल u32 sprd_mcdt_adc_fअगरo_avail(काष्ठा sprd_mcdt_dev *mcdt, u8 channel)
अणु
	u32 reg = MCDT_ADC0_FIFO_ADDR_ST + channel * 8;
	u32 r_addr = (पढ़ोl_relaxed(mcdt->base + reg) >>
		      MCDT_CH_FIFO_ADDR_SHIFT) & MCDT_CH_FIFO_ADDR_MASK;
	u32 w_addr = पढ़ोl_relaxed(mcdt->base + reg) & MCDT_CH_FIFO_ADDR_MASK;

	अगर (w_addr >= r_addr)
		वापस 4 * (w_addr - r_addr);
	अन्यथा
		वापस 4 * (MCDT_FIFO_LENGTH - r_addr + w_addr);
पूर्ण

अटल u32 sprd_mcdt_पूर्णांक_type_shअगरt(u8 channel,
				    क्रमागत sprd_mcdt_fअगरo_पूर्णांक पूर्णांक_type)
अणु
	चयन (channel) अणु
	हाल 0:
	हाल 4:
	हाल 8:
		वापस पूर्णांक_type;

	हाल 1:
	हाल 5:
	हाल 9:
		वापस  8 + पूर्णांक_type;

	हाल 2:
	हाल 6:
		वापस 16 + पूर्णांक_type;

	हाल 3:
	हाल 7:
		वापस 24 + पूर्णांक_type;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम sprd_mcdt_chan_पूर्णांक_en(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				  क्रमागत sprd_mcdt_fअगरo_पूर्णांक पूर्णांक_type, bool enable)
अणु
	u32 reg, shअगरt = sprd_mcdt_पूर्णांक_type_shअगरt(channel, पूर्णांक_type);

	चयन (channel) अणु
	हाल 0 ... 3:
		reg = MCDT_INT_EN0;
		अवरोध;
	हाल 4 ... 7:
		reg = MCDT_INT_EN1;
		अवरोध;
	हाल 8 ... 9:
		reg = MCDT_INT_EN2;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (enable)
		sprd_mcdt_update(mcdt, reg, BIT(shअगरt), BIT(shअगरt));
	अन्यथा
		sprd_mcdt_update(mcdt, reg, 0, BIT(shअगरt));
पूर्ण

अटल व्योम sprd_mcdt_chan_पूर्णांक_clear(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				     क्रमागत sprd_mcdt_fअगरo_पूर्णांक पूर्णांक_type)
अणु
	u32 reg, shअगरt = sprd_mcdt_पूर्णांक_type_shअगरt(channel, पूर्णांक_type);

	चयन (channel) अणु
	हाल 0 ... 3:
		reg = MCDT_INT_CLR0;
		अवरोध;
	हाल 4 ... 7:
		reg = MCDT_INT_CLR1;
		अवरोध;
	हाल 8 ... 9:
		reg = MCDT_INT_CLR2;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	sprd_mcdt_update(mcdt, reg, BIT(shअगरt), BIT(shअगरt));
पूर्ण

अटल bool sprd_mcdt_chan_पूर्णांक_sts(काष्ठा sprd_mcdt_dev *mcdt, u8 channel,
				   क्रमागत sprd_mcdt_fअगरo_पूर्णांक पूर्णांक_type)
अणु
	u32 reg, shअगरt = sprd_mcdt_पूर्णांक_type_shअगरt(channel, पूर्णांक_type);

	चयन (channel) अणु
	हाल 0 ... 3:
		reg = MCDT_INT_MSK1;
		अवरोध;
	हाल 4 ... 7:
		reg = MCDT_INT_MSK2;
		अवरोध;
	हाल 8 ... 9:
		reg = MCDT_INT_MSK3;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस !!(पढ़ोl_relaxed(mcdt->base + reg) & BIT(shअगरt));
पूर्ण

अटल irqवापस_t sprd_mcdt_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sprd_mcdt_dev *mcdt = (काष्ठा sprd_mcdt_dev *)dev_id;
	पूर्णांक i;

	spin_lock(&mcdt->lock);

	क्रम (i = 0; i < MCDT_ADC_CHANNEL_NUM; i++) अणु
		अगर (sprd_mcdt_chan_पूर्णांक_sts(mcdt, i, MCDT_ADC_FIFO_AF_INT)) अणु
			काष्ठा sprd_mcdt_chan *chan = &mcdt->chan[i];

			sprd_mcdt_chan_पूर्णांक_clear(mcdt, i, MCDT_ADC_FIFO_AF_INT);
			अगर (chan->cb)
				chan->cb->notअगरy(chan->cb->data);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MCDT_DAC_CHANNEL_NUM; i++) अणु
		अगर (sprd_mcdt_chan_पूर्णांक_sts(mcdt, i, MCDT_DAC_FIFO_AE_INT)) अणु
			काष्ठा sprd_mcdt_chan *chan =
				&mcdt->chan[i + MCDT_ADC_CHANNEL_NUM];

			sprd_mcdt_chan_पूर्णांक_clear(mcdt, i, MCDT_DAC_FIFO_AE_INT);
			अगर (chan->cb)
				chan->cb->notअगरy(chan->cb->data);
		पूर्ण
	पूर्ण

	spin_unlock(&mcdt->lock);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * sprd_mcdt_chan_ग_लिखो - ग_लिखो data to the MCDT channel's fअगरo
 * @chan: the MCDT channel
 * @tx_buf: send buffer
 * @size: data size
 *
 * Note: We can not ग_लिखो data to the channel fअगरo when enabling the DMA mode,
 * otherwise the channel fअगरo data will be invalid.
 *
 * If there are not enough space of the channel fअगरo, it will वापस errors
 * to users.
 *
 * Returns 0 on success, or an appropriate error code on failure.
 */
पूर्णांक sprd_mcdt_chan_ग_लिखो(काष्ठा sprd_mcdt_chan *chan, अक्षर *tx_buf, u32 size)
अणु
	काष्ठा sprd_mcdt_dev *mcdt = chan->mcdt;
	अचिन्हित दीर्घ flags;
	पूर्णांक avail, i = 0, words = size / 4;
	u32 *buf = (u32 *)tx_buf;

	spin_lock_irqsave(&mcdt->lock, flags);

	अगर (chan->dma_enable) अणु
		dev_err(mcdt->dev,
			"Can not write data when DMA mode enabled\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस -EINVAL;
	पूर्ण

	अगर (sprd_mcdt_chan_fअगरo_sts(mcdt, chan->id, MCDT_DAC_FIFO_REAL_FULL)) अणु
		dev_err(mcdt->dev, "Channel fifo is full now\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस -EBUSY;
	पूर्ण

	avail = sprd_mcdt_dac_fअगरo_avail(mcdt, chan->id);
	अगर (size > avail) अणु
		dev_err(mcdt->dev,
			"Data size is larger than the available fifo size\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस -EBUSY;
	पूर्ण

	जबतक (i++ < words)
		sprd_mcdt_dac_ग_लिखो_fअगरo(mcdt, chan->id, *buf++);

	spin_unlock_irqrestore(&mcdt->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mcdt_chan_ग_लिखो);

/**
 * sprd_mcdt_chan_पढ़ो - पढ़ो data from the MCDT channel's fअगरo
 * @chan: the MCDT channel
 * @rx_buf: receive buffer
 * @size: data size
 *
 * Note: We can not पढ़ो data from the channel fअगरo when enabling the DMA mode,
 * otherwise the पढ़ोing data will be invalid.
 *
 * Usually user need start to पढ़ो data once receiving the fअगरo full पूर्णांकerrupt.
 *
 * Returns data size of पढ़ोing successfully, or an error code on failure.
 */
पूर्णांक sprd_mcdt_chan_पढ़ो(काष्ठा sprd_mcdt_chan *chan, अक्षर *rx_buf, u32 size)
अणु
	काष्ठा sprd_mcdt_dev *mcdt = chan->mcdt;
	अचिन्हित दीर्घ flags;
	पूर्णांक i = 0, avail, words = size / 4;
	u32 *buf = (u32 *)rx_buf;

	spin_lock_irqsave(&mcdt->lock, flags);

	अगर (chan->dma_enable) अणु
		dev_err(mcdt->dev, "Can not read data when DMA mode enabled\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस -EINVAL;
	पूर्ण

	अगर (sprd_mcdt_chan_fअगरo_sts(mcdt, chan->id, MCDT_ADC_FIFO_REAL_EMPTY)) अणु
		dev_err(mcdt->dev, "Channel fifo is empty\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस -EBUSY;
	पूर्ण

	avail = sprd_mcdt_adc_fअगरo_avail(mcdt, chan->id);
	अगर (size > avail)
		words = avail / 4;

	जबतक (i++ < words)
		sprd_mcdt_adc_पढ़ो_fअगरo(mcdt, chan->id, buf++);

	spin_unlock_irqrestore(&mcdt->lock, flags);
	वापस words * 4;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mcdt_chan_पढ़ो);

/**
 * sprd_mcdt_chan_पूर्णांक_enable - enable the पूर्णांकerrupt mode क्रम the MCDT channel
 * @chan: the MCDT channel
 * @water_mark: water mark to trigger a पूर्णांकerrupt
 * @cb: callback when a पूर्णांकerrupt happened
 *
 * Now it only can enable fअगरo almost full पूर्णांकerrupt क्रम ADC channel and fअगरo
 * almost empty पूर्णांकerrupt क्रम DAC channel. Morevoer क्रम पूर्णांकerrupt mode, user
 * should use sprd_mcdt_chan_पढ़ो() or sprd_mcdt_chan_ग_लिखो() to पढ़ो or ग_लिखो
 * data manually.
 *
 * For ADC channel, user can start to पढ़ो data once receiving one fअगरo full
 * पूर्णांकerrupt. For DAC channel, user can start to ग_लिखो data once receiving one
 * fअगरo empty पूर्णांकerrupt or just call sprd_mcdt_chan_ग_लिखो() to ग_लिखो data
 * directly.
 *
 * Returns 0 on success, or an error code on failure.
 */
पूर्णांक sprd_mcdt_chan_पूर्णांक_enable(काष्ठा sprd_mcdt_chan *chan, u32 water_mark,
			      काष्ठा sprd_mcdt_chan_callback *cb)
अणु
	काष्ठा sprd_mcdt_dev *mcdt = chan->mcdt;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&mcdt->lock, flags);

	अगर (chan->dma_enable || chan->पूर्णांक_enable) अणु
		dev_err(mcdt->dev, "Failed to set interrupt mode.\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस -EINVAL;
	पूर्ण

	चयन (chan->type) अणु
	हाल SPRD_MCDT_ADC_CHAN:
		sprd_mcdt_adc_fअगरo_clear(mcdt, chan->id);
		sprd_mcdt_adc_set_watermark(mcdt, chan->id, water_mark,
					    MCDT_FIFO_LENGTH - 1);
		sprd_mcdt_chan_पूर्णांक_en(mcdt, chan->id,
				      MCDT_ADC_FIFO_AF_INT, true);
		sprd_mcdt_ap_पूर्णांक_enable(mcdt, chan->id, true);
		अवरोध;

	हाल SPRD_MCDT_DAC_CHAN:
		sprd_mcdt_dac_fअगरo_clear(mcdt, chan->id);
		sprd_mcdt_dac_set_watermark(mcdt, chan->id,
					    MCDT_FIFO_LENGTH - 1, water_mark);
		sprd_mcdt_chan_पूर्णांक_en(mcdt, chan->id,
				      MCDT_DAC_FIFO_AE_INT, true);
		sprd_mcdt_ap_पूर्णांक_enable(mcdt, chan->id, true);
		अवरोध;

	शेष:
		dev_err(mcdt->dev, "Unsupported channel type\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!ret) अणु
		chan->cb = cb;
		chan->पूर्णांक_enable = true;
	पूर्ण

	spin_unlock_irqrestore(&mcdt->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mcdt_chan_पूर्णांक_enable);

/**
 * sprd_mcdt_chan_पूर्णांक_disable - disable the पूर्णांकerrupt mode क्रम the MCDT channel
 * @chan: the MCDT channel
 */
व्योम sprd_mcdt_chan_पूर्णांक_disable(काष्ठा sprd_mcdt_chan *chan)
अणु
	काष्ठा sprd_mcdt_dev *mcdt = chan->mcdt;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mcdt->lock, flags);

	अगर (!chan->पूर्णांक_enable) अणु
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस;
	पूर्ण

	चयन (chan->type) अणु
	हाल SPRD_MCDT_ADC_CHAN:
		sprd_mcdt_chan_पूर्णांक_en(mcdt, chan->id,
				      MCDT_ADC_FIFO_AF_INT, false);
		sprd_mcdt_chan_पूर्णांक_clear(mcdt, chan->id, MCDT_ADC_FIFO_AF_INT);
		sprd_mcdt_ap_पूर्णांक_enable(mcdt, chan->id, false);
		अवरोध;

	हाल SPRD_MCDT_DAC_CHAN:
		sprd_mcdt_chan_पूर्णांक_en(mcdt, chan->id,
				      MCDT_DAC_FIFO_AE_INT, false);
		sprd_mcdt_chan_पूर्णांक_clear(mcdt, chan->id, MCDT_DAC_FIFO_AE_INT);
		sprd_mcdt_ap_पूर्णांक_enable(mcdt, chan->id, false);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	chan->पूर्णांक_enable = false;
	spin_unlock_irqrestore(&mcdt->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mcdt_chan_पूर्णांक_disable);

/**
 * sprd_mcdt_chan_dma_enable - enable the DMA mode क्रम the MCDT channel
 * @chan: the MCDT channel
 * @dma_chan: specअगरy which DMA channel will be used क्रम this MCDT channel
 * @water_mark: water mark to trigger a DMA request
 *
 * Enable the DMA mode क्रम the MCDT channel, that means we can use DMA to
 * transfer data to the channel fअगरo and करो not need पढ़ोing/writing data
 * manually.
 *
 * Returns 0 on success, or an error code on failure.
 */
पूर्णांक sprd_mcdt_chan_dma_enable(काष्ठा sprd_mcdt_chan *chan,
			      क्रमागत sprd_mcdt_dma_chan dma_chan,
			      u32 water_mark)
अणु
	काष्ठा sprd_mcdt_dev *mcdt = chan->mcdt;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&mcdt->lock, flags);

	अगर (chan->dma_enable || chan->पूर्णांक_enable ||
	    dma_chan > SPRD_MCDT_DMA_CH4) अणु
		dev_err(mcdt->dev, "Failed to set DMA mode\n");
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस -EINVAL;
	पूर्ण

	चयन (chan->type) अणु
	हाल SPRD_MCDT_ADC_CHAN:
		sprd_mcdt_adc_fअगरo_clear(mcdt, chan->id);
		sprd_mcdt_adc_set_watermark(mcdt, chan->id,
					    water_mark, MCDT_FIFO_LENGTH - 1);
		sprd_mcdt_adc_dma_enable(mcdt, chan->id, true);
		sprd_mcdt_adc_dma_chn_select(mcdt, chan->id, dma_chan);
		sprd_mcdt_adc_dma_ack_select(mcdt, chan->id, dma_chan);
		अवरोध;

	हाल SPRD_MCDT_DAC_CHAN:
		sprd_mcdt_dac_fअगरo_clear(mcdt, chan->id);
		sprd_mcdt_dac_set_watermark(mcdt, chan->id,
					    MCDT_FIFO_LENGTH - 1, water_mark);
		sprd_mcdt_dac_dma_enable(mcdt, chan->id, true);
		sprd_mcdt_dac_dma_chn_select(mcdt, chan->id, dma_chan);
		sprd_mcdt_dac_dma_ack_select(mcdt, chan->id, dma_chan);
		अवरोध;

	शेष:
		dev_err(mcdt->dev, "Unsupported channel type\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!ret)
		chan->dma_enable = true;

	spin_unlock_irqrestore(&mcdt->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mcdt_chan_dma_enable);

/**
 * sprd_mcdt_chan_dma_disable - disable the DMA mode क्रम the MCDT channel
 * @chan: the MCDT channel
 */
व्योम sprd_mcdt_chan_dma_disable(काष्ठा sprd_mcdt_chan *chan)
अणु
	काष्ठा sprd_mcdt_dev *mcdt = chan->mcdt;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mcdt->lock, flags);

	अगर (!chan->dma_enable) अणु
		spin_unlock_irqrestore(&mcdt->lock, flags);
		वापस;
	पूर्ण

	चयन (chan->type) अणु
	हाल SPRD_MCDT_ADC_CHAN:
		sprd_mcdt_adc_dma_enable(mcdt, chan->id, false);
		sprd_mcdt_adc_fअगरo_clear(mcdt, chan->id);
		अवरोध;

	हाल SPRD_MCDT_DAC_CHAN:
		sprd_mcdt_dac_dma_enable(mcdt, chan->id, false);
		sprd_mcdt_dac_fअगरo_clear(mcdt, chan->id);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	chan->dma_enable = false;
	spin_unlock_irqrestore(&mcdt->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mcdt_chan_dma_disable);

/**
 * sprd_mcdt_request_chan - request one MCDT channel
 * @channel: channel id
 * @type: channel type, it can be one ADC channel or DAC channel
 *
 * Rवापस शून्य अगर no available channel.
 */
काष्ठा sprd_mcdt_chan *sprd_mcdt_request_chan(u8 channel,
					      क्रमागत sprd_mcdt_channel_type type)
अणु
	काष्ठा sprd_mcdt_chan *temp;

	mutex_lock(&sprd_mcdt_list_mutex);

	list_क्रम_each_entry(temp, &sprd_mcdt_chan_list, list) अणु
		अगर (temp->type == type && temp->id == channel) अणु
			list_del_init(&temp->list);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (list_entry_is_head(temp, &sprd_mcdt_chan_list, list))
		temp = शून्य;

	mutex_unlock(&sprd_mcdt_list_mutex);

	वापस temp;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mcdt_request_chan);

/**
 * sprd_mcdt_मुक्त_chan - मुक्त one MCDT channel
 * @chan: the channel to be मुक्तd
 */
व्योम sprd_mcdt_मुक्त_chan(काष्ठा sprd_mcdt_chan *chan)
अणु
	काष्ठा sprd_mcdt_chan *temp;

	sprd_mcdt_chan_dma_disable(chan);
	sprd_mcdt_chan_पूर्णांक_disable(chan);

	mutex_lock(&sprd_mcdt_list_mutex);

	list_क्रम_each_entry(temp, &sprd_mcdt_chan_list, list) अणु
		अगर (temp == chan) अणु
			mutex_unlock(&sprd_mcdt_list_mutex);
			वापस;
		पूर्ण
	पूर्ण

	list_add_tail(&chan->list, &sprd_mcdt_chan_list);
	mutex_unlock(&sprd_mcdt_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(sprd_mcdt_मुक्त_chan);

अटल व्योम sprd_mcdt_init_chans(काष्ठा sprd_mcdt_dev *mcdt,
				 काष्ठा resource *res)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MCDT_CHANNEL_NUM; i++) अणु
		काष्ठा sprd_mcdt_chan *chan = &mcdt->chan[i];

		अगर (i < MCDT_ADC_CHANNEL_NUM) अणु
			chan->id = i;
			chan->type = SPRD_MCDT_ADC_CHAN;
			chan->fअगरo_phys = res->start + MCDT_CH0_RXD + i * 4;
		पूर्ण अन्यथा अणु
			chan->id = i - MCDT_ADC_CHANNEL_NUM;
			chan->type = SPRD_MCDT_DAC_CHAN;
			chan->fअगरo_phys = res->start + MCDT_CH0_TXD +
				(i - MCDT_ADC_CHANNEL_NUM) * 4;
		पूर्ण

		chan->mcdt = mcdt;
		INIT_LIST_HEAD(&chan->list);

		mutex_lock(&sprd_mcdt_list_mutex);
		list_add_tail(&chan->list, &sprd_mcdt_chan_list);
		mutex_unlock(&sprd_mcdt_list_mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_mcdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_mcdt_dev *mcdt;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	mcdt = devm_kzalloc(&pdev->dev, माप(*mcdt), GFP_KERNEL);
	अगर (!mcdt)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mcdt->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mcdt->base))
		वापस PTR_ERR(mcdt->base);

	mcdt->dev = &pdev->dev;
	spin_lock_init(&mcdt->lock);
	platक्रमm_set_drvdata(pdev, mcdt);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, sprd_mcdt_irq_handler,
			       0, "sprd-mcdt", mcdt);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request MCDT IRQ\n");
		वापस ret;
	पूर्ण

	sprd_mcdt_init_chans(mcdt, res);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_mcdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_mcdt_chan *chan, *temp;

	mutex_lock(&sprd_mcdt_list_mutex);

	list_क्रम_each_entry_safe(chan, temp, &sprd_mcdt_chan_list, list)
		list_del(&chan->list);

	mutex_unlock(&sprd_mcdt_list_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_mcdt_of_match[] = अणु
	अणु .compatible = "sprd,sc9860-mcdt", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_mcdt_of_match);

अटल काष्ठा platक्रमm_driver sprd_mcdt_driver = अणु
	.probe = sprd_mcdt_probe,
	.हटाओ = sprd_mcdt_हटाओ,
	.driver = अणु
		.name = "sprd-mcdt",
		.of_match_table = sprd_mcdt_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sprd_mcdt_driver);

MODULE_DESCRIPTION("Spreadtrum Multi-Channel Data Transfer Driver");
MODULE_LICENSE("GPL v2");

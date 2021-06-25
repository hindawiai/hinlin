<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// linux/sound/soc/bcm/bcm63xx-i2s.h
// Copyright (c) 2020 Broadcom Corporation
// Author: Kevin-Ke Li <kevin-ke.li@broadcom.com>

#अगर_अघोषित __BCM63XX_I2S_H
#घोषणा __BCM63XX_I2S_H

#घोषणा I2S_DESC_FIFO_DEPTH		8
#घोषणा I2S_MISC_CFG			(0x003C)
#घोषणा I2S_PAD_LVL_LOOP_DIS_MASK	(1 << 2)
#घोषणा I2S_PAD_LVL_LOOP_DIS_ENABLE	I2S_PAD_LVL_LOOP_DIS_MASK

#घोषणा I2S_TX_ENABLE_MASK		(1 << 31)
#घोषणा I2S_TX_ENABLE			I2S_TX_ENABLE_MASK
#घोषणा I2S_TX_OUT_R			(1 << 19)
#घोषणा I2S_TX_DATA_ALIGNMENT		(1 << 2)
#घोषणा I2S_TX_DATA_ENABLE		(1 << 1)
#घोषणा I2S_TX_CLOCK_ENABLE		(1 << 0)

#घोषणा I2S_TX_DESC_OFF_LEVEL_SHIFT	12
#घोषणा I2S_TX_DESC_OFF_LEVEL_MASK	(0x0F << I2S_TX_DESC_OFF_LEVEL_SHIFT)
#घोषणा I2S_TX_DESC_IFF_LEVEL_SHIFT	8
#घोषणा I2S_TX_DESC_IFF_LEVEL_MASK	(0x0F << I2S_TX_DESC_IFF_LEVEL_SHIFT)
#घोषणा I2S_TX_DESC_OFF_INTR_EN_MSK	(1 << 1)
#घोषणा I2S_TX_DESC_OFF_INTR_EN	I2S_TX_DESC_OFF_INTR_EN_MSK

#घोषणा I2S_TX_CFG			(0x0000)
#घोषणा I2S_TX_IRQ_CTL			(0x0004)
#घोषणा I2S_TX_IRQ_EN			(0x0008)
#घोषणा I2S_TX_IRQ_IFF_THLD		(0x000c)
#घोषणा I2S_TX_IRQ_OFF_THLD		(0x0010)
#घोषणा I2S_TX_DESC_IFF_ADDR		(0x0014)
#घोषणा I2S_TX_DESC_IFF_LEN		(0x0018)
#घोषणा I2S_TX_DESC_OFF_ADDR		(0x001C)
#घोषणा I2S_TX_DESC_OFF_LEN		(0x0020)
#घोषणा I2S_TX_CFG_2			(0x0024)
#घोषणा I2S_TX_SLAVE_MODE_SHIFT	13
#घोषणा I2S_TX_SLAVE_MODE_MASK		(1 << I2S_TX_SLAVE_MODE_SHIFT)
#घोषणा I2S_TX_SLAVE_MODE		I2S_TX_SLAVE_MODE_MASK
#घोषणा I2S_TX_MASTER_MODE		0
#घोषणा I2S_TX_INTR_MASK		0x0F

#घोषणा I2S_RX_ENABLE_MASK		(1 << 31)
#घोषणा I2S_RX_ENABLE			I2S_RX_ENABLE_MASK
#घोषणा I2S_RX_IN_R			(1 << 19)
#घोषणा I2S_RX_DATA_ALIGNMENT		(1 << 2)
#घोषणा I2S_RX_CLOCK_ENABLE		(1 << 0)

#घोषणा I2S_RX_DESC_OFF_LEVEL_SHIFT	12
#घोषणा I2S_RX_DESC_OFF_LEVEL_MASK	(0x0F << I2S_RX_DESC_OFF_LEVEL_SHIFT)
#घोषणा I2S_RX_DESC_IFF_LEVEL_SHIFT	8
#घोषणा I2S_RX_DESC_IFF_LEVEL_MASK	(0x0F << I2S_RX_DESC_IFF_LEVEL_SHIFT)
#घोषणा I2S_RX_DESC_OFF_INTR_EN_MSK	(1 << 1)
#घोषणा I2S_RX_DESC_OFF_INTR_EN	I2S_RX_DESC_OFF_INTR_EN_MSK

#घोषणा I2S_RX_CFG			(0x0040) /* 20c0 */
#घोषणा I2S_RX_IRQ_CTL			(0x0044)
#घोषणा I2S_RX_IRQ_EN			(0x0048)
#घोषणा I2S_RX_IRQ_IFF_THLD		(0x004C)
#घोषणा I2S_RX_IRQ_OFF_THLD		(0x0050)
#घोषणा I2S_RX_DESC_IFF_ADDR		(0x0054)
#घोषणा I2S_RX_DESC_IFF_LEN		(0x0058)
#घोषणा I2S_RX_DESC_OFF_ADDR		(0x005C)
#घोषणा I2S_RX_DESC_OFF_LEN		(0x0060)
#घोषणा I2S_RX_CFG_2			(0x0064)
#घोषणा I2S_RX_SLAVE_MODE_SHIFT	13
#घोषणा I2S_RX_SLAVE_MODE_MASK		(1 << I2S_RX_SLAVE_MODE_SHIFT)
#घोषणा I2S_RX_SLAVE_MODE		I2S_RX_SLAVE_MODE_MASK
#घोषणा I2S_RX_MASTER_MODE		0
#घोषणा I2S_RX_INTR_MASK		0x0F

#घोषणा I2S_REG_MAX			0x007C

काष्ठा bcm_i2s_priv अणु
	काष्ठा device *dev;
	काष्ठा resource *r_irq;
	काष्ठा regmap *regmap_i2s;
	काष्ठा clk *i2s_clk;
	काष्ठा snd_pcm_substream	*play_substream;
	काष्ठा snd_pcm_substream	*capture_substream;
	काष्ठा i2s_dma_desc *play_dma_desc;
	काष्ठा i2s_dma_desc *capture_dma_desc;
पूर्ण;

बाह्य पूर्णांक bcm63xx_soc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev,
				      काष्ठा bcm_i2s_priv *i2s_priv);
बाह्य पूर्णांक bcm63xx_soc_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर

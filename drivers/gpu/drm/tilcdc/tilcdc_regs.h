<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Texas Instruments
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __TILCDC_REGS_H__
#घोषणा __TILCDC_REGS_H__

/* LCDC रेजिस्टर definitions, based on da8xx-fb */

#समावेश <linux/bitops.h>

#समावेश "tilcdc_drv.h"

/* LCDC Status Register */
#घोषणा LCDC_END_OF_FRAME1                       BIT(9)
#घोषणा LCDC_END_OF_FRAME0                       BIT(8)
#घोषणा LCDC_PL_LOAD_DONE                        BIT(6)
#घोषणा LCDC_FIFO_UNDERFLOW                      BIT(5)
#घोषणा LCDC_SYNC_LOST                           BIT(2)
#घोषणा LCDC_FRAME_DONE                          BIT(0)

/* LCDC DMA Control Register */
#घोषणा LCDC_DMA_BURST_SIZE(x)                   ((x) << 4)
#घोषणा LCDC_DMA_BURST_SIZE_MASK                 ((0x7) << 4)
#घोषणा LCDC_DMA_BURST_1                         0x0
#घोषणा LCDC_DMA_BURST_2                         0x1
#घोषणा LCDC_DMA_BURST_4                         0x2
#घोषणा LCDC_DMA_BURST_8                         0x3
#घोषणा LCDC_DMA_BURST_16                        0x4
#घोषणा LCDC_DMA_FIFO_THRESHOLD(x)               ((x) << 8)
#घोषणा LCDC_DMA_FIFO_THRESHOLD_MASK             ((0x3) << 8)
#घोषणा LCDC_V1_END_OF_FRAME_INT_ENA             BIT(2)
#घोषणा LCDC_V2_END_OF_FRAME0_INT_ENA            BIT(8)
#घोषणा LCDC_V2_END_OF_FRAME1_INT_ENA            BIT(9)
#घोषणा LCDC_DUAL_FRAME_BUFFER_ENABLE            BIT(0)

/* LCDC Control Register */
#घोषणा LCDC_CLK_DIVISOR(x)                      ((x) << 8)
#घोषणा LCDC_CLK_DIVISOR_MASK                    ((0xFF) << 8)
#घोषणा LCDC_RASTER_MODE                         0x01

/* LCDC Raster Control Register */
#घोषणा LCDC_PALETTE_LOAD_MODE(x)                ((x) << 20)
#घोषणा LCDC_PALETTE_LOAD_MODE_MASK              ((0x3) << 20)
#घोषणा PALETTE_AND_DATA                         0x00
#घोषणा PALETTE_ONLY                             0x01
#घोषणा DATA_ONLY                                0x02

#घोषणा LCDC_MONO_8BIT_MODE                      BIT(9)
#घोषणा LCDC_RASTER_ORDER                        BIT(8)
#घोषणा LCDC_TFT_MODE                            BIT(7)
#घोषणा LCDC_V1_UNDERFLOW_INT_ENA                BIT(6)
#घोषणा LCDC_V2_UNDERFLOW_INT_ENA                BIT(5)
#घोषणा LCDC_V1_PL_INT_ENA                       BIT(4)
#घोषणा LCDC_V2_PL_INT_ENA                       BIT(6)
#घोषणा LCDC_V1_SYNC_LOST_INT_ENA                BIT(5)
#घोषणा LCDC_V1_FRAME_DONE_INT_ENA               BIT(3)
#घोषणा LCDC_MONOCHROME_MODE                     BIT(1)
#घोषणा LCDC_RASTER_ENABLE                       BIT(0)
#घोषणा LCDC_TFT_ALT_ENABLE                      BIT(23)
#घोषणा LCDC_STN_565_ENABLE                      BIT(24)
#घोषणा LCDC_V2_DMA_CLK_EN                       BIT(2)
#घोषणा LCDC_V2_LIDD_CLK_EN                      BIT(1)
#घोषणा LCDC_V2_CORE_CLK_EN                      BIT(0)
#घोषणा LCDC_V2_LPP_B10                          26
#घोषणा LCDC_V2_TFT_24BPP_MODE                   BIT(25)
#घोषणा LCDC_V2_TFT_24BPP_UNPACK                 BIT(26)

/* LCDC Raster Timing 2 Register */
#घोषणा LCDC_AC_BIAS_TRANSITIONS_PER_INT(x)      ((x) << 16)
#घोषणा LCDC_AC_BIAS_TRANSITIONS_PER_INT_MASK    ((0xF) << 16)
#घोषणा LCDC_AC_BIAS_FREQUENCY(x)                ((x) << 8)
#घोषणा LCDC_AC_BIAS_FREQUENCY_MASK              ((0xFF) << 8)
#घोषणा LCDC_SYNC_CTRL                           BIT(25)
#घोषणा LCDC_SYNC_EDGE                           BIT(24)
#घोषणा LCDC_INVERT_PIXEL_CLOCK                  BIT(22)
#घोषणा LCDC_INVERT_HSYNC                        BIT(21)
#घोषणा LCDC_INVERT_VSYNC                        BIT(20)
#घोषणा LCDC_LPP_B10                             BIT(26)

/* LCDC Block */
#घोषणा LCDC_PID_REG                             0x0
#घोषणा LCDC_CTRL_REG                            0x4
#घोषणा LCDC_STAT_REG                            0x8
#घोषणा LCDC_RASTER_CTRL_REG                     0x28
#घोषणा LCDC_RASTER_TIMING_0_REG                 0x2c
#घोषणा LCDC_RASTER_TIMING_1_REG                 0x30
#घोषणा LCDC_RASTER_TIMING_2_REG                 0x34
#घोषणा LCDC_DMA_CTRL_REG                        0x40
#घोषणा LCDC_DMA_FB_BASE_ADDR_0_REG              0x44
#घोषणा LCDC_DMA_FB_CEILING_ADDR_0_REG           0x48
#घोषणा LCDC_DMA_FB_BASE_ADDR_1_REG              0x4c
#घोषणा LCDC_DMA_FB_CEILING_ADDR_1_REG           0x50

/* Interrupt Registers available only in Version 2 */
#घोषणा LCDC_RAW_STAT_REG                        0x58
#घोषणा LCDC_MASKED_STAT_REG                     0x5c
#घोषणा LCDC_INT_ENABLE_SET_REG                  0x60
#घोषणा LCDC_INT_ENABLE_CLR_REG                  0x64
#घोषणा LCDC_END_OF_INT_IND_REG                  0x68

/* Clock रेजिस्टरs available only on Version 2 */
#घोषणा LCDC_CLK_ENABLE_REG                      0x6c
#घोषणा LCDC_CLK_RESET_REG                       0x70
#घोषणा LCDC_CLK_MAIN_RESET                      BIT(3)


/*
 * Helpers:
 */

अटल अंतरभूत व्योम tilcdc_ग_लिखो(काष्ठा drm_device *dev, u32 reg, u32 data)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	ioग_लिखो32(data, priv->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम tilcdc_ग_लिखो64(काष्ठा drm_device *dev, u32 reg, u64 data)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	अस्थिर व्योम __iomem *addr = priv->mmio + reg;

#अगर defined(ioग_लिखो64) && !defined(ioग_लिखो64_is_nonatomic)
	ioग_लिखो64(data, addr);
#अन्यथा
	__iowmb();
	/* This compiles to strd (=64-bit ग_लिखो) on ARM7 */
	*(अस्थिर u64 __क्रमce *)addr = __cpu_to_le64(data);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 tilcdc_पढ़ो(काष्ठा drm_device *dev, u32 reg)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	वापस ioपढ़ो32(priv->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम tilcdc_ग_लिखो_mask(काष्ठा drm_device *dev, u32 reg,
				     u32 val, u32 mask)
अणु
	tilcdc_ग_लिखो(dev, reg, (tilcdc_पढ़ो(dev, reg) & ~mask) | (val & mask));
पूर्ण

अटल अंतरभूत व्योम tilcdc_set(काष्ठा drm_device *dev, u32 reg, u32 mask)
अणु
	tilcdc_ग_लिखो(dev, reg, tilcdc_पढ़ो(dev, reg) | mask);
पूर्ण

अटल अंतरभूत व्योम tilcdc_clear(काष्ठा drm_device *dev, u32 reg, u32 mask)
अणु
	tilcdc_ग_लिखो(dev, reg, tilcdc_पढ़ो(dev, reg) & ~mask);
पूर्ण

/* the रेजिस्टर to पढ़ो/clear irqstatus dअगरfers between v1 and v2 of the IP */
अटल अंतरभूत u32 tilcdc_irqstatus_reg(काष्ठा drm_device *dev)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	वापस (priv->rev == 2) ? LCDC_MASKED_STAT_REG : LCDC_STAT_REG;
पूर्ण

अटल अंतरभूत u32 tilcdc_पढ़ो_irqstatus(काष्ठा drm_device *dev)
अणु
	वापस tilcdc_पढ़ो(dev, tilcdc_irqstatus_reg(dev));
पूर्ण

अटल अंतरभूत व्योम tilcdc_clear_irqstatus(काष्ठा drm_device *dev, u32 mask)
अणु
	tilcdc_ग_लिखो(dev, tilcdc_irqstatus_reg(dev), mask);
पूर्ण

#पूर्ण_अगर /* __TILCDC_REGS_H__ */

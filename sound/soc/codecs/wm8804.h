<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8804.h  --  WM8804 S/PDIF transceiver driver
 *
 * Copyright 2010 Wolfson Microelectronics plc
 *
 * Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित _WM8804_H
#घोषणा _WM8804_H

#समावेश <linux/regmap.h>

/*
 * Register values.
 */
#घोषणा WM8804_RST_DEVID1			0x00
#घोषणा WM8804_DEVID2				0x01
#घोषणा WM8804_DEVREV				0x02
#घोषणा WM8804_PLL1				0x03
#घोषणा WM8804_PLL2				0x04
#घोषणा WM8804_PLL3				0x05
#घोषणा WM8804_PLL4				0x06
#घोषणा WM8804_PLL5				0x07
#घोषणा WM8804_PLL6				0x08
#घोषणा WM8804_SPDMODE				0x09
#घोषणा WM8804_INTMASK				0x0A
#घोषणा WM8804_INTSTAT				0x0B
#घोषणा WM8804_SPDSTAT				0x0C
#घोषणा WM8804_RXCHAN1				0x0D
#घोषणा WM8804_RXCHAN2				0x0E
#घोषणा WM8804_RXCHAN3				0x0F
#घोषणा WM8804_RXCHAN4				0x10
#घोषणा WM8804_RXCHAN5				0x11
#घोषणा WM8804_SPDTX1				0x12
#घोषणा WM8804_SPDTX2				0x13
#घोषणा WM8804_SPDTX3				0x14
#घोषणा WM8804_SPDTX4				0x15
#घोषणा WM8804_SPDTX5				0x16
#घोषणा WM8804_GPO0				0x17
#घोषणा WM8804_GPO1				0x18
#घोषणा WM8804_GPO2				0x1A
#घोषणा WM8804_AIFTX				0x1B
#घोषणा WM8804_AIFRX				0x1C
#घोषणा WM8804_SPDRX1				0x1D
#घोषणा WM8804_PWRDN				0x1E

#घोषणा WM8804_REGISTER_COUNT			30
#घोषणा WM8804_MAX_REGISTER			0x1E

#घोषणा WM8804_TX_CLKSRC_MCLK			1
#घोषणा WM8804_TX_CLKSRC_PLL			2

#घोषणा WM8804_CLKOUT_SRC_CLK1			3
#घोषणा WM8804_CLKOUT_SRC_OSCCLK		4

#घोषणा WM8804_CLKOUT_DIV			1
#घोषणा WM8804_MCLK_DIV				2

#घोषणा WM8804_MCLKDIV_256FS			0
#घोषणा WM8804_MCLKDIV_128FS			1

बाह्य स्थिर काष्ठा regmap_config wm8804_regmap_config;
बाह्य स्थिर काष्ठा dev_pm_ops wm8804_pm;

पूर्णांक wm8804_probe(काष्ठा device *dev, काष्ठा regmap *regmap);
व्योम wm8804_हटाओ(काष्ठा device *dev);

#पूर्ण_अगर  /* _WM8804_H */

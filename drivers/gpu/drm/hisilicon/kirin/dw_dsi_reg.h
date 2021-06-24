<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Linaro Limited.
 * Copyright (c) 2014-2016 Hisilicon Limited.
 */

#अगर_अघोषित __DW_DSI_REG_H__
#घोषणा __DW_DSI_REG_H__

#घोषणा MASK(x)				(BIT(x) - 1)

/*
 * regs
 */
#घोषणा PWR_UP                  0x04  /* Core घातer-up */
#घोषणा RESET                   0
#घोषणा POWERUP                 BIT(0)
#घोषणा PHY_IF_CFG              0xA4  /* D-PHY पूर्णांकerface configuration */
#घोषणा CLKMGR_CFG              0x08  /* the पूर्णांकernal घड़ी भागiders */
#घोषणा PHY_RSTZ                0xA0  /* D-PHY reset control */
#घोषणा PHY_ENABLECLK           BIT(2)
#घोषणा PHY_UNRSTZ              BIT(1)
#घोषणा PHY_UNSHUTDOWNZ         BIT(0)
#घोषणा PHY_TST_CTRL0           0xB4  /* D-PHY test पूर्णांकerface control 0 */
#घोषणा PHY_TST_CTRL1           0xB8  /* D-PHY test पूर्णांकerface control 1 */
#घोषणा CLK_TLPX                0x10
#घोषणा CLK_THS_PREPARE         0x11
#घोषणा CLK_THS_ZERO            0x12
#घोषणा CLK_THS_TRAIL           0x13
#घोषणा CLK_TWAKEUP             0x14
#घोषणा DATA_TLPX(x)            (0x20 + ((x) << 4))
#घोषणा DATA_THS_PREPARE(x)     (0x21 + ((x) << 4))
#घोषणा DATA_THS_ZERO(x)        (0x22 + ((x) << 4))
#घोषणा DATA_THS_TRAIL(x)       (0x23 + ((x) << 4))
#घोषणा DATA_TTA_GO(x)          (0x24 + ((x) << 4))
#घोषणा DATA_TTA_GET(x)         (0x25 + ((x) << 4))
#घोषणा DATA_TWAKEUP(x)         (0x26 + ((x) << 4))
#घोषणा PHY_CFG_I               0x60
#घोषणा PHY_CFG_PLL_I           0x63
#घोषणा PHY_CFG_PLL_II          0x64
#घोषणा PHY_CFG_PLL_III         0x65
#घोषणा PHY_CFG_PLL_IV          0x66
#घोषणा PHY_CFG_PLL_V           0x67
#घोषणा DPI_COLOR_CODING        0x10  /* DPI color coding */
#घोषणा DPI_CFG_POL             0x14  /* DPI polarity configuration */
#घोषणा VID_HSA_TIME            0x48  /* Horizontal Sync Active समय */
#घोषणा VID_HBP_TIME            0x4C  /* Horizontal Back Porch समय */
#घोषणा VID_HLINE_TIME          0x50  /* Line समय */
#घोषणा VID_VSA_LINES           0x54  /* Vertical Sync Active period */
#घोषणा VID_VBP_LINES           0x58  /* Vertical Back Porch period */
#घोषणा VID_VFP_LINES           0x5C  /* Vertical Front Porch period */
#घोषणा VID_VACTIVE_LINES       0x60  /* Vertical resolution */
#घोषणा VID_PKT_SIZE            0x3C  /* Video packet size */
#घोषणा VID_MODE_CFG            0x38  /* Video mode configuration */
#घोषणा PHY_TMR_CFG             0x9C  /* Data lanes timing configuration */
#घोषणा BTA_TO_CNT              0x8C  /* Response समयout definition */
#घोषणा PHY_TMR_LPCLK_CFG       0x98  /* घड़ी lane timing configuration */
#घोषणा CLK_DATA_TMR_CFG        0xCC
#घोषणा LPCLK_CTRL              0x94  /* Low-घातer in घड़ी lane */
#घोषणा PHY_TXREQUESTCLKHS      BIT(0)
#घोषणा MODE_CFG                0x34  /* Video or Command mode selection */
#घोषणा PHY_STATUS              0xB0  /* D-PHY PPI status पूर्णांकerface */

#घोषणा	PHY_STOP_WAIT_TIME      0x30

/*
 * regs relevant क्रमागत
 */
क्रमागत dpi_color_coding अणु
	DSI_24BITS_1 = 5,
पूर्ण;

क्रमागत dsi_video_mode_type अणु
	DSI_NON_BURST_SYNC_PULSES = 0,
	DSI_NON_BURST_SYNC_EVENTS,
	DSI_BURST_SYNC_PULSES_1,
	DSI_BURST_SYNC_PULSES_2
पूर्ण;

क्रमागत dsi_work_mode अणु
	DSI_VIDEO_MODE = 0,
	DSI_COMMAND_MODE
पूर्ण;

/*
 * Register Write/Read Helper functions
 */
अटल अंतरभूत व्योम dw_update_bits(व्योम __iomem *addr, u32 bit_start,
				  u32 mask, u32 val)
अणु
	u32 पंचांगp, orig;

	orig = पढ़ोl(addr);
	पंचांगp = orig & ~(mask << bit_start);
	पंचांगp |= (val & mask) << bit_start;
	ग_लिखोl(पंचांगp, addr);
पूर्ण

#पूर्ण_अगर /* __DW_DRM_DSI_H__ */

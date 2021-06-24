<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  arch/arm/mach-omap1/include/mach/lcd_dma.h
 *
 * Extracted from arch/arm/plat-omap/include/plat/dma.h
 *  Copyright (C) 2003 Nokia Corporation
 *  Author: Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 */
#अगर_अघोषित __MACH_OMAP1_LCD_DMA_H__
#घोषणा __MACH_OMAP1_LCD_DMA_H__

/* Hardware रेजिस्टरs क्रम LCD DMA */
#घोषणा OMAP1510_DMA_LCD_BASE		(0xfffedb00)
#घोषणा OMAP1510_DMA_LCD_CTRL		(OMAP1510_DMA_LCD_BASE + 0x00)
#घोषणा OMAP1510_DMA_LCD_TOP_F1_L	(OMAP1510_DMA_LCD_BASE + 0x02)
#घोषणा OMAP1510_DMA_LCD_TOP_F1_U	(OMAP1510_DMA_LCD_BASE + 0x04)
#घोषणा OMAP1510_DMA_LCD_BOT_F1_L	(OMAP1510_DMA_LCD_BASE + 0x06)
#घोषणा OMAP1510_DMA_LCD_BOT_F1_U	(OMAP1510_DMA_LCD_BASE + 0x08)

#घोषणा OMAP1610_DMA_LCD_BASE		(0xfffee300)
#घोषणा OMAP1610_DMA_LCD_CSDP		(OMAP1610_DMA_LCD_BASE + 0xc0)
#घोषणा OMAP1610_DMA_LCD_CCR		(OMAP1610_DMA_LCD_BASE + 0xc2)
#घोषणा OMAP1610_DMA_LCD_CTRL		(OMAP1610_DMA_LCD_BASE + 0xc4)
#घोषणा OMAP1610_DMA_LCD_TOP_B1_L	(OMAP1610_DMA_LCD_BASE + 0xc8)
#घोषणा OMAP1610_DMA_LCD_TOP_B1_U	(OMAP1610_DMA_LCD_BASE + 0xca)
#घोषणा OMAP1610_DMA_LCD_BOT_B1_L	(OMAP1610_DMA_LCD_BASE + 0xcc)
#घोषणा OMAP1610_DMA_LCD_BOT_B1_U	(OMAP1610_DMA_LCD_BASE + 0xce)
#घोषणा OMAP1610_DMA_LCD_TOP_B2_L	(OMAP1610_DMA_LCD_BASE + 0xd0)
#घोषणा OMAP1610_DMA_LCD_TOP_B2_U	(OMAP1610_DMA_LCD_BASE + 0xd2)
#घोषणा OMAP1610_DMA_LCD_BOT_B2_L	(OMAP1610_DMA_LCD_BASE + 0xd4)
#घोषणा OMAP1610_DMA_LCD_BOT_B2_U	(OMAP1610_DMA_LCD_BASE + 0xd6)
#घोषणा OMAP1610_DMA_LCD_SRC_EI_B1	(OMAP1610_DMA_LCD_BASE + 0xd8)
#घोषणा OMAP1610_DMA_LCD_SRC_FI_B1_L	(OMAP1610_DMA_LCD_BASE + 0xda)
#घोषणा OMAP1610_DMA_LCD_SRC_EN_B1	(OMAP1610_DMA_LCD_BASE + 0xe0)
#घोषणा OMAP1610_DMA_LCD_SRC_FN_B1	(OMAP1610_DMA_LCD_BASE + 0xe4)
#घोषणा OMAP1610_DMA_LCD_LCH_CTRL	(OMAP1610_DMA_LCD_BASE + 0xea)
#घोषणा OMAP1610_DMA_LCD_SRC_FI_B1_U	(OMAP1610_DMA_LCD_BASE + 0xf4)

/* LCD DMA block numbers */
क्रमागत अणु
	OMAP_LCD_DMA_B1_TOP,
	OMAP_LCD_DMA_B1_BOTTOM,
	OMAP_LCD_DMA_B2_TOP,
	OMAP_LCD_DMA_B2_BOTTOM
पूर्ण;

/* LCD DMA functions */
बाह्य पूर्णांक omap_request_lcd_dma(व्योम (*callback)(u16 status, व्योम *data),
				व्योम *data);
बाह्य व्योम omap_मुक्त_lcd_dma(व्योम);
बाह्य व्योम omap_setup_lcd_dma(व्योम);
बाह्य व्योम omap_enable_lcd_dma(व्योम);
बाह्य व्योम omap_stop_lcd_dma(व्योम);
बाह्य व्योम omap_set_lcd_dma_ext_controller(पूर्णांक बाह्यal);
बाह्य व्योम omap_set_lcd_dma_single_transfer(पूर्णांक single);
बाह्य व्योम omap_set_lcd_dma_b1(अचिन्हित दीर्घ addr, u16 fb_xres, u16 fb_yres,
				पूर्णांक data_type);
बाह्य व्योम omap_set_lcd_dma_b1_rotation(पूर्णांक rotate);
बाह्य व्योम omap_set_lcd_dma_b1_vxres(अचिन्हित दीर्घ vxres);
बाह्य व्योम omap_set_lcd_dma_b1_mirror(पूर्णांक mirror);
बाह्य व्योम omap_set_lcd_dma_b1_scale(अचिन्हित पूर्णांक xscale, अचिन्हित पूर्णांक yscale);

बाह्य पूर्णांक omap_lcd_dma_running(व्योम);

#पूर्ण_अगर /* __MACH_OMAP1_LCD_DMA_H__ */

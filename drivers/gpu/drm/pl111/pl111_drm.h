<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * (C) COPYRIGHT 2012-2013 ARM Limited. All rights reserved.
 *
 * Parts of this file were based on sources as follows:
 *
 * Copyright (c) 2006-2008 Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (C) 2011 Texas Instruments
 */

#अगर_अघोषित _PL111_DRM_H_
#घोषणा _PL111_DRM_H_

#समावेश <linux/clk-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_simple_kms_helper.h>

/*
 * CLCD Controller Internal Register addresses
 */
#घोषणा CLCD_TIM0		0x00000000
#घोषणा CLCD_TIM1		0x00000004
#घोषणा CLCD_TIM2		0x00000008
#घोषणा CLCD_TIM3		0x0000000c
#घोषणा CLCD_UBAS		0x00000010
#घोषणा CLCD_LBAS		0x00000014

#घोषणा CLCD_PL110_IENB		0x00000018
#घोषणा CLCD_PL110_CNTL		0x0000001c
#घोषणा CLCD_PL110_STAT		0x00000020
#घोषणा CLCD_PL110_INTR		0x00000024
#घोषणा CLCD_PL110_UCUR		0x00000028
#घोषणा CLCD_PL110_LCUR		0x0000002C

#घोषणा CLCD_PL111_CNTL		0x00000018
#घोषणा CLCD_PL111_IENB		0x0000001c
#घोषणा CLCD_PL111_RIS		0x00000020
#घोषणा CLCD_PL111_MIS		0x00000024
#घोषणा CLCD_PL111_ICR		0x00000028
#घोषणा CLCD_PL111_UCUR		0x0000002c
#घोषणा CLCD_PL111_LCUR		0x00000030

#घोषणा CLCD_PALL		0x00000200
#घोषणा CLCD_PALETTE		0x00000200

#घोषणा TIM2_PCD_LO_MASK	GENMASK(4, 0)
#घोषणा TIM2_PCD_LO_BITS	5
#घोषणा TIM2_CLKSEL		(1 << 5)
#घोषणा TIM2_ACB_MASK		GENMASK(10, 6)
#घोषणा TIM2_IVS		(1 << 11)
#घोषणा TIM2_IHS		(1 << 12)
#घोषणा TIM2_IPC		(1 << 13)
#घोषणा TIM2_IOE		(1 << 14)
#घोषणा TIM2_BCD		(1 << 26)
#घोषणा TIM2_PCD_HI_MASK	GENMASK(31, 27)
#घोषणा TIM2_PCD_HI_BITS	5
#घोषणा TIM2_PCD_HI_SHIFT	27

#घोषणा CNTL_LCDEN		(1 << 0)
#घोषणा CNTL_LCDBPP1		(0 << 1)
#घोषणा CNTL_LCDBPP2		(1 << 1)
#घोषणा CNTL_LCDBPP4		(2 << 1)
#घोषणा CNTL_LCDBPP8		(3 << 1)
#घोषणा CNTL_LCDBPP16		(4 << 1)
#घोषणा CNTL_LCDBPP16_565	(6 << 1)
#घोषणा CNTL_LCDBPP16_444	(7 << 1)
#घोषणा CNTL_LCDBPP24		(5 << 1)
#घोषणा CNTL_LCDBW		(1 << 4)
#घोषणा CNTL_LCDTFT		(1 << 5)
#घोषणा CNTL_LCDMONO8		(1 << 6)
#घोषणा CNTL_LCDDUAL		(1 << 7)
#घोषणा CNTL_BGR		(1 << 8)
#घोषणा CNTL_BEBO		(1 << 9)
#घोषणा CNTL_BEPO		(1 << 10)
#घोषणा CNTL_LCDPWR		(1 << 11)
#घोषणा CNTL_LCDVCOMP(x)	((x) << 12)
#घोषणा CNTL_LDMAFIFOTIME	(1 << 15)
#घोषणा CNTL_WATERMARK		(1 << 16)

/* ST Microelectronics variant bits */
#घोषणा CNTL_ST_1XBPP_444	0x0
#घोषणा CNTL_ST_1XBPP_5551	(1 << 17)
#घोषणा CNTL_ST_1XBPP_565	(1 << 18)
#घोषणा CNTL_ST_CDWID_12	0x0
#घोषणा CNTL_ST_CDWID_16	(1 << 19)
#घोषणा CNTL_ST_CDWID_18	(1 << 20)
#घोषणा CNTL_ST_CDWID_24	((1 << 19) | (1 << 20))
#घोषणा CNTL_ST_CEAEN		(1 << 21)
#घोषणा CNTL_ST_LCDBPP24_PACKED	(6 << 1)

#घोषणा CLCD_IRQ_NEXTBASE_UPDATE BIT(2)

काष्ठा drm_minor;

/**
 * काष्ठा pl111_variant_data - encodes IP dअगरferences
 * @name: the name of this variant
 * @is_pl110: this is the early PL110 variant
 * @is_lcdc: this is the ST Microelectronics Nomadik LCDC variant
 * @बाह्यal_bgr: this is the Versatile Pl110 variant with बाह्यal
 *	BGR/RGB routing
 * @broken_घड़ीभागider: the घड़ी भागider is broken and we need to
 *	use the supplied घड़ी directly
 * @broken_vblank: the vblank IRQ is broken on this variant
 * @st_biपंचांगux_control: this variant is using the ST Micro biपंचांगux
 *	extensions to the control रेजिस्टर
 * @क्रमmats: array of supported pixel क्रमmats on this variant
 * @nक्रमmats: the length of the array of supported pixel क्रमmats
 * @fb_bpp: desired bits per pixel on the शेष framebuffer
 */
काष्ठा pl111_variant_data अणु
	स्थिर अक्षर *name;
	bool is_pl110;
	bool is_lcdc;
	bool बाह्यal_bgr;
	bool broken_घड़ीभागider;
	bool broken_vblank;
	bool st_biपंचांगux_control;
	स्थिर u32 *क्रमmats;
	अचिन्हित पूर्णांक nक्रमmats;
	अचिन्हित पूर्णांक fb_bpp;
पूर्ण;

काष्ठा pl111_drm_dev_निजी अणु
	काष्ठा drm_device *drm;

	काष्ठा drm_connector *connector;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_simple_display_pipe pipe;

	व्योम *regs;
	u32 memory_bw;
	u32 ienb;
	u32 ctrl;
	/* The pixel घड़ी (a reference to our घड़ी भागider off of CLCDCLK). */
	काष्ठा clk *clk;
	/* pl111's पूर्णांकernal घड़ी भागider. */
	काष्ठा clk_hw clk_भाग;
	/* Lock to sync access to CLCD_TIM2 between the common घड़ी
	 * subप्रणाली and pl111_display_enable().
	 */
	spinlock_t tim2_lock;
	स्थिर काष्ठा pl111_variant_data *variant;
	व्योम (*variant_display_enable) (काष्ठा drm_device *drm, u32 क्रमmat);
	व्योम (*variant_display_disable) (काष्ठा drm_device *drm);
	bool use_device_memory;
पूर्ण;

पूर्णांक pl111_display_init(काष्ठा drm_device *dev);
irqवापस_t pl111_irq(पूर्णांक irq, व्योम *data);
व्योम pl111_debugfs_init(काष्ठा drm_minor *minor);

#पूर्ण_अगर /* _PL111_DRM_H_ */

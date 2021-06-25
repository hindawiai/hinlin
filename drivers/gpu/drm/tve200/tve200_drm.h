<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 * Parts of this file were based on sources as follows:
 *
 * Copyright (C) 2006-2008 Intel Corporation
 * Copyright (C) 2007 Amos Lee <amos_lee@storlinksemi.com>
 * Copyright (C) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (C) 2011 Texas Instruments
 * Copyright (C) 2017 Eric Anholt
 */

#अगर_अघोषित _TVE200_DRM_H_
#घोषणा _TVE200_DRM_H_

#समावेश <linux/irqवापस.h>

#समावेश <drm/drm_simple_kms_helper.h>

काष्ठा clk;
काष्ठा drm_bridge;
काष्ठा drm_connector;
काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_mode_create_dumb;
काष्ठा drm_panel;

/* Bits 2-31 are valid physical base addresses */
#घोषणा TVE200_Y_FRAME_BASE_ADDR	0x00
#घोषणा TVE200_U_FRAME_BASE_ADDR	0x04
#घोषणा TVE200_V_FRAME_BASE_ADDR	0x08

#घोषणा TVE200_INT_EN			0x0C
#घोषणा TVE200_INT_CLR			0x10
#घोषणा TVE200_INT_STAT			0x14
#घोषणा TVE200_INT_BUS_ERR		BIT(7)
#घोषणा TVE200_INT_V_STATUS		BIT(6) /* vertical blank */
#घोषणा TVE200_INT_V_NEXT_FRAME		BIT(5)
#घोषणा TVE200_INT_U_NEXT_FRAME		BIT(4)
#घोषणा TVE200_INT_Y_NEXT_FRAME		BIT(3)
#घोषणा TVE200_INT_V_FIFO_UNDERRUN	BIT(2)
#घोषणा TVE200_INT_U_FIFO_UNDERRUN	BIT(1)
#घोषणा TVE200_INT_Y_FIFO_UNDERRUN	BIT(0)
#घोषणा TVE200_FIFO_UNDERRUNS		(TVE200_INT_V_FIFO_UNDERRUN | \
					 TVE200_INT_U_FIFO_UNDERRUN | \
					 TVE200_INT_Y_FIFO_UNDERRUN)

#घोषणा TVE200_CTRL			0x18
#घोषणा TVE200_CTRL_YUV420		BIT(31)
#घोषणा TVE200_CTRL_CSMODE		BIT(30)
#घोषणा TVE200_CTRL_NONINTERLACE	BIT(28) /* 0 = non-पूर्णांकerlace CCIR656 */
#घोषणा TVE200_CTRL_TVCLKP		BIT(27) /* Inverted घड़ी phase */
/* Bits 24..26 define the burst size after arbitration on the bus */
#घोषणा TVE200_CTRL_BURST_4_WORDS	(0 << 24)
#घोषणा TVE200_CTRL_BURST_8_WORDS	(1 << 24)
#घोषणा TVE200_CTRL_BURST_16_WORDS	(2 << 24)
#घोषणा TVE200_CTRL_BURST_32_WORDS	(3 << 24)
#घोषणा TVE200_CTRL_BURST_64_WORDS	(4 << 24)
#घोषणा TVE200_CTRL_BURST_128_WORDS	(5 << 24)
#घोषणा TVE200_CTRL_BURST_256_WORDS	(6 << 24)
#घोषणा TVE200_CTRL_BURST_0_WORDS	(7 << 24) /* ? */
/*
 * Bits 16..23 is the retry count*16 beक्रमe issueing a new AHB transfer
 * on the AHB bus.
 */
#घोषणा TVE200_CTRL_RETRYCNT_MASK	GENMASK(23, 16)
#घोषणा TVE200_CTRL_RETRYCNT_16		(1 << 16)
#घोषणा TVE200_CTRL_BBBP		BIT(15) /* 0 = little-endian */
/* Bits 12..14 define the YCbCr ordering */
#घोषणा TVE200_CTRL_YCBCRODR_CB0Y0CR0Y1	(0 << 12)
#घोषणा TVE200_CTRL_YCBCRODR_Y0CB0Y1CR0	(1 << 12)
#घोषणा TVE200_CTRL_YCBCRODR_CR0Y0CB0Y1	(2 << 12)
#घोषणा TVE200_CTRL_YCBCRODR_Y1CB0Y0CR0	(3 << 12)
#घोषणा TVE200_CTRL_YCBCRODR_CR0Y1CB0Y0	(4 << 12)
#घोषणा TVE200_CTRL_YCBCRODR_Y1CR0Y0CB0	(5 << 12)
#घोषणा TVE200_CTRL_YCBCRODR_CB0Y1CR0Y0	(6 << 12)
#घोषणा TVE200_CTRL_YCBCRODR_Y0CR0Y1CB0	(7 << 12)
/* Bits 10..11 define the input resolution (framebuffer size) */
#घोषणा TVE200_CTRL_IPRESOL_CIF		(0 << 10)
#घोषणा TVE200_CTRL_IPRESOL_VGA		(1 << 10)
#घोषणा TVE200_CTRL_IPRESOL_D1		(2 << 10)
#घोषणा TVE200_CTRL_NTSC		BIT(9) /* 0 = PAL, 1 = NTSC */
#घोषणा TVE200_CTRL_INTERLACE		BIT(8) /* 1 = पूर्णांकerlace, only क्रम D1 */
#घोषणा TVE200_IPDMOD_RGB555		(0 << 6) /* TVE200_CTRL_YUV420 = 0 */
#घोषणा TVE200_IPDMOD_RGB565		(1 << 6)
#घोषणा TVE200_IPDMOD_RGB888		(2 << 6)
#घोषणा TVE200_IPDMOD_YUV420		(2 << 6) /* TVE200_CTRL_YUV420 = 1 */
#घोषणा TVE200_IPDMOD_YUV422		(3 << 6)
/* Bits 4 & 5 define when to fire the vblank IRQ */
#घोषणा TVE200_VSTSTYPE_VSYNC		(0 << 4) /* start of vsync */
#घोषणा TVE200_VSTSTYPE_VBP		(1 << 4) /* start of v back porch */
#घोषणा TVE200_VSTSTYPE_VAI		(2 << 4) /* start of v active image */
#घोषणा TVE200_VSTSTYPE_VFP		(3 << 4) /* start of v front porch */
#घोषणा TVE200_VSTSTYPE_BITS		(BIT(4) | BIT(5))
#घोषणा TVE200_BGR			BIT(1) /* 0 = RGB, 1 = BGR */
#घोषणा TVE200_TVEEN			BIT(0) /* Enable TVE block */

#घोषणा TVE200_CTRL_2			0x1c
#घोषणा TVE200_CTRL_3			0x20

#घोषणा TVE200_CTRL_4			0x24
#घोषणा TVE200_CTRL_4_RESET		BIT(0) /* triggers reset of TVE200 */

काष्ठा tve200_drm_dev_निजी अणु
	काष्ठा drm_device *drm;

	काष्ठा drm_connector *connector;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_simple_display_pipe pipe;

	व्योम *regs;
	काष्ठा clk *pclk;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा to_tve200_connector(x) \
	container_of(x, काष्ठा tve200_drm_connector, connector)

पूर्णांक tve200_display_init(काष्ठा drm_device *dev);
irqवापस_t tve200_irq(पूर्णांक irq, व्योम *data);
पूर्णांक tve200_connector_init(काष्ठा drm_device *dev);
पूर्णांक tve200_encoder_init(काष्ठा drm_device *dev);
पूर्णांक tve200_dumb_create(काष्ठा drm_file *file_priv,
		      काष्ठा drm_device *dev,
		      काष्ठा drm_mode_create_dumb *args);

#पूर्ण_अगर /* _TVE200_DRM_H_ */

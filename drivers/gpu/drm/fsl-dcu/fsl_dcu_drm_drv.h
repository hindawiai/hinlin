<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * Freescale DCU drm device driver
 */

#अगर_अघोषित __FSL_DCU_DRM_DRV_H__
#घोषणा __FSL_DCU_DRM_DRV_H__

#समावेश <drm/drm_encoder.h>

#समावेश "fsl_dcu_drm_crtc.h"
#समावेश "fsl_dcu_drm_output.h"
#समावेश "fsl_dcu_drm_plane.h"

#घोषणा DCU_DCU_MODE			0x0010
#घोषणा DCU_MODE_BLEND_ITER(x)		((x) << 20)
#घोषणा DCU_MODE_RASTER_EN		BIT(14)
#घोषणा DCU_MODE_DCU_MODE(x)		(x)
#घोषणा DCU_MODE_DCU_MODE_MASK		0x03
#घोषणा DCU_MODE_OFF			0
#घोषणा DCU_MODE_NORMAL			1
#घोषणा DCU_MODE_TEST			2
#घोषणा DCU_MODE_COLORBAR		3

#घोषणा DCU_BGND			0x0014
#घोषणा DCU_BGND_R(x)			((x) << 16)
#घोषणा DCU_BGND_G(x)			((x) << 8)
#घोषणा DCU_BGND_B(x)			(x)

#घोषणा DCU_DISP_SIZE			0x0018
#घोषणा DCU_DISP_SIZE_DELTA_Y(x)	((x) << 16)
/*Regisiter value 1/16 of horizontal resolution*/
#घोषणा DCU_DISP_SIZE_DELTA_X(x)	((x) >> 4)

#घोषणा DCU_HSYN_PARA			0x001c
#घोषणा DCU_HSYN_PARA_BP(x)		((x) << 22)
#घोषणा DCU_HSYN_PARA_PW(x)		((x) << 11)
#घोषणा DCU_HSYN_PARA_FP(x)		(x)

#घोषणा DCU_VSYN_PARA			0x0020
#घोषणा DCU_VSYN_PARA_BP(x)		((x) << 22)
#घोषणा DCU_VSYN_PARA_PW(x)		((x) << 11)
#घोषणा DCU_VSYN_PARA_FP(x)		(x)

#घोषणा DCU_SYN_POL			0x0024
#घोषणा DCU_SYN_POL_INV_PXCK		BIT(6)
#घोषणा DCU_SYN_POL_NEG			BIT(5)
#घोषणा DCU_SYN_POL_INV_VS_LOW		BIT(1)
#घोषणा DCU_SYN_POL_INV_HS_LOW		BIT(0)

#घोषणा DCU_THRESHOLD			0x0028
#घोषणा DCU_THRESHOLD_LS_BF_VS(x)	((x) << 16)
#घोषणा DCU_THRESHOLD_OUT_BUF_HIGH(x)	((x) << 8)
#घोषणा DCU_THRESHOLD_OUT_BUF_LOW(x)	(x)
#घोषणा BF_VS_VAL			0x03
#घोषणा BUF_MAX_VAL			0x78
#घोषणा BUF_MIN_VAL			0x0a

#घोषणा DCU_INT_STATUS			0x002C
#घोषणा DCU_INT_STATUS_VSYNC		BIT(0)
#घोषणा DCU_INT_STATUS_UNDRUN		BIT(1)
#घोषणा DCU_INT_STATUS_LSBFVS		BIT(2)
#घोषणा DCU_INT_STATUS_VBLANK		BIT(3)
#घोषणा DCU_INT_STATUS_CRCREADY		BIT(4)
#घोषणा DCU_INT_STATUS_CRCOVERFLOW	BIT(5)
#घोषणा DCU_INT_STATUS_P1FIFOLO		BIT(6)
#घोषणा DCU_INT_STATUS_P1FIFOHI		BIT(7)
#घोषणा DCU_INT_STATUS_P2FIFOLO		BIT(8)
#घोषणा DCU_INT_STATUS_P2FIFOHI		BIT(9)
#घोषणा DCU_INT_STATUS_PROGEND		BIT(10)
#घोषणा DCU_INT_STATUS_IPMERROR		BIT(11)
#घोषणा DCU_INT_STATUS_LYRTRANS		BIT(12)
#घोषणा DCU_INT_STATUS_DMATRANS		BIT(14)
#घोषणा DCU_INT_STATUS_P3FIFOLO		BIT(16)
#घोषणा DCU_INT_STATUS_P3FIFOHI		BIT(17)
#घोषणा DCU_INT_STATUS_P4FIFOLO		BIT(18)
#घोषणा DCU_INT_STATUS_P4FIFOHI		BIT(19)
#घोषणा DCU_INT_STATUS_P1EMPTY		BIT(26)
#घोषणा DCU_INT_STATUS_P2EMPTY		BIT(27)
#घोषणा DCU_INT_STATUS_P3EMPTY		BIT(28)
#घोषणा DCU_INT_STATUS_P4EMPTY		BIT(29)

#घोषणा DCU_INT_MASK			0x0030
#घोषणा DCU_INT_MASK_VSYNC		BIT(0)
#घोषणा DCU_INT_MASK_UNDRUN		BIT(1)
#घोषणा DCU_INT_MASK_LSBFVS		BIT(2)
#घोषणा DCU_INT_MASK_VBLANK		BIT(3)
#घोषणा DCU_INT_MASK_CRCREADY		BIT(4)
#घोषणा DCU_INT_MASK_CRCOVERFLOW	BIT(5)
#घोषणा DCU_INT_MASK_P1FIFOLO		BIT(6)
#घोषणा DCU_INT_MASK_P1FIFOHI		BIT(7)
#घोषणा DCU_INT_MASK_P2FIFOLO		BIT(8)
#घोषणा DCU_INT_MASK_P2FIFOHI		BIT(9)
#घोषणा DCU_INT_MASK_PROGEND		BIT(10)
#घोषणा DCU_INT_MASK_IPMERROR		BIT(11)
#घोषणा DCU_INT_MASK_LYRTRANS		BIT(12)
#घोषणा DCU_INT_MASK_DMATRANS		BIT(14)
#घोषणा DCU_INT_MASK_P3FIFOLO		BIT(16)
#घोषणा DCU_INT_MASK_P3FIFOHI		BIT(17)
#घोषणा DCU_INT_MASK_P4FIFOLO		BIT(18)
#घोषणा DCU_INT_MASK_P4FIFOHI		BIT(19)
#घोषणा DCU_INT_MASK_P1EMPTY		BIT(26)
#घोषणा DCU_INT_MASK_P2EMPTY		BIT(27)
#घोषणा DCU_INT_MASK_P3EMPTY		BIT(28)
#घोषणा DCU_INT_MASK_P4EMPTY		BIT(29)

#घोषणा DCU_DIV_RATIO			0x0054

#घोषणा DCU_UPDATE_MODE			0x00cc
#घोषणा DCU_UPDATE_MODE_MODE		BIT(31)
#घोषणा DCU_UPDATE_MODE_READREG		BIT(30)

#घोषणा DCU_DCFB_MAX			0x300

#घोषणा DCU_CTRLDESCLN(layer, reg)	(0x200 + (reg - 1) * 4 + (layer) * 0x40)

#घोषणा DCU_LAYER_HEIGHT(x)		((x) << 16)
#घोषणा DCU_LAYER_WIDTH(x)		(x)

#घोषणा DCU_LAYER_POSY(x)		((x) << 16)
#घोषणा DCU_LAYER_POSX(x)		(x)

#घोषणा DCU_LAYER_EN			BIT(31)
#घोषणा DCU_LAYER_TILE_EN		BIT(30)
#घोषणा DCU_LAYER_DATA_SEL_CLUT		BIT(29)
#घोषणा DCU_LAYER_SAFETY_EN		BIT(28)
#घोषणा DCU_LAYER_TRANS(x)		((x) << 20)
#घोषणा DCU_LAYER_BPP(x)		((x) << 16)
#घोषणा DCU_LAYER_RLE_EN		BIT(15)
#घोषणा DCU_LAYER_LUOFFS(x)		((x) << 4)
#घोषणा DCU_LAYER_BB_ON			BIT(2)
#घोषणा DCU_LAYER_AB_NONE		0
#घोषणा DCU_LAYER_AB_CHROMA_KEYING	1
#घोषणा DCU_LAYER_AB_WHOLE_FRAME	2

#घोषणा DCU_LAYER_CKMAX_R(x)		((x) << 16)
#घोषणा DCU_LAYER_CKMAX_G(x)		((x) << 8)
#घोषणा DCU_LAYER_CKMAX_B(x)		(x)

#घोषणा DCU_LAYER_CKMIN_R(x)		((x) << 16)
#घोषणा DCU_LAYER_CKMIN_G(x)		((x) << 8)
#घोषणा DCU_LAYER_CKMIN_B(x)		(x)

#घोषणा DCU_LAYER_TILE_VER(x)		((x) << 16)
#घोषणा DCU_LAYER_TILE_HOR(x)		(x)

#घोषणा DCU_LAYER_FG_FCOLOR(x)		(x)

#घोषणा DCU_LAYER_BG_BCOLOR(x)		(x)

#घोषणा DCU_LAYER_POST_SKIP(x)		((x) << 16)
#घोषणा DCU_LAYER_PRE_SKIP(x)		(x)

#घोषणा FSL_DCU_RGB565			4
#घोषणा FSL_DCU_RGB888			5
#घोषणा FSL_DCU_ARGB8888		6
#घोषणा FSL_DCU_ARGB1555		11
#घोषणा FSL_DCU_ARGB4444		12
#घोषणा FSL_DCU_YUV422			14

#घोषणा VF610_LAYER_REG_NUM		9
#घोषणा LS1021A_LAYER_REG_NUM		10

काष्ठा clk;
काष्ठा device;
काष्ठा drm_device;

काष्ठा fsl_dcu_soc_data अणु
	स्थिर अक्षर *name;
	/*total layer number*/
	अचिन्हित पूर्णांक total_layer;
	/*max layer number DCU supported*/
	अचिन्हित पूर्णांक max_layer;
	अचिन्हित पूर्णांक layer_regs;
पूर्ण;

काष्ठा fsl_dcu_drm_device अणु
	काष्ठा device *dev;
	काष्ठा device_node *np;
	काष्ठा regmap *regmap;
	पूर्णांक irq;
	काष्ठा clk *clk;
	काष्ठा clk *pix_clk;
	काष्ठा fsl_tcon *tcon;
	/*protects hardware रेजिस्टर*/
	spinlock_t irq_lock;
	काष्ठा drm_device *drm;
	काष्ठा drm_crtc crtc;
	काष्ठा drm_encoder encoder;
	काष्ठा fsl_dcu_drm_connector connector;
	स्थिर काष्ठा fsl_dcu_soc_data *soc;
पूर्ण;

पूर्णांक fsl_dcu_drm_modeset_init(काष्ठा fsl_dcu_drm_device *fsl_dev);

#पूर्ण_अगर /* __FSL_DCU_DRM_DRV_H__ */

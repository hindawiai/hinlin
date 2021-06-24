<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Microchip Image Sensor Controller (ISC) common driver base
 *
 * Copyright (C) 2016-2019 Microchip Technology, Inc.
 *
 * Author: Songjun Wu
 * Author: Eugen Hristev <eugen.hristev@microchip.com>
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/aपंचांगel-isc-media.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "atmel-isc-regs.h"
#समावेश "atmel-isc.h"

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

अटल अचिन्हित पूर्णांक sensor_preferred = 1;
module_param(sensor_preferred, uपूर्णांक, 0644);
MODULE_PARM_DESC(sensor_preferred,
		 "Sensor is preferred to output the specified format (1-on 0-off), default 1");

/* This is a list of the क्रमmats that the ISC can *output* */
स्थिर काष्ठा isc_क्रमmat controller_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_ARGB444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_ARGB555,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_ABGR32,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_XBGR32,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUV420,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUV422P,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_GREY,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_Y10,
	पूर्ण,
पूर्ण;

/* This is a list of क्रमmats that the ISC can receive as *input* */
काष्ठा isc_क्रमmat क्रमmats_list[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_SBGGR8,
		.mbus_code	= MEDIA_BUS_FMT_SBGGR8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
		.cfa_baycfg	= ISC_BAY_CFG_BGBG,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SGBRG8,
		.mbus_code	= MEDIA_BUS_FMT_SGBRG8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
		.cfa_baycfg	= ISC_BAY_CFG_GBGB,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG8,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
		.cfa_baycfg	= ISC_BAY_CFG_GRGR,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SRGGB8,
		.mbus_code	= MEDIA_BUS_FMT_SRGGB8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
		.cfa_baycfg	= ISC_BAY_CFG_RGRG,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SBGGR10,
		.mbus_code	= MEDIA_BUS_FMT_SBGGR10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
		.cfa_baycfg	= ISC_BAY_CFG_RGRG,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SGBRG10,
		.mbus_code	= MEDIA_BUS_FMT_SGBRG10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
		.cfa_baycfg	= ISC_BAY_CFG_GBGB,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG10,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
		.cfa_baycfg	= ISC_BAY_CFG_GRGR,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SRGGB10,
		.mbus_code	= MEDIA_BUS_FMT_SRGGB10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
		.cfa_baycfg	= ISC_BAY_CFG_RGRG,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SBGGR12,
		.mbus_code	= MEDIA_BUS_FMT_SBGGR12_1X12,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TWELVE,
		.cfa_baycfg	= ISC_BAY_CFG_BGBG,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SGBRG12,
		.mbus_code	= MEDIA_BUS_FMT_SGBRG12_1X12,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TWELVE,
		.cfa_baycfg	= ISC_BAY_CFG_GBGB,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG12,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG12_1X12,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TWELVE,
		.cfa_baycfg	= ISC_BAY_CFG_GRGR,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_SRGGB12,
		.mbus_code	= MEDIA_BUS_FMT_SRGGB12_1X12,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TWELVE,
		.cfa_baycfg	= ISC_BAY_CFG_RGRG,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_GREY,
		.mbus_code	= MEDIA_BUS_FMT_Y8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.mbus_code	= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_Y10,
		.mbus_code	= MEDIA_BUS_FMT_Y10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
	पूर्ण,

पूर्ण;

/* Gamma table with gamma 1/2.2 */
स्थिर u32 isc_gamma_table[GAMMA_MAX + 1][GAMMA_ENTRIES] = अणु
	/* 0 --> gamma 1/1.8 */
	अणु      0x65,  0x66002F,  0x950025,  0xBB0020,  0xDB001D,  0xF8001A,
	  0x1130018, 0x12B0017, 0x1420016, 0x1580014, 0x16D0013, 0x1810012,
	  0x1940012, 0x1A60012, 0x1B80011, 0x1C90010, 0x1DA0010, 0x1EA000F,
	  0x1FA000F, 0x209000F, 0x218000F, 0x227000E, 0x235000E, 0x243000E,
	  0x251000E, 0x25F000D, 0x26C000D, 0x279000D, 0x286000D, 0x293000C,
	  0x2A0000C, 0x2AC000C, 0x2B8000C, 0x2C4000C, 0x2D0000B, 0x2DC000B,
	  0x2E7000B, 0x2F3000B, 0x2FE000B, 0x309000B, 0x314000B, 0x31F000A,
	  0x32A000A, 0x334000B, 0x33F000A, 0x349000A, 0x354000A, 0x35E000A,
	  0x368000A, 0x372000A, 0x37C000A, 0x386000A, 0x3900009, 0x399000A,
	  0x3A30009, 0x3AD0009, 0x3B60009, 0x3BF000A, 0x3C90009, 0x3D20009,
	  0x3DB0009, 0x3E40009, 0x3ED0009, 0x3F60009 पूर्ण,

	/* 1 --> gamma 1/2 */
	अणु      0x7F,  0x800034,  0xB50028,  0xDE0021, 0x100001E, 0x11E001B,
	  0x1390019, 0x1520017, 0x16A0015, 0x1800014, 0x1940014, 0x1A80013,
	  0x1BB0012, 0x1CD0011, 0x1DF0010, 0x1EF0010, 0x200000F, 0x20F000F,
	  0x21F000E, 0x22D000F, 0x23C000E, 0x24A000E, 0x258000D, 0x265000D,
	  0x273000C, 0x27F000D, 0x28C000C, 0x299000C, 0x2A5000C, 0x2B1000B,
	  0x2BC000C, 0x2C8000B, 0x2D3000C, 0x2DF000B, 0x2EA000A, 0x2F5000A,
	  0x2FF000B, 0x30A000A, 0x314000B, 0x31F000A, 0x329000A, 0x333000A,
	  0x33D0009, 0x3470009, 0x350000A, 0x35A0009, 0x363000A, 0x36D0009,
	  0x3760009, 0x37F0009, 0x3880009, 0x3910009, 0x39A0009, 0x3A30009,
	  0x3AC0008, 0x3B40009, 0x3BD0008, 0x3C60008, 0x3CE0008, 0x3D60009,
	  0x3DF0008, 0x3E70008, 0x3EF0008, 0x3F70008 पूर्ण,

	/* 2 --> gamma 1/2.2 */
	अणु      0x99,  0x9B0038,  0xD4002A,  0xFF0023, 0x122001F, 0x141001B,
	  0x15D0019, 0x1760017, 0x18E0015, 0x1A30015, 0x1B80013, 0x1CC0012,
	  0x1DE0011, 0x1F00010, 0x2010010, 0x2110010, 0x221000F, 0x230000F,
	  0x23F000E, 0x24D000E, 0x25B000D, 0x269000C, 0x276000C, 0x283000C,
	  0x28F000C, 0x29B000C, 0x2A7000C, 0x2B3000B, 0x2BF000B, 0x2CA000B,
	  0x2D5000B, 0x2E0000A, 0x2EB000A, 0x2F5000A, 0x2FF000A, 0x30A000A,
	  0x3140009, 0x31E0009, 0x327000A, 0x3310009, 0x33A0009, 0x3440009,
	  0x34D0009, 0x3560009, 0x35F0009, 0x3680008, 0x3710008, 0x3790009,
	  0x3820008, 0x38A0008, 0x3930008, 0x39B0008, 0x3A30008, 0x3AB0008,
	  0x3B30008, 0x3BB0008, 0x3C30008, 0x3CB0007, 0x3D20008, 0x3DA0007,
	  0x3E20007, 0x3E90007, 0x3F00008, 0x3F80007 पूर्ण,
पूर्ण;

#घोषणा ISC_IS_FORMAT_RAW(mbus_code) \
	(((mbus_code) & 0xf000) == 0x3000)

#घोषणा ISC_IS_FORMAT_GREY(mbus_code) \
	(((mbus_code) == MEDIA_BUS_FMT_Y10_1X10) | \
	(((mbus_code) == MEDIA_BUS_FMT_Y8_1X8)))

अटल अंतरभूत व्योम isc_update_v4l2_ctrls(काष्ठा isc_device *isc)
अणु
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;

	/* In here we set the v4l2 controls w.r.t. our pipeline config */
	v4l2_ctrl_s_ctrl(isc->r_gain_ctrl, ctrls->gain[ISC_HIS_CFG_MODE_R]);
	v4l2_ctrl_s_ctrl(isc->b_gain_ctrl, ctrls->gain[ISC_HIS_CFG_MODE_B]);
	v4l2_ctrl_s_ctrl(isc->gr_gain_ctrl, ctrls->gain[ISC_HIS_CFG_MODE_GR]);
	v4l2_ctrl_s_ctrl(isc->gb_gain_ctrl, ctrls->gain[ISC_HIS_CFG_MODE_GB]);

	v4l2_ctrl_s_ctrl(isc->r_off_ctrl, ctrls->offset[ISC_HIS_CFG_MODE_R]);
	v4l2_ctrl_s_ctrl(isc->b_off_ctrl, ctrls->offset[ISC_HIS_CFG_MODE_B]);
	v4l2_ctrl_s_ctrl(isc->gr_off_ctrl, ctrls->offset[ISC_HIS_CFG_MODE_GR]);
	v4l2_ctrl_s_ctrl(isc->gb_off_ctrl, ctrls->offset[ISC_HIS_CFG_MODE_GB]);
पूर्ण

अटल अंतरभूत व्योम isc_update_awb_ctrls(काष्ठा isc_device *isc)
अणु
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;

	/* In here we set our actual hw pipeline config */

	regmap_ग_लिखो(isc->regmap, ISC_WB_O_RGR,
		     ((ctrls->offset[ISC_HIS_CFG_MODE_R])) |
		     ((ctrls->offset[ISC_HIS_CFG_MODE_GR]) << 16));
	regmap_ग_लिखो(isc->regmap, ISC_WB_O_BGB,
		     ((ctrls->offset[ISC_HIS_CFG_MODE_B])) |
		     ((ctrls->offset[ISC_HIS_CFG_MODE_GB]) << 16));
	regmap_ग_लिखो(isc->regmap, ISC_WB_G_RGR,
		     ctrls->gain[ISC_HIS_CFG_MODE_R] |
		     (ctrls->gain[ISC_HIS_CFG_MODE_GR] << 16));
	regmap_ग_लिखो(isc->regmap, ISC_WB_G_BGB,
		     ctrls->gain[ISC_HIS_CFG_MODE_B] |
		     (ctrls->gain[ISC_HIS_CFG_MODE_GB] << 16));
पूर्ण

अटल अंतरभूत व्योम isc_reset_awb_ctrls(काष्ठा isc_device *isc)
अणु
	अचिन्हित पूर्णांक c;

	क्रम (c = ISC_HIS_CFG_MODE_GR; c <= ISC_HIS_CFG_MODE_B; c++) अणु
		/* gains have a fixed poपूर्णांक at 9 decimals */
		isc->ctrls.gain[c] = 1 << 9;
		/* offsets are in 2's complements */
		isc->ctrls.offset[c] = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक isc_रुको_clk_stable(काष्ठा clk_hw *hw)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);
	काष्ठा regmap *regmap = isc_clk->regmap;
	अचिन्हित दीर्घ समयout = jअगरfies + usecs_to_jअगरfies(1000);
	अचिन्हित पूर्णांक status;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		regmap_पढ़ो(regmap, ISC_CLKSR, &status);
		अगर (!(status & ISC_CLKSR_SIP))
			वापस 0;

		usleep_range(10, 250);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक isc_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);

	अगर (isc_clk->id == ISC_ISPCK)
		pm_runसमय_get_sync(isc_clk->dev);

	वापस isc_रुको_clk_stable(hw);
पूर्ण

अटल व्योम isc_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);

	isc_रुको_clk_stable(hw);

	अगर (isc_clk->id == ISC_ISPCK)
		pm_runसमय_put_sync(isc_clk->dev);
पूर्ण

अटल पूर्णांक isc_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);
	u32 id = isc_clk->id;
	काष्ठा regmap *regmap = isc_clk->regmap;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	dev_dbg(isc_clk->dev, "ISC CLK: %s, div = %d, parent id = %d\n",
		__func__, isc_clk->भाग, isc_clk->parent_id);

	spin_lock_irqsave(&isc_clk->lock, flags);
	regmap_update_bits(regmap, ISC_CLKCFG,
			   ISC_CLKCFG_DIV_MASK(id) | ISC_CLKCFG_SEL_MASK(id),
			   (isc_clk->भाग << ISC_CLKCFG_DIV_SHIFT(id)) |
			   (isc_clk->parent_id << ISC_CLKCFG_SEL_SHIFT(id)));

	regmap_ग_लिखो(regmap, ISC_CLKEN, ISC_CLK(id));
	spin_unlock_irqrestore(&isc_clk->lock, flags);

	regmap_पढ़ो(regmap, ISC_CLKSR, &status);
	अगर (status & ISC_CLK(id))
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल व्योम isc_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);
	u32 id = isc_clk->id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&isc_clk->lock, flags);
	regmap_ग_लिखो(isc_clk->regmap, ISC_CLKDIS, ISC_CLK(id));
	spin_unlock_irqrestore(&isc_clk->lock, flags);
पूर्ण

अटल पूर्णांक isc_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);
	u32 status;

	अगर (isc_clk->id == ISC_ISPCK)
		pm_runसमय_get_sync(isc_clk->dev);

	regmap_पढ़ो(isc_clk->regmap, ISC_CLKSR, &status);

	अगर (isc_clk->id == ISC_ISPCK)
		pm_runसमय_put_sync(isc_clk->dev);

	वापस status & ISC_CLK(isc_clk->id) ? 1 : 0;
पूर्ण

अटल अचिन्हित दीर्घ
isc_clk_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);

	वापस DIV_ROUND_CLOSEST(parent_rate, isc_clk->भाग + 1);
पूर्ण

अटल पूर्णांक isc_clk_determine_rate(काष्ठा clk_hw *hw,
				   काष्ठा clk_rate_request *req)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);
	दीर्घ best_rate = -EINVAL;
	पूर्णांक best_dअगरf = -1;
	अचिन्हित पूर्णांक i, भाग;

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		काष्ठा clk_hw *parent;
		अचिन्हित दीर्घ parent_rate;

		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;

		parent_rate = clk_hw_get_rate(parent);
		अगर (!parent_rate)
			जारी;

		क्रम (भाग = 1; भाग < ISC_CLK_MAX_DIV + 2; भाग++) अणु
			अचिन्हित दीर्घ rate;
			पूर्णांक dअगरf;

			rate = DIV_ROUND_CLOSEST(parent_rate, भाग);
			dअगरf = असल(req->rate - rate);

			अगर (best_dअगरf < 0 || best_dअगरf > dअगरf) अणु
				best_rate = rate;
				best_dअगरf = dअगरf;
				req->best_parent_rate = parent_rate;
				req->best_parent_hw = parent;
			पूर्ण

			अगर (!best_dअगरf || rate < req->rate)
				अवरोध;
		पूर्ण

		अगर (!best_dअगरf)
			अवरोध;
	पूर्ण

	dev_dbg(isc_clk->dev,
		"ISC CLK: %s, best_rate = %ld, parent clk: %s @ %ld\n",
		__func__, best_rate,
		__clk_get_name((req->best_parent_hw)->clk),
		req->best_parent_rate);

	अगर (best_rate < 0)
		वापस best_rate;

	req->rate = best_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक isc_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);

	अगर (index >= clk_hw_get_num_parents(hw))
		वापस -EINVAL;

	isc_clk->parent_id = index;

	वापस 0;
पूर्ण

अटल u8 isc_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);

	वापस isc_clk->parent_id;
पूर्ण

अटल पूर्णांक isc_clk_set_rate(काष्ठा clk_hw *hw,
			     अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा isc_clk *isc_clk = to_isc_clk(hw);
	u32 भाग;

	अगर (!rate)
		वापस -EINVAL;

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (भाग > (ISC_CLK_MAX_DIV + 1) || !भाग)
		वापस -EINVAL;

	isc_clk->भाग = भाग - 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops isc_clk_ops = अणु
	.prepare	= isc_clk_prepare,
	.unprepare	= isc_clk_unprepare,
	.enable		= isc_clk_enable,
	.disable	= isc_clk_disable,
	.is_enabled	= isc_clk_is_enabled,
	.recalc_rate	= isc_clk_recalc_rate,
	.determine_rate	= isc_clk_determine_rate,
	.set_parent	= isc_clk_set_parent,
	.get_parent	= isc_clk_get_parent,
	.set_rate	= isc_clk_set_rate,
पूर्ण;

अटल पूर्णांक isc_clk_रेजिस्टर(काष्ठा isc_device *isc, अचिन्हित पूर्णांक id)
अणु
	काष्ठा regmap *regmap = isc->regmap;
	काष्ठा device_node *np = isc->dev->of_node;
	काष्ठा isc_clk *isc_clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *parent_names[3];
	पूर्णांक num_parents;

	num_parents = of_clk_get_parent_count(np);
	अगर (num_parents < 1 || num_parents > 3)
		वापस -EINVAL;

	अगर (num_parents > 2 && id == ISC_ISPCK)
		num_parents = 2;

	of_clk_parent_fill(np, parent_names, num_parents);

	अगर (id == ISC_MCK)
		of_property_पढ़ो_string(np, "clock-output-names", &clk_name);
	अन्यथा
		clk_name = "isc-ispck";

	init.parent_names	= parent_names;
	init.num_parents	= num_parents;
	init.name		= clk_name;
	init.ops		= &isc_clk_ops;
	init.flags		= CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;

	isc_clk = &isc->isc_clks[id];
	isc_clk->hw.init	= &init;
	isc_clk->regmap		= regmap;
	isc_clk->id		= id;
	isc_clk->dev		= isc->dev;
	spin_lock_init(&isc_clk->lock);

	isc_clk->clk = clk_रेजिस्टर(isc->dev, &isc_clk->hw);
	अगर (IS_ERR(isc_clk->clk)) अणु
		dev_err(isc->dev, "%s: clock register fail\n", clk_name);
		वापस PTR_ERR(isc_clk->clk);
	पूर्ण अन्यथा अगर (id == ISC_MCK)
		of_clk_add_provider(np, of_clk_src_simple_get, isc_clk->clk);

	वापस 0;
पूर्ण

पूर्णांक isc_clk_init(काष्ठा isc_device *isc)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(isc->isc_clks); i++)
		isc->isc_clks[i].clk = ERR_PTR(-EINVAL);

	क्रम (i = 0; i < ARRAY_SIZE(isc->isc_clks); i++) अणु
		ret = isc_clk_रेजिस्टर(isc, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम isc_clk_cleanup(काष्ठा isc_device *isc)
अणु
	अचिन्हित पूर्णांक i;

	of_clk_del_provider(isc->dev->of_node);

	क्रम (i = 0; i < ARRAY_SIZE(isc->isc_clks); i++) अणु
		काष्ठा isc_clk *isc_clk = &isc->isc_clks[i];

		अगर (!IS_ERR(isc_clk->clk))
			clk_unरेजिस्टर(isc_clk->clk);
	पूर्ण
पूर्ण

अटल पूर्णांक isc_queue_setup(काष्ठा vb2_queue *vq,
			    अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			    अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा isc_device *isc = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size = isc->fmt.fmt.pix.sizeimage;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल पूर्णांक isc_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा isc_device *isc = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size = isc->fmt.fmt.pix.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		v4l2_err(&isc->v4l2_dev, "buffer too small (%lu < %lu)\n",
			 vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);

	vbuf->field = isc->fmt.fmt.pix.field;

	वापस 0;
पूर्ण

अटल व्योम isc_start_dma(काष्ठा isc_device *isc)
अणु
	काष्ठा regmap *regmap = isc->regmap;
	u32 sizeimage = isc->fmt.fmt.pix.sizeimage;
	u32 dctrl_dview;
	dma_addr_t addr0;
	u32 h, w;

	h = isc->fmt.fmt.pix.height;
	w = isc->fmt.fmt.pix.width;

	/*
	 * In हाल the sensor is not RAW, it will output a pixel (12-16 bits)
	 * with two samples on the ISC Data bus (which is 8-12)
	 * ISC will count each sample, so, we need to multiply these values
	 * by two, to get the real number of samples क्रम the required pixels.
	 */
	अगर (!ISC_IS_FORMAT_RAW(isc->config.sd_क्रमmat->mbus_code)) अणु
		h <<= 1;
		w <<= 1;
	पूर्ण

	/*
	 * We limit the column/row count that the ISC will output according
	 * to the configured resolution that we want.
	 * This will aव्योम the situation where the sensor is misconfigured,
	 * sending more data, and the ISC will just take it and DMA to memory,
	 * causing corruption.
	 */
	regmap_ग_लिखो(regmap, ISC_PFE_CFG1,
		     (ISC_PFE_CFG1_COLMIN(0) & ISC_PFE_CFG1_COLMIN_MASK) |
		     (ISC_PFE_CFG1_COLMAX(w - 1) & ISC_PFE_CFG1_COLMAX_MASK));

	regmap_ग_लिखो(regmap, ISC_PFE_CFG2,
		     (ISC_PFE_CFG2_ROWMIN(0) & ISC_PFE_CFG2_ROWMIN_MASK) |
		     (ISC_PFE_CFG2_ROWMAX(h - 1) & ISC_PFE_CFG2_ROWMAX_MASK));

	regmap_update_bits(regmap, ISC_PFE_CFG0,
			   ISC_PFE_CFG0_COLEN | ISC_PFE_CFG0_ROWEN,
			   ISC_PFE_CFG0_COLEN | ISC_PFE_CFG0_ROWEN);

	addr0 = vb2_dma_contig_plane_dma_addr(&isc->cur_frm->vb.vb2_buf, 0);
	regmap_ग_लिखो(regmap, ISC_DAD0, addr0);

	चयन (isc->config.fourcc) अणु
	हाल V4L2_PIX_FMT_YUV420:
		regmap_ग_लिखो(regmap, ISC_DAD1, addr0 + (sizeimage * 2) / 3);
		regmap_ग_लिखो(regmap, ISC_DAD2, addr0 + (sizeimage * 5) / 6);
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		regmap_ग_लिखो(regmap, ISC_DAD1, addr0 + sizeimage / 2);
		regmap_ग_लिखो(regmap, ISC_DAD2, addr0 + (sizeimage * 3) / 4);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dctrl_dview = isc->config.dctrl_dview;

	regmap_ग_लिखो(regmap, ISC_DCTRL, dctrl_dview | ISC_DCTRL_IE_IS);
	spin_lock(&isc->awb_lock);
	regmap_ग_लिखो(regmap, ISC_CTRLEN, ISC_CTRL_CAPTURE);
	spin_unlock(&isc->awb_lock);
पूर्ण

अटल व्योम isc_set_pipeline(काष्ठा isc_device *isc, u32 pipeline)
अणु
	काष्ठा regmap *regmap = isc->regmap;
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;
	u32 val, bay_cfg;
	स्थिर u32 *gamma;
	अचिन्हित पूर्णांक i;

	/* WB-->CFA-->CC-->GAM-->CSC-->CBC-->SUB422-->SUB420 */
	क्रम (i = 0; i < ISC_PIPE_LINE_NODE_NUM; i++) अणु
		val = pipeline & BIT(i) ? 1 : 0;
		regmap_field_ग_लिखो(isc->pipeline[i], val);
	पूर्ण

	अगर (!pipeline)
		वापस;

	bay_cfg = isc->config.sd_क्रमmat->cfa_baycfg;

	regmap_ग_लिखो(regmap, ISC_WB_CFG, bay_cfg);
	isc_update_awb_ctrls(isc);
	isc_update_v4l2_ctrls(isc);

	regmap_ग_लिखो(regmap, ISC_CFA_CFG, bay_cfg | ISC_CFA_CFG_EITPOL);

	gamma = &isc_gamma_table[ctrls->gamma_index][0];
	regmap_bulk_ग_लिखो(regmap, ISC_GAM_BENTRY, gamma, GAMMA_ENTRIES);
	regmap_bulk_ग_लिखो(regmap, ISC_GAM_GENTRY, gamma, GAMMA_ENTRIES);
	regmap_bulk_ग_लिखो(regmap, ISC_GAM_RENTRY, gamma, GAMMA_ENTRIES);

	/* Convert RGB to YUV */
	regmap_ग_लिखो(regmap, ISC_CSC_YR_YG, 0x42 | (0x81 << 16));
	regmap_ग_लिखो(regmap, ISC_CSC_YB_OY, 0x19 | (0x10 << 16));
	regmap_ग_लिखो(regmap, ISC_CSC_CBR_CBG, 0xFDA | (0xFB6 << 16));
	regmap_ग_लिखो(regmap, ISC_CSC_CBB_OCB, 0x70 | (0x80 << 16));
	regmap_ग_लिखो(regmap, ISC_CSC_CRR_CRG, 0x70 | (0xFA2 << 16));
	regmap_ग_लिखो(regmap, ISC_CSC_CRB_OCR, 0xFEE | (0x80 << 16));

	regmap_ग_लिखो(regmap, ISC_CBC_BRIGHT, ctrls->brightness);
	regmap_ग_लिखो(regmap, ISC_CBC_CONTRAST, ctrls->contrast);
पूर्ण

अटल पूर्णांक isc_update_profile(काष्ठा isc_device *isc)
अणु
	काष्ठा regmap *regmap = isc->regmap;
	u32 sr;
	पूर्णांक counter = 100;

	regmap_ग_लिखो(regmap, ISC_CTRLEN, ISC_CTRL_UPPRO);

	regmap_पढ़ो(regmap, ISC_CTRLSR, &sr);
	जबतक ((sr & ISC_CTRL_UPPRO) && counter--) अणु
		usleep_range(1000, 2000);
		regmap_पढ़ो(regmap, ISC_CTRLSR, &sr);
	पूर्ण

	अगर (counter < 0) अणु
		v4l2_warn(&isc->v4l2_dev, "Time out to update profile\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम isc_set_histogram(काष्ठा isc_device *isc, bool enable)
अणु
	काष्ठा regmap *regmap = isc->regmap;
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;

	अगर (enable) अणु
		regmap_ग_लिखो(regmap, ISC_HIS_CFG,
			     ISC_HIS_CFG_MODE_GR |
			     (isc->config.sd_क्रमmat->cfa_baycfg
					<< ISC_HIS_CFG_BAYSEL_SHIFT) |
					ISC_HIS_CFG_RAR);
		regmap_ग_लिखो(regmap, ISC_HIS_CTRL, ISC_HIS_CTRL_EN);
		regmap_ग_लिखो(regmap, ISC_INTEN, ISC_INT_HISDONE);
		ctrls->hist_id = ISC_HIS_CFG_MODE_GR;
		isc_update_profile(isc);
		regmap_ग_लिखो(regmap, ISC_CTRLEN, ISC_CTRL_HISREQ);

		ctrls->hist_stat = HIST_ENABLED;
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(regmap, ISC_INTDIS, ISC_INT_HISDONE);
		regmap_ग_लिखो(regmap, ISC_HIS_CTRL, ISC_HIS_CTRL_DIS);

		ctrls->hist_stat = HIST_DISABLED;
	पूर्ण
पूर्ण

अटल पूर्णांक isc_configure(काष्ठा isc_device *isc)
अणु
	काष्ठा regmap *regmap = isc->regmap;
	u32 pfe_cfg0, rlp_mode, dcfg, mask, pipeline;
	काष्ठा isc_subdev_entity *subdev = isc->current_subdev;

	pfe_cfg0 = isc->config.sd_क्रमmat->pfe_cfg0_bps;
	rlp_mode = isc->config.rlp_cfg_mode;
	pipeline = isc->config.bits_pipeline;

	dcfg = isc->config.dcfg_imode |
		       ISC_DCFG_YMBSIZE_BEATS8 | ISC_DCFG_CMBSIZE_BEATS8;

	pfe_cfg0  |= subdev->pfe_cfg0 | ISC_PFE_CFG0_MODE_PROGRESSIVE;
	mask = ISC_PFE_CFG0_BPS_MASK | ISC_PFE_CFG0_HPOL_LOW |
	       ISC_PFE_CFG0_VPOL_LOW | ISC_PFE_CFG0_PPOL_LOW |
	       ISC_PFE_CFG0_MODE_MASK | ISC_PFE_CFG0_CCIR_CRC |
		   ISC_PFE_CFG0_CCIR656;

	regmap_update_bits(regmap, ISC_PFE_CFG0, mask, pfe_cfg0);

	regmap_update_bits(regmap, ISC_RLP_CFG, ISC_RLP_CFG_MODE_MASK,
			   rlp_mode);

	regmap_ग_लिखो(regmap, ISC_DCFG, dcfg);

	/* Set the pipeline */
	isc_set_pipeline(isc, pipeline);

	/*
	 * The current implemented histogram is available क्रम RAW R, B, GB, GR
	 * channels. We need to check अगर sensor is outputting RAW BAYER
	 */
	अगर (isc->ctrls.awb &&
	    ISC_IS_FORMAT_RAW(isc->config.sd_क्रमmat->mbus_code))
		isc_set_histogram(isc, true);
	अन्यथा
		isc_set_histogram(isc, false);

	/* Update profile */
	वापस isc_update_profile(isc);
पूर्ण

अटल पूर्णांक isc_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा isc_device *isc = vb2_get_drv_priv(vq);
	काष्ठा regmap *regmap = isc->regmap;
	काष्ठा isc_buffer *buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Enable stream on the sub device */
	ret = v4l2_subdev_call(isc->current_subdev->sd, video, s_stream, 1);
	अगर (ret && ret != -ENOIOCTLCMD) अणु
		v4l2_err(&isc->v4l2_dev, "stream on failed in subdev %d\n",
			 ret);
		जाओ err_start_stream;
	पूर्ण

	pm_runसमय_get_sync(isc->dev);

	ret = isc_configure(isc);
	अगर (unlikely(ret))
		जाओ err_configure;

	/* Enable DMA पूर्णांकerrupt */
	regmap_ग_लिखो(regmap, ISC_INTEN, ISC_INT_DDONE);

	spin_lock_irqsave(&isc->dma_queue_lock, flags);

	isc->sequence = 0;
	isc->stop = false;
	reinit_completion(&isc->comp);

	isc->cur_frm = list_first_entry(&isc->dma_queue,
					काष्ठा isc_buffer, list);
	list_del(&isc->cur_frm->list);

	isc_start_dma(isc);

	spin_unlock_irqrestore(&isc->dma_queue_lock, flags);

	/* अगर we streaming from RAW, we can करो one-shot white balance adj */
	अगर (ISC_IS_FORMAT_RAW(isc->config.sd_क्रमmat->mbus_code))
		v4l2_ctrl_activate(isc->करो_wb_ctrl, true);

	वापस 0;

err_configure:
	pm_runसमय_put_sync(isc->dev);

	v4l2_subdev_call(isc->current_subdev->sd, video, s_stream, 0);

err_start_stream:
	spin_lock_irqsave(&isc->dma_queue_lock, flags);
	list_क्रम_each_entry(buf, &isc->dma_queue, list)
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	INIT_LIST_HEAD(&isc->dma_queue);
	spin_unlock_irqrestore(&isc->dma_queue_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम isc_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा isc_device *isc = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ flags;
	काष्ठा isc_buffer *buf;
	पूर्णांक ret;

	v4l2_ctrl_activate(isc->करो_wb_ctrl, false);

	isc->stop = true;

	/* Wait until the end of the current frame */
	अगर (isc->cur_frm && !रुको_क्रम_completion_समयout(&isc->comp, 5 * HZ))
		v4l2_err(&isc->v4l2_dev,
			 "Timeout waiting for end of the capture\n");

	/* Disable DMA पूर्णांकerrupt */
	regmap_ग_लिखो(isc->regmap, ISC_INTDIS, ISC_INT_DDONE);

	pm_runसमय_put_sync(isc->dev);

	/* Disable stream on the sub device */
	ret = v4l2_subdev_call(isc->current_subdev->sd, video, s_stream, 0);
	अगर (ret && ret != -ENOIOCTLCMD)
		v4l2_err(&isc->v4l2_dev, "stream off failed in subdev\n");

	/* Release all active buffers */
	spin_lock_irqsave(&isc->dma_queue_lock, flags);
	अगर (unlikely(isc->cur_frm)) अणु
		vb2_buffer_करोne(&isc->cur_frm->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
		isc->cur_frm = शून्य;
	पूर्ण
	list_क्रम_each_entry(buf, &isc->dma_queue, list)
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	INIT_LIST_HEAD(&isc->dma_queue);
	spin_unlock_irqrestore(&isc->dma_queue_lock, flags);
पूर्ण

अटल व्योम isc_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा isc_buffer *buf = container_of(vbuf, काष्ठा isc_buffer, vb);
	काष्ठा isc_device *isc = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&isc->dma_queue_lock, flags);
	अगर (!isc->cur_frm && list_empty(&isc->dma_queue) &&
		vb2_is_streaming(vb->vb2_queue)) अणु
		isc->cur_frm = buf;
		isc_start_dma(isc);
	पूर्ण अन्यथा
		list_add_tail(&buf->list, &isc->dma_queue);
	spin_unlock_irqrestore(&isc->dma_queue_lock, flags);
पूर्ण

अटल काष्ठा isc_क्रमmat *find_क्रमmat_by_fourcc(काष्ठा isc_device *isc,
						 अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक num_क्रमmats = isc->num_user_क्रमmats;
	काष्ठा isc_क्रमmat *fmt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_क्रमmats; i++) अणु
		fmt = isc->user_क्रमmats[i];
		अगर (fmt->fourcc == fourcc)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा vb2_ops isc_vb2_ops = अणु
	.queue_setup		= isc_queue_setup,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.buf_prepare		= isc_buffer_prepare,
	.start_streaming	= isc_start_streaming,
	.stop_streaming		= isc_stop_streaming,
	.buf_queue		= isc_buffer_queue,
पूर्ण;

अटल पूर्णांक isc_querycap(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_capability *cap)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);

	strscpy(cap->driver, ATMEL_ISC_NAME, माप(cap->driver));
	strscpy(cap->card, "Atmel Image Sensor Controller", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", isc->v4l2_dev.name);

	वापस 0;
पूर्ण

अटल पूर्णांक isc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_fmtdesc *f)
अणु
	u32 index = f->index;
	u32 i, supported_index;

	अगर (index < ARRAY_SIZE(controller_क्रमmats)) अणु
		f->pixelक्रमmat = controller_क्रमmats[index].fourcc;
		वापस 0;
	पूर्ण

	index -= ARRAY_SIZE(controller_क्रमmats);

	i = 0;
	supported_index = 0;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats_list); i++) अणु
		अगर (!ISC_IS_FORMAT_RAW(क्रमmats_list[i].mbus_code) ||
		    !क्रमmats_list[i].sd_support)
			जारी;
		अगर (supported_index == index) अणु
			f->pixelक्रमmat = क्रमmats_list[i].fourcc;
			वापस 0;
		पूर्ण
		supported_index++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक isc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);

	*fmt = isc->fmt;

	वापस 0;
पूर्ण

/*
 * Checks the current configured क्रमmat, अगर ISC can output it,
 * considering which type of क्रमmat the ISC receives from the sensor
 */
अटल पूर्णांक isc_try_validate_क्रमmats(काष्ठा isc_device *isc)
अणु
	पूर्णांक ret;
	bool bayer = false, yuv = false, rgb = false, grey = false;

	/* all क्रमmats supported by the RLP module are OK */
	चयन (isc->try_config.fourcc) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SRGGB10:
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SRGGB12:
		ret = 0;
		bayer = true;
		अवरोध;

	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_YUYV:
		ret = 0;
		yuv = true;
		अवरोध;

	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_ABGR32:
	हाल V4L2_PIX_FMT_XBGR32:
	हाल V4L2_PIX_FMT_ARGB444:
	हाल V4L2_PIX_FMT_ARGB555:
		ret = 0;
		rgb = true;
		अवरोध;
	हाल V4L2_PIX_FMT_GREY:
	हाल V4L2_PIX_FMT_Y10:
		ret = 0;
		grey = true;
		अवरोध;
	शेष:
	/* any other dअगरferent क्रमmats are not supported */
		ret = -EINVAL;
	पूर्ण
	v4l2_dbg(1, debug, &isc->v4l2_dev,
		 "Format validation, requested rgb=%u, yuv=%u, grey=%u, bayer=%u\n",
		 rgb, yuv, grey, bayer);

	/* we cannot output RAW अगर we करो not receive RAW */
	अगर ((bayer) && !ISC_IS_FORMAT_RAW(isc->try_config.sd_क्रमmat->mbus_code))
		वापस -EINVAL;

	/* we cannot output GREY अगर we करो not receive RAW/GREY */
	अगर (grey && !ISC_IS_FORMAT_RAW(isc->try_config.sd_क्रमmat->mbus_code) &&
	    !ISC_IS_FORMAT_GREY(isc->try_config.sd_क्रमmat->mbus_code))
		वापस -EINVAL;

	वापस ret;
पूर्ण

/*
 * Configures the RLP and DMA modules, depending on the output क्रमmat
 * configured क्रम the ISC.
 * If direct_dump == true, just dump raw data 8/16 bits depending on क्रमmat.
 */
अटल पूर्णांक isc_try_configure_rlp_dma(काष्ठा isc_device *isc, bool direct_dump)
अणु
	चयन (isc->try_config.fourcc) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DAT8;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 8;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SRGGB10:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DAT10;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SRGGB12:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DAT12;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_RGB565;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_ARGB444:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_ARGB444;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_ARGB555:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_ARGB555;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_ABGR32:
	हाल V4L2_PIX_FMT_XBGR32:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_ARGB32;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED32;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 32;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_YYCC;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_YC420P;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PLANAR;
		isc->try_config.bpp = 12;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_YYCC;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_YC422P;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PLANAR;
		isc->try_config.bpp = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_YYCC;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED32;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		अवरोध;
	हाल V4L2_PIX_FMT_GREY:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DATY8;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 8;
		अवरोध;
	हाल V4L2_PIX_FMT_Y10:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DATY10;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (direct_dump) अणु
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DAT8;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Configuring pipeline modules, depending on which क्रमmat the ISC outमाला_दो
 * and considering which क्रमmat it has as input from the sensor.
 */
अटल पूर्णांक isc_try_configure_pipeline(काष्ठा isc_device *isc)
अणु
	चयन (isc->try_config.fourcc) अणु
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_ARGB555:
	हाल V4L2_PIX_FMT_ARGB444:
	हाल V4L2_PIX_FMT_ABGR32:
	हाल V4L2_PIX_FMT_XBGR32:
		/* अगर sensor क्रमmat is RAW, we convert inside ISC */
		अगर (ISC_IS_FORMAT_RAW(isc->try_config.sd_क्रमmat->mbus_code)) अणु
			isc->try_config.bits_pipeline = CFA_ENABLE |
				WB_ENABLE | GAM_ENABLES;
		पूर्ण अन्यथा अणु
			isc->try_config.bits_pipeline = 0x0;
		पूर्ण
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
		/* अगर sensor क्रमmat is RAW, we convert inside ISC */
		अगर (ISC_IS_FORMAT_RAW(isc->try_config.sd_क्रमmat->mbus_code)) अणु
			isc->try_config.bits_pipeline = CFA_ENABLE |
				CSC_ENABLE | WB_ENABLE | GAM_ENABLES |
				SUB420_ENABLE | SUB422_ENABLE | CBC_ENABLE;
		पूर्ण अन्यथा अणु
			isc->try_config.bits_pipeline = 0x0;
		पूर्ण
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		/* अगर sensor क्रमmat is RAW, we convert inside ISC */
		अगर (ISC_IS_FORMAT_RAW(isc->try_config.sd_क्रमmat->mbus_code)) अणु
			isc->try_config.bits_pipeline = CFA_ENABLE |
				CSC_ENABLE | WB_ENABLE | GAM_ENABLES |
				SUB422_ENABLE | CBC_ENABLE;
		पूर्ण अन्यथा अणु
			isc->try_config.bits_pipeline = 0x0;
		पूर्ण
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		/* अगर sensor क्रमmat is RAW, we convert inside ISC */
		अगर (ISC_IS_FORMAT_RAW(isc->try_config.sd_क्रमmat->mbus_code)) अणु
			isc->try_config.bits_pipeline = CFA_ENABLE |
				CSC_ENABLE | WB_ENABLE | GAM_ENABLES |
				SUB422_ENABLE | CBC_ENABLE;
		पूर्ण अन्यथा अणु
			isc->try_config.bits_pipeline = 0x0;
		पूर्ण
		अवरोध;
	हाल V4L2_PIX_FMT_GREY:
		अगर (ISC_IS_FORMAT_RAW(isc->try_config.sd_क्रमmat->mbus_code)) अणु
		/* अगर sensor क्रमmat is RAW, we convert inside ISC */
			isc->try_config.bits_pipeline = CFA_ENABLE |
				CSC_ENABLE | WB_ENABLE | GAM_ENABLES |
				CBC_ENABLE;
		पूर्ण अन्यथा अणु
			isc->try_config.bits_pipeline = 0x0;
		पूर्ण
		अवरोध;
	शेष:
		isc->try_config.bits_pipeline = 0x0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम isc_try_fse(काष्ठा isc_device *isc,
			काष्ठा v4l2_subdev_pad_config *pad_cfg)
अणु
	पूर्णांक ret;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणुपूर्ण;

	/*
	 * If we करो not know yet which क्रमmat the subdev is using, we cannot
	 * करो anything.
	 */
	अगर (!isc->try_config.sd_क्रमmat)
		वापस;

	fse.code = isc->try_config.sd_क्रमmat->mbus_code;
	fse.which = V4L2_SUBDEV_FORMAT_TRY;

	ret = v4l2_subdev_call(isc->current_subdev->sd, pad, क्रमागत_frame_size,
			       pad_cfg, &fse);
	/*
	 * Attempt to obtain क्रमmat size from subdev. If not available,
	 * just use the maximum ISC can receive.
	 */
	अगर (ret) अणु
		pad_cfg->try_crop.width = ISC_MAX_SUPPORT_WIDTH;
		pad_cfg->try_crop.height = ISC_MAX_SUPPORT_HEIGHT;
	पूर्ण अन्यथा अणु
		pad_cfg->try_crop.width = fse.max_width;
		pad_cfg->try_crop.height = fse.max_height;
	पूर्ण
पूर्ण

अटल पूर्णांक isc_try_fmt(काष्ठा isc_device *isc, काष्ठा v4l2_क्रमmat *f,
			u32 *code)
अणु
	पूर्णांक i;
	काष्ठा isc_क्रमmat *sd_fmt = शून्य, *direct_fmt = शून्य;
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &f->fmt.pix;
	काष्ठा v4l2_subdev_pad_config pad_cfg = अणुपूर्ण;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	u32 mbus_code;
	पूर्णांक ret;
	bool rlp_dma_direct_dump = false;

	अगर (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	/* Step 1: find a RAW क्रमmat that is supported */
	क्रम (i = 0; i < isc->num_user_क्रमmats; i++) अणु
		अगर (ISC_IS_FORMAT_RAW(isc->user_क्रमmats[i]->mbus_code)) अणु
			sd_fmt = isc->user_क्रमmats[i];
			अवरोध;
		पूर्ण
	पूर्ण
	/* Step 2: We can जारी with this RAW क्रमmat, or we can look
	 * क्रम better: maybe sensor supports directly what we need.
	 */
	direct_fmt = find_क्रमmat_by_fourcc(isc, pixfmt->pixelक्रमmat);

	/* Step 3: We have both. We decide given the module parameter which
	 * one to use.
	 */
	अगर (direct_fmt && sd_fmt && sensor_preferred)
		sd_fmt = direct_fmt;

	/* Step 4: we करो not have RAW but we have a direct क्रमmat. Use it. */
	अगर (direct_fmt && !sd_fmt)
		sd_fmt = direct_fmt;

	/* Step 5: अगर we are using a direct क्रमmat, we need to package
	 * everything as 8 bit data and just dump it
	 */
	अगर (sd_fmt == direct_fmt)
		rlp_dma_direct_dump = true;

	/* Step 6: We have no क्रमmat. This can happen अगर the userspace
	 * requests some weird/invalid क्रमmat.
	 * In this हाल, शेष to whatever we have
	 */
	अगर (!sd_fmt && !direct_fmt) अणु
		sd_fmt = isc->user_क्रमmats[isc->num_user_क्रमmats - 1];
		v4l2_dbg(1, debug, &isc->v4l2_dev,
			 "Sensor not supporting %.4s, using %.4s\n",
			 (अक्षर *)&pixfmt->pixelक्रमmat, (अक्षर *)&sd_fmt->fourcc);
	पूर्ण

	अगर (!sd_fmt) अणु
		ret = -EINVAL;
		जाओ isc_try_fmt_err;
	पूर्ण

	/* Step 7: Prपूर्णांक out what we decided क्रम debugging */
	v4l2_dbg(1, debug, &isc->v4l2_dev,
		 "Preferring to have sensor using format %.4s\n",
		 (अक्षर *)&sd_fmt->fourcc);

	/* Step 8: at this moment we decided which क्रमmat the subdev will use */
	isc->try_config.sd_क्रमmat = sd_fmt;

	/* Limit to Aपंचांगel ISC hardware capabilities */
	अगर (pixfmt->width > ISC_MAX_SUPPORT_WIDTH)
		pixfmt->width = ISC_MAX_SUPPORT_WIDTH;
	अगर (pixfmt->height > ISC_MAX_SUPPORT_HEIGHT)
		pixfmt->height = ISC_MAX_SUPPORT_HEIGHT;

	/*
	 * The mbus क्रमmat is the one the subdev outमाला_दो.
	 * The pixels will be transferred in this क्रमmat Sensor -> ISC
	 */
	mbus_code = sd_fmt->mbus_code;

	/*
	 * Validate क्रमmats. If the required क्रमmat is not OK, शेष to raw.
	 */

	isc->try_config.fourcc = pixfmt->pixelक्रमmat;

	अगर (isc_try_validate_क्रमmats(isc)) अणु
		pixfmt->pixelक्रमmat = isc->try_config.fourcc = sd_fmt->fourcc;
		/* Re-try to validate the new क्रमmat */
		ret = isc_try_validate_क्रमmats(isc);
		अगर (ret)
			जाओ isc_try_fmt_err;
	पूर्ण

	ret = isc_try_configure_rlp_dma(isc, rlp_dma_direct_dump);
	अगर (ret)
		जाओ isc_try_fmt_err;

	ret = isc_try_configure_pipeline(isc);
	अगर (ret)
		जाओ isc_try_fmt_err;

	/* Obtain frame sizes अगर possible to have crop requirements पढ़ोy */
	isc_try_fse(isc, &pad_cfg);

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, pixfmt, mbus_code);
	ret = v4l2_subdev_call(isc->current_subdev->sd, pad, set_fmt,
			       &pad_cfg, &क्रमmat);
	अगर (ret < 0)
		जाओ isc_try_fmt_subdev_err;

	v4l2_fill_pix_क्रमmat(pixfmt, &क्रमmat.क्रमmat);

	pixfmt->field = V4L2_FIELD_NONE;
	pixfmt->bytesperline = (pixfmt->width * isc->try_config.bpp) >> 3;
	pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	अगर (code)
		*code = mbus_code;

	वापस 0;

isc_try_fmt_err:
	v4l2_err(&isc->v4l2_dev, "Could not find any possible format for a working pipeline\n");
isc_try_fmt_subdev_err:
	स_रखो(&isc->try_config, 0, माप(isc->try_config));

	वापस ret;
पूर्ण

अटल पूर्णांक isc_set_fmt(काष्ठा isc_device *isc, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	u32 mbus_code = 0;
	पूर्णांक ret;

	ret = isc_try_fmt(isc, f, &mbus_code);
	अगर (ret)
		वापस ret;

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, &f->fmt.pix, mbus_code);
	ret = v4l2_subdev_call(isc->current_subdev->sd, pad,
			       set_fmt, शून्य, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	isc->fmt = *f;

	अगर (isc->try_config.sd_क्रमmat && isc->config.sd_क्रमmat &&
	    isc->try_config.sd_क्रमmat != isc->config.sd_क्रमmat) अणु
		isc->ctrls.hist_stat = HIST_INIT;
		isc_reset_awb_ctrls(isc);
		isc_update_v4l2_ctrls(isc);
	पूर्ण
	/* make the try configuration active */
	isc->config = isc->try_config;

	v4l2_dbg(1, debug, &isc->v4l2_dev, "New ISC configuration in place\n");

	वापस 0;
पूर्ण

अटल पूर्णांक isc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);

	अगर (vb2_is_streaming(&isc->vb2_vidq))
		वापस -EBUSY;

	वापस isc_set_fmt(isc, f);
पूर्ण

अटल पूर्णांक isc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);

	वापस isc_try_fmt(isc, f, शून्य);
पूर्ण

अटल पूर्णांक isc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_input *inp)
अणु
	अगर (inp->index != 0)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = 0;
	strscpy(inp->name, "Camera", माप(inp->name));

	वापस 0;
पूर्ण

अटल पूर्णांक isc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक isc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i > 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक isc_g_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);

	वापस v4l2_g_parm_cap(video_devdata(file), isc->current_subdev->sd, a);
पूर्ण

अटल पूर्णांक isc_s_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);

	वापस v4l2_s_parm_cap(video_devdata(file), isc->current_subdev->sd, a);
पूर्ण

अटल पूर्णांक isc_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.code = isc->config.sd_क्रमmat->mbus_code,
		.index = fsize->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < isc->num_user_क्रमmats; i++)
		अगर (isc->user_क्रमmats[i]->fourcc == fsize->pixel_क्रमmat)
			ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(controller_क्रमmats); i++)
		अगर (controller_क्रमmats[i].fourcc == fsize->pixel_क्रमmat)
			ret = 0;

	अगर (ret)
		वापस ret;

	ret = v4l2_subdev_call(isc->current_subdev->sd, pad, क्रमागत_frame_size,
			       शून्य, &fse);
	अगर (ret)
		वापस ret;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक isc_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.code = isc->config.sd_क्रमmat->mbus_code,
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret = -EINVAL;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < isc->num_user_क्रमmats; i++)
		अगर (isc->user_क्रमmats[i]->fourcc == fival->pixel_क्रमmat)
			ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(controller_क्रमmats); i++)
		अगर (controller_क्रमmats[i].fourcc == fival->pixel_क्रमmat)
			ret = 0;

	अगर (ret)
		वापस ret;

	ret = v4l2_subdev_call(isc->current_subdev->sd, pad,
			       क्रमागत_frame_पूर्णांकerval, शून्य, &fie);
	अगर (ret)
		वापस ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.पूर्णांकerval;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops isc_ioctl_ops = अणु
	.vidioc_querycap		= isc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= isc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= isc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= isc_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= isc_try_fmt_vid_cap,

	.vidioc_क्रमागत_input		= isc_क्रमागत_input,
	.vidioc_g_input			= isc_g_input,
	.vidioc_s_input			= isc_s_input,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_g_parm			= isc_g_parm,
	.vidioc_s_parm			= isc_s_parm,
	.vidioc_क्रमागत_framesizes		= isc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= isc_क्रमागत_frameपूर्णांकervals,

	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल पूर्णांक isc_खोलो(काष्ठा file *file)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = isc->current_subdev->sd;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&isc->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(file);
	अगर (ret < 0)
		जाओ unlock;

	अगर (!v4l2_fh_is_singular_file(file))
		जाओ unlock;

	ret = v4l2_subdev_call(sd, core, s_घातer, 1);
	अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
		v4l2_fh_release(file);
		जाओ unlock;
	पूर्ण

	ret = isc_set_fmt(isc, &isc->fmt);
	अगर (ret) अणु
		v4l2_subdev_call(sd, core, s_घातer, 0);
		v4l2_fh_release(file);
	पूर्ण

unlock:
	mutex_unlock(&isc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक isc_release(काष्ठा file *file)
अणु
	काष्ठा isc_device *isc = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = isc->current_subdev->sd;
	bool fh_singular;
	पूर्णांक ret;

	mutex_lock(&isc->lock);

	fh_singular = v4l2_fh_is_singular_file(file);

	ret = _vb2_fop_release(file, शून्य);

	अगर (fh_singular)
		v4l2_subdev_call(sd, core, s_घातer, 0);

	mutex_unlock(&isc->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations isc_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= isc_खोलो,
	.release	= isc_release,
	.unlocked_ioctl	= video_ioctl2,
	.पढ़ो		= vb2_fop_पढ़ो,
	.mmap		= vb2_fop_mmap,
	.poll		= vb2_fop_poll,
पूर्ण;

irqवापस_t isc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा isc_device *isc = (काष्ठा isc_device *)dev_id;
	काष्ठा regmap *regmap = isc->regmap;
	u32 isc_पूर्णांकsr, isc_पूर्णांकmask, pending;
	irqवापस_t ret = IRQ_NONE;

	regmap_पढ़ो(regmap, ISC_INTSR, &isc_पूर्णांकsr);
	regmap_पढ़ो(regmap, ISC_INTMASK, &isc_पूर्णांकmask);

	pending = isc_पूर्णांकsr & isc_पूर्णांकmask;

	अगर (likely(pending & ISC_INT_DDONE)) अणु
		spin_lock(&isc->dma_queue_lock);
		अगर (isc->cur_frm) अणु
			काष्ठा vb2_v4l2_buffer *vbuf = &isc->cur_frm->vb;
			काष्ठा vb2_buffer *vb = &vbuf->vb2_buf;

			vb->बारtamp = kसमय_get_ns();
			vbuf->sequence = isc->sequence++;
			vb2_buffer_करोne(vb, VB2_BUF_STATE_DONE);
			isc->cur_frm = शून्य;
		पूर्ण

		अगर (!list_empty(&isc->dma_queue) && !isc->stop) अणु
			isc->cur_frm = list_first_entry(&isc->dma_queue,
						     काष्ठा isc_buffer, list);
			list_del(&isc->cur_frm->list);

			isc_start_dma(isc);
		पूर्ण

		अगर (isc->stop)
			complete(&isc->comp);

		ret = IRQ_HANDLED;
		spin_unlock(&isc->dma_queue_lock);
	पूर्ण

	अगर (pending & ISC_INT_HISDONE) अणु
		schedule_work(&isc->awb_work);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम isc_hist_count(काष्ठा isc_device *isc, u32 *min, u32 *max)
अणु
	काष्ठा regmap *regmap = isc->regmap;
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;
	u32 *hist_count = &ctrls->hist_count[ctrls->hist_id];
	u32 *hist_entry = &ctrls->hist_entry[0];
	u32 i;

	*min = 0;
	*max = HIST_ENTRIES;

	regmap_bulk_पढ़ो(regmap, ISC_HIS_ENTRY, hist_entry, HIST_ENTRIES);

	*hist_count = 0;
	/*
	 * we deliberately ignore the end of the histogram,
	 * the most white pixels
	 */
	क्रम (i = 1; i < HIST_ENTRIES; i++) अणु
		अगर (*hist_entry && !*min)
			*min = i;
		अगर (*hist_entry)
			*max = i;
		*hist_count += i * (*hist_entry++);
	पूर्ण

	अगर (!*min)
		*min = 1;
पूर्ण

अटल व्योम isc_wb_update(काष्ठा isc_ctrls *ctrls)
अणु
	u32 *hist_count = &ctrls->hist_count[0];
	u32 c, offset[4];
	u64 avg = 0;
	/* We compute two gains, stretch gain and grey world gain */
	u32 s_gain[4], gw_gain[4];

	/*
	 * According to Grey World, we need to set gains क्रम R/B to normalize
	 * them towards the green channel.
	 * Thus we want to keep Green as fixed and adjust only Red/Blue
	 * Compute the average of the both green channels first
	 */
	avg = (u64)hist_count[ISC_HIS_CFG_MODE_GR] +
		(u64)hist_count[ISC_HIS_CFG_MODE_GB];
	avg >>= 1;

	/* Green histogram is null, nothing to करो */
	अगर (!avg)
		वापस;

	क्रम (c = ISC_HIS_CFG_MODE_GR; c <= ISC_HIS_CFG_MODE_B; c++) अणु
		/*
		 * the color offset is the minimum value of the histogram.
		 * we stretch this color to the full range by substracting
		 * this value from the color component.
		 */
		offset[c] = ctrls->hist_minmax[c][HIST_MIN_INDEX];
		/*
		 * The offset is always at least 1. If the offset is 1, we करो
		 * not need to adjust it, so our result must be zero.
		 * the offset is computed in a histogram on 9 bits (0..512)
		 * but the offset in रेजिस्टर is based on
		 * 12 bits pipeline (0..4096).
		 * we need to shअगरt with the 3 bits that the histogram is
		 * ignoring
		 */
		ctrls->offset[c] = (offset[c] - 1) << 3;

		/*
		 * the offset is then taken and converted to 2's complements,
		 * and must be negative, as we subtract this value from the
		 * color components
		 */
		ctrls->offset[c] = -ctrls->offset[c];

		/*
		 * the stretch gain is the total number of histogram bins
		 * भागided by the actual range of color component (Max - Min)
		 * If we compute gain like this, the actual color component
		 * will be stretched to the full histogram.
		 * We need to shअगरt 9 bits क्रम precision, we have 9 bits क्रम
		 * decimals
		 */
		s_gain[c] = (HIST_ENTRIES << 9) /
			(ctrls->hist_minmax[c][HIST_MAX_INDEX] -
			ctrls->hist_minmax[c][HIST_MIN_INDEX] + 1);

		/*
		 * Now we have to compute the gain w.r.t. the average.
		 * Add/lose gain to the component towards the average.
		 * If it happens that the component is zero, use the
		 * fixed poपूर्णांक value : 1.0 gain.
		 */
		अगर (hist_count[c])
			gw_gain[c] = भाग_u64(avg << 9, hist_count[c]);
		अन्यथा
			gw_gain[c] = 1 << 9;

		/* multiply both gains and adjust क्रम decimals */
		ctrls->gain[c] = s_gain[c] * gw_gain[c];
		ctrls->gain[c] >>= 9;
	पूर्ण
पूर्ण

अटल व्योम isc_awb_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा isc_device *isc =
		container_of(w, काष्ठा isc_device, awb_work);
	काष्ठा regmap *regmap = isc->regmap;
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;
	u32 hist_id = ctrls->hist_id;
	u32 baysel;
	अचिन्हित दीर्घ flags;
	u32 min, max;

	/* streaming is not active anymore */
	अगर (isc->stop)
		वापस;

	अगर (ctrls->hist_stat != HIST_ENABLED)
		वापस;

	isc_hist_count(isc, &min, &max);
	ctrls->hist_minmax[hist_id][HIST_MIN_INDEX] = min;
	ctrls->hist_minmax[hist_id][HIST_MAX_INDEX] = max;

	अगर (hist_id != ISC_HIS_CFG_MODE_B) अणु
		hist_id++;
	पूर्ण अन्यथा अणु
		isc_wb_update(ctrls);
		hist_id = ISC_HIS_CFG_MODE_GR;
	पूर्ण

	ctrls->hist_id = hist_id;
	baysel = isc->config.sd_क्रमmat->cfa_baycfg << ISC_HIS_CFG_BAYSEL_SHIFT;

	pm_runसमय_get_sync(isc->dev);

	/*
	 * only update अगर we have all the required histograms and controls
	 * अगर awb has been disabled, we need to reset रेजिस्टरs as well.
	 */
	अगर (hist_id == ISC_HIS_CFG_MODE_GR || ctrls->awb == ISC_WB_NONE) अणु
		/*
		 * It may happen that DMA Done IRQ will trigger जबतक we are
		 * updating white balance रेजिस्टरs here.
		 * In that हाल, only parts of the controls have been updated.
		 * We can aव्योम that by locking the section.
		 */
		spin_lock_irqsave(&isc->awb_lock, flags);
		isc_update_awb_ctrls(isc);
		spin_unlock_irqrestore(&isc->awb_lock, flags);

		/*
		 * अगर we are करोing just the one समय white balance adjusपंचांगent,
		 * we are basically करोne.
		 */
		अगर (ctrls->awb == ISC_WB_ONETIME) अणु
			v4l2_info(&isc->v4l2_dev,
				  "Completed one time white-balance adjustment.\n");
			/* update the v4l2 controls values */
			isc_update_v4l2_ctrls(isc);
			ctrls->awb = ISC_WB_NONE;
		पूर्ण
	पूर्ण
	regmap_ग_लिखो(regmap, ISC_HIS_CFG, hist_id | baysel | ISC_HIS_CFG_RAR);
	isc_update_profile(isc);
	/* अगर awb has been disabled, we करोn't need to start another histogram */
	अगर (ctrls->awb)
		regmap_ग_लिखो(regmap, ISC_CTRLEN, ISC_CTRL_HISREQ);

	pm_runसमय_put_sync(isc->dev);
पूर्ण

अटल पूर्णांक isc_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा isc_device *isc = container_of(ctrl->handler,
					     काष्ठा isc_device, ctrls.handler);
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;

	अगर (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		ctrls->brightness = ctrl->val & ISC_CBC_BRIGHT_MASK;
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ctrls->contrast = ctrl->val & ISC_CBC_CONTRAST_MASK;
		अवरोध;
	हाल V4L2_CID_GAMMA:
		ctrls->gamma_index = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops isc_ctrl_ops = अणु
	.s_ctrl	= isc_s_ctrl,
पूर्ण;

अटल पूर्णांक isc_s_awb_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा isc_device *isc = container_of(ctrl->handler,
					     काष्ठा isc_device, ctrls.handler);
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;

	अगर (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		अगर (ctrl->val == 1)
			ctrls->awb = ISC_WB_AUTO;
		अन्यथा
			ctrls->awb = ISC_WB_NONE;

		/* we did not configure ISC yet */
		अगर (!isc->config.sd_क्रमmat)
			अवरोध;

		/* configure the controls with new values from v4l2 */
		अगर (ctrl->cluster[ISC_CTRL_R_GAIN]->is_new)
			ctrls->gain[ISC_HIS_CFG_MODE_R] = isc->r_gain_ctrl->val;
		अगर (ctrl->cluster[ISC_CTRL_B_GAIN]->is_new)
			ctrls->gain[ISC_HIS_CFG_MODE_B] = isc->b_gain_ctrl->val;
		अगर (ctrl->cluster[ISC_CTRL_GR_GAIN]->is_new)
			ctrls->gain[ISC_HIS_CFG_MODE_GR] = isc->gr_gain_ctrl->val;
		अगर (ctrl->cluster[ISC_CTRL_GB_GAIN]->is_new)
			ctrls->gain[ISC_HIS_CFG_MODE_GB] = isc->gb_gain_ctrl->val;

		अगर (ctrl->cluster[ISC_CTRL_R_OFF]->is_new)
			ctrls->offset[ISC_HIS_CFG_MODE_R] = isc->r_off_ctrl->val;
		अगर (ctrl->cluster[ISC_CTRL_B_OFF]->is_new)
			ctrls->offset[ISC_HIS_CFG_MODE_B] = isc->b_off_ctrl->val;
		अगर (ctrl->cluster[ISC_CTRL_GR_OFF]->is_new)
			ctrls->offset[ISC_HIS_CFG_MODE_GR] = isc->gr_off_ctrl->val;
		अगर (ctrl->cluster[ISC_CTRL_GB_OFF]->is_new)
			ctrls->offset[ISC_HIS_CFG_MODE_GB] = isc->gb_off_ctrl->val;

		isc_update_awb_ctrls(isc);

		अगर (vb2_is_streaming(&isc->vb2_vidq)) अणु
			/*
			 * If we are streaming, we can update profile to
			 * have the new settings in place.
			 */
			isc_update_profile(isc);
		पूर्ण अन्यथा अणु
			/*
			 * The स्वतः cluster will activate स्वतःmatically this
			 * control. This has to be deactivated when not
			 * streaming.
			 */
			v4l2_ctrl_activate(isc->करो_wb_ctrl, false);
		पूर्ण

		/* अगर we have स्वतःwhitebalance on, start histogram procedure */
		अगर (ctrls->awb == ISC_WB_AUTO &&
		    vb2_is_streaming(&isc->vb2_vidq) &&
		    ISC_IS_FORMAT_RAW(isc->config.sd_क्रमmat->mbus_code))
			isc_set_histogram(isc, true);

		/*
		 * क्रम one समय whitebalance adjusपंचांगent, check the button,
		 * अगर it's pressed, perक्रमm the one समय operation.
		 */
		अगर (ctrls->awb == ISC_WB_NONE &&
		    ctrl->cluster[ISC_CTRL_DO_WB]->is_new &&
		    !(ctrl->cluster[ISC_CTRL_DO_WB]->flags &
		    V4L2_CTRL_FLAG_INACTIVE)) अणु
			ctrls->awb = ISC_WB_ONETIME;
			isc_set_histogram(isc, true);
			v4l2_dbg(1, debug, &isc->v4l2_dev,
				 "One time white-balance started.\n");
		पूर्ण
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक isc_g_अस्थिर_awb_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा isc_device *isc = container_of(ctrl->handler,
					     काष्ठा isc_device, ctrls.handler);
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;

	चयन (ctrl->id) अणु
	/* being a cluster, this id will be called क्रम every control */
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ctrl->cluster[ISC_CTRL_R_GAIN]->val =
					ctrls->gain[ISC_HIS_CFG_MODE_R];
		ctrl->cluster[ISC_CTRL_B_GAIN]->val =
					ctrls->gain[ISC_HIS_CFG_MODE_B];
		ctrl->cluster[ISC_CTRL_GR_GAIN]->val =
					ctrls->gain[ISC_HIS_CFG_MODE_GR];
		ctrl->cluster[ISC_CTRL_GB_GAIN]->val =
					ctrls->gain[ISC_HIS_CFG_MODE_GB];

		ctrl->cluster[ISC_CTRL_R_OFF]->val =
			ctrls->offset[ISC_HIS_CFG_MODE_R];
		ctrl->cluster[ISC_CTRL_B_OFF]->val =
			ctrls->offset[ISC_HIS_CFG_MODE_B];
		ctrl->cluster[ISC_CTRL_GR_OFF]->val =
			ctrls->offset[ISC_HIS_CFG_MODE_GR];
		ctrl->cluster[ISC_CTRL_GB_OFF]->val =
			ctrls->offset[ISC_HIS_CFG_MODE_GB];
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops isc_awb_ops = अणु
	.s_ctrl = isc_s_awb_ctrl,
	.g_अस्थिर_ctrl = isc_g_अस्थिर_awb_ctrl,
पूर्ण;

#घोषणा ISC_CTRL_OFF(_name, _id, _name_str) \
	अटल स्थिर काष्ठा v4l2_ctrl_config _name = अणु \
		.ops = &isc_awb_ops, \
		.id = _id, \
		.name = _name_str, \
		.type = V4L2_CTRL_TYPE_INTEGER, \
		.flags = V4L2_CTRL_FLAG_SLIDER, \
		.min = -4095, \
		.max = 4095, \
		.step = 1, \
		.def = 0, \
	पूर्ण

ISC_CTRL_OFF(isc_r_off_ctrl, ISC_CID_R_OFFSET, "Red Component Offset");
ISC_CTRL_OFF(isc_b_off_ctrl, ISC_CID_B_OFFSET, "Blue Component Offset");
ISC_CTRL_OFF(isc_gr_off_ctrl, ISC_CID_GR_OFFSET, "Green Red Component Offset");
ISC_CTRL_OFF(isc_gb_off_ctrl, ISC_CID_GB_OFFSET, "Green Blue Component Offset");

#घोषणा ISC_CTRL_GAIN(_name, _id, _name_str) \
	अटल स्थिर काष्ठा v4l2_ctrl_config _name = अणु \
		.ops = &isc_awb_ops, \
		.id = _id, \
		.name = _name_str, \
		.type = V4L2_CTRL_TYPE_INTEGER, \
		.flags = V4L2_CTRL_FLAG_SLIDER, \
		.min = 0, \
		.max = 8191, \
		.step = 1, \
		.def = 512, \
	पूर्ण

ISC_CTRL_GAIN(isc_r_gain_ctrl, ISC_CID_R_GAIN, "Red Component Gain");
ISC_CTRL_GAIN(isc_b_gain_ctrl, ISC_CID_B_GAIN, "Blue Component Gain");
ISC_CTRL_GAIN(isc_gr_gain_ctrl, ISC_CID_GR_GAIN, "Green Red Component Gain");
ISC_CTRL_GAIN(isc_gb_gain_ctrl, ISC_CID_GB_GAIN, "Green Blue Component Gain");

अटल पूर्णांक isc_ctrl_init(काष्ठा isc_device *isc)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &isc_ctrl_ops;
	काष्ठा isc_ctrls *ctrls = &isc->ctrls;
	काष्ठा v4l2_ctrl_handler *hdl = &ctrls->handler;
	पूर्णांक ret;

	ctrls->hist_stat = HIST_INIT;
	isc_reset_awb_ctrls(isc);

	ret = v4l2_ctrl_handler_init(hdl, 13);
	अगर (ret < 0)
		वापस ret;

	ctrls->brightness = 0;
	ctrls->contrast = 256;

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS, -1024, 1023, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST, -2048, 2047, 1, 256);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_GAMMA, 0, GAMMA_MAX, 1, 2);
	isc->awb_ctrl = v4l2_ctrl_new_std(hdl, &isc_awb_ops,
					  V4L2_CID_AUTO_WHITE_BALANCE,
					  0, 1, 1, 1);

	/* करो_white_balance is a button, so min,max,step,शेष are ignored */
	isc->करो_wb_ctrl = v4l2_ctrl_new_std(hdl, &isc_awb_ops,
					    V4L2_CID_DO_WHITE_BALANCE,
					    0, 0, 0, 0);

	अगर (!isc->करो_wb_ctrl) अणु
		ret = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण

	v4l2_ctrl_activate(isc->करो_wb_ctrl, false);

	isc->r_gain_ctrl = v4l2_ctrl_new_custom(hdl, &isc_r_gain_ctrl, शून्य);
	isc->b_gain_ctrl = v4l2_ctrl_new_custom(hdl, &isc_b_gain_ctrl, शून्य);
	isc->gr_gain_ctrl = v4l2_ctrl_new_custom(hdl, &isc_gr_gain_ctrl, शून्य);
	isc->gb_gain_ctrl = v4l2_ctrl_new_custom(hdl, &isc_gb_gain_ctrl, शून्य);
	isc->r_off_ctrl = v4l2_ctrl_new_custom(hdl, &isc_r_off_ctrl, शून्य);
	isc->b_off_ctrl = v4l2_ctrl_new_custom(hdl, &isc_b_off_ctrl, शून्य);
	isc->gr_off_ctrl = v4l2_ctrl_new_custom(hdl, &isc_gr_off_ctrl, शून्य);
	isc->gb_off_ctrl = v4l2_ctrl_new_custom(hdl, &isc_gb_off_ctrl, शून्य);

	/*
	 * The cluster is in स्वतः mode with स्वतःwhitebalance enabled
	 * and manual mode otherwise.
	 */
	v4l2_ctrl_स्वतः_cluster(10, &isc->awb_ctrl, 0, true);

	v4l2_ctrl_handler_setup(hdl);

	वापस 0;
पूर्ण

अटल पूर्णांक isc_async_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
			    काष्ठा v4l2_subdev *subdev,
			    काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा isc_device *isc = container_of(notअगरier->v4l2_dev,
					      काष्ठा isc_device, v4l2_dev);
	काष्ठा isc_subdev_entity *subdev_entity =
		container_of(notअगरier, काष्ठा isc_subdev_entity, notअगरier);

	अगर (video_is_रेजिस्टरed(&isc->video_dev)) अणु
		v4l2_err(&isc->v4l2_dev, "only supports one sub-device.\n");
		वापस -EBUSY;
	पूर्ण

	subdev_entity->sd = subdev;

	वापस 0;
पूर्ण

अटल व्योम isc_async_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
			      काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा isc_device *isc = container_of(notअगरier->v4l2_dev,
					      काष्ठा isc_device, v4l2_dev);
	cancel_work_sync(&isc->awb_work);
	video_unरेजिस्टर_device(&isc->video_dev);
	v4l2_ctrl_handler_मुक्त(&isc->ctrls.handler);
पूर्ण

अटल काष्ठा isc_क्रमmat *find_क्रमmat_by_code(अचिन्हित पूर्णांक code, पूर्णांक *index)
अणु
	काष्ठा isc_क्रमmat *fmt = &क्रमmats_list[0];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats_list); i++) अणु
		अगर (fmt->mbus_code == code) अणु
			*index = i;
			वापस fmt;
		पूर्ण

		fmt++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक isc_क्रमmats_init(काष्ठा isc_device *isc)
अणु
	काष्ठा isc_क्रमmat *fmt;
	काष्ठा v4l2_subdev *subdev = isc->current_subdev->sd;
	अचिन्हित पूर्णांक num_fmts, i, j;
	u32 list_size = ARRAY_SIZE(क्रमmats_list);
	काष्ठा v4l2_subdev_mbus_code_क्रमागत mbus_code = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	num_fmts = 0;
	जबतक (!v4l2_subdev_call(subdev, pad, क्रमागत_mbus_code,
	       शून्य, &mbus_code)) अणु
		mbus_code.index++;

		fmt = find_क्रमmat_by_code(mbus_code.code, &i);
		अगर (!fmt) अणु
			v4l2_warn(&isc->v4l2_dev, "Mbus code %x not supported\n",
				  mbus_code.code);
			जारी;
		पूर्ण

		fmt->sd_support = true;
		num_fmts++;
	पूर्ण

	अगर (!num_fmts)
		वापस -ENXIO;

	isc->num_user_क्रमmats = num_fmts;
	isc->user_क्रमmats = devm_kसुस्मृति(isc->dev,
					 num_fmts, माप(*isc->user_क्रमmats),
					 GFP_KERNEL);
	अगर (!isc->user_क्रमmats)
		वापस -ENOMEM;

	fmt = &क्रमmats_list[0];
	क्रम (i = 0, j = 0; i < list_size; i++) अणु
		अगर (fmt->sd_support)
			isc->user_क्रमmats[j++] = fmt;
		fmt++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक isc_set_शेष_fmt(काष्ठा isc_device *isc)
अणु
	काष्ठा v4l2_क्रमmat f = अणु
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
		.fmt.pix = अणु
			.width		= VGA_WIDTH,
			.height		= VGA_HEIGHT,
			.field		= V4L2_FIELD_NONE,
			.pixelक्रमmat	= isc->user_क्रमmats[0]->fourcc,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = isc_try_fmt(isc, &f, शून्य);
	अगर (ret)
		वापस ret;

	isc->fmt = f;
	वापस 0;
पूर्ण

अटल पूर्णांक isc_async_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा isc_device *isc = container_of(notअगरier->v4l2_dev,
					      काष्ठा isc_device, v4l2_dev);
	काष्ठा video_device *vdev = &isc->video_dev;
	काष्ठा vb2_queue *q = &isc->vb2_vidq;
	पूर्णांक ret = 0;

	INIT_WORK(&isc->awb_work, isc_awb_work);

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&isc->v4l2_dev);
	अगर (ret < 0) अणु
		v4l2_err(&isc->v4l2_dev, "Failed to register subdev nodes\n");
		वापस ret;
	पूर्ण

	isc->current_subdev = container_of(notअगरier,
					   काष्ठा isc_subdev_entity, notअगरier);
	mutex_init(&isc->lock);
	init_completion(&isc->comp);

	/* Initialize videobuf2 queue */
	q->type			= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes		= VB2_MMAP | VB2_DMABUF | VB2_READ;
	q->drv_priv		= isc;
	q->buf_काष्ठा_size	= माप(काष्ठा isc_buffer);
	q->ops			= &isc_vb2_ops;
	q->mem_ops		= &vb2_dma_contig_memops;
	q->बारtamp_flags	= V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock			= &isc->lock;
	q->min_buffers_needed	= 1;
	q->dev			= isc->dev;

	ret = vb2_queue_init(q);
	अगर (ret < 0) अणु
		v4l2_err(&isc->v4l2_dev,
			 "vb2_queue_init() failed: %d\n", ret);
		जाओ isc_async_complete_err;
	पूर्ण

	/* Init video dma queues */
	INIT_LIST_HEAD(&isc->dma_queue);
	spin_lock_init(&isc->dma_queue_lock);
	spin_lock_init(&isc->awb_lock);

	ret = isc_क्रमmats_init(isc);
	अगर (ret < 0) अणु
		v4l2_err(&isc->v4l2_dev,
			 "Init format failed: %d\n", ret);
		जाओ isc_async_complete_err;
	पूर्ण

	ret = isc_set_शेष_fmt(isc);
	अगर (ret) अणु
		v4l2_err(&isc->v4l2_dev, "Could not set default format\n");
		जाओ isc_async_complete_err;
	पूर्ण

	ret = isc_ctrl_init(isc);
	अगर (ret) अणु
		v4l2_err(&isc->v4l2_dev, "Init isc ctrols failed: %d\n", ret);
		जाओ isc_async_complete_err;
	पूर्ण

	/* Register video device */
	strscpy(vdev->name, ATMEL_ISC_NAME, माप(vdev->name));
	vdev->release		= video_device_release_empty;
	vdev->fops		= &isc_fops;
	vdev->ioctl_ops		= &isc_ioctl_ops;
	vdev->v4l2_dev		= &isc->v4l2_dev;
	vdev->vfl_dir		= VFL_सूची_RX;
	vdev->queue		= q;
	vdev->lock		= &isc->lock;
	vdev->ctrl_handler	= &isc->ctrls.handler;
	vdev->device_caps	= V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE;
	video_set_drvdata(vdev, isc);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		v4l2_err(&isc->v4l2_dev,
			 "video_register_device failed: %d\n", ret);
		जाओ isc_async_complete_err;
	पूर्ण

	वापस 0;

isc_async_complete_err:
	mutex_destroy(&isc->lock);
	वापस ret;
पूर्ण

स्थिर काष्ठा v4l2_async_notअगरier_operations isc_async_ops = अणु
	.bound = isc_async_bound,
	.unbind = isc_async_unbind,
	.complete = isc_async_complete,
पूर्ण;

व्योम isc_subdev_cleanup(काष्ठा isc_device *isc)
अणु
	काष्ठा isc_subdev_entity *subdev_entity;

	list_क्रम_each_entry(subdev_entity, &isc->subdev_entities, list) अणु
		v4l2_async_notअगरier_unरेजिस्टर(&subdev_entity->notअगरier);
		v4l2_async_notअगरier_cleanup(&subdev_entity->notअगरier);
	पूर्ण

	INIT_LIST_HEAD(&isc->subdev_entities);
पूर्ण

पूर्णांक isc_pipeline_init(काष्ठा isc_device *isc)
अणु
	काष्ठा device *dev = isc->dev;
	काष्ठा regmap *regmap = isc->regmap;
	काष्ठा regmap_field *regs;
	अचिन्हित पूर्णांक i;

	/* WB-->CFA-->CC-->GAM-->CSC-->CBC-->SUB422-->SUB420 */
	स्थिर काष्ठा reg_field regfields[ISC_PIPE_LINE_NODE_NUM] = अणु
		REG_FIELD(ISC_WB_CTRL, 0, 0),
		REG_FIELD(ISC_CFA_CTRL, 0, 0),
		REG_FIELD(ISC_CC_CTRL, 0, 0),
		REG_FIELD(ISC_GAM_CTRL, 0, 0),
		REG_FIELD(ISC_GAM_CTRL, 1, 1),
		REG_FIELD(ISC_GAM_CTRL, 2, 2),
		REG_FIELD(ISC_GAM_CTRL, 3, 3),
		REG_FIELD(ISC_CSC_CTRL, 0, 0),
		REG_FIELD(ISC_CBC_CTRL, 0, 0),
		REG_FIELD(ISC_SUB422_CTRL, 0, 0),
		REG_FIELD(ISC_SUB420_CTRL, 0, 0),
	पूर्ण;

	क्रम (i = 0; i < ISC_PIPE_LINE_NODE_NUM; i++) अणु
		regs = devm_regmap_field_alloc(dev, regmap, regfields[i]);
		अगर (IS_ERR(regs))
			वापस PTR_ERR(regs);

		isc->pipeline[i] =  regs;
	पूर्ण

	वापस 0;
पूर्ण

/* regmap configuration */
#घोषणा ATMEL_ISC_REG_MAX    0xbfc
स्थिर काष्ठा regmap_config isc_regmap_config = अणु
	.reg_bits       = 32,
	.reg_stride     = 4,
	.val_bits       = 32,
	.max_रेजिस्टर	= ATMEL_ISC_REG_MAX,
पूर्ण;


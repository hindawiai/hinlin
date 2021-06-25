<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Rockchip ISP1 Driver - V4l resizer device
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Based on Rockchip ISP1 driver by Rockchip Electronics Co., Ltd.
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 */

#समावेश "rkisp1-common.h"

#घोषणा RKISP1_RSZ_SP_DEV_NAME	RKISP1_DRIVER_NAME "_resizer_selfpath"
#घोषणा RKISP1_RSZ_MP_DEV_NAME	RKISP1_DRIVER_NAME "_resizer_mainpath"

#घोषणा RKISP1_DEF_FMT MEDIA_BUS_FMT_YUYV8_2X8
#घोषणा RKISP1_DEF_PIXEL_ENC V4L2_PIXEL_ENC_YUV

काष्ठा rkisp1_rsz_yuv_mbus_info अणु
	u32 mbus_code;
	u32 hभाग;
	u32 vभाग;
पूर्ण;

अटल स्थिर काष्ठा rkisp1_rsz_yuv_mbus_info rkisp1_rsz_yuv_src_क्रमmats[] = अणु
	अणु
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8, /* YUV422 */
		.hभाग		= 2,
		.vभाग		= 1,
	पूर्ण,
	अणु
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_1_5X8, /* YUV420 */
		.hभाग		= 2,
		.vभाग		= 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rkisp1_rsz_yuv_mbus_info *rkisp1_rsz_get_yuv_mbus_info(u32 mbus_code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rkisp1_rsz_yuv_src_क्रमmats); i++) अणु
		अगर (rkisp1_rsz_yuv_src_क्रमmats[i].mbus_code == mbus_code)
			वापस &rkisp1_rsz_yuv_src_क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

क्रमागत rkisp1_shaकरोw_regs_when अणु
	RKISP1_SHADOW_REGS_SYNC,
	RKISP1_SHADOW_REGS_ASYNC,
पूर्ण;

काष्ठा rkisp1_rsz_config अणु
	/* स्थिरrains */
	स्थिर पूर्णांक max_rsz_width;
	स्थिर पूर्णांक max_rsz_height;
	स्थिर पूर्णांक min_rsz_width;
	स्थिर पूर्णांक min_rsz_height;
	/* रेजिस्टरs */
	काष्ठा अणु
		u32 ctrl;
		u32 ctrl_shd;
		u32 scale_hy;
		u32 scale_hcr;
		u32 scale_hcb;
		u32 scale_vy;
		u32 scale_vc;
		u32 scale_lut;
		u32 scale_lut_addr;
		u32 scale_hy_shd;
		u32 scale_hcr_shd;
		u32 scale_hcb_shd;
		u32 scale_vy_shd;
		u32 scale_vc_shd;
		u32 phase_hy;
		u32 phase_hc;
		u32 phase_vy;
		u32 phase_vc;
		u32 phase_hy_shd;
		u32 phase_hc_shd;
		u32 phase_vy_shd;
		u32 phase_vc_shd;
	पूर्ण rsz;
	काष्ठा अणु
		u32 ctrl;
		u32 yuvmode_mask;
		u32 rawmode_mask;
		u32 h_offset;
		u32 v_offset;
		u32 h_size;
		u32 v_size;
	पूर्ण dual_crop;
पूर्ण;

अटल स्थिर काष्ठा rkisp1_rsz_config rkisp1_rsz_config_mp = अणु
	/* स्थिरraपूर्णांकs */
	.max_rsz_width = RKISP1_RSZ_MP_SRC_MAX_WIDTH,
	.max_rsz_height = RKISP1_RSZ_MP_SRC_MAX_HEIGHT,
	.min_rsz_width = RKISP1_RSZ_SRC_MIN_WIDTH,
	.min_rsz_height = RKISP1_RSZ_SRC_MIN_HEIGHT,
	/* रेजिस्टरs */
	.rsz = अणु
		.ctrl =			RKISP1_CIF_MRSZ_CTRL,
		.scale_hy =		RKISP1_CIF_MRSZ_SCALE_HY,
		.scale_hcr =		RKISP1_CIF_MRSZ_SCALE_HCR,
		.scale_hcb =		RKISP1_CIF_MRSZ_SCALE_HCB,
		.scale_vy =		RKISP1_CIF_MRSZ_SCALE_VY,
		.scale_vc =		RKISP1_CIF_MRSZ_SCALE_VC,
		.scale_lut =		RKISP1_CIF_MRSZ_SCALE_LUT,
		.scale_lut_addr =	RKISP1_CIF_MRSZ_SCALE_LUT_ADDR,
		.scale_hy_shd =		RKISP1_CIF_MRSZ_SCALE_HY_SHD,
		.scale_hcr_shd =	RKISP1_CIF_MRSZ_SCALE_HCR_SHD,
		.scale_hcb_shd =	RKISP1_CIF_MRSZ_SCALE_HCB_SHD,
		.scale_vy_shd =		RKISP1_CIF_MRSZ_SCALE_VY_SHD,
		.scale_vc_shd =		RKISP1_CIF_MRSZ_SCALE_VC_SHD,
		.phase_hy =		RKISP1_CIF_MRSZ_PHASE_HY,
		.phase_hc =		RKISP1_CIF_MRSZ_PHASE_HC,
		.phase_vy =		RKISP1_CIF_MRSZ_PHASE_VY,
		.phase_vc =		RKISP1_CIF_MRSZ_PHASE_VC,
		.ctrl_shd =		RKISP1_CIF_MRSZ_CTRL_SHD,
		.phase_hy_shd =		RKISP1_CIF_MRSZ_PHASE_HY_SHD,
		.phase_hc_shd =		RKISP1_CIF_MRSZ_PHASE_HC_SHD,
		.phase_vy_shd =		RKISP1_CIF_MRSZ_PHASE_VY_SHD,
		.phase_vc_shd =		RKISP1_CIF_MRSZ_PHASE_VC_SHD,
	पूर्ण,
	.dual_crop = अणु
		.ctrl =			RKISP1_CIF_DUAL_CROP_CTRL,
		.yuvmode_mask =		RKISP1_CIF_DUAL_CROP_MP_MODE_YUV,
		.rawmode_mask =		RKISP1_CIF_DUAL_CROP_MP_MODE_RAW,
		.h_offset =		RKISP1_CIF_DUAL_CROP_M_H_OFFS,
		.v_offset =		RKISP1_CIF_DUAL_CROP_M_V_OFFS,
		.h_size =		RKISP1_CIF_DUAL_CROP_M_H_SIZE,
		.v_size =		RKISP1_CIF_DUAL_CROP_M_V_SIZE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rkisp1_rsz_config rkisp1_rsz_config_sp = अणु
	/* स्थिरraपूर्णांकs */
	.max_rsz_width = RKISP1_RSZ_SP_SRC_MAX_WIDTH,
	.max_rsz_height = RKISP1_RSZ_SP_SRC_MAX_HEIGHT,
	.min_rsz_width = RKISP1_RSZ_SRC_MIN_WIDTH,
	.min_rsz_height = RKISP1_RSZ_SRC_MIN_HEIGHT,
	/* रेजिस्टरs */
	.rsz = अणु
		.ctrl =			RKISP1_CIF_SRSZ_CTRL,
		.scale_hy =		RKISP1_CIF_SRSZ_SCALE_HY,
		.scale_hcr =		RKISP1_CIF_SRSZ_SCALE_HCR,
		.scale_hcb =		RKISP1_CIF_SRSZ_SCALE_HCB,
		.scale_vy =		RKISP1_CIF_SRSZ_SCALE_VY,
		.scale_vc =		RKISP1_CIF_SRSZ_SCALE_VC,
		.scale_lut =		RKISP1_CIF_SRSZ_SCALE_LUT,
		.scale_lut_addr =	RKISP1_CIF_SRSZ_SCALE_LUT_ADDR,
		.scale_hy_shd =		RKISP1_CIF_SRSZ_SCALE_HY_SHD,
		.scale_hcr_shd =	RKISP1_CIF_SRSZ_SCALE_HCR_SHD,
		.scale_hcb_shd =	RKISP1_CIF_SRSZ_SCALE_HCB_SHD,
		.scale_vy_shd =		RKISP1_CIF_SRSZ_SCALE_VY_SHD,
		.scale_vc_shd =		RKISP1_CIF_SRSZ_SCALE_VC_SHD,
		.phase_hy =		RKISP1_CIF_SRSZ_PHASE_HY,
		.phase_hc =		RKISP1_CIF_SRSZ_PHASE_HC,
		.phase_vy =		RKISP1_CIF_SRSZ_PHASE_VY,
		.phase_vc =		RKISP1_CIF_SRSZ_PHASE_VC,
		.ctrl_shd =		RKISP1_CIF_SRSZ_CTRL_SHD,
		.phase_hy_shd =		RKISP1_CIF_SRSZ_PHASE_HY_SHD,
		.phase_hc_shd =		RKISP1_CIF_SRSZ_PHASE_HC_SHD,
		.phase_vy_shd =		RKISP1_CIF_SRSZ_PHASE_VY_SHD,
		.phase_vc_shd =		RKISP1_CIF_SRSZ_PHASE_VC_SHD,
	पूर्ण,
	.dual_crop = अणु
		.ctrl =			RKISP1_CIF_DUAL_CROP_CTRL,
		.yuvmode_mask =		RKISP1_CIF_DUAL_CROP_SP_MODE_YUV,
		.rawmode_mask =		RKISP1_CIF_DUAL_CROP_SP_MODE_RAW,
		.h_offset =		RKISP1_CIF_DUAL_CROP_S_H_OFFS,
		.v_offset =		RKISP1_CIF_DUAL_CROP_S_V_OFFS,
		.h_size =		RKISP1_CIF_DUAL_CROP_S_H_SIZE,
		.v_size =		RKISP1_CIF_DUAL_CROP_S_V_SIZE,
	पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_mbus_framefmt *
rkisp1_rsz_get_pad_fmt(काष्ठा rkisp1_resizer *rsz,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       अचिन्हित पूर्णांक pad, u32 which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&rsz->sd, cfg, pad);
	अन्यथा
		वापस v4l2_subdev_get_try_क्रमmat(&rsz->sd, rsz->pad_cfg, pad);
पूर्ण

अटल काष्ठा v4l2_rect *
rkisp1_rsz_get_pad_crop(काष्ठा rkisp1_resizer *rsz,
			काष्ठा v4l2_subdev_pad_config *cfg,
			अचिन्हित पूर्णांक pad, u32 which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_crop(&rsz->sd, cfg, pad);
	अन्यथा
		वापस v4l2_subdev_get_try_crop(&rsz->sd, rsz->pad_cfg, pad);
पूर्ण

/* ----------------------------------------------------------------------------
 * Dual crop hw configs
 */

अटल व्योम rkisp1_dcrop_disable(काष्ठा rkisp1_resizer *rsz,
				 क्रमागत rkisp1_shaकरोw_regs_when when)
अणु
	u32 dc_ctrl = rkisp1_पढ़ो(rsz->rkisp1, rsz->config->dual_crop.ctrl);
	u32 mask = ~(rsz->config->dual_crop.yuvmode_mask |
		     rsz->config->dual_crop.rawmode_mask);

	dc_ctrl &= mask;
	अगर (when == RKISP1_SHADOW_REGS_ASYNC)
		dc_ctrl |= RKISP1_CIF_DUAL_CROP_GEN_CFG_UPD;
	अन्यथा
		dc_ctrl |= RKISP1_CIF_DUAL_CROP_CFG_UPD;
	rkisp1_ग_लिखो(rsz->rkisp1, dc_ctrl, rsz->config->dual_crop.ctrl);
पूर्ण

/* configure dual-crop unit */
अटल व्योम rkisp1_dcrop_config(काष्ठा rkisp1_resizer *rsz)
अणु
	काष्ठा rkisp1_device *rkisp1 = rsz->rkisp1;
	काष्ठा v4l2_mbus_framefmt *sink_fmt;
	काष्ठा v4l2_rect *sink_crop;
	u32 dc_ctrl;

	sink_crop = rkisp1_rsz_get_pad_crop(rsz, शून्य, RKISP1_RSZ_PAD_SINK,
					    V4L2_SUBDEV_FORMAT_ACTIVE);
	sink_fmt = rkisp1_rsz_get_pad_fmt(rsz, शून्य, RKISP1_RSZ_PAD_SINK,
					  V4L2_SUBDEV_FORMAT_ACTIVE);

	अगर (sink_crop->width == sink_fmt->width &&
	    sink_crop->height == sink_fmt->height &&
	    sink_crop->left == 0 && sink_crop->top == 0) अणु
		rkisp1_dcrop_disable(rsz, RKISP1_SHADOW_REGS_SYNC);
		dev_dbg(rkisp1->dev, "capture %d crop disabled\n", rsz->id);
		वापस;
	पूर्ण

	dc_ctrl = rkisp1_पढ़ो(rkisp1, rsz->config->dual_crop.ctrl);
	rkisp1_ग_लिखो(rkisp1, sink_crop->left, rsz->config->dual_crop.h_offset);
	rkisp1_ग_लिखो(rkisp1, sink_crop->top, rsz->config->dual_crop.v_offset);
	rkisp1_ग_लिखो(rkisp1, sink_crop->width, rsz->config->dual_crop.h_size);
	rkisp1_ग_लिखो(rkisp1, sink_crop->height, rsz->config->dual_crop.v_size);
	dc_ctrl |= rsz->config->dual_crop.yuvmode_mask;
	dc_ctrl |= RKISP1_CIF_DUAL_CROP_CFG_UPD;
	rkisp1_ग_लिखो(rkisp1, dc_ctrl, rsz->config->dual_crop.ctrl);

	dev_dbg(rkisp1->dev, "stream %d crop: %dx%d -> %dx%d\n", rsz->id,
		sink_fmt->width, sink_fmt->height,
		sink_crop->width, sink_crop->height);
पूर्ण

/* ----------------------------------------------------------------------------
 * Resizer hw configs
 */

अटल व्योम rkisp1_rsz_dump_regs(काष्ठा rkisp1_resizer *rsz)
अणु
	dev_dbg(rsz->rkisp1->dev,
		"RSZ_CTRL 0x%08x/0x%08x\n"
		"RSZ_SCALE_HY %d/%d\n"
		"RSZ_SCALE_HCB %d/%d\n"
		"RSZ_SCALE_HCR %d/%d\n"
		"RSZ_SCALE_VY %d/%d\n"
		"RSZ_SCALE_VC %d/%d\n"
		"RSZ_PHASE_HY %d/%d\n"
		"RSZ_PHASE_HC %d/%d\n"
		"RSZ_PHASE_VY %d/%d\n"
		"RSZ_PHASE_VC %d/%d\n",
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.ctrl),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.ctrl_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_hy),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_hy_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_hcb),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_hcb_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_hcr),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_hcr_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_vy),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_vy_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_vc),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.scale_vc_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.phase_hy),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.phase_hy_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.phase_hc),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.phase_hc_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.phase_vy),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.phase_vy_shd),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.phase_vc),
		rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.phase_vc_shd));
पूर्ण

अटल व्योम rkisp1_rsz_update_shaकरोw(काष्ठा rkisp1_resizer *rsz,
				     क्रमागत rkisp1_shaकरोw_regs_when when)
अणु
	u32 ctrl_cfg = rkisp1_पढ़ो(rsz->rkisp1, rsz->config->rsz.ctrl);

	अगर (when == RKISP1_SHADOW_REGS_ASYNC)
		ctrl_cfg |= RKISP1_CIF_RSZ_CTRL_CFG_UPD_AUTO;
	अन्यथा
		ctrl_cfg |= RKISP1_CIF_RSZ_CTRL_CFG_UPD;

	rkisp1_ग_लिखो(rsz->rkisp1, ctrl_cfg, rsz->config->rsz.ctrl);
पूर्ण

अटल u32 rkisp1_rsz_calc_ratio(u32 len_sink, u32 len_src)
अणु
	अगर (len_sink < len_src)
		वापस ((len_sink - 1) * RKISP1_CIF_RSZ_SCALER_FACTOR) /
		       (len_src - 1);

	वापस ((len_src - 1) * RKISP1_CIF_RSZ_SCALER_FACTOR) /
	       (len_sink - 1) + 1;
पूर्ण

अटल व्योम rkisp1_rsz_disable(काष्ठा rkisp1_resizer *rsz,
			       क्रमागत rkisp1_shaकरोw_regs_when when)
अणु
	rkisp1_ग_लिखो(rsz->rkisp1, 0, rsz->config->rsz.ctrl);

	अगर (when == RKISP1_SHADOW_REGS_SYNC)
		rkisp1_rsz_update_shaकरोw(rsz, when);
पूर्ण

अटल व्योम rkisp1_rsz_config_regs(काष्ठा rkisp1_resizer *rsz,
				   काष्ठा v4l2_rect *sink_y,
				   काष्ठा v4l2_rect *sink_c,
				   काष्ठा v4l2_rect *src_y,
				   काष्ठा v4l2_rect *src_c,
				   क्रमागत rkisp1_shaकरोw_regs_when when)
अणु
	काष्ठा rkisp1_device *rkisp1 = rsz->rkisp1;
	u32 ratio, rsz_ctrl = 0;
	अचिन्हित पूर्णांक i;

	/* No phase offset */
	rkisp1_ग_लिखो(rkisp1, 0, rsz->config->rsz.phase_hy);
	rkisp1_ग_लिखो(rkisp1, 0, rsz->config->rsz.phase_hc);
	rkisp1_ग_लिखो(rkisp1, 0, rsz->config->rsz.phase_vy);
	rkisp1_ग_लिखो(rkisp1, 0, rsz->config->rsz.phase_vc);

	/* Linear पूर्णांकerpolation */
	क्रम (i = 0; i < 64; i++) अणु
		rkisp1_ग_लिखो(rkisp1, i, rsz->config->rsz.scale_lut_addr);
		rkisp1_ग_लिखो(rkisp1, i, rsz->config->rsz.scale_lut);
	पूर्ण

	अगर (sink_y->width != src_y->width) अणु
		rsz_ctrl |= RKISP1_CIF_RSZ_CTRL_SCALE_HY_ENABLE;
		अगर (sink_y->width < src_y->width)
			rsz_ctrl |= RKISP1_CIF_RSZ_CTRL_SCALE_HY_UP;
		ratio = rkisp1_rsz_calc_ratio(sink_y->width, src_y->width);
		rkisp1_ग_लिखो(rkisp1, ratio, rsz->config->rsz.scale_hy);
	पूर्ण

	अगर (sink_c->width != src_c->width) अणु
		rsz_ctrl |= RKISP1_CIF_RSZ_CTRL_SCALE_HC_ENABLE;
		अगर (sink_c->width < src_c->width)
			rsz_ctrl |= RKISP1_CIF_RSZ_CTRL_SCALE_HC_UP;
		ratio = rkisp1_rsz_calc_ratio(sink_c->width, src_c->width);
		rkisp1_ग_लिखो(rkisp1, ratio, rsz->config->rsz.scale_hcb);
		rkisp1_ग_लिखो(rkisp1, ratio, rsz->config->rsz.scale_hcr);
	पूर्ण

	अगर (sink_y->height != src_y->height) अणु
		rsz_ctrl |= RKISP1_CIF_RSZ_CTRL_SCALE_VY_ENABLE;
		अगर (sink_y->height < src_y->height)
			rsz_ctrl |= RKISP1_CIF_RSZ_CTRL_SCALE_VY_UP;
		ratio = rkisp1_rsz_calc_ratio(sink_y->height, src_y->height);
		rkisp1_ग_लिखो(rkisp1, ratio, rsz->config->rsz.scale_vy);
	पूर्ण

	अगर (sink_c->height != src_c->height) अणु
		rsz_ctrl |= RKISP1_CIF_RSZ_CTRL_SCALE_VC_ENABLE;
		अगर (sink_c->height < src_c->height)
			rsz_ctrl |= RKISP1_CIF_RSZ_CTRL_SCALE_VC_UP;
		ratio = rkisp1_rsz_calc_ratio(sink_c->height, src_c->height);
		rkisp1_ग_लिखो(rkisp1, ratio, rsz->config->rsz.scale_vc);
	पूर्ण

	rkisp1_ग_लिखो(rkisp1, rsz_ctrl, rsz->config->rsz.ctrl);

	rkisp1_rsz_update_shaकरोw(rsz, when);
पूर्ण

अटल व्योम rkisp1_rsz_config(काष्ठा rkisp1_resizer *rsz,
			      क्रमागत rkisp1_shaकरोw_regs_when when)
अणु
	स्थिर काष्ठा rkisp1_rsz_yuv_mbus_info *sink_yuv_info, *src_yuv_info;
	काष्ठा v4l2_rect sink_y, sink_c, src_y, src_c;
	काष्ठा v4l2_mbus_framefmt *src_fmt, *sink_fmt;
	काष्ठा v4l2_rect *sink_crop;

	sink_crop = rkisp1_rsz_get_pad_crop(rsz, शून्य, RKISP1_RSZ_PAD_SINK,
					    V4L2_SUBDEV_FORMAT_ACTIVE);
	src_fmt = rkisp1_rsz_get_pad_fmt(rsz, शून्य, RKISP1_RSZ_PAD_SRC,
					 V4L2_SUBDEV_FORMAT_ACTIVE);
	src_yuv_info = rkisp1_rsz_get_yuv_mbus_info(src_fmt->code);
	sink_fmt = rkisp1_rsz_get_pad_fmt(rsz, शून्य, RKISP1_RSZ_PAD_SINK,
					  V4L2_SUBDEV_FORMAT_ACTIVE);
	sink_yuv_info = rkisp1_rsz_get_yuv_mbus_info(sink_fmt->code);

	/*
	 * The resizer only works on yuv क्रमmats,
	 * so वापस अगर it is bayer क्रमmat.
	 */
	अगर (rsz->pixel_enc == V4L2_PIXEL_ENC_BAYER) अणु
		rkisp1_rsz_disable(rsz, when);
		वापस;
	पूर्ण

	sink_y.width = sink_crop->width;
	sink_y.height = sink_crop->height;
	src_y.width = src_fmt->width;
	src_y.height = src_fmt->height;

	sink_c.width = sink_y.width / sink_yuv_info->hभाग;
	sink_c.height = sink_y.height / sink_yuv_info->vभाग;

	/*
	 * The resizer is used not only to change the dimensions of the frame
	 * but also to change the scale क्रम YUV क्रमmats,
	 * (4:2:2 -> 4:2:0 क्रम example). So the width/height of the CbCr
	 * streams should be set according to the media bus क्रमmat in the src pad.
	 */
	src_c.width = src_y.width / src_yuv_info->hभाग;
	src_c.height = src_y.height / src_yuv_info->vभाग;

	अगर (sink_c.width == src_c.width && sink_c.height == src_c.height) अणु
		rkisp1_rsz_disable(rsz, when);
		वापस;
	पूर्ण

	dev_dbg(rsz->rkisp1->dev, "stream %d rsz/scale: %dx%d -> %dx%d\n",
		rsz->id, sink_crop->width, sink_crop->height,
		src_fmt->width, src_fmt->height);
	dev_dbg(rsz->rkisp1->dev, "chroma scaling %dx%d -> %dx%d\n",
		sink_c.width, sink_c.height, src_c.width, src_c.height);

	/* set values in the hw */
	rkisp1_rsz_config_regs(rsz, &sink_y, &sink_c, &src_y, &src_c, when);

	rkisp1_rsz_dump_regs(rsz);
पूर्ण

/* ----------------------------------------------------------------------------
 * Subdev pad operations
 */

अटल पूर्णांक rkisp1_rsz_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा rkisp1_resizer *rsz =
		container_of(sd, काष्ठा rkisp1_resizer, sd);
	काष्ठा v4l2_subdev_pad_config dummy_cfg;
	u32 pad = code->pad;
	पूर्णांक ret;

	अगर (code->pad == RKISP1_RSZ_PAD_SRC) अणु
		/* supported mbus codes on the src are the same as in the capture */
		काष्ठा rkisp1_capture *cap = &rsz->rkisp1->capture_devs[rsz->id];

		वापस rkisp1_cap_क्रमागत_mbus_codes(cap, code);
	पूर्ण

	/*
	 * The selfpath capture करोesn't support bayer क्रमmats. Thereक्रमe the selfpath resizer
	 * should support only YUV422 on the sink pad
	 */
	अगर (rsz->id == RKISP1_SELFPATH) अणु
		अगर (code->index > 0)
			वापस -EINVAL;
		code->code = MEDIA_BUS_FMT_YUYV8_2X8;
		वापस 0;
	पूर्ण

	/* supported mbus codes on the sink pad are the same as isp src pad */
	code->pad = RKISP1_ISP_PAD_SOURCE_VIDEO;
	ret = v4l2_subdev_call(&rsz->rkisp1->isp.sd, pad, क्रमागत_mbus_code,
			       &dummy_cfg, code);

	/* restore pad */
	code->pad = pad;
	code->flags = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक rkisp1_rsz_init_config(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_mbus_framefmt *sink_fmt, *src_fmt;
	काष्ठा v4l2_rect *sink_crop;

	sink_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, RKISP1_RSZ_PAD_SRC);
	sink_fmt->width = RKISP1_DEFAULT_WIDTH;
	sink_fmt->height = RKISP1_DEFAULT_HEIGHT;
	sink_fmt->field = V4L2_FIELD_NONE;
	sink_fmt->code = RKISP1_DEF_FMT;

	sink_crop = v4l2_subdev_get_try_crop(sd, cfg, RKISP1_RSZ_PAD_SINK);
	sink_crop->width = RKISP1_DEFAULT_WIDTH;
	sink_crop->height = RKISP1_DEFAULT_HEIGHT;
	sink_crop->left = 0;
	sink_crop->top = 0;

	src_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, RKISP1_RSZ_PAD_SINK);
	*src_fmt = *sink_fmt;

	/* NOTE: there is no crop in the source pad, only in the sink */

	वापस 0;
पूर्ण

अटल व्योम rkisp1_rsz_set_src_fmt(काष्ठा rkisp1_resizer *rsz,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_mbus_framefmt *क्रमmat,
				   अचिन्हित पूर्णांक which)
अणु
	स्थिर काष्ठा rkisp1_isp_mbus_info *sink_mbus_info;
	काष्ठा v4l2_mbus_framefmt *src_fmt, *sink_fmt;

	sink_fmt = rkisp1_rsz_get_pad_fmt(rsz, cfg, RKISP1_RSZ_PAD_SINK, which);
	src_fmt = rkisp1_rsz_get_pad_fmt(rsz, cfg, RKISP1_RSZ_PAD_SRC, which);
	sink_mbus_info = rkisp1_isp_mbus_info_get(sink_fmt->code);

	/* क्रम YUV क्रमmats, userspace can change the mbus code on the src pad अगर it is supported */
	अगर (sink_mbus_info->pixel_enc == V4L2_PIXEL_ENC_YUV &&
	    rkisp1_rsz_get_yuv_mbus_info(क्रमmat->code))
		src_fmt->code = क्रमmat->code;

	src_fmt->width = clamp_t(u32, क्रमmat->width,
				 rsz->config->min_rsz_width,
				 rsz->config->max_rsz_width);
	src_fmt->height = clamp_t(u32, क्रमmat->height,
				  rsz->config->min_rsz_height,
				  rsz->config->max_rsz_height);

	*क्रमmat = *src_fmt;
पूर्ण

अटल व्योम rkisp1_rsz_set_sink_crop(काष्ठा rkisp1_resizer *rsz,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_rect *r,
				     अचिन्हित पूर्णांक which)
अणु
	स्थिर काष्ठा rkisp1_isp_mbus_info *mbus_info;
	काष्ठा v4l2_mbus_framefmt *sink_fmt;
	काष्ठा v4l2_rect *sink_crop;

	sink_fmt = rkisp1_rsz_get_pad_fmt(rsz, cfg, RKISP1_RSZ_PAD_SINK, which);
	sink_crop = rkisp1_rsz_get_pad_crop(rsz, cfg, RKISP1_RSZ_PAD_SINK,
					    which);

	/* Not crop क्रम MP bayer raw data */
	mbus_info = rkisp1_isp_mbus_info_get(sink_fmt->code);

	अगर (rsz->id == RKISP1_MAINPATH &&
	    mbus_info->pixel_enc == V4L2_PIXEL_ENC_BAYER) अणु
		sink_crop->left = 0;
		sink_crop->top = 0;
		sink_crop->width = sink_fmt->width;
		sink_crop->height = sink_fmt->height;

		*r = *sink_crop;
		वापस;
	पूर्ण

	sink_crop->left = ALIGN(r->left, 2);
	sink_crop->width = ALIGN(r->width, 2);
	sink_crop->top = r->top;
	sink_crop->height = r->height;
	rkisp1_sd_adjust_crop(sink_crop, sink_fmt);

	*r = *sink_crop;
पूर्ण

अटल व्योम rkisp1_rsz_set_sink_fmt(काष्ठा rkisp1_resizer *rsz,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_mbus_framefmt *क्रमmat,
				    अचिन्हित पूर्णांक which)
अणु
	स्थिर काष्ठा rkisp1_isp_mbus_info *mbus_info;
	काष्ठा v4l2_mbus_framefmt *sink_fmt, *src_fmt;
	काष्ठा v4l2_rect *sink_crop;

	sink_fmt = rkisp1_rsz_get_pad_fmt(rsz, cfg, RKISP1_RSZ_PAD_SINK, which);
	src_fmt = rkisp1_rsz_get_pad_fmt(rsz, cfg, RKISP1_RSZ_PAD_SRC, which);
	sink_crop = rkisp1_rsz_get_pad_crop(rsz, cfg, RKISP1_RSZ_PAD_SINK,
					    which);
	अगर (rsz->id == RKISP1_SELFPATH)
		sink_fmt->code = MEDIA_BUS_FMT_YUYV8_2X8;
	अन्यथा
		sink_fmt->code = क्रमmat->code;

	mbus_info = rkisp1_isp_mbus_info_get(sink_fmt->code);
	अगर (!mbus_info || !(mbus_info->direction & RKISP1_ISP_SD_SRC)) अणु
		sink_fmt->code = RKISP1_DEF_FMT;
		mbus_info = rkisp1_isp_mbus_info_get(sink_fmt->code);
	पूर्ण
	अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE)
		rsz->pixel_enc = mbus_info->pixel_enc;

	/* Propagete to source pad */
	src_fmt->code = sink_fmt->code;

	sink_fmt->width = clamp_t(u32, क्रमmat->width,
				  RKISP1_ISP_MIN_WIDTH,
				  RKISP1_ISP_MAX_WIDTH);
	sink_fmt->height = clamp_t(u32, क्रमmat->height,
				   RKISP1_ISP_MIN_HEIGHT,
				   RKISP1_ISP_MAX_HEIGHT);

	*क्रमmat = *sink_fmt;

	/* Update sink crop */
	rkisp1_rsz_set_sink_crop(rsz, cfg, sink_crop, which);
पूर्ण

अटल पूर्णांक rkisp1_rsz_get_fmt(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा rkisp1_resizer *rsz =
		container_of(sd, काष्ठा rkisp1_resizer, sd);

	mutex_lock(&rsz->ops_lock);
	fmt->क्रमmat = *rkisp1_rsz_get_pad_fmt(rsz, cfg, fmt->pad, fmt->which);
	mutex_unlock(&rsz->ops_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_rsz_set_fmt(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा rkisp1_resizer *rsz =
		container_of(sd, काष्ठा rkisp1_resizer, sd);

	mutex_lock(&rsz->ops_lock);
	अगर (fmt->pad == RKISP1_RSZ_PAD_SINK)
		rkisp1_rsz_set_sink_fmt(rsz, cfg, &fmt->क्रमmat, fmt->which);
	अन्यथा
		rkisp1_rsz_set_src_fmt(rsz, cfg, &fmt->क्रमmat, fmt->which);

	mutex_unlock(&rsz->ops_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_rsz_get_selection(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा rkisp1_resizer *rsz =
		container_of(sd, काष्ठा rkisp1_resizer, sd);
	काष्ठा v4l2_mbus_framefmt *mf_sink;
	पूर्णांक ret = 0;

	अगर (sel->pad == RKISP1_RSZ_PAD_SRC)
		वापस -EINVAL;

	mutex_lock(&rsz->ops_lock);
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		mf_sink = rkisp1_rsz_get_pad_fmt(rsz, cfg, RKISP1_RSZ_PAD_SINK,
						 sel->which);
		sel->r.height = mf_sink->height;
		sel->r.width = mf_sink->width;
		sel->r.left = 0;
		sel->r.top = 0;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		sel->r = *rkisp1_rsz_get_pad_crop(rsz, cfg, RKISP1_RSZ_PAD_SINK,
						  sel->which);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&rsz->ops_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rkisp1_rsz_set_selection(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा rkisp1_resizer *rsz =
		container_of(sd, काष्ठा rkisp1_resizer, sd);

	अगर (sel->target != V4L2_SEL_TGT_CROP || sel->pad == RKISP1_RSZ_PAD_SRC)
		वापस -EINVAL;

	dev_dbg(rsz->rkisp1->dev, "%s: pad: %d sel(%d,%d)/%dx%d\n", __func__,
		sel->pad, sel->r.left, sel->r.top, sel->r.width, sel->r.height);

	mutex_lock(&rsz->ops_lock);
	rkisp1_rsz_set_sink_crop(rsz, cfg, &sel->r, sel->which);
	mutex_unlock(&rsz->ops_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations rkisp1_rsz_media_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops rkisp1_rsz_pad_ops = अणु
	.क्रमागत_mbus_code = rkisp1_rsz_क्रमागत_mbus_code,
	.get_selection = rkisp1_rsz_get_selection,
	.set_selection = rkisp1_rsz_set_selection,
	.init_cfg = rkisp1_rsz_init_config,
	.get_fmt = rkisp1_rsz_get_fmt,
	.set_fmt = rkisp1_rsz_set_fmt,
	.link_validate = v4l2_subdev_link_validate_शेष,
पूर्ण;

/* ----------------------------------------------------------------------------
 * Stream operations
 */

अटल पूर्णांक rkisp1_rsz_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा rkisp1_resizer *rsz =
		container_of(sd, काष्ठा rkisp1_resizer, sd);
	काष्ठा rkisp1_device *rkisp1 = rsz->rkisp1;
	काष्ठा rkisp1_capture *other = &rkisp1->capture_devs[rsz->id ^ 1];
	क्रमागत rkisp1_shaकरोw_regs_when when = RKISP1_SHADOW_REGS_SYNC;

	अगर (!enable) अणु
		rkisp1_dcrop_disable(rsz, RKISP1_SHADOW_REGS_ASYNC);
		rkisp1_rsz_disable(rsz, RKISP1_SHADOW_REGS_ASYNC);
		वापस 0;
	पूर्ण

	अगर (other->is_streaming)
		when = RKISP1_SHADOW_REGS_ASYNC;

	mutex_lock(&rsz->ops_lock);
	rkisp1_rsz_config(rsz, when);
	rkisp1_dcrop_config(rsz);

	mutex_unlock(&rsz->ops_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops rkisp1_rsz_video_ops = अणु
	.s_stream = rkisp1_rsz_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops rkisp1_rsz_ops = अणु
	.video = &rkisp1_rsz_video_ops,
	.pad = &rkisp1_rsz_pad_ops,
पूर्ण;

अटल व्योम rkisp1_rsz_unरेजिस्टर(काष्ठा rkisp1_resizer *rsz)
अणु
	v4l2_device_unरेजिस्टर_subdev(&rsz->sd);
	media_entity_cleanup(&rsz->sd.entity);
पूर्ण

अटल पूर्णांक rkisp1_rsz_रेजिस्टर(काष्ठा rkisp1_resizer *rsz)
अणु
	अटल स्थिर अक्षर * स्थिर dev_names[] = अणु
		RKISP1_RSZ_MP_DEV_NAME,
		RKISP1_RSZ_SP_DEV_NAME
	पूर्ण;
	काष्ठा media_pad *pads = rsz->pads;
	काष्ठा v4l2_subdev *sd = &rsz->sd;
	पूर्णांक ret;

	अगर (rsz->id == RKISP1_SELFPATH)
		rsz->config = &rkisp1_rsz_config_sp;
	अन्यथा
		rsz->config = &rkisp1_rsz_config_mp;

	v4l2_subdev_init(sd, &rkisp1_rsz_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	sd->entity.ops = &rkisp1_rsz_media_ops;
	sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_SCALER;
	sd->owner = THIS_MODULE;
	strscpy(sd->name, dev_names[rsz->id], माप(sd->name));

	pads[RKISP1_RSZ_PAD_SINK].flags = MEDIA_PAD_FL_SINK |
					  MEDIA_PAD_FL_MUST_CONNECT;
	pads[RKISP1_RSZ_PAD_SRC].flags = MEDIA_PAD_FL_SOURCE |
					 MEDIA_PAD_FL_MUST_CONNECT;

	rsz->pixel_enc = RKISP1_DEF_PIXEL_ENC;

	mutex_init(&rsz->ops_lock);
	ret = media_entity_pads_init(&sd->entity, RKISP1_RSZ_PAD_MAX, pads);
	अगर (ret)
		वापस ret;

	ret = v4l2_device_रेजिस्टर_subdev(&rsz->rkisp1->v4l2_dev, sd);
	अगर (ret) अणु
		dev_err(sd->dev, "Failed to register resizer subdev\n");
		जाओ err_cleanup_media_entity;
	पूर्ण

	rkisp1_rsz_init_config(sd, rsz->pad_cfg);
	वापस 0;

err_cleanup_media_entity:
	media_entity_cleanup(&sd->entity);

	वापस ret;
पूर्ण

पूर्णांक rkisp1_resizer_devs_रेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_resizer *rsz;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(rkisp1->resizer_devs); i++) अणु
		rsz = &rkisp1->resizer_devs[i];
		rsz->rkisp1 = rkisp1;
		rsz->id = i;
		ret = rkisp1_rsz_रेजिस्टर(rsz);
		अगर (ret)
			जाओ err_unreg_resizer_devs;
	पूर्ण

	वापस 0;

err_unreg_resizer_devs:
	क्रम (j = 0; j < i; j++) अणु
		rsz = &rkisp1->resizer_devs[j];
		rkisp1_rsz_unरेजिस्टर(rsz);
	पूर्ण

	वापस ret;
पूर्ण

व्योम rkisp1_resizer_devs_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_resizer *mp = &rkisp1->resizer_devs[RKISP1_MAINPATH];
	काष्ठा rkisp1_resizer *sp = &rkisp1->resizer_devs[RKISP1_SELFPATH];

	rkisp1_rsz_unरेजिस्टर(mp);
	rkisp1_rsz_unरेजिस्टर(sp);
पूर्ण

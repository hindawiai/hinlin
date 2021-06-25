<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-csiphy.c
 *
 * Qualcomm MSM Camera Subप्रणाली - CSIPHY Module
 *
 * Copyright (c) 2011-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2016-2018 Linaro Ltd.
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "camss-csiphy.h"
#समावेश "camss.h"

#घोषणा MSM_CSIPHY_NAME "msm_csiphy"

काष्ठा csiphy_क्रमmat अणु
	u32 code;
	u8 bpp;
पूर्ण;

अटल स्थिर काष्ठा csiphy_क्रमmat csiphy_क्रमmats_8x16[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, 10 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा csiphy_क्रमmat csiphy_क्रमmats_8x96[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, 10 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा csiphy_क्रमmat csiphy_क्रमmats_sdm845[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, 8 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12 पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB14_1X14, 14 पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, 10 पूर्ण,
पूर्ण;

/*
 * csiphy_get_bpp - map media bus क्रमmat to bits per pixel
 * @क्रमmats: supported media bus क्रमmats array
 * @nक्रमmats: size of @क्रमmats array
 * @code: media bus क्रमmat code
 *
 * Return number of bits per pixel
 */
अटल u8 csiphy_get_bpp(स्थिर काष्ठा csiphy_क्रमmat *क्रमmats,
			 अचिन्हित पूर्णांक nक्रमmats, u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nक्रमmats; i++)
		अगर (code == क्रमmats[i].code)
			वापस क्रमmats[i].bpp;

	WARN(1, "Unknown format\n");

	वापस क्रमmats[0].bpp;
पूर्ण

/*
 * csiphy_set_घड़ी_rates - Calculate and set घड़ी rates on CSIPHY module
 * @csiphy: CSIPHY device
 */
अटल पूर्णांक csiphy_set_घड़ी_rates(काष्ठा csiphy_device *csiphy)
अणु
	काष्ठा device *dev = csiphy->camss->dev;
	s64 link_freq;
	पूर्णांक i, j;
	पूर्णांक ret;

	u8 bpp = csiphy_get_bpp(csiphy->क्रमmats, csiphy->nक्रमmats,
				csiphy->fmt[MSM_CSIPHY_PAD_SINK].code);
	u8 num_lanes = csiphy->cfg.csi2->lane_cfg.num_data;

	link_freq = camss_get_link_freq(&csiphy->subdev.entity, bpp, num_lanes);
	अगर (link_freq < 0)
		link_freq  = 0;

	क्रम (i = 0; i < csiphy->nघड़ीs; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &csiphy->घड़ी[i];

		अगर (csiphy->rate_set[i]) अणु
			u64 min_rate = link_freq / 4;
			दीर्घ round_rate;

			camss_add_घड़ी_margin(&min_rate);

			क्रम (j = 0; j < घड़ी->nfreqs; j++)
				अगर (min_rate < घड़ी->freq[j])
					अवरोध;

			अगर (j == घड़ी->nfreqs) अणु
				dev_err(dev,
					"Pixel clock is too high for CSIPHY\n");
				वापस -EINVAL;
			पूर्ण

			/* अगर sensor pixel घड़ी is not available */
			/* set highest possible CSIPHY घड़ी rate */
			अगर (min_rate == 0)
				j = घड़ी->nfreqs - 1;

			round_rate = clk_round_rate(घड़ी->clk, घड़ी->freq[j]);
			अगर (round_rate < 0) अणु
				dev_err(dev, "clk round rate failed: %ld\n",
					round_rate);
				वापस -EINVAL;
			पूर्ण

			csiphy->समयr_clk_rate = round_rate;

			ret = clk_set_rate(घड़ी->clk, csiphy->समयr_clk_rate);
			अगर (ret < 0) अणु
				dev_err(dev, "clk set rate failed: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csiphy_set_घातer - Power on/off CSIPHY module
 * @sd: CSIPHY V4L2 subdevice
 * @on: Requested घातer state
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csiphy_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा csiphy_device *csiphy = v4l2_get_subdevdata(sd);
	काष्ठा device *dev = csiphy->camss->dev;

	अगर (on) अणु
		पूर्णांक ret;

		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			वापस ret;
		पूर्ण

		ret = csiphy_set_घड़ी_rates(csiphy);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			वापस ret;
		पूर्ण

		ret = camss_enable_घड़ीs(csiphy->nघड़ीs, csiphy->घड़ी, dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			वापस ret;
		पूर्ण

		enable_irq(csiphy->irq);

		csiphy->ops->reset(csiphy);

		csiphy->ops->hw_version_पढ़ो(csiphy, dev);
	पूर्ण अन्यथा अणु
		disable_irq(csiphy->irq);

		camss_disable_घड़ीs(csiphy->nघड़ीs, csiphy->घड़ी);

		pm_runसमय_put_sync(dev);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csiphy_get_lane_mask - Calculate CSI2 lane mask configuration parameter
 * @lane_cfg - CSI2 lane configuration
 *
 * Return lane mask
 */
अटल u8 csiphy_get_lane_mask(काष्ठा csiphy_lanes_cfg *lane_cfg)
अणु
	u8 lane_mask;
	पूर्णांक i;

	lane_mask = 1 << lane_cfg->clk.pos;

	क्रम (i = 0; i < lane_cfg->num_data; i++)
		lane_mask |= 1 << lane_cfg->data[i].pos;

	वापस lane_mask;
पूर्ण

/*
 * csiphy_stream_on - Enable streaming on CSIPHY module
 * @csiphy: CSIPHY device
 *
 * Helper function to enable streaming on CSIPHY module.
 * Main configuration of CSIPHY module is also करोne here.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csiphy_stream_on(काष्ठा csiphy_device *csiphy)
अणु
	काष्ठा csiphy_config *cfg = &csiphy->cfg;
	s64 link_freq;
	u8 lane_mask = csiphy_get_lane_mask(&cfg->csi2->lane_cfg);
	u8 bpp = csiphy_get_bpp(csiphy->क्रमmats, csiphy->nक्रमmats,
				csiphy->fmt[MSM_CSIPHY_PAD_SINK].code);
	u8 num_lanes = csiphy->cfg.csi2->lane_cfg.num_data;
	u8 val;

	link_freq = camss_get_link_freq(&csiphy->subdev.entity, bpp, num_lanes);

	अगर (link_freq < 0) अणु
		dev_err(csiphy->camss->dev,
			"Cannot get CSI2 transmitter's link frequency\n");
		वापस -EINVAL;
	पूर्ण

	अगर (csiphy->base_clk_mux) अणु
		val = पढ़ोl_relaxed(csiphy->base_clk_mux);
		अगर (cfg->combo_mode && (lane_mask & 0x18) == 0x18) अणु
			val &= ~0xf0;
			val |= cfg->csid_id << 4;
		पूर्ण अन्यथा अणु
			val &= ~0xf;
			val |= cfg->csid_id;
		पूर्ण
		ग_लिखोl_relaxed(val, csiphy->base_clk_mux);

		/* Enक्रमce reg ग_लिखो ordering between clk mux & lane enabling */
		wmb();
	पूर्ण

	csiphy->ops->lanes_enable(csiphy, cfg, link_freq, lane_mask);

	वापस 0;
पूर्ण

/*
 * csiphy_stream_off - Disable streaming on CSIPHY module
 * @csiphy: CSIPHY device
 *
 * Helper function to disable streaming on CSIPHY module
 */
अटल व्योम csiphy_stream_off(काष्ठा csiphy_device *csiphy)
अणु
	csiphy->ops->lanes_disable(csiphy, &csiphy->cfg);
पूर्ण


/*
 * csiphy_set_stream - Enable/disable streaming on CSIPHY module
 * @sd: CSIPHY V4L2 subdevice
 * @enable: Requested streaming state
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csiphy_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा csiphy_device *csiphy = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (enable)
		ret = csiphy_stream_on(csiphy);
	अन्यथा
		csiphy_stream_off(csiphy);

	वापस ret;
पूर्ण

/*
 * __csiphy_get_क्रमmat - Get poपूर्णांकer to क्रमmat काष्ठाure
 * @csiphy: CSIPHY device
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad from which क्रमmat is requested
 * @which: TRY or ACTIVE क्रमmat
 *
 * Return poपूर्णांकer to TRY or ACTIVE क्रमmat काष्ठाure
 */
अटल काष्ठा v4l2_mbus_framefmt *
__csiphy_get_क्रमmat(काष्ठा csiphy_device *csiphy,
		    काष्ठा v4l2_subdev_pad_config *cfg,
		    अचिन्हित पूर्णांक pad,
		    क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&csiphy->subdev, cfg, pad);

	वापस &csiphy->fmt[pad];
पूर्ण

/*
 * csiphy_try_क्रमmat - Handle try क्रमmat by pad subdev method
 * @csiphy: CSIPHY device
 * @cfg: V4L2 subdev pad configuration
 * @pad: pad on which क्रमmat is requested
 * @fmt: poपूर्णांकer to v4l2 क्रमmat काष्ठाure
 * @which: wanted subdev क्रमmat
 */
अटल व्योम csiphy_try_क्रमmat(काष्ठा csiphy_device *csiphy,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      अचिन्हित पूर्णांक pad,
			      काष्ठा v4l2_mbus_framefmt *fmt,
			      क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल MSM_CSIPHY_PAD_SINK:
		/* Set क्रमmat on sink pad */

		क्रम (i = 0; i < csiphy->nक्रमmats; i++)
			अगर (fmt->code == csiphy->क्रमmats[i].code)
				अवरोध;

		/* If not found, use UYVY as शेष */
		अगर (i >= csiphy->nक्रमmats)
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, 1, 8191);
		fmt->height = clamp_t(u32, fmt->height, 1, 8191);

		fmt->field = V4L2_FIELD_NONE;
		fmt->colorspace = V4L2_COLORSPACE_SRGB;

		अवरोध;

	हाल MSM_CSIPHY_PAD_SRC:
		/* Set and वापस a क्रमmat same as sink pad */

		*fmt = *__csiphy_get_क्रमmat(csiphy, cfg, MSM_CSID_PAD_SINK,
					    which);

		अवरोध;
	पूर्ण
पूर्ण

/*
 * csiphy_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd: CSIPHY V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @code: poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csiphy_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा csiphy_device *csiphy = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	अगर (code->pad == MSM_CSIPHY_PAD_SINK) अणु
		अगर (code->index >= csiphy->nक्रमmats)
			वापस -EINVAL;

		code->code = csiphy->क्रमmats[code->index].code;
	पूर्ण अन्यथा अणु
		अगर (code->index > 0)
			वापस -EINVAL;

		क्रमmat = __csiphy_get_क्रमmat(csiphy, cfg, MSM_CSIPHY_PAD_SINK,
					     code->which);

		code->code = क्रमmat->code;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csiphy_क्रमागत_frame_size - Handle frame size क्रमागतeration
 * @sd: CSIPHY V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fse: poपूर्णांकer to v4l2_subdev_frame_size_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csiphy_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा csiphy_device *csiphy = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	csiphy_try_क्रमmat(csiphy, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	csiphy_try_क्रमmat(csiphy, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * csiphy_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd: CSIPHY V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक csiphy_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा csiphy_device *csiphy = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csiphy_get_क्रमmat(csiphy, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;

	वापस 0;
पूर्ण

/*
 * csiphy_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd: CSIPHY V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 *
 * Return -EINVAL or zero on success
 */
अटल पूर्णांक csiphy_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा csiphy_device *csiphy = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csiphy_get_क्रमmat(csiphy, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	csiphy_try_क्रमmat(csiphy, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == MSM_CSIPHY_PAD_SINK) अणु
		क्रमmat = __csiphy_get_क्रमmat(csiphy, cfg, MSM_CSIPHY_PAD_SRC,
					     fmt->which);

		*क्रमmat = fmt->क्रमmat;
		csiphy_try_क्रमmat(csiphy, cfg, MSM_CSIPHY_PAD_SRC, क्रमmat,
				  fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csiphy_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: CSIPHY V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csiphy_init_क्रमmats(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.pad = MSM_CSIPHY_PAD_SINK,
		.which = fh ? V4L2_SUBDEV_FORMAT_TRY :
			      V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat = अणु
			.code = MEDIA_BUS_FMT_UYVY8_2X8,
			.width = 1920,
			.height = 1080
		पूर्ण
	पूर्ण;

	वापस csiphy_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);
पूर्ण

/*
 * msm_csiphy_subdev_init - Initialize CSIPHY device काष्ठाure and resources
 * @csiphy: CSIPHY device
 * @res: CSIPHY module resources table
 * @id: CSIPHY module id
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक msm_csiphy_subdev_init(काष्ठा camss *camss,
			   काष्ठा csiphy_device *csiphy,
			   स्थिर काष्ठा resources *res, u8 id)
अणु
	काष्ठा device *dev = camss->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *r;
	पूर्णांक i, j;
	पूर्णांक ret;

	csiphy->camss = camss;
	csiphy->id = id;
	csiphy->cfg.combo_mode = 0;

	अगर (camss->version == CAMSS_8x16) अणु
		csiphy->ops = &csiphy_ops_2ph_1_0;
		csiphy->क्रमmats = csiphy_क्रमmats_8x16;
		csiphy->nक्रमmats = ARRAY_SIZE(csiphy_क्रमmats_8x16);
	पूर्ण अन्यथा अगर (camss->version == CAMSS_8x96 ||
		   camss->version == CAMSS_660) अणु
		csiphy->ops = &csiphy_ops_3ph_1_0;
		csiphy->क्रमmats = csiphy_क्रमmats_8x96;
		csiphy->nक्रमmats = ARRAY_SIZE(csiphy_क्रमmats_8x96);
	पूर्ण अन्यथा अगर (camss->version == CAMSS_845) अणु
		csiphy->ops = &csiphy_ops_3ph_1_0;
		csiphy->क्रमmats = csiphy_क्रमmats_sdm845;
		csiphy->nक्रमmats = ARRAY_SIZE(csiphy_क्रमmats_sdm845);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* Memory */

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, res->reg[0]);
	csiphy->base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(csiphy->base))
		वापस PTR_ERR(csiphy->base);

	अगर (camss->version == CAMSS_8x16 ||
	    camss->version == CAMSS_8x96) अणु
		r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						 res->reg[1]);
		csiphy->base_clk_mux = devm_ioremap_resource(dev, r);
		अगर (IS_ERR(csiphy->base_clk_mux))
			वापस PTR_ERR(csiphy->base_clk_mux);
	पूर्ण अन्यथा अणु
		csiphy->base_clk_mux = शून्य;
	पूर्ण

	/* Interrupt */

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ,
					 res->पूर्णांकerrupt[0]);
	अगर (!r) अणु
		dev_err(dev, "missing IRQ\n");
		वापस -EINVAL;
	पूर्ण

	csiphy->irq = r->start;
	snम_लिखो(csiphy->irq_name, माप(csiphy->irq_name), "%s_%s%d",
		 dev_name(dev), MSM_CSIPHY_NAME, csiphy->id);

	ret = devm_request_irq(dev, csiphy->irq, csiphy->ops->isr,
			       IRQF_TRIGGER_RISING, csiphy->irq_name, csiphy);
	अगर (ret < 0) अणु
		dev_err(dev, "request_irq failed: %d\n", ret);
		वापस ret;
	पूर्ण

	disable_irq(csiphy->irq);

	/* Clocks */

	csiphy->nघड़ीs = 0;
	जबतक (res->घड़ी[csiphy->nघड़ीs])
		csiphy->nघड़ीs++;

	csiphy->घड़ी = devm_kसुस्मृति(dev,
				     csiphy->nघड़ीs, माप(*csiphy->घड़ी),
				     GFP_KERNEL);
	अगर (!csiphy->घड़ी)
		वापस -ENOMEM;

	csiphy->rate_set = devm_kसुस्मृति(dev,
					csiphy->nघड़ीs,
					माप(*csiphy->rate_set),
					GFP_KERNEL);
	अगर (!csiphy->rate_set)
		वापस -ENOMEM;

	क्रम (i = 0; i < csiphy->nघड़ीs; i++) अणु
		काष्ठा camss_घड़ी *घड़ी = &csiphy->घड़ी[i];

		घड़ी->clk = devm_clk_get(dev, res->घड़ी[i]);
		अगर (IS_ERR(घड़ी->clk))
			वापस PTR_ERR(घड़ी->clk);

		घड़ी->name = res->घड़ी[i];

		घड़ी->nfreqs = 0;
		जबतक (res->घड़ी_rate[i][घड़ी->nfreqs])
			घड़ी->nfreqs++;

		अगर (!घड़ी->nfreqs) अणु
			घड़ी->freq = शून्य;
			जारी;
		पूर्ण

		घड़ी->freq = devm_kसुस्मृति(dev,
					   घड़ी->nfreqs,
					   माप(*घड़ी->freq),
					   GFP_KERNEL);
		अगर (!घड़ी->freq)
			वापस -ENOMEM;

		क्रम (j = 0; j < घड़ी->nfreqs; j++)
			घड़ी->freq[j] = res->घड़ी_rate[i][j];

		अगर (!म_भेद(घड़ी->name, "csiphy0_timer") ||
		    !म_भेद(घड़ी->name, "csiphy1_timer") ||
		    !म_भेद(घड़ी->name, "csiphy2_timer"))
			csiphy->rate_set[i] = true;

		अगर (camss->version == CAMSS_660 &&
		    (!म_भेद(घड़ी->name, "csi0_phy") ||
		     !म_भेद(घड़ी->name, "csi1_phy") ||
		     !म_भेद(घड़ी->name, "csi2_phy")))
			csiphy->rate_set[i] = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csiphy_link_setup - Setup CSIPHY connections
 * @entity: Poपूर्णांकer to media entity काष्ठाure
 * @local: Poपूर्णांकer to local pad
 * @remote: Poपूर्णांकer to remote pad
 * @flags: Link flags
 *
 * Rवापस 0 on success
 */
अटल पूर्णांक csiphy_link_setup(काष्ठा media_entity *entity,
			     स्थिर काष्ठा media_pad *local,
			     स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	अगर ((local->flags & MEDIA_PAD_FL_SOURCE) &&
	    (flags & MEDIA_LNK_FL_ENABLED)) अणु
		काष्ठा v4l2_subdev *sd;
		काष्ठा csiphy_device *csiphy;
		काष्ठा csid_device *csid;

		अगर (media_entity_remote_pad(local))
			वापस -EBUSY;

		sd = media_entity_to_v4l2_subdev(entity);
		csiphy = v4l2_get_subdevdata(sd);

		sd = media_entity_to_v4l2_subdev(remote->entity);
		csid = v4l2_get_subdevdata(sd);

		csiphy->cfg.csid_id = csid->id;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops csiphy_core_ops = अणु
	.s_घातer = csiphy_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops csiphy_video_ops = अणु
	.s_stream = csiphy_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops csiphy_pad_ops = अणु
	.क्रमागत_mbus_code = csiphy_क्रमागत_mbus_code,
	.क्रमागत_frame_size = csiphy_क्रमागत_frame_size,
	.get_fmt = csiphy_get_क्रमmat,
	.set_fmt = csiphy_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops csiphy_v4l2_ops = अणु
	.core = &csiphy_core_ops,
	.video = &csiphy_video_ops,
	.pad = &csiphy_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops csiphy_v4l2_पूर्णांकernal_ops = अणु
	.खोलो = csiphy_init_क्रमmats,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations csiphy_media_ops = अणु
	.link_setup = csiphy_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * msm_csiphy_रेजिस्टर_entity - Register subdev node क्रम CSIPHY module
 * @csiphy: CSIPHY device
 * @v4l2_dev: V4L2 device
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक msm_csiphy_रेजिस्टर_entity(काष्ठा csiphy_device *csiphy,
			       काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा v4l2_subdev *sd = &csiphy->subdev;
	काष्ठा media_pad *pads = csiphy->pads;
	काष्ठा device *dev = csiphy->camss->dev;
	पूर्णांक ret;

	v4l2_subdev_init(sd, &csiphy_v4l2_ops);
	sd->पूर्णांकernal_ops = &csiphy_v4l2_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	snम_लिखो(sd->name, ARRAY_SIZE(sd->name), "%s%d",
		 MSM_CSIPHY_NAME, csiphy->id);
	v4l2_set_subdevdata(sd, csiphy);

	ret = csiphy_init_क्रमmats(sd, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to init format: %d\n", ret);
		वापस ret;
	पूर्ण

	pads[MSM_CSIPHY_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[MSM_CSIPHY_PAD_SRC].flags = MEDIA_PAD_FL_SOURCE;

	sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	sd->entity.ops = &csiphy_media_ops;
	ret = media_entity_pads_init(&sd->entity, MSM_CSIPHY_PADS_NUM, pads);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to init media entity: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, sd);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register subdev: %d\n", ret);
		media_entity_cleanup(&sd->entity);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * msm_csiphy_unरेजिस्टर_entity - Unरेजिस्टर CSIPHY module subdev node
 * @csiphy: CSIPHY device
 */
व्योम msm_csiphy_unरेजिस्टर_entity(काष्ठा csiphy_device *csiphy)
अणु
	v4l2_device_unरेजिस्टर_subdev(&csiphy->subdev);
	media_entity_cleanup(&csiphy->subdev.entity);
पूर्ण

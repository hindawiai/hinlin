<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Rockchip ISP1 Driver - ISP Subdevice
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Based on Rockchip ISP1 driver by Rockchip Electronics Co., Ltd.
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 */

#समावेश <linux/iopoll.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-mipi-dphy.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/videodev2.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <media/v4l2-event.h>

#समावेश "rkisp1-common.h"

#घोषणा RKISP1_DEF_SINK_PAD_FMT MEDIA_BUS_FMT_SRGGB10_1X10
#घोषणा RKISP1_DEF_SRC_PAD_FMT MEDIA_BUS_FMT_YUYV8_2X8

#घोषणा RKISP1_ISP_DEV_NAME	RKISP1_DRIVER_NAME "_isp"

/*
 * NOTE: MIPI controller and input MUX are also configured in this file.
 * This is because ISP Subdev describes not only ISP submodule (input size,
 * क्रमmat, output size, क्रमmat), but also a भव route device.
 */

/*
 * There are many variables named with क्रमmat/frame in below code,
 * please see here क्रम their meaning.
 * Cropping in the sink pad defines the image region from the sensor.
 * Cropping in the source pad defines the region क्रम the Image Stabilizer (IS)
 *
 * Cropping regions of ISP
 *
 * +---------------------------------------------------------+
 * | Sensor image                                            |
 * | +---------------------------------------------------+   |
 * | | CIF_ISP_ACQ (क्रम black level)                     |   |
 * | | sink pad क्रमmat                                   |   |
 * | | +--------------------------------------------+    |   |
 * | | |    CIF_ISP_OUT                             |    |   |
 * | | |    sink pad crop                           |    |   |
 * | | |    +---------------------------------+     |    |   |
 * | | |    |   CIF_ISP_IS                    |     |    |   |
 * | | |    |   source pad crop and क्रमmat    |     |    |   |
 * | | |    +---------------------------------+     |    |   |
 * | | +--------------------------------------------+    |   |
 * | +---------------------------------------------------+   |
 * +---------------------------------------------------------+
 */

अटल स्थिर काष्ठा rkisp1_isp_mbus_info rkisp1_isp_क्रमmats[] = अणु
	अणु
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.pixel_enc	= V4L2_PIXEL_ENC_YUV,
		.direction	= RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SRGGB10_1X10,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW10,
		.bayer_pat	= RKISP1_RAW_RGGB,
		.bus_width	= 10,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SBGGR10_1X10,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW10,
		.bayer_pat	= RKISP1_RAW_BGGR,
		.bus_width	= 10,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SGBRG10_1X10,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW10,
		.bayer_pat	= RKISP1_RAW_GBRG,
		.bus_width	= 10,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SGRBG10_1X10,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW10,
		.bayer_pat	= RKISP1_RAW_GRBG,
		.bus_width	= 10,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SRGGB12_1X12,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW12,
		.bayer_pat	= RKISP1_RAW_RGGB,
		.bus_width	= 12,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SBGGR12_1X12,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW12,
		.bayer_pat	= RKISP1_RAW_BGGR,
		.bus_width	= 12,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SGBRG12_1X12,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW12,
		.bayer_pat	= RKISP1_RAW_GBRG,
		.bus_width	= 12,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SGRBG12_1X12,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW12,
		.bayer_pat	= RKISP1_RAW_GRBG,
		.bus_width	= 12,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SRGGB8_1X8,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW8,
		.bayer_pat	= RKISP1_RAW_RGGB,
		.bus_width	= 8,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SBGGR8_1X8,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW8,
		.bayer_pat	= RKISP1_RAW_BGGR,
		.bus_width	= 8,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SGBRG8_1X8,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW8,
		.bayer_pat	= RKISP1_RAW_GBRG,
		.bus_width	= 8,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_SGRBG8_1X8,
		.pixel_enc	= V4L2_PIXEL_ENC_BAYER,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_RAW8,
		.bayer_pat	= RKISP1_RAW_GRBG,
		.bus_width	= 8,
		.direction	= RKISP1_ISP_SD_SINK | RKISP1_ISP_SD_SRC,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_1X16,
		.pixel_enc	= V4L2_PIXEL_ENC_YUV,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_YUV422_8b,
		.yuv_seq	= RKISP1_CIF_ISP_ACQ_PROP_YCBYCR,
		.bus_width	= 16,
		.direction	= RKISP1_ISP_SD_SINK,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_1X16,
		.pixel_enc	= V4L2_PIXEL_ENC_YUV,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_YUV422_8b,
		.yuv_seq	= RKISP1_CIF_ISP_ACQ_PROP_YCRYCB,
		.bus_width	= 16,
		.direction	= RKISP1_ISP_SD_SINK,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_1X16,
		.pixel_enc	= V4L2_PIXEL_ENC_YUV,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_YUV422_8b,
		.yuv_seq	= RKISP1_CIF_ISP_ACQ_PROP_CBYCRY,
		.bus_width	= 16,
		.direction	= RKISP1_ISP_SD_SINK,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_1X16,
		.pixel_enc	= V4L2_PIXEL_ENC_YUV,
		.mipi_dt	= RKISP1_CIF_CSI2_DT_YUV422_8b,
		.yuv_seq	= RKISP1_CIF_ISP_ACQ_PROP_CRYCBY,
		.bus_width	= 16,
		.direction	= RKISP1_ISP_SD_SINK,
	पूर्ण,
पूर्ण;

/* ----------------------------------------------------------------------------
 * Helpers
 */

स्थिर काष्ठा rkisp1_isp_mbus_info *rkisp1_isp_mbus_info_get(u32 mbus_code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rkisp1_isp_क्रमmats); i++) अणु
		स्थिर काष्ठा rkisp1_isp_mbus_info *fmt = &rkisp1_isp_क्रमmats[i];

		अगर (fmt->mbus_code == mbus_code)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा v4l2_subdev *rkisp1_get_remote_sensor(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा media_pad *local, *remote;
	काष्ठा media_entity *sensor_me;

	local = &sd->entity.pads[RKISP1_ISP_PAD_SINK_VIDEO];
	remote = media_entity_remote_pad(local);
	अगर (!remote)
		वापस शून्य;

	sensor_me = remote->entity;
	वापस media_entity_to_v4l2_subdev(sensor_me);
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
rkisp1_isp_get_pad_fmt(काष्ठा rkisp1_isp *isp,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       अचिन्हित पूर्णांक pad, u32 which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&isp->sd, cfg, pad);
	अन्यथा
		वापस v4l2_subdev_get_try_क्रमmat(&isp->sd, isp->pad_cfg, pad);
पूर्ण

अटल काष्ठा v4l2_rect *
rkisp1_isp_get_pad_crop(काष्ठा rkisp1_isp *isp,
			काष्ठा v4l2_subdev_pad_config *cfg,
			अचिन्हित पूर्णांक pad, u32 which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_crop(&isp->sd, cfg, pad);
	अन्यथा
		वापस v4l2_subdev_get_try_crop(&isp->sd, isp->pad_cfg, pad);
पूर्ण

/* ----------------------------------------------------------------------------
 * Camera Interface रेजिस्टरs configurations
 */

/*
 * Image Stabilization.
 * This should only be called when configuring CIF
 * or at the frame end पूर्णांकerrupt
 */
अटल व्योम rkisp1_config_ism(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा v4l2_rect *src_crop =
		rkisp1_isp_get_pad_crop(&rkisp1->isp, शून्य,
					RKISP1_ISP_PAD_SOURCE_VIDEO,
					V4L2_SUBDEV_FORMAT_ACTIVE);
	u32 val;

	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_ISP_IS_RECENTER);
	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_ISP_IS_MAX_DX);
	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_ISP_IS_MAX_DY);
	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_ISP_IS_DISPLACE);
	rkisp1_ग_लिखो(rkisp1, src_crop->left, RKISP1_CIF_ISP_IS_H_OFFS);
	rkisp1_ग_लिखो(rkisp1, src_crop->top, RKISP1_CIF_ISP_IS_V_OFFS);
	rkisp1_ग_लिखो(rkisp1, src_crop->width, RKISP1_CIF_ISP_IS_H_SIZE);
	rkisp1_ग_लिखो(rkisp1, src_crop->height, RKISP1_CIF_ISP_IS_V_SIZE);

	/* IS(Image Stabilization) is always on, working as output crop */
	rkisp1_ग_लिखो(rkisp1, 1, RKISP1_CIF_ISP_IS_CTRL);
	val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_CTRL);
	val |= RKISP1_CIF_ISP_CTRL_ISP_CFG_UPD;
	rkisp1_ग_लिखो(rkisp1, val, RKISP1_CIF_ISP_CTRL);
पूर्ण

/*
 * configure ISP blocks with input क्रमmat, size......
 */
अटल पूर्णांक rkisp1_config_isp(काष्ठा rkisp1_device *rkisp1)
अणु
	u32 isp_ctrl = 0, irq_mask = 0, acq_mult = 0, संकेत = 0;
	स्थिर काष्ठा rkisp1_isp_mbus_info *src_fmt, *sink_fmt;
	काष्ठा rkisp1_sensor_async *sensor;
	काष्ठा v4l2_mbus_framefmt *sink_frm;
	काष्ठा v4l2_rect *sink_crop;

	sensor = rkisp1->active_sensor;
	sink_fmt = rkisp1->isp.sink_fmt;
	src_fmt = rkisp1->isp.src_fmt;
	sink_frm = rkisp1_isp_get_pad_fmt(&rkisp1->isp, शून्य,
					  RKISP1_ISP_PAD_SINK_VIDEO,
					  V4L2_SUBDEV_FORMAT_ACTIVE);
	sink_crop = rkisp1_isp_get_pad_crop(&rkisp1->isp, शून्य,
					    RKISP1_ISP_PAD_SINK_VIDEO,
					    V4L2_SUBDEV_FORMAT_ACTIVE);

	अगर (sink_fmt->pixel_enc == V4L2_PIXEL_ENC_BAYER) अणु
		acq_mult = 1;
		अगर (src_fmt->pixel_enc == V4L2_PIXEL_ENC_BAYER) अणु
			अगर (sensor->mbus_type == V4L2_MBUS_BT656)
				isp_ctrl = RKISP1_CIF_ISP_CTRL_ISP_MODE_RAW_PICT_ITU656;
			अन्यथा
				isp_ctrl = RKISP1_CIF_ISP_CTRL_ISP_MODE_RAW_PICT;
		पूर्ण अन्यथा अणु
			rkisp1_ग_लिखो(rkisp1, RKISP1_CIF_ISP_DEMOSAIC_TH(0xc),
				     RKISP1_CIF_ISP_DEMOSAIC);

			अगर (sensor->mbus_type == V4L2_MBUS_BT656)
				isp_ctrl = RKISP1_CIF_ISP_CTRL_ISP_MODE_BAYER_ITU656;
			अन्यथा
				isp_ctrl = RKISP1_CIF_ISP_CTRL_ISP_MODE_BAYER_ITU601;
		पूर्ण
	पूर्ण अन्यथा अगर (sink_fmt->pixel_enc == V4L2_PIXEL_ENC_YUV) अणु
		acq_mult = 2;
		अगर (sensor->mbus_type == V4L2_MBUS_CSI2_DPHY) अणु
			isp_ctrl = RKISP1_CIF_ISP_CTRL_ISP_MODE_ITU601;
		पूर्ण अन्यथा अणु
			अगर (sensor->mbus_type == V4L2_MBUS_BT656)
				isp_ctrl = RKISP1_CIF_ISP_CTRL_ISP_MODE_ITU656;
			अन्यथा
				isp_ctrl = RKISP1_CIF_ISP_CTRL_ISP_MODE_ITU601;
		पूर्ण

		irq_mask |= RKISP1_CIF_ISP_DATA_LOSS;
	पूर्ण

	/* Set up input acquisition properties */
	अगर (sensor->mbus_type == V4L2_MBUS_BT656 ||
	    sensor->mbus_type == V4L2_MBUS_PARALLEL) अणु
		अगर (sensor->mbus_flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
			संकेत = RKISP1_CIF_ISP_ACQ_PROP_POS_EDGE;
	पूर्ण

	अगर (sensor->mbus_type == V4L2_MBUS_PARALLEL) अणु
		अगर (sensor->mbus_flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			संकेत |= RKISP1_CIF_ISP_ACQ_PROP_VSYNC_LOW;

		अगर (sensor->mbus_flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
			संकेत |= RKISP1_CIF_ISP_ACQ_PROP_HSYNC_LOW;
	पूर्ण

	rkisp1_ग_लिखो(rkisp1, isp_ctrl, RKISP1_CIF_ISP_CTRL);
	rkisp1_ग_लिखो(rkisp1, संकेत | sink_fmt->yuv_seq |
		     RKISP1_CIF_ISP_ACQ_PROP_BAYER_PAT(sink_fmt->bayer_pat) |
		     RKISP1_CIF_ISP_ACQ_PROP_FIELD_SEL_ALL,
		     RKISP1_CIF_ISP_ACQ_PROP);
	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_ISP_ACQ_NR_FRAMES);

	/* Acquisition Size */
	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_ISP_ACQ_H_OFFS);
	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_ISP_ACQ_V_OFFS);
	rkisp1_ग_लिखो(rkisp1,
		     acq_mult * sink_frm->width, RKISP1_CIF_ISP_ACQ_H_SIZE);
	rkisp1_ग_लिखो(rkisp1, sink_frm->height, RKISP1_CIF_ISP_ACQ_V_SIZE);

	/* ISP Out Area */
	rkisp1_ग_लिखो(rkisp1, sink_crop->left, RKISP1_CIF_ISP_OUT_H_OFFS);
	rkisp1_ग_लिखो(rkisp1, sink_crop->top, RKISP1_CIF_ISP_OUT_V_OFFS);
	rkisp1_ग_लिखो(rkisp1, sink_crop->width, RKISP1_CIF_ISP_OUT_H_SIZE);
	rkisp1_ग_लिखो(rkisp1, sink_crop->height, RKISP1_CIF_ISP_OUT_V_SIZE);

	irq_mask |= RKISP1_CIF_ISP_FRAME | RKISP1_CIF_ISP_V_START |
		    RKISP1_CIF_ISP_PIC_SIZE_ERROR;
	rkisp1_ग_लिखो(rkisp1, irq_mask, RKISP1_CIF_ISP_IMSC);

	अगर (src_fmt->pixel_enc == V4L2_PIXEL_ENC_BAYER) अणु
		rkisp1_params_disable(&rkisp1->params);
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_mbus_framefmt *src_frm;

		src_frm = rkisp1_isp_get_pad_fmt(&rkisp1->isp, शून्य,
						 RKISP1_ISP_PAD_SINK_VIDEO,
						 V4L2_SUBDEV_FORMAT_ACTIVE);
		rkisp1_params_configure(&rkisp1->params, sink_fmt->bayer_pat,
					src_frm->quantization);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_config_dvp(काष्ठा rkisp1_device *rkisp1)
अणु
	स्थिर काष्ठा rkisp1_isp_mbus_info *sink_fmt = rkisp1->isp.sink_fmt;
	u32 val, input_sel;

	चयन (sink_fmt->bus_width) अणु
	हाल 8:
		input_sel = RKISP1_CIF_ISP_ACQ_PROP_IN_SEL_8B_ZERO;
		अवरोध;
	हाल 10:
		input_sel = RKISP1_CIF_ISP_ACQ_PROP_IN_SEL_10B_ZERO;
		अवरोध;
	हाल 12:
		input_sel = RKISP1_CIF_ISP_ACQ_PROP_IN_SEL_12B;
		अवरोध;
	शेष:
		dev_err(rkisp1->dev, "Invalid bus width\n");
		वापस -EINVAL;
	पूर्ण

	val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_ACQ_PROP);
	rkisp1_ग_लिखो(rkisp1, val | input_sel, RKISP1_CIF_ISP_ACQ_PROP);

	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_config_mipi(काष्ठा rkisp1_device *rkisp1)
अणु
	स्थिर काष्ठा rkisp1_isp_mbus_info *sink_fmt = rkisp1->isp.sink_fmt;
	अचिन्हित पूर्णांक lanes = rkisp1->active_sensor->lanes;
	u32 mipi_ctrl;

	अगर (lanes < 1 || lanes > 4)
		वापस -EINVAL;

	mipi_ctrl = RKISP1_CIF_MIPI_CTRL_NUM_LANES(lanes - 1) |
		    RKISP1_CIF_MIPI_CTRL_SHUTDOWNLANES(0xf) |
		    RKISP1_CIF_MIPI_CTRL_ERR_SOT_SYNC_HS_SKIP |
		    RKISP1_CIF_MIPI_CTRL_CLOCKLANE_ENA;

	rkisp1_ग_लिखो(rkisp1, mipi_ctrl, RKISP1_CIF_MIPI_CTRL);

	/* Configure Data Type and Virtual Channel */
	rkisp1_ग_लिखो(rkisp1,
		     RKISP1_CIF_MIPI_DATA_SEL_DT(sink_fmt->mipi_dt) |
		     RKISP1_CIF_MIPI_DATA_SEL_VC(0),
		     RKISP1_CIF_MIPI_IMG_DATA_SEL);

	/* Clear MIPI पूर्णांकerrupts */
	rkisp1_ग_लिखो(rkisp1, ~0, RKISP1_CIF_MIPI_ICR);
	/*
	 * Disable RKISP1_CIF_MIPI_ERR_DPHY पूर्णांकerrupt here temporary क्रम
	 * isp bus may be dead when चयन isp.
	 */
	rkisp1_ग_लिखो(rkisp1,
		     RKISP1_CIF_MIPI_FRAME_END | RKISP1_CIF_MIPI_ERR_CSI |
		     RKISP1_CIF_MIPI_ERR_DPHY |
		     RKISP1_CIF_MIPI_SYNC_FIFO_OVFLW(0x03) |
		     RKISP1_CIF_MIPI_ADD_DATA_OVFLW,
		     RKISP1_CIF_MIPI_IMSC);

	dev_dbg(rkisp1->dev, "\n  MIPI_CTRL 0x%08x\n"
		"  MIPI_IMG_DATA_SEL 0x%08x\n"
		"  MIPI_STATUS 0x%08x\n"
		"  MIPI_IMSC 0x%08x\n",
		rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_CTRL),
		rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_IMG_DATA_SEL),
		rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_STATUS),
		rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_IMSC));

	वापस 0;
पूर्ण

/* Configure MUX */
अटल पूर्णांक rkisp1_config_path(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_sensor_async *sensor = rkisp1->active_sensor;
	u32 dpcl = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_VI_DPCL);
	पूर्णांक ret = 0;

	अगर (sensor->mbus_type == V4L2_MBUS_BT656 ||
	    sensor->mbus_type == V4L2_MBUS_PARALLEL) अणु
		ret = rkisp1_config_dvp(rkisp1);
		dpcl |= RKISP1_CIF_VI_DPCL_IF_SEL_PARALLEL;
	पूर्ण अन्यथा अगर (sensor->mbus_type == V4L2_MBUS_CSI2_DPHY) अणु
		ret = rkisp1_config_mipi(rkisp1);
		dpcl |= RKISP1_CIF_VI_DPCL_IF_SEL_MIPI;
	पूर्ण

	rkisp1_ग_लिखो(rkisp1, dpcl, RKISP1_CIF_VI_DPCL);

	वापस ret;
पूर्ण

/* Hardware configure Entry */
अटल पूर्णांक rkisp1_config_cअगर(काष्ठा rkisp1_device *rkisp1)
अणु
	u32 cअगर_id;
	पूर्णांक ret;

	cअगर_id = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_VI_ID);
	dev_dbg(rkisp1->dev, "CIF_ID 0x%08x\n", cअगर_id);

	ret = rkisp1_config_isp(rkisp1);
	अगर (ret)
		वापस ret;
	ret = rkisp1_config_path(rkisp1);
	अगर (ret)
		वापस ret;
	rkisp1_config_ism(rkisp1);

	वापस 0;
पूर्ण

अटल व्योम rkisp1_isp_stop(काष्ठा rkisp1_device *rkisp1)
अणु
	u32 val;

	/*
	 * ISP(mi) stop in mi frame end -> Stop ISP(mipi) ->
	 * Stop ISP(isp) ->रुको क्रम ISP isp off
	 */
	/* stop and clear MI, MIPI, and ISP पूर्णांकerrupts */
	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_MIPI_IMSC);
	rkisp1_ग_लिखो(rkisp1, ~0, RKISP1_CIF_MIPI_ICR);

	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_ISP_IMSC);
	rkisp1_ग_लिखो(rkisp1, ~0, RKISP1_CIF_ISP_ICR);

	rkisp1_ग_लिखो(rkisp1, 0, RKISP1_CIF_MI_IMSC);
	rkisp1_ग_लिखो(rkisp1, ~0, RKISP1_CIF_MI_ICR);
	val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_CTRL);
	rkisp1_ग_लिखो(rkisp1, val & (~RKISP1_CIF_MIPI_CTRL_OUTPUT_ENA),
		     RKISP1_CIF_MIPI_CTRL);
	/* stop ISP */
	val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_CTRL);
	val &= ~(RKISP1_CIF_ISP_CTRL_ISP_INFORM_ENABLE |
		 RKISP1_CIF_ISP_CTRL_ISP_ENABLE);
	rkisp1_ग_लिखो(rkisp1, val, RKISP1_CIF_ISP_CTRL);

	val = rkisp1_पढ़ो(rkisp1,	RKISP1_CIF_ISP_CTRL);
	rkisp1_ग_लिखो(rkisp1, val | RKISP1_CIF_ISP_CTRL_ISP_CFG_UPD,
		     RKISP1_CIF_ISP_CTRL);

	पढ़ोx_poll_समयout(पढ़ोl, rkisp1->base_addr + RKISP1_CIF_ISP_RIS,
			   val, val & RKISP1_CIF_ISP_OFF, 20, 100);
	rkisp1_ग_लिखो(rkisp1,
		     RKISP1_CIF_IRCL_MIPI_SW_RST | RKISP1_CIF_IRCL_ISP_SW_RST,
		     RKISP1_CIF_IRCL);
	rkisp1_ग_लिखो(rkisp1, 0x0, RKISP1_CIF_IRCL);
पूर्ण

अटल व्योम rkisp1_config_clk(काष्ठा rkisp1_device *rkisp1)
अणु
	u32 val = RKISP1_CIF_ICCL_ISP_CLK | RKISP1_CIF_ICCL_CP_CLK |
		  RKISP1_CIF_ICCL_MRSZ_CLK | RKISP1_CIF_ICCL_SRSZ_CLK |
		  RKISP1_CIF_ICCL_JPEG_CLK | RKISP1_CIF_ICCL_MI_CLK |
		  RKISP1_CIF_ICCL_IE_CLK | RKISP1_CIF_ICCL_MIPI_CLK |
		  RKISP1_CIF_ICCL_DCROP_CLK;

	rkisp1_ग_लिखो(rkisp1, val, RKISP1_CIF_ICCL);
पूर्ण

अटल व्योम rkisp1_isp_start(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_sensor_async *sensor = rkisp1->active_sensor;
	u32 val;

	rkisp1_config_clk(rkisp1);

	/* Activate MIPI */
	अगर (sensor->mbus_type == V4L2_MBUS_CSI2_DPHY) अणु
		val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_CTRL);
		rkisp1_ग_लिखो(rkisp1, val | RKISP1_CIF_MIPI_CTRL_OUTPUT_ENA,
			     RKISP1_CIF_MIPI_CTRL);
	पूर्ण
	/* Activate ISP */
	val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_CTRL);
	val |= RKISP1_CIF_ISP_CTRL_ISP_CFG_UPD |
	       RKISP1_CIF_ISP_CTRL_ISP_ENABLE |
	       RKISP1_CIF_ISP_CTRL_ISP_INFORM_ENABLE;
	rkisp1_ग_लिखो(rkisp1, val, RKISP1_CIF_ISP_CTRL);

	/*
	 * CIF spec says to रुको क्रम sufficient समय after enabling
	 * the MIPI पूर्णांकerface and beक्रमe starting the sensor output.
	 */
	usleep_range(1000, 1200);
पूर्ण

/* ----------------------------------------------------------------------------
 * Subdev pad operations
 */

अटल पूर्णांक rkisp1_isp_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अचिन्हित पूर्णांक i, dir;
	पूर्णांक pos = 0;

	अगर (code->pad == RKISP1_ISP_PAD_SINK_VIDEO) अणु
		dir = RKISP1_ISP_SD_SINK;
	पूर्ण अन्यथा अगर (code->pad == RKISP1_ISP_PAD_SOURCE_VIDEO) अणु
		dir = RKISP1_ISP_SD_SRC;
	पूर्ण अन्यथा अणु
		अगर (code->index > 0)
			वापस -EINVAL;
		code->code = MEDIA_BUS_FMT_METADATA_FIXED;
		वापस 0;
	पूर्ण

	अगर (code->index >= ARRAY_SIZE(rkisp1_isp_क्रमmats))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(rkisp1_isp_क्रमmats); i++) अणु
		स्थिर काष्ठा rkisp1_isp_mbus_info *fmt = &rkisp1_isp_क्रमmats[i];

		अगर (fmt->direction & dir)
			pos++;

		अगर (code->index == pos - 1) अणु
			code->code = fmt->mbus_code;
			अगर (fmt->pixel_enc == V4L2_PIXEL_ENC_YUV &&
			    dir == RKISP1_ISP_SD_SRC)
				code->flags =
					V4L2_SUBDEV_MBUS_CODE_CSC_QUANTIZATION;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rkisp1_isp_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	स्थिर काष्ठा rkisp1_isp_mbus_info *mbus_info;

	अगर (fse->pad == RKISP1_ISP_PAD_SINK_PARAMS ||
	    fse->pad == RKISP1_ISP_PAD_SOURCE_STATS)
		वापस -ENOTTY;

	अगर (fse->index > 0)
		वापस -EINVAL;

	mbus_info = rkisp1_isp_mbus_info_get(fse->code);
	अगर (!mbus_info)
		वापस -EINVAL;

	अगर (!(mbus_info->direction & RKISP1_ISP_SD_SINK) &&
	    fse->pad == RKISP1_ISP_PAD_SINK_VIDEO)
		वापस -EINVAL;

	अगर (!(mbus_info->direction & RKISP1_ISP_SD_SRC) &&
	    fse->pad == RKISP1_ISP_PAD_SOURCE_VIDEO)
		वापस -EINVAL;

	fse->min_width = RKISP1_ISP_MIN_WIDTH;
	fse->max_width = RKISP1_ISP_MAX_WIDTH;
	fse->min_height = RKISP1_ISP_MIN_HEIGHT;
	fse->max_height = RKISP1_ISP_MAX_HEIGHT;

	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_isp_init_config(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_mbus_framefmt *sink_fmt, *src_fmt;
	काष्ठा v4l2_rect *sink_crop, *src_crop;

	sink_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg,
					      RKISP1_ISP_PAD_SINK_VIDEO);
	sink_fmt->width = RKISP1_DEFAULT_WIDTH;
	sink_fmt->height = RKISP1_DEFAULT_HEIGHT;
	sink_fmt->field = V4L2_FIELD_NONE;
	sink_fmt->code = RKISP1_DEF_SINK_PAD_FMT;

	sink_crop = v4l2_subdev_get_try_crop(sd, cfg,
					     RKISP1_ISP_PAD_SINK_VIDEO);
	sink_crop->width = RKISP1_DEFAULT_WIDTH;
	sink_crop->height = RKISP1_DEFAULT_HEIGHT;
	sink_crop->left = 0;
	sink_crop->top = 0;

	src_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg,
					     RKISP1_ISP_PAD_SOURCE_VIDEO);
	*src_fmt = *sink_fmt;
	src_fmt->code = RKISP1_DEF_SRC_PAD_FMT;

	src_crop = v4l2_subdev_get_try_crop(sd, cfg,
					    RKISP1_ISP_PAD_SOURCE_VIDEO);
	*src_crop = *sink_crop;

	sink_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg,
					      RKISP1_ISP_PAD_SINK_PARAMS);
	src_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg,
					     RKISP1_ISP_PAD_SOURCE_STATS);
	sink_fmt->width = 0;
	sink_fmt->height = 0;
	sink_fmt->field = V4L2_FIELD_NONE;
	sink_fmt->code = MEDIA_BUS_FMT_METADATA_FIXED;
	*src_fmt = *sink_fmt;

	वापस 0;
पूर्ण

अटल व्योम rkisp1_isp_set_src_fmt(काष्ठा rkisp1_isp *isp,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_mbus_framefmt *क्रमmat,
				   अचिन्हित पूर्णांक which)
अणु
	स्थिर काष्ठा rkisp1_isp_mbus_info *mbus_info;
	काष्ठा v4l2_mbus_framefmt *src_fmt;
	स्थिर काष्ठा v4l2_rect *src_crop;

	src_fmt = rkisp1_isp_get_pad_fmt(isp, cfg,
					 RKISP1_ISP_PAD_SOURCE_VIDEO, which);
	src_crop = rkisp1_isp_get_pad_crop(isp, cfg,
					   RKISP1_ISP_PAD_SOURCE_VIDEO, which);

	src_fmt->code = क्रमmat->code;
	mbus_info = rkisp1_isp_mbus_info_get(src_fmt->code);
	अगर (!mbus_info || !(mbus_info->direction & RKISP1_ISP_SD_SRC)) अणु
		src_fmt->code = RKISP1_DEF_SRC_PAD_FMT;
		mbus_info = rkisp1_isp_mbus_info_get(src_fmt->code);
	पूर्ण
	अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE)
		isp->src_fmt = mbus_info;
	src_fmt->width  = src_crop->width;
	src_fmt->height = src_crop->height;

	/*
	 * The CSC API is used to allow userspace to क्रमce full
	 * quantization on YUV क्रमmats.
	 */
	अगर (क्रमmat->flags & V4L2_MBUS_FRAMEFMT_SET_CSC &&
	    क्रमmat->quantization == V4L2_QUANTIZATION_FULL_RANGE &&
	    mbus_info->pixel_enc == V4L2_PIXEL_ENC_YUV)
		src_fmt->quantization = V4L2_QUANTIZATION_FULL_RANGE;
	अन्यथा अगर (mbus_info->pixel_enc == V4L2_PIXEL_ENC_YUV)
		src_fmt->quantization = V4L2_QUANTIZATION_LIM_RANGE;
	अन्यथा
		src_fmt->quantization = V4L2_QUANTIZATION_FULL_RANGE;

	*क्रमmat = *src_fmt;
पूर्ण

अटल व्योम rkisp1_isp_set_src_crop(काष्ठा rkisp1_isp *isp,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_rect *r, अचिन्हित पूर्णांक which)
अणु
	काष्ठा v4l2_mbus_framefmt *src_fmt;
	स्थिर काष्ठा v4l2_rect *sink_crop;
	काष्ठा v4l2_rect *src_crop;

	src_crop = rkisp1_isp_get_pad_crop(isp, cfg,
					   RKISP1_ISP_PAD_SOURCE_VIDEO,
					   which);
	sink_crop = rkisp1_isp_get_pad_crop(isp, cfg,
					    RKISP1_ISP_PAD_SINK_VIDEO,
					    which);

	src_crop->left = ALIGN(r->left, 2);
	src_crop->width = ALIGN(r->width, 2);
	src_crop->top = r->top;
	src_crop->height = r->height;
	rkisp1_sd_adjust_crop_rect(src_crop, sink_crop);

	*r = *src_crop;

	/* Propagate to out क्रमmat */
	src_fmt = rkisp1_isp_get_pad_fmt(isp, cfg,
					 RKISP1_ISP_PAD_SOURCE_VIDEO, which);
	rkisp1_isp_set_src_fmt(isp, cfg, src_fmt, which);
पूर्ण

अटल व्योम rkisp1_isp_set_sink_crop(काष्ठा rkisp1_isp *isp,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_rect *r, अचिन्हित पूर्णांक which)
अणु
	काष्ठा v4l2_rect *sink_crop, *src_crop;
	काष्ठा v4l2_mbus_framefmt *sink_fmt;

	sink_crop = rkisp1_isp_get_pad_crop(isp, cfg, RKISP1_ISP_PAD_SINK_VIDEO,
					    which);
	sink_fmt = rkisp1_isp_get_pad_fmt(isp, cfg, RKISP1_ISP_PAD_SINK_VIDEO,
					  which);

	sink_crop->left = ALIGN(r->left, 2);
	sink_crop->width = ALIGN(r->width, 2);
	sink_crop->top = r->top;
	sink_crop->height = r->height;
	rkisp1_sd_adjust_crop(sink_crop, sink_fmt);

	*r = *sink_crop;

	/* Propagate to out crop */
	src_crop = rkisp1_isp_get_pad_crop(isp, cfg,
					   RKISP1_ISP_PAD_SOURCE_VIDEO, which);
	rkisp1_isp_set_src_crop(isp, cfg, src_crop, which);
पूर्ण

अटल व्योम rkisp1_isp_set_sink_fmt(काष्ठा rkisp1_isp *isp,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_mbus_framefmt *क्रमmat,
				    अचिन्हित पूर्णांक which)
अणु
	स्थिर काष्ठा rkisp1_isp_mbus_info *mbus_info;
	काष्ठा v4l2_mbus_framefmt *sink_fmt;
	काष्ठा v4l2_rect *sink_crop;

	sink_fmt = rkisp1_isp_get_pad_fmt(isp, cfg, RKISP1_ISP_PAD_SINK_VIDEO,
					  which);
	sink_fmt->code = क्रमmat->code;
	mbus_info = rkisp1_isp_mbus_info_get(sink_fmt->code);
	अगर (!mbus_info || !(mbus_info->direction & RKISP1_ISP_SD_SINK)) अणु
		sink_fmt->code = RKISP1_DEF_SINK_PAD_FMT;
		mbus_info = rkisp1_isp_mbus_info_get(sink_fmt->code);
	पूर्ण
	अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE)
		isp->sink_fmt = mbus_info;

	sink_fmt->width = clamp_t(u32, क्रमmat->width,
				  RKISP1_ISP_MIN_WIDTH,
				  RKISP1_ISP_MAX_WIDTH);
	sink_fmt->height = clamp_t(u32, क्रमmat->height,
				   RKISP1_ISP_MIN_HEIGHT,
				   RKISP1_ISP_MAX_HEIGHT);

	*क्रमmat = *sink_fmt;

	/* Propagate to in crop */
	sink_crop = rkisp1_isp_get_pad_crop(isp, cfg, RKISP1_ISP_PAD_SINK_VIDEO,
					    which);
	rkisp1_isp_set_sink_crop(isp, cfg, sink_crop, which);
पूर्ण

अटल पूर्णांक rkisp1_isp_get_fmt(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा rkisp1_isp *isp = container_of(sd, काष्ठा rkisp1_isp, sd);

	mutex_lock(&isp->ops_lock);
	fmt->क्रमmat = *rkisp1_isp_get_pad_fmt(isp, cfg, fmt->pad, fmt->which);
	mutex_unlock(&isp->ops_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_isp_set_fmt(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा rkisp1_isp *isp = container_of(sd, काष्ठा rkisp1_isp, sd);

	mutex_lock(&isp->ops_lock);
	अगर (fmt->pad == RKISP1_ISP_PAD_SINK_VIDEO)
		rkisp1_isp_set_sink_fmt(isp, cfg, &fmt->क्रमmat, fmt->which);
	अन्यथा अगर (fmt->pad == RKISP1_ISP_PAD_SOURCE_VIDEO)
		rkisp1_isp_set_src_fmt(isp, cfg, &fmt->क्रमmat, fmt->which);
	अन्यथा
		fmt->क्रमmat = *rkisp1_isp_get_pad_fmt(isp, cfg, fmt->pad,
						      fmt->which);

	mutex_unlock(&isp->ops_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_isp_get_selection(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा rkisp1_isp *isp = container_of(sd, काष्ठा rkisp1_isp, sd);
	पूर्णांक ret = 0;

	अगर (sel->pad != RKISP1_ISP_PAD_SOURCE_VIDEO &&
	    sel->pad != RKISP1_ISP_PAD_SINK_VIDEO)
		वापस -EINVAL;

	mutex_lock(&isp->ops_lock);
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		अगर (sel->pad == RKISP1_ISP_PAD_SINK_VIDEO) अणु
			काष्ठा v4l2_mbus_framefmt *fmt;

			fmt = rkisp1_isp_get_pad_fmt(isp, cfg, sel->pad,
						     sel->which);
			sel->r.height = fmt->height;
			sel->r.width = fmt->width;
			sel->r.left = 0;
			sel->r.top = 0;
		पूर्ण अन्यथा अणु
			sel->r = *rkisp1_isp_get_pad_crop(isp, cfg,
						RKISP1_ISP_PAD_SINK_VIDEO,
						sel->which);
		पूर्ण
		अवरोध;
	हाल V4L2_SEL_TGT_CROP:
		sel->r = *rkisp1_isp_get_pad_crop(isp, cfg, sel->pad,
						  sel->which);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&isp->ops_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rkisp1_isp_set_selection(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा rkisp1_device *rkisp1 =
		container_of(sd->v4l2_dev, काष्ठा rkisp1_device, v4l2_dev);
	काष्ठा rkisp1_isp *isp = container_of(sd, काष्ठा rkisp1_isp, sd);
	पूर्णांक ret = 0;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	dev_dbg(rkisp1->dev, "%s: pad: %d sel(%d,%d)/%dx%d\n", __func__,
		sel->pad, sel->r.left, sel->r.top, sel->r.width, sel->r.height);
	mutex_lock(&isp->ops_lock);
	अगर (sel->pad == RKISP1_ISP_PAD_SINK_VIDEO)
		rkisp1_isp_set_sink_crop(isp, cfg, &sel->r, sel->which);
	अन्यथा अगर (sel->pad == RKISP1_ISP_PAD_SOURCE_VIDEO)
		rkisp1_isp_set_src_crop(isp, cfg, &sel->r, sel->which);
	अन्यथा
		ret = -EINVAL;

	mutex_unlock(&isp->ops_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rkisp1_subdev_link_validate(काष्ठा media_link *link)
अणु
	अगर (link->sink->index == RKISP1_ISP_PAD_SINK_PARAMS)
		वापस 0;

	वापस v4l2_subdev_link_validate(link);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops rkisp1_isp_pad_ops = अणु
	.क्रमागत_mbus_code = rkisp1_isp_क्रमागत_mbus_code,
	.क्रमागत_frame_size = rkisp1_isp_क्रमागत_frame_size,
	.get_selection = rkisp1_isp_get_selection,
	.set_selection = rkisp1_isp_set_selection,
	.init_cfg = rkisp1_isp_init_config,
	.get_fmt = rkisp1_isp_get_fmt,
	.set_fmt = rkisp1_isp_set_fmt,
	.link_validate = v4l2_subdev_link_validate_शेष,
पूर्ण;

/* ----------------------------------------------------------------------------
 * Stream operations
 */

अटल पूर्णांक rkisp1_mipi_csi2_start(काष्ठा rkisp1_isp *isp,
				  काष्ठा rkisp1_sensor_async *sensor)
अणु
	काष्ठा rkisp1_device *rkisp1 =
		container_of(isp->sd.v4l2_dev, काष्ठा rkisp1_device, v4l2_dev);
	जोड़ phy_configure_opts opts;
	काष्ठा phy_configure_opts_mipi_dphy *cfg = &opts.mipi_dphy;
	s64 pixel_घड़ी;

	अगर (!sensor->pixel_rate_ctrl) अणु
		dev_warn(rkisp1->dev, "No pixel rate control in sensor subdev\n");
		वापस -EPIPE;
	पूर्ण

	pixel_घड़ी = v4l2_ctrl_g_ctrl_पूर्णांक64(sensor->pixel_rate_ctrl);
	अगर (!pixel_घड़ी) अणु
		dev_err(rkisp1->dev, "Invalid pixel rate value\n");
		वापस -EINVAL;
	पूर्ण

	phy_mipi_dphy_get_शेष_config(pixel_घड़ी, isp->sink_fmt->bus_width,
					 sensor->lanes, cfg);
	phy_set_mode(sensor->dphy, PHY_MODE_MIPI_DPHY);
	phy_configure(sensor->dphy, &opts);
	phy_घातer_on(sensor->dphy);

	वापस 0;
पूर्ण

अटल व्योम rkisp1_mipi_csi2_stop(काष्ठा rkisp1_sensor_async *sensor)
अणु
	phy_घातer_off(sensor->dphy);
पूर्ण

अटल पूर्णांक rkisp1_isp_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा rkisp1_device *rkisp1 =
		container_of(sd->v4l2_dev, काष्ठा rkisp1_device, v4l2_dev);
	काष्ठा rkisp1_isp *isp = &rkisp1->isp;
	काष्ठा v4l2_subdev *sensor_sd;
	पूर्णांक ret = 0;

	अगर (!enable) अणु
		rkisp1_isp_stop(rkisp1);
		rkisp1_mipi_csi2_stop(rkisp1->active_sensor);
		वापस 0;
	पूर्ण

	sensor_sd = rkisp1_get_remote_sensor(sd);
	अगर (!sensor_sd) अणु
		dev_warn(rkisp1->dev, "No link between isp and sensor\n");
		वापस -ENODEV;
	पूर्ण

	rkisp1->active_sensor = container_of(sensor_sd->asd,
					     काष्ठा rkisp1_sensor_async, asd);

	अगर (rkisp1->active_sensor->mbus_type != V4L2_MBUS_CSI2_DPHY)
		वापस -EINVAL;

	rkisp1->isp.frame_sequence = -1;
	mutex_lock(&isp->ops_lock);
	ret = rkisp1_config_cअगर(rkisp1);
	अगर (ret)
		जाओ mutex_unlock;

	ret = rkisp1_mipi_csi2_start(&rkisp1->isp, rkisp1->active_sensor);
	अगर (ret)
		जाओ mutex_unlock;

	rkisp1_isp_start(rkisp1);

mutex_unlock:
	mutex_unlock(&isp->ops_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rkisp1_isp_subs_evt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
			       काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (sub->type != V4L2_EVENT_FRAME_SYNC)
		वापस -EINVAL;

	/* V4L2_EVENT_FRAME_SYNC करोesn't require an id, so zero should be set */
	अगर (sub->id != 0)
		वापस -EINVAL;

	वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा media_entity_operations rkisp1_isp_media_ops = अणु
	.link_validate = rkisp1_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops rkisp1_isp_video_ops = अणु
	.s_stream = rkisp1_isp_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops rkisp1_isp_core_ops = अणु
	.subscribe_event = rkisp1_isp_subs_evt,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops rkisp1_isp_ops = अणु
	.core = &rkisp1_isp_core_ops,
	.video = &rkisp1_isp_video_ops,
	.pad = &rkisp1_isp_pad_ops,
पूर्ण;

पूर्णांक rkisp1_isp_रेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_isp *isp = &rkisp1->isp;
	काष्ठा media_pad *pads = isp->pads;
	काष्ठा v4l2_subdev *sd = &isp->sd;
	पूर्णांक ret;

	v4l2_subdev_init(sd, &rkisp1_isp_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	sd->entity.ops = &rkisp1_isp_media_ops;
	sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	sd->owner = THIS_MODULE;
	strscpy(sd->name, RKISP1_ISP_DEV_NAME, माप(sd->name));

	pads[RKISP1_ISP_PAD_SINK_VIDEO].flags = MEDIA_PAD_FL_SINK |
						MEDIA_PAD_FL_MUST_CONNECT;
	pads[RKISP1_ISP_PAD_SINK_PARAMS].flags = MEDIA_PAD_FL_SINK;
	pads[RKISP1_ISP_PAD_SOURCE_VIDEO].flags = MEDIA_PAD_FL_SOURCE;
	pads[RKISP1_ISP_PAD_SOURCE_STATS].flags = MEDIA_PAD_FL_SOURCE;

	isp->sink_fmt = rkisp1_isp_mbus_info_get(RKISP1_DEF_SINK_PAD_FMT);
	isp->src_fmt = rkisp1_isp_mbus_info_get(RKISP1_DEF_SRC_PAD_FMT);

	mutex_init(&isp->ops_lock);
	ret = media_entity_pads_init(&sd->entity, RKISP1_ISP_PAD_MAX, pads);
	अगर (ret)
		वापस ret;

	ret = v4l2_device_रेजिस्टर_subdev(&rkisp1->v4l2_dev, sd);
	अगर (ret) अणु
		dev_err(rkisp1->dev, "Failed to register isp subdev\n");
		जाओ err_cleanup_media_entity;
	पूर्ण

	rkisp1_isp_init_config(sd, rkisp1->isp.pad_cfg);
	वापस 0;

err_cleanup_media_entity:
	media_entity_cleanup(&sd->entity);

	वापस ret;
पूर्ण

व्योम rkisp1_isp_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा v4l2_subdev *sd = &rkisp1->isp.sd;

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
पूर्ण

/* ----------------------------------------------------------------------------
 * Interrupt handlers
 */

व्योम rkisp1_mipi_isr(काष्ठा rkisp1_device *rkisp1)
अणु
	u32 val, status;

	status = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_MIS);
	अगर (!status)
		वापस;

	rkisp1_ग_लिखो(rkisp1, status, RKISP1_CIF_MIPI_ICR);

	/*
	 * Disable DPHY errctrl पूर्णांकerrupt, because this dphy
	 * erctrl संकेत is निश्चितed until the next changes
	 * of line state. This समय is may be too दीर्घ and cpu
	 * is hold in this पूर्णांकerrupt.
	 */
	अगर (status & RKISP1_CIF_MIPI_ERR_CTRL(0x0f)) अणु
		val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_IMSC);
		rkisp1_ग_लिखो(rkisp1, val & ~RKISP1_CIF_MIPI_ERR_CTRL(0x0f),
			     RKISP1_CIF_MIPI_IMSC);
		rkisp1->isp.is_dphy_errctrl_disabled = true;
	पूर्ण

	/*
	 * Enable DPHY errctrl पूर्णांकerrupt again, अगर mipi have receive
	 * the whole frame without any error.
	 */
	अगर (status == RKISP1_CIF_MIPI_FRAME_END) अणु
		/*
		 * Enable DPHY errctrl पूर्णांकerrupt again, अगर mipi have receive
		 * the whole frame without any error.
		 */
		अगर (rkisp1->isp.is_dphy_errctrl_disabled) अणु
			val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_MIPI_IMSC);
			val |= RKISP1_CIF_MIPI_ERR_CTRL(0x0f);
			rkisp1_ग_लिखो(rkisp1, val, RKISP1_CIF_MIPI_IMSC);
			rkisp1->isp.is_dphy_errctrl_disabled = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		rkisp1->debug.mipi_error++;
	पूर्ण
पूर्ण

अटल व्योम rkisp1_isp_queue_event_sof(काष्ठा rkisp1_isp *isp)
अणु
	काष्ठा v4l2_event event = अणु
		.type = V4L2_EVENT_FRAME_SYNC,
	पूर्ण;
	event.u.frame_sync.frame_sequence = isp->frame_sequence;

	v4l2_event_queue(isp->sd.devnode, &event);
पूर्ण

व्योम rkisp1_isp_isr(काष्ठा rkisp1_device *rkisp1)
अणु
	u32 status, isp_err;

	status = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_MIS);
	अगर (!status)
		वापस;

	rkisp1_ग_लिखो(rkisp1, status, RKISP1_CIF_ISP_ICR);

	/* Vertical sync संकेत, starting generating new frame */
	अगर (status & RKISP1_CIF_ISP_V_START) अणु
		rkisp1->isp.frame_sequence++;
		rkisp1_isp_queue_event_sof(&rkisp1->isp);
		अगर (status & RKISP1_CIF_ISP_FRAME) अणु
			WARN_ONCE(1, "irq delay is too long, buffers might not be in sync\n");
			rkisp1->debug.irq_delay++;
		पूर्ण
	पूर्ण
	अगर (status & RKISP1_CIF_ISP_PIC_SIZE_ERROR) अणु
		/* Clear pic_size_error */
		isp_err = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_ERR);
		अगर (isp_err & RKISP1_CIF_ISP_ERR_INFORM_SIZE)
			rkisp1->debug.inक्रमm_size_error++;
		अगर (isp_err & RKISP1_CIF_ISP_ERR_IS_SIZE)
			rkisp1->debug.img_stabilization_size_error++;
		अगर (isp_err & RKISP1_CIF_ISP_ERR_OUTFORM_SIZE)
			rkisp1->debug.outक्रमm_size_error++;
		rkisp1_ग_लिखो(rkisp1, isp_err, RKISP1_CIF_ISP_ERR_CLR);
	पूर्ण अन्यथा अगर (status & RKISP1_CIF_ISP_DATA_LOSS) अणु
		/* keep track of data_loss in debugfs */
		rkisp1->debug.data_loss++;
	पूर्ण

	अगर (status & RKISP1_CIF_ISP_FRAME) अणु
		u32 isp_ris;

		/* New frame from the sensor received */
		isp_ris = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_RIS);
		अगर (isp_ris & RKISP1_STATS_MEAS_MASK)
			rkisp1_stats_isr(&rkisp1->stats, isp_ris);
		/*
		 * Then update changed configs. Some of them involve
		 * lot of रेजिस्टर ग_लिखोs. Do those only one per frame.
		 * Do the updates in the order of the processing flow.
		 */
		rkisp1_params_isr(rkisp1);
	पूर्ण
पूर्ण

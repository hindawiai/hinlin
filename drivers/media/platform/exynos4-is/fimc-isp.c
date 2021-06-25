<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Sylwester Nawrocki <s.nawrocki@samsung.com>
 *          Younghwan Joo <yhwan.joo@samsung.com>
 */
#घोषणा pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-device.h>

#समावेश "media-dev.h"
#समावेश "fimc-isp-video.h"
#समावेश "fimc-is-command.h"
#समावेश "fimc-is-param.h"
#समावेश "fimc-is-regs.h"
#समावेश "fimc-is.h"

पूर्णांक fimc_isp_debug;
module_param_named(debug_isp, fimc_isp_debug, पूर्णांक, S_IRUGO | S_IWUSR);

अटल स्थिर काष्ठा fimc_fmt fimc_isp_क्रमmats[FIMC_ISP_NUM_FORMATS] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG8,
		.depth		= अणु 8 पूर्ण,
		.color		= FIMC_FMT_RAW8,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG8_1X8,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG10,
		.depth		= अणु 10 पूर्ण,
		.color		= FIMC_FMT_RAW10,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG10_1X10,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_SGRBG12,
		.depth		= अणु 12 पूर्ण,
		.color		= FIMC_FMT_RAW12,
		.memplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_SGRBG12_1X12,
	पूर्ण,
पूर्ण;

/**
 * fimc_isp_find_क्रमmat - lookup color क्रमmat by fourcc or media bus code
 * @pixelक्रमmat: fourcc to match, ignored अगर null
 * @mbus_code: media bus code to match, ignored अगर null
 * @index: index to the fimc_isp_क्रमmats array, ignored अगर negative
 */
स्थिर काष्ठा fimc_fmt *fimc_isp_find_क्रमmat(स्थिर u32 *pixelक्रमmat,
					स्थिर u32 *mbus_code, पूर्णांक index)
अणु
	स्थिर काष्ठा fimc_fmt *fmt, *def_fmt = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक id = 0;

	अगर (index >= (पूर्णांक)ARRAY_SIZE(fimc_isp_क्रमmats))
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(fimc_isp_क्रमmats); ++i) अणु
		fmt = &fimc_isp_क्रमmats[i];
		अगर (pixelक्रमmat && fmt->fourcc == *pixelक्रमmat)
			वापस fmt;
		अगर (mbus_code && fmt->mbus_code == *mbus_code)
			वापस fmt;
		अगर (index == id)
			def_fmt = fmt;
		id++;
	पूर्ण
	वापस def_fmt;
पूर्ण

व्योम fimc_isp_irq_handler(काष्ठा fimc_is *is)
अणु
	is->i2h_cmd.args[0] = mcuctl_पढ़ो(is, MCUCTL_REG_ISSR(20));
	is->i2h_cmd.args[1] = mcuctl_पढ़ो(is, MCUCTL_REG_ISSR(21));

	fimc_is_fw_clear_irq1(is, FIMC_IS_INT_FRAME_DONE_ISP);
	fimc_isp_video_irq_handler(is);

	wake_up(&is->irq_queue);
पूर्ण

/* Capture subdev media entity operations */
अटल पूर्णांक fimc_is_link_setup(काष्ठा media_entity *entity,
				स्थिर काष्ठा media_pad *local,
				स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations fimc_is_subdev_media_ops = अणु
	.link_setup = fimc_is_link_setup,
पूर्ण;

अटल पूर्णांक fimc_is_subdev_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	स्थिर काष्ठा fimc_fmt *fmt;

	fmt = fimc_isp_find_क्रमmat(शून्य, शून्य, code->index);
	अगर (!fmt)
		वापस -EINVAL;
	code->code = fmt->mbus_code;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_isp_subdev_get_fmt(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा fimc_isp *isp = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*mf = *v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		वापस 0;
	पूर्ण

	mf->colorspace = V4L2_COLORSPACE_SRGB;

	mutex_lock(&isp->subdev_lock);

	अगर (fmt->pad == FIMC_ISP_SD_PAD_SINK) अणु
		/* ISP OTF input image क्रमmat */
		*mf = isp->sink_fmt;
	पूर्ण अन्यथा अणु
		/* ISP OTF output image क्रमmat */
		*mf = isp->src_fmt;

		अगर (fmt->pad == FIMC_ISP_SD_PAD_SRC_FIFO) अणु
			mf->colorspace = V4L2_COLORSPACE_JPEG;
			mf->code = MEDIA_BUS_FMT_YUV10_1X30;
		पूर्ण
	पूर्ण

	mutex_unlock(&isp->subdev_lock);

	isp_dbg(1, sd, "%s: pad%d: fmt: 0x%x, %dx%d\n", __func__,
		fmt->pad, mf->code, mf->width, mf->height);

	वापस 0;
पूर्ण

अटल व्योम __isp_subdev_try_क्रमmat(काष्ठा fimc_isp *isp,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	mf->colorspace = V4L2_COLORSPACE_SRGB;

	अगर (fmt->pad == FIMC_ISP_SD_PAD_SINK) अणु
		v4l_bound_align_image(&mf->width, FIMC_ISP_SINK_WIDTH_MIN,
				FIMC_ISP_SINK_WIDTH_MAX, 0,
				&mf->height, FIMC_ISP_SINK_HEIGHT_MIN,
				FIMC_ISP_SINK_HEIGHT_MAX, 0, 0);
		mf->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	पूर्ण अन्यथा अणु
		अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
			क्रमmat = v4l2_subdev_get_try_क्रमmat(&isp->subdev, cfg,
						FIMC_ISP_SD_PAD_SINK);
		अन्यथा
			क्रमmat = &isp->sink_fmt;

		/* Allow changing क्रमmat only on sink pad */
		mf->width = क्रमmat->width - FIMC_ISP_CAC_MARGIN_WIDTH;
		mf->height = क्रमmat->height - FIMC_ISP_CAC_MARGIN_HEIGHT;

		अगर (fmt->pad == FIMC_ISP_SD_PAD_SRC_FIFO) अणु
			mf->code = MEDIA_BUS_FMT_YUV10_1X30;
			mf->colorspace = V4L2_COLORSPACE_JPEG;
		पूर्ण अन्यथा अणु
			mf->code = क्रमmat->code;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक fimc_isp_subdev_set_fmt(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा fimc_isp *isp = v4l2_get_subdevdata(sd);
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	पूर्णांक ret = 0;

	isp_dbg(1, sd, "%s: pad%d: code: 0x%x, %dx%d\n",
		 __func__, fmt->pad, mf->code, mf->width, mf->height);

	mutex_lock(&isp->subdev_lock);
	__isp_subdev_try_क्रमmat(isp, cfg, fmt);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*mf = fmt->क्रमmat;

		/* Propagate क्रमmat to the source pads */
		अगर (fmt->pad == FIMC_ISP_SD_PAD_SINK) अणु
			काष्ठा v4l2_subdev_क्रमmat क्रमmat = *fmt;
			अचिन्हित पूर्णांक pad;

			क्रम (pad = FIMC_ISP_SD_PAD_SRC_FIFO;
					pad < FIMC_ISP_SD_PADS_NUM; pad++) अणु
				क्रमmat.pad = pad;
				__isp_subdev_try_क्रमmat(isp, cfg, &क्रमmat);
				mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, pad);
				*mf = क्रमmat.क्रमmat;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sd->entity.stream_count == 0) अणु
			अगर (fmt->pad == FIMC_ISP_SD_PAD_SINK) अणु
				काष्ठा v4l2_subdev_क्रमmat क्रमmat = *fmt;

				isp->sink_fmt = *mf;

				क्रमmat.pad = FIMC_ISP_SD_PAD_SRC_DMA;
				__isp_subdev_try_क्रमmat(isp, cfg, &क्रमmat);

				isp->src_fmt = क्रमmat.क्रमmat;
				__is_set_frame_size(is, &isp->src_fmt);
			पूर्ण अन्यथा अणु
				isp->src_fmt = *mf;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = -EBUSY;
		पूर्ण
	पूर्ण

	mutex_unlock(&isp->subdev_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_isp_subdev_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा fimc_isp *isp = v4l2_get_subdevdata(sd);
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);
	पूर्णांक ret;

	isp_dbg(1, sd, "%s: on: %d\n", __func__, on);

	अगर (!test_bit(IS_ST_INIT_DONE, &is->state))
		वापस -EBUSY;

	fimc_is_mem_barrier();

	अगर (on) अणु
		अगर (__get_pending_param_count(is)) अणु
			ret = fimc_is_itf_s_param(is, true);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		isp_dbg(1, sd, "changing mode to %d\n", is->config_index);

		ret = fimc_is_itf_mode_change(is);
		अगर (ret)
			वापस -EINVAL;

		clear_bit(IS_ST_STREAM_ON, &is->state);
		fimc_is_hw_stream_on(is);
		ret = fimc_is_रुको_event(is, IS_ST_STREAM_ON, 1,
					 FIMC_IS_CONFIG_TIMEOUT);
		अगर (ret < 0) अणु
			v4l2_err(sd, "stream on timeout\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_bit(IS_ST_STREAM_OFF, &is->state);
		fimc_is_hw_stream_off(is);
		ret = fimc_is_रुको_event(is, IS_ST_STREAM_OFF, 1,
					 FIMC_IS_CONFIG_TIMEOUT);
		अगर (ret < 0) अणु
			v4l2_err(sd, "stream off timeout\n");
			वापस ret;
		पूर्ण
		is->setfile.sub_index = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_isp_subdev_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा fimc_isp *isp = v4l2_get_subdevdata(sd);
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);
	पूर्णांक ret = 0;

	pr_debug("on: %d\n", on);

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&is->pdev->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put(&is->pdev->dev);
			वापस ret;
		पूर्ण
		set_bit(IS_ST_PWR_ON, &is->state);

		ret = fimc_is_start_firmware(is);
		अगर (ret < 0) अणु
			v4l2_err(sd, "firmware booting failed\n");
			pm_runसमय_put(&is->pdev->dev);
			वापस ret;
		पूर्ण
		set_bit(IS_ST_PWR_SUBIP_ON, &is->state);

		ret = fimc_is_hw_initialize(is);
	पूर्ण अन्यथा अणु
		/* Close sensor */
		अगर (!test_bit(IS_ST_PWR_ON, &is->state)) अणु
			fimc_is_hw_बंद_sensor(is, 0);

			ret = fimc_is_रुको_event(is, IS_ST_OPEN_SENSOR, 0,
						 FIMC_IS_CONFIG_TIMEOUT);
			अगर (ret < 0) अणु
				v4l2_err(sd, "sensor close timeout\n");
				वापस ret;
			पूर्ण
		पूर्ण

		/* SUB IP घातer off */
		अगर (test_bit(IS_ST_PWR_SUBIP_ON, &is->state)) अणु
			fimc_is_hw_subip_घातer_off(is);
			ret = fimc_is_रुको_event(is, IS_ST_PWR_SUBIP_ON, 0,
						 FIMC_IS_CONFIG_TIMEOUT);
			अगर (ret < 0) अणु
				v4l2_err(sd, "sub-IP power off timeout\n");
				वापस ret;
			पूर्ण
		पूर्ण

		fimc_is_cpu_set_घातer(is, 0);
		pm_runसमय_put_sync(&is->pdev->dev);

		clear_bit(IS_ST_PWR_ON, &is->state);
		clear_bit(IS_ST_INIT_DONE, &is->state);
		is->state = 0;
		is->config[is->config_index].p_region_index[0] = 0;
		is->config[is->config_index].p_region_index[1] = 0;
		set_bit(IS_ST_IDLE, &is->state);
		wmb();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fimc_isp_subdev_खोलो(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_mbus_framefmt fmt = अणु
		.colorspace = V4L2_COLORSPACE_SRGB,
		.code = fimc_isp_क्रमmats[0].mbus_code,
		.width = DEFAULT_PREVIEW_STILL_WIDTH + FIMC_ISP_CAC_MARGIN_WIDTH,
		.height = DEFAULT_PREVIEW_STILL_HEIGHT + FIMC_ISP_CAC_MARGIN_HEIGHT,
		.field = V4L2_FIELD_NONE,
	पूर्ण;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, FIMC_ISP_SD_PAD_SINK);
	*क्रमmat = fmt;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, FIMC_ISP_SD_PAD_SRC_FIFO);
	fmt.width = DEFAULT_PREVIEW_STILL_WIDTH;
	fmt.height = DEFAULT_PREVIEW_STILL_HEIGHT;
	*क्रमmat = fmt;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, FIMC_ISP_SD_PAD_SRC_DMA);
	*क्रमmat = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_isp_subdev_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा fimc_isp *isp = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	/* Use pipeline object allocated by the media device. */
	isp->video_capture.ve.pipe = v4l2_get_subdev_hostdata(sd);

	ret = fimc_isp_video_device_रेजिस्टर(isp, sd->v4l2_dev,
			V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	अगर (ret < 0)
		isp->video_capture.ve.pipe = शून्य;

	वापस ret;
पूर्ण

अटल व्योम fimc_isp_subdev_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा fimc_isp *isp = v4l2_get_subdevdata(sd);

	fimc_isp_video_device_unरेजिस्टर(isp,
			V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops fimc_is_subdev_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = fimc_isp_subdev_रेजिस्टरed,
	.unरेजिस्टरed = fimc_isp_subdev_unरेजिस्टरed,
	.खोलो = fimc_isp_subdev_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops fimc_is_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = fimc_is_subdev_क्रमागत_mbus_code,
	.get_fmt = fimc_isp_subdev_get_fmt,
	.set_fmt = fimc_isp_subdev_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops fimc_is_subdev_video_ops = अणु
	.s_stream = fimc_isp_subdev_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops fimc_is_core_ops = अणु
	.s_घातer = fimc_isp_subdev_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops fimc_is_subdev_ops = अणु
	.core = &fimc_is_core_ops,
	.video = &fimc_is_subdev_video_ops,
	.pad = &fimc_is_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक __ctrl_set_white_balance(काष्ठा fimc_is *is, पूर्णांक value)
अणु
	चयन (value) अणु
	हाल V4L2_WHITE_BALANCE_AUTO:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_AUTO, 0);
		अवरोध;
	हाल V4L2_WHITE_BALANCE_DAYLIGHT:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_ILLUMINATION,
					ISP_AWB_ILLUMINATION_DAYLIGHT);
		अवरोध;
	हाल V4L2_WHITE_BALANCE_CLOUDY:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_ILLUMINATION,
					ISP_AWB_ILLUMINATION_CLOUDY);
		अवरोध;
	हाल V4L2_WHITE_BALANCE_INCANDESCENT:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_ILLUMINATION,
					ISP_AWB_ILLUMINATION_TUNGSTEN);
		अवरोध;
	हाल V4L2_WHITE_BALANCE_FLUORESCENT:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_ILLUMINATION,
					ISP_AWB_ILLUMINATION_FLUORESCENT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ctrl_set_aewb_lock(काष्ठा fimc_is *is,
				      काष्ठा v4l2_ctrl *ctrl)
अणु
	bool awb_lock = ctrl->val & V4L2_LOCK_WHITE_BALANCE;
	bool ae_lock = ctrl->val & V4L2_LOCK_EXPOSURE;
	काष्ठा isp_param *isp = &is->is_p_region->parameter.isp;
	पूर्णांक cmd, ret;

	cmd = ae_lock ? ISP_AA_COMMAND_STOP : ISP_AA_COMMAND_START;
	isp->aa.cmd = cmd;
	isp->aa.target = ISP_AA_TARGET_AE;
	fimc_is_set_param_bit(is, PARAM_ISP_AA);
	is->af.ae_lock_state = ae_lock;
	wmb();

	ret = fimc_is_itf_s_param(is, false);
	अगर (ret < 0)
		वापस ret;

	cmd = awb_lock ? ISP_AA_COMMAND_STOP : ISP_AA_COMMAND_START;
	isp->aa.cmd = cmd;
	isp->aa.target = ISP_AA_TARGET_AE;
	fimc_is_set_param_bit(is, PARAM_ISP_AA);
	is->af.awb_lock_state = awb_lock;
	wmb();

	वापस fimc_is_itf_s_param(is, false);
पूर्ण

/* Supported manual ISO values */
अटल स्थिर s64 iso_qmenu[] = अणु
	50, 100, 200, 400, 800,
पूर्ण;

अटल पूर्णांक __ctrl_set_iso(काष्ठा fimc_is *is, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक idx, iso;

	अगर (value == V4L2_ISO_SENSITIVITY_AUTO) अणु
		__is_set_isp_iso(is, ISP_ISO_COMMAND_AUTO, 0);
		वापस 0;
	पूर्ण
	idx = is->isp.ctrls.iso->val;
	अगर (idx >= ARRAY_SIZE(iso_qmenu))
		वापस -EINVAL;

	iso = iso_qmenu[idx];
	__is_set_isp_iso(is, ISP_ISO_COMMAND_MANUAL, iso);
	वापस 0;
पूर्ण

अटल पूर्णांक __ctrl_set_metering(काष्ठा fimc_is *is, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक val;

	चयन (value) अणु
	हाल V4L2_EXPOSURE_METERING_AVERAGE:
		val = ISP_METERING_COMMAND_AVERAGE;
		अवरोध;
	हाल V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
		val = ISP_METERING_COMMAND_CENTER;
		अवरोध;
	हाल V4L2_EXPOSURE_METERING_SPOT:
		val = ISP_METERING_COMMAND_SPOT;
		अवरोध;
	हाल V4L2_EXPOSURE_METERING_MATRIX:
		val = ISP_METERING_COMMAND_MATRIX;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	__is_set_isp_metering(is, IS_METERING_CONFIG_CMD, val);
	वापस 0;
पूर्ण

अटल पूर्णांक __ctrl_set_afc(काष्ठा fimc_is *is, पूर्णांक value)
अणु
	चयन (value) अणु
	हाल V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
		__is_set_isp_afc(is, ISP_AFC_COMMAND_DISABLE, 0);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
		__is_set_isp_afc(is, ISP_AFC_COMMAND_MANUAL, 50);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
		__is_set_isp_afc(is, ISP_AFC_COMMAND_MANUAL, 60);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY_AUTO:
		__is_set_isp_afc(is, ISP_AFC_COMMAND_AUTO, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ctrl_set_image_effect(काष्ठा fimc_is *is, पूर्णांक value)
अणु
	अटल स्थिर u8 effects[][2] = अणु
		अणु V4L2_COLORFX_NONE,	 ISP_IMAGE_EFFECT_DISABLE पूर्ण,
		अणु V4L2_COLORFX_BW,	 ISP_IMAGE_EFFECT_MONOCHROME पूर्ण,
		अणु V4L2_COLORFX_SEPIA,	 ISP_IMAGE_EFFECT_SEPIA पूर्ण,
		अणु V4L2_COLORFX_NEGATIVE, ISP_IMAGE_EFFECT_NEGATIVE_MONO पूर्ण,
		अणु 16 /* TODO */,	 ISP_IMAGE_EFFECT_NEGATIVE_COLOR पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(effects); i++) अणु
		अगर (effects[i][0] != value)
			जारी;

		__is_set_isp_effect(is, effects[i][1]);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fimc_is_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fimc_isp *isp = ctrl_to_fimc_isp(ctrl);
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);
	bool set_param = true;
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_CONTRAST:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_CONTRAST,
				    ctrl->val);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_SATURATION,
				    ctrl->val);
		अवरोध;

	हाल V4L2_CID_SHARPNESS:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_SHARPNESS,
				    ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE_ABSOLUTE:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_EXPOSURE,
				    ctrl->val);
		अवरोध;

	हाल V4L2_CID_BRIGHTNESS:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_BRIGHTNESS,
				    ctrl->val);
		अवरोध;

	हाल V4L2_CID_HUE:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_HUE,
				    ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE_METERING:
		ret = __ctrl_set_metering(is, ctrl->val);
		अवरोध;

	हाल V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		ret = __ctrl_set_white_balance(is, ctrl->val);
		अवरोध;

	हाल V4L2_CID_3A_LOCK:
		ret = __ctrl_set_aewb_lock(is, ctrl);
		set_param = false;
		अवरोध;

	हाल V4L2_CID_ISO_SENSITIVITY_AUTO:
		ret = __ctrl_set_iso(is, ctrl->val);
		अवरोध;

	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		ret = __ctrl_set_afc(is, ctrl->val);
		अवरोध;

	हाल V4L2_CID_COLORFX:
		__ctrl_set_image_effect(is, ctrl->val);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret < 0) अणु
		v4l2_err(&isp->subdev, "Failed to set control: %s (%d)\n",
						ctrl->name, ctrl->val);
		वापस ret;
	पूर्ण

	अगर (set_param && test_bit(IS_ST_STREAM_ON, &is->state))
		वापस fimc_is_itf_s_param(is, true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops fimc_isp_ctrl_ops = अणु
	.s_ctrl	= fimc_is_s_ctrl,
पूर्ण;

अटल व्योम __isp_subdev_set_शेष_क्रमmat(काष्ठा fimc_isp *isp)
अणु
	काष्ठा fimc_is *is = fimc_isp_to_is(isp);

	isp->sink_fmt.width = DEFAULT_PREVIEW_STILL_WIDTH +
				FIMC_ISP_CAC_MARGIN_WIDTH;
	isp->sink_fmt.height = DEFAULT_PREVIEW_STILL_HEIGHT +
				FIMC_ISP_CAC_MARGIN_HEIGHT;
	isp->sink_fmt.code = MEDIA_BUS_FMT_SGRBG10_1X10;

	isp->src_fmt.width = DEFAULT_PREVIEW_STILL_WIDTH;
	isp->src_fmt.height = DEFAULT_PREVIEW_STILL_HEIGHT;
	isp->src_fmt.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	__is_set_frame_size(is, &isp->src_fmt);
पूर्ण

पूर्णांक fimc_isp_subdev_create(काष्ठा fimc_isp *isp)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &fimc_isp_ctrl_ops;
	काष्ठा v4l2_ctrl_handler *handler = &isp->ctrls.handler;
	काष्ठा v4l2_subdev *sd = &isp->subdev;
	काष्ठा fimc_isp_ctrls *ctrls = &isp->ctrls;
	पूर्णांक ret;

	mutex_init(&isp->subdev_lock);

	v4l2_subdev_init(sd, &fimc_is_subdev_ops);

	sd->owner = THIS_MODULE;
	sd->grp_id = GRP_ID_FIMC_IS;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	snम_लिखो(sd->name, माप(sd->name), "FIMC-IS-ISP");

	sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	isp->subdev_pads[FIMC_ISP_SD_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	isp->subdev_pads[FIMC_ISP_SD_PAD_SRC_FIFO].flags = MEDIA_PAD_FL_SOURCE;
	isp->subdev_pads[FIMC_ISP_SD_PAD_SRC_DMA].flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&sd->entity, FIMC_ISP_SD_PADS_NUM,
				isp->subdev_pads);
	अगर (ret)
		वापस ret;

	v4l2_ctrl_handler_init(handler, 20);

	ctrls->saturation = v4l2_ctrl_new_std(handler, ops, V4L2_CID_SATURATION,
						-2, 2, 1, 0);
	ctrls->brightness = v4l2_ctrl_new_std(handler, ops, V4L2_CID_BRIGHTNESS,
						-4, 4, 1, 0);
	ctrls->contrast = v4l2_ctrl_new_std(handler, ops, V4L2_CID_CONTRAST,
						-2, 2, 1, 0);
	ctrls->sharpness = v4l2_ctrl_new_std(handler, ops, V4L2_CID_SHARPNESS,
						-2, 2, 1, 0);
	ctrls->hue = v4l2_ctrl_new_std(handler, ops, V4L2_CID_HUE,
						-2, 2, 1, 0);

	ctrls->स्वतः_wb = v4l2_ctrl_new_std_menu(handler, ops,
					V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE,
					8, ~0x14e, V4L2_WHITE_BALANCE_AUTO);

	ctrls->exposure = v4l2_ctrl_new_std(handler, ops,
					V4L2_CID_EXPOSURE_ABSOLUTE,
					-4, 4, 1, 0);

	ctrls->exp_metering = v4l2_ctrl_new_std_menu(handler, ops,
					V4L2_CID_EXPOSURE_METERING, 3,
					~0xf, V4L2_EXPOSURE_METERING_AVERAGE);

	v4l2_ctrl_new_std_menu(handler, ops, V4L2_CID_POWER_LINE_FREQUENCY,
					V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
					V4L2_CID_POWER_LINE_FREQUENCY_AUTO);
	/* ISO sensitivity */
	ctrls->स्वतः_iso = v4l2_ctrl_new_std_menu(handler, ops,
			V4L2_CID_ISO_SENSITIVITY_AUTO, 1, 0,
			V4L2_ISO_SENSITIVITY_AUTO);

	ctrls->iso = v4l2_ctrl_new_पूर्णांक_menu(handler, ops,
			V4L2_CID_ISO_SENSITIVITY, ARRAY_SIZE(iso_qmenu) - 1,
			ARRAY_SIZE(iso_qmenu)/2 - 1, iso_qmenu);

	ctrls->aewb_lock = v4l2_ctrl_new_std(handler, ops,
					V4L2_CID_3A_LOCK, 0, 0x3, 0, 0);

	/* TODO: Add support क्रम NEGATIVE_COLOR option */
	ctrls->colorfx = v4l2_ctrl_new_std_menu(handler, ops, V4L2_CID_COLORFX,
			V4L2_COLORFX_SET_CBCR + 1, ~0x1000f, V4L2_COLORFX_NONE);

	अगर (handler->error) अणु
		media_entity_cleanup(&sd->entity);
		वापस handler->error;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(2, &ctrls->स्वतः_iso,
			V4L2_ISO_SENSITIVITY_MANUAL, false);

	sd->ctrl_handler = handler;
	sd->पूर्णांकernal_ops = &fimc_is_subdev_पूर्णांकernal_ops;
	sd->entity.ops = &fimc_is_subdev_media_ops;
	v4l2_set_subdevdata(sd, isp);

	__isp_subdev_set_शेष_क्रमmat(isp);

	वापस 0;
पूर्ण

व्योम fimc_isp_subdev_destroy(काष्ठा fimc_isp *isp)
अणु
	काष्ठा v4l2_subdev *sd = &isp->subdev;

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(&isp->ctrls.handler);
	v4l2_set_subdevdata(sd, शून्य);
पूर्ण

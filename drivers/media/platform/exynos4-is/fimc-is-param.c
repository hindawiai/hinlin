<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Younghwan Joo <yhwan.joo@samsung.com>
 *          Sylwester Nawrocki <s.nawrocki@samsung.com>
 */
#घोषणा pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "fimc-is.h"
#समावेश "fimc-is-command.h"
#समावेश "fimc-is-errno.h"
#समावेश "fimc-is-param.h"
#समावेश "fimc-is-regs.h"
#समावेश "fimc-is-sensor.h"

अटल व्योम __hw_param_copy(व्योम *dst, व्योम *src)
अणु
	स_नकल(dst, src, FIMC_IS_PARAM_MAX_SIZE);
पूर्ण

अटल व्योम __fimc_is_hw_update_param_global_shoपंचांगode(काष्ठा fimc_is *is)
अणु
	काष्ठा param_global_shoपंचांगode *dst, *src;

	dst = &is->is_p_region->parameter.global.shoपंचांगode;
	src = &is->config[is->config_index].global.shoपंचांगode;
	__hw_param_copy(dst, src);
पूर्ण

अटल व्योम __fimc_is_hw_update_param_sensor_framerate(काष्ठा fimc_is *is)
अणु
	काष्ठा param_sensor_framerate *dst, *src;

	dst = &is->is_p_region->parameter.sensor.frame_rate;
	src = &is->config[is->config_index].sensor.frame_rate;
	__hw_param_copy(dst, src);
पूर्ण

पूर्णांक __fimc_is_hw_update_param(काष्ठा fimc_is *is, u32 offset)
अणु
	काष्ठा is_param_region *par = &is->is_p_region->parameter;
	काष्ठा chain_config *cfg = &is->config[is->config_index];

	चयन (offset) अणु
	हाल PARAM_ISP_CONTROL:
		__hw_param_copy(&par->isp.control, &cfg->isp.control);
		अवरोध;

	हाल PARAM_ISP_OTF_INPUT:
		__hw_param_copy(&par->isp.otf_input, &cfg->isp.otf_input);
		अवरोध;

	हाल PARAM_ISP_DMA1_INPUT:
		__hw_param_copy(&par->isp.dma1_input, &cfg->isp.dma1_input);
		अवरोध;

	हाल PARAM_ISP_DMA2_INPUT:
		__hw_param_copy(&par->isp.dma2_input, &cfg->isp.dma2_input);
		अवरोध;

	हाल PARAM_ISP_AA:
		__hw_param_copy(&par->isp.aa, &cfg->isp.aa);
		अवरोध;

	हाल PARAM_ISP_FLASH:
		__hw_param_copy(&par->isp.flash, &cfg->isp.flash);
		अवरोध;

	हाल PARAM_ISP_AWB:
		__hw_param_copy(&par->isp.awb, &cfg->isp.awb);
		अवरोध;

	हाल PARAM_ISP_IMAGE_EFFECT:
		__hw_param_copy(&par->isp.effect, &cfg->isp.effect);
		अवरोध;

	हाल PARAM_ISP_ISO:
		__hw_param_copy(&par->isp.iso, &cfg->isp.iso);
		अवरोध;

	हाल PARAM_ISP_ADJUST:
		__hw_param_copy(&par->isp.adjust, &cfg->isp.adjust);
		अवरोध;

	हाल PARAM_ISP_METERING:
		__hw_param_copy(&par->isp.metering, &cfg->isp.metering);
		अवरोध;

	हाल PARAM_ISP_AFC:
		__hw_param_copy(&par->isp.afc, &cfg->isp.afc);
		अवरोध;

	हाल PARAM_ISP_OTF_OUTPUT:
		__hw_param_copy(&par->isp.otf_output, &cfg->isp.otf_output);
		अवरोध;

	हाल PARAM_ISP_DMA1_OUTPUT:
		__hw_param_copy(&par->isp.dma1_output, &cfg->isp.dma1_output);
		अवरोध;

	हाल PARAM_ISP_DMA2_OUTPUT:
		__hw_param_copy(&par->isp.dma2_output, &cfg->isp.dma2_output);
		अवरोध;

	हाल PARAM_DRC_CONTROL:
		__hw_param_copy(&par->drc.control, &cfg->drc.control);
		अवरोध;

	हाल PARAM_DRC_OTF_INPUT:
		__hw_param_copy(&par->drc.otf_input, &cfg->drc.otf_input);
		अवरोध;

	हाल PARAM_DRC_DMA_INPUT:
		__hw_param_copy(&par->drc.dma_input, &cfg->drc.dma_input);
		अवरोध;

	हाल PARAM_DRC_OTF_OUTPUT:
		__hw_param_copy(&par->drc.otf_output, &cfg->drc.otf_output);
		अवरोध;

	हाल PARAM_FD_CONTROL:
		__hw_param_copy(&par->fd.control, &cfg->fd.control);
		अवरोध;

	हाल PARAM_FD_OTF_INPUT:
		__hw_param_copy(&par->fd.otf_input, &cfg->fd.otf_input);
		अवरोध;

	हाल PARAM_FD_DMA_INPUT:
		__hw_param_copy(&par->fd.dma_input, &cfg->fd.dma_input);
		अवरोध;

	हाल PARAM_FD_CONFIG:
		__hw_param_copy(&par->fd.config, &cfg->fd.config);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक __get_pending_param_count(काष्ठा fimc_is *is)
अणु
	काष्ठा chain_config *config = &is->config[is->config_index];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count;

	spin_lock_irqsave(&is->slock, flags);
	count = hweight32(config->p_region_index[0]);
	count += hweight32(config->p_region_index[1]);
	spin_unlock_irqrestore(&is->slock, flags);

	वापस count;
पूर्ण

पूर्णांक __is_hw_update_params(काष्ठा fimc_is *is)
अणु
	अचिन्हित दीर्घ *p_index;
	पूर्णांक i, id, ret = 0;

	id = is->config_index;
	p_index = &is->config[id].p_region_index[0];

	अगर (test_bit(PARAM_GLOBAL_SHOTMODE, p_index))
		__fimc_is_hw_update_param_global_shoपंचांगode(is);

	अगर (test_bit(PARAM_SENSOR_FRAME_RATE, p_index))
		__fimc_is_hw_update_param_sensor_framerate(is);

	क्रम (i = PARAM_ISP_CONTROL; i < PARAM_DRC_CONTROL; i++) अणु
		अगर (test_bit(i, p_index))
			ret = __fimc_is_hw_update_param(is, i);
	पूर्ण

	क्रम (i = PARAM_DRC_CONTROL; i < PARAM_SCALERC_CONTROL; i++) अणु
		अगर (test_bit(i, p_index))
			ret = __fimc_is_hw_update_param(is, i);
	पूर्ण

	क्रम (i = PARAM_FD_CONTROL; i <= PARAM_FD_CONFIG; i++) अणु
		अगर (test_bit(i, p_index))
			ret = __fimc_is_hw_update_param(is, i);
	पूर्ण

	वापस ret;
पूर्ण

व्योम __is_get_frame_size(काष्ठा fimc_is *is, काष्ठा v4l2_mbus_framefmt *mf)
अणु
	काष्ठा isp_param *isp;

	isp = &is->config[is->config_index].isp;
	mf->width = isp->otf_input.width;
	mf->height = isp->otf_input.height;
पूर्ण

व्योम __is_set_frame_size(काष्ठा fimc_is *is, काष्ठा v4l2_mbus_framefmt *mf)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा isp_param *isp;
	काष्ठा drc_param *drc;
	काष्ठा fd_param *fd;

	isp = &is->config[index].isp;
	drc = &is->config[index].drc;
	fd = &is->config[index].fd;

	/* Update isp size info (OTF only) */
	isp->otf_input.width = mf->width;
	isp->otf_input.height = mf->height;
	isp->otf_output.width = mf->width;
	isp->otf_output.height = mf->height;
	/* Update drc size info (OTF only) */
	drc->otf_input.width = mf->width;
	drc->otf_input.height = mf->height;
	drc->otf_output.width = mf->width;
	drc->otf_output.height = mf->height;
	/* Update fd size info (OTF only) */
	fd->otf_input.width = mf->width;
	fd->otf_input.height = mf->height;

	अगर (test_bit(PARAM_ISP_OTF_INPUT,
		      &is->config[index].p_region_index[0]))
		वापस;

	/* Update field */
	fimc_is_set_param_bit(is, PARAM_ISP_OTF_INPUT);
	fimc_is_set_param_bit(is, PARAM_ISP_OTF_OUTPUT);
	fimc_is_set_param_bit(is, PARAM_DRC_OTF_INPUT);
	fimc_is_set_param_bit(is, PARAM_DRC_OTF_OUTPUT);
	fimc_is_set_param_bit(is, PARAM_FD_OTF_INPUT);
पूर्ण

पूर्णांक fimc_is_hw_get_sensor_max_framerate(काष्ठा fimc_is *is)
अणु
	चयन (is->sensor->drvdata->id) अणु
	हाल FIMC_IS_SENSOR_ID_S5K6A3:
		वापस 30;
	शेष:
		वापस 15;
	पूर्ण
पूर्ण

व्योम __is_set_sensor(काष्ठा fimc_is *is, पूर्णांक fps)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा sensor_param *sensor;
	काष्ठा isp_param *isp;

	sensor = &is->config[index].sensor;
	isp = &is->config[index].isp;

	अगर (fps == 0) अणु
		sensor->frame_rate.frame_rate =
				fimc_is_hw_get_sensor_max_framerate(is);
		isp->otf_input.frameसमय_min = 0;
		isp->otf_input.frameसमय_max = 66666;
	पूर्ण अन्यथा अणु
		sensor->frame_rate.frame_rate = fps;
		isp->otf_input.frameसमय_min = 0;
		isp->otf_input.frameसमय_max = (u32)1000000 / fps;
	पूर्ण

	fimc_is_set_param_bit(is, PARAM_SENSOR_FRAME_RATE);
	fimc_is_set_param_bit(is, PARAM_ISP_OTF_INPUT);
पूर्ण

अटल व्योम __maybe_unused __is_set_init_isp_aa(काष्ठा fimc_is *is)
अणु
	काष्ठा isp_param *isp;

	isp = &is->config[is->config_index].isp;

	isp->aa.cmd = ISP_AA_COMMAND_START;
	isp->aa.target = ISP_AA_TARGET_AF | ISP_AA_TARGET_AE |
			 ISP_AA_TARGET_AWB;
	isp->aa.mode = 0;
	isp->aa.scene = 0;
	isp->aa.sleep = 0;
	isp->aa.face = 0;
	isp->aa.touch_x = 0;
	isp->aa.touch_y = 0;
	isp->aa.manual_af_setting = 0;
	isp->aa.err = ISP_AF_ERROR_NONE;

	fimc_is_set_param_bit(is, PARAM_ISP_AA);
पूर्ण

व्योम __is_set_isp_flash(काष्ठा fimc_is *is, u32 cmd, u32 redeye)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा isp_param *isp = &is->config[index].isp;

	isp->flash.cmd = cmd;
	isp->flash.redeye = redeye;
	isp->flash.err = ISP_FLASH_ERROR_NONE;

	fimc_is_set_param_bit(is, PARAM_ISP_FLASH);
पूर्ण

व्योम __is_set_isp_awb(काष्ठा fimc_is *is, u32 cmd, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा isp_param *isp;

	isp = &is->config[index].isp;

	isp->awb.cmd = cmd;
	isp->awb.illumination = val;
	isp->awb.err = ISP_AWB_ERROR_NONE;

	fimc_is_set_param_bit(is, PARAM_ISP_AWB);
पूर्ण

व्योम __is_set_isp_effect(काष्ठा fimc_is *is, u32 cmd)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा isp_param *isp;

	isp = &is->config[index].isp;

	isp->effect.cmd = cmd;
	isp->effect.err = ISP_IMAGE_EFFECT_ERROR_NONE;

	fimc_is_set_param_bit(is, PARAM_ISP_IMAGE_EFFECT);
पूर्ण

व्योम __is_set_isp_iso(काष्ठा fimc_is *is, u32 cmd, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा isp_param *isp;

	isp = &is->config[index].isp;

	isp->iso.cmd = cmd;
	isp->iso.value = val;
	isp->iso.err = ISP_ISO_ERROR_NONE;

	fimc_is_set_param_bit(is, PARAM_ISP_ISO);
पूर्ण

व्योम __is_set_isp_adjust(काष्ठा fimc_is *is, u32 cmd, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	अचिन्हित दीर्घ *p_index;
	काष्ठा isp_param *isp;

	p_index = &is->config[index].p_region_index[0];
	isp = &is->config[index].isp;

	चयन (cmd) अणु
	हाल ISP_ADJUST_COMMAND_MANUAL_CONTRAST:
		isp->adjust.contrast = val;
		अवरोध;
	हाल ISP_ADJUST_COMMAND_MANUAL_SATURATION:
		isp->adjust.saturation = val;
		अवरोध;
	हाल ISP_ADJUST_COMMAND_MANUAL_SHARPNESS:
		isp->adjust.sharpness = val;
		अवरोध;
	हाल ISP_ADJUST_COMMAND_MANUAL_EXPOSURE:
		isp->adjust.exposure = val;
		अवरोध;
	हाल ISP_ADJUST_COMMAND_MANUAL_BRIGHTNESS:
		isp->adjust.brightness = val;
		अवरोध;
	हाल ISP_ADJUST_COMMAND_MANUAL_HUE:
		isp->adjust.hue = val;
		अवरोध;
	हाल ISP_ADJUST_COMMAND_AUTO:
		isp->adjust.contrast = 0;
		isp->adjust.saturation = 0;
		isp->adjust.sharpness = 0;
		isp->adjust.exposure = 0;
		isp->adjust.brightness = 0;
		isp->adjust.hue = 0;
		अवरोध;
	पूर्ण

	अगर (!test_bit(PARAM_ISP_ADJUST, p_index)) अणु
		isp->adjust.cmd = cmd;
		isp->adjust.err = ISP_ADJUST_ERROR_NONE;
		fimc_is_set_param_bit(is, PARAM_ISP_ADJUST);
	पूर्ण अन्यथा अणु
		isp->adjust.cmd |= cmd;
	पूर्ण
पूर्ण

व्योम __is_set_isp_metering(काष्ठा fimc_is *is, u32 id, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा isp_param *isp;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[0];
	isp = &is->config[index].isp;

	चयन (id) अणु
	हाल IS_METERING_CONFIG_CMD:
		isp->metering.cmd = val;
		अवरोध;
	हाल IS_METERING_CONFIG_WIN_POS_X:
		isp->metering.win_pos_x = val;
		अवरोध;
	हाल IS_METERING_CONFIG_WIN_POS_Y:
		isp->metering.win_pos_y = val;
		अवरोध;
	हाल IS_METERING_CONFIG_WIN_WIDTH:
		isp->metering.win_width = val;
		अवरोध;
	हाल IS_METERING_CONFIG_WIN_HEIGHT:
		isp->metering.win_height = val;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (!test_bit(PARAM_ISP_METERING, p_index)) अणु
		isp->metering.err = ISP_METERING_ERROR_NONE;
		fimc_is_set_param_bit(is, PARAM_ISP_METERING);
	पूर्ण
पूर्ण

व्योम __is_set_isp_afc(काष्ठा fimc_is *is, u32 cmd, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा isp_param *isp;

	isp = &is->config[index].isp;

	isp->afc.cmd = cmd;
	isp->afc.manual = val;
	isp->afc.err = ISP_AFC_ERROR_NONE;

	fimc_is_set_param_bit(is, PARAM_ISP_AFC);
पूर्ण

व्योम __is_set_drc_control(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा drc_param *drc;

	drc = &is->config[index].drc;

	drc->control.bypass = val;

	fimc_is_set_param_bit(is, PARAM_DRC_CONTROL);
पूर्ण

व्योम __is_set_fd_control(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->control.cmd = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index))
		fimc_is_set_param_bit(is, PARAM_FD_CONTROL);
पूर्ण

व्योम __is_set_fd_config_maxface(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.max_number = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_MAXIMUM_NUMBER;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_MAXIMUM_NUMBER;
	पूर्ण
पूर्ण

व्योम __is_set_fd_config_rollangle(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.roll_angle = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_ROLL_ANGLE;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_ROLL_ANGLE;
	पूर्ण
पूर्ण

व्योम __is_set_fd_config_yawangle(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.yaw_angle = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_YAW_ANGLE;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_YAW_ANGLE;
	पूर्ण
पूर्ण

व्योम __is_set_fd_config_smilemode(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.smile_mode = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_SMILE_MODE;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_SMILE_MODE;
	पूर्ण
पूर्ण

व्योम __is_set_fd_config_blinkmode(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.blink_mode = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_BLINK_MODE;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_BLINK_MODE;
	पूर्ण
पूर्ण

व्योम __is_set_fd_config_eyedetect(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.eye_detect = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_EYES_DETECT;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_EYES_DETECT;
	पूर्ण
पूर्ण

व्योम __is_set_fd_config_mouthdetect(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.mouth_detect = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_MOUTH_DETECT;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_MOUTH_DETECT;
	पूर्ण
पूर्ण

व्योम __is_set_fd_config_orientation(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.orientation = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_ORIENTATION;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_ORIENTATION;
	पूर्ण
पूर्ण

व्योम __is_set_fd_config_orientation_val(काष्ठा fimc_is *is, u32 val)
अणु
	अचिन्हित पूर्णांक index = is->config_index;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;

	p_index = &is->config[index].p_region_index[1];
	fd = &is->config[index].fd;

	fd->config.orientation_value = val;

	अगर (!test_bit((PARAM_FD_CONFIG - 32), p_index)) अणु
		fd->config.cmd = FD_CONFIG_COMMAND_ORIENTATION_VALUE;
		fd->config.err = ERROR_FD_NONE;
		fimc_is_set_param_bit(is, PARAM_FD_CONFIG);
	पूर्ण अन्यथा अणु
		fd->config.cmd |= FD_CONFIG_COMMAND_ORIENTATION_VALUE;
	पूर्ण
पूर्ण

व्योम fimc_is_set_initial_params(काष्ठा fimc_is *is)
अणु
	काष्ठा global_param *global;
	काष्ठा isp_param *isp;
	काष्ठा drc_param *drc;
	काष्ठा fd_param *fd;
	अचिन्हित दीर्घ *p_index;
	अचिन्हित पूर्णांक index;

	index = is->config_index;
	global = &is->config[index].global;
	isp = &is->config[index].isp;
	drc = &is->config[index].drc;
	fd = &is->config[index].fd;
	p_index = &is->config[index].p_region_index[0];

	/* Global */
	global->shoपंचांगode.cmd = 1;
	fimc_is_set_param_bit(is, PARAM_GLOBAL_SHOTMODE);

	/* ISP */
	isp->control.cmd = CONTROL_COMMAND_START;
	isp->control.bypass = CONTROL_BYPASS_DISABLE;
	isp->control.err = CONTROL_ERROR_NONE;
	fimc_is_set_param_bit(is, PARAM_ISP_CONTROL);

	isp->otf_input.cmd = OTF_INPUT_COMMAND_ENABLE;
	अगर (!test_bit(PARAM_ISP_OTF_INPUT, p_index)) अणु
		isp->otf_input.width = DEFAULT_PREVIEW_STILL_WIDTH;
		isp->otf_input.height = DEFAULT_PREVIEW_STILL_HEIGHT;
		fimc_is_set_param_bit(is, PARAM_ISP_OTF_INPUT);
	पूर्ण
	अगर (is->sensor->test_pattern)
		isp->otf_input.क्रमmat = OTF_INPUT_FORMAT_STRGEN_COLORBAR_BAYER;
	अन्यथा
		isp->otf_input.क्रमmat = OTF_INPUT_FORMAT_BAYER;
	isp->otf_input.bitwidth = 10;
	isp->otf_input.order = OTF_INPUT_ORDER_BAYER_GR_BG;
	isp->otf_input.crop_offset_x = 0;
	isp->otf_input.crop_offset_y = 0;
	isp->otf_input.err = OTF_INPUT_ERROR_NONE;

	isp->dma1_input.cmd = DMA_INPUT_COMMAND_DISABLE;
	isp->dma1_input.width = 0;
	isp->dma1_input.height = 0;
	isp->dma1_input.क्रमmat = 0;
	isp->dma1_input.bitwidth = 0;
	isp->dma1_input.plane = 0;
	isp->dma1_input.order = 0;
	isp->dma1_input.buffer_number = 0;
	isp->dma1_input.width = 0;
	isp->dma1_input.err = DMA_INPUT_ERROR_NONE;
	fimc_is_set_param_bit(is, PARAM_ISP_DMA1_INPUT);

	isp->dma2_input.cmd = DMA_INPUT_COMMAND_DISABLE;
	isp->dma2_input.width = 0;
	isp->dma2_input.height = 0;
	isp->dma2_input.क्रमmat = 0;
	isp->dma2_input.bitwidth = 0;
	isp->dma2_input.plane = 0;
	isp->dma2_input.order = 0;
	isp->dma2_input.buffer_number = 0;
	isp->dma2_input.width = 0;
	isp->dma2_input.err = DMA_INPUT_ERROR_NONE;
	fimc_is_set_param_bit(is, PARAM_ISP_DMA2_INPUT);

	isp->aa.cmd = ISP_AA_COMMAND_START;
	isp->aa.target = ISP_AA_TARGET_AE | ISP_AA_TARGET_AWB;
	fimc_is_set_param_bit(is, PARAM_ISP_AA);

	अगर (!test_bit(PARAM_ISP_FLASH, p_index))
		__is_set_isp_flash(is, ISP_FLASH_COMMAND_DISABLE,
						ISP_FLASH_REDEYE_DISABLE);

	अगर (!test_bit(PARAM_ISP_AWB, p_index))
		__is_set_isp_awb(is, ISP_AWB_COMMAND_AUTO, 0);

	अगर (!test_bit(PARAM_ISP_IMAGE_EFFECT, p_index))
		__is_set_isp_effect(is, ISP_IMAGE_EFFECT_DISABLE);

	अगर (!test_bit(PARAM_ISP_ISO, p_index))
		__is_set_isp_iso(is, ISP_ISO_COMMAND_AUTO, 0);

	अगर (!test_bit(PARAM_ISP_ADJUST, p_index)) अणु
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_CONTRAST, 0);
		__is_set_isp_adjust(is,
				ISP_ADJUST_COMMAND_MANUAL_SATURATION, 0);
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_SHARPNESS, 0);
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_EXPOSURE, 0);
		__is_set_isp_adjust(is,
				ISP_ADJUST_COMMAND_MANUAL_BRIGHTNESS, 0);
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_HUE, 0);
	पूर्ण

	अगर (!test_bit(PARAM_ISP_METERING, p_index)) अणु
		__is_set_isp_metering(is, 0, ISP_METERING_COMMAND_CENTER);
		__is_set_isp_metering(is, 1, 0);
		__is_set_isp_metering(is, 2, 0);
		__is_set_isp_metering(is, 3, 0);
		__is_set_isp_metering(is, 4, 0);
	पूर्ण

	अगर (!test_bit(PARAM_ISP_AFC, p_index))
		__is_set_isp_afc(is, ISP_AFC_COMMAND_AUTO, 0);

	isp->otf_output.cmd = OTF_OUTPUT_COMMAND_ENABLE;
	अगर (!test_bit(PARAM_ISP_OTF_OUTPUT, p_index)) अणु
		isp->otf_output.width = DEFAULT_PREVIEW_STILL_WIDTH;
		isp->otf_output.height = DEFAULT_PREVIEW_STILL_HEIGHT;
		fimc_is_set_param_bit(is, PARAM_ISP_OTF_OUTPUT);
	पूर्ण
	isp->otf_output.क्रमmat = OTF_OUTPUT_FORMAT_YUV444;
	isp->otf_output.bitwidth = 12;
	isp->otf_output.order = 0;
	isp->otf_output.err = OTF_OUTPUT_ERROR_NONE;

	अगर (!test_bit(PARAM_ISP_DMA1_OUTPUT, p_index)) अणु
		isp->dma1_output.cmd = DMA_OUTPUT_COMMAND_DISABLE;
		isp->dma1_output.width = 0;
		isp->dma1_output.height = 0;
		isp->dma1_output.क्रमmat = 0;
		isp->dma1_output.bitwidth = 0;
		isp->dma1_output.plane = 0;
		isp->dma1_output.order = 0;
		isp->dma1_output.buffer_number = 0;
		isp->dma1_output.buffer_address = 0;
		isp->dma1_output.notअगरy_dma_करोne = 0;
		isp->dma1_output.dma_out_mask = 0;
		isp->dma1_output.err = DMA_OUTPUT_ERROR_NONE;
		fimc_is_set_param_bit(is, PARAM_ISP_DMA1_OUTPUT);
	पूर्ण

	अगर (!test_bit(PARAM_ISP_DMA2_OUTPUT, p_index)) अणु
		isp->dma2_output.cmd = DMA_OUTPUT_COMMAND_DISABLE;
		isp->dma2_output.width = 0;
		isp->dma2_output.height = 0;
		isp->dma2_output.क्रमmat = 0;
		isp->dma2_output.bitwidth = 0;
		isp->dma2_output.plane = 0;
		isp->dma2_output.order = 0;
		isp->dma2_output.buffer_number = 0;
		isp->dma2_output.buffer_address = 0;
		isp->dma2_output.notअगरy_dma_करोne = 0;
		isp->dma2_output.dma_out_mask = 0;
		isp->dma2_output.err = DMA_OUTPUT_ERROR_NONE;
		fimc_is_set_param_bit(is, PARAM_ISP_DMA2_OUTPUT);
	पूर्ण

	/* Sensor */
	अगर (!test_bit(PARAM_SENSOR_FRAME_RATE, p_index)) अणु
		अगर (is->config_index == 0)
			__is_set_sensor(is, 0);
	पूर्ण

	/* DRC */
	drc->control.cmd = CONTROL_COMMAND_START;
	__is_set_drc_control(is, CONTROL_BYPASS_ENABLE);

	drc->otf_input.cmd = OTF_INPUT_COMMAND_ENABLE;
	अगर (!test_bit(PARAM_DRC_OTF_INPUT, p_index)) अणु
		drc->otf_input.width = DEFAULT_PREVIEW_STILL_WIDTH;
		drc->otf_input.height = DEFAULT_PREVIEW_STILL_HEIGHT;
		fimc_is_set_param_bit(is, PARAM_DRC_OTF_INPUT);
	पूर्ण
	drc->otf_input.क्रमmat = OTF_INPUT_FORMAT_YUV444;
	drc->otf_input.bitwidth = 12;
	drc->otf_input.order = 0;
	drc->otf_input.err = OTF_INPUT_ERROR_NONE;

	drc->dma_input.cmd = DMA_INPUT_COMMAND_DISABLE;
	drc->dma_input.width = 0;
	drc->dma_input.height = 0;
	drc->dma_input.क्रमmat = 0;
	drc->dma_input.bitwidth = 0;
	drc->dma_input.plane = 0;
	drc->dma_input.order = 0;
	drc->dma_input.buffer_number = 0;
	drc->dma_input.width = 0;
	drc->dma_input.err = DMA_INPUT_ERROR_NONE;
	fimc_is_set_param_bit(is, PARAM_DRC_DMA_INPUT);

	drc->otf_output.cmd = OTF_OUTPUT_COMMAND_ENABLE;
	अगर (!test_bit(PARAM_DRC_OTF_OUTPUT, p_index)) अणु
		drc->otf_output.width = DEFAULT_PREVIEW_STILL_WIDTH;
		drc->otf_output.height = DEFAULT_PREVIEW_STILL_HEIGHT;
		fimc_is_set_param_bit(is, PARAM_DRC_OTF_OUTPUT);
	पूर्ण
	drc->otf_output.क्रमmat = OTF_OUTPUT_FORMAT_YUV444;
	drc->otf_output.bitwidth = 8;
	drc->otf_output.order = 0;
	drc->otf_output.err = OTF_OUTPUT_ERROR_NONE;

	/* FD */
	__is_set_fd_control(is, CONTROL_COMMAND_STOP);
	fd->control.bypass = CONTROL_BYPASS_DISABLE;

	fd->otf_input.cmd = OTF_INPUT_COMMAND_ENABLE;
	अगर (!test_bit(PARAM_FD_OTF_INPUT, p_index)) अणु
		fd->otf_input.width = DEFAULT_PREVIEW_STILL_WIDTH;
		fd->otf_input.height = DEFAULT_PREVIEW_STILL_HEIGHT;
		fimc_is_set_param_bit(is, PARAM_FD_OTF_INPUT);
	पूर्ण

	fd->otf_input.क्रमmat = OTF_INPUT_FORMAT_YUV444;
	fd->otf_input.bitwidth = 8;
	fd->otf_input.order = 0;
	fd->otf_input.err = OTF_INPUT_ERROR_NONE;

	fd->dma_input.cmd = DMA_INPUT_COMMAND_DISABLE;
	fd->dma_input.width = 0;
	fd->dma_input.height = 0;
	fd->dma_input.क्रमmat = 0;
	fd->dma_input.bitwidth = 0;
	fd->dma_input.plane = 0;
	fd->dma_input.order = 0;
	fd->dma_input.buffer_number = 0;
	fd->dma_input.width = 0;
	fd->dma_input.err = DMA_INPUT_ERROR_NONE;
	fimc_is_set_param_bit(is, PARAM_FD_DMA_INPUT);

	__is_set_fd_config_maxface(is, 5);
	__is_set_fd_config_rollangle(is, FD_CONFIG_ROLL_ANGLE_FULL);
	__is_set_fd_config_yawangle(is, FD_CONFIG_YAW_ANGLE_45_90);
	__is_set_fd_config_smilemode(is, FD_CONFIG_SMILE_MODE_DISABLE);
	__is_set_fd_config_blinkmode(is, FD_CONFIG_BLINK_MODE_DISABLE);
	__is_set_fd_config_eyedetect(is, FD_CONFIG_EYES_DETECT_ENABLE);
	__is_set_fd_config_mouthdetect(is, FD_CONFIG_MOUTH_DETECT_DISABLE);
	__is_set_fd_config_orientation(is, FD_CONFIG_ORIENTATION_DISABLE);
	__is_set_fd_config_orientation_val(is, 0);
पूर्ण

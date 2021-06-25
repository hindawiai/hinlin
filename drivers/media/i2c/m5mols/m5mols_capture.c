<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * The Capture code क्रम Fujitsu M-5MOLS ISP
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * Author: HeungJun Kim <riverful.kim@samsung.com>
 *
 * Copyright (C) 2009 Samsung Electronics Co., Ltd.
 * Author: Dongsoo Nathaniel Kim <करोngsoo45.kim@samsung.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/i2c/m5mols.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

#समावेश "m5mols.h"
#समावेश "m5mols_reg.h"

/**
 * m5mols_पढ़ो_rational - I2C पढ़ो of a rational number
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 * @addr_num: numerator रेजिस्टर
 * @addr_den: denominator रेजिस्टर
 * @val: place to store the भागision result
 *
 * Read numerator and denominator from रेजिस्टरs @addr_num and @addr_den
 * respectively and वापस the भागision result in @val.
 */
अटल पूर्णांक m5mols_पढ़ो_rational(काष्ठा v4l2_subdev *sd, u32 addr_num,
				u32 addr_den, u32 *val)
अणु
	u32 num, den;

	पूर्णांक ret = m5mols_पढ़ो_u32(sd, addr_num, &num);
	अगर (!ret)
		ret = m5mols_पढ़ो_u32(sd, addr_den, &den);
	अगर (ret)
		वापस ret;
	*val = den == 0 ? 0 : num / den;
	वापस ret;
पूर्ण

/**
 * m5mols_capture_info - Gather captured image inक्रमmation
 * @info: M-5MOLS driver data काष्ठाure
 *
 * For now it gathers only EXIF inक्रमmation and file size.
 */
अटल पूर्णांक m5mols_capture_info(काष्ठा m5mols_info *info)
अणु
	काष्ठा m5mols_exअगर *exअगर = &info->cap.exअगर;
	काष्ठा v4l2_subdev *sd = &info->sd;
	पूर्णांक ret;

	ret = m5mols_पढ़ो_rational(sd, EXIF_INFO_EXPTIME_NU,
				   EXIF_INFO_EXPTIME_DE, &exअगर->exposure_समय);
	अगर (ret)
		वापस ret;
	ret = m5mols_पढ़ो_rational(sd, EXIF_INFO_TV_NU, EXIF_INFO_TV_DE,
				   &exअगर->shutter_speed);
	अगर (ret)
		वापस ret;
	ret = m5mols_पढ़ो_rational(sd, EXIF_INFO_AV_NU, EXIF_INFO_AV_DE,
				   &exअगर->aperture);
	अगर (ret)
		वापस ret;
	ret = m5mols_पढ़ो_rational(sd, EXIF_INFO_BV_NU, EXIF_INFO_BV_DE,
				   &exअगर->brightness);
	अगर (ret)
		वापस ret;
	ret = m5mols_पढ़ो_rational(sd, EXIF_INFO_EBV_NU, EXIF_INFO_EBV_DE,
				   &exअगर->exposure_bias);
	अगर (ret)
		वापस ret;

	ret = m5mols_पढ़ो_u16(sd, EXIF_INFO_ISO, &exअगर->iso_speed);
	अगर (!ret)
		ret = m5mols_पढ़ो_u16(sd, EXIF_INFO_FLASH, &exअगर->flash);
	अगर (!ret)
		ret = m5mols_पढ़ो_u16(sd, EXIF_INFO_SDR, &exअगर->sdr);
	अगर (!ret)
		ret = m5mols_पढ़ो_u16(sd, EXIF_INFO_QVAL, &exअगर->qval);
	अगर (ret)
		वापस ret;

	अगर (!ret)
		ret = m5mols_पढ़ो_u32(sd, CAPC_IMAGE_SIZE, &info->cap.मुख्य);
	अगर (!ret)
		ret = m5mols_पढ़ो_u32(sd, CAPC_THUMB_SIZE, &info->cap.thumb);
	अगर (!ret)
		info->cap.total = info->cap.मुख्य + info->cap.thumb;

	वापस ret;
पूर्ण

पूर्णांक m5mols_start_capture(काष्ठा m5mols_info *info)
अणु
	अचिन्हित पूर्णांक framesize = info->cap.buf_size - M5MOLS_JPEG_TAGS_SIZE;
	काष्ठा v4l2_subdev *sd = &info->sd;
	पूर्णांक ret;

	/*
	 * Synchronize the controls, set the capture frame resolution and color
	 * क्रमmat. The frame capture is initiated during चयनing from Monitor
	 * to Capture mode.
	 */
	ret = m5mols_set_mode(info, REG_MONITOR);
	अगर (!ret)
		ret = m5mols_restore_controls(info);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPP_YUVOUT_MAIN, REG_JPEG);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPP_MAIN_IMAGE_SIZE, info->resolution);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPP_JPEG_SIZE_MAX, framesize);
	अगर (!ret)
		ret = m5mols_set_mode(info, REG_CAPTURE);
	अगर (!ret)
		/* Wait until a frame is captured to ISP पूर्णांकernal memory */
		ret = m5mols_रुको_पूर्णांकerrupt(sd, REG_INT_CAPTURE, 2000);
	अगर (ret)
		वापस ret;

	/*
	 * Initiate the captured data transfer to a MIPI-CSI receiver.
	 */
	ret = m5mols_ग_लिखो(sd, CAPC_SEL_FRAME, 1);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPC_START, REG_CAP_START_MAIN);
	अगर (!ret) अणु
		bool captured = false;
		अचिन्हित पूर्णांक size;

		/* Wait क्रम the capture completion पूर्णांकerrupt */
		ret = m5mols_रुको_पूर्णांकerrupt(sd, REG_INT_CAPTURE, 2000);
		अगर (!ret) अणु
			captured = true;
			ret = m5mols_capture_info(info);
		पूर्ण
		size = captured ? info->cap.मुख्य : 0;
		v4l2_dbg(1, m5mols_debug, sd, "%s: size: %d, thumb.: %d B\n",
			 __func__, size, info->cap.thumb);

		v4l2_subdev_notअगरy(sd, S5P_FIMC_TX_END_NOTIFY, &size);
	पूर्ण

	वापस ret;
पूर्ण

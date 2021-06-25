<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम MT9M032 CMOS Image Sensor from Micron
 *
 * Copyright (C) 2010-2011 Lund Engineering
 * Contact: Gil Lund <gwlund@lundeng.com>
 * Author: Martin Hostettler <martin@neutronstar.dyndns.org>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-mediabus.h>

#समावेश <media/media-entity.h>
#समावेश <media/i2c/mt9m032.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "aptina-pll.h"

/*
 * width and height include active boundary and black parts
 *
 * column    0-  15 active boundary
 * column   16-1455 image
 * column 1456-1471 active boundary
 * column 1472-1599 black
 *
 * row       0-  51 black
 * row      53-  59 active boundary
 * row      60-1139 image
 * row    1140-1147 active boundary
 * row    1148-1151 black
 */

#घोषणा MT9M032_PIXEL_ARRAY_WIDTH			1600
#घोषणा MT9M032_PIXEL_ARRAY_HEIGHT			1152

#घोषणा MT9M032_CHIP_VERSION				0x00
#घोषणा		MT9M032_CHIP_VERSION_VALUE		0x1402
#घोषणा MT9M032_ROW_START				0x01
#घोषणा		MT9M032_ROW_START_MIN			0
#घोषणा		MT9M032_ROW_START_MAX			1152
#घोषणा		MT9M032_ROW_START_DEF			60
#घोषणा MT9M032_COLUMN_START				0x02
#घोषणा		MT9M032_COLUMN_START_MIN		0
#घोषणा		MT9M032_COLUMN_START_MAX		1600
#घोषणा		MT9M032_COLUMN_START_DEF		16
#घोषणा MT9M032_ROW_SIZE				0x03
#घोषणा		MT9M032_ROW_SIZE_MIN			32
#घोषणा		MT9M032_ROW_SIZE_MAX			1152
#घोषणा		MT9M032_ROW_SIZE_DEF			1080
#घोषणा MT9M032_COLUMN_SIZE				0x04
#घोषणा		MT9M032_COLUMN_SIZE_MIN			32
#घोषणा		MT9M032_COLUMN_SIZE_MAX			1600
#घोषणा		MT9M032_COLUMN_SIZE_DEF			1440
#घोषणा MT9M032_HBLANK					0x05
#घोषणा MT9M032_VBLANK					0x06
#घोषणा		MT9M032_VBLANK_MAX			0x7ff
#घोषणा MT9M032_SHUTTER_WIDTH_HIGH			0x08
#घोषणा MT9M032_SHUTTER_WIDTH_LOW			0x09
#घोषणा		MT9M032_SHUTTER_WIDTH_MIN		1
#घोषणा		MT9M032_SHUTTER_WIDTH_MAX		1048575
#घोषणा		MT9M032_SHUTTER_WIDTH_DEF		1943
#घोषणा MT9M032_PIX_CLK_CTRL				0x0a
#घोषणा		MT9M032_PIX_CLK_CTRL_INV_PIXCLK		0x8000
#घोषणा MT9M032_RESTART					0x0b
#घोषणा MT9M032_RESET					0x0d
#घोषणा MT9M032_PLL_CONFIG1				0x11
#घोषणा		MT9M032_PLL_CONFIG1_PREDIV_MASK		0x3f
#घोषणा		MT9M032_PLL_CONFIG1_MUL_SHIFT		8
#घोषणा MT9M032_READ_MODE1				0x1e
#घोषणा		MT9M032_READ_MODE1_OUTPUT_BAD_FRAMES	(1 << 13)
#घोषणा		MT9M032_READ_MODE1_MAINTAIN_FRAME_RATE	(1 << 12)
#घोषणा		MT9M032_READ_MODE1_XOR_LINE_VALID	(1 << 11)
#घोषणा		MT9M032_READ_MODE1_CONT_LINE_VALID	(1 << 10)
#घोषणा		MT9M032_READ_MODE1_INVERT_TRIGGER	(1 << 9)
#घोषणा		MT9M032_READ_MODE1_SNAPSHOT		(1 << 8)
#घोषणा		MT9M032_READ_MODE1_GLOBAL_RESET		(1 << 7)
#घोषणा		MT9M032_READ_MODE1_BULB_EXPOSURE	(1 << 6)
#घोषणा		MT9M032_READ_MODE1_INVERT_STROBE	(1 << 5)
#घोषणा		MT9M032_READ_MODE1_STROBE_ENABLE	(1 << 4)
#घोषणा		MT9M032_READ_MODE1_STROBE_START_TRIG1	(0 << 2)
#घोषणा		MT9M032_READ_MODE1_STROBE_START_EXP	(1 << 2)
#घोषणा		MT9M032_READ_MODE1_STROBE_START_SHUTTER	(2 << 2)
#घोषणा		MT9M032_READ_MODE1_STROBE_START_TRIG2	(3 << 2)
#घोषणा		MT9M032_READ_MODE1_STROBE_END_TRIG1	(0 << 0)
#घोषणा		MT9M032_READ_MODE1_STROBE_END_EXP	(1 << 0)
#घोषणा		MT9M032_READ_MODE1_STROBE_END_SHUTTER	(2 << 0)
#घोषणा		MT9M032_READ_MODE1_STROBE_END_TRIG2	(3 << 0)
#घोषणा MT9M032_READ_MODE2				0x20
#घोषणा		MT9M032_READ_MODE2_VFLIP_SHIFT		15
#घोषणा		MT9M032_READ_MODE2_HFLIP_SHIFT		14
#घोषणा		MT9M032_READ_MODE2_ROW_BLC		0x40
#घोषणा MT9M032_GAIN_GREEN1				0x2b
#घोषणा MT9M032_GAIN_BLUE				0x2c
#घोषणा MT9M032_GAIN_RED				0x2d
#घोषणा MT9M032_GAIN_GREEN2				0x2e

/* ग_लिखो only */
#घोषणा MT9M032_GAIN_ALL				0x35
#घोषणा		MT9M032_GAIN_DIGITAL_MASK		0x7f
#घोषणा		MT9M032_GAIN_DIGITAL_SHIFT		8
#घोषणा		MT9M032_GAIN_AMUL_SHIFT			6
#घोषणा		MT9M032_GAIN_ANALOG_MASK		0x3f
#घोषणा MT9M032_FORMATTER1				0x9e
#घोषणा		MT9M032_FORMATTER1_PLL_P1_6		(1 << 8)
#घोषणा		MT9M032_FORMATTER1_PARALLEL		(1 << 12)
#घोषणा MT9M032_FORMATTER2				0x9f
#घोषणा		MT9M032_FORMATTER2_DOUT_EN		0x1000
#घोषणा		MT9M032_FORMATTER2_PIXCLK_EN		0x2000

/*
 * The available MT9M032 datasheet is missing करोcumentation क्रम रेजिस्टर 0x10
 * MT9P031 seems to be बंद enough, so use स्थिरants from that datasheet क्रम
 * now.
 * But keep the name MT9P031 to remind us, that this isn't really confirmed
 * क्रम this sensor.
 */
#घोषणा MT9P031_PLL_CONTROL				0x10
#घोषणा		MT9P031_PLL_CONTROL_PWROFF		0x0050
#घोषणा		MT9P031_PLL_CONTROL_PWRON		0x0051
#घोषणा		MT9P031_PLL_CONTROL_USEPLL		0x0052

काष्ठा mt9m032 अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;
	काष्ठा mt9m032_platक्रमm_data *pdata;

	अचिन्हित पूर्णांक pix_घड़ी;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *hflip;
		काष्ठा v4l2_ctrl *vflip;
	पूर्ण;

	काष्ठा mutex lock; /* Protects streaming, क्रमmat, पूर्णांकerval and crop */

	bool streaming;

	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा v4l2_rect crop;
	काष्ठा v4l2_fract frame_पूर्णांकerval;
पूर्ण;

#घोषणा to_mt9m032(sd)	container_of(sd, काष्ठा mt9m032, subdev)
#घोषणा to_dev(sensor) \
	(&((काष्ठा i2c_client *)v4l2_get_subdevdata(&(sensor)->subdev))->dev)

अटल पूर्णांक mt9m032_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_swapped(client, reg);
पूर्ण

अटल पूर्णांक mt9m032_ग_लिखो(काष्ठा i2c_client *client, u8 reg, स्थिर u16 data)
अणु
	वापस i2c_smbus_ग_लिखो_word_swapped(client, reg, data);
पूर्ण

अटल u32 mt9m032_row_समय(काष्ठा mt9m032 *sensor, अचिन्हित पूर्णांक width)
अणु
	अचिन्हित पूर्णांक effective_width;
	u32 ns;

	effective_width = width + 716; /* empirical value */
	ns = भाग_u64(1000000000ULL * effective_width, sensor->pix_घड़ी);
	dev_dbg(to_dev(sensor),	"MT9M032 line time: %u ns\n", ns);
	वापस ns;
पूर्ण

अटल पूर्णांक mt9m032_update_timing(काष्ठा mt9m032 *sensor,
				 काष्ठा v4l2_fract *पूर्णांकerval)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	काष्ठा v4l2_rect *crop = &sensor->crop;
	अचिन्हित पूर्णांक min_vblank;
	अचिन्हित पूर्णांक vblank;
	u32 row_समय;

	अगर (!पूर्णांकerval)
		पूर्णांकerval = &sensor->frame_पूर्णांकerval;

	row_समय = mt9m032_row_समय(sensor, crop->width);

	vblank = भाग_u64(1000000000ULL * पूर्णांकerval->numerator,
			 (u64)row_समय * पूर्णांकerval->denominator)
	       - crop->height;

	अगर (vblank > MT9M032_VBLANK_MAX) अणु
		/* hardware limits to 11 bit values */
		पूर्णांकerval->denominator = 1000;
		पूर्णांकerval->numerator =
			भाग_u64((crop->height + MT9M032_VBLANK_MAX) *
				(u64)row_समय * पूर्णांकerval->denominator,
				1000000000ULL);
		vblank = भाग_u64(1000000000ULL * पूर्णांकerval->numerator,
				 (u64)row_समय * पूर्णांकerval->denominator)
		       - crop->height;
	पूर्ण
	/* enक्रमce minimal 1.6ms blanking समय. */
	min_vblank = 1600000 / row_समय;
	vblank = clamp_t(अचिन्हित पूर्णांक, vblank, min_vblank, MT9M032_VBLANK_MAX);

	वापस mt9m032_ग_लिखो(client, MT9M032_VBLANK, vblank);
पूर्ण

अटल पूर्णांक mt9m032_update_geom_timing(काष्ठा mt9m032 *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	पूर्णांक ret;

	ret = mt9m032_ग_लिखो(client, MT9M032_COLUMN_SIZE,
			    sensor->crop.width - 1);
	अगर (!ret)
		ret = mt9m032_ग_लिखो(client, MT9M032_ROW_SIZE,
				    sensor->crop.height - 1);
	अगर (!ret)
		ret = mt9m032_ग_लिखो(client, MT9M032_COLUMN_START,
				    sensor->crop.left);
	अगर (!ret)
		ret = mt9m032_ग_लिखो(client, MT9M032_ROW_START,
				    sensor->crop.top);
	अगर (!ret)
		ret = mt9m032_update_timing(sensor, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक update_क्रमmatter2(काष्ठा mt9m032 *sensor, bool streaming)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	u16 reg_val =   MT9M032_FORMATTER2_DOUT_EN
		      | 0x0070;  /* parts reserved! */
				 /* possibly क्रम changing to 14-bit mode */

	अगर (streaming)
		reg_val |= MT9M032_FORMATTER2_PIXCLK_EN;   /* pixघड़ी enable */

	वापस mt9m032_ग_लिखो(client, MT9M032_FORMATTER2, reg_val);
पूर्ण

अटल पूर्णांक mt9m032_setup_pll(काष्ठा mt9m032 *sensor)
अणु
	अटल स्थिर काष्ठा aptina_pll_limits limits = अणु
		.ext_घड़ी_min = 8000000,
		.ext_घड़ी_max = 16500000,
		.पूर्णांक_घड़ी_min = 2000000,
		.पूर्णांक_घड़ी_max = 24000000,
		.out_घड़ी_min = 322000000,
		.out_घड़ी_max = 693000000,
		.pix_घड़ी_max = 99000000,
		.n_min = 1,
		.n_max = 64,
		.m_min = 16,
		.m_max = 255,
		.p1_min = 6,
		.p1_max = 7,
	पूर्ण;

	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	काष्ठा mt9m032_platक्रमm_data *pdata = sensor->pdata;
	काष्ठा aptina_pll pll;
	u16 reg_val;
	पूर्णांक ret;

	pll.ext_घड़ी = pdata->ext_घड़ी;
	pll.pix_घड़ी = pdata->pix_घड़ी;

	ret = aptina_pll_calculate(&client->dev, &limits, &pll);
	अगर (ret < 0)
		वापस ret;

	sensor->pix_घड़ी = pdata->pix_घड़ी;

	ret = mt9m032_ग_लिखो(client, MT9M032_PLL_CONFIG1,
			    (pll.m << MT9M032_PLL_CONFIG1_MUL_SHIFT) |
			    ((pll.n - 1) & MT9M032_PLL_CONFIG1_PREDIV_MASK));
	अगर (!ret)
		ret = mt9m032_ग_लिखो(client, MT9P031_PLL_CONTROL,
				    MT9P031_PLL_CONTROL_PWRON |
				    MT9P031_PLL_CONTROL_USEPLL);
	अगर (!ret)		/* more reserved, Continuous, Master Mode */
		ret = mt9m032_ग_लिखो(client, MT9M032_READ_MODE1, 0x8000 |
				    MT9M032_READ_MODE1_STROBE_START_EXP |
				    MT9M032_READ_MODE1_STROBE_END_SHUTTER);
	अगर (!ret) अणु
		reg_val = (pll.p1 == 6 ? MT9M032_FORMATTER1_PLL_P1_6 : 0)
			| MT9M032_FORMATTER1_PARALLEL | 0x001e; /* 14-bit */
		ret = mt9m032_ग_लिखो(client, MT9M032_FORMATTER1, reg_val);
	पूर्ण

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Subdev pad operations
 */

अटल पूर्णांक mt9m032_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index != 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_Y8_1X8;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m032_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->index != 0 || fse->code != MEDIA_BUS_FMT_Y8_1X8)
		वापस -EINVAL;

	fse->min_width = MT9M032_COLUMN_SIZE_DEF;
	fse->max_width = MT9M032_COLUMN_SIZE_DEF;
	fse->min_height = MT9M032_ROW_SIZE_DEF;
	fse->max_height = MT9M032_ROW_SIZE_DEF;

	वापस 0;
पूर्ण

/**
 * __mt9m032_get_pad_crop() - get crop rect
 * @sensor: poपूर्णांकer to the sensor काष्ठा
 * @cfg: v4l2_subdev_pad_config क्रम getting the try crop rect from
 * @which: select try or active crop rect
 *
 * Returns a poपूर्णांकer the current active or fh relative try crop rect
 */
अटल काष्ठा v4l2_rect *
__mt9m032_get_pad_crop(काष्ठा mt9m032 *sensor, काष्ठा v4l2_subdev_pad_config *cfg,
		       क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&sensor->subdev, cfg, 0);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &sensor->crop;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * __mt9m032_get_pad_क्रमmat() - get क्रमmat
 * @sensor: poपूर्णांकer to the sensor काष्ठा
 * @cfg: v4l2_subdev_pad_config क्रम getting the try क्रमmat from
 * @which: select try or active क्रमmat
 *
 * Returns a poपूर्णांकer the current active or fh relative try क्रमmat
 */
अटल काष्ठा v4l2_mbus_framefmt *
__mt9m032_get_pad_क्रमmat(काष्ठा mt9m032 *sensor, काष्ठा v4l2_subdev_pad_config *cfg,
			 क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&sensor->subdev, cfg, 0);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &sensor->क्रमmat;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mt9m032_get_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(subdev);

	mutex_lock(&sensor->lock);
	fmt->क्रमmat = *__mt9m032_get_pad_क्रमmat(sensor, cfg, fmt->which);
	mutex_unlock(&sensor->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m032_set_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(subdev);
	पूर्णांक ret;

	mutex_lock(&sensor->lock);

	अगर (sensor->streaming && fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	/* Scaling is not supported, the क्रमmat is thus fixed. */
	fmt->क्रमmat = *__mt9m032_get_pad_क्रमmat(sensor, cfg, fmt->which);
	ret = 0;

करोne:
	mutex_unlock(&sensor->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m032_get_pad_selection(काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(subdev);

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	mutex_lock(&sensor->lock);
	sel->r = *__mt9m032_get_pad_crop(sensor, cfg, sel->which);
	mutex_unlock(&sensor->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m032_set_pad_selection(काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *__crop;
	काष्ठा v4l2_rect rect;
	पूर्णांक ret = 0;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	mutex_lock(&sensor->lock);

	अगर (sensor->streaming && sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	/* Clamp the crop rectangle boundaries and align them to a multiple of 2
	 * pixels to ensure a GRBG Bayer pattern.
	 */
	rect.left = clamp(ALIGN(sel->r.left, 2), MT9M032_COLUMN_START_MIN,
			  MT9M032_COLUMN_START_MAX);
	rect.top = clamp(ALIGN(sel->r.top, 2), MT9M032_ROW_START_MIN,
			 MT9M032_ROW_START_MAX);
	rect.width = clamp_t(अचिन्हित पूर्णांक, ALIGN(sel->r.width, 2),
			     MT9M032_COLUMN_SIZE_MIN, MT9M032_COLUMN_SIZE_MAX);
	rect.height = clamp_t(अचिन्हित पूर्णांक, ALIGN(sel->r.height, 2),
			      MT9M032_ROW_SIZE_MIN, MT9M032_ROW_SIZE_MAX);

	rect.width = min_t(अचिन्हित पूर्णांक, rect.width,
			   MT9M032_PIXEL_ARRAY_WIDTH - rect.left);
	rect.height = min_t(अचिन्हित पूर्णांक, rect.height,
			    MT9M032_PIXEL_ARRAY_HEIGHT - rect.top);

	__crop = __mt9m032_get_pad_crop(sensor, cfg, sel->which);

	अगर (rect.width != __crop->width || rect.height != __crop->height) अणु
		/* Reset the output image size अगर the crop rectangle size has
		 * been modअगरied.
		 */
		क्रमmat = __mt9m032_get_pad_क्रमmat(sensor, cfg, sel->which);
		क्रमmat->width = rect.width;
		क्रमmat->height = rect.height;
	पूर्ण

	*__crop = rect;
	sel->r = rect;

	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		ret = mt9m032_update_geom_timing(sensor);

करोne:
	mutex_unlock(&sensor->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m032_get_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				      काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(subdev);

	mutex_lock(&sensor->lock);
	स_रखो(fi, 0, माप(*fi));
	fi->पूर्णांकerval = sensor->frame_पूर्णांकerval;
	mutex_unlock(&sensor->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m032_set_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				      काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(subdev);
	पूर्णांक ret;

	mutex_lock(&sensor->lock);

	अगर (sensor->streaming) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	/* Aव्योम भागisions by 0. */
	अगर (fi->पूर्णांकerval.denominator == 0)
		fi->पूर्णांकerval.denominator = 1;

	ret = mt9m032_update_timing(sensor, &fi->पूर्णांकerval);
	अगर (!ret)
		sensor->frame_पूर्णांकerval = fi->पूर्णांकerval;

करोne:
	mutex_unlock(&sensor->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m032_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक streaming)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(subdev);
	पूर्णांक ret;

	mutex_lock(&sensor->lock);
	ret = update_क्रमmatter2(sensor, streaming);
	अगर (!ret)
		sensor->streaming = streaming;
	mutex_unlock(&sensor->lock);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev core operations
 */

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक mt9m032_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	पूर्णांक val;

	अगर (reg->reg > 0xff)
		वापस -EINVAL;

	val = mt9m032_पढ़ो(client, reg->reg);
	अगर (val < 0)
		वापस -EIO;

	reg->size = 2;
	reg->val = val;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m032_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा mt9m032 *sensor = to_mt9m032(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);

	अगर (reg->reg > 0xff)
		वापस -EINVAL;

	वापस mt9m032_ग_लिखो(client, reg->reg, reg->val);
पूर्ण
#पूर्ण_अगर

/* -----------------------------------------------------------------------------
 * V4L2 subdev control operations
 */

अटल पूर्णांक update_पढ़ो_mode2(काष्ठा mt9m032 *sensor, bool vflip, bool hflip)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	पूर्णांक reg_val = (vflip << MT9M032_READ_MODE2_VFLIP_SHIFT)
		    | (hflip << MT9M032_READ_MODE2_HFLIP_SHIFT)
		    | MT9M032_READ_MODE2_ROW_BLC
		    | 0x0007;

	वापस mt9m032_ग_लिखो(client, MT9M032_READ_MODE2, reg_val);
पूर्ण

अटल पूर्णांक mt9m032_set_gain(काष्ठा mt9m032 *sensor, s32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	पूर्णांक digital_gain_val;	/* in 1/8th (0..127) */
	पूर्णांक analog_mul;		/* 0 or 1 */
	पूर्णांक analog_gain_val;	/* in 1/16th. (0..63) */
	u16 reg_val;

	digital_gain_val = 51; /* from setup example */

	अगर (val < 63) अणु
		analog_mul = 0;
		analog_gain_val = val;
	पूर्ण अन्यथा अणु
		analog_mul = 1;
		analog_gain_val = val / 2;
	पूर्ण

	/* a_gain = (1 + analog_mul) + (analog_gain_val + 1) / 16 */
	/* overall_gain = a_gain * (1 + digital_gain_val / 8) */

	reg_val = ((digital_gain_val & MT9M032_GAIN_DIGITAL_MASK)
		   << MT9M032_GAIN_DIGITAL_SHIFT)
		| ((analog_mul & 1) << MT9M032_GAIN_AMUL_SHIFT)
		| (analog_gain_val & MT9M032_GAIN_ANALOG_MASK);

	वापस mt9m032_ग_लिखो(client, MT9M032_GAIN_ALL, reg_val);
पूर्ण

अटल पूर्णांक mt9m032_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	अगर (ctrl->id == V4L2_CID_GAIN && ctrl->val >= 63) अणु
		/* round because of multiplier used क्रम values >= 63 */
		ctrl->val &= ~1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m032_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9m032 *sensor =
		container_of(ctrl->handler, काष्ठा mt9m032, ctrls);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN:
		वापस mt9m032_set_gain(sensor, ctrl->val);

	हाल V4L2_CID_HFLIP:
	/* हाल V4L2_CID_VFLIP: -- In the same cluster */
		वापस update_पढ़ो_mode2(sensor, sensor->vflip->val,
					 sensor->hflip->val);

	हाल V4L2_CID_EXPOSURE:
		ret = mt9m032_ग_लिखो(client, MT9M032_SHUTTER_WIDTH_HIGH,
				    (ctrl->val >> 16) & 0xffff);
		अगर (ret < 0)
			वापस ret;

		वापस mt9m032_ग_लिखो(client, MT9M032_SHUTTER_WIDTH_LOW,
				     ctrl->val & 0xffff);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9m032_ctrl_ops = अणु
	.s_ctrl = mt9m032_set_ctrl,
	.try_ctrl = mt9m032_try_ctrl,
पूर्ण;

/* -------------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9m032_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = mt9m032_g_रेजिस्टर,
	.s_रेजिस्टर = mt9m032_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9m032_video_ops = अणु
	.s_stream = mt9m032_s_stream,
	.g_frame_पूर्णांकerval = mt9m032_get_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = mt9m032_set_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9m032_pad_ops = अणु
	.क्रमागत_mbus_code = mt9m032_क्रमागत_mbus_code,
	.क्रमागत_frame_size = mt9m032_क्रमागत_frame_size,
	.get_fmt = mt9m032_get_pad_क्रमmat,
	.set_fmt = mt9m032_set_pad_क्रमmat,
	.set_selection = mt9m032_set_pad_selection,
	.get_selection = mt9m032_get_pad_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9m032_ops = अणु
	.core = &mt9m032_core_ops,
	.video = &mt9m032_video_ops,
	.pad = &mt9m032_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Driver initialization and probing
 */

अटल पूर्णांक mt9m032_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *devid)
अणु
	काष्ठा mt9m032_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा mt9m032 *sensor;
	पूर्णांक chip_version;
	पूर्णांक ret;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_warn(&client->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		वापस -EIO;
	पूर्ण

	अगर (!client->dev.platक्रमm_data)
		वापस -ENODEV;

	sensor = devm_kzalloc(&client->dev, माप(*sensor), GFP_KERNEL);
	अगर (sensor == शून्य)
		वापस -ENOMEM;

	mutex_init(&sensor->lock);

	sensor->pdata = pdata;

	v4l2_i2c_subdev_init(&sensor->subdev, client, &mt9m032_ops);
	sensor->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	chip_version = mt9m032_पढ़ो(client, MT9M032_CHIP_VERSION);
	अगर (chip_version != MT9M032_CHIP_VERSION_VALUE) अणु
		dev_err(&client->dev, "MT9M032 not detected, wrong version "
			"0x%04x\n", chip_version);
		ret = -ENODEV;
		जाओ error_sensor;
	पूर्ण

	dev_info(&client->dev, "MT9M032 detected at address 0x%02x\n",
		 client->addr);

	sensor->frame_पूर्णांकerval.numerator = 1;
	sensor->frame_पूर्णांकerval.denominator = 30;

	sensor->crop.left = MT9M032_COLUMN_START_DEF;
	sensor->crop.top = MT9M032_ROW_START_DEF;
	sensor->crop.width = MT9M032_COLUMN_SIZE_DEF;
	sensor->crop.height = MT9M032_ROW_SIZE_DEF;

	sensor->क्रमmat.width = sensor->crop.width;
	sensor->क्रमmat.height = sensor->crop.height;
	sensor->क्रमmat.code = MEDIA_BUS_FMT_Y8_1X8;
	sensor->क्रमmat.field = V4L2_FIELD_NONE;
	sensor->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;

	v4l2_ctrl_handler_init(&sensor->ctrls, 5);

	v4l2_ctrl_new_std(&sensor->ctrls, &mt9m032_ctrl_ops,
			  V4L2_CID_GAIN, 0, 127, 1, 64);

	sensor->hflip = v4l2_ctrl_new_std(&sensor->ctrls,
					  &mt9m032_ctrl_ops,
					  V4L2_CID_HFLIP, 0, 1, 1, 0);
	sensor->vflip = v4l2_ctrl_new_std(&sensor->ctrls,
					  &mt9m032_ctrl_ops,
					  V4L2_CID_VFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&sensor->ctrls, &mt9m032_ctrl_ops,
			  V4L2_CID_EXPOSURE, MT9M032_SHUTTER_WIDTH_MIN,
			  MT9M032_SHUTTER_WIDTH_MAX, 1,
			  MT9M032_SHUTTER_WIDTH_DEF);
	v4l2_ctrl_new_std(&sensor->ctrls, &mt9m032_ctrl_ops,
			  V4L2_CID_PIXEL_RATE, pdata->pix_घड़ी,
			  pdata->pix_घड़ी, 1, pdata->pix_घड़ी);

	अगर (sensor->ctrls.error) अणु
		ret = sensor->ctrls.error;
		dev_err(&client->dev, "control initialization error %d\n", ret);
		जाओ error_ctrl;
	पूर्ण

	v4l2_ctrl_cluster(2, &sensor->hflip);

	sensor->subdev.ctrl_handler = &sensor->ctrls;
	sensor->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	sensor->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&sensor->subdev.entity, 1, &sensor->pad);
	अगर (ret < 0)
		जाओ error_ctrl;

	ret = mt9m032_ग_लिखो(client, MT9M032_RESET, 1);	/* reset on */
	अगर (ret < 0)
		जाओ error_entity;
	ret = mt9m032_ग_लिखो(client, MT9M032_RESET, 0);	/* reset off */
	अगर (ret < 0)
		जाओ error_entity;

	ret = mt9m032_setup_pll(sensor);
	अगर (ret < 0)
		जाओ error_entity;
	usleep_range(10000, 11000);

	ret = v4l2_ctrl_handler_setup(&sensor->ctrls);
	अगर (ret < 0)
		जाओ error_entity;

	/* SIZE */
	ret = mt9m032_update_geom_timing(sensor);
	अगर (ret < 0)
		जाओ error_entity;

	ret = mt9m032_ग_लिखो(client, 0x41, 0x0000);	/* reserved !!! */
	अगर (ret < 0)
		जाओ error_entity;
	ret = mt9m032_ग_लिखो(client, 0x42, 0x0003);	/* reserved !!! */
	अगर (ret < 0)
		जाओ error_entity;
	ret = mt9m032_ग_लिखो(client, 0x43, 0x0003);	/* reserved !!! */
	अगर (ret < 0)
		जाओ error_entity;
	ret = mt9m032_ग_लिखो(client, 0x7f, 0x0000);	/* reserved !!! */
	अगर (ret < 0)
		जाओ error_entity;
	अगर (sensor->pdata->invert_pixघड़ी) अणु
		ret = mt9m032_ग_लिखो(client, MT9M032_PIX_CLK_CTRL,
				    MT9M032_PIX_CLK_CTRL_INV_PIXCLK);
		अगर (ret < 0)
			जाओ error_entity;
	पूर्ण

	ret = mt9m032_ग_लिखो(client, MT9M032_RESTART, 1); /* Restart on */
	अगर (ret < 0)
		जाओ error_entity;
	msleep(100);
	ret = mt9m032_ग_लिखो(client, MT9M032_RESTART, 0); /* Restart off */
	अगर (ret < 0)
		जाओ error_entity;
	msleep(100);
	ret = update_क्रमmatter2(sensor, false);
	अगर (ret < 0)
		जाओ error_entity;

	वापस ret;

error_entity:
	media_entity_cleanup(&sensor->subdev.entity);
error_ctrl:
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls);
error_sensor:
	mutex_destroy(&sensor->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m032_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा mt9m032 *sensor = to_mt9m032(subdev);

	v4l2_device_unरेजिस्टर_subdev(subdev);
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls);
	media_entity_cleanup(&subdev->entity);
	mutex_destroy(&sensor->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mt9m032_id_table[] = अणु
	अणु MT9M032_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, mt9m032_id_table);

अटल काष्ठा i2c_driver mt9m032_i2c_driver = अणु
	.driver = अणु
		.name = MT9M032_NAME,
	पूर्ण,
	.probe = mt9m032_probe,
	.हटाओ = mt9m032_हटाओ,
	.id_table = mt9m032_id_table,
पूर्ण;

module_i2c_driver(mt9m032_i2c_driver);

MODULE_AUTHOR("Martin Hostettler <martin@neutronstar.dyndns.org>");
MODULE_DESCRIPTION("MT9M032 camera sensor driver");
MODULE_LICENSE("GPL v2");

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GS1662 device registration.
 *
 * Copyright (C) 2015-2016 Nexvision
 * Author: Charles-Antoine Couret <अक्षरles-antoine.couret@nexvision.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <linux/v4l2-dv-timings.h>

#घोषणा REG_STATUS			0x04
#घोषणा REG_FORCE_FMT			0x06
#घोषणा REG_LINES_PER_FRAME		0x12
#घोषणा REG_WORDS_PER_LINE		0x13
#घोषणा REG_WORDS_PER_ACT_LINE		0x14
#घोषणा REG_ACT_LINES_PER_FRAME	0x15

#घोषणा MASK_H_LOCK			0x001
#घोषणा MASK_V_LOCK			0x002
#घोषणा MASK_STD_LOCK			0x004
#घोषणा MASK_FORCE_STD			0x020
#घोषणा MASK_STD_STATUS		0x3E0

#घोषणा GS_WIDTH_MIN			720
#घोषणा GS_WIDTH_MAX			2048
#घोषणा GS_HEIGHT_MIN			487
#घोषणा GS_HEIGHT_MAX			1080
#घोषणा GS_PIXELCLOCK_MIN		10519200
#घोषणा GS_PIXELCLOCK_MAX		74250000

काष्ठा gs अणु
	काष्ठा spi_device *pdev;
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_dv_timings current_timings;
	पूर्णांक enabled;
पूर्ण;

काष्ठा gs_reg_fmt अणु
	u16 reg_value;
	काष्ठा v4l2_dv_timings क्रमmat;
पूर्ण;

काष्ठा gs_reg_fmt_custom अणु
	u16 reg_value;
	__u32 width;
	__u32 height;
	__u64 pixelघड़ी;
	__u32 पूर्णांकerlaced;
पूर्ण;

अटल स्थिर काष्ठा spi_device_id gs_id[] = अणु
	अणु "gs1662", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, gs_id);

अटल स्थिर काष्ठा v4l2_dv_timings fmt_cap[] = अणु
	V4L2_DV_BT_SDI_720X487I60,
	V4L2_DV_BT_CEA_720X576P50,
	V4L2_DV_BT_CEA_1280X720P24,
	V4L2_DV_BT_CEA_1280X720P25,
	V4L2_DV_BT_CEA_1280X720P30,
	V4L2_DV_BT_CEA_1280X720P50,
	V4L2_DV_BT_CEA_1280X720P60,
	V4L2_DV_BT_CEA_1920X1080P24,
	V4L2_DV_BT_CEA_1920X1080P25,
	V4L2_DV_BT_CEA_1920X1080P30,
	V4L2_DV_BT_CEA_1920X1080I50,
	V4L2_DV_BT_CEA_1920X1080I60,
पूर्ण;

अटल स्थिर काष्ठा gs_reg_fmt reg_fmt[] = अणु
	अणु 0x00, V4L2_DV_BT_CEA_1280X720P60 पूर्ण,
	अणु 0x01, V4L2_DV_BT_CEA_1280X720P60 पूर्ण,
	अणु 0x02, V4L2_DV_BT_CEA_1280X720P30 पूर्ण,
	अणु 0x03, V4L2_DV_BT_CEA_1280X720P30 पूर्ण,
	अणु 0x04, V4L2_DV_BT_CEA_1280X720P50 पूर्ण,
	अणु 0x05, V4L2_DV_BT_CEA_1280X720P50 पूर्ण,
	अणु 0x06, V4L2_DV_BT_CEA_1280X720P25 पूर्ण,
	अणु 0x07, V4L2_DV_BT_CEA_1280X720P25 पूर्ण,
	अणु 0x08, V4L2_DV_BT_CEA_1280X720P24 पूर्ण,
	अणु 0x09, V4L2_DV_BT_CEA_1280X720P24 पूर्ण,
	अणु 0x0A, V4L2_DV_BT_CEA_1920X1080I60 पूर्ण,
	अणु 0x0B, V4L2_DV_BT_CEA_1920X1080P30 पूर्ण,

	/* Default value: keep this field beक्रमe 0xC */
	अणु 0x14, V4L2_DV_BT_CEA_1920X1080I50 पूर्ण,
	अणु 0x0C, V4L2_DV_BT_CEA_1920X1080I50 पूर्ण,
	अणु 0x0D, V4L2_DV_BT_CEA_1920X1080P25 पूर्ण,
	अणु 0x0E, V4L2_DV_BT_CEA_1920X1080P25 पूर्ण,
	अणु 0x10, V4L2_DV_BT_CEA_1920X1080P24 पूर्ण,
	अणु 0x12, V4L2_DV_BT_CEA_1920X1080P24 पूर्ण,
	अणु 0x16, V4L2_DV_BT_SDI_720X487I60 पूर्ण,
	अणु 0x19, V4L2_DV_BT_SDI_720X487I60 पूर्ण,
	अणु 0x18, V4L2_DV_BT_CEA_720X576P50 पूर्ण,
	अणु 0x1A, V4L2_DV_BT_CEA_720X576P50 पूर्ण,

	/* Implement following timings beक्रमe enable it.
	 * Because of we करोn't have access to these theoretical timings yet.
	 * Workaround: use functions to get and set रेजिस्टरs क्रम these क्रमmats.
	 */
#अगर 0
	अणु 0x0F, V4L2_DV_BT_XXX_1920X1080I25 पूर्ण, /* SMPTE 274M */
	अणु 0x11, V4L2_DV_BT_XXX_1920X1080I24 पूर्ण, /* SMPTE 274M */
	अणु 0x13, V4L2_DV_BT_XXX_1920X1080I25 पूर्ण, /* SMPTE 274M */
	अणु 0x15, V4L2_DV_BT_XXX_1920X1035I60 पूर्ण, /* SMPTE 260M */
	अणु 0x17, V4L2_DV_BT_SDI_720X507I60 पूर्ण, /* SMPTE 125M */
	अणु 0x1B, V4L2_DV_BT_SDI_720X507I60 पूर्ण, /* SMPTE 125M */
	अणु 0x1C, V4L2_DV_BT_XXX_2048X1080P25 पूर्ण, /* SMPTE 428.1M */
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_dv_timings_cap gs_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(GS_WIDTH_MIN, GS_WIDTH_MAX, GS_HEIGHT_MIN,
			     GS_HEIGHT_MAX, GS_PIXELCLOCK_MIN,
			     GS_PIXELCLOCK_MAX,
			     V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_SDI,
			     V4L2_DV_BT_CAP_PROGRESSIVE
			     | V4L2_DV_BT_CAP_INTERLACED)
पूर्ण;

अटल पूर्णांक gs_पढ़ो_रेजिस्टर(काष्ठा spi_device *spi, u16 addr, u16 *value)
अणु
	पूर्णांक ret;
	u16 buf_addr = (0x8000 | (0x0FFF & addr));
	u16 buf_value = 0;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx[] = अणु
		अणु
			.tx_buf = &buf_addr,
			.len = 2,
			.delay = अणु
				.value = 1,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,
		पूर्ण, अणु
			.rx_buf = &buf_value,
			.len = 2,
			.delay = अणु
				.value = 1,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,
		पूर्ण,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&tx[0], &msg);
	spi_message_add_tail(&tx[1], &msg);
	ret = spi_sync(spi, &msg);

	*value = buf_value;

	वापस ret;
पूर्ण

अटल पूर्णांक gs_ग_लिखो_रेजिस्टर(काष्ठा spi_device *spi, u16 addr, u16 value)
अणु
	पूर्णांक ret;
	u16 buf_addr = addr;
	u16 buf_value = value;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx[] = अणु
		अणु
			.tx_buf = &buf_addr,
			.len = 2,
			.delay = अणु
				.value = 1,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,
		पूर्ण, अणु
			.tx_buf = &buf_value,
			.len = 2,
			.delay = अणु
				.value = 1,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,
		पूर्ण,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&tx[0], &msg);
	spi_message_add_tail(&tx[1], &msg);
	ret = spi_sync(spi, &msg);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक gs_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
		  काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा spi_device *spi = v4l2_get_subdevdata(sd);
	u16 val;
	पूर्णांक ret;

	ret = gs_पढ़ो_रेजिस्टर(spi, reg->reg & 0xFFFF, &val);
	reg->val = val;
	reg->size = 2;
	वापस ret;
पूर्ण

अटल पूर्णांक gs_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
		  स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा spi_device *spi = v4l2_get_subdevdata(sd);

	वापस gs_ग_लिखो_रेजिस्टर(spi, reg->reg & 0xFFFF, reg->val & 0xFFFF);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक gs_status_क्रमmat(u16 status, काष्ठा v4l2_dv_timings *timings)
अणु
	पूर्णांक std = (status & MASK_STD_STATUS) >> 5;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reg_fmt); i++) अणु
		अगर (reg_fmt[i].reg_value == std) अणु
			*timings = reg_fmt[i].क्रमmat;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -दुस्फल;
पूर्ण

अटल u16 get_रेजिस्टर_timings(काष्ठा v4l2_dv_timings *timings)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reg_fmt); i++) अणु
		अगर (v4l2_match_dv_timings(timings, &reg_fmt[i].क्रमmat, 0,
					  false))
			वापस reg_fmt[i].reg_value | MASK_FORCE_STD;
	पूर्ण

	वापस 0x0;
पूर्ण

अटल अंतरभूत काष्ठा gs *to_gs(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा gs, sd);
पूर्ण

अटल पूर्णांक gs_s_dv_timings(काष्ठा v4l2_subdev *sd,
		    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा gs *gs = to_gs(sd);
	पूर्णांक reg_value;

	reg_value = get_रेजिस्टर_timings(timings);
	अगर (reg_value == 0x0)
		वापस -EINVAL;

	gs->current_timings = *timings;
	वापस 0;
पूर्ण

अटल पूर्णांक gs_g_dv_timings(काष्ठा v4l2_subdev *sd,
		    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा gs *gs = to_gs(sd);

	*timings = gs->current_timings;
	वापस 0;
पूर्ण

अटल पूर्णांक gs_query_dv_timings(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा gs *gs = to_gs(sd);
	काष्ठा v4l2_dv_timings fmt;
	u16 reg_value, i;
	पूर्णांक ret;

	अगर (gs->enabled)
		वापस -EBUSY;

	/*
	 * Check अगर the component detect a line, a frame or something अन्यथा
	 * which looks like a video संकेत activity.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		gs_पढ़ो_रेजिस्टर(gs->pdev, REG_LINES_PER_FRAME + i, &reg_value);
		अगर (reg_value)
			अवरोध;
	पूर्ण

	/* If no रेजिस्टर reports a video संकेत */
	अगर (i >= 4)
		वापस -ENOLINK;

	gs_पढ़ो_रेजिस्टर(gs->pdev, REG_STATUS, &reg_value);
	अगर (!(reg_value & MASK_H_LOCK) || !(reg_value & MASK_V_LOCK))
		वापस -ENOLCK;
	अगर (!(reg_value & MASK_STD_LOCK))
		वापस -दुस्फल;

	ret = gs_status_क्रमmat(reg_value, &fmt);

	अगर (ret < 0)
		वापस ret;

	*timings = fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक gs_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	अगर (timings->index >= ARRAY_SIZE(fmt_cap))
		वापस -EINVAL;

	अगर (timings->pad != 0)
		वापस -EINVAL;

	timings->timings = fmt_cap[timings->index];
	वापस 0;
पूर्ण

अटल पूर्णांक gs_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा gs *gs = to_gs(sd);
	पूर्णांक reg_value;

	अगर (gs->enabled == enable)
		वापस 0;

	gs->enabled = enable;

	अगर (enable) अणु
		/* To क्रमce the specअगरic क्रमmat */
		reg_value = get_रेजिस्टर_timings(&gs->current_timings);
		वापस gs_ग_लिखो_रेजिस्टर(gs->pdev, REG_FORCE_FMT, reg_value);
	पूर्ण

	/* To renable स्वतः-detection mode */
	वापस gs_ग_लिखो_रेजिस्टर(gs->pdev, REG_FORCE_FMT, 0x0);
पूर्ण

अटल पूर्णांक gs_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	काष्ठा gs *gs = to_gs(sd);
	u16 reg_value, i;
	पूर्णांक ret;

	/*
	 * Check अगर the component detect a line, a frame or something अन्यथा
	 * which looks like a video संकेत activity.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		ret = gs_पढ़ो_रेजिस्टर(gs->pdev,
				       REG_LINES_PER_FRAME + i, &reg_value);
		अगर (reg_value)
			अवरोध;
		अगर (ret) अणु
			*status = V4L2_IN_ST_NO_POWER;
			वापस ret;
		पूर्ण
	पूर्ण

	/* If no रेजिस्टर reports a video संकेत */
	अगर (i >= 4)
		*status |= V4L2_IN_ST_NO_SIGNAL;

	ret = gs_पढ़ो_रेजिस्टर(gs->pdev, REG_STATUS, &reg_value);
	अगर (!(reg_value & MASK_H_LOCK))
		*status |=  V4L2_IN_ST_NO_H_LOCK;
	अगर (!(reg_value & MASK_V_LOCK))
		*status |=  V4L2_IN_ST_NO_V_LOCK;
	अगर (!(reg_value & MASK_STD_LOCK))
		*status |=  V4L2_IN_ST_NO_STD_LOCK;

	वापस ret;
पूर्ण

अटल पूर्णांक gs_dv_timings_cap(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_dv_timings_cap *cap)
अणु
	अगर (cap->pad != 0)
		वापस -EINVAL;

	*cap = gs_timings_cap;
	वापस 0;
पूर्ण

/* V4L2 core operation handlers */
अटल स्थिर काष्ठा v4l2_subdev_core_ops gs_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = gs_g_रेजिस्टर,
	.s_रेजिस्टर = gs_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops gs_video_ops = अणु
	.s_dv_timings = gs_s_dv_timings,
	.g_dv_timings = gs_g_dv_timings,
	.s_stream = gs_s_stream,
	.g_input_status = gs_g_input_status,
	.query_dv_timings = gs_query_dv_timings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops gs_pad_ops = अणु
	.क्रमागत_dv_timings = gs_क्रमागत_dv_timings,
	.dv_timings_cap = gs_dv_timings_cap,
पूर्ण;

/* V4L2 top level operation handlers */
अटल स्थिर काष्ठा v4l2_subdev_ops gs_ops = अणु
	.core = &gs_core_ops,
	.video = &gs_video_ops,
	.pad = &gs_pad_ops,
पूर्ण;

अटल पूर्णांक gs_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा gs *gs;
	काष्ठा v4l2_subdev *sd;

	gs = devm_kzalloc(&spi->dev, माप(काष्ठा gs), GFP_KERNEL);
	अगर (!gs)
		वापस -ENOMEM;

	gs->pdev = spi;
	sd = &gs->sd;

	spi->mode = SPI_MODE_0;
	spi->irq = -1;
	spi->max_speed_hz = 10000000;
	spi->bits_per_word = 16;
	ret = spi_setup(spi);
	v4l2_spi_subdev_init(sd, spi, &gs_ops);

	gs->current_timings = reg_fmt[0].क्रमmat;
	gs->enabled = 0;

	/* Set H_CONFIG to SMPTE timings */
	gs_ग_लिखो_रेजिस्टर(spi, 0x0, 0x300);

	वापस ret;
पूर्ण

अटल पूर्णांक gs_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा v4l2_subdev *sd = spi_get_drvdata(spi);

	v4l2_device_unरेजिस्टर_subdev(sd);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver gs_driver = अणु
	.driver = अणु
		.name		= "gs1662",
	पूर्ण,

	.probe		= gs_probe,
	.हटाओ		= gs_हटाओ,
	.id_table	= gs_id,
पूर्ण;

module_spi_driver(gs_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Charles-Antoine Couret <charles-antoine.couret@nexvision.fr>");
MODULE_DESCRIPTION("Gennum GS1662 HD/SD-SDI Serializer driver");

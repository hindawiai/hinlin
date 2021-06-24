<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम SiliconFile NOON010PC30 CIF (1/11") Image Sensor with ISP
 *
 * Copyright (C) 2010 - 2011 Samsung Electronics Co., Ltd.
 * Contact: Sylwester Nawrocki, <s.nawrocki@samsung.com>
 *
 * Initial रेजिस्टर configuration based on a driver authored by
 * HeungJun Kim <riverful.kim@samsung.com>.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/i2c/noon010pc30.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/module.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/v4l2-subdev.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable module debug trace. Set to 1 to enable.");

#घोषणा MODULE_NAME		"NOON010PC30"

/*
 * Register offsets within a page
 * b15..b8 - page id, b7..b0 - रेजिस्टर address
 */
#घोषणा POWER_CTRL_REG		0x0001
#घोषणा PAGEMODE_REG		0x03
#घोषणा DEVICE_ID_REG		0x0004
#घोषणा NOON010PC30_ID		0x86
#घोषणा VDO_CTL_REG(n)		(0x0010 + (n))
#घोषणा SYNC_CTL_REG		0x0012
/* Winकरोw size and position */
#घोषणा WIN_ROWH_REG		0x0013
#घोषणा WIN_ROWL_REG		0x0014
#घोषणा WIN_COLH_REG		0x0015
#घोषणा WIN_COLL_REG		0x0016
#घोषणा WIN_HEIGHTH_REG		0x0017
#घोषणा WIN_HEIGHTL_REG		0x0018
#घोषणा WIN_WIDTHH_REG		0x0019
#घोषणा WIN_WIDTHL_REG		0x001A
#घोषणा HBLANKH_REG		0x001B
#घोषणा HBLANKL_REG		0x001C
#घोषणा VSYNCH_REG		0x001D
#घोषणा VSYNCL_REG		0x001E
/* VSYNC control */
#घोषणा VS_CTL_REG(n)		(0x00A1 + (n))
/* page 1 */
#घोषणा ISP_CTL_REG(n)		(0x0110 + (n))
#घोषणा YOFS_REG		0x0119
#घोषणा DARK_YOFS_REG		0x011A
#घोषणा SAT_CTL_REG		0x0120
#घोषणा BSAT_REG		0x0121
#घोषणा RSAT_REG		0x0122
/* Color correction */
#घोषणा CMC_CTL_REG		0x0130
#घोषणा CMC_OFSGH_REG		0x0133
#घोषणा CMC_OFSGL_REG		0x0135
#घोषणा CMC_SIGN_REG		0x0136
#घोषणा CMC_GOFS_REG		0x0137
#घोषणा CMC_COEF_REG(n)		(0x0138 + (n))
#घोषणा CMC_OFS_REG(n)		(0x0141 + (n))
/* Gamma correction */
#घोषणा GMA_CTL_REG		0x0160
#घोषणा GMA_COEF_REG(n)		(0x0161 + (n))
/* Lens Shading */
#घोषणा LENS_CTRL_REG		0x01D0
#घोषणा LENS_XCEN_REG		0x01D1
#घोषणा LENS_YCEN_REG		0x01D2
#घोषणा LENS_RC_REG		0x01D3
#घोषणा LENS_GC_REG		0x01D4
#घोषणा LENS_BC_REG		0x01D5
#घोषणा L_AGON_REG		0x01D6
#घोषणा L_AGOFF_REG		0x01D7
/* Page 3 - Auto Exposure */
#घोषणा AE_CTL_REG(n)		(0x0310 + (n))
#घोषणा AE_CTL9_REG		0x032C
#घोषणा AE_CTL10_REG		0x032D
#घोषणा AE_YLVL_REG		0x031C
#घोषणा AE_YTH_REG(n)		(0x031D + (n))
#घोषणा AE_WGT_REG		0x0326
#घोषणा EXP_TIMEH_REG		0x0333
#घोषणा EXP_TIMEM_REG		0x0334
#घोषणा EXP_TIMEL_REG		0x0335
#घोषणा EXP_MMINH_REG		0x0336
#घोषणा EXP_MMINL_REG		0x0337
#घोषणा EXP_MMAXH_REG		0x0338
#घोषणा EXP_MMAXM_REG		0x0339
#घोषणा EXP_MMAXL_REG		0x033A
/* Page 4 - Auto White Balance */
#घोषणा AWB_CTL_REG(n)		(0x0410 + (n))
#घोषणा AWB_ENABE		0x80
#घोषणा AWB_WGHT_REG		0x0419
#घोषणा BGAIN_PAR_REG(n)	(0x044F + (n))
/* Manual white balance, when AWB_CTL2[0]=1 */
#घोषणा MWB_RGAIN_REG		0x0466
#घोषणा MWB_BGAIN_REG		0x0467

/* The token to mark an array end */
#घोषणा REG_TERM		0xFFFF

काष्ठा noon010_क्रमmat अणु
	u32 code;
	क्रमागत v4l2_colorspace colorspace;
	u16 ispctl1_reg;
पूर्ण;

काष्ठा noon010_frmsize अणु
	u16 width;
	u16 height;
	पूर्णांक vid_ctl1;
पूर्ण;

अटल स्थिर अक्षर * स्थिर noon010_supply_name[] = अणु
	"vdd_core", "vddio", "vdda"
पूर्ण;

#घोषणा NOON010_NUM_SUPPLIES ARRAY_SIZE(noon010_supply_name)

काष्ठा noon010_info अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा regulator_bulk_data supply[NOON010_NUM_SUPPLIES];
	u32 gpio_nreset;
	u32 gpio_nstby;

	/* Protects the काष्ठा members below */
	काष्ठा mutex lock;

	स्थिर काष्ठा noon010_क्रमmat *curr_fmt;
	स्थिर काष्ठा noon010_frmsize *curr_win;
	अचिन्हित पूर्णांक apply_new_cfg:1;
	अचिन्हित पूर्णांक streaming:1;
	अचिन्हित पूर्णांक hflip:1;
	अचिन्हित पूर्णांक vflip:1;
	अचिन्हित पूर्णांक घातer:1;
	u8 i2c_reg_page;
पूर्ण;

काष्ठा i2c_regval अणु
	u16 addr;
	u16 val;
पूर्ण;

/* Supported resolutions. */
अटल स्थिर काष्ठा noon010_frmsize noon010_sizes[] = अणु
	अणु
		.width		= 352,
		.height		= 288,
		.vid_ctl1	= 0,
	पूर्ण, अणु
		.width		= 176,
		.height		= 144,
		.vid_ctl1	= 0x10,
	पूर्ण, अणु
		.width		= 88,
		.height		= 72,
		.vid_ctl1	= 0x20,
	पूर्ण,
पूर्ण;

/* Supported pixel क्रमmats. */
अटल स्थिर काष्ठा noon010_क्रमmat noon010_क्रमmats[] = अणु
	अणु
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0x03,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0x02,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0x01,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_RGB565_2X8_BE,
		.colorspace	= V4L2_COLORSPACE_JPEG,
		.ispctl1_reg	= 0x40,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_regval noon010_base_regs[] = अणु
	अणु WIN_COLL_REG,		0x06 पूर्ण,	अणु HBLANKL_REG,		0x7C पूर्ण,
	/* Color corection and saturation */
	अणु ISP_CTL_REG(0),	0x30 पूर्ण, अणु ISP_CTL_REG(2),	0x30 पूर्ण,
	अणु YOFS_REG,		0x80 पूर्ण, अणु DARK_YOFS_REG,	0x04 पूर्ण,
	अणु SAT_CTL_REG,		0x1F पूर्ण, अणु BSAT_REG,		0x90 पूर्ण,
	अणु CMC_CTL_REG,		0x0F पूर्ण, अणु CMC_OFSGH_REG,	0x3C पूर्ण,
	अणु CMC_OFSGL_REG,	0x2C पूर्ण, अणु CMC_SIGN_REG,		0x3F पूर्ण,
	अणु CMC_COEF_REG(0),	0x79 पूर्ण, अणु CMC_OFS_REG(0),	0x00 पूर्ण,
	अणु CMC_COEF_REG(1),	0x39 पूर्ण, अणु CMC_OFS_REG(1),	0x00 पूर्ण,
	अणु CMC_COEF_REG(2),	0x00 पूर्ण, अणु CMC_OFS_REG(2),	0x00 पूर्ण,
	अणु CMC_COEF_REG(3),	0x11 पूर्ण, अणु CMC_OFS_REG(3),	0x8B पूर्ण,
	अणु CMC_COEF_REG(4),	0x65 पूर्ण, अणु CMC_OFS_REG(4),	0x07 पूर्ण,
	अणु CMC_COEF_REG(5),	0x14 पूर्ण, अणु CMC_OFS_REG(5),	0x04 पूर्ण,
	अणु CMC_COEF_REG(6),	0x01 पूर्ण, अणु CMC_OFS_REG(6),	0x9C पूर्ण,
	अणु CMC_COEF_REG(7),	0x33 पूर्ण, अणु CMC_OFS_REG(7),	0x89 पूर्ण,
	अणु CMC_COEF_REG(8),	0x74 पूर्ण, अणु CMC_OFS_REG(8),	0x25 पूर्ण,
	/* Automatic white balance */
	अणु AWB_CTL_REG(0),	0x78 पूर्ण, अणु AWB_CTL_REG(1),	0x2E पूर्ण,
	अणु AWB_CTL_REG(2),	0x20 पूर्ण, अणु AWB_CTL_REG(3),	0x85 पूर्ण,
	/* Auto exposure */
	अणु AE_CTL_REG(0),	0xDC पूर्ण, अणु AE_CTL_REG(1),	0x81 पूर्ण,
	अणु AE_CTL_REG(2),	0x30 पूर्ण, अणु AE_CTL_REG(3),	0xA5 पूर्ण,
	अणु AE_CTL_REG(4),	0x40 पूर्ण, अणु AE_CTL_REG(5),	0x51 पूर्ण,
	अणु AE_CTL_REG(6),	0x33 पूर्ण, अणु AE_CTL_REG(7),	0x7E पूर्ण,
	अणु AE_CTL9_REG,		0x00 पूर्ण, अणु AE_CTL10_REG,		0x02 पूर्ण,
	अणु AE_YLVL_REG,		0x44 पूर्ण,	अणु AE_YTH_REG(0),	0x34 पूर्ण,
	अणु AE_YTH_REG(1),	0x30 पूर्ण,	अणु AE_WGT_REG,		0xD5 पूर्ण,
	/* Lens shading compensation */
	अणु LENS_CTRL_REG,	0x01 पूर्ण, अणु LENS_XCEN_REG,	0x80 पूर्ण,
	अणु LENS_YCEN_REG,	0x70 पूर्ण, अणु LENS_RC_REG,		0x53 पूर्ण,
	अणु LENS_GC_REG,		0x40 पूर्ण, अणु LENS_BC_REG,		0x3E पूर्ण,
	अणु REG_TERM,		0 पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा noon010_info *to_noon010(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा noon010_info, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा noon010_info, hdl)->sd;
पूर्ण

अटल अंतरभूत पूर्णांक set_i2c_page(काष्ठा noon010_info *info,
			       काष्ठा i2c_client *client, अचिन्हित पूर्णांक reg)
अणु
	u32 page = reg >> 8 & 0xFF;
	पूर्णांक ret = 0;

	अगर (info->i2c_reg_page != page && (reg & 0xFF) != 0x03) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, PAGEMODE_REG, page);
		अगर (!ret)
			info->i2c_reg_page = page;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cam_i2c_पढ़ो(काष्ठा v4l2_subdev *sd, u32 reg_addr)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा noon010_info *info = to_noon010(sd);
	पूर्णांक ret = set_i2c_page(info, client, reg_addr);

	अगर (ret)
		वापस ret;
	वापस i2c_smbus_पढ़ो_byte_data(client, reg_addr & 0xFF);
पूर्ण

अटल पूर्णांक cam_i2c_ग_लिखो(काष्ठा v4l2_subdev *sd, u32 reg_addr, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा noon010_info *info = to_noon010(sd);
	पूर्णांक ret = set_i2c_page(info, client, reg_addr);

	अगर (ret)
		वापस ret;
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg_addr & 0xFF, val);
पूर्ण

अटल अंतरभूत पूर्णांक noon010_bulk_ग_लिखो_reg(काष्ठा v4l2_subdev *sd,
					 स्थिर काष्ठा i2c_regval *msg)
अणु
	जबतक (msg->addr != REG_TERM) अणु
		पूर्णांक ret = cam_i2c_ग_लिखो(sd, msg->addr, msg->val);

		अगर (ret)
			वापस ret;
		msg++;
	पूर्ण
	वापस 0;
पूर्ण

/* Device reset and sleep mode control */
अटल पूर्णांक noon010_घातer_ctrl(काष्ठा v4l2_subdev *sd, bool reset, bool sleep)
अणु
	काष्ठा noon010_info *info = to_noon010(sd);
	u8 reg = sleep ? 0xF1 : 0xF0;
	पूर्णांक ret = 0;

	अगर (reset) अणु
		ret = cam_i2c_ग_लिखो(sd, POWER_CTRL_REG, reg | 0x02);
		udelay(20);
	पूर्ण
	अगर (!ret) अणु
		ret = cam_i2c_ग_लिखो(sd, POWER_CTRL_REG, reg);
		अगर (reset && !ret)
			info->i2c_reg_page = -1;
	पूर्ण
	वापस ret;
पूर्ण

/* Automatic white balance control */
अटल पूर्णांक noon010_enable_स्वतःwhitebalance(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	पूर्णांक ret;

	ret = cam_i2c_ग_लिखो(sd, AWB_CTL_REG(1), on ? 0x2E : 0x2F);
	अगर (!ret)
		ret = cam_i2c_ग_लिखो(sd, AWB_CTL_REG(0), on ? 0xFB : 0x7B);
	वापस ret;
पूर्ण

/* Called with काष्ठा noon010_info.lock mutex held */
अटल पूर्णांक noon010_set_flip(काष्ठा v4l2_subdev *sd, पूर्णांक hflip, पूर्णांक vflip)
अणु
	काष्ठा noon010_info *info = to_noon010(sd);
	पूर्णांक reg, ret;

	reg = cam_i2c_पढ़ो(sd, VDO_CTL_REG(1));
	अगर (reg < 0)
		वापस reg;

	reg &= 0x7C;
	अगर (hflip)
		reg |= 0x01;
	अगर (vflip)
		reg |= 0x02;

	ret = cam_i2c_ग_लिखो(sd, VDO_CTL_REG(1), reg | 0x80);
	अगर (!ret) अणु
		info->hflip = hflip;
		info->vflip = vflip;
	पूर्ण
	वापस ret;
पूर्ण

/* Configure resolution and color क्रमmat */
अटल पूर्णांक noon010_set_params(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा noon010_info *info = to_noon010(sd);

	पूर्णांक ret = cam_i2c_ग_लिखो(sd, VDO_CTL_REG(0),
				info->curr_win->vid_ctl1);
	अगर (ret)
		वापस ret;
	वापस cam_i2c_ग_लिखो(sd, ISP_CTL_REG(0),
			     info->curr_fmt->ispctl1_reg);
पूर्ण

/* Find nearest matching image pixel size. */
अटल पूर्णांक noon010_try_frame_size(काष्ठा v4l2_mbus_framefmt *mf,
				  स्थिर काष्ठा noon010_frmsize **size)
अणु
	अचिन्हित पूर्णांक min_err = ~0;
	पूर्णांक i = ARRAY_SIZE(noon010_sizes);
	स्थिर काष्ठा noon010_frmsize *fsize = &noon010_sizes[0],
		*match = शून्य;

	जबतक (i--) अणु
		पूर्णांक err = असल(fsize->width - mf->width)
				+ असल(fsize->height - mf->height);

		अगर (err < min_err) अणु
			min_err = err;
			match = fsize;
		पूर्ण
		fsize++;
	पूर्ण
	अगर (match) अणु
		mf->width  = match->width;
		mf->height = match->height;
		अगर (size)
			*size = match;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Called with info.lock mutex held */
अटल पूर्णांक घातer_enable(काष्ठा noon010_info *info)
अणु
	पूर्णांक ret;

	अगर (info->घातer) अणु
		v4l2_info(&info->sd, "%s: sensor is already on\n", __func__);
		वापस 0;
	पूर्ण

	अगर (gpio_is_valid(info->gpio_nstby))
		gpio_set_value(info->gpio_nstby, 0);

	अगर (gpio_is_valid(info->gpio_nreset))
		gpio_set_value(info->gpio_nreset, 0);

	ret = regulator_bulk_enable(NOON010_NUM_SUPPLIES, info->supply);
	अगर (ret)
		वापस ret;

	अगर (gpio_is_valid(info->gpio_nreset)) अणु
		msleep(50);
		gpio_set_value(info->gpio_nreset, 1);
	पूर्ण
	अगर (gpio_is_valid(info->gpio_nstby)) अणु
		udelay(1000);
		gpio_set_value(info->gpio_nstby, 1);
	पूर्ण
	अगर (gpio_is_valid(info->gpio_nreset)) अणु
		udelay(1000);
		gpio_set_value(info->gpio_nreset, 0);
		msleep(100);
		gpio_set_value(info->gpio_nreset, 1);
		msleep(20);
	पूर्ण
	info->घातer = 1;

	v4l2_dbg(1, debug, &info->sd,  "%s: sensor is on\n", __func__);
	वापस 0;
पूर्ण

/* Called with info.lock mutex held */
अटल पूर्णांक घातer_disable(काष्ठा noon010_info *info)
अणु
	पूर्णांक ret;

	अगर (!info->घातer) अणु
		v4l2_info(&info->sd, "%s: sensor is already off\n", __func__);
		वापस 0;
	पूर्ण

	ret = regulator_bulk_disable(NOON010_NUM_SUPPLIES, info->supply);
	अगर (ret)
		वापस ret;

	अगर (gpio_is_valid(info->gpio_nstby))
		gpio_set_value(info->gpio_nstby, 0);

	अगर (gpio_is_valid(info->gpio_nreset))
		gpio_set_value(info->gpio_nreset, 0);

	info->घातer = 0;

	v4l2_dbg(1, debug, &info->sd,  "%s: sensor is off\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक noon010_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा noon010_info *info = to_noon010(sd);
	पूर्णांक ret = 0;

	v4l2_dbg(1, debug, sd, "%s: ctrl_id: %d, value: %d\n",
		 __func__, ctrl->id, ctrl->val);

	mutex_lock(&info->lock);
	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any controls to H/W at this समय. Instead
	 * the controls will be restored right after घातer-up.
	 */
	अगर (!info->घातer)
		जाओ unlock;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = noon010_enable_स्वतःwhitebalance(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BLUE_BALANCE:
		ret = cam_i2c_ग_लिखो(sd, MWB_BGAIN_REG, ctrl->val);
		अवरोध;
	हाल V4L2_CID_RED_BALANCE:
		ret =  cam_i2c_ग_लिखो(sd, MWB_RGAIN_REG, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
unlock:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक noon010_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(noon010_क्रमmats))
		वापस -EINVAL;

	code->code = noon010_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक noon010_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा noon010_info *info = to_noon010(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		अगर (cfg) अणु
			mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
			fmt->क्रमmat = *mf;
		पूर्ण
		वापस 0;
	पूर्ण
	mf = &fmt->क्रमmat;

	mutex_lock(&info->lock);
	mf->width = info->curr_win->width;
	mf->height = info->curr_win->height;
	mf->code = info->curr_fmt->code;
	mf->colorspace = info->curr_fmt->colorspace;
	mf->field = V4L2_FIELD_NONE;

	mutex_unlock(&info->lock);
	वापस 0;
पूर्ण

/* Return nearest media bus frame क्रमmat. */
अटल स्थिर काष्ठा noon010_क्रमmat *noon010_try_fmt(काष्ठा v4l2_subdev *sd,
					    काष्ठा v4l2_mbus_framefmt *mf)
अणु
	पूर्णांक i = ARRAY_SIZE(noon010_क्रमmats);

	जबतक (--i)
		अगर (mf->code == noon010_क्रमmats[i].code)
			अवरोध;
	mf->code = noon010_क्रमmats[i].code;

	वापस &noon010_क्रमmats[i];
पूर्ण

अटल पूर्णांक noon010_set_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा noon010_info *info = to_noon010(sd);
	स्थिर काष्ठा noon010_frmsize *size = शून्य;
	स्थिर काष्ठा noon010_क्रमmat *nf;
	काष्ठा v4l2_mbus_framefmt *mf;
	पूर्णांक ret = 0;

	nf = noon010_try_fmt(sd, &fmt->क्रमmat);
	noon010_try_frame_size(&fmt->क्रमmat, &size);
	fmt->क्रमmat.colorspace = V4L2_COLORSPACE_JPEG;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		अगर (cfg) अणु
			mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
			*mf = fmt->क्रमmat;
		पूर्ण
		वापस 0;
	पूर्ण
	mutex_lock(&info->lock);
	अगर (!info->streaming) अणु
		info->apply_new_cfg = 1;
		info->curr_fmt = nf;
		info->curr_win = size;
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

/* Called with काष्ठा noon010_info.lock mutex held */
अटल पूर्णांक noon010_base_config(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक ret = noon010_bulk_ग_लिखो_reg(sd, noon010_base_regs);
	अगर (!ret)
		ret = noon010_set_params(sd);
	अगर (!ret)
		ret = noon010_set_flip(sd, 1, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक noon010_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा noon010_info *info = to_noon010(sd);
	पूर्णांक ret;

	mutex_lock(&info->lock);
	अगर (on) अणु
		ret = घातer_enable(info);
		अगर (!ret)
			ret = noon010_base_config(sd);
	पूर्ण अन्यथा अणु
		noon010_घातer_ctrl(sd, false, true);
		ret = घातer_disable(info);
	पूर्ण
	mutex_unlock(&info->lock);

	/* Restore the controls state */
	अगर (!ret && on)
		ret = v4l2_ctrl_handler_setup(&info->hdl);

	वापस ret;
पूर्ण

अटल पूर्णांक noon010_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा noon010_info *info = to_noon010(sd);
	पूर्णांक ret = 0;

	mutex_lock(&info->lock);
	अगर (!info->streaming != !on) अणु
		ret = noon010_घातer_ctrl(sd, false, !on);
		अगर (!ret)
			info->streaming = on;
	पूर्ण
	अगर (!ret && on && info->apply_new_cfg) अणु
		ret = noon010_set_params(sd);
		अगर (!ret)
			info->apply_new_cfg = 0;
	पूर्ण
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक noon010_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा noon010_info *info = to_noon010(sd);

	v4l2_ctrl_handler_log_status(&info->hdl, sd->name);
	वापस 0;
पूर्ण

अटल पूर्णांक noon010_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	mf->width = noon010_sizes[0].width;
	mf->height = noon010_sizes[0].height;
	mf->code = noon010_क्रमmats[0].code;
	mf->colorspace = V4L2_COLORSPACE_JPEG;
	mf->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops noon010_subdev_पूर्णांकernal_ops = अणु
	.खोलो = noon010_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops noon010_ctrl_ops = अणु
	.s_ctrl = noon010_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops noon010_core_ops = अणु
	.s_घातer	= noon010_s_घातer,
	.log_status	= noon010_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops noon010_pad_ops = अणु
	.क्रमागत_mbus_code	= noon010_क्रमागत_mbus_code,
	.get_fmt	= noon010_get_fmt,
	.set_fmt	= noon010_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops noon010_video_ops = अणु
	.s_stream	= noon010_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops noon010_ops = अणु
	.core	= &noon010_core_ops,
	.pad	= &noon010_pad_ops,
	.video	= &noon010_video_ops,
पूर्ण;

/* Return 0 अगर NOON010PC30L sensor type was detected or -ENODEV otherwise. */
अटल पूर्णांक noon010_detect(काष्ठा i2c_client *client, काष्ठा noon010_info *info)
अणु
	पूर्णांक ret;

	ret = घातer_enable(info);
	अगर (ret)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, DEVICE_ID_REG);
	अगर (ret < 0)
		dev_err(&client->dev, "I2C read failed: 0x%X\n", ret);

	घातer_disable(info);

	वापस ret == NOON010PC30_ID ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक noon010_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा noon010_info *info;
	काष्ठा v4l2_subdev *sd;
	स्थिर काष्ठा noon010pc30_platक्रमm_data *pdata
		= client->dev.platक्रमm_data;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!pdata) अणु
		dev_err(&client->dev, "No platform data!\n");
		वापस -EIO;
	पूर्ण

	info = devm_kzalloc(&client->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	mutex_init(&info->lock);
	sd = &info->sd;
	v4l2_i2c_subdev_init(sd, client, &noon010_ops);
	/* Static name; NEVER use in new drivers! */
	strscpy(sd->name, MODULE_NAME, माप(sd->name));

	sd->पूर्णांकernal_ops = &noon010_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	v4l2_ctrl_handler_init(&info->hdl, 3);

	v4l2_ctrl_new_std(&info->hdl, &noon010_ctrl_ops,
			  V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&info->hdl, &noon010_ctrl_ops,
			  V4L2_CID_RED_BALANCE, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&info->hdl, &noon010_ctrl_ops,
			  V4L2_CID_BLUE_BALANCE, 0, 127, 1, 64);

	sd->ctrl_handler = &info->hdl;

	ret = info->hdl.error;
	अगर (ret)
		जाओ np_err;

	info->i2c_reg_page	= -1;
	info->gpio_nreset	= -EINVAL;
	info->gpio_nstby	= -EINVAL;
	info->curr_fmt		= &noon010_क्रमmats[0];
	info->curr_win		= &noon010_sizes[0];

	अगर (gpio_is_valid(pdata->gpio_nreset)) अणु
		ret = devm_gpio_request_one(&client->dev, pdata->gpio_nreset,
					    GPIOF_OUT_INIT_LOW,
					    "NOON010PC30 NRST");
		अगर (ret) अणु
			dev_err(&client->dev, "GPIO request error: %d\n", ret);
			जाओ np_err;
		पूर्ण
		info->gpio_nreset = pdata->gpio_nreset;
		gpio_export(info->gpio_nreset, 0);
	पूर्ण

	अगर (gpio_is_valid(pdata->gpio_nstby)) अणु
		ret = devm_gpio_request_one(&client->dev, pdata->gpio_nstby,
					    GPIOF_OUT_INIT_LOW,
					    "NOON010PC30 NSTBY");
		अगर (ret) अणु
			dev_err(&client->dev, "GPIO request error: %d\n", ret);
			जाओ np_err;
		पूर्ण
		info->gpio_nstby = pdata->gpio_nstby;
		gpio_export(info->gpio_nstby, 0);
	पूर्ण

	क्रम (i = 0; i < NOON010_NUM_SUPPLIES; i++)
		info->supply[i].supply = noon010_supply_name[i];

	ret = devm_regulator_bulk_get(&client->dev, NOON010_NUM_SUPPLIES,
				 info->supply);
	अगर (ret)
		जाओ np_err;

	info->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &info->pad);
	अगर (ret < 0)
		जाओ np_err;

	ret = noon010_detect(client, info);
	अगर (!ret)
		वापस 0;

np_err:
	v4l2_ctrl_handler_मुक्त(&info->hdl);
	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस ret;
पूर्ण

अटल पूर्णांक noon010_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा noon010_info *info = to_noon010(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&info->hdl);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id noon010_id[] = अणु
	अणु MODULE_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, noon010_id);


अटल काष्ठा i2c_driver noon010_i2c_driver = अणु
	.driver = अणु
		.name = MODULE_NAME
	पूर्ण,
	.probe		= noon010_probe,
	.हटाओ		= noon010_हटाओ,
	.id_table	= noon010_id,
पूर्ण;

module_i2c_driver(noon010_i2c_driver);

MODULE_DESCRIPTION("Siliconfile NOON010PC30 camera driver");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_LICENSE("GPL");

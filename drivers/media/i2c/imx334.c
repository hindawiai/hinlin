<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sony imx334 sensor driver
 *
 * Copyright (C) 2021 Intel Corporation
 */
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

/* Streaming Mode */
#घोषणा IMX334_REG_MODE_SELECT	0x3000
#घोषणा IMX334_MODE_STANDBY	0x01
#घोषणा IMX334_MODE_STREAMING	0x00

/* Lines per frame */
#घोषणा IMX334_REG_LPFR		0x3030

/* Chip ID */
#घोषणा IMX334_REG_ID		0x3044
#घोषणा IMX334_ID		0x1e

/* Exposure control */
#घोषणा IMX334_REG_SHUTTER	0x3058
#घोषणा IMX334_EXPOSURE_MIN	1
#घोषणा IMX334_EXPOSURE_OFFSET	5
#घोषणा IMX334_EXPOSURE_STEP	1
#घोषणा IMX334_EXPOSURE_DEFAULT	0x0648

/* Analog gain control */
#घोषणा IMX334_REG_AGAIN	0x30e8
#घोषणा IMX334_AGAIN_MIN	0
#घोषणा IMX334_AGAIN_MAX	240
#घोषणा IMX334_AGAIN_STEP	1
#घोषणा IMX334_AGAIN_DEFAULT	0

/* Group hold रेजिस्टर */
#घोषणा IMX334_REG_HOLD		0x3001

/* Input घड़ी rate */
#घोषणा IMX334_INCLK_RATE	24000000

/* CSI2 HW configuration */
#घोषणा IMX334_LINK_FREQ	891000000
#घोषणा IMX334_NUM_DATA_LANES	4

#घोषणा IMX334_REG_MIN		0x00
#घोषणा IMX334_REG_MAX		0xfffff

/**
 * काष्ठा imx334_reg - imx334 sensor रेजिस्टर
 * @address: Register address
 * @val: Register value
 */
काष्ठा imx334_reg अणु
	u16 address;
	u8 val;
पूर्ण;

/**
 * काष्ठा imx334_reg_list - imx334 sensor रेजिस्टर list
 * @num_of_regs: Number of रेजिस्टरs in the list
 * @regs: Poपूर्णांकer to रेजिस्टर list
 */
काष्ठा imx334_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा imx334_reg *regs;
पूर्ण;

/**
 * काष्ठा imx334_mode - imx334 sensor mode काष्ठाure
 * @width: Frame width
 * @height: Frame height
 * @code: Format code
 * @hblank: Horizontal blanking in lines
 * @vblank: Vertical blanking in lines
 * @vblank_min: Minimal vertical blanking in lines
 * @vblank_max: Maximum vertical blanking in lines
 * @pclk: Sensor pixel घड़ी
 * @link_freq_idx: Link frequency index
 * @reg_list: Register list क्रम sensor mode
 */
काष्ठा imx334_mode अणु
	u32 width;
	u32 height;
	u32 code;
	u32 hblank;
	u32 vblank;
	u32 vblank_min;
	u32 vblank_max;
	u64 pclk;
	u32 link_freq_idx;
	काष्ठा imx334_reg_list reg_list;
पूर्ण;

/**
 * काष्ठा imx334 - imx334 sensor device काष्ठाure
 * @dev: Poपूर्णांकer to generic device
 * @client: Poपूर्णांकer to i2c client
 * @sd: V4L2 sub-device
 * @pad: Media pad. Only one pad supported
 * @reset_gpio: Sensor reset gpio
 * @inclk: Sensor input घड़ी
 * @ctrl_handler: V4L2 control handler
 * @link_freq_ctrl: Poपूर्णांकer to link frequency control
 * @pclk_ctrl: Poपूर्णांकer to pixel घड़ी control
 * @hblank_ctrl: Poपूर्णांकer to horizontal blanking control
 * @vblank_ctrl: Poपूर्णांकer to vertical blanking control
 * @exp_ctrl: Poपूर्णांकer to exposure control
 * @again_ctrl: Poपूर्णांकer to analog gain control
 * @vblank: Vertical blanking in lines
 * @cur_mode: Poपूर्णांकer to current selected sensor mode
 * @mutex: Mutex क्रम serializing sensor controls
 * @streaming: Flag indicating streaming state
 */
काष्ठा imx334 अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा clk *inclk;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *link_freq_ctrl;
	काष्ठा v4l2_ctrl *pclk_ctrl;
	काष्ठा v4l2_ctrl *hblank_ctrl;
	काष्ठा v4l2_ctrl *vblank_ctrl;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *exp_ctrl;
		काष्ठा v4l2_ctrl *again_ctrl;
	पूर्ण;
	u32 vblank;
	स्थिर काष्ठा imx334_mode *cur_mode;
	काष्ठा mutex mutex;
	bool streaming;
पूर्ण;

अटल स्थिर s64 link_freq[] = अणु
	IMX334_LINK_FREQ,
पूर्ण;

/* Sensor mode रेजिस्टरs */
अटल स्थिर काष्ठा imx334_reg mode_3840x2160_regs[] = अणु
	अणु0x3000, 0x01पूर्ण,
	अणु0x3002, 0x00पूर्ण,
	अणु0x3018, 0x04पूर्ण,
	अणु0x37b0, 0x36पूर्ण,
	अणु0x304c, 0x00पूर्ण,
	अणु0x300c, 0x3bपूर्ण,
	अणु0x300d, 0x2aपूर्ण,
	अणु0x3034, 0x26पूर्ण,
	अणु0x3035, 0x02पूर्ण,
	अणु0x314c, 0x29पूर्ण,
	अणु0x314d, 0x01पूर्ण,
	अणु0x315a, 0x02पूर्ण,
	अणु0x3168, 0xa0पूर्ण,
	अणु0x316a, 0x7eपूर्ण,
	अणु0x3288, 0x21पूर्ण,
	अणु0x328a, 0x02पूर्ण,
	अणु0x302c, 0x3cपूर्ण,
	अणु0x302e, 0x00पूर्ण,
	अणु0x302f, 0x0fपूर्ण,
	अणु0x3076, 0x70पूर्ण,
	अणु0x3077, 0x08पूर्ण,
	अणु0x3090, 0x70पूर्ण,
	अणु0x3091, 0x08पूर्ण,
	अणु0x30d8, 0x20पूर्ण,
	अणु0x30d9, 0x12पूर्ण,
	अणु0x3308, 0x70पूर्ण,
	अणु0x3309, 0x08पूर्ण,
	अणु0x3414, 0x05पूर्ण,
	अणु0x3416, 0x18पूर्ण,
	अणु0x35ac, 0x0eपूर्ण,
	अणु0x3648, 0x01पूर्ण,
	अणु0x364a, 0x04पूर्ण,
	अणु0x364c, 0x04पूर्ण,
	अणु0x3678, 0x01पूर्ण,
	अणु0x367c, 0x31पूर्ण,
	अणु0x367e, 0x31पूर्ण,
	अणु0x3708, 0x02पूर्ण,
	अणु0x3714, 0x01पूर्ण,
	अणु0x3715, 0x02पूर्ण,
	अणु0x3716, 0x02पूर्ण,
	अणु0x3717, 0x02पूर्ण,
	अणु0x371c, 0x3dपूर्ण,
	अणु0x371d, 0x3fपूर्ण,
	अणु0x372c, 0x00पूर्ण,
	अणु0x372d, 0x00पूर्ण,
	अणु0x372e, 0x46पूर्ण,
	अणु0x372f, 0x00पूर्ण,
	अणु0x3730, 0x89पूर्ण,
	अणु0x3731, 0x00पूर्ण,
	अणु0x3732, 0x08पूर्ण,
	अणु0x3733, 0x01पूर्ण,
	अणु0x3734, 0xfeपूर्ण,
	अणु0x3735, 0x05पूर्ण,
	अणु0x375d, 0x00पूर्ण,
	अणु0x375e, 0x00पूर्ण,
	अणु0x375f, 0x61पूर्ण,
	अणु0x3760, 0x06पूर्ण,
	अणु0x3768, 0x1bपूर्ण,
	अणु0x3769, 0x1bपूर्ण,
	अणु0x376a, 0x1aपूर्ण,
	अणु0x376b, 0x19पूर्ण,
	अणु0x376c, 0x18पूर्ण,
	अणु0x376d, 0x14पूर्ण,
	अणु0x376e, 0x0fपूर्ण,
	अणु0x3776, 0x00पूर्ण,
	अणु0x3777, 0x00पूर्ण,
	अणु0x3778, 0x46पूर्ण,
	अणु0x3779, 0x00पूर्ण,
	अणु0x377a, 0x08पूर्ण,
	अणु0x377b, 0x01पूर्ण,
	अणु0x377c, 0x45पूर्ण,
	अणु0x377d, 0x01पूर्ण,
	अणु0x377e, 0x23पूर्ण,
	अणु0x377f, 0x02पूर्ण,
	अणु0x3780, 0xd9पूर्ण,
	अणु0x3781, 0x03पूर्ण,
	अणु0x3782, 0xf5पूर्ण,
	अणु0x3783, 0x06पूर्ण,
	अणु0x3784, 0xa5पूर्ण,
	अणु0x3788, 0x0fपूर्ण,
	अणु0x378a, 0xd9पूर्ण,
	अणु0x378b, 0x03पूर्ण,
	अणु0x378c, 0xebपूर्ण,
	अणु0x378d, 0x05पूर्ण,
	अणु0x378e, 0x87पूर्ण,
	अणु0x378f, 0x06पूर्ण,
	अणु0x3790, 0xf5पूर्ण,
	अणु0x3792, 0x43पूर्ण,
	अणु0x3794, 0x7aपूर्ण,
	अणु0x3796, 0xa1पूर्ण,
	अणु0x3e04, 0x0eपूर्ण,
	अणु0x3a00, 0x01पूर्ण,
पूर्ण;

/* Supported sensor mode configurations */
अटल स्थिर काष्ठा imx334_mode supported_mode = अणु
	.width = 3840,
	.height = 2160,
	.hblank = 560,
	.vblank = 2340,
	.vblank_min = 90,
	.vblank_max = 132840,
	.pclk = 594000000,
	.link_freq_idx = 0,
	.code = MEDIA_BUS_FMT_SRGGB12_1X12,
	.reg_list = अणु
		.num_of_regs = ARRAY_SIZE(mode_3840x2160_regs),
		.regs = mode_3840x2160_regs,
	पूर्ण,
पूर्ण;

/**
 * to_imx334() - imv334 V4L2 sub-device to imx334 device.
 * @subdev: poपूर्णांकer to imx334 V4L2 sub-device
 *
 * Return: poपूर्णांकer to imx334 device
 */
अटल अंतरभूत काष्ठा imx334 *to_imx334(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा imx334, sd);
पूर्ण

/**
 * imx334_पढ़ो_reg() - Read रेजिस्टरs.
 * @imx334: poपूर्णांकer to imx334 device
 * @reg: रेजिस्टर address
 * @len: length of bytes to पढ़ो. Max supported bytes is 4
 * @val: poपूर्णांकer to रेजिस्टर value to be filled.
 *
 * Big endian रेजिस्टर addresses with little endian values.
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_पढ़ो_reg(काष्ठा imx334 *imx334, u16 reg, u32 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx334->sd);
	काष्ठा i2c_msg msgs[2] = अणु0पूर्ण;
	u8 addr_buf[2] = अणु0पूर्ण;
	u8 data_buf[4] = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (WARN_ON(len > 4))
		वापस -EINVAL;

	put_unaligned_be16(reg, addr_buf);

	/* Write रेजिस्टर address */
	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = ARRAY_SIZE(addr_buf);
	msgs[0].buf = addr_buf;

	/* Read data from रेजिस्टर */
	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = data_buf;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs))
		वापस -EIO;

	*val = get_unaligned_le32(data_buf);

	वापस 0;
पूर्ण

/**
 * imx334_ग_लिखो_reg() - Write रेजिस्टर
 * @imx334: poपूर्णांकer to imx334 device
 * @reg: रेजिस्टर address
 * @len: length of bytes. Max supported bytes is 4
 * @val: रेजिस्टर value
 *
 * Big endian रेजिस्टर addresses with little endian values.
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_ग_लिखो_reg(काष्ठा imx334 *imx334, u16 reg, u32 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx334->sd);
	u8 buf[6] = अणु0पूर्ण;

	अगर (WARN_ON(len > 4))
		वापस -EINVAL;

	put_unaligned_be16(reg, buf);
	put_unaligned_le32(val, buf + 2);
	अगर (i2c_master_send(client, buf, len + 2) != len + 2)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * imx334_ग_लिखो_regs() - Write a list of रेजिस्टरs
 * @imx334: poपूर्णांकer to imx334 device
 * @regs: list of रेजिस्टरs to be written
 * @len: length of रेजिस्टरs array
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_ग_लिखो_regs(काष्ठा imx334 *imx334,
			     स्थिर काष्ठा imx334_reg *regs, u32 len)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < len; i++) अणु
		ret = imx334_ग_लिखो_reg(imx334, regs[i].address, 1, regs[i].val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * imx334_update_controls() - Update control ranges based on streaming mode
 * @imx334: poपूर्णांकer to imx334 device
 * @mode: poपूर्णांकer to imx334_mode sensor mode
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_update_controls(काष्ठा imx334 *imx334,
				  स्थिर काष्ठा imx334_mode *mode)
अणु
	पूर्णांक ret;

	ret = __v4l2_ctrl_s_ctrl(imx334->link_freq_ctrl, mode->link_freq_idx);
	अगर (ret)
		वापस ret;

	ret = __v4l2_ctrl_s_ctrl(imx334->hblank_ctrl, mode->hblank);
	अगर (ret)
		वापस ret;

	वापस __v4l2_ctrl_modअगरy_range(imx334->vblank_ctrl, mode->vblank_min,
					mode->vblank_max, 1, mode->vblank);
पूर्ण

/**
 * imx334_update_exp_gain() - Set updated exposure and gain
 * @imx334: poपूर्णांकer to imx334 device
 * @exposure: updated exposure value
 * @gain: updated analog gain value
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_update_exp_gain(काष्ठा imx334 *imx334, u32 exposure, u32 gain)
अणु
	u32 lpfr, shutter;
	पूर्णांक ret;

	lpfr = imx334->vblank + imx334->cur_mode->height;
	shutter = lpfr - exposure;

	dev_dbg(imx334->dev, "Set long exp %u analog gain %u sh0 %u lpfr %u",
		exposure, gain, shutter, lpfr);

	ret = imx334_ग_लिखो_reg(imx334, IMX334_REG_HOLD, 1, 1);
	अगर (ret)
		वापस ret;

	ret = imx334_ग_लिखो_reg(imx334, IMX334_REG_LPFR, 3, lpfr);
	अगर (ret)
		जाओ error_release_group_hold;

	ret = imx334_ग_लिखो_reg(imx334, IMX334_REG_SHUTTER, 3, shutter);
	अगर (ret)
		जाओ error_release_group_hold;

	ret = imx334_ग_लिखो_reg(imx334, IMX334_REG_AGAIN, 1, gain);

error_release_group_hold:
	imx334_ग_लिखो_reg(imx334, IMX334_REG_HOLD, 1, 0);

	वापस ret;
पूर्ण

/**
 * imx334_set_ctrl() - Set subdevice control
 * @ctrl: poपूर्णांकer to v4l2_ctrl काष्ठाure
 *
 * Supported controls:
 * - V4L2_CID_VBLANK
 * - cluster controls:
 *   - V4L2_CID_ANALOGUE_GAIN
 *   - V4L2_CID_EXPOSURE
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा imx334 *imx334 =
		container_of(ctrl->handler, काष्ठा imx334, ctrl_handler);
	u32 analog_gain;
	u32 exposure;
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VBLANK:
		imx334->vblank = imx334->vblank_ctrl->val;

		dev_dbg(imx334->dev, "Received vblank %u, new lpfr %u",
			imx334->vblank,
			imx334->vblank + imx334->cur_mode->height);

		ret = __v4l2_ctrl_modअगरy_range(imx334->exp_ctrl,
					       IMX334_EXPOSURE_MIN,
					       imx334->vblank +
					       imx334->cur_mode->height -
					       IMX334_EXPOSURE_OFFSET,
					       1, IMX334_EXPOSURE_DEFAULT);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:

		/* Set controls only अगर sensor is in घातer on state */
		अगर (!pm_runसमय_get_अगर_in_use(imx334->dev))
			वापस 0;

		exposure = ctrl->val;
		analog_gain = imx334->again_ctrl->val;

		dev_dbg(imx334->dev, "Received exp %u analog gain %u",
			exposure, analog_gain);

		ret = imx334_update_exp_gain(imx334, exposure, analog_gain);

		pm_runसमय_put(imx334->dev);

		अवरोध;
	शेष:
		dev_err(imx334->dev, "Invalid control %d", ctrl->id);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/* V4l2 subdevice control ops*/
अटल स्थिर काष्ठा v4l2_ctrl_ops imx334_ctrl_ops = अणु
	.s_ctrl = imx334_set_ctrl,
पूर्ण;

/**
 * imx334_क्रमागत_mbus_code() - Enumerate V4L2 sub-device mbus codes
 * @sd: poपूर्णांकer to imx334 V4L2 sub-device काष्ठाure
 * @cfg: V4L2 sub-device pad configuration
 * @code: V4L2 sub-device code क्रमागतeration need to be filled
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = supported_mode.code;

	वापस 0;
पूर्ण

/**
 * imx334_क्रमागत_frame_size() - Enumerate V4L2 sub-device frame sizes
 * @sd: poपूर्णांकer to imx334 V4L2 sub-device काष्ठाure
 * @cfg: V4L2 sub-device pad configuration
 * @fsize: V4L2 sub-device size क्रमागतeration need to be filled
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fsize)
अणु
	अगर (fsize->index > 0)
		वापस -EINVAL;

	अगर (fsize->code != supported_mode.code)
		वापस -EINVAL;

	fsize->min_width = supported_mode.width;
	fsize->max_width = fsize->min_width;
	fsize->min_height = supported_mode.height;
	fsize->max_height = fsize->min_height;

	वापस 0;
पूर्ण

/**
 * imx334_fill_pad_क्रमmat() - Fill subdevice pad क्रमmat
 *                            from selected sensor mode
 * @imx334: poपूर्णांकer to imx334 device
 * @mode: poपूर्णांकer to imx334_mode sensor mode
 * @fmt: V4L2 sub-device क्रमmat need to be filled
 */
अटल व्योम imx334_fill_pad_क्रमmat(काष्ठा imx334 *imx334,
				   स्थिर काष्ठा imx334_mode *mode,
				   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	fmt->क्रमmat.width = mode->width;
	fmt->क्रमmat.height = mode->height;
	fmt->क्रमmat.code = mode->code;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;
	fmt->क्रमmat.colorspace = V4L2_COLORSPACE_RAW;
	fmt->क्रमmat.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	fmt->क्रमmat.quantization = V4L2_QUANTIZATION_DEFAULT;
	fmt->क्रमmat.xfer_func = V4L2_XFER_FUNC_NONE;
पूर्ण

/**
 * imx334_get_pad_क्रमmat() - Get subdevice pad क्रमmat
 * @sd: poपूर्णांकer to imx334 V4L2 sub-device काष्ठाure
 * @cfg: V4L2 sub-device pad configuration
 * @fmt: V4L2 sub-device क्रमmat need to be set
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx334 *imx334 = to_imx334(sd);

	mutex_lock(&imx334->mutex);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *framefmt;

		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		fmt->क्रमmat = *framefmt;
	पूर्ण अन्यथा अणु
		imx334_fill_pad_क्रमmat(imx334, imx334->cur_mode, fmt);
	पूर्ण

	mutex_unlock(&imx334->mutex);

	वापस 0;
पूर्ण

/**
 * imx334_set_pad_क्रमmat() - Set subdevice pad क्रमmat
 * @sd: poपूर्णांकer to imx334 V4L2 sub-device काष्ठाure
 * @cfg: V4L2 sub-device pad configuration
 * @fmt: V4L2 sub-device क्रमmat need to be set
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx334 *imx334 = to_imx334(sd);
	स्थिर काष्ठा imx334_mode *mode;
	पूर्णांक ret = 0;

	mutex_lock(&imx334->mutex);

	mode = &supported_mode;
	imx334_fill_pad_क्रमmat(imx334, mode, fmt);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *framefmt;

		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*framefmt = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		ret = imx334_update_controls(imx334, mode);
		अगर (!ret)
			imx334->cur_mode = mode;
	पूर्ण

	mutex_unlock(&imx334->mutex);

	वापस ret;
पूर्ण

/**
 * imx334_init_pad_cfg() - Initialize sub-device pad configuration
 * @sd: poपूर्णांकer to imx334 V4L2 sub-device काष्ठाure
 * @cfg: V4L2 sub-device pad configuration
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_init_pad_cfg(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा imx334 *imx334 = to_imx334(sd);
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु 0 पूर्ण;

	fmt.which = cfg ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	imx334_fill_pad_क्रमmat(imx334, &supported_mode, &fmt);

	वापस imx334_set_pad_क्रमmat(sd, cfg, &fmt);
पूर्ण

/**
 * imx334_start_streaming() - Start sensor stream
 * @imx334: poपूर्णांकer to imx334 device
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_start_streaming(काष्ठा imx334 *imx334)
अणु
	स्थिर काष्ठा imx334_reg_list *reg_list;
	पूर्णांक ret;

	/* Write sensor mode रेजिस्टरs */
	reg_list = &imx334->cur_mode->reg_list;
	ret = imx334_ग_लिखो_regs(imx334, reg_list->regs,
				reg_list->num_of_regs);
	अगर (ret) अणु
		dev_err(imx334->dev, "fail to write initial registers");
		वापस ret;
	पूर्ण

	/* Setup handler will ग_लिखो actual exposure and gain */
	ret =  __v4l2_ctrl_handler_setup(imx334->sd.ctrl_handler);
	अगर (ret) अणु
		dev_err(imx334->dev, "fail to setup handler");
		वापस ret;
	पूर्ण

	/* Start streaming */
	ret = imx334_ग_लिखो_reg(imx334, IMX334_REG_MODE_SELECT,
			       1, IMX334_MODE_STREAMING);
	अगर (ret) अणु
		dev_err(imx334->dev, "fail to start streaming");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * imx334_stop_streaming() - Stop sensor stream
 * @imx334: poपूर्णांकer to imx334 device
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_stop_streaming(काष्ठा imx334 *imx334)
अणु
	वापस imx334_ग_लिखो_reg(imx334, IMX334_REG_MODE_SELECT,
				1, IMX334_MODE_STANDBY);
पूर्ण

/**
 * imx334_set_stream() - Enable sensor streaming
 * @sd: poपूर्णांकer to imx334 subdevice
 * @enable: set to enable sensor streaming
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा imx334 *imx334 = to_imx334(sd);
	पूर्णांक ret;

	mutex_lock(&imx334->mutex);

	अगर (imx334->streaming == enable) अणु
		mutex_unlock(&imx334->mutex);
		वापस 0;
	पूर्ण

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(imx334->dev);
		अगर (ret)
			जाओ error_घातer_off;

		ret = imx334_start_streaming(imx334);
		अगर (ret)
			जाओ error_घातer_off;
	पूर्ण अन्यथा अणु
		imx334_stop_streaming(imx334);
		pm_runसमय_put(imx334->dev);
	पूर्ण

	imx334->streaming = enable;

	mutex_unlock(&imx334->mutex);

	वापस 0;

error_घातer_off:
	pm_runसमय_put(imx334->dev);
	mutex_unlock(&imx334->mutex);

	वापस ret;
पूर्ण

/**
 * imx334_detect() - Detect imx334 sensor
 * @imx334: poपूर्णांकer to imx334 device
 *
 * Return: 0 अगर successful, -EIO अगर sensor id करोes not match
 */
अटल पूर्णांक imx334_detect(काष्ठा imx334 *imx334)
अणु
	पूर्णांक ret;
	u32 val;

	ret = imx334_पढ़ो_reg(imx334, IMX334_REG_ID, 2, &val);
	अगर (ret)
		वापस ret;

	अगर (val != IMX334_ID) अणु
		dev_err(imx334->dev, "chip id mismatch: %x!=%x",
			IMX334_ID, val);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * imx334_parse_hw_config() - Parse HW configuration and check अगर supported
 * @imx334: poपूर्णांकer to imx334 device
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_parse_hw_config(काष्ठा imx334 *imx334)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(imx334->dev);
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	काष्ठा fwnode_handle *ep;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!fwnode)
		वापस -ENXIO;

	/* Request optional reset pin */
	imx334->reset_gpio = devm_gpiod_get_optional(imx334->dev, "reset",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(imx334->reset_gpio)) अणु
		dev_err(imx334->dev, "failed to get reset gpio %ld",
			PTR_ERR(imx334->reset_gpio));
		वापस PTR_ERR(imx334->reset_gpio);
	पूर्ण

	/* Get sensor input घड़ी */
	imx334->inclk = devm_clk_get(imx334->dev, शून्य);
	अगर (IS_ERR(imx334->inclk)) अणु
		dev_err(imx334->dev, "could not get inclk");
		वापस PTR_ERR(imx334->inclk);
	पूर्ण

	rate = clk_get_rate(imx334->inclk);
	अगर (rate != IMX334_INCLK_RATE) अणु
		dev_err(imx334->dev, "inclk frequency mismatch");
		वापस -EINVAL;
	पूर्ण

	ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, शून्य);
	अगर (!ep)
		वापस -ENXIO;

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
	fwnode_handle_put(ep);
	अगर (ret)
		वापस ret;

	अगर (bus_cfg.bus.mipi_csi2.num_data_lanes != IMX334_NUM_DATA_LANES) अणु
		dev_err(imx334->dev,
			"number of CSI2 data lanes %d is not supported",
			bus_cfg.bus.mipi_csi2.num_data_lanes);
		ret = -EINVAL;
		जाओ करोne_endpoपूर्णांक_मुक्त;
	पूर्ण

	अगर (!bus_cfg.nr_of_link_frequencies) अणु
		dev_err(imx334->dev, "no link frequencies defined");
		ret = -EINVAL;
		जाओ करोne_endpoपूर्णांक_मुक्त;
	पूर्ण

	क्रम (i = 0; i < bus_cfg.nr_of_link_frequencies; i++)
		अगर (bus_cfg.link_frequencies[i] == IMX334_LINK_FREQ)
			जाओ करोne_endpoपूर्णांक_मुक्त;

	ret = -EINVAL;

करोne_endpoपूर्णांक_मुक्त:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);

	वापस ret;
पूर्ण

/* V4l2 subdevice ops */
अटल स्थिर काष्ठा v4l2_subdev_video_ops imx334_video_ops = अणु
	.s_stream = imx334_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imx334_pad_ops = अणु
	.init_cfg = imx334_init_pad_cfg,
	.क्रमागत_mbus_code = imx334_क्रमागत_mbus_code,
	.क्रमागत_frame_size = imx334_क्रमागत_frame_size,
	.get_fmt = imx334_get_pad_क्रमmat,
	.set_fmt = imx334_set_pad_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imx334_subdev_ops = अणु
	.video = &imx334_video_ops,
	.pad = &imx334_pad_ops,
पूर्ण;

/**
 * imx334_घातer_on() - Sensor घातer on sequence
 * @dev: poपूर्णांकer to i2c device
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx334 *imx334 = to_imx334(sd);
	पूर्णांक ret;

	gpiod_set_value_cansleep(imx334->reset_gpio, 1);

	ret = clk_prepare_enable(imx334->inclk);
	अगर (ret) अणु
		dev_err(imx334->dev, "fail to enable inclk");
		जाओ error_reset;
	पूर्ण

	usleep_range(18000, 20000);

	वापस 0;

error_reset:
	gpiod_set_value_cansleep(imx334->reset_gpio, 0);

	वापस ret;
पूर्ण

/**
 * imx334_घातer_off() - Sensor घातer off sequence
 * @dev: poपूर्णांकer to i2c device
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx334 *imx334 = to_imx334(sd);

	gpiod_set_value_cansleep(imx334->reset_gpio, 0);

	clk_disable_unprepare(imx334->inclk);

	वापस 0;
पूर्ण

/**
 * imx334_init_controls() - Initialize sensor subdevice controls
 * @imx334: poपूर्णांकer to imx334 device
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_init_controls(काष्ठा imx334 *imx334)
अणु
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr = &imx334->ctrl_handler;
	स्थिर काष्ठा imx334_mode *mode = imx334->cur_mode;
	u32 lpfr;
	पूर्णांक ret;

	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 6);
	अगर (ret)
		वापस ret;

	/* Serialize controls with sensor device */
	ctrl_hdlr->lock = &imx334->mutex;

	/* Initialize exposure and gain */
	lpfr = mode->vblank + mode->height;
	imx334->exp_ctrl = v4l2_ctrl_new_std(ctrl_hdlr,
					     &imx334_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     IMX334_EXPOSURE_MIN,
					     lpfr - IMX334_EXPOSURE_OFFSET,
					     IMX334_EXPOSURE_STEP,
					     IMX334_EXPOSURE_DEFAULT);

	imx334->again_ctrl = v4l2_ctrl_new_std(ctrl_hdlr,
					       &imx334_ctrl_ops,
					       V4L2_CID_ANALOGUE_GAIN,
					       IMX334_AGAIN_MIN,
					       IMX334_AGAIN_MAX,
					       IMX334_AGAIN_STEP,
					       IMX334_AGAIN_DEFAULT);

	v4l2_ctrl_cluster(2, &imx334->exp_ctrl);

	imx334->vblank_ctrl = v4l2_ctrl_new_std(ctrl_hdlr,
						&imx334_ctrl_ops,
						V4L2_CID_VBLANK,
						mode->vblank_min,
						mode->vblank_max,
						1, mode->vblank);

	/* Read only controls */
	imx334->pclk_ctrl = v4l2_ctrl_new_std(ctrl_hdlr,
					      &imx334_ctrl_ops,
					      V4L2_CID_PIXEL_RATE,
					      mode->pclk, mode->pclk,
					      1, mode->pclk);

	imx334->link_freq_ctrl = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr,
							&imx334_ctrl_ops,
							V4L2_CID_LINK_FREQ,
							ARRAY_SIZE(link_freq) -
							1,
							mode->link_freq_idx,
							link_freq);
	अगर (imx334->link_freq_ctrl)
		imx334->link_freq_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	imx334->hblank_ctrl = v4l2_ctrl_new_std(ctrl_hdlr,
						&imx334_ctrl_ops,
						V4L2_CID_HBLANK,
						IMX334_REG_MIN,
						IMX334_REG_MAX,
						1, mode->hblank);
	अगर (imx334->hblank_ctrl)
		imx334->hblank_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	अगर (ctrl_hdlr->error) अणु
		dev_err(imx334->dev, "control init failed: %d",
			ctrl_hdlr->error);
		v4l2_ctrl_handler_मुक्त(ctrl_hdlr);
		वापस ctrl_hdlr->error;
	पूर्ण

	imx334->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;
पूर्ण

/**
 * imx334_probe() - I2C client device binding
 * @client: poपूर्णांकer to i2c client device
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा imx334 *imx334;
	पूर्णांक ret;

	imx334 = devm_kzalloc(&client->dev, माप(*imx334), GFP_KERNEL);
	अगर (!imx334)
		वापस -ENOMEM;

	imx334->dev = &client->dev;

	/* Initialize subdev */
	v4l2_i2c_subdev_init(&imx334->sd, client, &imx334_subdev_ops);

	ret = imx334_parse_hw_config(imx334);
	अगर (ret) अणु
		dev_err(imx334->dev, "HW configuration is not supported");
		वापस ret;
	पूर्ण

	mutex_init(&imx334->mutex);

	ret = imx334_घातer_on(imx334->dev);
	अगर (ret) अणु
		dev_err(imx334->dev, "failed to power-on the sensor");
		जाओ error_mutex_destroy;
	पूर्ण

	/* Check module identity */
	ret = imx334_detect(imx334);
	अगर (ret) अणु
		dev_err(imx334->dev, "failed to find sensor: %d", ret);
		जाओ error_घातer_off;
	पूर्ण

	/* Set शेष mode to max resolution */
	imx334->cur_mode = &supported_mode;
	imx334->vblank = imx334->cur_mode->vblank;

	ret = imx334_init_controls(imx334);
	अगर (ret) अणु
		dev_err(imx334->dev, "failed to init controls: %d", ret);
		जाओ error_घातer_off;
	पूर्ण

	/* Initialize subdev */
	imx334->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	imx334->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	/* Initialize source pad */
	imx334->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&imx334->sd.entity, 1, &imx334->pad);
	अगर (ret) अणु
		dev_err(imx334->dev, "failed to init entity pads: %d", ret);
		जाओ error_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&imx334->sd);
	अगर (ret < 0) अणु
		dev_err(imx334->dev,
			"failed to register async subdev: %d", ret);
		जाओ error_media_entity;
	पूर्ण

	pm_runसमय_set_active(imx334->dev);
	pm_runसमय_enable(imx334->dev);
	pm_runसमय_idle(imx334->dev);

	वापस 0;

error_media_entity:
	media_entity_cleanup(&imx334->sd.entity);
error_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(imx334->sd.ctrl_handler);
error_घातer_off:
	imx334_घातer_off(imx334->dev);
error_mutex_destroy:
	mutex_destroy(&imx334->mutex);

	वापस ret;
पूर्ण

/**
 * imx334_हटाओ() - I2C client device unbinding
 * @client: poपूर्णांकer to I2C client device
 *
 * Return: 0 अगर successful, error code otherwise.
 */
अटल पूर्णांक imx334_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx334 *imx334 = to_imx334(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_suspended(&client->dev);

	mutex_destroy(&imx334->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx334_pm_ops = अणु
	SET_RUNTIME_PM_OPS(imx334_घातer_off, imx334_घातer_on, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx334_of_match[] = अणु
	अणु .compatible = "sony,imx334" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, imx334_of_match);

अटल काष्ठा i2c_driver imx334_driver = अणु
	.probe_new = imx334_probe,
	.हटाओ = imx334_हटाओ,
	.driver = अणु
		.name = "imx334",
		.pm = &imx334_pm_ops,
		.of_match_table = imx334_of_match,
	पूर्ण,
पूर्ण;

module_i2c_driver(imx334_driver);

MODULE_DESCRIPTION("Sony imx334 sensor driver");
MODULE_LICENSE("GPL");

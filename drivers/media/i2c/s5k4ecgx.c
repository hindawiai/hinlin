<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Samsung S5K4ECGX 1/4" 5Mp CMOS Image Sensor SoC
 * with an Embedded Image Signal Processor.
 *
 * Copyright (C) 2012, Linaro, Sangwook Lee <sangwook.lee@linaro.org>
 * Copyright (C) 2012, Inसंकेत Co,. Ltd, Homin Lee <suapapa@inसंकेत.co.kr>
 *
 * Based on s5k6aa and noon010pc30 driver
 * Copyright (C) 2011, Samsung Electronics Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <media/media-entity.h>
#समावेश <media/i2c/s5k4ecgx.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/v4l2-subdev.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

#घोषणा S5K4ECGX_DRIVER_NAME		"s5k4ecgx"
#घोषणा S5K4ECGX_FIRMWARE		"s5k4ecgx.bin"

/* Firmware revision inक्रमmation */
#घोषणा REG_FW_REVISION			0x700001a6
#घोषणा REG_FW_VERSION			0x700001a4
#घोषणा S5K4ECGX_REVISION_1_1		0x11
#घोषणा S5K4ECGX_FW_VERSION		0x4ec0

/* General purpose parameters */
#घोषणा REG_USER_BRIGHTNESS		0x7000022c
#घोषणा REG_USER_CONTRAST		0x7000022e
#घोषणा REG_USER_SATURATION		0x70000230

#घोषणा REG_G_ENABLE_PREV		0x7000023e
#घोषणा REG_G_ENABLE_PREV_CHG		0x70000240
#घोषणा REG_G_NEW_CFG_SYNC		0x7000024a
#घोषणा REG_G_PREV_IN_WIDTH		0x70000250
#घोषणा REG_G_PREV_IN_HEIGHT		0x70000252
#घोषणा REG_G_PREV_IN_XOFFS		0x70000254
#घोषणा REG_G_PREV_IN_YOFFS		0x70000256
#घोषणा REG_G_CAP_IN_WIDTH		0x70000258
#घोषणा REG_G_CAP_IN_HEIGHT		0x7000025a
#घोषणा REG_G_CAP_IN_XOFFS		0x7000025c
#घोषणा REG_G_CAP_IN_YOFFS		0x7000025e
#घोषणा REG_G_INPUTS_CHANGE_REQ		0x70000262
#घोषणा REG_G_ACTIVE_PREV_CFG		0x70000266
#घोषणा REG_G_PREV_CFG_CHG		0x70000268
#घोषणा REG_G_PREV_OPEN_AFTER_CH	0x7000026a

/* Preview context रेजिस्टर sets. n = 0...4. */
#घोषणा PREG(n, x)			((n) * 0x30 + (x))
#घोषणा REG_P_OUT_WIDTH(n)		PREG(n, 0x700002a6)
#घोषणा REG_P_OUT_HEIGHT(n)		PREG(n, 0x700002a8)
#घोषणा REG_P_FMT(n)			PREG(n, 0x700002aa)
#घोषणा REG_P_PVI_MASK(n)		PREG(n, 0x700002b4)
#घोषणा REG_P_FR_TIME_TYPE(n)		PREG(n, 0x700002be)
#घोषणा  FR_TIME_DYNAMIC		0
#घोषणा  FR_TIME_FIXED			1
#घोषणा  FR_TIME_FIXED_ACCURATE		2
#घोषणा REG_P_FR_TIME_Q_TYPE(n)		PREG(n, 0x700002c0)
#घोषणा  FR_TIME_Q_DYNAMIC		0
#घोषणा  FR_TIME_Q_BEST_FRRATE		1
#घोषणा  FR_TIME_Q_BEST_QUALITY		2

/* Frame period in 0.1 ms units */
#घोषणा REG_P_MAX_FR_TIME(n)		PREG(n, 0x700002c2)
#घोषणा REG_P_MIN_FR_TIME(n)		PREG(n, 0x700002c4)
#घोषणा  US_TO_FR_TIME(__t)		((__t) / 100)
#घोषणा REG_P_PREV_MIRROR(n)		PREG(n, 0x700002d0)
#घोषणा REG_P_CAP_MIRROR(n)		PREG(n, 0x700002d2)

#घोषणा REG_G_PREVZOOM_IN_WIDTH		0x70000494
#घोषणा REG_G_PREVZOOM_IN_HEIGHT	0x70000496
#घोषणा REG_G_PREVZOOM_IN_XOFFS		0x70000498
#घोषणा REG_G_PREVZOOM_IN_YOFFS		0x7000049a
#घोषणा REG_G_CAPZOOM_IN_WIDTH		0x7000049c
#घोषणा REG_G_CAPZOOM_IN_HEIGHT		0x7000049e
#घोषणा REG_G_CAPZOOM_IN_XOFFS		0x700004a0
#घोषणा REG_G_CAPZOOM_IN_YOFFS		0x700004a2

/* n = 0...4 */
#घोषणा REG_USER_SHARPNESS(n)		(0x70000a28 + (n) * 0xb6)

/* Reduce sharpness range क्रम user space API */
#घोषणा SHARPNESS_DIV			8208
#घोषणा TOK_TERM			0xffffffff

/*
 * FIXME: This is copied from s5k6aa, because of no inक्रमmation
 * in the S5K4ECGX datasheet.
 * H/W रेजिस्टर Interface (0xd0000000 - 0xd0000fff)
 */
#घोषणा AHB_MSB_ADDR_PTR		0xfcfc
#घोषणा GEN_REG_OFFSH			0xd000
#घोषणा REG_CMDWR_ADDRH			0x0028
#घोषणा REG_CMDWR_ADDRL			0x002a
#घोषणा REG_CMDRD_ADDRH			0x002c
#घोषणा REG_CMDRD_ADDRL			0x002e
#घोषणा REG_CMDBUF0_ADDR		0x0f12

काष्ठा s5k4ecgx_frmsize अणु
	काष्ठा v4l2_frmsize_discrete size;
	/* Fixed sensor matrix crop rectangle */
	काष्ठा v4l2_rect input_winकरोw;
पूर्ण;

काष्ठा regval_list अणु
	u32 addr;
	u16 val;
पूर्ण;

/*
 * TODO: currently only preview is supported and snapshot (capture)
 * is not implemented yet
 */
अटल स्थिर काष्ठा s5k4ecgx_frmsize s5k4ecgx_prev_sizes[] = अणु
	अणु
		.size = अणु 176, 144 पूर्ण,
		.input_winकरोw = अणु 0x00, 0x00, 0x928, 0x780 पूर्ण,
	पूर्ण, अणु
		.size = अणु 352, 288 पूर्ण,
		.input_winकरोw = अणु 0x00, 0x00, 0x928, 0x780 पूर्ण,
	पूर्ण, अणु
		.size = अणु 640, 480 पूर्ण,
		.input_winकरोw = अणु 0x00, 0x00, 0xa00, 0x780 पूर्ण,
	पूर्ण, अणु
		.size = अणु 720, 480 पूर्ण,
		.input_winकरोw = अणु 0x00, 0x00, 0xa00, 0x6a8 पूर्ण,
	पूर्ण
पूर्ण;

#घोषणा S5K4ECGX_NUM_PREV ARRAY_SIZE(s5k4ecgx_prev_sizes)

काष्ठा s5k4ecgx_pixfmt अणु
	u32 code;
	u32 colorspace;
	/* REG_TC_PCFG_Format रेजिस्टर value */
	u16 reg_p_क्रमmat;
पूर्ण;

/* By शेष value, output from sensor will be YUV422 0-255 */
अटल स्थिर काष्ठा s5k4ecgx_pixfmt s5k4ecgx_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_COLORSPACE_JPEG, 5 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर s5k4ecgx_supply_names[] = अणु
	/*
	 * Usually 2.8V is used क्रम analog घातer (vdda)
	 * and digital IO (vddio, vdddcore)
	 */
	"vdda",
	"vddio",
	"vddcore",
	"vddreg", /* The पूर्णांकernal s5k4ecgx regulator's supply (1.8V) */
पूर्ण;

#घोषणा S5K4ECGX_NUM_SUPPLIES ARRAY_SIZE(s5k4ecgx_supply_names)

क्रमागत s5k4ecgx_gpio_id अणु
	STBY,
	RST,
	GPIO_NUM,
पूर्ण;

काष्ठा s5k4ecgx अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_ctrl_handler handler;

	काष्ठा s5k4ecgx_platक्रमm_data *pdata;
	स्थिर काष्ठा s5k4ecgx_pixfmt *curr_pixfmt;
	स्थिर काष्ठा s5k4ecgx_frmsize *curr_frmsize;
	काष्ठा mutex lock;
	u8 streaming;
	u8 set_params;

	काष्ठा regulator_bulk_data supplies[S5K4ECGX_NUM_SUPPLIES];
	काष्ठा s5k4ecgx_gpio gpio[GPIO_NUM];
पूर्ण;

अटल अंतरभूत काष्ठा s5k4ecgx *to_s5k4ecgx(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा s5k4ecgx, sd);
पूर्ण

अटल पूर्णांक s5k4ecgx_i2c_पढ़ो(काष्ठा i2c_client *client, u16 addr, u16 *val)
अणु
	u8 wbuf[2] = अणु addr >> 8, addr & 0xff पूर्ण;
	काष्ठा i2c_msg msg[2];
	u8 rbuf[2];
	पूर्णांक ret;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 2;
	msg[0].buf = wbuf;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = 2;
	msg[1].buf = rbuf;

	ret = i2c_transfer(client->adapter, msg, 2);
	*val = be16_to_cpu(*((__be16 *)rbuf));

	v4l2_dbg(4, debug, client, "i2c_read: 0x%04X : 0x%04x\n", addr, *val);

	वापस ret == 2 ? 0 : ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 addr, u16 val)
अणु
	u8 buf[4] = अणु addr >> 8, addr & 0xff, val >> 8, val & 0xff पूर्ण;

	पूर्णांक ret = i2c_master_send(client, buf, 4);
	v4l2_dbg(4, debug, client, "i2c_write: 0x%04x : 0x%04x\n", addr, val);

	वापस ret == 4 ? 0 : ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_ग_लिखो(काष्ठा i2c_client *client, u32 addr, u16 val)
अणु
	u16 high = addr >> 16, low = addr & 0xffff;
	पूर्णांक ret;

	v4l2_dbg(3, debug, client, "write: 0x%08x : 0x%04x\n", addr, val);

	ret = s5k4ecgx_i2c_ग_लिखो(client, REG_CMDWR_ADDRH, high);
	अगर (!ret)
		ret = s5k4ecgx_i2c_ग_लिखो(client, REG_CMDWR_ADDRL, low);
	अगर (!ret)
		ret = s5k4ecgx_i2c_ग_लिखो(client, REG_CMDBUF0_ADDR, val);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_पढ़ो(काष्ठा i2c_client *client, u32 addr, u16 *val)
अणु
	u16 high = addr >> 16, low =  addr & 0xffff;
	पूर्णांक ret;

	ret = s5k4ecgx_i2c_ग_लिखो(client, REG_CMDRD_ADDRH, high);
	अगर (!ret)
		ret = s5k4ecgx_i2c_ग_लिखो(client, REG_CMDRD_ADDRL, low);
	अगर (!ret)
		ret = s5k4ecgx_i2c_पढ़ो(client, REG_CMDBUF0_ADDR, val);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_पढ़ो_fw_ver(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u16 hw_rev, fw_ver = 0;
	पूर्णांक ret;

	ret = s5k4ecgx_पढ़ो(client, REG_FW_VERSION, &fw_ver);
	अगर (ret < 0 || fw_ver != S5K4ECGX_FW_VERSION) अणु
		v4l2_err(sd, "FW version check failed!\n");
		वापस -ENODEV;
	पूर्ण

	ret = s5k4ecgx_पढ़ो(client, REG_FW_REVISION, &hw_rev);
	अगर (ret < 0)
		वापस ret;

	v4l2_info(sd, "chip found FW ver: 0x%x, HW rev: 0x%x\n",
						fw_ver, hw_rev);
	वापस 0;
पूर्ण

अटल पूर्णांक s5k4ecgx_set_ahb_address(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	/* Set APB peripherals start address */
	ret = s5k4ecgx_i2c_ग_लिखो(client, AHB_MSB_ADDR_PTR, GEN_REG_OFFSH);
	अगर (ret < 0)
		वापस ret;
	/*
	 * FIXME: This is copied from s5k6aa, because of no inक्रमmation
	 * in s5k4ecgx's datasheet.
	 * sw_reset is activated to put device पूर्णांकo idle status
	 */
	ret = s5k4ecgx_i2c_ग_लिखो(client, 0x0010, 0x0001);
	अगर (ret < 0)
		वापस ret;

	ret = s5k4ecgx_i2c_ग_लिखो(client, 0x1030, 0x0000);
	अगर (ret < 0)
		वापस ret;
	/* Halt ARM CPU */
	वापस s5k4ecgx_i2c_ग_लिखो(client, 0x0014, 0x0001);
पूर्ण

#घोषणा FW_CRC_SIZE	4
/* Register address, value are 4, 2 bytes */
#घोषणा FW_RECORD_SIZE	6
/*
 * The firmware has following क्रमmat:
 * < total number of records (4 bytes + 2 bytes padding) N >,
 * < record 0 >, ..., < record N - 1 >, < CRC32-CCITT (4-bytes) >,
 * where "record" is a 4-byte रेजिस्टर address followed by 2-byte
 * रेजिस्टर value (little endian).
 * The firmware generator can be found in following git repository:
 * git://git.linaro.org/people/sangwook/fimc-v4l2-app.git
 */
अटल पूर्णांक s5k4ecgx_load_firmware(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *ptr;
	पूर्णांक err, i, regs_num;
	u32 addr, crc, crc_file, addr_inc = 0;
	u16 val;

	err = request_firmware(&fw, S5K4ECGX_FIRMWARE, sd->v4l2_dev->dev);
	अगर (err) अणु
		v4l2_err(sd, "Failed to read firmware %s\n", S5K4ECGX_FIRMWARE);
		वापस err;
	पूर्ण
	regs_num = get_unaligned_le32(fw->data);

	v4l2_dbg(3, debug, sd, "FW: %s size %zu register sets %d\n",
		 S5K4ECGX_FIRMWARE, fw->size, regs_num);

	regs_num++; /* Add header */
	अगर (fw->size != regs_num * FW_RECORD_SIZE + FW_CRC_SIZE) अणु
		err = -EINVAL;
		जाओ fw_out;
	पूर्ण
	crc_file = get_unaligned_le32(fw->data + regs_num * FW_RECORD_SIZE);
	crc = crc32_le(~0, fw->data, regs_num * FW_RECORD_SIZE);
	अगर (crc != crc_file) अणु
		v4l2_err(sd, "FW: invalid crc (%#x:%#x)\n", crc, crc_file);
		err = -EINVAL;
		जाओ fw_out;
	पूर्ण
	ptr = fw->data + FW_RECORD_SIZE;
	क्रम (i = 1; i < regs_num; i++) अणु
		addr = get_unaligned_le32(ptr);
		ptr += माप(u32);
		val = get_unaligned_le16(ptr);
		ptr += माप(u16);
		अगर (addr - addr_inc != 2)
			err = s5k4ecgx_ग_लिखो(client, addr, val);
		अन्यथा
			err = s5k4ecgx_i2c_ग_लिखो(client, REG_CMDBUF0_ADDR, val);
		अगर (err)
			अवरोध;
		addr_inc = addr;
	पूर्ण
fw_out:
	release_firmware(fw);
	वापस err;
पूर्ण

/* Set preview and capture input winकरोw */
अटल पूर्णांक s5k4ecgx_set_input_winकरोw(काष्ठा i2c_client *c,
				     स्थिर काष्ठा v4l2_rect *r)
अणु
	पूर्णांक ret;

	ret = s5k4ecgx_ग_लिखो(c, REG_G_PREV_IN_WIDTH, r->width);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_PREV_IN_HEIGHT, r->height);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_PREV_IN_XOFFS, r->left);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_PREV_IN_YOFFS, r->top);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_CAP_IN_WIDTH, r->width);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_CAP_IN_HEIGHT, r->height);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_CAP_IN_XOFFS, r->left);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_CAP_IN_YOFFS, r->top);

	वापस ret;
पूर्ण

/* Set preview and capture zoom input winकरोw */
अटल पूर्णांक s5k4ecgx_set_zoom_winकरोw(काष्ठा i2c_client *c,
				    स्थिर काष्ठा v4l2_rect *r)
अणु
	पूर्णांक ret;

	ret = s5k4ecgx_ग_लिखो(c, REG_G_PREVZOOM_IN_WIDTH, r->width);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_PREVZOOM_IN_HEIGHT, r->height);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_PREVZOOM_IN_XOFFS, r->left);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_PREVZOOM_IN_YOFFS, r->top);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_CAPZOOM_IN_WIDTH, r->width);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_CAPZOOM_IN_HEIGHT, r->height);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_CAPZOOM_IN_XOFFS, r->left);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(c, REG_G_CAPZOOM_IN_YOFFS, r->top);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_set_output_framefmt(काष्ठा s5k4ecgx *priv)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&priv->sd);
	पूर्णांक ret;

	ret = s5k4ecgx_ग_लिखो(client, REG_P_OUT_WIDTH(0),
			     priv->curr_frmsize->size.width);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_P_OUT_HEIGHT(0),
				     priv->curr_frmsize->size.height);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_P_FMT(0),
				     priv->curr_pixfmt->reg_p_क्रमmat);
	वापस ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_init_sensor(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक ret;

	ret = s5k4ecgx_set_ahb_address(sd);

	/* The delay is from manufacturer's settings */
	msleep(100);

	अगर (!ret)
		ret = s5k4ecgx_load_firmware(sd);
	अगर (ret)
		v4l2_err(sd, "Failed to write initial settings\n");

	वापस ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_gpio_set_value(काष्ठा s5k4ecgx *priv, पूर्णांक id, u32 val)
अणु
	अगर (!gpio_is_valid(priv->gpio[id].gpio))
		वापस 0;
	gpio_set_value(priv->gpio[id].gpio, val);

	वापस 1;
पूर्ण

अटल पूर्णांक __s5k4ecgx_घातer_on(काष्ठा s5k4ecgx *priv)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(S5K4ECGX_NUM_SUPPLIES, priv->supplies);
	अगर (ret)
		वापस ret;
	usleep_range(30, 50);

	/* The polarity of STBY is controlled by TSP */
	अगर (s5k4ecgx_gpio_set_value(priv, STBY, priv->gpio[STBY].level))
		usleep_range(30, 50);

	अगर (s5k4ecgx_gpio_set_value(priv, RST, priv->gpio[RST].level))
		usleep_range(30, 50);

	वापस 0;
पूर्ण

अटल पूर्णांक __s5k4ecgx_घातer_off(काष्ठा s5k4ecgx *priv)
अणु
	अगर (s5k4ecgx_gpio_set_value(priv, RST, !priv->gpio[RST].level))
		usleep_range(30, 50);

	अगर (s5k4ecgx_gpio_set_value(priv, STBY, !priv->gpio[STBY].level))
		usleep_range(30, 50);

	priv->streaming = 0;

	वापस regulator_bulk_disable(S5K4ECGX_NUM_SUPPLIES, priv->supplies);
पूर्ण

/* Find nearest matching image pixel size. */
अटल पूर्णांक s5k4ecgx_try_frame_size(काष्ठा v4l2_mbus_framefmt *mf,
				  स्थिर काष्ठा s5k4ecgx_frmsize **size)
अणु
	अचिन्हित पूर्णांक min_err = ~0;
	पूर्णांक i = ARRAY_SIZE(s5k4ecgx_prev_sizes);
	स्थिर काष्ठा s5k4ecgx_frmsize *fsize = &s5k4ecgx_prev_sizes[0],
		*match = शून्य;

	जबतक (i--) अणु
		पूर्णांक err = असल(fsize->size.width - mf->width)
				+ असल(fsize->size.height - mf->height);
		अगर (err < min_err) अणु
			min_err = err;
			match = fsize;
		पूर्ण
		fsize++;
	पूर्ण
	अगर (match) अणु
		mf->width  = match->size.width;
		mf->height = match->size.height;
		अगर (size)
			*size = match;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक s5k4ecgx_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(s5k4ecgx_क्रमmats))
		वापस -EINVAL;
	code->code = s5k4ecgx_क्रमmats[code->index].code;

	वापस 0;
पूर्ण

अटल पूर्णांक s5k4ecgx_get_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5k4ecgx *priv = to_s5k4ecgx(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		अगर (cfg) अणु
			mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
			fmt->क्रमmat = *mf;
		पूर्ण
		वापस 0;
	पूर्ण

	mf = &fmt->क्रमmat;

	mutex_lock(&priv->lock);
	mf->width = priv->curr_frmsize->size.width;
	mf->height = priv->curr_frmsize->size.height;
	mf->code = priv->curr_pixfmt->code;
	mf->colorspace = priv->curr_pixfmt->colorspace;
	mf->field = V4L2_FIELD_NONE;
	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा s5k4ecgx_pixfmt *s5k4ecgx_try_fmt(काष्ठा v4l2_subdev *sd,
					    काष्ठा v4l2_mbus_framefmt *mf)
अणु
	पूर्णांक i = ARRAY_SIZE(s5k4ecgx_क्रमmats);

	जबतक (--i)
		अगर (mf->code == s5k4ecgx_क्रमmats[i].code)
			अवरोध;
	mf->code = s5k4ecgx_क्रमmats[i].code;

	वापस &s5k4ecgx_क्रमmats[i];
पूर्ण

अटल पूर्णांक s5k4ecgx_set_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5k4ecgx *priv = to_s5k4ecgx(sd);
	स्थिर काष्ठा s5k4ecgx_frmsize *fsize = शून्य;
	स्थिर काष्ठा s5k4ecgx_pixfmt *pf;
	काष्ठा v4l2_mbus_framefmt *mf;
	पूर्णांक ret = 0;

	pf = s5k4ecgx_try_fmt(sd, &fmt->क्रमmat);
	s5k4ecgx_try_frame_size(&fmt->क्रमmat, &fsize);
	fmt->क्रमmat.colorspace = V4L2_COLORSPACE_JPEG;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		अगर (cfg) अणु
			mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
			*mf = fmt->क्रमmat;
		पूर्ण
		वापस 0;
	पूर्ण

	mutex_lock(&priv->lock);
	अगर (!priv->streaming) अणु
		priv->curr_frmsize = fsize;
		priv->curr_pixfmt = pf;
		priv->set_params = 1;
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s5k4ecgx_pad_ops = अणु
	.क्रमागत_mbus_code	= s5k4ecgx_क्रमागत_mbus_code,
	.get_fmt	= s5k4ecgx_get_fmt,
	.set_fmt	= s5k4ecgx_set_fmt,
पूर्ण;

/*
 * V4L2 subdev controls
 */
अटल पूर्णांक s5k4ecgx_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = &container_of(ctrl->handler, काष्ठा s5k4ecgx,
						handler)->sd;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा s5k4ecgx *priv = to_s5k4ecgx(sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	v4l2_dbg(1, debug, sd, "ctrl: 0x%x, value: %d\n", ctrl->id, ctrl->val);

	mutex_lock(&priv->lock);
	चयन (ctrl->id) अणु
	हाल V4L2_CID_CONTRAST:
		err = s5k4ecgx_ग_लिखो(client, REG_USER_CONTRAST, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		err = s5k4ecgx_ग_लिखो(client, REG_USER_SATURATION, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SHARPNESS:
		/* TODO: Revisit, is this setting क्रम all presets ? */
		क्रम (i = 0; i < 4 && !err; i++)
			err = s5k4ecgx_ग_लिखो(client, REG_USER_SHARPNESS(i),
					     ctrl->val * SHARPNESS_DIV);
		अवरोध;

	हाल V4L2_CID_BRIGHTNESS:
		err = s5k4ecgx_ग_लिखो(client, REG_USER_BRIGHTNESS, ctrl->val);
		अवरोध;
	पूर्ण
	mutex_unlock(&priv->lock);
	अगर (err < 0)
		v4l2_err(sd, "Failed to write s_ctrl err %d\n", err);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops s5k4ecgx_ctrl_ops = अणु
	.s_ctrl = s5k4ecgx_s_ctrl,
पूर्ण;

/*
 * Reading s5k4ecgx version inक्रमmation
 */
अटल पूर्णांक s5k4ecgx_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक ret;
	काष्ठा s5k4ecgx *priv = to_s5k4ecgx(sd);

	mutex_lock(&priv->lock);
	ret = __s5k4ecgx_घातer_on(priv);
	अगर (!ret) अणु
		ret = s5k4ecgx_पढ़ो_fw_ver(sd);
		__s5k4ecgx_घातer_off(priv);
	पूर्ण
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

/*
 * V4L2 subdev पूर्णांकernal operations
 */
अटल पूर्णांक s5k4ecgx_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	mf->width = s5k4ecgx_prev_sizes[0].size.width;
	mf->height = s5k4ecgx_prev_sizes[0].size.height;
	mf->code = s5k4ecgx_क्रमmats[0].code;
	mf->colorspace = V4L2_COLORSPACE_JPEG;
	mf->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops s5k4ecgx_subdev_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = s5k4ecgx_रेजिस्टरed,
	.खोलो = s5k4ecgx_खोलो,
पूर्ण;

अटल पूर्णांक s5k4ecgx_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5k4ecgx *priv = to_s5k4ecgx(sd);
	पूर्णांक ret;

	v4l2_dbg(1, debug, sd, "Switching %s\n", on ? "on" : "off");

	अगर (on) अणु
		ret = __s5k4ecgx_घातer_on(priv);
		अगर (ret < 0)
			वापस ret;
		/* Time to stabilize sensor */
		msleep(100);
		ret = s5k4ecgx_init_sensor(sd);
		अगर (ret < 0)
			__s5k4ecgx_घातer_off(priv);
		अन्यथा
			priv->set_params = 1;
	पूर्ण अन्यथा अणु
		ret = __s5k4ecgx_घातer_off(priv);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_log_status(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_ctrl_handler_log_status(sd->ctrl_handler, sd->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops s5k4ecgx_core_ops = अणु
	.s_घातer	= s5k4ecgx_s_घातer,
	.log_status	= s5k4ecgx_log_status,
पूर्ण;

अटल पूर्णांक __s5k4ecgx_s_params(काष्ठा s5k4ecgx *priv)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&priv->sd);
	स्थिर काष्ठा v4l2_rect *crop_rect = &priv->curr_frmsize->input_winकरोw;
	पूर्णांक ret;

	ret = s5k4ecgx_set_input_winकरोw(client, crop_rect);
	अगर (!ret)
		ret = s5k4ecgx_set_zoom_winकरोw(client, crop_rect);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_G_INPUTS_CHANGE_REQ, 1);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, 0x70000a1e, 0x28);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, 0x70000ad4, 0x3c);
	अगर (!ret)
		ret = s5k4ecgx_set_output_framefmt(priv);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_P_PVI_MASK(0), 0x52);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_P_FR_TIME_TYPE(0),
				     FR_TIME_DYNAMIC);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_P_FR_TIME_Q_TYPE(0),
				     FR_TIME_Q_BEST_FRRATE);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client,  REG_P_MIN_FR_TIME(0),
				     US_TO_FR_TIME(33300));
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_P_MAX_FR_TIME(0),
				     US_TO_FR_TIME(66600));
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_P_PREV_MIRROR(0), 0);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_P_CAP_MIRROR(0), 0);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_G_ACTIVE_PREV_CFG, 0);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_G_PREV_OPEN_AFTER_CH, 1);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_G_NEW_CFG_SYNC, 1);
	अगर (!ret)
		ret = s5k4ecgx_ग_लिखो(client, REG_G_PREV_CFG_CHG, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक __s5k4ecgx_s_stream(काष्ठा s5k4ecgx *priv, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&priv->sd);
	पूर्णांक ret;

	अगर (on && priv->set_params) अणु
		ret = __s5k4ecgx_s_params(priv);
		अगर (ret < 0)
			वापस ret;
		priv->set_params = 0;
	पूर्ण
	/*
	 * This enables/disables preview stream only. Capture requests
	 * are not supported yet.
	 */
	ret = s5k4ecgx_ग_लिखो(client, REG_G_ENABLE_PREV, on);
	अगर (ret < 0)
		वापस ret;
	वापस s5k4ecgx_ग_लिखो(client, REG_G_ENABLE_PREV_CHG, 1);
पूर्ण

अटल पूर्णांक s5k4ecgx_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5k4ecgx *priv = to_s5k4ecgx(sd);
	पूर्णांक ret = 0;

	v4l2_dbg(1, debug, sd, "Turn streaming %s\n", on ? "on" : "off");

	mutex_lock(&priv->lock);

	अगर (priv->streaming == !on) अणु
		ret = __s5k4ecgx_s_stream(priv, on);
		अगर (!ret)
			priv->streaming = on & 1;
	पूर्ण

	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops s5k4ecgx_video_ops = अणु
	.s_stream = s5k4ecgx_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops s5k4ecgx_ops = अणु
	.core = &s5k4ecgx_core_ops,
	.pad = &s5k4ecgx_pad_ops,
	.video = &s5k4ecgx_video_ops,
पूर्ण;

/*
 * GPIO setup
 */
अटल पूर्णांक s5k4ecgx_config_gpio(पूर्णांक nr, पूर्णांक val, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ flags = val ? GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW;
	पूर्णांक ret;

	अगर (!gpio_is_valid(nr))
		वापस 0;
	ret = gpio_request_one(nr, flags, name);
	अगर (!ret)
		gpio_export(nr, 0);

	वापस ret;
पूर्ण

अटल व्योम s5k4ecgx_मुक्त_gpios(काष्ठा s5k4ecgx *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->gpio); i++) अणु
		अगर (!gpio_is_valid(priv->gpio[i].gpio))
			जारी;
		gpio_मुक्त(priv->gpio[i].gpio);
		priv->gpio[i].gpio = -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक s5k4ecgx_config_gpios(काष्ठा s5k4ecgx *priv,
				  स्थिर काष्ठा s5k4ecgx_platक्रमm_data *pdata)
अणु
	स्थिर काष्ठा s5k4ecgx_gpio *gpio = &pdata->gpio_stby;
	पूर्णांक ret;

	priv->gpio[STBY].gpio = -EINVAL;
	priv->gpio[RST].gpio  = -EINVAL;

	ret = s5k4ecgx_config_gpio(gpio->gpio, gpio->level, "S5K4ECGX_STBY");

	अगर (ret) अणु
		s5k4ecgx_मुक्त_gpios(priv);
		वापस ret;
	पूर्ण
	priv->gpio[STBY] = *gpio;
	अगर (gpio_is_valid(gpio->gpio))
		gpio_set_value(gpio->gpio, 0);

	gpio = &pdata->gpio_reset;

	ret = s5k4ecgx_config_gpio(gpio->gpio, gpio->level, "S5K4ECGX_RST");
	अगर (ret) अणु
		s5k4ecgx_मुक्त_gpios(priv);
		वापस ret;
	पूर्ण
	priv->gpio[RST] = *gpio;
	अगर (gpio_is_valid(gpio->gpio))
		gpio_set_value(gpio->gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक s5k4ecgx_init_v4l2_ctrls(काष्ठा s5k4ecgx *priv)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &s5k4ecgx_ctrl_ops;
	काष्ठा v4l2_ctrl_handler *hdl = &priv->handler;
	पूर्णांक ret;

	ret = v4l2_ctrl_handler_init(hdl, 4);
	अगर (ret)
		वापस ret;

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS, -208, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SATURATION, -127, 127, 1, 0);

	/* Sharpness शेष is 24612, and then (24612/SHARPNESS_DIV) = 2 */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SHARPNESS, -32704/SHARPNESS_DIV,
			  24612/SHARPNESS_DIV, 1, 2);
	अगर (hdl->error) अणु
		ret = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण
	priv->sd.ctrl_handler = hdl;

	वापस 0;
पूर्ण;

अटल पूर्णांक s5k4ecgx_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा s5k4ecgx_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा v4l2_subdev *sd;
	काष्ठा s5k4ecgx *priv;
	पूर्णांक ret, i;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "platform data is missing!\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&client->dev, माप(काष्ठा s5k4ecgx), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->lock);
	priv->streaming = 0;

	sd = &priv->sd;
	/* Registering subdev */
	v4l2_i2c_subdev_init(sd, client, &s5k4ecgx_ops);
	/* Static name; NEVER use in new drivers! */
	strscpy(sd->name, S5K4ECGX_DRIVER_NAME, माप(sd->name));

	sd->पूर्णांकernal_ops = &s5k4ecgx_subdev_पूर्णांकernal_ops;
	/* Support v4l2 sub-device user space API */
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	priv->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &priv->pad);
	अगर (ret)
		वापस ret;

	ret = s5k4ecgx_config_gpios(priv, pdata);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to set gpios\n");
		जाओ out_err1;
	पूर्ण
	क्रम (i = 0; i < S5K4ECGX_NUM_SUPPLIES; i++)
		priv->supplies[i].supply = s5k4ecgx_supply_names[i];

	ret = devm_regulator_bulk_get(&client->dev, S5K4ECGX_NUM_SUPPLIES,
				 priv->supplies);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to get regulators\n");
		जाओ out_err2;
	पूर्ण
	ret = s5k4ecgx_init_v4l2_ctrls(priv);
	अगर (ret)
		जाओ out_err2;

	priv->curr_pixfmt = &s5k4ecgx_क्रमmats[0];
	priv->curr_frmsize = &s5k4ecgx_prev_sizes[0];

	वापस 0;

out_err2:
	s5k4ecgx_मुक्त_gpios(priv);
out_err1:
	media_entity_cleanup(&priv->sd.entity);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k4ecgx_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा s5k4ecgx *priv = to_s5k4ecgx(sd);

	mutex_destroy(&priv->lock);
	s5k4ecgx_मुक्त_gpios(priv);
	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&priv->handler);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id s5k4ecgx_id[] = अणु
	अणु S5K4ECGX_DRIVER_NAME, 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s5k4ecgx_id);

अटल काष्ठा i2c_driver v4l2_i2c_driver = अणु
	.driver = अणु
		.name = S5K4ECGX_DRIVER_NAME,
	पूर्ण,
	.probe = s5k4ecgx_probe,
	.हटाओ = s5k4ecgx_हटाओ,
	.id_table = s5k4ecgx_id,
पूर्ण;

module_i2c_driver(v4l2_i2c_driver);

MODULE_DESCRIPTION("Samsung S5K4ECGX 5MP SOC camera");
MODULE_AUTHOR("Sangwook Lee <sangwook.lee@linaro.org>");
MODULE_AUTHOR("Seok-Young Jang <quartz.jang@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(S5K4ECGX_FIRMWARE);

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung LSI S5C73M3 8M pixel camera driver
 *
 * Copyright (C) 2012, Samsung Electronics, Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 * Andrzej Hajda <a.hajda@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/media.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/videodev2.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/i2c/s5c73m3.h>
#समावेश <media/v4l2-fwnode.h>

#समावेश "s5c73m3.h"

पूर्णांक s5c73m3_dbg;
module_param_named(debug, s5c73m3_dbg, पूर्णांक, 0644);

अटल पूर्णांक boot_from_rom = 1;
module_param(boot_from_rom, पूर्णांक, 0644);

अटल पूर्णांक update_fw;
module_param(update_fw, पूर्णांक, 0644);

#घोषणा S5C73M3_EMBEDDED_DATA_MAXLEN	SZ_4K
#घोषणा S5C73M3_MIPI_DATA_LANES		4
#घोषणा S5C73M3_CLK_NAME		"cis_extclk"

अटल स्थिर अक्षर * स्थिर s5c73m3_supply_names[S5C73M3_MAX_SUPPLIES] = अणु
	"vdd-int",	/* Digital Core supply (1.2V), CAM_ISP_CORE_1.2V */
	"vdda",		/* Analog Core supply (1.2V), CAM_SENSOR_CORE_1.2V */
	"vdd-reg",	/* Regulator input supply (2.8V), CAM_SENSOR_A2.8V */
	"vddio-host",	/* Digital Host I/O घातer supply (1.8V...2.8V),
			   CAM_ISP_SENSOR_1.8V */
	"vddio-cis",	/* Digital CIS I/O घातer (1.2V...1.8V),
			   CAM_ISP_MIPI_1.2V */
	"vdd-af",	/* Lens, CAM_AF_2.8V */
पूर्ण;

अटल स्थिर काष्ठा s5c73m3_frame_size s5c73m3_isp_resolutions[] = अणु
	अणु 320,	240,	COMM_CHG_MODE_YUV_320_240 पूर्ण,
	अणु 352,	288,	COMM_CHG_MODE_YUV_352_288 पूर्ण,
	अणु 640,	480,	COMM_CHG_MODE_YUV_640_480 पूर्ण,
	अणु 880,	720,	COMM_CHG_MODE_YUV_880_720 पूर्ण,
	अणु 960,	720,	COMM_CHG_MODE_YUV_960_720 पूर्ण,
	अणु 1008,	672,	COMM_CHG_MODE_YUV_1008_672 पूर्ण,
	अणु 1184,	666,	COMM_CHG_MODE_YUV_1184_666 पूर्ण,
	अणु 1280,	720,	COMM_CHG_MODE_YUV_1280_720 पूर्ण,
	अणु 1536,	864,	COMM_CHG_MODE_YUV_1536_864 पूर्ण,
	अणु 1600,	1200,	COMM_CHG_MODE_YUV_1600_1200 पूर्ण,
	अणु 1632,	1224,	COMM_CHG_MODE_YUV_1632_1224 पूर्ण,
	अणु 1920,	1080,	COMM_CHG_MODE_YUV_1920_1080 पूर्ण,
	अणु 1920,	1440,	COMM_CHG_MODE_YUV_1920_1440 पूर्ण,
	अणु 2304,	1296,	COMM_CHG_MODE_YUV_2304_1296 पूर्ण,
	अणु 3264,	2448,	COMM_CHG_MODE_YUV_3264_2448 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा s5c73m3_frame_size s5c73m3_jpeg_resolutions[] = अणु
	अणु 640,	480,	COMM_CHG_MODE_JPEG_640_480 पूर्ण,
	अणु 800,	450,	COMM_CHG_MODE_JPEG_800_450 पूर्ण,
	अणु 800,	600,	COMM_CHG_MODE_JPEG_800_600 पूर्ण,
	अणु 1024,	768,	COMM_CHG_MODE_JPEG_1024_768 पूर्ण,
	अणु 1280,	720,	COMM_CHG_MODE_JPEG_1280_720 पूर्ण,
	अणु 1280,	960,	COMM_CHG_MODE_JPEG_1280_960 पूर्ण,
	अणु 1600,	900,	COMM_CHG_MODE_JPEG_1600_900 पूर्ण,
	अणु 1600,	1200,	COMM_CHG_MODE_JPEG_1600_1200 पूर्ण,
	अणु 2048,	1152,	COMM_CHG_MODE_JPEG_2048_1152 पूर्ण,
	अणु 2048,	1536,	COMM_CHG_MODE_JPEG_2048_1536 पूर्ण,
	अणु 2560,	1440,	COMM_CHG_MODE_JPEG_2560_1440 पूर्ण,
	अणु 2560,	1920,	COMM_CHG_MODE_JPEG_2560_1920 पूर्ण,
	अणु 3264,	1836,	COMM_CHG_MODE_JPEG_3264_1836 पूर्ण,
	अणु 3264,	2176,	COMM_CHG_MODE_JPEG_3264_2176 पूर्ण,
	अणु 3264,	2448,	COMM_CHG_MODE_JPEG_3264_2448 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा s5c73m3_frame_size * स्थिर s5c73m3_resolutions[] = अणु
	[RES_ISP] = s5c73m3_isp_resolutions,
	[RES_JPEG] = s5c73m3_jpeg_resolutions
पूर्ण;

अटल स्थिर पूर्णांक s5c73m3_resolutions_len[] = अणु
	[RES_ISP] = ARRAY_SIZE(s5c73m3_isp_resolutions),
	[RES_JPEG] = ARRAY_SIZE(s5c73m3_jpeg_resolutions)
पूर्ण;

अटल स्थिर काष्ठा s5c73m3_पूर्णांकerval s5c73m3_पूर्णांकervals[] = अणु
	अणु COMM_FRAME_RATE_FIXED_7FPS, अणु142857, 1000000पूर्ण, अणु3264, 2448पूर्ण पूर्ण,
	अणु COMM_FRAME_RATE_FIXED_15FPS, अणु66667, 1000000पूर्ण, अणु3264, 2448पूर्ण पूर्ण,
	अणु COMM_FRAME_RATE_FIXED_20FPS, अणु50000, 1000000पूर्ण, अणु2304, 1296पूर्ण पूर्ण,
	अणु COMM_FRAME_RATE_FIXED_30FPS, अणु33333, 1000000पूर्ण, अणु2304, 1296पूर्ण पूर्ण,
पूर्ण;

#घोषणा S5C73M3_DEFAULT_FRAME_INTERVAL 3 /* 30 fps */

अटल व्योम s5c73m3_fill_mbus_fmt(काष्ठा v4l2_mbus_framefmt *mf,
				  स्थिर काष्ठा s5c73m3_frame_size *fs,
				  u32 code)
अणु
	mf->width = fs->width;
	mf->height = fs->height;
	mf->code = code;
	mf->colorspace = V4L2_COLORSPACE_JPEG;
	mf->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक s5c73m3_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 addr, u16 data)
अणु
	u8 buf[4] = अणु addr >> 8, addr & 0xff, data >> 8, data & 0xff पूर्ण;

	पूर्णांक ret = i2c_master_send(client, buf, माप(buf));

	v4l_dbg(4, s5c73m3_dbg, client, "%s: addr 0x%04x, data 0x%04x\n",
		 __func__, addr, data);

	अगर (ret == 4)
		वापस 0;

	वापस ret < 0 ? ret : -EREMOTEIO;
पूर्ण

अटल पूर्णांक s5c73m3_i2c_पढ़ो(काष्ठा i2c_client *client, u16 addr, u16 *data)
अणु
	पूर्णांक ret;
	u8 rbuf[2], wbuf[2] = अणु addr >> 8, addr & 0xff पूर्ण;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = माप(wbuf),
			.buf = wbuf
		पूर्ण, अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = माप(rbuf),
			.buf = rbuf
		पूर्ण
	पूर्ण;
	/*
	 * Issue repeated START after writing 2 address bytes and
	 * just one STOP only after पढ़ोing the data bytes.
	 */
	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret == 2) अणु
		*data = be16_to_cpup((__be16 *)rbuf);
		v4l2_dbg(4, s5c73m3_dbg, client,
			 "%s: addr: 0x%04x, data: 0x%04x\n",
			 __func__, addr, *data);
		वापस 0;
	पूर्ण

	v4l2_err(client, "I2C read failed: addr: %04x, (%d)\n", addr, ret);

	वापस ret >= 0 ? -EREMOTEIO : ret;
पूर्ण

पूर्णांक s5c73m3_ग_लिखो(काष्ठा s5c73m3 *state, u32 addr, u16 data)
अणु
	काष्ठा i2c_client *client = state->i2c_client;
	पूर्णांक ret;

	अगर ((addr ^ state->i2c_ग_लिखो_address) & 0xffff0000) अणु
		ret = s5c73m3_i2c_ग_लिखो(client, REG_CMDWR_ADDRH, addr >> 16);
		अगर (ret < 0) अणु
			state->i2c_ग_लिखो_address = 0;
			वापस ret;
		पूर्ण
	पूर्ण

	अगर ((addr ^ state->i2c_ग_लिखो_address) & 0xffff) अणु
		ret = s5c73m3_i2c_ग_लिखो(client, REG_CMDWR_ADDRL, addr & 0xffff);
		अगर (ret < 0) अणु
			state->i2c_ग_लिखो_address = 0;
			वापस ret;
		पूर्ण
	पूर्ण

	state->i2c_ग_लिखो_address = addr;

	ret = s5c73m3_i2c_ग_लिखो(client, REG_CMDBUF_ADDR, data);
	अगर (ret < 0)
		वापस ret;

	state->i2c_ग_लिखो_address += 2;

	वापस ret;
पूर्ण

पूर्णांक s5c73m3_पढ़ो(काष्ठा s5c73m3 *state, u32 addr, u16 *data)
अणु
	काष्ठा i2c_client *client = state->i2c_client;
	पूर्णांक ret;

	अगर ((addr ^ state->i2c_पढ़ो_address) & 0xffff0000) अणु
		ret = s5c73m3_i2c_ग_लिखो(client, REG_CMDRD_ADDRH, addr >> 16);
		अगर (ret < 0) अणु
			state->i2c_पढ़ो_address = 0;
			वापस ret;
		पूर्ण
	पूर्ण

	अगर ((addr ^ state->i2c_पढ़ो_address) & 0xffff) अणु
		ret = s5c73m3_i2c_ग_लिखो(client, REG_CMDRD_ADDRL, addr & 0xffff);
		अगर (ret < 0) अणु
			state->i2c_पढ़ो_address = 0;
			वापस ret;
		पूर्ण
	पूर्ण

	state->i2c_पढ़ो_address = addr;

	ret = s5c73m3_i2c_पढ़ो(client, REG_CMDBUF_ADDR, data);
	अगर (ret < 0)
		वापस ret;

	state->i2c_पढ़ो_address += 2;

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_check_status(काष्ठा s5c73m3 *state, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित दीर्घ start = jअगरfies;
	अचिन्हित दीर्घ end = start + msecs_to_jअगरfies(2000);
	पूर्णांक ret;
	u16 status;
	पूर्णांक count = 0;

	करो अणु
		ret = s5c73m3_पढ़ो(state, REG_STATUS, &status);
		अगर (ret < 0 || status == value)
			अवरोध;
		usleep_range(500, 1000);
		++count;
	पूर्ण जबतक (समय_is_after_jअगरfies(end));

	अगर (count > 0)
		v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd,
			 "status check took %dms\n",
			 jअगरfies_to_msecs(jअगरfies - start));

	अगर (ret == 0 && status != value) अणु
		u16 i2c_status = 0;
		u16 i2c_seq_status = 0;

		s5c73m3_पढ़ो(state, REG_I2C_STATUS, &i2c_status);
		s5c73m3_पढ़ो(state, REG_I2C_SEQ_STATUS, &i2c_seq_status);

		v4l2_err(&state->sensor_sd,
			 "wrong status %#x, expected: %#x, i2c_status: %#x/%#x\n",
			 status, value, i2c_status, i2c_seq_status);

		वापस -ETIMEDOUT;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक s5c73m3_isp_command(काष्ठा s5c73m3 *state, u16 command, u16 data)
अणु
	पूर्णांक ret;

	ret = s5c73m3_check_status(state, REG_STATUS_ISP_COMMAND_COMPLETED);
	अगर (ret < 0)
		वापस ret;

	ret = s5c73m3_ग_लिखो(state, 0x00095000, command);
	अगर (ret < 0)
		वापस ret;

	ret = s5c73m3_ग_लिखो(state, 0x00095002, data);
	अगर (ret < 0)
		वापस ret;

	वापस s5c73m3_ग_लिखो(state, REG_STATUS, 0x0001);
पूर्ण

अटल पूर्णांक s5c73m3_isp_comm_result(काष्ठा s5c73m3 *state, u16 command,
				   u16 *data)
अणु
	वापस s5c73m3_पढ़ो(state, COMM_RESULT_OFFSET + command, data);
पूर्ण

अटल पूर्णांक s5c73m3_set_af_softlanding(काष्ठा s5c73m3 *state)
अणु
	अचिन्हित दीर्घ start = jअगरfies;
	u16 af_softlanding;
	पूर्णांक count = 0;
	पूर्णांक ret;
	स्थिर अक्षर *msg;

	ret = s5c73m3_isp_command(state, COMM_AF_SOFTLANDING,
					COMM_AF_SOFTLANDING_ON);
	अगर (ret < 0) अणु
		v4l2_info(&state->sensor_sd, "AF soft-landing failed\n");
		वापस ret;
	पूर्ण

	क्रम (;;) अणु
		ret = s5c73m3_isp_comm_result(state, COMM_AF_SOFTLANDING,
							&af_softlanding);
		अगर (ret < 0) अणु
			msg = "failed";
			अवरोध;
		पूर्ण
		अगर (af_softlanding == COMM_AF_SOFTLANDING_RES_COMPLETE) अणु
			msg = "succeeded";
			अवरोध;
		पूर्ण
		अगर (++count > 100) अणु
			ret = -ETIME;
			msg = "timed out";
			अवरोध;
		पूर्ण
		msleep(25);
	पूर्ण

	v4l2_info(&state->sensor_sd, "AF soft-landing %s after %dms\n",
		  msg, jअगरfies_to_msecs(jअगरfies - start));

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_load_fw(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा s5c73m3 *state = sensor_sd_to_s5c73m3(sd);
	काष्ठा i2c_client *client = state->i2c_client;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;
	अक्षर fw_name[20];

	snम_लिखो(fw_name, माप(fw_name), "SlimISP_%.2s.bin",
							state->fw_file_version);
	ret = request_firmware(&fw, fw_name, &client->dev);
	अगर (ret < 0) अणु
		v4l2_err(sd, "Firmware request failed (%s)\n", fw_name);
		वापस -EINVAL;
	पूर्ण

	v4l2_info(sd, "Loading firmware (%s, %zu B)\n", fw_name, fw->size);

	ret = s5c73m3_spi_ग_लिखो(state, fw->data, fw->size, 64);

	अगर (ret >= 0)
		state->isp_पढ़ोy = 1;
	अन्यथा
		v4l2_err(sd, "SPI write failed\n");

	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_set_frame_size(काष्ठा s5c73m3 *state)
अणु
	स्थिर काष्ठा s5c73m3_frame_size *prev_size =
					state->sensor_pix_size[RES_ISP];
	स्थिर काष्ठा s5c73m3_frame_size *cap_size =
					state->sensor_pix_size[RES_JPEG];
	अचिन्हित पूर्णांक chg_mode;

	v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd,
		 "Preview size: %dx%d, reg_val: 0x%x\n",
		 prev_size->width, prev_size->height, prev_size->reg_val);

	chg_mode = prev_size->reg_val | COMM_CHG_MODE_NEW;

	अगर (state->mbus_code == S5C73M3_JPEG_FMT) अणु
		v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd,
			 "Capture size: %dx%d, reg_val: 0x%x\n",
			 cap_size->width, cap_size->height, cap_size->reg_val);
		chg_mode |= cap_size->reg_val;
	पूर्ण

	वापस s5c73m3_isp_command(state, COMM_CHG_MODE, chg_mode);
पूर्ण

अटल पूर्णांक s5c73m3_set_frame_rate(काष्ठा s5c73m3 *state)
अणु
	पूर्णांक ret;

	अगर (state->ctrls.stabilization->val)
		वापस 0;

	अगर (WARN_ON(state->fiv == शून्य))
		वापस -EINVAL;

	ret = s5c73m3_isp_command(state, COMM_FRAME_RATE, state->fiv->fps_reg);
	अगर (!ret)
		state->apply_fiv = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक __s5c73m3_s_stream(काष्ठा s5c73m3 *state, काष्ठा v4l2_subdev *sd,
								पूर्णांक on)
अणु
	u16 mode;
	पूर्णांक ret;

	अगर (on && state->apply_fmt) अणु
		अगर (state->mbus_code == S5C73M3_JPEG_FMT)
			mode = COMM_IMG_OUTPUT_INTERLEAVED;
		अन्यथा
			mode = COMM_IMG_OUTPUT_YUV;

		ret = s5c73m3_isp_command(state, COMM_IMG_OUTPUT, mode);
		अगर (!ret)
			ret = s5c73m3_set_frame_size(state);
		अगर (ret)
			वापस ret;
		state->apply_fmt = 0;
	पूर्ण

	ret = s5c73m3_isp_command(state, COMM_SENSOR_STREAMING, !!on);
	अगर (ret)
		वापस ret;

	state->streaming = !!on;

	अगर (!on)
		वापस ret;

	अगर (state->apply_fiv) अणु
		ret = s5c73m3_set_frame_rate(state);
		अगर (ret < 0)
			v4l2_err(sd, "Error setting frame rate(%d)\n", ret);
	पूर्ण

	वापस s5c73m3_check_status(state, REG_STATUS_ISP_COMMAND_COMPLETED);
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	पूर्णांक ret;

	mutex_lock(&state->lock);
	ret = __s5c73m3_s_stream(state, sd, on);
	mutex_unlock(&state->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_प्रणाली_status_रुको(काष्ठा s5c73m3 *state, u32 value,
				      अचिन्हित पूर्णांक delay, अचिन्हित पूर्णांक steps)
अणु
	u16 reg = 0;

	जबतक (steps-- > 0) अणु
		पूर्णांक ret = s5c73m3_पढ़ो(state, 0x30100010, &reg);
		अगर (ret < 0)
			वापस ret;
		अगर (reg == value)
			वापस 0;
		usleep_range(delay, delay + 25);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक s5c73m3_पढ़ो_fw_version(काष्ठा s5c73m3 *state)
अणु
	काष्ठा v4l2_subdev *sd = &state->sensor_sd;
	पूर्णांक i, ret;
	u16 data[2];
	पूर्णांक offset;

	offset = state->isp_पढ़ोy ? 0x60 : 0;

	क्रम (i = 0; i < S5C73M3_SENSOR_FW_LEN / 2; i++) अणु
		ret = s5c73m3_पढ़ो(state, offset + i * 2, data);
		अगर (ret < 0)
			वापस ret;
		state->sensor_fw[i * 2] = (अक्षर)(*data & 0xff);
		state->sensor_fw[i * 2 + 1] = (अक्षर)(*data >> 8);
	पूर्ण
	state->sensor_fw[S5C73M3_SENSOR_FW_LEN] = '\0';


	क्रम (i = 0; i < S5C73M3_SENSOR_TYPE_LEN / 2; i++) अणु
		ret = s5c73m3_पढ़ो(state, offset + 6 + i * 2, data);
		अगर (ret < 0)
			वापस ret;
		state->sensor_type[i * 2] = (अक्षर)(*data & 0xff);
		state->sensor_type[i * 2 + 1] = (अक्षर)(*data >> 8);
	पूर्ण
	state->sensor_type[S5C73M3_SENSOR_TYPE_LEN] = '\0';

	ret = s5c73m3_पढ़ो(state, offset + 0x14, data);
	अगर (ret >= 0) अणु
		ret = s5c73m3_पढ़ो(state, offset + 0x16, data + 1);
		अगर (ret >= 0)
			state->fw_size = data[0] + (data[1] << 16);
	पूर्ण

	v4l2_info(sd, "Sensor type: %s, FW version: %s\n",
		  state->sensor_type, state->sensor_fw);
	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_fw_update_from(काष्ठा s5c73m3 *state)
अणु
	काष्ठा v4l2_subdev *sd = &state->sensor_sd;
	u16 status = COMM_FW_UPDATE_NOT_READY;
	पूर्णांक ret;
	पूर्णांक count = 0;

	v4l2_warn(sd, "Updating F-ROM firmware.\n");
	करो अणु
		अगर (status == COMM_FW_UPDATE_NOT_READY) अणु
			ret = s5c73m3_isp_command(state, COMM_FW_UPDATE, 0);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ret = s5c73m3_पढ़ो(state, 0x00095906, &status);
		अगर (ret < 0)
			वापस ret;
		चयन (status) अणु
		हाल COMM_FW_UPDATE_FAIL:
			v4l2_warn(sd, "Updating F-ROM firmware failed.\n");
			वापस -EIO;
		हाल COMM_FW_UPDATE_SUCCESS:
			v4l2_warn(sd, "Updating F-ROM firmware finished.\n");
			वापस 0;
		पूर्ण
		++count;
		msleep(20);
	पूर्ण जबतक (count < 500);

	v4l2_warn(sd, "Updating F-ROM firmware timed-out.\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक s5c73m3_spi_boot(काष्ठा s5c73m3 *state, bool load_fw)
अणु
	काष्ठा v4l2_subdev *sd = &state->sensor_sd;
	पूर्णांक ret;

	/* Run ARM MCU */
	ret = s5c73m3_ग_लिखो(state, 0x30000004, 0xffff);
	अगर (ret < 0)
		वापस ret;

	usleep_range(400, 500);

	/* Check booting status */
	ret = s5c73m3_प्रणाली_status_रुको(state, 0x0c, 100, 3);
	अगर (ret < 0) अणु
		v4l2_err(sd, "booting failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* P,M,S and Boot Mode */
	ret = s5c73m3_ग_लिखो(state, 0x30100014, 0x2146);
	अगर (ret < 0)
		वापस ret;

	ret = s5c73m3_ग_लिखो(state, 0x30100010, 0x210c);
	अगर (ret < 0)
		वापस ret;

	usleep_range(200, 250);

	/* Check SPI status */
	ret = s5c73m3_प्रणाली_status_रुको(state, 0x210d, 100, 300);
	अगर (ret < 0)
		v4l2_err(sd, "SPI not ready: %d\n", ret);

	/* Firmware करोwnload over SPI */
	अगर (load_fw)
		s5c73m3_load_fw(sd);

	/* MCU reset */
	ret = s5c73m3_ग_लिखो(state, 0x30000004, 0xfffd);
	अगर (ret < 0)
		वापस ret;

	/* Remap */
	ret = s5c73m3_ग_लिखो(state, 0x301000a4, 0x0183);
	अगर (ret < 0)
		वापस ret;

	/* MCU restart */
	ret = s5c73m3_ग_लिखो(state, 0x30000004, 0xffff);
	अगर (ret < 0 || !load_fw)
		वापस ret;

	ret = s5c73m3_पढ़ो_fw_version(state);
	अगर (ret < 0)
		वापस ret;

	अगर (load_fw && update_fw) अणु
		ret = s5c73m3_fw_update_from(state);
		update_fw = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_set_timing_रेजिस्टर_क्रम_vdd(काष्ठा s5c73m3 *state)
अणु
	अटल स्थिर u32 regs[][2] = अणु
		अणु 0x30100018, 0x0618 पूर्ण,
		अणु 0x3010001c, 0x10c1 पूर्ण,
		अणु 0x30100020, 0x249e पूर्ण
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		ret = s5c73m3_ग_लिखो(state, regs[i][0], regs[i][1]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम s5c73m3_set_fw_file_version(काष्ठा s5c73m3 *state)
अणु
	चयन (state->sensor_fw[0]) अणु
	हाल 'G':
	हाल 'O':
		state->fw_file_version[0] = 'G';
		अवरोध;
	हाल 'S':
	हाल 'Z':
		state->fw_file_version[0] = 'Z';
		अवरोध;
	पूर्ण

	चयन (state->sensor_fw[1]) अणु
	हाल 'C'...'F':
		state->fw_file_version[1] = state->sensor_fw[1];
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक s5c73m3_get_fw_version(काष्ठा s5c73m3 *state)
अणु
	काष्ठा v4l2_subdev *sd = &state->sensor_sd;
	पूर्णांक ret;

	/* Run ARM MCU */
	ret = s5c73m3_ग_लिखो(state, 0x30000004, 0xffff);
	अगर (ret < 0)
		वापस ret;
	usleep_range(400, 500);

	/* Check booting status */
	ret = s5c73m3_प्रणाली_status_रुको(state, 0x0c, 100, 3);
	अगर (ret < 0) अणु

		v4l2_err(sd, "%s: booting failed: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	/* Change I/O Driver Current in order to पढ़ो from F-ROM */
	ret = s5c73m3_ग_लिखो(state, 0x30100120, 0x0820);
	ret = s5c73m3_ग_लिखो(state, 0x30100124, 0x0820);

	/* Offset Setting */
	ret = s5c73m3_ग_लिखो(state, 0x00010418, 0x0008);

	/* P,M,S and Boot Mode */
	ret = s5c73m3_ग_लिखो(state, 0x30100014, 0x2146);
	अगर (ret < 0)
		वापस ret;
	ret = s5c73m3_ग_लिखो(state, 0x30100010, 0x230c);
	अगर (ret < 0)
		वापस ret;

	usleep_range(200, 250);

	/* Check SPI status */
	ret = s5c73m3_प्रणाली_status_रुको(state, 0x230e, 100, 300);
	अगर (ret < 0)
		v4l2_err(sd, "SPI not ready: %d\n", ret);

	/* ARM reset */
	ret = s5c73m3_ग_लिखो(state, 0x30000004, 0xfffd);
	अगर (ret < 0)
		वापस ret;

	/* Remap */
	ret = s5c73m3_ग_लिखो(state, 0x301000a4, 0x0183);
	अगर (ret < 0)
		वापस ret;

	s5c73m3_set_timing_रेजिस्टर_क्रम_vdd(state);

	ret = s5c73m3_पढ़ो_fw_version(state);

	s5c73m3_set_fw_file_version(state);

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_rom_boot(काष्ठा s5c73m3 *state, bool load_fw)
अणु
	अटल स्थिर u32 boot_regs[][2] = अणु
		अणु 0x3100010c, 0x0044 पूर्ण,
		अणु 0x31000108, 0x000d पूर्ण,
		अणु 0x31000304, 0x0001 पूर्ण,
		अणु 0x00010000, 0x5800 पूर्ण,
		अणु 0x00010002, 0x0002 पूर्ण,
		अणु 0x31000000, 0x0001 पूर्ण,
		अणु 0x30100014, 0x1b85 पूर्ण,
		अणु 0x30100010, 0x230c पूर्ण
	पूर्ण;
	काष्ठा v4l2_subdev *sd = &state->sensor_sd;
	पूर्णांक i, ret;

	/* Run ARM MCU */
	ret = s5c73m3_ग_लिखो(state, 0x30000004, 0xffff);
	अगर (ret < 0)
		वापस ret;
	usleep_range(400, 450);

	/* Check booting status */
	ret = s5c73m3_प्रणाली_status_रुको(state, 0x0c, 100, 4);
	अगर (ret < 0) अणु
		v4l2_err(sd, "Booting failed: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(boot_regs); i++) अणु
		ret = s5c73m3_ग_लिखो(state, boot_regs[i][0], boot_regs[i][1]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	msleep(200);

	/* Check the binary पढ़ो status */
	ret = s5c73m3_प्रणाली_status_रुको(state, 0x230e, 1000, 150);
	अगर (ret < 0) अणु
		v4l2_err(sd, "Binary read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* ARM reset */
	ret = s5c73m3_ग_लिखो(state, 0x30000004, 0xfffd);
	अगर (ret < 0)
		वापस ret;
	/* Remap */
	ret = s5c73m3_ग_लिखो(state, 0x301000a4, 0x0183);
	अगर (ret < 0)
		वापस ret;
	/* MCU re-start */
	ret = s5c73m3_ग_लिखो(state, 0x30000004, 0xffff);
	अगर (ret < 0)
		वापस ret;

	state->isp_पढ़ोy = 1;

	वापस s5c73m3_पढ़ो_fw_version(state);
पूर्ण

अटल पूर्णांक s5c73m3_isp_init(काष्ठा s5c73m3 *state)
अणु
	पूर्णांक ret;

	state->i2c_पढ़ो_address = 0;
	state->i2c_ग_लिखो_address = 0;

	ret = s5c73m3_i2c_ग_लिखो(state->i2c_client, AHB_MSB_ADDR_PTR, 0x3310);
	अगर (ret < 0)
		वापस ret;

	अगर (boot_from_rom)
		वापस s5c73m3_rom_boot(state, true);
	अन्यथा
		वापस s5c73m3_spi_boot(state, true);
पूर्ण

अटल स्थिर काष्ठा s5c73m3_frame_size *s5c73m3_find_frame_size(
					काष्ठा v4l2_mbus_framefmt *fmt,
					क्रमागत s5c73m3_resolution_types idx)
अणु
	स्थिर काष्ठा s5c73m3_frame_size *fs;
	स्थिर काष्ठा s5c73m3_frame_size *best_fs;
	पूर्णांक best_dist = पूर्णांक_उच्च;
	पूर्णांक i;

	fs = s5c73m3_resolutions[idx];
	best_fs = शून्य;
	क्रम (i = 0; i < s5c73m3_resolutions_len[idx]; ++i) अणु
		पूर्णांक dist = असल(fs->width - fmt->width) +
						असल(fs->height - fmt->height);
		अगर (dist < best_dist) अणु
			best_dist = dist;
			best_fs = fs;
		पूर्ण
		++fs;
	पूर्ण

	वापस best_fs;
पूर्ण

अटल व्योम s5c73m3_oअगर_try_क्रमmat(काष्ठा s5c73m3 *state,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *fmt,
				   स्थिर काष्ठा s5c73m3_frame_size **fs)
अणु
	काष्ठा v4l2_subdev *sd = &state->sensor_sd;
	u32 code;

	चयन (fmt->pad) अणु
	हाल OIF_ISP_PAD:
		*fs = s5c73m3_find_frame_size(&fmt->क्रमmat, RES_ISP);
		code = S5C73M3_ISP_FMT;
		अवरोध;
	हाल OIF_JPEG_PAD:
		*fs = s5c73m3_find_frame_size(&fmt->क्रमmat, RES_JPEG);
		code = S5C73M3_JPEG_FMT;
		अवरोध;
	हाल OIF_SOURCE_PAD:
	शेष:
		अगर (fmt->क्रमmat.code == S5C73M3_JPEG_FMT)
			code = S5C73M3_JPEG_FMT;
		अन्यथा
			code = S5C73M3_ISP_FMT;

		अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE)
			*fs = state->oअगर_pix_size[RES_ISP];
		अन्यथा
			*fs = s5c73m3_find_frame_size(
						v4l2_subdev_get_try_क्रमmat(sd, cfg,
							OIF_ISP_PAD),
						RES_ISP);
		अवरोध;
	पूर्ण

	s5c73m3_fill_mbus_fmt(&fmt->क्रमmat, *fs, code);
पूर्ण

अटल व्योम s5c73m3_try_क्रमmat(काष्ठा s5c73m3 *state,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt,
			      स्थिर काष्ठा s5c73m3_frame_size **fs)
अणु
	u32 code;

	अगर (fmt->pad == S5C73M3_ISP_PAD) अणु
		*fs = s5c73m3_find_frame_size(&fmt->क्रमmat, RES_ISP);
		code = S5C73M3_ISP_FMT;
	पूर्ण अन्यथा अणु
		*fs = s5c73m3_find_frame_size(&fmt->क्रमmat, RES_JPEG);
		code = S5C73M3_JPEG_FMT;
	पूर्ण

	s5c73m3_fill_mbus_fmt(&fmt->क्रमmat, *fs, code);
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);

	अगर (fi->pad != OIF_SOURCE_PAD)
		वापस -EINVAL;

	mutex_lock(&state->lock);
	fi->पूर्णांकerval = state->fiv->पूर्णांकerval;
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __s5c73m3_set_frame_पूर्णांकerval(काष्ठा s5c73m3 *state,
					काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	स्थिर काष्ठा s5c73m3_frame_size *prev_size =
						state->sensor_pix_size[RES_ISP];
	स्थिर काष्ठा s5c73m3_पूर्णांकerval *fiv = &s5c73m3_पूर्णांकervals[0];
	अचिन्हित पूर्णांक ret, min_err = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक i, fr_समय;

	अगर (fi->पूर्णांकerval.denominator == 0)
		वापस -EINVAL;

	fr_समय = fi->पूर्णांकerval.numerator * 1000 / fi->पूर्णांकerval.denominator;

	क्रम (i = 0; i < ARRAY_SIZE(s5c73m3_पूर्णांकervals); i++) अणु
		स्थिर काष्ठा s5c73m3_पूर्णांकerval *iv = &s5c73m3_पूर्णांकervals[i];

		अगर (prev_size->width > iv->size.width ||
		    prev_size->height > iv->size.height)
			जारी;

		ret = असल(iv->पूर्णांकerval.numerator / 1000 - fr_समय);
		अगर (ret < min_err) अणु
			fiv = iv;
			min_err = ret;
		पूर्ण
	पूर्ण
	state->fiv = fiv;

	v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd,
		 "Changed frame interval to %u us\n", fiv->पूर्णांकerval.numerator);
	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	पूर्णांक ret;

	अगर (fi->pad != OIF_SOURCE_PAD)
		वापस -EINVAL;

	v4l2_dbg(1, s5c73m3_dbg, sd, "Setting %d/%d frame interval\n",
		 fi->पूर्णांकerval.numerator, fi->पूर्णांकerval.denominator);

	mutex_lock(&state->lock);

	ret = __s5c73m3_set_frame_पूर्णांकerval(state, fi);
	अगर (!ret) अणु
		अगर (state->streaming)
			ret = s5c73m3_set_frame_rate(state);
		अन्यथा
			state->apply_fiv = 1;
	पूर्ण
	mutex_unlock(&state->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	स्थिर काष्ठा s5c73m3_पूर्णांकerval *fi;
	पूर्णांक ret = 0;

	अगर (fie->pad != OIF_SOURCE_PAD)
		वापस -EINVAL;
	अगर (fie->index >= ARRAY_SIZE(s5c73m3_पूर्णांकervals))
		वापस -EINVAL;

	mutex_lock(&state->lock);
	fi = &s5c73m3_पूर्णांकervals[fie->index];
	अगर (fie->width > fi->size.width || fie->height > fi->size.height)
		ret = -EINVAL;
	अन्यथा
		fie->पूर्णांकerval = fi->पूर्णांकerval;
	mutex_unlock(&state->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_get_pad_code(पूर्णांक pad, पूर्णांक index)
अणु
	अगर (pad == OIF_SOURCE_PAD) अणु
		अगर (index > 1)
			वापस -EINVAL;
		वापस (index == 0) ? S5C73M3_ISP_FMT : S5C73M3_JPEG_FMT;
	पूर्ण

	अगर (index > 0)
		वापस -EINVAL;

	वापस (pad == OIF_ISP_PAD) ? S5C73M3_ISP_FMT : S5C73M3_JPEG_FMT;
पूर्ण

अटल पूर्णांक s5c73m3_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5c73m3 *state = sensor_sd_to_s5c73m3(sd);
	स्थिर काष्ठा s5c73m3_frame_size *fs;
	u32 code;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		वापस 0;
	पूर्ण

	mutex_lock(&state->lock);

	चयन (fmt->pad) अणु
	हाल S5C73M3_ISP_PAD:
		code = S5C73M3_ISP_FMT;
		fs = state->sensor_pix_size[RES_ISP];
		अवरोध;
	हाल S5C73M3_JPEG_PAD:
		code = S5C73M3_JPEG_FMT;
		fs = state->sensor_pix_size[RES_JPEG];
		अवरोध;
	शेष:
		mutex_unlock(&state->lock);
		वापस -EINVAL;
	पूर्ण
	s5c73m3_fill_mbus_fmt(&fmt->क्रमmat, fs, code);

	mutex_unlock(&state->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	स्थिर काष्ठा s5c73m3_frame_size *fs;
	u32 code;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		वापस 0;
	पूर्ण

	mutex_lock(&state->lock);

	चयन (fmt->pad) अणु
	हाल OIF_ISP_PAD:
		code = S5C73M3_ISP_FMT;
		fs = state->oअगर_pix_size[RES_ISP];
		अवरोध;
	हाल OIF_JPEG_PAD:
		code = S5C73M3_JPEG_FMT;
		fs = state->oअगर_pix_size[RES_JPEG];
		अवरोध;
	हाल OIF_SOURCE_PAD:
		code = state->mbus_code;
		fs = state->oअगर_pix_size[RES_ISP];
		अवरोध;
	शेष:
		mutex_unlock(&state->lock);
		वापस -EINVAL;
	पूर्ण
	s5c73m3_fill_mbus_fmt(&fmt->क्रमmat, fs, code);

	mutex_unlock(&state->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_set_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	स्थिर काष्ठा s5c73m3_frame_size *frame_size = शून्य;
	काष्ठा s5c73m3 *state = sensor_sd_to_s5c73m3(sd);
	काष्ठा v4l2_mbus_framefmt *mf;
	पूर्णांक ret = 0;

	mutex_lock(&state->lock);

	s5c73m3_try_क्रमmat(state, cfg, fmt, &frame_size);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*mf = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		चयन (fmt->pad) अणु
		हाल S5C73M3_ISP_PAD:
			state->sensor_pix_size[RES_ISP] = frame_size;
			अवरोध;
		हाल S5C73M3_JPEG_PAD:
			state->sensor_pix_size[RES_JPEG] = frame_size;
			अवरोध;
		शेष:
			ret = -EBUSY;
		पूर्ण

		अगर (state->streaming)
			ret = -EBUSY;
		अन्यथा
			state->apply_fmt = 1;
	पूर्ण

	mutex_unlock(&state->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_set_fmt(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_subdev_pad_config *cfg,
			 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	स्थिर काष्ठा s5c73m3_frame_size *frame_size = शून्य;
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	काष्ठा v4l2_mbus_framefmt *mf;
	पूर्णांक ret = 0;

	mutex_lock(&state->lock);

	s5c73m3_oअगर_try_क्रमmat(state, cfg, fmt, &frame_size);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*mf = fmt->क्रमmat;
		अगर (fmt->pad == OIF_ISP_PAD) अणु
			mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, OIF_SOURCE_PAD);
			mf->width = fmt->क्रमmat.width;
			mf->height = fmt->क्रमmat.height;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (fmt->pad) अणु
		हाल OIF_ISP_PAD:
			state->oअगर_pix_size[RES_ISP] = frame_size;
			अवरोध;
		हाल OIF_JPEG_PAD:
			state->oअगर_pix_size[RES_JPEG] = frame_size;
			अवरोध;
		हाल OIF_SOURCE_PAD:
			state->mbus_code = fmt->क्रमmat.code;
			अवरोध;
		शेष:
			ret = -EBUSY;
		पूर्ण

		अगर (state->streaming)
			ret = -EBUSY;
		अन्यथा
			state->apply_fmt = 1;
	पूर्ण

	mutex_unlock(&state->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_get_frame_desc(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
				  काष्ठा v4l2_mbus_frame_desc *fd)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	पूर्णांक i;

	अगर (pad != OIF_SOURCE_PAD || fd == शून्य)
		वापस -EINVAL;

	mutex_lock(&state->lock);
	fd->num_entries = 2;
	क्रम (i = 0; i < fd->num_entries; i++)
		fd->entry[i] = state->frame_desc.entry[i];
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_set_frame_desc(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
				      काष्ठा v4l2_mbus_frame_desc *fd)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	काष्ठा v4l2_mbus_frame_desc *frame_desc = &state->frame_desc;
	पूर्णांक i;

	अगर (pad != OIF_SOURCE_PAD || fd == शून्य)
		वापस -EINVAL;

	fd->entry[0].length = 10 * SZ_1M;
	fd->entry[1].length = max_t(u32, fd->entry[1].length,
				    S5C73M3_EMBEDDED_DATA_MAXLEN);
	fd->num_entries = 2;

	mutex_lock(&state->lock);
	क्रम (i = 0; i < fd->num_entries; i++)
		frame_desc->entry[i] = fd->entry[i];
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अटल स्थिर पूर्णांक codes[] = अणु
			[S5C73M3_ISP_PAD] = S5C73M3_ISP_FMT,
			[S5C73M3_JPEG_PAD] = S5C73M3_JPEG_FMTपूर्ण;

	अगर (code->index > 0 || code->pad >= S5C73M3_NUM_PADS)
		वापस -EINVAL;

	code->code = codes[code->pad];

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	पूर्णांक ret;

	ret = s5c73m3_oअगर_get_pad_code(code->pad, code->index);
	अगर (ret < 0)
		वापस ret;

	code->code = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक idx;

	अगर (fse->pad == S5C73M3_ISP_PAD) अणु
		अगर (fse->code != S5C73M3_ISP_FMT)
			वापस -EINVAL;
		idx = RES_ISP;
	पूर्ण अन्यथाअणु
		अगर (fse->code != S5C73M3_JPEG_FMT)
			वापस -EINVAL;
		idx = RES_JPEG;
	पूर्ण

	अगर (fse->index >= s5c73m3_resolutions_len[idx])
		वापस -EINVAL;

	fse->min_width  = s5c73m3_resolutions[idx][fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = s5c73m3_resolutions[idx][fse->index].height;
	fse->min_height = fse->max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	पूर्णांक idx;

	अगर (fse->pad == OIF_SOURCE_PAD) अणु
		अगर (fse->index > 0)
			वापस -EINVAL;

		चयन (fse->code) अणु
		हाल S5C73M3_JPEG_FMT:
		हाल S5C73M3_ISP_FMT: अणु
			अचिन्हित w, h;

			अगर (fse->which == V4L2_SUBDEV_FORMAT_TRY) अणु
				काष्ठा v4l2_mbus_framefmt *mf;

				mf = v4l2_subdev_get_try_क्रमmat(sd, cfg,
								OIF_ISP_PAD);

				w = mf->width;
				h = mf->height;
			पूर्ण अन्यथा अणु
				स्थिर काष्ठा s5c73m3_frame_size *fs;

				fs = state->oअगर_pix_size[RES_ISP];
				w = fs->width;
				h = fs->height;
			पूर्ण
			fse->max_width = fse->min_width = w;
			fse->max_height = fse->min_height = h;
			वापस 0;
		पूर्ण
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (fse->code != s5c73m3_oअगर_get_pad_code(fse->pad, 0))
		वापस -EINVAL;

	अगर (fse->pad == OIF_JPEG_PAD)
		idx = RES_JPEG;
	अन्यथा
		idx = RES_ISP;

	अगर (fse->index >= s5c73m3_resolutions_len[idx])
		वापस -EINVAL;

	fse->min_width  = s5c73m3_resolutions[idx][fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = s5c73m3_resolutions[idx][fse->index].height;
	fse->min_height = fse->max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);

	v4l2_ctrl_handler_log_status(sd->ctrl_handler, sd->name);

	v4l2_info(sd, "power: %d, apply_fmt: %d\n", state->घातer,
							state->apply_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *mf;

	mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, S5C73M3_ISP_PAD);
	s5c73m3_fill_mbus_fmt(mf, &s5c73m3_isp_resolutions[1],
						S5C73M3_ISP_FMT);

	mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, S5C73M3_JPEG_PAD);
	s5c73m3_fill_mbus_fmt(mf, &s5c73m3_jpeg_resolutions[1],
					S5C73M3_JPEG_FMT);

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *mf;

	mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, OIF_ISP_PAD);
	s5c73m3_fill_mbus_fmt(mf, &s5c73m3_isp_resolutions[1],
						S5C73M3_ISP_FMT);

	mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, OIF_JPEG_PAD);
	s5c73m3_fill_mbus_fmt(mf, &s5c73m3_jpeg_resolutions[1],
					S5C73M3_JPEG_FMT);

	mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, OIF_SOURCE_PAD);
	s5c73m3_fill_mbus_fmt(mf, &s5c73m3_isp_resolutions[1],
						S5C73M3_ISP_FMT);
	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_gpio_set_value(काष्ठा s5c73m3 *priv, पूर्णांक id, u32 val)
अणु
	अगर (!gpio_is_valid(priv->gpio[id].gpio))
		वापस 0;
	gpio_set_value(priv->gpio[id].gpio, !!val);
	वापस 1;
पूर्ण

अटल पूर्णांक s5c73m3_gpio_निश्चित(काष्ठा s5c73m3 *priv, पूर्णांक id)
अणु
	वापस s5c73m3_gpio_set_value(priv, id, priv->gpio[id].level);
पूर्ण

अटल पूर्णांक s5c73m3_gpio_deनिश्चित(काष्ठा s5c73m3 *priv, पूर्णांक id)
अणु
	वापस s5c73m3_gpio_set_value(priv, id, !priv->gpio[id].level);
पूर्ण

अटल पूर्णांक __s5c73m3_घातer_on(काष्ठा s5c73m3 *state)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < S5C73M3_MAX_SUPPLIES; i++) अणु
		ret = regulator_enable(state->supplies[i].consumer);
		अगर (ret)
			जाओ err_reg_dis;
	पूर्ण

	ret = clk_set_rate(state->घड़ी, state->mclk_frequency);
	अगर (ret < 0)
		जाओ err_reg_dis;

	ret = clk_prepare_enable(state->घड़ी);
	अगर (ret < 0)
		जाओ err_reg_dis;

	v4l2_dbg(1, s5c73m3_dbg, &state->oअगर_sd, "clock frequency: %ld\n",
					clk_get_rate(state->घड़ी));

	s5c73m3_gpio_deनिश्चित(state, STBY);
	usleep_range(100, 200);

	s5c73m3_gpio_deनिश्चित(state, RST);
	usleep_range(50, 100);

	वापस 0;

err_reg_dis:
	क्रम (--i; i >= 0; i--)
		regulator_disable(state->supplies[i].consumer);
	वापस ret;
पूर्ण

अटल पूर्णांक __s5c73m3_घातer_off(काष्ठा s5c73m3 *state)
अणु
	पूर्णांक i, ret;

	अगर (s5c73m3_gpio_निश्चित(state, RST))
		usleep_range(10, 50);

	अगर (s5c73m3_gpio_निश्चित(state, STBY))
		usleep_range(100, 200);

	clk_disable_unprepare(state->घड़ी);

	state->streaming = 0;
	state->isp_पढ़ोy = 0;

	क्रम (i = S5C73M3_MAX_SUPPLIES - 1; i >= 0; i--) अणु
		ret = regulator_disable(state->supplies[i].consumer);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	क्रम (++i; i < S5C73M3_MAX_SUPPLIES; i++) अणु
		पूर्णांक r = regulator_enable(state->supplies[i].consumer);
		अगर (r < 0)
			v4l2_err(&state->oअगर_sd, "Failed to re-enable %s: %d\n",
				 state->supplies[i].supply, r);
	पूर्ण

	clk_prepare_enable(state->घड़ी);
	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	पूर्णांक ret = 0;

	mutex_lock(&state->lock);

	अगर (on && !state->घातer) अणु
		ret = __s5c73m3_घातer_on(state);
		अगर (!ret)
			ret = s5c73m3_isp_init(state);
		अगर (!ret) अणु
			state->apply_fiv = 1;
			state->apply_fmt = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (state->घातer == !on) अणु
		ret = s5c73m3_set_af_softlanding(state);
		अगर (!ret)
			ret = __s5c73m3_घातer_off(state);
		अन्यथा
			v4l2_err(sd, "Soft landing lens failed\n");
	पूर्ण
	अगर (!ret)
		state->घातer += on ? 1 : -1;

	v4l2_dbg(1, s5c73m3_dbg, sd, "%s: power: %d\n",
		 __func__, state->घातer);

	mutex_unlock(&state->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_oअगर_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	पूर्णांक ret;

	ret = v4l2_device_रेजिस्टर_subdev(sd->v4l2_dev, &state->sensor_sd);
	अगर (ret) अणु
		v4l2_err(sd->v4l2_dev, "Failed to register %s\n",
							state->oअगर_sd.name);
		वापस ret;
	पूर्ण

	ret = media_create_pad_link(&state->sensor_sd.entity,
			S5C73M3_ISP_PAD, &state->oअगर_sd.entity, OIF_ISP_PAD,
			MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED);

	ret = media_create_pad_link(&state->sensor_sd.entity,
			S5C73M3_JPEG_PAD, &state->oअगर_sd.entity, OIF_JPEG_PAD,
			MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED);

	वापस ret;
पूर्ण

अटल व्योम s5c73m3_oअगर_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(sd);
	v4l2_device_unरेजिस्टर_subdev(&state->sensor_sd);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops s5c73m3_पूर्णांकernal_ops = अणु
	.खोलो		= s5c73m3_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s5c73m3_pad_ops = अणु
	.क्रमागत_mbus_code		= s5c73m3_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= s5c73m3_क्रमागत_frame_size,
	.get_fmt		= s5c73m3_get_fmt,
	.set_fmt		= s5c73m3_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops s5c73m3_subdev_ops = अणु
	.pad	= &s5c73m3_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops oअगर_पूर्णांकernal_ops = अणु
	.रेजिस्टरed	= s5c73m3_oअगर_रेजिस्टरed,
	.unरेजिस्टरed	= s5c73m3_oअगर_unरेजिस्टरed,
	.खोलो		= s5c73m3_oअगर_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s5c73m3_oअगर_pad_ops = अणु
	.क्रमागत_mbus_code		= s5c73m3_oअगर_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= s5c73m3_oअगर_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval	= s5c73m3_oअगर_क्रमागत_frame_पूर्णांकerval,
	.get_fmt		= s5c73m3_oअगर_get_fmt,
	.set_fmt		= s5c73m3_oअगर_set_fmt,
	.get_frame_desc		= s5c73m3_oअगर_get_frame_desc,
	.set_frame_desc		= s5c73m3_oअगर_set_frame_desc,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops s5c73m3_oअगर_core_ops = अणु
	.s_घातer	= s5c73m3_oअगर_set_घातer,
	.log_status	= s5c73m3_oअगर_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops s5c73m3_oअगर_video_ops = अणु
	.s_stream		= s5c73m3_oअगर_s_stream,
	.g_frame_पूर्णांकerval	= s5c73m3_oअगर_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval	= s5c73m3_oअगर_s_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops oअगर_subdev_ops = अणु
	.core	= &s5c73m3_oअगर_core_ops,
	.pad	= &s5c73m3_oअगर_pad_ops,
	.video	= &s5c73m3_oअगर_video_ops,
पूर्ण;

अटल पूर्णांक s5c73m3_configure_gpios(काष्ठा s5c73m3 *state)
अणु
	अटल स्थिर अक्षर * स्थिर gpio_names[] = अणु
		"S5C73M3_STBY", "S5C73M3_RST"
	पूर्ण;
	काष्ठा i2c_client *c = state->i2c_client;
	काष्ठा s5c73m3_gpio *g = state->gpio;
	पूर्णांक ret, i;

	क्रम (i = 0; i < GPIO_NUM; ++i) अणु
		अचिन्हित पूर्णांक flags = GPIOF_सूची_OUT;
		अगर (g[i].level)
			flags |= GPIOF_INIT_HIGH;
		ret = devm_gpio_request_one(&c->dev, g[i].gpio, flags,
					    gpio_names[i]);
		अगर (ret) अणु
			v4l2_err(c, "failed to request gpio %s\n",
				 gpio_names[i]);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_parse_gpios(काष्ठा s5c73m3 *state)
अणु
	अटल स्थिर अक्षर * स्थिर prop_names[] = अणु
		"standby-gpios", "xshutdown-gpios",
	पूर्ण;
	काष्ठा device *dev = &state->i2c_client->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret, i;

	क्रम (i = 0; i < GPIO_NUM; ++i) अणु
		क्रमागत of_gpio_flags of_flags;

		ret = of_get_named_gpio_flags(node, prop_names[i],
					      0, &of_flags);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to parse %s DT property\n",
				prop_names[i]);
			वापस -EINVAL;
		पूर्ण
		state->gpio[i].gpio = ret;
		state->gpio[i].level = !(of_flags & OF_GPIO_ACTIVE_LOW);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_get_platक्रमm_data(काष्ठा s5c73m3 *state)
अणु
	काष्ठा device *dev = &state->i2c_client->dev;
	स्थिर काष्ठा s5c73m3_platक्रमm_data *pdata = dev->platक्रमm_data;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *node_ep;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep = अणु .bus_type = 0 पूर्ण;
	पूर्णांक ret;

	अगर (!node) अणु
		अगर (!pdata) अणु
			dev_err(dev, "Platform data not specified\n");
			वापस -EINVAL;
		पूर्ण

		state->mclk_frequency = pdata->mclk_frequency;
		state->gpio[STBY] = pdata->gpio_stby;
		state->gpio[RST] = pdata->gpio_reset;
		वापस 0;
	पूर्ण

	state->घड़ी = devm_clk_get(dev, S5C73M3_CLK_NAME);
	अगर (IS_ERR(state->घड़ी))
		वापस PTR_ERR(state->घड़ी);

	अगर (of_property_पढ़ो_u32(node, "clock-frequency",
				 &state->mclk_frequency)) अणु
		state->mclk_frequency = S5C73M3_DEFAULT_MCLK_FREQ;
		dev_info(dev, "using default %u Hz clock frequency\n",
					state->mclk_frequency);
	पूर्ण

	ret = s5c73m3_parse_gpios(state);
	अगर (ret < 0)
		वापस -EINVAL;

	node_ep = of_graph_get_next_endpoपूर्णांक(node, शून्य);
	अगर (!node_ep) अणु
		dev_warn(dev, "no endpoint defined for node: %pOF\n", node);
		वापस 0;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(node_ep), &ep);
	of_node_put(node_ep);
	अगर (ret)
		वापस ret;

	अगर (ep.bus_type != V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(dev, "unsupported bus type\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * Number of MIPI CSI-2 data lanes is currently not configurable,
	 * always a शेष value of 4 lanes is used.
	 */
	अगर (ep.bus.mipi_csi2.num_data_lanes != S5C73M3_MIPI_DATA_LANES)
		dev_info(dev, "falling back to 4 MIPI CSI-2 data lanes\n");

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_subdev *oअगर_sd;
	काष्ठा s5c73m3 *state;
	पूर्णांक ret, i;

	state = devm_kzalloc(dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->i2c_client = client;
	ret = s5c73m3_get_platक्रमm_data(state);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&state->lock);
	sd = &state->sensor_sd;
	oअगर_sd = &state->oअगर_sd;

	v4l2_subdev_init(sd, &s5c73m3_subdev_ops);
	sd->owner = client->dev.driver->owner;
	v4l2_set_subdevdata(sd, state);
	strscpy(sd->name, "S5C73M3", माप(sd->name));

	sd->पूर्णांकernal_ops = &s5c73m3_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	state->sensor_pads[S5C73M3_JPEG_PAD].flags = MEDIA_PAD_FL_SOURCE;
	state->sensor_pads[S5C73M3_ISP_PAD].flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret = media_entity_pads_init(&sd->entity, S5C73M3_NUM_PADS,
							state->sensor_pads);
	अगर (ret < 0)
		वापस ret;

	v4l2_i2c_subdev_init(oअगर_sd, client, &oअगर_subdev_ops);
	/* Static name; NEVER use in new drivers! */
	strscpy(oअगर_sd->name, "S5C73M3-OIF", माप(oअगर_sd->name));

	oअगर_sd->पूर्णांकernal_ops = &oअगर_पूर्णांकernal_ops;
	oअगर_sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	state->oअगर_pads[OIF_ISP_PAD].flags = MEDIA_PAD_FL_SINK;
	state->oअगर_pads[OIF_JPEG_PAD].flags = MEDIA_PAD_FL_SINK;
	state->oअगर_pads[OIF_SOURCE_PAD].flags = MEDIA_PAD_FL_SOURCE;
	oअगर_sd->entity.function = MEDIA_ENT_F_PROC_VIDEO_SCALER;

	ret = media_entity_pads_init(&oअगर_sd->entity, OIF_NUM_PADS,
							state->oअगर_pads);
	अगर (ret < 0)
		वापस ret;

	ret = s5c73m3_configure_gpios(state);
	अगर (ret)
		जाओ out_err;

	क्रम (i = 0; i < S5C73M3_MAX_SUPPLIES; i++)
		state->supplies[i].supply = s5c73m3_supply_names[i];

	ret = devm_regulator_bulk_get(dev, S5C73M3_MAX_SUPPLIES,
			       state->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to get regulators\n");
		जाओ out_err;
	पूर्ण

	ret = s5c73m3_init_controls(state);
	अगर (ret)
		जाओ out_err;

	state->sensor_pix_size[RES_ISP] = &s5c73m3_isp_resolutions[1];
	state->sensor_pix_size[RES_JPEG] = &s5c73m3_jpeg_resolutions[1];
	state->oअगर_pix_size[RES_ISP] = state->sensor_pix_size[RES_ISP];
	state->oअगर_pix_size[RES_JPEG] = state->sensor_pix_size[RES_JPEG];

	state->mbus_code = S5C73M3_ISP_FMT;

	state->fiv = &s5c73m3_पूर्णांकervals[S5C73M3_DEFAULT_FRAME_INTERVAL];

	state->fw_file_version[0] = 'G';
	state->fw_file_version[1] = 'C';

	ret = s5c73m3_रेजिस्टर_spi_driver(state);
	अगर (ret < 0)
		जाओ out_err;

	oअगर_sd->dev = dev;

	ret = __s5c73m3_घातer_on(state);
	अगर (ret < 0)
		जाओ out_err1;

	ret = s5c73m3_get_fw_version(state);
	__s5c73m3_घातer_off(state);

	अगर (ret < 0) अणु
		dev_err(dev, "Device detection failed: %d\n", ret);
		जाओ out_err1;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev(oअगर_sd);
	अगर (ret < 0)
		जाओ out_err1;

	v4l2_info(sd, "%s: completed successfully\n", __func__);
	वापस 0;

out_err1:
	s5c73m3_unरेजिस्टर_spi_driver(state);
out_err:
	media_entity_cleanup(&sd->entity);
	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *oअगर_sd = i2c_get_clientdata(client);
	काष्ठा s5c73m3 *state = oअगर_sd_to_s5c73m3(oअगर_sd);
	काष्ठा v4l2_subdev *sensor_sd = &state->sensor_sd;

	v4l2_async_unरेजिस्टर_subdev(oअगर_sd);

	v4l2_ctrl_handler_मुक्त(oअगर_sd->ctrl_handler);
	media_entity_cleanup(&oअगर_sd->entity);

	v4l2_device_unरेजिस्टर_subdev(sensor_sd);
	media_entity_cleanup(&sensor_sd->entity);

	s5c73m3_unरेजिस्टर_spi_driver(state);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id s5c73m3_id[] = अणु
	अणु DRIVER_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s5c73m3_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id s5c73m3_of_match[] = अणु
	अणु .compatible = "samsung,s5c73m3" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s5c73m3_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver s5c73m3_i2c_driver = अणु
	.driver = अणु
		.of_match_table = of_match_ptr(s5c73m3_of_match),
		.name	= DRIVER_NAME,
	पूर्ण,
	.probe_new	= s5c73m3_probe,
	.हटाओ		= s5c73m3_हटाओ,
	.id_table	= s5c73m3_id,
पूर्ण;

module_i2c_driver(s5c73m3_i2c_driver);

MODULE_DESCRIPTION("Samsung S5C73M3 camera driver");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_LICENSE("GPL");

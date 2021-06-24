<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम M-5MOLS 8M Pixel camera sensor with ISP
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
#समावेश <linux/module.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/i2c/m5mols.h>

#समावेश "m5mols.h"
#समावेश "m5mols_reg.h"

पूर्णांक m5mols_debug;
module_param(m5mols_debug, पूर्णांक, 0644);

#घोषणा MODULE_NAME		"M5MOLS"
#घोषणा M5MOLS_I2C_CHECK_RETRY	500

/* The regulator consumer names क्रम बाह्यal voltage regulators */
अटल काष्ठा regulator_bulk_data supplies[] = अणु
	अणु
		.supply = "core",	/* ARM core घातer, 1.2V */
	पूर्ण, अणु
		.supply	= "dig_18",	/* digital घातer 1, 1.8V */
	पूर्ण, अणु
		.supply	= "d_sensor",	/* sensor घातer 1, 1.8V */
	पूर्ण, अणु
		.supply	= "dig_28",	/* digital घातer 2, 2.8V */
	पूर्ण, अणु
		.supply	= "a_sensor",	/* analog घातer */
	पूर्ण, अणु
		.supply	= "dig_12",	/* digital घातer 3, 1.2V */
	पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_mbus_framefmt m5mols_शेष_ffmt[M5MOLS_RESTYPE_MAX] = अणु
	[M5MOLS_RESTYPE_MONITOR] = अणु
		.width		= 1920,
		.height		= 1080,
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.field		= V4L2_FIELD_NONE,
		.colorspace	= V4L2_COLORSPACE_JPEG,
	पूर्ण,
	[M5MOLS_RESTYPE_CAPTURE] = अणु
		.width		= 1920,
		.height		= 1080,
		.code		= MEDIA_BUS_FMT_JPEG_1X8,
		.field		= V4L2_FIELD_NONE,
		.colorspace	= V4L2_COLORSPACE_JPEG,
	पूर्ण,
पूर्ण;
#घोषणा SIZE_DEFAULT_FFMT	ARRAY_SIZE(m5mols_शेष_ffmt)

अटल स्थिर काष्ठा m5mols_resolution m5mols_reg_res[] = अणु
	अणु 0x01, M5MOLS_RESTYPE_MONITOR, 128, 96 पूर्ण,	/* SUB-QCIF */
	अणु 0x03, M5MOLS_RESTYPE_MONITOR, 160, 120 पूर्ण,	/* QQVGA */
	अणु 0x05, M5MOLS_RESTYPE_MONITOR, 176, 144 पूर्ण,	/* QCIF */
	अणु 0x06, M5MOLS_RESTYPE_MONITOR, 176, 176 पूर्ण,
	अणु 0x08, M5MOLS_RESTYPE_MONITOR, 240, 320 पूर्ण,	/* QVGA */
	अणु 0x09, M5MOLS_RESTYPE_MONITOR, 320, 240 पूर्ण,	/* QVGA */
	अणु 0x0c, M5MOLS_RESTYPE_MONITOR, 240, 400 पूर्ण,	/* WQVGA */
	अणु 0x0d, M5MOLS_RESTYPE_MONITOR, 400, 240 पूर्ण,	/* WQVGA */
	अणु 0x0e, M5MOLS_RESTYPE_MONITOR, 352, 288 पूर्ण,	/* CIF */
	अणु 0x13, M5MOLS_RESTYPE_MONITOR, 480, 360 पूर्ण,
	अणु 0x15, M5MOLS_RESTYPE_MONITOR, 640, 360 पूर्ण,	/* qHD */
	अणु 0x17, M5MOLS_RESTYPE_MONITOR, 640, 480 पूर्ण,	/* VGA */
	अणु 0x18, M5MOLS_RESTYPE_MONITOR, 720, 480 पूर्ण,
	अणु 0x1a, M5MOLS_RESTYPE_MONITOR, 800, 480 पूर्ण,	/* WVGA */
	अणु 0x1f, M5MOLS_RESTYPE_MONITOR, 800, 600 पूर्ण,	/* SVGA */
	अणु 0x21, M5MOLS_RESTYPE_MONITOR, 1280, 720 पूर्ण,	/* HD */
	अणु 0x25, M5MOLS_RESTYPE_MONITOR, 1920, 1080 पूर्ण,	/* 1080p */
	अणु 0x29, M5MOLS_RESTYPE_MONITOR, 3264, 2448 पूर्ण,	/* 2.63fps 8M */
	अणु 0x39, M5MOLS_RESTYPE_MONITOR, 800, 602 पूर्ण,	/* AHS_MON debug */

	अणु 0x02, M5MOLS_RESTYPE_CAPTURE, 320, 240 पूर्ण,	/* QVGA */
	अणु 0x04, M5MOLS_RESTYPE_CAPTURE, 400, 240 पूर्ण,	/* WQVGA */
	अणु 0x07, M5MOLS_RESTYPE_CAPTURE, 480, 360 पूर्ण,
	अणु 0x08, M5MOLS_RESTYPE_CAPTURE, 640, 360 पूर्ण,	/* qHD */
	अणु 0x09, M5MOLS_RESTYPE_CAPTURE, 640, 480 पूर्ण,	/* VGA */
	अणु 0x0a, M5MOLS_RESTYPE_CAPTURE, 800, 480 पूर्ण,	/* WVGA */
	अणु 0x10, M5MOLS_RESTYPE_CAPTURE, 1280, 720 पूर्ण,	/* HD */
	अणु 0x14, M5MOLS_RESTYPE_CAPTURE, 1280, 960 पूर्ण,	/* 1M */
	अणु 0x17, M5MOLS_RESTYPE_CAPTURE, 1600, 1200 पूर्ण,	/* 2M */
	अणु 0x19, M5MOLS_RESTYPE_CAPTURE, 1920, 1080 पूर्ण,	/* Full-HD */
	अणु 0x1a, M5MOLS_RESTYPE_CAPTURE, 2048, 1152 पूर्ण,	/* 3Mega */
	अणु 0x1b, M5MOLS_RESTYPE_CAPTURE, 2048, 1536 पूर्ण,
	अणु 0x1c, M5MOLS_RESTYPE_CAPTURE, 2560, 1440 पूर्ण,	/* 4Mega */
	अणु 0x1d, M5MOLS_RESTYPE_CAPTURE, 2560, 1536 पूर्ण,
	अणु 0x1f, M5MOLS_RESTYPE_CAPTURE, 2560, 1920 पूर्ण,	/* 5Mega */
	अणु 0x21, M5MOLS_RESTYPE_CAPTURE, 3264, 1836 पूर्ण,	/* 6Mega */
	अणु 0x22, M5MOLS_RESTYPE_CAPTURE, 3264, 1960 पूर्ण,
	अणु 0x25, M5MOLS_RESTYPE_CAPTURE, 3264, 2448 पूर्ण,	/* 8Mega */
पूर्ण;

/**
 * m5mols_swap_byte - an byte array to पूर्णांकeger conversion function
 * @data: byte array
 * @length: size in bytes of I2C packet defined in the M-5MOLS datasheet
 *
 * Convert I2C data byte array with perक्रमming any required byte
 * reordering to assure proper values क्रम each data type, regardless
 * of the architecture endianness.
 */
अटल u32 m5mols_swap_byte(u8 *data, u8 length)
अणु
	अगर (length == 1)
		वापस *data;
	अन्यथा अगर (length == 2)
		वापस be16_to_cpu(*((__be16 *)data));
	अन्यथा
		वापस be32_to_cpu(*((__be32 *)data));
पूर्ण

/**
 * m5mols_पढ़ो -  I2C पढ़ो function
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 * @size: desired size of I2C packet
 * @reg: combination of size, category and command क्रम the I2C packet
 * @val: पढ़ो value
 *
 * Returns 0 on success, or अन्यथा negative त्रुटि_सं.
 */
अटल पूर्णांक m5mols_पढ़ो(काष्ठा v4l2_subdev *sd, u32 size, u32 reg, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा m5mols_info *info = to_m5mols(sd);
	u8 rbuf[M5MOLS_I2C_MAX_SIZE + 1];
	u8 category = I2C_CATEGORY(reg);
	u8 cmd = I2C_COMMAND(reg);
	काष्ठा i2c_msg msg[2];
	u8 wbuf[5];
	पूर्णांक ret;

	अगर (!client->adapter)
		वापस -ENODEV;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 5;
	msg[0].buf = wbuf;
	wbuf[0] = 5;
	wbuf[1] = M5MOLS_BYTE_READ;
	wbuf[2] = category;
	wbuf[3] = cmd;
	wbuf[4] = size;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = size + 1;
	msg[1].buf = rbuf;

	/* minimum stabilization समय */
	usleep_range(200, 300);

	ret = i2c_transfer(client->adapter, msg, 2);

	अगर (ret == 2) अणु
		*val = m5mols_swap_byte(&rbuf[1], size);
		वापस 0;
	पूर्ण

	अगर (info->isp_पढ़ोy)
		v4l2_err(sd, "read failed: size:%d cat:%02x cmd:%02x. %d\n",
			 size, category, cmd, ret);

	वापस ret < 0 ? ret : -EIO;
पूर्ण

पूर्णांक m5mols_पढ़ो_u8(काष्ठा v4l2_subdev *sd, u32 reg, u8 *val)
अणु
	u32 val_32;
	पूर्णांक ret;

	अगर (I2C_SIZE(reg) != 1) अणु
		v4l2_err(sd, "Wrong data size\n");
		वापस -EINVAL;
	पूर्ण

	ret = m5mols_पढ़ो(sd, I2C_SIZE(reg), reg, &val_32);
	अगर (ret)
		वापस ret;

	*val = (u8)val_32;
	वापस ret;
पूर्ण

पूर्णांक m5mols_पढ़ो_u16(काष्ठा v4l2_subdev *sd, u32 reg, u16 *val)
अणु
	u32 val_32;
	पूर्णांक ret;

	अगर (I2C_SIZE(reg) != 2) अणु
		v4l2_err(sd, "Wrong data size\n");
		वापस -EINVAL;
	पूर्ण

	ret = m5mols_पढ़ो(sd, I2C_SIZE(reg), reg, &val_32);
	अगर (ret)
		वापस ret;

	*val = (u16)val_32;
	वापस ret;
पूर्ण

पूर्णांक m5mols_पढ़ो_u32(काष्ठा v4l2_subdev *sd, u32 reg, u32 *val)
अणु
	अगर (I2C_SIZE(reg) != 4) अणु
		v4l2_err(sd, "Wrong data size\n");
		वापस -EINVAL;
	पूर्ण

	वापस m5mols_पढ़ो(sd, I2C_SIZE(reg), reg, val);
पूर्ण

/**
 * m5mols_ग_लिखो - I2C command ग_लिखो function
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 * @reg: combination of size, category and command क्रम the I2C packet
 * @val: value to ग_लिखो
 *
 * Returns 0 on success, or अन्यथा negative त्रुटि_सं.
 */
पूर्णांक m5mols_ग_लिखो(काष्ठा v4l2_subdev *sd, u32 reg, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा m5mols_info *info = to_m5mols(sd);
	u8 wbuf[M5MOLS_I2C_MAX_SIZE + 4];
	u8 category = I2C_CATEGORY(reg);
	u8 cmd = I2C_COMMAND(reg);
	u8 size	= I2C_SIZE(reg);
	u32 *buf = (u32 *)&wbuf[4];
	काष्ठा i2c_msg msg[1];
	पूर्णांक ret;

	अगर (!client->adapter)
		वापस -ENODEV;

	अगर (size != 1 && size != 2 && size != 4) अणु
		v4l2_err(sd, "Wrong data size\n");
		वापस -EINVAL;
	पूर्ण

	msg->addr = client->addr;
	msg->flags = 0;
	msg->len = (u16)size + 4;
	msg->buf = wbuf;
	wbuf[0] = size + 4;
	wbuf[1] = M5MOLS_BYTE_WRITE;
	wbuf[2] = category;
	wbuf[3] = cmd;

	*buf = m5mols_swap_byte((u8 *)&val, size);

	/* minimum stabilization समय */
	usleep_range(200, 300);

	ret = i2c_transfer(client->adapter, msg, 1);
	अगर (ret == 1)
		वापस 0;

	अगर (info->isp_पढ़ोy)
		v4l2_err(sd, "write failed: cat:%02x cmd:%02x ret:%d\n",
			 category, cmd, ret);

	वापस ret < 0 ? ret : -EIO;
पूर्ण

/**
 * m5mols_busy_रुको - Busy रुकोing with I2C रेजिस्टर polling
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 * @reg: the I2C_REG() address of an 8-bit status रेजिस्टर to check
 * @value: expected status रेजिस्टर value
 * @mask: bit mask क्रम the पढ़ो status रेजिस्टर value
 * @समयout: समयout in milliseconds, or -1 क्रम शेष समयout
 *
 * The @reg रेजिस्टर value is ORed with @mask beक्रमe comparing with @value.
 *
 * Return: 0 अगर the requested condition became true within less than
 *         @समयout ms, or अन्यथा negative त्रुटि_सं.
 */
पूर्णांक m5mols_busy_रुको(काष्ठा v4l2_subdev *sd, u32 reg, u32 value, u32 mask,
		     पूर्णांक समयout)
अणु
	पूर्णांक ms = समयout < 0 ? M5MOLS_BUSY_WAIT_DEF_TIMEOUT : समयout;
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(ms);
	u8 status;

	करो अणु
		पूर्णांक ret = m5mols_पढ़ो_u8(sd, reg, &status);

		अगर (ret < 0 && !(mask & M5MOLS_I2C_RDY_WAIT_FL))
			वापस ret;
		अगर (!ret && (status & mask & 0xff) == (value & 0xff))
			वापस 0;
		usleep_range(100, 250);
	पूर्ण जबतक (ms > 0 && समय_is_after_jअगरfies(end));

	वापस -EBUSY;
पूर्ण

/**
 * m5mols_enable_पूर्णांकerrupt - Clear पूर्णांकerrupt pending bits and unmask पूर्णांकerrupts
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 * @reg: combination of size, category and command क्रम the I2C packet
 *
 * Beक्रमe writing desired पूर्णांकerrupt value the INT_FACTOR रेजिस्टर should
 * be पढ़ो to clear pending पूर्णांकerrupts.
 */
पूर्णांक m5mols_enable_पूर्णांकerrupt(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	u8 mask = is_available_af(info) ? REG_INT_AF : 0;
	u8 dummy;
	पूर्णांक ret;

	ret = m5mols_पढ़ो_u8(sd, SYSTEM_INT_FACTOR, &dummy);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, SYSTEM_INT_ENABLE, reg & ~mask);
	वापस ret;
पूर्ण

पूर्णांक m5mols_रुको_पूर्णांकerrupt(काष्ठा v4l2_subdev *sd, u8 irq_mask, u32 समयout)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);

	पूर्णांक ret = रुको_event_पूर्णांकerruptible_समयout(info->irq_रुकोq,
				atomic_add_unless(&info->irq_करोne, -1, 0),
				msecs_to_jअगरfies(समयout));
	अगर (ret <= 0)
		वापस ret ? ret : -ETIMEDOUT;

	वापस m5mols_busy_रुको(sd, SYSTEM_INT_FACTOR, irq_mask,
				M5MOLS_I2C_RDY_WAIT_FL | irq_mask, -1);
पूर्ण

/**
 * m5mols_reg_mode - Write the mode and check busy status
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 * @mode: the required operation mode
 *
 * It always accompanies a little delay changing the M-5MOLS mode, so it is
 * needed checking current busy status to guarantee right mode.
 */
अटल पूर्णांक m5mols_reg_mode(काष्ठा v4l2_subdev *sd, u8 mode)
अणु
	पूर्णांक ret = m5mols_ग_लिखो(sd, SYSTEM_SYSMODE, mode);
	अगर (ret < 0)
		वापस ret;
	वापस m5mols_busy_रुको(sd, SYSTEM_SYSMODE, mode, 0xff,
				M5MOLS_MODE_CHANGE_TIMEOUT);
पूर्ण

/**
 * m5mols_set_mode - set the M-5MOLS controller mode
 * @info: M-5MOLS driver data काष्ठाure
 * @mode: the required operation mode
 *
 * The commands of M-5MOLS are grouped पूर्णांकo specअगरic modes. Each functionality
 * can be guaranteed only when the sensor is operating in mode which a command
 * beदीर्घs to.
 */
पूर्णांक m5mols_set_mode(काष्ठा m5mols_info *info, u8 mode)
अणु
	काष्ठा v4l2_subdev *sd = &info->sd;
	पूर्णांक ret = -EINVAL;
	u8 reg;

	अगर (mode < REG_PARAMETER || mode > REG_CAPTURE)
		वापस ret;

	ret = m5mols_पढ़ो_u8(sd, SYSTEM_SYSMODE, &reg);
	अगर (ret || reg == mode)
		वापस ret;

	चयन (reg) अणु
	हाल REG_PARAMETER:
		ret = m5mols_reg_mode(sd, REG_MONITOR);
		अगर (mode == REG_MONITOR)
			अवरोध;
		अगर (!ret)
			ret = m5mols_reg_mode(sd, REG_CAPTURE);
		अवरोध;

	हाल REG_MONITOR:
		अगर (mode == REG_PARAMETER) अणु
			ret = m5mols_reg_mode(sd, REG_PARAMETER);
			अवरोध;
		पूर्ण

		ret = m5mols_reg_mode(sd, REG_CAPTURE);
		अवरोध;

	हाल REG_CAPTURE:
		ret = m5mols_reg_mode(sd, REG_MONITOR);
		अगर (mode == REG_MONITOR)
			अवरोध;
		अगर (!ret)
			ret = m5mols_reg_mode(sd, REG_PARAMETER);
		अवरोध;

	शेष:
		v4l2_warn(sd, "Wrong mode: %d\n", mode);
	पूर्ण

	अगर (!ret)
		info->mode = mode;

	वापस ret;
पूर्ण

/**
 * m5mols_get_version - retrieve full revisions inक्रमmation of M-5MOLS
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 *
 * The version inक्रमmation includes revisions of hardware and firmware,
 * AutoFocus alghorithm version and the version string.
 */
अटल पूर्णांक m5mols_get_version(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	काष्ठा m5mols_version *ver = &info->ver;
	u8 *str = ver->str;
	पूर्णांक i;
	पूर्णांक ret;

	ret = m5mols_पढ़ो_u8(sd, SYSTEM_VER_CUSTOMER, &ver->customer);
	अगर (!ret)
		ret = m5mols_पढ़ो_u8(sd, SYSTEM_VER_PROJECT, &ver->project);
	अगर (!ret)
		ret = m5mols_पढ़ो_u16(sd, SYSTEM_VER_FIRMWARE, &ver->fw);
	अगर (!ret)
		ret = m5mols_पढ़ो_u16(sd, SYSTEM_VER_HARDWARE, &ver->hw);
	अगर (!ret)
		ret = m5mols_पढ़ो_u16(sd, SYSTEM_VER_PARAMETER, &ver->param);
	अगर (!ret)
		ret = m5mols_पढ़ो_u16(sd, SYSTEM_VER_AWB, &ver->awb);
	अगर (!ret)
		ret = m5mols_पढ़ो_u8(sd, AF_VERSION, &ver->af);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < VERSION_STRING_SIZE; i++) अणु
		ret = m5mols_पढ़ो_u8(sd, SYSTEM_VER_STRING, &str[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	v4l2_info(sd, "Manufacturer\t[%s]\n",
			is_manufacturer(info, REG_SAMSUNG_ELECTRO) ?
			"Samsung Electro-Mechanics" :
			is_manufacturer(info, REG_SAMSUNG_OPTICS) ?
			"Samsung Fiber-Optics" :
			is_manufacturer(info, REG_SAMSUNG_TECHWIN) ?
			"Samsung Techwin" : "None");
	v4l2_info(sd, "Customer/Project\t[0x%02x/0x%02x]\n",
			info->ver.customer, info->ver.project);

	अगर (!is_available_af(info))
		v4l2_info(sd, "No support Auto Focus on this firmware\n");

	वापस ret;
पूर्ण

/**
 * __find_restype - Lookup M-5MOLS resolution type according to pixel code
 * @code: pixel code
 */
अटल क्रमागत m5mols_restype __find_restype(u32 code)
अणु
	क्रमागत m5mols_restype type = M5MOLS_RESTYPE_MONITOR;

	करो अणु
		अगर (code == m5mols_शेष_ffmt[type].code)
			वापस type;
	पूर्ण जबतक (type++ != SIZE_DEFAULT_FFMT);

	वापस 0;
पूर्ण

/**
 * __find_resolution - Lookup preset and type of M-5MOLS's resolution
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 * @mf: pixel क्रमmat to find/negotiate the resolution preset क्रम
 * @type: M-5MOLS resolution type
 * @resolution:	M-5MOLS resolution preset रेजिस्टर value
 *
 * Find nearest resolution matching resolution preset and adjust mf
 * to supported values.
 */
अटल पूर्णांक __find_resolution(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_mbus_framefmt *mf,
			     क्रमागत m5mols_restype *type,
			     u32 *resolution)
अणु
	स्थिर काष्ठा m5mols_resolution *fsize = &m5mols_reg_res[0];
	स्थिर काष्ठा m5mols_resolution *match = शून्य;
	क्रमागत m5mols_restype stype = __find_restype(mf->code);
	पूर्णांक i = ARRAY_SIZE(m5mols_reg_res);
	अचिन्हित पूर्णांक min_err = ~0;

	जबतक (i--) अणु
		पूर्णांक err;
		अगर (stype == fsize->type) अणु
			err = असल(fsize->width - mf->width)
				+ असल(fsize->height - mf->height);

			अगर (err < min_err) अणु
				min_err = err;
				match = fsize;
			पूर्ण
		पूर्ण
		fsize++;
	पूर्ण
	अगर (match) अणु
		mf->width  = match->width;
		mf->height = match->height;
		*resolution = match->reg;
		*type = stype;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *__find_क्रमmat(काष्ठा m5mols_info *info,
				काष्ठा v4l2_subdev_pad_config *cfg,
				क्रमागत v4l2_subdev_क्रमmat_whence which,
				क्रमागत m5mols_restype type)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस cfg ? v4l2_subdev_get_try_क्रमmat(&info->sd, cfg, 0) : शून्य;

	वापस &info->ffmt[type];
पूर्ण

अटल पूर्णांक m5mols_get_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	पूर्णांक ret = 0;

	mutex_lock(&info->lock);

	क्रमmat = __find_क्रमmat(info, cfg, fmt->which, info->res_type);
	अगर (क्रमmat)
		fmt->क्रमmat = *क्रमmat;
	अन्यथा
		ret = -EINVAL;

	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_set_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat = &fmt->क्रमmat;
	काष्ठा v4l2_mbus_framefmt *sfmt;
	क्रमागत m5mols_restype type;
	u32 resolution = 0;
	पूर्णांक ret;

	ret = __find_resolution(sd, क्रमmat, &type, &resolution);
	अगर (ret < 0)
		वापस ret;

	sfmt = __find_क्रमmat(info, cfg, fmt->which, type);
	अगर (!sfmt)
		वापस 0;

	mutex_lock(&info->lock);

	क्रमmat->code = m5mols_शेष_ffmt[type].code;
	क्रमmat->colorspace = V4L2_COLORSPACE_JPEG;
	क्रमmat->field = V4L2_FIELD_NONE;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		*sfmt = *क्रमmat;
		info->resolution = resolution;
		info->res_type = type;
	पूर्ण

	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_get_frame_desc(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
				 काष्ठा v4l2_mbus_frame_desc *fd)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);

	अगर (pad != 0 || fd == शून्य)
		वापस -EINVAL;

	mutex_lock(&info->lock);
	/*
	 * .get_frame_desc is only used क्रम compressed क्रमmats,
	 * thus we always वापस the capture frame parameters here.
	 */
	fd->entry[0].length = info->cap.buf_size;
	fd->entry[0].pixelcode = info->ffmt[M5MOLS_RESTYPE_CAPTURE].code;
	mutex_unlock(&info->lock);

	fd->entry[0].flags = V4L2_MBUS_FRAME_DESC_FL_LEN_MAX;
	fd->num_entries = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक m5mols_set_frame_desc(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
				 काष्ठा v4l2_mbus_frame_desc *fd)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &info->ffmt[M5MOLS_RESTYPE_CAPTURE];

	अगर (pad != 0 || fd == शून्य)
		वापस -EINVAL;

	fd->entry[0].flags = V4L2_MBUS_FRAME_DESC_FL_LEN_MAX;
	fd->num_entries = 1;
	fd->entry[0].length = clamp_t(u32, fd->entry[0].length,
				      mf->width * mf->height,
				      M5MOLS_MAIN_JPEG_SIZE_MAX);
	mutex_lock(&info->lock);
	info->cap.buf_size = fd->entry[0].length;
	mutex_unlock(&info->lock);

	वापस 0;
पूर्ण


अटल पूर्णांक m5mols_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (!code || code->index >= SIZE_DEFAULT_FFMT)
		वापस -EINVAL;

	code->code = m5mols_शेष_ffmt[code->index].code;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops m5mols_pad_ops = अणु
	.क्रमागत_mbus_code	= m5mols_क्रमागत_mbus_code,
	.get_fmt	= m5mols_get_fmt,
	.set_fmt	= m5mols_set_fmt,
	.get_frame_desc	= m5mols_get_frame_desc,
	.set_frame_desc	= m5mols_set_frame_desc,
पूर्ण;

/**
 * m5mols_restore_controls - Apply current control values to the रेजिस्टरs
 * @info: M-5MOLS driver data काष्ठाure
 *
 * m5mols_करो_scenemode() handles all parameters क्रम which there is yet no
 * inभागidual control. It should be replaced at some poपूर्णांक by setting each
 * control inभागidually, in required रेजिस्टर set up order.
 */
पूर्णांक m5mols_restore_controls(काष्ठा m5mols_info *info)
अणु
	पूर्णांक ret;

	अगर (info->ctrl_sync)
		वापस 0;

	ret = m5mols_करो_scenemode(info, REG_SCENE_NORMAL);
	अगर (ret)
		वापस ret;

	ret = v4l2_ctrl_handler_setup(&info->handle);
	info->ctrl_sync = !ret;

	वापस ret;
पूर्ण

/**
 * m5mols_start_monitor - Start the monitor mode
 * @info: M-5MOLS driver data काष्ठाure
 *
 * Beक्रमe applying the controls setup the resolution and frame rate
 * in PARAMETER mode, and then चयन over to MONITOR mode.
 */
अटल पूर्णांक m5mols_start_monitor(काष्ठा m5mols_info *info)
अणु
	काष्ठा v4l2_subdev *sd = &info->sd;
	पूर्णांक ret;

	ret = m5mols_set_mode(info, REG_PARAMETER);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, PARM_MON_SIZE, info->resolution);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, PARM_MON_FPS, REG_FPS_30);
	अगर (!ret)
		ret = m5mols_set_mode(info, REG_MONITOR);
	अगर (!ret)
		ret = m5mols_restore_controls(info);

	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	u32 code;
	पूर्णांक ret;

	mutex_lock(&info->lock);
	code = info->ffmt[info->res_type].code;

	अगर (enable) अणु
		अगर (is_code(code, M5MOLS_RESTYPE_MONITOR))
			ret = m5mols_start_monitor(info);
		अन्यथा अगर (is_code(code, M5MOLS_RESTYPE_CAPTURE))
			ret = m5mols_start_capture(info);
		अन्यथा
			ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = m5mols_set_mode(info, REG_PARAMETER);
	पूर्ण

	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops m5mols_video_ops = अणु
	.s_stream	= m5mols_s_stream,
पूर्ण;

अटल पूर्णांक m5mols_sensor_घातer(काष्ठा m5mols_info *info, bool enable)
अणु
	काष्ठा v4l2_subdev *sd = &info->sd;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	स्थिर काष्ठा m5mols_platक्रमm_data *pdata = info->pdata;
	पूर्णांक ret;

	अगर (info->घातer == enable)
		वापस 0;

	अगर (enable) अणु
		अगर (info->set_घातer) अणु
			ret = info->set_घातer(&client->dev, 1);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = regulator_bulk_enable(ARRAY_SIZE(supplies), supplies);
		अगर (ret) अणु
			अगर (info->set_घातer)
				info->set_घातer(&client->dev, 0);
			वापस ret;
		पूर्ण

		gpio_set_value(pdata->gpio_reset, !pdata->reset_polarity);
		info->घातer = 1;

		वापस ret;
	पूर्ण

	ret = regulator_bulk_disable(ARRAY_SIZE(supplies), supplies);
	अगर (ret)
		वापस ret;

	अगर (info->set_घातer)
		info->set_घातer(&client->dev, 0);

	gpio_set_value(pdata->gpio_reset, pdata->reset_polarity);

	info->isp_पढ़ोy = 0;
	info->घातer = 0;

	वापस ret;
पूर्ण

/* m5mols_update_fw - optional firmware update routine */
पूर्णांक __attribute__ ((weak)) m5mols_update_fw(काष्ठा v4l2_subdev *sd,
		पूर्णांक (*set_घातer)(काष्ठा m5mols_info *, bool))
अणु
	वापस 0;
पूर्ण

/**
 * m5mols_fw_start - M-5MOLS पूर्णांकernal ARM controller initialization
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 *
 * Execute the M-5MOLS पूर्णांकernal ARM controller initialization sequence.
 * This function should be called after the supply voltage has been
 * applied and beक्रमe any requests to the device are made.
 */
अटल पूर्णांक m5mols_fw_start(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	पूर्णांक ret;

	atomic_set(&info->irq_करोne, 0);
	/* Wait until I2C slave is initialized in Flash Writer mode */
	ret = m5mols_busy_रुको(sd, FLASH_CAM_START, REG_IN_FLASH_MODE,
			       M5MOLS_I2C_RDY_WAIT_FL | 0xff, -1);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, FLASH_CAM_START, REG_START_ARM_BOOT);
	अगर (!ret)
		ret = m5mols_रुको_पूर्णांकerrupt(sd, REG_INT_MODE, 2000);
	अगर (ret < 0)
		वापस ret;

	info->isp_पढ़ोy = 1;

	ret = m5mols_get_version(sd);
	अगर (!ret)
		ret = m5mols_update_fw(sd, m5mols_sensor_घातer);
	अगर (ret)
		वापस ret;

	v4l2_dbg(1, m5mols_debug, sd, "Success ARM Booting\n");

	ret = m5mols_ग_लिखो(sd, PARM_INTERFACE, REG_INTERFACE_MIPI);
	अगर (!ret)
		ret = m5mols_enable_पूर्णांकerrupt(sd,
				REG_INT_AF | REG_INT_CAPTURE);

	वापस ret;
पूर्ण

/* Execute the lens soft-landing algorithm */
अटल पूर्णांक m5mols_स्वतः_focus_stop(काष्ठा m5mols_info *info)
अणु
	पूर्णांक ret;

	ret = m5mols_ग_लिखो(&info->sd, AF_EXECUTE, REG_AF_STOP);
	अगर (!ret)
		ret = m5mols_ग_लिखो(&info->sd, AF_MODE, REG_AF_POWEROFF);
	अगर (!ret)
		ret = m5mols_busy_रुको(&info->sd, SYSTEM_STATUS, REG_AF_IDLE,
				       0xff, -1);
	वापस ret;
पूर्ण

/**
 * m5mols_s_घातer - Main sensor घातer control function
 * @sd: sub-device, as poपूर्णांकed by काष्ठा v4l2_subdev
 * @on: अगर true, घातers on the device; घातers off otherwise.
 *
 * To prevent अवरोधing the lens when the sensor is घातered off the Soft-Landing
 * algorithm is called where available. The Soft-Landing algorithm availability
 * dependends on the firmware provider.
 */
अटल पूर्णांक m5mols_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	पूर्णांक ret;

	mutex_lock(&info->lock);

	अगर (on) अणु
		ret = m5mols_sensor_घातer(info, true);
		अगर (!ret)
			ret = m5mols_fw_start(sd);
	पूर्ण अन्यथा अणु
		अगर (is_manufacturer(info, REG_SAMSUNG_TECHWIN)) अणु
			ret = m5mols_set_mode(info, REG_MONITOR);
			अगर (!ret)
				ret = m5mols_स्वतः_focus_stop(info);
			अगर (ret < 0)
				v4l2_warn(sd, "Soft landing lens failed\n");
		पूर्ण
		ret = m5mols_sensor_घातer(info, false);

		info->ctrl_sync = 0;
	पूर्ण

	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);

	v4l2_ctrl_handler_log_status(&info->handle, sd->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops m5mols_core_ops = अणु
	.s_घातer	= m5mols_s_घातer,
	.log_status	= m5mols_log_status,
पूर्ण;

/*
 * V4L2 subdev पूर्णांकernal operations
 */
अटल पूर्णांक m5mols_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	*क्रमmat = m5mols_शेष_ffmt[0];
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops m5mols_subdev_पूर्णांकernal_ops = अणु
	.खोलो		= m5mols_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops m5mols_ops = अणु
	.core		= &m5mols_core_ops,
	.pad		= &m5mols_pad_ops,
	.video		= &m5mols_video_ops,
पूर्ण;

अटल irqवापस_t m5mols_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा m5mols_info *info = to_m5mols(data);

	atomic_set(&info->irq_करोne, 1);
	wake_up_पूर्णांकerruptible(&info->irq_रुकोq);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक m5mols_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा m5mols_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	अचिन्हित दीर्घ gpio_flags;
	काष्ठा m5mols_info *info;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!gpio_is_valid(pdata->gpio_reset)) अणु
		dev_err(&client->dev, "No valid RESET GPIO specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(&client->dev, "Interrupt not assigned\n");
		वापस -EINVAL;
	पूर्ण

	info = devm_kzalloc(&client->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->pdata = pdata;
	info->set_घातer	= pdata->set_घातer;

	gpio_flags = pdata->reset_polarity
		   ? GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW;
	ret = devm_gpio_request_one(&client->dev, pdata->gpio_reset, gpio_flags,
				    "M5MOLS_NRST");
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to request gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_regulator_bulk_get(&client->dev, ARRAY_SIZE(supplies),
				      supplies);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	sd = &info->sd;
	v4l2_i2c_subdev_init(sd, client, &m5mols_ops);
	/* Static name; NEVER use in new drivers! */
	strscpy(sd->name, MODULE_NAME, माप(sd->name));
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	sd->पूर्णांकernal_ops = &m5mols_subdev_पूर्णांकernal_ops;
	info->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&sd->entity, 1, &info->pad);
	अगर (ret < 0)
		वापस ret;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;

	init_रुकोqueue_head(&info->irq_रुकोq);
	mutex_init(&info->lock);

	ret = devm_request_irq(&client->dev, client->irq, m5mols_irq_handler,
			       IRQF_TRIGGER_RISING, MODULE_NAME, sd);
	अगर (ret) अणु
		dev_err(&client->dev, "Interrupt request failed: %d\n", ret);
		जाओ error;
	पूर्ण
	info->res_type = M5MOLS_RESTYPE_MONITOR;
	info->ffmt[0] = m5mols_शेष_ffmt[0];
	info->ffmt[1] =	m5mols_शेष_ffmt[1];

	ret = m5mols_sensor_घातer(info, true);
	अगर (ret)
		जाओ error;

	ret = m5mols_fw_start(sd);
	अगर (!ret)
		ret = m5mols_init_controls(sd);

	ret = m5mols_sensor_घातer(info, false);
	अगर (!ret)
		वापस 0;
error:
	media_entity_cleanup(&sd->entity);
	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id m5mols_id[] = अणु
	अणु MODULE_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, m5mols_id);

अटल काष्ठा i2c_driver m5mols_i2c_driver = अणु
	.driver = अणु
		.name	= MODULE_NAME,
	पूर्ण,
	.probe		= m5mols_probe,
	.हटाओ		= m5mols_हटाओ,
	.id_table	= m5mols_id,
पूर्ण;

module_i2c_driver(m5mols_i2c_driver);

MODULE_AUTHOR("HeungJun Kim <riverful.kim@samsung.com>");
MODULE_AUTHOR("Dongsoo Kim <dongsoo45.kim@samsung.com>");
MODULE_DESCRIPTION("Fujitsu M-5MOLS 8M Pixel camera driver");
MODULE_LICENSE("GPL");

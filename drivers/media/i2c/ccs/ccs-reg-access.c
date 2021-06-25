<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/ccs/ccs-reg-access.c
 *
 * Generic driver क्रम MIPI CCS/SMIA/SMIA++ compliant camera sensors
 *
 * Copyright (C) 2020 Intel Corporation
 * Copyright (C) 2011--2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#समावेश <यंत्र/unaligned.h>

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>

#समावेश "ccs.h"
#समावेश "ccs-limits.h"

अटल u32 भग्न_to_u32_mul_1000000(काष्ठा i2c_client *client, u32 phloat)
अणु
	s32 exp;
	u64 man;

	अगर (phloat >= 0x80000000) अणु
		dev_err(&client->dev, "this is a negative number\n");
		वापस 0;
	पूर्ण

	अगर (phloat == 0x7f800000)
		वापस ~0; /* Inf. */

	अगर ((phloat & 0x7f800000) == 0x7f800000) अणु
		dev_err(&client->dev, "NaN or other special number\n");
		वापस 0;
	पूर्ण

	/* Valid हालs begin here */
	अगर (phloat == 0)
		वापस 0; /* Valid zero */

	अगर (phloat > 0x4f800000)
		वापस ~0; /* larger than 4294967295 */

	/*
	 * Unbias exponent (note how phloat is now guaranteed to
	 * have 0 in the high bit)
	 */
	exp = ((पूर्णांक32_t)phloat >> 23) - 127;

	/* Extract mantissa, add missing '1' bit and it's in MHz */
	man = ((phloat & 0x7fffff) | 0x800000) * 1000000ULL;

	अगर (exp < 0)
		man >>= -exp;
	अन्यथा
		man <<= exp;

	man >>= 23; /* Remove mantissa bias */

	वापस man & 0xffffffff;
पूर्ण


/*
 * Read a 8/16/32-bit i2c रेजिस्टर.  The value is वापसed in 'val'.
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक ____ccs_पढ़ो_addr(काष्ठा ccs_sensor *sensor, u16 reg, u16 len,
			     u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	काष्ठा i2c_msg msg;
	अचिन्हित अक्षर data_buf[माप(u32)] = अणु 0 पूर्ण;
	अचिन्हित अक्षर offset_buf[माप(u16)];
	पूर्णांक r;

	अगर (len > माप(data_buf))
		वापस -EINVAL;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = माप(offset_buf);
	msg.buf = offset_buf;
	put_unaligned_be16(reg, offset_buf);

	r = i2c_transfer(client->adapter, &msg, 1);
	अगर (r != 1) अणु
		अगर (r >= 0)
			r = -EBUSY;
		जाओ err;
	पूर्ण

	msg.len = len;
	msg.flags = I2C_M_RD;
	msg.buf = &data_buf[माप(data_buf) - len];

	r = i2c_transfer(client->adapter, &msg, 1);
	अगर (r != 1) अणु
		अगर (r >= 0)
			r = -EBUSY;
		जाओ err;
	पूर्ण

	*val = get_unaligned_be32(data_buf);

	वापस 0;

err:
	dev_err(&client->dev, "read from offset 0x%x error %d\n", reg, r);

	वापस r;
पूर्ण

/* Read a रेजिस्टर using 8-bit access only. */
अटल पूर्णांक ____ccs_पढ़ो_addr_8only(काष्ठा ccs_sensor *sensor, u16 reg,
				   u16 len, u32 *val)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rval;

	*val = 0;

	क्रम (i = 0; i < len; i++) अणु
		u32 val8;

		rval = ____ccs_पढ़ो_addr(sensor, reg + i, 1, &val8);
		अगर (rval < 0)
			वापस rval;
		*val |= val8 << ((len - i - 1) << 3);
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक ccs_reg_width(u32 reg)
अणु
	अगर (reg & CCS_FL_16BIT)
		वापस माप(u16);
	अगर (reg & CCS_FL_32BIT)
		वापस माप(u32);

	वापस माप(u8);
पूर्ण

अटल u32 ireal32_to_u32_mul_1000000(काष्ठा i2c_client *client, u32 val)
अणु
	अगर (val >> 10 > U32_MAX / 15625) अणु
		dev_warn(&client->dev, "value %u overflows!\n", val);
		वापस U32_MAX;
	पूर्ण

	वापस ((val >> 10) * 15625) +
		(val & GENMASK(9, 0)) * 15625 / 1024;
पूर्ण

u32 ccs_reg_conv(काष्ठा ccs_sensor *sensor, u32 reg, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);

	अगर (reg & CCS_FL_FLOAT_IREAL) अणु
		अगर (CCS_LIM(sensor, CLOCK_CAPA_TYPE_CAPABILITY) &
		    CCS_CLOCK_CAPA_TYPE_CAPABILITY_IREAL)
			val = ireal32_to_u32_mul_1000000(client, val);
		अन्यथा
			val = भग्न_to_u32_mul_1000000(client, val);
	पूर्ण अन्यथा अगर (reg & CCS_FL_IREAL) अणु
		val = ireal32_to_u32_mul_1000000(client, val);
	पूर्ण

	वापस val;
पूर्ण

/*
 * Read a 8/16/32-bit i2c रेजिस्टर.  The value is वापसed in 'val'.
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक __ccs_पढ़ो_addr(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val,
			   bool only8, bool conv)
अणु
	अचिन्हित पूर्णांक len = ccs_reg_width(reg);
	पूर्णांक rval;

	अगर (!only8)
		rval = ____ccs_पढ़ो_addr(sensor, CCS_REG_ADDR(reg), len, val);
	अन्यथा
		rval = ____ccs_पढ़ो_addr_8only(sensor, CCS_REG_ADDR(reg), len,
					       val);
	अगर (rval < 0)
		वापस rval;

	अगर (!conv)
		वापस 0;

	*val = ccs_reg_conv(sensor, reg, *val);

	वापस 0;
पूर्ण

अटल पूर्णांक __ccs_पढ़ो_data(काष्ठा ccs_reg *regs, माप_प्रकार num_regs,
			   u32 reg, u32 *val)
अणु
	अचिन्हित पूर्णांक width = ccs_reg_width(reg);
	माप_प्रकार i;

	क्रम (i = 0; i < num_regs; i++, regs++) अणु
		u8 *data;

		अगर (regs->addr + regs->len < CCS_REG_ADDR(reg) + width)
			जारी;

		अगर (regs->addr > CCS_REG_ADDR(reg))
			अवरोध;

		data = &regs->value[CCS_REG_ADDR(reg) - regs->addr];

		चयन (width) अणु
		हाल माप(u8):
			*val = *data;
			अवरोध;
		हाल माप(u16):
			*val = get_unaligned_be16(data);
			अवरोध;
		हाल माप(u32):
			*val = get_unaligned_be32(data);
			अवरोध;
		शेष:
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक ccs_पढ़ो_data(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val)
अणु
	अगर (!__ccs_पढ़ो_data(sensor->sdata.sensor_पढ़ो_only_regs,
			     sensor->sdata.num_sensor_पढ़ो_only_regs,
			     reg, val))
		वापस 0;

	वापस __ccs_पढ़ो_data(sensor->mdata.module_पढ़ो_only_regs,
			       sensor->mdata.num_module_पढ़ो_only_regs,
			       reg, val);
पूर्ण

अटल पूर्णांक ccs_पढ़ो_addr_raw(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val,
			     bool क्रमce8, bool quirk, bool conv, bool data)
अणु
	पूर्णांक rval;

	अगर (data) अणु
		rval = ccs_पढ़ो_data(sensor, reg, val);
		अगर (!rval)
			वापस 0;
	पूर्ण

	अगर (quirk) अणु
		*val = 0;
		rval = ccs_call_quirk(sensor, reg_access, false, &reg, val);
		अगर (rval == -ENOIOCTLCMD)
			वापस 0;
		अगर (rval < 0)
			वापस rval;

		अगर (क्रमce8)
			वापस __ccs_पढ़ो_addr(sensor, reg, val, true, conv);
	पूर्ण

	वापस __ccs_पढ़ो_addr(sensor, reg, val,
			       ccs_needs_quirk(sensor,
					       CCS_QUIRK_FLAG_8BIT_READ_ONLY),
			       conv);
पूर्ण

पूर्णांक ccs_पढ़ो_addr(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val)
अणु
	वापस ccs_पढ़ो_addr_raw(sensor, reg, val, false, true, true, true);
पूर्ण

पूर्णांक ccs_पढ़ो_addr_8only(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val)
अणु
	वापस ccs_पढ़ो_addr_raw(sensor, reg, val, true, true, true, true);
पूर्ण

पूर्णांक ccs_पढ़ो_addr_noconv(काष्ठा ccs_sensor *sensor, u32 reg, u32 *val)
अणु
	वापस ccs_पढ़ो_addr_raw(sensor, reg, val, false, true, false, true);
पूर्ण

अटल पूर्णांक ccs_ग_लिखो_retry(काष्ठा i2c_client *client, काष्ठा i2c_msg *msg)
अणु
	अचिन्हित पूर्णांक retries;
	पूर्णांक r;

	क्रम (retries = 0; retries < 10; retries++) अणु
		/*
		 * Due to unknown reason sensor stops responding. This
		 * loop is a temporaty solution until the root cause
		 * is found.
		 */
		r = i2c_transfer(client->adapter, msg, 1);
		अगर (r != 1) अणु
			usleep_range(1000, 2000);
			जारी;
		पूर्ण

		अगर (retries)
			dev_err(&client->dev,
				"sensor i2c stall encountered. retries: %d\n",
				retries);
		वापस 0;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक ccs_ग_लिखो_addr_no_quirk(काष्ठा ccs_sensor *sensor, u32 reg, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	काष्ठा i2c_msg msg;
	अचिन्हित अक्षर data[6];
	अचिन्हित पूर्णांक len = ccs_reg_width(reg);
	पूर्णांक r;

	अगर (len > माप(data) - 2)
		वापस -EINVAL;

	msg.addr = client->addr;
	msg.flags = 0; /* Write */
	msg.len = 2 + len;
	msg.buf = data;

	put_unaligned_be16(CCS_REG_ADDR(reg), data);
	put_unaligned_be32(val << (8 * (माप(val) - len)), data + 2);

	dev_dbg(&client->dev, "writing reg 0x%4.4x value 0x%*.*x (%u)\n",
		CCS_REG_ADDR(reg), ccs_reg_width(reg) << 1,
		ccs_reg_width(reg) << 1, val, val);

	r = ccs_ग_लिखो_retry(client, &msg);
	अगर (r)
		dev_err(&client->dev,
			"wrote 0x%x to offset 0x%x error %d\n", val,
			CCS_REG_ADDR(reg), r);

	वापस r;
पूर्ण

/*
 * Write to a 8/16-bit रेजिस्टर.
 * Returns zero अगर successful, or non-zero otherwise.
 */
पूर्णांक ccs_ग_लिखो_addr(काष्ठा ccs_sensor *sensor, u32 reg, u32 val)
अणु
	पूर्णांक rval;

	rval = ccs_call_quirk(sensor, reg_access, true, &reg, &val);
	अगर (rval == -ENOIOCTLCMD)
		वापस 0;
	अगर (rval < 0)
		वापस rval;

	वापस ccs_ग_लिखो_addr_no_quirk(sensor, reg, val);
पूर्ण

#घोषणा MAX_WRITE_LEN	32U

पूर्णांक ccs_ग_लिखो_data_regs(काष्ठा ccs_sensor *sensor, काष्ठा ccs_reg *regs,
			माप_प्रकार num_regs)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	अचिन्हित अक्षर buf[2 + MAX_WRITE_LEN];
	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.buf = buf,
	पूर्ण;
	माप_प्रकार i;

	क्रम (i = 0; i < num_regs; i++, regs++) अणु
		अचिन्हित अक्षर *regdata = regs->value;
		अचिन्हित पूर्णांक j;

		क्रम (j = 0; j < regs->len;
		     j += msg.len - 2, regdata += msg.len - 2) अणु
			अक्षर prपूर्णांकbuf[(MAX_WRITE_LEN << 1) +
				      1 /* \0 */] = अणु 0 पूर्ण;
			पूर्णांक rval;

			msg.len = min(regs->len - j, MAX_WRITE_LEN);

			bin2hex(prपूर्णांकbuf, regdata, msg.len);
			dev_dbg(&client->dev,
				"writing msr reg 0x%4.4x value 0x%s\n",
				regs->addr + j, prपूर्णांकbuf);

			put_unaligned_be16(regs->addr + j, buf);
			स_नकल(buf + 2, regdata, msg.len);

			msg.len += 2;

			rval = ccs_ग_लिखो_retry(client, &msg);
			अगर (rval) अणु
				dev_err(&client->dev,
					"error writing %u octets to address 0x%4.4x\n",
					msg.len, regs->addr + j);
				वापस rval;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

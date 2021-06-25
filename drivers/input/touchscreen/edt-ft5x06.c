<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 Simon Budig, <simon.budig@kernelconcepts.de>
 * Daniel Wagener <daniel.wagener@kernelconcepts.de> (M09 firmware support)
 * Lothar Waथmann <LW@KARO-electronics.de> (DT support)
 */

/*
 * This is a driver क्रम the EDT "Polytouch" family of touch controllers
 * based on the FocalTech FT5x06 line of chips.
 *
 * Development of this driver has been sponsored by Glyn:
 *    http://www.glyn.com/Products/Displays
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा WORK_REGISTER_THRESHOLD		0x00
#घोषणा WORK_REGISTER_REPORT_RATE	0x08
#घोषणा WORK_REGISTER_GAIN		0x30
#घोषणा WORK_REGISTER_OFFSET		0x31
#घोषणा WORK_REGISTER_NUM_X		0x33
#घोषणा WORK_REGISTER_NUM_Y		0x34

#घोषणा PMOD_REGISTER_ACTIVE		0x00
#घोषणा PMOD_REGISTER_HIBERNATE		0x03

#घोषणा M09_REGISTER_THRESHOLD		0x80
#घोषणा M09_REGISTER_GAIN		0x92
#घोषणा M09_REGISTER_OFFSET		0x93
#घोषणा M09_REGISTER_NUM_X		0x94
#घोषणा M09_REGISTER_NUM_Y		0x95

#घोषणा EV_REGISTER_THRESHOLD		0x40
#घोषणा EV_REGISTER_GAIN		0x41
#घोषणा EV_REGISTER_OFFSET_Y		0x45
#घोषणा EV_REGISTER_OFFSET_X		0x46

#घोषणा NO_REGISTER			0xff

#घोषणा WORK_REGISTER_OPMODE		0x3c
#घोषणा FACTORY_REGISTER_OPMODE		0x01
#घोषणा PMOD_REGISTER_OPMODE		0xa5

#घोषणा TOUCH_EVENT_DOWN		0x00
#घोषणा TOUCH_EVENT_UP			0x01
#घोषणा TOUCH_EVENT_ON			0x02
#घोषणा TOUCH_EVENT_RESERVED		0x03

#घोषणा EDT_NAME_LEN			23
#घोषणा EDT_SWITCH_MODE_RETRIES		10
#घोषणा EDT_SWITCH_MODE_DELAY		5 /* msec */
#घोषणा EDT_RAW_DATA_RETRIES		100
#घोषणा EDT_RAW_DATA_DELAY		1000 /* usec */

#घोषणा EDT_DEFAULT_NUM_X		1024
#घोषणा EDT_DEFAULT_NUM_Y		1024

क्रमागत edt_pmode अणु
	EDT_PMODE_NOT_SUPPORTED,
	EDT_PMODE_HIBERNATE,
	EDT_PMODE_POWEROFF,
पूर्ण;

क्रमागत edt_ver अणु
	EDT_M06,
	EDT_M09,
	EDT_M12,
	EV_FT,
	GENERIC_FT,
पूर्ण;

काष्ठा edt_reg_addr अणु
	पूर्णांक reg_threshold;
	पूर्णांक reg_report_rate;
	पूर्णांक reg_gain;
	पूर्णांक reg_offset;
	पूर्णांक reg_offset_x;
	पूर्णांक reg_offset_y;
	पूर्णांक reg_num_x;
	पूर्णांक reg_num_y;
पूर्ण;

काष्ठा edt_ft5x06_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा touchscreen_properties prop;
	u16 num_x;
	u16 num_y;
	काष्ठा regulator *vcc;

	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *wake_gpio;

#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *debug_dir;
	u8 *raw_buffer;
	माप_प्रकार raw_bufsize;
#पूर्ण_अगर

	काष्ठा mutex mutex;
	bool factory_mode;
	क्रमागत edt_pmode suspend_mode;
	पूर्णांक threshold;
	पूर्णांक gain;
	पूर्णांक offset;
	पूर्णांक offset_x;
	पूर्णांक offset_y;
	पूर्णांक report_rate;
	पूर्णांक max_support_poपूर्णांकs;

	अक्षर name[EDT_NAME_LEN];

	काष्ठा edt_reg_addr reg_addr;
	क्रमागत edt_ver version;
पूर्ण;

काष्ठा edt_i2c_chip_data अणु
	पूर्णांक  max_support_poपूर्णांकs;
पूर्ण;

अटल पूर्णांक edt_ft5x06_ts_पढ़ोग_लिखो(काष्ठा i2c_client *client,
				   u16 wr_len, u8 *wr_buf,
				   u16 rd_len, u8 *rd_buf)
अणु
	काष्ठा i2c_msg wrmsg[2];
	पूर्णांक i = 0;
	पूर्णांक ret;

	अगर (wr_len) अणु
		wrmsg[i].addr  = client->addr;
		wrmsg[i].flags = 0;
		wrmsg[i].len = wr_len;
		wrmsg[i].buf = wr_buf;
		i++;
	पूर्ण
	अगर (rd_len) अणु
		wrmsg[i].addr  = client->addr;
		wrmsg[i].flags = I2C_M_RD;
		wrmsg[i].len = rd_len;
		wrmsg[i].buf = rd_buf;
		i++;
	पूर्ण

	ret = i2c_transfer(client->adapter, wrmsg, i);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != i)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल bool edt_ft5x06_ts_check_crc(काष्ठा edt_ft5x06_ts_data *tsdata,
				    u8 *buf, पूर्णांक buflen)
अणु
	पूर्णांक i;
	u8 crc = 0;

	क्रम (i = 0; i < buflen - 1; i++)
		crc ^= buf[i];

	अगर (crc != buf[buflen-1]) अणु
		dev_err_ratelimited(&tsdata->client->dev,
				    "crc error: 0x%02x expected, got 0x%02x\n",
				    crc, buf[buflen-1]);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल irqवापस_t edt_ft5x06_ts_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा edt_ft5x06_ts_data *tsdata = dev_id;
	काष्ठा device *dev = &tsdata->client->dev;
	u8 cmd;
	u8 rdbuf[63];
	पूर्णांक i, type, x, y, id;
	पूर्णांक offset, tplen, datalen, crclen;
	पूर्णांक error;

	चयन (tsdata->version) अणु
	हाल EDT_M06:
		cmd = 0xf9; /* tell the controller to send touch data */
		offset = 5; /* where the actual touch data starts */
		tplen = 4;  /* data comes in so called frames */
		crclen = 1; /* length of the crc data */
		अवरोध;

	हाल EDT_M09:
	हाल EDT_M12:
	हाल EV_FT:
	हाल GENERIC_FT:
		cmd = 0x0;
		offset = 3;
		tplen = 6;
		crclen = 0;
		अवरोध;

	शेष:
		जाओ out;
	पूर्ण

	स_रखो(rdbuf, 0, माप(rdbuf));
	datalen = tplen * tsdata->max_support_poपूर्णांकs + offset + crclen;

	error = edt_ft5x06_ts_पढ़ोग_लिखो(tsdata->client,
					माप(cmd), &cmd,
					datalen, rdbuf);
	अगर (error) अणु
		dev_err_ratelimited(dev, "Unable to fetch data, error: %d\n",
				    error);
		जाओ out;
	पूर्ण

	/* M09/M12 करोes not send header or CRC */
	अगर (tsdata->version == EDT_M06) अणु
		अगर (rdbuf[0] != 0xaa || rdbuf[1] != 0xaa ||
			rdbuf[2] != datalen) अणु
			dev_err_ratelimited(dev,
					"Unexpected header: %02x%02x%02x!\n",
					rdbuf[0], rdbuf[1], rdbuf[2]);
			जाओ out;
		पूर्ण

		अगर (!edt_ft5x06_ts_check_crc(tsdata, rdbuf, datalen))
			जाओ out;
	पूर्ण

	क्रम (i = 0; i < tsdata->max_support_poपूर्णांकs; i++) अणु
		u8 *buf = &rdbuf[i * tplen + offset];

		type = buf[0] >> 6;
		/* ignore Reserved events */
		अगर (type == TOUCH_EVENT_RESERVED)
			जारी;

		/* M06 someबार sends bogus coordinates in TOUCH_DOWN */
		अगर (tsdata->version == EDT_M06 && type == TOUCH_EVENT_DOWN)
			जारी;

		x = get_unaligned_be16(buf) & 0x0fff;
		y = get_unaligned_be16(buf + 2) & 0x0fff;
		/* The FT5x26 send the y coordinate first */
		अगर (tsdata->version == EV_FT)
			swap(x, y);

		id = (buf[2] >> 4) & 0x0f;

		input_mt_slot(tsdata->input, id);
		अगर (input_mt_report_slot_state(tsdata->input, MT_TOOL_FINGER,
					       type != TOUCH_EVENT_UP))
			touchscreen_report_pos(tsdata->input, &tsdata->prop,
					       x, y, true);
	पूर्ण

	input_mt_report_poपूर्णांकer_emulation(tsdata->input, true);
	input_sync(tsdata->input);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक edt_ft5x06_रेजिस्टर_ग_लिखो(काष्ठा edt_ft5x06_ts_data *tsdata,
				     u8 addr, u8 value)
अणु
	u8 wrbuf[4];

	चयन (tsdata->version) अणु
	हाल EDT_M06:
		wrbuf[0] = tsdata->factory_mode ? 0xf3 : 0xfc;
		wrbuf[1] = tsdata->factory_mode ? addr & 0x7f : addr & 0x3f;
		wrbuf[2] = value;
		wrbuf[3] = wrbuf[0] ^ wrbuf[1] ^ wrbuf[2];
		वापस edt_ft5x06_ts_पढ़ोग_लिखो(tsdata->client, 4,
					wrbuf, 0, शून्य);

	हाल EDT_M09:
	हाल EDT_M12:
	हाल EV_FT:
	हाल GENERIC_FT:
		wrbuf[0] = addr;
		wrbuf[1] = value;

		वापस edt_ft5x06_ts_पढ़ोग_लिखो(tsdata->client, 2,
					wrbuf, 0, शून्य);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक edt_ft5x06_रेजिस्टर_पढ़ो(काष्ठा edt_ft5x06_ts_data *tsdata,
				    u8 addr)
अणु
	u8 wrbuf[2], rdbuf[2];
	पूर्णांक error;

	चयन (tsdata->version) अणु
	हाल EDT_M06:
		wrbuf[0] = tsdata->factory_mode ? 0xf3 : 0xfc;
		wrbuf[1] = tsdata->factory_mode ? addr & 0x7f : addr & 0x3f;
		wrbuf[1] |= tsdata->factory_mode ? 0x80 : 0x40;

		error = edt_ft5x06_ts_पढ़ोग_लिखो(tsdata->client, 2, wrbuf, 2,
						rdbuf);
		अगर (error)
			वापस error;

		अगर ((wrbuf[0] ^ wrbuf[1] ^ rdbuf[0]) != rdbuf[1]) अणु
			dev_err(&tsdata->client->dev,
				"crc error: 0x%02x expected, got 0x%02x\n",
				wrbuf[0] ^ wrbuf[1] ^ rdbuf[0],
				rdbuf[1]);
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल EDT_M09:
	हाल EDT_M12:
	हाल EV_FT:
	हाल GENERIC_FT:
		wrbuf[0] = addr;
		error = edt_ft5x06_ts_पढ़ोग_लिखो(tsdata->client, 1,
						wrbuf, 1, rdbuf);
		अगर (error)
			वापस error;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस rdbuf[0];
पूर्ण

काष्ठा edt_ft5x06_attribute अणु
	काष्ठा device_attribute dattr;
	माप_प्रकार field_offset;
	u8 limit_low;
	u8 limit_high;
	u8 addr_m06;
	u8 addr_m09;
	u8 addr_ev;
पूर्ण;

#घोषणा EDT_ATTR(_field, _mode, _addr_m06, _addr_m09, _addr_ev,		\
		_limit_low, _limit_high)				\
	काष्ठा edt_ft5x06_attribute edt_ft5x06_attr_##_field = अणु	\
		.dattr = __ATTR(_field, _mode,				\
				edt_ft5x06_setting_show,		\
				edt_ft5x06_setting_store),		\
		.field_offset = दुरत्व(काष्ठा edt_ft5x06_ts_data, _field), \
		.addr_m06 = _addr_m06,					\
		.addr_m09 = _addr_m09,					\
		.addr_ev  = _addr_ev,					\
		.limit_low = _limit_low,				\
		.limit_high = _limit_high,				\
	पूर्ण

अटल sमाप_प्रकार edt_ft5x06_setting_show(काष्ठा device *dev,
				       काष्ठा device_attribute *dattr,
				       अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा edt_ft5x06_ts_data *tsdata = i2c_get_clientdata(client);
	काष्ठा edt_ft5x06_attribute *attr =
			container_of(dattr, काष्ठा edt_ft5x06_attribute, dattr);
	u8 *field = (u8 *)tsdata + attr->field_offset;
	पूर्णांक val;
	माप_प्रकार count = 0;
	पूर्णांक error = 0;
	u8 addr;

	mutex_lock(&tsdata->mutex);

	अगर (tsdata->factory_mode) अणु
		error = -EIO;
		जाओ out;
	पूर्ण

	चयन (tsdata->version) अणु
	हाल EDT_M06:
		addr = attr->addr_m06;
		अवरोध;

	हाल EDT_M09:
	हाल EDT_M12:
	हाल GENERIC_FT:
		addr = attr->addr_m09;
		अवरोध;

	हाल EV_FT:
		addr = attr->addr_ev;
		अवरोध;

	शेष:
		error = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (addr != NO_REGISTER) अणु
		val = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata, addr);
		अगर (val < 0) अणु
			error = val;
			dev_err(&tsdata->client->dev,
				"Failed to fetch attribute %s, error %d\n",
				dattr->attr.name, error);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		val = *field;
	पूर्ण

	अगर (val != *field) अणु
		dev_warn(&tsdata->client->dev,
			 "%s: read (%d) and stored value (%d) differ\n",
			 dattr->attr.name, val, *field);
		*field = val;
	पूर्ण

	count = scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);
out:
	mutex_unlock(&tsdata->mutex);
	वापस error ?: count;
पूर्ण

अटल sमाप_प्रकार edt_ft5x06_setting_store(काष्ठा device *dev,
					काष्ठा device_attribute *dattr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा edt_ft5x06_ts_data *tsdata = i2c_get_clientdata(client);
	काष्ठा edt_ft5x06_attribute *attr =
			container_of(dattr, काष्ठा edt_ft5x06_attribute, dattr);
	u8 *field = (u8 *)tsdata + attr->field_offset;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;
	u8 addr;

	mutex_lock(&tsdata->mutex);

	अगर (tsdata->factory_mode) अणु
		error = -EIO;
		जाओ out;
	पूर्ण

	error = kstrtouपूर्णांक(buf, 0, &val);
	अगर (error)
		जाओ out;

	अगर (val < attr->limit_low || val > attr->limit_high) अणु
		error = -दुस्फल;
		जाओ out;
	पूर्ण

	चयन (tsdata->version) अणु
	हाल EDT_M06:
		addr = attr->addr_m06;
		अवरोध;

	हाल EDT_M09:
	हाल EDT_M12:
	हाल GENERIC_FT:
		addr = attr->addr_m09;
		अवरोध;

	हाल EV_FT:
		addr = attr->addr_ev;
		अवरोध;

	शेष:
		error = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (addr != NO_REGISTER) अणु
		error = edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, addr, val);
		अगर (error) अणु
			dev_err(&tsdata->client->dev,
				"Failed to update attribute %s, error: %d\n",
				dattr->attr.name, error);
			जाओ out;
		पूर्ण
	पूर्ण
	*field = val;

out:
	mutex_unlock(&tsdata->mutex);
	वापस error ?: count;
पूर्ण

/* m06, m09: range 0-31, m12: range 0-5 */
अटल EDT_ATTR(gain, S_IWUSR | S_IRUGO, WORK_REGISTER_GAIN,
		M09_REGISTER_GAIN, EV_REGISTER_GAIN, 0, 31);
/* m06, m09: range 0-31, m12: range 0-16 */
अटल EDT_ATTR(offset, S_IWUSR | S_IRUGO, WORK_REGISTER_OFFSET,
		M09_REGISTER_OFFSET, NO_REGISTER, 0, 31);
/* m06, m09, m12: no supported, ev_ft: range 0-80 */
अटल EDT_ATTR(offset_x, S_IWUSR | S_IRUGO, NO_REGISTER, NO_REGISTER,
		EV_REGISTER_OFFSET_X, 0, 80);
/* m06, m09, m12: no supported, ev_ft: range 0-80 */
अटल EDT_ATTR(offset_y, S_IWUSR | S_IRUGO, NO_REGISTER, NO_REGISTER,
		EV_REGISTER_OFFSET_Y, 0, 80);
/* m06: range 20 to 80, m09: range 0 to 30, m12: range 1 to 255... */
अटल EDT_ATTR(threshold, S_IWUSR | S_IRUGO, WORK_REGISTER_THRESHOLD,
		M09_REGISTER_THRESHOLD, EV_REGISTER_THRESHOLD, 0, 255);
/* m06: range 3 to 14, m12: (0x64: 100Hz) */
अटल EDT_ATTR(report_rate, S_IWUSR | S_IRUGO, WORK_REGISTER_REPORT_RATE,
		NO_REGISTER, NO_REGISTER, 0, 255);

अटल काष्ठा attribute *edt_ft5x06_attrs[] = अणु
	&edt_ft5x06_attr_gain.dattr.attr,
	&edt_ft5x06_attr_offset.dattr.attr,
	&edt_ft5x06_attr_offset_x.dattr.attr,
	&edt_ft5x06_attr_offset_y.dattr.attr,
	&edt_ft5x06_attr_threshold.dattr.attr,
	&edt_ft5x06_attr_report_rate.dattr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group edt_ft5x06_attr_group = अणु
	.attrs = edt_ft5x06_attrs,
पूर्ण;

अटल व्योम edt_ft5x06_restore_reg_parameters(काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
	काष्ठा edt_reg_addr *reg_addr = &tsdata->reg_addr;

	edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, reg_addr->reg_threshold,
				  tsdata->threshold);
	edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, reg_addr->reg_gain,
				  tsdata->gain);
	अगर (reg_addr->reg_offset != NO_REGISTER)
		edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, reg_addr->reg_offset,
					  tsdata->offset);
	अगर (reg_addr->reg_offset_x != NO_REGISTER)
		edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, reg_addr->reg_offset_x,
					  tsdata->offset_x);
	अगर (reg_addr->reg_offset_y != NO_REGISTER)
		edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, reg_addr->reg_offset_y,
					  tsdata->offset_y);
	अगर (reg_addr->reg_report_rate != NO_REGISTER)
		edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, reg_addr->reg_report_rate,
				  tsdata->report_rate);

पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक edt_ft5x06_factory_mode(काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
	काष्ठा i2c_client *client = tsdata->client;
	पूर्णांक retries = EDT_SWITCH_MODE_RETRIES;
	पूर्णांक ret;
	पूर्णांक error;

	अगर (tsdata->version != EDT_M06) अणु
		dev_err(&client->dev,
			"No factory mode support for non-M06 devices\n");
		वापस -EINVAL;
	पूर्ण

	disable_irq(client->irq);

	अगर (!tsdata->raw_buffer) अणु
		tsdata->raw_bufsize = tsdata->num_x * tsdata->num_y *
				      माप(u16);
		tsdata->raw_buffer = kzalloc(tsdata->raw_bufsize, GFP_KERNEL);
		अगर (!tsdata->raw_buffer) अणु
			error = -ENOMEM;
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* mode रेजिस्टर is 0x3c when in the work mode */
	error = edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, WORK_REGISTER_OPMODE, 0x03);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to switch to factory mode, error %d\n", error);
		जाओ err_out;
	पूर्ण

	tsdata->factory_mode = true;
	करो अणु
		mdelay(EDT_SWITCH_MODE_DELAY);
		/* mode रेजिस्टर is 0x01 when in factory mode */
		ret = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata, FACTORY_REGISTER_OPMODE);
		अगर (ret == 0x03)
			अवरोध;
	पूर्ण जबतक (--retries > 0);

	अगर (retries == 0) अणु
		dev_err(&client->dev, "not in factory mode after %dms.\n",
			EDT_SWITCH_MODE_RETRIES * EDT_SWITCH_MODE_DELAY);
		error = -EIO;
		जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	kमुक्त(tsdata->raw_buffer);
	tsdata->raw_buffer = शून्य;
	tsdata->factory_mode = false;
	enable_irq(client->irq);

	वापस error;
पूर्ण

अटल पूर्णांक edt_ft5x06_work_mode(काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
	काष्ठा i2c_client *client = tsdata->client;
	पूर्णांक retries = EDT_SWITCH_MODE_RETRIES;
	पूर्णांक ret;
	पूर्णांक error;

	/* mode रेजिस्टर is 0x01 when in the factory mode */
	error = edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, FACTORY_REGISTER_OPMODE, 0x1);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to switch to work mode, error: %d\n", error);
		वापस error;
	पूर्ण

	tsdata->factory_mode = false;

	करो अणु
		mdelay(EDT_SWITCH_MODE_DELAY);
		/* mode रेजिस्टर is 0x01 when in factory mode */
		ret = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata, WORK_REGISTER_OPMODE);
		अगर (ret == 0x01)
			अवरोध;
	पूर्ण जबतक (--retries > 0);

	अगर (retries == 0) अणु
		dev_err(&client->dev, "not in work mode after %dms.\n",
			EDT_SWITCH_MODE_RETRIES * EDT_SWITCH_MODE_DELAY);
		tsdata->factory_mode = true;
		वापस -EIO;
	पूर्ण

	kमुक्त(tsdata->raw_buffer);
	tsdata->raw_buffer = शून्य;

	edt_ft5x06_restore_reg_parameters(tsdata);
	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक edt_ft5x06_debugfs_mode_get(व्योम *data, u64 *mode)
अणु
	काष्ठा edt_ft5x06_ts_data *tsdata = data;

	*mode = tsdata->factory_mode;

	वापस 0;
पूर्ण;

अटल पूर्णांक edt_ft5x06_debugfs_mode_set(व्योम *data, u64 mode)
अणु
	काष्ठा edt_ft5x06_ts_data *tsdata = data;
	पूर्णांक retval = 0;

	अगर (mode > 1)
		वापस -दुस्फल;

	mutex_lock(&tsdata->mutex);

	अगर (mode != tsdata->factory_mode) अणु
		retval = mode ? edt_ft5x06_factory_mode(tsdata) :
				edt_ft5x06_work_mode(tsdata);
	पूर्ण

	mutex_unlock(&tsdata->mutex);

	वापस retval;
पूर्ण;

DEFINE_SIMPLE_ATTRIBUTE(debugfs_mode_fops, edt_ft5x06_debugfs_mode_get,
			edt_ft5x06_debugfs_mode_set, "%llu\n");

अटल sमाप_प्रकार edt_ft5x06_debugfs_raw_data_पढ़ो(काष्ठा file *file,
				अक्षर __user *buf, माप_प्रकार count, loff_t *off)
अणु
	काष्ठा edt_ft5x06_ts_data *tsdata = file->निजी_data;
	काष्ठा i2c_client *client = tsdata->client;
	पूर्णांक retries  = EDT_RAW_DATA_RETRIES;
	पूर्णांक val, i, error;
	माप_प्रकार पढ़ो = 0;
	पूर्णांक colbytes;
	अक्षर wrbuf[3];
	u8 *rdbuf;

	अगर (*off < 0 || *off >= tsdata->raw_bufsize)
		वापस 0;

	mutex_lock(&tsdata->mutex);

	अगर (!tsdata->factory_mode || !tsdata->raw_buffer) अणु
		error = -EIO;
		जाओ out;
	पूर्ण

	error = edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, 0x08, 0x01);
	अगर (error) अणु
		dev_dbg(&client->dev,
			"failed to write 0x08 register, error %d\n", error);
		जाओ out;
	पूर्ण

	करो अणु
		usleep_range(EDT_RAW_DATA_DELAY, EDT_RAW_DATA_DELAY + 100);
		val = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata, 0x08);
		अगर (val < 1)
			अवरोध;
	पूर्ण जबतक (--retries > 0);

	अगर (val < 0) अणु
		error = val;
		dev_dbg(&client->dev,
			"failed to read 0x08 register, error %d\n", error);
		जाओ out;
	पूर्ण

	अगर (retries == 0) अणु
		dev_dbg(&client->dev,
			"timed out waiting for register to settle\n");
		error = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	rdbuf = tsdata->raw_buffer;
	colbytes = tsdata->num_y * माप(u16);

	wrbuf[0] = 0xf5;
	wrbuf[1] = 0x0e;
	क्रम (i = 0; i < tsdata->num_x; i++) अणु
		wrbuf[2] = i;  /* column index */
		error = edt_ft5x06_ts_पढ़ोग_लिखो(tsdata->client,
						माप(wrbuf), wrbuf,
						colbytes, rdbuf);
		अगर (error)
			जाओ out;

		rdbuf += colbytes;
	पूर्ण

	पढ़ो = min_t(माप_प्रकार, count, tsdata->raw_bufsize - *off);
	अगर (copy_to_user(buf, tsdata->raw_buffer + *off, पढ़ो)) अणु
		error = -EFAULT;
		जाओ out;
	पूर्ण

	*off += पढ़ो;
out:
	mutex_unlock(&tsdata->mutex);
	वापस error ?: पढ़ो;
पूर्ण;

अटल स्थिर काष्ठा file_operations debugfs_raw_data_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = edt_ft5x06_debugfs_raw_data_पढ़ो,
पूर्ण;

अटल व्योम edt_ft5x06_ts_prepare_debugfs(काष्ठा edt_ft5x06_ts_data *tsdata,
					  स्थिर अक्षर *debugfs_name)
अणु
	tsdata->debug_dir = debugfs_create_dir(debugfs_name, शून्य);

	debugfs_create_u16("num_x", S_IRUSR, tsdata->debug_dir, &tsdata->num_x);
	debugfs_create_u16("num_y", S_IRUSR, tsdata->debug_dir, &tsdata->num_y);

	debugfs_create_file("mode", S_IRUSR | S_IWUSR,
			    tsdata->debug_dir, tsdata, &debugfs_mode_fops);
	debugfs_create_file("raw_data", S_IRUSR,
			    tsdata->debug_dir, tsdata, &debugfs_raw_data_fops);
पूर्ण

अटल व्योम edt_ft5x06_ts_tearकरोwn_debugfs(काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
	debugfs_हटाओ_recursive(tsdata->debug_dir);
	kमुक्त(tsdata->raw_buffer);
पूर्ण

#अन्यथा

अटल पूर्णांक edt_ft5x06_factory_mode(काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम edt_ft5x06_ts_prepare_debugfs(काष्ठा edt_ft5x06_ts_data *tsdata,
					  स्थिर अक्षर *debugfs_name)
अणु
पूर्ण

अटल व्योम edt_ft5x06_ts_tearकरोwn_debugfs(काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUGFS */

अटल पूर्णांक edt_ft5x06_ts_identअगरy(काष्ठा i2c_client *client,
					काष्ठा edt_ft5x06_ts_data *tsdata,
					अक्षर *fw_version)
अणु
	u8 rdbuf[EDT_NAME_LEN];
	अक्षर *p;
	पूर्णांक error;
	अक्षर *model_name = tsdata->name;

	/* see what we find अगर we assume it is a M06 *
	 * अगर we get less than EDT_NAME_LEN, we करोn't want
	 * to have garbage in there
	 */
	स_रखो(rdbuf, 0, माप(rdbuf));
	error = edt_ft5x06_ts_पढ़ोग_लिखो(client, 1, "\xBB",
					EDT_NAME_LEN - 1, rdbuf);
	अगर (error)
		वापस error;

	/* Probe content क्रम something consistent.
	 * M06 starts with a response byte, M12 gives the data directly.
	 * M09/Generic करोes not provide model number inक्रमmation.
	 */
	अगर (!strnहालcmp(rdbuf + 1, "EP0", 3)) अणु
		tsdata->version = EDT_M06;

		/* हटाओ last '$' end marker */
		rdbuf[EDT_NAME_LEN - 1] = '\0';
		अगर (rdbuf[EDT_NAME_LEN - 2] == '$')
			rdbuf[EDT_NAME_LEN - 2] = '\0';

		/* look क्रम Model/Version separator */
		p = म_अक्षर(rdbuf, '*');
		अगर (p)
			*p++ = '\0';
		strlcpy(model_name, rdbuf + 1, EDT_NAME_LEN);
		strlcpy(fw_version, p ? p : "", EDT_NAME_LEN);
	पूर्ण अन्यथा अगर (!strnहालcmp(rdbuf, "EP0", 3)) अणु
		tsdata->version = EDT_M12;

		/* हटाओ last '$' end marker */
		rdbuf[EDT_NAME_LEN - 2] = '\0';
		अगर (rdbuf[EDT_NAME_LEN - 3] == '$')
			rdbuf[EDT_NAME_LEN - 3] = '\0';

		/* look क्रम Model/Version separator */
		p = म_अक्षर(rdbuf, '*');
		अगर (p)
			*p++ = '\0';
		strlcpy(model_name, rdbuf, EDT_NAME_LEN);
		strlcpy(fw_version, p ? p : "", EDT_NAME_LEN);
	पूर्ण अन्यथा अणु
		/* If it is not an EDT M06/M12 touchscreen, then the model
		 * detection is a bit hairy. The dअगरferent ft5x06
		 * firmares around करोn't reliably implement the
		 * identअगरication रेजिस्टरs. Well, we'll take a shot.
		 *
		 * The मुख्य dअगरference between generic focaltec based
		 * touches and EDT M09 is that we know how to retrieve
		 * the max coordinates क्रम the latter.
		 */
		tsdata->version = GENERIC_FT;

		error = edt_ft5x06_ts_पढ़ोग_लिखो(client, 1, "\xA6",
						2, rdbuf);
		अगर (error)
			वापस error;

		strlcpy(fw_version, rdbuf, 2);

		error = edt_ft5x06_ts_पढ़ोग_लिखो(client, 1, "\xA8",
						1, rdbuf);
		अगर (error)
			वापस error;

		/* This "model identification" is not exact. Unक्रमtunately
		 * not all firmwares क्रम the ft5x06 put useful values in
		 * the identअगरication रेजिस्टरs.
		 */
		चयन (rdbuf[0]) अणु
		हाल 0x35:   /* EDT EP0350M09 */
		हाल 0x43:   /* EDT EP0430M09 */
		हाल 0x50:   /* EDT EP0500M09 */
		हाल 0x57:   /* EDT EP0570M09 */
		हाल 0x70:   /* EDT EP0700M09 */
			tsdata->version = EDT_M09;
			snम_लिखो(model_name, EDT_NAME_LEN, "EP0%i%i0M09",
				rdbuf[0] >> 4, rdbuf[0] & 0x0F);
			अवरोध;
		हाल 0xa1:   /* EDT EP1010ML00 */
			tsdata->version = EDT_M09;
			snम_लिखो(model_name, EDT_NAME_LEN, "EP%i%i0ML00",
				rdbuf[0] >> 4, rdbuf[0] & 0x0F);
			अवरोध;
		हाल 0x5a:   /* Solomon Goldentek Display */
			snम_लिखो(model_name, EDT_NAME_LEN, "GKTW50SCED1R0");
			अवरोध;
		हाल 0x59:  /* Evervision Display with FT5xx6 TS */
			tsdata->version = EV_FT;
			error = edt_ft5x06_ts_पढ़ोग_लिखो(client, 1, "\x53",
							1, rdbuf);
			अगर (error)
				वापस error;
			strlcpy(fw_version, rdbuf, 1);
			snम_लिखो(model_name, EDT_NAME_LEN,
				 "EVERVISION-FT5726NEi");
			अवरोध;
		शेष:
			snम_लिखो(model_name, EDT_NAME_LEN,
				 "generic ft5x06 (%02x)",
				 rdbuf[0]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम edt_ft5x06_ts_get_शेषs(काष्ठा device *dev,
				       काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
	काष्ठा edt_reg_addr *reg_addr = &tsdata->reg_addr;
	u32 val;
	पूर्णांक error;

	error = device_property_पढ़ो_u32(dev, "threshold", &val);
	अगर (!error) अणु
		edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, reg_addr->reg_threshold, val);
		tsdata->threshold = val;
	पूर्ण

	error = device_property_पढ़ो_u32(dev, "gain", &val);
	अगर (!error) अणु
		edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, reg_addr->reg_gain, val);
		tsdata->gain = val;
	पूर्ण

	error = device_property_पढ़ो_u32(dev, "offset", &val);
	अगर (!error) अणु
		अगर (reg_addr->reg_offset != NO_REGISTER)
			edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata,
						  reg_addr->reg_offset, val);
		tsdata->offset = val;
	पूर्ण

	error = device_property_पढ़ो_u32(dev, "offset-x", &val);
	अगर (!error) अणु
		अगर (reg_addr->reg_offset_x != NO_REGISTER)
			edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata,
						  reg_addr->reg_offset_x, val);
		tsdata->offset_x = val;
	पूर्ण

	error = device_property_पढ़ो_u32(dev, "offset-y", &val);
	अगर (!error) अणु
		अगर (reg_addr->reg_offset_y != NO_REGISTER)
			edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata,
						  reg_addr->reg_offset_y, val);
		tsdata->offset_y = val;
	पूर्ण
पूर्ण

अटल व्योम edt_ft5x06_ts_get_parameters(काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
	काष्ठा edt_reg_addr *reg_addr = &tsdata->reg_addr;

	tsdata->threshold = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata,
						     reg_addr->reg_threshold);
	tsdata->gain = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata, reg_addr->reg_gain);
	अगर (reg_addr->reg_offset != NO_REGISTER)
		tsdata->offset =
			edt_ft5x06_रेजिस्टर_पढ़ो(tsdata, reg_addr->reg_offset);
	अगर (reg_addr->reg_offset_x != NO_REGISTER)
		tsdata->offset_x = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata,
						reg_addr->reg_offset_x);
	अगर (reg_addr->reg_offset_y != NO_REGISTER)
		tsdata->offset_y = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata,
						reg_addr->reg_offset_y);
	अगर (reg_addr->reg_report_rate != NO_REGISTER)
		tsdata->report_rate = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata,
						reg_addr->reg_report_rate);
	tsdata->num_x = EDT_DEFAULT_NUM_X;
	अगर (reg_addr->reg_num_x != NO_REGISTER)
		tsdata->num_x = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata,
							 reg_addr->reg_num_x);
	tsdata->num_y = EDT_DEFAULT_NUM_Y;
	अगर (reg_addr->reg_num_y != NO_REGISTER)
		tsdata->num_y = edt_ft5x06_रेजिस्टर_पढ़ो(tsdata,
							 reg_addr->reg_num_y);
पूर्ण

अटल व्योम edt_ft5x06_ts_set_regs(काष्ठा edt_ft5x06_ts_data *tsdata)
अणु
	काष्ठा edt_reg_addr *reg_addr = &tsdata->reg_addr;

	चयन (tsdata->version) अणु
	हाल EDT_M06:
		reg_addr->reg_threshold = WORK_REGISTER_THRESHOLD;
		reg_addr->reg_report_rate = WORK_REGISTER_REPORT_RATE;
		reg_addr->reg_gain = WORK_REGISTER_GAIN;
		reg_addr->reg_offset = WORK_REGISTER_OFFSET;
		reg_addr->reg_offset_x = NO_REGISTER;
		reg_addr->reg_offset_y = NO_REGISTER;
		reg_addr->reg_num_x = WORK_REGISTER_NUM_X;
		reg_addr->reg_num_y = WORK_REGISTER_NUM_Y;
		अवरोध;

	हाल EDT_M09:
	हाल EDT_M12:
		reg_addr->reg_threshold = M09_REGISTER_THRESHOLD;
		reg_addr->reg_report_rate = NO_REGISTER;
		reg_addr->reg_gain = M09_REGISTER_GAIN;
		reg_addr->reg_offset = M09_REGISTER_OFFSET;
		reg_addr->reg_offset_x = NO_REGISTER;
		reg_addr->reg_offset_y = NO_REGISTER;
		reg_addr->reg_num_x = M09_REGISTER_NUM_X;
		reg_addr->reg_num_y = M09_REGISTER_NUM_Y;
		अवरोध;

	हाल EV_FT:
		reg_addr->reg_threshold = EV_REGISTER_THRESHOLD;
		reg_addr->reg_report_rate = NO_REGISTER;
		reg_addr->reg_gain = EV_REGISTER_GAIN;
		reg_addr->reg_offset = NO_REGISTER;
		reg_addr->reg_offset_x = EV_REGISTER_OFFSET_X;
		reg_addr->reg_offset_y = EV_REGISTER_OFFSET_Y;
		reg_addr->reg_num_x = NO_REGISTER;
		reg_addr->reg_num_y = NO_REGISTER;
		अवरोध;

	हाल GENERIC_FT:
		/* this is a guesswork */
		reg_addr->reg_threshold = M09_REGISTER_THRESHOLD;
		reg_addr->reg_report_rate = NO_REGISTER;
		reg_addr->reg_gain = M09_REGISTER_GAIN;
		reg_addr->reg_offset = M09_REGISTER_OFFSET;
		reg_addr->reg_offset_x = NO_REGISTER;
		reg_addr->reg_offset_y = NO_REGISTER;
		reg_addr->reg_num_x = NO_REGISTER;
		reg_addr->reg_num_y = NO_REGISTER;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम edt_ft5x06_disable_regulator(व्योम *arg)
अणु
	काष्ठा edt_ft5x06_ts_data *data = arg;

	regulator_disable(data->vcc);
पूर्ण

अटल पूर्णांक edt_ft5x06_ts_probe(काष्ठा i2c_client *client,
					 स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा edt_i2c_chip_data *chip_data;
	काष्ठा edt_ft5x06_ts_data *tsdata;
	u8 buf[2] = अणु 0xfc, 0x00 पूर्ण;
	काष्ठा input_dev *input;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक error;
	अक्षर fw_version[EDT_NAME_LEN];

	dev_dbg(&client->dev, "probing for EDT FT5x06 I2C\n");

	tsdata = devm_kzalloc(&client->dev, माप(*tsdata), GFP_KERNEL);
	अगर (!tsdata) अणु
		dev_err(&client->dev, "failed to allocate driver data.\n");
		वापस -ENOMEM;
	पूर्ण

	chip_data = device_get_match_data(&client->dev);
	अगर (!chip_data)
		chip_data = (स्थिर काष्ठा edt_i2c_chip_data *)id->driver_data;
	अगर (!chip_data || !chip_data->max_support_poपूर्णांकs) अणु
		dev_err(&client->dev, "invalid or missing chip data\n");
		वापस -EINVAL;
	पूर्ण

	tsdata->max_support_poपूर्णांकs = chip_data->max_support_poपूर्णांकs;

	tsdata->vcc = devm_regulator_get(&client->dev, "vcc");
	अगर (IS_ERR(tsdata->vcc)) अणु
		error = PTR_ERR(tsdata->vcc);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"failed to request regulator: %d\n", error);
		वापस error;
	पूर्ण

	error = regulator_enable(tsdata->vcc);
	अगर (error < 0) अणु
		dev_err(&client->dev, "failed to enable vcc: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev,
					 edt_ft5x06_disable_regulator,
					 tsdata);
	अगर (error)
		वापस error;

	tsdata->reset_gpio = devm_gpiod_get_optional(&client->dev,
						     "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tsdata->reset_gpio)) अणु
		error = PTR_ERR(tsdata->reset_gpio);
		dev_err(&client->dev,
			"Failed to request GPIO reset pin, error %d\n", error);
		वापस error;
	पूर्ण

	tsdata->wake_gpio = devm_gpiod_get_optional(&client->dev,
						    "wake", GPIOD_OUT_LOW);
	अगर (IS_ERR(tsdata->wake_gpio)) अणु
		error = PTR_ERR(tsdata->wake_gpio);
		dev_err(&client->dev,
			"Failed to request GPIO wake pin, error %d\n", error);
		वापस error;
	पूर्ण

	/*
	 * Check which sleep modes we can support. Power-off requieres the
	 * reset-pin to ensure correct घातer-करोwn/घातer-up behaviour. Start with
	 * the EDT_PMODE_POWEROFF test since this is the deepest possible sleep
	 * mode.
	 */
	अगर (tsdata->reset_gpio)
		tsdata->suspend_mode = EDT_PMODE_POWEROFF;
	अन्यथा अगर (tsdata->wake_gpio)
		tsdata->suspend_mode = EDT_PMODE_HIBERNATE;
	अन्यथा
		tsdata->suspend_mode = EDT_PMODE_NOT_SUPPORTED;

	अगर (tsdata->wake_gpio) अणु
		usleep_range(5000, 6000);
		gpiod_set_value_cansleep(tsdata->wake_gpio, 1);
	पूर्ण

	अगर (tsdata->reset_gpio) अणु
		usleep_range(5000, 6000);
		gpiod_set_value_cansleep(tsdata->reset_gpio, 0);
		msleep(300);
	पूर्ण

	input = devm_input_allocate_device(&client->dev);
	अगर (!input) अणु
		dev_err(&client->dev, "failed to allocate input device.\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&tsdata->mutex);
	tsdata->client = client;
	tsdata->input = input;
	tsdata->factory_mode = false;

	error = edt_ft5x06_ts_identअगरy(client, tsdata, fw_version);
	अगर (error) अणु
		dev_err(&client->dev, "touchscreen probe failed\n");
		वापस error;
	पूर्ण

	/*
	 * Dummy पढ़ो access. EP0700MLP1 वापसs bogus data on the first
	 * रेजिस्टर पढ़ो access and ignores ग_लिखोs.
	 */
	edt_ft5x06_ts_पढ़ोग_लिखो(tsdata->client, 2, buf, 2, buf);

	edt_ft5x06_ts_set_regs(tsdata);
	edt_ft5x06_ts_get_शेषs(&client->dev, tsdata);
	edt_ft5x06_ts_get_parameters(tsdata);

	dev_dbg(&client->dev,
		"Model \"%s\", Rev. \"%s\", %dx%d sensors\n",
		tsdata->name, fw_version, tsdata->num_x, tsdata->num_y);

	input->name = tsdata->name;
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;

	input_set_असल_params(input, ABS_MT_POSITION_X,
			     0, tsdata->num_x * 64 - 1, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y,
			     0, tsdata->num_y * 64 - 1, 0, 0);

	touchscreen_parse_properties(input, true, &tsdata->prop);

	error = input_mt_init_slots(input, tsdata->max_support_poपूर्णांकs,
				INPUT_MT_सूचीECT);
	अगर (error) अणु
		dev_err(&client->dev, "Unable to init MT slots.\n");
		वापस error;
	पूर्ण

	i2c_set_clientdata(client, tsdata);

	irq_flags = irq_get_trigger_type(client->irq);
	अगर (irq_flags == IRQF_TRIGGER_NONE)
		irq_flags = IRQF_TRIGGER_FALLING;
	irq_flags |= IRQF_ONESHOT;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, edt_ft5x06_ts_isr, irq_flags,
					client->name, tsdata);
	अगर (error) अणु
		dev_err(&client->dev, "Unable to request touchscreen IRQ.\n");
		वापस error;
	पूर्ण

	error = devm_device_add_group(&client->dev, &edt_ft5x06_attr_group);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	edt_ft5x06_ts_prepare_debugfs(tsdata, dev_driver_string(&client->dev));

	dev_dbg(&client->dev,
		"EDT FT5x06 initialized: IRQ %d, WAKE pin %d, Reset pin %d.\n",
		client->irq,
		tsdata->wake_gpio ? desc_to_gpio(tsdata->wake_gpio) : -1,
		tsdata->reset_gpio ? desc_to_gpio(tsdata->reset_gpio) : -1);

	वापस 0;
पूर्ण

अटल पूर्णांक edt_ft5x06_ts_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा edt_ft5x06_ts_data *tsdata = i2c_get_clientdata(client);

	edt_ft5x06_ts_tearकरोwn_debugfs(tsdata);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused edt_ft5x06_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा edt_ft5x06_ts_data *tsdata = i2c_get_clientdata(client);
	काष्ठा gpio_desc *reset_gpio = tsdata->reset_gpio;
	पूर्णांक ret;

	अगर (device_may_wakeup(dev))
		वापस 0;

	अगर (tsdata->suspend_mode == EDT_PMODE_NOT_SUPPORTED)
		वापस 0;

	/* Enter hibernate mode. */
	ret = edt_ft5x06_रेजिस्टर_ग_लिखो(tsdata, PMOD_REGISTER_OPMODE,
					PMOD_REGISTER_HIBERNATE);
	अगर (ret)
		dev_warn(dev, "Failed to set hibernate mode\n");

	अगर (tsdata->suspend_mode == EDT_PMODE_HIBERNATE)
		वापस 0;

	/*
	 * Power-off according the datasheet. Cut the घातer may leaf the irq
	 * line in an undefined state depending on the host pull resistor
	 * settings. Disable the irq to aव्योम adjusting each host till the
	 * device is back in a full functional state.
	 */
	disable_irq(tsdata->client->irq);

	gpiod_set_value_cansleep(reset_gpio, 1);
	usleep_range(1000, 2000);

	ret = regulator_disable(tsdata->vcc);
	अगर (ret)
		dev_warn(dev, "Failed to disable vcc\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused edt_ft5x06_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा edt_ft5x06_ts_data *tsdata = i2c_get_clientdata(client);
	पूर्णांक ret = 0;

	अगर (device_may_wakeup(dev))
		वापस 0;

	अगर (tsdata->suspend_mode == EDT_PMODE_NOT_SUPPORTED)
		वापस 0;

	अगर (tsdata->suspend_mode == EDT_PMODE_POWEROFF) अणु
		काष्ठा gpio_desc *reset_gpio = tsdata->reset_gpio;

		/*
		 * We can't check अगर the regulator is a dummy or a real
		 * regulator. So we need to specअगरy the 5ms reset समय (T_rst)
		 * here instead of the 100us T_rtp समय. We also need to रुको
		 * 300ms in हाल it was a real supply and the घातer was cutted
		 * of. Toggle the reset pin is also a way to निकास the hibernate
		 * mode.
		 */
		gpiod_set_value_cansleep(reset_gpio, 1);
		usleep_range(5000, 6000);

		ret = regulator_enable(tsdata->vcc);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable vcc\n");
			वापस ret;
		पूर्ण

		usleep_range(1000, 2000);
		gpiod_set_value_cansleep(reset_gpio, 0);
		msleep(300);

		edt_ft5x06_restore_reg_parameters(tsdata);
		enable_irq(tsdata->client->irq);

		अगर (tsdata->factory_mode)
			ret = edt_ft5x06_factory_mode(tsdata);
	पूर्ण अन्यथा अणु
		काष्ठा gpio_desc *wake_gpio = tsdata->wake_gpio;

		gpiod_set_value_cansleep(wake_gpio, 0);
		usleep_range(5000, 6000);
		gpiod_set_value_cansleep(wake_gpio, 1);
	पूर्ण


	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(edt_ft5x06_ts_pm_ops,
			 edt_ft5x06_ts_suspend, edt_ft5x06_ts_resume);

अटल स्थिर काष्ठा edt_i2c_chip_data edt_ft5x06_data = अणु
	.max_support_poपूर्णांकs = 5,
पूर्ण;

अटल स्थिर काष्ठा edt_i2c_chip_data edt_ft5506_data = अणु
	.max_support_poपूर्णांकs = 10,
पूर्ण;

अटल स्थिर काष्ठा edt_i2c_chip_data edt_ft6236_data = अणु
	.max_support_poपूर्णांकs = 2,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id edt_ft5x06_ts_id[] = अणु
	अणु .name = "edt-ft5x06", .driver_data = (दीर्घ)&edt_ft5x06_data पूर्ण,
	अणु .name = "edt-ft5506", .driver_data = (दीर्घ)&edt_ft5506_data पूर्ण,
	अणु .name = "ev-ft5726", .driver_data = (दीर्घ)&edt_ft5506_data पूर्ण,
	/* Note no edt- prefix क्रम compatibility with the ft6236.c driver */
	अणु .name = "ft6236", .driver_data = (दीर्घ)&edt_ft6236_data पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, edt_ft5x06_ts_id);

अटल स्थिर काष्ठा of_device_id edt_ft5x06_of_match[] = अणु
	अणु .compatible = "edt,edt-ft5206", .data = &edt_ft5x06_data पूर्ण,
	अणु .compatible = "edt,edt-ft5306", .data = &edt_ft5x06_data पूर्ण,
	अणु .compatible = "edt,edt-ft5406", .data = &edt_ft5x06_data पूर्ण,
	अणु .compatible = "edt,edt-ft5506", .data = &edt_ft5506_data पूर्ण,
	अणु .compatible = "evervision,ev-ft5726", .data = &edt_ft5506_data पूर्ण,
	/* Note focaltech venकरोr prefix क्रम compatibility with ft6236.c */
	अणु .compatible = "focaltech,ft6236", .data = &edt_ft6236_data पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, edt_ft5x06_of_match);

अटल काष्ठा i2c_driver edt_ft5x06_ts_driver = अणु
	.driver = अणु
		.name = "edt_ft5x06",
		.of_match_table = edt_ft5x06_of_match,
		.pm = &edt_ft5x06_ts_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.id_table = edt_ft5x06_ts_id,
	.probe    = edt_ft5x06_ts_probe,
	.हटाओ   = edt_ft5x06_ts_हटाओ,
पूर्ण;

module_i2c_driver(edt_ft5x06_ts_driver);

MODULE_AUTHOR("Simon Budig <simon.budig@kernelconcepts.de>");
MODULE_DESCRIPTION("EDT FT5x06 I2C Touchscreen Driver");
MODULE_LICENSE("GPL v2");

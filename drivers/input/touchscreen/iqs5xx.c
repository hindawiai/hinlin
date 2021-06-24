<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Azoteq IQS550/572/525 Trackpad/Touchscreen Controller
 *
 * Copyright (C) 2018 Jeff LaBundy <jeff@labundy.com>
 *
 * These devices require firmware exported from a PC-based configuration tool
 * made available by the venकरोr. Firmware files may be pushed to the device's
 * nonअस्थिर memory by writing the filename to the 'fw_file' sysfs control.
 *
 * Link to PC-based configuration tool and datasheet: https://www.azoteq.com/
 */

#समावेश <linux/bits.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा IQS5XX_FW_खाता_LEN	64
#घोषणा IQS5XX_NUM_RETRIES	10
#घोषणा IQS5XX_NUM_CONTACTS	5
#घोषणा IQS5XX_WR_BYTES_MAX	2

#घोषणा IQS5XX_PROD_NUM_IQS550	40
#घोषणा IQS5XX_PROD_NUM_IQS572	58
#घोषणा IQS5XX_PROD_NUM_IQS525	52

#घोषणा IQS5XX_SHOW_RESET	BIT(7)
#घोषणा IQS5XX_ACK_RESET	BIT(7)

#घोषणा IQS5XX_SUSPEND		BIT(0)
#घोषणा IQS5XX_RESUME		0

#घोषणा IQS5XX_SETUP_COMPLETE	BIT(6)
#घोषणा IQS5XX_WDT		BIT(5)
#घोषणा IQS5XX_ALP_REATI	BIT(3)
#घोषणा IQS5XX_REATI		BIT(2)

#घोषणा IQS5XX_TP_EVENT		BIT(2)
#घोषणा IQS5XX_EVENT_MODE	BIT(0)

#घोषणा IQS5XX_PROD_NUM		0x0000
#घोषणा IQS5XX_SYS_INFO0	0x000F
#घोषणा IQS5XX_SYS_INFO1	0x0010
#घोषणा IQS5XX_SYS_CTRL0	0x0431
#घोषणा IQS5XX_SYS_CTRL1	0x0432
#घोषणा IQS5XX_SYS_CFG0		0x058E
#घोषणा IQS5XX_SYS_CFG1		0x058F
#घोषणा IQS5XX_X_RES		0x066E
#घोषणा IQS5XX_Y_RES		0x0670
#घोषणा IQS5XX_EXP_खाता		0x0677
#घोषणा IQS5XX_CHKSM		0x83C0
#घोषणा IQS5XX_APP		0x8400
#घोषणा IQS5XX_CSTM		0xBE00
#घोषणा IQS5XX_PMAP_END		0xBFFF
#घोषणा IQS5XX_END_COMM		0xEEEE

#घोषणा IQS5XX_CHKSM_LEN	(IQS5XX_APP - IQS5XX_CHKSM)
#घोषणा IQS5XX_APP_LEN		(IQS5XX_CSTM - IQS5XX_APP)
#घोषणा IQS5XX_CSTM_LEN		(IQS5XX_PMAP_END + 1 - IQS5XX_CSTM)
#घोषणा IQS5XX_PMAP_LEN		(IQS5XX_PMAP_END + 1 - IQS5XX_CHKSM)

#घोषणा IQS5XX_REC_HDR_LEN	4
#घोषणा IQS5XX_REC_LEN_MAX	255
#घोषणा IQS5XX_REC_TYPE_DATA	0x00
#घोषणा IQS5XX_REC_TYPE_खातापूर्ण	0x01

#घोषणा IQS5XX_BL_ADDR_MASK	0x40
#घोषणा IQS5XX_BL_CMD_VER	0x00
#घोषणा IQS5XX_BL_CMD_READ	0x01
#घोषणा IQS5XX_BL_CMD_EXEC	0x02
#घोषणा IQS5XX_BL_CMD_CRC	0x03
#घोषणा IQS5XX_BL_BLK_LEN_MAX	64
#घोषणा IQS5XX_BL_ID		0x0200
#घोषणा IQS5XX_BL_STATUS_NONE	0xEE
#घोषणा IQS5XX_BL_CRC_PASS	0x00
#घोषणा IQS5XX_BL_CRC_FAIL	0x01
#घोषणा IQS5XX_BL_ATTEMPTS	3

काष्ठा iqs5xx_dev_id_info अणु
	__be16 prod_num;
	__be16 proj_num;
	u8 major_ver;
	u8 minor_ver;
	u8 bl_status;
पूर्ण __packed;

काष्ठा iqs5xx_ihex_rec अणु
	अक्षर start;
	अक्षर len[2];
	अक्षर addr[4];
	अक्षर type[2];
	अक्षर data[2];
पूर्ण __packed;

काष्ठा iqs5xx_touch_data अणु
	__be16 असल_x;
	__be16 असल_y;
	__be16 strength;
	u8 area;
पूर्ण __packed;

काष्ठा iqs5xx_status अणु
	u8 sys_info[2];
	u8 num_active;
	__be16 rel_x;
	__be16 rel_y;
	काष्ठा iqs5xx_touch_data touch_data[IQS5XX_NUM_CONTACTS];
पूर्ण __packed;

काष्ठा iqs5xx_निजी अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा touchscreen_properties prop;
	काष्ठा mutex lock;
	काष्ठा iqs5xx_dev_id_info dev_id_info;
	u8 exp_file[2];
पूर्ण;

अटल पूर्णांक iqs5xx_पढ़ो_burst(काष्ठा i2c_client *client,
			     u16 reg, व्योम *val, u16 len)
अणु
	__be16 reg_buf = cpu_to_be16(reg);
	पूर्णांक ret, i;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = माप(reg_buf),
			.buf = (u8 *)&reg_buf,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = (u8 *)val,
		पूर्ण,
	पूर्ण;

	/*
	 * The first addressing attempt outside of a communication winकरोw fails
	 * and must be retried, after which the device घड़ी stretches until it
	 * is available.
	 */
	क्रम (i = 0; i < IQS5XX_NUM_RETRIES; i++) अणु
		ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
		अगर (ret == ARRAY_SIZE(msg))
			वापस 0;

		usleep_range(200, 300);
	पूर्ण

	अगर (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "Failed to read from address 0x%04X: %d\n",
		reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs5xx_पढ़ो_word(काष्ठा i2c_client *client, u16 reg, u16 *val)
अणु
	__be16 val_buf;
	पूर्णांक error;

	error = iqs5xx_पढ़ो_burst(client, reg, &val_buf, माप(val_buf));
	अगर (error)
		वापस error;

	*val = be16_to_cpu(val_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक iqs5xx_ग_लिखो_burst(काष्ठा i2c_client *client,
			      u16 reg, स्थिर व्योम *val, u16 len)
अणु
	पूर्णांक ret, i;
	u16 mlen = माप(reg) + len;
	u8 mbuf[माप(reg) + IQS5XX_WR_BYTES_MAX];

	अगर (len > IQS5XX_WR_BYTES_MAX)
		वापस -EINVAL;

	put_unaligned_be16(reg, mbuf);
	स_नकल(mbuf + माप(reg), val, len);

	/*
	 * The first addressing attempt outside of a communication winकरोw fails
	 * and must be retried, after which the device घड़ी stretches until it
	 * is available.
	 */
	क्रम (i = 0; i < IQS5XX_NUM_RETRIES; i++) अणु
		ret = i2c_master_send(client, mbuf, mlen);
		अगर (ret == mlen)
			वापस 0;

		usleep_range(200, 300);
	पूर्ण

	अगर (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "Failed to write to address 0x%04X: %d\n",
		reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs5xx_ग_लिखो_word(काष्ठा i2c_client *client, u16 reg, u16 val)
अणु
	__be16 val_buf = cpu_to_be16(val);

	वापस iqs5xx_ग_लिखो_burst(client, reg, &val_buf, माप(val_buf));
पूर्ण

अटल पूर्णांक iqs5xx_ग_लिखो_byte(काष्ठा i2c_client *client, u16 reg, u8 val)
अणु
	वापस iqs5xx_ग_लिखो_burst(client, reg, &val, माप(val));
पूर्ण

अटल व्योम iqs5xx_reset(काष्ठा i2c_client *client)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = i2c_get_clientdata(client);

	gpiod_set_value_cansleep(iqs5xx->reset_gpio, 1);
	usleep_range(200, 300);

	gpiod_set_value_cansleep(iqs5xx->reset_gpio, 0);
पूर्ण

अटल पूर्णांक iqs5xx_bl_cmd(काष्ठा i2c_client *client, u8 bl_cmd, u16 bl_addr)
अणु
	काष्ठा i2c_msg msg;
	पूर्णांक ret;
	u8 mbuf[माप(bl_cmd) + माप(bl_addr)];

	msg.addr = client->addr ^ IQS5XX_BL_ADDR_MASK;
	msg.flags = 0;
	msg.len = माप(bl_cmd);
	msg.buf = mbuf;

	*mbuf = bl_cmd;

	चयन (bl_cmd) अणु
	हाल IQS5XX_BL_CMD_VER:
	हाल IQS5XX_BL_CMD_CRC:
	हाल IQS5XX_BL_CMD_EXEC:
		अवरोध;
	हाल IQS5XX_BL_CMD_READ:
		msg.len += माप(bl_addr);
		put_unaligned_be16(bl_addr, mbuf + माप(bl_cmd));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1)
		जाओ msg_fail;

	चयन (bl_cmd) अणु
	हाल IQS5XX_BL_CMD_VER:
		msg.len = माप(u16);
		अवरोध;
	हाल IQS5XX_BL_CMD_CRC:
		msg.len = माप(u8);
		/*
		 * This delay saves the bus controller the trouble of having to
		 * tolerate a relatively दीर्घ घड़ी-stretching period जबतक the
		 * CRC is calculated.
		 */
		msleep(50);
		अवरोध;
	हाल IQS5XX_BL_CMD_EXEC:
		usleep_range(10000, 10100);
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण

	msg.flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1)
		जाओ msg_fail;

	अगर (bl_cmd == IQS5XX_BL_CMD_VER &&
	    get_unaligned_be16(mbuf) != IQS5XX_BL_ID) अणु
		dev_err(&client->dev, "Unrecognized bootloader ID: 0x%04X\n",
			get_unaligned_be16(mbuf));
		वापस -EINVAL;
	पूर्ण

	अगर (bl_cmd == IQS5XX_BL_CMD_CRC && *mbuf != IQS5XX_BL_CRC_PASS) अणु
		dev_err(&client->dev, "Bootloader CRC failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;

msg_fail:
	अगर (ret >= 0)
		ret = -EIO;

	अगर (bl_cmd != IQS5XX_BL_CMD_VER)
		dev_err(&client->dev,
			"Unsuccessful bootloader command 0x%02X: %d\n",
			bl_cmd, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs5xx_bl_खोलो(काष्ठा i2c_client *client)
अणु
	पूर्णांक error, i, j;

	/*
	 * The device खोलोs a bootloader polling winकरोw क्रम 2 ms following the
	 * release of reset. If the host cannot establish communication during
	 * this समय frame, it must cycle reset again.
	 */
	क्रम (i = 0; i < IQS5XX_BL_ATTEMPTS; i++) अणु
		iqs5xx_reset(client);
		usleep_range(350, 400);

		क्रम (j = 0; j < IQS5XX_NUM_RETRIES; j++) अणु
			error = iqs5xx_bl_cmd(client, IQS5XX_BL_CMD_VER, 0);
			अगर (!error)
				usleep_range(10000, 10100);
			अन्यथा अगर (error != -EINVAL)
				जारी;

			वापस error;
		पूर्ण
	पूर्ण

	dev_err(&client->dev, "Failed to open bootloader: %d\n", error);

	वापस error;
पूर्ण

अटल पूर्णांक iqs5xx_bl_ग_लिखो(काष्ठा i2c_client *client,
			   u16 bl_addr, u8 *pmap_data, u16 pmap_len)
अणु
	काष्ठा i2c_msg msg;
	पूर्णांक ret, i;
	u8 mbuf[माप(bl_addr) + IQS5XX_BL_BLK_LEN_MAX];

	अगर (pmap_len % IQS5XX_BL_BLK_LEN_MAX)
		वापस -EINVAL;

	msg.addr = client->addr ^ IQS5XX_BL_ADDR_MASK;
	msg.flags = 0;
	msg.len = माप(mbuf);
	msg.buf = mbuf;

	क्रम (i = 0; i < pmap_len; i += IQS5XX_BL_BLK_LEN_MAX) अणु
		put_unaligned_be16(bl_addr + i, mbuf);
		स_नकल(mbuf + माप(bl_addr), pmap_data + i,
		       माप(mbuf) - माप(bl_addr));

		ret = i2c_transfer(client->adapter, &msg, 1);
		अगर (ret != 1)
			जाओ msg_fail;

		usleep_range(10000, 10100);
	पूर्ण

	वापस 0;

msg_fail:
	अगर (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "Failed to write block at address 0x%04X: %d\n",
		bl_addr + i, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs5xx_bl_verअगरy(काष्ठा i2c_client *client,
			    u16 bl_addr, u8 *pmap_data, u16 pmap_len)
अणु
	काष्ठा i2c_msg msg;
	पूर्णांक ret, i;
	u8 bl_data[IQS5XX_BL_BLK_LEN_MAX];

	अगर (pmap_len % IQS5XX_BL_BLK_LEN_MAX)
		वापस -EINVAL;

	msg.addr = client->addr ^ IQS5XX_BL_ADDR_MASK;
	msg.flags = I2C_M_RD;
	msg.len = माप(bl_data);
	msg.buf = bl_data;

	क्रम (i = 0; i < pmap_len; i += IQS5XX_BL_BLK_LEN_MAX) अणु
		ret = iqs5xx_bl_cmd(client, IQS5XX_BL_CMD_READ, bl_addr + i);
		अगर (ret)
			वापस ret;

		ret = i2c_transfer(client->adapter, &msg, 1);
		अगर (ret != 1)
			जाओ msg_fail;

		अगर (स_भेद(bl_data, pmap_data + i, माप(bl_data))) अणु
			dev_err(&client->dev,
				"Failed to verify block at address 0x%04X\n",
				bl_addr + i);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;

msg_fail:
	अगर (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "Failed to read block at address 0x%04X: %d\n",
		bl_addr + i, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs5xx_set_state(काष्ठा i2c_client *client, u8 state)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = i2c_get_clientdata(client);
	पूर्णांक error1, error2;

	अगर (!iqs5xx->dev_id_info.bl_status)
		वापस 0;

	mutex_lock(&iqs5xx->lock);

	/*
	 * Addressing the device outside of a communication winकरोw prompts it
	 * to निश्चित the RDY output, so disable the पूर्णांकerrupt line to prevent
	 * the handler from servicing a false पूर्णांकerrupt.
	 */
	disable_irq(client->irq);

	error1 = iqs5xx_ग_लिखो_byte(client, IQS5XX_SYS_CTRL1, state);
	error2 = iqs5xx_ग_लिखो_byte(client, IQS5XX_END_COMM, 0);

	usleep_range(50, 100);
	enable_irq(client->irq);

	mutex_unlock(&iqs5xx->lock);

	अगर (error1)
		वापस error1;

	वापस error2;
पूर्ण

अटल पूर्णांक iqs5xx_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = input_get_drvdata(input);

	वापस iqs5xx_set_state(iqs5xx->client, IQS5XX_RESUME);
पूर्ण

अटल व्योम iqs5xx_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = input_get_drvdata(input);

	iqs5xx_set_state(iqs5xx->client, IQS5XX_SUSPEND);
पूर्ण

अटल पूर्णांक iqs5xx_axis_init(काष्ठा i2c_client *client)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = i2c_get_clientdata(client);
	काष्ठा touchscreen_properties *prop = &iqs5xx->prop;
	काष्ठा input_dev *input;
	u16 max_x, max_y;
	पूर्णांक error;

	अगर (!iqs5xx->input) अणु
		input = devm_input_allocate_device(&client->dev);
		अगर (!input)
			वापस -ENOMEM;

		input->name = client->name;
		input->id.bustype = BUS_I2C;
		input->खोलो = iqs5xx_खोलो;
		input->बंद = iqs5xx_बंद;

		input_set_drvdata(input, iqs5xx);
		iqs5xx->input = input;
	पूर्ण

	error = iqs5xx_पढ़ो_word(client, IQS5XX_X_RES, &max_x);
	अगर (error)
		वापस error;

	error = iqs5xx_पढ़ो_word(client, IQS5XX_Y_RES, &max_y);
	अगर (error)
		वापस error;

	input_set_असल_params(iqs5xx->input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_असल_params(iqs5xx->input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	input_set_असल_params(iqs5xx->input, ABS_MT_PRESSURE, 0, U16_MAX, 0, 0);

	touchscreen_parse_properties(iqs5xx->input, true, prop);

	/*
	 * The device reserves 0xFFFF क्रम coordinates that correspond to slots
	 * which are not in a state of touch.
	 */
	अगर (prop->max_x >= U16_MAX || prop->max_y >= U16_MAX) अणु
		dev_err(&client->dev, "Invalid touchscreen size: %u*%u\n",
			prop->max_x, prop->max_y);
		वापस -EINVAL;
	पूर्ण

	अगर (prop->max_x != max_x) अणु
		error = iqs5xx_ग_लिखो_word(client, IQS5XX_X_RES, prop->max_x);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (prop->max_y != max_y) अणु
		error = iqs5xx_ग_लिखो_word(client, IQS5XX_Y_RES, prop->max_y);
		अगर (error)
			वापस error;
	पूर्ण

	error = input_mt_init_slots(iqs5xx->input, IQS5XX_NUM_CONTACTS,
				    INPUT_MT_सूचीECT);
	अगर (error)
		dev_err(&client->dev, "Failed to initialize slots: %d\n",
			error);

	वापस error;
पूर्ण

अटल पूर्णांक iqs5xx_dev_init(काष्ठा i2c_client *client)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = i2c_get_clientdata(client);
	काष्ठा iqs5xx_dev_id_info *dev_id_info;
	पूर्णांक error;
	u8 buf[माप(*dev_id_info) + 1];

	error = iqs5xx_पढ़ो_burst(client, IQS5XX_PROD_NUM,
				  &buf[1], माप(*dev_id_info));
	अगर (error)
		वापस iqs5xx_bl_खोलो(client);

	/*
	 * A000 and B000 devices use 8-bit and 16-bit addressing, respectively.
	 * Querying an A000 device's version inक्रमmation with 16-bit addressing
	 * gives the appearance that the data is shअगरted by one byte; a nonzero
	 * leading array element suggests this could be the हाल (in which हाल
	 * the missing zero is prepended).
	 */
	buf[0] = 0;
	dev_id_info = (काष्ठा iqs5xx_dev_id_info *)&buf[buf[1] ? 0 : 1];

	चयन (be16_to_cpu(dev_id_info->prod_num)) अणु
	हाल IQS5XX_PROD_NUM_IQS550:
	हाल IQS5XX_PROD_NUM_IQS572:
	हाल IQS5XX_PROD_NUM_IQS525:
		अवरोध;
	शेष:
		dev_err(&client->dev, "Unrecognized product number: %u\n",
			be16_to_cpu(dev_id_info->prod_num));
		वापस -EINVAL;
	पूर्ण

	/*
	 * With the product number recognized yet shअगरted by one byte, खोलो the
	 * bootloader and रुको क्रम user space to convert the A000 device पूर्णांकo a
	 * B000 device via new firmware.
	 */
	अगर (buf[1]) अणु
		dev_err(&client->dev, "Opening bootloader for A000 device\n");
		वापस iqs5xx_bl_खोलो(client);
	पूर्ण

	error = iqs5xx_पढ़ो_burst(client, IQS5XX_EXP_खाता,
				  iqs5xx->exp_file, माप(iqs5xx->exp_file));
	अगर (error)
		वापस error;

	error = iqs5xx_axis_init(client);
	अगर (error)
		वापस error;

	error = iqs5xx_ग_लिखो_byte(client, IQS5XX_SYS_CTRL0, IQS5XX_ACK_RESET);
	अगर (error)
		वापस error;

	error = iqs5xx_ग_लिखो_byte(client, IQS5XX_SYS_CFG0,
				  IQS5XX_SETUP_COMPLETE | IQS5XX_WDT |
				  IQS5XX_ALP_REATI | IQS5XX_REATI);
	अगर (error)
		वापस error;

	error = iqs5xx_ग_लिखो_byte(client, IQS5XX_SYS_CFG1,
				  IQS5XX_TP_EVENT | IQS5XX_EVENT_MODE);
	अगर (error)
		वापस error;

	error = iqs5xx_ग_लिखो_byte(client, IQS5XX_END_COMM, 0);
	अगर (error)
		वापस error;

	iqs5xx->dev_id_info = *dev_id_info;

	/*
	 * The following delay allows ATI to complete beक्रमe the खोलो and बंद
	 * callbacks are मुक्त to elicit I2C communication. Any attempts to पढ़ो
	 * from or ग_लिखो to the device during this समय may face extended घड़ी
	 * stretching and prompt the I2C controller to report an error.
	 */
	msleep(250);

	वापस 0;
पूर्ण

अटल irqवापस_t iqs5xx_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = data;
	काष्ठा iqs5xx_status status;
	काष्ठा i2c_client *client = iqs5xx->client;
	काष्ठा input_dev *input = iqs5xx->input;
	पूर्णांक error, i;

	/*
	 * This check is purely a precaution, as the device करोes not निश्चित the
	 * RDY output during bootloader mode. If the device operates outside of
	 * bootloader mode, the input device is guaranteed to be allocated.
	 */
	अगर (!iqs5xx->dev_id_info.bl_status)
		वापस IRQ_NONE;

	error = iqs5xx_पढ़ो_burst(client, IQS5XX_SYS_INFO0,
				  &status, माप(status));
	अगर (error)
		वापस IRQ_NONE;

	अगर (status.sys_info[0] & IQS5XX_SHOW_RESET) अणु
		dev_err(&client->dev, "Unexpected device reset\n");

		error = iqs5xx_dev_init(client);
		अगर (error) अणु
			dev_err(&client->dev,
				"Failed to re-initialize device: %d\n", error);
			वापस IRQ_NONE;
		पूर्ण

		वापस IRQ_HANDLED;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(status.touch_data); i++) अणु
		काष्ठा iqs5xx_touch_data *touch_data = &status.touch_data[i];
		u16 pressure = be16_to_cpu(touch_data->strength);

		input_mt_slot(input, i);
		अगर (input_mt_report_slot_state(input, MT_TOOL_FINGER,
					       pressure != 0)) अणु
			touchscreen_report_pos(iqs5xx->input, &iqs5xx->prop,
					       be16_to_cpu(touch_data->असल_x),
					       be16_to_cpu(touch_data->असल_y),
					       true);
			input_report_असल(input, ABS_MT_PRESSURE, pressure);
		पूर्ण
	पूर्ण

	input_mt_sync_frame(input);
	input_sync(input);

	error = iqs5xx_ग_लिखो_byte(client, IQS5XX_END_COMM, 0);
	अगर (error)
		वापस IRQ_NONE;

	/*
	 * Once the communication winकरोw is बंदd, a small delay is added to
	 * ensure the device's RDY output has been deनिश्चितed by the समय the
	 * पूर्णांकerrupt handler वापसs.
	 */
	usleep_range(50, 100);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक iqs5xx_fw_file_parse(काष्ठा i2c_client *client,
				स्थिर अक्षर *fw_file, u8 *pmap)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा iqs5xx_ihex_rec *rec;
	माप_प्रकार pos = 0;
	पूर्णांक error, i;
	u16 rec_num = 1;
	u16 rec_addr;
	u8 rec_len, rec_type, rec_chksm, chksm;
	u8 rec_hdr[IQS5XX_REC_HDR_LEN];
	u8 rec_data[IQS5XX_REC_LEN_MAX];

	/*
	 * Firmware exported from the venकरोr's configuration tool deviates from
	 * standard ihex as follows: (1) the checksum क्रम records corresponding
	 * to user-exported settings is not recalculated, and (2) an address of
	 * 0xFFFF is used क्रम the खातापूर्ण record.
	 *
	 * Because the ihex2fw tool tolerates neither (1) nor (2), the slightly
	 * nonstandard ihex firmware is parsed directly by the driver.
	 */
	error = request_firmware(&fw, fw_file, &client->dev);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to request firmware %s: %d\n",
			fw_file, error);
		वापस error;
	पूर्ण

	करो अणु
		अगर (pos + माप(*rec) > fw->size) अणु
			dev_err(&client->dev, "Insufficient firmware size\n");
			error = -EINVAL;
			अवरोध;
		पूर्ण
		rec = (काष्ठा iqs5xx_ihex_rec *)(fw->data + pos);
		pos += माप(*rec);

		अगर (rec->start != ':') अणु
			dev_err(&client->dev, "Invalid start at record %u\n",
				rec_num);
			error = -EINVAL;
			अवरोध;
		पूर्ण

		error = hex2bin(rec_hdr, rec->len, माप(rec_hdr));
		अगर (error) अणु
			dev_err(&client->dev, "Invalid header at record %u\n",
				rec_num);
			अवरोध;
		पूर्ण

		rec_len = *rec_hdr;
		rec_addr = get_unaligned_be16(rec_hdr + माप(rec_len));
		rec_type = *(rec_hdr + माप(rec_len) + माप(rec_addr));

		अगर (pos + rec_len * 2 > fw->size) अणु
			dev_err(&client->dev, "Insufficient firmware size\n");
			error = -EINVAL;
			अवरोध;
		पूर्ण
		pos += (rec_len * 2);

		error = hex2bin(rec_data, rec->data, rec_len);
		अगर (error) अणु
			dev_err(&client->dev, "Invalid data at record %u\n",
				rec_num);
			अवरोध;
		पूर्ण

		error = hex2bin(&rec_chksm,
				rec->data + rec_len * 2, माप(rec_chksm));
		अगर (error) अणु
			dev_err(&client->dev, "Invalid checksum at record %u\n",
				rec_num);
			अवरोध;
		पूर्ण

		chksm = 0;
		क्रम (i = 0; i < माप(rec_hdr); i++)
			chksm += rec_hdr[i];
		क्रम (i = 0; i < rec_len; i++)
			chksm += rec_data[i];
		chksm = ~chksm + 1;

		अगर (chksm != rec_chksm && rec_addr < IQS5XX_CSTM) अणु
			dev_err(&client->dev,
				"Incorrect checksum at record %u\n",
				rec_num);
			error = -EINVAL;
			अवरोध;
		पूर्ण

		चयन (rec_type) अणु
		हाल IQS5XX_REC_TYPE_DATA:
			अगर (rec_addr < IQS5XX_CHKSM ||
			    rec_addr > IQS5XX_PMAP_END) अणु
				dev_err(&client->dev,
					"Invalid address at record %u\n",
					rec_num);
				error = -EINVAL;
			पूर्ण अन्यथा अणु
				स_नकल(pmap + rec_addr - IQS5XX_CHKSM,
				       rec_data, rec_len);
			पूर्ण
			अवरोध;
		हाल IQS5XX_REC_TYPE_खातापूर्ण:
			अवरोध;
		शेष:
			dev_err(&client->dev, "Invalid type at record %u\n",
				rec_num);
			error = -EINVAL;
		पूर्ण

		अगर (error)
			अवरोध;

		rec_num++;
		जबतक (pos < fw->size) अणु
			अगर (*(fw->data + pos) == ':')
				अवरोध;
			pos++;
		पूर्ण
	पूर्ण जबतक (rec_type != IQS5XX_REC_TYPE_खातापूर्ण);

	release_firmware(fw);

	वापस error;
पूर्ण

अटल पूर्णांक iqs5xx_fw_file_ग_लिखो(काष्ठा i2c_client *client, स्थिर अक्षर *fw_file)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = i2c_get_clientdata(client);
	पूर्णांक error, error_init = 0;
	u8 *pmap;

	pmap = kzalloc(IQS5XX_PMAP_LEN, GFP_KERNEL);
	अगर (!pmap)
		वापस -ENOMEM;

	error = iqs5xx_fw_file_parse(client, fw_file, pmap);
	अगर (error)
		जाओ err_kमुक्त;

	mutex_lock(&iqs5xx->lock);

	/*
	 * Disable the पूर्णांकerrupt line in हाल the first attempt(s) to enter the
	 * bootloader करोn't happen quickly enough, in which हाल the device may
	 * निश्चित the RDY output until the next attempt.
	 */
	disable_irq(client->irq);

	iqs5xx->dev_id_info.bl_status = 0;

	error = iqs5xx_bl_cmd(client, IQS5XX_BL_CMD_VER, 0);
	अगर (error) अणु
		error = iqs5xx_bl_खोलो(client);
		अगर (error)
			जाओ err_reset;
	पूर्ण

	error = iqs5xx_bl_ग_लिखो(client, IQS5XX_CHKSM, pmap, IQS5XX_PMAP_LEN);
	अगर (error)
		जाओ err_reset;

	error = iqs5xx_bl_cmd(client, IQS5XX_BL_CMD_CRC, 0);
	अगर (error)
		जाओ err_reset;

	error = iqs5xx_bl_verअगरy(client, IQS5XX_CSTM,
				 pmap + IQS5XX_CHKSM_LEN + IQS5XX_APP_LEN,
				 IQS5XX_CSTM_LEN);

err_reset:
	iqs5xx_reset(client);
	usleep_range(15000, 15100);

	error_init = iqs5xx_dev_init(client);
	अगर (!iqs5xx->dev_id_info.bl_status)
		error_init = error_init ? : -EINVAL;

	enable_irq(client->irq);

	mutex_unlock(&iqs5xx->lock);

err_kमुक्त:
	kमुक्त(pmap);

	वापस error ? : error_init;
पूर्ण

अटल sमाप_प्रकार fw_file_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = iqs5xx->client;
	माप_प्रकार len = count;
	bool input_reg = !iqs5xx->input;
	अक्षर fw_file[IQS5XX_FW_खाता_LEN + 1];
	पूर्णांक error;

	अगर (!len)
		वापस -EINVAL;

	अगर (buf[len - 1] == '\n')
		len--;

	अगर (len > IQS5XX_FW_खाता_LEN)
		वापस -ENAMETOOLONG;

	स_नकल(fw_file, buf, len);
	fw_file[len] = '\0';

	error = iqs5xx_fw_file_ग_लिखो(client, fw_file);
	अगर (error)
		वापस error;

	/*
	 * If the input device was not allocated alपढ़ोy, it is guaranteed to
	 * be allocated by this poपूर्णांक and can finally be रेजिस्टरed.
	 */
	अगर (input_reg) अणु
		error = input_रेजिस्टर_device(iqs5xx->input);
		अगर (error) अणु
			dev_err(&client->dev,
				"Failed to register device: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार fw_info_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = dev_get_drvdata(dev);

	अगर (!iqs5xx->dev_id_info.bl_status)
		वापस -ENODATA;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u.%u.%u.%u:%u.%u\n",
			 be16_to_cpu(iqs5xx->dev_id_info.prod_num),
			 be16_to_cpu(iqs5xx->dev_id_info.proj_num),
			 iqs5xx->dev_id_info.major_ver,
			 iqs5xx->dev_id_info.minor_ver,
			 iqs5xx->exp_file[0], iqs5xx->exp_file[1]);
पूर्ण

अटल DEVICE_ATTR_WO(fw_file);
अटल DEVICE_ATTR_RO(fw_info);

अटल काष्ठा attribute *iqs5xx_attrs[] = अणु
	&dev_attr_fw_file.attr,
	&dev_attr_fw_info.attr,
	शून्य,
पूर्ण;

अटल umode_t iqs5xx_attr_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा iqs5xx_निजी *iqs5xx = dev_get_drvdata(dev);

	अगर (attr == &dev_attr_fw_file.attr &&
	    (iqs5xx->dev_id_info.bl_status == IQS5XX_BL_STATUS_NONE ||
	    !iqs5xx->reset_gpio))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group iqs5xx_attr_group = अणु
	.is_visible = iqs5xx_attr_is_visible,
	.attrs = iqs5xx_attrs,
पूर्ण;

अटल पूर्णांक __maybe_unused iqs5xx_suspend(काष्ठा device *dev)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = dev_get_drvdata(dev);
	काष्ठा input_dev *input = iqs5xx->input;
	पूर्णांक error = 0;

	अगर (!input || device_may_wakeup(dev))
		वापस error;

	mutex_lock(&input->mutex);

	अगर (input_device_enabled(input))
		error = iqs5xx_set_state(iqs5xx->client, IQS5XX_SUSPEND);

	mutex_unlock(&input->mutex);

	वापस error;
पूर्ण

अटल पूर्णांक __maybe_unused iqs5xx_resume(काष्ठा device *dev)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx = dev_get_drvdata(dev);
	काष्ठा input_dev *input = iqs5xx->input;
	पूर्णांक error = 0;

	अगर (!input || device_may_wakeup(dev))
		वापस error;

	mutex_lock(&input->mutex);

	अगर (input_device_enabled(input))
		error = iqs5xx_set_state(iqs5xx->client, IQS5XX_RESUME);

	mutex_unlock(&input->mutex);

	वापस error;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(iqs5xx_pm, iqs5xx_suspend, iqs5xx_resume);

अटल पूर्णांक iqs5xx_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iqs5xx_निजी *iqs5xx;
	पूर्णांक error;

	iqs5xx = devm_kzalloc(&client->dev, माप(*iqs5xx), GFP_KERNEL);
	अगर (!iqs5xx)
		वापस -ENOMEM;

	i2c_set_clientdata(client, iqs5xx);
	iqs5xx->client = client;

	iqs5xx->reset_gpio = devm_gpiod_get_optional(&client->dev,
						     "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(iqs5xx->reset_gpio)) अणु
		error = PTR_ERR(iqs5xx->reset_gpio);
		dev_err(&client->dev, "Failed to request GPIO: %d\n", error);
		वापस error;
	पूर्ण

	mutex_init(&iqs5xx->lock);

	error = iqs5xx_dev_init(client);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, iqs5xx_irq, IRQF_ONESHOT,
					  client->name, iqs5xx);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to request IRQ: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_device_add_group(&client->dev, &iqs5xx_attr_group);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to add attributes: %d\n", error);
		वापस error;
	पूर्ण

	अगर (iqs5xx->input) अणु
		error = input_रेजिस्टर_device(iqs5xx->input);
		अगर (error)
			dev_err(&client->dev,
				"Failed to register device: %d\n",
				error);
	पूर्ण

	वापस error;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id iqs5xx_id[] = अणु
	अणु "iqs550", 0 पूर्ण,
	अणु "iqs572", 1 पूर्ण,
	अणु "iqs525", 2 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, iqs5xx_id);

अटल स्थिर काष्ठा of_device_id iqs5xx_of_match[] = अणु
	अणु .compatible = "azoteq,iqs550" पूर्ण,
	अणु .compatible = "azoteq,iqs572" पूर्ण,
	अणु .compatible = "azoteq,iqs525" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, iqs5xx_of_match);

अटल काष्ठा i2c_driver iqs5xx_i2c_driver = अणु
	.driver = अणु
		.name		= "iqs5xx",
		.of_match_table	= iqs5xx_of_match,
		.pm		= &iqs5xx_pm,
	पूर्ण,
	.id_table	= iqs5xx_id,
	.probe		= iqs5xx_probe,
पूर्ण;
module_i2c_driver(iqs5xx_i2c_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("Azoteq IQS550/572/525 Trackpad/Touchscreen Controller");
MODULE_LICENSE("GPL");

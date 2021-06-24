<शैली गुरु>
/*
 * Weida HiTech WDT87xx TouchScreen I2C driver
 *
 * Copyright (c) 2015  Weida Hi-Tech Co., Ltd.
 * HN Chen <hn.chen@weidahitech.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License, as published by the Free Software Foundation, and
 * may be copied, distributed, and modअगरied under those terms.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा WDT87XX_NAME		"wdt87xx_i2c"
#घोषणा WDT87XX_FW_NAME		"wdt87xx_fw.bin"
#घोषणा WDT87XX_CFG_NAME	"wdt87xx_cfg.bin"

#घोषणा MODE_ACTIVE			0x01
#घोषणा MODE_READY			0x02
#घोषणा MODE_IDLE			0x03
#घोषणा MODE_SLEEP			0x04
#घोषणा MODE_STOP			0xFF

#घोषणा WDT_MAX_FINGER			10
#घोषणा WDT_RAW_BUF_COUNT		54
#घोषणा WDT_V1_RAW_BUF_COUNT		74
#घोषणा WDT_FIRMWARE_ID			0xa9e368f5

#घोषणा PG_SIZE				0x1000
#घोषणा MAX_RETRIES			3

#घोषणा MAX_UNIT_AXIS			0x7FFF

#घोषणा PKT_READ_SIZE			72
#घोषणा PKT_WRITE_SIZE			80

/* the finger definition of the report event */
#घोषणा FINGER_EV_OFFSET_ID		0
#घोषणा FINGER_EV_OFFSET_X		1
#घोषणा FINGER_EV_OFFSET_Y		3
#घोषणा FINGER_EV_SIZE			5

#घोषणा FINGER_EV_V1_OFFSET_ID		0
#घोषणा FINGER_EV_V1_OFFSET_W		1
#घोषणा FINGER_EV_V1_OFFSET_P		2
#घोषणा FINGER_EV_V1_OFFSET_X		3
#घोषणा FINGER_EV_V1_OFFSET_Y		5
#घोषणा FINGER_EV_V1_SIZE		7

/* The definition of a report packet */
#घोषणा TOUCH_PK_OFFSET_REPORT_ID	0
#घोषणा TOUCH_PK_OFFSET_EVENT		1
#घोषणा TOUCH_PK_OFFSET_SCAN_TIME	51
#घोषणा TOUCH_PK_OFFSET_FNGR_NUM	53

#घोषणा TOUCH_PK_V1_OFFSET_REPORT_ID	0
#घोषणा TOUCH_PK_V1_OFFSET_EVENT	1
#घोषणा TOUCH_PK_V1_OFFSET_SCAN_TIME	71
#घोषणा TOUCH_PK_V1_OFFSET_FNGR_NUM	73

/* The definition of the controller parameters */
#घोषणा CTL_PARAM_OFFSET_FW_ID		0
#घोषणा CTL_PARAM_OFFSET_PLAT_ID	2
#घोषणा CTL_PARAM_OFFSET_XMLS_ID1	4
#घोषणा CTL_PARAM_OFFSET_XMLS_ID2	6
#घोषणा CTL_PARAM_OFFSET_PHY_CH_X	8
#घोषणा CTL_PARAM_OFFSET_PHY_CH_Y	10
#घोषणा CTL_PARAM_OFFSET_PHY_X0		12
#घोषणा CTL_PARAM_OFFSET_PHY_X1		14
#घोषणा CTL_PARAM_OFFSET_PHY_Y0		16
#घोषणा CTL_PARAM_OFFSET_PHY_Y1		18
#घोषणा CTL_PARAM_OFFSET_PHY_W		22
#घोषणा CTL_PARAM_OFFSET_PHY_H		24
#घोषणा CTL_PARAM_OFFSET_FACTOR		32

/* The definition of the device descriptor */
#घोषणा WDT_GD_DEVICE			1
#घोषणा DEV_DESC_OFFSET_VID		8
#घोषणा DEV_DESC_OFFSET_PID		10

/* Communication commands */
#घोषणा PACKET_SIZE			56
#घोषणा VND_REQ_READ			0x06
#घोषणा VND_READ_DATA			0x07
#घोषणा VND_REQ_WRITE			0x08

#घोषणा VND_CMD_START			0x00
#घोषणा VND_CMD_STOP			0x01
#घोषणा VND_CMD_RESET			0x09

#घोषणा VND_CMD_ERASE			0x1A

#घोषणा VND_GET_CHECKSUM		0x66

#घोषणा VND_SET_DATA			0x83
#घोषणा VND_SET_COMMAND_DATA		0x84
#घोषणा VND_SET_CHECKSUM_CALC		0x86
#घोषणा VND_SET_CHECKSUM_LENGTH		0x87

#घोषणा VND_CMD_SFLCK			0xFC
#घोषणा VND_CMD_SFUNL			0xFD

#घोषणा CMD_SFLCK_KEY			0xC39B
#घोषणा CMD_SFUNL_KEY			0x95DA

#घोषणा STRIDX_PLATFORM_ID		0x80
#घोषणा STRIDX_PARAMETERS		0x81

#घोषणा CMD_BUF_SIZE			8
#घोषणा PKT_BUF_SIZE			64

/* The definition of the command packet */
#घोषणा CMD_REPORT_ID_OFFSET		0x0
#घोषणा CMD_TYPE_OFFSET			0x1
#घोषणा CMD_INDEX_OFFSET		0x2
#घोषणा CMD_KEY_OFFSET			0x3
#घोषणा CMD_LENGTH_OFFSET		0x4
#घोषणा CMD_DATA_OFFSET			0x8

/* The definition of firmware chunk tags */
#घोषणा FOURCC_ID_RIFF			0x46464952
#घोषणा FOURCC_ID_WHIF			0x46494857
#घोषणा FOURCC_ID_FRMT			0x544D5246
#घोषणा FOURCC_ID_FRWR			0x52575246
#घोषणा FOURCC_ID_CNFG			0x47464E43

#घोषणा CHUNK_ID_FRMT			FOURCC_ID_FRMT
#घोषणा CHUNK_ID_FRWR			FOURCC_ID_FRWR
#घोषणा CHUNK_ID_CNFG			FOURCC_ID_CNFG

#घोषणा FW_FOURCC1_OFFSET		0
#घोषणा FW_SIZE_OFFSET			4
#घोषणा FW_FOURCC2_OFFSET		8
#घोषणा FW_PAYLOAD_OFFSET		40

#घोषणा FW_CHUNK_ID_OFFSET		0
#घोषणा FW_CHUNK_SIZE_OFFSET		4
#घोषणा FW_CHUNK_TGT_START_OFFSET	8
#घोषणा FW_CHUNK_PAYLOAD_LEN_OFFSET	12
#घोषणा FW_CHUNK_SRC_START_OFFSET	16
#घोषणा FW_CHUNK_VERSION_OFFSET		20
#घोषणा FW_CHUNK_ATTR_OFFSET		24
#घोषणा FW_CHUNK_PAYLOAD_OFFSET		32

/* Controller requires minimum 300us between commands */
#घोषणा WDT_COMMAND_DELAY_MS		2
#घोषणा WDT_FLASH_WRITE_DELAY_MS	4
#घोषणा WDT_FLASH_ERASE_DELAY_MS	200
#घोषणा WDT_FW_RESET_TIME		2500

काष्ठा wdt87xx_sys_param अणु
	u16	fw_id;
	u16	plat_id;
	u16	xmls_id1;
	u16	xmls_id2;
	u16	phy_ch_x;
	u16	phy_ch_y;
	u16	phy_w;
	u16	phy_h;
	u16	scaling_factor;
	u32	max_x;
	u32	max_y;
	u16	venकरोr_id;
	u16	product_id;
पूर्ण;

काष्ठा wdt87xx_data अणु
	काष्ठा i2c_client		*client;
	काष्ठा input_dev		*input;
	/* Mutex क्रम fw update to prevent concurrent access */
	काष्ठा mutex			fw_mutex;
	काष्ठा wdt87xx_sys_param	param;
	u8				phys[32];
पूर्ण;

अटल पूर्णांक wdt87xx_i2c_xfer(काष्ठा i2c_client *client,
			    व्योम *txdata, माप_प्रकार txlen,
			    व्योम *rxdata, माप_प्रकार rxlen)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= client->addr,
			.flags	= 0,
			.len	= txlen,
			.buf	= txdata,
		पूर्ण,
		अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD,
			.len	= rxlen,
			.buf	= rxdata,
		पूर्ण,
	पूर्ण;
	पूर्णांक error;
	पूर्णांक ret;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs)) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&client->dev, "%s: i2c transfer failed: %d\n",
			__func__, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_get_desc(काष्ठा i2c_client *client, u8 desc_idx,
			    u8 *buf, माप_प्रकार len)
अणु
	u8 tx_buf[] = अणु 0x22, 0x00, 0x10, 0x0E, 0x23, 0x00 पूर्ण;
	पूर्णांक error;

	tx_buf[2] |= desc_idx & 0xF;

	error = wdt87xx_i2c_xfer(client, tx_buf, माप(tx_buf),
				 buf, len);
	अगर (error) अणु
		dev_err(&client->dev, "get desc failed: %d\n", error);
		वापस error;
	पूर्ण

	अगर (buf[0] != len) अणु
		dev_err(&client->dev, "unexpected response to get desc: %d\n",
			buf[0]);
		वापस -EINVAL;
	पूर्ण

	mdelay(WDT_COMMAND_DELAY_MS);

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_get_string(काष्ठा i2c_client *client, u8 str_idx,
			      u8 *buf, माप_प्रकार len)
अणु
	u8 tx_buf[] = अणु 0x22, 0x00, 0x13, 0x0E, str_idx, 0x23, 0x00 पूर्ण;
	u8 rx_buf[PKT_WRITE_SIZE];
	माप_प्रकार rx_len = len + 2;
	पूर्णांक error;

	अगर (rx_len > माप(rx_buf))
		वापस -EINVAL;

	error = wdt87xx_i2c_xfer(client, tx_buf, माप(tx_buf),
				 rx_buf, rx_len);
	अगर (error) अणु
		dev_err(&client->dev, "get string failed: %d\n", error);
		वापस error;
	पूर्ण

	अगर (rx_buf[1] != 0x03) अणु
		dev_err(&client->dev, "unexpected response to get string: %d\n",
			rx_buf[1]);
		वापस -EINVAL;
	पूर्ण

	rx_len = min_t(माप_प्रकार, len, rx_buf[0]);
	स_नकल(buf, &rx_buf[2], rx_len);

	mdelay(WDT_COMMAND_DELAY_MS);

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_get_feature(काष्ठा i2c_client *client,
			       u8 *buf, माप_प्रकार buf_size)
अणु
	u8 tx_buf[8];
	u8 rx_buf[PKT_WRITE_SIZE];
	माप_प्रकार tx_len = 0;
	माप_प्रकार rx_len = buf_size + 2;
	पूर्णांक error;

	अगर (rx_len > माप(rx_buf))
		वापस -EINVAL;

	/* Get feature command packet */
	tx_buf[tx_len++] = 0x22;
	tx_buf[tx_len++] = 0x00;
	अगर (buf[CMD_REPORT_ID_OFFSET] > 0xF) अणु
		tx_buf[tx_len++] = 0x30;
		tx_buf[tx_len++] = 0x02;
		tx_buf[tx_len++] = buf[CMD_REPORT_ID_OFFSET];
	पूर्ण अन्यथा अणु
		tx_buf[tx_len++] = 0x30 | buf[CMD_REPORT_ID_OFFSET];
		tx_buf[tx_len++] = 0x02;
	पूर्ण
	tx_buf[tx_len++] = 0x23;
	tx_buf[tx_len++] = 0x00;

	error = wdt87xx_i2c_xfer(client, tx_buf, tx_len, rx_buf, rx_len);
	अगर (error) अणु
		dev_err(&client->dev, "get feature failed: %d\n", error);
		वापस error;
	पूर्ण

	rx_len = min_t(माप_प्रकार, buf_size, get_unaligned_le16(rx_buf));
	स_नकल(buf, &rx_buf[2], rx_len);

	mdelay(WDT_COMMAND_DELAY_MS);

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_set_feature(काष्ठा i2c_client *client,
			       स्थिर u8 *buf, माप_प्रकार buf_size)
अणु
	u8 tx_buf[PKT_WRITE_SIZE];
	पूर्णांक tx_len = 0;
	पूर्णांक error;

	/* Set feature command packet */
	tx_buf[tx_len++] = 0x22;
	tx_buf[tx_len++] = 0x00;
	अगर (buf[CMD_REPORT_ID_OFFSET] > 0xF) अणु
		tx_buf[tx_len++] = 0x30;
		tx_buf[tx_len++] = 0x03;
		tx_buf[tx_len++] = buf[CMD_REPORT_ID_OFFSET];
	पूर्ण अन्यथा अणु
		tx_buf[tx_len++] = 0x30 | buf[CMD_REPORT_ID_OFFSET];
		tx_buf[tx_len++] = 0x03;
	पूर्ण
	tx_buf[tx_len++] = 0x23;
	tx_buf[tx_len++] = 0x00;
	tx_buf[tx_len++] = (buf_size & 0xFF);
	tx_buf[tx_len++] = ((buf_size & 0xFF00) >> 8);

	अगर (tx_len + buf_size > माप(tx_buf))
		वापस -EINVAL;

	स_नकल(&tx_buf[tx_len], buf, buf_size);
	tx_len += buf_size;

	error = i2c_master_send(client, tx_buf, tx_len);
	अगर (error < 0) अणु
		dev_err(&client->dev, "set feature failed: %d\n", error);
		वापस error;
	पूर्ण

	mdelay(WDT_COMMAND_DELAY_MS);

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_send_command(काष्ठा i2c_client *client, पूर्णांक cmd, पूर्णांक value)
अणु
	u8 cmd_buf[CMD_BUF_SIZE];

	/* Set the command packet */
	cmd_buf[CMD_REPORT_ID_OFFSET] = VND_REQ_WRITE;
	cmd_buf[CMD_TYPE_OFFSET] = VND_SET_COMMAND_DATA;
	put_unaligned_le16((u16)cmd, &cmd_buf[CMD_INDEX_OFFSET]);

	चयन (cmd) अणु
	हाल VND_CMD_START:
	हाल VND_CMD_STOP:
	हाल VND_CMD_RESET:
		/* Mode selector */
		put_unaligned_le32((value & 0xFF), &cmd_buf[CMD_LENGTH_OFFSET]);
		अवरोध;

	हाल VND_CMD_SFLCK:
		put_unaligned_le16(CMD_SFLCK_KEY, &cmd_buf[CMD_KEY_OFFSET]);
		अवरोध;

	हाल VND_CMD_SFUNL:
		put_unaligned_le16(CMD_SFUNL_KEY, &cmd_buf[CMD_KEY_OFFSET]);
		अवरोध;

	हाल VND_CMD_ERASE:
	हाल VND_SET_CHECKSUM_CALC:
	हाल VND_SET_CHECKSUM_LENGTH:
		put_unaligned_le32(value, &cmd_buf[CMD_KEY_OFFSET]);
		अवरोध;

	शेष:
		cmd_buf[CMD_REPORT_ID_OFFSET] = 0;
		dev_err(&client->dev, "Invalid command: %d\n", cmd);
		वापस -EINVAL;
	पूर्ण

	वापस wdt87xx_set_feature(client, cmd_buf, माप(cmd_buf));
पूर्ण

अटल पूर्णांक wdt87xx_sw_reset(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;

	dev_dbg(&client->dev, "resetting device now\n");

	error = wdt87xx_send_command(client, VND_CMD_RESET, 0);
	अगर (error) अणु
		dev_err(&client->dev, "reset failed\n");
		वापस error;
	पूर्ण

	/* Wait the device to be पढ़ोy */
	msleep(WDT_FW_RESET_TIME);

	वापस 0;
पूर्ण

अटल स्थिर व्योम *wdt87xx_get_fw_chunk(स्थिर काष्ठा firmware *fw, u32 id)
अणु
	माप_प्रकार pos = FW_PAYLOAD_OFFSET;
	u32 chunk_id, chunk_size;

	जबतक (pos < fw->size) अणु
		chunk_id = get_unaligned_le32(fw->data +
					      pos + FW_CHUNK_ID_OFFSET);
		अगर (chunk_id == id)
			वापस fw->data + pos;

		chunk_size = get_unaligned_le32(fw->data +
						pos + FW_CHUNK_SIZE_OFFSET);
		pos += chunk_size + 2 * माप(u32); /* chunk ID + size */
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक wdt87xx_get_sysparam(काष्ठा i2c_client *client,
				काष्ठा wdt87xx_sys_param *param)
अणु
	u8 buf[PKT_READ_SIZE];
	पूर्णांक error;

	error = wdt87xx_get_desc(client, WDT_GD_DEVICE, buf, 18);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get device desc\n");
		वापस error;
	पूर्ण

	param->venकरोr_id = get_unaligned_le16(buf + DEV_DESC_OFFSET_VID);
	param->product_id = get_unaligned_le16(buf + DEV_DESC_OFFSET_PID);

	error = wdt87xx_get_string(client, STRIDX_PARAMETERS, buf, 34);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get parameters\n");
		वापस error;
	पूर्ण

	param->xmls_id1 = get_unaligned_le16(buf + CTL_PARAM_OFFSET_XMLS_ID1);
	param->xmls_id2 = get_unaligned_le16(buf + CTL_PARAM_OFFSET_XMLS_ID2);
	param->phy_ch_x = get_unaligned_le16(buf + CTL_PARAM_OFFSET_PHY_CH_X);
	param->phy_ch_y = get_unaligned_le16(buf + CTL_PARAM_OFFSET_PHY_CH_Y);
	param->phy_w = get_unaligned_le16(buf + CTL_PARAM_OFFSET_PHY_W) / 10;
	param->phy_h = get_unaligned_le16(buf + CTL_PARAM_OFFSET_PHY_H) / 10;

	/* Get the scaling factor of pixel to logical coordinate */
	param->scaling_factor =
			get_unaligned_le16(buf + CTL_PARAM_OFFSET_FACTOR);

	param->max_x = MAX_UNIT_AXIS;
	param->max_y = DIV_ROUND_CLOSEST(MAX_UNIT_AXIS * param->phy_h,
					 param->phy_w);

	error = wdt87xx_get_string(client, STRIDX_PLATFORM_ID, buf, 8);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get platform id\n");
		वापस error;
	पूर्ण

	param->plat_id = buf[1];

	buf[0] = 0xf2;
	error = wdt87xx_get_feature(client, buf, 16);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get firmware id\n");
		वापस error;
	पूर्ण

	अगर (buf[0] != 0xf2) अणु
		dev_err(&client->dev, "wrong id of fw response: 0x%x\n",
			buf[0]);
		वापस -EINVAL;
	पूर्ण

	param->fw_id = get_unaligned_le16(&buf[1]);

	dev_info(&client->dev,
		 "fw_id: 0x%x, plat_id: 0x%x, xml_id1: %04x, xml_id2: %04x\n",
		 param->fw_id, param->plat_id,
		 param->xmls_id1, param->xmls_id2);

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_validate_firmware(काष्ठा wdt87xx_data *wdt,
				     स्थिर काष्ठा firmware *fw)
अणु
	स्थिर व्योम *fw_chunk;
	u32 data1, data2;
	u32 size;
	u8 fw_chip_id;
	u8 chip_id;

	data1 = get_unaligned_le32(fw->data + FW_FOURCC1_OFFSET);
	data2 = get_unaligned_le32(fw->data + FW_FOURCC2_OFFSET);
	अगर (data1 != FOURCC_ID_RIFF || data2 != FOURCC_ID_WHIF) अणु
		dev_err(&wdt->client->dev, "check fw tag failed\n");
		वापस -EINVAL;
	पूर्ण

	size = get_unaligned_le32(fw->data + FW_SIZE_OFFSET);
	अगर (size != fw->size) अणु
		dev_err(&wdt->client->dev,
			"fw size mismatch: expected %d, actual %zu\n",
			size, fw->size);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Get the chip_id from the firmware. Make sure that it is the
	 * right controller to करो the firmware and config update.
	 */
	fw_chunk = wdt87xx_get_fw_chunk(fw, CHUNK_ID_FRWR);
	अगर (!fw_chunk) अणु
		dev_err(&wdt->client->dev,
			"unable to locate firmware chunk\n");
		वापस -EINVAL;
	पूर्ण

	fw_chip_id = (get_unaligned_le32(fw_chunk +
					 FW_CHUNK_VERSION_OFFSET) >> 12) & 0xF;
	chip_id = (wdt->param.fw_id >> 12) & 0xF;

	अगर (fw_chip_id != chip_id) अणु
		dev_err(&wdt->client->dev,
			"fw version mismatch: fw %d vs. chip %d\n",
			fw_chip_id, chip_id);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_validate_fw_chunk(स्थिर व्योम *data, पूर्णांक id)
अणु
	अगर (id == CHUNK_ID_FRWR) अणु
		u32 fw_id;

		fw_id = get_unaligned_le32(data + FW_CHUNK_PAYLOAD_OFFSET);
		अगर (fw_id != WDT_FIRMWARE_ID)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_ग_लिखो_data(काष्ठा i2c_client *client, स्थिर अक्षर *data,
			      u32 address, पूर्णांक length)
अणु
	u16 packet_size;
	पूर्णांक count = 0;
	पूर्णांक error;
	u8 pkt_buf[PKT_BUF_SIZE];

	/* Address and length should be 4 bytes aligned */
	अगर ((address & 0x3) != 0 || (length & 0x3) != 0) अणु
		dev_err(&client->dev,
			"addr & len must be 4 bytes aligned %x, %x\n",
			address, length);
		वापस -EINVAL;
	पूर्ण

	जबतक (length) अणु
		packet_size = min(length, PACKET_SIZE);

		pkt_buf[CMD_REPORT_ID_OFFSET] = VND_REQ_WRITE;
		pkt_buf[CMD_TYPE_OFFSET] = VND_SET_DATA;
		put_unaligned_le16(packet_size, &pkt_buf[CMD_INDEX_OFFSET]);
		put_unaligned_le32(address, &pkt_buf[CMD_LENGTH_OFFSET]);
		स_नकल(&pkt_buf[CMD_DATA_OFFSET], data, packet_size);

		error = wdt87xx_set_feature(client, pkt_buf, माप(pkt_buf));
		अगर (error)
			वापस error;

		length -= packet_size;
		data += packet_size;
		address += packet_size;

		/* Wait क्रम the controller to finish the ग_लिखो */
		mdelay(WDT_FLASH_WRITE_DELAY_MS);

		अगर ((++count % 32) == 0) अणु
			/* Delay क्रम fw to clear watch करोg */
			msleep(20);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 misr(u16 cur_value, u8 new_value)
अणु
	u32 a, b;
	u32 bit0;
	u32 y;

	a = cur_value;
	b = new_value;
	bit0 = a ^ (b & 1);
	bit0 ^= a >> 1;
	bit0 ^= a >> 2;
	bit0 ^= a >> 4;
	bit0 ^= a >> 5;
	bit0 ^= a >> 7;
	bit0 ^= a >> 11;
	bit0 ^= a >> 15;
	y = (a << 1) ^ b;
	y = (y & ~1) | (bit0 & 1);

	वापस (u16)y;
पूर्ण

अटल u16 wdt87xx_calculate_checksum(स्थिर u8 *data, माप_प्रकार length)
अणु
	u16 checksum = 0;
	माप_प्रकार i;

	क्रम (i = 0; i < length; i++)
		checksum = misr(checksum, data[i]);

	वापस checksum;
पूर्ण

अटल पूर्णांक wdt87xx_get_checksum(काष्ठा i2c_client *client, u16 *checksum,
				u32 address, पूर्णांक length)
अणु
	पूर्णांक error;
	पूर्णांक समय_delay;
	u8 pkt_buf[PKT_BUF_SIZE];
	u8 cmd_buf[CMD_BUF_SIZE];

	error = wdt87xx_send_command(client, VND_SET_CHECKSUM_LENGTH, length);
	अगर (error) अणु
		dev_err(&client->dev, "failed to set checksum length\n");
		वापस error;
	पूर्ण

	error = wdt87xx_send_command(client, VND_SET_CHECKSUM_CALC, address);
	अगर (error) अणु
		dev_err(&client->dev, "failed to set checksum address\n");
		वापस error;
	पूर्ण

	/* Wait the operation to complete */
	समय_delay = DIV_ROUND_UP(length, 1024);
	msleep(समय_delay * 30);

	स_रखो(cmd_buf, 0, माप(cmd_buf));
	cmd_buf[CMD_REPORT_ID_OFFSET] = VND_REQ_READ;
	cmd_buf[CMD_TYPE_OFFSET] = VND_GET_CHECKSUM;
	error = wdt87xx_set_feature(client, cmd_buf, माप(cmd_buf));
	अगर (error) अणु
		dev_err(&client->dev, "failed to request checksum\n");
		वापस error;
	पूर्ण

	स_रखो(pkt_buf, 0, माप(pkt_buf));
	pkt_buf[CMD_REPORT_ID_OFFSET] = VND_READ_DATA;
	error = wdt87xx_get_feature(client, pkt_buf, माप(pkt_buf));
	अगर (error) अणु
		dev_err(&client->dev, "failed to read checksum\n");
		वापस error;
	पूर्ण

	*checksum = get_unaligned_le16(&pkt_buf[CMD_DATA_OFFSET]);
	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_ग_लिखो_firmware(काष्ठा i2c_client *client, स्थिर व्योम *chunk)
अणु
	u32 start_addr = get_unaligned_le32(chunk + FW_CHUNK_TGT_START_OFFSET);
	u32 size = get_unaligned_le32(chunk + FW_CHUNK_PAYLOAD_LEN_OFFSET);
	स्थिर व्योम *data = chunk + FW_CHUNK_PAYLOAD_OFFSET;
	पूर्णांक error;
	पूर्णांक err1;
	पूर्णांक page_size;
	पूर्णांक retry = 0;
	u16 device_checksum, firmware_checksum;

	dev_dbg(&client->dev, "start 4k page program\n");

	error = wdt87xx_send_command(client, VND_CMD_STOP, MODE_STOP);
	अगर (error) अणु
		dev_err(&client->dev, "stop report mode failed\n");
		वापस error;
	पूर्ण

	error = wdt87xx_send_command(client, VND_CMD_SFUNL, 0);
	अगर (error) अणु
		dev_err(&client->dev, "unlock failed\n");
		जाओ out_enable_reporting;
	पूर्ण

	mdelay(10);

	जबतक (size) अणु
		dev_dbg(&client->dev, "%s: %x, %x\n", __func__,
			start_addr, size);

		page_size = min_t(u32, size, PG_SIZE);
		size -= page_size;

		क्रम (retry = 0; retry < MAX_RETRIES; retry++) अणु
			error = wdt87xx_send_command(client, VND_CMD_ERASE,
						     start_addr);
			अगर (error) अणु
				dev_err(&client->dev,
					"erase failed at %#08x\n", start_addr);
				अवरोध;
			पूर्ण

			msleep(WDT_FLASH_ERASE_DELAY_MS);

			error = wdt87xx_ग_लिखो_data(client, data, start_addr,
						   page_size);
			अगर (error) अणु
				dev_err(&client->dev,
					"write failed at %#08x (%d bytes)\n",
					start_addr, page_size);
				अवरोध;
			पूर्ण

			error = wdt87xx_get_checksum(client, &device_checksum,
						     start_addr, page_size);
			अगर (error) अणु
				dev_err(&client->dev,
					"failed to retrieve checksum for %#08x (len: %d)\n",
					start_addr, page_size);
				अवरोध;
			पूर्ण

			firmware_checksum =
				wdt87xx_calculate_checksum(data, page_size);

			अगर (device_checksum == firmware_checksum)
				अवरोध;

			dev_err(&client->dev,
				"checksum fail: %d vs %d, retry %d\n",
				device_checksum, firmware_checksum, retry);
		पूर्ण

		अगर (retry == MAX_RETRIES) अणु
			dev_err(&client->dev, "page write failed\n");
			error = -EIO;
			जाओ out_lock_device;
		पूर्ण

		start_addr = start_addr + page_size;
		data = data + page_size;
	पूर्ण

out_lock_device:
	err1 = wdt87xx_send_command(client, VND_CMD_SFLCK, 0);
	अगर (err1)
		dev_err(&client->dev, "lock failed\n");

	mdelay(10);

out_enable_reporting:
	err1 = wdt87xx_send_command(client, VND_CMD_START, 0);
	अगर (err1)
		dev_err(&client->dev, "start to report failed\n");

	वापस error ? error : err1;
पूर्ण

अटल पूर्णांक wdt87xx_load_chunk(काष्ठा i2c_client *client,
			      स्थिर काष्ठा firmware *fw, u32 ck_id)
अणु
	स्थिर व्योम *chunk;
	पूर्णांक error;

	chunk = wdt87xx_get_fw_chunk(fw, ck_id);
	अगर (!chunk) अणु
		dev_err(&client->dev, "unable to locate chunk (type %d)\n",
			ck_id);
		वापस -EINVAL;
	पूर्ण

	error = wdt87xx_validate_fw_chunk(chunk, ck_id);
	अगर (error) अणु
		dev_err(&client->dev, "invalid chunk (type %d): %d\n",
			ck_id, error);
		वापस error;
	पूर्ण

	error = wdt87xx_ग_लिखो_firmware(client, chunk);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to write fw chunk (type %d): %d\n",
			ck_id, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_करो_update_firmware(काष्ठा i2c_client *client,
				      स्थिर काष्ठा firmware *fw,
				      अचिन्हित पूर्णांक chunk_id)
अणु
	काष्ठा wdt87xx_data *wdt = i2c_get_clientdata(client);
	पूर्णांक error;

	error = wdt87xx_validate_firmware(wdt, fw);
	अगर (error)
		वापस error;

	error = mutex_lock_पूर्णांकerruptible(&wdt->fw_mutex);
	अगर (error)
		वापस error;

	disable_irq(client->irq);

	error = wdt87xx_load_chunk(client, fw, chunk_id);
	अगर (error) अणु
		dev_err(&client->dev,
			"firmware load failed (type: %d): %d\n",
			chunk_id, error);
		जाओ out;
	पूर्ण

	error = wdt87xx_sw_reset(client);
	अगर (error) अणु
		dev_err(&client->dev, "soft reset failed: %d\n", error);
		जाओ out;
	पूर्ण

	/* Refresh the parameters */
	error = wdt87xx_get_sysparam(client, &wdt->param);
	अगर (error)
		dev_err(&client->dev,
			"failed to refresh system parameters: %d\n", error);
out:
	enable_irq(client->irq);
	mutex_unlock(&wdt->fw_mutex);

	वापस error ? error : 0;
पूर्ण

अटल पूर्णांक wdt87xx_update_firmware(काष्ठा device *dev,
				   स्थिर अक्षर *fw_name, अचिन्हित पूर्णांक chunk_id)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	स्थिर काष्ठा firmware *fw;
	पूर्णांक error;

	error = request_firmware(&fw, fw_name, dev);
	अगर (error) अणु
		dev_err(&client->dev, "unable to retrieve firmware %s: %d\n",
			fw_name, error);
		वापस error;
	पूर्ण

	error = wdt87xx_करो_update_firmware(client, fw, chunk_id);

	release_firmware(fw);

	वापस error ? error : 0;
पूर्ण

अटल sमाप_प्रकार config_csum_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा wdt87xx_data *wdt = i2c_get_clientdata(client);
	u32 cfg_csum;

	cfg_csum = wdt->param.xmls_id1;
	cfg_csum = (cfg_csum << 16) | wdt->param.xmls_id2;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%x\n", cfg_csum);
पूर्ण

अटल sमाप_प्रकार fw_version_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा wdt87xx_data *wdt = i2c_get_clientdata(client);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%x\n", wdt->param.fw_id);
पूर्ण

अटल sमाप_प्रकार plat_id_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा wdt87xx_data *wdt = i2c_get_clientdata(client);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%x\n", wdt->param.plat_id);
पूर्ण

अटल sमाप_प्रकार update_config_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक error;

	error = wdt87xx_update_firmware(dev, WDT87XX_CFG_NAME, CHUNK_ID_CNFG);

	वापस error ? error : count;
पूर्ण

अटल sमाप_प्रकार update_fw_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक error;

	error = wdt87xx_update_firmware(dev, WDT87XX_FW_NAME, CHUNK_ID_FRWR);

	वापस error ? error : count;
पूर्ण

अटल DEVICE_ATTR_RO(config_csum);
अटल DEVICE_ATTR_RO(fw_version);
अटल DEVICE_ATTR_RO(plat_id);
अटल DEVICE_ATTR_WO(update_config);
अटल DEVICE_ATTR_WO(update_fw);

अटल काष्ठा attribute *wdt87xx_attrs[] = अणु
	&dev_attr_config_csum.attr,
	&dev_attr_fw_version.attr,
	&dev_attr_plat_id.attr,
	&dev_attr_update_config.attr,
	&dev_attr_update_fw.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group wdt87xx_attr_group = अणु
	.attrs = wdt87xx_attrs,
पूर्ण;

अटल व्योम wdt87xx_report_contact(काष्ठा input_dev *input,
				   काष्ठा wdt87xx_sys_param *param,
				   u8 *buf)
अणु
	पूर्णांक finger_id;
	u32 x, y, w;
	u8 p;

	finger_id = (buf[FINGER_EV_V1_OFFSET_ID] >> 3) - 1;
	अगर (finger_id < 0)
		वापस;

	/* Check अगर this is an active contact */
	अगर (!(buf[FINGER_EV_V1_OFFSET_ID] & 0x1))
		वापस;

	w = buf[FINGER_EV_V1_OFFSET_W];
	w *= param->scaling_factor;

	p = buf[FINGER_EV_V1_OFFSET_P];

	x = get_unaligned_le16(buf + FINGER_EV_V1_OFFSET_X);

	y = get_unaligned_le16(buf + FINGER_EV_V1_OFFSET_Y);
	y = DIV_ROUND_CLOSEST(y * param->phy_h, param->phy_w);

	/* Refuse incorrect coordinates */
	अगर (x > param->max_x || y > param->max_y)
		वापस;

	dev_dbg(input->dev.parent, "tip on (%d), x(%d), y(%d)\n",
		finger_id, x, y);

	input_mt_slot(input, finger_id);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, 1);
	input_report_असल(input, ABS_MT_TOUCH_MAJOR, w);
	input_report_असल(input, ABS_MT_PRESSURE, p);
	input_report_असल(input, ABS_MT_POSITION_X, x);
	input_report_असल(input, ABS_MT_POSITION_Y, y);
पूर्ण

अटल irqवापस_t wdt87xx_ts_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा wdt87xx_data *wdt = dev_id;
	काष्ठा i2c_client *client = wdt->client;
	पूर्णांक i, fingers;
	पूर्णांक error;
	u8 raw_buf[WDT_V1_RAW_BUF_COUNT] = अणु0पूर्ण;

	error = i2c_master_recv(client, raw_buf, WDT_V1_RAW_BUF_COUNT);
	अगर (error < 0) अणु
		dev_err(&client->dev, "read v1 raw data failed: %d\n", error);
		जाओ irq_निकास;
	पूर्ण

	fingers = raw_buf[TOUCH_PK_V1_OFFSET_FNGR_NUM];
	अगर (!fingers)
		जाओ irq_निकास;

	क्रम (i = 0; i < WDT_MAX_FINGER; i++)
		wdt87xx_report_contact(wdt->input,
				       &wdt->param,
				       &raw_buf[TOUCH_PK_V1_OFFSET_EVENT +
						i * FINGER_EV_V1_SIZE]);

	input_mt_sync_frame(wdt->input);
	input_sync(wdt->input);

irq_निकास:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wdt87xx_ts_create_input_device(काष्ठा wdt87xx_data *wdt)
अणु
	काष्ठा device *dev = &wdt->client->dev;
	काष्ठा input_dev *input;
	अचिन्हित पूर्णांक res = DIV_ROUND_CLOSEST(MAX_UNIT_AXIS, wdt->param.phy_w);
	पूर्णांक error;

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण
	wdt->input = input;

	input->name = "WDT87xx Touchscreen";
	input->id.bustype = BUS_I2C;
	input->id.venकरोr = wdt->param.venकरोr_id;
	input->id.product = wdt->param.product_id;
	input->phys = wdt->phys;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0,
			     wdt->param.max_x, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0,
			     wdt->param.max_y, 0, 0);
	input_असल_set_res(input, ABS_MT_POSITION_X, res);
	input_असल_set_res(input, ABS_MT_POSITION_Y, res);

	input_set_असल_params(input, ABS_MT_TOUCH_MAJOR,
			     0, wdt->param.max_x, 0, 0);
	input_set_असल_params(input, ABS_MT_PRESSURE, 0, 0xFF, 0, 0);

	input_mt_init_slots(input, WDT_MAX_FINGER,
			    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wdt87xx_ts_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wdt87xx_data *wdt;
	पूर्णांक error;

	dev_dbg(&client->dev, "adapter=%d, client irq: %d\n",
		client->adapter->nr, client->irq);

	/* Check अगर the I2C function is ok in this adaptor */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENXIO;

	wdt = devm_kzalloc(&client->dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->client = client;
	mutex_init(&wdt->fw_mutex);
	i2c_set_clientdata(client, wdt);

	snम_लिखो(wdt->phys, माप(wdt->phys), "i2c-%u-%04x/input0",
		 client->adapter->nr, client->addr);

	error = wdt87xx_get_sysparam(client, &wdt->param);
	अगर (error)
		वापस error;

	error = wdt87xx_ts_create_input_device(wdt);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, wdt87xx_ts_पूर्णांकerrupt,
					  IRQF_ONESHOT,
					  client->name, wdt);
	अगर (error) अणु
		dev_err(&client->dev, "request irq failed: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_device_add_group(&client->dev, &wdt87xx_attr_group);
	अगर (error) अणु
		dev_err(&client->dev, "create sysfs failed: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused wdt87xx_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक error;

	disable_irq(client->irq);

	error = wdt87xx_send_command(client, VND_CMD_STOP, MODE_IDLE);
	अगर (error) अणु
		enable_irq(client->irq);
		dev_err(&client->dev,
			"failed to stop device when suspending: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused wdt87xx_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक error;

	/*
	 * The chip may have been reset जबतक प्रणाली is resuming,
	 * give it some समय to settle.
	 */
	msleep(100);

	error = wdt87xx_send_command(client, VND_CMD_START, 0);
	अगर (error)
		dev_err(&client->dev,
			"failed to start device when resuming: %d\n",
			error);

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(wdt87xx_pm_ops, wdt87xx_suspend, wdt87xx_resume);

अटल स्थिर काष्ठा i2c_device_id wdt87xx_dev_id[] = अणु
	अणु WDT87XX_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wdt87xx_dev_id);

अटल स्थिर काष्ठा acpi_device_id wdt87xx_acpi_id[] = अणु
	अणु "WDHT0001", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, wdt87xx_acpi_id);

अटल काष्ठा i2c_driver wdt87xx_driver = अणु
	.probe		= wdt87xx_ts_probe,
	.id_table	= wdt87xx_dev_id,
	.driver	= अणु
		.name	= WDT87XX_NAME,
		.pm     = &wdt87xx_pm_ops,
		.acpi_match_table = ACPI_PTR(wdt87xx_acpi_id),
	पूर्ण,
पूर्ण;
module_i2c_driver(wdt87xx_driver);

MODULE_AUTHOR("HN Chen <hn.chen@weidahitech.com>");
MODULE_DESCRIPTION("WeidaHiTech WDT87XX Touchscreen driver");
MODULE_LICENSE("GPL");

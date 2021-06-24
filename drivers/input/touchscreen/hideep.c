<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2017 Hideep, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा HIDEEP_TS_NAME			"HiDeep Touchscreen"
#घोषणा HIDEEP_I2C_NAME			"hideep_ts"

#घोषणा HIDEEP_MT_MAX			10
#घोषणा HIDEEP_KEY_MAX			3

/* count(2) + touch data(100) + key data(6) */
#घोषणा HIDEEP_MAX_EVENT		108UL

#घोषणा HIDEEP_TOUCH_EVENT_INDEX	2
#घोषणा HIDEEP_KEY_EVENT_INDEX		102

/* Touch & key event */
#घोषणा HIDEEP_EVENT_ADDR		0x240

/* command list */
#घोषणा HIDEEP_RESET_CMD		0x9800

/* event bit */
#घोषणा HIDEEP_MT_RELEASED		BIT(4)
#घोषणा HIDEEP_KEY_PRESSED		BIT(7)
#घोषणा HIDEEP_KEY_FIRST_PRESSED	BIT(8)
#घोषणा HIDEEP_KEY_PRESSED_MASK		(HIDEEP_KEY_PRESSED | \
					 HIDEEP_KEY_FIRST_PRESSED)

#घोषणा HIDEEP_KEY_IDX_MASK		0x0f

/* For NVM */
#घोषणा HIDEEP_YRAM_BASE		0x40000000
#घोषणा HIDEEP_PERIPHERAL_BASE		0x50000000
#घोषणा HIDEEP_ESI_BASE			(HIDEEP_PERIPHERAL_BASE + 0x00000000)
#घोषणा HIDEEP_FLASH_BASE		(HIDEEP_PERIPHERAL_BASE + 0x01000000)
#घोषणा HIDEEP_SYSCON_BASE		(HIDEEP_PERIPHERAL_BASE + 0x02000000)

#घोषणा HIDEEP_SYSCON_MOD_CON		(HIDEEP_SYSCON_BASE + 0x0000)
#घोषणा HIDEEP_SYSCON_SPC_CON		(HIDEEP_SYSCON_BASE + 0x0004)
#घोषणा HIDEEP_SYSCON_CLK_CON		(HIDEEP_SYSCON_BASE + 0x0008)
#घोषणा HIDEEP_SYSCON_CLK_ENA		(HIDEEP_SYSCON_BASE + 0x000C)
#घोषणा HIDEEP_SYSCON_RST_CON		(HIDEEP_SYSCON_BASE + 0x0010)
#घोषणा HIDEEP_SYSCON_WDT_CON		(HIDEEP_SYSCON_BASE + 0x0014)
#घोषणा HIDEEP_SYSCON_WDT_CNT		(HIDEEP_SYSCON_BASE + 0x0018)
#घोषणा HIDEEP_SYSCON_PWR_CON		(HIDEEP_SYSCON_BASE + 0x0020)
#घोषणा HIDEEP_SYSCON_PGM_ID		(HIDEEP_SYSCON_BASE + 0x00F4)

#घोषणा HIDEEP_FLASH_CON		(HIDEEP_FLASH_BASE + 0x0000)
#घोषणा HIDEEP_FLASH_STA		(HIDEEP_FLASH_BASE + 0x0004)
#घोषणा HIDEEP_FLASH_CFG		(HIDEEP_FLASH_BASE + 0x0008)
#घोषणा HIDEEP_FLASH_TIM		(HIDEEP_FLASH_BASE + 0x000C)
#घोषणा HIDEEP_FLASH_CACHE_CFG		(HIDEEP_FLASH_BASE + 0x0010)
#घोषणा HIDEEP_FLASH_PIO_SIG		(HIDEEP_FLASH_BASE + 0x400000)

#घोषणा HIDEEP_ESI_TX_INVALID		(HIDEEP_ESI_BASE + 0x0008)

#घोषणा HIDEEP_PERASE			0x00040000
#घोषणा HIDEEP_WRONLY			0x00100000

#घोषणा HIDEEP_NVM_MASK_OFS		0x0000000C
#घोषणा HIDEEP_NVM_DEFAULT_PAGE		0
#घोषणा HIDEEP_NVM_SFR_WPAGE		1
#घोषणा HIDEEP_NVM_SFR_RPAGE		2

#घोषणा HIDEEP_PIO_SIG			0x00400000
#घोषणा HIDEEP_PROT_MODE		0x03400000

#घोषणा HIDEEP_NVM_PAGE_SIZE		128

#घोषणा HIDEEP_DWZ_INFO			0x000002C0

काष्ठा hideep_event अणु
	__le16 x;
	__le16 y;
	__le16 z;
	u8 w;
	u8 flag;
	u8 type;
	u8 index;
पूर्ण;

काष्ठा dwz_info अणु
	__be32 code_start;
	u8 code_crc[12];

	__be32 c_code_start;
	__be16 gen_ver;
	__be16 c_code_len;

	__be32 vr_start;
	__be16 rsv0;
	__be16 vr_len;

	__be32 ft_start;
	__be16 vr_version;
	__be16 ft_len;

	__be16 core_ver;
	__be16 boot_ver;

	__be16 release_ver;
	__be16 custom_ver;

	u8 factory_id;
	u8 panel_type;
	u8 model_name[6];

	__be16 extra_option;
	__be16 product_code;

	__be16 venकरोr_id;
	__be16 product_id;
पूर्ण;

काष्ठा pgm_packet अणु
	काष्ठा अणु
		u8 unused[3];
		u8 len;
		__be32 addr;
	पूर्ण header;
	__be32 payload[HIDEEP_NVM_PAGE_SIZE / माप(__be32)];
पूर्ण;

#घोषणा HIDEEP_XFER_BUF_SIZE	माप(काष्ठा pgm_packet)

काष्ठा hideep_ts अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	काष्ठा regmap *reg;

	काष्ठा touchscreen_properties prop;

	काष्ठा gpio_desc *reset_gpio;

	काष्ठा regulator *vcc_vdd;
	काष्ठा regulator *vcc_vid;

	काष्ठा mutex dev_mutex;

	u32 tch_count;
	u32 lpm_count;

	/*
	 * Data buffer to पढ़ो packet from the device (contacts and key
	 * states). We align it on द्विगुन-word boundary to keep word-sized
	 * fields in contact data and द्विगुन-word-sized fields in program
	 * packet aligned.
	 */
	u8 xfer_buf[HIDEEP_XFER_BUF_SIZE] __aligned(4);

	पूर्णांक key_num;
	u32 key_codes[HIDEEP_KEY_MAX];

	काष्ठा dwz_info dwz_info;

	अचिन्हित पूर्णांक fw_size;
	u32 nvm_mask;
पूर्ण;

अटल पूर्णांक hideep_pgm_w_mem(काष्ठा hideep_ts *ts, u32 addr,
			    स्थिर __be32 *data, माप_प्रकार count)
अणु
	काष्ठा pgm_packet *packet = (व्योम *)ts->xfer_buf;
	माप_प्रकार len = count * माप(*data);
	काष्ठा i2c_msg msg = अणु
		.addr	= ts->client->addr,
		.len	= len + माप(packet->header.len) +
				माप(packet->header.addr),
		.buf	= &packet->header.len,
	पूर्ण;
	पूर्णांक ret;

	अगर (len > HIDEEP_NVM_PAGE_SIZE)
		वापस -EINVAL;

	packet->header.len = 0x80 | (count - 1);
	packet->header.addr = cpu_to_be32(addr);
	स_नकल(packet->payload, data, len);

	ret = i2c_transfer(ts->client->adapter, &msg, 1);
	अगर (ret != 1)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक hideep_pgm_r_mem(काष्ठा hideep_ts *ts, u32 addr,
			    __be32 *data, माप_प्रकार count)
अणु
	काष्ठा pgm_packet *packet = (व्योम *)ts->xfer_buf;
	माप_प्रकार len = count * माप(*data);
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= ts->client->addr,
			.len	= माप(packet->header.len) +
					माप(packet->header.addr),
			.buf	= &packet->header.len,
		पूर्ण,
		अणु
			.addr	= ts->client->addr,
			.flags	= I2C_M_RD,
			.len	= len,
			.buf	= (u8 *)data,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	अगर (len > HIDEEP_NVM_PAGE_SIZE)
		वापस -EINVAL;

	packet->header.len = count - 1;
	packet->header.addr = cpu_to_be32(addr);

	ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
	अगर (ret != ARRAY_SIZE(msg))
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक hideep_pgm_r_reg(काष्ठा hideep_ts *ts, u32 addr, u32 *val)
अणु
	__be32 data;
	पूर्णांक error;

	error = hideep_pgm_r_mem(ts, addr, &data, 1);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"read of register %#08x failed: %d\n",
			addr, error);
		वापस error;
	पूर्ण

	*val = be32_to_cpu(data);
	वापस 0;
पूर्ण

अटल पूर्णांक hideep_pgm_w_reg(काष्ठा hideep_ts *ts, u32 addr, u32 val)
अणु
	__be32 data = cpu_to_be32(val);
	पूर्णांक error;

	error = hideep_pgm_w_mem(ts, addr, &data, 1);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"write to register %#08x (%#08x) failed: %d\n",
			addr, val, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SW_RESET_IN_PGM(clk)					\
अणु								\
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_WDT_CNT, (clk));	\
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_WDT_CON, 0x03);	\
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_WDT_CON, 0x01);	\
पूर्ण

#घोषणा SET_FLASH_PIO(ce)					\
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CON,			\
			 0x01 | ((ce) << 1))

#घोषणा SET_PIO_SIG(x, y)					\
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_PIO_SIG + (x), (y))

#घोषणा SET_FLASH_HWCONTROL()					\
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CON, 0x00)

#घोषणा NVM_W_SFR(x, y)						\
अणु								\
	SET_FLASH_PIO(1);					\
	SET_PIO_SIG(x, y);					\
	SET_FLASH_PIO(0);					\
पूर्ण

अटल व्योम hideep_pgm_set(काष्ठा hideep_ts *ts)
अणु
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_WDT_CON, 0x00);
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_SPC_CON, 0x00);
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_CLK_ENA, 0xFF);
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_CLK_CON, 0x01);
	hideep_pgm_w_reg(ts, HIDEEP_SYSCON_PWR_CON, 0x01);
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_TIM, 0x03);
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CACHE_CFG, 0x00);
पूर्ण

अटल पूर्णांक hideep_pgm_get_pattern(काष्ठा hideep_ts *ts, u32 *pattern)
अणु
	u16 p1 = 0xAF39;
	u16 p2 = 0xDF9D;
	पूर्णांक error;

	error = regmap_bulk_ग_लिखो(ts->reg, p1, &p2, 1);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"%s: regmap_bulk_write() failed with %d\n",
			__func__, error);
		वापस error;
	पूर्ण

	usleep_range(1000, 1100);

	/* flush invalid Tx load रेजिस्टर */
	error = hideep_pgm_w_reg(ts, HIDEEP_ESI_TX_INVALID, 0x01);
	अगर (error)
		वापस error;

	error = hideep_pgm_r_reg(ts, HIDEEP_SYSCON_PGM_ID, pattern);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक hideep_enter_pgm(काष्ठा hideep_ts *ts)
अणु
	पूर्णांक retry_count = 10;
	u32 pattern;
	पूर्णांक error;

	जबतक (retry_count--) अणु
		error = hideep_pgm_get_pattern(ts, &pattern);
		अगर (error) अणु
			dev_err(&ts->client->dev,
				"hideep_pgm_get_pattern failed: %d\n", error);
		पूर्ण अन्यथा अगर (pattern != 0x39AF9DDF) अणु
			dev_err(&ts->client->dev, "%s: bad pattern: %#08x\n",
				__func__, pattern);
		पूर्ण अन्यथा अणु
			dev_dbg(&ts->client->dev, "found magic code");

			hideep_pgm_set(ts);
			usleep_range(1000, 1100);

			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(&ts->client->dev, "failed to  enter pgm mode\n");
	SW_RESET_IN_PGM(1000);
	वापस -EIO;
पूर्ण

अटल व्योम hideep_nvm_unlock(काष्ठा hideep_ts *ts)
अणु
	u32 unmask_code;

	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CFG, HIDEEP_NVM_SFR_RPAGE);
	hideep_pgm_r_reg(ts, 0x0000000C, &unmask_code);
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CFG, HIDEEP_NVM_DEFAULT_PAGE);

	/* make it unरक्षित code */
	unmask_code &= ~HIDEEP_PROT_MODE;

	/* compare unmask code */
	अगर (unmask_code != ts->nvm_mask)
		dev_warn(&ts->client->dev,
			 "read mask code different %#08x vs %#08x",
			 unmask_code, ts->nvm_mask);

	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CFG, HIDEEP_NVM_SFR_WPAGE);
	SET_FLASH_PIO(0);

	NVM_W_SFR(HIDEEP_NVM_MASK_OFS, ts->nvm_mask);
	SET_FLASH_HWCONTROL();
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CFG, HIDEEP_NVM_DEFAULT_PAGE);
पूर्ण

अटल पूर्णांक hideep_check_status(काष्ठा hideep_ts *ts)
अणु
	पूर्णांक समय_out = 100;
	पूर्णांक status;
	पूर्णांक error;

	जबतक (समय_out--) अणु
		error = hideep_pgm_r_reg(ts, HIDEEP_FLASH_STA, &status);
		अगर (!error && status)
			वापस 0;

		usleep_range(1000, 1100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक hideep_program_page(काष्ठा hideep_ts *ts, u32 addr,
			       स्थिर __be32 *ucode, माप_प्रकार xfer_count)
अणु
	u32 val;
	पूर्णांक error;

	error = hideep_check_status(ts);
	अगर (error)
		वापस -EBUSY;

	addr &= ~(HIDEEP_NVM_PAGE_SIZE - 1);

	SET_FLASH_PIO(0);
	SET_FLASH_PIO(1);

	/* erase page */
	SET_PIO_SIG(HIDEEP_PERASE | addr, 0xFFFFFFFF);

	SET_FLASH_PIO(0);

	error = hideep_check_status(ts);
	अगर (error)
		वापस -EBUSY;

	/* ग_लिखो page */
	SET_FLASH_PIO(1);

	val = be32_to_cpu(ucode[0]);
	SET_PIO_SIG(HIDEEP_WRONLY | addr, val);

	hideep_pgm_w_mem(ts, HIDEEP_FLASH_PIO_SIG | HIDEEP_WRONLY,
			 ucode, xfer_count);

	val = be32_to_cpu(ucode[xfer_count - 1]);
	SET_PIO_SIG(124, val);

	SET_FLASH_PIO(0);

	usleep_range(1000, 1100);

	error = hideep_check_status(ts);
	अगर (error)
		वापस -EBUSY;

	SET_FLASH_HWCONTROL();

	वापस 0;
पूर्ण

अटल पूर्णांक hideep_program_nvm(काष्ठा hideep_ts *ts,
			      स्थिर __be32 *ucode, माप_प्रकार ucode_len)
अणु
	काष्ठा pgm_packet *packet_r = (व्योम *)ts->xfer_buf;
	__be32 *current_ucode = packet_r->payload;
	माप_प्रकार xfer_len;
	माप_प्रकार xfer_count;
	u32 addr = 0;
	पूर्णांक error;

	hideep_nvm_unlock(ts);

	जबतक (ucode_len > 0) अणु
		xfer_len = min_t(माप_प्रकार, ucode_len, HIDEEP_NVM_PAGE_SIZE);
		xfer_count = xfer_len / माप(*ucode);

		error = hideep_pgm_r_mem(ts, 0x00000000 + addr,
					 current_ucode, xfer_count);
		अगर (error) अणु
			dev_err(&ts->client->dev,
				"%s: failed to read page at offset %#08x: %d\n",
				__func__, addr, error);
			वापस error;
		पूर्ण

		/* See अगर the page needs updating */
		अगर (स_भेद(ucode, current_ucode, xfer_len)) अणु
			error = hideep_program_page(ts, addr,
						    ucode, xfer_count);
			अगर (error) अणु
				dev_err(&ts->client->dev,
					"%s: iwrite failure @%#08x: %d\n",
					__func__, addr, error);
				वापस error;
			पूर्ण

			usleep_range(1000, 1100);
		पूर्ण

		ucode += xfer_count;
		addr += xfer_len;
		ucode_len -= xfer_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hideep_verअगरy_nvm(काष्ठा hideep_ts *ts,
			     स्थिर __be32 *ucode, माप_प्रकार ucode_len)
अणु
	काष्ठा pgm_packet *packet_r = (व्योम *)ts->xfer_buf;
	__be32 *current_ucode = packet_r->payload;
	माप_प्रकार xfer_len;
	माप_प्रकार xfer_count;
	u32 addr = 0;
	पूर्णांक i;
	पूर्णांक error;

	जबतक (ucode_len > 0) अणु
		xfer_len = min_t(माप_प्रकार, ucode_len, HIDEEP_NVM_PAGE_SIZE);
		xfer_count = xfer_len / माप(*ucode);

		error = hideep_pgm_r_mem(ts, 0x00000000 + addr,
					 current_ucode, xfer_count);
		अगर (error) अणु
			dev_err(&ts->client->dev,
				"%s: failed to read page at offset %#08x: %d\n",
				__func__, addr, error);
			वापस error;
		पूर्ण

		अगर (स_भेद(ucode, current_ucode, xfer_len)) अणु
			स्थिर u8 *ucode_bytes = (स्थिर u8 *)ucode;
			स्थिर u8 *current_bytes = (स्थिर u8 *)current_ucode;

			क्रम (i = 0; i < xfer_len; i++)
				अगर (ucode_bytes[i] != current_bytes[i])
					dev_err(&ts->client->dev,
						"%s: mismatch @%#08x: (%#02x vs %#02x)\n",
						__func__, addr + i,
						ucode_bytes[i],
						current_bytes[i]);

			वापस -EIO;
		पूर्ण

		ucode += xfer_count;
		addr += xfer_len;
		ucode_len -= xfer_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hideep_load_dwz(काष्ठा hideep_ts *ts)
अणु
	u16 product_code;
	पूर्णांक error;

	error = hideep_enter_pgm(ts);
	अगर (error)
		वापस error;

	msleep(50);

	error = hideep_pgm_r_mem(ts, HIDEEP_DWZ_INFO,
				 (व्योम *)&ts->dwz_info,
				 माप(ts->dwz_info) / माप(__be32));

	SW_RESET_IN_PGM(10);
	msleep(50);

	अगर (error) अणु
		dev_err(&ts->client->dev,
			"failed to fetch DWZ data: %d\n", error);
		वापस error;
	पूर्ण

	product_code = be16_to_cpu(ts->dwz_info.product_code);

	चयन (product_code & 0xF0) अणु
	हाल 0x40:
		dev_dbg(&ts->client->dev, "used crimson IC");
		ts->fw_size = 1024 * 48;
		ts->nvm_mask = 0x00310000;
		अवरोध;
	हाल 0x60:
		dev_dbg(&ts->client->dev, "used lime IC");
		ts->fw_size = 1024 * 64;
		ts->nvm_mask = 0x0030027B;
		अवरोध;
	शेष:
		dev_err(&ts->client->dev, "product code is wrong: %#04x",
			product_code);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&ts->client->dev, "firmware release version: %#04x",
		be16_to_cpu(ts->dwz_info.release_ver));

	वापस 0;
पूर्ण

अटल पूर्णांक hideep_flash_firmware(काष्ठा hideep_ts *ts,
				 स्थिर __be32 *ucode, माप_प्रकार ucode_len)
अणु
	पूर्णांक retry_cnt = 3;
	पूर्णांक error;

	जबतक (retry_cnt--) अणु
		error = hideep_program_nvm(ts, ucode, ucode_len);
		अगर (!error) अणु
			error = hideep_verअगरy_nvm(ts, ucode, ucode_len);
			अगर (!error)
				वापस 0;
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक hideep_update_firmware(काष्ठा hideep_ts *ts,
				  स्थिर __be32 *ucode, माप_प्रकार ucode_len)
अणु
	पूर्णांक error, error2;

	dev_dbg(&ts->client->dev, "starting firmware update");

	/* enter program mode */
	error = hideep_enter_pgm(ts);
	अगर (error)
		वापस error;

	error = hideep_flash_firmware(ts, ucode, ucode_len);
	अगर (error)
		dev_err(&ts->client->dev,
			"firmware update failed: %d\n", error);
	अन्यथा
		dev_dbg(&ts->client->dev, "firmware updated successfully\n");

	SW_RESET_IN_PGM(1000);

	error2 = hideep_load_dwz(ts);
	अगर (error2)
		dev_err(&ts->client->dev,
			"failed to load dwz after firmware update: %d\n",
			error2);

	वापस error ?: error2;
पूर्ण

अटल पूर्णांक hideep_घातer_on(काष्ठा hideep_ts *ts)
अणु
	पूर्णांक error = 0;

	error = regulator_enable(ts->vcc_vdd);
	अगर (error)
		dev_err(&ts->client->dev,
			"failed to enable 'vdd' regulator: %d", error);

	usleep_range(999, 1000);

	error = regulator_enable(ts->vcc_vid);
	अगर (error)
		dev_err(&ts->client->dev,
			"failed to enable 'vcc_vid' regulator: %d",
			error);

	msleep(30);

	अगर (ts->reset_gpio) अणु
		gpiod_set_value_cansleep(ts->reset_gpio, 0);
	पूर्ण अन्यथा अणु
		error = regmap_ग_लिखो(ts->reg, HIDEEP_RESET_CMD, 0x01);
		अगर (error)
			dev_err(&ts->client->dev,
				"failed to send 'reset' command: %d\n", error);
	पूर्ण

	msleep(50);

	वापस error;
पूर्ण

अटल व्योम hideep_घातer_off(व्योम *data)
अणु
	काष्ठा hideep_ts *ts = data;

	अगर (ts->reset_gpio)
		gpiod_set_value(ts->reset_gpio, 1);

	regulator_disable(ts->vcc_vid);
	regulator_disable(ts->vcc_vdd);
पूर्ण

#घोषणा __GET_MT_TOOL_TYPE(type) ((type) == 0x01 ? MT_TOOL_FINGER : MT_TOOL_PEN)

अटल व्योम hideep_report_slot(काष्ठा input_dev *input,
			       स्थिर काष्ठा hideep_event *event)
अणु
	input_mt_slot(input, event->index & 0x0f);
	input_mt_report_slot_state(input,
				   __GET_MT_TOOL_TYPE(event->type),
				   !(event->flag & HIDEEP_MT_RELEASED));
	अगर (!(event->flag & HIDEEP_MT_RELEASED)) अणु
		input_report_असल(input, ABS_MT_POSITION_X,
				 le16_to_cpup(&event->x));
		input_report_असल(input, ABS_MT_POSITION_Y,
				 le16_to_cpup(&event->y));
		input_report_असल(input, ABS_MT_PRESSURE,
				 le16_to_cpup(&event->z));
		input_report_असल(input, ABS_MT_TOUCH_MAJOR, event->w);
	पूर्ण
पूर्ण

अटल व्योम hideep_parse_and_report(काष्ठा hideep_ts *ts)
अणु
	स्थिर काष्ठा hideep_event *events =
			(व्योम *)&ts->xfer_buf[HIDEEP_TOUCH_EVENT_INDEX];
	स्थिर u8 *keys = &ts->xfer_buf[HIDEEP_KEY_EVENT_INDEX];
	पूर्णांक touch_count = ts->xfer_buf[0];
	पूर्णांक key_count = ts->xfer_buf[1] & 0x0f;
	पूर्णांक lpm_count = ts->xfer_buf[1] & 0xf0;
	पूर्णांक i;

	/* get touch event count */
	dev_dbg(&ts->client->dev, "mt = %d, key = %d, lpm = %02x",
		touch_count, key_count, lpm_count);

	touch_count = min(touch_count, HIDEEP_MT_MAX);
	क्रम (i = 0; i < touch_count; i++)
		hideep_report_slot(ts->input_dev, events + i);

	key_count = min(key_count, HIDEEP_KEY_MAX);
	क्रम (i = 0; i < key_count; i++) अणु
		u8 key_data = keys[i * 2];

		input_report_key(ts->input_dev,
				 ts->key_codes[key_data & HIDEEP_KEY_IDX_MASK],
				 key_data & HIDEEP_KEY_PRESSED_MASK);
	पूर्ण

	input_mt_sync_frame(ts->input_dev);
	input_sync(ts->input_dev);
पूर्ण

अटल irqवापस_t hideep_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा hideep_ts *ts = handle;
	पूर्णांक error;

	BUILD_BUG_ON(HIDEEP_MAX_EVENT > HIDEEP_XFER_BUF_SIZE);

	error = regmap_bulk_पढ़ो(ts->reg, HIDEEP_EVENT_ADDR,
				 ts->xfer_buf, HIDEEP_MAX_EVENT / 2);
	अगर (error) अणु
		dev_err(&ts->client->dev, "failed to read events: %d\n", error);
		जाओ out;
	पूर्ण

	hideep_parse_and_report(ts);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hideep_get_axis_info(काष्ठा hideep_ts *ts)
अणु
	__le16 val[2];
	पूर्णांक error;

	error = regmap_bulk_पढ़ो(ts->reg, 0x28, val, ARRAY_SIZE(val));
	अगर (error)
		वापस error;

	ts->prop.max_x = le16_to_cpup(val);
	ts->prop.max_y = le16_to_cpup(val + 1);

	dev_dbg(&ts->client->dev, "X: %d, Y: %d",
		ts->prop.max_x, ts->prop.max_y);

	वापस 0;
पूर्ण

अटल पूर्णांक hideep_init_input(काष्ठा hideep_ts *ts)
अणु
	काष्ठा device *dev = &ts->client->dev;
	पूर्णांक i;
	पूर्णांक error;

	ts->input_dev = devm_input_allocate_device(dev);
	अगर (!ts->input_dev) अणु
		dev_err(dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	ts->input_dev->name = HIDEEP_TS_NAME;
	ts->input_dev->id.bustype = BUS_I2C;
	input_set_drvdata(ts->input_dev, ts);

	input_set_capability(ts->input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(ts->input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_असल_params(ts->input_dev, ABS_MT_PRESSURE, 0, 65535, 0, 0);
	input_set_असल_params(ts->input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_असल_params(ts->input_dev, ABS_MT_TOOL_TYPE,
			     0, MT_TOOL_MAX, 0, 0);
	touchscreen_parse_properties(ts->input_dev, true, &ts->prop);

	अगर (ts->prop.max_x == 0 || ts->prop.max_y == 0) अणु
		error = hideep_get_axis_info(ts);
		अगर (error)
			वापस error;
	पूर्ण

	error = input_mt_init_slots(ts->input_dev, HIDEEP_MT_MAX,
				    INPUT_MT_सूचीECT);
	अगर (error)
		वापस error;

	ts->key_num = device_property_count_u32(dev, "linux,keycodes");
	अगर (ts->key_num > HIDEEP_KEY_MAX) अणु
		dev_err(dev, "too many keys defined: %d\n",
			ts->key_num);
		वापस -EINVAL;
	पूर्ण

	अगर (ts->key_num <= 0) अणु
		dev_dbg(dev,
			"missing or malformed 'linux,keycodes' property\n");
	पूर्ण अन्यथा अणु
		error = device_property_पढ़ो_u32_array(dev, "linux,keycodes",
						       ts->key_codes,
						       ts->key_num);
		अगर (error) अणु
			dev_dbg(dev, "failed to read keymap: %d", error);
			वापस error;
		पूर्ण

		अगर (ts->key_num) अणु
			ts->input_dev->keycode = ts->key_codes;
			ts->input_dev->keycodesize = माप(ts->key_codes[0]);
			ts->input_dev->keycodemax = ts->key_num;

			क्रम (i = 0; i < ts->key_num; i++)
				input_set_capability(ts->input_dev, EV_KEY,
					ts->key_codes[i]);
		पूर्ण
	पूर्ण

	error = input_रेजिस्टर_device(ts->input_dev);
	अगर (error) अणु
		dev_err(dev, "failed to register input device: %d", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार hideep_update_fw(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा hideep_ts *ts = i2c_get_clientdata(client);
	स्थिर काष्ठा firmware *fw_entry;
	अक्षर *fw_name;
	पूर्णांक mode;
	पूर्णांक error;

	error = kstrtoपूर्णांक(buf, 0, &mode);
	अगर (error)
		वापस error;

	fw_name = kaप्र_लिखो(GFP_KERNEL, "hideep_ts_%04x.bin",
			    be16_to_cpu(ts->dwz_info.product_id));
	अगर (!fw_name)
		वापस -ENOMEM;

	error = request_firmware(&fw_entry, fw_name, dev);
	अगर (error) अणु
		dev_err(dev, "failed to request firmware %s: %d",
			fw_name, error);
		जाओ out_मुक्त_fw_name;
	पूर्ण

	अगर (fw_entry->size % माप(__be32)) अणु
		dev_err(dev, "invalid firmware size %zu\n", fw_entry->size);
		error = -EINVAL;
		जाओ out_release_fw;
	पूर्ण

	अगर (fw_entry->size > ts->fw_size) अणु
		dev_err(dev, "fw size (%zu) is too big (memory size %d)\n",
			fw_entry->size, ts->fw_size);
		error = -EFBIG;
		जाओ out_release_fw;
	पूर्ण

	mutex_lock(&ts->dev_mutex);
	disable_irq(client->irq);

	error = hideep_update_firmware(ts, (स्थिर __be32 *)fw_entry->data,
				       fw_entry->size);

	enable_irq(client->irq);
	mutex_unlock(&ts->dev_mutex);

out_release_fw:
	release_firmware(fw_entry);
out_मुक्त_fw_name:
	kमुक्त(fw_name);

	वापस error ?: count;
पूर्ण

अटल sमाप_प्रकार hideep_fw_version_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा hideep_ts *ts = i2c_get_clientdata(client);
	sमाप_प्रकार len;

	mutex_lock(&ts->dev_mutex);
	len = scnम_लिखो(buf, PAGE_SIZE, "%04x\n",
			be16_to_cpu(ts->dwz_info.release_ver));
	mutex_unlock(&ts->dev_mutex);

	वापस len;
पूर्ण

अटल sमाप_प्रकार hideep_product_id_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा hideep_ts *ts = i2c_get_clientdata(client);
	sमाप_प्रकार len;

	mutex_lock(&ts->dev_mutex);
	len = scnम_लिखो(buf, PAGE_SIZE, "%04x\n",
			be16_to_cpu(ts->dwz_info.product_id));
	mutex_unlock(&ts->dev_mutex);

	वापस len;
पूर्ण

अटल DEVICE_ATTR(version, 0664, hideep_fw_version_show, शून्य);
अटल DEVICE_ATTR(product_id, 0664, hideep_product_id_show, शून्य);
अटल DEVICE_ATTR(update_fw, 0664, शून्य, hideep_update_fw);

अटल काष्ठा attribute *hideep_ts_sysfs_entries[] = अणु
	&dev_attr_version.attr,
	&dev_attr_product_id.attr,
	&dev_attr_update_fw.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hideep_ts_attr_group = अणु
	.attrs = hideep_ts_sysfs_entries,
पूर्ण;

अटल पूर्णांक __maybe_unused hideep_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा hideep_ts *ts = i2c_get_clientdata(client);

	disable_irq(client->irq);
	hideep_घातer_off(ts);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hideep_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा hideep_ts *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	error = hideep_घातer_on(ts);
	अगर (error) अणु
		dev_err(&client->dev, "power on failed");
		वापस error;
	पूर्ण

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(hideep_pm_ops, hideep_suspend, hideep_resume);

अटल स्थिर काष्ठा regmap_config hideep_regmap_config = अणु
	.reg_bits = 16,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.val_bits = 16,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.max_रेजिस्टर = 0xffff,
पूर्ण;

अटल पूर्णांक hideep_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा hideep_ts *ts;
	पूर्णांक error;

	/* check i2c bus */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "check i2c device error");
		वापस -ENODEV;
	पूर्ण

	अगर (client->irq <= 0) अणु
		dev_err(&client->dev, "missing irq: %d\n", client->irq);
		वापस -EINVAL;
	पूर्ण

	ts = devm_kzalloc(&client->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->client = client;
	i2c_set_clientdata(client, ts);
	mutex_init(&ts->dev_mutex);

	ts->reg = devm_regmap_init_i2c(client, &hideep_regmap_config);
	अगर (IS_ERR(ts->reg)) अणु
		error = PTR_ERR(ts->reg);
		dev_err(&client->dev,
			"failed to initialize regmap: %d\n", error);
		वापस error;
	पूर्ण

	ts->vcc_vdd = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(ts->vcc_vdd))
		वापस PTR_ERR(ts->vcc_vdd);

	ts->vcc_vid = devm_regulator_get(&client->dev, "vid");
	अगर (IS_ERR(ts->vcc_vid))
		वापस PTR_ERR(ts->vcc_vid);

	ts->reset_gpio = devm_gpiod_get_optional(&client->dev,
						 "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts->reset_gpio))
		वापस PTR_ERR(ts->reset_gpio);

	error = hideep_घातer_on(ts);
	अगर (error) अणु
		dev_err(&client->dev, "power on failed: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev, hideep_घातer_off, ts);
	अगर (error)
		वापस error;

	error = hideep_load_dwz(ts);
	अगर (error) अणु
		dev_err(&client->dev, "failed to load dwz: %d", error);
		वापस error;
	पूर्ण

	error = hideep_init_input(ts);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, hideep_irq, IRQF_ONESHOT,
					  client->name, ts);
	अगर (error) अणु
		dev_err(&client->dev, "failed to request irq %d: %d\n",
			client->irq, error);
		वापस error;
	पूर्ण

	error = devm_device_add_group(&client->dev, &hideep_ts_attr_group);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to add sysfs attributes: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hideep_i2c_id[] = अणु
	अणु HIDEEP_I2C_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hideep_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id hideep_acpi_id[] = अणु
	अणु "HIDP0001", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hideep_acpi_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id hideep_match_table[] = अणु
	अणु .compatible = "hideep,hideep-ts" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hideep_match_table);
#पूर्ण_अगर

अटल काष्ठा i2c_driver hideep_driver = अणु
	.driver = अणु
		.name			= HIDEEP_I2C_NAME,
		.of_match_table		= of_match_ptr(hideep_match_table),
		.acpi_match_table	= ACPI_PTR(hideep_acpi_id),
		.pm			= &hideep_pm_ops,
	पूर्ण,
	.id_table	= hideep_i2c_id,
	.probe		= hideep_probe,
पूर्ण;

module_i2c_driver(hideep_driver);

MODULE_DESCRIPTION("Driver for HiDeep Touchscreen Controller");
MODULE_AUTHOR("anthony.kim@hideep.com");
MODULE_LICENSE("GPL v2");

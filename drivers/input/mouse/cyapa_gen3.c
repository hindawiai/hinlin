<शैली गुरु>
/*
 * Cypress APA trackpad with I2C पूर्णांकerface
 *
 * Author: Dudley Du <dudl@cypress.com>
 * Further cleanup and reकाष्ठाuring by:
 *   Daniel Kurtz <djkurtz@chromium.org>
 *   Benson Leung <bleung@chromium.org>
 *
 * Copyright (C) 2011-2015 Cypress Semiconductor, Inc.
 * Copyright (C) 2011-2012 Google, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "cyapa.h"


#घोषणा GEN3_MAX_FINGERS 5
#घोषणा GEN3_FINGER_NUM(x) (((x) >> 4) & 0x07)

#घोषणा BLK_HEAD_BYTES 32

/* Macro क्रम रेजिस्टर map group offset. */
#घोषणा PRODUCT_ID_SIZE  16
#घोषणा QUERY_DATA_SIZE  27
#घोषणा REG_PROTOCOL_GEN_QUERY_OFFSET  20

#घोषणा REG_OFFSET_DATA_BASE     0x0000
#घोषणा REG_OFFSET_COMMAND_BASE  0x0028
#घोषणा REG_OFFSET_QUERY_BASE    0x002a

#घोषणा CYAPA_OFFSET_SOFT_RESET  REG_OFFSET_COMMAND_BASE
#घोषणा OP_RECALIBRATION_MASK    0x80
#घोषणा OP_REPORT_BASELINE_MASK  0x40
#घोषणा REG_OFFSET_MAX_BASELINE  0x0026
#घोषणा REG_OFFSET_MIN_BASELINE  0x0027

#घोषणा REG_OFFSET_POWER_MODE (REG_OFFSET_COMMAND_BASE + 1)
#घोषणा SET_POWER_MODE_DELAY   10000  /* Unit: us */
#घोषणा SET_POWER_MODE_TRIES   5

#घोषणा GEN3_BL_CMD_CHECKSUM_SEED 0xff
#घोषणा GEN3_BL_CMD_INITIATE_BL   0x38
#घोषणा GEN3_BL_CMD_WRITE_BLOCK   0x39
#घोषणा GEN3_BL_CMD_VERIFY_BLOCK  0x3a
#घोषणा GEN3_BL_CMD_TERMINATE_BL  0x3b
#घोषणा GEN3_BL_CMD_LAUNCH_APP    0xa5

/*
 * CYAPA trackpad device states.
 * Used in रेजिस्टर 0x00, bit1-0, DeviceStatus field.
 * Other values indicate device is in an abnormal state and must be reset.
 */
#घोषणा CYAPA_DEV_NORMAL  0x03
#घोषणा CYAPA_DEV_BUSY    0x01

#घोषणा CYAPA_FW_BLOCK_SIZE	64
#घोषणा CYAPA_FW_READ_SIZE	16
#घोषणा CYAPA_FW_HDR_START	0x0780
#घोषणा CYAPA_FW_HDR_BLOCK_COUNT  2
#घोषणा CYAPA_FW_HDR_BLOCK_START  (CYAPA_FW_HDR_START / CYAPA_FW_BLOCK_SIZE)
#घोषणा CYAPA_FW_HDR_SIZE	  (CYAPA_FW_HDR_BLOCK_COUNT * \
					CYAPA_FW_BLOCK_SIZE)
#घोषणा CYAPA_FW_DATA_START	0x0800
#घोषणा CYAPA_FW_DATA_BLOCK_COUNT  480
#घोषणा CYAPA_FW_DATA_BLOCK_START  (CYAPA_FW_DATA_START / CYAPA_FW_BLOCK_SIZE)
#घोषणा CYAPA_FW_DATA_SIZE	(CYAPA_FW_DATA_BLOCK_COUNT * \
				 CYAPA_FW_BLOCK_SIZE)
#घोषणा CYAPA_FW_SIZE		(CYAPA_FW_HDR_SIZE + CYAPA_FW_DATA_SIZE)
#घोषणा CYAPA_CMD_LEN		16

#घोषणा GEN3_BL_IDLE_FW_MAJ_VER_OFFSET 0x0b
#घोषणा GEN3_BL_IDLE_FW_MIN_VER_OFFSET (GEN3_BL_IDLE_FW_MAJ_VER_OFFSET + 1)


काष्ठा cyapa_touch अणु
	/*
	 * high bits or x/y position value
	 * bit 7 - 4: high 4 bits of x position value
	 * bit 3 - 0: high 4 bits of y position value
	 */
	u8 xy_hi;
	u8 x_lo;  /* low 8 bits of x position value. */
	u8 y_lo;  /* low 8 bits of y position value. */
	u8 pressure;
	/* id range is 1 - 15.  It is incremented with every new touch. */
	u8 id;
पूर्ण __packed;

काष्ठा cyapa_reg_data अणु
	/*
	 * bit 0 - 1: device status
	 * bit 3 - 2: घातer mode
	 * bit 6 - 4: reserved
	 * bit 7: पूर्णांकerrupt valid bit
	 */
	u8 device_status;
	/*
	 * bit 7 - 4: number of fingers currently touching pad
	 * bit 3: valid data check bit
	 * bit 2: middle mechanism button state अगर exists
	 * bit 1: right mechanism button state अगर exists
	 * bit 0: left mechanism button state अगर exists
	 */
	u8 finger_btn;
	/* CYAPA reports up to 5 touches per packet. */
	काष्ठा cyapa_touch touches[5];
पूर्ण __packed;

काष्ठा gen3_ग_लिखो_block_cmd अणु
	u8 checksum_seed;  /* Always be 0xff */
	u8 cmd_code;       /* command code: 0x39 */
	u8 key[8];         /* 8-byte security key */
	__be16 block_num;
	u8 block_data[CYAPA_FW_BLOCK_SIZE];
	u8 block_checksum;  /* Calculated using bytes 12 - 75 */
	u8 cmd_checksum;    /* Calculated using bytes 0-76 */
पूर्ण __packed;

अटल स्थिर u8 security_key[] = अणु
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 पूर्ण;
अटल स्थिर u8 bl_activate[] = अणु 0x00, 0xff, 0x38, 0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07 पूर्ण;
अटल स्थिर u8 bl_deactivate[] = अणु 0x00, 0xff, 0x3b, 0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07 पूर्ण;
अटल स्थिर u8 bl_निकास[] = अणु 0x00, 0xff, 0xa5, 0x00, 0x01, 0x02, 0x03, 0x04,
		0x05, 0x06, 0x07 पूर्ण;


 /* क्रम byte पढ़ो/ग_लिखो command */
#घोषणा CMD_RESET 0
#घोषणा CMD_POWER_MODE 1
#घोषणा CMD_DEV_STATUS 2
#घोषणा CMD_REPORT_MAX_BASELINE 3
#घोषणा CMD_REPORT_MIN_BASELINE 4
#घोषणा SMBUS_BYTE_CMD(cmd) (((cmd) & 0x3f) << 1)
#घोषणा CYAPA_SMBUS_RESET         SMBUS_BYTE_CMD(CMD_RESET)
#घोषणा CYAPA_SMBUS_POWER_MODE    SMBUS_BYTE_CMD(CMD_POWER_MODE)
#घोषणा CYAPA_SMBUS_DEV_STATUS    SMBUS_BYTE_CMD(CMD_DEV_STATUS)
#घोषणा CYAPA_SMBUS_MAX_BASELINE  SMBUS_BYTE_CMD(CMD_REPORT_MAX_BASELINE)
#घोषणा CYAPA_SMBUS_MIN_BASELINE  SMBUS_BYTE_CMD(CMD_REPORT_MIN_BASELINE)

 /* क्रम group रेजिस्टरs पढ़ो/ग_लिखो command */
#घोषणा REG_GROUP_DATA  0
#घोषणा REG_GROUP_CMD   2
#घोषणा REG_GROUP_QUERY 3
#घोषणा SMBUS_GROUP_CMD(grp) (0x80 | (((grp) & 0x07) << 3))
#घोषणा CYAPA_SMBUS_GROUP_DATA  SMBUS_GROUP_CMD(REG_GROUP_DATA)
#घोषणा CYAPA_SMBUS_GROUP_CMD   SMBUS_GROUP_CMD(REG_GROUP_CMD)
#घोषणा CYAPA_SMBUS_GROUP_QUERY SMBUS_GROUP_CMD(REG_GROUP_QUERY)

 /* क्रम रेजिस्टर block पढ़ो/ग_लिखो command */
#घोषणा CMD_BL_STATUS		0
#घोषणा CMD_BL_HEAD		1
#घोषणा CMD_BL_CMD		2
#घोषणा CMD_BL_DATA		3
#घोषणा CMD_BL_ALL		4
#घोषणा CMD_BLK_PRODUCT_ID	5
#घोषणा CMD_BLK_HEAD		6
#घोषणा SMBUS_BLOCK_CMD(cmd) (0xc0 | (((cmd) & 0x1f) << 1))

/* रेजिस्टर block पढ़ो/ग_लिखो command in bootloader mode */
#घोषणा CYAPA_SMBUS_BL_STATUS SMBUS_BLOCK_CMD(CMD_BL_STATUS)
#घोषणा CYAPA_SMBUS_BL_HEAD   SMBUS_BLOCK_CMD(CMD_BL_HEAD)
#घोषणा CYAPA_SMBUS_BL_CMD    SMBUS_BLOCK_CMD(CMD_BL_CMD)
#घोषणा CYAPA_SMBUS_BL_DATA   SMBUS_BLOCK_CMD(CMD_BL_DATA)
#घोषणा CYAPA_SMBUS_BL_ALL    SMBUS_BLOCK_CMD(CMD_BL_ALL)

/* रेजिस्टर block पढ़ो/ग_लिखो command in operational mode */
#घोषणा CYAPA_SMBUS_BLK_PRODUCT_ID SMBUS_BLOCK_CMD(CMD_BLK_PRODUCT_ID)
#घोषणा CYAPA_SMBUS_BLK_HEAD       SMBUS_BLOCK_CMD(CMD_BLK_HEAD)

काष्ठा cyapa_cmd_len अणु
	u8 cmd;
	u8 len;
पूर्ण;

/* maps generic CYAPA_CMD_* code to the I2C equivalent */
अटल स्थिर काष्ठा cyapa_cmd_len cyapa_i2c_cmds[] = अणु
	अणु CYAPA_OFFSET_SOFT_RESET, 1 पूर्ण,		/* CYAPA_CMD_SOFT_RESET */
	अणु REG_OFFSET_COMMAND_BASE + 1, 1 पूर्ण,	/* CYAPA_CMD_POWER_MODE */
	अणु REG_OFFSET_DATA_BASE, 1 पूर्ण,		/* CYAPA_CMD_DEV_STATUS */
	अणु REG_OFFSET_DATA_BASE, माप(काष्ठा cyapa_reg_data) पूर्ण,
						/* CYAPA_CMD_GROUP_DATA */
	अणु REG_OFFSET_COMMAND_BASE, 0 पूर्ण,		/* CYAPA_CMD_GROUP_CMD */
	अणु REG_OFFSET_QUERY_BASE, QUERY_DATA_SIZE पूर्ण, /* CYAPA_CMD_GROUP_QUERY */
	अणु BL_HEAD_OFFSET, 3 पूर्ण,			/* CYAPA_CMD_BL_STATUS */
	अणु BL_HEAD_OFFSET, 16 पूर्ण,			/* CYAPA_CMD_BL_HEAD */
	अणु BL_HEAD_OFFSET, 16 पूर्ण,			/* CYAPA_CMD_BL_CMD */
	अणु BL_DATA_OFFSET, 16 पूर्ण,			/* CYAPA_CMD_BL_DATA */
	अणु BL_HEAD_OFFSET, 32 पूर्ण,			/* CYAPA_CMD_BL_ALL */
	अणु REG_OFFSET_QUERY_BASE, PRODUCT_ID_SIZE पूर्ण,
						/* CYAPA_CMD_BLK_PRODUCT_ID */
	अणु REG_OFFSET_DATA_BASE, 32 पूर्ण,		/* CYAPA_CMD_BLK_HEAD */
	अणु REG_OFFSET_MAX_BASELINE, 1 पूर्ण,		/* CYAPA_CMD_MAX_BASELINE */
	अणु REG_OFFSET_MIN_BASELINE, 1 पूर्ण,		/* CYAPA_CMD_MIN_BASELINE */
पूर्ण;

अटल स्थिर काष्ठा cyapa_cmd_len cyapa_smbus_cmds[] = अणु
	अणु CYAPA_SMBUS_RESET, 1 पूर्ण,		/* CYAPA_CMD_SOFT_RESET */
	अणु CYAPA_SMBUS_POWER_MODE, 1 पूर्ण,		/* CYAPA_CMD_POWER_MODE */
	अणु CYAPA_SMBUS_DEV_STATUS, 1 पूर्ण,		/* CYAPA_CMD_DEV_STATUS */
	अणु CYAPA_SMBUS_GROUP_DATA, माप(काष्ठा cyapa_reg_data) पूर्ण,
						/* CYAPA_CMD_GROUP_DATA */
	अणु CYAPA_SMBUS_GROUP_CMD, 2 पूर्ण,		/* CYAPA_CMD_GROUP_CMD */
	अणु CYAPA_SMBUS_GROUP_QUERY, QUERY_DATA_SIZE पूर्ण,
						/* CYAPA_CMD_GROUP_QUERY */
	अणु CYAPA_SMBUS_BL_STATUS, 3 पूर्ण,		/* CYAPA_CMD_BL_STATUS */
	अणु CYAPA_SMBUS_BL_HEAD, 16 पूर्ण,		/* CYAPA_CMD_BL_HEAD */
	अणु CYAPA_SMBUS_BL_CMD, 16 पूर्ण,		/* CYAPA_CMD_BL_CMD */
	अणु CYAPA_SMBUS_BL_DATA, 16 पूर्ण,		/* CYAPA_CMD_BL_DATA */
	अणु CYAPA_SMBUS_BL_ALL, 32 पूर्ण,		/* CYAPA_CMD_BL_ALL */
	अणु CYAPA_SMBUS_BLK_PRODUCT_ID, PRODUCT_ID_SIZE पूर्ण,
						/* CYAPA_CMD_BLK_PRODUCT_ID */
	अणु CYAPA_SMBUS_BLK_HEAD, 16 पूर्ण,		/* CYAPA_CMD_BLK_HEAD */
	अणु CYAPA_SMBUS_MAX_BASELINE, 1 पूर्ण,	/* CYAPA_CMD_MAX_BASELINE */
	अणु CYAPA_SMBUS_MIN_BASELINE, 1 पूर्ण,	/* CYAPA_CMD_MIN_BASELINE */
पूर्ण;

अटल पूर्णांक cyapa_gen3_try_poll_handler(काष्ठा cyapa *cyapa);

/*
 * cyapa_smbus_पढ़ो_block - perक्रमm smbus block पढ़ो command
 * @cyapa  - निजी data काष्ठाure of the driver
 * @cmd    - the properly encoded smbus command
 * @len    - expected length of smbus command result
 * @values - buffer to store smbus command result
 *
 * Returns negative त्रुटि_सं, अन्यथा the number of bytes written.
 *
 * Note:
 * In trackpad device, the memory block allocated क्रम I2C रेजिस्टर map
 * is 256 bytes, so the max पढ़ो block क्रम I2C bus is 256 bytes.
 */
sमाप_प्रकार cyapa_smbus_पढ़ो_block(काष्ठा cyapa *cyapa, u8 cmd, माप_प्रकार len,
				      u8 *values)
अणु
	sमाप_प्रकार ret;
	u8 index;
	u8 smbus_cmd;
	u8 *buf;
	काष्ठा i2c_client *client = cyapa->client;

	अगर (!(SMBUS_BYTE_BLOCK_CMD_MASK & cmd))
		वापस -EINVAL;

	अगर (SMBUS_GROUP_BLOCK_CMD_MASK & cmd) अणु
		/* पढ़ो specअगरic block रेजिस्टरs command. */
		smbus_cmd = SMBUS_ENCODE_RW(cmd, SMBUS_READ);
		ret = i2c_smbus_पढ़ो_block_data(client, smbus_cmd, values);
		जाओ out;
	पूर्ण

	ret = 0;
	क्रम (index = 0; index * I2C_SMBUS_BLOCK_MAX < len; index++) अणु
		smbus_cmd = SMBUS_ENCODE_IDX(cmd, index);
		smbus_cmd = SMBUS_ENCODE_RW(smbus_cmd, SMBUS_READ);
		buf = values + I2C_SMBUS_BLOCK_MAX * index;
		ret = i2c_smbus_पढ़ो_block_data(client, smbus_cmd, buf);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	वापस ret > 0 ? len : ret;
पूर्ण

अटल s32 cyapa_पढ़ो_byte(काष्ठा cyapa *cyapa, u8 cmd_idx)
अणु
	u8 cmd;

	अगर (cyapa->smbus) अणु
		cmd = cyapa_smbus_cmds[cmd_idx].cmd;
		cmd = SMBUS_ENCODE_RW(cmd, SMBUS_READ);
	पूर्ण अन्यथा अणु
		cmd = cyapa_i2c_cmds[cmd_idx].cmd;
	पूर्ण
	वापस i2c_smbus_पढ़ो_byte_data(cyapa->client, cmd);
पूर्ण

अटल s32 cyapa_ग_लिखो_byte(काष्ठा cyapa *cyapa, u8 cmd_idx, u8 value)
अणु
	u8 cmd;

	अगर (cyapa->smbus) अणु
		cmd = cyapa_smbus_cmds[cmd_idx].cmd;
		cmd = SMBUS_ENCODE_RW(cmd, SMBUS_WRITE);
	पूर्ण अन्यथा अणु
		cmd = cyapa_i2c_cmds[cmd_idx].cmd;
	पूर्ण
	वापस i2c_smbus_ग_लिखो_byte_data(cyapa->client, cmd, value);
पूर्ण

sमाप_प्रकार cyapa_i2c_reg_पढ़ो_block(काष्ठा cyapa *cyapa, u8 reg, माप_प्रकार len,
					u8 *values)
अणु
	वापस i2c_smbus_पढ़ो_i2c_block_data(cyapa->client, reg, len, values);
पूर्ण

अटल sमाप_प्रकार cyapa_i2c_reg_ग_लिखो_block(काष्ठा cyapa *cyapa, u8 reg,
					 माप_प्रकार len, स्थिर u8 *values)
अणु
	वापस i2c_smbus_ग_लिखो_i2c_block_data(cyapa->client, reg, len, values);
पूर्ण

sमाप_प्रकार cyapa_पढ़ो_block(काष्ठा cyapa *cyapa, u8 cmd_idx, u8 *values)
अणु
	u8 cmd;
	माप_प्रकार len;

	अगर (cyapa->smbus) अणु
		cmd = cyapa_smbus_cmds[cmd_idx].cmd;
		len = cyapa_smbus_cmds[cmd_idx].len;
		वापस cyapa_smbus_पढ़ो_block(cyapa, cmd, len, values);
	पूर्ण
	cmd = cyapa_i2c_cmds[cmd_idx].cmd;
	len = cyapa_i2c_cmds[cmd_idx].len;
	वापस cyapa_i2c_reg_पढ़ो_block(cyapa, cmd, len, values);
पूर्ण

/*
 * Determine the Gen3 trackpad device's current operating state.
 *
 */
अटल पूर्णांक cyapa_gen3_state_parse(काष्ठा cyapa *cyapa, u8 *reg_data, पूर्णांक len)
अणु
	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Parse based on Gen3 अक्षरacteristic रेजिस्टरs and bits */
	अगर (reg_data[REG_BL_खाता] == BL_खाता &&
		reg_data[REG_BL_ERROR] == BL_ERROR_NO_ERR_IDLE &&
		(reg_data[REG_BL_STATUS] ==
			(BL_STATUS_RUNNING | BL_STATUS_CSUM_VALID) ||
			reg_data[REG_BL_STATUS] == BL_STATUS_RUNNING)) अणु
		/*
		 * Normal state after घातer on or reset,
		 * REG_BL_STATUS == 0x11, firmware image checksum is valid.
		 * REG_BL_STATUS == 0x10, firmware image checksum is invalid.
		 */
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_BL_IDLE;
	पूर्ण अन्यथा अगर (reg_data[REG_BL_खाता] == BL_खाता &&
		(reg_data[REG_BL_STATUS] & BL_STATUS_RUNNING) ==
			BL_STATUS_RUNNING) अणु
		cyapa->gen = CYAPA_GEN3;
		अगर (reg_data[REG_BL_STATUS] & BL_STATUS_BUSY) अणु
			cyapa->state = CYAPA_STATE_BL_BUSY;
		पूर्ण अन्यथा अणु
			अगर ((reg_data[REG_BL_ERROR] & BL_ERROR_BOOTLOADING) ==
					BL_ERROR_BOOTLOADING)
				cyapa->state = CYAPA_STATE_BL_ACTIVE;
			अन्यथा
				cyapa->state = CYAPA_STATE_BL_IDLE;
		पूर्ण
	पूर्ण अन्यथा अगर ((reg_data[REG_OP_STATUS] & OP_STATUS_SRC) &&
			(reg_data[REG_OP_DATA1] & OP_DATA_VALID)) अणु
		/*
		 * Normal state when running in operational mode,
		 * may also not in full घातer state or
		 * busying in command process.
		 */
		अगर (GEN3_FINGER_NUM(reg_data[REG_OP_DATA1]) <=
				GEN3_MAX_FINGERS) अणु
			/* Finger number data is valid. */
			cyapa->gen = CYAPA_GEN3;
			cyapa->state = CYAPA_STATE_OP;
		पूर्ण
	पूर्ण अन्यथा अगर (reg_data[REG_OP_STATUS] == 0x0C &&
			reg_data[REG_OP_DATA1] == 0x08) अणु
		/* Op state when first two रेजिस्टरs overwritten with 0x00 */
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_OP;
	पूर्ण अन्यथा अगर (reg_data[REG_BL_STATUS] &
			(BL_STATUS_RUNNING | BL_STATUS_BUSY)) अणु
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_BL_BUSY;
	पूर्ण

	अगर (cyapa->gen == CYAPA_GEN3 && (cyapa->state == CYAPA_STATE_OP ||
		cyapa->state == CYAPA_STATE_BL_IDLE ||
		cyapa->state == CYAPA_STATE_BL_ACTIVE ||
		cyapa->state == CYAPA_STATE_BL_BUSY))
		वापस 0;

	वापस -EAGAIN;
पूर्ण

/*
 * Enter bootloader by soft resetting the device.
 *
 * If device is alपढ़ोy in the bootloader, the function just वापसs.
 * Otherwise, reset the device; after reset, device enters bootloader idle
 * state immediately.
 *
 * Returns:
 *   0        on success
 *   -EAGAIN  device was reset, but is not now in bootloader idle state
 *   < 0      अगर the device never responds within the समयout
 */
अटल पूर्णांक cyapa_gen3_bl_enter(काष्ठा cyapa *cyapa)
अणु
	पूर्णांक error;
	पूर्णांक रुकोing_समय;

	error = cyapa_poll_state(cyapa, 500);
	अगर (error)
		वापस error;
	अगर (cyapa->state == CYAPA_STATE_BL_IDLE) अणु
		/* Alपढ़ोy in BL_IDLE. Skipping reset. */
		वापस 0;
	पूर्ण

	अगर (cyapa->state != CYAPA_STATE_OP)
		वापस -EAGAIN;

	cyapa->operational = false;
	cyapa->state = CYAPA_STATE_NO_DEVICE;
	error = cyapa_ग_लिखो_byte(cyapa, CYAPA_CMD_SOFT_RESET, 0x01);
	अगर (error)
		वापस -EIO;

	usleep_range(25000, 50000);
	रुकोing_समय = 2000;  /* For some shipset, max रुकोing समय is 1~2s. */
	करो अणु
		error = cyapa_poll_state(cyapa, 500);
		अगर (error) अणु
			अगर (error == -ETIMEDOUT) अणु
				रुकोing_समय -= 500;
				जारी;
			पूर्ण
			वापस error;
		पूर्ण

		अगर ((cyapa->state == CYAPA_STATE_BL_IDLE) &&
			!(cyapa->status[REG_BL_STATUS] & BL_STATUS_WATCHDOG))
			अवरोध;

		msleep(100);
		रुकोing_समय -= 100;
	पूर्ण जबतक (रुकोing_समय > 0);

	अगर ((cyapa->state != CYAPA_STATE_BL_IDLE) ||
		(cyapa->status[REG_BL_STATUS] & BL_STATUS_WATCHDOG))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen3_bl_activate(काष्ठा cyapa *cyapa)
अणु
	पूर्णांक error;

	error = cyapa_i2c_reg_ग_लिखो_block(cyapa, 0, माप(bl_activate),
					bl_activate);
	अगर (error)
		वापस error;

	/* Wait क्रम bootloader to activate; takes between 2 and 12 seconds */
	msleep(2000);
	error = cyapa_poll_state(cyapa, 11000);
	अगर (error)
		वापस error;
	अगर (cyapa->state != CYAPA_STATE_BL_ACTIVE)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen3_bl_deactivate(काष्ठा cyapa *cyapa)
अणु
	पूर्णांक error;

	error = cyapa_i2c_reg_ग_लिखो_block(cyapa, 0, माप(bl_deactivate),
					bl_deactivate);
	अगर (error)
		वापस error;

	/* Wait क्रम bootloader to चयन to idle state; should take < 100ms */
	msleep(100);
	error = cyapa_poll_state(cyapa, 500);
	अगर (error)
		वापस error;
	अगर (cyapa->state != CYAPA_STATE_BL_IDLE)
		वापस -EAGAIN;
	वापस 0;
पूर्ण

/*
 * Exit bootloader
 *
 * Send bl_निकास command, then रुको 50 - 100 ms to let device transition to
 * operational mode.  If this is the first समय the device's firmware is
 * running, it can take up to 2 seconds to calibrate its sensors.  So, poll
 * the device's new state क्रम up to 2 seconds.
 *
 * Returns:
 *   -EIO    failure जबतक पढ़ोing from device
 *   -EAGAIN device is stuck in bootloader, b/c it has invalid firmware
 *   0       device is supported and in operational mode
 */
अटल पूर्णांक cyapa_gen3_bl_निकास(काष्ठा cyapa *cyapa)
अणु
	पूर्णांक error;

	error = cyapa_i2c_reg_ग_लिखो_block(cyapa, 0, माप(bl_निकास), bl_निकास);
	अगर (error)
		वापस error;

	/*
	 * Wait क्रम bootloader to निकास, and operation mode to start.
	 * Normally, this takes at least 50 ms.
	 */
	msleep(50);
	/*
	 * In addition, when a device boots क्रम the first समय after being
	 * updated to new firmware, it must first calibrate its sensors, which
	 * can take up to an additional 2 seconds. If the device घातer is
	 * running low, this may take even दीर्घer.
	 */
	error = cyapa_poll_state(cyapa, 4000);
	अगर (error < 0)
		वापस error;
	अगर (cyapa->state != CYAPA_STATE_OP)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल u16 cyapa_gen3_csum(स्थिर u8 *buf, माप_प्रकार count)
अणु
	पूर्णांक i;
	u16 csum = 0;

	क्रम (i = 0; i < count; i++)
		csum += buf[i];

	वापस csum;
पूर्ण

/*
 * Verअगरy the पूर्णांकegrity of a CYAPA firmware image file.
 *
 * The firmware image file is 30848 bytes, composed of 482 64-byte blocks.
 *
 * The first 2 blocks are the firmware header.
 * The next 480 blocks are the firmware image.
 *
 * The first two bytes of the header hold the header checksum, computed by
 * summing the other 126 bytes of the header.
 * The last two bytes of the header hold the firmware image checksum, computed
 * by summing the 30720 bytes of the image modulo 0xffff.
 *
 * Both checksums are stored little-endian.
 */
अटल पूर्णांक cyapa_gen3_check_fw(काष्ठा cyapa *cyapa, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	u16 csum;
	u16 csum_expected;

	/* Firmware must match exact 30848 bytes = 482 64-byte blocks. */
	अगर (fw->size != CYAPA_FW_SIZE) अणु
		dev_err(dev, "invalid firmware size = %zu, expected %u.\n",
			fw->size, CYAPA_FW_SIZE);
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy header block */
	csum_expected = (fw->data[0] << 8) | fw->data[1];
	csum = cyapa_gen3_csum(&fw->data[2], CYAPA_FW_HDR_SIZE - 2);
	अगर (csum != csum_expected) अणु
		dev_err(dev, "%s %04x, expected: %04x\n",
			"invalid firmware header checksum = ",
			csum, csum_expected);
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy firmware image */
	csum_expected = (fw->data[CYAPA_FW_HDR_SIZE - 2] << 8) |
			 fw->data[CYAPA_FW_HDR_SIZE - 1];
	csum = cyapa_gen3_csum(&fw->data[CYAPA_FW_HDR_SIZE],
			CYAPA_FW_DATA_SIZE);
	अगर (csum != csum_expected) अणु
		dev_err(dev, "%s %04x, expected: %04x\n",
			"invalid firmware header checksum = ",
			csum, csum_expected);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Write a |len| byte दीर्घ buffer |buf| to the device, by chopping it up पूर्णांकo a
 * sequence of smaller |CYAPA_CMD_LEN|-length ग_लिखो commands.
 *
 * The data bytes क्रम a ग_लिखो command are prepended with the 1-byte offset
 * of the data relative to the start of |buf|.
 */
अटल पूर्णांक cyapa_gen3_ग_लिखो_buffer(काष्ठा cyapa *cyapa,
		स्थिर u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक error;
	माप_प्रकार i;
	अचिन्हित अक्षर cmd[CYAPA_CMD_LEN + 1];
	माप_प्रकार cmd_len;

	क्रम (i = 0; i < len; i += CYAPA_CMD_LEN) अणु
		स्थिर u8 *payload = &buf[i];

		cmd_len = (len - i >= CYAPA_CMD_LEN) ? CYAPA_CMD_LEN : len - i;
		cmd[0] = i;
		स_नकल(&cmd[1], payload, cmd_len);

		error = cyapa_i2c_reg_ग_लिखो_block(cyapa, 0, cmd_len + 1, cmd);
		अगर (error)
			वापस error;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * A firmware block ग_लिखो command ग_लिखोs 64 bytes of data to a single flash
 * page in the device.  The 78-byte block ग_लिखो command has the क्रमmat:
 *   <0xff> <CMD> <Key> <Start> <Data> <Data-Checksum> <CMD Checksum>
 *
 *  <0xff>  - every command starts with 0xff
 *  <CMD>   - the ग_लिखो command value is 0x39
 *  <Key>   - ग_लिखो commands include an 8-byte key: अणु 00 01 02 03 04 05 06 07 पूर्ण
 *  <Block> - Memory Block number (address / 64) (16-bit, big-endian)
 *  <Data>  - 64 bytes of firmware image data
 *  <Data Checksum> - sum of 64 <Data> bytes, modulo 0xff
 *  <CMD Checksum> - sum of 77 bytes, from 0xff to <Data Checksum>
 *
 * Each ग_लिखो command is split पूर्णांकo 5 i2c ग_लिखो transactions of up to 16 bytes.
 * Each transaction starts with an i2c रेजिस्टर offset: (00, 10, 20, 30, 40).
 */
अटल पूर्णांक cyapa_gen3_ग_लिखो_fw_block(काष्ठा cyapa *cyapa,
		u16 block, स्थिर u8 *data)
अणु
	पूर्णांक ret;
	काष्ठा gen3_ग_लिखो_block_cmd ग_लिखो_block_cmd;
	u8 status[BL_STATUS_SIZE];
	पूर्णांक tries;
	u8 bl_status, bl_error;

	/* Set ग_लिखो command and security key bytes. */
	ग_लिखो_block_cmd.checksum_seed = GEN3_BL_CMD_CHECKSUM_SEED;
	ग_लिखो_block_cmd.cmd_code = GEN3_BL_CMD_WRITE_BLOCK;
	स_नकल(ग_लिखो_block_cmd.key, security_key, माप(security_key));
	put_unaligned_be16(block, &ग_लिखो_block_cmd.block_num);
	स_नकल(ग_लिखो_block_cmd.block_data, data, CYAPA_FW_BLOCK_SIZE);
	ग_लिखो_block_cmd.block_checksum = cyapa_gen3_csum(
			ग_लिखो_block_cmd.block_data, CYAPA_FW_BLOCK_SIZE);
	ग_लिखो_block_cmd.cmd_checksum = cyapa_gen3_csum((u8 *)&ग_लिखो_block_cmd,
			माप(ग_लिखो_block_cmd) - 1);

	ret = cyapa_gen3_ग_लिखो_buffer(cyapa, (u8 *)&ग_लिखो_block_cmd,
			माप(ग_लिखो_block_cmd));
	अगर (ret)
		वापस ret;

	/* Wait क्रम ग_लिखो to finish */
	tries = 11;  /* Programming क्रम one block can take about 100ms. */
	करो अणु
		usleep_range(10000, 20000);

		/* Check block ग_लिखो command result status. */
		ret = cyapa_i2c_reg_पढ़ो_block(cyapa, BL_HEAD_OFFSET,
					       BL_STATUS_SIZE, status);
		अगर (ret != BL_STATUS_SIZE)
			वापस (ret < 0) ? ret : -EIO;
	पूर्ण जबतक ((status[REG_BL_STATUS] & BL_STATUS_BUSY) && --tries);

	/* Ignore WATCHDOG bit and reserved bits. */
	bl_status = status[REG_BL_STATUS] & ~BL_STATUS_REV_MASK;
	bl_error = status[REG_BL_ERROR] & ~BL_ERROR_RESERVED;

	अगर (bl_status & BL_STATUS_BUSY)
		ret = -ETIMEDOUT;
	अन्यथा अगर (bl_status != BL_STATUS_RUNNING ||
		bl_error != BL_ERROR_BOOTLOADING)
		ret = -EIO;
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक cyapa_gen3_ग_लिखो_blocks(काष्ठा cyapa *cyapa,
		माप_प्रकार start_block, माप_प्रकार block_count,
		स्थिर u8 *image_data)
अणु
	पूर्णांक error;
	पूर्णांक i;

	क्रम (i = 0; i < block_count; i++) अणु
		माप_प्रकार block = start_block + i;
		माप_प्रकार addr = i * CYAPA_FW_BLOCK_SIZE;
		स्थिर u8 *data = &image_data[addr];

		error = cyapa_gen3_ग_लिखो_fw_block(cyapa, block, data);
		अगर (error)
			वापस error;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen3_करो_fw_update(काष्ठा cyapa *cyapa,
		स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	पूर्णांक error;

	/* First ग_लिखो data, starting at byte 128 of fw->data */
	error = cyapa_gen3_ग_लिखो_blocks(cyapa,
		CYAPA_FW_DATA_BLOCK_START, CYAPA_FW_DATA_BLOCK_COUNT,
		&fw->data[CYAPA_FW_HDR_BLOCK_COUNT * CYAPA_FW_BLOCK_SIZE]);
	अगर (error) अणु
		dev_err(dev, "FW update aborted, write image: %d\n", error);
		वापस error;
	पूर्ण

	/* Then ग_लिखो checksum */
	error = cyapa_gen3_ग_लिखो_blocks(cyapa,
		CYAPA_FW_HDR_BLOCK_START, CYAPA_FW_HDR_BLOCK_COUNT,
		&fw->data[0]);
	अगर (error) अणु
		dev_err(dev, "FW update aborted, write checksum: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cyapa_gen3_करो_calibrate(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	ret = cyapa_पढ़ो_byte(cyapa, CYAPA_CMD_DEV_STATUS);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading dev status: %d\n", ret);
		जाओ out;
	पूर्ण
	अगर ((ret & CYAPA_DEV_NORMAL) != CYAPA_DEV_NORMAL) अणु
		dev_warn(dev, "Trackpad device is busy, device state: 0x%02x\n",
			 ret);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = cyapa_ग_लिखो_byte(cyapa, CYAPA_CMD_SOFT_RESET,
			       OP_RECALIBRATION_MASK);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to send calibrate command: %d\n",
			ret);
		जाओ out;
	पूर्ण

	/* max recalibration समयout 2s. */
	समयout = jअगरfies + 2 * HZ;
	करो अणु
		/*
		 * For this recalibration, the max समय will not exceed 2s.
		 * The average समय is approximately 500 - 700 ms, and we
		 * will check the status every 100 - 200ms.
		 */
		msleep(100);
		ret = cyapa_पढ़ो_byte(cyapa, CYAPA_CMD_DEV_STATUS);
		अगर (ret < 0) अणु
			dev_err(dev, "Error reading dev status: %d\n", ret);
			जाओ out;
		पूर्ण
		अगर ((ret & CYAPA_DEV_NORMAL) == CYAPA_DEV_NORMAL) अणु
			dev_dbg(dev, "Calibration successful.\n");
			जाओ out;
		पूर्ण
	पूर्ण जबतक (समय_is_after_jअगरfies(समयout));

	dev_err(dev, "Failed to calibrate. Timeout.\n");
	ret = -ETIMEDOUT;

out:
	वापस ret < 0 ? ret : count;
पूर्ण

अटल sमाप_प्रकार cyapa_gen3_show_baseline(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	पूर्णांक max_baseline, min_baseline;
	पूर्णांक tries;
	पूर्णांक ret;

	ret = cyapa_पढ़ो_byte(cyapa, CYAPA_CMD_DEV_STATUS);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading dev status. err = %d\n", ret);
		जाओ out;
	पूर्ण
	अगर ((ret & CYAPA_DEV_NORMAL) != CYAPA_DEV_NORMAL) अणु
		dev_warn(dev, "Trackpad device is busy. device state = 0x%x\n",
			 ret);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = cyapa_ग_लिखो_byte(cyapa, CYAPA_CMD_SOFT_RESET,
			       OP_REPORT_BASELINE_MASK);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to send report baseline command. %d\n",
			ret);
		जाओ out;
	पूर्ण

	tries = 3;  /* Try क्रम 30 to 60 ms */
	करो अणु
		usleep_range(10000, 20000);

		ret = cyapa_पढ़ो_byte(cyapa, CYAPA_CMD_DEV_STATUS);
		अगर (ret < 0) अणु
			dev_err(dev, "Error reading dev status. err = %d\n",
				ret);
			जाओ out;
		पूर्ण
		अगर ((ret & CYAPA_DEV_NORMAL) == CYAPA_DEV_NORMAL)
			अवरोध;
	पूर्ण जबतक (--tries);

	अगर (tries == 0) अणु
		dev_err(dev, "Device timed out going to Normal state.\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	ret = cyapa_पढ़ो_byte(cyapa, CYAPA_CMD_MAX_BASELINE);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read max baseline. err = %d\n", ret);
		जाओ out;
	पूर्ण
	max_baseline = ret;

	ret = cyapa_पढ़ो_byte(cyapa, CYAPA_CMD_MIN_BASELINE);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read min baseline. err = %d\n", ret);
		जाओ out;
	पूर्ण
	min_baseline = ret;

	dev_dbg(dev, "Baseline report successful. Max: %d Min: %d\n",
		max_baseline, min_baseline);
	ret = scnम_लिखो(buf, PAGE_SIZE, "%d %d\n", max_baseline, min_baseline);

out:
	वापस ret;
पूर्ण

/*
 * cyapa_get_रुको_समय_क्रम_pwr_cmd
 *
 * Compute the amount of समय we need to रुको after updating the touchpad
 * घातer mode. The touchpad needs to consume the incoming घातer mode set
 * command at the current घड़ी rate.
 */

अटल u16 cyapa_get_रुको_समय_क्रम_pwr_cmd(u8 pwr_mode)
अणु
	चयन (pwr_mode) अणु
	हाल PWR_MODE_FULL_ACTIVE: वापस 20;
	हाल PWR_MODE_BTN_ONLY: वापस 20;
	हाल PWR_MODE_OFF: वापस 20;
	शेष: वापस cyapa_pwr_cmd_to_sleep_समय(pwr_mode) + 50;
	पूर्ण
पूर्ण

/*
 * Set device घातer mode
 *
 * Write to the field to configure घातer state. Power states include :
 *   Full : Max scans and report rate.
 *   Idle : Report rate set by user specअगरied समय.
 *   ButtonOnly : No scans क्रम fingers. When the button is triggered,
 *     a slave पूर्णांकerrupt is निश्चितed to notअगरy host to wake up.
 *   Off : Only awake क्रम i2c commands from host. No function क्रम button
 *     or touch sensors.
 *
 * The घातer_mode command should conक्रमm to the following :
 *   Full : 0x3f
 *   Idle : Configurable from 20 to 1000ms. See note below क्रम
 *     cyapa_sleep_समय_प्रकारo_pwr_cmd and cyapa_pwr_cmd_to_sleep_समय
 *   ButtonOnly : 0x01
 *   Off : 0x00
 *
 * Device घातer mode can only be set when device is in operational mode.
 */
अटल पूर्णांक cyapa_gen3_set_घातer_mode(काष्ठा cyapa *cyapa, u8 घातer_mode,
		u16 always_unused, क्रमागत cyapa_pm_stage pm_stage)
अणु
	काष्ठा input_dev *input = cyapa->input;
	u8 घातer;
	पूर्णांक tries;
	पूर्णांक sleep_समय;
	पूर्णांक पूर्णांकerval;
	पूर्णांक ret;

	अगर (cyapa->state != CYAPA_STATE_OP)
		वापस 0;

	tries = SET_POWER_MODE_TRIES;
	जबतक (tries--) अणु
		ret = cyapa_पढ़ो_byte(cyapa, CYAPA_CMD_POWER_MODE);
		अगर (ret >= 0)
			अवरोध;
		usleep_range(SET_POWER_MODE_DELAY, 2 * SET_POWER_MODE_DELAY);
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	/*
	 * Return early अगर the घातer mode to set is the same as the current
	 * one.
	 */
	अगर ((ret & PWR_MODE_MASK) == घातer_mode)
		वापस 0;

	sleep_समय = (पूर्णांक)cyapa_get_रुको_समय_क्रम_pwr_cmd(ret & PWR_MODE_MASK);
	घातer = ret;
	घातer &= ~PWR_MODE_MASK;
	घातer |= घातer_mode & PWR_MODE_MASK;
	tries = SET_POWER_MODE_TRIES;
	जबतक (tries--) अणु
		ret = cyapa_ग_लिखो_byte(cyapa, CYAPA_CMD_POWER_MODE, घातer);
		अगर (!ret)
			अवरोध;
		usleep_range(SET_POWER_MODE_DELAY, 2 * SET_POWER_MODE_DELAY);
	पूर्ण

	/*
	 * Wait क्रम the newly set घातer command to go in at the previous
	 * घड़ी speed (scanrate) used by the touchpad firmware. Not
	 * करोing so beक्रमe issuing the next command may result in errors
	 * depending on the command's content.
	 */
	अगर (cyapa->operational &&
	    input && input_device_enabled(input) &&
	    (pm_stage == CYAPA_PM_RUNTIME_SUSPEND ||
	     pm_stage == CYAPA_PM_RUNTIME_RESUME)) अणु
		/* Try to polling in 120Hz, पढ़ो may fail, just ignore it. */
		पूर्णांकerval = 1000 / 120;
		जबतक (sleep_समय > 0) अणु
			अगर (sleep_समय > पूर्णांकerval)
				msleep(पूर्णांकerval);
			अन्यथा
				msleep(sleep_समय);
			sleep_समय -= पूर्णांकerval;
			cyapa_gen3_try_poll_handler(cyapa);
		पूर्ण
	पूर्ण अन्यथा अणु
		msleep(sleep_समय);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cyapa_gen3_set_proximity(काष्ठा cyapa *cyapa, bool enable)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक cyapa_gen3_get_query_data(काष्ठा cyapa *cyapa)
अणु
	u8 query_data[QUERY_DATA_SIZE];
	पूर्णांक ret;

	अगर (cyapa->state != CYAPA_STATE_OP)
		वापस -EBUSY;

	ret = cyapa_पढ़ो_block(cyapa, CYAPA_CMD_GROUP_QUERY, query_data);
	अगर (ret != QUERY_DATA_SIZE)
		वापस (ret < 0) ? ret : -EIO;

	स_नकल(&cyapa->product_id[0], &query_data[0], 5);
	cyapa->product_id[5] = '-';
	स_नकल(&cyapa->product_id[6], &query_data[5], 6);
	cyapa->product_id[12] = '-';
	स_नकल(&cyapa->product_id[13], &query_data[11], 2);
	cyapa->product_id[15] = '\0';

	cyapa->fw_maj_ver = query_data[15];
	cyapa->fw_min_ver = query_data[16];

	cyapa->btn_capability = query_data[19] & CAPABILITY_BTN_MASK;

	cyapa->gen = query_data[20] & 0x0f;

	cyapa->max_असल_x = ((query_data[21] & 0xf0) << 4) | query_data[22];
	cyapa->max_असल_y = ((query_data[21] & 0x0f) << 8) | query_data[23];

	cyapa->physical_size_x =
		((query_data[24] & 0xf0) << 4) | query_data[25];
	cyapa->physical_size_y =
		((query_data[24] & 0x0f) << 8) | query_data[26];

	cyapa->max_z = 255;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen3_bl_query_data(काष्ठा cyapa *cyapa)
अणु
	u8 bl_data[CYAPA_CMD_LEN];
	पूर्णांक ret;

	ret = cyapa_i2c_reg_पढ़ो_block(cyapa, 0, CYAPA_CMD_LEN, bl_data);
	अगर (ret != CYAPA_CMD_LEN)
		वापस (ret < 0) ? ret : -EIO;

	/*
	 * This value will be updated again when entered application mode.
	 * If TP failed to enter application mode, this fw version values
	 * can be used as a reference.
	 * This firmware version valid when fw image checksum is valid.
	 */
	अगर (bl_data[REG_BL_STATUS] ==
			(BL_STATUS_RUNNING | BL_STATUS_CSUM_VALID)) अणु
		cyapa->fw_maj_ver = bl_data[GEN3_BL_IDLE_FW_MAJ_VER_OFFSET];
		cyapa->fw_min_ver = bl_data[GEN3_BL_IDLE_FW_MIN_VER_OFFSET];
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Check अगर device is operational.
 *
 * An operational device is responding, has निकासed bootloader, and has
 * firmware supported by this driver.
 *
 * Returns:
 *   -EBUSY  no device or in bootloader
 *   -EIO    failure जबतक पढ़ोing from device
 *   -EAGAIN device is still in bootloader
 *           अगर ->state = CYAPA_STATE_BL_IDLE, device has invalid firmware
 *   -EINVAL device is in operational mode, but not supported by this driver
 *   0       device is supported
 */
अटल पूर्णांक cyapa_gen3_करो_operational_check(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	पूर्णांक error;

	चयन (cyapa->state) अणु
	हाल CYAPA_STATE_BL_ACTIVE:
		error = cyapa_gen3_bl_deactivate(cyapa);
		अगर (error) अणु
			dev_err(dev, "failed to bl_deactivate: %d\n", error);
			वापस error;
		पूर्ण

		fallthrough;
	हाल CYAPA_STATE_BL_IDLE:
		/* Try to get firmware version in bootloader mode. */
		cyapa_gen3_bl_query_data(cyapa);

		error = cyapa_gen3_bl_निकास(cyapa);
		अगर (error) अणु
			dev_err(dev, "failed to bl_exit: %d\n", error);
			वापस error;
		पूर्ण

		fallthrough;
	हाल CYAPA_STATE_OP:
		/*
		 * Reading query data beक्रमe going back to the full mode
		 * may cause problems, so we set the घातer mode first here.
		 */
		error = cyapa_gen3_set_घातer_mode(cyapa,
				PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_ACTIVE);
		अगर (error)
			dev_err(dev, "%s: set full power mode failed: %d\n",
				__func__, error);
		error = cyapa_gen3_get_query_data(cyapa);
		अगर (error < 0)
			वापस error;

		/* Only support firmware protocol gen3 */
		अगर (cyapa->gen != CYAPA_GEN3) अणु
			dev_err(dev, "unsupported protocol version (%d)",
				cyapa->gen);
			वापस -EINVAL;
		पूर्ण

		/* Only support product ID starting with CYTRA */
		अगर (स_भेद(cyapa->product_id, product_id,
				म_माप(product_id)) != 0) अणु
			dev_err(dev, "unsupported product ID (%s)\n",
				cyapa->product_id);
			वापस -EINVAL;
		पूर्ण

		वापस 0;

	शेष:
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return false, करो not जारी process
 * Return true, जारी process.
 */
अटल bool cyapa_gen3_irq_cmd_handler(काष्ठा cyapa *cyapa)
अणु
	/* Not gen3 irq command response, skip क्रम जारी. */
	अगर (cyapa->gen != CYAPA_GEN3)
		वापस true;

	अगर (cyapa->operational)
		वापस true;

	/*
	 * Driver in detecting or other पूर्णांकerface function processing,
	 * so, stop cyapa_gen3_irq_handler to जारी process to
	 * aव्योम unwanted to error detecting and processing.
	 *
	 * And also, aव्योम the periodically निश्चितed पूर्णांकerrupts to be processed
	 * as touch inमाला_दो when gen3 failed to launch पूर्णांकo application mode,
	 * which will cause gen3 stays in bootloader mode.
	 */
	वापस false;
पूर्ण

अटल पूर्णांक cyapa_gen3_event_process(काष्ठा cyapa *cyapa,
				    काष्ठा cyapa_reg_data *data)
अणु
	काष्ठा input_dev *input = cyapa->input;
	पूर्णांक num_fingers;
	पूर्णांक i;

	num_fingers = (data->finger_btn >> 4) & 0x0f;
	क्रम (i = 0; i < num_fingers; i++) अणु
		स्थिर काष्ठा cyapa_touch *touch = &data->touches[i];
		/* Note: touch->id range is 1 to 15; slots are 0 to 14. */
		पूर्णांक slot = touch->id - 1;

		input_mt_slot(input, slot);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		input_report_असल(input, ABS_MT_POSITION_X,
				 ((touch->xy_hi & 0xf0) << 4) | touch->x_lo);
		input_report_असल(input, ABS_MT_POSITION_Y,
				 ((touch->xy_hi & 0x0f) << 8) | touch->y_lo);
		input_report_असल(input, ABS_MT_PRESSURE, touch->pressure);
	पूर्ण

	input_mt_sync_frame(input);

	अगर (cyapa->btn_capability & CAPABILITY_LEFT_BTN_MASK)
		input_report_key(input, BTN_LEFT,
				 !!(data->finger_btn & OP_DATA_LEFT_BTN));
	अगर (cyapa->btn_capability & CAPABILITY_MIDDLE_BTN_MASK)
		input_report_key(input, BTN_MIDDLE,
				 !!(data->finger_btn & OP_DATA_MIDDLE_BTN));
	अगर (cyapa->btn_capability & CAPABILITY_RIGHT_BTN_MASK)
		input_report_key(input, BTN_RIGHT,
				 !!(data->finger_btn & OP_DATA_RIGHT_BTN));
	input_sync(input);

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen3_irq_handler(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	काष्ठा cyapa_reg_data data;
	पूर्णांक ret;

	ret = cyapa_पढ़ो_block(cyapa, CYAPA_CMD_GROUP_DATA, (u8 *)&data);
	अगर (ret != माप(data)) अणु
		dev_err(dev, "failed to read report data, (%d)\n", ret);
		वापस -EINVAL;
	पूर्ण

	अगर ((data.device_status & OP_STATUS_SRC) != OP_STATUS_SRC ||
	    (data.device_status & OP_STATUS_DEV) != CYAPA_DEV_NORMAL ||
	    (data.finger_btn & OP_DATA_VALID) != OP_DATA_VALID) अणु
		dev_err(dev, "invalid device state bytes: %02x %02x\n",
			data.device_status, data.finger_btn);
		वापस -EINVAL;
	पूर्ण

	वापस cyapa_gen3_event_process(cyapa, &data);
पूर्ण

/*
 * This function will be called in the cyapa_gen3_set_घातer_mode function,
 * and it's known that it may failed in some situation after the set घातer
 * mode command was sent. So this function is aimed to aव्योम the knwon
 * and unwanted output I2C and data parse error messages.
 */
अटल पूर्णांक cyapa_gen3_try_poll_handler(काष्ठा cyapa *cyapa)
अणु
	काष्ठा cyapa_reg_data data;
	पूर्णांक ret;

	ret = cyapa_पढ़ो_block(cyapa, CYAPA_CMD_GROUP_DATA, (u8 *)&data);
	अगर (ret != माप(data))
		वापस -EINVAL;

	अगर ((data.device_status & OP_STATUS_SRC) != OP_STATUS_SRC ||
	    (data.device_status & OP_STATUS_DEV) != CYAPA_DEV_NORMAL ||
	    (data.finger_btn & OP_DATA_VALID) != OP_DATA_VALID)
		वापस -EINVAL;

	वापस cyapa_gen3_event_process(cyapa, &data);

पूर्ण

अटल पूर्णांक cyapa_gen3_initialize(काष्ठा cyapa *cyapa) अणु वापस 0; पूर्ण
अटल पूर्णांक cyapa_gen3_bl_initiate(काष्ठा cyapa *cyapa,
		स्थिर काष्ठा firmware *fw) अणु वापस 0; पूर्ण
अटल पूर्णांक cyapa_gen3_empty_output_data(काष्ठा cyapa *cyapa,
		u8 *buf, पूर्णांक *len, cb_sort func) अणु वापस 0; पूर्ण

स्थिर काष्ठा cyapa_dev_ops cyapa_gen3_ops = अणु
	.check_fw = cyapa_gen3_check_fw,
	.bl_enter = cyapa_gen3_bl_enter,
	.bl_activate = cyapa_gen3_bl_activate,
	.update_fw = cyapa_gen3_करो_fw_update,
	.bl_deactivate = cyapa_gen3_bl_deactivate,
	.bl_initiate = cyapa_gen3_bl_initiate,

	.show_baseline = cyapa_gen3_show_baseline,
	.calibrate_store = cyapa_gen3_करो_calibrate,

	.initialize = cyapa_gen3_initialize,

	.state_parse = cyapa_gen3_state_parse,
	.operational_check = cyapa_gen3_करो_operational_check,

	.irq_handler = cyapa_gen3_irq_handler,
	.irq_cmd_handler = cyapa_gen3_irq_cmd_handler,
	.sort_empty_output_data = cyapa_gen3_empty_output_data,
	.set_घातer_mode = cyapa_gen3_set_घातer_mode,

	.set_proximity = cyapa_gen3_set_proximity,
पूर्ण;

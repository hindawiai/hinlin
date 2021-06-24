<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ROHM BU21023/24 Dual touch support resistive touch screen driver
 * Copyright (C) 2012 ROHM CO.,LTD.
 */
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#घोषणा BU21023_NAME			"bu21023_ts"
#घोषणा BU21023_FIRMWARE_NAME		"bu21023.bin"

#घोषणा MAX_CONTACTS			2

#घोषणा AXIS_ADJUST			4
#घोषणा AXIS_OFFSET			8

#घोषणा FIRMWARE_BLOCK_SIZE		32U
#घोषणा FIRMWARE_RETRY_MAX		4

#घोषणा SAMPLING_DELAY			12	/* msec */

#घोषणा CALIBRATION_RETRY_MAX		6

#घोषणा ROHM_TS_ABS_X_MIN		40
#घोषणा ROHM_TS_ABS_X_MAX		990
#घोषणा ROHM_TS_ABS_Y_MIN		160
#घोषणा ROHM_TS_ABS_Y_MAX		920
#घोषणा ROHM_TS_DISPLACEMENT_MAX	0	/* zero क्रम infinite */

/*
 * BU21023GUL/BU21023MUV/BU21024FV-M रेजिस्टरs map
 */
#घोषणा VADOUT_YP_H		0x00
#घोषणा VADOUT_YP_L		0x01
#घोषणा VADOUT_XP_H		0x02
#घोषणा VADOUT_XP_L		0x03
#घोषणा VADOUT_YN_H		0x04
#घोषणा VADOUT_YN_L		0x05
#घोषणा VADOUT_XN_H		0x06
#घोषणा VADOUT_XN_L		0x07

#घोषणा PRM1_X_H		0x08
#घोषणा PRM1_X_L		0x09
#घोषणा PRM1_Y_H		0x0a
#घोषणा PRM1_Y_L		0x0b
#घोषणा PRM2_X_H		0x0c
#घोषणा PRM2_X_L		0x0d
#घोषणा PRM2_Y_H		0x0e
#घोषणा PRM2_Y_L		0x0f

#घोषणा MLT_PRM_MONI_X		0x10
#घोषणा MLT_PRM_MONI_Y		0x11

#घोषणा DEBUG_MONI_1		0x12
#घोषणा DEBUG_MONI_2		0x13

#घोषणा VADOUT_ZX_H		0x14
#घोषणा VADOUT_ZX_L		0x15
#घोषणा VADOUT_ZY_H		0x16
#घोषणा VADOUT_ZY_L		0x17

#घोषणा Z_PARAM_H		0x18
#घोषणा Z_PARAM_L		0x19

/*
 * Value क्रम VADOUT_*_L
 */
#घोषणा VADOUT_L_MASK		0x01

/*
 * Value क्रम PRM*_*_L
 */
#घोषणा PRM_L_MASK		0x01

#घोषणा POS_X1_H		0x20
#घोषणा POS_X1_L		0x21
#घोषणा POS_Y1_H		0x22
#घोषणा POS_Y1_L		0x23
#घोषणा POS_X2_H		0x24
#घोषणा POS_X2_L		0x25
#घोषणा POS_Y2_H		0x26
#घोषणा POS_Y2_L		0x27

/*
 * Value क्रम POS_*_L
 */
#घोषणा POS_L_MASK		0x01

#घोषणा TOUCH			0x28
#घोषणा TOUCH_DETECT		0x01

#घोषणा TOUCH_GESTURE		0x29
#घोषणा SINGLE_TOUCH		0x01
#घोषणा DUAL_TOUCH		0x03
#घोषणा TOUCH_MASK		0x03
#घोषणा CALIBRATION_REQUEST	0x04
#घोषणा CALIBRATION_STATUS	0x08
#घोषणा CALIBRATION_MASK	0x0c
#घोषणा GESTURE_SPREAD		0x10
#घोषणा GESTURE_PINCH		0x20
#घोषणा GESTURE_ROTATE_R	0x40
#घोषणा GESTURE_ROTATE_L	0x80

#घोषणा INT_STATUS		0x2a
#घोषणा INT_MASK		0x3d
#घोषणा INT_CLEAR		0x3e

/*
 * Values क्रम INT_*
 */
#घोषणा COORD_UPDATE		0x01
#घोषणा CALIBRATION_DONE	0x02
#घोषणा SLEEP_IN		0x04
#घोषणा SLEEP_OUT		0x08
#घोषणा PROGRAM_LOAD_DONE	0x10
#घोषणा ERROR			0x80
#घोषणा INT_ALL			0x9f

#घोषणा ERR_STATUS		0x2b
#घोषणा ERR_MASK		0x3f

/*
 * Values क्रम ERR_*
 */
#घोषणा ADC_TIMEOUT		0x01
#घोषणा CPU_TIMEOUT		0x02
#घोषणा CALIBRATION_ERR		0x04
#घोषणा PROGRAM_LOAD_ERR	0x10

#घोषणा COMMON_SETUP1			0x30
#घोषणा PROGRAM_LOAD_HOST		0x02
#घोषणा PROGRAM_LOAD_EEPROM		0x03
#घोषणा CENSOR_4PORT			0x04
#घोषणा CENSOR_8PORT			0x00	/* Not supported by BU21023 */
#घोषणा CALIBRATION_TYPE_DEFAULT	0x08
#घोषणा CALIBRATION_TYPE_SPECIAL	0x00
#घोषणा INT_ACTIVE_HIGH			0x10
#घोषणा INT_ACTIVE_LOW			0x00
#घोषणा AUTO_CALIBRATION		0x40
#घोषणा MANUAL_CALIBRATION		0x00
#घोषणा COMMON_SETUP1_DEFAULT		0x4e

#घोषणा COMMON_SETUP2		0x31
#घोषणा MAF_NONE		0x00
#घोषणा MAF_1SAMPLE		0x01
#घोषणा MAF_3SAMPLES		0x02
#घोषणा MAF_5SAMPLES		0x03
#घोषणा INV_Y			0x04
#घोषणा INV_X			0x08
#घोषणा SWAP_XY			0x10

#घोषणा COMMON_SETUP3		0x32
#घोषणा EN_SLEEP		0x01
#घोषणा EN_MULTI		0x02
#घोषणा EN_GESTURE		0x04
#घोषणा EN_INTVL		0x08
#घोषणा SEL_STEP		0x10
#घोषणा SEL_MULTI		0x20
#घोषणा SEL_TBL_DEFAULT		0x40

#घोषणा INTERVAL_TIME		0x33
#घोषणा INTERVAL_TIME_DEFAULT	0x10

#घोषणा STEP_X			0x34
#घोषणा STEP_X_DEFAULT		0x41

#घोषणा STEP_Y			0x35
#घोषणा STEP_Y_DEFAULT		0x8d

#घोषणा OFFSET_X		0x38
#घोषणा OFFSET_X_DEFAULT	0x0c

#घोषणा OFFSET_Y		0x39
#घोषणा OFFSET_Y_DEFAULT	0x0c

#घोषणा THRESHOLD_TOUCH		0x3a
#घोषणा THRESHOLD_TOUCH_DEFAULT	0xa0

#घोषणा THRESHOLD_GESTURE		0x3b
#घोषणा THRESHOLD_GESTURE_DEFAULT	0x17

#घोषणा SYSTEM			0x40
#घोषणा ANALOG_POWER_ON		0x01
#घोषणा ANALOG_POWER_OFF	0x00
#घोषणा CPU_POWER_ON		0x02
#घोषणा CPU_POWER_OFF		0x00

#घोषणा FORCE_CALIBRATION	0x42
#घोषणा FORCE_CALIBRATION_ON	0x01
#घोषणा FORCE_CALIBRATION_OFF	0x00

#घोषणा CPU_FREQ		0x50	/* 10 / (reg + 1) MHz */
#घोषणा CPU_FREQ_10MHZ		0x00
#घोषणा CPU_FREQ_5MHZ		0x01
#घोषणा CPU_FREQ_1MHZ		0x09

#घोषणा EEPROM_ADDR		0x51

#घोषणा CALIBRATION_ADJUST		0x52
#घोषणा CALIBRATION_ADJUST_DEFAULT	0x00

#घोषणा THRESHOLD_SLEEP_IN	0x53

#घोषणा EVR_XY			0x56
#घोषणा EVR_XY_DEFAULT		0x10

#घोषणा PRM_SWOFF_TIME		0x57
#घोषणा PRM_SWOFF_TIME_DEFAULT	0x04

#घोषणा PROGRAM_VERSION		0x5f

#घोषणा ADC_CTRL		0x60
#घोषणा ADC_DIV_MASK		0x1f	/* The minimum value is 4 */
#घोषणा ADC_DIV_DEFAULT		0x08

#घोषणा ADC_WAIT		0x61
#घोषणा ADC_WAIT_DEFAULT	0x0a

#घोषणा SWCONT			0x62
#घोषणा SWCONT_DEFAULT		0x0f

#घोषणा EVR_X			0x63
#घोषणा EVR_X_DEFAULT		0x86

#घोषणा EVR_Y			0x64
#घोषणा EVR_Y_DEFAULT		0x64

#घोषणा TEST1			0x65
#घोषणा DUALTOUCH_STABILIZE_ON	0x01
#घोषणा DUALTOUCH_STABILIZE_OFF	0x00
#घोषणा DUALTOUCH_REG_ON	0x20
#घोषणा DUALTOUCH_REG_OFF	0x00

#घोषणा CALIBRATION_REG1		0x68
#घोषणा CALIBRATION_REG1_DEFAULT	0xd9

#घोषणा CALIBRATION_REG2		0x69
#घोषणा CALIBRATION_REG2_DEFAULT	0x36

#घोषणा CALIBRATION_REG3		0x6a
#घोषणा CALIBRATION_REG3_DEFAULT	0x32

#घोषणा EX_ADDR_H		0x70
#घोषणा EX_ADDR_L		0x71
#घोषणा EX_WDAT			0x72
#घोषणा EX_RDAT			0x73
#घोषणा EX_CHK_SUM1		0x74
#घोषणा EX_CHK_SUM2		0x75
#घोषणा EX_CHK_SUM3		0x76

काष्ठा rohm_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;

	bool initialized;

	अचिन्हित पूर्णांक contact_count[MAX_CONTACTS + 1];
	पूर्णांक finger_count;

	u8 setup2;
पूर्ण;

/*
 * rohm_i2c_burst_पढ़ो - execute combined I2C message क्रम ROHM BU21023/24
 * @client: Handle to ROHM BU21023/24
 * @start: Where to start पढ़ो address from ROHM BU21023/24
 * @buf: Where to store पढ़ो data from ROHM BU21023/24
 * @len: How many bytes to पढ़ो
 *
 * Returns negative त्रुटि_सं, अन्यथा zero on success.
 *
 * Note
 * In BU21023/24 burst पढ़ो, stop condition is needed after "address write".
 * Thereक्रमe, transmission is perक्रमmed in 2 steps.
 */
अटल पूर्णांक rohm_i2c_burst_पढ़ो(काष्ठा i2c_client *client, u8 start, व्योम *buf,
			       माप_प्रकार len)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा i2c_msg msg[2];
	पूर्णांक i, ret = 0;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &start;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = len;
	msg[1].buf = buf;

	i2c_lock_bus(adap, I2C_LOCK_SEGMENT);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (__i2c_transfer(adap, &msg[i], 1) < 0) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	i2c_unlock_bus(adap, I2C_LOCK_SEGMENT);

	वापस ret;
पूर्ण

अटल पूर्णांक rohm_ts_manual_calibration(काष्ठा rohm_ts_data *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	काष्ठा device *dev = &client->dev;
	u8 buf[33];	/* क्रम PRM1_X_H(0x08)-TOUCH(0x28) */

	पूर्णांक retry;
	bool success = false;
	bool first_समय = true;
	bool calibration_करोne;

	u8 reg1, reg2, reg3;
	s32 reg1_orig, reg2_orig, reg3_orig;
	s32 val;

	पूर्णांक calib_x = 0, calib_y = 0;
	पूर्णांक reg_x, reg_y;
	पूर्णांक err_x, err_y;

	पूर्णांक error, error2;
	पूर्णांक i;

	reg1_orig = i2c_smbus_पढ़ो_byte_data(client, CALIBRATION_REG1);
	अगर (reg1_orig < 0)
		वापस reg1_orig;

	reg2_orig = i2c_smbus_पढ़ो_byte_data(client, CALIBRATION_REG2);
	अगर (reg2_orig < 0)
		वापस reg2_orig;

	reg3_orig = i2c_smbus_पढ़ो_byte_data(client, CALIBRATION_REG3);
	अगर (reg3_orig < 0)
		वापस reg3_orig;

	error = i2c_smbus_ग_लिखो_byte_data(client, INT_MASK,
					  COORD_UPDATE | SLEEP_IN | SLEEP_OUT |
					  PROGRAM_LOAD_DONE);
	अगर (error)
		जाओ out;

	error = i2c_smbus_ग_लिखो_byte_data(client, TEST1,
					  DUALTOUCH_STABILIZE_ON);
	अगर (error)
		जाओ out;

	क्रम (retry = 0; retry < CALIBRATION_RETRY_MAX; retry++) अणु
		/* रुको 2 sampling क्रम update */
		mdelay(2 * SAMPLING_DELAY);

#घोषणा READ_CALIB_BUF(reg)	buf[((reg) - PRM1_X_H)]

		error = rohm_i2c_burst_पढ़ो(client, PRM1_X_H, buf, माप(buf));
		अगर (error)
			जाओ out;

		अगर (READ_CALIB_BUF(TOUCH) & TOUCH_DETECT)
			जारी;

		अगर (first_समय) अणु
			/* generate calibration parameter */
			calib_x = ((पूर्णांक)READ_CALIB_BUF(PRM1_X_H) << 2 |
				READ_CALIB_BUF(PRM1_X_L)) - AXIS_OFFSET;
			calib_y = ((पूर्णांक)READ_CALIB_BUF(PRM1_Y_H) << 2 |
				READ_CALIB_BUF(PRM1_Y_L)) - AXIS_OFFSET;

			error = i2c_smbus_ग_लिखो_byte_data(client, TEST1,
				DUALTOUCH_STABILIZE_ON | DUALTOUCH_REG_ON);
			अगर (error)
				जाओ out;

			first_समय = false;
		पूर्ण अन्यथा अणु
			/* generate adjusपंचांगent parameter */
			err_x = (पूर्णांक)READ_CALIB_BUF(PRM1_X_H) << 2 |
				READ_CALIB_BUF(PRM1_X_L);
			err_y = (पूर्णांक)READ_CALIB_BUF(PRM1_Y_H) << 2 |
				READ_CALIB_BUF(PRM1_Y_L);

			/* X axis ajust */
			अगर (err_x <= 4)
				calib_x -= AXIS_ADJUST;
			अन्यथा अगर (err_x >= 60)
				calib_x += AXIS_ADJUST;

			/* Y axis ajust */
			अगर (err_y <= 4)
				calib_y -= AXIS_ADJUST;
			अन्यथा अगर (err_y >= 60)
				calib_y += AXIS_ADJUST;
		पूर्ण

		/* generate calibration setting value */
		reg_x = calib_x + ((calib_x & 0x200) << 1);
		reg_y = calib_y + ((calib_y & 0x200) << 1);

		/* convert क्रम रेजिस्टर क्रमmat */
		reg1 = reg_x >> 3;
		reg2 = (reg_y & 0x7) << 4 | (reg_x & 0x7);
		reg3 = reg_y >> 3;

		error = i2c_smbus_ग_लिखो_byte_data(client,
						  CALIBRATION_REG1, reg1);
		अगर (error)
			जाओ out;

		error = i2c_smbus_ग_लिखो_byte_data(client,
						  CALIBRATION_REG2, reg2);
		अगर (error)
			जाओ out;

		error = i2c_smbus_ग_लिखो_byte_data(client,
						  CALIBRATION_REG3, reg3);
		अगर (error)
			जाओ out;

		/*
		 * क्रमce calibration sequcence
		 */
		error = i2c_smbus_ग_लिखो_byte_data(client, FORCE_CALIBRATION,
						  FORCE_CALIBRATION_OFF);
		अगर (error)
			जाओ out;

		error = i2c_smbus_ग_लिखो_byte_data(client, FORCE_CALIBRATION,
						  FORCE_CALIBRATION_ON);
		अगर (error)
			जाओ out;

		/* clear all पूर्णांकerrupts */
		error = i2c_smbus_ग_लिखो_byte_data(client, INT_CLEAR, 0xff);
		अगर (error)
			जाओ out;

		/*
		 * Wait क्रम the status change of calibration, max 10 sampling
		 */
		calibration_करोne = false;

		क्रम (i = 0; i < 10; i++) अणु
			mdelay(SAMPLING_DELAY);

			val = i2c_smbus_पढ़ो_byte_data(client, TOUCH_GESTURE);
			अगर (!(val & CALIBRATION_MASK)) अणु
				calibration_करोne = true;
				अवरोध;
			पूर्ण अन्यथा अगर (val < 0) अणु
				error = val;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (calibration_करोne) अणु
			val = i2c_smbus_पढ़ो_byte_data(client, INT_STATUS);
			अगर (val == CALIBRATION_DONE) अणु
				success = true;
				अवरोध;
			पूर्ण अन्यथा अगर (val < 0) अणु
				error = val;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(dev, "calibration timeout\n");
		पूर्ण
	पूर्ण

	अगर (!success) अणु
		error = i2c_smbus_ग_लिखो_byte_data(client, CALIBRATION_REG1,
						  reg1_orig);
		अगर (error)
			जाओ out;

		error = i2c_smbus_ग_लिखो_byte_data(client, CALIBRATION_REG2,
						  reg2_orig);
		अगर (error)
			जाओ out;

		error = i2c_smbus_ग_लिखो_byte_data(client, CALIBRATION_REG3,
						  reg3_orig);
		अगर (error)
			जाओ out;

		/* calibration data enable */
		error = i2c_smbus_ग_लिखो_byte_data(client, TEST1,
						  DUALTOUCH_STABILIZE_ON |
						  DUALTOUCH_REG_ON);
		अगर (error)
			जाओ out;

		/* रुको 10 sampling */
		mdelay(10 * SAMPLING_DELAY);

		error = -EBUSY;
	पूर्ण

out:
	error2 = i2c_smbus_ग_लिखो_byte_data(client, INT_MASK, INT_ALL);
	अगर (!error2)
		/* Clear all पूर्णांकerrupts */
		error2 = i2c_smbus_ग_लिखो_byte_data(client, INT_CLEAR, 0xff);

	वापस error ? error : error2;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक untouch_threshold[3] = अणु 0, 1, 5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक single_touch_threshold[3] = अणु 0, 0, 4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक dual_touch_threshold[3] = अणु 10, 8, 0 पूर्ण;

अटल irqवापस_t rohm_ts_soft_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rohm_ts_data *ts = dev_id;
	काष्ठा i2c_client *client = ts->client;
	काष्ठा input_dev *input_dev = ts->input;
	काष्ठा device *dev = &client->dev;

	u8 buf[10];	/* क्रम POS_X1_H(0x20)-TOUCH_GESTURE(0x29) */

	काष्ठा input_mt_pos pos[MAX_CONTACTS];
	पूर्णांक slots[MAX_CONTACTS];
	u8 touch_flags;
	अचिन्हित पूर्णांक threshold;
	पूर्णांक finger_count = -1;
	पूर्णांक prev_finger_count = ts->finger_count;
	पूर्णांक count;
	पूर्णांक error;
	पूर्णांक i;

	error = i2c_smbus_ग_लिखो_byte_data(client, INT_MASK, INT_ALL);
	अगर (error)
		वापस IRQ_HANDLED;

	/* Clear all पूर्णांकerrupts */
	error = i2c_smbus_ग_लिखो_byte_data(client, INT_CLEAR, 0xff);
	अगर (error)
		वापस IRQ_HANDLED;

#घोषणा READ_POS_BUF(reg)	buf[((reg) - POS_X1_H)]

	error = rohm_i2c_burst_पढ़ो(client, POS_X1_H, buf, माप(buf));
	अगर (error)
		वापस IRQ_HANDLED;

	touch_flags = READ_POS_BUF(TOUCH_GESTURE) & TOUCH_MASK;
	अगर (touch_flags) अणु
		/* generate coordinates */
		pos[0].x = ((s16)READ_POS_BUF(POS_X1_H) << 2) |
			   READ_POS_BUF(POS_X1_L);
		pos[0].y = ((s16)READ_POS_BUF(POS_Y1_H) << 2) |
			   READ_POS_BUF(POS_Y1_L);
		pos[1].x = ((s16)READ_POS_BUF(POS_X2_H) << 2) |
			   READ_POS_BUF(POS_X2_L);
		pos[1].y = ((s16)READ_POS_BUF(POS_Y2_H) << 2) |
			   READ_POS_BUF(POS_Y2_L);
	पूर्ण

	चयन (touch_flags) अणु
	हाल 0:
		threshold = untouch_threshold[prev_finger_count];
		अगर (++ts->contact_count[0] >= threshold)
			finger_count = 0;
		अवरोध;

	हाल SINGLE_TOUCH:
		threshold = single_touch_threshold[prev_finger_count];
		अगर (++ts->contact_count[1] >= threshold)
			finger_count = 1;

		अगर (finger_count == 1) अणु
			अगर (pos[1].x != 0 && pos[1].y != 0) अणु
				pos[0].x = pos[1].x;
				pos[0].y = pos[1].y;
				pos[1].x = 0;
				pos[1].y = 0;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल DUAL_TOUCH:
		threshold = dual_touch_threshold[prev_finger_count];
		अगर (++ts->contact_count[2] >= threshold)
			finger_count = 2;
		अवरोध;

	शेष:
		dev_dbg(dev,
			"Three or more touches are not supported\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (finger_count >= 0) अणु
		अगर (prev_finger_count != finger_count) अणु
			count = ts->contact_count[finger_count];
			स_रखो(ts->contact_count, 0, माप(ts->contact_count));
			ts->contact_count[finger_count] = count;
		पूर्ण

		input_mt_assign_slots(input_dev, slots, pos,
				      finger_count, ROHM_TS_DISPLACEMENT_MAX);

		क्रम (i = 0; i < finger_count; i++) अणु
			input_mt_slot(input_dev, slots[i]);
			input_mt_report_slot_state(input_dev,
						   MT_TOOL_FINGER, true);
			input_report_असल(input_dev,
					 ABS_MT_POSITION_X, pos[i].x);
			input_report_असल(input_dev,
					 ABS_MT_POSITION_Y, pos[i].y);
		पूर्ण

		input_mt_sync_frame(input_dev);
		input_mt_report_poपूर्णांकer_emulation(input_dev, true);
		input_sync(input_dev);

		ts->finger_count = finger_count;
	पूर्ण

	अगर (READ_POS_BUF(TOUCH_GESTURE) & CALIBRATION_REQUEST) अणु
		error = rohm_ts_manual_calibration(ts);
		अगर (error)
			dev_warn(dev, "manual calibration failed: %d\n",
				 error);
	पूर्ण

	i2c_smbus_ग_लिखो_byte_data(client, INT_MASK,
				  CALIBRATION_DONE | SLEEP_OUT | SLEEP_IN |
				  PROGRAM_LOAD_DONE);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rohm_ts_load_firmware(काष्ठा i2c_client *client,
				 स्थिर अक्षर *firmware_name)
अणु
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा firmware *fw;
	s32 status;
	अचिन्हित पूर्णांक offset, len, xfer_len;
	अचिन्हित पूर्णांक retry = 0;
	पूर्णांक error, error2;

	error = request_firmware(&fw, firmware_name, dev);
	अगर (error) अणु
		dev_err(dev, "unable to retrieve firmware %s: %d\n",
			firmware_name, error);
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, INT_MASK,
					  COORD_UPDATE | CALIBRATION_DONE |
					  SLEEP_IN | SLEEP_OUT);
	अगर (error)
		जाओ out;

	करो अणु
		अगर (retry) अणु
			dev_warn(dev, "retrying firmware load\n");

			/* settings क्रम retry */
			error = i2c_smbus_ग_लिखो_byte_data(client, EX_WDAT, 0);
			अगर (error)
				जाओ out;
		पूर्ण

		error = i2c_smbus_ग_लिखो_byte_data(client, EX_ADDR_H, 0);
		अगर (error)
			जाओ out;

		error = i2c_smbus_ग_लिखो_byte_data(client, EX_ADDR_L, 0);
		अगर (error)
			जाओ out;

		error = i2c_smbus_ग_लिखो_byte_data(client, COMMON_SETUP1,
						  COMMON_SETUP1_DEFAULT);
		अगर (error)
			जाओ out;

		/* firmware load to the device */
		offset = 0;
		len = fw->size;

		जबतक (len) अणु
			xfer_len = min(FIRMWARE_BLOCK_SIZE, len);

			error = i2c_smbus_ग_लिखो_i2c_block_data(client, EX_WDAT,
						xfer_len, &fw->data[offset]);
			अगर (error)
				जाओ out;

			len -= xfer_len;
			offset += xfer_len;
		पूर्ण

		/* check firmware load result */
		status = i2c_smbus_पढ़ो_byte_data(client, INT_STATUS);
		अगर (status < 0) अणु
			error = status;
			जाओ out;
		पूर्ण

		/* clear all पूर्णांकerrupts */
		error = i2c_smbus_ग_लिखो_byte_data(client, INT_CLEAR, 0xff);
		अगर (error)
			जाओ out;

		अगर (status == PROGRAM_LOAD_DONE)
			अवरोध;

		error = -EIO;
	पूर्ण जबतक (++retry <= FIRMWARE_RETRY_MAX);

out:
	error2 = i2c_smbus_ग_लिखो_byte_data(client, INT_MASK, INT_ALL);

	release_firmware(fw);

	वापस error ? error : error2;
पूर्ण

अटल sमाप_प्रकार swap_xy_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rohm_ts_data *ts = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d\n", !!(ts->setup2 & SWAP_XY));
पूर्ण

अटल sमाप_प्रकार swap_xy_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rohm_ts_data *ts = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 0, &val);
	अगर (error)
		वापस error;

	error = mutex_lock_पूर्णांकerruptible(&ts->input->mutex);
	अगर (error)
		वापस error;

	अगर (val)
		ts->setup2 |= SWAP_XY;
	अन्यथा
		ts->setup2 &= ~SWAP_XY;

	अगर (ts->initialized)
		error = i2c_smbus_ग_लिखो_byte_data(ts->client, COMMON_SETUP2,
						  ts->setup2);

	mutex_unlock(&ts->input->mutex);

	वापस error ? error : count;
पूर्ण

अटल sमाप_प्रकार inv_x_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rohm_ts_data *ts = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d\n", !!(ts->setup2 & INV_X));
पूर्ण

अटल sमाप_प्रकार inv_x_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rohm_ts_data *ts = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 0, &val);
	अगर (error)
		वापस error;

	error = mutex_lock_पूर्णांकerruptible(&ts->input->mutex);
	अगर (error)
		वापस error;

	अगर (val)
		ts->setup2 |= INV_X;
	अन्यथा
		ts->setup2 &= ~INV_X;

	अगर (ts->initialized)
		error = i2c_smbus_ग_लिखो_byte_data(ts->client, COMMON_SETUP2,
						  ts->setup2);

	mutex_unlock(&ts->input->mutex);

	वापस error ? error : count;
पूर्ण

अटल sमाप_प्रकार inv_y_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rohm_ts_data *ts = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d\n", !!(ts->setup2 & INV_Y));
पूर्ण

अटल sमाप_प्रकार inv_y_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rohm_ts_data *ts = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 0, &val);
	अगर (error)
		वापस error;

	error = mutex_lock_पूर्णांकerruptible(&ts->input->mutex);
	अगर (error)
		वापस error;

	अगर (val)
		ts->setup2 |= INV_Y;
	अन्यथा
		ts->setup2 &= ~INV_Y;

	अगर (ts->initialized)
		error = i2c_smbus_ग_लिखो_byte_data(client, COMMON_SETUP2,
						  ts->setup2);

	mutex_unlock(&ts->input->mutex);

	वापस error ? error : count;
पूर्ण

अटल DEVICE_ATTR_RW(swap_xy);
अटल DEVICE_ATTR_RW(inv_x);
अटल DEVICE_ATTR_RW(inv_y);

अटल काष्ठा attribute *rohm_ts_attrs[] = अणु
	&dev_attr_swap_xy.attr,
	&dev_attr_inv_x.attr,
	&dev_attr_inv_y.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rohm_ts_attr_group = अणु
	.attrs = rohm_ts_attrs,
पूर्ण;

अटल पूर्णांक rohm_ts_device_init(काष्ठा i2c_client *client, u8 setup2)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;

	disable_irq(client->irq);

	/*
	 * Wait 200usec क्रम reset
	 */
	udelay(200);

	/* Release analog reset */
	error = i2c_smbus_ग_लिखो_byte_data(client, SYSTEM,
					  ANALOG_POWER_ON | CPU_POWER_OFF);
	अगर (error)
		वापस error;

	/* Waiting क्रम the analog warm-up, max. 200usec */
	udelay(200);

	/* clear all पूर्णांकerrupts */
	error = i2c_smbus_ग_लिखो_byte_data(client, INT_CLEAR, 0xff);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, EX_WDAT, 0);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, COMMON_SETUP1, 0);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, COMMON_SETUP2, setup2);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, COMMON_SETUP3,
					  SEL_TBL_DEFAULT | EN_MULTI);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, THRESHOLD_GESTURE,
					  THRESHOLD_GESTURE_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, INTERVAL_TIME,
					  INTERVAL_TIME_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, CPU_FREQ, CPU_FREQ_10MHZ);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, PRM_SWOFF_TIME,
					  PRM_SWOFF_TIME_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, ADC_CTRL, ADC_DIV_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, ADC_WAIT, ADC_WAIT_DEFAULT);
	अगर (error)
		वापस error;

	/*
	 * Panel setup, these values change with the panel.
	 */
	error = i2c_smbus_ग_लिखो_byte_data(client, STEP_X, STEP_X_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, STEP_Y, STEP_Y_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, OFFSET_X, OFFSET_X_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, OFFSET_Y, OFFSET_Y_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, THRESHOLD_TOUCH,
					  THRESHOLD_TOUCH_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, EVR_XY, EVR_XY_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, EVR_X, EVR_X_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, EVR_Y, EVR_Y_DEFAULT);
	अगर (error)
		वापस error;

	/* Fixed value settings */
	error = i2c_smbus_ग_लिखो_byte_data(client, CALIBRATION_ADJUST,
					  CALIBRATION_ADJUST_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, SWCONT, SWCONT_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, TEST1,
					  DUALTOUCH_STABILIZE_ON |
					  DUALTOUCH_REG_ON);
	अगर (error)
		वापस error;

	error = rohm_ts_load_firmware(client, BU21023_FIRMWARE_NAME);
	अगर (error) अणु
		dev_err(dev, "failed to load firmware: %d\n", error);
		वापस error;
	पूर्ण

	/*
	 * Manual calibration results are not changed in same environment.
	 * If the क्रमce calibration is perक्रमmed,
	 * the controller will not require calibration request पूर्णांकerrupt
	 * when the typical values are set to the calibration रेजिस्टरs.
	 */
	error = i2c_smbus_ग_लिखो_byte_data(client, CALIBRATION_REG1,
					  CALIBRATION_REG1_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, CALIBRATION_REG2,
					  CALIBRATION_REG2_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, CALIBRATION_REG3,
					  CALIBRATION_REG3_DEFAULT);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, FORCE_CALIBRATION,
					  FORCE_CALIBRATION_OFF);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, FORCE_CALIBRATION,
					  FORCE_CALIBRATION_ON);
	अगर (error)
		वापस error;

	/* Clear all पूर्णांकerrupts */
	error = i2c_smbus_ग_लिखो_byte_data(client, INT_CLEAR, 0xff);
	अगर (error)
		वापस error;

	/* Enable coordinates update पूर्णांकerrupt */
	error = i2c_smbus_ग_लिखो_byte_data(client, INT_MASK,
					  CALIBRATION_DONE | SLEEP_OUT |
					  SLEEP_IN | PROGRAM_LOAD_DONE);
	अगर (error)
		वापस error;

	error = i2c_smbus_ग_लिखो_byte_data(client, ERR_MASK,
					  PROGRAM_LOAD_ERR | CPU_TIMEOUT |
					  ADC_TIMEOUT);
	अगर (error)
		वापस error;

	/* controller CPU घातer on */
	error = i2c_smbus_ग_लिखो_byte_data(client, SYSTEM,
					  ANALOG_POWER_ON | CPU_POWER_ON);

	enable_irq(client->irq);

	वापस error;
पूर्ण

अटल पूर्णांक rohm_ts_घातer_off(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;

	error = i2c_smbus_ग_लिखो_byte_data(client, SYSTEM,
					  ANALOG_POWER_ON | CPU_POWER_OFF);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to power off device CPU: %d\n", error);
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, SYSTEM,
					  ANALOG_POWER_OFF | CPU_POWER_OFF);
	अगर (error)
		dev_err(&client->dev,
			"failed to power off the device: %d\n", error);

	वापस error;
पूर्ण

अटल पूर्णांक rohm_ts_खोलो(काष्ठा input_dev *input_dev)
अणु
	काष्ठा rohm_ts_data *ts = input_get_drvdata(input_dev);
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक error;

	अगर (!ts->initialized) अणु
		error = rohm_ts_device_init(client, ts->setup2);
		अगर (error) अणु
			dev_err(&client->dev,
				"device initialization failed: %d\n", error);
			वापस error;
		पूर्ण

		ts->initialized = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rohm_ts_बंद(काष्ठा input_dev *input_dev)
अणु
	काष्ठा rohm_ts_data *ts = input_get_drvdata(input_dev);

	rohm_ts_घातer_off(ts->client);

	ts->initialized = false;
पूर्ण

अटल पूर्णांक rohm_bu21023_i2c_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा rohm_ts_data *ts;
	काष्ठा input_dev *input;
	पूर्णांक error;

	अगर (!client->irq) अणु
		dev_err(dev, "IRQ is not assigned\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!client->adapter->algo->master_xfer) अणु
		dev_err(dev, "I2C level transfers not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Turn off CPU just in हाल */
	error = rohm_ts_घातer_off(client);
	अगर (error)
		वापस error;

	ts = devm_kzalloc(dev, माप(काष्ठा rohm_ts_data), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->client = client;
	ts->setup2 = MAF_1SAMPLE;
	i2c_set_clientdata(client, ts);

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = BU21023_NAME;
	input->id.bustype = BUS_I2C;
	input->खोलो = rohm_ts_खोलो;
	input->बंद = rohm_ts_बंद;

	ts->input = input;
	input_set_drvdata(input, ts);

	input_set_असल_params(input, ABS_MT_POSITION_X,
			     ROHM_TS_ABS_X_MIN, ROHM_TS_ABS_X_MAX, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y,
			     ROHM_TS_ABS_Y_MIN, ROHM_TS_ABS_Y_MAX, 0, 0);

	error = input_mt_init_slots(input, MAX_CONTACTS,
				    INPUT_MT_सूचीECT | INPUT_MT_TRACK |
				    INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(dev, "failed to multi touch slots initialization\n");
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, rohm_ts_soft_irq,
					  IRQF_ONESHOT, client->name, ts);
	अगर (error) अणु
		dev_err(dev, "failed to request IRQ: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_device_add_group(dev, &rohm_ts_attr_group);
	अगर (error) अणु
		dev_err(dev, "failed to create sysfs group: %d\n", error);
		वापस error;
	पूर्ण

	वापस error;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rohm_bu21023_i2c_id[] = अणु
	अणु BU21023_NAME, 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rohm_bu21023_i2c_id);

अटल काष्ठा i2c_driver rohm_bu21023_i2c_driver = अणु
	.driver = अणु
		.name = BU21023_NAME,
	पूर्ण,
	.probe = rohm_bu21023_i2c_probe,
	.id_table = rohm_bu21023_i2c_id,
पूर्ण;
module_i2c_driver(rohm_bu21023_i2c_driver);

MODULE_DESCRIPTION("ROHM BU21023/24 Touchscreen driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("ROHM Co., Ltd.");

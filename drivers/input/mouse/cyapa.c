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
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश "cyapa.h"


#घोषणा CYAPA_ADAPTER_FUNC_NONE   0
#घोषणा CYAPA_ADAPTER_FUNC_I2C    1
#घोषणा CYAPA_ADAPTER_FUNC_SMBUS  2
#घोषणा CYAPA_ADAPTER_FUNC_BOTH   3

#घोषणा CYAPA_FW_NAME		"cyapa.bin"

स्थिर अक्षर product_id[] = "CYTRA";

अटल पूर्णांक cyapa_reinitialize(काष्ठा cyapa *cyapa);

bool cyapa_is_pip_bl_mode(काष्ठा cyapa *cyapa)
अणु
	अगर (cyapa->gen == CYAPA_GEN6 && cyapa->state == CYAPA_STATE_GEN6_BL)
		वापस true;

	अगर (cyapa->gen == CYAPA_GEN5 && cyapa->state == CYAPA_STATE_GEN5_BL)
		वापस true;

	वापस false;
पूर्ण

bool cyapa_is_pip_app_mode(काष्ठा cyapa *cyapa)
अणु
	अगर (cyapa->gen == CYAPA_GEN6 && cyapa->state == CYAPA_STATE_GEN6_APP)
		वापस true;

	अगर (cyapa->gen == CYAPA_GEN5 && cyapa->state == CYAPA_STATE_GEN5_APP)
		वापस true;

	वापस false;
पूर्ण

अटल bool cyapa_is_bootloader_mode(काष्ठा cyapa *cyapa)
अणु
	अगर (cyapa_is_pip_bl_mode(cyapa))
		वापस true;

	अगर (cyapa->gen == CYAPA_GEN3 &&
		cyapa->state >= CYAPA_STATE_BL_BUSY &&
		cyapa->state <= CYAPA_STATE_BL_ACTIVE)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool cyapa_is_operational_mode(काष्ठा cyapa *cyapa)
अणु
	अगर (cyapa_is_pip_app_mode(cyapa))
		वापस true;

	अगर (cyapa->gen == CYAPA_GEN3 && cyapa->state == CYAPA_STATE_OP)
		वापस true;

	वापस false;
पूर्ण

/* Returns 0 on success, अन्यथा negative त्रुटि_सं on failure. */
अटल sमाप_प्रकार cyapa_i2c_पढ़ो(काष्ठा cyapa *cyapa, u8 reg, माप_प्रकार len,
					u8 *values)
अणु
	काष्ठा i2c_client *client = cyapa->client;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 1,
			.buf = &reg,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = values,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));

	अगर (ret != ARRAY_SIZE(msgs))
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

/**
 * cyapa_i2c_ग_लिखो - Execute i2c block data ग_लिखो operation
 * @cyapa: Handle to this driver
 * @reg: Offset of the data to written in the रेजिस्टर map
 * @len: number of bytes to ग_लिखो
 * @values: Data to be written
 *
 * Return negative त्रुटि_सं code on error; वापस zero when success.
 */
अटल पूर्णांक cyapa_i2c_ग_लिखो(काष्ठा cyapa *cyapa, u8 reg,
					 माप_प्रकार len, स्थिर व्योम *values)
अणु
	काष्ठा i2c_client *client = cyapa->client;
	अक्षर buf[32];
	पूर्णांक ret;

	अगर (len > माप(buf) - 1)
		वापस -ENOMEM;

	buf[0] = reg;
	स_नकल(&buf[1], values, len);

	ret = i2c_master_send(client, buf, len + 1);
	अगर (ret != len + 1)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल u8 cyapa_check_adapter_functionality(काष्ठा i2c_client *client)
अणु
	u8 ret = CYAPA_ADAPTER_FUNC_NONE;

	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		ret |= CYAPA_ADAPTER_FUNC_I2C;
	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_BLOCK_DATA |
				     I2C_FUNC_SMBUS_I2C_BLOCK))
		ret |= CYAPA_ADAPTER_FUNC_SMBUS;
	वापस ret;
पूर्ण

/*
 * Query device क्रम its current operating state.
 */
अटल पूर्णांक cyapa_get_state(काष्ठा cyapa *cyapa)
अणु
	u8 status[BL_STATUS_SIZE];
	u8 cmd[32];
	/* The i2c address of gen4 and gen5 trackpad device must be even. */
	bool even_addr = ((cyapa->client->addr & 0x0001) == 0);
	bool smbus = false;
	पूर्णांक retries = 2;
	पूर्णांक error;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/*
	 * Get trackpad status by पढ़ोing 3 रेजिस्टरs starting from 0.
	 * If the device is in the bootloader, this will be BL_HEAD.
	 * If the device is in operation mode, this will be the DATA regs.
	 *
	 */
	error = cyapa_i2c_reg_पढ़ो_block(cyapa, BL_HEAD_OFFSET, BL_STATUS_SIZE,
				       status);

	/*
	 * On smbus प्रणालीs in OP mode, the i2c_reg_पढ़ो will fail with
	 * -ETIMEDOUT.  In this हाल, try again using the smbus equivalent
	 * command.  This should वापस a BL_HEAD indicating CYAPA_STATE_OP.
	 */
	अगर (cyapa->smbus && (error == -ETIMEDOUT || error == -ENXIO)) अणु
		अगर (!even_addr)
			error = cyapa_पढ़ो_block(cyapa,
					CYAPA_CMD_BL_STATUS, status);
		smbus = true;
	पूर्ण

	अगर (error != BL_STATUS_SIZE)
		जाओ error;

	/*
	 * Detect trackpad protocol based on अक्षरacteristic रेजिस्टरs and bits.
	 */
	करो अणु
		cyapa->status[REG_OP_STATUS] = status[REG_OP_STATUS];
		cyapa->status[REG_BL_STATUS] = status[REG_BL_STATUS];
		cyapa->status[REG_BL_ERROR] = status[REG_BL_ERROR];

		अगर (cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN3) अणु
			error = cyapa_gen3_ops.state_parse(cyapa,
					status, BL_STATUS_SIZE);
			अगर (!error)
				जाओ out_detected;
		पूर्ण
		अगर (cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN6 ||
				cyapa->gen == CYAPA_GEN5) अणु
			error = cyapa_pip_state_parse(cyapa,
					status, BL_STATUS_SIZE);
			अगर (!error)
				जाओ out_detected;
		पूर्ण
		/* For old Gen5 trackpads detecting. */
		अगर ((cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN5) &&
			!smbus && even_addr) अणु
			error = cyapa_gen5_ops.state_parse(cyapa,
					status, BL_STATUS_SIZE);
			अगर (!error)
				जाओ out_detected;
		पूर्ण

		/*
		 * Write 0x00 0x00 to trackpad device to क्रमce update its
		 * status, then reकरो the detection again.
		 */
		अगर (!smbus) अणु
			cmd[0] = 0x00;
			cmd[1] = 0x00;
			error = cyapa_i2c_ग_लिखो(cyapa, 0, 2, cmd);
			अगर (error)
				जाओ error;

			msleep(50);

			error = cyapa_i2c_पढ़ो(cyapa, BL_HEAD_OFFSET,
					BL_STATUS_SIZE, status);
			अगर (error)
				जाओ error;
		पूर्ण
	पूर्ण जबतक (--retries > 0 && !smbus);

	जाओ error;

out_detected:
	अगर (cyapa->state <= CYAPA_STATE_BL_BUSY)
		वापस -EAGAIN;
	वापस 0;

error:
	वापस (error < 0) ? error : -EAGAIN;
पूर्ण

/*
 * Poll device क्रम its status in a loop, रुकोing up to समयout क्रम a response.
 *
 * When the device चयनes state, it usually takes ~300 ms.
 * However, when running a new firmware image, the device must calibrate its
 * sensors, which can take as दीर्घ as 2 seconds.
 *
 * Note: The समयout has granularity of the polling rate, which is 100 ms.
 *
 * Returns:
 *   0 when the device eventually responds with a valid non-busy state.
 *   -ETIMEDOUT अगर device never responds (too many -EAGAIN)
 *   -EAGAIN    अगर bootload is busy, or unknown state.
 *   < 0        other errors
 */
पूर्णांक cyapa_poll_state(काष्ठा cyapa *cyapa, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक error;
	पूर्णांक tries = समयout / 100;

	करो अणु
		error = cyapa_get_state(cyapa);
		अगर (!error && cyapa->state > CYAPA_STATE_BL_BUSY)
			वापस 0;

		msleep(100);
	पूर्ण जबतक (tries--);

	वापस (error == -EAGAIN || error == -ETIMEDOUT) ? -ETIMEDOUT : error;
पूर्ण

/*
 * Check अगर device is operational.
 *
 * An operational device is responding, has निकासed bootloader, and has
 * firmware supported by this driver.
 *
 * Returns:
 *   -ENODEV no device
 *   -EBUSY  no device or in bootloader
 *   -EIO    failure जबतक पढ़ोing from device
 *   -ETIMEDOUT समयout failure क्रम bus idle or bus no response
 *   -EAGAIN device is still in bootloader
 *           अगर ->state = CYAPA_STATE_BL_IDLE, device has invalid firmware
 *   -EINVAL device is in operational mode, but not supported by this driver
 *   0       device is supported
 */
अटल पूर्णांक cyapa_check_is_operational(काष्ठा cyapa *cyapa)
अणु
	पूर्णांक error;

	error = cyapa_poll_state(cyapa, 4000);
	अगर (error)
		वापस error;

	चयन (cyapa->gen) अणु
	हाल CYAPA_GEN6:
		cyapa->ops = &cyapa_gen6_ops;
		अवरोध;
	हाल CYAPA_GEN5:
		cyapa->ops = &cyapa_gen5_ops;
		अवरोध;
	हाल CYAPA_GEN3:
		cyapa->ops = &cyapa_gen3_ops;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	error = cyapa->ops->operational_check(cyapa);
	अगर (!error && cyapa_is_operational_mode(cyapa))
		cyapa->operational = true;
	अन्यथा
		cyapa->operational = false;

	वापस error;
पूर्ण


/*
 * Returns 0 on device detected, negative त्रुटि_सं on no device detected.
 * And when the device is detected and operational, it will be reset to
 * full घातer active mode स्वतःmatically.
 */
अटल पूर्णांक cyapa_detect(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	पूर्णांक error;

	error = cyapa_check_is_operational(cyapa);
	अगर (error) अणु
		अगर (error != -ETIMEDOUT && error != -ENODEV &&
			cyapa_is_bootloader_mode(cyapa)) अणु
			dev_warn(dev, "device detected but not operational\n");
			वापस 0;
		पूर्ण

		dev_err(dev, "no device detected: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा cyapa *cyapa = input_get_drvdata(input);
	काष्ठा i2c_client *client = cyapa->client;
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	अगर (cyapa->operational) अणु
		/*
		 * though failed to set active घातer mode,
		 * but still may be able to work in lower scan rate
		 * when in operational mode.
		 */
		error = cyapa->ops->set_घातer_mode(cyapa,
				PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_ACTIVE);
		अगर (error) अणु
			dev_warn(dev, "set active power failed: %d\n", error);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		error = cyapa_reinitialize(cyapa);
		अगर (error || !cyapa->operational) अणु
			error = error ? error : -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण

	enable_irq(client->irq);
	अगर (!pm_runसमय_enabled(dev)) अणु
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	pm_runसमय_get_sync(dev);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_sync_स्वतःsuspend(dev);
out:
	mutex_unlock(&cyapa->state_sync_lock);
	वापस error;
पूर्ण

अटल व्योम cyapa_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा cyapa *cyapa = input_get_drvdata(input);
	काष्ठा i2c_client *client = cyapa->client;
	काष्ठा device *dev = &cyapa->client->dev;

	mutex_lock(&cyapa->state_sync_lock);

	disable_irq(client->irq);
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);

	अगर (cyapa->operational)
		cyapa->ops->set_घातer_mode(cyapa,
				PWR_MODE_OFF, 0, CYAPA_PM_DEACTIVE);

	mutex_unlock(&cyapa->state_sync_lock);
पूर्ण

अटल पूर्णांक cyapa_create_input_dev(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	काष्ठा input_dev *input;
	पूर्णांक error;

	अगर (!cyapa->physical_size_x || !cyapa->physical_size_y)
		वापस -EINVAL;

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "failed to allocate memory for input device.\n");
		वापस -ENOMEM;
	पूर्ण

	input->name = CYAPA_NAME;
	input->phys = cyapa->phys;
	input->id.bustype = BUS_I2C;
	input->id.version = 1;
	input->id.product = 0;  /* Means any product in eventcomm. */
	input->dev.parent = &cyapa->client->dev;

	input->खोलो = cyapa_खोलो;
	input->बंद = cyapa_बंद;

	input_set_drvdata(input, cyapa);

	__set_bit(EV_ABS, input->evbit);

	/* Finger position */
	input_set_असल_params(input, ABS_MT_POSITION_X, 0, cyapa->max_असल_x, 0,
			     0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, cyapa->max_असल_y, 0,
			     0);
	input_set_असल_params(input, ABS_MT_PRESSURE, 0, cyapa->max_z, 0, 0);
	अगर (cyapa->gen > CYAPA_GEN3) अणु
		input_set_असल_params(input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
		input_set_असल_params(input, ABS_MT_TOUCH_MINOR, 0, 255, 0, 0);
		/*
		 * Orientation is the angle between the vertical axis and
		 * the major axis of the contact ellipse.
		 * The range is -127 to 127.
		 * the positive direction is घड़ीwise क्रमm the vertical axis.
		 * If the ellipse of contact degenerates पूर्णांकo a circle,
		 * orientation is reported as 0.
		 *
		 * Also, क्रम Gen5 trackpad the accurate of this orientation
		 * value is value + (-30 ~ 30).
		 */
		input_set_असल_params(input, ABS_MT_ORIENTATION,
				-127, 127, 0, 0);
	पूर्ण
	अगर (cyapa->gen >= CYAPA_GEN5) अणु
		input_set_असल_params(input, ABS_MT_WIDTH_MAJOR, 0, 255, 0, 0);
		input_set_असल_params(input, ABS_MT_WIDTH_MINOR, 0, 255, 0, 0);
		input_set_असल_params(input, ABS_DISTANCE, 0, 1, 0, 0);
	पूर्ण

	input_असल_set_res(input, ABS_MT_POSITION_X,
			  cyapa->max_असल_x / cyapa->physical_size_x);
	input_असल_set_res(input, ABS_MT_POSITION_Y,
			  cyapa->max_असल_y / cyapa->physical_size_y);

	अगर (cyapa->btn_capability & CAPABILITY_LEFT_BTN_MASK)
		__set_bit(BTN_LEFT, input->keybit);
	अगर (cyapa->btn_capability & CAPABILITY_MIDDLE_BTN_MASK)
		__set_bit(BTN_MIDDLE, input->keybit);
	अगर (cyapa->btn_capability & CAPABILITY_RIGHT_BTN_MASK)
		__set_bit(BTN_RIGHT, input->keybit);

	अगर (cyapa->btn_capability == CAPABILITY_LEFT_BTN_MASK)
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	/* Handle poपूर्णांकer emulation and unused slots in core */
	error = input_mt_init_slots(input, CYAPA_MAX_MT_SLOTS,
				    INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(dev, "failed to initialize MT slots: %d\n", error);
		वापस error;
	पूर्ण

	/* Register the device in input subप्रणाली */
	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	cyapa->input = input;
	वापस 0;
पूर्ण

अटल व्योम cyapa_enable_irq_क्रम_cmd(काष्ठा cyapa *cyapa)
अणु
	काष्ठा input_dev *input = cyapa->input;

	अगर (!input || !input_device_enabled(input)) अणु
		/*
		 * When input is शून्य, TP must be in deep sleep mode.
		 * In this mode, later non-घातer I2C command will always failed
		 * अगर not bring it out of deep sleep mode firstly,
		 * so must command TP to active mode here.
		 */
		अगर (!input || cyapa->operational)
			cyapa->ops->set_घातer_mode(cyapa,
				PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_ACTIVE);
		/* Gen3 always using polling mode क्रम command. */
		अगर (cyapa->gen >= CYAPA_GEN5)
			enable_irq(cyapa->client->irq);
	पूर्ण
पूर्ण

अटल व्योम cyapa_disable_irq_क्रम_cmd(काष्ठा cyapa *cyapa)
अणु
	काष्ठा input_dev *input = cyapa->input;

	अगर (!input || !input_device_enabled(input)) अणु
		अगर (cyapa->gen >= CYAPA_GEN5)
			disable_irq(cyapa->client->irq);
		अगर (!input || cyapa->operational)
			cyapa->ops->set_घातer_mode(cyapa,
					PWR_MODE_OFF, 0, CYAPA_PM_ACTIVE);
	पूर्ण
पूर्ण

/*
 * cyapa_sleep_समय_प्रकारo_pwr_cmd and cyapa_pwr_cmd_to_sleep_समय
 *
 * These are helper functions that convert to and from पूर्णांकeger idle
 * बार and रेजिस्टर settings to ग_लिखो to the PowerMode रेजिस्टर.
 * The trackpad supports between 20ms to 1000ms scan पूर्णांकervals.
 * The समय will be increased in increments of 10ms from 20ms to 100ms.
 * From 100ms to 1000ms, समय will be increased in increments of 20ms.
 *
 * When Idle_Time < 100, the क्रमmat to convert Idle_Time to Idle_Command is:
 *   Idle_Command = Idle Time / 10;
 * When Idle_Time >= 100, the क्रमmat to convert Idle_Time to Idle_Command is:
 *   Idle_Command = Idle Time / 20 + 5;
 */
u8 cyapa_sleep_समय_प्रकारo_pwr_cmd(u16 sleep_समय)
अणु
	u16 encoded_समय;

	sleep_समय = clamp_val(sleep_समय, 20, 1000);
	encoded_समय = sleep_समय < 100 ? sleep_समय / 10 : sleep_समय / 20 + 5;
	वापस (encoded_समय << 2) & PWR_MODE_MASK;
पूर्ण

u16 cyapa_pwr_cmd_to_sleep_समय(u8 pwr_mode)
अणु
	u8 encoded_समय = pwr_mode >> 2;

	वापस (encoded_समय < 10) ? encoded_समय * 10
				   : (encoded_समय - 5) * 20;
पूर्ण

/* 0 on driver initialize and detected successfully, negative on failure. */
अटल पूर्णांक cyapa_initialize(काष्ठा cyapa *cyapa)
अणु
	पूर्णांक error = 0;

	cyapa->state = CYAPA_STATE_NO_DEVICE;
	cyapa->gen = CYAPA_GEN_UNKNOWN;
	mutex_init(&cyapa->state_sync_lock);

	/*
	 * Set to hard code शेष, they will be updated with trackpad set
	 * शेष values after probe and initialized.
	 */
	cyapa->suspend_घातer_mode = PWR_MODE_SLEEP;
	cyapa->suspend_sleep_समय =
		cyapa_pwr_cmd_to_sleep_समय(cyapa->suspend_घातer_mode);

	/* ops.initialize() is aimed to prepare क्रम module communications. */
	error = cyapa_gen3_ops.initialize(cyapa);
	अगर (!error)
		error = cyapa_gen5_ops.initialize(cyapa);
	अगर (!error)
		error = cyapa_gen6_ops.initialize(cyapa);
	अगर (error)
		वापस error;

	error = cyapa_detect(cyapa);
	अगर (error)
		वापस error;

	/* Power करोwn the device until we need it. */
	अगर (cyapa->operational)
		cyapa->ops->set_घातer_mode(cyapa,
				PWR_MODE_OFF, 0, CYAPA_PM_ACTIVE);

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_reinitialize(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	काष्ठा input_dev *input = cyapa->input;
	पूर्णांक error;

	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);

	/* Aव्योम command failures when TP was in OFF state. */
	अगर (cyapa->operational)
		cyapa->ops->set_घातer_mode(cyapa,
				PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_ACTIVE);

	error = cyapa_detect(cyapa);
	अगर (error)
		जाओ out;

	अगर (!input && cyapa->operational) अणु
		error = cyapa_create_input_dev(cyapa);
		अगर (error) अणु
			dev_err(dev, "create input_dev instance failed: %d\n",
					error);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (!input || !input_device_enabled(input)) अणु
		/* Reset to घातer OFF state to save घातer when no user खोलो. */
		अगर (cyapa->operational)
			cyapa->ops->set_घातer_mode(cyapa,
					PWR_MODE_OFF, 0, CYAPA_PM_DEACTIVE);
	पूर्ण अन्यथा अगर (!error && cyapa->operational) अणु
		/*
		 * Make sure only enable runसमय PM when device is
		 * in operational mode and input->users > 0.
		 */
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);

		pm_runसमय_get_sync(dev);
		pm_runसमय_mark_last_busy(dev);
		pm_runसमय_put_sync_स्वतःsuspend(dev);
	पूर्ण

	वापस error;
पूर्ण

अटल irqवापस_t cyapa_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cyapa *cyapa = dev_id;
	काष्ठा device *dev = &cyapa->client->dev;
	पूर्णांक error;

	अगर (device_may_wakeup(dev))
		pm_wakeup_event(dev, 0);

	/* Interrupt event can be caused by host command to trackpad device. */
	अगर (cyapa->ops->irq_cmd_handler(cyapa)) अणु
		/*
		 * Interrupt event maybe from trackpad device input reporting.
		 */
		अगर (!cyapa->input) अणु
			/*
			 * Still in probing or in firmware image
			 * updating or पढ़ोing.
			 */
			cyapa->ops->sort_empty_output_data(cyapa,
					शून्य, शून्य, शून्य);
			जाओ out;
		पूर्ण

		अगर (cyapa->operational) अणु
			error = cyapa->ops->irq_handler(cyapa);

			/*
			 * Apply runसमय घातer management to touch report event
			 * except the events caused by the command responses.
			 * Note:
			 * It will पूर्णांकroduce about 20~40 ms additional delay
			 * समय in receiving क्रम first valid touch report data.
			 * The समय is used to execute device runसमय resume
			 * process.
			 */
			pm_runसमय_get_sync(dev);
			pm_runसमय_mark_last_busy(dev);
			pm_runसमय_put_sync_स्वतःsuspend(dev);
		पूर्ण

		अगर (!cyapa->operational || error) अणु
			अगर (!mutex_trylock(&cyapa->state_sync_lock)) अणु
				cyapa->ops->sort_empty_output_data(cyapa,
					शून्य, शून्य, शून्य);
				जाओ out;
			पूर्ण
			cyapa_reinitialize(cyapa);
			mutex_unlock(&cyapa->state_sync_lock);
		पूर्ण
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

/*
 **************************************************************
 * sysfs पूर्णांकerface
 **************************************************************
*/
#अगर_घोषित CONFIG_PM_SLEEP
अटल sमाप_प्रकार cyapa_show_suspend_scanrate(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	u8 pwr_cmd;
	u16 sleep_समय;
	पूर्णांक len;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	pwr_cmd = cyapa->suspend_घातer_mode;
	sleep_समय = cyapa->suspend_sleep_समय;

	mutex_unlock(&cyapa->state_sync_lock);

	चयन (pwr_cmd) अणु
	हाल PWR_MODE_BTN_ONLY:
		len = scnम_लिखो(buf, PAGE_SIZE, "%s\n", BTN_ONLY_MODE_NAME);
		अवरोध;

	हाल PWR_MODE_OFF:
		len = scnम_लिखो(buf, PAGE_SIZE, "%s\n", OFF_MODE_NAME);
		अवरोध;

	शेष:
		len = scnम_लिखो(buf, PAGE_SIZE, "%u\n",
				cyapa->gen == CYAPA_GEN3 ?
					cyapa_pwr_cmd_to_sleep_समय(pwr_cmd) :
					sleep_समय);
		अवरोध;
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार cyapa_update_suspend_scanrate(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	u16 sleep_समय;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	अगर (sysfs_streq(buf, BTN_ONLY_MODE_NAME)) अणु
		cyapa->suspend_घातer_mode = PWR_MODE_BTN_ONLY;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, OFF_MODE_NAME)) अणु
		cyapa->suspend_घातer_mode = PWR_MODE_OFF;
	पूर्ण अन्यथा अगर (!kstrtou16(buf, 10, &sleep_समय)) अणु
		cyapa->suspend_sleep_समय = min_t(u16, sleep_समय, 1000);
		cyapa->suspend_घातer_mode =
			cyapa_sleep_समय_प्रकारo_pwr_cmd(cyapa->suspend_sleep_समय);
	पूर्ण अन्यथा अणु
		count = -EINVAL;
	पूर्ण

	mutex_unlock(&cyapa->state_sync_lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(suspend_scanrate_ms, S_IRUGO|S_IWUSR,
		   cyapa_show_suspend_scanrate,
		   cyapa_update_suspend_scanrate);

अटल काष्ठा attribute *cyapa_घातer_wakeup_entries[] = अणु
	&dev_attr_suspend_scanrate_ms.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cyapa_घातer_wakeup_group = अणु
	.name = घातer_group_name,
	.attrs = cyapa_घातer_wakeup_entries,
पूर्ण;

अटल व्योम cyapa_हटाओ_घातer_wakeup_group(व्योम *data)
अणु
	काष्ठा cyapa *cyapa = data;

	sysfs_unmerge_group(&cyapa->client->dev.kobj,
				&cyapa_घातer_wakeup_group);
पूर्ण

अटल पूर्णांक cyapa_prepare_wakeup_controls(काष्ठा cyapa *cyapa)
अणु
	काष्ठा i2c_client *client = cyapa->client;
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;

	अगर (device_can_wakeup(dev)) अणु
		error = sysfs_merge_group(&dev->kobj,
					  &cyapa_घातer_wakeup_group);
		अगर (error) अणु
			dev_err(dev, "failed to add power wakeup group: %d\n",
				error);
			वापस error;
		पूर्ण

		error = devm_add_action_or_reset(dev,
				cyapa_हटाओ_घातer_wakeup_group, cyapa);
		अगर (error) अणु
			dev_err(dev, "failed to add power cleanup action: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक cyapa_prepare_wakeup_controls(काष्ठा cyapa *cyapa)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल sमाप_प्रकार cyapa_show_rt_suspend_scanrate(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	u8 pwr_cmd;
	u16 sleep_समय;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	pwr_cmd = cyapa->runसमय_suspend_घातer_mode;
	sleep_समय = cyapa->runसमय_suspend_sleep_समय;

	mutex_unlock(&cyapa->state_sync_lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 cyapa->gen == CYAPA_GEN3 ?
				cyapa_pwr_cmd_to_sleep_समय(pwr_cmd) :
				sleep_समय);
पूर्ण

अटल sमाप_प्रकार cyapa_update_rt_suspend_scanrate(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	u16 समय;
	पूर्णांक error;

	अगर (buf == शून्य || count == 0 || kstrtou16(buf, 10, &समय)) अणु
		dev_err(dev, "invalid runtime suspend scanrate ms parameter\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * When the suspend scanrate is changed, pm_runसमय_get to resume
	 * a potentially suspended device, update to the new pwr_cmd
	 * and then pm_runसमय_put to suspend पूर्णांकo the new घातer mode.
	 */
	pm_runसमय_get_sync(dev);

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	cyapa->runसमय_suspend_sleep_समय = min_t(u16, समय, 1000);
	cyapa->runसमय_suspend_घातer_mode =
		cyapa_sleep_समय_प्रकारo_pwr_cmd(cyapa->runसमय_suspend_sleep_समय);

	mutex_unlock(&cyapa->state_sync_lock);

	pm_runसमय_put_sync_स्वतःsuspend(dev);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(runसमय_suspend_scanrate_ms, S_IRUGO|S_IWUSR,
		   cyapa_show_rt_suspend_scanrate,
		   cyapa_update_rt_suspend_scanrate);

अटल काष्ठा attribute *cyapa_घातer_runसमय_entries[] = अणु
	&dev_attr_runसमय_suspend_scanrate_ms.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cyapa_घातer_runसमय_group = अणु
	.name = घातer_group_name,
	.attrs = cyapa_घातer_runसमय_entries,
पूर्ण;

अटल व्योम cyapa_हटाओ_घातer_runसमय_group(व्योम *data)
अणु
	काष्ठा cyapa *cyapa = data;

	sysfs_unmerge_group(&cyapa->client->dev.kobj,
				&cyapa_घातer_runसमय_group);
पूर्ण

अटल पूर्णांक cyapa_start_runसमय(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	पूर्णांक error;

	cyapa->runसमय_suspend_घातer_mode = PWR_MODE_IDLE;
	cyapa->runसमय_suspend_sleep_समय =
		cyapa_pwr_cmd_to_sleep_समय(cyapa->runसमय_suspend_घातer_mode);

	error = sysfs_merge_group(&dev->kobj, &cyapa_घातer_runसमय_group);
	अगर (error) अणु
		dev_err(dev,
			"failed to create power runtime group: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(dev, cyapa_हटाओ_घातer_runसमय_group,
					 cyapa);
	अगर (error) अणु
		dev_err(dev,
			"failed to add power runtime cleanup action: %d\n",
			error);
		वापस error;
	पूर्ण

	/* runसमय is enabled until device is operational and खोलोed. */
	pm_runसमय_set_suspended(dev);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, AUTOSUSPEND_DELAY);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक cyapa_start_runसमय(काष्ठा cyapa *cyapa)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल sमाप_प्रकार cyapa_show_fm_ver(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक error;
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;
	error = scnम_लिखो(buf, PAGE_SIZE, "%d.%d\n", cyapa->fw_maj_ver,
			 cyapa->fw_min_ver);
	mutex_unlock(&cyapa->state_sync_lock);
	वापस error;
पूर्ण

अटल sमाप_प्रकार cyapa_show_product_id(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	पूर्णांक size;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;
	size = scnम_लिखो(buf, PAGE_SIZE, "%s\n", cyapa->product_id);
	mutex_unlock(&cyapa->state_sync_lock);
	वापस size;
पूर्ण

अटल पूर्णांक cyapa_firmware(काष्ठा cyapa *cyapa, स्थिर अक्षर *fw_name)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक error;

	error = request_firmware(&fw, fw_name, dev);
	अगर (error) अणु
		dev_err(dev, "Could not load firmware from %s: %d\n",
			fw_name, error);
		वापस error;
	पूर्ण

	error = cyapa->ops->check_fw(cyapa, fw);
	अगर (error) अणु
		dev_err(dev, "Invalid CYAPA firmware image: %s\n",
				fw_name);
		जाओ करोne;
	पूर्ण

	/*
	 * Resume the potentially suspended device because करोing FW
	 * update on a device not in the FULL mode has a chance to
	 * fail.
	 */
	pm_runसमय_get_sync(dev);

	/* Require IRQ support क्रम firmware update commands. */
	cyapa_enable_irq_क्रम_cmd(cyapa);

	error = cyapa->ops->bl_enter(cyapa);
	अगर (error) अणु
		dev_err(dev, "bl_enter failed, %d\n", error);
		जाओ err_detect;
	पूर्ण

	error = cyapa->ops->bl_activate(cyapa);
	अगर (error) अणु
		dev_err(dev, "bl_activate failed, %d\n", error);
		जाओ err_detect;
	पूर्ण

	error = cyapa->ops->bl_initiate(cyapa, fw);
	अगर (error) अणु
		dev_err(dev, "bl_initiate failed, %d\n", error);
		जाओ err_detect;
	पूर्ण

	error = cyapa->ops->update_fw(cyapa, fw);
	अगर (error) अणु
		dev_err(dev, "update_fw failed, %d\n", error);
		जाओ err_detect;
	पूर्ण

err_detect:
	cyapa_disable_irq_क्रम_cmd(cyapa);
	pm_runसमय_put_noidle(dev);

करोne:
	release_firmware(fw);
	वापस error;
पूर्ण

अटल sमाप_प्रकार cyapa_update_fw_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	अक्षर fw_name[NAME_MAX];
	पूर्णांक ret, error;

	अगर (count >= NAME_MAX) अणु
		dev_err(dev, "File name too long\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(fw_name, buf, count);
	अगर (fw_name[count - 1] == '\n')
		fw_name[count - 1] = '\0';
	अन्यथा
		fw_name[count] = '\0';

	अगर (cyapa->input) अणु
		/*
		 * Force the input device to be रेजिस्टरed after the firmware
		 * image is updated, so अगर the corresponding parameters updated
		 * in the new firmware image can taken effect immediately.
		 */
		input_unरेजिस्टर_device(cyapa->input);
		cyapa->input = शून्य;
	पूर्ण

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error) अणु
		/*
		 * Whatever, करो reinitialize to try to recover TP state to
		 * previous state just as it entered fw update entrance.
		 */
		cyapa_reinitialize(cyapa);
		वापस error;
	पूर्ण

	error = cyapa_firmware(cyapa, fw_name);
	अगर (error)
		dev_err(dev, "firmware update failed: %d\n", error);
	अन्यथा
		dev_dbg(dev, "firmware update successfully done.\n");

	/*
	 * Re-detect trackpad device states because firmware update process
	 * will reset trackpad device पूर्णांकo bootloader mode.
	 */
	ret = cyapa_reinitialize(cyapa);
	अगर (ret) अणु
		dev_err(dev, "failed to re-detect after updated: %d\n", ret);
		error = error ? error : ret;
	पूर्ण

	mutex_unlock(&cyapa->state_sync_lock);

	वापस error ? error : count;
पूर्ण

अटल sमाप_प्रकार cyapa_calibrate_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	अगर (cyapa->operational) अणु
		cyapa_enable_irq_क्रम_cmd(cyapa);
		error = cyapa->ops->calibrate_store(dev, attr, buf, count);
		cyapa_disable_irq_क्रम_cmd(cyapa);
	पूर्ण अन्यथा अणु
		error = -EBUSY;  /* Still running in bootloader mode. */
	पूर्ण

	mutex_unlock(&cyapa->state_sync_lock);
	वापस error < 0 ? error : count;
पूर्ण

अटल sमाप_प्रकार cyapa_show_baseline(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	sमाप_प्रकार error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	अगर (cyapa->operational) अणु
		cyapa_enable_irq_क्रम_cmd(cyapa);
		error = cyapa->ops->show_baseline(dev, attr, buf);
		cyapa_disable_irq_क्रम_cmd(cyapa);
	पूर्ण अन्यथा अणु
		error = -EBUSY;  /* Still running in bootloader mode. */
	पूर्ण

	mutex_unlock(&cyapa->state_sync_lock);
	वापस error;
पूर्ण

अटल अक्षर *cyapa_state_to_string(काष्ठा cyapa *cyapa)
अणु
	चयन (cyapa->state) अणु
	हाल CYAPA_STATE_BL_BUSY:
		वापस "bootloader busy";
	हाल CYAPA_STATE_BL_IDLE:
		वापस "bootloader idle";
	हाल CYAPA_STATE_BL_ACTIVE:
		वापस "bootloader active";
	हाल CYAPA_STATE_GEN5_BL:
	हाल CYAPA_STATE_GEN6_BL:
		वापस "bootloader";
	हाल CYAPA_STATE_OP:
	हाल CYAPA_STATE_GEN5_APP:
	हाल CYAPA_STATE_GEN6_APP:
		वापस "operational";  /* Normal valid state. */
	शेष:
		वापस "invalid mode";
	पूर्ण
पूर्ण

अटल sमाप_प्रकार cyapa_show_mode(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	पूर्णांक size;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	size = scnम_लिखो(buf, PAGE_SIZE, "gen%d %s\n",
			cyapa->gen, cyapa_state_to_string(cyapa));

	mutex_unlock(&cyapa->state_sync_lock);
	वापस size;
पूर्ण

अटल DEVICE_ATTR(firmware_version, S_IRUGO, cyapa_show_fm_ver, शून्य);
अटल DEVICE_ATTR(product_id, S_IRUGO, cyapa_show_product_id, शून्य);
अटल DEVICE_ATTR(update_fw, S_IWUSR, शून्य, cyapa_update_fw_store);
अटल DEVICE_ATTR(baseline, S_IRUGO, cyapa_show_baseline, शून्य);
अटल DEVICE_ATTR(calibrate, S_IWUSR, शून्य, cyapa_calibrate_store);
अटल DEVICE_ATTR(mode, S_IRUGO, cyapa_show_mode, शून्य);

अटल काष्ठा attribute *cyapa_sysfs_entries[] = अणु
	&dev_attr_firmware_version.attr,
	&dev_attr_product_id.attr,
	&dev_attr_update_fw.attr,
	&dev_attr_baseline.attr,
	&dev_attr_calibrate.attr,
	&dev_attr_mode.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cyapa_sysfs_group = अणु
	.attrs = cyapa_sysfs_entries,
पूर्ण;

अटल व्योम cyapa_disable_regulator(व्योम *data)
अणु
	काष्ठा cyapa *cyapa = data;

	regulator_disable(cyapa->vcc);
पूर्ण

अटल पूर्णांक cyapa_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *dev_id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा cyapa *cyapa;
	u8 adapter_func;
	जोड़ i2c_smbus_data dummy;
	पूर्णांक error;

	adapter_func = cyapa_check_adapter_functionality(client);
	अगर (adapter_func == CYAPA_ADAPTER_FUNC_NONE) अणु
		dev_err(dev, "not a supported I2C/SMBus adapter\n");
		वापस -EIO;
	पूर्ण

	/* Make sure there is something at this address */
	अगर (i2c_smbus_xfer(client->adapter, client->addr, 0,
			I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &dummy) < 0)
		वापस -ENODEV;

	cyapa = devm_kzalloc(dev, माप(काष्ठा cyapa), GFP_KERNEL);
	अगर (!cyapa)
		वापस -ENOMEM;

	/* i2c isn't supported, use smbus */
	अगर (adapter_func == CYAPA_ADAPTER_FUNC_SMBUS)
		cyapa->smbus = true;

	cyapa->client = client;
	i2c_set_clientdata(client, cyapa);
	प्र_लिखो(cyapa->phys, "i2c-%d-%04x/input0", client->adapter->nr,
		client->addr);

	cyapa->vcc = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(cyapa->vcc)) अणु
		error = PTR_ERR(cyapa->vcc);
		dev_err(dev, "failed to get vcc regulator: %d\n", error);
		वापस error;
	पूर्ण

	error = regulator_enable(cyapa->vcc);
	अगर (error) अणु
		dev_err(dev, "failed to enable regulator: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(dev, cyapa_disable_regulator, cyapa);
	अगर (error) अणु
		dev_err(dev, "failed to add disable regulator action: %d\n",
			error);
		वापस error;
	पूर्ण

	error = cyapa_initialize(cyapa);
	अगर (error) अणु
		dev_err(dev, "failed to detect and initialize tp device.\n");
		वापस error;
	पूर्ण

	error = devm_device_add_group(dev, &cyapa_sysfs_group);
	अगर (error) अणु
		dev_err(dev, "failed to create sysfs entries: %d\n", error);
		वापस error;
	पूर्ण

	error = cyapa_prepare_wakeup_controls(cyapa);
	अगर (error) अणु
		dev_err(dev, "failed to prepare wakeup controls: %d\n", error);
		वापस error;
	पूर्ण

	error = cyapa_start_runसमय(cyapa);
	अगर (error) अणु
		dev_err(dev, "failed to start pm_runtime: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, cyapa_irq,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					  "cyapa", cyapa);
	अगर (error) अणु
		dev_err(dev, "failed to request threaded irq: %d\n", error);
		वापस error;
	पूर्ण

	/* Disable IRQ until the device is खोलोed */
	disable_irq(client->irq);

	/*
	 * Register the device in the input subप्रणाली when it's operational.
	 * Otherwise, keep in this driver, so it can be be recovered or updated
	 * through the sysfs mode and update_fw पूर्णांकerfaces by user or apps.
	 */
	अगर (cyapa->operational) अणु
		error = cyapa_create_input_dev(cyapa);
		अगर (error) अणु
			dev_err(dev, "create input_dev instance failed: %d\n",
					error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cyapa_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cyapa *cyapa = i2c_get_clientdata(client);
	u8 घातer_mode;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&cyapa->state_sync_lock);
	अगर (error)
		वापस error;

	/*
	 * Runसमय PM is enable only when device is in operational mode and
	 * users in use, so need check it beक्रमe disable it to
	 * aव्योम unbalance warning.
	 */
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	disable_irq(client->irq);

	/*
	 * Set trackpad device to idle mode अगर wakeup is allowed,
	 * otherwise turn off.
	 */
	अगर (cyapa->operational) अणु
		घातer_mode = device_may_wakeup(dev) ? cyapa->suspend_घातer_mode
						    : PWR_MODE_OFF;
		error = cyapa->ops->set_घातer_mode(cyapa, घातer_mode,
				cyapa->suspend_sleep_समय, CYAPA_PM_SUSPEND);
		अगर (error)
			dev_err(dev, "suspend set power mode failed: %d\n",
					error);
	पूर्ण

	/*
	 * Disable proximity पूर्णांकerrupt when प्रणाली idle, want true touch to
	 * wake the प्रणाली.
	 */
	अगर (cyapa->dev_pwr_mode != PWR_MODE_OFF)
		cyapa->ops->set_proximity(cyapa, false);

	अगर (device_may_wakeup(dev))
		cyapa->irq_wake = (enable_irq_wake(client->irq) == 0);

	mutex_unlock(&cyapa->state_sync_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cyapa_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cyapa *cyapa = i2c_get_clientdata(client);
	पूर्णांक error;

	mutex_lock(&cyapa->state_sync_lock);

	अगर (device_may_wakeup(dev) && cyapa->irq_wake) अणु
		disable_irq_wake(client->irq);
		cyapa->irq_wake = false;
	पूर्ण

	/*
	 * Update device states and runसमय PM states.
	 * Re-Enable proximity पूर्णांकerrupt after enter operational mode.
	 */
	error = cyapa_reinitialize(cyapa);
	अगर (error)
		dev_warn(dev, "failed to reinitialize TP device: %d\n", error);

	enable_irq(client->irq);

	mutex_unlock(&cyapa->state_sync_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cyapa_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	पूर्णांक error;

	error = cyapa->ops->set_घातer_mode(cyapa,
			cyapa->runसमय_suspend_घातer_mode,
			cyapa->runसमय_suspend_sleep_समय,
			CYAPA_PM_RUNTIME_SUSPEND);
	अगर (error)
		dev_warn(dev, "runtime suspend failed: %d\n", error);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cyapa_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	पूर्णांक error;

	error = cyapa->ops->set_घातer_mode(cyapa,
			PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_RUNTIME_RESUME);
	अगर (error)
		dev_warn(dev, "runtime resume failed: %d\n", error);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cyapa_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cyapa_suspend, cyapa_resume)
	SET_RUNTIME_PM_OPS(cyapa_runसमय_suspend, cyapa_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id cyapa_id_table[] = अणु
	अणु "cyapa", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cyapa_id_table);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cyapa_acpi_id[] = अणु
	अणु "CYAP0000", 0 पूर्ण,  /* Gen3 trackpad with 0x67 I2C address. */
	अणु "CYAP0001", 0 पूर्ण,  /* Gen5 trackpad with 0x24 I2C address. */
	अणु "CYAP0002", 0 पूर्ण,  /* Gen6 trackpad with 0x24 I2C address. */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cyapa_acpi_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cyapa_of_match[] = अणु
	अणु .compatible = "cypress,cyapa" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cyapa_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver cyapa_driver = अणु
	.driver = अणु
		.name = "cyapa",
		.pm = &cyapa_pm_ops,
		.acpi_match_table = ACPI_PTR(cyapa_acpi_id),
		.of_match_table = of_match_ptr(cyapa_of_match),
	पूर्ण,

	.probe = cyapa_probe,
	.id_table = cyapa_id_table,
पूर्ण;

module_i2c_driver(cyapa_driver);

MODULE_DESCRIPTION("Cypress APA I2C Trackpad Driver");
MODULE_AUTHOR("Dudley Du <dudl@cypress.com>");
MODULE_LICENSE("GPL");

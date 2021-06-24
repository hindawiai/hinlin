<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PlayStation 1/2 joypads via SPI पूर्णांकerface Driver
 *
 * Copyright (C) 2017 Tomohiro Yoshiकरोmi <sylph23k@gmail.com>
 *
 * PlayStation 1/2 joypad's plug (not socket)
 *  123 456 789
 * (...|...|...)
 *
 * 1: DAT -> MISO (pullup with 1k owm to 3.3V)
 * 2: CMD -> MOSI
 * 3: 9V (क्रम motor, अगर not use N.C.)
 * 4: GND
 * 5: 3.3V
 * 6: Attention -> CS(SS)
 * 7: SCK -> SCK
 * 8: N.C.
 * 9: ACK -> N.C.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा REVERSE_BIT(x) ((((x) & 0x80) >> 7) | (((x) & 0x40) >> 5) | \
	(((x) & 0x20) >> 3) | (((x) & 0x10) >> 1) | (((x) & 0x08) << 1) | \
	(((x) & 0x04) << 3) | (((x) & 0x02) << 5) | (((x) & 0x01) << 7))

/* PlayStation 1/2 joypad command and response are LSBFIRST. */

/*
 *	0x01, 0x42, 0x00, 0x00, 0x00,
 *	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 *	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 */
अटल स्थिर u8 PSX_CMD_POLL[] = अणु
	0x80, 0x42, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;
/*	0x01, 0x43, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 */
अटल स्थिर u8 PSX_CMD_ENTER_CFG[] = अणु
	0x80, 0xC2, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;
/*	0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A */
अटल स्थिर u8 PSX_CMD_EXIT_CFG[] = अणु
	0x80, 0xC2, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A
पूर्ण;
/*	0x01, 0x4D, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF */
अटल स्थिर u8 PSX_CMD_ENABLE_MOTOR[]	= अणु
	0x80, 0xB2, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF
पूर्ण;

काष्ठा psxpad अणु
	काष्ठा spi_device *spi;
	काष्ठा input_dev *idev;
	अक्षर phys[0x20];
	bool motor1enable;
	bool motor2enable;
	u8 motor1level;
	u8 motor2level;
	u8 sendbuf[0x20] ____cacheline_aligned;
	u8 response[माप(PSX_CMD_POLL)] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक psxpad_command(काष्ठा psxpad *pad, स्थिर u8 sendcmdlen)
अणु
	काष्ठा spi_transfer xfers = अणु
		.tx_buf		= pad->sendbuf,
		.rx_buf		= pad->response,
		.len		= sendcmdlen,
	पूर्ण;
	पूर्णांक err;

	err = spi_sync_transfer(pad->spi, &xfers, 1);
	अगर (err) अणु
		dev_err(&pad->spi->dev,
			"%s: failed to SPI xfers mode: %d\n",
			__func__, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_JOYSTICK_PSXPAD_SPI_FF
अटल व्योम psxpad_control_motor(काष्ठा psxpad *pad,
				 bool motor1enable, bool motor2enable)
अणु
	पूर्णांक err;

	pad->motor1enable = motor1enable;
	pad->motor2enable = motor2enable;

	स_नकल(pad->sendbuf, PSX_CMD_ENTER_CFG, माप(PSX_CMD_ENTER_CFG));
	err = psxpad_command(pad, माप(PSX_CMD_ENTER_CFG));
	अगर (err) अणु
		dev_err(&pad->spi->dev,
			"%s: failed to enter config mode: %d\n",
			__func__, err);
		वापस;
	पूर्ण

	स_नकल(pad->sendbuf, PSX_CMD_ENABLE_MOTOR,
	       माप(PSX_CMD_ENABLE_MOTOR));
	pad->sendbuf[3] = pad->motor1enable ? 0x00 : 0xFF;
	pad->sendbuf[4] = pad->motor2enable ? 0x80 : 0xFF;
	err = psxpad_command(pad, माप(PSX_CMD_ENABLE_MOTOR));
	अगर (err) अणु
		dev_err(&pad->spi->dev,
			"%s: failed to enable motor mode: %d\n",
			__func__, err);
		वापस;
	पूर्ण

	स_नकल(pad->sendbuf, PSX_CMD_EXIT_CFG, माप(PSX_CMD_EXIT_CFG));
	err = psxpad_command(pad, माप(PSX_CMD_EXIT_CFG));
	अगर (err) अणु
		dev_err(&pad->spi->dev,
			"%s: failed to exit config mode: %d\n",
			__func__, err);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम psxpad_set_motor_level(काष्ठा psxpad *pad,
				   u8 motor1level, u8 motor2level)
अणु
	pad->motor1level = motor1level ? 0xFF : 0x00;
	pad->motor2level = REVERSE_BIT(motor2level);
पूर्ण

अटल पूर्णांक psxpad_spi_play_effect(काष्ठा input_dev *idev,
				  व्योम *data, काष्ठा ff_effect *effect)
अणु
	काष्ठा psxpad *pad = input_get_drvdata(idev);

	चयन (effect->type) अणु
	हाल FF_RUMBLE:
		psxpad_set_motor_level(pad,
			(effect->u.rumble.weak_magnitude >> 8) & 0xFFU,
			(effect->u.rumble.strong_magnitude >> 8) & 0xFFU);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psxpad_spi_init_ff(काष्ठा psxpad *pad)
अणु
	पूर्णांक err;

	input_set_capability(pad->idev, EV_FF, FF_RUMBLE);

	err = input_ff_create_memless(pad->idev, शून्य, psxpad_spi_play_effect);
	अगर (err) अणु
		dev_err(&pad->spi->dev,
			"input_ff_create_memless() failed: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा	/* CONFIG_JOYSTICK_PSXPAD_SPI_FF */

अटल व्योम psxpad_control_motor(काष्ठा psxpad *pad,
				 bool motor1enable, bool motor2enable)
अणु
पूर्ण

अटल व्योम psxpad_set_motor_level(काष्ठा psxpad *pad,
				   u8 motor1level, u8 motor2level)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक psxpad_spi_init_ff(काष्ठा psxpad *pad)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_JOYSTICK_PSXPAD_SPI_FF */

अटल पूर्णांक psxpad_spi_poll_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा psxpad *pad = input_get_drvdata(input);

	pm_runसमय_get_sync(&pad->spi->dev);

	वापस 0;
पूर्ण

अटल व्योम psxpad_spi_poll_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा psxpad *pad = input_get_drvdata(input);

	pm_runसमय_put_sync(&pad->spi->dev);
पूर्ण

अटल व्योम psxpad_spi_poll(काष्ठा input_dev *input)
अणु
	काष्ठा psxpad *pad = input_get_drvdata(input);
	u8 b_rsp3, b_rsp4;
	पूर्णांक err;

	psxpad_control_motor(pad, true, true);

	स_नकल(pad->sendbuf, PSX_CMD_POLL, माप(PSX_CMD_POLL));
	pad->sendbuf[3] = pad->motor1enable ? pad->motor1level : 0x00;
	pad->sendbuf[4] = pad->motor2enable ? pad->motor2level : 0x00;
	err = psxpad_command(pad, माप(PSX_CMD_POLL));
	अगर (err) अणु
		dev_err(&pad->spi->dev,
			"%s: poll command failed mode: %d\n", __func__, err);
		वापस;
	पूर्ण

	चयन (pad->response[1]) अणु
	हाल 0xCE:	/* 0x73 : analog 1 */
		/* button data is inverted */
		b_rsp3 = ~pad->response[3];
		b_rsp4 = ~pad->response[4];

		input_report_असल(input, ABS_X, REVERSE_BIT(pad->response[7]));
		input_report_असल(input, ABS_Y, REVERSE_BIT(pad->response[8]));
		input_report_असल(input, ABS_RX, REVERSE_BIT(pad->response[5]));
		input_report_असल(input, ABS_RY, REVERSE_BIT(pad->response[6]));
		input_report_key(input, BTN_DPAD_UP, b_rsp3 & BIT(3));
		input_report_key(input, BTN_DPAD_DOWN, b_rsp3 & BIT(1));
		input_report_key(input, BTN_DPAD_LEFT, b_rsp3 & BIT(0));
		input_report_key(input, BTN_DPAD_RIGHT, b_rsp3 & BIT(2));
		input_report_key(input, BTN_X, b_rsp4 & BIT(3));
		input_report_key(input, BTN_A, b_rsp4 & BIT(2));
		input_report_key(input, BTN_B, b_rsp4 & BIT(1));
		input_report_key(input, BTN_Y, b_rsp4 & BIT(0));
		input_report_key(input, BTN_TL, b_rsp4 & BIT(5));
		input_report_key(input, BTN_TR, b_rsp4 & BIT(4));
		input_report_key(input, BTN_TL2, b_rsp4 & BIT(7));
		input_report_key(input, BTN_TR2, b_rsp4 & BIT(6));
		input_report_key(input, BTN_THUMBL, b_rsp3 & BIT(6));
		input_report_key(input, BTN_THUMBR, b_rsp3 & BIT(5));
		input_report_key(input, BTN_SELECT, b_rsp3 & BIT(7));
		input_report_key(input, BTN_START, b_rsp3 & BIT(4));
		अवरोध;

	हाल 0x82:	/* 0x41 : digital */
		/* button data is inverted */
		b_rsp3 = ~pad->response[3];
		b_rsp4 = ~pad->response[4];

		input_report_असल(input, ABS_X, 0x80);
		input_report_असल(input, ABS_Y, 0x80);
		input_report_असल(input, ABS_RX, 0x80);
		input_report_असल(input, ABS_RY, 0x80);
		input_report_key(input, BTN_DPAD_UP, b_rsp3 & BIT(3));
		input_report_key(input, BTN_DPAD_DOWN, b_rsp3 & BIT(1));
		input_report_key(input, BTN_DPAD_LEFT, b_rsp3 & BIT(0));
		input_report_key(input, BTN_DPAD_RIGHT, b_rsp3 & BIT(2));
		input_report_key(input, BTN_X, b_rsp4 & BIT(3));
		input_report_key(input, BTN_A, b_rsp4 & BIT(2));
		input_report_key(input, BTN_B, b_rsp4 & BIT(1));
		input_report_key(input, BTN_Y, b_rsp4 & BIT(0));
		input_report_key(input, BTN_TL, b_rsp4 & BIT(5));
		input_report_key(input, BTN_TR, b_rsp4 & BIT(4));
		input_report_key(input, BTN_TL2, b_rsp4 & BIT(7));
		input_report_key(input, BTN_TR2, b_rsp4 & BIT(6));
		input_report_key(input, BTN_THUMBL, false);
		input_report_key(input, BTN_THUMBR, false);
		input_report_key(input, BTN_SELECT, b_rsp3 & BIT(7));
		input_report_key(input, BTN_START, b_rsp3 & BIT(4));
		अवरोध;
	पूर्ण

	input_sync(input);
पूर्ण

अटल पूर्णांक psxpad_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा psxpad *pad;
	काष्ठा input_dev *idev;
	पूर्णांक err;

	pad = devm_kzalloc(&spi->dev, माप(काष्ठा psxpad), GFP_KERNEL);
	अगर (!pad)
		वापस -ENOMEM;

	idev = devm_input_allocate_device(&spi->dev);
	अगर (!idev) अणु
		dev_err(&spi->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	/* input poll device settings */
	pad->idev = idev;
	pad->spi = spi;

	/* input device settings */
	input_set_drvdata(idev, pad);

	idev->name = "PlayStation 1/2 joypad";
	snम_लिखो(pad->phys, माप(pad->phys), "%s/input", dev_name(&spi->dev));
	idev->id.bustype = BUS_SPI;

	idev->खोलो = psxpad_spi_poll_खोलो;
	idev->बंद = psxpad_spi_poll_बंद;

	/* key/value map settings */
	input_set_असल_params(idev, ABS_X, 0, 255, 0, 0);
	input_set_असल_params(idev, ABS_Y, 0, 255, 0, 0);
	input_set_असल_params(idev, ABS_RX, 0, 255, 0, 0);
	input_set_असल_params(idev, ABS_RY, 0, 255, 0, 0);
	input_set_capability(idev, EV_KEY, BTN_DPAD_UP);
	input_set_capability(idev, EV_KEY, BTN_DPAD_DOWN);
	input_set_capability(idev, EV_KEY, BTN_DPAD_LEFT);
	input_set_capability(idev, EV_KEY, BTN_DPAD_RIGHT);
	input_set_capability(idev, EV_KEY, BTN_A);
	input_set_capability(idev, EV_KEY, BTN_B);
	input_set_capability(idev, EV_KEY, BTN_X);
	input_set_capability(idev, EV_KEY, BTN_Y);
	input_set_capability(idev, EV_KEY, BTN_TL);
	input_set_capability(idev, EV_KEY, BTN_TR);
	input_set_capability(idev, EV_KEY, BTN_TL2);
	input_set_capability(idev, EV_KEY, BTN_TR2);
	input_set_capability(idev, EV_KEY, BTN_THUMBL);
	input_set_capability(idev, EV_KEY, BTN_THUMBR);
	input_set_capability(idev, EV_KEY, BTN_SELECT);
	input_set_capability(idev, EV_KEY, BTN_START);

	err = psxpad_spi_init_ff(pad);
	अगर (err)
		वापस err;

	/* SPI settings */
	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	/* (PlayStation 1/2 joypad might be possible works 250kHz/500kHz) */
	spi->master->min_speed_hz = 125000;
	spi->master->max_speed_hz = 125000;
	spi_setup(spi);

	/* pad settings */
	psxpad_set_motor_level(pad, 0, 0);


	err = input_setup_polling(idev, psxpad_spi_poll);
	अगर (err) अणु
		dev_err(&spi->dev, "failed to set up polling: %d\n", err);
		वापस err;
	पूर्ण

	/* poll पूर्णांकerval is about 60fps */
	input_set_poll_पूर्णांकerval(idev, 16);
	input_set_min_poll_पूर्णांकerval(idev, 8);
	input_set_max_poll_पूर्णांकerval(idev, 32);

	/* रेजिस्टर input poll device */
	err = input_रेजिस्टर_device(idev);
	अगर (err) अणु
		dev_err(&spi->dev,
			"failed to register input device: %d\n", err);
		वापस err;
	पूर्ण

	pm_runसमय_enable(&spi->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused psxpad_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा psxpad *pad = spi_get_drvdata(spi);

	psxpad_set_motor_level(pad, 0, 0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(psxpad_spi_pm, psxpad_spi_suspend, शून्य);

अटल स्थिर काष्ठा spi_device_id psxpad_spi_id[] = अणु
	अणु "psxpad-spi", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, psxpad_spi_id);

अटल काष्ठा spi_driver psxpad_spi_driver = अणु
	.driver = अणु
		.name = "psxpad-spi",
		.pm = &psxpad_spi_pm,
	पूर्ण,
	.id_table = psxpad_spi_id,
	.probe   = psxpad_spi_probe,
पूर्ण;

module_spi_driver(psxpad_spi_driver);

MODULE_AUTHOR("Tomohiro Yoshidomi <sylph23k@gmail.com>");
MODULE_DESCRIPTION("PlayStation 1/2 joypads via SPI interface Driver");
MODULE_LICENSE("GPL");

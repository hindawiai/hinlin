<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/media/radio/si470x/radio-si470x-i2c.c
 *
 * I2C driver क्रम radios with Silicon Lअसल Si470x FM Radio Receivers
 *
 * Copyright (c) 2009 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */


/* driver definitions */
#घोषणा DRIVER_AUTHOR "Joonyoung Shim <jy0922.shim@samsung.com>";
#घोषणा DRIVER_CARD "Silicon Labs Si470x FM Radio Receiver"
#घोषणा DRIVER_DESC "I2C radio driver for Si470x FM Radio Receivers"
#घोषणा DRIVER_VERSION "1.0.2"

/* kernel includes */
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "radio-si470x.h"


/* I2C Device ID List */
अटल स्थिर काष्ठा i2c_device_id si470x_i2c_id[] = अणु
	/* Generic Entry */
	अणु "si470x", 0 पूर्ण,
	/* Terminating entry */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si470x_i2c_id);


/**************************************************************************
 * Module Parameters
 **************************************************************************/

/* Radio Nr */
अटल पूर्णांक radio_nr = -1;
module_param(radio_nr, पूर्णांक, 0444);
MODULE_PARM_DESC(radio_nr, "Radio Nr");

/* RDS buffer blocks */
अटल अचिन्हित पूर्णांक rds_buf = 100;
module_param(rds_buf, uपूर्णांक, 0444);
MODULE_PARM_DESC(rds_buf, "RDS buffer entries: *100*");

/* RDS maximum block errors */
अटल अचिन्हित लघु max_rds_errors = 1;
/* 0 means   0  errors requiring correction */
/* 1 means 1-2  errors requiring correction (used by original USBRadio.exe) */
/* 2 means 3-5  errors requiring correction */
/* 3 means   6+ errors or errors in checkword, correction not possible */
module_param(max_rds_errors, uलघु, 0644);
MODULE_PARM_DESC(max_rds_errors, "RDS maximum block errors: *1*");



/**************************************************************************
 * I2C Definitions
 **************************************************************************/

/* Write starts with the upper byte of रेजिस्टर 0x02 */
#घोषणा WRITE_REG_NUM		8
#घोषणा WRITE_INDEX(i)		(i + 0x02)

/* Read starts with the upper byte of रेजिस्टर 0x0a */
#घोषणा READ_REG_NUM		RADIO_REGISTER_NUM
#घोषणा READ_INDEX(i)		((i + RADIO_REGISTER_NUM - 0x0a) % READ_REG_NUM)



/**************************************************************************
 * General Driver Functions - REGISTERs
 **************************************************************************/

/*
 * si470x_get_रेजिस्टर - पढ़ो रेजिस्टर
 */
अटल पूर्णांक si470x_get_रेजिस्टर(काष्ठा si470x_device *radio, पूर्णांक regnr)
अणु
	__be16 buf[READ_REG_NUM];
	काष्ठा i2c_msg msgs[1] = अणु
		अणु
			.addr = radio->client->addr,
			.flags = I2C_M_RD,
			.len = माप(u16) * READ_REG_NUM,
			.buf = (व्योम *)buf
		पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(radio->client->adapter, msgs, 1) != 1)
		वापस -EIO;

	radio->रेजिस्टरs[regnr] = __be16_to_cpu(buf[READ_INDEX(regnr)]);

	वापस 0;
पूर्ण


/*
 * si470x_set_रेजिस्टर - ग_लिखो रेजिस्टर
 */
अटल पूर्णांक si470x_set_रेजिस्टर(काष्ठा si470x_device *radio, पूर्णांक regnr)
अणु
	पूर्णांक i;
	__be16 buf[WRITE_REG_NUM];
	काष्ठा i2c_msg msgs[1] = अणु
		अणु
			.addr = radio->client->addr,
			.len = माप(u16) * WRITE_REG_NUM,
			.buf = (व्योम *)buf
		पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < WRITE_REG_NUM; i++)
		buf[i] = __cpu_to_be16(radio->रेजिस्टरs[WRITE_INDEX(i)]);

	अगर (i2c_transfer(radio->client->adapter, msgs, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण



/**************************************************************************
 * General Driver Functions - ENTIRE REGISTERS
 **************************************************************************/

/*
 * si470x_get_all_रेजिस्टरs - पढ़ो entire रेजिस्टरs
 */
अटल पूर्णांक si470x_get_all_रेजिस्टरs(काष्ठा si470x_device *radio)
अणु
	पूर्णांक i;
	__be16 buf[READ_REG_NUM];
	काष्ठा i2c_msg msgs[1] = अणु
		अणु
			.addr = radio->client->addr,
			.flags = I2C_M_RD,
			.len = माप(u16) * READ_REG_NUM,
			.buf = (व्योम *)buf
		पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(radio->client->adapter, msgs, 1) != 1)
		वापस -EIO;

	क्रम (i = 0; i < READ_REG_NUM; i++)
		radio->रेजिस्टरs[i] = __be16_to_cpu(buf[READ_INDEX(i)]);

	वापस 0;
पूर्ण



/**************************************************************************
 * File Operations Interface
 **************************************************************************/

/*
 * si470x_fops_खोलो - file खोलो
 */
अटल पूर्णांक si470x_fops_खोलो(काष्ठा file *file)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);
	पूर्णांक retval = v4l2_fh_खोलो(file);

	अगर (retval)
		वापस retval;

	अगर (v4l2_fh_is_singular_file(file)) अणु
		/* start radio */
		retval = si470x_start(radio);
		अगर (retval < 0)
			जाओ करोne;

		/* enable RDS / STC पूर्णांकerrupt */
		radio->रेजिस्टरs[SYSCONFIG1] |= SYSCONFIG1_RDSIEN;
		radio->रेजिस्टरs[SYSCONFIG1] |= SYSCONFIG1_STCIEN;
		radio->रेजिस्टरs[SYSCONFIG1] &= ~SYSCONFIG1_GPIO2;
		radio->रेजिस्टरs[SYSCONFIG1] |= 0x1 << 2;
		retval = si470x_set_रेजिस्टर(radio, SYSCONFIG1);
	पूर्ण

करोne:
	अगर (retval)
		v4l2_fh_release(file);
	वापस retval;
पूर्ण


/*
 * si470x_fops_release - file release
 */
अटल पूर्णांक si470x_fops_release(काष्ठा file *file)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);

	अगर (v4l2_fh_is_singular_file(file))
		/* stop radio */
		si470x_stop(radio);

	वापस v4l2_fh_release(file);
पूर्ण



/**************************************************************************
 * Video4Linux Interface
 **************************************************************************/

/*
 * si470x_vidioc_querycap - query device capabilities
 */
अटल पूर्णांक si470x_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_capability *capability)
अणु
	strscpy(capability->driver, DRIVER_NAME, माप(capability->driver));
	strscpy(capability->card, DRIVER_CARD, माप(capability->card));
	वापस 0;
पूर्ण



/**************************************************************************
 * I2C Interface
 **************************************************************************/

/*
 * si470x_i2c_पूर्णांकerrupt - पूर्णांकerrupt handler
 */
अटल irqवापस_t si470x_i2c_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा si470x_device *radio = dev_id;
	अचिन्हित अक्षर regnr;
	अचिन्हित अक्षर blocknum;
	अचिन्हित लघु bler; /* rds block errors */
	अचिन्हित लघु rds;
	अचिन्हित अक्षर पंचांगpbuf[3];
	पूर्णांक retval = 0;

	/* check Seek/Tune Complete */
	retval = si470x_get_रेजिस्टर(radio, STATUSRSSI);
	अगर (retval < 0)
		जाओ end;

	अगर (radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_STC)
		complete(&radio->completion);

	/* safety checks */
	अगर ((radio->रेजिस्टरs[SYSCONFIG1] & SYSCONFIG1_RDS) == 0)
		जाओ end;

	/* Update RDS रेजिस्टरs */
	क्रम (regnr = 1; regnr < RDS_REGISTER_NUM; regnr++) अणु
		retval = si470x_get_रेजिस्टर(radio, STATUSRSSI + regnr);
		अगर (retval < 0)
			जाओ end;
	पूर्ण

	/* get rds blocks */
	अगर ((radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_RDSR) == 0)
		/* No RDS group पढ़ोy, better luck next समय */
		जाओ end;

	क्रम (blocknum = 0; blocknum < 4; blocknum++) अणु
		चयन (blocknum) अणु
		शेष:
			bler = (radio->रेजिस्टरs[STATUSRSSI] &
					STATUSRSSI_BLERA) >> 9;
			rds = radio->रेजिस्टरs[RDSA];
			अवरोध;
		हाल 1:
			bler = (radio->रेजिस्टरs[READCHAN] &
					READCHAN_BLERB) >> 14;
			rds = radio->रेजिस्टरs[RDSB];
			अवरोध;
		हाल 2:
			bler = (radio->रेजिस्टरs[READCHAN] &
					READCHAN_BLERC) >> 12;
			rds = radio->रेजिस्टरs[RDSC];
			अवरोध;
		हाल 3:
			bler = (radio->रेजिस्टरs[READCHAN] &
					READCHAN_BLERD) >> 10;
			rds = radio->रेजिस्टरs[RDSD];
			अवरोध;
		पूर्ण

		/* Fill the V4L2 RDS buffer */
		put_unaligned_le16(rds, &पंचांगpbuf);
		पंचांगpbuf[2] = blocknum;		/* offset name */
		पंचांगpbuf[2] |= blocknum << 3;	/* received offset */
		अगर (bler > max_rds_errors)
			पंचांगpbuf[2] |= 0x80;	/* uncorrectable errors */
		अन्यथा अगर (bler > 0)
			पंचांगpbuf[2] |= 0x40;	/* corrected error(s) */

		/* copy RDS block to पूर्णांकernal buffer */
		स_नकल(&radio->buffer[radio->wr_index], &पंचांगpbuf, 3);
		radio->wr_index += 3;

		/* wrap ग_लिखो poपूर्णांकer */
		अगर (radio->wr_index >= radio->buf_size)
			radio->wr_index = 0;

		/* check क्रम overflow */
		अगर (radio->wr_index == radio->rd_index) अणु
			/* increment and wrap पढ़ो poपूर्णांकer */
			radio->rd_index += 3;
			अगर (radio->rd_index >= radio->buf_size)
				radio->rd_index = 0;
		पूर्ण
	पूर्ण

	अगर (radio->wr_index != radio->rd_index)
		wake_up_पूर्णांकerruptible(&radio->पढ़ो_queue);

end:
	वापस IRQ_HANDLED;
पूर्ण


/*
 * si470x_i2c_probe - probe क्रम the device
 */
अटल पूर्णांक si470x_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा si470x_device *radio;
	पूर्णांक retval = 0;
	अचिन्हित अक्षर version_warning = 0;

	/* निजी data allocation and initialization */
	radio = devm_kzalloc(&client->dev, माप(*radio), GFP_KERNEL);
	अगर (!radio) अणु
		retval = -ENOMEM;
		जाओ err_initial;
	पूर्ण

	radio->client = client;
	radio->band = 1; /* Default to 76 - 108 MHz */
	mutex_init(&radio->lock);
	init_completion(&radio->completion);

	radio->get_रेजिस्टर = si470x_get_रेजिस्टर;
	radio->set_रेजिस्टर = si470x_set_रेजिस्टर;
	radio->fops_खोलो = si470x_fops_खोलो;
	radio->fops_release = si470x_fops_release;
	radio->vidioc_querycap = si470x_vidioc_querycap;

	retval = v4l2_device_रेजिस्टर(&client->dev, &radio->v4l2_dev);
	अगर (retval < 0) अणु
		dev_err(&client->dev, "couldn't register v4l2_device\n");
		जाओ err_initial;
	पूर्ण

	v4l2_ctrl_handler_init(&radio->hdl, 2);
	v4l2_ctrl_new_std(&radio->hdl, &si470x_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&radio->hdl, &si470x_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 15, 1, 15);
	अगर (radio->hdl.error) अणु
		retval = radio->hdl.error;
		dev_err(&client->dev, "couldn't register control\n");
		जाओ err_dev;
	पूर्ण

	/* video device initialization */
	radio->videodev = si470x_viddev_ढाँचा;
	radio->videodev.ctrl_handler = &radio->hdl;
	radio->videodev.lock = &radio->lock;
	radio->videodev.v4l2_dev = &radio->v4l2_dev;
	radio->videodev.release = video_device_release_empty;
	radio->videodev.device_caps =
		V4L2_CAP_HW_FREQ_SEEK | V4L2_CAP_READWRITE | V4L2_CAP_TUNER |
		V4L2_CAP_RADIO | V4L2_CAP_RDS_CAPTURE;
	video_set_drvdata(&radio->videodev, radio);

	radio->gpio_reset = devm_gpiod_get_optional(&client->dev, "reset",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(radio->gpio_reset)) अणु
		retval = PTR_ERR(radio->gpio_reset);
		dev_err(&client->dev, "Failed to request gpio: %d\n", retval);
		जाओ err_all;
	पूर्ण

	अगर (radio->gpio_reset)
		gpiod_set_value(radio->gpio_reset, 1);

	/* घातer up : need 110ms */
	radio->रेजिस्टरs[POWERCFG] = POWERCFG_ENABLE;
	अगर (si470x_set_रेजिस्टर(radio, POWERCFG) < 0) अणु
		retval = -EIO;
		जाओ err_all;
	पूर्ण
	msleep(110);

	/* get device and chip versions */
	अगर (si470x_get_all_रेजिस्टरs(radio) < 0) अणु
		retval = -EIO;
		जाओ err_all;
	पूर्ण
	dev_info(&client->dev, "DeviceID=0x%4.4hx ChipID=0x%4.4hx\n",
			radio->रेजिस्टरs[DEVICEID], radio->रेजिस्टरs[SI_CHIPID]);
	अगर ((radio->रेजिस्टरs[SI_CHIPID] & SI_CHIPID_FIRMWARE) < RADIO_FW_VERSION) अणु
		dev_warn(&client->dev,
			"This driver is known to work with firmware version %hu,\n",
			RADIO_FW_VERSION);
		dev_warn(&client->dev,
			"but the device has firmware version %hu.\n",
			radio->रेजिस्टरs[SI_CHIPID] & SI_CHIPID_FIRMWARE);
		version_warning = 1;
	पूर्ण

	/* give out version warning */
	अगर (version_warning == 1) अणु
		dev_warn(&client->dev,
			"If you have some trouble using this driver,\n");
		dev_warn(&client->dev,
			"please report to V4L ML at linux-media@vger.kernel.org\n");
	पूर्ण

	/* set initial frequency */
	si470x_set_freq(radio, 87.5 * FREQ_MUL); /* available in all regions */

	/* rds buffer allocation */
	radio->buf_size = rds_buf * 3;
	radio->buffer = devm_kदो_स्मृति(&client->dev, radio->buf_size, GFP_KERNEL);
	अगर (!radio->buffer) अणु
		retval = -EIO;
		जाओ err_all;
	पूर्ण

	/* rds buffer configuration */
	radio->wr_index = 0;
	radio->rd_index = 0;
	init_रुकोqueue_head(&radio->पढ़ो_queue);

	retval = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					   si470x_i2c_पूर्णांकerrupt,
					   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					   DRIVER_NAME, radio);
	अगर (retval) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		जाओ err_all;
	पूर्ण

	/* रेजिस्टर video device */
	retval = video_रेजिस्टर_device(&radio->videodev, VFL_TYPE_RADIO,
			radio_nr);
	अगर (retval) अणु
		dev_warn(&client->dev, "Could not register video device\n");
		जाओ err_all;
	पूर्ण
	i2c_set_clientdata(client, radio);

	वापस 0;
err_all:
	v4l2_ctrl_handler_मुक्त(&radio->hdl);
err_dev:
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
err_initial:
	वापस retval;
पूर्ण


/*
 * si470x_i2c_हटाओ - हटाओ the device
 */
अटल पूर्णांक si470x_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा si470x_device *radio = i2c_get_clientdata(client);

	video_unरेजिस्टर_device(&radio->videodev);

	अगर (radio->gpio_reset)
		gpiod_set_value(radio->gpio_reset, 0);

	v4l2_ctrl_handler_मुक्त(&radio->hdl);
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_PM_SLEEP
/*
 * si470x_i2c_suspend - suspend the device
 */
अटल पूर्णांक si470x_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा si470x_device *radio = i2c_get_clientdata(client);

	/* घातer करोwn */
	radio->रेजिस्टरs[POWERCFG] |= POWERCFG_DISABLE;
	अगर (si470x_set_रेजिस्टर(radio, POWERCFG) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण


/*
 * si470x_i2c_resume - resume the device
 */
अटल पूर्णांक si470x_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा si470x_device *radio = i2c_get_clientdata(client);

	/* घातer up : need 110ms */
	radio->रेजिस्टरs[POWERCFG] |= POWERCFG_ENABLE;
	अगर (si470x_set_रेजिस्टर(radio, POWERCFG) < 0)
		वापस -EIO;
	msleep(110);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(si470x_i2c_pm, si470x_i2c_suspend, si470x_i2c_resume);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id si470x_of_match[] = अणु
	अणु .compatible = "silabs,si470x" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, si470x_of_match);
#पूर्ण_अगर

/*
 * si470x_i2c_driver - i2c driver पूर्णांकerface
 */
अटल काष्ठा i2c_driver si470x_i2c_driver = अणु
	.driver = अणु
		.name		= "si470x",
		.of_match_table = of_match_ptr(si470x_of_match),
#अगर_घोषित CONFIG_PM_SLEEP
		.pm		= &si470x_i2c_pm,
#पूर्ण_अगर
	पूर्ण,
	.probe_new		= si470x_i2c_probe,
	.हटाओ			= si470x_i2c_हटाओ,
	.id_table		= si470x_i2c_id,
पूर्ण;

module_i2c_driver(si470x_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);

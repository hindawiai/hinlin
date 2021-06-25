<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	SEGA Dreamcast controller driver
 *	Based on drivers/usb/अगरorce.c
 *
 *	Copyright Yaegashi Takeshi, 2001
 *	Adrian McMenamin, 2008 - 2009
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/maple.h>

MODULE_AUTHOR("Adrian McMenamin <adrian@mcmen.demon.co.uk>");
MODULE_DESCRIPTION("SEGA Dreamcast controller driver");
MODULE_LICENSE("GPL");

काष्ठा dc_pad अणु
	काष्ठा input_dev *dev;
	काष्ठा maple_device *mdev;
पूर्ण;

अटल व्योम dc_pad_callback(काष्ठा mapleq *mq)
अणु
	अचिन्हित लघु buttons;
	काष्ठा maple_device *mapledev = mq->dev;
	काष्ठा dc_pad *pad = maple_get_drvdata(mapledev);
	काष्ठा input_dev *dev = pad->dev;
	अचिन्हित अक्षर *res = mq->recvbuf->buf;

	buttons = ~le16_to_cpup((__le16 *)(res + 8));

	input_report_असल(dev, ABS_HAT0Y,
		(buttons & 0x0010 ? -1 : 0) + (buttons & 0x0020 ? 1 : 0));
	input_report_असल(dev, ABS_HAT0X,
		(buttons & 0x0040 ? -1 : 0) + (buttons & 0x0080 ? 1 : 0));
	input_report_असल(dev, ABS_HAT1Y,
		(buttons & 0x1000 ? -1 : 0) + (buttons & 0x2000 ? 1 : 0));
	input_report_असल(dev, ABS_HAT1X,
		(buttons & 0x4000 ? -1 : 0) + (buttons & 0x8000 ? 1 : 0));

	input_report_key(dev, BTN_C,      buttons & 0x0001);
	input_report_key(dev, BTN_B,      buttons & 0x0002);
	input_report_key(dev, BTN_A,      buttons & 0x0004);
	input_report_key(dev, BTN_START,  buttons & 0x0008);
	input_report_key(dev, BTN_Z,      buttons & 0x0100);
	input_report_key(dev, BTN_Y,      buttons & 0x0200);
	input_report_key(dev, BTN_X,      buttons & 0x0400);
	input_report_key(dev, BTN_SELECT, buttons & 0x0800);

	input_report_असल(dev, ABS_GAS,    res[10]);
	input_report_असल(dev, ABS_BRAKE,  res[11]);
	input_report_असल(dev, ABS_X,      res[12]);
	input_report_असल(dev, ABS_Y,      res[13]);
	input_report_असल(dev, ABS_RX,     res[14]);
	input_report_असल(dev, ABS_RY,     res[15]);
पूर्ण

अटल पूर्णांक dc_pad_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा dc_pad *pad = dev_get_platdata(&dev->dev);

	maple_अ_लोond_callback(pad->mdev, dc_pad_callback, HZ/20,
		MAPLE_FUNC_CONTROLLER);

	वापस 0;
पूर्ण

अटल व्योम dc_pad_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा dc_pad *pad = dev_get_platdata(&dev->dev);

	maple_अ_लोond_callback(pad->mdev, dc_pad_callback, 0,
		MAPLE_FUNC_CONTROLLER);
पूर्ण

/* allow the controller to be used */
अटल पूर्णांक probe_maple_controller(काष्ठा device *dev)
अणु
	अटल स्थिर लघु btn_bit[32] = अणु
		BTN_C, BTN_B, BTN_A, BTN_START, -1, -1, -1, -1,
		BTN_Z, BTN_Y, BTN_X, BTN_SELECT, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
	पूर्ण;

	अटल स्थिर लघु असल_bit[32] = अणु
		-1, -1, -1, -1, ABS_HAT0Y, ABS_HAT0Y, ABS_HAT0X, ABS_HAT0X,
		-1, -1, -1, -1, ABS_HAT1Y, ABS_HAT1Y, ABS_HAT1X, ABS_HAT1X,
		ABS_GAS, ABS_BRAKE, ABS_X, ABS_Y, ABS_RX, ABS_RY, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
	पूर्ण;

	काष्ठा maple_device *mdev = to_maple_dev(dev);
	काष्ठा maple_driver *mdrv = to_maple_driver(dev->driver);
	पूर्णांक i, error;
	काष्ठा dc_pad *pad;
	काष्ठा input_dev *idev;
	अचिन्हित दीर्घ data = be32_to_cpu(mdev->devinfo.function_data[0]);

	pad = kzalloc(माप(काष्ठा dc_pad), GFP_KERNEL);
	idev = input_allocate_device();
	अगर (!pad || !idev) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण

	pad->dev = idev;
	pad->mdev = mdev;

	idev->खोलो = dc_pad_खोलो;
	idev->बंद = dc_pad_बंद;

	क्रम (i = 0; i < 32; i++) अणु
		अगर (data & (1 << i)) अणु
			अगर (btn_bit[i] >= 0)
				__set_bit(btn_bit[i], idev->keybit);
			अन्यथा अगर (असल_bit[i] >= 0)
				__set_bit(असल_bit[i], idev->असलbit);
		पूर्ण
	पूर्ण

	अगर (idev->keybit[BIT_WORD(BTN_JOYSTICK)])
		idev->evbit[0] |= BIT_MASK(EV_KEY);

	अगर (idev->असलbit[0])
		idev->evbit[0] |= BIT_MASK(EV_ABS);

	क्रम (i = ABS_X; i <= ABS_BRAKE; i++)
		input_set_असल_params(idev, i, 0, 255, 0, 0);

	क्रम (i = ABS_HAT0X; i <= ABS_HAT3Y; i++)
		input_set_असल_params(idev, i, 1, -1, 0, 0);

	idev->dev.platक्रमm_data = pad;
	idev->dev.parent = &mdev->dev;
	idev->name = mdev->product_name;
	idev->id.bustype = BUS_HOST;

	error = input_रेजिस्टर_device(idev);
	अगर (error)
		जाओ fail;

	mdev->driver = mdrv;
	maple_set_drvdata(mdev, pad);

	वापस 0;

fail:
	input_मुक्त_device(idev);
	kमुक्त(pad);
	maple_set_drvdata(mdev, शून्य);
	वापस error;
पूर्ण

अटल पूर्णांक हटाओ_maple_controller(काष्ठा device *dev)
अणु
	काष्ठा maple_device *mdev = to_maple_dev(dev);
	काष्ठा dc_pad *pad = maple_get_drvdata(mdev);

	mdev->callback = शून्य;
	input_unरेजिस्टर_device(pad->dev);
	maple_set_drvdata(mdev, शून्य);
	kमुक्त(pad);

	वापस 0;
पूर्ण

अटल काष्ठा maple_driver dc_pad_driver = अणु
	.function =	MAPLE_FUNC_CONTROLLER,
	.drv = अणु
		.name	= "Dreamcast_controller",
		.probe	= probe_maple_controller,
		.हटाओ	= हटाओ_maple_controller,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dc_pad_init(व्योम)
अणु
	वापस maple_driver_रेजिस्टर(&dc_pad_driver);
पूर्ण

अटल व्योम __निकास dc_pad_निकास(व्योम)
अणु
	maple_driver_unरेजिस्टर(&dc_pad_driver);
पूर्ण

module_init(dc_pad_init);
module_निकास(dc_pad_निकास);

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	SEGA Dreamcast mouse driver
 *	Based on drivers/usb/usbmouse.c
 *
 *	Copyright (c) Yaegashi Takeshi, 2001
 *	Copyright (c) Adrian McMenamin, 2008 - 2009
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/maple.h>

MODULE_AUTHOR("Adrian McMenamin <adrian@mcmen.demon.co.uk>");
MODULE_DESCRIPTION("SEGA Dreamcast mouse driver");
MODULE_LICENSE("GPL");

काष्ठा dc_mouse अणु
	काष्ठा input_dev *dev;
	काष्ठा maple_device *mdev;
पूर्ण;

अटल व्योम dc_mouse_callback(काष्ठा mapleq *mq)
अणु
	पूर्णांक buttons, relx, rely, relz;
	काष्ठा maple_device *mapledev = mq->dev;
	काष्ठा dc_mouse *mse = maple_get_drvdata(mapledev);
	काष्ठा input_dev *dev = mse->dev;
	अचिन्हित अक्षर *res = mq->recvbuf->buf;

	buttons = ~res[8];
	relx = *(अचिन्हित लघु *)(res + 12) - 512;
	rely = *(अचिन्हित लघु *)(res + 14) - 512;
	relz = *(अचिन्हित लघु *)(res + 16) - 512;

	input_report_key(dev, BTN_LEFT,   buttons & 4);
	input_report_key(dev, BTN_MIDDLE, buttons & 9);
	input_report_key(dev, BTN_RIGHT,  buttons & 2);
	input_report_rel(dev, REL_X,      relx);
	input_report_rel(dev, REL_Y,      rely);
	input_report_rel(dev, REL_WHEEL,  relz);
	input_sync(dev);
पूर्ण

अटल पूर्णांक dc_mouse_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा dc_mouse *mse = maple_get_drvdata(to_maple_dev(&dev->dev));

	maple_अ_लोond_callback(mse->mdev, dc_mouse_callback, HZ/50,
		MAPLE_FUNC_MOUSE);

	वापस 0;
पूर्ण

अटल व्योम dc_mouse_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा dc_mouse *mse = maple_get_drvdata(to_maple_dev(&dev->dev));

	maple_अ_लोond_callback(mse->mdev, dc_mouse_callback, 0,
		MAPLE_FUNC_MOUSE);
पूर्ण

/* allow the mouse to be used */
अटल पूर्णांक probe_maple_mouse(काष्ठा device *dev)
अणु
	काष्ठा maple_device *mdev = to_maple_dev(dev);
	काष्ठा maple_driver *mdrv = to_maple_driver(dev->driver);
	पूर्णांक error;
	काष्ठा input_dev *input_dev;
	काष्ठा dc_mouse *mse;

	mse = kzalloc(माप(काष्ठा dc_mouse), GFP_KERNEL);
	अगर (!mse) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		error = -ENOMEM;
		जाओ fail_nomem;
	पूर्ण

	mse->dev = input_dev;
	mse->mdev = mdev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	input_dev->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_RIGHT) | BIT_MASK(BTN_MIDDLE);
	input_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y) |
		BIT_MASK(REL_WHEEL);
	input_dev->खोलो = dc_mouse_खोलो;
	input_dev->बंद = dc_mouse_बंद;
	input_dev->name = mdev->product_name;
	input_dev->id.bustype = BUS_HOST;
	error =	input_रेजिस्टर_device(input_dev);
	अगर (error)
		जाओ fail_रेजिस्टर;

	mdev->driver = mdrv;
	maple_set_drvdata(mdev, mse);

	वापस error;

fail_रेजिस्टर:
	input_मुक्त_device(input_dev);
fail_nomem:
	kमुक्त(mse);
fail:
	वापस error;
पूर्ण

अटल पूर्णांक हटाओ_maple_mouse(काष्ठा device *dev)
अणु
	काष्ठा maple_device *mdev = to_maple_dev(dev);
	काष्ठा dc_mouse *mse = maple_get_drvdata(mdev);

	mdev->callback = शून्य;
	input_unरेजिस्टर_device(mse->dev);
	maple_set_drvdata(mdev, शून्य);
	kमुक्त(mse);

	वापस 0;
पूर्ण

अटल काष्ठा maple_driver dc_mouse_driver = अणु
	.function =	MAPLE_FUNC_MOUSE,
	.drv = अणु
		.name = "Dreamcast_mouse",
		.probe = probe_maple_mouse,
		.हटाओ = हटाओ_maple_mouse,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dc_mouse_init(व्योम)
अणु
	वापस maple_driver_रेजिस्टर(&dc_mouse_driver);
पूर्ण

अटल व्योम __निकास dc_mouse_निकास(व्योम)
अणु
	maple_driver_unरेजिस्टर(&dc_mouse_driver);
पूर्ण

module_init(dc_mouse_init);
module_निकास(dc_mouse_निकास);

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EETI Egalax serial touchscreen driver
 *
 * Copyright (c) 2015 Zoltथँn Bथघszथघrmथऊnyi <zboszor@pr.hu>
 *
 * based on the
 *
 * Hampshire serial touchscreen driver (Copyright (c) 2010 Adam Bennett)
 */


#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC	"EETI Egalax serial touchscreen driver"

/*
 * Definitions & global arrays.
 */

#घोषणा EGALAX_FORMAT_MAX_LENGTH	6
#घोषणा EGALAX_FORMAT_START_BIT		BIT(7)
#घोषणा EGALAX_FORMAT_PRESSURE_BIT	BIT(6)
#घोषणा EGALAX_FORMAT_TOUCH_BIT		BIT(0)
#घोषणा EGALAX_FORMAT_RESOLUTION_MASK	0x06

#घोषणा EGALAX_MIN_XC			0
#घोषणा EGALAX_MAX_XC			0x4000
#घोषणा EGALAX_MIN_YC			0
#घोषणा EGALAX_MAX_YC			0x4000

/*
 * Per-touchscreen data.
 */
काष्ठा egalax अणु
	काष्ठा input_dev *input;
	काष्ठा serio *serio;
	पूर्णांक idx;
	u8 data[EGALAX_FORMAT_MAX_LENGTH];
	अक्षर phys[32];
पूर्ण;

अटल व्योम egalax_process_data(काष्ठा egalax *egalax)
अणु
	काष्ठा input_dev *dev = egalax->input;
	u8 *data = egalax->data;
	u16 x, y;
	u8 shअगरt;
	u8 mask;

	shअगरt = 3 - ((data[0] & EGALAX_FORMAT_RESOLUTION_MASK) >> 1);
	mask = 0xff >> (shअगरt + 1);

	x = (((u16)(data[1] & mask) << 7) | (data[2] & 0x7f)) << shअगरt;
	y = (((u16)(data[3] & mask) << 7) | (data[4] & 0x7f)) << shअगरt;

	input_report_key(dev, BTN_TOUCH, data[0] & EGALAX_FORMAT_TOUCH_BIT);
	input_report_असल(dev, ABS_X, x);
	input_report_असल(dev, ABS_Y, y);
	input_sync(dev);
पूर्ण

अटल irqवापस_t egalax_पूर्णांकerrupt(काष्ठा serio *serio,
				    अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा egalax *egalax = serio_get_drvdata(serio);
	पूर्णांक pkt_len;

	egalax->data[egalax->idx++] = data;

	अगर (likely(egalax->data[0] & EGALAX_FORMAT_START_BIT)) अणु
		pkt_len = egalax->data[0] & EGALAX_FORMAT_PRESSURE_BIT ? 6 : 5;
		अगर (pkt_len == egalax->idx) अणु
			egalax_process_data(egalax);
			egalax->idx = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&serio->dev, "unknown/unsynchronized data: %x\n",
			egalax->data[0]);
		egalax->idx = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * egalax_connect() is the routine that is called when someone adds a
 * new serio device that supports egalax protocol and रेजिस्टरs it as
 * an input device. This is usually accomplished using inputattach.
 */
अटल पूर्णांक egalax_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा egalax *egalax;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	egalax = kzalloc(माप(काष्ठा egalax), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!egalax || !input_dev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	egalax->serio = serio;
	egalax->input = input_dev;
	snम_लिखो(egalax->phys, माप(egalax->phys),
		 "%s/input0", serio->phys);

	input_dev->name = "EETI eGalaxTouch Serial TouchScreen";
	input_dev->phys = egalax->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->id.venकरोr = SERIO_EGALAX;
	input_dev->id.product = 0;
	input_dev->id.version = 0x0001;
	input_dev->dev.parent = &serio->dev;

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X,
			     EGALAX_MIN_XC, EGALAX_MAX_XC, 0, 0);
	input_set_असल_params(input_dev, ABS_Y,
			     EGALAX_MIN_YC, EGALAX_MAX_YC, 0, 0);

	serio_set_drvdata(serio, egalax);

	error = serio_खोलो(serio, drv);
	अगर (error)
		जाओ err_reset_drvdata;

	error = input_रेजिस्टर_device(input_dev);
	अगर (error)
		जाओ err_बंद_serio;

	वापस 0;

err_बंद_serio:
	serio_बंद(serio);
err_reset_drvdata:
	serio_set_drvdata(serio, शून्य);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(egalax);
	वापस error;
पूर्ण

अटल व्योम egalax_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा egalax *egalax = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(egalax->input);
	kमुक्त(egalax);
पूर्ण

/*
 * The serio driver काष्ठाure.
 */

अटल स्थिर काष्ठा serio_device_id egalax_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_EGALAX,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, egalax_serio_ids);

अटल काष्ठा serio_driver egalax_drv = अणु
	.driver		= अणु
		.name	= "egalax",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= egalax_serio_ids,
	.पूर्णांकerrupt	= egalax_पूर्णांकerrupt,
	.connect	= egalax_connect,
	.disconnect	= egalax_disconnect,
पूर्ण;
module_serio_driver(egalax_drv);

MODULE_AUTHOR("Zoltथँn Bथघszथघrmथऊnyi <zboszor@pr.hu>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");

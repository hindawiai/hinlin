<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 */

/*
 * Creative Lअसल Blaster GamePad Cobra driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/input.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"Creative Labs Blaster GamePad Cobra driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा COBRA_MAX_STROBE	45	/* 45 us max रुको क्रम first strobe */
#घोषणा COBRA_LENGTH		36

अटल पूर्णांक cobra_btn[] = अणु BTN_START, BTN_SELECT, BTN_TL, BTN_TR, BTN_X, BTN_Y, BTN_Z, BTN_A, BTN_B, BTN_C, BTN_TL2, BTN_TR2, 0 पूर्ण;

काष्ठा cobra अणु
	काष्ठा gameport *gameport;
	काष्ठा input_dev *dev[2];
	पूर्णांक पढ़ोs;
	पूर्णांक bads;
	अचिन्हित अक्षर exists;
	अक्षर phys[2][32];
पूर्ण;

अटल अचिन्हित अक्षर cobra_पढ़ो_packet(काष्ठा gameport *gameport, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर u, v, w;
	__u64 buf[2];
	पूर्णांक r[2], t[2];
	पूर्णांक i, j, ret;

	पूर्णांक strobe = gameport_समय(gameport, COBRA_MAX_STROBE);

	क्रम (i = 0; i < 2; i++) अणु
		r[i] = buf[i] = 0;
		t[i] = COBRA_MAX_STROBE;
	पूर्ण

	local_irq_save(flags);

	u = gameport_पढ़ो(gameport);

	करो अणु
		t[0]--; t[1]--;
		v = gameport_पढ़ो(gameport);
		क्रम (i = 0, w = u ^ v; i < 2 && w; i++, w >>= 2)
			अगर (w & 0x30) अणु
				अगर ((w & 0x30) < 0x30 && r[i] < COBRA_LENGTH && t[i] > 0) अणु
					buf[i] |= (__u64)((w >> 5) & 1) << r[i]++;
					t[i] = strobe;
					u = v;
				पूर्ण अन्यथा t[i] = 0;
			पूर्ण
	पूर्ण जबतक (t[0] > 0 || t[1] > 0);

	local_irq_restore(flags);

	ret = 0;

	क्रम (i = 0; i < 2; i++) अणु

		अगर (r[i] != COBRA_LENGTH) जारी;

		क्रम (j = 0; j < COBRA_LENGTH && (buf[i] & 0x04104107f) ^ 0x041041040; j++)
			buf[i] = (buf[i] >> 1) | ((__u64)(buf[i] & 1) << (COBRA_LENGTH - 1));

		अगर (j < COBRA_LENGTH) ret |= (1 << i);

		data[i] = ((buf[i] >>  7) & 0x000001f) | ((buf[i] >>  8) & 0x00003e0)
			| ((buf[i] >>  9) & 0x0007c00) | ((buf[i] >> 10) & 0x00f8000)
			| ((buf[i] >> 11) & 0x1f00000);

	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cobra_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा cobra *cobra = gameport_get_drvdata(gameport);
	काष्ठा input_dev *dev;
	अचिन्हित पूर्णांक data[2];
	पूर्णांक i, j, r;

	cobra->पढ़ोs++;

	अगर ((r = cobra_पढ़ो_packet(gameport, data)) != cobra->exists) अणु
		cobra->bads++;
		वापस;
	पूर्ण

	क्रम (i = 0; i < 2; i++)
		अगर (cobra->exists & r & (1 << i)) अणु

			dev = cobra->dev[i];

			input_report_असल(dev, ABS_X, ((data[i] >> 4) & 1) - ((data[i] >> 3) & 1));
			input_report_असल(dev, ABS_Y, ((data[i] >> 2) & 1) - ((data[i] >> 1) & 1));

			क्रम (j = 0; cobra_btn[j]; j++)
				input_report_key(dev, cobra_btn[j], data[i] & (0x20 << j));

			input_sync(dev);

		पूर्ण
पूर्ण

अटल पूर्णांक cobra_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा cobra *cobra = input_get_drvdata(dev);

	gameport_start_polling(cobra->gameport);
	वापस 0;
पूर्ण

अटल व्योम cobra_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा cobra *cobra = input_get_drvdata(dev);

	gameport_stop_polling(cobra->gameport);
पूर्ण

अटल पूर्णांक cobra_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा cobra *cobra;
	काष्ठा input_dev *input_dev;
	अचिन्हित पूर्णांक data[2];
	पूर्णांक i, j;
	पूर्णांक err;

	cobra = kzalloc(माप(काष्ठा cobra), GFP_KERNEL);
	अगर (!cobra)
		वापस -ENOMEM;

	cobra->gameport = gameport;

	gameport_set_drvdata(gameport, cobra);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	cobra->exists = cobra_पढ़ो_packet(gameport, data);

	क्रम (i = 0; i < 2; i++)
		अगर ((cobra->exists >> i) & data[i] & 1) अणु
			prपूर्णांकk(KERN_WARNING "cobra.c: Device %d on %s has the Ext bit set. ID is: %d"
				" Contact vojtech@ucw.cz\n", i, gameport->phys, (data[i] >> 2) & 7);
			cobra->exists &= ~(1 << i);
		पूर्ण

	अगर (!cobra->exists) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	gameport_set_poll_handler(gameport, cobra_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (~(cobra->exists >> i) & 1)
			जारी;

		cobra->dev[i] = input_dev = input_allocate_device();
		अगर (!input_dev) अणु
			err = -ENOMEM;
			जाओ fail3;
		पूर्ण

		snम_लिखो(cobra->phys[i], माप(cobra->phys[i]),
			 "%s/input%d", gameport->phys, i);

		input_dev->name = "Creative Labs Blaster GamePad Cobra";
		input_dev->phys = cobra->phys[i];
		input_dev->id.bustype = BUS_GAMEPORT;
		input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_CREATIVE;
		input_dev->id.product = 0x0008;
		input_dev->id.version = 0x0100;
		input_dev->dev.parent = &gameport->dev;

		input_set_drvdata(input_dev, cobra);

		input_dev->खोलो = cobra_खोलो;
		input_dev->बंद = cobra_बंद;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input_set_असल_params(input_dev, ABS_X, -1, 1, 0, 0);
		input_set_असल_params(input_dev, ABS_Y, -1, 1, 0, 0);
		क्रम (j = 0; cobra_btn[j]; j++)
			set_bit(cobra_btn[j], input_dev->keybit);

		err = input_रेजिस्टर_device(cobra->dev[i]);
		अगर (err)
			जाओ fail4;
	पूर्ण

	वापस 0;

 fail4:	input_मुक्त_device(cobra->dev[i]);
 fail3:	जबतक (--i >= 0)
		अगर (cobra->dev[i])
			input_unरेजिस्टर_device(cobra->dev[i]);
 fail2:	gameport_बंद(gameport);
 fail1:	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(cobra);
	वापस err;
पूर्ण

अटल व्योम cobra_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा cobra *cobra = gameport_get_drvdata(gameport);
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		अगर ((cobra->exists >> i) & 1)
			input_unरेजिस्टर_device(cobra->dev[i]);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(cobra);
पूर्ण

अटल काष्ठा gameport_driver cobra_drv = अणु
	.driver		= अणु
		.name	= "cobra",
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= cobra_connect,
	.disconnect	= cobra_disconnect,
पूर्ण;

module_gameport_driver(cobra_drv);

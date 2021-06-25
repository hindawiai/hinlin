<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Steffen Schwenke
 */

/*
 * TurboGraFX parallel port पूर्णांकerface driver क्रम Linux.
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/parport.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("TurboGraFX parallel port interface driver");
MODULE_LICENSE("GPL");

#घोषणा TGFX_MAX_PORTS		3
#घोषणा TGFX_MAX_DEVICES	7

काष्ठा tgfx_config अणु
	पूर्णांक args[TGFX_MAX_DEVICES + 1];
	अचिन्हित पूर्णांक nargs;
पूर्ण;

अटल काष्ठा tgfx_config tgfx_cfg[TGFX_MAX_PORTS];

module_param_array_named(map, tgfx_cfg[0].args, पूर्णांक, &tgfx_cfg[0].nargs, 0);
MODULE_PARM_DESC(map, "Describes first set of devices (<parport#>,<js1>,<js2>,..<js7>");
module_param_array_named(map2, tgfx_cfg[1].args, पूर्णांक, &tgfx_cfg[1].nargs, 0);
MODULE_PARM_DESC(map2, "Describes second set of devices");
module_param_array_named(map3, tgfx_cfg[2].args, पूर्णांक, &tgfx_cfg[2].nargs, 0);
MODULE_PARM_DESC(map3, "Describes third set of devices");

#घोषणा TGFX_REFRESH_TIME	HZ/100	/* 10 ms */

#घोषणा TGFX_TRIGGER		0x08
#घोषणा TGFX_UP			0x10
#घोषणा TGFX_DOWN		0x20
#घोषणा TGFX_LEFT		0x40
#घोषणा TGFX_RIGHT		0x80

#घोषणा TGFX_THUMB		0x02
#घोषणा TGFX_THUMB2		0x04
#घोषणा TGFX_TOP		0x01
#घोषणा TGFX_TOP2		0x08

अटल पूर्णांक tgfx_buttons[] = अणु BTN_TRIGGER, BTN_THUMB, BTN_THUMB2, BTN_TOP, BTN_TOP2 पूर्ण;

अटल काष्ठा tgfx अणु
	काष्ठा pardevice *pd;
	काष्ठा समयr_list समयr;
	काष्ठा input_dev *dev[TGFX_MAX_DEVICES];
	अक्षर name[TGFX_MAX_DEVICES][64];
	अक्षर phys[TGFX_MAX_DEVICES][32];
	पूर्णांक sticks;
	पूर्णांक used;
	पूर्णांक parportno;
	काष्ठा mutex sem;
पूर्ण *tgfx_base[TGFX_MAX_PORTS];

/*
 * tgfx_समयr() पढ़ोs and analyzes TurboGraFX joystick data.
 */

अटल व्योम tgfx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tgfx *tgfx = from_समयr(tgfx, t, समयr);
	काष्ठा input_dev *dev;
	पूर्णांक data1, data2, i;

	क्रम (i = 0; i < 7; i++)
		अगर (tgfx->sticks & (1 << i)) अणु

			dev = tgfx->dev[i];

			parport_ग_लिखो_data(tgfx->pd->port, ~(1 << i));
			data1 = parport_पढ़ो_status(tgfx->pd->port) ^ 0x7f;
			data2 = parport_पढ़ो_control(tgfx->pd->port) ^ 0x04;	/* CAVEAT parport */

			input_report_असल(dev, ABS_X, !!(data1 & TGFX_RIGHT) - !!(data1 & TGFX_LEFT));
			input_report_असल(dev, ABS_Y, !!(data1 & TGFX_DOWN ) - !!(data1 & TGFX_UP  ));

			input_report_key(dev, BTN_TRIGGER, (data1 & TGFX_TRIGGER));
			input_report_key(dev, BTN_THUMB,   (data2 & TGFX_THUMB  ));
			input_report_key(dev, BTN_THUMB2,  (data2 & TGFX_THUMB2 ));
			input_report_key(dev, BTN_TOP,     (data2 & TGFX_TOP    ));
			input_report_key(dev, BTN_TOP2,    (data2 & TGFX_TOP2   ));

			input_sync(dev);
		पूर्ण

	mod_समयr(&tgfx->समयr, jअगरfies + TGFX_REFRESH_TIME);
पूर्ण

अटल पूर्णांक tgfx_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा tgfx *tgfx = input_get_drvdata(dev);
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&tgfx->sem);
	अगर (err)
		वापस err;

	अगर (!tgfx->used++) अणु
		parport_claim(tgfx->pd);
		parport_ग_लिखो_control(tgfx->pd->port, 0x04);
		mod_समयr(&tgfx->समयr, jअगरfies + TGFX_REFRESH_TIME);
	पूर्ण

	mutex_unlock(&tgfx->sem);
	वापस 0;
पूर्ण

अटल व्योम tgfx_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा tgfx *tgfx = input_get_drvdata(dev);

	mutex_lock(&tgfx->sem);
	अगर (!--tgfx->used) अणु
		del_समयr_sync(&tgfx->समयr);
		parport_ग_लिखो_control(tgfx->pd->port, 0x00);
		parport_release(tgfx->pd);
	पूर्ण
	mutex_unlock(&tgfx->sem);
पूर्ण



/*
 * tgfx_probe() probes क्रम tg gamepads.
 */

अटल व्योम tgfx_attach(काष्ठा parport *pp)
अणु
	काष्ठा tgfx *tgfx;
	काष्ठा input_dev *input_dev;
	काष्ठा pardevice *pd;
	पूर्णांक i, j, port_idx;
	पूर्णांक *n_buttons, n_devs;
	काष्ठा pardev_cb tgfx_parport_cb;

	क्रम (port_idx = 0; port_idx < TGFX_MAX_PORTS; port_idx++) अणु
		अगर (tgfx_cfg[port_idx].nargs == 0 ||
		    tgfx_cfg[port_idx].args[0] < 0)
			जारी;
		अगर (tgfx_cfg[port_idx].args[0] == pp->number)
			अवरोध;
	पूर्ण

	अगर (port_idx == TGFX_MAX_PORTS) अणु
		pr_debug("Not using parport%d.\n", pp->number);
		वापस;
	पूर्ण
	n_buttons = tgfx_cfg[port_idx].args + 1;
	n_devs = tgfx_cfg[port_idx].nargs - 1;

	स_रखो(&tgfx_parport_cb, 0, माप(tgfx_parport_cb));
	tgfx_parport_cb.flags = PARPORT_FLAG_EXCL;

	pd = parport_रेजिस्टर_dev_model(pp, "turbografx", &tgfx_parport_cb,
					port_idx);
	अगर (!pd) अणु
		pr_err("parport busy already - lp.o loaded?\n");
		वापस;
	पूर्ण

	tgfx = kzalloc(माप(काष्ठा tgfx), GFP_KERNEL);
	अगर (!tgfx) अणु
		prपूर्णांकk(KERN_ERR "turbografx.c: Not enough memory\n");
		जाओ err_unreg_pardev;
	पूर्ण

	mutex_init(&tgfx->sem);
	tgfx->pd = pd;
	tgfx->parportno = pp->number;
	समयr_setup(&tgfx->समयr, tgfx_समयr, 0);

	क्रम (i = 0; i < n_devs; i++) अणु
		अगर (n_buttons[i] < 1)
			जारी;

		अगर (n_buttons[i] > ARRAY_SIZE(tgfx_buttons)) अणु
			prपूर्णांकk(KERN_ERR "turbografx.c: Invalid number of buttons %d\n", n_buttons[i]);
			जाओ err_unreg_devs;
		पूर्ण

		tgfx->dev[i] = input_dev = input_allocate_device();
		अगर (!input_dev) अणु
			prपूर्णांकk(KERN_ERR "turbografx.c: Not enough memory for input device\n");
			जाओ err_unreg_devs;
		पूर्ण

		tgfx->sticks |= (1 << i);
		snम_लिखो(tgfx->name[i], माप(tgfx->name[i]),
			 "TurboGraFX %d-button Multisystem joystick", n_buttons[i]);
		snम_लिखो(tgfx->phys[i], माप(tgfx->phys[i]),
			 "%s/input%d", tgfx->pd->port->name, i);

		input_dev->name = tgfx->name[i];
		input_dev->phys = tgfx->phys[i];
		input_dev->id.bustype = BUS_PARPORT;
		input_dev->id.venकरोr = 0x0003;
		input_dev->id.product = n_buttons[i];
		input_dev->id.version = 0x0100;

		input_set_drvdata(input_dev, tgfx);

		input_dev->खोलो = tgfx_खोलो;
		input_dev->बंद = tgfx_बंद;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input_set_असल_params(input_dev, ABS_X, -1, 1, 0, 0);
		input_set_असल_params(input_dev, ABS_Y, -1, 1, 0, 0);

		क्रम (j = 0; j < n_buttons[i]; j++)
			set_bit(tgfx_buttons[j], input_dev->keybit);

		अगर (input_रेजिस्टर_device(tgfx->dev[i]))
			जाओ err_मुक्त_dev;
	पूर्ण

        अगर (!tgfx->sticks) अणु
		prपूर्णांकk(KERN_ERR "turbografx.c: No valid devices specified\n");
		जाओ err_मुक्त_tgfx;
        पूर्ण

	tgfx_base[port_idx] = tgfx;
	वापस;

 err_मुक्त_dev:
	input_मुक्त_device(tgfx->dev[i]);
 err_unreg_devs:
	जबतक (--i >= 0)
		अगर (tgfx->dev[i])
			input_unरेजिस्टर_device(tgfx->dev[i]);
 err_मुक्त_tgfx:
	kमुक्त(tgfx);
 err_unreg_pardev:
	parport_unरेजिस्टर_device(pd);
पूर्ण

अटल व्योम tgfx_detach(काष्ठा parport *port)
अणु
	पूर्णांक i;
	काष्ठा tgfx *tgfx;

	क्रम (i = 0; i < TGFX_MAX_PORTS; i++) अणु
		अगर (tgfx_base[i] && tgfx_base[i]->parportno == port->number)
			अवरोध;
	पूर्ण

	अगर (i == TGFX_MAX_PORTS)
		वापस;

	tgfx = tgfx_base[i];
	tgfx_base[i] = शून्य;

	क्रम (i = 0; i < TGFX_MAX_DEVICES; i++)
		अगर (tgfx->dev[i])
			input_unरेजिस्टर_device(tgfx->dev[i]);
	parport_unरेजिस्टर_device(tgfx->pd);
	kमुक्त(tgfx);
पूर्ण

अटल काष्ठा parport_driver tgfx_parport_driver = अणु
	.name = "turbografx",
	.match_port = tgfx_attach,
	.detach = tgfx_detach,
	.devmodel = true,
पूर्ण;

अटल पूर्णांक __init tgfx_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक have_dev = 0;

	क्रम (i = 0; i < TGFX_MAX_PORTS; i++) अणु
		अगर (tgfx_cfg[i].nargs == 0 || tgfx_cfg[i].args[0] < 0)
			जारी;

		अगर (tgfx_cfg[i].nargs < 2) अणु
			prपूर्णांकk(KERN_ERR "turbografx.c: at least one joystick must be specified\n");
			वापस -EINVAL;
		पूर्ण

		have_dev = 1;
	पूर्ण

	अगर (!have_dev)
		वापस -ENODEV;

	वापस parport_रेजिस्टर_driver(&tgfx_parport_driver);
पूर्ण

अटल व्योम __निकास tgfx_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&tgfx_parport_driver);
पूर्ण

module_init(tgfx_init);
module_निकास(tgfx_निकास);

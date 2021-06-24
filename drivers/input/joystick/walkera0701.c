<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Parallel port to Walkera WK-0701 TX joystick
 *
 *  Copyright (c) 2008 Peter Popovec
 *
 *  More about driver:  <file:Documentation/input/devices/walkera0701.rst>
 */


#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा RESERVE 20000
#घोषणा SYNC_PULSE 1306000
#घोषणा BIN0_PULSE 288000
#घोषणा BIN1_PULSE 438000

#घोषणा ANALOG_MIN_PULSE 318000
#घोषणा ANALOG_MAX_PULSE 878000
#घोषणा ANALOG_DELTA 80000

#घोषणा BIN_SAMPLE ((BIN0_PULSE + BIN1_PULSE) / 2)

#घोषणा NO_SYNC 25

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/parport.h>
#समावेश <linux/input.h>
#समावेश <linux/hrसमयr.h>

MODULE_AUTHOR("Peter Popovec <popovec@fei.tuke.sk>");
MODULE_DESCRIPTION("Walkera WK-0701 TX as joystick");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक walkera0701_pp_no;
module_param_named(port, walkera0701_pp_no, पूर्णांक, 0);
MODULE_PARM_DESC(port,
		 "Parallel port adapter for Walkera WK-0701 TX (default is 0)");

/*
 * For now, only one device is supported, अगर somebody need more devices, code
 * can be expanded, one काष्ठा walkera_dev per device must be allocated and
 * set up by walkera0701_connect (release of device by walkera0701_disconnect)
 */

काष्ठा walkera_dev अणु
	अचिन्हित अक्षर buf[25];
	u64 irq_समय, irq_lastसमय;
	पूर्णांक counter;
	पूर्णांक ack;

	काष्ठा input_dev *input_dev;
	काष्ठा hrसमयr समयr;

	काष्ठा parport *parport;
	काष्ठा pardevice *pardevice;
पूर्ण;

अटल काष्ठा walkera_dev w_dev;

अटल अंतरभूत व्योम walkera0701_parse_frame(काष्ठा walkera_dev *w)
अणु
	पूर्णांक i;
	पूर्णांक val1, val2, val3, val4, val5, val6, val7, val8;
	पूर्णांक magic, magic_bit;
	पूर्णांक crc1, crc2;

	क्रम (crc1 = crc2 = i = 0; i < 10; i++) अणु
		crc1 += w->buf[i] & 7;
		crc2 += (w->buf[i] & 8) >> 3;
	पूर्ण
	अगर ((w->buf[10] & 7) != (crc1 & 7))
		वापस;
	अगर (((w->buf[10] & 8) >> 3) != (((crc1 >> 3) + crc2) & 1))
		वापस;
	क्रम (crc1 = crc2 = 0, i = 11; i < 23; i++) अणु
		crc1 += w->buf[i] & 7;
		crc2 += (w->buf[i] & 8) >> 3;
	पूर्ण
	अगर ((w->buf[23] & 7) != (crc1 & 7))
		वापस;
	अगर (((w->buf[23] & 8) >> 3) != (((crc1 >> 3) + crc2) & 1))
		वापस;
	val1 = ((w->buf[0] & 7) * 256 + w->buf[1] * 16 + w->buf[2]) >> 2;
	val1 *= ((w->buf[0] >> 2) & 2) - 1;	/* sign */
	val2 = (w->buf[2] & 1) << 8 | (w->buf[3] << 4) | w->buf[4];
	val2 *= (w->buf[2] & 2) - 1;	/* sign */
	val3 = ((w->buf[5] & 7) * 256 + w->buf[6] * 16 + w->buf[7]) >> 2;
	val3 *= ((w->buf[5] >> 2) & 2) - 1;	/* sign */
	val4 = (w->buf[7] & 1) << 8 | (w->buf[8] << 4) | w->buf[9];
	val4 *= (w->buf[7] & 2) - 1;	/* sign */
	val5 = ((w->buf[11] & 7) * 256 + w->buf[12] * 16 + w->buf[13]) >> 2;
	val5 *= ((w->buf[11] >> 2) & 2) - 1;	/* sign */
	val6 = (w->buf[13] & 1) << 8 | (w->buf[14] << 4) | w->buf[15];
	val6 *= (w->buf[13] & 2) - 1;	/* sign */
	val7 = ((w->buf[16] & 7) * 256 + w->buf[17] * 16 + w->buf[18]) >> 2;
	val7 *= ((w->buf[16] >> 2) & 2) - 1;	/*sign */
	val8 = (w->buf[18] & 1) << 8 | (w->buf[19] << 4) | w->buf[20];
	val8 *= (w->buf[18] & 2) - 1;	/*sign */

	magic = (w->buf[21] << 4) | w->buf[22];
	magic_bit = (w->buf[24] & 8) >> 3;
	pr_debug("%4d %4d %4d %4d  %4d %4d %4d %4d (magic %2x %d)\n",
		 val1, val2, val3, val4, val5, val6, val7, val8,
		 magic, magic_bit);

	input_report_असल(w->input_dev, ABS_X, val2);
	input_report_असल(w->input_dev, ABS_Y, val1);
	input_report_असल(w->input_dev, ABS_Z, val6);
	input_report_असल(w->input_dev, ABS_THROTTLE, val3);
	input_report_असल(w->input_dev, ABS_RUDDER, val4);
	input_report_असल(w->input_dev, ABS_MISC, val7);
	input_report_key(w->input_dev, BTN_GEAR_DOWN, val5 > 0);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_ack(काष्ठा pardevice *p)
अणु
	वापस parport_पढ़ो_status(p->port) & 0x40;
पूर्ण

/* falling edge, prepare to BIN value calculation */
अटल व्योम walkera0701_irq_handler(व्योम *handler_data)
अणु
	u64 pulse_समय;
	काष्ठा walkera_dev *w = handler_data;

	w->irq_समय = kसमय_प्रकारo_ns(kसमय_get());
	pulse_समय = w->irq_समय - w->irq_lastसमय;
	w->irq_lastसमय = w->irq_समय;

	/* cancel समयr, अगर in handler or active करो resync */
	अगर (unlikely(0 != hrसमयr_try_to_cancel(&w->समयr))) अणु
		w->counter = NO_SYNC;
		वापस;
	पूर्ण

	अगर (w->counter < NO_SYNC) अणु
		अगर (w->ack) अणु
			pulse_समय -= BIN1_PULSE;
			w->buf[w->counter] = 8;
		पूर्ण अन्यथा अणु
			pulse_समय -= BIN0_PULSE;
			w->buf[w->counter] = 0;
		पूर्ण
		अगर (w->counter == 24) अणु	/* full frame */
			walkera0701_parse_frame(w);
			w->counter = NO_SYNC;
			अगर (असल(pulse_समय - SYNC_PULSE) < RESERVE)	/* new frame sync */
				w->counter = 0;
		पूर्ण अन्यथा अणु
			अगर ((pulse_समय > (ANALOG_MIN_PULSE - RESERVE)
			     && (pulse_समय < (ANALOG_MAX_PULSE + RESERVE)))) अणु
				pulse_समय -= (ANALOG_MIN_PULSE - RESERVE);
				pulse_समय = (u32) pulse_समय / ANALOG_DELTA;	/* overtiping is safe, pulseसमय < s32.. */
				w->buf[w->counter++] |= (pulse_समय & 7);
			पूर्ण अन्यथा
				w->counter = NO_SYNC;
		पूर्ण
	पूर्ण अन्यथा अगर (असल(pulse_समय - SYNC_PULSE - BIN0_PULSE) <
				RESERVE + BIN1_PULSE - BIN0_PULSE)	/* frame sync .. */
		w->counter = 0;

	hrसमयr_start(&w->समयr, BIN_SAMPLE, HRTIMER_MODE_REL);
पूर्ण

अटल क्रमागत hrसमयr_restart समयr_handler(काष्ठा hrसमयr
					  *handle)
अणु
	काष्ठा walkera_dev *w;

	w = container_of(handle, काष्ठा walkera_dev, समयr);
	w->ack = पढ़ो_ack(w->pardevice);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल पूर्णांक walkera0701_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा walkera_dev *w = input_get_drvdata(dev);

	अगर (parport_claim(w->pardevice))
		वापस -EBUSY;

	parport_enable_irq(w->parport);
	वापस 0;
पूर्ण

अटल व्योम walkera0701_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा walkera_dev *w = input_get_drvdata(dev);

	parport_disable_irq(w->parport);
	hrसमयr_cancel(&w->समयr);

	parport_release(w->pardevice);
पूर्ण

अटल व्योम walkera0701_attach(काष्ठा parport *pp)
अणु
	काष्ठा pardev_cb walkera0701_parport_cb;
	काष्ठा walkera_dev *w = &w_dev;

	अगर (pp->number != walkera0701_pp_no) अणु
		pr_debug("Not using parport%d.\n", pp->number);
		वापस;
	पूर्ण

	अगर (pp->irq == -1) अणु
		pr_err("parport %d does not have interrupt assigned\n",
			pp->number);
		वापस;
	पूर्ण

	w->parport = pp;

	स_रखो(&walkera0701_parport_cb, 0, माप(walkera0701_parport_cb));
	walkera0701_parport_cb.flags = PARPORT_FLAG_EXCL;
	walkera0701_parport_cb.irq_func = walkera0701_irq_handler;
	walkera0701_parport_cb.निजी = w;

	w->pardevice = parport_रेजिस्टर_dev_model(pp, "walkera0701",
						  &walkera0701_parport_cb, 0);

	अगर (!w->pardevice) अणु
		pr_err("failed to register parport device\n");
		वापस;
	पूर्ण

	अगर (parport_negotiate(w->pardevice->port, IEEE1284_MODE_COMPAT)) अणु
		pr_err("failed to negotiate parport mode\n");
		जाओ err_unरेजिस्टर_device;
	पूर्ण

	hrसमयr_init(&w->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	w->समयr.function = समयr_handler;

	w->input_dev = input_allocate_device();
	अगर (!w->input_dev) अणु
		pr_err("failed to allocate input device\n");
		जाओ err_unरेजिस्टर_device;
	पूर्ण

	input_set_drvdata(w->input_dev, w);
	w->input_dev->name = "Walkera WK-0701 TX";
	w->input_dev->phys = w->parport->name;
	w->input_dev->id.bustype = BUS_PARPORT;

	/* TODO what id venकरोr/product/version ? */
	w->input_dev->id.venकरोr = 0x0001;
	w->input_dev->id.product = 0x0001;
	w->input_dev->id.version = 0x0100;
	w->input_dev->dev.parent = w->parport->dev;
	w->input_dev->खोलो = walkera0701_खोलो;
	w->input_dev->बंद = walkera0701_बंद;

	w->input_dev->evbit[0] = BIT(EV_ABS) | BIT_MASK(EV_KEY);
	w->input_dev->keybit[BIT_WORD(BTN_GEAR_DOWN)] = BIT_MASK(BTN_GEAR_DOWN);

	input_set_असल_params(w->input_dev, ABS_X, -512, 512, 0, 0);
	input_set_असल_params(w->input_dev, ABS_Y, -512, 512, 0, 0);
	input_set_असल_params(w->input_dev, ABS_Z, -512, 512, 0, 0);
	input_set_असल_params(w->input_dev, ABS_THROTTLE, -512, 512, 0, 0);
	input_set_असल_params(w->input_dev, ABS_RUDDER, -512, 512, 0, 0);
	input_set_असल_params(w->input_dev, ABS_MISC, -512, 512, 0, 0);

	अगर (input_रेजिस्टर_device(w->input_dev)) अणु
		pr_err("failed to register input device\n");
		जाओ err_मुक्त_input_dev;
	पूर्ण

	वापस;

err_मुक्त_input_dev:
	input_मुक्त_device(w->input_dev);
err_unरेजिस्टर_device:
	parport_unरेजिस्टर_device(w->pardevice);
पूर्ण

अटल व्योम walkera0701_detach(काष्ठा parport *port)
अणु
	काष्ठा walkera_dev *w = &w_dev;

	अगर (!w->pardevice || w->parport->number != port->number)
		वापस;

	input_unरेजिस्टर_device(w->input_dev);
	parport_unरेजिस्टर_device(w->pardevice);
	w->parport = शून्य;
पूर्ण

अटल काष्ठा parport_driver walkera0701_parport_driver = अणु
	.name = "walkera0701",
	.match_port = walkera0701_attach,
	.detach = walkera0701_detach,
	.devmodel = true,
पूर्ण;

अटल पूर्णांक __init walkera0701_init(व्योम)
अणु
	वापस parport_रेजिस्टर_driver(&walkera0701_parport_driver);
पूर्ण

अटल व्योम __निकास walkera0701_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&walkera0701_parport_driver);
पूर्ण

module_init(walkera0701_init);
module_निकास(walkera0701_निकास);

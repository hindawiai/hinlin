<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Parallel port to Keyboard port adapter driver क्रम Linux
 *
 *  Copyright (c) 1999-2004 Vojtech Pavlik
 */


/*
 * To connect an AT or XT keyboard to the parallel port, a fairly simple adapter
 * can be made:
 * 
 *  Parallel port            Keyboard port
 *
 *     +5V --------------------- +5V (4)
 *  
 *                 ______
 *     +5V -------|______|--.
 *                          |
 *     ACK (10) ------------|
 *                          |--- KBD CLOCK (5)
 *     STROBE (1) ---|<|----'
 *     
 *                 ______
 *     +5V -------|______|--.
 *                          |
 *     BUSY (11) -----------|
 *                          |--- KBD DATA (1)
 *     AUTOFD (14) --|<|----'
 *
 *     GND (18-25) ------------- GND (3)
 *     
 * The diodes can be fairly any type, and the resistors should be somewhere
 * around 5 kOhm, but the adapter will likely work without the resistors,
 * too.
 *
 * The +5V source can be taken either from USB, from mouse or keyboard ports,
 * or from a joystick port. Unक्रमtunately, the parallel port of a PC करोesn't
 * have a +5V pin, and feeding the keyboard from संकेत pins is out of question
 * with 300 mA घातer reqirement of a typical AT keyboard.
 */

#समावेश <linux/module.h>
#समावेश <linux/parport.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/serपन.स>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Parallel port to Keyboard port adapter driver");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक parkbd_pp_no;
module_param_named(port, parkbd_pp_no, पूर्णांक, 0);
MODULE_PARM_DESC(port, "Parallel port the adapter is connected to (default is 0)");

अटल अचिन्हित पूर्णांक parkbd_mode = SERIO_8042;
module_param_named(mode, parkbd_mode, uपूर्णांक, 0);
MODULE_PARM_DESC(mode, "Mode of operation: XT = 0/AT = 1 (default)");

#घोषणा PARKBD_CLOCK	0x01	/* Strobe & Ack */
#घोषणा PARKBD_DATA	0x02	/* AutoFd & Busy */

अटल पूर्णांक parkbd_buffer;
अटल पूर्णांक parkbd_counter;
अटल अचिन्हित दीर्घ parkbd_last;
अटल पूर्णांक parkbd_writing;
अटल अचिन्हित दीर्घ parkbd_start;

अटल काष्ठा pardevice *parkbd_dev;
अटल काष्ठा serio *parkbd_port;

अटल पूर्णांक parkbd_पढ़ोlines(व्योम)
अणु
	वापस (parport_पढ़ो_status(parkbd_dev->port) >> 6) ^ 2;
पूर्ण

अटल व्योम parkbd_ग_लिखोlines(पूर्णांक data)
अणु
	parport_ग_लिखो_control(parkbd_dev->port, (~data & 3) | 0x10);
पूर्ण

अटल पूर्णांक parkbd_ग_लिखो(काष्ठा serio *port, अचिन्हित अक्षर c)
अणु
	अचिन्हित अक्षर p;

	अगर (!parkbd_mode) वापस -1;

        p = c ^ (c >> 4);
	p = p ^ (p >> 2);
	p = p ^ (p >> 1);

	parkbd_counter = 0;
	parkbd_writing = 1;
	parkbd_buffer = c | (((पूर्णांक) (~p & 1)) << 8) | 0x600;

	parkbd_ग_लिखोlines(2);

	वापस 0;
पूर्ण

अटल व्योम parkbd_पूर्णांकerrupt(व्योम *dev_id)
अणु

	अगर (parkbd_writing) अणु

		अगर (parkbd_counter && ((parkbd_counter == 11) || समय_after(jअगरfies, parkbd_last + HZ/100))) अणु
			parkbd_counter = 0;
			parkbd_buffer = 0;
			parkbd_writing = 0;
			parkbd_ग_लिखोlines(3);
			वापस;
		पूर्ण

		parkbd_ग_लिखोlines(((parkbd_buffer >> parkbd_counter++) & 1) | 2);

		अगर (parkbd_counter == 11) अणु
			parkbd_counter = 0;
			parkbd_buffer = 0;
			parkbd_writing = 0;
			parkbd_ग_लिखोlines(3);
		पूर्ण

	पूर्ण अन्यथा अणु

		अगर ((parkbd_counter == parkbd_mode + 10) || समय_after(jअगरfies, parkbd_last + HZ/100)) अणु
			parkbd_counter = 0;
			parkbd_buffer = 0;
		पूर्ण

		parkbd_buffer |= (parkbd_पढ़ोlines() >> 1) << parkbd_counter++;

		अगर (parkbd_counter == parkbd_mode + 10)
			serio_पूर्णांकerrupt(parkbd_port, (parkbd_buffer >> (2 - parkbd_mode)) & 0xff, 0);
	पूर्ण

	parkbd_last = jअगरfies;
पूर्ण

अटल पूर्णांक parkbd_getport(काष्ठा parport *pp)
अणु
	काष्ठा pardev_cb parkbd_parport_cb;

	स_रखो(&parkbd_parport_cb, 0, माप(parkbd_parport_cb));
	parkbd_parport_cb.irq_func = parkbd_पूर्णांकerrupt;
	parkbd_parport_cb.flags = PARPORT_FLAG_EXCL;

	parkbd_dev = parport_रेजिस्टर_dev_model(pp, "parkbd",
						&parkbd_parport_cb, 0);

	अगर (!parkbd_dev)
		वापस -ENODEV;

	अगर (parport_claim(parkbd_dev)) अणु
		parport_unरेजिस्टर_device(parkbd_dev);
		वापस -EBUSY;
	पूर्ण

	parkbd_start = jअगरfies;

	वापस 0;
पूर्ण

अटल काष्ठा serio *parkbd_allocate_serio(व्योम)
अणु
	काष्ठा serio *serio;

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (serio) अणु
		serio->id.type = parkbd_mode;
		serio->ग_लिखो = parkbd_ग_लिखो;
		strlcpy(serio->name, "PARKBD AT/XT keyboard adapter", माप(serio->name));
		snम_लिखो(serio->phys, माप(serio->phys), "%s/serio0", parkbd_dev->port->name);
	पूर्ण

	वापस serio;
पूर्ण

अटल व्योम parkbd_attach(काष्ठा parport *pp)
अणु
	अगर (pp->number != parkbd_pp_no) अणु
		pr_debug("Not using parport%d.\n", pp->number);
		वापस;
	पूर्ण

	अगर (parkbd_getport(pp))
		वापस;

	parkbd_port = parkbd_allocate_serio();
	अगर (!parkbd_port) अणु
		parport_release(parkbd_dev);
		parport_unरेजिस्टर_device(parkbd_dev);
		वापस;
	पूर्ण

	parkbd_ग_लिखोlines(3);

	serio_रेजिस्टर_port(parkbd_port);

	prपूर्णांकk(KERN_INFO "serio: PARKBD %s adapter on %s\n",
                        parkbd_mode ? "AT" : "XT", parkbd_dev->port->name);

	वापस;
पूर्ण

अटल व्योम parkbd_detach(काष्ठा parport *port)
अणु
	अगर (!parkbd_port || port->number != parkbd_pp_no)
		वापस;

	parport_release(parkbd_dev);
	serio_unरेजिस्टर_port(parkbd_port);
	parport_unरेजिस्टर_device(parkbd_dev);
	parkbd_port = शून्य;
पूर्ण

अटल काष्ठा parport_driver parkbd_parport_driver = अणु
	.name = "parkbd",
	.match_port = parkbd_attach,
	.detach = parkbd_detach,
	.devmodel = true,
पूर्ण;

अटल पूर्णांक __init parkbd_init(व्योम)
अणु
	वापस parport_रेजिस्टर_driver(&parkbd_parport_driver);
पूर्ण

अटल व्योम __निकास parkbd_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&parkbd_parport_driver);
पूर्ण

module_init(parkbd_init);
module_निकास(parkbd_निकास);

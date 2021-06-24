<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1996-2001 Vojtech Pavlik
 */

/*
 * This is just a very simple driver that can dump the data
 * out of the joystick port पूर्णांकo the syslog ...
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/gameport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#घोषणा DRIVER_DESC	"Gameport data dumper module"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा BUF_SIZE 256

काष्ठा joydump अणु
	अचिन्हित पूर्णांक समय;
	अचिन्हित अक्षर data;
पूर्ण;

अटल पूर्णांक joydump_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा joydump *buf;	/* all entries */
	काष्ठा joydump *dump, *prev;	/* one entry each */
	पूर्णांक axes[4], buttons;
	पूर्णांक i, j, t, समयout;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर u;

	prपूर्णांकk(KERN_INFO "joydump: ,------------------ START ----------------.\n");
	prपूर्णांकk(KERN_INFO "joydump: | Dumping: %30s |\n", gameport->phys);
	prपूर्णांकk(KERN_INFO "joydump: | Speed: %28d kHz |\n", gameport->speed);

	अगर (gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW)) अणु

		prपूर्णांकk(KERN_INFO "joydump: | Raw mode not available - trying cooked.    |\n");

		अगर (gameport_खोलो(gameport, drv, GAMEPORT_MODE_COOKED)) अणु

			prपूर्णांकk(KERN_INFO "joydump: | Cooked not available either. Failing.   |\n");
			prपूर्णांकk(KERN_INFO "joydump: `------------------- END -----------------'\n");
			वापस -ENODEV;
		पूर्ण

		gameport_cooked_पढ़ो(gameport, axes, &buttons);

		क्रम (i = 0; i < 4; i++)
			prपूर्णांकk(KERN_INFO "joydump: | Axis %d: %4d.                           |\n", i, axes[i]);
		prपूर्णांकk(KERN_INFO "joydump: | Buttons %02x.                             |\n", buttons);
		prपूर्णांकk(KERN_INFO "joydump: `------------------- END -----------------'\n");
	पूर्ण

	समयout = gameport_समय(gameport, 10000); /* 10 ms */

	buf = kदो_स्मृति_array(BUF_SIZE, माप(काष्ठा joydump), GFP_KERNEL);
	अगर (!buf) अणु
		prपूर्णांकk(KERN_INFO "joydump: no memory for testing\n");
		जाओ jd_end;
	पूर्ण
	dump = buf;
	t = 0;
	i = 1;

	local_irq_save(flags);

	u = gameport_पढ़ो(gameport);

	dump->data = u;
	dump->समय = t;
	dump++;

	gameport_trigger(gameport);

	जबतक (i < BUF_SIZE && t < समयout) अणु

		dump->data = gameport_पढ़ो(gameport);

		अगर (dump->data ^ u) अणु
			u = dump->data;
			dump->समय = t;
			i++;
			dump++;
		पूर्ण
		t++;
	पूर्ण

	local_irq_restore(flags);

/*
 * Dump data.
 */

	t = i;
	dump = buf;
	prev = dump;

	prपूर्णांकk(KERN_INFO "joydump: >------------------ DATA -----------------<\n");
	prपूर्णांकk(KERN_INFO "joydump: | index: %3d delta: %3d us data: ", 0, 0);
	क्रम (j = 7; j >= 0; j--)
		prपूर्णांकk("%d", (dump->data >> j) & 1);
	prपूर्णांकk(" |\n");
	dump++;

	क्रम (i = 1; i < t; i++, dump++, prev++) अणु
		prपूर्णांकk(KERN_INFO "joydump: | index: %3d delta: %3d us data: ",
			i, dump->समय - prev->समय);
		क्रम (j = 7; j >= 0; j--)
			prपूर्णांकk("%d", (dump->data >> j) & 1);
		prपूर्णांकk(" |\n");
	पूर्ण
	kमुक्त(buf);

jd_end:
	prपूर्णांकk(KERN_INFO "joydump: `------------------- END -----------------'\n");

	वापस 0;
पूर्ण

अटल व्योम joydump_disconnect(काष्ठा gameport *gameport)
अणु
	gameport_बंद(gameport);
पूर्ण

अटल काष्ठा gameport_driver joydump_drv = अणु
	.driver		= अणु
		.name	= "joydump",
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= joydump_connect,
	.disconnect	= joydump_disconnect,
पूर्ण;

module_gameport_driver(joydump_drv);

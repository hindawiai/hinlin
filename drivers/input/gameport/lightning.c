<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2001 Vojtech Pavlik
 */

/*
 * PDPI Lightning 4 gamecard driver क्रम Linux.
 */

/*
 */

#समावेश <यंत्र/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/gameport.h>

#घोषणा L4_PORT			0x201
#घोषणा L4_SELECT_ANALOG	0xa4
#घोषणा L4_SELECT_DIGITAL	0xa5
#घोषणा L4_SELECT_SECONDARY	0xa6
#घोषणा L4_CMD_ID		0x80
#घोषणा L4_CMD_GETCAL		0x92
#घोषणा L4_CMD_SETCAL		0x93
#घोषणा L4_ID			0x04
#घोषणा L4_BUSY			0x01
#घोषणा L4_TIMEOUT		80	/* 80 us */

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("PDPI Lightning 4 gamecard driver");
MODULE_LICENSE("GPL");

काष्ठा l4 अणु
	काष्ठा gameport *gameport;
	अचिन्हित अक्षर port;
पूर्ण;

अटल काष्ठा l4 l4_ports[8];

/*
 * l4_रुको_पढ़ोy() रुकोs क्रम the L4 to become पढ़ोy.
 */

अटल पूर्णांक l4_रुको_पढ़ोy(व्योम)
अणु
	अचिन्हित पूर्णांक t = L4_TIMEOUT;

	जबतक ((inb(L4_PORT) & L4_BUSY) && t > 0) t--;
	वापस -(t <= 0);
पूर्ण

/*
 * l4_cooked_पढ़ो() पढ़ोs data from the Lightning 4.
 */

अटल पूर्णांक l4_cooked_पढ़ो(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *buttons)
अणु
	काष्ठा l4 *l4 = gameport->port_data;
	अचिन्हित अक्षर status;
	पूर्णांक i, result = -1;

	outb(L4_SELECT_ANALOG, L4_PORT);
	outb(L4_SELECT_DIGITAL + (l4->port >> 2), L4_PORT);

	अगर (inb(L4_PORT) & L4_BUSY) जाओ fail;
	outb(l4->port & 3, L4_PORT);

	अगर (l4_रुको_पढ़ोy()) जाओ fail;
	status = inb(L4_PORT);

	क्रम (i = 0; i < 4; i++)
		अगर (status & (1 << i)) अणु
			अगर (l4_रुको_पढ़ोy()) जाओ fail;
			axes[i] = inb(L4_PORT);
			अगर (axes[i] > 252) axes[i] = -1;
		पूर्ण

	अगर (status & 0x10) अणु
		अगर (l4_रुको_पढ़ोy()) जाओ fail;
		*buttons = inb(L4_PORT) & 0x0f;
	पूर्ण

	result = 0;

fail:	outb(L4_SELECT_ANALOG, L4_PORT);
	वापस result;
पूर्ण

अटल पूर्णांक l4_खोलो(काष्ठा gameport *gameport, पूर्णांक mode)
अणु
	काष्ठा l4 *l4 = gameport->port_data;

        अगर (l4->port != 0 && mode != GAMEPORT_MODE_COOKED)
		वापस -1;
	outb(L4_SELECT_ANALOG, L4_PORT);
	वापस 0;
पूर्ण

/*
 * l4_अ_लोal() पढ़ोs the L4 with calibration values.
 */

अटल पूर्णांक l4_अ_लोal(पूर्णांक port, पूर्णांक *cal)
अणु
	पूर्णांक i, result = -1;

	outb(L4_SELECT_ANALOG, L4_PORT);
	outb(L4_SELECT_DIGITAL + (port >> 2), L4_PORT);
	अगर (inb(L4_PORT) & L4_BUSY)
		जाओ out;

	outb(L4_CMD_GETCAL, L4_PORT);
	अगर (l4_रुको_पढ़ोy())
		जाओ out;

	अगर (inb(L4_PORT) != L4_SELECT_DIGITAL + (port >> 2))
		जाओ out;

	अगर (l4_रुको_पढ़ोy())
		जाओ out;
        outb(port & 3, L4_PORT);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (l4_रुको_पढ़ोy())
			जाओ out;
		cal[i] = inb(L4_PORT);
	पूर्ण

	result = 0;

out:	outb(L4_SELECT_ANALOG, L4_PORT);
	वापस result;
पूर्ण

/*
 * l4_setcal() programs the L4 with calibration values.
 */

अटल पूर्णांक l4_setcal(पूर्णांक port, पूर्णांक *cal)
अणु
	पूर्णांक i, result = -1;

	outb(L4_SELECT_ANALOG, L4_PORT);
	outb(L4_SELECT_DIGITAL + (port >> 2), L4_PORT);
	अगर (inb(L4_PORT) & L4_BUSY)
		जाओ out;

	outb(L4_CMD_SETCAL, L4_PORT);
	अगर (l4_रुको_पढ़ोy())
		जाओ out;

	अगर (inb(L4_PORT) != L4_SELECT_DIGITAL + (port >> 2))
		जाओ out;

	अगर (l4_रुको_पढ़ोy())
		जाओ out;
        outb(port & 3, L4_PORT);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (l4_रुको_पढ़ोy())
			जाओ out;
		outb(cal[i], L4_PORT);
	पूर्ण

	result = 0;

out:	outb(L4_SELECT_ANALOG, L4_PORT);
	वापस result;
पूर्ण

/*
 * l4_calibrate() calibrates the L4 क्रम the attached device, so
 * that the device's resistance fits into the L4's 8-bit range.
 */

अटल पूर्णांक l4_calibrate(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *max)
अणु
	पूर्णांक i, t;
	पूर्णांक cal[4];
	काष्ठा l4 *l4 = gameport->port_data;

	अगर (l4_अ_लोal(l4->port, cal))
		वापस -1;

	क्रम (i = 0; i < 4; i++) अणु
		t = (max[i] * cal[i]) / 200;
		t = (t < 1) ? 1 : ((t > 255) ? 255 : t);
		axes[i] = (axes[i] < 0) ? -1 : (axes[i] * cal[i]) / t;
		axes[i] = (axes[i] > 252) ? 252 : axes[i];
		cal[i] = t;
	पूर्ण

	अगर (l4_setcal(l4->port, cal))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक __init l4_create_ports(पूर्णांक card_no)
अणु
	काष्ठा l4 *l4;
	काष्ठा gameport *port;
	पूर्णांक i, idx;

	क्रम (i = 0; i < 4; i++) अणु

		idx = card_no * 4 + i;
		l4 = &l4_ports[idx];

		अगर (!(l4->gameport = port = gameport_allocate_port())) अणु
			prपूर्णांकk(KERN_ERR "lightning: Memory allocation failed\n");
			जबतक (--i >= 0) अणु
				gameport_मुक्त_port(l4->gameport);
				l4->gameport = शून्य;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
		l4->port = idx;

		port->port_data = l4;
		port->खोलो = l4_खोलो;
		port->cooked_पढ़ो = l4_cooked_पढ़ो;
		port->calibrate = l4_calibrate;

		gameport_set_name(port, "PDPI Lightning 4");
		gameport_set_phys(port, "isa%04x/gameport%d", L4_PORT, idx);

		अगर (idx == 0)
			port->io = L4_PORT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init l4_add_card(पूर्णांक card_no)
अणु
	पूर्णांक cal[4] = अणु 255, 255, 255, 255 पूर्ण;
	पूर्णांक i, rev, result;
	काष्ठा l4 *l4;

	outb(L4_SELECT_ANALOG, L4_PORT);
	outb(L4_SELECT_DIGITAL + card_no, L4_PORT);

	अगर (inb(L4_PORT) & L4_BUSY)
		वापस -1;
	outb(L4_CMD_ID, L4_PORT);

	अगर (l4_रुको_पढ़ोy())
		वापस -1;

	अगर (inb(L4_PORT) != L4_SELECT_DIGITAL + card_no)
		वापस -1;

	अगर (l4_रुको_पढ़ोy())
		वापस -1;
	अगर (inb(L4_PORT) != L4_ID)
		वापस -1;

	अगर (l4_रुको_पढ़ोy())
		वापस -1;
	rev = inb(L4_PORT);

	अगर (!rev)
		वापस -1;

	result = l4_create_ports(card_no);
	अगर (result)
		वापस result;

	prपूर्णांकk(KERN_INFO "gameport: PDPI Lightning 4 %s card v%d.%d at %#x\n",
		card_no ? "secondary" : "primary", rev >> 4, rev, L4_PORT);

	क्रम (i = 0; i < 4; i++) अणु
		l4 = &l4_ports[card_no * 4 + i];

		अगर (rev > 0x28)		/* on 2.9+ the setcal command works correctly */
			l4_setcal(l4->port, cal);
		gameport_रेजिस्टर_port(l4->gameport);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init l4_init(व्योम)
अणु
	पूर्णांक i, cards = 0;

	अगर (!request_region(L4_PORT, 1, "lightning"))
		वापस -EBUSY;

	क्रम (i = 0; i < 2; i++)
		अगर (l4_add_card(i) == 0)
			cards++;

	outb(L4_SELECT_ANALOG, L4_PORT);

	अगर (!cards) अणु
		release_region(L4_PORT, 1);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास l4_निकास(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक cal[4] = अणु 59, 59, 59, 59 पूर्ण;

	क्रम (i = 0; i < 8; i++)
		अगर (l4_ports[i].gameport) अणु
			l4_setcal(l4_ports[i].port, cal);
			gameport_unरेजिस्टर_port(l4_ports[i].gameport);
		पूर्ण

	outb(L4_SELECT_ANALOG, L4_PORT);
	release_region(L4_PORT, 1);
पूर्ण

module_init(l4_init);
module_निकास(l4_निकास);

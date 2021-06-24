<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* suncore.c
 *
 * Common SUN serial routines.  Based entirely
 * upon drivers/sbus/अक्षर/sunserial.c which is:
 *
 * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 *
 * Adaptation to new UART layer is:
 *
 * Copyright (C) 2002 David S. Miller (davem@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/sunserialcore.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/prom.h>


अटल पूर्णांक sunserial_current_minor = 64;

पूर्णांक sunserial_रेजिस्टर_minors(काष्ठा uart_driver *drv, पूर्णांक count)
अणु
	पूर्णांक err = 0;

	drv->minor = sunserial_current_minor;
	drv->nr += count;
	/* Register the driver on the first call */
	अगर (drv->nr == count)
		err = uart_रेजिस्टर_driver(drv);
	अगर (err == 0) अणु
		sunserial_current_minor += count;
		drv->tty_driver->name_base = drv->minor - 64;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(sunserial_रेजिस्टर_minors);

व्योम sunserial_unरेजिस्टर_minors(काष्ठा uart_driver *drv, पूर्णांक count)
अणु
	drv->nr -= count;
	sunserial_current_minor -= count;

	अगर (drv->nr == 0)
		uart_unरेजिस्टर_driver(drv);
पूर्ण
EXPORT_SYMBOL(sunserial_unरेजिस्टर_minors);

पूर्णांक sunserial_console_match(काष्ठा console *con, काष्ठा device_node *dp,
			    काष्ठा uart_driver *drv, पूर्णांक line, bool ignore_line)
अणु
	अगर (!con)
		वापस 0;

	drv->cons = con;

	अगर (of_console_device != dp)
		वापस 0;

	अगर (!ignore_line) अणु
		पूर्णांक off = 0;

		अगर (of_console_options &&
		    *of_console_options == 'b')
			off = 1;

		अगर ((line & 1) != off)
			वापस 0;
	पूर्ण

	अगर (!console_set_on_cmdline) अणु
		con->index = line;
		add_preferred_console(con->name, line, शून्य);
	पूर्ण
	वापस 1;
पूर्ण
EXPORT_SYMBOL(sunserial_console_match);

व्योम sunserial_console_termios(काष्ठा console *con, काष्ठा device_node *uart_dp)
अणु
	स्थिर अक्षर *mode, *s;
	अक्षर mode_prop[] = "ttyX-mode";
	पूर्णांक baud, bits, stop, cflag;
	अक्षर parity;

	अगर (of_node_name_eq(uart_dp, "rsc") ||
	    of_node_name_eq(uart_dp, "rsc-console") ||
	    of_node_name_eq(uart_dp, "rsc-control")) अणु
		mode = of_get_property(uart_dp,
				       "ssp-console-modes", शून्य);
		अगर (!mode)
			mode = "115200,8,n,1,-";
	पूर्ण अन्यथा अगर (of_node_name_eq(uart_dp, "lom-console")) अणु
		mode = "9600,8,n,1,-";
	पूर्ण अन्यथा अणु
		काष्ठा device_node *dp;
		अक्षर c;

		c = 'a';
		अगर (of_console_options)
			c = *of_console_options;

		mode_prop[3] = c;

		dp = of_find_node_by_path("/options");
		mode = of_get_property(dp, mode_prop, शून्य);
		अगर (!mode)
			mode = "9600,8,n,1,-";
		of_node_put(dp);
	पूर्ण

	cflag = CREAD | HUPCL | CLOCAL;

	s = mode;
	baud = simple_म_से_अदीर्घ(s, शून्य, 0);
	s = म_अक्षर(s, ',');
	bits = simple_म_से_अदीर्घ(++s, शून्य, 0);
	s = म_अक्षर(s, ',');
	parity = *(++s);
	s = म_अक्षर(s, ',');
	stop = simple_म_से_अदीर्घ(++s, शून्य, 0);
	s = म_अक्षर(s, ',');
	/* XXX handshake is not handled here. */

	चयन (baud) अणु
		हाल 150: cflag |= B150; अवरोध;
		हाल 300: cflag |= B300; अवरोध;
		हाल 600: cflag |= B600; अवरोध;
		हाल 1200: cflag |= B1200; अवरोध;
		हाल 2400: cflag |= B2400; अवरोध;
		हाल 4800: cflag |= B4800; अवरोध;
		हाल 9600: cflag |= B9600; अवरोध;
		हाल 19200: cflag |= B19200; अवरोध;
		हाल 38400: cflag |= B38400; अवरोध;
		हाल 57600: cflag |= B57600; अवरोध;
		हाल 115200: cflag |= B115200; अवरोध;
		हाल 230400: cflag |= B230400; अवरोध;
		हाल 460800: cflag |= B460800; अवरोध;
		शेष: baud = 9600; cflag |= B9600; अवरोध;
	पूर्ण

	चयन (bits) अणु
		हाल 5: cflag |= CS5; अवरोध;
		हाल 6: cflag |= CS6; अवरोध;
		हाल 7: cflag |= CS7; अवरोध;
		हाल 8: cflag |= CS8; अवरोध;
		शेष: cflag |= CS8; अवरोध;
	पूर्ण

	चयन (parity) अणु
		हाल 'o': cflag |= (PARENB | PARODD); अवरोध;
		हाल 'e': cflag |= PARENB; अवरोध;
		हाल 'n': शेष: अवरोध;
	पूर्ण

	चयन (stop) अणु
		हाल 2: cflag |= CSTOPB; अवरोध;
		हाल 1: शेष: अवरोध;
	पूर्ण

	con->cflag = cflag;
पूर्ण

/* Sun serial MOUSE स्वतः baud rate detection.  */
अटल काष्ठा mouse_baud_cflag अणु
	पूर्णांक baud;
	अचिन्हित पूर्णांक cflag;
पूर्ण mouse_baud_table[] = अणु
	अणु 1200, B1200 पूर्ण,
	अणु 2400, B2400 पूर्ण,
	अणु 4800, B4800 पूर्ण,
	अणु 9600, B9600 पूर्ण,
	अणु -1, ~0 पूर्ण,
	अणु -1, ~0 पूर्ण,
पूर्ण;

अचिन्हित पूर्णांक suncore_mouse_baud_cflag_next(अचिन्हित पूर्णांक cflag, पूर्णांक *new_baud)
अणु
	पूर्णांक i;

	क्रम (i = 0; mouse_baud_table[i].baud != -1; i++)
		अगर (mouse_baud_table[i].cflag == (cflag & CBAUD))
			अवरोध;

	i += 1;
	अगर (mouse_baud_table[i].baud == -1)
		i = 0;

	*new_baud = mouse_baud_table[i].baud;
	वापस mouse_baud_table[i].cflag;
पूर्ण

EXPORT_SYMBOL(suncore_mouse_baud_cflag_next);

/* Basically, when the baud rate is wrong the mouse spits out
 * अवरोधs to us.
 */
पूर्णांक suncore_mouse_baud_detection(अचिन्हित अक्षर ch, पूर्णांक is_अवरोध)
अणु
	अटल पूर्णांक mouse_got_अवरोध = 0;
	अटल पूर्णांक ctr = 0;

	अगर (is_अवरोध) अणु
		/* Let a few normal bytes go by beक्रमe we jump the gun
		 * and say we need to try another baud rate.
		 */
		अगर (mouse_got_अवरोध && ctr < 8)
			वापस 1;

		/* Ok, we need to try another baud. */
		ctr = 0;
		mouse_got_अवरोध = 1;
		वापस 2;
	पूर्ण
	अगर (mouse_got_अवरोध) अणु
		ctr++;
		अगर (ch == 0x87) अणु
			/* Correct baud rate determined. */
			mouse_got_अवरोध = 0;
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(suncore_mouse_baud_detection);

अटल पूर्णांक __init suncore_init(व्योम)
अणु
	वापस 0;
पूर्ण
device_initcall(suncore_init);

#अगर 0 /* ..def MODULE ; never supported as such */
MODULE_AUTHOR("Eddie C. Dost, David S. Miller");
MODULE_DESCRIPTION("Sun serial common layer");
MODULE_LICENSE("GPL");
#पूर्ण_अगर

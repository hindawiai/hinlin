<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/serial_sci.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>

#घोषणा PSCR 0xA405011E

अटल व्योम sh7722_sci_init_pins(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag)
अणु
	अचिन्हित लघु data;

	अगर (port->mapbase == 0xffe00000) अणु
		data = __raw_पढ़ोw(PSCR);
		data &= ~0x03cf;
		अगर (!(cflag & CRTSCTS))
			data |= 0x0340;

		__raw_ग_लिखोw(data, PSCR);
	पूर्ण
पूर्ण

काष्ठा plat_sci_port_ops sh7722_sci_port_ops = अणु
	.init_pins	= sh7722_sci_init_pins,
पूर्ण;

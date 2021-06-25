<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/serial_sci.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>
#समावेश <cpu/serial.h>

#घोषणा PACR 0xa4050100
#घोषणा PBCR 0xa4050102

अटल व्योम sh7710_sci_init_pins(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag)
अणु
	अगर (port->mapbase == 0xA4400000) अणु
		__raw_ग_लिखोw(__raw_पढ़ोw(PACR) & 0xffc0, PACR);
		__raw_ग_लिखोw(__raw_पढ़ोw(PBCR) & 0x0fff, PBCR);
	पूर्ण अन्यथा अगर (port->mapbase == 0xA4410000)
		__raw_ग_लिखोw(__raw_पढ़ोw(PBCR) & 0xf003, PBCR);
पूर्ण

काष्ठा plat_sci_port_ops sh7710_sci_port_ops = अणु
	.init_pins	= sh7710_sci_init_pins,
पूर्ण;

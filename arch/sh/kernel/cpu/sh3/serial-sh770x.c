<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/serial_sci.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>
#समावेश <cpu/serial.h>

#घोषणा SCPCR 0xA4000116
#घोषणा SCPDR 0xA4000136

अटल व्योम sh770x_sci_init_pins(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag)
अणु
	अचिन्हित लघु data;

	/* We need to set SCPCR to enable RTS/CTS */
	data = __raw_पढ़ोw(SCPCR);
	/* Clear out SCP7MD1,0, SCP6MD1,0, SCP4MD1,0*/
	__raw_ग_लिखोw(data & 0x0fcf, SCPCR);

	अगर (!(cflag & CRTSCTS)) अणु
		/* We need to set SCPCR to enable RTS/CTS */
		data = __raw_पढ़ोw(SCPCR);
		/* Clear out SCP7MD1,0, SCP4MD1,0,
		   Set SCP6MD1,0 = अणु01पूर्ण (output)  */
		__raw_ग_लिखोw((data & 0x0fcf) | 0x1000, SCPCR);

		data = __raw_पढ़ोb(SCPDR);
		/* Set /RTS2 (bit6) = 0 */
		__raw_ग_लिखोb(data & 0xbf, SCPDR);
	पूर्ण
पूर्ण

काष्ठा plat_sci_port_ops sh770x_sci_port_ops = अणु
	.init_pins	= sh770x_sci_init_pins,
पूर्ण;

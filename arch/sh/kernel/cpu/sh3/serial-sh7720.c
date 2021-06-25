<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/serial_sci.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>
#समावेश <cpu/serial.h>
#समावेश <cpu/gpपन.स>

अटल व्योम sh7720_sci_init_pins(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag)
अणु
	अचिन्हित लघु data;

	अगर (cflag & CRTSCTS) अणु
		/* enable RTS/CTS */
		अगर (port->mapbase == 0xa4430000) अणु /* SCIF0 */
			/* Clear PTCR bit 9-2; enable all scअगर pins but sck */
			data = __raw_पढ़ोw(PORT_PTCR);
			__raw_ग_लिखोw((data & 0xfc03), PORT_PTCR);
		पूर्ण अन्यथा अगर (port->mapbase == 0xa4438000) अणु /* SCIF1 */
			/* Clear PVCR bit 9-2 */
			data = __raw_पढ़ोw(PORT_PVCR);
			__raw_ग_लिखोw((data & 0xfc03), PORT_PVCR);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (port->mapbase == 0xa4430000) अणु /* SCIF0 */
			/* Clear PTCR bit 5-2; enable only tx and rx  */
			data = __raw_पढ़ोw(PORT_PTCR);
			__raw_ग_लिखोw((data & 0xffc3), PORT_PTCR);
		पूर्ण अन्यथा अगर (port->mapbase == 0xa4438000) अणु /* SCIF1 */
			/* Clear PVCR bit 5-2 */
			data = __raw_पढ़ोw(PORT_PVCR);
			__raw_ग_लिखोw((data & 0xffc3), PORT_PVCR);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा plat_sci_port_ops sh7720_sci_port_ops = अणु
	.init_pins	= sh7720_sci_init_pins,
पूर्ण;

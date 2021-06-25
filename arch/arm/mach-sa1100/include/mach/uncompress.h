<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-sa1100/include/mach/uncompress.h
 *
 * (C) 1999 Nicolas Pitre <nico@fluxnic.net>
 *
 * Reorganised to be machine independent.
 */

#समावेश "hardware.h"

#घोषणा IOMEM(x)	(x)

/*
 * The following code assumes the serial port has alपढ़ोy been
 * initialized by the bootloader.  We search क्रम the first enabled
 * port in the most probable order.  If you didn't setup a port in
 * your bootloader then nothing will appear (which might be desired).
 */

#घोषणा UART(x)		(*(अस्थिर अचिन्हित दीर्घ *)(serial_port + (x)))

अटल अंतरभूत व्योम अ_दो(पूर्णांक c)
अणु
	अचिन्हित दीर्घ serial_port;

	करो अणु
		serial_port = _Ser3UTCR0;
		अगर (UART(UTCR3) & UTCR3_TXE) अवरोध;
		serial_port = _Ser1UTCR0;
		अगर (UART(UTCR3) & UTCR3_TXE) अवरोध;
		serial_port = _Ser2UTCR0;
		अगर (UART(UTCR3) & UTCR3_TXE) अवरोध;
		वापस;
	पूर्ण जबतक (0);

	/* रुको क्रम space in the UART's transmitter */
	जबतक (!(UART(UTSR1) & UTSR1_TNF))
		barrier();

	/* send the अक्षरacter out. */
	UART(UTDR) = c;
पूर्ण

अटल अंतरभूत व्योम flush(व्योम)
अणु
पूर्ण

/*
 * Nothing to करो क्रम these
 */
#घोषणा arch_decomp_setup()

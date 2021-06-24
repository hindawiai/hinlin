<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-m68k/serial.h
 *
 * currently this seems useful only क्रम a Q40,
 * it's an almost exact copy of ../यंत्र-alpha/serial.h
 *
 */


/*
 * This assumes you have a 1.8432 MHz घड़ी क्रम your UART.
 *
 * It'd be nice अगर someone built a serial card with a 24.576 MHz
 * घड़ी, since the 16550A is capable of handling a top speed of 1.5
 * megabits/second; but this requires the faster घड़ी.
 */
#घोषणा BASE_BAUD ( 1843200 / 16 )

/* Standard COM flags (except क्रम COM4, because of the 8514 problem) */
#अगर_घोषित CONFIG_SERIAL_8250_DETECT_IRQ
#घोषणा STD_COM_FLAGS (UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_AUTO_IRQ)
#घोषणा STD_COM4_FLAGS (UPF_BOOT_AUTOCONF | UPF_AUTO_IRQ)
#अन्यथा
#घोषणा STD_COM_FLAGS (UPF_BOOT_AUTOCONF | UPF_SKIP_TEST)
#घोषणा STD_COM4_FLAGS UPF_BOOT_AUTOCONF
#पूर्ण_अगर

#अगर_घोषित CONFIG_ISA
#घोषणा SERIAL_PORT_DFNS			\
	/* UART CLK   PORT IRQ     FLAGS        */			\
	अणु 0, BASE_BAUD, 0x3F8, 4, STD_COM_FLAGS पूर्ण,	/* ttyS0 */	\
	अणु 0, BASE_BAUD, 0x2F8, 3, STD_COM_FLAGS पूर्ण,	/* ttyS1 */	\
	अणु 0, BASE_BAUD, 0x3E8, 4, STD_COM_FLAGS पूर्ण,	/* ttyS2 */	\
	अणु 0, BASE_BAUD, 0x2E8, 3, STD_COM4_FLAGS पूर्ण,	/* ttyS3 */
#पूर्ण_अगर

<शैली गुरु>
/*
 * Derived from the i386 version.
 */

/*
 * This assumes you have a 1.8432 MHz घड़ी क्रम your UART.
 *
 * It'd be nice अगर someone built a serial card with a 24.576 MHz
 * घड़ी, since the 16550A is capable of handling a top speed of 1.5
 * megabits/second; but this requires the faster घड़ी.
 */
#घोषणा BASE_BAUD ( 1843200 / 16 )

/*
 * All legacy serial ports should be क्रमागतerated via ACPI namespace, so
 * we need not list them here.
 */

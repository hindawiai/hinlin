<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * dz.h: Serial port driver क्रम DECstations equipped
 *       with the DZ chipset.
 *
 * Copyright (C) 1998 Olivier A. D. Lebaillअगर 
 *             
 * Email: olivier.lebaillअगर@अगरrsys.com
 *
 * Copyright (C) 2004, 2006  Maciej W. Rozycki
 */
#अगर_अघोषित DZ_SERIAL_H
#घोषणा DZ_SERIAL_H

/*
 * Definitions क्रम the Control and Status Register.
 */
#घोषणा DZ_TRDY        0x8000                 /* Transmitter empty */
#घोषणा DZ_TIE         0x4000                 /* Transmitter Interrupt Enbl */
#घोषणा DZ_TLINE       0x0300                 /* Transmitter Line Number */
#घोषणा DZ_RDONE       0x0080                 /* Receiver data पढ़ोy */
#घोषणा DZ_RIE         0x0040                 /* Receive Interrupt Enable */
#घोषणा DZ_MSE         0x0020                 /* Master Scan Enable */
#घोषणा DZ_CLR         0x0010                 /* Master reset */
#घोषणा DZ_MAINT       0x0008                 /* Loop Back Mode */

/*
 * Definitions क्रम the Receiver Buffer Register.
 */
#घोषणा DZ_RBUF_MASK   0x00FF                 /* Data Mask */
#घोषणा DZ_LINE_MASK   0x0300                 /* Line Mask */
#घोषणा DZ_DVAL        0x8000                 /* Valid Data indicator */
#घोषणा DZ_OERR        0x4000                 /* Overrun error indicator */
#घोषणा DZ_FERR        0x2000                 /* Frame error indicator */
#घोषणा DZ_PERR        0x1000                 /* Parity error indicator */

#घोषणा DZ_BREAK       0x0800                 /* BREAK event software flag */

#घोषणा LINE(x) ((x & DZ_LINE_MASK) >> 8)     /* Get the line number
                                                 from the input buffer */
#घोषणा UCHAR(x) ((अचिन्हित अक्षर)(x & DZ_RBUF_MASK))

/*
 * Definitions क्रम the Transmit Control Register.
 */
#घोषणा DZ_LINE_KEYBOARD 0x0001
#घोषणा DZ_LINE_MOUSE    0x0002
#घोषणा DZ_LINE_MODEM    0x0004
#घोषणा DZ_LINE_PRINTER  0x0008

#घोषणा DZ_MODEM_RTS     0x0800               /* RTS क्रम the modem line (2) */
#घोषणा DZ_MODEM_DTR     0x0400               /* DTR क्रम the modem line (2) */
#घोषणा DZ_PRINT_RTS     0x0200               /* RTS क्रम the prntr line (3) */
#घोषणा DZ_PRINT_DTR     0x0100               /* DTR क्रम the prntr line (3) */
#घोषणा DZ_LNENB         0x000f               /* Transmitter Line Enable */

/*
 * Definitions क्रम the Modem Status Register.
 */
#घोषणा DZ_MODEM_RI      0x0800               /* RI क्रम the modem line (2) */
#घोषणा DZ_MODEM_CD      0x0400               /* CD क्रम the modem line (2) */
#घोषणा DZ_MODEM_DSR     0x0200               /* DSR क्रम the modem line (2) */
#घोषणा DZ_MODEM_CTS     0x0100               /* CTS क्रम the modem line (2) */
#घोषणा DZ_PRINT_RI      0x0008               /* RI क्रम the prपूर्णांकer line (3) */
#घोषणा DZ_PRINT_CD      0x0004               /* CD क्रम the prपूर्णांकer line (3) */
#घोषणा DZ_PRINT_DSR     0x0002               /* DSR क्रम the prntr line (3) */
#घोषणा DZ_PRINT_CTS     0x0001               /* CTS क्रम the prntr line (3) */

/*
 * Definitions क्रम the Transmit Data Register.
 */
#घोषणा DZ_BRK0          0x0100               /* Break निश्चितion क्रम line 0 */
#घोषणा DZ_BRK1          0x0200               /* Break निश्चितion क्रम line 1 */
#घोषणा DZ_BRK2          0x0400               /* Break निश्चितion क्रम line 2 */
#घोषणा DZ_BRK3          0x0800               /* Break निश्चितion क्रम line 3 */

/*
 * Definitions क्रम the Line Parameter Register.
 */
#घोषणा DZ_KEYBOARD      0x0000               /* line 0 = keyboard */
#घोषणा DZ_MOUSE         0x0001               /* line 1 = mouse */
#घोषणा DZ_MODEM         0x0002               /* line 2 = modem */
#घोषणा DZ_PRINTER       0x0003               /* line 3 = prपूर्णांकer */

#घोषणा DZ_CSIZE         0x0018               /* Number of bits per byte (mask) */
#घोषणा DZ_CS5           0x0000               /* 5 bits per byte */
#घोषणा DZ_CS6           0x0008               /* 6 bits per byte */
#घोषणा DZ_CS7           0x0010               /* 7 bits per byte */
#घोषणा DZ_CS8           0x0018               /* 8 bits per byte */

#घोषणा DZ_CSTOPB        0x0020               /* 2 stop bits instead of one */ 

#घोषणा DZ_PARENB        0x0040               /* Parity enable */
#घोषणा DZ_PARODD        0x0080               /* Odd parity instead of even */

#घोषणा DZ_CBAUD         0x0E00               /* Baud Rate (mask) */
#घोषणा DZ_B50           0x0000
#घोषणा DZ_B75           0x0100
#घोषणा DZ_B110          0x0200
#घोषणा DZ_B134          0x0300
#घोषणा DZ_B150          0x0400
#घोषणा DZ_B300          0x0500
#घोषणा DZ_B600          0x0600
#घोषणा DZ_B1200         0x0700 
#घोषणा DZ_B1800         0x0800
#घोषणा DZ_B2000         0x0900
#घोषणा DZ_B2400         0x0A00
#घोषणा DZ_B3600         0x0B00
#घोषणा DZ_B4800         0x0C00
#घोषणा DZ_B7200         0x0D00
#घोषणा DZ_B9600         0x0E00

#घोषणा DZ_RXENAB        0x1000               /* Receiver Enable */

/*
 * Addresses क्रम the DZ रेजिस्टरs
 */
#घोषणा DZ_CSR       0x00            /* Control and Status Register */
#घोषणा DZ_RBUF      0x08            /* Receive Buffer */
#घोषणा DZ_LPR       0x08            /* Line Parameters Register */
#घोषणा DZ_TCR       0x10            /* Transmitter Control Register */
#घोषणा DZ_MSR       0x18            /* Modem Status Register */
#घोषणा DZ_TDR       0x18            /* Transmit Data Register */

#घोषणा DZ_NB_PORT 4

#घोषणा DZ_XMIT_SIZE   4096                 /* buffer size */
#घोषणा DZ_WAKEUP_CHARS   DZ_XMIT_SIZE/4

#पूर्ण_अगर /* DZ_SERIAL_H */

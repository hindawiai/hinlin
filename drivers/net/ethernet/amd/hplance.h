<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Ranकरोm defines and काष्ठाures क्रम the HP Lance driver.
 * Copyright (C) 05/1998 Peter Maydell <pmaydell@chiark.greenend.org.uk>
 * Based on the Sun Lance driver and the NetBSD HP Lance driver
 */

/* Registers */
#घोषणा HPLANCE_ID		0x01		/* DIO रेजिस्टर: ID byte */
#घोषणा HPLANCE_STATUS		0x03		/* DIO रेजिस्टर: पूर्णांकerrupt enable/status */

/* Control and status bits क्रम the status रेजिस्टर */
#घोषणा LE_IE 0x80                                /* पूर्णांकerrupt enable */
#घोषणा LE_IR 0x40                                /* पूर्णांकerrupt requested */
#घोषणा LE_LOCK 0x08                              /* lock status रेजिस्टर */
#घोषणा LE_ACK 0x04                               /* ack of lock */
#घोषणा LE_JAB 0x02                               /* loss of tx घड़ी (???) */
/* We can also extract the IPL from the status रेजिस्टर with the standard
 * DIO_IPL(hplance) macro, or using dio_scodetoipl()
 */

/* These are the offsets क्रम the DIO regs (hplance_reg), lance_ioreg,
 * memory and NVRAM:
 */
#घोषणा HPLANCE_IDOFF 0                           /* board baseaddr */
#घोषणा HPLANCE_REGOFF 0x4000                     /* lance रेजिस्टरs */
#घोषणा HPLANCE_MEMOFF 0x8000                     /* काष्ठा lance_init_block */
#घोषणा HPLANCE_NVRAMOFF 0xC008                   /* etheraddress as one *nibble* per byte */

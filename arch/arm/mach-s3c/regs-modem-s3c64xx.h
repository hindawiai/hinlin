<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      http://armlinux.simtec.co.uk/
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * S3C64XX - modem block रेजिस्टरs
 */

#अगर_अघोषित __MACH_S3C64XX_REGS_MODEM_H
#घोषणा __MACH_S3C64XX_REGS_MODEM_H __खाता__

#घोषणा S3C64XX_MODEMREG(x)			(S3C64XX_VA_MODEM + (x))

#घोषणा S3C64XX_MODEM_INT2AP			S3C64XX_MODEMREG(0x0)
#घोषणा S3C64XX_MODEM_INT2MODEM			S3C64XX_MODEMREG(0x4)
#घोषणा S3C64XX_MODEM_MIFCON			S3C64XX_MODEMREG(0x8)
#घोषणा S3C64XX_MODEM_MIFPCON			S3C64XX_MODEMREG(0xC)
#घोषणा S3C64XX_MODEM_INTCLR			S3C64XX_MODEMREG(0x10)
#घोषणा S3C64XX_MODEM_DMA_TXADDR		S3C64XX_MODEMREG(0x14)
#घोषणा S3C64XX_MODEM_DMA_RXADDR		S3C64XX_MODEMREG(0x18)

#घोषणा MIFPCON_INT2M_LEVEL			(1 << 4)
#घोषणा MIFPCON_LCD_BYPASS			(1 << 3)

#पूर्ण_अगर /* __MACH_S3C64XX_REGS_MODEM_H */

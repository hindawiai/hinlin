<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      http://armlinux.simtec.co.uk/
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - USB2.0 Highspeed/OtG device PHY रेजिस्टरs
*/

/* Note, this is a separate header file as some of the घड़ी framework
 * needs to touch this अगर the clk_48m is used as the USB OHCI or other
 * peripheral source.
*/

#अगर_अघोषित __PLAT_S3C64XX_REGS_USB_HSOTG_PHY_H
#घोषणा __PLAT_S3C64XX_REGS_USB_HSOTG_PHY_H __खाता__

/* S3C64XX_PA_USB_HSPHY */

#घोषणा S3C_HSOTG_PHYREG(x)	((x) + S3C_VA_USB_HSPHY)

#घोषणा S3C_PHYPWR				S3C_HSOTG_PHYREG(0x00)
#घोषणा S3C_PHYPWR_NORMAL_MASK			(0x19 << 0)
#घोषणा S3C_PHYPWR_OTG_DISABLE			(1 << 4)
#घोषणा S3C_PHYPWR_ANALOG_POWERDOWN		(1 << 3)
#घोषणा SRC_PHYPWR_FORCE_SUSPEND		(1 << 1)

#घोषणा S3C_PHYCLK				S3C_HSOTG_PHYREG(0x04)
#घोषणा S3C_PHYCLK_MODE_USB11			(1 << 6)
#घोषणा S3C_PHYCLK_EXT_OSC			(1 << 5)
#घोषणा S3C_PHYCLK_CLK_FORCE			(1 << 4)
#घोषणा S3C_PHYCLK_ID_PULL			(1 << 2)
#घोषणा S3C_PHYCLK_CLKSEL_MASK			(0x3 << 0)
#घोषणा S3C_PHYCLK_CLKSEL_SHIFT			(0)
#घोषणा S3C_PHYCLK_CLKSEL_48M			(0x0 << 0)
#घोषणा S3C_PHYCLK_CLKSEL_12M			(0x2 << 0)
#घोषणा S3C_PHYCLK_CLKSEL_24M			(0x3 << 0)

#घोषणा S3C_RSTCON				S3C_HSOTG_PHYREG(0x08)
#घोषणा S3C_RSTCON_PHYCLK			(1 << 2)
#घोषणा S3C_RSTCON_HCLK				(1 << 1)
#घोषणा S3C_RSTCON_PHY				(1 << 0)

#घोषणा S3C_PHYTUNE				S3C_HSOTG_PHYREG(0x20)

#पूर्ण_अगर /* __PLAT_S3C64XX_REGS_USB_HSOTG_PHY_H */

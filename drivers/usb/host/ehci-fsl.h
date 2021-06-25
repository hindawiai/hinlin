<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2005-2010,2012 Freescale Semiconductor, Inc.
 * Copyright (c) 2005 MontaVista Software
 */
#अगर_अघोषित _EHCI_FSL_H
#घोषणा _EHCI_FSL_H

/* offsets क्रम the non-ehci रेजिस्टरs in the FSL SOC USB controller */
#घोषणा FSL_SOC_USB_SBUSCFG	0x90
#घोषणा SBUSCFG_INCR8		0x02	/* INCR8, specअगरied */
#घोषणा FSL_SOC_USB_ULPIVP	0x170
#घोषणा FSL_SOC_USB_PORTSC1	0x184
#घोषणा PORT_PTS_MSK		(3<<30)
#घोषणा PORT_PTS_UTMI		(0<<30)
#घोषणा PORT_PTS_ULPI		(2<<30)
#घोषणा	PORT_PTS_SERIAL		(3<<30)
#घोषणा PORT_PTS_PTW		(1<<28)
#घोषणा FSL_SOC_USB_PORTSC2	0x188
#घोषणा FSL_SOC_USB_USBMODE	0x1a8
#घोषणा USBMODE_CM_MASK		(3 << 0)	/* controller mode mask */
#घोषणा USBMODE_CM_HOST		(3 << 0)	/* controller mode: host */
#घोषणा USBMODE_ES		(1 << 2)	/* (Big) Endian Select */

#घोषणा FSL_SOC_USB_USBGENCTRL	0x200
#घोषणा USBGENCTRL_PPP		(1 << 3)
#घोषणा USBGENCTRL_PFP		(1 << 2)
#घोषणा FSL_SOC_USB_ISIPHYCTRL	0x204
#घोषणा ISIPHYCTRL_PXE		(1)
#घोषणा ISIPHYCTRL_PHYE		(1 << 4)

#घोषणा FSL_SOC_USB_SNOOP1	0x400	/* NOTE: big-endian */
#घोषणा FSL_SOC_USB_SNOOP2	0x404	/* NOTE: big-endian */
#घोषणा FSL_SOC_USB_AGECNTTHRSH	0x408	/* NOTE: big-endian */
#घोषणा FSL_SOC_USB_PRICTRL	0x40c	/* NOTE: big-endian */
#घोषणा FSL_SOC_USB_SICTRL	0x410	/* NOTE: big-endian */
#घोषणा FSL_SOC_USB_CTRL	0x500	/* NOTE: big-endian */
#घोषणा CTRL_UTMI_PHY_EN	(1<<9)
#घोषणा CTRL_PHY_CLK_VALID	(1 << 17)
#घोषणा SNOOP_SIZE_2GB		0x1e

/* control Register Bit Masks */
#घोषणा CONTROL_REGISTER_W1C_MASK       0x00020000  /* W1C: PHY_CLK_VALID */
#घोषणा ULPI_INT_EN             (1<<0)
#घोषणा WU_INT_EN               (1<<1)
#घोषणा USB_CTRL_USB_EN         (1<<2)
#घोषणा LINE_STATE_FILTER__EN   (1<<3)
#घोषणा KEEP_OTG_ON             (1<<4)
#घोषणा OTG_PORT                (1<<5)
#घोषणा PLL_RESET               (1<<8)
#घोषणा UTMI_PHY_EN             (1<<9)
#घोषणा ULPI_PHY_CLK_SEL        (1<<10)
#घोषणा PHY_CLK_VALID		(1<<17)

/* Retry count क्रम checking UTMI PHY CLK validity */
#घोषणा UTMI_PHY_CLK_VALID_CHK_RETRY 5
#पूर्ण_अगर				/* _EHCI_FSL_H */

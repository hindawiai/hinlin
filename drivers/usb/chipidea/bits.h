<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * bits.h - रेजिस्टर bits of the ChipIdea USB IP core
 *
 * Copyright (C) 2008 Chipidea - MIPS Technologies, Inc. All rights reserved.
 *
 * Author: David Lopo
 */

#अगर_अघोषित __DRIVERS_USB_CHIPIDEA_BITS_H
#घोषणा __DRIVERS_USB_CHIPIDEA_BITS_H

#समावेश <linux/usb/ehci_def.h>

/*
 * ID
 * For 1.x revision, bit24 - bit31 are reserved
 * For 2.x revision, bit25 - bit28 are 0x2
 */
#घोषणा TAG		      (0x1F << 16)
#घोषणा REVISION	      (0xF << 21)
#घोषणा VERSION		      (0xF << 25)
#घोषणा CIVERSION	      (0x7 << 29)

/* SBUSCFG */
#घोषणा AHBBRST_MASK		0x7

/* HCCPARAMS */
#घोषणा HCCPARAMS_LEN         BIT(17)

/* DCCPARAMS */
#घोषणा DCCPARAMS_DEN         (0x1F << 0)
#घोषणा DCCPARAMS_DC          BIT(7)
#घोषणा DCCPARAMS_HC          BIT(8)

/* TESTMODE */
#घोषणा TESTMODE_FORCE        BIT(0)

/* USBCMD */
#घोषणा USBCMD_RS             BIT(0)
#घोषणा USBCMD_RST            BIT(1)
#घोषणा USBCMD_SUTW           BIT(13)
#घोषणा USBCMD_ATDTW          BIT(14)

/* USBSTS & USBINTR */
#घोषणा USBi_UI               BIT(0)
#घोषणा USBi_UEI              BIT(1)
#घोषणा USBi_PCI              BIT(2)
#घोषणा USBi_URI              BIT(6)
#घोषणा USBi_SLI              BIT(8)

/* DEVICEADDR */
#घोषणा DEVICEADDR_USBADRA    BIT(24)
#घोषणा DEVICEADDR_USBADR     (0x7FUL << 25)

/* TTCTRL */
#घोषणा TTCTRL_TTHA_MASK	(0x7fUL << 24)
/* Set non-zero value क्रम पूर्णांकernal TT Hub address representation */
#घोषणा TTCTRL_TTHA		(0x7fUL << 24)

/* BURSTSIZE */
#घोषणा RX_BURST_MASK		0xff
#घोषणा TX_BURST_MASK		0xff00

/* PORTSC */
#घोषणा PORTSC_CCS            BIT(0)
#घोषणा PORTSC_CSC            BIT(1)
#घोषणा PORTSC_PEC            BIT(3)
#घोषणा PORTSC_OCC            BIT(5)
#घोषणा PORTSC_FPR            BIT(6)
#घोषणा PORTSC_SUSP           BIT(7)
#घोषणा PORTSC_HSP            BIT(9)
#घोषणा PORTSC_PP             BIT(12)
#घोषणा PORTSC_PTC            (0x0FUL << 16)
#घोषणा PORTSC_WKCN           BIT(20)
#घोषणा PORTSC_PHCD(d)	      ((d) ? BIT(22) : BIT(23))
/* PTS and PTW क्रम non lpm version only */
#घोषणा PORTSC_PFSC           BIT(24)
#घोषणा PORTSC_PTS(d)						\
	(u32)((((d) & 0x3) << 30) | (((d) & 0x4) ? BIT(25) : 0))
#घोषणा PORTSC_PTW            BIT(28)
#घोषणा PORTSC_STS            BIT(29)

#घोषणा PORTSC_W1C_BITS						\
	(PORTSC_CSC | PORTSC_PEC | PORTSC_OCC)

/* DEVLC */
#घोषणा DEVLC_PFSC            BIT(23)
#घोषणा DEVLC_PSPD            (0x03UL << 25)
#घोषणा DEVLC_PSPD_HS         (0x02UL << 25)
#घोषणा DEVLC_PTW             BIT(27)
#घोषणा DEVLC_STS             BIT(28)
#घोषणा DEVLC_PTS(d)          (u32)(((d) & 0x7) << 29)

/* Encoding क्रम DEVLC_PTS and PORTSC_PTS */
#घोषणा PTS_UTMI              0
#घोषणा PTS_ULPI              2
#घोषणा PTS_SERIAL            3
#घोषणा PTS_HSIC              4

/* OTGSC */
#घोषणा OTGSC_IDPU	      BIT(5)
#घोषणा OTGSC_HADP	      BIT(6)
#घोषणा OTGSC_HABA	      BIT(7)
#घोषणा OTGSC_ID	      BIT(8)
#घोषणा OTGSC_AVV	      BIT(9)
#घोषणा OTGSC_ASV	      BIT(10)
#घोषणा OTGSC_BSV	      BIT(11)
#घोषणा OTGSC_BSE	      BIT(12)
#घोषणा OTGSC_IDIS	      BIT(16)
#घोषणा OTGSC_AVVIS	      BIT(17)
#घोषणा OTGSC_ASVIS	      BIT(18)
#घोषणा OTGSC_BSVIS	      BIT(19)
#घोषणा OTGSC_BSEIS	      BIT(20)
#घोषणा OTGSC_1MSIS	      BIT(21)
#घोषणा OTGSC_DPIS	      BIT(22)
#घोषणा OTGSC_IDIE	      BIT(24)
#घोषणा OTGSC_AVVIE	      BIT(25)
#घोषणा OTGSC_ASVIE	      BIT(26)
#घोषणा OTGSC_BSVIE	      BIT(27)
#घोषणा OTGSC_BSEIE	      BIT(28)
#घोषणा OTGSC_1MSIE	      BIT(29)
#घोषणा OTGSC_DPIE	      BIT(30)
#घोषणा OTGSC_INT_EN_BITS	(OTGSC_IDIE | OTGSC_AVVIE | OTGSC_ASVIE \
				| OTGSC_BSVIE | OTGSC_BSEIE | OTGSC_1MSIE \
				| OTGSC_DPIE)
#घोषणा OTGSC_INT_STATUS_BITS	(OTGSC_IDIS | OTGSC_AVVIS | OTGSC_ASVIS	\
				| OTGSC_BSVIS | OTGSC_BSEIS | OTGSC_1MSIS \
				| OTGSC_DPIS)

/* USBMODE */
#घोषणा USBMODE_CM            (0x03UL <<  0)
#घोषणा USBMODE_CM_DC         (0x02UL <<  0)
#घोषणा USBMODE_SLOM          BIT(3)
#घोषणा USBMODE_CI_SDIS       BIT(4)

/* ENDPTCTRL */
#घोषणा ENDPTCTRL_RXS         BIT(0)
#घोषणा ENDPTCTRL_RXT         (0x03UL <<  2)
#घोषणा ENDPTCTRL_RXR         BIT(6)         /* reserved क्रम port 0 */
#घोषणा ENDPTCTRL_RXE         BIT(7)
#घोषणा ENDPTCTRL_TXS         BIT(16)
#घोषणा ENDPTCTRL_TXT         (0x03UL << 18)
#घोषणा ENDPTCTRL_TXR         BIT(22)        /* reserved क्रम port 0 */
#घोषणा ENDPTCTRL_TXE         BIT(23)

#पूर्ण_अगर /* __DRIVERS_USB_CHIPIDEA_BITS_H */

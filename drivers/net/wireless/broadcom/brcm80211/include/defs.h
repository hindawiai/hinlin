<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित	_BRCM_DEFS_H_
#घोषणा	_BRCM_DEFS_H_

#समावेश <linux/types.h>

#घोषणा	SI_BUS			0
#घोषणा	PCI_BUS			1
#घोषणा	PCMCIA_BUS		2
#घोषणा SDIO_BUS		3
#घोषणा JTAG_BUS		4
#घोषणा USB_BUS			5
#घोषणा SPI_BUS			6

#घोषणा	OFF	0
#घोषणा	ON	1		/* ON = 1 */
#घोषणा	AUTO	(-1)		/* Auto = -1 */

/*
 * Priority definitions according 802.1D
 */
#घोषणा	PRIO_8021D_NONE		2
#घोषणा	PRIO_8021D_BK		1
#घोषणा	PRIO_8021D_BE		0
#घोषणा	PRIO_8021D_EE		3
#घोषणा	PRIO_8021D_CL		4
#घोषणा	PRIO_8021D_VI		5
#घोषणा	PRIO_8021D_VO		6
#घोषणा	PRIO_8021D_NC		7

#घोषणा	MAXPRIO			7
#घोषणा NUMPRIO			(MAXPRIO + 1)

#घोषणा WL_NUMRATES		16	/* max # of rates in a rateset */

#घोषणा BRCM_CNTRY_BUF_SZ	4	/* Country string is 3 bytes + NUL */

#घोषणा BRCM_SET_CHANNEL	30
#घोषणा BRCM_SET_SRL		32
#घोषणा BRCM_SET_LRL		34
#घोषणा BRCM_SET_BCNPRD		76

#घोषणा BRCM_GET_CURR_RATESET	114	/* current rateset */
#घोषणा BRCM_GET_PHYLIST	180

/* Bit masks क्रम radio disabled status - वापसed by WL_GET_RADIO */

#घोषणा WL_RADIO_SW_DISABLE		(1<<0)
#घोषणा WL_RADIO_HW_DISABLE		(1<<1)
/* some countries करोn't support any channel */
#घोषणा WL_RADIO_COUNTRY_DISABLE	(1<<3)

/* Override bit क्रम SET_TXPWR.  अगर set, ignore other level limits */
#घोषणा WL_TXPWR_OVERRIDE	(1U<<31)

/* band types */
#घोषणा	BRCM_BAND_AUTO		0	/* स्वतः-select */
#घोषणा	BRCM_BAND_5G		1	/* 5 Ghz */
#घोषणा	BRCM_BAND_2G		2	/* 2.4 Ghz */
#घोषणा	BRCM_BAND_ALL		3	/* all bands */

/* Debug levels */
#घोषणा BRCM_DL_INFO		0x00000001
#घोषणा BRCM_DL_MAC80211	0x00000002
#घोषणा BRCM_DL_RX		0x00000004
#घोषणा BRCM_DL_TX		0x00000008
#घोषणा BRCM_DL_INT		0x00000010
#घोषणा BRCM_DL_DMA		0x00000020
#घोषणा BRCM_DL_HT		0x00000040

/* Values क्रम PM */
#घोषणा PM_OFF	0
#घोषणा PM_MAX	1
#घोषणा PM_FAST 2

/*
 * Sonics Configuration Space Registers.
 */

/* core sbconfig regs are top 256bytes of regs */
#घोषणा	SBCONFIGOFF		0xf00

/* cpp contortions to concatenate w/arg prescan */
#अगर_अघोषित	PAD
#घोषणा	_PADLINE(line)	pad ## line
#घोषणा	_XSTR(line)	_PADLINE(line)
#घोषणा	PAD		_XSTR(__LINE__)
#पूर्ण_अगर

#पूर्ण_अगर				/* _BRCM_DEFS_H_ */

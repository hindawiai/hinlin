<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2001-2002 by David Brownell
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __LINUX_USB_EHCI_DEF_H
#घोषणा __LINUX_USB_EHCI_DEF_H

#समावेश <linux/usb/ehci-dbgp.h>

/* EHCI रेजिस्टर पूर्णांकerface, corresponds to EHCI Revision 0.95 specअगरication */

/* Section 2.2 Host Controller Capability Registers */
काष्ठा ehci_caps अणु
	/* these fields are specअगरied as 8 and 16 bit रेजिस्टरs,
	 * but some hosts can't perक्रमm 8 or 16 bit PCI accesses.
	 * some hosts treat caplength and hciversion as parts of a 32-bit
	 * रेजिस्टर, others treat them as two separate रेजिस्टरs, this
	 * affects the memory map क्रम big endian controllers.
	 */
	u32		hc_capbase;
#घोषणा HC_LENGTH(ehci, p)	(0x00ff&((p) >> /* bits 7:0 / offset 00h */ \
				(ehci_big_endian_capbase(ehci) ? 24 : 0)))
#घोषणा HC_VERSION(ehci, p)	(0xffff&((p) >> /* bits 31:16 / offset 02h */ \
				(ehci_big_endian_capbase(ehci) ? 0 : 16)))
	u32		hcs_params;     /* HCSPARAMS - offset 0x4 */
#घोषणा HCS_DEBUG_PORT(p)	(((p)>>20)&0xf)	/* bits 23:20, debug port? */
#घोषणा HCS_INDICATOR(p)	((p)&(1 << 16))	/* true: has port indicators */
#घोषणा HCS_N_CC(p)		(((p)>>12)&0xf)	/* bits 15:12, #companion HCs */
#घोषणा HCS_N_PCC(p)		(((p)>>8)&0xf)	/* bits 11:8, ports per CC */
#घोषणा HCS_PORTROUTED(p)	((p)&(1 << 7))	/* true: port routing */
#घोषणा HCS_PPC(p)		((p)&(1 << 4))	/* true: port घातer control */
#घोषणा HCS_N_PORTS(p)		(((p)>>0)&0xf)	/* bits 3:0, ports on HC */

	u32		hcc_params;      /* HCCPARAMS - offset 0x8 */
/* EHCI 1.1 addendum */
#घोषणा HCC_32FRAME_PERIODIC_LIST(p)	((p)&(1 << 19))
#घोषणा HCC_PER_PORT_CHANGE_EVENT(p)	((p)&(1 << 18))
#घोषणा HCC_LPM(p)			((p)&(1 << 17))
#घोषणा HCC_HW_PREFETCH(p)		((p)&(1 << 16))

#घोषणा HCC_EXT_CAPS(p)		(((p)>>8)&0xff)	/* क्रम pci extended caps */
#घोषणा HCC_ISOC_CACHE(p)       ((p)&(1 << 7))  /* true: can cache isoc frame */
#घोषणा HCC_ISOC_THRES(p)       (((p)>>4)&0x7)  /* bits 6:4, uframes cached */
#घोषणा HCC_CANPARK(p)		((p)&(1 << 2))  /* true: can park on async qh */
#घोषणा HCC_PGM_FRAMELISTLEN(p) ((p)&(1 << 1))  /* true: periodic_size changes*/
#घोषणा HCC_64BIT_ADDR(p)       ((p)&(1))       /* true: can use 64-bit addr */
	u8		portroute[8];	 /* nibbles क्रम routing - offset 0xC */
पूर्ण;


/* Section 2.3 Host Controller Operational Registers */
काष्ठा ehci_regs अणु

	/* USBCMD: offset 0x00 */
	u32		command;

/* EHCI 1.1 addendum */
#घोषणा CMD_HIRD	(0xf<<24)	/* host initiated resume duration */
#घोषणा CMD_PPCEE	(1<<15)		/* per port change event enable */
#घोषणा CMD_FSP		(1<<14)		/* fully synchronized prefetch */
#घोषणा CMD_ASPE	(1<<13)		/* async schedule prefetch enable */
#घोषणा CMD_PSPE	(1<<12)		/* periodic schedule prefetch enable */
/* 23:16 is r/w पूर्णांकr rate, in microframes; शेष "8" == 1/msec */
#घोषणा CMD_PARK	(1<<11)		/* enable "park" on async qh */
#घोषणा CMD_PARK_CNT(c)	(((c)>>8)&3)	/* how many transfers to park क्रम */
#घोषणा CMD_LRESET	(1<<7)		/* partial reset (no ports, etc) */
#घोषणा CMD_IAAD	(1<<6)		/* "doorbell" पूर्णांकerrupt async advance */
#घोषणा CMD_ASE		(1<<5)		/* async schedule enable */
#घोषणा CMD_PSE		(1<<4)		/* periodic schedule enable */
/* 3:2 is periodic frame list size */
#घोषणा CMD_RESET	(1<<1)		/* reset HC not bus */
#घोषणा CMD_RUN		(1<<0)		/* start/stop HC */

	/* USBSTS: offset 0x04 */
	u32		status;
#घोषणा STS_PPCE_MASK	(0xff<<16)	/* Per-Port change event 1-16 */
#घोषणा STS_ASS		(1<<15)		/* Async Schedule Status */
#घोषणा STS_PSS		(1<<14)		/* Periodic Schedule Status */
#घोषणा STS_RECL	(1<<13)		/* Reclamation */
#घोषणा STS_HALT	(1<<12)		/* Not running (any reason) */
/* some bits reserved */
	/* these STS_* flags are also पूर्णांकr_enable bits (USBINTR) */
#घोषणा STS_IAA		(1<<5)		/* Interrupted on async advance */
#घोषणा STS_FATAL	(1<<4)		/* such as some PCI access errors */
#घोषणा STS_FLR		(1<<3)		/* frame list rolled over */
#घोषणा STS_PCD		(1<<2)		/* port change detect */
#घोषणा STS_ERR		(1<<1)		/* "error" completion (overflow, ...) */
#घोषणा STS_INT		(1<<0)		/* "normal" completion (लघु, ...) */

	/* USBINTR: offset 0x08 */
	u32		पूर्णांकr_enable;

	/* FRINDEX: offset 0x0C */
	u32		frame_index;	/* current microframe number */
	/* CTRLDSSEGMENT: offset 0x10 */
	u32		segment;	/* address bits 63:32 अगर needed */
	/* PERIODICLISTBASE: offset 0x14 */
	u32		frame_list;	/* poपूर्णांकs to periodic list */
	/* ASYNCLISTADDR: offset 0x18 */
	u32		async_next;	/* address of next async queue head */

	u32		reserved1[2];

	/* TXFILLTUNING: offset 0x24 */
	u32		txfill_tuning;	/* TX FIFO Tuning रेजिस्टर */
#घोषणा TXFIFO_DEFAULT	(8<<16)		/* FIFO burst threshold 8 */

	u32		reserved2[6];

	/* CONFIGFLAG: offset 0x40 */
	u32		configured_flag;
#घोषणा FLAG_CF		(1<<0)		/* true: we'll support "high speed" */

	/* PORTSC: offset 0x44 */
	u32		port_status[0];	/* up to N_PORTS */
/* EHCI 1.1 addendum */
#घोषणा PORTSC_SUSPEND_STS_ACK 0
#घोषणा PORTSC_SUSPEND_STS_NYET 1
#घोषणा PORTSC_SUSPEND_STS_STALL 2
#घोषणा PORTSC_SUSPEND_STS_ERR 3

#घोषणा PORT_DEV_ADDR	(0x7f<<25)		/* device address */
#घोषणा PORT_SSTS	(0x3<<23)		/* suspend status */
/* 31:23 reserved */
#घोषणा PORT_WKOC_E	(1<<22)		/* wake on overcurrent (enable) */
#घोषणा PORT_WKDISC_E	(1<<21)		/* wake on disconnect (enable) */
#घोषणा PORT_WKCONN_E	(1<<20)		/* wake on connect (enable) */
/* 19:16 क्रम port testing */
#घोषणा PORT_TEST(x)	(((x)&0xf)<<16)	/* Port Test Control */
#घोषणा PORT_TEST_PKT	PORT_TEST(0x4)	/* Port Test Control - packet test */
#घोषणा PORT_TEST_FORCE	PORT_TEST(0x5)	/* Port Test Control - क्रमce enable */
#घोषणा PORT_LED_OFF	(0<<14)
#घोषणा PORT_LED_AMBER	(1<<14)
#घोषणा PORT_LED_GREEN	(2<<14)
#घोषणा PORT_LED_MASK	(3<<14)
#घोषणा PORT_OWNER	(1<<13)		/* true: companion hc owns this port */
#घोषणा PORT_POWER	(1<<12)		/* true: has घातer (see PPC) */
#घोषणा PORT_USB11(x) (((x)&(3<<10)) == (1<<10))	/* USB 1.1 device */
#घोषणा PORT_LS_MASK	(3<<10)		/* Link status (SE0, K or J */
/* 9 reserved */
#घोषणा PORT_LPM	(1<<9)		/* LPM transaction */
#घोषणा PORT_RESET	(1<<8)		/* reset port */
#घोषणा PORT_SUSPEND	(1<<7)		/* suspend port */
#घोषणा PORT_RESUME	(1<<6)		/* resume it */
#घोषणा PORT_OCC	(1<<5)		/* over current change */
#घोषणा PORT_OC		(1<<4)		/* over current active */
#घोषणा PORT_PEC	(1<<3)		/* port enable change */
#घोषणा PORT_PE		(1<<2)		/* port enable */
#घोषणा PORT_CSC	(1<<1)		/* connect status change */
#घोषणा PORT_CONNECT	(1<<0)		/* device connected */
#घोषणा PORT_RWC_BITS   (PORT_CSC | PORT_PEC | PORT_OCC)

	u32		reserved3[9];

	/* USBMODE: offset 0x68 */
	u32		usbmode;	/* USB Device mode */
#घोषणा USBMODE_SDIS	(1<<3)		/* Stream disable */
#घोषणा USBMODE_BE	(1<<2)		/* BE/LE endianness select */
#घोषणा USBMODE_CM_HC	(3<<0)		/* host controller mode */
#घोषणा USBMODE_CM_IDLE	(0<<0)		/* idle state */

	u32		reserved4[6];

/* Moorestown has some non-standard रेजिस्टरs, partially due to the fact that
 * its EHCI controller has both TT and LPM support. HOSTPCx are extensions to
 * PORTSCx
 */
	/* HOSTPC: offset 0x84 */
	u32		hostpc[0];	/* HOSTPC extension */
#घोषणा HOSTPC_PHCD	(1<<22)		/* Phy घड़ी disable */
#घोषणा HOSTPC_PSPD	(3<<25)		/* Port speed detection */

	u32		reserved5[17];

	/* USBMODE_EX: offset 0xc8 */
	u32		usbmode_ex;	/* USB Device mode extension */
#घोषणा USBMODE_EX_VBPS	(1<<5)		/* VBus Power Select On */
#घोषणा USBMODE_EX_HC	(3<<0)		/* host controller mode */
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_EHCI_DEF_H */

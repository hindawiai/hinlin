<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* fhc.h: FHC and Clock board रेजिस्टर definitions.
 *
 * Copyright (C) 1997, 1999 David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित _SPARC64_FHC_H
#घोषणा _SPARC64_FHC_H

/* Clock board रेजिस्टर offsets. */
#घोषणा CLOCK_CTRL	0x00UL	/* Main control */
#घोषणा CLOCK_STAT1	0x10UL	/* Status one */
#घोषणा CLOCK_STAT2	0x20UL	/* Status two */
#घोषणा CLOCK_PWRSTAT	0x30UL	/* Power status */
#घोषणा CLOCK_PWRPRES	0x40UL	/* Power presence */
#घोषणा CLOCK_TEMP	0x50UL	/* Temperature */
#घोषणा CLOCK_IRQDIAG	0x60UL	/* IRQ diagnostics */
#घोषणा CLOCK_PWRSTAT2	0x70UL	/* Power status two */

#घोषणा CLOCK_CTRL_LLED		0x04	/* Left LED, 0 == on */
#घोषणा CLOCK_CTRL_MLED		0x02	/* Mid LED, 1 == on */
#घोषणा CLOCK_CTRL_RLED		0x01	/* RIght LED, 1 == on */

/* Firehose controller रेजिस्टर offsets */
#घोषणा FHC_PREGS_ID	0x00UL	/* FHC ID */
#घोषणा  FHC_ID_VERS		0xf0000000 /* Version of this FHC		*/
#घोषणा  FHC_ID_PARTID		0x0ffff000 /* Part ID code (0x0f9f == FHC)	*/
#घोषणा  FHC_ID_MANUF		0x0000007e /* Manufacturer (0x3e == SUN's JEDEC)*/
#घोषणा  FHC_ID_RESV		0x00000001 /* Read as one			*/
#घोषणा FHC_PREGS_RCS	0x10UL	/* FHC Reset Control/Status Register */
#घोषणा  FHC_RCS_POR		0x80000000 /* Last reset was a घातer cycle	*/
#घोषणा  FHC_RCS_SPOR		0x40000000 /* Last reset was sw घातer on reset	*/
#घोषणा  FHC_RCS_SXIR		0x20000000 /* Last reset was sw XIR reset	*/
#घोषणा  FHC_RCS_BPOR		0x10000000 /* Last reset was due to POR button	*/
#घोषणा  FHC_RCS_BXIR		0x08000000 /* Last reset was due to XIR button	*/
#घोषणा  FHC_RCS_WEVENT		0x04000000 /* CPU reset was due to wakeup event	*/
#घोषणा  FHC_RCS_CFATAL		0x02000000 /* Centerplane Fatal Error संकेतled	*/
#घोषणा  FHC_RCS_FENAB		0x01000000 /* Fatal errors elicit प्रणाली reset	*/
#घोषणा FHC_PREGS_CTRL	0x20UL	/* FHC Control Register */
#घोषणा  FHC_CONTROL_ICS	0x00100000 /* Ignore Centerplane Signals	*/
#घोषणा  FHC_CONTROL_FRST	0x00080000 /* Fatal Error Reset Enable		*/
#घोषणा  FHC_CONTROL_LFAT	0x00040000 /* AC/DC संकेतled a local error	*/
#घोषणा  FHC_CONTROL_SLINE	0x00010000 /* Firmware Synchronization Line	*/
#घोषणा  FHC_CONTROL_DCD	0x00008000 /* DC-->DC Converter Disable		*/
#घोषणा  FHC_CONTROL_POFF	0x00004000 /* AC/DC Controller PLL Disable	*/
#घोषणा  FHC_CONTROL_FOFF	0x00002000 /* FHC Controller PLL Disable	*/
#घोषणा  FHC_CONTROL_AOFF	0x00001000 /* CPU A SRAM/SBD Low Power Mode	*/
#घोषणा  FHC_CONTROL_BOFF	0x00000800 /* CPU B SRAM/SBD Low Power Mode	*/
#घोषणा  FHC_CONTROL_PSOFF	0x00000400 /* Turns off this FHC's घातer supply	*/
#घोषणा  FHC_CONTROL_IXIST	0x00000200 /* 0=FHC tells घड़ी board it exists	*/
#घोषणा  FHC_CONTROL_XMSTR	0x00000100 /* 1=Causes this FHC to be XIR master*/
#घोषणा  FHC_CONTROL_LLED	0x00000040 /* 0=Left LED ON			*/
#घोषणा  FHC_CONTROL_MLED	0x00000020 /* 1=Middle LED ON			*/
#घोषणा  FHC_CONTROL_RLED	0x00000010 /* 1=Right LED			*/
#घोषणा  FHC_CONTROL_BPINS	0x00000003 /* Spare Bidirectional Pins		*/
#घोषणा FHC_PREGS_BSR	0x30UL	/* FHC Board Status Register */
#घोषणा  FHC_BSR_DA64		0x00040000 /* Port A: 0=128bit 1=64bit data path */
#घोषणा  FHC_BSR_DB64		0x00020000 /* Port B: 0=128bit 1=64bit data path */
#घोषणा  FHC_BSR_BID		0x0001e000 /* Board ID                           */
#घोषणा  FHC_BSR_SA		0x00001c00 /* Port A UPA Speed (from the pins)   */
#घोषणा  FHC_BSR_SB		0x00000380 /* Port B UPA Speed (from the pins)   */
#घोषणा  FHC_BSR_NDIAG		0x00000040 /* Not in Diag Mode                   */
#घोषणा  FHC_BSR_NTBED		0x00000020 /* Not in TestBED Mode                */
#घोषणा  FHC_BSR_NIA		0x0000001c /* Jumper, bit 18 in PROM space       */
#घोषणा  FHC_BSR_SI		0x00000001 /* Spare input pin value              */
#घोषणा FHC_PREGS_ECC	0x40UL	/* FHC ECC Control Register (16 bits) */
#घोषणा FHC_PREGS_JCTRL	0xf0UL	/* FHC JTAG Control Register */
#घोषणा  FHC_JTAG_CTRL_MENAB	0x80000000 /* Indicates this is JTAG Master	 */
#घोषणा  FHC_JTAG_CTRL_MNONE	0x40000000 /* Indicates no JTAG Master present	 */
#घोषणा FHC_PREGS_JCMD	0x100UL	/* FHC JTAG Command Register */
#घोषणा FHC_IREG_IGN	0x00UL	/* This FHC's IGN */
#घोषणा FHC_FFREGS_IMAP	0x00UL	/* FHC Fanfail IMAP */
#घोषणा FHC_FFREGS_ICLR	0x10UL	/* FHC Fanfail ICLR */
#घोषणा FHC_SREGS_IMAP	0x00UL	/* FHC System IMAP */
#घोषणा FHC_SREGS_ICLR	0x10UL	/* FHC System ICLR */
#घोषणा FHC_UREGS_IMAP	0x00UL	/* FHC Uart IMAP */
#घोषणा FHC_UREGS_ICLR	0x10UL	/* FHC Uart ICLR */
#घोषणा FHC_TREGS_IMAP	0x00UL	/* FHC TOD IMAP */
#घोषणा FHC_TREGS_ICLR	0x10UL	/* FHC TOD ICLR */

#पूर्ण_अगर /* !(_SPARC64_FHC_H) */

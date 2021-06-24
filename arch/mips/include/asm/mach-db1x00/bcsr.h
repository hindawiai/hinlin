<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * bcsr.h -- Db1xxx/Pb1xxx Devboard CPLD रेजिस्टरs ("BCSR") असलtraction.
 *
 * All Alchemy development boards (except, of course, the weird PB1000)
 * have a few रेजिस्टरs in a CPLD with standardised layout; they mostly
 * only dअगरfer in base address and bit meanings in the RESETS and BOARD
 * रेजिस्टरs.
 *
 * All data taken from the official AMD board करोcumentation sheets.
 */

#अगर_अघोषित _DB1XXX_BCSR_H_
#घोषणा _DB1XXX_BCSR_H_


/* BCSR base addresses on various boards. BCSR base 2 refers to the
 * physical address of the first HEXLEDS रेजिस्टर, which is usually
 * a variable offset from the WHOAMI रेजिस्टर.
 */

/* DB1000, DB1100, DB1500, PB1100, PB1500 */
#घोषणा DB1000_BCSR_PHYS_ADDR	0x0E000000
#घोषणा DB1000_BCSR_HEXLED_OFS	0x01000000

#घोषणा DB1550_BCSR_PHYS_ADDR	0x0F000000
#घोषणा DB1550_BCSR_HEXLED_OFS	0x00400000

#घोषणा PB1550_BCSR_PHYS_ADDR	0x0F000000
#घोषणा PB1550_BCSR_HEXLED_OFS	0x00800000

#घोषणा DB1200_BCSR_PHYS_ADDR	0x19800000
#घोषणा DB1200_BCSR_HEXLED_OFS	0x00400000

#घोषणा PB1200_BCSR_PHYS_ADDR	0x0D800000
#घोषणा PB1200_BCSR_HEXLED_OFS	0x00400000

#घोषणा DB1300_BCSR_PHYS_ADDR	0x19800000
#घोषणा DB1300_BCSR_HEXLED_OFS	0x00400000

क्रमागत bcsr_id अणु
	/* BCSR base 1 */
	BCSR_WHOAMI	= 0,
	BCSR_STATUS,
	BCSR_SWITCHES,
	BCSR_RESETS,
	BCSR_PCMCIA,
	BCSR_BOARD,
	BCSR_LEDS,
	BCSR_SYSTEM,
	/* Au1200/1300 based boards */
	BCSR_INTCLR,
	BCSR_INTSET,
	BCSR_MASKCLR,
	BCSR_MASKSET,
	BCSR_SIGSTAT,
	BCSR_INTSTAT,

	/* BCSR base 2 */
	BCSR_HEXLEDS,
	BCSR_RSVD1,
	BCSR_HEXCLEAR,

	BCSR_CNT,
पूर्ण;

/* रेजिस्टर offsets, valid क्रम all Db1xxx/Pb1xxx boards */
#घोषणा BCSR_REG_WHOAMI		0x00
#घोषणा BCSR_REG_STATUS		0x04
#घोषणा BCSR_REG_SWITCHES	0x08
#घोषणा BCSR_REG_RESETS		0x0c
#घोषणा BCSR_REG_PCMCIA		0x10
#घोषणा BCSR_REG_BOARD		0x14
#घोषणा BCSR_REG_LEDS		0x18
#घोषणा BCSR_REG_SYSTEM		0x1c
/* Au1200/Au1300 based boards: CPLD IRQ muxer */
#घोषणा BCSR_REG_INTCLR		0x20
#घोषणा BCSR_REG_INTSET		0x24
#घोषणा BCSR_REG_MASKCLR	0x28
#घोषणा BCSR_REG_MASKSET	0x2c
#घोषणा BCSR_REG_SIGSTAT	0x30
#घोषणा BCSR_REG_INTSTAT	0x34

/* hexled control, offset from BCSR base 2 */
#घोषणा BCSR_REG_HEXLEDS	0x00
#घोषणा BCSR_REG_HEXCLEAR	0x08

/*
 * Register Bits and Pieces.
 */
#घोषणा BCSR_WHOAMI_DCID(x)		((x) & 0xf)
#घोषणा BCSR_WHOAMI_CPLD(x)		(((x) >> 4) & 0xf)
#घोषणा BCSR_WHOAMI_BOARD(x)		(((x) >> 8) & 0xf)

/* रेजिस्टर "WHOAMI" bits 11:8 identअगरy the board */
क्रमागत bcsr_whoami_boards अणु
	BCSR_WHOAMI_PB1500 = 1,
	BCSR_WHOAMI_PB1500R2,
	BCSR_WHOAMI_PB1100,
	BCSR_WHOAMI_DB1000,
	BCSR_WHOAMI_DB1100,
	BCSR_WHOAMI_DB1500,
	BCSR_WHOAMI_DB1550,
	BCSR_WHOAMI_PB1550_DDR,
	BCSR_WHOAMI_PB1550 = BCSR_WHOAMI_PB1550_DDR,
	BCSR_WHOAMI_PB1550_SDR,
	BCSR_WHOAMI_PB1200_DDR1,
	BCSR_WHOAMI_PB1200 = BCSR_WHOAMI_PB1200_DDR1,
	BCSR_WHOAMI_PB1200_DDR2,
	BCSR_WHOAMI_DB1200,
	BCSR_WHOAMI_DB1300,
पूर्ण;

/* STATUS reg.	Unless otherwise noted, they're valid on all boards.
 * PB1200 = DB1200.
 */
#घोषणा BCSR_STATUS_PC0VS		0x0003
#घोषणा BCSR_STATUS_PC1VS		0x000C
#घोषणा BCSR_STATUS_PC0FI		0x0010
#घोषणा BCSR_STATUS_PC1FI		0x0020
#घोषणा BCSR_STATUS_PB1550_SWAPBOOT	0x0040
#घोषणा BCSR_STATUS_SRAMWIDTH		0x0080
#घोषणा BCSR_STATUS_FLASHBUSY		0x0100
#घोषणा BCSR_STATUS_ROMBUSY		0x0400
#घोषणा BCSR_STATUS_SD0WP		0x0400	/* DB1200/DB1300:SD1 */
#घोषणा BCSR_STATUS_SD1WP		0x0800
#घोषणा BCSR_STATUS_USBOTGID		0x0800	/* PB/DB1550 */
#घोषणा BCSR_STATUS_DB1000_SWAPBOOT	0x2000
#घोषणा BCSR_STATUS_DB1200_SWAPBOOT	0x0040	/* DB1200/1300 */
#घोषणा BCSR_STATUS_IDECBLID		0x0200	/* DB1200/1300 */
#घोषणा BCSR_STATUS_DB1200_U0RXD	0x1000	/* DB1200 */
#घोषणा BCSR_STATUS_DB1200_U1RXD	0x2000	/* DB1200 */
#घोषणा BCSR_STATUS_FLASHDEN		0xC000
#घोषणा BCSR_STATUS_DB1550_U0RXD	0x1000	/* DB1550 */
#घोषणा BCSR_STATUS_DB1550_U3RXD	0x2000	/* DB1550 */
#घोषणा BCSR_STATUS_PB1550_U0RXD	0x1000	/* PB1550 */
#घोषणा BCSR_STATUS_PB1550_U1RXD	0x2000	/* PB1550 */
#घोषणा BCSR_STATUS_PB1550_U3RXD	0x8000	/* PB1550 */

#घोषणा BCSR_STATUS_CFWP		0x4000	/* DB1300 */
#घोषणा BCSR_STATUS_USBOCn		0x2000	/* DB1300 */
#घोषणा BCSR_STATUS_OTGOCn		0x1000	/* DB1300 */
#घोषणा BCSR_STATUS_DCDMARQ		0x0010	/* DB1300 */
#घोषणा BCSR_STATUS_IDEDMARQ		0x0020	/* DB1300 */

/* DB/PB1000,1100,1500,1550 */
#घोषणा BCSR_RESETS_PHY0		0x0001
#घोषणा BCSR_RESETS_PHY1		0x0002
#घोषणा BCSR_RESETS_DC			0x0004
#घोषणा BCSR_RESETS_FIR_SEL		0x2000
#घोषणा BCSR_RESETS_IRDA_MODE_MASK	0xC000
#घोषणा BCSR_RESETS_IRDA_MODE_FULL	0x0000
#घोषणा BCSR_RESETS_PB1550_WSCFSM	0x2000
#घोषणा BCSR_RESETS_IRDA_MODE_OFF	0x4000
#घोषणा BCSR_RESETS_IRDA_MODE_2_3	0x8000
#घोषणा BCSR_RESETS_IRDA_MODE_1_3	0xC000
#घोषणा BCSR_RESETS_DMAREQ		0x8000	/* PB1550 */

#घोषणा BCSR_BOARD_PCIM66EN		0x0001
#घोषणा BCSR_BOARD_SD0PWR		0x0040
#घोषणा BCSR_BOARD_SD1PWR		0x0080
#घोषणा BCSR_BOARD_PCIM33		0x0100
#घोषणा BCSR_BOARD_PCIEXTARB		0x0200
#घोषणा BCSR_BOARD_GPIO200RST		0x0400
#घोषणा BCSR_BOARD_PCICLKOUT		0x0800
#घोषणा BCSR_BOARD_PB1100_SD0PWR	0x0400
#घोषणा BCSR_BOARD_PB1100_SD1PWR	0x0800
#घोषणा BCSR_BOARD_PCICFG		0x1000
#घोषणा BCSR_BOARD_SPISEL		0x2000	/* PB/DB1550 */
#घोषणा BCSR_BOARD_SD0WP		0x4000	/* DB1100 */
#घोषणा BCSR_BOARD_SD1WP		0x8000	/* DB1100 */


/* DB/PB1200/1300 */
#घोषणा BCSR_RESETS_ETH			0x0001
#घोषणा BCSR_RESETS_CAMERA		0x0002
#घोषणा BCSR_RESETS_DC			0x0004
#घोषणा BCSR_RESETS_IDE			0x0008
#घोषणा BCSR_RESETS_TV			0x0010	/* DB1200/1300 */
/* Not resets but in the same रेजिस्टर */
#घोषणा BCSR_RESETS_PWMR1MUX		0x0800	/* DB1200 */
#घोषणा BCSR_RESETS_PB1200_WSCFSM	0x0800	/* PB1200 */
#घोषणा BCSR_RESETS_PSC0MUX		0x1000
#घोषणा BCSR_RESETS_PSC1MUX		0x2000
#घोषणा BCSR_RESETS_SPISEL		0x4000
#घोषणा BCSR_RESETS_SD1MUX		0x8000	/* PB1200 */

#घोषणा BCSR_RESETS_VDDQSHDN		0x0200	/* DB1300 */
#घोषणा BCSR_RESETS_OTPPGM		0x0400	/* DB1300 */
#घोषणा BCSR_RESETS_OTPSCLK		0x0800	/* DB1300 */
#घोषणा BCSR_RESETS_OTPWRPROT		0x1000	/* DB1300 */
#घोषणा BCSR_RESETS_OTPCSB		0x2000	/* DB1300 */
#घोषणा BCSR_RESETS_OTGPWR		0x4000	/* DB1300 */
#घोषणा BCSR_RESETS_USBHPWR		0x8000	/* DB1300 */

#घोषणा BCSR_BOARD_LCDVEE		0x0001
#घोषणा BCSR_BOARD_LCDVDD		0x0002
#घोषणा BCSR_BOARD_LCDBL		0x0004
#घोषणा BCSR_BOARD_CAMSNAP		0x0010
#घोषणा BCSR_BOARD_CAMPWR		0x0020
#घोषणा BCSR_BOARD_SD0PWR		0x0040
#घोषणा BCSR_BOARD_CAMCS		0x0010	/* DB1300 */
#घोषणा BCSR_BOARD_HDMI_DE		0x0040	/* DB1300 */

#घोषणा BCSR_SWITCHES_DIP		0x00FF
#घोषणा BCSR_SWITCHES_DIP_1		0x0080
#घोषणा BCSR_SWITCHES_DIP_2		0x0040
#घोषणा BCSR_SWITCHES_DIP_3		0x0020
#घोषणा BCSR_SWITCHES_DIP_4		0x0010
#घोषणा BCSR_SWITCHES_DIP_5		0x0008
#घोषणा BCSR_SWITCHES_DIP_6		0x0004
#घोषणा BCSR_SWITCHES_DIP_7		0x0002
#घोषणा BCSR_SWITCHES_DIP_8		0x0001
#घोषणा BCSR_SWITCHES_ROTARY		0x0F00


#घोषणा BCSR_PCMCIA_PC0VPP		0x0003
#घोषणा BCSR_PCMCIA_PC0VCC		0x000C
#घोषणा BCSR_PCMCIA_PC0DRVEN		0x0010
#घोषणा BCSR_PCMCIA_PC0RST		0x0080
#घोषणा BCSR_PCMCIA_PC1VPP		0x0300
#घोषणा BCSR_PCMCIA_PC1VCC		0x0C00
#घोषणा BCSR_PCMCIA_PC1DRVEN		0x1000
#घोषणा BCSR_PCMCIA_PC1RST		0x8000


#घोषणा BCSR_LEDS_DECIMALS		0x0003
#घोषणा BCSR_LEDS_LED0			0x0100
#घोषणा BCSR_LEDS_LED1			0x0200
#घोषणा BCSR_LEDS_LED2			0x0400
#घोषणा BCSR_LEDS_LED3			0x0800


#घोषणा BCSR_SYSTEM_RESET		0x8000	/* clear to reset */
#घोषणा BCSR_SYSTEM_PWROFF		0x4000	/* set to घातer off */
#घोषणा BCSR_SYSTEM_VDDI		0x001F	/* PB1xxx boards */
#घोषणा BCSR_SYSTEM_DEBUGCSMASK		0x003F	/* DB1300 */
#घोषणा BCSR_SYSTEM_UDMAMODE		0x0100	/* DB1300 */
#घोषणा BCSR_SYSTEM_WAKEONIRQ		0x0200	/* DB1300 */
#घोषणा BCSR_SYSTEM_VDDI1300		0x3C00	/* DB1300 */



/* initialize BCSR क्रम a board. Provide the PHYSICAL addresses of both
 * BCSR spaces.
 */
व्योम __init bcsr_init(अचिन्हित दीर्घ bcsr1_phys, अचिन्हित दीर्घ bcsr2_phys);

/* पढ़ो a board रेजिस्टर */
अचिन्हित लघु bcsr_पढ़ो(क्रमागत bcsr_id reg);

/* ग_लिखो to a board रेजिस्टर */
व्योम bcsr_ग_लिखो(क्रमागत bcsr_id reg, अचिन्हित लघु val);

/* modअगरy a रेजिस्टर. clear bits set in 'clr', set bits set in 'set' */
व्योम bcsr_mod(क्रमागत bcsr_id reg, अचिन्हित लघु clr, अचिन्हित लघु set);

/* install CPLD IRQ demuxer (DB1200/PB1200) */
व्योम __init bcsr_init_irq(पूर्णांक csc_start, पूर्णांक csc_end, पूर्णांक hook_irq);

#पूर्ण_अगर

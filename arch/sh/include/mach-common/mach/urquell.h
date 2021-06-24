<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_URQUELL_H
#घोषणा __MACH_URQUELL_H

/*
 * ------ 0x00000000 ------------------------------------
 *  CS0 | (SW1,SW47)    EEPROM, SRAM, NOR FLASH
 * -----+ 0x04000000 ------------------------------------
 *  CS1 | (SW47)        SRAM, SRAM-LAN-PCMCIA, NOR FLASH
 * -----+ 0x08000000 ------------------------------------
 *  CS2 |               DDR3
 *  CS3 |
 * -----+ 0x10000000 ------------------------------------
 *  CS4 |               PCIe
 * -----+ 0x14000000 ------------------------------------
 *  CS5 | (SW47)        LRAM/URAM, SRAM-LAN-PCMCIA
 * -----+ 0x18000000 ------------------------------------
 *  CS6 |               ATA, न_अंकD FLASH
 * -----+ 0x1c000000 ------------------------------------
 *  CS7 |               SH7786 रेजिस्टर
 * -----+------------------------------------------------
 */

#घोषणा NOR_FLASH_ADDR	0x00000000
#घोषणा NOR_FLASH_SIZE	0x04000000

#घोषणा CS1_BASE	0x05000000
#घोषणा CS5_BASE	0x15000000
#घोषणा FPGA_BASE	CS1_BASE

#घोषणा BOARDREG(ofs)	(FPGA_BASE + ofs##_OFS)
#घोषणा UBOARDREG(ofs)	(0xa0000000 + FPGA_BASE + ofs##_OFS)

#घोषणा SRSTR_OFS	0x0000 /* System reset रेजिस्टर */
#घोषणा BDMR_OFS	0x0010 /* Board operating mode resister */
#घोषणा IRL0SR_OFS	0x0020 /* IRL0 Status रेजिस्टर */
#घोषणा IRL0MSKR_OFS	0x0030 /* IRL0 Mask रेजिस्टर */
#घोषणा IRL1SR_OFS	0x0040 /* IRL1 Status रेजिस्टर */
#घोषणा IRL1MSKR_OFS	0x0050 /* IRL1 Mask रेजिस्टर */
#घोषणा IRL2SR_OFS	0x0060 /* IRL2 Status रेजिस्टर */
#घोषणा IRL2MSKR_OFS	0x0070 /* IRL2 Mask रेजिस्टर */
#घोषणा IRL3SR_OFS	0x0080 /* IRL3 Status रेजिस्टर */
#घोषणा IRL3MSKR_OFS	0x0090 /* IRL3 Mask रेजिस्टर */
#घोषणा SOFTINTR_OFS	0x0120 /* Softwear Interrupt रेजिस्टर */
#घोषणा SLEDR_OFS	0x0130 /* LED control resister */
#घोषणा MAPSCIFSWR_OFS	0x0140 /* Map/SCIF Switch रेजिस्टर */
#घोषणा FPVERR_OFS	0x0150 /* FPGA Version रेजिस्टर */
#घोषणा FPDATER_OFS	0x0160 /* FPGA Date रेजिस्टर */
#घोषणा FPYEARR_OFS	0x0170 /* FPGA Year रेजिस्टर */
#घोषणा TCLKCR_OFS	0x0180 /* TCLK Control रेजिस्टर */
#घोषणा DIPSWMR_OFS	0x1000 /* DIPSW monitor रेजिस्टर */
#घोषणा FPODR_OFS	0x1010 /* Output port data रेजिस्टर */
#घोषणा ATACNR_OFS	0x1020 /* ATA-CN Control/status रेजिस्टर */
#घोषणा FPINDR_OFS	0x1030 /* Input port data रेजिस्टर */
#घोषणा MDSWMR_OFS	0x1040 /* MODE SW monitor रेजिस्टर */
#घोषणा DDR3BUPCR_OFS	0x1050 /* DDR3 Backup control रेजिस्टर */
#घोषणा SSICODECCR_OFS	0x1060 /* SSI-CODEC control रेजिस्टर */
#घोषणा PCIESLOTSR_OFS	0x1070 /* PCIexpress Slot status रेजिस्टर */
#घोषणा ETHERPORTSR_OFS	0x1080 /* EtherPhy Port status रेजिस्टर */
#घोषणा LATCHCR_OFS	0x3000 /* Latch control रेजिस्टर */
#घोषणा LATCUAR_OFS	0x3010 /* Latch upper address रेजिस्टर */
#घोषणा LATCLAR_OFS	0x3012 /* Latch lower address रेजिस्टर */
#घोषणा LATCLUDR_OFS	0x3024 /* Latch D31-16 रेजिस्टर */
#घोषणा LATCLLDR_OFS	0x3026 /* Latch D15-0 रेजिस्टर */

#घोषणा CHARLED_OFS	0x2000 /* Character LED */

#पूर्ण_अगर  /* __MACH_URQUELL_H */

